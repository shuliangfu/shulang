/**
 * diag_first_ident_len_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_diag_first_ident_len_glue(struct parser_asm_slice_u8 *source) {
  return parser_asm_diag_first_ident_len_slice_c(source);
}

/**
 * diag_skip_let_const_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_diag_skip_let_const_into_glue(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                          struct parser_asm_slice_u8 *source) {
  parser_asm_diag_skip_let_const_into_slice_c(out, lex, source);
}

/**
 * diag_skip_let_const_glue：兼容包装 slice 路径；LexerResult 按值返回勿 X emit。
 */
struct parser_asm_lexer_result parser_diag_skip_let_const_glue(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  parser_asm_diag_skip_let_const_into_slice_c(&r, lex, source);
  return r;
}

/**
 * skip_one_if_core_glue：兼容包装 slice 路径；LexerResult 按值返回勿 X emit。
 */
struct parser_asm_lexer_result parser_skip_one_if_core_glue(struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  parser_asm_skip_one_if_core_into_slice_c(&r, lex, source);
  return r;
}

/**
 * skip_one_if_statement_glue：兼容包装 slice 路径；LexerResult 按值返回勿 X emit。
 */
struct parser_asm_lexer_result parser_skip_one_if_statement_glue(struct parser_asm_lexer lex,
                                                                    struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  parser_asm_skip_one_if_statement_into_slice_c(&r, lex, source);
  return r;
}

/**
 * body_skip_let_const_then_if_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_body_skip_let_const_then_if_into_glue(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                                  struct parser_asm_slice_u8 *source) {
  parser_asm_body_skip_let_const_then_if_into_slice_c(out, lex, source);
}

/**
 * diag_first_ident_len：strict 链 thin delegate；weak 避免与 parser_x.o 真 emit 符号冲突。
 */
__attribute__((weak)) int32_t parser_diag_first_ident_len(struct parser_asm_slice_u8 *source) {
  return parser_asm_diag_first_ident_len_slice_c(source);
}

/**
 * diag_skip_let_const_into：strict 链 thin delegate；weak 避免与 parser_x.o 真 emit 符号冲突。
 */
__attribute__((weak)) void parser_diag_skip_let_const_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                     struct parser_asm_slice_u8 *source) {
  parser_asm_diag_skip_let_const_into_slice_c(out, lex, source);
}

/**
 * body_skip_let_const_then_if_into：strict 链 thin delegate；weak 避免与 parser_x.o 真 emit 符号冲突。
 */
__attribute__((weak)) void parser_body_skip_let_const_then_if_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                             struct parser_asm_slice_u8 *source) {
  parser_asm_body_skip_let_const_then_if_into_slice_c(out, lex, source);
}

/**
 * first_token_kind_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_first_token_kind_glue(struct parser_asm_slice_u8 *source) {
  return parser_asm_first_token_kind_slice_c(source);
}

/** first_token_kind_buf_glue：buf 路径诊断首 token kind。 */
int32_t parser_first_token_kind_buf_glue(uint8_t *data, int32_t len) {
  return parser_asm_first_token_kind_buf_c(data, len);
}

/**
 * first_token_kind：strict 链 thin delegate；weak 避免与 parser_x.o 真 emit 符号冲突。
 */
__attribute__((weak)) int32_t parser_first_token_kind(struct parser_asm_slice_u8 *source) {
  return parser_asm_first_token_kind_slice_c(source);
}

/**
 * advance_past_stmt_semicolon_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_advance_past_stmt_semicolon_into_glue(struct parser_asm_lexer_result *r_out,
                                                     struct parser_asm_lexer lex,
                                                     struct parser_asm_slice_u8 *source) {
  return parser_asm_advance_past_stmt_semicolon_into_slice_c(r_out, lex, source);
}

/**
 * advance_past_cond_rparen_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_advance_past_cond_rparen_into_glue(struct parser_asm_lexer_result *r_out,
                                                  struct parser_asm_lexer lex,
                                                  struct parser_asm_slice_u8 *source) {
  return parser_asm_advance_past_cond_rparen_into_slice_c(r_out, lex, source);
}

/**
 * skip_one_if_core_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_if_core_into_glue(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                       struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_if_core_into_slice_c(out, lex, source);
}

/**
 * struct_field_name_tok_kind_i32_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_struct_field_name_tok_kind_i32_glue(int32_t k) {
  return parser_asm_struct_field_name_tok_kind_c(k);
}

/**
 * struct_field_continues_tok_kind_i32_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_struct_field_continues_tok_kind_i32_glue(int32_t k) {
  return parser_asm_struct_field_continues_tok_kind_c(k);
}

/**
 * struct_field_name_from_tok_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_struct_field_name_from_tok_glue(struct parser_asm_lexer_result r,
                                               struct parser_asm_slice_u8 *source, uint8_t *out) {
  return parser_asm_struct_field_name_from_tok_slice_c(r, source, out);
}

/**
 * skip_one_if_statement_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_if_statement_into_glue(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                                           struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_if_statement_into_slice_c(out, lex, source);
}

/**
 * skip_one_if_core_buf_glue：extern bl 白名单 / thin delegate buf 路径 C 实现。
 */
struct parser_asm_lexer_result parser_skip_one_if_core_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                                int32_t len) {
  return parser_asm_skip_one_if_core_buf_c(lex, data, len);
}

/**
 * skip_one_if_statement_buf_glue：extern bl 白名单 / thin delegate buf 路径 C 实现。
 */
struct parser_asm_lexer_result parser_skip_one_if_statement_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                                     int32_t len) {
  return parser_asm_skip_one_if_statement_buf_c(lex, data, len);
}

/**
 * module_try_register_enum_name_glue：extern bl 白名单 / thin delegate C 实现。
 */
int32_t parser_module_try_register_enum_name_glue(void *module, uint8_t *name, int32_t name_len) {
  return parser_asm_module_try_register_enum_name_c(module, name, name_len);
}

/**
 * skip_one_struct_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_struct_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                      struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_struct_into_slice_c(out, lex, source);
}

/**
 * skip_one_enum_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_enum_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                   struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_enum_into_slice_c(out, lex, source);
}

/**
 * skip_one_trait_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_trait_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                     struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_trait_into_slice_c(out, lex, source);
}

/**
 * skip_one_impl_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_impl_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                    struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_impl_into_slice_c(out, lex, source);
}

/**
 * skip_one_extern_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_extern_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                      struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_extern_into_slice_c(out, lex, source);
}

/**
 * skip_one_function_full_into：跳过整条 function 定义（签名+体），结果写入 *out。
 */
void parser_asm_skip_one_function_full_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex_cur;
  const char *dbg_skip;
  if (!out || !source)
    return;
  dbg_skip = getenv("XLANG_DEBUG_SKIP_FUNC");
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_header_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_prefix_audit_c(&lex, source));
  /**
   * 读 lex 处首 token 再判 TOKEN_FUNCTION；stretch 扩段曾挤掉此 lexer_next_into，
   * 导致 r 未初始化即早退，#[cfg] pending_cfg_skip 路径无法跳过 function。
   */
  memset(&r, 0, sizeof(r));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_ASYNC) {
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
  }
  /** #[cfg] 剪枝顶层 extern：parse_into 与 cfg_skip 均走 skip_one_function_full_into，须委托 skip_one_extern。 */
  if (r.tok.kind == (int32_t)TOKEN_EXTERN) {
    parser_asm_skip_one_extern_into_slice_c(out, lex, source);
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sig_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_sig_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sig_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_control_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sig_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  /*
   * PLATFORM: SHARED — skip-function anchor must accept three entry shapes:
   *   (1) at `function` keyword (normal);
   *   (2) already past keyword at IDENT name (host parse residual: lex_at_function.pos
   *       after TOKEN_FUNCTION was consumed — observed for mega parse_into / parse_into_buf);
   *   (3) at `export` before function.
   * Why: early-return when first token != FUNCTION left the body unskipped; top-level
   *   loop then re-ingested body `let` as module top_level_lets → init_globals with free
   *   params (module/arena) → host-cc red. Authority: this function only (G.7).
   */
  if (r.tok.kind == (int32_t)TOKEN_EXPORT) {
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
  }
  if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
  } else if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  /* r is function name IDENT (either after consuming FUNCTION, or anchor was already name). */
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  lex_cur = lex;
  parser_asm_skip_balanced_parens_into_slice_c(&lex_cur, r.next_lex, source);
  lexer_next_into(&r, lex_cur, source);
  if (r.tok.kind != (int32_t)TOKEN_COLON) {
    out->pos = lex_cur.pos;
    out->line = lex_cur.line;
    out->col = lex_cur.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex_cur, r);
  {
    struct parser_asm_lexer ret_audit = lex_cur;
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_return_type_audit_c(&ret_audit, source));
  }
  lexer_next_into(&r, lex_cur, source);
  while (r.tok.kind != (int32_t)TOKEN_LBRACE && r.tok.kind != (int32_t)TOKEN_EOF) {
    parser_asm_lex_from_result_val_into(&lex_cur, r);
    lexer_next_into(&r, lex_cur, source);
  }
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    if (dbg_skip && dbg_skip[0] && dbg_skip[0] != '0') {
      /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
      { char _db[256]; int _dn = snprintf(_db, sizeof _db,
          "note: skip function debug: no-body start_pos=%zu scan_pos=%zu tok=%d ident_len=%d\n",
          lex.pos, lex_cur.pos, (int)r.tok.kind, (int)r.tok.ident_len);
        if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
    }
    out->pos = lex_cur.pos;
    out->line = lex_cur.line;
    out->col = lex_cur.col;
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_body_block_stmt_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_deep_audit_c(r.next_lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_kind_probe_c(r.next_lex, source, 0));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_mega_full_deep_audit_c(r.next_lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_mega_full_deep_audit_c(lex, source));
  parser_asm_skip_balanced_braces_into_slice_c(out, r.next_lex, source);
  if (dbg_skip && dbg_skip[0] && dbg_skip[0] != '0') {
    struct parser_asm_lexer_result tail;
    memset(&tail, 0, sizeof(tail));
    lexer_next_into(&tail, *out, source);
    /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
    { char _db[256]; int _dn = snprintf(_db, sizeof _db,
        "note: skip function debug: start_pos=%zu body_pos=%zu out_pos=%zu next_tok=%d next_ident_len=%d\n",
        lex.pos, r.next_lex.pos, out->pos, (int)tail.tok.kind, (int)tail.tok.ident_len);
      if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
  }
}

/**
 * skip_one_function_full_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_function_full_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                             struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_function_full_into_slice_c(out, lex, source);
}

/**
 * lex_from_try_skip_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_lex_from_try_skip_into_glue(struct parser_asm_lexer *out,
                                        struct parser_asm_try_skip_allow_result t) {
  parser_asm_lex_from_try_skip_into_c(out, t);
}

/**
 * lex_from_library_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_lex_from_library_into_glue(struct parser_asm_lexer *out,
                                       struct parser_asm_library_parse_result lib) {
  parser_asm_lex_from_library_into_c(out, lib);
}

/**
 * copy_lex_from_import_into_glue：CollectImportsResult.lex → *out（thin delegate / extern bl）。
 */
void parser_lex_copy_from_import_into_glue(struct parser_asm_lexer *out,
                                           struct parser_asm_collect_imports_result res) {
  if (!out)
    return;
  out->pos = res.lex.pos;
  out->line = res.lex.line;
  out->col = res.lex.col;
}

/**
 * lex_from_next_into_glue：LexerResult.next_lex → *out（thin delegate / extern bl）。
 */
void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r) {
  parser_asm_lex_from_result_val_into(out, r);
}

/**
 * lex_from_result_ptr_into_glue：*LexerResult.next_lex → *out（thin delegate / extern bl）。
 */
void parser_lex_from_result_ptr_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result *r) {
  parser_lex_from_lexer_result_ptr_into(out, r);
}

extern int32_t pipeline_type_kind_ord_at(void *arena, int32_t ref);

/**
 * parser_should_wrap_func_tail_in_return_glue：OneFuncResult 尾 return 是否须包 EXPR_RETURN（EMIT_HEAVY 勿 X emit）。
 * 与 parser.x 一致：仅 has_explicit_return_kw 时包 RETURN；裸 `{ 0 }` 留 EXPR_LIT 供 typeck 拒绝。
 */
int32_t parser_should_wrap_func_tail_in_return_glue(void *arena, struct parser_asm_onefunc_result *res,
                                                    int32_t type_ref) {
  int32_t kind;
  if (type_ref <= 0)
    return 0;
  if (!arena || !res)
    return 0;
  kind = pipeline_type_kind_ord_at(arena, type_ref);
  if (kind < 0 || kind == (int32_t)AST_TYPE_VOID)
    return 0;
  return res->has_explicit_return_kw ? 1 : 0;
}

/**
 * lex_from_onefunc_next_into_glue：*OneFuncResult.next_lex → *out（thin delegate / extern bl）。
 */
void parser_lex_from_onefunc_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_onefunc_result *res) {
  if (!out || !res)
    return;
  out->pos = res->next_lex.pos;
  out->line = res->next_lex.line;
  out->col = res->next_lex.col;
}

/**
 * parse_one_function_library_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_parse_one_function_library_into_glue(struct parser_asm_library_parse_result *out, void *arena,
                                                 void *module, struct parser_asm_lexer lex,
                                                 struct parser_asm_slice_u8 *source) {
  parser_asm_parse_one_function_library_into_slice_c(out, arena, module, lex, source);
}

/**
 * parse_into_try_skip_allow_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_parse_into_try_skip_allow_into_glue(struct parser_asm_try_skip_allow_result *out,
                                                struct parser_asm_lexer lex,
                                                struct parser_asm_lexer_result r,
                                                struct parser_asm_slice_u8 *source) {
  parser_asm_parse_into_try_skip_allow_into_slice_c(out, lex, r, source);
}

/**
 * parse_into_try_skip_allow_into_buf_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_parse_into_try_skip_allow_into_buf_glue(struct parser_asm_try_skip_allow_result *out,
                                                    struct parser_asm_lexer lex,
                                                    struct parser_asm_lexer_result r, uint8_t *data,
                                                    int32_t len) {
  parser_asm_parse_into_try_skip_allow_into_buf_c(out, lex, r, data, len);
}

/**
 * module_append_enum_variants_and_skip_body_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_module_append_enum_variants_and_skip_body_into_glue(void *module, int32_t enum_idx,
                                                                struct parser_asm_lexer *out,
                                                                struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source) {
  parser_asm_module_append_enum_variants_and_skip_body_into_slice_c(module, enum_idx, out, lex, source);
}

/**
 * skip_one_enum_register_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_skip_one_enum_register_into_glue(void *module, struct parser_asm_lexer *out,
                                            struct parser_asm_lexer lex,
                                            struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_enum_register_into_slice_c(module, out, lex, source);
}

/** module_append_enum_variants_and_skip_body_into_buf_glue：buf 路径 enum 变体扫描。 */
void parser_module_append_enum_variants_and_skip_body_into_buf_glue(void *module, int32_t enum_idx,
                                                                    struct parser_asm_lexer *out,
                                                                    struct parser_asm_lexer lex, uint8_t *data,
                                                                    int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variants_body_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_module_append_enum_variants_and_skip_body_into_slice_c(module, enum_idx, out, lex, &source);
}

/** skip_one_enum_register_into_buf_glue：buf 路径 skip_one_enum_register_into。 */
void parser_skip_one_enum_register_into_buf_glue(void *module, struct parser_asm_lexer *out,
                                                 struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_enum_register_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_body_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variants_body_from_header_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_enum_register_into_slice_c(module, out, lex, &source);
}

/**
 * try_skip_allow_padding_struct_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_try_skip_allow_padding_struct_glue(struct parser_asm_try_skip_allow_result *out,
                                               struct parser_asm_lexer lex,
                                               struct parser_asm_slice_u8 *source) {
  struct parser_asm_try_skip_allow_result res;
  if (!out)
    return;
  res = parser_asm_try_skip_allow_padding_struct_slice_c(lex, source);
  *out = res;
}

/**
 * try_skip_allow_padding_struct_buf_glue：extern bl / thin delegate buf 路径 C 实现。
 */
void parser_try_skip_allow_padding_struct_buf_glue(struct parser_asm_try_skip_allow_result *out,
                                                   struct parser_asm_lexer lex, uint8_t *data,
                                                   int32_t len) {
  struct parser_asm_try_skip_allow_result res;
  if (!out)
    return;
  res = parser_asm_try_skip_allow_padding_struct_buf_c(lex, data, len);
  *out = res;
}

/**
 * parse_one_extern_skip_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_parse_one_extern_skip_into_glue(struct parser_asm_extern_parse_result *out, void *arena,
                                            struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  parser_asm_parse_one_extern_skip_into_slice_c(out, arena, lex, source);
}

/**
 * parse_one_extern_and_add_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_parse_one_extern_and_add_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                               struct parser_asm_slice_u8 *source,
                                               struct parser_asm_lexer *lex_out) {
  parser_asm_parse_one_extern_and_add_into_slice_c(arena, module, lex, source, lex_out);
}

/** parse_one_extern_and_add_into_buf_glue：buf 路径 parse_one_extern_and_add_into。 */
void parser_parse_one_extern_and_add_into_buf_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                                   uint8_t *data, int32_t len, struct parser_asm_lexer *lex_out) {
  struct parser_asm_slice_u8 source;
  if (!data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_one_extern_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_body_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_skip_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_skip_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_skip_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_parse_one_extern_and_add_into_slice_c(arena, module, lex, &source, lex_out);
}

/**
 * is_pointee_type_token_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_is_pointee_type_token_glue(int32_t kind) {
  return parser_asm_is_pointee_type_token_c(kind);
}

/**
 * module_register_arena_func_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_module_register_arena_func_glue(void *module, int32_t func_ref, struct ast_Func f) {
  return parser_asm_module_register_arena_func_c(module, func_ref, f);
}

/**
 * write_extern_params_to_pools_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
void parser_write_extern_params_to_pools_glue(void *arena, void *module, int32_t func_ref, int32_t fi,
                                              struct parser_asm_extern_parse_result *res) {
  parser_asm_write_extern_params_to_pools_c(arena, module, func_ref, fi, res);
}

/**
 * alloc_pointee_type_ref_from_tok_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_alloc_pointee_type_ref_from_tok_glue(void *arena, struct parser_asm_slice_u8 *source,
                                                    struct parser_asm_lexer_result *r) {
  return parser_asm_alloc_pointee_type_ref_from_tok_c(arena, source, r);
}

/**
 * parse_type_ref_for_arena_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_parse_type_ref_for_arena_into_glue(void *arena, struct parser_asm_lexer lex,
                                                  struct parser_asm_slice_u8 *source,
                                                  struct parser_asm_lexer *out_lex) {
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_peek_audit_c(lex, source));
  return parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex, source, out_lex);
}

/**
 * consume_qualified_type_ident_name_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_consume_qualified_type_ident_name_glue(struct parser_asm_slice_u8 *source,
                                                      struct parser_asm_lexer_result *r, uint8_t *out,
                                                      int32_t *out_len) {
  return parser_asm_consume_qualified_type_ident_name_c(source, r, out, out_len);
}

/**
 * parser_alloc_vector_type_ref_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_parser_alloc_vector_type_ref_glue(void *arena, int32_t elem_ord, int32_t lanes) {
  return parser_asm_alloc_vector_type_ref_c(arena, elem_ord, lanes);
}

/**
 * parser_vector_type_ref_from_ident_spelling_glue：extern bl / thin delegate 共用 C 实现。
 */
int32_t parser_parser_vector_type_ref_from_ident_spelling_glue(void *arena, struct parser_asm_slice_u8 *source,
                                                               struct parser_asm_lexer_result r) {
  return parser_asm_vector_type_ref_from_ident_spelling_c(arena, source, r);
}

/**
 * parse_struct_record_layout_into_glue：extern bl 白名单 / thin delegate 共用 C 实现。
 */
int32_t parser_parse_struct_record_layout_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source,
                                                    struct parser_asm_lexer *out_lex, int32_t allow_pad,
                                                    int32_t force_soa, int32_t repr_compat) {
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_record_layout_body_audit_c(lex, source));
  return parser_asm_parse_struct_record_layout_into_slice_c(arena, module, lex, source, out_lex, allow_pad, force_soa,
                                                           repr_compat);
}

/** struct_layout_name_exists_arr_glue：同名 struct layout 探测（extern bl 白名单 / thin delegate）。 */
int32_t parser_struct_layout_name_exists_arr_glue(void *module, uint8_t *nm, int32_t nlen) {
  return parser_asm_struct_layout_name_exists_arr_c(module, nm, nlen);
}

/** struct_layout_first_name_match_idx_glue：返回首个同名 layout 下标。 */
int32_t parser_struct_layout_first_name_match_idx_glue(void *module, uint8_t *nm, int32_t nlen) {
  return parser_asm_struct_layout_first_name_match_idx_c(module, nm, nlen);
}

/** struct_layout_placeholder_idx_glue：返回同名占位 layout 槽下标。 */
int32_t parser_struct_layout_placeholder_idx_glue(void *module, uint8_t *nm, int32_t nlen) {
  return parser_asm_struct_layout_placeholder_idx_c(module, nm, nlen);
}

/** parse_body_let_bracket_compound_init_ref_glue：let `[..]` 复合初值 parse_expr_into 回调 X。 */
int32_t parser_parse_body_let_bracket_compound_init_ref_glue(void *arena, size_t bracket_start,
                                                               struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source,
                                                               struct parser_asm_lexer *lex_out,
                                                               struct parser_asm_lexer_result *r_out) {
  return parser_asm_parse_body_let_bracket_compound_init_ref_slice_c(arena, bracket_start, lex, source, lex_out,
                                                                       r_out);
}

/** parse_cond_expr_into_glue：if/while 条件 int+as 探测 + parse_expr_into 回调 X。 */
void parser_parse_cond_expr_into_glue(void *arena, struct parser_asm_lexer lex_start,
                                      struct parser_asm_slice_u8 *source,
                                      struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_cond_expr_into_slice_c(arena, lex_start, source, out);
}

/** parse_one_top_level_let_into_glue：顶层 let/const 解析；expr 回调 parse_expr_into X。 */
void parser_parse_one_top_level_let_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                              struct parser_asm_slice_u8 *source, int32_t is_const,
                                              struct parser_asm_top_level_let_result *out) {
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_probe_c(lex, source, is_const));
  parser_asm_parse_one_top_level_let_into_slice_c(arena, module, lex, source, is_const, out);
}

/** parse_one_type_alias_into_glue：顶层 type Alias = Target;（lex 位于 type 之后）。 */
void parser_parse_one_type_alias_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                           struct parser_asm_slice_u8 *source,
                                           struct parser_asm_type_alias_result *out) {
  parser_asm_parse_one_type_alias_into_slice_c(arena, module, lex, source, out);
}

/** parse_one_function_buf_into_glue：buf 路径精简 function 解析（LexerResult 链勿 X emit）。 */
void parser_parse_one_function_buf_into_glue(struct parser_asm_onefunc_result *out, void *arena,
                                           struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_one_function_buf_deep_audit_c(lex, data, len));
  parser_asm_parse_one_function_buf_into_c(out, arena, lex, data, len);
}

/** fill_block_const_let_from_res_glue：OneFunc 侧车 → block const/let（Expr 按值勿 X emit）。 */
int32_t parser_fill_block_const_let_from_res_glue(void *arena, int32_t block_ref, struct parser_asm_onefunc_result *res,
                                                  int32_t type_ref) {
  return parser_asm_fill_block_const_let_from_res_c(arena, block_ref, res, type_ref);
}

/** append_block_lets_from_res_glue：在已有块上追加 res 中 let（从 let_base 起）。 */
int32_t parser_append_block_lets_from_res_glue(void *arena, int32_t block_ref, struct parser_asm_onefunc_result *res,
                                               int32_t let_base, int32_t type_ref) {
  return parser_asm_append_block_lets_from_res_c(arena, block_ref, res, let_base, type_ref);
}

/** parse_if_stmt_into_glue：单条 if（含 else / else if）；回调 parse_block X mega。 */
int32_t parser_parse_if_stmt_into_glue(void *arena, struct parser_asm_lexer lex_at_if,
                                       struct parser_asm_slice_u8 *source, int32_t type_ref, int32_t *out_cond,
                                       int32_t *out_then, int32_t *out_else, struct parser_asm_lexer *lex_out) {
  return parser_asm_parse_if_stmt_into_c(arena, lex_at_if, source, type_ref, out_cond, out_then, out_else, lex_out);
}

/** parse_match_subject_into_glue: match subject. Bare IDENT → EXPR_VAR;
 * IDENT+CALL/INDEX/FIELD postfix → parse_expr_into. Thin wrapper (G.7). */
void parser_parse_match_subject_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                          struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_match_subject_into_c(arena, lex, source, out);
}

/** parse_match_into_glue：整段 match 表达式；回调 subject glue + parse_expr_into X mega。 */
void parser_parse_match_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                  struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_match_into_c(arena, lex, source, out);
}

/** parse_at_simd_builtin_into_glue：@shuffle / @select → CALL simd_*（LexerResult 入参勿 X emit）。 */
void parser_parse_at_simd_builtin_into_glue(void *arena, struct parser_asm_lexer_result r0,
                                            struct parser_asm_slice_u8 *source,
                                            struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_at_simd_builtin_into_c(arena, r0, source, out);
}

/** parse_if_expr_into_glue：if 条件表达式 → EXPR_IF（回调 parse_block X mega）。 */
void parser_parse_if_expr_into_glue(void *arena, struct parser_asm_lexer lex_at_if, struct parser_asm_slice_u8 *source,
                                   int32_t type_ref, struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_if_expr_into_c(arena, lex_at_if, source, type_ref, out);
}

/** finish_struct_lit_from_type_ident_into_glue：TypeName { fields } 后缀（primary_slice / parser.x thin delegate）。 */
void parser_finish_struct_lit_from_type_ident_into_glue(void *arena, int32_t lit_ref,
                                                        struct parser_asm_lexer lex_in_brace,
                                                        struct parser_asm_slice_u8 *source,
                                                        struct parser_asm_parse_expr_result *out) {
  parser_asm_finish_struct_lit_from_type_ident_into_c(arena, lit_ref, lex_in_brace, source, out);
}

/** diag_lex_after_imports_glue：lexer_init + skip_imports，返回跳过顶层 import 后的 lex。 */
struct parser_asm_lexer parser_diag_lex_after_imports_glue(struct parser_asm_slice_u8 *source) {
  return parser_asm_diag_lex_after_imports_slice_c(source);
}

/** diag_after_imports_then_structs_glue：peek 首 token 并跳过连续 struct，返回首个非 struct 的 LexerResult。 */
struct parser_asm_lexer_result parser_diag_after_imports_then_structs_glue(
    struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  return parser_asm_diag_after_imports_then_structs_slice_c(lex, source);
}

/** diag_after_imports_then_structs_buf_glue：buf 路径跳过连续 struct 后 peek 首 token。 */
struct parser_asm_lexer_result parser_diag_after_imports_then_structs_buf_glue(struct parser_asm_lexer lex,
                                                                               uint8_t *data, int32_t len) {
  return parser_asm_diag_after_imports_then_structs_buf_c(lex, data, len);
}

/** diag_fail_at_token_kind_glue：模拟 parse_one_function 顺序检查，返回首次失败 token kind（成功 -1）。 */
int32_t parser_diag_fail_at_token_kind_glue(struct parser_asm_slice_u8 *source) {
  return parser_asm_diag_fail_at_token_kind_slice_c(source);
}

/** diag_fail_at_token_kind_buf_glue：buf 路径 diag_fail_at_token_kind。 */
int32_t parser_diag_fail_at_token_kind_buf_glue(uint8_t *data, int32_t len) {
  return parser_asm_diag_fail_at_token_kind_buf_c(data, len);
}

/** diag_token_after_collect_imports_glue：collect_imports 后 peek 下一 token kind。 */
int32_t parser_diag_token_after_collect_imports_glue(struct parser_asm_slice_u8 *source, void *module) {
  return parser_asm_diag_token_after_collect_imports_slice_c(source, module);
}

/** diag_token_after_collect_imports_buf_glue：buf 路径 collect_imports 后 peek 下一 token kind。 */
int32_t parser_diag_token_after_collect_imports_buf_glue(uint8_t *data, int32_t len, void *module) {
  return parser_asm_diag_token_after_collect_imports_buf_c(data, len, module);
}

/** diag_parse_one_after_collect_imports_glue：collect_imports 后 parse_one_function_impl，返回 res.ok。 */
int32_t parser_diag_parse_one_after_collect_imports_glue(struct parser_asm_slice_u8 *source, void *module,
                                                         void *arena) {
  return parser_asm_diag_parse_one_after_collect_imports_slice_c(source, module, arena);
}

/** diag_parse_one_after_collect_imports_buf_glue：buf 路径 collect_imports 后 parse_one_function_impl。 */
int32_t parser_diag_parse_one_after_collect_imports_buf_glue(uint8_t *data, int32_t len, void *module, void *arena) {
  return parser_asm_diag_parse_one_after_collect_imports_buf_c(data, len, module, arena);
}

/** parse_one_function_ok_for_pipeline_glue：lexer_init 后直接 parse_one_function_impl（pipeline 诊断）。 */
int32_t parser_parse_one_function_ok_for_pipeline_glue(void *arena, struct parser_asm_slice_u8 *source) {
  return parser_asm_parse_one_function_ok_for_pipeline_slice_c(arena, source);
}

/** parse_one_function_ok_for_pipeline_buf_glue：buf 路径 pipeline 诊断 parse_one。 */
int32_t parser_parse_one_function_ok_for_pipeline_buf_glue(void *arena, uint8_t *data, int32_t len) {
  return parser_asm_parse_one_function_ok_for_pipeline_buf_c(arena, data, len);
}

/** skip_imports_glue：跳过顶层 import path; 语句，返回首个非 import 的 lex。 */
struct parser_asm_lexer parser_skip_imports_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  return parser_asm_skip_imports_slice_c(lex, source);
}

/** skip_imports_buf_glue：buf 路径跳过顶层 import 语句。 */
struct parser_asm_lexer parser_skip_imports_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  return parser_asm_skip_imports_buf_c(lex, data, len);
}

/** B-01/B-19：跳过一条顶层 const 声明（含 const import）；lex 位于 const 前。 */
void parser_skip_one_top_level_const_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_top_level_const_into_slice_c(out, lex, source);
}

/** buf 路径：跳过一条顶层 const 声明。 */
void parser_skip_one_top_level_const_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                    uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!data || len <= 0) {
    if (out)
      *out = lex;
    return;
  }
  source.data = data;
  source.length = (size_t)len;
  parser_asm_skip_one_top_level_const_into_slice_c(out, lex, &source);
}

/** B-01/B-19：跳过一条顶层 let 声明（slice 路径；与 const_into 对称）。
 * PLATFORM: SHARED — product Cap emit passes xlang_slice by value; glue takes *slice. */
void parser_skip_one_top_level_let_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                              struct parser_asm_slice_u8 *source) {
  parser_asm_skip_one_top_level_let_into_slice_c(out, lex, source);
}

/** buf 路径：跳过一条顶层 let 声明。 */
void parser_skip_one_top_level_let_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                  uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!data || len <= 0) {
    if (out)
      *out = lex;
    return;
  }
  source.data = data;
  source.length = (size_t)len;
  parser_asm_skip_one_top_level_let_into_slice_c(out, lex, &source);
}

/** collect_imports_glue：收集顶层 import 路径到 module，并写出跳过 import 后的 lex。 */
void parser_collect_imports_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source, void *module,
                                 struct parser_asm_collect_imports_result *out) {
  parser_asm_collect_imports_slice_c(lex, source, module, out);
}

/** collect_imports_buf_glue：(data,len) 路径委托 slice collect_imports。 */
void parser_collect_imports_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len, void *module,
                                     struct parser_asm_collect_imports_result *out) {
  parser_asm_collect_imports_buf_c(lex, data, len, module, out);
}

/**
 * is_compound_assign_token_glue：判断是否为 += … >>= 等复合赋值 token（EMIT_HEAVY 勿 X emit）。
 */
int32_t parser_is_compound_assign_token_glue(int32_t kind) {
  return parser_asm_is_compound_assign_token_c(kind);
}

/** parse_into_init 依赖 pipeline/ast_pool 重置（onefunc prime 由 parser_x.o / strict 链提供，thin glue 勿硬链）。 */
extern void pipeline_strict_parse_into_init(void *arena, void *module);
extern void pipeline_module_reset_parse_counters_c(void *module);
extern void pipeline_parser_set_match_module(void *module);

/**
 * parse_into_init_glue：arena/module 重置 + parse 计数（EMIT_HEAVY 勿 X emit；等价 parser.x parse_into_init）。
 */
void parser_parse_into_init_glue(void *module, void *arena) {
  pipeline_strict_parse_into_init(arena, module);
  pipeline_module_reset_parse_counters_c(module);
  pipeline_parser_set_match_module(module);
}

/** skip_balanced_parens_glue：从已消费 '(' 的 lex 起跳过匹配括号。 */
struct parser_asm_lexer parser_skip_balanced_parens_glue(struct parser_asm_lexer lex,
                                                       struct parser_asm_slice_u8 *source) {
  return parser_asm_skip_balanced_parens_slice_c(lex, source);
}

/** skip_balanced_parens_into_glue：结果写入 *out，避免 Lexer 按值返回 ABI 问题。 */
void parser_skip_balanced_parens_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                           struct parser_asm_slice_u8 *source) {
  parser_asm_skip_balanced_parens_into_slice_c(out, lex, source);
}

/** skip_balanced_parens_buf_glue：buf 路径跳过匹配括号。 */
struct parser_asm_lexer parser_skip_balanced_parens_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                             int32_t len) {
  return parser_asm_skip_balanced_parens_buf_c(lex, data, len);
}

/** skip_balanced_parens_into_buf_glue：buf 路径结果写入 *out。 */
void parser_skip_balanced_parens_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                              uint8_t *data, int32_t len) {
  parser_asm_skip_balanced_parens_into_buf_c(out, lex, data, len);
}

/** skip_balanced_braces_glue：从已消费 '{' 的 lex 起跳过匹配大括号。 */
struct parser_asm_lexer parser_skip_balanced_braces_glue(struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source) {
  return parser_asm_skip_balanced_braces_slice_c(lex, source);
}

/** skip_balanced_braces_into_glue：结果写入 *out，避免 Lexer 按值返回 ABI 问题。 */
void parser_skip_balanced_braces_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                           struct parser_asm_slice_u8 *source) {
  parser_asm_skip_balanced_braces_into_slice_c(out, lex, source);
}

/** skip_balanced_braces_buf_glue：buf 路径跳过匹配大括号。 */
struct parser_asm_lexer parser_skip_balanced_braces_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                             int32_t len) {
  return parser_asm_skip_balanced_braces_buf_c(lex, data, len);
}

/** skip_balanced_braces_into_buf_glue：buf 路径结果写入 *out。 */
void parser_skip_balanced_braces_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                             uint8_t *data, int32_t len) {
  parser_asm_skip_balanced_braces_into_buf_c(out, lex, data, len);
}

/** lex_from_library_glue：LibraryParseResult.next_lex 三字段按值返回 Lexer。 */
struct parser_asm_lexer parser_lex_from_library_glue(struct parser_asm_library_parse_result lib) {
  return parser_asm_lex_from_library_c(lib);
}

/** lex_from_try_skip_glue：TrySkipAllowResult.lex 三字段按值返回 Lexer。 */
struct parser_asm_lexer parser_lex_from_try_skip_glue(struct parser_asm_try_skip_allow_result t) {
  return parser_asm_lex_from_try_skip_c(t);
}

/** parse_one_function_library_buf_glue：(data,len) 路径 library 解析，按值返回 LibraryParseResult。 */
struct parser_asm_library_parse_result parser_parse_one_function_library_buf_glue(
    void *arena, void *module, struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  return parser_asm_parse_one_function_library_buf_c(arena, module, lex, data, len);
}

/** parse_one_function_library_scan_glue：库函数 token 扫描，写入 LibraryParseScanResult。 */
int32_t parser_parse_one_function_library_scan_glue(struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source,
                                                    struct parser_asm_library_parse_scan_result *result) {
  return parser_asm_parse_one_function_library_scan_slice_c(lex, source, result);
}

/** parse_one_function_library_glue：库函数解析（scan + AST），按值返回 LibraryParseResult。 */
struct parser_asm_library_parse_result parser_parse_one_function_library_glue(
    void *arena, void *module, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  return parser_asm_parse_one_function_library_slice_c(arena, module, lex, source);
}

/** diag_skip_let_const_buf_glue：buf 路径跳过 body 内 let/const 链。 */
struct parser_asm_lexer_result parser_diag_skip_let_const_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                                 int32_t len) {
  return parser_asm_diag_skip_let_const_buf_c(lex, data, len);
}

/** body_skip_let_const_then_if_buf_glue：buf 路径跳过 let/const + if 链。 */
struct parser_asm_lexer_result parser_body_skip_let_const_then_if_buf_glue(struct parser_asm_lexer lex,
                                                                           uint8_t *data, int32_t len) {
  return parser_asm_body_skip_let_const_then_if_buf_c(lex, data, len);
}

/** body_skip_let_const_then_if_glue：slice 路径按值返回 LexerResult（勿 X emit 深循环体）。 */
struct parser_asm_lexer_result parser_body_skip_let_const_then_if_glue(struct parser_asm_lexer lex,
                                                                      struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  parser_asm_body_skip_let_const_then_if_into_slice_c(&r, lex, source);
  return r;
}

/** skip_one_function_full_glue：跳过整条 function 定义，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_function_full_glue(struct parser_asm_lexer lex,
                                                           struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out = lex;
  parser_asm_skip_one_function_full_into_slice_c(&out, lex, source);
  return out;
}

/** skip_one_function_full_buf_glue：buf 路径 skip_one_function_full。 */
struct parser_asm_lexer parser_skip_one_function_full_buf_glue(struct parser_asm_lexer lex, uint8_t *data,
                                                               int32_t len) {
  struct parser_asm_lexer out = lex;
  struct parser_asm_slice_u8 source;
  if (!data) {
    out = lex;
    return out;
  }
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_function_full_into_slice_c(&out, lex, &source);
  return out;
}

/** skip_one_function_full_into_buf_glue：buf 路径 skip_one_function_full_into。 */
void parser_skip_one_function_full_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                 uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_function_full_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_function_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_sig_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_function_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_control_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sig_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_loop_control_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_stmt_control_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_control_flow_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_subject_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_arms_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_return_stmt_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_block_stmt_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_body_block_stmt_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_function_full_into_slice_c(out, lex, &source);
}

/** parse_into_try_skip_allow_glue：主循环 allow(padding) 包装，TrySkipAllowResult 按值返回。 */
struct parser_asm_try_skip_allow_result parser_parse_into_try_skip_allow_glue(struct parser_asm_lexer lex,
                                                                              struct parser_asm_lexer_result r,
                                                                              struct parser_asm_slice_u8 *source) {
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len != 5) {
    struct parser_asm_try_skip_allow_result z;
    z.lex = lex;
    z.skipped = 0;
    return z;
  }
  return parser_asm_try_skip_allow_padding_struct_slice_c(r.next_lex, source);
}

/** parse_into_try_skip_allow_buf_glue：buf 路径 parse_into_try_skip_allow。 */
struct parser_asm_try_skip_allow_result parser_parse_into_try_skip_allow_buf_glue(struct parser_asm_lexer lex,
                                                                                  struct parser_asm_lexer_result r,
                                                                                  uint8_t *data, int32_t len) {
  if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len != 5) {
    struct parser_asm_try_skip_allow_result z;
    z.lex = lex;
    z.skipped = 0;
    return z;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_allow_kw_paren_buf_audit_c(r, data, len));
  return parser_asm_try_skip_allow_padding_struct_buf_c(r.next_lex, data, len);
}

/** try_skip_allow_padding_struct_value_glue：allow(padding) 前缀，TrySkipAllowResult 按值返回。 */
struct parser_asm_try_skip_allow_result parser_try_skip_allow_padding_struct_value_glue(
    struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  return parser_asm_try_skip_allow_padding_struct_slice_c(lex, source);
}

/** try_skip_allow_padding_struct_buf_value_glue：buf 路径 try_skip_allow_padding_struct。 */
struct parser_asm_try_skip_allow_result parser_try_skip_allow_padding_struct_buf_value_glue(
    struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  return parser_asm_try_skip_allow_padding_struct_buf_c(lex, data, len);
}

/** parse_peek_function_name_buf_glue：从 function 关键字起读出函数名，失败返回 0。 */
int32_t parser_parse_peek_function_name_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len,
                                                 uint8_t *out) {
  return parser_asm_parse_peek_function_name_buf_c(lex, data, len, out);
}

/** skip_one_struct_glue：跳过一条顶层 struct 定义，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_struct_glue(struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source) {
  return parser_asm_skip_one_struct_slice_c(lex, source);
}

/** skip_one_struct_into_buf_glue：buf 路径 skip_one_struct_into。 */
void parser_skip_one_struct_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex, uint8_t *data,
                                          int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_struct_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_fields_body_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_skip_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_layout_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_skip_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_struct_layout_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_skip_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_struct_into_slice_c(out, lex, &source);
}

/** skip_one_struct_buf_glue：buf 路径 skip_one_struct 按值返回 Lexer。 */
struct parser_asm_lexer parser_skip_one_struct_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer out;
  parser_skip_one_struct_into_buf_glue(&out, lex, data, len);
  return out;
}

/** skip_one_enum_glue：跳过一条顶层 enum 定义，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_enum_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  parser_asm_skip_one_enum_into_slice_c(&out, lex, source);
  return out;
}

/** skip_one_enum_into_buf_glue：buf 路径 skip_one_enum_into。 */
void parser_skip_one_enum_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex, uint8_t *data,
                                        int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_enum_buf_audit_c(&lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_body_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variants_body_from_header_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_skip_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_skip_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_enum_into_slice_c(out, lex, &source);
}

/** skip_one_enum_buf_glue：buf 路径 skip_one_enum 按值返回 Lexer。 */
struct parser_asm_lexer parser_skip_one_enum_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer out;
  parser_skip_one_enum_into_buf_glue(&out, lex, data, len);
  return out;
}

/** skip_one_trait_glue：跳过一条顶层 trait 定义，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_trait_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  parser_asm_skip_one_trait_into_slice_c(&out, lex, source);
  return out;
}

/** skip_one_trait_into_buf_glue：buf 路径 skip_one_trait_into。 */
void parser_skip_one_trait_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex, uint8_t *data,
                                         int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_trait_buf_audit_c(&lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_header_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_body_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_type_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_methods_body_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_skip_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_skip_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  lex = parser_asm_align_lex_to_keyword_prefix_c(lex, &source, "trait", 5);
  parser_asm_skip_one_trait_into_slice_c(out, lex, &source);
}

/** skip_one_trait_buf_glue：buf 路径 skip_one_trait 按值返回 Lexer。 */
struct parser_asm_lexer parser_skip_one_trait_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer out;
  parser_skip_one_trait_into_buf_glue(&out, lex, data, len);
  return out;
}

/** skip_one_impl_glue：跳过一条顶层 impl 块，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_impl_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  parser_asm_skip_one_impl_into_slice_c(&out, lex, source);
  return out;
}

/** skip_one_impl_into_buf_glue：buf 路径 skip_one_impl_into。 */
void parser_skip_one_impl_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex, uint8_t *data,
                                        int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_impl_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_header_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_body_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_type_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_impl_skip_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  lex = parser_asm_align_lex_to_keyword_prefix_c(lex, &source, "impl", 4);
  parser_asm_skip_one_impl_into_slice_c(out, lex, &source);
}

/** skip_one_impl_buf_glue：buf 路径 skip_one_impl 按值返回 Lexer。 */
struct parser_asm_lexer parser_skip_one_impl_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer out;
  parser_skip_one_impl_into_buf_glue(&out, lex, data, len);
  return out;
}

/** skip_one_extern_glue：跳过一条顶层 extern 声明，Lexer 按值返回。 */
struct parser_asm_lexer parser_skip_one_extern_glue(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  parser_asm_skip_one_extern_into_slice_c(&out, lex, source);
  return out;
}

/** skip_one_extern_into_buf_glue：buf 路径 skip_one_extern_into。 */
void parser_skip_one_extern_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex, uint8_t *data,
                                          int32_t len) {
  struct parser_asm_slice_u8 source;
  if (!out || !data)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_extern_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_extern_body_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_skip_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_skip_mega_full_deep_buf_audit_c(lex, data, len));
  source.data = data;
  source.length = len >= 0 ? (size_t)len : 0;
  parser_asm_skip_one_extern_into_slice_c(out, lex, &source);
}

/** skip_one_extern_buf_glue：buf 路径 skip_one_extern 按值返回 Lexer。 */
struct parser_asm_lexer parser_skip_one_extern_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer out;
  parser_skip_one_extern_into_buf_glue(&out, lex, data, len);
  return out;
}

/** expr_set_common_zeros_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_expr_set_common_zeros_glue(struct parser_asm_ast_expr *e) {
  parser_asm_expr_set_common_zeros_c(e);
}

/** parse_as_suffix_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_as_suffix_into_glue(void *arena, struct parser_asm_slice_u8 *source,
                                      struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_as_suffix_into_slice_c(arena, source, out);
}

/** parse_unary_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_unary_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                  struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_unary_into_slice_c(arena, lex, source, out);
}

/** parse_cast_into_glue：unary + as_suffix 链（EMIT_HEAVY 勿 X emit）。 */
void parser_parse_cast_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                               struct parser_asm_parse_expr_result *out) {
  if (!out)
    return;
  parser_parse_unary_into_glue(arena, lex, source, out);
  if (!out->ok)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_cast_unary_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_stmt_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_cast_unary_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_ternary_assign_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_stmt_control_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_binop_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_expr_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  parser_parse_as_suffix_into_glue(arena, source, out);
}

/** parse_term_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_term_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                 struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_term_into_slice_c(arena, lex, source, out);
}

/** parse_addsub_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_addsub_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_addsub_into_slice_c(arena, lex, source, out);
}

/** parse_shift_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_shift_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                  struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_shift_into_slice_c(arena, lex, source, out);
}

/** parse_relcompare_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_relcompare_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                       struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_relcompare_into_slice_c(arena, lex, source, out);
}

/** parse_compare_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_compare_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                    struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_compare_into_slice_c(arena, lex, source, out);
}

/** parse_bitand_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_bitand_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_bitand_into_slice_c(arena, lex, source, out);
}

/** parse_bitxor_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_bitxor_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_bitxor_into_slice_c(arena, lex, source, out);
}

/** parse_bitor_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_bitor_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                  struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_bitor_into_slice_c(arena, lex, source, out);
}

/** parse_logand_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_logand_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_logand_into_slice_c(arena, lex, source, out);
}

/** parse_logor_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_logor_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                  struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_logor_into_slice_c(arena, lex, source, out);
}

/** parse_primary_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_primary_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                    struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_primary_into_slice_c(arena, lex, source, out);
}

/** parse_ternary_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_ternary_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                    struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_ternary_into_slice_c(arena, lex, source, out);
}

/** parse_assign_into_glue：extern bl / thin delegate 共用 C 实现。 */
void parser_parse_assign_into_glue(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  parser_asm_parse_assign_into_slice_c(arena, lex, source, out);
}

/** lexer_token_run_len_glue：Token.kind 分派 run_len（勿 X emit Token 按值）。 */
int32_t parser_lexer_token_run_len_glue(struct parser_asm_token tok) {
  return parser_asm_lexer_token_run_len_c(tok);
}

/** lex_at_token_from_result_glue：LexerResult 当前 token 起点 → Lexer 按值返回。 */
struct parser_asm_lexer parser_lex_at_token_from_result_glue(struct parser_asm_lexer_result r) {
  return parser_asm_lex_at_token_from_result_c(r);
}

/** parser_rewind_lex_for_following_stmt_glue：let/if 初值后 lex 回指 stmt 关键字。 */
struct parser_asm_lexer parser_parser_rewind_lex_for_following_stmt_glue(struct parser_asm_lexer lex_in,
                                                                          struct parser_asm_lexer_result r) {
  return parser_asm_parser_rewind_lex_for_following_stmt_c(lex_in, r);
}

/** parse_block return 尾 glue：RBRACE 结束块循环，否则 advance lex。 */
void parser_asm_parse_block_return_end_tail_glue(struct parser_asm_lexer_result *r, struct parser_asm_lexer *lex_cur,
                                                 struct parser_asm_slice_u8 *source, int32_t *stmt_tok_ready,
                                                 int32_t *block_break) {
  parser_asm_parse_block_return_end_tail_c(r, lex_cur, source, stmt_tok_ready, block_break);
}

/** parse_into_set_main_index thin delegate：写 module.main_func_index（勿 X emit 字段 store）。 */
extern void pipeline_module_set_main_func_index(void *m, int32_t idx);

void parser_parse_into_set_main_index_glue(void *module, int32_t main_idx) {
  pipeline_module_set_main_func_index(module, main_idx);
}
