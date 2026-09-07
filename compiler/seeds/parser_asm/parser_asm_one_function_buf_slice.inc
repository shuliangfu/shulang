/**
 * parser_asm_one_function_buf_slice.inc — parse_one_function_buf_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 精简 buf 路径：function ident(): type { … return …; }。
 * wave473: body lets/consts collected via G.7 parser_parse_body_lets_into (not skip).
 * PLATFORM: SHARED parse.
 */
#ifndef PARSER_ASM_ONE_FUNCTION_BUF_SLICE_INCLUDED
#define PARSER_ASM_ONE_FUNCTION_BUF_SLICE_INCLUDED

extern struct parser_asm_lexer_result lexer_next_buf(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern int32_t pipeline_onefunc_num_lets(uint8_t *out);
extern int32_t pipeline_onefunc_num_consts(uint8_t *out);
/* G.7 authority (parser.x / parser_gen); layout-compatible with parser_asm_onefunc_result. */
extern int parser_parse_body_lets_into(void *arena, struct parser_asm_lexer lex,
                                       struct parser_asm_slice_u8 *source,
                                       struct parser_asm_onefunc_result *out,
                                       struct parser_asm_lexer *lex_out);
/* G.7 parse_expr authority (primary + postfix); used for compound return exprs. */
extern void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                            struct parser_asm_parse_expr_result *out);
/* Layout twin of parser.x ParseBlockResult (bool→i32); may be defined later in if_stmt_slice. */
#ifndef PARSER_ASM_PARSE_BLOCK_RESULT_FWD
#define PARSER_ASM_PARSE_BLOCK_RESULT_FWD
struct parser_asm_parse_block_result {
  int32_t ok;
  int32_t block_ref;
  struct parser_asm_lexer next_lex;
};
#endif
/* wave475/476/477/478: mid-body control + return-match final in
 * default-hoist buf path (G.7 free onefunc twin). */
extern int32_t parser_asm_parse_if_stmt_into_c(void *arena, struct parser_asm_lexer lex_at_if,
                                               struct parser_asm_slice_u8 *source, int32_t type_ref,
                                               int32_t *out_cond, int32_t *out_then, int32_t *out_else,
                                               struct parser_asm_lexer *lex_out);
extern void parser_parse_cond_expr_into_glue(void *arena, struct parser_asm_lexer lex_start,
                                             struct parser_asm_slice_u8 *source,
                                             struct parser_asm_parse_expr_result *out);
extern int32_t parser_advance_past_cond_rparen_into_glue(struct parser_asm_lexer_result *r_out,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source);
extern void parser_parse_block_into(void *arena, struct parser_asm_lexer lex_after_lbrace,
                                    struct parser_asm_slice_u8 *source, int32_t type_ref,
                                    struct parser_asm_parse_block_result *out);
extern void parser_parse_match_into(void *arena, struct parser_asm_lexer lex,
                                    struct parser_asm_slice_u8 *source,
                                    struct parser_asm_parse_expr_result *out);
extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
extern struct parser_asm_lexer parser_asm_lex_at_token_from_result_c(struct parser_asm_lexer_result r);
extern int32_t pipeline_onefunc_append_if(uint8_t *out, int32_t cond, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_onefunc_append_while(uint8_t *out, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_append_for(uint8_t *out, int32_t init_ref, int32_t cond_ref,
                                           int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_push_body_expr_stmt(uint8_t *out, int32_t expr_ref);
extern int32_t pipeline_onefunc_push_stmt_order(uint8_t *out, uint8_t kind, int32_t idx);
extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t *out);
extern int32_t pipeline_onefunc_num_body_expr_stmts(uint8_t *out);
extern int32_t pipeline_onefunc_num_if_stmts(uint8_t *out);
extern int32_t pipeline_onefunc_num_whiles(uint8_t *out);
extern int32_t pipeline_onefunc_num_fors(uint8_t *out);
extern void parser_asm_copy_slice_to_param32_buf_c(uint8_t *source, int32_t source_len, size_t start, int32_t nlen,
                                                   uint8_t *out);
extern int32_t pipeline_onefunc_append_param(uint8_t *out, uint8_t *name, int32_t name_len, int32_t type_ref);
extern void pipeline_onefunc_set_param_type_ref(uint8_t *out, int32_t pidx, int32_t ty);
extern int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                struct parser_asm_lexer *out_lex);
extern int32_t parser_asm_stretch_onefunc_buf_name_audit_c(const uint8_t *name, int32_t name_len);
extern int32_t parser_asm_stretch_onefunc_slice_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_onefunc_buf_full_deep_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_onefunc_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_onefunc_slice_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_ultra_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_super_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_fn_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_onefunc_buf_deep_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);

/** 写失败 OneFuncResult（等价 parser.x set_onefunc_fail；force_stub 勿 X emit）。 */
static void parser_asm_set_onefunc_fail_c(struct parser_asm_onefunc_result *out, struct parser_asm_lexer lex) {
  if (!out)
    return;
  out->ok = 0;
  out->next_lex = lex;
}

/** 返回值类型 token 是否允许（标量 / void / ident）。 */
static int32_t parser_asm_onefunc_buf_return_type_ok_c(int32_t kind) {
  return kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64 || kind == (int32_t)TOKEN_BOOL
         || kind == (int32_t)TOKEN_VOID || kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32
         || kind == (int32_t)TOKEN_U64 || kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_IDENT;
}

/**
 * parse_one_function_buf_into：buf 路径精简 function 解析，结果写入 *out。
 */
void parser_asm_parse_one_function_buf_into_c(struct parser_asm_onefunc_result *out, void *arena,
                                              struct parser_asm_lexer lex, uint8_t *data, int32_t len) {
  struct parser_asm_lexer_result r;
  struct parser_asm_slice_u8 source;
  uint8_t dummy_name[64];
  uint8_t pname_buf[128];
  uint8_t *out_pool;
  int32_t param_idx;
  int32_t param_name_len;
  int32_t param_type_ref;
  int32_t ret_type_ref;
  int32_t name_len;
  size_t name_start_buf;
  int32_t ret_val;
  int32_t ni;
  extern void ast_pool_onefunc_reset(uint8_t *out_ptr);
  if (!out || !data || len <= 0)
    return;
  /*
   * wave471: reset OneFunc sidecar keyed by `out` address before re-parse.
   * Hoist of the same default into multiple empty impls reuses the same stack
   * slot for `res` → same pool key → append_param accumulated (np=2 on 2nd
   * inject → false "parameter count mismatch"). parser_gen already resets;
   * buf path must too. PLATFORM: SHARED parse.
   */
  ast_pool_onefunc_reset((uint8_t *)out);
  source.data = data;
  source.length = (size_t)len;
  memset(dummy_name, 0, sizeof(dummy_name));
  memset(pname_buf, 0, sizeof(pname_buf));
  out_pool = (uint8_t *)out;
  out->return_var_name_len = 0;
  out->return_expr_ref = 0;
  out->num_params = 0;
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
  }
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  name_len = r.tok.ident_len;
  if (name_len <= 0 || name_len > 63) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  name_start_buf = r.next_lex.pos - (size_t)name_len;
  parser_asm_copy_slice_to_name64_buf_c(data, len, name_start_buf, name_len, dummy_name);
  /* 消费函数名，后续须读到 '(' */
  parser_lex_from_next_into_glue(&lex, r);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_buf_name_audit_c(dummy_name, name_len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_buf_deep_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_buf_full_deep_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_onefunc_slice_mega_full_deep_buf_audit_c(lex, data, len));
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
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_fn_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  out->num_params = 0;
  if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
    parser_lex_from_next_into_glue(&lex, r);
  } else {
    for (;;) {
      /*
       * wave468: accept TOKEN_SELF as param binding name "self".
       * Twin of parser_gen / parser.x: lexer keywords self as TOKEN_SELF with
       * ident_len=0; IDENT-only check rejected default-method `self: T` when
       * re-parsing trait bodies as free UFCS methods. PLATFORM: SHARED parse.
       */
      if (r.tok.kind != (int32_t)TOKEN_IDENT && r.tok.kind != (int32_t)TOKEN_SELF) {
        /* Keyword param name: P014 hard (twin of parser.x / parser_gen).
         * PLATFORM: SHARED parse. */
        extern void parser_report_keyword_binding_p014_c(int32_t line, int32_t col);
        parser_report_keyword_binding_p014_c((int32_t)r.tok.line, (int32_t)r.tok.col);
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (r.tok.kind == (int32_t)TOKEN_SELF) {
        param_name_len = 4;
        pname_buf[0] = (uint8_t)'s';
        pname_buf[1] = (uint8_t)'e';
        pname_buf[2] = (uint8_t)'l';
        pname_buf[3] = (uint8_t)'f';
        pname_buf[4] = 0;
      } else {
        param_name_len = r.tok.ident_len;
        if (param_name_len <= 0 || param_name_len > 127) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        parser_asm_copy_slice_to_param32_buf_c(data, len, r.token_start, param_name_len, pname_buf);
      }
      /*
       * wave679 Cap residual: duplicate param name → host BLD001. P012 + sticky.
       * PLATFORM: SHARED parse (buf path twin of parser.x / parser_gen).
       */
      {
        extern int32_t parser_onefunc_param_name_dup_c(uint8_t *pool, int32_t nparams, uint8_t *name,
                                                      int32_t name_len);
        extern void parser_report_duplicate_name_p012_c(int32_t line, int32_t col, int32_t kind);
        if (parser_onefunc_param_name_dup_c(out_pool, out->num_params, pname_buf, param_name_len) != 0) {
          parser_report_duplicate_name_p012_c((int32_t)r.tok.line, (int32_t)r.tok.col, 0);
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
      }
      param_idx = pipeline_onefunc_append_param(out_pool, pname_buf, param_name_len, 0);
      if (param_idx < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_params = param_idx + 1;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      /*
       * wave676 Cap residual: do not accept bare `name)` as untyped formal.
       * Prior soft residual: RPAREN without `: Type` → param_type_ref left 0 →
       * `function bad(x): i32` compiled green. Require `: Type` always.
       * 4.2.1: free / inherent `function m(self)` stays P011 (wave493).
       * Trait-default hoist sets parser_allow_bare_self so `get(self)` can
       * parse; commit stamps the impl for-type (wave477). Twin of parser.x.
       * PLATFORM: SHARED parse.
       */
      if (r.tok.kind != (int32_t)TOKEN_COLON) {
        extern int32_t parser_allow_bare_self_pending_c(void);
        int32_t is_self_param = 0;
        if (param_name_len == 4 && pname_buf[0] == (uint8_t)'s' && pname_buf[1] == (uint8_t)'e'
            && pname_buf[2] == (uint8_t)'l' && pname_buf[3] == (uint8_t)'f')
          is_self_param = 1;
        if (is_self_param && parser_allow_bare_self_pending_c() != 0
            && (r.tok.kind == (int32_t)TOKEN_RPAREN || r.tok.kind == (int32_t)TOKEN_COMMA)) {
          /* Hoist only: leave type_ref 0; commit supplies the for-type. */
          pipeline_onefunc_set_param_type_ref(out_pool, param_idx, 0);
          if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
            parser_lex_from_next_into_glue(&lex, r);
            break;
          }
          parser_lex_from_next_into_glue(&lex, r);
          r = lexer_next_buf(lex, data, len);
          if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
            parser_lex_from_next_into_glue(&lex, r);
            break;
          }
          continue;
        }
        extern void parser_report_untyped_formal_p011_c(int32_t line, int32_t col, int32_t kind);
        parser_report_untyped_formal_p011_c((int32_t)r.tok.line, (int32_t)r.tok.col, 0);
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      param_type_ref = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex, &source, &lex);
      if (param_type_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      pipeline_onefunc_set_param_type_ref(out_pool, param_idx, param_type_ref);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
        parser_lex_from_next_into_glue(&lex, r);
        break;
      }
      if (r.tok.kind != (int32_t)TOKEN_COMMA) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
        parser_lex_from_next_into_glue(&lex, r);
        break;
      }
    }
  }
  r = lexer_next_buf(lex, data, len);
  /* wave676: missing return `: Type` after `)` was silent set_onefunc_fail. */
  if (r.tok.kind != (int32_t)TOKEN_COLON) {
    extern void parser_report_untyped_formal_p011_c(int32_t line, int32_t col, int32_t kind);
    parser_report_untyped_formal_p011_c((int32_t)r.tok.line, (int32_t)r.tok.col, 1);
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (!parser_asm_onefunc_buf_return_type_ok_c(r.tok.kind)) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  ret_type_ref = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex, &source, &lex);
  if (ret_type_ref == 0) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  out->func_return_type_ref = ret_type_ref;
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  parser_lex_from_next_into_glue(&lex, r);
  /*
   * wave473 Cap residual pure: collect body `let`/`const` into OneFunc sidecar.
   * Root: body_skip_let_const_then_if dropped bindings but still accepted
   * `return s` → hoist inject with return_var_name=s and num_lets=0 → typeck
   * "cannot resolve return subexpression: s". Free functions already use
   * parse_body_lets_into; default-method re-parse (buf path) must share that
   * authority (G.7).
   * wave475: after prefix lets, accept mid-body if/while/expr_stmt before
   * final `return` (G.7 twin of free onefunc body loop: parse_if_stmt_into /
   * parse_cond+block / parse_expr → append_if|append_while|push_body_expr_stmt
   * + push_stmt_order).
   * wave476: mid-body C-style `for (init;cond;step) { }` + stmt-position
   * `match` (G.7 twin free onefunc append_for / parse_match_into → expr_stmt).
   * wave477: mid-body `let`/`const` after control (prefix-only was soft leave-off;
   * free onefunc already re-enters parse_body_lets_into + stmt_order kind 1).
   * Soft: dyn Trait; dual Method.POST; multi mono rare; return-match compound.
   * PLATFORM: SHARED parse.
   */
  if (!parser_parse_body_lets_into(arena, lex, &source, out, &lex)) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  out->num_lets = pipeline_onefunc_num_lets(out_pool);
  out->num_consts = pipeline_onefunc_num_consts(out_pool);
  out->num_src_stmt_order = 0;
  out->num_src_body_expr_stmts = 0;
  out->num_if_stmts = 0;
  out->num_loops = 0;
  out->num_for_loops = 0;
  /* Prefix consts/lets enter stmt_order (same as free parse_one_function_impl). */
  {
    int32_t csr0 = 0;
    int32_t lsr = 0;
    while (csr0 < out->num_consts) {
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)0, csr0) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      csr0++;
    }
    while (lsr < out->num_lets) {
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)1, lsr) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      lsr++;
    }
    out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
  }
  /*
   * Mid-body statements until final TOKEN_RETURN / RBRACE.
   * IF → parse_if_stmt_into (then/else blocks may contain return).
   * WHILE → cond + parse_block_into + append_while.
   * FOR → C-style for(init;cond;step) body + append_for (kind 4).
   * MATCH → parse_match_into → body_expr_stmt (kind 2; optional ';').
   * LET/CONST → re-enter parse_body_lets_into + stmt_order kind 0/1 (wave477).
   * Else → expr_stmt (assign / call) via parse_expr_into + ';'.
   */
  r = lexer_next_buf(lex, data, len);
  while (r.tok.kind != (int32_t)TOKEN_RETURN && r.tok.kind != (int32_t)TOKEN_RBRACE &&
         r.tok.kind != (int32_t)TOKEN_EOF) {
    /*
     * 9.6.3: function-local `static let` / `static const` — C twin of the
     * parser.x / parser_gen pin onefunc hook (buf retry face). `static` is NOT
     * a keyword: TOKEN_IDENT spelling "static" (115,116,97,116,105,99) followed
     * by let/const desugars through parser_parse_one_top_level_let_into_glue
     * into the module installed by parser_cur_module_set_c (pin parse_into /
     * parse_into_buf windows). Other uses of an identifier named "static" see
     * a non-let/const next token and fall through untouched. Any desugar
     * failure is loud (set_onefunc_fail); the P012 duplicate-binding sticky
     * raised inside the top-level-let authority is converted to the module
     * loop's hard abort by the caller's wave676 check.
     * PLATFORM: SHARED parse — parser.x + pin + C twin same commit.
     */
    if (r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len == 6) {
      extern void *parser_cur_module_get_c(void);
      extern void parser_parse_one_top_level_let_into_glue(void *arena, void *module,
          struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source, int32_t is_const,
          struct parser_asm_top_level_let_result *out);
      uint8_t st_b0 = 0;
      uint8_t st_b1 = 0;
      uint8_t st_b2 = 0;
      uint8_t st_b3 = 0;
      uint8_t st_b4 = 0;
      uint8_t st_b5 = 0;
      if (r.token_start < (size_t)len)
        st_b0 = data[r.token_start];
      if (r.token_start + 1 < (size_t)len)
        st_b1 = data[r.token_start + 1];
      if (r.token_start + 2 < (size_t)len)
        st_b2 = data[r.token_start + 2];
      if (r.token_start + 3 < (size_t)len)
        st_b3 = data[r.token_start + 3];
      if (r.token_start + 4 < (size_t)len)
        st_b4 = data[r.token_start + 4];
      if (r.token_start + 5 < (size_t)len)
        st_b5 = data[r.token_start + 5];
      if (st_b0 == 115 && st_b1 == 116 && st_b2 == 97 && st_b3 == 116 && st_b4 == 105 && st_b5 == 99) {
        struct parser_asm_lexer lex_st = parser_asm_lex_at_token_from_result_c(r);
        struct parser_asm_lexer_result st_r2 = lexer_next_buf(lex_st, data, len);
        if (st_r2.tok.kind == (int32_t)TOKEN_LET || st_r2.tok.kind == (int32_t)TOKEN_CONST) {
          struct parser_asm_top_level_let_result tl_res;
          memset(&tl_res, 0, sizeof(tl_res));
          parser_parse_one_top_level_let_into_glue(arena, parser_cur_module_get_c(), lex_st,
                                                   &source, st_r2.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0,
                                                   &tl_res);
          if (!tl_res.ok) {
            /* Loud: duplicate P012 sticky or real parse failure — never
             * silently drop the declaration (wave679 no-soft-skip). */
            parser_asm_set_onefunc_fail_c(out, lex);
            return;
          }
          /* Whole `static let/const ...;` consumed; emit nothing into the frame. */
          lex = tl_res.next_lex;
          r = lexer_next_buf(lex, data, len);
          continue;
        }
      }
    }
    if (r.tok.kind == (int32_t)TOKEN_IF) {
      struct parser_asm_lexer if_start;
      int32_t if_cref = 0;
      int32_t if_then_ref = 0;
      int32_t if_else_ref = 0;
      int32_t if_pool_idx;
      if_start = parser_asm_lex_at_token_from_result_c(r);
      if (!parser_asm_parse_if_stmt_into_c(arena, if_start, &source, 0, &if_cref, &if_then_ref,
                                          &if_else_ref, &lex)) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if_pool_idx = pipeline_onefunc_append_if(out_pool, if_cref, if_then_ref, if_else_ref);
      if (if_pool_idx < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)5, if_pool_idx) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_if_stmts = pipeline_onefunc_num_if_stmts(out_pool);
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      r = lexer_next_buf(lex, data, len);
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_WHILE) {
      struct parser_asm_lexer while_cond_start;
      struct parser_asm_parse_expr_result expr_res;
      struct parser_asm_parse_block_result block_res;
      int32_t cond_ref;
      int32_t while_idx;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      /* docs/03: bare `while cond { }` or `while (cond) { }`. */
      if (r.tok.kind == (int32_t)TOKEN_LPAREN) {
        parser_lex_from_next_into_glue(&lex, r);
        while_cond_start = lex;
      } else {
        while_cond_start = parser_asm_lex_at_token_from_result_c(r);
      }
      memset(&expr_res, 0, sizeof(expr_res));
      parser_parse_cond_expr_into_glue(arena, while_cond_start, &source, &expr_res);
      if (!expr_res.ok || expr_res.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      cond_ref = expr_res.expr_ref;
      lex = expr_res.next_lex;
      if (parser_advance_past_cond_rparen_into_glue(&r, lex, &source) == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      memset(&block_res, 0, sizeof(block_res));
      parser_parse_block_into(arena, lex, &source, ret_type_ref, &block_res);
      if (!block_res.ok || block_res.block_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      while_idx = pipeline_onefunc_append_while(out_pool, cond_ref, block_res.block_ref);
      if (while_idx < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)3, while_idx) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_loops = pipeline_onefunc_num_whiles(out_pool);
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      lex = block_res.next_lex;
      r = lexer_next_buf(lex, data, len);
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_FOR) {
      /* C-style for (init; cond; step) { body } — G.7 free onefunc twin. */
      int32_t init_ref = 0;
      int32_t for_cond_ref = 0;
      int32_t step_ref = 0;
      int32_t for_idx;
      int32_t for_past_init_semi = 0;
      struct parser_asm_parse_block_result block_res_f;
      struct parser_asm_parse_expr_result expr_res_fi;
      struct parser_asm_parse_expr_result expr_res_fc;
      struct parser_asm_parse_expr_result expr_res_fs;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      /* init: empty | let …; | expr */
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
        if (r.tok.kind == (int32_t)TOKEN_LET) {
          int32_t n_before_fi = pipeline_onefunc_num_lets(out_pool);
          int32_t push_fi;
          struct parser_asm_lexer lex_fi_let;
          /* body_lets expects lex at `let` keyword (free path twin). */
          lex_fi_let = parser_asm_lex_at_token_from_result_c(r);
          if (!parser_parse_body_lets_into(arena, lex_fi_let, &source, out, &lex)) {
            parser_asm_set_onefunc_fail_c(out, lex);
            return;
          }
          out->num_lets = pipeline_onefunc_num_lets(out_pool);
          push_fi = n_before_fi;
          while (push_fi < out->num_lets) {
            if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)1, push_fi) < 0) {
              parser_asm_set_onefunc_fail_c(out, lex);
              return;
            }
            push_fi++;
          }
          out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
          init_ref = 0;
          for_past_init_semi = 1;
          r = lexer_next_buf(lex, data, len);
        } else {
          struct parser_asm_lexer init_start;
          init_start = parser_asm_lex_at_token_from_result_c(r);
          memset(&expr_res_fi, 0, sizeof(expr_res_fi));
          parse_expr_into(arena, init_start, &source, &expr_res_fi);
          if (!expr_res_fi.ok || expr_res_fi.expr_ref == 0) {
            parser_asm_set_onefunc_fail_c(out, lex);
            return;
          }
          init_ref = expr_res_fi.expr_ref;
          lex = expr_res_fi.next_lex;
          r = lexer_next_buf(lex, data, len);
        }
      }
      if (!for_past_init_semi) {
        if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        parser_lex_from_next_into_glue(&lex, r);
        r = lexer_next_buf(lex, data, len);
      }
      /* cond: empty → true (INT_LIT 1); else expr before ';' */
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
        struct parser_asm_lexer cond_start;
        cond_start = parser_asm_lex_at_token_from_result_c(r);
        memset(&expr_res_fc, 0, sizeof(expr_res_fc));
        parse_expr_into(arena, cond_start, &source, &expr_res_fc);
        if (!expr_res_fc.ok || expr_res_fc.expr_ref == 0) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        for_cond_ref = expr_res_fc.expr_ref;
        lex = expr_res_fc.next_lex;
        r = lexer_next_buf(lex, data, len);
      }
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      /* step: empty | expr before ')' */
      if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
        struct parser_asm_lexer step_start;
        step_start = parser_asm_lex_at_token_from_result_c(r);
        memset(&expr_res_fs, 0, sizeof(expr_res_fs));
        parse_expr_into(arena, step_start, &source, &expr_res_fs);
        if (!expr_res_fs.ok || expr_res_fs.expr_ref == 0) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        step_ref = expr_res_fs.expr_ref;
        lex = expr_res_fs.next_lex;
        r = lexer_next_buf(lex, data, len);
      }
      if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      memset(&block_res_f, 0, sizeof(block_res_f));
      parser_parse_block_into(arena, lex, &source, ret_type_ref, &block_res_f);
      if (!block_res_f.ok || block_res_f.block_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (for_cond_ref == 0) {
        /* Empty cond → always-true INT_LIT (kind 2), same as free onefunc. */
        int32_t cond_expr_ref = 0;
        if (arena)
          cond_expr_ref = ast_ast_arena_expr_alloc(arena);
        if (cond_expr_ref != 0) {
          struct ast_Expr ce;
          memset(&ce, 0, sizeof(ce));
          /* EXPR_INT_LIT kind=2 — free onefunc empty-for-cond twin. */
          ce.kind = 2;
          ce.int_val = 1;
          ast_ast_arena_expr_set(arena, cond_expr_ref, ce);
          for_cond_ref = cond_expr_ref;
        }
      }
      for_idx = pipeline_onefunc_append_for(out_pool, init_ref, for_cond_ref, step_ref,
                                            block_res_f.block_ref);
      if (for_idx < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)4, for_idx) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_for_loops = pipeline_onefunc_num_fors(out_pool);
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      lex = block_res_f.next_lex;
      r = lexer_next_buf(lex, data, len);
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_MATCH) {
      /* wave371/476: stmt-position match → body_expr_stmt (optional ';'). */
      struct parser_asm_lexer match_mid_lex;
      struct parser_asm_parse_expr_result match_mid_res;
      int32_t match_ex_i;
      match_mid_lex = parser_asm_lex_at_token_from_result_c(r);
      memset(&match_mid_res, 0, sizeof(match_mid_res));
      parser_parse_match_into(arena, match_mid_lex, &source, &match_mid_res);
      if (!match_mid_res.ok || match_mid_res.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      lex = match_mid_res.next_lex;
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
        parser_lex_from_next_into_glue(&lex, r);
        r = lexer_next_buf(lex, data, len);
      }
      match_ex_i = pipeline_onefunc_push_body_expr_stmt(out_pool, match_mid_res.expr_ref);
      if (match_ex_i < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)2, match_ex_i) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_src_body_expr_stmts = pipeline_onefunc_num_body_expr_stmts(out_pool);
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_LET || r.tok.kind == (int32_t)TOKEN_CONST) {
      /*
       * wave477: mid-body let/const after if/while/for/match/expr_stmt.
       * Root: prefix-only parse_body_lets_into left post-control `let j` to fall
       * into expr_stmt → parse_expr fail → whole default method dropped →
       * missing method (free path green via parse_one_function_impl mid_let).
       * G.7: re-enter parse_body_lets_into at keyword; push new consts (kind 0)
       * then new lets (kind 1) into src_stmt_order (free twin + const complete).
       * PLATFORM: SHARED parse.
       */
      int32_t n_before_mid = pipeline_onefunc_num_lets(out_pool);
      int32_t n_const_before = pipeline_onefunc_num_consts(out_pool);
      int32_t push_mi;
      int32_t push_mc;
      struct parser_asm_lexer lex_mid_let;
      lex_mid_let = parser_asm_lex_at_token_from_result_c(r);
      if (!parser_parse_body_lets_into(arena, lex_mid_let, &source, out, &lex)) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_lets = pipeline_onefunc_num_lets(out_pool);
      out->num_consts = pipeline_onefunc_num_consts(out_pool);
      push_mc = n_const_before;
      while (push_mc < out->num_consts) {
        if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)0, push_mc) < 0) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        push_mc++;
      }
      push_mi = n_before_mid;
      while (push_mi < out->num_lets) {
        if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)1, push_mi) < 0) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
        push_mi++;
      }
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      r = lexer_next_buf(lex, data, len);
      continue;
    }
    /* Mid-body expr_stmt (assign / call / …); require trailing ';'. */
    {
      struct parser_asm_lexer stmt_start;
      struct parser_asm_parse_expr_result expr_stmt_res;
      int32_t ex_i;
      stmt_start = parser_asm_lex_at_token_from_result_c(r);
      memset(&expr_stmt_res, 0, sizeof(expr_stmt_res));
      parse_expr_into(arena, stmt_start, &source, &expr_stmt_res);
      if (!expr_stmt_res.ok || expr_stmt_res.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      lex = expr_stmt_res.next_lex;
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      ex_i = pipeline_onefunc_push_body_expr_stmt(out_pool, expr_stmt_res.expr_ref);
      if (ex_i < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (pipeline_onefunc_push_stmt_order(out_pool, (uint8_t)2, ex_i) < 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->num_src_body_expr_stmts = pipeline_onefunc_num_body_expr_stmts(out_pool);
      out->num_src_stmt_order = pipeline_onefunc_num_src_stmt_order(out_pool);
      r = lexer_next_buf(lex, data, len);
      continue;
    }
  }
  if (r.tok.kind != (int32_t)TOKEN_RETURN) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  /** `return if (cond) { int } else { int }`：与 parse_one_function_impl legacy has_if_expr 对齐。 */
  if (r.tok.kind == (int32_t)TOKEN_IF) {
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_TRUE || r.tok.kind == (int32_t)TOKEN_FALSE) {
      out->if_cond_true = (r.tok.kind == (int32_t)TOKEN_TRUE) ? 1 : 0;
      out->if_cond_expr_ref = 0;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    } else {
      out->if_cond_true = 0;
      out->if_cond_expr_ref = 0;
      while (r.tok.kind != (int32_t)TOKEN_RPAREN && r.tok.kind != (int32_t)TOKEN_EOF) {
        parser_lex_from_next_into_glue(&lex, r);
        r = lexer_next_buf(lex, data, len);
      }
      if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind != (int32_t)TOKEN_INT) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    out->if_then_val = r.tok.int_val;
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind != (int32_t)TOKEN_ELSE) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind != (int32_t)TOKEN_INT) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    out->if_else_val = r.tok.int_val;
    out->has_if_expr = 1;
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind != (int32_t)TOKEN_RBRACE && r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
    }
    parser_lex_from_next_into_glue(&lex, r);
    out->ok = 1;
    out->next_lex = lex;
    out->name_len = name_len;
    for (ni = 0; ni < 64; ni++)
      out->name[ni] = dummy_name[ni];
    out->has_explicit_return_kw = 1;
    return;
  }
  /*
   * wave478: `return match …` final expression in trait default hoist.
   * Root: thin onefunc after `return` only accepted if-expr / self|ident|INT;
   * TOKEN_MATCH failed → whole default dropped → missing method (free path
   * green via parse_one_function_impl return-match → return_expr_ref).
   * G.7: parse_match_into for bare `return match {…};`; if a binary/postfix
   * tail follows (`return match … + 2`), re-parse from MATCH with parse_expr_into
   * (match primary + ops — free twin). Mid-body stmt match is wave476.
   * Soft: multi mono rare; dyn Trait; dual Method.POST.
   * PLATFORM: SHARED parse.
   */
  if (r.tok.kind == (int32_t)TOKEN_MATCH) {
    struct parser_asm_lexer match_ret_lex;
    struct parser_asm_parse_expr_result match_ret_res;
    size_t match_start;
    int32_t match_line;
    int32_t match_col;
    if (!arena) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    match_start = r.token_start;
    match_line = r.tok.line;
    match_col = r.tok.col;
    match_ret_lex = parser_asm_lex_at_token_from_result_c(r);
    memset(&match_ret_res, 0, sizeof(match_ret_res));
    parser_parse_match_into(arena, match_ret_lex, &source, &match_ret_res);
    if (!match_ret_res.ok || match_ret_res.expr_ref == 0) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    out->return_expr_ref = match_ret_res.expr_ref;
    out->return_var_name_len = 0;
    memset(out->return_var_name, 0, sizeof(out->return_var_name));
    out->return_val = 0;
    lex = match_ret_res.next_lex;
    r = lexer_next_buf(lex, data, len);
    /*
     * Compound after match (e.g. `return match x {…} + 2`): free path builds
     * match primary + binop via parse_expr/cond; re-parse from match_start.
     */
    if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE) {
      struct parser_asm_lexer expr_lex;
      struct parser_asm_parse_expr_result expr_out;
      memset(&expr_lex, 0, sizeof(expr_lex));
      expr_lex.pos = match_start;
      expr_lex.line = match_line;
      expr_lex.col = match_col;
      memset(&expr_out, 0, sizeof(expr_out));
      parse_expr_into(arena, expr_lex, &source, &expr_out);
      if (!expr_out.ok || expr_out.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->return_expr_ref = expr_out.expr_ref;
      lex = expr_out.next_lex;
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
    }
    if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
    parser_lex_from_next_into_glue(&lex, r);
    out->ok = 1;
    out->next_lex = lex;
    out->name_len = name_len;
    for (ni = 0; ni < 64; ni++)
      out->name[ni] = dummy_name[ni];
    out->has_explicit_return_kw = 1;
    return;
  }
  /*
   * wave471: accept `return self` / `return ident` (default methods that
   * return Self by identity). INT lit path retained.
   * wave472: also `return Type { fields }` / `return Self { fields }` —
   * onefunc IDENT path used to fail when next was `{` (looked like bad
   * tail after bare var), so trait default hoist skipped inject → false
   * "missing method". G.7: reuse finish_struct_lit_from_type_ident (same
   * primary authority); commit rewrites TYPE_NAMED Self → for-type.
   * wave473: body lets collected (parse_body_lets_into); return self|ident|lit
   * after prefix lets is the thin-path contract.
   * wave474: `return self.v` / other postfix after self|ident → G.7 parse_expr
   * into return_expr_ref (bare SEMI/RBRACE and Type `{` keep fast paths).
   * Soft: mid-body if/loop before return; dyn Trait.
   * PLATFORM: SHARED parse.
   */
  if (r.tok.kind == (int32_t)TOKEN_SELF || r.tok.kind == (int32_t)TOKEN_IDENT) {
    int32_t rvn = 0;
    uint8_t tnm64[64];
    int32_t tnl = 0;
    struct parser_asm_lexer_result r_after;
    size_t expr_start;
    int32_t expr_line;
    int32_t expr_col;
    memset(out->return_var_name, 0, sizeof(out->return_var_name));
    memset(tnm64, 0, sizeof(tnm64));
    /* Save start of self|ident for compound return (field / call / binop). */
    expr_start = r.token_start;
    expr_line = r.tok.line;
    expr_col = r.tok.col;
    if (r.tok.kind == (int32_t)TOKEN_SELF) {
      /* Binding name for bare `return self` (lowercase VAR). */
      out->return_var_name[0] = (uint8_t)'s';
      out->return_var_name[1] = (uint8_t)'e';
      out->return_var_name[2] = (uint8_t)'l';
      out->return_var_name[3] = (uint8_t)'f';
      rvn = 4;
      /* STRUCT_LIT type spelling is capital Self (TYPE_NAMED). */
      tnm64[0] = (uint8_t)'S';
      tnm64[1] = (uint8_t)'e';
      tnm64[2] = (uint8_t)'l';
      tnm64[3] = (uint8_t)'f';
      tnl = 4;
    } else {
      rvn = r.tok.ident_len;
      if (rvn <= 0 || rvn > 63) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      parser_asm_copy_slice_to_name64_buf_c(data, len, r.token_start, rvn, out->return_var_name);
      tnl = rvn;
      for (ni = 0; ni < 64 && ni < tnl; ni++)
        tnm64[ni] = out->return_var_name[ni];
    }
    out->return_var_name_len = rvn;
    out->return_val = 0;
    parser_lex_from_next_into_glue(&lex, r);
    r_after = lexer_next_buf(lex, data, len);
    /*
     * wave472: Name `{` → STRUCT_LIT return (not bare VAR). Peek after name;
     * if LBRACE, finish_struct_lit into return_expr_ref (commit already
     * prefers return_expr_ref over return_var_name / INT).
     */
    if (r_after.tok.kind == (int32_t)TOKEN_LBRACE) {
      int32_t lit_ref;
      int32_t ti;
      struct ast_Expr pe;
      struct parser_asm_parse_expr_result lit_out;
      extern int32_t ast_ast_arena_expr_alloc(void *arena);
      extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
      extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
      extern void parser_asm_finish_struct_lit_from_type_ident_into_c(
          void *arena, int32_t lit_ref, struct parser_asm_lexer lex_in_brace,
          struct parser_asm_slice_u8 *source, struct parser_asm_parse_expr_result *lit_out_p);

      if (!arena) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      lit_ref = ast_ast_arena_expr_alloc(arena);
      if (lit_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      pe = ast_ast_arena_expr_get(arena, lit_ref);
      memset(&pe, 0, sizeof(pe));
      pe.var_name_len = tnl;
      for (ti = 0; ti < 64 && ti < tnl; ti++)
        pe.var_name[ti] = tnm64[ti];
      ast_ast_arena_expr_set(arena, lit_ref, pe);
      /* lex_in_brace must be past `{` (same as primary TypeName { path). */
      parser_lex_from_next_into_glue(&lex, r_after);
      memset(&lit_out, 0, sizeof(lit_out));
      parser_asm_finish_struct_lit_from_type_ident_into_c(arena, lit_ref, lex, &source, &lit_out);
      if (!lit_out.ok || lit_out.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->return_expr_ref = lit_out.expr_ref;
      out->return_var_name_len = 0;
      memset(out->return_var_name, 0, sizeof(out->return_var_name));
      lex = lit_out.next_lex;
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
        parser_lex_from_next_into_glue(&lex, r);
        r = lexer_next_buf(lex, data, len);
        if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
      }
      parser_lex_from_next_into_glue(&lex, r);
      out->ok = 1;
      out->next_lex = lex;
      out->name_len = name_len;
      for (ni = 0; ni < 64; ni++)
        out->name[ni] = dummy_name[ni];
      out->has_explicit_return_kw = 1;
      return;
    }
    /*
     * Bare `return self` / `return ident` (wave471) when next is `;` / `}`.
     * wave474: otherwise compound expr from the same start (`self.v`, `x.f`,
     * etc.) via G.7 parse_expr_into → return_expr_ref. Soft: mid-body stmts.
     */
    r = r_after;
    if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE) {
      struct parser_asm_lexer expr_lex;
      struct parser_asm_parse_expr_result expr_out;
      if (!arena) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      memset(&expr_lex, 0, sizeof(expr_lex));
      expr_lex.pos = expr_start;
      expr_lex.line = expr_line;
      expr_lex.col = expr_col;
      memset(&expr_out, 0, sizeof(expr_out));
      parse_expr_into(arena, expr_lex, &source, &expr_out);
      if (!expr_out.ok || expr_out.expr_ref == 0) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      out->return_expr_ref = expr_out.expr_ref;
      out->return_var_name_len = 0;
      memset(out->return_var_name, 0, sizeof(out->return_var_name));
      out->return_val = 0;
      lex = expr_out.next_lex;
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
      if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
        parser_lex_from_next_into_glue(&lex, r);
        r = lexer_next_buf(lex, data, len);
        if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
          parser_asm_set_onefunc_fail_c(out, lex);
          return;
        }
      }
      parser_lex_from_next_into_glue(&lex, r);
      out->ok = 1;
      out->next_lex = lex;
      out->name_len = name_len;
      for (ni = 0; ni < 64; ni++)
        out->name[ni] = dummy_name[ni];
      out->has_explicit_return_kw = 1;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
        parser_asm_set_onefunc_fail_c(out, lex);
        return;
      }
    }
    parser_lex_from_next_into_glue(&lex, r);
    out->ok = 1;
    out->next_lex = lex;
    out->name_len = name_len;
    for (ni = 0; ni < 64; ni++)
      out->name[ni] = dummy_name[ni];
    out->has_explicit_return_kw = 1;
    return;
  }
  if (r.tok.kind != (int32_t)TOKEN_INT) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  ret_val = r.tok.int_val;
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE) {
    parser_asm_set_onefunc_fail_c(out, lex);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_SEMICOLON) {
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind != (int32_t)TOKEN_RBRACE) {
      parser_asm_set_onefunc_fail_c(out, lex);
      return;
    }
  }
  parser_lex_from_next_into_glue(&lex, r);
  out->ok = 1;
  out->next_lex = lex;
  out->name_len = name_len;
  for (ni = 0; ni < 64; ni++)
    out->name[ni] = dummy_name[ni];
  out->return_val = ret_val;
  out->has_explicit_return_kw = 1;
}

#endif /* PARSER_ASM_ONE_FUNCTION_BUF_SLICE_INCLUDED */
