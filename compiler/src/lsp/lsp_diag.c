/**
 * lsp_diag.c — LSP 诊断收集器实现
 *
 * 维护固定大小诊断列表；parser 在 fail() 时若 lsp_diag_enabled 则 lsp_diag_add。
 * lsp_build_diagnostics_response 对源码跑 C parser，收集错误，生成完整 JSON-RPC 响应正文。
 * 高性能：仅在此入口跑一次解析，不依赖 .su pipeline，无 arena 分配。
 */

#include "lsp/lsp_diag.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "typeck/typeck.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

/* 前向声明：行索引、引用索引与定义/引用/悬停。 */
static void build_line_index(const struct ASTModule *mod);
static void build_refs_index(const struct ASTModule *mod);
static struct ASTFunc *get_function_at_line(const struct ASTModule *mod, int line_1);
static int find_def_in_expr(const struct ASTExpr *e, int line_1, int col_1, int *out_line, int *out_col);
static int find_def_in_block(const struct ASTBlock *b, int line_1, int col_1, int *out_line, int *out_col);
static int find_def_in_module(const struct ASTModule *mod, int line_1, int col_1, int *out_line, int *out_col);
/* References：按位置确定目标函数，并收集所有引用位置。 */
static struct ASTFunc *find_target_function_at(const struct ASTModule *mod, int line_1, int col_1);
static int collect_refs_to_func(const struct ASTModule *mod, const struct ASTFunc *func, int *out_lines, int *out_cols, int max_refs);
/* Hover：按位置找最内层表达式，并格式化类型字符串。 */
static struct ASTExpr *get_innermost_expr_at(struct ASTExpr *e, int line_1, int col_1);
static struct ASTExpr *get_expr_at_in_block(const struct ASTBlock *b, int line_1, int col_1);
static struct ASTExpr *get_expr_at_in_module(const struct ASTModule *mod, int line_1, int col_1);
static int type_to_string(const struct ASTType *ty, char *buf, int cap);
static int lsp_diag_to_json(char *out, int out_cap);

#define LSP_DIAG_MAX  64
#define LSP_MSG_MAX   240

typedef struct {
    int line;
    int col;
    int severity;
    char msg[LSP_MSG_MAX + 1];
} LspDiagEntry;

static LspDiagEntry s_diag[LSP_DIAG_MAX];
static int s_diag_count;

/* 诊断/模块缓存与行索引（lsp_diag_invalidate_cache 需在文件前部可见）。 */
#define LSP_CACHE_DIAG_JSON_INIT 8192
#define LSP_CACHE_DIAG_JSON_MAX_CAP  (2 * 1024 * 1024)  /* 单次缓存上限 2MB */
static int s_last_source_len;
static unsigned s_last_source_hash;
static char *s_last_diag_json = NULL;
static int s_last_diag_json_cap = 0;
static int s_last_diag_len = 0;
static ASTModule *s_cached_mod = NULL;
static int s_cached_source_len = -1;
static unsigned s_cached_source_hash = 0;
static int s_typeck_full = 0;  /* 1=缓存模块已全量 typeck，0=仅懒 typeck 过单函数 */
#define LSP_LINE_INDEX_MAX 1024
#define LSP_REFS_PER_FUNC_MAX 256
static struct {
    int start_line;
    int end_line;
    struct ASTFunc *func;
} s_line_index[LSP_LINE_INDEX_MAX];
static int s_line_index_n = 0;
/* References 索引：s_refs_lines[i][0..s_refs_count[i]-1] 为第 i 个函数被引用的 (line,col)。 */
static int s_refs_lines[LSP_LINE_INDEX_MAX][LSP_REFS_PER_FUNC_MAX];
static int s_refs_cols[LSP_LINE_INDEX_MAX][LSP_REFS_PER_FUNC_MAX];
static int s_refs_count[LSP_LINE_INDEX_MAX];

int lsp_diag_enabled = 0;

void lsp_diag_clear(void) {
    s_diag_count = 0;
}

/** 文档变更时调用，使模块与诊断缓存失效；避免旧 AST 指向已释放的文档缓冲（与 lsp_io 配合）。 */
void lsp_diag_invalidate_cache(void) {
    if (s_cached_mod) {
        ast_module_free(s_cached_mod);
        s_cached_mod = NULL;
    }
    s_cached_source_len = -1;
    s_cached_source_hash = 0;
    if (s_last_diag_json) {
        free(s_last_diag_json);
        s_last_diag_json = NULL;
        s_last_diag_json_cap = 0;
    }
    s_last_diag_len = 0;
    s_line_index_n = 0;
    s_typeck_full = 0;
}

void lsp_diag_add(int line, int col, int severity, const char *msg) {
    if (s_diag_count >= LSP_DIAG_MAX) return;
    LspDiagEntry *e = &s_diag[s_diag_count++];
    e->line = line;
    e->col = col;
    e->severity = (severity == 2) ? 2 : 1;
    if (msg) {
        size_t n = 0;
        while (n < LSP_MSG_MAX && msg[n] != '\0') {
            e->msg[n] = msg[n];
            n++;
        }
        e->msg[n] = '\0';
    } else {
        e->msg[0] = '\0';
    }
}

void lsp_diag_report_typeck(int line, int col, const char *fmt, ...) {
    char buf[LSP_MSG_MAX + 1];
    va_list ap;
    va_start(ap, fmt);
    (void)vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (lsp_diag_enabled) {
        lsp_diag_add(line, col, 1, buf);
    } else {
        fprintf(stderr, "typeck error: %s at %d:%d\n", buf, line, col);
    }
}

/** 将 msg 按 JSON 字符串转义写入 out，返回写入长度；out_cap 为 out 的容量。 */
static int json_escape_str(const char *msg, char *out, int out_cap) {
    int k = 0;
    if (!msg || !out || out_cap <= 0) return 0;
    for (; *msg != '\0' && k < out_cap - 1; msg++) {
        if (*msg == '"' || *msg == '\\') {
            if (k + 2 > out_cap - 1) break;
            out[k++] = '\\';
            out[k++] = *msg;
        } else if (*msg == '\n') {
            if (k + 2 > out_cap - 1) break;
            out[k++] = '\\';
            out[k++] = 'n';
        } else if (*msg == '\r') {
            if (k + 2 > out_cap - 1) break;
            out[k++] = '\\';
            out[k++] = 'r';
        } else if (*msg == '\t') {
            if (k + 2 > out_cap - 1) break;
            out[k++] = '\\';
            out[k++] = 't';
        } else {
            out[k++] = *msg;
        }
    }
    out[k] = '\0';
    return k;
}

/** 快速 32 位哈希：64 位状态 + 8 字节块 mix，折叠为 32 位；大文档缓存校验比 djb2 更快。 */
static unsigned lsp_hash_source(const uint8_t *src, int len) {
    uint64_t h = (uint64_t)(unsigned)len;
    int i = 0;
    for (; i + 8 <= len; i += 8) {
        uint64_t x;
        memcpy(&x, src + i, 8);
        h = (h * 0x9e3779b97f4a7c15ULL) + x;
    }
    for (; i < len; i++)
        h = (h * 0x9e3779b97f4a7c15ULL) + (uint64_t)(unsigned)src[i];
    return (unsigned)(h ^ (h >> 32));
}

/**
 * 返回当前文档对应的已解析+类型检查模块；文档未变则直接返回缓存，否则重新 parse+typeck 并更新缓存与诊断 JSON。
 * cursor_line_1 < 0 表示需要全量 typeck（diagnostics/references）；>= 0 时仅 typeck 该行所在函数（definition/hover 懒 typeck）。
 * 调用方不得 free 返回值；仅在同一文档上多次请求时复用，避免重复解析。
 */
static ASTModule *lsp_ensure_module(const uint8_t *source, int source_len, int cursor_line_1) {
    if (!source || source_len < 0) return NULL;
    /* 先比长度，不等则必未命中，可避免哈希计算（大文档时省时）。 */
    if (source_len == s_cached_source_len) {
        unsigned h = lsp_hash_source(source, source_len);
        if (h == s_cached_source_hash && s_cached_mod != NULL) {
            if (cursor_line_1 < 0 && !s_typeck_full) {
                (void)typeck_module(s_cached_mod, NULL, 0, NULL, 0);
                s_typeck_full = 1;
            }
            return s_cached_mod;
        }
    }
    /* 缓存未命中：释放旧模块与诊断缓存，重新解析。 */
    if (s_cached_mod) {
        ast_module_free(s_cached_mod);
        s_cached_mod = NULL;
    }
    if (s_last_diag_json) {
        free(s_last_diag_json);
        s_last_diag_json = NULL;
        s_last_diag_json_cap = 0;
    }
    s_last_diag_len = 0;
    s_cached_source_len = -1;
    s_cached_source_hash = 0;
    /* 零拷贝解析：source 为当前文档缓冲时（至少 source_len+1 字节可写），就地临时 NUL 后交给 lexer，省去整份 memcpy。source_len==0 时不能写 source[0]，走小缓冲。 */
    char *parse_src = NULL;
    char saved = 0;
    int in_place = (source_len > 0 && source_len < (1 << 28));
    if (in_place) {
        parse_src = (char *)(uintptr_t)source;
        saved = parse_src[source_len];
        parse_src[source_len] = '\0';
    } else {
        size_t alloc_len = (source_len > 0) ? (size_t)source_len + 1 : 1;
        parse_src = (char *)malloc(alloc_len);
        if (!parse_src) return NULL;
        if (source_len > 0) {
            memcpy(parse_src, source, (size_t)source_len);
            parse_src[source_len] = '\0';
        } else
            parse_src[0] = '\0';
    }
    Lexer *lex = lexer_new(parse_src);
    if (!lex) {
        if (in_place)
            parse_src[source_len] = saved;
        else if (parse_src)
            free(parse_src);
        return NULL;
    }
    lsp_diag_clear();
    lsp_diag_enabled = 1;
    ASTModule *mod = NULL;
    (void)parse(lex, &mod);
    lsp_diag_enabled = 0;
    lexer_free(lex);
    /* 解析结束后再恢复末尾字节（零拷贝）或释放拷贝缓冲，避免解析期间缓冲区被改/释放。 */
    if (in_place)
        parse_src[source_len] = saved;
    else if (parse_src)
        free(parse_src);
    s_last_source_len = source_len;
    s_last_source_hash = lsp_hash_source(source, source_len);
    /* 仅当解析失败时在此处写诊断缓存；成功则等 typeck 后只写一次。 */
    if (!mod) {
        int cap = LSP_CACHE_DIAG_JSON_INIT;
        char *tmp = (char *)malloc((size_t)cap);
        int diag_len = 0;
        if (tmp) {
            for (;;) {
                diag_len = lsp_diag_to_json(tmp, cap);
                if (diag_len <= 0) diag_len = 1;
                if (tmp[0] != '[') { tmp[0] = '['; tmp[1] = ']'; tmp[2] = '\0'; diag_len = 2; }
                if (diag_len < cap || (size_t)cap >= (size_t)LSP_CACHE_DIAG_JSON_MAX_CAP) break;
                cap = (int)((size_t)cap * 2);
                if (cap > LSP_CACHE_DIAG_JSON_MAX_CAP) cap = LSP_CACHE_DIAG_JSON_MAX_CAP;
                char *t2 = (char *)realloc(tmp, (size_t)cap);
                if (!t2) break;
                tmp = t2;
            }
        }
        if (tmp && diag_len > 0) {
            size_t need = (size_t)diag_len + 1;
            if (need > (size_t)s_last_diag_json_cap) {
                char *p = (char *)realloc(s_last_diag_json, need);
                if (p) { s_last_diag_json = p; s_last_diag_json_cap = (int)need; }
            }
            if (s_last_diag_json)
                memcpy(s_last_diag_json, tmp, need);
            s_last_diag_len = diag_len;
            free(tmp);
        } else if (tmp) free(tmp);
        return NULL;
    }
    build_line_index(mod);
    build_refs_index(mod);
    if (cursor_line_1 >= 0) {
        struct ASTFunc *at_line = get_function_at_line(mod, cursor_line_1);
        int only_func_index = -1;
        if (at_line && mod->funcs) {
            for (int i = 0; i < mod->num_funcs; i++)
                if (mod->funcs[i] == at_line) { only_func_index = i; break; }
        }
        if (only_func_index >= 0)
            (void)typeck_one_function(mod, NULL, 0, NULL, 0, only_func_index);
        else
            (void)typeck_module(mod, NULL, 0, NULL, 0);
        s_typeck_full = (only_func_index < 0) ? 1 : 0;
    } else {
        (void)typeck_module(mod, NULL, 0, NULL, 0);
        s_typeck_full = 1;
    }
    s_cached_mod = mod;
    s_cached_source_len = source_len;
    s_cached_source_hash = s_last_source_hash;
    /* 解析成功后再写一次诊断 JSON（typeck 可能新增错误）；同样动态扩容。 */
    {
        int cap = LSP_CACHE_DIAG_JSON_INIT;
        char *tmp = (char *)malloc((size_t)cap);
        int diag_len = 0;
        if (tmp) {
            for (;;) {
                diag_len = lsp_diag_to_json(tmp, cap);
                if (diag_len <= 0) diag_len = 1;
                if (tmp[0] != '[') {
                    tmp[0] = '['; tmp[1] = ']'; tmp[2] = '\0';
                    diag_len = 2;
                }
                if (diag_len < cap || (size_t)cap >= (size_t)LSP_CACHE_DIAG_JSON_MAX_CAP) break;
                cap = (int)((size_t)cap * 2);
                if (cap > LSP_CACHE_DIAG_JSON_MAX_CAP) cap = LSP_CACHE_DIAG_JSON_MAX_CAP;
                char *t2 = (char *)realloc(tmp, (size_t)cap);
                if (!t2) break;
                tmp = t2;
            }
        }
        if (tmp && diag_len > 0) {
            size_t need = (size_t)diag_len + 1;
            if (need > (size_t)s_last_diag_json_cap) {
                char *p = (char *)realloc(s_last_diag_json, need);
                if (p) { s_last_diag_json = p; s_last_diag_json_cap = (int)need; }
            }
            if (s_last_diag_json)
                memcpy(s_last_diag_json, tmp, need);
            s_last_diag_len = diag_len;
            free(tmp);
        } else if (tmp) free(tmp);
    }
    return mod;
}

/** 判断 (line_1, col_1) 是否与表达式起点一致（1-based）。 */
static int expr_at(const struct ASTExpr *e, int line_1, int col_1) {
    return e && e->line == line_1 && e->col == col_1;
}

/* ---------- 行/区间索引：按行快速定位所在函数，减少 definition/references/hover 的全 AST 遍历 ---------- */

/** 求表达式中出现的最大行号（递归）。 */
static int expr_max_line(const struct ASTExpr *e) {
    if (!e) return 0;
    int m = e->line;
    switch (e->kind) {
        case AST_EXPR_CALL:
            if (e->value.call.callee) { int t = expr_max_line(e->value.call.callee); if (t > m) m = t; }
            for (int i = 0; i < e->value.call.num_args; i++)
                if (e->value.call.args[i]) { int t = expr_max_line(e->value.call.args[i]); if (t > m) m = t; }
            break;
        case AST_EXPR_METHOD_CALL:
            if (e->value.method_call.base) { int t = expr_max_line(e->value.method_call.base); if (t > m) m = t; }
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (e->value.method_call.args[i]) { int t = expr_max_line(e->value.method_call.args[i]); if (t > m) m = t; }
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
            if (e->value.binop.left) { int t = expr_max_line(e->value.binop.left); if (t > m) m = t; }
            if (e->value.binop.right) { int t = expr_max_line(e->value.binop.right); if (t > m) m = t; }
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            if (e->value.unary.operand) { int t = expr_max_line(e->value.unary.operand); if (t > m) m = t; }
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            if (e->value.if_expr.cond) { int t = expr_max_line(e->value.if_expr.cond); if (t > m) m = t; }
            if (e->value.if_expr.then_expr) { int t = expr_max_line(e->value.if_expr.then_expr); if (t > m) m = t; }
            if (e->value.if_expr.else_expr) { int t = expr_max_line(e->value.if_expr.else_expr); if (t > m) m = t; }
            break;
        case AST_EXPR_BLOCK:
            /* 块内行号由 block_max_line 覆盖，此处仅取本节点 */
            break;
        case AST_EXPR_MATCH:
            if (e->value.match_expr.matched_expr) { int t = expr_max_line(e->value.match_expr.matched_expr); if (t > m) m = t; }
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (e->value.match_expr.arms[i].result) { int t = expr_max_line(e->value.match_expr.arms[i].result); if (t > m) m = t; }
            break;
        case AST_EXPR_FIELD_ACCESS:
            if (e->value.field_access.base) { int t = expr_max_line(e->value.field_access.base); if (t > m) m = t; }
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (e->value.struct_lit.inits[i]) { int t = expr_max_line(e->value.struct_lit.inits[i]); if (t > m) m = t; }
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (e->value.array_lit.elems[i]) { int t = expr_max_line(e->value.array_lit.elems[i]); if (t > m) m = t; }
            break;
        case AST_EXPR_INDEX:
            if (e->value.index.base) { int t = expr_max_line(e->value.index.base); if (t > m) m = t; }
            if (e->value.index.index_expr) { int t = expr_max_line(e->value.index.index_expr); if (t > m) m = t; }
            break;
        case AST_EXPR_AS:
            if (e->value.as_type.operand) { int t = expr_max_line(e->value.as_type.operand); if (t > m) m = t; }
            break;
        default:
            break;
    }
    return m;
}

/** 求块内出现的最大行号。 */
static int block_max_line(const struct ASTBlock *b) {
    if (!b) return 0;
    int m = 0;
    int i;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) { int t = expr_max_line(b->const_decls[i].init); if (t > m) m = t; }
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) { int t = expr_max_line(b->let_decls[i].init); if (t > m) m = t; }
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond) { int t = expr_max_line(b->loops[i].cond); if (t > m) m = t; }
        if (b->loops[i].body) { int t = block_max_line(b->loops[i].body); if (t > m) m = t; }
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init) { int t = expr_max_line(fl->init); if (t > m) m = t; }
        if (fl->cond) { int t = expr_max_line(fl->cond); if (t > m) m = t; }
        if (fl->step) { int t = expr_max_line(fl->step); if (t > m) m = t; }
        if (fl->body) { int t = block_max_line(fl->body); if (t > m) m = t; }
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            { int t = expr_max_line(b->labeled_stmts[i].u.return_expr); if (t > m) m = t; }
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i]) { int t = expr_max_line(b->expr_stmts[i]); if (t > m) m = t; }
    if (b->final_expr) { int t = expr_max_line(b->final_expr); if (t > m) m = t; }
    return m;
}

/** 根据模块构建行→函数索引（每个函数的 [start_line, end_line]），供 get_function_at_line 使用。 */
static void build_line_index(const struct ASTModule *mod) {
    s_line_index_n = 0;
    if (!mod || !mod->funcs) return;
    for (int i = 0; i < mod->num_funcs && s_line_index_n < LSP_LINE_INDEX_MAX; i++) {
        struct ASTFunc *f = mod->funcs[i];
        if (!f) continue;
        int start = f->line > 0 ? f->line : 1;
        int end = start;
        if (f->body) {
            int be = block_max_line(f->body);
            if (be > end) end = be;
        }
        s_line_index[s_line_index_n].start_line = start;
        s_line_index[s_line_index_n].end_line = end;
        s_line_index[s_line_index_n].func = f;
        s_line_index_n++;
    }
}

/** 返回 func 在 s_line_index 中的下标，未找到返回 -1。 */
static int line_index_of_func(const struct ASTFunc *func) {
    for (int i = 0; i < s_line_index_n; i++)
        if (s_line_index[i].func == func) return i;
    return -1;
}

/** 向 func 对应的引用表追加 (line, col)；用于构建引用索引。 */
static void add_ref_for_func(const struct ASTFunc *func, int line, int col) {
    int j = line_index_of_func(func);
    if (j < 0 || s_refs_count[j] >= LSP_REFS_PER_FUNC_MAX) return;
    for (int i = 0; i < s_refs_count[j]; i++)
        if (s_refs_lines[j][i] == line && s_refs_cols[j][i] == col) return;
    s_refs_lines[j][s_refs_count[j]] = line;
    s_refs_cols[j][s_refs_count[j]] = col;
    s_refs_count[j]++;
}

/** 遍历表达式，将 resolved_callee_func / resolved_impl_func 的调用点加入引用索引。 */
static void collect_refs_index_in_expr(const struct ASTExpr *e) {
    if (!e) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func) {
        const struct ASTExpr *callee = e->value.call.callee;
        if (callee) add_ref_for_func(e->value.call.resolved_callee_func, callee->line, callee->col);
    } else if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func)
        add_ref_for_func(e->value.method_call.resolved_impl_func, e->line, e->col);
    switch (e->kind) {
        case AST_EXPR_CALL:
            if (e->value.call.callee) collect_refs_index_in_expr(e->value.call.callee);
            for (int i = 0; i < e->value.call.num_args; i++)
                if (e->value.call.args[i]) collect_refs_index_in_expr(e->value.call.args[i]);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_refs_index_in_expr(e->value.method_call.base);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (e->value.method_call.args[i]) collect_refs_index_in_expr(e->value.method_call.args[i]);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_refs_index_in_expr(e->value.binop.left);
            collect_refs_index_in_expr(e->value.binop.right);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            collect_refs_index_in_expr(e->value.unary.operand);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_refs_index_in_expr(e->value.if_expr.cond);
            collect_refs_index_in_expr(e->value.if_expr.then_expr);
            collect_refs_index_in_expr(e->value.if_expr.else_expr);
            break;
        case AST_EXPR_ASSIGN:
            collect_refs_index_in_expr(e->value.binop.left);
            collect_refs_index_in_expr(e->value.binop.right);
            break;
        case AST_EXPR_MATCH:
            collect_refs_index_in_expr(e->value.match_expr.matched_expr);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_refs_index_in_expr(e->value.match_expr.arms[i].result);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_refs_index_in_expr(e->value.field_access.base);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_refs_index_in_expr(e->value.struct_lit.inits[i]);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_refs_index_in_expr(e->value.array_lit.elems[i]);
            break;
        case AST_EXPR_INDEX:
            collect_refs_index_in_expr(e->value.index.base);
            collect_refs_index_in_expr(e->value.index.index_expr);
            break;
        case AST_EXPR_AS:
            collect_refs_index_in_expr(e->value.as_type.operand);
            break;
        default:
            break;
    }
}

static void collect_refs_index_in_block(const struct ASTBlock *b) {
    if (!b) return;
    int i;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_refs_index_in_expr(b->const_decls[i].init);
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_refs_index_in_expr(b->let_decls[i].init);
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond) collect_refs_index_in_expr(b->loops[i].cond);
        if (b->loops[i].body) collect_refs_index_in_block(b->loops[i].body);
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init) collect_refs_index_in_expr(fl->init);
        if (fl->cond) collect_refs_index_in_expr(fl->cond);
        if (fl->step) collect_refs_index_in_expr(fl->step);
        if (fl->body) collect_refs_index_in_block(fl->body);
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_refs_index_in_expr(b->labeled_stmts[i].u.return_expr);
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i]) collect_refs_index_in_expr(b->expr_stmts[i]);
    if (b->final_expr) collect_refs_index_in_expr(b->final_expr);
}

/** 在 build_line_index 之后调用：一次遍历全模块，为每个函数填好引用索引。 */
static void build_refs_index(const struct ASTModule *mod) {
    for (int i = 0; i < s_line_index_n; i++) {
        s_refs_count[i] = 0;
        add_ref_for_func(s_line_index[i].func, s_line_index[i].func->line, s_line_index[i].func->col);
    }
    if (!mod || !mod->funcs) return;
    for (int i = 0; i < mod->num_funcs; i++)
        if (mod->funcs[i]->body) collect_refs_index_in_block(mod->funcs[i]->body);
}

/** 返回包含行 line_1（1-based）的函数；若多函数包含该行则取区间最小的（最内层）。无则返回 NULL。 */
static struct ASTFunc *get_function_at_line(const struct ASTModule *mod, int line_1) {
    (void)mod;
    struct ASTFunc *best = NULL;
    int best_span = 0;
    for (int i = 0; i < s_line_index_n; i++) {
        if (line_1 >= s_line_index[i].start_line && line_1 <= s_line_index[i].end_line) {
            int span = s_line_index[i].end_line - s_line_index[i].start_line;
            if (!best || span < best_span) {
                best = s_line_index[i].func;
                best_span = span;
            }
        }
    }
    return best;
}

/**
 * 在表达式 e 中查找位置 (line_1, col_1) 对应的“定义”：
 * 若该位置在函数调用上（call 或 callee），且已解析到 resolved_callee_func / resolved_impl_func，则写出定义行列并返回 1。
 * 先递归子表达式，以便命中“调用内的标识符”；否则再检查本节点是否为 CALL/METHOD_CALL 且位置匹配。
 */
static int find_def_in_expr(const struct ASTExpr *e, int line_1, int col_1, int *out_line, int *out_col) {
    if (!e || !out_line || !out_col) return 0;
    switch (e->kind) {
        case AST_EXPR_CALL: {
            const struct ASTExpr *callee = e->value.call.callee;
            if (callee && find_def_in_expr(callee, line_1, col_1, out_line, out_col)) return 1;
            for (int i = 0; i < e->value.call.num_args; i++)
                if (e->value.call.args[i] && find_def_in_expr(e->value.call.args[i], line_1, col_1, out_line, out_col)) return 1;
            if ((expr_at(e, line_1, col_1) || (callee && expr_at(callee, line_1, col_1))) && e->value.call.resolved_callee_func) {
                struct ASTFunc *f = e->value.call.resolved_callee_func;
                *out_line = f->line;
                *out_col = f->col;
                return 1;
            }
            return 0;
        }
        case AST_EXPR_METHOD_CALL: {
            if (e->value.method_call.base && find_def_in_expr(e->value.method_call.base, line_1, col_1, out_line, out_col)) return 1;
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (e->value.method_call.args[i] && find_def_in_expr(e->value.method_call.args[i], line_1, col_1, out_line, out_col)) return 1;
            if (expr_at(e, line_1, col_1) && e->value.method_call.resolved_impl_func) {
                struct ASTFunc *f = e->value.method_call.resolved_impl_func;
                *out_line = f->line;
                *out_col = f->col;
                return 1;
            }
            return 0;
        }
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            if (e->value.binop.left && find_def_in_expr(e->value.binop.left, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.binop.right && find_def_in_expr(e->value.binop.right, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_NEG:
        case AST_EXPR_BITNOT:
        case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF:
        case AST_EXPR_DEREF:
            return e->value.unary.operand ? find_def_in_expr(e->value.unary.operand, line_1, col_1, out_line, out_col) : 0;
        case AST_EXPR_IF:
            if (e->value.if_expr.cond && find_def_in_expr(e->value.if_expr.cond, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.if_expr.then_expr && find_def_in_expr(e->value.if_expr.then_expr, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.if_expr.else_expr && find_def_in_expr(e->value.if_expr.else_expr, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_BLOCK:
            return e->value.block ? find_def_in_block(e->value.block, line_1, col_1, out_line, out_col) : 0;
        case AST_EXPR_TERNARY:
            if (e->value.if_expr.cond && find_def_in_expr(e->value.if_expr.cond, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.if_expr.then_expr && find_def_in_expr(e->value.if_expr.then_expr, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.if_expr.else_expr && find_def_in_expr(e->value.if_expr.else_expr, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_ASSIGN:
            if (e->value.binop.left && find_def_in_expr(e->value.binop.left, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.binop.right && find_def_in_expr(e->value.binop.right, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_RETURN:
            return e->value.unary.operand ? find_def_in_expr(e->value.unary.operand, line_1, col_1, out_line, out_col) : 0;
        case AST_EXPR_PANIC:
            return e->value.unary.operand ? find_def_in_expr(e->value.unary.operand, line_1, col_1, out_line, out_col) : 0;
        case AST_EXPR_MATCH:
            if (e->value.match_expr.matched_expr && find_def_in_expr(e->value.match_expr.matched_expr, line_1, col_1, out_line, out_col)) return 1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (e->value.match_expr.arms[i].result && find_def_in_expr(e->value.match_expr.arms[i].result, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_FIELD_ACCESS:
            return e->value.field_access.base ? find_def_in_expr(e->value.field_access.base, line_1, col_1, out_line, out_col) : 0;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (e->value.struct_lit.inits[i] && find_def_in_expr(e->value.struct_lit.inits[i], line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (e->value.array_lit.elems[i] && find_def_in_expr(e->value.array_lit.elems[i], line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_INDEX:
            if (e->value.index.base && find_def_in_expr(e->value.index.base, line_1, col_1, out_line, out_col)) return 1;
            if (e->value.index.index_expr && find_def_in_expr(e->value.index.index_expr, line_1, col_1, out_line, out_col)) return 1;
            return 0;
        case AST_EXPR_AS:
            return e->value.as_type.operand ? find_def_in_expr(e->value.as_type.operand, line_1, col_1, out_line, out_col) : 0;
        default:
            return 0;
    }
}

/** 在块 b 内所有表达式（const/let init、循环、expr_stmts、final_expr）中查找定义。 */
static int find_def_in_block(const struct ASTBlock *b, int line_1, int col_1, int *out_line, int *out_col) {
    if (!b || !out_line || !out_col) return 0;
    int i;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init && find_def_in_expr(b->const_decls[i].init, line_1, col_1, out_line, out_col)) return 1;
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && find_def_in_expr(b->let_decls[i].init, line_1, col_1, out_line, out_col)) return 1;
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond && find_def_in_expr(b->loops[i].cond, line_1, col_1, out_line, out_col)) return 1;
        if (b->loops[i].body && find_def_in_block(b->loops[i].body, line_1, col_1, out_line, out_col)) return 1;
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init && find_def_in_expr(fl->init, line_1, col_1, out_line, out_col)) return 1;
        if (fl->cond && find_def_in_expr(fl->cond, line_1, col_1, out_line, out_col)) return 1;
        if (fl->step && find_def_in_expr(fl->step, line_1, col_1, out_line, out_col)) return 1;
        if (fl->body && find_def_in_block(fl->body, line_1, col_1, out_line, out_col)) return 1;
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr &&
            find_def_in_expr(b->labeled_stmts[i].u.return_expr, line_1, col_1, out_line, out_col)) return 1;
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i] && find_def_in_expr(b->expr_stmts[i], line_1, col_1, out_line, out_col)) return 1;
    if (b->final_expr && find_def_in_expr(b->final_expr, line_1, col_1, out_line, out_col)) return 1;
    return 0;
}

/** 在模块中查找位置对应的定义；先按行索引定位到包含该行的函数，只遍历该函数 body，减少大文件下的全 AST 遍历。 */
static int find_def_in_module(const struct ASTModule *mod, int line_1, int col_1, int *out_line, int *out_col) {
    if (!mod || !out_line || !out_col) return 0;
    /* 若光标恰在某个函数名上，定义即该函数。 */
    for (int i = 0; i < mod->num_funcs; i++) {
        struct ASTFunc *f = mod->funcs[i];
        if (f->line == line_1 && f->col == col_1) {
            *out_line = f->line;
            *out_col = f->col;
            return 1;
        }
    }
    struct ASTFunc *containing = get_function_at_line(mod, line_1);
    if (containing && containing->body)
        return find_def_in_block(containing->body, line_1, col_1, out_line, out_col);
    return 0;
}

/* ---------- References：目标函数 + 收集引用 ---------- */

/** 在表达式 e 中查找位置 (line_1, col_1) 对应的“被调用函数”（CALL 的 resolved_callee_func 或 METHOD_CALL 的 resolved_impl_func）。 */
static struct ASTFunc *find_callee_func_in_expr(const struct ASTExpr *e, int line_1, int col_1) {
    if (!e) return NULL;
    if (e->kind == AST_EXPR_CALL) {
        const struct ASTExpr *callee = e->value.call.callee;
        if ((expr_at(e, line_1, col_1) || (callee && expr_at(callee, line_1, col_1))) && e->value.call.resolved_callee_func)
            return e->value.call.resolved_callee_func;
        if (callee) {
            struct ASTFunc *f = find_callee_func_in_expr(callee, line_1, col_1);
            if (f) return f;
        }
        for (int i = 0; i < e->value.call.num_args; i++)
            if (e->value.call.args[i]) {
                struct ASTFunc *f = find_callee_func_in_expr(e->value.call.args[i], line_1, col_1);
                if (f) return f;
            }
        return NULL;
    }
    if (e->kind == AST_EXPR_METHOD_CALL) {
        if (expr_at(e, line_1, col_1) && e->value.method_call.resolved_impl_func)
            return e->value.method_call.resolved_impl_func;
        if (e->value.method_call.base) {
            struct ASTFunc *f = find_callee_func_in_expr(e->value.method_call.base, line_1, col_1);
            if (f) return f;
        }
        for (int i = 0; i < e->value.method_call.num_args; i++)
            if (e->value.method_call.args[i]) {
                struct ASTFunc *f = find_callee_func_in_expr(e->value.method_call.args[i], line_1, col_1);
                if (f) return f;
            }
        return NULL;
    }
    /* 其余种类仅递归子节点 */
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            if (e->value.binop.left) { struct ASTFunc *f = find_callee_func_in_expr(e->value.binop.left, line_1, col_1); if (f) return f; }
            if (e->value.binop.right) { struct ASTFunc *f = find_callee_func_in_expr(e->value.binop.right, line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            if (e->value.unary.operand) return find_callee_func_in_expr(e->value.unary.operand, line_1, col_1);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            if (e->value.if_expr.cond) { struct ASTFunc *f = find_callee_func_in_expr(e->value.if_expr.cond, line_1, col_1); if (f) return f; }
            if (e->value.if_expr.then_expr) { struct ASTFunc *f = find_callee_func_in_expr(e->value.if_expr.then_expr, line_1, col_1); if (f) return f; }
            if (e->value.if_expr.else_expr) { struct ASTFunc *f = find_callee_func_in_expr(e->value.if_expr.else_expr, line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_BLOCK:
            break; /* 块内由 find_callee_func_in_block 遍历 */
        case AST_EXPR_ASSIGN:
            if (e->value.binop.left) { struct ASTFunc *f = find_callee_func_in_expr(e->value.binop.left, line_1, col_1); if (f) return f; }
            if (e->value.binop.right) { struct ASTFunc *f = find_callee_func_in_expr(e->value.binop.right, line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_MATCH:
            if (e->value.match_expr.matched_expr) { struct ASTFunc *f = find_callee_func_in_expr(e->value.match_expr.matched_expr, line_1, col_1); if (f) return f; }
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (e->value.match_expr.arms[i].result) { struct ASTFunc *f = find_callee_func_in_expr(e->value.match_expr.arms[i].result, line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_FIELD_ACCESS:
            if (e->value.field_access.base) return find_callee_func_in_expr(e->value.field_access.base, line_1, col_1);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (e->value.struct_lit.inits[i]) { struct ASTFunc *f = find_callee_func_in_expr(e->value.struct_lit.inits[i], line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (e->value.array_lit.elems[i]) { struct ASTFunc *f = find_callee_func_in_expr(e->value.array_lit.elems[i], line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_INDEX:
            if (e->value.index.base) { struct ASTFunc *f = find_callee_func_in_expr(e->value.index.base, line_1, col_1); if (f) return f; }
            if (e->value.index.index_expr) { struct ASTFunc *f = find_callee_func_in_expr(e->value.index.index_expr, line_1, col_1); if (f) return f; }
            break;
        case AST_EXPR_AS:
            if (e->value.as_type.operand) return find_callee_func_in_expr(e->value.as_type.operand, line_1, col_1);
            break;
        default:
            break;
    }
    return NULL;
}

static struct ASTFunc *find_callee_func_in_block(const struct ASTBlock *b, int line_1, int col_1) {
    if (!b) return NULL;
    int i;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) { struct ASTFunc *f = find_callee_func_in_expr(b->const_decls[i].init, line_1, col_1); if (f) return f; }
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) { struct ASTFunc *f = find_callee_func_in_expr(b->let_decls[i].init, line_1, col_1); if (f) return f; }
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond) { struct ASTFunc *f = find_callee_func_in_expr(b->loops[i].cond, line_1, col_1); if (f) return f; }
        if (b->loops[i].body) { struct ASTFunc *f = find_callee_func_in_block(b->loops[i].body, line_1, col_1); if (f) return f; }
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init) { struct ASTFunc *f = find_callee_func_in_expr(fl->init, line_1, col_1); if (f) return f; }
        if (fl->cond) { struct ASTFunc *f = find_callee_func_in_expr(fl->cond, line_1, col_1); if (f) return f; }
        if (fl->step) { struct ASTFunc *f = find_callee_func_in_expr(fl->step, line_1, col_1); if (f) return f; }
        if (fl->body) { struct ASTFunc *f = find_callee_func_in_block(fl->body, line_1, col_1); if (f) return f; }
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            { struct ASTFunc *f = find_callee_func_in_expr(b->labeled_stmts[i].u.return_expr, line_1, col_1); if (f) return f; }
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i]) { struct ASTFunc *f = find_callee_func_in_expr(b->expr_stmts[i], line_1, col_1); if (f) return f; }
    if (b->final_expr) { struct ASTFunc *f = find_callee_func_in_expr(b->final_expr, line_1, col_1); if (f) return f; }
    return NULL;
}

/** 确定位置 (line_1, col_1) 处的“目标函数”：若在函数名定义上则返回该函数，若在调用处则返回被调函数。用行索引只搜包含该行的函数。 */
static struct ASTFunc *find_target_function_at(const struct ASTModule *mod, int line_1, int col_1) {
    if (!mod) return NULL;
    for (int i = 0; i < mod->num_funcs; i++) {
        struct ASTFunc *f = mod->funcs[i];
        if (f->line == line_1 && f->col == col_1) return f;
    }
    struct ASTFunc *containing = get_function_at_line(mod, line_1);
    if (containing && containing->body) {
        struct ASTFunc *f = find_callee_func_in_block(containing->body, line_1, col_1);
        if (f) return f;
    }
    return NULL;
}

/** 收集对 func 的所有引用位置（定义 + 各调用点），写入 out_lines/out_cols，返回个数，最多 max_refs。 */
static int collect_refs_add(int line, int col, int *out_lines, int *out_cols, int *count, int max_refs) {
    if (*count >= max_refs) return 0;
    for (int i = 0; i < *count; i++)
        if (out_lines[i] == line && out_cols[i] == col) return 0; /* 去重 */
    out_lines[*count] = line;
    out_cols[*count] = col;
    (*count)++;
    return 1;
}

static void collect_refs_in_expr(const struct ASTExpr *e, const struct ASTFunc *func, int *out_lines, int *out_cols, int *count, int max_refs) {
    if (!e || *count >= max_refs) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func == func) {
        const struct ASTExpr *callee = e->value.call.callee;
        if (callee) collect_refs_add(callee->line, callee->col, out_lines, out_cols, count, max_refs);
    } else if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func == func)
        collect_refs_add(e->line, e->col, out_lines, out_cols, count, max_refs);
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_refs_in_expr(e->value.binop.left, func, out_lines, out_cols, count, max_refs);
            collect_refs_in_expr(e->value.binop.right, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            collect_refs_in_expr(e->value.unary.operand, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_refs_in_expr(e->value.if_expr.cond, func, out_lines, out_cols, count, max_refs);
            collect_refs_in_expr(e->value.if_expr.then_expr, func, out_lines, out_cols, count, max_refs);
            collect_refs_in_expr(e->value.if_expr.else_expr, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_BLOCK:
            break;
        case AST_EXPR_ASSIGN:
            collect_refs_in_expr(e->value.binop.left, func, out_lines, out_cols, count, max_refs);
            collect_refs_in_expr(e->value.binop.right, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_MATCH:
            collect_refs_in_expr(e->value.match_expr.matched_expr, func, out_lines, out_cols, count, max_refs);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_refs_in_expr(e->value.match_expr.arms[i].result, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_refs_in_expr(e->value.field_access.base, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_refs_in_expr(e->value.struct_lit.inits[i], func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_refs_in_expr(e->value.array_lit.elems[i], func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_INDEX:
            collect_refs_in_expr(e->value.index.base, func, out_lines, out_cols, count, max_refs);
            collect_refs_in_expr(e->value.index.index_expr, func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_CALL:
            if (e->value.call.callee) collect_refs_in_expr(e->value.call.callee, func, out_lines, out_cols, count, max_refs);
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_refs_in_expr(e->value.call.args[i], func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_refs_in_expr(e->value.method_call.base, func, out_lines, out_cols, count, max_refs);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_refs_in_expr(e->value.method_call.args[i], func, out_lines, out_cols, count, max_refs);
            break;
        case AST_EXPR_AS:
            collect_refs_in_expr(e->value.as_type.operand, func, out_lines, out_cols, count, max_refs);
            break;
        default:
            break;
    }
}

static void collect_refs_in_block(const struct ASTBlock *b, const struct ASTFunc *func, int *out_lines, int *out_cols, int *count, int max_refs) {
    if (!b) return;
    int i;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_refs_in_expr(b->const_decls[i].init, func, out_lines, out_cols, count, max_refs);
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_refs_in_expr(b->let_decls[i].init, func, out_lines, out_cols, count, max_refs);
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond) collect_refs_in_expr(b->loops[i].cond, func, out_lines, out_cols, count, max_refs);
        if (b->loops[i].body) collect_refs_in_block(b->loops[i].body, func, out_lines, out_cols, count, max_refs);
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init) collect_refs_in_expr(fl->init, func, out_lines, out_cols, count, max_refs);
        if (fl->cond) collect_refs_in_expr(fl->cond, func, out_lines, out_cols, count, max_refs);
        if (fl->step) collect_refs_in_expr(fl->step, func, out_lines, out_cols, count, max_refs);
        if (fl->body) collect_refs_in_block(fl->body, func, out_lines, out_cols, count, max_refs);
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_refs_in_expr(b->labeled_stmts[i].u.return_expr, func, out_lines, out_cols, count, max_refs);
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i]) collect_refs_in_expr(b->expr_stmts[i], func, out_lines, out_cols, count, max_refs);
    if (b->final_expr) collect_refs_in_expr(b->final_expr, func, out_lines, out_cols, count, max_refs);
}

static int collect_refs_to_func(const struct ASTModule *mod, const struct ASTFunc *func, int *out_lines, int *out_cols, int max_refs) {
    int count = 0;
    collect_refs_add(func->line, func->col, out_lines, out_cols, &count, max_refs);
    for (int i = 0; i < mod->num_funcs; i++)
        if (mod->funcs[i]->body) collect_refs_in_block(mod->funcs[i]->body, func, out_lines, out_cols, &count, max_refs);
    return count;
}

/* ---------- Hover：按位置找表达式 + 类型转字符串 ---------- */

/** 递归找包含 (line_1, col_1) 的最内层表达式；先查子节点，再判断本节点。 */
static struct ASTExpr *get_innermost_expr_at(struct ASTExpr *e, int line_1, int col_1) {
    if (!e) return NULL;
    struct ASTExpr *child = NULL;
    switch (e->kind) {
        case AST_EXPR_CALL:
            if (e->value.call.callee) { child = get_innermost_expr_at(e->value.call.callee, line_1, col_1); if (child) return child; }
            for (int i = 0; i < e->value.call.num_args; i++)
                if (e->value.call.args[i]) { child = get_innermost_expr_at(e->value.call.args[i], line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_METHOD_CALL:
            if (e->value.method_call.base) { child = get_innermost_expr_at(e->value.method_call.base, line_1, col_1); if (child) return child; }
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (e->value.method_call.args[i]) { child = get_innermost_expr_at(e->value.method_call.args[i], line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            if (e->value.binop.left) { child = get_innermost_expr_at(e->value.binop.left, line_1, col_1); if (child) return child; }
            if (e->value.binop.right) { child = get_innermost_expr_at(e->value.binop.right, line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            if (e->value.unary.operand) return get_innermost_expr_at(e->value.unary.operand, line_1, col_1);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            if (e->value.if_expr.cond) { child = get_innermost_expr_at(e->value.if_expr.cond, line_1, col_1); if (child) return child; }
            if (e->value.if_expr.then_expr) { child = get_innermost_expr_at(e->value.if_expr.then_expr, line_1, col_1); if (child) return child; }
            if (e->value.if_expr.else_expr) { child = get_innermost_expr_at(e->value.if_expr.else_expr, line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_BLOCK:
            break;
        case AST_EXPR_ASSIGN:
            if (e->value.binop.left) { child = get_innermost_expr_at(e->value.binop.left, line_1, col_1); if (child) return child; }
            if (e->value.binop.right) { child = get_innermost_expr_at(e->value.binop.right, line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_MATCH:
            if (e->value.match_expr.matched_expr) { child = get_innermost_expr_at(e->value.match_expr.matched_expr, line_1, col_1); if (child) return child; }
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (e->value.match_expr.arms[i].result) { child = get_innermost_expr_at(e->value.match_expr.arms[i].result, line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_FIELD_ACCESS:
            if (e->value.field_access.base) return get_innermost_expr_at(e->value.field_access.base, line_1, col_1);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (e->value.struct_lit.inits[i]) { child = get_innermost_expr_at(e->value.struct_lit.inits[i], line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (e->value.array_lit.elems[i]) { child = get_innermost_expr_at(e->value.array_lit.elems[i], line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_INDEX:
            if (e->value.index.base) { child = get_innermost_expr_at(e->value.index.base, line_1, col_1); if (child) return child; }
            if (e->value.index.index_expr) { child = get_innermost_expr_at(e->value.index.index_expr, line_1, col_1); if (child) return child; }
            break;
        case AST_EXPR_AS:
            if (e->value.as_type.operand) return get_innermost_expr_at(e->value.as_type.operand, line_1, col_1);
            break;
        default:
            break;
    }
    if (expr_at(e, line_1, col_1)) return e;
    return NULL;
}

static struct ASTExpr *get_expr_at_in_block(const struct ASTBlock *b, int line_1, int col_1) {
    if (!b) return NULL;
    int i;
    struct ASTExpr *e;
    for (i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init && (e = get_innermost_expr_at(b->const_decls[i].init, line_1, col_1))) return e;
    for (i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && (e = get_innermost_expr_at(b->let_decls[i].init, line_1, col_1))) return e;
    for (i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond && (e = get_innermost_expr_at(b->loops[i].cond, line_1, col_1))) return e;
        if (b->loops[i].body && (e = get_expr_at_in_block(b->loops[i].body, line_1, col_1))) return e;
    }
    for (i = 0; i < b->num_for_loops; i++) {
        struct ASTForLoop *fl = &b->for_loops[i];
        if (fl->init && (e = get_innermost_expr_at(fl->init, line_1, col_1))) return e;
        if (fl->cond && (e = get_innermost_expr_at(fl->cond, line_1, col_1))) return e;
        if (fl->step && (e = get_innermost_expr_at(fl->step, line_1, col_1))) return e;
        if (fl->body && (e = get_expr_at_in_block(fl->body, line_1, col_1))) return e;
    }
    for (i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr &&
            (e = get_innermost_expr_at(b->labeled_stmts[i].u.return_expr, line_1, col_1))) return e;
    for (i = 0; i < b->num_expr_stmts; i++)
        if (b->expr_stmts[i] && (e = get_innermost_expr_at(b->expr_stmts[i], line_1, col_1))) return e;
    if (b->final_expr && (e = get_innermost_expr_at(b->final_expr, line_1, col_1))) return e;
    return NULL;
}

/** 按位置取表达式；先按行索引只搜包含该行的函数，再搜顶层 let/const 的 init。 */
static struct ASTExpr *get_expr_at_in_module(const struct ASTModule *mod, int line_1, int col_1) {
    if (!mod) return NULL;
    struct ASTFunc *containing = get_function_at_line(mod, line_1);
    if (containing && containing->body) {
        struct ASTExpr *e = get_expr_at_in_block(containing->body, line_1, col_1);
        if (e) return e;
    }
    for (int i = 0; i < mod->num_top_level_lets; i++)
        if (mod->top_level_lets[i].init) {
            struct ASTExpr *e = get_innermost_expr_at(mod->top_level_lets[i].init, line_1, col_1);
            if (e) return e;
        }
    return NULL;
}

/** 将 ASTType 格式化为字符串写入 buf，返回长度；cap 为 buf 容量。 */
static int type_to_string(const struct ASTType *ty, char *buf, int cap) {
    if (!ty || !buf || cap <= 0) return 0;
    switch (ty->kind) {
        case AST_TYPE_I32: return snprintf(buf, (size_t)cap, "i32");
        case AST_TYPE_BOOL: return snprintf(buf, (size_t)cap, "bool");
        case AST_TYPE_U8: return snprintf(buf, (size_t)cap, "u8");
        case AST_TYPE_U32: return snprintf(buf, (size_t)cap, "u32");
        case AST_TYPE_U64: return snprintf(buf, (size_t)cap, "u64");
        case AST_TYPE_I64: return snprintf(buf, (size_t)cap, "i64");
        case AST_TYPE_USIZE: return snprintf(buf, (size_t)cap, "usize");
        case AST_TYPE_ISIZE: return snprintf(buf, (size_t)cap, "isize");
        case AST_TYPE_F32: return snprintf(buf, (size_t)cap, "f32");
        case AST_TYPE_F64: return snprintf(buf, (size_t)cap, "f64");
        case AST_TYPE_VOID: return snprintf(buf, (size_t)cap, "void");
        case AST_TYPE_NAMED: return snprintf(buf, (size_t)cap, "%s", ty->name ? ty->name : "?");
        case AST_TYPE_PTR: {
            char inner[64];
            int n = ty->elem_type ? type_to_string(ty->elem_type, inner, (int)sizeof(inner)) : 0;
            if (n <= 0) return snprintf(buf, (size_t)cap, "*?");
            return snprintf(buf, (size_t)cap, "*%s", inner);
        }
        case AST_TYPE_ARRAY: {
            char inner[64];
            int n = ty->elem_type ? type_to_string(ty->elem_type, inner, (int)sizeof(inner)) : 0;
            if (n <= 0) return snprintf(buf, (size_t)cap, "[%d]?", ty->array_size);
            return snprintf(buf, (size_t)cap, "[%d]%s", ty->array_size, inner);
        }
        case AST_TYPE_SLICE: {
            char inner[64];
            int n = ty->elem_type ? type_to_string(ty->elem_type, inner, (int)sizeof(inner)) : 0;
            if (n <= 0) return snprintf(buf, (size_t)cap, "[]?");
            return snprintf(buf, (size_t)cap, "[]%s", inner);
        }
        case AST_TYPE_VECTOR: {
            char inner[64];
            int n = ty->elem_type ? type_to_string(ty->elem_type, inner, (int)sizeof(inner)) : 0;
            if (n <= 0) return snprintf(buf, (size_t)cap, "?x%d", ty->array_size);
            return snprintf(buf, (size_t)cap, "%sx%d", inner, ty->array_size);
        }
        default: return snprintf(buf, (size_t)cap, "?");
    }
}

/** 将诊断列表写成 LSP Diagnostic[] JSON 写入 out，返回长度；out_cap 为 out 的容量。 */
static int lsp_diag_to_json(char *out, int out_cap) {
    int k = 0;
    if (!out || out_cap <= 0) return 0;
    if (out_cap < 3) return 0;
    out[k++] = '[';
    for (int i = 0; i < s_diag_count && k < out_cap - 2; i++) {
        LspDiagEntry *e = &s_diag[i];
        int line0 = e->line > 0 ? e->line - 1 : 0;
        int col0 = e->col > 0 ? e->col - 1 : 0;
        char esc_buf[LSP_MSG_MAX * 2 + 16];
        json_escape_str(e->msg, esc_buf, (int)sizeof(esc_buf));
        int n = snprintf(out + k, (size_t)(out_cap - k),
            "%s{\"range\":{\"start\":{\"line\":%d,\"character\":%d},\"end\":{\"line\":%d,\"character\":%d}},\"message\":\"%s\",\"severity\":%d}",
            i > 0 ? "," : "", line0, col0, line0, col0 + 1, esc_buf, e->severity);
        if (n <= 0 || n >= out_cap - k) break;
        k += n;
    }
    if (k < out_cap) out[k++] = ']';
    out[k] = '\0';
    return k;
}

int lsp_build_diagnostics_response(int id_val, const uint8_t *source, int source_len,
                                   uint8_t *out_buf, int out_cap) {
    if (!source || !out_buf || out_cap <= 0) return -1;
    if (source_len < 0) source_len = 0;
    (void)lsp_ensure_module(source, source_len, -1); /* 命中则复用缓存；未命中则 parse+全量 typeck 并更新 s_last_diag_* */
    if (s_last_diag_len <= 0) s_last_diag_len = 1;
    const char *result_json = s_last_diag_json;
    int result_len = s_last_diag_len;
    if (!result_json || result_json[0] != '[') {
        result_json = "[]";
        result_len = 2;
    }
    const char *prefix = "{\"jsonrpc\":\"2.0\",\"id\":";
    const char *mid = ",\"result\":";
    const char *suffix = "}";
    int k = 0;
    for (int i = 0; prefix[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)prefix[i];
    if (k >= out_cap - 20) return -1;
    k += snprintf((char *)out_buf + k, (size_t)(out_cap - k), "%d", id_val);
    if (k >= out_cap - 2) return -1;
    for (int i = 0; mid[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)mid[i];
    for (int i = 0; i < result_len && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)result_json[i];
    for (int i = 0; suffix[i] && k < out_cap - 1; i++, k++) out_buf[k] = (uint8_t)suffix[i];
    return k;
}

/**
 * 在 (line_0, col_0)（LSP 0-based）处查找“定义”；复用模块缓存，不重复 parse/typeck。
 */
int lsp_definition_at(const uint8_t *source, int source_len, int line_0, int col_0, int *out_line, int *out_col) {
    if (!source || !out_line || !out_col || source_len < 0) return 0;
    ASTModule *mod = lsp_ensure_module(source, source_len, line_0 + 1);
    if (!mod) return 0;
    int line_1 = line_0 + 1;
    int col_1 = col_0 + 1;
    return find_def_in_module(mod, line_1, col_1, out_line, out_col);
}

#define LSP_REFs_MAX 128

/**
 * 在 (line_0, col_0) 处确定目标函数并收集引用位置；复用模块缓存。优先使用预计算的引用索引，O(目标函数)。
 */
int lsp_references_at(const uint8_t *source, int source_len, int line_0, int col_0,
                      int *out_lines, int *out_cols, int max_refs) {
    if (!source || !out_lines || !out_cols || source_len < 0 || max_refs <= 0) return 0;
    ASTModule *mod = lsp_ensure_module(source, source_len, -1);
    if (!mod) return 0;
    int line_1 = line_0 + 1;
    int col_1 = col_0 + 1;
    struct ASTFunc *target = find_target_function_at(mod, line_1, col_1);
    if (!target) return 0;
    int j = line_index_of_func(target);
    if (j >= 0 && s_refs_count[j] > 0) {
        int n = s_refs_count[j];
        if (n > max_refs) n = max_refs;
        for (int i = 0; i < n; i++) {
            out_lines[i] = s_refs_lines[j][i];
            out_cols[i] = s_refs_cols[j][i];
        }
        return n;
    }
    return collect_refs_to_func(mod, target, out_lines, out_cols, max_refs);
}

#define LSP_HOVER_BUF_MAX 128

/**
 * 在 (line_0, col_0) 处找表达式类型并格式化为字符串；复用模块缓存。
 */
int lsp_hover_at(const uint8_t *source, int source_len, int line_0, int col_0, char *out_buf, int out_cap) {
    if (!source || !out_buf || out_cap <= 0 || source_len < 0) return 0;
    ASTModule *mod = lsp_ensure_module(source, source_len, line_0 + 1);
    if (!mod) return 0;
    int line_1 = line_0 + 1;
    int col_1 = col_0 + 1;
    struct ASTExpr *e = get_expr_at_in_module(mod, line_1, col_1);
    int len = 0;
    if (e && e->resolved_type) len = type_to_string(e->resolved_type, out_buf, out_cap);
    return len > 0 ? len : 0;
}
