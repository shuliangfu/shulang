/**
 * ast.h — 抽象语法树（AST）节点定义
 *
 * 文件职责：
 *   定义 .su 源码对应的 AST 节点类型（表达式、函数、模块），供 Parser 构建、Typeck/Codegen 消费。
 * 所属模块：
 *   编译器前端，compiler/include/；被 src/parser、src/typeck、src/codegen、src/ast 引用。
 * 与其它文件的关系：
 *   - Parser 根据 token 流填充本头文件中的结构体并调用 ast_module_free；
 *   - Typeck 只读 AST 做类型检查；Codegen 只读 AST 生成 C；
 *   - ast.c 实现 ast_module_free，负责释放 Parser 分配的所有 AST 内存。
 * 重要约定：
 *   - 与 compiler/docs/语法子集-阶段1与2.md 一致；阶段 5 起支持 import_paths，阶段 7 将扩展 generic_params。
 *   - name/return_type 等字符串由 Parser 侧 strdup，由 ast_module_free 统一释放，调用方不得单独 free。
 */

#ifndef SHUC_AST_H
#define SHUC_AST_H

/** 表达式节点类型（阶段 1–2 字面量；扩展后含二元加减） */
typedef enum ASTExprKind {
    AST_EXPR_LIT,  /**< 整数字面量 */
    AST_EXPR_ADD,  /**< 二元加 left + right */
    AST_EXPR_SUB   /**< 二元减 left - right */
} ASTExprKind;

/** 表达式节点（可递归，用于二元运算） */
typedef struct ASTExpr {
    ASTExprKind kind;
    union {
        int int_val;  /**< AST_EXPR_LIT 时的值 */
        struct {
            struct ASTExpr *left;
            struct ASTExpr *right;
        } binop;      /**< AST_EXPR_ADD/SUB 时的左右操作数 */
    } value;
} ASTExpr;

/** 函数节点：name、返回类型（可为 NULL 表示未写）、体为单一表达式；阶段 7 将增加 generic_param_names/num_generic_params */
typedef struct ASTFunc {
    const char *name;       /**< 函数名，如 "main" */
    const char *return_type; /**< 返回类型名，如 "i32"，NULL 表示未写 */
    ASTExpr *body;          /**< 函数体（单一表达式） */
} ASTFunc;

/** 模块/程序：阶段 1–2 仅含一个 main；阶段 5 支持顶层 import */
typedef struct ASTModule {
    /** import 路径列表，如 "core.types"；由 parser 分配，ast_module_free 释放 */
    char **import_paths;
    int num_imports;    /**< import_paths 有效长度 */
    ASTFunc *main_func; /**< 顶层 main 函数，库模块可为 NULL */
} ASTModule;

/**
 * 释放 AST 模块及其子节点。
 *
 * 功能说明：递归释放模块内 import_paths、main_func（含 name/return_type/body）及模块自身；用于 Parser/Driver 在解析或编译结束后回收内存。
 * 参数：m 待释放的模块指针；可为 NULL，此时无操作。
 * 返回值：无。
 * 错误与边界：m 为 NULL 时安全返回；m 及其子节点不得在调用后再次使用（use-after-free）。
 * 副作用与约定：会 free 所有 Parser 通过 strndup/strdup 分配的名称与类型字符串；调用方不得再对 m->import_paths[i]、m->main_func->name 等做 free。
 */
void ast_module_free(ASTModule *m);

/**
 * 释放单棵表达式树（递归释放二元表达式的 left/right）。
 * 功能说明：用于 Parser 构建的 body 等表达式；ASTModule 释放时通过 ast_module_free 内部调用，也可由调用方在仅持有 ASTExpr* 时使用。
 * 参数：e 待释放的表达式根节点；可为 NULL，此时无操作。
 * 返回值：无。
 * 错误与边界：e 及所有子节点不得在调用后再次使用。
 * 副作用与约定：递归 free 所有子节点；不 free 除 ASTExpr 以外的指针（如 ident）。
 */
void ast_expr_free(ASTExpr *e);

#endif /* SHUC_AST_H */
