/**
 * codegen.h — 代码生成接口
 *
 * 文件职责：声明将 AST 生成 C 源码的两个入口（入口模块含 main、库模块占位），供 Driver 在 typeck 之后调用并交给 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/typeck；输出流由 main 管理。
 * 重要约定：阶段 4 方案 B，入口模块生成 Hello World 的 printf 且 return 使用 main 体表达式的值（当前仅整数字面量）；库模块仅生成注释行（阶段 7.3）。阶段 8.1 DCE：可选传入 is_func_used/is_mono_used 仅生成被引用的函数与单态化实例。
 */

#ifndef SHUC_CODEGEN_H
#define SHUC_CODEGEN_H

#include <stdio.h>

struct ASTModule;
struct ASTFunc;

/** 阶段 8.1 DCE：可选回调，若非 NULL 则仅生成被引用函数/单态化/类型。ctx 由调用方传入。 */
typedef int (*codegen_is_func_used_fn)(void *ctx, const struct ASTModule *mod, const struct ASTFunc *func);
typedef int (*codegen_is_mono_used_fn)(void *ctx, const struct ASTModule *mod, int mono_k);
/** 阶段 8.1 DCE 扩展：若提供则仅生成被引用的结构体/枚举定义；NULL 表示全部输出。 */
typedef int (*codegen_is_type_used_fn)(void *ctx, const struct ASTModule *mod, const char *type_name);

/**
 * 将入口模块（含 main）生成 C 源码写入 out。
 * 若 is_func_used/is_mono_used 非 NULL，仅生成被引用函数与单态化实例；若 is_type_used 非 NULL 则仅生成被引用 struct/enum（阶段 8.1 DCE）。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx);

/**
 * 将库模块（无 main 或仅 import）生成 C 写入 out；若 is_*_used 非 NULL 则仅生成被引用部分（阶段 8.1 DCE）。
 * lib_dep_mods / lib_dep_paths / n_lib_dep 为该库模块的 import 依赖，用于生成跨模块调用时的 C 前缀（传递依赖）。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx);

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

#endif /* SHUC_CODEGEN_H */
