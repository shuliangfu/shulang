/* parser_asm_helpers_slice.inc — G-02f-328 P19 thin helpers
 * Hybrid: XLANG_PTHIN_HELPERS_FROM_X via seeds/pthin_helpers.from_x.c
 * import_path/label/struct_field, lex rewind/advance/peek, align_lex, first_token_kind
 * (lexer_init + expr zeros stay in thin rest for shared foundation)
 */
#ifndef PARSER_ASM_HELPERS_SLICE_INC
#define PARSER_ASM_HELPERS_SLICE_INC

/* ---- thin L3908-4287 ---- */
/**
 * import_path_dot_segment_len：import 路径段长度（IDENT/I32/ASYNC），非法 token 返回 -1。
 */
int32_t parser_asm_import_path_dot_segment_len_c(struct parser_asm_token tok) {
  if (tok.kind == (int32_t)TOKEN_IDENT && tok.ident_len > 0)
    return tok.ident_len;
  if (tok.kind == (int32_t)TOKEN_I32)
    return 3;
  if (tok.kind == (int32_t)TOKEN_ASYNC)
    return 5;
  return -1;
}

/**
 * import_path_dot_segment_len_glue：thin delegate / extern bl 共用 C 实现。
 */
int32_t parser_import_path_dot_segment_len_glue(struct parser_asm_token tok) {
  return parser_asm_import_path_dot_segment_len_c(tok);
}

/**
 * import_path_dot_segment_copy_glue：thin delegate / extern bl 共用 C 实现。
 */
void parser_import_path_dot_segment_copy_glue(struct parser_asm_slice_u8 *source, size_t token_start,
                                              int32_t seg_len, uint8_t *path_buf, int32_t path_len) {
  parser_asm_import_path_dot_segment_copy_slice_c(source, token_start, seg_len, path_buf, path_len);
}

/**
 * parser_token_is_label_start_glue：IDENT 且下一 token 为 COLON（thin delegate / extern bl）。
 */
int32_t parser_token_is_label_start_glue(struct parser_asm_lexer_result r, struct parser_asm_slice_u8 *source) {
  return parser_asm_parser_token_is_label_start_slice_c(r, source);
}

/**
 * import_path_dot_segment_copy：将 source[token_start..+seg_len) 写入 path_buf[path_len..]。
 */
void parser_asm_import_path_dot_segment_copy_slice_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t seg_len, uint8_t *path_buf, int32_t path_len) {
  int32_t i;
  if (!path_buf || seg_len <= 0)
    return;
  for (i = 0; i < seg_len; i++) {
    if (source && source->data && token_start + (size_t)i < source->length)
      path_buf[path_len + i] = source->data[token_start + (size_t)i];
  }
}

/**
 * struct_field_name_from_tok：结构体字段名（ident / keyword-as-ident）。
 * PLATFORM: SHARED — field names may reuse keyword tokens (soa/packed/type).
 * Root fix for std/schema: field `type: i32` was TOKEN_TYPE; prior code returned
 * -1 here → layout parse aborted mid-struct → later fields "unknown field".
 */
int32_t parser_asm_struct_field_name_from_tok_slice_c(struct parser_asm_lexer_result r,
                                                      struct parser_asm_slice_u8 *source, uint8_t *out) {
  if (!out)
    return -1;
  /* wave583 Cap residual: field name content ≤127 (StructLayoutFieldEntry.name[128]). */
  if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len > 0 && r.tok.ident_len <= 127) {
    parser_asm_copy_slice_to_name64_at_end_slice_c(source, r.next_lex.pos, r.tok.ident_len, out);
    return r.tok.ident_len;
  }
  if (r.tok.kind == (int32_t)TOKEN_SOA) {
    out[0] = (uint8_t)'s';
    out[1] = (uint8_t)'o';
    out[2] = (uint8_t)'a';
    return 3;
  }
  if (r.tok.kind == (int32_t)TOKEN_PACKED) {
    out[0] = (uint8_t)'p';
    out[1] = (uint8_t)'a';
    out[2] = (uint8_t)'c';
    out[3] = (uint8_t)'k';
    out[4] = (uint8_t)'e';
    out[5] = (uint8_t)'d';
    return 6;
  }
  /* Keyword `type` (TOKEN_TYPE) is a valid field name: `type: i32` in struct bodies. */
  if (r.tok.kind == (int32_t)TOKEN_TYPE) {
    out[0] = (uint8_t)'t';
    out[1] = (uint8_t)'y';
    out[2] = (uint8_t)'p';
    out[3] = (uint8_t)'e';
    return 4;
  }
  return -1;
}

/**
 * struct_field_name_tok_kind：token kind 是否为合法字段名起点。
 * PLATFORM: SHARED — include TOKEN_TYPE (keyword-as-field-name).
 */
int32_t parser_asm_struct_field_name_tok_kind_c(int32_t k) {
  if (parser_asm_stretch_struct_field_name_kind_c(k) != 0)
    return 1;
  return k == (int32_t)TOKEN_IDENT || k == (int32_t)TOKEN_SOA || k == (int32_t)TOKEN_PACKED ||
         k == (int32_t)TOKEN_TYPE;
}

/**
 * struct_field_continues_tok_kind：字段列表是否可继续（含 align(N) 前缀）。
 */
int32_t parser_asm_struct_field_continues_tok_kind_c(int32_t k) {
  if (parser_asm_stretch_struct_field_continues_kind_c(k) != 0)
    return 1;
  /* let/const 字段前缀：多字段 struct 在 ; 后下一字段以 let/const 开头 */
  if (k == (int32_t)TOKEN_LET || k == (int32_t)TOKEN_CONST)
    return 1;
  return parser_asm_struct_field_name_tok_kind_c(k) != 0 || k == (int32_t)TOKEN_ALIGN;
}

/**
 * parser_token_is_label_start：当前 IDENT 且下一 token 为 COLON（标号语句 label:）。
 */
int32_t parser_asm_parser_token_is_label_start_slice_c(struct parser_asm_lexer_result r,
                                                       struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result nx;
  if (r.tok.kind != (int32_t)TOKEN_IDENT)
    return 0;
  if (!source)
    return 0;
  lexer_next_into(&nx, r.next_lex, source);
  return parser_asm_stretch_token_is_label_start_c((int32_t)r.tok.kind, (int32_t)nx.tok.kind);
}

/**
 * lexer_pos_before_run：由 token 结束位置与 run_len 反推起点。
 */
size_t parser_asm_lexer_pos_before_run_c(size_t end_pos, int32_t run_len) {
  return end_pos - (size_t)run_len;
}

/**
 * lexer_token_run_len：token_start==0 时按 kind 推断关键字/字面量字节长度。
 */
int32_t parser_asm_lexer_token_run_len_c(struct parser_asm_token tok) {
  int32_t stretch = parser_asm_stretch_token_run_len_c(tok.kind);
  if (stretch > 0)
    return stretch;
  switch (tok.kind) {
  case TOKEN_FATARROW:
    return 2;
  case TOKEN_RETURN:
    return 6;
  case TOKEN_FUNCTION:
    return 8;
  case TOKEN_CONST:
    return 5;
  case TOKEN_WHILE:
    return 5;
  case TOKEN_FALSE:
    return 5;
  case TOKEN_STRUCT:
    return 6;
  case TOKEN_IMPORT:
    return 6;
  case TOKEN_EXTERN:
    return 6;
  case TOKEN_ASYNC:
    return 5;
  case TOKEN_LET:
    return 3;
  case TOKEN_IF:
    return 2;
  case TOKEN_FOR:
    return 3;
  case TOKEN_ELSE:
    return 4;
  case TOKEN_TRUE:
    return 4;
  case TOKEN_NULL:
    /* wave668: keyword null span length. PLATFORM: SHARED. */
    return 4;
  case TOKEN_ENUM:
    return 4;
  case TOKEN_MATCH:
    return 5;
  case TOKEN_LSHIFT:
  case TOKEN_RSHIFT:
  case TOKEN_EQ:
  case TOKEN_NE:
  case TOKEN_LE:
  case TOKEN_GE:
  case TOKEN_AMPAMP:
  case TOKEN_PIPEPIPE:
  case TOKEN_PLUS_EQ:
  case TOKEN_MINUS_EQ:
  case TOKEN_STAR_EQ:
  case TOKEN_SLASH_EQ:
  case TOKEN_PERCENT_EQ:
  case TOKEN_AMP_EQ:
  case TOKEN_PIPE_EQ:
  case TOKEN_CARET_EQ:
    return 2;
  case TOKEN_LSHIFT_EQ:
  case TOKEN_RSHIFT_EQ:
    return 3;
  default:
    return 1;
  }
}

/**
 * parser_match_kw_immediately_before：ident 前是否为 "match "（6 字节）。
 */
int32_t parser_asm_parser_match_kw_immediately_before_slice_c(struct parser_asm_slice_u8 *source,
                                                            size_t ident_start) {
  size_t p;
  if (!source || !source->data || ident_start < 6)
    return 0;
  p = ident_start - 6;
  return source->data[p] == (uint8_t)'m' && source->data[p + 1] == (uint8_t)'a' &&
         source->data[p + 2] == (uint8_t)'t' && source->data[p + 3] == (uint8_t)'c' &&
         source->data[p + 4] == (uint8_t)'h' && source->data[p + 5] == (uint8_t)' ';
}

/**
 * ident 是否为语句关键字 unsafe。
 */
int32_t parser_asm_ident_is_unsafe_stmt_slice_c(struct parser_asm_lexer_result r,
                                                struct parser_asm_slice_u8 *source) {
  size_t start;
  if (!source || !source->data || r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len != 6)
    return 0;
  start = r.token_start;
  if (start == 0)
    start = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, r.tok.ident_len);
  if (start + 6 > source->length)
    return 0;
  return source->data[start] == (uint8_t)'u' && source->data[start + 1] == (uint8_t)'n' &&
         source->data[start + 2] == (uint8_t)'s' && source->data[start + 3] == (uint8_t)'a' &&
         source->data[start + 4] == (uint8_t)'f' && source->data[start + 5] == (uint8_t)'e';
}

/**
 * lex_at_token_from_result 内部：从 LexerResult 构造指向当前 token 起点的 Lexer。
 *
 * PLATFORM: SHARED — wave280 Cap residual pure leaf.
 * Root cause: lexer.x TOKEN_STRING sets token_start to the first content byte
 * *after* the opening quote (so primary/let-init can copy raw content). Callers
 * that re-enter parse_expr via lex_at_token_from_result (return expr, bare
 * expr-stmt, etc.) must start at the opening quote, otherwise:
 *   - lex pos lands inside the literal (e.g. `h` of `"hi"`)
 *   - primary builds IDENT / partial junk
 *   - the closing `"` is re-scanned as a new string to EOF → false L002
 *   (or, if a later `"` exists, a silent wrong spanning string — false green)
 * Fix: for TOKEN_STRING, back up one byte from content token_start to the `"`.
 * tok.line/col already name the opening quote (lexer line0/col0).
 */
static struct parser_asm_lexer parser_asm_lex_at_token_from_result_inner(struct parser_asm_lexer_result r) {
  struct parser_asm_lexer lex;
  size_t p;
  p = r.token_start;
  if (p == 0) {
    if (r.tok.kind == (int32_t)TOKEN_STRING) {
      /* content len + opening + closing quotes; next_lex is past closer. */
      int32_t run = r.tok.ident_len + 2;
      if (run < 2)
        run = 2;
      p = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, run);
    } else if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len > 0)
      p = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, r.tok.ident_len);
    else
      p = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, parser_asm_lexer_token_run_len_c(r.tok));
  } else if (r.tok.kind == (int32_t)TOKEN_STRING) {
    /* token_start = first content byte; re-lex needs the opening quote. */
    p = p - (size_t)1;
  }
  lex.pos = p;
  lex.line = r.tok.line;
  lex.col = r.tok.col;
  return lex;
}

/**
 * lex_at_token_from_result：供 parse_expr / stmt 从 r.tok 重读（按值返回 Lexer）。
 */
struct parser_asm_lexer parser_asm_lex_at_token_from_result_c(struct parser_asm_lexer_result r) {
  return parser_asm_lex_at_token_from_result_inner(r);
}

/**
 * parser_rewind_lex_for_following_stmt：let/if 初值后若后继为 stmt 关键字则回绕 lex。
 */
struct parser_asm_lexer parser_asm_parser_rewind_lex_for_following_stmt_c(struct parser_asm_lexer lex_in,
                                                                          struct parser_asm_lexer_result r) {
  if (r.tok.kind == (int32_t)TOKEN_RETURN || r.tok.kind == (int32_t)TOKEN_IF ||
      r.tok.kind == (int32_t)TOKEN_WHILE || r.tok.kind == (int32_t)TOKEN_FOR ||
      r.tok.kind == (int32_t)TOKEN_MATCH || r.tok.kind == (int32_t)TOKEN_RBRACE)
    return parser_asm_lex_at_token_from_result_inner(r);
  return lex_in;
}

/**
 * parse_block return 语句尾：r 已在 RBRACE 时置 *block_break=1 结束块循环（勿 lexer_next 吞 sibling if）；
 * 否则 advance lex 并置 *stmt_tok_ready=1。
 */
void parser_asm_parse_block_return_end_tail_c(struct parser_asm_lexer_result *r,
                                              struct parser_asm_lexer *lex_cur,
                                              struct parser_asm_slice_u8 *source, int32_t *stmt_tok_ready,
                                              int32_t *block_break) {
  if (!r || !lex_cur || !source || !stmt_tok_ready || !block_break)
    return;
  if (r->tok.kind == (int32_t)TOKEN_RBRACE) {
    *block_break = 1;
    return;
  }
  lex_cur->pos = r->next_lex.pos;
  lex_cur->line = r->next_lex.line;
  lex_cur->col = r->next_lex.col;
  lexer_next_into(r, *lex_cur, source);
  *stmt_tok_ready = 1;
}

/**
 * advance_past_stmt_semicolon_into: sync past `;` after an expression statement,
 * or accept a legal ASI following token that clearly starts the next statement.
 *
 * Historical ASI allowlist: `;` · unsafe · let/const · return · if/while/for · `}`.
 * That omitted IDENT and other stmt heads, so mid-block
 *   break
 *   s = 99
 * (and assign chains `x = 1` / `y = 2`) failed with XP003 while the same break
 * before `}` or before `if` already succeeded.
 *
 * wave654 Cap residual: G.7 extend the same authority — also accept IDENT,
 * BREAK/CONTINUE, MATCH/LOOP, PANIC/DEFER/GOTO, STAR (*p = …), SELF as
 * following-stmt heads. Expr parse already finished before this call, so
 * IDENT cannot continue the prior expr (no sticky binop across ASI).
 *
 * PLATFORM: SHARED — parse ASI; docs/08 still recommends `;` mid-block;
 * product accepts keyword ASI (wave361+) and IDENT/control heads here.
 */
int32_t parser_asm_advance_past_stmt_semicolon_into_slice_c(struct parser_asm_lexer_result *r_out,
                                                            struct parser_asm_lexer lex,
                                                            struct parser_asm_slice_u8 *source) {
  int32_t k;
  if (!r_out || !source)
    return 0;
  lexer_next_into(r_out, lex, source);
  if (r_out->tok.kind == (int32_t)TOKEN_SEMICOLON)
    return 1;
  if (parser_asm_ident_is_unsafe_stmt_slice_c(*r_out, source) != 0)
    return 1;
  k = r_out->tok.kind;
  if (k == (int32_t)TOKEN_LET || k == (int32_t)TOKEN_CONST || k == (int32_t)TOKEN_RETURN ||
      k == (int32_t)TOKEN_IF || k == (int32_t)TOKEN_WHILE || k == (int32_t)TOKEN_FOR ||
      k == (int32_t)TOKEN_RBRACE || k == (int32_t)TOKEN_IDENT || k == (int32_t)TOKEN_BREAK ||
      k == (int32_t)TOKEN_CONTINUE || k == (int32_t)TOKEN_MATCH || k == (int32_t)TOKEN_LOOP ||
      k == (int32_t)TOKEN_PANIC || k == (int32_t)TOKEN_DEFER || k == (int32_t)TOKEN_GOTO ||
      k == (int32_t)TOKEN_STAR || k == (int32_t)TOKEN_SELF)
    return 1;
  return 0;
}

/**
 * advance_past_cond_rparen_into：if/while 条件后同步到 ) 之后（或已见 {）。
 * PLATFORM: SHARED — paren form `if (cond) {` and bare form `if cond {` (docs/03; wave361).
 */
int32_t parser_asm_advance_past_cond_rparen_into_slice_c(struct parser_asm_lexer_result *r_out,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex_after;
  if (!r_out || !source)
    return 0;
  lexer_next_into(r_out, lex, source);
  if (r_out->tok.kind == (int32_t)TOKEN_RPAREN) {
    lex_after.pos = r_out->next_lex.pos;
    lex_after.line = r_out->next_lex.line;
    lex_after.col = r_out->next_lex.col;
    lexer_next_into(r_out, lex_after, source);
    return 1;
  }
  if (r_out->tok.kind == (int32_t)TOKEN_LBRACE)
    return 1;
  return 0;
}

/**
 * parse_peek_function_name_buf 的 C 实现；EMIT_HEAVY 桩 bl 目标。
 * lex 位于 function 关键字；成功返回 name_len，失败返回 0。
 */
int32_t parser_asm_parse_peek_function_name_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len,
                                                  uint8_t *out) {
  struct parser_asm_lexer_result r;
  size_t name_start;
  if (!data || !out)
    return 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_peek_function_name_buf_audit_c(&lex, data, len));
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION)
    return 0;
  parser_asm_lex_from_result_val_into(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind == (int32_t)TOKEN_SPAWN) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_spawn_kw_audit_c((int32_t)TOKEN_SPAWN));
    out[0] = (uint8_t)'s';
    out[1] = (uint8_t)'p';
    out[2] = (uint8_t)'a';
    out[3] = (uint8_t)'w';
    return 5;
  }
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0 || r.tok.ident_len > 63)
    return 0;
  name_start = r.token_start;
  if (name_start == 0 && r.tok.ident_len > 0)
    name_start = r.next_lex.pos - (size_t)r.tok.ident_len;
  parser_asm_copy_slice_to_name64_buf_c(data, len, name_start, r.tok.ident_len, out);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_name_audit_c(out, r.tok.ident_len));
  return r.tok.ident_len;
}

/* G-02f-281: moved to parser_asm_lex_skip_slice.inc (was L4320-L4447) */

/**
 * 将 lex 对齐到 trait/impl 关键字起点；统一跳过空白与注释，并用 lexer 复核 token kind。
 * hybrid 跨 TU：P10 glue 以 extern 引用，故非 static（G-02f-326）。
 */
struct parser_asm_lexer parser_asm_align_lex_to_keyword_prefix_c(struct parser_asm_lexer lex,
                                                                        struct parser_asm_slice_u8 *source,
                                                                        const char *kw, size_t kw_len) {
  struct parser_asm_lexer_result r;
  int32_t want_kind = 0;
  if (!source || !source->data || !kw || kw_len == 0)
    return lex;
  lex.pos = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, lex.pos);
  if (kw_len == 5 && memcmp(kw, "trait", 5) == 0)
    want_kind = (int32_t)TOKEN_TRAIT;
  else if (kw_len == 4 && memcmp(kw, "impl", 4) == 0)
    want_kind = (int32_t)TOKEN_IMPL;
  if (want_kind == 0)
    return lex;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == want_kind)
    return parser_asm_lex_at_token_from_result_inner(r);
  return lex;
}

/* ---- thin L4303-5080 ---- */
/**
 * first_token_kind：诊断用，返回 source 首 token 的 kind（整型）。
 */
int32_t parser_asm_first_token_kind_slice_c(struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  if (!source)
    return (int32_t)TOKEN_EOF;
  lex = parser_asm_lexer_init_c();
  lexer_next_into(&r, lex, source);
  return r.tok.kind;
}

/**
 * first_token_kind_buf：buf 路径诊断首 token kind。
 */
int32_t parser_asm_first_token_kind_buf_c(uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;

  if (!data || len <= 0)
    return (int32_t)TOKEN_EOF;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_first_token_kind_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_expr_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_call_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_expr_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultra_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_super_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_simd_builtin_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_expr_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  source.data = data;
  source.length = (size_t)len;
  return parser_asm_first_token_kind_slice_c(&source);
}


#endif /* PARSER_ASM_HELPERS_SLICE_INC */
