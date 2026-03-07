/**
 * typeck.h — 类型检查接口
 *
 * 文件职责：声明对 AST 模块做类型检查的入口 typeck_module，供 Driver 在 parse 之后、codegen 之前调用。
 * 所属模块：编译器前端 typeck，compiler/src/typeck/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/codegen。
 * 重要约定：阶段 3 最小子集仅校验「有 main 则返回 i32、体为整数字面量」；库模块（无 main）直接通过。类型错误时向 stderr 输出并返回 -1。
 */

#ifndef SHUC_TYPECK_H
#define SHUC_TYPECK_H

struct ASTModule;

/**
 * 对模块做类型检查。
 * 功能说明：若有 main 则校验返回类型为 i32、体为整数字面量；无 main 的库模块视为通过。
 * 参数：m 已解析的 AST 模块；NULL 时返回 -1 并报错。
 * 返回值：0 通过；-1 类型错误且已向 stderr 输出 "typeck error: ..."。
 * 错误与边界：m 为 NULL、main 返回类型非 i32、无 body 或 body 非整数字面量时返回 -1。
 * 副作用与约定：只读 m；不分配内存；不修改 m。
 */
int typeck_module(struct ASTModule *m);

#endif /* SHUC_TYPECK_H */
