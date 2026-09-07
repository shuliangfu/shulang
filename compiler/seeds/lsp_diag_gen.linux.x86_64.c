/* generated (single-file with deps) */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: CRASH_EVIDENCE path → Cap snprintf */
/* G.7: Cap after stdio for compiler-only gen seed pin crash evidence. */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_io_cap.h>   /* Cap residual 9.5.3: xlang_io_write / xlang_io_open_write */
#include <xlang_proc_cap.h> /* Cap residual 9.5.3: xlang_proc_close_fd (single close authority) */
#include <string.h>
#include <math.h>
/* wave245 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED orch / host getenv residual via single face.
 * Compiler-only gen seed pin (CRASH_EVIDENCE inline) — not user program template
 * (runtime.from_x.c fprintf CRASH_EVIDENCE user C templates use link_abi_getenv since wave254). */
extern char *link_abi_getenv(const char *name);
extern int getpid(void);
static inline void xlang_crash_evidence_collect_inline(int has_msg, int msg_val) {
  const char *_ev = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  char _note[192];
  if (!_ev || _ev[0] != '1') return;
  int _pid = (int)getpid();
  { int _n = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val, _pid);
    if (_n > 0) (void)xlang_io_write(2, _note, (size_t)_n); }
  { const char *_dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (_dir && _dir[0]) { char _p[1024]; snprintf(_p, sizeof _p, "%s/xlang-crash-%d.txt", _dir, _pid);
      { int _fd = xlang_io_open_write(_p);
        if (_fd >= 0) { char _body[160];
          int _bl = snprintf(_body, sizeof _body, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, _pid);
          if (_bl > 0) (void)xlang_io_write(_fd, _body, (size_t)_bl);
          (void)xlang_proc_close_fd(_fd);
          { int _bn = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] bundle=%s\n", _p);
            if (_bn > 0) (void)xlang_io_write(2, _note, (size_t)_bn); } } } } }
}
static inline void xlang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static inline void xlang_panic_(int has_msg, int msg_val) {
  xlang_crash_evidence_collect_inline(has_msg, msg_val);
  if (has_msg) { char _mb[32]; int _mn = snprintf(_mb, sizeof _mb, "%d\n", msg_val);
    if (_mn > 0) (void)xlang_io_write(2, _mb, (size_t)_mn); }
  abort();
}
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[128]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; uint8_t region_label[128]; int32_t region_label_len; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t var_name[128]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_base; int32_t match_num_arms; int32_t field_access_base_ref; uint8_t field_access_field_name[128]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t field_access_soa_stride; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_base; int32_t call_num_args; int32_t call_num_type_args; int32_t method_call_base_ref; uint8_t method_call_name[128]; int32_t method_call_name_len; int32_t method_call_arg_base; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[128]; int32_t struct_lit_struct_name_len; int32_t struct_lit_field_base; int32_t struct_lit_num_fields; int32_t array_lit_elem_base; int32_t array_lit_num_elems; int32_t float_bits_lo; int32_t float_bits_hi; int32_t enum_variant_tag; int32_t as_operand_ref; int32_t as_target_type_ref; int32_t call_resolved_func_index; int32_t call_resolved_dep_index; };
struct ast_ConstDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_IfStmt { int32_t cond_ref; int32_t then_body_ref; int32_t else_body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[128]; int32_t label_len; int32_t is_goto; uint8_t goto_target[128]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { int32_t const_base; int32_t num_consts; int32_t let_base; int32_t num_lets; int32_t num_early_lets; int32_t loop_base; int32_t num_loops; int32_t for_loop_base; int32_t num_for_loops; int32_t if_base; int32_t num_if_stmts; int32_t region_base; int32_t num_regions; int32_t defer_base; int32_t num_defers; int32_t labeled_base; int32_t num_labeled_stmts; int32_t expr_stmt_base; int32_t num_expr_stmts; int32_t final_expr_ref; int32_t stmt_order_base; int32_t num_stmt_order; int32_t parent_block_ref; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[128]; int32_t name_len; int32_t param_base; int32_t num_params; int32_t num_generic_params; int32_t return_type_ref; int32_t body_ref; int32_t body_expr_ref; int32_t is_extern; int32_t is_async; int32_t is_used; int32_t is_naked; int32_t is_entry; int32_t is_no_mangle; int32_t is_interrupt; int32_t abi_kind; int32_t is_variadic; int32_t is_export; };
struct ast_StructLayout { uint8_t name[128]; int32_t name_len; int32_t field_base; int32_t num_fields; int32_t allow_padding; int32_t soa; int32_t packed; int32_t repr_compatible; int32_t is_export; };
struct ast_Module { int32_t num_funcs; int32_t main_func_index; int32_t num_imports; int32_t num_top_level_lets; int32_t num_struct_layouts; int32_t pending_allow_padding; int32_t pending_soa_struct; int32_t pending_cfg_skip; int32_t pending_repr_c_struct; int32_t pending_repr_compatible_struct; int32_t pending_used; int32_t pending_naked; int32_t pending_entry; int32_t pending_no_mangle; int32_t pending_interrupt; int32_t pending_export; int32_t num_module_enums; };
struct ast_ASTArena { int32_t num_types; int32_t num_exprs; int32_t num_blocks; int32_t num_funcs; };
struct ast_PipelineDepCtx { int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t path_buf[512]; uint8_t loaded_buf[4194304]; ptrdiff_t loaded_len; uint8_t preprocess_buf[4194304]; int32_t preprocess_len; int32_t use_asm_backend; int32_t target_arch; int32_t target_cpu_features; int32_t use_macho_o; int32_t use_coff_o; int32_t current_block_ref; int32_t typeck_loop_depth; int32_t current_func_index; int32_t skip_codegen_dep_0; int32_t entry_already_parsed; int32_t current_func_single_empty_param_index; int32_t current_func_empty_param_count; int32_t current_emit_empty_var_next_index; int32_t emit_expr_as_callee; struct ast_Module * current_codegen_module; struct ast_ASTArena * current_codegen_arena; int32_t current_codegen_dep_index; uint8_t current_codegen_prefix_mirror[128]; int32_t current_codegen_prefix_len; int32_t asm_entry_module_only; uint8_t entry_module_import_path_mirror[128]; int32_t entry_module_import_path_len; int32_t typeck_scope_region_len; uint8_t typeck_scope_region_label[128]; };
/* slim arena grow pool glue (C-04 codegen; linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);

extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern int32_t pipeline_lsp_diag_parse_typeck_buf(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, int32_t source_len, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_module_func_name_len_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_name_copy64(struct ast_Module * module, int32_t fi, uint8_t * dst);
extern void lsp_diag_prepare_pipeline_ctx(struct ast_PipelineDepCtx * ctx);
extern uint8_t * std_heap_alloc(size_t size);
extern void std_heap_free(uint8_t * ptr);
extern void lsp_diag_invalidate_cache();
extern void lsp_diag_collect_begin();
extern void lsp_diag_collect_end();
extern void lsp_diag_x_reset_parse_buffers();
extern struct ast_ASTArena * lsp_diag_x_arena_ptr();
extern struct ast_Module * lsp_diag_x_module_ptr();
extern struct ast_PipelineDepCtx * lsp_diag_x_ctx_ptr();
extern int32_t lsp_diag_format_diagnostics_json(uint8_t * out, int32_t out_cap);
extern int32_t lsp_build_response_with_result(int32_t id_val, uint8_t * result_ptr, int32_t result_len, uint8_t * out_buf, int32_t out_cap);

/* C-04 -E-extern TU aliases */
#define ast_arena_expr_get ast_ast_arena_expr_get
#define ast_arena_type_get ast_ast_arena_type_get

void lsp_diag_copy_bytes(uint8_t * dest, uint8_t * src, size_t n);
int32_t lsp_diag_run_pipeline_on_buf(uint8_t * mut_buf, int32_t sl);
int32_t lsp_diag_lsp_build_diagnostics_response(int32_t id_val, uint8_t * source, int32_t source_len, uint8_t * out_buf, int32_t out_cap);
int32_t lsp_diag_lsp_find_type_ref_at_pos(struct ast_ASTArena * arena, int32_t line_1, int32_t col_1);
int32_t lsp_diag_hover_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, uint8_t * out_buf, int32_t out_cap);
int32_t lsp_diag_lsp_collect_call_refs(struct ast_ASTArena * arena, int32_t func_index, int32_t * out_lines, int32_t * out_cols, int32_t max_refs);
int32_t lsp_diag_references_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_lines, int32_t * out_cols, int32_t max_refs);
int32_t lsp_diag_lsp_col_in_ident_span(int32_t line_1, int32_t col_1, int32_t span_line, int32_t span_col, int32_t span_len);
int32_t lsp_diag_lsp_source_find_function_def(uint8_t * source, int32_t sl, uint8_t * name, int32_t name_len, int32_t * out_line, int32_t * out_col);
int32_t lsp_diag_lsp_func_def_pos_in_source(uint8_t * source, int32_t sl, struct ast_Module * module, int32_t func_index, int32_t * out_line, int32_t * out_col);
int32_t lsp_diag_definition_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_line, int32_t * out_col);
int32_t lsp_diag_lsp_collect_semantic_tokens(struct ast_ASTArena * arena, int32_t * out_data, int32_t out_cap);
int32_t lsp_diag_lsp_build_semantic_tokens_response(int32_t id_val, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
void lsp_diag_copy_bytes(uint8_t * dest, uint8_t * src, size_t n) {
  size_t i = ((size_t)(0));
  while (i < n) {
    ((dest)[i] = ((src)[i]));
    (i = (i + ((size_t)(1))));
  }
}
int32_t lsp_diag_run_pipeline_on_buf(uint8_t * mut_buf, int32_t sl) {
  (void)(lsp_diag_x_reset_parse_buffers());
  struct ast_ASTArena * arena = lsp_diag_x_arena_ptr();
  struct ast_Module * module = lsp_diag_x_module_ptr();
  struct ast_PipelineDepCtx * ctx = lsp_diag_x_ctx_ptr();
  (void)(lsp_diag_prepare_pipeline_ctx(ctx));
  return pipeline_lsp_diag_parse_typeck_buf(module, arena, mut_buf, sl, ctx);
}
int32_t lsp_diag_lsp_build_diagnostics_response(int32_t id_val, uint8_t * source, int32_t source_len, uint8_t * out_buf, int32_t out_cap) {
  (void)(({ int32_t __tmp = 0; if (source == ((uint8_t *)(0)) || out_buf == ((uint8_t *)(0)) || out_cap <= 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t sl = source_len;
  (void)(({ int32_t __tmp = 0; if (sl < 0) {   (sl = (0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(lsp_diag_invalidate_cache());
  size_t ncopy = ((size_t)(sl));
  size_t alloc_bytes = ncopy + ((size_t)(1));
  (void)(({ size_t __tmp = 0; if (alloc_bytes == ((size_t)(0))) {   (alloc_bytes = (((size_t)(1))));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t * mut_buf = std_heap_alloc(alloc_bytes);
  (void)(({ int32_t __tmp = 0; if (mut_buf == ((uint8_t *)(0))) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (sl > 0) {   (void)(lsp_diag_copy_bytes(mut_buf, source, ncopy));
 } else (__tmp = 0) ; __tmp; }));
  ((mut_buf)[sl] = (((uint8_t)(0))));
  (void)(lsp_diag_collect_begin());
  int32_t rc = lsp_diag_run_pipeline_on_buf(mut_buf, sl);
  (void)(lsp_diag_collect_end());
  (void)(std_heap_free(mut_buf));
  int32_t diag_cap = 65536 + rc * 0;
  uint8_t * diag_buf = std_heap_alloc(((size_t)(diag_cap)));
  (void)(({ int32_t __tmp = 0; if (diag_buf == ((uint8_t *)(0))) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t dn = lsp_diag_format_diagnostics_json(diag_buf, diag_cap);
  int32_t result_len = dn;
  (void)(({ int32_t __tmp = 0; if (result_len <= 0) {   ((diag_buf)[0] = (((uint8_t)(91))));
  ((diag_buf)[1] = (((uint8_t)(93))));
  (result_len = (2));
 } else (__tmp = 0) ; __tmp; }));
  int32_t resp_len = lsp_build_response_with_result(id_val, diag_buf, result_len, out_buf, out_cap);
  (void)(std_heap_free(diag_buf));
  return resp_len;
}
int32_t lsp_diag_lsp_find_type_ref_at_pos(struct ast_ASTArena * arena, int32_t line_1, int32_t col_1) {
  (void)(({ int32_t __tmp = 0; if (arena == ((struct ast_ASTArena *)(0))) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t ei = 1;
  while (ei <= (arena)->num_exprs) {
    struct ast_Expr e = ast_arena_expr_get(arena, ei);
    (void)(({ int32_t __tmp = 0; if ((e).line == line_1 && (e).col == col_1) {   __tmp = ({ int32_t __tmp = 0; if ((e).resolved_type_ref != 0) {   return (e).resolved_type_ref;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    ++ei;
  }
  return 0;
}
int32_t lsp_diag_hover_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, uint8_t * out_buf, int32_t out_cap) {
  (void)(({ int32_t __tmp = 0; if (source == ((uint8_t *)(0)) || out_buf == ((uint8_t *)(0)) || out_cap <= 0 || source_len < 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t sl = source_len;
  (void)(({ int32_t __tmp = 0; if (sl < 0) {   (sl = (0));
 } else (__tmp = 0) ; __tmp; }));
  size_t ncopy = ((size_t)(sl));
  size_t ab = ncopy + ((size_t)(1));
  (void)(({ size_t __tmp = 0; if (ab == ((size_t)(0))) {   (ab = (((size_t)(1))));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t * mut_buf = std_heap_alloc(ab);
  (void)(({ int32_t __tmp = 0; if (mut_buf == ((uint8_t *)(0))) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (sl > 0) {   (void)(lsp_diag_copy_bytes(mut_buf, source, ncopy));
 } else (__tmp = 0) ; __tmp; }));
  ((mut_buf)[sl] = (((uint8_t)(0))));
  (void)(lsp_diag_invalidate_cache());
  (void)(lsp_diag_collect_begin());
  int32_t rc = lsp_diag_run_pipeline_on_buf(mut_buf, sl);
  (void)(lsp_diag_collect_end());
  (void)(({ int32_t __tmp = 0; if (rc != 0) {   (void)(std_heap_free(mut_buf));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_ASTArena * arena = lsp_diag_x_arena_ptr();
  (void)(std_heap_free(mut_buf));
  int32_t type_ref = lsp_diag_lsp_find_type_ref_at_pos(arena, line_0 + 1, col_0 + 1);
  (void)(({ int32_t __tmp = 0; if (type_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (type_ref <= 0 || type_ref > (arena)->num_types) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Type ty = ast_arena_type_get(arena, type_ref);
  int32_t k = 0;
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_I32 && out_cap >= 4) {   ((out_buf)[0] = (105));
  ((out_buf)[1] = (51));
  ((out_buf)[2] = (50));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_BOOL && out_cap >= 5) {   ((out_buf)[0] = (98));
  ((out_buf)[1] = (111));
  ((out_buf)[2] = (111));
  ((out_buf)[3] = (108));
  return 4;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_U8 && out_cap >= 3) {   ((out_buf)[0] = (117));
  ((out_buf)[1] = (56));
  return 2;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_U32 && out_cap >= 4) {   ((out_buf)[0] = (117));
  ((out_buf)[1] = (51));
  ((out_buf)[2] = (50));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_U64 && out_cap >= 4) {   ((out_buf)[0] = (117));
  ((out_buf)[1] = (54));
  ((out_buf)[2] = (52));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_I64 && out_cap >= 4) {   ((out_buf)[0] = (105));
  ((out_buf)[1] = (54));
  ((out_buf)[2] = (52));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_USIZE && out_cap >= 6) {   ((out_buf)[0] = (117));
  ((out_buf)[1] = (115));
  ((out_buf)[2] = (105));
  ((out_buf)[3] = (122));
  ((out_buf)[4] = (101));
  return 5;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_F32 && out_cap >= 4) {   ((out_buf)[0] = (102));
  ((out_buf)[1] = (51));
  ((out_buf)[2] = (50));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_F64 && out_cap >= 4) {   ((out_buf)[0] = (102));
  ((out_buf)[1] = (54));
  ((out_buf)[2] = (52));
  return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_VOID && out_cap >= 5) {   ((out_buf)[0] = (118));
  ((out_buf)[1] = (111));
  ((out_buf)[2] = (105));
  ((out_buf)[3] = (100));
  return 4;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_PTR && out_cap >= 2) {   ((out_buf)[0] = (42));
  return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_NAMED && (ty).name_len > 0 && (ty).name_len <= 64 && out_cap > (ty).name_len) {   int32_t i = 0;
  while (i < (ty).name_len && k < out_cap) {
    ((out_buf)[k] = ((i < 0 || (i) >= 64 ? (xlang_panic_(1, 0), ((ty).name)[0]) : ((ty).name)[i])));
    ++k;
    ++i;
  }
  return k;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_cap >= 2) {   ((out_buf)[0] = (63));
  return 1;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t lsp_diag_lsp_collect_call_refs(struct ast_ASTArena * arena, int32_t func_index, int32_t * out_lines, int32_t * out_cols, int32_t max_refs) {
  (void)(({ int32_t __tmp = 0; if (arena == ((struct ast_ASTArena *)(0)) || out_lines == ((int32_t *)(0)) || out_cols == ((int32_t *)(0)) || max_refs <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t count = 0;
  int32_t ei = 1;
  while (ei <= (arena)->num_exprs && count < max_refs) {
    struct ast_Expr e = ast_arena_expr_get(arena, ei);
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL && (e).call_resolved_func_index == func_index && (e).line > 0) {   ((out_lines)[count] = ((e).line));
  ((out_cols)[count] = ((e).col));
  ++count;
 } else (__tmp = 0) ; __tmp; }));
    ++ei;
  }
  return count;
}
int32_t lsp_diag_references_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_lines, int32_t * out_cols, int32_t max_refs) {
  (void)(({ int32_t __tmp = 0; if (source == ((uint8_t *)(0)) || out_lines == ((int32_t *)(0)) || out_cols == ((int32_t *)(0)) || max_refs <= 0 || source_len < 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t sl = source_len;
  (void)(({ int32_t __tmp = 0; if (sl < 0) {   (sl = (0));
 } else (__tmp = 0) ; __tmp; }));
  size_t ncopy = ((size_t)(sl));
  size_t ab = ncopy + ((size_t)(1));
  (void)(({ size_t __tmp = 0; if (ab == ((size_t)(0))) {   (ab = (((size_t)(1))));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t * mut_buf = std_heap_alloc(ab);
  (void)(({ int32_t __tmp = 0; if (mut_buf == ((uint8_t *)(0))) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (sl > 0) {   (void)(lsp_diag_copy_bytes(mut_buf, source, ncopy));
 } else (__tmp = 0) ; __tmp; }));
  ((mut_buf)[sl] = (((uint8_t)(0))));
  (void)(lsp_diag_invalidate_cache());
  (void)(lsp_diag_collect_begin());
  int32_t rc = lsp_diag_run_pipeline_on_buf(mut_buf, sl);
  (void)(lsp_diag_collect_end());
  (void)(({ int32_t __tmp = 0; if (rc != 0) {   (void)(std_heap_free(mut_buf));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_ASTArena * arena = lsp_diag_x_arena_ptr();
  (void)(std_heap_free(mut_buf));
  int32_t line_1 = line_0 + 1;
  int32_t col_1 = col_0 + 1;
  int32_t func_index = -1;
  int32_t ei = 1;
  while (ei <= (arena)->num_exprs) {
    struct ast_Expr e = ast_arena_expr_get(arena, ei);
    (void)(({ int32_t __tmp = 0; if ((e).line == line_1 && (e).col == col_1 && (e).kind == ast_ExprKind_EXPR_CALL && (e).call_resolved_func_index >= 0) {   (func_index = ((e).call_resolved_func_index));
  break;
 } else (__tmp = 0) ; __tmp; }));
    ++ei;
  }
  (void)(({ int32_t __tmp = 0; if (func_index < 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t tmp_lines[512] = { 0 };
  int32_t tmp_cols[512] = { 0 };
  int32_t n = lsp_diag_lsp_collect_call_refs(arena, func_index, (&((tmp_lines)[0])), (&((tmp_cols)[0])), 512);
  int32_t out_n = n;
  (void)(({ int32_t __tmp = 0; if (out_n > max_refs) {   (out_n = (max_refs));
 } else (__tmp = 0) ; __tmp; }));
  int32_t oi = 0;
  while (oi < out_n) {
    ((out_lines)[oi] = ((oi < 0 || (oi) >= 512 ? (xlang_panic_(1, 0), (tmp_lines)[0]) : (tmp_lines)[oi]) - 1));
    ((out_cols)[oi] = ((oi < 0 || (oi) >= 512 ? (xlang_panic_(1, 0), (tmp_cols)[0]) : (tmp_cols)[oi]) - 1));
    ++oi;
  }
  return out_n;
}
int32_t lsp_diag_lsp_col_in_ident_span(int32_t line_1, int32_t col_1, int32_t span_line, int32_t span_col, int32_t span_len) {
  (void)(({ int32_t __tmp = 0; if (line_1 != span_line || span_len <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (col_1 >= span_col && col_1 < span_col + span_len) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t lsp_diag_lsp_source_find_function_def(uint8_t * source, int32_t sl, uint8_t * name, int32_t name_len, int32_t * out_line, int32_t * out_col) {
  (void)(({ int32_t __tmp = 0; if (source == ((uint8_t *)(0)) || name == ((uint8_t *)(0)) || name_len <= 0 || sl <= 0 || out_line == ((int32_t *)(0)) || out_col == ((int32_t *)(0))) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  uint8_t kw[9] = { 102, 117, 110, 99, 116, 105, 111, 110, 32 };
  int32_t line = 1;
  int32_t col = 1;
  int32_t i = 0;
  while (i < sl) {
    int32_t boundary = 0;
    (void)(({ int32_t __tmp = 0; if (i == 0) {   (boundary = (1));
 } else {   uint8_t prev = (source)[i - 1];
  __tmp = ({ int32_t __tmp = 0; if (prev == ((uint8_t)(32)) || prev == ((uint8_t)(9)) || prev == ((uint8_t)(10))) {   (boundary = (1));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (boundary != 0 && (i + 9) + name_len <= sl) {   int32_t ki = 0;
  int32_t kw_ok = 1;
  while (ki < 9) {
    (void)(({ int32_t __tmp = 0; if ((source)[i + ki] != (kw)[ki]) {   (kw_ok = (0));
  break;
 } else (__tmp = 0) ; __tmp; }));
    ++ki;
  }
  __tmp = ({ int32_t __tmp = 0; if (kw_ok != 0) {   int32_t ni = 0;
  int32_t name_ok = 1;
  while (ni < name_len) {
    (void)(({ int32_t __tmp = 0; if ((source)[(i + 9) + ni] != (name)[ni]) {   (name_ok = (0));
  break;
 } else (__tmp = 0) ; __tmp; }));
    ++ni;
  }
  __tmp = ({ int32_t __tmp = 0; if (name_ok != 0) {   int32_t after = (i + 9) + name_len;
  (void)(({ int32_t __tmp = 0; if (after >= sl) {   ((out_line)[0] = (line));
  ((out_col)[0] = (col + 9));
  return 1;
 } else (__tmp = 0) ; __tmp; }));
  uint8_t ac = (source)[after];
  __tmp = ({ int32_t __tmp = 0; if (ac == ((uint8_t)(32)) || ac == ((uint8_t)(40)) || ac == ((uint8_t)(10)) || ac == ((uint8_t)(9))) {   ((out_line)[0] = (line));
  ((out_col)[0] = (col + 9));
  return 1;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((source)[i] == ((uint8_t)(10))) {   ++line;
  (col = (1));
 } else {   ++col;
 } ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_diag_lsp_func_def_pos_in_source(uint8_t * source, int32_t sl, struct ast_Module * module, int32_t func_index, int32_t * out_line, int32_t * out_col) {
  (void)(({ int32_t __tmp = 0; if (module == ((struct ast_Module *)(0)) || func_index < 0 || func_index >= (module)->num_funcs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t nl = pipeline_module_func_name_len_at(module, func_index);
  (void)(({ int32_t __tmp = 0; if (nl <= 0 || nl > 64) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  uint8_t nm[128] = { 0 };
  (void)(pipeline_module_func_name_copy64(module, func_index, (&((nm)[0]))));
  return lsp_diag_lsp_source_find_function_def(source, sl, (&((nm)[0])), nl, out_line, out_col);
}
int32_t lsp_diag_definition_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_line, int32_t * out_col) {
  (void)(({ int32_t __tmp = 0; if (source == ((uint8_t *)(0)) || out_line == ((int32_t *)(0)) || out_col == ((int32_t *)(0)) || source_len < 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t sl = source_len;
  size_t ncopy = ((size_t)(sl));
  size_t ab = ncopy + ((size_t)(1));
  (void)(({ size_t __tmp = 0; if (ab == ((size_t)(0))) {   (ab = (((size_t)(1))));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t * mut_buf = std_heap_alloc(ab);
  (void)(({ int32_t __tmp = 0; if (mut_buf == ((uint8_t *)(0))) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (sl > 0) {   (void)(lsp_diag_copy_bytes(mut_buf, source, ncopy));
 } else (__tmp = 0) ; __tmp; }));
  ((mut_buf)[sl] = (((uint8_t)(0))));
  (void)(lsp_diag_invalidate_cache());
  (void)(lsp_diag_collect_begin());
  int32_t rc = lsp_diag_run_pipeline_on_buf(mut_buf, sl);
  (void)(lsp_diag_collect_end());
  (void)(({ int32_t __tmp = 0; if (rc != 0) {   (void)(std_heap_free(mut_buf));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Module * module = lsp_diag_x_module_ptr();
  struct ast_ASTArena * arena = lsp_diag_x_arena_ptr();
  int32_t line_1 = line_0 + 1;
  int32_t col_1 = col_0 + 1;
  int32_t def_l1 = 0;
  int32_t def_c1 = 0;
  int32_t fi = 0;
  while (fi < (module)->num_funcs) {
    (void)(({ int32_t __tmp = 0; if (lsp_diag_lsp_func_def_pos_in_source(mut_buf, sl, module, fi, (&(def_l1)), (&(def_c1))) != 0) {   int32_t nl2 = pipeline_module_func_name_len_at(module, fi);
  __tmp = ({ int32_t __tmp = 0; if (lsp_diag_lsp_col_in_ident_span(line_1, col_1, def_l1, def_c1, nl2) != 0) {   ((out_line)[0] = (def_l1 - 1));
  ((out_col)[0] = (def_c1 - 1));
  (void)(std_heap_free(mut_buf));
  return 1;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    ++fi;
  }
  int32_t func_index = -1;
  int32_t ei = 1;
  while (ei <= (arena)->num_exprs) {
    struct ast_Expr e = ast_arena_expr_get(arena, ei);
    (void)(({ int32_t __tmp = 0; if ((e).line == line_1 && (e).col == col_1 && (e).kind == ast_ExprKind_EXPR_CALL && (e).call_resolved_func_index >= 0) {   (func_index = ((e).call_resolved_func_index));
  break;
 } else (__tmp = 0) ; __tmp; }));
    ++ei;
  }
  (void)(({ int32_t __tmp = 0; if (func_index >= 0 && lsp_diag_lsp_func_def_pos_in_source(mut_buf, sl, module, func_index, (&(def_l1)), (&(def_c1))) != 0) {   ((out_line)[0] = (def_l1 - 1));
  ((out_col)[0] = (def_c1 - 1));
  (void)(std_heap_free(mut_buf));
  return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(std_heap_free(mut_buf));
  return 0;
}
int32_t lsp_diag_lsp_collect_semantic_tokens(struct ast_ASTArena * arena, int32_t * out_data, int32_t out_cap) {
  (void)(({ int32_t __tmp = 0; if (arena == ((struct ast_ASTArena *)(0)) || out_data == ((int32_t *)(0)) || out_cap < 5) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t count = 0;
  int32_t prev_line = 0;
  int32_t prev_start = 0;
  int32_t ei = 1;
  while (ei <= (arena)->num_exprs && count + 5 <= out_cap) {
    struct ast_Expr e = ast_arena_expr_get(arena, ei);
    (void)(({ int32_t __tmp = 0; if ((e).line <= 0 || (e).col <= 0) {   ++ei;
  continue;
 } else (__tmp = 0) ; __tmp; }));
    int32_t line0 = (e).line - 1;
    int32_t start0 = (e).col - 1;
    int32_t len = (e).var_name_len;
    (void)(({ int32_t __tmp = 0; if (len <= 0) {   (len = (1));
 } else (__tmp = 0) ; __tmp; }));
    int32_t token_type = -1;
    int32_t modifiers = 0;
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_VAR) {   (token_type = (8));
  __tmp = ({ int32_t __tmp = 0; if ((e).resolved_type_ref != 0) {   (modifiers = (4));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL || (e).kind == ast_ExprKind_EXPR_METHOD_CALL) {   (token_type = (12));
  __tmp = ({ int32_t __tmp = 0; if ((e).var_name_len > 0) {   (len = ((e).var_name_len));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_STRUCT_LIT) {   (token_type = (5));
  __tmp = ({ int32_t __tmp = 0; if ((e).struct_lit_struct_name_len > 0) {   (len = ((e).struct_lit_struct_name_len));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ENUM_VARIANT) {   (token_type = (3));
  __tmp = ({ int32_t __tmp = 0; if ((e).var_name_len > 0) {   (len = ((e).var_name_len));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LIT) {   (token_type = (19));
  (len = (1));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FLOAT_LIT) {   (token_type = (19));
  (len = (1));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FIELD_ACCESS) {   (token_type = (9));
  __tmp = ({ int32_t __tmp = 0; if ((e).field_access_field_len > 0) {   (len = ((e).field_access_field_len));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_AS) {   (token_type = (8));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (token_type >= 0) {   int32_t delta_line = line0 - prev_line;
  int32_t delta_start = 0;
  (void)(({ int32_t __tmp = 0; if (delta_line == 0) {   (delta_start = (start0 - prev_start));
 } else {   (delta_start = (start0));
 } ; __tmp; }));
  ((out_data)[count] = (delta_line));
  ++count;
  ((out_data)[count] = (delta_start));
  ++count;
  ((out_data)[count] = (len));
  ++count;
  ((out_data)[count] = (token_type));
  ++count;
  ((out_data)[count] = (modifiers));
  ++count;
  (prev_line = (line0));
  (prev_start = (start0));
 } else (__tmp = 0) ; __tmp; }));
    ++ei;
  }
  return count;
}
int32_t lsp_diag_lsp_build_semantic_tokens_response(int32_t id_val, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap) {
  (void)(({ int32_t __tmp = 0; if (doc_buf == ((uint8_t *)(0)) || out_buf == ((uint8_t *)(0)) || out_cap <= 0 || doc_len < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t sl = doc_len;
  size_t ncopy = ((size_t)(sl));
  size_t ab = ncopy + ((size_t)(1));
  (void)(({ size_t __tmp = 0; if (ab == ((size_t)(0))) {   (ab = (((size_t)(1))));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t * mut_buf = std_heap_alloc(ab);
  (void)(({ int32_t __tmp = 0; if (mut_buf == ((uint8_t *)(0))) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (sl > 0) {   (void)(lsp_diag_copy_bytes(mut_buf, doc_buf, ncopy));
 } else (__tmp = 0) ; __tmp; }));
  ((mut_buf)[sl] = (((uint8_t)(0))));
  (void)(lsp_diag_invalidate_cache());
  (void)(lsp_diag_collect_begin());
  int32_t rc = lsp_diag_run_pipeline_on_buf(mut_buf, sl);
  (void)(lsp_diag_collect_end());
  (void)(({ int32_t __tmp = 0; if (rc != 0) {   (void)(std_heap_free(mut_buf));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  struct ast_ASTArena * arena = lsp_diag_x_arena_ptr();
  (void)(std_heap_free(mut_buf));
  int32_t token_cap = 4096;
  size_t token_bytes = ((size_t)(token_cap * 4));
  uint8_t * token_data_raw = std_heap_alloc(token_bytes);
  int32_t * token_data = ((int32_t *)(token_data_raw));
  (void)(({ int32_t __tmp = 0; if (token_data == ((int32_t *)(0))) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t n_tokens = lsp_diag_lsp_collect_semantic_tokens(arena, token_data, token_cap);
  int32_t json_cap = 262144;
  uint8_t * json_ptr = std_heap_alloc(((size_t)(json_cap)));
  (void)(({ int32_t __tmp = 0; if (json_ptr == ((uint8_t *)(0))) {   (void)(std_heap_free(((uint8_t *)(token_data))));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t prefix[128] = { 0 };
  int32_t pi = 0;
  ((prefix)[0] = (123));
  ((1 < 0 || (1) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[1] = 34, 0)));
  ((2 < 0 || (2) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[2] = 106, 0)));
  ((3 < 0 || (3) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[3] = 115, 0)));
  ((4 < 0 || (4) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[4] = 111, 0)));
  ((5 < 0 || (5) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[5] = 110, 0)));
  ((6 < 0 || (6) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[6] = 114, 0)));
  ((7 < 0 || (7) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[7] = 112, 0)));
  ((8 < 0 || (8) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[8] = 99, 0)));
  ((9 < 0 || (9) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[9] = 34, 0)));
  ((10 < 0 || (10) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[10] = 58, 0)));
  ((11 < 0 || (11) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[11] = 34, 0)));
  ((12 < 0 || (12) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[12] = 50, 0)));
  ((13 < 0 || (13) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[13] = 46, 0)));
  ((14 < 0 || (14) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[14] = 48, 0)));
  ((15 < 0 || (15) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[15] = 34, 0)));
  ((16 < 0 || (16) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[16] = 44, 0)));
  ((17 < 0 || (17) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[17] = 34, 0)));
  ((18 < 0 || (18) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[18] = 105, 0)));
  ((19 < 0 || (19) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[19] = 100, 0)));
  ((20 < 0 || (20) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[20] = 34, 0)));
  ((21 < 0 || (21) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[21] = 58, 0)));
  (pi = (22));
  uint8_t id_str[12] = { 0 };
  int32_t id_len = 0;
  int32_t tmp = id_val;
  (void)(({ int32_t __tmp = 0; if (tmp == 0) {   ((id_str)[0] = (48));
  (id_len = (1));
 } else {   int32_t ds[12] = { 0 };
  int32_t dn = 0;
  while (tmp > 0) {
    ((dn < 0 || (dn) >= 12 ? (xlang_panic_(1, 0), 0) : ((ds)[dn] = (10 == 0 ? (xlang_panic_(1, 0), tmp) : (tmp % 10)), 0)));
    (tmp = ((10 == 0 ? (xlang_panic_(1, 0), tmp) : (tmp / 10))));
    ++dn;
  }
  int32_t di = dn - 1;
  while (di >= 0) {
    ((id_len < 0 || (id_len) >= 12 ? (xlang_panic_(1, 0), 0) : ((id_str)[id_len] = ((uint8_t)((di < 0 || (di) >= 12 ? (xlang_panic_(1, 0), (ds)[0]) : (ds)[di]) + 48)), 0)));
    ++id_len;
    (di = (di - 1));
  }
 } ; __tmp; }));
  int32_t ji = 0;
  while (ji < id_len && pi < 64) {
    ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = (ji < 0 || (ji) >= 12 ? (xlang_panic_(1, 0), (id_str)[0]) : (id_str)[ji]), 0)));
    ++pi;
    ++ji;
  }
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 44, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 34, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 114, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 101, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 115, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 117, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 108, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 116, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 34, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 58, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 123, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 34, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 100, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 97, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 116, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 97, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 34, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 58, 0)));
  ++pi;
  ((pi < 0 || (pi) >= 64 ? (xlang_panic_(1, 0), 0) : ((prefix)[pi] = 91, 0)));
  ++pi;
  int32_t pj = 0;
  while (pj < pi) {
    ((json_ptr)[pj] = ((pj < 0 || (pj) >= 64 ? (xlang_panic_(1, 0), (prefix)[0]) : (prefix)[pj])));
    ++pj;
  }
  int32_t ti = 0;
  int32_t first = 1;
  while (ti < n_tokens) {
    int32_t val = (token_data)[ti];
    (void)(({ int32_t __tmp = 0; if (first == 0 && pj < json_cap) {   ((json_ptr)[pj] = (44));
  ++pj;
 } else (__tmp = 0) ; __tmp; }));
    (first = (0));
    (void)(({ int32_t __tmp = 0; if (val < 0) {   __tmp = ({ int32_t __tmp = 0; if (pj < json_cap) {   ((json_ptr)[pj] = (45));
  ++pj;
  (val = ((-val)));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    int32_t digits[12] = { 0 };
    int32_t dn = 0;
    (void)(({ int32_t __tmp = 0; if (val == 0) {   ((digits)[0] = (0));
  (dn = (1));
 } else {   int32_t v2 = val;
  while (v2 > 0) {
    ((dn < 0 || (dn) >= 12 ? (xlang_panic_(1, 0), 0) : ((digits)[dn] = (10 == 0 ? (xlang_panic_(1, 0), v2) : (v2 % 10)), 0)));
    (v2 = ((10 == 0 ? (xlang_panic_(1, 0), v2) : (v2 / 10))));
    ++dn;
  }
 } ; __tmp; }));
    int32_t di = dn - 1;
    while (di >= 0 && pj < json_cap) {
      ((json_ptr)[pj] = (((uint8_t)((di < 0 || (di) >= 12 ? (xlang_panic_(1, 0), (digits)[0]) : (digits)[di]) + 48))));
      ++pj;
      (di = (di - 1));
    }
    ++ti;
  }
  (void)(({ int32_t __tmp = 0; if (pj < json_cap) {   ((json_ptr)[pj] = (93));
  ++pj;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (pj < json_cap) {   ((json_ptr)[pj] = (125));
  ++pj;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (pj < json_cap) {   ((json_ptr)[pj] = (125));
  ++pj;
 } else (__tmp = 0) ; __tmp; }));
  int32_t resp_len = pj;
  int32_t ri = 0;
  while (ri < resp_len && ri < out_cap) {
    ((out_buf)[ri] = ((json_ptr)[ri]));
    ++ri;
  }
  (void)(std_heap_free(json_ptr));
  (void)(std_heap_free(((uint8_t *)(token_data))));
  return resp_len;
}
