/**
 * parser_asm_body_let_slice.inc — body let / cond expr 解析 helper C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 */
#ifndef PARSER_ASM_BODY_LET_SLICE_INCLUDED
#define PARSER_ASM_BODY_LET_SLICE_INCLUDED

/** 与 parser.x ParseExprResult 布局一致（bool→i32）。 */
struct parser_asm_parse_expr_result {
  int32_t ok;
  int32_t expr_ref;
  struct parser_asm_lexer next_lex;
};

extern void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                            struct parser_asm_parse_expr_result *out);
extern int32_t parser_asm_stretch_parse_cond_expr_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_parse_cond_expr_deep_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_body_let_bracket_deep_audit_c(void *lex_inout, void *source);

/**
 * let 初值 `[..] op [..]`：自 `[` 起点 parse_expr_into，更新 lex/r；成功返回 expr ref，失败 0。
 */
int32_t parser_asm_parse_body_let_bracket_compound_init_ref_slice_c(void *arena, size_t bracket_start,
                                                                    struct parser_asm_lexer lex,
                                                                    struct parser_asm_slice_u8 *source,
                                                                    struct parser_asm_lexer *lex_out,
                                                                    struct parser_asm_lexer_result *r_out) {
  struct parser_asm_lexer arr_lex;
  struct parser_asm_parse_expr_result arr_binop_res;
  if (!arena || !source || !lex_out || !r_out)
    return 0;
  arr_lex.pos = bracket_start;
  arr_lex.line = lex.line;
  arr_lex.col = lex.col;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_let_bracket_deep_audit_c(&arr_lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_array_lit_head_audit_c(&arr_lex, source));
  memset(&arr_binop_res, 0, sizeof(arr_binop_res));
  arr_binop_res.next_lex = arr_lex;
  parse_expr_into(arena, arr_lex, source, &arr_binop_res);
  if (!arr_binop_res.ok)
    return 0;
  lex_out->pos = arr_binop_res.next_lex.pos;
  lex_out->line = arr_binop_res.next_lex.line;
  lex_out->col = arr_binop_res.next_lex.col;
  lexer_next_into(r_out, arr_binop_res.next_lex, source);
  return arr_binop_res.expr_ref;
}

/**
 * parse_cond_expr_into：if/while 条件；int 后接 as 时从 int 起点 parse_expr（与 return 0 as T 一致）。
 * Also used for some return/expr-stmt paths — do not attach cond-only global state here.
 * Bare `if b {` disambiguation is in primary IDENT+LBRACE (looks_like_block; wave361).
 * PLATFORM: SHARED.
 */
void parser_asm_parse_cond_expr_into_slice_c(void *arena, struct parser_asm_lexer lex_start,
                                             struct parser_asm_slice_u8 *source,
                                             struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer_result rpeek;
  struct parser_asm_lexer_result r_as;
  struct parser_asm_lexer int_lex;
  size_t int_start;
  if (!arena || !source || !out)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_cond_expr_audit_c(&lex_start, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_cond_expr_deep_audit_c(&lex_start, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_cond_int_as_audit_c(&lex_start, source));
  lexer_next_into(&rpeek, lex_start, source);
  if (rpeek.tok.kind == (int32_t)TOKEN_INT) {
    int_start = rpeek.token_start;
    if (int_start == 0)
      int_start = rpeek.next_lex.pos - 1;
    int_lex.pos = int_start;
    int_lex.line = lex_start.line;
    int_lex.col = lex_start.col;
    lexer_next_into(&r_as, rpeek.next_lex, source);
    if (r_as.tok.kind == (int32_t)TOKEN_AS) {
      parse_expr_into(arena, int_lex, source, out);
      return;
    }
    parse_expr_into(arena, lex_start, source, out);
    return;
  }
  parse_expr_into(arena, lex_start, source, out);
}

#endif /* PARSER_ASM_BODY_LET_SLICE_INCLUDED */
