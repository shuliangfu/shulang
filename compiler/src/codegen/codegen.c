/**
 * codegen.c — 代码生成实现（AST → C）
 *
 * 文件职责：实现 codegen.h 声明的 codegen_module_to_c 与 codegen_library_module_to_c，将 AST 转为 C 源码供系统 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；实现 codegen.h。
 * 与其它文件的关系：依赖 include/ast.h；被 main 在 typeck 通过后调用；输出到 main 提供的临时文件流。
 * 重要约定：入口模块仅支持 main；生成 Hello World 的 printf，且 return 使用 main 体整数字面量的值（阶段 4 方案 B 扩展）；库模块仅输出注释（阶段 7.3 多文件占位）。
 */

#include "codegen/codegen.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

/** 用于生成唯一 match 临时变量名，避免嵌套 match 时冲突 */
static int codegen_match_id;

/** 当前生成所在模块（用于 CALL 时解析泛型调用的单态化实例名）；由 codegen_module_to_c 设置。 */
static const struct ASTModule *codegen_current_module;

/** 库模块 C 符号前缀（如 foo_、core_types_）；由 codegen_library_module_to_c 设置，生成时所有类型/函数名加此前缀。 */
static const char *codegen_library_prefix;
/** 库模块代码生成时指向当前模块，用于 NAMED 类型输出 "struct " 前缀（仅当前模块内定义的 struct）。 */
static const struct ASTModule *codegen_library_module;
/** 库模块 import 路径（如 std.process），用于 std.process.exit 等特殊函数体生成。 */
static const char *codegen_library_import_path;
/** 入口模块代码生成时的依赖模块与 import 路径，用于 NAMED 类型解析为 "struct prefix_Name"（依赖中的 struct）。 */
static struct ASTModule **codegen_dep_mods;
static const char **codegen_dep_paths;
static int codegen_ndep;

/** 当 codegen_library_prefix 已设置时，将 name 写成 prefix+name 到 buf；否则只写 name。用于库模块符号不冲突。 */
static void library_prefixed_name(const char *name, char *buf, size_t size) {
    if (!name) name = "";
    if (!codegen_library_prefix || !*codegen_library_prefix) {
        (void)snprintf(buf, size, "%s", name);
        return;
    }
    (void)snprintf(buf, size, "%s%s", codegen_library_prefix, name);
}

/** 泛型单态化生成时的代入上下文（由 codegen_one_mono_instance 设置）；非 NULL 时 const/let 类型用代入后的类型。 */
static char **codegen_subst_gp_names;
static struct ASTType **codegen_subst_type_args;
static int codegen_subst_n;

/** 判断 NAMED 类型名是否为顶层枚举（§7.4）；用于输出 enum 与 struct 区分。 */
static int is_enum_type(const struct ASTModule *m, const char *name) {
    if (!m || !name || !m->enum_defs) return 0;
    for (int i = 0; i < m->num_enums; i++)
        if (m->enum_defs[i] && m->enum_defs[i]->name && strcmp(m->enum_defs[i]->name, name) == 0) return 1;
    return 0;
}

/** 判断两个类型是否相等（用于查找单态化实例）；与 typeck 的 type_equal 逻辑一致。 */
static int type_equal(const struct ASTType *a, const struct ASTType *b) {
    if (!a || !b) return (a == b);
    if (a->kind != b->kind) return 0;
    if (a->kind == AST_TYPE_NAMED)
        return (a->name && b->name && strcmp(a->name, b->name) == 0);
    if (a->kind == AST_TYPE_PTR || a->kind == AST_TYPE_SLICE || a->kind == AST_TYPE_VECTOR)
        return type_equal(a->elem_type, b->elem_type);
    if (a->kind == AST_TYPE_ARRAY)
        return a->array_size == b->array_size && type_equal(a->elem_type, b->elem_type);
    return 1;
}

/** 泛型代入：若 ty 为 NAMED 且在 gp_names 中则返回对应 type_args[i]，否则返回 ty。用于单态化生成时类型替换。 */
static const struct ASTType *subst_type(const struct ASTType *ty, char **gp_names,
    struct ASTType **type_args, int num_gp) {
    if (!ty || !gp_names || !type_args || num_gp <= 0) return ty;
    if (ty->kind == AST_TYPE_NAMED && ty->name) {
        for (int i = 0; i < num_gp; i++)
            if (gp_names[i] && strcmp(ty->name, gp_names[i]) == 0) return type_args[i];
    }
    return ty;
}

/** 将类型写成 mangle 用后缀（如 i32 -> "i32"，*i32 -> "ptr_i32"）；写入 buf，最多 size 字节。 */
static void type_to_suffix(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || size == 0) return;
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        type_to_suffix(ty->elem_type, buf, size);
        size_t len = strnlen(buf, size - 1);
        if (len + 6 < size) { snprintf(buf + len, size - len, "_ptr"); }
        return;
    }
    if (ty->kind == AST_TYPE_NAMED && ty->name) { snprintf(buf, size, "%s", ty->name); return; }
    const char *s = "i32";
    switch (ty->kind) {
        case AST_TYPE_I32:   s = "i32"; break;
        case AST_TYPE_F32:   s = "f32"; break;
        case AST_TYPE_F64:   s = "f64"; break;
        case AST_TYPE_BOOL:  s = "bool"; break;
        case AST_TYPE_U8:   s = "u8"; break;
        case AST_TYPE_U32:   s = "u32"; break;
        case AST_TYPE_U64:   s = "u64"; break;
        case AST_TYPE_I64:   s = "i64"; break;
        case AST_TYPE_USIZE: s = "usize"; break;
        case AST_TYPE_ISIZE: s = "isize"; break;
        default: break;
    }
    snprintf(buf, size, "%s", s);
}

/** impl 方法 C 函数名：Trait_Type_method（阶段 7.2）；f 须为 impl 块内函数（impl_for_trait/impl_for_type 非 NULL）。 */
static const char *impl_method_c_name(const struct ASTFunc *f) {
    static char buf[256];
    if (!f || !f->impl_for_trait || !f->impl_for_type || !f->name) return f ? f->name : "";
    snprintf(buf, sizeof(buf), "%s_%s_%s", f->impl_for_trait, f->impl_for_type, f->name);
    return buf;
}

/** 单态化实例的 C 函数名：name_t1_t2（如 id_i32、id_i32_bool）。返回值使用静态缓冲区。 */
static const char *mono_instance_mangled_name(const struct ASTFunc *f,
    struct ASTType **type_args, int num_type_args) {
    static char buf[256];
    if (!f || !f->name || num_type_args <= 0 || !type_args) return f ? f->name : "";
    size_t n = (size_t)snprintf(buf, sizeof(buf), "%s", f->name);
    for (int i = 0; i < num_type_args && n < sizeof(buf) - 2; i++) {
        char suf[64];
        type_to_suffix(type_args[i], suf, sizeof(suf));
        n += (size_t)snprintf(buf + n, sizeof(buf) - n, "_%s", suf);
    }
    return buf;
}

/** 将 import 路径转为 C 符号前缀（如 "foo" -> "foo_"，"core.types" -> "core_types_"）；用于跨模块调用。 */
static void import_path_to_c_prefix(const char *import_path, char *buf, size_t size) {
    if (!buf || size == 0) return;
    size_t off = 0;
    for (const char *s = import_path; *s && off + 2 < size; s++)
        buf[off++] = (char)(*s == '.' ? '_' : *s);
    if (off + 1 < size) buf[off++] = '_';
    buf[off] = '\0';
}

#define MAX_IMPORT_DECLS 32
/** 泛型 import 调用收集：path、func、type_args、num_type_args；最多 MAX_IMPORT_DECLS 条。 */
#define MAX_GEN_IMPORT_DECLS 32

/** 前向声明：块体生成与块内 import/lib_dep 收集在文件后部定义，供 AST_EXPR_BLOCK 与 AST_EXPR_IF 使用。 */
static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out, int cast_return_to_int, const char *final_result_var);
static void collect_import_calls_from_block(const struct ASTBlock *b, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count);
static void collect_lib_dep_calls_from_block(const struct ASTBlock *b, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out);

/** 从表达式 e 递归收集跨模块 CALL：非泛型追加到 paths/funcs/n，泛型追加到 gen_*（供 emit extern）。 */
static void collect_import_calls_from_expr(const struct ASTExpr *e, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count) {
    if (!e || !paths || !funcs || !n) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_import_path && e->value.call.resolved_callee_func) {
        if (e->value.call.num_type_args <= 0 || !e->value.call.type_args) {
            if (*n >= MAX_IMPORT_DECLS) return;
            for (int i = 0; i < *n; i++)
                if (paths[i] == e->value.call.resolved_import_path && funcs[i] == e->value.call.resolved_callee_func) return;
            paths[*n] = e->value.call.resolved_import_path;
            funcs[*n] = e->value.call.resolved_callee_func;
            (*n)++;
            return;
        }
        if (gen_paths && gen_funcs && gen_type_args && gen_n && gen_count && *gen_count < MAX_GEN_IMPORT_DECLS) {
            int nt = e->value.call.num_type_args;
            int found = 0;
            for (int i = 0; i < *gen_count; i++) {
                if (gen_paths[i] != e->value.call.resolved_import_path || gen_funcs[i] != e->value.call.resolved_callee_func) continue;
                if (gen_n[i] != nt) continue;
                int eq = 1;
                for (int j = 0; j < nt && eq; j++)
                    if (!type_equal(gen_type_args[i][j], e->value.call.type_args[j])) eq = 0;
                if (eq) { found = 1; break; }
            }
            if (!found) {
                gen_paths[*gen_count] = e->value.call.resolved_import_path;
                gen_funcs[*gen_count] = e->value.call.resolved_callee_func;
                gen_type_args[*gen_count] = e->value.call.type_args;
                gen_n[*gen_count] = nt;
                (*gen_count)++;
            }
        }
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_import_calls_from_expr(e->value.call.args[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_import_calls_from_expr(e->value.binop.left, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.binop.right, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            collect_import_calls_from_expr(e->value.unary.operand, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            collect_import_calls_from_expr(e->value.if_expr.cond, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.if_expr.then_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            if (e->value.if_expr.else_expr) collect_import_calls_from_expr(e->value.if_expr.else_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_BLOCK:
            collect_import_calls_from_block(e->value.block, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ASSIGN:
            collect_import_calls_from_expr(e->value.binop.left, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.binop.right, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_MATCH:
            collect_import_calls_from_expr(e->value.match_expr.matched_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_import_calls_from_expr(e->value.match_expr.arms[i].result, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_import_calls_from_expr(e->value.field_access.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_import_calls_from_expr(e->value.struct_lit.inits[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_import_calls_from_expr(e->value.array_lit.elems[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_INDEX:
            collect_import_calls_from_expr(e->value.index.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.index.index_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_import_calls_from_expr(e->value.method_call.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_import_calls_from_expr(e->value.method_call.args[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_PANIC:
            if (e->value.unary.operand) collect_import_calls_from_expr(e->value.unary.operand, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        default: break;
    }
}
/** 从表达式 e 递归收集「库模块内对 lib_dep 的调用」：callee 为 VAR 且在 lib_dep_mods 中找到则追加 (path, func)，供生成 extern。 */
static void collect_lib_dep_calls_from_expr(const struct ASTExpr *e, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out) {
    if (!e || !paths_out || !funcs_out || !n_out || *n_out >= max_out) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.callee->kind == AST_EXPR_VAR && lib_dep_mods && lib_dep_paths && n_lib_dep > 0) {
        const char *callee_name = e->value.call.callee->value.var.name;
        if (callee_name) {
            for (int di = 0; di < n_lib_dep; di++) {
                const struct ASTModule *dm = lib_dep_mods[di];
                if (!dm || !dm->funcs) continue;
                for (int fi = 0; fi < dm->num_funcs; fi++) {
                    if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) {
                        for (int k = 0; k < *n_out; k++)
                            if (paths_out[k] == lib_dep_paths[di] && funcs_out[k] == dm->funcs[fi]) goto next_call;
                        paths_out[*n_out] = lib_dep_paths[di];
                        funcs_out[*n_out] = (struct ASTFunc *)dm->funcs[fi];
                        (*n_out)++;
                        goto next_call;
                    }
                }
            }
        }
next_call: ;
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_lib_dep_calls_from_expr(e->value.call.args[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_lib_dep_calls_from_expr(e->value.binop.left, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.binop.right, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
            collect_lib_dep_calls_from_expr(e->value.unary.operand, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            collect_lib_dep_calls_from_expr(e->value.if_expr.cond, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.if_expr.then_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            if (e->value.if_expr.else_expr) collect_lib_dep_calls_from_expr(e->value.if_expr.else_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_BLOCK:
            collect_lib_dep_calls_from_block(e->value.block, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ASSIGN:
            collect_lib_dep_calls_from_expr(e->value.binop.left, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.binop.right, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_MATCH:
            collect_lib_dep_calls_from_expr(e->value.match_expr.matched_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_lib_dep_calls_from_expr(e->value.match_expr.arms[i].result, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_lib_dep_calls_from_expr(e->value.field_access.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_lib_dep_calls_from_expr(e->value.struct_lit.inits[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_lib_dep_calls_from_expr(e->value.array_lit.elems[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_INDEX:
            collect_lib_dep_calls_from_expr(e->value.index.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.index.index_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_lib_dep_calls_from_expr(e->value.method_call.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_lib_dep_calls_from_expr(e->value.method_call.args[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_PANIC:
            if (e->value.unary.operand) collect_lib_dep_calls_from_expr(e->value.unary.operand, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        default: break;
    }
}
static void collect_lib_dep_calls_from_block(const struct ASTBlock *b, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_lib_dep_calls_from_expr(b->const_decls[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_lib_dep_calls_from_expr(b->let_decls[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_loops; i++)
        collect_lib_dep_calls_from_block(b->loops[i].body, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_lib_dep_calls_from_expr(b->for_loops[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        if (b->for_loops[i].cond) collect_lib_dep_calls_from_expr(b->for_loops[i].cond, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        if (b->for_loops[i].step) collect_lib_dep_calls_from_expr(b->for_loops[i].step, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        collect_lib_dep_calls_from_block(b->for_loops[i].body, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_lib_dep_calls_from_expr(b->labeled_stmts[i].u.return_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_lib_dep_calls_from_expr(b->expr_stmts[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    if (b->final_expr) collect_lib_dep_calls_from_expr(b->final_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
}

/** 从块 b 递归收集所有跨模块 CALL（非泛型与泛型）。 */
static void collect_import_calls_from_block(const struct ASTBlock *b, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_import_calls_from_expr(b->const_decls[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_import_calls_from_expr(b->let_decls[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_loops; i++)
        collect_import_calls_from_block(b->loops[i].body, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_import_calls_from_expr(b->for_loops[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        if (b->for_loops[i].cond) collect_import_calls_from_expr(b->for_loops[i].cond, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        if (b->for_loops[i].step) collect_import_calls_from_expr(b->for_loops[i].step, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        collect_import_calls_from_block(b->for_loops[i].body, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_import_calls_from_expr(b->labeled_stmts[i].u.return_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_import_calls_from_expr(b->expr_stmts[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    if (b->final_expr) collect_import_calls_from_expr(b->final_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
}

/** 若当前处于单态化代入上下文则返回代入后的类型，否则返回 ty；用于 const/let 等类型输出。 */
static const struct ASTType *codegen_emit_type(const struct ASTType *ty) {
    if (!ty) return ty;
    if (codegen_subst_gp_names) return subst_type(ty, codegen_subst_gp_names, codegen_subst_type_args, codegen_subst_n);
    return ty;
}

/** 前向声明：向量类型 C 名（定义在 c_type_to_buf 之后）。 */
static const char *vector_c_type_name(const struct ASTType *ty);

/**
 * 将 AST 类型写入 buf，用于递归拼指针类型（*T、**T 等）。
 * 参数：ty 类型节点；buf 输出缓冲区；size 缓冲区大小。副作用：写入 buf。
 */
static void c_type_to_buf(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || size == 0) return;
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        static char inner_buf[256];
        c_type_to_buf(ty->elem_type, inner_buf, sizeof(inner_buf));
        snprintf(buf, size, "%s *", inner_buf);
        return;
    }
    /* 数组类型 [N]T：声明时用 elem_type name[N]，此处只写元素类型（文档 §6.2） */
    if (ty->kind == AST_TYPE_ARRAY && ty->elem_type) {
        c_type_to_buf(ty->elem_type, buf, size);
        return;
    }
    /* 切片 []T：C 侧为 struct shulang_slice_<elem>；elem 为 struct 时含 "struct "，切片名须单标识符故 strip 掉 */
    if (ty->kind == AST_TYPE_SLICE && ty->elem_type) {
        static char elem_buf[128];
        c_type_to_buf(ty->elem_type, elem_buf, sizeof(elem_buf));
        const char *name_part = (strncmp(elem_buf, "struct ", 7) == 0) ? elem_buf + 7 : elem_buf;
        snprintf(buf, size, "struct shulang_slice_%s", name_part);
        return;
    }
    /* 向量类型 i32x4/u32x4/i32x8/u32x8（文档 §10）：C 侧为 typedef struct { elem v[lanes]; } *_t */
    if (ty->kind == AST_TYPE_VECTOR && ty->elem_type) {
        snprintf(buf, size, "%s", vector_c_type_name(ty));
        return;
    }
    const char *s = "int";
    switch (ty->kind) {
        case AST_TYPE_VOID:  s = "void"; break;
        case AST_TYPE_I32:   s = "int32_t"; break;
        case AST_TYPE_F32:   s = "float"; break;
        case AST_TYPE_F64:   s = "double"; break;
        case AST_TYPE_BOOL:  s = "int"; break;
        case AST_TYPE_U8:    s = "uint8_t"; break;
        case AST_TYPE_U32:   s = "uint32_t"; break;
        case AST_TYPE_U64:   s = "uint64_t"; break;
        case AST_TYPE_I64:   s = "int64_t"; break;
        case AST_TYPE_USIZE: s = "size_t"; break;
        case AST_TYPE_ISIZE: s = "ptrdiff_t"; break;
        case AST_TYPE_NAMED: {
            const char *n = ty->name ? ty->name : "int";
            /* 入口模块：若类型来自依赖模块的 enum，用 "enum prefix_Name" 与库 .c 一致 */
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->enum_defs) continue;
                    for (int j = 0; j < d->num_enums; j++)
                        if (d->enum_defs[j]->name && strcmp(d->enum_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "enum %s%s", dep_pre, n);
                            return;
                        }
                }
            }
            /* 库模块：本模块内的 enum 须用 "enum prefix_Name" 以便与库 .c 中定义一致 */
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs) {
                for (int i = 0; i < codegen_library_module->num_enums; i++)
                    if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, n) == 0) {
                        snprintf(buf, size, "enum %s%s", codegen_library_prefix, n);
                        return;
                    }
            }
            int is_struct_in_lib = 0;
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->struct_defs) {
                for (int i = 0; i < codegen_library_module->num_structs; i++)
                    if (codegen_library_module->struct_defs[i]->name && strcmp(codegen_library_module->struct_defs[i]->name, n) == 0) {
                        is_struct_in_lib = 1;
                        break;
                    }
            }
            if (is_struct_in_lib) {
                snprintf(buf, size, "struct %s%s", codegen_library_prefix, n);
                return;
            }
            /* 入口模块：若类型来自依赖模块的 struct，用 "struct prefix_Name" 与库 .c 一致 */
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->struct_defs) continue;
                    for (int j = 0; j < d->num_structs; j++)
                        if (d->struct_defs[j]->name && strcmp(d->struct_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "struct %s%s", dep_pre, n);
                            return;
                        }
                }
            }
            /* 入口模块：本模块内定义的 struct 须用 "struct Name" */
            if (!codegen_library_prefix && codegen_current_module && codegen_current_module->struct_defs) {
                for (int i = 0; i < codegen_current_module->num_structs; i++)
                    if (codegen_current_module->struct_defs[i]->name && strcmp(codegen_current_module->struct_defs[i]->name, n) == 0) {
                        snprintf(buf, size, "struct %s", n);
                        return;
                    }
            }
            if (codegen_library_prefix && *codegen_library_prefix)
                snprintf(buf, size, "%s%s", codegen_library_prefix, n);
            else
                snprintf(buf, size, "%s", n);
            return;
        }
        default: break;
    }
    snprintf(buf, size, "%s", s);
}

/**
 * 将 AST 类型映射为 C 类型字符串；用于 const/let 声明。支持裸指针 *T（文档 §5.1）。
 * 参数：ty 类型节点，不可为 NULL。返回值：C 类型名（静态缓冲区，非线程安全）。
 */
static const char *c_type_str(const struct ASTType *ty) {
    if (!ty) return "int";
    static char buf[256];
    c_type_to_buf(ty, buf, sizeof(buf));
    return buf;
}

/**
 * §3.4 内建函数映射框架：将 C 符号名映射为后端 intrinsic（如 memcpy -> __builtin_memcpy）；默认返回原名。
 * 供 core.builtin / SIMD 等生成目标平台最优指令时扩展。
 */
static const char *builtin_intrinsic_name(const char *c_name) {
    if (!c_name) return c_name;
    /* 可扩展：if (strcmp(c_name, "memcpy") == 0) return "__builtin_memcpy"; */
    return c_name;
}

/**
 * 向 out 输出单个函数形参的 C 声明；若为指针且 is_restrict 则插入 restrict（noalias 传递）。
 * override_ty 非 NULL 时用其替代 p->type（用于单态化），仍用 p->is_restrict。
 */
static void codegen_emit_param(const struct ASTParam *p, FILE *out, const struct ASTType *override_ty) {
    if (!p || !out) return;
    const struct ASTType *ty = override_ty ? override_ty : p->type;
    const char *name = p->name ? p->name : "";
    if (ty && ty->kind == AST_TYPE_PTR && p->is_restrict)
        fprintf(out, "%s restrict %s", c_type_str(ty), name);
    else
        fprintf(out, "%s %s", ty ? c_type_str(ty) : "int32_t", name);
}

/** 已输出的切片结构体 elem 类型 key，避免重复定义；最多 16 种 */
#define MAX_SLICE_STRUCTS 16
static const char *codegen_slice_emitted[MAX_SLICE_STRUCTS];
static int codegen_slice_emitted_n;

/** 向量 typedef 已输出 key 列表（如 "i32x4","u32x8"），每轮 codegen 开始时清空 */
#define MAX_VECTOR_TYPEDEFS 8
static const char *codegen_vector_emitted[MAX_VECTOR_TYPEDEFS];
static int codegen_vector_emitted_n;

/** 返回向量类型的 C 类型名（如 i32x4_t）；ty 须为 AST_TYPE_VECTOR 且 elem_type/array_size 为支持的组合。 */
static const char *vector_c_type_name(const struct ASTType *ty) {
    if (!ty || ty->kind != AST_TYPE_VECTOR || !ty->elem_type) return "int32_t";
    int lanes = ty->array_size;
    switch (ty->elem_type->kind) {
        case AST_TYPE_I32: if (lanes == 4) return "i32x4_t"; if (lanes == 8) return "i32x8_t"; if (lanes == 16) return "i32x16_t"; break;
        case AST_TYPE_U32: if (lanes == 4) return "u32x4_t"; if (lanes == 8) return "u32x8_t"; if (lanes == 16) return "u32x16_t"; break;
        default: break;
    }
    return "int32_t";
}

/** 若 ty 为支持的向量类型且尚未输出，则输出一次 typedef；无返回值。 */
static void ensure_vector_typedef(const struct ASTType *ty, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_VECTOR || !ty->elem_type || !out) return;
    const char *name = vector_c_type_name(ty);
    const char *key = name;
    for (int i = 0; i < codegen_vector_emitted_n; i++)
        if (codegen_vector_emitted[i] && strcmp(codegen_vector_emitted[i], key) == 0) return;
    if (codegen_vector_emitted_n >= MAX_VECTOR_TYPEDEFS) return;
    codegen_vector_emitted[codegen_vector_emitted_n++] = key;
    const char *elem = (ty->elem_type->kind == AST_TYPE_U32) ? "uint32_t" : "int32_t";
    int lanes = ty->array_size;
    fprintf(out, "typedef struct { %s v[%d]; } %s;\n", elem, lanes, name);
}

/** 递归扫描块内 const/let，为所有用到的向量类型输出 typedef。 */
static void ensure_block_vector_typedefs(const struct ASTBlock *b, FILE *out) {
    if (!b || !out) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_VECTOR)
            ensure_vector_typedef(b->const_decls[i].type, out);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_VECTOR)
            ensure_vector_typedef(b->let_decls[i].type, out);
    for (int i = 0; i < b->num_loops; i++)
        if (b->loops[i].body) ensure_block_vector_typedefs(b->loops[i].body, out);
    for (int i = 0; i < b->num_for_loops; i++)
        if (b->for_loops[i].body) ensure_block_vector_typedefs(b->for_loops[i].body, out);
}

/**
 * 若 ty 为切片类型，则向 out 输出一次 struct shulang_slice_<elem> { elem* data; size_t length; }（文档 §6.3）。
 * 同一 elem 类型只输出一次。elem 为 struct 时 key 含 "struct "，切片名须用单标识符，故 strip 掉 "struct " 再拼名。
 */
static void ensure_slice_struct(const struct ASTType *ty, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_SLICE || !ty->elem_type || !out) return;
    const char *key = c_type_str(ty->elem_type);
    for (int i = 0; i < codegen_slice_emitted_n; i++)
        if (codegen_slice_emitted[i] && strcmp(codegen_slice_emitted[i], key) == 0) return;
    if (codegen_slice_emitted_n >= MAX_SLICE_STRUCTS) return;
    codegen_slice_emitted[codegen_slice_emitted_n++] = key;
    const char *name_part = (strncmp(key, "struct ", 7) == 0) ? key + 7 : key;
    fprintf(out, "struct shulang_slice_%s { %s *data; size_t length; };\n", name_part, key);
}

/** 前向声明，供 codegen_init 使用 */
static int codegen_expr(const struct ASTExpr *e, FILE *out);

/** 若 e 为向量二元运算（resolved_type 为 VECTOR），则生成逐分量 op 的复合字面量并返回 0；否则返回 -1（调用方走标量分支）。 */
static int codegen_vector_binop(const struct ASTExpr *e, const char *op, FILE *out) {
    if (!e || !e->resolved_type || e->resolved_type->kind != AST_TYPE_VECTOR
        || !e->resolved_type->elem_type || e->resolved_type->array_size <= 0)
        return -1;
    int lanes = e->resolved_type->array_size;
    const char *tname = vector_c_type_name(e->resolved_type);
    fprintf(out, "(%s){ ", tname);
    for (int i = 0; i < lanes; i++) {
        if (i) fprintf(out, ", ");
        fprintf(out, "(");
        if (codegen_expr(e->value.binop.left, out) != 0) return -1;
        fprintf(out, ").v[%d] %s (", i, op);
        if (codegen_expr(e->value.binop.right, out) != 0) return -1;
        fprintf(out, ").v[%d]", i);
    }
    fprintf(out, " }");
    return 0;
}

/**
 * 输出 const/let 的初始化表达式。block 用于“切片从数组”时查数组长度；可为 NULL（则不解析数组→切片）。
 * 当类型为数组且初值为字面量 0 时输出 {0}；当类型为切片且初值为数组变量时输出 { .data = name, .length = N }。
 */
static int codegen_init(const struct ASTType *ty, const struct ASTExpr *init, FILE *out, const struct ASTBlock *block) {
    if (!init) {
        if (ty && ty->kind == AST_TYPE_VECTOR) { fprintf(out, "{0}"); return 0; }
        return -1;
    }
    if (ty && ty->kind == AST_TYPE_ARRAY && init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
        fprintf(out, "{0}");
        return 0;
    }
    if (ty && ty->kind == AST_TYPE_VECTOR && init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
        fprintf(out, "{0}");
        return 0;
    }
    /* f32/f64：整数字面量 0 生成 0.0f / 0.0；浮点字面量按 resolved_type 加 f 后缀（f32） */
    if (ty && (ty->kind == AST_TYPE_F32 || ty->kind == AST_TYPE_F64) && init) {
        if (init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
            fprintf(out, ty->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            return 0;
        }
        if (init->kind == AST_EXPR_FLOAT_LIT) {
            double v = init->value.float_val;
            if (v == 0.0)
                fprintf(out, init->resolved_type && init->resolved_type->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            else if (init->resolved_type && init->resolved_type->kind == AST_TYPE_F32)
                fprintf(out, "%gf", v);
            else
                fprintf(out, "%g", v);
            return 0;
        }
    }
    if (ty && ty->kind == AST_TYPE_VECTOR && init->kind == AST_EXPR_ARRAY_LIT) {
        struct ASTExpr **elems = init->value.array_lit.elems;
        int num = init->value.array_lit.num_elems;
        fprintf(out, "{ ");
        for (int i = 0; i < num; i++) {
            if (i) fprintf(out, ", ");
            if (codegen_expr(elems[i], out) != 0) return -1;
        }
        fprintf(out, " }");
        return 0;
    }
    if (ty && ty->kind == AST_TYPE_SLICE && init && init->kind == AST_EXPR_VAR && block) {
        const char *name = init->value.var.name;
        for (int i = 0; i < block->num_consts; i++)
            if (block->const_decls[i].name && name && strcmp(block->const_decls[i].name, name) == 0 &&
                block->const_decls[i].type && block->const_decls[i].type->kind == AST_TYPE_ARRAY) {
                fprintf(out, "{ .data = %s, .length = %d }", name ? name : "", block->const_decls[i].type->array_size);
                return 0;
            }
        for (int i = 0; i < block->num_lets; i++)
            if (block->let_decls[i].name && name && strcmp(block->let_decls[i].name, name) == 0 &&
                block->let_decls[i].type && block->let_decls[i].type->kind == AST_TYPE_ARRAY) {
                fprintf(out, "{ .data = %s, .length = %d }", name ? name : "", block->let_decls[i].type->array_size);
                return 0;
            }
    }
    return codegen_expr(init, out);
}

/** 返回 1 表示类型为整数（用于除零检查：仅整数 / % 时插入运行时检查），0 表示浮点或其它 */
static int is_integer_type(const struct ASTType *ty) {
    if (!ty) return 0;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_I64: case AST_TYPE_U64:
        case AST_TYPE_USIZE: case AST_TYPE_ISIZE: case AST_TYPE_U8: case AST_TYPE_BOOL:
            return 1;
        default: return 0;
    }
}

/**
 * 将单棵表达式生成 C 表达式写入 out（LIT 输出整数字面量，ADD/SUB 递归输出左 op 右）。
 * 参数：e 表达式根节点，不可为 NULL；out 输出流。返回值：0 成功，-1 不支持的节点类型。副作用：仅写 out。
 */
static int codegen_expr(const struct ASTExpr *e, FILE *out) {
    if (!e || !out) return -1;
    /* CTFE 最小集：typeck 已折叠的常量表达式直接输出整型值，避免运行时计算 */
    if (e->const_folded_valid) {
        fprintf(out, "%d", e->const_folded_val);
        return 0;
    }
    switch (e->kind) {
        case AST_EXPR_LIT:
            fprintf(out, "%d", e->value.int_val);
            return 0;
        case AST_EXPR_FLOAT_LIT: {
            double v = e->value.float_val;
            if (v == 0.0)
                fprintf(out, e->resolved_type && e->resolved_type->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            else if (e->resolved_type && e->resolved_type->kind == AST_TYPE_F32)
                fprintf(out, "%gf", v);
            else
                fprintf(out, "%g", v);
            return 0;
        }
        case AST_EXPR_BOOL_LIT:
            fprintf(out, "%d", e->value.int_val ? 1 : 0);
            return 0;
        case AST_EXPR_VAR:
            fprintf(out, "%s", e->value.var.name ? e->value.var.name : "");
            return 0;
        case AST_EXPR_ENUM_VARIANT: {
            /* C 中枚举值为 EnumName_VariantName；跨模块或库模块时加 prefix */
            const char *en = e->value.enum_variant.enum_name ? e->value.enum_variant.enum_name : "";
            const char *vn = e->value.enum_variant.variant_name ? e->value.enum_variant.variant_name : "";
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en[0]) {
                for (int di = 0; di < codegen_ndep; di++) {
                    const struct ASTModule *d = codegen_dep_mods[di];
                    if (!d || !d->enum_defs) continue;
                    for (int ej = 0; ej < d->num_enums; ej++)
                        if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                            char pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                            fprintf(out, "%s%s_%s", pre, en, vn);
                            return 0;
                        }
                }
            }
            if (codegen_library_prefix && *codegen_library_prefix && en[0])
                fprintf(out, "%s%s_%s", codegen_library_prefix, en, vn);
            else
                fprintf(out, "%s_%s", en, vn);
            return 0;
        }
        case AST_EXPR_ADD:
            if (codegen_vector_binop(e, "+", out) == 0) return 0;
            { const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR);
            int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " + ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0; }
        case AST_EXPR_SUB:
            if (codegen_vector_binop(e, "-", out) == 0) return 0;
            { const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR);
            int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " - ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0; }
        case AST_EXPR_MUL:
            if (codegen_vector_binop(e, "*", out) == 0) return 0;
            { const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
            int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " * ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0; }
        case AST_EXPR_DIV: {
            if (codegen_vector_binop(e, "/", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            /* 整数除零：运行时检查，除数为 0 时 panic（UB 收窄为定义行为，见 UB与未定义行为.md） */
            if (e->resolved_type && is_integer_type(e->resolved_type)) {
                int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
                int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
                fprintf(out, "(");
                if (need_r) fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                if (need_r) fprintf(out, ")");
                fprintf(out, " == 0 ? (shulang_panic_(1, 0), ");
                if (need_l) fprintf(out, "(");
                if (codegen_expr(l, out) != 0) return -1;
                if (need_l) fprintf(out, ")");
                fprintf(out, ") : (");
                if (need_l) fprintf(out, "(");
                if (codegen_expr(l, out) != 0) return -1;
                if (need_l) fprintf(out, ")");
                fprintf(out, " / ");
                if (need_r) fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                if (need_r) fprintf(out, ")");
                fprintf(out, "))");
                return 0;
            }
            int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
            int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " / ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0; }
        case AST_EXPR_MOD: {
            if (codegen_vector_binop(e, "%%", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            /* 整数取模零：运行时检查（UB 收窄为定义行为） */
            if (e->resolved_type && is_integer_type(e->resolved_type)) {
                fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                fprintf(out, " == 0 ? (shulang_panic_(1, 0), ");
                if (codegen_expr(l, out) != 0) return -1;
                fprintf(out, ") : (");
                if (codegen_expr(l, out) != 0) return -1;
                fprintf(out, " %% ");
                if (codegen_expr(r, out) != 0) return -1;
                fprintf(out, "))");
                return 0;
            }
            if (codegen_expr(l, out) != 0) return -1;
            fprintf(out, " %% ");
            if (codegen_expr(r, out) != 0) return -1;
            return 0;
        }
        case AST_EXPR_SHL:
            if (codegen_vector_binop(e, "<<", out) == 0) return 0;
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " << ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_SHR:
            if (codegen_vector_binop(e, ">>", out) == 0) return 0;
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >> ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITAND:
            if (codegen_vector_binop(e, "&", out) == 0) return 0;
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " & ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITOR:
            if (codegen_vector_binop(e, "|", out) == 0) return 0;
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " | ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITXOR:
            if (codegen_vector_binop(e, "^", out) == 0) return 0;
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " ^ ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_ASSIGN:
            /* 赋值表达式：生成 (left = right)，与 C 语义一致且可作为表达式使用（如 for 的 step） */
            fprintf(out, "(");
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " = ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_EQ:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " == ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_NE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " != ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LT:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " < ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " <= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_GT:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " > ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_GE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LOGAND:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " && ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LOGOR:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " || ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_NEG:
            fprintf(out, "(-");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_BITNOT:
            fprintf(out, "(~");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_LOGNOT:
            fprintf(out, "(!");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_IF: {
            const struct ASTExpr *then_e = e->value.if_expr.then_expr;
            const struct ASTExpr *else_e = e->value.if_expr.else_expr;
            int then_is_block = (then_e && then_e->kind == AST_EXPR_BLOCK);
            int else_is_block = (else_e && else_e->kind == AST_EXPR_BLOCK);
            /* continue/break/return 不能作为表达式求值，需当作“块”生成 { continue; } 等 */
            int then_is_control = (then_e && (then_e->kind == AST_EXPR_CONTINUE || then_e->kind == AST_EXPR_BREAK || then_e->kind == AST_EXPR_RETURN));
            int else_is_control = (else_e && (else_e->kind == AST_EXPR_CONTINUE || else_e->kind == AST_EXPR_BREAK || else_e->kind == AST_EXPR_RETURN));
            then_is_block = then_is_block || then_is_control;
            else_is_block = else_is_block || else_is_control;
            /* then/else 任一为块（含 let/return）或控制流时用 GNU C 语句表达式 + 临时变量，否则用三元运算符 */
            if (then_is_block || else_is_block) {
                const struct ASTType *tmp_ty = e->resolved_type;
                const char *tmp_ty_str = tmp_ty ? c_type_str(tmp_ty) : "int32_t";
                fprintf(out, "({ %s __tmp; if (", tmp_ty_str);
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, ") ");
                if (then_is_block) {
                    if (then_e->kind == AST_EXPR_BLOCK) {
                        fprintf(out, "{ ");
                        if (codegen_block_body(then_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                        fprintf(out, " } ");
                    } else if (then_e->kind == AST_EXPR_CONTINUE) {
                        fprintf(out, "{ continue; } ");
                    } else if (then_e->kind == AST_EXPR_BREAK) {
                        fprintf(out, "{ break; } ");
                    } else if (then_e->kind == AST_EXPR_RETURN) {
                        /* return 在语句表达式内：先赋 __tmp 再 return（AST_EXPR_RETURN 用 value.unary.operand）；无操作数时 struct 用 (type){0} */
                        fprintf(out, "{ __tmp = ");
                        if (then_e->value.unary.operand && codegen_expr(then_e->value.unary.operand, out) != 0) return -1;
                        if (!then_e->value.unary.operand) {
                            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                            else fprintf(out, "0");
                        }
                        fprintf(out, "; return __tmp; } ");
                    } else {
                        fprintf(out, "(__tmp = ");
                        if (codegen_expr(then_e, out) != 0) return -1;
                        fprintf(out, ") ");
                    }
                } else {
                    fprintf(out, "(__tmp = ");
                    if (codegen_expr(then_e, out) != 0) return -1;
                    fprintf(out, ") ");
                }
                fprintf(out, "else ");
                if (else_is_block) {
                    if (else_e->kind == AST_EXPR_BLOCK) {
                        fprintf(out, "{ ");
                        if (codegen_block_body(else_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                        fprintf(out, " } ");
                    } else if (else_e->kind == AST_EXPR_CONTINUE) {
                        fprintf(out, "{ continue; } ");
                    } else if (else_e->kind == AST_EXPR_BREAK) {
                        fprintf(out, "{ break; } ");
                    } else if (else_e->kind == AST_EXPR_RETURN) {
                        fprintf(out, "{ __tmp = ");
                        if (else_e->value.unary.operand && codegen_expr(else_e->value.unary.operand, out) != 0) return -1;
                        if (!else_e->value.unary.operand) {
                            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                            else fprintf(out, "0");
                        }
                        fprintf(out, "; return __tmp; } ");
                    } else {
                        fprintf(out, "(__tmp = ");
                        if (else_e) {
                            if (codegen_expr(else_e, out) != 0) return -1;
                        } else {
                            /* else 缺失时：struct 用 (type){0}，标量用 0 */
                            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0)
                                fprintf(out, "(%s){0}", tmp_ty_str);
                            else
                                fprintf(out, "0");
                        }
                        fprintf(out, ") ");
                    }
                } else {
                    fprintf(out, "(__tmp = ");
                    if (else_e) {
                        if (codegen_expr(else_e, out) != 0) return -1;
                    } else {
                        if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0)
                            fprintf(out, "(%s){0}", tmp_ty_str);
                        else
                            fprintf(out, "0");
                    }
                    fprintf(out, ") ");
                }
                fprintf(out, "; __tmp; })");
                return 0;
            }
            /* 若 then 分支为 panic，条件用 __builtin_expect(!!(cond),0) 包裹，使热点路径线性取指（控制流清单 §8.3） */
            int then_is_panic = (then_e && then_e->kind == AST_EXPR_PANIC);
            fprintf(out, "(");
            if (then_is_panic) {
                fprintf(out, "__builtin_expect(!!(");
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, "), 0) ? ");
            } else {
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, " ? ");
            }
            if (codegen_expr(then_e, out) != 0) return -1;
            fprintf(out, " : ");
            if (else_e) {
                if (codegen_expr(else_e, out) != 0) return -1;
            } else {
                fprintf(out, "0");
            }
            fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_TERNARY: {
            /* cond ? then : else → C 三元运算符 */
            fprintf(out, "(");
            if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
            fprintf(out, " ? ");
            if (codegen_expr(e->value.if_expr.then_expr, out) != 0) return -1;
            fprintf(out, " : ");
            if (codegen_expr(e->value.if_expr.else_expr, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_PANIC:
            /* 冷路径：通过辅助函数标记 noreturn+cold，避免污染 ICache（控制流清单 §8.3、§8.4） */
            if (e->value.unary.operand) {
                fprintf(out, "shulang_panic_(1, ");
                if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
                fprintf(out, ")");
            } else {
                fprintf(out, "shulang_panic_(0, 0)");
            }
            return 0;
        case AST_EXPR_FIELD_ACCESS:
            /* Type.Variant 枚举变体（typeck 已设 is_enum_variant）与 base.field 结构体字段（§7.4）；跨模块时用 prefix_Enum_Variant */
            if (e->value.field_access.is_enum_variant && e->value.field_access.base->kind == AST_EXPR_VAR) {
                const char *en = e->value.field_access.base->value.var.name;
                const char *vn = e->value.field_access.field_name;
                if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en) {
                    int found = 0;
                    for (int di = 0; di < codegen_ndep && !found; di++) {
                        const struct ASTModule *d = codegen_dep_mods[di];
                        if (!d || !d->enum_defs) continue;
                        for (int ej = 0; ej < d->num_enums; ej++)
                            if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                                char pre[256];
                                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                                fprintf(out, "%s%s_%s", pre, en, vn ? vn : "");
                                found = 1;
                                break;
                            }
                    }
                    if (found) return 0;
                }
                if (codegen_library_prefix && *codegen_library_prefix && en)
                    fprintf(out, "%s%s_%s", codegen_library_prefix, en, vn ? vn : "");
                else
                    fprintf(out, "%s_%s", en ? en : "", vn ? vn : "");
                return 0;
            }
            /* 库模块未做 typeck 时 is_enum_variant 可能为 0；若 base 为当前模块枚举类型名则按枚举变体输出 */
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs
                && e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
                const char *en2 = e->value.field_access.base->value.var.name;
                const char *vn2 = e->value.field_access.field_name;
                for (int i = 0; i < codegen_library_module->num_enums; i++)
                    if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, en2) == 0) {
                        fprintf(out, "%s%s_%s", codegen_library_prefix, en2, vn2 ? vn2 : "");
                        return 0;
                    }
            }
            /* 字段访问 base.field，基表达式加括号以保证 a+b.x 为 (a+b).x */
            fprintf(out, "(");
            if (codegen_expr(e->value.field_access.base, out) != 0) return -1;
            fprintf(out, ").%s", e->value.field_access.field_name ? e->value.field_access.field_name : "");
            return 0;
        case AST_EXPR_STRUCT_LIT: {
            /* 结构体字面量 TypeName { f: expr, ... } → (struct Name){ .f = expr, ... }（C99 指定初始化）；库模块或依赖模块用前缀名 */
            const char *sname = e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "";
            if (codegen_library_prefix && *codegen_library_prefix && e->value.struct_lit.struct_name) {
                char sname_buf[256];
                library_prefixed_name(e->value.struct_lit.struct_name, sname_buf, sizeof(sname_buf));
                fprintf(out, "(struct %s){ ", sname_buf);
            } else if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.struct_lit.struct_name) {
                int found = 0;
                for (int di = 0; di < codegen_ndep && !found; di++) {
                    const struct ASTModule *d = codegen_dep_mods[di];
                    if (!d || !d->struct_defs) continue;
                    for (int sj = 0; sj < d->num_structs; sj++)
                        if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, e->value.struct_lit.struct_name) == 0) {
                            char pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                            fprintf(out, "(struct %s%s){ ", pre, e->value.struct_lit.struct_name);
                            found = 1;
                            break;
                        }
                }
                if (!found) fprintf(out, "(struct %s){ ", sname);
            } else {
                fprintf(out, "(struct %s){ ", sname);
            }
            for (int i = 0; i < e->value.struct_lit.num_fields; i++) {
                if (i) fprintf(out, ", ");
                fprintf(out, ".%s = ", e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "");
                /* 结构体字段初值为数组字面量时用 { e1, e2, ... }，避免 (type[N]){ } 在 C 中作 designator 初值时的类型问题 */
                if (e->value.struct_lit.inits[i]->kind == AST_EXPR_ARRAY_LIT) {
                    const struct ASTExpr *arr = e->value.struct_lit.inits[i];
                    fprintf(out, "{ ");
                    for (int j = 0; j < arr->value.array_lit.num_elems; j++) {
                        if (j) fprintf(out, ", ");
                        if (codegen_expr(arr->value.array_lit.elems[j], out) != 0) return -1;
                    }
                    fprintf(out, " }");
                } else if (codegen_expr(e->value.struct_lit.inits[i], out) != 0)
                    return -1;
            }
            fprintf(out, " }");
            return 0;
        }
        case AST_EXPR_ARRAY_LIT: {
            /* 数组字面量 [e1, e2, ...]：实参期望 slice 时生成 (struct shulang_slice_X){ .data = (elem[]){ ... }, .length = N }，否则 (elem_ty[]){ ... }（文档 §6.2） */
            const struct ASTType *aty = e->resolved_type;
            const struct ASTType *elem_ty = (aty && (aty->kind == AST_TYPE_ARRAY || aty->kind == AST_TYPE_SLICE)) ? aty->elem_type : NULL;
            /* 未从 resolved_type 得到元素类型时（如结构体字面量字段初值未设），用任一首个有类型的元素兜底，避免误用 uint8_t */
            if (!elem_ty && e->value.array_lit.num_elems > 0) {
                for (int ei = 0; ei < e->value.array_lit.num_elems && !elem_ty; ei++)
                    if (e->value.array_lit.elems[ei]->resolved_type)
                        elem_ty = e->value.array_lit.elems[ei]->resolved_type;
            }
            int n = e->value.array_lit.num_elems;
            /* 元素类型字符串存局部缓冲，避免 c_type_str 静态缓冲被后续 c_type_str(aty) 覆盖 */
            char elem_ty_buf[64];
            snprintf(elem_ty_buf, sizeof(elem_ty_buf), "%s", elem_ty ? c_type_str(elem_ty) : "uint8_t");
            if (aty && aty->kind == AST_TYPE_SLICE && elem_ty) {
                ensure_slice_struct(aty, out);
                fprintf(out, "(%s){ .data = (%s[]){ ", c_type_str(aty), elem_ty_buf);
                for (int i = 0; i < n; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
                }
                fprintf(out, " }, .length = %d }", n);
                return 0;
            }
            if (aty && aty->kind == AST_TYPE_ARRAY && aty->array_size > 0)
                fprintf(out, "(%s[%d]){ ", elem_ty_buf, aty->array_size);
            else
                fprintf(out, "(%s[]){ ", elem_ty_buf);
            for (int i = 0; i < n; i++) {
                if (i) fprintf(out, ", ");
                if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
            }
            fprintf(out, " }");
            return 0;
        }
        case AST_EXPR_INDEX: {
            /* 数组 base[i] → (base)[i]；切片 base[i] → (base).data[i]（文档 §6.3）；越界时 panic（UB 收窄，见 UB与未定义行为.md） */
            const struct ASTExpr *base = e->value.index.base;
            const struct ASTExpr *idx = e->value.index.index_expr;
            const struct ASTType *base_ty = base->resolved_type;
            int skip_bounds_check = e->index_proven_in_bounds;
            if (e->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_SLICE) {
                if (skip_bounds_check) {
                    /* BCE：已证明在界内，只生成 (base).data[(idx)] */
                    fprintf(out, "(");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ").data[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "]");
                } else {
                    /* 切片下标：((idx)<0 || (size_t)(idx)>=(base).length ? (shulang_panic_(1,0), (base).data[0]) : (base).data[(idx)]) */
                    fprintf(out, "(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, " < 0 || (size_t)(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, ") >= (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ").length ? (shulang_panic_(1, 0), (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ").data[0]) : (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ").data[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "])");
                }
                return 0;
            }
            if (!e->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size > 0) {
                if (skip_bounds_check) {
                    /* BCE：已证明在界内，只生成 (base)[(idx)] */
                    fprintf(out, "(");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "]");
                } else {
                    /* 数组下标：((idx)<0 || (idx)>=%d ? (shulang_panic_(1,0), (base)[0]) : (base)[(idx)]) */
                    int n = base_ty->array_size;
                    fprintf(out, "(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, " < 0 || (");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, ") >= %d ? (shulang_panic_(1, 0), (", n);
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[0]) : (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "])");
                }
                return 0;
            }
            /* 无类型信息或非数组/切片时按原样生成 */
            fprintf(out, "(");
            if (codegen_expr(base, out) != 0) return -1;
            if (e->value.index.base_is_slice)
                fprintf(out, ").data[");
            else
                fprintf(out, ")[");
            if (codegen_expr(idx, out) != 0) return -1;
            fprintf(out, "]");
            return 0;
        }
        case AST_EXPR_CALL: {
            /* 跨模块调用：从 import 解析到的函数用前缀名；泛型时用 prefix + mono_instance_mangled_name（阶段 7.3） */
            if (e->value.call.resolved_import_path && e->value.call.resolved_callee_func) {
                char pre[256];
                import_path_to_c_prefix(e->value.call.resolved_import_path, pre, sizeof(pre));
                const struct ASTFunc *f = e->value.call.resolved_callee_func;
                if (e->value.call.num_type_args > 0 && e->value.call.type_args) {
                    fprintf(out, "%s%s(", pre, mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args));
                } else {
                    fprintf(out, "%s%s(", pre, f->name ? f->name : "");
                }
                for (int i = 0; i < e->value.call.num_args; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_expr(e->value.call.args[i], out) != 0) return -1;
                }
                fprintf(out, ")");
                return 0;
            }
            /* 库模块内同模块函数调用：须用前缀名，与生成的定义/前向声明一致，避免 C 侧 undeclared；extern 保持 C 名不加重前缀 */
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && e->value.call.callee->kind == AST_EXPR_VAR) {
                const char *callee_name = e->value.call.callee->value.var.name;
                const struct ASTFunc *f = NULL;
                for (int i = 0; i < codegen_library_module->num_funcs && codegen_library_module->funcs; i++) {
                    if (codegen_library_module->funcs[i]->name && callee_name
                        && strcmp(codegen_library_module->funcs[i]->name, callee_name) == 0) {
                        f = codegen_library_module->funcs[i];
                        break;
                    }
                }
                if (f && !f->is_extern) {
                    char cname[256];
                    if (e->value.call.num_type_args > 0 && e->value.call.type_args)
                        library_prefixed_name(mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args), cname, sizeof(cname));
                    else
                        library_prefixed_name(f->name ? f->name : "", cname, sizeof(cname));
                    fprintf(out, "%s(", cname);
                    for (int i = 0; i < e->value.call.num_args; i++) {
                        if (i) fprintf(out, ", ");
                        if (codegen_expr(e->value.call.args[i], out) != 0) return -1;
                    }
                    fprintf(out, ")");
                    return 0;
                }
            }
            /* 库模块内跨模块调用：callee 不在本库内时，从 lib_dep_mods 查找并用 lib_dep_paths 前缀（传递依赖） */
            if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.call.callee->kind == AST_EXPR_VAR) {
                const char *callee_name = e->value.call.callee->value.var.name;
                if (callee_name) {
                    for (int di = 0; di < codegen_ndep; di++) {
                        const struct ASTModule *dm = codegen_dep_mods[di];
                        if (!dm || !dm->funcs) continue;
                        for (int fi = 0; fi < dm->num_funcs; fi++) {
                            if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) {
                                char pre[256];
                                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                                fprintf(out, "%s%s(", pre, callee_name);
                                for (int i = 0; i < e->value.call.num_args; i++) {
                                    if (i) fprintf(out, ", ");
                                    if (codegen_expr(e->value.call.args[i], out) != 0) return -1;
                                }
                                fprintf(out, ")");
                                return 0;
                            }
                        }
                    }
                }
            }
            /* 函数调用：泛型调用 f<Type>(args) 生成单态化实例名，否则生成 callee 名 */
            if (e->value.call.num_type_args > 0 && codegen_current_module && e->value.call.callee->kind == AST_EXPR_VAR) {
                const char *callee_name = e->value.call.callee->value.var.name;
                const struct ASTFunc *func = NULL;
                for (int i = 0; i < codegen_current_module->num_funcs; i++) {
                    if (codegen_current_module->funcs[i]->name && callee_name
                        && strcmp(codegen_current_module->funcs[i]->name, callee_name) == 0) {
                        func = codegen_current_module->funcs[i];
                        break;
                    }
                }
                if (func && codegen_current_module->mono_instances) {
                    for (int k = 0; k < codegen_current_module->num_mono_instances; k++) {
                        if (codegen_current_module->mono_instances[k].template != func) continue;
                        if (codegen_current_module->mono_instances[k].num_type_args != e->value.call.num_type_args) continue;
                        int eq = 1;
                        for (int j = 0; j < e->value.call.num_type_args; j++) {
                            if (!type_equal(codegen_current_module->mono_instances[k].type_args[j], e->value.call.type_args[j])) { eq = 0; break; }
                        }
                        if (eq) {
                            fprintf(out, "%s(", builtin_intrinsic_name(mono_instance_mangled_name(func, e->value.call.type_args, e->value.call.num_type_args)));
                            for (int i = 0; i < e->value.call.num_args; i++) {
                                if (i) fprintf(out, ", ");
                                if (codegen_expr(e->value.call.args[i], out) != 0) return -1;
                            }
                            fprintf(out, ")");
                            return 0;
                        }
                    }
                }
            }
            if (codegen_expr(e->value.call.callee, out) != 0) return -1;
            fprintf(out, "(");
            for (int i = 0; i < e->value.call.num_args; i++) {
                if (i) fprintf(out, ", ");
                if (codegen_expr(e->value.call.args[i], out) != 0) return -1;
            }
            fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_METHOD_CALL: {
            struct ASTFunc *impl_func = e->value.method_call.resolved_impl_func;
            if (!impl_func) {
                fprintf(stderr, "codegen error: method call not resolved\n");
                return -1;
            }
            fprintf(out, "%s(", impl_method_c_name(impl_func));
            if (codegen_expr(e->value.method_call.base, out) != 0) return -1;
            for (int i = 0; i < e->value.method_call.num_args; i++) {
                fprintf(out, ", ");
                if (codegen_expr(e->value.method_call.args[i], out) != 0) return -1;
            }
            fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_MATCH: {
            /* 按控制流清单 §8.6：密度 > 0.7 时生成 switch，否则三元链；支持整数字面量与枚举变体（§7.4） */
            const struct ASTExpr *me = e->value.match_expr.matched_expr;
            const struct ASTMatchArm *arms = e->value.match_expr.arms;
            int num_arms = e->value.match_expr.num_arms;
            int value_min = INT_MAX, value_max = INT_MIN, lit_count = 0;
            for (int i = 0; i < num_arms; i++) {
                if (arms[i].is_wildcard) continue;
                int v = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                lit_count++;
                if (v < value_min) value_min = v;
                if (v > value_max) value_max = v;
            }
            int range = (value_max >= value_min) ? (value_max - value_min + 1) : 0;
            double density = (range > 0 && lit_count > 0) ? (double)lit_count / (double)range : 0.0;
            int use_switch = (density > 0.7 && lit_count > 0);

            if (use_switch) {
                int id = codegen_match_id++;
                fprintf(out, "({ int _su_m%d = (", id);
                if (codegen_expr(me, out) != 0) return -1;
                fprintf(out, "); int _su_r; switch (_su_m%d) { ", id);
                for (int i = 0; i < num_arms; i++) {
                    if (arms[i].is_wildcard) {
                        fprintf(out, "default: _su_r = (");
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        fprintf(out, "); break; ");
                        break;
                    }
                    {
                        int case_val = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                        fprintf(out, "case %d: _su_r = (", case_val);
                    }
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                    fprintf(out, "); break; ");
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, "default: _su_r = 0; break; ");
                fprintf(out, "} _su_r; })");
            } else {
                fprintf(out, "(");
                for (int i = 0; i < num_arms; i++) {
                    if (i) fprintf(out, " : ");
                    if (arms[i].is_wildcard) {
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        break;
                    }
                    {
                        int cmp_val = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                        fprintf(out, "(");
                        if (codegen_expr(me, out) != 0) return -1;
                        fprintf(out, ") == %d ? ", cmp_val);
                    }
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, " : 0");
                fprintf(out, ")");
            }
            return 0;
        }
        case AST_EXPR_BLOCK:
            /* 块表达式单独出现时（少见）：GNU C 语句表达式，块体后补 0 作为值 */
            fprintf(out, "({ ");
            if (codegen_block_body(e->value.block, 2, out, 0, NULL) != 0) return -1;
            fprintf(out, " 0; })");
            return 0;
        default:
            fprintf(stderr, "codegen error: unhandled expression kind %d\n", (int)e->kind);
            return -1;
    }
}

/** 阶段 8.1 块内 DCE 前向声明：收集块内被引用变量名、判断是否在 used 集合中。 */
static void collect_var_names_from_block(const struct ASTBlock *b, const char **out, int *n, int max);
static int is_var_used(const char *name, const char **used, int n_used);

/**
 * 按逆序生成执行本块所有 defer 块的 C 代码（块退出时执行）。
 * 参数：out 输出流；b 当前块（含 defer_blocks）；indent 缩进（2 或 4）。
 */
static int codegen_run_defers(FILE *out, const struct ASTBlock *b, int indent) {
    if (!b || !out || !b->defer_blocks) return 0;
    for (int i = b->num_defers - 1; i >= 0; i--) {
        if (codegen_block_body(b->defer_blocks[i], indent, out, 0, NULL) != 0) return -1;
    }
    return 0;
}

/**
 * 将块体生成到 out：const/let 声明（带 indent 空格缩进），再 labeled_stmts（label/goto/return）、run_defers，再 final_expr。
 * 若 final_expr 为 break/continue/return/panic 则生成对应语句，否则 (void)(final_expr); 或 final_result_var = (expr);（当 final_result_var 非 NULL 时）。
 * 用于 main 块或 while 体；indent 为每行前空格数（如 2 或 4）。final_result_var 用于 if-expr 的 then/else 块，将块结果赋给该变量（如 "__tmp"）。
 */
#define MAX_BLOCK_USED_VARS 128

static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out, int cast_return_to_int, const char *final_result_var) {
    if (!b || !out) return -1;
    const char *pad = (indent == 2) ? "  " : (indent == 4) ? "    " : "      ";
    /* 阶段 8.1 块内 DCE：仅输出被引用的 const/let */
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    /* 有 stmt_order 时按源码顺序输出 const/let/expr/loop/for；否则按原逻辑（const → early lets → expr/loops → late lets） */
    if (b->num_stmt_order > 0) {
        for (int i = 0; i < b->num_stmt_order; i++) {
            int k = (int)b->stmt_order[i].kind;
            int idx = b->stmt_order[i].idx;
            switch (k) {
            case 0: { /* const */
                if (idx >= b->num_consts) break;
                const char *name = b->const_decls[idx].name ? b->const_decls[idx].name : "";
                if (!is_var_used(name, used_buf, n_used)) break;
                const struct ASTType *ty = b->const_decls[idx].type;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) fprintf(out, "%sconst %s %s[%d] = ", pad, c_type_str(ety->elem_type), name, ety->array_size);
                else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%sconst %s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, b->const_decls[idx].init, out, b) != 0) return -1;
                fprintf(out, ";\n");
                break;
            }
            case 1: { /* let */
                if (idx >= b->num_lets) break;
                const char *name = b->let_decls[idx].name ? b->let_decls[idx].name : "";
                if (!is_var_used(name, used_buf, n_used)) break;
                const struct ASTType *ty = b->let_decls[idx].type;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%sconst %s * %s = ", pad, c_type_str(ety->elem_type), name);
                else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) fprintf(out, "%s%s %s[%d] = ", pad, c_type_str(ety->elem_type), name, ety->array_size);
                else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, b->let_decls[idx].init, out, b) != 0) return -1;
                fprintf(out, ";\n");
                break;
            }
            case 2: { /* expr_stmt */
                if (idx >= b->num_expr_stmts) break;
                const struct ASTExpr *st = b->expr_stmts[idx];
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) {
                    if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); }
                    else fprintf(out, "%sreturn;\n", pad);
                } else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
                break;
            }
            case 3: /* loop */
                if (idx < b->num_loops) {
                    fprintf(out, "%swhile (", pad);
                    if (codegen_expr(b->loops[idx].cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    if (codegen_block_body(b->loops[idx].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                    fprintf(out, "%s}\n", pad);
                }
                break;
            case 4: /* for */
                if (idx < b->num_for_loops) {
                    fprintf(out, "%sfor (", pad);
                    if (b->for_loops[idx].init) { if (codegen_expr(b->for_loops[idx].init, out) != 0) return -1; }
                    fprintf(out, "; ");
                    if (b->for_loops[idx].cond) { if (codegen_expr(b->for_loops[idx].cond, out) != 0) return -1; }
                    fprintf(out, "; ");
                    if (b->for_loops[idx].step) { if (codegen_expr(b->for_loops[idx].step, out) != 0) return -1; }
                    fprintf(out, ") {\n");
                    if (codegen_block_body(b->for_loops[idx].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                    fprintf(out, "%s}\n", pad);
                }
                break;
            }
        }
    } else {
        /* 无 stmt_order：原逻辑 — const → early lets → expr/loops → late lets */
        for (int i = 0; i < b->num_consts; i++) {
            const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
            if (!is_var_used(name, used_buf, n_used)) continue;
            const struct ASTType *ty = b->const_decls[i].type;
            const struct ASTType *ety = codegen_emit_type(ty);
            if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
            else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) { const char *cty = c_type_str(ety->elem_type); fprintf(out, "%sconst %s %s[%d] = ", pad, cty, name, ety->array_size); }
            else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name); }
            else { fprintf(out, "%sconst %s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name); }
            if (codegen_init(ty, b->const_decls[i].init, out, b) != 0) return -1;
            fprintf(out, ";\n");
        }
        int n_early = (b->num_early_lets > 0 && b->num_early_lets <= b->num_lets) ? b->num_early_lets : b->num_lets;
        int reorder_safe = (b->num_early_lets > 0 && b->num_early_lets < b->num_lets && b->num_loops == 0 && b->num_for_loops == 0);
        for (int i = 0; i < n_early; i++) {
            const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
            if (!is_var_used(name, used_buf, n_used)) continue;
            const struct ASTType *ty = b->let_decls[i].type;
            const struct ASTType *ety = codegen_emit_type(ty);
            if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%sconst %s * %s = ", pad, c_type_str(ety->elem_type), name);
            else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
            else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) { const char *cty = c_type_str(ety->elem_type); fprintf(out, "%s%s %s[%d] = ", pad, cty, name, ety->array_size); }
            else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
            else { fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name); }
            if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
            fprintf(out, ";\n");
        }
        if (reorder_safe) {
            for (int i = 0; i < b->num_expr_stmts; i++) {
                const struct ASTExpr *st = b->expr_stmts[i];
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); } else fprintf(out, "%sreturn;\n", pad); }
                else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
            }
            for (int i = b->num_early_lets; i < b->num_lets; i++) {
                const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
                if (!is_var_used(name, used_buf, n_used)) continue;
                const struct ASTType *ty = b->let_decls[i].type;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%sconst %s * %s = ", pad, c_type_str(ety->elem_type), name);
                else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) { const char *cty = c_type_str(ety->elem_type); fprintf(out, "%s%s %s[%d] = ", pad, cty, name, ety->array_size); }
                else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
                fprintf(out, ";\n");
            }
        } else {
            for (int i = 0; i < b->num_expr_stmts; i++) {
                const struct ASTExpr *st = b->expr_stmts[i];
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); } else fprintf(out, "%sreturn;\n", pad); }
                else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
            }
            for (int i = 0; i < b->num_loops; i++) {
                fprintf(out, "%swhile (", pad);
                if (codegen_expr(b->loops[i].cond, out) != 0) return -1;
                fprintf(out, ") {\n");
                if (codegen_block_body(b->loops[i].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                fprintf(out, "%s}\n", pad);
            }
            for (int i = 0; i < b->num_for_loops; i++) {
                fprintf(out, "%sfor (", pad);
                if (b->for_loops[i].init) { if (codegen_expr(b->for_loops[i].init, out) != 0) return -1; }
                fprintf(out, "; ");
                if (b->for_loops[i].cond) { if (codegen_expr(b->for_loops[i].cond, out) != 0) return -1; }
                fprintf(out, "; ");
                if (b->for_loops[i].step) { if (codegen_expr(b->for_loops[i].step, out) != 0) return -1; }
                fprintf(out, ") {\n");
                if (codegen_block_body(b->for_loops[i].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                fprintf(out, "%s}\n", pad);
            }
            if (b->num_early_lets > 0 && b->num_early_lets < b->num_lets) {
                for (int i = b->num_early_lets; i < b->num_lets; i++) {
                    const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
                    if (!is_var_used(name, used_buf, n_used)) continue;
                    const struct ASTType *ty = b->let_decls[i].type;
                    const struct ASTType *ety = codegen_emit_type(ty);
                    if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%sconst %s * %s = ", pad, c_type_str(ety->elem_type), name);
                    else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                    else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) { const char *cty = c_type_str(ety->elem_type); fprintf(out, "%s%s %s[%d] = ", pad, cty, name, ety->array_size); }
                    else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                    else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                    if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
                    fprintf(out, ";\n");
                }
            }
        }
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label)
            fprintf(out, "%s%s:\n", pad, b->labeled_stmts[i].label);
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
            if (codegen_run_defers(out, b, indent) != 0) return -1;
            fprintf(out, "%sgoto %s;\n", pad, b->labeled_stmts[i].u.goto_target);
        } else {
            if (codegen_run_defers(out, b, indent) != 0) return -1;
            const struct ASTExpr *re = b->labeled_stmts[i].u.return_expr;
            if (!re) {
                fprintf(out, "%sreturn;\n", pad);
                continue;
            }
            int if_panic = (re->kind == AST_EXPR_IF && re->value.if_expr.then_expr
                && re->value.if_expr.then_expr->kind == AST_EXPR_PANIC && re->value.if_expr.else_expr);
            if (if_panic) {
                fprintf(out, "%sif (", pad);
                if (codegen_expr(re->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, ") {\n");
                fprintf(out, "%s  ", pad);
                if (codegen_expr(re->value.if_expr.then_expr, out) != 0) return -1;
                fprintf(out, ";\n%s}\n", pad);
                if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                if (codegen_expr(re->value.if_expr.else_expr, out) != 0) return -1;
                fprintf(out, cast_return_to_int ? ");\n" : ";\n");
            } else if (re->kind == AST_EXPR_PANIC) {
                fprintf(out, "%s", pad);
                if (codegen_expr(re, out) != 0) return -1;
                fprintf(out, ";\n%sreturn 0;\n", pad);
            } else {
                if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                if (codegen_expr(re, out) != 0) return -1;
                fprintf(out, cast_return_to_int ? ");\n" : ";\n");
            }
        }
    }
    if (codegen_run_defers(out, b, indent) != 0) return -1;
    if (!b->final_expr) return 0;  /* 块以 return/goto 结尾，无需 final_expr */
    if (b->final_expr->kind == AST_EXPR_BREAK) {
        fprintf(out, "%sbreak;\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_CONTINUE) {
        fprintf(out, "%scontinue;\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *op = b->final_expr->value.unary.operand;
        if (!op) {
            fprintf(out, "%sreturn;\n", pad);
            return 0;
        }
        if (op->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s", pad);
            if (codegen_expr(op, out) != 0) return -1;
            fprintf(out, ";\n%sreturn 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (codegen_expr(op, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
        && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
        && b->final_expr->value.if_expr.else_expr
        && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *iff = b->final_expr;
        const struct ASTExpr *then_ret = iff->value.if_expr.then_expr->value.unary.operand;
        const struct ASTExpr *else_ret = iff->value.if_expr.else_expr->value.unary.operand;
        fprintf(out, "%sif (", pad);
        if (codegen_expr(iff->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (then_ret && then_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            fprintf(out, "%s  return ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n");
        }
        fprintf(out, "%s} else {\n", pad);
        if (else_ret && else_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            fprintf(out, "%s  return ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n");
        }
        fprintf(out, "%s}\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "%s", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        return 0;
    }
    if (final_result_var && *final_result_var) {
        fprintf(out, "%s%s = ", pad, final_result_var);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
    } else {
        fprintf(out, "%s(void)(", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ");\n");
    }
    return 0;
}

/**
 * 统计块内「会执行 return」的出口个数（用于决定是否用 goto cleanup 减少 defer 重复展开）。
 * 仅计 return 类出口，不含 goto。
 */
static int count_return_exits(const struct ASTBlock *b) {
    if (!b) return 0;
    int n = 0;
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN) {
            const struct ASTExpr *e = b->labeled_stmts[i].u.return_expr;
            if (e && e->kind == AST_EXPR_IF && e->value.if_expr.then_expr
                && e->value.if_expr.then_expr->kind == AST_EXPR_PANIC && e->value.if_expr.else_expr)
                n += 2; /* then panic + else return */
            else
                n += 1;
        }
    }
    if (b->final_expr) {
        if (b->final_expr->kind == AST_EXPR_RETURN) n += 1;
        else if (b->final_expr->kind == AST_EXPR_PANIC) n += 1;
        else if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
            && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
            && b->final_expr->value.if_expr.else_expr
            && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN)
            n += 2;
    }
    return n;
}

/**
 * 生成单个函数体（const/let、while/for、labeled、final_expr return/panic）。
 * 用于多函数时每个函数的函数体；indent 固定为 2（两空格）。
 * f 非 NULL 且为 main 且返回 i64 时，对 return 表达式包 (int) 以适配 C 的 int main()。
 * 当存在多个 return 出口且至少一个 defer 时，使用单一 shulang_cleanup 标签，避免每出口重复展开 defer。
 */
static int codegen_func_body(const struct ASTBlock *b, const struct ASTModule *m, FILE *out, const struct ASTFunc *f) {
    if (!b || !m || !out) return -1;
    int cast_return_to_int = (f && f->name && strcmp(f->name, "main") == 0
        && f->return_type && f->return_type->kind == AST_TYPE_I64);
    const char *pad = "  ";
    int is_void = (f && f->return_type && f->return_type->kind == AST_TYPE_VOID);
    int use_cleanup = (!is_void && b->num_defers > 0 && count_return_exits(b) >= 2);
    const char *ret_ctype = (f && f->return_type) ? c_type_str(f->return_type) : "int32_t";
    if (cast_return_to_int) ret_ctype = "int";
    /* 阶段 8.1 块内 DCE：仅输出被引用的 const/let */
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    for (int i = 0; i < b->num_consts; i++) {
        const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
        if (!is_var_used(name, used_buf, n_used)) continue;
        const struct ASTType *ty = b->const_decls[i].type;
        const struct ASTType *ety = codegen_emit_type(ty);
        if (ety && ety->kind == AST_TYPE_NAMED && ety->name) {
            if (is_enum_type(m, ety->name))
                fprintf(out, "%sconst enum %s %s = ", pad, ety->name, name);
            else
                fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
        }
        else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type)
            fprintf(out, "%sconst %s %s[%d] = ", pad, c_type_str(ety->elem_type), name, ety->array_size);
        else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) {
            ensure_slice_struct(ety, out);
            fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
        } else {
            const char *cty = ety ? c_type_str(ety) : "int32_t";
            fprintf(out, "%sconst %s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, b->const_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_lets; i++) {
        const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
        if (!is_var_used(name, used_buf, n_used)) continue;
        const struct ASTType *ty = b->let_decls[i].type;
        const struct ASTType *ety = codegen_emit_type(ty);
        if (ety && ety->kind == AST_TYPE_NAMED && ety->name) {
            if (is_enum_type(m, ety->name))
                fprintf(out, "%senum %s %s = ", pad, ety->name, name);
            else
                fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
        }
        else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type)
            fprintf(out, "%s%s %s[%d] = ", pad, c_type_str(ety->elem_type), name, ety->array_size);
        else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) {
            ensure_slice_struct(ety, out);
            fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
        } else {
            const char *cty = ety ? c_type_str(ety) : "int32_t";
            fprintf(out, "%s%s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    if (use_cleanup) {
        fprintf(out, "%sint shulang_exit_kind = 0;\n", pad);
        fprintf(out, "%s%s shulang_ret_val = 0;\n", pad, ret_ctype);
    }
    for (int i = 0; i < b->num_loops; i++) {
        fprintf(out, "%swhile (", pad);
        if (codegen_expr(b->loops[i].cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (codegen_block_body(b->loops[i].body, 4, out, cast_return_to_int, NULL) != 0) return -1;
        fprintf(out, "%s}\n", pad);
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        fprintf(out, "%sfor (", pad);
        if (b->for_loops[i].init) {
            if (codegen_expr(b->for_loops[i].init, out) != 0) return -1;
        }
        fprintf(out, "; ");
        if (b->for_loops[i].cond) {
            if (codegen_expr(b->for_loops[i].cond, out) != 0) return -1;
        } else {
            fprintf(out, "1");
        }
        fprintf(out, "; ");
        if (b->for_loops[i].step) {
            if (codegen_expr(b->for_loops[i].step, out) != 0) return -1;
        }
        fprintf(out, ") {\n");
        if (codegen_block_body(b->for_loops[i].body, 4, out, cast_return_to_int, NULL) != 0) return -1;
        fprintf(out, "%s}\n", pad);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label)
            fprintf(out, "%s%s:\n", pad, b->labeled_stmts[i].label);
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
            if (codegen_run_defers(out, b, 2) != 0) return -1;
            fprintf(out, "%sgoto %s;\n", pad, b->labeled_stmts[i].u.goto_target);
        } else {
            const struct ASTExpr *ret_e = b->labeled_stmts[i].u.return_expr;
            if (!ret_e) {
                if (use_cleanup) {
                    fprintf(out, "%sshulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
                } else {
                    if (codegen_run_defers(out, b, 2) != 0) return -1;
                    fprintf(out, "%sreturn;\n", pad);
                }
                continue;
            }
            int ret_if_panic = (ret_e->kind == AST_EXPR_IF && ret_e->value.if_expr.then_expr
                && ret_e->value.if_expr.then_expr->kind == AST_EXPR_PANIC && ret_e->value.if_expr.else_expr);
            if (use_cleanup) {
                if (ret_if_panic) {
                    fprintf(out, "%sif (", pad);
                    if (codegen_expr(ret_e->value.if_expr.cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    fprintf(out, "%s  ", pad);
                    if (codegen_expr(ret_e->value.if_expr.then_expr, out) != 0) return -1;
                    fprintf(out, ";\n%sshulang_ret_val = 0; shulang_exit_kind = 1; goto shulang_cleanup;\n%s} else {\n", pad, pad);
                    if (cast_return_to_int) fprintf(out, "%s  shulang_ret_val = (int)(", pad); else fprintf(out, "%s  shulang_ret_val = ", pad);
                    if (codegen_expr(ret_e->value.if_expr.else_expr, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                    fprintf(out, "%s  shulang_exit_kind = 1; goto shulang_cleanup;\n%s}\n", pad, pad);
                } else if (ret_e && ret_e->kind == AST_EXPR_PANIC) {
                    fprintf(out, "%s", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, ";\n%sshulang_ret_val = 0; shulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
                } else {
                    if (cast_return_to_int) fprintf(out, "%sshulang_ret_val = (int)(", pad); else fprintf(out, "%sshulang_ret_val = ", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                    fprintf(out, "%sshulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
                }
            } else {
                if (codegen_run_defers(out, b, 2) != 0) return -1;
                if (ret_if_panic) {
                    fprintf(out, "%sif (", pad);
                    if (codegen_expr(ret_e->value.if_expr.cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    fprintf(out, "%s  ", pad);
                    if (codegen_expr(ret_e->value.if_expr.then_expr, out) != 0) return -1;
                    fprintf(out, ";\n%s}\n", pad);
                    if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                    if (codegen_expr(ret_e->value.if_expr.else_expr, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                } else if (ret_e && ret_e->kind == AST_EXPR_PANIC) {
                    fprintf(out, "%s", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, ";\n%sreturn 0;\n", pad);
                } else {
                    if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                }
            }
        }
    }
    /* 表达式语句 (expr;)：continue/break/return 须直接生成语句，不能包在 (void)(...) 中 */
    for (int i = 0; i < b->num_expr_stmts; i++) {
        const struct ASTExpr *st = b->expr_stmts[i];
        if (st->kind == AST_EXPR_CONTINUE) {
            fprintf(out, "%scontinue;\n", pad);
        } else if (st->kind == AST_EXPR_BREAK) {
            fprintf(out, "%sbreak;\n", pad);
        } else if (st->kind == AST_EXPR_RETURN) {
            if (st->value.unary.operand) {
                fprintf(out, "%sreturn ", pad);
                if (codegen_expr(st->value.unary.operand, out) != 0) return -1;
                fprintf(out, ";\n");
            } else {
                fprintf(out, "%sreturn;\n", pad);
            }
        } else {
            fprintf(out, "%s(void)(", pad);
            if (codegen_expr(st, out) != 0) return -1;
            fprintf(out, ");\n");
        }
    }
    if (use_cleanup)
        fprintf(out, "%sgoto shulang_cleanup;\n", pad);
    else if (codegen_run_defers(out, b, 2) != 0)
        return -1;
    if (use_cleanup) {
        fprintf(out, "%sshulang_cleanup:\n", pad);
        if (codegen_run_defers(out, b, 2) != 0) return -1;
        fprintf(out, "%sif (shulang_exit_kind) return shulang_ret_val;\n", pad);
    }
    if (!b->final_expr) return 0;
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "%s", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        fprintf(out, "%sreturn 0;\n", pad);
    } else if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
        && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
        && b->final_expr->value.if_expr.else_expr
        && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *iff = b->final_expr;
        const struct ASTExpr *then_ret = iff->value.if_expr.then_expr->value.unary.operand;
        const struct ASTExpr *else_ret = iff->value.if_expr.else_expr->value.unary.operand;
        fprintf(out, "%sif (", pad);
        if (codegen_expr(iff->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (then_ret && then_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%s  return (int)(", pad); else fprintf(out, "%s  return ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        fprintf(out, "%s} else {\n", pad);
        if (else_ret && else_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%s  return (int)(", pad); else fprintf(out, "%s  return ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        fprintf(out, "%s}\n", pad);
    } else {
        if (b->final_expr->kind == AST_EXPR_RETURN && !b->final_expr->value.unary.operand) {
            fprintf(out, "%sreturn;\n", pad);
            return 0;
        }
        const struct ASTExpr *ret_op = (b->final_expr->kind == AST_EXPR_RETURN) ? b->final_expr->value.unary.operand : b->final_expr;
        int is_return_if_panic = (ret_op && ret_op->kind == AST_EXPR_IF && ret_op->value.if_expr.then_expr
            && ret_op->value.if_expr.then_expr->kind == AST_EXPR_PANIC && ret_op->value.if_expr.else_expr);
        if (is_return_if_panic) {
            fprintf(out, "%sif (", pad);
            if (codegen_expr(ret_op->value.if_expr.cond, out) != 0) return -1;
            fprintf(out, ") {\n");
            fprintf(out, "%s  ", pad);
            if (codegen_expr(ret_op->value.if_expr.then_expr, out) != 0) return -1;
            fprintf(out, ";\n%s}\n", pad);
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (codegen_expr(ret_op->value.if_expr.else_expr, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        } else {
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (b->final_expr->kind == AST_EXPR_RETURN) {
                if (codegen_expr(ret_op, out) != 0) return -1;
            } else {
                if (codegen_expr(b->final_expr, out) != 0) return -1;
            }
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
    }
    return 0;
}

/**
 * 生成单个 C 函数定义：return_type name(params) { body }。
 * 多函数时对 mod->funcs 中每个函数调用；main 放在最后以便其它函数可被 main 调用。
 */
static int codegen_one_func(const struct ASTFunc *f, const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out) return -1;
    /* 泛型函数由单态化实例生成，不在此直接输出（阶段 7.1） */
    if (f->num_generic_params > 0) return 0;
    char fname[256];
    library_prefixed_name(f->name, fname, sizeof(fname));
    /* C 要求 main 返回 int；若 .su 中 main 返回 i64 则在函数体内对 return 包 (int) */
    const char *cret = (f->name && strcmp(f->name, "main") == 0) ? "int" : c_type_str(f->return_type);
    /* 小函数内联提示（§3.4）：仅入口模块内非 main、非 extern 函数加 static inline（库函数需导出符号，不加 static） */
    if (!codegen_library_prefix && f->name && strcmp(f->name, "main") != 0 && !f->is_extern)
        fprintf(out, "static inline ");
    fprintf(out, "%s %s(", cret, fname);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        codegen_emit_param(&f->params[i], out, NULL);
    }
    fprintf(out, ") {\n");
    if (f->name && strcmp(f->name, "main") == 0)
        fprintf(out, "  printf(\"Hello World\\n\");\n");
    /* std.process.exit(code)：生成对 C exit() 的调用（noreturn） */
    if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.process") == 0
        && f->name && strcmp(f->name, "exit") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I32) {
        const char *pname = f->params[0].name ? f->params[0].name : "code";
        fprintf(out, "  exit(%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_i32") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I32) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%d\\n\", (int)%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_u32") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_U32) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%u\\n\", (unsigned int)%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_i64") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I64) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%lld\\n\", (long long)%s);\n  return 0;\n", pname);
    } else if (codegen_func_body(f->body, m, out, f) != 0)
        return -1;
    fprintf(out, "}\n");
    return 0;
}

/**
 * 为 impl 块内单条方法生成 C 函数（使用 mangle 名 Trait_Type_method）；阶段 7.2。
 */
static int codegen_one_impl_func(const struct ASTFunc *f, const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out || !f->impl_for_trait || !f->impl_for_type) return -1;
    char cname_buf[256];
    library_prefixed_name(impl_method_c_name(f), cname_buf, sizeof(cname_buf));
    /* 库模块 impl 方法不加 static 以保持可链接；入口模块可考虑在单文件时加 inline，此处从简 */
    fprintf(out, "%s %s(", c_type_str(f->return_type), cname_buf);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        codegen_emit_param(&f->params[i], out, NULL);
    }
    fprintf(out, ") {\n");
    if (codegen_func_body(f->body, m, out, NULL) != 0) return -1;
    fprintf(out, "}\n");
    return 0;
}

/**
 * 为单个泛型单态化实例生成 C 函数：代入类型后的签名 + 模板体（体中类型按代入上下文输出）。
 */
static int codegen_one_mono_instance(const struct ASTFunc *f, struct ASTType **type_args, int num_type_args,
    const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out || !type_args || num_type_args <= 0 || !f->generic_param_names) return -1;
    const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, type_args, num_type_args);
    char mangled_buf[256];
    library_prefixed_name(mono_instance_mangled_name(f, type_args, num_type_args), mangled_buf, sizeof(mangled_buf));
    fprintf(out, "%s %s(", c_type_str(ret_ty), mangled_buf);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        const struct ASTType *pty = subst_type(f->params[i].type, f->generic_param_names, type_args, num_type_args);
        codegen_emit_param(&f->params[i], out, pty);
    }
    fprintf(out, ") {\n");
    codegen_subst_gp_names = f->generic_param_names;
    codegen_subst_type_args = type_args;
    codegen_subst_n = num_type_args;
    int r = codegen_func_body(f->body, m, out, NULL);
    codegen_subst_gp_names = NULL;
    codegen_subst_type_args = NULL;
    codegen_subst_n = 0;
    if (r != 0) return -1;
    fprintf(out, "}\n");
    return 0;
}

/** 阶段 8.1 DCE：在模块 m 的 mono_instances 中查找 (template, type_args) 对应的实例下标，未找到返回 -1。 */
static int find_mono_index(const struct ASTModule *m, const struct ASTFunc *template,
    struct ASTType **type_args, int n) {
    if (!m || !m->mono_instances || !template || !type_args) return -1;
    for (int k = 0; k < m->num_mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (inst->template != template || inst->num_type_args != n) continue;
        int eq = 1;
        for (int j = 0; j < n && eq; j++)
            if (!type_equal(inst->type_args[j], type_args[j])) eq = 0;
        if (eq) return k;
    }
    return -1;
}

/** 返回 func 所在模块在 (entry, dep_mods[0..ndep-1]) 中的下标：0=entry，1+i=dep_mods[i]，未找到返回 -1。 */
static int module_index(const struct ASTModule *entry, struct ASTModule **dep_mods, int ndep, const struct ASTModule *mod) {
    if (mod == entry) return 0;
    for (int i = 0; i < ndep; i++)
        if (dep_mods[i] == mod) return 1 + i;
    return -1;
}

/** 判断 func 是否属于模块 m（顶层函数或 impl 方法）。 */
static int func_belongs_to_module(const struct ASTModule *m, const struct ASTFunc *func) {
    if (!m || !func) return 0;
    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] == func) return 1;
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j] == func) return 1;
    return 0;
}

/** 阶段 8.1 DCE：从表达式递归收集被调函数与单态化，加入 worklist 并标记 used_mono。 */
static void dce_collect_from_expr(const struct ASTExpr *e, struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **worklist, int *n_wl, int max_wl, int *in_wl,
    int used_mono[][64], int used_mono_rows) {
    if (!e) return;
    /* return expr 在 parser 中为 AST_EXPR_RETURN(operand)，须先递归 operand 才能看到其中的 CALL 并收集 callee */
    if (e->kind == AST_EXPR_RETURN && e->value.unary.operand) {
        dce_collect_from_expr(e->value.unary.operand, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        return;
    }
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func) {
        const struct ASTFunc *callee = e->value.call.resolved_callee_func;
        if (e->value.call.num_type_args > 0 && e->value.call.type_args) {
            const struct ASTModule *owner = NULL;
            if (func_belongs_to_module(entry, callee)) owner = entry;
            else
                for (int i = 0; i < ndep && !owner; i++)
                    if (func_belongs_to_module(dep_mods[i], callee)) owner = dep_mods[i];
            if (owner) {
                int mi = module_index(entry, dep_mods, ndep, owner);
                int k = find_mono_index(owner, callee, (struct ASTType **)e->value.call.type_args, e->value.call.num_type_args);
                if (mi >= 0 && mi < used_mono_rows && k >= 0 && k < 64)
                    used_mono[mi][k] = 1;
            }
        }
        for (int i = 0; i < *n_wl; i++)
            if (worklist[i] == (struct ASTFunc *)callee) goto skip_add;
        if (*n_wl < max_wl) {
            worklist[*n_wl++] = (struct ASTFunc *)callee;
            if (in_wl) in_wl[(size_t)(const char *)callee % (size_t)max_wl] = 1;
        }
    skip_add: ;
    }
    if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func) {
        const struct ASTFunc *callee = e->value.method_call.resolved_impl_func;
        for (int i = 0; i < *n_wl; i++)
            if (worklist[i] == (struct ASTFunc *)callee) goto skip_impl;
        if (*n_wl < max_wl) worklist[*n_wl++] = (struct ASTFunc *)callee;
    skip_impl: ;
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                dce_collect_from_expr(e->value.call.args[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_METHOD_CALL:
            dce_collect_from_expr(e->value.method_call.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                dce_collect_from_expr(e->value.method_call.args[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
            dce_collect_from_expr(e->value.binop.left, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.binop.right, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_PANIC:
            dce_collect_from_expr(e->value.unary.operand, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            dce_collect_from_expr(e->value.if_expr.cond, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.if_expr.then_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            if (e->value.if_expr.else_expr) dce_collect_from_expr(e->value.if_expr.else_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_MATCH:
            dce_collect_from_expr(e->value.match_expr.matched_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                dce_collect_from_expr(e->value.match_expr.arms[i].result, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_FIELD_ACCESS:
            dce_collect_from_expr(e->value.field_access.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                dce_collect_from_expr(e->value.struct_lit.inits[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                dce_collect_from_expr(e->value.array_lit.elems[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_INDEX:
            dce_collect_from_expr(e->value.index.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.index.index_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        default: break;
    }
}

/** 阶段 8.1 DCE 兜底：判断表达式 e 中是否出现对 func 的调用（CALL/METHOD_CALL），含 AST_EXPR_RETURN 内层。用于 ndep==0 时 used 未收到同模块 callee 仍保留被 main 引用的函数。 */
static int expr_references_func(const struct ASTExpr *e, const struct ASTFunc *func) {
    if (!e || !func) return 0;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func == func) return 1;
    if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func == func) return 1;
    if (e->kind == AST_EXPR_RETURN && e->value.unary.operand && expr_references_func(e->value.unary.operand, func)) return 1;
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                if (expr_references_func(e->value.call.args[i], func)) return 1;
            break;
        case AST_EXPR_METHOD_CALL:
            if (expr_references_func(e->value.method_call.base, func)) return 1;
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (expr_references_func(e->value.method_call.args[i], func)) return 1;
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            if (expr_references_func(e->value.binop.left, func) || expr_references_func(e->value.binop.right, func)) return 1;
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC:
            if (expr_references_func(e->value.unary.operand, func)) return 1;
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            if (expr_references_func(e->value.if_expr.cond, func) || expr_references_func(e->value.if_expr.then_expr, func)) return 1;
            if (e->value.if_expr.else_expr && expr_references_func(e->value.if_expr.else_expr, func)) return 1;
            break;
        case AST_EXPR_MATCH:
            if (expr_references_func(e->value.match_expr.matched_expr, func)) return 1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (expr_references_func(e->value.match_expr.arms[i].result, func)) return 1;
            break;
        case AST_EXPR_FIELD_ACCESS:
            if (expr_references_func(e->value.field_access.base, func)) return 1;
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (expr_references_func(e->value.struct_lit.inits[i], func)) return 1;
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (expr_references_func(e->value.array_lit.elems[i], func)) return 1;
            break;
        case AST_EXPR_INDEX:
            if (expr_references_func(e->value.index.base, func) || expr_references_func(e->value.index.index_expr, func)) return 1;
            break;
        default: break;
    }
    return 0;
}

/** 阶段 8.1 块内 DCE：将 name 加入 used 集合（去重），out 为指针数组，n 为当前个数，max 为上限。 */
static void add_used_var_name(const char *name, const char **out, int *n, int max) {
    if (!name || !out || !n || *n >= max) return;
    for (int i = 0; i < *n; i++) if (out[i] && strcmp(out[i], name) == 0) return;
    out[(*n)++] = name;
}

/** 从表达式中收集所有作为 VAR 出现的变量名到 out（用于块内 const/let DCE）。 */
static void collect_var_names_from_expr(const struct ASTExpr *e, const char **out, int *n, int max) {
    if (!e || *n >= max) return;
    if (e->kind == AST_EXPR_VAR && e->value.var.name)
        add_used_var_name(e->value.var.name, out, n, max);
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            collect_var_names_from_expr(e->value.binop.left, out, n, max);
            collect_var_names_from_expr(e->value.binop.right, out, n, max);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC: case AST_EXPR_RETURN:
            if (e->value.unary.operand) collect_var_names_from_expr(e->value.unary.operand, out, n, max);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_var_names_from_expr(e->value.if_expr.cond, out, n, max);
            if (e->value.if_expr.then_expr) collect_var_names_from_expr(e->value.if_expr.then_expr, out, n, max);
            if (e->value.if_expr.else_expr) collect_var_names_from_expr(e->value.if_expr.else_expr, out, n, max);
            break;
        case AST_EXPR_BLOCK:
            if (e->value.block) collect_var_names_from_block(e->value.block, out, n, max);
            break;
        case AST_EXPR_MATCH:
            collect_var_names_from_expr(e->value.match_expr.matched_expr, out, n, max);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_var_names_from_expr(e->value.match_expr.arms[i].result, out, n, max);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_var_names_from_expr(e->value.field_access.base, out, n, max);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_var_names_from_expr(e->value.struct_lit.inits[i], out, n, max);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_var_names_from_expr(e->value.array_lit.elems[i], out, n, max);
            break;
        case AST_EXPR_INDEX:
            collect_var_names_from_expr(e->value.index.base, out, n, max);
            collect_var_names_from_expr(e->value.index.index_expr, out, n, max);
            break;
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_var_names_from_expr(e->value.call.args[i], out, n, max);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_var_names_from_expr(e->value.method_call.base, out, n, max);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_var_names_from_expr(e->value.method_call.args[i], out, n, max);
            break;
        default: break;
    }
}

/** 从块中收集所有被引用的变量名（final_expr、const/let 的 init、循环、defer、labeled）；用于仅输出被使用的 const/let。 */
static void collect_var_names_from_block(const struct ASTBlock *b, const char **out, int *n, int max) {
    if (!b || *n >= max) return;
    for (int i = 0; i < b->num_consts; i++) {
        if (b->const_decls[i].init) collect_var_names_from_expr(b->const_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].init) collect_var_names_from_expr(b->let_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_loops; i++)
        collect_var_names_from_block(b->loops[i].body, out, n, max);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_var_names_from_expr(b->for_loops[i].init, out, n, max);
        if (b->for_loops[i].cond) collect_var_names_from_expr(b->for_loops[i].cond, out, n, max);
        if (b->for_loops[i].step) collect_var_names_from_expr(b->for_loops[i].step, out, n, max);
        collect_var_names_from_block(b->for_loops[i].body, out, n, max);
    }
    for (int i = 0; i < b->num_defers; i++)
        collect_var_names_from_block(b->defer_blocks[i], out, n, max);
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_var_names_from_expr(b->labeled_stmts[i].u.return_expr, out, n, max);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_var_names_from_expr(b->expr_stmts[i], out, n, max);
    if (b->final_expr) collect_var_names_from_expr(b->final_expr, out, n, max);
}

/** 判断 name 是否在 used 集合中（用于块内 const/let DCE）。 */
static int is_var_used(const char *name, const char **used, int n_used) {
    if (!name || !used) return 1;
    for (int i = 0; i < n_used; i++) if (used[i] && strcmp(used[i], name) == 0) return 1;
    return 0;
}

/** 判断块 b 中是否出现对 func 的调用（遍历 const/let/循环/labeled/final_expr）。 */
static int block_references_func(const struct ASTBlock *b, const struct ASTFunc *func) {
    if (!b || !func) return 0;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init && expr_references_func(b->const_decls[i].init, func)) return 1;
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && expr_references_func(b->let_decls[i].init, func)) return 1;
    for (int i = 0; i < b->num_loops; i++)
        if (block_references_func(b->loops[i].body, func)) return 1;
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init && expr_references_func(b->for_loops[i].init, func)) return 1;
        if (b->for_loops[i].cond && expr_references_func(b->for_loops[i].cond, func)) return 1;
        if (b->for_loops[i].step && expr_references_func(b->for_loops[i].step, func)) return 1;
        if (block_references_func(b->for_loops[i].body, func)) return 1;
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr
            && expr_references_func(b->labeled_stmts[i].u.return_expr, func)) return 1;
    for (int i = 0; i < b->num_expr_stmts; i++)
        if (expr_references_func(b->expr_stmts[i], func)) return 1;
    if (b->final_expr && expr_references_func(b->final_expr, func)) return 1;
    return 0;
}

static void dce_collect_from_block(const struct ASTBlock *b, struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **worklist, int *n_wl, int max_wl, int *in_wl, int used_mono[][64], int used_mono_rows) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) dce_collect_from_expr(b->const_decls[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) dce_collect_from_expr(b->let_decls[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_loops; i++)
        dce_collect_from_block(b->loops[i].body, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) dce_collect_from_expr(b->for_loops[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        if (b->for_loops[i].cond) dce_collect_from_expr(b->for_loops[i].cond, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        if (b->for_loops[i].step) dce_collect_from_expr(b->for_loops[i].step, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        dce_collect_from_block(b->for_loops[i].body, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            dce_collect_from_expr(b->labeled_stmts[i].u.return_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_expr_stmts; i++)
        dce_collect_from_expr(b->expr_stmts[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    if (b->final_expr) dce_collect_from_expr(b->final_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
}

void codegen_compute_used(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs_out, int *n_used_out, int max_used,
    int used_mono[][64]) {
    if (!entry || !entry->main_func || !used_funcs_out || !n_used_out || max_used <= 0) return;
    if (used_mono) {
        for (int r = 0; r <= ndep; r++)
            for (int k = 0; k < 64; k++) used_mono[r][k] = 0;
    }
    int n = 0;
    used_funcs_out[n++] = entry->main_func;
    struct ASTFunc *worklist[256];
    int n_wl = 0;
    worklist[n_wl++] = (struct ASTFunc *)entry->main_func;
    int used_mono_rows = used_mono ? (1 + ndep) : 0;
    /* 种子：先遍历 main 体填满 worklist，再把 worklist 中所有函数加入 used，确保入口引用的 import 符号不被误删 */
    if (entry->main_func->body)
        dce_collect_from_block(entry->main_func->body, entry, dep_mods, ndep, worklist, &n_wl, 256, NULL, used_mono, used_mono_rows);
    for (int i = 0; i < n_wl && n < max_used; i++) {
        struct ASTFunc *f = worklist[i];
        if (!f) continue;
        int already = 0;
        for (int j = 0; j < n; j++) if (used_funcs_out[j] == f) { already = 1; break; }
        if (!already) used_funcs_out[n++] = f;
    }
    while (n_wl > 0) {
        struct ASTFunc *f = worklist[--n_wl];
        if (!f || !f->body) continue;
        {
            int already = 0;
            for (int i = 0; i < n; i++) if (used_funcs_out[i] == f) { already = 1; break; }
            if (!already && n < max_used) used_funcs_out[n++] = f;
        }
        dce_collect_from_block(f->body, entry, dep_mods, ndep, worklist, &n_wl, 256, NULL, used_mono, used_mono_rows);
    }
    *n_used_out = n;
}

/** 若 name 非空且未在 out[0..*n) 中则追加并返回 1，否则返回 0；*n 不超过 max。 */
static int add_used_type_name(const char *name, const char **out, int *n, int max) {
    if (!name || !*name || *n >= max) return 0;
    for (int i = 0; i < *n; i++) if (out[i] && strcmp(out[i], name) == 0) return 0;
    out[(*n)++] = name;
    return 1;
}

/** 从类型中收集 NAMED 类型名并递归 elem_type。 */
static void collect_type_from_type(const struct ASTType *ty, const char **out, int *n, int max) {
    if (!ty || *n >= max) return;
    if (ty->kind == AST_TYPE_NAMED && ty->name) add_used_type_name(ty->name, out, n, max);
    if (ty->elem_type) collect_type_from_type(ty->elem_type, out, n, max);
}

/** 从表达式中收集类型名（resolved_type、struct_lit.struct_name）并递归子表达式。 */
static void collect_type_from_expr(const struct ASTExpr *e, const char **out, int *n, int max) {
    if (!e || *n >= max) return;
    if (e->resolved_type) collect_type_from_type(e->resolved_type, out, n, max);
    if (e->kind == AST_EXPR_STRUCT_LIT && e->value.struct_lit.struct_name)
        add_used_type_name(e->value.struct_lit.struct_name, out, n, max);
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++) collect_type_from_expr(e->value.call.args[i], out, n, max);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_type_from_expr(e->value.method_call.base, out, n, max);
            for (int i = 0; i < e->value.method_call.num_args; i++) collect_type_from_expr(e->value.method_call.args[i], out, n, max);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            collect_type_from_expr(e->value.binop.left, out, n, max);
            collect_type_from_expr(e->value.binop.right, out, n, max);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC:
        case AST_EXPR_RETURN:
            collect_type_from_expr(e->value.unary.operand, out, n, max);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_type_from_expr(e->value.if_expr.cond, out, n, max);
            collect_type_from_expr(e->value.if_expr.then_expr, out, n, max);
            if (e->value.if_expr.else_expr) collect_type_from_expr(e->value.if_expr.else_expr, out, n, max);
            break;
        case AST_EXPR_MATCH:
            collect_type_from_expr(e->value.match_expr.matched_expr, out, n, max);
            for (int i = 0; i < e->value.match_expr.num_arms; i++) collect_type_from_expr(e->value.match_expr.arms[i].result, out, n, max);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_type_from_expr(e->value.field_access.base, out, n, max);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++) collect_type_from_expr(e->value.struct_lit.inits[i], out, n, max);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++) collect_type_from_expr(e->value.array_lit.elems[i], out, n, max);
            break;
        case AST_EXPR_INDEX:
            collect_type_from_expr(e->value.index.base, out, n, max);
            collect_type_from_expr(e->value.index.index_expr, out, n, max);
            break;
        default: break;
    }
}

/** 从块中收集类型名。 */
static void collect_type_from_block(const struct ASTBlock *b, const char **out, int *n, int max) {
    if (!b || *n >= max) return;
    for (int i = 0; i < b->num_consts; i++) {
        if (b->const_decls[i].type) collect_type_from_type(b->const_decls[i].type, out, n, max);
        if (b->const_decls[i].init) collect_type_from_expr(b->const_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].type) collect_type_from_type(b->let_decls[i].type, out, n, max);
        if (b->let_decls[i].init) collect_type_from_expr(b->let_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_loops; i++) collect_type_from_block(b->loops[i].body, out, n, max);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_type_from_expr(b->for_loops[i].init, out, n, max);
        if (b->for_loops[i].cond) collect_type_from_expr(b->for_loops[i].cond, out, n, max);
        if (b->for_loops[i].step) collect_type_from_expr(b->for_loops[i].step, out, n, max);
        collect_type_from_block(b->for_loops[i].body, out, n, max);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_type_from_expr(b->labeled_stmts[i].u.return_expr, out, n, max);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_type_from_expr(b->expr_stmts[i], out, n, max);
    if (b->final_expr) collect_type_from_expr(b->final_expr, out, n, max);
}

/** 对已收集的类型名做结构体字段传递闭包：若某名为本模块或依赖中的 struct，则将其字段类型名加入集合（多轮至不动点）。 */
static void close_struct_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    const char **out, int *n, int max) {
    struct ASTModule *mods[33];
    int nmods = 0;
    if (entry) mods[nmods++] = entry;
    for (int i = 0; i < ndep && dep_mods && nmods < 33; i++) if (dep_mods[i]) mods[nmods++] = dep_mods[i];
    for (int round = 0; round < 8; round++) {
        int added = 0;
        for (int i = 0; i < *n; i++) {
            const char *name = out[i];
            if (!name) continue;
            for (int m = 0; m < nmods; m++) {
                struct ASTStructDef **sd = mods[m]->struct_defs;
                int num = mods[m]->num_structs;
                if (!sd) continue;
                for (int j = 0; j < num; j++) {
                    if (!sd[j] || !sd[j]->name || strcmp(sd[j]->name, name) != 0) continue;
                    for (int k = 0; k < sd[j]->num_fields; k++) {
                        const struct ASTType *fty = sd[j]->fields[k].type;
                        if (fty) collect_type_from_type(fty, out, n, max);
                    }
                    added = 1;
                    break;
                }
                if (added) break;
            }
        }
        if (!added) break;
    }
}

void codegen_compute_used_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs, int n_used, const char **used_type_names_out, int *n_out, int max_types) {
    if (!used_type_names_out || !n_out || max_types <= 0) return;
    *n_out = 0;
    for (int i = 0; i < n_used && used_funcs && used_funcs[i]; i++) {
        const struct ASTFunc *f = used_funcs[i];
        if (f->return_type) collect_type_from_type(f->return_type, used_type_names_out, n_out, max_types);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) collect_type_from_type(f->params[j].type, used_type_names_out, n_out, max_types);
        if (f->body) collect_type_from_block(f->body, used_type_names_out, n_out, max_types);
    }
    close_struct_types(entry, dep_mods, ndep, used_type_names_out, n_out, max_types);
}

/**
 * 将入口模块生成 C；功能、参数、返回值见 codegen.h 声明处注释。
 * 多函数：先生成所有函数的 vector/slice 前置定义，再按「非 main 先、main 最后」生成各函数定义。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx) {
    if (!m || !out) return -1;
    if (!m->main_func || !m->main_func->body) return -1;
    if (strcmp(m->main_func->name, "main") != 0) return -1;
    if (!m->funcs || m->num_funcs <= 0) return -1;

    codegen_current_module = m;
    codegen_dep_mods = dep_mods;
    codegen_dep_paths = dep_import_paths;
    codegen_ndep = dep_mods && dep_import_paths ? ndep : 0;
    codegen_slice_emitted_n = 0;
    codegen_vector_emitted_n = 0;
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include <stdlib.h>\n");
    fprintf(out, "#include <stdint.h>\n");
    fprintf(out, "#include <stddef.h>\n");
    /* 依赖模块中的 enum 须在 struct 之前输出，避免 struct 字段 "enum prefix_Name" 引用不完整类型 */
    if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->enum_defs) continue;
            char pre[256];
            import_path_to_c_prefix(codegen_dep_paths[i], pre, sizeof(pre));
            for (int j = 0; j < d->num_enums; j++) {
                const struct ASTEnumDef *ed = d->enum_defs[j];
                if (!ed || !ed->name) continue;
                fprintf(out, "enum %s%s { ", pre, ed->name);
                for (int k = 0; k < ed->num_variants; k++) {
                    if (k > 0) fprintf(out, ", ");
                    fprintf(out, "%s%s_%s", pre, ed->name, ed->variant_names[k] ? ed->variant_names[k] : "");
                }
                fprintf(out, " };\n");
            }
        }
    }
    /* 依赖模块中的 struct 须在 extern 声明之前输出，避免 extern 引用不完整类型（如 std.mem.Buffer） */
    if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->struct_defs) continue;
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd) continue;
                for (int k = 0; k < sd->num_fields; k++)
                    if (sd->fields[k].type) ensure_slice_struct(sd->fields[k].type, out);
            }
        }
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->struct_defs) continue;
            char pre[256];
            import_path_to_c_prefix(codegen_dep_paths[i], pre, sizeof(pre));
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd || !sd->name) continue;
                fprintf(out, "struct %s%s { ", pre, sd->name);
                for (int k = 0; k < sd->num_fields; k++) {
                    const struct ASTType *fty = sd->fields[k].type;
                    const char *fname = sd->fields[k].name ? sd->fields[k].name : "";
                    if (fty && fty->kind == AST_TYPE_ARRAY && fty->elem_type)
                        fprintf(out, "%s %s[%d]; ", c_type_str(fty->elem_type), fname, fty->array_size);
                    else
                        fprintf(out, "%s %s; ", fty ? c_type_str(fty) : "int32_t", fname);
                }
                fprintf(out, "};\n");
            }
        }
    }
    /* 跨模块调用：收集本模块内对 import 函数的调用，生成 extern 声明（含泛型单态化，阶段 7.3） */
    {
        const char *imp_paths[MAX_IMPORT_DECLS];
        struct ASTFunc *imp_funcs[MAX_IMPORT_DECLS];
        int nimp = 0;
        const char *gen_paths[MAX_GEN_IMPORT_DECLS];
        struct ASTFunc *gen_funcs[MAX_GEN_IMPORT_DECLS];
        struct ASTType **gen_type_args[MAX_GEN_IMPORT_DECLS];
        int gen_n[MAX_GEN_IMPORT_DECLS];
        int gen_count = 0;
        for (int i = 0; i < m->num_funcs && m->funcs; i++)
            if (m->funcs[i] && m->funcs[i]->body)
                collect_import_calls_from_block(m->funcs[i]->body, imp_paths, imp_funcs, &nimp,
                    gen_paths, gen_funcs, gen_type_args, gen_n, &gen_count);
        /* 入口使用 []T 时 extern 会引用 struct shulang_slice_*，须先输出 slice 结构体定义 */
        for (int i = 0; i < nimp; i++) {
            const struct ASTFunc *f = imp_funcs[i];
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int j = 0; j < f->num_params; j++)
                if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
        }
        for (int i = 0; i < gen_count; i++) {
            const struct ASTFunc *f = gen_funcs[i];
            struct ASTType **ta = gen_type_args[i];
            int nta = gen_n[i];
            const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, ta, nta);
            if (ret_ty) ensure_slice_struct(ret_ty, out);
            for (int j = 0; j < f->num_params; j++) {
                const struct ASTType *pt = subst_type(f->params[j].type, f->generic_param_names, ta, nta);
                if (pt) ensure_slice_struct(pt, out);
            }
        }
        for (int i = 0; i < nimp; i++) {
            char pre[256];
            import_path_to_c_prefix(imp_paths[i], pre, sizeof(pre));
            const struct ASTFunc *f = imp_funcs[i];
            fprintf(out, "extern %s %s%s(", c_type_str(f->return_type), pre, f->name ? f->name : "");
            for (int j = 0; j < f->num_params; j++) {
                if (j) fprintf(out, ", ");
                codegen_emit_param(&f->params[j], out, NULL);
            }
            fprintf(out, ");\n");
        }
        for (int i = 0; i < gen_count; i++) {
            const struct ASTFunc *f = gen_funcs[i];
            struct ASTType **ta = gen_type_args[i];
            int nta = gen_n[i];
            const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, ta, nta);
            char pre[256];
            import_path_to_c_prefix(gen_paths[i], pre, sizeof(pre));
            fprintf(out, "extern %s %s%s(", c_type_str(ret_ty), pre, mono_instance_mangled_name(f, ta, nta));
            for (int j = 0; j < f->num_params; j++) {
                if (j) fprintf(out, ", ");
                const struct ASTType *pt = subst_type(f->params[j].type, f->generic_param_names, ta, nta);
                codegen_emit_param(&f->params[j], out, pt);
            }
            fprintf(out, ");\n");
        }
    }
    /* 为所有函数体块及泛型单态化实例体生成 vector/slice 前置定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] && m->funcs[i]->body)
            ensure_block_vector_typedefs(m->funcs[i]->body, out);
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++)
        if (m->mono_instances[k].template && m->mono_instances[k].template->body)
            ensure_block_vector_typedefs(m->mono_instances[k].template->body, out);
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j]->body)
                ensure_block_vector_typedefs(m->impl_blocks[k]->funcs[j]->body, out);
    /* 入口模块自身函数若参数/返回为 []T，须先输出 slice 结构体定义，避免 C 不完整类型 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0) continue;
        if (f->return_type) ensure_slice_struct(f->return_type, out);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int p = 0; p < f->num_params; p++)
                if (f->params[p].type) ensure_slice_struct(f->params[p].type, out);
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        if (ret_ty) ensure_slice_struct(ret_ty, out);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (pt) ensure_slice_struct(pt, out);
        }
    }
    /* 顶层枚举定义 → C enum；阶段 8.1 DCE 扩展：若 is_type_used 非 NULL 则仅输出被引用枚举 */
    for (int i = 0; i < m->num_enums && m->enum_defs; i++) {
        const struct ASTEnumDef *ed = m->enum_defs[i];
        if (!ed || !ed->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, ed->name)) continue;
        fprintf(out, "enum %s { ", ed->name);
        for (int j = 0; j < ed->num_variants; j++) {
            if (j > 0) fprintf(out, ", ");
            fprintf(out, "%s_%s", ed->name, ed->variant_names[j] ? ed->variant_names[j] : "");
        }
        fprintf(out, " };\n");
    }
    /* 顶层结构体定义 → C struct；阶段 8.1 DCE 扩展：若 is_type_used 非 NULL 则仅输出被引用结构体 */
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || !sd->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name)) continue;
        fprintf(out, "struct %s { ", sd->name);
        for (int j = 0; j < sd->num_fields; j++) {
            const struct ASTType *fty = sd->fields[j].type;
            const char *fname = sd->fields[j].name ? sd->fields[j].name : "";
            if (fty && fty->kind == AST_TYPE_ARRAY && fty->elem_type)
                fprintf(out, "%s %s[%d]; ", c_type_str(fty->elem_type), fname, fty->array_size);
            else {
                const char *cty = fty ? c_type_str(fty) : "int32_t";
                fprintf(out, "%s %s; ", cty, fname);
            }
        }
        if (sd->packed)
            fprintf(out, "} __attribute__((packed));\n");
        else
            fprintf(out, "};\n");
    }
    /* 冷路径辅助：panic 分支标记 noreturn+cold，利于 ICache 与分支预测（控制流清单 §8.3） */
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) {\n");
    fprintf(out, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
    fprintf(out, "  abort();\n");
    fprintf(out, "}\n");
    /* 入口模块内函数前向声明：满足 C 要求（任意顺序调用须先声明后定义）；对所有有体的非 main、非 extern、非泛型函数均声明，避免 DCE 未收集到的同模块 callee 导致 C undeclared */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0 || f->is_extern || !f->body) continue;
        fprintf(out, "static inline %s %s(", c_type_str(f->return_type), f->name ? f->name : "");
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            fprintf(out, "static inline %s %s(", c_type_str(f->return_type), impl_method_c_name(f));
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                codegen_emit_param(&f->params[p], out, NULL);
            }
            fprintf(out, ");\n");
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        fprintf(out, "static inline %s %s(", ret_ty ? c_type_str(ret_ty) : "int32_t", mono_instance_mangled_name(f, inst->type_args, inst->num_type_args));
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (p) fprintf(out, ", ");
            codegen_emit_param(&f->params[p], out, pt);
        }
        fprintf(out, ");\n");
    }
    /* 先输出非 main 函数，再输出 impl 方法、泛型单态化实例，最后 main；阶段 8.1 DCE 时仅输出已引用；若未在 used 中但被 main 体直接引用则兜底保留；extern 函数仅声明不生成定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") == 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (m->funcs[i]->is_extern || !m->funcs[i]->body) continue;
        /* 入口模块内被同模块调用的函数须全部生成定义，否则 DCE 未收集到的间接 callee 会导致链接未定义符号；此处不再按 DCE 过滤 */
        if (codegen_one_func(m->funcs[i], m, out) != 0) {
            fprintf(stderr, "codegen error: failed to emit function '%s'\n", m->funcs[i]->name ? m->funcs[i]->name : "?");
            return -1;
        }
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->impl_blocks[k]->funcs[j])) {
                if (!m->main_func || !m->main_func->body || !block_references_func(m->main_func->body, m->impl_blocks[k]->funcs[j])) continue;
            }
            if (codegen_one_impl_func(m->impl_blocks[k]->funcs[j], m, out) != 0) return -1;
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        if (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k)) continue;
        if (codegen_one_mono_instance(inst->template, inst->type_args, inst->num_type_args, m, out) != 0) return -1;
    }
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") != 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->funcs[i])) continue;
        if (codegen_one_func(m->funcs[i], m, out) != 0) return -1;
        break;
    }
    return 0;
}

/**
 * 将库模块生成 C（类型与函数带 import 前缀，避免与入口模块符号冲突）；功能见 codegen.h。阶段 8.1 DCE 时仅输出已引用。
 * lib_dep_mods/lib_dep_paths/n_lib_dep 为该库的 import 依赖，用于生成跨模块调用前缀（库内调用其他 import 时）。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx) {
    if (!m || !out) return -1;
    static char lib_prefix_buf[256];
    size_t off = 0;
    if (import_path) {
        for (const char *s = import_path; *s && off + 2 < sizeof(lib_prefix_buf); s++)
            lib_prefix_buf[off++] = (*s == '.') ? '_' : *s;
    }
    if (off + 1 < sizeof(lib_prefix_buf)) lib_prefix_buf[off++] = '_';
    lib_prefix_buf[off] = '\0';
    codegen_library_prefix = lib_prefix_buf;
    codegen_library_module = m;
    codegen_library_import_path = import_path;
    codegen_dep_mods = lib_dep_mods;
    codegen_dep_paths = lib_dep_paths;
    codegen_ndep = (lib_dep_mods && lib_dep_paths) ? n_lib_dep : 0;
    codegen_slice_emitted_n = 0;

    fprintf(out, "/* generated from %s */\n", import_path ? import_path : "");
    fprintf(out, "#include <stdint.h>\n");
    fprintf(out, "#include <stddef.h>\n");
    fprintf(out, "#include <stdlib.h>\n");
    fprintf(out, "#include <stdio.h>\n");

    /* 本库对 lib_dep 的调用：收集后生成 extern，避免 C 编译 undeclared */
    if (codegen_ndep > 0 && lib_dep_mods && lib_dep_paths) {
        const char *ext_paths[MAX_IMPORT_DECLS];
        struct ASTFunc *ext_funcs[MAX_IMPORT_DECLS];
        int n_ext = 0;
        for (int i = 0; i < m->num_funcs && m->funcs; i++)
            if (m->funcs[i] && m->funcs[i]->body)
                collect_lib_dep_calls_from_block(m->funcs[i]->body, lib_dep_mods, lib_dep_paths, n_lib_dep, ext_paths, ext_funcs, &n_ext, MAX_IMPORT_DECLS);
        for (int k = 0; k < n_ext && ext_paths[k] && ext_funcs[k]; k++) {
            char pre[256];
            import_path_to_c_prefix(ext_paths[k], pre, sizeof(pre));
            const struct ASTFunc *f = ext_funcs[k];
            fprintf(out, "extern %s %s%s(", c_type_str(f->return_type), pre, f->name ? f->name : "");
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                fprintf(out, "%s", c_type_str(f->params[p].type));
            }
            fprintf(out, ");\n");
        }
    }

    /* 库模块中若函数参数/返回类型为 []T，须先输出 slice 结构体定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0) continue;
        if (f->return_type) ensure_slice_struct(f->return_type, out);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int p = 0; p < f->num_params; p++)
                if (f->params[p].type) ensure_slice_struct(f->params[p].type, out);
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        if (ret_ty) ensure_slice_struct(ret_ty, out);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (pt) ensure_slice_struct(pt, out);
        }
    }

    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] && m->funcs[i]->body)
            ensure_block_vector_typedefs(m->funcs[i]->body, out);
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++)
        if (m->mono_instances[k].template && m->mono_instances[k].template->body)
            ensure_block_vector_typedefs(m->mono_instances[k].template->body, out);
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j]->body)
                ensure_block_vector_typedefs(m->impl_blocks[k]->funcs[j]->body, out);

    for (int i = 0; i < m->num_enums && m->enum_defs; i++) {
        const struct ASTEnumDef *ed = m->enum_defs[i];
        if (!ed || !ed->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, ed->name)) continue;
        char ename[256];
        library_prefixed_name(ed->name, ename, sizeof(ename));
        fprintf(out, "enum %s { ", ename);
        for (int j = 0; j < ed->num_variants; j++) {
            if (j > 0) fprintf(out, ", ");
            fprintf(out, "%s_%s", ename, ed->variant_names[j] ? ed->variant_names[j] : "");
        }
        fprintf(out, " };\n");
    }
    /* 结构体字段若为 []T，须先输出 slice 结构体定义，避免 C 侧不完整类型 */
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name))) continue;
        for (int j = 0; j < sd->num_fields; j++)
            if (sd->fields[j].type) ensure_slice_struct(sd->fields[j].type, out);
    }
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || !sd->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name)) continue;
        char sname[256];
        library_prefixed_name(sd->name, sname, sizeof(sname));
        fprintf(out, "struct %s { ", sname);
        for (int j = 0; j < sd->num_fields; j++) {
            const struct ASTType *fty = sd->fields[j].type;
            const char *fname = sd->fields[j].name ? sd->fields[j].name : "";
            if (fty && fty->kind == AST_TYPE_ARRAY && fty->elem_type)
                fprintf(out, "%s %s[%d]; ", c_type_str(fty->elem_type), fname, fty->array_size);
            else
                fprintf(out, "%s %s; ", fty ? c_type_str(fty) : "int32_t", fname);
        }
        if (sd->packed)
            fprintf(out, "} __attribute__((packed));\n");
        else
            fprintf(out, "};\n");
    }
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) {\n");
    fprintf(out, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
    fprintf(out, "  abort();\n");
    fprintf(out, "}\n");

    /* extern 函数：仅生成 C 的 extern 声明，符号名为 .su 中的函数名（与 C 一致），无定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || !f->is_extern) continue;
        fprintf(out, "extern %s %s(", c_type_str(f->return_type), f->name ? f->name : "");
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }

    /* 库模块内函数前向声明：满足 C 要求（递归或任意顺序调用时须先声明后定义）；无 static 以便符号可被入口模块链接 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0 || f->is_extern || !f->body) continue;
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, f)) continue;
        char fwd_name[256];
        library_prefixed_name(f->name, fwd_name, sizeof(fwd_name));
        fprintf(out, "%s %s(", c_type_str(f->return_type), fwd_name);
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f || (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, f))) continue;
            char fwd_name[256];
            library_prefixed_name(impl_method_c_name(f), fwd_name, sizeof(fwd_name));
            fprintf(out, "%s %s(", c_type_str(f->return_type), fwd_name);
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                codegen_emit_param(&f->params[p], out, NULL);
            }
            fprintf(out, ");\n");
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args || (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k))) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        char fwd_name[256];
        library_prefixed_name(mono_instance_mangled_name(f, inst->type_args, inst->num_type_args), fwd_name, sizeof(fwd_name));
        fprintf(out, "%s %s(", ret_ty ? c_type_str(ret_ty) : "int32_t", fwd_name);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (p) fprintf(out, ", ");
            codegen_emit_param(&f->params[p], out, pt);
        }
        fprintf(out, ");\n");
    }

    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") == 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (m->funcs[i]->is_extern || !m->funcs[i]->body) continue; /* extern 无体，不生成定义 */
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->funcs[i])) continue;
        if (codegen_one_func(m->funcs[i], m, out) != 0) { codegen_library_prefix = NULL; codegen_library_module = NULL; codegen_library_import_path = NULL; codegen_dep_mods = NULL; codegen_dep_paths = NULL; codegen_ndep = 0; return -1; }
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->impl_blocks[k]->funcs[j])) continue;
            if (codegen_one_impl_func(m->impl_blocks[k]->funcs[j], m, out) != 0) { codegen_library_prefix = NULL; codegen_library_module = NULL; codegen_library_import_path = NULL; codegen_dep_mods = NULL; codegen_dep_paths = NULL; codegen_ndep = 0; return -1; }
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        if (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k)) continue;
        if (codegen_one_mono_instance(inst->template, inst->type_args, inst->num_type_args, m, out) != 0) {
            codegen_library_prefix = NULL;
            codegen_library_module = NULL;
            codegen_library_import_path = NULL;
            codegen_dep_mods = NULL;
            codegen_dep_paths = NULL;
            codegen_ndep = 0;
            return -1;
        }
    }
    codegen_library_prefix = NULL;
    codegen_library_module = NULL;
    codegen_library_import_path = NULL;
    codegen_dep_mods = NULL;
    codegen_dep_paths = NULL;
    codegen_ndep = 0;
    return 0;
}
