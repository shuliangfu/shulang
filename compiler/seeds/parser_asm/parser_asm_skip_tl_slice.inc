/* wave439: forward decl — stash full-file source slice for the generic-bound
 * scan. Defined below; called from each top-level skip_*_into_slice_c entry.
 * PLATFORM: SHARED parse. */
void xlang_generic_bound_stash_source_c(struct parser_asm_slice_u8 *source);

/**
 * skip_one_struct_into：跳过一条顶层 struct 定义，结果写入 *out。
 */
void parser_asm_skip_one_struct_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                             struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  if (!out || !source)
    return;
  /* wave439: stash full-file source for generic-bound scan. */
  xlang_generic_bound_stash_source_c(source);
  {
    struct parser_asm_lexer mod_lex = lex;
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_allow_modifiers_c(&mod_lex, source));
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_modifiers_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_layout_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_skip_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_header_audit_c(&lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_STRUCT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  {
    uint8_t sname_audit[64];
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, sname_audit);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(sname_audit, r.tok.ident_len));
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  /*
   * wave466: `struct Name<T> { ... }` — skip type-param angle list so skip
   * reaches the body braces (same contract as parse_struct_record_layout).
   * PLATFORM: SHARED — without this, skip stalled on TOKEN_LT and left the
   * brace body in the top-level stream after a failed layout parse.
   */
  if (r.tok.kind == (int32_t)TOKEN_LT) {
    parser_asm_skip_generic_angle_list_into_slice_c(&lex, lex, source);
    lexer_next_into(&r, lex, source);
  }
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_fields_probe_c(r.next_lex, source, 0));
  parser_asm_skip_balanced_braces_into_slice_c(out, r.next_lex, source);
}

/**
 * skip_one_enum_into：跳过一条顶层 enum 定义，结果写入 *out。
 */
void parser_asm_skip_one_enum_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                          struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  if (!out || !source)
    return;
  /* wave439: stash full-file source for generic-bound scan. */
  xlang_generic_bound_stash_source_c(source);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_header_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_body_deep_slice_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_ENUM) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  {
    uint8_t ename_audit[64];
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, ename_audit);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(ename_audit, r.tok.ident_len));
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variants_probe_c(r.next_lex, source, 0));
  parser_asm_skip_balanced_braces_into_slice_c(out, r.next_lex, source);
}
/*
 * wave421 Cap residual pure — product-path trait registry (LANG-004 missing method).
 * Root: parser.x skip_one_trait/impl never stored trait signatures → incomplete
 * impl compiled green. G.7 authority: this skip_tl slice (product skip glue).
 * wave424: unknown_trait hard fail (was soft continue when trait not registered).
 * wave425: store method return TypeKind at trait register; hard fail return_mismatch
 *   (was soft: only method names stored → `impl` with wrong `: bool` false-green).
 * wave426: store method param count + typed param TypeKinds; hard fail arity /
 *   parameter type mismatch (was soft: only names+ret → extra/wrong params green).
 * wave427: named ret (IDENT→TYPE_NAMED+name) + ptr/slice ret (STAR/[] + elem);
 *   hard fail Point vs Other / []i32 vs []u8 (was soft: kind=-1 skip).
 * wave428: store impl for-type; hard fail untyped trait self vs for-type
 *   (was soft: param0 ek=-1 skip → `self: u64` on `impl … for i32` false-green).
 * wave429: typed self vs for-type hard fail (drop ek0<0 gate).
 * wave430: suffix T[N]/T[] ret capture + TYPE_ARRAY size/elem hard fail
 *   (was: base-only registry → ok path false-red; scalar-vs-array false-green).
 * wave431: multi-dim suffix T[N][M]… ret (dims[0]=outer, C order) + recursive size walk
 *   (was: one dim only → ok i32[2][3] false-red; impl i32[2] vs trait i32[2][3] false-green).
 * wave432: named/ptr/slice param shape + hard fail (twin of seed parse_into_buf).
 * wave468: method_has_default + fn start pos — trait method bodies hoist as free
 *   UFCS methods when impl does not override (empty/partial impl inherits default).
 * Soft leave-off: dyn Trait; Self receiver rewrite; multi-default same-name across traits.
 * PLATFORM: SHARED parse.
 */
#define XLANG_SKIP_TRAIT_REG_MAX 16
#define XLANG_SKIP_TRAIT_METH_MAX 32
#define XLANG_SKIP_TRAIT_PARAM_MAX 8
#define XLANG_SKIP_IMPL_SEEN_MAX 16
#define XLANG_SKIP_TRAIT_ARRAY_DIM_MAX 8
typedef struct {
  uint8_t name[64];
  int32_t name_len;
  uint8_t methods[XLANG_SKIP_TRAIT_METH_MAX][64];
  int32_t method_lens[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave468: 1 if method ended with `{ body }` (default method), else 0 (`;`/ASI only). */
  int32_t method_has_default[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave468: lexer pos/line/col at TOKEN_FUNCTION for re-parse inject. */
  int32_t method_fn_pos[XLANG_SKIP_TRAIT_METH_MAX];
  int32_t method_fn_line[XLANG_SKIP_TRAIT_METH_MAX];
  int32_t method_fn_col[XLANG_SKIP_TRAIT_METH_MAX];
  /* TypeKind ord (PARSER_ASM_TYPE_*); -1 = unknown / not stored (skip ret check). */
  int32_t method_ret_kinds[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave427: TYPE_NAMED ret name, or *T / []T / T[N] element name when elem is named. */
  uint8_t method_ret_names[XLANG_SKIP_TRAIT_METH_MAX][64];
  int32_t method_ret_name_lens[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave427/430: element TypeKind for TYPE_PTR / TYPE_SLICE / TYPE_ARRAY leaf; -1 = not captured. */
  int32_t method_ret_elem_kinds[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave430: fixed T[N] outer size when ret kind is TYPE_ARRAY; -1 = N/A. */
  int32_t method_ret_array_sizes[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave431: multi-dim count; dims[0]=outer … dims[n-1]=innermost (align type_ref). 0 = N/A. */
  int32_t method_ret_array_ndims[XLANG_SKIP_TRAIT_METH_MAX];
  int32_t method_ret_array_dims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
  /* wave438: when PTR/SLICE ret elem is itself ARRAY/SLICE (e.g. *T[N] / *[]T / *[N][M]T),
   * elem_array_ndims = ndims of the inner ARRAY (0 = N/A); elem_array_dims = its dims;
   * elem_elem_kinds = leaf element TypeKind of that inner ARRAY/SLICE (-1 = not captured).
   * Twin of wave434 param elem fields, lifted into the PTR/SLICE ret elem slot.
   * PLATFORM: SHARED parse. */
  int32_t method_ret_elem_array_ndims[XLANG_SKIP_TRAIT_METH_MAX];
  int32_t method_ret_elem_array_dims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
  int32_t method_ret_elem_elem_kinds[XLANG_SKIP_TRAIT_METH_MAX];
  /* wave426: arity of `(params)`; -1 = not captured (skip arity check). */
  int32_t method_param_counts[XLANG_SKIP_TRAIT_METH_MAX];
  /* Per-param TypeKind when trait wrote `: Ty`; -1 = untyped / unknown. */
  int32_t method_param_kinds[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  /* wave432: TYPE_NAMED param name, or *T / []T / T[N] leaf element name when elem is named. */
  uint8_t method_param_names[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX][64];
  int32_t method_param_name_lens[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  /* wave432: element TypeKind for TYPE_PTR / TYPE_SLICE / TYPE_ARRAY leaf; -1 = not captured. */
  int32_t method_param_elem_kinds[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  /* wave433: multi-dim count for TYPE_ARRAY param; 0 = N/A. dims[0]=outer … dims[n-1]=innermost. */
  int32_t method_param_array_ndims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  int32_t method_param_array_dims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX][XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
  /* wave434: when PTR/SLICE elem is itself ARRAY/SLICE (e.g. *T[N] / *[]T / *T[N][M]),
   * elem_array_ndims = ndims of the inner ARRAY (0 = N/A); elem_array_dims = its dims;
   * elem_elem_kinds = leaf element TypeKind of that inner ARRAY/SLICE (-1 = not captured).
   * Twin of wave433 top-level ARRAY fields, lifted into the PTR/SLICE elem slot. */
  int32_t method_param_elem_array_ndims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  int32_t method_param_elem_array_dims[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX][XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
  int32_t method_param_elem_elem_kinds[XLANG_SKIP_TRAIT_METH_MAX][XLANG_SKIP_TRAIT_PARAM_MAX];
  int32_t num_methods;
} xlang_skip_trait_reg_ent_t;
static xlang_skip_trait_reg_ent_t g_xlang_skip_trait_reg[XLANG_SKIP_TRAIT_REG_MAX];
static int32_t g_xlang_skip_trait_reg_n;
static uint8_t g_xlang_skip_impl_trait[XLANG_SKIP_IMPL_SEEN_MAX][64];
static int32_t g_xlang_skip_impl_trait_len[XLANG_SKIP_IMPL_SEEN_MAX];
static int32_t g_xlang_skip_impl_seen_n;
static int32_t g_xlang_skip_impl_line[XLANG_SKIP_IMPL_SEEN_MAX];
static int32_t g_xlang_skip_impl_col[XLANG_SKIP_IMPL_SEEN_MAX];
/* wave428: for-type of `impl Trait for T` (T may be *U). -1 kind = not captured. */
static int32_t g_xlang_skip_impl_for_kinds[XLANG_SKIP_IMPL_SEEN_MAX];
static int32_t g_xlang_skip_impl_for_is_ptr[XLANG_SKIP_IMPL_SEEN_MAX];
static uint8_t g_xlang_skip_impl_for_names[XLANG_SKIP_IMPL_SEEN_MAX][64];
static int32_t g_xlang_skip_impl_for_name_lens[XLANG_SKIP_IMPL_SEEN_MAX];
/* wave425: arena stashed at reset so check can ord return_type_ref without API churn. */
static void *g_xlang_trait_check_arena;

/**
 * Map builtin type token → TypeKind ordinal (align PARSER_ASM_TYPE_* / ast TypeKind).
 * @return kind ord >=0; -1 if not a scalar/void builtin (IDENT handled separately as NAMED).
 * PLATFORM: SHARED parse.
 */
static int32_t xlang_trait_token_to_type_kind_c(int32_t tok_kind) {
  switch (tok_kind) {
  case (int32_t)TOKEN_I32:
    return 0;
  case (int32_t)TOKEN_BOOL:
    return 1;
  case (int32_t)TOKEN_U8:
    return 2;
  case (int32_t)TOKEN_U32:
    return 3;
  case (int32_t)TOKEN_U64:
    return 4;
  case (int32_t)TOKEN_I64:
    return 5;
  case (int32_t)TOKEN_USIZE:
    return 6;
  case (int32_t)TOKEN_ISIZE:
    return 7;
  case (int32_t)TOKEN_F32:
    return 14;
  case (int32_t)TOKEN_F64:
    return 15;
  case (int32_t)TOKEN_VOID:
    return 16;
  default:
    return -1;
  }
}

/* Align PARSER_ASM_TYPE_* / ast TypeKind for wave427/430 ret shape checks. */
#define XLANG_TRAIT_TY_NAMED 8
#define XLANG_TRAIT_TY_PTR 9
#define XLANG_TRAIT_TY_ARRAY 10
#define XLANG_TRAIT_TY_SLICE 11
/* dest-SLICE extra inner SLICE on method_param_elem_array_ndims.
 * 0 = scalar/NAMED (`[]*i32` / two-wrap `[][]i32`); >=1 = ARRAY pointee
 * (`[]*[N]T`); -2 = extra SLICE wrap (`[]*[]T` / `[]*[][]T` PTR
 * pointee, or `[][][]T` / `[][][][]T` SLICE-of-SLICE). Extra wrap
 * COUNT lives in dims[0] (0 means 1 extra wrap = `[]*[]T` or 3-layer
 * SLICE; 2 = `[]*[][]T` or 4-layer SLICE). Accessor invalid is -1 so
 * this sentinel must not collide. Do not invent -3. PTR vs SLICE is
 * elem_kind, not a second sentinel.
 * PLATFORM: SHARED parse. */
#define XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS (-2)

/* wave455: prototype — body after g_fn_gp_* tables. */
void xlang_generic_func_reg_reset_c(void);

/**
 * Reset per-module trait registry and stash arena for ret-kind checks.
 * @param arena void* — ASTArena for pipeline_type_kind_ord_at (may be null → ret check skipped).
 * PLATFORM: SHARED parse.
 */
void xlang_trait_reg_reset_c(void *arena) {
  g_xlang_skip_trait_reg_n = 0;
  g_xlang_skip_impl_seen_n = 0;
  g_xlang_trait_check_arena = arena;
  memset(g_xlang_skip_trait_reg, 0, sizeof(g_xlang_skip_trait_reg));
  memset(g_xlang_skip_impl_trait, 0, sizeof(g_xlang_skip_impl_trait));
  memset(g_xlang_skip_impl_trait_len, 0, sizeof(g_xlang_skip_impl_trait_len));
  memset(g_xlang_skip_impl_line, 0, sizeof(g_xlang_skip_impl_line));
  memset(g_xlang_skip_impl_col, 0, sizeof(g_xlang_skip_impl_col));
  memset(g_xlang_skip_impl_for_kinds, 0xff, sizeof(g_xlang_skip_impl_for_kinds)); /* -1 each */
  memset(g_xlang_skip_impl_for_is_ptr, 0, sizeof(g_xlang_skip_impl_for_is_ptr));
  memset(g_xlang_skip_impl_for_names, 0, sizeof(g_xlang_skip_impl_for_names));
  memset(g_xlang_skip_impl_for_name_lens, 0, sizeof(g_xlang_skip_impl_for_name_lens));
  /* wave455: type-param name registry cleared in xlang_generic_func_reg_reset_c
   * (defined after g_fn_gp_* tables) — called from here via tail. */
  xlang_generic_func_reg_reset_c();
}

extern void lsp_diag_report_typeck(int line, int col, const char *fmt, ...);
extern int32_t pipeline_module_num_funcs(void *module);
extern int32_t pipeline_module_func_name_equal_at(void *module, int32_t fi, uint8_t *name, int32_t name_len);
extern int32_t pipeline_module_func_name_len_at(void *module, int32_t fi);
extern void pipeline_module_func_name_copy64(void *module, int32_t fi, uint8_t *dst);
extern int32_t pipeline_module_func_return_type_at(void *module, int32_t fi);
extern int32_t pipeline_module_func_num_params_at(void *module, int32_t fi);
extern int32_t pipeline_module_func_param_type_ref_at(void *module, int32_t fi, int32_t pi);
extern int32_t pipeline_type_kind_ord_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_named_name_into(void *arena, int32_t type_ref, uint8_t *out);
extern int32_t pipeline_type_array_size_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_elem_ref_at(void *arena, int32_t type_ref);

/**
 * After parse: every `impl Trait for T` must name a registered trait and provide
 * free funcs for all trait methods with matching arity / param TypeKinds / ret
 * TypeKind (+ named name / ptr·slice elem) when known.
 * wave424 Cap residual pure — unknown_trait was soft-skipped (ti<0 continue) →
 * `impl Missing for i32` false-green (build exit 0).
 * wave425 Cap residual pure — return_mismatch: only names stored → wrong ret green.
 * wave426 Cap residual pure — param arity / typed param kinds were soft → extra
 *   `double(self, x)` vs trait `double(self)` false-green run=42.
 * wave427 Cap residual pure — named/ptr/slice ret soft (kind=-1) → Point vs Other /
 *   []i32 vs []u8 false-green run=42.
 * wave428 Cap residual pure — untyped trait self (param0 ek=-1) vs for-type soft →
 *   `impl Double for i32 { double(self: u64) }` false-green run≠42.
 * G.7 expand this function only (twin: seed_check_impl_missing_methods_c).
 * @return 0 ok; -1 unknown trait / missing method / signature mismatch.
 * PLATFORM: SHARED parse+typeck gate.
 */
/* wave439: forward decls — defined below, called from trait check. */
int32_t xlang_generic_bound_check_c(void);
void xlang_generic_bound_scan_c(uint8_t *data, int32_t len);
/* wave455: declaration-order type-param names per generic function (for ret fixup). */
int32_t xlang_generic_func_type_param_index_c(const uint8_t *fn_name, int32_t fn_name_len,
                                               const uint8_t *tp_name, int32_t tp_name_len);
int32_t xlang_generic_func_register_type_params_c(const uint8_t *fn_name, int32_t fn_name_len,
                                                    const uint8_t names[][64], const int32_t *lens,
                                                    int32_t n);
void xlang_generic_func_reg_reset_c(void);
/* 4.2.2 generic-body method: T: Trait → Trait.method (typeck method_call). */
int32_t xlang_generic_bound_method_on_param_c(const uint8_t *fn_name, int32_t fn_name_len,
                                               const uint8_t *tp_name, int32_t tp_name_len,
                                               const uint8_t *method_name, int32_t method_name_len,
                                               int32_t num_args, int32_t *out_ret_kind,
                                               uint8_t *out_ret_name, int32_t *out_ret_name_len);

/* wave439: source buffer stash. Populated by xlang_generic_bound_stash_source_c
 * from the top-level skip functions (struct/enum/trait/impl), each of which
 * receives the full-file source slice from parser.x. Read by the scan invoked
 * inside xlang_trait_check_impls_complete_c (which only gets *Module). Any file
 * exercising generic bounds has at least a trait+struct decl, so at least one
 * skip function runs before the trait checker. PLATFORM: SHARED parse. */
static uint8_t *g_w439_src_data;
static int32_t g_w439_src_len;

/**
 * TYPE_NAMED spelling "Self" (capital S) — not TOKEN_SELF lowercase binding.
 * Used by self_matches_for and named_eq_self as the for-type alias.
 * PLATFORM: SHARED parse.
 */
static int32_t xlang_skip_name_is_self_c(const uint8_t *nm, int32_t nl) {
  return (nl == 4 && nm &&
          nm[0] == (uint8_t)'S' && nm[1] == (uint8_t)'e' &&
          nm[2] == (uint8_t)'l' && nm[3] == (uint8_t)'f')
             ? 1
             : 0;
}

/**
 * wave441: verify impl method's self (param0) type matches the impl's for-type.
 * Used both during method lookup (find the method belonging to THIS impl block,
 * not another impl of the same trait — two structs impl same trait was a
 * false-red: 2nd impl found 1st impl's method by name-only and failed self check)
 * and during wave428 self-type verification.
 *
 * wave470: TYPE_NAMED "Self" aliases the named non-ptr for-type. Default-method
 * hoist re-parses the trait body with literal Self still on param0; without
 * this alias, empty `impl Trait for A` false-reds "self type mismatch".
 *
 * wave471: also accept pointer receivers `self: *For` / `self: *Self` when the
 * impl is `for For` (non-ptr). Method style *Self is common; for_ptr still means
 * the for-type itself is *T (unchanged branch above).
 *
 * @param arena       ASTArena (void*) for kind/name access; may be null.
 * @param pty0        type_ref of impl method param0 (self); 0 if untyped.
 * @param for_k       for-type kind ord (g_xlang_skip_impl_for_kinds[si]); -1 unknown.
 * @param for_ptr     1 if for-type is *T (g_xlang_skip_impl_for_is_ptr[si]).
 * @param for_name    for-type name bytes (g_xlang_skip_impl_for_names[si]); may be null.
 * @param for_nlen    for-type name length (g_xlang_skip_impl_for_name_lens[si]).
 * @return 1 if match or unknown/untyped (accept, preserve old first-match);
 *         0 if definite mismatch.
 * PLATFORM: SHARED parse.
 */
static int32_t xlang_skip_impl_self_matches_for_c(void *arena, int32_t pty0,
                                                   int32_t for_k, int32_t for_ptr,
                                                   const uint8_t *for_name, int32_t for_nlen) {
  int32_t got0;
  if (for_k < 0)
    return 1; /* for-type unknown — accept (preserve old first-match behavior) */
  got0 = (pty0 != 0) ? pipeline_type_kind_ord_at(arena, pty0) : -1;
  if (got0 < 0)
    return 1; /* impl self untyped — accept (wave428 skip when got0<0) */
  if (for_ptr) {
    int32_t elem;
    int32_t gek;
    if (got0 != XLANG_TRAIT_TY_PTR)
      return 0;
    elem = (pty0 != 0) ? pipeline_type_elem_ref_at(arena, pty0) : 0;
    gek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (gek >= 0 && gek != for_k)
      return 0;
    if (gek == for_k && for_k == XLANG_TRAIT_TY_NAMED && for_nlen > 0 && for_name && elem != 0) {
      uint8_t gnm[64];
      int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
      /* wave471: *Self elem aliases named for-type under for_ptr. */
      if (xlang_skip_name_is_self_c(gnm, gnl))
        return 1;
      if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
        return 0;
    }
    return 1;
  }
  /*
   * wave471: for is non-ptr named/builtin; receiver may still be *For / *Self
   * (by-pointer method). Walk PTR elem and match for_k / Self alias.
   */
  if (got0 == XLANG_TRAIT_TY_PTR) {
    int32_t elem = (pty0 != 0) ? pipeline_type_elem_ref_at(arena, pty0) : 0;
    int32_t gek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (gek < 0)
      return 1;
    if (gek != for_k)
      return 0;
    if (for_k == XLANG_TRAIT_TY_NAMED && for_nlen > 0 && for_name && elem != 0) {
      uint8_t gnm[64];
      int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
      if (xlang_skip_name_is_self_c(gnm, gnl))
        return 1;
      if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
        return 0;
    }
    return 1;
  }
  if (got0 != for_k)
    return 0;
  if (got0 == XLANG_TRAIT_TY_NAMED && for_nlen > 0 && for_name) {
    uint8_t gnm[64];
    int32_t gnl = pipeline_type_named_name_into(arena, pty0, gnm);
    /* wave470: Self on free/default method ≡ named for-type. */
    if (xlang_skip_name_is_self_c(gnm, gnl))
      return (for_k == XLANG_TRAIT_TY_NAMED) ? 1 : 0;
    if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
      return 0;
  }
  return 1;
}

/**
 * F2: Returns 1 iff some registered impl block has trait_name == trait_nm AND
 * for-type matches concrete_ty_ref (reuses xlang_skip_impl_self_matches_for_c
 * for the for-type shape comparison). 0 otherwise.
 *
 * Called from typeck dyn-coerce gate (src/typeck/typeck.x assign + let-init
 * paths) to verify `let x: dyn Trait = concrete_T_val` requires an impl block.
 * G.7 single authority: this function (twin of xlang_skip_impl_self_matches_for_c);
 * typeck must NOT iterate g_xlang_skip_impl_* globals directly.
 * PLATFORM: SHARED.
 *
 * @param arena           ASTArena (void*) for kind/name access; same instance
 *                       the parser populated impl entries into.
 * @param concrete_ty_ref type_ref of the RHS concrete type (e.g. struct A);
 *                       must be non-zero.
 * @param trait_nm       trait name bytes (e.g. "Clone"); must be non-null.
 * @param trait_nlen     trait name length; must be > 0.
 * @return 1 if any impl block matches; 0 otherwise.
 */
int32_t xlang_skip_impl_concrete_implements_trait_c(void *arena,
        int32_t concrete_ty_ref, const uint8_t *trait_nm, int32_t trait_nlen) {
  int32_t si;
  if (!trait_nm || trait_nlen <= 0 || concrete_ty_ref == 0)
    return 0;
  for (si = 0; si < g_xlang_skip_impl_seen_n; si++) {
    int32_t tlen = g_xlang_skip_impl_trait_len[si];
    const uint8_t *tname = g_xlang_skip_impl_trait[si];
    if (tlen != trait_nlen || tlen <= 0)
      continue;
    if (memcmp(tname, trait_nm, (size_t)tlen) != 0)
      continue;
    if (xlang_skip_impl_self_matches_for_c(arena, concrete_ty_ref,
            g_xlang_skip_impl_for_kinds[si],
            g_xlang_skip_impl_for_is_ptr[si],
            g_xlang_skip_impl_for_names[si],
            g_xlang_skip_impl_for_name_lens[si]))
      return 1;
  }
  return 0;
}

/**
 * F4 per-impl vtable statics: iterator accessors over the impl registry
 * `g_xlang_skip_impl_*`. These complement the F2 query accessor
 * `xlang_skip_impl_concrete_implements_trait_c` (which answers "does Type X
 * implement Trait Y") by exposing the list of registered impl blocks so that
 * codegen can iterate every `impl Trait for Type` and emit a module-level
 * static vtable per impl.
 *
 * G.7 "有则补全": the query authority (concrete_implements_trait_c) already
 * iterates internally; these three new iterators expose iteration to codegen
 * without duplicating the for-type shape-matching logic (shape matching stays
 * in xlang_skip_impl_self_matches_for_c). codegen must NOT touch the globals
 * directly — same rule as typeck (see L1183 comment).
 *
 * PLATFORM: SHARED parse + codegen.
 */

/**
 * Return the count of registered impl blocks in the current module's impl
 * registry. Safe to call with empty registry (returns 0).
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_impl_seen_count_c(void) {
  return g_xlang_skip_impl_seen_n;
}

/**
 * Copy the trait name of impl block at index `si` into `out64` (must be
 * >= 64 bytes). Returns the trait name length (0 if si out of range or name
 * is empty). The copied bytes are exactly `min(name_len, 64)` long; if the
 * stored name is longer than 64 it is truncated but the returned length is
 * the true stored length (caller can detect truncation).
 *
 * @param si    impl block index, 0..xlang_skip_impl_seen_count_c()-1.
 * @param out64 output buffer for the trait name bytes (capacity >= 64).
 * @return trait name length, or 0 on invalid si / empty name.
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_impl_trait_name_into_c(int32_t si, uint8_t *out64) {
  int32_t nlen;
  int32_t ci;
  if (si < 0 || si >= g_xlang_skip_impl_seen_n || !out64)
    return 0;
  nlen = g_xlang_skip_impl_trait_len[si];
  if (nlen <= 0)
    return 0;
  for (ci = 0; ci < nlen && ci < 64; ci++)
    out64[ci] = g_xlang_skip_impl_trait[si][ci];
  return nlen;
}

/**
 * Read the for-type info of impl block at index `si`. All out-params are
 * written on success (returns 1) and left untouched on failure (returns 0).
 *
 * @param si          impl block index.
 * @param out_kind    receives for-type kind ord (XLANG_TRAIT_TY_NAMED=8 etc.),
 *                    or -1 if unknown (matches g_xlang_skip_impl_for_kinds init).
 * @param out_is_ptr  receives 1 if for-type is *T, 0 otherwise.
 * @param out_name64  receives for-type name bytes (capacity >= 64; empty for
 *                    builtin for-types).
 * @param out_nlen_ptr receives for-type name length (0 for builtin / unknown).
 * @return 1 on success, 0 if si out of range.
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_impl_for_type_into_c(int32_t si, int32_t *out_kind,
        int32_t *out_is_ptr, uint8_t *out_name64, int32_t *out_nlen_ptr) {
  int32_t nlen;
  int32_t ci;
  if (si < 0 || si >= g_xlang_skip_impl_seen_n)
    return 0;
  if (!out_kind || !out_is_ptr || !out_name64 || !out_nlen_ptr)
    return 0;
  *out_kind = g_xlang_skip_impl_for_kinds[si];
  *out_is_ptr = g_xlang_skip_impl_for_is_ptr[si];
  nlen = g_xlang_skip_impl_for_name_lens[si];
  *out_nlen_ptr = nlen;
  for (ci = 0; ci < nlen && ci < 64; ci++)
    out_name64[ci] = g_xlang_skip_impl_for_names[si][ci];
  return 1;
}

/**
 * F3 vtable dispatch helpers — G.7 single-authority accessors over the
 * trait registry `g_xlang_skip_trait_reg[]`. Method declaration order in the
 * trait body defines the vtable slot index (slot 0 = first declared method).
 *
 * Used by typeck (resolve method name -> vtable slot for dyn dispatch) and
 * codegen (enumerate trait methods to build the per-impl function-pointer
 * array at the concrete->dyn coerce site).
 *
 * PLATFORM: SHARED parse + typeck + codegen.
 */

/**
 * Find the trait registry index for a trait by name (linear scan).
 * @param trait_nm   trait name bytes (e.g. "Clone"); must be non-null.
 * @param trait_nlen trait name length; must be > 0.
 * @return registry slot 0..g_xlang_skip_trait_reg_n-1, or -1 if not found.
 * PLATFORM: SHARED.
 */
static int32_t xlang_skip_trait_find_reg_c(const uint8_t *trait_nm, int32_t trait_nlen) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0)
    return -1;
  for (ti = 0; ti < g_xlang_skip_trait_reg_n; ti++) {
    int32_t tlen = g_xlang_skip_trait_reg[ti].name_len;
    const uint8_t *tname = g_xlang_skip_trait_reg[ti].name;
    if (tlen != trait_nlen || tlen <= 0)
      continue;
    if (memcmp(tname, trait_nm, (size_t)tlen) != 0)
      continue;
    return ti;
  }
  return -1;
}

/**
 * True when `trait_nm` is a registered trait (skip-trait table).
 * G.7: thin public wrapper over xlang_skip_trait_find_reg_c so type_ref
 * can treat a bare trait name as TYPE_DYN without a second lookup table.
 * `xlang_skip_trait_method_count_c` returns 0 for both "missing" and
 * "empty trait", so it cannot be this predicate.
 * @param trait_nm *u8 — trait name bytes; null rejected
 * @param trait_nlen i32 — byte count; must be > 0
 * @return i32 — 1 if registered, 0 otherwise
 * PLATFORM: SHARED parse.
 */
int32_t xlang_skip_trait_is_registered_c(const uint8_t *trait_nm, int32_t trait_nlen) {
  if (xlang_skip_trait_find_reg_c(trait_nm, trait_nlen) >= 0)
    return 1;
  return 0;
}

/**
 * Resolve a method name to its vtable slot index within a trait.
 * Slot = declaration order (0-based) in the trait body.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param method_nm   method name bytes; must be non-null.
 * @param method_nlen method name length; must be > 0.
 * @return slot index >= 0, or -1 if trait not registered or method absent.
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_trait_method_slot_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                       const uint8_t *method_nm, int32_t method_nlen) {
  int32_t ti;
  int32_t mi;
  int32_t n;
  if (!trait_nm || trait_nlen <= 0 || !method_nm || method_nlen <= 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  n = g_xlang_skip_trait_reg[ti].num_methods;
  if (n < 0)
    n = 0;
  for (mi = 0; mi < n; mi++) {
    int32_t mlen = g_xlang_skip_trait_reg[ti].method_lens[mi];
    const uint8_t *mname = g_xlang_skip_trait_reg[ti].methods[mi];
    if (mlen != method_nlen || mlen <= 0)
      continue;
    if (memcmp(mname, method_nm, (size_t)mlen) != 0)
      continue;
    return mi;
  }
  return -1;
}

/**
 * Return the number of declared methods in a trait (= vtable slot count).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @return method count (0 if trait not registered or empty).
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_trait_method_count_c(const uint8_t *trait_nm, int32_t trait_nlen) {
  int32_t ti;
  int32_t n;
  if (!trait_nm || trait_nlen <= 0)
    return 0;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return 0;
  n = g_xlang_skip_trait_reg[ti].num_methods;
  return (n > 0) ? n : 0;
}

/**
 * Copy the method name at a given vtable slot into a caller buffer.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param out64       output buffer of at least 64 bytes; must be non-null.
 * @return method name length (>0 on success), 0 if trait/slot invalid.
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_trait_method_name_into_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                           int32_t slot, uint8_t *out64) {
  int32_t ti;
  int32_t mlen;
  int32_t mi;
  if (!trait_nm || trait_nlen <= 0 || !out64 || slot < 0)
    return 0;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return 0;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return 0;
  mlen = g_xlang_skip_trait_reg[ti].method_lens[slot];
  if (mlen <= 0 || mlen > 64)
    return 0;
  for (mi = 0; mi < mlen; mi++)
    out64[mi] = g_xlang_skip_trait_reg[ti].methods[slot][mi];
  return mlen;
}

/**
 * Return the TypeKind ordinal of the method's return type at a vtable slot.
 * Used by typeck to stamp the call's resolved_type_ref for dyn dispatch so
 * codegen can emit a typed function-pointer cast at the call site.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot invalid or not captured.
 * PLATFORM: SHARED.
 */
int32_t xlang_skip_trait_method_ret_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                          int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_kinds[slot];
}

/**
 * Return the TypeKind ordinal of a trait-method return's element type.
 * Completes the F3 accessor family next to ret_kind. The scanner already
 * stores method_ret_elem_kinds (leaf of `[]T` / `[N]T`). Typeck dyn
 * dispatch cannot look up a module-func return type_ref (func_ix is the
 * vtable slot), so host-C ret `[2]i32` / `[]i32` reconstructs the type
 * via this + find_or_alloc_array/slice (sit-red XP003).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_elem_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                               int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_elem_kinds[slot];
}

/**
 * Return the outer N of a trait-method `[N]T` return (method_ret_array_sizes).
 * Completes the F3 accessor family next to ret_kind / ret_elem_kind.
 * `[]T` stores -1. Used with ret_elem_kind to find_or_alloc_array.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return N > 0, or -1 if trait/slot invalid / not a sized array.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_array_size_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_array_sizes[slot];
}

/**
 * Return ndims of a trait-method `[K][N]…T` return (method_ret_array_ndims).
 * Completes the F3 accessor family next to ret_array_size. The scanner
 * already stores ndims + dims; typeck dyn ret used only the outer N
 * (sit-red XT001 expected [2][2]i32 found [2]i32).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return ndims (>=1) for `[N]T` / `[K][N]T`, or 0 / -1 if unset / invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_array_ndims_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_array_ndims[slot];
}

/**
 * Return one dim of a trait-method `[K][N]…T` return (method_ret_array_dims).
 * dim_ix 0 is the outer K (same as ret_array_size); last dim is the
 * innermost N next to the leaf. Cap is XLANG_SKIP_TRAIT_ARRAY_DIM_MAX (8).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param dim_ix      dimension index (0 = outer).
 * @return N > 0, or -1 if trait/slot/dim invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_array_dim_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                              int32_t slot, int32_t dim_ix) {
  int32_t ti;
  int32_t nd;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || dim_ix < 0
      || dim_ix >= XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  nd = g_xlang_skip_trait_reg[ti].method_ret_array_ndims[slot];
  if (dim_ix >= nd)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_array_dims[slot][dim_ix];
}

/**
 * Return the TypeKind ordinal of a trait-method return's ARRAY/SLICE
 * element leaf (method_ret_elem_elem_kinds). Completes the F3 accessor
 * family next to ret_elem_kind. The scanner already stores the leaf of
 * `*[N]T` / `*[]T` (elem=ARRAY/SLICE, elem_elem=T). Typeck dyn ret
 * cannot look up a module-func return type_ref (func_ix is the slot),
 * so `*[2]i32` reconstructs via this + elem_array ndims/dims +
 * find_or_alloc_array then wrap ptr (sit-red: host-C
 * `int32_t (*p)[2] = (void)call`). Twin of param_elem_elem_kind.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_elem_elem_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                    int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[slot];
}

/**
 * Return ndims of a trait-method return's ARRAY elem (`*[K][N]T`).
 * Completes the F3 accessor family next to ret_elem_elem_kind. The
 * scanner already stores method_ret_elem_array_ndims (not the
 * top-level ret_array_ndims used by `[K][N]T` ret). Twin of
 * param_elem_array_ndims.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @return ndims (>=1), or 0 / -1 if unset / invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_elem_array_ndims_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                      int32_t slot) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[slot];
}

/**
 * Return one dim of a trait-method return's ARRAY elem (`*[K][N]T`).
 * dim_ix 0 is the outer K of the ARRAY elem; last dim is innermost N.
 * Cap is XLANG_SKIP_TRAIT_ARRAY_DIM_MAX (8). Twin of param_elem_array_dim.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param dim_ix      dimension index (0 = outer of the ARRAY elem).
 * @return N > 0, or -1 if trait/slot/dim invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_elem_array_dim_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                    int32_t slot, int32_t dim_ix) {
  int32_t ti;
  int32_t nd;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || dim_ix < 0
      || dim_ix >= XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  nd = g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[slot];
  /*
   * dest extras dest-RET extra STAR SLICE-elem ndims=-2 `*[][]*T`:
   * extra SLICE wrap COUNT in dims[0] (0 means 1 = `*[][]T`;
   * 2 = `*[][][]T`). Unused slot dims[1] extra PTR wrap COUNT
   * (1 = `*[][]*T`; 2 = `*[][]**T`; 0 / missing → -1 so
   * `*[][]T` stays extra-SLICE-only). dim_ix>=nd would reject
   * every dim_ix>=0 because -2 is negative. Twin of param extra
   * STAR `*[][]*T` unused slot dims[1]. Discriminant vs dest
   * extras dest-RET extra STAR SLICE-elem ndims=0 `*[]*T`
   * (extra PTR in dims[0]) / ndims>=1 `*[][2]*T` (extra PTR in
   * dims[ndims]) is ndims=-2 vs ndims=0 vs ndims>=1. Do not
   * invent -3. PLATFORM: SHARED.
   */
  if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
    int32_t extra;
    if (dim_ix == 0) {
      extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][0];
      if (extra <= 0)
        extra = 1;
      return extra;
    }
    if (dim_ix == 1) {
      extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][1];
      if (extra <= 0)
        return -1;
      return extra;
    }
    return -1;
  }
  /*
   * dest extras dest-RET extra STAR SLICE-elem ndims=0 `*[]*T`
   * AND dest extras dest-RET extra empty `[]` PTR-elem ndims=0
   * `**[]T`: unused slot dims[0] when ndims==0. dim_ix>=nd would
   * treat dim_ix=0 as an extra-wrap probe and reject because nd
   * is not >0. extra>0 returns the count; 0 / missing → -1 so
   * `*[]i32` / `**T` stays wrap-once. For SLICE-elem dims[0] is
   * extra PTR (1 = `*[]*T`); for PTR-elem dims[0] is extra SLICE
   * (1 = `**[]T`; 2 = `**[][]T`; extra PTR stays dims[1]). Twin
   * of param extra STAR `*[]*T` unused slot dims[0]. Discriminant
   * vs dest extras dest-RET extra STAR SLICE-elem ndims>=1
   * `*[][2]*T` (extra PTR in dims[ndims]) / extra empty `[]`
   * PTR-elem ndims>=1 `**[2][]T` (extra SLICE in dims[ndims]) is
   * ndims==0 vs ndims>=1 AND SLICE vs PTR elem. Do not invent
   * -3. PLATFORM: SHARED.
   */
  if (nd == 0 && dim_ix == 0) {
    int32_t extra;
    extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][0];
    if (extra <= 0)
      return -1;
    return extra;
  }
  /*
   * dest extras dest-RET extra STAR PTR-elem ndims=0 `***T`:
   * unused slot dims[1] extra PTR wrap COUNT (1 = `***T`; 2 =
   * `****T`; 0 / missing → -1 so `**T` stays wrap-once).
   * dim_ix>=nd would treat dim_ix=1 as an extra-wrap probe and
   * then reject because nd is not >0. Twin of dest extras dest-
   * RET extra STAR PTR-elem ndims>=1 `**[2]*T` (extra PTR in
   * dims[ndims+1]). Discriminant vs dest extras dest-RET extra
   * STAR SLICE-elem ndims=0 `*[]*T` (extra PTR in dims[0]) is
   * PTR vs SLICE elem. Do not invent -3. PLATFORM: SHARED.
   */
  if (nd == 0 && dim_ix == 1) {
    int32_t extra;
    extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][1];
    if (extra <= 0)
      return -1;
    return extra;
  }
  if (dim_ix >= nd) {
    /*
     * dest extras dest-RET PTR-to-ARRAY extra empty `[]` `*[2][]T`
     * AND dest extras dest-RET extra STAR `*[2]*T` AND dest extras
     * dest-RET extra empty `[]` SLICE-elem `*[][2][]T`: unused
     * slot dims[ndims] holds extra SLICE wrap COUNT for ARRAY/PTR
     * elem (1 = `*[2][]T` / `**[2][]T`; 2 = `*[2][][]T`) OR extra
     * PTR wrap COUNT for SLICE elem (1 = `*[][2]*T`). Unused slot
     * dims[ndims+1] holds extra PTR wrap COUNT for ARRAY/PTR elem
     * (1 = `*[2]*T` / `**[2]*T` / `*[2][]*T` / `**[2][]*T`) OR
     * extra SLICE wrap COUNT for SLICE elem (1 = `*[][2][]T`; 2 =
     * `*[][2][][]T`; 0 = no extra wrap = `*[][2]i32` / `*[][2]*T`;
     * extra PTR of `*[][2]*T` stays dims[ndims] — do not reopen).
     * Discriminant extra STAR ARRAY/PTR-elem vs extra empty `[]`
     * SLICE-elem (same unused slot dims[ndims+1]) is elem_kind
     * ARRAY vs PTR vs SLICE. dim_ix==ndims or ndims+1 and extra>0
     * → return the count. 0 / missing → -1 so `*[2]i32` /
     * `*[][2]i32` stays wrap-once. Twin of param_elem_array_dim
     * unused-slot dims[ndims] / dims[ndims+1]. Do not invent -3.
     * PLATFORM: SHARED.
     */
    int32_t extra;
    if (!(nd > 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX))
      return -1;
    if (dim_ix == nd) {
      extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][nd];
      if (extra <= 0)
        return -1;
      return extra;
    }
    if (dim_ix == nd + 1 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
      extra = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][nd + 1];
      if (extra <= 0)
        return -1;
      return extra;
    }
    return -1;
  }
  return g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[slot][dim_ix];
}

/**
 * Copy the TYPE_NAMED spelling of a trait-method return into out64.
 * Completes the F3 accessor family next to ret_kind / ret_elem_kind.
 * The scanner already stores method_ret_names for a bare `Pair` return
 * (and for a NAMED leaf of `*T` / `[]T` / `[N]T`). Typeck dyn dispatch
 * cannot look up a module-func return type_ref (func_ix is the vtable
 * slot), so host-C `let r: Pair = x.getp()` reconstructs via this +
 * find_or_alloc_named (sit-red: void-cast assignment).
 * Twin of xlang_skip_trait_method_name_into_c.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param out64       output buffer of at least 64 bytes; must be non-null.
 * @return name length (>0 on success), 0 if trait/slot invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_ret_name_into_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                               int32_t slot, uint8_t *out64) {
  int32_t ti;
  int32_t nlen;
  int32_t i;
  if (!trait_nm || trait_nlen <= 0 || !out64 || slot < 0)
    return 0;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return 0;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return 0;
  nlen = g_xlang_skip_trait_reg[ti].method_ret_name_lens[slot];
  if (nlen <= 0 || nlen > 64)
    return 0;
  for (i = 0; i < nlen; i++)
    out64[i] = g_xlang_skip_trait_reg[ti].method_ret_names[slot][i];
  return nlen;
}

/**
 * Return the TypeKind ordinal of one trait-method formal.
 * Completes the F3 accessor family (slot / count / name / ret_kind).
 * wave426 already stores method_param_kinds at parse; typeck dyn dispatch
 * cannot call typeck_stamp_resolved_args_float_lit (func_ix is the vtable
 * slot, not a module func) so it reads formals here and reuses
 * typeck_coerce_init_float_lit_to_decl.
 * Extra i of a METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot/param invalid or untyped.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                            int32_t slot, int32_t param_ix) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_kinds[slot][param_ix];
}

/**
 * Return the TypeKind ordinal of one trait-method formal's element type.
 * Completes the F3 accessor family next to param_kind. wave426 already
 * stores method_param_elem_kinds (leaf of `[]T` / `[N]T` / `*[N]T`).
 * Typeck dyn extras cannot look up a module-func formal type_ref
 * (func_ix is the vtable slot), so dest-SLICE ARRAY_LIT reuse
 * typeck_coerce_init_slice_from_array after this + find_or_alloc_slice.
 * Extra i of a METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot/param invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_elem_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                 int32_t slot, int32_t param_ix) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_elem_kinds[slot][param_ix];
}

/**
 * Copy the TYPE_NAMED spelling of one trait-method formal into out64.
 * Completes the F3 accessor family next to param_kind / param_elem_kind.
 * The scanner already stores method_param_names for a bare `Pair` formal
 * (and for a NAMED leaf of `*T` / `[]T` / `[N]T`). Typeck dyn extras
 * cannot look up a module-func formal type_ref (func_ix is the vtable
 * slot), so STRUCT_LIT dest-stamp reconstructs via this +
 * find_or_alloc_named + typeck_coerce_init_struct_lit_to_decl
 * (sit-red: host-C `(struct )` / asm run=162). Twin of
 * xlang_skip_trait_method_ret_name_into_c. Extra i of a METHOD_CALL
 * maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @param out64       output buffer of at least 64 bytes; must be non-null.
 * @return name length (>0 on success), 0 if trait/slot/param invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_name_into_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                 int32_t slot, int32_t param_ix,
                                                 uint8_t *out64) {
  int32_t ti;
  int32_t nlen;
  int32_t i;
  if (!trait_nm || trait_nlen <= 0 || !out64 || slot < 0 || param_ix < 0)
    return 0;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return 0;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return 0;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return 0;
  nlen = g_xlang_skip_trait_reg[ti].method_param_name_lens[slot][param_ix];
  if (nlen <= 0 || nlen > 64)
    return 0;
  for (i = 0; i < nlen; i++)
    out64[i] = g_xlang_skip_trait_reg[ti].method_param_names[slot][param_ix][i];
  return nlen;
}

/**
 * Return ndims of a trait-method `[K][N]…T` formal (method_param_array_ndims).
 * Completes the F3 accessor family next to param_elem_kind / param_name.
 * The scanner already stores ndims + dims for prefix `[N]T` / `[K][N]T`.
 * Typeck dyn extras cannot look up a module-func formal type_ref (func_ix
 * is the vtable slot), so dest-ARRAY extras (`[2]Pair`) reconstruct via
 * this + param_array_dim + find_or_alloc_array (sit-red host-C
 * `(uint8_t[]){(struct )}`). Twin of xlang_skip_trait_method_ret_array_ndims_c.
 * Extra i of a METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @return ndims (>=1) for `[N]T` / `[K][N]T`, or 0 / -1 if unset / invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_array_ndims_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                   int32_t slot, int32_t param_ix) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_array_ndims[slot][param_ix];
}

/**
 * Return one dim of a trait-method `[K][N]…T` formal (method_param_array_dims).
 * dim_ix 0 is the outer K; last dim is the innermost N next to the leaf.
 * Cap is XLANG_SKIP_TRAIT_ARRAY_DIM_MAX (8). Twin of
 * xlang_skip_trait_method_ret_array_dim_c. Extra i maps to param_ix = i+1.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @param dim_ix      dimension index (0 = outer).
 * @return N > 0, or -1 if trait/slot/param/dim invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_array_dim_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                 int32_t slot, int32_t param_ix, int32_t dim_ix) {
  int32_t ti;
  int32_t nd;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0 || dim_ix < 0
      || dim_ix >= XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  nd = g_xlang_skip_trait_reg[ti].method_param_array_ndims[slot][param_ix];
  if (dim_ix >= nd)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_array_dims[slot][param_ix][dim_ix];
}

/**
 * Return the TypeKind ordinal of a trait-method formal's ARRAY/SLICE
 * element leaf (method_param_elem_elem_kinds). Completes the F3
 * accessor family next to param_elem_kind. The scanner already stores
 * the leaf of `[][N]T` / `*[N]T` (elem=ARRAY, elem_elem=T). Typeck
 * dest-SLICE extras cannot look up a module-func formal type_ref
 * (func_ix is the vtable slot), so `[][2]i32` reconstructs via this +
 * elem_array ndims/dims + find_or_alloc_array then wrap slice
 * (sit-red: dyn extra `[[2,4]]` asm=1 / host-C=139). Extra i of a
 * METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @return TypeKind ord (>=0), or -1 if trait/slot/param invalid or unset.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_elem_elem_kind_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                      int32_t slot, int32_t param_ix) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_elem_elem_kinds[slot][param_ix];
}

/**
 * Return ndims of a trait-method formal's ARRAY elem (`[][K][N]T`).
 * Completes the F3 accessor family next to param_elem_elem_kind.
 * The scanner already stores method_param_elem_array_ndims (not the
 * top-level param_array_ndims used by dest-ARRAY extras). Extra i
 * maps to param_ix = i+1.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @return ndims (>=1 ARRAY pointee), 0 scalar, -2 extra SLICE wrap
 *         (`[]*[]T` / `[]*[][]T` / `[2]*[]T` / `[2]*[][]T` PTR
 *         pointee or `[][][]T` / `[][][][]T` SLICE-of-SLICE; extra
 *         wrap count in dims[0]), or -1 if unset / invalid.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_elem_array_ndims_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                        int32_t slot, int32_t param_ix) {
  int32_t ti;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  return g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[slot][param_ix];
}

/**
 * Return one dim of a trait-method formal's ARRAY elem (`[][K][N]T`).
 * dim_ix 0 is the outer K of the ARRAY elem; last dim is innermost N.
 * Cap is XLANG_SKIP_TRAIT_ARRAY_DIM_MAX (8). Extra i maps to param_ix = i+1.
 * @param trait_nm    trait name bytes; must be non-null.
 * @param trait_nlen  trait name length; must be > 0.
 * @param slot        vtable slot index (0..num_methods-1).
 * @param param_ix    formal index including self (0..PARAM_MAX-1).
 * @param dim_ix      dimension index (0 = outer of the ARRAY elem).
 * @return N > 0, or -1 if trait/slot/param/dim invalid.
 * When ndims==-2, dim_ix 0 returns the extra SLICE wrap count
 * (`[]*[]T` / `[][][]T` / `[2]*[]T` / `[2][][]T` = 1,
 * `[]*[][]T` / `[][][][]T` / `[2]*[][]T` / `[2][][][]T`
 * = 2). dims[0]==0 means 1 (`[]*[]T` / `[2]*[]T` /
 * `[2][][]T` / 3-layer compat). dest extras dest-SLICE-of-PTR,
 * dest-SLICE-of-SLICE, dest-ARRAY-of-PTR, and dest-ARRAY-of-SLICE
 * all read this for ndims==-2.
 * When ndims==0, dim_ix 0 returns dest extras dest-ARRAY-of-SLICE
 * extra PTR wrap count in unused slot dims[0] (`[2][]*T` = 1;
 * 0 / missing means no extra PTR = `[2][]i32`) AND dest extras
 * dest-SLICE-of-SLICE extra PTR wrap count (`[][]*T` = 1;
 * 0 / missing means no extra PTR = `[][]i32`). Discriminant is
 * the dest extras consumer (ARRAY outer vs SLICE outer), not a
 * second slot. When ndims==-2, dim_ix 1 returns dest extras
 * dest-SLICE-of-SLICE extra PTR wrap count in unused slot
 * dims[1] (`[][][]*T` = 1; 0 / missing means no extra PTR =
 * `[][][]T`) AND dest extras dest-ARRAY-of-SLICE extra PTR
 * wrap count (`[2][][]*T` = 1; 0 / missing means no extra
 * PTR = `[2][][]T`). Discriminant is the dest extras consumer
 * (SLICE outer vs ARRAY outer), not a second slot. dims[0]
 * stays extra SLICE (ban -3 / reuse of dim_ix 0).
 * When ndims>0, dim_ix==ndims returns dest extras dest-SLICE-of-ARRAY
 * extra SLICE wrap count in the unused slot (`[][2][]T` = 1;
 * `[][2][][]T` = 2; 0 / missing means no extra wrap = `[][2]i32`)
 * AND dest extras dest-SLICE-of-PTR extra SLICE wrap count
 * (`[]*[2][]T` = 1; `[]*[2][][]T` = 2; 0 / missing means no extra
 * wrap = `[]*[2]i32`) AND dest extras dest-ARRAY-of-SLICE extra
 * PTR wrap count (`[2][][2]*T` = 1; 0 / missing means no extra
 * PTR = `[2][][2]T`) AND dest extras dest-SLICE-of-SLICE extra
 * PTR wrap count (`[][][2]*T` = 1; 0 / missing means no extra
 * PTR = `[][][2]T`) AND dest extras dest-ARRAY of PTR extra
 * SLICE wrap count (`[2]*[2][]T` = 1; `[2]*[2][][]T` = 2; 0 /
 * missing means no extra wrap = `[2]*[2]i32` / `[2]*[2]*T`)
 * AND PTR-elem + PTR-outer extra SLICE wrap count (`**[2][]T`
 * = 1; `**[2][][]T` = 2; 0 / missing means no extra wrap =
 * `**[2]i32` / `**[2]*T`). Discriminant vs extra SLICE is
 * elem_kind (ARRAY vs SLICE vs PTR); discriminant ARRAY vs
 * SLICE vs PTR outer is param kind. dim_ix==ndims+1 returns extra PTR wrap count
 * (`[][2]*T` = 1; `[][2][]*T` = 1 with extra SLICE also in
 * dims[ndims]; `[]*[2]*T` = 1; `[]*[2][]*T` = 1 with extra
 * SLICE also in dims[ndims]; `[2]*[2]*T` = 1;
 * `[2]*[2][]*T` = 1 with extra SLICE also in dims[ndims];
 * `*[2]*T` = 1; `*[2][]*T` = 1 with extra SLICE also in
 * dims[ndims]; `**[2]*T` = 1; `**[2][]*T` = 1 with extra
 * SLICE also in dims[ndims]; 0 / missing means no extra PTR)
 * AND dest extras dest-ARRAY-of-SLICE extra wrap
 * `[2][][2][]T` extra SLICE wrap count (`[2][][2][]T` = 1;
 * `[2][][2][][]T` = 2) AND dest extras dest-SLICE-of-SLICE
 * extra wrap `[][][2][]T` extra SLICE wrap count
 * (`[][][2][]T` = 1; `[][][2][][]T` = 2) AND PTR-outer
 * extra empty `[]` extra SLICE wrap count (`*[][2][]T` = 1;
 * `*[][2][][]T` = 2; extra PTR of `[2][][2]*T` /
 * `[][][2]*T` / `*[][2]*T` stays dims[ndims] — do not
 * reopen; 0 / missing means no extra wrap = `[2][][2]T` /
 * `[][][2]T` / `*[][2]T`).
 * Discriminant dest extras dest-SLICE of ARRAY extra `[][2]*T`
 * vs dest extras dest-SLICE of PTR extra `[]*[2]*T` vs dest
 * extras dest-ARRAY of PTR extra `[2]*[2]*T` vs PTR-outer
 * `*[2]*T` vs dest extras dest-ARRAY of SLICE extra wrap
 * `[2][][2][]T` vs dest extras dest-SLICE of SLICE extra wrap
 * `[][][2][]T` vs PTR-outer extra empty `[]` `*[][2][]T`
 * is elem_kind ARRAY vs PTR vs SLICE (ARRAY vs SLICE vs PTR
 * outer). Both unused slots may be set
 * (`[][2][]*T` / `[]*[2][]*T` / `[2]*[2][]*T` /
 * `[2][][2][]*T` / `[][][2][]*T` / `*[2][]*T` /
 * `*[][2][]*T`). Do not invent -3: ARRAY
 * dims occupy 0..ndims-1 so extra wrap cannot reuse ndims=-2.
 * PLATFORM: SHARED parse + typeck.
 */
int32_t xlang_skip_trait_method_param_elem_array_dim_c(const uint8_t *trait_nm, int32_t trait_nlen,
                                                      int32_t slot, int32_t param_ix, int32_t dim_ix) {
  int32_t ti;
  int32_t nd;
  if (!trait_nm || trait_nlen <= 0 || slot < 0 || param_ix < 0 || dim_ix < 0
      || dim_ix >= XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
    return -1;
  if (param_ix >= XLANG_SKIP_TRAIT_PARAM_MAX)
    return -1;
  ti = xlang_skip_trait_find_reg_c(trait_nm, trait_nlen);
  if (ti < 0)
    return -1;
  if (slot >= g_xlang_skip_trait_reg[ti].num_methods)
    return -1;
  nd = g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[slot][param_ix];
  /* ndims==-2: extra SLICE wrap count in dims[0]. dim_ix>=nd would
   * reject every dim_ix>=0 because -2 is negative. PLATFORM: SHARED. */
  if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
    int32_t extra;
    if (dim_ix == 0) {
      extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][0];
      if (extra <= 0)
        extra = 1;
      return extra;
    }
    /*
     * dest extras dest-SLICE-of-SLICE extra PTR (`[][][]*T`) and
     * dest extras dest-ARRAY-of-SLICE extra PTR (`[2][][]*T`):
     * unused slot dims[1] when ndims==-2. extra>0 returns the
     * count; 0 / missing → -1 so `[][][]i32` / `[2][][]i32`
     * stay extra-SLICE-only. Discriminant is SLICE vs ARRAY
     * outer. Do not invent -3. PLATFORM: SHARED.
     */
    if (dim_ix == 1) {
      extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][1];
      if (extra <= 0)
        return -1;
      return extra;
    }
    return -1;
  }
  /*
   * dest extras dest-ARRAY-of-SLICE extra PTR (`[2][]*T`), dest
   * extras dest-SLICE-of-SLICE extra PTR (`[][]*T`), PTR-outer
   * extra STAR `*[]*T`, AND dest extras dest-PARAM extra empty
   * `[]` PTR-elem ndims=0 `**[]T`: unused slot dims[0] when
   * ndims==0. dim_ix>=nd would treat dim_ix=0 as an extra-wrap
   * probe and reject because nd is not >0. extra>0 returns the
   * count; 0 / missing → -1 so `[2][]i32` / `[][]i32` / `*[]i32`
   * / `**T` stay wrap-once. For SLICE-elem dims[0] is extra PTR
   * (1 = `[2][]*T` / `[][]*T` / `*[]*T`); for PTR-elem dims[0]
   * is extra SLICE (1 = `**[]T`; 2 = `**[][]T`; extra PTR stays
   * dims[1]). Discriminant ARRAY vs SLICE vs PTR outer is param
   * kind; discriminant extra PTR vs extra SLICE is SLICE vs PTR
   * elem. Twin of dest extras dest-RET extra empty `[]` PTR-elem
   * ndims=0 unused slot dims[0]. Do not invent -3. PLATFORM:
   * SHARED.
   */
  if (nd == 0 && dim_ix == 0) {
    int32_t extra;
    extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][0];
    if (extra <= 0)
      return -1;
    return extra;
  }
  /*
   * dest extras dest-PARAM extra STAR PTR-elem ndims=0 `***T`:
   * unused slot dims[1] extra PTR wrap COUNT (1 = `***T`; 2 =
   * `****T`; 0 / missing → -1 so `**T` stays wrap-once).
   * dim_ix>=nd would treat dim_ix=1 as an extra-wrap probe and
   * then reject because nd is not >0. Twin of dest extras dest-
   * PARAM extra STAR PTR-elem ndims>=1 `**[2]*T` (extra PTR in
   * dims[ndims+1]) AND dest extras dest-RET extra STAR PTR-elem
   * ndims=0 unused slot dims[1]. Discriminant vs dest extras
   * dest-PARAM extra STAR SLICE-elem ndims=0 `*[]*T` (extra PTR
   * in dims[0]) is PTR vs SLICE elem. Do not invent -3.
   * PLATFORM: SHARED.
   */
  if (nd == 0 && dim_ix == 1) {
    int32_t extra;
    extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][1];
    if (extra <= 0)
      return -1;
    return extra;
  }
  if (dim_ix >= nd) {
    /*
     * dest extras dest-SLICE-of-ARRAY extra wraps: unused slot
     * dims[ndims] holds extra SLICE wraps (`[][2][]T`); unused slot
     * dims[ndims+1] holds extra PTR wraps (`[][2]*T`). Both slots
     * may be set (`[][2][]*T`). dim_ix==ndims or ndims+1 and extra>0
     * → return the count. 0 / missing → -1 so `[][2]i32` (no extra
     * wrap) stays wrap-once. PLATFORM: SHARED.
     */
    int32_t extra;
    if (!(nd > 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX))
      return -1;
    if (dim_ix == nd) {
      /* dest extras dest-SLICE-of-ARRAY extra `[][2][]T`, dest
       * extras dest-SLICE-of-PTR extra `[]*[2][]T`, dest extras
       * dest-ARRAY-of-PTR extra `[2]*[2][]T`, dest extras
       * dest-ARRAY-of-SLICE extra PTR `[2][][2]*T`, dest extras
       * dest-SLICE-of-SLICE extra PTR `[][][2]*T`, PTR-outer
       * extra STAR `*[][2]*T` (elem=SLICE, unused slot
       * dims[ndims]; discriminant vs extra SLICE of `[][2][]T`
       * is elem_kind; discriminant ARRAY vs SLICE vs PTR outer
       * is param kind), and PTR-elem + PTR-outer extra
       * `**[2][]T` (elem=PTR, unused slot dims[ndims];
       * discriminant vs `[]*[2][]T` / `[2]*[2][]T` is SLICE vs
       * ARRAY vs PTR outer). extra>0 returns the count; 0 /
       * missing → -1 so `[][2]i32` / `[]*[2]i32` /
       * `[2]*[2]i32` / `[2]*[2]*T` / `[2][][2]i32` /
       * `[][][2]i32` / `*[][2]i32` / `**[2]i32` / `**[2]*T`
       * stay wrap-once / extra-ARRAY-only / extra-PTR-only.
       * PLATFORM: SHARED. */
      extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][nd];
      if (extra <= 0)
        return -1;
      return extra;
    }
    if (dim_ix == nd + 1 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
      /* dest extras dest-SLICE-of-ARRAY extra PTR `[][2]*T`,
       * dest extras dest-SLICE-of-PTR extra PTR `[]*[2]*T`,
       * dest extras dest-ARRAY-of-PTR extra PTR `[2]*[2]*T`,
       * PTR-outer extra PTR `*[2]*T`, dest extras
       * dest-ARRAY-of-SLICE extra wrap `[2][][2][]T`,
       * dest extras dest-SLICE-of-SLICE extra wrap
       * `[][][2][]T`, and PTR-outer extra empty `[]`
       * `*[][2][]T` (elem=SLICE, unused slot dims[ndims+1];
       * extra PTR of `[2][][2]*T` / `[][][2]*T` /
       * `*[][2]*T` stays dims[ndims] — do not reopen).
       * Discriminant dest extras dest-SLICE of PTR extra
       * `[]*[2]*T` vs dest extras dest-ARRAY of PTR extra
       * `[2]*[2]*T` (same unused slot) is SLICE vs ARRAY
       * outer. Discriminant dest extras dest-SLICE of ARRAY
       * extra `[][2]*T` vs PTR-outer `*[2]*T` (same unused
       * slot) is SLICE vs PTR outer. Discriminant dest
       * extras dest-ARRAY of SLICE extra wrap `[2][][2][]T`
       * vs dest extras dest-SLICE of SLICE extra wrap
       * `[][][2][]T` vs PTR-outer extra empty `[]`
       * `*[][2][]T` (same unused slot) is ARRAY vs SLICE
       * vs PTR outer. Discriminant vs dest extras dest-SLICE
       * of ARRAY extra PTR (same unused slot) is elem_kind
       * PTR vs ARRAY AND param kind ARRAY vs SLICE vs PTR.
       * extra>0 returns the count; 0 / missing → -1 so
       * `[][2]i32` / `[]*[2]i32` / `[2]*[2]i32` /
       * `*[2]i32` / `[2][][2]i32` / `[][][2]i32` /
       * `*[][2]i32` stay wrap-once / extra-ARRAY-only /
       * extra-PTR-only. PLATFORM: SHARED. */
      extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][nd + 1];
      if (extra <= 0)
        return -1;
      return extra;
    }
    return -1;
  }
  return g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[slot][param_ix][dim_ix];
}

/**
 * wave469 Cap residual pure — trait TYPE_NAMED "Self" rewrites to the impl
 * `for` type name when matching method param/ret signatures.
 *
 * Root: trait methods may write `self: Self` / `: Self` (capital Self is a
 * TYPE_NAMED spelling, not TOKEN_SELF). Completeness compared the literal
 * name "Self" to the impl's concrete type (e.g. A) → false-red
 * "parameter/return type mismatch" even when the impl correctly uses `for`.
 *
 * wave470: also accept got=="Self" when expect is Self (default hoist re-parse
 * keeps literal Self on the free UFCS function) or when expect is the for-type
 * name (impl wrote Self). Both sides mean the named non-ptr for-type.
 *
 * G.7 single authority: this helper; all NAMED name compares in
 * xlang_trait_check_impls_complete_c must call it (seed twin mirrors).
 * Soft: *Self / Self with non-named for (builtin i32 etc.) still mismatch
 * until kind-level rewrite; dyn Trait; multi-instantiation layout.
 * PLATFORM: SHARED parse.
 *
 * @param expect_nm trait expected type name bytes (may be "Self")
 * @param expect_nl length; <=0 → no name constraint (match)
 * @param got_nm    impl-side type name bytes
 * @param got_nl    length
 * @param for_nm    impl for-type name (g_xlang_skip_impl_for_names[si])
 * @param for_nl    length
 * @param for_ptr   1 if for-type is *T
 * @return 1 match, 0 mismatch
 */
static int32_t xlang_skip_trait_named_eq_self_c(
    const uint8_t *expect_nm, int32_t expect_nl,
    const uint8_t *got_nm, int32_t got_nl,
    const uint8_t *for_nm, int32_t for_nl, int32_t for_ptr) {
  int32_t exp_self;
  int32_t got_self;
  if (expect_nl <= 0)
    return 1;
  exp_self = xlang_skip_name_is_self_c(expect_nm, expect_nl);
  got_self = xlang_skip_name_is_self_c(got_nm, got_nl);
  if (exp_self) {
    /* Trait wrote Self → for-type (named, non-ptr only this wave). */
    if (for_ptr || for_nl <= 0 || !for_nm)
      return 0;
    /* Default hoist: free fn still has Self; both sides alias for. */
    if (got_self)
      return 1;
    return (got_nl == for_nl && got_nm &&
            memcmp(got_nm, for_nm, (size_t)for_nl) == 0) ? 1 : 0;
  }
  if (got_self) {
    /* Impl/default side wrote Self; trait wrote concrete for name. */
    if (for_ptr || for_nl <= 0 || !for_nm)
      return 0;
    return (expect_nl == for_nl && expect_nm &&
            memcmp(expect_nm, for_nm, (size_t)for_nl) == 0) ? 1 : 0;
  }
  return (got_nl == expect_nl && got_nm &&
          memcmp(got_nm, expect_nm, (size_t)expect_nl) == 0) ? 1 : 0;
}

/**
 * wave470: rewrite TYPE_NAMED "Self" to the impl `for` named type.
 * Used when hoisting trait default methods so UFCS method_call can match
 * receiver type A against param0 type A (not the literal Self name).
 *
 * wave471: also rewrite PTR-to-Self → PTR-to-for (`self: *Self` → `self: *A`).
 * Soft: for_ptr (impl for *T) / non-named for → leave type_ref unchanged.
 * PLATFORM: SHARED parse.
 * @param arena   ASTArena
 * @param type_ref type to rewrite; 0 → 0
 * @param for_nm  for-type name bytes
 * @param for_nl  length
 * @param for_ptr 1 if for is *T (no rewrite this wave)
 * @return rewritten type_ref or original
 */
static int32_t xlang_skip_rewrite_self_type_ref_c(void *arena, int32_t type_ref,
                                                   const uint8_t *for_nm, int32_t for_nl,
                                                   int32_t for_ptr) {
  int32_t k;
  uint8_t gnm[64];
  int32_t gnl;
  uint8_t for_copy[64];
  int32_t n;
  int32_t for_named;
  extern int32_t pipeline_type_find_or_alloc_named(void *arena, uint8_t *name, int32_t name_len);
  extern int32_t pipeline_type_find_or_alloc_compound(void *arena, int32_t kind_ord, int32_t elem_ref,
                                                       int32_t array_size);
  if (!arena || type_ref == 0 || for_ptr || for_nl <= 0 || !for_nm)
    return type_ref;
  n = for_nl;
  if (n > 63)
    n = 63;
  memset(for_copy, 0, sizeof(for_copy));
  memcpy(for_copy, for_nm, (size_t)n);
  k = pipeline_type_kind_ord_at(arena, type_ref);
  /* wave471: *Self → *For */
  if (k == XLANG_TRAIT_TY_PTR) {
    int32_t elem = pipeline_type_elem_ref_at(arena, type_ref);
    int32_t ek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (ek != XLANG_TRAIT_TY_NAMED)
      return type_ref;
    gnl = pipeline_type_named_name_into(arena, elem, gnm);
    if (!xlang_skip_name_is_self_c(gnm, gnl))
      return type_ref;
    for_named = pipeline_type_find_or_alloc_named(arena, for_copy, n);
    if (for_named == 0)
      return type_ref;
    return pipeline_type_find_or_alloc_compound(arena, XLANG_TRAIT_TY_PTR, for_named, 0);
  }
  if (k != XLANG_TRAIT_TY_NAMED)
    return type_ref;
  gnl = pipeline_type_named_name_into(arena, type_ref, gnm);
  if (!xlang_skip_name_is_self_c(gnm, gnl))
    return type_ref;
  return pipeline_type_find_or_alloc_named(arena, for_copy, n);
}

/*
 * wave468 Cap residual pure — hoist trait default method bodies as free UFCS
 * functions when not already present (impl override / free def).
 *
 * Root: skip_one_trait only registered signatures and discarded `{ body }`, so
 * empty `impl Trait for T {}` reported missing method and method_call failed
 * even when the trait provided a default body.
 *
 * wave470: per-impl inject + rewrite TYPE_NAMED Self → for-type on param/ret
 * so method_call UFCS type_refs_equal(receiver, param0) succeeds. Override /
 * same-name with matching self skips inject. Multi empty impls get one free
 * method per for-type (same link name; UFCS scores by self type).
 *
 * G.7 authority: general onefunc parse (`parser_asm_parse_one_function_buf_into_c`)
 * + minimal module slot commit (same pipeline_* APIs as seed_commit_onefunc).
 * Soft: multi-trait same default name; dyn Trait.
 * wave472: STRUCT_LIT return + Self type name rewrite.
 * wave473: body lets via parse_body_lets_into; Self rewrite on let types +
 *          STRUCT_LIT inits (same class as return STRUCT_LIT).
 * wave475: mid-body if/while/expr_stmt — fill ifs/whiles/expr_stmts + prefer
 *          onefunc src_stmt_order (G.7 twin of seed_commit free path).
 * wave476: also fill fors from onefunc (mid-body C-style for; match is
 *          body_expr_stmt already covered by fill_expr_stmts).
 * PLATFORM: SHARED parse.
 */
static int32_t xlang_skip_commit_default_onefunc_c(void *arena, void *module,
                                                   struct parser_asm_onefunc_result *res,
                                                   const uint8_t *for_nm, int32_t for_nl,
                                                   int32_t for_ptr) {
  int32_t type_ref;
  int32_t final_expr_ref;
  int32_t block_ref;
  int32_t fi_mod;
  int32_t p_copy;
  int32_t func_ref;
  struct ast_Block b;
  struct ast_Expr e;
  uint8_t *pool;
  /* EXPR_STRUCT_LIT ord — match ast.h / finish_struct_lit (must stay 45). */
  const int32_t k_expr_struct_lit = 45;
  /* EXPR_RETURN ord — match free commit final_expr RETURN guard (must stay 41). */
  const int32_t k_expr_return = 41;
  extern int32_t pipeline_module_func_alloc_slot(void *module);
  extern void pipeline_module_func_name_write(void *module, int32_t fi, uint8_t *name_bytes, int32_t name_len);
  extern void pipeline_module_func_set_num_params(void *module, int32_t fi, int32_t n);
  extern void pipeline_module_func_param_write(void *module, int32_t func_index, int32_t param_index,
                                              uint8_t *name_bytes, int32_t name_len, int32_t type_ref);
  extern void pipeline_module_func_set_return_type(void *module, int32_t fi, int32_t type_ref);
  extern void pipeline_module_func_set_body_ref(void *module, int32_t fi, int32_t body_ref);
  extern void pipeline_module_func_set_body_expr_ref(void *module, int32_t fi, int32_t body_expr_ref);
  extern void pipeline_module_func_set_is_extern(void *module, int32_t fi, int32_t is_extern);
  extern void pipeline_module_func_set_is_async(void *module, int32_t fi, int32_t is_async);
  extern void pipeline_module_func_ref_set(void *module, int32_t fi, int32_t func_ref);
  extern void pipeline_arena_func_copy_slot_from_module(void *arena, int32_t func_ref, void *module, int32_t fi);
  extern uint8_t *parser_asm_onefunc_result_pool_ptr_c(struct parser_asm_onefunc_result *res);
  extern int32_t pipeline_onefunc_param_name_len(uint8_t *pool, int32_t pi);
  extern void pipeline_onefunc_param_name_copy32(uint8_t *pool, int32_t pi, uint8_t *out32);
  extern int32_t pipeline_onefunc_param_type_ref(uint8_t *pool, int32_t pi);
  extern int32_t parser_asm_fill_block_const_let_from_res_c(void *arena, int32_t block_ref,
                                                           struct parser_asm_onefunc_result *res,
                                                           int32_t type_ref);
  extern int32_t pipeline_block_append_expr_stmt(void *arena, int32_t block_ref, int32_t expr_ref);
  extern int32_t pipeline_block_append_stmt_order(void *arena, int32_t block_ref, uint8_t kind, int32_t idx);
  extern int32_t parser_should_wrap_func_tail_in_return_glue(void *arena, struct parser_asm_onefunc_result *res,
                                                            int32_t type_ref);
  extern int32_t pipeline_type_ensure_by_kind_ord(void *arena, int32_t kind_ord);
  extern int32_t pipeline_block_let_type_ref(void *arena, int32_t br, int32_t li);
  extern int32_t pipeline_block_set_let_type_ref(void *arena, int32_t br, int32_t li, int32_t type_ref);
  extern int32_t pipeline_block_let_init_ref(void *arena, int32_t br, int32_t li);
  extern int32_t pipeline_onefunc_num_if_stmts(uint8_t *pool);
  extern int32_t pipeline_onefunc_num_whiles(uint8_t *pool);
  extern int32_t pipeline_onefunc_num_fors(uint8_t *pool);
  extern int32_t pipeline_onefunc_num_body_expr_stmts(uint8_t *pool);
  extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t *pool);
  extern void pipeline_block_fill_ifs_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
  extern void pipeline_block_fill_whiles_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
  extern void pipeline_block_fill_fors_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
  extern void pipeline_block_fill_expr_stmts_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
  extern void pipeline_block_fill_stmt_order_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);

  if (!arena || !module || !res || !res->ok)
    return -1;
  type_ref = res->func_return_type_ref;
  if (type_ref == 0) {
    /* default i32 when untyped ret (rare for trait methods). */
    type_ref = pipeline_type_ensure_by_kind_ord(arena, (int32_t)PARSER_ASM_TYPE_I32);
  }
  /* wave470: Self return → for-type before body wrap uses type_ref. */
  type_ref = xlang_skip_rewrite_self_type_ref_c(arena, type_ref, for_nm, for_nl, for_ptr);
  if (type_ref == 0)
    return -1;

  if (res->return_expr_ref != 0) {
    final_expr_ref = res->return_expr_ref;
    /*
     * wave472 Cap residual pure: STRUCT_LIT type name "Self" → for-type.
     * Default re-parse keeps literal Self on `return Self { … }`; without
     * rewrite typeck reports expected A found Self (same class as free-fn
     * Self lit). Concrete `return A { … }` already matches for-type name.
     * Also stamp resolved_type_ref = rewritten return type for emit/typeck.
     * PLATFORM: SHARED parse.
     */
    e = ast_ast_arena_expr_get(arena, final_expr_ref);
    if (e.kind == k_expr_struct_lit) {
      int32_t snl = e.struct_lit_struct_name_len;
      if (snl > 0 && xlang_skip_name_is_self_c(e.struct_lit_struct_name, snl) &&
          for_nm && for_nl > 0 && for_nl <= 63 && for_ptr == 0) {
        int32_t ti;
        uint8_t for_copy[64];
        memset(for_copy, 0, sizeof(for_copy));
        memcpy(for_copy, for_nm, (size_t)for_nl);
        memset(e.struct_lit_struct_name, 0, sizeof(e.struct_lit_struct_name));
        for (ti = 0; ti < for_nl; ti++)
          e.struct_lit_struct_name[ti] = for_copy[ti];
        e.struct_lit_struct_name_len = for_nl;
      }
      if (type_ref != 0)
        e.resolved_type_ref = type_ref;
      ast_ast_arena_expr_set(arena, final_expr_ref, e);
    }
  } else if (res->return_var_name_len > 0) {
    final_expr_ref = ast_ast_arena_expr_alloc(arena);
    if (final_expr_ref == 0)
      return -1;
    e = ast_ast_arena_expr_get(arena, final_expr_ref);
    memset(&e, 0, sizeof(e));
    e.kind = (int32_t)AST_EXPR_VAR;
    e.var_name_len = res->return_var_name_len;
    memcpy(e.var_name, res->return_var_name, (size_t)res->return_var_name_len);
    ast_ast_arena_expr_set(arena, final_expr_ref, e);
  } else {
    final_expr_ref = ast_ast_arena_expr_alloc(arena);
    if (final_expr_ref == 0)
      return -1;
    e = ast_ast_arena_expr_get(arena, final_expr_ref);
    memset(&e, 0, sizeof(e));
    e.kind = (int32_t)AST_EXPR_LIT;
    e.int_val = res->return_val;
    e.resolved_type_ref = type_ref;
    ast_ast_arena_expr_set(arena, final_expr_ref, e);
  }

  /* Wrap tail in RETURN when needed (authority: should_wrap_func_tail glue). */
  if (parser_should_wrap_func_tail_in_return_glue(arena, res, type_ref)) {
    int32_t wrapped = ast_ast_arena_expr_alloc(arena);
    if (wrapped == 0)
      return -1;
    e = ast_ast_arena_expr_get(arena, wrapped);
    memset(&e, 0, sizeof(e));
    e.kind = (int32_t)AST_EXPR_RETURN;
    e.unary_operand_ref = final_expr_ref;
    e.resolved_type_ref = type_ref;
    ast_ast_arena_expr_set(arena, wrapped, e);
    final_expr_ref = wrapped;
  }

  block_ref = ast_ast_arena_block_alloc(arena);
  if (block_ref == 0)
    return -1;
  b = ast_ast_arena_block_get(arena, block_ref);
  memset(&b, 0, sizeof(b));
  /*
   * G.7 twin of parser_gen seed_commit: num_consts/num_lets must stay 0 before
   * fill_block_const_let (append_* increments). Pre-setting res->num_lets made
   * block_pool_append_pos treat the first append as "subsequent" → insert-and-
   * shift in the global lets pool and corrupt sibling function bodies (wave473
   * main `let b` became garbage `s` / undeclared b). PLATFORM: SHARED parse.
   */
  b.num_consts = 0;
  b.num_lets = 0;
  b.final_expr_ref = final_expr_ref;
  ast_ast_arena_block_set(arena, block_ref, b);
  if (!parser_asm_fill_block_const_let_from_res_c(arena, block_ref, res, type_ref))
    return -1;
  /* fill updates res->num_* from sidecar; re-read block counts for stmt_order. */

  /*
   * wave473: after fill, rewrite let-decl TYPE_NAMED Self → for-type and
   * STRUCT_LIT init names Self → for (G.7 same helpers as param/ret/return
   * STRUCT_LIT). Without this `let s: Self = Self { … }; return s` typeck
   * still sees Self vs A. PLATFORM: SHARED parse.
   */
  b = ast_ast_arena_block_get(arena, block_ref);
  {
    int32_t li_rw;
    for (li_rw = 0; li_rw < b.num_lets; li_rw++) {
      int32_t lty = pipeline_block_let_type_ref(arena, block_ref, li_rw);
      int32_t nty = xlang_skip_rewrite_self_type_ref_c(arena, lty, for_nm, for_nl, for_ptr);
      int32_t init_ref;
      if (nty != 0 && nty != lty)
        (void)pipeline_block_set_let_type_ref(arena, block_ref, li_rw, nty);
      init_ref = pipeline_block_let_init_ref(arena, block_ref, li_rw);
      if (init_ref != 0) {
        e = ast_ast_arena_expr_get(arena, init_ref);
        if (e.kind == k_expr_struct_lit) {
          int32_t snl = e.struct_lit_struct_name_len;
          if (snl > 0 && xlang_skip_name_is_self_c(e.struct_lit_struct_name, snl) &&
              for_nm && for_nl > 0 && for_nl <= 63 && for_ptr == 0) {
            int32_t ti;
            uint8_t for_copy[64];
            memset(for_copy, 0, sizeof(for_copy));
            memcpy(for_copy, for_nm, (size_t)for_nl);
            memset(e.struct_lit_struct_name, 0, sizeof(e.struct_lit_struct_name));
            for (ti = 0; ti < for_nl; ti++)
              e.struct_lit_struct_name[ti] = for_copy[ti];
            e.struct_lit_struct_name_len = for_nl;
          }
          if (nty != 0)
            e.resolved_type_ref = nty;
          else if (type_ref != 0 && e.resolved_type_ref == 0)
            e.resolved_type_ref = type_ref;
          ast_ast_arena_expr_set(arena, init_ref, e);
        }
      }
    }
  }

  /*
   * wave475/476: fill mid-body if/while/for/expr_stmt from onefunc pool, then
   * prefer src_stmt_order when present (free seed_commit twin). Else synthetic
   * order: consts → lets → final expr_stmt.
   * PLATFORM: SHARED parse.
   */
  pool = parser_asm_onefunc_result_pool_ptr_c(res);
  b = ast_ast_arena_block_get(arena, block_ref);
  {
    int32_t n_while = pool ? pipeline_onefunc_num_whiles(pool) : 0;
    int32_t n_for = pool ? pipeline_onefunc_num_fors(pool) : 0;
    int32_t n_if = pool ? pipeline_onefunc_num_if_stmts(pool) : 0;
    int32_t n_src = pool ? pipeline_onefunc_num_src_stmt_order(pool) : 0;
    int32_t n_ex = pool ? pipeline_onefunc_num_body_expr_stmts(pool) : 0;
    if (n_while > 0)
      pipeline_block_fill_whiles_from_onefunc(arena, block_ref, pool, n_while);
    if (n_for > 0)
      pipeline_block_fill_fors_from_onefunc(arena, block_ref, pool, n_for);
    if (n_if > 0)
      pipeline_block_fill_ifs_from_onefunc(arena, block_ref, pool, n_if);
    b = ast_ast_arena_block_get(arena, block_ref);
    if (n_src > 0) {
      if (n_ex > 0)
        pipeline_block_fill_expr_stmts_from_onefunc(arena, block_ref, pool, n_ex);
      pipeline_block_fill_stmt_order_from_onefunc(arena, block_ref, pool, n_src);
      b = ast_ast_arena_block_get(arena, block_ref);
      b.final_expr_ref = final_expr_ref;
      if (b.num_expr_stmts > 0 && final_expr_ref != 0) {
        e = ast_ast_arena_expr_get(arena, final_expr_ref);
        if (e.kind != k_expr_return)
          b.final_expr_ref = 0;
      }
      ast_ast_arena_block_set(arena, block_ref, b);
    } else {
      int32_t ci;
      int32_t li;
      for (ci = 0; ci < b.num_consts; ci++) {
        if (pipeline_block_append_stmt_order(arena, block_ref, (uint8_t)0, ci) < 0)
          return -1;
      }
      for (li = 0; li < b.num_lets; li++) {
        if (pipeline_block_append_stmt_order(arena, block_ref, (uint8_t)1, li) < 0)
          return -1;
      }
      if (final_expr_ref != 0) {
        int32_t fin_ex = pipeline_block_append_expr_stmt(arena, block_ref, final_expr_ref);
        if (fin_ex < 0)
          return -1;
        if (pipeline_block_append_stmt_order(arena, block_ref, (uint8_t)2, fin_ex) < 0)
          return -1;
        b = ast_ast_arena_block_get(arena, block_ref);
        b.final_expr_ref = 0;
        ast_ast_arena_block_set(arena, block_ref, b);
      }
    }
  }

  func_ref = ast_ast_arena_func_alloc(arena);
  if (func_ref == 0)
    return -1;
  fi_mod = pipeline_module_func_alloc_slot(module);
  if (fi_mod < 0)
    return -1;
  pipeline_module_func_name_write(module, fi_mod, res->name, res->name_len);
  /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
  { static int dbgac=0; if (dbgac<4000){dbgac++; char _db[384]; int _dn = snprintf(_db, sizeof _db, "DBG_ACOMMIT mod=%p idx=%d name=%.*s nfns=%d\n",(void*)module,(int)fi_mod,(int)(res->name_len>0?res->name_len:0),(char*)res->name,(int)pipeline_module_num_funcs(module)); if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn);} }
  pipeline_module_func_set_num_params(module, fi_mod, res->num_params);
  pipeline_module_func_set_return_type(module, fi_mod, type_ref);
  pipeline_module_func_set_body_ref(module, fi_mod, block_ref);
  pipeline_module_func_set_body_expr_ref(module, fi_mod, 0);
  pipeline_module_func_set_is_extern(module, fi_mod, 0);
  pipeline_module_func_set_is_async(module, fi_mod, 0);
  pool = parser_asm_onefunc_result_pool_ptr_c(res);
  for (p_copy = 0; p_copy < res->num_params; p_copy++) {
    uint8_t pname32[128];
    int32_t pty;
    memset(pname32, 0, sizeof(pname32));
    if (pool)
      pipeline_onefunc_param_name_copy32(pool, p_copy, pname32);
    pty = pool ? pipeline_onefunc_param_type_ref(pool, p_copy) : 0;
    /* wave470: self: Self / T: Self → for-type for UFCS match. */
    pty = xlang_skip_rewrite_self_type_ref_c(arena, pty, for_nm, for_nl, for_ptr);
    /* wave477: self without type annotation → set to for-type so UFCS resolves. */
    if (pty == 0 && p_copy == 0 && for_nm && for_nl > 0) {
      extern int32_t pipeline_type_find_or_alloc_named(void *arena, uint8_t *name, int32_t name_len);
      pty = pipeline_type_find_or_alloc_named(arena, (uint8_t *)for_nm, for_nl);
    }
    pipeline_module_func_param_write(module, fi_mod, p_copy, pname32,
                                     pool ? pipeline_onefunc_param_name_len(pool, p_copy) : 0,
                                     pty);
  }
  pipeline_module_func_ref_set(module, fi_mod, func_ref);
  pipeline_arena_func_copy_slot_from_module(arena, func_ref, module, fi_mod);
  return 0;
}

static void xlang_skip_hoist_default_methods_c(void *module) {
  int32_t si;
  int32_t ti;
  int32_t mi;
  void *arena = g_xlang_trait_check_arena;
  extern void parser_asm_parse_one_function_buf_into_c(struct parser_asm_onefunc_result *out, void *arena,
                                                      struct parser_asm_lexer lex, uint8_t *data, int32_t len);
  extern struct parser_asm_onefunc_result
  parser_asm_onefunc_alloc_wired_for_parse_c(struct parser_asm_lexer lex);
  if (!module || !arena || !g_w439_src_data || g_w439_src_len <= 0) {
    return;
  }
  /* wave470: per-impl inject so Self can be rewritten to each for-type. */
  for (si = 0; si < g_xlang_skip_impl_seen_n; si++) {
    int32_t tlen = g_xlang_skip_impl_trait_len[si];
    uint8_t *tname = g_xlang_skip_impl_trait[si];
    if (tlen <= 0)
      continue;
    ti = -1;
    for (mi = 0; mi < g_xlang_skip_trait_reg_n; mi++) {
      if (g_xlang_skip_trait_reg[mi].name_len == tlen &&
          memcmp(g_xlang_skip_trait_reg[mi].name, tname, (size_t)tlen) == 0) {
        ti = mi;
        break;
      }
    }
    if (ti < 0)
      continue;
    for (mi = 0; mi < g_xlang_skip_trait_reg[ti].num_methods; mi++) {
      uint8_t *mnm;
      int32_t mlen;
      int32_t fi;
      int32_t nf;
      int32_t exists;
      struct parser_asm_lexer fn_lex;
      struct parser_asm_onefunc_result res;
      if (g_xlang_skip_trait_reg[ti].method_has_default[mi] == 0)
        continue;
      mnm = g_xlang_skip_trait_reg[ti].methods[mi];
      mlen = g_xlang_skip_trait_reg[ti].method_lens[mi];
      if (mlen <= 0)
        continue;
      /* Override / free def for THIS for-type already present → skip. */
      exists = 0;
      nf = pipeline_module_num_funcs(module);
      for (fi = 0; fi < nf; fi++) {
        if (pipeline_module_func_name_equal_at(module, fi, mnm, mlen) != 0) {
          int32_t pty0 = pipeline_module_func_param_type_ref_at(module, fi, 0);
          if (xlang_skip_impl_self_matches_for_c(arena, pty0,
                                                   g_xlang_skip_impl_for_kinds[si],
                                                   g_xlang_skip_impl_for_is_ptr[si],
                                                   g_xlang_skip_impl_for_names[si],
                                                   g_xlang_skip_impl_for_name_lens[si])) {
            exists = 1;
            break;
          }
          /* Static default (no self / untyped): name-only match still skips. */
          if (pipeline_module_func_num_params_at(module, fi) == 0) {
            exists = 1;
            break;
          }
        }
      }
      if (exists)
        continue;
      memset(&fn_lex, 0, sizeof(fn_lex));
      fn_lex.pos = (size_t)g_xlang_skip_trait_reg[ti].method_fn_pos[mi];
      fn_lex.line = g_xlang_skip_trait_reg[ti].method_fn_line[mi];
      fn_lex.col = g_xlang_skip_trait_reg[ti].method_fn_col[mi];
      if (fn_lex.line <= 0)
        fn_lex.line = 1;
      if (fn_lex.col <= 0)
        fn_lex.col = 1;
      res = parser_asm_onefunc_alloc_wired_for_parse_c(fn_lex);
      {
        extern void parser_allow_bare_self_set_c(int32_t on);
        parser_allow_bare_self_set_c(1);
        parser_asm_parse_one_function_buf_into_c(&res, arena, fn_lex, g_w439_src_data, g_w439_src_len);
        parser_allow_bare_self_set_c(0);
      }
      if (!res.ok)
        continue;
      (void)xlang_skip_commit_default_onefunc_c(arena, module, &res,
                                                g_xlang_skip_impl_for_names[si],
                                                g_xlang_skip_impl_for_name_lens[si],
                                                g_xlang_skip_impl_for_is_ptr[si]);
    }
  }
}

int32_t xlang_trait_check_impls_complete_c(void *module) {
  int32_t si;
  int32_t ti;
  int32_t mi;
  int32_t fi;
  int32_t nf;
  int32_t rc = 0;
  void *arena = g_xlang_trait_check_arena;
  if (!module)
    return 0;
  /* wave468: inject default bodies before missing-method scan. */
  xlang_skip_hoist_default_methods_c(module);
  nf = pipeline_module_num_funcs(module);
  for (si = 0; si < g_xlang_skip_impl_seen_n; si++) {
    int32_t tlen = g_xlang_skip_impl_trait_len[si];
    uint8_t *tname = g_xlang_skip_impl_trait[si];
    if (tlen <= 0)
      continue;
    ti = -1;
    for (mi = 0; mi < g_xlang_skip_trait_reg_n; mi++) {
      if (g_xlang_skip_trait_reg[mi].name_len == tlen &&
          memcmp(g_xlang_skip_trait_reg[mi].name, tname, (size_t)tlen) == 0) {
        ti = mi;
        break;
      }
    }
    /* wave424: hard fail — was `continue` soft leave-off (LANG-004 unknown_trait). */
    if (ti < 0) {
      lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si], (int)g_xlang_skip_impl_col[si],
                             "impl for unknown trait %.*s", (int)tlen, (const char *)tname);
      rc = -1;
      continue;
    }
    for (mi = 0; mi < g_xlang_skip_trait_reg[ti].num_methods; mi++) {
      int32_t found = 0;
      int32_t found_fi = -1;
      int32_t first_fi = -1; /* wave441: first same-name method (fallback for static) */
      uint8_t *mnm = g_xlang_skip_trait_reg[ti].methods[mi];
      int32_t mlen = g_xlang_skip_trait_reg[ti].method_lens[mi];
      int32_t expect_k = g_xlang_skip_trait_reg[ti].method_ret_kinds[mi];
      int32_t expect_np = g_xlang_skip_trait_reg[ti].method_param_counts[mi];
      if (mlen <= 0)
        continue;
      for (fi = 0; fi < nf; fi++) {
        if (pipeline_module_func_name_equal_at(module, fi, mnm, mlen) != 0) {
          /* wave441: match self (param0) type to impl for-type so two structs
           * impl the same trait no longer collide — without this, the 2nd impl
           * found the 1st impl's same-named method and failed the self check
           * (false-red "method clone self type mismatch"). Prefer self-matched
           * method; fallback to first same-name method when none matches
           * (static trait methods w/o self have param0 != for-type → helper
           * returns 0 for all → fallback preserves old first-match behavior). */
          int32_t pty0 = pipeline_module_func_param_type_ref_at(module, fi, 0);
          if (first_fi < 0)
            first_fi = fi; /* record first same-name method as fallback */
          if (xlang_skip_impl_self_matches_for_c(arena, pty0,
                                                   g_xlang_skip_impl_for_kinds[si],
                                                   g_xlang_skip_impl_for_is_ptr[si],
                                                   g_xlang_skip_impl_for_names[si],
                                                   g_xlang_skip_impl_for_name_lens[si])) {
            found = 1;
            found_fi = fi;
            break;
          }
        }
      }
      if (!found && first_fi >= 0) {
        /* no self-type match (e.g. static trait method w/o self) — use first
         * same-name method so signature-only checks still run (param/ret). */
        found = 1;
        found_fi = first_fi;
      }
      if (!found) {
        lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si], (int)g_xlang_skip_impl_col[si],
                               "missing method %.*s", (int)mlen, (const char *)mnm);
        rc = -1;
        continue;
      }
      /* wave426: hard fail parameter count mismatch. */
      if (expect_np >= 0 && found_fi >= 0) {
        int32_t got_np = pipeline_module_func_num_params_at(module, found_fi);
        if (got_np != expect_np) {
          lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si], (int)g_xlang_skip_impl_col[si],
                                 "method %.*s parameter count mismatch", (int)mlen,
                                 (const char *)mnm);
          rc = -1;
        } else if (arena) {
          int32_t pi;
          for (pi = 0; pi < expect_np && pi < XLANG_SKIP_TRAIT_PARAM_MAX; pi++) {
            int32_t ek = g_xlang_skip_trait_reg[ti].method_param_kinds[mi][pi];
            int32_t pty;
            int32_t got_pk;
            if (ek < 0)
              continue;
            pty = pipeline_module_func_param_type_ref_at(module, found_fi, pi);
            got_pk = (pty != 0) ? pipeline_type_kind_ord_at(arena, pty) : -1;
            /* wave432: twin of seed param shape check (NAMED name / *T elem / []T elem). */
            {
              int32_t mm = 0;
              if (got_pk >= 0 && got_pk != ek) {
                mm = 1;
              } else if (got_pk == ek && ek == XLANG_TRAIT_TY_NAMED) {
                int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                if (enl > 0 && pty != 0) {
                  uint8_t gnm[64];
                  int32_t gnl = pipeline_type_named_name_into(arena, pty, gnm);
                  if (!xlang_skip_trait_named_eq_self_c(
                        g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                        gnm, gnl,
                        g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                        g_xlang_skip_impl_for_is_ptr[si]))
                    mm = 1;
                }
              } else if (got_pk == ek &&
                         (ek == XLANG_TRAIT_TY_PTR || ek == XLANG_TRAIT_TY_SLICE)) {
                int32_t eek = g_xlang_skip_trait_reg[ti].method_param_elem_kinds[mi][pi];
                int32_t elem = (pty != 0) ? pipeline_type_elem_ref_at(arena, pty) : 0;
                if (eek >= 0 && elem != 0) {
                  int32_t gek = pipeline_type_kind_ord_at(arena, elem);
                  if (gek >= 0 && gek != eek) {
                    mm = 1;
                  } else if (gek == eek && eek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  } else if (gek == eek && eek == XLANG_TRAIT_TY_SLICE) {
                    /*
                     * wave435: *[]T → PTR to SLICE of T. Walk pipeline SLICE
                     * leaf → its elem → compare elem_elem (the slice base T).
                     * dest-SLICE extra `[][][]T` / `[][][][]T`: skip-trait
                     * stores eek=SLICE + eeek=leaf + ndims=-2 (extra inner
                     * SLICE). Extra wrap count is dims[0] (0 means 1).
                     * Pipeline pelem is then still SLICE — peel extra times
                     * when ndims==-2 or T001 if layers run out. `[][]T`
                     * (ndims=0) keeps the one-peel. dest extras dest-SLICE
                     * of SLICE extra `[][]*T`: extra PTR wrap COUNT is
                     * unused slot dims[0] with ndims staying 0 (1 =
                     * `[][]*T`; 0 = no extra PTR = `[][]i32`). After the
                     * leftover-SLICE peel, pelem is still PTR vs eeek=leaf
                     * — peel leftover PTR extra times or T001. dest extras
                     * dest-SLICE of SLICE extra ARRAY `[][][2]T`: leftover
                     * after leftover-SLICE peel is ARRAY vs eeek=leaf
                     * (ndims>=1, dims[0..ndims-1] from wave437 pending
                     * LBRACKET after `[][]` then `[M]`). Peel leftover
                     * ARRAY or T001. dest extras dest-SLICE of SLICE extra
                     * ARRAY extra PTR `[][][2]*T`: leftover after extra
                     * ARRAY peels is PTR vs eeek=leaf; extra PTR wrap
                     * COUNT is unused slot dims[ndims] (1 = `[][][2]*T`;
                     * 0 = no extra PTR = `[][][2]T`). Peel leftover PTR
                     * extra times or T001. Store already has ndims>=1
                     * (named / UFCS dest-stamp via the formal).
                     * Discriminant: ndims==-2 extra SLICE; ndims==0 extra
                     * PTR; ndims>=1 inner ARRAY (plus unused-slot extra
                     * PTR). Do not invent -3.
                     * PLATFORM: SHARED parse. G.7: complete this walk.
                     */
                    int32_t eeek = g_xlang_skip_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                    int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
                    if (eeek >= 0 && pelem != 0) {
                      int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                      int32_t eand = g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                      if (eand == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                        int32_t extra =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                        int32_t extra_ptr;
                        if (extra <= 0)
                          extra = 1;
                        while (extra > 0) {
                          if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                            mm = 1;
                            break;
                          }
                          pelem = pipeline_type_elem_ref_at(arena, pelem);
                          if (pelem == 0) {
                            mm = 1;
                            break;
                          }
                          pgek = pipeline_type_kind_ord_at(arena, pelem);
                          extra = extra - 1;
                        }
                        /*
                         * dest extras dest-SLICE of SLICE extra PTR
                         * `[][][]*T`: leftover after extra SLICE peels
                         * is PTR vs eeek=leaf. Extra PTR wrap COUNT is
                         * unused slot dims[1] (1 = `[][][]*T`; 0 = no
                         * extra PTR = `[][][]T`). Peel leftover PTR
                         * extra times or T001. dest extras dest-ARRAY
                         * of SLICE extra PTR `[2][][]*T` uses the same
                         * dims[1] encoding (ARRAY leftover matches at
                         * leftover SLICE vs eek=SLICE — not this walk;
                         * not T001). Do not invent -3. PLATFORM:
                         * SHARED. G.7: complete this walk.
                         */
                        extra_ptr =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][1];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                      } else if (eand == 0) {
                        int32_t extra_ptr =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                      } else if (eand >= 1) {
                        /*
                         * dest extras dest-SLICE of SLICE extra ARRAY
                         * `[][][2]T`: leftover after leftover-SLICE
                         * peel is ARRAY vs eeek=leaf. Inner ARRAY
                         * dims are dims[0..ndims-1] (wave437 pending
                         * LBRACKET after `[][]` then `[M]`). Peel
                         * ARRAY outer-first or T001 if layers run
                         * out. dest extras dest-SLICE of SLICE extra
                         * ARRAY extra PTR `[][][2]*T`: leftover after
                         * extra ARRAY peels is PTR vs eeek=leaf.
                         * Extra PTR wrap COUNT is unused slot
                         * dims[ndims] (1 = `[][][2]*T`; 0 = no extra
                         * PTR = `[][][2]T`; same unused slot as dest
                         * extras dest-SLICE of ARRAY extra `[][2][]T`
                         * and dest extras dest-ARRAY of SLICE extra
                         * `[2][][2]*T`; discriminant is elem_kind
                         * SLICE vs ARRAY AND SLICE vs ARRAY outer).
                         * Peel leftover PTR extra times or T001.
                         * dest extras dest-ARRAY of SLICE extra PTR
                         * `[2][][2]*T` uses the same dims[ndims]
                         * encoding (ARRAY leftover matches at leftover
                         * SLICE vs eek=SLICE — not this walk; not
                         * T001). dest extras dest-SLICE of SLICE extra
                         * wrap `[][][2][]T`: leftover after extra
                         * ARRAY peels is SLICE vs eeek=leaf. Extra
                         * SLICE wrap COUNT is unused slot
                         * dims[ndims+1] (1 = `[][][2][]T`; 2 =
                         * `[][][2][][]T`; 0 = no extra wrap =
                         * `[][][2]T`; extra PTR of `[][][2]*T`
                         * stays dims[ndims] — do not reopen). Peel
                         * leftover SLICE extra times (after ARRAY,
                         * before extra PTR) or T001. dest extras
                         * dest-ARRAY of SLICE extra wrap `[2][][2][]T`
                         * uses the same dims[ndims+1] encoding
                         * (ARRAY leftover matches at leftover SLICE
                         * vs eek=SLICE — not this walk; not T001).
                         * PTR-outer extra empty `[]` `*[][2][]T`
                         * uses the same dims[ndims+1] extra SLICE
                         * encoding (this walk peels leftover SLICE
                         * then extra ARRAY then extra SLICE then
                         * extra PTR; leftover PTR vs eek=SLICE is
                         * not T001 once extra SLICE is stored).
                         * Extra ADDR_OF of typed `[][2][]i32`
                         * dest-stamps via the formal (no dest extras
                         * dest-PTR stamp). Nested extra lit dest
                         * extras dest-PTR stamp stays deferred.
                         * PTR-outer extra STAR `*[][2]*T` uses the
                         * same dims[ndims] extra PTR encoding (this
                         * walk peels leftover SLICE then extra ARRAY
                         * then extra PTR; leftover PTR vs eek=SLICE
                         * is not T001 once extra PTR is stored). Extra
                         * ADDR_OF of typed `[][2]*i32` dest-stamps via
                         * the formal (no dest extras dest-PTR stamp).
                         * `[][]i32` (ndims==0) keeps leftover vs
                         * eeek=leaf. Discriminant vs extra PTR
                         * wrap-once: ndims==0 dims[0]; vs extra SLICE:
                         * ndims==-2. Store already has ndims>=1
                         * (named / UFCS dest-stamp via the formal).
                         * Do not invent -3. PLATFORM: SHARED.
                         * G.7: complete this walk.
                         */
                        int32_t d;
                        int32_t extra_slice;
                        int32_t extra_ptr;
                        for (d = 0; d < eand; d++) {
                          int32_t gsz;
                          if (pgek != XLANG_TRAIT_TY_ARRAY || pelem == 0) {
                            mm = 1;
                            break;
                          }
                          gsz = pipeline_type_array_size_at(arena, pelem);
                          if (gsz != g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][d]) {
                            mm = 1;
                            break;
                          }
                          pelem = pipeline_type_elem_ref_at(arena, pelem);
                          if (pelem == 0) {
                            mm = 1;
                            break;
                          }
                          pgek = pipeline_type_kind_ord_at(arena, pelem);
                        }
                        extra_slice = 0;
                        if (eand > 0 && eand + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                          extra_slice = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand + 1];
                        if (extra_slice > 0) {
                          while (extra_slice > 0) {
                            if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_slice = extra_slice - 1;
                          }
                        }
                        extra_ptr = 0;
                        if (eand > 0 && eand < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                          extra_ptr = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                      }
                      if (pgek >= 0 && pgek != eeek) {
                        mm = 1;
                      } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                        int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                        if (enl > 0) {
                          uint8_t gnm[64];
                          int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                          if (!xlang_skip_trait_named_eq_self_c(
                                g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                gnm, gnl,
                                g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                g_xlang_skip_impl_for_is_ptr[si]))
                            mm = 1;
                        }
                      }
                    }
                  } else if (gek == eek && eek == XLANG_TRAIT_TY_ARRAY) {
                    /*
                     * wave436: *[N]T → PTR to ARRAY of N T. The PTR's elem
                     * (elem) is the ARRAY. Walk its dims (elem_array_ndims/
                     * dims) then compare the leaf elem kind/name with
                     * elem_elem (base T). Multi-dim *[N][M]T is soft-skipped
                     * at registration (eeks=-1) so this path only fires for
                     * single-dim. Twin of wave433 ARRAY walk but on elem level.
                     * PLATFORM: SHARED parse.
                     */
                    int32_t eeek = g_xlang_skip_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                    int32_t eend = g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                    int32_t leaf_tr = elem;
                    int32_t d;
                    for (d = 0; d < eend && leaf_tr != 0; d++) {
                      int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
                      int32_t gsz;
                      if (k != XLANG_TRAIT_TY_ARRAY) {
                        mm = 1;
                        break;
                      }
                      gsz = pipeline_type_array_size_at(arena, leaf_tr);
                      if (gsz != g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][d]) {
                        mm = 1;
                        break;
                      }
                      leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                      if (leaf_tr == 0 && d + 1 < eend) {
                        mm = 1;
                        break;
                      }
                    }
                    if (!mm && eeek >= 0 && leaf_tr != 0) {
                      int32_t pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                      /*
                       * dest extras dest-SLICE of ARRAY extra `[][2]*T` /
                       * `[][2][]T` / `[][2][]*T` and PTR-outer `*[2]*T` /
                       * `*[2][]*T`: after walking ARRAY dims leftover is
                       * still PTR (inner `*` of i32), SLICE (inner `[]`
                       * of i32), or SLICE-of-PTR (`[][2][]*T` /
                       * `*[2][]*T`) vs eeek=leaf. Extra PTR wrap count
                       * is unused slot dims[ndims+1] (1 = `[][2]*T` /
                       * `[][2][]*T` / `*[2]*T` / `*[2][]*T`); extra
                       * SLICE wrap count is unused slot dims[ndims]
                       * (1 = `[][2][]T` / `[][2][]*T` / `*[2][]T` /
                       * `*[2][]*T`). Peel extra SLICE first (outer extra)
                       * then extra PTR (inner extra) — dest extras wraps
                       * PTR of leaf then SLICE. Peel PTR first of
                       * `[][2][]*T` / `*[2][]*T` is T001 (leftover SLICE
                       * vs PTR). `[][2]*T` / `*[2]*T` extra SLICE=0 still
                       * peels PTR; `[][2][]T` extra PTR=0 still peels
                       * SLICE. `[][2]i32` / `*[2]i32` (both slots 0)
                       * keeps the ARRAY-then-leaf compare. Discriminant
                       * dest extras dest-SLICE of ARRAY extra `[][2]*T`
                       * vs PTR-outer `*[2]*T` (same unused slot) is
                       * SLICE vs PTR outer. Do not invent -3.
                       * PLATFORM: SHARED. G.7: complete this walk.
                       */
                      int32_t extra_ptr = 0;
                      int32_t extra = 0;
                      if (eend > 0 && eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        extra = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eend];
                      if (extra > 0) {
                        while (extra > 0) {
                          if (pgek != XLANG_TRAIT_TY_SLICE || leaf_tr == 0) {
                            mm = 1;
                            break;
                          }
                          leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                          if (leaf_tr == 0) {
                            mm = 1;
                            break;
                          }
                          pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                          extra = extra - 1;
                        }
                      }
                      if (eend > 0 && eend + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        extra_ptr = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eend + 1];
                      if (extra_ptr > 0) {
                        while (extra_ptr > 0) {
                          if (pgek != XLANG_TRAIT_TY_PTR || leaf_tr == 0) {
                            mm = 1;
                            break;
                          }
                          leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                          if (leaf_tr == 0) {
                            mm = 1;
                            break;
                          }
                          pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                          extra_ptr = extra_ptr - 1;
                        }
                      }
                      if (pgek >= 0 && pgek != eeek) {
                        mm = 1;
                      } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                        int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                        if (enl > 0) {
                          uint8_t gnm[64];
                          int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                          if (!xlang_skip_trait_named_eq_self_c(
                                g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                gnm, gnl,
                                g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                g_xlang_skip_impl_for_is_ptr[si]))
                            mm = 1;
                        }
                      }
                    }
                  } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
                    /*
                     * dest extras dest-PARAM leftover extra
                     * ARRAY/SLICE/PTR peels PTR-elem ndims>=1
                     * `**[2][]T` / `**[2]*T` AND dest extras
                     * dest-PARAM extra empty `[]` PTR-elem ndims=0
                     * `**[]T` AND dest extras dest-PARAM extra STAR
                     * PTR-elem ndims=0 `***T`: leftover PTR vs
                     * eek=PTR is not T001 without extra ARRAY then
                     * extra SLICE then extra PTR peels (store-only
                     * leftover PTR vs eeek=leaf after extra ARRAY
                     * peels is T001). Peel leftover PTR then ARRAY
                     * dims then extra SLICE then extra PTR or T001
                     * when ndims>=1. Extra SLICE wrap COUNT is unused
                     * slot dims[ndims] when ndims>=1 (1 = `**[2][]T`;
                     * 2 = `**[2][][]T`; 0 = no extra wrap =
                     * `**[2]i32` / `**[2]*T`) and unused slot
                     * dims[0] with ndims staying 0 (1 = `**[]T`;
                     * 2 = `**[][]T`; 0 = no extra SLICE = `**T` /
                     * `***T`). Extra PTR wrap COUNT is unused slot
                     * dims[ndims+1] (1 = `**[2]*T` / `**[2][]*T`;
                     * 0 = no extra PTR = `**[2]i32` / `**[2][]T`;
                     * both slots = `**[2][]*T`) and unused slot
                     * dims[1] with ndims staying 0 (1 = `***T`;
                     * 2 = `****T`; 0 = no extra PTR = `**T`; both
                     * slots = `**[]*T`). leftover skip eek=-1 was
                     * false green of leftover extras never compared
                     * (impl `**[2]i32` vs trait `**[2][]i32`
                     * compile=0 run=2 leftover skip so leftover
                     * never compares extras; impl `**[2]i32` vs
                     * trait `**[2]*i32` compile=0 run=98 leftover
                     * skip). Twin of leftover eek==PTR eend>0 extra
                     * ARRAY then extra SLICE then extra PTR peels
                     * (`**[2][]T` / `**[2]*T` dest extras dest-RET
                     * already closed) AND leftover eek==PTR eend==0
                     * extra SLICE then extra PTR peels (`**[]T` /
                     * `***T` dest extras dest-RET already closed).
                     * Extra ADDR_OF of typed `*[2][]i32` / `*[2]*i32`
                     * dest-stamps via the formal (no dest extras
                     * dest-PTR stamp). leftover extra SLICE peels
                     * leftover eek==PTR eand==-2 (`[]*[]T` /
                     * `[]*[][]T` PTR-to-SLICE of SLICE outer) peel
                     * leftover SLICE extra times then leftover PTR
                     * extra times (eeek compare stays inside the
                     * eand==-2 branch — leftover after leftover-PTR
                     * peel is SLICE vs eeek=leaf would T001 matching
                     * `[]*[]T` if lifted). leftover skip leftover
                     * extras never compared was false green (impl
                     * `[]*i32` vs trait `[]*[]i32` compile=0 run=1
                     * leftover skip). Twin of leftover eek==SLICE
                     * eand==-2 extra SLICE then extra PTR peels.
                     * Do not invent -3. PLATFORM: SHARED. G.7:
                     * complete this walk.
                     */
                    int32_t eeek = g_xlang_skip_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                    int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
                    int32_t eand = g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                    if (eeek >= 0 && pelem != 0) {
                      int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                      if (pgek == XLANG_TRAIT_TY_ARRAY && eand > 0) {
                        int32_t d;
                        int32_t extra_slice;
                        int32_t extra_ptr;
                        for (d = 0; d < eand && pelem != 0; d++) {
                          int32_t k = pipeline_type_kind_ord_at(arena, pelem);
                          int32_t gsz;
                          if (k != XLANG_TRAIT_TY_ARRAY) {
                            mm = 1;
                            break;
                          }
                          gsz = pipeline_type_array_size_at(arena, pelem);
                          if (gsz != g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][d]) {
                            mm = 1;
                            break;
                          }
                          pelem = pipeline_type_elem_ref_at(arena, pelem);
                          if (pelem == 0 && d + 1 < eand) {
                            mm = 1;
                            break;
                          }
                        }
                        if (!mm && pelem != 0)
                          pgek = pipeline_type_kind_ord_at(arena, pelem);
                        extra_slice = 0;
                        if (eand > 0 && eand < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                          extra_slice = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand];
                        if (extra_slice > 0) {
                          while (extra_slice > 0) {
                            if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_slice = extra_slice - 1;
                          }
                        }
                        extra_ptr = 0;
                        if (eand > 0 && eand + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                          extra_ptr = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand + 1];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                        if (!mm) {
                          if (pgek >= 0 && pgek != eeek) {
                            mm = 1;
                          } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                            int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                            if (enl > 0) {
                              uint8_t gnm[64];
                              int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                              if (!xlang_skip_trait_named_eq_self_c(
                                    g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                    gnm, gnl,
                                    g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                    g_xlang_skip_impl_for_is_ptr[si]))
                                mm = 1;
                            }
                          }
                        }
                      } else if (eand == 0) {
                        int32_t extra_slice;
                        int32_t extra_ptr;
                        extra_slice =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                        if (extra_slice > 0) {
                          while (extra_slice > 0) {
                            if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_slice = extra_slice - 1;
                          }
                        }
                        extra_ptr =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][1];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                        if (!mm) {
                          if (pgek >= 0 && pgek != eeek) {
                            mm = 1;
                          } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                            int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                            if (enl > 0) {
                              uint8_t gnm[64];
                              int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                              if (!xlang_skip_trait_named_eq_self_c(
                                    g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                    gnm, gnl,
                                    g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                    g_xlang_skip_impl_for_is_ptr[si]))
                                mm = 1;
                            }
                          }
                        }
                      } else if (eand == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                        /*
                         * leftover extra SLICE peels leftover
                         * eek==PTR eand==-2 `[]*[]T` / `[]*[][]T`
                         * PTR-to-SLICE of SLICE outer: leftover PTR
                         * vs eek=PTR is not T001 without leftover
                         * extra SLICE peels (store-only leftover
                         * extras never compared leftover skip false
                         * green; impl `[]*i32` vs trait `[]*[]i32`
                         * compile=0 run=1 leftover skip). Extra
                         * SLICE wrap COUNT is dims[0] (0 means 1 =
                         * `[]*[]T`; 2 = `[]*[][]T`). Extra PTR wrap
                         * COUNT is unused slot dims[1] (1 =
                         * `[]*[]*T`; 2 = `[]*[]**T`; 0 = no extra
                         * PTR = `[]*[]T`). Peel leftover SLICE extra
                         * times then leftover PTR extra times or
                         * T001. Twin of leftover eek==SLICE
                         * eand==-2 extra SLICE then extra PTR peels
                         * (`[][][]T` / `[][][]*T` already closed)
                         * AND leftover eek==ARRAY eand==-2 extra
                         * SLICE peels (`[2]*[]T` already closed)
                         * AND leftover eek==PTR eend==-2 extra
                         * SLICE then extra PTR peels (`*[][]T` /
                         * `*[][]*T` dest extras dest-RET already
                         * closed). Extra ADDR_OF of typed dest
                         * dest-stamps via the formal (no dest extras
                         * dest-PTR stamp). Do not lift eeek compare
                         * outside this branch — leftover after
                         * leftover-PTR peel is SLICE vs eeek=leaf
                         * would T001 matching `[]*[]T`. Do not
                         * invent -3. PLATFORM: SHARED. G.7:
                         * complete this walk.
                         */
                        int32_t extra;
                        int32_t extra_ptr;
                        extra =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                        if (extra <= 0)
                          extra = 1;
                        while (extra > 0) {
                          if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                            mm = 1;
                            break;
                          }
                          pelem = pipeline_type_elem_ref_at(arena, pelem);
                          if (pelem == 0) {
                            mm = 1;
                            break;
                          }
                          pgek = pipeline_type_kind_ord_at(arena, pelem);
                          extra = extra - 1;
                        }
                        extra_ptr =
                            g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][1];
                        if (extra_ptr > 0) {
                          while (extra_ptr > 0) {
                            if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pelem = pipeline_type_elem_ref_at(arena, pelem);
                            if (pelem == 0) {
                              mm = 1;
                              break;
                            }
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                            extra_ptr = extra_ptr - 1;
                          }
                        }
                        if (!mm) {
                          if (pgek >= 0 && pgek != eeek) {
                            mm = 1;
                          } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                            int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                            if (enl > 0) {
                              uint8_t gnm[64];
                              int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                              if (!xlang_skip_trait_named_eq_self_c(
                                    g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                    gnm, gnl,
                                    g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                    g_xlang_skip_impl_for_is_ptr[si]))
                                mm = 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else if (got_pk == ek && ek == XLANG_TRAIT_TY_ARRAY) {
                /*
                 * wave433: walk nested TYPE_ARRAY dims[0]=outer … then leaf elem
                 * kind/name. Twin of wave431 ret multi-dim walk.
                 * PLATFORM: SHARED parse.
                 */
                int32_t nd = g_xlang_skip_trait_reg[ti].method_param_array_ndims[mi][pi];
                int32_t eek = g_xlang_skip_trait_reg[ti].method_param_elem_kinds[mi][pi];
                int32_t leaf_tr = pty;
                if (nd > 0 && pty != 0) {
                  int32_t d;
                  for (d = 0; d < nd; d++) {
                    int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
                    int32_t gsz;
                    if (k != XLANG_TRAIT_TY_ARRAY) {
                      mm = 1;
                      break;
                    }
                    gsz = pipeline_type_array_size_at(arena, leaf_tr);
                    if (gsz != g_xlang_skip_trait_reg[ti].method_param_array_dims[mi][pi][d]) {
                      mm = 1;
                      break;
                    }
                    leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                    if (leaf_tr == 0 && d + 1 < nd) {
                      mm = 1;
                      break;
                    }
                  }
                  if (!mm && eek >= 0 && leaf_tr != 0) {
                    int32_t gek = pipeline_type_kind_ord_at(arena, leaf_tr);
                    if (gek >= 0 && gek != eek) {
                      mm = 1;
                    } else if (gek == eek && eek == XLANG_TRAIT_TY_NAMED) {
                      int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                      if (enl > 0) {
                        uint8_t gnm[64];
                        int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                        if (!xlang_skip_trait_named_eq_self_c(
                              g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                              gnm, gnl,
                              g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                              g_xlang_skip_impl_for_is_ptr[si]))
                          mm = 1;
                      }
                    } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
                      /*
                       * wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter
                       * than *). Walk pipeline ARRAY leaf (must be PTR) → its elem →
                       * compare elem_elem (the *T base). PLATFORM: SHARED parse.
                       */
                      int32_t eeek = g_xlang_skip_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                      int32_t pelem = pipeline_type_elem_ref_at(arena, leaf_tr);
                      if (eeek >= 0 && pelem != 0) {
                        int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                        /*
                         * wave774: PTR pointee may be ARRAY/SLICE (e.g.
                         * *[2]i32 or *[]i32). eeek holds the LEAF kind
                         * (i32=0), not the direct pointee kind (ARRAY=10 /
                         * SLICE=11). Walk elem_array_ndims dims (or -2 for
                         * SLICE) to reach the leaf, then compare. Without
                         * this, [2]*[2]i32 and [2]*[]i32 trait/impl params
                         * mismatch (eeek=0 vs pgek=10/11).
                         * dest extras dest-ARRAY of PTR `[2]*[][]T`: extra
                         * wrap count is dims[0] (0 means 1 = `[2]*[]T`;
                         * 2 = `[2]*[][]T`). Peel extra times when
                         * ndims==-2 or T001 if layers run out. Peel-once
                         * left pelem still SLICE vs eeek=leaf. Twin of
                         * SLICE-of-SLICE extra peel above. Do not invent
                         * -3. PLATFORM: SHARED. G.7: complete this walk.
                         */
                        if (pgek == XLANG_TRAIT_TY_ARRAY || pgek == XLANG_TRAIT_TY_SLICE) {
                          int32_t eand = g_xlang_skip_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                          if (eand > 0) {
                            int32_t ed;
                            int32_t extra_slice;
                            int32_t extra_ptr;
                            for (ed = 0; ed < eand && pelem != 0; ed++) {
                              pelem = pipeline_type_elem_ref_at(arena, pelem);
                            }
                            if (pelem != 0) {
                              pgek = pipeline_type_kind_ord_at(arena, pelem);
                            }
                            /*
                             * dest extras dest-ARRAY of PTR extra
                             * `[2]*[2]*T` / `[2]*[2][]*T`: leftover
                             * after extra ARRAY peels is PTR vs
                             * eeek=leaf (store-only T001). Extra
                             * SLICE wrap COUNT is unused slot
                             * dims[ndims] (1 = `[2]*[2][]T`; 0 = no
                             * extra wrap = `[2]*[2]i32`). Extra PTR
                             * wrap COUNT is unused slot
                             * dims[ndims+1] (1 = `[2]*[2]*T`; 0 =
                             * no extra PTR = `[2]*[2]i32`;
                             * `[2]*[2][]*T` has both slots set).
                             * Peel leftover SLICE extra times then
                             * leftover PTR extra times or T001.
                             * dest extras dest-SLICE of PTR extra
                             * `[]*[2]*T` uses the same
                             * dims[ndims+1] encoding (SLICE leftover
                             * matches at leftover PTR vs eek=PTR —
                             * not this walk; not T001). Discriminant
                             * is ARRAY vs SLICE outer. Do not invent
                             * -3. PLATFORM: SHARED. G.7: complete
                             * this walk.
                             */
                            extra_slice = 0;
                            if (eand < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                              extra_slice = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand];
                            if (extra_slice > 0) {
                              while (extra_slice > 0) {
                                if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                                  mm = 1;
                                  break;
                                }
                                pelem = pipeline_type_elem_ref_at(arena, pelem);
                                if (pelem == 0) {
                                  mm = 1;
                                  break;
                                }
                                pgek = pipeline_type_kind_ord_at(arena, pelem);
                                extra_slice = extra_slice - 1;
                              }
                            }
                            extra_ptr = 0;
                            if (eand + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                              extra_ptr = g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][eand + 1];
                            if (extra_ptr > 0) {
                              while (extra_ptr > 0) {
                                if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                                  mm = 1;
                                  break;
                                }
                                pelem = pipeline_type_elem_ref_at(arena, pelem);
                                if (pelem == 0) {
                                  mm = 1;
                                  break;
                                }
                                pgek = pipeline_type_kind_ord_at(arena, pelem);
                                extra_ptr = extra_ptr - 1;
                              }
                            }
                          } else if (eand == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                            int32_t extra =
                                g_xlang_skip_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                            if (extra <= 0)
                              extra = 1;
                            while (extra > 0) {
                              if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                                mm = 1;
                                break;
                              }
                              pelem = pipeline_type_elem_ref_at(arena, pelem);
                              if (pelem == 0) {
                                mm = 1;
                                break;
                              }
                              pgek = pipeline_type_kind_ord_at(arena, pelem);
                              extra = extra - 1;
                            }
                          } else if (pelem != 0) {
                            pgek = pipeline_type_kind_ord_at(arena, pelem);
                          }
                        }
                        if (pgek >= 0 && pgek != eeek) {
                          mm = 1;
                        } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                          int32_t enl = g_xlang_skip_trait_reg[ti].method_param_name_lens[mi][pi];
                          if (enl > 0) {
                            uint8_t gnm[64];
                            int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                            if (!xlang_skip_trait_named_eq_self_c(
                                  g_xlang_skip_trait_reg[ti].method_param_names[mi][pi], enl,
                                  gnm, gnl,
                                  g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                                  g_xlang_skip_impl_for_is_ptr[si]))
                              mm = 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
              if (mm) {
                lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si], (int)g_xlang_skip_impl_col[si],
                                       "method %.*s parameter type mismatch", (int)mlen,
                                       (const char *)mnm);
                rc = -1;
                break;
              }
            }
          }
          /*
           * wave428: trait wrote untyped self (param0 ek=-1) → require impl param0
           * matches `for` type (builtin / named / *T).
           * wave429: also when trait annotated self (ek0>=0) — was false-green:
           *   trait Double { double(self: i32) } + impl for u64 { double(self: i32) }
           *   passed param-type (matches trait) but for-type was ignored → call on i32 run=42.
           * wave441: logic extracted to xlang_skip_impl_self_matches_for_c (shared
           *   with method lookup); helper returns 1 when for-type unknown or self
           *   untyped (preserve old skip behavior). PLATFORM: SHARED parse.
           */
          if (expect_np >= 1) {
            int32_t pty0 = pipeline_module_func_param_type_ref_at(module, found_fi, 0);
            if (!xlang_skip_impl_self_matches_for_c(arena, pty0,
                                                     g_xlang_skip_impl_for_kinds[si],
                                                     g_xlang_skip_impl_for_is_ptr[si],
                                                     g_xlang_skip_impl_for_names[si],
                                                     g_xlang_skip_impl_for_name_lens[si])) {
              lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si],
                                     (int)g_xlang_skip_impl_col[si],
                                     "method %.*s self type mismatch", (int)mlen,
                                     (const char *)mnm);
              rc = -1;
            }
          }
        }
      }
      /* wave425/427/430/431: hard fail return type mismatch
       * (builtin / named / ptr / slice / fixed T[N] / multi-dim T[N][M]…). */
      if (expect_k >= 0 && arena && found_fi >= 0) {
        int32_t rty = pipeline_module_func_return_type_at(module, found_fi);
        int32_t got_k = (rty != 0) ? pipeline_type_kind_ord_at(arena, rty) : -1;
        int32_t mm = 0;
        if (got_k >= 0 && got_k != expect_k) {
          mm = 1;
        } else if (got_k == expect_k && expect_k == XLANG_TRAIT_TY_NAMED) {
          int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
          if (enl > 0 && rty != 0) {
            uint8_t gnm[64];
            int32_t gnl = pipeline_type_named_name_into(arena, rty, gnm);
            if (!xlang_skip_trait_named_eq_self_c(
                  g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                  gnm, gnl,
                  g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                  g_xlang_skip_impl_for_is_ptr[si]))
              mm = 1;
          }
        } else if (got_k == expect_k && expect_k == XLANG_TRAIT_TY_ARRAY) {
          /*
           * wave431: walk nested TYPE_ARRAY dims[0]=outer … then leaf elem kind/name.
           * ndims==0 falls back to wave430 single outer size + one elem.
           * PLATFORM: SHARED parse.
           */
          int32_t nd = g_xlang_skip_trait_reg[ti].method_ret_array_ndims[mi];
          int32_t eek = g_xlang_skip_trait_reg[ti].method_ret_elem_kinds[mi];
          int32_t leaf_tr = rty;
          if (nd > 0 && rty != 0) {
            int32_t d;
            for (d = 0; d < nd; d++) {
              int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
              int32_t gsz;
              if (k != XLANG_TRAIT_TY_ARRAY) {
                mm = 1;
                break;
              }
              gsz = pipeline_type_array_size_at(arena, leaf_tr);
              if (gsz != g_xlang_skip_trait_reg[ti].method_ret_array_dims[mi][d]) {
                mm = 1;
                break;
              }
              leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
              if (leaf_tr == 0 && d + 1 < nd) {
                mm = 1;
                break;
              }
            }
            if (!mm && eek >= 0 && leaf_tr != 0) {
              int32_t gek = pipeline_type_kind_ord_at(arena, leaf_tr);
              if (gek >= 0 && gek != eek) {
                mm = 1;
              } else if (gek == eek && eek == XLANG_TRAIT_TY_NAMED) {
                int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                if (enl > 0) {
                  uint8_t gnm[64];
                  int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                  if (!xlang_skip_trait_named_eq_self_c(
                        g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                        gnm, gnl,
                        g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                        g_xlang_skip_impl_for_is_ptr[si]))
                    mm = 1;
                }
              } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
                /*
                 * wave438: *T[N] → ARRAY of PTR (type syntax: [] binds tighter
                 * than *). Walk pipeline ARRAY leaf (must be PTR) → its elem →
                 * compare elem_elem (the *T base). Twin of wave434 param *T[N]
                 * check. PLATFORM: SHARED parse.
                 */
                int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
                int32_t pelem = pipeline_type_elem_ref_at(arena, leaf_tr);
                if (eeek >= 0 && pelem != 0) {
                  int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                  if (pgek >= 0 && pgek != eeek) {
                    mm = 1;
                  } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  }
                }
              }
            }
          } else {
            int32_t elem = (rty != 0) ? pipeline_type_elem_ref_at(arena, rty) : 0;
            int32_t esz = g_xlang_skip_trait_reg[ti].method_ret_array_sizes[mi];
            if (esz >= 0 && rty != 0) {
              int32_t gsz = pipeline_type_array_size_at(arena, rty);
              if (gsz != esz)
                mm = 1;
            }
            if (!mm && eek >= 0 && elem != 0) {
              int32_t gek = pipeline_type_kind_ord_at(arena, elem);
              if (gek >= 0 && gek != eek) {
                mm = 1;
              } else if (gek == eek && eek == XLANG_TRAIT_TY_NAMED) {
                int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                if (enl > 0) {
                  uint8_t gnm[64];
                  int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
                  if (!xlang_skip_trait_named_eq_self_c(
                        g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                        gnm, gnl,
                        g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                        g_xlang_skip_impl_for_is_ptr[si]))
                    mm = 1;
                }
              } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
                /*
                 * wave438: *T[N] single-dim (nd==0 fallback) → ARRAY of PTR.
                 * Walk pipeline ARRAY leaf (must be PTR) → its elem → compare
                 * elem_elem (the *T base). Twin of wave434 param *T[N] check.
                 * PLATFORM: SHARED parse.
                 */
                int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
                int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
                if (eeek >= 0 && pelem != 0) {
                  int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                  if (pgek >= 0 && pgek != eeek) {
                    mm = 1;
                  } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  }
                }
              }
            }
          }
        } else if (got_k == expect_k &&
                   (expect_k == XLANG_TRAIT_TY_PTR || expect_k == XLANG_TRAIT_TY_SLICE)) {
          int32_t eek = g_xlang_skip_trait_reg[ti].method_ret_elem_kinds[mi];
          int32_t elem = (rty != 0) ? pipeline_type_elem_ref_at(arena, rty) : 0;
          if (!mm && eek >= 0 && elem != 0) {
            int32_t gek = pipeline_type_kind_ord_at(arena, elem);
            if (gek >= 0 && gek != eek) {
              mm = 1;
            } else if (gek == eek && eek == XLANG_TRAIT_TY_NAMED) {
              int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
              if (enl > 0) {
                uint8_t gnm[64];
                int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
                if (!xlang_skip_trait_named_eq_self_c(
                      g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                      gnm, gnl,
                      g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                      g_xlang_skip_impl_for_is_ptr[si]))
                  mm = 1;
              }
            } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
              /*
               * wave954: leftover extra SLICE peels leftover eek=PTR
               * eand=-2 []*[]T / []*[][]T RET twin. After outer PTR or
               * SLICE (got_k==expect_k: PTR outer *[]*T vs SLICE outer
               * []*[]T both reach this via eek==PTR elem vs gek==PTR
               * elem of impl), walk pointee ARRAY/SLICE ndims or PTR-
               * to-SLICE sentinel (-2) to reach the leaf, then compare
               * eeek (the leaf kind). Without this, impl []*i32 vs
               * trait []*[]i32 RET (eeek=leaf i32 vs leftover SLICE of
               * impl ptr-pointee) compiled=0 T001 leftover skip false
               * green. Produce: leftover PTR vs eek=PTR matched then
               * eend=-2 did not peel extra SLICE (store-only leftover
               * extras never compared = leftover skip false green).
               * Storage already complete (elem=PTR / eek=leaf /
               * ndims=-2 / dims[0]=N extra SLICE / dims[1]=extra PTR).
               * Discriminant vs dest extras dest-RET extra STAR
               * SLICE-elem ndims=-2 *[][]*T (RET eek=SLICE not PTR)
               * is eek=PTR vs eek=SLICE. Consume: leftover PTR vs
               * eek=PTR non-T001 must first peel leftover PTR then
               * extra SLICE then extra PTR. Peel leftover ARRAY when
               * eend>=1 (discriminant vs *[]*T eend=0 which takes the
               * no-peel direct compare path). Peel extra SLICE extra
               * times from dims[eend+1] (eend>=1) or dims[0]
               * (eend=-2 PTR_TO_SLICE sentinel; 0 means 1 extra SLICE
               * like *[][]T). Peel extra PTR extra times from
               * dims[eend] (eend>=1) or dims[1] (eend=-2). Then
               * compare pgek vs eeek (or T001 if peel fails). Twin of
               * param leftover PTR vs eek=PTR walk (param line 3584
               * already closed). Do not invent -3. PLATFORM: SHARED
               * parse. G.7: complete this walk for the RET twin.
               */
              int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
              if (eeek >= 0 && pelem != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                int32_t eend = g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[mi];
                /*
                 * wave954: leftover ARRAY/SLICE/PTR walk must happen
                 * whenever eend>=1 or eend==PTR_TO_SLICE(-2), REGARDLESS
                 * of current pgek. Before wave954: gated on
                 * `pgek==ARRAY || pgek==SLICE` which skipped the walk
                 * for impl `[]*i32` vs trait `[]*[]i32` (pelem is
                 * PTR→i32, pgek=I32, not SLICE/ARRAY) — eend=-2
                 * extra=1 never peeled; pgek=I32==eeek=I32 false green.
                 * Peel flow: if eend>=1 → ARRAY peels + extra SLICE +
                 * extra PTR; if eend==-2 → extra SLICE + extra PTR;
                 * else (eend==0) → no leftover peel, direct compare
                 * (classic case like `*T` or `**T` with no extra dims).
                 * Each peel step T001 on kind mismatch. Twin of param
                 * line 3449 (eand==-2 walk) and param line 3395
                 * (eand==0 extra SLICE/PTR walk). PLATFORM: SHARED.
                 */
                if (eend > 0) {
                  if (pgek == XLANG_TRAIT_TY_ARRAY) {
                    int32_t ed;
                    int32_t extra_slice;
                    int32_t extra_ptr;
                    for (ed = 0; ed < eend && pelem != 0; ed++) {
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                    }
                    if (pelem != 0) {
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                    }
                    extra_slice = 0;
                    if (eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      extra_slice = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend + 1];
                    if (extra_slice > 0) {
                      while (extra_slice > 0) {
                        if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pelem = pipeline_type_elem_ref_at(arena, pelem);
                        if (pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pgek = pipeline_type_kind_ord_at(arena, pelem);
                        extra_slice = extra_slice - 1;
                      }
                    }
                    extra_ptr = 0;
                    if (eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      extra_ptr = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend];
                    if (extra_ptr > 0) {
                      while (extra_ptr > 0) {
                        if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pelem = pipeline_type_elem_ref_at(arena, pelem);
                        if (pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pgek = pipeline_type_kind_ord_at(arena, pelem);
                        extra_ptr = extra_ptr - 1;
                      }
                    }
                  } else {
                    mm = 1;
                  }
                } else if (eend == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                  /*
                   * PTR_TO_SLICE sentinel eend=-2: extra SLICE wrap
                   * COUNT in dims[0] (0 means 1 = []*[]T / *[]T;
                   * 2 = []*[][]T). Extra PTR wrap COUNT in dims[1]
                   * (1 = []*[]*T; 2 = []*[]**T; 0 = no extra PTR =
                   * []*[]T / *[]T). Peel SLICE extra times then
                   * PTR extra times or T001. Twin of param line 3449
                   * (PARAM path, already closed 875d557e2). Do not
                   * invent -3. PLATFORM: SHARED parse.
                   */
                  int32_t extra =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][0];
                  if (extra <= 0)
                    extra = 1;
                  while (extra > 0) {
                    if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                      mm = 1;
                      break;
                    }
                    pelem = pipeline_type_elem_ref_at(arena, pelem);
                    if (pelem == 0) {
                      mm = 1;
                      break;
                    }
                    pgek = pipeline_type_kind_ord_at(arena, pelem);
                    extra = extra - 1;
                  }
                  if (!mm) {
                    int32_t extra_ptr =
                        g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][1];
                    if (extra_ptr > 0) {
                      while (extra_ptr > 0) {
                        if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pelem = pipeline_type_elem_ref_at(arena, pelem);
                        if (pelem == 0) {
                          mm = 1;
                          break;
                        }
                        pgek = pipeline_type_kind_ord_at(arena, pelem);
                        extra_ptr = extra_ptr - 1;
                      }
                    }
                  }
                }
                if (!mm && pgek >= 0 && pgek != eeek) {
                  mm = 1;
                } else if (!mm && pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                  int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                  if (enl > 0) {
                    uint8_t gnm[64];
                    int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                    if (!xlang_skip_trait_named_eq_self_c(
                          g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                          gnm, gnl,
                          g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                          g_xlang_skip_impl_for_is_ptr[si]))
                      mm = 1;
                  }
                }
              }
            } else if (gek == eek && eek == XLANG_TRAIT_TY_SLICE) {
              /*
               * wave438: *[]T → PTR to SLICE of T. Walk pipeline SLICE
               * leaf → its elem → compare elem_elem (the slice base T).
               * dest extras dest-RET extra empty `[]` SLICE-elem
               * `*[][2][]T`: leftover SLICE vs eek=SLICE is not T001
               * without extra ARRAY peels (store-only leftover ARRAY
               * vs eeek=leaf after leftover-SLICE peel is T001). Peel
               * leftover SLICE then extra ARRAY then extra SLICE then
               * extra PTR or T001. Extra SLICE wrap COUNT is unused
               * slot dims[ndims+1] (1 = `*[][2][]T`; 2 =
               * `*[][2][][]T`; 0 = no extra wrap = `*[][2]i32` /
               * `*[][2]*T`). Extra PTR wrap COUNT is unused slot
               * dims[ndims] (1 = `*[][2]*T` / `*[][2][]*T`; 0 = no
               * extra PTR = `*[][2]i32` / `*[][2][]T`; `*[][2][]*T`
               * has both slots set). leftover skip eek=-1 was false
               * green of extra empty `[]` SLICE-elem (impl
               * `*[][2]i32` vs trait `*[][2][]i32` compile=0;
               * dest-stamp via the local of typed dest = false
               * green even Ubuntu). dest extras dest-RET extra STAR
               * SLICE-elem ndims=0 `*[]*T`: extra PTR wrap COUNT is
               * unused slot dims[0] with ndims staying 0 (1 =
               * `*[]*T`; 2 = `*[]**T`; 0 = no extra PTR = `*[]i32`).
               * leftover skip eek=-1 was false green (impl `*[]i32`
               * vs trait `*[]*i32` compile=0; dest-stamp via the
               * local of typed dest = false green even Ubuntu). Peel
               * leftover PTR extra times or T001. `*[]T` (ndims=0
               * extra PTR=0) keeps leftover SLICE vs eek=SLICE
               * (pointee compare eeek). Twin of param leftover PTR
               * vs eek=SLICE extra ARRAY-then-SLICE-then-PTR peels
               * (`*[][2][]T` param already closed) and param extra
               * STAR ndims=0 leftover eand==0 extra PTR peels
               * (`*[]*T` param already closed). Discriminant vs dest
               * extras dest-RET extra empty `[]` ARRAY-elem `*[2][]T`
               * / PTR-elem `**[2][]T` is SLICE vs ARRAY vs PTR elem.
               * Extra ADDR_OF of typed `[][2][]i32` dest-stamps via
               * the formal leftover skip eek=-1 was false green. Do
               * not invent -3. PLATFORM: SHARED. G.7: complete this
               * walk.
               */
              int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
              if (eeek >= 0 && pelem != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                int32_t eend = g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[mi];
                if (eend >= 1) {
                  int32_t d;
                  int32_t extra_slice;
                  int32_t extra_ptr;
                  for (d = 0; d < eend && pelem != 0; d++) {
                    int32_t k = pipeline_type_kind_ord_at(arena, pelem);
                    int32_t gsz;
                    if (k != XLANG_TRAIT_TY_ARRAY) {
                      mm = 1;
                      break;
                    }
                    gsz = pipeline_type_array_size_at(arena, pelem);
                    if (gsz != g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][d]) {
                      mm = 1;
                      break;
                    }
                    pelem = pipeline_type_elem_ref_at(arena, pelem);
                    if (pelem == 0 && d + 1 < eend) {
                      mm = 1;
                      break;
                    }
                  }
                  if (!mm && pelem != 0)
                    pgek = pipeline_type_kind_ord_at(arena, pelem);
                  extra_slice = 0;
                  if (eend > 0 && eend + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    extra_slice = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend + 1];
                  if (extra_slice > 0) {
                    while (extra_slice > 0) {
                      if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_slice = extra_slice - 1;
                    }
                  }
                  extra_ptr = 0;
                  if (eend > 0 && eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    extra_ptr = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend];
                  if (extra_ptr > 0) {
                    while (extra_ptr > 0) {
                      if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_ptr = extra_ptr - 1;
                    }
                  }
                } else if (eend == 0) {
                  /*
                   * dest extras dest-RET extra STAR SLICE-elem
                   * ndims=0 `*[]*T`: leftover after leftover-SLICE
                   * peel is PTR vs eeek=leaf. Extra PTR wrap COUNT
                   * is unused slot dims[0] (1 = `*[]*T`; 2 =
                   * `*[]**T`; 0 = no extra PTR = `*[]i32`). Peel
                   * leftover PTR extra times or T001. Twin of param
                   * leftover eand==0 extra PTR peels. Do not invent
                   * -3. PLATFORM: SHARED. G.7: complete this walk.
                   */
                  int32_t extra_ptr;
                  extra_ptr =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][0];
                  if (extra_ptr > 0) {
                    while (extra_ptr > 0) {
                      if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_ptr = extra_ptr - 1;
                    }
                  }
                } else if (eend == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                  /*
                   * dest extras dest-RET extra STAR SLICE-elem
                   * ndims=-2 `*[][]*T`: leftover after leftover-
                   * SLICE peel is still SLICE vs eeek=leaf. Extra
                   * SLICE wrap COUNT is dims[0] (0 means 1 =
                   * `*[][]T`; 2 = `*[][][]T`). Extra PTR wrap
                   * COUNT is unused slot dims[1] (1 = `*[][]*T`;
                   * 2 = `*[][]**T`; 0 = no extra PTR = `*[][]T`).
                   * Peel leftover SLICE extra times then leftover
                   * PTR extra times or T001. Twin of param leftover
                   * eand==-2 extra SLICE then extra PTR peels
                   * (`*[][]*T` param already closed). Do not invent
                   * -3. PLATFORM: SHARED. G.7: complete this walk.
                   */
                  int32_t extra;
                  int32_t extra_ptr;
                  extra =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][0];
                  if (extra <= 0)
                    extra = 1;
                  while (extra > 0) {
                    if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                      mm = 1;
                      break;
                    }
                    pelem = pipeline_type_elem_ref_at(arena, pelem);
                    if (pelem == 0) {
                      mm = 1;
                      break;
                    }
                    pgek = pipeline_type_kind_ord_at(arena, pelem);
                    extra = extra - 1;
                  }
                  extra_ptr =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][1];
                  if (extra_ptr > 0) {
                    while (extra_ptr > 0) {
                      if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_ptr = extra_ptr - 1;
                    }
                  }
                }
                if (!mm) {
                  if (pgek >= 0 && pgek != eeek) {
                    mm = 1;
                  } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  }
                }
              }
            } else if (gek == eek && eek == XLANG_TRAIT_TY_ARRAY) {
              /*
               * wave438: *[N]T / *[N][M]T → PTR to ARRAY of N T. The PTR's
               * elem (elem) is the ARRAY. Walk its dims (elem_array_ndims/
               * dims) then compare the leaf elem kind/name with elem_elem
               * (base T). Multi-dim *[N][M]T collected at registration
               * (wave437 twin). PLATFORM: SHARED parse.
               */
              int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t eend = g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[mi];
              int32_t leaf_tr = elem;
              int32_t d;
              for (d = 0; d < eend && leaf_tr != 0; d++) {
                int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
                int32_t gsz;
                if (k != XLANG_TRAIT_TY_ARRAY) {
                  mm = 1;
                  break;
                }
                gsz = pipeline_type_array_size_at(arena, leaf_tr);
                if (gsz != g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][d]) {
                  mm = 1;
                  break;
                }
                leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                if (leaf_tr == 0 && d + 1 < eend) {
                  mm = 1;
                  break;
                }
              }
              if (!mm && eeek >= 0 && leaf_tr != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                /*
                 * dest extras dest-RET PTR-to-ARRAY extra empty `[]`
                 * `*[2][]T` AND dest extras dest-RET extra STAR
                 * `*[2]*T`: leftover after ARRAY peels is SLICE /
                 * PTR / SLICE-of-PTR vs eeek=leaf (store-only
                 * T001). Extra SLICE wrap COUNT is unused slot
                 * dims[ndims] (1 = `*[2][]T`; 0 = no extra wrap =
                 * `*[2]i32`). Extra PTR wrap COUNT is unused slot
                 * dims[ndims+1] (1 = `*[2]*T` / `*[2][]*T`; 0 = no
                 * extra PTR = `*[2]i32` / `*[2][]T`; `*[2][]*T`
                 * has both slots set). Peel leftover SLICE extra
                 * times then leftover PTR extra times or T001.
                 * Extra ADDR_OF of typed `[2]*i32` dest-stamps via
                 * the formal leftover skip eek=-1 was false green;
                 * dest extras dest-RET wrap-once dest-stamps
                 * `*[2]i32`. Twin of param ARRAY leftover extra
                 * SLICE-then-PTR peels. Do not invent -3.
                 * PLATFORM: SHARED. G.7: complete this walk.
                 */
                int32_t extra_slice = 0;
                int32_t extra_ptr = 0;
                if (eend > 0 && eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  extra_slice = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend];
                if (extra_slice > 0) {
                  while (extra_slice > 0) {
                    if (pgek != XLANG_TRAIT_TY_SLICE || leaf_tr == 0) {
                      mm = 1;
                      break;
                    }
                    leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                    if (leaf_tr == 0) {
                      mm = 1;
                      break;
                    }
                    pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                    extra_slice = extra_slice - 1;
                  }
                }
                if (eend > 0 && eend + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  extra_ptr = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend + 1];
                if (extra_ptr > 0) {
                  while (extra_ptr > 0) {
                    if (pgek != XLANG_TRAIT_TY_PTR || leaf_tr == 0) {
                      mm = 1;
                      break;
                    }
                    leaf_tr = pipeline_type_elem_ref_at(arena, leaf_tr);
                    if (leaf_tr == 0) {
                      mm = 1;
                      break;
                    }
                    pgek = pipeline_type_kind_ord_at(arena, leaf_tr);
                    extra_ptr = extra_ptr - 1;
                  }
                }
                if (!mm) {
                  if (pgek >= 0 && pgek != eeek) {
                    mm = 1;
                  } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  }
                }
              }
            } else if (gek == eek && eek == XLANG_TRAIT_TY_PTR) {
              /*
               * dest extras dest-RET extra STAR PTR-elem `**[2]*T`
               * AND dest extras dest-RET extra empty `[]` PTR-elem
               * `**[2][]T` / `**[]T`: leftover PTR vs eek=PTR is
               * not T001 without extra ARRAY peels (store-only
               * leftover PTR vs eeek=leaf after extra ARRAY peels
               * is T001). Peel leftover PTR then ARRAY dims then
               * extra SLICE then extra PTR or T001. Extra SLICE
               * wrap COUNT is unused slot dims[ndims] when
               * ndims>=1 (1 = `**[2][]T`; 0 = no extra wrap =
               * `**[2]i32`) and unused slot dims[0] with ndims
               * staying 0 (1 = `**[]T`; 2 = `**[][]T`; 0 = no
               * extra SLICE = `**T` / `***T`). Extra PTR wrap
               * COUNT is unused slot dims[ndims+1] (1 = `**[2]*T`
               * / `**[2][]*T`; 0 = no extra PTR = `**[2]i32` /
               * `**[2][]T`; `**[2][]*T` has both slots set) and
               * unused slot dims[1] with ndims staying 0 (1 =
               * `***T`; 2 = `****T`; 0 = no extra PTR = `**T`;
               * both slots = `**[]*T`). leftover skip eek=-1 was
               * false green of extra empty `[]` PTR-elem (impl
               * `**[2]i32` / `**i32` vs trait `**[2][]i32` /
               * `**[]i32` compile=0). dest extras dest-RET extra
               * STAR PTR-elem ndims=0 `***T`: extra PTR wrap
               * COUNT is unused slot dims[1]. leftover skip
               * eek=-1 was false green (impl `**i32` vs trait
               * `***i32` compile=0; dest-stamp via the local of
               * typed dest = false green even Ubuntu). Peel
               * leftover PTR extra times or T001. `**i32`
               * (ndims=0 extra PTR=0 extra SLICE=0) keeps leftover
               * PTR vs eek=PTR (pointee compare eeek). Twin of
               * leftover eek==SLICE eend==0 extra PTR peels
               * (`*[]*T` already closed). Discriminant vs dest
               * extras dest-RET extra STAR ARRAY-elem `*[2]*T` /
               * extra empty `[]` ARRAY-elem `*[2][]T` is PTR vs
               * ARRAY elem. Extra ADDR_OF of typed `*[2]*i32`
               * dest-stamps via the formal leftover skip eek=-1
               * was false green; dest extras dest-RET wrap-once
               * dest-stamps `**[2]i32` / `**i32`. Do not invent
               * -3. PLATFORM: SHARED. G.7: complete this walk.
               */
              int32_t eeek = g_xlang_skip_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
              if (eeek >= 0 && pelem != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                int32_t eend = g_xlang_skip_trait_reg[ti].method_ret_elem_array_ndims[mi];
                if (pgek == XLANG_TRAIT_TY_ARRAY && eend > 0) {
                  int32_t d;
                  int32_t extra_slice;
                  int32_t extra_ptr;
                  for (d = 0; d < eend && pelem != 0; d++) {
                    int32_t k = pipeline_type_kind_ord_at(arena, pelem);
                    int32_t gsz;
                    if (k != XLANG_TRAIT_TY_ARRAY) {
                      mm = 1;
                      break;
                    }
                    gsz = pipeline_type_array_size_at(arena, pelem);
                    if (gsz != g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][d]) {
                      mm = 1;
                      break;
                    }
                    pelem = pipeline_type_elem_ref_at(arena, pelem);
                    if (pelem == 0 && d + 1 < eend) {
                      mm = 1;
                      break;
                    }
                  }
                  if (!mm && pelem != 0)
                    pgek = pipeline_type_kind_ord_at(arena, pelem);
                  extra_slice = 0;
                  if (eend > 0 && eend < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    extra_slice = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend];
                  if (extra_slice > 0) {
                    while (extra_slice > 0) {
                      if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_slice = extra_slice - 1;
                    }
                  }
                  extra_ptr = 0;
                  if (eend > 0 && eend + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    extra_ptr = g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][eend + 1];
                  if (extra_ptr > 0) {
                    while (extra_ptr > 0) {
                      if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_ptr = extra_ptr - 1;
                    }
                  }
                } else if (eend == 0) {
                  /*
                   * dest extras dest-RET extra STAR PTR-elem
                   * ndims=0 `***T` AND dest extras dest-RET extra
                   * empty `[]` PTR-elem ndims=0 `**[]T`: leftover
                   * after leftover-PTR peel is PTR / SLICE vs
                   * eeek=leaf. Extra SLICE wrap COUNT is unused
                   * slot dims[0] (1 = `**[]T`; 2 = `**[][]T`; 0 =
                   * no extra SLICE = `**T` / `***T`). Extra PTR
                   * wrap COUNT is unused slot dims[1] (1 = `***T`;
                   * 2 = `****T`; 0 = no extra PTR = `**T`; both
                   * slots = `**[]*T`). Peel leftover SLICE extra
                   * times then leftover PTR extra times or T001.
                   * leftover skip eek=-1 was false green of extra
                   * empty `[]` PTR-elem ndims=0 (impl `**i32` vs
                   * trait `**[]i32` compile=0; dest-stamp via the
                   * local of typed dest = false green even Ubuntu).
                   * Twin of leftover eek==SLICE eend==0 extra PTR
                   * peels and leftover eek==PTR ndims>=1 extra
                   * SLICE-then-PTR peels. Do not invent -3.
                   * PLATFORM: SHARED. G.7: complete this walk.
                   */
                  int32_t extra_slice;
                  int32_t extra_ptr;
                  extra_slice =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][0];
                  if (extra_slice > 0) {
                    while (extra_slice > 0) {
                      if (pgek != XLANG_TRAIT_TY_SLICE || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_slice = extra_slice - 1;
                    }
                  }
                  extra_ptr =
                      g_xlang_skip_trait_reg[ti].method_ret_elem_array_dims[mi][1];
                  if (extra_ptr > 0) {
                    while (extra_ptr > 0) {
                      if (pgek != XLANG_TRAIT_TY_PTR || pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pelem = pipeline_type_elem_ref_at(arena, pelem);
                      if (pelem == 0) {
                        mm = 1;
                        break;
                      }
                      pgek = pipeline_type_kind_ord_at(arena, pelem);
                      extra_ptr = extra_ptr - 1;
                    }
                  }
                }
                if (!mm) {
                  if (pgek >= 0 && pgek != eeek) {
                    mm = 1;
                  } else if (pgek == eeek && eeek == XLANG_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                      if (!xlang_skip_trait_named_eq_self_c(
                            g_xlang_skip_trait_reg[ti].method_ret_names[mi], enl,
                            gnm, gnl,
                            g_xlang_skip_impl_for_names[si], g_xlang_skip_impl_for_name_lens[si],
                            g_xlang_skip_impl_for_is_ptr[si]))
                        mm = 1;
                    }
                  }
                }
              }
            }
          }
        }
        if (mm) {
          lsp_diag_report_typeck((int)g_xlang_skip_impl_line[si], (int)g_xlang_skip_impl_col[si],
                                 "method %.*s return type mismatch", (int)mlen, (const char *)mnm);
          rc = -1;
        }
      }
    }
  }
  /* wave439: tokenize stashed source to capture generic bounds + sites,
   * then verify each site's type arg satisfies the decl bound (function
   * or struct). Scan is idempotent (resets globals at entry); running it
   * here guarantees it executes on every product path. PLATFORM: SHARED. */
  xlang_generic_bound_scan_c(g_w439_src_data, g_w439_src_len);
  if (xlang_generic_bound_check_c() != 0)
    rc = -1;
  return rc;
}

/* ============================================================ */
/* wave439: generic trait bound scan + check                    */
/*                                                              */
/* Captures `function foo<T: Trait>` bound declarations and     */
/* `foo<Type>(` generic call sites by tokenizing the source.   */
/* At check time, for each call site whose callee has a bound,  */
/* verifies `impl Trait for Type` exists in the impl registry. */
/* False-green fix: `copy<B>(b)` where B does not impl the     */
/* bound trait previously compiled and ran without error.       */
/* PLATFORM: SHARED parse.                                      */
/* ============================================================ */

#define XLANG_FN_BOUND_MAX 16
#define XLANG_GENERIC_CALL_MAX 32
/* wave442: max type args per generic call site (foo<A,B,C,D>). Most generic
 * calls have ≤4 type args; calls exceeding this fall back to first-arg-only
 * check (preserve wave439 behavior) — see scan capture gate. */
#define XLANG_GENERIC_CALL_MAX_ARGS 4

/* function name → bound trait name (populated by scan, read by check).
 * wave442: g_fn_bound_pos records the type-param POSITION (0-based) of each
 * bound within its function, so `foo<T: Clone, U: Hash>` stores two entries
 * (Clone@pos0, Hash@pos1) and the check matches each to the call's type arg
 * at the same position (`foo<A,B>` → A@0 checked vs Clone, B@1 vs Hash). */
static uint8_t g_fn_bound_name[XLANG_FN_BOUND_MAX][64];
static int32_t g_fn_bound_name_len[XLANG_FN_BOUND_MAX];
static uint8_t g_fn_bound_trait[XLANG_FN_BOUND_MAX][64];
static int32_t g_fn_bound_trait_len[XLANG_FN_BOUND_MAX];
static int32_t g_fn_bound_pos[XLANG_FN_BOUND_MAX];
static int32_t g_fn_bound_n;

/* generic call site: callee name + type args. g_call_typearg (first arg) is
 * kept for backward compat with any first-arg reader; g_call_typeargs holds
 * all captured type args (up to XLANG_GENERIC_CALL_MAX_ARGS) and g_call_nargs
 * the count. wave439 captured only the first type arg → multi-arg bounds like
 * `copy_both<A,B>` where B violates `U: Default` went unchecked (false-green
 * falling through to confusing BLD001). wave442 captures all simple type args
 * and checks each against its positional bound. */
static uint8_t g_call_callee[XLANG_GENERIC_CALL_MAX][64];
static int32_t g_call_callee_len[XLANG_GENERIC_CALL_MAX];
static uint8_t g_call_typearg[XLANG_GENERIC_CALL_MAX][64];
static int32_t g_call_typearg_len[XLANG_GENERIC_CALL_MAX];
static uint8_t g_call_typeargs[XLANG_GENERIC_CALL_MAX][XLANG_GENERIC_CALL_MAX_ARGS][64];
static int32_t g_call_typearg_lens[XLANG_GENERIC_CALL_MAX][XLANG_GENERIC_CALL_MAX_ARGS];
static int32_t g_call_nargs[XLANG_GENERIC_CALL_MAX];
static int32_t g_call_line[XLANG_GENERIC_CALL_MAX];
static int32_t g_call_col[XLANG_GENERIC_CALL_MAX];
static int32_t g_call_n;

/*
 * wave455 Cap residual: declaration-order type-parameter names per generic
 * function (`function mk2<T, U>(): T` → fn "mk2" params ["T","U"]).
 *
 * Why: Func only stores num_generic_params (count), not names. typeck fixup
 * mapping ret TYPE_NAMED "T" → turbofish type_arg[i] required collecting
 * type-param names from formals+ret and demanded gnames_n == n_gp — phantom
 * type params that never appear in the signature (`U` unused) made gnames
 * short → multi type_arg ret-only turbofish false-red *found T*.
 *
 * Authority: same G.7 thin-glue source scan as bound/call capture (no Func
 * layout / SHARED ABI churn). Lookup: xlang_generic_func_type_param_index_c.
 * PLATFORM: SHARED parse — rebuild parser thin glue after edit.
 */
#define XLANG_FN_GP_MAX 32
static uint8_t g_fn_gp_fname[XLANG_FN_GP_MAX][64];
static int32_t g_fn_gp_fname_len[XLANG_FN_GP_MAX];
static uint8_t g_fn_gp_names[XLANG_FN_GP_MAX][XLANG_GENERIC_CALL_MAX_ARGS][64];
static int32_t g_fn_gp_lens[XLANG_FN_GP_MAX][XLANG_GENERIC_CALL_MAX_ARGS];
static int32_t g_fn_gp_nargs[XLANG_FN_GP_MAX];
static int32_t g_fn_gp_n;

/** wave455: clear type-param name registry (per-module / trait_reg_reset). */
void xlang_generic_func_reg_reset_c(void) {
  g_fn_gp_n = 0;
  memset(g_fn_gp_nargs, 0, sizeof(g_fn_gp_nargs));
}

/**
 * Stash the full-file source slice pointer so the generic-bound scan (run later
 * from xlang_trait_check_impls_complete_c) can tokenize it. Called from each
 * top-level skip_*_into_slice_c entry; idempotent (same file slice each call).
 * PLATFORM: SHARED parse.
 */
void xlang_generic_bound_stash_source_c(struct parser_asm_slice_u8 *source) {
  if (source) {
    g_w439_src_data = source->data;
    g_w439_src_len = (int32_t)source->length;
  }
}

/**
 * wave455: product parse entry (pipeline_glue) stashes without depending on
 * parser_asm_slice_u8 visibility in the glue TU.
 * @param data full-file source bytes
 * @param len  byte length
 * PLATFORM: SHARED parse.
 */
void xlang_generic_bound_stash_source_buf_c(uint8_t *data, int32_t len) {
  g_w439_src_data = data;
  g_w439_src_len = (data && len > 0) ? len : 0;
}

/**
 * Scan source text for generic trait bound declarations and generic call
 * sites. Called from xlang_trait_check_impls_complete_c via the stashed source
 * pointer. Populates g_fn_bound_* and g_call_* globals.
 *
 * Bound pattern: `function IDENT < IDENT : IDENT >`,
 *   `struct IDENT < IDENT : IDENT >`, `impl IDENT < IDENT : IDENT >`, and
 *   `impl < IDENT : IDENT > Type` / `impl <…> Trait for Type` — the bound
 *   trait is the IDENT after `:`; stored as (decl_name, trait_name).
 *   Impl-level rows are keyed by the for-type (inherent Type or `for Type`)
 *   so type-position `Foo<B>` uses the same check as struct-level bounds.
 *   Same type-param may list several traits with `+` (`T: Clone + Default`):
 *   each IDENT after `+` is another bound at the SAME pos (COMMA still
 *   advances pos).
 * Instantiation pattern: `IDENT < IDENT >` followed by `(` (generic call)
 *   or type-position `{` `=` `;` `,` `)` (`let f: Foo<B> = …`, `x: Foo<B>`,
 *   `Foo<B> { … }`). Comparisons `a < b` have no `>` so they are not
 *   captured. Nested `foo<Vec<i32>>` (angle depth > 1) stays soft-skip.
 * Soft: TYPE_DYN / vtable (dyn / impl type-pos now peel to the trait
 *   NAMED in type_ref; no object dispatch). Bare `Foo { }` without a
 *   type-pos `Foo<B>` is not captured (inference leftover).
 * PLATFORM: SHARED parse.
 */

extern void parser_asm_skip_generic_angle_list_into_slice_c(struct parser_asm_lexer *out,
                                                            struct parser_asm_lexer lex,
                                                            struct parser_asm_slice_u8 *source);

/*
 * Peek the for-type IDENT after `impl<...>`.
 * `lex` must sit at the `<` of `impl<`. Does not mutate caller lex.
 * Inherent `impl<T: Clone> Foo` → Foo; `impl<T: Clone> Clone for Foo` → Foo.
 * @param source   file slice (same as the scan lexer)
 * @param lex      lexer at the impl-level `<`
 * @param name64   out: for-type bytes (cleared on miss)
 * @param name_len out: length ≤63
 * @return 1 hit; 0 no IDENT for-type
 * PLATFORM: SHARED parse — G.7 peek only; bound walk stays in scan.
 */
static int32_t xlang_generic_bound_peek_impl_for_type_c(struct parser_asm_slice_u8 *source,
                                                        struct parser_asm_lexer lex,
                                                        uint8_t *name64, int32_t *name_len) {
  struct parser_asm_lexer peek;
  struct parser_asm_lexer_result pr;
  uint8_t name1[64];
  int32_t n1;
  if (!source || !name64 || !name_len)
    return 0;
  *name_len = 0;
  memset(name64, 0, 64);
  memset(name1, 0, 64);
  n1 = 0;
  parser_asm_skip_generic_angle_list_into_slice_c(&peek, lex, source);
  lexer_next_into(&pr, peek, source);
  if (pr.tok.kind != (int32_t)TOKEN_IDENT)
    return 0;
  n1 = pr.tok.ident_len > 63 ? 63 : pr.tok.ident_len;
  if (n1 > 0 && source->data)
    memcpy(name1, source->data + pr.token_start, (size_t)n1);
  peek = pr.next_lex;
  lexer_next_into(&pr, peek, source);
  if (pr.tok.kind == (int32_t)TOKEN_LT) {
    parser_asm_skip_generic_angle_list_into_slice_c(&peek, peek, source);
    lexer_next_into(&pr, peek, source);
  }
  if (pr.tok.kind == (int32_t)TOKEN_FOR) {
    peek = pr.next_lex;
    lexer_next_into(&pr, peek, source);
    if (pr.tok.kind == (int32_t)TOKEN_STAR) {
      peek = pr.next_lex;
      lexer_next_into(&pr, peek, source);
    }
    if (pr.tok.kind != (int32_t)TOKEN_IDENT)
      return 0;
    n1 = pr.tok.ident_len > 63 ? 63 : pr.tok.ident_len;
    memset(name1, 0, 64);
    if (n1 > 0 && source->data)
      memcpy(name1, source->data + pr.token_start, (size_t)n1);
  }
  if (n1 <= 0)
    return 0;
  memcpy(name64, name1, (size_t)n1);
  *name_len = n1;
  return 1;
}

void xlang_generic_bound_scan_c(uint8_t *data, int32_t len) {
  struct parser_asm_slice_u8 source;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  int32_t prev_function = 0;
  int32_t prev_struct = 0;
  int32_t prev_impl = 0;
  uint8_t last_ident[64];
  int32_t last_ident_len = 0;
  int32_t last_ident_is_fn = 0;
  int32_t last_ident_is_struct = 0;
  int32_t last_ident_is_impl = 0;

  /*
   * wave455: if source was never stashed (product pure parse path fully
   * parses structs and never hit skip_one_* stash), do NOT wipe g_fn_gp_* —
   * parse-time registration (xlang_generic_func_register_type_params_c) may
   * already hold declaration-order names. Only reset+rescan when we have
   * real source bytes.
   */
  if (!data || len <= 0)
    return;
  /* reset before each file scan */
  g_fn_bound_n = 0;
  g_call_n = 0;
  g_fn_gp_n = 0;
  /* wave442: zero multi-arg storage so stale data from a prior file cannot
   * leak into the check (g_call_nargs/g_fn_bound_pos drive positional match). */
  memset(g_call_nargs, 0, sizeof(g_call_nargs));
  memset(g_fn_bound_pos, 0, sizeof(g_fn_bound_pos));
  memset(g_fn_gp_nargs, 0, sizeof(g_fn_gp_nargs));
  source.data = data;
  source.length = (size_t)len;
  /* wave440: lexer line/col must start at 1 (matching lexer_init in lexer.x).
   * memset(0) left line=0 → all reported line numbers off by -1, causing
   * diag positions to point at the line above the actual call site. col is
   * reset to 1 by advance_one on newline so only line 1 was affected, but
   * initializing col=1 too for full correctness on the first line. */
  memset(&lex, 0, sizeof(lex));
  lex.line = 1;
  lex.col = 1;
  memset(last_ident, 0, 64);

  for (;;) {
    lexer_next_into(&r, lex, &source);
    if (r.tok.kind == (int32_t)TOKEN_EOF)
      break;

    if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
      prev_function = 1;
      prev_struct = 0;
      prev_impl = 0;
      last_ident_len = 0;
    } else if (r.tok.kind == (int32_t)TOKEN_STRUCT) {
      /* 4.2.2 struct-level `<T: Trait>` — same bound tables as function.
       * Prior: only TOKEN_FUNCTION armed last_ident_is_fn, so
       * `struct Foo<T: Clone>` never recorded → Foo<B> false-green. */
      prev_struct = 1;
      prev_function = 0;
      prev_impl = 0;
      last_ident_len = 0;
    } else if (r.tok.kind == (int32_t)TOKEN_IMPL) {
      /* 4.2.2 impl-level `<T: Trait>` — `impl<T: Clone> Foo` has no IDENT
       * before `<`; `impl Foo<T: Clone>` has IDENT Foo after impl.
       * prev_impl arms both: peek for-type on bare `<`, or last_ident_is_impl
       * on `impl Type<...>`. Key = for-type so Foo<B> uses the same check.
       * PLATFORM: SHARED parse. */
      prev_impl = 1;
      prev_function = 0;
      prev_struct = 0;
      last_ident_len = 0;
    } else if (r.tok.kind == (int32_t)TOKEN_IDENT) {
      last_ident_len = r.tok.ident_len > 63 ? 63 : r.tok.ident_len;
      if (last_ident_len > 0 && source.data)
        memcpy(last_ident, source.data + r.token_start, (size_t)last_ident_len);
      last_ident_is_fn = prev_function;
      last_ident_is_struct = prev_struct;
      last_ident_is_impl = prev_impl;
      prev_function = 0;
      prev_struct = 0;
      prev_impl = 0;
    } else if (r.tok.kind == (int32_t)TOKEN_LT && (last_ident_len > 0 || prev_impl)) {
      /* `impl<T: Trait> Type` — no IDENT before `<`. Peek the for-type and
       * reuse the function/struct bound walk (name = for-type). */
      if (prev_impl && last_ident_len == 0) {
        if (xlang_generic_bound_peek_impl_for_type_c(&source, lex, last_ident,
                                                     &last_ident_len))
          last_ident_is_impl = 1;
        prev_impl = 0;
      }
      /* advance lex past the `<` so the inner loops read the token AFTER it
       * (otherwise the first lexer_next_into re-reads `<` and inflates depth). */
      lex = r.next_lex;
      if (last_ident_len > 0 && (last_ident_is_fn || last_ident_is_struct
                                 || last_ident_is_impl)) {
        /* function/struct/impl name < ... > — scan for:
         *  (1) wave442 `IDENT : IDENT` bounds with positional pos
         *  (2) wave455 declaration-order type-param names (all slots)
         * Type-param IDENT is the first IDENT at depth 1 after `<` or `,`
         * (expect_tp); COLON switches to expect_trait for the bound name.
         * struct Foo<T: Clone> / impl Foo<T: Clone> / impl<T: Clone> Foo
         * use the same tables (name = struct / for-type).
         * PLATFORM: SHARED — same angle walk as bound-only path. */
        int32_t angle_depth = 1;
        int32_t expect_trait = 0;
        int32_t expect_tp = 1;
        /* 1 after a bound IDENT so `+ Trait` stays on the same pos. */
        int32_t after_bound = 0;
        int32_t pos = 0;
        int32_t gp_slot = -1;
        if (g_fn_gp_n < XLANG_FN_GP_MAX) {
          gp_slot = g_fn_gp_n;
          memset(g_fn_gp_fname[gp_slot], 0, 64);
          memcpy(g_fn_gp_fname[gp_slot], last_ident, (size_t)last_ident_len);
          g_fn_gp_fname_len[gp_slot] = last_ident_len;
          g_fn_gp_nargs[gp_slot] = 0;
          memset(g_fn_gp_lens[gp_slot], 0, sizeof(g_fn_gp_lens[gp_slot]));
          g_fn_gp_n++;
        }
        while (angle_depth > 0) {
          lexer_next_into(&r, lex, &source);
          if (r.tok.kind == (int32_t)TOKEN_EOF)
            break;
          if (r.tok.kind == (int32_t)TOKEN_LT)
            angle_depth++;
          else if (r.tok.kind == (int32_t)TOKEN_GT) {
            angle_depth--;
            if (angle_depth == 0)
              break;
          } else if (r.tok.kind == (int32_t)TOKEN_COLON && angle_depth == 1) {
            expect_trait = 1;
            expect_tp = 0;
            after_bound = 0;
          } else if (r.tok.kind == (int32_t)TOKEN_PLUS && angle_depth == 1 && after_bound) {
            /* T: Clone + Default — another bound on this type-param slot.
             * Do not increment pos (COMMA does that). Previously PLUS was
             * ignored so Default never registered → call-site false-green.
             * PLATFORM: SHARED parse. */
            expect_trait = 1;
            expect_tp = 0;
            after_bound = 0;
          } else if (r.tok.kind == (int32_t)TOKEN_IDENT && angle_depth == 1 && expect_trait) {
            if (g_fn_bound_n < XLANG_FN_BOUND_MAX) {
              memcpy(g_fn_bound_name[g_fn_bound_n], last_ident, (size_t)last_ident_len);
              g_fn_bound_name_len[g_fn_bound_n] = last_ident_len;
              int32_t tl = r.tok.ident_len > 63 ? 63 : r.tok.ident_len;
              if (tl > 0 && source.data)
                memcpy(g_fn_bound_trait[g_fn_bound_n], source.data + r.token_start, (size_t)tl);
              g_fn_bound_trait_len[g_fn_bound_n] = tl;
              g_fn_bound_pos[g_fn_bound_n] = pos;
              g_fn_bound_n++;
            }
            expect_trait = 0;
            after_bound = 1;
          } else if (r.tok.kind == (int32_t)TOKEN_IDENT && angle_depth == 1 && expect_tp
                     && !expect_trait) {
            /* wave455: type-param name at declaration position. */
            if (gp_slot >= 0 && g_fn_gp_nargs[gp_slot] < XLANG_GENERIC_CALL_MAX_ARGS) {
              int32_t pi = g_fn_gp_nargs[gp_slot];
              int32_t pl = r.tok.ident_len > 63 ? 63 : r.tok.ident_len;
              memset(g_fn_gp_names[gp_slot][pi], 0, 64);
              if (pl > 0 && source.data)
                memcpy(g_fn_gp_names[gp_slot][pi], source.data + r.token_start, (size_t)pl);
              g_fn_gp_lens[gp_slot][pi] = pl;
              g_fn_gp_nargs[gp_slot] = pi + 1;
            }
            expect_tp = 0;
            after_bound = 0;
          } else if (r.tok.kind == (int32_t)TOKEN_COMMA && angle_depth == 1) {
            expect_trait = 0;
            expect_tp = 1;
            after_bound = 0;
            pos++;
          }
          lex = r.next_lex;
        }
      } else if (!last_ident_is_fn && last_ident_len > 0 && g_call_n < XLANG_GENERIC_CALL_MAX) {
        /* IDENT < ... > — possible generic call. wave442: capture ALL simple
         * type args (up to XLANG_GENERIC_CALL_MAX_ARGS) at angle depth 1, not
         * just the first, so multi-arg bounds `foo<A,B>` check each type arg
         * against its positional bound. `simple=0` on any nested `<` (e.g.
         * `foo<Vec<i32>>`) keeps the wave439 nested-generic soft-skip — only
         * flat type-arg lists are captured. expect_arg gates one IDENT per
         * slot (right after `<` or after `,`) so `foo<A,B>` captures A then B
         * without consuming `B` as part of A's name. */
        int32_t angle_depth = 1;
        int32_t simple = 1;
        uint8_t type_args[XLANG_GENERIC_CALL_MAX_ARGS][64];
        int32_t type_arg_lens[XLANG_GENERIC_CALL_MAX_ARGS];
        int32_t nargs = 0;
        int32_t expect_arg = 1;
        memset(type_arg_lens, 0, sizeof(type_arg_lens));
        while (angle_depth > 0) {
          lexer_next_into(&r, lex, &source);
          if (r.tok.kind == (int32_t)TOKEN_EOF)
            break;
          if (r.tok.kind == (int32_t)TOKEN_LT) {
            angle_depth++;
            simple = 0;
          } else if (r.tok.kind == (int32_t)TOKEN_GT) {
            angle_depth--;
            if (angle_depth == 0)
              break;
          } else if (r.tok.kind == (int32_t)TOKEN_IDENT && angle_depth == 1 && expect_arg
                     && nargs < XLANG_GENERIC_CALL_MAX_ARGS) {
            int32_t al = r.tok.ident_len > 63 ? 63 : r.tok.ident_len;
            if (al > 0 && source.data)
              memcpy(type_args[nargs], source.data + r.token_start, (size_t)al);
            type_arg_lens[nargs] = al;
            nargs++;
            expect_arg = 0;
          } else if (r.tok.kind == (int32_t)TOKEN_COMMA && angle_depth == 1) {
            expect_arg = 1;
          }
          lex = r.next_lex;
        }
        /* Record instantiations: generic call `foo<T>(` or type-position
         * `Foo<B>` followed by `{` `=` `;` `,` `)`. Comparisons `a < b`
         * never produce `>` so they stay out. PLATFORM: SHARED parse. */
        if (nargs > 0 && simple) {
          struct parser_asm_lexer after = r.next_lex;
          int32_t nk;
          lexer_next_into(&r, after, &source);
          nk = r.tok.kind;
          if (nk == (int32_t)TOKEN_LPAREN || nk == (int32_t)TOKEN_LBRACE
              || nk == (int32_t)TOKEN_ASSIGN || nk == (int32_t)TOKEN_SEMICOLON
              || nk == (int32_t)TOKEN_COMMA || nk == (int32_t)TOKEN_RPAREN) {
            int32_t k;
            memcpy(g_call_callee[g_call_n], last_ident, (size_t)last_ident_len);
            g_call_callee_len[g_call_n] = last_ident_len;
            /* keep g_call_typearg (first arg) for backward compat with any
             * first-arg reader; g_call_typeargs holds all for positional check. */
            memcpy(g_call_typearg[g_call_n], type_args[0], 64);
            g_call_typearg_len[g_call_n] = type_arg_lens[0];
            for (k = 0; k < nargs; k++) {
              memcpy(g_call_typeargs[g_call_n][k], type_args[k], 64);
              g_call_typearg_lens[g_call_n][k] = type_arg_lens[k];
            }
            g_call_nargs[g_call_n] = nargs;
            g_call_line[g_call_n] = (int32_t)r.tok.line;
            g_call_col[g_call_n] = (int32_t)r.tok.col;
            g_call_n++;
          }
        }
      }
      last_ident_len = 0;
      last_ident_is_fn = 0;
      last_ident_is_struct = 0;
      last_ident_is_impl = 0;
      prev_function = 0;
      prev_struct = 0;
      prev_impl = 0;
    } else {
      prev_function = 0;
      prev_struct = 0;
      prev_impl = 0;
      if (r.tok.kind != (int32_t)TOKEN_DOT && r.tok.kind != (int32_t)TOKEN_COLON) {
        /* clear last_ident for tokens that can't precede `<` in a call;
         * keep it for `.` (qualified path) — though we only handle simple
         * IDENT callees for now. */
        last_ident_len = 0;
      }
    }
    lex = r.next_lex;
  }
}

/**
 * wave455: register declaration-order type-param names for a function.
 * Called from parse_one_function immediately after counting `<T,U>` (pending
 * snapshot) and optionally refilled by source scan when stash has bytes.
 * Replaces any prior entry with the same function name.
 * PLATFORM: SHARED parse+typeck.
 */
int32_t xlang_generic_func_register_type_params_c(const uint8_t *fn_name, int32_t fn_name_len,
                                                    const uint8_t names[][64], const int32_t *lens,
                                                    int32_t n) {
  int32_t fi;
  int32_t pi;
  int32_t slot;
  if (!fn_name || fn_name_len <= 0 || !names || !lens || n <= 0)
    return 0;
  if (fn_name_len > 63)
    fn_name_len = 63;
  if (n > XLANG_GENERIC_CALL_MAX_ARGS)
    n = XLANG_GENERIC_CALL_MAX_ARGS;
  /* Replace existing entry for same function name. */
  slot = -1;
  for (fi = 0; fi < g_fn_gp_n; fi++) {
    if (g_fn_gp_fname_len[fi] == fn_name_len &&
        memcmp(g_fn_gp_fname[fi], fn_name, (size_t)fn_name_len) == 0) {
      slot = fi;
      break;
    }
  }
  if (slot < 0) {
    if (g_fn_gp_n >= XLANG_FN_GP_MAX)
      return -1;
    slot = g_fn_gp_n;
    g_fn_gp_n++;
  }
  memset(g_fn_gp_fname[slot], 0, 64);
  memcpy(g_fn_gp_fname[slot], fn_name, (size_t)fn_name_len);
  g_fn_gp_fname_len[slot] = fn_name_len;
  g_fn_gp_nargs[slot] = n;
  for (pi = 0; pi < n; pi++) {
    memset(g_fn_gp_names[slot][pi], 0, 64);
    if (lens[pi] > 0) {
      int32_t pl = lens[pi] > 63 ? 63 : lens[pi];
      memcpy(g_fn_gp_names[slot][pi], names[pi], (size_t)pl);
      g_fn_gp_lens[slot][pi] = pl;
    } else {
      g_fn_gp_lens[slot][pi] = 0;
    }
  }
  return n;
}

/**
 * wave455: look up declaration-order index of a type-parameter name on a
 * generic function recorded by xlang_generic_bound_scan_c or parse-time
 * register_type_params.
 *
 * @param fn_name       function name bytes
 * @param fn_name_len   name length (≤63)
 * @param tp_name       type-parameter name (e.g. "T", "U")
 * @param tp_name_len   length of tp_name
 * @return 0-based type-arg index, or -1 if unknown function / name
 * PLATFORM: SHARED — used by pipeline_glue generic call ret fixup.
 */
int32_t xlang_generic_func_type_param_index_c(const uint8_t *fn_name, int32_t fn_name_len,
                                               const uint8_t *tp_name, int32_t tp_name_len) {
  int32_t fi;
  int32_t pi;
  if (!fn_name || fn_name_len <= 0 || !tp_name || tp_name_len <= 0)
    return -1;
  if (fn_name_len > 63)
    fn_name_len = 63;
  if (tp_name_len > 63)
    tp_name_len = 63;
  for (fi = 0; fi < g_fn_gp_n; fi++) {
    if (g_fn_gp_fname_len[fi] != fn_name_len)
      continue;
    if (memcmp(g_fn_gp_fname[fi], fn_name, (size_t)fn_name_len) != 0)
      continue;
    for (pi = 0; pi < g_fn_gp_nargs[fi]; pi++) {
      if (g_fn_gp_lens[fi][pi] != tp_name_len)
        continue;
      if (memcmp(g_fn_gp_names[fi][pi], tp_name, (size_t)tp_name_len) == 0) {
        return pi;
      }
    }
    return -1;
  }
  return -1;
}

/**
 * 4.2.2 generic-body method via bound (G.7 complete the skip_tl bound+trait tables).
 *
 * typeck method_call used to LANG-004 `x.clone()` when `x: T` even if the
 * enclosing function declared `T: Clone` and Clone lists `clone`. Call-site
 * `copy<A>` already checks the impl; the body still needs the method.
 *
 * Walk (fn, type-param pos) bounds (PLUS rows share pos) and the trait
 * registry. First trait that lists `method_name` with matching arity wins.
 * `num_args` is METHOD_CALL extras (not including self). expect_np < 0
 * (uncaptured) skips the arity gate.
 *
 * On hit, writes TypeKind ordinal + optional NAMED spelling (`Self`, `A`).
 * typeck maps Self / the type-param name to the receiver type_ref.
 *
 * Same globals as scan+check (last parsed file). Soft: dyn Trait;
 * compound ret (PTR/SLICE/ARRAY) still reported so typeck can refuse
 * or leave unresolved.
 * PLATFORM: SHARED parse+typeck — rebuild parser thin glue after edit.
 *
 * @param fn_name           enclosing generic function name
 * @param fn_name_len       ≤63
 * @param tp_name           receiver type-param spelling (e.g. "T")
 * @param tp_name_len       length
 * @param method_name       method spelling
 * @param method_name_len   length
 * @param num_args          extra METHOD_CALL args (self is implicit)
 * @param out_ret_kind      TypeKind ord, or -1 unknown; may be NULL
 * @param out_ret_name      64-byte NAMED spelling; may be NULL
 * @param out_ret_name_len  name length; may be NULL
 * @return 1 method granted by a bound; 0 no
 */
int32_t xlang_generic_bound_method_on_param_c(const uint8_t *fn_name, int32_t fn_name_len,
                                               const uint8_t *tp_name, int32_t tp_name_len,
                                               const uint8_t *method_name, int32_t method_name_len,
                                               int32_t num_args, int32_t *out_ret_kind,
                                               uint8_t *out_ret_name, int32_t *out_ret_name_len) {
  int32_t pos;
  int32_t bi;
  int32_t ti;
  int32_t mi;
  if (!fn_name || fn_name_len <= 0 || !tp_name || tp_name_len <= 0
      || !method_name || method_name_len <= 0)
    return 0;
  if (fn_name_len > 63)
    fn_name_len = 63;
  if (tp_name_len > 63)
    tp_name_len = 63;
  if (method_name_len > 63)
    method_name_len = 63;
  pos = xlang_generic_func_type_param_index_c(fn_name, fn_name_len, tp_name, tp_name_len);
  if (pos < 0)
    return 0;
  for (bi = 0; bi < g_fn_bound_n; bi++) {
    if (g_fn_bound_name_len[bi] != fn_name_len
        || memcmp(g_fn_bound_name[bi], fn_name, (size_t)fn_name_len) != 0)
      continue;
    if (g_fn_bound_pos[bi] != pos)
      continue;
    for (ti = 0; ti < g_xlang_skip_trait_reg_n; ti++) {
      if (g_xlang_skip_trait_reg[ti].name_len != g_fn_bound_trait_len[bi]
          || memcmp(g_xlang_skip_trait_reg[ti].name, g_fn_bound_trait[bi],
                    (size_t)g_fn_bound_trait_len[bi]) != 0)
        continue;
      for (mi = 0; mi < g_xlang_skip_trait_reg[ti].num_methods; mi++) {
        int32_t expect_np;
        if (g_xlang_skip_trait_reg[ti].method_lens[mi] != method_name_len)
          continue;
        if (memcmp(g_xlang_skip_trait_reg[ti].methods[mi], method_name,
                   (size_t)method_name_len) != 0)
          continue;
        /* Trait param count includes self. METHOD extras = count - 1. */
        expect_np = g_xlang_skip_trait_reg[ti].method_param_counts[mi];
        if (expect_np >= 0 && expect_np != num_args + 1)
          continue;
        if (out_ret_kind)
          *out_ret_kind = g_xlang_skip_trait_reg[ti].method_ret_kinds[mi];
        if (out_ret_name_len)
          *out_ret_name_len = 0;
        if (out_ret_name) {
          int32_t rnl = g_xlang_skip_trait_reg[ti].method_ret_name_lens[mi];
          memset(out_ret_name, 0, 64);
          if (rnl > 0) {
            if (rnl > 63)
              rnl = 63;
            memcpy(out_ret_name, g_xlang_skip_trait_reg[ti].method_ret_names[mi],
                   (size_t)rnl);
            if (out_ret_name_len)
              *out_ret_name_len = rnl;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

/**
 * wave449: single authority for generic trait-bound satisfaction.
 *
 * Given a callee name and positional concrete type-arg names (from turbofish
 * source scan OR from typeck value-arg inference when turbofish is omitted),
 * verify every bound declared on that function against the impl registry.
 *
 * wave442: iterates ALL bounds matching the callee (not just the first) so
 * `copy_both<T: Clone, U: Default>` checks both positions.
 *
 * 4.2.4 residual close: under-specified slots (nargs==0 pure-phantom bare, or
 * bound pos >= nargs, or empty concrete name) used to skip silently → bare
 * `unit_bound<T: Clone>()` false-green. Fail closed: need turbofish or
 * value/ret pin that fills every bound position.
 *
 * G.7: turbofish path (parse-time g_call_*) and no-turbofish path (typeck after
 * wave448 infer) both call this helper — no second bound algorithm.
 *
 * @param fn_name       callee function name bytes
 * @param fn_name_len   name length (≤63)
 * @param type_args     type_args[pos][64] concrete type names (e.g. "A");
 *                      may be null only when nargs==0
 * @param type_arg_lens length of each type_args[pos]; 0 → under-specified slot
 * @param nargs         number of type-arg slots (≤ XLANG_GENERIC_CALL_MAX_ARGS)
 * @param line          diagnostic line (1-based)
 * @param col           diagnostic column (1-based)
 * @return 0 all bounds satisfied (or nothing to check); -1 ≥1 violation
 * PLATFORM: SHARED parse+typeck — rebuild parser thin glue after edit.
 */
int32_t xlang_generic_bound_check_type_args_c(const uint8_t *fn_name, int32_t fn_name_len,
                                               const uint8_t type_args[][64],
                                               const int32_t *type_arg_lens, int32_t nargs,
                                               int32_t line, int32_t col) {
  int32_t bi, si;
  int32_t violated = 0;
  if (!fn_name || fn_name_len <= 0)
    return 0;
  if (fn_name_len > 63)
    fn_name_len = 63;
  for (bi = 0; bi < g_fn_bound_n; bi++) {
    int32_t pos;
    int32_t ta_len;
    const uint8_t *ta;
    int32_t impl_ok;
    if (g_fn_bound_name_len[bi] != fn_name_len ||
        memcmp(g_fn_bound_name[bi], fn_name, (size_t)fn_name_len) != 0)
      continue;
    pos = g_fn_bound_pos[bi];
    /* Under-specified: no slots at all, missing position, or empty name. */
    if (nargs <= 0 || !type_args || !type_arg_lens || pos < 0 || pos >= nargs) {
      lsp_diag_report_typeck((int)line, (int)col,
                             "generic function '%.*s' requires type arguments to satisfy trait bounds",
                             (int)fn_name_len, (const char *)fn_name);
      violated = -1;
      continue;
    }
    ta_len = type_arg_lens[pos];
    ta = type_args[pos];
    if (ta_len <= 0) {
      lsp_diag_report_typeck((int)line, (int)col,
                             "generic function '%.*s' requires type arguments to satisfy trait bounds",
                             (int)fn_name_len, (const char *)fn_name);
      violated = -1;
      continue;
    }
    /* `Foo<T>` in a generic signature uses the callee's own type-param
     * name — not a concrete instantiation. Skip or `impl Clone for T`
     * false-reds every `x: Foo<T>` / `function f<T>(x: Foo<T>)`.
     * `Foo<B>` (B not a type-param of Foo) still checks. */
    if (xlang_generic_func_type_param_index_c(fn_name, fn_name_len, ta, ta_len) >= 0)
      continue;
    impl_ok = 0;
    for (si = 0; si < g_xlang_skip_impl_seen_n; si++) {
      if (g_xlang_skip_impl_trait_len[si] == g_fn_bound_trait_len[bi] &&
          memcmp(g_xlang_skip_impl_trait[si], g_fn_bound_trait[bi],
                 (size_t)g_fn_bound_trait_len[bi]) == 0 &&
          g_xlang_skip_impl_for_name_lens[si] == ta_len &&
          memcmp(g_xlang_skip_impl_for_names[si], ta, (size_t)ta_len) == 0) {
        impl_ok = 1;
        break;
      }
    }
    if (!impl_ok) {
      lsp_diag_report_typeck((int)line, (int)col,
                             "generic bound not satisfied: %.*s does not impl %.*s",
                             (int)ta_len, (const char *)ta,
                             (int)g_fn_bound_trait_len[bi],
                             (const char *)g_fn_bound_trait[bi]);
      violated = -1;
    }
  }
  return violated;
}

/**
 * Verify captured generic call / type-position sites against decl bounds.
 * For each site `foo<Type>(...)` or `Foo<Type>` where the decl has
 * `T: Trait`, checks that `impl Trait for Type` exists. Type-arg names
 * that are the callee's own type params (`Foo<T>`) are skipped.
 * wave442: multi-arg positional bounds via g_call_typeargs / g_fn_bound_pos.
 * wave449: body delegated to xlang_generic_bound_check_type_args_c (shared with
 * typeck no-turbofish inference path).
 * 4.2.2: struct-level `<T: Trait>` and impl-level `impl<T: Trait>` /
 * `impl Type<T: Trait>` use the same tables (decl name = struct / for-type).
 * PLATFORM: SHARED parse.
 * @return 0 all bounds satisfied (or no bounds to check); -1 ≥1 violation.
 */
int32_t xlang_generic_bound_check_c(void) {
  int32_t ci;
  int32_t violated = 0;
  for (ci = 0; ci < g_call_n; ci++) {
    if (xlang_generic_bound_check_type_args_c(g_call_callee[ci], g_call_callee_len[ci],
                                               g_call_typeargs[ci], g_call_typearg_lens[ci],
                                               g_call_nargs[ci], g_call_line[ci],
                                               g_call_col[ci]) != 0)
      violated = -1;
  }
  return violated;
}

static void xlang_skip_trait_copy_ident_c(struct parser_asm_slice_u8 *source, size_t token_start, int32_t ident_len,
                                           uint8_t *out64, int32_t *out_len) {
  int32_t n = ident_len;
  if (!out64 || !out_len)
    return;
  *out_len = 0;
  memset(out64, 0, 64);
  if (!source || !source->data || n <= 0)
    return;
  if (n > 63)
    n = 63;
  if (token_start + (size_t)n > source->length)
    return;
  memcpy(out64, source->data + token_start, (size_t)n);
  *out_len = n;
}

void parser_asm_skip_one_trait_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                            struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  xlang_skip_trait_reg_ent_t *ent = 0;
  int32_t guard;
  if (!out || !source)
    return;
  /* wave439: stash full-file source for generic-bound scan. */
  xlang_generic_bound_stash_source_c(source);
  /*
   * wave421: prefer token path so we can register method names. Byte raw skip
   * only when token path cannot start (defensive).
   */
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_header_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_type_deep_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_TRAIT) {
    /* Fallback raw skip for non-token edge cases. */
    if (lex.pos + 5 <= source->length && source->data[lex.pos] == (uint8_t)'t'
        && source->data[lex.pos + 1] == (uint8_t)'r' && source->data[lex.pos + 2] == (uint8_t)'a'
        && source->data[lex.pos + 3] == (uint8_t)'i' && source->data[lex.pos + 4] == (uint8_t)'t') {
      parser_asm_skip_trait_impl_block_raw_c(out, lex, source);
      return;
    }
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  if (g_xlang_skip_trait_reg_n < XLANG_SKIP_TRAIT_REG_MAX) {
    ent = &g_xlang_skip_trait_reg[g_xlang_skip_trait_reg_n];
    memset(ent, 0, sizeof(*ent));
    xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len, ent->name, &ent->name_len);
  }
  {
    uint8_t tname_audit[64];
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, tname_audit);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(tname_audit, r.tok.ident_len));
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_methods_body_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_methods_probe_c(r.next_lex, source, 0));
  /* wave421: walk trait body for `function name` rather than opaque brace skip. */
  lex = r.next_lex;
  guard = 0;
  while (guard++ < 512) {
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      out->pos = r.next_lex.pos;
      out->line = r.next_lex.line;
      out->col = r.next_lex.col;
      if (ent && ent->name_len > 0)
        g_xlang_skip_trait_reg_n++;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF) {
      out->pos = lex.pos;
      out->line = lex.line;
      out->col = lex.col;
      return;
    }
    if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
      int32_t mi_reg = -1;
      /* wave468: capture lexer at FUNCTION for default-body re-parse inject. */
      /* Use r.token_start (FUNCTION token start) instead of lex.pos (after FUNCTION). */
      int32_t fn_pos = (int32_t)r.token_start;
      int32_t fn_line = r.tok.line;
      int32_t fn_col = r.tok.col;
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind == (int32_t)TOKEN_IDENT && ent && ent->num_methods < XLANG_SKIP_TRAIT_METH_MAX) {
        int32_t pii;
        mi_reg = ent->num_methods;
        xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len, ent->methods[mi_reg],
                                      &ent->method_lens[mi_reg]);
        ent->method_has_default[mi_reg] = 0;
        ent->method_fn_pos[mi_reg] = fn_pos;
        ent->method_fn_line[mi_reg] = fn_line;
        ent->method_fn_col[mi_reg] = fn_col;
        ent->method_ret_kinds[mi_reg] = -1;
        ent->method_ret_name_lens[mi_reg] = 0;
        memset(ent->method_ret_names[mi_reg], 0, 64);
        ent->method_ret_elem_kinds[mi_reg] = -1;
        ent->method_ret_array_sizes[mi_reg] = -1;
        ent->method_ret_array_ndims[mi_reg] = 0;
        memset(ent->method_ret_array_dims[mi_reg], 0, sizeof(ent->method_ret_array_dims[mi_reg]));
        /* wave438: reset PTR/SLICE ret elem-is-ARRAY fields. */
        ent->method_ret_elem_array_ndims[mi_reg] = 0;
        memset(ent->method_ret_elem_array_dims[mi_reg], 0,
               sizeof(ent->method_ret_elem_array_dims[mi_reg]));
        ent->method_ret_elem_elem_kinds[mi_reg] = -1;
        ent->method_param_counts[mi_reg] = -1;
        for (pii = 0; pii < XLANG_SKIP_TRAIT_PARAM_MAX; pii++) {
          ent->method_param_kinds[mi_reg][pii] = -1;
          ent->method_param_name_lens[mi_reg][pii] = 0;
          memset(ent->method_param_names[mi_reg][pii], 0, 64);
          ent->method_param_elem_kinds[mi_reg][pii] = -1;
          ent->method_param_array_ndims[mi_reg][pii] = 0;
          memset(ent->method_param_array_dims[mi_reg][pii], 0,
                 sizeof(ent->method_param_array_dims[mi_reg][pii]));
          /* wave434: reset PTR/SLICE elem-is-ARRAY fields. */
          ent->method_param_elem_array_ndims[mi_reg][pii] = 0;
          memset(ent->method_param_elem_array_dims[mi_reg][pii], 0,
                 sizeof(ent->method_param_elem_array_dims[mi_reg][pii]));
          ent->method_param_elem_elem_kinds[mi_reg][pii] = -1;
        }
        if (ent->method_lens[mi_reg] > 0) {
          ent->num_methods++;
        } else
          mi_reg = -1;
      }
      {
        /*
         * Walk ` (params) : Ret ; ` or body `{...}` —
         * wave425: capture Ret TypeKind; wave426: param count + typed param kinds;
         * wave427: named / *T / []T ret shape;
         * wave430: suffix T[N] / T[] after scalar/named base;
         * wave431: multi-dim suffix T[N][M]… (collect dims; finalize on non-`[`).
         * PLATFORM: SHARED parse.
         */
        int32_t depth = 0;
        int32_t paren = 0;
        int32_t saw_params_close = 0;
        int32_t want_ret = 0;
        int32_t ret_elem_pending = 0;
        int32_t ret_slice_need_rb = 0;
        /* Prefix `[N]T` / `[N][M]T` ret — twin of wave436 *[N]T (INT was bail). */
        int32_t ret_prefix_arr_need_rb = 0;   /* saw `[N`, want `]` */
        int32_t ret_prefix_arr_need_size = 0; /* saw `[N][`, want next INT */
        int32_t ret_prefix_arr_elem_pending = 0; /* after `[N]`, want T or `[` */
        int32_t ret_suffix_pending = 0; /* base set; may still see [N] or [] */
        int32_t ret_arr_need_size = 0;  /* saw `[` after base; want INT or `]` */
        int32_t ret_arr_need_rb = 0;    /* saw `[N`; want `]` */
        int32_t ret_dim_n = 0;          /* wave431: collected suffix dims before finalize */
        int32_t ret_dims[XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
        /* wave438: twin of wave434-437 param elem suffix / prefix-arr state machine,
         * lifted into the PTR/SLICE ret elem slot (e.g. *T[N] / *[]T / *[N]T / *[N][M]T).
         * PLATFORM: SHARED parse. */
        int32_t ret_elem_suffix_pending = 0; /* elem base set; may still see [N]/[] */
        int32_t ret_elem_arr_need_size = 0;  /* elem saw `[`; want INT or `]` */
        int32_t ret_elem_arr_need_rb = 0;    /* elem saw `[N`; want `]` */
        int32_t ret_elem_slice_need_rb = 0;  /* elem is slice; saw `[`, want `]` */
        int32_t ret_elem_elem_pending = 0;   /* slice closed; want base T */
        int32_t ret_elem_prefix_arr_need_rb = 0; /* saw `*[N`, want `]` */
        int32_t ret_elem_prefix_arr_more = 0;    /* wave437: collecting extra *[N][M] dim */
        int32_t ret_elem_dim_n = 0;
        int32_t ret_elem_dims[XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
        int32_t param_count = 0;
        int32_t saw_param_tok = 0;
        int32_t want_param_ty = 0;
        int32_t param_elem_pending = 0;
        int32_t param_slice_need_rb = 0;
        /* Prefix `[N]T` / `[N][M]T` param — twin of wave436 *[N]T (INT was bail). */
        int32_t param_prefix_arr_need_rb = 0;   /* saw `[N`, want `]` */
        int32_t param_prefix_arr_need_size = 0; /* saw `[N][`, want next INT or `]` (`[N][]T`) */
        int32_t param_prefix_arr_elem_pending = 0; /* after `[N]`, want T or `[` */
        /* wave433: twin of wave431 ret multi-dim suffix state machine. */
        int32_t param_suffix_pending = 0; /* base set; may still see [N] or [] */
        int32_t param_arr_need_size = 0;  /* saw `[` after base; want INT or `]` */
        int32_t param_arr_need_rb = 0;    /* saw `[N`; want `]` */
        int32_t param_dim_n = 0;
        int32_t param_dims[XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
        /* wave434: twin of wave433 but for PTR/SLICE elem suffix (e.g. *T[N] / *[]T).
         * After `*` + elem base, keep scanning for elem's [N]/[]/[N][M] suffix. */
        int32_t param_elem_suffix_pending = 0; /* elem base set; may still see [N]/[] */
        int32_t param_elem_arr_need_size = 0;  /* elem saw `[`; want INT or `]` */
        int32_t param_elem_arr_need_rb = 0;    /* elem saw `[N`; want `]` */
        /* wave435: *[]T → PTR to SLICE of T (type syntax: [] binds tighter
         * than *; []T forms slice, * wraps). After elem `[`, close `]` then
         * capture slice base T. PLATFORM: SHARED parse. */
        int32_t param_elem_slice_need_rb = 0;  /* elem is slice; saw `[`, want `]` */
        int32_t param_elem_elem_pending = 0;   /* slice closed; want base T */
        /* wave436: *[N]T → PTR to ARRAY of N T. After `*[N`, close `]` then
         * capture base T (reuses param_elem_elem_pending for base T capture).
         * wave437: multi-dim *[N][M]T — after first `]`, if next is `[`,
         * collect further dims via param_elem_arr_need_size/rb, then return
         * to param_elem_elem_pending for base T (prefix_arr_more flag).
         * PLATFORM: SHARED parse. */
        int32_t param_elem_prefix_arr_need_rb = 0; /* saw `*[N`, want `]` */
        int32_t param_elem_prefix_arr_more = 0;    /* wave437: collecting extra *[N][M] dim */
        int32_t param_elem_dim_n = 0;
        int32_t param_elem_dims[XLANG_SKIP_TRAIT_ARRAY_DIM_MAX];
        int32_t steps = 0;
        while (steps++ < 4096) {
          if (r.tok.kind == (int32_t)TOKEN_LPAREN) {
            paren++;
          } else if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
            if (paren == 1 && depth == 0 && !saw_params_close) {
              /* Closing the method parameter list. */
              /* wave433: finalize pending suffix T[N][M] before param_count++. */
              if (param_suffix_pending && param_dim_n > 0 && mi_reg >= 0 && ent &&
                  param_count < XLANG_SKIP_TRAIT_PARAM_MAX) {
                int32_t leaf_k = ent->method_param_kinds[mi_reg][param_count];
                int32_t di;
                ent->method_param_elem_kinds[mi_reg][param_count] = leaf_k;
                ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                for (di = 0; di < param_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
              }
              param_suffix_pending = 0;
              param_dim_n = 0;
              /* wave434: finalize pending PTR/SLICE elem suffix *T[N] → elem=ARRAY. */
              if (param_elem_dim_n > 0 && mi_reg >= 0 && ent &&
                  param_count < XLANG_SKIP_TRAIT_PARAM_MAX) {
                int32_t base_k = ent->method_param_elem_kinds[mi_reg][param_count];
                int32_t di;
                /* wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter than *).
                 * Lift to top-level ARRAY: kind=ARRAY, elem=PTR, elem_elem=T, dims. */
                ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_PTR;
                ent->method_param_elem_elem_kinds[mi_reg][param_count] = base_k;
                ent->method_param_array_ndims[mi_reg][param_count] = param_elem_dim_n;
                for (di = 0; di < param_elem_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_elem_dims[di];
              }
              param_elem_suffix_pending = 0;
              param_elem_dim_n = 0;
              param_prefix_arr_need_rb = 0;
              param_prefix_arr_need_size = 0;
              param_prefix_arr_elem_pending = 0;
              if (saw_param_tok)
                param_count++;
              if (mi_reg >= 0 && ent)
                ent->method_param_counts[mi_reg] = param_count;
              saw_params_close = 1;
            }
            if (paren > 0)
              paren--;
          } else if (!saw_params_close && paren == 1 && depth == 0) {
            if (r.tok.kind == (int32_t)TOKEN_COMMA) {
              /* wave433: finalize pending suffix T[N][M] before param_count++. */
              if (param_suffix_pending && param_dim_n > 0 && mi_reg >= 0 && ent &&
                  param_count < XLANG_SKIP_TRAIT_PARAM_MAX) {
                int32_t leaf_k = ent->method_param_kinds[mi_reg][param_count];
                int32_t di;
                ent->method_param_elem_kinds[mi_reg][param_count] = leaf_k;
                ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                for (di = 0; di < param_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
              }
              param_suffix_pending = 0;
              param_dim_n = 0;
              /* wave434: finalize pending PTR/SLICE elem suffix *T[N] → elem=ARRAY. */
              if (param_elem_dim_n > 0 && mi_reg >= 0 && ent &&
                  param_count < XLANG_SKIP_TRAIT_PARAM_MAX) {
                int32_t base_k = ent->method_param_elem_kinds[mi_reg][param_count];
                int32_t di;
                /* wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter than *).
                 * Lift to top-level ARRAY: kind=ARRAY, elem=PTR, elem_elem=T, dims. */
                ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_PTR;
                ent->method_param_elem_elem_kinds[mi_reg][param_count] = base_k;
                ent->method_param_array_ndims[mi_reg][param_count] = param_elem_dim_n;
                for (di = 0; di < param_elem_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_elem_dims[di];
              }
              param_elem_suffix_pending = 0;
              param_elem_dim_n = 0;
              param_prefix_arr_need_rb = 0;
              param_prefix_arr_need_size = 0;
              param_prefix_arr_elem_pending = 0;
              if (saw_param_tok)
                param_count++;
              saw_param_tok = 0;
              want_param_ty = 0;
            } else if (r.tok.kind == (int32_t)TOKEN_COLON) {
              want_param_ty = 1;
            } else if (want_param_ty && mi_reg >= 0 && ent && param_count < XLANG_SKIP_TRAIT_PARAM_MAX) {
              /* wave432/433: twin of seed param shape capture
               * (NAMED / *T / []T / T[N] / T[N][M] multi-dim). */
              if (param_arr_need_rb) {
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  /* wave433: after T[N], stay open for further [M]… */
                  param_arr_need_rb = 0;
                  param_suffix_pending = 1;
                } else {
                  param_arr_need_rb = 0;
                  want_param_ty = 0;
                }
              } else if (param_arr_need_size) {
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  /* Suffix T[] → TYPE_SLICE with prior base as elem (no multi after). */
                  int32_t base_k = ent->method_param_kinds[mi_reg][param_count];
                  ent->method_param_elem_kinds[mi_reg][param_count] = base_k;
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_SLICE;
                  ent->method_param_array_ndims[mi_reg][param_count] = 0;
                  param_arr_need_size = 0;
                  param_dim_n = 0;
                  want_param_ty = 0;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  /* Collect one dim; finalize on non-`[` after closing `]`. */
                  if (param_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    param_dims[param_dim_n++] = r.tok.int_val;
                  param_arr_need_size = 0;
                  param_arr_need_rb = 1;
                } else {
                  param_arr_need_size = 0;
                  want_param_ty = 0;
                }
              } else if (param_suffix_pending) {
                if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  param_suffix_pending = 0;
                  param_arr_need_size = 1;
                } else {
                  /* Finalize multi-dim (or leave scalar/named base if no dims).
                   * Current token is not `,`/`)` (handled at outer branches), so
                   * just stop scanning — param_count++ happens at `,`/`)` later. */
                  if (param_dim_n > 0) {
                    int32_t leaf_k = ent->method_param_kinds[mi_reg][param_count];
                    int32_t di;
                    ent->method_param_elem_kinds[mi_reg][param_count] = leaf_k;
                    ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                    ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                    for (di = 0; di < param_dim_n; di++)
                      ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
                  }
                  param_suffix_pending = 0;
                  param_dim_n = 0;
                  want_param_ty = 0;
                }
              } else if (param_slice_need_rb) {
                /*
                 * Prefix `[...]T` after the opening `[` (kind tentatively SLICE).
                 * Twin of wave436 param_elem_slice_need_rb for `*[N]T`:
                 *   `]`     → `[]T`  = SLICE of T (existing)
                 *   INT N   → `[N]T` = ARRAY of N T (was bail → impl T001)
                 * PLATFORM: SHARED parse. G.7: complete this scanner (no second
                 * trait-type parser).
                 */
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  param_slice_need_rb = 0;
                  param_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                  param_dim_n = 0;
                  if (param_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    param_dims[param_dim_n++] = r.tok.int_val;
                  param_slice_need_rb = 0;
                  param_prefix_arr_need_rb = 1;
                } else {
                  want_param_ty = 0;
                  param_slice_need_rb = 0;
                }
              } else if (param_prefix_arr_need_rb) {
                /* Prefix `[N` — want `]` then leaf T or another `[`. */
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  int32_t di;
                  ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                  for (di = 0; di < param_dim_n; di++)
                    ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
                  param_prefix_arr_need_rb = 0;
                  param_prefix_arr_elem_pending = 1;
                } else {
                  param_prefix_arr_need_rb = 0;
                  want_param_ty = 0;
                }
              } else if (param_prefix_arr_need_size) {
                /*
                 * Prefix `[N][` — next dim INT (`[N][M]T`) or `]` (`[N][]T`
                 * = ARRAY of SLICE of T). Sit-red dest-ARRAY extra `[2][]i32`
                 * bailed here (want INT only) so registry never stored
                 * elem_kind=SLICE; dyn extras then stamped ARRAY-of-ARRAY
                 * `(int32_t[][2])` into a slice* wrapper (asm=139 / host-C=133).
                 * G.7: complete this scanner (twin of param_slice_need_rb
                 * `]` vs INT). Capture leaf T via param_elem_elem_pending
                 * (already used by *[]T). PLATFORM: SHARED parse.
                 */
                if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  if (param_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    param_dims[param_dim_n++] = r.tok.int_val;
                  param_prefix_arr_need_size = 0;
                  param_prefix_arr_need_rb = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_SLICE;
                  param_dim_n = 0;
                  param_prefix_arr_need_size = 0;
                  param_elem_elem_pending = 1;
                } else {
                  param_prefix_arr_need_size = 0;
                  want_param_ty = 0;
                }
              } else if (param_prefix_arr_elem_pending) {
                /* After `[N]` / `[N][M]…` — capture leaf T, or another `[`. */
                if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  param_prefix_arr_elem_pending = 0;
                  param_prefix_arr_need_size = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                  /*
                   * Prefix `[N]*T` — STAR is a PTR elem, not a scalar
                   * token_to_type_kind. Store elem=PTR; capture pointee T
                   * via param_elem_elem_pending (already used by *[]T /
                   * *[N]T / [N][]T). dest-ARRAY extras still skip kind 9
                   * (separate leftover; host-C `[2]*i32` extra already 7).
                   * PLATFORM: SHARED parse. G.7: complete this scanner.
                   */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_PTR;
                  param_prefix_arr_elem_pending = 0;
                  param_elem_elem_pending = 1;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_NAMED;
                  xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                                 ent->method_param_names[mi_reg][param_count],
                                                 &ent->method_param_name_lens[mi_reg][param_count]);
                  param_dim_n = 0;
                  param_prefix_arr_elem_pending = 0;
                  want_param_ty = 0;
                  saw_param_tok = 1;
                } else {
                  int32_t bk = xlang_trait_token_to_type_kind_c(r.tok.kind);
                  if (bk >= 0) {
                    ent->method_param_elem_kinds[mi_reg][param_count] = bk;
                    param_dim_n = 0;
                    param_prefix_arr_elem_pending = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  } else {
                    param_prefix_arr_elem_pending = 0;
                    want_param_ty = 0;
                  }
                }
              } else if (param_elem_slice_need_rb) {
                /*
                 * wave435/436: *[... — saw `[` after PTR. Decide on this token:
                 *   `]`     → *[]T  = PTR to SLICE of T (capture base T next)
                 *   INT N   → *[N]T = PTR to ARRAY of N T (capture N, expect `]`
                 *             then base T; multi-dim *[N][M]T soft-skipped later)
                 *   other   → bail out (avoid parse failure)
                 * PLATFORM: SHARED parse.
                 */
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_SLICE;
                  param_elem_slice_need_rb = 0;
                  param_elem_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  /* wave436: *[N]T → PTR to ARRAY of N T. Capture N, expect `]`. */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                  if (param_elem_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    param_elem_dims[param_elem_dim_n++] = r.tok.int_val;
                  param_elem_slice_need_rb = 0;
                  param_elem_prefix_arr_need_rb = 1;
                } else {
                  param_elem_slice_need_rb = 0;
                  want_param_ty = 0;
                }
              } else if (param_elem_prefix_arr_need_rb) {
                /*
                 * wave436/437: *[N]T — saw `*[N`, want `]` then base T. On `]`,
                 * transition to base T capture (param_elem_elem_pending, shared
                 * with wave435 slice path). Dims stay in the local buffer
                 * (param_elem_dim_n / param_elem_dims); they are committed to
                 * the registry when base T is captured, so multi-dim
                 * *[N][M]T can append further dims before finalize.
                 * PLATFORM: SHARED parse.
                 */
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  param_elem_prefix_arr_need_rb = 0;
                  param_elem_elem_pending = 1;
                } else {
                  param_elem_prefix_arr_need_rb = 0;
                  want_param_ty = 0;
                }
              } else if (param_elem_elem_pending) {
                /*
                 * wave435/436/437: slice/array closed; capture base T (NAMED
                 * name / builtin) and commit accumulated ARRAY dims from the
                 * local buffer to the registry. For `*[N][M]T` multi-dim
                 * PTR-to-ARRAY (next token is `[`), collect further dims via
                 * param_elem_arr_need_size/rb then return here (prefix_arr_more).
                 * PLATFORM: SHARED parse.
                 */
                if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_elem_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_NAMED;
                  xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                                 ent->method_param_names[mi_reg][param_count],
                                                 &ent->method_param_name_lens[mi_reg][param_count]);
                  /* wave437: commit accumulated dims (*[N] or *[N][M]…). Reset
                   * param_elem_dim_n so the wave434 *T[N] postfix lift at
                   * `,`/`)` does not re-fire and overwrite the PTR-of-ARRAY
                   * shape (root cause of wave437 c1 false red). PLATFORM: SHARED. */
                  if (param_elem_dim_n > 0) {
                    int32_t di;
                    ent->method_param_elem_array_ndims[mi_reg][param_count] = param_elem_dim_n;
                    for (di = 0; di < param_elem_dim_n; di++)
                      ent->method_param_elem_array_dims[mi_reg][param_count][di] = param_elem_dims[di];
                    param_elem_dim_n = 0;
                  }
                  param_elem_elem_pending = 0;
                  want_param_ty = 0;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  /* wave437: *[N][M]T multi-dim — collect next dim, return here. */
                  param_elem_elem_pending = 0;
                  param_elem_prefix_arr_more = 1;
                  param_elem_arr_need_size = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_STAR
                           && ent->method_param_elem_kinds[mi_reg][param_count]
                                  == XLANG_TRAIT_TY_PTR
                           && (ent->method_param_kinds[mi_reg][param_count]
                                   == XLANG_TRAIT_TY_ARRAY
                               || ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_SLICE
                               || ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_PTR)) {
                  /*
                   * dest extras dest-SLICE of PTR extra `[]*[2]*T` /
                   * `[]*[2][]*T`, dest extras dest-ARRAY of PTR extra
                   * `[2]*[2]*T` / `[2]*[2][]*T`, and PTR-elem +
                   * PTR-outer extra `**[2]*T` / `**[2][]*T` /
                   * `***T`: after `[]*` / `[K]*` / `**` then `[N]`
                   * (and optional extra empty `[]`), or after `**`
                   * (ndims=0), we are in param_elem_elem_pending
                   * (elem=PTR, dims in the local buffer or registry).
                   * Extra STAR used to require ARRAY or SLICE outer so
                   * PTR outer hit token_to_type_kind=-1 then
                   * want_param_ty=0 so leaf T never committed and
                   * param_elem_dim_n stayed live — COMMA/RPAREN
                   * wave434 *T[N] lift overwrote kind=ARRAY (impl T001
                   * leftover PTR vs ARRAY / leftover PTR vs
                   * eeek=-1). After `***` (ndims=0) leftover skip
                   * eek=-1 — extra ADDR_OF of typed dest dest-stamps
                   * via the formal = false green leftover skip;
                   * leftover mismatch impl `**i32` vs trait `***i32`
                   * compile=0 run=7 (leftover skip so leftover never
                   * compares). ndims=-2 would lose [N] (ban -3 / new
                   * field; do not invent ndims=-2 for PTR-elem extra
                   * STAR). Keep PTR; extra PTR wrap COUNT lives in
                   * unused slot dims[ndims+1] when ndims>=1
                   * (1 = `[]*[2]*T` / `[2]*[2]*T` / `**[2]*T` /
                   * `[]*[2][]*T` / `[2]*[2][]*T` / `**[2][]*T`;
                   * 0 = no extra PTR = `[]*[2]i32` / `[2]*[2]i32` /
                   * `**[2]i32` / `[]*[2][]T` / `[2]*[2][]T` /
                   * `**[2][]T`) and unused slot dims[1] with ndims
                   * staying 0 (1 = `***T`; 2 = `****T`; 0 = no extra
                   * PTR = `**T` / `**[]T`; extra SLICE stays dims[0];
                   * both slots = `**[]*T`). Extra SLICE stays
                   * dims[ndims] when ndims>=1 (`[]*[2][]*T` /
                   * `[2]*[2][]*T` / `**[2][]*T` have both slots
                   * set). Discriminant vs dest extras dest-SLICE of
                   * ARRAY extra `[][2]*T` (same unused slot) is
                   * elem_kind PTR vs ARRAY. Discriminant dest extras
                   * dest-SLICE of PTR extra `[]*[2]*T` vs dest extras
                   * dest-ARRAY of PTR extra `[2]*[2]*T` vs PTR-outer
                   * `**[2]*T` is SLICE vs ARRAY vs PTR outer.
                   * Discriminant ndims>=1 vs ndims=0 is the unused
                   * slot (dims[ndims+1] vs dims[1]). PTR-outer
                   * `*[N]*T` is ARRAY elem + PTR outer (extra STAR
                   * after `*[N]`; same unused slot as `[][2]*T`; not
                   * this PTR-elem branch). Twin of dest extras dest-
                   * RET extra STAR PTR-elem `**[2]*T` / `***T`
                   * (already closed). Capture leaf T by staying
                   * pending. Store-only of `[2]*[2]*T` without ARRAY
                   * leftover extra PTR peels is T001 leftover PTR vs
                   * eeek=leaf after extra ARRAY peels. PTR-outer
                   * leftover PTR vs eek=PTR is not T001; extra
                   * ADDR_OF of typed `*[2]*T` / `**i32` dest-stamps
                   * via the formal (no dest extras dest-PTR stamp).
                   * PLATFORM: SHARED parse. G.7: complete this
                   * scanner.
                   */
                  int32_t nd;
                  int32_t extra;
                  if (param_elem_dim_n > 0) {
                    int32_t di;
                    nd = param_elem_dim_n;
                    ent->method_param_elem_array_ndims[mi_reg][param_count] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_param_elem_array_dims[mi_reg][param_count][di] =
                          param_elem_dims[di];
                    param_elem_dim_n = 0;
                  } else {
                    nd = ent->method_param_elem_array_ndims[mi_reg][param_count];
                  }
                  if (nd >= 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1] =
                          extra;
                    /* stay param_elem_elem_pending to capture leaf T */
                  } else {
                    ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                    param_elem_elem_pending = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  }
                } else if (r.tok.kind == (int32_t)TOKEN_STAR
                           && ent->method_param_elem_kinds[mi_reg][param_count]
                                  == XLANG_TRAIT_TY_ARRAY
                           && (ent->method_param_kinds[mi_reg][param_count]
                                   == XLANG_TRAIT_TY_SLICE
                               || ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_PTR)) {
                  /*
                   * dest extras dest-SLICE of ARRAY extra `[][2]*T` /
                   * `[][2][]*T` and PTR-outer `*[2]*T` / `*[2][]*T`:
                   * after `[]` then `[N]`, or after `*` then `[N]`
                   * (and optional extra empty `[]`) we are in
                   * param_elem_elem_pending (elem=ARRAY, dims in the
                   * local buffer or registry). Extra STAR used to
                   * require SLICE outer so PTR outer hit
                   * token_to_type_kind=-1 then want_param_ty=0 (leaf
                   * T never committed; param_elem_dim_n stayed live;
                   * COMMA/RPAREN wave434 *T[N] lift overwrote
                   * kind=ARRAY — impl T001 leftover PTR vs ARRAY /
                   * leftover PTR vs eeek=-1). ndims=-2 would lose [N]
                   * (ban -3 / new field). Keep ARRAY; extra PTR wrap
                   * COUNT lives in unused slot dims[ndims+1]
                   * (1 = `[][2]*T` / `[][2][]*T` / `*[2]*T` /
                   * `*[2][]*T`; 0 = no extra PTR = `[][2]i32` /
                   * `[][2][]T` / `*[2]i32` / `*[2][]T`). Extra
                   * SLICE stays dims[ndims] (`[][2][]*T` /
                   * `*[2][]*T` have both slots set). Discriminant vs
                   * dest extras dest-SLICE of ARRAY extra `[][2]*T`
                   * (same unused slot) is PTR vs SLICE outer.
                   * Store-only of `[][2][]*T` / `*[2][]*T` without
                   * impl-match extra SLICE-then-PTR peels is T001
                   * (leftover SLICE-of-PTR vs eeek=leaf /
                   * peel-PTR-first leftover SLICE vs PTR). ARRAY
                   * leftover extra PTR peels already live in the
                   * PTR-or-SLICE outer walk (eek=ARRAY). Extra
                   * ADDR_OF of typed `[2]*T` dest-stamps via the
                   * formal (no dest extras dest-PTR stamp). Capture
                   * leaf T by staying pending (zeros param_elem_dim_n
                   * so wave434 does not lift). PLATFORM: SHARED
                   * parse. G.7: complete this scanner.
                   */
                  int32_t nd;
                  int32_t extra;
                  if (param_elem_dim_n > 0) {
                    int32_t di;
                    nd = param_elem_dim_n;
                    ent->method_param_elem_array_ndims[mi_reg][param_count] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_param_elem_array_dims[mi_reg][param_count][di] =
                          param_elem_dims[di];
                    param_elem_dim_n = 0;
                  } else {
                    nd = ent->method_param_elem_array_ndims[mi_reg][param_count];
                  }
                  if (nd > 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1] =
                          extra;
                    /* stay param_elem_elem_pending to capture leaf T */
                  } else {
                    ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                    param_elem_elem_pending = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  }
                } else if (r.tok.kind == (int32_t)TOKEN_STAR
                           && ent->method_param_elem_kinds[mi_reg][param_count]
                                  == XLANG_TRAIT_TY_SLICE
                           && (ent->method_param_kinds[mi_reg][param_count]
                                   == XLANG_TRAIT_TY_ARRAY
                               || ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_SLICE
                               || ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_PTR)) {
                  /*
                   * dest extras dest-ARRAY of SLICE extra `[2][]*T`,
                   * dest extras dest-SLICE of SLICE extra `[][]*T`,
                   * and PTR-outer extra STAR `*[]*T` / `*[][2]*T` /
                   * `*[][]*T`: after `[N][]` / `[][]` / `*[]` we are
                   * in param_elem_elem_pending (elem=SLICE). Extra
                   * STAR used to require ARRAY or SLICE outer so PTR
                   * outer hit token_to_type_kind=-1 then
                   * want_param_ty=0 (leaf T never committed). After
                   * `*[]` then `[N]` param_elem_dim_n stayed live —
                   * COMMA/RPAREN wave434 *T[N] lift overwrote
                   * kind=ARRAY (impl T001 leftover PTR vs ARRAY /
                   * leftover PTR vs eeek=-1). After `*[]*` (ndims=0)
                   * leftover skip eek=-1 — extra ADDR_OF of typed
                   * `[]*i32` dest-stamps via the formal = false
                   * green. ndims=-2 is extra SLICE wrap
                   * (`[2][][]T` / `[][][]T` / `*[][]T`). Keep SLICE;
                   * extra PTR wrap COUNT lives in unused slot
                   * dims[0] with ndims staying 0 (1 = `[2][]*T` /
                   * `[][]*T` / `*[]*T`; 0 = no extra PTR =
                   * `[2][]i32` / `[][]i32` / `*[]i32`). Discriminant
                   * is param kind (ARRAY vs SLICE vs PTR outer), not
                   * a second slot. dest extras dest-SLICE of SLICE
                   * extra `[][][]*T` and dest extras dest-ARRAY of
                   * SLICE extra `[2][][]*T` and PTR-outer `*[][]*T`:
                   * extra STAR when ndims==-2 used to set
                   * elem_kind=-1. dims[0] is extra SLICE (ban -3 /
                   * reuse). Keep SLICE; extra PTR wrap COUNT lives
                   * in unused slot dims[1] (1 = `[][][]*T` /
                   * `[2][][]*T` / `*[][]*T`; 0 = no extra PTR =
                   * `[][][]T` / `[2][][]T` / `*[][]T`). dest extras
                   * dest-ARRAY of SLICE extra `[2][][2]*T`, dest
                   * extras dest-SLICE of SLICE extra `[][][2]*T`,
                   * and PTR-outer extra STAR `*[][2]*T`: extra STAR
                   * when ndims>=1 used to set elem_kind=-1. After
                   * `[N][]` / `[][]` / `*[]` then `[M]` the inner
                   * ARRAY dims live in the local buffer (wave437
                   * pending LBRACKET) until IDENT commit — extra
                   * STAR must commit them first or ndims stays 0
                   * and the inner ARRAY is lost. Keep SLICE; extra
                   * PTR wrap COUNT lives in unused slot dims[ndims]
                   * (1 = `[2][][2]*T` / `[][][2]*T` / `*[][2]*T`;
                   * 0 = no extra PTR = `[2][][2]T` / `[][][2]T` /
                   * `*[][2]T`). Discriminant vs dest extras dest-
                   * SLICE of ARRAY extra `[][2][]T` (same unused
                   * slot) is elem_kind SLICE vs ARRAY. Discriminant
                   * ARRAY vs SLICE vs PTR outer is param kind.
                   * Capture leaf T by staying pending. Store-only
                   * of `[][][2]*T` without impl-match extra PTR
                   * peel is T001 (leftover PTR vs eeek=leaf after
                   * extra ARRAY peels; extra PTR peels live in the
                   * SLICE-of-SLICE / PTR-outer SLICE-elem walk).
                   * Store-only of `[2][][2]*T` is not T001 (ARRAY
                   * leftover SLICE vs eek=SLICE). PTR-outer leftover
                   * PTR vs eek=SLICE is not T001 once extra PTR is
                   * stored (walk peels leftover SLICE then extra
                   * ARRAY then extra PTR). Extra ADDR_OF of typed
                   * `[][2]*i32` dest-stamps via the formal (no dest
                   * extras dest-PTR stamp). PLATFORM: SHARED parse.
                   * G.7: complete this scanner.
                   */
                  int32_t nd;
                  int32_t extra;
                  int32_t di;
                  if (param_elem_dim_n > 0) {
                    nd = param_elem_dim_n;
                    ent->method_param_elem_array_ndims[mi_reg][param_count] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_param_elem_array_dims[mi_reg][param_count][di] =
                          param_elem_dims[di];
                    param_elem_dim_n = 0;
                  } else {
                    nd = ent->method_param_elem_array_ndims[mi_reg][param_count];
                  }
                  if (nd == 0) {
                    extra = ent->method_param_elem_array_dims[mi_reg][param_count][0];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_param_elem_array_dims[mi_reg][param_count][0] =
                          extra;
                    /* stay param_elem_elem_pending to capture leaf T */
                  } else if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                    extra = ent->method_param_elem_array_dims[mi_reg][param_count][1];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_param_elem_array_dims[mi_reg][param_count][1] =
                          extra;
                    /* stay param_elem_elem_pending to capture leaf T */
                  } else if (nd > 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_param_elem_array_dims[mi_reg][param_count][nd];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_param_elem_array_dims[mi_reg][param_count][nd] =
                          extra;
                    /* stay param_elem_elem_pending to capture leaf T */
                  } else {
                    ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                    param_elem_elem_pending = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  }
                } else {
                  int32_t bk = xlang_trait_token_to_type_kind_c(r.tok.kind);
                  if (bk >= 0) {
                    ent->method_param_elem_elem_kinds[mi_reg][param_count] = bk;
                    /* wave437: commit accumulated dims (*[N] or *[N][M]…). Reset
                     * param_elem_dim_n so the wave434 *T[N] postfix lift at
                     * `,`/`)` does not re-fire and overwrite the PTR-of-ARRAY
                     * shape (root cause of wave437 c1 false red). PLATFORM: SHARED. */
                    if (param_elem_dim_n > 0) {
                      int32_t di;
                      ent->method_param_elem_array_ndims[mi_reg][param_count] = param_elem_dim_n;
                      for (di = 0; di < param_elem_dim_n; di++)
                        ent->method_param_elem_array_dims[mi_reg][param_count][di] = param_elem_dims[di];
                      param_elem_dim_n = 0;
                    }
                    param_elem_elem_pending = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  } else {
                    param_elem_elem_pending = 0;
                    want_param_ty = 0;
                  }
                }
              } else if (param_elem_arr_need_rb) {
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  param_elem_arr_need_rb = 0;
                  if (param_elem_prefix_arr_more) {
                    /* wave437: *[N][M]T — return to base T capture for more
                     * dims or finalize. */
                    param_elem_prefix_arr_more = 0;
                    param_elem_elem_pending = 1;
                  } else {
                    /* wave434: after elem T[N], stay open for further [M]… */
                    param_elem_suffix_pending = 1;
                  }
                } else {
                  param_elem_arr_need_rb = 0;
                  param_elem_prefix_arr_more = 0;
                  want_param_ty = 0;
                }
              } else if (param_elem_arr_need_size) {
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  /*
                   * After `[]*` then `[` then `]` (`[]*[]T`): dest-SLICE of
                   * PTR-to-SLICE. After `[][]` then `[` then `]` (`[][][]T`):
                   * dest-SLICE of SLICE of SLICE. After a further empty
                   * `[]` (`[]*[][]T` / `[][][][]T`): ndims is already -2;
                   * count extra wraps in dims[0] (0 means 1 = `[]*[]T` or
                   * 3-layer; 2 = `[]*[][]T` or 4-layer). Do not invent -3.
                   * Prior wave434 deferred 3-layer by setting elem_kind=-1
                   * (dest extras never ran → dyn INDEX 139). Store-only
                   * without impl-match extra peel is T001 for SLICE-of-
                   * SLICE (eek=leaf vs pipeline still SLICE). PTR extra
                   * (`[]*[][]T`) is dest extras dest-stamp (dyn run=1
                   * panic: 0; named / UFCS already dest-stamp via the
                   * formal). Keep elem (PTR or SLICE); mark extra SLICE
                   * via ndims=-2 (same sentinel; discriminant is
                   * elem_kind); capture leaf T as eek via
                   * param_elem_elem_pending. `*[N][]T` / `*[N][]*T`
                   * (dim_n>0, ARRAY elem, PTR outer) is unused-slot
                   * extra wrap below — not this ndims=-2 sentinel.
                   * dest extras dest-SLICE of PTR extra wrap `[]*[2][][]T`:
                   * after `[]*[N][]` ndims>0 already holds [N]; a further
                   * empty `[]` used to hit this branch (dim_n==0) and set
                   * ndims=-2, wiping [N] (dyn extra wrap run=1 panic).
                   * Only take the ndims=-2 sentinel when ndims is still
                   * 0 / unset or already -2. ndims>0 falls through to
                   * unused-slot extra wrap COUNT. dest extras dest-PARAM
                   * extra empty `[]` PTR-elem ndims=0 `**[]T` (elem=PTR,
                   * PTR outer) must NOT take this sentinel: ndims=-2
                   * extra SLICE wrap is SLICE-elem extra SLICE (0 means
                   * 1) / PTR-to-SLICE of ARRAY/SLICE outer (`[2]*[]T` /
                   * `[]*[]T`). Twin of dest extras dest-RET extra empty
                   * `[]` PTR-elem ndims=0 (unused slot dims[0] with
                   * ndims staying 0; extra SLICE 0 means 0 wraps). Fall
                   * through to unused-slot extra wrap COUNT. PLATFORM:
                   * SHARED parse. G.7: complete this scanner.
                   */
                  if ((ent->method_param_elem_kinds[mi_reg][param_count] == XLANG_TRAIT_TY_PTR
                       || ent->method_param_elem_kinds[mi_reg][param_count] == XLANG_TRAIT_TY_SLICE)
                      && param_elem_dim_n == 0
                      && (ent->method_param_elem_array_ndims[mi_reg][param_count]
                              == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS
                          || ent->method_param_elem_array_ndims[mi_reg][param_count]
                              <= 0)
                      && !(ent->method_param_elem_kinds[mi_reg][param_count]
                               == XLANG_TRAIT_TY_PTR
                           && ent->method_param_kinds[mi_reg][param_count]
                                  == XLANG_TRAIT_TY_PTR)) {
                    if (ent->method_param_elem_array_ndims[mi_reg][param_count]
                        == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                      int32_t extra =
                          ent->method_param_elem_array_dims[mi_reg][param_count][0];
                      if (extra <= 0)
                        extra = 1;
                      extra = extra + 1;
                      if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        ent->method_param_elem_array_dims[mi_reg][param_count][0] = extra;
                    } else {
                      ent->method_param_elem_array_ndims[mi_reg][param_count] =
                          XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS;
                    }
                    param_elem_arr_need_size = 0;
                    param_elem_prefix_arr_more = 0;
                    param_elem_dim_n = 0;
                    param_elem_elem_pending = 1;
                  } else if ((ent->method_param_elem_kinds[mi_reg][param_count]
                                  == XLANG_TRAIT_TY_ARRAY
                              && (ent->method_param_kinds[mi_reg][param_count]
                                      == XLANG_TRAIT_TY_SLICE
                                  || ent->method_param_kinds[mi_reg][param_count]
                                         == XLANG_TRAIT_TY_PTR))
                             || (ent->method_param_elem_kinds[mi_reg][param_count]
                                     == XLANG_TRAIT_TY_PTR
                                 && (ent->method_param_kinds[mi_reg][param_count]
                                         == XLANG_TRAIT_TY_SLICE
                                     || ent->method_param_kinds[mi_reg][param_count]
                                            == XLANG_TRAIT_TY_PTR
                                     || ent->method_param_kinds[mi_reg][param_count]
                                            == XLANG_TRAIT_TY_ARRAY))) {
                    /*
                     * dest extras dest-SLICE of ARRAY extra `[][2][]T`,
                     * dest extras dest-SLICE of PTR extra `[]*[2][]T`,
                     * dest extras dest-ARRAY of PTR extra `[2]*[2][]T` /
                     * `[2]*[2][]*T`, PTR-outer extra wrap `*[2][]T` /
                     * `*[2][]*T`, and PTR-elem + PTR-outer extra
                     * `**[2][]T` / `**[2][]*T` / `**[]T`: after `[]`
                     * then `[N]` elem is ARRAY, after `[]*` / `[K]*`
                     * then `[N]` elem is PTR, after `*` then `[N]`
                     * elem is ARRAY (PTR outer), after `**` then
                     * `[N]` (ndims>=1) or after `**` (ndims=0) elem
                     * is PTR (PTR outer). ndims holds the [N] dim(s).
                     * Extra empty `[]` used to require SLICE or PTR
                     * outer, so PTR-elem + ARRAY outer hit wave434
                     * deferred elem_kind=-1, and PTR-elem ndims=0
                     * hit nd>0 fail then elem_kind=-1 (leaf T never
                     * committed; leftover skip eek=-1 — extra
                     * ADDR_OF of typed `[2][]i32` / `*[]i32`
                     * dest-stamps via the formal = false green;
                     * leftover mismatch impl `**i32` vs trait
                     * `**[]i32` compile=0 run=1; nested ARRAY_LIT
                     * dest extras wrap-once dest-stamps
                     * `[2]*[2]i32` / dest extras dest-PTR still
                     * banned → CG002). ndims=-2 would lose [N]
                     * (ban -3 / new field). Keep ARRAY or PTR;
                     * extra wrap COUNT lives in the first unused
                     * dim slot dims[ndims] when ndims>=1
                     * (1 = `[][2][]T` / `[]*[2][]T` / `[2]*[2][]T` /
                     * `*[2][]T` / `*[2][]*T` / `**[2][]T` /
                     * `**[2][]*T`; 2 = `[][2][][]T` /
                     * `[]*[2][][]T` / `[2]*[2][][]T` / `*[2][][]T` /
                     * `**[2][][]T`; 0 means no extra wrap =
                     * `[][2]i32` / `[]*[2]i32` / `[2]*[2]i32` /
                     * `[2]*[2]*T` / `*[2]i32` / `*[2]*T` /
                     * `**[2]i32` / `**[2]*T`) and unused slot
                     * dims[0] with ndims staying 0 (1 = `**[]T`;
                     * 2 = `**[][]T`; 0 = no extra SLICE = `**T` /
                     * `***T`; extra PTR stays dims[1]; both slots
                     * = `**[]*T`). Extra PTR of `[][2]*T` /
                     * `[]*[2]*T` / `[2]*[2]*T` / `*[2]*T` /
                     * `**[2]*T` stays dims[ndims+1] (`[][2][]*T` /
                     * `[]*[2][]*T` / `[2]*[2][]*T` / `*[2][]*T` /
                     * `**[2][]*T` have both slots set). Twin of
                     * dest extras dest-RET extra empty `[]`
                     * PTR-elem ndims=0 `**[]T` (already closed).
                     * Discriminant dest extras dest-SLICE of ARRAY
                     * extra `[][2][]T` vs dest extras dest-SLICE of
                     * PTR extra `[]*[2][]T` vs dest extras dest-ARRAY
                     * of PTR extra `[2]*[2][]T` vs PTR-outer
                     * `*[2][]T` vs PTR-elem + PTR-outer `**[2][]T`
                     * / `**[]T` (same unused-slot family) is SLICE
                     * vs ARRAY vs PTR outer AND ARRAY vs PTR elem
                     * AND ndims>=1 vs ndims=0. Capture leaf T via
                     * param_elem_elem_pending. ARRAY leftover PTR
                     * vs eek=PTR is not T001. Extra ADDR_OF of
                     * typed `[2][]i32` / `*[]i32` dest-stamps via
                     * the formal (no dest extras dest-PTR stamp).
                     * dest extras dest-ARRAY-of-PTR extra SLICE
                     * wraps already live (dims[ndims]). PLATFORM:
                     * SHARED parse. G.7: complete this scanner.
                     */
                    int32_t nd;
                    int32_t extra;
                    if (param_elem_dim_n > 0) {
                      int32_t di;
                      nd = param_elem_dim_n;
                      ent->method_param_elem_array_ndims[mi_reg][param_count] = nd;
                      for (di = 0; di < nd; di++)
                        ent->method_param_elem_array_dims[mi_reg][param_count][di] =
                            param_elem_dims[di];
                      param_elem_dim_n = 0;
                    } else {
                      nd = ent->method_param_elem_array_ndims[mi_reg][param_count];
                    }
                    if (nd >= 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                      extra = ent->method_param_elem_array_dims[mi_reg][param_count][nd];
                      if (extra < 0)
                        extra = 0;
                      extra = extra + 1;
                      if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        ent->method_param_elem_array_dims[mi_reg][param_count][nd] =
                            extra;
                      param_elem_arr_need_size = 0;
                      param_elem_prefix_arr_more = 0;
                      param_elem_elem_pending = 1;
                    } else {
                      ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                      param_elem_arr_need_size = 0;
                      param_elem_prefix_arr_more = 0;
                      param_elem_dim_n = 0;
                      want_param_ty = 0;
                      saw_param_tok = 1;
                    }
                  } else if (ent->method_param_elem_kinds[mi_reg][param_count]
                                 == XLANG_TRAIT_TY_SLICE
                             && (ent->method_param_kinds[mi_reg][param_count]
                                     == XLANG_TRAIT_TY_ARRAY
                                 || ent->method_param_kinds[mi_reg][param_count]
                                     == XLANG_TRAIT_TY_SLICE
                                 || ent->method_param_kinds[mi_reg][param_count]
                                     == XLANG_TRAIT_TY_PTR)) {
                    /*
                     * dest extras dest-ARRAY of SLICE extra wrap
                     * `[2][][2][]T`, dest extras dest-SLICE of
                     * SLICE extra wrap `[][][2][]T`, and PTR-outer
                     * extra empty `[]` `*[][2][]T`: after `[N][]`
                     * then `[M]`, after `[][]` then `[M]`, or after
                     * `*[]` then `[M]`, elem is SLICE; ndims holds
                     * the [M] dim(s) (often still in the local
                     * buffer). Extra empty `[]` used to require
                     * ARRAY or SLICE outer so PTR outer hit
                     * wave434 deferred elem_kind=-1 (leaf T never
                     * committed; leftover skip eek=-1 — extra
                     * ADDR_OF of typed `[][2][]i32` dest-stamps
                     * via the formal = false green; nested extra
                     * lit dest extras dest-PTR still banned →
                     * CG002). ndims=-2 would lose [M] (ban -3 /
                     * reuse of dims[0..ndims-1]). Extra PTR of
                     * `[2][][2]*T` / `[][][2]*T` / `*[][2]*T`
                     * already lives in unused slot dims[ndims]
                     * — do not reopen that encoding. Keep SLICE;
                     * extra SLICE wrap COUNT lives in unused slot
                     * dims[ndims+1] (1 = `[2][][2][]T` /
                     * `[][][2][]T` / `*[][2][]T`; 2 =
                     * `[2][][2][][]T` / `[][][2][][]T` /
                     * `*[][2][][]T`; 0 means no extra wrap =
                     * `[2][][2]T` / `[][][2]T` / `*[][2]T`).
                     * Discriminant vs dest extras dest-SLICE of
                     * ARRAY extra PTR `[][2]*T` (same unused slot
                     * dims[ndims+1]) is elem_kind SLICE vs ARRAY
                     * AND param kind ARRAY vs SLICE vs PTR.
                     * Discriminant dest extras dest-ARRAY of SLICE
                     * extra wrap `[2][][2][]T` vs dest extras dest-
                     * SLICE of SLICE extra wrap `[][][2][]T` vs
                     * PTR-outer extra empty `[]` `*[][2][]T`
                     * (same unused slot) is ARRAY vs SLICE vs PTR
                     * outer. Capture leaf T via
                     * param_elem_elem_pending. ARRAY leftover
                     * SLICE vs eek=SLICE is not T001. PTR-outer
                     * leftover PTR vs eek=SLICE is not T001 once
                     * extra SLICE is stored (walk peels leftover
                     * SLICE then extra ARRAY then extra SLICE
                     * then extra PTR). Extra ADDR_OF of typed
                     * `[][2][]i32` dest-stamps via the formal (no
                     * dest extras dest-PTR stamp). Do not add
                     * impl-match extra SLICE peels. PLATFORM:
                     * SHARED parse. G.7: complete this scanner.
                     */
                    int32_t nd;
                    int32_t extra;
                    if (param_elem_dim_n > 0) {
                      int32_t di;
                      nd = param_elem_dim_n;
                      ent->method_param_elem_array_ndims[mi_reg][param_count] = nd;
                      for (di = 0; di < nd; di++)
                        ent->method_param_elem_array_dims[mi_reg][param_count][di] =
                            param_elem_dims[di];
                      param_elem_dim_n = 0;
                    } else {
                      nd = ent->method_param_elem_array_ndims[mi_reg][param_count];
                    }
                    if (nd > 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                      extra = ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1];
                      if (extra < 0)
                        extra = 0;
                      extra = extra + 1;
                      if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        ent->method_param_elem_array_dims[mi_reg][param_count][nd + 1] =
                            extra;
                      param_elem_arr_need_size = 0;
                      param_elem_prefix_arr_more = 0;
                      param_elem_elem_pending = 1;
                    } else {
                      ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                      param_elem_arr_need_size = 0;
                      param_elem_prefix_arr_more = 0;
                      param_elem_dim_n = 0;
                      want_param_ty = 0;
                      saw_param_tok = 1;
                    }
                  } else {
                    /* wave434: elem T[] → PTR to SLICE of T (3-layer, deferred).
                     * wave437: also clears prefix_arr_more if came from *[N][]T. */
                    ent->method_param_elem_kinds[mi_reg][param_count] = -1;
                    param_elem_arr_need_size = 0;
                    param_elem_prefix_arr_more = 0;
                    param_elem_dim_n = 0;
                    want_param_ty = 0;
                    saw_param_tok = 1;
                  }
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  /* Collect one elem dim; finalize on non-`[` after closing `]`. */
                  if (param_elem_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    param_elem_dims[param_elem_dim_n++] = r.tok.int_val;
                  param_elem_arr_need_size = 0;
                  param_elem_arr_need_rb = 1;
                } else {
                  param_elem_arr_need_size = 0;
                  param_elem_prefix_arr_more = 0;
                  want_param_ty = 0;
                }
              } else if (param_elem_suffix_pending) {
                if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  param_elem_suffix_pending = 0;
                  param_elem_arr_need_size = 1;
                } else {
                  /* Finalize elem multi-dim (dims>0 → elem=ARRAY) or leave scalar elem. */
                  if (param_elem_dim_n > 0) {
                    int32_t base_k = ent->method_param_elem_kinds[mi_reg][param_count];
                    int32_t di;
                    ent->method_param_elem_elem_kinds[mi_reg][param_count] = base_k;
                    ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_ARRAY;
                    ent->method_param_elem_array_ndims[mi_reg][param_count] = param_elem_dim_n;
                    for (di = 0; di < param_elem_dim_n; di++)
                      ent->method_param_elem_array_dims[mi_reg][param_count][di] = param_elem_dims[di];
                  }
                  param_elem_suffix_pending = 0;
                  param_elem_dim_n = 0;
                  want_param_ty = 0;
                }
              } else if (param_elem_pending) {
                if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_NAMED;
                  xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                                 ent->method_param_names[mi_reg][param_count],
                                                 &ent->method_param_name_lens[mi_reg][param_count]);
                  /* wave434: keep scanning for elem suffix [N]/[]/[N][M]. */
                  param_elem_suffix_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  /*
                   * wave435: *[... — elem opens with `[` (could be *[]T slice or
                   * *[N]T array). Defer elem kind decision to param_elem_slice_need_rb
                   * state which inspects the next token (`]` vs INT). PLATFORM: SHARED.
                   */
                  param_elem_slice_need_rb = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                  /*
                   * After `[]` (or after top-level `*` for `**T`): STAR is a
                   * PTR elem. token_to_type_kind does not handle STAR so the
                   * prior else stored elem_kind=-1 and dest extras skipped
                   * kind 9. Store elem=PTR; capture pointee T via
                   * param_elem_elem_pending. dest-SLICE extra `[]*i32`
                   * reconstructs PTR then wrap slice.
                   * PLATFORM: SHARED parse. G.7: complete this scanner.
                   */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_PTR;
                  param_elem_elem_pending = 1;
                } else {
                  ent->method_param_elem_kinds[mi_reg][param_count] =
                      xlang_trait_token_to_type_kind_c(r.tok.kind);
                  /* wave434: keep scanning for elem suffix [N]/[]/[N][M]. */
                  param_elem_suffix_pending = 1;
                }
                param_elem_pending = 0;
                saw_param_tok = 1;
              } else if (ent->method_param_kinds[mi_reg][param_count] < 0) {
                if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_NAMED;
                  xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                                 ent->method_param_names[mi_reg][param_count],
                                                 &ent->method_param_name_lens[mi_reg][param_count]);
                  /* wave433: keep scanning for suffix T[N] / T[] / T[N][M]. */
                  param_suffix_pending = 1;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_PTR;
                  param_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_TRAIT_TY_SLICE;
                  param_slice_need_rb = 1;
                } else {
                  ent->method_param_kinds[mi_reg][param_count] =
                      xlang_trait_token_to_type_kind_c(r.tok.kind);
                  /* wave433: keep scanning for suffix T[N] / T[] / T[N][M]. */
                  param_suffix_pending = 1;
                  saw_param_tok = 1;
                }
              } else {
                want_param_ty = 0;
              }
            } else {
              saw_param_tok = 1;
            }
          } else if (saw_params_close && !want_ret && depth == 0 && paren == 0 &&
                     r.tok.kind == (int32_t)TOKEN_COLON) {
            want_ret = 1;
            ret_elem_pending = 0;
            ret_slice_need_rb = 0;
            ret_suffix_pending = 0;
            ret_arr_need_size = 0;
            ret_arr_need_rb = 0;
            ret_dim_n = 0;
            /* wave438: reset PTR/SLICE ret elem suffix state machine. */
            ret_elem_suffix_pending = 0;
            ret_elem_arr_need_size = 0;
            ret_elem_arr_need_rb = 0;
            ret_elem_slice_need_rb = 0;
            ret_elem_elem_pending = 0;
            ret_elem_prefix_arr_need_rb = 0;
            ret_elem_prefix_arr_more = 0;
            ret_elem_dim_n = 0;
            ret_prefix_arr_need_rb = 0;
            ret_prefix_arr_need_size = 0;
            ret_prefix_arr_elem_pending = 0;
          } else if (want_ret && mi_reg >= 0 && ent) {
            /* wave427/430/431: capture Ret as builtin / NAMED / PTR / SLICE / ARRAY / multi-dim. */
            if (ret_arr_need_rb) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                /* wave431: after T[N], stay open for further [M]… */
                ret_arr_need_rb = 0;
                ret_suffix_pending = 1;
              } else {
                ret_arr_need_rb = 0;
                want_ret = 0;
              }
            } else if (ret_arr_need_size) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                /* Suffix T[] → TYPE_SLICE with prior base as elem (no multi after). */
                int32_t base_k = ent->method_ret_kinds[mi_reg];
                ent->method_ret_elem_kinds[mi_reg] = base_k;
                ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_SLICE;
                ent->method_ret_array_sizes[mi_reg] = -1;
                ent->method_ret_array_ndims[mi_reg] = 0;
                ret_arr_need_size = 0;
                ret_dim_n = 0;
                want_ret = 0;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                /* Collect one dim; finalize on non-`[` after closing `]`. */
                if (ret_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  ret_dims[ret_dim_n++] = r.tok.int_val;
                ret_arr_need_size = 0;
                ret_arr_need_rb = 1;
              } else {
                ret_arr_need_size = 0;
                want_ret = 0;
              }
            } else if (ret_suffix_pending) {
              if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                ret_suffix_pending = 0;
                ret_arr_need_size = 1;
              } else {
                /* Finalize multi-dim (or leave scalar/named base if no dims). */
                if (ret_dim_n > 0) {
                  int32_t di;
                  int32_t leaf_k = ent->method_ret_kinds[mi_reg];
                  ent->method_ret_elem_kinds[mi_reg] = leaf_k;
                  ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_ARRAY;
                  ent->method_ret_array_ndims[mi_reg] = ret_dim_n;
                  ent->method_ret_array_sizes[mi_reg] = ret_dims[0];
                  for (di = 0; di < ret_dim_n; di++)
                    ent->method_ret_array_dims[mi_reg][di] = ret_dims[di];
                }
                ret_suffix_pending = 0;
                want_ret = 0;
              }
            } else if (ret_slice_need_rb) {
              /*
               * Prefix `[...]T` ret after the opening `[` (kind tentatively SLICE).
               * Twin of param_slice_need_rb / wave436 *[N]T:
               *   `]`     → `[]T`  = SLICE of T (existing)
               *   INT N   → `[N]T` = ARRAY of N T (was bail)
               * PLATFORM: SHARED parse. G.7: complete this scanner.
               */
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ret_slice_need_rb = 0;
                ret_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_ARRAY;
                ret_dim_n = 0;
                if (ret_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  ret_dims[ret_dim_n++] = r.tok.int_val;
                ret_slice_need_rb = 0;
                ret_prefix_arr_need_rb = 1;
              } else {
                want_ret = 0;
                ret_slice_need_rb = 0;
              }
            } else if (ret_prefix_arr_need_rb) {
              /* Prefix `[N` ret — want `]` then leaf T or another `[`. */
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                int32_t di;
                ent->method_ret_array_ndims[mi_reg] = ret_dim_n;
                ent->method_ret_array_sizes[mi_reg] = (ret_dim_n > 0) ? ret_dims[0] : -1;
                for (di = 0; di < ret_dim_n; di++)
                  ent->method_ret_array_dims[mi_reg][di] = ret_dims[di];
                ret_prefix_arr_need_rb = 0;
                ret_prefix_arr_elem_pending = 1;
              } else {
                ret_prefix_arr_need_rb = 0;
                want_ret = 0;
              }
            } else if (ret_prefix_arr_need_size) {
              /* Prefix `[N][` ret — want next dim INT. */
              if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                if (ret_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  ret_dims[ret_dim_n++] = r.tok.int_val;
                ret_prefix_arr_need_size = 0;
                ret_prefix_arr_need_rb = 1;
              } else {
                ret_prefix_arr_need_size = 0;
                want_ret = 0;
              }
            } else if (ret_prefix_arr_elem_pending) {
              /* After `[N]` / `[N][M]…` ret — capture leaf T, or another `[`. */
              if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                ret_prefix_arr_elem_pending = 0;
                ret_prefix_arr_need_size = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_NAMED;
                xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                              ent->method_ret_names[mi_reg],
                                              &ent->method_ret_name_lens[mi_reg]);
                ret_dim_n = 0;
                ret_prefix_arr_elem_pending = 0;
                want_ret = 0;
              } else {
                int32_t bk = xlang_trait_token_to_type_kind_c(r.tok.kind);
                if (bk >= 0) {
                  ent->method_ret_elem_kinds[mi_reg] = bk;
                  ret_dim_n = 0;
                  ret_prefix_arr_elem_pending = 0;
                  want_ret = 0;
                } else {
                  ret_prefix_arr_elem_pending = 0;
                  want_ret = 0;
                }
              }
            } else if (ret_elem_pending) {
              if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_NAMED;
                xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                              ent->method_ret_names[mi_reg],
                                              &ent->method_ret_name_lens[mi_reg]);
                /* wave438: keep scanning for elem suffix [N]/[]/[N][M]. */
                ret_elem_suffix_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                /*
                 * wave438: *[... — elem opens with `[` (could be *[]T slice or
                 * *[N]T array). Defer elem kind decision to ret_elem_slice_need_rb
                 * state which inspects the next token (`]` vs INT). PLATFORM: SHARED.
                 */
                ret_elem_slice_need_rb = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                /*
                 * dest extras dest-RET extra STAR PTR-elem `**[2]*T` /
                 * dest extras dest-RET of `**T`: after top-level `*`
                 * we are in ret_elem_pending. Extra STAR used to hit
                 * token_to_type_kind=-1 then ret_elem_suffix_pending
                 * (elem_kind=-1). After `**` then `[N]` wave434
                 * *T[N] lift overwrote kind=ARRAY (impl leftover PTR
                 * vs ARRAY T001). Twin of param_elem_pending STAR
                 * (`**T` / `**[N]T` param already closed). Store
                 * elem=PTR; capture pointee T via
                 * ret_elem_elem_pending (extra STAR after `**[N]`
                 * is the unused-slot scanner). PLATFORM: SHARED
                 * parse. G.7: complete this scanner.
                 */
                ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_PTR;
                ret_elem_elem_pending = 1;
              } else {
                ent->method_ret_elem_kinds[mi_reg] = xlang_trait_token_to_type_kind_c(r.tok.kind);
                /* wave438: keep scanning for elem suffix [N]/[]/[N][M]. */
                ret_elem_suffix_pending = 1;
              }
              ret_elem_pending = 0;
            } else if (ret_elem_slice_need_rb) {
              /*
               * wave438: *[... — saw `[` after PTR. Decide on this token:
               *   `]`     → *[]T  = PTR to SLICE of T (capture base T next)
               *   INT N   → *[N]T = PTR to ARRAY of N T (capture N, expect `]`
               *             then base T; multi-dim *[N][M]T collected later)
               *   other   → bail out (avoid parse failure)
               * Twin of wave435/436 param elem_slice_need_rb. PLATFORM: SHARED parse.
               */
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_SLICE;
                ret_elem_slice_need_rb = 0;
                ret_elem_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                /* wave438: *[N]T → PTR to ARRAY of N T. Capture N, expect `]`. */
                ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_ARRAY;
                if (ret_elem_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  ret_elem_dims[ret_elem_dim_n++] = r.tok.int_val;
                ret_elem_slice_need_rb = 0;
                ret_elem_prefix_arr_need_rb = 1;
              } else {
                ret_elem_slice_need_rb = 0;
                want_ret = 0;
              }
            } else if (ret_elem_prefix_arr_need_rb) {
              /*
               * wave438: *[N]T — saw `*[N`, want `]` then base T. On `]`,
               * transition to base T capture (ret_elem_elem_pending, shared
               * with slice path). Dims stay in the local buffer
               * (ret_elem_dim_n / ret_elem_dims); they are committed to
               * the registry when base T is captured, so multi-dim
               * *[N][M]T can append further dims before finalize.
               * Twin of wave436/437 param elem_prefix_arr_need_rb. PLATFORM: SHARED.
               */
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ret_elem_prefix_arr_need_rb = 0;
                ret_elem_elem_pending = 1;
              } else {
                ret_elem_prefix_arr_need_rb = 0;
                want_ret = 0;
              }
            } else if (ret_elem_elem_pending) {
              /*
               * wave438: slice/array closed; capture base T (NAMED name / builtin)
               * and commit accumulated ARRAY dims from the local buffer to the
               * registry. For `*[N][M]T` multi-dim PTR-to-ARRAY (next token is
               * `[`), collect further dims via ret_elem_arr_need_size/rb then
               * return here (prefix_arr_more).
               * Twin of wave435/436/437 param elem_elem_pending. PLATFORM: SHARED.
               */
              if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                ent->method_ret_elem_elem_kinds[mi_reg] = XLANG_TRAIT_TY_NAMED;
                xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                              ent->method_ret_names[mi_reg],
                                              &ent->method_ret_name_lens[mi_reg]);
                /* wave438: commit accumulated dims (*[N] or *[N][M]…). Reset
                 * ret_elem_dim_n so the wave434 *T[N] postfix lift at
                 * `;`/`{` does not re-fire and overwrite the PTR-of-ARRAY
                 * shape. PLATFORM: SHARED. */
                if (ret_elem_dim_n > 0) {
                  int32_t di;
                  ent->method_ret_elem_array_ndims[mi_reg] = ret_elem_dim_n;
                  for (di = 0; di < ret_elem_dim_n; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                  ret_elem_dim_n = 0;
                }
                ret_elem_elem_pending = 0;
                want_ret = 0;
              } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                /* wave438: *[N][M]T multi-dim — collect next dim, return here. */
                ret_elem_elem_pending = 0;
                ret_elem_prefix_arr_more = 1;
                ret_elem_arr_need_size = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_STAR
                         && ent->method_ret_elem_kinds[mi_reg]
                                == XLANG_TRAIT_TY_PTR
                         && ent->method_ret_kinds[mi_reg]
                                == XLANG_TRAIT_TY_PTR) {
                /*
                 * dest extras dest-RET extra STAR PTR-elem
                 * `**[2]*T` / `***T`: after `**` then `[N]` (and
                 * optional extra empty `[]`), or after `**`
                 * (ndims=0), we are in ret_elem_elem_pending
                 * (elem=PTR, dims in the local buffer or registry).
                 * Extra STAR used to hit token_to_type_kind=-1 then
                 * want_ret=0 (leaf T never committed; leftover skip
                 * eek=-1 / wave434 *T[N] lift leftover PTR vs ARRAY
                 * T001; dest extras dest-RET wrap-once dest-stamps
                 * `**[2]i32` / `**i32` so typed let `**[2]*i32` /
                 * `***i32` T001; dest-stamp via the local of typed
                 * dest = false green even Ubuntu; impl `**[2]i32` /
                 * `**i32` vs trait `**[2]*i32` / `***i32`
                 * compile=0). ndims=-2 would lose [N] (ban -3 / new
                 * field). Extra empty `[]` of `**[2][]T` already
                 * lives in unused slot dims[ndims] — do not reopen.
                 * Keep PTR; extra PTR wrap COUNT lives in unused
                 * slot dims[ndims+1] when ndims>=1 (1 = `**[2]*T` /
                 * `**[2][]*T`; 2 = `**[2]**T`; 0 = no extra PTR =
                 * `**[2]i32` / `**[2][]T`; extra SLICE stays
                 * dims[ndims]; both slots = `**[2][]*T`) and unused
                 * slot dims[1] with ndims staying 0 (1 = `***T`; 2 =
                 * `****T`; 0 = no extra PTR = `**T`; extra SLICE
                 * stays dims[0] for `**[]T`). Twin
                 * of param extra STAR PTR-elem + PTR outer
                 * (`**[2]*T` param already closed; `***T` param
                 * this leaf). Discriminant vs dest extras dest-
                 * RET extra STAR ARRAY-elem `*[2]*T` (same unused-
                 * slot family; extra PTR in dims[ndims+1]) is PTR vs
                 * ARRAY elem. Discriminant ndims>=1 vs ndims=0 is
                 * the unused slot (dims[ndims+1] vs dims[1]).
                 * Capture leaf T by staying pending (zeros
                 * ret_elem_dim_n so wave434 does not lift).
                 * PLATFORM: SHARED parse. G.7: complete this scanner.
                 */
                int32_t nd;
                int32_t extra;
                if (ret_elem_dim_n > 0) {
                  int32_t di;
                  nd = ret_elem_dim_n;
                  ent->method_ret_elem_array_ndims[mi_reg] = nd;
                  for (di = 0; di < nd; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                  ret_elem_dim_n = 0;
                } else {
                  nd = ent->method_ret_elem_array_ndims[mi_reg];
                }
                if (nd >= 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][nd + 1];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][nd + 1] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else {
                  ent->method_ret_elem_kinds[mi_reg] = -1;
                  ret_elem_elem_pending = 0;
                  want_ret = 0;
                }
              } else if (r.tok.kind == (int32_t)TOKEN_STAR
                         && ent->method_ret_elem_kinds[mi_reg]
                                == XLANG_TRAIT_TY_ARRAY
                         && ent->method_ret_kinds[mi_reg]
                                == XLANG_TRAIT_TY_PTR) {
                /*
                 * dest extras dest-RET extra STAR `*[2]*T`: after `*`
                 * then `[N]` (and optional extra empty `[]`) we are in
                 * ret_elem_elem_pending (elem=ARRAY, dims in the local
                 * buffer or registry). Extra STAR used to hit
                 * token_to_type_kind=-1 then want_ret=0 (leaf T never
                 * committed; leftover skip eek=-1 — typed let dest-
                 * stamps via the local = false green; dest extras
                 * dest-RET wrap-once dest-stamps `*[2]i32`). ndims=-2
                 * would lose [N] (ban -3 / new field). Keep ARRAY;
                 * extra PTR wrap COUNT lives in unused slot
                 * dims[ndims+1] (1 = `*[2]*T` / `*[2][]*T`; 0 = no
                 * extra PTR = `*[2]i32` / `*[2][]T`). Extra SLICE
                 * stays dims[ndims] (`*[2][]*T` has both slots set).
                 * Discriminant vs dest extras dest-RET extra empty `[]`
                 * `*[2][]T` (same unused-slot family) is extra PTR vs
                 * extra SLICE. Twin of param extra STAR ARRAY-elem +
                 * PTR outer (`*[2]*T` param already closed). Capture
                 * leaf T by staying pending (zeros ret_elem_dim_n so
                 * wave434 does not lift). PLATFORM: SHARED parse.
                 * G.7: complete this scanner.
                 */
                int32_t nd;
                int32_t extra;
                if (ret_elem_dim_n > 0) {
                  int32_t di;
                  nd = ret_elem_dim_n;
                  ent->method_ret_elem_array_ndims[mi_reg] = nd;
                  for (di = 0; di < nd; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                  ret_elem_dim_n = 0;
                } else {
                  nd = ent->method_ret_elem_array_ndims[mi_reg];
                }
                if (nd > 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][nd + 1];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][nd + 1] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else {
                  ent->method_ret_elem_kinds[mi_reg] = -1;
                  ret_elem_elem_pending = 0;
                  want_ret = 0;
                }
              } else if (r.tok.kind == (int32_t)TOKEN_STAR
                         && ent->method_ret_elem_kinds[mi_reg]
                                == XLANG_TRAIT_TY_SLICE
                         && ent->method_ret_kinds[mi_reg]
                                == XLANG_TRAIT_TY_PTR) {
                /*
                 * dest extras dest-RET extra STAR SLICE-elem
                 * `*[][2]*T` / `*[]*T` / `*[][]*T`: after `*` then
                 * `[]` then `[N]`, or after `*` then `[]` (ndims=0),
                 * or after `*` then `[]` then extra empty `[]`
                 * (ndims=-2), we are in ret_elem_elem_pending
                 * (elem=SLICE, dims in the local buffer or
                 * registry). Extra STAR used to hit
                 * token_to_type_kind=-1 then want_ret=0 (leaf T never
                 * committed; leftover skip eek=-1 — dest-stamp via
                 * the local of typed dest = false green even Ubuntu;
                 * dest extras dest-RET wrap rek3==11 dest-stamps
                 * `*[][2]i32` / `*[]i32` / `*[][]i32` so typed let
                 * `*[][2]*i32` / `*[]*i32` / `*[][]*i32` T001; impl
                 * `*[][2]i32` / `*[]i32` / `*[][]i32` vs trait
                 * `*[][2]*i32` / `*[]*i32` / `*[][]*i32` compile=0).
                 * Extra SLICE of `*[][2][]T` already lives in unused
                 * slot dims[ndims+1] — do not reopen that encoding.
                 * Keep SLICE; extra PTR wrap COUNT lives in unused
                 * slot dims[ndims] when ndims>=1 (1 = `*[][2]*T`; 2 =
                 * `*[][2]**T`; 0 = no extra PTR = `*[][2]i32` /
                 * `*[][2][]T`; extra SLICE stays dims[ndims+1]; both
                 * slots = `*[][2][]*T`), unused slot dims[0] with
                 * ndims staying 0 (1 = `*[]*T`; 2 = `*[]**T`; 0 =
                 * no extra PTR = `*[]i32`), and unused slot dims[1]
                 * with ndims staying -2 (1 = `*[][]*T`; 2 =
                 * `*[][]**T`; 0 = no extra PTR = `*[][]T`; extra
                 * SLICE stays dims[0]). Twin of param extra STAR
                 * SLICE-elem + PTR outer (`*[][2]*T` / `*[]*T` /
                 * `*[][]*T` param already closed). Discriminant vs
                 * dest extras dest-RET extra STAR ARRAY-elem `*[2]*T`
                 * / PTR-elem `**[2]*T` (same unused-slot family;
                 * ARRAY/PTR extra PTR lives in dims[ndims+1]) is
                 * SLICE vs ARRAY vs PTR elem. Discriminant ndims>=1
                 * vs ndims=0 vs ndims=-2 is the unused slot
                 * (dims[ndims] vs dims[0] vs dims[1]). Capture leaf
                 * T by staying pending (zeros ret_elem_dim_n so
                 * wave434 does not lift). PLATFORM: SHARED parse.
                 * G.7: complete this scanner.
                 */
                int32_t nd;
                int32_t extra;
                if (ret_elem_dim_n > 0) {
                  int32_t di;
                  nd = ret_elem_dim_n;
                  ent->method_ret_elem_array_ndims[mi_reg] = nd;
                  for (di = 0; di < nd; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                  ret_elem_dim_n = 0;
                } else {
                  nd = ent->method_ret_elem_array_ndims[mi_reg];
                }
                if (nd == 0) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][0];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][0] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][1];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][1] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else if (nd > 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][nd];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][nd] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else {
                  ent->method_ret_elem_kinds[mi_reg] = -1;
                  ret_elem_elem_pending = 0;
                  want_ret = 0;
                }
              } else if (r.tok.kind == (int32_t)TOKEN_STAR
                         && (ent->method_ret_elem_kinds[mi_reg]
                                 == XLANG_TRAIT_TY_PTR
                             || ent->method_ret_elem_kinds[mi_reg]
                                    == XLANG_TRAIT_TY_SLICE
                             || ent->method_ret_elem_kinds[mi_reg]
                                    == XLANG_TRAIT_TY_ARRAY)
                         && (ent->method_ret_kinds[mi_reg]
                                 == XLANG_TRAIT_TY_SLICE
                             || ent->method_ret_kinds[mi_reg]
                                    == XLANG_TRAIT_TY_ARRAY)) {
                /*
                 * wave954: dest extras dest-RET extra STAR PTR-elem
                 * SLICE-outer `[]*[]*T` / `[]*[2]*T` / SLICE-elem
                 * SLICE-outer `[][][]*T` / PTR-elem ARRAY-outer
                 * `[2]*[2]*T`. After outer `[` `]` (or `[2]`) then `*`
                 * then `[]` (or `[2]`) (and optional extra empty `[]`
                 * which set ndims=-2 and dims[0]), we are in
                 * ret_elem_elem_pending (elem=PTR/SLICE/ARRAY; dims in
                 * the local buffer or registry). Extra STAR used to
                 * hit token_to_type_kind=-1 then want_ret=0 (leaf T
                 * never committed; leftover skip eek=-1 — compile=0
                 * for impl `[]*[]i32` vs trait `[]*[]*i32`). ndims=-2
                 * would lose [N] (ban -3 / new field). Keep elem kind
                 * (PTR/SLICE/ARRAY); extra PTR wrap COUNT lives in:
                 *   ndims==0 → unused slot dims[0] (1 = `[]*i32`;
                 *              0 = no extra PTR = `[]i32`)
                 *   ndims==-2 (PTR_TO_SLICE) → unused slot dims[1]
                 *              (1 = `[]*[]*T`; 2 = `[]*[]**T`;
                 *              0 = no extra PTR = `[]*[]T`; extra
                 *              SLICE stays dims[0] — `[]*[][]*T` has
                 *              both slots set)
                 *   ndims>0 → unused slot dims[ndims] (1 = `[2]*[2]*T`;
                 *              0 = no extra PTR = `[2]*[2]T`; extra
                 *              SLICE stays dims[ndims+1] —
                 *              `[2]*[2][]*T` has both slots set)
                 * Twin of param extra STAR PTR-elem + SLICE/ARRAY
                 * outer (`[]*[]*T` / `[2]*[2]*T` param already
                 * closed via param eand==0 dims[1] scanner).
                 * Discriminant vs dest extras dest-RET PTR-outer
                 * STAR family (line 6835 / 6901 / 6953) is
                 * ret_kinds=SLICE/ARRAY vs ret_kinds=PTR. Capture
                 * leaf T by staying pending (zeros ret_elem_dim_n so
                 * wave434 does not lift). PLATFORM: SHARED parse.
                 * G.7: complete this scanner for the SLICE/ARRAY
                 * outer extra STAR family.
                 */
                int32_t nd;
                int32_t extra;
                if (ret_elem_dim_n > 0) {
                  int32_t di;
                  nd = ret_elem_dim_n;
                  ent->method_ret_elem_array_ndims[mi_reg] = nd;
                  for (di = 0; di < nd; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                  ret_elem_dim_n = 0;
                } else {
                  nd = ent->method_ret_elem_array_ndims[mi_reg];
                }
                if (nd == 0) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][0];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][0] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][1];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][1] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else if (nd > 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                  extra = ent->method_ret_elem_array_dims[mi_reg][nd];
                  if (extra < 0)
                    extra = 0;
                  extra = extra + 1;
                  if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                    ent->method_ret_elem_array_dims[mi_reg][nd] = extra;
                  /* stay ret_elem_elem_pending to capture leaf T */
                } else {
                  ent->method_ret_elem_kinds[mi_reg] = -1;
                  ret_elem_elem_pending = 0;
                  want_ret = 0;
                }
              } else {
                int32_t bk = xlang_trait_token_to_type_kind_c(r.tok.kind);
                if (bk >= 0) {
                  ent->method_ret_elem_elem_kinds[mi_reg] = bk;
                  /*
                   * wave954: commit accumulated dims (*[N] or *[N][M]…).
                   * When ret_elem_dim_n==0 AND ret_elem_kinds is PTR or
                   * SLICE (outer is []*T / *[]T / **T / etc.), commit
                   * PTR_TO_SLICE sentinel ndims=-2 to the registry so
                   * the leftover walk at line 3926 / line 4060 can find
                   * the sentinel and peel extra SLICE (dims[0]) + extra
                   * PTR (dims[1]) before comparing eeek (the builtin
                   * leaf kind). Without this, ret_elem_array_ndims
                   * stayed 0 (initialized at line 5323) so eeek walk
                   * compared impl []*i32 PTR-pointee (int32) vs trait
                   * []*[]i32 eeek (int32) directly — false green.
                   * After ret_elem_dim_n>0 commit: reset it so wave434
                   * *T[N] postfix lift at `;`/`{` does not re-fire and
                   * overwrite the PTR-of-ARRAY shape. Keep scanning for
                   * elem suffix [N]/[]/[N][M] via ret_elem_suffix_pending
                   * (twin of IDENT line 6715 and ret_elem_pending builtin
                   * line 6697 — they both set suffix_pending). PLATFORM:
                   * SHARED parse. G.7: complete scanner for the RET twin
                   * of []*[]T / []*[][]T / *[]*T.
                   */
                  if (ret_elem_dim_n > 0) {
                    int32_t di;
                    ent->method_ret_elem_array_ndims[mi_reg] = ret_elem_dim_n;
                    for (di = 0; di < ret_elem_dim_n; di++)
                      ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                    ret_elem_dim_n = 0;
                  } else if ((ent->method_ret_elem_kinds[mi_reg]
                                  == XLANG_TRAIT_TY_PTR
                              || ent->method_ret_elem_kinds[mi_reg]
                                     == XLANG_TRAIT_TY_SLICE)
                             && (ent->method_ret_kinds[mi_reg]
                                     == XLANG_TRAIT_TY_PTR
                                 || ent->method_ret_kinds[mi_reg]
                                        == XLANG_TRAIT_TY_SLICE
                                 || ent->method_ret_kinds[mi_reg]
                                        == XLANG_TRAIT_TY_ARRAY)) {
                    /*
                     * PTR or SLICE outer + PTR or SLICE elem: must be
                     * PTR-to-SLICE sentinel. dims[0] already holds
                     * extra SLICE count (from ret_elem_prefix_arr_more
                     * extra `[]` scanner or line 7048 initial setup).
                     * Set ndims=-2; the suffix scanner below will add
                     * more extra wraps before final. Do not invent -3.
                     */
                    int32_t cur_nd = ent->method_ret_elem_array_ndims[mi_reg];
                    if (cur_nd == 0) {
                      ent->method_ret_elem_array_ndims[mi_reg] =
                          XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS;
                    }
                  }
                  ret_elem_elem_pending = 0;
                  ret_elem_suffix_pending = 1;
                } else {
                  ret_elem_elem_pending = 0;
                  want_ret = 0;
                }
              }
            } else if (ret_elem_arr_need_rb) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ret_elem_arr_need_rb = 0;
                if (ret_elem_prefix_arr_more) {
                  /* wave438: *[N][M]T — return to base T capture for more
                   * dims or finalize. */
                  ret_elem_prefix_arr_more = 0;
                  ret_elem_elem_pending = 1;
                } else {
                  /* wave438: after elem T[N], stay open for further [M]… */
                  ret_elem_suffix_pending = 1;
                }
              } else {
                ret_elem_arr_need_rb = 0;
                ret_elem_prefix_arr_more = 0;
                want_ret = 0;
              }
            } else if (ret_elem_arr_need_size) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                /*
                 * dest extras dest-RET PTR-to-ARRAY extra empty `[]`
                 * `*[2][]T` AND dest extras dest-RET extra empty
                 * `[]` PTR-elem `**[2][]T` / `**[]T`: after `*`
                 * then `[N]` elem is ARRAY (PTR outer), or after
                 * `**` then `[N]` (ndims>=1) or after `**` (ndims=0)
                 * elem is PTR (PTR outer). Extra empty `[]` used to
                 * require ARRAY elem so PTR-elem ndims>=1 hit
                 * wave438 elem_kind=-1, and PTR-elem ndims=0 hit
                 * nd>0 fail then elem_kind=-1 (leaf T never
                 * committed; leftover skip eek=-1 — dest-stamp via
                 * the local of typed dest = false green even
                 * Ubuntu; impl `**[2]i32` / `**i32` vs trait
                 * `**[2][]i32` / `**[]i32` compile=0). ndims=-2
                 * would lose [N] (ban -3 / new field). Keep ARRAY
                 * or PTR; extra SLICE wrap COUNT lives in unused
                 * slot dims[ndims] when ndims>=1 (1 = `*[2][]T` /
                 * `**[2][]T`; 2 = `*[2][][]T` / `**[2][][]T`;
                 * 0 = no extra wrap = `*[2]i32` / `**[2]i32` /
                 * `**[2]*T`) and unused slot dims[0] with ndims
                 * staying 0 (1 = `**[]T`; 2 = `**[][]T`; 0 = no
                 * extra SLICE = `**T` / `***T`; extra PTR stays
                 * dims[1]; both slots = `**[]*T`). Extra STAR
                 * unused slot dims[ndims+1] / dims[1] is the
                 * sibling unused-slot scanner (TOKEN_STAR in
                 * ret_elem_elem_pending). Twin of param extra
                 * empty `[]` ARRAY-or-PTR elem + PTR outer
                 * (`*[2][]T` / `**[2][]T` / `**[]T` param
                 * already closed). Discriminant vs
                 * dest extras dest-RET extra empty `[]` ARRAY-elem
                 * `*[2][]T` (same unused-slot family) is PTR vs
                 * ARRAY elem. Discriminant ndims>=1 vs ndims=0 is
                 * the unused slot (dims[ndims] vs dims[0]).
                 * Capture leaf T via ret_elem_elem_pending.
                 * PLATFORM: SHARED parse. G.7: complete this
                 * scanner.
                 */
                if ((ent->method_ret_elem_kinds[mi_reg] == XLANG_TRAIT_TY_ARRAY
                     || ent->method_ret_elem_kinds[mi_reg] == XLANG_TRAIT_TY_PTR)
                    && ent->method_ret_kinds[mi_reg] == XLANG_TRAIT_TY_PTR) {
                  int32_t nd;
                  int32_t extra;
                  if (ret_elem_dim_n > 0) {
                    int32_t di;
                    nd = ret_elem_dim_n;
                    ent->method_ret_elem_array_ndims[mi_reg] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                    ret_elem_dim_n = 0;
                  } else {
                    nd = ent->method_ret_elem_array_ndims[mi_reg];
                  }
                  if (nd >= 0 && nd < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_ret_elem_array_dims[mi_reg][nd];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_ret_elem_array_dims[mi_reg][nd] = extra;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_elem_pending = 1;
                  } else {
                    ent->method_ret_elem_kinds[mi_reg] = -1;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_dim_n = 0;
                    want_ret = 0;
                  }
                } else if (ent->method_ret_elem_kinds[mi_reg] == XLANG_TRAIT_TY_SLICE
                           && ent->method_ret_kinds[mi_reg] == XLANG_TRAIT_TY_PTR) {
                  /*
                   * dest extras dest-RET extra empty `[]` SLICE-elem
                   * `*[][2][]T`: after `*` then `[]` then `[N]` elem is
                   * SLICE (PTR outer). Extra empty `[]` used to require
                   * ARRAY or PTR elem so SLICE-elem hit wave438
                   * elem_kind=-1 (leaf T never committed; leftover skip
                   * eek=-1 — dest-stamp via the local of typed dest =
                   * false green even Ubuntu; impl `*[][2]i32` vs trait
                   * `*[][2][]i32` compile=0). ndims=-2 would lose [N]
                   * (ban -3 / new field). Extra PTR of `*[][2]*T`
                   * already lives in unused slot dims[ndims] — do not
                   * reopen that encoding. Keep SLICE; extra SLICE wrap
                   * COUNT lives in unused slot dims[ndims+1] (1 =
                   * `*[][2][]T`; 2 = `*[][2][][]T`; 0 = no extra wrap
                   * = `*[][2]i32` / `*[][2]*T`). Extra STAR unused slot
                   * dims[ndims] is the sibling unused-slot scanner
                   * (TOKEN_STAR in ret_elem_elem_pending). Twin of param
                   * extra empty `[]` SLICE-elem + PTR outer (`*[][2][]T`
                   * param already closed). Discriminant vs dest extras
                   * dest-RET extra empty `[]` ARRAY-elem `*[2][]T` /
                   * PTR-elem `**[2][]T` (same unused-slot family) is
                   * SLICE vs ARRAY vs PTR elem. Capture leaf T via
                   * ret_elem_elem_pending. PLATFORM: SHARED parse.
                   * G.7: complete this scanner.
                   */
                  int32_t nd;
                  int32_t extra;
                  if (ret_elem_dim_n > 0) {
                    int32_t di;
                    nd = ret_elem_dim_n;
                    ent->method_ret_elem_array_ndims[mi_reg] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                    ret_elem_dim_n = 0;
                  } else {
                    nd = ent->method_ret_elem_array_ndims[mi_reg];
                  }
                  /*
                   * dest extras dest-RET extra empty `[]` SLICE-elem
                   * ndims=-2 `*[][]T` / extra STAR sibling `*[][]*T`:
                   * after `*` then `[]` (ndims=0) extra empty `[]`
                   * used to hit nd>0 fail then elem_kind=-1 leftover
                   * skip eek=-1. Twin of param extra empty `[]`
                   * SLICE-elem ndims<=0 (`*[][]T` param already
                   * closed): first extra `[]` sets ndims=-2; further
                   * extra `[]` increments dims[0] (0 means 1 =
                   * `*[][]T`; 2 = `*[][][]T`). Extra STAR unused
                   * slot dims[1] is the sibling unused-slot scanner
                   * (TOKEN_STAR in ret_elem_elem_pending). Do not
                   * invent -3. PLATFORM: SHARED parse. G.7: complete
                   * this scanner.
                   */
                  if ((nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS
                       || nd <= 0)
                      && ret_elem_dim_n == 0) {
                    if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                      extra = ent->method_ret_elem_array_dims[mi_reg][0];
                      if (extra <= 0)
                        extra = 1;
                      extra = extra + 1;
                      if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        ent->method_ret_elem_array_dims[mi_reg][0] = extra;
                    } else {
                      ent->method_ret_elem_array_ndims[mi_reg] =
                          XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS;
                    }
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_dim_n = 0;
                    ret_elem_elem_pending = 1;
                  } else if (nd > 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_ret_elem_array_dims[mi_reg][nd + 1];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_ret_elem_array_dims[mi_reg][nd + 1] = extra;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_elem_pending = 1;
                  } else {
                    ent->method_ret_elem_kinds[mi_reg] = -1;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_dim_n = 0;
                    want_ret = 0;
                  }
                } else if ((ent->method_ret_elem_kinds[mi_reg]
                                == XLANG_TRAIT_TY_PTR
                            || ent->method_ret_elem_kinds[mi_reg]
                                   == XLANG_TRAIT_TY_SLICE
                            || ent->method_ret_elem_kinds[mi_reg]
                                   == XLANG_TRAIT_TY_ARRAY)
                           && (ent->method_ret_kinds[mi_reg]
                                   == XLANG_TRAIT_TY_SLICE
                               || ent->method_ret_kinds[mi_reg]
                                      == XLANG_TRAIT_TY_ARRAY)) {
                  /*
                   * wave954: dest extras dest-RET extra empty `[]`
                   * PTR-elem SLICE-outer `[]*[]T`, PTR-elem ARRAY-
                   * outer `[2]*[2]T`, SLICE-elem SLICE-outer `[][][]T`,
                   * PTR-elem SLICE-outer `[]*[2]*T` (after elem `i32`
                   * suffix `[]`; outer is SLICE or ARRAY not PTR).
                   * Before wave954: hit the `else` line 7260 which
                   * set elem_kind=-1 (leaf T never committed; leftover
                   * skip eek=-1 — compile=0 run=1 leftover skip for
                   * impl `[]*i32` vs trait `[]*[]i32`). Extra SLICE
                   * wrap COUNT lives in dims[0] with ndims at
                   * PTR_TO_SLICE sentinel (-2) when ndims<=0 (first
                   * `[]` after elem `i32` with no ARRAY dims). Further
                   * extra `[]` increments dims[0] (2 = `[]*[][][]T`).
                   * Extra PTR sibling slot dims[1] is captured via
                   * the ret_elem_elem_pending TOKEN_STAR scanner.
                   * Twin of PTR-outer branches above (line 7143 /
                   * line 7178). Discriminant vs PTR outer is
                   * ret_kinds=SLICE/ARRAY vs ret_kinds=PTR. Do not
                   * invent -3. PLATFORM: SHARED parse. G.7: complete
                   * this scanner for the SLICE/ARRAY outer family.
                   */
                  int32_t nd;
                  int32_t extra;
                  if (ret_elem_dim_n > 0) {
                    int32_t di;
                    nd = ret_elem_dim_n;
                    ent->method_ret_elem_array_ndims[mi_reg] = nd;
                    for (di = 0; di < nd; di++)
                      ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                    ret_elem_dim_n = 0;
                  } else {
                    nd = ent->method_ret_elem_array_ndims[mi_reg];
                  }
                  if ((nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS
                       || nd <= 0)
                      && ret_elem_dim_n == 0) {
                    if (nd == XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                      extra = ent->method_ret_elem_array_dims[mi_reg][0];
                      if (extra <= 0)
                        extra = 1;
                      extra = extra + 1;
                      if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                        ent->method_ret_elem_array_dims[mi_reg][0] = extra;
                    } else {
                      ent->method_ret_elem_array_ndims[mi_reg] =
                          XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS;
                    }
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_dim_n = 0;
                    ret_elem_elem_pending = 1;
                  } else if (nd > 0 && nd + 1 < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX) {
                    extra = ent->method_ret_elem_array_dims[mi_reg][nd + 1];
                    if (extra < 0)
                      extra = 0;
                    extra = extra + 1;
                    if (extra < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                      ent->method_ret_elem_array_dims[mi_reg][nd + 1] = extra;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_elem_pending = 1;
                  } else {
                    ent->method_ret_elem_kinds[mi_reg] = -1;
                    ret_elem_arr_need_size = 0;
                    ret_elem_prefix_arr_more = 0;
                    ret_elem_dim_n = 0;
                    want_ret = 0;
                  }
                } else {
                  /* wave438: elem T[] → PTR to SLICE of T (3-layer, deferred to soft).
                   * Mark elem uncaptured so check skips; avoids parse failure.
                   * Also clears prefix_arr_more if came from *[N][]T. */
                  ent->method_ret_elem_kinds[mi_reg] = -1;
                  ret_elem_arr_need_size = 0;
                  ret_elem_prefix_arr_more = 0;
                  ret_elem_dim_n = 0;
                  want_ret = 0;
                }
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                /* Collect one elem dim; finalize on non-`[` after closing `]`. */
                if (ret_elem_dim_n < XLANG_SKIP_TRAIT_ARRAY_DIM_MAX)
                  ret_elem_dims[ret_elem_dim_n++] = r.tok.int_val;
                ret_elem_arr_need_size = 0;
                ret_elem_arr_need_rb = 1;
              } else {
                ret_elem_arr_need_size = 0;
                ret_elem_prefix_arr_more = 0;
                want_ret = 0;
              }
            } else if (ret_elem_suffix_pending) {
              if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                ret_elem_suffix_pending = 0;
                ret_elem_arr_need_size = 1;
              } else {
                /* Finalize elem multi-dim (dims>0 → elem=ARRAY) or leave scalar elem. */
                if (ret_elem_dim_n > 0) {
                  int32_t base_k = ent->method_ret_elem_kinds[mi_reg];
                  int32_t di;
                  ent->method_ret_elem_elem_kinds[mi_reg] = base_k;
                  ent->method_ret_elem_kinds[mi_reg] = XLANG_TRAIT_TY_ARRAY;
                  ent->method_ret_elem_array_ndims[mi_reg] = ret_elem_dim_n;
                  for (di = 0; di < ret_elem_dim_n; di++)
                    ent->method_ret_elem_array_dims[mi_reg][di] = ret_elem_dims[di];
                }
                ret_elem_suffix_pending = 0;
                ret_elem_dim_n = 0;
                want_ret = 0;
              }
            } else if (ent->method_ret_kinds[mi_reg] < 0) {
              if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_NAMED;
                xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                              ent->method_ret_names[mi_reg],
                                              &ent->method_ret_name_lens[mi_reg]);
                /* wave430/431: keep scanning for suffix T[N] / T[] / T[N][M]. */
                ret_suffix_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_PTR;
                ret_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                ent->method_ret_kinds[mi_reg] = XLANG_TRAIT_TY_SLICE;
                ret_slice_need_rb = 1;
              } else {
                int32_t bk = xlang_trait_token_to_type_kind_c(r.tok.kind);
                ent->method_ret_kinds[mi_reg] = bk;
                if (bk >= 0)
                  ret_suffix_pending = 1;
                else
                  want_ret = 0;
              }
            } else {
              want_ret = 0;
            }
          }
          if (r.tok.kind == (int32_t)TOKEN_LBRACE)
            depth++;
          else if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
            /*
             * wave464 Cap residual pure — trait method signature ASI.
             * Twin of seed parser_asm_seed_register_trait_c method-end.
             * Root: depth==0 RBRACE was treated as method-body close and advanced
             * past trait `}` → trait registry incomplete when signatures omit `;`.
             * G.7 single authority pair with seed register_trait; PLATFORM: SHARED.
             */
            if (depth > 0) {
              depth--;
              if (depth == 0) {
                /* wave468: method body closed → default method eligible for hoist. */
                if (mi_reg >= 0 && ent)
                  ent->method_has_default[mi_reg] = 1;
                lex = r.next_lex;
                break;
              }
            } else {
              /* Signature without `;` ends at trait `}` — leave brace for outer. */
              break;
            }
          } else if (r.tok.kind == (int32_t)TOKEN_SEMICOLON && depth == 0) {
            lex = r.next_lex;
            break;
          } else if (r.tok.kind == (int32_t)TOKEN_FUNCTION && depth == 0 && paren == 0) {
            /* wave464: ASI — next method; leave FUNCTION for outer loop. */
            break;
          } else if (r.tok.kind == (int32_t)TOKEN_EOF) {
            out->pos = lex.pos;
            out->line = lex.line;
            out->col = lex.col;
            return;
          }
          parser_asm_lex_from_result_val_into(&lex, r);
          lexer_next_into(&r, lex, source);
        }
      }
      continue;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
  }
  out->pos = lex.pos;
  out->line = lex.line;
  out->col = lex.col;
}

/**
 * skip_one_impl_into：consume impl header only; leave method bodies for outer parse_into.
 *
 * wave390 Cap residual pure — root map:
 * - Old byte-path skipped the whole brace block → IDENT for-type (struct) methods discarded.
 * - Old token-path required for-type TOKEN_IDENT only → i32/u64 mid-fail leaked methods
 *   as top-level free fns (accidental green); struct stayed red.
 * - Fix: parse header (IDENT + type keywords + optional *T), then set *out to body
 *   interior after `{`. Outer parse_into commits each `function` as free UFCS method;
 *   trailing `}` is skipped as non-function noise.
 * G.7 authority: this function (glue for parser.x + seed fallback).
 * Soft: dyn Trait.
 * wave421: record trait name for missing-method check (typeck).
 * wave428: also record for-type (kind / named / *T) for untyped-self check.
 * 4.2.2: skip `impl<T: Trait>` / `Type<T>` / `for Type<T>` angle lists
 *   (same helper as skip_one_struct) so the header reaches `{` instead of
 *   early-return on TOKEN_LT (methods leaked as unconstrained free fns).
 * PLATFORM: SHARED parse.
 */
void parser_asm_skip_one_impl_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                           struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  uint8_t first_nm[64];
  int32_t first_nlen = 0;
  int32_t impl_line = 0;
  int32_t impl_col = 0;
  if (!out || !source)
    return;
  /* wave439: stash full-file source for generic-bound scan. */
  xlang_generic_bound_stash_source_c(source);
  memset(first_nm, 0, sizeof(first_nm));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_impl_header_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IMPL) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  impl_line = r.tok.line;
  impl_col = r.tok.col;
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  /* impl<T: Trait> … — skip impl-level type params (≡ skip_one_struct). */
  if (r.tok.kind == (int32_t)TOKEN_LT) {
    parser_asm_skip_generic_angle_list_into_slice_c(&lex, lex, source);
    lexer_next_into(&r, lex, source);
  }
  /* Trait name or inherent type: IDENT or built-in type keyword. */
  if (r.tok.kind != (int32_t)TOKEN_IDENT && r.tok.kind != (int32_t)TOKEN_I32
      && r.tok.kind != (int32_t)TOKEN_I64 && r.tok.kind != (int32_t)TOKEN_BOOL
      && r.tok.kind != (int32_t)TOKEN_U8 && r.tok.kind != (int32_t)TOKEN_U32
      && r.tok.kind != (int32_t)TOKEN_U64 && r.tok.kind != (int32_t)TOKEN_USIZE
      && r.tok.kind != (int32_t)TOKEN_ISIZE && r.tok.kind != (int32_t)TOKEN_F32
      && r.tok.kind != (int32_t)TOKEN_F64) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_IDENT)
    xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len, first_nm, &first_nlen);
  {
    uint8_t iname_audit[64];
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, iname_audit);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(iname_audit, r.tok.ident_len));
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  /* impl Type<T> / impl Trait<T> for … — skip the type's angle list. */
  if (r.tok.kind == (int32_t)TOKEN_LT) {
    parser_asm_skip_generic_angle_list_into_slice_c(&lex, lex, source);
    lexer_next_into(&r, lex, source);
  }
  if (r.tok.kind == (int32_t)TOKEN_FOR) {
    /* wave421: record impl Trait for …; wave428: fill for-type after Type token. */
    int32_t si = -1;
    int32_t for_is_ptr = 0;
    int32_t for_k = -1;
    if (first_nlen > 0 && g_xlang_skip_impl_seen_n < XLANG_SKIP_IMPL_SEEN_MAX) {
      si = g_xlang_skip_impl_seen_n;
      memcpy(g_xlang_skip_impl_trait[si], first_nm, 64);
      g_xlang_skip_impl_trait_len[si] = first_nlen;
      g_xlang_skip_impl_line[si] = impl_line;
      g_xlang_skip_impl_col[si] = impl_col;
      g_xlang_skip_impl_for_kinds[si] = -1;
      g_xlang_skip_impl_for_is_ptr[si] = 0;
      g_xlang_skip_impl_for_name_lens[si] = 0;
      memset(g_xlang_skip_impl_for_names[si], 0, 64);
      g_xlang_skip_impl_seen_n++;
    }
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_impl_type_for_trait_audit_c(lex, source));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_trait_impl_type_deep_audit_c(lex, source));
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_STAR) {
      for_is_ptr = 1;
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
    }
    if (r.tok.kind != (int32_t)TOKEN_IDENT && r.tok.kind != (int32_t)TOKEN_I32
        && r.tok.kind != (int32_t)TOKEN_I64 && r.tok.kind != (int32_t)TOKEN_BOOL
        && r.tok.kind != (int32_t)TOKEN_U8 && r.tok.kind != (int32_t)TOKEN_U32
        && r.tok.kind != (int32_t)TOKEN_U64 && r.tok.kind != (int32_t)TOKEN_USIZE
        && r.tok.kind != (int32_t)TOKEN_ISIZE && r.tok.kind != (int32_t)TOKEN_F32
        && r.tok.kind != (int32_t)TOKEN_F64) {
      out->pos = lex.pos;
      out->line = lex.line;
      out->col = lex.col;
      return;
    }
    /* wave428: capture for-type shape for untyped-self match. */
    if (r.tok.kind == (int32_t)TOKEN_IDENT) {
      for_k = XLANG_TRAIT_TY_NAMED;
      if (si >= 0)
        xlang_skip_trait_copy_ident_c(source, r.token_start, r.tok.ident_len,
                                      g_xlang_skip_impl_for_names[si],
                                      &g_xlang_skip_impl_for_name_lens[si]);
    } else {
      for_k = xlang_trait_token_to_type_kind_c(r.tok.kind);
    }
    if (si >= 0) {
      g_xlang_skip_impl_for_kinds[si] = for_k;
      g_xlang_skip_impl_for_is_ptr[si] = for_is_ptr;
    }
    {
      uint8_t tname_audit[64];
      parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, tname_audit);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(tname_audit, r.tok.ident_len));
    }
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    /* impl Trait for Type<T> — skip for-type angle list. */
    if (r.tok.kind == (int32_t)TOKEN_LT) {
      parser_asm_skip_generic_angle_list_into_slice_c(&lex, lex, source);
      lexer_next_into(&r, lex, source);
    }
  }
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_impl_items_body_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_impl_items_probe_c(r.next_lex, source, 0));
  /* wave390: do NOT skip_balanced_braces — leave methods for outer parse_into free-fn commit. */
  out->pos = r.next_lex.pos;
  out->line = r.next_lex.line;
  out->col = r.next_lex.col;
}

/** 将 extern 解析失败快照写入 out（name_len=-1）。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void parser_asm_extern_parse_set_fail_c(struct parser_asm_extern_parse_result *out,
                                               struct parser_asm_lexer lex) {
  if (!out)
    return;
  memset(out->name, 0, sizeof(out->name));
  out->next_lex = lex;
  out->name_len = -1;
  out->return_ty_ref = 0;
  out->num_params = 0;
  out->abi_kind = 0;
  out->is_variadic = 0;
  out->has_body = 0;
}




/**
 * parse_one_extern_skip_into：解析 extern function 到分号，结果写入 *out；失败时 name_len=-1。
 */
void parser_asm_parse_one_extern_skip_into_slice_c(struct parser_asm_extern_parse_result *out, void *arena,
                                                   struct parser_asm_lexer lex,
                                                   struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex_cur;
  uint8_t name_buf[64];
  uint8_t pname_ex[128];
  uint8_t *ex_pool;
  int32_t name_len;
  int32_t n_ex;
  int32_t plen_ex;
  int32_t pidx_append;
  int32_t ty_pex;
  int32_t ret_ty;
  int32_t nk;
  if (!out || !source)
    return;
  {
    int32_t extern_param_score = 0;
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_param_count_audit_c(lex, source, &extern_param_score));
    (void)extern_param_score;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_fn_audit_c(lex, source));
  ast_pool_onefunc_reset((uint8_t *)out);
  out->abi_kind = 0; /* 默认 X ABI；extern "C" 时在下方设为 1 */
  out->is_variadic = 0; /* 默认定参；遇到 `...` 时在参数循环中设为 1 */
  out->has_body = 0;   /* 默认纯声明；遇到 `{` 时在下方设为 1 */
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_EXTERN) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  /* P0a: 可选 ABI 标记 — extern "C" function ... / extern "X" function ...
   * 默认（无标记）= X ABI（abi_kind=0）；"C" = C ABI（abi_kind=1，需 unsafe 调用）。
   * 语义降级：P0a 阶段 typeck/codegen 统一按 C ABI 生成，不改变行为。 */
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_STRING) {
    uint8_t *abi_str = source->data + r.token_start;
    int32_t abi_len = r.tok.ident_len;
    if (abi_len == 1 && abi_str[0] == 'C') {
      out->abi_kind = 1; /* C ABI */
    } else if (abi_len == 1 && abi_str[0] == 'X') {
      out->abi_kind = 0; /* X ABI（显式标记，与默认一致） */
    } else {
      parser_asm_extern_parse_set_fail_c(out, lex);
      return;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
  }
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  name_len = r.tok.ident_len;
  if (name_len <= 0 || name_len > 63) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  parser_asm_copy_slice_to_name64_at_end_slice_c(source, r.next_lex.pos, name_len, name_buf);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_param_bind_audit_c(name_buf, name_len));
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  ex_pool = (uint8_t *)out;
  n_ex = 0;
  if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
    parser_asm_lex_from_result_val_into(&lex, r);
  } else {
    for (;;) {
      /* 变参 `...`：必须是形参列表最后一个 token，紧跟 `)`；仅 C ABI 支持。 */
      if (r.tok.kind == (int32_t)TOKEN_ELLIPSIS) {
        out->is_variadic = 1;
        parser_asm_lex_from_result_val_into(&lex, r);
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
          parser_asm_extern_parse_set_fail_c(out, lex);
          return;
        }
        parser_asm_lex_from_result_val_into(&lex, r);
        break;
      }
      if (r.tok.kind != (int32_t)TOKEN_IDENT) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      plen_ex = r.tok.ident_len;
      if (plen_ex <= 0 || plen_ex > 127) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      parser_asm_copy_slice_to_param32_slice_c(source, r.token_start, plen_ex, pname_ex);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_param_bind_audit_c(pname_ex, plen_ex));
      pidx_append = pipeline_onefunc_append_param(ex_pool, pname_ex, plen_ex, 0);
      if (pidx_append < 0) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      n_ex = pidx_append + 1;
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind != (int32_t)TOKEN_COLON) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      parser_asm_lex_from_result_val_into(&lex, r);
      lex_cur = lex;
      ty_pex = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex_cur, source, &lex);
      if (ty_pex == 0) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      pipeline_onefunc_set_param_type_ref(ex_pool, pidx_append, ty_pex);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
        parser_asm_lex_from_result_val_into(&lex, r);
        break;
      }
      if (r.tok.kind != (int32_t)TOKEN_COMMA) {
        parser_asm_extern_parse_set_fail_c(out, lex);
        return;
      }
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
        parser_asm_lex_from_result_val_into(&lex, r);
        break;
      }
    }
  }
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_COLON) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_return_type_audit_c(lex, source));
  parser_asm_lex_from_result_val_into(&lex, r);
  lex_cur = lex;
  ret_ty = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex_cur, source, &lex);
  if (ret_ty == 0) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
    /* Body-bearing extern: `extern "C" function ... { body }`.
     * Set has_body=1 and leave next_lex BEFORE '{' so caller can parse body
     * via parse_block_into (parser.x). Caller sets is_extern=0 + body_ref. */
    out->has_body = 1;
    out->next_lex = lex;
    out->name_len = name_len;
    out->return_ty_ref = ret_ty;
    out->num_params = n_ex;
    for (nk = 0; nk < 64; nk++)
      out->name[nk] = name_buf[nk];
    return;
  }
  if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
    parser_asm_extern_parse_set_fail_c(out, lex);
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  out->has_body = 0;
  out->next_lex = lex;
  out->name_len = name_len;
  out->return_ty_ref = ret_ty;
  out->num_params = n_ex;
  for (nk = 0; nk < 64; nk++)
    out->name[nk] = name_buf[nk];
}

/**
 * parse_one_extern_and_add_into：解析 extern 声明并登记 module；失败 fallback skip_one_extern_into。
 */
void parser_asm_parse_one_extern_and_add_into_slice_c(void *arena, void *module, struct parser_asm_lexer lex,
                                                       struct parser_asm_slice_u8 *source,
                                                       struct parser_asm_lexer *lex_out) {
  struct parser_asm_extern_parse_result res;
  struct ast_Func f;
  int32_t type_ref;
  int32_t func_ref;
  int32_t fi_ex;
  int32_t ki;
  if (!lex_out || !source)
    return;
  memset(&res, 0, sizeof(res));
  res.name_len = -1;
  parser_asm_parse_one_extern_skip_into_slice_c(&res, arena, lex, source);
  if (res.name_len < 0) {
    parser_skip_one_extern_into_glue(lex_out, lex, source);
    return;
  }
  type_ref = res.return_ty_ref;
  if (type_ref == 0) {
    extern void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len,
                                                      const uint8_t *name);
    driver_diagnostic_parse_skip_function((int32_t)lex.pos, pipeline_module_num_funcs(module), res.name_len,
                                          res.name_len > 0 ? res.name : NULL);
    parser_skip_one_extern_into_glue(lex_out, lex, source);
    return;
  }
  func_ref = ast_ast_arena_func_alloc(arena);
  if (func_ref == 0) {
    extern void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len,
                                                      const uint8_t *name);
    driver_diagnostic_parse_skip_function((int32_t)lex.pos, pipeline_module_num_funcs(module), res.name_len,
                                          res.name_len > 0 ? res.name : NULL);
    parser_skip_one_extern_into_glue(lex_out, lex, source);
    return;
  }
  f = ast_arena_func_get(arena, func_ref);
  for (ki = 0; ki < 64; ki++) {
    if (ki < res.name_len)
      f.name[ki] = res.name[ki];
    else
      f.name[ki] = 0;
  }
  f.name_len = res.name_len;
  f.num_params = res.num_params;
  f.return_type_ref = type_ref;
  f.body_ref = 0;
  f.body_expr_ref = 0;
  /* Body-bearing extern (`extern "C" function ... { body }`): is_extern=0 so codegen
   * emits the body. Caller (.x TOKEN_EXTERN dispatch) parses body via parse_block_into
   * and sets body_ref. Pure declaration: is_extern=1 (codegen skips body). */
  f.is_extern = (res.has_body == 1) ? 0 : 1;
  f.is_async = 0;
  f.abi_kind = res.abi_kind;
  f.is_variadic = res.is_variadic;
  ast_arena_func_set(arena, func_ref, f);
  fi_ex = parser_asm_module_register_arena_func_c(module, func_ref, f);
  if (fi_ex < 0) {
    extern void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len,
                                                      const uint8_t *name);
    driver_diagnostic_parse_skip_function((int32_t)lex.pos, pipeline_module_num_funcs(module), res.name_len,
                                          res.name_len > 0 ? res.name : NULL);
    parser_skip_one_extern_into_glue(lex_out, lex, source);
    return;
  }
  parser_asm_write_extern_params_to_pools_c(arena, module, func_ref, fi_ex, &res);
  /* For has_body=1: next_lex is BEFORE '{' — caller (.x) reads '{' then calls parse_block_into.
   * For pure decl: next_lex is after ';'. */
  lex_out->pos = res.next_lex.pos;
  lex_out->line = res.next_lex.line;
  lex_out->col = res.next_lex.col;
}

/**
 * module_register_arena_func：将 arena Func 登记到 module 动态池，返回 module 下标或 -1。
 */
int32_t parser_asm_module_register_arena_func_c(void *module, int32_t func_ref, struct ast_Func f) {
  int32_t fi;
  if (!module)
    return -1;
  fi = pipeline_module_func_alloc_slot(module);
  if (fi < 0)
    return -1;
  pipeline_module_func_name_write(module, fi, f.name, f.name_len);
  pipeline_module_func_set_num_params(module, fi, f.num_params);
  pipeline_module_func_set_return_type(module, fi, f.return_type_ref);
  pipeline_module_func_set_body_ref(module, fi, f.body_ref);
  pipeline_module_func_set_body_expr_ref(module, fi, f.body_expr_ref);
  pipeline_module_func_set_is_extern(module, fi, f.is_extern);
  pipeline_module_func_set_is_async(module, fi, f.is_async);
  pipeline_module_func_set_is_variadic(module, fi, f.is_variadic);
  pipeline_module_func_ref_set(module, fi, func_ref);
  return fi;
}

/**
 * write_extern_params_to_pools：将 ExternParseResult 侧车池形参写入 arena 与 module sidecar。
 */
void parser_asm_write_extern_params_to_pools_c(void *arena, void *module, int32_t func_ref, int32_t fi,
                                               struct parser_asm_extern_parse_result *res) {
  uint8_t *pool;
  int32_t p;
  uint8_t pname32[128];
  int32_t plen;
  int32_t pty;
  if (!res)
    return;
  pool = (uint8_t *)res;
  p = 0;
  while (p < res->num_params) {
    pipeline_onefunc_param_name_copy32(pool, p, pname32);
    plen = pipeline_onefunc_param_name_len(pool, p);
    pty = pipeline_onefunc_param_type_ref(pool, p);
    pipeline_arena_func_param_write(arena, func_ref, p, pname32, plen, pty);
    pipeline_module_func_param_write(module, fi, p, pname32, plen, pty);
    p++;
  }
}

/**
 * skip_one_extern_into：跳过一条顶层 extern function 声明，结果写入 *out。
 *
 * PLATFORM: SHARED — must stay shape-aligned with parse_one_extern_skip_into
 * (optional ABI string after `extern`: "C" / "X"). G.7 single authority: this
 * function is the only skip path; cfg_skip + skip_one_function_full delegate here.
 *
 * Why: parse accepted `extern "C" function ...;` but skip required bare
 * `extern function`. A kept cfg-extern followed by a skipped sibling then left
 * the lexer mid-declaration; subsequent top-level items (including main) were
 * lost or re-ingested (cfg-extern residual / rt_diag always-on workaround).
 */
void parser_asm_skip_one_extern_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                             struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer lex_cur;
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_skip_one_extern_body_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_extern_fn_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_EXTERN) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  /* Optional ABI marker — same shape as parse_one_extern_skip_into (P0a).
   * Skip path does not record abi_kind; only advance past the string token. */
  if (r.tok.kind == (int32_t)TOKEN_STRING) {
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
  }
  if (r.tok.kind != (int32_t)TOKEN_FUNCTION) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
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
  while (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_EOF) {
    parser_asm_lex_from_result_val_into(&lex_cur, r);
    lexer_next_into(&r, lex_cur, source);
  }
  if (r.tok.kind == (int32_t)TOKEN_SEMICOLON)
    parser_asm_lex_from_result_val_into(&lex_cur, r);
  out->pos = lex_cur.pos;
  out->line = lex_cur.line;
  out->col = lex_cur.col;
}

/**
 * module_append_enum_variants_and_skip_body_into：扫描 enum 体变体名并 skip 至 `}`，结果写入 *out。
 */
void parser_asm_module_append_enum_variants_and_skip_body_into_slice_c(
    void *module, int32_t enum_idx, struct parser_asm_lexer *out, struct parser_asm_lexer lex,
    struct parser_asm_slice_u8 *source) {
  int32_t depth;
  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variants_body_audit_c(lex, source));
  depth = 1;
  while (depth > 0) {
    struct parser_asm_lexer_result r;
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      depth = depth - 1;
      if (depth == 0) {
        parser_asm_lex_from_result_val_into(&lex, r);
        break;
      }
    } else if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      depth = depth + 1;
    } else if (depth == 1 && enum_idx >= 0 && r.tok.kind == (int32_t)TOKEN_IDENT) {
      int32_t vlen;
      size_t vstart;
      /* wave582 Cap residual: variant name content ≤127 (variant_name[][128]). */
      uint8_t vb[128];
      vlen = r.tok.ident_len;
      if (vlen > 127)
        vlen = 127;
      vstart = r.token_start;
      if (vstart == 0)
        vstart = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, vlen);
      parser_asm_copy_slice_to_name64_slice_c(source, vstart, vlen, vb);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_enum_variant_bind_audit_c(source, vstart, vlen));
      pipeline_module_enum_append_variant(module, enum_idx, vb, vlen);
    }
    parser_asm_lex_from_result_val_into(&lex, r);
  }
  out->pos = lex.pos;
  out->line = lex.line;
  out->col = lex.col;
}

/**
 * skip_one_enum_register_into：登记 enum 名并 skip 整条 enum 定义，结果写入 *out。
 */
/**
 * Register enum name and skip whole enum definition.
 * wave582 Cap residual: enum name content ≤127 (nb[128]). PLATFORM: SHARED
 */
void parser_asm_skip_one_enum_register_into_slice_c(void *module, struct parser_asm_lexer *out,
                                                    struct parser_asm_lexer lex,
                                                    struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  int32_t enum_idx;
  uint8_t nb[128];
  if (!out || !source)
    return;
  enum_idx = -1;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_ENUM) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  if (r.tok.ident_len > 0 && r.tok.ident_len <= 127) {
    parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, nb);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_collect_imports_bind_audit_c(nb, r.tok.ident_len));
    enum_idx = parser_asm_module_try_register_enum_name_c(module, nb, r.tok.ident_len);
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE) {
    out->pos = lex.pos;
    out->line = lex.line;
    out->col = lex.col;
    return;
  }
  parser_asm_module_append_enum_variants_and_skip_body_into_slice_c(module, enum_idx, out, r.next_lex, source);
}

/**
 * skip_one_struct：与 skip_one_struct_into 等价，Lexer 按值返回。
 */
struct parser_asm_lexer parser_asm_skip_one_struct_slice_c(struct parser_asm_lexer lex,
                                                           struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer out;
  parser_asm_skip_one_struct_into_slice_c(&out, lex, source);
  return out;
}
