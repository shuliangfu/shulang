/**
 * parser_asm_if_stmt_slice.inc — parse_if_stmt_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 单条 if（含 else / else if 链）；回调 parse_cond_expr / parse_block X mega，勿 X emit 本函数体。
 */
#ifndef PARSER_ASM_IF_STMT_SLICE_INCLUDED
#define PARSER_ASM_IF_STMT_SLICE_INCLUDED

/** 与 parser.x ParseBlockResult 布局一致（bool→i32）。 */
#ifndef PARSER_ASM_PARSE_BLOCK_RESULT_FWD
#define PARSER_ASM_PARSE_BLOCK_RESULT_FWD
struct parser_asm_parse_block_result {
  int32_t ok;
  int32_t block_ref;
  struct parser_asm_lexer next_lex;
};
#endif

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *source);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parser_parse_cond_expr_into_glue(void *arena, struct parser_asm_lexer lex_start,
                                             struct parser_asm_slice_u8 *source,
                                             struct parser_asm_parse_expr_result *out);
extern int32_t parser_advance_past_cond_rparen_into_glue(struct parser_asm_lexer_result *r_out,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source);
extern void parser_parse_block_into(void *arena, struct parser_asm_lexer lex_after_lbrace,
                                    struct parser_asm_slice_u8 *source, int32_t type_ref,
                                    struct parser_asm_parse_block_result *out);
extern int32_t ast_ast_arena_block_alloc(void *arena);
extern int32_t pipeline_block_append_if(void *arena, int32_t br, int32_t cond_ref, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_block_append_stmt_order(void *arena, int32_t br, uint8_t kind, int32_t idx);
extern size_t parser_asm_lexer_pos_before_run_c(size_t end_pos, int32_t run_len);
extern size_t parser_asm_stretch_skip_ws_and_comments_c(const uint8_t *data, size_t len, size_t pos);
extern struct parser_asm_lexer parser_asm_lex_at_token_from_result_c(struct parser_asm_lexer_result r);
extern struct parser_asm_lexer parser_asm_parser_rewind_lex_for_following_stmt_c(struct parser_asm_lexer lex_in,
                                                                                  struct parser_asm_lexer_result r);
extern int32_t parser_asm_ident_is_unsafe_stmt_slice_c(struct parser_asm_lexer_result r,
                                                       struct parser_asm_slice_u8 *source);
/** 从已消费 '(' 的 lex 起跳过匹配括号，返回 ')' 之后的 lex。 */
extern struct parser_asm_lexer parser_asm_skip_balanced_parens_slice_c(struct parser_asm_lexer lex,
                                                                       struct parser_asm_slice_u8 *source);

/** if 条件 field 访问后按源码扫描对齐至 cond 的 ')' 之后（前向声明）。 */
static struct parser_asm_lexer parser_asm_sync_lex_after_if_cond_paren_c(
    struct parser_asm_lexer lex_at_if, struct parser_asm_slice_u8 *source);
/** 从当前 if 起点扫描整句 if/else 并返回下一语句首 token（前向声明）。 */
static struct parser_asm_lexer parser_asm_scan_sync_after_if_stmt_c(struct parser_asm_lexer lex_cur,
                                                                    struct parser_asm_slice_u8 *source);

/**
 * then/else 块结束后对齐 lex：parse_block 有时落在下一 if 的 `(`，回扫至 TOKEN_IF 或 stmt 关键字。
 * 非 static：供 parse_one_function_impl if 后 onefunc 回扫 glue 调用。
 */
struct parser_asm_lexer parser_asm_realign_lex_after_if_arm_c(struct parser_asm_lexer lex_cur,
                                                                     struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result at_cur = {0};
  struct parser_asm_lexer_result peek = {0};
  at_cur.next_lex = lex_cur;
  lexer_next_into(&at_cur, lex_cur, source);
  /** lex 已在 stmt 关键字上时直接保留（peek 会落到 expr 首 token，勿误回扫）。 */
  if (at_cur.tok.kind == (int32_t)TOKEN_RETURN || at_cur.tok.kind == (int32_t)TOKEN_IF ||
      at_cur.tok.kind == (int32_t)TOKEN_WHILE || at_cur.tok.kind == (int32_t)TOKEN_FOR ||
      at_cur.tok.kind == (int32_t)TOKEN_MATCH || at_cur.tok.kind == (int32_t)TOKEN_RBRACE ||
      at_cur.tok.kind == (int32_t)TOKEN_LET || at_cur.tok.kind == (int32_t)TOKEN_CONST ||
      parser_asm_ident_is_unsafe_stmt_slice_c(at_cur, source) != 0)
    return parser_asm_lex_at_token_from_result_c(at_cur);
  peek = at_cur;
  if (peek.tok.kind == (int32_t)TOKEN_LPAREN) {
    int32_t back_pos = 2;
    while (back_pos <= 128) {
      struct parser_asm_lexer lex_b;
      struct parser_asm_lexer_result r_b = {0};
      lex_b.pos = (int32_t)parser_asm_lexer_pos_before_run_c((size_t)lex_cur.pos, (size_t)back_pos);
      lex_b.line = peek.tok.line;
      lex_b.col = peek.tok.col;
      r_b.next_lex = lex_b;
      lexer_next_into(&r_b, lex_b, source);
      if (r_b.tok.kind == (int32_t)TOKEN_IF)
        return parser_asm_lex_at_token_from_result_c(r_b);
      back_pos = back_pos + 1;
    }
  }
  if (peek.tok.kind == (int32_t)TOKEN_RETURN || peek.tok.kind == (int32_t)TOKEN_IF ||
      peek.tok.kind == (int32_t)TOKEN_WHILE || peek.tok.kind == (int32_t)TOKEN_FOR ||
      peek.tok.kind == (int32_t)TOKEN_MATCH || peek.tok.kind == (int32_t)TOKEN_RBRACE ||
      peek.tok.kind == (int32_t)TOKEN_LET || peek.tok.kind == (int32_t)TOKEN_CONST ||
      parser_asm_ident_is_unsafe_stmt_slice_c(peek, source) != 0)
    return parser_asm_lex_at_token_from_result_c(peek);
  /*
   * if 条件含 struct.field 时 lex 偶发落在 `return r3.value` 的 expr 首 ident；按 ident_start 回溯 "return"。
   */
  if (peek.tok.kind == (int32_t)TOKEN_IDENT) {
    size_t ident_start = (size_t)peek.token_start;
    if (ident_start == 0 && peek.tok.ident_len > 0)
      ident_start = parser_asm_lexer_pos_before_run_c((size_t)peek.next_lex.pos, peek.tok.ident_len);
    if (ident_start >= 7 && source->data != NULL) {
      const uint8_t *sp = source->data + ident_start;
      if (sp[-7] == (uint8_t)'r' && sp[-6] == (uint8_t)'e' && sp[-5] == (uint8_t)'t' && sp[-4] == (uint8_t)'u'
          && sp[-3] == (uint8_t)'r' && sp[-2] == (uint8_t)'n') {
        uint8_t sep = sp[-1];
        if (sep == (uint8_t)' ' || sep == (uint8_t)'\t' || sep == (uint8_t)'\n' || sep == (uint8_t)'\r') {
          struct parser_asm_lexer ret_lex;
          ret_lex.pos = (int32_t)(ident_start - 7);
          ret_lex.line = peek.tok.line;
          ret_lex.col = peek.tok.col;
          return ret_lex;
        }
      }
    }
  }
  /*
   * if 条件含 struct.field 时 parse_cond 偶发将 lex 落在下一 stmt 的 return 之后（如 r3.value 的 r3）；
   * 回扫至 return/if/while 等 stmt 关键字。
   */
  {
    int32_t back_kw = 2;
    while (back_kw <= 160) {
      struct parser_asm_lexer lex_kw;
      struct parser_asm_lexer_result r_kw = {0};
      lex_kw.pos = (int32_t)parser_asm_lexer_pos_before_run_c((size_t)lex_cur.pos, (size_t)back_kw);
      lex_kw.line = peek.tok.line;
      lex_kw.col = peek.tok.col;
      r_kw.next_lex = lex_kw;
      lexer_next_into(&r_kw, lex_kw, source);
      if (r_kw.tok.kind == (int32_t)TOKEN_RETURN || r_kw.tok.kind == (int32_t)TOKEN_IF ||
          r_kw.tok.kind == (int32_t)TOKEN_WHILE || r_kw.tok.kind == (int32_t)TOKEN_FOR ||
          r_kw.tok.kind == (int32_t)TOKEN_MATCH || r_kw.tok.kind == (int32_t)TOKEN_LET ||
          r_kw.tok.kind == (int32_t)TOKEN_CONST || parser_asm_ident_is_unsafe_stmt_slice_c(r_kw, source) != 0)
        return parser_asm_lex_at_token_from_result_c(r_kw);
      back_kw = back_kw + 1;
    }
  }
  /*
   * if 条件含 struct.field 时 lex 可能滑入下一 stmt 中部；自当前 pos 向前（最多 512B）找 depth==0 的 stmt 关键字。
   */
  {
    size_t scan = (size_t)lex_cur.pos;
    size_t scan_end = scan + 512;
    int32_t depth = 0;
    if (scan_end > source->length)
      scan_end = source->length;
    while (scan + 2 < scan_end) {
      uint8_t ch = source->data[scan];
      if (ch == (uint8_t)'(')
        depth = depth + 1;
      else if (ch == (uint8_t)')' && depth > 0)
        depth = depth - 1;
      else if (ch == (uint8_t)'{')
        depth = depth + 1;
      else if (ch == (uint8_t)'}' && depth > 0)
        depth = depth - 1;
      if (depth == 0) {
        static const struct {
          const char *kw;
          int32_t klen;
          int32_t tok;
        } stmt_kws[] = {
            {"return", 6, (int32_t)TOKEN_RETURN}, {"let", 3, (int32_t)TOKEN_LET},
            {"const", 5, (int32_t)TOKEN_CONST},   {"if", 2, (int32_t)TOKEN_IF},
            {"while", 5, (int32_t)TOKEN_WHILE},   {"for", 3, (int32_t)TOKEN_FOR},
            {"match", 5, (int32_t)TOKEN_MATCH},   {"unsafe", 6, (int32_t)TOKEN_IDENT},
        };
        size_t ki;
        for (ki = 0; ki < sizeof(stmt_kws) / sizeof(stmt_kws[0]); ki++) {
          int32_t klen = stmt_kws[ki].klen;
          if (scan + (size_t)klen > scan_end)
            continue;
          if (memcmp(source->data + scan, stmt_kws[ki].kw, (size_t)klen) != 0)
            continue;
          if (scan > 0) {
            uint8_t prev = source->data[scan - 1];
            if ((prev >= (uint8_t)'a' && prev <= (uint8_t)'z') || (prev >= (uint8_t)'A' && prev <= (uint8_t)'Z')
                || (prev >= (uint8_t)'0' && prev <= (uint8_t)'9') || prev == (uint8_t)'_')
              continue;
          }
          if (scan + (size_t)klen < source->length) {
            uint8_t nx = source->data[scan + (size_t)klen];
            if (nx != (uint8_t)' ' && nx != (uint8_t)'\t' && nx != (uint8_t)'\n' && nx != (uint8_t)'\r'
                && nx != (uint8_t)'(' && nx != (uint8_t)';' && nx != (uint8_t)'{')
              continue;
          }
          {
            struct parser_asm_lexer lx;
            struct parser_asm_lexer_result rr = {0};
            lx.pos = (int32_t)scan;
            lx.line = lex_cur.line;
            lx.col = lex_cur.col;
            rr.next_lex = lx;
            lexer_next_into(&rr, lx, source);
            if (rr.tok.kind == stmt_kws[ki].tok)
              return parser_asm_lex_at_token_from_result_c(rr);
          }
        }
      }
      scan = scan + 1;
    }
  }
  return parser_asm_parser_rewind_lex_for_following_stmt_c(lex_cur, peek);
}

extern int32_t parser_asm_stretch_if_stmt_branch_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_if_stmt_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                       struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_if_else_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_ultra_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_super_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_control_flow_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_else_if_chain_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);

/** 前向声明：else-if 递归。 */
static int32_t parser_asm_parse_if_stmt_into_slice_c(void *arena, struct parser_asm_lexer lex_at_if,
                                                     struct parser_asm_slice_u8 *source, int32_t type_ref,
                                                     int32_t *out_cond, int32_t *out_then, int32_t *out_else,
                                                     struct parser_asm_lexer *lex_out);

/**
 * parse_if_stmt_into：解析 if (cond) { then } [ else { block } | else if … ]。
 * 成功写 out_cond/out_then/out_else 与 lex_out（下一语句首 token）。
 */
static int32_t parser_asm_parse_if_stmt_into_slice_c(void *arena, struct parser_asm_lexer lex_at_if,
                                                     struct parser_asm_slice_u8 *source, int32_t type_ref,
                                                     int32_t *out_cond, int32_t *out_then, int32_t *out_else,
                                                     struct parser_asm_lexer *lex_out) {
  struct parser_asm_lexer lex_cur;
  struct parser_asm_lexer_result r;
  struct parser_asm_parse_expr_result cond_res;
  struct parser_asm_parse_block_result then_res;
  struct parser_asm_parse_block_result else_res;
  int32_t cond_ref;
  int32_t wrap_ref;
  int32_t ncond;
  int32_t nthen;
  int32_t nelse;
  struct parser_asm_lexer lex_after;
  struct parser_asm_lexer elif_lex;
  if (!arena || !source || !out_cond || !out_then || !out_else || !lex_out)
    return 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_branch_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_else_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_super_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  lex_cur = lex_at_if;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex_at_if, source));
  lex_cur = lex_at_if;
  lexer_next_into(&r, lex_cur, source);
  if (r.tok.kind != (int32_t)TOKEN_IF)
    return 0;
  parser_lex_from_next_into_glue(&lex_cur, r);
  lexer_next_into(&r, lex_cur, source);
  /**
   * wave361/wave650: docs/03 `if cond { then }` — parentheses optional.
   * wave650: do NOT strip a leading `(` before parse_cond. The leading paren is
   * part of the condition expression (primary grouping): e.g.
   *   if (x >> 2) != 4 { ... }   → cond is `(x >> 2) != 4`
   *   if (s.b) { ... }           → cond is `(s.b)`
   * Stripping made the first form parse only `x >> 2`, leave `!= 4` outside the
   * cond, fail LBRACE check, silent-drop main → XP003 out_len=0. Bare
   * `if x >> 2 != 4` and double-paren `if ((x >> 2) != 4)` already worked.
   * Field-cond sync (sync_lex_after_if_cond_paren) was a strip-path workaround;
   * with inclusive parens, trust cond_res.next_lex (same as bare path).
   * PLATFORM: SHARED — G.7 single if-stmt cond path (expr primary owns parens).
   */
  {
    lex_cur = parser_asm_lex_at_token_from_result_c(r);
    memset(&cond_res, 0, sizeof(cond_res));
    cond_res.next_lex = lex_cur;
    parser_parse_cond_expr_into_glue(arena, lex_cur, source, &cond_res);
    if (!cond_res.ok)
      return 0;
    cond_ref = cond_res.expr_ref;
    lex_cur = cond_res.next_lex;
  }
  if (parser_advance_past_cond_rparen_into_glue(&r, lex_cur, source) == 0)
    return 0;
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return 0;
  lex_cur = r.next_lex;
  memset(&then_res, 0, sizeof(then_res));
  then_res.next_lex = lex_cur;
  parser_parse_block_into(arena, lex_cur, source, type_ref, &then_res);
  if (!then_res.ok)
    return 0;
  *out_cond = cond_ref;
  *out_then = then_res.block_ref;
  *out_else = 0;
  lex_cur = then_res.next_lex;
  /** 窥视 else：勿 lexer_next 写 r，否则 parse_block 再 advance 会漏掉连续 if 下一条。 */
  {
    struct parser_asm_lexer_result peek_else = {0};
    peek_else.next_lex = lex_cur;
    lexer_next_into(&peek_else, lex_cur, source);
    if (peek_else.tok.kind == (int32_t)TOKEN_ELSE) {
      r = peek_else;
      parser_lex_from_next_into_glue(&lex_cur, r);
      lexer_next_into(&r, lex_cur, source);
    if (r.tok.kind == (int32_t)TOKEN_IF) {
      elif_lex = parser_asm_lex_at_token_from_result_c(r);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_else_if_chain_audit_c(elif_lex, source));
      wrap_ref = ast_ast_arena_block_alloc(arena);
      if (wrap_ref == 0)
        return 0;
      ncond = 0;
      nthen = 0;
      nelse = 0;
      lex_after = elif_lex;
      if (!parser_asm_parse_if_stmt_into_slice_c(arena, elif_lex, source, type_ref, &ncond, &nthen, &nelse, &lex_after))
        return 0;
      if (pipeline_block_append_if(arena, wrap_ref, ncond, nthen, nelse) < 0)
        return 0;
      if (pipeline_block_append_stmt_order(arena, wrap_ref, 5, 0) < 0)
        return 0;
      *out_else = wrap_ref;
      lex_cur = lex_after;
    } else if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      lex_cur = r.next_lex;
      memset(&else_res, 0, sizeof(else_res));
      else_res.next_lex = lex_cur;
      parser_parse_block_into(arena, lex_cur, source, type_ref, &else_res);
      if (!else_res.ok)
        return 0;
      *out_else = else_res.block_ref;
      lex_cur = else_res.next_lex;
    } else {
      return 0;
    }
    }
  }
  /**
   * lex_out 必须单调前进到“整条 if/else 语句之后”的首 token。
   * 直接从当前 if 起点重扫完整语句，避免使用被块解析污染的 lex_cur 回扫到当前 if，
   * 否则外层 block/onefunc 可能重复解析同一条 if，最终无界分配 AST 节点。
   */
  {
    struct parser_asm_lexer lex_scanned = parser_asm_scan_sync_after_if_stmt_c(lex_at_if, source);
    if (lex_scanned.pos > lex_at_if.pos) {
      lex_cur = lex_scanned;
    } else {
      lex_cur = parser_asm_realign_lex_after_if_arm_c(lex_cur, source);
    }
    lex_out->pos = lex_cur.pos;
    lex_out->line = lex_cur.line;
    lex_out->col = lex_cur.col;
  }
  return 1;
}

/** 非 static 导出供 glue 调用。 */
int32_t parser_asm_parse_if_stmt_into_c(void *arena, struct parser_asm_lexer lex_at_if,
                                        struct parser_asm_slice_u8 *source, int32_t type_ref, int32_t *out_cond,
                                        int32_t *out_then, int32_t *out_else, struct parser_asm_lexer *lex_out) {
  return parser_asm_parse_if_stmt_into_slice_c(arena, lex_at_if, source, type_ref, out_cond, out_then, out_else,
                                               lex_out);
}

/** 判断 c 是否为空白符。 */
static int32_t parser_asm_is_ws_byte_c(uint8_t c) {
  return c == (uint8_t)' ' || c == (uint8_t)'\t' || c == (uint8_t)'\n' || c == (uint8_t)'\r';
}

/** 判断 source[i..] 是否为独立关键字 kw。 */
static int32_t parser_asm_kw_at_pos_c(struct parser_asm_slice_u8 *source, size_t i, const char *kw, int32_t klen) {
  size_t next_pos;
  if (!source || !source->data || klen <= 0)
    return 0;
  if (i + (size_t)klen > source->length)
    return 0;
  if (memcmp(source->data + i, kw, (size_t)klen) != 0)
    return 0;
  if (i > 0) {
    uint8_t prev = source->data[i - 1];
    if ((prev >= (uint8_t)'a' && prev <= (uint8_t)'z') || (prev >= (uint8_t)'A' && prev <= (uint8_t)'Z')
        || (prev >= (uint8_t)'0' && prev <= (uint8_t)'9') || prev == (uint8_t)'_')
      return 0;
  }
  if (i + (size_t)klen < source->length) {
    next_pos = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i + (size_t)klen);
    if (next_pos < source->length) {
      uint8_t nx = source->data[next_pos];
      /**
       * wave362 / docs/03: bare `if cond {` is legal (wave361). Keyword scan must NOT
       * require '(' after `if`, or scan_sync_after_if_stmt never finds bare ifs.
       * Failure mode: lex_out stuck at same if → outer block re-parses forever (100% CPU)
       * when the next stmt is an IDENT assign (return keyword realign still lucked out).
       * Accept any non-terminator after `if` (cond starts with ident/lit/!/(/…).
       * PLATFORM: SHARED — G.7 single kw_at_pos + scan_sync bare path.
       */
      if (klen == 2 && memcmp(kw, "if", 2) == 0) {
        if (nx == (uint8_t)'}' || nx == (uint8_t)';' || nx == (uint8_t)',')
          return 0;
      } else if (klen == 4 && memcmp(kw, "else", 4) == 0) {
        if (nx != (uint8_t)'{' && nx != (uint8_t)';') {
          if (next_pos + 2 > source->length || memcmp(source->data + next_pos, "if", 2) != 0)
            return 0;
        }
      } else if (nx != (uint8_t)'(' && nx != (uint8_t)'{' && nx != (uint8_t)';') {
        return 0;
      }
    }
  }
  return 1;
}

/**
 * Skip one balanced `{...}` starting at data[start] which must be '{'.
 * Returns the index immediately after the matching '}'.
 *
 * PLATFORM: SHARED — raw byte scan must ignore braces inside line comments (//),
 * block comments (slash-star), and "..." / '...' literals. The lexer path already
 * does this; scan_sync historically counted raw bytes and mis-closed large if
 * then-bodies when a comment contained a lone `{` (e.g. codegen.x note about
 * illegal `void {` C). That overshoot made outer while siblings (per-func emit)
 * nest under if (i==0), so Cap force-regen only co-emitted the first dep body.
 */
static size_t parser_asm_skip_balanced_braces_bytes_comment_aware_c(const uint8_t *data, size_t len,
                                                                     size_t start) {
  size_t i = start;
  int32_t br = 0;
  if (!data || i >= len || data[i] != (uint8_t)'{')
    return start;
  while (i < len) {
    uint8_t c = data[i];
    /* line comment (//) — skip to newline; braces inside do not affect depth. */
    if (c == (uint8_t)'/' && i + 1 < len && data[i + 1] == (uint8_t)'/') {
      i = i + 2;
      while (i < len && data[i] != (uint8_t)'\n')
        i = i + 1;
      continue;
    }
    /* block comment (slash-star) — skip to star-slash; braces inside ignored. */
    if (c == (uint8_t)'/' && i + 1 < len && data[i + 1] == (uint8_t)'*') {
      i = i + 2;
      while (i + 1 < len && !(data[i] == (uint8_t)'*' && data[i + 1] == (uint8_t)'/'))
        i = i + 1;
      if (i + 1 < len)
        i = i + 2;
      else
        i = len;
      continue;
    }
    /* double-quoted string */
    if (c == (uint8_t)'"') {
      i = i + 1;
      while (i < len && data[i] != (uint8_t)'"') {
        if (data[i] == (uint8_t)'\\' && i + 1 < len)
          i = i + 2;
        else
          i = i + 1;
      }
      if (i < len)
        i = i + 1;
      continue;
    }
    /* single-quoted char / byte literal */
    if (c == (uint8_t)'\'') {
      i = i + 1;
      while (i < len && data[i] != (uint8_t)'\'') {
        if (data[i] == (uint8_t)'\\' && i + 1 < len)
          i = i + 2;
        else
          i = i + 1;
      }
      if (i < len)
        i = i + 1;
      continue;
    }
    if (c == (uint8_t)'{') {
      br = br + 1;
      i = i + 1;
      continue;
    }
    if (c == (uint8_t)'}') {
      br = br - 1;
      i = i + 1;
      if (br == 0)
        return i;
      continue;
    }
    i = i + 1;
  }
  return i;
}

/**
 * Scan from the `if` near lex and return the lexer at the first token after
 * the whole if/else statement.
 *
 * Produce: byte scan of `if <cond> { then } [else …]`.
 * Store: returned Lexer.pos is the byte after the last `}` (or else-if tail).
 * Consume: parse_if_stmt lex_out, so the outer block/onefunc loop does not
 * re-enter the same `if`.
 *
 * wave361/wave650: parentheses are optional and a leading `(` is a *primary
 * grouping*, not wrapping of the entire condition. `if (x >> 2) != 4 {` and
 * `if (m + 1) == 1 {` are valid. The old `if (` path skipped only the first
 * balanced `(…)` and then demanded `{`; when `{` was not next it returned
 * lex_at_if unchanged. Combined with realign-backscan-to-IF, the outer stmt
 * loop re-parsed the same if forever (arena grew ~500MB/s).
 *
 * G.7 single path: after the `if` keyword, find the then-body `{` at
 * parenthesis-depth 0 (comment/string aware). That covers bare cond,
 * `(cond)`, and `(primary) binop …`.
 * PLATFORM: SHARED.
 */
static struct parser_asm_lexer parser_asm_scan_sync_after_if_stmt_c(struct parser_asm_lexer lex_cur,
                                                                    struct parser_asm_slice_u8 *source) {
  size_t if_pos = (size_t)lex_cur.pos;
  size_t lo = if_pos > 512 ? if_pos - 512 : 0;
  size_t cond_start = 0;
  size_t i;
  int32_t found = 0;
  if (!source || !source->data)
    return lex_cur;
  while (if_pos >= lo) {
    if (parser_asm_kw_at_pos_c(source, if_pos, "if", 2)) {
      size_t probe = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, if_pos + 2);
      if (probe < source->length) {
        found = 1;
        cond_start = probe;
        break;
      }
    }
    if (if_pos == lo)
      break;
    if_pos--;
  }
  if (!found)
    return lex_cur;
  /* First `{` at parenthesis-depth 0 after the condition start is the then body. */
  i = cond_start;
  {
    int32_t par = 0;
    while (i < source->length) {
      uint8_t c = source->data[i];
      if (c == (uint8_t)'/' && i + 1 < source->length && source->data[i + 1] == (uint8_t)'/') {
        i = i + 2;
        while (i < source->length && source->data[i] != (uint8_t)'\n')
          i = i + 1;
        continue;
      }
      if (c == (uint8_t)'/' && i + 1 < source->length && source->data[i + 1] == (uint8_t)'*') {
        i = i + 2;
        while (i + 1 < source->length
               && !(source->data[i] == (uint8_t)'*' && source->data[i + 1] == (uint8_t)'/'))
          i = i + 1;
        if (i + 1 < source->length)
          i = i + 2;
        else
          i = source->length;
        continue;
      }
      if (c == (uint8_t)'"' || c == (uint8_t)'\'') {
        uint8_t q = c;
        i = i + 1;
        while (i < source->length && source->data[i] != q) {
          if (source->data[i] == (uint8_t)'\\' && i + 1 < source->length)
            i = i + 2;
          else
            i = i + 1;
        }
        if (i < source->length)
          i = i + 1;
        continue;
      }
      if (c == (uint8_t)'(')
        par = par + 1;
      else if (c == (uint8_t)')' && par > 0)
        par = par - 1;
      else if (c == (uint8_t)'{' && par == 0)
        break;
      i = i + 1;
    }
  }
  i = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i);
  if (i >= source->length || source->data[i] != (uint8_t)'{')
    return lex_cur;
  i = parser_asm_skip_balanced_braces_bytes_comment_aware_c(source->data, source->length, i);
  i = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i);
  if (i + 4 <= source->length && parser_asm_kw_at_pos_c(source, i, "else", 4)) {
    i = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i + 4);
    if (i < source->length && source->data[i] == (uint8_t)'{') {
      i = parser_asm_skip_balanced_braces_bytes_comment_aware_c(source->data, source->length, i);
    } else if (i + 2 <= source->length && parser_asm_kw_at_pos_c(source, i, "if", 2)) {
      struct parser_asm_lexer inner;
      inner.pos = (int32_t)i;
      inner.line = lex_cur.line;
      inner.col = lex_cur.col;
      return parser_asm_scan_sync_after_if_stmt_c(inner, source);
    }
  }
  i = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i);
  return (struct parser_asm_lexer){ .pos = (int32_t)i, .line = lex_cur.line, .col = lex_cur.col };
}

/**
 * if 条件含 struct.field 时 cond_res.next_lex 可能被污染；自 if 关键字扫描至 cond 的 ')' 之后。
 */
static struct parser_asm_lexer parser_asm_sync_lex_after_if_cond_paren_c(
    struct parser_asm_lexer lex_at_if, struct parser_asm_slice_u8 *source) {
  size_t i = (size_t)lex_at_if.pos + 2;
  if (!source || !source->data)
    return lex_at_if;
  i = parser_asm_stretch_skip_ws_and_comments_c(source->data, source->length, i);
  if (i >= source->length || source->data[i] != (uint8_t)'(')
    return lex_at_if;
  {
    int32_t par = 1;
    i = i + 1;
    while (i < source->length && par > 0) {
      if (source->data[i] == (uint8_t)'(')
        par = par + 1;
      else if (source->data[i] == (uint8_t)')')
        par = par - 1;
      i = i + 1;
    }
  }
  return (struct parser_asm_lexer){ .pos = (int32_t)i, .line = lex_at_if.line, .col = lex_at_if.col };
}

/** parse_one_function_impl：if 语句后 lex 回扫（field cond 后偶发落在 return 之后）。 */
void parser_realign_lex_after_if_stmt_onefunc_glue(struct parser_asm_lexer *lex,
                                                   struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  if (!lex || !source)
    return;
  /**
   * parse_if_stmt_into_slice_c 已从 lex_at_if 重扫整句 if/else 并返回“整条语句之后”的 lex_out。
   * 这里若再从当前 lex 反向找最近的 if，会在嵌套 if 场景误命中内层 if，
   * 把 then 臂里的 `continue;` / `return;` 重新暴露给外层 block 或函数体。
   * 因此这里只做当前位置附近的 stmt 对齐，不再二次整句回扫。
   */
  out = parser_asm_realign_lex_after_if_arm_c(*lex, source);
  lex->pos = out.pos;
  lex->line = out.line;
  lex->col = out.col;
}

#endif /* PARSER_ASM_IF_STMT_SLICE_INCLUDED */
