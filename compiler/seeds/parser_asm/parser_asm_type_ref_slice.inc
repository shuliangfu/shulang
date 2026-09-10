/**
 * parser_asm_type_ref_slice.inc — parse_type_ref_for_arena_into / alloc_pointee C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 */
#ifndef PARSER_ASM_TYPE_REF_SLICE_INCLUDED
#define PARSER_ASM_TYPE_REF_SLICE_INCLUDED

/**
 * wave483 Cap residual pure: close one level of type-pos angle list.
 *
 * Nested generics spell `Name<Name<T>>` with adjacent `>>`. The lexer max-munch
 * path emits TOKEN_RSHIFT for `>>` (shift operator), so a bare TOKEN_GT check
 * fails mid-nest and the whole type_ref returns 0 (XP003 / dropped fn).
 *
 * Contract when the peek token ends a type-arg list:
 *   - TOKEN_GT: consume fully (one close).
 *   - TOKEN_RSHIFT: treat as two `>` — close this level and leave one `>` in the
 *     stream for the outer list (rewind next_lex.pos/col by 1). Same rule as
 *     C++/Rust nested-generic angle closing. Does **not** accept TOKEN_RSHIFT_EQ.
 *
 * @param peek lexer result already filled by lexer_next_into at the close site
 * @param lex_inout updated to the post-close lex state on success
 * @return 1 if closed, 0 if peek is neither GT nor RSHIFT
 * PLATFORM: SHARED type grammar — product type_ref path (this .inc).
 */
static int32_t parser_asm_type_angle_close_gt_or_rshift_c(struct parser_asm_lexer_result *peek,
                                                         struct parser_asm_lexer *lex_inout) {
  if (!peek || !lex_inout)
    return 0;
  if (peek->tok.kind == (int32_t)TOKEN_GT) {
    parser_asm_lex_from_result_val_into(lex_inout, *peek);
    return 1;
  }
  if (peek->tok.kind == (int32_t)TOKEN_RSHIFT) {
    /* next_lex is past both bytes of `>>`; leave the second `>` for the outer list. */
    *lex_inout = peek->next_lex;
    if (lex_inout->pos > 0)
      lex_inout->pos = lex_inout->pos - (size_t)1;
    if (lex_inout->col > 1)
      lex_inout->col = lex_inout->col - 1;
    return 1;
  }
  return 0;
}

/** 与 ast.x Type 布局一致。
 * wave577 Cap: name/region_label [64]→[128] must match arena Type (ast.x / pipeline_gen).
 * Wrong local sizeof tore by-value get/set on AArch64 → return type expected ?.
 * PLATFORM: SHARED — product type_ref path.
 */
struct ast_Type {
  int32_t kind;
  uint8_t name[128];
  int32_t name_len;
  int32_t elem_type_ref;
  int32_t array_size;
  uint8_t region_label[128];
  int32_t region_label_len;
};

/** 与 ast.x TypeKind 序一致。 */
enum {
  PARSER_ASM_TYPE_I32 = 0,
  PARSER_ASM_TYPE_BOOL = 1,
  PARSER_ASM_TYPE_U8 = 2,
  PARSER_ASM_TYPE_U32 = 3,
  PARSER_ASM_TYPE_U64 = 4,
  PARSER_ASM_TYPE_I64 = 5,
  PARSER_ASM_TYPE_USIZE = 6,
  PARSER_ASM_TYPE_ISIZE = 7,
  PARSER_ASM_TYPE_NAMED = 8,
  PARSER_ASM_TYPE_PTR = 9,
  PARSER_ASM_TYPE_ARRAY = 10,
  PARSER_ASM_TYPE_SLICE = 11,
  PARSER_ASM_TYPE_LINEAR = 12,
  PARSER_ASM_TYPE_VECTOR = 13,
  PARSER_ASM_TYPE_F32 = 14,
  PARSER_ASM_TYPE_F64 = 15,
  PARSER_ASM_TYPE_VOID = 16,
  /* TYPE_DYN fat trait object {data*, vtable*} — append after VOID (ord 17).
   * PLATFORM: SHARED type grammar. G.7 ≡ ast.x TypeKind. */
  PARSER_ASM_TYPE_DYN = 17,
  /* TYPE_FN (10.3.1): function(params...): Ret — append after DYN (ord 18).
   * elem_type_ref = return; array_size = n_params; params via type-arg sidecar.
   * PLATFORM: SHARED. G.7 ≡ ast.x TypeKind.TYPE_FN. */
  PARSER_ASM_TYPE_FN = 18
};

extern int32_t ast_ast_arena_type_alloc(void *arena);
extern struct ast_Type ast_arena_type_get(void *arena, int32_t ref);
extern void ast_arena_type_set(void *arena, int32_t ref, struct ast_Type t);
extern int32_t pipeline_type_ensure_by_kind_ord(void *arena, int32_t kind_ord);
extern int32_t parser_asm_stretch_type_ref_deep_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_type_ref_mega_full_deep_audit_c(struct parser_asm_lexer lex,
                                                                  struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_vector_type_ident_audit_c(struct parser_asm_slice_u8 *source, size_t token_start,
                                                          int32_t nlen);
extern int32_t parser_asm_stretch_linear_type_audit_c(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source);
extern int32_t parser_asm_stretch_array_type_bracket_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_slice_type_bracket_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_builtin_vec_token_audit_c(int32_t kind);

/**
 * Consume qualified type IDENT path `a.b.Type` into out[0..*out_len).
 * wave582 Cap residual: content cap 63→127 (Type.name[128] / AST Cap wave577).
 * Caller out must have capacity ≥128. PLATFORM: SHARED product type_ref path.
 */
int32_t parser_asm_consume_qualified_type_ident_name_c(struct parser_asm_slice_u8 *source,
                                                         struct parser_asm_lexer_result *r, uint8_t *out,
                                                         int32_t *out_len) {
  struct parser_asm_lexer saved_next;
  struct parser_asm_token saved_tok;
  size_t saved_start;
  int32_t seg_len;
  int32_t total;
  if (!r || !out || !out_len || !source)
    return -1;
  if (r->tok.kind != (int32_t)TOKEN_IDENT || r->tok.ident_len <= 0)
    return -1;
  seg_len = r->tok.ident_len;
  if (seg_len > 127)
    seg_len = 127;
  parser_asm_copy_slice_to_name64_at_end_slice_c(source, r->next_lex.pos, seg_len, out);
  total = seg_len;
  for (;;) {
    saved_next = r->next_lex;
    saved_tok = r->tok;
    saved_start = r->token_start;
    lexer_next_into(r, r->next_lex, source);
    if (r->tok.kind != (int32_t)TOKEN_DOT) {
      r->next_lex = saved_next;
      r->tok = saved_tok;
      r->token_start = saved_start;
      *out_len = total;
      return 0;
    }
    if (total >= 127)
      return -1;
    out[total] = 46;
    total++;
    lexer_next_into(r, r->next_lex, source);
    if (r->tok.kind != (int32_t)TOKEN_IDENT || r->tok.ident_len <= 0)
      return -1;
    seg_len = r->tok.ident_len;
    if (total + seg_len > 127)
      seg_len = 127 - total;
    if (seg_len <= 0)
      return -1;
    parser_asm_copy_slice_to_name64_at_end_slice_c(source, r->next_lex.pos, seg_len, &out[total]);
    total += seg_len;
  }
}

static int32_t parser_asm_parse_type_ref_impl_c(void *arena, struct parser_asm_lexer lex,
                                                struct parser_asm_slice_u8 *source,
                                                struct parser_asm_lexer *out_lex);

/**
 * True when IDENT spelling is contextual prefix `dyn` (docs/01 does not list
 * dyn as a keyword; same TOKEN_IDENT shape as `mut`). Used only to reject
 * the old `dyn Trait` spelling (P013); TYPE_DYN is produced by wrapping a
 * registered trait name.
 * PLATFORM: SHARED type grammar.
 */
static int32_t parser_asm_type_ref_ident_is_dyn_c(struct parser_asm_slice_u8 *source,
                                                  struct parser_asm_lexer_result *r) {
  uint8_t n[4];
  if (!source || !r)
    return 0;
  if (r->tok.kind != (int32_t)TOKEN_IDENT || r->tok.ident_len != 3)
    return 0;
  parser_asm_copy_slice_to_name64_slice_c(source, r->token_start, 3, n);
  return n[0] == 100 && n[1] == 121 && n[2] == 110; /* d y n */
}

/*
 * Skip-trait registry: defined in parser_asm_skip_tl_slice.inc (same product
 * TU, later include). pthin_type_ref hybrid resolves it from skip_tl glue.
 * PLATFORM: SHARED parse.
 */
extern int32_t xlang_skip_trait_is_registered_c(const uint8_t *trait_nm, int32_t trait_nlen);

/**
 * Allocate TYPE_DYN wrapping `inner_tr`. If inner is already TYPE_DYN,
 * return it (no nested fat). Copies the trait name from a TYPE_NAMED
 * inner for diagnostics / F2 impl lookup. G.7: single TYPE_DYN allocator
 * for type-position registered trait names.
 * @param arena void* — AST arena
 * @param inner_tr i32 — inner type_ref (trait NAMED, or already DYN)
 * @return i32 — TYPE_DYN type_ref, or inner_tr on alloc failure
 * PLATFORM: SHARED type grammar.
 */
static int32_t parser_asm_alloc_dyn_type_ref_c(void *arena, int32_t inner_tr) {
  struct ast_Type td;
  struct ast_Type ti;
  int32_t dyn_tr;
  int32_t ni;
  if (!arena || inner_tr <= 0)
    return inner_tr;
  ti = ast_arena_type_get(arena, inner_tr);
  if ((int32_t)ti.kind == PARSER_ASM_TYPE_DYN)
    return inner_tr;
  dyn_tr = ast_ast_arena_type_alloc(arena);
  if (dyn_tr == 0)
    return inner_tr;
  td = ast_arena_type_get(arena, dyn_tr);
  td.kind = PARSER_ASM_TYPE_DYN;
  td.elem_type_ref = inner_tr;
  td.array_size = 0;
  td.region_label_len = 0;
  td.name_len = 0;
  if ((int32_t)ti.kind == PARSER_ASM_TYPE_NAMED && ti.name_len > 0 && ti.name_len < 128) {
    for (ni = 0; ni < ti.name_len; ni++)
      td.name[ni] = ti.name[ni];
    td.name_len = ti.name_len;
  }
  ast_arena_type_set(arena, dyn_tr, td);
  return dyn_tr;
}

/**
 * If `named_tr` is TYPE_NAMED of a registered trait, wrap TYPE_DYN.
 * This is the only type-position producer of TYPE_DYN (write `Clone`,
 * not `dyn Clone`). Struct/alias names stay TYPE_NAMED.
 * @param arena void* — AST arena
 * @param named_tr i32 — candidate type_ref
 * @return i32 — TYPE_DYN or the original ref
 * PLATFORM: SHARED type grammar.
 */
static int32_t parser_asm_wrap_registered_trait_as_dyn_c(void *arena, int32_t named_tr) {
  struct ast_Type ti;
  if (!arena || named_tr <= 0)
    return named_tr;
  ti = ast_arena_type_get(arena, named_tr);
  if ((int32_t)ti.kind != PARSER_ASM_TYPE_NAMED || ti.name_len <= 0)
    return named_tr;
  if (xlang_skip_trait_is_registered_c(ti.name, ti.name_len) == 0)
    return named_tr;
  return parser_asm_alloc_dyn_type_ref_c(arena, named_tr);
}

/**
 * Token that may start a type after a peeled `dyn` / `impl` prefix.
 * PLATFORM: SHARED type grammar.
 */
static int32_t parser_asm_type_ref_token_starts_type_c(int32_t kind) {
  if (kind == (int32_t)TOKEN_IDENT || kind == (int32_t)TOKEN_STAR || kind == (int32_t)TOKEN_LBRACKET)
    return 1;
  if (kind == (int32_t)TOKEN_IMPL)
    return 1;
  /* 10.3.1: type-position `function(...): T` starts a TYPE_FN. */
  if (kind == (int32_t)TOKEN_FUNCTION)
    return 1;
  if (kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64 || kind == (int32_t)TOKEN_BOOL)
    return 1;
  if (kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32 || kind == (int32_t)TOKEN_U64)
    return 1;
  if (kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_ISIZE || kind == (int32_t)TOKEN_VOID)
    return 1;
  if (kind == (int32_t)TOKEN_F32 || kind == (int32_t)TOKEN_F64)
    return 1;
  if (kind == (int32_t)TOKEN_I32X4 || kind == (int32_t)TOKEN_I32X8 || kind == (int32_t)TOKEN_I32X16)
    return 1;
  if (kind == (int32_t)TOKEN_U32X4 || kind == (int32_t)TOKEN_U32X8 || kind == (int32_t)TOKEN_U32X16)
    return 1;
  if (kind == (int32_t)TOKEN_F32X4)
    return 1;
  return 0;
}

/** 将 lex 写入 out_lex（parse_type_ref 失败/成功路径共用）。 */
static void parser_asm_write_out_lex_c(struct parser_asm_lexer *out_lex, struct parser_asm_lexer lex) {
  if (!out_lex)
    return;
  out_lex->pos = lex.pos;
  out_lex->line = lex.line;
  out_lex->col = lex.col;
}

/** 分配并写入标量 Type 节点，返回 types 池 ref 或 0。 */
static int32_t parser_asm_arena_alloc_scalar_type_c(void *arena, int32_t type_kind) {
  int32_t ref;
  struct ast_Type t;
  ref = ast_ast_arena_type_alloc(arena);
  if (ref == 0)
    return 0;
  t = ast_arena_type_get(arena, ref);
  t.kind = type_kind;
  t.name_len = 0;
  t.elem_type_ref = 0;
  t.array_size = 0;
  t.region_label_len = 0;
  ast_arena_type_set(arena, ref, t);
  return ref;
}

/** 内建标量/void token → arena type ref。 */
static int32_t parser_asm_type_ref_from_builtin_token_c(void *arena, int32_t tok_kind) {
  switch (tok_kind) {
  case TOKEN_I32:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_I32);
  case TOKEN_I64:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_I64);
  case TOKEN_BOOL:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_BOOL);
  case TOKEN_U8:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_U8);
  case TOKEN_U32:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_U32);
  case TOKEN_U64:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_U64);
  case TOKEN_USIZE:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_USIZE);
  case TOKEN_ISIZE:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_ISIZE);
  case TOKEN_VOID:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_VOID);
  case TOKEN_F32:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_F32);
  case TOKEN_F64:
    return parser_asm_arena_alloc_scalar_type_c(arena, PARSER_ASM_TYPE_F64);
  default:
    return 0;
  }
}

/**
 * parser_alloc_vector_type_ref：分配 TYPE_VECTOR 节点（elem_ord 为 TypeKind 序数，lanes 为车道数）。
 */
int32_t parser_asm_alloc_vector_type_ref_c(void *arena, int32_t elem_ord, int32_t lanes) {
  int32_t elem_tr_v;
  int32_t vec_ref;
  struct ast_Type tv;
  elem_tr_v = pipeline_type_ensure_by_kind_ord(arena, elem_ord);
  if (elem_tr_v == 0)
    return 0;
  vec_ref = ast_ast_arena_type_alloc(arena);
  if (vec_ref == 0)
    return 0;
  tv = ast_arena_type_get(arena, vec_ref);
  tv.kind = PARSER_ASM_TYPE_VECTOR;
  tv.elem_type_ref = elem_tr_v;
  tv.array_size = lanes;
  tv.name_len = 0;
  tv.region_label_len = 0;
  ast_arena_type_set(arena, vec_ref, tv);
  return vec_ref;
}

/**
 * parser_vector_type_ref_from_ident_spelling：IDENT 拼写 i32x4 / Vec4f 等时返回 TYPE_VECTOR ref。
 */
int32_t parser_asm_vector_type_ref_from_ident_spelling_c(void *arena, struct parser_asm_slice_u8 *source,
                                                         struct parser_asm_lexer_result r) {
  int32_t nlen;
  uint8_t name_buf[64];
  nlen = r.tok.ident_len;
  if (nlen <= 0 || nlen > 63)
    return 0;
  parser_asm_copy_slice_to_name64_at_end_slice_c(source, r.next_lex.pos, nlen, name_buf);
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_vector_type_ident_audit_c(source, r.token_start, nlen));
  if (nlen == 5 && name_buf[0] == 105 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 52)
    return parser_asm_alloc_vector_type_ref_c(arena, 0, 4);
  if (nlen == 5 && name_buf[0] == 105 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 56)
    return parser_asm_alloc_vector_type_ref_c(arena, 0, 8);
  if (nlen == 6 && name_buf[0] == 105 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 49 && name_buf[4] == 54)
    return parser_asm_alloc_vector_type_ref_c(arena, 0, 16);
  if (nlen == 5 && name_buf[0] == 117 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 52)
    return parser_asm_alloc_vector_type_ref_c(arena, 3, 4);
  if (nlen == 5 && name_buf[0] == 117 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 56)
    return parser_asm_alloc_vector_type_ref_c(arena, 3, 8);
  if (nlen == 6 && name_buf[0] == 117 && name_buf[1] == 51 && name_buf[2] == 120 && name_buf[3] == 49 && name_buf[4] == 54)
    return parser_asm_alloc_vector_type_ref_c(arena, 3, 16);
  /* f32x4: elem_ord=14 (TYPE_F32), NOT 13 (TYPE_VECTOR). 13 made elem a
   * nonsensical TYPE_VECTOR so codegen fell back to int32_t. PLATFORM: SHARED. */
  if (nlen == 5 && name_buf[0] == 102 && name_buf[1] == 51 && name_buf[2] == 50 && name_buf[3] == 120 && name_buf[4] == 52)
    return parser_asm_alloc_vector_type_ref_c(arena, 14, 4);
  /* Vec4f: elem_ord=14 (TYPE_F32). Was 13 (TYPE_VECTOR) — same bug as f32x4. */
  if (nlen == 5 && name_buf[0] == 86 && name_buf[1] == 101 && name_buf[2] == 99 && name_buf[3] == 52 && name_buf[4] == 102)
    return parser_asm_alloc_vector_type_ref_c(arena, 14, 4);
  if (nlen == 5 && name_buf[0] == 86 && name_buf[1] == 101 && name_buf[2] == 99 && name_buf[3] == 56 && name_buf[4] == 105)
    return parser_asm_alloc_vector_type_ref_c(arena, 0, 8);
  return 0;
}

/**
 * alloc_pointee_type_ref_from_tok：在 r 指向「*」后首 token 时写入 arena 元素类型 ref。
 */
int32_t parser_asm_alloc_pointee_type_ref_from_tok_c(void *arena, struct parser_asm_slice_u8 *source,
                                                       struct parser_asm_lexer_result *r) {
  int32_t elem_ref;
  struct ast_Type te;
  int32_t qn_len;
  if (!r || !source)
    return 0;
  if (!parser_asm_is_pointee_type_token_c(r->tok.kind))
    return 0;
  elem_ref = ast_ast_arena_type_alloc(arena);
  if (elem_ref == 0)
    return 0;
  te = ast_arena_type_get(arena, elem_ref);
  te.elem_type_ref = 0;
  te.array_size = 0;
  te.name_len = 0;
  te.region_label_len = 0;
  if (r->tok.kind == (int32_t)TOKEN_IDENT) {
    te.kind = PARSER_ASM_TYPE_NAMED;
    qn_len = 0;
    if (parser_asm_consume_qualified_type_ident_name_c(source, r, te.name, &qn_len) != 0)
      return 0;
    te.name_len = qn_len;
  } else if (r->tok.kind == (int32_t)TOKEN_I32) {
    te.kind = PARSER_ASM_TYPE_I32;
  } else if (r->tok.kind == (int32_t)TOKEN_I64) {
    te.kind = PARSER_ASM_TYPE_I64;
  } else if (r->tok.kind == (int32_t)TOKEN_BOOL) {
    te.kind = PARSER_ASM_TYPE_BOOL;
  } else if (r->tok.kind == (int32_t)TOKEN_U8) {
    te.kind = PARSER_ASM_TYPE_U8;
  } else if (r->tok.kind == (int32_t)TOKEN_U32) {
    te.kind = PARSER_ASM_TYPE_U32;
  } else if (r->tok.kind == (int32_t)TOKEN_U64) {
    te.kind = PARSER_ASM_TYPE_U64;
  } else if (r->tok.kind == (int32_t)TOKEN_USIZE) {
    te.kind = PARSER_ASM_TYPE_USIZE;
  } else if (r->tok.kind == (int32_t)TOKEN_ISIZE) {
    te.kind = PARSER_ASM_TYPE_ISIZE;
  } else if (r->tok.kind == (int32_t)TOKEN_F32) {
    te.kind = PARSER_ASM_TYPE_F32;
  } else if (r->tok.kind == (int32_t)TOKEN_F64) {
    te.kind = PARSER_ASM_TYPE_F64;
  } else {
    te.kind = PARSER_ASM_TYPE_VOID;
  }
  ast_arena_type_set(arena, elem_ref, te);
  return elem_ref;
}

/**
 * 解析 `T[]<label>` 后缀：空 `[]` 为 slice，可选 `<ident>` 域标签（M-3）。
 * lex 须已消费 `[`；若下一 token 不是 `]` 则返回 0。
 */
static int32_t parser_asm_parse_postfix_slice_type_ref_c(void *arena, int32_t elem_tr,
                                                         struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source,
                                                         struct parser_asm_lexer *out_lex) {
  struct parser_asm_lexer_result r;
  int32_t slice_ref;
  struct ast_Type ts;
  if (!out_lex || elem_tr == 0)
    return 0;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_RBRACKET) {
    parser_asm_write_out_lex_c(out_lex, lex);
    return 0;
  }
  parser_asm_lex_from_result_val_into(&lex, r);
  slice_ref = ast_ast_arena_type_alloc(arena);
  if (slice_ref != 0) {
    ts = ast_arena_type_get(arena, slice_ref);
    ts.kind = PARSER_ASM_TYPE_SLICE;
    ts.elem_type_ref = elem_tr;
    ts.array_size = 0;
    ts.name_len = 0;
    ts.region_label_len = 0;
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_LT) {
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0 || r.tok.ident_len > 63) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, ts.region_label);
      ts.region_label_len = r.tok.ident_len;
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
      if (r.tok.kind != (int32_t)TOKEN_GT) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      parser_asm_lex_from_result_val_into(&lex, r);
    }
    ast_arena_type_set(arena, slice_ref, ts);
  }
  parser_asm_write_out_lex_c(out_lex, lex);
  return slice_ref;
}

/**
 * Parse postfix array/slice after an element type: `T[]` / `T[]<label>` / `T[N]` / `T[N][M]…`.
 * lex must already have consumed the element-type token. If the next token is not `[`,
 * *out_lex is left unchanged and elem_tr is returned.
 *
 * PLATFORM: SHARED — multi-dim postfix (wave356). Product spelling is C-style `T[N][M]`
 * (docs/02): outer N, inner M, same AST as prefix `[N][M]T`. Collect dimensions left-to-right,
 * then wrap from the rightmost dim so `i32[2][3]` ≡ `[2][3]i32` ≡ array-of-2 of array-of-3 of i32.
 * Cap 8 dims; empty `[]` remains slice only as the first postfix (`T[]`, not `T[N][]`).
 */
static int32_t parser_asm_parse_postfix_array_type_ref_c(void *arena, int32_t elem_tr,
                                                       struct parser_asm_lexer lex,
                                                       struct parser_asm_slice_u8 *source,
                                                       struct parser_asm_lexer *out_lex) {
  struct parser_asm_lexer_result r;
  int32_t dims[8];
  int32_t ndims;
  int32_t di;
  int32_t cur;
  int32_t arr_ref;
  struct ast_Type ta;
  if (!out_lex || elem_tr == 0)
    return elem_tr;
  lexer_next_into(&r, lex, source);
  if (r.tok.kind != (int32_t)TOKEN_LBRACKET) {
    parser_asm_write_out_lex_c(out_lex, lex);
    return elem_tr;
  }
  ndims = 0;
  for (;;) {
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    /** M-3: empty `[]` is slice only when it is the first postfix (`T[]` / `T[]<label>`). */
    if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
      if (ndims > 0) {
        /* `T[N][]` is not a product form — fail closed. */
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      return parser_asm_parse_postfix_slice_type_ref_c(arena, elem_tr, lex, source, out_lex);
    }
    if (r.tok.kind != (int32_t)TOKEN_INT || r.tok.int_val <= 0) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    if (ndims >= 8) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    dims[ndims] = r.tok.int_val;
    ndims = ndims + 1;
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    if (r.tok.kind != (int32_t)TOKEN_RBRACKET) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
    /* Peek next token without consuming; another `[` continues multi-dim. */
    lexer_next_into(&r, lex, source);
    if (r.tok.kind != (int32_t)TOKEN_LBRACKET)
      break;
  }
  /* Build right-to-left: dims[0]=outer … dims[ndims-1]=innermost (C / prefix form). */
  cur = elem_tr;
  di = ndims - 1;
  while (di >= 0) {
    arr_ref = ast_ast_arena_type_alloc(arena);
    if (arr_ref == 0) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    ta = ast_arena_type_get(arena, arr_ref);
    ta.kind = PARSER_ASM_TYPE_ARRAY;
    ta.elem_type_ref = cur;
    ta.array_size = dims[di];
    ta.name_len = 0;
    ta.region_label_len = 0;
    ast_arena_type_set(arena, arr_ref, ta);
    cur = arr_ref;
    di = di - 1;
  }
  parser_asm_write_out_lex_c(out_lex, lex);
  return cur;
}

/**
 * parse_type_ref_for_arena_into：从 lex 解析类型写入 arena，成功返回 type ref。
 */
static int32_t parser_asm_parse_type_ref_impl_c(void *arena, struct parser_asm_lexer lex,
                                                                struct parser_asm_slice_u8 *source,
                                                                struct parser_asm_lexer *out_lex) {
  struct parser_asm_lexer_result r;
  int32_t ptr_depth;
  int32_t elem_ref;
  int32_t type_ref_param;
  struct ast_Type t;
  int32_t slice_elem_tr;
  int32_t slice_ref;
  struct ast_Type ts;
  int32_t asz;
  int32_t elem_tr;
  int32_t arr_ref;
  struct ast_Type ta;
  int32_t elem_ord;
  int32_t lanes;
  int32_t vec_ref;
  int32_t type_ref_scalar;
  uint8_t linear_spell[6];
  uint8_t linear_buf[64];
  int32_t li;
  int32_t linear_match;
  int32_t inner_linear_tr;
  int32_t linear_ref;
  struct ast_Type tl;
  int32_t vec_ident_ref;
  int32_t qn_len_tr;
  if (!source || !out_lex)
    return 0;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_deep_audit_c(&lex, source));
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_type_ref_mega_full_deep_audit_c(lex, source));
  lexer_next_into(&r, lex, source);
  /*
   * 4.2.2 impl type prefix + one TYPE_DYN producer (G.7).
   *
   * TYPE_DYN (ord 17) is produced only by wrapping a registered trait
   * name in type position (`let x: Clone = a`). Host-C emits
   * `struct xlang_dyn_obj` fat {data*, vtable*} — not incomplete
   * `struct Trait` (empty-struct paint ban).
   *
   * `dyn Trait` is not a second producer (AI / users write the trait
   * name). Prior peel wrapped TYPE_DYN from the `dyn` prefix; that
   * path is removed. Seeing `dyn` followed by a type is P013 hard-fail
   * (sticky, so unused `take(x: dyn Clone)` cannot vanish while main
   * stays green). Bare `dyn` (no following type) stays TYPE_NAMED "dyn".
   *
   * `impl Trait` stays peeled TYPE_NAMED trait (static path; not fat)
   * unless the inner IDENT is a registered trait (then implicit DYN,
   * same as bare `Trait`).
   * PLATFORM: SHARED type grammar.
   */
  if (parser_asm_type_ref_ident_is_dyn_c(source, &r)) {
    struct parser_asm_lexer_result peek_pref;
    lexer_next_into(&peek_pref, r.next_lex, source);
    if (parser_asm_type_ref_token_starts_type_c(peek_pref.tok.kind)) {
      extern void parser_report_dyn_prefix_p013_c(int32_t line, int32_t col);
      parser_report_dyn_prefix_p013_c((int32_t)r.tok.line, (int32_t)r.tok.col);
      parser_asm_write_out_lex_c(out_lex, r.next_lex);
      return 0;
    }
  }
  if (r.tok.kind == (int32_t)TOKEN_IMPL) {
    struct parser_asm_lexer_result peek_impl;
    lexer_next_into(&peek_impl, r.next_lex, source);
    if (parser_asm_type_ref_token_starts_type_c(peek_impl.tok.kind))
      return parser_asm_parse_type_ref_impl_c(arena, r.next_lex, source, out_lex);
  }
  /*
   * 10.3.1 TYPE_FN (ord 18): type-position `function(T0, T1, ...): Ret`.
   * X grammar (docs/ai/anti-patterns H02): keyword is `function`, return uses
   * `: Ret` — not Rust `fn` / `->`. Storage (G.7 reuse wave467 sidecar):
   *   - kind = TYPE_FN
   *   - elem_type_ref = return type
   *   - array_size = n_params
   *   - each param via pipeline_type_append_type_arg
   * Empty param list `function(): i32` is valid (n_params=0).
   * PLATFORM: SHARED type grammar.
   */
  if (r.tok.kind == (int32_t)TOKEN_FUNCTION) {
    struct parser_asm_lexer_result peek_fn;
    int32_t fn_ref;
    int32_t n_params;
    int32_t param_tr;
    int32_t ret_tr;
    struct ast_Type tf;
    extern int32_t pipeline_type_append_type_arg(void *arena, int32_t type_ref, int32_t arg_ref);
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&peek_fn, lex, source);
    if (peek_fn.tok.kind != (int32_t)TOKEN_LPAREN) {
      /* Bare `function` is not a type (decl keyword only). */
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    parser_asm_lex_from_result_val_into(&lex, peek_fn);
    fn_ref = ast_ast_arena_type_alloc(arena);
    if (fn_ref == 0) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    n_params = 0;
    lexer_next_into(&peek_fn, lex, source);
    if (peek_fn.tok.kind != (int32_t)TOKEN_RPAREN) {
      /* At least one param type; leave lex before first type token. */
      for (;;) {
        param_tr = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
        if (param_tr == 0) {
          parser_asm_write_out_lex_c(out_lex, lex);
          return 0;
        }
        (void)pipeline_type_append_type_arg(arena, fn_ref, param_tr);
        n_params = n_params + 1;
        lexer_next_into(&peek_fn, lex, source);
        if (peek_fn.tok.kind == (int32_t)TOKEN_COMMA) {
          parser_asm_lex_from_result_val_into(&lex, peek_fn);
          continue;
        }
        if (peek_fn.tok.kind == (int32_t)TOKEN_RPAREN) {
          parser_asm_lex_from_result_val_into(&lex, peek_fn);
          break;
        }
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
    } else {
      parser_asm_lex_from_result_val_into(&lex, peek_fn);
    }
    lexer_next_into(&peek_fn, lex, source);
    if (peek_fn.tok.kind != (int32_t)TOKEN_COLON) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    parser_asm_lex_from_result_val_into(&lex, peek_fn);
    ret_tr = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
    if (ret_tr == 0) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    tf = ast_arena_type_get(arena, fn_ref);
    tf.kind = PARSER_ASM_TYPE_FN;
    tf.elem_type_ref = ret_tr;
    tf.array_size = n_params;
    tf.name_len = 0;
    tf.region_label_len = 0;
    ast_arena_type_set(arena, fn_ref, tf);
    parser_asm_write_out_lex_c(out_lex, lex);
    return fn_ref;
  }
  if (r.tok.kind == (int32_t)TOKEN_STAR) {
    ptr_depth = 0;
    while (r.tok.kind == (int32_t)TOKEN_STAR) {
      ++ptr_depth;
      parser_asm_lex_from_result_val_into(&lex, r);
      lexer_next_into(&r, lex, source);
    }
    if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
      /*
       * wave435: *[]T / *[N]T → PTR to SLICE/ARRAY of T (type syntax: [] binds
       * tighter than *). The inner slice/array is parsed recursively (it owns
       * the `[`), then PTR is wrapped around it. The C-style postfix *T[N]
       * (ARRAY of PTR to T, scalar base T) is preserved for the scalar path
       * below. PLATFORM: SHARED parse.
       */
      elem_ref = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
      if (elem_ref == 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
    } else if (parser_asm_type_ref_ident_is_dyn_c(source, &r) || r.tok.kind == (int32_t)TOKEN_IMPL) {
      /*
       * Same-layer: `*dyn Trait` (P013 reject via recurse) / `*impl Trait`.
       * alloc_pointee only accepts IDENT as TYPE_NAMED, so a leftover
       * Clone after `*dyn` would drop the function. Recurse so the
       * prefix handler above reports P013 (or peels `impl`). `lex` sits
       * after the stars, before the pointee token. PLATFORM: SHARED.
       */
      elem_ref = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
      if (elem_ref == 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
    } else {
      elem_ref = parser_asm_alloc_pointee_type_ref_from_tok_c(arena, source, &r);
      if (elem_ref == 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      parser_asm_lex_from_result_val_into(&lex, r);
    }
    while (ptr_depth > 0) {
      type_ref_param = ast_ast_arena_type_alloc(arena);
      if (type_ref_param == 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      t = ast_arena_type_get(arena, type_ref_param);
      t.kind = PARSER_ASM_TYPE_PTR;
      t.elem_type_ref = elem_ref;
      t.name_len = 0;
      t.array_size = 0;
      t.region_label_len = 0;
      ast_arena_type_set(arena, type_ref_param, t);
      elem_ref = type_ref_param;
      --ptr_depth;
    }
    /** C 风格后缀：*T[N] 为 N 个 T 指针的固定数组（如 *u8[2]）。 */
    return parser_asm_parse_postfix_array_type_ref_c(arena, elem_ref, lex, source, out_lex);
  }
  if (r.tok.kind == (int32_t)TOKEN_LBRACKET) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_slice_type_bracket_audit_c(&lex, source));
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_array_type_bracket_audit_c(&lex, source));
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    if (r.tok.kind == (int32_t)TOKEN_RBRACKET) {
      parser_asm_lex_from_result_val_into(&lex, r);
      slice_elem_tr = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
      if (slice_elem_tr == 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      slice_ref = ast_ast_arena_type_alloc(arena);
      if (slice_ref != 0) {
        ts = ast_arena_type_get(arena, slice_ref);
        ts.kind = PARSER_ASM_TYPE_SLICE;
        ts.elem_type_ref = slice_elem_tr;
        ts.array_size = 0;
        ts.name_len = 0;
        ts.region_label_len = 0;
        lexer_next_into(&r, lex, source);
        if (r.tok.kind == (int32_t)TOKEN_LT) {
          parser_asm_lex_from_result_val_into(&lex, r);
          lexer_next_into(&r, lex, source);
          if (r.tok.kind != (int32_t)TOKEN_IDENT || r.tok.ident_len <= 0 || r.tok.ident_len > 63) {
            parser_asm_write_out_lex_c(out_lex, lex);
            return 0;
          }
          parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, r.tok.ident_len, ts.region_label);
          ts.region_label_len = r.tok.ident_len;
          parser_asm_lex_from_result_val_into(&lex, r);
          lexer_next_into(&r, lex, source);
          if (r.tok.kind != (int32_t)TOKEN_GT) {
            parser_asm_write_out_lex_c(out_lex, lex);
            return 0;
          }
          parser_asm_lex_from_result_val_into(&lex, r);
        }
        ast_arena_type_set(arena, slice_ref, ts);
      }
      parser_asm_write_out_lex_c(out_lex, lex);
      return slice_ref;
    }
    if (r.tok.kind != (int32_t)TOKEN_INT) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    asz = r.tok.int_val;
    parser_asm_lex_from_result_val_into(&lex, r);
    lexer_next_into(&r, lex, source);
    if (r.tok.kind != (int32_t)TOKEN_RBRACKET) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    parser_asm_lex_from_result_val_into(&lex, r);
    elem_tr = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
    if (elem_tr == 0) {
      parser_asm_write_out_lex_c(out_lex, lex);
      return 0;
    }
    arr_ref = ast_ast_arena_type_alloc(arena);
    if (arr_ref != 0) {
      ta = ast_arena_type_get(arena, arr_ref);
      ta.kind = PARSER_ASM_TYPE_ARRAY;
      ta.elem_type_ref = elem_tr;
      ta.array_size = asz;
      ta.name_len = 0;
      ta.region_label_len = 0;
      ast_arena_type_set(arena, arr_ref, ta);
    }
    parser_asm_write_out_lex_c(out_lex, lex);
    return arr_ref;
  }
  if (r.tok.kind == (int32_t)TOKEN_I32X4 || r.tok.kind == (int32_t)TOKEN_I32X8 || r.tok.kind == (int32_t)TOKEN_I32X16
      || r.tok.kind == (int32_t)TOKEN_U32X4 || r.tok.kind == (int32_t)TOKEN_U32X8 || r.tok.kind == (int32_t)TOKEN_U32X16
      || r.tok.kind == (int32_t)TOKEN_F32X4) {
    PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_builtin_vec_token_audit_c(r.tok.kind));
    elem_ord = 0;
    lanes = 4;
    if (r.tok.kind == (int32_t)TOKEN_U32X4 || r.tok.kind == (int32_t)TOKEN_U32X8
        || r.tok.kind == (int32_t)TOKEN_U32X16)
      elem_ord = 3;
    if (r.tok.kind == (int32_t)TOKEN_F32X4)
      elem_ord = 13;
    if (r.tok.kind == (int32_t)TOKEN_I32X8 || r.tok.kind == (int32_t)TOKEN_U32X8)
      lanes = 8;
    if (r.tok.kind == (int32_t)TOKEN_I32X16 || r.tok.kind == (int32_t)TOKEN_U32X16)
      lanes = 16;
    vec_ref = parser_asm_alloc_vector_type_ref_c(arena, elem_ord, lanes);
    parser_asm_lex_from_result_val_into(&lex, r);
    parser_asm_write_out_lex_c(out_lex, lex);
    return vec_ref;
  }
  if (r.tok.kind == (int32_t)TOKEN_I32 || r.tok.kind == (int32_t)TOKEN_BOOL || r.tok.kind == (int32_t)TOKEN_I64
      || r.tok.kind == (int32_t)TOKEN_U8 || r.tok.kind == (int32_t)TOKEN_U32 || r.tok.kind == (int32_t)TOKEN_U64
      || r.tok.kind == (int32_t)TOKEN_USIZE || r.tok.kind == (int32_t)TOKEN_ISIZE || r.tok.kind == (int32_t)TOKEN_VOID
      || r.tok.kind == (int32_t)TOKEN_F32 || r.tok.kind == (int32_t)TOKEN_F64) {
    type_ref_scalar = parser_asm_type_ref_from_builtin_token_c(arena, r.tok.kind);
    parser_asm_lex_from_result_val_into(&lex, r);
    return parser_asm_parse_postfix_array_type_ref_c(arena, type_ref_scalar, lex, source, out_lex);
  }
  if (r.tok.kind == (int32_t)TOKEN_IDENT) {
    if (r.tok.ident_len == 6) {
      linear_spell[0] = 76;
      linear_spell[1] = 105;
      linear_spell[2] = 110;
      linear_spell[3] = 101;
      linear_spell[4] = 97;
      linear_spell[5] = 114;
      parser_asm_copy_slice_to_name64_slice_c(source, r.token_start, 6, linear_buf);
      linear_match = 1;
      for (li = 0; li < 6; li++) {
        if (linear_buf[li] != linear_spell[li])
          linear_match = 0;
      }
      if (linear_match) {
        PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_linear_type_audit_c(lex, source));
        parser_asm_lex_from_result_val_into(&lex, r);
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_LPAREN) {
          parser_asm_write_out_lex_c(out_lex, lex);
          return 0;
        }
        parser_asm_lex_from_result_val_into(&lex, r);
        inner_linear_tr = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
        if (inner_linear_tr == 0) {
          parser_asm_write_out_lex_c(out_lex, lex);
          return 0;
        }
        lexer_next_into(&r, lex, source);
        if (r.tok.kind != (int32_t)TOKEN_RPAREN) {
          parser_asm_write_out_lex_c(out_lex, lex);
          return 0;
        }
        parser_asm_lex_from_result_val_into(&lex, r);
        linear_ref = ast_ast_arena_type_alloc(arena);
        if (linear_ref != 0) {
          tl = ast_arena_type_get(arena, linear_ref);
          tl.kind = PARSER_ASM_TYPE_LINEAR;
          tl.elem_type_ref = inner_linear_tr;
          tl.array_size = 0;
          tl.name_len = 0;
          tl.region_label_len = 0;
          ast_arena_type_set(arena, linear_ref, tl);
        }
        parser_asm_write_out_lex_c(out_lex, lex);
        return linear_ref;
      }
    }
    vec_ident_ref = parser_asm_vector_type_ref_from_ident_spelling_c(arena, source, r);
    if (vec_ident_ref == 0 && r.tok.kind == (int32_t)TOKEN_IDENT && r.tok.ident_len > 0)
      PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_vector_type_ident_audit_c(source, r.token_start, r.tok.ident_len));
    if (vec_ident_ref != 0) {
      parser_asm_lex_from_result_val_into(&lex, r);
      parser_asm_write_out_lex_c(out_lex, lex);
      return vec_ident_ref;
    }
    type_ref_param = ast_ast_arena_type_alloc(arena);
    if (type_ref_param != 0) {
      t = ast_arena_type_get(arena, type_ref_param);
      t.kind = PARSER_ASM_TYPE_NAMED;
      qn_len_tr = 0;
      if (parser_asm_consume_qualified_type_ident_name_c(source, &r, t.name, &qn_len_tr) != 0) {
        parser_asm_write_out_lex_c(out_lex, lex);
        return 0;
      }
      t.name_len = qn_len_tr;
      t.elem_type_ref = 0;
      t.array_size = 0;
      t.region_label_len = 0;
      ast_arena_type_set(arena, type_ref_param, t);
    }
    parser_asm_lex_from_result_val_into(&lex, r);
    /*
     * wave466/467 Cap residual pure: type-position `Name<T>` / `Name<T,U>` (docs/02).
     * Prior: IDENT became TYPE_NAMED then postfix only saw `[` — bare `<` after the
     * name failed the surrounding param/let type parse (XP003 out_len=0) for
     * `let w: Wrap<i32>` / `w: Wrap<i32>`. Call-site turbofish (primary) already
     * parsed angles; type_ref had no twin path (G.7 single authority here).
     *
     * Contract: after TYPE_NAMED, optional `< type (, type)* >`.
     *   - first type arg → elem_type_ref (wave466 single-arg mono)
     *   - array_size → top-level arg count
     *   - wave467: all args also in sidecar via pipeline_type_append_type_arg
     * Nested angles work via recursive parse_type_ref. PLATFORM: SHARED type grammar.
     */
    {
      struct parser_asm_lexer_result peek_ta;
      int32_t first_ta;
      int32_t n_ta;
      int32_t ta_ref;
      extern int32_t pipeline_type_append_type_arg(void *arena, int32_t type_ref, int32_t arg_ref);
      lexer_next_into(&peek_ta, lex, source);
      if (peek_ta.tok.kind == (int32_t)TOKEN_LT) {
        parser_asm_lex_from_result_val_into(&lex, peek_ta);
        first_ta = 0;
        n_ta = 0;
        for (;;) {
          ta_ref = parser_asm_parse_type_ref_impl_c(arena, lex, source, &lex);
          if (ta_ref == 0) {
            parser_asm_write_out_lex_c(out_lex, lex);
            return 0;
          }
          if (n_ta == 0)
            first_ta = ta_ref;
          if (type_ref_param != 0 && ta_ref > 0)
            (void)pipeline_type_append_type_arg(arena, type_ref_param, ta_ref);
          n_ta = n_ta + 1;
          lexer_next_into(&peek_ta, lex, source);
          if (peek_ta.tok.kind == (int32_t)TOKEN_COMMA) {
            parser_asm_lex_from_result_val_into(&lex, peek_ta);
            continue;
          }
          /* wave483: TOKEN_GT or nested `>>` (TOKEN_RSHIFT) closes this angle level. */
          if (parser_asm_type_angle_close_gt_or_rshift_c(&peek_ta, &lex) != 0)
            break;
          parser_asm_write_out_lex_c(out_lex, lex);
          return 0;
        }
        if (type_ref_param != 0 && first_ta > 0) {
          t = ast_arena_type_get(arena, type_ref_param);
          t.elem_type_ref = first_ta;
          t.array_size = n_ta;
          ast_arena_type_set(arena, type_ref_param, t);
        }
      }
      /* If next was not `<`, leave lex unadvanced so postfix sees `[` / end. */
    }
    /*
     * Bare trait name in type position (`let x: Clone = a`) is TYPE_DYN
     * without writing `dyn`. Registered skip-trait names wrap the same
     * fat as `dyn Trait`. Struct / alias IDENT stays TYPE_NAMED.
     * Wrap after `<T>` so generic `Wrap<i32>` is not treated as a trait.
     * PLATFORM: SHARED type grammar. G.7 complete this IDENT path.
     */
    type_ref_param = parser_asm_wrap_registered_trait_as_dyn_c(arena, type_ref_param);
    return parser_asm_parse_postfix_array_type_ref_c(arena, type_ref_param, lex, source, out_lex);
  }
  parser_asm_write_out_lex_c(out_lex, lex);
  return 0;
}

/** parse_type_ref_for_arena_into slice 路径公开入口。 */
int32_t parser_asm_parse_type_ref_for_arena_into_slice_c(void *arena, struct parser_asm_lexer lex,
                                                         struct parser_asm_slice_u8 *source,
                                                         struct parser_asm_lexer *out_lex) {
  return parser_asm_parse_type_ref_impl_c(arena, lex, source, out_lex);
}

#endif /* PARSER_ASM_TYPE_REF_SLICE_INCLUDED */
