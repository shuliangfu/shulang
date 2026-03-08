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
    switch (e->kind) {
        case AST_EXPR_LIT:
        case AST_EXPR_BOOL_LIT:
            break;
        case AST_EXPR_VAR:
            if (e->value.var.name) free((void *)e->value.var.name);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            ast_expr_free(e->value.binop.left);
            ast_expr_free(e->value.binop.right);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            ast_expr_free(e->value.unary.operand);
            break;
        case AST_EXPR_IF:
            ast_expr_free(e->value.if_expr.cond);
            ast_expr_free(e->value.if_expr.then_expr);
            ast_expr_free(e->value.if_expr.else_expr);
            break;
        case AST_EXPR_BREAK:
        case AST_EXPR_CONTINUE:
            break;  /* 无子节点 */
        case AST_EXPR_RETURN:
        case AST_EXPR_PANIC:
            ast_expr_free(e->value.unary.operand);  /* 返回值或 panic 消息表达式 */
            break;
        case AST_EXPR_MATCH: {
            ast_expr_free(e->value.match_expr.matched_expr);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                ast_expr_free(e->value.match_expr.arms[i].result);
            free(e->value.match_expr.arms);
            break;
        }
        case AST_EXPR_FIELD_ACCESS:
            ast_expr_free(e->value.field_access.base);
            if (e->value.field_access.field_name) free((void *)e->value.field_access.field_name);
            break;
        case AST_EXPR_STRUCT_LIT: {
            if (e->value.struct_lit.struct_name) free((void *)e->value.struct_lit.struct_name);
            if (e->value.struct_lit.field_names) {
                for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                    if (e->value.struct_lit.field_names[i]) free((void *)e->value.struct_lit.field_names[i]);
                free(e->value.struct_lit.field_names);
            }
            if (e->value.struct_lit.inits) {
                for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                    ast_expr_free(e->value.struct_lit.inits[i]);
                free(e->value.struct_lit.inits);
            }
            break;
        }
        case AST_EXPR_ARRAY_LIT:
            if (e->value.array_lit.elems) {
                for (int i = 0; i < e->value.array_lit.num_elems; i++)
                    ast_expr_free(e->value.array_lit.elems[i]);
                free(e->value.array_lit.elems);
            }
            break;
        case AST_EXPR_INDEX:
            ast_expr_free(e->value.index.base);
            ast_expr_free(e->value.index.index_expr);
            break;
    }
    free(e);
}

/**
 * 释放类型节点；功能、参数见 ast.h 中 ast_type_free 声明处注释。
 * 对 AST_TYPE_PTR / AST_TYPE_ARRAY 会递归释放 elem_type。
 */
void ast_type_free(ASTType *t) {
    if (!t) return;
    if ((t->kind == AST_TYPE_PTR || t->kind == AST_TYPE_ARRAY || t->kind == AST_TYPE_SLICE) && t->elem_type)
        ast_type_free(t->elem_type);
    if (t->kind == AST_TYPE_NAMED && t->name)
        free((void *)t->name);
    free(t);
}

/**
 * 释放块（const/let 声明及 final_expr）；功能、参数见 ast.h 中 ast_block_free 声明处注释。
 */
void ast_block_free(ASTBlock *b) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++) {
        if (b->const_decls[i].name) free((void *)b->const_decls[i].name);
        if (b->const_decls[i].type) ast_type_free(b->const_decls[i].type);
        ast_expr_free(b->const_decls[i].init);
    }
    if (b->const_decls) free(b->const_decls);
    b->const_decls = NULL;
    b->num_consts = 0;
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].name) free((void *)b->let_decls[i].name);
        if (b->let_decls[i].type) ast_type_free(b->let_decls[i].type);
        ast_expr_free(b->let_decls[i].init);
    }
    if (b->let_decls) free(b->let_decls);
    b->let_decls = NULL;
    b->num_lets = 0;
    if (b->loops) {
        for (int i = 0; i < b->num_loops; i++) {
            ast_expr_free(b->loops[i].cond);
            ast_block_free(b->loops[i].body);
        }
        free(b->loops);
        b->loops = NULL;
        b->num_loops = 0;
    }
    if (b->for_loops) {
        for (int i = 0; i < b->num_for_loops; i++) {
            ast_expr_free(b->for_loops[i].init);
            ast_expr_free(b->for_loops[i].cond);
            ast_expr_free(b->for_loops[i].step);
            ast_block_free(b->for_loops[i].body);
        }
        free(b->for_loops);
        b->for_loops = NULL;
        b->num_for_loops = 0;
    }
    if (b->defer_blocks) {
        for (int i = 0; i < b->num_defers; i++)
            ast_block_free(b->defer_blocks[i]);
        free(b->defer_blocks);
        b->defer_blocks = NULL;
        b->num_defers = 0;
    }
    if (b->labeled_stmts) {
        for (int i = 0; i < b->num_labeled_stmts; i++) {
            if (b->labeled_stmts[i].label) free((void *)b->labeled_stmts[i].label);
            if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
                if (b->labeled_stmts[i].u.goto_target) free((void *)b->labeled_stmts[i].u.goto_target);
            } else {
                ast_expr_free(b->labeled_stmts[i].u.return_expr);
            }
        }
        free(b->labeled_stmts);
        b->labeled_stmts = NULL;
        b->num_labeled_stmts = 0;
    }
    ast_expr_free(b->final_expr);
    b->final_expr = NULL;
    free(b);
}

/**
 * 释放单条结构体定义；功能、参数见 ast.h 中 ast_struct_def_free 声明处注释。
 */
void ast_struct_def_free(ASTStructDef *s) {
    if (!s) return;
    if (s->name) free((void *)s->name);
    if (s->fields) {
        for (int i = 0; i < s->num_fields; i++) {
            if (s->fields[i].name) free((void *)s->fields[i].name);
            if (s->fields[i].type) ast_type_free(s->fields[i].type);
        }
        free(s->fields);
    }
    free(s);
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
    if (m->struct_defs) {
        for (int i = 0; i < m->num_structs; i++)
            ast_struct_def_free(m->struct_defs[i]);  /* 每项为 malloc 的 ASTStructDef* */
        free(m->struct_defs);
        m->struct_defs = NULL;
        m->num_structs = 0;
    }
    if (m->main_func) {
        if (m->main_func->name) free((void *)m->main_func->name);
        if (m->main_func->return_type) ast_type_free(m->main_func->return_type);
        if (m->main_func->body) ast_block_free(m->main_func->body);
        free(m->main_func);
        m->main_func = NULL;
    }
    free(m);
}
