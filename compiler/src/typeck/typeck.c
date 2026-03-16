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

/** BCE 扩展：循环内值域上下文，用于 for (let i=0; i<n; i++) 或 i < s.length 时证明 arr[i]/s[i] 在界内。 */
#define MAX_BCE_RANGES 4
static const char *bce_var_names[MAX_BCE_RANGES];
static int bce_bound_const[MAX_BCE_RANGES];   /* 1 表示上界为常数 bce_bound_val，0 表示上界为 bce_bound_base 的 .length */
static int bce_bound_val[MAX_BCE_RANGES];
static const struct ASTExpr *bce_bound_base[MAX_BCE_RANGES];
static int bce_n;

/** 结构体字面量具名类型缓存：为 (Type){0} 等设置 resolved_type，使 if-expr/嵌套 if 能正确推断 __tmp 类型，从源头消除对 sed 补丁的依赖。 */
#define MAX_STRUCT_LIT_TYPES 32
static struct ASTType struct_lit_type_cache[MAX_STRUCT_LIT_TYPES];
static const char *struct_lit_type_names[MAX_STRUCT_LIT_TYPES];
static int struct_lit_type_n;

/** 字面量默认类型，用于设置 resolved_type 以便函数调用实参匹配 */
static struct ASTType static_type_i32 = { AST_TYPE_I32, NULL, NULL, 0 };
static struct ASTType static_type_i64 = { AST_TYPE_I64, NULL, NULL, 0 };
static struct ASTType static_type_f64 = { AST_TYPE_F64, NULL, NULL, 0 };
static struct ASTType static_type_f32 = { AST_TYPE_F32, NULL, NULL, 0 };
static struct ASTType static_type_bool = { AST_TYPE_BOOL, NULL, NULL, 0 };
/** 切片 .length 字段类型（与 C 侧 size_t 对应） */
static struct ASTType static_type_usize = { AST_TYPE_USIZE, NULL, NULL, 0 };
/** u8 与 *u8，用于切片 []u8 的 .data 字段类型（与 C 侧 elem* data 一致） */
static struct ASTType static_type_u8 = { AST_TYPE_U8, NULL, NULL, 0 };
static struct ASTType static_type_ptr_u8 = { AST_TYPE_PTR, NULL, &static_type_u8, 0 };

/** 当前 typeck 的依赖模块列表（与 m->import_paths 顺序一致），供 CALL 跨模块解析；由 typeck_module 设置。 */
static struct ASTModule **typeck_dep_mods;
static int typeck_num_deps;

/** 判断第 j 个 import 是否导出符号 name：WHOLE 导出全部，BINDING 不导出（仅绑定名为模块引用），SELECT 仅导出列表中的名。 */
static int import_exports_name(const struct ASTModule *m, int j, const char *name) {
    if (!m || !name || j < 0 || j >= m->num_imports) return 0;
    if (!m->import_kinds) return 1; /* 旧 AST 无 import_kinds，视为整模块 */
    if (m->import_kinds[j] == AST_IMPORT_KIND_WHOLE) return 1;
    if (m->import_kinds[j] == AST_IMPORT_KIND_BINDING) return 0;
    if (m->import_kinds[j] == AST_IMPORT_KIND_SELECT && m->import_select_names && m->import_select_counts) {
        for (int k = 0; k < m->import_select_counts[j]; k++)
            if (m->import_select_names[j][k] && strcmp(m->import_select_names[j][k], name) == 0) return 1;
    }
    return 0;
}

/** 全面自举：仅填 resolved_type，不做语义检查；.su 用访问器遍历 AST 并做检查（重写实现）。 */
static int typeck_fill_only;

/** 前向声明：typeck_block 在文件后部定义，供 AST_EXPR_BLOCK 的 typeck 调用。 */
static int typeck_block(const struct ASTBlock *b, const char **parent_names,
    const int *parent_type_kinds, const char **parent_type_names, const struct ASTType **parent_type_ptrs, int parent_n,
    const int *parent_const_values, int parent_n_consts, int inside_loop,
    struct ASTStructDef **struct_defs, int num_structs, struct ASTEnumDef **enum_defs, int num_enums, const struct ASTModule *m,
    const struct ASTType *func_return_type);

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
 * 先在本模块 defs 中查找结构体，未找到时在 typeck_dep_mods 中查找（跨模块类型解析，如 import std.mem 后使用 Buffer）。
 * 参数：defs/num 当前模块结构体；name 类型名。返回值：找到返回该 ASTStructDef*，否则 NULL。
 */
static const struct ASTStructDef *find_struct_def_with_deps(struct ASTStructDef **defs, int num, const char *name) {
    const struct ASTStructDef *sd = find_struct_def(defs, num, name);
    if (sd) return sd;
    if (!typeck_dep_mods || !name) return NULL;
    for (int j = 0; j < typeck_num_deps; j++) {
        struct ASTModule *dm = typeck_dep_mods[j];
        if (!dm || !dm->struct_defs) continue;
        sd = find_struct_def(dm->struct_defs, dm->num_structs, name);
        if (sd) return sd;
    }
    /* 限定名 platform.elf.ElfCodegenCtx：依赖里只存短名 ElfCodegenCtx，用最后一段再查 */
    const char *tail = strrchr(name, '.');
    if (tail && tail[1]) {
        const char *base = tail + 1;
        sd = find_struct_def(defs, num, base);
        if (sd) return sd;
        for (int j = 0; j < typeck_num_deps; j++) {
            struct ASTModule *dm = typeck_dep_mods[j];
            if (!dm || !dm->struct_defs) continue;
            sd = find_struct_def(dm->struct_defs, dm->num_structs, base);
            if (sd) return sd;
        }
    }
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

/** 先在本模块 defs 中查找枚举，未找到时在 typeck_dep_mods 中查找（跨模块 Type.Variant，如 import token 后 TokenKind.TOKEN_EOF）。 */
static const struct ASTEnumDef *find_enum_def_with_deps(struct ASTEnumDef **defs, int num, const char *name) {
    const struct ASTEnumDef *ed = find_enum_def(defs, num, name);
    if (ed) return ed;
    if (!typeck_dep_mods || !name) return NULL;
    for (int j = 0; j < typeck_num_deps; j++) {
        struct ASTModule *dm = typeck_dep_mods[j];
        if (!dm || !dm->enum_defs) continue;
        ed = find_enum_def(dm->enum_defs, dm->num_enums, name);
        if (ed) return ed;
    }
    return NULL;
}

/**
 * 判断 import 路径是否与标识符 name 匹配（用于 module.func 中的模块名）。
 * path 如 "backend" 或 "codegen.types"；name 如 "backend" 或 "types"。
 * 返回值：1 表示匹配（path 等于 name 或 path 最后一段等于 name），0 表示不匹配。
 */
static int import_path_matches(const char *path, const char *name) {
    if (!path || !name) return 0;
    if (strcmp(path, name) == 0) return 1;
    const char *last = strrchr(path, '.');
    if (last && last[1] && strcmp(last + 1, name) == 0) return 1;
    return 0;
}

/**
 * 判断 name 是否为某 import 路径的前缀（用于 arch.x86_64 中单独出现 arch 时视为合法）。
 * 例如 path="arch.x86_64"、name="arch" 则返回 1，使 arch.x86_64.emit_* 的中间前缀合法。
 */
static int import_path_has_prefix(const char *path, const char *name) {
    if (!path || !name) return 0;
    size_t nlen = strlen(name);
    if (strlen(path) < nlen) return 0;
    if (strncmp(path, name, nlen) != 0) return 0;
    return (path[nlen] == '\0' || path[nlen] == '.');
}

/**
 * 从“模块引用”表达式（VAR 或嵌套 FIELD_ACCESS 如 arch.x86_64）拼出完整 import 路径到 buf，返回长度，失败返回 -1。
 * 用于 CALL(arch.x86_64.emit_*, ...) 时从 callee->base 得到 "arch.x86_64" 以在 typeck_dep_mods 中查找。
 */
static int expr_to_import_path(const struct ASTExpr *e, char *buf, size_t buf_size) {
    if (!e || !buf || buf_size == 0) return -1;
    if (e->kind == AST_EXPR_VAR && e->value.var.name) {
        size_t len = strlen(e->value.var.name);
        if (len >= buf_size) return -1;
        memcpy(buf, e->value.var.name, len + 1);
        return (int)len;
    }
    if (e->kind == AST_EXPR_FIELD_ACCESS && e->value.field_access.base && e->value.field_access.field_name) {
        int base_len = expr_to_import_path(e->value.field_access.base, buf, buf_size);
        if (base_len < 0) return -1;
        size_t need = (size_t)base_len + 1 + strlen(e->value.field_access.field_name);
        if (need >= buf_size) return -1;
        buf[base_len] = '.';
        strcpy(buf + base_len + 1, e->value.field_access.field_name);
        return (int)need;
    }
    return -1;
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
        if (a->name && b->name && strcmp(a->name, b->name) == 0) return 1;
        /* 跨模块限定名与短名视为同类型：ElfCodegenCtx 与 platform.elf.ElfCodegenCtx */
        if (a->name && b->name) {
            const char *tail_a = strrchr(a->name, '.');
            const char *tail_b = strrchr(b->name, '.');
            const char *base_a = tail_a ? tail_a + 1 : a->name;
            const char *base_b = tail_b ? tail_b + 1 : b->name;
            if (strcmp(base_a, base_b) == 0) return 1;
        }
        return 0;
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
 * 将类型格式化为可读字符串，用于面包屑错误（Expected/Found）；写入 buf，最多 size 字节。
 * 支持标量、NAMED、*T、[]T、[N]T。
 */
static void type_to_string_buf(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || !buf || size == 0) { if (buf && size) buf[0] = '\0'; return; }
    const char *base = type_to_name_string(ty);
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        char inner[64];
        type_to_string_buf(ty->elem_type, inner, sizeof(inner));
        (void)snprintf(buf, size, "*%s", inner[0] ? inner : "?");
        return;
    }
    if (ty->kind == AST_TYPE_SLICE && ty->elem_type) {
        char inner[64];
        type_to_string_buf(ty->elem_type, inner, sizeof(inner));
        (void)snprintf(buf, size, "[]%s", inner[0] ? inner : "?");
        return;
    }
    if (ty->kind == AST_TYPE_ARRAY && ty->elem_type && ty->array_size > 0) {
        char inner[64];
        type_to_string_buf(ty->elem_type, inner, sizeof(inner));
        (void)snprintf(buf, size, "[%d]%s", ty->array_size, inner[0] ? inner : "?");
        return;
    }
    if (base && base[0])
        (void)snprintf(buf, size, "%s", base);
    else
        (void)snprintf(buf, size, "?");
}

/** 若表达式节点有源码位置则输出 " at line:col"，然后换行；用于面包屑错误。 */
static void typeck_err_loc(const struct ASTExpr *e) {
    if (e && (e->line > 0 || e->col > 0))
        fprintf(stderr, " at %d:%d", e->line, e->col);
    fprintf(stderr, "\n");
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
            const struct ASTStructDef *sd = find_struct_def_with_deps(struct_defs, num_structs, ty->name);
            if (sd && sd->struct_align > 0) return sd->struct_align;
            if (find_enum_def(enum_defs, num_enums, ty->name)) return 4;  /* 枚举按 int 对齐 */
            /* 自举：NAMED "i32" 等按内建类型给对齐 */
            if (ty->name && (strcmp(ty->name, "i32") == 0 || strcmp(ty->name, "u32") == 0 || strcmp(ty->name, "bool") == 0)) return 4;
            if (ty->name && strcmp(ty->name, "u8") == 0) return 1;
            if (ty->name && (strcmp(ty->name, "i64") == 0 || strcmp(ty->name, "u64") == 0 || strcmp(ty->name, "f64") == 0)) return 8;
            if (ty->name && strcmp(ty->name, "f32") == 0) return 4;
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
            const struct ASTStructDef *sd = find_struct_def_with_deps(struct_defs, num_structs, ty->name);
            if (sd && sd->struct_size > 0) return sd->struct_size;
            if (find_enum_def(enum_defs, num_enums, ty->name)) return 4;  /* 枚举按 int */
            /* 自举：.su 中 [N]i32 等会解析为 NAMED "i32"，按内建类型给大小 */
            if (ty->name && strcmp(ty->name, "i32") == 0) return 4;
            if (ty->name && strcmp(ty->name, "u32") == 0) return 4;
            if (ty->name && strcmp(ty->name, "bool") == 0) return 4;
            if (ty->name && strcmp(ty->name, "u8") == 0) return 1;
            if (ty->name && strcmp(ty->name, "i64") == 0) return 8;
            if (ty->name && strcmp(ty->name, "u64") == 0) return 8;
            if (ty->name && strcmp(ty->name, "f64") == 0) return 8;
            if (ty->name && strcmp(ty->name, "f32") == 0) return 4;
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
        if (sd->packed) {
            /* packed：无填充，字段紧密排列，结构体对齐为 1（内存契约） */
            for (int i = 0; i < sd->num_fields && i < AST_STRUCT_MAX_FIELDS; i++) {
                const struct ASTType *fty = sd->fields[i].type;
                if (!fty) { sd->field_offsets[i] = current_offset; continue; }
                sd->field_offsets[i] = current_offset;
                int fsize = type_size_of(fty, struct_defs, num_structs, enum_defs, num_enums);
                if (fsize <= 0) {
                    fprintf(stderr, "typeck error: struct '%s' field '%s' has unknown or invalid type size\n",
                        sd->name ? sd->name : "?", sd->fields[i].name ? sd->fields[i].name : "?");
                    return -1;
                }
                current_offset += fsize;
            }
            sd->struct_size = current_offset;
            sd->struct_align = 1;
            continue;
        }
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
            /* 已 typeck 的表达式：若 resolved_type 为 bool 则视为产生 bool（如返回 bool 的函数调用、字段访问等） */
            return (e->resolved_type && e->resolved_type->kind == AST_TYPE_BOOL);
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
        case AST_EXPR_ADDR_OF:
            return 0;  /* 取址非常量表达式 */
        case AST_EXPR_DEREF:
            return 0;  /* 解引用非常量表达式 */
        case AST_EXPR_AS:
            return 0;  /* 类型转换非常量（或可扩展为递归 is_const_expr(operand)） */
        case AST_EXPR_ARRAY_LIT: {
            /* CTFE 扩展：数组字面量为常量表达式（各元素须为常量），求值时返回元素个数（数组长度） */
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (!is_const_expr(e->value.array_lit.elems[i], names, n)) return 0;
            return 1;
        }
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
        case AST_EXPR_ASSIGN:
            return 0;  /* if/三元/赋值 表达式非常量 */
        default:
            return 0;
    }
}

/**
 * CTFE 最小集：对常量表达式求值，返回整型结果（用于 const 初值及折叠）。
 * 要求 e 已通过 is_const_expr；names/const_values 为当前作用域 const 名与已求值；n 为 const 个数。
 */
static int eval_const_int(const struct ASTExpr *e, const char **names, const int *const_values, int n) {
    if (!e) return 0;
    switch (e->kind) {
        case AST_EXPR_LIT:
            return e->value.int_val;
        case AST_EXPR_BOOL_LIT:
            return e->value.int_val ? 1 : 0;
        case AST_EXPR_FLOAT_LIT:
            return (int)e->value.float_val;
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n && names && const_values; i++)
                if (names[i] && name && strcmp(names[i], name) == 0) return const_values[i];
            return 0;
        }
        case AST_EXPR_ADD: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l + r;
        }
        case AST_EXPR_SUB: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l - r;
        }
        case AST_EXPR_MUL: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l * r;
        }
        case AST_EXPR_DIV: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return (r != 0) ? (l / r) : 0;
        }
        case AST_EXPR_MOD: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return (r != 0) ? (l % r) : 0;
        }
        case AST_EXPR_SHL: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return (int)((unsigned int)l << (r & 31));
        }
        case AST_EXPR_SHR: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return (int)((unsigned int)l >> (r & 31));
        }
        case AST_EXPR_BITAND: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l & r;
        }
        case AST_EXPR_BITOR: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l | r;
        }
        case AST_EXPR_BITXOR: {
            int l = eval_const_int(e->value.binop.left, names, const_values, n);
            int r = eval_const_int(e->value.binop.right, names, const_values, n);
            return l ^ r;
        }
        case AST_EXPR_EQ:  return eval_const_int(e->value.binop.left, names, const_values, n) == eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_NE:  return eval_const_int(e->value.binop.left, names, const_values, n) != eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_LT:  return eval_const_int(e->value.binop.left, names, const_values, n) <  eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_LE:  return eval_const_int(e->value.binop.left, names, const_values, n) <= eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_GT:  return eval_const_int(e->value.binop.left, names, const_values, n) >  eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_GE:  return eval_const_int(e->value.binop.left, names, const_values, n) >= eval_const_int(e->value.binop.right, names, const_values, n) ? 1 : 0;
        case AST_EXPR_LOGAND: return (eval_const_int(e->value.binop.left, names, const_values, n) && eval_const_int(e->value.binop.right, names, const_values, n)) ? 1 : 0;
        case AST_EXPR_LOGOR:  return (eval_const_int(e->value.binop.left, names, const_values, n) || eval_const_int(e->value.binop.right, names, const_values, n)) ? 1 : 0;
        case AST_EXPR_NEG: {
            int o = eval_const_int(e->value.unary.operand, names, const_values, n);
            return -o;
        }
        case AST_EXPR_BITNOT: {
            int o = eval_const_int(e->value.unary.operand, names, const_values, n);
            return ~o;
        }
        case AST_EXPR_LOGNOT: {
            int o = eval_const_int(e->value.unary.operand, names, const_values, n);
            return !o ? 1 : 0;
        }
        case AST_EXPR_ARRAY_LIT:
            /* CTFE 扩展：数组字面量在整型上下文中求值为元素个数（数组长度） */
            return e->value.array_lit.num_elems;
        default:
            return 0;
    }
}

/**
 * 若 e 为整型/布尔常量表达式，则求值并设置 const_folded_val/const_folded_valid（CTFE 最小集）。
 * const_start：当前块 const 在 names 中的起始下标；parent_n_consts：父块 const 个数（names[0..parent_n_consts) 有父 const 值）。
 */
static void fold_expr(struct ASTExpr *e, const char **names, const int *const_values, int n_consts, int const_start, int parent_n_consts) {
    if (!e || !names) return;
    e->const_folded_valid = 0; /* 默认未折叠，避免 malloc 分配的节点残留垃圾 */
    switch (e->kind) {
        case AST_EXPR_LIT:
        case AST_EXPR_BOOL_LIT:
            e->const_folded_val = e->value.int_val;
            e->const_folded_valid = 1;
            return;
        case AST_EXPR_FLOAT_LIT:
            e->const_folded_val = (int)e->value.float_val;
            e->const_folded_valid = 1;
            return;
        case AST_EXPR_VAR:
            if (const_values) {
                const char *name = e->value.var.name;
                int i;
                for (i = 0; i < parent_n_consts; i++)
                    if (names[i] && name && strcmp(names[i], name) == 0) {
                        e->const_folded_val = const_values[i];
                        e->const_folded_valid = 1;
                        return;
                    }
                for (i = const_start; i < const_start + n_consts; i++)
                    if (names[i] && name && strcmp(names[i], name) == 0) {
                        e->const_folded_val = const_values[i];
                        e->const_folded_valid = 1;
                        return;
                    }
            }
            return;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: {
            fold_expr(e->value.binop.left, names, const_values, n_consts, const_start, parent_n_consts);
            fold_expr(e->value.binop.right, names, const_values, n_consts, const_start, parent_n_consts);
            if (e->value.binop.left->const_folded_valid && e->value.binop.right->const_folded_valid && e->resolved_type &&
                (e->resolved_type->kind == AST_TYPE_I32 || e->resolved_type->kind == AST_TYPE_BOOL ||
                 e->resolved_type->kind == AST_TYPE_U8 || e->resolved_type->kind == AST_TYPE_U32 ||
                 e->resolved_type->kind == AST_TYPE_I64 || e->resolved_type->kind == AST_TYPE_USIZE || e->resolved_type->kind == AST_TYPE_ISIZE)) {
                int l = e->value.binop.left->const_folded_val, r = e->value.binop.right->const_folded_val;
                switch (e->kind) {
                    case AST_EXPR_ADD: e->const_folded_val = l + r; break;
                    case AST_EXPR_SUB: e->const_folded_val = l - r; break;
                    case AST_EXPR_MUL: e->const_folded_val = l * r; break;
                    case AST_EXPR_DIV: e->const_folded_val = (r != 0) ? (l / r) : 0; break;
                    case AST_EXPR_MOD: e->const_folded_val = (r != 0) ? (l % r) : 0; break;
                    case AST_EXPR_SHL: e->const_folded_val = (int)((unsigned int)l << (r & 31)); break;
                    case AST_EXPR_SHR: e->const_folded_val = (int)((unsigned int)l >> (r & 31)); break;
                    case AST_EXPR_BITAND: e->const_folded_val = l & r; break;
                    case AST_EXPR_BITOR: e->const_folded_val = l | r; break;
                    case AST_EXPR_BITXOR: e->const_folded_val = l ^ r; break;
                    case AST_EXPR_EQ: e->const_folded_val = (l == r) ? 1 : 0; break;
                    case AST_EXPR_NE: e->const_folded_val = (l != r) ? 1 : 0; break;
                    case AST_EXPR_LT: e->const_folded_val = (l < r) ? 1 : 0; break;
                    case AST_EXPR_LE: e->const_folded_val = (l <= r) ? 1 : 0; break;
                    case AST_EXPR_GT: e->const_folded_val = (l > r) ? 1 : 0; break;
                    case AST_EXPR_GE: e->const_folded_val = (l >= r) ? 1 : 0; break;
                    case AST_EXPR_LOGAND: e->const_folded_val = (l && r) ? 1 : 0; break;
                    case AST_EXPR_LOGOR: e->const_folded_val = (l || r) ? 1 : 0; break;
                    default: break;
                }
                e->const_folded_valid = 1;
            }
            return;
        }
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            fold_expr(e->value.unary.operand, names, const_values, n_consts, const_start, parent_n_consts);
            if (e->kind != AST_EXPR_ADDR_OF && e->kind != AST_EXPR_DEREF && e->value.unary.operand->const_folded_valid && e->resolved_type &&
                (e->resolved_type->kind == AST_TYPE_I32 || e->resolved_type->kind == AST_TYPE_BOOL ||
                 e->resolved_type->kind == AST_TYPE_U8 || e->resolved_type->kind == AST_TYPE_U32 ||
                 e->resolved_type->kind == AST_TYPE_I64 || e->resolved_type->kind == AST_TYPE_USIZE || e->resolved_type->kind == AST_TYPE_ISIZE)) {
                int o = e->value.unary.operand->const_folded_val;
                if (e->kind == AST_EXPR_NEG) e->const_folded_val = -o;
                else if (e->kind == AST_EXPR_BITNOT) e->const_folded_val = ~o;
                else e->const_folded_val = !o ? 1 : 0;
                e->const_folded_valid = 1;
            }
            return;
        case AST_EXPR_AS:
            fold_expr(e->value.as_type.operand, names, const_values, n_consts, const_start, parent_n_consts);
            return;
        default:
            return;
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
                    (type_ptrs[i]->kind == AST_TYPE_ARRAY || type_ptrs[i]->kind == AST_TYPE_SLICE || type_ptrs[i]->kind == AST_TYPE_PTR))
                    *out_elem_type = type_ptrs[i]->elem_type;
                return 0;
            }
        fprintf(stderr, "typeck error: get_expr_type variable '%.*s' not in scope\n", name ? (int)strlen(name) : 0, name ? name : "?");
        typeck_err_loc((struct ASTExpr *)e);
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
        /* 切片 []T 的 .length（usize）与 .data（*elem_type） */
        if (base_kind == AST_TYPE_SLICE) {
            const char *field = e->value.field_access.field_name;
            if (field && strcmp(field, "length") == 0) {
                *out_kind = AST_TYPE_USIZE;
                *out_name = NULL;
                return 0;
            }
            if (field && strcmp(field, "data") == 0) {
                *out_kind = AST_TYPE_PTR;
                *out_name = NULL;
                if (out_elem_type && e->value.field_access.base->resolved_type
                    && e->value.field_access.base->resolved_type->kind == AST_TYPE_SLICE
                    && e->value.field_access.base->resolved_type->elem_type)
                    *out_elem_type = e->value.field_access.base->resolved_type->elem_type;
                return 0;
            }
            return -1;
        }
        /* 自举：指针到结构体 *T 的 p.field 按 T 的字段类型返回 */
        if (base_kind == AST_TYPE_PTR && e->value.field_access.base->kind == AST_EXPR_VAR && type_ptrs) {
            const char *var_name = e->value.field_access.base->value.var.name;
            for (int vi = 0; vi < n && var_name && names[vi]; vi++)
                if (strcmp(names[vi], var_name) == 0 && type_ptrs[vi] && type_ptrs[vi]->kind == AST_TYPE_PTR
                    && type_ptrs[vi]->elem_type && type_ptrs[vi]->elem_type->kind == AST_TYPE_NAMED
                    && type_ptrs[vi]->elem_type->name) {
                    base_name = type_ptrs[vi]->elem_type->name;
                    base_kind = AST_TYPE_NAMED;
                    break;
                }
        }
        if (base_kind != AST_TYPE_NAMED || !base_name) return -1;
        const struct ASTStructDef *sd = find_struct_def_with_deps(struct_defs, num_structs, base_name);
        if (!sd) return -1;
        const char *field = e->value.field_access.field_name;
        for (int i = 0; i < sd->num_fields; i++)
            if (sd->fields[i].name && field && strcmp(sd->fields[i].name, field) == 0) {
                *out_kind = sd->fields[i].type->kind;
                *out_name = sd->fields[i].type->name;
                if (out_elem_type && sd->fields[i].type->elem_type && (sd->fields[i].type->kind == AST_TYPE_ARRAY || sd->fields[i].type->kind == AST_TYPE_SLICE || sd->fields[i].type->kind == AST_TYPE_PTR))
                    *out_elem_type = sd->fields[i].type->elem_type;
                return 0;
            }
        return -1;
    }
    if (e->kind == AST_EXPR_INDEX) {
        int base_kind;
        const char *base_name = NULL;
        const struct ASTType *base_elem = NULL;
        if (get_expr_type(e->value.index.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, &base_elem) != 0) return -1;
        if (base_kind == AST_TYPE_PTR && !base_elem && e->value.index.base->resolved_type && e->value.index.base->resolved_type->kind == AST_TYPE_PTR)
            base_elem = e->value.index.base->resolved_type->elem_type;
        if (base_kind != AST_TYPE_ARRAY && base_kind != AST_TYPE_SLICE && base_kind != AST_TYPE_PTR) {
                fprintf(stderr, "typeck error: subscript base must be array, slice or pointer type");
                typeck_err_loc(e);
                return -1;
        }
        if (!base_elem) {
                fprintf(stderr, "typeck error: subscript base must be array, slice or pointer type");
                typeck_err_loc(e);
                return -1;
        }
        *out_kind = base_elem->kind;
        *out_name = base_elem->name;
        if (out_elem_type && base_elem->elem_type && (base_elem->kind == AST_TYPE_ARRAY || base_elem->kind == AST_TYPE_SLICE || base_elem->kind == AST_TYPE_PTR))
            *out_elem_type = base_elem->elem_type;
        return 0;
    }
    if (e->kind == AST_EXPR_AS) {
        const struct ASTType *ty = e->value.as_type.type;
        if (!ty) return -1;
        *out_kind = ty->kind;
        *out_name = ty->name;
        if (out_elem_type && ty->elem_type && (ty->kind == AST_TYPE_ARRAY || ty->kind == AST_TYPE_SLICE || ty->kind == AST_TYPE_PTR))
            *out_elem_type = ty->elem_type;
        return 0;
    }
    fprintf(stderr, "typeck error: get_expr_type unhandled expression kind %d\n", (int)e->kind);
    typeck_err_loc((struct ASTExpr *)e);
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
                fprintf(stderr, "typeck error: unknown enum type '%s'", e->value.enum_variant.enum_name ? e->value.enum_variant.enum_name : "?");
                typeck_err_loc(e);
                return -1;
            }
            const char *v = e->value.enum_variant.variant_name;
            for (int i = 0; i < ed->num_variants; i++)
                if (ed->variant_names[i] && v && strcmp(ed->variant_names[i], v) == 0) return 0;
            fprintf(stderr, "typeck error: enum '%s' has no variant '%s'", ed->name ? ed->name : "?", v ? v : "?");
            typeck_err_loc(e);
            return -1;
        }
        case AST_EXPR_BREAK:
        case AST_EXPR_CONTINUE:
            if (!inside_loop) {
                fprintf(stderr, "typeck error: '%s' only allowed inside a loop",
                    e->kind == AST_EXPR_BREAK ? "break" : "continue");
                typeck_err_loc(e);
                return -1;
            }
            return 0;
        case AST_EXPR_RETURN:
            if (e->value.unary.operand)
                return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
            return 0;  /* return; 的 void 检查在 typeck_block 中根据 func_return_type 完成 */
        case AST_EXPR_LIT:
            ((struct ASTExpr *)e)->resolved_type = &static_type_i32;
            return 0;
        case AST_EXPR_BOOL_LIT:
            ((struct ASTExpr *)e)->resolved_type = &static_type_bool;
            return 0;
        case AST_EXPR_FLOAT_LIT: {
            if (!e->resolved_type)
                ((struct ASTExpr *)e)->resolved_type = &static_type_f64;
            /* 填写 64 位位模式供 asm 后端 EXPR_FLOAT_LIT 发射 movq 立即数 */
            union { double d; unsigned long long u; } u;
            u.d = e->value.float_val;
            ((struct ASTExpr *)e)->float_bits_lo = (int)(u.u & 0xFFFFFFFFU);
            ((struct ASTExpr *)e)->float_bits_hi = (int)(u.u >> 32);
            return 0;
        }
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name;
            for (int i = 0; i < n; i++)
                if (names[i] && name && strcmp(names[i], name) == 0) {
                    if (type_ptrs && i < n && type_ptrs[i])
                        ((struct ASTExpr *)e)->resolved_type = type_ptrs[i];
                    return 0;
                }
            /* 标识符未在局部/参数中：若为 import 的模块名（如 backend）或某 import 路径的前缀（如 arch 对 arch.x86_64），视为合法，供 module.func / arch.x86_64.func 使用 */
            if (m && m->import_paths && name) {
                for (int j = 0; j < m->num_imports; j++) {
                    if (!m->import_paths[j]) continue;
                    if (import_path_matches(m->import_paths[j], name)) return 0;
                    if (import_path_has_prefix(m->import_paths[j], name)) return 0;
                }
            }
            fprintf(stderr, "typeck error: undefined name '%s'", name ? name : "");
            typeck_err_loc(e);
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
                    /* 标量算术：i64 与 i32 混合时提升为 i64；含 f64/f32 时提升为浮点；否则两类型须一致 */
                    if (lt->kind == AST_TYPE_I64 || rt->kind == AST_TYPE_I64)
                        ((struct ASTExpr *)e)->resolved_type = &static_type_i64;
                    else if (lt->kind == AST_TYPE_F64 || rt->kind == AST_TYPE_F64)
                        ((struct ASTExpr *)e)->resolved_type = &static_type_f64;
                    else if (lt->kind == AST_TYPE_F32 || rt->kind == AST_TYPE_F32)
                        ((struct ASTExpr *)e)->resolved_type = &static_type_f32;
                    else if (type_equal(lt, rt))
                        ((struct ASTExpr *)e)->resolved_type = lt;
                }
            }
            return 0;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_ADDR_OF:
            return typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m);
        case AST_EXPR_DEREF: {
            if (typeck_expr_sym(e->value.unary.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            const struct ASTType *op_ty = e->value.unary.operand->resolved_type;
            if (!op_ty || op_ty->kind != AST_TYPE_PTR || !op_ty->elem_type) {
                if (!typeck_fill_only) {
                    fprintf(stderr, "typeck error: dereference operand must be pointer type");
                    typeck_err_loc(e);
                    return -1;
                }
                return 0;
            }
            ((struct ASTExpr *)e)->resolved_type = op_ty->elem_type;
            return 0;
        }
        case AST_EXPR_AS:
            if (typeck_expr_sym(e->value.as_type.operand, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            ((struct ASTExpr *)e)->resolved_type = e->value.as_type.type;
            return 0;
        case AST_EXPR_IF: {
            const struct ASTExpr *cond_if = e->value.if_expr.cond;
            if (typeck_expr_sym(cond_if, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (!expr_produces_bool(cond_if, names, type_kinds, n)) {
                if (!typeck_fill_only) {
                    fprintf(stderr, "typeck error: if condition must be bool (no implicit int-to-bool)");
                    typeck_err_loc(e);
                    return -1;
                }
            }
            if (typeck_expr_sym(e->value.if_expr.then_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (e->value.if_expr.else_expr && typeck_expr_sym(e->value.if_expr.else_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            /* if 表达式类型：两分支均为 struct 时须类型一致，否则 codegen 会生成 struct X = struct Y；一侧 struct 一侧标量时取 struct 以便 __tmp 声明正确 */
            {
                const struct ASTExpr *te = e->value.if_expr.then_expr;
                const struct ASTExpr *ee = e->value.if_expr.else_expr;
                const struct ASTType *ty_t = te ? te->resolved_type : NULL;
                const struct ASTType *ty_e = ee ? ee->resolved_type : NULL;
                int t_named = (ty_t && ty_t->kind == AST_TYPE_NAMED);
                int e_named = (ty_e && ty_e->kind == AST_TYPE_NAMED);
                if (ty_t && ty_e && t_named && e_named && !type_equal(ty_t, ty_e)) {
                    if (!typeck_fill_only) {
                        char ebuf[80], fbuf[80];
                        type_to_string_buf(ty_t, ebuf, sizeof(ebuf));
                        type_to_string_buf(ty_e, fbuf, sizeof(fbuf));
                        fprintf(stderr, "typeck error: if-expr branches must have the same type when both are struct: then %s, else %s", ebuf, fbuf);
                        typeck_err_loc(e);
                    }
                    return -1;
                }
                if (ty_t && ty_e)
                    ((struct ASTExpr *)e)->resolved_type = (e_named && !t_named) ? ty_e : ty_t;
                else if (ty_t) ((struct ASTExpr *)e)->resolved_type = ty_t;
                else if (ty_e) ((struct ASTExpr *)e)->resolved_type = ty_e;
            }
            return 0;
        }
        case AST_EXPR_BLOCK: {
            /* 块表达式（if 的 then/else 体）：用块表达式上下文 typeck_block（func_return_type=NULL 允许 return） */
            const struct ASTBlock *b = e->value.block;
            if (typeck_block(b, names, type_kinds, type_names, type_ptrs, n, NULL, 0, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m, NULL) != 0) return -1;
            if (b->final_expr && b->final_expr->kind != AST_EXPR_RETURN) {
                /* 若 final_expr 为赋值，用 RHS 类型作为块类型（如 else { __tmp = (struct ast_Type){0} } 取 ast.Type），便于 if 表达式 __tmp 推断 */
                if (b->final_expr->kind == AST_EXPR_ASSIGN && b->final_expr->value.binop.right && b->final_expr->value.binop.right->resolved_type)
                    ((struct ASTExpr *)e)->resolved_type = b->final_expr->value.binop.right->resolved_type;
                else
                    ((struct ASTExpr *)e)->resolved_type = b->final_expr->resolved_type;
            } else if (b->final_expr && b->final_expr->kind == AST_EXPR_RETURN && b->final_expr->value.unary.operand)
                ((struct ASTExpr *)e)->resolved_type = b->final_expr->value.unary.operand->resolved_type;
            else if (b->num_labeled_stmts == 1 && b->labeled_stmts[0].kind == AST_STMT_RETURN && b->labeled_stmts[0].u.return_expr)
                ((struct ASTExpr *)e)->resolved_type = b->labeled_stmts[0].u.return_expr->resolved_type;
            /* 块仅含一条赋值语句且无 final_expr 时（如 else { __tmp = (struct ast_Type){0} }），用赋值 RHS 类型作为块类型，供 if 表达式取 else 分支 struct 类型 */
            else if (!b->final_expr && b->expr_stmts && b->num_expr_stmts == 1
                && b->expr_stmts[0]->kind == AST_EXPR_ASSIGN && b->expr_stmts[0]->value.binop.right
                && b->expr_stmts[0]->value.binop.right->resolved_type)
                ((struct ASTExpr *)e)->resolved_type = b->expr_stmts[0]->value.binop.right->resolved_type;
            return 0;
        }
        case AST_EXPR_TERNARY: {
            /* cond ? then : else：条件须为 bool，两分支类型须一致 */
            const struct ASTExpr *cond_ter = e->value.if_expr.cond;
            if (typeck_expr_sym(cond_ter, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (!expr_produces_bool(cond_ter, names, type_kinds, n)) {
                if (!typeck_fill_only) {
                    fprintf(stderr, "typeck error: ternary condition must be bool (no implicit int-to-bool)");
                    typeck_err_loc(e);
                    return -1;
                }
            }
            if (typeck_expr_sym(e->value.if_expr.then_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            if (typeck_expr_sym(e->value.if_expr.else_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            const struct ASTType *ty_then = e->value.if_expr.then_expr->resolved_type;
            const struct ASTType *ty_else = e->value.if_expr.else_expr->resolved_type;
            if (!ty_then || !ty_else || !type_equal(ty_then, ty_else)) {
                {
                    char ebuf[80], fbuf[80];
                    type_to_string_buf(e->value.if_expr.then_expr->resolved_type, ebuf, sizeof(ebuf));
                    type_to_string_buf(e->value.if_expr.else_expr->resolved_type, fbuf, sizeof(fbuf));
                    fprintf(stderr, "typeck error: ternary branches must have the same type: expected %s, found %s", ebuf, fbuf);
                    typeck_err_loc(e);
                }
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
                /* 允许 0..255 整数字面量赋给 u8（与函数实参一致，便于 out_buf[i] = 10 等） */
                int allow_u8_lit = 0;
                if (lt && lt->kind == AST_TYPE_U8 && e->value.binop.right->kind == AST_EXPR_LIT) {
                    int v = e->value.binop.right->value.int_val;
                    if (v >= 0 && v <= 255) { allow_u8_lit = 1; ((struct ASTExpr *)e->value.binop.right)->resolved_type = lt; }
                }
                /* 允许字面量 0 赋给指针（如 v.ptr = 0），与 C 的 NULL 一致 */
                int allow_ptr_zero = 0;
                if (lt && lt->kind == AST_TYPE_PTR && e->value.binop.right->kind == AST_EXPR_LIT && e->value.binop.right->value.int_val == 0) {
                    allow_ptr_zero = 1;
                    ((struct ASTExpr *)e->value.binop.right)->resolved_type = lt;
                }
                if (!allow_u8_lit && !allow_ptr_zero && !typeck_fill_only) {
                    char ebuf[80], fbuf[80];
                    type_to_string_buf(lt, ebuf, sizeof(ebuf));
                    type_to_string_buf(rt, fbuf, sizeof(fbuf));
                    fprintf(stderr, "typeck error: assignment type mismatch: expected %s, found %s", ebuf, fbuf);
                    typeck_err_loc(e);
                    return -1;
                }
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
                fprintf(stderr, "typeck error: match expression has no determinable type");
                typeck_err_loc(e);
                return -1;
            }
            const struct ASTEnumDef *match_enum = (match_kind == AST_TYPE_NAMED && match_name) ? find_enum_def(enum_defs, num_enums, match_name) : NULL;
            for (int i = 0; i < e->value.match_expr.num_arms; i++) {
                ASTMatchArm *arm = &e->value.match_expr.arms[i];
                if (arm->is_enum_variant) {
                    if (!match_enum) {
                        fprintf(stderr, "typeck error: enum variant pattern requires matched expression to be an enum type");
                        typeck_err_loc(e);
                        return -1;
                    }
                    if (!arm->enum_name || strcmp(arm->enum_name, match_name) != 0) {
                        fprintf(stderr, "typeck error: match arm enum type must match matched expression type");
                        typeck_err_loc(e);
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
            /* module.func 或 arch.x86_64.func 形式：base 为 import 的模块名或嵌套路径时，在依赖模块中按函数名解析 */
            if (e->value.field_access.base && e->value.field_access.field_name
                && m && m->import_paths && typeck_dep_mods && typeck_num_deps > 0) {
                char path_buf[128];
                int path_len = expr_to_import_path(e->value.field_access.base, path_buf, sizeof(path_buf));
                if (path_len >= 0) {
                    path_buf[path_len] = '\0';
                    const char *fn_name = e->value.field_access.field_name;
                    for (int j = 0; j < m->num_imports && j < typeck_num_deps; j++) {
                        if (!m->import_paths[j] || strcmp(m->import_paths[j], path_buf) != 0) continue;
                        struct ASTModule *dm = typeck_dep_mods[j];
                        if (!dm || !dm->funcs) continue;
                        for (int i = 0; i < dm->num_funcs; i++) {
                            if (!dm->funcs[i]) continue;
                            if (dm->funcs[i]->name && strcmp(dm->funcs[i]->name, fn_name) == 0) {
                                if (dm->funcs[i]->return_type)
                                    ((struct ASTExpr *)e)->resolved_type = dm->funcs[i]->return_type;
                                return 0;
                            }
                        }
                    }
                    /* base 为单 VAR 时可能是子模块引用（如 arch.x86_64）；若完整路径 mod.field 为某 import，则接受 */
                    if (e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
                        size_t plen = (size_t)path_len;
                        if (plen + 1 + strlen(fn_name) < sizeof(path_buf)) {
                            path_buf[plen] = '.';
                            strcpy(path_buf + plen + 1, fn_name);
                            for (int j = 0; j < m->num_imports; j++) {
                                if (m->import_paths[j] && strcmp(m->import_paths[j], path_buf) == 0)
                                    return 0;
                            }
                        }
                    }
                }
            }
            /* Type.Variant 形式：base 为标识符且为枚举类型名时，按枚举变体处理（§7.4）；含跨模块 import 的枚举 */
            if (e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
                const char *type_name = e->value.field_access.base->value.var.name;
                const struct ASTEnumDef *ed = find_enum_def_with_deps(enum_defs, num_enums, type_name);
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
            /* base 为模块引用（VAR 或嵌套 FIELD 且无 resolved_type）时，按 module.func 或 arch.x86_64.func 在依赖中解析 */
            if (!e->value.field_access.base->resolved_type && e->value.field_access.base && e->value.field_access.field_name
                && m && m->import_paths && typeck_dep_mods && typeck_num_deps > 0) {
                char path_buf2[128];
                int path_len2 = expr_to_import_path(e->value.field_access.base, path_buf2, sizeof(path_buf2));
                if (path_len2 >= 0) {
                    path_buf2[path_len2] = '\0';
                    const char *fn_name = e->value.field_access.field_name;
                    for (int j = 0; j < m->num_imports && j < typeck_num_deps; j++) {
                        if (!m->import_paths[j] || strcmp(m->import_paths[j], path_buf2) != 0) continue;
                        struct ASTModule *dm = typeck_dep_mods[j];
                        if (!dm || !dm->funcs) continue;
                        for (int i = 0; i < dm->num_funcs; i++) {
                            if (!dm->funcs[i]) continue;
                            if (dm->funcs[i]->name && strcmp(dm->funcs[i]->name, fn_name) == 0) {
                                if (dm->funcs[i]->return_type)
                                    ((struct ASTExpr *)e)->resolved_type = dm->funcs[i]->return_type;
                                return 0;
                            }
                        }
                    }
                    /* 未找到函数时，若 base 为 VAR，可能是子模块引用（arch.x86_64）；若 path.field 为某 import 则接受 */
                    if (e->value.field_access.base->kind == AST_EXPR_VAR && path_len2 + 1 + (int)strlen(fn_name) < (int)sizeof(path_buf2)) {
                        path_buf2[path_len2] = '.';
                        strcpy(path_buf2 + path_len2 + 1, fn_name);
                        for (int j = 0; j < m->num_imports; j++) {
                            if (m->import_paths[j] && strcmp(m->import_paths[j], path_buf2) == 0)
                                return 0;
                        }
                    }
                }
            }
            int base_kind;
            const char *base_name = NULL;
            if (get_expr_type(e->value.field_access.base, names, type_kinds, type_names, n, type_ptrs, struct_defs, num_structs, enum_defs, num_enums, &base_kind, &base_name, NULL) != 0) {
                fprintf(stderr, "typeck error: field access base has no struct or slice type");
                typeck_err_loc(e);
                return -1;
            }
            /* 切片 []T 支持 .length（usize）与 .data（*elem_type；C 侧 struct 为 data/length） */
            if (base_kind == AST_TYPE_SLICE) {
                const char *field = e->value.field_access.field_name;
                const struct ASTType *base_type = e->value.field_access.base->resolved_type;
                if (field && strcmp(field, "length") == 0) {
                    ((struct ASTExpr *)e)->resolved_type = &static_type_usize;
                    return 0;
                }
                if (field && strcmp(field, "data") == 0) {
                    if (!base_type || base_type->kind != AST_TYPE_SLICE || !base_type->elem_type) {
                        fprintf(stderr, "typeck error: slice .data requires resolved slice type");
                        typeck_err_loc(e);
                        return -1;
                    }
                    /* 当前仅支持 []u8.data → *u8；其它 elem_type 可后续扩展 static_type_ptr_* */
                    if (base_type->elem_type->kind == AST_TYPE_U8) {
                        ((struct ASTExpr *)e)->resolved_type = &static_type_ptr_u8;
                        return 0;
                    }
                    fprintf(stderr, "typeck error: slice .data currently only supported for []u8");
                    typeck_err_loc(e);
                    return -1;
                }
                fprintf(stderr, "typeck error: slice only has fields 'length' and 'data'");
                typeck_err_loc(e);
                return -1;
            }
            /* 自举：允许指针到结构体 p.field，按 pointee 结构体查字段（如 arena: *ASTArena 时 arena.num_types） */
            if ((base_kind != AST_TYPE_NAMED || !base_name) && base_kind == AST_TYPE_PTR
                && e->value.field_access.base->kind == AST_EXPR_VAR && type_ptrs) {
                const char *var_name = e->value.field_access.base->value.var.name;
                for (int vi = 0; vi < n && var_name && names[vi]; vi++)
                    if (strcmp(names[vi], var_name) == 0 && type_ptrs[vi] && type_ptrs[vi]->kind == AST_TYPE_PTR
                        && type_ptrs[vi]->elem_type && type_ptrs[vi]->elem_type->kind == AST_TYPE_NAMED
                        && type_ptrs[vi]->elem_type->name) {
                        base_name = type_ptrs[vi]->elem_type->name;
                        base_kind = AST_TYPE_NAMED;
                        break;
                    }
            }
            if (base_kind != AST_TYPE_NAMED || !base_name) {
                fprintf(stderr, "typeck error: field access requires struct type");
                typeck_err_loc(e);
                return -1;
            }
            const struct ASTStructDef *sd = find_struct_def_with_deps(struct_defs, num_structs, base_name);
            if (!sd) {
                fprintf(stderr, "typeck error: unknown struct type '%s'", base_name);
                typeck_err_loc(e);
                return -1;
            }
            const char *field = e->value.field_access.field_name;
            for (int i = 0; i < sd->num_fields; i++)
                if (sd->fields[i].name && field && strcmp(sd->fields[i].name, field) == 0) {
                    if (sd->fields[i].type)
                        ((struct ASTExpr *)e)->resolved_type = sd->fields[i].type;
                    ((struct ASTExpr *)e)->value.field_access.field_offset = sd->field_offsets[i];
                    return 0;
                }
            fprintf(stderr, "typeck error: struct '%s' has no field '%s'", base_name, field ? field : "");
            typeck_err_loc(e);
            return -1;
        }
        case AST_EXPR_STRUCT_LIT: {
            const struct ASTStructDef *sd = find_struct_def_with_deps(struct_defs, num_structs, e->value.struct_lit.struct_name);
            if (!sd) {
                fprintf(stderr, "typeck error: unknown struct type '%s'", e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "");
                typeck_err_loc(e);
                return -1;
            }
            if (e->value.struct_lit.num_fields != sd->num_fields) {
                fprintf(stderr, "typeck error: struct literal field count mismatch for '%s'", sd->name);
                typeck_err_loc(e);
                return -1;
            }
            for (int i = 0; i < sd->num_fields; i++) {
                if (!e->value.struct_lit.field_names[i] || !sd->fields[i].name ||
                    strcmp(e->value.struct_lit.field_names[i], sd->fields[i].name) != 0) {
                    fprintf(stderr, "typeck error: struct literal field name mismatch at %d", i);
                    typeck_err_loc(e);
                    return -1;
                }
                if (typeck_expr_sym(e->value.struct_lit.inits[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                /* 将字段初值的 resolved_type 设为字段类型，供 codegen 生成正确类型（如 [8]i32 的 data 用 int32_t 而非 uint8_t） */
                if (sd->fields[i].type)
                    ((struct ASTExpr *)e->value.struct_lit.inits[i])->resolved_type = sd->fields[i].type;
            }
            /* 为结构体字面量本身设 resolved_type（AST_TYPE_NAMED），供 if-expr/嵌套 else 推断 __tmp 类型，从源头消除 int __tmp 却赋 (struct X){0} 的补丁 */
            if (sd->name) {
                int ci;
                for (ci = 0; ci < struct_lit_type_n; ci++)
                    if (struct_lit_type_names[ci] && strcmp(struct_lit_type_names[ci], sd->name) == 0) break;
                if (ci >= struct_lit_type_n && struct_lit_type_n < MAX_STRUCT_LIT_TYPES) {
                    ci = struct_lit_type_n++;
                    struct_lit_type_cache[ci].kind = AST_TYPE_NAMED;
                    struct_lit_type_cache[ci].name = sd->name;
                    struct_lit_type_cache[ci].elem_type = NULL;
                    struct_lit_type_cache[ci].array_size = 0;
                    struct_lit_type_names[ci] = sd->name;
                }
                if (ci < struct_lit_type_n)
                    ((struct ASTExpr *)e)->resolved_type = &struct_lit_type_cache[ci];
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
                fprintf(stderr, "typeck error: subscript base must be array, slice or pointer");
                typeck_err_loc(e);
                return -1;
            }
            if (base_kind != AST_TYPE_ARRAY && base_kind != AST_TYPE_SLICE && base_kind != AST_TYPE_PTR) {
                fprintf(stderr, "typeck error: subscript base must be array, slice or pointer type");
                typeck_err_loc(e);
                return -1;
            }
            ((struct ASTExpr *)e)->value.index.base_is_slice = (base_kind == AST_TYPE_SLICE);
            /* BCE：下标为字面量 0 且 base 为长度≥1 的数组时，可证明在界内，codegen 可省略边界检查 */
            {
                const struct ASTExpr *idx = e->value.index.index_expr;
                const struct ASTType *base_ty = e->value.index.base->resolved_type;
                if (idx->kind == AST_EXPR_LIT && idx->value.int_val == 0 && base_ty &&
                    base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size >= 1)
                    ((struct ASTExpr *)e)->index_proven_in_bounds = 1;
            }
            /* BCE 扩展：循环内值域——若下标为变量且在当前 for 的 [0, bound) 上下文中，且 base 长度与 bound 一致则标为在界内 */
            if (!((struct ASTExpr *)e)->index_proven_in_bounds && e->value.index.index_expr->kind == AST_EXPR_VAR) {
                const char *idx_name = e->value.index.index_expr->value.var.name;
                const struct ASTType *base_ty = e->value.index.base->resolved_type;
                for (int k = 0; k < bce_n && idx_name; k++) {
                    if (!bce_var_names[k] || strcmp(bce_var_names[k], idx_name) != 0) continue;
                    if (bce_bound_const[k]) {
                        if (base_ty && base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size == bce_bound_val[k])
                            ((struct ASTExpr *)e)->index_proven_in_bounds = 1;
                        break;
                    }
                    if (base_kind == AST_TYPE_SLICE && bce_bound_base[k] &&
                        e->value.index.base == bce_bound_base[k])
                        ((struct ASTExpr *)e)->index_proven_in_bounds = 1;
                    break;
                }
            }
            /* 下标表达式类型为数组/切片/指针的元素类型（供实参匹配等使用） */
            {
                const struct ASTType *base_ty = e->value.index.base->resolved_type;
                if (base_ty && (base_ty->kind == AST_TYPE_ARRAY || base_ty->kind == AST_TYPE_SLICE || base_ty->kind == AST_TYPE_PTR) && base_ty->elem_type)
                    ((struct ASTExpr *)e)->resolved_type = base_ty->elem_type;
            }
            return 0;
        }
        case AST_EXPR_CALL: {
            const char *callee_name = NULL;
            const struct ASTFunc *func = NULL;
            int from_dep = -1;  /* 若 >=0 表示在 typeck_dep_mods[from_dep] 中找到 */
            /* 支持 module.func 或 arch.x86_64.func 形式：callee 为 FIELD_ACCESS(base, func_name) 时从 import 解析，base 可为 VAR 或嵌套 */
            if (e->value.call.callee->kind == AST_EXPR_FIELD_ACCESS
                && e->value.call.callee->value.field_access.base
                && e->value.call.callee->value.field_access.field_name
                && m && m->import_paths && typeck_dep_mods && typeck_num_deps > 0) {
                char call_path_buf[128];
                int call_path_len = expr_to_import_path(e->value.call.callee->value.field_access.base, call_path_buf, sizeof(call_path_buf));
                if (call_path_len >= 0) {
                    call_path_buf[call_path_len] = '\0';
                    const char *fn_name = e->value.call.callee->value.field_access.field_name;
                    for (int j = 0; j < m->num_imports && j < typeck_num_deps; j++) {
                        if (!m->import_paths[j] || !import_path_matches(m->import_paths[j], call_path_buf)) continue; /* 支持短名/绑定名匹配 */
                        struct ASTModule *dm = typeck_dep_mods[j];
                        if (!dm || !dm->funcs) continue;
                        for (int i = 0; i < dm->num_funcs; i++) {
                            if (!dm->funcs[i]) continue;
                            if (dm->funcs[i]->name && strcmp(dm->funcs[i]->name, fn_name) == 0) {
                                func = dm->funcs[i];
                                from_dep = j;
                                callee_name = fn_name;
                                break;
                            }
                        }
                        if (func) break;
                    }
                }
            }
            if (!func && e->value.call.callee->kind == AST_EXPR_VAR) {
                callee_name = e->value.call.callee->value.var.name;
                if (m && m->funcs) {
                    for (int i = 0; i < m->num_funcs; i++) {
                        if (!m->funcs[i]) continue;
                        if (m->funcs[i]->name && callee_name && strcmp(m->funcs[i]->name, callee_name) == 0) {
                            func = m->funcs[i];
                            break;
                        }
                    }
                }
                if (!func && typeck_dep_mods && typeck_num_deps > 0) {
                    for (int j = 0; j < typeck_num_deps; j++) {
                        if (!import_exports_name(m, j, callee_name)) continue; /* SELECT 仅导出列表中的名；BINDING 不导出 */
                        struct ASTModule *dm = typeck_dep_mods[j];
                        if (!dm || !dm->funcs) continue;
                        for (int i = 0; i < dm->num_funcs; i++) {
                            if (!dm->funcs[i]) continue;
                            if (dm->funcs[i]->name && callee_name && strcmp(dm->funcs[i]->name, callee_name) == 0) {
                                func = dm->funcs[i];
                                from_dep = j;
                                break;
                            }
                        }
                        if (func) break;
                    }
                }
            }
            if (!func) {
                if (e->value.call.callee->kind != AST_EXPR_VAR && e->value.call.callee->kind != AST_EXPR_FIELD_ACCESS) {
                    fprintf(stderr, "typeck error: call callee must be a function name");
                    typeck_err_loc(e);
                    return -1;
                }
                fprintf(stderr, "typeck error: unknown function '%s'", callee_name ? callee_name : "");
                typeck_err_loc(e);
                return -1;
            }
            /* 本模块与 import 调用均登记 resolved_callee_func，供阶段 8.1 DCE 可达性分析使用 */
            ((struct ASTExpr *)e)->value.call.resolved_callee_func = (struct ASTFunc *)func;
            if (from_dep >= 0)
                ((struct ASTExpr *)e)->value.call.resolved_import_path = m->import_paths[from_dep];
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
                    fprintf(stderr, "typeck error: function '%s' expects %d arguments, got %d",
                        callee_name, func->num_params, e->value.call.num_args);
                    typeck_err_loc(e);
                    return -1;
                }
                for (int i = 0; i < e->value.call.num_args; i++) {
                    if (typeck_expr_sym(e->value.call.args[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                    const struct ASTType *arg_type = e->value.call.args[i]->resolved_type;
                    const struct ASTType *param_type = func->params[i].type;
                    if (!arg_type || !param_type || !type_equal_subst(param_type, arg_type,
                            func->generic_param_names, e->value.call.type_args, e->value.call.num_type_args)) {
                        const struct ASTType *exp_ty = get_substituted_return_type(param_type,
                            func->generic_param_names, e->value.call.type_args, e->value.call.num_type_args);
                        char ebuf[80], fbuf[80];
                        type_to_string_buf(exp_ty ? exp_ty : param_type, ebuf, sizeof(ebuf));
                        type_to_string_buf(arg_type, fbuf, sizeof(fbuf));
                        fprintf(stderr, "typeck error: argument %d of '%s' type mismatch: expected %s, found %s",
                            i + 1, callee_name ? callee_name : "", ebuf, fbuf);
                        typeck_err_loc(e->value.call.args[i]);
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
                fprintf(stderr, "typeck error: generic function '%s' requires type arguments (e.g. %s<Type>(...))", callee_name ? callee_name : "", callee_name ? callee_name : "");
                typeck_err_loc(e);
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
                /* 允许非负整数字面量传给 usize 参数（如 fs_read 的 count；C 会隐式转换） */
                if (!ok && param_type && param_type->kind == AST_TYPE_USIZE
                    && e->value.call.args[i]->kind == AST_EXPR_LIT
                    && e->value.call.args[i]->value.int_val >= 0)
                    ok = 1;
                /* 允许整数字面量传给 i64 参数（C 会隐式转换） */
                if (!ok && param_type && param_type->kind == AST_TYPE_I64
                    && e->value.call.args[i]->kind == AST_EXPR_LIT)
                    ok = 1;
                /* 允许 0..255 整数字面量传给 u8 参数（自举 lexer 中 advance_one(l, 47) 等） */
                if (!ok && param_type && param_type->kind == AST_TYPE_U8
                    && e->value.call.args[i]->kind == AST_EXPR_LIT) {
                    int v = e->value.call.args[i]->value.int_val;
                    if (v >= 0 && v <= 255) ok = 1;
                }
                /* 允许数组字面量 [x, y, ...] 传给 []u8 参数（如 match_keyword 的 keyword）；设 resolved_type 为参数类型供 codegen 生成 slice 复合字面量 */
                if (!ok && param_type && param_type->kind == AST_TYPE_SLICE && param_type->elem_type
                    && param_type->elem_type->kind == AST_TYPE_U8
                    && e->value.call.args[i]->kind == AST_EXPR_ARRAY_LIT) {
                    ok = 1;
                    ((struct ASTExpr *)e->value.call.args[i])->resolved_type = param_type;
                }
                /* 允许数组 [N]T 传给 *T 参数（数组到指针衰减，如 fs_open_read(path)、fs_read(fd, buf, n)；9.1 联调） */
                if (!ok && param_type && param_type->kind == AST_TYPE_PTR && arg_type && arg_type->kind == AST_TYPE_ARRAY
                    && param_type->elem_type && arg_type->elem_type && type_equal(param_type->elem_type, arg_type->elem_type))
                    ok = 1;
                /* 允许任意指针 *T 传给 *u8 参数（extern 中 *u8 表示 C 的 void*，如 pipeline_run_su_pipeline 的 out_buf/ctx） */
                if (!ok && param_type && param_type->kind == AST_TYPE_PTR && param_type->elem_type && param_type->elem_type->kind == AST_TYPE_U8
                    && arg_type && arg_type->kind == AST_TYPE_PTR)
                    ok = 1;
                /* 取址 &expr 可传给 *u8 参数（&out、&ctx 等；此时 arg_type 可能尚未设为指针类型） */
                if (!ok && param_type && param_type->kind == AST_TYPE_PTR && param_type->elem_type && param_type->elem_type->kind == AST_TYPE_U8
                    && e->value.call.args[i]->kind == AST_EXPR_ADDR_OF)
                    ok = 1;
                /* 取址 &expr 可传给 *T 参数：要求 expr 的类型与 T 一致（如 driver_argv_parse_su(..., &state)） */
                if (!ok && param_type && param_type->kind == AST_TYPE_PTR && param_type->elem_type
                    && e->value.call.args[i]->kind == AST_EXPR_ADDR_OF) {
                    const struct ASTExpr *operand = e->value.call.args[i]->value.unary.operand;
                    if (operand->resolved_type && type_equal(param_type->elem_type, operand->resolved_type))
                        ok = 1;
                }
                if (!ok) {
                    char ebuf[80], fbuf[80];
                    type_to_string_buf(param_type, ebuf, sizeof(ebuf));
                    type_to_string_buf(arg_type, fbuf, sizeof(fbuf));
                    fprintf(stderr, "typeck error: argument %d of '%s' type mismatch: expected %s, found %s",
                        i + 1, callee_name ? callee_name : "", ebuf, fbuf);
                    typeck_err_loc(e->value.call.args[i]);
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
            const char *method_name = e->value.method_call.method_name;
            /* module.func 或 arch.x86_64.func 形式：base 为模块引用（VAR 或嵌套 FIELD 且无 resolved_type）时，在依赖中按函数名解析 */
            if (!base_ty && e->value.method_call.base && method_name
                && m && m->import_paths && typeck_dep_mods && typeck_num_deps > 0) {
                char meth_path_buf[128];
                int meth_path_len = expr_to_import_path(e->value.method_call.base, meth_path_buf, sizeof(meth_path_buf));
                if (meth_path_len >= 0) {
                    meth_path_buf[meth_path_len] = '\0';
                    for (int j = 0; j < m->num_imports && j < typeck_num_deps; j++) {
                        /* 支持短名匹配：process.getenv 中 "process" 匹配 import_paths[j]=="std.process"（最后一段） */
                        if (!m->import_paths[j] || !import_path_matches(m->import_paths[j], meth_path_buf)) continue;
                        struct ASTModule *dm = typeck_dep_mods[j];
                    if (!dm || !dm->funcs) continue;
                    for (int i = 0; i < dm->num_funcs; i++) {
                        if (!dm->funcs[i]) continue;
                        if (dm->funcs[i]->name && strcmp(dm->funcs[i]->name, method_name) == 0) {
                            struct ASTFunc *func = dm->funcs[i];
                            if (e->value.method_call.num_args != func->num_params) {
                                fprintf(stderr, "typeck error: function '%s' expects %d arguments, got %d\n",
                                    method_name, func->num_params, e->value.method_call.num_args);
                                typeck_err_loc(e);
                                return -1;
                            }
                            for (int ai = 0; ai < e->value.method_call.num_args; ai++) {
                                if (typeck_expr_sym(e->value.method_call.args[ai], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                                const struct ASTType *arg_type = e->value.method_call.args[ai]->resolved_type;
                                const struct ASTType *param_type = func->params[ai].type;
                                /* 取址 &expr 未填 resolved_type 时：若形参为 *T 且 operand 类型为 T，则补全为形参类型并接受 */
                                if ((!arg_type || !type_equal(arg_type, param_type))
                                    && param_type && param_type->kind == AST_TYPE_PTR && param_type->elem_type
                                    && e->value.method_call.args[ai]->kind == AST_EXPR_ADDR_OF
                                    && e->value.method_call.args[ai]->value.unary.operand) {
                                    const struct ASTExpr *operand = e->value.method_call.args[ai]->value.unary.operand;
                                    if (operand->resolved_type && type_equal(param_type->elem_type, operand->resolved_type)) {
                                        ((struct ASTExpr *)e->value.method_call.args[ai])->resolved_type = param_type;
                                        arg_type = param_type;
                                    }
                                }
                                /* 允许数组 [N]T 传给 *T 参数（数组到指针衰减，如 platform.elf.append_elf_bytes(ctx, buf, n)） */
                                if ((!arg_type || !type_equal(arg_type, param_type))
                                    && param_type && param_type->kind == AST_TYPE_PTR && arg_type && arg_type->kind == AST_TYPE_ARRAY
                                    && param_type->elem_type && arg_type->elem_type && type_equal(param_type->elem_type, arg_type->elem_type)) {
                                    ((struct ASTExpr *)e->value.method_call.args[ai])->resolved_type = param_type;
                                    arg_type = param_type;
                                }
                                if (!arg_type || !param_type || !type_equal(arg_type, param_type)) {
                                    fprintf(stderr, "typeck error: argument %d of '%s' type mismatch", ai + 1, method_name ? method_name : "");
                                    typeck_err_loc(e->value.method_call.args[ai]);
                                    return -1;
                                }
                            }
                            if (func->return_type)
                                ((struct ASTExpr *)e)->resolved_type = func->return_type;
                            ((struct ASTExpr *)e)->value.method_call.resolved_impl_func = func;
                            ((struct ASTExpr *)e)->value.method_call.resolved_import_path = m->import_paths[j];
                            return 0;
                        }
                    }
                }
                }
            }
            if (!base_ty) {
                fprintf(stderr, "typeck error: method call base has no type");
                typeck_err_loc(e);
                return -1;
            }
            const char *type_str = type_to_name_string(base_ty);
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
                fprintf(stderr, "typeck error: no impl for type '%s' with method '%s'", type_str ? type_str : "?", method_name ? method_name : "?");
                typeck_err_loc(e);
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
                    fprintf(stderr, "typeck error: argument %d of method '%s' type mismatch", i + 1, method_name ? method_name : "");
                    typeck_err_loc(e->value.method_call.args[i]);
                    return -1;
                }
            }
            ((struct ASTExpr *)e)->resolved_type = impl_func->return_type;
            ((struct ASTExpr *)e)->value.method_call.resolved_impl_func = impl_func;
            return 0;
        }
        default:
            fprintf(stderr, "typeck error: unsupported expression kind");
            typeck_err_loc(e);
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
 * 对块做类型检查；parent_names/... 为外层符号表；parent_const_values/parent_n_consts 为外层 const 求值结果（CTFE）；inside_loop 表示当前块是否为某 while 体。
 */
static int typeck_block(const struct ASTBlock *b, const char **parent_names,
    const int *parent_type_kinds, const char **parent_type_names, const struct ASTType **parent_type_ptrs, int parent_n,
    const int *parent_const_values, int parent_n_consts,
    int inside_loop,
    struct ASTStructDef **struct_defs, int num_structs, struct ASTEnumDef **enum_defs, int num_enums, const struct ASTModule *m,
    const struct ASTType *func_return_type) {
    if (!b) return -1;
    /* 允许空块 {}（如 if (x) { } 的 then 体）；仅当块完全为空且无 final_expr 时放行，不视为错误 */
    if (!b->final_expr && b->num_labeled_stmts == 0 && b->num_expr_stmts == 0
        && b->num_consts == 0 && b->num_lets == 0 && b->num_loops == 0 && b->num_for_loops == 0 && b->num_defers == 0)
        return 0;
    const char *names[MAX_SYMTAB];
    int type_kinds[MAX_SYMTAB];
    const char *type_names[MAX_SYMTAB];
    const struct ASTType *type_ptrs[MAX_SYMTAB];
    int const_values[MAX_SYMTAB]; /* CTFE：当前作用域 const 的求值结果，仅 names[0..n_consts) 为 const */
    int n = parent_n < MAX_SYMTAB ? parent_n : 0;
    for (int i = 0; i < n && parent_names; i++) {
        names[i] = parent_names[i];
        type_kinds[i] = (parent_type_kinds && i < parent_n) ? parent_type_kinds[i] : AST_TYPE_I32;
        type_names[i] = (parent_type_names && i < parent_n) ? parent_type_names[i] : NULL;
        type_ptrs[i] = (parent_type_ptrs && i < parent_n) ? parent_type_ptrs[i] : NULL;
        const_values[i] = (parent_const_values && i < parent_n_consts) ? parent_const_values[i] : 0;
    }
    int const_start = n; /* 当前块 const 在 names 中的起始下标（进入 const 循环前 n = parent_n） */
    int n_consts = 0;
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
        const_values[n] = eval_const_int(b->const_decls[i].init, names, const_values, n);
        fold_expr((struct ASTExpr *)b->const_decls[i].init, names, const_values, i, const_start, parent_n_consts);
        /* 数组初值：= [] 表示全零初始化；= [e1,e2,...] 可写不超过声明长度的元素，不足部分按 0 填充 */
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            int narr = b->const_decls[i].init->value.array_lit.num_elems;
            int decl_size = b->const_decls[i].type->array_size;
            if (narr > decl_size) {
                fprintf(stderr, "typeck error: array literal length exceeds declaration size\n");
                return -1;
            }
            /* 将数组字面量 resolved_type 设为声明类型，供 codegen 生成 { e1,... } 或 { 0 }，C 对未写元素零初始化 */
            ((struct ASTExpr *)b->const_decls[i].init)->resolved_type = b->const_decls[i].type;
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
        /* f32/f64 初值：浮点字面量或整数字面量 0；非零整数字面量禁止（避免隐式截断）；浮点字面量设 resolved_type 供 codegen 生成 0.0f/0.0 */
        if (b->const_decls[i].type && (b->const_decls[i].type->kind == AST_TYPE_F32 || b->const_decls[i].type->kind == AST_TYPE_F64) && b->const_decls[i].init) {
            const struct ASTExpr *init = b->const_decls[i].init;
            if (init->kind == AST_EXPR_FLOAT_LIT)
                ((struct ASTExpr *)init)->resolved_type = b->const_decls[i].type;
            else if (init->kind == AST_EXPR_LIT && init->value.int_val == 0)
                ;
            else if (init->kind == AST_EXPR_LIT && init->value.int_val != 0) {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal or integer 0\n");
                return -1;
            }
            else if (init->resolved_type && (init->resolved_type->kind == AST_TYPE_I32 || init->resolved_type->kind == AST_TYPE_F32 || init->resolved_type->kind == AST_TYPE_F64))
                ;
            else if (init->kind == AST_EXPR_VAR) {
                const char *v = init->value.var.name;
                int allow = 0;
                for (int k = 0; k < n && v; k++)
                    if (names[k] && strcmp(names[k], v) == 0 && (type_kinds[k] == AST_TYPE_I32 || type_kinds[k] == AST_TYPE_F32 || type_kinds[k] == AST_TYPE_F64)) { allow = 1; break; }
                if (!allow) {
                    fprintf(stderr, "typeck error: f32/f64 init must be float literal, integer 0, or numeric expression\n");
                    return -1;
                }
            }
            else {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal, integer 0, or numeric expression\n");
                return -1;
            }
        }
        type_kinds[n] = b->const_decls[i].type ? b->const_decls[i].type->kind : AST_TYPE_I32;
        type_names[n] = (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_NAMED) ? b->const_decls[i].type->name : NULL;
        type_ptrs[n] = b->const_decls[i].type;
        names[n++] = b->const_decls[i].name;
        n_consts++;
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (n >= MAX_SYMTAB) {
            fprintf(stderr, "typeck error: too many declarations\n");
            return -1;
        }
        if (typeck_expr_sym(b->let_decls[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        fold_expr((struct ASTExpr *)b->let_decls[i].init, names, const_values, n_consts, const_start, parent_n_consts);
        /* 数组初值：= [] 表示全零初始化；= [e1,e2,...] 可写不超过声明长度的元素，不足部分按 0 填充 */
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_ARRAY &&
            b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_ARRAY_LIT) {
            int narr = b->let_decls[i].init->value.array_lit.num_elems;
            int decl_size = b->let_decls[i].type->array_size;
            if (narr > decl_size) {
                fprintf(stderr, "typeck error: array literal length exceeds declaration size\n");
                return -1;
            }
            /* 将数组字面量 resolved_type 设为声明类型，供 codegen 生成 { e1,... } 或 { 0 }，C 对未写元素零初始化 */
            ((struct ASTExpr *)b->let_decls[i].init)->resolved_type = b->let_decls[i].type;
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
        /* f32/f64 初值：浮点字面量或整数字面量 0；非零整数字面量禁止（避免隐式截断）；浮点字面量设 resolved_type 供 codegen 生成 0.0f/0.0 */
        if (b->let_decls[i].type && (b->let_decls[i].type->kind == AST_TYPE_F32 || b->let_decls[i].type->kind == AST_TYPE_F64) && b->let_decls[i].init) {
            const struct ASTExpr *init = b->let_decls[i].init;
            if (init->kind == AST_EXPR_FLOAT_LIT)
                ((struct ASTExpr *)init)->resolved_type = b->let_decls[i].type;
            else if (init->kind == AST_EXPR_LIT && init->value.int_val == 0)
                ;
            else if (init->kind == AST_EXPR_LIT && init->value.int_val != 0) {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal or integer 0\n");
                return -1;
            }
            else if (init->resolved_type && (init->resolved_type->kind == AST_TYPE_I32 || init->resolved_type->kind == AST_TYPE_F32 || init->resolved_type->kind == AST_TYPE_F64))
                ;
            else if (init->kind == AST_EXPR_VAR) {
                const char *v = init->value.var.name;
                int allow = 0;
                for (int k = 0; k < n && v; k++)
                    if (names[k] && strcmp(names[k], v) == 0 && (type_kinds[k] == AST_TYPE_I32 || type_kinds[k] == AST_TYPE_F32 || type_kinds[k] == AST_TYPE_F64)) { allow = 1; break; }
                if (!allow) {
                    fprintf(stderr, "typeck error: f32/f64 init must be float literal, integer 0, or numeric expression\n");
                    return -1;
                }
            }
            else {
                fprintf(stderr, "typeck error: f32/f64 init must be float literal, integer 0, or numeric expression\n");
                return -1;
            }
        }
        type_kinds[n] = b->let_decls[i].type ? b->let_decls[i].type->kind : AST_TYPE_I32;
        type_names[n] = (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_NAMED) ? b->let_decls[i].type->name : NULL;
        type_ptrs[n] = b->let_decls[i].type;
        names[n++] = b->let_decls[i].name;
    }
    for (int i = 0; i < b->num_loops; i++) {
        const struct ASTExpr *cond_while = b->loops[i].cond;
        if (typeck_expr_sym(cond_while, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        fold_expr((struct ASTExpr *)cond_while, names, const_values, n_consts, const_start, parent_n_consts);
        if (!expr_produces_bool(cond_while, names, type_kinds, n)) {
            if (!typeck_fill_only) {
                fprintf(stderr, "typeck error: while condition must be bool (no implicit int-to-bool)\n");
                return -1;
            }
        }
        if (typeck_block(b->loops[i].body, names, type_kinds, type_names, type_ptrs, n, const_values, n_consts, 1, struct_defs, num_structs, enum_defs, num_enums, m, func_return_type) != 0) return -1;
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init && typeck_expr_sym(b->for_loops[i].init, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (b->for_loops[i].init) fold_expr((struct ASTExpr *)b->for_loops[i].init, names, const_values, n_consts, const_start, parent_n_consts);
        if (b->for_loops[i].cond) {
            const struct ASTExpr *cond_for = b->for_loops[i].cond;
            if (typeck_expr_sym(cond_for, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
            fold_expr((struct ASTExpr *)cond_for, names, const_values, n_consts, const_start, parent_n_consts);
            if (!expr_produces_bool(cond_for, names, type_kinds, n)) {
                if (!typeck_fill_only) {
                    fprintf(stderr, "typeck error: for condition must be bool (no implicit int-to-bool)\n");
                    return -1;
                }
            }
        }
        if (b->for_loops[i].step && typeck_expr_sym(b->for_loops[i].step, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
        if (b->for_loops[i].step) fold_expr((struct ASTExpr *)b->for_loops[i].step, names, const_values, n_consts, const_start, parent_n_consts);
        /* BCE 扩展：从 for 条件 i < bound 推断循环变量值域 [0, bound)，供体内 INDEX 消除边界检查 */
        {
            int saved_bce = bce_n;
            const struct ASTExpr *cond = b->for_loops[i].cond;
            if (cond && cond->kind == AST_EXPR_LT && bce_n < MAX_BCE_RANGES) {
                const struct ASTExpr *left = cond->value.binop.left;
                const struct ASTExpr *right = cond->value.binop.right;
                if (left && left->kind == AST_EXPR_VAR && left->value.var.name) {
                    bce_var_names[bce_n] = left->value.var.name;
                    if (right->kind == AST_EXPR_LIT) {
                        bce_bound_const[bce_n] = 1;
                        bce_bound_val[bce_n] = right->value.int_val;
                        bce_bound_base[bce_n] = NULL;
                        bce_n++;
                    } else if (right->kind == AST_EXPR_VAR && right->value.var.name) {
                        int j;
                        for (j = 0; j < n && (!names[j] || strcmp(names[j], right->value.var.name) != 0); j++) ;
                        if (j < n && j >= const_start && j < const_start + n_consts) {
                            bce_bound_const[bce_n] = 1;
                            bce_bound_val[bce_n] = const_values[j];
                            bce_bound_base[bce_n] = NULL;
                            bce_n++;
                        }
                    } else if (right->kind == AST_EXPR_FIELD_ACCESS && right->value.field_access.field_name &&
                               strcmp(right->value.field_access.field_name, "length") == 0 &&
                               right->value.field_access.base) {
                        bce_bound_const[bce_n] = 0;
                        bce_bound_val[bce_n] = 0;
                        bce_bound_base[bce_n] = right->value.field_access.base;
                        bce_n++;
                    }
                }
            }
            if (typeck_block(b->for_loops[i].body, names, type_kinds, type_names, type_ptrs, n, const_values, n_consts, 1, struct_defs, num_structs, enum_defs, num_enums, m, func_return_type) != 0) return -1;
            bce_n = saved_bce;
        }
    }
    for (int i = 0; i < b->num_defers; i++) {
        if (typeck_block(b->defer_blocks[i], names, type_kinds, type_names, type_ptrs, n, const_values, n_consts, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m, func_return_type) != 0) return -1;
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN) {
            if (!b->labeled_stmts[i].u.return_expr) {
                /* func_return_type 为 NULL 表示块表达式上下文（如 if 体），允许 return; */
                if (func_return_type && func_return_type->kind != AST_TYPE_VOID) {
                    fprintf(stderr, "typeck error: return; only allowed in void function\n");
                    return -1;
                }
            } else {
                if (func_return_type && func_return_type->kind == AST_TYPE_VOID) {
                    fprintf(stderr, "typeck error: void function cannot return a value\n");
                    return -1;
                }
                if (typeck_expr_sym(b->labeled_stmts[i].u.return_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
                fold_expr((struct ASTExpr *)b->labeled_stmts[i].u.return_expr, names, const_values, n_consts, const_start, parent_n_consts);
            }
        }
    }
    for (int i = 0; i < b->num_expr_stmts; i++) {
        if (typeck_expr_sym(b->expr_stmts[i], names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
    }
    if (!b->final_expr) return 0;
    if (b->final_expr->kind == AST_EXPR_RETURN && !b->final_expr->value.unary.operand) {
        if (func_return_type && func_return_type->kind != AST_TYPE_VOID) {
            fprintf(stderr, "typeck error: return; only allowed in void function\n");
            return -1;
        }
    } else if (b->final_expr->kind == AST_EXPR_RETURN && b->final_expr->value.unary.operand && func_return_type && func_return_type->kind == AST_TYPE_VOID) {
        fprintf(stderr, "typeck error: void function cannot return a value\n");
        return -1;
    }
    if (typeck_expr_sym(b->final_expr, names, type_kinds, type_names, n, type_ptrs, inside_loop, struct_defs, num_structs, enum_defs, num_enums, m) != 0) return -1;
    fold_expr((struct ASTExpr *)b->final_expr, names, const_values, n_consts, const_start, parent_n_consts);
    return 0;
}

/* ---------- .su typeck 查询 API：供 typeck.su 读取 AST，实现 main 等检查迁入 .su ---------- */
void *typeck_su_get_main_func(void *mod) {
    struct ASTModule *m = (struct ASTModule *)mod;
    return m ? (void *)m->main_func : NULL;
}
int typeck_su_func_return_kind(void *func) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    if (!f || !f->return_type) return -1;
    return f->return_type->kind;
}
int typeck_su_func_is_extern(void *func) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    return f ? f->is_extern : 0;
}
int typeck_su_func_has_body(void *func) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    return (f && f->body) ? 1 : 0;
}
int typeck_su_func_is_generic(void *func) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    return (f && f->num_generic_params > 0) ? 1 : 0;
}
void *typeck_su_func_body(void *func) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    return f ? (void *)f->body : NULL;
}
int typeck_su_block_has_implicit_return(const void *block) {
    return block_has_implicit_return((const struct ASTBlock *)block);
}
int typeck_su_ast_type_i32(void) { return AST_TYPE_I32; }
int typeck_su_ast_type_i64(void) { return AST_TYPE_I64; }

/**
 * 全面自举（重写实现）：仅填 resolved_type，不做任何语义检查；.su 用访问器遍历并做检查。
 * 返回与 typeck_module 相同（0 成功填类型，-1 推导失败等）。
 */
int typeck_su_fill_resolved_types(void *mod, void *dep_mods, int num_deps) {
    typeck_fill_only = 1;
    int r = typeck_module((struct ASTModule *)mod, (struct ASTModule **)dep_mods, num_deps, NULL, 0);
    typeck_fill_only = 0;
    return r;
}

/** 全面自举：块访问器，供 .su 遍历并检查条件须为 bool。 */
int typeck_su_block_num_loops(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? b->num_loops : 0;
}
void *typeck_su_block_loop_cond(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->loops || i < 0 || i >= b->num_loops) return NULL;
    return (void *)b->loops[i].cond;
}
void *typeck_su_block_loop_body(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->loops || i < 0 || i >= b->num_loops) return NULL;
    return (void *)b->loops[i].body;
}
int typeck_su_block_num_for_loops(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? b->num_for_loops : 0;
}
void *typeck_su_block_for_cond(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || i < 0 || i >= b->num_for_loops) return NULL;
    return (void *)b->for_loops[i].cond;
}
void *typeck_su_block_for_body(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || i < 0 || i >= b->num_for_loops) return NULL;
    return (void *)b->for_loops[i].body;
}
/** 表达式 resolved_type 的 kind；无类型或 expr 为空返回 -1。 */
int typeck_su_expr_type_kind(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->resolved_type) ? (int)e->resolved_type->kind : -1;
}
int typeck_su_ast_type_bool(void) { return AST_TYPE_BOOL; }

/** 块内表达式语句个数与第 i 个、最终表达式；供 .su 遍历 if/三元。 */
int typeck_su_block_num_expr_stmts(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? b->num_expr_stmts : 0;
}
void *typeck_su_block_expr_stmt(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->expr_stmts || i < 0 || i >= b->num_expr_stmts) return NULL;
    return (void *)b->expr_stmts[i];
}
void *typeck_su_block_final_expr(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? (void *)b->final_expr : NULL;
}

/** .su 自实现 typeck 用：块内 const/let 个数及「声明类型与初值类型一致」检查。 */
int typeck_su_block_num_consts(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? b->num_consts : 0;
}
int typeck_su_block_num_lets(const void *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? b->num_lets : 0;
}
/** 返回 1 表示第 i 个 const 的声明类型与初值表达式 resolved_type 一致，0 表示不一致或无效。 */
int typeck_su_block_const_type_matches_init(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->const_decls || i < 0 || i >= b->num_consts) return 0;
    const struct ASTType *ty = b->const_decls[i].type;
    const struct ASTExpr *init = b->const_decls[i].init;
    if (!ty) return 1;
    if (!init || !init->resolved_type) return 0;
    return type_equal(ty, init->resolved_type) ? 1 : 0;
}
/** 返回 1 表示第 i 个 let 的声明类型与初值表达式 resolved_type 一致，0 表示不一致或无效。 */
int typeck_su_block_let_type_matches_init(const void *block, int i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->let_decls || i < 0 || i >= b->num_lets) return 0;
    const struct ASTType *ty = b->let_decls[i].type;
    const struct ASTExpr *init = b->let_decls[i].init;
    if (!ty) return 1;
    if (!init || !init->resolved_type) return 0;
    return type_equal(ty, init->resolved_type) ? 1 : 0;
}

/** 表达式节点 kind（ASTExprKind）；IF/TERNARY 共用 if_expr 字段。 */
int typeck_su_expr_kind(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return e ? (int)e->kind : -1;
}
void *typeck_su_expr_if_cond(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || (e->kind != AST_EXPR_IF && e->kind != AST_EXPR_TERNARY)) return NULL;
    return (void *)e->value.if_expr.cond;
}
void *typeck_su_expr_if_then(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || (e->kind != AST_EXPR_IF && e->kind != AST_EXPR_TERNARY)) return NULL;
    return (void *)e->value.if_expr.then_expr;
}
void *typeck_su_expr_if_else(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || (e->kind != AST_EXPR_IF && e->kind != AST_EXPR_TERNARY)) return NULL;
    return (void *)e->value.if_expr.else_expr;
}
void *typeck_su_expr_block(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_BLOCK) return NULL;
    return (void *)e->value.block;
}
int typeck_su_expr_kind_if(void) { return AST_EXPR_IF; }
int typeck_su_expr_kind_ternary(void) { return AST_EXPR_TERNARY; }
int typeck_su_expr_kind_block(void) { return AST_EXPR_BLOCK; }
int typeck_su_expr_kind_assign(void) { return AST_EXPR_ASSIGN; }
void *typeck_su_expr_assign_left(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_ASSIGN) return NULL;
    return (void *)e->value.binop.left;
}
void *typeck_su_expr_assign_right(const void *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_ASSIGN) return NULL;
    return (void *)e->value.binop.right;
}
int typeck_su_types_equal(const void *expr_a, const void *expr_b) {
    const struct ASTExpr *a = (const struct ASTExpr *)expr_a;
    const struct ASTExpr *b = (const struct ASTExpr *)expr_b;
    if (!a || !b || !a->resolved_type || !b->resolved_type) return 0;
    return type_equal(a->resolved_type, b->resolved_type) ? 1 : 0;
}

/**
 * .su 自实现 typeck 用：块体的「结果类型」是否与函数声明的返回类型一致。
 * 非 void 函数：块 final_expr 须为表达式或 return expr，其 resolved_type 与 func->return_type 一致。
 * void 函数：块 final_expr 不得为「带操作数的 return」。
 * 返回 1 一致，0 不一致或无效。
 */
int typeck_su_block_result_matches_func_return(const void *func, const void *block) {
    const struct ASTFunc *f = (const struct ASTFunc *)func;
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!f || !f->return_type || !b) return 0;
    const struct ASTExpr *fe = b->final_expr;
    if (f->return_type->kind == AST_TYPE_VOID) {
        if (fe && fe->kind == AST_EXPR_RETURN && fe->value.unary.operand) return 0;
        return 1;
    }
    if (!fe) return 0;
    const struct ASTType *block_ty = NULL;
    if (fe->kind == AST_EXPR_RETURN && fe->value.unary.operand)
        block_ty = fe->value.unary.operand->resolved_type;
    else if (fe->kind != AST_EXPR_RETURN && fe->kind != AST_EXPR_PANIC && fe->kind != AST_EXPR_BREAK && fe->kind != AST_EXPR_CONTINUE)
        block_ty = fe->resolved_type;
    if (!block_ty) return 0;
    return type_equal(block_ty, f->return_type) ? 1 : 0;
}

/** 模块内函数个数；mod 为空返回 0。 */
int typeck_su_module_num_funcs(const void *mod) {
    const struct ASTModule *m = (const struct ASTModule *)mod;
    return m ? m->num_funcs : 0;
}
/** 模块内第 i 个函数；越界或 mod 为空返回 NULL。 */
void *typeck_su_module_func(const void *mod, int i) {
    const struct ASTModule *m = (const struct ASTModule *)mod;
    if (!m || !m->funcs || i < 0 || i >= m->num_funcs) return NULL;
    return (void *)m->funcs[i];
}
/** impl 块内函数：impl_blocks[k].funcs[j]；越界返回 NULL。 */
int typeck_su_module_num_impl_blocks(const void *mod) {
    const struct ASTModule *m = (const struct ASTModule *)mod;
    return m ? m->num_impl_blocks : 0;
}
int typeck_su_impl_block_num_funcs(const void *mod, int k) {
    const struct ASTModule *m = (const struct ASTModule *)mod;
    if (!m || !m->impl_blocks || k < 0 || k >= m->num_impl_blocks) return 0;
    return m->impl_blocks[k]->num_funcs;
}
void *typeck_su_impl_block_func(const void *mod, int k, int j) {
    const struct ASTModule *m = (const struct ASTModule *)mod;
    if (!m || !m->impl_blocks || k < 0 || k >= m->num_impl_blocks) return NULL;
    const struct ASTImplBlock *impl = m->impl_blocks[k];
    if (!impl->funcs || j < 0 || j >= impl->num_funcs) return NULL;
    return (void *)impl->funcs[j];
}

/**
 * 对模块做类型检查；功能、参数、返回值见 typeck.h 声明处注释。
 */
int typeck_module(struct ASTModule *m, struct ASTModule **dep_mods, int num_deps, struct ASTModule **all_dep_mods, int n_all_deps) {
    if (!m) {
        fprintf(stderr, "typeck error: null module\n");
        return -1;
    }
    /* 布局阶段使用全部传递依赖（若有），以便依赖内结构体引用其他依赖类型时能解析（如 parser 的 OneFuncResult.next_lex: Lexer） */
    struct ASTModule **layout_deps = (all_dep_mods && n_all_deps > 0) ? all_dep_mods : dep_mods;
    int layout_ndeps = (all_dep_mods && n_all_deps > 0) ? n_all_deps : num_deps;
    typeck_dep_mods = layout_deps;
    typeck_num_deps = layout_ndeps;
    /* 先为所有依赖模块计算结构体布局（按 layout_deps 顺序，保证拓扑序如 lexer 在 parser 前） */
    if (layout_deps && layout_ndeps > 0) {
        for (int j = 0; j < layout_ndeps; j++) {
            if (!layout_deps[j]) continue;
            if (layout_deps[j]->struct_defs && layout_deps[j]->num_structs > 0 &&
                compute_struct_layouts(layout_deps[j]->struct_defs, layout_deps[j]->num_structs, layout_deps[j]->enum_defs, layout_deps[j]->num_enums) != 0)
                return -1;
        }
    }
    /* 本模块结构体布局（库模块也计算，供入口模块引用；§11.1） */
    if (m->struct_defs && m->num_structs > 0 && compute_struct_layouts(m->struct_defs, m->num_structs, m->enum_defs, m->num_enums) != 0)
        return -1;
    /* 后续 CALL 解析等仍用直接依赖 dep_mods */
    typeck_dep_mods = dep_mods;
    typeck_num_deps = num_deps;

    /* 顶层 let：按顺序 typeck 每个 init（作用域为前面的顶层 let + import 符号），并校验 init 类型与声明类型一致 */
    if (m->top_level_lets && m->num_top_level_lets > 0) {
        const char *tl_names[MAX_SYMTAB];
        int tl_type_kinds[MAX_SYMTAB];
        const char *tl_type_names[MAX_SYMTAB];
        const struct ASTType *tl_type_ptrs[MAX_SYMTAB];
        int tl_n = 0;
        for (int i = 0; i < m->num_top_level_lets; i++) {
            if (tl_n >= MAX_SYMTAB) {
                fprintf(stderr, "typeck error: too many top-level lets\n");
                return -1;
            }
            if (typeck_expr_sym(m->top_level_lets[i].init, tl_names, tl_type_kinds, tl_type_names, tl_n, tl_type_ptrs, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m) != 0)
                return -1;
            if (m->top_level_lets[i].type && m->top_level_lets[i].init->resolved_type
                && !type_equal(m->top_level_lets[i].type, m->top_level_lets[i].init->resolved_type)) {
                fprintf(stderr, "typeck error: top-level let init type mismatch\n");
                return -1;
            }
            tl_names[tl_n] = m->top_level_lets[i].name;
            tl_type_kinds[tl_n] = m->top_level_lets[i].type ? m->top_level_lets[i].type->kind : AST_TYPE_I32;
            tl_type_names[tl_n] = (m->top_level_lets[i].type && m->top_level_lets[i].type->kind == AST_TYPE_NAMED) ? m->top_level_lets[i].type->name : NULL;
            tl_type_ptrs[tl_n] = m->top_level_lets[i].type;
            tl_n++;
        }
    }

    /* 库模块也需对每个函数体做 typeck，以便设置 resolved_type 等供 codegen 使用（如结构体字面量内数组字面量类型） */
    if (!m->main_func) {
        for (int i = 0; i < m->num_funcs; i++) {
            const struct ASTFunc *f = m->funcs[i];
            if (!f->body) continue;
            if (f->num_generic_params > 0) continue;
            const char *names[MAX_SYMTAB];
            int type_kinds[MAX_SYMTAB];
            const char *type_names[MAX_SYMTAB];
            const struct ASTType *type_ptrs[MAX_SYMTAB];
            int n = 0;
            for (int j = 0; j < f->num_params && n < MAX_SYMTAB; j++) {
                names[n] = f->params[j].name;
                type_kinds[n] = f->params[j].type ? f->params[j].type->kind : AST_TYPE_I32;
                type_names[n] = (f->params[j].type && f->params[j].type->kind == AST_TYPE_NAMED) ? f->params[j].type->name : NULL;
                type_ptrs[n] = f->params[j].type;
                n++;
            }
            for (int t = 0; m->top_level_lets && t < m->num_top_level_lets && n < MAX_SYMTAB; t++) {
                names[n] = m->top_level_lets[t].name;
                type_kinds[n] = m->top_level_lets[t].type ? m->top_level_lets[t].type->kind : AST_TYPE_I32;
                type_names[n] = (m->top_level_lets[t].type && m->top_level_lets[t].type->kind == AST_TYPE_NAMED) ? m->top_level_lets[t].type->name : NULL;
                type_ptrs[n] = m->top_level_lets[t].type;
                n++;
            }
            if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, NULL, 0, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m, f->return_type) != 0)
                return -1;
        }
        return 0;
    }

#ifndef SHUC_USE_SU_TYPECK
    /* 未使用 .su typeck 入口时，在此做 main 校验；使用 .su 时由 typeck.su 在调用 typeck_module 前完成。 */
    if (!m->main_func->return_type ||
        (m->main_func->return_type->kind != AST_TYPE_I32 && m->main_func->return_type->kind != AST_TYPE_I64)) {
        fprintf(stderr, "typeck error: main must return i32 or i64\n");
        return -1;
    }
    if (m->main_func->is_extern) {
        fprintf(stderr, "typeck error: main cannot be extern\n");
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
#endif

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
                int n = 0;
                for (int i = 0; i < f->num_params && n < MAX_SYMTAB; i++) {
                    names[n] = f->params[i].name;
                    type_kinds[n] = f->params[i].type ? f->params[i].type->kind : AST_TYPE_I32;
                    type_names[n] = (f->params[i].type && f->params[i].type->kind == AST_TYPE_NAMED) ? f->params[i].type->name : NULL;
                    type_ptrs[n] = f->params[i].type;
                    n++;
                }
                for (int t = 0; m->top_level_lets && t < m->num_top_level_lets && n < MAX_SYMTAB; t++) {
                    names[n] = m->top_level_lets[t].name;
                    type_kinds[n] = m->top_level_lets[t].type ? m->top_level_lets[t].type->kind : AST_TYPE_I32;
                    type_names[n] = (m->top_level_lets[t].type && m->top_level_lets[t].type->kind == AST_TYPE_NAMED) ? m->top_level_lets[t].type->name : NULL;
                    type_ptrs[n] = m->top_level_lets[t].type;
                    n++;
                }
                if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, NULL, 0, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m, f->return_type) != 0)
                    return -1;
                if (f->return_type && f->return_type->kind != AST_TYPE_VOID && block_has_implicit_return(f->body)) {
                    fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
                    return -1;
                }
            }
        }
    }

    /* 对每个非泛型函数做体块类型检查；泛型函数体在对单态化实例检查时再做。初始作用域 = 形参 + 顶层 let。 */
    for (int i = 0; i < m->num_funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f->body) continue;
        if (f->num_generic_params > 0) continue;
        const char *names[MAX_SYMTAB];
        int type_kinds[MAX_SYMTAB];
        const char *type_names[MAX_SYMTAB];
        const struct ASTType *type_ptrs[MAX_SYMTAB];
        int n = 0;
        for (int j = 0; j < f->num_params && n < MAX_SYMTAB; j++) {
            names[n] = f->params[j].name;
            type_kinds[n] = f->params[j].type ? f->params[j].type->kind : AST_TYPE_I32;
            type_names[n] = (f->params[j].type && f->params[j].type->kind == AST_TYPE_NAMED) ? f->params[j].type->name : NULL;
            type_ptrs[n] = f->params[j].type;
            n++;
        }
        for (int t = 0; m->top_level_lets && t < m->num_top_level_lets && n < MAX_SYMTAB; t++) {
            names[n] = m->top_level_lets[t].name;
            type_kinds[n] = m->top_level_lets[t].type ? m->top_level_lets[t].type->kind : AST_TYPE_I32;
            type_names[n] = (m->top_level_lets[t].type && m->top_level_lets[t].type->kind == AST_TYPE_NAMED) ? m->top_level_lets[t].type->name : NULL;
            type_ptrs[n] = m->top_level_lets[t].type;
            n++;
        }
        if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, NULL, 0, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m, f->return_type) != 0)
            return -1;
        if (f->return_type && f->return_type->kind != AST_TYPE_VOID && block_has_implicit_return(f->body)) {
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
        int n = 0;
        for (int j = 0; j < f->num_params && n < MAX_SYMTAB; j++) {
            names[n] = f->params[j].name;
            type_ptrs[n] = get_substituted_return_type(f->params[j].type, f->generic_param_names, type_args, num_type_args);
            type_kinds[n] = type_ptrs[n] ? type_ptrs[n]->kind : AST_TYPE_I32;
            type_names[n] = (type_ptrs[n] && type_ptrs[n]->kind == AST_TYPE_NAMED) ? type_ptrs[n]->name : NULL;
            n++;
        }
        for (int t = 0; m->top_level_lets && t < m->num_top_level_lets && n < MAX_SYMTAB; t++) {
            names[n] = m->top_level_lets[t].name;
            type_kinds[n] = m->top_level_lets[t].type ? m->top_level_lets[t].type->kind : AST_TYPE_I32;
            type_names[n] = (m->top_level_lets[t].type && m->top_level_lets[t].type->kind == AST_TYPE_NAMED) ? m->top_level_lets[t].type->name : NULL;
            type_ptrs[n] = m->top_level_lets[t].type;
            n++;
        }
        const struct ASTType *mono_ret = get_substituted_return_type(f->return_type, f->generic_param_names, type_args, num_type_args);
        if (typeck_block(f->body, names, type_kinds, type_names, type_ptrs, n, NULL, 0, 0, m->struct_defs, m->num_structs, m->enum_defs, m->num_enums, m, mono_ret) != 0)
            return -1;
        if (mono_ret && mono_ret->kind != AST_TYPE_VOID && block_has_implicit_return(f->body)) {
            fprintf(stderr, "typeck error: return value must use explicit return statement (e.g. return 0;)\n");
            return -1;
        }
    }
    /* noalias 传递：对指针形参标记 is_restrict，codegen 生成 C restrict，便于优化 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        struct ASTFunc *f = (struct ASTFunc *)m->funcs[i];
        if (!f || !f->params) continue;
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type && f->params[j].type->kind == AST_TYPE_PTR)
                f->params[j].is_restrict = 1;
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            struct ASTFunc *f = (struct ASTFunc *)m->impl_blocks[k]->funcs[j];
            if (!f || !f->params) continue;
            for (int p = 0; p < f->num_params; p++)
                if (f->params[p].type && f->params[p].type->kind == AST_TYPE_PTR)
                    f->params[p].is_restrict = 1;
        }
    return 0;
}

/** double 的 64 位位模式低 32 位，供 .su typeck 填写 EXPR_FLOAT_LIT（asm 后端用）。 */
int typeck_float64_bits_lo(double d) {
    union { double d; unsigned long long u; } u;
    u.d = d;
    return (int)(u.u & 0xFFFFFFFFULL);
}

/** double 的 64 位位模式高 32 位，供 .su typeck 填写 EXPR_FLOAT_LIT（asm 后端用）。 */
int typeck_float64_bits_hi(double d) {
    union { double d; unsigned long long u; } u;
    u.d = d;
    return (int)(u.u >> 32);
}
