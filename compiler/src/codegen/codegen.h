/**
 * codegen.h — 代码生成接口
 *
 * 文件职责：声明将 AST 生成 C 源码的两个入口（入口模块含 main、库模块占位），供 Driver 在 typeck 之后调用并交给 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/typeck；输出流由 main 管理。
 * 重要约定：阶段 4 方案 B，入口模块生成 Hello World 的 printf 且 return 使用 main 体表达式的值（当前仅整数字面量）；库模块仅生成注释行（阶段 7.3）。阶段 8.1 DCE：可选传入 is_func_used/is_mono_used 仅生成被引用的函数与单态化实例。
 */

#ifndef SHU_CODEGEN_H
#define SHU_CODEGEN_H

#include <stdio.h>

struct ASTModule;
struct ASTFunc;

/** 阶段 8.1 DCE：可选回调，若非 NULL 则仅生成被引用函数/单态化/类型。ctx 由调用方传入。 */
typedef int (*codegen_is_func_used_fn)(void *ctx, const struct ASTModule *mod, const struct ASTFunc *func);
typedef int (*codegen_is_mono_used_fn)(void *ctx, const struct ASTModule *mod, int mono_k);
/** 阶段 8.1 DCE 扩展：若提供则仅生成被引用的结构体/枚举定义；NULL 表示全部输出。 */
typedef int (*codegen_is_type_used_fn)(void *ctx, const struct ASTModule *mod, const char *type_name);

/** 单文件多模块时避免 enum/struct 重定义：调用方提供 emitted_type_names[][64] 与 *n_emitted_inout；codegen 输出前检查、输出后追加 C 类型名。NULL 表示不启用。 */
#define CODEGEN_EMITTED_TYPE_NAME_MAX 64

/**
 * 将入口模块（含 main）生成 C 源码写入 out。
 * 若 is_func_used/is_mono_used 非 NULL，仅生成被引用函数与单态化实例；若 is_type_used 非 NULL 则仅生成被引用 struct/enum（阶段 8.1 DCE）。
 * emitted_type_names/n_emitted_inout/max_emitted 非 NULL 时用于单文件去重：已出现的 C 类型名不再输出。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);

/**
 * 将库模块（无 main 或仅 import）生成 C 写入 out；若 is_*_used 非 NULL 则仅生成被引用部分（阶段 8.1 DCE）。
 * lib_dep_mods / lib_dep_paths / n_lib_dep 为该库模块的 import 依赖，用于生成跨模块调用时的 C 前缀（传递依赖）。
 * emitted_type_names/n_emitted_inout/max_emitted 非 NULL 时用于单文件去重。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);

/**
 * 阶段 8.1 DCE：从 main 起算可达性，填充 used_funcs 与 used_mono。used_funcs 与 used_mono 由调用方分配。
 * used_mono 为 (1+ndep) 行、每行 AST_MODULE_MAX_MONO_INSTANCES 的 int 数组，used_mono[0] 为入口模块，used_mono[1+i] 为 dep_mods[i]。
 */
void codegen_compute_used(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs_out, int *n_used_out, int max_used,
    int used_mono[][64]);

/**
 * 阶段 8.1 DCE 扩展：从已用函数与 mono 中收集被引用的类型名（struct/enum），并做结构体字段传递闭包；结果写入 used_type_names_out，供 is_type_used 使用。
 */
void codegen_compute_used_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs, int n_used, const char **used_type_names_out, int *n_out, int max_types);

/**
 * 阶段 3.1（完全脱离 C 路线图）：仅输出依赖模块的类型定义（enum/struct，带 import 前缀），不输出函数体。
 * 供 -E-extern 生成「瘦」pipeline_gen.c 时先输出 ast/parser/typeck/codegen 等类型，再输出入口模块（extern + 本体）。
 */
int codegen_emit_dep_types_only(struct ASTModule **mods, const char **import_paths, int n, FILE *out);

/**
 * .su pipeline 用：在调用 pipeline_run_su_pipeline 前设置 dep 模块与路径，使 codegen 生成跨 dep 调用时使用正确 C 符号前缀（如 std_io_driver_）；调用后由 pipeline 或 driver 在适当时机清空。
 */
void codegen_set_dep_slots_for_su_pipeline(struct ASTModule **mods, const char **paths, int n);

/** .su 用：path 为 "std.io.core" 时返回 1，codegen 不为其加前缀，生成 shu_io_register 等符号。 */
int codegen_su_path_is_std_io_core(const char *path);

#endif /* SHU_CODEGEN_H */
