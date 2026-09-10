/**
 * parser_asm_type_alias_slice.inc — parse_one_type_alias_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 顶层 type 别名「type Alias = TargetType ;」；Target 经 parse_type_ref 完整语法。
 */
#ifndef PARSER_ASM_TYPE_ALIAS_SLICE_INCLUDED
#define PARSER_ASM_TYPE_ALIAS_SLICE_INCLUDED

/** 与 parser.x TypeAliasResult（allow(padding)）布局一致。 */
struct parser_asm_type_alias_result {
  int32_t ok;
  uint8_t _pad[4];
  struct parser_asm_lexer next_lex;
};

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *data);
extern void parser_lex_from_lexer_result_ptr_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result *r);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern int32_t pipeline_module_type_alias_alloc(void *module);
extern void pipeline_module_type_alias_set(void *module, int32_t idx, uint8_t *name, int32_t name_len,
                                           int32_t target_type_ref);
extern int32_t parser_asm_stretch_function_name_audit_c(const uint8_t *name, int32_t name_len);
extern int32_t parser_asm_stretch_type_ref_deep_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                struct parser_asm_lexer *out_lex);
extern void parser_asm_copy_slice_to_name64_slice_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                    int32_t name_len, uint8_t *name_buf);

/**
 * parse_one_type_alias_into：解析单条顶层 type 别名，写入 module 侧车与 out。
 * lex 位于消费掉 `type` 关键字之后。
 */
/**
 * Parse one top-level `type Alias = Target;`.
 * wave582 Cap residual: Alias name content ≤127 (TypeAliasEntry.name[128] + AST Cap).
 * Prior name_buf[64] + name_len>63 rejected long aliases while type_ref still
 * truncated use-sites to 63 → typeck "expected NAMED, found i32".
 * PLATFORM: SHARED product type_alias path (this .inc → thin glue).
 */
void parser_asm_parse_one_type_alias_into_slice_c(void *arena, void *module, struct parser_asm_lexer lex,
                                                  struct parser_asm_slice_u8 *source,
                                                  struct parser_asm_type_alias_result *out) {
  struct parser_asm_lexer_result r;
  uint8_t name_buf[128];
  int32_t name_len;
  int32_t target_ref;
  int32_t alias_ix;
  if (!out)
    return;
  out->ok = 0;
  if (!arena || !module || !source)
    return;
  memset(&r, 0, sizeof(r));
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_IDENT)
    return;
  name_len = r.tok.ident_len;
  if (name_len <= 0 || name_len > 127)
    return;
  parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, name_len, name_buf);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_name_audit_c(name_buf, name_len));
  parser_lex_from_lexer_result_ptr_into(&lex, &r);
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_ASSIGN)
    return;
  parser_lex_from_lexer_result_ptr_into(&lex, &r);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_deep_audit_c(&lex, source));
  target_ref = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex, source, &lex);
  if (target_ref == 0)
    return;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_SEMICOLON)
    return;
  alias_ix = pipeline_module_type_alias_alloc(module);
  if (alias_ix < 0)
    return;
  pipeline_module_type_alias_set(module, alias_ix, name_buf, name_len, target_ref);
  parser_lex_from_next_into_glue(&out->next_lex, r);
  out->ok = 1;
}

#endif /* PARSER_ASM_TYPE_ALIAS_SLICE_INCLUDED */
