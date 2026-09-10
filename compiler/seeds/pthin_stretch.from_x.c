/* seeds/pthin_stretch.from_x.c — G-02f-290/318 P2 parser thin P9 stretch + suite
 * Logic source: src/asm/pthin_stretch.x
 * Hybrid: XLANG_PTHIN_STRETCH_FROM_X + ld -r into parser_asm_thin_glue.o
 *
 * Body: emit_heavy_stretch_slice.inc (lite) + suite_slice.inc (~28k) — G-02f-318
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

/* P1 lex_skip / mega rest helpers used by suite (ld -r) */
extern void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern int32_t parser_asm_is_compound_assign_token_c(int32_t kind);
extern struct parser_asm_lexer parser_asm_lexer_init_c(void);
extern void parser_asm_skip_balanced_parens_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                        struct parser_asm_slice_u8 *source);
extern void parser_asm_skip_balanced_braces_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                        struct parser_asm_slice_u8 *source);
extern struct parser_asm_lexer parser_asm_skip_imports_slice_c(struct parser_asm_lexer lex,
                                                              struct parser_asm_slice_u8 *source);
extern struct parser_asm_lexer parser_asm_skip_one_struct_slice_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern struct parser_asm_lexer_result parser_asm_diag_after_imports_then_structs_slice_c(
    struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);

/** stretch slice 前向声明（定义在 #include parser_asm_emit_heavy_stretch_*.c）。 */
int32_t parser_asm_stretch_token_run_len_c(int32_t kind);
int32_t parser_asm_stretch_struct_field_name_kind_c(int32_t kind);
int32_t parser_asm_stretch_struct_field_continues_kind_c(int32_t kind);
int32_t parser_asm_stretch_token_is_label_start_c(int32_t cur_kind, int32_t next_kind);
int32_t parser_asm_stretch_import_path_validate_c(const uint8_t *path, int32_t path_len);
int32_t parser_asm_stretch_import_path_finalize_c(uint8_t *path_buf, int32_t path_len, const uint8_t *source,
                                                  size_t source_len);
int32_t parser_asm_stretch_diag_after_imports_kind_c(int32_t kind);
int32_t parser_asm_stretch_verify_kw_spelling_c(const uint8_t *data, size_t len, size_t token_start, int32_t kind,
                                                int32_t run_len);
size_t parser_asm_stretch_skip_ws_and_comments_c(const uint8_t *data, size_t len, size_t pos);
void parser_asm_stretch_collect_imports_preamble_audit_c(struct parser_asm_lexer_result r,
                                                           struct parser_asm_lexer_result r2,
                                                           struct parser_asm_lexer_result r3,
                                                           struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_struct_fields_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                 int32_t *out_field_count);
int32_t parser_asm_stretch_enum_variants_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                 int32_t *out_variant_count);
int32_t parser_asm_stretch_fn_sig_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_struct_modifiers_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_async_fn_prefix_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_match_arms_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                              int32_t *out_arm_count);
int32_t parser_asm_stretch_block_stmt_kind_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                   int32_t *out_stmt_score);
int32_t parser_asm_stretch_top_level_let_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                 int32_t is_const);
int32_t parser_asm_stretch_if_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_loop_header_audit_c(void *lex_inout, void *source, int32_t expect_while);
int32_t parser_asm_stretch_let_const_decl_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_import_stmt_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_bind_name_validate_c(const uint8_t *name, int32_t len);
int32_t parser_asm_stretch_collect_imports_bind_audit_c(const uint8_t *bind, int32_t bind_len);
int32_t parser_asm_stretch_enum_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_extern_param_count_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                      int32_t *out_param_count);
int32_t parser_asm_stretch_import_select_list_audit_c(struct parser_asm_lexer *inout_lex,
                                                      struct parser_asm_slice_u8 *source, int32_t max_names);
int32_t parser_asm_stretch_struct_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_trait_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_impl_header_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_function_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_skip_allow_modifiers_c(struct parser_asm_lexer *inout_lex,
                                                  struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_import_path_post_audit_c(uint8_t *path_buf, int32_t path_len,
                                                    struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_peek_kind_chain_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                             int32_t *kinds, int32_t max_peek);
int32_t parser_asm_stretch_toplevel_kind_peek_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_match_kw_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_else_if_chain_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_type_ref_peek_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_skip_return_type_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_break_continue_audit_c(void *lex_inout, void *source, int32_t want_break);
int32_t parser_asm_stretch_else_stmt_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_import_dot_segment_audit_c(struct parser_asm_lexer_result r,
                                                      struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_cond_int_as_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_function_name_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_let_in_block_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_label_stmt_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_assign_stmt_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_const_import_kw_audit_c(int32_t after_assign_kind);
int32_t parser_asm_stretch_spawn_kw_audit_c(int32_t after_function_kind);
int32_t parser_asm_stretch_library_fn_shape_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_primary_head_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_match_subject_ident_audit_c(struct parser_asm_lexer_result r,
                                                       struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_struct_layout_name_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_expr_mul_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_addsub_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_onefunc_buf_name_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_panic_kw_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_shift_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_rel_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_eq_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_bitand_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_bitxor_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_bitor_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_logand_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_expr_logor_binop_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_as_suffix_chain_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_unary_prefix_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_if_expr_branch_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_simd_builtin_audit_c(struct parser_asm_lexer_result r_at,
                                                struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_struct_lit_fields_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                     int32_t *out_field_count);
int32_t parser_asm_stretch_array_lit_head_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_primary_suffix_chain_probe_c(struct parser_asm_lexer lex,
                                                        struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_field_access_name_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t name_len);
int32_t parser_asm_stretch_ternary_op_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_assign_op_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_if_stmt_branch_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_type_ref_deep_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_block_bind_name_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_call_args_shape_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                    int32_t *out_arg_count);
int32_t parser_asm_stretch_diag_fn_header_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_library_param_bind_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_paren_expr_head_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_vector_type_ident_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t nlen);
int32_t parser_asm_stretch_enum_variant_bind_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t name_len);
int32_t parser_asm_stretch_diag_toplevel_after_imports_audit_c(struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_diag_fn_param_sig_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_allow_kw_paren_audit_c(struct parser_asm_lexer_result r,
                                                  struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_try_skip_allow_paren_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_linear_type_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_array_type_bracket_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_slice_type_bracket_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_builtin_vec_token_audit_c(int32_t kind);
int32_t parser_asm_stretch_import_select_bind_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                      int32_t name_len);
int32_t parser_asm_stretch_extern_param_bind_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_diag_after_collect_preamble_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_balanced_parens_depth_probe_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_diag_fn_return_type_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_library_return_type_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_struct_field_bind_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t name_len);
int32_t parser_asm_stretch_enum_discriminant_kind_audit_c(int32_t kind);
int32_t parser_asm_stretch_struct_align_paren_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_body_skip_let_const_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_library_field_bind_audit_c(const uint8_t *name, int32_t name_len);
int32_t parser_asm_stretch_trait_method_return_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_impl_type_for_trait_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_extern_return_type_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_import_as_bind_audit_c(struct parser_asm_lexer_result r, struct parser_asm_slice_u8 *source);
int32_t parser_asm_stretch_diag_skip_let_const_type_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_diag_skip_let_const_type_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                int32_t len);
int32_t parser_asm_stretch_impl_fn_return_audit_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_trait_method_paren_audit_c(void *lex_inout, void *source);

int32_t parser_asm_stretch_balanced_braces_depth_probe_c(void *lex_inout, void *source);
int32_t parser_asm_stretch_balanced_braces_depth_probe_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_trait_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_impl_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_parse_one_extern_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_import_select_item_bind_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                           int32_t name_len);
int32_t parser_asm_stretch_import_select_brace_head_audit_c(struct parser_asm_lexer_result r);

int32_t parser_asm_stretch_balanced_parens_depth_probe_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_struct_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_enum_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_collect_imports_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_if_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_skip_one_extern_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);

int32_t parser_asm_stretch_try_skip_allow_paren_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
int32_t parser_asm_stretch_allow_kw_paren_buf_audit_c(struct parser_asm_lexer_result r, uint8_t *data, int32_t len);

#include "parser_asm_emit_heavy_stretch_slice.inc"
#include "parser_asm_emit_heavy_stretch_suite_slice.inc"

int labi_pthin_stretch_slice_marker(void) {
  return 1;
}

int labi_pthin_stretch_suite_slice_marker(void) {
  return 1;
}
