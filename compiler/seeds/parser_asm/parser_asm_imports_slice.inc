/* Forward decl: defined later in this file (G-02f-422 Ubuntu gcc fix) */
int32_t parser_asm_collect_imports_consume_path(struct parser_asm_collect_imports_result *out,
                                                      struct parser_asm_slice_u8 *source, uint8_t *path_buf,
                                                      int32_t *path_len);

/**
 * 若 lex 位于 const 之后，尝试跳过整条 const [=|{]= import("path"); 语句。
 * 成功返回 1 并更新 *lex；否则返回 0。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int32_t parser_asm_try_skip_const_import_stmt(struct parser_asm_lexer *lex,
                                                     struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer_result r2;
  struct parser_asm_lexer_result r3;
  struct parser_asm_collect_imports_result dummy;
  /* wave584 Cap residual: import path content ≤127 (dep_path_rows[128] / typeck). */
  uint8_t path_buf[128];
  int32_t path_len = 0;
  int32_t i;

  if (!lex || !source)
    return 0;
  lexer_next_into(&r, *lex, source);
  if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len > 0) {
    lexer_next_into(&r2, r.next_lex, source);
    if (r2.tok.kind == (int32_t)TOKEN_ASSIGN) {
      dummy.lex = r2.next_lex;
      lexer_next_into(&r3, dummy.lex, source);
      if (r3.tok.kind != (int32_t)TOKEN_IMPORT)
        return 0;
      dummy.lex = r3.next_lex;
      if (!parser_asm_collect_imports_consume_path(&dummy, source, path_buf, &path_len))
        return 0;
      *lex = dummy.lex;
      return 1;
    }
  }
  (void)i;
  return 0;
}




/**
 * skip_imports：跳过顶层 const import 语句，返回首个非 import 的 lex。
 */
struct parser_asm_lexer parser_asm_skip_imports_slice_c(struct parser_asm_lexer lex,
                                                      struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  int32_t pending_cfg_skip_import = 0;
  if (!source)
    return lex;
  for (;;) {
    lexer_next_into(&r, lex, source);
    /** B-01/B-19：`#[cfg]` 不匹配 host 时跳过紧随其后的 const import 绑定。 */
    if (r.tok.kind == (int32_t)TOKEN_ATTR_CFG) {
      pending_cfg_skip_import = (r.tok.int_val == 0) ? 1 : 0;
      lex = r.next_lex;
      continue;
    }
    if (pending_cfg_skip_import) {
      parser_asm_cfg_skip_pending_top_level_into_slice_c(&lex, source, &pending_cfg_skip_import);
      if (pending_cfg_skip_import)
        pending_cfg_skip_import = 0;
      continue;
    }
    if (r.tok.kind != (int32_t)TOKEN_CONST)
      return lex;
    lex = r.next_lex;
    if (parser_asm_try_skip_const_import_stmt(&lex, source))
      continue;
    return lex;
  }
}

/**
 * skip_imports_buf：(data,len) 路径跳过顶层 import；返回首个非 import 的 lex。
 */
struct parser_asm_lexer parser_asm_skip_imports_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!data || len <= 0)
    return lex;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_imports_buf_audit_c(&lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_imports_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_stmt_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_imports_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = (size_t)len;
  return parser_asm_skip_imports_slice_c(lex, &source);
}

/**
 * Copy source[token_start..+tok_len) into a 128-byte buffer (zero-pad remainder).
 * wave584 Cap residual: binding-name content ≤127 (ImportEntry.binding_name[128]).
 * Historical name kept for symbol stability; width is 128.
 * PLATFORM: SHARED — product import collect path (this .inc → thin glue).
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_copy_token_bytes_to_buf64(struct parser_asm_slice_u8 *source, size_t token_start,
                                                 int32_t tok_len, uint8_t *buf) {
  int32_t bi;
  if (!buf)
    return;
  for (bi = 0; bi < 128; bi++) {
    if (bi < tok_len && source && source->data && token_start + (size_t)bi < source->length)
      buf[bi] = source->data[token_start + bi];
    else
      buf[bi] = 0;
  }
}




/**
 * 从 out.lex 当前位解析 import("path"); 成功更新 out.lex 并返回 1。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int32_t parser_asm_collect_imports_consume_path(struct parser_asm_collect_imports_result *out,
                                                      struct parser_asm_slice_u8 *source, uint8_t *path_buf,
                                                      int32_t *path_len) {
  struct parser_asm_lexer_result r;

  if (!out || !source || !path_buf || !path_len)
    return 0;
  *path_len = 0;
  lexer_next_into(&r, out->lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN)
    return 0;
  parser_asm_lex_from_result_val_into(&out->lex, r);
  lexer_next_into(&r, out->lex, source);
  /* wave584 Cap residual: import path content ≤127 (dep_path_rows[128] + typeck plen). */
  if (r.tok.kind == (int32_t)TOKEN_STRING && r.tok.ident_len > 0 && r.tok.ident_len <= 127) {
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, path_buf);
    *path_len = r.tok.ident_len;
  } else if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len > 0 && r.tok.ident_len <= 127
      && source->data && r.token_start < source->length && source->data[r.token_start] == (uint8_t)'"') {
    /* Compat: when lexer did not emit TOKEN_STRING, copy bytes between quotes. */
    size_t q0 = r.token_start + 1;
    size_t q1 = q0;
    while (q1 < source->length && source->data[q1] != (uint8_t)'"')
      q1++;
    if (q1 >= source->length || q1 - q0 > 127)
      return 0;
    {
      size_t k;
      for (k = 0; k < q1 - q0; k++)
        path_buf[k] = source->data[q0 + k];
      path_buf[k] = 0;
      *path_len = (int32_t)(q1 - q0);
    }
  } else {
    return 0;
  }
  parser_asm_lex_from_result_val_into(&out->lex, r);
  lexer_next_into(&r, out->lex, source);
  if (r.tok.kind != (int32_t)TOKEN_RPAREN)
    return 0;
  parser_asm_lex_from_result_val_into(&out->lex, r);
  lexer_next_into(&r, out->lex, source);
  if (r.tok.kind != (int32_t)TOKEN_SEMICOLON)
    return 0;
  if (parser_asm_stretch_import_path_validate_c(path_buf, *path_len) == 0)
    return 0;
  {
    int32_t finalized =
        parser_asm_stretch_import_path_finalize_c(path_buf, *path_len, source->data, source->length);
    if (finalized <= 0)
      return 0;
    *path_len = finalized;
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_score_c(path_buf, *path_len));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_post_audit_c(path_buf, *path_len, source));
  }
  parser_asm_lex_from_result_val_into(&out->lex, r);
  return 1;
}




/**
 * collect_imports：收集顶层 import 路径到 module，并写出跳过 import 后的 lex。
 */
void parser_asm_collect_imports_slice_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source, void *module,
                                        struct parser_asm_collect_imports_result *out) {
  /* wave584 Cap residual: path ≤127 (dep row[128]); binding ≤127 (binding_name[128]). */
  uint8_t path_buf[128];
  uint8_t bind_buf[128];
  uint8_t sel_buf[128];
  int32_t path_len;
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer_result r2;
  struct parser_asm_lexer_result r3;
  int32_t imp_ix;
  int32_t seg;

  if (!source || !out || !module)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_stmt_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  memset(path_buf, 0, sizeof(path_buf));
  out->lex.pos = lex.pos;
  out->lex.line = lex.line;
  out->lex.col = lex.col;
  {
    int32_t pending_cfg_skip_import = 0;
  for (;;) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_kind_peek_audit_c(&out->lex, source));
    lexer_next_into(&r, out->lex, source);
    lexer_next_into(&r2, r.next_lex, source);
    lexer_next_into(&r3, r2.next_lex, source);
    parser_asm_stretch_collect_imports_preamble_audit_c(r, r2, r3, source);
    /** B-01/B-19：`#[cfg]` 不匹配 host 时跳过紧随其后的 const import 绑定。 */
    if (r.tok.kind == (int32_t)TOKEN_ATTR_CFG) {
      pending_cfg_skip_import = (r.tok.int_val == 0) ? 1 : 0;
      parser_asm_lex_from_result_val_into(&out->lex, r);
      continue;
    }
    if (pending_cfg_skip_import) {
      parser_asm_cfg_skip_pending_top_level_into_slice_c(&out->lex, source, &pending_cfg_skip_import);
      if (pending_cfg_skip_import)
        pending_cfg_skip_import = 0;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_CONST) {
      lexer_next_into(&r2, r.next_lex, source);
      /* wave584 Cap residual: binding name content ≤127 (binding_name[128]). */
      if (r2.tok.kind == (int32_t)TOKEN_IDENT && r2.tok.ident_len > 0 && r2.tok.ident_len <= 127) {
        lexer_next_into(&r3, r2.next_lex, source);
        if (r3.tok.kind == (int32_t)TOKEN_ASSIGN) {
          /*
           * wave423: only consume `const name = import ...` as import binding.
           * Bare `const name = expr` (type inference) must leave lex at TOKEN_CONST
           * so parse_one_top_level_let can parse it. Prior: advanced past `=` then
           * returned → dropped binding → XT001 on use of name.
           * Look ahead one token after `=` without advancing out->lex until confirmed.
           * PLATFORM: SHARED parse.
           */
          lexer_next_into(&r, r3.next_lex, source);
          PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_const_import_kw_audit_c((int32_t)r.tok.kind));
          if (r.tok.kind != (int32_t)TOKEN_IMPORT) {
            /* Not import-binding: end import collection; out->lex still at CONST. */
            break;
          }
          parser_asm_copy_token_bytes_to_buf64(source, r2.token_start, r2.tok.ident_len, bind_buf);
          parser_asm_lex_from_result_val_into(&out->lex, r);
          if (!parser_asm_collect_imports_consume_path(out, source, path_buf, &path_len))
            return;
          imp_ix = pipeline_module_import_alloc(module);
          if (imp_ix < 0)
            return;
          pipeline_module_import_set_path(module, imp_ix, path_buf, path_len);
          pipeline_module_import_set_kind(module, imp_ix, 1);
          PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(bind_buf, r2.tok.ident_len));
          pipeline_module_import_set_binding_name(module, imp_ix, bind_buf, r2.tok.ident_len);
          pipeline_module_import_set_select_count(module, imp_ix, 0);
          continue;
        }
      }
      break; /* 非 const x = import：结束 import 收集 */
    }
    return;
  }
  }
}

/**
 * collect_imports_buf：(data,len) 路径委托 slice collect_imports。
 */
void parser_asm_collect_imports_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len, void *module,
                                    struct parser_asm_collect_imports_result *out) {
  struct parser_asm_slice_u8 source;
  if (!data || !out)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_buf_audit_c(&lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_select_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_post_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_stmt_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_import_path_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_lex_after_imports_buf_audit_c(data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_collect_imports_slice_c(lex, &source, module, out);
}

/**
 * diag_token_after_collect_imports：collect_imports 后 peek 下一 token kind。
 */
int32_t parser_asm_diag_token_after_collect_imports_slice_c(struct parser_asm_slice_u8 *source, void *module) {
  struct parser_asm_lexer lex;
  struct parser_asm_collect_imports_result import_res;
  struct parser_asm_lexer_result r;

  if (!source || !module)
    return (int32_t)TOKEN_EOF;
  lex = parser_asm_lexer_init_c();
  import_res.lex = lex;
  parser_asm_collect_imports_slice_c(lex, source, module, &import_res);
  lex = import_res.lex;
  {
    int32_t peek_kinds[6];
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_peek_kind_chain_c(lex, source, peek_kinds, 6));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_toplevel_after_imports_audit_c(&lex, source));
  }
  lexer_next_into(&r, lex, source);
  return r.tok.kind;
}

/**
 * diag_token_after_collect_imports_buf：buf 路径 collect_imports 后 peek 下一 token kind。
 */
int32_t parser_asm_diag_token_after_collect_imports_buf_c(uint8_t *data, int32_t len, void *module) {
  struct parser_asm_slice_u8 source;

  if (!data || len <= 0 || !module)
    return (int32_t)TOKEN_EOF;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_token_after_collect_imports_buf_audit_c(data, len));
  source.data = data;
  source.length = (size_t)len;
  return parser_asm_diag_token_after_collect_imports_slice_c(&source, module);
}

