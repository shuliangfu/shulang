/**
 * lexer.c — 词法分析器实现
 *
 * 文件职责：将 .su 源码按字符流切分为 Token 流，识别关键字（function、import、i32）、标识符、整数字面量、符号（括号、->、.、;）及空白与行注释。
 * 所属模块：编译器前端 lexer，compiler/src/lexer/；实现 lexer.h 声明的接口。
 * 与其它文件的关系：依赖 include/token.h；被 parser、main 通过 lexer.h 调用；不依赖 parser 或 ast。
 * 重要约定：与 compiler/docs/语法子集-阶段1与2.md 及阶段 5 import 词法一致；Token 的 line/col 为该 Token 在源码中的起始位置；ident 不拷贝，指向 source 内地址。
 */

#include "lexer.h"
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Lexer {
    const char *src;  /**< 当前扫描位置 */
    const char *end;  /**< 源码结尾（不含 NUL） */
    int line;         /**< 当前行号，从 1 开始 */
    int col;          /**< 当前列号，从 1 开始 */
};

/**
 * 查看当前字符不消费；到达末尾返回 0。
 * 参数：l 当前 Lexer。返回值：当前字节值（0 表示已到 end）。无副作用。
 */
static int lexer_peek(Lexer *l) {
    return (l->src < l->end) ? (unsigned char)*l->src : 0;
}

/**
 * 消费当前字符并推进指针；若为换行则 line++、col 置 1，否则 col++。
 * 参数：l 当前 Lexer。返回值：被消费的字节值，已到末尾则返回 0。副作用：修改 l->src、l->line、l->col。
 */
static int lexer_advance(Lexer *l) {
    if (l->src >= l->end) return 0;
    int c = (unsigned char)*l->src++;
    if (c == '\n') { l->line++; l->col = 1; } else { l->col++; }
    return c;
}

/**
 * 创建 Lexer；见 lexer.h 中 lexer_new 注释。
 */
Lexer *lexer_new(const char *source) {
    Lexer *l = (Lexer *)malloc(sizeof(Lexer));
    if (!l) return NULL;
    l->src = source;
    l->end = source + strlen(source);
    l->line = 1;
    l->col = 1;
    return l;
}

/**
 * 向 out 写入仅 kind 的 Token，位置取当前 l->line/col；value 与 ident_len 置 0/NULL。
 * 参数：l 提供位置；out 输出；kind 类型。无返回值。副作用：仅写 out。
 */
static void emit_token(Lexer *l, Token *out, TokenKind kind) {
    out->kind = kind;
    out->line = l->line;
    out->col = l->col;
    out->value.int_val = 0;
    out->value.ident = NULL;
    out->ident_len = 0;
}

/**
 * 识别标识符或关键字（function、i32、import）；先按 [a-zA-Z0-9_] 推进，再按内容区分。
 * 参数：l 当前 Lexer；out 输出 Token。返回值：无。副作用：推进 l，写 out；IDENT 时 out->value.ident 指向 start，ident_len 有效。
 */
static void lex_ident_or_keyword(Lexer *l, Token *out) {
    const char *start = l->src;
    int line0 = l->line, col0 = l->col;
    while (l->src < l->end && (isalnum((unsigned char)*l->src) || *l->src == '_'))
        lexer_advance(l);
    size_t len = (size_t)(l->src - start);

    if (len == 8 && memcmp(start, "function", 8) == 0) {
        out->kind = TOKEN_FUNCTION;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "let", 3) == 0) {
        out->kind = TOKEN_LET;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "const", 5) == 0) {
        out->kind = TOKEN_CONST;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 2 && memcmp(start, "if", 2) == 0) {
        out->kind = TOKEN_IF;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 4 && memcmp(start, "else", 4) == 0) {
        out->kind = TOKEN_ELSE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "while", 5) == 0) {
        out->kind = TOKEN_WHILE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 4 && memcmp(start, "loop", 4) == 0) {
        out->kind = TOKEN_LOOP;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "for", 3) == 0) {
        out->kind = TOKEN_FOR;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "break", 5) == 0) {
        out->kind = TOKEN_BREAK;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 8 && memcmp(start, "continue", 8) == 0) {
        out->kind = TOKEN_CONTINUE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 6 && memcmp(start, "return", 6) == 0) {
        out->kind = TOKEN_RETURN;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "panic", 5) == 0) {
        out->kind = TOKEN_PANIC;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "defer", 5) == 0) {
        out->kind = TOKEN_DEFER;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "match", 5) == 0) {
        out->kind = TOKEN_MATCH;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 6 && memcmp(start, "struct", 6) == 0) {
        out->kind = TOKEN_STRUCT;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 4 && memcmp(start, "goto", 4) == 0) {
        out->kind = TOKEN_GOTO;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    /* _ 单独作为 match 通配模式 */
    if (len == 1 && start[0] == '_') {
        out->kind = TOKEN_UNDERSCORE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "i32", 3) == 0) {
        out->kind = TOKEN_I32;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 4 && memcmp(start, "bool", 4) == 0) {
        out->kind = TOKEN_BOOL;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 2 && memcmp(start, "u8", 2) == 0) {
        out->kind = TOKEN_U8;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "u32", 3) == 0) {
        out->kind = TOKEN_U32;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "u64", 3) == 0) {
        out->kind = TOKEN_U64;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 3 && memcmp(start, "i64", 3) == 0) {
        out->kind = TOKEN_I64;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "usize", 5) == 0) {
        out->kind = TOKEN_USIZE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "isize", 5) == 0) {
        out->kind = TOKEN_ISIZE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 4 && memcmp(start, "true", 4) == 0) {
        out->kind = TOKEN_TRUE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 5 && memcmp(start, "false", 5) == 0) {
        out->kind = TOKEN_FALSE;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }
    if (len == 6 && memcmp(start, "import", 6) == 0) {
        out->kind = TOKEN_IMPORT;
        out->line = line0;
        out->col = col0;
        out->value.ident = NULL;
        out->ident_len = 0;
        return;
    }

    out->kind = TOKEN_IDENT;
    out->line = line0;
    out->col = col0;
    out->value.ident = start;
    out->ident_len = (int)(len <= (size_t)INT_MAX ? len : 0);
}

/**
 * 识别十进制整数字面量；推进连续数字并计算值，写入 out->value.int_val。
 * 参数：l 当前 Lexer；out 输出 Token。返回值：无。副作用：推进 l，写 out；line/col 为数字起始位置。
 */
static void lex_int(Lexer *l, Token *out) {
    int line0 = l->line, col0 = l->col;
    int val = 0;
    while (l->src < l->end && isdigit((unsigned char)*l->src))
        val = val * 10 + (lexer_advance(l) - '0');
    out->kind = TOKEN_INT;
    out->line = line0;
    out->col = col0;
    out->value.int_val = val;
    out->ident_len = 0;
}

/**
 * 取下一个 Token；见 lexer.h 中 lexer_next 注释。
 */
void lexer_next(Lexer *l, Token *out) {
    /* 跳过空白 */
    while (l->src < l->end) {
        int c = lexer_peek(l);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            lexer_advance(l);
            continue;
        }
        if (c == '/' && l->src + 1 < l->end && l->src[1] == '/') {
            while (l->src < l->end && lexer_peek(l) != '\n') lexer_advance(l);
            continue;
        }
        break;
    }

    if (l->src >= l->end) {
        emit_token(l, out, TOKEN_EOF);
        return;
    }

    int c = lexer_peek(l);
    if (isalpha((unsigned char)c) || c == '_') {
        lex_ident_or_keyword(l, out);
        return;
    }
    if (isdigit((unsigned char)c)) {
        lex_int(l, out);
        return;
    }

    int line = l->line, col = l->col;
    lexer_advance(l);
    out->line = line;
    out->col = col;
    out->value.int_val = 0;
    out->value.ident = NULL;
    out->ident_len = 0;

    switch (c) {
        case '(': out->kind = TOKEN_LPAREN; break;
        case ')': out->kind = TOKEN_RPAREN; break;
        case '{': out->kind = TOKEN_LBRACE; break;
        case '}': out->kind = TOKEN_RBRACE; break;
        case '[': out->kind = TOKEN_LBRACKET; break;
        case ']': out->kind = TOKEN_RBRACKET; break;
        case ',': out->kind = TOKEN_COMMA; break;
        case ':': out->kind = TOKEN_COLON; break;
        case '.': out->kind = TOKEN_DOT; break;
        case ';': out->kind = TOKEN_SEMICOLON; break;
        case '+': out->kind = TOKEN_PLUS; break;
        case '-':
            if (lexer_peek(l) == '>') { lexer_advance(l); out->kind = TOKEN_ARROW; }
            else { out->kind = TOKEN_MINUS; } /* 二元减 */
            break;
        case '*': out->kind = TOKEN_STAR; break;   /* 二元乘 */
        case '/': out->kind = TOKEN_SLASH; break;  /* 二元除（// 已在 while 中跳过） */
        case '%': out->kind = TOKEN_PERCENT; break; /* 取模 */
        case '^': out->kind = TOKEN_CARET; break;   /* 按位异或 */
        case '~': out->kind = TOKEN_TILDE; break;   /* 按位取反 */
        case '&':
            if (lexer_peek(l) == '&') { lexer_advance(l); out->kind = TOKEN_AMPAMP; }
            else { out->kind = TOKEN_AMP; }
            break;
        case '|':
            if (lexer_peek(l) == '|') { lexer_advance(l); out->kind = TOKEN_PIPEPIPE; }
            else { out->kind = TOKEN_PIPE; }
            break;
        case '<':
            if (lexer_peek(l) == '=') { lexer_advance(l); out->kind = TOKEN_LE; }
            else if (lexer_peek(l) == '<') { lexer_advance(l); out->kind = TOKEN_LSHIFT; }
            else { out->kind = TOKEN_LT; }
            break;
        case '>':
            if (lexer_peek(l) == '=') { lexer_advance(l); out->kind = TOKEN_GE; }
            else if (lexer_peek(l) == '>') { lexer_advance(l); out->kind = TOKEN_RSHIFT; }
            else { out->kind = TOKEN_GT; }
            break;
        case '!':
            if (lexer_peek(l) == '=') { lexer_advance(l); out->kind = TOKEN_NE; }
            else { out->kind = TOKEN_BANG; }
            break;
        case '=':
            if (lexer_peek(l) == '>') { lexer_advance(l); out->kind = TOKEN_FATARROW; }
            else if (lexer_peek(l) == '=') { lexer_advance(l); out->kind = TOKEN_EQ; }
            else { out->kind = TOKEN_ASSIGN; } /* 单 = 用于 let/const 初始化 */
            break;
        default:
            out->kind = TOKEN_EOF; /* 非法字符，用 EOF 表示错误，后续可增加 TOKEN_ERROR */
            break;
    }
}

/**
 * 释放 Lexer；见 lexer.h 中 lexer_free 注释。
 */
void lexer_free(Lexer *l) {
    free(l);
}
