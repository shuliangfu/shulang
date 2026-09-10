/**
 * parser_asm_library_slice.inc — parse_one_function_library C 实现。
 *
 * 由 parser_asm_thin_c.c #include；勿单独编译。
 * 先调 parser_asm_parse_one_function_library_scan_slice_c 扫描 token，再建 AST / module func 槽。
 * 依赖同 TU 内 parser_asm_type_ref_slice.inc 的 struct ast_Type / PARSER_ASM_TYPE_*。
 */
#ifndef PARSER_ASM_LIBRARY_SLICE_INCLUDED
#define PARSER_ASM_LIBRARY_SLICE_INCLUDED

/** 与 ast.x Block 布局一致（library 形态仅写 labeled return）。 */
#ifndef PARSER_ASM_AST_BLOCK_DEFINED
#define PARSER_ASM_AST_BLOCK_DEFINED
struct ast_Block {
  int32_t const_base;
  int32_t num_consts;
  int32_t let_base;
  int32_t num_lets;
  int32_t num_early_lets;
  int32_t loop_base;
  int32_t num_loops;
  int32_t for_loop_base;
  int32_t num_for_loops;
  int32_t if_base;
  int32_t num_if_stmts;
  int32_t region_base;
  int32_t num_regions;
  int32_t defer_base;
  int32_t num_defers;
  int32_t labeled_base;
  int32_t num_labeled_stmts;
  int32_t expr_stmt_base;
  int32_t num_expr_stmts;
  int32_t final_expr_ref;
  int32_t stmt_order_base;
  int32_t num_stmt_order;
  int32_t parent_block_ref;
};
#endif

/** 与 ast.x ExprKind 序一致（library 形态用到的子集；勿与 primary_slice 枚举混用）。 */
enum {
  PARSER_ASM_LIB_EXPR_VAR = 3,
  PARSER_ASM_LIB_EXPR_EQ = 14,
  PARSER_ASM_LIB_EXPR_FIELD_ACCESS = 44,
  PARSER_ASM_LIB_EXPR_ENUM_VARIANT = 50
};

extern int32_t ast_ast_arena_type_alloc(void *arena);
extern struct ast_Type ast_ast_arena_type_get(void *arena, int32_t ref);
extern void ast_ast_arena_type_set(void *arena, int32_t ref, struct ast_Type t);
extern int32_t ast_ast_arena_expr_alloc(void *arena);
extern struct ast_Expr ast_ast_arena_expr_get(void *arena, int32_t ref);
extern void ast_ast_arena_expr_set(void *arena, int32_t ref, struct ast_Expr e);
extern int32_t ast_ast_arena_block_alloc(void *arena);
extern struct ast_Block ast_ast_arena_block_get(void *arena, int32_t ref);
extern void ast_ast_arena_block_set(void *arena, int32_t ref, struct ast_Block b);
extern int32_t ast_pipeline_block_append_labeled(void *arena, int32_t br, int32_t label_len, int32_t is_goto,
                                                 int32_t goto_target_len, int32_t return_expr_ref);
extern int32_t pipeline_module_struct_layout_alloc(void *module);
extern void pipeline_module_struct_layout_set_name(void *module, int32_t idx, uint8_t *bytes, int32_t len);
extern void pipeline_module_struct_layout_set_num_fields(void *module, int32_t idx, int32_t nf);
extern void pipeline_module_struct_layout_set_field(void *module, int32_t layout_idx, int32_t j, uint8_t *fname,
                                                    int32_t fname_len, int32_t type_ref, int32_t field_off);
extern int32_t pipeline_module_func_alloc_slot(void *module);
extern void pipeline_module_func_name_write(void *module, int32_t fi, uint8_t *name_bytes, int32_t name_len);
extern void pipeline_module_func_set_num_params(void *module, int32_t fi, int32_t n);
extern void pipeline_module_func_param_write(void *module, int32_t func_index, int32_t param_index,
                                             uint8_t *name_bytes, int32_t name_len, int32_t type_ref);
extern void pipeline_module_func_set_return_type(void *module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(void *module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(void *module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(void *module, int32_t fi, int32_t is_extern);

extern int32_t parser_asm_parse_one_function_library_scan_slice_c(
    struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
    struct parser_asm_library_parse_scan_result *result);
extern int32_t parser_asm_struct_layout_name_exists_arr_c(void *module, uint8_t *nm, int32_t nlen);
extern int32_t parser_asm_stretch_library_fn_shape_audit_c(void *lex_inout, void *source);

/** 与 parser.x ast.expr_init_match_enum 一致：清零 match 占位字段。 */
static void parser_asm_lib_expr_init_match_c(struct ast_Expr *e) {
  if (!e)
    return;
  e->match_matched_ref = 0;
  e->match_arm_base = 0;
  e->match_num_arms = 0;
}

/** 失败快照：ok=false，next_lex 为调用方传入 lex。 */
static struct parser_asm_library_parse_result parser_asm_library_fail_c(struct parser_asm_lexer lex) {
  struct parser_asm_library_parse_result out;
  memset(&out, 0, sizeof(out));
  out.next_lex = lex;
  return out;
}

/**
 * 解析库函数单参 bool return 形态并写入 module/arena；与 parser.x parse_one_function_library 一致。
 */
struct parser_asm_library_parse_result parser_asm_parse_one_function_library_slice_c(
    void *arena, void *module, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {
  struct parser_asm_library_parse_scan_result scan;
  struct parser_asm_library_parse_result fail;
  struct ast_Type bt;
  struct ast_Type tt;
  struct ast_Expr ve;
  struct ast_Expr fe;
  struct ast_Expr ene;
  struct ast_Expr eqe;
  struct ast_Block b;
  int32_t bool_type_ref;
  int32_t token_type_ref;
  int32_t var_ref;
  int32_t field_ref;
  int32_t enum_ref;
  int32_t eq_ref;
  int32_t block_ref;
  int32_t fi_lib;
  int32_t ti;
  int32_t vi;
  int32_t fi;
  int32_t idx;

  fail = parser_asm_library_fail_c(lex);
  if (!arena || !module || !source)
    return fail;
  PARSER_ASM_STRETCH_AUDIT_CALL(parser_asm_stretch_library_fn_shape_audit_c(&lex, source));
  memset(&scan, 0, sizeof(scan));
  if (parser_asm_parse_one_function_library_scan_slice_c(lex, source, &scan) == 0) {
    fail.next_lex = scan.next_lex;
    return fail;
  }

  bool_type_ref = ast_ast_arena_type_alloc(arena);
  if (bool_type_ref == 0)
    return fail;
  bt = ast_ast_arena_type_get(arena, bool_type_ref);
  bt.kind = PARSER_ASM_TYPE_BOOL;
  bt.name_len = 0;
  bt.elem_type_ref = 0;
  bt.array_size = 0;
  ast_ast_arena_type_set(arena, bool_type_ref, bt);

  token_type_ref = ast_ast_arena_type_alloc(arena);
  if (token_type_ref == 0)
    return fail;
  tt = ast_ast_arena_type_get(arena, token_type_ref);
  tt.kind = PARSER_ASM_TYPE_NAMED;
  tt.name_len = scan.param_type_len;
  for (ti = 0; ti < 64; ti++) {
    if (ti < scan.param_type_len)
      tt.name[ti] = scan.param_type_name[ti];
    else
      tt.name[ti] = 0;
  }
  tt.elem_type_ref = 0;
  tt.array_size = 0;
  ast_ast_arena_type_set(arena, token_type_ref, tt);

  var_ref = ast_ast_arena_expr_alloc(arena);
  if (var_ref == 0)
    return fail;
  ve = ast_ast_arena_expr_get(arena, var_ref);
  ve.kind = PARSER_ASM_LIB_EXPR_VAR;
  ve.resolved_type_ref = token_type_ref;
  ve.line = 0;
  ve.col = 0;
  ve.var_name_len = scan.param_name_len;
  for (vi = 0; vi < 64; vi++) {
    if (vi < 32)
      ve.var_name[vi] = scan.param_name[vi];
    else
      ve.var_name[vi] = 0;
  }
  parser_asm_lib_expr_init_match_c(&ve);
  ve.field_access_base_ref = 0;
  ve.field_access_field_len = 0;
  ve.field_access_is_enum_variant = 0;
  ve.field_access_offset = 0;
  ast_ast_arena_expr_set(arena, var_ref, ve);

  field_ref = ast_ast_arena_expr_alloc(arena);
  if (field_ref == 0)
    return fail;
  fe = ast_ast_arena_expr_get(arena, field_ref);
  fe.kind = PARSER_ASM_LIB_EXPR_FIELD_ACCESS;
  fe.resolved_type_ref = 0;
  fe.line = 0;
  fe.col = 0;
  fe.field_access_base_ref = var_ref;
  fe.field_access_field_len = scan.field_len;
  for (fi = 0; fi < 64; fi++) {
    if (fi < scan.field_len)
      fe.field_access_field_name[fi] = scan.field_name[fi];
    else
      fe.field_access_field_name[fi] = 0;
  }
  fe.field_access_is_enum_variant = 0;
  fe.field_access_offset = 0;
  parser_asm_lib_expr_init_match_c(&fe);
  fe.binop_left_ref = 0;
  fe.binop_right_ref = 0;
  ast_ast_arena_expr_set(arena, field_ref, fe);

  enum_ref = ast_ast_arena_expr_alloc(arena);
  if (enum_ref == 0)
    return fail;
  ene = ast_ast_arena_expr_get(arena, enum_ref);
  ene.kind = PARSER_ASM_LIB_EXPR_ENUM_VARIANT;
  ene.resolved_type_ref = 0;
  ene.line = 0;
  ene.col = 0;
  ene.enum_variant_tag = 0;
  parser_asm_lib_expr_init_match_c(&ene);
  ene.field_access_base_ref = 0;
  ene.field_access_field_len = 0;
  ast_ast_arena_expr_set(arena, enum_ref, ene);

  eq_ref = ast_ast_arena_expr_alloc(arena);
  if (eq_ref == 0)
    return fail;
  eqe = ast_ast_arena_expr_get(arena, eq_ref);
  eqe.kind = PARSER_ASM_LIB_EXPR_EQ;
  eqe.resolved_type_ref = bool_type_ref;
  eqe.line = 0;
  eqe.col = 0;
  eqe.binop_left_ref = field_ref;
  eqe.binop_right_ref = enum_ref;
  parser_asm_lib_expr_init_match_c(&eqe);
  eqe.field_access_base_ref = 0;
  eqe.field_access_field_len = 0;
  ast_ast_arena_expr_set(arena, eq_ref, eqe);

  block_ref = ast_ast_arena_block_alloc(arena);
  if (block_ref == 0)
    return fail;
  b = ast_ast_arena_block_get(arena, block_ref);
  b.num_consts = 0;
  b.num_lets = 0;
  b.num_early_lets = 0;
  b.num_loops = 0;
  b.num_for_loops = 0;
  b.num_if_stmts = 0;
  b.num_defers = 0;
  if (ast_pipeline_block_append_labeled(arena, block_ref, 0, 0, 0, eq_ref) < 0)
    return fail;
  b = ast_ast_arena_block_get(arena, block_ref);
  b.num_expr_stmts = 0;
  b.final_expr_ref = 0;
  b.num_stmt_order = 0;
  ast_ast_arena_block_set(arena, block_ref, b);

  if (scan.field_len > 0 &&
      parser_asm_struct_layout_name_exists_arr_c(module, scan.param_type_name, scan.param_type_len) == 0) {
    idx = pipeline_module_struct_layout_alloc(module);
    if (idx >= 0) {
      pipeline_module_struct_layout_set_name(module, idx, scan.param_type_name, scan.param_type_len);
      pipeline_module_struct_layout_set_num_fields(module, idx, 1);
      pipeline_module_struct_layout_set_field(module, idx, 0, scan.field_name, scan.field_len, 0, 0);
    }
  }

  fi_lib = pipeline_module_func_alloc_slot(module);
  if (fi_lib < 0)
    return fail;
  pipeline_module_func_name_write(module, fi_lib, scan.name, scan.name_len);
  pipeline_module_func_set_num_params(module, fi_lib, 1);
  pipeline_module_func_param_write(module, fi_lib, 0, scan.param_name, scan.param_name_len, token_type_ref);
  pipeline_module_func_set_return_type(module, fi_lib, bool_type_ref);
  pipeline_module_func_set_body_ref(module, fi_lib, block_ref);
  pipeline_module_func_set_body_expr_ref(module, fi_lib, 0);
  pipeline_module_func_set_is_extern(module, fi_lib, 0);

  memset(&fail, 0, sizeof(fail));
  fail.ok = 1;
  fail.next_lex = scan.next_lex;
  fail.name_len = scan.name_len;
  memcpy(fail.name, scan.name, (size_t)scan.name_len);
  return fail;
}

#endif /* PARSER_ASM_LIBRARY_SLICE_INCLUDED */
