/**
 * parser.c — 语法分析器实现
 *
 * 文件职责：递归下降解析 Token 流，支持顶层 import path; 与可选的 fn main() -> i32 { 整数字面量 }，构建 ASTModule（含 import_paths、main_func）。
 * 所属模块：编译器前端 parser，compiler/src/parser/；实现 parser.h 声明的 parse。
 * 与其它文件的关系：依赖 lexer.h、include/ast.h、include/token.h；被 main 调用；产出的 AST 由 typeck、codegen 消费。
 * 重要约定：与 compiler/docs/语法子集-阶段1与2.md 及阶段 5 import 语法一致；所有动态分配由 ast_module_free 统一释放；语法错误时已向 stderr 打印 "parse error at line:col: msg"。
 */

#include "parser/parser.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 解析器内部状态：Lexer 引用 + 当前 lookahead Token */
typedef struct {
    Lexer *lex;
    Token cur;
    int cur_loaded;  /**< 1 表示 cur 已加载有效 Token */
} Parser;

/**
 * 推进到下一个 Token 并写入 p->cur。
 * 参数：p 解析器状态。返回值：无。副作用：调用 lexer_next，更新 p->cur 与 p->cur_loaded。
 */
static void advance(Parser *p) {
    lexer_next(p->lex, &p->cur);
    p->cur_loaded = 1;
}

/**
 * 返回当前 lookahead Token 指针；若尚未加载则先 advance 一次。
 * 参数：p 解析器状态。返回值：指向 p->cur 的只读指针。无额外副作用。
 */
static const Token *peek(Parser *p) {
    if (!p->cur_loaded) advance(p);
    return &p->cur;
}

/**
 * 判断当前 Token 是否为 IDENT 且内容为 "main"（用于识别入口函数）。
 * 参数：t 当前 Token。返回值：1 表示是 main 标识符，0 否则。无副作用。
 */
static int is_main_ident(const Token *t) {
    return t->kind == TOKEN_IDENT && t->ident_len == 4
           && memcmp(t->value.ident, "main", 4) == 0;
}

/**
 * 向 stderr 输出 "parse error at line:col: msg" 并返回 -1；用于统一错误处理。
 * 参数：p 解析器状态（用于取当前 Token 位置）；msg 错误描述字符串。返回值：-1。副作用：写 stderr。
 */
static int fail(Parser *p, const char *msg) {
    const Token *t = peek(p);
    fprintf(stderr, "parse error at %d:%d: %s\n", t->line, t->col, msg);
    return -1;
}

/**
 * 解析主表达式（primary）；当前仅支持整数字面量（TOKEN_INT）。
 * 参数：p 解析器状态。返回值：成功返回新分配的 ASTExpr*；失败返回 NULL 且已通过 fail 报错。
 * 错误与边界：当前 Token 非 INT 时失败；malloc 失败时返回 NULL。副作用：成功时 advance。
 */
static ASTExpr *parse_primary(Parser *p) {
    const Token *t = peek(p);
    if (t->kind != TOKEN_INT) {
        fail(p, "expected integer literal");
        return NULL;
    }
    ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
    if (!e) {
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    e->kind = AST_EXPR_LIT;
    e->value.int_val = t->value.int_val;
    advance(p);
    return e;
}

/**
 * 解析表达式；支持整数字面量及左结合的加减（primary (PLUS|MINUS primary)*）。
 * 参数：p 解析器状态。返回值：成功返回新分配的 ASTExpr*（调用方通过 ast_module_free/ast_expr_free 释放）；失败返回 NULL 且已通过 fail 报错。
 * 错误与边界：primary 失败或中间 malloc 失败时返回 NULL。副作用：成功时 advance 消耗对应 Token。
 */
static ASTExpr *parse_expr(Parser *p) {
    ASTExpr *left = parse_primary(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        if (t->kind != TOKEN_PLUS && t->kind != TOKEN_MINUS)
            return left;
        /* 保存运算符类型再 advance，否则 peek 返回 &p->cur，advance 后 t 会指向下一 token */
        int op = t->kind;
        advance(p);
        ASTExpr *right = parse_primary(p);
        if (!right) {
            ast_expr_free(left);
            return NULL;
        }
        ASTExpr *bin = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!bin) {
            ast_expr_free(left);
            ast_expr_free(right);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        bin->kind = (op == TOKEN_PLUS) ? AST_EXPR_ADD : AST_EXPR_SUB;
        bin->value.binop.left = left;
        bin->value.binop.right = right;
        left = bin;
    }
}

/** 最大 import 数量 */
#define MAX_IMPORTS 32

/**
 * 解析单条 import 路径：IDENT 或 I32 后接零个或多个 . IDENT/I32，拼成 "core.types" 形式。
 * 参数：p 解析器状态；当前 Token 须为路径起始。返回值：成功返回 strdup 的字符串，调用方须 free；失败返回 NULL 且已 fail。
 * 错误与边界：路径过长（≥256）或非法 token 序列时失败。副作用：成功时 advance 消耗整条路径。
 */
static char *parse_import_path(Parser *p) {
    char buf[256];
    int off = 0;
    const Token *t = peek(p);
    if (t->kind != TOKEN_IDENT && t->kind != TOKEN_I32) {
        fail(p, "expected identifier in import path");
        return NULL;
    }
    int len = t->ident_len;
    if (t->kind == TOKEN_IDENT && t->value.ident && len > 0) {
        if (off + len >= (int)sizeof(buf)) { fail(p, "import path too long"); return NULL; }
        memcpy(buf + off, t->value.ident, (size_t)len);
        off += len;
    } else if (t->kind == TOKEN_I32) {
        if (off + 3 >= (int)sizeof(buf)) { fail(p, "import path too long"); return NULL; }
        memcpy(buf + off, "i32", 3);
        off += 3;
    } else {
        fail(p, "expected identifier in import path");
        return NULL;
    }
    advance(p);
    while (peek(p)->kind == TOKEN_DOT) {
        advance(p);
        buf[off++] = '.';
        t = peek(p);
        if (t->kind != TOKEN_IDENT && t->kind != TOKEN_I32) {
            fail(p, "expected identifier after '.' in import path");
            return NULL;
        }
        len = t->ident_len;
        if (t->kind == TOKEN_IDENT && t->value.ident && len > 0) {
            if (off + len >= (int)sizeof(buf)) { fail(p, "import path too long"); return NULL; }
            memcpy(buf + off, t->value.ident, (size_t)len);
            off += len;
        } else if (t->kind == TOKEN_I32) {
            if (off + 3 >= (int)sizeof(buf)) { fail(p, "import path too long"); return NULL; }
            memcpy(buf + off, "i32", 3);
            off += 3;
        } else {
            fail(p, "expected identifier after '.'");
            return NULL;
        }
        advance(p);
    }
    buf[off] = '\0';
    return strdup(buf);
}

/* parse 的完整说明见 parser.h */
int parse(Lexer *lex, ASTModule **out) {
    if (!out) return -1;
    *out = NULL;

    Parser prs = { .lex = lex, .cur_loaded = 0 };

    ASTModule *mod = (ASTModule *)malloc(sizeof(ASTModule));
    if (!mod) {
        fprintf(stderr, "parse: out of memory\n");
        return -1;
    }
    mod->import_paths = NULL;
    mod->num_imports = 0;
    mod->main_func = NULL;

    /* [ import path ; ]* */
    char *import_list[MAX_IMPORTS];
    int nimports = 0;
    while (peek(&prs)->kind == TOKEN_IMPORT) {
        advance(&prs);
        char *path = parse_import_path(&prs);
        if (!path) {
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        if (peek(&prs)->kind != TOKEN_SEMICOLON) {
            free(path);
            fail(&prs, "expected ';' after import path");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (nimports >= MAX_IMPORTS) {
            free(path);
            fail(&prs, "too many imports");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        import_list[nimports++] = path;
    }

    /* 可选：fn main() -> i32 { expr } */
    if (peek(&prs)->kind == TOKEN_FN) {
        advance(&prs);
        if (!is_main_ident(peek(&prs))) {
            fail(&prs, "expected 'main'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_LPAREN) {
            fail(&prs, "expected '('");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_RPAREN) {
            fail(&prs, "expected ')'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_ARROW) {
            fail(&prs, "expected '->'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_I32) {
            fail(&prs, "expected 'i32'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_LBRACE) {
            fail(&prs, "expected '{'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        ASTExpr *body = parse_expr(&prs);
        if (!body) {
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        if (peek(&prs)->kind != TOKEN_RBRACE) {
            ast_expr_free(body);
            fail(&prs, "expected '}'");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_EOF) {
            ast_expr_free(body);
            fail(&prs, "expected end of file");
            while (nimports--) free(import_list[nimports]);
            free(mod);
            return -1;
        }
        ASTFunc *func = (ASTFunc *)malloc(sizeof(ASTFunc));
        if (!func) {
            ast_expr_free(body);
            while (nimports--) free(import_list[nimports]);
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        func->name = (const char *)strdup("main");
        func->return_type = (const char *)strdup("i32");
        func->body = body;
        if (!func->name || !func->return_type) {
            if (func->name) free((void *)func->name);
            if (func->return_type) free((void *)func->return_type);
            ast_expr_free(body);
            free(func);
            while (nimports--) free(import_list[nimports]);
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        mod->main_func = func;
    } else if (peek(&prs)->kind != TOKEN_EOF) {
        fail(&prs, "expected 'fn main' or end of file");
        while (nimports--) free(import_list[nimports]);
        free(mod);
        return -1;
    }

    /* 拷贝 import 列表到 mod */
    if (nimports > 0) {
        mod->import_paths = (char **)malloc((size_t)nimports * sizeof(char *));
        if (!mod->import_paths) {
            while (nimports--) free(import_list[nimports]);
            if (mod->main_func) {
                free((void *)mod->main_func->name);
                free((void *)mod->main_func->return_type);
                ast_expr_free(mod->main_func->body);
                free(mod->main_func);
            }
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        for (int i = 0; i < nimports; i++)
            mod->import_paths[i] = import_list[i];
        mod->num_imports = nimports;
    }

    *out = mod;
    return 0;
}
