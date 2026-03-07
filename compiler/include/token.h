/**
 * token.h — 词法单元（Token）定义
 *
 * 文件职责：定义 Lexer 产出的 Token 种类（TokenKind）与单个 Token 结构（含 kind、位置、可选值），供 Parser 消费。
 * 所属模块：编译器前端，compiler/include/；被 src/lexer、src/parser、src/main 引用。
 * 与其它文件的关系：Lexer 根据 .su 源码填充 Token；Parser 按 Token 流递归下降构建 AST；main 打印 Token 时使用 token_kind_str。
 * 重要约定：与 compiler/docs/语法子集-阶段1与2.md 词法一致；value.ident 指向源码片段不拷贝，生命周期由调用方保证；IDENT/I32 须配合 ident_len 使用。阶段 7 将增加 TOKEN_LANGLE/TOKEN_RANGLE。
 */

#ifndef SHUC_TOKEN_H
#define SHUC_TOKEN_H

/** Token 类型枚举 */
typedef enum TokenKind {
    TOKEN_EOF = 0,
    TOKEN_FN,       /**< 关键字 fn */
    TOKEN_IMPORT,   /**< 关键字 import（阶段 5） */
    TOKEN_IDENT,    /**< 标识符（如 main） */
    TOKEN_I32,      /**< 类型名 i32 */
    TOKEN_INT,      /**< 整数字面量 */
    TOKEN_LPAREN,   /**< ( */
    TOKEN_RPAREN,   /**< ) */
    TOKEN_LBRACE,   /**< { */
    TOKEN_RBRACE,   /**< } */
    TOKEN_ARROW,    /**< -> */
    TOKEN_COMMA,    /**< , 预留 */
    TOKEN_DOT,      /**< . 用于 import core.types */
    TOKEN_SEMICOLON,/**< ; 用于 import path; */
    TOKEN_PLUS,     /**< + 二元加 */
    TOKEN_MINUS     /**< - 二元减（单字符 -，非 ->） */
} TokenKind;

/** 单个 Token：类型 + 源码位置 + 可选值（字面量/标识符） */
typedef struct Token {
    TokenKind kind;
    int line;   /**< 行号，从 1 开始 */
    int col;    /**< 列号，从 1 开始 */
    union {
        int int_val;        /**< TOKEN_INT 时使用 */
        const char *ident;  /**< TOKEN_IDENT / TOKEN_I32 时指向源码中的标识符（不拷贝，生命周期由调用方保证） */
    } value;
    /** TOKEN_IDENT / TOKEN_I32 时标识符字节长度，其它为 0 */
    int ident_len;
} Token;

#endif /* SHUC_TOKEN_H */
