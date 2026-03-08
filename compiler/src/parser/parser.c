/**
 * parser.c — 语法分析器实现
 *
 * 文件职责：递归下降解析 Token 流，支持顶层 import path; 与可选的 function main() -> i32 { 整数字面量 }，构建 ASTModule（含 import_paths、main_func）。
 * 所属模块：编译器前端 parser，compiler/src/parser/；实现 parser.h 声明的 parse。
 * 与其它文件的关系：依赖 lexer.h、include/ast.h、include/token.h；被 main 调用；产出的 AST 由 typeck、codegen 消费。
 * 重要约定：与 compiler/docs/语法子集-阶段1与2.md 及阶段 5 import 语法一致；所有动态分配由 ast_module_free 统一释放；语法错误时已向 stderr 打印 "parse error at line:col: msg"。
 */

#include "parser/parser.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 解析器内部状态：Lexer 引用 + 当前 lookahead Token + 下一 Token（用于 label: 判断） */
typedef struct {
    Lexer *lex;
    Token cur;
    int cur_loaded;  /**< 1 表示 cur 已加载有效 Token */
    Token next;      /**< 下一 Token，用于 peek_next（如 ident 后是否 : ） */
    int next_loaded; /**< 1 表示 next 已加载 */
} Parser;

/**
 * 推进到下一个 Token：cur 变为 next（或新取词），next 置为未加载。
 * 参数：p 解析器状态。返回值：无。副作用：更新 p->cur、p->next_loaded。
 */
static void advance(Parser *p) {
    if (p->next_loaded) {
        p->cur = p->next;
        p->next_loaded = 0;
    } else {
        lexer_next(p->lex, &p->cur);
    }
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
 * 返回下一 Token 指针（用于判断 ident 后是否为 : 以区分 label 与表达式）；若未加载则取词一次。
 * 参数：p 解析器状态。返回值：指向 p->next 的只读指针。副作用：可能调用 lexer_next 填充 p->next。
 */
static const Token *peek_next(Parser *p) {
    if (!p->next_loaded) {
        lexer_next(p->lex, &p->next);
        p->next_loaded = 1;
    }
    return &p->next;
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

/** 单 struct 字面量最大字段数（与 parse_one_struct 用到的 MAX_STRUCT_FIELDS 一致） */
#define MAX_STRUCT_FIELDS 32

/* 前向声明：parse_primary 中 ( expr ) 会调用 parse_expr；parse_postfix 调用 parse_primary */
static ASTExpr *parse_expr(Parser *p);

static ASTExpr *parse_term(Parser *p);

static ASTExpr *parse_postfix(Parser *p);

/**
 * 解析类型名称（内建/标识符类型名、裸指针 *T；* 后递归解析元素类型）。
 * 参数：p 解析器状态，当前 Token 须为类型起始（* 或内建关键字或标识符）。返回值：成功返回新分配的 ASTType*，失败返回 NULL 且已报错。
 */
static ASTType *parse_type_name(Parser *p) {
    const Token *t = peek(p);
    if (!t) return NULL;
    /* 裸指针 *T：文档 §5.1，阶段 6 */
    if (t->kind == TOKEN_STAR) {
        advance(p);
        ASTType *inner = parse_type_name(p);
        if (!inner) return NULL;
        ASTType *ty = (ASTType *)malloc(sizeof(ASTType));
        if (!ty) {
            ast_type_free(inner);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        ty->kind = AST_TYPE_PTR;
        ty->name = NULL;
        ty->elem_type = inner;
        ty->array_size = 0;
        return ty;
    }
    /* 切片 []T 或 固定长数组 [N]T：文档 §6.2、§6.3 */
    if (t->kind == TOKEN_LBRACKET) {
        advance(p);
        t = peek(p);
        if (t && t->kind == TOKEN_RBRACKET) {
            /* []T 切片类型 */
            advance(p);
            ASTType *inner = parse_type_name(p);
            if (!inner) return NULL;
            ASTType *ty = (ASTType *)malloc(sizeof(ASTType));
            if (!ty) {
                ast_type_free(inner);
                fprintf(stderr, "parse: out of memory\n");
                return NULL;
            }
            ty->kind = AST_TYPE_SLICE;
            ty->name = NULL;
            ty->elem_type = inner;
            ty->array_size = 0;
            return ty;
        }
        if (!t || t->kind != TOKEN_INT) {
            fail(p, "expected array size (integer literal) in [N]T or ] for []T");
            return NULL;
        }
        int size = t->value.int_val;
        if (size <= 0) {
            fail(p, "array size must be positive");
            return NULL;
        }
        advance(p);
        if (peek(p)->kind != TOKEN_RBRACKET) {
            fail(p, "expected ']' after array size in [N]T");
            return NULL;
        }
        advance(p);
        ASTType *inner = parse_type_name(p);
        if (!inner) return NULL;
        ASTType *ty = (ASTType *)malloc(sizeof(ASTType));
        if (!ty) {
            ast_type_free(inner);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        ty->kind = AST_TYPE_ARRAY;
        ty->name = NULL;
        ty->elem_type = inner;
        ty->array_size = size;
        return ty;
    }
    ASTType *ty = (ASTType *)malloc(sizeof(ASTType));
    if (!ty) {
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    ty->name = NULL;
    ty->elem_type = NULL;
    ty->array_size = 0;
    switch (t->kind) {
        case TOKEN_I32:
            ty->kind = AST_TYPE_I32;
            advance(p);
            return ty;
        case TOKEN_BOOL:
            ty->kind = AST_TYPE_BOOL;
            advance(p);
            return ty;
        case TOKEN_U8:
            ty->kind = AST_TYPE_U8;
            advance(p);
            return ty;
        case TOKEN_U32:
            ty->kind = AST_TYPE_U32;
            advance(p);
            return ty;
        case TOKEN_U64:
            ty->kind = AST_TYPE_U64;
            advance(p);
            return ty;
        case TOKEN_I64:
            ty->kind = AST_TYPE_I64;
            advance(p);
            return ty;
        case TOKEN_USIZE:
            ty->kind = AST_TYPE_USIZE;
            advance(p);
            return ty;
        case TOKEN_ISIZE:
            ty->kind = AST_TYPE_ISIZE;
            advance(p);
            return ty;
        case TOKEN_IDENT:
            if (t->ident_len > 0 && t->value.ident) {
                ty->kind = AST_TYPE_NAMED;
                ty->name = strndup(t->value.ident, (size_t)t->ident_len);
                advance(p);
                if (!ty->name) {
                    free(ty);
                    fprintf(stderr, "parse: out of memory\n");
                    return NULL;
                }
                return ty;
            }
            /* fallthrough */
        default:
            free(ty);
            fail(p, "expected type name");
            return NULL;
    }
}

/**
 * 解析 if 条件表达式：if ( expr ) { expr } else { expr }；条件须带括号（C/Java 风格）。
 * 参数：p 解析器状态；当前 Token 须为 IF。返回值：成功返回 AST_EXPR_IF；失败返回 NULL。
 */
static ASTExpr *parse_if_expr(Parser *p) {
    if (peek(p)->kind != TOKEN_IF) return NULL;
    advance(p);
    if (peek(p)->kind != TOKEN_LPAREN) {
        fail(p, "expected '(' after 'if'");
        return NULL;
    }
    advance(p);
    ASTExpr *cond = parse_expr(p);
    if (!cond) return NULL;
    if (peek(p)->kind != TOKEN_RPAREN) {
        ast_expr_free(cond);
        fail(p, "expected ')' after if condition");
        return NULL;
    }
    advance(p);
    if (peek(p)->kind != TOKEN_LBRACE) {
        ast_expr_free(cond);
        fail(p, "expected '{' after if condition");
        return NULL;
    }
    advance(p);
    ASTExpr *then_expr = parse_expr(p);
    if (!then_expr) {
        ast_expr_free(cond);
        return NULL;
    }
    if (peek(p)->kind != TOKEN_RBRACE) {
        ast_expr_free(cond);
        ast_expr_free(then_expr);
        fail(p, "expected '}' after if body");
        return NULL;
    }
    advance(p);
    /* else 后可为 else if cond { block } 或 else { block }，实现链式条件 */
    ASTExpr *else_expr = NULL;
    if (peek(p)->kind == TOKEN_ELSE) {
        advance(p);
        if (peek(p)->kind == TOKEN_IF) {
            /* else if cond { then } [ else ... ]：递归解析为嵌套 if 表达式 */
            else_expr = parse_if_expr(p);
            if (!else_expr) {
                ast_expr_free(cond);
                ast_expr_free(then_expr);
                return NULL;
            }
        } else {
            if (peek(p)->kind != TOKEN_LBRACE) {
                ast_expr_free(cond);
                ast_expr_free(then_expr);
                fail(p, "expected '{' or 'if' after else");
                return NULL;
            }
            advance(p);
            else_expr = parse_expr(p);
            if (!else_expr) {
                ast_expr_free(cond);
                ast_expr_free(then_expr);
                return NULL;
            }
            if (peek(p)->kind != TOKEN_RBRACE) {
                ast_expr_free(cond);
                ast_expr_free(then_expr);
                ast_expr_free(else_expr);
                fail(p, "expected '}' after else body");
                return NULL;
            }
            advance(p);
        }
    }
    ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
    if (!e) {
        ast_expr_free(cond);
        ast_expr_free(then_expr);
        ast_expr_free(else_expr);
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    e->kind = AST_EXPR_IF;
    e->value.if_expr.cond = cond;
    e->value.if_expr.then_expr = then_expr;
    e->value.if_expr.else_expr = else_expr;
    return e;
}

/**
 * 解析主表达式（primary）：整数字面量、括号 ( expr )、if/break/continue、或标识符引用。
 * 参数：p 解析器状态。返回值：成功返回新分配的 ASTExpr*；失败返回 NULL 且已通过 fail 报错。
 */
static ASTExpr *parse_primary(Parser *p) {
    const Token *t = peek(p);
    /* break/continue 仅允许出现在循环体 final_expr 中，由 typeck 校验 */
    if (t->kind == TOKEN_BREAK) {
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) { fprintf(stderr, "parse: out of memory\n"); return NULL; }
        e->kind = AST_EXPR_BREAK;
        return e;
    }
    if (t->kind == TOKEN_CONTINUE) {
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) { fprintf(stderr, "parse: out of memory\n"); return NULL; }
        e->kind = AST_EXPR_CONTINUE;
        return e;
    }
    /* return expr：显式返回，仅允许在函数体内，由 typeck 校验 */
    if (t->kind == TOKEN_RETURN) {
        advance(p);
        ASTExpr *val = parse_expr(p);
        if (!val) return NULL;
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) { ast_expr_free(val); fprintf(stderr, "parse: out of memory\n"); return NULL; }
        e->kind = AST_EXPR_RETURN;
        e->value.unary.operand = val;
        return e;
    }
    /* panic 或 panic(expr)：终止程序，可选消息表达式；panic() 无参合法 */
    if (t->kind == TOKEN_PANIC) {
        advance(p);
        ASTExpr *operand = NULL;
        if (peek(p)->kind == TOKEN_LPAREN) {
            advance(p);
            if (peek(p)->kind == TOKEN_RPAREN) {
                advance(p);  /* panic() 无参 */
            } else {
                operand = parse_expr(p);
                if (!operand) return NULL;
                if (peek(p)->kind != TOKEN_RPAREN) {
                    ast_expr_free(operand);
                    fail(p, "expected ')' after panic(expr)");
                    return NULL;
                }
                advance(p);
            }
        }
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) { ast_expr_free(operand); fprintf(stderr, "parse: out of memory\n"); return NULL; }
        e->kind = AST_EXPR_PANIC;
        e->value.unary.operand = operand;
        return e;
    }
    /* match expr { lit|_ => expr ; ... }：最小形式仅整数字面量与 _ */
    if (t->kind == TOKEN_MATCH) {
        advance(p);
        ASTExpr *matched = parse_expr(p);
        if (!matched) return NULL;
        if (peek(p)->kind != TOKEN_LBRACE) {
            ast_expr_free(matched);
            fail(p, "expected '{' after match expr");
            return NULL;
        }
        advance(p);
        ASTMatchArm *arms = (ASTMatchArm *)malloc(16 * sizeof(ASTMatchArm));
        if (!arms) {
            ast_expr_free(matched);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        int num_arms = 0;
        int cap = 16;
        for (;;) {
            if (peek(p)->kind == TOKEN_RBRACE) break;
            if (num_arms >= cap) {
                ASTMatchArm *n = (ASTMatchArm *)realloc(arms, (size_t)(cap *= 2) * sizeof(ASTMatchArm));
                if (!n) {
                    while (num_arms--) ast_expr_free(arms[num_arms].result);
                    free(arms);
                    ast_expr_free(matched);
                    return NULL;
                }
                arms = n;
            }
            if (peek(p)->kind == TOKEN_INT) {
                arms[num_arms].is_wildcard = 0;
                arms[num_arms].lit_val = peek(p)->value.int_val;
                advance(p);
            } else if (peek(p)->kind == TOKEN_UNDERSCORE) {
                arms[num_arms].is_wildcard = 1;
                arms[num_arms].lit_val = 0;
                advance(p);
            } else {
                while (num_arms--) ast_expr_free(arms[num_arms].result);
                free(arms);
                ast_expr_free(matched);
                fail(p, "expected integer literal or '_' in match arm");
                return NULL;
            }
            if (peek(p)->kind != TOKEN_FATARROW) {
                while (num_arms--) ast_expr_free(arms[num_arms].result);
                free(arms);
                ast_expr_free(matched);
                fail(p, "expected '=>' in match arm");
                return NULL;
            }
            advance(p);
            arms[num_arms].result = parse_expr(p);
            if (!arms[num_arms].result) {
                while (num_arms--) ast_expr_free(arms[num_arms].result);
                free(arms);
                ast_expr_free(matched);
                return NULL;
            }
            num_arms++;
            if (peek(p)->kind == TOKEN_SEMICOLON) advance(p);
        }
        if (peek(p)->kind != TOKEN_RBRACE) {
            while (num_arms--) ast_expr_free(arms[num_arms].result);
            free(arms);
            ast_expr_free(matched);
            fail(p, "expected '}' to close match");
            return NULL;
        }
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            while (num_arms--) ast_expr_free(arms[num_arms].result);
            free(arms);
            ast_expr_free(matched);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_MATCH;
        e->value.match_expr.matched_expr = matched;
        e->value.match_expr.arms = arms;
        e->value.match_expr.num_arms = num_arms;
        return e;
    }
    /* 数组字面量 [e1, e2, ...]（文档 §6.2）；表达式语境下 [ 即数组字面量 */
    if (t->kind == TOKEN_LBRACKET) {
        advance(p);
        ASTExpr **elems = (ASTExpr **)malloc(32 * sizeof(ASTExpr *));
        if (!elems) { fprintf(stderr, "parse: out of memory\n"); return NULL; }
        int num_elems = 0, cap = 32;
        if (peek(p)->kind != TOKEN_RBRACKET) {
            for (;;) {
                if (num_elems >= cap) {
                    ASTExpr **n = (ASTExpr **)realloc(elems, (size_t)(cap *= 2) * sizeof(ASTExpr *));
                    if (!n) {
                        while (num_elems--) ast_expr_free(elems[num_elems]);
                        free(elems);
                        return NULL;
                    }
                    elems = n;
                }
                ASTExpr *e = parse_expr(p);
                if (!e) {
                    while (num_elems--) ast_expr_free(elems[num_elems]);
                    free(elems);
                    return NULL;
                }
                elems[num_elems++] = e;
                if (peek(p)->kind == TOKEN_COMMA) {
                    advance(p);
                    continue;
                }
                break;
            }
        }
        if (peek(p)->kind != TOKEN_RBRACKET) {
            while (num_elems--) ast_expr_free(elems[num_elems]);
            free(elems);
            fail(p, "expected ']' to close array literal");
            return NULL;
        }
        advance(p);
        ASTExpr *arr = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!arr) {
            while (num_elems--) ast_expr_free(elems[num_elems]);
            free(elems);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        arr->kind = AST_EXPR_ARRAY_LIT;
        arr->value.array_lit.elems = elems;
        arr->value.array_lit.num_elems = num_elems;
        return arr;
    }
    if (t->kind == TOKEN_IF) {
        return parse_if_expr(p);
    }
    if (t->kind == TOKEN_LPAREN) {
        advance(p);
        ASTExpr *e = parse_expr(p);
        if (!e) return NULL;
        if (peek(p)->kind != TOKEN_RPAREN) {
            ast_expr_free(e);
            fail(p, "expected ')'");
            return NULL;
        }
        advance(p);
        return e;
    }
    /* 变量/常量引用（标识符）或结构体字面量 TypeName { field: expr, ... } */
    if (t->kind == TOKEN_IDENT) {
        char *name = t->ident_len > 0 && t->value.ident
            ? strndup(t->value.ident, (size_t)t->ident_len) : NULL;
        advance(p);
        if (!name) {
            fail(p, "invalid identifier");
            return NULL;
        }
        /* 仅当首字母大写（类型名约定）且下一 token 为 { 时解析为结构体字面量，避免 if ok { } 中的 ok 被误判 */
        if (peek(p)->kind == TOKEN_LBRACE && name[0] >= 'A' && name[0] <= 'Z') {
            advance(p);
            char **fnames = (char **)malloc((size_t)MAX_STRUCT_FIELDS * sizeof(char *));
            ASTExpr **inits = (ASTExpr **)malloc((size_t)MAX_STRUCT_FIELDS * sizeof(ASTExpr *));
            if (!fnames || !inits) {
                free(name);
                if (fnames) free(fnames);
                if (inits) free(inits);
                fprintf(stderr, "parse: out of memory\n");
                return NULL;
            }
            int nf = 0;
            while (peek(p)->kind != TOKEN_RBRACE) {
                if (nf >= MAX_STRUCT_FIELDS) {
                    free(name);
                    for (int i = 0; i < nf; i++) {
                        free((void *)fnames[i]);
                        ast_expr_free(inits[i]);
                    }
                    free(fnames);
                    free(inits);
                    fail(p, "too many struct literal fields");
                    return NULL;
                }
                if (peek(p)->kind != TOKEN_IDENT) {
                    free(name);
                    for (int i = 0; i < nf; i++) {
                        free((void *)fnames[i]);
                        ast_expr_free(inits[i]);
                    }
                    free(fnames);
                    free(inits);
                    fail(p, "expected field name in struct literal");
                    return NULL;
                }
                fnames[nf] = strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len);
                if (!fnames[nf]) {
                    free(name);
                    for (int i = 0; i < nf; i++) {
                        free((void *)fnames[i]);
                        ast_expr_free(inits[i]);
                    }
                    free(fnames);
                    free(inits);
                    fprintf(stderr, "parse: out of memory\n");
                    return NULL;
                }
                advance(p);
                if (peek(p)->kind != TOKEN_COLON) {
                    free((void *)fnames[nf]);
                    free(name);
                    for (int i = 0; i < nf; i++) {
                        free((void *)fnames[i]);
                        ast_expr_free(inits[i]);
                    }
                    free(fnames);
                    free(inits);
                    fail(p, "expected ':' after field name in struct literal");
                    return NULL;
                }
                advance(p);
                inits[nf] = parse_expr(p);
                if (!inits[nf]) {
                    free((void *)fnames[nf]);
                    free(name);
                    for (int i = 0; i < nf; i++) {
                        free((void *)fnames[i]);
                        ast_expr_free(inits[i]);
                    }
                    free(fnames);
                    free(inits);
                    return NULL;
                }
                nf++;
                if (peek(p)->kind == TOKEN_COMMA) advance(p);
            }
            if (peek(p)->kind != TOKEN_RBRACE) {
                free(name);
                for (int i = 0; i < nf; i++) {
                    free((void *)fnames[i]);
                    ast_expr_free(inits[i]);
                }
                free(fnames);
                free(inits);
                fail(p, "expected '}' in struct literal");
                return NULL;
            }
            advance(p);
            ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
            if (!e) {
                free(name);
                for (int i = 0; i < nf; i++) {
                    free((void *)fnames[i]);
                    ast_expr_free(inits[i]);
                }
                free(fnames);
                free(inits);
                fprintf(stderr, "parse: out of memory\n");
                return NULL;
            }
            e->kind = AST_EXPR_STRUCT_LIT;
            e->value.struct_lit.struct_name = name;
            e->value.struct_lit.field_names = fnames;
            e->value.struct_lit.inits = inits;
            e->value.struct_lit.num_fields = nf;
            return e;
        }
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            free(name);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_VAR;
        e->value.var.name = name;
        return e;
    }
    if (t->kind == TOKEN_TRUE) {
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_BOOL_LIT;
        e->value.int_val = 1;
        return e;
    }
    if (t->kind == TOKEN_FALSE) {
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_BOOL_LIT;
        e->value.int_val = 0;
        return e;
    }
    if (t->kind != TOKEN_INT) {
        fail(p, "expected integer literal, identifier, 'true', 'false', 'if', 'break', 'continue', 'return', 'panic', 'match', or '('");
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
 * 解析后缀表达式：primary 后接零个或多个 . field，得到 base.field 链。
 * 参数：p 解析器状态。返回值：成功返回 ASTExpr*；失败返回 NULL。
 */
static ASTExpr *parse_postfix(Parser *p) {
    ASTExpr *left = parse_primary(p);
    if (!left) return NULL;
    while (peek(p)->kind == TOKEN_DOT) {
        advance(p);
        if (peek(p)->kind != TOKEN_IDENT) {
            ast_expr_free(left);
            fail(p, "expected field name after '.'");
            return NULL;
        }
        char *field_name = strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len);
        if (!field_name) {
            ast_expr_free(left);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            ast_expr_free(left);
            free(field_name);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_FIELD_ACCESS;
        e->value.field_access.base = left;
        e->value.field_access.field_name = field_name;
        left = e;
    }
    /* 下标访问 base[index]（文档 §6.2） */
    while (peek(p)->kind == TOKEN_LBRACKET) {
        advance(p);
        ASTExpr *idx = parse_expr(p);
        if (!idx) {
            ast_expr_free(left);
            return NULL;
        }
        if (peek(p)->kind != TOKEN_RBRACKET) {
            ast_expr_free(left);
            ast_expr_free(idx);
            fail(p, "expected ']' after array index");
            return NULL;
        }
        advance(p);
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            ast_expr_free(left);
            ast_expr_free(idx);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = AST_EXPR_INDEX;
        e->value.index.base = left;
        e->value.index.index_expr = idx;
        e->value.index.base_is_slice = 0;  /* typeck 会设为 1 当基类型为切片 */
        left = e;
    }
    return left;
}

/**
 * 解析一元表达式（unary）：可选前缀 - ~ ! 后接 unary；否则 postfix（含 primary 与 .field）。支持 -x、~a、!b、p.x。
 * 参数：p 解析器状态。返回值：成功返回 ASTExpr*；失败返回 NULL。副作用：成功时 advance。
 */
static ASTExpr *parse_unary(Parser *p) {
    TokenKind k = peek(p)->kind;
    if (k == TOKEN_MINUS || k == TOKEN_TILDE || k == TOKEN_BANG) {
        advance(p);
        ASTExpr *inner = parse_unary(p);
        if (!inner) return NULL;
        ASTExpr *e = (ASTExpr *)malloc(sizeof(ASTExpr));
        if (!e) {
            ast_expr_free(inner);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        e->kind = (k == TOKEN_MINUS) ? AST_EXPR_NEG : (k == TOKEN_TILDE) ? AST_EXPR_BITNOT : AST_EXPR_LOGNOT;
        e->value.unary.operand = inner;
        return e;
    }
    return parse_postfix(p);
}

/**
 * 解析项（term）：unary 后接零个或多个 (STAR|SLASH unary)，左结合；乘除优先于加减。
 * 参数：p 解析器状态。返回值：成功返回 ASTExpr*；失败返回 NULL。副作用：成功时 advance。
 */
static ASTExpr *parse_term(Parser *p) {
    ASTExpr *left = parse_unary(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        if (t->kind != TOKEN_STAR && t->kind != TOKEN_SLASH && t->kind != TOKEN_PERCENT)
            return left;
        int op = t->kind;
        advance(p);
        ASTExpr *right = parse_unary(p);
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
        bin->kind = (op == TOKEN_STAR) ? AST_EXPR_MUL : (op == TOKEN_SLASH) ? AST_EXPR_DIV : AST_EXPR_MOD;
        bin->value.binop.left = left;
        bin->value.binop.right = right;
        left = bin;
    }
}

/** 辅助：用 left、right 与 kind 构建二元节点，失败时释放 left/right 并返回 NULL */
static ASTExpr *parse_binop_right(Parser *p, ASTExpr *left, ASTExpr *right, int op, ASTExprKind kind) {
    (void)p;
    (void)op;
    ASTExpr *bin = (ASTExpr *)malloc(sizeof(ASTExpr));
    if (!bin) {
        ast_expr_free(left);
        ast_expr_free(right);
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    bin->kind = kind;
    bin->value.binop.left = left;
    bin->value.binop.right = right;
    return bin;
}

/** 加减：term (PLUS|MINUS term)* */
static ASTExpr *parse_addsub(Parser *p) {
    ASTExpr *left = parse_term(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        if (t->kind != TOKEN_PLUS && t->kind != TOKEN_MINUS) return left;
        int op = t->kind;
        advance(p);
        ASTExpr *right = parse_term(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, op, (op == TOKEN_PLUS) ? AST_EXPR_ADD : AST_EXPR_SUB);
        if (!left) return NULL;
    }
}

/** 移位：addsub (LSHIFT|RSHIFT addsub)* */
static ASTExpr *parse_shift(Parser *p) {
    ASTExpr *left = parse_addsub(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        if (t->kind != TOKEN_LSHIFT && t->kind != TOKEN_RSHIFT) return left;
        int op = t->kind;
        advance(p);
        ASTExpr *right = parse_addsub(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, op, (op == TOKEN_LSHIFT) ? AST_EXPR_SHL : AST_EXPR_SHR);
        if (!left) return NULL;
    }
}

/** 比较：shift (LT|LE|GT|GE shift)* */
static ASTExpr *parse_compare(Parser *p) {
    ASTExpr *left = parse_shift(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        ASTExprKind k;
        if (t->kind == TOKEN_LT) k = AST_EXPR_LT;
        else if (t->kind == TOKEN_LE) k = AST_EXPR_LE;
        else if (t->kind == TOKEN_GT) k = AST_EXPR_GT;
        else if (t->kind == TOKEN_GE) k = AST_EXPR_GE;
        else return left;
        advance(p);
        ASTExpr *right = parse_shift(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, 0, k);
        if (!left) return NULL;
    }
}

/** 相等：compare (EQ|NE compare)* */
static ASTExpr *parse_eq(Parser *p) {
    ASTExpr *left = parse_compare(p);
    if (!left) return NULL;
    for (;;) {
        const Token *t = peek(p);
        if (t->kind != TOKEN_EQ && t->kind != TOKEN_NE) return left;
        int op = t->kind;
        advance(p);
        ASTExpr *right = parse_compare(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, op, (op == TOKEN_EQ) ? AST_EXPR_EQ : AST_EXPR_NE);
        if (!left) return NULL;
    }
}

/** 按位与：eq (AMP eq)* */
static ASTExpr *parse_bitand(Parser *p) {
    ASTExpr *left = parse_eq(p);
    if (!left) return NULL;
    for (;;) {
        if (peek(p)->kind != TOKEN_AMP) return left;
        advance(p);
        ASTExpr *right = parse_eq(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, TOKEN_AMP, AST_EXPR_BITAND);
        if (!left) return NULL;
    }
}

/** 按位异或：bitand (CARET bitand)* */
static ASTExpr *parse_bitxor(Parser *p) {
    ASTExpr *left = parse_bitand(p);
    if (!left) return NULL;
    for (;;) {
        if (peek(p)->kind != TOKEN_CARET) return left;
        advance(p);
        ASTExpr *right = parse_bitand(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, TOKEN_CARET, AST_EXPR_BITXOR);
        if (!left) return NULL;
    }
}

/** 按位或：bitxor (PIPE bitxor)* */
static ASTExpr *parse_bitor(Parser *p) {
    ASTExpr *left = parse_bitxor(p);
    if (!left) return NULL;
    for (;;) {
        if (peek(p)->kind != TOKEN_PIPE) return left;
        advance(p);
        ASTExpr *right = parse_bitxor(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, TOKEN_PIPE, AST_EXPR_BITOR);
        if (!left) return NULL;
    }
}

/** 逻辑与：bitor (AMPAMP bitor)* */
static ASTExpr *parse_logand(Parser *p) {
    ASTExpr *left = parse_bitor(p);
    if (!left) return NULL;
    for (;;) {
        if (peek(p)->kind != TOKEN_AMPAMP) return left;
        advance(p);
        ASTExpr *right = parse_bitor(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, TOKEN_AMPAMP, AST_EXPR_LOGAND);
        if (!left) return NULL;
    }
}

/** 逻辑或：logand (PIPEPIPE logand)*，为表达式顶层 */
static ASTExpr *parse_logor(Parser *p) {
    ASTExpr *left = parse_logand(p);
    if (!left) return NULL;
    for (;;) {
        if (peek(p)->kind != TOKEN_PIPEPIPE) return left;
        advance(p);
        ASTExpr *right = parse_logand(p);
        if (!right) { ast_expr_free(left); return NULL; }
        left = parse_binop_right(p, left, right, TOKEN_PIPEPIPE, AST_EXPR_LOGOR);
        if (!left) return NULL;
    }
}

/**
 * 解析表达式（入口）；即逻辑或层，支持全运算符与括号。
 * 参数：p 解析器状态。返回值：成功返回 ASTExpr*；失败返回 NULL。副作用：成功时 advance。
 */
static ASTExpr *parse_expr(Parser *p) {
    return parse_logor(p);
}

/** 最大 import 数量 */
#define MAX_IMPORTS 32
/** 顶层最大 struct 定义数 */
#define MAX_STRUCTS 16
/** 单 struct 定义最大字段数（parse_one_struct 用） */
#define MAX_STRUCT_FIELDS_DEF 32
/** 块内最大 const/let 声明数 */
#define MAX_CONST_DECLS 32
#define MAX_LET_DECLS 32
/** 块内最大 while 循环数 */
#define MAX_WHILE_LOOPS 32
#define MAX_FOR_LOOPS 32
#define MAX_DEFERS 16
#define MAX_LABELED_STMTS 32

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

/**
 * 解析单条结构体定义：struct Name { field : Type ; ... }。
 * 参数：p 解析器状态；当前 Token 须为 TOKEN_STRUCT。返回值：成功返回新分配的 ASTStructDef*（调用方须通过 ast_struct_def_free 释放）；失败返回 NULL 且已 fail。
 */
static ASTStructDef *parse_one_struct(Parser *p) {
    if (peek(p)->kind != TOKEN_STRUCT) return NULL;
    advance(p);
    if (peek(p)->kind != TOKEN_IDENT) {
        fail(p, "expected struct name after 'struct'");
        return NULL;
    }
    char *name = strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len);
    if (!name) {
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    advance(p);
    if (peek(p)->kind != TOKEN_LBRACE) {
        free(name);
        fail(p, "expected '{' after struct name");
        return NULL;
    }
    advance(p);
    ASTStructField *fields = (ASTStructField *)malloc((size_t)MAX_STRUCT_FIELDS * sizeof(ASTStructField));
    if (!fields) {
        free(name);
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    int num_fields = 0;
    while (peek(p)->kind != TOKEN_RBRACE) {
        if (num_fields >= MAX_STRUCT_FIELDS_DEF) {
            free(name);
            for (int i = 0; i < num_fields; i++) {
                free((void *)fields[i].name);
                ast_type_free(fields[i].type);
            }
            free(fields);
            fail(p, "too many struct fields");
            return NULL;
        }
        if (peek(p)->kind != TOKEN_IDENT) {
            free(name);
            for (int i = 0; i < num_fields; i++) {
                free((void *)fields[i].name);
                ast_type_free(fields[i].type);
            }
            free(fields);
            fail(p, "expected field name in struct");
            return NULL;
        }
        char *fname = strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len);
        if (!fname) {
            free(name);
            for (int i = 0; i < num_fields; i++) {
                free((void *)fields[i].name);
                ast_type_free(fields[i].type);
            }
            free(fields);
            fprintf(stderr, "parse: out of memory\n");
            return NULL;
        }
        advance(p);
        if (peek(p)->kind != TOKEN_COLON) {
            free(fname);
            free(name);
            for (int i = 0; i < num_fields; i++) {
                free((void *)fields[i].name);
                ast_type_free(fields[i].type);
            }
            free(fields);
            fail(p, "expected ':' after field name");
            return NULL;
        }
        advance(p);
        ASTType *ty = parse_type_name(p);
        if (!ty) {
            free(fname);
            free(name);
            for (int i = 0; i < num_fields; i++) {
                free((void *)fields[i].name);
                ast_type_free(fields[i].type);
            }
            free(fields);
            return NULL;
        }
        fields[num_fields].name = fname;
        fields[num_fields].type = ty;
        num_fields++;
        if (peek(p)->kind == TOKEN_SEMICOLON) advance(p);
    }
    advance(p); /* consume RBRACE */
    ASTStructDef *s = (ASTStructDef *)malloc(sizeof(ASTStructDef));
    if (!s) {
        free(name);
        for (int i = 0; i < num_fields; i++) {
            free((void *)fields[i].name);
            ast_type_free(fields[i].type);
        }
        free(fields);
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    s->name = name;
    s->fields = fields;
    s->num_fields = num_fields;
    return s;
}

/**
 * 解析块体：(const|let)* (while 条件 { 块 })* 最终表达式；可选是否解析 while 及结尾 }。
 * 参数：p 解析器状态；allow_while 1 表示解析 while 并在最后消耗 RBRACE，0 表示仅 (const|let)* expr（用于 while 体）。返回值：成功返回 ASTBlock*；失败返回 NULL。
 */
static ASTBlock *parse_block(Parser *p, int allow_while) {
    ASTBlock *b = (ASTBlock *)malloc(sizeof(ASTBlock));
    if (!b) {
        fprintf(stderr, "parse: out of memory\n");
        return NULL;
    }
    b->const_decls = (ASTConstDecl *)malloc((size_t)MAX_CONST_DECLS * sizeof(ASTConstDecl));
    b->let_decls = (ASTLetDecl *)malloc((size_t)MAX_LET_DECLS * sizeof(ASTLetDecl));
    b->loops = NULL;
    b->num_loops = 0;
    b->for_loops = NULL;
    b->num_for_loops = 0;
    b->defer_blocks = NULL;
    b->num_defers = 0;
    b->labeled_stmts = NULL;
    b->num_labeled_stmts = 0;
    b->final_expr = NULL;
    if (!b->const_decls || !b->let_decls) {
        if (b->const_decls) free(b->const_decls);
        if (b->let_decls) free(b->let_decls);
        free(b);
        return NULL;
    }
    for (;;) {
        if (peek(p)->kind == TOKEN_CONST) {
            if (b->num_consts >= MAX_CONST_DECLS) {
                fail(p, "too many const declarations");
                ast_block_free(b);
                return NULL;
            }
            advance(p);
            if (peek(p)->kind != TOKEN_IDENT && peek(p)->kind != TOKEN_I32) {
                fail(p, "expected identifier after const");
                ast_block_free(b);
                return NULL;
            }
            char *name = (peek(p)->ident_len > 0 && peek(p)->value.ident)
                ? strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len)
                : (peek(p)->kind == TOKEN_I32 ? strdup("i32") : NULL);
            advance(p);
            if (!name) {
                ast_block_free(b);
                return NULL;
            }
            ASTType *type = NULL;
        if (peek(p)->kind == TOKEN_COLON) {
                advance(p);
                type = parse_type_name(p);
                if (!type) {
                free(name);
                ast_block_free(b);
                return NULL;
            }
        }
            if (peek(p)->kind != TOKEN_ASSIGN) {
                free(name);
                if (type) free((void *)type);
                fail(p, "expected '=' in const");
                ast_block_free(b);
                return NULL;
            }
            advance(p);
            ASTExpr *init = parse_expr(p);
            if (!init) {
                free(name);
                if (type) free((void *)type);
                ast_block_free(b);
                return NULL;
            }
            /* 分号可选：若下一 token 为 } 或下一句开头（const/let/while/for 等）则可不写分号（类 TS） */
            if (peek(p)->kind == TOKEN_SEMICOLON)
                advance(p);
            else if (peek(p)->kind != TOKEN_RBRACE && peek(p)->kind != TOKEN_CONST && peek(p)->kind != TOKEN_LET
                     && peek(p)->kind != TOKEN_WHILE && peek(p)->kind != TOKEN_LOOP && peek(p)->kind != TOKEN_FOR
                     && peek(p)->kind != TOKEN_DEFER && peek(p)->kind != TOKEN_IF) {
                free(name);
                if (type) free((void *)type);
                ast_expr_free(init);
                fail(p, "expected ';' after const init (or close block '}')");
                ast_block_free(b);
                return NULL;
            }
            b->const_decls[b->num_consts].name = name;
            b->const_decls[b->num_consts].type = type;
            b->const_decls[b->num_consts].init = init;
            b->num_consts++;
        } else if (peek(p)->kind == TOKEN_LET) {
            if (b->num_lets >= MAX_LET_DECLS) {
                fail(p, "too many let declarations");
                ast_block_free(b);
                return NULL;
            }
            advance(p);
            if (peek(p)->kind != TOKEN_IDENT) {
                fail(p, "expected identifier after let");
                ast_block_free(b);
                return NULL;
            }
            char *name = (peek(p)->ident_len > 0 && peek(p)->value.ident)
                ? strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len) : NULL;
            advance(p);
            if (!name) {
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind != TOKEN_COLON) {
                free(name);
                fail(p, "expected ':' and type in let");
                ast_block_free(b);
                return NULL;
            }
            advance(p);
            ASTType *type = parse_type_name(p);
            if (!type) {
                free(name);
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind != TOKEN_ASSIGN) {
                free(name);
                free((void *)type);
                fail(p, "expected '=' in let");
                ast_block_free(b);
                return NULL;
            }
            advance(p);
            ASTExpr *init = parse_expr(p);
            if (!init) {
                free(name);
                free((void *)type);
                ast_block_free(b);
                return NULL;
            }
            /* 分号可选：若下一 token 为 } 或下一句开头则可不写分号（类 TS，} 后不必写 ;） */
            if (peek(p)->kind == TOKEN_SEMICOLON)
                advance(p);
            else if (peek(p)->kind != TOKEN_RBRACE && peek(p)->kind != TOKEN_CONST && peek(p)->kind != TOKEN_LET
                     && peek(p)->kind != TOKEN_WHILE && peek(p)->kind != TOKEN_LOOP && peek(p)->kind != TOKEN_FOR
                     && peek(p)->kind != TOKEN_DEFER && peek(p)->kind != TOKEN_IF) {
                free(name);
                free((void *)type);
                ast_expr_free(init);
                fail(p, "expected ';' after let init (or close block '}')");
                ast_block_free(b);
                return NULL;
            }
            b->let_decls[b->num_lets].name = name;
            b->let_decls[b->num_lets].type = type;
            b->let_decls[b->num_lets].init = init;
            b->num_lets++;
        } else
            break;
    }
    /* 可选：解析 while 条件 { 块 } 或 loop { 块 }（loop 等价 while 1） */
    if (allow_while) {
        while (peek(p)->kind == TOKEN_WHILE || peek(p)->kind == TOKEN_LOOP) {
            if (b->num_loops >= MAX_WHILE_LOOPS) {
                fail(p, "too many while/loop");
                ast_block_free(b);
                return NULL;
            }
            if (!b->loops) {
                b->loops = (ASTWhileLoop *)malloc((size_t)MAX_WHILE_LOOPS * sizeof(ASTWhileLoop));
                if (!b->loops) {
                    ast_block_free(b);
                    return NULL;
                }
            }
            int is_loop = (peek(p)->kind == TOKEN_LOOP);
            advance(p);
            ASTExpr *cond;
            if (is_loop) {
                /* loop { body }：条件恒为 1 */
                if (peek(p)->kind != TOKEN_LBRACE) {
                    ast_block_free(b);
                    fail(p, "expected '{' after loop");
                    return NULL;
                }
                cond = (ASTExpr *)malloc(sizeof(ASTExpr));
                if (!cond) {
                    ast_block_free(b);
                    fprintf(stderr, "parse: out of memory\n");
                    return NULL;
                }
                cond->kind = AST_EXPR_BOOL_LIT;  /* loop 等价 while true */
                cond->value.int_val = 1;
            } else {
                /* while ( cond ) { body }：条件必须用括号包裹，可读性更好 */
                if (peek(p)->kind != TOKEN_LPAREN) {
                    ast_block_free(b);
                    fail(p, "expected '(' after while");
                    return NULL;
                }
                advance(p);
                cond = parse_expr(p);
                if (!cond) {
                    ast_block_free(b);
                    return NULL;
                }
                if (peek(p)->kind != TOKEN_RPAREN) {
                    ast_expr_free(cond);
                    ast_block_free(b);
                    fail(p, "expected ')' after while condition");
                    return NULL;
                }
                advance(p);
                if (peek(p)->kind != TOKEN_LBRACE) {
                    ast_expr_free(cond);
                    ast_block_free(b);
                    fail(p, "expected '{' after while (cond)");
                    return NULL;
                }
            }
            advance(p);
            ASTBlock *body = parse_block(p, 0);  /* 体不包含嵌套 while/loop，不消耗 } */
            if (!body) {
                ast_expr_free(cond);
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind != TOKEN_RBRACE) {
                ast_expr_free(cond);
                ast_block_free(body);
                ast_block_free(b);
                fail(p, "expected '}' after loop/while body");
                return NULL;
            }
            advance(p);
            b->loops[b->num_loops].cond = cond;
            b->loops[b->num_loops].body = body;
            b->num_loops++;
        }
        /* 解析 for ( [init]; [cond]; [step] ) { body } */
        while (allow_while && peek(p)->kind == TOKEN_FOR) {
            if (b->num_for_loops >= MAX_FOR_LOOPS) {
                fail(p, "too many for loops");
                ast_block_free(b);
                return NULL;
            }
            if (!b->for_loops) {
                b->for_loops = (ASTForLoop *)malloc((size_t)MAX_FOR_LOOPS * sizeof(ASTForLoop));
                if (!b->for_loops) {
                    ast_block_free(b);
                    return NULL;
                }
            }
            advance(p);
            if (peek(p)->kind != TOKEN_LPAREN) {
                ast_block_free(b);
                fail(p, "expected '(' after for");
                return NULL;
            }
            advance(p);
            /* init：可选，; 前无表达式则为 NULL */
            ASTExpr *init = NULL;
            if (peek(p)->kind != TOKEN_SEMICOLON) {
                init = parse_expr(p);
                if (!init) { ast_block_free(b); return NULL; }
            }
            if (peek(p)->kind != TOKEN_SEMICOLON) {
                ast_expr_free(init);
                ast_block_free(b);
                fail(p, "expected ';' in for");
                return NULL;
            }
            advance(p);
            /* cond：可选，; 前无表达式则为 NULL（表示恒真） */
            ASTExpr *cond = NULL;
            if (peek(p)->kind != TOKEN_SEMICOLON) {
                cond = parse_expr(p);
                if (!cond) {
                    ast_expr_free(init);
                    ast_block_free(b);
                    return NULL;
                }
            }
            if (peek(p)->kind != TOKEN_SEMICOLON) {
                ast_expr_free(init);
                ast_expr_free(cond);
                ast_block_free(b);
                fail(p, "expected ';' in for");
                return NULL;
            }
            advance(p);
            /* step：可选，) 前无表达式则为 NULL */
            ASTExpr *step = NULL;
            if (peek(p)->kind != TOKEN_RPAREN) {
                step = parse_expr(p);
                if (!step) {
                    ast_expr_free(init);
                    ast_expr_free(cond);
                    ast_block_free(b);
                    return NULL;
                }
            }
            if (peek(p)->kind != TOKEN_RPAREN) {
                ast_expr_free(init);
                ast_expr_free(cond);
                ast_expr_free(step);
                ast_block_free(b);
                fail(p, "expected ')' in for");
                return NULL;
            }
            advance(p);
            if (peek(p)->kind != TOKEN_LBRACE) {
                ast_expr_free(init);
                ast_expr_free(cond);
                ast_expr_free(step);
                ast_block_free(b);
                fail(p, "expected '{' after for");
                return NULL;
            }
            advance(p);
            ASTBlock *body = parse_block(p, 0);
            if (!body) {
                ast_expr_free(init);
                ast_expr_free(cond);
                ast_expr_free(step);
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind != TOKEN_RBRACE) {
                ast_expr_free(init);
                ast_expr_free(cond);
                ast_expr_free(step);
                ast_block_free(body);
                ast_block_free(b);
                fail(p, "expected '}' after for body");
                return NULL;
            }
            advance(p);
            b->for_loops[b->num_for_loops].init = init;
            b->for_loops[b->num_for_loops].cond = cond;
            b->for_loops[b->num_for_loops].step = step;
            b->for_loops[b->num_for_loops].body = body;
            b->num_for_loops++;
        }
    }
    /* 解析 defer { block }*：块退出时逆序执行 */
    while (peek(p)->kind == TOKEN_DEFER) {
        if (b->num_defers >= MAX_DEFERS) {
            fail(p, "too many defer blocks");
            ast_block_free(b);
            return NULL;
        }
        advance(p);
        if (peek(p)->kind != TOKEN_LBRACE) {
            ast_block_free(b);
            fail(p, "expected '{' after defer");
            return NULL;
        }
        advance(p);
        ASTBlock *db = parse_block(p, 0);
        if (!db) {
            ast_block_free(b);
            return NULL;
        }
        if (peek(p)->kind != TOKEN_RBRACE) {
            ast_block_free(db);
            ast_block_free(b);
            fail(p, "expected '}' after defer block");
            return NULL;
        }
        advance(p);
        if (!b->defer_blocks) {
            b->defer_blocks = (ASTBlock **)malloc((size_t)MAX_DEFERS * sizeof(ASTBlock *));
            if (!b->defer_blocks) {
                ast_block_free(db);
                ast_block_free(b);
                return NULL;
            }
        }
        b->defer_blocks[b->num_defers++] = db;
    }
    /* 解析 ( [label:] (goto id;|return expr;) )*，然后 final_expr */
    while (1) {
        char *label = NULL;
        if (peek(p)->kind == TOKEN_IDENT && peek_next(p)->kind == TOKEN_COLON) {
            const Token *t = peek(p);
            label = (t->ident_len > 0 && t->value.ident)
                ? strndup(t->value.ident, (size_t)t->ident_len) : NULL;
            advance(p);
            advance(p); /* consume COLON */
            if (!label) {
                ast_block_free(b);
                return NULL;
            }
        }
        if (peek(p)->kind == TOKEN_GOTO) {
            advance(p);
            if (peek(p)->kind != TOKEN_IDENT && peek(p)->kind != TOKEN_I32) {
                if (label) free(label);
                ast_block_free(b);
                fail(p, "expected identifier after goto");
                return NULL;
            }
            char *target = (peek(p)->ident_len > 0 && peek(p)->value.ident)
                ? strndup(peek(p)->value.ident, (size_t)peek(p)->ident_len) : NULL;
            advance(p);
            if (!target) {
                if (label) free(label);
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind == TOKEN_SEMICOLON)
                advance(p);
            else if (peek(p)->kind != TOKEN_RBRACE) {
                free(target);
                if (label) free(label);
                ast_block_free(b);
                fail(p, "expected ';' after goto target (or '}')");
                return NULL;
            }
            if (b->num_labeled_stmts >= MAX_LABELED_STMTS) {
                free(target);
                if (label) free(label);
                fail(p, "too many labeled statements");
                ast_block_free(b);
                return NULL;
            }
            if (!b->labeled_stmts) {
                b->labeled_stmts = (ASTLabeledStmt *)malloc((size_t)MAX_LABELED_STMTS * sizeof(ASTLabeledStmt));
                if (!b->labeled_stmts) {
                    free(target);
                    if (label) free(label);
                    ast_block_free(b);
                    return NULL;
                }
            }
            b->labeled_stmts[b->num_labeled_stmts].label = label;
            b->labeled_stmts[b->num_labeled_stmts].kind = AST_STMT_GOTO;
            b->labeled_stmts[b->num_labeled_stmts].u.goto_target = target;
            b->num_labeled_stmts++;
            continue;
        }
        if (peek(p)->kind == TOKEN_RETURN) {
            advance(p);
            ASTExpr *ret_expr = parse_expr(p);
            if (!ret_expr) {
                if (label) free(label);
                ast_block_free(b);
                return NULL;
            }
            if (peek(p)->kind == TOKEN_SEMICOLON)
                advance(p);
            else if (peek(p)->kind != TOKEN_RBRACE) {
                ast_expr_free(ret_expr);
                if (label) free(label);
                ast_block_free(b);
                fail(p, "expected ';' after return expr (or '}')");
                return NULL;
            }
            if (b->num_labeled_stmts >= MAX_LABELED_STMTS) {
                ast_expr_free(ret_expr);
                if (label) free(label);
                fail(p, "too many labeled statements");
                ast_block_free(b);
                return NULL;
            }
            if (!b->labeled_stmts) {
                b->labeled_stmts = (ASTLabeledStmt *)malloc((size_t)MAX_LABELED_STMTS * sizeof(ASTLabeledStmt));
                if (!b->labeled_stmts) {
                    ast_expr_free(ret_expr);
                    if (label) free(label);
                    ast_block_free(b);
                    return NULL;
                }
            }
            b->labeled_stmts[b->num_labeled_stmts].label = label;
            b->labeled_stmts[b->num_labeled_stmts].kind = AST_STMT_RETURN;
            b->labeled_stmts[b->num_labeled_stmts].u.return_expr = ret_expr;
            b->num_labeled_stmts++;
            continue;
        }
        if (label) free(label);
        break;
    }
    /* 当块以 return/goto 结尾且下一 token 为 } 时，final_expr 可选（无需占位表达式） */
    if (allow_while && peek(p)->kind == TOKEN_RBRACE) {
        b->final_expr = NULL;
    } else {
        b->final_expr = parse_expr(p);
        if (!b->final_expr) {
            ast_block_free(b);
            return NULL;
        }
    }
    if (allow_while && peek(p)->kind != TOKEN_RBRACE) {
        ast_block_free(b);
        fail(p, "expected '}'");
        return NULL;
    }
    if (allow_while) advance(p);
    return b;
}

/* parse 的完整说明见 parser.h */
int parse(Lexer *lex, ASTModule **out) {
    if (!out) return -1;
    *out = NULL;

    Parser prs = { .lex = lex, .cur_loaded = 0, .next_loaded = 0 };

    ASTModule *mod = (ASTModule *)malloc(sizeof(ASTModule));
    if (!mod) {
        fprintf(stderr, "parse: out of memory\n");
        return -1;
    }
    mod->import_paths = NULL;
    mod->num_imports = 0;
    mod->struct_defs = NULL;
    mod->num_structs = 0;
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

    /* [ struct Name { field : Type ; ... } ]* */
    ASTStructDef *struct_list[MAX_STRUCTS];
    int nstructs = 0;
    while (peek(&prs)->kind == TOKEN_STRUCT) {
        ASTStructDef *s = parse_one_struct(&prs);
        if (!s) {
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        if (nstructs >= MAX_STRUCTS) {
            ast_struct_def_free(s);
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            fail(&prs, "too many struct definitions");
            return -1;
        }
        struct_list[nstructs++] = s;
    }

    /* 可选：function main() -> i32 { expr } */
    if (peek(&prs)->kind == TOKEN_FUNCTION) {
        advance(&prs);
        if (!is_main_ident(peek(&prs))) {
            fail(&prs, "expected 'main'");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_LPAREN) {
            fail(&prs, "expected '('");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_RPAREN) {
            fail(&prs, "expected ')'");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_ARROW) {
            fail(&prs, "expected '->'");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        /* 目前仍仅允许 main 返回 i32，但用统一的类型解析接口，便于后续扩展 */
        if (peek(&prs)->kind != TOKEN_I32) {
            fail(&prs, "expected 'i32'");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        if (peek(&prs)->kind != TOKEN_LBRACE) {
            fail(&prs, "expected '{'");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        advance(&prs);
        ASTBlock *body = parse_block(&prs, 1);
        if (!body) {
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        if (peek(&prs)->kind != TOKEN_EOF) {
            ast_block_free(body);
            fail(&prs, "expected end of file");
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            return -1;
        }
        ASTFunc *func = (ASTFunc *)malloc(sizeof(ASTFunc));
        if (!func) {
            ast_block_free(body);
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        func->name = (const char *)strdup("main");
        func->return_type = (ASTType *)malloc(sizeof(ASTType));
        func->body = body;
        if (!func->name || !func->return_type) {
            if (func->name) free((void *)func->name);
            if (func->return_type) free(func->return_type);
            ast_block_free(body);
            free(func);
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        func->return_type->kind = AST_TYPE_I32;
        func->return_type->name = NULL;
        mod->main_func = func;
    } else if (peek(&prs)->kind != TOKEN_EOF) {
        fail(&prs, "expected 'function main' or end of file");
        while (nimports--) free(import_list[nimports]);
        while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
        free(mod);
        return -1;
    }

    /* 拷贝 struct 定义到 mod */
    if (nstructs > 0) {
        mod->struct_defs = (ASTStructDef **)malloc((size_t)nstructs * sizeof(ASTStructDef *));
        if (!mod->struct_defs) {
            while (nimports--) free(import_list[nimports]);
            while (nstructs--) ast_struct_def_free(struct_list[nstructs]);
            if (mod->main_func) {
                free((void *)mod->main_func->name);
                free(mod->main_func->return_type);
                ast_block_free(mod->main_func->body);
                free(mod->main_func);
            }
            free(mod);
            fprintf(stderr, "parse: out of memory\n");
            return -1;
        }
        for (int i = 0; i < nstructs; i++)
            mod->struct_defs[i] = struct_list[i];
        mod->num_structs = nstructs;
    }

    /* 拷贝 import 列表到 mod */
    if (nimports > 0) {
        mod->import_paths = (char **)malloc((size_t)nimports * sizeof(char *));
        if (!mod->import_paths) {
            while (nimports--) free(import_list[nimports]);
            if (mod->struct_defs) {
                for (int i = 0; i < mod->num_structs; i++) ast_struct_def_free(mod->struct_defs[i]);
                free(mod->struct_defs);
            }
            if (mod->main_func) {
                free((void *)mod->main_func->name);
                free((void *)mod->main_func->return_type);
                ast_block_free(mod->main_func->body);
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
