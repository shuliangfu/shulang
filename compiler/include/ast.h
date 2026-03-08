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

/** 类型节点种类：内建整数/布尔、用户自定义名、指针等；与 analysis/变量类型与类型系统设计.md §2–§5、§六 一致 */
typedef enum ASTTypeKind {
    AST_TYPE_I32,    /**< 内建 i32 整数 */
    AST_TYPE_BOOL,   /**< 布尔 bool */
    AST_TYPE_U8,     /**< 无符号 8 位整数（字节） */
    AST_TYPE_U32,    /**< 无符号 32 位整数 */
    AST_TYPE_U64,    /**< 无符号 64 位整数 */
    AST_TYPE_I64,    /**< 有符号 64 位整数 */
    AST_TYPE_USIZE,  /**< 与指针同宽的无符号整数 */
    AST_TYPE_ISIZE,  /**< 与指针同宽的有符号整数 */
    AST_TYPE_NAMED,  /**< 用户自定义类型名（如结构体/枚举），name 保存标识符文本 */
    AST_TYPE_PTR,    /**< 裸指针 *T，elem_type 指向元素类型（见 §5.1） */
    AST_TYPE_ARRAY,  /**< 固定长数组 [N]T，elem_type 为元素类型，array_size 为 N（文档 §6.2） */
    AST_TYPE_SLICE   /**< 切片 []T，elem_type 为元素类型；语义为 { ptr, len }（文档 §6.3） */
} ASTTypeKind;

/** 类型节点：内建/具名/指针/数组/切片等；指针/数组/切片时 elem_type 非 NULL，由 ast_type_free 递归释放 */
typedef struct ASTType {
    ASTTypeKind kind;
    const char *name;  /**< 对于 AST_TYPE_NAMED 为 strdup 的类型名，其它种类可为 NULL */
    struct ASTType *elem_type;  /**< 对于 AST_TYPE_PTR / AST_TYPE_ARRAY 为元素类型，其它为 NULL */
    int array_size;    /**< 对于 AST_TYPE_ARRAY 为编译期常量长度 N，其它为 0 */
} ASTType;

/** 表达式节点类型：字面量、变量引用、二元运算、一元运算 */
typedef enum ASTExprKind {
    AST_EXPR_LIT,      /**< 整数字面量 */
    AST_EXPR_BOOL_LIT, /**< 布尔字面量 true/false（value.int_val 0/1） */
    AST_EXPR_VAR,    /**< 变量/常量引用（value.var.name 为 strdup 的名称） */
    AST_EXPR_ADD,    /**< + */
    AST_EXPR_SUB,    /**< - */
    AST_EXPR_MUL,    /**< * */
    AST_EXPR_DIV,    /**< / */
    AST_EXPR_MOD,    /**< % */
    AST_EXPR_SHL,    /**< << */
    AST_EXPR_SHR,    /**< >> */
    AST_EXPR_BITAND, /**< & */
    AST_EXPR_BITOR,  /**< | */
    AST_EXPR_BITXOR, /**< ^ */
    AST_EXPR_EQ,     /**< == */
    AST_EXPR_NE,     /**< != */
    AST_EXPR_LT,     /**< < */
    AST_EXPR_LE,     /**< <= */
    AST_EXPR_GT,     /**< > */
    AST_EXPR_GE,     /**< >= */
    AST_EXPR_LOGAND, /**< && */
    AST_EXPR_LOGOR,  /**< || */
    AST_EXPR_NEG,    /**< 一元 - */
    AST_EXPR_BITNOT, /**< 一元 ~ */
    AST_EXPR_LOGNOT, /**< 一元 ! */
    AST_EXPR_IF,     /**< if cond { then_expr } else { else_expr }（条件表达式） */
    AST_EXPR_BREAK,   /**< break（仅允许在循环体内） */
    AST_EXPR_CONTINUE,/**< continue（仅允许在循环体内） */
    AST_EXPR_RETURN,  /**< return expr（显式返回，仅允许在函数体内） */
    AST_EXPR_PANIC,   /**< panic 或 panic(expr)，终止程序；可选消息表达式 */
    AST_EXPR_MATCH,   /**< match expr { lit|_ => expr ; ... }，最小形式仅整数字面量与 _ */
    AST_EXPR_FIELD_ACCESS, /**< 字段访问 base.field（base 为表达式，field 为字段名） */
    AST_EXPR_STRUCT_LIT,   /**< 结构体字面量 TypeName { field: expr, ... } */
    AST_EXPR_ARRAY_LIT,    /**< 数组字面量 [e1, e2, ...]（文档 §6.2） */
    AST_EXPR_INDEX         /**< 下标访问 base[index] */
} ASTExprKind;

/** match 单分支：字面量或 _ => 表达式（arms 由 ast_module_free 路径释放） */
typedef struct ASTMatchArm {
    int is_wildcard;  /**< 1 表示 _ 分支，0 表示整数字面量 */
    int lit_val;      /**< 字面量值（is_wildcard 时忽略） */
    struct ASTExpr *result; /**< 该分支结果表达式 */
} ASTMatchArm;

/** 表达式节点（可递归；二元用 binop，一元用 unary，变量用 var，条件用 if_expr） */
typedef struct ASTExpr {
    ASTExprKind kind;
    union {
        int int_val;  /**< AST_EXPR_LIT 时的值 */
        struct {
            const char *name;  /**< AST_EXPR_VAR 时的名称（strdup，由 ast_expr_free 释放） */
        } var;
        struct {
            struct ASTExpr *left;
            struct ASTExpr *right;
        } binop;      /**< 所有二元运算的左右操作数 */
        struct {
            struct ASTExpr *operand;  /**< 一元运算的子表达式 */
        } unary;
        struct {
            struct ASTExpr *cond;       /**< AST_EXPR_IF 条件 */
            struct ASTExpr *then_expr;  /**< then 分支表达式 */
            struct ASTExpr *else_expr;  /**< else 分支表达式（可为 NULL，生成时按 0 处理） */
        } if_expr;
        struct {
            struct ASTExpr *matched_expr;  /**< match 的待匹配表达式 */
            struct ASTMatchArm *arms;     /**< 分支数组 */
            int num_arms;
        } match_expr;
        struct {
            struct ASTExpr *base;    /**< AST_EXPR_FIELD_ACCESS 的基表达式（如变量或另一字段访问） */
            char *field_name;        /**< 字段名（strdup，由 ast_expr_free 释放） */
        } field_access;
        struct {
            char *struct_name;        /**< 结构体类型名（strdup，由 ast_expr_free 释放） */
            char **field_names;       /**< 字段名数组（strdup，由 ast_expr_free 释放） */
            struct ASTExpr **inits;   /**< 各字段初始化表达式指针数组（与 field_names 一一对应） */
            int num_fields;
        } struct_lit;
        struct {
            struct ASTExpr **elems;   /**< AST_EXPR_ARRAY_LIT 元素表达式数组；由 ast_expr_free 释放 */
            int num_elems;
        } array_lit;
        struct {
            struct ASTExpr *base;     /**< AST_EXPR_INDEX 的数组或切片基表达式 */
            struct ASTExpr *index_expr; /**< 下标表达式（须为整数类型） */
            int base_is_slice;        /**< 1 表示基类型为切片 []T，codegen 生成 base.data[i]；0 表示数组，生成 base[i] */
        } index;
    } value;
} ASTExpr;

/** 块内语句类型：goto 或 return（在 final_expr 前出现） */
typedef enum ASTStmtKind {
    AST_STMT_GOTO,
    AST_STMT_RETURN
} ASTStmtKind;

/** 带可选 label 的语句（label 为 NULL 表示无标签） */
typedef struct ASTLabeledStmt {
    char *label;  /**< 标签名，NULL 表示无标签；strdup，由 ast_block_free 释放 */
    ASTStmtKind kind;
    union {
        char *goto_target;            /**< AST_STMT_GOTO 时目标标签名 */
        struct ASTExpr *return_expr;   /**< AST_STMT_RETURN 时返回值表达式 */
    } u;
} ASTLabeledStmt;

/** 结构体字段：名称、类型（与 analysis/变量类型与类型系统设计.md §6.1 一致） */
typedef struct ASTStructField {
    char *name;           /**< 字段名（strdup，由 ast_struct_def_free 释放） */
    struct ASTType *type; /**< 字段类型，不可为 NULL */
} ASTStructField;

/** 单结构体最大字段数（与 parser 一致），用于布局偏移数组 */
#define AST_STRUCT_MAX_FIELDS 32

/** 结构体定义：名称与字段列表（顶层定义，由 ast_module_free 释放）。布局由 typeck 按 §11.1 计算后填充。 */
typedef struct ASTStructDef {
    char *name;                  /**< 结构体类型名（strdup） */
    ASTStructField *fields;      /**< 字段数组 */
    int num_fields;
    /** 以下由 typeck 结构体布局 pass 填充（变量类型与类型系统设计 §11.1） */
    int field_offsets[AST_STRUCT_MAX_FIELDS]; /**< 各字段偏移（字节），未计算时为 0 */
    int struct_size;   /**< 结构体总大小（字节），含末尾对齐；未计算时为 0 */
    int struct_align;  /**< 结构体对齐要求（字节）；未计算时为 0 */
} ASTStructDef;

/** 常量声明：名称、类型（可选，如 "i32"）、初始化表达式（须为常量表达式） */
typedef struct ASTConstDecl {
    const char *name;
    struct ASTType *type;   /**< 可为 NULL 表示省略，当前子集仅若干内建整数/布尔及具名类型 */
    struct ASTExpr *init;
} ASTConstDecl;

/** 变量声明：名称、类型、初始化表达式 */
typedef struct ASTLetDecl {
    const char *name;
    struct ASTType *type;   /**< 如 i32/bool/u8 等，或用户自定义类型名 */
    struct ASTExpr *init;
} ASTLetDecl;

/** 单条 while 循环：条件 + 体块（体块内无嵌套 while） */
typedef struct ASTWhileLoop {
    struct ASTExpr *cond;   /**< 条件表达式 */
    struct ASTBlock *body;  /**< 循环体块（const/let + final_expr） */
} ASTWhileLoop;

/** 单条 for 循环：init/cond/step 均可为 NULL（cond 空表示恒真） */
typedef struct ASTForLoop {
    struct ASTExpr *init;   /**< 初始化表达式，可为 NULL */
    struct ASTExpr *cond;   /**< 条件表达式，可为 NULL 表示 true */
    struct ASTExpr *step;   /**< 步进表达式，可为 NULL */
    struct ASTBlock *body;  /**< 循环体块 */
} ASTForLoop;

/** 块：const/let + while/for + defer 块列表 + 可选 label/goto/return 语句 + 最终表达式 */
typedef struct ASTBlock {
    ASTConstDecl *const_decls;
    int num_consts;
    ASTLetDecl *let_decls;
    int num_lets;
    ASTWhileLoop *loops;    /**< while/loop 循环列表，可为 NULL */
    int num_loops;
    ASTForLoop *for_loops;   /**< for 循环列表，可为 NULL */
    int num_for_loops;
    struct ASTBlock **defer_blocks;  /**< defer { block } 列表，块退出时逆序执行；可为 NULL */
    int num_defers;
    ASTLabeledStmt *labeled_stmts;  /**< label: / goto / return 语句序列，可为 NULL */
    int num_labeled_stmts;
    struct ASTExpr *final_expr;
} ASTBlock;

/** 函数节点：name、返回类型、体为块（含 const/let + 最终表达式） */
typedef struct ASTFunc {
    const char *name;
    struct ASTType *return_type;
    ASTBlock *body;    /**< 函数体（块）；不可为 NULL（main 至少含 final_expr） */
} ASTFunc;

/** 模块/程序：阶段 1–2 仅含一个 main；阶段 5 支持顶层 import；阶段 4–5 支持顶层 struct 定义 */
typedef struct ASTModule {
    /** import 路径列表，如 "core.types"；由 parser 分配，ast_module_free 释放 */
    char **import_paths;
    int num_imports;       /**< import_paths 有效长度 */
    ASTStructDef **struct_defs; /**< 顶层结构体定义指针数组，可为 NULL；由 ast_module_free 逐项释放后 free 本数组 */
    int num_structs;
    ASTFunc *main_func;    /**< 顶层 main 函数，库模块可为 NULL */
} ASTModule;

/**
 * 释放单条结构体定义（字段名、类型及自身）；由 ast_module_free 内部调用。
 * 参数：s 待释放的结构体定义；可为 NULL。
 */
void ast_struct_def_free(ASTStructDef *s);

/**
 * 释放 AST 模块及其子节点。
 *
 * 功能说明：递归释放模块内 import_paths、struct_defs、main_func（含 name/return_type/body）及模块自身；用于 Parser/Driver 在解析或编译结束后回收内存。
 * 参数：m 待释放的模块指针；可为 NULL，此时无操作。
 * 返回值：无。
 * 错误与边界：m 为 NULL 时安全返回；m 及其子节点不得在调用后再次使用（use-after-free）。
 * 副作用与约定：会 free 所有 Parser 通过 strndup/strdup 分配的名称与类型字符串；调用方不得再对 m->import_paths[i]、m->main_func->name 等做 free。
 */
void ast_module_free(ASTModule *m);

/**
 * 释放块（const/let 声明及 final_expr）；由 ast_module_free 内部调用。
 * 参数：b 待释放的块；可为 NULL。副作用：递归释放所有声明中的 name/type/init 及 final_expr。
 */
void ast_block_free(ASTBlock *b);

/**
 * 释放单棵表达式树（递归释放二元/一元/VAR 等）。
 * 功能说明：用于 Parser 构建的 body 等表达式；ASTModule 释放时通过 ast_module_free 内部调用，也可由调用方在仅持有 ASTExpr* 时使用。
 * 参数：e 待释放的表达式根节点；可为 NULL，此时无操作。
 * 返回值：无。
 * 错误与边界：e 及所有子节点不得在调用后再次使用。
 * 副作用与约定：递归 free 所有子节点；AST_EXPR_VAR 时 free value.var.name（Parser 侧 strdup）。
 */
void ast_expr_free(ASTExpr *e);

/**
 * 释放类型节点；若为 AST_TYPE_NAMED 会 free 其中的 name，其它种类仅 free 节点本身。
 * 参数：t 待释放的类型节点；可为 NULL。
 */
void ast_type_free(ASTType *t);

#endif /* SHUC_AST_H */
