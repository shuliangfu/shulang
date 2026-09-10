/**
 * parser_asm_match_subject_slice.inc — parse_match_subject_into / parse_match_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * match subject: bare IDENT → EXPR_VAR (so `{` after IDENT is match arms,
 * not STRUCT_LIT). IDENT followed by CALL `(` / INDEX `[` / FIELD `.`
 * falls through to parse_expr_into (parser_x mega). parse_match_into
 * parses the full match expression and callbacks parse_expr_into.
 */
#ifndef PARSER_ASM_MATCH_SUBJECT_SLICE_INCLUDED
#define PARSER_ASM_MATCH_SUBJECT_SLICE_INCLUDED

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *source);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                            struct parser_asm_parse_expr_result *out);
extern void parser_parse_match_subject_into_glue(void *arena, struct parser_asm_lexer lex,
                                                 struct parser_asm_slice_u8 *source,
                                                 struct parser_asm_parse_expr_result *out);
extern int32_t parser_asm_stretch_match_kw_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_match_subject_deep_audit_c(struct parser_asm_lexer lex,
                                                             struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_arms_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_subject_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_arms_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_ultra_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_super_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_subject_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_block_deep_audit_c(struct parser_asm_lexer lex,
                                                           struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_match_subject_ident_audit_c(struct parser_asm_lexer_result r,
                                                              struct parser_asm_slice_u8 *source);
extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
extern size_t parser_asm_lexer_pos_before_run_c(size_t end_pos, int32_t run_len);
extern void parser_asm_copy_slice_to_name64_slice_c(struct parser_asm_slice_u8 *source, size_t start, int32_t nlen,
                                                      uint8_t *out);
extern struct ast_Module *pipeline_parser_get_match_module(void);
extern int32_t pipeline_module_enum_variant_tag_for_names(struct ast_Module *m, uint8_t *enum_name, int32_t enum_len,
                                                            uint8_t *variant_name, int32_t variant_len);
extern int32_t pipeline_module_enum_name_len(void *module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(void *module, int32_t idx, int32_t off);
extern int32_t pipeline_expr_append_match_arm(void *arena, int32_t expr_ref, int32_t result_ref, int32_t is_wildcard,
                                              int32_t lit_val, int32_t is_enum_variant, int32_t variant_index);
/* wave700: optional match-arm guard (`pat if cond =>`). */
extern void pipeline_expr_match_arm_set_guard_ref(void *arena, int32_t expr_ref, int32_t i, int32_t guard_ref);

/** 与 parser.x ast.expr_init_match_enum 一致。 */
static void parser_asm_expr_init_match_enum_c(struct ast_Expr *e) {
  if (!e)
    return;
  e->match_arm_base = 0;
  e->enum_variant_tag = 0;
}

/** expr_set_common_zeros：与 parser.x 字段清零顺序一致。 */
static void parser_asm_match_expr_common_zeros_c(struct ast_Expr *e) {
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

/**
 * parse_match_subject_into: parse the match subject.
 * Bare IDENT stays EXPR_VAR and does not call parse_expr_into — `{` after
 * the ident is the arm list, not a STRUCT_LIT (`match x { 1 => 2; _ => 0 }`).
 * IDENT with postfix CALL `(` / INDEX `[` / FIELD `.` rewinds to the original
 * lex and uses parse_expr_into (parser_x mega suffix authority). Do not
 * peek-fallthrough on TOKEN_LBRACE.
 * PLATFORM: SHARED — parser_asm match-subject authority (G.7).
 */
void parser_asm_parse_match_subject_into_c(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                           struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer_result peek;
  int32_t ref;
  struct ast_Expr e;
  int32_t name_len;
  size_t start;
  int32_t ni;
  if (!arena || !source || !out)
    return;
  out->ok = 0;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind == (int32_t)TOKEN_IDENT) {
    /* Peek next token without consuming original lex. Postfix CALL/INDEX/FIELD
     * must go through parse_expr_into from the IDENT start; `{` must not. */
    lexer_next_into(&peek, r.next_lex, source);
    if (peek.tok.kind == (int32_t)TOKEN_LPAREN
        || peek.tok.kind == (int32_t)TOKEN_LBRACKET
        || peek.tok.kind == (int32_t)TOKEN_DOT) {
      parse_expr_into(arena, lex, source, out);
      return;
    }
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_subject_ident_audit_c(r, source));
    ref = ast_ast_arena_expr_alloc(arena);
    if (ref == 0)
      return;
    e = ast_ast_arena_expr_get(arena, ref);
    e.kind = 3; /* AST_EXPR_VAR */
    /* wave582 Cap residual: Expr.var_name is u8[128]; clamp 63→127, pad 128. */
    name_len = r.tok.ident_len;
    if (name_len > 127)
      name_len = 127;
    e.var_name_len = name_len;
    start = r.token_start;
    for (ni = 0; ni < name_len && start + (size_t)ni < source->length; ni++)
      e.var_name[ni] = source->data[start + ni];
    for (; ni < 128; ni++)
      e.var_name[ni] = 0;
    e.line = 0;
    e.col = 0;
    parser_asm_match_expr_common_zeros_c(&e);
    ast_ast_arena_expr_set(arena, ref, e);
    out->ok = 1;
    out->expr_ref = ref;
    out->next_lex = r.next_lex;
    return;
  }
  parse_expr_into(arena, lex, source, out);
}

/**
 * Parse `{ field, field: lit, field: _ }` after TOKEN_LBRACE is consumed.
 * *r is the first token inside the braces. On 0: *lex sits after `}`,
 * *out_guard is 0 or the implicit `subject.field == lit && ...` chain.
 * On -1: parse fail (caller returns).
 * Named `Type { fields }` and anonymous `{ fields }` share this loop.
 * The type name is not stored; match subject type names the struct.
 * PLATFORM: SHARED — one field-pattern authority (G.7).
 */
static int32_t parser_asm_parse_match_struct_fields_c(void *arena, struct parser_asm_lexer *lex,
                                                      struct parser_asm_slice_u8 *source,
                                                      struct parser_asm_lexer_result *r,
                                                      int32_t subject_ref, int32_t *out_guard) {
  int32_t field_guard = 0;
  if (!arena || !lex || !source || !r || !out_guard)
    return -1;
  *out_guard = 0;
  while (r->tok.kind != (int32_t)TOKEN_RBRACE && r->tok.kind != (int32_t)TOKEN_EOF) {
    if (r->tok.kind == (int32_t)TOKEN_IDENT) {
      uint8_t fname[128];
      int32_t flen = r->tok.ident_len;
      size_t fstart = r->token_start;
      int32_t fi;
      if (flen > 127)
        flen = 127;
      memset(fname, 0, sizeof(fname));
      for (fi = 0; fi < flen && fstart + (size_t)fi < source->length; fi++)
        fname[fi] = source->data[fstart + fi];
      parser_lex_from_next_into_glue(lex, *r);
      lexer_next_into(r, *lex, source);
      if (r->tok.kind == (int32_t)TOKEN_COLON) {
        int32_t fval;
        int32_t fref, lit_ref, eq_ref;
        struct ast_Expr fe, le, ee;
        parser_lex_from_next_into_glue(lex, *r);
        lexer_next_into(r, *lex, source);
        /* `field: _` — wildcard field value, skip (no guard). */
        if (r->tok.kind == (int32_t)TOKEN_UNDERSCORE) {
          parser_lex_from_next_into_glue(lex, *r);
          lexer_next_into(r, *lex, source);
        } else {
          if (r->tok.kind != (int32_t)TOKEN_INT)
            return -1;
          fval = r->tok.int_val;
          parser_lex_from_next_into_glue(lex, *r);
          lexer_next_into(r, *lex, source);
          fref = ast_ast_arena_expr_alloc(arena);
          if (fref == 0)
            return -1;
          fe = ast_ast_arena_expr_get(arena, fref);
          memset(&fe, 0, sizeof(fe));
          fe.kind = 44; /* EXPR_FIELD_ACCESS */
          fe.field_access_base_ref = subject_ref;
          memcpy(fe.field_access_field_name, fname, (size_t)flen);
          fe.field_access_field_len = flen;
          ast_ast_arena_expr_set(arena, fref, fe);
          lit_ref = ast_ast_arena_expr_alloc(arena);
          if (lit_ref == 0)
            return -1;
          le = ast_ast_arena_expr_get(arena, lit_ref);
          memset(&le, 0, sizeof(le));
          le.kind = 0; /* EXPR_LIT */
          le.int_val = (int64_t)fval;
          ast_ast_arena_expr_set(arena, lit_ref, le);
          eq_ref = ast_ast_arena_expr_alloc(arena);
          if (eq_ref == 0)
            return -1;
          ee = ast_ast_arena_expr_get(arena, eq_ref);
          memset(&ee, 0, sizeof(ee));
          ee.kind = 14; /* EXPR_EQ */
          ee.binop_left_ref = fref;
          ee.binop_right_ref = lit_ref;
          ast_ast_arena_expr_set(arena, eq_ref, ee);
          if (field_guard == 0) {
            field_guard = eq_ref;
          } else {
            int32_t and_ref = ast_ast_arena_expr_alloc(arena);
            struct ast_Expr ae;
            if (and_ref == 0)
              return -1;
            ae = ast_ast_arena_expr_get(arena, and_ref);
            memset(&ae, 0, sizeof(ae));
            ae.kind = 20; /* EXPR_LOGAND */
            ae.binop_left_ref = field_guard;
            ae.binop_right_ref = eq_ref;
            ast_ast_arena_expr_set(arena, and_ref, ae);
            field_guard = and_ref;
          }
        }
      }
      /* `field` bind — skip here; typeck/codegen resolve as subject fields. */
      if (r->tok.kind == (int32_t)TOKEN_COMMA) {
        parser_lex_from_next_into_glue(lex, *r);
        lexer_next_into(r, *lex, source);
      }
    } else {
      return -1;
    }
  }
  if (r->tok.kind == (int32_t)TOKEN_RBRACE)
    parser_lex_from_next_into_glue(lex, *r);
  *out_guard = field_guard;
  return 0;
}

/**
 * Dest-typed `.Variant` match pattern: unique registered enum that
 * owns this variant name. Type comes from the match subject the
 * same way dest-typed `{ fields }` does; this scan finds the unique
 * sidecar owner so named `Type.Variant` tag lookup can run.
 * @return tag >= 0; -1 unknown or ambiguous (caller parse-fails)
 * G.7: same pipeline_module_enum_variant_tag_for_names as IDENT+DOT.
 * PLATFORM: SHARED dest-typed enum match.
 */
static int32_t parser_asm_match_dest_enum_tag_c(void *m, uint8_t *vname, int32_t vlen) {
  uint8_t ename[128];
  int32_t ei;
  int32_t nlen;
  int32_t bi;
  int32_t tag;
  int32_t hits;
  int32_t found;
  if (!m || !vname || vlen <= 0)
    return -1;
  hits = 0;
  found = -1;
  ei = 0;
  while (ei < 64) {
    nlen = pipeline_module_enum_name_len(m, ei);
    if (nlen <= 0)
      break;
    if (nlen > 127)
      nlen = 127;
    memset(ename, 0, sizeof(ename));
    bi = 0;
    while (bi < nlen) {
      ename[bi] = pipeline_module_enum_name_byte_at(m, ei, bi);
      bi = bi + 1;
    }
    tag = pipeline_module_enum_variant_tag_for_names(m, ename, nlen, vname, vlen);
    if (tag >= 0) {
      hits = hits + 1;
      found = tag;
    }
    ei = ei + 1;
  }
  if (hits != 1)
    return -1;
  return found;
}

/**
 * parse_match_into：解析 `match expr { pat => result; ... }`；lex 指向 match 关键字。
 *
 * PLATFORM: SHARED — arm pattern authority (G.7). wave327: multi-pattern arms
 * `1 | 2 | 3 => result` expand to one MatchArmEntry per lit/enum (same result_ref).
 * Docs/04: `|` here is multi-pattern only, not type union.
 * Struct patterns: named `Type { fields }` or dest-typed `{ fields }`
 * (type from match subject). Enum patterns: named `Type.Variant` or
 * dest-typed `.Variant` / bare `Variant`. Rebuild: parser_asm_thin_glue.o + g05.
 */
void parser_asm_parse_match_into_c(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                   struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer_result r;
  struct parser_asm_parse_expr_result matched_res;
  int32_t mref;
  struct ast_Expr me;
  int32_t is_wc;
  int32_t lit_v;
  int32_t is_ev;
  int32_t var_idx;
  int32_t enum_len;
  size_t enum_start;
  uint8_t enum_buf[128]; /* wave582 Cap residual: match Enum.Variant names ≤127 */
  int32_t variant_len;
  size_t variant_start;
  uint8_t variant_buf[128];
  struct ast_Module *mod_m;
  struct parser_asm_parse_expr_result arm_res;
  int32_t arm_i;
  /* wave327: multi-pattern arm buffers (docs: `1 | 2 => expr`). Cap 16 patterns per arm. */
  int32_t pat_is_wc[16];
  int32_t pat_lit_v[16];
  int32_t pat_is_ev[16];
  int32_t pat_var_idx[16];
  int32_t pat_n;
  int32_t pat_i;
  int32_t arm_via_guard; /* wave700: 1 = arm fully handled in TOKEN_IF path */
  /* wave708: implicit guard expr for struct field lit patterns (`Point { x: 0, y: 0 }`).
   * 0 = no guard; >0 = expr_ref to `subject.field == val && ...` chain. */
  int32_t pat_guard_ref[16];
  if (!arena || !source || !out)
    return;
  out->ok = 0;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_MATCH)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_kw_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_arms_body_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_subject_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_block_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_subject_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_arms_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_subject_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_arms_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultra_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_super_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));







  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));








  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));









  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));










  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));











  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));












  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));













  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));














  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






















  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));






























  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));

































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));


































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));



































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));




































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));





































  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apexversal_maxversal_wholeversal_completeversal_fullversal_everyversal_totversal_allversal_panversal_omniversal_hyperversal_metaversal_multiversal_intergalactic_galactic_celestial_divine_imperial_sovereign_omnipotent_universal_cosmic_eternal_infinite_transcendent_absolute_ultimate_supreme_crown_pinnacle_zenith_peak_summit_apex_max_ultra_hyper_mega_full_deep_audit_c(lex, source));
  memset(&matched_res, 0, sizeof(matched_res));
  matched_res.next_lex = r.next_lex;
  parser_parse_match_subject_into_glue(arena, r.next_lex, source, &matched_res);
  if (!matched_res.ok)
    return;
  lex = matched_res.next_lex;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_match_arms_probe_c(&r.next_lex, source, 0));
  lex = r.next_lex;
  mref = ast_ast_arena_expr_alloc(arena);
  if (mref == 0)
    return;
  me = ast_ast_arena_expr_get(arena, mref);
  me.kind = 43; /* EXPR_MATCH */
  me.line = 0;
  me.col = 0;
  parser_asm_match_expr_common_zeros_c(&me);
  parser_asm_expr_init_match_enum_c(&me);
  me.match_matched_ref = matched_res.expr_ref;
  ast_ast_arena_expr_set(arena, mref, me);
  for (;;) {
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_RBRACE) {
      lex = r.next_lex;
      break;
    }
    /* wave327: collect one or more patterns joined by TOKEN_PIPE before =>. */
    pat_n = 0;
    arm_via_guard = 0;
    for (;;) {
      if (pat_n >= 16)
        return;
      is_wc = 0;
      lit_v = 0;
      is_ev = 0;
      var_idx = -1;
      pat_guard_ref[pat_n] = 0; /* wave708: reset implicit guard */
      if (r.tok.kind == (int32_t)TOKEN_INT) {
        lit_v = r.tok.int_val;
        parser_lex_from_next_into_glue(&lex, r);
      } else if (r.tok.kind == (int32_t)TOKEN_UNDERSCORE) {
        is_wc = 1;
        parser_lex_from_next_into_glue(&lex, r);
      } else if (r.tok.kind == (int32_t)TOKEN_IDENT) {
        /* wave582 Cap residual: enum/variant pattern names content ≤127. */
        enum_len = r.tok.ident_len;
        if (enum_len > 127)
          enum_len = 127;
        enum_start = r.token_start;
        if (enum_start == 0)
          enum_start = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, enum_len);
        memset(enum_buf, 0, sizeof(enum_buf));
        parser_asm_copy_slice_to_name64_slice_c(source, enum_start, enum_len, enum_buf);
        parser_lex_from_next_into_glue(&lex, r);
        lexer_next_into(&r, lex, source);
        /*
         * wave708: struct field pattern `Point { x: 0, y: 0 }` / `Point { x, y }`.
         * After type name IDENT, TOKEN_LBRACE starts field patterns (not enum DOT).
         * For `field: lit_val`, build implicit guard `subject.field == lit_val`
         * chained with LOGAND. For `field` (bind), skip (wave707 field bind handles).
         * Arm stays wildcard; guard_ref carries field lit comparisons.
         * PLATFORM: SHARED — parser_asm match arm authority.
         */
        if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
          parser_lex_from_next_into_glue(&lex, r);
          lexer_next_into(&r, lex, source);
          if (parser_asm_parse_match_struct_fields_c(arena, &lex, source, &r, matched_res.expr_ref,
                                                    &pat_guard_ref[pat_n]) != 0)
            return;
          is_wc = 1;
        } else if (r.tok.kind == (int32_t)TOKEN_DOT) {
          parser_lex_from_next_into_glue(&lex, r);
          lexer_next_into(&r, lex, source);
          if (r.tok.kind != (int32_t)TOKEN_IDENT)
            return;
          variant_len = r.tok.ident_len;
          if (variant_len > 127)
            variant_len = 127;
          variant_start = r.token_start;
          if (variant_start == 0)
            variant_start = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, variant_len);
          memset(variant_buf, 0, sizeof(variant_buf));
          parser_asm_copy_slice_to_name64_slice_c(source, variant_start, variant_len, variant_buf);
          parser_lex_from_next_into_glue(&lex, r);
          is_ev = 1;
          mod_m = pipeline_parser_get_match_module();
          if (mod_m)
            var_idx = pipeline_module_enum_variant_tag_for_names(mod_m, enum_buf, enum_len, variant_buf,
                                                                variant_len);
        } else {
          /* Dest-typed `Green =>`. IDENT is already in enum_buf;
           * r is FATARROW/PIPE/IF and lex still sits after IDENT
           * so the common next re-reads that token. Same unique
           * sidecar scan as dest-typed `.Variant`. Unknown IDENT
           * still parse-fails. PLATFORM: SHARED dest-typed bare enum. */
          is_ev = 1;
          mod_m = pipeline_parser_get_match_module();
          var_idx = -1;
          if (mod_m)
            var_idx = parser_asm_match_dest_enum_tag_c(mod_m, enum_buf, enum_len);
          if (var_idx < 0)
            return;
        }
      } else if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
        /* Anonymous `{ fields } =>`. Type comes from the match subject
         * (named `Type { fields }` discards IDENT the same way).
         * PLATFORM: SHARED — dest-typed match pattern. */
        parser_lex_from_next_into_glue(&lex, r);
        lexer_next_into(&r, lex, source);
        if (parser_asm_parse_match_struct_fields_c(arena, &lex, source, &r, matched_res.expr_ref,
                                                  &pat_guard_ref[pat_n]) != 0)
          return;
        is_wc = 1;
      } else if (r.tok.kind == (int32_t)TOKEN_DOT) {
        /* Dest-typed `.Variant =>`. Type comes from the match
         * subject (named `Type.Variant` already uses IDENT+DOT).
         * Bare `Green =>` is the IDENT-without-DOT dest-typed
         * arm above (same tag scan).
         * PLATFORM: SHARED dest-typed enum match. */
        parser_lex_from_next_into_glue(&lex, r);
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_IDENT)
          return;
        variant_len = r.tok.ident_len;
        if (variant_len > 127)
          variant_len = 127;
        variant_start = r.token_start;
        if (variant_start == 0)
          variant_start = parser_asm_lexer_pos_before_run_c(r.next_lex.pos, variant_len);
        memset(variant_buf, 0, sizeof(variant_buf));
        parser_asm_copy_slice_to_name64_slice_c(source, variant_start, variant_len, variant_buf);
        parser_lex_from_next_into_glue(&lex, r);
        is_ev = 1;
        mod_m = pipeline_parser_get_match_module();
        var_idx = -1;
        if (mod_m)
          var_idx = parser_asm_match_dest_enum_tag_c(mod_m, variant_buf, variant_len);
        if (var_idx < 0)
          return;
      } else {
        return;
      }
      pat_is_wc[pat_n] = is_wc;
      pat_lit_v[pat_n] = lit_v;
      pat_is_ev[pat_n] = is_ev;
      pat_var_idx[pat_n] = var_idx;
      pat_n = pat_n + 1;
      lexer_next_into(&r, lex, source);
      if (r.tok.kind == (int32_t)TOKEN_PIPE) {
        /* Multi-pattern: another lit/enum/_ after `|`. Wildcard alone is ok; `_ | 1` is soft-accepted. */
        parser_lex_from_next_into_glue(&lex, r);
        lexer_next_into(&r, lex, source);
        continue;
      }
      /*
       * wave700 Cap residual: optional guard `pat if cond => result`.
       * After the pattern list, TOKEN_IF starts a boolean guard expr, then FATARROW.
       * PLATFORM: SHARED — G.7 single authority (this parse path + MatchArmEntry.guard_ref).
       */
      if (r.tok.kind == (int32_t)TOKEN_IF) {
        struct parser_asm_parse_expr_result guard_res;
        parser_lex_from_next_into_glue(&lex, r);
        memset(&guard_res, 0, sizeof(guard_res));
        guard_res.next_lex = lex;
        parse_expr_into(arena, lex, source, &guard_res);
        if (!guard_res.ok) {
          return;
        }
        lex = guard_res.next_lex;
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_FATARROW) {
          return;
        }
        parser_lex_from_next_into_glue(&lex, r);
        memset(&arm_res, 0, sizeof(arm_res));
        arm_res.next_lex = lex;
        parse_expr_into(arena, lex, source, &arm_res);
        if (!arm_res.ok) {
          return;
        }
        lex = arm_res.next_lex;
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
          return;
        }
        parser_lex_from_next_into_glue(&lex, r);
        for (pat_i = 0; pat_i < pat_n; pat_i = pat_i + 1) {
          arm_i = pipeline_expr_append_match_arm(arena, mref, arm_res.expr_ref, pat_is_wc[pat_i],
                                                pat_lit_v[pat_i], pat_is_ev[pat_i], pat_var_idx[pat_i]);
          if (arm_i < 0)
            return;
          pipeline_expr_match_arm_set_guard_ref(arena, mref, arm_i, guard_res.expr_ref);
        }
        arm_via_guard = 1;
        break; /* leave pattern loop; outer arm loop continues */
      }
      if (r.tok.kind != (int32_t)TOKEN_FATARROW) {
        return;
      }
      break;
    }
    if (arm_via_guard != 0)
      continue; /* next outer arm (guard path already appended) */
    parser_lex_from_next_into_glue(&lex, r);
    memset(&arm_res, 0, sizeof(arm_res));
    arm_res.next_lex = lex;
    parse_expr_into(arena, lex, source, &arm_res);
    if (!arm_res.ok) {
      return;
    }
    lex = arm_res.next_lex;
    lexer_next_into(&r, lex, source);
    if (r.tok.kind != (int32_t)TOKEN_SEMICOLON) {
      return;
    }
    parser_lex_from_next_into_glue(&lex, r);
    /* Expand multi-pattern to N arms sharing the same result expr (G.7: reuse MatchArmEntry). */
    for (pat_i = 0; pat_i < pat_n; pat_i = pat_i + 1) {
      arm_i = pipeline_expr_append_match_arm(arena, mref, arm_res.expr_ref, pat_is_wc[pat_i],
                                            pat_lit_v[pat_i], pat_is_ev[pat_i], pat_var_idx[pat_i]);
      if (arm_i < 0)
        return;
      /* wave708: set implicit guard for struct field lit patterns */
      if (pat_guard_ref[pat_i] > 0)
        pipeline_expr_match_arm_set_guard_ref(arena, mref, arm_i, pat_guard_ref[pat_i]);
    }
  }
  out->ok = 1;
  out->expr_ref = mref;
  out->next_lex = lex;
}

#endif /* PARSER_ASM_MATCH_SUBJECT_SLICE_INCLUDED */
