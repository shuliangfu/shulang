/* seeds/rt_run_x_emit_surface.from_x.c
 * R2 full surface — isomorphic with src/runtime/rt_run_x_emit.x
 * Product PREFER_X_O: full .x + rest marker (H=0)
 * Regen: xlang -E ... rt_run_x_emit.x | strip DBG + polish libc redecl
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
extern int32_t wp_path(void);
extern int32_t wp_src(void);
extern int32_t wp_arena(void);
extern int32_t wp_module(void);
extern int32_t wp_entry(void);
extern int32_t wp_dsrc(void);
extern int32_t wp_dpath(void);
extern int32_t wp_dlens(void);
extern int32_t wp_dar(void);
extern int32_t wp_dmod(void);
extern int32_t wp_out(void);
extern int32_t wp_pctx(void);
extern int32_t wp_kind(void);
extern int32_t wp_code(void);
extern int32_t wp_msg(void);
extern int32_t wp_lib(void);
extern int32_t wi_nlib(void);
extern int32_t wi_ndeps(void);
extern int32_t wi_asm(void);
extern int32_t wi_nimp(void);
extern int32_t wi_main(void);
extern int32_t wz_slen(void);
extern int32_t wz_asz(void);
extern int32_t wz_msz(void);
extern void rt_xe_fill_kind_io(uint8_t * k);
extern void rt_xe_fill_code_io001(uint8_t * c);
extern void rt_xe_fill_kind_pp(uint8_t * k);
extern void rt_xe_fill_code_pp002(uint8_t * c);
extern void rt_xe_fill_kind_pipe(uint8_t * k);
extern void rt_xe_fill_code_xp003(uint8_t * c);
extern void rt_xe_fill_code_xp005(uint8_t * c);
extern void rt_xe_fill_code_xp006(uint8_t * c);
extern void rt_xe_fill_code_xp007(uint8_t * c);
extern void rt_xe_fill_code_xp008(uint8_t * c);
extern void rt_xe_fill_kind_parse(uint8_t * k);
extern void rt_xe_fill_code_p001(uint8_t * c);
extern void rt_xe_fill_kind_cg(uint8_t * k);
extern void rt_xe_fill_code_cg004(uint8_t * c);
extern void rt_xe_msg_cannot_read(uint8_t * m);
extern void rt_xe_msg_pp_failed(uint8_t * m);
extern void rt_xe_msg_alloc_failed(uint8_t * m);
extern void rt_xe_msg_src_too_large(uint8_t * m);
extern void rt_xe_msg_parse_failed(uint8_t * m);
extern void rt_xe_msg_dep_alloc(uint8_t * m);
extern void rt_xe_msg_out_ctx_alloc(uint8_t * m);
extern void rt_xe_msg_dep_prerun(uint8_t * m);
extern void rt_xe_msg_pipe_failed(uint8_t * m);
extern void rt_xe_msg_no_funcs(uint8_t * m);
extern void rt_xe_msg_empty_buf(uint8_t * m);
extern void rt_xe_msg_expected_lit(uint8_t * m);
extern void rt_xe_diag(uint8_t * path, int32_t kind_fn, int32_t code_fn, int32_t msg_fn);
extern int32_t rt_xe_step_read_pp(void);
extern int32_t rt_xe_step_parse(void);
extern int32_t rt_xe_step_load_deps(void);
extern int32_t rt_xe_step_prerun(void);
extern int32_t rt_xe_step_finish(void);
extern int32_t driver_run_x_emit_c(void);
extern uint8_t * runtime_read_file_malloc(uint8_t * path, size_t * out_len);
extern uint8_t * xlang_preprocess_with_path(uint8_t * data, size_t len, uint8_t * path, uint8_t * defines, int32_t n_defines, size_t * out_len);
extern uint8_t * xlang_preprocess(uint8_t * data, size_t len, uint8_t * defines, int32_t n_defines, size_t * out_len);
extern void pipeline_diag_emitted_reset(void);
extern int32_t pipeline_diag_emitted_get(void);
extern void diag_set_file(uint8_t * path, uint8_t * src, size_t len);
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_module(void);
extern void parser_parse_into_init(uint8_t * module, uint8_t * arena);
extern void parser_parse_into_set_main_index(uint8_t * module, int32_t main_idx);
extern int32_t driver_get_module_num_funcs(uint8_t * m);
extern int32_t parser_get_module_num_imports(uint8_t * module);
extern void xlang_get_entry_dir(uint8_t * path, uint8_t * out, size_t out_sz);
extern void pipeline_set_entry_dir(uint8_t * dir);
extern int32_t driver_x_emit_asm_direct_import_only(uint8_t * input_path);
extern int32_t driver_x_emit_asm_dep_parse_only_ok(uint8_t * input_path, uint8_t * dep_path);
extern int32_t driver_x_emit_asm_dep_parse_skip_typeck_ok(uint8_t * input_path, uint8_t * dep_path);
extern void driver_dep_seeded_clear_all(void);
extern void driver_set_current_dep_path_for_codegen(uint8_t * path);
extern int32_t xlang_pipeline_dep_prerun_parse_skip_typeck(uint8_t * mod, uint8_t * arena, uint8_t * src, size_t len, uint8_t * out, uint8_t * ctx);
extern int32_t xlang_pipeline_dep_prerun_parse_only(uint8_t * mod, uint8_t * arena, uint8_t * src, size_t len);
extern int32_t xlang_pipeline_dep_prerun_typeck_only(uint8_t * mod, uint8_t * arena, uint8_t * src, size_t len, uint8_t * out, uint8_t * ctx);
extern void driver_dep_publish_slot(int32_t j, uint8_t * arena, uint8_t * module, uint8_t * path);
extern void pipeline_set_dep_slots(uint8_t * arenas, uint8_t * modules);
extern void driver_dep_seed_slots(uint8_t * arenas, uint8_t * modules, int32_t n);
extern void codegen_set_dep_slots_for_x_pipeline(uint8_t * mods, uint8_t * paths, int32_t n);
extern int32_t runtime_report_precise_parse_failure_if_known(uint8_t * input_path, uint8_t * src, size_t src_len);
extern int32_t driver_x_emit_try_extern_via_cparser(uint8_t * input_path);
extern void pipeline_dep_ctx_heap_destroy(uint8_t * ctx);
extern int32_t xlang_pipeline_run_x_pipeline_large_stack(uint8_t * module, uint8_t * arena, uint8_t * src, size_t src_len, uint8_t * out_buf, uint8_t * pctx);
extern void xlang_pipeline_fill_ctx_path_buffers(uint8_t * ctx, uint8_t * entry_dir, uint8_t * lib_roots, int32_t n_lib);
extern int32_t xlang_driver_x_emit_lib_name_into(uint8_t * out, int32_t cap);
extern void xlang_pipeline_pctx_set_entry_lib_prefix(uint8_t * ctx, uint8_t * name, int32_t name_len);
extern void xlang_pipeline_pctx_seed_dep_import_paths_only(uint8_t * ctx, uint8_t * import_paths, int32_t n);
extern void xlang_pipeline_pctx_seed_dep_slots(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ar, uint8_t * dep_paths, int32_t n);
extern void xlang_pipeline_one_ctx_for_dep_prerun(uint8_t * ctx, int32_t j, uint8_t * dep_mods, uint8_t * dep_ar, uint8_t * dep_paths, int32_t n, uint8_t * dep_src, size_t dep_len);
extern int32_t xlang_load_direct_imports_for_asm_layout(uint8_t * module, uint8_t * lib_roots, int32_t n_lib, uint8_t * entry_dir, uint8_t * defines, int32_t n_defines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n_deps);
extern int32_t xlang_collect_dep_paths_transitive(uint8_t * module, size_t arena_sz, size_t module_sz, uint8_t * lib_roots, int32_t n_lib, uint8_t * entry_dir, uint8_t * defines, int32_t n_defines, uint8_t * cpaths, int32_t * n_closure);
extern int32_t xlang_merge_direct_then_transitive_dep_paths(uint8_t * module, int32_t n_imports, uint8_t * cpaths, int32_t n_closure, uint8_t * dep_paths, int32_t * n_deps);
extern void xlang_resolve_import_file_path_multi(uint8_t * lib_roots, int32_t n_lib, uint8_t * entry_dir, uint8_t * import_path, uint8_t * resolved, size_t resolved_sz);
extern void pipeline_diag_import_open_fail_once(uint8_t * dep, uint8_t * resolved);
extern uint8_t * xlang_dep_prerun_entry_dir(uint8_t * entry_dir, uint8_t * lib_roots, int32_t n_lib);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern uint8_t * driver_x_emit_take_c_path(void);
extern int32_t driver_x_emit_take_want_extern(void);
extern void driver_x_emit_stdout_set_unbuffered(void);
extern int32_t driver_x_emit_fwrite_stdout(uint8_t * data, int32_t len);
extern uint8_t * driver_codegen_outbuf_calloc(void);
extern void driver_codegen_outbuf_free(uint8_t * p);
extern int32_t driver_codegen_outbuf_len(uint8_t * p);
extern uint8_t * driver_codegen_outbuf_data(uint8_t * p);
extern uint8_t * driver_pipeline_dep_ctx_calloc(void);
extern uint8_t * driver_ptr_table_calloc(int32_t n);
extern void driver_ptr_table_free(uint8_t * t);
extern uint8_t * driver_ptr_table_get(uint8_t * t, int32_t i);
extern void driver_ptr_table_set(uint8_t * t, int32_t i, uint8_t * p);
extern uint8_t * driver_size_table_calloc(int32_t n);
extern void driver_size_table_free(uint8_t * t);
extern size_t driver_size_table_get(uint8_t * t, int32_t i);
extern int32_t driver_parse_into_buf_rc(uint8_t * arena, uint8_t * module, uint8_t * data, int32_t len, int32_t * out_main_idx);
extern uint8_t * driver_diag_snapshot_alloc(void);
extern void driver_diag_snapshot_free(uint8_t * s);
extern void driver_diag_push_file(uint8_t * snap, uint8_t * path, uint8_t * src, size_t len);
extern void driver_diag_restore(uint8_t * snap);
extern void driver_typeck_ndep_set(int32_t n);
extern void driver_typeck_dep_ptrs_set(int32_t j, uint8_t * mod, uint8_t * arena);
extern uint8_t * driver_path_max_slot(void);
extern uint8_t * driver_entry_dir_slot(void);
extern uint8_t * driver_x_emit_effective_lib_roots(int32_t * n_out);
extern int32_t driver_parser_diag_fail_tok_kind(uint8_t * src, size_t len);
extern void driver_pipeline_dep_ctx_set_use_asm(uint8_t * ctx, int32_t v);
extern void driver_x_emit_work_reset(void);
extern uint8_t * driver_x_emit_work_p_get(int32_t i);
extern void driver_x_emit_work_p_set(int32_t i, uint8_t * v);
extern int32_t driver_x_emit_work_i_get(int32_t i);
extern void driver_x_emit_work_i_set(int32_t i, int32_t v);
extern size_t driver_x_emit_work_z_get(int32_t i);
extern void driver_x_emit_work_z_set(int32_t i, size_t v);
extern void driver_x_emit_work_cleanup(void);
extern int32_t typeck_set_allow_legacy_extern_calls(int32_t allow);
int32_t wp_path(void) {
  return 0;
}
int32_t wp_src(void) {
  return 1;
}
int32_t wp_arena(void) {
  return 3;
}
int32_t wp_module(void) {
  return 4;
}
int32_t wp_entry(void) {
  return 5;
}
int32_t wp_dsrc(void) {
  return 6;
}
int32_t wp_dpath(void) {
  return 7;
}
int32_t wp_dlens(void) {
  return 8;
}
int32_t wp_dar(void) {
  return 9;
}
int32_t wp_dmod(void) {
  return 10;
}
int32_t wp_out(void) {
  return 11;
}
int32_t wp_pctx(void) {
  return 12;
}
int32_t wp_kind(void) {
  return 19;
}
int32_t wp_code(void) {
  return 20;
}
int32_t wp_msg(void) {
  return 21;
}
int32_t wp_lib(void) {
  return 24;
}
int32_t wi_nlib(void) {
  return 1;
}
int32_t wi_ndeps(void) {
  return 2;
}
int32_t wi_asm(void) {
  return 3;
}
int32_t wi_nimp(void) {
  return 4;
}
int32_t wi_main(void) {
  return 5;
}
int32_t wz_slen(void) {
  return 0;
}
int32_t wz_asz(void) {
  return 2;
}
int32_t wz_msz(void) {
  return 3;
}
void rt_xe_fill_kind_io(uint8_t * k) {
  (void)(((k)[0] = 105));
  (void)(((k)[1] = 111));
  (void)(((k)[2] = 32));
  (void)(((k)[3] = 101));
  (void)(((k)[4] = 114));
  (void)(((k)[5] = 114));
  (void)(((k)[6] = 111));
  (void)(((k)[7] = 114));
  (void)(((k)[8] = 0));
}
void rt_xe_fill_code_io001(uint8_t * c) {
  (void)(((c)[0] = 73));
  (void)(((c)[1] = 79));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 49));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_kind_pp(uint8_t * k) {
  (void)(((k)[0] = 112));
  (void)(((k)[1] = 114));
  (void)(((k)[2] = 101));
  (void)(((k)[3] = 112));
  (void)(((k)[4] = 114));
  (void)(((k)[5] = 111));
  (void)(((k)[6] = 99));
  (void)(((k)[7] = 101));
  (void)(((k)[8] = 115));
  (void)(((k)[9] = 115));
  (void)(((k)[10] = 32));
  (void)(((k)[11] = 101));
  (void)(((k)[12] = 114));
  (void)(((k)[13] = 114));
  (void)(((k)[14] = 111));
  (void)(((k)[15] = 114));
  (void)(((k)[16] = 0));
}
void rt_xe_fill_code_pp002(uint8_t * c) {
  (void)(((c)[0] = 80));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 50));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_kind_pipe(uint8_t * k) {
  (void)(((k)[0] = 112));
  (void)(((k)[1] = 105));
  (void)(((k)[2] = 112));
  (void)(((k)[3] = 101));
  (void)(((k)[4] = 108));
  (void)(((k)[5] = 105));
  (void)(((k)[6] = 110));
  (void)(((k)[7] = 101));
  (void)(((k)[8] = 32));
  (void)(((k)[9] = 101));
  (void)(((k)[10] = 114));
  (void)(((k)[11] = 114));
  (void)(((k)[12] = 111));
  (void)(((k)[13] = 114));
  (void)(((k)[14] = 0));
}
void rt_xe_fill_code_xp003(uint8_t * c) {
  (void)(((c)[0] = 88));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 51));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_code_xp005(uint8_t * c) {
  (void)(((c)[0] = 88));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 53));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_code_xp006(uint8_t * c) {
  (void)(((c)[0] = 88));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 54));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_code_xp007(uint8_t * c) {
  (void)(((c)[0] = 88));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 55));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_code_xp008(uint8_t * c) {
  (void)(((c)[0] = 88));
  (void)(((c)[1] = 80));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 56));
  (void)(((c)[5] = 0));
}
void rt_xe_fill_kind_parse(uint8_t * k) {
  (void)(((k)[0] = 112));
  (void)(((k)[1] = 97));
  (void)(((k)[2] = 114));
  (void)(((k)[3] = 115));
  (void)(((k)[4] = 101));
  (void)(((k)[5] = 32));
  (void)(((k)[6] = 101));
  (void)(((k)[7] = 114));
  (void)(((k)[8] = 114));
  (void)(((k)[9] = 111));
  (void)(((k)[10] = 114));
  (void)(((k)[11] = 0));
}
void rt_xe_fill_code_p001(uint8_t * c) {
  (void)(((c)[0] = 80));
  (void)(((c)[1] = 48));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 49));
  (void)(((c)[4] = 0));
}
void rt_xe_fill_kind_cg(uint8_t * k) {
  (void)(((k)[0] = 99));
  (void)(((k)[1] = 111));
  (void)(((k)[2] = 100));
  (void)(((k)[3] = 101));
  (void)(((k)[4] = 103));
  (void)(((k)[5] = 101));
  (void)(((k)[6] = 110));
  (void)(((k)[7] = 32));
  (void)(((k)[8] = 101));
  (void)(((k)[9] = 114));
  (void)(((k)[10] = 114));
  (void)(((k)[11] = 111));
  (void)(((k)[12] = 114));
  (void)(((k)[13] = 0));
}
void rt_xe_fill_code_cg004(uint8_t * c) {
  (void)(((c)[0] = 67));
  (void)(((c)[1] = 71));
  (void)(((c)[2] = 48));
  (void)(((c)[3] = 48));
  (void)(((c)[4] = 52));
  (void)(((c)[5] = 0));
}
void rt_xe_msg_cannot_read(uint8_t * m) {
  (void)(((m)[0] = 99));
  (void)(((m)[1] = 97));
  (void)(((m)[2] = 110));
  (void)(((m)[3] = 110));
  (void)(((m)[4] = 111));
  (void)(((m)[5] = 116));
  (void)(((m)[6] = 32));
  (void)(((m)[7] = 114));
  (void)(((m)[8] = 101));
  (void)(((m)[9] = 97));
  (void)(((m)[10] = 100));
  (void)(((m)[11] = 32));
  (void)(((m)[12] = 102));
  (void)(((m)[13] = 105));
  (void)(((m)[14] = 108));
  (void)(((m)[15] = 101));
  (void)(((m)[16] = 0));
}
void rt_xe_msg_pp_failed(uint8_t * m) {
  (void)(((m)[0] = 112));
  (void)(((m)[1] = 114));
  (void)(((m)[2] = 101));
  (void)(((m)[3] = 112));
  (void)(((m)[4] = 114));
  (void)(((m)[5] = 111));
  (void)(((m)[6] = 99));
  (void)(((m)[7] = 101));
  (void)(((m)[8] = 115));
  (void)(((m)[9] = 115));
  (void)(((m)[10] = 32));
  (void)(((m)[11] = 102));
  (void)(((m)[12] = 97));
  (void)(((m)[13] = 105));
  (void)(((m)[14] = 108));
  (void)(((m)[15] = 101));
  (void)(((m)[16] = 100));
  (void)(((m)[17] = 0));
}
void rt_xe_msg_alloc_failed(uint8_t * m) {
  (void)(((m)[0] = 46));
  (void)(((m)[1] = 120));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 112));
  (void)(((m)[4] = 105));
  (void)(((m)[5] = 112));
  (void)(((m)[6] = 101));
  (void)(((m)[7] = 108));
  (void)(((m)[8] = 105));
  (void)(((m)[9] = 110));
  (void)(((m)[10] = 101));
  (void)(((m)[11] = 32));
  (void)(((m)[12] = 97));
  (void)(((m)[13] = 108));
  (void)(((m)[14] = 108));
  (void)(((m)[15] = 111));
  (void)(((m)[16] = 99));
  (void)(((m)[17] = 97));
  (void)(((m)[18] = 116));
  (void)(((m)[19] = 105));
  (void)(((m)[20] = 111));
  (void)(((m)[21] = 110));
  (void)(((m)[22] = 32));
  (void)(((m)[23] = 102));
  (void)(((m)[24] = 97));
  (void)(((m)[25] = 105));
  (void)(((m)[26] = 108));
  (void)(((m)[27] = 101));
  (void)(((m)[28] = 100));
  (void)(((m)[29] = 0));
}
void rt_xe_msg_src_too_large(uint8_t * m) {
  (void)(((m)[0] = 46));
  (void)(((m)[1] = 120));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 45));
  (void)(((m)[4] = 69));
  (void)(((m)[5] = 32));
  (void)(((m)[6] = 115));
  (void)(((m)[7] = 111));
  (void)(((m)[8] = 117));
  (void)(((m)[9] = 114));
  (void)(((m)[10] = 99));
  (void)(((m)[11] = 101));
  (void)(((m)[12] = 32));
  (void)(((m)[13] = 116));
  (void)(((m)[14] = 111));
  (void)(((m)[15] = 111));
  (void)(((m)[16] = 32));
  (void)(((m)[17] = 108));
  (void)(((m)[18] = 97));
  (void)(((m)[19] = 114));
  (void)(((m)[20] = 103));
  (void)(((m)[21] = 101));
  (void)(((m)[22] = 0));
}
void rt_xe_msg_parse_failed(uint8_t * m) {
  (void)(((m)[0] = 46));
  (void)(((m)[1] = 120));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 45));
  (void)(((m)[4] = 69));
  (void)(((m)[5] = 32));
  (void)(((m)[6] = 112));
  (void)(((m)[7] = 97));
  (void)(((m)[8] = 114));
  (void)(((m)[9] = 115));
  (void)(((m)[10] = 101));
  (void)(((m)[11] = 32));
  (void)(((m)[12] = 102));
  (void)(((m)[13] = 97));
  (void)(((m)[14] = 105));
  (void)(((m)[15] = 108));
  (void)(((m)[16] = 101));
  (void)(((m)[17] = 100));
  (void)(((m)[18] = 0));
}
void rt_xe_msg_dep_alloc(uint8_t * m) {
  (void)(((m)[0] = 100));
  (void)(((m)[1] = 101));
  (void)(((m)[2] = 112));
  (void)(((m)[3] = 32));
  (void)(((m)[4] = 97));
  (void)(((m)[5] = 108));
  (void)(((m)[6] = 108));
  (void)(((m)[7] = 111));
  (void)(((m)[8] = 99));
  (void)(((m)[9] = 32));
  (void)(((m)[10] = 102));
  (void)(((m)[11] = 97));
  (void)(((m)[12] = 105));
  (void)(((m)[13] = 108));
  (void)(((m)[14] = 101));
  (void)(((m)[15] = 100));
  (void)(((m)[16] = 0));
}
void rt_xe_msg_out_ctx_alloc(uint8_t * m) {
  (void)(((m)[0] = 111));
  (void)(((m)[1] = 117));
  (void)(((m)[2] = 116));
  (void)(((m)[3] = 47));
  (void)(((m)[4] = 99));
  (void)(((m)[5] = 116));
  (void)(((m)[6] = 120));
  (void)(((m)[7] = 32));
  (void)(((m)[8] = 97));
  (void)(((m)[9] = 108));
  (void)(((m)[10] = 108));
  (void)(((m)[11] = 111));
  (void)(((m)[12] = 99));
  (void)(((m)[13] = 32));
  (void)(((m)[14] = 102));
  (void)(((m)[15] = 97));
  (void)(((m)[16] = 105));
  (void)(((m)[17] = 108));
  (void)(((m)[18] = 101));
  (void)(((m)[19] = 100));
  (void)(((m)[20] = 0));
}
void rt_xe_msg_dep_prerun(uint8_t * m) {
  (void)(((m)[0] = 100));
  (void)(((m)[1] = 101));
  (void)(((m)[2] = 112));
  (void)(((m)[3] = 32));
  (void)(((m)[4] = 112));
  (void)(((m)[5] = 114));
  (void)(((m)[6] = 101));
  (void)(((m)[7] = 114));
  (void)(((m)[8] = 117));
  (void)(((m)[9] = 110));
  (void)(((m)[10] = 32));
  (void)(((m)[11] = 102));
  (void)(((m)[12] = 97));
  (void)(((m)[13] = 105));
  (void)(((m)[14] = 108));
  (void)(((m)[15] = 101));
  (void)(((m)[16] = 100));
  (void)(((m)[17] = 0));
}
void rt_xe_msg_pipe_failed(uint8_t * m) {
  (void)(((m)[0] = 46));
  (void)(((m)[1] = 120));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 112));
  (void)(((m)[4] = 105));
  (void)(((m)[5] = 112));
  (void)(((m)[6] = 101));
  (void)(((m)[7] = 108));
  (void)(((m)[8] = 105));
  (void)(((m)[9] = 110));
  (void)(((m)[10] = 101));
  (void)(((m)[11] = 32));
  (void)(((m)[12] = 102));
  (void)(((m)[13] = 97));
  (void)(((m)[14] = 105));
  (void)(((m)[15] = 108));
  (void)(((m)[16] = 101));
  (void)(((m)[17] = 100));
  (void)(((m)[18] = 0));
}
void rt_xe_msg_no_funcs(uint8_t * m) {
  (void)(((m)[0] = 110));
  (void)(((m)[1] = 111));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 102));
  (void)(((m)[4] = 117));
  (void)(((m)[5] = 110));
  (void)(((m)[6] = 99));
  (void)(((m)[7] = 116));
  (void)(((m)[8] = 105));
  (void)(((m)[9] = 111));
  (void)(((m)[10] = 110));
  (void)(((m)[11] = 115));
  (void)(((m)[12] = 0));
}
void rt_xe_msg_empty_buf(uint8_t * m) {
  (void)(((m)[0] = 99));
  (void)(((m)[1] = 103));
  (void)(((m)[2] = 32));
  (void)(((m)[3] = 98));
  (void)(((m)[4] = 117));
  (void)(((m)[5] = 102));
  (void)(((m)[6] = 32));
  (void)(((m)[7] = 101));
  (void)(((m)[8] = 109));
  (void)(((m)[9] = 112));
  (void)(((m)[10] = 116));
  (void)(((m)[11] = 121));
  (void)(((m)[12] = 0));
}
void rt_xe_msg_expected_lit(uint8_t * m) {
  (void)(((m)[0] = 101));
  (void)(((m)[1] = 120));
  (void)(((m)[2] = 112));
  (void)(((m)[3] = 101));
  (void)(((m)[4] = 99));
  (void)(((m)[5] = 116));
  (void)(((m)[6] = 101));
  (void)(((m)[7] = 100));
  (void)(((m)[8] = 32));
  (void)(((m)[9] = 108));
  (void)(((m)[10] = 105));
  (void)(((m)[11] = 116));
  (void)(((m)[12] = 101));
  (void)(((m)[13] = 114));
  (void)(((m)[14] = 97));
  (void)(((m)[15] = 108));
  (void)(((m)[16] = 0));
}
void rt_xe_diag(uint8_t * path, int32_t kind_fn, int32_t code_fn, int32_t msg_fn) {
  uint8_t * k = ((uint8_t *)(0));
  uint8_t * c = ((uint8_t *)(0));
  uint8_t * m = ((uint8_t *)(0));
  {
    (void)((k = driver_x_emit_work_p_get(wp_kind())));
    (void)((c = driver_x_emit_work_p_get(wp_code())));
    (void)((m = driver_x_emit_work_p_get(wp_msg())));
  }
  if ((k ==((uint8_t *)(0)))) {
    return;
  }
  if ((kind_fn ==1)) {
    (void)(rt_xe_fill_kind_io(k));
  }
  if ((kind_fn ==2)) {
    (void)(rt_xe_fill_kind_pp(k));
  }
  if ((kind_fn ==3)) {
    (void)(rt_xe_fill_kind_pipe(k));
  }
  if ((kind_fn ==4)) {
    (void)(rt_xe_fill_kind_parse(k));
  }
  if ((kind_fn ==5)) {
    (void)(rt_xe_fill_kind_cg(k));
  }
  if ((code_fn ==1)) {
    (void)(rt_xe_fill_code_io001(c));
  }
  if ((code_fn ==2)) {
    (void)(rt_xe_fill_code_pp002(c));
  }
  if ((code_fn ==3)) {
    (void)(rt_xe_fill_code_xp003(c));
  }
  if ((code_fn ==5)) {
    (void)(rt_xe_fill_code_xp005(c));
  }
  if ((code_fn ==6)) {
    (void)(rt_xe_fill_code_xp006(c));
  }
  if ((code_fn ==7)) {
    (void)(rt_xe_fill_code_xp007(c));
  }
  if ((code_fn ==8)) {
    (void)(rt_xe_fill_code_xp008(c));
  }
  if ((code_fn ==9)) {
    (void)(rt_xe_fill_code_p001(c));
  }
  if ((code_fn ==10)) {
    (void)(rt_xe_fill_code_cg004(c));
  }
  if ((msg_fn ==1)) {
    (void)(rt_xe_msg_cannot_read(m));
  }
  if ((msg_fn ==2)) {
    (void)(rt_xe_msg_pp_failed(m));
  }
  if ((msg_fn ==3)) {
    (void)(rt_xe_msg_alloc_failed(m));
  }
  if ((msg_fn ==4)) {
    (void)(rt_xe_msg_src_too_large(m));
  }
  if ((msg_fn ==5)) {
    (void)(rt_xe_msg_parse_failed(m));
  }
  if ((msg_fn ==6)) {
    (void)(rt_xe_msg_dep_alloc(m));
  }
  if ((msg_fn ==7)) {
    (void)(rt_xe_msg_out_ctx_alloc(m));
  }
  if ((msg_fn ==8)) {
    (void)(rt_xe_msg_dep_prerun(m));
  }
  if ((msg_fn ==9)) {
    (void)(rt_xe_msg_pipe_failed(m));
  }
  if ((msg_fn ==10)) {
    (void)(rt_xe_msg_no_funcs(m));
  }
  if ((msg_fn ==11)) {
    (void)(rt_xe_msg_empty_buf(m));
  }
  if ((msg_fn ==12)) {
    (void)(rt_xe_msg_expected_lit(m));
  }
  {
    (void)(diag_report_with_code(path, 0, 0, k, c, m, ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
int32_t rt_xe_step_read_pp(void) {
  uint8_t * path = ((uint8_t *)(0));
  uint8_t * raw = ((uint8_t *)(0));
  size_t raw_len = 0;
  uint8_t * src = ((uint8_t *)(0));
  size_t src_len = 0;
  int32_t rc = 0;
  {
    (void)((path = driver_x_emit_work_p_get(wp_path())));
    (void)((raw = runtime_read_file_malloc(path, &(raw_len))));
  }
  if ((raw ==((uint8_t *)(0)))) {
    (void)(rt_xe_diag(path, 1, 1, 1));
    return 1;
  }
  {
    (void)(pipeline_diag_emitted_reset());
    (void)((src = xlang_preprocess_with_path(raw, raw_len, path, ((uint8_t *)(0)), 0, &(src_len))));
    (void)(free(raw));
  }
  if ((src ==((uint8_t *)(0)))) {
    {
      (void)((rc = pipeline_diag_emitted_get()));
    }
    if ((rc ==0)) {
      (void)(rt_xe_diag(path, 2, 2, 2));
    }
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_src(), src));
    (void)(driver_x_emit_work_z_set(wz_slen(), src_len));
    (void)(diag_set_file(path, src, src_len));
  }
  return 0;
}
int32_t rt_xe_step_parse(void) {
  uint8_t * path = ((uint8_t *)(0));
  uint8_t * src = ((uint8_t *)(0));
  size_t src_len = 0;
  uint8_t * arena = ((uint8_t *)(0));
  uint8_t * module = ((uint8_t *)(0));
  size_t asz = 0;
  size_t msz = 0;
  int32_t main_idx = -(1);
  int32_t pr_ok = 0;
  int32_t rc = 0;
  int32_t fail_tok = 0;
  {
    (void)((path = driver_x_emit_work_p_get(wp_path())));
    (void)((src = driver_x_emit_work_p_get(wp_src())));
    (void)((src_len = driver_x_emit_work_z_get(wz_slen())));
    (void)((asz = pipeline_sizeof_arena()));
    (void)((msz = pipeline_sizeof_module()));
    (void)((arena = malloc(asz)));
    (void)((module = malloc(msz)));
  }
  if ((arena ==((uint8_t *)(0)))) {
    (void)(rt_xe_diag(((uint8_t *)(0)), 3, 5, 3));
    return 1;
  }
  if ((module ==((uint8_t *)(0)))) {
    {
      (void)(free(arena));
    }
    (void)(rt_xe_diag(((uint8_t *)(0)), 3, 5, 3));
    return 1;
  }
  if ((src_len > ((size_t)(2147483647)))) {
    {
      (void)(free(arena));
      (void)(free(module));
    }
    (void)(rt_xe_diag(path, 3, 7, 4));
    return 1;
  }
  {
    (void)(memset(arena, 0, asz));
    (void)(memset(module, 0, msz));
    (void)(parser_parse_into_init(module, arena));
    (void)((pr_ok = driver_parse_into_buf_rc(arena, module, src, ((int32_t)(src_len)), &(main_idx))));
  }
  if ((pr_ok !=0)) {
    {
      (void)((rc = runtime_report_precise_parse_failure_if_known(path, src, src_len)));
    }
    if ((rc !=0)) {
      {
        (void)(free(arena));
        (void)(free(module));
      }
      return 1;
    }
    {
      (void)(free(arena));
      (void)(free(module));
    }
    (void)(rt_xe_diag(path, 4, 9, 5));
    return 1;
  }
  {
    (void)(parser_parse_into_set_main_index(module, main_idx));
    (void)((rc = driver_get_module_num_funcs(module)));
  }
  if ((rc <=0)) {
    {
      (void)((fail_tok = driver_parser_diag_fail_tok_kind(src, src_len)));
    }
    if ((fail_tok ==130)) {
      {
        (void)(free(arena));
        (void)(free(module));
      }
      (void)(rt_xe_diag(path, 4, 9, 12));
      return 1;
    }
  }
  {
    (void)(driver_x_emit_work_p_set(wp_arena(), arena));
    (void)(driver_x_emit_work_p_set(wp_module(), module));
    (void)(driver_x_emit_work_z_set(wz_asz(), asz));
    (void)(driver_x_emit_work_z_set(wz_msz(), msz));
    (void)(driver_x_emit_work_i_set(wi_main(), main_idx));
    (void)((rc = parser_get_module_num_imports(module)));
    (void)(driver_x_emit_work_i_set(wi_nimp(), rc));
  }
  return 0;
}
int32_t rt_xe_step_load_deps(void) {
  uint8_t * path = ((uint8_t *)(0));
  uint8_t * module = ((uint8_t *)(0));
  uint8_t * entry = ((uint8_t *)(0));
  uint8_t * lib = ((uint8_t *)(0));
  int32_t n_lib = 0;
  int32_t n_imp = 0;
  int32_t asm_d = 0;
  uint8_t * ds = ((uint8_t *)(0));
  uint8_t * dp = ((uint8_t *)(0));
  uint8_t * dl = ((uint8_t *)(0));
  int32_t n_deps = 0;
  uint8_t * cpaths = ((uint8_t *)(0));
  int32_t n_cl = 0;
  size_t asz = 0;
  size_t msz = 0;
  uint8_t * da = ((uint8_t *)(0));
  uint8_t * dm = ((uint8_t *)(0));
  int32_t i = 0;
  uint8_t * p = ((uint8_t *)(0));
  int32_t rc = 0;
  {
    (void)((path = driver_x_emit_work_p_get(wp_path())));
    (void)((module = driver_x_emit_work_p_get(wp_module())));
    (void)((n_imp = driver_x_emit_work_i_get(wi_nimp())));
    (void)((asz = driver_x_emit_work_z_get(wz_asz())));
    (void)((msz = driver_x_emit_work_z_get(wz_msz())));
    (void)((entry = driver_entry_dir_slot()));
    (void)(xlang_get_entry_dir(path, entry, ((size_t)(512))));
    (void)(driver_x_emit_work_p_set(wp_entry(), entry));
  }
  if ((n_imp > 0)) {
    {
      (void)(pipeline_set_entry_dir(entry));
    }
  }
  {
    (void)((lib = driver_x_emit_effective_lib_roots(&(n_lib))));
    (void)(driver_x_emit_work_p_set(wp_lib(), lib));
    (void)(driver_x_emit_work_i_set(wi_nlib(), n_lib));
    (void)((asm_d = driver_x_emit_asm_direct_import_only(path)));
    (void)(driver_x_emit_work_i_set(wi_asm(), asm_d));
    (void)((ds = driver_ptr_table_calloc(128)));
    (void)((dp = driver_ptr_table_calloc(128)));
    (void)((dl = driver_size_table_calloc(128)));
  }
  if ((ds ==((uint8_t *)(0)))) {
    return 1;
  }
  if ((dp ==((uint8_t *)(0)))) {
    {
      (void)(driver_ptr_table_free(ds));
    }
    return 1;
  }
  if ((dl ==((uint8_t *)(0)))) {
    {
      (void)(driver_ptr_table_free(ds));
      (void)(driver_ptr_table_free(dp));
    }
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_dsrc(), ds));
    (void)(driver_x_emit_work_p_set(wp_dpath(), dp));
    (void)(driver_x_emit_work_p_set(wp_dlens(), dl));
  }
  (void)((n_deps = 0));
  if ((n_imp > 0)) {
    if ((n_imp <=32)) {
      if ((asm_d !=0)) {
        {
          (void)((rc = xlang_load_direct_imports_for_asm_layout(module, lib, n_lib, entry, ((uint8_t *)(0)), 0, ds, dl, dp, &(n_deps))));
        }
        if ((rc !=0)) {
          return 1;
        }
      } else {
        {
          (void)((cpaths = driver_ptr_table_calloc(128)));
        }
        if ((cpaths ==((uint8_t *)(0)))) {
          return 1;
        }
        (void)((n_cl = 0));
        {
          (void)((rc = xlang_collect_dep_paths_transitive(module, asz, msz, lib, n_lib, entry, ((uint8_t *)(0)), 0, cpaths, &(n_cl))));
        }
        if ((rc !=0)) {
          {
            (void)(driver_ptr_table_free(cpaths));
          }
          return 1;
        }
        {
          (void)((rc = xlang_merge_direct_then_transitive_dep_paths(module, n_imp, cpaths, n_cl, dp, &(n_deps))));
          (void)(driver_ptr_table_free(cpaths));
        }
        if ((rc !=0)) {
          return 1;
        }
      }
    }
  }
  {
    (void)(driver_x_emit_work_i_set(wi_ndeps(), n_deps));
    (void)(driver_typeck_ndep_set(0));
    (void)((da = driver_ptr_table_calloc(32)));
    (void)((dm = driver_ptr_table_calloc(32)));
  }
  if ((da ==((uint8_t *)(0)))) {
    return 1;
  }
  if ((dm ==((uint8_t *)(0)))) {
    {
      (void)(driver_ptr_table_free(da));
    }
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_dar(), da));
    (void)(driver_x_emit_work_p_set(wp_dmod(), dm));
  }
  (void)((i = 0));
  while ((i < n_deps)) {
    {
      (void)((p = malloc(asz)));
      (void)(driver_ptr_table_set(da, i, p));
      (void)((p = malloc(msz)));
      (void)(driver_ptr_table_set(dm, i, p));
    }
    {
      if ((driver_ptr_table_get(da, i) ==((uint8_t *)(0)))) {
        (void)((rc = 1));
      } else {
        if ((driver_ptr_table_get(dm, i) ==((uint8_t *)(0)))) {
          (void)((rc = 1));
        } else {
          (void)((rc = 0));
        }
      }
    }
    if ((rc !=0)) {
      (void)(rt_xe_diag(((uint8_t *)(0)), 3, 5, 6));
      return 1;
    }
    {
      (void)(memset(driver_ptr_table_get(da, i), 0, asz));
      (void)(memset(driver_ptr_table_get(dm, i), 0, msz));
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t rt_xe_step_prerun(void) {
  uint8_t * path = ((uint8_t *)(0));
  uint8_t * entry = ((uint8_t *)(0));
  uint8_t * lib = ((uint8_t *)(0));
  int32_t n_lib = 0;
  int32_t n_deps = 0;
  int32_t asm_d = 0;
  uint8_t * da = ((uint8_t *)(0));
  uint8_t * dm = ((uint8_t *)(0));
  uint8_t * ds = ((uint8_t *)(0));
  uint8_t * dp = ((uint8_t *)(0));
  uint8_t * dl = ((uint8_t *)(0));
  uint8_t * out_buf = ((uint8_t *)(0));
  uint8_t * pctx = ((uint8_t *)(0));
  uint8_t * one = ((uint8_t *)(0));
  uint8_t * dep_out = ((uint8_t *)(0));
  uint8_t * dep_src = ((uint8_t *)(0));
  size_t dep_len = 0;
  uint8_t * resolved = ((uint8_t *)(0));
  uint8_t * snap = ((uint8_t *)(0));
  uint8_t * dfile = ((uint8_t *)(0));
  int32_t j = 0;
  uint8_t * p = ((uint8_t *)(0));
  int32_t rc = 0;
  int32_t ec = 0;
  {
    (void)((path = driver_x_emit_work_p_get(wp_path())));
    (void)((entry = driver_x_emit_work_p_get(wp_entry())));
    (void)((lib = driver_x_emit_work_p_get(wp_lib())));
    (void)((n_lib = driver_x_emit_work_i_get(wi_nlib())));
    (void)((n_deps = driver_x_emit_work_i_get(wi_ndeps())));
    (void)((asm_d = driver_x_emit_work_i_get(wi_asm())));
    (void)((da = driver_x_emit_work_p_get(wp_dar())));
    (void)((dm = driver_x_emit_work_p_get(wp_dmod())));
    (void)((ds = driver_x_emit_work_p_get(wp_dsrc())));
    (void)((dp = driver_x_emit_work_p_get(wp_dpath())));
    (void)((dl = driver_x_emit_work_p_get(wp_dlens())));
    (void)((out_buf = driver_codegen_outbuf_calloc()));
    (void)((pctx = driver_pipeline_dep_ctx_calloc()));
  }
  if ((out_buf ==((uint8_t *)(0)))) {
    (void)(rt_xe_diag(((uint8_t *)(0)), 3, 6, 7));
    return 1;
  }
  if ((pctx ==((uint8_t *)(0)))) {
    {
      (void)(driver_codegen_outbuf_free(out_buf));
    }
    (void)(rt_xe_diag(((uint8_t *)(0)), 3, 6, 7));
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_out(), out_buf));
    (void)(driver_x_emit_work_p_set(wp_pctx(), pctx));
    (void)(xlang_pipeline_fill_ctx_path_buffers(pctx, entry, lib, n_lib));
    /* 7.4.4 v3: opt-in -lib-name entry prefix (slot in rt_emit_state). */
    {
      uint8_t ln_buf[64] = { 0 };
      int32_t ln_len = xlang_driver_x_emit_lib_name_into((&((ln_buf)[0])), 64);
      if ((ln_len >0)) {
        (void)(xlang_pipeline_pctx_set_entry_lib_prefix(pctx, (&((ln_buf)[0])), ln_len));
      }
    }
  }
  if ((asm_d !=0)) {
    {
      (void)(xlang_pipeline_pctx_seed_dep_import_paths_only(pctx, dp, n_deps));
    }
  } else {
    {
      (void)(xlang_pipeline_pctx_seed_dep_slots(pctx, dm, da, dp, n_deps));
    }
  }
  {
    (void)(driver_pipeline_dep_ctx_set_use_asm(pctx, 0));
    (void)(driver_dep_seeded_clear_all());
  }
  (void)((j = (n_deps - 1)));
  while ((j >=0)) {
    {
      (void)((one = driver_pipeline_dep_ctx_calloc()));
      (void)((dep_out = driver_codegen_outbuf_calloc()));
    }
    if ((one ==((uint8_t *)(0)))) {
      {
        (void)(driver_codegen_outbuf_free(dep_out));
      }
      (void)(rt_xe_diag(((uint8_t *)(0)), 3, 6, 7));
      return 1;
    }
    if ((dep_out ==((uint8_t *)(0)))) {
      {
        (void)(pipeline_dep_ctx_heap_destroy(one));
      }
      (void)(rt_xe_diag(((uint8_t *)(0)), 3, 6, 7));
      return 1;
    }
    {
      (void)((p = xlang_dep_prerun_entry_dir(entry, lib, n_lib)));
      (void)(xlang_pipeline_fill_ctx_path_buffers(one, p, lib, n_lib));
      (void)((resolved = driver_path_max_slot()));
      (void)(((resolved)[0] = 0));
    }
    if ((asm_d !=0)) {
      {
        (void)((dep_src = driver_ptr_table_get(ds, j)));
        (void)((dep_len = driver_size_table_get(dl, j)));
      }
    } else {
      {
        (void)((p = driver_ptr_table_get(dp, j)));
        (void)(xlang_resolve_import_file_path_multi(lib, n_lib, entry, p, resolved, ((size_t)(4096))));
        (void)((dep_src = runtime_read_file_malloc(resolved, &(dep_len))));
      }
      if ((dep_src ==((uint8_t *)(0)))) {
        {
          (void)(pipeline_diag_import_open_fail_once(p, resolved));
          (void)(pipeline_dep_ctx_heap_destroy(one));
          (void)(driver_codegen_outbuf_free(dep_out));
        }
        return 1;
      }
      {
        (void)((p = dep_src));
        (void)((dep_src = xlang_preprocess(p, dep_len, ((uint8_t *)(0)), 0, &(dep_len))));
        (void)(free(p));
      }
      if ((dep_src ==((uint8_t *)(0)))) {
        {
          (void)(pipeline_dep_ctx_heap_destroy(one));
          (void)(driver_codegen_outbuf_free(dep_out));
        }
        (void)(rt_xe_diag(resolved, 2, 2, 2));
        return 1;
      }
    }
    {
      (void)(xlang_pipeline_one_ctx_for_dep_prerun(one, j, dm, da, dp, n_deps, dep_src, dep_len));
      (void)((p = driver_ptr_table_get(dp, j)));
      (void)(driver_set_current_dep_path_for_codegen(p));
      (void)((snap = driver_diag_snapshot_alloc()));
    }
    (void)((dfile = p));
    if ((asm_d ==0)) {
      (void)((dfile = resolved));
    }
    {
      (void)(driver_diag_push_file(snap, dfile, dep_src, dep_len));
      (void)((rc = driver_x_emit_asm_dep_parse_skip_typeck_ok(path, p)));
    }
    if ((rc !=0)) {
      {
        (void)((ec = xlang_pipeline_dep_prerun_parse_skip_typeck(driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j), dep_src, dep_len, dep_out, one)));
      }
    } else {
      {
        (void)((rc = driver_x_emit_asm_dep_parse_only_ok(path, p)));
      }
      if ((asm_d !=0)) {
        (void)((rc = 1));
      }
      if ((rc !=0)) {
        {
          (void)((ec = xlang_pipeline_dep_prerun_parse_only(driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j), dep_src, dep_len)));
        }
      } else {
        {
          (void)((ec = xlang_pipeline_dep_prerun_typeck_only(driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j), dep_src, dep_len, dep_out, one)));
        }
      }
    }
    {
      (void)(driver_diag_restore(snap));
      (void)(driver_diag_snapshot_free(snap));
      (void)(driver_set_current_dep_path_for_codegen(((uint8_t *)(0))));
      (void)(pipeline_dep_ctx_heap_destroy(one));
      (void)(driver_codegen_outbuf_free(dep_out));
    }
    if ((asm_d ==0)) {
      {
        (void)(free(dep_src));
      }
    }
    if ((ec !=0)) {
      (void)(rt_xe_diag(dfile, 3, 8, 8));
      return 1;
    }
    {
      (void)(driver_dep_publish_slot(j, driver_ptr_table_get(da, j), driver_ptr_table_get(dm, j), driver_ptr_table_get(dp, j)));
    }
    (void)((j = (j - 1)));
  }
  return 0;
}
int32_t rt_xe_step_finish(void) {
  uint8_t * path = ((uint8_t *)(0));
  uint8_t * src = ((uint8_t *)(0));
  size_t src_len = 0;
  uint8_t * arena = ((uint8_t *)(0));
  uint8_t * module = ((uint8_t *)(0));
  size_t asz = 0;
  size_t msz = 0;
  int32_t n_deps = 0;
  int32_t asm_d = 0;
  uint8_t * da = ((uint8_t *)(0));
  uint8_t * dm = ((uint8_t *)(0));
  uint8_t * dp = ((uint8_t *)(0));
  uint8_t * out_buf = ((uint8_t *)(0));
  uint8_t * pctx = ((uint8_t *)(0));
  int32_t j = 0;
  int32_t ec = 0;
  int32_t out_len = 0;
  uint8_t * out_data = ((uint8_t *)(0));
  int32_t rc = 0;
  {
    (void)((path = driver_x_emit_work_p_get(wp_path())));
    (void)((src = driver_x_emit_work_p_get(wp_src())));
    (void)((src_len = driver_x_emit_work_z_get(wz_slen())));
    (void)((arena = driver_x_emit_work_p_get(wp_arena())));
    (void)((module = driver_x_emit_work_p_get(wp_module())));
    (void)((asz = driver_x_emit_work_z_get(wz_asz())));
    (void)((msz = driver_x_emit_work_z_get(wz_msz())));
    (void)((n_deps = driver_x_emit_work_i_get(wi_ndeps())));
    (void)((asm_d = driver_x_emit_work_i_get(wi_asm())));
    (void)((da = driver_x_emit_work_p_get(wp_dar())));
    (void)((dm = driver_x_emit_work_p_get(wp_dmod())));
    (void)((dp = driver_x_emit_work_p_get(wp_dpath())));
    (void)((out_buf = driver_x_emit_work_p_get(wp_out())));
    (void)((pctx = driver_x_emit_work_p_get(wp_pctx())));
  }
  if ((asm_d !=0)) {
    {
      (void)(driver_typeck_ndep_set(0));
      (void)(pipeline_set_dep_slots(da, dm));
      (void)(driver_dep_seed_slots(((uint8_t *)(0)), ((uint8_t *)(0)), 0));
      (void)(codegen_set_dep_slots_for_x_pipeline(((uint8_t *)(0)), ((uint8_t *)(0)), 0));
    }
  } else {
    {
      (void)(driver_typeck_ndep_set(n_deps));
    }
    (void)((j = 0));
    while ((j < n_deps)) {
      {
        (void)(driver_typeck_dep_ptrs_set(j, driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j)));
      }
      (void)((j = (j + 1)));
    }
    {
      (void)(pipeline_set_dep_slots(da, dm));
      (void)(driver_dep_seed_slots(da, dm, n_deps));
      (void)(codegen_set_dep_slots_for_x_pipeline(dm, dp, n_deps));
      (void)(pipeline_set_dep_slots(da, dm));
    }
  }
  {
    (void)(memset(arena, 0, asz));
    (void)(memset(module, 0, msz));
    (void)((ec = xlang_pipeline_run_x_pipeline_large_stack(module, arena, src, src_len, out_buf, pctx)));
    (void)((out_len = driver_codegen_outbuf_len(out_buf)));
    (void)((out_data = driver_codegen_outbuf_data(out_buf)));
  }
  if ((ec ==0)) {
    if ((out_len > 0)) {
      {
        (void)(driver_x_emit_fwrite_stdout(out_data, out_len));
      }
      return 0;
    }
    {
      (void)((rc = driver_get_module_num_funcs(module)));
    }
    if ((rc <=0)) {
      {
        (void)((rc = runtime_report_precise_parse_failure_if_known(path, src, src_len)));
      }
      if ((rc ==0)) {
        (void)(rt_xe_diag(path, 4, 9, 10));
      }
      return 1;
    }
    (void)(rt_xe_diag(path, 5, 10, 11));
    return 1;
  }
  (void)(rt_xe_diag(path, 3, 3, 9));
  return 1;
}
int32_t driver_run_x_emit_c(void) {
  uint8_t * path = ((uint8_t *)(0));
  int32_t want = 0;
  uint8_t * k = ((uint8_t *)(0));
  uint8_t * c = ((uint8_t *)(0));
  uint8_t * m = ((uint8_t *)(0));
  int32_t rc = 0;
  int32_t old_legacy = 0;
  {
    (void)((old_legacy = typeck_set_allow_legacy_extern_calls(1)));
    (void)(driver_x_emit_work_reset());
    (void)((path = driver_x_emit_take_c_path()));
  }
  if ((path ==((uint8_t *)(0)))) {
    {
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_path(), path));
    (void)(driver_x_emit_stdout_set_unbuffered());
    (void)((want = driver_x_emit_take_want_extern()));
  }
  if ((want !=0)) {
    {
      (void)((rc = driver_x_emit_try_extern_via_cparser(path)));
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return rc;
  }
  {
    (void)((k = malloc(((size_t)(32)))));
    (void)((c = malloc(((size_t)(16)))));
    (void)((m = malloc(((size_t)(64)))));
  }
  if ((k ==((uint8_t *)(0)))) {
    {
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  if ((c ==((uint8_t *)(0)))) {
    {
      (void)(free(k));
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  if ((m ==((uint8_t *)(0)))) {
    {
      (void)(free(k));
      (void)(free(c));
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)(driver_x_emit_work_p_set(wp_kind(), k));
    (void)(driver_x_emit_work_p_set(wp_code(), c));
    (void)(driver_x_emit_work_p_set(wp_msg(), m));
  }
  {
    (void)((rc = rt_xe_step_read_pp()));
  }
  if ((rc !=0)) {
    {
      (void)(driver_x_emit_work_cleanup());
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)((rc = rt_xe_step_parse()));
  }
  if ((rc !=0)) {
    {
      (void)(driver_x_emit_work_cleanup());
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)((rc = rt_xe_step_load_deps()));
  }
  if ((rc !=0)) {
    {
      (void)(driver_x_emit_work_cleanup());
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)((rc = rt_xe_step_prerun()));
  }
  if ((rc !=0)) {
    {
      (void)(driver_x_emit_work_cleanup());
      (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
    }
    return 1;
  }
  {
    (void)((rc = rt_xe_step_finish()));
    (void)(driver_x_emit_work_cleanup());
    (void)(typeck_set_allow_legacy_extern_calls(old_legacy));
  }
  return rc;
}
