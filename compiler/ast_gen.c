/* generated from ast */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[64]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int32_t int_val; double float_val; uint8_t var_name[64]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_result_refs[16]; int32_t match_num_arms; int32_t field_access_base_ref; uint8_t field_access_field_name[64]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_refs[16]; int32_t call_num_args; int32_t method_call_base_ref; uint8_t method_call_name[64]; int32_t method_call_name_len; int32_t method_call_arg_refs[16]; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[64]; int32_t struct_lit_struct_name_len; int32_t struct_lit_num_fields; uint8_t struct_lit_field_names[8][64]; int32_t struct_lit_field_lens[8]; int32_t struct_lit_init_refs[8]; int32_t array_lit_num_elems; int32_t array_lit_elem_refs[16]; };
struct ast_ConstDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[32]; int32_t label_len; int32_t is_goto; uint8_t goto_target[32]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { struct ast_ConstDecl const_decls[24]; int32_t num_consts; struct ast_LetDecl let_decls[24]; int32_t num_lets; int32_t num_early_lets; struct ast_WhileLoop loops[8]; int32_t num_loops; struct ast_ForLoop for_loops[8]; int32_t num_for_loops; int32_t defer_block_refs[8]; int32_t num_defers; struct ast_LabeledStmt labeled_stmts[8]; int32_t num_labeled_stmts; int32_t expr_stmt_refs[32]; int32_t num_expr_stmts; int32_t final_expr_ref; struct ast_StmtOrderItem stmt_order[96]; int32_t num_stmt_order; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[64]; int32_t name_len; struct ast_Param params[16]; int32_t num_params; int32_t return_type_ref; int32_t body_ref; int32_t is_extern; };
struct ast_Module { struct ast_Func funcs[256]; int32_t num_funcs; int32_t main_func_index; uint8_t import_path_data[2048]; int32_t import_path_lens[32]; int32_t num_imports; };
struct ast_ASTArena { struct ast_Type types[512]; int32_t num_types; struct ast_Expr exprs[4096]; int32_t num_exprs; struct ast_Block blocks[512]; int32_t num_blocks; };
struct ast_PipelineDepCtx { struct ast_Module * dep_modules[32]; struct ast_ASTArena * dep_arenas[32]; int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t lib_root_bufs[8][256]; int32_t lib_root_lens[8]; uint8_t path_buf[512]; uint8_t loaded_buf[262144]; ptrdiff_t loaded_len; uint8_t preprocess_buf[262144]; int32_t preprocess_len; };
static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static void shulang_panic_(int has_msg, int msg_val) {
  if (has_msg) (void)fprintf(stderr, "%d\n", msg_val);
  abort();
}
int ast_ref_is_null(int32_t ref);
int32_t ast_ast_placeholder();
void ast_ast_arena_init(struct ast_ASTArena * arena);
int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena);
int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena);
int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena);
struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
int ast_ref_is_null(int32_t ref) {
  return ref == 0;
}
int32_t ast_ast_placeholder() {
  return 0;
}
void ast_ast_arena_init(struct ast_ASTArena * arena) {
  (void)(((arena)->num_types = 0));
  (void)(((arena)->num_exprs = 0));
  (void)(((arena)->num_blocks = 0));
}
int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp; if ((arena)->num_types >= 512) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_types = (arena)->num_types + 1));
  return (arena)->num_types;
}
int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp; if ((arena)->num_exprs >= 4096) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_exprs = (arena)->num_exprs + 1));
  return (arena)->num_exprs;
}
int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp; if ((arena)->num_blocks >= 512) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_blocks = (arena)->num_blocks + 1));
  return (arena)->num_blocks;
}
struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), ((arena)->types)[0]) : ((arena)->types)[ref - 1]);
}
void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((arena)->types)[ref - 1] = t, 0))));
}
struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 4096 ? (shulang_panic_(1, 0), ((arena)->exprs)[0]) : ((arena)->exprs)[ref - 1]);
}
void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 4096 ? (shulang_panic_(1, 0), 0) : (((arena)->exprs)[ref - 1] = e, 0))));
}
struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), ((arena)->blocks)[0]) : ((arena)->blocks)[ref - 1]);
}
void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((arena)->blocks)[ref - 1] = b, 0))));
}
