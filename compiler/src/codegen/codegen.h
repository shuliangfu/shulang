/**
 * codegen.h — 代码生成接口
 *
 * 文件职责：声明将 AST 生成 C 源码的两个入口（入口模块含 main、库模块占位），供 Driver 在 typeck 之后调用并交给 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/typeck；输出流由 main 管理。
 * 重要约定：阶段 4 方案 B，入口模块生成 Hello World 的 printf 且 return 使用 main 体表达式的值（当前仅整数字面量）；库模块仅生成注释行（阶段 7.3）。
 */

#ifndef SHUC_CODEGEN_H
#define SHUC_CODEGEN_H

#include <stdio.h>

struct ASTModule;

/**
 * 将入口模块（含 main）生成 C 源码写入 out。
 * 功能说明：仅支持名为 main 的函数；生成 #include、main、extern 等；当 dep_mods 非 NULL 且 ndep>0 时，对来自依赖的 struct 类型使用 "struct prefix_Name" 以便与库 .c 符号一致。
 * 参数：m 已通过 typeck 的 AST 模块；out 输出流；dep_mods 依赖模块数组（可为 NULL）；dep_import_paths 各依赖的 import 路径（与 dep_mods 对应）；ndep 依赖个数，0 表示无依赖。
 * 返回值：0 成功；-1 表示 m 为 NULL、out 为 NULL、无 main 等。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep);

/**
 * 将库模块（无 main 或仅 import）生成 C 写入 out，供多文件链接时参与编译。
 * 功能说明：阶段 7.3 多文件；类型与函数名均加 import_path 前缀（如 foo_、core_types_），避免与入口模块符号冲突。
 * 参数：m 库模块 AST；import_path 模块路径如 foo 或 core.types，用于生成前缀；out 输出流，不可为 NULL。
 * 返回值：0 成功；-1 表示 m/out 为 NULL。副作用：写 out。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path, FILE *out);

#endif /* SHUC_CODEGEN_H */
