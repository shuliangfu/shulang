/**
 * typeck.c — 类型检查实现
 *
 * 文件职责：实现 typeck.h 声明的 typeck_module，对 AST 做最小类型校验（main 返回 i32、体为整数字面量；库模块放行）。
 * 所属模块：编译器前端 typeck，compiler/src/typeck/；实现 typeck.h。
 * 与其它文件的关系：依赖 include/ast.h；被 main 在 parse 之后调用；不修改 AST。
 * 重要约定：与阶段 3 设计一致；后续阶段可在此扩展泛型、trait 等检查。
 */

#include "typeck/typeck.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>

/**
 * 对单棵表达式做类型检查；当前子集仅整数字面量与加减，均视为整型。
 * 参数：e 表达式根节点，不可为 NULL。返回值：0 通过，-1 发现非法节点类型并已写 stderr。
 */
static int typeck_expr(const struct ASTExpr *e) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_LIT:
            return 0;
        case AST_EXPR_ADD:
        case AST_EXPR_SUB:
            if (typeck_expr(e->value.binop.left) != 0) return -1;
            if (typeck_expr(e->value.binop.right) != 0) return -1;
            return 0;
        default:
            fprintf(stderr, "typeck error: unsupported expression kind\n");
            return -1;
    }
}

/**
 * 对模块做类型检查；功能、参数、返回值见 typeck.h 声明处注释。
 */
int typeck_module(struct ASTModule *m) {
    if (!m) {
        fprintf(stderr, "typeck error: null module\n");
        return -1;
    }
    /* 库模块（仅 import 或无 main）视为通过 */
    if (!m->main_func)
        return 0;

    if (!m->main_func->return_type || strcmp(m->main_func->return_type, "i32") != 0) {
        fprintf(stderr, "typeck error: main must return i32\n");
        return -1;
    }

    if (!m->main_func->body) {
        fprintf(stderr, "typeck error: main must have a body expression\n");
        return -1;
    }

    /* 递归检查 body 表达式：LIT 通过，ADD/SUB 递归检查左右子表达式（当前子集均为整型） */
    return typeck_expr(m->main_func->body);
}
