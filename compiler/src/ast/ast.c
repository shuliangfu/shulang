/**
 * ast.c — AST 内存管理
 *
 * 文件职责：实现 ast.h 声明的 ast_module_free，释放整棵 AST 树及 Parser 分配的所有附属字符串（import_paths、name、return_type 等）。
 * 所属模块：编译器前端 ast，compiler/src/ast/；与 include/ast.h 对应，被 parser、main 调用。
 * 与其它文件的关系：仅依赖 include/ast.h；不依赖 lexer/parser/typeck；调用方在解析或编译结束后统一调用，避免 use-after-free。
 * 重要约定：m 及其子节点中的字符串均由 Parser 侧 strdup/strndup，本函数负责全部 free；m 可为 NULL；调用后 m 不可再使用。
 */

#include "ast.h"
#include <stdlib.h>

/**
 * 释放表达式树；功能、参数、返回值见 ast.h 中 ast_expr_free 声明处注释。
 */
void ast_expr_free(ASTExpr *e) {
    if (!e) return;
    if (e->kind == AST_EXPR_ADD || e->kind == AST_EXPR_SUB) {
        ast_expr_free(e->value.binop.left);
        ast_expr_free(e->value.binop.right);
    }
    free(e);
}

/**
 * 释放 AST 模块及其子节点；功能、参数、返回值、约定见 ast.h 中声明处注释。
 */
void ast_module_free(ASTModule *m) {
    if (!m) return;
    if (m->import_paths) {
        for (int i = 0; i < m->num_imports; i++)
            if (m->import_paths[i]) free(m->import_paths[i]);
        free(m->import_paths);
        m->import_paths = NULL;
        m->num_imports = 0;
    }
    if (m->main_func) {
        if (m->main_func->name) free((void *)m->main_func->name);
        if (m->main_func->return_type) free((void *)m->main_func->return_type);
        if (m->main_func->body) ast_expr_free(m->main_func->body);
        free(m->main_func);
        m->main_func = NULL;
    }
    free(m);
}
