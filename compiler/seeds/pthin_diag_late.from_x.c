/* seeds/pthin_diag_late.from_x.c — G-02f-326 P2 parser thin diag_late
 * Logic source: src/asm/pthin_diag_late.x
 * Hybrid: XLANG_PTHIN_DIAG_LATE_FROM_X + ld -r into parser_asm_thin_glue.o
 *
 * Body: seeds/parser_asm/parser_asm_diag_late_slice.inc (~269)
 * diag_after_imports_then_structs + diag_fail_at_token_kind + diag_skip_let_const_buf + body_skip_buf
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




extern struct parser_asm_lexer_result lexer_next_buf(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *data);
extern void parser_asm_body_skip_let_const_then_if_into_slice_c(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern struct parser_asm_lexer parser_asm_diag_lex_after_imports_slice_c(struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_is_fn_sig_scalar_type_token_c(int32_t kind);
extern int32_t parser_asm_is_pointee_type_token_c(int32_t kind);
extern void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern struct parser_asm_lexer parser_asm_lexer_init_c(void);
extern struct parser_asm_lexer parser_asm_skip_one_struct_slice_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_array_type_bracket_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_bind_name_validate_c(const uint8_t *name, int32_t len);
extern int32_t parser_asm_stretch_diag_after_imports_structs_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_after_imports_then_structs_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_fail_at_token_kind_buf_audit_c(uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_fn_deep_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_diag_fn_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_fn_header_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_diag_fn_mega_full_deep_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_diag_fn_param_sig_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_diag_fn_return_type_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_diag_skip_let_const_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_skip_let_const_type_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_skip_let_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_diag_toplevel_after_imports_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_struct_fields_body_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_struct_header_audit_c(void *lex_inout, void *source);

#include "parser_asm_diag_late_slice.inc"

int labi_pthin_diag_late_slice_marker(void) {
  return 1;
}
