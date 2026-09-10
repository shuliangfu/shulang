/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_if_header_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_if_header(void *lex_inout, void *source) {

  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IF)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LPAREN ? 1 : 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_loop_header_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_loop_header(void *lex_inout, void *source, int32_t expect_while) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  int32_t want;
  want = expect_while != 0 ? (int32_t)TOKEN_WHILE : (int32_t)TOKEN_FOR;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != want)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LPAREN ? 1 : 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_break_continue_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_break_continue(void *lex_inout, void *source, int32_t want_break) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  int32_t want;
  want = want_break != 0 ? (int32_t)TOKEN_BREAK : (int32_t)TOKEN_CONTINUE;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != want)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_SEMICOLON ? 1 : 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_else_stmt_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_else_stmt(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_ELSE)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind == (int32_t)TOKEN_IF || r.tok.kind == (int32_t)TOKEN_LBRACE)
    return 1;
  return 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_else_if_chain_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_else_if_chain(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_ELSE)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IF)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LPAREN ? 1 : 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_let_const_decl_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_let_const_decl(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_LET && r.tok.kind != (int32_t)TOKEN_CONST)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_COLON)
    return 0;
  return 1;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_enum_header_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_enum_header(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_ENUM)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LBRACE ? 1 : 0;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_match_kw_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_match_kw(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer lex_cur;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  int32_t guard;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_MATCH)
    return 0;
  lex_cur = r.next_lex;
  guard = 0;
  for (;;) {
    if (guard++ > 512)
      return 0;
    lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
    if (r.tok.kind == (int32_t)TOKEN_LBRACE)
      return 1;
    if (r.tok.kind == (int32_t)TOKEN_EOF || r.tok.kind == (int32_t)TOKEN_SEMICOLON)
      return 0;
    lex_cur = r.next_lex;
  }

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_return_stmt_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_return_stmt(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer lex_cur;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  int32_t guard;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_RETURN)
    return 0;
  lex_cur = r.next_lex;
  guard = 0;
  for (;;) {
    if (guard++ > 256)
      return 0;
    lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON)
      return 1;
    if (r.tok.kind == (int32_t)TOKEN_EOF)
      return 0;
    lex_cur = r.next_lex;
  }

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_import_stmt_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_import_stmt(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  int32_t guard;
  guard = 0;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IMPORT)
    return 0;
  parser_asm_lex_from_result_val_into(&lex, r);
  for (;;) {
    if (guard++ > 64)
      return 0;
    lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON)
      return 1;
    if (r.tok.kind == (int32_t)TOKEN_EOF)
      return 0;
    if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len == 2 && ((struct parser_asm_slice_u8 *)source)->data && r.token_start + 1 < ((struct parser_asm_slice_u8 *)source)->length
        && ((struct parser_asm_slice_u8 *)source)->data[r.token_start] == (uint8_t)'a' && ((struct parser_asm_slice_u8 *)source)->data[r.token_start + 1] == (uint8_t)'s')
      continue;
    parser_asm_lex_from_result_val_into(&lex, r);
  }

}
