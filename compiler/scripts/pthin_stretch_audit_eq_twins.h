/* Suite skip helpers — verbatim extraction from the suite slice (the C
 * authority bodies; un-static'ed for the bridge, re-static'ed here for the
 * harness TU). Refresh together with the suite slice. */
extern void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);

int32_t parser_asm_stretch_is_type_start_kind_c(int32_t kind) {
  if (kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64 || kind == (int32_t)TOKEN_BOOL
      || kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32 || kind == (int32_t)TOKEN_U64
      || kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_VOID || kind == (int32_t)TOKEN_IDENT)
    return 1;
  return 0;
}

void parser_asm_stretch_skip_balanced_brackets_into_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source) {
  int32_t depth;
  struct parser_asm_lexer_result r;
  if (!out || !source)
    return;
  depth = 1;
  while (depth > 0) {
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_LBRACKET)
      depth++;
    else if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
      depth--;
      if (depth == 0) {
        out->pos = r.next_lex.pos;
        out->line = r.next_lex.line;
        out->col = r.next_lex.col;
        return;
      }
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF) {
      out->pos = lex.pos;
      out->line = lex.line;
      out->col = lex.col;
      return;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
  }
  out->pos = lex.pos;
  out->line = lex.line;
  out->col = lex.col;
}

struct parser_asm_lexer parser_asm_stretch_skip_type_suffix_c(struct parser_asm_lexer lex,
                                                                     struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer after;
  int32_t guard;
  guard = 0;
  for (;;) {
    if (guard++ > 64)
      break;
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_STAR) {
      lex = r.next_lex;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
      parser_asm_stretch_skip_balanced_brackets_into_c(&after, r.next_lex, source);
      lex = after;
      continue;
    }
    break;
  }
  return lex;
}

struct parser_asm_lexer parser_asm_stretch_skip_one_param_type_c(struct parser_asm_lexer lex,
                                                                        struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_STAR) {
    lex = parser_asm_stretch_skip_type_suffix_c(r.next_lex, source);
    return lex;
  }
  if (!parser_asm_stretch_is_type_start_kind_c(r.tok.kind))
    return lex;
  lex = parser_asm_stretch_skip_type_suffix_c(r.next_lex, source);
  return lex;
}

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

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_fn_param_list_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_fn_param_list(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  int32_t nparams;
  int32_t guard;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  nparams = 0;
  guard = 0;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
    *(struct parser_asm_lexer *)lex_inout = r.next_lex;
    return 1;
  }
  for (;;) {
    if (guard++ > 128)
      return 0;
    if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0 || r.tok.ident_len > 63)
      return 0;
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
    if (r.tok.kind != (int32_t)TOKEN_COLON)
      return 0;
    lex = parser_asm_stretch_skip_one_param_type_c(r.next_lex, source);
    nparams++;
    lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
    if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
      *(struct parser_asm_lexer *)lex_inout = r.next_lex;
      (void)nparams;
      return 1;
    }
    if (r.tok.kind != (int32_t)TOKEN_COMMA)
      return 0;
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  }

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_skip_return_type_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_skip_return_type(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  int32_t guard;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  guard = 0;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  while (r.tok.kind != (int32_t)TOKEN_LBRACE && r.tok.kind != (int32_t)TOKEN_EOF) {
    if (guard++ > 96)
      return 0;
    if (r.tok.kind == (int32_t)TOKEN_STAR) {
      lex = r.next_lex;
      lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
      continue;
    }
    if (parser_asm_stretch_is_type_start_kind_c(r.tok.kind)) {
      lex = parser_asm_stretch_skip_type_suffix_c(r.next_lex, source);
      lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
      struct parser_asm_lexer after;
      parser_asm_stretch_skip_balanced_brackets_into_c(&after, r.next_lex, source);
      lex = after;
      lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
      continue;
    }
    return 0;
  }
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return 0;
  *(struct parser_asm_lexer *)lex_inout = lex;
  return 1;

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_fn_sig_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_fn_sig(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer lex_cur;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION)
    return 0;
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0)
    return 0;
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN)
    return 0;
  lex_cur = r.next_lex;
  if (!c_ref_fn_param_list(&lex_cur, source))
    return 0;
  lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_COLON)
    return 0;
  lex_cur = r.next_lex;
  return c_ref_skip_return_type(&lex_cur, source);

}

/* Reference twin — verbatim copy of the gated C authority for
 * parser_asm_stretch_function_header_audit_c (suite slice; refresh in the same commit
 * whenever the suite twin changes). */
static int32_t c_ref_function_header(void *lex_inout, void *source) {

  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer lex_cur;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lex_cur = lex;
  lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind == (int32_t)TOKEN_ASYNC) {
    parser_asm_lex_from_result_val_into(&lex_cur, r);
    lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
  }
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION)
    return 0;
  parser_asm_lex_from_result_val_into(&lex_cur, r);
  lexer_next_into(&r, lex_cur, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LPAREN ? 1 : 0;

}
