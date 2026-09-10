/**
 * parser_asm_as_suffix_slice.inc — parse_as_suffix_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 与 parser.x parse_as_suffix_into 一致：`as type` 后缀链。
 * After `as`, the full type_ref parser is the only matcher (`[]T` / `[N]T` /
 * `*T` / scalars / NAMED / SIMD tokens). PLATFORM: SHARED parse.
 */
#ifndef PARSER_ASM_AS_SUFFIX_SLICE_INCLUDED
#define PARSER_ASM_AS_SUFFIX_SLICE_INCLUDED

/** 与 ast.x ExprKind 序一致（含 EXPR_BINOP；TRY_PROPAGATE 在 EXPR_SPAWN 之后）。 */
enum {
  PARSER_ASM_EXPR_AS = 54
};
#ifndef PARSER_ASM_EXPR_TRY_PROPAGATE
#define PARSER_ASM_EXPR_TRY_PROPAGATE 58
#endif

extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                               struct parser_asm_slice_u8 *source,
                                                               struct parser_asm_lexer *out_lex);

/** parser_asm_thin_c.c 在 #include 前定义（同 TU）。 */
struct parser_asm_ast_expr parser_asm_arena_expr_get_c(void *arena, int32_t ref);
static void parser_asm_arena_expr_set_c(void *arena, int32_t ref, struct parser_asm_ast_expr ae);
void parser_asm_expr_set_common_zeros_c(struct parser_asm_ast_expr *e);
/* parser_asm_lex_from_result_val_into: provided by P1 lex_skip (non-static) */
extern int32_t parser_asm_stretch_as_suffix_chain_audit_c(void *lex_inout, void *source);

/**
 * parse_as_suffix_into：解析零个或多个 postfix 后缀（`?` Result 传播、`as type`；假定 out 已由 primary 填充）。
 */
void parser_asm_parse_as_suffix_into_slice_c(void *arena, struct parser_asm_slice_u8 *source,
                                             struct parser_asm_parse_expr_result *out) {
  struct parser_asm_lexer lex_cur;
  struct parser_asm_lexer_result r;
  int32_t type_ref;
  int32_t inner_ref;
  int32_t as_ref;
  int32_t try_ref;
  struct parser_asm_ast_expr ae;
  if (!out || !out->ok || !source)
    return;
  lex_cur = out->next_lex;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_as_suffix_chain_audit_c(&lex_cur, source));
  for (;;) {
    lexer_next_into(&r, lex_cur, source);
    if (r.tok.kind == (int32_t)TOKEN_QUESTION) {
      struct parser_asm_lexer_result rpeek;
      struct parser_asm_lexer lex_after_q;
      /** 三元 `cond ? then : else` 的 `?` 须留给 ternary 层；仅 `?` 后紧跟 `;` `)` 等为 ERR-01 传播。 */
      parser_asm_lex_from_result_val_into(&lex_after_q, r);
      lexer_next_into(&rpeek, lex_after_q, source);
      if (rpeek.tok.kind != (int32_t)TOKEN_SEMICOLON && rpeek.tok.kind != (int32_t)TOKEN_RPAREN &&
          rpeek.tok.kind != (int32_t)TOKEN_RBRACE && rpeek.tok.kind != (int32_t)TOKEN_COMMA &&
          rpeek.tok.kind != (int32_t)TOKEN_RBRACKET) {
        out->next_lex = lex_cur;
        return;
      }
      inner_ref = out->expr_ref;
      try_ref = ast_ast_arena_expr_alloc(arena);
      if (try_ref == 0) {
        out->ok = 0;
        return;
      }
      ae = parser_asm_arena_expr_get_c(arena, try_ref);
      ae.kind = PARSER_ASM_EXPR_TRY_PROPAGATE;
      ae.line = 0;
      ae.col = 0;
      parser_asm_expr_set_common_zeros_c(&ae);
      ae.unary_operand_ref = inner_ref;
      parser_asm_arena_expr_set_c(arena, try_ref, ae);
      out->expr_ref = try_ref;
      out->next_lex = rpeek.next_lex;
      return;
    }
    if (r.tok.kind != (int32_t)TOKEN_AS) {
      out->next_lex = lex_cur;
      return;
    }
    parser_asm_lex_from_result_val_into(&lex_cur, r);
    /*
     * After `as`, parse the full type (same authority as formals / wave438 STAR).
     * Prior: only TOKEN_STAR delegated to type_ref; a half table handled
     * scalars + IDENT and rejected `[]T` / `[N]T` / SIMD tokens →
     * parse_expr.ok=0 → body_lets drop → P001 (`let x = [10,32] as []i32`).
     * G.7: complete this suffix; no second type matcher.
     * lex_cur now sits at the type-start token. type_ref consumes the whole
     * type and writes the post-type position back into lex_cur. Sync
     * r.next_lex so the loop tail `lex_cur = r.next_lex` stays consistent.
     * PLATFORM: SHARED parse.
     */
    type_ref = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex_cur, source, &lex_cur);
    if (type_ref == 0) {
      out->ok = 0;
      return;
    }
    r.next_lex = lex_cur;
    inner_ref = out->expr_ref;
    as_ref = ast_ast_arena_expr_alloc(arena);
    if (as_ref == 0) {
      out->ok = 0;
      return;
    }
    ae = parser_asm_arena_expr_get_c(arena, as_ref);
    ae.kind = PARSER_ASM_EXPR_AS;
    ae.line = 0;
    ae.col = 0;
    parser_asm_expr_set_common_zeros_c(&ae);
    ae.as_operand_ref = inner_ref;
    ae.as_target_type_ref = type_ref;
    parser_asm_arena_expr_set_c(arena, as_ref, ae);
    out->expr_ref = as_ref;
    lex_cur = r.next_lex;
  }
}

#endif /* PARSER_ASM_AS_SUFFIX_SLICE_INCLUDED */
