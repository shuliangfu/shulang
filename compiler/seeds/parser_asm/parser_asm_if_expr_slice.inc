/**
 * parser_asm_if_expr_slice.inc — parse_if_expr_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * if 条件表达式：if (cond) { block } [ else { block } | else if … ] → EXPR_IF。
 */
#ifndef PARSER_ASM_IF_EXPR_SLICE_INCLUDED
#define PARSER_ASM_IF_EXPR_SLICE_INCLUDED

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *source);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parser_parse_cond_expr_into_glue(void *arena, struct parser_asm_lexer lex_start,
                                             struct parser_asm_slice_u8 *source,
                                             struct parser_asm_parse_expr_result *out);
extern int32_t parser_advance_past_cond_rparen_into_glue(struct parser_asm_lexer_result *r_out,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source);
extern struct parser_asm_lexer parser_lex_at_token_from_result_glue(struct parser_asm_lexer_result r);
extern void parser_parse_if_expr_into_glue(void *arena, struct parser_asm_lexer lex_at_if,
                                           struct parser_asm_slice_u8 *source, int32_t type_ref,
                                           struct parser_asm_parse_expr_result *out);
extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
extern int32_t parser_asm_stretch_parse_cond_expr_deep_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_if_expr_deep_audit_c(struct parser_asm_lexer lex_at_if,
                                                       struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_if_expr_branch_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_else_if_chain_audit_c(void *lex_inout, void *source);

/** expr_set_common_zeros：与 parser.x 字段清零顺序一致。 */
static void parser_asm_if_expr_common_zeros_c(struct ast_Expr *e) {
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
 * wrap_block_ref_as_expr：块 ref 包成 EXPR_BLOCK 节点（if 表达式 then/else 分支）。
 */
static int32_t parser_asm_wrap_block_ref_as_expr_c(void *arena, int32_t block_ref, int32_t type_ref) {
  int32_t ref;
  struct ast_Expr e;
  if (block_ref == 0)
    return 0;
  ref = ast_ast_arena_expr_alloc(arena);
  if (ref == 0)
    return 0;
  e = ast_ast_arena_expr_get(arena, ref);
  parser_asm_if_expr_common_zeros_c(&e);
  e.kind = 26; /* EXPR_BLOCK */
  e.block_ref = block_ref;
  e.resolved_type_ref = type_ref;
  e.line = 0;
  e.col = 0;
  ast_ast_arena_expr_set(arena, ref, e);
  return ref;
}

/**
 * parse_if_expr_into：lex_at_if 须指向 if；成功写 out.expr_ref 为 EXPR_IF。
 */
void parser_asm_parse_if_expr_into_c(void *arena, struct parser_asm_lexer lex_at_if, struct parser_asm_slice_u8 *source,
                                     int32_t type_ref, struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer lex_cur;
  struct parser_asm_lexer_result r;
  struct parser_asm_parse_expr_result cond_res;
  int32_t cond_ref;
  struct parser_asm_parse_block_result then_res;
  int32_t then_expr_ref;
  int32_t else_expr_ref;
  struct parser_asm_parse_block_result else_res;
  struct parser_asm_lexer elif_lex;
  struct parser_asm_parse_expr_result elif_res;
  int32_t if_ref;
  struct ast_Expr ie;
  if (!arena || !source || !out)
    return;
  out->ok = 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_expr_branch_audit_c(&lex_at_if, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_if_expr_deep_audit_c(lex_at_if, source));
  lexer_next_into(&r, lex_at_if, source);
  if (r.tok.kind == (int32_t)TOKEN_IF)
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_parse_cond_expr_deep_audit_c(&r.next_lex, source));
  lex_cur = lex_at_if;
  lexer_next_into(&r, lex_cur, source);
  if (r.tok.kind != (int32_t)TOKEN_IF)
    return;
  parser_lex_from_next_into_glue(&lex_cur, r);
  lexer_next_into(&r, lex_cur, source);
  /**
   * wave361/wave650: docs/03 `if cond { then } else { else }` — parens optional.
   * wave650: do NOT strip leading `(` — same root as if_stmt (inclusive grouping
   * so `(x >> 2) != 4` is one cond expr). PLATFORM: SHARED — G.7 single if-expr
   * cond path (expr primary owns parens).
   */
  lex_cur = parser_lex_at_token_from_result_glue(r);
  memset(&cond_res, 0, sizeof(cond_res));
  cond_res.next_lex = lex_cur;
  parser_parse_cond_expr_into_glue(arena, lex_cur, source, &cond_res);
  if (!cond_res.ok)
    return;
  cond_ref = cond_res.expr_ref;
  lex_cur = cond_res.next_lex;
  if (parser_advance_past_cond_rparen_into_glue(&r, lex_cur, source) == 0)
    return;
  if (r.tok.kind != (int32_t)TOKEN_LBRACE)
    return;
  lex_cur = r.next_lex;
  memset(&then_res, 0, sizeof(then_res));
  then_res.next_lex = lex_cur;
  parser_parse_block_into(arena, lex_cur, source, type_ref, &then_res);
  if (!then_res.ok)
    return;
  then_expr_ref = parser_asm_wrap_block_ref_as_expr_c(arena, then_res.block_ref, type_ref);
  if (then_expr_ref == 0)
    return;
  else_expr_ref = 0;
  lex_cur = then_res.next_lex;
  lexer_next_into(&r, lex_cur, source);
  if (r.tok.kind == (int32_t)TOKEN_ELSE) {
    parser_lex_from_next_into_glue(&lex_cur, r);
    lexer_next_into(&r, lex_cur, source);
    if (r.tok.kind == (int32_t)TOKEN_IF) {
      elif_lex = parser_lex_at_token_from_result_glue(r);
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_else_if_chain_audit_c(&elif_lex, source));
      memset(&elif_res, 0, sizeof(elif_res));
      elif_res.next_lex = elif_lex;
      parser_parse_if_expr_into_glue(arena, elif_lex, source, type_ref, &elif_res);
      if (!elif_res.ok)
        return;
      else_expr_ref = elif_res.expr_ref;
      lex_cur = elif_res.next_lex;
    } else if (r.tok.kind == (int32_t)TOKEN_LBRACE) {
      lex_cur = r.next_lex;
      memset(&else_res, 0, sizeof(else_res));
      else_res.next_lex = lex_cur;
      parser_parse_block_into(arena, lex_cur, source, type_ref, &else_res);
      if (!else_res.ok)
        return;
      else_expr_ref = parser_asm_wrap_block_ref_as_expr_c(arena, else_res.block_ref, type_ref);
      if (else_expr_ref == 0)
        return;
      lex_cur = else_res.next_lex;
    } else {
      return;
    }
  }
  if_ref = ast_ast_arena_expr_alloc(arena);
  if (if_ref == 0)
    return;
  ie = ast_ast_arena_expr_get(arena, if_ref);
  parser_asm_if_expr_common_zeros_c(&ie);
  ie.kind = 25; /* EXPR_IF */
  ie.resolved_type_ref = type_ref;
  ie.line = 0;
  ie.col = 0;
  ie.if_cond_ref = cond_ref;
  ie.if_then_ref = then_expr_ref;
  ie.if_else_ref = else_expr_ref;
  ast_ast_arena_expr_set(arena, if_ref, ie);
  out->ok = 1;
  out->expr_ref = if_ref;
  out->next_lex = lex_cur;
}

#endif /* PARSER_ASM_IF_EXPR_SLICE_INCLUDED */
