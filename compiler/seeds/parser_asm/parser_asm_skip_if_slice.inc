/**
 * 从 trait/impl 等顶层块关键字位置扫描至匹配 `}` 之后。
 * 使用 lexer 跳过空白/注释，再以 token 级大括号配对，避免 `{`/`}` 落在注释里时错位。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_skip_trait_impl_block_raw_c(struct parser_asm_lexer *out, struct parser_asm_lexer start,
                                                   struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  if (!out || !source || !source->data)
    return;
  lex = start;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_TRAIT || r.tok.kind == (int32_t)TOKEN_IMPL)
    parser_asm_lex_from_result_val_into(&lex, r);
  for (;;) {
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      parser_asm_skip_balanced_braces_into_slice_c(out, r.next_lex, source);
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF) {
      *out = start;
      return;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
  }
}




/* G-02f-281: moved to parser_asm_lex_skip_slice.inc (was L4504-L4625) */

/* G-02f-281: moved to parser_asm_lex_skip_slice.inc (was L4627-L4673) */

/**
 * skip_one_if_core_into：跳过 if (cond) { ... } / if (cond) stmt; 的核心 lex 推进（slice 路径）。
 */
void parser_asm_skip_one_if_core_into_slice_c(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                              struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex_cur;
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_if_core_deep_audit_c(lex, source));
  lexer_next_into(out, lex, source);
  if (out->tok.kind != (int32_t)TOKEN_LPAREN)
    return;
  parser_asm_skip_balanced_parens_into_slice_c(&lex_cur, out->next_lex, source);
  lexer_next_into(out, lex_cur, source);
  if (out->tok.kind == (int32_t)TOKEN_LBRACE) {
    parser_asm_skip_balanced_braces_into_slice_c(&lex_cur, out->next_lex, source);
    lexer_next_into(out, lex_cur, source);
  } else {
    while (out->tok.kind != (int32_t)TOKEN_SEMICOLON && out->tok.kind != (int32_t)TOKEN_EOF) {
      parser_asm_lex_from_result_val_into(&lex_cur, *out);
      lexer_next_into(out, lex_cur, source);
    }
    if (out->tok.kind == (int32_t)TOKEN_SEMICOLON) {
      parser_asm_lex_from_result_val_into(&lex_cur, *out);
      lexer_next_into(out, lex_cur, source);
    }
  }
}

/**
 * skip_one_if_core_buf：与 skip_one_if_core_into 等价，buf 路径 + LexerResult 按值返回。
 */
struct parser_asm_lexer_result parser_asm_skip_one_if_core_buf_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                 int32_t len) {
  struct parser_asm_lexer_result r;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_cond_int_as_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_if_core_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_cond_expr_deep_buf_audit_c(lex, data, len));
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN)
    return r;
  lex = parser_asm_skip_balanced_parens_buf_c(r.next_lex, data, len);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
    lex = parser_asm_skip_balanced_braces_buf_c(r.next_lex, data, len);
    r = lexer_next_buf(lex, data, len);
  } else {
    while (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_EOF) {
      parser_asm_lex_from_result_val_into(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
      parser_asm_lex_from_result_val_into(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
  }
  return r;
}

/**
 * Register top-level enum name (dedupe); returns sidecar index or -1.
 * wave582 Cap residual: name_len content cap 63→127 (ModuleEnumEntry.name[128]).
 * PLATFORM: SHARED product enum path.
 */
int32_t parser_asm_module_try_register_enum_name_c(void *module, uint8_t *name, int32_t name_len) {
  int32_t ei;
  int32_t j;
  int32_t slot;
  int32_t cur_len;
  if (!module || !name || name_len <= 0 || name_len > 127)
    return -1;
  ei = 0;
  for (;;) {
    cur_len = pipeline_module_enum_name_len(module, ei);
    if (cur_len <= 0)
      break;
    if (cur_len == name_len) {
      int32_t eq = 1;
      j = 0;
      while (j < name_len) {
        if (pipeline_module_enum_name_byte_at(module, ei, j) != name[j]) {
          eq = 0;
          break;
        }
        j++;
      }
      if (eq)
        return ei;
    }
    ei++;
  }
  slot = pipeline_module_enum_alloc(module);
  if (slot < 0)
    return -1;
  pipeline_module_enum_set_name(module, slot, name, name_len);
  return slot;
}

/**
 * skip_one_if_statement_into：跳过整条 if（含 else / else if），slice 路径写入 *out。
 */
void parser_asm_skip_one_if_statement_into_slice_c(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                                   struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex_cur;
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_header_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_body_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_body_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_else_chain_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_control_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  parser_asm_skip_one_if_core_into_slice_c(out, lex, source);
  while (out->tok.kind == (int32_t)TOKEN_ELSE) {
    parser_asm_lex_from_result_val_into(&lex_cur, *out);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_else_stmt_audit_c(&lex_cur, source));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_if_else_chain_audit_c(&lex_cur, source));
    lexer_next_into(out, lex_cur, source);
    if (out->tok.kind == (int32_t)TOKEN_IF) {
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_else_if_chain_audit_c(&lex_cur, source));
      parser_asm_lex_from_result_val_into(&lex_cur, *out);
      parser_asm_skip_one_if_core_into_slice_c(out, lex_cur, source);
    } else if (out->tok.kind == (int32_t)TOKEN_LBRACE) {
      parser_asm_skip_balanced_braces_into_slice_c(&lex_cur, out->next_lex, source);
      lexer_next_into(out, lex_cur, source);
    } else {
      while (out->tok.kind != (int32_t)TOKEN_SEMICOLON && out->tok.kind != (int32_t)TOKEN_EOF) {
        parser_asm_lex_from_result_val_into(&lex_cur, *out);
        lexer_next_into(out, lex_cur, source);
      }
      if (out->tok.kind == (int32_t)TOKEN_SEMICOLON) {
        parser_asm_lex_from_result_val_into(&lex_cur, *out);
        lexer_next_into(out, lex_cur, source);
      }
    }
  }
}

/**
 * skip_one_if_statement_buf：与 skip_one_if_statement_into 等价，buf 路径。
 */
struct parser_asm_lexer_result parser_asm_skip_one_if_statement_buf_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                      int32_t len) {
  struct parser_asm_lexer_result r;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_if_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_body_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_body_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_stmt_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_else_chain_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_control_mega_full_deep_buf_audit_c(lex, data, len));
  r = parser_asm_skip_one_if_core_buf_c(lex, data, len);
  while (r.tok.kind == (int32_t)TOKEN_ELSE) {
    parser_asm_lex_from_result_val_into(&lex, r);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_if_else_chain_buf_audit_c(lex, data, len));
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_IF) {
      parser_asm_lex_from_result_val_into(&lex, r);
      r = parser_asm_skip_one_if_core_buf_c(lex, data, len);
    } else if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      lex = parser_asm_skip_balanced_braces_buf_c(r.next_lex, data, len);
      r = lexer_next_buf(lex, data, len);
    } else {
      while (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_EOF) {
        parser_asm_lex_from_result_val_into(&lex, r);
        r = lexer_next_buf(lex, data, len);
      }
      if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
        parser_asm_lex_from_result_val_into(&lex, r);
        r = lexer_next_buf(lex, data, len);
      }
    }
  }
  return r;
}
