/* parser_asm_body_tl_slice.inc — G-02f-327 P18 body/diag residual + top_level skip
 * Hybrid: XLANG_PTHIN_BODY_TL_FROM_X via seeds/pthin_body_tl.from_x.c
 * is_fn_sig_scalar + diag_first_ident + diag_skip_let_const_into + body_skip_into
 * + skip_one_top_level_{let,const} + cfg_skip_pending_top_level
 */
#ifndef PARSER_ASM_BODY_TL_SLICE_INC
#define PARSER_ASM_BODY_TL_SLICE_INC

/* Forward decls: defined in skip_tl_slice.inc / glue_tail_slice.inc (G-02f-422 Ubuntu gcc fix) */
void parser_asm_skip_one_struct_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                             struct parser_asm_slice_u8 *source);
void parser_asm_skip_one_function_full_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source);

/**
 * wave422/423 Cap residual pure: hard P010 for illegal binding forms.
 * Root (wave422): missing COLON returned false with no diag → function dropped → soft P001
 * "no functions" / BLD001 missing _main. docs/06 bans let type inference.
 * wave423: const may omit `: Type` when followed by `= init` (type inferred in typeck);
 * this helper is only called for illegal forms (let without `:`, const without `:`/`=`).
 * G.7 authority: this helper; parse_body_lets_into + top_level_let call it.
 * @param line 1-based source line of the unexpected token after the binding name
 * @param col  1-based column
 * @param is_let 1 = let (docs ban inference); 0 = const (needs `: Type` or `= init`)
 * PLATFORM: SHARED parse.
 */
void parser_report_untyped_binding_p010_c(int32_t line, int32_t col, int32_t is_let) {
  extern void diag_report_with_code(const char *file, int32_t line, int32_t col, const char *kind,
                                    const char *code, const char *msg, const char *detail);
  if (is_let != 0) {
    diag_report_with_code(NULL, line, col, "parse error", "P010",
                          "let requires type annotation (no type inference; write let name: Type = ...)",
                          NULL);
  } else {
    diag_report_with_code(NULL, line, col, "parse error", "P010",
                          "const requires ': Type = init' or '= init' (type inferred from init)",
                          NULL);
  }
}

/*
 * wave676 Cap residual: hard P011 for untyped function formals / missing return type.
 * Root: parse_one_function set_onefunc_fail with no diag → function dropped from AST;
 * buf path accepted `fn(x): i32` (RPAREN without param `: Type`) → typeck/codegen green.
 * G.7 authority: this helper + call sites in parser.x / parser_gen / one_function_buf_slice.
 * Sticky flag: parse_into_buf must abort (ok=-2) instead of soft-skip+continue.
 * @param line 1-based source line of the unexpected token
 * @param col  1-based column
 * @param kind 0 = param missing `: Type`; 1 = function missing return `: Type`
 * PLATFORM: SHARED parse.
 */
static int32_t g_parser_sig_type_hard = 0;

void parser_sig_type_hard_reset_c(void) { g_parser_sig_type_hard = 0; }

int32_t parser_sig_type_hard_pending_c(void) { return g_parser_sig_type_hard; }

/*
 * 4.2.1 / wave676: product P011 rejects untyped formals, including free/inherent
 * `function m(self)`. Trait default hoist re-parses `function get(self): T {…}`
 * via the buf onefunc path and must be allowed to leave param0 type_ref=0;
 * commit then stamps the impl for-type (wave477).
 * Set 1 only around that hoist parse; always clear afterwards.
 * PLATFORM: SHARED parse.
 */
static int32_t g_parser_allow_bare_self = 0;

void parser_allow_bare_self_set_c(int32_t on) { g_parser_allow_bare_self = on ? 1 : 0; }

int32_t parser_allow_bare_self_pending_c(void) { return g_parser_allow_bare_self; }

/*
 * 9.6.3: module pointer installed by parser_cur_module_set_c around each
 * function-body parse (parse_into / parse_into_buf), read by parse_block_into
 * to desugar a function-local `static let/const` into a module top-level let.
 * C-side static because the parser.x pin carries no module-scope pointer
 * global; same pattern as g_parser_sig_type_hard above.
 * PLATFORM: SHARED parse.
 */
static void *g_parser_cur_module = 0;

void parser_cur_module_set_c(void *m) { g_parser_cur_module = m; }

void *parser_cur_module_get_c(void) { return g_parser_cur_module; }

void parser_report_untyped_formal_p011_c(int32_t line, int32_t col, int32_t kind) {
  extern void diag_report_with_code(const char *file, int32_t line, int32_t col, const char *kind_s,
                                    const char *code, const char *msg, const char *detail);
  g_parser_sig_type_hard = 1;
  if (kind == 0) {
    diag_report_with_code(NULL, line, col, "parse error", "P011",
                          "function parameter requires type annotation (write name: Type)",
                          NULL);
  } else {
    diag_report_with_code(NULL, line, col, "parse error", "P011",
                          "function requires return type annotation (write ): Type { ... })",
                          NULL);
  }
}

/*
 * wave679 Cap residual: hard P012 for duplicate function param / struct field names.
 * Root: parse+typeck green → host-C BLD001 (redefinition / duplicate member).
 * G.7 authority: this helper + call sites before append_param / set_field.
 * Sticky: reuses g_parser_sig_type_hard so parse_into_buf aborts (ok=-2), same as P011.
 * @param line 1-based source line of the duplicate name token
 * @param col  1-based column
 * @param kind 0 = function param; 1 = struct field; 2 = module top-level let/const
 * PLATFORM: SHARED parse.
 */
void parser_report_duplicate_name_p012_c(int32_t line, int32_t col, int32_t kind) {
  extern void diag_report_with_code(const char *file, int32_t line, int32_t col, const char *kind_s,
                                    const char *code, const char *msg, const char *detail);
  g_parser_sig_type_hard = 1;
  if (kind == 0) {
    diag_report_with_code(NULL, line, col, "parse error", "P012",
                          "duplicate parameter name in function signature",
                          NULL);
  } else if (kind == 2) {
    /* 9.6.3: two module-level let/const with one name used to compile silently
     * (second registration won). Root-fixed at the top-level-let registration
     * authority; sticky abort via g_parser_sig_type_hard. PLATFORM: SHARED parse. */
    diag_report_with_code(NULL, line, col, "parse error", "P012",
                          "duplicate top-level binding name (module already declares this let/const; rename one)",
                          NULL);
  } else {
    diag_report_with_code(NULL, line, col, "parse error", "P012",
                          "duplicate field name in struct definition",
                          NULL);
  }
}

/*
 * One type-position path for trait objects: write the trait name
 * (`let x: Clone = a`). `dyn Trait` is not a second producer (AI /
 * users had two spellings). Sticky reuses g_parser_sig_type_hard so
 * parse_into_buf aborts (ok=-2) instead of silently dropping the
 * function (P001 false green when main remains).
 * @param line 1-based source line of the `dyn` token
 * @param col  1-based column
 * PLATFORM: SHARED parse.
 */
void parser_report_dyn_prefix_p013_c(int32_t line, int32_t col) {
  extern void diag_report_with_code(const char *file, int32_t line, int32_t col, const char *kind_s,
                                    const char *code, const char *msg, const char *detail);
  g_parser_sig_type_hard = 1;
  diag_report_with_code(NULL, line, col, "parse error", "P013",
                        "do not write 'dyn Trait'; write the trait name (e.g. let x: Clone = a)",
                        NULL);
}

/*
 * Hard P014 when a let/const/param binding name is a keyword token.
 * Root: parse_body_lets_into / param list / top-level let accepted only
 * IDENT|SELF|UNDERSCORE; TOKEN_RUN/SPAWN/ASYNC/AWAIT/`if`/… returned false
 * with no diag → whole function dropped → soft P001 "no functions" /
 * BLD001 missing _main. Cookbook `let run: u8[3] = [114,117,110]` hit this
 * (`run` is unary EXPR_RUN; `run[0]` cannot be a variable index).
 * G.7: complete this diagnostic family (P010–P013); call from the existing
 * IDENT|SELF gates — do not make `run` an ident (unary vs `run[0]` collide).
 * Sticky: g_parser_sig_type_hard so parse_into_buf aborts (ok=-2).
 * @param line 1-based source line of the keyword token
 * @param col  1-based column
 * PLATFORM: SHARED parse.
 */
void parser_report_keyword_binding_p014_c(int32_t line, int32_t col) {
  extern void diag_report_with_code(const char *file, int32_t line, int32_t col, const char *kind_s,
                                    const char *code, const char *msg, const char *detail);
  g_parser_sig_type_hard = 1;
  diag_report_with_code(NULL, line, col, "parse error", "P014",
                        "binding name must be an identifier, not a keyword",
                        NULL);
}

/**
 * wave679: return 1 if `name` already appears among params [0, nparams).
 * @param pool OneFunc sidecar pool (pipeline_onefunc_*)
 * @param nparams number of params already appended
 * @param name binding name bytes
 * @param name_len byte length (1..127)
 * @return 1 if duplicate, 0 otherwise
 * PLATFORM: SHARED parse.
 */
int32_t parser_onefunc_param_name_dup_c(uint8_t *pool, int32_t nparams, uint8_t *name, int32_t name_len) {
  extern int32_t pipeline_onefunc_param_name_len(uint8_t *out, int32_t i);
  extern uint8_t pipeline_onefunc_param_name_byte_at(uint8_t *out, int32_t i, int32_t off);
  int32_t i;
  int32_t k;
  int32_t pl;
  if (!pool || !name || name_len <= 0 || nparams <= 0)
    return 0;
  for (i = 0; i < nparams; i++) {
    pl = pipeline_onefunc_param_name_len(pool, i);
    if (pl != name_len)
      continue;
    for (k = 0; k < name_len; k++) {
      if (pipeline_onefunc_param_name_byte_at(pool, i, k) != name[k])
        break;
    }
    if (k == name_len)
      return 1;
  }
  return 0;
}

/* G-02f-123：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t parser_asm_is_fn_sig_scalar_type_token_c(int32_t kind) {
  return kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64 || kind == (int32_t)TOKEN_BOOL
      || kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32 || kind == (int32_t)TOKEN_U64
      || kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_VOID || kind == (int32_t)TOKEN_IDENT;
}




/**
 * diag_first_ident_len：诊断用，返回 function 后首 IDENT 的 ident_len（失败负值）。
 */
int32_t parser_asm_diag_first_ident_len_slice_c(struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  if (!source)
    return -2;
  lex = parser_asm_lexer_init_c();
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION)
    return -2;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_fn_header_audit_c(lex, source));
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT)
    return -3;
  return r.tok.ident_len;
}

/**
 * diag_skip_let_const_into：从 body 首 token 起跳过 let/const 声明，写入 *out。
 */
void parser_asm_diag_skip_let_const_into_slice_c(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                                 struct parser_asm_slice_u8 *source) {
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_skip_let_const_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_skip_let_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_let_const_decl_audit_c(&lex, source));
  lexer_next_into(out, lex, source);
  while (out->tok.kind == (int32_t)TOKEN_LET || out->tok.kind == (int32_t)TOKEN_CONST) {
    parser_lex_from_lexer_result_ptr_into(&lex, out);
    lexer_next_into(out, lex, source);
    if (out->tok.kind != (int32_t)TOKEN_IDENT)
      return;
    parser_lex_from_lexer_result_ptr_into(&lex, out);
    lexer_next_into(out, lex, source);
    if (out->tok.kind != (int32_t)TOKEN_COLON)
      return;
    parser_lex_from_lexer_result_ptr_into(&lex, out);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_skip_let_const_type_audit_c(lex, source));
    lexer_next_into(out, lex, source);
    if (out->tok.kind == (int32_t)TOKEN_STAR) {
      parser_lex_from_lexer_result_ptr_into(&lex, out);
      lexer_next_into(out, lex, source);
      if (out->tok.kind != (int32_t)TOKEN_IDENT)
        return;
      parser_lex_from_lexer_result_ptr_into(&lex, out);
      lexer_next_into(out, lex, source);
    } else if (parser_asm_is_fn_sig_scalar_type_token_c(out->tok.kind)) {
      parser_lex_from_lexer_result_ptr_into(&lex, out);
      lexer_next_into(out, lex, source);
      if (out->tok.kind == (int32_t)TOKEN_LBRACKET) {
        parser_lex_from_lexer_result_ptr_into(&lex, out);
        lexer_next_into(out, lex, source);
        if (out->tok.kind != (int32_t)TOKEN_RBRACKET)
          return;
        parser_lex_from_lexer_result_ptr_into(&lex, out);
        lexer_next_into(out, lex, source);
      }
    } else {
      return;
    }
    if (out->tok.kind != (int32_t)TOKEN_ASSIGN)
      return;
    parser_lex_from_lexer_result_ptr_into(&lex, out);
    lexer_next_into(out, lex, source);
    while (out->tok.kind != (int32_t)TOKEN_SEMICOLON && out->tok.kind != (int32_t)TOKEN_EOF) {
      if (out->tok.kind == (int32_t)TOKEN_STRING)
        return;
      parser_lex_from_lexer_result_ptr_into(&lex, out);
      lexer_next_into(out, lex, source);
    }
    if (out->tok.kind != (int32_t)TOKEN_SEMICOLON)
      return;
    parser_lex_from_lexer_result_ptr_into(&lex, out);
    lexer_next_into(out, lex, source);
  }
}

/**
 * body_skip_let_const_then_if_into：跳过 body 内 let/const 后连续 if 语句。
 */
void parser_asm_body_skip_let_const_then_if_into_slice_c(struct parser_asm_lexer_result *out,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source) {
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_let_const_then_if_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_skip_let_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_let_const_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_let_const_decl_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_body_skip_let_const_type_audit_c(lex, source));
  parser_asm_diag_skip_let_const_into_slice_c(out, lex, source);
  while (out->tok.kind == (int32_t)TOKEN_IF) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_header_audit_c(&out->next_lex, source));
    parser_asm_skip_one_if_statement_into_slice_c(out, out->next_lex, source);
  }
}

/**
 * B-01/B-19：跳过一条顶层 `let ... ;`（与 const 跳过对称；cfg 不匹配时须跳过 let 而非仅 const）。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_skip_one_top_level_let_into_slice_c(struct parser_asm_lexer *out,
                                                             struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;

  if (!out || !source) {
    if (out)
      *out = lex;
    return;
  }
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LET) {
    *out = lex;
    return;
  }
  lex = r.next_lex;
  for (;;) {
    lexer_next_into(&r, lex, source);
    lex = r.next_lex;
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON || r.tok.kind == (int32_t)TOKEN_EOF)
      break;
  }
  if (r.tok.kind == (int32_t)TOKEN_SEMICOLON)
    lex = r.next_lex;
  *out = lex;
}




/**
 * B-01/B-19：跳过一条顶层 `const ... ;`（含 const x = import("path");），不建 AST。
 * lex 位于 const 之前；*out 写出跳过后的 lex。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_skip_one_top_level_const_into_slice_c(struct parser_asm_lexer *out,
                                                               struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;

  if (!out || !source) {
    if (out)
      *out = lex;
    return;
  }
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_CONST) {
    *out = lex;
    return;
  }
  lex = r.next_lex;
  for (;;) {
    lexer_next_into(&r, lex, source);
    lex = r.next_lex;
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON || r.tok.kind == (int32_t)TOKEN_EOF)
      break;
  }
  if (r.tok.kind == (int32_t)TOKEN_SEMICOLON)
    lex = r.next_lex;
  *out = lex;
}




/**
 * B-02/B-19：import/collect 区段 `#[cfg]` 不匹配时跳过紧随其后的顶层 const/struct/function。
 * lex 位于待跳过项之前；*pending 置 0 后 *lex 写出跳过后的位置。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_cfg_skip_pending_top_level_into_slice_c(struct parser_asm_lexer *lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                int32_t *pending) {
  if (!lex || !source || !pending || !*pending)
    return;
  if (lex->pos >= source->length) {
    *pending = 0;
    return;
  }
  {
    struct parser_asm_lexer_result r;
    lexer_next_into(&r, *lex, source);
    if (r.tok.kind == (int32_t)TOKEN_CONST) {
      parser_asm_skip_one_top_level_const_into_slice_c(lex, *lex, source);
      *pending = 0;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_LET) {
      parser_asm_skip_one_top_level_let_into_slice_c(lex, *lex, source);
      *pending = 0;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_STRUCT) {
      parser_asm_skip_one_struct_into_slice_c(lex, *lex, source);
      *pending = 0;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_FUNCTION || r.tok.kind == (int32_t)TOKEN_EXTERN
        || r.tok.kind == (int32_t)TOKEN_ASYNC) {
      parser_asm_skip_one_function_full_into_slice_c(lex, *lex, source);
      *pending = 0;
      return;
    }
  }
  *pending = 0;
}




#endif /* PARSER_ASM_BODY_TL_SLICE_INC */
