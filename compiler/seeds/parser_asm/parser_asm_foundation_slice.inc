/* parser_asm_foundation_slice.inc — G-02f-329 P20 expr foundation
 * Hybrid: XLANG_PTHIN_FOUNDATION_FROM_X via seeds/pthin_foundation.from_x.c
 * arena_expr_get / arena_expr_set / expr_set_common_zeros
 * lexer_init is in the seed TU (and default mega wrap) separately.
 */
#ifndef PARSER_ASM_FOUNDATION_SLICE_INC
#define PARSER_ASM_FOUNDATION_SLICE_INC

/** pipeline ast_Expr ↔ parser_asm_ast_expr 布局一致时 memcpy 桥接。 */
struct parser_asm_ast_expr parser_asm_arena_expr_get_c(void *arena, int32_t ref) {
  struct parser_asm_ast_expr out;
  struct ast_Expr e;
  e = ast_arena_expr_get(arena, ref);
  memcpy(&out, &e, sizeof(out));
  return out;
}

static void parser_asm_arena_expr_set_c(void *arena, int32_t ref, struct parser_asm_ast_expr ae) {
  struct ast_Expr e;
  const char *trace_name;
  const char *trace_type;
  int trace_ty;
  int trace_hit;
  memcpy(&e, &ae, sizeof(e));
  trace_name = getenv("XLANG_TRACE_EXPR_NAME");
  trace_type = getenv("XLANG_TRACE_TYPE_REF");
  trace_ty = 0;
  trace_hit = 0;
  if (trace_name && *trace_name && e.var_name_len > 0) {
    size_t want_len = strlen(trace_name);
    if ((int32_t)want_len == e.var_name_len && want_len < sizeof(e.var_name) &&
        memcmp(e.var_name, trace_name, want_len) == 0)
      trace_hit = 1;
  }
  if (trace_type && *trace_type) {
    trace_ty = atoi(trace_type);
    if (trace_ty != 0 && e.resolved_type_ref == trace_ty)
      trace_hit = 1;
  }
  if (trace_hit) {
    /* Cap residual 9.5.3: Cap IO debug print (was libc fprintf; PLATFORM: SHARED). */
    { char _db[384]; int _dn = snprintf(_db, sizeof _db,
        "note: parser expr watch: expr=%d kind=%d block=%d ty=%d left=%d right=%d name_len=%d name=%.*s\n",
        (int)ref, (int)e.kind, (int)e.block_ref, (int)e.resolved_type_ref,
        (int)e.binop_left_ref, (int)e.binop_right_ref, (int)e.var_name_len,
        (int)e.var_name_len, (const char *)e.var_name);
      if (_dn > 0) (void)xlang_io_write(2, _db, (size_t)_dn); }
  }
  ast_arena_expr_set(arena, ref, e);
}

/**
 * expr_set_common_zeros C 实现：与 parser.x 字段清零顺序一致；match 占位同 ast.expr_init_match_enum。
 * hybrid 跨 TU：P10 glue 以 extern 引用，故非 static（G-02f-326）。
 * （P4 expr seeds 仍可保留本地 static 副本，不冲突。）
 */
void parser_asm_expr_set_common_zeros_c(struct parser_asm_ast_expr *e) {
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
  e->match_arm_base = 0;
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
  e->call_num_type_args = 0;
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

#endif /* PARSER_ASM_FOUNDATION_SLICE_INC */
