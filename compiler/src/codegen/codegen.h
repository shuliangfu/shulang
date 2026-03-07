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
 * 功能说明：仅支持名为 main 的函数；生成 #include <stdio.h>、int main(void)、printf("Hello World\\n")，且 return 语句使用 main 体表达式的值（当前仅 AST_EXPR_LIT 的 int_val），使 .su 中写 fn main() -> i32 { 42 } 时程序退出码为 42。
 * 参数：m 已通过 typeck 的 AST 模块，须含 main_func（name 为 "main"）及 body（当前须为整数字面量）；out 输出流，不可为 NULL。
 * 返回值：0 成功；-1 表示 m 为 NULL、out 为 NULL、无 main、main 名非 "main" 或 body 为 NULL。
 * 错误与边界：body 非 AST_EXPR_LIT 时仍按 0 生成（可后续扩展）；仅写 out，不关闭流。副作用：写 out，不修改 m。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out);

/**
 * 将库模块（无 main 或仅 import）生成占位 C 写入 out，供多文件链接时参与编译。
 * 功能说明：阶段 7.3 多文件；向 out 输出一行 C 注释（内容含 import_path），避免空翻译单元。
 * 参数：m 库模块 AST，可为 NULL（未使用）；import_path 模块路径如 core.types，用于注释内容，可为 NULL；out 输出流，不可为 NULL。
 * 返回值：0 成功；-1 表示 out 为 NULL。副作用：仅写 out。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path, FILE *out);

#endif /* SHUC_CODEGEN_H */
