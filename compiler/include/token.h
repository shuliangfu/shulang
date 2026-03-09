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
    TOKEN_FUNCTION, /**< 关键字 function（函数定义） */
    TOKEN_LET,      /**< 关键字 let（变量） */
    TOKEN_CONST,    /**< 关键字 const（常量） */
    TOKEN_IF,       /**< 关键字 if（条件） */
    TOKEN_ELSE,     /**< 关键字 else */
    TOKEN_WHILE,    /**< 关键字 while（循环） */
    TOKEN_LOOP,     /**< 关键字 loop（无限循环，等价 while true） */
    TOKEN_FOR,      /**< 关键字 for（C 风格 for(init;cond;step)） */
    TOKEN_BREAK,    /**< 关键字 break（跳出循环） */
    TOKEN_CONTINUE, /**< 关键字 continue（继续下一轮） */
    TOKEN_RETURN,   /**< 关键字 return（显式返回） */
    TOKEN_PANIC,    /**< 关键字 panic（终止并可选打印） */
    TOKEN_DEFER,    /**< 关键字 defer（作用域退出时执行） */
    TOKEN_MATCH,    /**< 关键字 match（多分支匹配） */
    TOKEN_STRUCT,   /**< 关键字 struct（结构体定义） */
    TOKEN_PACKED,   /**< 关键字 packed（结构体无填充布局，与 C __attribute__((packed)) 一致） */
    TOKEN_ENUM,     /**< 关键字 enum（枚举定义，§7） */
    TOKEN_GOTO,     /**< 关键字 goto（跳转） */
    TOKEN_TRAIT,    /**< 关键字 trait（接口定义，阶段 7.2） */
    TOKEN_IMPL,     /**< 关键字 impl（trait 实现，阶段 7.2） */
    TOKEN_SELF,     /**< 关键字 self（方法接收者，阶段 7.2） */
    TOKEN_UNDERSCORE, /**< _（match 通配模式） */
    TOKEN_IMPORT,   /**< 关键字 import（阶段 5） */
    TOKEN_EXTERN,   /**< 关键字 extern（FFI：声明 C 函数，无体） */
    TOKEN_IDENT,    /**< 标识符（如 main） */
    TOKEN_I32,      /**< 类型名 i32（内建整数） */
    TOKEN_BOOL,     /**< 类型名 bool（布尔） */
    TOKEN_U8,       /**< 类型名 u8（字节） */
    TOKEN_U32,      /**< 类型名 u32 */
    TOKEN_U64,      /**< 类型名 u64 */
    TOKEN_I64,      /**< 类型名 i64 */
    TOKEN_USIZE,    /**< 类型名 usize（与指针同宽的无符号整数） */
    TOKEN_ISIZE,    /**< 类型名 isize（与指针同宽的有符号整数） */
    TOKEN_I32X4,    /**< 类型名 i32x4（4 车道 i32 向量，文档 §10） */
    TOKEN_I32X8,    /**< 类型名 i32x8（8 车道 i32 向量） */
    TOKEN_I32X16,   /**< 类型名 i32x16（16 车道 i32 向量，512-bit，对应 AVX-512） */
    TOKEN_U32X4,    /**< 类型名 u32x4（4 车道 u32 向量） */
    TOKEN_U32X8,    /**< 类型名 u32x8（8 车道 u32 向量） */
    TOKEN_U32X16,   /**< 类型名 u32x16（16 车道 u32 向量，512-bit） */
    TOKEN_TRUE,     /**< 布尔字面量 true */
    TOKEN_FALSE,    /**< 布尔字面量 false */
    TOKEN_F32,      /**< 类型名 f32（32 位浮点，文档阶段 8+） */
    TOKEN_F64,      /**< 类型名 f64（64 位浮点） */
    TOKEN_VOID,     /**< 类型名 void（仅用于函数返回类型，如 extern function foo(): void;） */
    TOKEN_INT,      /**< 整数字面量 */
    TOKEN_FLOAT,    /**< 浮点字面量（如 0.0、1.5） */
    TOKEN_LPAREN,   /**< ( */
    TOKEN_RPAREN,   /**< ) */
    TOKEN_LBRACE,   /**< { */
    TOKEN_RBRACE,   /**< } */
    TOKEN_LBRACKET, /**< [ 用于数组类型 [N]T、数组字面量、下标 */
    TOKEN_RBRACKET, /**< ] */
    TOKEN_ARROW,    /**< -> */
    TOKEN_FATARROW, /**< => 用于 match 分支 */
    TOKEN_COMMA,    /**< , 预留 */
    TOKEN_COLON,    /**< : 用于 let x: i32、const N: i32 */
    TOKEN_DOT,      /**< . 用于 import core.types */
    TOKEN_SEMICOLON,/**< ; 用于 import path; */
    TOKEN_PLUS,     /**< + 二元加 */
    TOKEN_MINUS,    /**< - 二元减（单字符 -，非 ->） */
    TOKEN_STAR,     /**< * 二元乘 */
    TOKEN_SLASH,    /**< / 二元除（仅单字符 /，非 // 注释） */
    TOKEN_PERCENT,  /**< % 取模 */
    TOKEN_AMP,      /**< & 按位与（单字符） */
    TOKEN_PIPE,     /**< | 按位或（单字符） */
    TOKEN_CARET,    /**< ^ 按位异或 */
    TOKEN_LSHIFT,   /**< << 左移 */
    TOKEN_RSHIFT,   /**< >> 右移 */
    TOKEN_TILDE,    /**< ~ 按位取反（一元） */
    TOKEN_ASSIGN,   /**< = 赋值/初始化（单字符，非 ==） */
    TOKEN_EQ,       /**< == 等于 */
    TOKEN_NE,       /**< != 不等于 */
    TOKEN_LT,       /**< < 小于 */
    TOKEN_GT,       /**< > 大于 */
    TOKEN_LE,       /**< <= 小于等于 */
    TOKEN_GE,       /**< >= 大于等于 */
    TOKEN_AMPAMP,   /**< && 逻辑与 */
    TOKEN_PIPEPIPE, /**< || 逻辑或 */
    TOKEN_BANG,     /**< ! 逻辑非（一元） */
    TOKEN_QUESTION  /**< ? 三元运算符 cond ? then : else */
} TokenKind;

/** 单个 Token：类型 + 源码位置 + 可选值（字面量/标识符） */
typedef struct Token {
    TokenKind kind;
    int line;   /**< 行号，从 1 开始 */
    int col;    /**< 列号，从 1 开始 */
    union {
        int int_val;        /**< TOKEN_INT 时使用 */
        double float_val;   /**< TOKEN_FLOAT 时使用 */
        const char *ident;  /**< TOKEN_IDENT / TOKEN_I32 等部分类型 Token 时指向源码中的标识符（不拷贝，生命周期由调用方保证） */
    } value;
    /** TOKEN_IDENT / 类型名 Token 时标识符字节长度，其它为 0 */
    int ident_len;
} Token;

#endif /* SHUC_TOKEN_H */
