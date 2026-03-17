/**
 * parser.h — 语法分析器接口
 *
 * 文件职责：声明从 Token 流解析为 AST 的入口 parse，供 Driver 在 lexer 之后调用，产出 ASTModule。
 * 所属模块：编译器前端 parser，compiler/src/parser/；被 src/main 引用。
 * 与其它文件的关系：依赖 include/ast.h；通过前向声明使用 Lexer，实现时包含 lexer.h；不依赖 typeck/codegen。
 * 重要约定：parse 成功后 *out 由调用方 ast_module_free；语法错误时已向 stderr 输出行号列号及信息，返回 -1。
 */

#ifndef SHU_PARSER_H
#define SHU_PARSER_H

#include "ast.h"

struct Lexer;  /* 前向声明，避免 parser 使用者强制依赖 lexer.h */

/**
 * 从 Lexer 解析整段源码为 AST 模块。
 * 功能说明：支持顶层 [ import path ; ]* 与可选的 function main() -> i32 { 整数字面量 }；库模块可为仅 import 或空。
 * 参数：lex 已创建并指向待解析源码的 Lexer，在 parse 调用期间不得被其它线程使用；out 成功时写入 ASTModule*，不可为 NULL。
 * 返回值：0 成功，*out 已设置且调用方须 ast_module_free(*out)；-1 语法错误或内存不足，*out 未修改或为 NULL，已向 stderr 输出信息。
 * 错误与边界：lex 为 NULL 或 out 为 NULL 时行为未定义；import 超过 MAX_IMPORTS 时报错。
 * 副作用与约定：会推进 lex 的读取位置；成功时分配 AST 及 strdup 的字符串，由调用方统一 free。
 */
int parse(struct Lexer *lex, ASTModule **out);

#endif /* SHU_PARSER_H */
