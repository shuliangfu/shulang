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
#include <stdlib.h>
#include <string.h>

/** 符号表：names[0..n) 为当前作用域内 const/let 名称（const 在前）；type_kinds[i] 为对应类型；type_names[i] 为 NAMED 类型名（结构体名等）。 */
#define MAX_SYMTAB 64

/** 字面量默认类型，用于设置 resolved_type 以便函数调用实参匹配 */
static struct ASTType static_type_i32 = { AST_TYPE_I32, NULL, NULL, 0 };
static struct ASTType static_type_i64 = { AST_TYPE_I64, NULL, NULL, 0 };
static struct ASTType static_type_f64 = { AST_TYPE_F64, NULL, NULL, 0 };
static struct ASTType static_type_bool = { AST_TYPE_BOOL, NULL, NULL, 0 };
/** 切片 .len 字段类型（与 C 侧 size_t 对应） */
static struct ASTType static_type_usize = { AST_TYPE_USIZE, NULL, NULL, 0 };

/** 当前 typeck 的依赖模块列表（与 m->import_paths 顺序一致），供 CALL 跨模块解析；由 typeck_module 设置。 */
static struct ASTModule **typeck_dep_mods;
static int typeck_num_deps;

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
 * 按名称查找枚举定义；用于枚举值 Name::Variant 校验（§7.4）。
 * 参数：defs 枚举定义数组；num 长度；name 类型名。返回值：找到返回该 ASTEnumDef*，否则 NULL。
 */
static const struct ASTEnumDef *find_enum_def(struct ASTEnumDef **defs, int num, const char *name) {
    if (!defs || !name) return NULL;
    for (int i = 0; i < num; i++)
        if (defs[i] && defs[i]->name && strcmp(defs[i]->name, name) == 0) return defs[i];
    return NULL;
}

/** 按名称查找 trait 定义；用于 impl 校验（阶段 7.2）。 */
static const struct ASTTraitDef *find_trait_def(struct ASTTraitDef **defs, int num, const char *name) {
    if (!defs || !name) return NULL;
    for (int i = 0; i < num; i++)
        if (defs[i] && defs[i]->name && strcmp(defs[i]->name, name) == 0) return defs[i];
    return NULL;
}

/**
 * 判断两个类型是否相等（用于函数调用实参与形参匹配）；NAMED 比较 name，PTR/ARRAY/SLICE/VECTOR 递归 elem_type。
 */
static int type_equal(const struct ASTType *a, const struct ASTType *b) {
    if (!a || !b) return (a == b);
    if (a->kind != b->kind) return 0;
    if (a->kind == AST_TYPE_NAMED) {
        if (!a->name && !b->name) return 1;
        return (a->name && b->name && strcmp(a->name, b->name) == 0);
    }
    if (a->kind == AST_TYPE_PTR || a->kind == AST_TYPE_SLICE || a->kind == AST_TYPE_VECTOR)
        return type_equal(a->elem_type, b->elem_type);
    if (a->kind == AST_TYPE_ARRAY)
        return a->array_size == b->array_size && type_equal(a->elem_type, b->elem_type);
    return 1;
}

/**
 * 判断实参类型 arg_type 是否与形参类型 param_type 在代入泛型实参后一致。
 * 用于泛型调用 f<Type>(args) 的实参与形参匹配；gp_names/type_args 为泛型参数名与类型实参。
 * 若 param_type 为泛型参数名（NAMED 且 name 在 gp_names 中），则与对应 type_args[i] 比较；
 * PTR/ARRAY/SLICE/VECTOR 递归 elem_type；否则退化为 type_equal。
 */
static int type_equal_subst(const struct ASTType *param_type, const struct ASTType *arg_type,
    char **gp_names, struct ASTType **type_args, int num_gp) {
    if (!param_type || !arg_type) return (param_type == arg_type);
    if (param_type->kind == AST_TYPE_NAMED && gp_names && type_args && num_gp > 0) {
        for (int i = 0; i < num_gp; i++)
            if (param_type->name && gp_names[i] && strcmp(param_type->name, gp_names[i]) == 0)
                return type_equal(arg_type, type_args[i]);
    }
    if (param_type->kind != arg_type->kind) return 0;
    if (param_type->kind == AST_TYPE_PTR || param_type->kind == AST_TYPE_SLICE || param_type->kind == AST_TYPE_VECTOR)
        return type_equal_subst(param_type->elem_type, arg_type->elem_type, gp_names, type_args, num_gp);
    if (param_type->kind == AST_TYPE_ARRAY)
        return param_type->array_size == arg_type->array_size
            && type_equal_subst(param_type->elem_type, arg_type->elem_type, gp_names, type_args, num_gp);
    return type_equal(param_type, arg_type);
}

/**
 * 返回泛型函数 return_type 在代入 type_args 后的类型指针（仅支持顶层 NAMED 泛型参数，如 -> T）。
 * 用于设置泛型调用表达式的 resolved_type；不分配新节点，返回的为 type_args[i] 或 return_type 自身。
 */
static const struct ASTType *get_substituted_return_type(const struct ASTType *return_type,
    char **gp_names, struct ASTType **type_args, int num_gp) {
    if (!return_type || !gp_names || !type_args || num_gp <= 0) return return_type;
    if (return_type->kind == AST_TYPE_NAMED && return_type->name) {
        for (int i = 0; i < num_gp; i++)
            if (gp_names[i] && strcmp(return_type->name, gp_names[i]) == 0)
                return type_args[i];
    }
    return return_type;
}

/** 将类型转为用于 impl 查找的名字串（i32/bool/NAMED 等）；用于方法调用解析（阶段 7.2）。 */
static const char *type_to_name_string(const struct ASTType *ty) {
    if (!ty) return "";
    if (ty->kind == AST_TYPE_NAMED && ty->name) return ty->name;
    switch (ty->kind) {
        case AST_TYPE_I32:   return "i32";
        case AST_TYPE_BOOL:  return "bool";
        case AST_TYPE_U8:    return "u8";
        case AST_TYPE_U32:   return "u32";
        case AST_TYPE_U64:   return "u64";
        case AST_TYPE_I64:   return "i64";
        case AST_TYPE_USIZE: return "usize";
        case AST_TYPE_ISIZE: return "isize";
        case AST_TYPE_F32:   return "f32";
        case AST_TYPE_F64:   return "f64";
        default: break;
    }
    return "";
}

/**
 * 在枚举定义中按变体名查找 0-based 序号；用于 match 枚举分支（§7.4）。
 * 参数：ed 枚举定义；variant_name 变体名。返回值：序号（>=0）或 -1 表示未找到。
 */
static int enum_variant_index(const struct ASTEnumDef *ed, const char *variant_name) {
    if (!ed || !variant_name) return -1;
    for (int i = 0; i < ed->num_variants; i++)
        if (ed->variant_names[i] && strcmp(ed->variant_names[i], variant_name) == 0) return i;
    return -1;
}

/**
 * 返回类型的对齐要求（字节）；用于结构体布局算法（变量类型与类型系统设计 §11.1）。
 * 参数：ty 字段类型；struct_defs/num_structs 已计算过布局的结构体；enum_defs/num_enums 枚举（NAMED 时可能为枚举）。返回值：对齐字节数，无法确定时返回 1。
 */
static int type_align_of(const struct ASTType *ty, struct ASTStructDef **struct_defs, int num_structs,
    struct ASTEnumDef **enum_defs, int num_enums) {
    if (!ty) return 1;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_BOOL: return 4;
        case AST_TYPE_F32: return 4;
        case AST_TYPE_F64: return 8;
        case AST_TYPE_U8: return 1;
        case AST_TYPE_I64: case AST_TYPE_U64: case AST_TYPE_USIZE: case AST_TYPE_ISIZE: return 8;
        case AST_TYPE_PTR: return 8;
        case AST_TYPE_SLICE: return 8;  /* 对齐与指针一致 */
        case AST_TYPE_ARRAY:
            return ty->elem_type ? type_align_of(ty->elem_type, struct_defs, num_structs, enum_defs, num_enums) : 1;
        case AST_TYPE_VECTOR:
            return ty->elem_type ? type_align_of(ty->elem_type, struct_defs, num_structs, enum_defs, num_enums) : 1;
        case AST_TYPE_NAMED: {
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, ty->name);
            if (sd && sd->struct_align > 0) return sd->struct_align;
            if (find_enum_def(enum_defs, num_enums, ty->name)) return 4;  /* 枚举按 int 对齐 */
            return 1;
        }
        default: return 1;
    }
}

/**
 * 返回类型的大小（字节）；用于结构体布局算法 §11.1。
 * 参数：同上。返回值：大小字节数，无法确定时返回 0。
 */
static int type_size_of(const struct ASTType *ty, struct ASTStructDef **struct_defs, int num_structs,
    struct ASTEnumDef **enum_defs, int num_enums) {
    if (!ty) return 0;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_BOOL: return 4;
        case AST_TYPE_F32: return 4;
        case AST_TYPE_F64: return 8;
        case AST_TYPE_U8: return 1;
        case AST_TYPE_I64: case AST_TYPE_U64: case AST_TYPE_USIZE: case AST_TYPE_ISIZE: return 8;
        case AST_TYPE_PTR: return 8;
        case AST_TYPE_SLICE: return 16;  /* C 侧为 { ptr, len }，两字 */
        case AST_TYPE_ARRAY: {
            int esz = ty->elem_type ? type_size_of(ty->elem_type, struct_defs, num_structs, enum_defs, num_enums) : 0;
            return (ty->array_size > 0 && esz > 0) ? (ty->array_size * esz) : 0;
        }
        case AST_TYPE_VECTOR: {
            int esz = ty->elem_type ? type_size_of(ty->elem_type, struct_defs, num_structs, enum_defs, num_enums) : 0;
            return (ty->array_size > 0 && esz > 0) ? (ty->array_size * esz) : 0;
        }
        case AST_TYPE_NAMED: {
            const struct ASTStructDef *sd = find_struct_def(struct_defs, num_structs, ty->name);
            if (sd && sd->struct_size > 0) return sd->struct_size;
            if (find_enum_def(enum_defs, num_enums, ty->name)) return 4;  /* 枚举按 int */
            return 0;
        }
        default: return 0;
    }
}

/**
 * 对模块内所有结构体计算布局（字段偏移、总大小、对齐）；按定义顺序计算，NAMED 字段须引用已计算过的结构体（变量类型与类型系统设计 §11.1）。
 * 参数：struct_defs/num_structs 顶层结构体；enum_defs/num_enums 枚举（用于 NAMED 字段为枚举时）。返回值：0 成功，-1 失败并已写 stderr。
 */
static int compute_struct_layouts(struct ASTStructDef **struct_defs, int num_structs,
    struct ASTEnumDef **enum_defs, int num_enums) {
    if (!struct_defs || num_structs <= 0) return 0;
    for (int idx = 0; idx < num_structs; idx++) {
        struct ASTStructDef *sd = struct_defs[idx];
        if (!sd || !sd->fields || sd->num_fields <= 0) continue;
        int current_offset = 0;
        int max_align = 1;
        for (int i = 0; i < sd->num_fields && i < AST_STRUCT_MAX_FIELDS; i++) {
            const struct ASTType *fty = sd->fields[i].type;
            if (!fty) { sd->field_offsets[i] = current_offset; continue; }
            int A = type_align_of(fty, struct_defs, num_structs, enum_defs, num_enums);
            if (A <= 0) A = 1;
            int gap = (A - (current_offset % A)) % A;
            /* Zero-Padding 强制校验（§11.1）：存在隐式 padding 且未标记 allow(padding) 则报错 */
            if (gap > 0 && !sd->allow_padding) {
                fprintf(stderr, "typeck error: struct '%s' has %d byte(s) implicit padding before field '%s'; add explicit padding field or allow(padding)\n",
                    sd->name ? sd->name : "?", gap, sd->fields[i].name ? sd->fields[i].name : "?");
                return -1;
            }
            current_offset += gap;
            sd->field_offsets[i] = current_offset;
            int fsize = type_size_of(fty, struct_defs, num_structs, enum_defs, num_enums);
            if (fsize <= 0) {
                fprintf(stderr, "typeck error: struct '%s' field '%s' has unknown or invalid type size\n",
                    sd->name ? sd->name : "?", sd->fields[i].name ? sd->fields[i].name : "?");
                return -1;
            }
            current_offset += fsize;
            if (A > max_align) max_align = A;
        }
        /* 末尾对齐；若存在末尾空隙且未标记 allow(padding) 则报错（§11.1 Zero-Padding） */
        if (max_align > 0 && (current_offset % max_align) != 0) {
            int end_pad = max_align - (current_offset % max_align);
            if (end_pad > 0 && !sd->allow_padding) {
                fprintf(stderr, "typeck error: struct '%s' has %d byte(s) implicit trailing padding; add explicit padding field or allow(padding)\n",
                    sd->name ? sd->name : "?", end_pad);
                return -1;
            }
            current_offset += end_pad;
        }
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
        case AST_EXPR_FLOAT_LIT:
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
        case AST_EXPR_TERNARY:
        case AST_EXPR_ASSIGN:
            return 0;  /* if/三元/赋值 表达式非常量 */
        default:
            return 0;
    }
}

/**
 * 获取表达式类型（用于字段访问、下标校验）：VAR 查符号表；FIELD_ACCESS 取字段类型；INDEX 取数组元素类型；ENUM_VARIANT 为枚举类型。
 * 参数：type_ptrs 与 names 平行，存各符号的 ASTType*；out_elem_type 仅当表达式为数组时写入。
 * 返回值：0 成功并写入 out_*；-1 无法确定类型。
 */
static int get_expr_type(const struct ASTExpr *e, const char **names, const int *type_kinds,
    const char **type_names, int n, const struct ASTType **type_ptrs,
    struct ASTStructDef **struct_defs, int num_structs,
    struct ASTEnumDef **enum_defs, int num_enums,
    int *out_kind, const char **out_name, const struct ASTType **out_elem_type) {
    if (!e || !out_kind || !out_name) return -1;
    *out_name = NULL;
    if (out_elem_type) *out_elem_type = NULL;
    if (e->kind == AST_EXPR_FLOAT_LIT) {
        if (e->resolved_type) {
            *out_kind = e->resolved_type->kind;
            *out_name = e->resolved_type->name;
        } else {
            *out_kind = AST_TYPE_F64;
            *out_name = NULL;
        }
        return 0;
    }
    if (e->kind == AST_EXPR_ENUM_VARIANT) {
        *out_kind = AST_TYPE_NAMED;
        *out_name = e->value.enum_variant.enum_name;
        return 0;
    }
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
        /* Type.Variant 形式（typeck 已设 is_enum_variant）：类型为枚举名 */
        if (e->value.field_access.is_enum_variant && e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
            *out_kind = AST_TYPE_NAMED;
            *out_name = e->value.field_access.base->value.var.name;
            return 0;
        }
        int base_kind;
        const char *base_name = NULL;
        if (get_expr_type(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, NULL) != 0) return -1;
        /* 切片 []T 的 .len 字段：类型为 usize（C 侧 struct 的 len 为 size_t） */
        if (base_kind == AST_TYPE_SLICE) {
            const char *field = e->value.field_access.field_name;
            if (field && strcmp(field, "len") == 0) {
                *out_kind = AST_TYPE_USIZE;
                *out_name = NULL;
                return 0;
            }
            return -1;
        }
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
        if (get_expr_type(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, &base_elem) != 0) return -1;
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
 * 对单棵表达式做类型检查；VAR 须在符号表 names[0..n) 中已定义；break/continue 仅允许在循环体内；FIELD_ACCESS/STRUCT_LIT/ARRAY_LIT/INDEX 须与类型一致；CALL 须在模块函数表中找到并参数匹配。
 * 参数：type_ptrs 与 names 平行，存各符号的 ASTType*；m 为当前模块，用于 CALL 查找函数签名，可为 NULL。
 * 返回值：0 通过，-1 非法并已写 stderr。
 */
static int typeck_expr_sym(const struct ASTExpr *e, const char **names,
    const int *type_kinds, const char **type_names, int n, const struct ASTType **type_ptrs,
    int inside_loop, struct ASTStructDef **struct_defs, int num_structs,
    struct ASTEnumDef **enum_defs, int num_enums, const struct ASTModule *m) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_ENUM_VARIANT: {
            const struct ASTEnumDef *ed = find_enum_def(enum_defs, num_enums, e->value.enum_variant.enum_name);
            if (!ed) {
                fprintf(stderr, "typeck error: unknown enum type '%s'\n", e->value.enum_variant.enum_name ? e->value.enum_variant.enum_name : "?");
                return -1;
            }
            const char *v = e->value.enum_variant.variant_name;
            for (int i = 0; i < ed->num_variants; i++)
                if (ed->variant_names[i] && v && strcmp(ed->variant_names[i], v) == 0) return 0;
            fprintf(stderr, "typeck error: enum '%s' has no variant '%s'\n", ed->name ? ed->name : "?", v ? v : "?");
            return -1;
        }
        case AST_EXPR_BREAK:
        case AST_EXPR_CONTINUE:
            if (!inside_loop) {
                fprintf(stderr, "typeck error: '%s' only allowed inside a loop\n",
                    e->kind == AST_EXPR_BREAK ? "break" : "continue");
                return -1;
            }
            return 0;
        case AST_EXPR_RETURN:
            return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
        case AST_EXPR_LIT:
            ((struct ASTExpr *)e)->resolved_type = &static_type_i32;
            return 0;
        case AST_EXPR_BOOL_LIT:
            ((struct ASTExpr *)e)->resolved_type = &static_type_bool;
            return 0;
        case AST_EXPR_FLOAT_LIT:
            if (!e->resolved_type)
                ((struct ASTExpr *)e)->resolved_type = &static_type_f64;
            return 0;
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n; i++)
                if (names[i] && name && strcmp(names[i], name) == 0) {
                    if (type_ptrs && i < n && type_ptrs[i])
                        ((struct ASTExpr *)e)->resolved_type = type_ptrs[i];
                    return 0;
                }
            fprintf(stderr, "typeck error: undefined name '%s'\n", name ? name : "");
            return -1;
        }
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV:
        case AST_EXPR_MOD: case AST_EXPR_SHL: case AST_EXPR_SHR:
        case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE:
        case AST_EXPR_GT: case AST_EXPR_GE: case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            if (typeck_expr_sym(e->value.binop.left, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (typeck_expr_sym(e->value.binop.right, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            /* 向量逐分量运算（§10）：两操作数均为同类型向量时，结果类型为该向量 */
            {
                const struct ASTType *lt = e->value.binop.left->resolved_type;
                const struct ASTType *rt = e->value.binop.right->resolved_type;
                if (lt && rt && lt->kind == AST_TYPE_VECTOR && rt->kind == AST_TYPE_VECTOR
                    && lt->elem_type && rt->elem_type && lt->elem_type->kind == rt->elem_type->kind
                    && lt->array_size == rt->array_size)
                    ((struct ASTExpr *)e)->resolved_type = lt;
                else if (e->kind >= AST_EXPR_EQ && e->kind <= AST_EXPR_GE)
                    ((struct ASTExpr *)e)->resolved_type = &static_type_bool;
                else if (e->kind == AST_EXPR_LOGAND || e->kind == AST_EXPR_LOGOR)
                    ((struct ASTExpr *)e)->resolved_type = &static_type_bool;
                else if (lt && rt && e->kind <= AST_EXPR_GE) {
                    /* 标量算术：i64 与 i32 混合时提升为 i64，否则两类型须一致 */
                    if (lt->kind == AST_TYPE_I64 || rt->kind == AST_TYPE_I64)
                        ((struct ASTExpr *)e)->resolved_type = &static_type_i64;
                    else if (type_equal(lt, rt))
                        ((struct ASTExpr *)e)->resolved_type = lt;
                }
            }
            return 0;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
        case AST_EXPR_IF:
            if (typeck_expr_sym(e->value.if_expr.cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (!expr_produces_bool(e->value.if_expr.cond, names, type_kinds, n)) {
                fprintf(stderr, "typeck error: if condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
            if (typeck_expr_sym(e->value.if_expr.then_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (e->value.if_expr.else_expr && typeck_expr_sym(e->value.if_expr.else_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            return 0;
        case AST_EXPR_TERNARY: {
            /* cond ? then : else：条件须为 bool，两分支类型须一致 */
            if (typeck_expr_sym(e->value.if_expr.cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (!expr_produces_bool(e->value.if_expr.cond, names, type_kinds, n)) {
                fprintf(stderr, "typeck error: ternary condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
            if (typeck_expr_sym(e->value.if_expr.then_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (typeck_expr_sym(e->value.if_expr.else_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            const struct ASTType *ty_then = e->value.if_expr.then_expr->resolved_type;
            const struct ASTType *ty_else = e->value.if_expr.else_expr->resolved_type;
            if (!ty_then || !ty_else || !type_equal(ty_then, ty_else)) {
                fprintf(stderr, "typeck error: ternary branches must have the same type\n");
                return -1;
            }
            ((struct ASTExpr *)e)->resolved_type = ty_then;
            return 0;
        }
        case AST_EXPR_ASSIGN: {
            /* left = right：左值类型须与右值一致，表达式类型为左值类型 */
            if (typeck_expr_sym(e->value.binop.left, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (typeck_expr_sym(e->value.binop.right, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            const struct ASTType *lt = e->value.binop.left->resolved_type;
            const struct ASTType *rt = e->value.binop.right->resolved_type;
            if (!rt && lt)
                ((struct ASTExpr *)e->value.binop.right)->resolved_type = lt;  /* 子块中右端可能未解析到类型，用左端补 */
            rt = e->value.binop.right->resolved_type;
            if (!lt || !rt || !type_equal(lt, rt)) {
                fprintf(stderr, "typeck error: assignment type mismatch\n");
                return -1;
            }
            ((struct ASTExpr *)e)->resolved_type = lt;
            return 0;
        }
        case AST_EXPR_PANIC:
            if (e->value.unary.operand)
                return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
            return 0;
        case AST_EXPR_MATCH: {
            if (typeck_expr_sym(e->value.match_expr.matched_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            int match_kind;
            const char *match_name = NULL;
            if (get_expr_type(e->value.match_expr.matched_expr, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &match_kind, &match_name, NULL) != 0) {
                fprintf(stderr, "typeck error: match expression has no determinable type\n");
                return -1;
            }
            const struct ASTEnumDef *match_enum = (match_kind == AST_TYPE_NAMED && match_name) ? find_enum_def(enum_defs, num_enums, match_name) : NULL;
            for (int i = 0; i < e->value.match_expr.num_arms; i++) {
                ASTMatchArm *arm = &e->value.match_expr.arms[i];
                if (arm->is_enum_variant) {
                    if (!match_enum) {
                        fprintf(stderr, "typeck error: enum variant pattern requires matched expression to be an enum type\n");
                        return -1;
                    }
                    if (!arm->enum_name || strcmp(arm->enum_name, match_name) != 0) {
                        fprintf(stderr, "typeck error: match arm enum type must match matched expression type\n");
                        return -1;
                    }
                    int idx = enum_variant_index(match_enum, arm->variant_name);
                    if (idx < 0) {
                        fprintf(stderr, "typeck error: enum '%s' has no variant '%s'\n", arm->enum_name, arm->variant_name ? arm->variant_name : "");
                        return -1;
                    }
                    arm->variant_index = idx;
                }
                if (typeck_expr_sym(arm->result, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            }
            return 0;
        }
        case AST_EXPR_FIELD_ACCESS: {
            /* Type.Variant 形式：base 为标识符且为枚举类型名时，按枚举变体处理（§7.4） */
            if (e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
                const char *type_name = e->value.field_access.base->value.var.name;
                const struct ASTEnumDef *ed = find_enum_def(enum_defs, num_enums, type_name);
                if (ed) {
                    const char *vname = e->value.field_access.field_name;
                    if (enum_variant_index(ed, vname) >= 0) {
                        ((struct ASTExpr *)e)->value.field_access.is_enum_variant = 1;
                        return 0;
                    }
                    fprintf(stderr, "typeck error: enum '%s' has no variant '%s'\n", type_name, vname ? vname : "");
                    return -1;
                }
            }
            if (typeck_expr_sym(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            int base_kind;
            const char *base_name = NULL;
            if (get_expr_type(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, NULL) != 0) {
                fprintf(stderr, "typeck error: field access base has no struct or slice type\n");
                return -1;
            }
            /* 切片 []T 仅支持 .len，类型为 usize */
            if (base_kind == AST_TYPE_SLICE) {
                const char *field = e->value.field_access.field_name;
                if (field && strcmp(field, "len") == 0) {
                    ((struct ASTExpr *)e)->resolved_type = &static_type_usize;
                    return 0;
                }
                fprintf(stderr, "typeck error: slice only has field 'len'\n");
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
                if (typeck_expr_sym(e->value.struct_lit.inits[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            }
            return 0;
        }
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++) {
                if (typeck_expr_sym(e->value.array_lit.elems[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            }
            return 0;
        case AST_EXPR_INDEX: {
            if (typeck_expr_sym(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (typeck_expr_sym(e->value.index.index_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            int base_kind;
            const char *base_name = NULL;
            if (get_expr_type(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, NULL) != 0) {
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
        case AST_EXPR_CALL: {
            if (e->value.call.callee->kind != AST_EXPR_VAR) {
                fprintf(stderr, "typeck error: call callee must be a function name\n");
                return -1;
            }
            const char *callee_name = e->value.call.callee->value.var.name;
            const struct ASTFunc *func = NULL;
            int from_dep = -1;  /* 若 >=0 表示在 typeck_dep_mods[from_dep] 中找到 */
            if (m && m->funcs) {
                for (int i = 0; i < m->num_funcs; i++) {
                    if (m->funcs[i]->name && callee_name && strcmp(m->funcs[i]->name, callee_name) == 0) {
                        func = m->funcs[i];
                        break;
                    }
                }
            }
            if (!func && typeck_dep_mods && typeck_num_deps > 0) {
                for (int j = 0; j < typeck_num_deps; j++) {
                    struct ASTModule *dm = typeck_dep_mods[j];
                    if (!dm || !dm->funcs) continue;
                    for (int i = 0; i < dm->num_funcs; i++) {
                        if (dm->funcs[i]->name && callee_name && strcmp(dm->funcs[i]->name, callee_name) == 0) {
                            func = dm->funcs[i];
                            from_dep = j;
                            break;
                        }
                    }
                    if (func) break;
                }
            }
            if (!func) {
                fprintf(stderr, "typeck error: unknown function '%s'\n", callee_name ? callee_name : "");
                return -1;
            }
            if (from_dep >= 0) {
                ((struct ASTExpr *)e)->value.call.resolved_import_path = m->import_paths[from_dep];
                ((struct ASTExpr *)e)->value.call.resolved_callee_func = (struct ASTFunc *)func;
            }
            /* 泛型调用 f<Type>(args)：要求函数为泛型、类型实参个数一致，登记单态化实例并做代入后类型检查 */
            if (e->value.call.num_type_args > 0) {
                if (func->num_generic_params == 0) {
                    fprintf(stderr, "typeck error: function '%s' is not generic but type arguments were provided\n", callee_name ? callee_name : "");
                    return -1;
                }
                if (e->value.call.num_type_args != func->num_generic_params) {
                    fprintf(stderr, "typeck error: generic function '%s' expects %d type arguments, got %d\n",
                        callee_name, func->num_generic_params, e->value.call.num_type_args);
                    return -1;
                }
                /* 在对应模块中登记 (template, type_args)：本模块调用则登记到 m，从 import 调用则登记到 dep（供 codegen 生成单态化体） */
                {
                    struct ASTModule *mod = (from_dep >= 0 && typeck_dep_mods && from_dep < typeck_num_deps)
                        ? typeck_dep_mods[from_dep] : (struct ASTModule *)m;
                    int found = 0;
                    if (mod->mono_instances) {
                        for (int k = 0; k < mod->num_mono_instances; k++) {
                            if (mod->mono_instances[k].template != (struct ASTFunc *)func) continue;
                            if (mod->mono_instances[k].num_type_args != e->value.call.num_type_args) continue;
                            int eq = 1;
                            for (int j = 0; j < e->value.call.num_type_args; j++) {
                                if (!type_equal(mod->mono_instances[k].type_args[j], e->value.call.type_args[j])) { eq = 0; break; }
                            }
                            if (eq) { found = 1; break; }
                        }
                    }
                    if (!found) {
                        if (mod->num_mono_instances >= AST_MODULE_MAX_MONO_INSTANCES) {
                            fprintf(stderr, "typeck error: too many generic instances\n");
                            return -1;
                        }
                        ASTMonoInstance *new_list = (ASTMonoInstance *)realloc(mod->mono_instances,
                            (size_t)(mod->num_mono_instances + 1) * sizeof(ASTMonoInstance));
                        if (!new_list) {
                            fprintf(stderr, "typeck error: out of memory for mono instances\n");
                            return -1;
                        }
                        mod->mono_instances = new_list;
                        mod->mono_instances[mod->num_mono_instances].template = (struct ASTFunc *)func;
                        mod->mono_instances[mod->num_mono_instances].type_args = e->value.call.type_args;
                        mod->mono_instances[mod->num_mono_instances].num_type_args = e->value.call.num_type_args;
                        mod->num_mono_instances++;
                    }
                }
                if (e->value.call.num_args != func->num_params) {
                    fprintf(stderr, "typeck error: function '%s' expects %d arguments, got %d\n",
                        callee_name, func->num_params, e->value.call.num_args);
                    return -1;
                }
                for (int i = 0; i < e->value.call.num_args; i++) {
                    if (typeck_expr_sym(e->value.call.args[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                    const struct ASTType *arg_type = e->value.call.args[i]->resolved_type;
                    const struct ASTType *param_type = func->params[i].type;
                    if (!arg_type || !param_type || !type_equal_subst(param_type, arg_type,
                            func->generic_param_names, e->value.call.type_args, e->value.call.num_type_args)) {
                        fprintf(stderr, "typeck error: argument %d of '%s' type mismatch\n", i + 1, callee_name ? callee_name : "");
                        return -1;
                    }
                }
                if (func->return_type)
                    ((struct ASTExpr *)e)->resolved_type = get_substituted_return_type(func->return_type,
                        func->generic_param_names, e->value.call.type_args, e->value.call.num_type_args);
                return 0;
            }
            /* 非泛型调用：不允许调用泛型函数而不提供类型实参 */
            if (func->num_generic_params > 0) {
                fprintf(stderr, "typeck error: generic function '%s' requires type arguments (e.g. %s<Type>(...))\n", callee_name ? callee_name : "", callee_name ? callee_name : "");
                return -1;
            }
            if (e->value.call.num_args != func->num_params) {
                fprintf(stderr, "typeck error: function '%s' expects %d arguments, got %d\n",
                    callee_name, func->num_params, e->value.call.num_args);
                return -1;
            }
            for (int i = 0; i < e->value.call.num_args; i++) {
                if (typeck_expr_sym(e->value.call.args[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                const struct ASTType *arg_type = e->value.call.args[i]->resolved_type;
                const struct ASTType *param_type = func->params[i].type;
                int ok = (arg_type && param_type && type_equal(arg_type, param_type));
                /* 允许非负整数字面量传给 u32 参数（C 会隐式转换） */
                if (!ok && param_type && param_type->kind == AST_TYPE_U32
                    && e->value.call.args[i]->kind == AST_EXPR_LIT
                    && e->value.call.args[i]->value.int_val >= 0)
                    ok = 1;
                /* 允许整数字面量传给 i64 参数（C 会隐式转换） */
                if (!ok && param_type && param_type->kind == AST_TYPE_I64
                    && e->value.call.args[i]->kind == AST_EXPR_LIT)
                    ok = 1;
                if (!ok) {
                    fprintf(stderr, "typeck error: argument %d of '%s' type mismatch\n", i + 1, callee_name ? callee_name : "");
                    return -1;
                }
            }
            if (func->return_type)
                ((struct ASTExpr *)e)->resolved_type = func->return_type;
            return 0;
        }
        case AST_EXPR_METHOD_CALL: {
            if (typeck_expr_sym(e->value.method_call.base, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            const struct ASTType *base_ty = e->value.method_call.base->resolved_type;
            if (!base_ty) {
                fprintf(stderr, "typeck error: method call base has no type\n");
                return -1;
            }
            const char *type_str = type_to_name_string(base_ty);
            const char *method_name = e->value.method_call.method_name;
            struct ASTFunc *impl_func = NULL;
            if (m && m->impl_blocks) {
                for (int k = 0; k < m->num_impl_blocks; k++) {
                    if (!m->impl_blocks[k]->type_name || strcmp(m->impl_blocks[k]->type_name, type_str) != 0) continue;
                    for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
                        if (m->impl_blocks[k]->funcs[j]->name && method_name && strcmp(m->impl_blocks[k]->funcs[j]->name, method_name) == 0) {
                            impl_func = m->impl_blocks[k]->funcs[j];
                            break;
                        }
                    }
                    if (impl_func) break;
                }
            }
            if (!impl_func) {
                fprintf(stderr, "typeck error: no impl for type '%s' with method '%s'\n", type_str ? type_str : "?", method_name ? method_name : "?");
                return -1;
            }
            /* impl 方法首参为 self，实参仅对应 params[1..] */
            int num_params_no_self = impl_func->num_params - 1;
            if (e->value.method_call.num_args != num_params_no_self) {
                fprintf(stderr, "typeck error: method '%s' expects %d arguments, got %d\n",
                    method_name, num_params_no_self, e->value.method_call.num_args);
                return -1;
            }
            for (int i = 0; i < e->value.method_call.num_args; i++) {
                if (typeck_expr_sym(e->value.method_call.args[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                const struct ASTType *arg_type = e->value.method_call.args[i]->resolved_type;
                const struct ASTType *param_type = impl_func->params[i + 1].type;
                if (!arg_type || !param_type || !type_equal(arg_type, param_type)) {
                    fprintf(stderr, "typeck error: argument %d of method '%s' type mismatch\n", i + 1, method_name ? method_name : "");
                    return -1;
                }
            }
            ((struct ASTExpr *)e)->resolved_type = impl_func->return_type;
            ((struct ASTExpr *)e)->value.method_call.resolved_impl_func = impl_func;
            return 0;
        }
        default:
            fprintf(stderr, "typeck error: unsupported expression kind\n");
            return -1;
    }
}

/**
 * 判断块是否以「裸的最终表达式」作为返回值（即未写 return，仅写 0 等表达式）。
 * 约定：返回值统一使用 return expr;，不允许以块尾表达式隐式作为返回值。
 * 返回值：1 表示块有 final_expr 且非 return/panic/break/continue（即隐式返回值）；0 表示无或为控制流。
 */
static int block_has_implicit_return(const struct ASTBlock *b) {
    if (!b || !b->final_expr) return 0;
    switch (b->final_expr->kind) {
        case AST_EXPR_RETURN:
        case AST_EXPR_PANIC:
        case AST_EXPR_BREAK:
        case AST_EXPR_CONTINUE:
            return 0;
        default:
            return 1;
    }
}

/**
 * 对块做类型检查；parent_names/... 为外层符号表；inside_loop 表示当前块是否为某 while 体；struct_defs/num_structs 为顶层结构体；enum_defs/num_enums 为顶层枚举。
 */
static int typeck_block(const struct ASTBlock *b, const char **parent_names,
    const int *parent_type_kinds, const char **parent_type_names, const struct ASTType **parent_type_ptrs, int parent_n, int inside_loop,
    struct ASTStructDef **struct_defs, int num_structs, struct ASTEnumDef **enum_defs, int num_enums, const struct ASTModule *m) {
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
        if (typeck_expr_sym(b->const_decls[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->const_decls[i].init->value.array_lit.num_elems != b->const_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: array literal length must match declaration size\n");
                return -1;
            }
        }
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_VECTOR &&
            b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->const_decls[i].init->value.array_lit.num_elems != b->const_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: vector literal length must match vector lanes\n");
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
        /* f32/f64 初值：浮点字面量或整数字面量 0；浮点字面量设 resolved_type 供 codegen 生成 0.0f/0.0 */
        if (b->const_decls[i].type && (b->const_decls[i].type->kind == AST_TYPE_F32 || b->const_decls[i].type->kind == AST_TYPE_F64) && b->const_decls[i].init) {
            const struct ASTExpr *init = b->const_decls[i].init;
            if (init->kind == AST_EXPR_FLOAT_LIT)
                ((struct ASTExpr *)init)->resolved_type = b->const_decls[i].type;
            else if (init->kind != AST_EXPR_LIT || init->value.int_val != 0) {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal or integer 0\n");
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
        if (typeck_expr_sym(b->let_decls[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->let_decls[i].init->value.array_lit.num_elems != b->let_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: array literal length must match declaration size\n");
                return -1;
            }
        }
        /* 向量可从数组字面量初始化：let v: i32x4 = [a,b,c,d]（文档 §10） */
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_VECTOR &&
            b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            if (b->let_decls[i].init->value.array_lit.num_elems != b->let_decls[i].type->array_size) {
                fprintf(stderr, "typeck error: vector literal length must match vector lanes\n");
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
        /* f32/f64 初值：浮点字面量或整数字面量 0；浮点字面量设 resolved_type 供 codegen 生成 0.0f/0.0 */
        if (b->let_decls[i].type && (b->let_decls[i].type->kind == AST_TYPE_F32 || b->let_decls[i].type->kind == AST_TYPE_F64) && b->let_decls[i].init) {
            const struct ASTExpr *init = b->let_decls[i].init;
            if (init->kind == AST_EXPR_FLOAT_LIT)
                ((struct ASTExpr *)init)->resolved_type = b->let_decls[i].type;
            else if (init->kind != AST_EXPR_LIT || init->value.int_val != 0) {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal or integer 0\n");
                return -1;
            }
        }
        type_kinds[n] = b->let_decls[i].type ? b->let_decls[i].type->kind : AST_TYPE_I32;
        type_names[n] = (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_NAMED) ? b->let_decls[i].type->name : NULL;
        type_ptrs[n] = b->let_decls[i].type;
        names[n++] = b->let_decls[i].name;
    }
    for (int i = 0; i < b->num_loops; i++) {
        if (typeck_expr_sym(b->loops[i].cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (!expr_produces_bool(b->loops[i].cond, names, type_kinds, n)) {
            fprintf(stderr, "typeck error: while condition must be bool (no implicit int-to-bool)\n");
            return -1;
        }
        if (typeck_block(b->loops[i].body, names, type_kinds, type_names, type_ptrs, n, 1, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init && typeck_expr_sym(b->for_loops[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (b->for_loops[i].cond) {
            if (typeck_expr_sym(b->for_loops[i].cond, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (!expr_produces_bool(b->for_loops[i].cond, names, type_kinds, n)) {
                fprintf(stderr, "typeck error: for condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
        }
        if (b->for_loops[i].step && typeck_expr_sym(b->for_loops[i].step, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (typeck_block(b->for_loops[i].body, names, type_kinds, type_names, type_ptrs, n, 1, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
    }
    for (int i = 0; i < b->num_defers; i++) {
        if (typeck_block(b->defer_blocks[i], names, type_kinds, type_names, type_ptrs, n, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr) {
            if (typeck_expr_sym(b->labeled_stmts[i].u.return_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        }
    }
    if (!b->final_expr) return 0;
    return typeck_expr_sym(b->final_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
}

/**
 * 对模块做类型检查；功能、参数、返回值见 typeck.h 声明处注释。
 */
int typeck_module(struct ASTModule *m, struct ASTModule **dep_mods, int num_deps) {
    typeck_dep_mods = dep_mods;
    typeck_num_deps = num_deps;
    if (!m) {
        fprintf(stderr, "typeck error: null module\n");
        return -1;
    }
    /* 库模块（仅 import 或无 main）视为通过 */
    if (!m->main_func)
        return 0;

    if (!m->main_func->return_type ||
        (m->main_func->return_type->kind != AST_TYPE_I32 && m->main_func->return_type->kind != AST_TYPE_I64)) {
        fprintf(stderr, "typeck error: main must return i32 or i64\n");
        return -1;
    }

    if (!m->main_func->body) {
        fprintf(stderr, "typeck error: main must have a body (block)\n");
        return -1;
    }
    if (block_has_implicit_return(m->main_func->body)) {
        fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
        return -1;
    }
    if (m->main_func->num_generic_params > 0) {
        fprintf(stderr, "typeck error: main cannot be generic\n");
        return -1;
    }

    /* 结构体布局计算（§11.1）：字段偏移、总大小、对齐，供后续 codegen 使用 size_of/offset_of */
    if (m->struct_defs && m->num_structs > 0 && compute_struct_layouts(m->struct_defs, m->num_structs, m->enum_defs, m->num_enums) != 0)
        return -1;

    /* impl 块校验：trait 存在、类型存在、每个 trait 方法在 impl 中有且签名一致（阶段 7.2） */
    if (m->impl_blocks) {
        for (int k = 0; k < m->num_impl_blocks; k++) {
            const struct ASTImplBlock *impl = m->impl_blocks[k];
            const struct ASTTraitDef *trait = find_trait_def(m->trait_defs, m->num_traits, impl->trait_name);
            if (!trait) {
                fprintf(stderr, "typeck error: impl for unknown trait '%s'\n", impl->trait_name ? impl->trait_name : "");
                return -1;
            }
            for (int i = 0; i < trait->num_methods; i++) {
                const char *meth = trait->methods[i].name;
                struct ASTFunc *impl_func = NULL;
                for (int j = 0; j < impl->num_funcs; j++)
                    if (impl->funcs[j]->name && meth && strcmp(impl->funcs[j]->name, meth) == 0) { impl_func = impl->funcs[j]; break; }
                if (!impl_func) {
                    fprintf(stderr, "typeck error: impl '%s' for '%s' missing method '%s'\n",
                        impl->trait_name ? impl->trait_name : "", impl->type_name ? impl->type_name : "", meth ? meth : "");
                    return -1;
                }
                if (!impl_func->return_type || !trait->methods[i].return_type || !type_equal(impl_func->return_type, trait->methods[i].return_type)) {
                    fprintf(stderr, "typeck error: impl method '%s' return type mismatch\n", meth ? meth : "");
                    return -1;
                }
            }
        }
        /* 对 impl 块内方法做体块类型检查 */
        for (int k = 0; k < m->num_impl_blocks; k++) {
            const struct ASTImplBlock *impl = m->impl_blocks[k];
            for (int j = 0; j < impl->num_funcs; j++) {
                const struct ASTFunc *f = impl->funcs[j];
                if (!f->body) continue;
                const char *names[MAX_SYMTAB];
                int type_kinds[MAX_SYMTAB];
                const char *type_names[MAX_SYMTAB];
                const struct ASTType *type_ptrs[MAX_SYMTAB];
                int n = (f->num_params < MAX_SYMTAB) ? f->num_params : 0;
                for (int i = 0; i < n; i++) {
                    names[i] = f->params[i].name;
                    type_kinds[i] = f->params[i].type ? f->params[i].type->kind : AST_TYPE_I32;
                    type_names[i] = (f->params[i].type && f->params[i].type->kind == AST_TYPE_NAMED) ? f->params[i].type->name : NULL;
                    type_ptrs[i] = f->params[i].type;
                }
                if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m) != 0)
                    return -1;
                if (f->return_type && block_has_implicit_return(f->body)) {
                    fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
                    return -1;
                }
            }
        }
    }

    /* 对每个非泛型函数做体块类型检查；泛型函数体在对单态化实例检查时再做。 */
    for (int i = 0; i < m->num_funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f->body) continue;
        if (f->num_generic_params > 0) continue;
        const char *names[MAX_SYMTAB];
        int type_kinds[MAX_SYMTAB];
        const char *type_names[MAX_SYMTAB];
        const struct ASTType *type_ptrs[MAX_SYMTAB];
        int n = (f->num_params < MAX_SYMTAB) ? f->num_params : 0;
        for (int j = 0; j < n; j++) {
            names[j] = f->params[j].name;
            type_kinds[j] = f->params[j].type ? f->params[j].type->kind : AST_TYPE_I32;
            type_names[j] = (f->params[j].type && f->params[j].type->kind == AST_TYPE_NAMED) ? f->params[j].type->name : NULL;
            type_ptrs[j] = f->params[j].type;
        }
        if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m) != 0)
            return -1;
        if (f->return_type && block_has_implicit_return(f->body)) {
            fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
            return -1;
        }
    }
    /* 对每个泛型单态化实例，用代入后的形参类型再检查一次模板函数体，保证体在具体类型下合法 */
    for (int k = 0; k < m->num_mono_instances; k++) {
        const struct ASTFunc *f = m->mono_instances[k].template;
        struct ASTType **type_args = m->mono_instances[k].type_args;
        int num_type_args = m->mono_instances[k].num_type_args;
        if (!f->body || !f->generic_param_names || !type_args) continue;
        const char *names[MAX_SYMTAB];
        int type_kinds[MAX_SYMTAB];
        const char *type_names[MAX_SYMTAB];
        const struct ASTType *type_ptrs[MAX_SYMTAB];
        int n = (f->num_params < MAX_SYMTAB) ? f->num_params : 0;
        for (int j = 0; j < n; j++) {
            names[j] = f->params[j].name;
            type_ptrs[j] = get_substituted_return_type(f->params[j].type, f->generic_param_names, type_args, num_type_args);
            type_kinds[j] = type_ptrs[j] ? type_ptrs[j]->kind : AST_TYPE_I32;
            type_names[j] = (type_ptrs[j] && type_ptrs[j]->kind == AST_TYPE_NAMED) ? type_ptrs[j]->name : NULL;
        }
        if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m) != 0)
            return -1;
        if (f->return_type && block_has_implicit_return(f->body)) {
            fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
            return -1;
        }
    }
    return 0;
}
