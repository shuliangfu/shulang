/**
 * typeck.h — 类型检查接口
 *
 * 文件职责：声明对 AST 模块做类型检查的入口 typeck_module，供 Driver 在 parse 之后、codegen 之前调用。
 * 所属模块：编译器前端 typeck，compiler/src/typeck/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/codegen。
 * 重要约定：阶段 3 最小子集仅校验「有 main 则返回 i32、体为整数字面量」；库模块（无 main）直接通过。类型错误时向 stderr 输出并返回 -1。
 */

#ifndef SHU_TYPECK_H
#define SHU_TYPECK_H

struct ASTModule;

/**
 * 对模块做类型检查。
 * 功能说明：若有 main 则校验返回类型为 i32、体为整数字面量；无 main 的库模块视为通过。若提供 dep_mods，则 CALL 可在依赖模块中解析（跨模块调用）。
 * 参数：m 已解析的 AST 模块；dep_mods 直接依赖模块数组（与 m->import_paths 顺序一致），可为 NULL；num_deps 直接依赖个数。
 *       all_dep_mods/n_all_deps 可选：全部传递依赖，用于结构体布局阶段解析跨模块类型（如 parser 内 OneFuncResult.next_lex: Lexer）；为 NULL/0 时仅用 dep_mods。
 * 返回值：0 通过；-1 类型错误且已向 stderr 输出 "typeck error: ..."。
 * 副作用与约定：只读 m 与 dep_mods；会写 m 中 CALL 节点的 resolved_import_path、resolved_callee_func。
 */
int typeck_module(struct ASTModule *m, struct ASTModule **dep_mods, int num_deps, struct ASTModule **all_dep_mods, int n_all_deps);

/**
 * 仅对模块中指定下标的函数做体块类型检查（布局与顶层 let 仍会执行）；用于 LSP definition/hover 懒 typeck。
 * only_func_index >= 0 且 < m->num_funcs 时只 typeck 该函数；否则无操作返回 0。
 */
int typeck_one_function(struct ASTModule *m, struct ASTModule **dep_mods, int num_deps, struct ASTModule **all_dep_mods, int n_all_deps, int only_func_index);

/**
 * 以下为 .su typeck 入口使用的 AST 查询 API（全面自举：typeck 逻辑迁入 .su）。
 * 参数均以 void* 传递以与 .su 的 *u8 一致；内部转为具体 AST 类型后访问。
 */
void *typeck_su_get_main_func(void *mod);
int typeck_su_func_return_kind(void *func);
int typeck_su_func_is_extern(void *func);
int typeck_su_func_has_body(void *func);
int typeck_su_func_is_generic(void *func);
void *typeck_su_func_body(void *func);
int typeck_su_block_has_implicit_return(const void *block);
int typeck_su_ast_type_i32(void);
int typeck_su_ast_type_i64(void);
int typeck_su_ast_type_bool(void);

/** 全面自举（重写）：仅填 resolved_type，不做语义检查；.su 用访问器遍历并做检查。 */
int typeck_su_fill_resolved_types(void *mod, void *dep_mods, int num_deps);

/** 块/表达式访问器：.su 中实现遍历与「条件须为 bool」等判断。 */
int typeck_su_block_num_loops(const void *block);
void *typeck_su_block_loop_cond(const void *block, int i);
void *typeck_su_block_loop_body(const void *block, int i);
int typeck_su_block_num_for_loops(const void *block);
void *typeck_su_block_for_cond(const void *block, int i);
void *typeck_su_block_for_body(const void *block, int i);
int typeck_su_expr_type_kind(const void *expr);

/** 块内表达式语句与最终表达式：.su 遍历 if/三元 所在表达式。 */
int typeck_su_block_num_expr_stmts(const void *block);
void *typeck_su_block_expr_stmt(const void *block, int i);
void *typeck_su_block_final_expr(const void *block);

/** 表达式节点 kind（ASTExprKind）；供 .su 判断是否为 IF/TERNARY/BLOCK 并递归。 */
int typeck_su_expr_kind(const void *expr);
void *typeck_su_expr_if_cond(const void *expr);
void *typeck_su_expr_if_then(const void *expr);
void *typeck_su_expr_if_else(const void *expr);
void *typeck_su_expr_block(const void *expr);
int typeck_su_expr_kind_if(void);
int typeck_su_expr_kind_ternary(void);
int typeck_su_expr_kind_block(void);
int typeck_su_expr_kind_assign(void);
void *typeck_su_expr_assign_left(const void *expr);
void *typeck_su_expr_assign_right(const void *expr);
/** 两表达式 resolved_type 是否一致（C 的 type_equal）；供 .su 做赋值类型一致检查。 */
int typeck_su_types_equal(const void *expr_a, const void *expr_b);

/** .su 自实现 typeck 用：块体结果类型是否与函数返回类型一致，返回 1 一致 0 否。 */
int typeck_su_block_result_matches_func_return(const void *func, const void *block);

/** .su 自实现 typeck 用：块内 const/let 个数及「声明类型与初值类型一致」检查。 */
int typeck_su_block_num_consts(const void *block);
int typeck_su_block_num_lets(const void *block);
int typeck_su_block_const_type_matches_init(const void *block, int i);
int typeck_su_block_let_type_matches_init(const void *block, int i);

/** 模块/impl 访问器：.su 遍历所有函数及其 body。 */
int typeck_su_module_num_funcs(const void *mod);
void *typeck_su_module_func(const void *mod, int i);
int typeck_su_module_num_impl_blocks(const void *mod);
int typeck_su_impl_block_num_funcs(const void *mod, int k);
void *typeck_su_impl_block_func(const void *mod, int k, int j);

/** double 的 64 位位模式拆成低/高 32 位，供 .su typeck 填写 EXPR_FLOAT_LIT 的 float_bits_lo/hi（asm 后端用）。 */
int typeck_float64_bits_lo(double d);
int typeck_float64_bits_hi(double d);

#endif /* SHU_TYPECK_H */
