/**
 * typeck.c — 类型检查实现
 *
 * 文件职责：实现 typeck.h 声明的 typeck_module，对 AST 做类型校验（main 返回 i32；if/while/for 条件须为 bool，禁止整型隐式转 bool；库模块放行）。
 * 所属模块：编译器前端 typeck，compiler/src/typeck/；实现 typeck.h。
 * 与其它文件的关系：依赖 include/ast.h；被 main 在 parse 之后调用；不修改 AST。
 * 重要约定：类型与变量规则以 analysis/变量类型与类型系统设计.md 为准（§4 基础标量、§九 衔接建议）；后续阶段可在此扩展 struct 布局与泛型、trait 等检查。
 */

#include "typeck/typeck.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>

/** 符号表：names[0..n) 为当前作用域内 const/let 名称（const 在前）；type_kinds[i] 为对应类型；type_names[i] 为 NAMED 类型名（结构体名等）。 */
#define MAX_SYMTAB 64

/**
 * 按名称查找结构体定义；用于字段访问与结构体字面量校验。
 * 参数：defs 结构体定义数组；num 长度；name 类型名。返回值：找到返回该 ASTStructDef*，否则 NULL。
 */
static const struct ASTStructDef *find_struct_def(struct ASTStructDef **defs, int num, const char *name) {
    if (!defs || !name) return NULL;
    for (int i = 0; i < num; i++)
        if (defs[i] && defs[i]->name && strcmp(defs[i]->name, name) == 0) return defs[i];
    return NULL;
}

/**
 * 返回类型的对齐要求（字节）；用于结构体布局算法（变量类型与类型系统设计 §11.1）。
 * 参数：ty 字段类型；struct_defs/num_structs 已计算过布局的结构体（仅 NAMED 时使用）。返回值：对齐字节数，无法确定时返回 1。
 */
static int type_align_of(const struct ASTType *ty, struct ASTStructDef **struct_defs, int num_structs) {
    if (!ty) return 1;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_BOOL: return 4;
        case AST_TYPE_U8: return 1;
        case AST_TYPE_I64: case AST_TYPE_U64: case AST_TYPE_USIZE: case AST_TYPE_ISIZE: return 8;
        case AST_TYPE_PTR: return 8;
        case AST_TYPE_SLICE: return 8;  /* 对齐与指针一致 */
        case AST_TYPE_ARRAY:
            return ty->elem_type ? type_align_of(ty->elem_type, struct_defs, num_structs) : 1;
        case AST_TYPE_NAMED: {
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, ty->name);
            return (sd && sd->struct_align > 0) ? sd->struct_align : 1;
        }
        default: return 1;
    }
}

/**
 * 返回类型的大小（字节）；用于结构体布局算法 §11.1。
 * 参数：同上。返回值：大小字节数，无法确定时返回 0。
 */
static int type_size_of(const struct ASTType *ty, struct ASTStructDef **struct_defs, int num_structs) {
    if (!ty) return 0;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_BOOL: return 4;
        case AST_TYPE_U8: return 1;
        case AST_TYPE_I64: case AST_TYPE_U64: case AST_TYPE_USIZE: case AST_TYPE_ISIZE: return 8;
        case AST_TYPE_PTR: return 8;
        case AST_TYPE_SLICE: return 16;  /* C 侧为 { ptr, len }，两字 */
        case AST_TYPE_ARRAY: {
            int esz = ty->elem_type ? type_size_of(ty->elem_type, struct_defs, num_structs) : 0;
            return (ty->array_size > 0 && esz > 0) ? (ty->array_size * esz) : 0;
        }
        case AST_TYPE_NAMED: {
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, ty->name);
            return (sd && sd->struct_size > 0) ? sd->struct_size : 0;
        }
        default: return 0;
    }
}

/**
 * 对模块内所有结构体计算布局（字段偏移、总大小、对齐）；按定义顺序计算，NAMED 字段须引用已计算过的结构体（变量类型与类型系统设计 §11.1）。
 * 参数：struct_defs 顶层结构体数组；num_structs 长度。返回值：0 成功，-1 失败并已写 stderr。
 */
static int compute_struct_layouts(struct ASTStructDef **struct_defs, int num_structs) {
    if (!struct_defs || num_structs <= 0) return 0;
    for (int idx = 0; idx < num_structs; idx++) {
        struct ASTStructDef *sd = struct_defs[idx];
        if (!sd || !sd->fields || sd->num_fields <= 0) continue;
        int current_offset = 0;
        int max_align = 1;
        for (int i = 0; i < sd->num_fields && i < AST_STRUCT_MAX_FIELDS; i++) {
            const struct ASTType *fty = sd->fields[i].type;
            if (!fty) { sd->field_offsets[i] = current_offset; continue; }
            int A = type_align_of(fty, struct_defs, num_structs);
            if (A <= 0) A = 1;
            int gap = (A - (current_offset % A)) % A;
            /* 当前阶段默认允许隐式 padding，仅做布局计算；后续可加 allow(padding) 属性并在此报错 */
            current_offset += gap;
            sd->field_offsets[i] = current_offset;
            int fsize = type_size_of(fty, struct_defs, num_structs);
            if (fsize <= 0) {
                fprintf(stderr, "typeck error: struct '%s' field '%s' has unknown or invalid type size\n",
                    sd->name ? sd->name : "?", sd->fields[i].name ? sd->fields[i].name : "?");
                return -1;
            }
            current_offset += fsize;
            if (A > max_align) max_align = A;
        }
        /* 末尾对齐 */
        if (max_align > 0 && (current_offset % max_align) != 0)
            current_offset += (max_align - (current_offset % max_align));
        sd->struct_size = current_offset;
        sd->struct_align = max_align;
    }
    return 0;
}

/**
 * 判断表达式是否产生 bool 类型（用于 if/while 条件；禁止整型隐式转 bool）。
 * 参数：e 表达式；names 符号表；type_kinds 各符号类型（与 names 平行）；n 数量。
 * 返回值：1 表示产生 bool，0 表示否（如整型字面量或整型变量）。
 */
static int expr_produces_bool(const struct ASTExpr *e, const char **names,
    const int *type_kinds, int n) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_BOOL_LIT:
            return 1;
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE:
            return 1;  /* 比较运算产生 bool */
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            return expr_produces_bool(e->value.binop.left, names, type_kinds, n)
                && expr_produces_bool(e->value.binop.right, names, type_kinds, n);
        case AST_EXPR_LOGNOT:
            return expr_produces_bool(e->value.unary.operand, names, type_kinds, n);
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n; i++) {
                if (names[i] && name && strcmp(names[i], name) == 0 && type_kinds && i < n)
                    return (type_kinds[i] == AST_TYPE_BOOL);
            }
            return 0;  /* 未定义或非 bool 变量 */
        }
        default:
            return 0;
    }
}

/**
 * 判断表达式是否为常量表达式（仅字面量、或引用已定义 const 的 VAR、或二者的运算）。
 * 参数：e 表达式；names 已定义 const 名列表；n 数量。返回值：1 是常量表达式，0 否。
 */
static int is_const_expr(const struct ASTExpr *e, const char **names, int n) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_LIT:
        case AST_EXPR_BOOL_LIT:
            return 1;
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n; i++)
                if (names[i] && name && strcmp(names[i], name) == 0) return 1;
            return 0;
        }
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            return is_const_expr(e->value.binop.left, names, n) && is_const_expr(e->value.binop.right, names, n);
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            return is_const_expr(e->value.unary.operand, names, n);
        case AST_EXPR_IF:
            return 0;  /* if 表达式非常量 */
        default:
            return 0;
    }
}

/**
 * 获取表达式类型（用于字段访问、下标校验）：VAR 查符号表；FIELD_ACCESS 取字段类型；INDEX 取数组元素类型。
 * 参数：type_ptrs 与 names 平行，存各符号的 ASTType*，用于解析 ARRAY 的 elem_type；out_elem_type 仅当表达式为数组时写入。
 * 返回值：0 成功并写入 out_*；-1 无法确定类型。
 */
static int get_expr_type(const struct ASTExpr *e, const char **names, const int *type_kinds,
    const char **type_names, int n, const struct ASTType **type_ptrs,
    struct ASTStructDef **struct_defs, int num_structs,
    int *out_kind, const char **out_name, const struct ASTType **out_elem_type) {
    if (!e || !out_kind || !out_name) return -1;
    *out_name = NULL;
    if (out_elem_type) *out_elem_type = NULL;
    if (e->kind == AST_EXPR_VAR) {
        const char *name = e->value.var.name;
        for (int i = 0; i < n; i++)
            if (names[i] && name && strcmp(names[i], name) == 0) {
                *out_kind = type_kinds[i];
                *out_name = (type_names && i < n) ? type_names[i] : NULL;
                if (out_elem_type && type_ptrs && i < n && type_ptrs[i] && type_ptrs[i]->elem_type &&
                    (type_ptrs[i]->kind == AST_TYPE_ARRAY || type_ptrs[i]->kind == AST_TYPE_SLICE))
                    *out_elem_type = type_ptrs[i]->elem_type;
                return 0;
            }
        return -1;
    }
    if (e->kind == AST_EXPR_FIELD_ACCESS) {
        int base_kind;
        const char *base_name = NULL;
        if (get_expr_type(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, &base_kind, &base_name, NULL) != 0) return -1;
        if (base_kind != AST_TYPE_NAMED || !base_name) return -1;
        const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, base_name);
        if (!sd) return -1;
        const char *field = e->value.field_access.field_name;
        for (int i = 0; i < sd->num_fields; i++)
            if (sd->fields[i].name && field && strcmp(sd->fields[i].name, field) == 0) {
                *out_kind = sd->fields[i].type->kind;
                *out_name = sd->fields[i].type->name;
                return 0;
            }
        return -1;
    }
    if (e->kind == AST_EXPR_INDEX) {
        int base_kind;
        const char *base_name = NULL;
        const struct ASTType *base_elem = NULL;
        if (get_expr_type(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, &base_kind, &base_name, &base_elem) != 0) return -1;
        if ((base_kind != AST_TYPE_ARRAY && base_kind != AST_TYPE_SLICE) || !base_elem) {
            fprintf(stderr, "typeck error: subscript base must be array or slice type\n");
            return -1;
        }
        *out_kind = base_elem->kind;
        *out_name = base_elem->name;
        return 0;
    }
    return -1;
}

/**
 * 对单棵表达式做类型检查；VAR 须在符号表 names[0..n) 中已定义；break/continue 仅允许在循环体内；FIELD_ACCESS/STRUCT_LIT/ARRAY_LIT/INDEX 须与类型一致。
 * 参数：type_ptrs 与 names 平行，存各符号的 ASTType*，用于 INDEX 校验数组元素类型。
 * 返回值：0 通过，-1 非法并已写 stderr。
 */
static int typeck_expr_sym(const struct ASTExpr *e, const char **names,
    const int *type_kinds, const char **type_names, int n, const struct ASTType **type_ptrs,
    int inside_loop, struct ASTStructDef **struct_defs, int num_structs) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_BREAK:
        case AST_EXPR_CONTINUE:
            if (!inside_loop) {
                fprintf(stderr, "typeck error: '%s' only allowed inside a loop\n",
                    e->kind == AST_EXPR_BREAK ? "break" : "continue");
                return -1;
            }
            return 0;
        case AST_EXPR_RETURN:
            return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs);
        case AST_EXPR_LIT:
        case AST_EXPR_BOOL_LIT:
            return 0;
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n; i++)
                if (names[i] && name && strcmp(names[i], name) == 0) return 0;
            fprintf(stderr, "typeck error: undefined name '%s'\n", name ? name : "");
            return -1;
        }
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            if (typeck_expr_sym(e->value.binop.left, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            if (typeck_expr_sym(e->value.binop.right, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            return 0;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs);
        case AST_EXPR_IF:
            if (typeck_expr_sym(e->value.if_expr.cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            if (!expr_produces_bool(e->value.if_expr.cond, names, type_kinds, n)) {
                fprintf(stderr, "typeck error: if condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
            if (typeck_expr_sym(e->value.if_expr.then_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            if (e->value.if_expr.else_expr && typeck_expr_sym(e->value.if_expr.else_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            return 0;
        case AST_EXPR_PANIC:
            if (e->value.unary.operand)
                return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs);
            return 0;
        case AST_EXPR_MATCH: {
            if (typeck_expr_sym(e->value.match_expr.matched_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++) {
                if (typeck_expr_sym(e->value.match_expr.arms[i].result, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            }
            return 0;
        }
        case AST_EXPR_FIELD_ACCESS: {
            if (typeck_expr_sym(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            int base_kind;
            const char *base_name = NULL;
            if (get_expr_type(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, &base_kind, &base_name, NULL) != 0) {
                fprintf(stderr, "typeck error: field access base has no struct type\n");
                return -1;
            }
            if (base_kind != AST_TYPE_NAMED || !base_name) {
                fprintf(stderr, "typeck error: field access requires struct type\n");
                return -1;
            }
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, base_name);
            if (!sd) {
                fprintf(stderr, "typeck error: unknown struct type '%s'\n", base_name);
                return -1;
            }
            const char *field = e->value.field_access.field_name;
            for (int i = 0; i < sd->num_fields; i++)
                if (sd->fields[i].name && field && strcmp(sd->fields[i].name, field) == 0) return 0;
            fprintf(stderr, "typeck error: struct '%s' has no field '%s'\n", base_name, field ? field : "");
            return -1;
        }
        case AST_EXPR_STRUCT_LIT: {
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, e->value.struct_lit.struct_name);
            if (!sd) {
                fprintf(stderr, "typeck error: unknown struct type '%s'\n", e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "");
                return -1;
            }
            if (e->value.struct_lit.num_fields != sd->num_fields) {
                fprintf(stderr, "typeck error: struct literal field count mismatch for '%s'\n", sd->name);
                return -1;
            }
            for (int i = 0; i < sd->num_fields; i++) {
                if (!e->value.struct_lit.field_names[i] || !sd->fields[i].name ||
                    strcmp(e->value.struct_lit.field_names[i], sd->fields[i].name) != 0) {
                    fprintf(stderr, "typeck error: struct literal field name mismatch at %d\n", i);
                    return -1;
                }
                if (typeck_expr_sym(e->value.struct_lit.inits[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            }
            return 0;
        }
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++) {
                if (typeck_expr_sym(e->value.array_lit.elems[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            }
            return 0;
        case AST_EXPR_INDEX: {
            if (typeck_expr_sym(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            if (typeck_expr_sym(e->value.index.index_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            int base_kind;
            const char *base_name = NULL;
            if (get_expr_type(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, &base_kind, &base_name, NULL) != 0) {
                fprintf(stderr, "typeck error: subscript base must be array or slice\n");
                return -1;
            }
            if (base_kind != AST_TYPE_ARRAY && base_kind != AST_TYPE_SLICE) {
                fprintf(stderr, "typeck error: subscript base must be array or slice type\n");
                return -1;
            }
            ((struct ASTExpr *)e)->value.index.base_is_slice = (base_kind == AST_TYPE_SLICE);
            return 0;
        }
        default:
            fprintf(stderr, "typeck error: unsupported expression kind\n");
            return -1;
    }
}

/**
 * 对块做类型检查；parent_names/parent_type_kinds/parent_type_names/parent_n 为外层符号表（顶层传 NULL,NULL,NULL,0）；inside_loop 表示当前块是否为某 while 体；struct_defs/num_structs 为顶层结构体定义。
 */
static int typeck_block(const struct ASTBlock *b, const char **parent_names,
    const int *parent_type_kinds, const char **parent_type_names, const struct ASTType **parent_type_ptrs, int parent_n, int inside_loop,
    struct ASTStructDef **struct_defs, int num_structs) {
    if (!b) return -1;
    if (!b->final_expr && b->num_labeled_stmts == 0) return -1;
    const char *names[MAX_SYMTAB];
    int type_kinds[MAX_SYMTAB];
    const char *type_names[MAX_SYMTAB];
    const struct ASTType *type_ptrs[MAX_SYMTAB];
    int n = parent_n < MAX_SYMTAB ? parent_n : 0;
    for (int i = 0; i < n && parent_names; i++) {
        names[i] = parent_names[i];
        type_kinds[i] = (parent_type_kinds && i < parent_n) ? parent_type_kinds[i] : AST_TYPE_I32;
        type_names[i] = (parent_type_names && i < parent_n) ? parent_type_names[i] : NULL;
        type_ptrs[i] = (parent_type_ptrs && i < parent_n) ? parent_type_ptrs[i] : NULL;
    }
    int n_consts = n;
    for (int i = 0; i < b->num_consts; i++) {
        if (n >= MAX_SYMTAB) {
            fprintf(stderr, "typeck error: too many declarations\n");
            return -1;
        }
        if (!is_const_expr(b->const_decls[i].init, names, n_consts)) {
            fprintf(stderr, "typeck error: const init must be constant expression\n");
            return -1;
        }
        if (typeck_expr_sym(b->const_decls[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->const_decls[i].init->value.array_lit.num_elems != b->const_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: array literal length must match declaration size\n");
                return -1;
            }
        }
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_SLICE &&
            b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_VAR) {
            const char *vname = b->const_decls[i].init->value.var.name;
            int j;
            for (j = 0; j < n && (!names[j] || !vname || strcmp(names[j], vname) != 0); j++) ;
            if (j >= n || !type_ptrs[j] || type_ptrs[j]->kind != AST_TYPE_ARRAY || !type_ptrs[j]->elem_type ||
                !b->const_decls[i].type->elem_type ||
                type_ptrs[j]->elem_type->kind != b->const_decls[i].type->elem_type->kind ||
                (type_ptrs[j]->elem_type->kind == AST_TYPE_NAMED && (!type_ptrs[j]->elem_type->name || !b->const_decls[i].type->elem_type->name || strcmp(type_ptrs[j]->elem_type->name, b->const_decls[i].type->elem_type->name) != 0))) {
                fprintf(stderr, "typeck error: slice init must be array variable with matching element type\n");
                return -1;
            }
        }
        type_kinds[n] = b->const_decls[i].type ? b->const_decls[i].type->kind : AST_TYPE_I32;
        type_names[n] = (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_NAMED) ? b->const_decls[i].type->name : NULL;
        type_ptrs[n] = b->const_decls[i].type;
        names[n++] = b->const_decls[i].name;
        n_consts = n;
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (n >= MAX_SYMTAB) {
            fprintf(stderr, "typeck error: too many declarations\n");
            return -1;
        }
        if (typeck_expr_sym(b->let_decls[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->let_decls[i].init->value.array_lit.num_elems != b->let_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: array literal length must match declaration size\n");
                return -1;
            }
        }
        /* 切片可从数组变量初始化：init 为 VAR 且该变量类型为 ARRAY，elem_type 须与切片一致 */
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_SLICE &&
            b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_VAR) {
            const char *vname = b->let_decls[i].init->value.var.name;
            int j;
            for (j = 0; j < n && (!names[j] || !vname || strcmp(names[j], vname) != 0); j++) ;
            if (j >= n || !type_ptrs[j] || type_ptrs[j]->kind != AST_TYPE_ARRAY || !type_ptrs[j]->elem_type ||
                !b->let_decls[i].type->elem_type ||
                type_ptrs[j]->elem_type->kind != b->let_decls[i].type->elem_type->kind ||
                (type_ptrs[j]->elem_type->kind == AST_TYPE_NAMED && (!type_ptrs[j]->elem_type->name || !b->let_decls[i].type->elem_type->name || strcmp(type_ptrs[j]->elem_type->name, b->let_decls[i].type->elem_type->name) != 0))) {
                fprintf(stderr, "typeck error: slice init must be array variable with matching element type\n");
                return -1;
            }
        }
        type_kinds[n] = b->let_decls[i].type ? b->let_decls[i].type->kind : AST_TYPE_I32;
        type_names[n] = (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_NAMED) ? b->let_decls[i].type->name : NULL;
        type_ptrs[n] = b->let_decls[i].type;
        names[n++] = b->let_decls[i].name;
    }
    for (int i = 0; i < b->num_loops; i++) {
        if (typeck_expr_sym(b->loops[i].cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        if (!expr_produces_bool(b->loops[i].cond, names, type_kinds, n)) {
            fprintf(stderr, "typeck error: while condition must be bool (no implicit int-to-bool)\n");
            return -1;
        }
        if (typeck_block(b->loops[i].body, names, type_kinds, type_names, type_ptrs, n, 1, struct_defs, num_structs) != 0) return -1;
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init && typeck_expr_sym(b->for_loops[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        if (b->for_loops[i].cond) {
            if (typeck_expr_sym(b->for_loops[i].cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
            if (!expr_produces_bool(b->for_loops[i].cond, names, type_kinds, n)) {
                fprintf(stderr, "typeck error: for condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
        }
        if (b->for_loops[i].step && typeck_expr_sym(b->for_loops[i].step, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        if (typeck_block(b->for_loops[i].body, names, type_kinds, type_names, type_ptrs, n, 1, struct_defs, num_structs) != 0) return -1;
    }
    for (int i = 0; i < b->num_defers; i++) {
        if (typeck_block(b->defer_blocks[i], names, type_kinds, type_names, type_ptrs, n, inside_loop, struct_defs, num_structs) != 0) return -1;
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr) {
            if (typeck_expr_sym(b->labeled_stmts[i].u.return_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs) != 0) return -1;
        }
    }
    if (!b->final_expr) return 0;
    return typeck_expr_sym(b->final_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs);
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

    if (!m->main_func->return_type || m->main_func->return_type->kind != AST_TYPE_I32) {
        fprintf(stderr, "typeck error: main must return i32\n");
        return -1;
    }

    if (!m->main_func->body) {
        fprintf(stderr, "typeck error: main must have a body (block)\n");
        return -1;
    }

    /* 结构体布局计算（§11.1）：字段偏移、总大小、对齐，供后续 codegen 使用 size_of/offset_of */
    if (m->struct_defs && m->num_structs > 0 && compute_struct_layouts(m->struct_defs, m->num_structs) != 0)
        return -1;

    /* 块内 const/let、while、final_expr 类型检查（顶层块非循环体）；传入顶层结构体定义供字段访问与结构体字面量校验 */
    return typeck_block(m->main_func->body, NULL, NULL, NULL, NULL, 0, 0, m->struct_defs, m->num_structs);
}
