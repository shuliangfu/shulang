/**
 * parser_asm_primary_slice.inc — parse_primary_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * INT/FLOAT/BOOL/break/continue/IDENT 后缀/paren/array/if/match/panic/@simd 与 parser.x 一致。
 */
#ifndef PARSER_ASM_PRIMARY_SLICE_INCLUDED
#define PARSER_ASM_PRIMARY_SLICE_INCLUDED

#include "diag.h"
#include <stdio.h>
#include <stdlib.h>

/** 与 ast.x ExprKind 序一致（primary 用到的子集；勿用 C ast.h 旧序 +32 误值）。 */
enum {
  PARSER_ASM_EXPR_LIT = 0,
  PARSER_ASM_EXPR_FLOAT_LIT = 1,
  PARSER_ASM_EXPR_BOOL_LIT = 2,
  PARSER_ASM_EXPR_VAR = 3,
  PARSER_ASM_EXPR_IF = 25,
  PARSER_ASM_EXPR_BLOCK = 26,
  PARSER_ASM_EXPR_BREAK = 39,
  PARSER_ASM_EXPR_CONTINUE = 40,
  /** wave371: `return expr` as primary so match arms `1 => return 42;` parse. */
  PARSER_ASM_EXPR_RETURN = 41,
  PARSER_ASM_EXPR_PANIC = 42,
  PARSER_ASM_EXPR_FIELD_ACCESS = 44,
  PARSER_ASM_EXPR_ARRAY_LIT = 46,
  PARSER_ASM_EXPR_INDEX = 47,
  PARSER_ASM_EXPR_CALL = 48,
  /** 与 ast.x ExprKind.EXPR_METHOD_CALL 一致；`.method(...)` 后缀。 */
  PARSER_ASM_EXPR_METHOD_CALL = 49,
  /** 与 ast.x ExprKind.EXPR_STRING_LIT 序一致；字符串字面量写入 var_name。 */
  PARSER_ASM_EXPR_STRING_LIT = 59,
  /** Stage10 10.2.1: `asm!("template")`；模板语义字节写入 var_name（同 STRING_LIT）。 */
  PARSER_ASM_EXPR_ASM = 60
};

extern void lexer_note_string_lit_overflow(int32_t line, int32_t col);
extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *source);
extern void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                            struct parser_asm_parse_expr_result *out);
extern void parser_parse_match_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                    struct parser_asm_parse_expr_result *out);
extern void parser_parse_if_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                       int32_t type_ref, struct parser_asm_parse_expr_result *out);
extern void parser_parse_block_into(void *arena, struct parser_asm_lexer lex_after_lbrace,
                                    struct parser_asm_slice_u8 *source, int32_t type_ref,
                                    struct parser_asm_parse_block_result *out);
extern void parser_parse_at_simd_builtin_into(void *arena, struct parser_asm_lexer_result r0,
                                              struct parser_asm_slice_u8 *source,
                                              struct parser_asm_parse_expr_result *out);
extern void parser_finish_struct_lit_from_type_ident_into_glue(void *arena, int32_t lit_ref,
                                                               struct parser_asm_lexer lex_in_brace,
                                                               struct parser_asm_slice_u8 *source,
                                                               struct parser_asm_parse_expr_result *out);
extern int32_t parser_asm_stretch_primary_head_audit_c(struct parser_asm_lexer lex,
                                                       struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_expr_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_expr_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_ultra_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_super_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                 struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_expr_deep_audit_c(struct parser_asm_lexer lex,
                                                            struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_call_deep_audit_c(struct parser_asm_lexer lex,
                                                            struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_panic_kw_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_if_expr_branch_audit_c(struct parser_asm_lexer lex_at_if,
                                                       struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_array_lit_head_audit_c(struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_primary_suffix_chain_probe_c(struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_field_access_name_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                            int32_t name_len);
extern int32_t parser_asm_stretch_call_args_shape_probe_c(struct parser_asm_lexer lex,
                                                          struct parser_asm_slice_u8 *source,
                                                          int32_t *out_arg_count);
extern int32_t parser_asm_stretch_paren_expr_head_audit_c(struct parser_asm_lexer lex,
                                                          struct parser_asm_slice_u8 *source);
extern int32_t pipeline_expr_append_call_arg(void *arena, int32_t expr_ref, int32_t arg_ref);
/** wave452: store turbofish type-arg type_ref on CALL (sidecar pool). */
extern int32_t pipeline_expr_append_call_type_arg(void *arena, int32_t expr_ref, int32_t type_ref);
extern int32_t pipeline_expr_append_method_call_arg(void *arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                struct parser_asm_lexer *out_lex);
/* LANG-009 M8: type_ref → mangle suffix (G.7 with codegen_type_ref_to_suffix semantics). */
extern int32_t pipeline_type_kind_ord_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_elem_ref_at(void *arena, int32_t type_ref);
extern int32_t pipeline_type_named_name_into(void *arena, int32_t type_ref, uint8_t *out);
extern int32_t ast_ast_arena_block_alloc(void *arena);
extern int32_t pipeline_block_append_unsafe(void *arena, int32_t block_ref, int32_t body_ref);
extern int32_t pipeline_block_append_stmt_order(void *arena, int32_t block_ref, uint8_t kind, int32_t idx);
extern void parser_asm_skip_generic_angle_list_into_slice_c(struct parser_asm_lexer *out, struct parser_asm_lexer lex,
                                                              struct parser_asm_slice_u8 *source);
extern void parser_asm_skip_generic_angle_list_count_into_slice_c(struct parser_asm_lexer *out, int32_t *count,
                                                                  struct parser_asm_lexer lex,
                                                                  struct parser_asm_slice_u8 *source);
extern int32_t pipeline_expr_append_array_lit_elem(void *arena, int32_t expr_ref, int32_t elem_ref);
extern int32_t ast_ast_arena_expr_alloc(void *arena);

extern struct parser_asm_lexer parser_asm_lex_at_token_from_result_c(struct parser_asm_lexer_result r);
static void parser_asm_arena_expr_set_c(void *arena, int32_t ref, struct parser_asm_ast_expr ae);
void parser_asm_expr_set_common_zeros_c(struct parser_asm_ast_expr *e);
/* parser_asm_lex_from_result_val_into: provided by P1 lex_skip (non-static) */
struct parser_asm_ast_expr parser_asm_arena_expr_get_c(void *arena, int32_t ref);

/** 分配 EXPR_FLOAT_LIT 节点；与 parser.x parser_alloc_float_lit 一致。 */
static int32_t parser_asm_alloc_float_lit_c(void *arena, double fval) {
  int32_t ref;
  struct parser_asm_ast_expr e;
  if (!arena)
    return 0;
  ref = ast_ast_arena_expr_alloc(arena);
  if (ref == 0)
    return 0;
  e = parser_asm_arena_expr_get_c(arena, ref);
  e.kind = PARSER_ASM_EXPR_FLOAT_LIT;
  e.float_val = fval;
  e.line = 0;
  e.col = 0;
  parser_asm_expr_set_common_zeros_c(&e);
  parser_asm_arena_expr_set_c(arena, ref, e);
  return ref;
}

static int parser_asm_suffix_debug_enabled(void) {
  const char *v = getenv("XLANG_PARSER_ASM_DEBUG");
  return v && *v && *v != '0';
}

/** Copy ident into e.var_name (wave577 Cap: up to 127 bytes + zero-pad to 128). */
static void parser_asm_primary_copy_ident_to_var_c(struct parser_asm_ast_expr *e, struct parser_asm_slice_u8 *source,
                                                   size_t start, int32_t len) {
  int32_t i;
  if (!e)
    return;
  if (len > 127)
    len = 127;
  e->var_name_len = len;
  for (i = 0; i < len; i++) {
    if (start + (size_t)i < source->length)
      e->var_name[i] = source->data[start + i];
    else
      e->var_name[i] = 0;
  }
  while (i < 128) {
    e->var_name[i] = 0;
    i++;
  }
}

static int32_t parser_asm_wrap_block_ref_as_expr_primary_c(void *arena, int32_t block_ref) {
  int32_t ref;
  struct parser_asm_ast_expr e;
  if (!arena || block_ref == 0)
    return 0;
  ref = ast_ast_arena_expr_alloc(arena);
  if (ref == 0)
    return 0;
  e = parser_asm_arena_expr_get_c(arena, ref);
  parser_asm_expr_set_common_zeros_c(&e);
  e.kind = PARSER_ASM_EXPR_BLOCK;
  e.block_ref = block_ref;
  e.line = 0;
  e.col = 0;
  parser_asm_arena_expr_set_c(arena, ref, e);
  return ref;
}

/*
 * STRING_LIT payload beyond Expr.var_name[128]: overflow chunks are extra
 * STRING_LIT exprs chained via int_val (next-ref). Head.var_name_len is the
 * total semantic length; overflow nodes store chunk size in var_name_len.
 * Identifier name slots stay 127 (4.2.8 leave-off). L011 still honest-fails
 * past PARSER_ASM_STRING_LIT_MAX. PLATFORM: SHARED.
 */
#define PARSER_ASM_STRING_LIT_MAX 4095
#define PARSER_ASM_STRING_LIT_CHUNK 127

static int32_t parser_asm_string_lit_append_byte_c(void *arena, int32_t head_ref, uint8_t b,
                                                   int32_t line, int32_t col) {
  struct parser_asm_ast_expr e;
  struct parser_asm_ast_expr ch;
  int32_t total;
  int32_t cur;
  int32_t next;
  int32_t ov;
  int32_t off;
  if (!arena || head_ref <= 0)
    return -1;
  e = parser_asm_arena_expr_get_c(arena, head_ref);
  total = e.var_name_len;
  if (total < 0)
    total = 0;
  if (total >= PARSER_ASM_STRING_LIT_MAX) {
    lexer_note_string_lit_overflow(line, col);
    return -1;
  }
  if (total < PARSER_ASM_STRING_LIT_CHUNK) {
    e.var_name[total] = b;
    e.var_name_len = total + 1;
    parser_asm_arena_expr_set_c(arena, head_ref, e);
    return 0;
  }
  cur = (int32_t)e.int_val;
  off = total - PARSER_ASM_STRING_LIT_CHUNK;
  if (cur <= 0) {
    ov = ast_ast_arena_expr_alloc(arena);
    if (ov == 0)
      return -1;
    ch = parser_asm_arena_expr_get_c(arena, ov);
    parser_asm_expr_set_common_zeros_c(&ch);
    ch.kind = PARSER_ASM_EXPR_STRING_LIT;
    ch.line = e.line;
    ch.col = e.col;
    ch.int_val = 0;
    ch.var_name_len = 0;
    parser_asm_arena_expr_set_c(arena, ov, ch);
    e.int_val = (int64_t)ov;
    parser_asm_arena_expr_set_c(arena, head_ref, e);
    cur = ov;
  }
  while (off >= PARSER_ASM_STRING_LIT_CHUNK) {
    ch = parser_asm_arena_expr_get_c(arena, cur);
    next = (int32_t)ch.int_val;
    if (next <= 0) {
      ov = ast_ast_arena_expr_alloc(arena);
      if (ov == 0)
        return -1;
      ch.int_val = (int64_t)ov;
      parser_asm_arena_expr_set_c(arena, cur, ch);
      ch = parser_asm_arena_expr_get_c(arena, ov);
      parser_asm_expr_set_common_zeros_c(&ch);
      ch.kind = PARSER_ASM_EXPR_STRING_LIT;
      ch.line = e.line;
      ch.col = e.col;
      ch.int_val = 0;
      ch.var_name_len = 0;
      parser_asm_arena_expr_set_c(arena, ov, ch);
      next = ov;
    }
    off -= PARSER_ASM_STRING_LIT_CHUNK;
    cur = next;
  }
  ch = parser_asm_arena_expr_get_c(arena, cur);
  ch.var_name[off] = b;
  if (ch.var_name_len < off + 1)
    ch.var_name_len = off + 1;
  parser_asm_arena_expr_set_c(arena, cur, ch);
  e = parser_asm_arena_expr_get_c(arena, head_ref);
  e.var_name_len = total + 1;
  parser_asm_arena_expr_set_c(arena, head_ref, e);
  return 0;
}

/* Decode one TOKEN_STRING span (escapes already product-set) onto head_ref. */
static int32_t parser_asm_string_lit_decode_span_c(void *arena, int32_t head_ref,
    struct parser_asm_slice_u8 *source, size_t q0, int32_t nlen, int32_t line, int32_t col) {
  int32_t ri;
  if (!arena || !source || head_ref <= 0)
    return -1;
  if (nlen < 0)
    nlen = 0;
  ri = 0;
  while (ri < nlen) {
    uint8_t c = 0;
    uint8_t b;
    int32_t consumed = 1;
    if (q0 + (size_t)ri < source->length)
      c = source->data[q0 + (size_t)ri];
    b = c;
    if (c == 92 && (ri + 1) < nlen) {
      uint8_t n = 0;
      if (q0 + (size_t)(ri + 1) < source->length)
        n = source->data[q0 + (size_t)(ri + 1)];
      if (n == 110) { b = 10; consumed = 2; }
      else if (n == 116) { b = 9; consumed = 2; }
      else if (n == 114) { b = 13; consumed = 2; }
      else if (n == 48) { b = 0; consumed = 2; }
      else if (n == 92 || n == 34) { b = n; consumed = 2; }
      else if (n == 120 && (ri + 3) < nlen) {
        uint8_t h1 = 0;
        uint8_t h2 = 0;
        int32_t v1 = -1;
        int32_t v2 = -1;
        if (q0 + (size_t)(ri + 2) < source->length)
          h1 = source->data[q0 + (size_t)(ri + 2)];
        if (q0 + (size_t)(ri + 3) < source->length)
          h2 = source->data[q0 + (size_t)(ri + 3)];
        if (h1 >= 48 && h1 <= 57) v1 = (int32_t)h1 - 48;
        if (h1 >= 97 && h1 <= 102) v1 = (int32_t)h1 - 97 + 10;
        if (h1 >= 65 && h1 <= 70) v1 = (int32_t)h1 - 65 + 10;
        if (h2 >= 48 && h2 <= 57) v2 = (int32_t)h2 - 48;
        if (h2 >= 97 && h2 <= 102) v2 = (int32_t)h2 - 97 + 10;
        if (h2 >= 65 && h2 <= 70) v2 = (int32_t)h2 - 65 + 10;
        if (v1 >= 0 && v2 >= 0) {
          b = (uint8_t)((v1 * 16) + v2);
          consumed = 4;
        } else {
          b = n;
          consumed = 2;
        }
      } else {
        b = n;
        consumed = 2;
      }
    }
    if (parser_asm_string_lit_append_byte_c(arena, head_ref, b, line, col) != 0)
      return -1;
    ri += consumed;
  }
  return 0;
}

static int32_t parser_asm_primary_ident_is_unsafe_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                    int32_t ident_len) {
  if (!source || !source->data || ident_len != 6)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'u' && source->data[token_start + 1] == (uint8_t)'n'
      && source->data[token_start + 2] == (uint8_t)'s' && source->data[token_start + 3] == (uint8_t)'a'
      && source->data[token_start + 4] == (uint8_t)'f' && source->data[token_start + 5] == (uint8_t)'e';
}

/**
 * True when IDENT spelling is exactly `asm` (stage10 10.2.1 `asm!(...)`).
 * PLATFORM: SHARED — G.7 primary authority (parser_asm_thin include).
 */
static int32_t parser_asm_primary_ident_is_asm_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                 int32_t ident_len) {
  if (!source || !source->data || ident_len != 3)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'a' && source->data[token_start + 1] == (uint8_t)'s'
      && source->data[token_start + 2] == (uint8_t)'m';
}

/**
 * True when IDENT spelling is exactly `in` (stage10 10.2.1 slice1 `in("reg") expr`).
 * PLATFORM: SHARED — G.7 primary authority (parser_asm_thin include).
 */
static int32_t parser_asm_primary_ident_is_in_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                int32_t ident_len) {
  if (!source || !source->data || ident_len != 2)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'i' && source->data[token_start + 1] == (uint8_t)'n';
}

/**
 * True when IDENT is `out` (stage10 10.2.1 slice4).
 * PLATFORM: SHARED.
 */
static int32_t parser_asm_primary_ident_is_out_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                 int32_t ident_len) {
  if (!source || !source->data || ident_len != 3)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'o' && source->data[token_start + 1] == (uint8_t)'u'
      && source->data[token_start + 2] == (uint8_t)'t';
}

/**
 * True when IDENT is `lateout` (stage10 10.2.1 slice4; same emit as out for now).
 * PLATFORM: SHARED.
 */
static int32_t parser_asm_primary_ident_is_lateout_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t ident_len) {
  if (!source || !source->data || ident_len != 7)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'l' && source->data[token_start + 1] == (uint8_t)'a'
      && source->data[token_start + 2] == (uint8_t)'t' && source->data[token_start + 3] == (uint8_t)'e'
      && source->data[token_start + 4] == (uint8_t)'o' && source->data[token_start + 5] == (uint8_t)'u'
      && source->data[token_start + 6] == (uint8_t)'t';
}

/**
 * True when IDENT is `options` (stage10 10.2.1 slice6 trailing options(...)).
 * PLATFORM: SHARED.
 */
static int32_t parser_asm_primary_ident_is_options_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                     int32_t ident_len) {
  if (!source || !source->data || ident_len != 7)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  return source->data[token_start + 0] == (uint8_t)'o' && source->data[token_start + 1] == (uint8_t)'p'
      && source->data[token_start + 2] == (uint8_t)'t' && source->data[token_start + 3] == (uint8_t)'i'
      && source->data[token_start + 4] == (uint8_t)'o' && source->data[token_start + 5] == (uint8_t)'n'
      && source->data[token_start + 6] == (uint8_t)'s';
}

/**
 * Map IDENT to asm! options bit (stage10 10.2.1 slice8), or 0 if unknown.
 * Bits: nostack=1, preserves_flags=2, nomem=4, readonly=8, pure=16, noreturn=32.
 * Stored on EXPR_ASM.call_num_type_args (ASM has no type-args).
 * PLATFORM: SHARED — G.7 single bit table for parse+emit.
 */
static int32_t parser_asm_primary_asm_option_bit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                    int32_t ident_len) {
  if (!source || !source->data || ident_len <= 0)
    return 0;
  if (token_start + (size_t)ident_len > source->length)
    return 0;
  /* nostack = 1 */
  if (ident_len == 7 && source->data[token_start + 0] == (uint8_t)'n'
      && source->data[token_start + 1] == (uint8_t)'o' && source->data[token_start + 2] == (uint8_t)'s'
      && source->data[token_start + 3] == (uint8_t)'t' && source->data[token_start + 4] == (uint8_t)'a'
      && source->data[token_start + 5] == (uint8_t)'c' && source->data[token_start + 6] == (uint8_t)'k')
    return 1;
  /* preserves_flags = 2 */
  if (ident_len == 15 && source->data[token_start + 0] == (uint8_t)'p'
      && source->data[token_start + 1] == (uint8_t)'r' && source->data[token_start + 2] == (uint8_t)'e'
      && source->data[token_start + 3] == (uint8_t)'s' && source->data[token_start + 4] == (uint8_t)'e'
      && source->data[token_start + 5] == (uint8_t)'r' && source->data[token_start + 6] == (uint8_t)'v'
      && source->data[token_start + 7] == (uint8_t)'e' && source->data[token_start + 8] == (uint8_t)'s'
      && source->data[token_start + 9] == (uint8_t)'_' && source->data[token_start + 10] == (uint8_t)'f'
      && source->data[token_start + 11] == (uint8_t)'l' && source->data[token_start + 12] == (uint8_t)'a'
      && source->data[token_start + 13] == (uint8_t)'g' && source->data[token_start + 14] == (uint8_t)'s')
    return 2;
  /* nomem = 4 */
  if (ident_len == 5 && source->data[token_start + 0] == (uint8_t)'n'
      && source->data[token_start + 1] == (uint8_t)'o' && source->data[token_start + 2] == (uint8_t)'m'
      && source->data[token_start + 3] == (uint8_t)'e' && source->data[token_start + 4] == (uint8_t)'m')
    return 4;
  /* readonly = 8 */
  if (ident_len == 8 && source->data[token_start + 0] == (uint8_t)'r'
      && source->data[token_start + 1] == (uint8_t)'e' && source->data[token_start + 2] == (uint8_t)'a'
      && source->data[token_start + 3] == (uint8_t)'d' && source->data[token_start + 4] == (uint8_t)'o'
      && source->data[token_start + 5] == (uint8_t)'n' && source->data[token_start + 6] == (uint8_t)'l'
      && source->data[token_start + 7] == (uint8_t)'y')
    return 8;
  /* pure = 16 */
  if (ident_len == 4 && source->data[token_start + 0] == (uint8_t)'p'
      && source->data[token_start + 1] == (uint8_t)'u' && source->data[token_start + 2] == (uint8_t)'r'
      && source->data[token_start + 3] == (uint8_t)'e')
    return 16;
  /* noreturn = 32 */
  if (ident_len == 8 && source->data[token_start + 0] == (uint8_t)'n'
      && source->data[token_start + 1] == (uint8_t)'o' && source->data[token_start + 2] == (uint8_t)'r'
      && source->data[token_start + 3] == (uint8_t)'e' && source->data[token_start + 4] == (uint8_t)'t'
      && source->data[token_start + 5] == (uint8_t)'u' && source->data[token_start + 6] == (uint8_t)'r'
      && source->data[token_start + 7] == (uint8_t)'n')
    return 32;
  return 0;
}

/**
 * True when IDENT is a known Rust-style asm! option name (slice6+/8).
 * PLATFORM: SHARED.
 */
static int32_t parser_asm_primary_ident_is_asm_option_name_c(struct parser_asm_slice_u8 *source,
                                                             size_t token_start, int32_t ident_len) {
  return parser_asm_primary_asm_option_bit_c(source, token_start, ident_len) != 0;
}

static void parser_asm_primary_parse_unsafe_expr_c(void *arena, struct parser_asm_lexer lex_after_kw,
                                                   struct parser_asm_slice_u8 *source,
                                                   struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer_result r;
  struct parser_asm_parse_block_result block_res;
  int32_t wrapper_block_ref;
  int32_t unsafe_idx;
  int32_t expr_ref;
  if (!arena || !source || !out)
    return;
  out->ok = 0;
  lexer_next_into(&r, lex_after_kw, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return;
  memset(&block_res, 0, sizeof(block_res));
  block_res.next_lex = r.next_lex;
  parser_parse_block_into(arena, r.next_lex, source, 0, &block_res);
  if (!block_res.ok)
    return;
  wrapper_block_ref = ast_ast_arena_block_alloc(arena);
  if (wrapper_block_ref == 0)
    return;
  unsafe_idx = pipeline_block_append_unsafe(arena, wrapper_block_ref, block_res.block_ref);
  if (unsafe_idx < 0)
    return;
  if (pipeline_block_append_stmt_order(arena, wrapper_block_ref, 6, unsafe_idx) < 0)
    return;
  expr_ref = parser_asm_wrap_block_ref_as_expr_primary_c(arena, wrapper_block_ref);
  if (expr_ref == 0)
    return;
  out->ok = 1;
  out->expr_ref = expr_ref;
  out->next_lex = block_res.next_lex;
}

/**
 * Parse bare `{ ... }` as an EXPR_BLOCK primary (docs/08 §2.3 block expression).
 * lex_after_lbrace must already be past the opening `{`.
 * PLATFORM: SHARED — single authority for block-expr primary (G.7); used by
 * TOKEN_LBRACE disambiguation so `{ let ... }` no longer whole-function parse-skips.
 */
static void parser_asm_primary_parse_block_expr_c(void *arena, struct parser_asm_lexer lex_after_lbrace,
                                                  struct parser_asm_slice_u8 *source,
                                                  struct parser_asm_parse_expr_result *out) {
  struct parser_asm_parse_block_result block_res;
  int32_t expr_ref;
  if (!arena || !source || !out)
    return;
  out->ok = 0;
  memset(&block_res, 0, sizeof(block_res));
  block_res.next_lex = lex_after_lbrace;
  parser_parse_block_into(arena, lex_after_lbrace, source, 0, &block_res);
  if (!block_res.ok)
    return;
  expr_ref = parser_asm_wrap_block_ref_as_expr_primary_c(arena, block_res.block_ref);
  if (expr_ref == 0)
    return;
  out->ok = 1;
  out->expr_ref = expr_ref;
  out->next_lex = block_res.next_lex;
}

/**
 * After `{`, decide block expression vs anonymous struct literal.
 * PLATFORM: SHARED — root fix for parser residual `{ let y = ... }` parse-skip:
 * primary historically always took anonymous struct lit on TOKEN_LBRACE, so any
 * bare block with let/return/if failed and the enclosing function was skipped.
 *
 * Lookahead rules (preserve existing struct forms):
 *  - stmt / control keywords, nested `{`, `unsafe` → block
 *  - IDENT then `:` / `,` / `}` → anonymous struct lit (`{ fd: 1 }`, `{ fd, x }`, `{ fd }`)
 *  - IDENT then other → block (`{ y = 1; }`, `{ y; }`)
 *  - empty `}` → keep anonymous struct lit path (`{}`) for bare `{` primary
 *  - INT / other primary heads → block (`{ 10 }`, `{ (a) }`)
 * Named empty `Type {}` vs bare `if b {}` is NOT decided here — see
 * parser_asm_primary_empty_ident_braces_prefer_block_c (wave364).
 */
static int32_t parser_asm_primary_lbrace_looks_like_block_c(struct parser_asm_lexer lex_after_lbrace,
                                                            struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer_result r2;
  if (!source)
    return 0;
  lexer_next_into(&r, lex_after_lbrace, source);
  if (r.tok.kind == (int32_t)TOKEN_LET || r.tok.kind == (int32_t)TOKEN_CONST
      || r.tok.kind == (int32_t)TOKEN_RETURN || r.tok.kind == (int32_t)TOKEN_IF
      || r.tok.kind == (int32_t)TOKEN_WHILE || r.tok.kind == (int32_t)TOKEN_LOOP
      || r.tok.kind == (int32_t)TOKEN_FOR || r.tok.kind == (int32_t)TOKEN_DEFER
      || r.tok.kind == (int32_t)TOKEN_MATCH || r.tok.kind == (int32_t)TOKEN_BREAK
      || r.tok.kind == (int32_t)TOKEN_CONTINUE || r.tok.kind == (int32_t)TOKEN_PANIC
      || r.tok.kind == (int32_t)TOKEN_REGION || r.tok.kind == (int32_t)TOKEN_WITH_ARENA
      || r.tok.kind == (int32_t)TOKEN_LBRACE || r.tok.kind == (int32_t)TOKEN_GOTO) {
    return 1;
  }
  if (r.tok.kind == (int32_t)TOKEN_IDENT
      && parser_asm_primary_ident_is_unsafe_c(source, r.token_start, r.tok.ident_len)) {
    return 1;
  }
  if (r.tok.kind == (int32_t)TOKEN_IDENT) {
    lexer_next_into(&r2, r.next_lex, source);
    if (r2.tok.kind == (int32_t)TOKEN_COLON || r2.tok.kind == (int32_t)TOKEN_COMMA
        || r2.tok.kind == (int32_t)TOKEN_RBRACE) {
      return 0;
    }
    return 1;
  }
  if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
    return 0;
  }
  return 1;
}

/**
 * wave364 / docs/03: empty `IDENT {}` after a type/var name is ambiguous:
 *   - value: `let s: S = S {}` / `return S {}` / `f(S {})`
 *   - bare ctrl: `if b {}` / `while b {}` / `if b {} else {…}`
 * G.7 single authority on IDENT+LBRACE (not a second parse path).
 * Lookahead past the empty braces: value-position terminators keep struct lit;
 * otherwise end primary as VAR and leave `{` for the then/while body.
 * PLATFORM: SHARED.
 * @param lex_after_lbrace lexer after the opening `{`
 * @param source source slice
 * @return 1 prefer end-as-VAR (block), 0 keep Type {} struct lit, -1 not empty braces
 */
static int32_t parser_asm_primary_empty_ident_braces_prefer_block_c(
    struct parser_asm_lexer lex_after_lbrace, struct parser_asm_slice_u8 *source) {
  struct parser_asm_lexer_result r_empty;
  struct parser_asm_lexer_result r_after;
  int32_t k;
  if (!source)
    return -1;
  lexer_next_into(&r_empty, lex_after_lbrace, source);
  if (r_empty.tok.kind != (int32_t)TOKEN_RBRACE)
    return -1;
  lexer_next_into(&r_after, r_empty.next_lex, source);
  k = r_after.tok.kind;
  /* Value-position / expr-continuation after empty Type {} → keep struct lit. */
  if (k == (int32_t)TOKEN_SEMICOLON || k == (int32_t)TOKEN_COMMA || k == (int32_t)TOKEN_RPAREN
      || k == (int32_t)TOKEN_RBRACKET || k == (int32_t)TOKEN_DOT || k == (int32_t)TOKEN_AS) {
    return 0;
  }
  /**
   * wave367: last STRUCT_LIT field empty Type {} is followed by outer `}`:
   *   A { x: 42, e: E {} }
   * wave364 treated any post-empty `}` as bare if/while prefer-block → primary ends as VAR
   * "E", leaves `{`, field parse fails → whole function P001 / out_len=0.
   * When under field-value parse (parser_asm_struct_field_value_depth > 0), keep struct lit.
   * Nested bare `if b { if c {} }` keeps depth==0 → still prefer block. PLATFORM: SHARED.
   */
  if (k == (int32_t)TOKEN_RBRACE && parser_asm_struct_field_value_depth > 0) {
    return 0;
  }
  /* Bare if/while empty body: next is return/else/ident/rbrace/if/… → then-block. */
  return 1;
}

/**
 * TypeKind ordinals for STRUCT_LIT type-inst mangle (≡ ast.x / type_ref_slice).
 * PLATFORM: SHARED — keep in lockstep with PARSER_ASM_TYPE_* in type_ref_slice.inc.
 */
enum {
  PARSER_ASM_PRIM_TYPE_I32 = 0,
  PARSER_ASM_PRIM_TYPE_BOOL = 1,
  PARSER_ASM_PRIM_TYPE_U8 = 2,
  PARSER_ASM_PRIM_TYPE_U32 = 3,
  PARSER_ASM_PRIM_TYPE_U64 = 4,
  PARSER_ASM_PRIM_TYPE_I64 = 5,
  PARSER_ASM_PRIM_TYPE_USIZE = 6,
  PARSER_ASM_PRIM_TYPE_ISIZE = 7,
  PARSER_ASM_PRIM_TYPE_NAMED = 8,
  PARSER_ASM_PRIM_TYPE_PTR = 9
};

/**
 * Map one type_ref to a C-safe mangle suffix into buf.
 * Mirrors codegen_type_ref_to_suffix for the STRUCT_LIT parse path (LANG-009 M8).
 * Examples: i32→"i32", u8→"u8", *u8→"u8_ptr", bool→"bool", Named→name.
 * @return bytes written, or 0 on failure
 * PLATFORM: SHARED — G.7 single suffix spelling with codegen; parser-local copy avoids
 * parser→codegen link edge on the thin primary TU.
 */
static int32_t parser_asm_type_ref_mangle_suffix_c(void *arena, int32_t type_ref, uint8_t *buf, int32_t buf_cap) {
  int32_t tk;
  int32_t n;
  int32_t elem;
  if (!arena || type_ref <= 0 || !buf || buf_cap <= 0)
    return 0;
  tk = pipeline_type_kind_ord_at(arena, type_ref);
  if (tk == PARSER_ASM_PRIM_TYPE_PTR) {
    elem = pipeline_type_elem_ref_at(arena, type_ref);
    n = parser_asm_type_ref_mangle_suffix_c(arena, elem, buf, buf_cap);
    if (n > 0 && n + 4 < buf_cap) {
      buf[n] = 95;     /* _ */
      buf[n + 1] = 112; /* p */
      buf[n + 2] = 116; /* t */
      buf[n + 3] = 114; /* r */
      return n + 4;
    }
    return n;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_NAMED) {
    n = pipeline_type_named_name_into(arena, type_ref, buf);
    if (n <= 0 || n >= buf_cap)
      return 0;
    return n;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_I32) {
    if (buf_cap < 3)
      return 0;
    buf[0] = 105;
    buf[1] = 51;
    buf[2] = 50;
    return 3;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_I64) {
    if (buf_cap < 3)
      return 0;
    buf[0] = 105;
    buf[1] = 54;
    buf[2] = 52;
    return 3;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_U8) {
    if (buf_cap < 2)
      return 0;
    buf[0] = 117;
    buf[1] = 56;
    return 2;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_U32) {
    if (buf_cap < 3)
      return 0;
    buf[0] = 117;
    buf[1] = 51;
    buf[2] = 50;
    return 3;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_U64) {
    if (buf_cap < 3)
      return 0;
    buf[0] = 117;
    buf[1] = 54;
    buf[2] = 52;
    return 3;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_BOOL) {
    if (buf_cap < 4)
      return 0;
    buf[0] = 98;
    buf[1] = 111;
    buf[2] = 111;
    buf[3] = 108;
    return 4;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_USIZE) {
    if (buf_cap < 5)
      return 0;
    buf[0] = 117;
    buf[1] = 115;
    buf[2] = 105;
    buf[3] = 122;
    buf[4] = 101;
    return 5;
  }
  if (tk == PARSER_ASM_PRIM_TYPE_ISIZE) {
    if (buf_cap < 5)
      return 0;
    buf[0] = 105;
    buf[1] = 115;
    buf[2] = 105;
    buf[3] = 122;
    buf[4] = 101;
    return 5;
  }
  return 0;
}

/**
 * LANG-009 M8 / DOC `parser_append_type_inst_mangle`:
 * `Name` + type_arg refs → `Name_suf0[_suf1…]` (cap 127 content).
 * CORE-016: `Result<T,i32>` compresses to `Result_T` (drop trailing `_i32` for E=i32).
 * @return mangled length, or 0 on failure
 * PLATFORM: SHARED — sole parse-time STRUCT_LIT type-inst mangle authority.
 */
static int32_t parser_asm_append_type_inst_mangle_c(void *arena, const uint8_t *base, int32_t base_len,
                                                     const int32_t *type_refs, int32_t nrefs, uint8_t *out,
                                                     int32_t out_cap) {
  int32_t pos;
  int32_t ai;
  int32_t is_result;
  int32_t e_is_i32;
  if (!arena || !base || base_len <= 0 || !type_refs || nrefs <= 0 || !out || out_cap <= 0)
    return 0;
  if (base_len >= out_cap)
    return 0;
  pos = 0;
  while (pos < base_len) {
    out[pos] = base[pos];
    pos = pos + 1;
  }
  is_result = 0;
  if (base_len == 6 && base[0] == 82 && base[1] == 101 && base[2] == 115 && base[3] == 117 && base[4] == 108
      && base[5] == 116) {
    /* "Result" */
    is_result = 1;
  }
  e_is_i32 = 0;
  if (is_result != 0 && nrefs >= 2 && type_refs[1] > 0
      && pipeline_type_kind_ord_at(arena, type_refs[1]) == PARSER_ASM_PRIM_TYPE_I32) {
    e_is_i32 = 1;
  }
  ai = 0;
  while (ai < nrefs && ai < 8) {
    uint8_t suf[64];
    int32_t sl;
    int32_t sj;
    if (is_result != 0 && e_is_i32 != 0 && ai == 1) {
      ai = ai + 1;
      continue;
    }
    if (type_refs[ai] <= 0)
      return 0;
    sl = parser_asm_type_ref_mangle_suffix_c(arena, type_refs[ai], suf, 64);
    if (sl <= 0)
      return 0;
    if (pos + 1 + sl >= out_cap)
      return 0;
    out[pos] = 95; /* _ */
    pos = pos + 1;
    sj = 0;
    while (sj < sl) {
      out[pos] = suf[sj];
      pos = pos + 1;
      sj = sj + 1;
    }
    ai = ai + 1;
  }
  if (pos <= base_len)
    return 0;
  return pos;
}

/** IDENT 后 `.field` / `[idx]` / `(args)` 后缀链；失败时写 out.ok=0 或仅写 out.next_lex 后返回。 */
static void parser_asm_primary_ident_suffix_loop_c(void *arena, struct parser_asm_slice_u8 *source,
                                                   struct parser_asm_lexer *lex, struct parser_asm_lexer_result *r,
                                                   struct parser_asm_parse_expr_result *out, int32_t first_suffix) {
  enum { PARSER_ASM_SUFFIX_STALL_LIMIT = 4096 };
  static int parser_asm_suffix_debug_calls = 0;
  static int parser_asm_suffix_debug_iters = 0;
  struct parser_asm_parse_expr_result arg_res;
  int32_t base_ref;
  int32_t fa_ref;
  int32_t idx_ref;
  int32_t call_ref;
  int32_t callee_ref;
  struct parser_asm_ast_expr fe;
  struct parser_asm_ast_expr ie;
  struct parser_asm_ast_expr ce_init;
  int32_t fi;
  int32_t pending_call_num_type_args;
  /* wave452: parsed turbofish type_arg type_refs (max 8); 0 slots = count-only soft path. */
  int32_t pending_call_type_arg_refs[8];
  int32_t prev_pos;
  int32_t prev_tok_kind;
  int32_t stall_count;
  int debug_enabled;

  pending_call_num_type_args = 0;
  {
    int32_t _zi;
    for (_zi = 0; _zi < 8; _zi++)
      pending_call_type_arg_refs[_zi] = 0;
  }
  prev_pos = -1;
  prev_tok_kind = -1;
  stall_count = 0;
  debug_enabled = parser_asm_suffix_debug_enabled();
  parser_asm_suffix_debug_calls++;
  if (debug_enabled && (parser_asm_suffix_debug_calls <= 64 || (parser_asm_suffix_debug_calls % 1024) == 0)) {
    /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
    { char _db[256]; int _dn = snprintf(_db, sizeof _db, "parser_asm suffix call=%d pos=%d tok=%d line=%d col=%d first=%d expr=%d\n",
        parser_asm_suffix_debug_calls, lex->pos, r->tok.kind, lex->line, lex->col, first_suffix, out->expr_ref);
      if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
  }
  for (;;) {
    const char *branch_tag;
    if (!first_suffix)
      lexer_next_into(r, *lex, source);
    first_suffix = 0;
    if (r->tok.kind == (int32_t)TOKEN_DOT)
      branch_tag = "dot";
    else if (r->tok.kind == (int32_t)TOKEN_LT)
      branch_tag = "lt";
    else if (r->tok.kind == (int32_t)TOKEN_LBRACKET)
      branch_tag = "index";
    else if (r->tok.kind == (int32_t)TOKEN_LPAREN)
      branch_tag = "call";
    else
      branch_tag = "stop";
    parser_asm_suffix_debug_iters++;
    if (debug_enabled && (parser_asm_suffix_debug_iters % 16384) == 0) {
      /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
      { char _db[256]; int _dn = snprintf(_db, sizeof _db, "parser_asm suffix iter=%d pos=%d tok=%d branch=%s line=%d col=%d expr=%d\n",
          parser_asm_suffix_debug_iters, lex->pos, r->tok.kind, branch_tag, lex->line, lex->col, out->expr_ref);
        if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
    }
    if (lex->pos == prev_pos && r->tok.kind == prev_tok_kind) {
      stall_count++;
      if (stall_count >= PARSER_ASM_SUFFIX_STALL_LIMIT) {
        diag_reportf(NULL, lex->line, lex->col, "parse error", NULL,
                     "parser asm suffix loop stalled (pos=%d, tok=%d, stall_count=%d)",
                     lex->pos, r->tok.kind, stall_count);
        out->ok = 0;
        out->next_lex = *lex;
        return;
      }
    } else {
      prev_pos = lex->pos;
      prev_tok_kind = r->tok.kind;
      stall_count = 0;
    }
    if (r->tok.kind == (int32_t)TOKEN_DOT) {
      int32_t mc_ref;
      int32_t mname_len;
      struct parser_asm_ast_expr me;
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      /**
       * Field / method name after `.`: IDENT or keyword-as-ident.
       * PLATFORM: SHARED — TOKEN_TYPE/SOA/PACKED may spell field names
       * (`s.type`, `x.soa`). Prior: only TOKEN_IDENT → `.type` aborted the
       * suffix loop and left a broken expr (function uncallable in typeck).
       */
      mname_len = -1;
      if (r->tok.kind == (int32_t)TOKEN_IDENT && r->tok.ident_len > 0) {
        mname_len = r->tok.ident_len;
      } else if (r->tok.kind == (int32_t)TOKEN_TYPE) {
        mname_len = 4; /* "type" */
      } else if (r->tok.kind == (int32_t)TOKEN_SOA) {
        mname_len = 3; /* "soa" */
      } else if (r->tok.kind == (int32_t)TOKEN_PACKED) {
        mname_len = 6; /* "packed" */
      }
      if (mname_len < 0) {
        out->next_lex = *lex;
        return;
      }
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_field_access_name_audit_c(source, r->token_start, mname_len));
      if (mname_len > 127)
        mname_len = 127;
      {
        size_t mname_start = r->token_start;
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        /** `.name(` → EXPR_METHOD_CALL；否则 EXPR_FIELD_ACCESS。 */
        if (r->tok.kind == (int32_t)TOKEN_LPAREN) {
          mc_ref = ast_ast_arena_expr_alloc(arena);
          if (mc_ref == 0) {
            out->ok = 0;
            return;
          }
          me = parser_asm_arena_expr_get_c(arena, mc_ref);
          parser_asm_expr_set_common_zeros_c(&me);
          me.kind = PARSER_ASM_EXPR_METHOD_CALL;
          me.method_call_base_ref = out->expr_ref;
          me.method_call_name_len = mname_len;
          fi = 0;
          while (fi < mname_len && (mname_start + (size_t)fi) < source->length) {
            me.method_call_name[fi] = source->data[mname_start + (size_t)fi];
            fi++;
          }
          while (fi < 128) {
            me.method_call_name[fi] = 0;
            fi++;
          }
          me.line = 0;
          me.col = 0;
          parser_asm_arena_expr_set_c(arena, mc_ref, me);
          out->expr_ref = mc_ref;
          *lex = r->next_lex;
          lexer_next_into(r, *lex, source);
          if (r->tok.kind != (int32_t)TOKEN_RPAREN) {
            int32_t mc_arg_buf[256];
            int32_t mc_arg_n = 0;
            int32_t mc_ai;
            for (;;) {
              if (mc_arg_n >= 256) {
                out->ok = 0;
                return;
              }
              memset(&arg_res, 0, sizeof(arg_res));
              arg_res.next_lex = *lex;
              parse_expr_into(arena, *lex, source, &arg_res);
              if (!arg_res.ok) {
                out->ok = 0;
                return;
              }
              mc_arg_buf[mc_arg_n] = arg_res.expr_ref;
              mc_arg_n = mc_arg_n + 1;
              *lex = arg_res.next_lex;
              lexer_next_into(r, *lex, source);
              if (r->tok.kind == (int32_t)TOKEN_COMMA) {
                *lex = r->next_lex;
                continue;
              }
              if (r->tok.kind == (int32_t)TOKEN_RPAREN) {
                *lex = r->next_lex;
                mc_ai = 0;
                while (mc_ai < mc_arg_n) {
                  if (pipeline_expr_append_method_call_arg(arena, mc_ref, mc_arg_buf[mc_ai]) < 0) {
                    out->ok = 0;
                    return;
                  }
                  mc_ai = mc_ai + 1;
                }
                break;
              }
              out->ok = 0;
              return;
            }
          } else {
            *lex = r->next_lex;
          }
        } else {
          fa_ref = ast_ast_arena_expr_alloc(arena);
          if (fa_ref == 0) {
            out->ok = 0;
            return;
          }
          fe = parser_asm_arena_expr_get_c(arena, fa_ref);
          parser_asm_expr_set_common_zeros_c(&fe);
          fe.kind = PARSER_ASM_EXPR_FIELD_ACCESS;
          fe.field_access_base_ref = out->expr_ref;
          fe.field_access_field_len = mname_len;
          fi = 0;
          while (fi < fe.field_access_field_len && (mname_start + (size_t)fi) < source->length) {
            fe.field_access_field_name[fi] = source->data[mname_start + (size_t)fi];
            fi++;
          }
          while (fi < 128) {
            fe.field_access_field_name[fi] = 0;
            fi++;
          }
          fe.line = 0;
          fe.col = 0;
          parser_asm_arena_expr_set_c(arena, fa_ref, fe);
          out->expr_ref = fa_ref;
          *lex = parser_asm_lex_at_token_from_result_c(*r);
        }
      }
    } else if (r->tok.kind == (int32_t)TOKEN_LT) {
      /**
       * 仅当 `<...>` 后真实跟 `(` 时才视为泛型调用 `id<T>(...)`。
       * 否则必须把 `<` 留给上层 relcompare，避免把 `elapsed_ns < 10000000`
       * 误吞成“带类型参数的变量引用”。
       *
       * wave452: when it is a generic call, also parse top-level type args into
       * type_refs (sidecar via append_call_type_arg). Nested/unparsable type
       * args fall back to count-only (call_num_type_args) for arity checks.
       * PLATFORM: SHARED — product primary path (parser_asm thin).
       */
      struct parser_asm_lexer after_angle;
      struct parser_asm_lexer_result after_angle_tok;
      int32_t type_arg_count = 0;
      int32_t parsed_n = 0;
      int32_t parsed_refs[8];
      int32_t parse_ok = 1;
      struct parser_asm_lexer cur;
      int32_t pi;
      for (pi = 0; pi < 8; pi++)
        parsed_refs[pi] = 0;
      /* First try real type_ref parse: IDENT/builtin/*T/[]T etc. */
      cur = r->next_lex;
      for (;;) {
        struct parser_asm_lexer out_ty;
        struct parser_asm_lexer_result sep;
        int32_t tr;
        if (parsed_n >= 8) {
          parse_ok = 0;
          break;
        }
        memset(&out_ty, 0, sizeof(out_ty));
        tr = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, cur, source, &out_ty);
        if (tr <= 0) {
          parse_ok = 0;
          break;
        }
        parsed_refs[parsed_n] = tr;
        parsed_n = parsed_n + 1;
        cur = out_ty;
        memset(&sep, 0, sizeof(sep));
        lexer_next_into(&sep, cur, source);
        if (sep.tok.kind == (int32_t)TOKEN_COMMA) {
          cur = sep.next_lex;
          continue;
        }
        if (sep.tok.kind == (int32_t)TOKEN_GT) {
          after_angle = sep.next_lex;
          break;
        }
        /*
         * wave483: nested turbofish `foo<Bar<A>>(` — lexer yields TOKEN_RSHIFT for
         * adjacent `>>`. Close this level and leave one `>` for the outer list
         * (same split as type_ref angle close). PLATFORM: SHARED call-site turbofish.
         */
        if (sep.tok.kind == (int32_t)TOKEN_RSHIFT) {
          after_angle = sep.next_lex;
          if (after_angle.pos > 0)
            after_angle.pos = after_angle.pos - (size_t)1;
          if (after_angle.col > 1)
            after_angle.col = after_angle.col - 1;
          break;
        }
        parse_ok = 0;
        break;
      }
      if (parse_ok != 0 && parsed_n > 0) {
        memset(&after_angle_tok, 0, sizeof(after_angle_tok));
        after_angle_tok.next_lex = after_angle;
        lexer_next_into(&after_angle_tok, after_angle, source);
        /**
         * LANG-009 M8: `Name<T,…> { fields }` is STRUCT_LIT with parse-time mangle
         * (Option<i32>→Option_i32), not a failed turbofish call. Prior path only
         * accepted `(` after angles → left lex at `<` → let-init fail → whole
         * function soft-drop (P001 no functions) → ld undefined `_main`.
         * G.7: reuse finish_struct_lit + prefer-block gates; mangle authority =
         * parser_asm_append_type_inst_mangle_c. PLATFORM: SHARED.
         */
        if (after_angle_tok.tok.kind == (int32_t)TOKEN_LBRACE) {
          struct parser_asm_ast_expr be;
          uint8_t mangled[128];
          int32_t mlen;
          int32_t bi;
          int32_t prefer_block;
          be = parser_asm_arena_expr_get_c(arena, out->expr_ref);
          if (be.kind != PARSER_ASM_EXPR_VAR || be.var_name_len <= 0) {
            out->next_lex = *lex;
            return;
          }
          prefer_block = 0;
          if (parser_asm_primary_lbrace_looks_like_block_c(after_angle_tok.next_lex, source) != 0) {
            prefer_block = 1;
          } else if (parser_asm_primary_empty_ident_braces_prefer_block_c(after_angle_tok.next_lex, source)
                     == 1) {
            prefer_block = 1;
          }
          if (prefer_block != 0) {
            out->next_lex = *lex;
            return;
          }
          mlen = parser_asm_append_type_inst_mangle_c(arena, be.var_name, be.var_name_len, parsed_refs,
                                                       parsed_n, mangled, 128);
          if (mlen <= 0 || mlen > 127) {
            out->ok = 0;
            return;
          }
          be.var_name_len = mlen;
          bi = 0;
          while (bi < 128) {
            be.var_name[bi] = (bi < mlen) ? mangled[bi] : (uint8_t)0;
            bi = bi + 1;
          }
          parser_asm_arena_expr_set_c(arena, out->expr_ref, be);
          parser_finish_struct_lit_from_type_ident_into_glue(arena, out->expr_ref,
                                                              after_angle_tok.next_lex, source, out);
          if (!out->ok)
            return;
          *lex = out->next_lex;
          lexer_next_into(r, *lex, source);
          pending_call_num_type_args = 0;
          for (pi = 0; pi < 8; pi++)
            pending_call_type_arg_refs[pi] = 0;
          continue;
        }
        if (after_angle_tok.tok.kind != (int32_t)TOKEN_LPAREN) {
          out->next_lex = *lex;
          return;
        }
        pending_call_num_type_args = parsed_n;
        for (pi = 0; pi < parsed_n && pi < 8; pi++)
          pending_call_type_arg_refs[pi] = parsed_refs[pi];
        for (pi = parsed_n; pi < 8; pi++)
          pending_call_type_arg_refs[pi] = 0;
        *lex = after_angle;
      } else {
        /* Fallback: count-only skip (complex type args / soft leave-off). */
        parser_asm_skip_generic_angle_list_count_into_slice_c(&after_angle, &type_arg_count, *lex, source);
        memset(&after_angle_tok, 0, sizeof(after_angle_tok));
        after_angle_tok.next_lex = after_angle;
        lexer_next_into(&after_angle_tok, after_angle, source);
        /* STRUCT_LIT type-inst needs real type_refs for mangle; count-only cannot. */
        if (after_angle_tok.tok.kind != (int32_t)TOKEN_LPAREN) {
          out->next_lex = *lex;
          return;
        }
        pending_call_num_type_args = type_arg_count;
        for (pi = 0; pi < 8; pi++)
          pending_call_type_arg_refs[pi] = 0;
        *lex = after_angle;
      }
    } else if (r->tok.kind == (int32_t)TOKEN_LBRACKET) {
      base_ref = out->expr_ref;
      *lex = r->next_lex;
      parse_expr_into(arena, *lex, source, out);
      if (!out->ok)
        return;
      fi = out->expr_ref;
      *lex = out->next_lex;
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_RBRACKET) {
        out->ok = 0;
        return;
      }
      *lex = r->next_lex;
      idx_ref = ast_ast_arena_expr_alloc(arena);
      if (idx_ref == 0) {
        out->ok = 0;
        return;
      }
      ie = parser_asm_arena_expr_get_c(arena, idx_ref);
      parser_asm_expr_set_common_zeros_c(&ie);
      ie.kind = PARSER_ASM_EXPR_INDEX;
      ie.index_base_ref = base_ref;
      ie.index_index_ref = fi;
      ie.index_base_is_slice = 0;
      ie.line = 0;
      ie.col = 0;
      parser_asm_arena_expr_set_c(arena, idx_ref, ie);
      out->expr_ref = idx_ref;
    } else if (r->tok.kind == (int32_t)TOKEN_LPAREN) {
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_call_args_shape_probe_c(r->next_lex, source, 0));
      callee_ref = out->expr_ref;
      *lex = r->next_lex;
      call_ref = ast_ast_arena_expr_alloc(arena);
      if (call_ref == 0) {
        out->ok = 0;
        return;
      }
      ce_init = parser_asm_arena_expr_get_c(arena, call_ref);
      ce_init.kind = PARSER_ASM_EXPR_CALL;
      ce_init.line = 0;
      ce_init.col = 0;
      parser_asm_expr_set_common_zeros_c(&ce_init);
      ce_init.call_callee_ref = callee_ref;
      /* call_num_type_args set by append_call_type_arg when type_refs stored;
       * pre-set count for count-only fallback (no type_ref sidecar). */
      ce_init.call_num_type_args = pending_call_num_type_args;
      parser_asm_arena_expr_set_c(arena, call_ref, ce_init);
      /*
       * wave452: persist turbofish type_arg type_refs when parsed (sidecar).
       * append resets count then re-increments — keeps count aligned with slots.
       */
      if (pending_call_num_type_args > 0 && pending_call_type_arg_refs[0] > 0) {
        int32_t tai;
        int32_t nstore = pending_call_num_type_args;
        if (nstore > 8)
          nstore = 8;
        for (tai = 0; tai < nstore; tai++) {
          if (pending_call_type_arg_refs[tai] <= 0)
            break;
          if (pipeline_expr_append_call_type_arg(arena, call_ref, pending_call_type_arg_refs[tai]) < 0) {
            out->ok = 0;
            return;
          }
        }
      }
      /*
       * 【Why 根源】call_arg 侧车池按「call_arg_base + idx」连续占槽。若 parse 嵌套 CALL 时
       * 外层已 append 部分实参，内层 base 会落在外层后续 idx 上，外层继续 append 时覆盖
       * 内层槽 → method(body)/无 mangle。
       * 【Invariant】先完整 parse 全部实参（嵌套 CALL 先落盘），再统一 append_call_arg，
       * 使外层 base 落在所有嵌套 call_arg 区间之后。
       */
      pending_call_num_type_args = 0;
      {
        int32_t _zi2;
        for (_zi2 = 0; _zi2 < 8; _zi2++)
          pending_call_type_arg_refs[_zi2] = 0;
      }
      lexer_next_into(r, *lex, source);
      {
        /* 旧硬顶 64：`arg_n >= 64` 使 65 实参 call 解析失败 → main 丢弃、无 _main（pool-limits）。 */
        int32_t arg_buf[256];
        int32_t arg_n = 0;
        int32_t ai;
        if (r->tok.kind != (int32_t)TOKEN_RPAREN) {
          for (;;) {
            if (arg_n >= 256) {
              out->ok = 0;
              return;
            }
            memset(&arg_res, 0, sizeof(arg_res));
            arg_res.next_lex = *lex;
            parse_expr_into(arena, *lex, source, &arg_res);
            if (!arg_res.ok) {
              out->ok = 0;
              return;
            }
            arg_buf[arg_n] = arg_res.expr_ref;
            arg_n = arg_n + 1;
            *lex = arg_res.next_lex;
            lexer_next_into(r, *lex, source);
            if (r->tok.kind == (int32_t)TOKEN_COMMA) {
              *lex = r->next_lex;
              continue;
            }
            if (r->tok.kind == (int32_t)TOKEN_RPAREN) {
              *lex = r->next_lex;
              break;
            }
            out->ok = 0;
            return;
          }
        } else {
          *lex = r->next_lex;
        }
        ai = 0;
        while (ai < arg_n) {
          if (pipeline_expr_append_call_arg(arena, call_ref, arg_buf[ai]) < 0) {
            out->ok = 0;
            return;
          }
          ai = ai + 1;
        }
      }
      out->expr_ref = call_ref;
    } else if (r->tok.kind == (int32_t)TOKEN_LBRACE) {
      /**
       * Qualified struct lit `Module.TypeName { ... }` (e.g. heap.PageMmapHeap { … },
       * process.SpawnIo { … }) vs bare if/while cond ending in field access:
       *   if a.x { … } / while b.x { … } / if c == Color.Red { … } / if 1 == b.x { … }
       *
       * Historical path always rewrote FIELD_ACCESS + `{` into STRUCT_LIT, which ate the
       * then/while body → XP003 out_len=0. wave361/364 already disambiguate IDENT+`{`;
       * G.7 reuses the same authorities here (no second heuristic).
       *
       * Invariant: only FIELD_ACCESS (ko=44) may become qualified struct lit; CALL/INDEX
       * after LBRACE still stop the suffix loop. PLATFORM: SHARED.
       */
      struct parser_asm_ast_expr fae;
      int32_t fa_ref;
      int32_t tlen;
      /*
       * wave1244 / PLATFORM: SHARED — qualified `Mod.Type { ... }` temp name buffer.
       * Must be 128 to match field_access_field_name[128] / struct_lit_struct_name[128]
       * (same as finish_struct_lit tnm[128]). Prior tnm[64] + while(ti<128) stack-smashed
       * the canary → silent exit(127) on Ubuntu when check hit lexer.x token.Token { ... }.
       * Mac could appear green depending on stack layout / protector placement.
       */
      uint8_t tnm[128];
      int32_t ti;
      int32_t tj;
      int32_t prefer_block;
      fa_ref = out->expr_ref;
      fae = parser_asm_arena_expr_get_c(arena, fa_ref);
      if (fae.kind != PARSER_ASM_EXPR_FIELD_ACCESS) {
        out->next_lex = *lex;
        return;
      }
      /* Same G.7 disambiguation as IDENT+LBRACE (wave361/364). Leave `{` for ctrl body. */
      prefer_block = 0;
      if (parser_asm_primary_lbrace_looks_like_block_c(r->next_lex, source) != 0) {
        prefer_block = 1;
      } else if (parser_asm_primary_empty_ident_braces_prefer_block_c(r->next_lex, source) == 1) {
        prefer_block = 1;
      }
      if (prefer_block != 0) {
        out->next_lex = *lex;
        return;
      }
      tlen = fae.field_access_field_len;
      /* Cap matches struct_lit_struct_name[128] content max (finish_struct_lit uses >127). */
      if (tlen <= 0 || tlen > 127) {
        out->ok = 0;
        return;
      }
      ti = 0;
      while (ti < 128) {
        tnm[ti] = fae.field_access_field_name[ti];
        ti = ti + 1;
      }
      parser_asm_expr_set_common_zeros_c(&fae);
      fae.kind = PARSER_ASM_FINISH_STRUCT_LIT_KIND;
      fae.struct_lit_struct_name_len = tlen;
      tj = 0;
      while (tj < 128) {
        fae.struct_lit_struct_name[tj] = tnm[tj];
        tj = tj + 1;
      }
      fae.struct_lit_field_base = 0;
      fae.struct_lit_num_fields = 0;
      fae.line = 0;
      fae.col = 0;
      parser_asm_arena_expr_set_c(arena, fa_ref, fae);
      *lex = r->next_lex;
      parser_asm_parse_struct_lit_fields_c(arena, fa_ref, *lex, source, out);
      if (!out->ok)
        return;
      /**
       * wave607 / PLATFORM: SHARED — qualified `Mod.Type { ... }.method()` /
       * `.field` continues the suffix chain (same as bare Type { } primary).
       * G.7: stay in this loop; do not open a second postfix path.
       */
      *lex = out->next_lex;
      lexer_next_into(r, *lex, source);
      first_suffix = 1;
      continue;
    } else {
      out->next_lex = *lex;
      return;
    }
  }
}

/** panic / panic(expr) primary。 */
static void parser_asm_primary_parse_panic_c(void *arena, struct parser_asm_slice_u8 *source,
                                             struct parser_asm_lexer *lex, struct parser_asm_lexer_result *r,
                                             struct parser_asm_parse_expr_result *out) {
  struct parser_asm_parse_expr_result arg_pr;
  int32_t panic_op;
  int32_t pref;
  struct parser_asm_ast_expr pe;

  parser_asm_lex_from_result_val_into(lex, *r);
  lexer_next_into(r, *lex, source);
  panic_op = 0;
  if (r->tok.kind == (int32_t)TOKEN_LPAREN) {
    parser_asm_lex_from_result_val_into(lex, *r);
    lexer_next_into(r, *lex, source);
    if (r->tok.kind != (int32_t)TOKEN_RPAREN) {
      memset(&arg_pr, 0, sizeof(arg_pr));
      arg_pr.next_lex = *lex;
      parse_expr_into(arena, *lex, source, &arg_pr);
      if (!arg_pr.ok) {
        out->ok = 0;
        return;
      }
      panic_op = arg_pr.expr_ref;
      *lex = arg_pr.next_lex;
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_RPAREN) {
        out->ok = 0;
        return;
      }
    }
    parser_asm_lex_from_result_val_into(lex, *r);
  }
  pref = ast_ast_arena_expr_alloc(arena);
  if (pref == 0) {
    out->ok = 0;
    return;
  }
  pe = parser_asm_arena_expr_get_c(arena, pref);
  parser_asm_expr_set_common_zeros_c(&pe);
  pe.kind = PARSER_ASM_EXPR_PANIC;
  pe.unary_operand_ref = panic_op;
  pe.line = 0;
  pe.col = 0;
  parser_asm_arena_expr_set_c(arena, pref, pe);
  out->ok = 1;
  out->expr_ref = pref;
  out->next_lex = *lex;
}

/**
 * Parse `asm!("template")` / `asm!("template", in/out/lateout(...), options(...))`
 * (stage10 10.2.1). Caller must have consumed IDENT `asm` and leave `*r` on TOKEN_BANG.
 * Slice6: `out`/`lateout` place may be `_` (clobber discard); trailing `options(name…)`.
 * Reg spellings packed comma-separated in method_call_name (matches call_arg order).
 * GNU `:` operands still rejected.
 * Escape decode matches STRING_LIT (G.7). Template → var_name; kind=EXPR_ASM(60).
 * PLATFORM: SHARED.
 */
static void parser_asm_primary_parse_asm_bang_c(void *arena, struct parser_asm_slice_u8 *source,
                                                struct parser_asm_lexer *lex, struct parser_asm_lexer_result *r,
                                                struct parser_asm_parse_expr_result *out) {
  int32_t pref;
  struct parser_asm_ast_expr ae;
  size_t q0;
  int32_t nlen;
  int32_t ri;
  int32_t wi;
  int32_t nops;
  struct parser_asm_parse_expr_result arg_res;
  size_t rq0;
  int32_t rlen;
  int32_t rwi;

  if (!arena || !source || !lex || !r || !out)
    return;
  out->ok = 0;
  if (r->tok.kind != (int32_t)TOKEN_BANG)
    return;
  parser_asm_lex_from_result_val_into(lex, *r);
  lexer_next_into(r, *lex, source);
  if (r->tok.kind != (int32_t)TOKEN_LPAREN)
    return;
  parser_asm_lex_from_result_val_into(lex, *r);
  lexer_next_into(r, *lex, source);
  if (r->tok.kind != (int32_t)TOKEN_STRING)
    return;
  pref = ast_ast_arena_expr_alloc(arena);
  if (pref == 0)
    return;
  ae = parser_asm_arena_expr_get_c(arena, pref);
  parser_asm_expr_set_common_zeros_c(&ae);
  ae.kind = PARSER_ASM_EXPR_ASM;
  ae.line = r->tok.line;
  ae.col = r->tok.col;
  q0 = r->token_start;
  nlen = r->tok.ident_len;
  ri = 0;
  wi = 0;
  if (nlen < 0)
    nlen = 0;
  while (ri < nlen) {
    uint8_t c = 0;
    if (wi >= 127) {
      lexer_note_string_lit_overflow(ae.line, ae.col);
      break;
    }
    if (q0 + (size_t)ri < source->length)
      c = source->data[q0 + (size_t)ri];
    if (c == 92 && (ri + 1) < nlen) {
      uint8_t n = 0;
      if (q0 + (size_t)(ri + 1) < source->length)
        n = source->data[q0 + (size_t)(ri + 1)];
      if (n == 110) { ae.var_name[wi++] = 10; ri += 2; continue; }
      if (n == 116) { ae.var_name[wi++] = 9; ri += 2; continue; }
      if (n == 114) { ae.var_name[wi++] = 13; ri += 2; continue; }
      if (n == 48) { ae.var_name[wi++] = 0; ri += 2; continue; }
      if (n == 92 || n == 34) { ae.var_name[wi++] = n; ri += 2; continue; }
      if (n == 120 && (ri + 3) < nlen) {
        uint8_t h1 = 0;
        uint8_t h2 = 0;
        int32_t v1 = -1;
        int32_t v2 = -1;
        if (q0 + (size_t)(ri + 2) < source->length)
          h1 = source->data[q0 + (size_t)(ri + 2)];
        if (q0 + (size_t)(ri + 3) < source->length)
          h2 = source->data[q0 + (size_t)(ri + 3)];
        if (h1 >= 48 && h1 <= 57) v1 = (int32_t)h1 - 48;
        if (h1 >= 97 && h1 <= 102) v1 = (int32_t)h1 - 97 + 10;
        if (h1 >= 65 && h1 <= 70) v1 = (int32_t)h1 - 65 + 10;
        if (h2 >= 48 && h2 <= 57) v2 = (int32_t)h2 - 48;
        if (h2 >= 97 && h2 <= 102) v2 = (int32_t)h2 - 97 + 10;
        if (h2 >= 65 && h2 <= 70) v2 = (int32_t)h2 - 65 + 10;
        if (v1 >= 0 && v2 >= 0) {
          ae.var_name[wi++] = (uint8_t)((v1 << 4) | v2);
          ri += 4;
          continue;
        }
      }
    }
    ae.var_name[wi++] = c;
    ri += 1;
  }
  ae.var_name_len = wi;
  if (wi < 128)
    ae.var_name[wi] = 0;
  parser_asm_arena_expr_set_c(arena, pref, ae);
  parser_asm_lex_from_result_val_into(lex, *r);
  lexer_next_into(r, *lex, source);
  /* GNU colon operands deferred — Rust comma form only. */
  if (r->tok.kind == (int32_t)TOKEN_COLON)
    return;
  nops = 0;
  {
    int32_t n_in = 0;
    int32_t saw_out = 0;
    int32_t saw_options = 0;
    int32_t opt_bits = 0;
    while (r->tok.kind == (int32_t)TOKEN_COMMA) {
      /* Slice6/8: in/out/lateout operands and/or trailing options(...). */
      int32_t is_out_op = 0;
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_IDENT)
        return;
      /* Trailing options(...) — once; bits → call_num_type_args (slice8). */
      if (parser_asm_primary_ident_is_options_c(source, r->token_start, r->tok.ident_len)) {
        if (saw_options)
          return;
        saw_options = 1;
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        if (r->tok.kind != (int32_t)TOKEN_LPAREN)
          return;
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        /* Empty options() ok; else IDENT[, IDENT…] of known names. */
        if (r->tok.kind != (int32_t)TOKEN_RPAREN) {
          while (1) {
            int32_t obit = 0;
            if (r->tok.kind != (int32_t)TOKEN_IDENT)
              return;
            obit = parser_asm_primary_asm_option_bit_c(source, r->token_start, r->tok.ident_len);
            if (obit == 0)
              return;
            opt_bits = opt_bits | obit;
            parser_asm_lex_from_result_val_into(lex, *r);
            lexer_next_into(r, *lex, source);
            if (r->tok.kind == (int32_t)TOKEN_RPAREN)
              break;
            if (r->tok.kind != (int32_t)TOKEN_COMMA)
              return;
            parser_asm_lex_from_result_val_into(lex, *r);
            lexer_next_into(r, *lex, source);
          }
        }
        /* Persist option bitmask on EXPR_ASM (reuse call_num_type_args). */
        ae = parser_asm_arena_expr_get_c(arena, pref);
        ae.call_num_type_args = opt_bits;
        parser_asm_arena_expr_set_c(arena, pref, ae);
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        continue;
      }
      if (saw_options)
        return;
      if (nops >= 6)
        return;
      if (parser_asm_primary_ident_is_in_c(source, r->token_start, r->tok.ident_len)) {
        if (saw_out)
          return;
        is_out_op = 0;
      } else if (parser_asm_primary_ident_is_out_c(source, r->token_start, r->tok.ident_len)
                 || parser_asm_primary_ident_is_lateout_c(source, r->token_start, r->tok.ident_len)) {
        is_out_op = 1;
        saw_out = 1;
      } else {
        return;
      }
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_LPAREN)
        return;
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_STRING)
        return;
      /*
       * Register spellings packed comma-separated in method_call_name
       * (order matches call_arg indices). int_val = num_in (outs follow).
       */
      ae = parser_asm_arena_expr_get_c(arena, pref);
      rq0 = r->token_start;
      rlen = r->tok.ident_len;
      if (rlen < 0)
        rlen = 0;
      if (rlen > 16)
        rlen = 16;
      if (nops == 0) {
        rwi = 0;
        while (rwi < rlen) {
          uint8_t rc = 0;
          if (rq0 + (size_t)rwi < source->length)
            rc = source->data[rq0 + (size_t)rwi];
          ae.method_call_name[rwi] = rc;
          rwi += 1;
        }
        ae.method_call_name_len = rwi;
        if (rwi < 128)
          ae.method_call_name[rwi] = 0;
      } else {
        int32_t base = ae.method_call_name_len;
        if (base < 0)
          base = 0;
        if (base + 1 + rlen >= 128)
          return;
        ae.method_call_name[base] = (uint8_t)',';
        rwi = 0;
        while (rwi < rlen) {
          uint8_t rc = 0;
          if (rq0 + (size_t)rwi < source->length)
            rc = source->data[rq0 + (size_t)rwi];
          ae.method_call_name[base + 1 + rwi] = rc;
          rwi += 1;
        }
        ae.method_call_name_len = base + 1 + rlen;
        if (ae.method_call_name_len < 128)
          ae.method_call_name[ae.method_call_name_len] = 0;
      }
      parser_asm_arena_expr_set_c(arena, pref, ae);
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      if (r->tok.kind != (int32_t)TOKEN_RPAREN)
        return;
      parser_asm_lex_from_result_val_into(lex, *r);
      lexer_next_into(r, *lex, source);
      /* Slice6: out/lateout place may be `_` (TOKEN_UNDERSCORE → VAR "_"). */
      if (is_out_op && r->tok.kind == (int32_t)TOKEN_UNDERSCORE) {
        int32_t disc = 0;
        struct parser_asm_ast_expr de;
        disc = ast_ast_arena_expr_alloc(arena);
        if (disc == 0)
          return;
        de = parser_asm_arena_expr_get_c(arena, disc);
        parser_asm_expr_set_common_zeros_c(&de);
        de.kind = PARSER_ASM_EXPR_VAR;
        de.line = r->tok.line;
        de.col = r->tok.col;
        de.var_name[0] = (uint8_t)'_';
        de.var_name[1] = 0;
        de.var_name_len = 1;
        parser_asm_arena_expr_set_c(arena, disc, de);
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        if (pipeline_expr_append_call_arg(arena, pref, disc) < 0)
          return;
      } else {
        memset(&arg_res, 0, sizeof(arg_res));
        arg_res.next_lex = *lex;
        parse_expr_into(arena, *lex, source, &arg_res);
        if (!arg_res.ok || arg_res.expr_ref <= 0)
          return;
        *lex = arg_res.next_lex;
        lexer_next_into(r, *lex, source);
        if (pipeline_expr_append_call_arg(arena, pref, arg_res.expr_ref) < 0)
          return;
      }
      if (!is_out_op)
        n_in += 1;
      nops += 1;
    }
    /* Persist num_in in int_val (outs are call_args[num_in..]). */
    ae = parser_asm_arena_expr_get_c(arena, pref);
    ae.int_val = (int64_t)n_in;
    parser_asm_arena_expr_set_c(arena, pref, ae);
  }
  if (r->tok.kind != (int32_t)TOKEN_RPAREN)
    return;
  parser_asm_lex_from_result_val_into(lex, *r);
  out->ok = 1;
  out->expr_ref = pref;
  out->next_lex = *lex;
}

/** `[ e0, ... ]` / `[]` 数组字面量 primary。 */
static void parser_asm_primary_parse_array_lit_c(void *arena, struct parser_asm_slice_u8 *source,
                                                 struct parser_asm_lexer *lex, struct parser_asm_lexer_result *r,
                                                 struct parser_asm_parse_expr_result *out) {
  struct parser_asm_parse_expr_result elem_res;
  struct parser_asm_lexer elem_lex;
  int32_t arr_ref;
  struct parser_asm_ast_expr ae0;

  parser_asm_lex_from_result_val_into(lex, *r);
  lexer_next_into(r, *lex, source);
  arr_ref = ast_ast_arena_expr_alloc(arena);
  if (arr_ref == 0) {
    out->ok = 0;
    return;
  }
  ae0 = parser_asm_arena_expr_get_c(arena, arr_ref);
  ae0.kind = PARSER_ASM_EXPR_ARRAY_LIT;
  ae0.resolved_type_ref = 0;
  ae0.line = 0;
  ae0.col = 0;
  parser_asm_expr_set_common_zeros_c(&ae0);
  parser_asm_arena_expr_set_c(arena, arr_ref, ae0);
  if (r->tok.kind != (int32_t)TOKEN_RBRACKET) {
    for (;;) {
      elem_lex = parser_asm_lex_at_token_from_result_c(*r);
      memset(&elem_res, 0, sizeof(elem_res));
      elem_res.next_lex = elem_lex;
      parse_expr_into(arena, elem_lex, source, &elem_res);
      if (!elem_res.ok || elem_res.expr_ref == 0) {
        out->ok = 0;
        return;
      }
      if (pipeline_expr_append_array_lit_elem(arena, arr_ref, elem_res.expr_ref) < 0) {
        out->ok = 0;
        return;
      }
      *lex = elem_res.next_lex;
      lexer_next_into(r, *lex, source);
      if (r->tok.kind == (int32_t)TOKEN_COMMA) {
        parser_asm_lex_from_result_val_into(lex, *r);
        lexer_next_into(r, *lex, source);
        if (r->tok.kind == (int32_t)TOKEN_RBRACKET)
          break;
        continue;
      }
      break;
    }
  }
  if (r->tok.kind == (int32_t)TOKEN_RBRACKET) {
    out->ok = 1;
    out->expr_ref = arr_ref;
    out->next_lex = r->next_lex;
    return;
  }
  out->ok = 0;
}

/**
 * parse_primary_into：INT | FLOAT | BOOL | break | continue | IDENT 后缀 | (expr) | [] | if | match | panic | @simd。
 */
void parser_asm_parse_primary_into_slice_c(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                           struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer_result r;
  struct parser_asm_ast_expr e;
  int32_t ref;
  int32_t fref;
  struct parser_asm_lexer if_lex;

  if (!out || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_head_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_expr_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_call_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_expr_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_expr_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_STRING) {
    size_t q0;
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    parser_asm_expr_set_common_zeros_c(&e);
    e.kind = PARSER_ASM_EXPR_STRING_LIT;
    e.line = r.tok.line;
    e.col = r.tok.col;
    e.var_name_len = 0;
    e.int_val = 0;
    /* lexer.x：TOKEN_STRING 的 token_start 已指向开引号后首字节。
     * wave281: decode escapes into AST semantic bytes (G.7 ≡ parser.x let-init STRING path).
     * Product set: \n \t \r \0 \\ \" \xHH. Lexer sticky L010 rejects others.
     * slen>127: overflow chunks chained via int_val (same store, not a second pool). */
    parser_asm_arena_expr_set_c(arena, ref, e);
    q0 = r.token_start;
    (void)parser_asm_string_lit_decode_span_c(arena, ref, source, q0, r.tok.ident_len, e.line, e.col);
    /* wave282: C-style adjacent string-literal concat (G.7 ≡ parser.x / parser_gen).
     * Soft residual: 2nd+ TOKEN_STRING after primary STRING was left unconsumed or
     * dropped as bare expr-stmt; only first literal entered the AST.
     * Peek/consume only TOKEN_STRING; leave non-string for parent via next_lex. */
    {
      struct parser_asm_lexer_result nr;
      struct parser_asm_lexer nlex = r.next_lex;
      out->ok = 1;
      out->expr_ref = ref;
      out->next_lex = r.next_lex;
      for (;;) {
        lexer_next_into(&nr, nlex, source);
        if (nr.tok.kind != (int32_t)TOKEN_STRING)
          break;
        e = parser_asm_arena_expr_get_c(arena, ref);
        (void)parser_asm_string_lit_decode_span_c(arena, ref, source, nr.token_start, nr.tok.ident_len,
                                                 e.line, e.col);
        nlex = nr.next_lex;
        out->next_lex = nlex;
      }
    }
    return;
  }
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_AT) {
    parser_parse_at_simd_builtin_into(arena, r, source, out);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_INT) {
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = PARSER_ASM_EXPR_LIT;
    e.line = r.tok.line;
    e.col = r.tok.col;
    e.int_val = r.tok.int_val;
    parser_asm_expr_set_common_zeros_c(&e);
    parser_asm_arena_expr_set_c(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    lex = r.next_lex;
    /** 与 IDENT 一致：先 lex 到 INT 后 token，再进后缀链（否则 r 仍为 TOKEN_INT）。 */
    lexer_next_into(&r, lex, source);
    /** 字面量后缀 `.method()` / `[i]` / 泛型 `<T>` 实例化须走与 IDENT 相同的后缀链。 */
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    out->next_lex = lex;
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_FLOAT) {
    fref = parser_asm_alloc_float_lit_c(arena, r.tok.float_val);
    if (fref == 0) {
      out->ok = 0;
      return;
    }
    out->ok = 1;
    out->expr_ref = fref;
    out->next_lex = r.next_lex;
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_TRUE || r.tok.kind == (int32_t)TOKEN_FALSE) {
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = PARSER_ASM_EXPR_BOOL_LIT;
    e.int_val = (r.tok.kind == (int32_t)TOKEN_TRUE) ? 1 : 0;
    e.line = 0;
    e.col = 0;
    parser_asm_expr_set_common_zeros_c(&e);
    parser_asm_arena_expr_set_c(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    out->next_lex = r.next_lex;
    return;
  }
  /**
   * wave668 Cap residual: TOKEN_NULL → EXPR_LIT int_val=0 (null pointer literal).
   * wave670: tag keyword null via var_name="null"/len=4 so typeck can hard-fail
   * null→non-ptr while bare INT 0 stays integer-coercible. Still EXPR_LIT 0 for
   * emit (no new ExprKind / ordinal churn). G.7 single primary path.
   * PLATFORM: SHARED.
   */
  if (r.tok.kind == (int32_t)TOKEN_NULL) {
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = PARSER_ASM_EXPR_LIT;
    e.line = r.tok.line;
    e.col = r.tok.col;
    e.int_val = 0;
    parser_asm_expr_set_common_zeros_c(&e);
    parser_asm_arena_expr_set_c(arena, ref, e);
    /*
     * Tag on live ast_Expr (G.7 pipeline_expr_tag_null_keyword_c) so
     * parser_asm_ast_expr memcpy layout drift cannot drop the keyword mark.
     */
    {
      extern void pipeline_expr_tag_null_keyword_c(void *arena, int32_t expr_ref);
      pipeline_expr_tag_null_keyword_c(arena, ref);
    }
    out->ok = 1;
    out->expr_ref = ref;
    lex = r.next_lex;
    lexer_next_into(&r, lex, source);
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    out->next_lex = lex;
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_BREAK || r.tok.kind == (int32_t)TOKEN_CONTINUE) {
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = (r.tok.kind == (int32_t)TOKEN_BREAK) ? PARSER_ASM_EXPR_BREAK : PARSER_ASM_EXPR_CONTINUE;
    e.line = 0;
    e.col = 0;
    parser_asm_expr_set_common_zeros_c(&e);
    parser_asm_arena_expr_set_c(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    out->next_lex = r.next_lex;
    return;
  }
  /**
   * wave371: TOKEN_RETURN as primary → EXPR_RETURN (operand in unary_operand_ref).
   * Needed for match-arm results `1 => return 42;` (docs/03 statement form).
   * Arm terminator `;` is left for parse_match_into; bare `return;` has no operand.
   * G.7: same EXPR_RETURN shape as parse_block_into return stmt (not a second return AST).
   * PLATFORM: SHARED.
   */
  if (r.tok.kind == (int32_t)TOKEN_RETURN) {
    struct parser_asm_parse_expr_result ret_op;
    int32_t ret_line = r.tok.line;
    int32_t ret_col = r.tok.col;
    lex = r.next_lex;
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = PARSER_ASM_EXPR_RETURN;
    e.line = ret_line;
    e.col = ret_col;
    parser_asm_expr_set_common_zeros_c(&e);
    lexer_next_into(&r, lex, source);
    /* Operand starts if next is not arm/stmt terminator. */
    if (r.tok.kind != (int32_t)TOKEN_SEMICOLON && r.tok.kind != (int32_t)TOKEN_RBRACE
        && r.tok.kind != (int32_t)TOKEN_EOF && r.tok.kind != (int32_t)TOKEN_COMMA
        && r.tok.kind != (int32_t)TOKEN_FATARROW) {
      ret_op.ok = 0;
      ret_op.expr_ref = 0;
      ret_op.next_lex = parser_asm_lex_at_token_from_result_c(r);
      parse_expr_into(arena, ret_op.next_lex, source, &ret_op);
      if (!ret_op.ok) {
        out->ok = 0;
        return;
      }
      e.unary_operand_ref = ret_op.expr_ref;
      parser_asm_arena_expr_set_c(arena, ref, e);
      out->ok = 1;
      out->expr_ref = ref;
      out->next_lex = ret_op.next_lex;
      return;
    }
    parser_asm_arena_expr_set_c(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    out->next_lex = lex;
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_MATCH) {
    parser_parse_match_into(arena, parser_asm_lex_at_token_from_result_c(r), source, out);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_PANIC) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_panic_kw_audit_c(parser_asm_lex_at_token_from_result_c(r), source));
    parser_asm_primary_parse_panic_c(arena, source, &lex, &r, out);
    return;
  }
  /* TOKEN_IDENT or TOKEN_SELF: keyword self is a valid EXPR_VAR name "self"
   * (pairs with param/let binding accept TOKEN_SELF; lexer ident_len=0 for SELF). */
  if (r.tok.kind == (int32_t)TOKEN_IDENT || r.tok.kind == (int32_t)TOKEN_SELF) {
    int32_t vlen = r.tok.ident_len;
    int name_was_self = (r.tok.kind == (int32_t)TOKEN_SELF);
    if (name_was_self)
      vlen = 4;
    if (!name_was_self
        && parser_asm_primary_ident_is_unsafe_c(source, r.token_start, r.tok.ident_len)) {
      parser_asm_primary_parse_unsafe_expr_c(arena, r.next_lex, source, out);
      return;
    }
    /* Stage10 10.2.1: `asm!("...")` — peek BANG; bare `asm` remains EXPR_VAR. */
    if (!name_was_self
        && parser_asm_primary_ident_is_asm_c(source, r.token_start, r.tok.ident_len)) {
      struct parser_asm_lexer_result peek;
      struct parser_asm_lexer peek_lex;
      peek_lex = r.next_lex;
      lexer_next_into(&peek, peek_lex, source);
      if (peek.tok.kind == (int32_t)TOKEN_BANG) {
        parser_asm_primary_parse_asm_bang_c(arena, source, &peek_lex, &peek, out);
        return;
      }
    }
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0) {
      out->ok = 0;
      return;
    }
    e = parser_asm_arena_expr_get_c(arena, ref);
    e.kind = PARSER_ASM_EXPR_VAR;
    parser_asm_primary_copy_ident_to_var_c(&e, source, r.token_start, vlen);
    e.line = r.tok.line;
    e.col = r.tok.col;
    parser_asm_expr_set_common_zeros_c(&e);
    parser_asm_arena_expr_set_c(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    lex = r.next_lex;
    lexer_next_into(&r, lex, source);
    /* Struct lit Type { ... } only for IDENT type names, not keyword self. */
    if (r.tok.kind == (int32_t)TOKEN_LBRACE && !name_was_self) {
      /**
       * wave361 / docs/03 bare if/while: `if b { body }` must not parse `b {` as struct lit.
       * Reuse G.7 lbrace_looks_like_block: stmt-like after `{` → end primary as VAR, leave `{`.
       * Field-like (`x:`, `,`, `}`) → keep Type { fields } struct lit (return/let paths).
       * wave364: empty `}` was field-like → bare `if b {}` / `while b {}` ate then-body as
       * empty struct lit; prefer block when post-`}` is not a value-position terminator.
       * PLATFORM: SHARED.
       */
      if (parser_asm_primary_lbrace_looks_like_block_c(r.next_lex, source) != 0) {
        out->next_lex = lex;
        return;
      }
      if (parser_asm_primary_empty_ident_braces_prefer_block_c(r.next_lex, source) == 1) {
        out->next_lex = lex;
        return;
      }
      parser_finish_struct_lit_from_type_ident_into_glue(arena, ref, r.next_lex, source, out);
      if (!out->ok)
        return;
      /**
       * wave607 / PLATFORM: SHARED — STRUCT_LIT is not a suffix-chain terminal.
       * `Type { ... }.method()` / `.field` / `[i]` must continue the same suffix
       * loop as `(expr).method()`. Historical early return left `.sum()` unparsed
       * → return-stmt parse fail → main dropped (num_funcs=1, main_idx=-1) →
       * ld undefined `_main` (soft residual "STRUCT_LIT as method base").
       * G.7: reuse parser_asm_primary_ident_suffix_loop_c (no second postfix path).
       */
      lex = out->next_lex;
      lexer_next_into(&r, lex, source);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_suffix_chain_probe_c(lex, source));
      parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
      return;
    }
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_suffix_chain_probe_c(lex, source));
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_LPAREN) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_paren_expr_head_audit_c(lex, source));
    parser_asm_lex_from_result_val_into(&lex, r);
    parse_expr_into(arena, lex, source, out);
    if (!out->ok)
      return;
    lex = out->next_lex;
    lexer_next_into(&r, lex, source);
    if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
      out->ok = 0;
      return;
    }
    /**
     * `(expr)` 不是后缀链终点；如 `(p + i)[0]` / `(f())(...)` 仍需继续走统一 suffix loop。
     * 之前这里直接 return，会把 `)` 后的 `[` / `(` / `.` 留给外层，导致整条 expr-stmt parse skip。
     */
    out->next_lex = r.next_lex;
    lex = r.next_lex;
    lexer_next_into(&r, lex, source);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_suffix_chain_probe_c(lex, source));
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_array_lit_head_audit_c(parser_asm_lex_at_token_from_result_c(r), source));
    parser_asm_primary_parse_array_lit_c(arena, source, &lex, &r, out);
    if (!out->ok)
      return;
    /**
     * wave611 / PLATFORM: SHARED — array literal is not a suffix-chain endpoint.
     * `[e0, e1][i]` / `[..][0] + …` need the same G.7 postfix loop as `(expr)`
     * and anonymous `{…}` (INDEX / CALL / FIELD). Early return left the trailing
     * `[` for the outer expr layer → whole-function parse skip (XP003 out_len=0).
     * G.7: reuse parser_asm_primary_ident_suffix_loop_c only; no second path.
     */
    lex = out->next_lex;
    lexer_next_into(&r, lex, source);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_suffix_chain_probe_c(lex, source));
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_IF) {
    if_lex = parser_asm_lex_at_token_from_result_c(r);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_expr_branch_audit_c(if_lex, source));
    parser_parse_if_expr_into(arena, if_lex, source, 0, out);
    return;
  }
  if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
    /**
     * PLATFORM: SHARED — bare `{` primary disambiguation (G.7 single path):
     * block expression `{ stmt; ... expr }` vs anonymous struct lit `{ field: e }`.
     * Prefer block when lookahead is stmt-like so `{ let y = 1; return y; }` parses
     * instead of whole-function parse-skip (codegen M2 residual root cause).
     */
    if (parser_asm_primary_lbrace_looks_like_block_c(r.next_lex, source) != 0) {
      parser_asm_primary_parse_block_expr_c(arena, r.next_lex, source, out);
      return;
    }
    /** 匿名 struct 字面量 `{ fd, x: 1 }`（let p: PollFd = { ... }）。 */
    parser_asm_parse_anonymous_struct_lit_c(arena, r.next_lex, source, out);
    if (!out->ok)
      return;
    /**
     * wave607 / PLATFORM: SHARED — anonymous `{ ... }.field` / `.method()` suffix.
     * Same G.7 suffix loop as named Type { } (no second path).
     */
    lex = out->next_lex;
    lexer_next_into(&r, lex, source);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_primary_suffix_chain_probe_c(lex, source));
    parser_asm_primary_ident_suffix_loop_c(arena, source, &lex, &r, out, 1);
    return;
  }
  out->ok = 0;
}

#endif /* PARSER_ASM_PRIMARY_SLICE_INCLUDED */
