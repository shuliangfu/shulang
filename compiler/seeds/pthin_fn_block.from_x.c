/* seeds/pthin_fn_block.from_x.c — G-02f-287 P2 parser thin P6 fn/block
 * Logic source: src/asm/pthin_fn_block.x
 * Hybrid: XLANG_PTHIN_FN_BLOCK_FROM_X + ld -r into parser_asm_thin_glue.o
 *
 * Bodies: struct_layout + library + one_function_buf + block_from_res
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser_asm_stretch_audit_gate.h"
#include "token.h"

struct parser_asm_token {
  int32_t kind;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t *ident;
  int32_t ident_len;
};

struct parser_asm_lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};

struct parser_asm_lexer_result {
  struct parser_asm_lexer next_lex;
  struct parser_asm_token tok;
  size_t token_start;
};

struct parser_asm_slice_u8 {
  uint8_t *data;
  size_t length;
};

struct parser_asm_library_parse_result {
  uint8_t ok;
  uint8_t _pad[4];
  struct parser_asm_lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  uint8_t _pad_tail[4];
};

struct parser_asm_library_parse_scan_result {
  uint8_t ok;
  uint8_t _pad[4];
  struct parser_asm_lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  uint8_t param_name[128];
  int32_t param_name_len;
  uint8_t param_type_name[128];
  int32_t param_type_len;
  uint8_t field_name[128];
  int32_t field_len;
  uint8_t _pad_tail[4];
};

struct parser_asm_onefunc_result {
  int32_t ok;
  struct parser_asm_lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  int32_t num_params;
  int32_t num_generic_params;
  int32_t num_consts;
  int32_t num_lets;
  int32_t has_if_expr;
  int32_t if_cond_true;
  int32_t if_then_val;
  int32_t if_else_val;
  int32_t if_cond_expr_ref;
  int32_t has_mul;
  int32_t mul_right_val;
  int32_t has_binop;
  int32_t binop_right_val;
  int32_t binop_left_param_idx;
  int32_t binop_right_param_idx;
  int32_t has_unary_neg;
  int32_t return_val;
  int32_t has_call_expr;
  uint8_t call_callee_name[128];
  int32_t call_callee_len;
  uint8_t return_var_name[128];
  int32_t return_var_name_len;
  int32_t return_expr_ref;
  int32_t has_final_expr;
  int32_t has_explicit_return_kw;
  int32_t call_num_args;
  int32_t num_loops;
  int32_t num_for_loops;
  int32_t num_if_stmts;
  int32_t num_src_stmt_order;
  int32_t num_src_body_expr_stmts;
  int32_t func_return_type_ref;
};

/* wave-fix: parser_asm_parse_expr_result used by parser_asm_one_function_buf_slice.inc
 * (expr_res / match_res / expr_stmt_res). Defined in sibling pthin TUs (ctrl/primary/
 * binop/etc.) but missing here → incomplete-type error. Single authority layout matches
 * pthin_ctrl.from_x.c. PLATFORM: SHARED. */
struct parser_asm_parse_expr_result {
  int32_t ok;
  int32_t expr_ref;
  struct parser_asm_lexer next_lex;
};

/* 9.6.3 wave-fix: parser_asm_top_level_let_result used by the static-desugar hook in
 * parser_asm_one_function_buf_slice.inc (function-local `static let/const` → module
 * top-level let). Defined in sibling pthin TUs (glue/seed_parse/thin_c) but missing
 * here → incomplete-type error. Single authority layout matches pthin_glue.from_x.c.
 * PLATFORM: SHARED. */
struct parser_asm_top_level_let_result {
  int32_t ok;
  uint8_t _pad[4];
  struct parser_asm_lexer next_lex;
};

struct ast_Type {
  int32_t kind;
  uint8_t name[128];
  int32_t name_len;
  int32_t elem_type_ref;
  int32_t array_size;
  uint8_t region_label[128];
  int32_t region_label_len;
};

enum {
  PARSER_ASM_TYPE_I32 = 0,
  PARSER_ASM_TYPE_BOOL = 1,
  PARSER_ASM_TYPE_U8 = 2,
  PARSER_ASM_TYPE_U32 = 3,
  PARSER_ASM_TYPE_U64 = 4,
  PARSER_ASM_TYPE_I64 = 5,
  PARSER_ASM_TYPE_USIZE = 6,
  PARSER_ASM_TYPE_ISIZE = 7,
  PARSER_ASM_TYPE_NAMED = 8,
  PARSER_ASM_TYPE_PTR = 9,
  PARSER_ASM_TYPE_ARRAY = 10,
  PARSER_ASM_TYPE_SLICE = 11,
  PARSER_ASM_TYPE_LINEAR = 12,
  PARSER_ASM_TYPE_VECTOR = 13,
  PARSER_ASM_TYPE_F32 = 14,
  PARSER_ASM_TYPE_F64 = 15,
  PARSER_ASM_TYPE_VOID = 16
};

struct ast_Expr {
  int32_t kind;
  int32_t resolved_type_ref;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t var_name[128];
  int32_t var_name_len;
  int32_t binop_left_ref;
  int32_t binop_right_ref;
  int32_t unary_operand_ref;
  int32_t if_cond_ref;
  int32_t if_then_ref;
  int32_t if_else_ref;
  int32_t block_ref;
  int32_t match_matched_ref;
  int32_t match_arm_base;
  int32_t match_num_arms;
  int32_t field_access_base_ref;
  uint8_t field_access_field_name[128];
  int32_t field_access_field_len;
  int32_t field_access_is_enum_variant;
  int32_t field_access_offset;
  int32_t field_access_soa_stride;
  int32_t index_base_ref;
  int32_t index_index_ref;
  int32_t index_base_is_slice;
  int32_t call_callee_ref;
  int32_t call_arg_base;
  int32_t call_num_args;
  int32_t call_num_type_args;
  int32_t method_call_base_ref;
  uint8_t method_call_name[128];
  int32_t method_call_name_len;
  int32_t method_call_arg_base;
  int32_t method_call_num_args;
  int32_t const_folded_val;
  int32_t const_folded_valid;
  int32_t index_proven_in_bounds;
  uint8_t struct_lit_struct_name[128];
  int32_t struct_lit_struct_name_len;
  int32_t struct_lit_field_base;
  int32_t struct_lit_num_fields;
  int32_t array_lit_elem_base;
  int32_t array_lit_num_elems;
  int32_t float_bits_lo;
  int32_t float_bits_hi;
  int32_t enum_variant_tag;
  int32_t as_operand_ref;
  int32_t as_target_type_ref;
  int32_t call_resolved_func_index;
  int32_t call_resolved_dep_index;
};

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *data);
extern struct parser_asm_lexer_result lexer_next_buf(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parser_asm_copy_slice_to_name64_at_end_slice_c(struct parser_asm_slice_u8 *source, size_t end_pos,
                                                          int32_t nlen, uint8_t *out);
extern void parser_asm_copy_slice_to_name64_buf_c(uint8_t *source, int32_t source_len, size_t start, int32_t nlen,
                                                 uint8_t *out);
extern int32_t parser_asm_parse_one_function_library_scan_slice_c(
    struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
    struct parser_asm_library_parse_scan_result *result);

#include "parser_asm_struct_layout_slice.inc"
#include "parser_asm_library_slice.inc"
#include "parser_asm_one_function_buf_slice.inc"
#include "parser_asm_block_from_res_slice.inc"

int labi_pthin_fn_block_slice_marker(void) {
  return 4; /* struct_layout + library + onefunc + block */
}
