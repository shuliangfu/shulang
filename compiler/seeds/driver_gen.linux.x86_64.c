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
#include <string.h>
#undef htonl
#undef htons
#undef ntohl
#undef ntohs
#ifdef _WIN32
#define XLANG_LIB_WEAK
#else
#define XLANG_LIB_WEAK __attribute__((weak))
#endif
#ifndef XLANG_BUILTIN_INLINE_DECLS_GUARD
#define XLANG_BUILTIN_INLINE_DECLS_GUARD
/* CORE-009 xlang_builtin_* static inline wrappers (clz/ctz/popcount/bswap/rotl/rotr) */
static inline int xlang_builtin_clz_u32(uint32_t x) { return x == 0 ? 32 : __builtin_clz(x); }
static inline int xlang_builtin_ctz_u32(uint32_t x) { return x == 0 ? 32 : __builtin_ctz(x); }
static inline int xlang_builtin_popcount_u32(uint32_t x) { return __builtin_popcount(x); }
static inline uint32_t xlang_builtin_bswap_u32(uint32_t x) { return __builtin_bswap32(x); }
static inline uint32_t xlang_builtin_rotl_u32(uint32_t x, uint32_t c) {
  c &= 31; return c == 0 ? x : (x << c) | (x >> (32 - c));
}
static inline uint32_t xlang_builtin_rotr_u32(uint32_t x, uint32_t c) {
  c &= 31; return c == 0 ? x : (x >> c) | (x << (32 - c));
}
#endif
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
  { int _n = snprintf(_note, sizeof _note, "note: crash evidence: panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val, _pid);
    if (_n > 0) (void)xlang_io_write(2, _note, (size_t)_n); }
  { const char *_dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (_dir && _dir[0]) { char _p[1024]; snprintf(_p, sizeof _p, "%s/xlang-crash-%d.txt", _dir, _pid);
      { int _fd = xlang_io_open_write(_p);
        if (_fd >= 0) { char _body[160];
          int _bl = snprintf(_body, sizeof _body, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, _pid);
          if (_bl > 0) (void)xlang_io_write(_fd, _body, (size_t)_bl);
          (void)xlang_proc_close_fd(_fd);
          { int _bn = snprintf(_note, sizeof _note, "note: crash evidence: bundle=%s\n", _p);
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
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[128]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; uint8_t region_label[128]; int32_t region_label_len; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t var_name[128]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_base; int32_t match_num_arms; int32_t field_access_base_ref; uint8_t field_access_field_name[128]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t field_access_soa_stride; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_base; int32_t call_num_args; int32_t call_num_type_args; int32_t method_call_base_ref; uint8_t method_call_name[128]; int32_t method_call_name_len; int32_t method_call_arg_base; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[128]; int32_t struct_lit_struct_name_len; int32_t struct_lit_field_base; int32_t struct_lit_num_fields; int32_t array_lit_elem_base; int32_t array_lit_num_elems; int32_t float_bits_lo; int32_t float_bits_hi; int32_t enum_variant_tag; int32_t as_operand_ref; int32_t as_target_type_ref; int32_t call_resolved_func_index; int32_t call_resolved_dep_index; };
struct ast_ConstDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_IfStmt { int32_t cond_ref; int32_t then_body_ref; int32_t else_body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[32]; int32_t label_len; int32_t is_goto; uint8_t goto_target[32]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { int32_t const_base; int32_t num_consts; int32_t let_base; int32_t num_lets; int32_t num_early_lets; int32_t loop_base; int32_t num_loops; int32_t for_loop_base; int32_t num_for_loops; int32_t if_base; int32_t num_if_stmts; int32_t region_base; int32_t num_regions; int32_t defer_base; int32_t num_defers; int32_t labeled_base; int32_t num_labeled_stmts; int32_t expr_stmt_base; int32_t num_expr_stmts; int32_t final_expr_ref; int32_t stmt_order_base; int32_t num_stmt_order; int32_t parent_block_ref; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[128]; int32_t name_len; int32_t param_base; int32_t num_params; int32_t num_generic_params; int32_t return_type_ref; int32_t body_ref; int32_t body_expr_ref; int32_t is_extern; int32_t is_async; int32_t is_used; int32_t is_naked; int32_t is_entry; int32_t is_no_mangle; int32_t is_interrupt; int32_t abi_kind; int32_t is_variadic; int32_t is_export; };
struct ast_StructLayout { uint8_t name[128]; int32_t name_len; int32_t field_base; int32_t num_fields; int32_t allow_padding; int32_t soa; int32_t packed; int32_t repr_compatible; int32_t is_export; };
struct ast_Module { int32_t num_funcs; int32_t main_func_index; int32_t num_imports; int32_t num_top_level_lets; int32_t num_struct_layouts; int32_t pending_allow_padding; int32_t pending_soa_struct; int32_t pending_cfg_skip; int32_t pending_repr_c_struct; int32_t pending_repr_compatible_struct; int32_t pending_used; int32_t pending_naked; int32_t pending_entry; int32_t pending_no_mangle; int32_t pending_interrupt; int32_t pending_export; int32_t num_module_enums; };
struct ast_ASTArena { int32_t num_types; int32_t num_exprs; int32_t num_blocks; int32_t num_funcs; };
struct ast_PipelineDepCtx { int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t path_buf[512]; uint8_t loaded_buf[4194304]; ptrdiff_t loaded_len; uint8_t preprocess_buf[4194304]; int32_t preprocess_len; int32_t use_asm_backend; int32_t target_arch; int32_t target_cpu_features; int32_t use_macho_o; int32_t use_coff_o; int32_t current_block_ref; int32_t typeck_loop_depth; int32_t current_func_index; int32_t skip_codegen_dep_0; int32_t entry_already_parsed; int32_t current_func_single_empty_param_index; int32_t current_func_empty_param_count; int32_t current_emit_empty_var_next_index; int32_t emit_expr_as_callee; struct ast_Module * current_codegen_module; struct ast_ASTArena * current_codegen_arena; int32_t current_codegen_dep_index; uint8_t current_codegen_prefix_mirror[128]; int32_t current_codegen_prefix_len; int32_t asm_entry_module_only; uint8_t entry_module_import_path_mirror[128]; int32_t entry_module_import_path_len; int32_t typeck_scope_region_len; uint8_t typeck_scope_region_label[128]; };
struct codegen_CodegenOutBuf { uint8_t data[9437184]; int32_t length; };
/* slim arena grow pool glue (C-04 codegen; linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);

extern int32_t std_sys_read_file_into(uint8_t * path, uint8_t * buf, int32_t cap);
struct main_DriverXEmitState { uint8_t path_buf[512]; int32_t path_len; int32_t emit_extern_imports; int32_t use_asm_backend; int32_t target_arch; uint8_t out_path_buf[512]; int32_t out_path_len; };
/* driver_gen thin TU aliases: main.x -E-extern 调用 main_*，build_asm/main.o 为单前缀符号 */
extern int32_t eq_minus_E(uint8_t *buf, int32_t len);
extern int32_t eq_minus_E_extern(uint8_t *buf, int32_t len);
extern int32_t eq_asm(uint8_t *buf, int32_t len);
extern int32_t str_eq(uint8_t *a, int32_t a_len, uint8_t *b, int32_t b_len);
extern int32_t target_contains_arm(uint8_t *buf, int32_t len);
extern int32_t target_contains_riscv(uint8_t *buf, int32_t len);
extern int32_t driver_emit_try_append_lib_from_argv(int32_t argc, uint8_t *argv, int32_t arg_i, struct main_DriverXEmitState *state);
extern int32_t main_run_compiler_c(int32_t argc, uint8_t *argv);
extern int32_t main_cmd_build(int32_t argc, uint8_t *argv);
extern int32_t main_cmd_run(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_fmt(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_check(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_test(int32_t argc, uint8_t *argv);
extern void driver_print_usage_write(void);
#define main_eq_minus_E eq_minus_E
#define main_eq_minus_E_extern eq_minus_E_extern
#define main_eq_asm eq_asm
#define main_str_eq str_eq
#define main_target_contains_arm target_contains_arm
#define main_target_contains_riscv target_contains_riscv
#define main_driver_emit_try_append_lib_from_argv driver_emit_try_append_lib_from_argv
#define main_run_compiler_c_impl main_run_compiler_c


extern ptrdiff_t fs_posix_write_c(int32_t fd, uint8_t * buf, size_t count);
extern int32_t fs_posix_close_c(int32_t fd);
extern int32_t preprocess_x_buf(uint8_t * source_buf, ptrdiff_t source_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t driver_cmd_fmt(int32_t argc, uint8_t * argv);
extern int32_t driver_cmd_check(int32_t argc, uint8_t * argv);
extern int32_t driver_cmd_test(int32_t argc, uint8_t * argv);
extern void driver_emit_lib_root_reset(uint8_t * state);
extern int32_t driver_emit_append_lib_root(uint8_t * state, uint8_t * path, int32_t len);
extern int32_t driver_emit_lib_root_count(uint8_t * state);
extern int32_t driver_emit_lib_root_len(uint8_t * state, int32_t i);
extern void driver_emit_lib_root_copy(uint8_t * state, int32_t i, uint8_t * dst, int32_t cap);
extern int32_t driver_get_argv_i(int32_t argc, uint8_t * argv, int32_t i, uint8_t * buf, int32_t max);
/* Dangling-value guard for value-taking driver flags (authority body in
 * seeds/rt_compile.from_x.c / src/runtime/rt_compile.x, same commit): 1 iff
 * argv[i+1] exists, is non-empty, and does not start with '-'. PLATFORM: SHARED. */
extern int32_t driver_compile_argv_next_is_value_c(int32_t argc, uint8_t * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern uint8_t * driver_argv_drop_subcommand(int32_t argc, uint8_t * argv);
/* xlang run / bare xlang file.x: append `-o <temp>` when no -o so the product
   is built in /tmp and exec'd (no a.out, no generated C to stdout). */
extern uint8_t * driver_argv_ensure_run_o(int32_t argc, uint8_t * argv, int32_t * out_argc);
extern int32_t driver_build_build_x();
extern int32_t driver_exec_compiled(int32_t argc, uint8_t * argv);
extern int32_t driver_fs_open_read_path(uint8_t * path, int32_t path_len);
extern uint8_t * driver_arena_buf();
extern uint8_t * driver_module_buf();
extern int32_t driver_fs_open_write(uint8_t * path, int32_t path_len);
extern void driver_pipeline_fail_code(int32_t rc, uint8_t * path);
extern void driver_print_x_smoke_summary(uint8_t * module, size_t codegen_len);
extern int32_t driver_run_x_emit_c_set_path(uint8_t * path, int32_t path_len);
extern int32_t driver_run_x_emit_c_set_lib(int32_t i, uint8_t * buf, int32_t len);
extern int32_t driver_run_x_emit_c_set_n_lib_roots(int32_t n);
extern int32_t driver_run_x_emit_c_set_emit_extern(int32_t v);
extern int32_t driver_run_x_emit_c();
extern int32_t pipeline_run_x_pipeline_impl(uint8_t * module, uint8_t * arena, uint8_t * source_data, size_t source_len, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
extern int32_t ast_pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx * ctx, uint8_t * path, int32_t len);
extern int32_t driver_run_compiler_full(int32_t argc, uint8_t * argv);
extern int32_t typeck_lsp_main();

/* C-04 -E-extern TU aliases */
#define pipeline_ctx_append_lib_root ast_pipeline_ctx_append_lib_root

uint8_t * main_driver_emit_state_key(struct main_DriverXEmitState * state);
int32_t main_driver_emit_try_append_lib_from_argv(int32_t argc, uint8_t * argv, int32_t arg_i, struct main_DriverXEmitState * state);
void main_driver_emit_ensure_default_lib_root(struct main_DriverXEmitState * state);
void main_driver_emit_copy_lib_roots_to_ctx(struct main_DriverXEmitState * state, struct ast_PipelineDepCtx * ctx);
struct main_DriverXEmitState main_driver_emit_state_default();
struct ast_PipelineDepCtx main_pipeline_dep_ctx_for_emit(int32_t use_asm, int32_t target);
int32_t main_run_compiler_c_impl(int32_t argc, uint8_t * argv);
int32_t main_run_compiler_c(int32_t argc, uint8_t * argv);
int32_t main_eq_minus_L(uint8_t * buf, int32_t len);
int32_t main_eq_minus_x(uint8_t * buf, int32_t len);
int32_t main_eq_minus_E(uint8_t * buf, int32_t len);
int32_t main_eq_minus_E_extern(uint8_t * buf, int32_t len);
int32_t main_eq_minus_backend(uint8_t * buf, int32_t len);
int32_t main_eq_asm(uint8_t * buf, int32_t len);
int32_t main_eq_minus_lsp(uint8_t * buf, int32_t len);
int32_t main_eq_minus_target(uint8_t * buf, int32_t len);
int32_t main_str_eq(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len);
int32_t main_target_contains_arm(uint8_t * buf, int32_t len);
int32_t main_target_contains_riscv(uint8_t * buf, int32_t len);
int32_t main_driver_argv_parse_x_path(int32_t argc, uint8_t * argv, struct main_DriverXEmitState * state);
int32_t main_driver_argv_parse_x(int32_t argc, uint8_t * argv, struct main_DriverXEmitState * state);
int32_t main_driver_run_x_emit_x(struct main_DriverXEmitState * state);
int32_t main_run_compiler_x_path_impl(int32_t argc, uint8_t * argv);
int32_t main_cmd_build(int32_t argc, uint8_t * argv);
int32_t main_cmd_run(int32_t argc, uint8_t * argv);
int32_t main_entry(int32_t argc, uint8_t * argv);
XLANG_LIB_WEAK uint8_t * main_driver_emit_state_key(struct main_DriverXEmitState * state) {
  return ((uint8_t *)(state));
}
XLANG_LIB_WEAK int32_t main_driver_emit_try_append_lib_from_argv(int32_t argc, uint8_t * argv, int32_t arg_i, struct main_DriverXEmitState * state) {
  uint8_t tmp[256] = { 0 };
  int32_t llen = driver_get_argv_i(argc, argv, arg_i, (&((tmp)[0])), 256);
  if (llen >= 0 && driver_emit_append_lib_root(main_driver_emit_state_key(state), (&((tmp)[0])), llen) >= 0) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK void main_driver_emit_ensure_default_lib_root(struct main_DriverXEmitState * state) {
  (void)(({ int32_t __tmp = 0; if (driver_emit_lib_root_count(main_driver_emit_state_key(state)) == 0) {   uint8_t dot[1] = { 46 };
  (void)(driver_emit_append_lib_root(main_driver_emit_state_key(state), (&((dot)[0])), 1));
 } else (__tmp = 0) ; __tmp; }));
}
XLANG_LIB_WEAK void main_driver_emit_copy_lib_roots_to_ctx(struct main_DriverXEmitState * state, struct ast_PipelineDepCtx * ctx) {
  int32_t k = 0;
  int32_t n = driver_emit_lib_root_count(main_driver_emit_state_key(state));
  uint8_t tmp[256] = { 0 };
  while (k < n) {
    int32_t llen = driver_emit_lib_root_len(main_driver_emit_state_key(state), k);
    if (llen > 0) {   (void)(driver_emit_lib_root_copy(main_driver_emit_state_key(state), k, (&((tmp)[0])), 256));
  (void)(ast_pipeline_ctx_append_lib_root(ctx, (&((tmp)[0])), llen));
 }
    ++k;
  }
}
XLANG_LIB_WEAK struct main_DriverXEmitState main_driver_emit_state_default() {
  return ({ struct main_DriverXEmitState _t = { 0 }; _t.path_len = 0; _t.emit_extern_imports = 0; _t.use_asm_backend = 1; _t.target_arch = 0; _t; });
}
XLANG_LIB_WEAK struct ast_PipelineDepCtx main_pipeline_dep_ctx_for_emit(int32_t use_asm, int32_t target) {
  struct ast_PipelineDepCtx ctx = ({ struct ast_PipelineDepCtx _t = { 0 }; _t.ndep = 0; _t.entry_dir_len = 0; _t.num_lib_roots = 0; _t; });
  ((ctx).use_asm_backend = (use_asm));
  ((ctx).target_arch = (target));
  ((ctx).current_func_index = ((-1)));
  ((ctx).current_func_single_empty_param_index = ((-1)));
  return ctx;
}
XLANG_LIB_WEAK int32_t main_run_compiler_c_impl(int32_t argc, uint8_t * argv) {
  return driver_run_compiler_full(argc, argv);
}
XLANG_LIB_WEAK int32_t main_eq_minus_L(uint8_t * buf, int32_t len) {
  if (len < 2) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 76) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_x(uint8_t * buf, int32_t len) {
  if (len < 3) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 115 && (buf)[2] == 120) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_E(uint8_t * buf, int32_t len) {
  if (len < 2) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 69) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_E_extern(uint8_t * buf, int32_t len) {
  if (len < 9) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 69 && (buf)[2] == 45 && (buf)[3] == 101 && (buf)[4] == 120 && (buf)[5] == 116 && (buf)[6] == 101 && (buf)[7] == 114 && (buf)[8] == 110) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_backend(uint8_t * buf, int32_t len) {
  if (len < 8) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 98 && (buf)[2] == 97 && (buf)[3] == 99 && (buf)[4] == 107 && (buf)[5] == 101 && (buf)[6] == 110 && (buf)[7] == 100) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_asm(uint8_t * buf, int32_t len) {
  if (len < 3) {   return 0;
 }
  if ((buf)[0] == 97 && (buf)[1] == 115 && (buf)[2] == 109) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_lsp(uint8_t * buf, int32_t len) {
  if (len < 5) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 45 && (buf)[2] == 108 && (buf)[3] == 115 && (buf)[4] == 112) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_eq_minus_target(uint8_t * buf, int32_t len) {
  if (len != 7) {   return 0;
 }
  if ((buf)[0] == 45 && (buf)[1] == 116 && (buf)[2] == 97 && (buf)[3] == 114 && (buf)[4] == 103 && (buf)[5] == 101 && (buf)[6] == 116) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_str_eq(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len) {
  if (a_len != b_len) {   return 0;
 }
  int32_t i = 0;
  while (i < a_len) {
    if ((a)[i] != (b)[i]) {   return 0;
 }
    ++i;
  }
  return 1;
}
XLANG_LIB_WEAK int32_t main_target_contains_arm(uint8_t * buf, int32_t len) {
  int32_t start = 0;
  while (start + 7 <= len) {
    if ((buf)[start] == 97 && (buf)[start + 1] == 97 && (buf)[start + 2] == 114 && (buf)[start + 3] == 99 && (buf)[start + 4] == 104 && (buf)[start + 5] == 54 && (buf)[start + 6] == 52) {   return 1;
 }
    ++start;
  }
  (start = (0));
  while (start + 5 <= len) {
    if ((buf)[start] == 97 && (buf)[start + 1] == 114 && (buf)[start + 2] == 109 && (buf)[start + 3] == 54 && (buf)[start + 4] == 52) {   return 1;
 }
    ++start;
  }
  return 0;
}
XLANG_LIB_WEAK int32_t main_target_contains_riscv(uint8_t * buf, int32_t len) {
  int32_t start = 0;
  while (start + 7 <= len) {
    if ((buf)[start] == 114 && (buf)[start + 1] == 105 && (buf)[start + 2] == 115 && (buf)[start + 3] == 99 && (buf)[start + 4] == 118 && (buf)[start + 5] == 54 && (buf)[start + 6] == 52) {   return 1;
 }
    ++start;
  }
  return 0;
}
XLANG_LIB_WEAK int32_t main_driver_argv_parse_x_path(int32_t argc, uint8_t * argv, struct main_DriverXEmitState * state) {
  ((state)->path_len = (0));
  (void)(driver_emit_lib_root_reset(main_driver_emit_state_key(state)));
  ((state)->emit_extern_imports = (0));
  ((state)->use_asm_backend = (1));
  ((state)->target_arch = (0));
  ((state)->out_path_len = (0));
  if (argc < 2) {   return 2;
 }
  uint8_t arg_buf[512] = { 0 };
  int32_t i = 1;
  int32_t has_o = 0;
  while (i < argc) {
    int32_t len = driver_get_argv_i(argc, argv, i, arg_buf, 512);
    if (len < 0) {   ++i;
  continue;
 }
    if (main_eq_minus_target(arg_buf, len) != 0 && i + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   int32_t tlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
  if (tlen >= 0 && main_target_contains_arm(arg_buf, tlen) != 0) {   ((state)->target_arch = (1));
 }
  if (tlen >= 0 && main_target_contains_riscv(arg_buf, tlen) != 0) {   ((state)->target_arch = (2));
 }
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_L(arg_buf, len) != 0) {   if (i + 1 >= argc) {   return 2;
 }
  if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   (void)(main_driver_emit_try_append_lib_from_argv(argc, argv, i + 1, state));
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_backend(arg_buf, len) != 0 && i + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   int32_t vlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
  if (vlen >= 0 && vlen == 1 && (arg_buf)[0] == 99) {   ((state)->use_asm_backend = (0));
 }
  if (vlen >= 0 && main_eq_asm(arg_buf, vlen) != 0) {   ((state)->use_asm_backend = (1));
 }
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (len == 2 && (arg_buf)[0] == 45 && (1 < 0 || (1) >= 512 ? (xlang_panic_(1, 0), (arg_buf)[0]) : (arg_buf)[1]) == 111) {   if (i + 1 < argc && driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   int32_t olen = driver_get_argv_i(argc, argv, i + 1, (state)->out_path_buf, 512);
  if (olen >= 0) {   ((state)->out_path_len = (olen));
 }
  i += 2;
 } else {   (has_o = (1));
  ++i;
 }
  continue;
 }
    if (len == 2 && (arg_buf)[0] == 45 && (1 < 0 || (1) >= 512 ? (xlang_panic_(1, 0), (arg_buf)[0]) : (arg_buf)[1]) == 79) {   if (i + 1 < argc && driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_x(arg_buf, len) != 0) {   ++i;
  continue;
 }
    if (main_eq_minus_E(arg_buf, len) != 0) {   ++i;
  continue;
 }
    if (main_eq_minus_E_extern(arg_buf, len) != 0) {   ++i;
  continue;
 }
    if ((state)->path_len == 0 && len > 0) {   int32_t k = 0;
  while (k < len && k < 512) {
    ((k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), 0) : (((state)->path_buf)[k] = (k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), (arg_buf)[0]) : (arg_buf)[k]), 0)));
    ++k;
  }
  ((state)->path_len = (len));
 }
    ++i;
  }
  if (has_o != 0) {   return 1;
 }
  if ((state)->path_len == 0) {   return 2;
 }
  (void)(main_driver_emit_ensure_default_lib_root(state));
  return 0;
}
XLANG_LIB_WEAK int32_t main_driver_argv_parse_x(int32_t argc, uint8_t * argv, struct main_DriverXEmitState * state) {
  ((state)->path_len = (0));
  (void)(driver_emit_lib_root_reset(main_driver_emit_state_key(state)));
  ((state)->emit_extern_imports = (0));
  ((state)->use_asm_backend = (0));
  ((state)->target_arch = (0));
  ((state)->out_path_len = (0));
  if (argc < 3) {   return 0;
 }
  uint8_t arg_buf[512] = { 0 };
  int32_t i = 1;
  while (i < argc) {
    int32_t len = driver_get_argv_i(argc, argv, i, arg_buf, 512);
    if (len < 0) {   ++i;
  continue;
 }
    if (main_eq_minus_L(arg_buf, len) != 0 && i + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   (void)(main_driver_emit_try_append_lib_from_argv(argc, argv, i + 1, state));
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_backend(arg_buf, len) != 0 && i + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   int32_t vlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
  if (vlen >= 0 && main_eq_asm(arg_buf, vlen) != 0) {   ((state)->use_asm_backend = (1));
 }
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_target(arg_buf, len) != 0 && i + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, 512) != 0) {   int32_t tlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
  if (tlen >= 0 && main_target_contains_arm(arg_buf, tlen) != 0) {   ((state)->target_arch = (1));
 }
  if (tlen >= 0 && main_target_contains_riscv(arg_buf, tlen) != 0) {   ((state)->target_arch = (2));
 }
  i += 2;
 } else {   ++i;
 }
  continue;
 }
    if (main_eq_minus_x(arg_buf, len) != 0) {   ++i;
  continue;
 }
    if (main_eq_minus_E(arg_buf, len) != 0) {   int32_t pi = i + 1;
  while (pi < argc) {
    int32_t plen_temp = driver_get_argv_i(argc, argv, pi, arg_buf, 512);
    if (plen_temp > 0 && main_eq_minus_L(arg_buf, plen_temp) != 0 && pi + 1 < argc) {   if (driver_compile_argv_next_is_value_c(argc, argv, pi, arg_buf, 512) != 0) {   (void)(main_driver_emit_try_append_lib_from_argv(argc, argv, pi + 1, state));
  pi += 2;
 } else {   ++pi;
 }
  continue;
 }
    if (plen_temp > 0 && main_eq_minus_x(arg_buf, plen_temp) != 0) {   ++pi;
  continue;
 }
    break;
  }
  if (pi < argc) {   int32_t opt_len = driver_get_argv_i(argc, argv, pi, arg_buf, 512);
  if (opt_len >= 0 && main_eq_minus_E_extern(arg_buf, opt_len) != 0) {   ((state)->emit_extern_imports = (1));
  ++pi;
 }
 }
  if (pi < argc) {   int32_t plen = driver_get_argv_i(argc, argv, pi, (state)->path_buf, 512);
  if (plen >= 0) {   ((state)->path_len = (plen));
  return 1;
 }
 }
 }
    ++i;
  }
  return 0;
}
XLANG_LIB_WEAK int32_t main_driver_run_x_emit_x(struct main_DriverXEmitState * state) {
  if ((state)->path_len >= 0 && (state)->path_len < 511) {   (((state)->path_len < 0 || ((state)->path_len) >= 512 ? (xlang_panic_(1, 0), 0) : (((state)->path_buf)[(state)->path_len] = ((uint8_t)(0)), 0)));
 }
  uint8_t loaded_buf[4194304] = { 0 };
  int32_t cap_i = 4194304;
  int32_t n = std_sys_read_file_into((&(((state)->path_buf)[0])), (&((loaded_buf)[0])), cap_i);
  if (n < 0) {   return 1;
 }
  uint8_t preprocess_buf[4194304] = { 0 };
  int32_t out_len = preprocess_x_buf((&((loaded_buf)[0])), n, (&((preprocess_buf)[0])), 4194304);
  if (out_len < 0) {   return 1;
 }
  uint8_t * arena_buf = driver_arena_buf();
  uint8_t * module_buf = driver_module_buf();
  struct ast_PipelineDepCtx ctx = main_pipeline_dep_ctx_for_emit((state)->use_asm_backend, (state)->target_arch);
  int32_t last_slash = -1;
  int32_t k = 0;
  while (k < (state)->path_len && k < 512) {
    if ((k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), ((state)->path_buf)[0]) : ((state)->path_buf)[k]) == 47) {   (last_slash = (k));
 }
    ++k;
  }
  if (last_slash >= 0) {   (k = (0));
  while (k < last_slash && k < 511) {
    ((k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), 0) : (((ctx).entry_dir_buf)[k] = (k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), ((state)->path_buf)[0]) : ((state)->path_buf)[k]), 0)));
    ++k;
  }
  ((k < 0 || (k) >= 512 ? (xlang_panic_(1, 0), 0) : (((ctx).entry_dir_buf)[k] = 0, 0)));
  ((ctx).entry_dir_len = (k));
 } else {   (((ctx).entry_dir_buf)[0] = (46));
  ((1 < 0 || (1) >= 512 ? (xlang_panic_(1, 0), 0) : (((ctx).entry_dir_buf)[1] = 0, 0)));
  ((ctx).entry_dir_len = (1));
 }
  ((ctx).num_lib_roots = (0));
  (void)(main_driver_emit_copy_lib_roots_to_ctx(state, (&(ctx))));
  struct codegen_CodegenOutBuf out = ({ struct codegen_CodegenOutBuf _t = { 0 }; _t.length = 0; _t; });
  size_t source_len = ((size_t)(out_len));
  int32_t rc = pipeline_run_x_pipeline_impl(module_buf, arena_buf, preprocess_buf, source_len, (&(out)), (&(ctx)));
  if (rc != 0) {   (void)(driver_pipeline_fail_code(rc, (&(((ctx).path_buf)[0]))));
  return 1;
 }
  int32_t len = (out).length;
  if ((state)->out_path_len == 0) {   (void)(driver_print_x_smoke_summary(module_buf, ((size_t)(len))));
 }
  if ((state)->out_path_len > 0) {   int32_t fd = driver_fs_open_write((state)->out_path_buf, (state)->out_path_len);
  if (fd < 0) {   return 1;
 }
  if (len > 262144) {   ptrdiff_t written = fs_posix_write_c(fd, (out).data, 262144);
  (void)(fs_posix_close_c(fd));
  if (written < 0 || ((int32_t)(written)) != 262144) {   return 1;
 }
 } else {   ptrdiff_t written = fs_posix_write_c(fd, (out).data, ((size_t)(len)));
  (void)(fs_posix_close_c(fd));
  if (written < 0 || ((int32_t)(written)) != len) {   return 1;
 }
 }
 } else {   if (len > 262144) {   ptrdiff_t written = fs_posix_write_c(1, (out).data, 262144);
  if (written < 0 || ((int32_t)(written)) != 262144) {   return 1;
 }
 } else {   ptrdiff_t written = fs_posix_write_c(1, (out).data, ((size_t)(len)));
  if (written < 0 || ((int32_t)(written)) != len) {   return 1;
 }
 }
 }
  return 0;
}
XLANG_LIB_WEAK int32_t main_run_compiler_x_path_impl(int32_t argc, uint8_t * argv) {
  struct main_DriverXEmitState state = main_driver_emit_state_default();
  int32_t r = main_driver_argv_parse_x_path(argc, argv, (&(state)));
  if (r == 1) {   return main_run_compiler_c_impl(argc, argv);
 }
  if (r == 2) {   return main_run_compiler_c_impl(argc, argv);
 }
  if ((state).use_asm_backend != 0) {   return main_run_compiler_c_impl(argc, argv);
 }
  if ((state).out_path_len > 0) {   return main_run_compiler_c_impl(argc, argv);
 }
  return main_driver_run_x_emit_x((&(state)));
}
XLANG_LIB_WEAK int32_t main_cmd_build(int32_t argc, uint8_t * argv) {
  if (argc < 2) {   return driver_build_build_x();
 }
  return main_run_compiler_x_path_impl(argc, argv);
}
/* Returns 1 if any argv[i] (i in [1, argc)) equals "-o" (the canonical short
 * form for output path), 0 otherwise. Used by main_cmd_run to distinguish
 * compile-only invocations from in-memory compile-and-run. PLATFORM: SHARED.
 * Contract: argc >= 1; argv may be null only when argc < 1 (returns 0). */
XLANG_LIB_WEAK int32_t main_argv_has_o_flag(int32_t argc, uint8_t * argv) {
  int32_t i = 1;
  uint8_t buf[8] = { 0 };
  while (i < argc) {
    int32_t len = driver_get_argv_i(argc, argv, i, (&((buf)[0])), 8);
    /* "-o" == bytes [45 ('-'), 111 ('o')] */
    if (len == 2 && (buf)[0] == 45 && (buf)[1] == 111) {   return 1;
 }
    ++i;
  }
  return 0;
}
XLANG_LIB_WEAK int32_t main_cmd_run(int32_t argc, uint8_t * argv) {
  if (argc < 2) {   return 1;
 }
  /* Detect an explicit user-supplied -o before driver_argv_ensure_run_o runs.
   * Why: driver_argv_ensure_run_o silently injects a temp -o when none is
   * present, so run_argv alone cannot tell whether the user asked for
   * compile-only. When -o is explicit, skip the exec path so the compiled
   * program's exit code does not leak through xlang's own exit status. */
  int32_t has_explicit_o = main_argv_has_o_flag(argc, argv);
  int32_t run_argc = argc;
  uint8_t * run_argv = driver_argv_ensure_run_o(argc, argv, &run_argc);
  if (has_explicit_o != 0) {
    /* Compile-only: do not set XLANG_RUN_QUIET (let cc warnings surface, since
     * the user explicitly requested an output path) and do not exec. */
    return main_run_compiler_x_path_impl(run_argc, run_argv);
  }
  /* mute generated-C warning noise so `xlang run`/bare `xlang file.x` prints
     only the program output; cc errors still surface (XLANG_RUN_QUIET only
     adds -w / -Wl,-w in xlang_invoke_cc_impl). */
  (void)setenv("XLANG_RUN_QUIET", "1", 1);
  int32_t rc = main_run_compiler_x_path_impl(run_argc, run_argv);
  if (rc == 0) {   return driver_exec_compiled(run_argc, run_argv);
 }
  return rc;
}
XLANG_LIB_WEAK int32_t main_entry(int32_t argc, uint8_t * argv) {
  uint8_t arg_buf[128] = { 0 };
  int32_t i = 1;
  while (i < argc) {
    int32_t len = driver_get_argv_i(argc, argv, i, arg_buf, 64);
    if (len >= 0 && main_eq_minus_lsp(arg_buf, len) != 0) {   return typeck_lsp_main();
 }
    ++i;
  }
  if (argc >= 2) {   int32_t alen = driver_get_argv_i(argc, argv, 1, arg_buf, 64);
  if (alen > 0 && (arg_buf)[0] != 45) {   uint8_t w_build[5] = { 98, 117, 105, 108, 100 };
  uint8_t w_run[3] = { 114, 117, 110 };
  uint8_t w_fmt[3] = { 102, 109, 116 };
  uint8_t w_check[5] = { 99, 104, 101, 99, 107 };
  uint8_t w_test[4] = { 116, 101, 115, 116 };
  if (main_str_eq((&((arg_buf)[0])), alen, (&((w_build)[0])), 5) != 0) {   return main_cmd_build(argc - 1, driver_argv_drop_subcommand(argc, argv));
 }
  if (main_str_eq((&((arg_buf)[0])), alen, (&((w_run)[0])), 3) != 0) {   return main_cmd_run(argc - 1, driver_argv_drop_subcommand(argc, argv));
 }
  if (main_str_eq((&((arg_buf)[0])), alen, (&((w_fmt)[0])), 3) != 0) {   return driver_cmd_fmt(argc - 1, driver_argv_drop_subcommand(argc, argv));
 }
  if (main_str_eq((&((arg_buf)[0])), alen, (&((w_check)[0])), 5) != 0) {   return driver_cmd_check(argc - 1, driver_argv_drop_subcommand(argc, argv));
 }
  if (main_str_eq((&((arg_buf)[0])), alen, (&((w_test)[0])), 4) != 0) {   return driver_cmd_test(argc - 1, driver_argv_drop_subcommand(argc, argv));
 }
  /* Bare path (ends with .x or contains / or \\): run semantics; with -o compile-only.
   * PLATFORM: SHARED — matches main.x entry(); do not print usage for historical `xlang file.x -o`. */
  {
    int32_t looks = 0;
    if (alen >= 2 && (arg_buf)[alen - 2] == 46 && (arg_buf)[alen - 1] == 120) {
      looks = 1;
    } else {
      int32_t pi = 0;
      while (pi < alen) {
        if ((arg_buf)[pi] == 47 || (arg_buf)[pi] == 92) {
          looks = 1;
          break;
        }
        ++pi;
      }
    }
    if (looks != 0) {
      return main_cmd_run(argc, argv);
    }
  }
  driver_print_usage_write();
  return 1;
 }
 }
  struct main_DriverXEmitState state = main_driver_emit_state_default();
  if (main_driver_argv_parse_x(argc, argv, (&(state))) != 0) {   (void)(driver_run_x_emit_c_set_emit_extern((state).emit_extern_imports));
  (void)(driver_run_x_emit_c_set_path((state).path_buf, (state).path_len));
  int32_t k = 0;
  int32_t n_roots = driver_emit_lib_root_count(main_driver_emit_state_key((&(state))));
  uint8_t lib_tmp[256] = { 0 };
  while (k < n_roots) {
    int32_t llen = driver_emit_lib_root_len(main_driver_emit_state_key((&(state))), k);
    (void)(driver_emit_lib_root_copy(main_driver_emit_state_key((&(state))), k, (&((lib_tmp)[0])), 256));
    (void)(driver_run_x_emit_c_set_lib(k, (&((lib_tmp)[0])), llen));
    ++k;
  }
  (void)(driver_run_x_emit_c_set_n_lib_roots(n_roots));
  return driver_run_compiler_full(argc, argv);
 }
  return main_run_compiler_x_path_impl(argc, argv);
}
