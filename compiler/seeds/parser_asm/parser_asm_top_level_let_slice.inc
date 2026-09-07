/**
 * parser_asm_top_level_let_slice.inc — parse_one_top_level_let_into C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 顶层 let/const「ident : type = expr ;」路径；expr 经 parse_expr_into 回调 X mega。
 */
#ifndef PARSER_ASM_TOP_LEVEL_LET_SLICE_INCLUDED
#define PARSER_ASM_TOP_LEVEL_LET_SLICE_INCLUDED

/** 与 parser.x TopLevelLetResult（allow(padding)）布局一致。 */
struct parser_asm_top_level_let_result {
  int32_t ok;
  uint8_t _pad[4];
  struct parser_asm_lexer next_lex;
};

/** 与 parser_asm_body_let_slice.inc ParseExprResult 布局一致（body_let 已先 include）。 */

extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *data);
extern void parser_lex_from_lexer_result_ptr_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result *r);
extern void parser_lex_from_next_into_glue(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
extern void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                            struct parser_asm_parse_expr_result *out);
extern int32_t ast_ast_arena_type_alloc(void *arena);
extern struct ast_Type ast_arena_type_get(void *arena, int32_t ref);
extern void ast_arena_type_set(void *arena, int32_t ref, struct ast_Type t);
extern int32_t pipeline_module_top_level_let_alloc(void *module);
extern void pipeline_module_top_level_let_set(void *module, int32_t idx, uint8_t *name, int32_t name_len,
                                              int32_t type_ref, int32_t init_ref, int32_t is_const);
/* 9.6.3: pure module top-level-let name scan (thin .x authority in
 * runtime_pipeline_abi.x, seed twin in runtime_pipeline_abi.from_x.c). */
extern int32_t asm_module_top_level_let_name_exists(void *module, uint8_t *name, int32_t name_len);
extern int32_t parser_asm_stretch_top_level_let_probe_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                                                        int32_t is_const);
extern int32_t parser_asm_stretch_function_name_audit_c(const uint8_t *name, int32_t name_len);
extern int32_t parser_asm_stretch_type_ref_deep_audit_c(struct parser_asm_lexer lex,
                                                        struct parser_asm_slice_u8 *source);
/** 与 function/struct 字段共用：支持 u8[N]、*T、slice 等完整类型语法。 */
extern int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                struct parser_asm_lexer *out_lex);

/** Copy ident into name_buf (content up to 127; buffer capacity 128). wave581 Cap residual. */
static void parser_asm_top_level_let_copy_ident_name_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                       int32_t name_len, uint8_t *name_buf) {
  if (!name_buf || name_len <= 0)
    return;
  parser_asm_copy_slice_to_name64_slice_c(source, token_start, name_len, name_buf);
}

/**
 * parse_one_top_level_let_into：解析单条顶层 let/const，写入 module 侧车与 out。
 */
void parser_asm_parse_one_top_level_let_into_slice_c(void *arena, void *module, struct parser_asm_lexer lex,
                                                     struct parser_asm_slice_u8 *source, int32_t is_const,
                                                     struct parser_asm_top_level_let_result *out) {
  struct parser_asm_lexer_result r;
  struct parser_asm_parse_expr_result expr_res;
  /* wave581 Cap residual: top-level let/const name content cap 127. */
  uint8_t name_buf[128];
  int32_t name_len;
  int32_t name_line;
  int32_t name_col;
  int32_t type_ref;
  int32_t tl_ix;
  int32_t ic;
  if (!out)
    return;
  out->ok = 0;
  if (!arena || !module || !source)
    return;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_top_level_let_probe_c(lex, source, is_const));
  memset(&r, 0, sizeof(r));
  memset(&expr_res, 0, sizeof(expr_res));
  memset(name_buf, 0, sizeof(name_buf));
  lexer_next_into(&r, lex, source);
  /* wave385: optional IDENT "mut" after let (not const). PLATFORM: SHARED G.7 with parse_body_lets. */
  if (is_const == 0 && r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len == 3) {
    size_t mut_start = r.token_start;
    if (source->data && mut_start + 2 < source->length && source->data[mut_start] == 109 &&
        source->data[mut_start + 1] == 117 && source->data[mut_start + 2] == 116) {
      parser_lex_from_lexer_result_ptr_into(&lex, &r);
      lexer_next_into(&r, lex, source);
    }
  }
  if (r.tok.kind != (int32_t)TOKEN_IDENT) {
    /* Keyword as top-level let/const name: same silent-drop class as body-lets
     * `let run` (P001 / missing _main). G.7: P014 at this IDENT gate.
     * PLATFORM: SHARED parse. */
    extern void parser_report_keyword_binding_p014_c(int32_t line, int32_t col);
    parser_report_keyword_binding_p014_c((int32_t)r.tok.line, (int32_t)r.tok.col);
    return;
  }
  name_len = r.tok.ident_len;
  /* 9.6.3: binding-name token position, kept for the P012 dup diagnostic. */
  name_line = (int32_t)r.tok.line;
  name_col = (int32_t)r.tok.col;
  /* wave581 Cap residual: content cap 127 (was 63). PLATFORM: SHARED parse. */
  if (name_len <= 0 || name_len > 127)
    return;
  parser_asm_top_level_let_copy_ident_name_c(source, r.token_start, name_len, name_buf);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_function_name_audit_c(name_buf, name_len));
  parser_lex_from_lexer_result_ptr_into(&lex, &r);
  lexer_next_into(&r, lex, source);
  /* wave423: const may omit `: Type` when next is `=` (type_ref=0 → typeck infer).
   * let still requires `: Type` (docs/06 ban inference). PLATFORM: SHARED parse. */
  type_ref = 0;
  if (r.tok.kind == (int32_t)TOKEN_COLON) {
    parser_lex_from_lexer_result_ptr_into(&lex, &r);
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_deep_audit_c(lex, source));
    type_ref = parser_asm_parse_type_ref_for_arena_into_slice_c(arena, lex, source, &lex);
    if (type_ref == 0)
      return;
    lexer_next_into(&r, lex, source);
  } else if (is_const != 0 && r.tok.kind == (int32_t)TOKEN_ASSIGN) {
    /* const name = init — type inference; leave type_ref=0. */
  } else {
    /* wave422: P010 illegal untyped let / const without `=` (G.7 twin of body lets). */
    extern void parser_report_untyped_binding_p010_c(int32_t line, int32_t col, int32_t is_let);
    parser_report_untyped_binding_p010_c((int32_t)r.tok.line, (int32_t)r.tok.col, is_const == 0 ? 1 : 0);
    return;
  }
  if (r.tok.kind != (int32_t)TOKEN_ASSIGN)
    return;
  parser_lex_from_lexer_result_ptr_into(&lex, &r);
  expr_res.ok = 0;
  expr_res.expr_ref = 0;
  expr_res.next_lex = lex;
  parse_expr_into(arena, lex, source, &expr_res);
  if (!expr_res.ok)
    return;
  lex = expr_res.next_lex;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_SEMICOLON)
    return;
  /*
   * 9.6.3: P012 duplicate top-level binding — two module-level lets with one
   * name used to compile silently, the second registration winning (q6 probe).
   * Root fix at this registration authority: reject BEFORE alloc so no phantom
   * entry lands. Sticky g_parser_sig_type_hard makes parse_into_buf abort
   * (ok=-2). kind=2 = module top-level let/const (0 = param, 1 = struct field).
   * PLATFORM: SHARED parse.
   */
  if (asm_module_top_level_let_name_exists(module, name_buf, name_len) != 0) {
    extern void parser_report_duplicate_name_p012_c(int32_t line, int32_t col, int32_t kind);
    parser_report_duplicate_name_p012_c(name_line, name_col, 2);
    return;
  }
  tl_ix = pipeline_module_top_level_let_alloc(module);
  if (tl_ix < 0)
    return;
  ic = is_const != 0 ? 1 : 0;
  pipeline_module_top_level_let_set(module, tl_ix, name_buf, name_len, type_ref, expr_res.expr_ref, ic);
  parser_lex_from_next_into_glue(&out->next_lex, r);
  out->ok = 1;
}

#endif /* PARSER_ASM_TOP_LEVEL_LET_SLICE_INCLUDED */
