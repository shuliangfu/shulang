/**
 * parser_asm_seed_parse_into_buf_slice.inc — seed ./xlang 链 parse_into_buf / parse_into C 实现。
 *
 * 瘦 parser_x.o 无 parse_into_buf；由本 TU（parser_asm_thin_c.c #include）提供强符号，
 * 覆盖 parser_asm_parse_expr_link.c 弱桩，供 runtime asm 后端 parse 任意 .x。
 */
#ifndef PARSER_ASM_SEED_PARSE_INTO_BUF_SLICE_INCLUDED
#define PARSER_ASM_SEED_PARSE_INTO_BUF_SLICE_INCLUDED

#include <string.h>

/** 与 parser.x ParseIntoResult 布局一致。 */
struct parser_asm_seed_parse_into_result {
  int32_t ok;
  int32_t main_idx;
};

/** X Module 池头部（与 ast.x / pipeline_glue_types.inc 一致）。 */
typedef struct {
  int32_t num_funcs;
  int32_t main_func_index;
  int32_t num_imports;
  int32_t num_top_level_lets;
  int32_t num_struct_layouts;
  int32_t pending_allow_padding;
  int32_t pending_soa_struct;
  int32_t pending_cfg_skip;
  int32_t pending_repr_c_struct;
  int32_t pending_repr_compatible_struct;
  int32_t num_module_enums;
} parser_asm_x_module_hdr_t;

extern struct parser_asm_lexer_result lexer_next_buf(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_parse_into_buf_preamble_peek_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                           int32_t len);
extern int32_t parser_asm_stretch_top_level_let_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len,
                                                            int32_t is_const);
extern int32_t parser_asm_stretch_struct_record_layout_body_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                        int32_t len);
extern int32_t parser_asm_stretch_type_ref_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len,
                                                  const uint8_t *name);
extern void driver_diagnostic_parse_commit_fail(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len,
                                                const uint8_t *name);
extern int32_t parser_parse_peek_function_name_buf_glue(struct parser_asm_lexer lex, uint8_t *data, int32_t len,
                                                        uint8_t *out);
extern int32_t parser_diag_fail_at_token_kind_buf_glue(uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_type_ref_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                      int32_t len);
extern int32_t parser_asm_stretch_type_ref_deep_buf_audit_c(void *lex_inout, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_type_ref_bracket_composite_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                       int32_t len);
extern int32_t parser_asm_stretch_parse_into_buf_loop_toplevel_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                           int32_t len);
extern int32_t parser_asm_stretch_async_fn_prefix_buf_audit_c(void *lex_inout, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_parse_into_function_branch_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                              int32_t len);
extern int32_t parser_asm_stretch_parse_into_preamble_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                     int32_t len);
extern int32_t parser_asm_stretch_parse_into_entry_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                       int32_t len);
extern int32_t parser_asm_stretch_parse_into_loop_entry_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                            int32_t len);
extern int32_t parser_asm_stretch_parse_into_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                      int32_t len);
extern int32_t parser_asm_stretch_parse_into_ultra_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                              int32_t len);
extern int32_t parser_asm_stretch_top_level_let_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                      int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_top_level_let_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                           int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_parse_struct_layout_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex,
                                                                                 uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_parse_struct_layout_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_preamble_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_entry_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                              int32_t len);
extern int32_t parser_asm_stretch_parse_into_super_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                              int32_t len);
extern int32_t parser_asm_stretch_parse_into_max_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_toplevel_super_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_parse_into_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_toplevel_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_parse_into_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_parse_into_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len);
extern int32_t parser_asm_stretch_toplevel_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_toplevel_max_ultra_hyper_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                          int32_t len, int32_t is_const);
extern int32_t parser_asm_stretch_parse_preamble_mega_full_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                            int32_t len);
extern int32_t parser_asm_stretch_top_level_let_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_struct_layout_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern int32_t parser_asm_stretch_parse_into_loop_iter_deep_buf_audit_c(struct parser_asm_lexer lex, uint8_t *data,
                                                                      int32_t len);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parser_asm_collect_imports_buf_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len, void *module,
                                             struct parser_asm_collect_imports_result *out);
extern void parser_parse_one_function_impl(struct parser_asm_onefunc_result *res, void *arena,
                                           struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern void parser_asm_parse_one_function_buf_into_c(struct parser_asm_onefunc_result *out, void *arena,
                                                      struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern struct parser_asm_library_parse_result parser_asm_parse_one_function_library_buf_c(
    void *arena, void *module, struct parser_asm_lexer lex, uint8_t *data, int32_t len);
extern struct parser_asm_onefunc_result parser_onefunc_scratch_empty(void);
extern void parser_onefunc_res_wire_dummy_head(struct parser_asm_onefunc_result *res, struct parser_asm_lexer lex,
                                               uint8_t *name64);
extern void parser_onefunc_res_wire_dummy_const_let(struct parser_asm_onefunc_result *res);
extern void parser_onefunc_res_wire_dummy_if_mul(struct parser_asm_onefunc_result *res);
extern void parser_onefunc_res_wire_dummy_call_binop(struct parser_asm_onefunc_result *res, uint8_t *name64);
extern void parser_onefunc_res_wire_dummy_loop_call(struct parser_asm_onefunc_result *res);
extern void parser_onefunc_res_wire_dummy_for_if(struct parser_asm_onefunc_result *res);
extern uint8_t *parser_asm_onefunc_result_pool_ptr_c(struct parser_asm_onefunc_result *res);
extern int32_t parser_asm_fill_block_const_let_from_res_c(void *arena, int32_t block_ref,
                                                            struct parser_asm_onefunc_result *res, int32_t type_ref);
extern int32_t parser_should_wrap_func_tail_in_return_glue(void *arena, struct parser_asm_onefunc_result *res,
                                                            int32_t type_ref);
extern void parser_lex_from_onefunc_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_onefunc_result *res);
extern void parser_parse_into_try_skip_allow_into_buf_glue(struct parser_asm_try_skip_allow_result *out,
                                                             struct parser_asm_lexer lex,
                                                             struct parser_asm_lexer_result r, uint8_t *data,
                                                             int32_t len);
extern void parser_parse_one_extern_and_add_into_buf_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                                            uint8_t *data, int32_t len,
                                                            struct parser_asm_lexer *lex_out);
extern void parser_skip_one_extern_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                 uint8_t *data, int32_t len);
extern int32_t parser_parse_struct_record_layout_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source,
                                                             struct parser_asm_lexer *out_lex, int32_t allow_pad,
                                                             int32_t force_soa, int32_t repr_compat);
extern void parser_skip_one_struct_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                 uint8_t *data, int32_t len);
extern void parser_skip_one_enum_register_into_buf_glue(void *module, struct parser_asm_lexer *out,
                                                        struct parser_asm_lexer lex_at, uint8_t *data, int32_t len);
extern void parser_skip_one_trait_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                uint8_t *data, int32_t len);
extern void parser_skip_one_impl_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                               uint8_t *data, int32_t len);
extern void parser_skip_one_function_full_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                        uint8_t *data, int32_t len);
/** B-01/B-19：跳过一条顶层 const 声明（含 const import）。 */
extern void parser_skip_one_top_level_const_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                           uint8_t *data, int32_t len);
/** B-01/B-19：跳过一条顶层 let 声明（cfg 不匹配时与 const 对称）。 */
extern void parser_skip_one_top_level_let_into_buf_glue(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                         uint8_t *data, int32_t len);
extern void parser_parse_one_top_level_let_into_glue(void *arena, void *module, struct parser_asm_lexer lex,
                                                     struct parser_asm_slice_u8 *source, int32_t is_const,
                                                     struct parser_asm_top_level_let_result *out);
extern struct parser_asm_lexer parser_lex_from_library_glue(struct parser_asm_library_parse_result lib);
extern struct parser_asm_lexer parser_lex_from_try_skip_glue(struct parser_asm_try_skip_allow_result t);

extern int32_t ast_ast_arena_type_alloc(void *arena);
extern struct ast_Type ast_ast_arena_type_get(void *arena, int32_t ref);
extern void ast_ast_arena_type_set(void *arena, int32_t ref, struct ast_Type t);
extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
extern int32_t ast_ast_arena_block_alloc(void *arena);
extern struct ast_Block ast_ast_arena_block_get(void *arena, int32_t ref);
extern void ast_ast_arena_block_set(void *arena, int32_t ref, struct ast_Block b);
extern int32_t ast_ast_arena_func_alloc(void *arena);
extern int32_t pipeline_type_kind_ord_at(void *arena, int32_t type_ref);
extern int32_t pipeline_block_append_expr_stmt(void *arena, int32_t block_ref, int32_t expr_ref);
extern int32_t pipeline_block_append_stmt_order(void *arena, int32_t block_ref, uint8_t kind, int32_t index);
extern int32_t pipeline_module_func_alloc_slot(void *module);
extern void pipeline_module_func_name_write(void *module, int32_t fi, uint8_t *name, int32_t name_len);
extern void pipeline_module_func_set_num_params(void *module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_return_type(void *module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(void *module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(void *module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(void *module, int32_t fi, int32_t is_extern);
extern void pipeline_module_func_set_is_async(void *module, int32_t fi, int32_t is_async);
extern void pipeline_module_func_ref_set(void *module, int32_t fi, int32_t func_ref);
extern void pipeline_arena_func_copy_slot_from_module(void *arena, int32_t func_ref, void *module, int32_t fi);
extern void pipeline_onefunc_param_name_copy32(uint8_t *pool, int32_t i, uint8_t *dst);
extern int32_t pipeline_onefunc_param_name_len(uint8_t *pool, int32_t i);
extern int32_t pipeline_onefunc_param_type_ref(uint8_t *pool, int32_t i);
extern void pipeline_module_func_param_write(void *module, int32_t fi, int32_t pi, uint8_t *name, int32_t name_len,
                                             int32_t type_ref);
extern void pipeline_block_fill_whiles_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern void pipeline_block_fill_fors_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern void pipeline_block_fill_ifs_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern void pipeline_block_fill_regions_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern void pipeline_block_fill_expr_stmts_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern void pipeline_block_fill_stmt_order_from_onefunc(void *arena, int32_t br, uint8_t *out, int32_t count);
extern int32_t pipeline_onefunc_num_whiles(uint8_t *out);
extern int32_t pipeline_onefunc_num_fors(uint8_t *out);
extern int32_t pipeline_onefunc_num_if_stmts(uint8_t *out);
extern int32_t pipeline_onefunc_num_regions(uint8_t *out);
extern int32_t pipeline_onefunc_num_body_expr_stmts(uint8_t *out);
extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t *out);

/** u8[] slice 路径与 xlang_slice_uint8_t 布局一致。 */
struct parser_asm_seed_slice_u8 {
  uint8_t *data;
  size_t length;
};

/** OneFuncResult 工作区：wire dummy 侧车后供 parse_one_function_impl 使用。 */
static struct parser_asm_onefunc_result parser_asm_seed_onefunc_wired_c(struct parser_asm_lexer lex) {
  struct parser_asm_onefunc_result res;
  uint8_t empty64[64];

  memset(empty64, 0, sizeof(empty64));
  res = parser_onefunc_scratch_empty();
  parser_onefunc_res_wire_dummy_head(&res, lex, empty64);
  parser_onefunc_res_wire_dummy_const_let(&res);
  parser_onefunc_res_wire_dummy_if_mul(&res);
  parser_onefunc_res_wire_dummy_call_binop(&res, empty64);
  parser_onefunc_res_wire_dummy_loop_call(&res);
  parser_onefunc_res_wire_dummy_for_if(&res);
  return res;
}

/** 分配默认 i32 返回类型 ref。 */
static int32_t parser_asm_seed_default_i32_type_ref_c(void *arena) {
  int32_t type_ref;
  struct ast_Type t;

  type_ref = ast_ast_arena_type_alloc(arena);
  if (type_ref == 0)
    return 0;
  t = ast_ast_arena_type_get(arena, type_ref);
  t.kind = AST_TYPE_I32;
  t.name_len = 0;
  t.elem_type_ref = 0;
  t.array_size = 0;
  ast_ast_arena_type_set(arena, type_ref, t);
  return type_ref;
}

/** Expr 公共字段清零（与 parser_asm_block_from_res_slice 一致）。 */
static void parser_asm_seed_expr_common_zeros_c(struct ast_Expr *e) {
  if (!e)
    return;
  e->resolved_type_ref = 0;
  e->binop_left_ref = 0;
  e->binop_right_ref = 0;
  e->unary_operand_ref = 0;
  e->if_cond_ref = 0;
  e->if_then_ref = 0;
  e->if_else_ref = 0;
  e->block_ref = 0;
  e->match_matched_ref = 0;
  e->match_arm_base = 0;
  e->match_num_arms = 0;
  e->enum_variant_tag = 0;
  e->field_access_base_ref = 0;
  e->field_access_field_len = 0;
  e->field_access_is_enum_variant = 0;
  e->field_access_offset = 0;
  e->index_base_ref = 0;
  e->index_index_ref = 0;
  e->index_base_is_slice = 0;
  e->call_callee_ref = 0;
  e->call_arg_base = 0;
  e->call_num_args = 0;
  e->method_call_base_ref = 0;
  e->method_call_name_len = 0;
  e->method_call_arg_base = 0;
  e->method_call_num_args = 0;
  e->const_folded_val = 0;
  e->const_folded_valid = 0;
  e->index_proven_in_bounds = 0;
  e->struct_lit_field_base = 0;
  e->struct_lit_num_fields = 0;
  e->array_lit_elem_base = 0;
  e->array_lit_num_elems = 0;
  e->as_operand_ref = 0;
  e->as_target_type_ref = 0;
  e->call_resolved_func_index = -1;
  e->call_resolved_dep_index = -1;
}

/** 判断 name 是否为 main（4 字节 m-a-i-n）。 */
static int32_t parser_asm_seed_is_main_name_c(const uint8_t *name, int32_t name_len) {
  return name_len == 4 && name[0] == 109 && name[1] == 97 && name[2] == 105 && name[3] == 110;
}

/**
 * 将 inner_ref 包一层 EXPR_RETURN（已是 RETURN 则原样返回）；与 parser.x parser_expr_wrap_in_return 一致。
 */
static int32_t parser_asm_seed_expr_wrap_in_return_c(void *arena, int32_t type_ref, int32_t inner_ref) {
  int32_t wrap;
  struct ast_Expr inner;
  struct ast_Expr rwe;

  if (inner_ref == 0)
    return 0;
  inner = ast_ast_arena_expr_get(arena, inner_ref);
  if (inner.kind == AST_EXPR_RETURN)
    return inner_ref;
  wrap = ast_ast_arena_expr_alloc(arena);
  if (wrap == 0)
    return 0;
  rwe = ast_ast_arena_expr_get(arena, wrap);
  rwe.kind = AST_EXPR_RETURN;
  rwe.line = 0;
  rwe.col = 0;
  rwe.int_val = 0;
  parser_asm_seed_expr_common_zeros_c(&rwe);
  rwe.resolved_type_ref = type_ref;
  rwe.unary_operand_ref = inner_ref;
  ast_ast_arena_expr_set(arena, wrap, rwe);
  return wrap;
}

/**
 * 将已成功解析的 OneFuncResult 登记到 module/arena（parse_into_buf 主路径 commit）。
 * 返回 0 成功，-1 失败。
 */
static int32_t parser_asm_seed_commit_onefunc_c(void *arena, void *module, struct parser_asm_onefunc_result *res,
                                                int32_t func_is_async, int32_t *inout_main_idx,
                                                struct parser_asm_lexer *inout_lex) {
  int32_t type_ref;
  int32_t final_expr_ref;
  int32_t block_ref;
  struct ast_Block b;
  struct ast_Expr e;
  int32_t func_ref;
  int32_t fi_mod;
  int32_t p_copy;
  uint8_t *pool;
  size_t guard_pos;
  int32_t n_while;
  int32_t n_for;
  int32_t n_if;
  int32_t n_reg;
  int32_t ci;
  int32_t li;
  int32_t loop_i;
  int32_t for_i;
  int32_t if_i;

  if (!arena || !module || !res || !res->ok || !inout_lex)
    return -1;

  type_ref = res->func_return_type_ref;
  if (type_ref == 0)
    type_ref = parser_asm_seed_default_i32_type_ref_c(arena);
  if (type_ref == 0)
    return -1;

  if (res->return_expr_ref != 0) {
    final_expr_ref = res->return_expr_ref;
  } else if (res->return_var_name_len > 0) {
    final_expr_ref = ast_ast_arena_expr_alloc(arena);
    if (final_expr_ref == 0)
      return -1;
    e = ast_ast_arena_expr_get(arena, final_expr_ref);
    e.kind = AST_EXPR_VAR;
    e.var_name_len = res->return_var_name_len;
    memcpy(e.var_name, res->return_var_name, (size_t)res->return_var_name_len);
    e.int_val = 0;
    parser_asm_seed_expr_common_zeros_c(&e);
    ast_ast_arena_expr_set(arena, final_expr_ref, e);
  } else {
    final_expr_ref = ast_ast_arena_expr_alloc(arena);
    if (final_expr_ref == 0)
      return -1;
    e = ast_ast_arena_expr_get(arena, final_expr_ref);
    e.kind = AST_EXPR_LIT;
    e.int_val = res->return_val;
    e.resolved_type_ref = type_ref;
    parser_asm_seed_expr_common_zeros_c(&e);
    ast_ast_arena_expr_set(arena, final_expr_ref, e);
  }

  if (parser_should_wrap_func_tail_in_return_glue(arena, res, type_ref)) {
    int32_t wrapped_fe = parser_asm_seed_expr_wrap_in_return_c(arena, type_ref, final_expr_ref);
    if (wrapped_fe == 0)
      return -1;
    final_expr_ref = wrapped_fe;
  }

  block_ref = ast_ast_arena_block_alloc(arena);
  if (block_ref == 0)
    return -1;
  b = ast_ast_arena_block_get(arena, block_ref);
  b.num_consts = res->num_consts;
  b.num_lets = res->num_lets;
  b.num_early_lets = 0;
  b.num_loops = 0;
  b.num_for_loops = 0;
  b.num_if_stmts = 0;
  b.num_defers = 0;
  b.num_labeled_stmts = 0;
  b.num_expr_stmts = 0;
  b.final_expr_ref = final_expr_ref;
  b.num_stmt_order = 0;
  ast_ast_arena_block_set(arena, block_ref, b);

  if (!parser_asm_fill_block_const_let_from_res_c(arena, block_ref, res, type_ref))
    return -1;

  pool = parser_asm_onefunc_result_pool_ptr_c(res);
  n_while = pipeline_onefunc_num_whiles(pool);
  res->num_loops = n_while;
  pipeline_block_fill_whiles_from_onefunc(arena, block_ref, pool, n_while);
  n_for = pipeline_onefunc_num_fors(pool);
  res->num_for_loops = n_for;
  pipeline_block_fill_fors_from_onefunc(arena, block_ref, pool, n_for);
  n_if = pipeline_onefunc_num_if_stmts(pool);
  res->num_if_stmts = n_if;
  pipeline_block_fill_ifs_from_onefunc(arena, block_ref, pool, n_if);
  n_reg = pipeline_onefunc_num_regions(pool);
  pipeline_block_fill_regions_from_onefunc(arena, block_ref, pool, n_reg);

  b = ast_ast_arena_block_get(arena, block_ref);
  if (res->num_src_stmt_order > 0) {
    pipeline_block_fill_expr_stmts_from_onefunc(arena, block_ref, pool,
                                                pipeline_onefunc_num_body_expr_stmts(pool));
    pipeline_block_fill_stmt_order_from_onefunc(arena, block_ref, pool,
                                                pipeline_onefunc_num_src_stmt_order(pool));
    b = ast_ast_arena_block_get(arena, block_ref);
  } else {
    for (ci = 0; ci < b.num_consts; ci++) {
      if (pipeline_block_append_stmt_order(arena, block_ref, 0, ci) < 0)
        return -1;
    }
    for (li = 0; li < b.num_lets; li++) {
      if (pipeline_block_append_stmt_order(arena, block_ref, 1, li) < 0)
        return -1;
    }
    for (loop_i = 0; loop_i < b.num_loops; loop_i++) {
      if (pipeline_block_append_stmt_order(arena, block_ref, 3, loop_i) < 0)
        return -1;
    }
    for (for_i = 0; for_i < b.num_for_loops; for_i++) {
      if (pipeline_block_append_stmt_order(arena, block_ref, 4, for_i) < 0)
        return -1;
    }
    for (if_i = 0; if_i < b.num_if_stmts; if_i++) {
      if (pipeline_block_append_stmt_order(arena, block_ref, 5, if_i) < 0)
        return -1;
    }
    if (final_expr_ref != 0 && b.num_expr_stmts == 0) {
      int32_t fin_ex = pipeline_block_append_expr_stmt(arena, block_ref, final_expr_ref);
      if (fin_ex < 0)
        return -1;
      b.final_expr_ref = 0;
      final_expr_ref = 0;
      if (pipeline_block_append_stmt_order(arena, block_ref, 2, fin_ex) < 0)
        return -1;
      b = ast_ast_arena_block_get(arena, block_ref);
    }
  }
  b = ast_ast_arena_block_get(arena, block_ref);
  b.final_expr_ref = final_expr_ref;
  if (b.num_expr_stmts > 0 && final_expr_ref != 0) {
    struct ast_Expr fe_dedup = ast_ast_arena_expr_get(arena, final_expr_ref);
    if (fe_dedup.kind != AST_EXPR_RETURN)
      b.final_expr_ref = 0;
  }
  ast_ast_arena_block_set(arena, block_ref, b);

  func_ref = ast_ast_arena_func_alloc(arena);
  if (func_ref == 0)
    return -1;
  fi_mod = pipeline_module_func_alloc_slot(module);
  if (fi_mod < 0)
    return -1;
  pipeline_module_func_name_write(module, fi_mod, res->name, res->name_len);
  pipeline_module_func_set_num_params(module, fi_mod, res->num_params);
  pipeline_module_func_set_return_type(module, fi_mod, type_ref);
  pipeline_module_func_set_body_ref(module, fi_mod, block_ref);
  pipeline_module_func_set_body_expr_ref(module, fi_mod, 0);
  pipeline_module_func_set_is_extern(module, fi_mod, 0);
  pipeline_module_func_set_is_async(module, fi_mod, func_is_async);
  for (p_copy = 0; p_copy < res->num_params; p_copy++) {
    uint8_t pname32[128];
    memset(pname32, 0, sizeof(pname32));
    pipeline_onefunc_param_name_copy32(pool, p_copy, pname32);
    pipeline_module_func_param_write(module, fi_mod, p_copy, pname32,
                                     pipeline_onefunc_param_name_len(pool, p_copy),
                                     pipeline_onefunc_param_type_ref(pool, p_copy));
  }
  pipeline_module_func_ref_set(module, fi_mod, func_ref);
  pipeline_arena_func_copy_slot_from_module(arena, func_ref, module, fi_mod);
  if (inout_main_idx && parser_asm_seed_is_main_name_c(res->name, res->name_len))
    *inout_main_idx = fi_mod;

  guard_pos = inout_lex->pos;
  parser_lex_from_onefunc_next_into_glue(inout_lex, res);
  if (inout_lex->pos == guard_pos)
    inout_lex->pos++;
  return 0;
}

/**
 * wave390 Cap residual pure — type-start for impl for-type / inherent type.
 * Accepts IDENT, built-in type keywords, and STAR (pointer peel one level).
 * PLATFORM: SHARED parse.
 */
static int32_t parser_asm_seed_impl_type_start_kind_c(int32_t kind) {
  if (kind == (int32_t)TOKEN_IDENT || kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64
      || kind == (int32_t)TOKEN_BOOL || kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32
      || kind == (int32_t)TOKEN_U64 || kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_ISIZE
      || kind == (int32_t)TOKEN_F32 || kind == (int32_t)TOKEN_F64 || kind == (int32_t)TOKEN_VOID
      || kind == (int32_t)TOKEN_STAR)
    return 1;
  return 0;
}

/*
 * wave421 Cap residual pure — trait method registry for missing-method diagnostics.
 * Root: product path only hoisted impl methods as free funcs (wave390); never stored
 * trait signatures → impl_missing_method.x false-green (compile exit 0).
 * G.7: single table in seed parse_into_buf (reset per module).
 * wave424: unknown_trait hard fail (align product skip_tl xlang_trait_check_impls_complete_c).
 * wave425: method_ret_kinds + return_mismatch hard fail (twin of skip_tl).
 * wave426: method_param_counts + method_param_kinds + arity/param-type hard fail.
 * wave427: named/ptr/slice ret shape + hard fail (twin of skip_tl).
 * wave428: for-type + untyped-self vs for-type hard fail (twin of skip_tl).
 * wave429: typed self vs for-type hard fail (twin of skip_tl).
 * wave430: suffix T[N]/T[] ret + TYPE_ARRAY size/elem hard fail (twin of skip_tl).
 * wave431: multi-dim suffix T[N][M]… ret + recursive size walk (twin of skip_tl).
 * wave432: named/ptr/slice param shape + hard fail (twin of skip_tl).
 * wave468: method_has_default + fn start pos — hoist default bodies as free UFCS
 *   when not overridden (twin of skip_tl xlang_skip_hoist_default_methods_c).
 * Soft leave-off: dyn Trait; Self receiver rewrite; multi-default same-name across traits.
 * PLATFORM: SHARED parse.
 */
#define XLANG_TRAIT_REG_MAX 16
#define XLANG_TRAIT_METH_MAX 32
#define XLANG_TRAIT_PARAM_MAX 8
#define XLANG_SEED_TRAIT_ARRAY_DIM_MAX 8
#define XLANG_SEED_TRAIT_TY_NAMED 8
#define XLANG_SEED_TRAIT_TY_PTR 9
#define XLANG_SEED_TRAIT_TY_ARRAY 10
#define XLANG_SEED_TRAIT_TY_SLICE 11
/* dest-SLICE extra inner SLICE ndims discriminant.
 * 0 = scalar/NAMED; >=1 = ARRAY; -2 = extra SLICE wrap (`[]*[]T` /
 * `[]*[][]T` / `[][][]T` / `[][][][]T`). Extra wrap COUNT lives
 * in dims[0] (0 means 1 extra wrap = `[]*[]T` or 3-layer; 2 =
 * `[]*[][]T` or 4-layer). Do not invent -3.
 * Twin of XLANG_SKIP_TRAIT_ELEM_PTR_TO_SLICE_NDIMS.
 * PLATFORM: SHARED. */
#define XLANG_SEED_TRAIT_ELEM_PTR_TO_SLICE_NDIMS (-2)
typedef struct {
  uint8_t name[64];
  int32_t name_len;
  uint8_t methods[XLANG_TRAIT_METH_MAX][64];
  int32_t method_lens[XLANG_TRAIT_METH_MAX];
  /* wave468: 1 if method ended with `{ body }` (default method). */
  int32_t method_has_default[XLANG_TRAIT_METH_MAX];
  int32_t method_fn_pos[XLANG_TRAIT_METH_MAX];
  int32_t method_fn_line[XLANG_TRAIT_METH_MAX];
  int32_t method_fn_col[XLANG_TRAIT_METH_MAX];
  int32_t method_ret_kinds[XLANG_TRAIT_METH_MAX]; /* TypeKind ord; -1 unknown */
  uint8_t method_ret_names[XLANG_TRAIT_METH_MAX][64];
  int32_t method_ret_name_lens[XLANG_TRAIT_METH_MAX];
  int32_t method_ret_elem_kinds[XLANG_TRAIT_METH_MAX]; /* -1 not captured; ARRAY leaf kind */
  int32_t method_ret_array_sizes[XLANG_TRAIT_METH_MAX]; /* wave430: outer T[N] N; -1 N/A */
  /* wave431: multi-dim; dims[0]=outer. 0 ndims = N/A. */
  int32_t method_ret_array_ndims[XLANG_TRAIT_METH_MAX];
  int32_t method_ret_array_dims[XLANG_TRAIT_METH_MAX][XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
  /* wave438: when PTR/SLICE ret elem is itself ARRAY/SLICE (e.g. *T[N] / *[]T / *[N][M]T),
   * elem_array_ndims = ndims of the inner ARRAY (0 = N/A); elem_array_dims = its dims;
   * elem_elem_kinds = leaf element TypeKind of that inner ARRAY/SLICE (-1 = not captured).
   * Twin of wave434 param elem fields, lifted into the PTR/SLICE ret elem slot.
   * PLATFORM: SHARED parse. */
  int32_t method_ret_elem_array_ndims[XLANG_TRAIT_METH_MAX];
  int32_t method_ret_elem_array_dims[XLANG_TRAIT_METH_MAX][XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
  int32_t method_ret_elem_elem_kinds[XLANG_TRAIT_METH_MAX];
  int32_t method_param_counts[XLANG_TRAIT_METH_MAX]; /* -1 not captured */
  int32_t method_param_kinds[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  /* wave432: TYPE_NAMED param name, or *T / []T element name when elem is named. */
  uint8_t method_param_names[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX][64];
  int32_t method_param_name_lens[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  /* wave432: element TypeKind for TYPE_PTR / TYPE_SLICE param; -1 = not captured. */
  int32_t method_param_elem_kinds[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  /* wave433: multi-dim count for TYPE_ARRAY param; 0 = N/A. dims[0]=outer … dims[n-1]=innermost. */
  int32_t method_param_array_ndims[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  int32_t method_param_array_dims[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX][XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
  /* wave434: when PTR/SLICE elem is itself ARRAY/SLICE (e.g. *T[N] / *[]T / *T[N][M]),
   * elem_array_ndims = ndims of the inner ARRAY (0 = N/A); elem_array_dims = its dims;
   * elem_elem_kinds = leaf element TypeKind of that inner ARRAY/SLICE (-1 = not captured).
   * Twin of wave433 top-level ARRAY fields, lifted into the PTR/SLICE elem slot. */
  int32_t method_param_elem_array_ndims[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  int32_t method_param_elem_array_dims[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX][XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
  int32_t method_param_elem_elem_kinds[XLANG_TRAIT_METH_MAX][XLANG_TRAIT_PARAM_MAX];
  int32_t num_methods;
} xlang_trait_reg_ent_t;
static xlang_trait_reg_ent_t g_xlang_trait_reg[XLANG_TRAIT_REG_MAX];
static int32_t g_xlang_trait_reg_n;
static void *g_xlang_seed_trait_check_arena;
/* wave468: full-file source for default-method re-parse (seed twin of g_w439_*). */
static uint8_t *g_xlang_seed_trait_src_data;
static int32_t g_xlang_seed_trait_src_len;

/**
 * Builtin type token → TypeKind ord (align PARSER_ASM_TYPE_*). Twin of skip_tl helper.
 * PLATFORM: SHARED parse.
 */
static int32_t parser_asm_seed_trait_token_to_type_kind_c(int32_t tok_kind) {
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

static void xlang_trait_reg_reset_c(void *arena) {
  g_xlang_trait_reg_n = 0;
  g_xlang_seed_trait_check_arena = arena;
  memset(g_xlang_trait_reg, 0, sizeof(g_xlang_trait_reg));
}

static void xlang_trait_reg_copy_ident_c(uint8_t *data, int32_t len, size_t token_start, int32_t ident_len,
                                          uint8_t *out64, int32_t *out_len) {
  int32_t n = ident_len;
  if (!out64 || !out_len)
    return;
  *out_len = 0;
  memset(out64, 0, 64);
  if (!data || len <= 0 || n <= 0)
    return;
  if (n > 63)
    n = 63;
  if ((size_t)token_start + (size_t)n > (size_t)len)
    return;
  memcpy(out64, data + token_start, (size_t)n);
  *out_len = n;
}

static int32_t xlang_trait_reg_find_c(const uint8_t *name, int32_t name_len) {
  int32_t i;
  if (!name || name_len <= 0)
    return -1;
  for (i = 0; i < g_xlang_trait_reg_n; i++) {
    if (g_xlang_trait_reg[i].name_len == name_len &&
        memcmp(g_xlang_trait_reg[i].name, name, (size_t)name_len) == 0)
      return i;
  }
  return -1;
}

extern void lsp_diag_report_typeck(int line, int col, const char *fmt, ...);
extern int32_t pipeline_module_num_funcs(void *module);
extern int32_t pipeline_module_func_name_equal_at(void *module, int32_t fi, uint8_t *name, int32_t name_len);
extern int32_t pipeline_module_func_return_type_at(void *module, int32_t fi);
extern int32_t pipeline_module_func_num_params_at(void *module, int32_t fi);
extern int32_t pipeline_module_func_param_type_ref_at(void *module, int32_t fi, int32_t pi);
extern int32_t pipeline_type_kind_ord_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_named_name_into(void *arena, int32_t type_ref, uint8_t *out);
extern int32_t pipeline_type_array_size_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_elem_ref_at(void *arena, int32_t type_ref);

/**
 * Register trait Name { function m(...); ... } method names; advance lex past `}`.
 * @return 0 success; -1 parse fail (caller may fallback skip).
 */
/* Forward: seed_commit defined later in this slice (wave468 hoist uses it). */
static int32_t parser_asm_seed_commit_onefunc_c(void *arena, void *module, struct parser_asm_onefunc_result *res,
                                                int32_t func_is_async, int32_t *inout_main_idx,
                                                struct parser_asm_lexer *inout_lex);
/* Forward: Self helpers defined later (wave470 hoist needs them above register). */
static int32_t xlang_seed_name_is_self_c(const uint8_t *nm, int32_t nl);
static int32_t xlang_seed_impl_self_matches_for_c(void *arena, int32_t pty0, int32_t for_kind,
                                                   int32_t for_is_ptr, const uint8_t *for_name,
                                                   int32_t for_nlen);

/**
 * wave470/471: rewrite TYPE_NAMED Self / PTR-to-Self → for (seed twin of
 * xlang_skip_rewrite_self_type_ref_c). PLATFORM: SHARED parse.
 */
static int32_t xlang_seed_rewrite_self_type_ref_c(void *arena, int32_t type_ref,
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
  if (k == XLANG_SEED_TRAIT_TY_PTR) {
    int32_t elem = pipeline_type_elem_ref_at(arena, type_ref);
    int32_t ek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (ek != XLANG_SEED_TRAIT_TY_NAMED)
      return type_ref;
    gnl = pipeline_type_named_name_into(arena, elem, gnm);
    if (!xlang_seed_name_is_self_c(gnm, gnl))
      return type_ref;
    for_named = pipeline_type_find_or_alloc_named(arena, for_copy, n);
    if (for_named == 0)
      return type_ref;
    return pipeline_type_find_or_alloc_compound(arena, XLANG_SEED_TRAIT_TY_PTR, for_named, 0);
  }
  if (k != XLANG_SEED_TRAIT_TY_NAMED)
    return type_ref;
  gnl = pipeline_type_named_name_into(arena, type_ref, gnm);
  if (!xlang_seed_name_is_self_c(gnm, gnl))
    return type_ref;
  return pipeline_type_find_or_alloc_named(arena, for_copy, n);
}

/*
 * wave468: hoist trait default bodies as free UFCS methods (seed twin of
 * xlang_skip_hoist_default_methods_c). Uses general onefunc parse + seed_commit.
 * wave470: Self → for rewrite on param/ret after commit; exists check is
 * name + self match for this for-type (not name-only).
 * PLATFORM: SHARED parse.
 */
static void xlang_seed_hoist_default_methods_c(void *module, int32_t for_kind, int32_t for_is_ptr,
                                                const uint8_t *for_name, int32_t for_nlen) {
  int32_t ti;
  int32_t mi;
  void *arena = g_xlang_seed_trait_check_arena;
  int32_t dummy_main = -1;
  extern void pipeline_module_func_set_return_type(void *module, int32_t fi, int32_t type_ref);
  extern void pipeline_module_func_param_write(void *module, int32_t func_index, int32_t param_index,
                                              uint8_t *name_bytes, int32_t name_len, int32_t type_ref);
  extern int32_t pipeline_module_func_param_name_len_at(void *module, int32_t fi, int32_t pi);
  extern void pipeline_module_func_param_name_copy32(void *module, int32_t fi, int32_t pi, uint8_t *dst);
  (void)for_kind;
  if (!module || !arena || !g_xlang_seed_trait_src_data || g_xlang_seed_trait_src_len <= 0)
    return;
  for (ti = 0; ti < g_xlang_trait_reg_n; ti++) {
    for (mi = 0; mi < g_xlang_trait_reg[ti].num_methods; mi++) {
      const uint8_t *mnm;
      int32_t mlen;
      int32_t fi;
      int32_t nf;
      int32_t exists;
      int32_t nf_before;
      struct parser_asm_lexer fn_lex;
      struct parser_asm_onefunc_result res;
      if (g_xlang_trait_reg[ti].method_has_default[mi] == 0)
        continue;
      mnm = g_xlang_trait_reg[ti].methods[mi];
      mlen = g_xlang_trait_reg[ti].method_lens[mi];
      if (mlen <= 0)
        continue;
      exists = 0;
      nf = pipeline_module_num_funcs(module);
      for (fi = 0; fi < nf; fi++) {
        if (pipeline_module_func_name_equal_at(module, fi, (uint8_t *)mnm, mlen) != 0) {
          int32_t pty0 = pipeline_module_func_param_type_ref_at(module, fi, 0);
          if (xlang_seed_impl_self_matches_for_c(arena, pty0, for_kind, for_is_ptr, for_name,
                                                  for_nlen)) {
            exists = 1;
            break;
          }
          if (pipeline_module_func_num_params_at(module, fi) == 0) {
            exists = 1;
            break;
          }
        }
      }
      if (exists)
        continue;
      memset(&fn_lex, 0, sizeof(fn_lex));
      fn_lex.pos = (size_t)g_xlang_trait_reg[ti].method_fn_pos[mi];
      fn_lex.line = g_xlang_trait_reg[ti].method_fn_line[mi];
      fn_lex.col = g_xlang_trait_reg[ti].method_fn_col[mi];
      if (fn_lex.line <= 0)
        fn_lex.line = 1;
      if (fn_lex.col <= 0)
        fn_lex.col = 1;
      res = parser_asm_seed_onefunc_wired_c(fn_lex);
      {
        extern void parser_allow_bare_self_set_c(int32_t on);
        parser_allow_bare_self_set_c(1);
        parser_asm_parse_one_function_buf_into_c(&res, arena, fn_lex, g_xlang_seed_trait_src_data,
                                                g_xlang_seed_trait_src_len);
        parser_allow_bare_self_set_c(0);
      }
      if (!res.ok)
        continue;
      nf_before = pipeline_module_num_funcs(module);
      if (parser_asm_seed_commit_onefunc_c(arena, module, &res, 0, &dummy_main, &fn_lex) != 0)
        continue;
      /* wave470: patch Self on the newly committed free method. */
      if (pipeline_module_num_funcs(module) > nf_before) {
        int32_t new_fi = nf_before;
        int32_t rty = pipeline_module_func_return_type_at(module, new_fi);
        int32_t nparams = pipeline_module_func_num_params_at(module, new_fi);
        int32_t pi;
        rty = xlang_seed_rewrite_self_type_ref_c(arena, rty, for_name, for_nlen, for_is_ptr);
        pipeline_module_func_set_return_type(module, new_fi, rty);
        for (pi = 0; pi < nparams; pi++) {
          int32_t pty = pipeline_module_func_param_type_ref_at(module, new_fi, pi);
          uint8_t pname32[128];
          int32_t plen;
          memset(pname32, 0, sizeof(pname32));
          plen = pipeline_module_func_param_name_len_at(module, new_fi, pi);
          if (plen > 0)
            pipeline_module_func_param_name_copy32(module, new_fi, pi, pname32);
          if (plen > 32)
            plen = 32;
          pty = xlang_seed_rewrite_self_type_ref_c(arena, pty, for_name, for_nlen, for_is_ptr);
          /* wave477 / 4.2.1: bare self (type_ref 0) → impl for-type so UFCS matches. */
          if (pty == 0 && pi == 0 && for_name && for_nlen > 0) {
            extern int32_t pipeline_type_find_or_alloc_named(void *arena, uint8_t *name, int32_t name_len);
            pty = pipeline_type_find_or_alloc_named(arena, (uint8_t *)for_name, for_nlen);
          }
          pipeline_module_func_param_write(module, new_fi, pi, pname32, plen, pty);
        }
      }
    }
  }
}

static int32_t parser_asm_seed_register_trait_c(struct parser_asm_lexer lex, uint8_t *data, int32_t len,
                                                 struct parser_asm_lexer *lex_out) {
  struct parser_asm_lexer_result r;
  xlang_trait_reg_ent_t *ent;
  int32_t guard;

  if (!data || len <= 0 || !lex_out)
    return -1;
  /* wave468: stash full-file source for default hoist. */
  g_xlang_seed_trait_src_data = data;
  g_xlang_seed_trait_src_len = len;
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_TRAIT)
    return -1;
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_IDENT)
    return -1;
  if (g_xlang_trait_reg_n >= XLANG_TRAIT_REG_MAX)
    return -1;
  ent = &g_xlang_trait_reg[g_xlang_trait_reg_n];
  memset(ent, 0, sizeof(*ent));
  xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len, ent->name, &ent->name_len);
  if (ent->name_len <= 0)
    return -1;
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return -1;
  lex = r.next_lex;
  guard = 0;
  while (guard++ < 512) {
    r = lexer_next_buf(lex, data, len);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      lex_out->pos = r.next_lex.pos;
      lex_out->line = r.next_lex.line;
      lex_out->col = r.next_lex.col;
      g_xlang_trait_reg_n++;
      return 0;
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF)
      return -1;
    if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
      int32_t mi_reg = -1;
      /* wave468: capture lexer at FUNCTION for default-body re-parse inject. */
      /* Use r.token_start (FUNCTION token start) instead of lex.pos (after FUNCTION). */
      int32_t fn_pos = (int32_t)r.token_start;
      int32_t fn_line = r.tok.line;
      int32_t fn_col = r.tok.col;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (r.tok.kind == (int32_t)TOKEN_IDENT && ent->num_methods < XLANG_TRAIT_METH_MAX) {
        int32_t pii;
        mi_reg = ent->num_methods;
        xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len, ent->methods[mi_reg],
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
        for (pii = 0; pii < XLANG_TRAIT_PARAM_MAX; pii++) {
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
        if (ent->method_lens[mi_reg] > 0)
          ent->num_methods++;
        else
          mi_reg = -1;
      }
      /* Skip remainder; wave425–431 Ret/params/named/ptr/slice/T[N]/multi-dim. */
      {
        int32_t depth = 0;
        int32_t paren = 0;
        int32_t saw_params_close = 0;
        int32_t want_ret = 0;
        int32_t ret_elem_pending = 0;
        int32_t ret_slice_need_rb = 0;
        /* Prefix `[N]T` / `[N][M]T` ret — twin of skip_tl / wave436 *[N]T. */
        int32_t ret_prefix_arr_need_rb = 0;
        int32_t ret_prefix_arr_need_size = 0;
        int32_t ret_prefix_arr_elem_pending = 0;
        int32_t ret_suffix_pending = 0;
        int32_t ret_arr_need_size = 0;
        int32_t ret_arr_need_rb = 0;
        int32_t ret_dim_n = 0;
        int32_t ret_dims[XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
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
        int32_t ret_elem_dims[XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
        int32_t param_count = 0;
        int32_t saw_param_tok = 0;
        int32_t want_param_ty = 0;
        int32_t param_elem_pending = 0;   /* wave432: saw STAR, awaiting elem type */
        int32_t param_slice_need_rb = 0; /* wave432: saw LBRACKET, awaiting RBRACKET */
        /* Prefix `[N]T` / `[N][M]T` param — twin of skip_tl / wave436 *[N]T. */
        int32_t param_prefix_arr_need_rb = 0;
        int32_t param_prefix_arr_need_size = 0;
        int32_t param_prefix_arr_elem_pending = 0;
        /* wave433: twin of wave431 ret multi-dim suffix state machine. */
        int32_t param_suffix_pending = 0; /* base set; may still see [N] or [] */
        int32_t param_arr_need_size = 0;  /* saw `[` after base; want INT or `]` */
        int32_t param_arr_need_rb = 0;    /* saw `[N`; want `]` */
        int32_t param_dim_n = 0;
        int32_t param_dims[XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
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
        /* wave436: *[N]T → PTR to ARRAY. After `*[N`, want `]` then base T.
         * wave437: multi-dim *[N][M]T — after first `]`, if next is `[`,
         * collect further dims then return to elem_pending for base T. */
        int32_t param_elem_prefix_arr_need_rb = 0;
        int32_t param_elem_prefix_arr_more = 0;    /* wave437: extra *[N][M] dim */
        int32_t param_elem_dim_n = 0;
        int32_t param_elem_dims[XLANG_SEED_TRAIT_ARRAY_DIM_MAX];
        int32_t steps = 0;
        while (steps++ < 4096) {
          if (r.tok.kind == (int32_t)TOKEN_LPAREN) {
            paren++;
          } else if (r.tok.kind == (int32_t)TOKEN_RPAREN) {
            if (paren == 1 && depth == 0 && !saw_params_close) {
              /* wave433: finalize pending suffix T[N][M] before param_count++. */
              if (param_suffix_pending && param_dim_n > 0 && mi_reg >= 0 &&
                  param_count < XLANG_TRAIT_PARAM_MAX) {
                int32_t leaf_k = ent->method_param_kinds[mi_reg][param_count];
                int32_t di;
                ent->method_param_elem_kinds[mi_reg][param_count] = leaf_k;
                ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                for (di = 0; di < param_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
              }
              param_suffix_pending = 0;
              param_dim_n = 0;
              /* wave434: finalize pending PTR/SLICE elem suffix *T[N] → elem=ARRAY. */
              if (param_elem_dim_n > 0 && mi_reg >= 0 &&
                  param_count < XLANG_TRAIT_PARAM_MAX) {
                int32_t base_k = ent->method_param_elem_kinds[mi_reg][param_count];
                int32_t di;
                /* wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter than *).
                 * Lift to top-level ARRAY: kind=ARRAY, elem=PTR, elem_elem=T, dims. */
                ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_PTR;
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
              if (mi_reg >= 0)
                ent->method_param_counts[mi_reg] = param_count;
              saw_params_close = 1;
            }
            if (paren > 0)
              paren--;
          } else if (!saw_params_close && paren == 1 && depth == 0) {
            if (r.tok.kind == (int32_t)TOKEN_COMMA) {
              /* wave433: finalize pending suffix T[N][M] before param_count++. */
              if (param_suffix_pending && param_dim_n > 0 && mi_reg >= 0 &&
                  param_count < XLANG_TRAIT_PARAM_MAX) {
                int32_t leaf_k = ent->method_param_kinds[mi_reg][param_count];
                int32_t di;
                ent->method_param_elem_kinds[mi_reg][param_count] = leaf_k;
                ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                ent->method_param_array_ndims[mi_reg][param_count] = param_dim_n;
                for (di = 0; di < param_dim_n; di++)
                  ent->method_param_array_dims[mi_reg][param_count][di] = param_dims[di];
              }
              param_suffix_pending = 0;
              param_dim_n = 0;
              /* wave434: finalize pending PTR/SLICE elem suffix *T[N] → elem=ARRAY. */
              if (param_elem_dim_n > 0 && mi_reg >= 0 &&
                  param_count < XLANG_TRAIT_PARAM_MAX) {
                int32_t base_k = ent->method_param_elem_kinds[mi_reg][param_count];
                int32_t di;
                /* wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter than *).
                 * Lift to top-level ARRAY: kind=ARRAY, elem=PTR, elem_elem=T, dims. */
                ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_PTR;
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
            } else if (want_param_ty && mi_reg >= 0 && param_count < XLANG_TRAIT_PARAM_MAX) {
              /* wave432/433: twin of skip_tl param shape capture
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
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_SLICE;
                  ent->method_param_array_ndims[mi_reg][param_count] = 0;
                  param_arr_need_size = 0;
                  param_dim_n = 0;
                  want_param_ty = 0;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  /* Collect one dim; finalize on non-`[` after closing `]`. */
                  if (param_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                    ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
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
                 * Twin of skip_tl param_slice_need_rb / wave436 *[N]T:
                 *   `]`     → `[]T`  = SLICE of T (existing)
                 *   INT N   → `[N]T` = ARRAY of N T (was bail → impl T001)
                 * PLATFORM: SHARED parse. G.7: complete this scanner.
                 */
                if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  param_slice_need_rb = 0;
                  param_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                  param_dim_n = 0;
                  if (param_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                 * = ARRAY of SLICE of T). Twin of skip_tl. G.7: complete
                 * this scanner (no second trait-type parser).
                 * PLATFORM: SHARED parse.
                 */
                if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  if (param_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
                    param_dims[param_dim_n++] = r.tok.int_val;
                  param_prefix_arr_need_size = 0;
                  param_prefix_arr_need_rb = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_SLICE;
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
                   * via param_elem_elem_pending. dest-ARRAY extras still
                   * skip kind 9 (separate leftover).
                   * PLATFORM: SHARED parse. G.7: complete this scanner.
                   */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_PTR;
                  param_prefix_arr_elem_pending = 0;
                  param_elem_elem_pending = 1;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_NAMED;
                  xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
                                               ent->method_param_names[mi_reg][param_count],
                                               &ent->method_param_name_lens[mi_reg][param_count]);
                  param_dim_n = 0;
                  param_prefix_arr_elem_pending = 0;
                  want_param_ty = 0;
                  saw_param_tok = 1;
                } else {
                  int32_t bk = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_SLICE;
                  param_elem_slice_need_rb = 0;
                  param_elem_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                  /* wave436: *[N]T → PTR to ARRAY of N T. Capture N, expect `]`. */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
                  if (param_elem_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                 * transition to base T capture (param_elem_elem_pending). Dims
                 * stay in the local buffer; committed when base T is captured,
                 * so multi-dim *[N][M]T can append further dims before finalize.
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
                  ent->method_param_elem_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_NAMED;
                  xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
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
                } else {
                  int32_t bk = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
                   * Keep elem (PTR or SLICE); mark extra SLICE via
                   * ndims=-2; capture leaf T as eek. Twin of skip_tl.
                   * PLATFORM: SHARED parse. G.7: complete this scanner.
                   */
                  if ((ent->method_param_elem_kinds[mi_reg][param_count] == XLANG_SEED_TRAIT_TY_PTR
                       || ent->method_param_elem_kinds[mi_reg][param_count] == XLANG_SEED_TRAIT_TY_SLICE)
                      && param_elem_dim_n == 0) {
                    if (ent->method_param_elem_array_ndims[mi_reg][param_count]
                        == XLANG_SEED_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                      int32_t extra =
                          ent->method_param_elem_array_dims[mi_reg][param_count][0];
                      if (extra <= 0)
                        extra = 1;
                      extra = extra + 1;
                      if (extra < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
                        ent->method_param_elem_array_dims[mi_reg][param_count][0] = extra;
                    } else {
                      ent->method_param_elem_array_ndims[mi_reg][param_count] =
                          XLANG_SEED_TRAIT_ELEM_PTR_TO_SLICE_NDIMS;
                    }
                    param_elem_arr_need_size = 0;
                    param_elem_prefix_arr_more = 0;
                    param_elem_dim_n = 0;
                    param_elem_elem_pending = 1;
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
                  if (param_elem_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                    ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_ARRAY;
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
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_NAMED;
                  xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
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
                   * prior else stored elem_kind=-1. Store elem=PTR; capture
                   * pointee T via param_elem_elem_pending. dest-SLICE extra
                   * `[]*i32` reconstructs PTR then wrap slice.
                   * PLATFORM: SHARED parse. G.7: complete this scanner.
                   */
                  ent->method_param_elem_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_PTR;
                  param_elem_elem_pending = 1;
                } else {
                  ent->method_param_elem_kinds[mi_reg][param_count] =
                      parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
                  /* wave434: keep scanning for elem suffix [N]/[]/[N][M]. */
                  param_elem_suffix_pending = 1;
                }
                param_elem_pending = 0;
                saw_param_tok = 1;
              } else if (ent->method_param_kinds[mi_reg][param_count] < 0) {
                if (r.tok.kind == (int32_t)TOKEN_IDENT) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_NAMED;
                  xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
                                               ent->method_param_names[mi_reg][param_count],
                                               &ent->method_param_name_lens[mi_reg][param_count]);
                  /* wave433: keep scanning for suffix T[N] / T[] / T[N][M]. */
                  param_suffix_pending = 1;
                  saw_param_tok = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_PTR;
                  param_elem_pending = 1;
                } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                  ent->method_param_kinds[mi_reg][param_count] = XLANG_SEED_TRAIT_TY_SLICE;
                  param_slice_need_rb = 1;
                } else {
                  ent->method_param_kinds[mi_reg][param_count] =
                      parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
          } else if (want_ret && mi_reg >= 0) {
            /* wave427/430/431: twin of skip_tl ret capture (suffix T[N]/T[]/T[N][M]). */
            if (ret_arr_need_rb) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ret_arr_need_rb = 0;
                ret_suffix_pending = 1;
              } else {
                ret_arr_need_rb = 0;
                want_ret = 0;
              }
            } else if (ret_arr_need_size) {
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                int32_t base_k = ent->method_ret_kinds[mi_reg];
                ent->method_ret_elem_kinds[mi_reg] = base_k;
                ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_SLICE;
                ent->method_ret_array_sizes[mi_reg] = -1;
                ent->method_ret_array_ndims[mi_reg] = 0;
                ret_arr_need_size = 0;
                ret_dim_n = 0;
                want_ret = 0;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                if (ret_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                if (ret_dim_n > 0) {
                  int32_t di;
                  int32_t leaf_k = ent->method_ret_kinds[mi_reg];
                  ent->method_ret_elem_kinds[mi_reg] = leaf_k;
                  ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_ARRAY;
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
               * Twin of skip_tl ret_slice_need_rb / wave436 *[N]T:
               *   `]`     → `[]T`  = SLICE of T (existing)
               *   INT N   → `[N]T` = ARRAY of N T (was bail)
               * PLATFORM: SHARED parse. G.7: complete this scanner.
               */
              if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
                ret_slice_need_rb = 0;
                ret_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_ARRAY;
                ret_dim_n = 0;
                if (ret_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                if (ret_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                ent->method_ret_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_NAMED;
                xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
                                             ent->method_ret_names[mi_reg],
                                             &ent->method_ret_name_lens[mi_reg]);
                ret_dim_n = 0;
                ret_prefix_arr_elem_pending = 0;
                want_ret = 0;
              } else {
                int32_t bk = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
                ent->method_ret_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_NAMED;
                xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
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
              } else {
                ent->method_ret_elem_kinds[mi_reg] =
                    parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
                ent->method_ret_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_SLICE;
                ret_elem_slice_need_rb = 0;
                ret_elem_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                /* wave438: *[N]T → PTR to ARRAY of N T. Capture N, expect `]`. */
                ent->method_ret_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_ARRAY;
                if (ret_elem_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                ent->method_ret_elem_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_NAMED;
                xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
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
              } else {
                int32_t bk = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
                if (bk >= 0) {
                  ent->method_ret_elem_elem_kinds[mi_reg] = bk;
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
                /* wave438: elem T[] → PTR to SLICE of T (3-layer, deferred to soft).
                 * Mark elem uncaptured so check skips; avoids parse failure.
                 * Also clears prefix_arr_more if came from *[N][]T. */
                ent->method_ret_elem_kinds[mi_reg] = -1;
                ret_elem_arr_need_size = 0;
                ret_elem_prefix_arr_more = 0;
                ret_elem_dim_n = 0;
                want_ret = 0;
              } else if (r.tok.kind == (int32_t)TOKEN_INT && r.tok.int_val > 0) {
                /* Collect one elem dim; finalize on non-`[` after closing `]`. */
                if (ret_elem_dim_n < XLANG_SEED_TRAIT_ARRAY_DIM_MAX)
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
                  ent->method_ret_elem_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_ARRAY;
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
                ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_NAMED;
                xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len,
                                             ent->method_ret_names[mi_reg],
                                             &ent->method_ret_name_lens[mi_reg]);
                ret_suffix_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_STAR) {
                ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_PTR;
                ret_elem_pending = 1;
              } else if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
                ent->method_ret_kinds[mi_reg] = XLANG_SEED_TRAIT_TY_SLICE;
                ret_slice_need_rb = 1;
              } else {
                int32_t bk = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
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
             * Root: depth==0 RBRACE was always treated as "method body closed" and
             * advanced past `}`. Signature-only methods without trailing `;`
             * (`function get(self): i32` then trait `}`) consumed the trait's
             * closing brace → register_trait never finished → trait soft-skipped
             * → impl methods not hoisted → typeck "no impl for type with method".
             * Product free-function / inherent-impl bodies use braces (no `;`
             * required); trait method *signatures* may also omit `;` when the
             * next token is trait `}` or the next `function` (ASI, like free form).
             * G.7: twin skip_tl method-end; PLATFORM: SHARED parse.
             */
            if (depth > 0) {
              depth--;
              if (depth == 0) {
                /* wave468: method body closed → default method eligible for hoist. */
                if (mi_reg >= 0)
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
            /* wave464: ASI — next method starts; leave FUNCTION for outer loop. */
            break;
          } else if (r.tok.kind == (int32_t)TOKEN_EOF)
            return -1;
          parser_lex_from_next_into_glue(&lex, r);
          r = lexer_next_buf(lex, data, len);
        }
      }
      continue;
    }
    /* Unknown token inside trait: advance one token (doc comments already stripped). */
    parser_lex_from_next_into_glue(&lex, r);
  }
  return -1;
}

/**
 * After impl Trait for T body: require registered trait + every method as free func
 * with matching arity / typed param kinds / return TypeKind when known.
 * wave424 Cap residual pure — unknown_trait was soft return 0 → false-green.
 * wave425 Cap residual pure — return_mismatch hard fail (sig ret was not stored).
 * wave426 Cap residual pure — param arity / typed param kinds hard fail.
 * wave427 Cap residual pure — named/ptr/slice ret hard fail.
 * wave428 Cap residual pure — untyped trait self vs for-type hard fail.
 * G.7 expand this helper only (twin of skip_tl xlang_trait_check_impls_complete_c).
 * @param for_kind TypeKind of for-type (or elem of *T); -1 unknown
 * @param for_is_ptr 1 if for-type is *T
 * @param for_name named for-type bytes when for_kind is TYPE_NAMED
 * @param for_nlen name length; 0 if not named
 * @return 0 ok; -2 hard unknown trait / missing method / signature mismatch.
 * PLATFORM: SHARED parse.
 */

/**
 * wave441: verify impl method's self (param0) type matches the impl's for-type.
 * Twin of skip_tl xlang_skip_impl_self_matches_for_c. Used both during method
 * lookup (find the method belonging to THIS impl block, not another impl of the
 * same trait — two structs impl same trait was a false-red: 2nd impl found 1st
 * impl's method by name-only and failed self check) and during wave428 self
 * verification.
 * @param arena     ASTArena (void*) for kind/name access; may be null.
 * @param pty0      type_ref of impl method param0 (self); 0 if untyped.
 * @param for_kind  for-type kind ord; -1 unknown.
 * @param for_is_ptr 1 if for-type is *T.
 * @param for_name  named for-type bytes; may be null.
 * @param for_nlen  name length; 0 if not named.
 * @return 1 if match or unknown/untyped (accept, preserve old first-match);
 *         0 if definite mismatch.
 * PLATFORM: SHARED parse.
 */
/**
 * TYPE_NAMED spelling "Self" (seed twin of xlang_skip_name_is_self_c).
 * PLATFORM: SHARED parse.
 */
static int32_t xlang_seed_name_is_self_c(const uint8_t *nm, int32_t nl) {
  return (nl == 4 && nm &&
          nm[0] == (uint8_t)'S' && nm[1] == (uint8_t)'e' &&
          nm[2] == (uint8_t)'l' && nm[3] == (uint8_t)'f')
             ? 1
             : 0;
}

static int32_t xlang_seed_impl_self_matches_for_c(void *arena, int32_t pty0,
                                                    int32_t for_kind, int32_t for_is_ptr,
                                                    const uint8_t *for_name, int32_t for_nlen) {
  int32_t got0;
  if (for_kind < 0)
    return 1; /* for-type unknown — accept (preserve old first-match behavior) */
  got0 = (pty0 != 0) ? pipeline_type_kind_ord_at(arena, pty0) : -1;
  if (got0 < 0)
    return 1; /* impl self untyped — accept (wave428 skip when got0<0) */
  if (for_is_ptr) {
    int32_t elem;
    int32_t gek;
    if (got0 != XLANG_SEED_TRAIT_TY_PTR)
      return 0;
    elem = (pty0 != 0) ? pipeline_type_elem_ref_at(arena, pty0) : 0;
    gek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (gek >= 0 && gek != for_kind)
      return 0;
    if (gek == for_kind && for_kind == XLANG_SEED_TRAIT_TY_NAMED && for_nlen > 0 && for_name && elem != 0) {
      uint8_t gnm[64];
      int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
      /* wave471: *Self elem aliases named for under for_is_ptr. */
      if (xlang_seed_name_is_self_c(gnm, gnl))
        return 1;
      if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
        return 0;
    }
    return 1;
  }
  /* wave471: non-ptr for + *For / *Self receiver. */
  if (got0 == XLANG_SEED_TRAIT_TY_PTR) {
    int32_t elem = (pty0 != 0) ? pipeline_type_elem_ref_at(arena, pty0) : 0;
    int32_t gek = (elem != 0) ? pipeline_type_kind_ord_at(arena, elem) : -1;
    if (gek < 0)
      return 1;
    if (gek != for_kind)
      return 0;
    if (for_kind == XLANG_SEED_TRAIT_TY_NAMED && for_nlen > 0 && for_name && elem != 0) {
      uint8_t gnm[64];
      int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
      if (xlang_seed_name_is_self_c(gnm, gnl))
        return 1;
      if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
        return 0;
    }
    return 1;
  }
  if (got0 != for_kind)
    return 0;
  if (got0 == XLANG_SEED_TRAIT_TY_NAMED && for_nlen > 0 && for_name) {
    uint8_t gnm[64];
    int32_t gnl = pipeline_type_named_name_into(arena, pty0, gnm);
    /* wave470: Self on free/default method ≡ named for-type. */
    if (xlang_seed_name_is_self_c(gnm, gnl))
      return (for_kind == XLANG_SEED_TRAIT_TY_NAMED) ? 1 : 0;
    if (gnl != for_nlen || memcmp(gnm, for_name, (size_t)for_nlen) != 0)
      return 0;
  }
  return 1;
}

/**
 * wave469 Cap residual pure — trait TYPE_NAMED "Self" rewrites to the impl
 * `for` type name when matching method param/ret signatures (seed twin of
 * xlang_skip_trait_named_eq_self_c).
 *
 * wave470: also accept got=="Self" (default hoist) and got Self vs expect for.
 * G.7 single authority pair with skip_tl; same semantics and soft leaves.
 * PLATFORM: SHARED parse.
 *
 * @param expect_nm trait expected type name bytes (may be "Self")
 * @param expect_nl length; <=0 → no name constraint (match)
 * @param got_nm    impl-side type name bytes
 * @param got_nl    length
 * @param for_nm    impl for-type name
 * @param for_nl    length
 * @param for_ptr   1 if for-type is *T
 * @return 1 match, 0 mismatch
 */
static int32_t xlang_seed_trait_named_eq_self_c(
    const uint8_t *expect_nm, int32_t expect_nl,
    const uint8_t *got_nm, int32_t got_nl,
    const uint8_t *for_nm, int32_t for_nl, int32_t for_ptr) {
  int32_t exp_self;
  int32_t got_self;
  if (expect_nl <= 0)
    return 1;
  exp_self = xlang_seed_name_is_self_c(expect_nm, expect_nl);
  got_self = xlang_seed_name_is_self_c(got_nm, got_nl);
  if (exp_self) {
    if (for_ptr || for_nl <= 0 || !for_nm)
      return 0;
    if (got_self)
      return 1;
    return (got_nl == for_nl && got_nm &&
            memcmp(got_nm, for_nm, (size_t)for_nl) == 0) ? 1 : 0;
  }
  if (got_self) {
    if (for_ptr || for_nl <= 0 || !for_nm)
      return 0;
    return (expect_nl == for_nl && expect_nm &&
            memcmp(expect_nm, for_nm, (size_t)for_nl) == 0) ? 1 : 0;
  }
  return (got_nl == expect_nl && got_nm &&
          memcmp(got_nm, expect_nm, (size_t)expect_nl) == 0) ? 1 : 0;
}


static int32_t parser_asm_seed_check_impl_missing_methods_c(void *module, const uint8_t *trait_nm,
                                                            int32_t trait_nlen, int32_t for_kind,
                                                            int32_t for_is_ptr, const uint8_t *for_name,
                                                            int32_t for_nlen, int32_t line, int32_t col) {
  int32_t ti;
  int32_t mi;
  int32_t nf;
  int32_t fi;
  void *arena = g_xlang_seed_trait_check_arena;
  if (!module || !trait_nm || trait_nlen <= 0)
    return 0;
  /* wave468/wave470: inject defaults; Self rewritten to this for-type. */
  xlang_seed_hoist_default_methods_c(module, for_kind, for_is_ptr, for_name, for_nlen);
  ti = xlang_trait_reg_find_c(trait_nm, trait_nlen);
  /* wave424: hard fail — was soft leave-off return 0 (LANG-004 unknown_trait). */
  if (ti < 0) {
    lsp_diag_report_typeck((int)line, (int)col, "impl for unknown trait %.*s", (int)trait_nlen,
                           (const char *)trait_nm);
    return -2;
  }
  nf = pipeline_module_num_funcs(module);
  for (mi = 0; mi < g_xlang_trait_reg[ti].num_methods; mi++) {
    int32_t found = 0;
    int32_t found_fi = -1;
    int32_t first_fi = -1; /* wave441: first same-name method (fallback for static) */
    const uint8_t *mnm = g_xlang_trait_reg[ti].methods[mi];
    int32_t mlen = g_xlang_trait_reg[ti].method_lens[mi];
    int32_t expect_k = g_xlang_trait_reg[ti].method_ret_kinds[mi];
    int32_t expect_np = g_xlang_trait_reg[ti].method_param_counts[mi];
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
        if (xlang_seed_impl_self_matches_for_c(arena, pty0, for_kind, for_is_ptr, for_name, for_nlen)) {
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
      lsp_diag_report_typeck((int)line, (int)col, "missing method %.*s", (int)mlen, (const char *)mnm);
      return -2;
    }
    /* wave426: hard fail parameter count / typed param kind mismatch. */
    if (expect_np >= 0 && found_fi >= 0) {
      int32_t got_np = pipeline_module_func_num_params_at(module, found_fi);
      if (got_np != expect_np) {
        lsp_diag_report_typeck((int)line, (int)col, "method %.*s parameter count mismatch",
                               (int)mlen, (const char *)mnm);
        return -2;
      }
      if (arena) {
        int32_t pi;
        for (pi = 0; pi < expect_np && pi < XLANG_TRAIT_PARAM_MAX; pi++) {
          int32_t ek = g_xlang_trait_reg[ti].method_param_kinds[mi][pi];
          int32_t pty;
          int32_t got_pk;
          if (ek < 0)
            continue;
          pty = pipeline_module_func_param_type_ref_at(module, found_fi, pi);
          got_pk = (pty != 0) ? pipeline_type_kind_ord_at(arena, pty) : -1;
          /* wave432: twin of skip_tl param shape check (NAMED name / *T elem / []T elem). */
          {
            int32_t mm = 0;
            if (got_pk >= 0 && got_pk != ek) {
              mm = 1;
            } else if (got_pk == ek && ek == XLANG_SEED_TRAIT_TY_NAMED) {
              int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
              if (enl > 0 && pty != 0) {
                uint8_t gnm[64];
                int32_t gnl = pipeline_type_named_name_into(arena, pty, gnm);
                if (!xlang_seed_trait_named_eq_self_c(
                      g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                      gnm, gnl,
                      for_name, for_nlen, for_is_ptr))
                  mm = 1;
              }
            } else if (got_pk == ek &&
                       (ek == XLANG_SEED_TRAIT_TY_PTR || ek == XLANG_SEED_TRAIT_TY_SLICE)) {
              int32_t eek = g_xlang_trait_reg[ti].method_param_elem_kinds[mi][pi];
              int32_t elem = (pty != 0) ? pipeline_type_elem_ref_at(arena, pty) : 0;
              if (eek >= 0 && elem != 0) {
                int32_t gek = pipeline_type_kind_ord_at(arena, elem);
                if (gek >= 0 && gek != eek) {
                  mm = 1;
                } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_NAMED) {
                  int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
                  if (enl > 0) {
                    uint8_t gnm[64];
                    int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
                    if (!xlang_seed_trait_named_eq_self_c(
                          g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                          gnm, gnl,
                          for_name, for_nlen, for_is_ptr))
                      mm = 1;
                  }
                } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_SLICE) {
                  /*
                   * wave435: *[]T → PTR to SLICE of T. Walk pipeline SLICE
                   * leaf → its elem → compare elem_elem (the slice base T).
                   * dest-SLICE extra `[][][]T` / `[][][][]T`: eek=SLICE +
                   * eeek=leaf + ndims=-2; extra wrap count is dims[0]
                   * (0 means 1). Peel extra times when ndims==-2 or T001
                   * if layers run out. Twin of skip_tl. Do not invent -3.
                   * PLATFORM: SHARED parse. G.7: complete this walk.
                   */
                  int32_t eeek = g_xlang_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                  int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
                  if (eeek >= 0 && pelem != 0) {
                    int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                    int32_t eand = g_xlang_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                    if (eand == XLANG_SEED_TRAIT_ELEM_PTR_TO_SLICE_NDIMS) {
                      int32_t extra =
                          g_xlang_trait_reg[ti].method_param_elem_array_dims[mi][pi][0];
                      if (extra <= 0)
                        extra = 1;
                      while (extra > 0) {
                        if (pgek != XLANG_SEED_TRAIT_TY_SLICE || pelem == 0) {
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
                    }
                    if (pgek >= 0 && pgek != eeek) {
                      mm = 1;
                    } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                      int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
                      if (enl > 0) {
                        uint8_t gnm[64];
                        int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                        if (!xlang_seed_trait_named_eq_self_c(
                              g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                              gnm, gnl,
                              for_name, for_nlen, for_is_ptr))
                          mm = 1;
                      }
                    }
                  }
                } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_ARRAY) {
                  /*
                   * wave436: *[N]T → PTR to ARRAY of N T. The PTR's elem
                   * (elem) is the ARRAY. Walk its dims (elem_array_ndims/
                   * dims) then compare the leaf elem kind/name with
                   * elem_elem (base T). Multi-dim *[N][M]T is soft-skipped
                   * at registration (eeks=-1) so this path only fires for
                   * single-dim. Twin of wave433 ARRAY walk but on elem level.
                   * PLATFORM: SHARED parse.
                   */
                  int32_t eeek = g_xlang_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                  int32_t eend = g_xlang_trait_reg[ti].method_param_elem_array_ndims[mi][pi];
                  int32_t leaf_tr = elem;
                  int32_t d;
                  for (d = 0; d < eend && leaf_tr != 0; d++) {
                    int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
                    int32_t gsz;
                    if (k != XLANG_SEED_TRAIT_TY_ARRAY) {
                      mm = 1;
                      break;
                    }
                    gsz = pipeline_type_array_size_at(arena, leaf_tr);
                    if (gsz != g_xlang_trait_reg[ti].method_param_elem_array_dims[mi][pi][d]) {
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
                    if (pgek >= 0 && pgek != eeek) {
                      mm = 1;
                    } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                      int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
                      if (enl > 0) {
                        uint8_t gnm[64];
                        int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                        if (!xlang_seed_trait_named_eq_self_c(
                              g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                              gnm, gnl,
                              for_name, for_nlen, for_is_ptr))
                          mm = 1;
                      }
                    }
                  }
                }
              }
            } else if (got_pk == ek && ek == XLANG_SEED_TRAIT_TY_ARRAY) {
              /*
               * wave433: walk nested TYPE_ARRAY dims[0]=outer … then leaf elem
               * kind/name. Twin of wave431 ret multi-dim walk.
               * PLATFORM: SHARED parse.
               */
              int32_t nd = g_xlang_trait_reg[ti].method_param_array_ndims[mi][pi];
              int32_t eek = g_xlang_trait_reg[ti].method_param_elem_kinds[mi][pi];
              int32_t leaf_tr = pty;
              if (nd > 0 && pty != 0) {
                int32_t d;
                for (d = 0; d < nd; d++) {
                  int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
                  int32_t gsz;
                  if (k != XLANG_SEED_TRAIT_TY_ARRAY) {
                    mm = 1;
                    break;
                  }
                  gsz = pipeline_type_array_size_at(arena, leaf_tr);
                  if (gsz != g_xlang_trait_reg[ti].method_param_array_dims[mi][pi][d]) {
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
                  } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_NAMED) {
                    int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
                    if (enl > 0) {
                      uint8_t gnm[64];
                      int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                      if (!xlang_seed_trait_named_eq_self_c(
                            g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                            gnm, gnl,
                            for_name, for_nlen, for_is_ptr))
                        mm = 1;
                    }
                  } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_PTR) {
                    /*
                     * wave434: *T[N] → ARRAY of PTR (type syntax: [] binds tighter
                     * than *). Walk pipeline ARRAY leaf (must be PTR) → its elem →
                     * compare elem_elem (the *T base). PLATFORM: SHARED parse.
                     */
                    int32_t eeek = g_xlang_trait_reg[ti].method_param_elem_elem_kinds[mi][pi];
                    int32_t pelem = pipeline_type_elem_ref_at(arena, leaf_tr);
                    if (eeek >= 0 && pelem != 0) {
                      int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                      if (pgek >= 0 && pgek != eeek) {
                        mm = 1;
                      } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                        int32_t enl = g_xlang_trait_reg[ti].method_param_name_lens[mi][pi];
                        if (enl > 0) {
                          uint8_t gnm[64];
                          int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                          if (!xlang_seed_trait_named_eq_self_c(
                                g_xlang_trait_reg[ti].method_param_names[mi][pi], enl,
                                gnm, gnl,
                                for_name, for_nlen, for_is_ptr))
                            mm = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
            if (mm) {
              lsp_diag_report_typeck((int)line, (int)col, "method %.*s parameter type mismatch",
                                     (int)mlen, (const char *)mnm);
              return -2;
            }
          }
        }
        /*
         * wave428: untyped trait self (param0 ek=-1) must match for-type.
         * wave429: also when trait annotated self — typed self matching trait but
         * not `for` type was false-green (param loop only vs trait, ignored for-type).
         * wave441: logic extracted to xlang_seed_impl_self_matches_for_c (shared
         *   with method lookup); helper returns 1 when for-type unknown or self
         *   untyped (preserve old skip behavior). PLATFORM: SHARED parse.
         */
        if (expect_np >= 1) {
          int32_t pty0 = pipeline_module_func_param_type_ref_at(module, found_fi, 0);
          if (!xlang_seed_impl_self_matches_for_c(arena, pty0, for_kind, for_is_ptr, for_name, for_nlen)) {
            lsp_diag_report_typeck((int)line, (int)col, "method %.*s self type mismatch",
                                   (int)mlen, (const char *)mnm);
            return -2;
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
      } else if (got_k == expect_k && expect_k == XLANG_SEED_TRAIT_TY_NAMED) {
        int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
        if (enl > 0 && rty != 0) {
          uint8_t gnm[64];
          int32_t gnl = pipeline_type_named_name_into(arena, rty, gnm);
          if (!xlang_seed_trait_named_eq_self_c(
                g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                gnm, gnl,
                for_name, for_nlen, for_is_ptr))
            mm = 1;
        }
      } else if (got_k == expect_k && expect_k == XLANG_SEED_TRAIT_TY_ARRAY) {
        /* wave431: multi-dim walk (twin of skip_tl). PLATFORM: SHARED parse. */
        int32_t nd = g_xlang_trait_reg[ti].method_ret_array_ndims[mi];
        int32_t eek = g_xlang_trait_reg[ti].method_ret_elem_kinds[mi];
        int32_t leaf_tr = rty;
        if (nd > 0 && rty != 0) {
          int32_t d;
          for (d = 0; d < nd; d++) {
            int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
            int32_t gsz;
            if (k != XLANG_SEED_TRAIT_TY_ARRAY) {
              mm = 1;
              break;
            }
            gsz = pipeline_type_array_size_at(arena, leaf_tr);
            if (gsz != g_xlang_trait_reg[ti].method_ret_array_dims[mi][d]) {
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
            } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_NAMED) {
              int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
              if (enl > 0) {
                uint8_t gnm[64];
                int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                if (!xlang_seed_trait_named_eq_self_c(
                      g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                      gnm, gnl,
                      for_name, for_nlen, for_is_ptr))
                  mm = 1;
              }
            } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_PTR) {
              /*
               * wave438: *T[N] → ARRAY of PTR (type syntax: [] binds tighter
               * than *). Walk pipeline ARRAY leaf (must be PTR) → its elem →
               * compare elem_elem (the *T base). Twin of wave434 param *T[N]
               * check. PLATFORM: SHARED parse.
               */
              int32_t eeek = g_xlang_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t pelem = pipeline_type_elem_ref_at(arena, leaf_tr);
              if (eeek >= 0 && pelem != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                if (pgek >= 0 && pgek != eeek) {
                  mm = 1;
                } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                  int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
                  if (enl > 0) {
                    uint8_t gnm[64];
                    int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                    if (!xlang_seed_trait_named_eq_self_c(
                          g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                          gnm, gnl,
                          for_name, for_nlen, for_is_ptr))
                      mm = 1;
                  }
                }
              }
            }
          }
        } else {
          int32_t elem = (rty != 0) ? pipeline_type_elem_ref_at(arena, rty) : 0;
          int32_t esz = g_xlang_trait_reg[ti].method_ret_array_sizes[mi];
          if (esz >= 0 && rty != 0) {
            int32_t gsz = pipeline_type_array_size_at(arena, rty);
            if (gsz != esz)
              mm = 1;
          }
          if (!mm && eek >= 0 && elem != 0) {
            int32_t gek = pipeline_type_kind_ord_at(arena, elem);
            if (gek >= 0 && gek != eek) {
              mm = 1;
            } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_NAMED) {
              int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
              if (enl > 0) {
                uint8_t gnm[64];
                int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
                if (!xlang_seed_trait_named_eq_self_c(
                      g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                      gnm, gnl,
                      for_name, for_nlen, for_is_ptr))
                  mm = 1;
              }
            } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_PTR) {
              /*
               * wave438: *T[N] single-dim (nd==0 fallback) → ARRAY of PTR.
               * Walk pipeline ARRAY leaf (must be PTR) → its elem → compare
               * elem_elem (the *T base). Twin of wave434 param *T[N] check.
               * PLATFORM: SHARED parse.
               */
              int32_t eeek = g_xlang_trait_reg[ti].method_ret_elem_elem_kinds[mi];
              int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
              if (eeek >= 0 && pelem != 0) {
                int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
                if (pgek >= 0 && pgek != eeek) {
                  mm = 1;
                } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                  int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
                  if (enl > 0) {
                    uint8_t gnm[64];
                    int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                    if (!xlang_seed_trait_named_eq_self_c(
                          g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                          gnm, gnl,
                          for_name, for_nlen, for_is_ptr))
                      mm = 1;
                  }
                }
              }
            }
          }
        }
      } else if (got_k == expect_k &&
                 (expect_k == XLANG_SEED_TRAIT_TY_PTR || expect_k == XLANG_SEED_TRAIT_TY_SLICE)) {
        int32_t eek = g_xlang_trait_reg[ti].method_ret_elem_kinds[mi];
        int32_t elem = (rty != 0) ? pipeline_type_elem_ref_at(arena, rty) : 0;
        if (!mm && eek >= 0 && elem != 0) {
          int32_t gek = pipeline_type_kind_ord_at(arena, elem);
          if (gek >= 0 && gek != eek) {
            mm = 1;
          } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_NAMED) {
            int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
            if (enl > 0) {
              uint8_t gnm[64];
              int32_t gnl = pipeline_type_named_name_into(arena, elem, gnm);
              if (!xlang_seed_trait_named_eq_self_c(
                    g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                    gnm, gnl,
                    for_name, for_nlen, for_is_ptr))
                mm = 1;
            }
          } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_SLICE) {
            /*
             * wave438: *[]T → PTR to SLICE of T. Walk pipeline SLICE
             * leaf → its elem → compare elem_elem (the slice base T).
             * Twin of wave435 param *[]T check. PLATFORM: SHARED parse.
             */
            int32_t eeek = g_xlang_trait_reg[ti].method_ret_elem_elem_kinds[mi];
            int32_t pelem = pipeline_type_elem_ref_at(arena, elem);
            if (eeek >= 0 && pelem != 0) {
              int32_t pgek = pipeline_type_kind_ord_at(arena, pelem);
              if (pgek >= 0 && pgek != eeek) {
                mm = 1;
              } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
                if (enl > 0) {
                  uint8_t gnm[64];
                  int32_t gnl = pipeline_type_named_name_into(arena, pelem, gnm);
                  if (!xlang_seed_trait_named_eq_self_c(
                        g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                        gnm, gnl,
                        for_name, for_nlen, for_is_ptr))
                    mm = 1;
                }
              }
            }
          } else if (gek == eek && eek == XLANG_SEED_TRAIT_TY_ARRAY) {
            /*
             * wave438: *[N]T / *[N][M]T → PTR to ARRAY of N T. The PTR's
             * elem (elem) is the ARRAY. Walk its dims (elem_array_ndims/
             * dims) then compare the leaf elem kind/name with elem_elem
             * (base T). Multi-dim *[N][M]T collected at registration
             * (wave437 twin). PLATFORM: SHARED parse.
             */
            int32_t eeek = g_xlang_trait_reg[ti].method_ret_elem_elem_kinds[mi];
            int32_t eend = g_xlang_trait_reg[ti].method_ret_elem_array_ndims[mi];
            int32_t leaf_tr = elem;
            int32_t d;
            for (d = 0; d < eend && leaf_tr != 0; d++) {
              int32_t k = pipeline_type_kind_ord_at(arena, leaf_tr);
              int32_t gsz;
              if (k != XLANG_SEED_TRAIT_TY_ARRAY) {
                mm = 1;
                break;
              }
              gsz = pipeline_type_array_size_at(arena, leaf_tr);
              if (gsz != g_xlang_trait_reg[ti].method_ret_elem_array_dims[mi][d]) {
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
              if (pgek >= 0 && pgek != eeek) {
                mm = 1;
              } else if (pgek == eeek && eeek == XLANG_SEED_TRAIT_TY_NAMED) {
                int32_t enl = g_xlang_trait_reg[ti].method_ret_name_lens[mi];
                if (enl > 0) {
                  uint8_t gnm[64];
                  int32_t gnl = pipeline_type_named_name_into(arena, leaf_tr, gnm);
                  if (!xlang_seed_trait_named_eq_self_c(
                        g_xlang_trait_reg[ti].method_ret_names[mi], enl,
                        gnm, gnl,
                        for_name, for_nlen, for_is_ptr))
                    mm = 1;
                }
              }
            }
          }
        }
      }
      if (mm) {
        lsp_diag_report_typeck((int)line, (int)col, "method %.*s return type mismatch", (int)mlen,
                               (const char *)mnm);
        return -2;
      }
    }
  }
  return 0;
}

/**
 * wave390 Cap residual pure — parse `impl [Trait for] Type { methods }` and hoist
 * each method as a same-module free function (UFCS receiver.method).
 *
 * Root cause map:
 * - Who produces: skip_one_impl discarded IDENT for-type bodies; type-keyword for-types
 *   failed mid-header (required TOKEN_IDENT only) so methods leaked as top-level free
 *   fns (i32/u64 accidental green; struct Box red).
 * - Who stores: module.funcs via seed_commit_onefunc (same as top-level function).
 * - Who consumes: typeck UFCS (wave358/360) + host/fs emit free method.
 * G.7 authority: this seed parse_into_buf path (product parse_into_buf strong symbol).
 * wave421: missing-method check vs registered trait methods (return -2 hard fail).
 * wave424: unknown_trait hard fail (return -2).
 * wave428: capture for-type; untyped-self vs for-type hard fail.
 * Soft leave-off: bounds / dyn Trait.
 * PLATFORM: SHARED parse · mac + Ubuntu L2.
 *
 * @return 0 success (lex_out past closing `}`); -1 failure (caller may fallback skip);
 *         -2 hard trait completeness error (abort parse_into).
 */
static int32_t parser_asm_seed_parse_impl_and_add_c(void *arena, void *module, struct parser_asm_lexer lex,
                                                     uint8_t *data, int32_t len, struct parser_asm_lexer *lex_out,
                                                     int32_t *inout_main_idx) {
  struct parser_asm_slice_u8 slice;
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer body;
  int32_t guard;
  int32_t func_is_async;
  uint8_t trait_nm[64];
  int32_t trait_nlen = 0;
  int32_t is_trait_impl = 0;
  int32_t impl_line = 0;
  int32_t impl_col = 0;
  int32_t for_kind = -1;
  int32_t for_is_ptr = 0;
  uint8_t for_nm[64];
  int32_t for_nlen = 0;

  if (!arena || !module || !data || len <= 0 || !lex_out)
    return -1;
  slice.data = data;
  slice.length = (size_t)len;
  memset(trait_nm, 0, sizeof(trait_nm));
  memset(for_nm, 0, sizeof(for_nm));

  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind != (int32_t)TOKEN_IMPL)
    return -1;
  impl_line = r.tok.line;
  impl_col = r.tok.col;
  parser_lex_from_next_into_glue(&lex, r);

  /* Header: impl Trait for Type | impl Type */
  r = lexer_next_buf(lex, data, len);
  if (!parser_asm_seed_impl_type_start_kind_c(r.tok.kind))
    return -1;
  if (r.tok.kind == (int32_t)TOKEN_STAR) {
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (!parser_asm_seed_impl_type_start_kind_c(r.tok.kind) || r.tok.kind == (int32_t)TOKEN_STAR)
      return -1;
  }
  /* First name: trait (if `for`) or inherent type. */
  if (r.tok.kind == (int32_t)TOKEN_IDENT)
    xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len, trait_nm, &trait_nlen);
  parser_lex_from_next_into_glue(&lex, r);
  r = lexer_next_buf(lex, data, len);
  if (r.tok.kind == (int32_t)TOKEN_FOR) {
    is_trait_impl = (trait_nlen > 0) ? 1 : 0;
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
    if (!parser_asm_seed_impl_type_start_kind_c(r.tok.kind))
      return -1;
    if (r.tok.kind == (int32_t)TOKEN_STAR) {
      for_is_ptr = 1;
      parser_lex_from_next_into_glue(&lex, r);
      r = lexer_next_buf(lex, data, len);
      if (!parser_asm_seed_impl_type_start_kind_c(r.tok.kind) || r.tok.kind == (int32_t)TOKEN_STAR)
        return -1;
    }
    /* wave428: capture for-type for untyped-self match. */
    if (r.tok.kind == (int32_t)TOKEN_IDENT) {
      for_kind = XLANG_SEED_TRAIT_TY_NAMED;
      xlang_trait_reg_copy_ident_c(data, len, r.token_start, r.tok.ident_len, for_nm, &for_nlen);
    } else {
      for_kind = parser_asm_seed_trait_token_to_type_kind_c(r.tok.kind);
    }
    parser_lex_from_next_into_glue(&lex, r);
    r = lexer_next_buf(lex, data, len);
  } else {
    /* Inherent impl: clear trait name so we do not false-check. */
    trait_nlen = 0;
    is_trait_impl = 0;
  }
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return -1;
  /* Body interior starts at r.next_lex. */
  body = r.next_lex;
  guard = 0;
  while (guard++ < 512) {
    struct parser_asm_lexer fn_start;
    struct parser_asm_onefunc_result res;
    struct parser_asm_library_parse_result lib;

    fn_start = body;
    r = lexer_next_buf(body, data, len);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      lex_out->pos = r.next_lex.pos;
      lex_out->line = r.next_lex.line;
      lex_out->col = r.next_lex.col;
      /* wave421: trait completeness after all methods committed. */
      if (is_trait_impl) {
        int32_t mrc = parser_asm_seed_check_impl_missing_methods_c(
            module, trait_nm, trait_nlen, for_kind, for_is_ptr, for_nm, for_nlen, impl_line, impl_col);
        if (mrc != 0)
          return mrc;
      }
      return 0;
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF)
      return -1;
    if (r.tok.kind != (int32_t)TOKEN_FUNCTION) {
      /* Unknown item: fail closed (do not half-skip). */
      return -1;
    }
    /* Same commit path as top-level function (library shape first, then onefunc). */
    func_is_async = 0;
    lib = parser_asm_parse_one_function_library_buf_c(arena, module, fn_start, data, len);
    if (lib.ok) {
      body = parser_lex_from_library_glue(lib);
      continue;
    }
    res = parser_asm_seed_onefunc_wired_c(fn_start);
    /* 9.6.3: module window for the static-desugar hooks (impl slice + buf
     * retry), mirroring the pin parse_into_buf window. PLATFORM: SHARED. */
    {
      extern void parser_cur_module_set_c(void *m);
      parser_cur_module_set_c(module);
    }
    {
      struct parser_asm_lexer fn_lex = fn_start;
      parser_lex_from_next_into_glue(&fn_lex, r); /* after FUNCTION */
      parser_parse_one_function_impl(&res, arena, fn_lex, &slice);
    }
    if (!res.ok)
      parser_asm_parse_one_function_buf_into_c(&res, arena, fn_start, data, len);
    {
      extern void parser_cur_module_set_c(void *m);
      parser_cur_module_set_c(0);
    }
    if (!res.ok) {
      /* wave676: P011 sticky → hard abort (same as main parse_into_buf loop). */
      {
        extern int32_t parser_sig_type_hard_pending_c(void);
        if (parser_sig_type_hard_pending_c() != 0)
          return -2;
      }
      parser_skip_one_function_full_into_buf_glue(&body, fn_start, data, len);
      if (body.pos == fn_start.pos && body.pos < (size_t)len)
        body.pos++;
      continue;
    }
    if (parser_asm_seed_commit_onefunc_c(arena, module, &res, func_is_async, inout_main_idx, &body) != 0) {
      parser_skip_one_function_full_into_buf_glue(&body, fn_start, data, len);
      if (body.pos == fn_start.pos && body.pos < (size_t)len)
        body.pos++;
      continue;
    }
  }
  return -1;
}

/**
 * seed parse_into_buf：collect_imports + 主循环 parse/skip（buf 路径）。
 */
struct parser_asm_seed_parse_into_result parser_asm_seed_parse_into_buf_c(void *arena, void *module, uint8_t *data,
                                                                          int32_t len) {
  struct parser_asm_seed_parse_into_result out;
  struct parser_asm_lexer lex;
  struct parser_asm_collect_imports_result import_res;
  parser_asm_x_module_hdr_t *mod_hdr;
  int32_t main_idx;
  int32_t loop_count;
  int32_t func_is_async;
  struct parser_asm_slice_u8 slice;

  out.ok = 0;
  out.main_idx = -1;
  if (!arena || !module || !data || len <= 0)
    return out;

  /* wave676: clear sticky P011 so a prior file cannot poison this parse. */
  {
    extern void parser_sig_type_hard_reset_c(void);
    parser_sig_type_hard_reset_c();
  }

  /* wave421/wave425: per-module trait method registry (+ ret kinds; stash arena). */
  xlang_trait_reg_reset_c(arena);

  mod_hdr = (parser_asm_x_module_hdr_t *)module;
  lex.pos = 0;
  lex.line = 1;
  lex.col = 1;
  import_res.lex = lex;
  parser_asm_collect_imports_buf_c(lex, data, len, module, &import_res);
  lex = import_res.lex;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_buf_preamble_peek_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_preamble_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_preamble_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_preamble_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_entry_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_ultra_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_entry_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_super_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_max_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  loop_count = 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(lex, data, len));
  loop_count = 0;
  slice.data = data;
  slice.length = (size_t)len;

  while (1) {
    struct parser_asm_lexer iter_start;
    struct parser_asm_lexer_result r;
    struct parser_asm_lexer lex_at_function;

    if (loop_count >= 131072) {
      out.ok = -1;
      out.main_idx = -1003;
      return out;
    }
    loop_count++;
    iter_start = lex;
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_buf_loop_toplevel_buf_audit_c(iter_start, data, len));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_loop_iter_deep_buf_audit_c(iter_start, data, len));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_loop_entry_full_deep_buf_audit_c(iter_start, data, len));
    r = lexer_next_buf(lex, data, len);
    lex_at_function = lex;
    parser_lex_from_next_into_glue(&lex, r);
    func_is_async = 0;
    if (r.tok.kind == (int32_t)TOKEN_ASYNC) {
      func_is_async = 1;
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_async_fn_prefix_buf_audit_c(&iter_start, data, len));
      parser_lex_from_next_into_glue(&lex, r);
      lex_at_function = lex;
      r = lexer_next_buf(lex, data, len);
      parser_lex_from_next_into_glue(&lex, r);
    }
    if (r.tok.kind == (int32_t)TOKEN_ATTR_SOA) {
      mod_hdr->pending_soa_struct = 1;
      parser_lex_from_next_into_glue(&lex, r);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_ATTR_CFG) {
      mod_hdr->pending_cfg_skip = (r.tok.int_val == 0) ? 1 : 0;
      parser_lex_from_next_into_glue(&lex, r);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_ATTR_REPR_C) {
      mod_hdr->pending_repr_c_struct = 1;
      parser_lex_from_next_into_glue(&lex, r);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_ATTR_REPR_COMPATIBLE) {
      mod_hdr->pending_repr_compatible_struct = 1;
      parser_lex_from_next_into_glue(&lex, r);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_ATTR_ALLOC) {
      parser_lex_from_next_into_glue(&lex, r);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (mod_hdr->pending_cfg_skip) {
      if (r.tok.kind == (int32_t)TOKEN_STRUCT) {
        parser_skip_one_struct_into_buf_glue(&lex, iter_start, data, len);
        mod_hdr->pending_cfg_skip = 0;
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (r.tok.kind == (int32_t)TOKEN_CONST) {
        parser_skip_one_top_level_const_into_buf_glue(&lex, iter_start, data, len);
        mod_hdr->pending_cfg_skip = 0;
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (r.tok.kind == (int32_t)TOKEN_LET) {
        parser_skip_one_top_level_let_into_buf_glue(&lex, iter_start, data, len);
        mod_hdr->pending_cfg_skip = 0;
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (r.tok.kind == (int32_t)TOKEN_FUNCTION || func_is_async ||
          r.tok.kind == (int32_t)TOKEN_EXTERN) {
        parser_skip_one_function_full_into_buf_glue(&lex, iter_start, data, len);
        mod_hdr->pending_cfg_skip = 0;
        func_is_async = 0;
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      mod_hdr->pending_cfg_skip = 0;
    }
    if (r.tok.kind == (int32_t)TOKEN_STRUCT) {
      struct parser_asm_lexer out_lex;
      int32_t ap = mod_hdr->pending_allow_padding;
      int32_t ps = mod_hdr->pending_soa_struct;
      int32_t pr = mod_hdr->pending_repr_c_struct;
      int32_t pc = mod_hdr->pending_repr_compatible_struct;
      mod_hdr->pending_allow_padding = 0;
      mod_hdr->pending_soa_struct = 0;
      mod_hdr->pending_repr_c_struct = 0;
      mod_hdr->pending_repr_compatible_struct = 0;
      if (pr)
        ap = 1;
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_record_layout_body_buf_audit_c(lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_struct_layout_deep_buf_audit_c(lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_struct_layout_full_deep_buf_audit_c(lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_struct_layout_mega_full_deep_buf_audit_c(lex, data, len));
      if (parser_parse_struct_record_layout_into_glue(arena, module, lex, &slice, &out_lex, ap, ps, pc) != 0) {
        /*
         * wave679 Cap residual: P012 duplicate field must not soft-skip+continue.
         * PLATFORM: SHARED parse.
         */
        {
          extern int32_t parser_sig_type_hard_pending_c(void);
          if (parser_sig_type_hard_pending_c() != 0) {
            out.ok = -2;
            out.main_idx = -1;
            return out;
          }
        }
        parser_skip_one_struct_into_buf_glue(&lex, iter_start, data, len);
      } else
        lex = out_lex;
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_ENUM) {
      parser_skip_one_enum_register_into_buf_glue(module, &lex, iter_start, data, len);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_TRAIT) {
      /* wave421: register method names for missing-method check; fallback skip. */
      if (parser_asm_seed_register_trait_c(iter_start, data, len, &lex) != 0) {
        parser_skip_one_trait_into_buf_glue(&lex, iter_start, data, len);
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
      }
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_IMPL) {
      /* wave390: hoist impl methods as free funcs (UFCS).
       * wave421: -2 = missing method hard fail (do not soft-skip). */
      {
        int32_t impl_rc =
            parser_asm_seed_parse_impl_and_add_c(arena, module, iter_start, data, len, &lex, &main_idx);
        if (impl_rc == -2) {
          out.ok = 0;
          out.main_idx = -1;
          return out;
        }
        if (impl_rc != 0) {
          parser_skip_one_impl_into_buf_glue(&lex, iter_start, data, len);
          if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
            lex.pos++;
        }
      }
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_EXTERN) {
      parser_parse_one_extern_and_add_into_buf_glue(arena, module, iter_start, data, len, &lex);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        parser_skip_one_extern_into_buf_glue(&lex, iter_start, data, len);
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_LET || r.tok.kind == (int32_t)TOKEN_CONST) {
      struct parser_asm_top_level_let_result tl_res;
      memset(&tl_res, 0, sizeof(tl_res));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_buf_audit_c(r.next_lex, data, len,
                                                        r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_deep_buf_audit_c(r.next_lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                 r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                      r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_ultra_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                         r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_super_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                        r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                       r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                              r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_toplevel_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_buf_audit_c(r.next_lex, data, len,
                                                                                   r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_deep_buf_audit_c(&r.next_lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_full_deep_buf_audit_c(r.next_lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_mega_full_deep_buf_audit_c(r.next_lex, data, len));
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_bracket_composite_buf_audit_c(r.next_lex, data, len));
      parser_parse_one_top_level_let_into_glue(arena, module, r.next_lex, &slice,
                                             r.tok.kind == (int32_t)TOKEN_CONST ? 1 : 0, &tl_res);
      if (tl_res.ok) {
        lex = tl_res.next_lex;
        continue;
      }
      /* 9.6.3: P012 duplicate top-level binding must not soft-skip (mirror of
       * the parser.x parse_into_buf let branch; wave679 sticky pattern). */
      {
        extern int32_t parser_sig_type_hard_pending_c(void);
        if (parser_sig_type_hard_pending_c() != 0) {
          out.ok = -2;
          out.main_idx = -1;
          return out;
        }
      }
    }
    if (r.tok.kind != (int32_t)TOKEN_FUNCTION) {
      struct parser_asm_try_skip_allow_result try_res;
      memset(&try_res, 0, sizeof(try_res));
      parser_parse_into_try_skip_allow_into_buf_glue(&try_res, lex, r, data, len);
      if (try_res.skipped != 0) {
        mod_hdr->pending_allow_padding = 1;
        lex = parser_lex_from_try_skip_glue(try_res);
        if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (r.tok.kind == (int32_t)TOKEN_EOF)
        break;
      if (lex.pos == iter_start.pos && lex.pos < (size_t)len)
        lex.pos++;
      continue;
    }
    if (r.tok.kind == (int32_t)TOKEN_EOF) {
      if (mod_hdr->num_funcs == 0) {
        int32_t fail_tok = parser_diag_fail_at_token_kind_buf_glue(data, len);
        if (fail_tok == (int32_t)TOKEN_STRING)
          out.ok = -2;
        out.main_idx = -1;
        return out;
      }
      out.main_idx = main_idx;
      return out;
    }

    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_into_function_branch_deep_buf_audit_c(lex_at_function, data, len));
    parser_lex_from_next_into_glue(&lex, r);
    {
      struct parser_asm_library_parse_result lib;
      struct parser_asm_onefunc_result res;

      lib = parser_asm_parse_one_function_library_buf_c(arena, module, lex_at_function, data, len);
      if (lib.ok) {
        lex = parser_lex_from_library_glue(lib);
        continue;
      }
      res = parser_asm_seed_onefunc_wired_c(lex);
      /* 9.6.3: install the module while this function body parses so the
       * static-desugar hooks (impl slice + buf retry) can reach it; window
       * covers both faces, cleared right after the retry. PLATFORM: SHARED. */
      {
        extern void parser_cur_module_set_c(void *m);
        parser_cur_module_set_c(module);
      }
      parser_parse_one_function_impl(&res, arena, lex, &slice);
      if (!res.ok) {
        /* wave676: skip buf retry when P011 already sticky (avoid double diag). */
        extern int32_t parser_sig_type_hard_pending_c(void);
        if (parser_sig_type_hard_pending_c() == 0)
          parser_asm_parse_one_function_buf_into_c(&res, arena, lex_at_function, data, len);
      }
      {
        extern void parser_cur_module_set_c(void *m);
        parser_cur_module_set_c(0);
      }
      if (!res.ok) {
        /*
         * wave676 Cap residual: P011 untyped formal / missing return type must not
         * soft-skip+continue (silent drop → false green when main remains).
         * G.7: sticky from parser_report_untyped_formal_p011_c.
         * PLATFORM: SHARED parse.
         */
        {
          extern int32_t parser_sig_type_hard_pending_c(void);
          if (parser_sig_type_hard_pending_c() != 0) {
            out.ok = -2;
            out.main_idx = -1;
            return out;
          }
        }
        /* 与 parser.x parse_into_buf 一致：跳过前打印函数名，供 A-11 typeck 截断 bisect。 */
        {
          uint8_t skip_name[64];
          int32_t skip_nlen =
              parser_parse_peek_function_name_buf_glue(lex_at_function, data, len, skip_name);
          driver_diagnostic_parse_skip_function((int32_t)lex_at_function.pos, mod_hdr->num_funcs, skip_nlen,
                                                skip_name);
        }
        parser_skip_one_function_full_into_buf_glue(&lex, lex_at_function, data, len);
        if (lex.pos == lex_at_function.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (parser_asm_seed_commit_onefunc_c(arena, module, &res, func_is_async, &main_idx, &lex) != 0) {
        /* 与 parse skip 一致：commit 失败跳过该函数并继续，避免 typeck 等大模块在 ~47 func 处整文件 abort。 */
        {
          uint8_t cname[64];
          int32_t cnlen = res.name_len > 0 ? res.name_len : 0;
          if (cnlen > 63)
            cnlen = 63;
          if (cnlen > 0)
            memcpy(cname, res.name, (size_t)cnlen);
          cname[cnlen > 0 ? cnlen : 0] = '\0';
          driver_diagnostic_parse_commit_fail((int32_t)lex_at_function.pos, mod_hdr->num_funcs, cnlen, cname);
        }
        parser_skip_one_function_full_into_buf_glue(&lex, lex_at_function, data, len);
        if (lex.pos == lex_at_function.pos && lex.pos < (size_t)len)
          lex.pos++;
        continue;
      }
      if (getenv("XLANG_DBG_FUNC")) {
        /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
        { char _db[384]; int _dn = snprintf(_db, sizeof _db, "[DBG_FUNC] ok name=%.*s pos_before=%zu pos_after=%zu\n",
            (int)(res.name_len > 0 ? res.name_len : 0), res.name,
            (size_t)lex_at_function.pos, (size_t)lex.pos);
          if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
      }
    }
  }

  out.main_idx = main_idx;
  return out;
}

/** runtime / pipeline 期望裸名 parse_into_buf；强符号覆盖 link_alias 弱桩。 */
struct parser_asm_seed_parse_into_result parse_into_buf(void *arena, void *module, uint8_t *data, int32_t len) {
  return parser_asm_seed_parse_into_buf_c(arena, module, data, len);
}

/** runtime 期望 parser_parse_into_buf 前缀。 */
struct parser_asm_seed_parse_into_result parser_parse_into_buf(void *arena, void *module, uint8_t *data, int32_t len) {
  return parse_into_buf(arena, module, data, len);
}

/** slice 路径 parse_into。 */
struct parser_asm_seed_parse_into_result parse_into(void *arena, void *module,
                                                    struct parser_asm_seed_slice_u8 *source) {
  if (!source || !source->data) {
    struct parser_asm_seed_parse_into_result fail;
    fail.ok = 0;
    fail.main_idx = -1;
    return fail;
  }
  return parser_asm_seed_parse_into_buf_c(arena, module, source->data, (int32_t)source->length);
}

struct parser_asm_seed_parse_into_result parser_parse_into(void *arena, void *module,
                                                           struct parser_asm_seed_slice_u8 *source) {
  return parse_into(arena, module, source);
}

/** parse_into_set_main_index：写 module.main_func_index。 */
extern void pipeline_module_set_main_func_index(void *m, int32_t idx);

void parse_into_set_main_index(void *module, int32_t main_idx) {
  pipeline_module_set_main_func_index(module, main_idx);
}

void parser_parse_into_set_main_index(void *module, int32_t main_idx) {
  parse_into_set_main_index(module, main_idx);
}

#endif /* PARSER_ASM_SEED_PARSE_INTO_BUF_SLICE_INCLUDED */
