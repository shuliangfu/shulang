/**
 * codegen.c — 代码生成实现（AST → C）
 *
 * 文件职责：实现 codegen.h 声明的 codegen_module_to_c 与 codegen_library_module_to_c，将 AST 转为 C 源码供系统 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；实现 codegen.h。
 * 与其它文件的关系：依赖 include/ast.h；被 main 在 typeck 通过后调用；输出到 main 提供的临时文件流。
 * 重要约定：入口模块仅支持 main；生成 Hello World 的 printf，且 return 使用 main 体整数字面量的值（阶段 4 方案 B 扩展）；库模块仅输出注释（阶段 7.3 多文件占位）。
 */

#include "codegen/codegen.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#ifdef SHUC_USE_SU_CODEGEN
/** .su 侧整数字面量格式化入口：向 out（FILE* 不透明）逐字节输出 val 的十进制表示；由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_format_int_lit(uint8_t *out, int32_t val);
/** .su 侧布尔字面量输出：向 out 输出 '0' 或 '1'（val 非 0 为 1）；由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_format_bool_lit(uint8_t *out, int32_t val);
/** .su 侧 C 字符串输出：向 out 逐字节输出 ptr[0..len-1]；由 codegen.su 实现，用于 VAR 变量名等。 */
extern int32_t codegen_codegen_su_emit_c_string(uint8_t *out, uint8_t *ptr, int32_t len);
/** .su 侧浮点字面量输出：ptr 指向 double，is_f32 非 0 为 f32；由 codegen.su 转调 C 的 codegen_su_emit_float。 */
extern int32_t codegen_codegen_su_emit_float_lit(uint8_t *out, uint8_t *ptr, int32_t is_f32);
/** .su 侧二元运算输出：左/右子表达式与运算符串；need_l/need_r 非 0 时在对应子表达式外加括号。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_binop(uint8_t *out, uint8_t *left, uint8_t *right, uint8_t *op_ptr, int32_t op_len, int32_t need_l, int32_t need_r);
/** .su 侧一元运算输出：左括号+前缀串、子表达式、右括号。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_unary(uint8_t *out, uint8_t *operand, uint8_t *prefix_ptr, int32_t prefix_len);
/** .su 侧赋值表达式输出：( left = right )。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_assign(uint8_t *out, uint8_t *left, uint8_t *right);
/** .su 侧 DIV 表达式：is_int 非 0 时走整数除零检查，否则为浮点 /。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_div_expr(uint8_t *out, uint8_t *left, uint8_t *right, int32_t is_int);
/** .su 侧 MOD 表达式：is_int 非 0 时走整数取模零检查，否则为浮点 %。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_mod_expr(uint8_t *out, uint8_t *left, uint8_t *right, int32_t is_int);
/** .su 侧三元表达式内层：cond、op_q（" ? "）、then_e、op_c（" : "）、else_e；C 外包括号。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_ternary_inner(uint8_t *out, uint8_t *cond, uint8_t *then_e, uint8_t *else_e, uint8_t *op_q, int32_t len_q, uint8_t *op_c, int32_t len_c);
/** .su 侧字段访问统一入口：枚举变体走 C 的 full，结构体字段走 .su 的 (base).field。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_field_access_expr(uint8_t *out, uint8_t *expr);
/** .su 侧函数调用统一入口：按 dispatch 调 C 的 import/library_same/library_dep/mono full 或 fallback callee(args)。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_call_expr(uint8_t *out, uint8_t *expr);
/** .su 侧 panic 输出：has_operand 非 0 时 shulang_panic_(1, operand)，否则 shulang_panic_(0, 0)。由 codegen.su 转调 C 的 codegen_su_emit_panic_*。 */
extern int32_t codegen_codegen_su_emit_panic(uint8_t *out, int32_t has_operand, uint8_t *operand);
/** .su 侧下标 fallback：(base)[index] 或 (base).data[index]。is_slice 非 0 为 .data 形式。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_index_fallback(uint8_t *out, uint8_t *base, uint8_t *index, int32_t is_slice);
/** .su 侧块表达式：输出 ({  + block_body +  0; })；C 提供 codegen_su_block_body。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_block_expr(uint8_t *out, uint8_t *block);
/** .su 侧方法调用：c_name(base, arg0, ...)；C 提供 method_call 访问器。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_method_call(uint8_t *out, uint8_t *expr);
/** .su 侧下标完整：按类型/BCE 分发到 fallback 或边界检查；C 提供 index 访问器与 slice/array bounds 输出。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_index(uint8_t *out, uint8_t *expr);
/** .su 侧 match：switch 或三元链；C 提供 match 访问器与 next_id。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_match(uint8_t *out, uint8_t *expr);
/** .su 侧结构体字面量：入口在 .su，转调 C 的 codegen_su_emit_struct_lit_full。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_struct_lit(uint8_t *out, uint8_t *expr);
/** .su 侧数组字面量：入口在 .su，转调 C 的 codegen_su_emit_array_lit_full。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_array_lit(uint8_t *out, uint8_t *expr);
/** .su 侧 if 表达式：语句表达式或三元；入口在 .su，转调 C 的 codegen_su_emit_if_expr_full。由 codegen.su 实现。 */
extern int32_t codegen_codegen_su_emit_if_expr(uint8_t *out, uint8_t *expr);
/** .su 侧单条 while 循环输出：indent + while ( cond ) { body }。 */
extern int32_t codegen_codegen_su_emit_one_while_loop(uint8_t *out, uint8_t *cond, uint8_t *body, int32_t indent, int32_t cast_return);
/** .su 侧单条 for 循环输出：indent + for ( init; cond 或 1; step ) { body }。 */
extern int32_t codegen_codegen_su_emit_one_for_loop(uint8_t *out, uint8_t *init, uint8_t *cond, uint8_t *step, uint8_t *body, int32_t indent, int32_t cast_return);
/** .su 侧语句输出：continue;/break;/return;/return expr;/(void)(expr); */
extern int32_t codegen_codegen_su_emit_continue_stmt(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_break_stmt(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_return_no_val(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_return_expr(uint8_t *out, int32_t indent, uint8_t *expr);
extern int32_t codegen_codegen_su_emit_void_expr_stmt(uint8_t *out, int32_t indent, uint8_t *expr);
/** .su 侧 label 输出：indent + label 字符串（ptr[0..len-1]）+ ":\n"。 */
extern int32_t codegen_codegen_su_emit_label(uint8_t *out, int32_t indent, uint8_t *label_ptr, int32_t label_len);
/** .su 侧 goto 输出：indent + "goto " + target 字符串 + ";\n"。 */
extern int32_t codegen_codegen_su_emit_goto(uint8_t *out, int32_t indent, uint8_t *target_ptr, int32_t target_len);
/** .su 侧 cleanup 相关：goto shulang_cleanup; / shulang_cleanup: / exit_kind=1; goto cleanup / ret_val=0; exit_kind=1; goto cleanup / if(exit_kind) return ret_val; / 声明 exit_kind / 声明 ret_val。 */
extern int32_t codegen_codegen_su_emit_goto_shulang_cleanup(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_shulang_cleanup_label(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_exit_kind_goto_cleanup(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_ret_val_zero_exit_goto_cleanup(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_if_exit_kind_return_ret_val(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_cleanup_decl_exit_kind(uint8_t *out, int32_t indent);
extern int32_t codegen_codegen_su_emit_cleanup_decl_ret_val(uint8_t *out, int32_t indent, uint8_t *ret_ctype_ptr, int32_t ret_ctype_len);
/** .su 侧 defer 逆序执行：对 block 的 num_defers 从高到低依次输出各 defer 块体。 */
extern int32_t codegen_codegen_su_run_defers(uint8_t *out, uint8_t *block, int32_t indent);
/** .su 侧块 const/let 声明批量输出：const_decls 全量；let_decls 按 [start,end) 区间。 */
extern int32_t codegen_codegen_su_emit_block_const_decls(uint8_t *out, uint8_t *block, int32_t indent);
extern int32_t codegen_codegen_su_emit_block_let_decls_range(uint8_t *out, uint8_t *block, int32_t indent, int32_t start, int32_t end);
#endif
/** .su 侧通过 extern 调用的写单字节接口；out 为 FILE* 的不透明指针，b 为要输出的字节（0..255）。返回 0 成功，非 0 失败。始终编译进 codegen.o 以便 bootstrap-codegen 链接时解析。 */
int32_t codegen_su_emit_byte(uint8_t *out, int32_t b) {
    int c = (unsigned char)(b & 0xff);
    return (fputc(c, (FILE *)out) == c) ? 0 : -1;
}
/** .su 侧通过 extern 调用的读单字节接口：返回 ptr[i] 的 0..255 值，供 .su 逐字节输出 C 字符串用。 */
int32_t codegen_su_char_at(uint8_t *ptr, int32_t i) {
    return (int32_t)(unsigned char)ptr[i];
}
/** .su 侧通过 extern 调用的浮点字面量输出：ptr 指向 double，is_f32 非 0 时输出 f32 后缀；0.0 输出 "0.0"/"0.0f"，否则 %g/%gf。返回 0 成功。 */
int32_t codegen_su_emit_float(uint8_t *out, uint8_t *ptr, int32_t is_f32) {
    double v;
    memcpy(&v, ptr, sizeof(double));
    if (v == 0.0)
        fprintf((FILE *)out, is_f32 ? "0.0f" : "0.0");
    else if (is_f32)
        fprintf((FILE *)out, "%gf", v);
    else
        fprintf((FILE *)out, "%g", v);
    return 0;
}

static int codegen_expr(const struct ASTExpr *e, FILE *out);
static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out, int cast_return_to_int, const char *final_result_var);
/** 当 else 为单语句块且唯一语句为 __tmp = (struct X){0} 时返回该 struct 的 C 类型串，否则 NULL。前向声明。 */
static const char *struct_type_from_else_block(const struct ASTExpr *else_e);
/** 返回结构体字面量 e 的 C 类型串，与 codegen 发射时一致；前向声明。 */
static const char *struct_lit_c_type_str(const struct ASTExpr *e, char *buf, size_t bufsize);
/** 递归求表达式可能产生的 struct 类型 C 串；前向声明。 */
static const char *expr_struct_type_str(const struct ASTExpr *e, char *buf, size_t bufsize);
static const char *impl_method_c_name(const struct ASTFunc *f);
/** CALL 四条分支的 C 内实现，供 .su 统一入口转调；需在 codegen_expr 之后定义。 */
static int codegen_emit_one_call_arg(FILE *out, const struct ASTExpr *arg);
static int codegen_emit_call_import_path_impl(FILE *out, const struct ASTExpr *e);
static int codegen_emit_call_library_same_impl(FILE *out, const struct ASTExpr *e);
static int codegen_emit_call_library_dep_impl(FILE *out, const struct ASTExpr *e);
static int codegen_emit_call_mono_impl(FILE *out, const struct ASTExpr *e);
/** 用于生成唯一 match 临时变量名；需在 codegen_su_match_next_id 前可见。 */
static int codegen_match_id;

/** .su 侧通过 extern 调用的“输出整棵表达式”接口：递归调用 codegen_expr，供 .su 在二元运算等中输出子表达式。返回 0 成功，-1 失败。 */
int32_t codegen_su_emit_expr(uint8_t *out, uint8_t *expr) {
    return (int32_t)codegen_expr((const struct ASTExpr *)expr, (FILE *)out);
}
/** .su 侧判断子表达式是否需加括号（比较/逻辑运算符作为加减操作数时）：kind 在 [AST_EXPR_EQ, AST_EXPR_LOGOR] 返回 1。 */
int32_t codegen_su_expr_needs_compare_parens(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind >= AST_EXPR_EQ && e->kind <= AST_EXPR_LOGOR) ? 1 : 0;
}
/** .su 侧判断子表达式是否需加括号（加减作为乘除操作数时）：kind 为 ADD 或 SUB 返回 1。 */
int32_t codegen_su_expr_needs_addsub_parens(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && (e->kind == AST_EXPR_ADD || e->kind == AST_EXPR_SUB)) ? 1 : 0;
}
/** .su 侧 CALL 访问器：返回 callee 子表达式指针。 */
uint8_t *codegen_su_call_callee(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_CALL && e->value.call.callee) ? (uint8_t *)e->value.call.callee : NULL;
}
/** .su 侧 CALL 访问器：返回实参个数。 */
int32_t codegen_su_call_num_args(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_CALL) ? (int32_t)e->value.call.num_args : 0;
}
/** .su 侧 CALL 访问器：返回第 i 个实参表达式指针，i 从 0 起。 */
uint8_t *codegen_su_call_arg(uint8_t *expr, int32_t i) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL || !e->value.call.args || i < 0 || i >= e->value.call.num_args) return NULL;
    return (uint8_t *)e->value.call.args[i];
}
/** .su 侧 panic 无参：输出 shulang_panic_(0, 0)。 */
int32_t codegen_su_emit_panic_no_arg(uint8_t *out) {
    return fprintf((FILE *)out, "shulang_panic_(0, 0)") < 0 ? -1 : 0;
}
/** .su 侧 panic 有参：输出 shulang_panic_(1, expr)。 */
int32_t codegen_su_emit_panic_with_arg(uint8_t *out, uint8_t *operand) {
    if (fprintf((FILE *)out, "shulang_panic_(1, ") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)operand, (FILE *)out) != 0) return -1;
    return fprintf((FILE *)out, ")") < 0 ? -1 : 0;
}
/** .su 侧块体输出（无 final_result_var）：块表达式用，传 NULL 给 codegen_block_body。 */
int32_t codegen_su_block_body_no_result(uint8_t *out, uint8_t *block, int32_t indent, int32_t cast_return_to_int) {
    return codegen_block_body((const struct ASTBlock *)block, (int)indent, (FILE *)out, (int)cast_return_to_int, NULL) != 0 ? -1 : 0;
}
/** .su 侧块体输出（带 final_result_var "__tmp"）：供 if 语句表达式 then/else 块用。 */
int32_t codegen_su_block_body_with_result_var(uint8_t *out, uint8_t *block, int32_t indent, int32_t cast_return_to_int) {
    return codegen_block_body((const struct ASTBlock *)block, (int)indent, (FILE *)out, (int)cast_return_to_int, "__tmp") != 0 ? -1 : 0;
}
/** .su 侧块 defer 访问器：块内 defer 数量；供 run_defers 逆序遍历。 */
int32_t codegen_su_block_num_defers(uint8_t *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return (b && b->defer_blocks) ? (int32_t)b->num_defers : 0;
}
/** .su 侧块 defer 访问器：第 i 个 defer 子块（i 从 0 到 num_defers-1）；逆序时从 num_defers-1 到 0。 */
uint8_t *codegen_su_block_defer_block(uint8_t *block, int32_t i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->defer_blocks || i < 0 || i >= b->num_defers) return NULL;
    return (uint8_t *)b->defer_blocks[i];
}
/** .su 侧块 const/let 访问器：数量与 early_lets 分界，供 .su 循环输出声明。 */
int32_t codegen_su_block_num_consts(uint8_t *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? (int32_t)b->num_consts : 0;
}
int32_t codegen_su_block_num_lets(uint8_t *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? (int32_t)b->num_lets : 0;
}
int32_t codegen_su_block_num_early_lets(uint8_t *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || b->num_early_lets <= 0 || b->num_early_lets > b->num_lets) return 0;
    return (int32_t)b->num_early_lets;
}
/** .su 用：stmt_order 条数；>0 时 .su 按序输出 const/let/expr_stmt/loop/for。 */
int32_t codegen_su_block_num_stmt_order(uint8_t *block) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    return b ? (int32_t)b->num_stmt_order : 0;
}
/** .su 用：第 i 条 stmt_order 的 kind：0=const, 1=let, 2=expr_stmt, 3=loop, 4=for。 */
int32_t codegen_su_block_stmt_order_kind(uint8_t *block, int32_t i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || i < 0 || i >= b->num_stmt_order) return -1;
    return (int32_t)(unsigned char)b->stmt_order[i].kind;
}
/** .su 用：第 i 条 stmt_order 的 idx（对应 const_decls/let_decls/expr_stmts/loops/for_loops 下标）。 */
int32_t codegen_su_block_stmt_order_idx(uint8_t *block, int32_t i) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || i < 0 || i >= b->num_stmt_order) return -1;
    return b->stmt_order[i].idx;
}
/** .su 用：块内第 idx 条表达式语句（expr_stmts[idx]），供 emit_void_expr_stmt 等。 */
uint8_t *codegen_su_block_expr_stmt(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->expr_stmts || idx < 0 || idx >= b->num_expr_stmts) return NULL;
    return (uint8_t *)b->expr_stmts[idx];
}
/** .su 用：块内第 idx 条 while 的 cond/body。 */
uint8_t *codegen_su_block_loop_cond(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->loops || idx < 0 || idx >= b->num_loops) return NULL;
    return (uint8_t *)b->loops[idx].cond;
}
uint8_t *codegen_su_block_loop_body(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->loops || idx < 0 || idx >= b->num_loops) return NULL;
    return (uint8_t *)b->loops[idx].body;
}
/** .su 用：块内第 idx 条 for 的 init/cond/step/body。 */
uint8_t *codegen_su_block_for_init(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || idx < 0 || idx >= b->num_for_loops) return NULL;
    return (uint8_t *)b->for_loops[idx].init;
}
uint8_t *codegen_su_block_for_cond(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || idx < 0 || idx >= b->num_for_loops) return NULL;
    return (uint8_t *)b->for_loops[idx].cond;
}
uint8_t *codegen_su_block_for_step(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || idx < 0 || idx >= b->num_for_loops) return NULL;
    return (uint8_t *)b->for_loops[idx].step;
}
uint8_t *codegen_su_block_for_body(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->for_loops || idx < 0 || idx >= b->num_for_loops) return NULL;
    return (uint8_t *)b->for_loops[idx].body;
}
/** .su 侧 METHOD_CALL：返回 impl 方法的 C 名（Trait_Type_method）指针；非 method_call 或未解析返回 NULL。 */
uint8_t *codegen_su_method_call_c_name_ptr(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_METHOD_CALL || !e->value.method_call.resolved_impl_func) return NULL;
    return (uint8_t *)impl_method_c_name(e->value.method_call.resolved_impl_func);
}
/** .su 侧 METHOD_CALL：返回 C 名长度（strlen）。 */
int32_t codegen_su_method_call_c_name_len(uint8_t *expr) {
    const char *p = (const char *)codegen_su_method_call_c_name_ptr(expr);
    return p ? (int32_t)strlen(p) : 0;
}
/** .su 侧 METHOD_CALL：base、num_args、第 i 个实参。 */
uint8_t *codegen_su_method_call_base(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.base) ? (uint8_t *)e->value.method_call.base : NULL; }
int32_t codegen_su_method_call_num_args(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_METHOD_CALL) ? (int32_t)e->value.method_call.num_args : 0; }
uint8_t *codegen_su_method_call_arg(uint8_t *expr, int32_t i) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_METHOD_CALL || !e->value.method_call.args || i < 0 || i >= e->value.method_call.num_args) return NULL;
    return (uint8_t *)e->value.method_call.args[i];
}
/** .su 侧 INDEX：base、index、base_is_slice、skip_bounds；base 的 resolved_type kind 与 array_size。 */
uint8_t *codegen_su_index_base(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_INDEX && e->value.index.base) ? (uint8_t *)e->value.index.base : NULL; }
uint8_t *codegen_su_index_index(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_INDEX && e->value.index.index_expr) ? (uint8_t *)e->value.index.index_expr : NULL; }
int32_t codegen_su_index_base_is_slice(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_INDEX && e->value.index.base_is_slice) ? 1 : 0; }
int32_t codegen_su_index_skip_bounds(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_INDEX && e->index_proven_in_bounds) ? 1 : 0; }
/** .su 侧 FIELD_ACCESS：base 表达式、字段名指针、字段名长度（strlen），供 .su 输出 (base).field。 */
uint8_t *codegen_su_field_access_base(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_FIELD_ACCESS && e->value.field_access.base) ? (uint8_t *)e->value.field_access.base : NULL; }
uint8_t *codegen_su_field_access_field_name(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_FIELD_ACCESS && e->value.field_access.field_name) ? (uint8_t *)e->value.field_access.field_name : (uint8_t *)""; }
int32_t codegen_su_field_access_field_len(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; const char *fn = (e && e->kind == AST_EXPR_FIELD_ACCESS && e->value.field_access.field_name) ? e->value.field_access.field_name : ""; return (int32_t)strlen(fn); }
/** .su 侧 FIELD_ACCESS：base 是否为指针或 slice 类型（1 则输出 ->，0 则输出 .）；C 中 slice 按指针传，自举时 arena/source/out_buf.field 需生成 ->。 */
int32_t codegen_su_field_access_base_is_pointer(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_FIELD_ACCESS || !e->value.field_access.base) return 0;
    const struct ASTExpr *base = e->value.field_access.base;
    if (!base->resolved_type) return 0;
    if (base->resolved_type->kind == AST_TYPE_PTR) return 1;
    if (base->resolved_type->kind == AST_TYPE_SLICE) return 1;
    return 0;
}
int32_t codegen_su_expr_type_kind(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->resolved_type) ? (int32_t)e->resolved_type->kind : -1; }
int32_t codegen_su_expr_type_array_size(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->resolved_type && e->resolved_type->kind == AST_TYPE_ARRAY) ? (int32_t)e->resolved_type->array_size : 0; }
/** .su 侧 INDEX 数组边界检查：((idx)<0||(idx)>=N ? (shulang_panic_(1,0),(base)[0]) : (base)[(idx)])。 */
int32_t codegen_su_emit_index_array_bounds_check(uint8_t *out, uint8_t *base, uint8_t *idx, int32_t array_size) {
    FILE *f = (FILE *)out;
    if (fprintf(f, "(") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    if (fprintf(f, " < 0 || (") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    if (fprintf(f, ") >= %d ? (shulang_panic_(1, 0), (", (int)array_size) < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)base, f) != 0) return -1;
    if (fprintf(f, ")[0]) : (") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)base, f) != 0) return -1;
    if (fprintf(f, ")[") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    return fprintf(f, "])") < 0 ? -1 : 0;
}
/** .su 侧 MATCH：matched_expr、num_arms、arm is_wildcard/is_enum_variant/variant_index/lit_val/result；use_switch(expr)、next_id()。 */
uint8_t *codegen_su_match_matched(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_MATCH && e->value.match_expr.matched_expr) ? (uint8_t *)e->value.match_expr.matched_expr : NULL; }
int32_t codegen_su_match_num_arms(uint8_t *expr) { const struct ASTExpr *e = (const struct ASTExpr *)expr; return (e && e->kind == AST_EXPR_MATCH) ? (int32_t)e->value.match_expr.num_arms : 0; }
int32_t codegen_su_match_arm_is_wildcard(uint8_t *expr, int32_t i) { const struct ASTExpr *e = (const struct ASTExpr *)expr; if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms || i < 0 || i >= e->value.match_expr.num_arms) return 0; return e->value.match_expr.arms[i].is_wildcard ? 1 : 0; }
int32_t codegen_su_match_arm_is_enum_variant(uint8_t *expr, int32_t i) { const struct ASTExpr *e = (const struct ASTExpr *)expr; if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms || i < 0 || i >= e->value.match_expr.num_arms) return 0; return e->value.match_expr.arms[i].is_enum_variant ? 1 : 0; }
int32_t codegen_su_match_arm_variant_index(uint8_t *expr, int32_t i) { const struct ASTExpr *e = (const struct ASTExpr *)expr; if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms || i < 0 || i >= e->value.match_expr.num_arms) return 0; return (int32_t)e->value.match_expr.arms[i].variant_index; }
int32_t codegen_su_match_arm_lit_val(uint8_t *expr, int32_t i) { const struct ASTExpr *e = (const struct ASTExpr *)expr; if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms || i < 0 || i >= e->value.match_expr.num_arms) return 0; return (int32_t)e->value.match_expr.arms[i].lit_val; }
uint8_t *codegen_su_match_arm_result(uint8_t *expr, int32_t i) { const struct ASTExpr *e = (const struct ASTExpr *)expr; if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms || i < 0 || i >= e->value.match_expr.num_arms) return NULL; return (uint8_t *)e->value.match_expr.arms[i].result; }
int32_t codegen_su_match_use_switch(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_MATCH || !e->value.match_expr.arms) return 0;
    int num_arms = e->value.match_expr.num_arms;
    const struct ASTMatchArm *arms = e->value.match_expr.arms;
    int value_min = INT_MAX, value_max = INT_MIN, lit_count = 0;
    for (int i = 0; i < num_arms; i++) {
        if (arms[i].is_wildcard) continue;
        int v = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
        lit_count++;
        if (v < value_min) value_min = v;
        if (v > value_max) value_max = v;
    }
    int range = (value_max >= value_min) ? (value_max - value_min + 1) : 0;
    double density = (range > 0 && lit_count > 0) ? (double)lit_count / (double)range : 0.0;
    return (density > 0.7 && lit_count > 0) ? 1 : 0;
}
int32_t codegen_su_match_next_id(void) { return (int32_t)codegen_match_id++; }

/** .su 侧整数除法输出（含除零检查）：( r==0 ? (shulang_panic_(1,0), l) : (l/r) )，l/r 按需加括号。 */
int32_t codegen_su_emit_int_div(uint8_t *out, uint8_t *left, uint8_t *right) {
    const struct ASTExpr *l = (const struct ASTExpr *)left, *r = (const struct ASTExpr *)right;
    FILE *f = (FILE *)out;
    int need_l = (l && (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB));
    int need_r = (r && (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB));
    fprintf(f, "(");
    if (need_r) fprintf(f, "(");
    if (codegen_expr(r, f) != 0) return -1;
    if (need_r) fprintf(f, ")");
    fprintf(f, " == 0 ? (shulang_panic_(1, 0), ");
    if (need_l) fprintf(f, "(");
    if (codegen_expr(l, f) != 0) return -1;
    if (need_l) fprintf(f, ")");
    fprintf(f, ") : (");
    if (need_l) fprintf(f, "(");
    if (codegen_expr(l, f) != 0) return -1;
    if (need_l) fprintf(f, ")");
    fprintf(f, " / ");
    if (need_r) fprintf(f, "(");
    if (codegen_expr(r, f) != 0) return -1;
    if (need_r) fprintf(f, ")");
    fprintf(f, "))");
    return 0;
}

/** .su 侧整数取模输出（含取模零检查）：( r==0 ? (shulang_panic_(1,0), l) : (l %% r) )。 */
int32_t codegen_su_emit_int_mod(uint8_t *out, uint8_t *left, uint8_t *right) {
    const struct ASTExpr *l = (const struct ASTExpr *)left, *r = (const struct ASTExpr *)right;
    FILE *f = (FILE *)out;
    fprintf(f, "(");
    if (codegen_expr(r, f) != 0) return -1;
    fprintf(f, " == 0 ? (shulang_panic_(1, 0), ");
    if (codegen_expr(l, f) != 0) return -1;
    fprintf(f, ") : (");
    if (codegen_expr(l, f) != 0) return -1;
    fprintf(f, " %% ");
    if (codegen_expr(r, f) != 0) return -1;
    fprintf(f, "))");
    return 0;
}

/** 当前生成所在模块（用于 CALL 时解析泛型调用的单态化实例名）；由 codegen_module_to_c 设置。 */
static const struct ASTModule *codegen_current_module;

/** 库模块 C 符号前缀（如 foo_、core_types_）；由 codegen_library_module_to_c 设置，生成时所有类型/函数名加此前缀。 */
static const char *codegen_library_prefix;
/** 库模块代码生成时指向当前模块，用于 NAMED 类型输出 "struct " 前缀（仅当前模块内定义的 struct）。 */
static const struct ASTModule *codegen_library_module;
/** 库模块 import 路径（如 std.process），用于 std.process.exit 等特殊函数体生成。 */
static const char *codegen_library_import_path;
/** 入口模块代码生成时的依赖模块与 import 路径，用于 NAMED 类型解析为 "struct prefix_Name"（依赖中的 struct）。 */
static struct ASTModule **codegen_dep_mods;
static const char **codegen_dep_paths;
static int codegen_ndep;

/** .su 侧 FIELD_ACCESS：是否为枚举变体输出路径（Type.Variant 或库模块枚举），非 0 时 .su 转调 emit_field_access_enum_variant_full。需在 codegen_library_prefix 等声明之后。 */
int32_t codegen_su_field_access_is_enum_variant(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_FIELD_ACCESS || !e->value.field_access.base) return 0;
    if (e->value.field_access.is_enum_variant && e->value.field_access.base->kind == AST_EXPR_VAR) return 1;
    if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs
        && e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
        const char *en2 = e->value.field_access.base->value.var.name;
        for (int i = 0; i < codegen_library_module->num_enums; i++)
            if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, en2) == 0)
                return 1;
    }
    return 0;
}

/** 单文件模式时已输出类型名集合（与 codegen_module_to_c/codegen_library_module_to_c 参数一致），供 ensure_slice_struct 去重 slice 结构体。 */
static char (*codegen_emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX];
static int *codegen_n_emitted_inout;
static int codegen_max_emitted;

/** 单文件多模块去重：判断 c_name 是否已在已输出类型名列表中。 */
static int emitted_type_contains(const char *c_name, char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int n) {
    if (!emitted_type_names || !c_name) return 0;
    for (int i = 0; i < n; i++)
        if (strcmp(emitted_type_names[i], c_name) == 0) return 1;
    return 0;
}
/** 单文件多模块去重：将 c_name 加入已输出列表。 */
static void emitted_type_add(const char *c_name, char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted) {
    if (!emitted_type_names || !n_emitted_inout || *n_emitted_inout >= max_emitted || !c_name) return;
    snprintf(emitted_type_names[*n_emitted_inout], CODEGEN_EMITTED_TYPE_NAME_MAX, "%s", c_name);
    (*n_emitted_inout)++;
}

/** 当 codegen_library_prefix 已设置时，将 name 写成 prefix+name 到 buf；否则只写 name。用于库模块符号不冲突。 */
static void library_prefixed_name(const char *name, char *buf, size_t size) {
    if (!name) name = "";
    if (!codegen_library_prefix || !*codegen_library_prefix) {
        (void)snprintf(buf, size, "%s", name);
        return;
    }
    (void)snprintf(buf, size, "%s%s", codegen_library_prefix, name);
}

/** 泛型单态化生成时的代入上下文（由 codegen_one_mono_instance 设置）；非 NULL 时 const/let 类型用代入后的类型。 */
static char **codegen_subst_gp_names;
static struct ASTType **codegen_subst_type_args;
static int codegen_subst_n;

/** 判断 NAMED 类型名是否为顶层枚举（§7.4）；用于输出 enum 与 struct 区分。 */
static int is_enum_type(const struct ASTModule *m, const char *name) {
    if (!m || !name || !m->enum_defs) return 0;
    for (int i = 0; i < m->num_enums; i++)
        if (m->enum_defs[i] && m->enum_defs[i]->name && strcmp(m->enum_defs[i]->name, name) == 0) return 1;
    return 0;
}

/** 判断两个类型是否相等（用于查找单态化实例）；与 typeck 的 type_equal 逻辑一致。 */
static int type_equal(const struct ASTType *a, const struct ASTType *b) {
    if (!a || !b) return (a == b);
    if (a->kind != b->kind) return 0;
    if (a->kind == AST_TYPE_NAMED)
        return (a->name && b->name && strcmp(a->name, b->name) == 0);
    if (a->kind == AST_TYPE_PTR || a->kind == AST_TYPE_SLICE || a->kind == AST_TYPE_VECTOR)
        return type_equal(a->elem_type, b->elem_type);
    if (a->kind == AST_TYPE_ARRAY)
        return a->array_size == b->array_size && type_equal(a->elem_type, b->elem_type);
    return 1;
}

/** 泛型代入：若 ty 为 NAMED 且在 gp_names 中则返回对应 type_args[i]，否则返回 ty。用于单态化生成时类型替换。 */
static const struct ASTType *subst_type(const struct ASTType *ty, char **gp_names,
    struct ASTType **type_args, int num_gp) {
    if (!ty || !gp_names || !type_args || num_gp <= 0) return ty;
    if (ty->kind == AST_TYPE_NAMED && ty->name) {
        for (int i = 0; i < num_gp; i++)
            if (gp_names[i] && strcmp(ty->name, gp_names[i]) == 0) return type_args[i];
    }
    return ty;
}

/** 将类型写成 mangle 用后缀（如 i32 -> "i32"，*i32 -> "ptr_i32"）；写入 buf，最多 size 字节。 */
static void type_to_suffix(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || size == 0) return;
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        type_to_suffix(ty->elem_type, buf, size);
        size_t len = strnlen(buf, size - 1);
        if (len + 6 < size) { snprintf(buf + len, size - len, "_ptr"); }
        return;
    }
    if (ty->kind == AST_TYPE_NAMED && ty->name) { snprintf(buf, size, "%s", ty->name); return; }
    const char *s = "i32";
    switch (ty->kind) {
        case AST_TYPE_I32:   s = "i32"; break;
        case AST_TYPE_F32:   s = "f32"; break;
        case AST_TYPE_F64:   s = "f64"; break;
        case AST_TYPE_BOOL:  s = "bool"; break;
        case AST_TYPE_U8:   s = "u8"; break;
        case AST_TYPE_U32:   s = "u32"; break;
        case AST_TYPE_U64:   s = "u64"; break;
        case AST_TYPE_I64:   s = "i64"; break;
        case AST_TYPE_USIZE: s = "usize"; break;
        case AST_TYPE_ISIZE: s = "isize"; break;
        default: break;
    }
    snprintf(buf, size, "%s", s);
}

/** impl 方法 C 函数名：Trait_Type_method（阶段 7.2）；f 须为 impl 块内函数（impl_for_trait/impl_for_type 非 NULL）。 */
static const char *impl_method_c_name(const struct ASTFunc *f) {
    static char buf[256];
    if (!f || !f->impl_for_trait || !f->impl_for_type || !f->name) return f ? f->name : "";
    snprintf(buf, sizeof(buf), "%s_%s_%s", f->impl_for_trait, f->impl_for_type, f->name);
    return buf;
}

/** 单态化实例的 C 函数名：name_t1_t2（如 id_i32、id_i32_bool）。返回值使用静态缓冲区。 */
static const char *mono_instance_mangled_name(const struct ASTFunc *f,
    struct ASTType **type_args, int num_type_args) {
    static char buf[256];
    if (!f || !f->name || num_type_args <= 0 || !type_args) return f ? f->name : "";
    size_t n = (size_t)snprintf(buf, sizeof(buf), "%s", f->name);
    for (int i = 0; i < num_type_args && n < sizeof(buf) - 2; i++) {
        char suf[64];
        type_to_suffix(type_args[i], suf, sizeof(suf));
        n += (size_t)snprintf(buf + n, sizeof(buf) - n, "_%s", suf);
    }
    return buf;
}

/** 将 import 路径转为 C 符号前缀（如 "foo" -> "foo_"，"core.types" -> "core_types_"）；用于跨模块调用。 */
static void import_path_to_c_prefix(const char *import_path, char *buf, size_t size) {
    if (!buf || size == 0) return;
    size_t off = 0;
    for (const char *s = import_path; *s && off + 2 < size; s++)
        buf[off++] = (char)(*s == '.' ? '_' : *s);
    if (off + 1 < size) buf[off++] = '_';
    buf[off] = '\0';
}

#define MAX_IMPORT_DECLS 32
/** 泛型 import 调用收集：path、func、type_args、num_type_args；最多 MAX_IMPORT_DECLS 条。 */
#define MAX_GEN_IMPORT_DECLS 32

/** 前向声明：块体生成与块内 import/lib_dep 收集在文件后部定义，供 AST_EXPR_BLOCK 与 AST_EXPR_IF 使用。 */
static void collect_import_calls_from_block(const struct ASTBlock *b, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count);
static void collect_lib_dep_calls_from_block(const struct ASTBlock *b, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out);

/** 从表达式 e 递归收集跨模块 CALL：非泛型追加到 paths/funcs/n，泛型追加到 gen_*（供 emit extern）。 */
static void collect_import_calls_from_expr(const struct ASTExpr *e, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count) {
    if (!e || !paths || !funcs || !n) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_import_path && e->value.call.resolved_callee_func) {
        if (e->value.call.num_type_args <= 0 || !e->value.call.type_args) {
            if (*n >= MAX_IMPORT_DECLS) return;
            for (int i = 0; i < *n; i++)
                if (paths[i] == e->value.call.resolved_import_path && funcs[i] == e->value.call.resolved_callee_func) return;
            paths[*n] = e->value.call.resolved_import_path;
            funcs[*n] = e->value.call.resolved_callee_func;
            (*n)++;
            return;
        }
        if (gen_paths && gen_funcs && gen_type_args && gen_n && gen_count && *gen_count < MAX_GEN_IMPORT_DECLS) {
            int nt = e->value.call.num_type_args;
            int found = 0;
            for (int i = 0; i < *gen_count; i++) {
                if (gen_paths[i] != e->value.call.resolved_import_path || gen_funcs[i] != e->value.call.resolved_callee_func) continue;
                if (gen_n[i] != nt) continue;
                int eq = 1;
                for (int j = 0; j < nt && eq; j++)
                    if (!type_equal(gen_type_args[i][j], e->value.call.type_args[j])) eq = 0;
                if (eq) { found = 1; break; }
            }
            if (!found) {
                gen_paths[*gen_count] = e->value.call.resolved_import_path;
                gen_funcs[*gen_count] = e->value.call.resolved_callee_func;
                gen_type_args[*gen_count] = e->value.call.type_args;
                gen_n[*gen_count] = nt;
                (*gen_count)++;
            }
        }
    }
    /* module.func 形式的 METHOD_CALL 也需登记，供 -E 生成 extern */
    if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_import_path && e->value.method_call.resolved_impl_func) {
        if (*n < MAX_IMPORT_DECLS) {
            int found = 0;
            for (int i = 0; i < *n; i++)
                if (paths[i] == e->value.method_call.resolved_import_path && funcs[i] == e->value.method_call.resolved_impl_func) { found = 1; break; }
            if (!found) {
                paths[*n] = e->value.method_call.resolved_import_path;
                funcs[*n] = e->value.method_call.resolved_impl_func;
                (*n)++;
            }
        }
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_import_calls_from_expr(e->value.call.args[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_import_calls_from_expr(e->value.binop.left, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.binop.right, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            collect_import_calls_from_expr(e->value.unary.operand, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_AS:
            collect_import_calls_from_expr(e->value.as_type.operand, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            collect_import_calls_from_expr(e->value.if_expr.cond, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.if_expr.then_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            if (e->value.if_expr.else_expr) collect_import_calls_from_expr(e->value.if_expr.else_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_BLOCK:
            collect_import_calls_from_block(e->value.block, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ASSIGN:
            collect_import_calls_from_expr(e->value.binop.left, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.binop.right, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_MATCH:
            collect_import_calls_from_expr(e->value.match_expr.matched_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_import_calls_from_expr(e->value.match_expr.arms[i].result, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_import_calls_from_expr(e->value.field_access.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_import_calls_from_expr(e->value.struct_lit.inits[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_import_calls_from_expr(e->value.array_lit.elems[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_INDEX:
            collect_import_calls_from_expr(e->value.index.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            collect_import_calls_from_expr(e->value.index.index_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_import_calls_from_expr(e->value.method_call.base, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_import_calls_from_expr(e->value.method_call.args[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        case AST_EXPR_PANIC:
            if (e->value.unary.operand) collect_import_calls_from_expr(e->value.unary.operand, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
            break;
        default: break;
    }
}
/** 从表达式 e 递归收集「库模块内对 lib_dep 的调用」：callee 为 VAR 且在 lib_dep_mods 中找到则追加 (path, func)，供生成 extern。 */
static void collect_lib_dep_calls_from_expr(const struct ASTExpr *e, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out) {
    if (!e || !paths_out || !funcs_out || !n_out || *n_out >= max_out) return;
    if (e->kind == AST_EXPR_CALL && e->value.call.callee->kind == AST_EXPR_VAR && lib_dep_mods && lib_dep_paths && n_lib_dep > 0) {
        const char *callee_name = e->value.call.callee->value.var.name;
        if (callee_name) {
            for (int di = 0; di < n_lib_dep; di++) {
                const struct ASTModule *dm = lib_dep_mods[di];
                if (!dm || !dm->funcs) continue;
                for (int fi = 0; fi < dm->num_funcs; fi++) {
                    if (!dm->funcs[fi]) continue;
                    if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) {
                        for (int k = 0; k < *n_out; k++)
                            if (paths_out[k] == lib_dep_paths[di] && funcs_out[k] == dm->funcs[fi]) goto next_call;
                        paths_out[*n_out] = lib_dep_paths[di];
                        funcs_out[*n_out] = (struct ASTFunc *)dm->funcs[fi];
                        (*n_out)++;
                        goto next_call;
                    }
                }
            }
        }
next_call: ;
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_lib_dep_calls_from_expr(e->value.call.args[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
            collect_lib_dep_calls_from_expr(e->value.binop.left, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.binop.right, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            collect_lib_dep_calls_from_expr(e->value.unary.operand, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_AS:
            collect_lib_dep_calls_from_expr(e->value.as_type.operand, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            collect_lib_dep_calls_from_expr(e->value.if_expr.cond, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.if_expr.then_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            if (e->value.if_expr.else_expr) collect_lib_dep_calls_from_expr(e->value.if_expr.else_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_BLOCK:
            collect_lib_dep_calls_from_block(e->value.block, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ASSIGN:
            collect_lib_dep_calls_from_expr(e->value.binop.left, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.binop.right, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_MATCH:
            collect_lib_dep_calls_from_expr(e->value.match_expr.matched_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_lib_dep_calls_from_expr(e->value.match_expr.arms[i].result, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_lib_dep_calls_from_expr(e->value.field_access.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_lib_dep_calls_from_expr(e->value.struct_lit.inits[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_lib_dep_calls_from_expr(e->value.array_lit.elems[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_INDEX:
            collect_lib_dep_calls_from_expr(e->value.index.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            collect_lib_dep_calls_from_expr(e->value.index.index_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_lib_dep_calls_from_expr(e->value.method_call.base, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_lib_dep_calls_from_expr(e->value.method_call.args[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        case AST_EXPR_PANIC:
        case AST_EXPR_RETURN:
            if (e->value.unary.operand) collect_lib_dep_calls_from_expr(e->value.unary.operand, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
            break;
        default: break;
    }
}
static void collect_lib_dep_calls_from_block(const struct ASTBlock *b, struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    const char **paths_out, struct ASTFunc **funcs_out, int *n_out, int max_out) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_lib_dep_calls_from_expr(b->const_decls[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_lib_dep_calls_from_expr(b->let_decls[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_loops; i++)
        collect_lib_dep_calls_from_block(b->loops[i].body, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_lib_dep_calls_from_expr(b->for_loops[i].init, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        if (b->for_loops[i].cond) collect_lib_dep_calls_from_expr(b->for_loops[i].cond, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        if (b->for_loops[i].step) collect_lib_dep_calls_from_expr(b->for_loops[i].step, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
        collect_lib_dep_calls_from_block(b->for_loops[i].body, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_lib_dep_calls_from_expr(b->labeled_stmts[i].u.return_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_lib_dep_calls_from_expr(b->expr_stmts[i], lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
    if (b->final_expr) collect_lib_dep_calls_from_expr(b->final_expr, lib_dep_mods, lib_dep_paths, n_lib_dep, paths_out, funcs_out, n_out, max_out);
}

/** 从块 b 递归收集所有跨模块 CALL（非泛型与泛型）。 */
static void collect_import_calls_from_block(const struct ASTBlock *b, const char **paths, struct ASTFunc **funcs, int *n,
    const char **gen_paths, struct ASTFunc **gen_funcs, struct ASTType ***gen_type_args, int *gen_n, int *gen_count) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) collect_import_calls_from_expr(b->const_decls[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) collect_import_calls_from_expr(b->let_decls[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_loops; i++)
        collect_import_calls_from_block(b->loops[i].body, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_import_calls_from_expr(b->for_loops[i].init, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        if (b->for_loops[i].cond) collect_import_calls_from_expr(b->for_loops[i].cond, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        if (b->for_loops[i].step) collect_import_calls_from_expr(b->for_loops[i].step, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
        collect_import_calls_from_block(b->for_loops[i].body, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_import_calls_from_expr(b->labeled_stmts[i].u.return_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_import_calls_from_expr(b->expr_stmts[i], paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
    if (b->final_expr) collect_import_calls_from_expr(b->final_expr, paths, funcs, n, gen_paths, gen_funcs, gen_type_args, gen_n, gen_count);
}

/** 若当前处于单态化代入上下文则返回代入后的类型，否则返回 ty；用于 const/let 等类型输出。 */
static const struct ASTType *codegen_emit_type(const struct ASTType *ty) {
    if (!ty) return ty;
    if (codegen_subst_gp_names) return subst_type(ty, codegen_subst_gp_names, codegen_subst_type_args, codegen_subst_n);
    return ty;
}

/** 前向声明：向量类型 C 名（定义在 c_type_to_buf 之后）。 */
static const char *vector_c_type_name(const struct ASTType *ty);

/**
 * 将 AST 类型写入 buf，用于递归拼指针类型（*T、**T 等）。
 * 参数：ty 类型节点；buf 输出缓冲区；size 缓冲区大小。副作用：写入 buf。
 */
static void c_type_to_buf(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || size == 0) return;
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        static char inner_buf[256];
        c_type_to_buf(ty->elem_type, inner_buf, sizeof(inner_buf));
        snprintf(buf, size, "%s *", inner_buf);
        return;
    }
    /* 数组类型 [N]T：声明时用 elem_type name[N]，此处只写元素类型（文档 §6.2） */
    if (ty->kind == AST_TYPE_ARRAY && ty->elem_type) {
        c_type_to_buf(ty->elem_type, buf, size);
        return;
    }
    /* 切片 []T：C 侧为 struct shulang_slice_<elem>；elem 为 struct 时含 "struct "，切片名须单标识符故 strip 掉 */
    if (ty->kind == AST_TYPE_SLICE && ty->elem_type) {
        static char elem_buf[128];
        c_type_to_buf(ty->elem_type, elem_buf, sizeof(elem_buf));
        const char *name_part = (strncmp(elem_buf, "struct ", 7) == 0) ? elem_buf + 7 : elem_buf;
        snprintf(buf, size, "struct shulang_slice_%s", name_part);
        return;
    }
    /* 向量类型 i32x4/u32x4/i32x8/u32x8（文档 §10）：C 侧为 typedef struct { elem v[lanes]; } *_t */
    if (ty->kind == AST_TYPE_VECTOR && ty->elem_type) {
        snprintf(buf, size, "%s", vector_c_type_name(ty));
        return;
    }
    const char *s = "int";
    switch (ty->kind) {
        case AST_TYPE_VOID:  s = "void"; break;
        case AST_TYPE_I32:   s = "int32_t"; break;
        case AST_TYPE_F32:   s = "float"; break;
        case AST_TYPE_F64:   s = "double"; break;
        case AST_TYPE_BOOL:  s = "int"; break;
        case AST_TYPE_U8:    s = "uint8_t"; break;
        case AST_TYPE_U32:   s = "uint32_t"; break;
        case AST_TYPE_U64:   s = "uint64_t"; break;
        case AST_TYPE_I64:   s = "int64_t"; break;
        case AST_TYPE_USIZE: s = "size_t"; break;
        case AST_TYPE_ISIZE: s = "ptrdiff_t"; break;
        case AST_TYPE_NAMED: {
            const char *n = ty->name ? ty->name : "int";
            /* 限定类型名（如 elf.ElfCodegenCtx、platform.elf.ElfCodegenCtx）：从最后一个点拆出类型名，在 dep 中按 import_path 匹配并输出 struct dep_prefix_TypeName，避免生成 xxx.elf.ElfCodegenCtx 导致 C 非法。 */
            if (strchr(n, '.') && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                const char *last_dot = strrchr(n, '.');
                if (last_dot && last_dot[1]) {
                    const char *type_name = last_dot + 1;
                    size_t module_len = (size_t)(last_dot - n);
                    for (int i = 0; i < codegen_ndep; i++) {
                        const struct ASTModule *d = codegen_dep_mods[i];
                        if (!d || !d->struct_defs) continue;
                        for (int j = 0; j < d->num_structs; j++) {
                            if (!d->struct_defs[j]->name || strcmp(d->struct_defs[j]->name, type_name) != 0) continue;
                            const char *dep_path = codegen_dep_paths[i];
                            if (!dep_path) continue;
                            /* 匹配：dep_path 等于 n 的 module 部分，或 dep_path 以 ".module_part" 结尾（如 platform.elf 对 elf） */
                            size_t dlen = strlen(dep_path);
                            int match = 0;
                            if (dlen == module_len && strncmp(dep_path, n, module_len) == 0) match = 1;
                            else if (dlen > module_len + 1 && dep_path[dlen - module_len - 1] == '.' && strncmp(dep_path + dlen - module_len, n, module_len) == 0) match = 1;
                            if (match) {
                                static char dep_pre[256];
                                import_path_to_c_prefix(dep_path, dep_pre, sizeof(dep_pre));
                                snprintf(buf, size, "struct %s%s", dep_pre, type_name);
                                return;
                            }
                        }
                    }
                }
            }
            /* 入口模块：若类型来自依赖模块的 enum，用 "enum prefix_Name" 与库 .c 一致 */
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->enum_defs) continue;
                    for (int j = 0; j < d->num_enums; j++)
                        if (d->enum_defs[j]->name && strcmp(d->enum_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "enum %s%s", dep_pre, n);
                            return;
                        }
                }
            }
            /* 库模块：本模块内的 enum 须用 "enum prefix_Name" 以便与库 .c 中定义一致 */
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs) {
                for (int i = 0; i < codegen_library_module->num_enums; i++)
                    if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, n) == 0) {
                        snprintf(buf, size, "enum %s%s", codegen_library_prefix, n);
                        return;
                    }
            }
            int is_struct_in_lib = 0;
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->struct_defs) {
                for (int i = 0; i < codegen_library_module->num_structs; i++)
                    if (codegen_library_module->struct_defs[i]->name && strcmp(codegen_library_module->struct_defs[i]->name, n) == 0) {
                        is_struct_in_lib = 1;
                        break;
                    }
            }
            if (is_struct_in_lib) {
                snprintf(buf, size, "struct %s%s", codegen_library_prefix, n);
                return;
            }
            /* 库模块：若类型来自其 import 依赖（如 lexer 中的 Token 来自 token），用依赖的 C 前缀，避免 lexer_Token 导致未定义类型 */
            if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->enum_defs) continue;
                    for (int j = 0; j < d->num_enums; j++)
                        if (d->enum_defs[j]->name && strcmp(d->enum_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "enum %s%s", dep_pre, n);
                            return;
                        }
                }
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->struct_defs) continue;
                    for (int j = 0; j < d->num_structs; j++)
                        if (d->struct_defs[j]->name && strcmp(d->struct_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "struct %s%s", dep_pre, n);
                            return;
                        }
                }
            }
            /* 入口模块：本模块内定义的 enum 须用 "enum Name"，否则 C 中 Color c 报错（须 enum Color c） */
            if (!codegen_library_prefix && codegen_current_module && codegen_current_module->enum_defs) {
                for (int i = 0; i < codegen_current_module->num_enums; i++)
                    if (codegen_current_module->enum_defs[i]->name && strcmp(codegen_current_module->enum_defs[i]->name, n) == 0) {
                        snprintf(buf, size, "enum %s", n);
                        return;
                    }
            }
            /* 入口模块：若类型来自依赖模块的 struct，用 "struct prefix_Name" 与库 .c 一致 */
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                for (int i = 0; i < codegen_ndep; i++) {
                    const struct ASTModule *d = codegen_dep_mods[i];
                    if (!d || !d->struct_defs) continue;
                    for (int j = 0; j < d->num_structs; j++)
                        if (d->struct_defs[j]->name && strcmp(d->struct_defs[j]->name, n) == 0) {
                            static char dep_pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[i], dep_pre, sizeof(dep_pre));
                            snprintf(buf, size, "struct %s%s", dep_pre, n);
                            return;
                        }
                }
            }
            /* 入口模块：本模块内定义的 struct 须用 "struct Name"；多模块 -E 时须带 C 前缀（如 ast_Type）与生成 C 一致 */
            if (codegen_current_module && codegen_current_module->struct_defs) {
                for (int i = 0; i < codegen_current_module->num_structs; i++)
                    if (codegen_current_module->struct_defs[i]->name && strcmp(codegen_current_module->struct_defs[i]->name, n) == 0) {
                        /* 库模块 -E 时须 "struct prefix_Name" 与生成 C 一致 */
                        if (codegen_library_prefix && *codegen_library_prefix) {
                            snprintf(buf, size, "struct %s%s", codegen_library_prefix, n);
                            return;
                        }
                        if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                            for (int di = 0; di < codegen_ndep; di++)
                                if (codegen_dep_mods[di] == codegen_current_module) {
                                    char pre[64];
                                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                                    snprintf(buf, size, "struct %s%s", pre, n);
                                    return;
                                }
                        }
                        if (!codegen_library_prefix) {
                            snprintf(buf, size, "struct %s", n);
                            return;
                        }
                    }
            }
            if (codegen_library_prefix && *codegen_library_prefix)
                snprintf(buf, size, "%s%s", codegen_library_prefix, n);
            else
                snprintf(buf, size, "%s", n);
            return;
        }
        default: break;
    }
    snprintf(buf, size, "%s", s);
}

/**
 * 将 AST 类型映射为 C 类型字符串；用于 const/let 声明。支持裸指针 *T（文档 §5.1）。
 * 参数：ty 类型节点，不可为 NULL。返回值：C 类型名（静态缓冲区，非线程安全）。
 */
static const char *c_type_str(const struct ASTType *ty) {
    if (!ty) return "int";
    static char buf[256];
    c_type_to_buf(ty, buf, sizeof(buf));
    return buf;
}

/** 表达式 e 的 resolved_type 是否为 struct（用于 if-expr __tmp：当 __tmp 为 struct 而分支产生标量时须赋 (struct X){0} 而非 0）。 */
static int expr_produces_struct_type(const struct ASTExpr *e) {
    if (!e || !e->resolved_type) return 0;
    const char *s = c_type_str(e->resolved_type);
    return (s && strncmp(s, "struct ", 7) == 0);
}

/** 表达式 e 的 resolved_type 是否为可折叠为整数的标量（仅此时 const_folded_val 才有意义；struct/float 等不能当整数字面量输出）。
 * 不含 U8：u8 的 const_folded_val 可能被误用导致 return -1094795586 等错误，故 u8 一律走正常表达式生成。 */
static int expr_type_is_foldable_scalar(const struct ASTExpr *e) {
    if (!e || !e->resolved_type) return 0;
    switch (e->resolved_type->kind) {
        case AST_TYPE_I32: case AST_TYPE_BOOL: case AST_TYPE_U32:
        case AST_TYPE_I64: case AST_TYPE_USIZE: case AST_TYPE_ISIZE:
            return 1;
        default:
            return 0;
    }
}

/** 当 __tmp 类型为 struct（tmp_ty_str）且 else 分支类型与之不一致时返回 1，此时应输出 (tmp_ty_str){0} 而非 else 表达式，避免 LexerResult __tmp = (Token){0} 等错误。
 * 统一用 expr_struct_type_str 取 else 的 C struct 类型再与 tmp_ty_str 比较，因 c_type_str(NAMED) 可能无 "struct " 前缀。 */
static int else_struct_type_mismatch(const char *tmp_ty_str, const struct ASTExpr *else_e) {
    if (!tmp_ty_str || strncmp(tmp_ty_str, "struct ", 7) != 0 || !else_e) return 0;
    if (!expr_produces_struct_type(else_e)) return 1;
    static char else_ty_buf[128];
    if (!expr_struct_type_str(else_e, else_ty_buf, sizeof(else_ty_buf))) {
        if (else_e->resolved_type) {
            const char *es = c_type_str(else_e->resolved_type);
            if (es && strncmp(es, "struct ", 7) == 0 && strcmp(es, tmp_ty_str) != 0) return 1;
        }
        return 0;
    }
    return (strcmp(else_ty_buf, tmp_ty_str) != 0) ? 1 : 0;
}

/**
 * 输出结构体字段的 C 类型+名（支持多维数组 [N][M]...，自举用：OneFuncResult 等含 [16][32]u8 字段）。
 * 参数：fty 字段类型；fname 字段名；out 输出。副作用：向 out 写入 "elem_type name[N][M]; " 或 "type name; "。
 */
static void emit_struct_field_c_type(const struct ASTType *fty, const char *fname, FILE *out) {
    if (!fty) { fprintf(out, "int32_t %s; ", fname); return; }
    if (fty->kind == AST_TYPE_ARRAY && fty->elem_type) {
        const struct ASTType *t = fty;
        char dims[64] = "";
        while (t->kind == AST_TYPE_ARRAY && t->elem_type) {
            char d[16];
            snprintf(d, sizeof(d), "[%d]", t->array_size);
            strncat(dims, d, sizeof(dims) - 1);
            t = t->elem_type;
        }
        fprintf(out, "%s %s%s; ", c_type_str(t), fname, dims);
    } else {
        fprintf(out, "%s %s; ", c_type_str(fty), fname);
    }
}

/**
 * 输出局部/块内数组变量声明前缀 "elem_type name[N][M] "（支持多维，自举用；不含 "= "）。
 * 参数：ty 数组类型；name 变量名；pad 缩进；out 输出。
 */
static void emit_local_array_decl(const struct ASTType *ty, const char *name, const char *pad, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_ARRAY || !ty->elem_type) return;
    const struct ASTType *t = ty;
    char dims[64] = "";
    while (t->kind == AST_TYPE_ARRAY && t->elem_type) {
        char d[16];
        snprintf(d, sizeof(d), "[%d]", t->array_size);
        strncat(dims, d, sizeof(dims) - 1);
        t = t->elem_type;
    }
    fprintf(out, "%s%s %s%s ", pad, c_type_str(t), name, dims);
}

/**
 * §3.4 内建函数映射框架：将 C 符号名映射为后端 intrinsic（如 core_mem_mem_copy -> __builtin_memcpy）；默认返回原名。
 * 供 core.mem / core.builtin / SIMD 等生成目标平台最优指令时扩展。
 * core.builtin：copy -> __builtin_memcpy，unreachable -> __builtin_unreachable，abort -> __builtin_abort，便于零开销与冷路径优化。
 */
static const char *builtin_intrinsic_name(const char *c_name) {
    if (!c_name) return c_name;
    if (strcmp(c_name, "core_mem_mem_copy") == 0) return "__builtin_memcpy";
    if (strcmp(c_name, "core_mem_mem_set") == 0) return "__builtin_memset";
    if (strcmp(c_name, "core_mem_mem_move") == 0) return "__builtin_memmove";
    if (strcmp(c_name, "core_builtin_copy") == 0) return "__builtin_memcpy";
    if (strcmp(c_name, "core_builtin_unreachable") == 0) return "__builtin_unreachable";
    if (strcmp(c_name, "core_builtin_abort") == 0) return "__builtin_abort";
    return c_name;
}

/**
 * 向 out 输出单个函数形参的 C 声明；若为指针且 is_restrict 则插入 restrict（noalias 传递）。
 * 数组类型 [N]T 输出为 elem_type name[N]，否则 c_type_str 只出元素类型会导致参数退化为指针（方案 A 自举 pipeline_gen.c 需完整数组声明）。
 * override_ty 非 NULL 时用其替代 p->type（用于单态化），仍用 p->is_restrict。
 * slice 形参按指针传递，避免 16 字节按值传参时 ABI 导致 length 错乱（bar→ba、main→mai）。
 */
static const struct ASTFunc *codegen_current_func;

static int expr_is_slice_ptr_param(const struct ASTExpr *e) {
    if (!e || e->kind != AST_EXPR_VAR || !e->value.var.name || !codegen_current_func) return 0;
    for (int i = 0; i < codegen_current_func->num_params; i++)
        if (codegen_current_func->params[i].name && strcmp(codegen_current_func->params[i].name, e->value.var.name) == 0
            && codegen_current_func->params[i].type && codegen_current_func->params[i].type->kind == AST_TYPE_SLICE)
            return 1;
    return 0;
}

/** 当 e 为形参且类型为 PTR 或 SLICE 时返回 1，用于字段访问输出 ->（C 中指针/slice 按指针传）；弥补 typeck 未填 base->resolved_type 时仍能正确生成）。 */
static int expr_is_ptr_or_slice_param(const struct ASTExpr *e) {
    if (!e || e->kind != AST_EXPR_VAR || !e->value.var.name || !codegen_current_func) return 0;
    for (int i = 0; i < codegen_current_func->num_params; i++)
        if (codegen_current_func->params[i].name && strcmp(codegen_current_func->params[i].name, e->value.var.name) == 0
            && codegen_current_func->params[i].type) {
            enum ASTTypeKind k = codegen_current_func->params[i].type->kind;
            if (k == AST_TYPE_PTR || k == AST_TYPE_SLICE) return 1;
        }
    return 0;
}

/** .su 侧：base 是否为 slice 形参（C 中按指针传，用 ->）；否则为局部/全局 struct 用 .；无当前函数时保守返回 0。 */
int32_t codegen_su_expr_is_slice_ptr_param(uint8_t *expr) {
    return (codegen_current_func && expr_is_slice_ptr_param((const struct ASTExpr *)expr)) ? 1 : 0;
}
/** .su 侧 INDEX 切片边界检查：((idx)<0||(size_t)(idx)>=(base).length 或 (base)->length ? ...）。仅形参用 ->。 */
int32_t codegen_su_emit_index_slice_bounds_check(uint8_t *out, uint8_t *base, uint8_t *idx) {
    FILE *f = (FILE *)out;
    int use_arrow = codegen_su_expr_is_slice_ptr_param(base);
    const char *da = use_arrow ? ")->" : ").";
    if (fprintf(f, "(") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    if (fprintf(f, " < 0 || (size_t)(") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    if (fprintf(f, ") >= (") < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)base, f) != 0) return -1;
    if (fprintf(f, "%slength ? (shulang_panic_(1, 0), (", da) < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)base, f) != 0) return -1;
    if (fprintf(f, "%sdata[0]) : (", da) < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)base, f) != 0) return -1;
    if (fprintf(f, "%sdata[", da) < 0) return -1;
    if (codegen_expr((const struct ASTExpr *)idx, f) != 0) return -1;
    return fprintf(f, "])") < 0 ? -1 : 0;
}

static void codegen_emit_param(const struct ASTParam *p, FILE *out, const struct ASTType *override_ty) {
    if (!p || !out) return;
    const struct ASTType *ty = override_ty ? override_ty : p->type;
    const char *name = p->name ? p->name : "";
    if (ty && ty->kind == AST_TYPE_PTR && p->is_restrict)
        fprintf(out, "%s restrict %s", c_type_str(ty), name);
    else if (ty && ty->kind == AST_TYPE_ARRAY && ty->elem_type && ty->array_size > 0)
        fprintf(out, "%s %s[%d]", c_type_str(ty->elem_type), name, ty->array_size);
    else if (ty && ty->kind == AST_TYPE_SLICE)
        fprintf(out, "%s * %s", c_type_str(ty), name);
    else
        fprintf(out, "%s %s", ty ? c_type_str(ty) : "int32_t", name);
}

/** 已输出的切片结构体 elem 类型 key 的副本，避免重复定义；c_type_str 返回静态缓冲区会被覆盖，故存副本 */
#define MAX_SLICE_STRUCTS 16
#define SLICE_KEY_MAX 64
static char codegen_slice_emitted[MAX_SLICE_STRUCTS][SLICE_KEY_MAX];
static int codegen_slice_emitted_n;

/** 向量 typedef 已输出 key 列表（如 "i32x4","u32x8"），每轮 codegen 开始时清空 */
#define MAX_VECTOR_TYPEDEFS 8
static const char *codegen_vector_emitted[MAX_VECTOR_TYPEDEFS];
static int codegen_vector_emitted_n;

/** 返回向量类型的 C 类型名（如 i32x4_t）；ty 须为 AST_TYPE_VECTOR 且 elem_type/array_size 为支持的组合。 */
static const char *vector_c_type_name(const struct ASTType *ty) {
    if (!ty || ty->kind != AST_TYPE_VECTOR || !ty->elem_type) return "int32_t";
    int lanes = ty->array_size;
    switch (ty->elem_type->kind) {
        case AST_TYPE_I32: if (lanes == 4) return "i32x4_t"; if (lanes == 8) return "i32x8_t"; if (lanes == 16) return "i32x16_t"; break;
        case AST_TYPE_U32: if (lanes == 4) return "u32x4_t"; if (lanes == 8) return "u32x8_t"; if (lanes == 16) return "u32x16_t"; break;
        default: break;
    }
    return "int32_t";
}

/** 若 ty 为支持的向量类型且尚未输出，则输出一次 typedef；无返回值。 */
static void ensure_vector_typedef(const struct ASTType *ty, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_VECTOR || !ty->elem_type || !out) return;
    const char *name = vector_c_type_name(ty);
    const char *key = name;
    for (int i = 0; i < codegen_vector_emitted_n; i++)
        if (codegen_vector_emitted[i] && strcmp(codegen_vector_emitted[i], key) == 0) return;
    if (codegen_vector_emitted_n >= MAX_VECTOR_TYPEDEFS) return;
    codegen_vector_emitted[codegen_vector_emitted_n++] = key;
    const char *elem = (ty->elem_type->kind == AST_TYPE_U32) ? "uint32_t" : "int32_t";
    int lanes = ty->array_size;
    fprintf(out, "typedef struct { %s v[%d]; } %s;\n", elem, lanes, name);
}

/** 递归扫描块内 const/let，为所有用到的向量类型输出 typedef。 */
static void ensure_block_vector_typedefs(const struct ASTBlock *b, FILE *out) {
    if (!b || !out) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_VECTOR)
            ensure_vector_typedef(b->const_decls[i].type, out);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_VECTOR)
            ensure_vector_typedef(b->let_decls[i].type, out);
    for (int i = 0; i < b->num_loops; i++)
        if (b->loops[i].body) ensure_block_vector_typedefs(b->loops[i].body, out);
    for (int i = 0; i < b->num_for_loops; i++)
        if (b->for_loops[i].body) ensure_block_vector_typedefs(b->for_loops[i].body, out);
}

/**
 * 若 ty 为切片类型，则向 out 输出一次 struct shulang_slice_<elem> { elem* data; size_t length; }（文档 §6.3）。
 * 同一 elem 类型只输出一次。单文件多模块时先查 codegen_emitted_type_names，避免跨库重复定义。
 */
static void ensure_slice_struct(const struct ASTType *ty, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_SLICE || !ty->elem_type || !out) return;
    const char *key = c_type_str(ty->elem_type);
    const char *name_part = (strncmp(key, "struct ", 7) == 0) ? key + 7 : key;
    char full_slice_name[128];
    (void)snprintf(full_slice_name, sizeof(full_slice_name), "shulang_slice_%s", name_part);
    if (codegen_emitted_type_names && codegen_n_emitted_inout &&
        emitted_type_contains(full_slice_name, codegen_emitted_type_names, *codegen_n_emitted_inout))
        return;
    for (int i = 0; i < codegen_slice_emitted_n; i++)
        if (strcmp(codegen_slice_emitted[i], key) == 0) return;
    if (codegen_slice_emitted_n >= MAX_SLICE_STRUCTS) return;
    (void)snprintf(codegen_slice_emitted[codegen_slice_emitted_n], SLICE_KEY_MAX, "%s", key);
    codegen_slice_emitted_n++;
    if (codegen_emitted_type_names && codegen_n_emitted_inout && codegen_max_emitted > 0)
        emitted_type_add(full_slice_name, codegen_emitted_type_names, codegen_n_emitted_inout, codegen_max_emitted);
    fprintf(out, "struct shulang_slice_%s { %s *data; size_t length; };\n", name_part, key);
}

/** FIELD_ACCESS 枚举变体完整输出：Type.Variant → prefix_Enum_Variant；依赖/库前缀查找在 C 内完成，供 .su 统一入口转调。 */
static int codegen_emit_field_access_enum_variant_impl(FILE *out, const struct ASTExpr *e) {
    /* 库模块未做 typeck 时 is_enum_variant 可能为 0；若 base 为当前库模块枚举类型名则按枚举变体输出 */
    if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs
        && e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
        const char *en2 = e->value.field_access.base->value.var.name;
        const char *vn2 = e->value.field_access.field_name;
        for (int i = 0; i < codegen_library_module->num_enums; i++)
            if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, en2) == 0) {
                fprintf(out, "%s%s_%s", codegen_library_prefix, en2, vn2 ? vn2 : "");
                return 0;
            }
    }
    const char *en = e->value.field_access.base->value.var.name;
    const char *vn = e->value.field_access.field_name;
    if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->enum_defs) continue;
            for (int ej = 0; ej < d->num_enums; ej++)
                if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "%s%s_%s", pre, en, vn ? vn : "");
                    found = 1;
                    break;
                }
        }
        if (found) return 0;
    }
    if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->enum_defs) continue;
            for (int ej = 0; ej < d->num_enums; ej++)
                if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "%s%s_%s", pre, en, vn ? vn : "");
                    found = 1;
                    break;
                }
        }
        if (found) return 0;
    }
    if (codegen_library_prefix && *codegen_library_prefix && en)
        fprintf(out, "%s%s_%s", codegen_library_prefix, en, vn ? vn : "");
    else
        fprintf(out, "%s_%s", en ? en : "", vn ? vn : "");
    return 0;
}

/** .su 侧 FIELD_ACCESS 枚举变体：仅将「前缀」写入 out，供 .su 自实现时拼 prefix+enum_name+'_'+variant_name。返回 0 成功，-1 失败。 */
int32_t codegen_su_emit_enum_variant_prefix(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_FIELD_ACCESS || !e->value.field_access.base
        || e->value.field_access.base->kind != AST_EXPR_VAR) return -1;
    const char *en = e->value.field_access.base->value.var.name;
    if (!en) return -1;
    if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs) {
        for (int i = 0; i < codegen_library_module->num_enums; i++)
            if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, en) == 0) {
                fprintf((FILE *)out, "%s", codegen_library_prefix);
                return 0;
            }
    }
    if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        for (int di = 0; di < codegen_ndep; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->enum_defs) continue;
            for (int ej = 0; ej < d->num_enums; ej++)
                if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf((FILE *)out, "%s", pre);
                    return 0;
                }
        }
    }
    if (codegen_library_prefix && *codegen_library_prefix) {
        fprintf((FILE *)out, "%s", codegen_library_prefix);
        return 0;
    }
    return 0; /* 无前缀 */
}

/** .su 侧 FIELD_ACCESS：base 为 VAR 时返回类型名（枚举名）指针，否则 NULL。 */
uint8_t *codegen_su_field_access_base_var_name(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_FIELD_ACCESS || !e->value.field_access.base
        || e->value.field_access.base->kind != AST_EXPR_VAR) return NULL;
    const char *n = e->value.field_access.base->value.var.name;
    return (uint8_t *)(n ? n : "");
}

/** .su 侧 FIELD_ACCESS：base 为 VAR 时返回类型名（枚举名）长度。 */
int32_t codegen_su_field_access_base_var_name_len(uint8_t *expr) {
    const char *n = (const char *)codegen_su_field_access_base_var_name(expr);
    return (int32_t)(n ? strlen(n) : 0);
}

/** .su 侧 FIELD_ACCESS 枚举变体全量输出：供 codegen.su 的 emit_field_access_expr 转调（fallback）。 */
int32_t codegen_su_emit_field_access_enum_variant_full(uint8_t *out, uint8_t *expr) {
    return codegen_emit_field_access_enum_variant_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0;
}

/** 根据结构体名查找字段类型（当前模块或依赖）；用于结构体字面量判断数组字段。返回 NULL 表示未找到。 */
static const struct ASTType *get_struct_field_type(const char *struct_name, const char *field_name) {
    if (!struct_name || !field_name) return NULL;
    if (codegen_current_module && codegen_current_module->struct_defs) {
        for (int i = 0; i < codegen_current_module->num_structs; i++) {
            const struct ASTStructDef *sd = codegen_current_module->struct_defs[i];
            if (!sd || !sd->name || strcmp(sd->name, struct_name) != 0) continue;
            for (int j = 0; j < sd->num_fields; j++)
                if (sd->fields[j].name && strcmp(sd->fields[j].name, field_name) == 0)
                    return sd->fields[j].type;
            return NULL;
        }
    }
    if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        for (int di = 0; di < codegen_ndep; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int j = 0; j < d->num_structs; j++) {
                if (!d->struct_defs[j]->name || strcmp(d->struct_defs[j]->name, struct_name) != 0) continue;
                const struct ASTStructDef *sd = d->struct_defs[j];
                for (int k = 0; k < sd->num_fields; k++)
                    if (sd->fields[k].name && strcmp(sd->fields[k].name, field_name) == 0)
                        return sd->fields[k].type;
                return NULL;
            }
        }
    }
    return NULL;
}

/** 仅写结构体类型名 "struct X" 或 "struct prefix_X"（不含 "( ){ "），供块形式结构体字面量用。 */
static void codegen_emit_struct_type_name_only(FILE *out, const char *struct_name) {
    if (!struct_name) { fprintf(out, "struct unknown"); return; }
    if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int sj = 0; sj < d->num_structs; sj++)
                if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, struct_name) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "struct %s%s", pre, struct_name);
                    found = 1;
                    break;
                }
        }
        if (!found) { char buf[256]; library_prefixed_name(struct_name, buf, sizeof(buf)); fprintf(out, "struct %s", buf); }
    } else if (codegen_library_prefix && *codegen_library_prefix) {
        char buf[256]; library_prefixed_name(struct_name, buf, sizeof(buf)); fprintf(out, "struct %s", buf);
    } else if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int sj = 0; sj < d->num_structs; sj++)
                if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, struct_name) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "struct %s%s", pre, struct_name);
                    found = 1;
                    break;
                }
        }
        if (!found) fprintf(out, "struct %s", struct_name);
    } else {
        fprintf(out, "struct %s", struct_name);
    }
}

/**
 * 递归求表达式可能产生的 struct 类型 C 串；用于嵌套 if-expr 的 __tmp 推断（else 为 else if 时 typeck 可能未设 resolved_type）。
 * 返回：若表达式会产生 struct 值则写入 buf 并返回 buf，否则返回 NULL。
 */
static const char *expr_struct_type_str(const struct ASTExpr *e, char *buf, size_t bufsize) {
    if (!e || !buf || bufsize < 16) return NULL;
    if (e->kind == AST_EXPR_STRUCT_LIT) return struct_lit_c_type_str(e, buf, bufsize);
    if (e->kind == AST_EXPR_IF) {
        const struct ASTExpr *ee = e->value.if_expr.else_expr;
        const struct ASTExpr *te = e->value.if_expr.then_expr;
        if (ee && expr_struct_type_str(ee, buf, bufsize)) return buf;
        if (te && expr_struct_type_str(te, buf, bufsize)) return buf;
        if (e->resolved_type) {
            const char *s = c_type_str(e->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) { snprintf(buf, bufsize, "%s", s); return buf; }
        }
        return NULL;
    }
    if (e->kind == AST_EXPR_ASSIGN && e->value.binop.right)
        return expr_struct_type_str(e->value.binop.right, buf, bufsize);
    /* 块仅含 return expr 或 if (cond) return 时从操作数/then 推断 struct 类型（如 if (ref<=0) { return Type{...}; } 无 else 时 then 为块） */
    if (e->kind == AST_EXPR_BLOCK && e->value.block) {
        const struct ASTBlock *b = e->value.block;
        const struct ASTExpr *ret_e = NULL;
        if (b->final_expr && b->final_expr->kind == AST_EXPR_RETURN)
            ret_e = b->final_expr->value.unary.operand;
        else if (b->final_expr && b->final_expr->kind == AST_EXPR_IF)
            return expr_struct_type_str(b->final_expr->value.if_expr.then_expr, buf, bufsize);
        else if (b->num_expr_stmts == 1 && b->expr_stmts && b->expr_stmts[0]
                 && b->expr_stmts[0]->kind == AST_EXPR_RETURN)
            ret_e = b->expr_stmts[0]->value.unary.operand;
        else if (b->num_labeled_stmts == 1 && b->labeled_stmts
                 && b->labeled_stmts[0].kind == AST_STMT_RETURN && b->labeled_stmts[0].u.return_expr)
            ret_e = b->labeled_stmts[0].u.return_expr;
        if (ret_e && expr_struct_type_str(ret_e, buf, bufsize)) return buf;
    }
    if (e->resolved_type) {
        const char *s = c_type_str(e->resolved_type);
        if (s && strncmp(s, "struct ", 7) == 0) { snprintf(buf, bufsize, "%s", s); return buf; }
    }
    return NULL;
}

/** 返回结构体字面量 e 的 C 类型串（如 "struct ast_Type"），写入 buf，与 codegen 发射该字面量时用的类型一致。
 * 用于 if-expr 的 __tmp 类型推断：else 为 (Type){0} 时 typeck 可能未设 resolved_type，用此函数得到正确 __tmp 类型。 */
static const char *struct_lit_c_type_str(const struct ASTExpr *e, char *buf, size_t bufsize) {
    if (!e || e->kind != AST_EXPR_STRUCT_LIT || !e->value.struct_lit.struct_name || bufsize < 16) return NULL;
    const char *sname = e->value.struct_lit.struct_name;
    if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        for (int di = 0; di < codegen_ndep; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int sj = 0; sj < d->num_structs; sj++)
                if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, sname) == 0) {
                    char pre[64];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    snprintf(buf, bufsize, "struct %s%s", pre, sname);
                    return buf;
                }
        }
    }
    if (codegen_current_module && codegen_current_module->struct_defs) {
        for (int i = 0; i < codegen_current_module->num_structs; i++)
            if (codegen_current_module->struct_defs[i]->name && strcmp(codegen_current_module->struct_defs[i]->name, sname) == 0) {
                /* 库模块 -E 时用 codegen_library_prefix（如 ast_），与生成 C 中 struct ast_Type 一致，避免 incomplete type */
                if (codegen_library_prefix && *codegen_library_prefix) {
                    snprintf(buf, bufsize, "struct %s%s", codegen_library_prefix, sname);
                    return buf;
                }
                if (codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                    for (int di = 0; di < codegen_ndep; di++)
                        if (codegen_dep_mods[di] == codegen_current_module) {
                            char pre[64];
                            import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                            snprintf(buf, bufsize, "struct %s%s", pre, sname);
                            return buf;
                        }
                }
                snprintf(buf, bufsize, "struct %s", sname);
                return buf;
            }
    }
    /* 未在 dep/本模块找到时（如 -E 展开时 dep 未设）：按 "mod.Type" → "struct mod_Type" 兜底，与 C 命名一致 */
    if (strchr(sname, '.')) {
        const char *dot = strchr(sname, '.');
        size_t pre_len = (size_t)(dot - sname);
        if (pre_len < bufsize && (pre_len + 2 + strlen(dot + 1)) < bufsize)
            snprintf(buf, bufsize, "struct %.*s_%s", (int)pre_len, sname, dot + 1);
        else
            snprintf(buf, bufsize, "struct %s", sname);
    } else {
        snprintf(buf, bufsize, "struct %s", sname);
    }
    return buf;
}

/** 仅写结构体字面量的 C 名前缀 "(struct X){ "，供 .su 自己实现字段循环时调用；名解析逻辑仍在 C。 */
static int codegen_emit_struct_lit_name_prefix(FILE *out, const struct ASTExpr *e) {
    const char *sname = e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "";
    if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.struct_lit.struct_name) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int sj = 0; sj < d->num_structs; sj++)
                if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, e->value.struct_lit.struct_name) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "(struct %s%s){ ", pre, e->value.struct_lit.struct_name);
                    found = 1;
                    break;
                }
        }
        if (!found) {
            char sname_buf[256];
            library_prefixed_name(e->value.struct_lit.struct_name, sname_buf, sizeof(sname_buf));
            fprintf(out, "(struct %s){ ", sname_buf);
        }
    } else if (codegen_library_prefix && *codegen_library_prefix && e->value.struct_lit.struct_name) {
        char sname_buf[256];
        library_prefixed_name(e->value.struct_lit.struct_name, sname_buf, sizeof(sname_buf));
        fprintf(out, "(struct %s){ ", sname_buf);
    } else if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.struct_lit.struct_name) {
        int found = 0;
        for (int di = 0; di < codegen_ndep && !found; di++) {
            const struct ASTModule *d = codegen_dep_mods[di];
            if (!d || !d->struct_defs) continue;
            for (int sj = 0; sj < d->num_structs; sj++)
                if (d->struct_defs[sj]->name && strcmp(d->struct_defs[sj]->name, e->value.struct_lit.struct_name) == 0) {
                    char pre[256];
                    import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                    fprintf(out, "(struct %s%s){ ", pre, e->value.struct_lit.struct_name);
                    found = 1;
                    break;
                }
        }
        if (!found) fprintf(out, "(struct %s){ ", sname);
    } else {
        fprintf(out, "(struct %s){ ", sname);
    }
    return 0;
}

/** 结构体字面量完整输出（C 路径保留，供非 .su 或 fallback）；字段循环与 .su 自实现一致。
 * 当存在任意数组类型字段时 C 不允许在复合字面量中直接赋数组（含变量或部分字面量），故改用块形式：临时变量 + 逐字段赋值 + memcpy。 */
static int codegen_emit_struct_lit_impl(FILE *out, const struct ASTExpr *e) {
    const char *sname = e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "";
    int use_block = 0;
    for (int i = 0; i < e->value.struct_lit.num_fields && !use_block; i++) {
        const char *fname = e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "";
        const struct ASTType *fty = get_struct_field_type(sname, fname);
        if (fty && fty->kind == AST_TYPE_ARRAY) use_block = 1;
    }
    if (use_block) {
        fprintf(out, "({ ");
        codegen_emit_struct_type_name_only(out, sname);
        fprintf(out, " _t = { 0 }; ");
        /* 先输出所有标量/小字段赋值，再输出 memcpy，避免 memcpy(_t.name, ...) 覆盖栈上相邻变量（如 parser 的 func_name_len_storage）导致 name_len 被破坏。 */
        for (int i = 0; i < e->value.struct_lit.num_fields; i++) {
            const char *fname = e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "";
            const struct ASTType *fty = get_struct_field_type(sname, fname);
            const struct ASTExpr *init = e->value.struct_lit.inits[i];
            if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_VAR && init->value.var.name) {
                /* 数组用 memcpy，放到后面一轮再输出 */
                continue;
            }
            if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_FIELD_ACCESS && init->value.field_access.base) {
                /* 数组字段来自另一结构体字段（如 scan.name），用 memcpy，放到后面一轮再输出 */
                continue;
            }
            if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_ARRAY_LIT && fty->elem_type && fty->elem_type->kind == AST_TYPE_ARRAY) {
                /* 多维数组字面量：C 不能对数组赋值，已由 _t = { 0 } 零初始化，跳过 */
                continue;
            }
            if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_ARRAY_LIT) {
                /* C 不允许 _t.arr = { ... } 赋值，改为逐元素 _t.arr[j] = expr */
                for (int j = 0; j < init->value.array_lit.num_elems; j++) {
                    fprintf(out, "_t.%s[%d] = ", fname, j);
                    if (codegen_expr(init->value.array_lit.elems[j], out) != 0) return -1;
                    fprintf(out, "; ");
                }
                continue;
            }
            fprintf(out, "_t.%s = ", fname);
            if (init && init->kind == AST_EXPR_ARRAY_LIT) {
                fprintf(out, "{ ");
                for (int j = 0; j < init->value.array_lit.num_elems; j++) {
                    if (j) fprintf(out, ", ");
                    if (codegen_expr(init->value.array_lit.elems[j], out) != 0) return -1;
                }
                fprintf(out, " }; ");
            } else if (codegen_expr(init, out) != 0)
                return -1;
            else
                fprintf(out, "; ");
        }
        for (int i = 0; i < e->value.struct_lit.num_fields; i++) {
            const char *fname = e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "";
            const struct ASTType *fty = get_struct_field_type(sname, fname);
            const struct ASTExpr *init = e->value.struct_lit.inits[i];
            if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_VAR && init->value.var.name)
                fprintf(out, "memcpy(_t.%s, %s, sizeof(_t.%s)); ", fname, init->value.var.name, fname);
            else if (fty && fty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_FIELD_ACCESS && init->value.field_access.base) {
                const char *src_field = init->value.field_access.field_name ? init->value.field_access.field_name : "";
                fprintf(out, "memcpy(_t.%s, (", fname);
                if (codegen_expr(init->value.field_access.base, out) != 0) return -1;
                fprintf(out, ").%s, sizeof(_t.%s)); ", src_field, fname);
            }
        }
        fprintf(out, "_t; })");
        return 0;
    }
    if (codegen_emit_struct_lit_name_prefix(out, e) != 0) return -1;
    for (int i = 0; i < e->value.struct_lit.num_fields; i++) {
        if (i) fprintf(out, ", ");
        fprintf(out, ".%s = ", e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "");
        if (e->value.struct_lit.inits[i]->kind == AST_EXPR_ARRAY_LIT) {
            const struct ASTExpr *arr = e->value.struct_lit.inits[i];
            fprintf(out, "{ ");
            for (int j = 0; j < arr->value.array_lit.num_elems; j++) {
                if (j) fprintf(out, ", ");
                if (codegen_expr(arr->value.array_lit.elems[j], out) != 0) return -1;
            }
            fprintf(out, " }");
        } else if (codegen_expr(e->value.struct_lit.inits[i], out) != 0)
            return -1;
    }
    fprintf(out, " }");
    return 0;
}

/** .su 侧仅写 "(struct X){ "，供 .su 自己实现 struct_lit 时调用。 */
int32_t codegen_su_emit_struct_lit_c_name_prefix(uint8_t *out, uint8_t *expr) {
    return codegen_emit_struct_lit_name_prefix((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0;
}

/** .su 侧 STRUCT_LIT 访问器：字段数、第 i 个字段名（ptr/len）、第 i 个初值表达式。 */
int32_t codegen_su_struct_lit_num_fields(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_STRUCT_LIT) ? (int32_t)e->value.struct_lit.num_fields : 0;
}
uint8_t *codegen_su_struct_lit_field_name(uint8_t *expr, int32_t i) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_STRUCT_LIT || !e->value.struct_lit.field_names || i < 0 || i >= e->value.struct_lit.num_fields)
        return (uint8_t *)"";
    return (uint8_t *)(e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "");
}
int32_t codegen_su_struct_lit_field_name_len(uint8_t *expr, int32_t i) {
    const char *fn = (const char *)codegen_su_struct_lit_field_name(expr, i);
    return (int32_t)strlen(fn);
}
uint8_t *codegen_su_struct_lit_init(uint8_t *expr, int32_t i) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_STRUCT_LIT || !e->value.struct_lit.inits || i < 0 || i >= e->value.struct_lit.num_fields)
        return NULL;
    return (uint8_t *)e->value.struct_lit.inits[i];
}

/** .su 侧表达式 kind（AST_EXPR_*），用于 .su 判断是否为 ARRAY_LIT 等。 */
int32_t codegen_su_expr_kind(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return e ? (int32_t)e->kind : -1;
}
int32_t codegen_su_expr_kind_array_lit(void) { return (int32_t)AST_EXPR_ARRAY_LIT; }

/** .su 侧 ARRAY_LIT 访问器：元素个数、第 j 个元素表达式。 */
int32_t codegen_su_array_lit_num_elems(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_ARRAY_LIT) ? (int32_t)e->value.array_lit.num_elems : 0;
}
uint8_t *codegen_su_array_lit_elem(uint8_t *expr, int32_t j) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_ARRAY_LIT || !e->value.array_lit.elems || j < 0 || j >= e->value.array_lit.num_elems)
        return NULL;
    return (uint8_t *)e->value.array_lit.elems[j];
}

/** .su 侧结构体字面量全量输出：供 codegen.su 在未自实现时转调（fallback）。 */
int32_t codegen_su_emit_struct_lit_full(uint8_t *out, uint8_t *expr) {
    return codegen_emit_struct_lit_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0;
}

/** 数组字面量完整输出（供 .su 转调）：slice 或 (elem_ty[]){ ... }。 */
static int codegen_emit_array_lit_impl(FILE *out, const struct ASTExpr *e) {
    const struct ASTType *aty = e->resolved_type;
    const struct ASTType *elem_ty = (aty && (aty->kind == AST_TYPE_ARRAY || aty->kind == AST_TYPE_SLICE)) ? aty->elem_type : NULL;
    if (!elem_ty && e->value.array_lit.num_elems > 0) {
        for (int ei = 0; ei < e->value.array_lit.num_elems && !elem_ty; ei++)
            if (e->value.array_lit.elems[ei]->resolved_type)
                elem_ty = e->value.array_lit.elems[ei]->resolved_type;
    }
    int n = e->value.array_lit.num_elems;
    char elem_ty_buf[64];
    snprintf(elem_ty_buf, sizeof(elem_ty_buf), "%s", elem_ty ? c_type_str(elem_ty) : "uint8_t");
    if (aty && aty->kind == AST_TYPE_SLICE && elem_ty) {
        ensure_slice_struct(aty, out);
        fprintf(out, "(%s){ .data = (%s[]){ ", c_type_str(aty), elem_ty_buf);
        for (int i = 0; i < n; i++) {
            if (i) fprintf(out, ", ");
            if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
        }
        fprintf(out, " }, .length = %d }", n);
        return 0;
    }
    if (aty && aty->kind == AST_TYPE_ARRAY && aty->array_size > 0)
        fprintf(out, "(%s[%d]){ ", elem_ty_buf, aty->array_size);
    else
        fprintf(out, "(%s[]){ ", elem_ty_buf);
    for (int i = 0; i < n; i++) {
        if (i) fprintf(out, ", ");
        if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
    }
    fprintf(out, " }");
    return 0;
}
/** .su 侧数组字面量全量输出：供 codegen.su 在未自实现时转调（fallback）。 */
int32_t codegen_su_emit_array_lit_full(uint8_t *out, uint8_t *expr) {
    return codegen_emit_array_lit_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0;
}

/** .su 侧 ARRAY_LIT 自实现用：是否为 slice 分支（resolved_type 为 SLICE 且有 elem_ty）。 */
int32_t codegen_su_array_lit_is_slice(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_ARRAY_LIT || !e->resolved_type || e->resolved_type->kind != AST_TYPE_SLICE)
        return 0;
    if (e->resolved_type->elem_type) return 1;
    if (e->value.array_lit.num_elems > 0)
        for (int ei = 0; ei < e->value.array_lit.num_elems; ei++)
            if (e->value.array_lit.elems[ei]->resolved_type) return 1;
    return 0;
}

/** .su 侧只写 slice 前缀：ensure_slice_struct + "(slice_ty){ .data = (elem_ty[]){ "。 */
int32_t codegen_su_emit_array_lit_slice_prefix(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    const struct ASTType *aty = e->resolved_type;
    const struct ASTType *elem_ty = (aty && aty->kind == AST_TYPE_SLICE && aty->elem_type) ? aty->elem_type : NULL;
    if (!elem_ty && e->value.array_lit.num_elems > 0)
        for (int ei = 0; ei < e->value.array_lit.num_elems && !elem_ty; ei++)
            if (e->value.array_lit.elems[ei]->resolved_type)
                elem_ty = e->value.array_lit.elems[ei]->resolved_type;
    if (!aty || aty->kind != AST_TYPE_SLICE || !elem_ty) return -1;
    ensure_slice_struct(aty, (FILE *)out);
    char elem_ty_buf[64];
    snprintf(elem_ty_buf, sizeof(elem_ty_buf), "%s", c_type_str(elem_ty));
    fprintf((FILE *)out, "(%s){ .data = (%s[]){ ", c_type_str(aty), elem_ty_buf);
    return 0;
}

/** .su 侧只写 slice 后缀：" }, .length = n }"。 */
int32_t codegen_su_emit_array_lit_slice_suffix(uint8_t *out, int32_t n_elems) {
    fprintf((FILE *)out, " }, .length = %d }", (int)n_elems);
    return 0;
}

/** .su 侧只写数组字面量前缀："(elem_ty[size]){ " 或 "(elem_ty[]){ "。 */
int32_t codegen_su_emit_array_lit_array_prefix(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    const struct ASTType *aty = e->resolved_type;
    const struct ASTType *elem_ty = (aty && (aty->kind == AST_TYPE_ARRAY || aty->kind == AST_TYPE_SLICE)) ? aty->elem_type : NULL;
    if (!elem_ty && e->value.array_lit.num_elems > 0)
        for (int ei = 0; ei < e->value.array_lit.num_elems && !elem_ty; ei++)
            if (e->value.array_lit.elems[ei]->resolved_type)
                elem_ty = e->value.array_lit.elems[ei]->resolved_type;
    char elem_ty_buf[64];
    snprintf(elem_ty_buf, sizeof(elem_ty_buf), "%s", elem_ty ? c_type_str(elem_ty) : "uint8_t");
    if (aty && aty->kind == AST_TYPE_ARRAY && aty->array_size > 0)
        fprintf((FILE *)out, "(%s[%d]){ ", elem_ty_buf, aty->array_size);
    else
        fprintf((FILE *)out, "(%s[]){ ", elem_ty_buf);
    return 0;
}

/** .su 侧只写数组字面量后缀：" }"。 */
int32_t codegen_su_emit_array_lit_array_suffix(uint8_t *out) {
    fprintf((FILE *)out, " }");
    return 0;
}

/** 若 e 为向量二元运算（resolved_type 为 VECTOR），则生成逐分量 op 的复合字面量并返回 0；否则返回 -1（调用方走标量分支）。 */
static int codegen_vector_binop(const struct ASTExpr *e, const char *op, FILE *out) {
    if (!e || !e->resolved_type || e->resolved_type->kind != AST_TYPE_VECTOR
        || !e->resolved_type->elem_type || e->resolved_type->array_size <= 0)
        return -1;
    int lanes = e->resolved_type->array_size;
    const char *tname = vector_c_type_name(e->resolved_type);
    fprintf(out, "(%s){ ", tname);
    for (int i = 0; i < lanes; i++) {
        if (i) fprintf(out, ", ");
        fprintf(out, "(");
        if (codegen_expr(e->value.binop.left, out) != 0) return -1;
        fprintf(out, ").v[%d] %s (", i, op);
        if (codegen_expr(e->value.binop.right, out) != 0) return -1;
        fprintf(out, ").v[%d]", i);
    }
    fprintf(out, " }");
    return 0;
}

/**
 * 输出 const/let 的初始化表达式。block 用于“切片从数组”时查数组长度；可为 NULL（则不解析数组→切片）。
 * 当类型为数组且初值为字面量 0 时输出 {0}；当类型为切片且初值为数组变量时输出 { .data = name, .length = N }。
 */
static int codegen_init(const struct ASTType *ty, const struct ASTExpr *init, FILE *out, const struct ASTBlock *block) {
    if (!init) {
        if (ty && ty->kind == AST_TYPE_VECTOR) { fprintf(out, "{0}"); return 0; }
        return -1;
    }
    if (ty && ty->kind == AST_TYPE_ARRAY && init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
        fprintf(out, "{0}");
        return 0;
    }
    if (ty && ty->kind == AST_TYPE_VECTOR && init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
        fprintf(out, "{0}");
        return 0;
    }
    /* f32/f64：整数字面量 0 生成 0.0f / 0.0；浮点字面量按 resolved_type 加 f 后缀（f32） */
    if (ty && (ty->kind == AST_TYPE_F32 || ty->kind == AST_TYPE_F64) && init) {
        if (init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
            fprintf(out, ty->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            return 0;
        }
        if (init->kind == AST_EXPR_FLOAT_LIT) {
            double v = init->value.float_val;
            if (v == 0.0)
                fprintf(out, init->resolved_type && init->resolved_type->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            else if (init->resolved_type && init->resolved_type->kind == AST_TYPE_F32)
                fprintf(out, "%gf", v);
            else
                fprintf(out, "%g", v);
            return 0;
        }
    }
    if (ty && ty->kind == AST_TYPE_VECTOR && init->kind == AST_EXPR_ARRAY_LIT) {
        struct ASTExpr **elems = init->value.array_lit.elems;
        int num = init->value.array_lit.num_elems;
        fprintf(out, "{ ");
        for (int i = 0; i < num; i++) {
            if (i) fprintf(out, ", ");
            if (codegen_expr(elems[i], out) != 0) return -1;
        }
        fprintf(out, " }");
        return 0;
    }
    /* 数组变量/常量初始化须用 { e1, e2, ... }，不能用 (type[]){ ... }，否则 GCC 报 "array initialized from non-constant array expression"（Clang 可过） */
    /* 多维数组且初值为数组字面量（如 [empty32, ...]）时 C 不允许用变量名做元素初始化，用 { 0 } 零初始化（自举用） */
    if (ty && ty->kind == AST_TYPE_ARRAY && init->kind == AST_EXPR_ARRAY_LIT) {
        if (ty->elem_type && ty->elem_type->kind == AST_TYPE_ARRAY) {
            fprintf(out, "{ 0 }");
            return 0;
        }
        struct ASTExpr **elems = init->value.array_lit.elems;
        int num = init->value.array_lit.num_elems;
        /* 空字面量 [] 表示按声明长度零初始化，C 用 { 0 } 保证整数组为零且兼容 C99 */
        if (num == 0 && ty->array_size > 0) {
            fprintf(out, "{ 0 }");
            return 0;
        }
        fprintf(out, "{ ");
        for (int i = 0; i < num; i++) {
            if (i) fprintf(out, ", ");
            if (codegen_expr(elems[i], out) != 0) return -1;
        }
        fprintf(out, " }");
        return 0;
    }
    /* 切片从数组变量初始化：先查当前 block 的 const/let；若未找到则用 init->resolved_type（typeck 已填，如外层块的 [64]u8） */
    if (ty && ty->kind == AST_TYPE_SLICE && init && init->kind == AST_EXPR_VAR) {
        const char *name = init->value.var.name;
        if (block) {
            for (int i = 0; i < block->num_consts; i++)
                if (block->const_decls[i].name && name && strcmp(block->const_decls[i].name, name) == 0 &&
                    block->const_decls[i].type && block->const_decls[i].type->kind == AST_TYPE_ARRAY) {
                    fprintf(out, "{ .data = %s, .length = %d }", name ? name : "", block->const_decls[i].type->array_size);
                    return 0;
                }
            for (int i = 0; i < block->num_lets; i++)
                if (block->let_decls[i].name && name && strcmp(block->let_decls[i].name, name) == 0 &&
                    block->let_decls[i].type && block->let_decls[i].type->kind == AST_TYPE_ARRAY) {
                    fprintf(out, "{ .data = %s, .length = %d }", name ? name : "", block->let_decls[i].type->array_size);
                    return 0;
                }
        }
        if (init->resolved_type && init->resolved_type->kind == AST_TYPE_ARRAY && init->resolved_type->array_size > 0) {
            fprintf(out, "{ .data = %s, .length = %d }", name ? name : "", init->resolved_type->array_size);
            return 0;
        }
    }
    return codegen_expr(init, out);
}

/** 返回 1 表示类型为整数（用于除零检查：仅整数 / % 时插入运行时检查），0 表示浮点或其它 */
static int is_integer_type(const struct ASTType *ty) {
    if (!ty) return 0;
    switch (ty->kind) {
        case AST_TYPE_I32: case AST_TYPE_U32: case AST_TYPE_I64: case AST_TYPE_U64:
        case AST_TYPE_USIZE: case AST_TYPE_ISIZE: case AST_TYPE_U8: case AST_TYPE_BOOL:
            return 1;
        default: return 0;
    }
}

/**
 * 赋值左端为 FIELD_ACCESS(INDEX(base, idx), field) 时，生成可赋值的 C，避免 (cond?panic:base[idx]).field=z 在 C 中非左值。
 * 生成 (idx 越界 ? (shulang_panic_(1,0), 0) : ((base)[idx].field = right, 0))。成功返回 0，否则 -1。
 */
static int codegen_assign_field_index_lvalue(FILE *out, const struct ASTExpr *left, const struct ASTExpr *right) {
    if (!left || left->kind != AST_EXPR_FIELD_ACCESS) return -1;
    const struct ASTExpr *base = left->value.field_access.base;
    const char *field = left->value.field_access.field_name;
    if (!base || base->kind != AST_EXPR_INDEX || !field) return -1;
    const struct ASTExpr *arr = base->value.index.base;
    const struct ASTExpr *idx = base->value.index.index_expr;
    const struct ASTType *arr_ty = arr ? arr->resolved_type : NULL;
    if (base->index_proven_in_bounds) return -1;
    if (!arr_ty || arr_ty->kind != AST_TYPE_ARRAY || arr_ty->array_size <= 0) return -1;
    int n = (int)arr_ty->array_size;
    fprintf(out, "(");
    if (codegen_expr(idx, out) != 0) return -1;
    fprintf(out, " < 0 || (");
    if (codegen_expr(idx, out) != 0) return -1;
    fprintf(out, ") >= %d ? (shulang_panic_(1, 0), 0) : ((", n);
    if (codegen_expr(arr, out) != 0) return -1;
    fprintf(out, ")[");
    if (codegen_expr(idx, out) != 0) return -1;
    fprintf(out, "].%s = ", field);
    if (codegen_expr(right, out) != 0) return -1;
    fprintf(out, ", 0))");
    return 0;
}

/**
 * 赋值左端为带边界检查的 INDEX 时，生成可赋值的 C 表达式，避免 (cond ? (panic(), x) : y) = z 在 C 中非左值。
 * 生成 (cond ? (shulang_panic_(1,0), 0) : (base[idx] = right, 0))。成功返回 0，非 INDEX 或无可做返回 -1。
 */
static int codegen_assign_index_lvalue(FILE *out, const struct ASTExpr *left, const struct ASTExpr *right) {
    if (!left || left->kind != AST_EXPR_INDEX) return -1;
    const struct ASTExpr *base = left->value.index.base;
    const struct ASTExpr *idx = left->value.index.index_expr;
    const struct ASTType *base_ty = base ? base->resolved_type : NULL;
    if (left->index_proven_in_bounds) return -1;
    if (left->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_SLICE) {
        int use_arrow = expr_is_slice_ptr_param(base);
        const char *da = use_arrow ? ")->" : ").";
        fprintf(out, "(");
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, " < 0 || (size_t)(");
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, ") >= (");
        if (codegen_expr(base, out) != 0) return -1;
        fprintf(out, "%slength ? (shulang_panic_(1, 0), 0) : ((", da);
        if (codegen_expr(base, out) != 0) return -1;
        fprintf(out, "%sdata[", da);
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, "] = ");
        if (codegen_expr(right, out) != 0) return -1;
        fprintf(out, ", 0))");
        return 0;
    }
    if (!left->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size > 0) {
        int n = (int)base_ty->array_size;
        fprintf(out, "(");
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, " < 0 || (");
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, ") >= %d ? (shulang_panic_(1, 0), 0) : ((", n);
        if (codegen_expr(base, out) != 0) return -1;
        fprintf(out, ")[");
        if (codegen_expr(idx, out) != 0) return -1;
        fprintf(out, "] = ");
        if (codegen_expr(right, out) != 0) return -1;
        fprintf(out, ", 0))");
        return 0;
    }
    return -1;
}

/**
 * 将单棵表达式生成 C 表达式写入 out（LIT 输出整数字面量，ADD/SUB 递归输出左 op 右）。
 * 参数：e 表达式根节点，不可为 NULL；out 输出流。返回值：0 成功，-1 不支持的节点类型。副作用：仅写 out。
 */
static int codegen_expr(const struct ASTExpr *e, FILE *out) {
    if (!e || !out) return -1;
    /* CTFE 最小集：仅当表达式类型为标量（整型/布尔/浮点）时才用 const_folded_val；struct 等类型不能当整数输出，否则会生成 return -1094795586 等错误 */
    if (e->const_folded_valid && expr_type_is_foldable_scalar(e)) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_format_int_lit((uint8_t *)out, (int32_t)e->const_folded_val) != 0) return -1;
        return 0;
#else
        fprintf(out, "%d", e->const_folded_val);
        return 0;
#endif
    }
    switch (e->kind) {
        case AST_EXPR_LIT:
#ifdef SHUC_USE_SU_CODEGEN
            /* 整数字面量输出由 .su 侧 codegen_su_format_int_lit 实现（自举 codegen 首块迁入）。 */
            if (codegen_codegen_su_format_int_lit((uint8_t *)out, (int32_t)e->value.int_val) != 0) return -1;
            return 0;
#else
            fprintf(out, "%d", e->value.int_val);
            return 0;
#endif
        case AST_EXPR_FLOAT_LIT: {
#ifdef SHUC_USE_SU_CODEGEN
            int is_f32 = (e->resolved_type && e->resolved_type->kind == AST_TYPE_F32) ? 1 : 0;
            if (codegen_codegen_su_emit_float_lit((uint8_t *)out, (uint8_t *)&e->value.float_val, is_f32) != 0) return -1;
            return 0;
#else
            double v = e->value.float_val;
            if (v == 0.0)
                fprintf(out, e->resolved_type && e->resolved_type->kind == AST_TYPE_F32 ? "0.0f" : "0.0");
            else if (e->resolved_type && e->resolved_type->kind == AST_TYPE_F32)
                fprintf(out, "%gf", v);
            else
                fprintf(out, "%g", v);
            return 0;
#endif
        }
        case AST_EXPR_BOOL_LIT:
#ifdef SHUC_USE_SU_CODEGEN
            /* 布尔字面量输出由 .su 侧 codegen_su_format_bool_lit 实现。 */
            if (codegen_codegen_su_format_bool_lit((uint8_t *)out, e->value.int_val ? 1 : 0) != 0) return -1;
            return 0;
#else
            fprintf(out, "%d", e->value.int_val ? 1 : 0);
            return 0;
#endif
        case AST_EXPR_VAR: {
            const char *name = e->value.var.name ? e->value.var.name : "";
#ifdef SHUC_USE_SU_CODEGEN
            /* 变量名输出由 .su 侧 codegen_su_emit_c_string 逐字节实现。 */
            if (codegen_codegen_su_emit_c_string((uint8_t *)out, (uint8_t *)name, (int32_t)strlen(name)) != 0) return -1;
            return 0;
#else
            fprintf(out, "%s", name);
            return 0;
#endif
        }
        case AST_EXPR_ENUM_VARIANT: {
            /* C 中枚举值为 EnumName_VariantName；跨模块或库模块时加 prefix；结果写入 buf 后由 .su emit_c_string 或 fprintf 输出。 */
            const char *en = e->value.enum_variant.enum_name ? e->value.enum_variant.enum_name : "";
            const char *vn = e->value.enum_variant.variant_name ? e->value.enum_variant.variant_name : "";
            char enum_buf[256];
            int n = 0;
            if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en[0]) {
                for (int di = 0; di < codegen_ndep; di++) {
                    const struct ASTModule *d = codegen_dep_mods[di];
                    if (!d || !d->enum_defs) continue;
                    for (int ej = 0; ej < d->num_enums; ej++)
                        if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                            char pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                            n = snprintf(enum_buf, sizeof(enum_buf), "%s%s_%s", pre, en, vn);
                            goto enum_emit;
                        }
                }
            }
            if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en[0]) {
                for (int di = 0; di < codegen_ndep; di++) {
                    const struct ASTModule *d = codegen_dep_mods[di];
                    if (!d || !d->enum_defs) continue;
                    for (int ej = 0; ej < d->num_enums; ej++)
                        if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                            char pre[256];
                            import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                            n = snprintf(enum_buf, sizeof(enum_buf), "%s%s_%s", pre, en, vn);
                            goto enum_emit;
                        }
                }
            }
            if (codegen_library_prefix && *codegen_library_prefix && en[0])
                n = snprintf(enum_buf, sizeof(enum_buf), "%s%s_%s", codegen_library_prefix, en, vn);
            else
                n = snprintf(enum_buf, sizeof(enum_buf), "%s_%s", en, vn);
        enum_emit:
            if (n <= 0 || (size_t)n >= sizeof(enum_buf)) n = 0;
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_c_string((uint8_t *)out, (uint8_t *)enum_buf, (int32_t)n) != 0) return -1;
            return 0;
#else
            fprintf(out, "%s", enum_buf);
            return 0;
#endif
        }
        case AST_EXPR_ADD: {
            if (codegen_vector_binop(e, "+", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " + "; int nl = codegen_su_expr_needs_compare_parens((uint8_t *)l); int nr = codegen_su_expr_needs_compare_parens((uint8_t *)r); if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)l, (uint8_t *)r, (uint8_t *)op, 3, nl, nr) != 0) return -1; return 0; }
#else
            { int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR); int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR); if (need_l) fprintf(out, "("); if (codegen_expr(l, out) != 0) return -1; if (need_l) fprintf(out, ")"); fprintf(out, " + "); if (need_r) fprintf(out, "("); if (codegen_expr(r, out) != 0) return -1; if (need_r) fprintf(out, ")"); return 0; }
#endif
        }
        case AST_EXPR_SUB: {
            if (codegen_vector_binop(e, "-", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " - "; int nl = codegen_su_expr_needs_compare_parens((uint8_t *)l); int nr = codegen_su_expr_needs_compare_parens((uint8_t *)r); if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)l, (uint8_t *)r, (uint8_t *)op, 3, nl, nr) != 0) return -1; return 0; }
#else
            { int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR); int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR); if (need_l) fprintf(out, "("); if (codegen_expr(l, out) != 0) return -1; if (need_l) fprintf(out, ")"); fprintf(out, " - "); if (need_r) fprintf(out, "("); if (codegen_expr(r, out) != 0) return -1; if (need_r) fprintf(out, ")"); return 0; }
#endif
        }
        case AST_EXPR_MUL: {
            if (codegen_vector_binop(e, "*", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " * "; int nl = codegen_su_expr_needs_addsub_parens((uint8_t *)l); int nr = codegen_su_expr_needs_addsub_parens((uint8_t *)r); if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)l, (uint8_t *)r, (uint8_t *)op, 3, nl, nr) != 0) return -1; return 0; }
#else
            { int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB); int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB); if (need_l) fprintf(out, "("); if (codegen_expr(l, out) != 0) return -1; if (need_l) fprintf(out, ")"); fprintf(out, " * "); if (need_r) fprintf(out, "("); if (codegen_expr(r, out) != 0) return -1; if (need_r) fprintf(out, ")"); return 0; }
#endif
        }
        case AST_EXPR_DIV: {
            if (codegen_vector_binop(e, "/", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
#ifdef SHUC_USE_SU_CODEGEN
            { int is_int = (e->resolved_type && is_integer_type(e->resolved_type)) ? 1 : 0; if (codegen_codegen_su_emit_div_expr((uint8_t *)out, (uint8_t *)l, (uint8_t *)r, is_int) != 0) return -1; return 0; }
#else
            /* 整数除零：运行时检查，除数为 0 时 panic（UB 收窄为定义行为，见 UB与未定义行为.md） */
            if (e->resolved_type && is_integer_type(e->resolved_type)) {
                int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
                int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
                fprintf(out, "(");
                if (need_r) fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                if (need_r) fprintf(out, ")");
                fprintf(out, " == 0 ? (shulang_panic_(1, 0), ");
                if (need_l) fprintf(out, "(");
                if (codegen_expr(l, out) != 0) return -1;
                if (need_l) fprintf(out, ")");
                fprintf(out, ") : (");
                if (need_l) fprintf(out, "(");
                if (codegen_expr(l, out) != 0) return -1;
                if (need_l) fprintf(out, ")");
                fprintf(out, " / ");
                if (need_r) fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                if (need_r) fprintf(out, ")");
                fprintf(out, "))");
                return 0;
            }
            int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
            int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " / ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0;
#endif
        }
        case AST_EXPR_MOD: {
            if (codegen_vector_binop(e, "%%", out) == 0) return 0;
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
#ifdef SHUC_USE_SU_CODEGEN
            { int is_int = (e->resolved_type && is_integer_type(e->resolved_type)) ? 1 : 0; if (codegen_codegen_su_emit_mod_expr((uint8_t *)out, (uint8_t *)l, (uint8_t *)r, is_int) != 0) return -1; return 0; }
#else
            /* 整数取模零：运行时检查（UB 收窄为定义行为） */
            if (e->resolved_type && is_integer_type(e->resolved_type)) {
                fprintf(out, "(");
                if (codegen_expr(r, out) != 0) return -1;
                fprintf(out, " == 0 ? (shulang_panic_(1, 0), ");
                if (codegen_expr(l, out) != 0) return -1;
                fprintf(out, ") : (");
                if (codegen_expr(l, out) != 0) return -1;
                fprintf(out, " %% ");
                if (codegen_expr(r, out) != 0) return -1;
                fprintf(out, "))");
                return 0;
            }
            if (codegen_expr(l, out) != 0) return -1;
            fprintf(out, " %% ");
            if (codegen_expr(r, out) != 0) return -1;
            return 0;
#endif
        }
        case AST_EXPR_SHL:
            if (codegen_vector_binop(e, "<<", out) == 0) return 0;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " << "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " << ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_SHR:
            if (codegen_vector_binop(e, ">>", out) == 0) return 0;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " >> "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >> ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_BITAND:
            if (codegen_vector_binop(e, "&", out) == 0) return 0;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " & "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 3, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " & ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_BITOR:
            if (codegen_vector_binop(e, "|", out) == 0) return 0;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " | "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 3, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " | ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_BITXOR:
            if (codegen_vector_binop(e, "^", out) == 0) return 0;
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " ^ "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 3, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " ^ ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_ASSIGN:
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_assign((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right) != 0) return -1;
            return 0;
#else
            /* 赋值表达式：左端为 FIELD_ACCESS(INDEX) 或 INDEX 时生成可赋值的边界检查形式，避免 (ternary)=z 非左值 */
            fprintf(out, "(");
            if (codegen_assign_field_index_lvalue(out, e->value.binop.left, e->value.binop.right) == 0) {
                fprintf(out, ")");
                return 0;
            }
            if (codegen_assign_index_lvalue(out, e->value.binop.left, e->value.binop.right) == 0) {
                fprintf(out, ")");
                return 0;
            }
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " = ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
#endif
        case AST_EXPR_EQ:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " == "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " == ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_NE:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " != "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " != ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_LT:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " < "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 3, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " < ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_LE:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " <= "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " <= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_GT:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " > "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 3, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " > ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_GE:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " >= "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_LOGAND:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " && "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " && ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_LOGOR:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char op[] = " || "; if (codegen_codegen_su_emit_binop((uint8_t *)out, (uint8_t *)e->value.binop.left, (uint8_t *)e->value.binop.right, (uint8_t *)op, 4, 0, 0) != 0) return -1; return 0; }
#else
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " || ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
#endif
        case AST_EXPR_NEG:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char pre[] = "(-"; if (codegen_codegen_su_emit_unary((uint8_t *)out, (uint8_t *)e->value.unary.operand, (uint8_t *)pre, 2) != 0) return -1; return 0; }
#else
            fprintf(out, "(-");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
#endif
        case AST_EXPR_BITNOT:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char pre[] = "(~"; if (codegen_codegen_su_emit_unary((uint8_t *)out, (uint8_t *)e->value.unary.operand, (uint8_t *)pre, 2) != 0) return -1; return 0; }
#else
            fprintf(out, "(~");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
#endif
        case AST_EXPR_LOGNOT:
#ifdef SHUC_USE_SU_CODEGEN
            { static const char pre[] = "(!"; if (codegen_codegen_su_emit_unary((uint8_t *)out, (uint8_t *)e->value.unary.operand, (uint8_t *)pre, 2) != 0) return -1; return 0; }
#else
            fprintf(out, "(!");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
#endif
        case AST_EXPR_ADDR_OF: {
            /* 取址操作数为 INDEX 且带边界检查时，避免 &(ternary) 在 C 中非法（三元结果为 rvalue）；改为 越界?panic:&(base)[idx] */
            const struct ASTExpr *op = e->value.unary.operand;
            if (op && op->kind == AST_EXPR_INDEX && !op->index_proven_in_bounds && op->value.index.base) {
                const struct ASTExpr *base = op->value.index.base;
                const struct ASTExpr *idx = op->value.index.index_expr;
                const struct ASTType *base_ty = base ? base->resolved_type : NULL;
                if (base_ty && base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size > 0) {
                    int n = (int)base_ty->array_size;
                    fprintf(out, "(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, " < 0 || (");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, ") >= %d ? (shulang_panic_(1, 0), &(", n);
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[0]) : &(");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "])");
                    return 0;
                }
            }
            fprintf(out, "(&(");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, "))");
            return 0;
        }
        case AST_EXPR_DEREF: {
            /* 解引用 *expr → C 的 (*(expr)) */
            fprintf(out, "(*(");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, "))");
            return 0;
        }
        case AST_EXPR_AS: {
            /* 类型转换 expr as type → C 的 (target_type)(expr) */
            const struct ASTType *ty = e->value.as_type.type;
            static char cast_buf[128];
            c_type_to_buf(ty, cast_buf, sizeof(cast_buf));
            fprintf(out, "((%s)(", cast_buf);
            if (codegen_expr(e->value.as_type.operand, out) != 0) return -1;
            fprintf(out, "))");
            return 0;
        }
        case AST_EXPR_IF: {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_if_expr((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            const struct ASTExpr *then_e = e->value.if_expr.then_expr;
            const struct ASTExpr *else_e = e->value.if_expr.else_expr;
            int then_is_block = (then_e && then_e->kind == AST_EXPR_BLOCK);
            int else_is_block = (else_e && else_e->kind == AST_EXPR_BLOCK);
            /* continue/break/return 不能作为表达式求值，需当作“块”生成 { continue; } 等 */
            int then_is_control = (then_e && (then_e->kind == AST_EXPR_CONTINUE || then_e->kind == AST_EXPR_BREAK || then_e->kind == AST_EXPR_RETURN));
            int else_is_control = (else_e && (else_e->kind == AST_EXPR_CONTINUE || else_e->kind == AST_EXPR_BREAK || else_e->kind == AST_EXPR_RETURN));
            then_is_block = then_is_block || then_is_control;
            else_is_block = else_is_block || else_is_control;
            /* then/else 任一为块（含 let/return）或控制流时用 GNU C 语句表达式 + 临时变量，否则用三元运算符 */
            if (then_is_block || else_is_block) {
                const struct ASTType *tmp_ty = e->resolved_type;
                /* 任一分支为表达式且类型为 struct 时，用该类型作 __tmp，避免 __tmp=(struct X){0} 赋给 int32_t */
                if (then_e && !then_is_block && then_e->resolved_type) {
                    const char *s = c_type_str(then_e->resolved_type);
                    if (s && strncmp(s, "struct ", 7) == 0) tmp_ty = then_e->resolved_type;
                }
                /* then 为块（如 if (ref<=0) { return Type{...}; }）且块类型为 struct 时也用上，避免 int __tmp；else 为 null 时赋 (struct X){0} */
                if (then_e && then_is_block && then_e->resolved_type) {
                    const char *s = c_type_str(then_e->resolved_type);
                    if (s && strncmp(s, "struct ", 7) == 0) tmp_ty = then_e->resolved_type;
                }
                /* else 为表达式且为 struct 时用 else 类型作 __tmp；但若 then 已为块且产出 struct（如 return LexerResult），则优先用 then 的类型，避免 __tmp=LexerResult 却赋 (Token){0} */
                if (else_e && !else_is_block && else_e->resolved_type) {
                    const char *s = c_type_str(else_e->resolved_type);
                    if (s && strncmp(s, "struct ", 7) == 0) {
                        const char *cur = tmp_ty ? c_type_str(tmp_ty) : NULL;
                        if (!cur || strncmp(cur, "struct ", 7) != 0 || !then_e || !then_is_block)
                            tmp_ty = else_e->resolved_type;
                    }
                }
                /* else 为嵌套 if 表达式（如 typeck 的 else if (!ref_is_null(ty_t)) { ... } else if (!ref_is_null(ty_e)) { ... }）时，取 else 的 resolved_type，否则会打成 int __tmp 却赋 (struct X){0}；同样不覆盖 then 块已给的 struct */
                if (else_e && else_e->kind == AST_EXPR_IF && else_e->resolved_type) {
                    const char *s = c_type_str(else_e->resolved_type);
                    if (s && strncmp(s, "struct ", 7) == 0) {
                        const char *cur = tmp_ty ? c_type_str(tmp_ty) : NULL;
                        if (!cur || strncmp(cur, "struct ", 7) != 0 || !then_e || !then_is_block)
                            tmp_ty = else_e->resolved_type;
                    }
                }
                const char *tmp_ty_str = tmp_ty ? c_type_str(tmp_ty) : "int32_t";
                /* else 为结构体字面量且 __tmp 类型尚非 struct 时，用 struct 名在 dep/本模块中推定 C 类型串。
                 * 但 then 为块且 tmp_ty 已来自 then（如 return LexerResult）时不要用 else（如 Token）覆盖，否则会生成 LexerResult __tmp = (Token){0}。 */
                if (else_e && !else_is_block && else_e->kind == AST_EXPR_STRUCT_LIT && else_e->value.struct_lit.struct_name
                    && strncmp(tmp_ty_str, "struct ", 7) != 0
                    && !(then_e && then_is_block && tmp_ty == then_e->resolved_type)) {
                    const char *sname = else_e->value.struct_lit.struct_name;
                    static char struct_fallback_ty_buf[128];
                    int found = 0;
                    if (codegen_current_module && codegen_current_module->struct_defs) {
                        for (int i = 0; i < codegen_current_module->num_structs; i++)
                            if (codegen_current_module->struct_defs[i]->name && strcmp(codegen_current_module->struct_defs[i]->name, sname) == 0) {
                                snprintf(struct_fallback_ty_buf, sizeof(struct_fallback_ty_buf), "struct %s", sname);
                                tmp_ty_str = struct_fallback_ty_buf;
                                found = 1;
                                break;
                            }
                    }
                    if (!found && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
                        for (int i = 0; i < codegen_ndep; i++) {
                            const struct ASTModule *d = codegen_dep_mods[i];
                            if (!d || !d->struct_defs) continue;
                            for (int j = 0; j < d->num_structs; j++)
                                if (d->struct_defs[j]->name && strcmp(d->struct_defs[j]->name, sname) == 0) {
                                    char pre[64];
                                    import_path_to_c_prefix(codegen_dep_paths[i], pre, sizeof(pre));
                                    snprintf(struct_fallback_ty_buf, sizeof(struct_fallback_ty_buf), "struct %s%s", pre, sname);
                                    tmp_ty_str = struct_fallback_ty_buf;
                                    found = 1;
                                    break;
                                }
                            if (found) break;
                        }
                    }
                    /* 仍未找到时用 else 的 resolved_type（如 (struct ast_Expr){0} / (struct ast_Type){0}），避免 __tmp 打成 int32_t */
                    if (!found && else_e->resolved_type) {
                        const char *s = c_type_str(else_e->resolved_type);
                        if (s && strncmp(s, "struct ", 7) == 0) {
                            snprintf(struct_fallback_ty_buf, sizeof(struct_fallback_ty_buf), "%s", s);
                            tmp_ty_str = struct_fallback_ty_buf;
                        }
                    }
                    /* typeck 可能未对 struct literal 设 resolved_type，用与发射时一致的 C 类型名推断（如 typeck 中 (Type){0} → struct ast_Type） */
                    if (strncmp(tmp_ty_str, "struct ", 7) != 0) {
                        static char struct_lit_ty_buf[128];
                        if (struct_lit_c_type_str(else_e, struct_lit_ty_buf, sizeof(struct_lit_ty_buf)))
                            tmp_ty_str = struct_lit_ty_buf;
                    }
                }
                /* else 为赋值且 RHS 为结构体字面量（如 (__tmp = (struct ast_Type){0})），从 RHS 推断 __tmp 类型 */
                if (else_e && !else_is_block && strncmp(tmp_ty_str, "struct ", 7) != 0
                    && else_e->kind == AST_EXPR_ASSIGN && else_e->value.binop.right
                    && else_e->value.binop.right->kind == AST_EXPR_STRUCT_LIT) {
                    const struct ASTExpr *rhs = else_e->value.binop.right;
                    if (rhs->resolved_type) {
                        const char *s = c_type_str(rhs->resolved_type);
                        if (s && strncmp(s, "struct ", 7) == 0) {
                            static char assign_rhs_ty_buf[128];
                            snprintf(assign_rhs_ty_buf, sizeof(assign_rhs_ty_buf), "%s", s);
                            tmp_ty_str = assign_rhs_ty_buf;
                        }
                    }
                    if (strncmp(tmp_ty_str, "struct ", 7) != 0 && rhs->value.struct_lit.struct_name) {
                        static char assign_struct_lit_buf[128];
                        if (struct_lit_c_type_str(rhs, assign_struct_lit_buf, sizeof(assign_struct_lit_buf)))
                            tmp_ty_str = assign_struct_lit_buf;
                    }
                }
                /* else 为块且块内仅 __tmp = (struct X){0} 时，从块内推断 __tmp 类型（如 backend EXPR_INDEX 路径） */
                if (else_e && else_is_block && strncmp(tmp_ty_str, "struct ", 7) != 0) {
                    const char *block_ty = struct_type_from_else_block(else_e);
                    if (block_ty) {
                        static char main_if_else_block_ty_buf[128];
                        snprintf(main_if_else_block_ty_buf, sizeof(main_if_else_block_ty_buf), "%s", block_ty);
                        tmp_ty_str = main_if_else_block_ty_buf;
                    }
                }
                /* 最后兜底：else 为嵌套 if 等时递归求其产生的 struct 类型（typeck 可能未设 resolved_type）；then 为块且 tmp_ty 已来自 then 时不覆盖 */
                if (else_e && strncmp(tmp_ty_str, "struct ", 7) != 0 && !(then_e && then_is_block && tmp_ty == then_e->resolved_type)) {
                    static char expr_struct_fallback_buf[128];
                    if (expr_struct_type_str(else_e, expr_struct_fallback_buf, sizeof(expr_struct_fallback_buf)))
                        tmp_ty_str = expr_struct_fallback_buf;
                }
                /* 无 else 且 then 为块（如 if (ref<=0) { return Type{...}; }）时从块内 return 操作数推断 __tmp 类型 */
                if (!else_e && then_e && then_is_block && strncmp(tmp_ty_str, "struct ", 7) != 0) {
                    static char then_block_struct_buf[128];
                    if (expr_struct_type_str(then_e, then_block_struct_buf, sizeof(then_block_struct_buf)))
                        tmp_ty_str = then_block_struct_buf;
                }
                /* c_type_str 对库模块 NAMED 可能返回 "prefix_Type" 无 "struct "，此处统一为 "struct prefix_Type" 以便 C 合法声明；若已是 "enum X" 则不要加 struct。 */
                if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) != 0 && strncmp(tmp_ty_str, "enum ", 5) != 0
                    && e->resolved_type && e->resolved_type->kind == AST_TYPE_NAMED) {
                    static char struct_named_buf[128];
                    snprintf(struct_named_buf, sizeof(struct_named_buf), "struct %s", tmp_ty_str);
                    tmp_ty_str = struct_named_buf;
                }
                /* 带初值避免 -Wuninitialized：标量用 0，struct 用 (type){0} */
                if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0)
                    fprintf(out, "({ %s __tmp = (%s){0}; if (", tmp_ty_str, tmp_ty_str);
                else
                    fprintf(out, "({ %s __tmp = 0; if (", tmp_ty_str ? tmp_ty_str : "int32_t");
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, ") ");
                if (then_is_block) {
                    if (then_e->kind == AST_EXPR_BLOCK) {
                        fprintf(out, "{ ");
                        if (codegen_block_body(then_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                        fprintf(out, " } ");
                    } else if (then_e->kind == AST_EXPR_CONTINUE) {
                        fprintf(out, "{ continue; } ");
                    } else if (then_e->kind == AST_EXPR_BREAK) {
                        fprintf(out, "{ break; } ");
                    } else if (then_e->kind == AST_EXPR_RETURN) {
                        /* return 在语句表达式内：先赋 __tmp 再 return（AST_EXPR_RETURN 用 value.unary.operand）；无操作数时 struct 用 (type){0} */
                        fprintf(out, "{ __tmp = ");
                        if (then_e->value.unary.operand && codegen_expr(then_e->value.unary.operand, out) != 0) return -1;
                        if (!then_e->value.unary.operand) {
                            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                            else fprintf(out, "0");
                        }
                        fprintf(out, "; return __tmp; } ");
                    } else {
                        fprintf(out, "(__tmp = ");
                        if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && !expr_produces_struct_type(then_e))
                            fprintf(out, "(%s){0}", tmp_ty_str);
                        else if (codegen_expr(then_e, out) != 0) return -1;
                        fprintf(out, ") ");
                    }
                } else {
                    fprintf(out, "(__tmp = ");
                    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && !expr_produces_struct_type(then_e))
                        fprintf(out, "(%s){0}", tmp_ty_str);
                    else if (codegen_expr(then_e, out) != 0) return -1;
                    fprintf(out, ") ");
                }
                fprintf(out, "else ");
                if (else_is_block) {
                    if (else_e->kind == AST_EXPR_BLOCK) {
                        fprintf(out, "{ ");
                        if (codegen_block_body(else_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                        fprintf(out, " } ");
                    } else if (else_e->kind == AST_EXPR_CONTINUE) {
                        fprintf(out, "{ continue; } ");
                    } else if (else_e->kind == AST_EXPR_BREAK) {
                        fprintf(out, "{ break; } ");
                    } else if (else_e->kind == AST_EXPR_RETURN) {
                        fprintf(out, "{ __tmp = ");
                        if (else_e->value.unary.operand && codegen_expr(else_e->value.unary.operand, out) != 0) return -1;
                        if (!else_e->value.unary.operand) {
                            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                            else fprintf(out, "0");
                        }
                        fprintf(out, "; return __tmp; } ");
                    } else {
                        fprintf(out, "(__tmp = ");
                        /* then 为块时 codegen_block_body 可能已覆盖静态缓冲区，用 then_e 重新推断 __tmp 类型到局部缓冲，保证 else 发射时类型正确（LexerResult vs Token）。优先从 then_e 推断，不依赖 tmp_ty_str。 */
                        char else_emit_ty_buf[128];
                        const char *else_emit_ty = tmp_ty_str;
                        if (then_e && then_is_block) {
                            if (expr_struct_type_str(then_e, else_emit_ty_buf, sizeof(else_emit_ty_buf)))
                                else_emit_ty = else_emit_ty_buf;
                            else if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) {
                                snprintf(else_emit_ty_buf, sizeof(else_emit_ty_buf), "%s", tmp_ty_str);
                                else_emit_ty = else_emit_ty_buf;
                            }
                        }
                        if (else_e) {
                            /* __tmp 为 struct 时，若 else 类型与 else_emit_ty 不同则输出 (else_emit_ty){0}；先处理结构体字面量（struct_lit_c_type_str 可靠），再统一用 expr_struct_type_str。
                             * LexerResult vs Token：else_emit_ty 可能无 "struct " 前缀（如 lexer_LexerResult），用 strstr 判 LexerResult 且 else 的 C 类型含 Token 则输出 (else_emit_ty){0}；若无前缀则用 "struct "+else_emit_ty。 */
                            if (else_emit_ty && else_e->kind == AST_EXPR_STRUCT_LIT) {
                                static char else_lit_ty[128];
                                const char *else_ctype = struct_lit_c_type_str(else_e, else_lit_ty, sizeof(else_lit_ty));
                                int lexer_result_else_token = (strstr(else_emit_ty, "LexerResult") != NULL && else_ctype && strstr(else_ctype, "Token") != NULL);
                                if (lexer_result_else_token) {
                                    if (strncmp(else_emit_ty, "struct ", 7) == 0) fprintf(out, "(%s){0}", else_emit_ty);
                                    else { static char struct_lex_buf[128]; snprintf(struct_lex_buf, sizeof(struct_lex_buf), "struct %s", else_emit_ty); fprintf(out, "(%s){0}", struct_lex_buf); }
                                } else if (strncmp(else_emit_ty, "struct ", 7) == 0 && else_ctype && strcmp(else_ctype, else_emit_ty) != 0) {
                                    fprintf(out, "(%s){0}", else_emit_ty);
                                } else if (else_struct_type_mismatch(else_emit_ty, else_e))
                                    fprintf(out, "(%s){0}", else_emit_ty);
                                else if (codegen_expr(else_e, out) != 0) return -1;
                            } else {
                                static char else_ty_any[128];
                                const char *else_ty_ptr = expr_struct_type_str(else_e, else_ty_any, sizeof(else_ty_any));
                                if (else_emit_ty && strncmp(else_emit_ty, "struct ", 7) == 0 && else_ty_ptr && strcmp(else_ty_ptr, else_emit_ty) != 0) {
                                    fprintf(out, "(%s){0}", else_emit_ty);
                                } else if (else_emit_ty && else_struct_type_mismatch(else_emit_ty, else_e))
                                    fprintf(out, "(%s){0}", else_emit_ty);
                                else if (codegen_expr(else_e, out) != 0) return -1;
                            }
                        } else {
                            if (else_emit_ty && strncmp(else_emit_ty, "struct ", 7) == 0)
                                fprintf(out, "(%s){0}", else_emit_ty);
                            else if (then_e && then_is_block) {
                                if (else_emit_ty && strstr(else_emit_ty, "LexerResult")) {
                                    static char struct_lex_buf0[128];
                                    snprintf(struct_lex_buf0, sizeof(struct_lex_buf0), "struct %s", else_emit_ty);
                                    fprintf(out, "(%s){0}", struct_lex_buf0);
                                } else if (expr_struct_type_str(then_e, else_emit_ty_buf, sizeof(else_emit_ty_buf)))
                                    fprintf(out, "(%s){0}", else_emit_ty_buf);
                                else
                                    fprintf(out, "0");
                            } else
                                fprintf(out, "0");
                        }
                        fprintf(out, ") ");
                    }
                } else {
                    fprintf(out, "(__tmp = ");
                    /* 同上：then 为块时优先从 then_e 重算类型到局部缓冲 */
                    char else_emit_ty_buf2[128];
                    const char *else_emit_ty2 = tmp_ty_str;
                    if (then_e && then_is_block) {
                        if (expr_struct_type_str(then_e, else_emit_ty_buf2, sizeof(else_emit_ty_buf2)))
                            else_emit_ty2 = else_emit_ty_buf2;
                        else if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) {
                            snprintf(else_emit_ty_buf2, sizeof(else_emit_ty_buf2), "%s", tmp_ty_str);
                            else_emit_ty2 = else_emit_ty_buf2;
                        }
                    }
                    if (else_e) {
                        if (else_emit_ty2 && else_e->kind == AST_EXPR_STRUCT_LIT) {
                            static char else_lit_ty2[128];
                            const char *else_ctype2 = struct_lit_c_type_str(else_e, else_lit_ty2, sizeof(else_lit_ty2));
                            int lexer_result_else_token2 = (strstr(else_emit_ty2, "LexerResult") != NULL && else_ctype2 && strstr(else_ctype2, "Token") != NULL);
                            if (lexer_result_else_token2) {
                                if (strncmp(else_emit_ty2, "struct ", 7) == 0) fprintf(out, "(%s){0}", else_emit_ty2);
                                else { static char struct_lex_buf2[128]; snprintf(struct_lex_buf2, sizeof(struct_lex_buf2), "struct %s", else_emit_ty2); fprintf(out, "(%s){0}", struct_lex_buf2); }
                            } else if (strncmp(else_emit_ty2, "struct ", 7) == 0 && else_ctype2 && strcmp(else_ctype2, else_emit_ty2) != 0)
                                fprintf(out, "(%s){0}", else_emit_ty2);
                            else if (else_struct_type_mismatch(else_emit_ty2, else_e))
                                fprintf(out, "(%s){0}", else_emit_ty2);
                            else if (codegen_expr(else_e, out) != 0) return -1;
                        } else {
                            static char else_ty_any2[128];
                            const char *else_ty_ptr2 = expr_struct_type_str(else_e, else_ty_any2, sizeof(else_ty_any2));
                            if (else_emit_ty2 && strncmp(else_emit_ty2, "struct ", 7) == 0 && else_ty_ptr2 && strcmp(else_ty_ptr2, else_emit_ty2) != 0)
                                fprintf(out, "(%s){0}", else_emit_ty2);
                            else if (else_emit_ty2 && else_struct_type_mismatch(else_emit_ty2, else_e))
                                fprintf(out, "(%s){0}", else_emit_ty2);
                            else if (codegen_expr(else_e, out) != 0) return -1;
                        }
                    } else {
                        if (else_emit_ty2 && strncmp(else_emit_ty2, "struct ", 7) == 0)
                            fprintf(out, "(%s){0}", else_emit_ty2);
                        else if (then_e && then_is_block) {
                            if (else_emit_ty2 && strstr(else_emit_ty2, "LexerResult")) {
                                static char struct_lex_buf02[128];
                                snprintf(struct_lex_buf02, sizeof(struct_lex_buf02), "struct %s", else_emit_ty2);
                                fprintf(out, "(%s){0}", struct_lex_buf02);
                            } else if (expr_struct_type_str(then_e, else_emit_ty_buf2, sizeof(else_emit_ty_buf2)))
                                fprintf(out, "(%s){0}", else_emit_ty_buf2);
                            else
                                fprintf(out, "0");
                        } else
                            fprintf(out, "0");
                    }
                    fprintf(out, ") ");
                }
                fprintf(out, "; __tmp; })");
                return 0;
            }
            /* 若 then 分支为 panic，条件用 __builtin_expect(!!(cond),0) 包裹，使热点路径线性取指（控制流清单 §8.3） */
            int then_is_panic = (then_e && then_e->kind == AST_EXPR_PANIC);
            fprintf(out, "(");
            if (then_is_panic) {
                fprintf(out, "__builtin_expect(!!(");
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, "), 0) ? ");
            } else {
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, " ? ");
            }
            if (codegen_expr(then_e, out) != 0) return -1;
            fprintf(out, " : ");
            if (else_e) {
                if (codegen_expr(else_e, out) != 0) return -1;
            } else {
                fprintf(out, "0");
            }
            fprintf(out, ")");
            return 0;
#endif
        }
        case AST_EXPR_TERNARY: {
            /* cond ? then : else → C 三元运算符 */
#ifdef SHUC_USE_SU_CODEGEN
            { static const char q[] = " ? ", c[] = " : "; fprintf(out, "("); if (codegen_codegen_su_emit_ternary_inner((uint8_t *)out, (uint8_t *)e->value.if_expr.cond, (uint8_t *)e->value.if_expr.then_expr, (uint8_t *)e->value.if_expr.else_expr, (uint8_t *)q, 3, (uint8_t *)c, 3) != 0) return -1; fprintf(out, ")"); return 0; }
#else
            fprintf(out, "(");
            if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
            fprintf(out, " ? ");
            if (codegen_expr(e->value.if_expr.then_expr, out) != 0) return -1;
            fprintf(out, " : ");
            if (codegen_expr(e->value.if_expr.else_expr, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
#endif
        }
        case AST_EXPR_PANIC:
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_panic((uint8_t *)out, e->value.unary.operand ? 1 : 0, (uint8_t *)e->value.unary.operand) != 0) return -1;
            return 0;
#else
            /* 冷路径：通过辅助函数标记 noreturn+cold，避免污染 ICache（控制流清单 §8.3、§8.4） */
            if (e->value.unary.operand) {
                fprintf(out, "shulang_panic_(1, ");
                if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
                fprintf(out, ")");
            } else {
                fprintf(out, "shulang_panic_(0, 0)");
            }
            return 0;
#endif
        case AST_EXPR_FIELD_ACCESS:
            /* 统一由 .su 入口分发：枚举变体转调 C 的 emit_field_access_enum_variant_full，结构体字段由 .su 输出 (base).field */
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_field_access_expr((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            /* Type.Variant 枚举变体（typeck 已设 is_enum_variant）与 base.field 结构体字段（§7.4）；跨模块时用 prefix_Enum_Variant */
            if (e->value.field_access.is_enum_variant && e->value.field_access.base->kind == AST_EXPR_VAR) {
                const char *en = e->value.field_access.base->value.var.name;
                const char *vn = e->value.field_access.field_name;
                if (!codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en) {
                    int found = 0;
                    for (int di = 0; di < codegen_ndep && !found; di++) {
                        const struct ASTModule *d = codegen_dep_mods[di];
                        if (!d || !d->enum_defs) continue;
                        for (int ej = 0; ej < d->num_enums; ej++)
                            if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                                char pre[256];
                                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                                fprintf(out, "%s%s_%s", pre, en, vn ? vn : "");
                                found = 1;
                                break;
                            }
                    }
                    if (found) return 0;
                }
                if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && en) {
                    int found = 0;
                    for (int di = 0; di < codegen_ndep && !found; di++) {
                        const struct ASTModule *d = codegen_dep_mods[di];
                        if (!d || !d->enum_defs) continue;
                        for (int ej = 0; ej < d->num_enums; ej++)
                            if (d->enum_defs[ej]->name && strcmp(d->enum_defs[ej]->name, en) == 0) {
                                char pre[256];
                                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                                fprintf(out, "%s%s_%s", pre, en, vn ? vn : "");
                                found = 1;
                                break;
                            }
                    }
                    if (found) return 0;
                }
                if (codegen_library_prefix && *codegen_library_prefix && en)
                    fprintf(out, "%s%s_%s", codegen_library_prefix, en, vn ? vn : "");
                else
                    fprintf(out, "%s_%s", en ? en : "", vn ? vn : "");
                return 0;
            }
            /* 库模块未做 typeck 时 is_enum_variant 可能为 0；若 base 为当前模块枚举类型名则按枚举变体输出 */
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && codegen_library_module->enum_defs
                && e->value.field_access.base->kind == AST_EXPR_VAR && e->value.field_access.base->value.var.name) {
                const char *en2 = e->value.field_access.base->value.var.name;
                const char *vn2 = e->value.field_access.field_name;
                for (int i = 0; i < codegen_library_module->num_enums; i++)
                    if (codegen_library_module->enum_defs[i]->name && strcmp(codegen_library_module->enum_defs[i]->name, en2) == 0) {
                        fprintf(out, "%s%s_%s", codegen_library_prefix, en2, vn2 ? vn2 : "");
                        return 0;
                    }
            }
            /* 字段访问 base.field；base 为指针、slice 类型或指针/slice 形参时输出 ->（C 中按指针传），否则 .；形参查表弥补 resolved_type 未填。 */
            fprintf(out, "(");
            if (codegen_expr(e->value.field_access.base, out) != 0) return -1;
            if ((e->value.field_access.base->resolved_type && (e->value.field_access.base->resolved_type->kind == AST_TYPE_PTR || e->value.field_access.base->resolved_type->kind == AST_TYPE_SLICE))
                || expr_is_ptr_or_slice_param(e->value.field_access.base))
                fprintf(out, ")->%s", e->value.field_access.field_name ? e->value.field_access.field_name : "");
            else
                fprintf(out, ").%s", e->value.field_access.field_name ? e->value.field_access.field_name : "");
            return 0;
#endif
        case AST_EXPR_STRUCT_LIT: {
#ifdef SHUC_USE_SU_CODEGEN
            /* 直接调 C 的 full 实现，避免 .su 再 extern 回 C；.su 主路径走 emit_expr 占位。 */
            if (codegen_su_emit_struct_lit_full((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            /* 统一走 codegen_emit_struct_lit_impl：含数组字段时用块形式（临时变量 + memcpy），避免 C 复合字面量中数组赋值非法 */
            return codegen_emit_struct_lit_impl(out, e);
#endif
        }
        case AST_EXPR_ARRAY_LIT: {
#ifdef SHUC_USE_SU_CODEGEN
            /* 直接调 C 的 full 实现，避免 .su 再 extern 回 C；.su 主路径走 emit_expr 占位。 */
            if (codegen_su_emit_array_lit_full((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            /* 数组字面量 [e1, e2, ...]：实参期望 slice 时生成 (struct shulang_slice_X){ .data = (elem[]){ ... }, .length = N }，否则 (elem_ty[]){ ... }（文档 §6.2） */
            const struct ASTType *aty = e->resolved_type;
            const struct ASTType *elem_ty = (aty && (aty->kind == AST_TYPE_ARRAY || aty->kind == AST_TYPE_SLICE)) ? aty->elem_type : NULL;
            /* 未从 resolved_type 得到元素类型时（如结构体字面量字段初值未设），用任一首个有类型的元素兜底，避免误用 uint8_t */
            if (!elem_ty && e->value.array_lit.num_elems > 0) {
                for (int ei = 0; ei < e->value.array_lit.num_elems && !elem_ty; ei++)
                    if (e->value.array_lit.elems[ei]->resolved_type)
                        elem_ty = e->value.array_lit.elems[ei]->resolved_type;
            }
            int n = e->value.array_lit.num_elems;
            /* 元素类型字符串存局部缓冲，避免 c_type_str 静态缓冲被后续 c_type_str(aty) 覆盖 */
            char elem_ty_buf[64];
            snprintf(elem_ty_buf, sizeof(elem_ty_buf), "%s", elem_ty ? c_type_str(elem_ty) : "uint8_t");
            if (aty && aty->kind == AST_TYPE_SLICE && elem_ty) {
                ensure_slice_struct(aty, out);
                fprintf(out, "(%s){ .data = (%s[]){ ", c_type_str(aty), elem_ty_buf);
                for (int i = 0; i < n; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
                }
                fprintf(out, " }, .length = %d }", n);
                return 0;
            }
            if (aty && aty->kind == AST_TYPE_ARRAY && aty->array_size > 0)
                fprintf(out, "(%s[%d]){ ", elem_ty_buf, aty->array_size);
            else
                fprintf(out, "(%s[]){ ", elem_ty_buf);
            /* 空字面量 [] 且固定长度时零初始化，C 用 0 填充剩余元素 */
            if (n == 0 && aty && aty->kind == AST_TYPE_ARRAY && aty->array_size > 0)
                fprintf(out, "0");
            else
                for (int i = 0; i < n; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
                }
            fprintf(out, " }");
            return 0;
#endif
        }
        case AST_EXPR_INDEX: {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_index((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            /* 数组 base[i] → (base)[i]；切片 base[i] → (base).data[i]；指针 base[i] → (base)[i]（无界检，与 C 一致） */
            const struct ASTExpr *base = e->value.index.base;
            const struct ASTExpr *idx = e->value.index.index_expr;
            const struct ASTType *base_ty = base->resolved_type;
            int skip_bounds_check = e->index_proven_in_bounds;
            if (base_ty && base_ty->kind == AST_TYPE_PTR && base_ty->elem_type) {
                fprintf(out, "(");
                if (codegen_expr(base, out) != 0) return -1;
                fprintf(out, ")[");
                if (codegen_expr(idx, out) != 0) return -1;
                fprintf(out, "]");
                return 0;
            }
            if (e->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_SLICE) {
                /* 仅形参 slice 在 C 中按指针传用 ->；局部/全局 slice 为 struct 用 .；无当前函数时保守用 . */
                int use_arrow = codegen_current_func && expr_is_slice_ptr_param(base);
                const char *da = use_arrow ? ")->" : ").";
                if (skip_bounds_check) {
                    fprintf(out, "(");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, "%sdata[", da);
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "]");
                } else {
                    fprintf(out, "(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, " < 0 || (size_t)(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, ") >= (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, "%slength ? (shulang_panic_(1, 0), (", da);
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, "%sdata[0]) : (", da);
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, "%sdata[", da);
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "])");
                }
                return 0;
            }
            if (!e->value.index.base_is_slice && base_ty && base_ty->kind == AST_TYPE_ARRAY && base_ty->array_size > 0) {
                if (skip_bounds_check) {
                    fprintf(out, "(");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "]");
                } else {
                    int n = base_ty->array_size;
                    fprintf(out, "(");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, " < 0 || (");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, ") >= %d ? (shulang_panic_(1, 0), (", n);
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[0]) : (");
                    if (codegen_expr(base, out) != 0) return -1;
                    fprintf(out, ")[");
                    if (codegen_expr(idx, out) != 0) return -1;
                    fprintf(out, "])");
                }
                return 0;
            }
            /* 仅形参 slice 在 C 中按指针传用 ->；局部 slice 为 struct 用 . */
            fprintf(out, "(");
            if (codegen_expr(base, out) != 0) return -1;
            if (e->value.index.base_is_slice) {
                int use_arrow = expr_is_slice_ptr_param(base);
                fprintf(out, ")%sdata[", use_arrow ? "->" : ".");
            } else
                fprintf(out, ")[");
            if (codegen_expr(idx, out) != 0) return -1;
            fprintf(out, "]");
            return 0;
#endif
        }
        case AST_EXPR_CALL: {
            /* 统一由 .su 入口 codegen_su_emit_call_expr 分发：import_path / library_same / library_dep / mono 转调 C 的 full，否则 fallback callee(args)。 */
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_call_expr((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            if (e->value.call.resolved_import_path && e->value.call.resolved_callee_func) {
                if (codegen_emit_call_import_path_impl(out, e) != 0) return -1;
                return 0;
            }
            if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && e->value.call.callee->kind == AST_EXPR_VAR) {
                if (codegen_emit_call_library_same_impl(out, e) == 0) return 0;
            }
            if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.call.callee->kind == AST_EXPR_VAR) {
                if (codegen_emit_call_library_dep_impl(out, e) == 0) return 0;
            }
            if (e->value.call.num_type_args > 0 && codegen_current_module && e->value.call.callee->kind == AST_EXPR_VAR) {
                if (codegen_emit_call_mono_impl(out, e) == 0) return 0;
            }
            if (codegen_expr(e->value.call.callee, out) != 0) return -1;
            fprintf(out, "(");
            for (int i = 0; i < e->value.call.num_args; i++) {
                if (i) fprintf(out, ", ");
                if (codegen_emit_one_call_arg(out, e->value.call.args[i]) != 0) return -1;
            }
            fprintf(out, ")");
            return 0;
#endif
        }
        case AST_EXPR_METHOD_CALL: {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_method_call((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            struct ASTFunc *impl_func = e->value.method_call.resolved_impl_func;
            if (!impl_func) {
                fprintf(stderr, "codegen error: method call not resolved\n");
                return -1;
            }
            /* module.func 形式：resolved_import_path 已由 typeck 填写，仅出 prefix+name(args)，不出 base */
            if (e->value.method_call.resolved_import_path) {
                char pre[256];
                import_path_to_c_prefix(e->value.method_call.resolved_import_path, pre, sizeof(pre));
                fprintf(out, "%s%s(", pre, impl_func->name ? impl_func->name : "");
                for (int i = 0; i < e->value.method_call.num_args; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_emit_one_call_arg(out, e->value.method_call.args[i]) != 0) return -1;
                }
                fprintf(out, ")");
                return 0;
            }
            fprintf(out, "%s(", impl_method_c_name(impl_func));
            if (codegen_expr(e->value.method_call.base, out) != 0) return -1;
            for (int i = 0; i < e->value.method_call.num_args; i++) {
                fprintf(out, ", ");
                if (codegen_expr(e->value.method_call.args[i], out) != 0) return -1;
            }
            fprintf(out, ")");
            return 0;
#endif
        }
        case AST_EXPR_MATCH: {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_match((uint8_t *)out, (uint8_t *)e) != 0) return -1;
            return 0;
#else
            /* 按控制流清单 §8.6：密度 > 0.7 时生成 switch，否则三元链；支持整数字面量与枚举变体（§7.4） */
            const struct ASTExpr *me = e->value.match_expr.matched_expr;
            const struct ASTMatchArm *arms = e->value.match_expr.arms;
            int num_arms = e->value.match_expr.num_arms;
            int value_min = INT_MAX, value_max = INT_MIN, lit_count = 0;
            for (int i = 0; i < num_arms; i++) {
                if (arms[i].is_wildcard) continue;
                int v = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                lit_count++;
                if (v < value_min) value_min = v;
                if (v > value_max) value_max = v;
            }
            int range = (value_max >= value_min) ? (value_max - value_min + 1) : 0;
            double density = (range > 0 && lit_count > 0) ? (double)lit_count / (double)range : 0.0;
            int use_switch = (density > 0.7 && lit_count > 0);

            if (use_switch) {
                int id = codegen_match_id++;
                fprintf(out, "({ int _su_m%d = (", id);
                if (codegen_expr(me, out) != 0) return -1;
                fprintf(out, "); int _su_r; switch (_su_m%d) { ", id);
                for (int i = 0; i < num_arms; i++) {
                    if (arms[i].is_wildcard) {
                        fprintf(out, "default: _su_r = (");
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        fprintf(out, "); break; ");
                        break;
                    }
                    {
                        int case_val = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                        fprintf(out, "case %d: _su_r = (", case_val);
                    }
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                    fprintf(out, "); break; ");
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, "default: _su_r = 0; break; ");
                fprintf(out, "} _su_r; })");
            } else {
                fprintf(out, "(");
                for (int i = 0; i < num_arms; i++) {
                    if (i) fprintf(out, " : ");
                    if (arms[i].is_wildcard) {
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        break;
                    }
                    {
                        int cmp_val = arms[i].is_enum_variant ? arms[i].variant_index : arms[i].lit_val;
                        fprintf(out, "(");
                        if (codegen_expr(me, out) != 0) return -1;
                        fprintf(out, ") == %d ? ", cmp_val);
                    }
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, " : 0");
                fprintf(out, ")");
            }
            return 0;
#endif
        }
        case AST_EXPR_BLOCK:
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_block_expr((uint8_t *)out, (uint8_t *)e->value.block) != 0) return -1;
            return 0;
#else
            /* 块表达式单独出现时（少见）：GNU C 语句表达式，块体后补 0 作为值 */
            fprintf(out, "({ ");
            if (codegen_block_body(e->value.block, 2, out, 0, NULL) != 0) return -1;
            fprintf(out, " 0; })");
            return 0;
#endif
        default:
            fprintf(stderr, "codegen error: unhandled expression kind %d\n", (int)e->kind);
            return -1;
    }
}

/** 输出单次调用的一个实参：slice 值包 &(...)，slice 指针形参不包。 */
static int codegen_emit_one_call_arg(FILE *out, const struct ASTExpr *arg) {
    int is_slice_val = (arg && arg->resolved_type && arg->resolved_type->kind == AST_TYPE_SLICE);
    int is_slice_ptr_param = is_slice_val && expr_is_slice_ptr_param(arg);
    if (is_slice_val && !is_slice_ptr_param) {
        fprintf(out, "&(");
        if (codegen_expr(arg, out) != 0) return -1;
        fprintf(out, ")");
    } else if (codegen_expr(arg, out) != 0)
        return -1;
    return 0;
}

/** CALL 跨模块（import 解析）：prefix + name(args)；经 builtin_intrinsic_name 映射后可变为 __builtin_memcpy 等。 */
static int codegen_emit_call_import_path_impl(FILE *out, const struct ASTExpr *e) {
    char pre[256];
    import_path_to_c_prefix(e->value.call.resolved_import_path, pre, sizeof(pre));
    const struct ASTFunc *f = e->value.call.resolved_callee_func;
    char full_name[256];
    if (e->value.call.num_type_args > 0 && e->value.call.type_args)
        (void)snprintf(full_name, sizeof(full_name), "%s%s", pre, mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args));
    else
        (void)snprintf(full_name, sizeof(full_name), "%s%s", pre, f->name ? f->name : "");
    fprintf(out, "%s(", builtin_intrinsic_name(full_name));
    for (int i = 0; i < e->value.call.num_args; i++) {
        if (i) fprintf(out, ", ");
        if (codegen_emit_one_call_arg(out, e->value.call.args[i]) != 0) return -1;
    }
    fprintf(out, ")");
    return 0;
}

/** CALL 库模块内同模块：前缀名 + args。 */
static int codegen_emit_call_library_same_impl(FILE *out, const struct ASTExpr *e) {
    const char *callee_name = e->value.call.callee->value.var.name;
    const struct ASTFunc *f = NULL;
    for (int i = 0; i < codegen_library_module->num_funcs && codegen_library_module->funcs; i++) {
        if (!codegen_library_module->funcs[i]) continue;
        if (codegen_library_module->funcs[i]->name && callee_name && strcmp(codegen_library_module->funcs[i]->name, callee_name) == 0) {
            f = codegen_library_module->funcs[i];
            break;
        }
    }
    if (!f || f->is_extern) return -1;
    char cname[256];
    if (e->value.call.num_type_args > 0 && e->value.call.type_args)
        library_prefixed_name(mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args), cname, sizeof(cname));
    else
        library_prefixed_name(f->name ? f->name : "", cname, sizeof(cname));
    fprintf(out, "%s(", builtin_intrinsic_name(cname));
    for (int i = 0; i < e->value.call.num_args; i++) {
        if (i) fprintf(out, ", ");
        if (codegen_emit_one_call_arg(out, e->value.call.args[i]) != 0) return -1;
    }
    fprintf(out, ")");
    return 0;
}

/** CALL 库模块内跨模块（依赖）：dep_prefix + name(args)。 */
static int codegen_emit_call_library_dep_impl(FILE *out, const struct ASTExpr *e) {
    const char *callee_name = e->value.call.callee->value.var.name;
    if (!callee_name) return -1;
    for (int di = 0; di < codegen_ndep; di++) {
        const struct ASTModule *dm = codegen_dep_mods[di];
        if (!dm || !dm->funcs) continue;
        for (int fi = 0; fi < dm->num_funcs; fi++) {
            if (!dm->funcs[fi]) continue;
            if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) {
                char pre[256];
                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                char full_name[256];
                (void)snprintf(full_name, sizeof(full_name), "%s%s", pre, callee_name);
                fprintf(out, "%s(", builtin_intrinsic_name(full_name));
                for (int i = 0; i < e->value.call.num_args; i++) {
                    if (i) fprintf(out, ", ");
                    if (codegen_emit_one_call_arg(out, e->value.call.args[i]) != 0) return -1;
                }
                fprintf(out, ")");
                return 0;
            }
        }
    }
    return -1;
}

/** CALL 入口模块泛型单态化：builtin_intrinsic_name(mono_mangled)(args)。 */
static int codegen_emit_call_mono_impl(FILE *out, const struct ASTExpr *e) {
    const char *callee_name = e->value.call.callee->value.var.name;
    const struct ASTFunc *func = NULL;
    for (int i = 0; i < codegen_current_module->num_funcs; i++) {
        if (!codegen_current_module->funcs[i]) continue;
        if (codegen_current_module->funcs[i]->name && callee_name
            && strcmp(codegen_current_module->funcs[i]->name, callee_name) == 0) {
            func = codegen_current_module->funcs[i];
            break;
        }
    }
    if (!func || !codegen_current_module->mono_instances) return -1;
    for (int k = 0; k < codegen_current_module->num_mono_instances; k++) {
        if (codegen_current_module->mono_instances[k].template != func) continue;
        if (codegen_current_module->mono_instances[k].num_type_args != e->value.call.num_type_args) continue;
        int eq = 1;
        for (int j = 0; j < e->value.call.num_type_args; j++) {
            if (!type_equal(codegen_current_module->mono_instances[k].type_args[j], e->value.call.type_args[j])) { eq = 0; break; }
        }
        if (eq) {
            fprintf(out, "%s(", builtin_intrinsic_name(mono_instance_mangled_name(func, e->value.call.type_args, e->value.call.num_type_args)));
            for (int i = 0; i < e->value.call.num_args; i++) {
                if (i) fprintf(out, ", ");
                if (codegen_emit_one_call_arg(out, e->value.call.args[i]) != 0) return -1;
            }
            fprintf(out, ")");
            return 0;
        }
    }
    return -1;
}

/** .su 侧 CALL 分发：1=import_path，2=library_same，3=library_dep，4=mono，0=fallback。供 codegen.su 的 emit_call_expr 统一入口。 */
int32_t codegen_su_call_dispatch_kind(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL) return 0;
    if (e->value.call.resolved_import_path && e->value.call.resolved_callee_func) return 1;
    if (codegen_library_prefix && *codegen_library_prefix && codegen_library_module && e->value.call.callee && e->value.call.callee->kind == AST_EXPR_VAR) {
        const char *callee_name = e->value.call.callee->value.var.name;
        for (int i = 0; i < codegen_library_module->num_funcs && codegen_library_module->funcs; i++) {
            if (!codegen_library_module->funcs[i]) continue;
            if (codegen_library_module->funcs[i]->name && callee_name && strcmp(codegen_library_module->funcs[i]->name, callee_name) == 0) {
                if (!codegen_library_module->funcs[i]->is_extern) return 2;
                break;
            }
        }
    }
    if (codegen_library_prefix && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths && e->value.call.callee && e->value.call.callee->kind == AST_EXPR_VAR && e->value.call.callee->value.var.name) {
        const char *callee_name = e->value.call.callee->value.var.name;
        for (int di = 0; di < codegen_ndep; di++) {
            const struct ASTModule *dm = codegen_dep_mods[di];
            if (!dm || !dm->funcs) continue;
            for (int fi = 0; fi < dm->num_funcs; fi++) {
                if (!dm->funcs[fi]) continue;
                if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) return 3;
            }
        }
    }
    if (e->value.call.num_type_args > 0 && codegen_current_module && e->value.call.callee && e->value.call.callee->kind == AST_EXPR_VAR) {
        const char *callee_name = e->value.call.callee->value.var.name;
        const struct ASTFunc *func = NULL;
        for (int i = 0; i < codegen_current_module->num_funcs; i++) {
            if (!codegen_current_module->funcs[i]) continue;
            if (codegen_current_module->funcs[i]->name && callee_name && strcmp(codegen_current_module->funcs[i]->name, callee_name) == 0) {
                func = codegen_current_module->funcs[i];
                break;
            }
        }
        if (func && codegen_current_module->mono_instances) {
            for (int k = 0; k < codegen_current_module->num_mono_instances; k++) {
                if (codegen_current_module->mono_instances[k].template != func) continue;
                if (codegen_current_module->mono_instances[k].num_type_args != e->value.call.num_type_args) continue;
                int eq = 1;
                for (int j = 0; j < e->value.call.num_type_args; j++) {
                    if (!type_equal(codegen_current_module->mono_instances[k].type_args[j], e->value.call.type_args[j])) { eq = 0; break; }
                }
                if (eq) return 4;
            }
        }
    }
    return 0;
}

/** .su 自实现 CALL 用：仅将「调用目标」prefix+name 写入 out，不写 '(' 与实参。返回 0 成功，-1 失败。 */
int32_t codegen_su_emit_call_import_path_target(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL || !e->value.call.resolved_import_path || !e->value.call.resolved_callee_func) return -1;
    char pre[256];
    import_path_to_c_prefix(e->value.call.resolved_import_path, pre, sizeof(pre));
    const struct ASTFunc *f = e->value.call.resolved_callee_func;
    const char *name = (e->value.call.num_type_args > 0 && e->value.call.type_args)
        ? mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args) : (f->name ? f->name : "");
    fprintf((FILE *)out, "%s%s", pre, name);
    return 0;
}
int32_t codegen_su_emit_call_library_same_target(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL || !codegen_library_prefix || !*codegen_library_prefix || !codegen_library_module
        || !e->value.call.callee || e->value.call.callee->kind != AST_EXPR_VAR) return -1;
    const char *callee_name = e->value.call.callee->value.var.name;
    const struct ASTFunc *f = NULL;
    for (int i = 0; i < codegen_library_module->num_funcs && codegen_library_module->funcs; i++) {
        if (!codegen_library_module->funcs[i]) continue;
        if (codegen_library_module->funcs[i]->name && callee_name && strcmp(codegen_library_module->funcs[i]->name, callee_name) == 0) {
            f = codegen_library_module->funcs[i];
            break;
        }
    }
    if (!f || f->is_extern) return -1;
    char cname[256];
    if (e->value.call.num_type_args > 0 && e->value.call.type_args)
        library_prefixed_name(mono_instance_mangled_name(f, e->value.call.type_args, e->value.call.num_type_args), cname, sizeof(cname));
    else
        library_prefixed_name(f->name ? f->name : "", cname, sizeof(cname));
    fprintf((FILE *)out, "%s", cname);
    return 0;
}
int32_t codegen_su_emit_call_library_dep_target(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL || !codegen_ndep || !codegen_dep_mods || !codegen_dep_paths
        || !e->value.call.callee || e->value.call.callee->kind != AST_EXPR_VAR) return -1;
    const char *callee_name = e->value.call.callee->value.var.name;
    if (!callee_name) return -1;
    for (int di = 0; di < codegen_ndep; di++) {
        const struct ASTModule *dm = codegen_dep_mods[di];
        if (!dm || !dm->funcs) continue;
        for (int fi = 0; fi < dm->num_funcs; fi++) {
            if (!dm->funcs[fi]) continue;
            if (dm->funcs[fi]->name && strcmp(dm->funcs[fi]->name, callee_name) == 0) {
                char pre[256];
                import_path_to_c_prefix(codegen_dep_paths[di], pre, sizeof(pre));
                fprintf((FILE *)out, "%s%s", pre, callee_name);
                return 0;
            }
        }
    }
    return -1;
}
int32_t codegen_su_emit_call_mono_target(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_CALL || !codegen_current_module || !e->value.call.callee || e->value.call.callee->kind != AST_EXPR_VAR) return -1;
    const char *callee_name = e->value.call.callee->value.var.name;
    const struct ASTFunc *func = NULL;
    for (int i = 0; i < codegen_current_module->num_funcs; i++) {
        if (!codegen_current_module->funcs[i]) continue;
        if (codegen_current_module->funcs[i]->name && callee_name && strcmp(codegen_current_module->funcs[i]->name, callee_name) == 0) {
            func = codegen_current_module->funcs[i];
            break;
        }
    }
    if (!func || !codegen_current_module->mono_instances) return -1;
    for (int k = 0; k < codegen_current_module->num_mono_instances; k++) {
        if (codegen_current_module->mono_instances[k].template != func) continue;
        if (codegen_current_module->mono_instances[k].num_type_args != e->value.call.num_type_args) continue;
        int eq = 1;
        for (int j = 0; j < e->value.call.num_type_args; j++) {
            if (!type_equal(codegen_current_module->mono_instances[k].type_args[j], e->value.call.type_args[j])) { eq = 0; break; }
        }
        if (eq) {
            fprintf((FILE *)out, "%s", builtin_intrinsic_name(mono_instance_mangled_name(func, e->value.call.type_args, e->value.call.num_type_args)));
            return 0;
        }
    }
    return -1;
}

int32_t codegen_su_emit_call_import_path_full(uint8_t *out, uint8_t *expr) { return codegen_emit_call_import_path_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0; }
int32_t codegen_su_emit_call_library_same_full(uint8_t *out, uint8_t *expr) { return codegen_emit_call_library_same_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0; }
int32_t codegen_su_emit_call_library_dep_full(uint8_t *out, uint8_t *expr) { return codegen_emit_call_library_dep_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0; }
int32_t codegen_su_emit_call_mono_full(uint8_t *out, uint8_t *expr) { return codegen_emit_call_mono_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0; }

/** 阶段 8.1 块内 DCE 前向声明：收集块内被引用变量名、判断是否在 used 集合中。 */
static void collect_var_names_from_block(const struct ASTBlock *b, const char **out, int *n, int max);
static int is_var_used(const char *name, const char **used, int n_used);

/**
 * 按逆序生成执行本块所有 defer 块的 C 代码（块退出时执行）。
 * 参数：out 输出流；b 当前块（含 defer_blocks）；indent 缩进（2 或 4）。
 */
static int codegen_run_defers(FILE *out, const struct ASTBlock *b, int indent) {
    if (!b || !out || !b->defer_blocks) return 0;
    for (int i = b->num_defers - 1; i >= 0; i--) {
        if (codegen_block_body(b->defer_blocks[i], indent, out, 0, NULL) != 0) return -1;
    }
    return 0;
}

/**
 * 将块体生成到 out：const/let 声明（带 indent 空格缩进），再 labeled_stmts（label/goto/return）、run_defers，再 final_expr。
 * 若 final_expr 为 break/continue/return/panic 则生成对应语句，否则 (void)(final_expr); 或 final_result_var = (expr);（当 final_result_var 非 NULL 时）。
 * 用于 main 块或 while 体；indent 为每行前空格数（如 2 或 4）。final_result_var 用于 if-expr 的 then/else 块，将块结果赋给该变量（如 "__tmp"）。
 */
#define MAX_BLOCK_USED_VARS 128

static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out, int cast_return_to_int, const char *final_result_var) {
    if (!b || !out) return -1;
    const char *pad = (indent == 2) ? "  " : (indent == 4) ? "    " : "      ";
    /* 阶段 8.1 块内 DCE：仅输出被引用的 const/let */
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    /* 有 stmt_order 时一律按源码顺序输出 const/let/expr/loop/for，保证 skip_whitespace 等「while; continue」与 copy_onefunc_into「let; while; expr」顺序正确。 */
    int use_stmt_order = (b->num_stmt_order > 0) ? 1 : 0;
#ifdef SHUC_USE_SU_CODEGEN
    if (b->num_stmt_order > 0 && use_stmt_order) {
        if (codegen_codegen_su_emit_block_stmt_order((uint8_t *)out, (uint8_t *)b, indent, cast_return_to_int) != 0) return -1;
    } else {
#else
    if (b->num_stmt_order > 0 && use_stmt_order) {
        for (int i = 0; i < b->num_stmt_order; i++) {
            int k = (int)b->stmt_order[i].kind;
            int idx = b->stmt_order[i].idx;
            switch (k) {
            case 0: { /* const */
                if (idx >= b->num_consts) break;
                const char *name = b->const_decls[idx].name ? b->const_decls[idx].name : "";
                if (!is_var_used(name, used_buf, n_used)) break;
                const struct ASTType *ty = b->const_decls[idx].type;
                const struct ASTExpr *cinit = b->const_decls[idx].init;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                    fprintf(out, "%sconst ", pad);
                    emit_local_array_decl(ety, name, "", out);
                    if (cinit && cinit->kind == AST_EXPR_VAR && cinit->value.var.name) {
                        fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, cinit->value.var.name, name);
                        break;
                    }
                    if (cinit && cinit->kind == AST_EXPR_LIT && cinit->value.int_val == 0) {
                        fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                        break;
                    }
                    if (cinit && cinit->kind != AST_EXPR_ARRAY_LIT) {
                        fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                        if (codegen_expr(cinit, out) != 0) return -1;
                        fprintf(out, "), sizeof(%s));\n", name);
                        break;
                    }
                    fprintf(out, "= ");
                } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%sconst %s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, cinit, out, b) != 0) return -1;
                fprintf(out, ";\n");
                break;
            }
            case 1: { /* let */
                if (idx >= b->num_lets) break;
                const char *name = b->let_decls[idx].name ? b->let_decls[idx].name : "";
                if (!is_var_used(name, used_buf, n_used)) break;
                const struct ASTType *ty = b->let_decls[idx].type;
                const struct ASTExpr *linit = b->let_decls[idx].init;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%s%s * %s = ", pad, c_type_str(ety->elem_type), name);
                else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                    fprintf(out, "%s", pad);
                    emit_local_array_decl(ety, name, "", out);
                    if (linit && linit->kind == AST_EXPR_VAR && linit->value.var.name) {
                        fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, linit->value.var.name, name);
                        break;
                    }
                    if (linit && linit->kind == AST_EXPR_LIT && linit->value.int_val == 0) {
                        fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                        break;
                    }
                    if (linit && linit->kind != AST_EXPR_ARRAY_LIT) {
                        fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                        if (codegen_expr(linit, out) != 0) return -1;
                        fprintf(out, "), sizeof(%s));\n", name);
                        break;
                    }
                    fprintf(out, "= ");
                } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, linit, out, b) != 0) return -1;
                fprintf(out, ";\n");
                break;
            }
            case 2: { /* expr_stmt */
                if (idx >= b->num_expr_stmts) break;
                const struct ASTExpr *st = b->expr_stmts[idx];
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) {
                    if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); }
                    else fprintf(out, "%sreturn;\n", pad);
                } else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
                break;
            }
            case 3: /* loop */
                if (idx < b->num_loops) {
                    fprintf(out, "%swhile (", pad);
                    if (codegen_expr(b->loops[idx].cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    if (codegen_block_body(b->loops[idx].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                    fprintf(out, "%s}\n", pad);
                }
                break;
            case 4: /* for */
                if (idx < b->num_for_loops) {
                    fprintf(out, "%sfor (", pad);
                    if (b->for_loops[idx].init) { if (codegen_expr(b->for_loops[idx].init, out) != 0) return -1; }
                    fprintf(out, "; ");
                    if (b->for_loops[idx].cond) { if (codegen_expr(b->for_loops[idx].cond, out) != 0) return -1; }
                    fprintf(out, "; ");
                    if (b->for_loops[idx].step) { if (codegen_expr(b->for_loops[idx].step, out) != 0) return -1; }
                    fprintf(out, ") {\n");
                    if (codegen_block_body(b->for_loops[idx].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                    fprintf(out, "%s}\n", pad);
                }
                break;
            }
        }
    } else {
#endif
        /* 无 stmt_order：原逻辑 — const → early lets → expr/loops → late lets */
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_block_const_decls((uint8_t *)out, (uint8_t *)b, indent) != 0) return -1;
        int n_early = (b->num_early_lets > 0 && b->num_early_lets <= b->num_lets) ? b->num_early_lets : b->num_lets;
        if (codegen_codegen_su_emit_block_let_decls_range((uint8_t *)out, (uint8_t *)b, indent, 0, (int32_t)n_early) != 0) return -1;
#else
        for (int i = 0; i < b->num_consts; i++) {
            const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
            if (!is_var_used(name, used_buf, n_used)) continue;
            const struct ASTType *ty = b->const_decls[i].type;
            const struct ASTExpr *cinit = b->const_decls[i].init;
            const struct ASTType *ety = codegen_emit_type(ty);
            if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
            else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                fprintf(out, "%sconst ", pad);
                emit_local_array_decl(ety, name, "", out);
                if (cinit && cinit->kind == AST_EXPR_VAR && cinit->value.var.name) {
                    fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, cinit->value.var.name, name);
                    continue;
                }
                if (cinit && cinit->kind == AST_EXPR_LIT && cinit->value.int_val == 0) {
                    fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                    continue;
                }
                if (cinit && cinit->kind != AST_EXPR_ARRAY_LIT) {
                    fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                    if (codegen_expr(cinit, out) != 0) return -1;
                    fprintf(out, "), sizeof(%s));\n", name);
                    continue;
                }
                fprintf(out, "= ");
            } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name); }
            else { fprintf(out, "%sconst %s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name); }
            if (codegen_init(ty, cinit, out, b) != 0) return -1;
            fprintf(out, ";\n");
        }
        int n_early = (b->num_early_lets > 0 && b->num_early_lets <= b->num_lets) ? b->num_early_lets : b->num_lets;
        for (int i = 0; i < n_early; i++) {
            const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
            if (!is_var_used(name, used_buf, n_used)) continue;
            const struct ASTType *ty = b->let_decls[i].type;
            const struct ASTExpr *linit = b->let_decls[i].init;
            const struct ASTType *ety = codegen_emit_type(ty);
            if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%s%s * %s = ", pad, c_type_str(ety->elem_type), name);
            else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
            else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                fprintf(out, "%s", pad);
                emit_local_array_decl(ety, name, "", out);
                if (linit && linit->kind == AST_EXPR_VAR && linit->value.var.name) {
                    fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, linit->value.var.name, name);
                    continue;
                }
                if (linit && linit->kind != AST_EXPR_ARRAY_LIT) {
                    fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                    if (codegen_expr(linit, out) != 0) return -1;
                    fprintf(out, "), sizeof(%s));\n", name);
                    continue;
                }
                fprintf(out, "= ");
            } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
            else { fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name); }
            if (codegen_init(ty, linit, out, b) != 0) return -1;
            fprintf(out, ";\n");
        }
#endif
        int reorder_safe = (b->num_early_lets > 0 && b->num_early_lets < b->num_lets && b->num_loops == 0 && b->num_for_loops == 0);
        if (reorder_safe) {
            for (int i = 0; i < b->num_expr_stmts; i++) {
                const struct ASTExpr *st = b->expr_stmts[i];
#ifdef SHUC_USE_SU_CODEGEN
                if (st->kind == AST_EXPR_CONTINUE) { if (codegen_codegen_su_emit_continue_stmt((uint8_t *)out, indent) != 0) return -1; }
                else if (st->kind == AST_EXPR_BREAK) { if (codegen_codegen_su_emit_break_stmt((uint8_t *)out, indent) != 0) return -1; }
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { if (codegen_codegen_su_emit_return_expr((uint8_t *)out, indent, (uint8_t *)st->value.unary.operand) != 0) return -1; } else { if (codegen_codegen_su_emit_return_no_val((uint8_t *)out, indent) != 0) return -1; } }
                else { if (codegen_codegen_su_emit_void_expr_stmt((uint8_t *)out, indent, (uint8_t *)st) != 0) return -1; }
#else
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); } else fprintf(out, "%sreturn;\n", pad); }
                else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
#endif
            }
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_block_let_decls_range((uint8_t *)out, (uint8_t *)b, indent, (int32_t)b->num_early_lets, (int32_t)b->num_lets) != 0) return -1;
#else
            for (int i = b->num_early_lets; i < b->num_lets; i++) {
                const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
                if (!is_var_used(name, used_buf, n_used)) continue;
                const struct ASTType *ty = b->let_decls[i].type;
                const struct ASTType *ety = codegen_emit_type(ty);
                if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%s%s * %s = ", pad, c_type_str(ety->elem_type), name);
                else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                    fprintf(out, "%s", pad);
                    emit_local_array_decl(ety, name, "", out);
                    if (b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_VAR && b->let_decls[i].init->value.var.name) {
                        fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, b->let_decls[i].init->value.var.name, name);
                        continue;
                    }
                    if (b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_LIT && b->let_decls[i].init->value.int_val == 0) {
                        fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                        continue;
                    }
                    if (b->let_decls[i].init && b->let_decls[i].init->kind != AST_EXPR_ARRAY_LIT) {
                        fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                        if (codegen_expr(b->let_decls[i].init, out) != 0) return -1;
                        fprintf(out, "), sizeof(%s));\n", name);
                        continue;
                    }
                    fprintf(out, "= ");
                } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
                fprintf(out, ";\n");
            }
#endif
        } else {
            for (int i = 0; i < b->num_expr_stmts; i++) {
                const struct ASTExpr *st = b->expr_stmts[i];
#ifdef SHUC_USE_SU_CODEGEN
                if (st->kind == AST_EXPR_CONTINUE) { if (codegen_codegen_su_emit_continue_stmt((uint8_t *)out, indent) != 0) return -1; }
                else if (st->kind == AST_EXPR_BREAK) { if (codegen_codegen_su_emit_break_stmt((uint8_t *)out, indent) != 0) return -1; }
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { if (codegen_codegen_su_emit_return_expr((uint8_t *)out, indent, (uint8_t *)st->value.unary.operand) != 0) return -1; } else { if (codegen_codegen_su_emit_return_no_val((uint8_t *)out, indent) != 0) return -1; } }
                else { if (codegen_codegen_su_emit_void_expr_stmt((uint8_t *)out, indent, (uint8_t *)st) != 0) return -1; }
#else
                if (st->kind == AST_EXPR_CONTINUE) fprintf(out, "%scontinue;\n", pad);
                else if (st->kind == AST_EXPR_BREAK) fprintf(out, "%sbreak;\n", pad);
                else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { fprintf(out, "%sreturn ", pad); if (codegen_expr(st->value.unary.operand, out) != 0) return -1; fprintf(out, ";\n"); } else fprintf(out, "%sreturn;\n", pad); }
                else { fprintf(out, "%s(void)(", pad); if (codegen_expr(st, out) != 0) return -1; fprintf(out, ");\n"); }
#endif
            }
            for (int i = 0; i < b->num_loops; i++) {
#ifdef SHUC_USE_SU_CODEGEN
                if (codegen_codegen_su_emit_one_while_loop((uint8_t *)out, (uint8_t *)b->loops[i].cond, (uint8_t *)b->loops[i].body, indent, cast_return_to_int) != 0) return -1;
#else
                fprintf(out, "%swhile (", pad);
                if (codegen_expr(b->loops[i].cond, out) != 0) return -1;
                fprintf(out, ") {\n");
                if (codegen_block_body(b->loops[i].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                fprintf(out, "%s}\n", pad);
#endif
            }
            for (int i = 0; i < b->num_for_loops; i++) {
#ifdef SHUC_USE_SU_CODEGEN
                if (codegen_codegen_su_emit_one_for_loop((uint8_t *)out,
                    (uint8_t *)b->for_loops[i].init, (uint8_t *)b->for_loops[i].cond, (uint8_t *)b->for_loops[i].step,
                    (uint8_t *)b->for_loops[i].body, indent, cast_return_to_int) != 0) return -1;
#else
                fprintf(out, "%sfor (", pad);
                if (b->for_loops[i].init) { if (codegen_expr(b->for_loops[i].init, out) != 0) return -1; }
                fprintf(out, "; ");
                if (b->for_loops[i].cond) { if (codegen_expr(b->for_loops[i].cond, out) != 0) return -1; }
                fprintf(out, "; ");
                if (b->for_loops[i].step) { if (codegen_expr(b->for_loops[i].step, out) != 0) return -1; }
                fprintf(out, ") {\n");
                if (codegen_block_body(b->for_loops[i].body, indent + 2, out, cast_return_to_int, NULL) != 0) return -1;
                fprintf(out, "%s}\n", pad);
#endif
            }
#ifdef SHUC_USE_SU_CODEGEN
            if (b->num_early_lets > 0 && b->num_early_lets < b->num_lets)
                if (codegen_codegen_su_emit_block_let_decls_range((uint8_t *)out, (uint8_t *)b, indent, (int32_t)b->num_early_lets, (int32_t)b->num_lets) != 0) return -1;
#else
            if (b->num_early_lets > 0 && b->num_early_lets < b->num_lets) {
                for (int i = b->num_early_lets; i < b->num_lets; i++) {
                    const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
                    if (!is_var_used(name, used_buf, n_used)) continue;
                    const struct ASTType *ty = b->let_decls[i].type;
                    const struct ASTType *ety = codegen_emit_type(ty);
                    if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(out, "%s%s * %s = ", pad, c_type_str(ety->elem_type), name);
                    else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
                    else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
                        fprintf(out, "%s", pad);
                        emit_local_array_decl(ety, name, "", out);
                        if (b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_VAR && b->let_decls[i].init->value.var.name) {
                            fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, b->let_decls[i].init->value.var.name, name);
                            continue;
                        }
                        if (b->let_decls[i].init && b->let_decls[i].init->kind == AST_EXPR_LIT && b->let_decls[i].init->value.int_val == 0) {
                            fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                            continue;
                        }
                        if (b->let_decls[i].init && b->let_decls[i].init->kind != AST_EXPR_ARRAY_LIT) {
                            fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                            if (codegen_expr(b->let_decls[i].init, out) != 0) return -1;
                            fprintf(out, "), sizeof(%s));\n", name);
                            continue;
                        }
                        fprintf(out, "= ");
                    } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, out); fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name); }
                    else fprintf(out, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
                    if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
                    fprintf(out, ";\n");
                }
            }
#endif
        }
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label) {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_label((uint8_t *)out, indent, (uint8_t *)b->labeled_stmts[i].label, (int32_t)strlen(b->labeled_stmts[i].label)) != 0) return -1;
#else
            fprintf(out, "%s%s:\n", pad, b->labeled_stmts[i].label);
#endif
        }
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, indent) != 0) return -1;
            if (codegen_codegen_su_emit_goto((uint8_t *)out, indent, (uint8_t *)b->labeled_stmts[i].u.goto_target, (int32_t)strlen(b->labeled_stmts[i].u.goto_target)) != 0) return -1;
#else
            if (codegen_run_defers(out, b, indent) != 0) return -1;
            fprintf(out, "%sgoto %s;\n", pad, b->labeled_stmts[i].u.goto_target);
#endif
        } else {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, indent) != 0) return -1;
#else
            if (codegen_run_defers(out, b, indent) != 0) return -1;
#endif
            const struct ASTExpr *re = b->labeled_stmts[i].u.return_expr;
            if (!re) {
                fprintf(out, "%sreturn;\n", pad);
                continue;
            }
            int if_panic = (re->kind == AST_EXPR_IF && re->value.if_expr.then_expr
                && re->value.if_expr.then_expr->kind == AST_EXPR_PANIC && re->value.if_expr.else_expr);
            if (if_panic) {
                fprintf(out, "%sif (", pad);
                if (codegen_expr(re->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, ") {\n");
                fprintf(out, "%s  ", pad);
                if (codegen_expr(re->value.if_expr.then_expr, out) != 0) return -1;
                fprintf(out, ";\n%s}\n", pad);
                if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                if (codegen_expr(re->value.if_expr.else_expr, out) != 0) return -1;
                fprintf(out, cast_return_to_int ? ");\n" : ";\n");
            } else if (re->kind == AST_EXPR_PANIC) {
                fprintf(out, "%s", pad);
                if (codegen_expr(re, out) != 0) return -1;
                fprintf(out, ";\n%sreturn 0;\n", pad);
            } else {
                if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                if (codegen_expr(re, out) != 0) return -1;
                fprintf(out, cast_return_to_int ? ");\n" : ";\n");
            }
        }
    }
#ifdef SHUC_USE_SU_CODEGEN
    if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, indent) != 0) return -1;
#else
    if (codegen_run_defers(out, b, indent) != 0) return -1;
#endif
    if (!b->final_expr) return 0;  /* 块以 return/goto 结尾，无需 final_expr */
    if (b->final_expr->kind == AST_EXPR_BREAK) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_break_stmt((uint8_t *)out, indent) != 0) return -1;
#else
        fprintf(out, "%sbreak;\n", pad);
#endif
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_CONTINUE) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_continue_stmt((uint8_t *)out, indent) != 0) return -1;
#else
        fprintf(out, "%scontinue;\n", pad);
#endif
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *op = b->final_expr->value.unary.operand;
        if (!op) {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_return_no_val((uint8_t *)out, indent) != 0) return -1;
#else
            fprintf(out, "%sreturn;\n", pad);
#endif
            return 0;
        }
        if (op->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s", pad);
            if (codegen_expr(op, out) != 0) return -1;
            fprintf(out, ";\n%sreturn 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (codegen_expr(op, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
        && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
        && b->final_expr->value.if_expr.else_expr
        && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *iff = b->final_expr;
        const struct ASTExpr *then_ret = iff->value.if_expr.then_expr->value.unary.operand;
        const struct ASTExpr *else_ret = iff->value.if_expr.else_expr->value.unary.operand;
        fprintf(out, "%sif (", pad);
        if (codegen_expr(iff->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (then_ret && then_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            fprintf(out, "%s  return ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n");
        }
        fprintf(out, "%s} else {\n", pad);
        if (else_ret && else_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            fprintf(out, "%s  return ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n");
        }
        fprintf(out, "%s}\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "%s", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        return 0;
    }
    if (final_result_var && *final_result_var) {
        fprintf(out, "%s%s = ", pad, final_result_var);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
    } else {
        fprintf(out, "%s(void)(", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ");\n");
    }
    return 0;
}

/** 当 else 分支为单语句块且唯一语句为 __tmp = (struct X){0} 或仅为 (struct X){0} 时，返回该 struct 的 C 类型串，否则返回 NULL。
 * 用于 EXPR_INDEX 等路径避免 __tmp 打成 int32_t；并修复 typeck 中 if(cond){ block } else (Type){0} 产出 int __tmp 却赋 (struct ast_Type){0} 的错型。 */
static const char *struct_type_from_else_block(const struct ASTExpr *else_e) {
    if (!else_e || else_e->kind != AST_EXPR_BLOCK) return NULL;
    const struct ASTBlock *b = else_e->value.block;
    if (!b) return NULL;
    /* 情况 1：块内唯一语句为赋值且 RHS 为结构体字面量（__tmp = (struct X){0}） */
    const struct ASTExpr *assign = NULL;
    if (b->expr_stmts && b->num_expr_stmts == 1)
        assign = b->expr_stmts[0];
    else if (b->num_expr_stmts == 0 && b->final_expr)
        assign = b->final_expr;
    if (assign && assign->kind == AST_EXPR_ASSIGN) {
        const struct ASTExpr *rhs = assign->value.binop.right;
        if (rhs && rhs->kind == AST_EXPR_STRUCT_LIT && rhs->resolved_type) {
            const char *s = c_type_str(rhs->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) return s;
        }
    }
    /* 情况 2：块内唯一语句或 final_expr 为结构体字面量（无赋值，如 else { (Type){0} }），codegen 会生成 __tmp = (struct X){0} */
    const struct ASTExpr *struct_lit = NULL;
    if (b->expr_stmts && b->num_expr_stmts == 1 && b->expr_stmts[0]->kind == AST_EXPR_STRUCT_LIT)
        struct_lit = b->expr_stmts[0];
    else if (b->num_expr_stmts == 0 && b->final_expr && b->final_expr->kind == AST_EXPR_STRUCT_LIT)
        struct_lit = b->final_expr;
    if (struct_lit) {
        if (struct_lit->resolved_type) {
            const char *s = c_type_str(struct_lit->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) return s;
        }
        /* typeck 可能未对 struct literal 设 resolved_type，用与发射时一致的 C 类型名（需前向声明 struct_lit_c_type_str） */
        if (struct_lit->value.struct_lit.struct_name) {
            static char block_struct_ty_buf[128];
            if (struct_lit_c_type_str(struct_lit, block_struct_ty_buf, sizeof(block_struct_ty_buf)))
                return block_struct_ty_buf;
        }
    }
    return NULL;
}

/** if 表达式完整输出（供 .su 转调）：语句表达式 ({ __tmp; if(cond) ... else ...; __tmp; }) 或三元 cond ? then : else。 */
static int codegen_emit_if_expr_impl(FILE *out, const struct ASTExpr *e) {
    const struct ASTExpr *then_e = e->value.if_expr.then_expr;
    const struct ASTExpr *else_e = e->value.if_expr.else_expr;
    int then_is_block = (then_e && then_e->kind == AST_EXPR_BLOCK);
    int else_is_block = (else_e && else_e->kind == AST_EXPR_BLOCK);
    int then_is_control = (then_e && (then_e->kind == AST_EXPR_CONTINUE || then_e->kind == AST_EXPR_BREAK || then_e->kind == AST_EXPR_RETURN));
    int else_is_control = (else_e && (else_e->kind == AST_EXPR_CONTINUE || else_e->kind == AST_EXPR_BREAK || else_e->kind == AST_EXPR_RETURN));
    then_is_block = then_is_block || then_is_control;
    else_is_block = else_is_block || else_is_control;
    if (then_is_block || else_is_block) {
        const struct ASTType *tmp_ty = e->resolved_type;
        /* 任一分支为 struct 时用该类型作 __tmp（与 AST_EXPR_IF 主路径一致） */
        if (then_e && !then_is_block && then_e->resolved_type) {
            const char *s = c_type_str(then_e->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) tmp_ty = then_e->resolved_type;
        }
        /* then 为块且块类型为 struct 时也用上（如 if (ref<=0) { return Type{...}; }） */
        if (then_e && then_is_block && then_e->resolved_type) {
            const char *s = c_type_str(then_e->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) tmp_ty = then_e->resolved_type;
        }
        /* else 为 struct 时用 else 类型，但若 then 已为块且产出 struct 则优先 then，避免 LexerResult __tmp 赋 (Token){0} */
        if (else_e && !else_is_block && else_e->resolved_type) {
            const char *s = c_type_str(else_e->resolved_type);
            if (s && strncmp(s, "struct ", 7) == 0) {
                const char *cur = tmp_ty ? c_type_str(tmp_ty) : NULL;
                if (!cur || strncmp(cur, "struct ", 7) != 0 || !then_e || !then_is_block)
                    tmp_ty = else_e->resolved_type;
            }
        }
        /* else 为结构体字面量且 tmp_ty 仍非 struct 时，用 else 的 resolved_type（如 ast_Type/ast_Expr）；then 为块且 tmp_ty 已来自 then 时不覆盖，避免 LexerResult __tmp = (Token){0} */
        const char *tmp_ty_str = tmp_ty ? c_type_str(tmp_ty) : "int32_t";
        if (else_e && !else_is_block && else_e->kind == AST_EXPR_STRUCT_LIT && strncmp(tmp_ty_str, "struct ", 7) != 0
            && !(then_e && then_is_block && tmp_ty == then_e->resolved_type)) {
            if (else_e->resolved_type) {
                const char *s = c_type_str(else_e->resolved_type);
                if (s && strncmp(s, "struct ", 7) == 0) {
                    static char if_impl_ty_buf[64];
                    snprintf(if_impl_ty_buf, sizeof(if_impl_ty_buf), "%s", s);
                    tmp_ty_str = if_impl_ty_buf;
                }
            }
            if (strncmp(tmp_ty_str, "struct ", 7) != 0) {
                static char if_impl_struct_lit_buf[128];
                if (struct_lit_c_type_str(else_e, if_impl_struct_lit_buf, sizeof(if_impl_struct_lit_buf)))
                    tmp_ty_str = if_impl_struct_lit_buf;
            }
        }
        /* else 为块且块内仅 __tmp = (struct X){0} 时，从块内推断 __tmp 类型（如 backend EXPR_INDEX 路径），避免 sed 兜底 */
        if (else_e && else_is_block && strncmp(tmp_ty_str, "struct ", 7) != 0) {
            const char *block_ty = struct_type_from_else_block(else_e);
            if (block_ty) {
                static char if_impl_else_block_ty_buf[64];
                snprintf(if_impl_else_block_ty_buf, sizeof(if_impl_else_block_ty_buf), "%s", block_ty);
                tmp_ty_str = if_impl_else_block_ty_buf;
            }
        }
        /* 无 else 且 then 为块时从块内 return 操作数推断 struct 类型 */
        if (!else_e && then_e && then_is_block && strncmp(tmp_ty_str, "struct ", 7) != 0) {
            static char if_impl_then_block_buf[128];
            if (expr_struct_type_str(then_e, if_impl_then_block_buf, sizeof(if_impl_then_block_buf)))
                tmp_ty_str = if_impl_then_block_buf;
        }
        /* c_type_str 对库模块 NAMED 可能返回 "prefix_Type" 无 "struct "，此处统一为 "struct prefix_Type"；若已是 "enum X" 则不要加 struct。 */
        if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) != 0 && strncmp(tmp_ty_str, "enum ", 5) != 0
            && e->resolved_type && e->resolved_type->kind == AST_TYPE_NAMED) {
            static char if_impl_struct_named_buf[128];
            snprintf(if_impl_struct_named_buf, sizeof(if_impl_struct_named_buf), "struct %s", tmp_ty_str);
            tmp_ty_str = if_impl_struct_named_buf;
        }
        /* 带初值避免 -Wuninitialized：标量用 0，struct 用 (type){0} */
        if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0)
            fprintf(out, "({ %s __tmp = (%s){0}; if (", tmp_ty_str, tmp_ty_str);
        else
            fprintf(out, "({ %s __tmp = 0; if (", tmp_ty_str);
        if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, ") ");
        if (then_is_block) {
            if (then_e->kind == AST_EXPR_BLOCK) {
                fprintf(out, "{ ");
                if (codegen_block_body(then_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                fprintf(out, " } ");
            } else if (then_e->kind == AST_EXPR_CONTINUE) {
                fprintf(out, "{ continue; } ");
            } else if (then_e->kind == AST_EXPR_BREAK) {
                fprintf(out, "{ break; } ");
            } else if (then_e->kind == AST_EXPR_RETURN) {
                fprintf(out, "{ __tmp = ");
                if (then_e->value.unary.operand && codegen_expr(then_e->value.unary.operand, out) != 0) return -1;
                if (!then_e->value.unary.operand) {
                    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                    else fprintf(out, "0");
                }
                fprintf(out, "; return __tmp; } ");
            } else {
                fprintf(out, "(__tmp = ");
                if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && !expr_produces_struct_type(then_e))
                    fprintf(out, "(%s){0}", tmp_ty_str);
                else if (codegen_expr(then_e, out) != 0) return -1;
                fprintf(out, ") ");
            }
        } else {
            fprintf(out, "(__tmp = ");
            if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && !expr_produces_struct_type(then_e))
                fprintf(out, "(%s){0}", tmp_ty_str);
            else if (codegen_expr(then_e, out) != 0) return -1;
            fprintf(out, ") ");
        }
        fprintf(out, "else ");
        if (else_is_block) {
            if (else_e->kind == AST_EXPR_BLOCK) {
                fprintf(out, "{ ");
                if (codegen_block_body(else_e->value.block, 2, out, 0, "__tmp") != 0) return -1;
                fprintf(out, " } ");
            } else if (else_e->kind == AST_EXPR_CONTINUE) {
                fprintf(out, "{ continue; } ");
            } else if (else_e->kind == AST_EXPR_BREAK) {
                fprintf(out, "{ break; } ");
            } else if (else_e->kind == AST_EXPR_RETURN) {
                fprintf(out, "{ __tmp = ");
                if (else_e->value.unary.operand && codegen_expr(else_e->value.unary.operand, out) != 0) return -1;
                if (!else_e->value.unary.operand) {
                    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                    else fprintf(out, "0");
                }
                fprintf(out, "; return __tmp; } ");
            } else {
                fprintf(out, "(__tmp = ");
                if (else_e) {
                    static char impl_else_ty[128], impl_else_lit_ty[128];
                    const char *impl_ty_ptr = expr_struct_type_str(else_e, impl_else_ty, sizeof(impl_else_ty));
                    const char *impl_else_ctype = (else_e->kind == AST_EXPR_STRUCT_LIT) ? struct_lit_c_type_str(else_e, impl_else_lit_ty, sizeof(impl_else_lit_ty)) : NULL;
                    int impl_lex_tok = (tmp_ty_str && else_e->kind == AST_EXPR_STRUCT_LIT && impl_else_ctype && strstr(tmp_ty_str, "LexerResult") && strstr(impl_else_ctype, "Token"));
                    if (impl_lex_tok) {
                        if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                        else { static char impl_lex_buf[128]; snprintf(impl_lex_buf, sizeof(impl_lex_buf), "struct %s", tmp_ty_str ? tmp_ty_str : "lexer_LexerResult"); fprintf(out, "(%s){0}", impl_lex_buf); }
                    } else if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && impl_ty_ptr && strcmp(impl_ty_ptr, tmp_ty_str) != 0)
                        fprintf(out, "(%s){0}", tmp_ty_str);
                    else if (else_struct_type_mismatch(tmp_ty_str, else_e))
                        fprintf(out, "(%s){0}", tmp_ty_str);
                    else if (codegen_expr(else_e, out) != 0) return -1;
                } else {
                    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                    else fprintf(out, "0");
                }
                fprintf(out, ") ");
            }
        } else {
            fprintf(out, "(__tmp = ");
            if (else_e) {
                static char impl_else_ty2[128], impl_else_lit_ty2[128];
                const char *impl_ty_ptr2 = expr_struct_type_str(else_e, impl_else_ty2, sizeof(impl_else_ty2));
                const char *impl_else_ctype2 = (else_e->kind == AST_EXPR_STRUCT_LIT) ? struct_lit_c_type_str(else_e, impl_else_lit_ty2, sizeof(impl_else_lit_ty2)) : NULL;
                int impl_lex_tok2 = (tmp_ty_str && else_e->kind == AST_EXPR_STRUCT_LIT && impl_else_ctype2 && strstr(tmp_ty_str, "LexerResult") && strstr(impl_else_ctype2, "Token"));
                if (impl_lex_tok2) {
                    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                    else { static char impl_lex_buf2[128]; snprintf(impl_lex_buf2, sizeof(impl_lex_buf2), "struct %s", tmp_ty_str); fprintf(out, "(%s){0}", impl_lex_buf2); }
                } else if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0 && impl_ty_ptr2 && strcmp(impl_ty_ptr2, tmp_ty_str) != 0)
                    fprintf(out, "(%s){0}", tmp_ty_str);
                else if (else_struct_type_mismatch(tmp_ty_str, else_e))
                    fprintf(out, "(%s){0}", tmp_ty_str);
                else if (codegen_expr(else_e, out) != 0) return -1;
            } else {
                if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0) fprintf(out, "(%s){0}", tmp_ty_str);
                else fprintf(out, "0");
            }
            fprintf(out, ") ");
        }
        fprintf(out, "; __tmp; })");
        return 0;
    }
    int then_is_panic = (then_e && then_e->kind == AST_EXPR_PANIC);
    fprintf(out, "(");
    if (then_is_panic) {
        fprintf(out, "__builtin_expect(!!(");
        if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, "), 0) ? ");
    } else {
        if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, " ? ");
    }
    if (codegen_expr(then_e, out) != 0) return -1;
    fprintf(out, " : ");
    if (else_e) {
        if (codegen_expr(else_e, out) != 0) return -1;
    } else {
        fprintf(out, "0");
    }
    fprintf(out, ")");
    return 0;
}
/** .su 侧 if 表达式全量输出：供 codegen.su 在需要语句表达式时转调。 */
int32_t codegen_su_emit_if_expr_full(uint8_t *out, uint8_t *expr) {
    return codegen_emit_if_expr_impl((FILE *)out, (const struct ASTExpr *)expr) != 0 ? -1 : 0;
}

/** .su 侧 IF 表达式：是否需要语句表达式（then/else 为 BLOCK 或 continue/break/return），非 0 时 .su 转调 full。 */
int32_t codegen_su_if_expr_need_stmt_expr(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_IF) return 0;
    const struct ASTExpr *then_e = e->value.if_expr.then_expr;
    const struct ASTExpr *else_e = e->value.if_expr.else_expr;
    int then_block = (then_e && (then_e->kind == AST_EXPR_BLOCK || then_e->kind == AST_EXPR_CONTINUE || then_e->kind == AST_EXPR_BREAK || then_e->kind == AST_EXPR_RETURN));
    int else_block = (else_e && (else_e->kind == AST_EXPR_BLOCK || else_e->kind == AST_EXPR_CONTINUE || else_e->kind == AST_EXPR_BREAK || else_e->kind == AST_EXPR_RETURN));
    return (then_block || else_block) ? 1 : 0;
}

/** .su 侧 IF 表达式：三元分支时 then 是否为 PANIC（生成 __builtin_expect）。 */
int32_t codegen_su_if_expr_then_is_panic(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_IF || !e->value.if_expr.then_expr) return 0;
    return e->value.if_expr.then_expr->kind == AST_EXPR_PANIC ? 1 : 0;
}

/** .su 侧 IF 表达式访问器：cond、then、else。 */
uint8_t *codegen_su_if_expr_cond(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_IF && e->value.if_expr.cond) ? (uint8_t *)e->value.if_expr.cond : NULL;
}
uint8_t *codegen_su_if_expr_then(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_IF) ? (uint8_t *)e->value.if_expr.then_expr : NULL;
}
uint8_t *codegen_su_if_expr_else(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_IF) ? (uint8_t *)e->value.if_expr.else_expr : NULL;
}

/** .su 自实现 if 语句表达式用：将 __tmp 的 C 类型写入 out（如 int32_t 或 struct X）。 */
int32_t codegen_su_emit_if_expr_tmp_type(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_IF) return -1;
    const struct ASTType *tmp_ty = e->resolved_type;
    const char *s = tmp_ty ? c_type_str(tmp_ty) : "int32_t";
    fprintf((FILE *)out, "%s", s);
    return 0;
}
/** .su 自实现 if 语句表达式用：将默认值写入 out（0 或 (struct X){0}）。 */
int32_t codegen_su_emit_if_expr_default_val(uint8_t *out, uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    if (!e || e->kind != AST_EXPR_IF) return -1;
    const struct ASTType *tmp_ty = e->resolved_type;
    const char *tmp_ty_str = tmp_ty ? c_type_str(tmp_ty) : "int32_t";
    if (tmp_ty_str && strncmp(tmp_ty_str, "struct ", 7) == 0)
        fprintf((FILE *)out, "(%s){0}", tmp_ty_str);
    else
        fprintf((FILE *)out, "0");
    return 0;
}
/** .su 表达式 kind 常量：BLOCK、CONTINUE、BREAK、RETURN，供 if 语句表达式分支判断。 */
int32_t codegen_su_expr_kind_block(void) { return (int32_t)AST_EXPR_BLOCK; }
int32_t codegen_su_expr_kind_continue(void) { return (int32_t)AST_EXPR_CONTINUE; }
int32_t codegen_su_expr_kind_break(void) { return (int32_t)AST_EXPR_BREAK; }
int32_t codegen_su_expr_kind_return(void) { return (int32_t)AST_EXPR_RETURN; }
/** .su 自实现用：expr 为 BLOCK 时返回块指针，否则 NULL。 */
uint8_t *codegen_su_expr_block_ptr(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_BLOCK && e->value.block) ? (uint8_t *)e->value.block : NULL;
}
/** .su 自实现用：expr 为 RETURN 时返回 return 的操作数表达式，否则 NULL。 */
uint8_t *codegen_su_return_operand(uint8_t *expr) {
    const struct ASTExpr *e = (const struct ASTExpr *)expr;
    return (e && e->kind == AST_EXPR_RETURN) ? (uint8_t *)e->value.unary.operand : NULL;
}

/**
 * 统计块内「会执行 return」的出口个数（用于决定是否用 goto cleanup 减少 defer 重复展开）。
 * 仅计 return 类出口，不含 goto。
 */
static int count_return_exits(const struct ASTBlock *b) {
    if (!b) return 0;
    int n = 0;
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN) {
            const struct ASTExpr *e = b->labeled_stmts[i].u.return_expr;
            if (e && e->kind == AST_EXPR_IF && e->value.if_expr.then_expr
                && e->value.if_expr.then_expr->kind == AST_EXPR_PANIC && e->value.if_expr.else_expr)
                n += 2; /* then panic + else return */
            else
                n += 1;
        }
    }
    if (b->final_expr) {
        if (b->final_expr->kind == AST_EXPR_RETURN) n += 1;
        else if (b->final_expr->kind == AST_EXPR_PANIC) n += 1;
        else if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
            && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
            && b->final_expr->value.if_expr.else_expr
            && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN)
            n += 2;
    }
    return n;
}

/**
 * 生成单个函数体（const/let、while/for、labeled、final_expr return/panic）。
 * 用于多函数时每个函数的函数体；indent 固定为 2（两空格）。
 * f 非 NULL 且为 main 且返回 i64 时，对 return 表达式包 (int) 以适配 C 的 int main()。
 * 当存在多个 return 出口且至少一个 defer 时，使用单一 shulang_cleanup 标签，避免每出口重复展开 defer。
 */
static int codegen_func_body(const struct ASTBlock *b, const struct ASTModule *m, FILE *out, const struct ASTFunc *f) {
    if (!b || !m || !out) return -1;
    codegen_current_func = f;
    int cast_return_to_int = (f && f->name && strcmp(f->name, "main") == 0
        && f->return_type && f->return_type->kind == AST_TYPE_I64);
    const char *pad = "  ";
    int is_void = (f && f->return_type && f->return_type->kind == AST_TYPE_VOID);
    int use_cleanup = (!is_void && b->num_defers > 0 && count_return_exits(b) >= 2);
    const char *ret_ctype = (f && f->return_type) ? c_type_str(f->return_type) : "int32_t";
    if (cast_return_to_int) ret_ctype = "int";
    /* 阶段 8.1 块内 DCE：仅输出被引用的 const/let */
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    /* 有 stmt_order 时按源码顺序输出函数体，与 codegen_block_body 一致。 */
    int used_block_body_order = 0;
    if (b->num_stmt_order > 0) {
        if (1) {
            used_block_body_order = 1;
            if (codegen_block_body(b, 2, out, cast_return_to_int, use_cleanup ? "shulang_ret_val" : NULL) != 0) return -1;
            if (use_cleanup) fprintf(out, "%sgoto shulang_cleanup;\n", pad);
            goto func_body_after_block;
        }
    }
    for (int i = 0; i < b->num_consts; i++) {
        const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
        if (!is_var_used(name, used_buf, n_used)) continue;
        const struct ASTType *ty = b->const_decls[i].type;
        const struct ASTType *ety = codegen_emit_type(ty);
        if (ety && ety->kind == AST_TYPE_NAMED && ety->name) {
            if (is_enum_type(m, ety->name))
                fprintf(out, "%sconst enum %s %s = ", pad, ety->name, name);
            else
                fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
        }
        else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
            fprintf(out, "%sconst ", pad);
            emit_local_array_decl(ety, name, "", out);
            if (b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_VAR && b->const_decls[i].init->value.var.name) {
                fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, b->const_decls[i].init->value.var.name, name);
                continue;
            }
            if (b->const_decls[i].init && b->const_decls[i].init->kind == AST_EXPR_LIT && b->const_decls[i].init->value.int_val == 0) {
                fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                continue;
            }
            if (b->const_decls[i].init && b->const_decls[i].init->kind != AST_EXPR_ARRAY_LIT) {
                fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                if (codegen_expr(b->const_decls[i].init, out) != 0) return -1;
                fprintf(out, "), sizeof(%s));\n", name);
                continue;
            }
            fprintf(out, "= ");
        } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) {
            ensure_slice_struct(ety, out);
            fprintf(out, "%sconst %s %s = ", pad, c_type_str(ety), name);
        } else {
            const char *cty = ety ? c_type_str(ety) : "int32_t";
            fprintf(out, "%sconst %s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, b->const_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_lets; i++) {
        const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
        if (!is_var_used(name, used_buf, n_used)) continue;
        const struct ASTType *ty = b->let_decls[i].type;
        const struct ASTExpr *linit = b->let_decls[i].init;
        const struct ASTType *ety = codegen_emit_type(ty);
        if (ety && ety->kind == AST_TYPE_NAMED && ety->name) {
            if (is_enum_type(m, ety->name))
                fprintf(out, "%senum %s %s = ", pad, ety->name, name);
            else
                fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
        }
        else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
            fprintf(out, "%s", pad);
            emit_local_array_decl(ety, name, "", out);
            if (linit && linit->kind == AST_EXPR_VAR && linit->value.var.name) {
                fprintf(out, ";\n%smemcpy(%s, %s, sizeof(%s));\n", pad, name, linit->value.var.name, name);
                continue;
            }
            if (linit && linit->kind == AST_EXPR_LIT && linit->value.int_val == 0) {
                fprintf(out, ";\n%smemset(%s, 0, sizeof(%s));\n", pad, name, name);
                continue;
            }
            if (linit && linit->kind != AST_EXPR_ARRAY_LIT) {
                fprintf(out, ";\n%smemcpy(%s, (", pad, name);
                if (codegen_expr(linit, out) != 0) return -1;
                fprintf(out, "), sizeof(%s));\n", name);
                continue;
            }
            fprintf(out, "= ");
        } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) {
            ensure_slice_struct(ety, out);
            fprintf(out, "%s%s %s = ", pad, c_type_str(ety), name);
        } else {
            const char *cty = ety ? c_type_str(ety) : "int32_t";
            fprintf(out, "%s%s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, linit, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    if (use_cleanup) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_cleanup_decl_exit_kind((uint8_t *)out, 2) != 0) return -1;
        if (codegen_codegen_su_emit_cleanup_decl_ret_val((uint8_t *)out, 2, (uint8_t *)ret_ctype, (int32_t)strlen(ret_ctype)) != 0) return -1;
#else
        fprintf(out, "%sint shulang_exit_kind = 0;\n", pad);
        fprintf(out, "%s%s shulang_ret_val = 0;\n", pad, ret_ctype);
#endif
    }
    for (int i = 0; i < b->num_loops; i++) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_one_while_loop((uint8_t *)out, (uint8_t *)b->loops[i].cond, (uint8_t *)b->loops[i].body, 2, cast_return_to_int) != 0) return -1;
#else
        fprintf(out, "%swhile (", pad);
        if (codegen_expr(b->loops[i].cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (codegen_block_body(b->loops[i].body, 4, out, cast_return_to_int, NULL) != 0) return -1;
        fprintf(out, "%s}\n", pad);
#endif
    }
    for (int i = 0; i < b->num_for_loops; i++) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_one_for_loop((uint8_t *)out,
            (uint8_t *)b->for_loops[i].init, (uint8_t *)b->for_loops[i].cond, (uint8_t *)b->for_loops[i].step,
            (uint8_t *)b->for_loops[i].body, 2, cast_return_to_int) != 0) return -1;
#else
        fprintf(out, "%sfor (", pad);
        if (b->for_loops[i].init) {
            if (codegen_expr(b->for_loops[i].init, out) != 0) return -1;
        }
        fprintf(out, "; ");
        if (b->for_loops[i].cond) {
            if (codegen_expr(b->for_loops[i].cond, out) != 0) return -1;
        } else {
            fprintf(out, "1");
        }
        fprintf(out, "; ");
        if (b->for_loops[i].step) {
            if (codegen_expr(b->for_loops[i].step, out) != 0) return -1;
        }
        fprintf(out, ") {\n");
        if (codegen_block_body(b->for_loops[i].body, 4, out, cast_return_to_int, NULL) != 0) return -1;
        fprintf(out, "%s}\n", pad);
#endif
    }
func_body_after_block:
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label) {
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_label((uint8_t *)out, 2, (uint8_t *)b->labeled_stmts[i].label, (int32_t)strlen(b->labeled_stmts[i].label)) != 0) return -1;
#else
            fprintf(out, "%s%s:\n", pad, b->labeled_stmts[i].label);
#endif
        }
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
            if (codegen_run_defers(out, b, 2) != 0) return -1;
#ifdef SHUC_USE_SU_CODEGEN
            if (codegen_codegen_su_emit_goto((uint8_t *)out, 2, (uint8_t *)b->labeled_stmts[i].u.goto_target, (int32_t)strlen(b->labeled_stmts[i].u.goto_target)) != 0) return -1;
#else
            fprintf(out, "%sgoto %s;\n", pad, b->labeled_stmts[i].u.goto_target);
#endif
        } else {
            const struct ASTExpr *ret_e = b->labeled_stmts[i].u.return_expr;
                if (!ret_e) {
                if (use_cleanup) {
#ifdef SHUC_USE_SU_CODEGEN
                    if (codegen_codegen_su_emit_exit_kind_goto_cleanup((uint8_t *)out, 2) != 0) return -1;
#else
                    fprintf(out, "%sshulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
#endif
                } else {
#ifdef SHUC_USE_SU_CODEGEN
                    if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, 2) != 0) return -1;
#else
                    if (codegen_run_defers(out, b, 2) != 0) return -1;
#endif
                    fprintf(out, "%sreturn;\n", pad);
                }
                continue;
            }
            int ret_if_panic = (ret_e->kind == AST_EXPR_IF && ret_e->value.if_expr.then_expr
                && ret_e->value.if_expr.then_expr->kind == AST_EXPR_PANIC && ret_e->value.if_expr.else_expr);
            if (use_cleanup) {
                if (ret_if_panic) {
                    fprintf(out, "%sif (", pad);
                    if (codegen_expr(ret_e->value.if_expr.cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    fprintf(out, "%s  ", pad);
                    if (codegen_expr(ret_e->value.if_expr.then_expr, out) != 0) return -1;
#ifdef SHUC_USE_SU_CODEGEN
                    fprintf(out, ";\n");
                    if (codegen_codegen_su_emit_ret_val_zero_exit_goto_cleanup((uint8_t *)out, 2) != 0) return -1;
                    fprintf(out, "%s} else {\n", pad);
                    if (cast_return_to_int) fprintf(out, "%s  shulang_ret_val = (int)(", pad); else fprintf(out, "%s  shulang_ret_val = ", pad);
                    if (codegen_expr(ret_e->value.if_expr.else_expr, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                    if (codegen_codegen_su_emit_exit_kind_goto_cleanup((uint8_t *)out, 4) != 0) return -1;
                    fprintf(out, "%s}\n", pad);
#else
                    fprintf(out, ";\n%sshulang_ret_val = 0; shulang_exit_kind = 1; goto shulang_cleanup;\n%s} else {\n", pad, pad);
                    if (cast_return_to_int) fprintf(out, "%s  shulang_ret_val = (int)(", pad); else fprintf(out, "%s  shulang_ret_val = ", pad);
                    if (codegen_expr(ret_e->value.if_expr.else_expr, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                    fprintf(out, "%s  shulang_exit_kind = 1; goto shulang_cleanup;\n%s}\n", pad, pad);
#endif
                } else if (ret_e && ret_e->kind == AST_EXPR_PANIC) {
                    fprintf(out, "%s", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
#ifdef SHUC_USE_SU_CODEGEN
                    fprintf(out, ";\n");
                    if (codegen_codegen_su_emit_ret_val_zero_exit_goto_cleanup((uint8_t *)out, 2) != 0) return -1;
#else
                    fprintf(out, ";\n%sshulang_ret_val = 0; shulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
#endif
                } else {
                    if (cast_return_to_int) fprintf(out, "%sshulang_ret_val = (int)(", pad); else fprintf(out, "%sshulang_ret_val = ", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
#ifdef SHUC_USE_SU_CODEGEN
                    if (codegen_codegen_su_emit_exit_kind_goto_cleanup((uint8_t *)out, 2) != 0) return -1;
#else
                    fprintf(out, "%sshulang_exit_kind = 1; goto shulang_cleanup;\n", pad);
#endif
                }
            } else {
#ifdef SHUC_USE_SU_CODEGEN
                if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, 2) != 0) return -1;
#else
                if (codegen_run_defers(out, b, 2) != 0) return -1;
#endif
                if (ret_if_panic) {
                    fprintf(out, "%sif (", pad);
                    if (codegen_expr(ret_e->value.if_expr.cond, out) != 0) return -1;
                    fprintf(out, ") {\n");
                    fprintf(out, "%s  ", pad);
                    if (codegen_expr(ret_e->value.if_expr.then_expr, out) != 0) return -1;
                    fprintf(out, ";\n%s}\n", pad);
                    if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                    if (codegen_expr(ret_e->value.if_expr.else_expr, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                } else if (ret_e && ret_e->kind == AST_EXPR_PANIC) {
                    fprintf(out, "%s", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, ";\n%sreturn 0;\n", pad);
                } else {
                    if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
                    if (codegen_expr(ret_e, out) != 0) return -1;
                    fprintf(out, cast_return_to_int ? ");\n" : ";\n");
                }
            }
        }
    }
    /* 表达式语句 (expr;)：continue/break/return 须直接生成语句，不能包在 (void)(...) 中；若已用 codegen_block_body 按 stmt_order 输出则跳过。 */
    if (!used_block_body_order) {
    for (int i = 0; i < b->num_expr_stmts; i++) {
        const struct ASTExpr *st = b->expr_stmts[i];
#ifdef SHUC_USE_SU_CODEGEN
        if (st->kind == AST_EXPR_CONTINUE) { if (codegen_codegen_su_emit_continue_stmt((uint8_t *)out, 2) != 0) return -1; }
        else if (st->kind == AST_EXPR_BREAK) { if (codegen_codegen_su_emit_break_stmt((uint8_t *)out, 2) != 0) return -1; }
        else if (st->kind == AST_EXPR_RETURN) { if (st->value.unary.operand) { if (codegen_codegen_su_emit_return_expr((uint8_t *)out, 2, (uint8_t *)st->value.unary.operand) != 0) return -1; } else { if (codegen_codegen_su_emit_return_no_val((uint8_t *)out, 2) != 0) return -1; } }
        else { if (codegen_codegen_su_emit_void_expr_stmt((uint8_t *)out, 2, (uint8_t *)st) != 0) return -1; }
#else
        if (st->kind == AST_EXPR_CONTINUE) {
            fprintf(out, "%scontinue;\n", pad);
        } else if (st->kind == AST_EXPR_BREAK) {
            fprintf(out, "%sbreak;\n", pad);
        } else if (st->kind == AST_EXPR_RETURN) {
            if (st->value.unary.operand) {
                fprintf(out, "%sreturn ", pad);
                if (codegen_expr(st->value.unary.operand, out) != 0) return -1;
                fprintf(out, ";\n");
            } else {
                fprintf(out, "%sreturn;\n", pad);
            }
        } else {
            fprintf(out, "%s(void)(", pad);
            if (codegen_expr(st, out) != 0) return -1;
            fprintf(out, ");\n");
        }
#endif
    }
    if (use_cleanup) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_goto_shulang_cleanup((uint8_t *)out, 2) != 0) return -1;
#else
        fprintf(out, "%sgoto shulang_cleanup;\n", pad);
#endif
    } else {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, 2) != 0) return -1;
#else
        if (codegen_run_defers(out, b, 2) != 0) return -1;
#endif
    }
    }  /* end if (!used_block_body_order): expr_stmts + goto/run_defers */
    if (use_cleanup) {
#ifdef SHUC_USE_SU_CODEGEN
        if (codegen_codegen_su_emit_shulang_cleanup_label((uint8_t *)out, 2) != 0) return -1;
        if (codegen_codegen_su_run_defers((uint8_t *)out, (uint8_t *)b, 2) != 0) return -1;
        if (codegen_codegen_su_emit_if_exit_kind_return_ret_val((uint8_t *)out, 2) != 0) return -1;
#else
        fprintf(out, "%sshulang_cleanup:\n", pad);
        if (codegen_run_defers(out, b, 2) != 0) return -1;
        fprintf(out, "%sif (shulang_exit_kind) return shulang_ret_val;\n", pad);
#endif
    }
    if (used_block_body_order || !b->final_expr) return 0;
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "%s", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        fprintf(out, "%sreturn 0;\n", pad);
    } else if (b->final_expr->kind == AST_EXPR_IF && b->final_expr->value.if_expr.then_expr
        && b->final_expr->value.if_expr.then_expr->kind == AST_EXPR_RETURN
        && b->final_expr->value.if_expr.else_expr
        && b->final_expr->value.if_expr.else_expr->kind == AST_EXPR_RETURN) {
        const struct ASTExpr *iff = b->final_expr;
        const struct ASTExpr *then_ret = iff->value.if_expr.then_expr->value.unary.operand;
        const struct ASTExpr *else_ret = iff->value.if_expr.else_expr->value.unary.operand;
        fprintf(out, "%sif (", pad);
        if (codegen_expr(iff->value.if_expr.cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (then_ret && then_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%s  return (int)(", pad); else fprintf(out, "%s  return ", pad);
            if (codegen_expr(then_ret, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        fprintf(out, "%s} else {\n", pad);
        if (else_ret && else_ret->kind == AST_EXPR_PANIC) {
            fprintf(out, "%s  ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, ";\n%s  return 0;\n", pad);
        } else {
            if (cast_return_to_int) fprintf(out, "%s  return (int)(", pad); else fprintf(out, "%s  return ", pad);
            if (codegen_expr(else_ret, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
        fprintf(out, "%s}\n", pad);
    } else {
        if (b->final_expr->kind == AST_EXPR_RETURN && !b->final_expr->value.unary.operand) {
            fprintf(out, "%sreturn;\n", pad);
            return 0;
        }
        /* void 函数：最后表达式只求值不返回，避免 C 报 "void function should not return a value"（如 vec truncate） */
        if (is_void) {
            fprintf(out, "%s(void)(", pad);
            if (codegen_expr(b->final_expr->kind == AST_EXPR_RETURN ? b->final_expr->value.unary.operand : b->final_expr, out) != 0) return -1;
            fprintf(out, ");\n");
            return 0;
        }
        const struct ASTExpr *ret_op = (b->final_expr->kind == AST_EXPR_RETURN) ? b->final_expr->value.unary.operand : b->final_expr;
        int is_return_if_panic = (ret_op && ret_op->kind == AST_EXPR_IF && ret_op->value.if_expr.then_expr
            && ret_op->value.if_expr.then_expr->kind == AST_EXPR_PANIC && ret_op->value.if_expr.else_expr);
        if (is_return_if_panic) {
            fprintf(out, "%sif (", pad);
            if (codegen_expr(ret_op->value.if_expr.cond, out) != 0) return -1;
            fprintf(out, ") {\n");
            fprintf(out, "%s  ", pad);
            if (codegen_expr(ret_op->value.if_expr.then_expr, out) != 0) return -1;
            fprintf(out, ";\n%s}\n", pad);
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (codegen_expr(ret_op->value.if_expr.else_expr, out) != 0) return -1;
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        } else {
            if (cast_return_to_int) fprintf(out, "%sreturn (int)(", pad); else fprintf(out, "%sreturn ", pad);
            if (b->final_expr->kind == AST_EXPR_RETURN) {
                if (codegen_expr(ret_op, out) != 0) return -1;
            } else {
                if (codegen_expr(b->final_expr, out) != 0) return -1;
            }
            fprintf(out, cast_return_to_int ? ");\n" : ";\n");
        }
    }
    return 0;
}

/**
 * 生成单个 C 函数定义：return_type name(params) { body }。
 * 多函数时对 mod->funcs 中每个函数调用；main 放在最后以便其它函数可被 main 调用。
 */
static int codegen_one_func(const struct ASTFunc *f, const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out) return -1;
    /* 泛型函数由单态化实例生成，不在此直接输出（阶段 7.1） */
    if (f->num_generic_params > 0) return 0;
    char fname[256];
    library_prefixed_name(f->name, fname, sizeof(fname));
    /* C 要求 main 返回 int；若 .su 中 main 返回 i64 则在函数体内对 return 包 (int) */
    const char *cret = (f->name && strcmp(f->name, "main") == 0) ? "int" : c_type_str(f->return_type);
    /* 入口模块的 main：生成 main(int argc, char **argv) 并保存到 std.process 全局，供 args_count/arg 使用 */
    if (!codegen_library_prefix && f->name && strcmp(f->name, "main") == 0) {
        fprintf(out, "int main(int argc, char **argv) {\n");
        fprintf(out, "  shulang_process_argc = argc;\n");
        fprintf(out, "  shulang_process_argv = argv;\n");
        if (codegen_func_body(f->body, m, out, f) != 0)
            return -1;
        fprintf(out, "}\n");
        return 0;
    }
    /* 小函数内联提示（§3.4）：入口模块内非 main、非 extern 加 static inline；core.option/core.result 库函数加 inline；core.types/core.mem 的 size_of_* 与 align_of_* 加 inline 便于常量折叠 */
    if (!codegen_library_prefix && f->name && strcmp(f->name, "main") != 0 && !f->is_extern)
        fprintf(out, "static inline ");
    else if (codegen_library_prefix && codegen_library_import_path && !f->is_extern
        && (strcmp(codegen_library_import_path, "core.option") == 0 || strcmp(codegen_library_import_path, "core.result") == 0))
        fprintf(out, "static inline ");
    else if (codegen_library_prefix && codegen_library_import_path && f->name && !f->is_extern
        && (strcmp(codegen_library_import_path, "core.types") == 0 || strcmp(codegen_library_import_path, "core.mem") == 0)
        && (strncmp(f->name, "size_of_", 8) == 0 || strncmp(f->name, "align_of_", 9) == 0))
        fprintf(out, "inline ");
    fprintf(out, "%s %s(", cret, fname);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        codegen_emit_param(&f->params[i], out, NULL);
    }
    fprintf(out, ") {\n");
    /* std.process.exit(code)：生成对 C exit() 的调用（noreturn） */
    if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.process") == 0
        && f->name && strcmp(f->name, "exit") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I32) {
        const char *pname = f->params[0].name ? f->params[0].name : "code";
        fprintf(out, "  exit(%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_i32") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I32) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%d\\n\", (int)%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_u32") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_U32) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%u\\n\", (unsigned int)%s);\n  return 0;\n", pname);
    } else if (codegen_library_import_path && strcmp(codegen_library_import_path, "std.io") == 0
        && f->name && strcmp(f->name, "print_i64") == 0 && f->num_params == 1
        && f->params[0].type && f->params[0].type->kind == AST_TYPE_I64) {
        const char *pname = f->params[0].name ? f->params[0].name : "x";
        fprintf(out, "  (void)printf(\"%%lld\\n\", (long long)%s);\n  return 0;\n", pname);
    } else if (codegen_func_body(f->body, m, out, f) != 0)
        return -1;
    fprintf(out, "}\n");
    return 0;
}

/**
 * 为 impl 块内单条方法生成 C 函数（使用 mangle 名 Trait_Type_method）；阶段 7.2。
 */
static int codegen_one_impl_func(const struct ASTFunc *f, const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out || !f->impl_for_trait || !f->impl_for_type) return -1;
    char cname_buf[256];
    library_prefixed_name(impl_method_c_name(f), cname_buf, sizeof(cname_buf));
    /* 库模块 impl 方法不加 static 以保持可链接；入口模块可考虑在单文件时加 inline，此处从简 */
    fprintf(out, "%s %s(", c_type_str(f->return_type), cname_buf);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        codegen_emit_param(&f->params[i], out, NULL);
    }
    fprintf(out, ") {\n");
    if (codegen_func_body(f->body, m, out, NULL) != 0) return -1;
    fprintf(out, "}\n");
    return 0;
}

/**
 * 为单个泛型单态化实例生成 C 函数：代入类型后的签名 + 模板体（体中类型按代入上下文输出）。
 */
static int codegen_one_mono_instance(const struct ASTFunc *f, struct ASTType **type_args, int num_type_args,
    const struct ASTModule *m, FILE *out) {
    if (!f || !f->body || !m || !out || !type_args || num_type_args <= 0 || !f->generic_param_names) return -1;
    const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, type_args, num_type_args);
    char mangled_buf[256];
    library_prefixed_name(mono_instance_mangled_name(f, type_args, num_type_args), mangled_buf, sizeof(mangled_buf));
    fprintf(out, "%s %s(", c_type_str(ret_ty), mangled_buf);
    for (int i = 0; i < f->num_params; i++) {
        if (i) fprintf(out, ", ");
        const struct ASTType *pty = subst_type(f->params[i].type, f->generic_param_names, type_args, num_type_args);
        codegen_emit_param(&f->params[i], out, pty);
    }
    fprintf(out, ") {\n");
    codegen_subst_gp_names = f->generic_param_names;
    codegen_subst_type_args = type_args;
    codegen_subst_n = num_type_args;
    int r = codegen_func_body(f->body, m, out, NULL);
    codegen_subst_gp_names = NULL;
    codegen_subst_type_args = NULL;
    codegen_subst_n = 0;
    if (r != 0) return -1;
    fprintf(out, "}\n");
    return 0;
}

/** 阶段 8.1 DCE：在模块 m 的 mono_instances 中查找 (template, type_args) 对应的实例下标，未找到返回 -1。 */
static int find_mono_index(const struct ASTModule *m, const struct ASTFunc *template,
    struct ASTType **type_args, int n) {
    if (!m || !m->mono_instances || !template || !type_args) return -1;
    for (int k = 0; k < m->num_mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (inst->template != template || inst->num_type_args != n) continue;
        int eq = 1;
        for (int j = 0; j < n && eq; j++)
            if (!type_equal(inst->type_args[j], type_args[j])) eq = 0;
        if (eq) return k;
    }
    return -1;
}

/** 返回 func 所在模块在 (entry, dep_mods[0..ndep-1]) 中的下标：0=entry，1+i=dep_mods[i]，未找到返回 -1。 */
static int module_index(const struct ASTModule *entry, struct ASTModule **dep_mods, int ndep, const struct ASTModule *mod) {
    if (mod == entry) return 0;
    for (int i = 0; i < ndep; i++)
        if (dep_mods[i] == mod) return 1 + i;
    return -1;
}

/** 判断 func 是否属于模块 m（顶层函数或 impl 方法）。 */
static int func_belongs_to_module(const struct ASTModule *m, const struct ASTFunc *func) {
    if (!m || !func) return 0;
    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] == func) return 1;
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j] == func) return 1;
    return 0;
}

/** 阶段 8.1 DCE：从表达式递归收集被调函数与单态化，加入 worklist 并标记 used_mono。 */
static void dce_collect_from_expr(const struct ASTExpr *e, struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **worklist, int *n_wl, int max_wl, int *in_wl,
    int used_mono[][64], int used_mono_rows) {
    if (!e) return;
    /* return expr 在 parser 中为 AST_EXPR_RETURN(operand)，须先递归 operand 才能看到其中的 CALL 并收集 callee */
    if (e->kind == AST_EXPR_RETURN && e->value.unary.operand) {
        dce_collect_from_expr(e->value.unary.operand, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        return;
    }
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func) {
        const struct ASTFunc *callee = e->value.call.resolved_callee_func;
        if (e->value.call.num_type_args > 0 && e->value.call.type_args) {
            const struct ASTModule *owner = NULL;
            if (func_belongs_to_module(entry, callee)) owner = entry;
            else
                for (int i = 0; i < ndep && !owner; i++)
                    if (func_belongs_to_module(dep_mods[i], callee)) owner = dep_mods[i];
            if (owner) {
                int mi = module_index(entry, dep_mods, ndep, owner);
                int k = find_mono_index(owner, callee, (struct ASTType **)e->value.call.type_args, e->value.call.num_type_args);
                if (mi >= 0 && mi < used_mono_rows && k >= 0 && k < 64)
                    used_mono[mi][k] = 1;
            }
        }
        for (int i = 0; i < *n_wl && i < max_wl; i++)
            if (worklist[i] == (struct ASTFunc *)callee) goto skip_add;
        if (*n_wl < max_wl) {
            worklist[*n_wl++] = (struct ASTFunc *)callee;
            if (in_wl) in_wl[(size_t)(const char *)callee % (size_t)max_wl] = 1;
        }
    skip_add: ;
    }
    if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func) {
        const struct ASTFunc *callee = e->value.method_call.resolved_impl_func;
        for (int i = 0; i < *n_wl && i < max_wl; i++)
            if (worklist[i] == (struct ASTFunc *)callee) goto skip_impl;
        if (*n_wl < max_wl) worklist[*n_wl++] = (struct ASTFunc *)callee;
    skip_impl: ;
    }
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                dce_collect_from_expr(e->value.call.args[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_METHOD_CALL:
            dce_collect_from_expr(e->value.method_call.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                dce_collect_from_expr(e->value.method_call.args[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR:
        case AST_EXPR_ASSIGN:
            dce_collect_from_expr(e->value.binop.left, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.binop.right, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT:
        case AST_EXPR_PANIC: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            dce_collect_from_expr(e->value.unary.operand, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_AS:
            dce_collect_from_expr(e->value.as_type.operand, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_IF:
        case AST_EXPR_TERNARY:
            dce_collect_from_expr(e->value.if_expr.cond, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.if_expr.then_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            if (e->value.if_expr.else_expr) dce_collect_from_expr(e->value.if_expr.else_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_MATCH:
            dce_collect_from_expr(e->value.match_expr.matched_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                dce_collect_from_expr(e->value.match_expr.arms[i].result, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_FIELD_ACCESS:
            dce_collect_from_expr(e->value.field_access.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                dce_collect_from_expr(e->value.struct_lit.inits[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                dce_collect_from_expr(e->value.array_lit.elems[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        case AST_EXPR_INDEX:
            dce_collect_from_expr(e->value.index.base, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            dce_collect_from_expr(e->value.index.index_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
            break;
        default: break;
    }
}

/** 阶段 8.1 DCE 兜底：判断表达式 e 中是否出现对 func 的调用（CALL/METHOD_CALL），含 AST_EXPR_RETURN 内层。用于 ndep==0 时 used 未收到同模块 callee 仍保留被 main 引用的函数。 */
static int expr_references_func(const struct ASTExpr *e, const struct ASTFunc *func) {
    if (!e || !func) return 0;
    if (e->kind == AST_EXPR_CALL && e->value.call.resolved_callee_func == func) return 1;
    if (e->kind == AST_EXPR_METHOD_CALL && e->value.method_call.resolved_impl_func == func) return 1;
    if (e->kind == AST_EXPR_RETURN && e->value.unary.operand && expr_references_func(e->value.unary.operand, func)) return 1;
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                if (expr_references_func(e->value.call.args[i], func)) return 1;
            break;
        case AST_EXPR_METHOD_CALL:
            if (expr_references_func(e->value.method_call.base, func)) return 1;
            for (int i = 0; i < e->value.method_call.num_args; i++)
                if (expr_references_func(e->value.method_call.args[i], func)) return 1;
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            if (expr_references_func(e->value.binop.left, func) || expr_references_func(e->value.binop.right, func)) return 1;
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            if (expr_references_func(e->value.unary.operand, func)) return 1;
            break;
        case AST_EXPR_AS:
            if (expr_references_func(e->value.as_type.operand, func)) return 1;
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            if (expr_references_func(e->value.if_expr.cond, func) || expr_references_func(e->value.if_expr.then_expr, func)) return 1;
            if (e->value.if_expr.else_expr && expr_references_func(e->value.if_expr.else_expr, func)) return 1;
            break;
        case AST_EXPR_MATCH:
            if (expr_references_func(e->value.match_expr.matched_expr, func)) return 1;
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                if (expr_references_func(e->value.match_expr.arms[i].result, func)) return 1;
            break;
        case AST_EXPR_FIELD_ACCESS:
            if (expr_references_func(e->value.field_access.base, func)) return 1;
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                if (expr_references_func(e->value.struct_lit.inits[i], func)) return 1;
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                if (expr_references_func(e->value.array_lit.elems[i], func)) return 1;
            break;
        case AST_EXPR_INDEX:
            if (expr_references_func(e->value.index.base, func) || expr_references_func(e->value.index.index_expr, func)) return 1;
            break;
        default: break;
    }
    return 0;
}

/** 阶段 8.1 块内 DCE：将 name 加入 used 集合（去重），out 为指针数组，n 为当前个数，max 为上限。 */
static void add_used_var_name(const char *name, const char **out, int *n, int max) {
    if (!name || !out || !n || *n >= max) return;
    for (int i = 0; i < *n; i++) if (out[i] && strcmp(out[i], name) == 0) return;
    out[(*n)++] = name;
}

/** 从表达式中收集所有作为 VAR 出现的变量名到 out（用于块内 const/let DCE）。 */
static void collect_var_names_from_expr(const struct ASTExpr *e, const char **out, int *n, int max) {
    if (!e || *n >= max) return;
    if (e->kind == AST_EXPR_VAR && e->value.var.name)
        add_used_var_name(e->value.var.name, out, n, max);
    switch (e->kind) {
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            collect_var_names_from_expr(e->value.binop.left, out, n, max);
            collect_var_names_from_expr(e->value.binop.right, out, n, max);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC: case AST_EXPR_RETURN: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
            if (e->value.unary.operand) collect_var_names_from_expr(e->value.unary.operand, out, n, max);
            break;
        case AST_EXPR_AS:
            if (e->value.as_type.operand) collect_var_names_from_expr(e->value.as_type.operand, out, n, max);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_var_names_from_expr(e->value.if_expr.cond, out, n, max);
            if (e->value.if_expr.then_expr) collect_var_names_from_expr(e->value.if_expr.then_expr, out, n, max);
            if (e->value.if_expr.else_expr) collect_var_names_from_expr(e->value.if_expr.else_expr, out, n, max);
            break;
        case AST_EXPR_BLOCK:
            if (e->value.block) collect_var_names_from_block(e->value.block, out, n, max);
            break;
        case AST_EXPR_MATCH:
            collect_var_names_from_expr(e->value.match_expr.matched_expr, out, n, max);
            for (int i = 0; i < e->value.match_expr.num_arms; i++)
                collect_var_names_from_expr(e->value.match_expr.arms[i].result, out, n, max);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_var_names_from_expr(e->value.field_access.base, out, n, max);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++)
                collect_var_names_from_expr(e->value.struct_lit.inits[i], out, n, max);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++)
                collect_var_names_from_expr(e->value.array_lit.elems[i], out, n, max);
            break;
        case AST_EXPR_INDEX:
            collect_var_names_from_expr(e->value.index.base, out, n, max);
            collect_var_names_from_expr(e->value.index.index_expr, out, n, max);
            break;
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++)
                collect_var_names_from_expr(e->value.call.args[i], out, n, max);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_var_names_from_expr(e->value.method_call.base, out, n, max);
            for (int i = 0; i < e->value.method_call.num_args; i++)
                collect_var_names_from_expr(e->value.method_call.args[i], out, n, max);
            break;
        default: break;
    }
}

/** 从块中收集所有被引用的变量名（final_expr、const/let 的 init、循环 cond/body、defer、labeled）；用于仅输出被使用的 const/let。
 * 必须收集 while 的 cond（如 pad 在 while (z < pad) 中），否则 DCE 会漏掉 let pad 导致 -E 产出无 pad 声明的 C。 */
static void collect_var_names_from_block(const struct ASTBlock *b, const char **out, int *n, int max) {
    if (!b || *n >= max) return;
    for (int i = 0; i < b->num_consts; i++) {
        if (b->const_decls[i].init) collect_var_names_from_expr(b->const_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].init) collect_var_names_from_expr(b->let_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_loops; i++) {
        if (b->loops[i].cond) collect_var_names_from_expr(b->loops[i].cond, out, n, max);
        collect_var_names_from_block(b->loops[i].body, out, n, max);
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_var_names_from_expr(b->for_loops[i].init, out, n, max);
        if (b->for_loops[i].cond) collect_var_names_from_expr(b->for_loops[i].cond, out, n, max);
        if (b->for_loops[i].step) collect_var_names_from_expr(b->for_loops[i].step, out, n, max);
        collect_var_names_from_block(b->for_loops[i].body, out, n, max);
    }
    for (int i = 0; i < b->num_defers; i++)
        collect_var_names_from_block(b->defer_blocks[i], out, n, max);
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_var_names_from_expr(b->labeled_stmts[i].u.return_expr, out, n, max);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_var_names_from_expr(b->expr_stmts[i], out, n, max);
    if (b->final_expr) collect_var_names_from_expr(b->final_expr, out, n, max);
}

/** 判断 name 是否在 used 集合中（用于块内 const/let DCE）。 */
static int is_var_used(const char *name, const char **used, int n_used) {
    if (!name || !used) return 1;
    for (int i = 0; i < n_used; i++) if (used[i] && strcmp(used[i], name) == 0) return 1;
    return 0;
}

/** .su 用原语：块中第 idx 条 const 是否被引用（1=是 0=否），.su 据此决定是否输出。 */
int32_t codegen_su_block_const_is_used(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->const_decls || idx < 0 || idx >= b->num_consts) return 0;
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    const char *name = b->const_decls[idx].name ? b->const_decls[idx].name : "";
    return is_var_used(name, used_buf, n_used) ? 1 : 0;
}

/** .su 用原语：只写 const 声明前缀（indent + "const " + type + name + " = "），不写初值与分号。 */
int32_t codegen_su_emit_const_decl_prefix(uint8_t *out, uint8_t *block, int32_t idx, int32_t indent) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    FILE *f = (FILE *)out;
    if (!b || !f || !b->const_decls || idx < 0 || idx >= b->num_consts) return -1;
    const char *pad = (indent == 2) ? "  " : (indent == 4) ? "    " : "      ";
    const struct ASTType *ty = b->const_decls[idx].type;
    const struct ASTType *ety = codegen_emit_type(ty);
    if (ety && ety->kind == AST_TYPE_VECTOR) ensure_vector_typedef(ety, f);
    const char *name = b->const_decls[idx].name ? b->const_decls[idx].name : "";
    if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(f, "%sconst %s %s = ", pad, c_type_str(ety), name);
    else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
        fprintf(f, "%sconst ", pad);
        emit_local_array_decl(ety, name, "", f);
        fprintf(f, "= ");
    } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, f); fprintf(f, "%sconst %s %s = ", pad, c_type_str(ety), name); }
    else fprintf(f, "%sconst %s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
    return 0;
}

/** .su 用原语：只写 const 声明的初值部分（不写前缀与 ";\n"）。 */
int32_t codegen_su_emit_const_decl_init(uint8_t *out, uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    FILE *f = (FILE *)out;
    if (!b || !f || !b->const_decls || idx < 0 || idx >= b->num_consts) return -1;
    return codegen_init(b->const_decls[idx].type, b->const_decls[idx].init, f, b) != 0 ? -1 : 0;
}

/** .su 用原语：块中第 idx 条 let 是否被引用（1=是 0=否）。 */
int32_t codegen_su_block_let_is_used(uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    if (!b || !b->let_decls || idx < 0 || idx >= b->num_lets) return 0;
    const char *used_buf[MAX_BLOCK_USED_VARS];
    int n_used = 0;
    collect_var_names_from_block(b, used_buf, &n_used, MAX_BLOCK_USED_VARS);
    const char *name = b->let_decls[idx].name ? b->let_decls[idx].name : "";
    return is_var_used(name, used_buf, n_used) ? 1 : 0;
}

/** .su 用原语：只写 let 声明前缀（indent + type + name + " = "）。 */
int32_t codegen_su_emit_let_decl_prefix(uint8_t *out, uint8_t *block, int32_t idx, int32_t indent) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    FILE *f = (FILE *)out;
    if (!b || !f || !b->let_decls || idx < 0 || idx >= b->num_lets) return -1;
    const char *pad = (indent == 2) ? "  " : (indent == 4) ? "    " : "      ";
    const struct ASTType *ty = b->let_decls[idx].type;
    const struct ASTType *ety = codegen_emit_type(ty);
    if (ety && ety->kind == AST_TYPE_VECTOR) ensure_vector_typedef(ety, f);
    const char *name = b->let_decls[idx].name ? b->let_decls[idx].name : "";
    if (ety && ety->kind == AST_TYPE_PTR && ety->elem_type) fprintf(f, "%s%s * %s = ", pad, c_type_str(ety->elem_type), name);
    else if (ety && ety->kind == AST_TYPE_NAMED && ety->name) fprintf(f, "%s%s %s = ", pad, c_type_str(ety), name);
    else if (ety && ety->kind == AST_TYPE_ARRAY && ety->elem_type) {
        fprintf(f, "%s", pad);
        emit_local_array_decl(ety, name, "", f);
        fprintf(f, "= ");
    } else if (ety && ety->kind == AST_TYPE_SLICE && ety->elem_type) { ensure_slice_struct(ety, f); fprintf(f, "%s%s %s = ", pad, c_type_str(ety), name); }
    else fprintf(f, "%s%s %s = ", pad, ety ? c_type_str(ety) : "int32_t", name);
    return 0;
}

/** .su 用原语：只写 let 声明的初值部分。 */
int32_t codegen_su_emit_let_decl_init(uint8_t *out, uint8_t *block, int32_t idx) {
    const struct ASTBlock *b = (const struct ASTBlock *)block;
    FILE *f = (FILE *)out;
    if (!b || !f || !b->let_decls || idx < 0 || idx >= b->num_lets) return -1;
    return codegen_init(b->let_decls[idx].type, b->let_decls[idx].init, f, b) != 0 ? -1 : 0;
}

/** 判断块 b 中是否出现对 func 的调用（遍历 const/let/循环/labeled/final_expr）。 */
static int block_references_func(const struct ASTBlock *b, const struct ASTFunc *func) {
    if (!b || !func) return 0;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init && expr_references_func(b->const_decls[i].init, func)) return 1;
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init && expr_references_func(b->let_decls[i].init, func)) return 1;
    for (int i = 0; i < b->num_loops; i++)
        if (block_references_func(b->loops[i].body, func)) return 1;
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init && expr_references_func(b->for_loops[i].init, func)) return 1;
        if (b->for_loops[i].cond && expr_references_func(b->for_loops[i].cond, func)) return 1;
        if (b->for_loops[i].step && expr_references_func(b->for_loops[i].step, func)) return 1;
        if (block_references_func(b->for_loops[i].body, func)) return 1;
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr
            && expr_references_func(b->labeled_stmts[i].u.return_expr, func)) return 1;
    for (int i = 0; i < b->num_expr_stmts; i++)
        if (expr_references_func(b->expr_stmts[i], func)) return 1;
    if (b->final_expr && expr_references_func(b->final_expr, func)) return 1;
    return 0;
}

static void dce_collect_from_block(const struct ASTBlock *b, struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **worklist, int *n_wl, int max_wl, int *in_wl, int used_mono[][64], int used_mono_rows) {
    if (!b) return;
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].init) dce_collect_from_expr(b->const_decls[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].init) dce_collect_from_expr(b->let_decls[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_loops; i++)
        dce_collect_from_block(b->loops[i].body, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) dce_collect_from_expr(b->for_loops[i].init, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        if (b->for_loops[i].cond) dce_collect_from_expr(b->for_loops[i].cond, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        if (b->for_loops[i].step) dce_collect_from_expr(b->for_loops[i].step, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
        dce_collect_from_block(b->for_loops[i].body, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            dce_collect_from_expr(b->labeled_stmts[i].u.return_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    for (int i = 0; i < b->num_expr_stmts; i++)
        dce_collect_from_expr(b->expr_stmts[i], entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
    if (b->final_expr) dce_collect_from_expr(b->final_expr, entry, dep_mods, ndep, worklist, n_wl, max_wl, in_wl, used_mono, used_mono_rows);
}

void codegen_compute_used(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs_out, int *n_used_out, int max_used,
    int used_mono[][64]) {
    if (!entry || !entry->main_func || !used_funcs_out || !n_used_out || max_used <= 0) return;
    if (used_mono) {
        for (int r = 0; r <= ndep; r++)
            for (int k = 0; k < 64; k++) used_mono[r][k] = 0;
    }
    int n = 0;
    used_funcs_out[n++] = entry->main_func;
#define DCE_WORKLIST_MAX 512
    /* worklist 与 n_wl 放在同一 struct 内，避免栈上 n_wl 与 used_mono_rows 相邻导致 &n_wl 被误用为相邻变量地址（ASan 报 offset 52 越界） */
    struct dce_worklist {
        struct ASTFunc *list[DCE_WORKLIST_MAX];
        int n;
    } wl = { .n = 0 };
    wl.list[wl.n++] = (struct ASTFunc *)entry->main_func;
    int used_mono_rows = used_mono ? (1 + ndep) : 0;
    /* 种子：先遍历 main 体填满 worklist，再把 worklist 中所有函数加入 used，确保入口引用的 import 符号不被误删 */
    if (entry->main_func->body)
        dce_collect_from_block(entry->main_func->body, entry, dep_mods, ndep, wl.list, &wl.n, DCE_WORKLIST_MAX, NULL, used_mono, used_mono_rows);
    for (int i = 0; i < wl.n && n < max_used; i++) {
        struct ASTFunc *f = wl.list[i];
        if (!f) continue;
        int already = 0;
        for (int j = 0; j < n; j++) if (used_funcs_out[j] == f) { already = 1; break; }
        if (!already) used_funcs_out[n++] = f;
    }
    while (wl.n > 0) {
        struct ASTFunc *f = wl.list[--wl.n];
        if (!f || !f->body) continue;
        {
            int already = 0;
            for (int i = 0; i < n; i++) if (used_funcs_out[i] == f) { already = 1; break; }
            if (!already && n < max_used) used_funcs_out[n++] = f;
        }
        dce_collect_from_block(f->body, entry, dep_mods, ndep, wl.list, &wl.n, DCE_WORKLIST_MAX, NULL, used_mono, used_mono_rows);
    }
    *n_used_out = n;
#undef DCE_WORKLIST_MAX
}

/** 若 name 非空且未在 out[0..*n) 中则追加并返回 1，否则返回 0；*n 不超过 max。 */
static int add_used_type_name(const char *name, const char **out, int *n, int max) {
    if (!name || !*name || *n >= max) return 0;
    for (int i = 0; i < *n; i++) if (out[i] && strcmp(out[i], name) == 0) return 0;
    out[(*n)++] = name;
    return 1;
}

/** 从类型中收集 NAMED 类型名并递归 elem_type。 */
static void collect_type_from_type(const struct ASTType *ty, const char **out, int *n, int max) {
    if (!ty || *n >= max) return;
    if (ty->kind == AST_TYPE_NAMED && ty->name) add_used_type_name(ty->name, out, n, max);
    if (ty->elem_type) collect_type_from_type(ty->elem_type, out, n, max);
}

/** 从表达式中收集类型名（resolved_type、struct_lit.struct_name）并递归子表达式。 */
static void collect_type_from_expr(const struct ASTExpr *e, const char **out, int *n, int max) {
    if (!e || *n >= max) return;
    if (e->resolved_type) collect_type_from_type(e->resolved_type, out, n, max);
    if (e->kind == AST_EXPR_STRUCT_LIT && e->value.struct_lit.struct_name)
        add_used_type_name(e->value.struct_lit.struct_name, out, n, max);
    switch (e->kind) {
        case AST_EXPR_CALL:
            for (int i = 0; i < e->value.call.num_args; i++) collect_type_from_expr(e->value.call.args[i], out, n, max);
            break;
        case AST_EXPR_METHOD_CALL:
            collect_type_from_expr(e->value.method_call.base, out, n, max);
            for (int i = 0; i < e->value.method_call.num_args; i++) collect_type_from_expr(e->value.method_call.args[i], out, n, max);
            break;
        case AST_EXPR_ADD: case AST_EXPR_SUB: case AST_EXPR_MUL: case AST_EXPR_DIV: case AST_EXPR_MOD:
        case AST_EXPR_SHL: case AST_EXPR_SHR: case AST_EXPR_BITAND: case AST_EXPR_BITOR: case AST_EXPR_BITXOR:
        case AST_EXPR_EQ: case AST_EXPR_NE: case AST_EXPR_LT: case AST_EXPR_LE: case AST_EXPR_GT: case AST_EXPR_GE:
        case AST_EXPR_LOGAND: case AST_EXPR_LOGOR: case AST_EXPR_ASSIGN:
            collect_type_from_expr(e->value.binop.left, out, n, max);
            collect_type_from_expr(e->value.binop.right, out, n, max);
            break;
        case AST_EXPR_NEG: case AST_EXPR_BITNOT: case AST_EXPR_LOGNOT: case AST_EXPR_PANIC: case AST_EXPR_ADDR_OF: case AST_EXPR_DEREF:
        case AST_EXPR_RETURN:
            collect_type_from_expr(e->value.unary.operand, out, n, max);
            break;
        case AST_EXPR_AS:
            collect_type_from_expr(e->value.as_type.operand, out, n, max);
            break;
        case AST_EXPR_IF: case AST_EXPR_TERNARY:
            collect_type_from_expr(e->value.if_expr.cond, out, n, max);
            collect_type_from_expr(e->value.if_expr.then_expr, out, n, max);
            if (e->value.if_expr.else_expr) collect_type_from_expr(e->value.if_expr.else_expr, out, n, max);
            break;
        case AST_EXPR_MATCH:
            collect_type_from_expr(e->value.match_expr.matched_expr, out, n, max);
            for (int i = 0; i < e->value.match_expr.num_arms; i++) collect_type_from_expr(e->value.match_expr.arms[i].result, out, n, max);
            break;
        case AST_EXPR_FIELD_ACCESS:
            collect_type_from_expr(e->value.field_access.base, out, n, max);
            break;
        case AST_EXPR_STRUCT_LIT:
            for (int i = 0; i < e->value.struct_lit.num_fields; i++) collect_type_from_expr(e->value.struct_lit.inits[i], out, n, max);
            break;
        case AST_EXPR_ARRAY_LIT:
            for (int i = 0; i < e->value.array_lit.num_elems; i++) collect_type_from_expr(e->value.array_lit.elems[i], out, n, max);
            break;
        case AST_EXPR_INDEX:
            collect_type_from_expr(e->value.index.base, out, n, max);
            collect_type_from_expr(e->value.index.index_expr, out, n, max);
            break;
        default: break;
    }
}

/** 从块中收集类型名。 */
static void collect_type_from_block(const struct ASTBlock *b, const char **out, int *n, int max) {
    if (!b || *n >= max) return;
    for (int i = 0; i < b->num_consts; i++) {
        if (b->const_decls[i].type) collect_type_from_type(b->const_decls[i].type, out, n, max);
        if (b->const_decls[i].init) collect_type_from_expr(b->const_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_lets; i++) {
        if (b->let_decls[i].type) collect_type_from_type(b->let_decls[i].type, out, n, max);
        if (b->let_decls[i].init) collect_type_from_expr(b->let_decls[i].init, out, n, max);
    }
    for (int i = 0; i < b->num_loops; i++) collect_type_from_block(b->loops[i].body, out, n, max);
    for (int i = 0; i < b->num_for_loops; i++) {
        if (b->for_loops[i].init) collect_type_from_expr(b->for_loops[i].init, out, n, max);
        if (b->for_loops[i].cond) collect_type_from_expr(b->for_loops[i].cond, out, n, max);
        if (b->for_loops[i].step) collect_type_from_expr(b->for_loops[i].step, out, n, max);
        collect_type_from_block(b->for_loops[i].body, out, n, max);
    }
    for (int i = 0; i < b->num_labeled_stmts; i++)
        if (b->labeled_stmts[i].kind == AST_STMT_RETURN && b->labeled_stmts[i].u.return_expr)
            collect_type_from_expr(b->labeled_stmts[i].u.return_expr, out, n, max);
    for (int i = 0; i < b->num_expr_stmts; i++)
        collect_type_from_expr(b->expr_stmts[i], out, n, max);
    if (b->final_expr) collect_type_from_expr(b->final_expr, out, n, max);
}

/** 对已收集的类型名做结构体字段传递闭包：若某名为本模块或依赖中的 struct，则将其字段类型名加入集合（多轮至不动点）。 */
static void close_struct_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    const char **out, int *n, int max) {
    struct ASTModule *mods[33];
    int nmods = 0;
    if (entry) mods[nmods++] = entry;
    for (int i = 0; i < ndep && dep_mods && nmods < 33; i++) if (dep_mods[i]) mods[nmods++] = dep_mods[i];
    for (int round = 0; round < 8; round++) {
        int added = 0;
        for (int i = 0; i < *n; i++) {
            const char *name = out[i];
            if (!name) continue;
            for (int m = 0; m < nmods; m++) {
                struct ASTStructDef **sd = mods[m]->struct_defs;
                int num = mods[m]->num_structs;
                if (!sd) continue;
                for (int j = 0; j < num; j++) {
                    if (!sd[j] || !sd[j]->name || strcmp(sd[j]->name, name) != 0) continue;
                    for (int k = 0; k < sd[j]->num_fields; k++) {
                        const struct ASTType *fty = sd[j]->fields[k].type;
                        if (fty) collect_type_from_type(fty, out, n, max);
                    }
                    added = 1;
                    break;
                }
                if (added) break;
            }
        }
        if (!added) break;
    }
}

void codegen_compute_used_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs, int n_used, const char **used_type_names_out, int *n_out, int max_types) {
    if (!used_type_names_out || !n_out || max_types <= 0) return;
    *n_out = 0;
    for (int i = 0; i < n_used && used_funcs && used_funcs[i]; i++) {
        const struct ASTFunc *f = used_funcs[i];
        if (f->return_type) collect_type_from_type(f->return_type, used_type_names_out, n_out, max_types);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) collect_type_from_type(f->params[j].type, used_type_names_out, n_out, max_types);
        if (f->body) collect_type_from_block(f->body, used_type_names_out, n_out, max_types);
    }
    close_struct_types(entry, dep_mods, ndep, used_type_names_out, n_out, max_types);
}

/**
 * 阶段 3.1：仅输出 mods[0..n-1] 的类型定义（enum、struct，带 import_paths 前缀），不输出函数体。
 * 供 -E-extern 生成瘦 pipeline_gen.c 时先输出依赖类型，再输出入口模块（extern + 本体）。
 */
int codegen_emit_dep_types_only(struct ASTModule **mods, const char **import_paths, int n, FILE *out) {
    if (!mods || !import_paths || n < 0 || !out) return -1;
    codegen_emitted_type_names = NULL;
    codegen_slice_emitted_n = 0;
    static char lib_prefix_buf[256];
    for (int i = 0; i < n; i++) {
        const struct ASTModule *d = mods[i];
        if (!d) continue;
        char pre[256];
        import_path_to_c_prefix(import_paths[i] ? import_paths[i] : "", pre, sizeof(pre));
        (void)snprintf(lib_prefix_buf, sizeof(lib_prefix_buf), "%s", pre);
        /* 设置库前缀与当前模块，使 c_type_str/emit_struct_field_c_type 输出带前缀的类型名（如 ast_Block）。
         * 前面已输出的模块作为当前模块的 dep，便于字段类型跨模块时用正确前缀（如 parser 的 struct 引用 ast_Module）。 */
        codegen_library_prefix = lib_prefix_buf;
        codegen_library_module = (struct ASTModule *)d;
        codegen_dep_mods = i > 0 ? (struct ASTModule **)(mods) : NULL;
        codegen_dep_paths = i > 0 ? (const char **)(import_paths) : NULL;
        codegen_ndep = i > 0 ? i : 0;
        if (d->enum_defs) {
            for (int j = 0; j < d->num_enums; j++) {
                const struct ASTEnumDef *ed = d->enum_defs[j];
                if (!ed || !ed->name) continue;
                fprintf(out, "enum %s%s { ", pre, ed->name);
                for (int k = 0; k < ed->num_variants; k++) {
                    if (k > 0) fprintf(out, ", ");
                    fprintf(out, "%s%s_%s", pre, ed->name, ed->variant_names[k] ? ed->variant_names[k] : "");
                }
                fprintf(out, " };\n");
            }
        }
        if (d->struct_defs) {
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd) continue;
                for (int k = 0; k < sd->num_fields; k++)
                    if (sd->fields[k].type) ensure_slice_struct(sd->fields[k].type, out);
            }
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd || !sd->name) continue;
                fprintf(out, "struct %s%s { ", pre, sd->name);
                for (int k = 0; k < sd->num_fields; k++) {
                    const struct ASTType *fty = sd->fields[k].type;
                    const char *fname = sd->fields[k].name ? sd->fields[k].name : "";
                    emit_struct_field_c_type(fty, fname, out);
                }
                if (sd->packed)
                    fprintf(out, "} __attribute__((packed));\n");
                else
                    fprintf(out, "};\n");
            }
        }
    }
    return 0;
}

/**
 * 将入口模块生成 C；功能、参数、返回值见 codegen.h 声明处注释。
 * 多函数：先生成所有函数的 vector/slice 前置定义，再按「非 main 先、main 最后」生成各函数定义。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted) {
    if (!m || !out) return -1;
    if (!m->main_func || !m->main_func->body) return -1;
    if (strcmp(m->main_func->name, "main") != 0) return -1;
    if (!m->funcs || m->num_funcs <= 0) return -1;

    codegen_current_module = m;
    codegen_dep_mods = dep_mods;
    codegen_dep_paths = dep_import_paths;
    codegen_ndep = dep_mods && dep_import_paths ? ndep : 0;
    codegen_emitted_type_names = emitted_type_names;
    codegen_n_emitted_inout = n_emitted_inout;
    codegen_max_emitted = max_emitted;
    codegen_slice_emitted_n = 0;
    codegen_vector_emitted_n = 0;
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include <stdlib.h>\n");
    fprintf(out, "#include <stdint.h>\n");
    fprintf(out, "#include <stddef.h>\n");
    fprintf(out, "#include <string.h>\n"); /* memcpy 用于数组拷贝（自举 parser.su 中 let/const 数组 = 变量） */
    /* std.process：入口 main 会保存 argc/argv 到此，供 args_count/arg 读取 */
    fprintf(out, "extern int shulang_process_argc;\n");
    fprintf(out, "extern char **shulang_process_argv;\n");
    /* 单文件模式（emitted_type_names 非 NULL）时依赖类型已在前面写出，此处不再重复输出，避免 C 重定义 */
    if (!emitted_type_names && codegen_ndep > 0 && codegen_dep_mods && codegen_dep_paths) {
        /* 依赖模块中的 enum 须在 struct 之前输出，避免 struct 字段 "enum prefix_Name" 引用不完整类型 */
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->enum_defs) continue;
            char pre[256];
            import_path_to_c_prefix(codegen_dep_paths[i], pre, sizeof(pre));
            for (int j = 0; j < d->num_enums; j++) {
                const struct ASTEnumDef *ed = d->enum_defs[j];
                if (!ed || !ed->name) continue;
                fprintf(out, "enum %s%s { ", pre, ed->name);
                for (int k = 0; k < ed->num_variants; k++) {
                    if (k > 0) fprintf(out, ", ");
                    fprintf(out, "%s%s_%s", pre, ed->name, ed->variant_names[k] ? ed->variant_names[k] : "");
                }
                fprintf(out, " };\n");
            }
        }
        /* 依赖模块中的 struct 须在 extern 声明之前输出，避免 extern 引用不完整类型（如 std.mem.Buffer） */
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->struct_defs) continue;
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd) continue;
                for (int k = 0; k < sd->num_fields; k++)
                    if (sd->fields[k].type) ensure_slice_struct(sd->fields[k].type, out);
            }
        }
        for (int i = 0; i < codegen_ndep; i++) {
            const struct ASTModule *d = codegen_dep_mods[i];
            if (!d || !d->struct_defs) continue;
            char pre[256];
            import_path_to_c_prefix(codegen_dep_paths[i], pre, sizeof(pre));
            for (int j = 0; j < d->num_structs; j++) {
                const struct ASTStructDef *sd = d->struct_defs[j];
                if (!sd || !sd->name) continue;
                fprintf(out, "struct %s%s { ", pre, sd->name);
                for (int k = 0; k < sd->num_fields; k++) {
                    const struct ASTType *fty = sd->fields[k].type;
                    const char *fname = sd->fields[k].name ? sd->fields[k].name : "";
                    emit_struct_field_c_type(fty, fname, out);
                }
                fprintf(out, "};\n");
            }
        }
    }
    /* 跨模块调用：收集本模块内对 import 函数的调用，生成 extern 声明（含泛型单态化，阶段 7.3） */
    {
        const char *imp_paths[MAX_IMPORT_DECLS];
        struct ASTFunc *imp_funcs[MAX_IMPORT_DECLS];
        int nimp = 0;
        const char *gen_paths[MAX_GEN_IMPORT_DECLS];
        struct ASTFunc *gen_funcs[MAX_GEN_IMPORT_DECLS];
        struct ASTType **gen_type_args[MAX_GEN_IMPORT_DECLS];
        int gen_n[MAX_GEN_IMPORT_DECLS];
        int gen_count = 0;
        for (int i = 0; i < m->num_funcs && m->funcs; i++)
            if (m->funcs[i] && m->funcs[i]->body)
                collect_import_calls_from_block(m->funcs[i]->body, imp_paths, imp_funcs, &nimp,
                    gen_paths, gen_funcs, gen_type_args, gen_n, &gen_count);
        /* 入口使用 []T 时 extern 会引用 struct shulang_slice_*，须先输出 slice 结构体定义 */
        for (int i = 0; i < nimp; i++) {
            const struct ASTFunc *f = imp_funcs[i];
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int j = 0; j < f->num_params; j++)
                if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
        }
        for (int i = 0; i < gen_count; i++) {
            const struct ASTFunc *f = gen_funcs[i];
            struct ASTType **ta = gen_type_args[i];
            int nta = gen_n[i];
            const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, ta, nta);
            if (ret_ty) ensure_slice_struct(ret_ty, out);
            for (int j = 0; j < f->num_params; j++) {
                const struct ASTType *pt = subst_type(f->params[j].type, f->generic_param_names, ta, nta);
                if (pt) ensure_slice_struct(pt, out);
            }
        }
        for (int i = 0; i < nimp; i++) {
            char pre[256];
            import_path_to_c_prefix(imp_paths[i], pre, sizeof(pre));
            const struct ASTFunc *f = imp_funcs[i];
            fprintf(out, "extern %s %s%s(", c_type_str(f->return_type), pre, f->name ? f->name : "");
            for (int j = 0; j < f->num_params; j++) {
                if (j) fprintf(out, ", ");
                codegen_emit_param(&f->params[j], out, NULL);
            }
            fprintf(out, ");\n");
        }
        for (int i = 0; i < gen_count; i++) {
            const struct ASTFunc *f = gen_funcs[i];
            struct ASTType **ta = gen_type_args[i];
            int nta = gen_n[i];
            const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, ta, nta);
            char pre[256];
            import_path_to_c_prefix(gen_paths[i], pre, sizeof(pre));
            fprintf(out, "extern %s %s%s(", c_type_str(ret_ty), pre, mono_instance_mangled_name(f, ta, nta));
            for (int j = 0; j < f->num_params; j++) {
                if (j) fprintf(out, ", ");
                const struct ASTType *pt = subst_type(f->params[j].type, f->generic_param_names, ta, nta);
                codegen_emit_param(&f->params[j], out, pt);
            }
            fprintf(out, ");\n");
        }
    }
    /* 为所有函数体块及泛型单态化实例体生成 vector/slice 前置定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] && m->funcs[i]->body)
            ensure_block_vector_typedefs(m->funcs[i]->body, out);
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++)
        if (m->mono_instances[k].template && m->mono_instances[k].template->body)
            ensure_block_vector_typedefs(m->mono_instances[k].template->body, out);
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j]->body)
                ensure_block_vector_typedefs(m->impl_blocks[k]->funcs[j]->body, out);
    /* 入口模块自身函数若参数/返回为 []T，须先输出 slice 结构体定义，避免 C 不完整类型 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0) continue;
        if (f->return_type) ensure_slice_struct(f->return_type, out);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int p = 0; p < f->num_params; p++)
                if (f->params[p].type) ensure_slice_struct(f->params[p].type, out);
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        if (ret_ty) ensure_slice_struct(ret_ty, out);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (pt) ensure_slice_struct(pt, out);
        }
    }
    /* 顶层枚举定义 → C enum；阶段 8.1 DCE 扩展：若 is_type_used 非 NULL 则仅输出被引用枚举；单文件去重时已出现则跳过 */
    for (int i = 0; i < m->num_enums && m->enum_defs; i++) {
        const struct ASTEnumDef *ed = m->enum_defs[i];
        if (!ed || !ed->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, ed->name)) continue;
        if (emitted_type_names && n_emitted_inout && emitted_type_contains(ed->name, emitted_type_names, *n_emitted_inout)) continue;
        fprintf(out, "enum %s { ", ed->name);
        for (int j = 0; j < ed->num_variants; j++) {
            if (j > 0) fprintf(out, ", ");
            fprintf(out, "%s_%s", ed->name, ed->variant_names[j] ? ed->variant_names[j] : "");
        }
        fprintf(out, " };\n");
        if (emitted_type_names && n_emitted_inout) emitted_type_add(ed->name, emitted_type_names, n_emitted_inout, max_emitted);
    }
    /* 顶层结构体定义 → C struct；阶段 8.1 DCE 扩展：若 is_type_used 非 NULL 则仅输出被引用结构体；单文件去重时已出现则跳过。
     * 自举：若某结构体被本模块将输出的函数的返回/参数类型使用，则强制输出，避免 DCE 未收集到导致 incomplete type。 */
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || !sd->name) continue;
        {
            int need_for_sig = 0;
            for (int fi = 0; fi < m->num_funcs && m->funcs && !need_for_sig; fi++) {
                const struct ASTFunc *f = m->funcs[fi];
                if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0 || f->is_extern || !f->body) continue;
                if (f->return_type && f->return_type->kind == AST_TYPE_NAMED && f->return_type->name && strcmp(f->return_type->name, sd->name) == 0) need_for_sig = 1;
                for (int p = 0; p < f->num_params && !need_for_sig; p++)
                    if (f->params[p].type && f->params[p].type->kind == AST_TYPE_NAMED && f->params[p].type->name && strcmp(f->params[p].type->name, sd->name) == 0) need_for_sig = 1;
            }
            if (need_for_sig) { /* 被本模块某函数签名使用，必须输出，不因 DCE 跳过 */ }
            else if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name)) continue;
        }
        if (emitted_type_names && n_emitted_inout && emitted_type_contains(sd->name, emitted_type_names, *n_emitted_inout)) continue;
        fprintf(out, "struct %s { ", sd->name);
        for (int j = 0; j < sd->num_fields; j++) {
            const struct ASTType *fty = sd->fields[j].type;
            const char *fname = sd->fields[j].name ? sd->fields[j].name : "";
            emit_struct_field_c_type(fty, fname, out);
        }
        if (sd->packed)
            fprintf(out, "} __attribute__((packed));\n");
        else
            fprintf(out, "};\n");
        if (emitted_type_names && n_emitted_inout) emitted_type_add(sd->name, emitted_type_names, n_emitted_inout, max_emitted);
    }
    /* 冷路径辅助：panic 分支标记 noreturn+cold；单文件时已在第一个库块中输出，此处仅多文件时输出；static inline 避免与 runtime_panic.o 重复符号且可被同 TU 内 inline 调用 */
    if (!emitted_type_names) {
        fprintf(out, "static inline void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
        fprintf(out, "static inline void shulang_panic_(int has_msg, int msg_val) {\n");
        fprintf(out, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
        fprintf(out, "  abort();\n");
        fprintf(out, "}\n");
    }
    /* 入口模块内函数前向声明：满足 C 要求（任意顺序调用须先声明后定义）；对所有有体的非 main、非 extern、非泛型函数均声明，避免 DCE 未收集到的同模块 callee 导致 C undeclared */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0 || f->is_extern || !f->body) continue;
        fprintf(out, "static inline %s %s(", c_type_str(f->return_type), f->name ? f->name : "");
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            fprintf(out, "static inline %s %s(", c_type_str(f->return_type), impl_method_c_name(f));
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                codegen_emit_param(&f->params[p], out, NULL);
            }
            fprintf(out, ");\n");
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        fprintf(out, "static inline %s %s(", ret_ty ? c_type_str(ret_ty) : "int32_t", mono_instance_mangled_name(f, inst->type_args, inst->num_type_args));
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (p) fprintf(out, ", ");
            codegen_emit_param(&f->params[p], out, pt);
        }
        fprintf(out, ");\n");
    }
    /* 先输出非 main 函数，再输出 impl 方法、泛型单态化实例，最后 main；阶段 8.1 DCE 时仅输出已引用；若未在 used 中但被 main 体直接引用则兜底保留；extern 函数仅声明不生成定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") == 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (m->funcs[i]->is_extern || !m->funcs[i]->body) continue;
        /* 入口模块内被同模块调用的函数须全部生成定义，否则 DCE 未收集到的间接 callee 会导致链接未定义符号；此处不再按 DCE 过滤 */
        if (codegen_one_func(m->funcs[i], m, out) != 0) {
            fprintf(stderr, "codegen error: failed to emit function '%s'\n", m->funcs[i]->name ? m->funcs[i]->name : "?");
            return -1;
        }
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->impl_blocks[k]->funcs[j])) {
                if (!m->main_func || !m->main_func->body || !block_references_func(m->main_func->body, m->impl_blocks[k]->funcs[j])) continue;
            }
            if (codegen_one_impl_func(m->impl_blocks[k]->funcs[j], m, out) != 0) return -1;
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        if (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k)) continue;
        if (codegen_one_mono_instance(inst->template, inst->type_args, inst->num_type_args, m, out) != 0) return -1;
    }
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") != 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->funcs[i])) continue;
        if (codegen_one_func(m->funcs[i], m, out) != 0) return -1;
        break;
    }
    return 0;
}

/**
 * 将库模块生成 C（类型与函数带 import 前缀，避免与入口模块符号冲突）；功能见 codegen.h。阶段 8.1 DCE 时仅输出已引用。
 * lib_dep_mods/lib_dep_paths/n_lib_dep 为该库的 import 依赖，用于生成跨模块调用前缀（库内调用其他 import 时）。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted) {
    if (!m || !out) return -1;
    static char lib_prefix_buf[256];
    size_t off = 0;
    if (import_path) {
        for (const char *s = import_path; *s && off + 2 < sizeof(lib_prefix_buf); s++)
            lib_prefix_buf[off++] = (*s == '.') ? '_' : *s;
    }
    if (off + 1 < sizeof(lib_prefix_buf)) lib_prefix_buf[off++] = '_';
    lib_prefix_buf[off] = '\0';
    codegen_library_prefix = lib_prefix_buf;
    codegen_library_module = m;
    codegen_current_module = m;  /* 供 get_struct_field_type 解析本库内结构体（如 parser 的 OneFuncResult），以便结构体字面量走块形式 */
    codegen_library_import_path = import_path;
    codegen_dep_mods = lib_dep_mods;
    codegen_dep_paths = lib_dep_paths;
    codegen_ndep = (lib_dep_mods && lib_dep_paths) ? n_lib_dep : 0;
    codegen_emitted_type_names = emitted_type_names;
    codegen_n_emitted_inout = n_emitted_inout;
    codegen_max_emitted = max_emitted;
    codegen_slice_emitted_n = 0;

    /* 单文件模式时 include 与 panic 已由 driver 在写库前统一输出，此处不再输出；仅多文件（无 emitted_type_names）时每个库自己输出 include */
    if (!emitted_type_names) {
        fprintf(out, "/* generated from %s */\n", import_path ? import_path : "");
        fprintf(out, "#include <stdint.h>\n");
        fprintf(out, "#include <stddef.h>\n");
        fprintf(out, "#include <stdlib.h>\n");
        fprintf(out, "#include <stdio.h>\n");
        fprintf(out, "#include <string.h>\n"); /* memcpy 用于数组拷贝 */
    }

    /* 本库函数签名若含 []T，须最先输出 slice 结构体定义，否则后续 extern/前向声明中的 struct shulang_slice_* 为不完整类型导致 C 报错 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0) continue;
        if (f->return_type) ensure_slice_struct(f->return_type, out);
        for (int j = 0; j < f->num_params; j++)
            if (f->params[j].type) ensure_slice_struct(f->params[j].type, out);
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f) continue;
            if (f->return_type) ensure_slice_struct(f->return_type, out);
            for (int p = 0; p < f->num_params; p++)
                if (f->params[p].type) ensure_slice_struct(f->params[p].type, out);
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        if (ret_ty) ensure_slice_struct(ret_ty, out);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (pt) ensure_slice_struct(pt, out);
        }
    }

    /* 本库对 lib_dep 的调用：收集后生成 extern，避免 C 编译 undeclared */
    if (codegen_ndep > 0 && lib_dep_mods && lib_dep_paths) {
        const char *ext_paths[MAX_IMPORT_DECLS];
        struct ASTFunc *ext_funcs[MAX_IMPORT_DECLS];
        int n_ext = 0;
        for (int i = 0; i < m->num_funcs && m->funcs; i++)
            if (m->funcs[i] && m->funcs[i]->body)
                collect_lib_dep_calls_from_block(m->funcs[i]->body, lib_dep_mods, lib_dep_paths, n_lib_dep, ext_paths, ext_funcs, &n_ext, MAX_IMPORT_DECLS);
        for (int k = 0; k < n_ext && ext_paths[k] && ext_funcs[k]; k++) {
            char pre[256];
            import_path_to_c_prefix(ext_paths[k], pre, sizeof(pre));
            const struct ASTFunc *f = ext_funcs[k];
            fprintf(out, "extern %s %s%s(", c_type_str(f->return_type), pre, f->name ? f->name : "");
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                codegen_emit_param(&f->params[p], out, NULL);
            }
            fprintf(out, ");\n");
        }
    }

    for (int i = 0; i < m->num_funcs && m->funcs; i++)
        if (m->funcs[i] && m->funcs[i]->body)
            ensure_block_vector_typedefs(m->funcs[i]->body, out);
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++)
        if (m->mono_instances[k].template && m->mono_instances[k].template->body)
            ensure_block_vector_typedefs(m->mono_instances[k].template->body, out);
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++)
            if (m->impl_blocks[k]->funcs[j]->body)
                ensure_block_vector_typedefs(m->impl_blocks[k]->funcs[j]->body, out);

    for (int i = 0; i < m->num_enums && m->enum_defs; i++) {
        const struct ASTEnumDef *ed = m->enum_defs[i];
        if (!ed || !ed->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, ed->name)) continue;
        char ename[256];
        library_prefixed_name(ed->name, ename, sizeof(ename));
        if (emitted_type_names && n_emitted_inout && emitted_type_contains(ename, emitted_type_names, *n_emitted_inout)) continue;
        fprintf(out, "enum %s { ", ename);
        for (int j = 0; j < ed->num_variants; j++) {
            if (j > 0) fprintf(out, ", ");
            fprintf(out, "%s_%s", ename, ed->variant_names[j] ? ed->variant_names[j] : "");
        }
        fprintf(out, " };\n");
        if (emitted_type_names && n_emitted_inout) emitted_type_add(ename, emitted_type_names, n_emitted_inout, max_emitted);
    }
    /* 结构体字段若为 []T，须先输出 slice 结构体定义，避免 C 侧不完整类型 */
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name))) continue;
        for (int j = 0; j < sd->num_fields; j++)
            if (sd->fields[j].type) ensure_slice_struct(sd->fields[j].type, out);
    }
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || !sd->name) continue;
        if (dce_ctx && is_type_used && !is_type_used(dce_ctx, m, sd->name)) continue;
        char sname[256];
        library_prefixed_name(sd->name, sname, sizeof(sname));
        if (emitted_type_names && n_emitted_inout && emitted_type_contains(sname, emitted_type_names, *n_emitted_inout)) continue;
        fprintf(out, "struct %s { ", sname);
        for (int j = 0; j < sd->num_fields; j++) {
            const struct ASTType *fty = sd->fields[j].type;
            const char *fname = sd->fields[j].name ? sd->fields[j].name : "";
            emit_struct_field_c_type(fty, fname, out);
        }
        if (sd->packed)
            fprintf(out, "} __attribute__((packed));\n");
        else
            fprintf(out, "};\n");
        if (emitted_type_names && n_emitted_inout) emitted_type_add(sname, emitted_type_names, n_emitted_inout, max_emitted);
    }
    /* 单文件时 panic 已在第一个库的 include 块中输出；仅多文件（无 emitted_type_names）时每库各自输出 panic */
    if (!emitted_type_names) {
        fprintf(out, "static inline void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
        fprintf(out, "static inline void shulang_panic_(int has_msg, int msg_val) {\n");
        fprintf(out, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
        fprintf(out, "  abort();\n");
        fprintf(out, "}\n");
    }

    /* extern 函数：仅生成 C 的 extern 声明，符号名为 .su 中的函数名（与 C 一致），无定义 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || !f->is_extern) continue;
        fprintf(out, "extern %s %s(", c_type_str(f->return_type), f->name ? f->name : "");
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }

    /* 库模块内函数前向声明：满足 C 要求（递归或任意顺序调用时须先声明后定义）；无 static 以便符号可被入口模块链接 */
    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        const struct ASTFunc *f = m->funcs[i];
        if (!f || strcmp(f->name, "main") == 0 || f->num_generic_params > 0 || f->is_extern || !f->body) continue;
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, f)) continue;
        char fwd_name[256];
        library_prefixed_name(f->name, fwd_name, sizeof(fwd_name));
        if (codegen_library_import_path && !f->is_extern && (strcmp(codegen_library_import_path, "core.option") == 0 || strcmp(codegen_library_import_path, "core.result") == 0))
            fprintf(out, "static inline ");
        fprintf(out, "%s %s(", c_type_str(f->return_type), fwd_name);
        for (int j = 0; j < f->num_params; j++) {
            if (j) fprintf(out, ", ");
            codegen_emit_param(&f->params[j], out, NULL);
        }
        fprintf(out, ");\n");
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            const struct ASTFunc *f = m->impl_blocks[k]->funcs[j];
            if (!f || (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, f))) continue;
            char fwd_name[256];
            library_prefixed_name(impl_method_c_name(f), fwd_name, sizeof(fwd_name));
            fprintf(out, "%s %s(", c_type_str(f->return_type), fwd_name);
            for (int p = 0; p < f->num_params; p++) {
                if (p) fprintf(out, ", ");
                codegen_emit_param(&f->params[p], out, NULL);
            }
            fprintf(out, ");\n");
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args || (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k))) continue;
        const struct ASTFunc *f = inst->template;
        const struct ASTType *ret_ty = subst_type(f->return_type, f->generic_param_names, inst->type_args, inst->num_type_args);
        char fwd_name[256];
        library_prefixed_name(mono_instance_mangled_name(f, inst->type_args, inst->num_type_args), fwd_name, sizeof(fwd_name));
        fprintf(out, "%s %s(", ret_ty ? c_type_str(ret_ty) : "int32_t", fwd_name);
        for (int p = 0; p < f->num_params; p++) {
            const struct ASTType *pt = subst_type(f->params[p].type, f->generic_param_names, inst->type_args, inst->num_type_args);
            if (p) fprintf(out, ", ");
            codegen_emit_param(&f->params[p], out, pt);
        }
        fprintf(out, ");\n");
    }

    for (int i = 0; i < m->num_funcs && m->funcs; i++) {
        if (!m->funcs[i] || strcmp(m->funcs[i]->name, "main") == 0 || m->funcs[i]->num_generic_params > 0) continue;
        if (m->funcs[i]->is_extern || !m->funcs[i]->body) continue; /* extern 无体，不生成定义 */
        if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->funcs[i])) continue;
        if (codegen_one_func(m->funcs[i], m, out) != 0) { codegen_library_prefix = NULL; codegen_library_module = NULL; codegen_library_import_path = NULL; codegen_dep_mods = NULL; codegen_dep_paths = NULL; codegen_ndep = 0; return -1; }
    }
    for (int k = 0; k < m->num_impl_blocks && m->impl_blocks; k++)
        for (int j = 0; j < m->impl_blocks[k]->num_funcs; j++) {
            if (dce_ctx && is_func_used && !is_func_used(dce_ctx, m, m->impl_blocks[k]->funcs[j])) continue;
            if (codegen_one_impl_func(m->impl_blocks[k]->funcs[j], m, out) != 0) { codegen_library_prefix = NULL; codegen_library_module = NULL; codegen_library_import_path = NULL; codegen_dep_mods = NULL; codegen_dep_paths = NULL; codegen_ndep = 0; return -1; }
        }
    for (int k = 0; k < m->num_mono_instances && m->mono_instances; k++) {
        const struct ASTMonoInstance *inst = &m->mono_instances[k];
        if (!inst->template || !inst->type_args) continue;
        if (dce_ctx && is_mono_used && !is_mono_used(dce_ctx, m, k)) continue;
        if (codegen_one_mono_instance(inst->template, inst->type_args, inst->num_type_args, m, out) != 0) {
            codegen_library_prefix = NULL;
            codegen_library_module = NULL;
            codegen_library_import_path = NULL;
            codegen_dep_mods = NULL;
            codegen_dep_paths = NULL;
            codegen_ndep = 0;
            return -1;
        }
    }
    codegen_library_prefix = NULL;
    codegen_library_module = NULL;
    codegen_library_import_path = NULL;
    codegen_dep_mods = NULL;
    codegen_dep_paths = NULL;
    codegen_ndep = 0;
    return 0;
}
