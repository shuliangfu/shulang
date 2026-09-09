/* seeds/async_liveness.from_x.c — G-02f-18 product TU
 * G-02f-169～171 refs/analyze true .x; G-02f-166～168 await AST true .x; G-02f-132 true .x pure helpers.
 *
 * R2 pure surface + Cap residual pure（2026-07-21）：await walk / live frame / mangle /
 *   frame_build_tag + lookup/type/size/layout/has_await/needs_cps/analyze/module_struct
 *   + FILE* emit_*（typedef/local/codegen_comment via shared driver_preamble_fputs）
 *   由 src/async/async_liveness.x 提供；FROM_X 下 pure C 体省略（仅 slice_marker）。
 * Cap residual（G.7 单一权威）：driver_preamble_fputs（runtime_driver_abi；opaque FILE*）。
 * 冷启动/无 PREFER：完整 pure C 体 + FILE* emit 用原生 fputs；-c 本文件。
 * 产品 PREFER（2026-07-21）：g05/Makefile full .x + rest (-DXLANG_ASYNC_LIVENESS_FROM_X)
 *   ld -r → src/async/async_liveness.o（独立 TU，非 pipeline_glue #include）。
 * PLATFORM: SHARED — pure helper 面跨平台；Ubuntu 金标 prove。
 */
/**
 * async_liveness.c — async 跨 await liveness 分析与协程帧 struct emit（A3）
 *
 * 文件职责：按 stmt_order 线性扫描 async 函数体，求帧存活集并 emit C typedef + 帧局部占位。
 * 所属模块：compiler/src/async/；实现 async_liveness.h。
 */
#include "async_liveness.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: async_liveness type/name format → Cap snprintf */
/* G.7: single Cap authority for this TU (after stdio). */
#undef snprintf
#define snprintf xlang_snprintf

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
int expr_has_await(const struct ASTExpr *e);
int block_has_await(const struct ASTBlock *b);
int block_has_io_read_await(const struct ASTBlock *b);
int block_has_io_write_await(const struct ASTBlock *b);
int expr_count_await(const struct ASTExpr *e);
int block_count_await(const struct ASTBlock *b);
int expr_refs_var(const struct ASTExpr *e, const char *name);
int block_refs_var(const struct ASTBlock *b, const char *name);
void analyze_block_linear(const struct ASTBlock *b, const char **prefix, int n_prefix, AsyncFrameLive *frame);
void frame_build_tag(const struct ASTFunc *f, char *buf, size_t n);
void frame_mangle_ident(const char *fn, char *out, size_t n);
int live_name_cmp(const void *a, const void *b);

#ifndef XLANG_ASYNC_LIVENESS_FROM_X
/* G-02f-20 thin+rest：DIRECT 模式，thin（src/async/async_liveness.x）提供完整实现 */
/** 表达式是否含 await（递归）。 */
/* G-02f-166：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int expr_has_await(const struct ASTExpr *e) {
    if (!e) return 0;
    if (e->kind == AST_EXPR_AWAIT) return 1;
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
        case AST_EXPR_ADD_ASSIGN: case AST_EXPR_SUB_ASSIGN: case AST_EXPR_MUL_ASSIGN:
        case AST_EXPR_DIV_ASSIGN: case AST_EXPR_MOD_ASSIGN:
        case AST_EXPR_BITAND_ASSIGN: case AST_EXPR_BITOR_ASSIGN: case AST_EXPR_BITXOR_ASSIGN:
        case AST_EXPR_SHL_ASSIGN: case AST_EXPR_SHR_ASSIGN:
            return expr_has_await(e->value.binop.left) || expr_has_await(e->value.binop.right);
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            return expr_has_await(e->value.unary.operand);
        case AST_EXPR_AS:
            return expr_has_await(e->value.as_type.operand);
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            return expr_has_await(e->value.if_expr.cond)
                || expr_has_await(e->value.if_expr.then_expr)
                || (e->value.if_expr.else_expr && expr_has_await(e->value.if_expr.else_expr));
        case AST_EXPR_BLOCK:
            return block_has_await(e->value.block);
        case AST_EXPR_FIELD_ACCESS:
            return expr_has_await(e->value.field_access.base);
        case AST_EXPR_INDEX:
            return expr_has_await(e->value.index.base) || expr_has_await(e->value.index.index_expr);
        case AST_EXPR_CALL:
            if (expr_has_await(e->value.call.callee)) return 1;
            for (int i = 0; i < e->value.call.num_args; i++)
                if (expr_has_await(e->value.call.args[i])) return 1;
            return 0;
        case AST_EXPR_METHOD_CALL:
            if (expr_has_await(e->value.method_call.base)) return 1;
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (expr_has_await(e->value.method_call.args[i])) return 1;
            return 0;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (expr_has_await(e->value.struct_lit.inits[i])) return 1;
            return 0;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (expr_has_await(e->value.array_lit.elems[i])) return 1;
            return 0;
        case AST_EXPR_MATCH:
            if (expr_has_await(e->value.match_expr.matched_expr)) return 1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (expr_has_await(e->value.match_expr.arms[i].result)) return 1;
            return 0;
        default:
            return 0;
    }
}
/** 统计表达式内 await 个数（递归累加）。 */
/* G-02f-166：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int expr_count_await(const struct ASTExpr *e) {
    if (!e) return 0;
    if (e->kind == AST_EXPR_AWAIT)
        return 1 + expr_count_await(e->value.unary.operand);
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
        case AST_EXPR_ADD_ASSIGN: case AST_EXPR_SUB_ASSIGN: case AST_EXPR_MUL_ASSIGN:
        case AST_EXPR_DIV_ASSIGN: case AST_EXPR_MOD_ASSIGN:
        case AST_EXPR_BITAND_ASSIGN: case AST_EXPR_BITOR_ASSIGN: case AST_EXPR_BITXOR_ASSIGN:
        case AST_EXPR_SHL_ASSIGN: case AST_EXPR_SHR_ASSIGN:
            return expr_count_await(e->value.binop.left) + expr_count_await(e->value.binop.right);
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            return expr_count_await(e->value.unary.operand);
        case AST_EXPR_AS:
            return expr_count_await(e->value.as_type.operand);
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            return expr_count_await(e->value.if_expr.cond)
                + expr_count_await(e->value.if_expr.then_expr)
                + (e->value.if_expr.else_expr ? expr_count_await(e->value.if_expr.else_expr) : 0);
        case AST_EXPR_BLOCK:
            return block_count_await(e->value.block);
        case AST_EXPR_FIELD_ACCESS:
            return expr_count_await(e->value.field_access.base);
        case AST_EXPR_INDEX:
            return expr_count_await(e->value.index.base) + expr_count_await(e->value.index.index_expr);
        case AST_EXPR_CALL:
            { int n = expr_count_await(e->value.call.callee);
              for (int i = 0; i < e->value.call.num_args; i++)
                  n += expr_count_await(e->value.call.args[i]);
              return n; }
        case AST_EXPR_METHOD_CALL:
            { int n = expr_count_await(e->value.method_call.base);
              for (int i = 0; i < e->value.method_call.num_args; i++)
                  n += expr_count_await(e->value.method_call.args[i]);
              return n; }
        case AST_EXPR_STRUCT_LIT:
            { int n = 0;
              for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                  n += expr_count_await(e->value.struct_lit.inits[i]);
              return n; }
        case AST_EXPR_ARRAY_LIT:
            { int n = 0;
              for (int i = 0; i < e->value.array_lit.num_elems; i++)
                  n += expr_count_await(e->value.array_lit.elems[i]);
              return n; }
        case AST_EXPR_MATCH:
            { int n = expr_count_await(e->value.match_expr.matched_expr);
              for (int i = 0; i < e->value.match_expr.num_arms; i++)
                  n += expr_count_await(e->value.match_expr.arms[i].result);
              return n; }
        default:
            return 0;
    }
}
/** 块内是否存在 await（A3 v0 不扫描 loop/for 体）。 */
/* G-02f-168：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_has_await(const struct ASTBlock *b) {
    return block_count_await(b) > 0;
}




/** 块内 await 个数（A3 v0 不扫描 loop/for 体）。 */
/* G-02f-168：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_count_await(const struct ASTBlock *b) {
    if (!b) return 0;
    int n = 0;
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) n += expr_count_await(b->let_decls[i].init);
    for (int i = 0; i < b->num_expr_stmts; i++)
        n += expr_count_await(b->expr_stmts[i]);
    if (b->final_expr) n += expr_count_await(b->final_expr);
    return n;
}
/** callee 是否为 IO read await 目标（read / read_fd）。 */
/* G-02f-132：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int async_liveness_callee_is_io_read(const struct ASTFunc *callee) {
    if (!callee || !callee->name)
        return 0;
    return strcmp(callee->name, "read") == 0 || strcmp(callee->name, "read_fd") == 0;

}


/** callee 是否为 IO write await 目标（write / write_fd）。 */
/* G-02f-132：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int async_liveness_callee_is_io_write(const struct ASTFunc *callee) {
    if (!callee || !callee->name)
        return 0;
    return strcmp(callee->name, "write") == 0 || strcmp(callee->name, "write_fd") == 0;

}


/** 表达式是否含 await read/read_fd（递归）。 */
/* G-02f-167：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int expr_has_io_read_await(const struct ASTExpr *e) {
    const struct ASTExpr *op;
    const struct ASTFunc *callee;
    if (!e)
        return 0;
    if (e->kind == AST_EXPR_AWAIT) {
        op = e->value.unary.operand;
        if (op && op->kind == AST_EXPR_CALL && op->value.call.resolved_callee_func) {
            callee = op->value.call.resolved_callee_func;
            if (async_liveness_callee_is_io_read(callee))
                return 1;
        }
    }
    if (expr_has_await(e)) {
        /* 复用 await 扫描路径：对含 await 的子树递归（避免漏嵌套 expr）。 */
        switch (e->kind) {
            case AST_EXPR_AWAIT:
                return expr_has_io_read_await(e->value.unary.operand);
            case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
            case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
            case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
            case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
            case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            case AST_EXPR_ASSIGN:
            case AST_EXPR_ADD_ASSIGN: case AST_EXPR_SUB_ASSIGN: case AST_EXPR_MUL_ASSIGN:
            case AST_EXPR_DIV_ASSIGN: case AST_EXPR_MOD_ASSIGN:
            case AST_EXPR_BITAND_ASSIGN: case AST_EXPR_BITOR_ASSIGN: case AST_EXPR_BITXOR_ASSIGN:
            case AST_EXPR_SHL_ASSIGN: case AST_EXPR_SHR_ASSIGN:
                return expr_has_io_read_await(e->value.binop.left)
                    || expr_has_io_read_await(e->value.binop.right);
            case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            case AST_EXPR_RETURN: case AST_EXPR_PANIC:
                return expr_has_io_read_await(e->value.unary.operand);
            case AST_EXPR_AS:
                return expr_has_io_read_await(e->value.as_type.operand);
            case AST_EXPR_IF: case AST_EXPR_TERNARY:
                return expr_has_io_read_await(e->value.if_expr.cond)
                    || expr_has_io_read_await(e->value.if_expr.then_expr)
                    || (e->value.if_expr.else_expr && expr_has_io_read_await(e->value.if_expr.else_expr));
            case AST_EXPR_BLOCK:
                return block_has_io_read_await(e->value.block);
            case AST_EXPR_FIELD_ACCESS:
                return expr_has_io_read_await(e->value.field_access.base);
            case AST_EXPR_INDEX:
                return expr_has_io_read_await(e->value.index.base)
                    || expr_has_io_read_await(e->value.index.index_expr);
            case AST_EXPR_CALL:
                if (expr_has_io_read_await(e->value.call.callee)) return 1;
                for (int i = 0; i < e->value.call.num_args; i++)
                    if (expr_has_io_read_await(e->value.call.args[i])) return 1;
                return 0;
            case AST_EXPR_METHOD_CALL:
                if (expr_has_io_read_await(e->value.method_call.base)) return 1;
                for (int i = 0; i < e->value.method_call.num_args; i++)
                    if (expr_has_io_read_await(e->value.method_call.args[i])) return 1;
                return 0;
            case AST_EXPR_STRUCT_LIT:
                for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                    if (expr_has_io_read_await(e->value.struct_lit.inits[i])) return 1;
                return 0;
            case AST_EXPR_ARRAY_LIT:
                for (int i = 0; i < e->value.array_lit.num_elems; i++)
                    if (expr_has_io_read_await(e->value.array_lit.elems[i])) return 1;
                return 0;
            case AST_EXPR_MATCH:
                if (expr_has_io_read_await(e->value.match_expr.matched_expr)) return 1;
                for (int i = 0; i < e->value.match_expr.num_arms; i++)
                    if (expr_has_io_read_await(e->value.match_expr.arms[i].result)) return 1;
                return 0;
            default:
                return 0;
        }
    }
    return 0;
}
/** 表达式是否含 await write/write_fd（递归）。 */
/* G-02f-167：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int expr_has_io_write_await(const struct ASTExpr *e) {
    const struct ASTExpr *op;
    const struct ASTFunc *callee;
    if (!e)
        return 0;
    if (e->kind == AST_EXPR_AWAIT) {
        op = e->value.unary.operand;
        if (op && op->kind == AST_EXPR_CALL && op->value.call.resolved_callee_func) {
            callee = op->value.call.resolved_callee_func;
            if (async_liveness_callee_is_io_write(callee))
                return 1;
        }
    }
    if (expr_has_await(e)) {
        switch (e->kind) {
            case AST_EXPR_AWAIT:
                return expr_has_io_write_await(e->value.unary.operand);
            case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
            case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
            case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
            case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
            case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            case AST_EXPR_ASSIGN:
            case AST_EXPR_ADD_ASSIGN: case AST_EXPR_SUB_ASSIGN: case AST_EXPR_MUL_ASSIGN:
            case AST_EXPR_DIV_ASSIGN: case AST_EXPR_MOD_ASSIGN:
            case AST_EXPR_BITAND_ASSIGN: case AST_EXPR_BITOR_ASSIGN: case AST_EXPR_BITXOR_ASSIGN:
            case AST_EXPR_SHL_ASSIGN: case AST_EXPR_SHR_ASSIGN:
                return expr_has_io_write_await(e->value.binop.left)
                    || expr_has_io_write_await(e->value.binop.right);
            case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            case AST_EXPR_RETURN: case AST_EXPR_PANIC:
                return expr_has_io_write_await(e->value.unary.operand);
            case AST_EXPR_AS:
                return expr_has_io_write_await(e->value.as_type.operand);
            case AST_EXPR_IF: case AST_EXPR_TERNARY:
                return expr_has_io_write_await(e->value.if_expr.cond)
                    || expr_has_io_write_await(e->value.if_expr.then_expr)
                    || (e->value.if_expr.else_expr && expr_has_io_write_await(e->value.if_expr.else_expr));
            case AST_EXPR_BLOCK:
                return block_has_io_write_await(e->value.block);
            case AST_EXPR_FIELD_ACCESS:
                return expr_has_io_write_await(e->value.field_access.base);
            case AST_EXPR_INDEX:
                return expr_has_io_write_await(e->value.index.base)
                    || expr_has_io_write_await(e->value.index.index_expr);
            case AST_EXPR_CALL:
                if (expr_has_io_write_await(e->value.call.callee)) return 1;
                for (int i = 0; i < e->value.call.num_args; i++)
                    if (expr_has_io_write_await(e->value.call.args[i])) return 1;
                return 0;
            case AST_EXPR_METHOD_CALL:
                if (expr_has_io_write_await(e->value.method_call.base)) return 1;
                for (int i = 0; i < e->value.method_call.num_args; i++)
                    if (expr_has_io_write_await(e->value.method_call.args[i])) return 1;
                return 0;
            case AST_EXPR_STRUCT_LIT:
                for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                    if (expr_has_io_write_await(e->value.struct_lit.inits[i])) return 1;
                return 0;
            case AST_EXPR_ARRAY_LIT:
                for (int i = 0; i < e->value.array_lit.num_elems; i++)
                    if (expr_has_io_write_await(e->value.array_lit.elems[i])) return 1;
                return 0;
            case AST_EXPR_MATCH:
                if (expr_has_io_write_await(e->value.match_expr.matched_expr)) return 1;
                for (int i = 0; i < e->value.match_expr.num_arms; i++)
                    if (expr_has_io_write_await(e->value.match_expr.arms[i].result)) return 1;
                return 0;
            default:
                return 0;
        }
    }
    return 0;
}
/** 块内是否含 await read/read_fd。 */
/* G-02f-167：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_has_io_read_await(const struct ASTBlock *b) {
    if (!b)
        return 0;
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && expr_has_io_read_await(b->let_decls[i].init))
            return 1;
    for (int i = 0; i < b->num_expr_stmts; i++)
        if (expr_has_io_read_await(b->expr_stmts[i]))
            return 1;
    if (b->final_expr && expr_has_io_read_await(b->final_expr))
        return 1;
    return 0;
}
/** 块内是否含 await write/write_fd。 */
/* G-02f-167：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_has_io_write_await(const struct ASTBlock *b) {
    if (!b)
        return 0;
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && expr_has_io_write_await(b->let_decls[i].init))
            return 1;
    for (int i = 0; i < b->num_expr_stmts; i++)
        if (expr_has_io_write_await(b->expr_stmts[i]))
            return 1;
    if (b->final_expr && expr_has_io_write_await(b->final_expr))
        return 1;
    return 0;
}
/** 表达式是否引用变量 name。 */
/* G-02f-169：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int expr_refs_var(const struct ASTExpr *e, const char *name) {
    if (!e || !name || !name[0]) return 0;
    if (e->kind == AST_EXPR_VAR && e->value.var.name && strcmp(e->value.var.name, name) == 0)
        return 1;
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
        case AST_EXPR_ADD_ASSIGN: case AST_EXPR_SUB_ASSIGN: case AST_EXPR_MUL_ASSIGN:
        case AST_EXPR_DIV_ASSIGN: case AST_EXPR_MOD_ASSIGN:
        case AST_EXPR_BITAND_ASSIGN: case AST_EXPR_BITOR_ASSIGN: case AST_EXPR_BITXOR_ASSIGN:
        case AST_EXPR_SHL_ASSIGN: case AST_EXPR_SHR_ASSIGN:
            return expr_refs_var(e->value.binop.left, name) || expr_refs_var(e->value.binop.right, name);
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF: case AST_EXPR_AWAIT:
        case AST_EXPR_RETURN: case AST_EXPR_PANIC:
            return expr_refs_var(e->value.unary.operand, name);
        case AST_EXPR_AS:
            return expr_refs_var(e->value.as_type.operand, name);
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            return expr_refs_var(e->value.if_expr.cond, name)
                || expr_refs_var(e->value.if_expr.then_expr, name)
                || (e->value.if_expr.else_expr && expr_refs_var(e->value.if_expr.else_expr, name));
        case AST_EXPR_BLOCK:
            return block_refs_var(e->value.block, name);
        case AST_EXPR_FIELD_ACCESS:
            return expr_refs_var(e->value.field_access.base, name);
        case AST_EXPR_INDEX:
            return expr_refs_var(e->value.index.base, name) || expr_refs_var(e->value.index.index_expr, name);
        case AST_EXPR_CALL:
            if (expr_refs_var(e->value.call.callee, name)) return 1;
            for (int i = 0; i < e->value.call.num_args; i++)
                if (expr_refs_var(e->value.call.args[i], name)) return 1;
            return 0;
        case AST_EXPR_METHOD_CALL:
            if (expr_refs_var(e->value.method_call.base, name)) return 1;
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (expr_refs_var(e->value.method_call.args[i], name)) return 1;
            return 0;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (expr_refs_var(e->value.struct_lit.inits[i], name)) return 1;
            return 0;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (expr_refs_var(e->value.array_lit.elems[i], name)) return 1;
            return 0;
        case AST_EXPR_MATCH:
            if (expr_refs_var(e->value.match_expr.matched_expr, name)) return 1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (expr_refs_var(e->value.match_expr.arms[i].result, name)) return 1;
            return 0;
        default:
            return 0;
    }
}
/** 块内是否引用变量 name（A3 v0 不递归 loop/for）。 */
/* G-02f-169：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_refs_var(const struct ASTBlock *b, const char *name) {
    if (!b) return 0;
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].init && expr_refs_var(b->let_decls[i].init, name)) return 1;
    }
    for (int i = 0; i < b->num_expr_stmts; i++)
        if (expr_refs_var(b->expr_stmts[i], name)) return 1;
    if (b->final_expr && expr_refs_var(b->final_expr, name)) return 1;
    return 0;
}
/** continuation 是否引用 name（从 stmt_order[from_exclusive+1] 起到块末）。 */
/* G-02f-170：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int block_rest_refs_var(const struct ASTBlock *b, int from_exclusive,
    const char *name) {
    if (!b || !name || !name[0]) return 0;
    if (b->num_stmt_order > 0) {
        for (int si = from_exclusive + 1; si < b->num_stmt_order; si++) {
            unsigned char kind = b->stmt_order[si].kind;
            int idx = b->stmt_order[si].idx;
            if (kind == 1 && b->let_decls && idx >= 0 && idx < b->num_lets) {
                if (b->let_decls[idx].init && expr_refs_var(b->let_decls[idx].init, name)) return 1;
            } else if (kind == 2 && b->expr_stmts && idx >= 0 && idx < b->num_expr_stmts) {
                if (expr_refs_var(b->expr_stmts[idx], name)) return 1;
            }
        }
        if (b->final_expr && expr_refs_var(b->final_expr, name)) return 1;
        return 0;
    }
    if (b->final_expr && expr_refs_var(b->final_expr, name)) return 1;
    return 0;
}



/** 将 name 插入 out（去重，超上限静默丢弃）。 */
/* G-02f-162：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void frame_live_add(AsyncFrameLive *out, const char *name) {
    if (!out || !name || !name[0]) return;
    for (int i = 0; i < out->n; i++)
        if (strcmp(out->names[i], name) == 0) return;
    if (out->n >= ASYNC_LIVE_MAX_VARS) return;
    strncpy(out->names[out->n], name, sizeof(out->names[0]) - 1);
    out->names[out->n][sizeof(out->names[0]) - 1] = '\0';
    out->n++;
}


/** 在 await 点将 defined[0..n_def) 中 continuation 仍引用的符号加入 frame。 */
/* G-02f-164：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void frame_live_at_await(const struct ASTBlock *b, int stmt_idx,
    const char **defined, int n_def, AsyncFrameLive *frame) {
    for (int i = 0; i < n_def; i++) {
        if (defined[i] && block_rest_refs_var(b, stmt_idx, defined[i]))
            frame_live_add(frame, defined[i]);
    }
}


/** 按 stmt_order 线性扫描并更新 frame（A3 v0：不进入 loop/for 体）。 */
/* G-02f-171：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void analyze_block_linear(const struct ASTBlock *b,
    const char **prefix_defined, int n_prefix, AsyncFrameLive *frame) {
    const char *defined[ASYNC_LIVE_MAX_VARS];
    int n_def = 0;
    for (int i = 0; i < n_prefix && n_def < ASYNC_LIVE_MAX_VARS; i++)
        defined[n_def++] = prefix_defined[i];

    if (b->num_stmt_order > 0) {
        for (int si = 0; si < b->num_stmt_order; si++) {
            unsigned char kind = b->stmt_order[si].kind;
            int idx = b->stmt_order[si].idx;
            if (kind == 1 && b->let_decls && idx >= 0 && idx < b->num_lets) {
                const struct ASTExpr *init = b->let_decls[idx].init;
                if (init && expr_has_await(init))
                    frame_live_at_await(b, si, defined, n_def, frame);
                if (n_def < ASYNC_LIVE_MAX_VARS && b->let_decls[idx].name)
                    defined[n_def++] = b->let_decls[idx].name;
            } else if (kind == 2 && b->expr_stmts && idx >= 0 && idx < b->num_expr_stmts) {
                const struct ASTExpr *ex = b->expr_stmts[idx];
                if (ex && expr_has_await(ex))
                    frame_live_at_await(b, si, defined, n_def, frame);
            }
        }
        if (b->final_expr && expr_has_await(b->final_expr))
            frame_live_at_await(b, b->num_stmt_order - 1, defined, n_def, frame);
        return;
    }

    if (b->final_expr && expr_has_await(b->final_expr))
        frame_live_at_await(b, -1, defined, n_def, frame);
}



/** 名称字典序比较（qsort 用）。 */
/* G-02f-119：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int live_name_cmp(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}




/** 函数名转 C 标识符（非 alnum/_ → _）。 */
/* G-02f-161：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void frame_mangle_ident(const char *fn, char *out, size_t n) {
    if (!out || n == 0) return;
    if (!fn || !fn[0]) {
        strncpy(out, "fn", n - 1);
        out[n - 1] = '\0';
        return;
    }
    size_t j = 0;
    for (size_t i = 0; fn[i] && j + 1 < n; i++) {
        char c = fn[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
            out[j++] = c;
        else
            out[j++] = '_';
    }
    out[j] = '\0';
}

/** 构造协程帧 C 类型名 __xlang_async_frame_<mangled>。
 * R2：.x 已真迁 frame_build_tag（字面量路径可用）；FROM_X 时由 .x 提供。 */
/* G-02f-161：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void frame_build_tag(const struct ASTFunc *f, char *buf, size_t n) {
    char m[64];
    frame_mangle_ident(f && f->name ? f->name : "fn", m, sizeof(m));
    (void)snprintf(buf, n, "__xlang_async_frame_%s", m);
}
#else /* XLANG_ASYNC_LIVENESS_FROM_X — pure helpers + Cap residual pure + emit from .x */
/* R2 pure surface + Cap residual pure + FILE* emit marker：业务 pure 不在此 TU 定义。 */
int async_liveness_slice_marker(void) {
    return 1;
}
#endif /* XLANG_ASYNC_LIVENESS_FROM_X */


#ifndef XLANG_ASYNC_LIVENESS_FROM_X
/* Cap residual pure + FILE* emit：.x 真迁；冷路径仍 seed C；FROM_X 时由 .x 提供 */
/** 在函数体/形参中查找变量类型。 */
const struct ASTType *async_liveness_lookup_var_type(const struct ASTFunc *f, const char *name) {
    if (!f || !name || !name[0]) return NULL;
    for (int i = 0; i < f->num_params; i++) {
        if (f->params[i].name && strcmp(f->params[i].name, name) == 0)
            return f->params[i].type;
    }
    if (f->body && f->body->let_decls) {
        for (int i = 0; i < f->body->num_lets; i++) {
            if (f->body->let_decls[i].name && strcmp(f->body->let_decls[i].name, name) == 0)
                return f->body->let_decls[i].type;
        }
    }
    return NULL;
}

/** AST 类型 → C 类型字符串（写入 buf；A3 覆盖常见标量/指针）。 */
void async_liveness_type_to_c_buf(const struct ASTType *ty, char *buf, size_t n) {
    if (!buf || n == 0) return;
    if (!ty) {
        strncpy(buf, "int32_t", n - 1);
        buf[n - 1] = '\0';
        return;
    }
    switch (ty->kind) {
        case AST_TYPE_I32: strncpy(buf, "int32_t", n - 1); break;
        case AST_TYPE_BOOL: strncpy(buf, "int32_t", n - 1); break;
        case AST_TYPE_U8: strncpy(buf, "uint8_t", n - 1); break;
        case AST_TYPE_U32: strncpy(buf, "uint32_t", n - 1); break;
        case AST_TYPE_U64: strncpy(buf, "uint64_t", n - 1); break;
        case AST_TYPE_I64: strncpy(buf, "int64_t", n - 1); break;
        case AST_TYPE_USIZE: strncpy(buf, "uintptr_t", n - 1); break;
        case AST_TYPE_ISIZE: strncpy(buf, "intptr_t", n - 1); break;
        case AST_TYPE_F32: strncpy(buf, "float", n - 1); break;
        case AST_TYPE_F64: strncpy(buf, "double", n - 1); break;
        case AST_TYPE_PTR:
            if (ty->elem_type) {
                char inner[64];
                async_liveness_type_to_c_buf(ty->elem_type, inner, sizeof(inner));
                (void)snprintf(buf, n, "%s *", inner);
            } else {
                strncpy(buf, "void *", n - 1);
            }
            break;
        case AST_TYPE_NAMED:
            if (ty->name) {
                if (strncmp(ty->name, "struct ", 7) == 0)
                    (void)snprintf(buf, n, "%s", ty->name);
                else
                    (void)snprintf(buf, n, "struct %s", ty->name);
            } else {
                strncpy(buf, "int32_t", n - 1);
            }
            break;
        default:
            strncpy(buf, "int32_t", n - 1);
            break;
    }
    buf[n - 1] = '\0';
}

/** 估算类型字节数；module 非 NULL 时 NAMED struct 用 layout pass 的 struct_size。 */
int async_liveness_type_size_bytes_module(const struct ASTType *ty, const struct ASTModule *m) {
    if (!ty) return 4;
    if (ty->kind == AST_TYPE_NAMED && ty->name && m && m->struct_defs) {
        for (int i = 0; i < m->num_structs; i++) {
            const struct ASTStructDef *sd = m->struct_defs[i];
            if (sd && sd->name && strcmp(sd->name, ty->name) == 0 && sd->struct_size > 0)
                return sd->struct_size;
        }
    }
    switch (ty->kind) {
        case AST_TYPE_I64: case AST_TYPE_U64: case AST_TYPE_F64:
        case AST_TYPE_USIZE: case AST_TYPE_ISIZE: case AST_TYPE_PTR:
            return 8;
        case AST_TYPE_NAMED:
            return 8;
        default:
            return 4;
    }
}

int async_liveness_func_has_await(const struct ASTFunc *f) {
    return f && f->is_async && f->body && block_has_await(f->body);
}

/** 是否须 CPS 帧：IO/多 await，或跨 await 存活非形参 let；仅形参 live 的 sync-stub 直返保留 C 签名。 */
int async_liveness_func_needs_cps_frame(const struct ASTFunc *f) {
    AsyncFrameLayout layout;
    int i;
    int pi;
    if (!f || !f->is_async || !f->body || !block_has_await(f->body))
        return 0;
    if (block_has_io_read_await(f->body) || block_has_io_write_await(f->body))
        return 1;
    if (block_count_await(f->body) > 1)
        return 1;
    /** 含 let/loop 的 await 须 CPS（yield_demo、liveness_demo）；无则为 return-await 直返 stub。 */
    if (f->body->num_lets > 0 || f->body->num_loops > 0 || f->body->num_for_loops > 0)
        return 1;
    if (async_liveness_layout_func_module(f, NULL, &layout) != 0)
        return 0;
    if (layout.live.n <= 0)
        return 0;
    for (i = 0; i < layout.live.n; i++) {
        int is_param = 0;
        for (pi = 0; pi < f->num_params; pi++) {
            if (f->params[pi].name && strcmp(f->params[pi].name, layout.live.names[i]) == 0) {
                is_param = 1;
                break;
            }
        }
        if (!is_param)
            return 1;
    }
    return 0;
}

int async_liveness_expr_has_await(const struct ASTExpr *e) {
    return expr_has_await(e);
}

int async_liveness_layout_func(const struct ASTFunc *f, AsyncFrameLayout *out) {
    return async_liveness_layout_func_module(f, NULL, out);
}

int async_liveness_layout_func_module(const struct ASTFunc *f, const struct ASTModule *m,
    AsyncFrameLayout *out) {
    if (!out) return -1;
    memset(out, 0, sizeof(*out));
    if (!f || !f->is_async || !f->body) return 0;
    if (!block_has_await(f->body)) return 0;

    const char *prefix[ASYNC_LIVE_MAX_VARS];
    int n_pre = 0;
    for (int i = 0; i < f->num_params && n_pre < ASYNC_LIVE_MAX_VARS; i++) {
        if (f->params[i].name)
            prefix[n_pre++] = f->params[i].name;
    }

    analyze_block_linear(f->body, prefix, n_pre, &out->live);
    if (out->live.n > 1)
        qsort(out->live.names, (size_t)out->live.n, sizeof(out->live.names[0]), live_name_cmp);

    out->num_awaits = block_count_await(f->body);
    out->has_io_rd_slot = block_has_io_read_await(f->body);
    out->has_io_wr_slot = block_has_io_write_await(f->body);
    frame_build_tag(f, out->frame_tag, sizeof(out->frame_tag));

    out->frame_bytes = 4; /* __phase */
    if (out->has_io_rd_slot)
        out->frame_bytes += 4;
    if (out->has_io_wr_slot)
        out->frame_bytes += 4;
    for (int i = 0; i < out->live.n; i++) {
        const struct ASTType *ty = async_liveness_lookup_var_type(f, out->live.names[i]);
        out->frame_bytes += async_liveness_type_size_bytes_module(ty, m);
    }
    return 0;
}

/** 结构体名是否出现在模块内某 async 协程帧 live 集（codegen 须先 emit struct 定义）。 */
int async_liveness_module_struct_in_frame(const struct ASTModule *m, const char *struct_name) {
    if (!m || !struct_name || !struct_name[0] || !m->funcs)
        return 0;
    for (int fi = 0; fi < m->num_funcs; fi++) {
        const struct ASTFunc *f = m->funcs[fi];
        AsyncFrameLayout layout;
        if (!f || !f->is_async || !async_liveness_func_has_await(f))
            continue;
        if (async_liveness_layout_func_module(f, m, &layout) != 0)
            continue;
        for (int li = 0; li < layout.live.n; li++) {
            const struct ASTType *ty = async_liveness_lookup_var_type(f, layout.live.names[li]);
            if (ty && ty->kind == AST_TYPE_NAMED && ty->name && strcmp(ty->name, struct_name) == 0)
                return 1;
        }
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++) {
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            AsyncFrameLayout layout;
            if (!f || !f->is_async || !async_liveness_func_has_await(f))
                continue;
            if (async_liveness_layout_func_module(f, m, &layout) != 0)
                continue;
            for (int li = 0; li < layout.live.n; li++) {
                const struct ASTType *ty = async_liveness_lookup_var_type(f, layout.live.names[li]);
                if (ty && ty->kind == AST_TYPE_NAMED && ty->name && strcmp(ty->name, struct_name) == 0)
                    return 1;
            }
        }
    }
    return 0;
}

int async_liveness_analyze_func(const struct ASTFunc *f, AsyncFrameLive *out) {
    if (!out) return -1;
    AsyncFrameLayout layout;
    if (async_liveness_layout_func(f, &layout) != 0) return -1;
    *out = layout.live;
    return 0;
}

/* Cap residual pure FILE* emit：.x 真迁；冷路径仍 seed C；FROM_X 时由 .x 提供 */
void async_liveness_emit_frame_typedef(const struct ASTFunc *f,
    const AsyncFrameLayout *layout, FILE *out) {
    if (!f || !layout || !out || layout->num_awaits <= 0) return;
    const char *tag = layout->frame_tag[0] ? layout->frame_tag : "__xlang_async_frame_fn";
    fprintf(out, "#ifndef XLANG_ASYNC_CPS_RT_DECL\n");
    fprintf(out, "#define XLANG_ASYNC_CPS_RT_DECL\n");
    fprintf(out, "extern int xlang_async_cps_suspend(int32_t *phase, int32_t next_phase);\n");
    fprintf(out, "extern int xlang_async_cps_suspend_io(int32_t *phase, int32_t next_phase);\n");
    fprintf(out, "extern int xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle);\n");
    fprintf(out, "extern int32_t xlang_io_complete_read_async(void);\n");
    fprintf(out, "extern int32_t xlang_io_complete_read_async_slot(int slot);\n");
    fprintf(out, "extern int xlang_io_submit_write_async(const uint8_t *ptr, size_t len, size_t handle);\n");
    fprintf(out, "extern int32_t xlang_io_complete_write_async(void);\n");
    fprintf(out, "extern int32_t xlang_io_complete_write_async_slot(int slot);\n");
    fprintf(out, "extern void xlang_async_run_seed_reset(void);\n");
    fprintf(out, "extern void xlang_async_run_seed_push_i32(int32_t v);\n");
    fprintf(out, "extern void xlang_async_run_seed_push_u32(uint32_t v);\n");
    fprintf(out, "extern void xlang_async_run_seed_push_i64(int64_t v);\n");
    fprintf(out, "extern void xlang_async_run_seed_push_usize(size_t v);\n");
    fprintf(out, "extern void xlang_async_run_seed_set_i32(int32_t v);\n");
    fprintf(out, "extern int xlang_async_run_seed_valid(void);\n");
    fprintf(out, "extern int32_t xlang_async_run_seed_take_i32(void);\n");
    fprintf(out, "extern uint32_t xlang_async_run_seed_take_u32(void);\n");
    fprintf(out, "extern int64_t xlang_async_run_seed_take_i64(void);\n");
    fprintf(out, "extern size_t xlang_async_run_seed_take_usize(void);\n");
    fprintf(out, "extern int xlang_async_task_submit(int32_t (*fn)(void));\n");
    fprintf(out, "extern int32_t xlang_async_run_drain_until_idle(void);\n");
    fprintf(out, "extern void xlang_async_queue_reset(void);\n");
    fprintf(out, "extern unsigned xlang_io_poll_async_completions(unsigned timeout_ms);\n");
    fprintf(out, "#define XLANG_ASYNC_SUSPENDED ((int32_t)0x41535700)\n");
    fprintf(out, "#define XLANG_IO_ASYNC_NOT_READY ((int32_t)-2)\n");
    fprintf(out, "#endif\n");
    fprintf(out, "typedef struct %s {\n", tag);
    fprintf(out, "  int32_t __phase;\n");
    if (layout->has_io_rd_slot)
        fprintf(out, "  int32_t __io_rd_slot;\n");
    if (layout->has_io_wr_slot)
        fprintf(out, "  int32_t __io_wr_slot;\n");
    for (int i = 0; i < layout->live.n; i++) {
        char cty[96];
        const struct ASTType *ty = async_liveness_lookup_var_type(f, layout->live.names[i]);
        async_liveness_type_to_c_buf(ty, cty, sizeof(cty));
        fprintf(out, "  %s %s;\n", cty, layout->live.names[i]);
    }
    fprintf(out, "} %s;\n", tag);
}

void async_liveness_emit_frame_local(const struct ASTFunc *f,
    const AsyncFrameLayout *layout, FILE *out) {
    if (!f || !layout || !out || layout->num_awaits <= 0) return;
    const char *tag = layout->frame_tag[0] ? layout->frame_tag : "__xlang_async_frame_fn";
    fprintf(out, "  static %s __xlang_frame;\n", tag);
}

void async_liveness_emit_codegen_comment(const struct ASTFunc *f,
    const AsyncFrameLayout *layout, FILE *out) {
    if (!f || !layout || !out) return;
    const char *fn = (f->name && f->name[0]) ? f->name : "?";
    fprintf(out, "  /* XLANG_ASYNC_FRAME func=%s slots=%d bytes=%d awaits=%d",
        fn, layout->live.n, layout->frame_bytes, layout->num_awaits);
    if (layout->has_io_rd_slot || layout->has_io_wr_slot) {
        fprintf(out, " io_slots=");
        if (layout->has_io_rd_slot)
            fputs("rd", out);
        if (layout->has_io_wr_slot) {
            if (layout->has_io_rd_slot)
                fputc('+', out);
            fputs("wr", out);
        }
    }
    if (layout->live.n > 0) {
        fprintf(out, " vars=");
        for (int i = 0; i < layout->live.n; i++) {
            if (i) fputc(',', out);
            fputs(layout->live.names[i], out);
        }
    }
    fprintf(out, " tag=%s", layout->frame_tag[0] ? layout->frame_tag : "?");
    fputs(" */\n", out);
}
#endif /* !XLANG_ASYNC_LIVENESS_FROM_X */

/* G.7 Cap residual：module-local async_liveness_fputs removed.
 * .x emit pure calls driver_preamble_fputs (authority in runtime_driver_abi seed).
 * Cold full C path (no FROM_X) uses FILE* fputs directly in emit_* above.
 * PLATFORM: SHARED — single opaque FILE* fputs authority. */
