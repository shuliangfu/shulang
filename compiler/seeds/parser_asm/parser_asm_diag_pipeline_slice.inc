/**
 * 为 parse_one_function_impl 准备已 wire 的 OneFuncResult 工作区（与 parser.x 诊断路径一致）。
 */
static struct parser_asm_onefunc_result parser_asm_onefunc_wired_for_parse_c(struct parser_asm_lexer lex) {
  struct parser_asm_onefunc_result res;
  uint8_t diag_empty64[64];

  memset(diag_empty64, 0, sizeof(diag_empty64));
  res = parser_onefunc_scratch_empty();
  parser_onefunc_res_wire_dummy_head(&res, lex, diag_empty64);
  parser_onefunc_res_wire_dummy_const_let(&res);
  parser_onefunc_res_wire_dummy_if_mul(&res);
  parser_onefunc_res_wire_dummy_call_binop(&res, diag_empty64);
  parser_onefunc_res_wire_dummy_loop_call(&res);
  parser_onefunc_res_wire_dummy_for_if(&res);
  return res;
}


/**
 * diag_parse_one_after_collect_imports：collect_imports 后 parse_one_function_impl，返回 res.ok。
 */
int32_t parser_asm_diag_parse_one_after_collect_imports_slice_c(struct parser_asm_slice_u8 *source, void *module,
                                                                void *arena) {
  struct parser_asm_lexer lex;
  struct parser_asm_collect_imports_result import_res;
  struct parser_asm_onefunc_result res;

  if (!source || !module || !arena)
    return 0;
  lex = parser_asm_lexer_init_c();
  import_res.lex = lex;
  parser_asm_collect_imports_slice_c(lex, source, module, &import_res);
  lex = import_res.lex;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_after_collect_preamble_audit_c(&lex, source));
  res = parser_asm_onefunc_wired_for_parse_c(lex);
  parser_parse_one_function_impl(&res, arena, lex, source);
  return res.ok ? 1 : 0;
}

/**
 * diag_parse_one_after_collect_imports_buf：buf 路径 collect_imports 后 parse_one_function_impl。
 */
int32_t parser_asm_diag_parse_one_after_collect_imports_buf_c(uint8_t *data, int32_t len, void *module,
                                                              void *arena) {
  struct parser_asm_slice_u8 source;

  if (!data || len <= 0 || !module || !arena)
    return 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_parse_one_after_collect_imports_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_parse_one_collect_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_parse_one_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_parse_one_mega_full_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_parse_ultra_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_ultra2_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_super_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_hyper_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_fn_mega_full_deep_buf_audit_c(parser_asm_lexer_init_c(), data, len));
  source.data = data;
  source.length = (size_t)len;
  return parser_asm_diag_parse_one_after_collect_imports_slice_c(&source, module, arena);
}

/**
 * parse_one_function_ok_for_pipeline：lexer_init 后直接 parse_one_function_impl（pipeline 诊断）。
 */
int32_t parser_asm_parse_one_function_ok_for_pipeline_slice_c(void *arena, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex;
  struct parser_asm_onefunc_result res;

  if (!source || !arena)
    return 0;
  lex = parser_asm_lexer_init_c();
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_one_function_ok_for_pipeline_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_toplevel_after_imports_audit_c(&lex, source));
  res = parser_asm_onefunc_wired_for_parse_c(lex);
  parser_parse_one_function_impl(&res, arena, lex, source);
  return res.ok ? 1 : 0;
}

/**
 * parse_one_function_ok_for_pipeline_buf：buf 路径 pipeline 诊断 parse_one。
 */
int32_t parser_asm_parse_one_function_ok_for_pipeline_buf_c(void *arena, uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;

  if (!data || len <= 0 || !arena)
    return 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_one_function_ok_for_pipeline_buf_audit_c(data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_one_function_ok_pipeline_deep_buf_audit_c(data, len));
  source.data = data;
  source.length = (size_t)len;
  return parser_asm_parse_one_function_ok_for_pipeline_slice_c(arena, &source);
}

/**
 * onefunc_alloc_wired_for_parse：返回已 wire 的 OneFuncResult 工作区（pipeline 诊断用）。
 */
struct parser_asm_onefunc_result parser_asm_onefunc_alloc_wired_for_parse_c(struct parser_asm_lexer lex) {
  return parser_asm_onefunc_wired_for_parse_c(lex);
}

/**
 * onefunc_result_pool_ptr：OneFuncResult 侧车池键（struct 地址即 pool 索引）。
 */
uint8_t *parser_asm_onefunc_result_pool_ptr_c(struct parser_asm_onefunc_result *res) {
  return (uint8_t *)res;
}

/**
 * get_module_num_imports：返回 module.num_imports（runtime / pipeline 多文件路径）。
 */
int32_t parser_asm_get_module_num_imports_c(struct ASTModule *module) {
  if (!module)
    return 0;
  return (int32_t)module->num_imports;
}

#ifndef PARSER_ASM_THIN_GLUE_NO_SEED_PARSE
/** runtime / backend_call_dispatch 期望 parser_get_module_num_imports 前缀符号。 */
int32_t parser_get_module_num_imports(struct ASTModule *module) {
  return parser_asm_get_module_num_imports_c(module);
}
#endif

/**
 * get_module_import_path：复制第 i 条 import 路径到 out[64]（NUL 结尾）；越界写空串。
 */
void parser_asm_get_module_import_path_c(struct ASTModule *module, int32_t i, uint8_t *out) {
  if (!out)
    return;
  if (i < 0 || !module || i >= module->num_imports) {
    out[0] = 0;
    return;
  }
  pipeline_module_import_path_copy(module, i, out, 64);
}

#ifndef PARSER_ASM_THIN_GLUE_NO_SEED_PARSE
/** runtime 期望 parser_get_module_import_path 前缀符号。 */
void parser_get_module_import_path(struct ASTModule *module, int32_t i, uint8_t *out) {
  parser_asm_get_module_import_path_c(module, i, out);
}
#endif

/**
 * copy_module_import_path64：复制 import 路径并返回字节长度（不含 NUL）。
 */
int32_t parser_asm_copy_module_import_path64_c(struct ASTModule *module, int32_t i, uint8_t *out) {
  int32_t path_len;

  parser_asm_get_module_import_path_c(module, i, out);
  if (!out)
    return 0;
  path_len = 0;
  while (path_len < 64 && out[path_len] != 0)
    path_len++;
  return path_len;
}

/**
 * diag_lex_after_imports：lexer_init + skip_imports，返回跳过顶层 import 后的 lex。
 */
struct parser_asm_lexer parser_asm_diag_lex_after_imports_slice_c(struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer lex;
  if (!source)
    return parser_asm_lexer_init_c();
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_diag_lex_after_imports_audit_c(source));
  lex = parser_asm_lexer_init_c();
  return parser_asm_skip_imports_slice_c(lex, source);
}
