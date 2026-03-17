/**
 * lsp_io.c — LSP 用 stdin/stdout 读写 + JSON 文档提取（C 原语）
 *
 * 提供 lsp_read_c / lsp_write_c，供 lsp.su 调用，避免 lsp 依赖 std.fs 导致与 pipeline 重复符号。
 * lsp_extract_document_text：从 didOpen/didChange 的 JSON body 中提取 "text" 字段（params.textDocument.text 或 contentChanges[0].text），
 * 解码 JSON 转义（\", \\, \n, \r, \t）后写入 out_buf，返回写入长度，失败返回 -1。
 * 动态缓冲：lsp_alloc / lsp_free 按需分配；lsp_set_document_from_body / lsp_get_document_ptr/len 维护当前文档（堆上），无固定上限。
 */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lsp/lsp_diag.h"

/** 单条消息 body 最大允许长度（防恶意超大请求），实际分配按 content_len 动态；64MB。 */
#define LSP_BODY_SAFETY_CAP (64 * 1024 * 1024)

static int lsp_find_text_value(const uint8_t *body, int len, uint8_t *out_buf, int out_cap);
static int lsp_find_key_after(const uint8_t *body, int len, int start, const char *key);
static int lsp_parse_int(const uint8_t *body, int len, int offset, int *out);
static int line_char_to_offset(const uint8_t *doc, int len, int line, int character);
static int parse_first_content_change(const uint8_t *body, int len,
    int *out_start_line, int *out_start_char, int *out_end_line, int *out_end_char,
    uint8_t *out_text, int out_text_cap, int *out_text_len);

static uint8_t *s_doc_ptr = NULL;
static int s_doc_len = 0;

void *lsp_alloc(size_t size) {
    if (size == 0 || size > (size_t)LSP_BODY_SAFETY_CAP) return NULL;
    return malloc(size);
}

void lsp_free(void *ptr) {
    if (ptr) free(ptr);
}

/** 供 .su 判断指针是否为空（lsp_alloc 失败时返回 NULL）。 */
int lsp_is_null(const uint8_t *ptr) {
    return ptr == NULL ? 1 : 0;
}

/** 若 body 含 contentChanges 且当前有文档，则解析并应用第一项 range 替换，成功返回 1，否则 0。 */
static int try_apply_content_changes(const uint8_t *body, int body_len) {
    if (!s_doc_ptr || s_doc_len < 0) return 0;
    uint8_t text_buf[256 * 1024];
    int text_len = 0;
    int start_line = 0, start_char = 0, end_line = 0, end_char = 0;
    if (!parse_first_content_change(body, body_len, &start_line, &start_char, &end_line, &end_char,
                                    text_buf, (int)sizeof(text_buf), &text_len))
        return 0;
    int start_off = line_char_to_offset(s_doc_ptr, s_doc_len, start_line, start_char);
    int end_off = line_char_to_offset(s_doc_ptr, s_doc_len, end_line, end_char);
    if (start_off < 0 || end_off < 0 || end_off < start_off) return 0;
    size_t new_len = (size_t)start_off + (size_t)text_len + (size_t)(s_doc_len - end_off);
    if (new_len > (size_t)LSP_BODY_SAFETY_CAP) return 0;
    uint8_t *new_ptr = (uint8_t *)malloc(new_len + 1);
    if (!new_ptr) return 0;
    memcpy(new_ptr, s_doc_ptr, (size_t)start_off);
    memcpy(new_ptr + start_off, text_buf, (size_t)text_len);
    memcpy(new_ptr + start_off + text_len, s_doc_ptr + end_off, (size_t)(s_doc_len - end_off));
    new_ptr[new_len] = '\0';
    free(s_doc_ptr);
    s_doc_ptr = new_ptr;
    s_doc_len = (int)new_len;
    return 1;
}

/** 从 didOpen/didChange 的 body 中提取文档内容，存入内部缓冲（替换旧文档）。若有 contentChanges 且当前有文档则做增量 range 替换，否则整份替换。先使 LSP 模块缓存失效，再释放旧缓冲，避免旧 AST 指向已释放内存。 */
void lsp_set_document_from_body(const uint8_t *body, int body_len) {
    if (!body || body_len <= 0) return;
    if (s_doc_ptr && try_apply_content_changes(body, body_len)) {
        lsp_diag_invalidate_cache();
        return;
    }
    lsp_diag_invalidate_cache();
    if (s_doc_ptr) { free(s_doc_ptr); s_doc_ptr = NULL; s_doc_len = 0; }
    s_doc_ptr = (uint8_t *)malloc((size_t)body_len + 1);
    if (!s_doc_ptr) return;
    int n = lsp_find_text_value(body, body_len, s_doc_ptr, body_len + 1);
    if (n >= 0) {
        s_doc_ptr[n] = '\0';
        s_doc_len = n;
    } else {
        free(s_doc_ptr);
        s_doc_ptr = NULL;
        s_doc_len = 0;
    }
}

uint8_t *lsp_get_document_ptr(void) {
    return s_doc_ptr;
}

int lsp_get_document_len(void) {
    return s_doc_len;
}

/** 从 fd 读最多 count 字节到 buf；返回读入字节数，0=EOF，-1=错误。 */
long lsp_read_c(int fd, uint8_t *buf, size_t count) {
    ssize_t n = read(fd, buf, count);
    return (long)n;
}

/** 从 fd 读最多 count 字节到 buf[offset..offset+count)；供 .su 端避免指针运算，返回读入字节数，0=EOF，-1=错误。 */
long lsp_read_at(int fd, uint8_t *buf, size_t offset, size_t count) {
    if (count == 0) return 0;
    ssize_t n = read(fd, buf + offset, count);
    return (long)n;
}

#define LSP_HEADER_BUF_SIZE 4096
/** 上次 read 后未消费的数据，供下一条消息使用，避免一次 read 含多条消息时丢弃后续消息。 */
static uint8_t s_read_leftover[LSP_HEADER_BUF_SIZE * 2];
static int s_read_leftover_n = 0;

/** 从 buf[0..n) 中找 "Content-Length: " 后的数字，写入 *out，成功返回 1，否则 0。 */
static int parse_content_length_from_buf(const uint8_t *buf, int n, int *out) {
    const char *key = "Content-Length: ";
    const int key_len = 16;
    if (n < key_len || !out) return 0;
    *out = 0;
    for (int i = 0; i + key_len <= n; i++) {
        int match = 1;
        for (int j = 0; j < key_len; j++)
            if (buf[i + j] != (uint8_t)key[j]) { match = 0; break; }
        if (!match) continue;
        int start = i + key_len;
        while (start < n && buf[start] >= '0' && buf[start] <= '9') {
            *out = *out * 10 + (buf[start] - '0');
            start++;
        }
        return 1;
    }
    return 0;
}

/**
 * 从 fd 读取一条 LSP 消息（Header + Body）：先使用 s_read_leftover（若有），再 read 补足；
 * 解析 Content-Length，将 body 写入 body_out，返回 body 长度；未消费的字节保留到 s_read_leftover 供下次调用。
 * 失败或 EOF 返回 -1。
 */
long lsp_read_message(int fd, uint8_t *body_out, int body_cap) {
    uint8_t *buf = s_read_leftover;
    int n = s_read_leftover_n;
    s_read_leftover_n = 0;
    if (n < (int)sizeof(s_read_leftover)) {
        ssize_t got = read(fd, buf + n, (size_t)(sizeof(s_read_leftover) - n));
        if (got > 0) n += (int)got;
    }
    if (n <= 0) return -1;
    int i = 0;
    for (; i + 4 <= n; i++)
        if (buf[i] == '\r' && buf[i+1] == '\n' && buf[i+2] == '\r' && buf[i+3] == '\n')
            break;
    if (i + 4 > n) return -1;
    int header_end = i + 4;
    int content_len = 0;
    if (!parse_content_length_from_buf(buf, i, &content_len)) return -1;
    if (content_len <= 0 || content_len > body_cap || content_len > LSP_BODY_SAFETY_CAP) return -1;
    int body_in_buf = n - header_end;
    if (body_in_buf > content_len) body_in_buf = content_len;
    memcpy(body_out, buf + header_end, (size_t)body_in_buf);
    if (content_len > body_in_buf) {
        size_t remain = (size_t)(content_len - body_in_buf);
        ssize_t got = read(fd, body_out + body_in_buf, remain);
        if (got != (ssize_t)remain) return -1;
    }
    /* 将本消息之后的数据保留到 s_read_leftover，供下一条消息使用 */
    int consumed = header_end + content_len;
    if (consumed < n) {
        int rest = n - consumed;
        memmove(s_read_leftover, buf + consumed, (size_t)rest);
        s_read_leftover_n = rest;
    }
    return (long)content_len;
}

/** 向 fd 写 buf[0..count-1]；返回写入字节数，-1=错误。 */
long lsp_write_c(int fd, const uint8_t *buf, size_t count) {
    ssize_t n = write(fd, buf, count);
    return (long)n;
}

/** 将 (line, character) 转为文档中的字节偏移；line/character 为 0-based。 */
static int line_char_to_offset(const uint8_t *doc, int len, int line, int character) {
    int cur_line = 0;
    int i = 0;
    while (i < len && cur_line < line) {
        if (doc[i] == '\n') cur_line++;
        i++;
    }
    if (cur_line != line) return -1;
    int col = 0;
    while (col < character && i < len && doc[i] != '\n') {
        col++;
        i++;
    }
    if (col != character) return -1;
    return i;
}

/** 从 body 中解析 contentChanges[0]：range.start.line/character、range.end.line/character、text；成功返回 1 并写入 *out_*，否则 0。 */
static int parse_first_content_change(const uint8_t *body, int len,
    int *out_start_line, int *out_start_char, int *out_end_line, int *out_end_char,
    uint8_t *out_text, int out_text_cap, int *out_text_len) {
    const char *key_cc = "\"contentChanges\":[";
    int key_cc_len = 16;
    int i = 0;
    for (; i + key_cc_len <= len; i++)
        if (memcmp(body + i, key_cc, (size_t)key_cc_len) == 0) break;
    if (i + key_cc_len > len) return 0;
    i += key_cc_len;
    while (i < len && (body[i] == ' ' || body[i] == '\n' || body[i] == '\r')) i++;
    if (i >= len || body[i] != '{') return 0;
    int pos = i + 1;
    int line_start = lsp_find_key_after(body, len, pos, "\"range\":");
    if (line_start < 0) return 0;
    int start_line_start = lsp_find_key_after(body, len, line_start, "\"start\":");
    if (start_line_start < 0) return 0;
    int sl = lsp_find_key_after(body, len, start_line_start, "\"line\":");
    if (sl < 0) return 0;
    int sc = lsp_find_key_after(body, len, start_line_start, "\"character\":");
    if (sc < 0) return 0;
    int el = lsp_find_key_after(body, len, line_start, "\"end\":");
    if (el < 0) return 0;
    int elv = lsp_find_key_after(body, len, el, "\"line\":");
    if (elv < 0) return 0;
    int ec = lsp_find_key_after(body, len, el, "\"character\":");
    if (ec < 0) return 0;
    int tl = lsp_find_key_after(body, len, pos, "\"text\":\"");
    if (tl < 0) return 0;
    int line1 = 0, char1 = 0, line2 = 0, char2 = 0;
    if (lsp_parse_int(body, len, sl, &line1) < 0) return 0;
    if (lsp_parse_int(body, len, sc, &char1) < 0) return 0;
    if (lsp_parse_int(body, len, elv, &line2) < 0) return 0;
    if (lsp_parse_int(body, len, ec, &char2) < 0) return 0;
    int text_len = 0;
    while (tl < len && text_len < out_text_cap - 1) {
        uint8_t c = body[tl];
        if (c == '"' && (tl == 0 || body[tl - 1] != '\\')) break;
        if (c == '\\' && tl + 1 < len) {
            tl++;
            if (body[tl] == 'n') { out_text[text_len++] = '\n'; tl++; continue; }
            if (body[tl] == 'r') { out_text[text_len++] = '\r'; tl++; continue; }
            if (body[tl] == 't') { out_text[text_len++] = '\t'; tl++; continue; }
            if (body[tl] == '"' || body[tl] == '\\') { out_text[text_len++] = body[tl]; tl++; continue; }
            out_text[text_len++] = body[tl];
            tl++;
            continue;
        }
        out_text[text_len++] = c;
        tl++;
    }
    out_text[text_len] = '\0';
    *out_start_line = line1;
    *out_start_char = char1;
    *out_end_line = line2;
    *out_end_char = char2;
    *out_text_len = text_len;
    return 1;
}

/** 在 body[0..len) 中找第一个 "\"text\":\""，然后取其后 JSON 字符串值到 out_buf，做 unescape；返回 out 长度，未找到或出错 -1。 */
static int lsp_find_text_value(const uint8_t *body, int len, uint8_t *out_buf, int out_cap) {
    const char *key = "\"text\":\"";
    const int key_len = 8;
    int i = 0;
    while (i + key_len <= len) {
        if (body[i] == (uint8_t)key[0] && body[i+1] == (uint8_t)key[1] && body[i+2] == (uint8_t)key[2] &&
            body[i+3] == (uint8_t)key[3] && body[i+4] == (uint8_t)key[4] && body[i+5] == (uint8_t)key[5] &&
            body[i+6] == (uint8_t)key[6] && body[i+7] == (uint8_t)key[7]) {
            int start = i + key_len;
            int out_len = 0;
            while (start < len && out_len < out_cap - 1) {
                uint8_t c = body[start];
                if (c == '"' && (start == 0 || body[start-1] != '\\'))
                    break;
                if (c == '\\' && start + 1 < len) {
                    start++;
                    if (body[start] == 'n') { out_buf[out_len++] = '\n'; start++; continue; }
                    if (body[start] == 'r') { out_buf[out_len++] = '\r'; start++; continue; }
                    if (body[start] == 't') { out_buf[out_len++] = '\t'; start++; continue; }
                    if (body[start] == '"' || body[start] == '\\') { out_buf[out_len++] = body[start]; start++; continue; }
                    /* 其他转义（如 \u）暂不展开，原样输出下一字符 */
                    out_buf[out_len++] = body[start];
                    start++;
                    continue;
                }
                out_buf[out_len++] = c;
                start++;
            }
            out_buf[out_len] = '\0';
            return (int)out_len;
        }
        i++;
    }
    return -1;
}

int lsp_extract_document_text(const uint8_t *body, int len, uint8_t *out_buf, int out_cap) {
    if (!body || !out_buf || out_cap <= 0 || len <= 0) return -1;
    return lsp_find_text_value(body, len, out_buf, out_cap);
}

/**
 * 构建 InitializeResult JSON，含 capabilities（textDocumentSync、definitionProvider、referencesProvider、hoverProvider）与 serverInfo。
 * 写入 out_buf，返回写入长度，失败返回 -1。
 */
int lsp_build_initialize_result(uint8_t *out_buf, int out_cap) {
    const char *json = "{\"jsonrpc\":\"2.0\",\"id\":1,\"result\":{"
        "\"capabilities\":{"
        "\"textDocumentSync\":1,"
        "\"definitionProvider\":true,"
        "\"referencesProvider\":true,"
        "\"hoverProvider\":true,"
        "\"documentFormattingProvider\":true"
        "},"
        "\"serverInfo\":{\"name\":\"shulang\",\"version\":\"0.1.0\"}"
        "}}";
    int len = 0;
    while (json[len] != '\0') len++;
    if (len >= out_cap) return -1;
    for (int i = 0; i < len; i++) out_buf[i] = (uint8_t)json[i];
    return len;
}

/**
 * 构建 JSON-RPC 响应正文：{"jsonrpc":"2.0","id":<id>,"result":<result>}。
 * id_val 为请求中的数字 id；result_ptr 为 result 内容（如 "[]"、"null"），result_len 为其长度。
 * 写入 out_buf，返回写入长度，失败返回 -1。
 */
int lsp_build_response_with_result(int id_val, const uint8_t *result_ptr, int result_len,
                                   uint8_t *out_buf, int out_cap) {
    const char *prefix = "{\"jsonrpc\":\"2.0\",\"id\":";
    const char *mid = ",\"result\":";
    const char *suffix = "}";
    int i = 0, k = 0;
    if (!out_buf || out_cap <= 0) return -1;
    for (; prefix[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)prefix[i];
    if (k >= out_cap - 12) return -1;
    /* 将 id_val 转为十进制写入（支持 0 与正整数） */
    char id_buf[16];
    int id_len = 0;
    int n = id_val;
    if (n < 0) n = -n;
    if (n == 0) {
        id_buf[id_len++] = '0';
    } else {
        while (n > 0 && id_len < 15) { id_buf[id_len++] = (char)('0' + n % 10); n /= 10; }
    }
    int j = id_len - 1;
    while (j >= 0 && k < out_cap - 1) { out_buf[k++] = (uint8_t)id_buf[j--]; }
    for (i = 0; mid[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)mid[i];
    for (i = 0; i < result_len && k < out_cap - 1; i++, k++) out_buf[k] = result_ptr[i];
    for (i = 0; suffix[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)suffix[i];
    return k;
}

/** 在 body[0..len) 中从 start 起找 key（如 "\"line\":\"），返回 key 结束后的偏移，未找到返回 -1。 */
static int lsp_find_key_after(const uint8_t *body, int len, int start, const char *key) {
    int key_len = 0;
    while (key[key_len] != '\0') key_len++;
    while (start + key_len <= len) {
        int match = 1;
        for (int j = 0; j < key_len; j++)
            if (body[start + j] != (uint8_t)key[j]) { match = 0; break; }
        if (match) return start + key_len;
        start++;
    }
    return -1;
}

/** 从 offset 起解析一个非负整数，写入 *out，返回解析结束后的偏移；非法返回 -1。 */
static int lsp_parse_int(const uint8_t *body, int len, int offset, int *out) {
    if (offset >= len || !out) return -1;
    *out = 0;
    while (offset < len && body[offset] >= '0' && body[offset] <= '9') {
        *out = *out * 10 + (body[offset] - '0');
        offset++;
    }
    return offset;
}

/**
 * 从 definition/hover 等请求的 body 中提取 params.position：line 与 character（0-based）。
 * 写入 *out_line、*out_character，成功返回 0，失败返回 -1。
 */
int lsp_extract_position_from_params(const uint8_t *body, int len, int *out_line, int *out_character) {
    if (!body || len <= 0 || !out_line || !out_character) return -1;
    int pos = lsp_find_key_after(body, len, 0, "\"position\":");
    if (pos < 0) return -1;
    int line_start = lsp_find_key_after(body, len, pos, "\"line\":");
    if (line_start < 0) return -1;
    int char_start = lsp_find_key_after(body, len, pos, "\"character\":");
    if (char_start < 0) return -1;
    int line_end = lsp_parse_int(body, len, line_start, out_line);
    if (line_end < 0) return -1;
    int char_end = lsp_parse_int(body, len, char_start, out_character);
    if (char_end < 0) return -1;
    return 0;
}

/**
 * 从 definition/hover 等请求的 body 中提取 params.textDocument.uri（JSON 字符串）。
 * 写入 uri_buf，做简单 unescape；返回写入长度，失败返回 -1。
 */
int lsp_extract_uri_from_params(const uint8_t *body, int len, uint8_t *uri_buf, int uri_cap) {
    if (!body || !uri_buf || uri_cap <= 0) return -1;
    int start = lsp_find_key_after(body, len, 0, "\"uri\":\"");
    if (start < 0) return -1;
    int out_len = 0;
    while (start < len && out_len < uri_cap - 1) {
        uint8_t c = body[start];
        if (c == '"' && (start == 0 || body[start - 1] != '\\')) break;
        if (c == '\\' && start + 1 < len) {
            start++;
            if (body[start] == '"' || body[start] == '\\') { uri_buf[out_len++] = body[start]; start++; continue; }
        }
        uri_buf[out_len++] = c;
        start++;
    }
    uri_buf[out_len] = '\0';
    return out_len;
}

#define LSP_DEFINITION_RESULT_MAX 2048

/**
 * 构建 textDocument/definition 的完整 JSON-RPC 响应正文。
 * 从 body 解析 position 与 uri，用 doc_buf/doc_len 跑 lsp_definition_at；找到则 result 为 Location，否则为 null。
 * 写入 out_buf，返回长度，失败返回 -1。
 */
int lsp_build_definition_response(int id_val, const uint8_t *body, int body_len,
                                  const uint8_t *doc_buf, int doc_len,
                                  uint8_t *out_buf, int out_cap) {
    if (!body || !out_buf || out_cap <= 0) return -1;
    int line0 = 0, char0 = 0;
    if (lsp_extract_position_from_params(body, body_len, &line0, &char0) != 0)
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    int def_line = 0, def_col = 0;
    if (!lsp_definition_at(doc_buf, doc_len, line0, char0, &def_line, &def_col))
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    uint8_t uri_buf[512];
    int uri_len = lsp_extract_uri_from_params(body, body_len, uri_buf, (int)sizeof(uri_buf));
    if (uri_len < 0) uri_len = 0;
    uri_buf[uri_len] = '\0';
    /* LSP Location: {"uri":"...","range":{"start":{"line":L,"character":C},"end":{...}}}；行列 0-based。 */
    int line0_def = def_line > 0 ? def_line - 1 : 0;
    int col0_def = def_col > 0 ? def_col - 1 : 0;
    char result_buf[LSP_DEFINITION_RESULT_MAX];
    int r = snprintf(result_buf, sizeof(result_buf),
        "{\"uri\":\"%.*s\",\"range\":{\"start\":{\"line\":%d,\"character\":%d},\"end\":{\"line\":%d,\"character\":%d}}}",
        uri_len, (const char *)uri_buf, line0_def, col0_def, line0_def, col0_def + 1);
    if (r <= 0 || r >= (int)sizeof(result_buf)) return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    return lsp_build_response_with_result(id_val, (const uint8_t *)result_buf, r, out_buf, out_cap);
}

#define LSP_REFS_MAX 128
#define LSP_REFERENCES_RESULT_MAX 8192

/**
 * 构建 textDocument/references 的完整 JSON-RPC 响应正文。
 * 从 body 解析 position 与 uri，用 doc_buf 跑 lsp_references_at，result 为 Location[]。
 */
int lsp_build_references_response(int id_val, const uint8_t *body, int body_len,
                                  const uint8_t *doc_buf, int doc_len,
                                  uint8_t *out_buf, int out_cap) {
    if (!body || !out_buf || out_cap <= 0) return -1;
    int line0 = 0, char0 = 0;
    if (lsp_extract_position_from_params(body, body_len, &line0, &char0) != 0)
        return lsp_build_response_with_result(id_val, (const uint8_t *)"[]", 2, out_buf, out_cap);
    int ref_lines[LSP_REFS_MAX];
    int ref_cols[LSP_REFS_MAX];
    int n = lsp_references_at(doc_buf, doc_len, line0, char0, ref_lines, ref_cols, LSP_REFS_MAX);
    uint8_t uri_buf[512];
    int uri_len = lsp_extract_uri_from_params(body, body_len, uri_buf, (int)sizeof(uri_buf));
    if (uri_len < 0) uri_len = 0;
    uri_buf[uri_len] = '\0';
    char result_buf[LSP_REFERENCES_RESULT_MAX];
    int k = 0;
    k += snprintf(result_buf + k, sizeof(result_buf) - k, "[");
    for (int i = 0; i < n && k < (int)sizeof(result_buf) - 80; i++) {
        int l0 = ref_lines[i] > 0 ? ref_lines[i] - 1 : 0;
        int c0 = ref_cols[i] > 0 ? ref_cols[i] - 1 : 0;
        if (i > 0) result_buf[k++] = ',';
        k += snprintf(result_buf + k, sizeof(result_buf) - k,
            "{\"uri\":\"%.*s\",\"range\":{\"start\":{\"line\":%d,\"character\":%d},\"end\":{\"line\":%d,\"character\":%d}}}",
            uri_len, (const char *)uri_buf, l0, c0, l0, c0 + 1);
    }
    k += snprintf(result_buf + k, sizeof(result_buf) - k, "]");
    return lsp_build_response_with_result(id_val, (const uint8_t *)result_buf, k, out_buf, out_cap);
}

#define LSP_HOVER_VALUE_MAX 256
#define LSP_HOVER_RESULT_MAX 512

/**
 * 构建 textDocument/hover 的完整 JSON-RPC 响应正文。
 * 从 body 解析 position，用 doc_buf 跑 lsp_hover_at 取类型字符串，result 为 {"contents":{"kind":"markdown","value":"..."}} 或 null。
 */
int lsp_build_hover_response(int id_val, const uint8_t *body, int body_len,
                              const uint8_t *doc_buf, int doc_len,
                              uint8_t *out_buf, int out_cap) {
    if (!body || !out_buf || out_cap <= 0) return -1;
    int line0 = 0, char0 = 0;
    if (lsp_extract_position_from_params(body, body_len, &line0, &char0) != 0)
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    char type_buf[LSP_HOVER_VALUE_MAX];
    int type_len = lsp_hover_at(doc_buf, doc_len, line0, char0, type_buf, (int)sizeof(type_buf));
    if (type_len <= 0)
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    /* 对 value 做 JSON 转义（仅 " 与 \） */
    char esc[LSP_HOVER_VALUE_MAX * 2 + 16];
    int e = 0;
    for (int i = 0; type_buf[i] != '\0' && e < (int)sizeof(esc) - 4; i++) {
        if (type_buf[i] == '"' || type_buf[i] == '\\') esc[e++] = '\\';
        esc[e++] = type_buf[i];
    }
    esc[e] = '\0';
    char result_buf[LSP_HOVER_RESULT_MAX];
    int r = snprintf(result_buf, sizeof(result_buf),
        "{\"contents\":{\"kind\":\"markdown\",\"value\":\"%s\"}}", esc);
    if (r <= 0 || r >= (int)sizeof(result_buf))
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    return lsp_build_response_with_result(id_val, (const uint8_t *)result_buf, r, out_buf, out_cap);
}

/* ---------- textDocument/formatting ---------- */

/** 在 body[start..] 中解析 key 对应的布尔值；1=true，0=false，未找到或无效返回 -1。 */
static int lsp_parse_bool_after(const uint8_t *body, int len, int start, const char *key, int *out_val) {
    int k = lsp_find_key_after(body, len, start, key);
    if (k < 0 || !out_val) return -1;
    if (k + 4 <= len && body[k] == 't' && body[k+1] == 'r' && body[k+2] == 'u' && body[k+3] == 'e') {
        *out_val = 1;
        return 0;
    }
    if (k + 5 <= len && body[k] == 'f' && body[k+1] == 'a' && body[k+2] == 'l' && body[k+3] == 's' && body[k+4] == 'e') {
        *out_val = 0;
        return 0;
    }
    return -1;
}

/** 从 params.options 提取格式化选项（见下方默认值）；成功返回 0。 */
static int lsp_extract_formatting_options(const uint8_t *body, int len,
    int *out_tab_size, int *out_insert_spaces, int *out_max_line_length,
    int *out_insert_final_newline, int *out_trim_trailing_whitespace, int *out_trim_final_newlines) {
    if (!body || len <= 0 || !out_tab_size || !out_insert_spaces || !out_max_line_length) return -1;
    *out_tab_size = 2;
    *out_insert_spaces = 1;
    *out_max_line_length = 100;
    *out_insert_final_newline = 1;
    *out_trim_trailing_whitespace = 1;
    *out_trim_final_newlines = 1;
    int opt = lsp_find_key_after(body, len, 0, "\"options\":");
    if (opt < 0) return 0;
    int ts = lsp_find_key_after(body, len, opt, "\"tabSize\":");
    if (ts >= 0) {
        int val = 0;
        int end = lsp_parse_int(body, len, ts, &val);
        if (end > ts && val >= 1 && val <= 16) *out_tab_size = val;
    }
    lsp_parse_bool_after(body, len, opt, "\"insertSpaces\":", out_insert_spaces);
    int ml = lsp_find_key_after(body, len, opt, "\"maxLineLength\":");
    if (ml >= 0) {
        int val = 0;
        int end = lsp_parse_int(body, len, ml, &val);
        if (end > ml && val >= 20 && val <= 512) *out_max_line_length = val;
    }
    if (out_insert_final_newline) lsp_parse_bool_after(body, len, opt, "\"insertFinalNewline\":", out_insert_final_newline);
    if (out_trim_trailing_whitespace) lsp_parse_bool_after(body, len, opt, "\"trimTrailingWhitespace\":", out_trim_trailing_whitespace);
    if (out_trim_final_newlines) lsp_parse_bool_after(body, len, opt, "\"trimFinalNewlines\":", out_trim_final_newlines);
    return 0;
}

/**
 * 对文档做简单格式化：按行处理，根据 { } 跟踪缩进深度，每行输出规范缩进 + 去首尾空白的内容；
 * 若缩进+内容超过 max_line_length 则在空格处折行；受 trim_trailing_whitespace / trim_final_newlines / insert_final_newline 控制结尾。
 * 写入 out_buf，返回长度；越界返回 -1。
 */
static int lsp_format_document(const uint8_t *doc, int doc_len, int tab_size, int insert_spaces, int max_line_length,
                               int trim_trailing_whitespace, int insert_final_newline, int trim_final_newlines,
                               uint8_t *out_buf, int out_cap) {
    if (!doc || !out_buf || out_cap <= 0) return -1;
    int depth = 0;
    int out_len = 0;
    int line_start = 0;
    for (int i = 0; i <= doc_len && out_len < out_cap - 2; i++) {
        int is_eol = (i == doc_len || doc[i] == '\n');
        if (!is_eol) continue;
        /* 当前行 [line_start..i) */
        int line_len = i - line_start;
        /* 可选：去掉行尾空白 */
        if (trim_trailing_whitespace) {
            while (line_len > 0 && (doc[line_start + line_len - 1] == ' ' || doc[line_start + line_len - 1] == '\t' || doc[line_start + line_len - 1] == '\r'))
                line_len--;
        }
        int lead = 0;
        while (lead < line_len && (doc[line_start + lead] == ' ' || doc[line_start + lead] == '\t'))
            lead++;
        int content_start = line_start + lead;
        int content_len = line_len - lead;
        int line_depth = depth;
        if (content_len > 0 && doc[content_start] == '}')
            line_depth = (depth - 1) >= 0 ? depth - 1 : 0;
        int indent_chars = insert_spaces ? (line_depth * tab_size) : line_depth;
        int room = max_line_length - indent_chars;
        if (room < 1) room = 1;
        /* 输出行内容：若超过 max_line_length 则在空格处折行 */
        int pos = 0;
        for (;;) {
            /* 输出本段缩进 */
            if (insert_spaces) {
                for (int k = 0; k < line_depth * tab_size && out_len < out_cap - 1; k++)
                    out_buf[out_len++] = ' ';
            } else {
                for (int k = 0; k < line_depth && out_len < out_cap - 1; k++)
                    out_buf[out_len++] = '\t';
            }
            if (pos >= content_len) {
                if (out_len < out_cap - 1) out_buf[out_len++] = '\n';
                break;
            }
            if (pos + room >= content_len) {
                for (int j = pos; j < content_len && out_len < out_cap - 1; j++)
                    out_buf[out_len++] = doc[content_start + j];
                if (out_len < out_cap - 1) out_buf[out_len++] = '\n';
                break;
            }
            /* 在 [pos, pos+room] 内找最后一个空格作为折行点 */
            int end = pos + room;
            int break_at = end;
            for (int k = end - 1; k >= pos; k--) {
                if (doc[content_start + k] == ' ') {
                    break_at = k + 1;
                    break;
                }
            }
            if (break_at <= pos) break_at = end;
            for (int j = pos; j < break_at && out_len < out_cap - 1; j++)
                out_buf[out_len++] = doc[content_start + j];
            if (out_len < out_cap - 1) out_buf[out_len++] = '\n';
            pos = break_at;
            while (pos < content_len && doc[content_start + pos] == ' ') pos++;
        }
        /* 更新 depth：统计本行 { 与 } */
        for (int j = 0; j < line_len; j++) {
            uint8_t c = doc[line_start + j];
            if (c == '{') depth++;
            else if (c == '}') depth--;
        }
        if (depth < 0) depth = 0;
        line_start = i + 1;
    }
    /* 结尾处理：trimFinalNewlines 去掉多余尾随换行，insertFinalNewline 保证/去掉末尾换行 */
    if (trim_final_newlines) {
        while (out_len >= 2 && out_buf[out_len - 1] == '\n' && out_buf[out_len - 2] == '\n')
            out_len--;
    }
    if (insert_final_newline) {
        if (out_len == 0 || out_buf[out_len - 1] != '\n') {
            if (out_len < out_cap - 1) out_buf[out_len++] = '\n';
        }
    } else {
        while (out_len > 0 && out_buf[out_len - 1] == '\n')
            out_len--;
    }
    return out_len;
}

/** 统计文档行数（0-based 最后一行号）与最后一行的字符数。 */
static void lsp_doc_line_count(const uint8_t *doc, int len, int *out_last_line, int *out_last_line_char) {
    int lines = 0;
    int last_char = 0;
    for (int i = 0; i < len; i++) {
        if (doc[i] == '\n') {
            lines++;
            last_char = 0;
        } else
            last_char++;
    }
    *out_last_line = lines > 0 ? lines - 1 : 0;
    *out_last_line_char = last_char;
}

/** 格式化结果 JSON（单条 TextEdit）最大长度，避免栈上 result_buf 过大。 */
#define LSP_FORMATTING_RESULT_MAX (1024 * 1024)

/**
 * 构建 textDocument/formatting 的完整 JSON-RPC 响应正文。
 * result 为 TextEdit[]，单条编辑：整文档替换为格式化后的文本。
 */
int lsp_build_formatting_response(int id_val, const uint8_t *body, int body_len,
                                  const uint8_t *doc_buf, int doc_len,
                                  uint8_t *out_buf, int out_cap) {
    if (!body || !out_buf || out_cap <= 0 || !doc_buf) return -1;
    int tab_size = 2, insert_spaces = 1, max_line_length = 100;
    int insert_final_newline = 1, trim_trailing_whitespace = 1, trim_final_newlines = 1;
    lsp_extract_formatting_options(body, body_len, &tab_size, &insert_spaces, &max_line_length,
        &insert_final_newline, &trim_trailing_whitespace, &trim_final_newlines);
    uint8_t *fmt_buf = (uint8_t *)malloc((size_t)(doc_len + 8192));
    if (!fmt_buf) return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    int fmt_len = lsp_format_document(doc_buf, doc_len, tab_size, insert_spaces, max_line_length,
        trim_trailing_whitespace, insert_final_newline, trim_final_newlines, fmt_buf, doc_len + 8192);
    if (fmt_len < 0) {
        free(fmt_buf);
        return lsp_build_response_with_result(id_val, (const uint8_t *)"null", 4, out_buf, out_cap);
    }
    int last_line = 0, last_char = 0;
    lsp_doc_line_count(doc_buf, doc_len, &last_line, &last_char);
    /* 将 newText JSON 转义： \ " 换行等 */
    static uint8_t result_buf[LSP_FORMATTING_RESULT_MAX];
    int r = 0;
    r += snprintf((char *)result_buf + r, sizeof(result_buf) - r,
        "[{\"range\":{\"start\":{\"line\":0,\"character\":0},\"end\":{\"line\":%d,\"character\":%d}},\"newText\":\"",
        last_line, last_char);
    for (int i = 0; i < fmt_len && r < (int)sizeof(result_buf) - 8; i++) {
        uint8_t c = fmt_buf[i];
        if (c == '\\') { result_buf[r++] = '\\'; result_buf[r++] = '\\'; }
        else if (c == '"') { result_buf[r++] = '\\'; result_buf[r++] = '"'; }
        else if (c == '\n') { result_buf[r++] = '\\'; result_buf[r++] = 'n'; }
        else if (c == '\r') { result_buf[r++] = '\\'; result_buf[r++] = 'r'; }
        else if (c == '\t') { result_buf[r++] = '\\'; result_buf[r++] = 't'; }
        else result_buf[r++] = c;
    }
    if (r + 3 >= (int)sizeof(result_buf)) {
        free(fmt_buf);
        return lsp_build_response_with_result(id_val, (const uint8_t *)"[]", 2, out_buf, out_cap);
    }
    result_buf[r++] = '"';
    result_buf[r++] = '}';
    result_buf[r++] = ']';
    free(fmt_buf);
    if (r <= 0 || r >= (int)sizeof(result_buf))
        return lsp_build_response_with_result(id_val, (const uint8_t *)"[]", 2, out_buf, out_cap);
    return lsp_build_response_with_result(id_val, result_buf, r, out_buf, out_cap);
}
