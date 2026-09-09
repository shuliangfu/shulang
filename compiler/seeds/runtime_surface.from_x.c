/* seeds/runtime_surface.from_x.c
 * G-02f runtime R2 mixed surface - isomorphic with src/runtime.x
 * Product: multi-slice layer seeds (wave321 monofile retired; was runtime.from_x.c rest)
 * Prove: full.x vs this surface -> nm IDENTICAL (101 symbols)
 * Mode: mixed - 30 DIRECT compute + 71 thin+rest forwards to _impl
 * Cap residual: 86 _impl bridges + 7 helper externs (link_abi_getenv,
 *   diag_json_enabled, xlang_output_want_exe, driver_argv_at,
 *   main_run_compiler_c, driver_run_fmt, driver_run_compiler_check).
 * doc_anchor: none (src/runtime.x has no doc_anchor).
 * Logic: 101 functions = 30 DIRECT compute (drv_eq_*, content_has_*,
 *   driver_argv0_basename_is, driver_x_emit_asm_*, xlang_smoke_diag_enabled,
 *   driver_asm_output_want_exe, drv_target_has_arm, driver_argv_has_emit_c_flag,
 *   driver_lib_root_ptr_usable, drv_path_ends_x, run_compiler_c,
 *   runtime_run_fmt_c, runtime_run_compiler_check_c,
 *   driver_run_x_emit_c_set_emit_extern, driver_run_x_emit_c_set_n_lib_roots)
 *   + 71 thin+rest forwards to _impl (driver_run_x_emit_c_set_path_impl,
 *   driver_fs_open_read_path_impl, driver_run_asm_backend_c_impl,
 *   driver_compile_state_free_c_impl, cfg_sync_compile_target_from_state_c_impl,
 *   main_entry_impl, runtime_diag_errno_impl, dce_is_func_used_impl,
 *   runtime_prepare_dce_ctx_impl, etc.).
 * Regen: xlang_asm -E src/runtime.x | filter DBG + polish prologue
 */
#include <stdint.h>
#include <stddef.h>
/* Forward declarations for all 101 surface functions (nm IDENTICAL targets). */
extern int32_t driver_run_x_emit_c_set_path(uint8_t * path, int32_t path_len);
extern int32_t driver_run_x_emit_c_set_lib(int32_t i, uint8_t * buf, int32_t len);
extern int32_t driver_fs_open_read_path(uint8_t * path, int32_t path_len);
extern int32_t driver_run_asm_backend_c(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, int32_t argc, uint8_t * argv);
extern int32_t driver_run_emit_c_path_c(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, uint8_t * opt_level, int32_t use_lto, int32_t argc, uint8_t * argv);
extern void driver_compile_state_free_c(uint8_t * state);
extern void cfg_sync_compile_target_from_state_c(uint8_t * state);
extern void driver_compile_ensure_default_lib_c(uint8_t * key);
extern void driver_compile_parse_argv_init_c(uint8_t * state);
extern void driver_compile_append_lib_root_c(uint8_t * state, uint8_t * path, int32_t len);
extern void driver_compile_argv_apply_minus_o_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_apply_minus_L_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_minus_O_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_set_use_lto_c(uint8_t * state);
extern void driver_compile_argv_set_use_freestanding_c(uint8_t * state);
extern void driver_compile_argv_set_legacy_f32_abi_c(void);
extern void driver_compile_argv_set_sanitize_address_c(void);
extern void driver_compile_argv_apply_backend_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_target_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_apply_target_cpu_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_set_print_target_cpu_c(uint8_t * state);
extern int32_t driver_print_target_cpu_features_c(int32_t features);
extern void driver_compile_resolve_target_cpu_c(uint8_t * state);
extern int32_t driver_run_compiler_full(int32_t argc, uint8_t * argv);
extern int32_t driver_run_test(int32_t argc, uint8_t * argv);
extern int32_t driver_fmt_report_no_files(void);
extern int32_t run_compiler_x_path(int32_t argc, uint8_t * argv);
extern int32_t driver_want_asm_emit_to_file(int32_t argc, uint8_t * argv);
extern int32_t driver_exec_compiled(int32_t argc, uint8_t * argv_opaque);
extern int32_t driver_build_build_x(void);
extern int32_t driver_fs_open_write(uint8_t * path, int32_t path_len);
extern int32_t driver_source_has_generic_syntax(uint8_t * path, int32_t path_len);
extern int32_t driver_source_has_compound_assign_syntax(uint8_t * path, int32_t path_len);
extern int32_t driver_run_asm_backend(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_roots_arr, int32_t n_lib_roots, uint8_t * target, int32_t argc, uint8_t * argv);
extern void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t * argv_opaque, uint8_t * state);
extern void driver_compile_argv_copy_path_c(uint8_t * state, uint8_t * arg_buf, int32_t plen);
extern int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t * argv_opaque);
extern void driver_print_usage_c(void);
extern int32_t driver_argv_parse_x_emit_c(int32_t argc, uint8_t * argv);
extern int32_t driver_run_x_emit_c(void);
extern int32_t driver_fmt_one_file(uint8_t * path, int32_t path_len);
extern int32_t main_entry(int32_t argc, uint8_t * argv);
extern void driver_unlink_failed_output(uint8_t * out_path);
extern void runtime_diag_cli_usage_note(uint8_t * argv0);
extern void runtime_diag_errno(uint8_t * file, uint8_t * kind, uint8_t * op);
extern void runtime_diag_errno_path(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * path);
extern void runtime_diag_errno_path_pair(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * from_path, uint8_t * to_path);
extern int32_t runtime_try_handle_explain_cli(int32_t argc, uint8_t * argv);
extern void driver_emit_legacy_smoke_summary_stdout(uint8_t * main_name, int32_t main_final_lit, int32_t has_main_body);
extern uint8_t * runtime_diag_code_for_kind(uint8_t * kind);
extern int32_t driver_deps_are_std_core_closure_only(uint8_t * dep_paths, int32_t n_deps);
extern int32_t driver_c_mod_imports_are_core_only(uint8_t * mod);
extern void driver_lib_root_default(uint8_t * root_buf);
extern int32_t runtime_test_status_to_rc(uint8_t * script, int32_t st);
extern uint8_t * xlang_get_tmp_prefix(void);
extern int32_t dce_is_func_used(uint8_t * ctx, uint8_t * mod, uint8_t * func);
extern int32_t dce_is_mono_used(uint8_t * ctx, uint8_t * mod, int32_t k);
extern int32_t dce_is_type_used(uint8_t * ctx, uint8_t * mod, uint8_t * type_name);
extern int32_t runtime_report_precise_parse_failure_if_known(uint8_t * input_path, uint8_t * src, int64_t src_len);
extern int32_t runtime_run_test_c(int32_t argc, uint8_t * argv);
extern int32_t driver_lib_roots_from_key(uint8_t * lib_key, uint8_t * out_arr, uint8_t * bufs);
extern void runtime_prepare_dce_ctx(uint8_t * mod, uint8_t * all_dep_mods, int32_t n_all, uint8_t * used_funcs, int32_t * n_used, uint8_t * used_mono, uint8_t * used_type_names, int32_t * n_used_types, uint8_t * wpo_reach, uint8_t * dce, int32_t * dce_ready);
extern int32_t driver_run_x_emit_c_from_compile_state(uint8_t * state, int32_t argc, uint8_t * argv);
extern int32_t write_fs_path_map_error_abi_inline(uint8_t * cf);
extern void codegen_emit_include_pipeline_glue_c(uint8_t * out, uint8_t * argv0);
extern void runtime_pipeline_elf_ctx_diag_note(uint8_t * ctx_bytes);
extern int32_t driver_compile_parse_argv_step_c(int32_t argc, uint8_t * argv, uint8_t * state, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern int32_t write_io_net_abi_inline(uint8_t * cf);
extern int32_t driver_run_compiler_parsed(uint8_t * p, int32_t argc, uint8_t * argv);
extern int32_t drv_eq_minus_o(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_L(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_O(uint8_t * buf, int32_t len);
extern int32_t drv_eq_flto(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_freestanding(uint8_t * buf, int32_t len);
extern int32_t drv_eq_legacy_f32_abi(uint8_t * buf, int32_t len);
extern int32_t drv_eq_fsanitize_address(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_backend(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target_cpu(uint8_t * buf, int32_t len);
extern int32_t drv_eq_print_target_cpu(uint8_t * buf, int32_t len);
extern int32_t drv_eq_asm_word(uint8_t * buf, int32_t len);
extern int32_t drv_eq_c_word(uint8_t * buf, int32_t len);
extern int32_t drv_path_ends_x(uint8_t * buf, int32_t len);
extern int32_t driver_lib_root_ptr_usable(uint8_t * p);
extern int32_t xlang_smoke_diag_enabled(void);
extern int32_t driver_asm_output_want_exe(uint8_t * path);
extern int32_t drv_target_has_arm(uint8_t * buf, int32_t len);
extern int32_t driver_argv_has_emit_c_flag(int32_t argc, uint8_t * argv);
extern int32_t driver_argv0_basename_is(uint8_t * argv0, uint8_t * base);
extern int32_t content_has_generic_syntax(uint8_t * content, int64_t n);
extern int32_t content_has_compound_assign_syntax(uint8_t * content, int64_t n);
extern int32_t driver_run_x_emit_c_set_emit_extern(int32_t v);
extern int32_t driver_run_x_emit_c_set_n_lib_roots(int32_t n);
extern int32_t run_compiler_c(int32_t argc, uint8_t * argv);
extern int32_t runtime_run_fmt_c(int32_t argc, uint8_t * argv);
extern int32_t runtime_run_compiler_check_c(int32_t argc, uint8_t * argv);
extern int32_t driver_x_emit_asm_direct_import_only(uint8_t * input_path);
extern int32_t driver_x_emit_asm_dep_parse_skip_typeck_ok(uint8_t * input_path, uint8_t * dep_path);
extern int32_t driver_x_emit_asm_dep_parse_only_ok(uint8_t * input_path, uint8_t * dep_path);
/* Cap residual: 86 _impl bridges (71 called by thin+rest + 15 declared for DIRECT but unused). */
extern int32_t driver_run_x_emit_c_set_path_impl(uint8_t * path, int32_t path_len);
extern int32_t driver_run_x_emit_c_set_lib_impl(int32_t i, uint8_t * buf, int32_t len);
extern int32_t driver_fs_open_read_path_impl(uint8_t * path, int32_t path_len);
extern int32_t driver_run_asm_backend_c_impl(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, int32_t argc, uint8_t * argv);
extern int32_t driver_run_emit_c_path_c_impl(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, uint8_t * opt_level, int32_t use_lto, int32_t argc, uint8_t * argv);
extern void driver_compile_state_free_c_impl(uint8_t * state);
extern void cfg_sync_compile_target_from_state_c_impl(uint8_t * state);
extern void driver_compile_ensure_default_lib_c_impl(uint8_t * key);
extern void driver_compile_parse_argv_init_c_impl(uint8_t * state);
extern void driver_compile_append_lib_root_c_impl(uint8_t * state, uint8_t * path, int32_t len);
extern void driver_compile_argv_apply_minus_o_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_apply_minus_L_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_minus_O_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_set_use_lto_c_impl(uint8_t * state);
extern void driver_compile_argv_set_use_freestanding_c_impl(uint8_t * state);
extern void driver_compile_argv_set_legacy_f32_abi_c_impl(void);
extern void driver_compile_argv_set_sanitize_address_c_impl(void);
extern void driver_compile_argv_apply_backend_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_target_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_apply_target_cpu_next_c_impl(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i);
extern void driver_compile_argv_set_print_target_cpu_c_impl(uint8_t * state);
extern int32_t driver_print_target_cpu_features_c_impl(int32_t features);
extern void driver_compile_resolve_target_cpu_c_impl(uint8_t * state);
extern int32_t driver_run_compiler_full_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_run_test_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_fmt_report_no_files_impl(void);
extern int32_t run_compiler_x_path_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_want_asm_emit_to_file_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_exec_compiled_impl(int32_t argc, uint8_t * argv_opaque);
extern int32_t driver_build_build_x_impl(void);
extern int32_t driver_fs_open_write_impl(uint8_t * path, int32_t path_len);
extern int32_t driver_source_has_generic_syntax_impl(uint8_t * path, int32_t path_len);
extern int32_t driver_source_has_compound_assign_syntax_impl(uint8_t * path, int32_t path_len);
extern int32_t driver_run_asm_backend_impl(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_roots_arr, int32_t n_lib_roots, uint8_t * target, int32_t argc, uint8_t * argv);
extern void driver_compile_parse_argv_scan_c_impl(int32_t argc, uint8_t * argv_opaque, uint8_t * state);
extern void driver_compile_argv_copy_path_c_impl(uint8_t * state, uint8_t * arg_buf, int32_t plen);
extern int32_t driver_compile_argv_is_help_c_impl(int32_t argc, uint8_t * argv_opaque);
extern void driver_print_usage_c_impl(void);
extern int32_t driver_argv_parse_x_emit_c_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_run_x_emit_c_impl(void);
extern int32_t driver_fmt_one_file_impl(uint8_t * path, int32_t path_len);
extern int32_t main_entry_impl(int32_t argc, uint8_t * argv);
extern void driver_unlink_failed_output_impl(uint8_t * out_path);
extern void runtime_diag_cli_usage_note_impl(uint8_t * argv0);
extern void runtime_diag_errno_impl(uint8_t * file, uint8_t * kind, uint8_t * op);
extern void runtime_diag_errno_path_impl(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * path);
extern void runtime_diag_errno_path_pair_impl(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * from_path, uint8_t * to_path);
extern int32_t runtime_try_handle_explain_cli_impl(int32_t argc, uint8_t * argv);
extern void driver_emit_legacy_smoke_summary_stdout_impl(uint8_t * main_name, int32_t main_final_lit, int32_t has_main_body);
extern uint8_t * runtime_diag_code_for_kind_impl(uint8_t * kind);
extern int32_t driver_lib_root_ptr_usable_impl(uint8_t * p);
extern int32_t drv_eq_minus_o_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_L_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_O_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_flto_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_freestanding_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_legacy_f32_abi_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_fsanitize_address_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_backend_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target_cpu_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_print_target_cpu_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_asm_word_impl(uint8_t * buf, int32_t len);
extern int32_t drv_eq_c_word_impl(uint8_t * buf, int32_t len);
extern int32_t drv_path_ends_x_impl(uint8_t * buf, int32_t len);
extern int32_t driver_deps_are_std_core_closure_only_impl(uint8_t * dep_paths, int32_t n_deps);
extern int32_t driver_c_mod_imports_are_core_only_impl(uint8_t * mod);
extern void driver_lib_root_default_impl(uint8_t * root_buf);
extern int32_t runtime_test_status_to_rc_impl(uint8_t * script, int32_t st);
extern uint8_t * xlang_get_tmp_prefix_impl(void);
extern int32_t dce_is_func_used_impl(uint8_t * ctx, uint8_t * mod, uint8_t * func);
extern int32_t dce_is_mono_used_impl(uint8_t * ctx, uint8_t * mod, int32_t k);
extern int32_t dce_is_type_used_impl(uint8_t * ctx, uint8_t * mod, uint8_t * type_name);
extern int32_t runtime_report_precise_parse_failure_if_known_impl(uint8_t * input_path, uint8_t * src, int64_t src_len);
extern int32_t runtime_run_test_c_impl(int32_t argc, uint8_t * argv);
extern int32_t driver_lib_roots_from_key_impl(uint8_t * lib_key, uint8_t * out_arr, uint8_t * bufs);
extern void runtime_prepare_dce_ctx_impl(uint8_t * mod, uint8_t * all_dep_mods, int32_t n_all, uint8_t * used_funcs, int32_t * n_used, uint8_t * used_mono, uint8_t * used_type_names, int32_t * n_used_types, uint8_t * wpo_reach, uint8_t * dce, int32_t * dce_ready);
extern int32_t driver_run_x_emit_c_from_compile_state_impl(uint8_t * state, int32_t argc, uint8_t * argv);
extern int32_t write_fs_path_map_error_abi_inline_impl(uint8_t * cf);
extern void codegen_emit_include_pipeline_glue_c_impl(uint8_t * out, uint8_t * argv0);
extern void runtime_pipeline_elf_ctx_diag_note_impl(uint8_t * ctx_bytes);
extern int32_t driver_compile_parse_argv_step_c_impl(int32_t argc, uint8_t * argv, uint8_t * state, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
/* Function definitions: 30 DIRECT compute + 69 thin+rest forwards to _impl. */
int32_t driver_run_x_emit_c_set_path(uint8_t * path, int32_t path_len) {
  return driver_run_x_emit_c_set_path_impl(path, path_len);
  return -1;
}
int32_t driver_run_x_emit_c_set_lib(int32_t i, uint8_t * buf, int32_t len) {
  return driver_run_x_emit_c_set_lib_impl(i, buf, len);
  return -1;
}
int32_t driver_fs_open_read_path(uint8_t * path, int32_t path_len) {
  return driver_fs_open_read_path_impl(path, path_len);
  return -1;
}
int32_t driver_run_asm_backend_c(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, int32_t argc, uint8_t * argv) {
  return driver_run_asm_backend_c_impl(input_path, out_path, lib_key, target, argc, argv);
  return -1;
}
int32_t driver_run_emit_c_path_c(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_key, uint8_t * target, uint8_t * opt_level, int32_t use_lto, int32_t argc, uint8_t * argv) {
  return driver_run_emit_c_path_c_impl(input_path, out_path, lib_key, target, opt_level, use_lto, argc, argv);
  return -1;
}
void driver_compile_state_free_c(uint8_t * state) {
  (void)(driver_compile_state_free_c_impl(state));
}
void cfg_sync_compile_target_from_state_c(uint8_t * state) {
  (void)(cfg_sync_compile_target_from_state_c_impl(state));
}
void driver_compile_ensure_default_lib_c(uint8_t * key) {
  (void)(driver_compile_ensure_default_lib_c_impl(key));
}
void driver_compile_parse_argv_init_c(uint8_t * state) {
  (void)(driver_compile_parse_argv_init_c_impl(state));
}
void driver_compile_append_lib_root_c(uint8_t * state, uint8_t * path, int32_t len) {
  (void)(driver_compile_append_lib_root_c_impl(state, path, len));
}
void driver_compile_argv_apply_minus_o_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i) {
  (void)(driver_compile_argv_apply_minus_o_next_c_impl(state, argc, argv_opaque, i));
}
void driver_compile_argv_apply_minus_L_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  (void)(driver_compile_argv_apply_minus_L_next_c_impl(state, argc, argv_opaque, i, arg_buf, arg_cap));
}
void driver_compile_argv_apply_minus_O_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i) {
  (void)(driver_compile_argv_apply_minus_O_next_c_impl(state, argc, argv_opaque, i));
}
void driver_compile_argv_set_use_lto_c(uint8_t * state) {
  (void)(driver_compile_argv_set_use_lto_c_impl(state));
}
void driver_compile_argv_set_use_freestanding_c(uint8_t * state) {
  (void)(driver_compile_argv_set_use_freestanding_c_impl(state));
}
void driver_compile_argv_set_legacy_f32_abi_c(void) {
  (void)(driver_compile_argv_set_legacy_f32_abi_c_impl());
}
void driver_compile_argv_set_sanitize_address_c(void) {
  (void)(driver_compile_argv_set_sanitize_address_c_impl());
}
void driver_compile_argv_apply_backend_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  (void)(driver_compile_argv_apply_backend_next_c_impl(state, argc, argv_opaque, i, arg_buf, arg_cap));
}
void driver_compile_argv_apply_target_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i) {
  (void)(driver_compile_argv_apply_target_next_c_impl(state, argc, argv_opaque, i));
}
void driver_compile_argv_apply_target_cpu_next_c(uint8_t * state, int32_t argc, uint8_t * argv_opaque, int32_t i) {
  (void)(driver_compile_argv_apply_target_cpu_next_c_impl(state, argc, argv_opaque, i));
}
void driver_compile_argv_set_print_target_cpu_c(uint8_t * state) {
  (void)(driver_compile_argv_set_print_target_cpu_c_impl(state));
}
int32_t driver_print_target_cpu_features_c(int32_t features) {
  return driver_print_target_cpu_features_c_impl(features);
  return -1;
}
void driver_compile_resolve_target_cpu_c(uint8_t * state) {
  (void)(driver_compile_resolve_target_cpu_c_impl(state));
}
int32_t driver_run_compiler_full(int32_t argc, uint8_t * argv) {
  return driver_run_compiler_full_impl(argc, argv);
  return -1;
}
int32_t driver_run_test(int32_t argc, uint8_t * argv) {
  return driver_run_test_impl(argc, argv);
  return -1;
}
int32_t driver_fmt_report_no_files(void) {
  return driver_fmt_report_no_files_impl();
  return -1;
}
int32_t run_compiler_x_path(int32_t argc, uint8_t * argv) {
  return run_compiler_x_path_impl(argc, argv);
  return -1;
}
int32_t driver_want_asm_emit_to_file(int32_t argc, uint8_t * argv) {
  return driver_want_asm_emit_to_file_impl(argc, argv);
  return -1;
}
int32_t driver_exec_compiled(int32_t argc, uint8_t * argv_opaque) {
  return driver_exec_compiled_impl(argc, argv_opaque);
  return -1;
}
int32_t driver_build_build_x(void) {
  return driver_build_build_x_impl();
  return -1;
}
int32_t driver_fs_open_write(uint8_t * path, int32_t path_len) {
  return driver_fs_open_write_impl(path, path_len);
  return -1;
}
int32_t driver_source_has_generic_syntax(uint8_t * path, int32_t path_len) {
  return driver_source_has_generic_syntax_impl(path, path_len);
  return -1;
}
int32_t driver_source_has_compound_assign_syntax(uint8_t * path, int32_t path_len) {
  return driver_source_has_compound_assign_syntax_impl(path, path_len);
  return -1;
}
int32_t driver_run_asm_backend(uint8_t * input_path, uint8_t * out_path, uint8_t * lib_roots_arr, int32_t n_lib_roots, uint8_t * target, int32_t argc, uint8_t * argv) {
  return driver_run_asm_backend_impl(input_path, out_path, lib_roots_arr, n_lib_roots, target, argc, argv);
  return -1;
}
void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t * argv_opaque, uint8_t * state) {
  (void)(driver_compile_parse_argv_scan_c_impl(argc, argv_opaque, state));
}
void driver_compile_argv_copy_path_c(uint8_t * state, uint8_t * arg_buf, int32_t plen) {
  (void)(driver_compile_argv_copy_path_c_impl(state, arg_buf, plen));
}
int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t * argv_opaque) {
  return driver_compile_argv_is_help_c_impl(argc, argv_opaque);
  return -1;
}
void driver_print_usage_c(void) {
  (void)(driver_print_usage_c_impl());
}
int32_t driver_argv_parse_x_emit_c(int32_t argc, uint8_t * argv) {
  return driver_argv_parse_x_emit_c_impl(argc, argv);
  return -1;
}
int32_t driver_run_x_emit_c(void) {
  return driver_run_x_emit_c_impl();
  return -1;
}
int32_t driver_fmt_one_file(uint8_t * path, int32_t path_len) {
  return driver_fmt_one_file_impl(path, path_len);
  return -1;
}
int32_t main_entry(int32_t argc, uint8_t * argv) {
  return main_entry_impl(argc, argv);
  return -1;
}
void driver_unlink_failed_output(uint8_t * out_path) {
  (void)(driver_unlink_failed_output_impl(out_path));
}
void runtime_diag_cli_usage_note(uint8_t * argv0) {
  (void)(runtime_diag_cli_usage_note_impl(argv0));
}
void runtime_diag_errno(uint8_t * file, uint8_t * kind, uint8_t * op) {
  (void)(runtime_diag_errno_impl(file, kind, op));
}
void runtime_diag_errno_path(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * path) {
  (void)(runtime_diag_errno_path_impl(file, kind, op, path));
}
void runtime_diag_errno_path_pair(uint8_t * file, uint8_t * kind, uint8_t * op, uint8_t * from_path, uint8_t * to_path) {
  (void)(runtime_diag_errno_path_pair_impl(file, kind, op, from_path, to_path));
}
int32_t runtime_try_handle_explain_cli(int32_t argc, uint8_t * argv) {
  return runtime_try_handle_explain_cli_impl(argc, argv);
  return -1;
}
void driver_emit_legacy_smoke_summary_stdout(uint8_t * main_name, int32_t main_final_lit, int32_t has_main_body) {
  (void)(driver_emit_legacy_smoke_summary_stdout_impl(main_name, main_final_lit, has_main_body));
}
uint8_t * runtime_diag_code_for_kind(uint8_t * kind) {
  return runtime_diag_code_for_kind_impl(kind);
  return ((uint8_t *)(0));
}
int32_t driver_deps_are_std_core_closure_only(uint8_t * dep_paths, int32_t n_deps) {
  return driver_deps_are_std_core_closure_only_impl(dep_paths, n_deps);
  return 0;
}
int32_t driver_c_mod_imports_are_core_only(uint8_t * mod) {
  return driver_c_mod_imports_are_core_only_impl(mod);
  return 0;
}
void driver_lib_root_default(uint8_t * root_buf) {
  (void)(driver_lib_root_default_impl(root_buf));
}
int32_t runtime_test_status_to_rc(uint8_t * script, int32_t st) {
  return runtime_test_status_to_rc_impl(script, st);
  return 0;
}
uint8_t * xlang_get_tmp_prefix(void) {
  return xlang_get_tmp_prefix_impl();
  return ((uint8_t *)(0));
}
int32_t dce_is_func_used(uint8_t * ctx, uint8_t * mod, uint8_t * func) {
  return dce_is_func_used_impl(ctx, mod, func);
  return 0;
}
int32_t dce_is_mono_used(uint8_t * ctx, uint8_t * mod, int32_t k) {
  return dce_is_mono_used_impl(ctx, mod, k);
  return 0;
}
int32_t dce_is_type_used(uint8_t * ctx, uint8_t * mod, uint8_t * type_name) {
  return dce_is_type_used_impl(ctx, mod, type_name);
  return 0;
}
int32_t runtime_report_precise_parse_failure_if_known(uint8_t * input_path, uint8_t * src, int64_t src_len) {
  return runtime_report_precise_parse_failure_if_known_impl(input_path, src, src_len);
  return 0;
}
int32_t runtime_run_test_c(int32_t argc, uint8_t * argv) {
  return runtime_run_test_c_impl(argc, argv);
  return 0;
}
int32_t driver_lib_roots_from_key(uint8_t * lib_key, uint8_t * out_arr, uint8_t * bufs) {
  return driver_lib_roots_from_key_impl(lib_key, out_arr, bufs);
  return 0;
}
/*
 * Retired mega wrappers: driver_smoke_lex_dump_{on_large_stack,thread_fn}
 * and driver_c_typeck_entry{,_thread_fn,_large_stack} forwarded to
 * never-defined *_impl. Product typeck authority is
 * pipeline_typeck_entry_module. rt_run_* leftover consume sites also
 * retired. PLATFORM: SHARED — isomorphic with src/runtime.x; do not re-add.
 */
/*
 * Retired mega wrappers: driver_c_frontend_smoke /
 * driver_check_only_c_typeck forwarded to never-defined *_impl.
 * Product typeck authority is pipeline_typeck_entry_module.
 * rt_run_* leftover consume sites also retired.
 * PLATFORM: SHARED — isomorphic with src/runtime.x; do not re-add.
 */
/*
 * Retired mega wrappers: driver_stack_esc_gate_thread_fn / large_stack
 * forwarded to never-defined *_impl. Product authority is rt_stack.x.
 * PLATFORM: SHARED — isomorphic with src/runtime.x; do not re-add.
 */
void runtime_prepare_dce_ctx(uint8_t * mod, uint8_t * all_dep_mods, int32_t n_all, uint8_t * used_funcs, int32_t * n_used, uint8_t * used_mono, uint8_t * used_type_names, int32_t * n_used_types, uint8_t * wpo_reach, uint8_t * dce, int32_t * dce_ready) {
  (void)(runtime_prepare_dce_ctx_impl(mod, all_dep_mods, n_all, used_funcs, n_used, used_mono, used_type_names, n_used_types, wpo_reach, dce, dce_ready));
}
int32_t driver_run_x_emit_c_from_compile_state(uint8_t * state, int32_t argc, uint8_t * argv) {
  return driver_run_x_emit_c_from_compile_state_impl(state, argc, argv);
  return -1;
}
/*
 * Retired mega wrapper: driver_c_frontend_smoke.
 * PLATFORM: SHARED — do not re-add.
 */
/*
 * Retired mega wrapper: driver_try_compile_via_shu_c_sibling forwarded
 * to never-defined *_impl. Product authority is rt_dispatch_thin
 * (HAS a real fork/exec body). Re-adding here would first-wins overlay
 * the spawn body.
 * PLATFORM: SHARED — do not re-add.
 */
/*
 * Retired mega wrapper: driver_smoke_lex_dump_thread_fn.
 * PLATFORM: SHARED — do not re-add.
 */
int32_t write_fs_path_map_error_abi_inline(uint8_t * cf) {
  return write_fs_path_map_error_abi_inline_impl(cf);
  return -1;
}
void codegen_emit_include_pipeline_glue_c(uint8_t * out, uint8_t * argv0) {
  (void)(codegen_emit_include_pipeline_glue_c_impl(out, argv0));
}
void runtime_pipeline_elf_ctx_diag_note(uint8_t * ctx_bytes) {
  (void)(runtime_pipeline_elf_ctx_diag_note_impl(ctx_bytes));
}
int32_t driver_compile_parse_argv_step_c(int32_t argc, uint8_t * argv, uint8_t * state, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  return driver_compile_parse_argv_step_c_impl(argc, argv, state, i, arg_buf, arg_cap);
  return (i + 1);
}
extern int32_t write_io_net_abi_inline_impl(uint8_t * cf);
extern int32_t driver_run_compiler_parsed_impl(uint8_t * p, int32_t argc, uint8_t * argv);
int32_t write_io_net_abi_inline(uint8_t * cf) {
  return write_io_net_abi_inline_impl(cf);
  return 0;
}
int32_t driver_run_compiler_parsed(uint8_t * p, int32_t argc, uint8_t * argv) {
  return driver_run_compiler_parsed_impl(p, argc, argv);
  return 0;
}
/*
 * Retired mega wrapper: driver_run_x_emit_c_extern_via_cparser forwarded
 * to never-defined *_impl. Product -E-extern authority is
 * driver_x_emit_try_extern_via_cparser (always BLD001).
 * PLATFORM: SHARED — do not re-add.
 */
/*
 * Retired mega wrapper: driver_c_typeck_entry.
 * PLATFORM: SHARED — do not re-add.
 */
int32_t drv_eq_minus_o(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] ==45) && ((buf)[1] ==111))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_L(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] ==45) && ((buf)[1] ==76))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_O(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] ==45) && ((buf)[1] ==79))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_flto(uint8_t * buf, int32_t len) {
  if ((len !=5)) {
    return 0;
  }
  if (((((((buf)[0] ==45) && ((buf)[1] ==102)) && ((buf)[2] ==108)) && ((buf)[3] ==116)) && ((buf)[4] ==111))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_freestanding(uint8_t * buf, int32_t len) {
  if ((len !=13)) {
    return 0;
  }
  if (((((((((((((((buf)[0] ==45) && ((buf)[1] ==102)) && ((buf)[2] ==114)) && ((buf)[3] ==101)) && ((buf)[4] ==101)) && ((buf)[5] ==115)) && ((buf)[6] ==116)) && ((buf)[7] ==97)) && ((buf)[8] ==110)) && ((buf)[9] ==100)) && ((buf)[10] ==105)) && ((buf)[11] ==110)) && ((buf)[12] ==103))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_legacy_f32_abi(uint8_t * buf, int32_t len) {
  if ((len !=15)) {
    return 0;
  }
  if (((((((((((((((((buf)[0] ==45) && ((buf)[1] ==108)) && ((buf)[2] ==101)) && ((buf)[3] ==103)) && ((buf)[4] ==97)) && ((buf)[5] ==99)) && ((buf)[6] ==121)) && ((buf)[7] ==45)) && ((buf)[8] ==102)) && ((buf)[9] ==51)) && ((buf)[10] ==50)) && ((buf)[11] ==45)) && ((buf)[12] ==97)) && ((buf)[13] ==98)) && ((buf)[14] ==105))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_fsanitize_address(uint8_t * buf, int32_t len) {
  if ((len !=18)) {
    return 0;
  }
  if ((((((((((((((((((((buf)[0] ==45) && ((buf)[1] ==102)) && ((buf)[2] ==115)) && ((buf)[3] ==97)) && ((buf)[4] ==110)) && ((buf)[5] ==105)) && ((buf)[6] ==116)) && ((buf)[7] ==105)) && ((buf)[8] ==122)) && ((buf)[9] ==101)) && ((buf)[10] ==61)) && ((buf)[11] ==97)) && ((buf)[12] ==100)) && ((buf)[13] ==100)) && ((buf)[14] ==114)) && ((buf)[15] ==101)) && ((buf)[16] ==115)) && ((buf)[17] ==115))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_backend(uint8_t * buf, int32_t len) {
  if ((len !=8)) {
    return 0;
  }
  if ((((((((((buf)[0] ==45) && ((buf)[1] ==98)) && ((buf)[2] ==97)) && ((buf)[3] ==99)) && ((buf)[4] ==107)) && ((buf)[5] ==101)) && ((buf)[6] ==110)) && ((buf)[7] ==100))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_target(uint8_t * buf, int32_t len) {
  if ((len != 7)) {
    return 0;
  }
  if (((((((((buf)[0] ==45) && ((buf)[1] ==116)) && ((buf)[2] ==97)) && ((buf)[3] ==114)) && ((buf)[4] ==103)) && ((buf)[5] ==101)) && ((buf)[6] ==116))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_minus_target_cpu(uint8_t * buf, int32_t len) {
  if ((len != 11)) {
    return 0;
  }
  if (((((((((((((buf)[0] ==45) && ((buf)[1] ==116)) && ((buf)[2] ==97)) && ((buf)[3] ==114)) && ((buf)[4] ==103)) && ((buf)[5] ==101)) && ((buf)[6] ==116)) && ((buf)[7] ==45)) && ((buf)[8] ==99)) && ((buf)[9] ==112)) && ((buf)[10] ==117))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_print_target_cpu(uint8_t * buf, int32_t len) {
  if ((len ==18)) {
    if ((((((((((((((((((((buf)[0] ==45) && ((buf)[1] ==45)) && ((buf)[2] ==112)) && ((buf)[3] ==114)) && ((buf)[4] ==105)) && ((buf)[5] ==110)) && ((buf)[6] ==116)) && ((buf)[7] ==45)) && ((buf)[8] ==116)) && ((buf)[9] ==97)) && ((buf)[10] ==114)) && ((buf)[11] ==103)) && ((buf)[12] ==101)) && ((buf)[13] ==116)) && ((buf)[14] ==45)) && ((buf)[15] ==99)) && ((buf)[16] ==112)) && ((buf)[17] ==117))) {
      return 1;
    }
  }
  if ((len ==17)) {
    if (((((((((((((((((((buf)[0] ==45) && ((buf)[1] ==112)) && ((buf)[2] ==114)) && ((buf)[3] ==105)) && ((buf)[4] ==110)) && ((buf)[5] ==116)) && ((buf)[6] ==45)) && ((buf)[7] ==116)) && ((buf)[8] ==97)) && ((buf)[9] ==114)) && ((buf)[10] ==103)) && ((buf)[11] ==101)) && ((buf)[12] ==116)) && ((buf)[13] ==45)) && ((buf)[14] ==99)) && ((buf)[15] ==112)) && ((buf)[16] ==117))) {
      return 1;
    }
  }
  return 0;
}
int32_t drv_eq_asm_word(uint8_t * buf, int32_t len) {
  if ((len !=3)) {
    return 0;
  }
  if (((((buf)[0] ==97) && ((buf)[1] ==115)) && ((buf)[2] ==109))) {
    return 1;
  }
  return 0;
}
int32_t drv_eq_c_word(uint8_t * buf, int32_t len) {
  if ((len !=1)) {
    return 0;
  }
  if (((buf)[0] ==99)) {
    return 1;
  }
  return 0;
}
int32_t drv_path_ends_x(uint8_t * buf, int32_t len) {
  if ((len >=2)) {
    if ((((buf)[(len - 2)] ==46) && ((buf)[(len - 1)] ==120))) {
      return 1;
    }
  }
  if ((len >=3)) {
    if (((((buf)[(len - 3)] ==46) && ((buf)[(len - 2)] ==115)) && ((buf)[(len - 1)] ==117))) {
      return 1;
    }
  }
  return 0;
}
int32_t driver_lib_root_ptr_usable(uint8_t * p) {
  if ((p ==0)) {
    return 0;
  }
  if (((p)[0] ==0)) {
    return 0;
  }
  return 1;
}
extern uint8_t * link_abi_getenv(uint8_t * name);
extern int32_t diag_json_enabled(void);
int32_t xlang_smoke_diag_enabled(void) {
  {
    int32_t j = diag_json_enabled();
    if ((j !=0)) {
      return 1;
    }
    uint8_t * e = link_abi_getenv(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x53\x4d\x4f\x4b\x45\x5f\x44\x49\x41\x47"));
    if ((e ==0)) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
  return 0;
}
extern int32_t xlang_output_want_exe(uint8_t * path);
int32_t driver_asm_output_want_exe(uint8_t * path) {
  return xlang_output_want_exe(path);
  return 0;
}
extern uint8_t * driver_argv_at(uint8_t * argv, int32_t i);
int32_t drv_target_has_arm(uint8_t * buf, int32_t len) {
  if ((buf ==0)) {
    return 0;
  }
  int32_t start = 0;
  while (((start + 5) <=len)) {
    if (((((((buf)[start] ==97) && ((buf)[(start + 1)] ==114)) && ((buf)[(start + 2)] ==109)) && ((buf)[(start + 3)] ==54)) && ((buf)[(start + 4)] ==52))) {
      return 1;
    }
    (void)((start = (start + 1)));
  }
  return 0;
}
int32_t driver_argv_has_emit_c_flag(int32_t argc, uint8_t * argv) {
  if ((argc < 2)) {
    return 0;
  }
  if ((argv ==0)) {
    return 0;
  }
  int32_t i = 1;
  while ((i < argc)) {
    {
      uint8_t * s = driver_argv_at(argv, i);
      if ((s !=0)) {
        if (((((s)[0] ==45) && ((s)[1] ==69)) && ((s)[2] ==0))) {
          return 1;
        }
        if ((((((((((((s)[0] ==45) && ((s)[1] ==69)) && ((s)[2] ==45)) && ((s)[3] ==101)) && ((s)[4] ==120)) && ((s)[5] ==116)) && ((s)[6] ==101)) && ((s)[7] ==114)) && ((s)[8] ==110)) && ((s)[9] ==0))) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t driver_argv0_basename_is(uint8_t * argv0, uint8_t * base) {
  if ((base ==0)) {
    return 0;
  }
  uint8_t * name = argv0;
  if ((argv0 !=0)) {
    int32_t i = 0;
    int32_t last = -1;
    while ((i < 4096)) {
      uint8_t c = (argv0)[i];
      if ((c ==0)) {
        break;
      }
      if ((c ==47)) {
        (void)((last = i));
      }
      if ((c ==92)) {
        (void)((last = i));
      }
      (void)((i = (i + 1)));
    }
    if ((last >=0)) {
      {
        int32_t j = 0;
        while ((j < 256)) {
          uint8_t a = (argv0)[((last + 1) + j)];
          uint8_t b = (base)[j];
          if ((a !=b)) {
            return 0;
          }
          if ((a ==0)) {
            return 1;
          }
          (void)((j = (j + 1)));
        }
      }
      return 0;
    }
  } else {
    (void)((name = ((uint8_t *)(0))));
  }
  if ((argv0 ==0)) {
    if (((base)[0] ==0)) {
      return 1;
    }
    return 0;
  }
  int32_t j = 0;
  while ((j < 256)) {
    uint8_t a = (argv0)[j];
    uint8_t b = (base)[j];
    if ((a !=b)) {
      return 0;
    }
    if ((a ==0)) {
      return 1;
    }
    (void)((j = (j + 1)));
  }
  return 0;
}
int32_t content_has_generic_syntax(uint8_t * content, int64_t n) {
  if ((content ==0)) {
    return 0;
  }
  if ((n ==0)) {
    return 0;
  }
  int32_t ni = ((int32_t)(n));
  int32_t p = 0;
  while ((p < ni)) {
    if (((content)[p] ==60)) {
      if (((p + 1) >=ni)) {
        break;
      }
      if ((p > 0)) {
        if (((content)[(p - 1)] ==93)) {
          (void)((p = (p + 1)));
          continue;
        }
      }
      if (((content)[(p + 1)] ==84)) {
        if (((p + 2) >=ni)) {
          return 1;
        }
        if (((content)[(p + 2)] ==62)) {
          return 1;
        }
        if (((content)[(p + 2)] ==44)) {
          return 1;
        }
      }
      if (((p + 4) <=ni)) {
        if (((((content)[(p + 1)] ==105) && ((content)[(p + 2)] ==56)) && ((content)[(p + 3)] ==62))) {
          return 1;
        }
        if (((((content)[(p + 1)] ==117) && ((content)[(p + 2)] ==56)) && ((content)[(p + 3)] ==62))) {
          return 1;
        }
      }
      if (((p + 5) <=ni)) {
        if ((((((content)[(p + 1)] ==105) && ((content)[(p + 2)] ==49)) && ((content)[(p + 3)] ==54)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==105) && ((content)[(p + 2)] ==51)) && ((content)[(p + 3)] ==50)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==105) && ((content)[(p + 2)] ==54)) && ((content)[(p + 3)] ==52)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==117) && ((content)[(p + 2)] ==49)) && ((content)[(p + 3)] ==54)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==117) && ((content)[(p + 2)] ==51)) && ((content)[(p + 3)] ==50)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==117) && ((content)[(p + 2)] ==54)) && ((content)[(p + 3)] ==52)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==102) && ((content)[(p + 2)] ==51)) && ((content)[(p + 3)] ==50)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
        if ((((((content)[(p + 1)] ==102) && ((content)[(p + 2)] ==54)) && ((content)[(p + 3)] ==52)) && ((content)[(p + 4)] ==62))) {
          return 1;
        }
      }
      if (((p + 6) <=ni)) {
        if (((((((content)[(p + 1)] ==98) && ((content)[(p + 2)] ==111)) && ((content)[(p + 3)] ==111)) && ((content)[(p + 4)] ==108)) && ((content)[(p + 5)] ==62))) {
          return 1;
        }
      }
    }
    (void)((p = (p + 1)));
  }
  if ((ni >=6)) {
    int32_t i = 0;
    while ((i <=(ni - 6))) {
      if ((((((((content)[i] ==116) && ((content)[(i + 1)] ==114)) && ((content)[(i + 2)] ==97)) && ((content)[(i + 3)] ==105)) && ((content)[(i + 4)] ==116)) && ((content)[(i + 5)] ==32))) {
        return 1;
      }
      if ((((((((content)[i] ==32) && ((content)[(i + 1)] ==105)) && ((content)[(i + 2)] ==109)) && ((content)[(i + 3)] ==112)) && ((content)[(i + 4)] ==108)) && ((content)[(i + 5)] ==32))) {
        return 1;
      }
      (void)((i = (i + 1)));
    }
  }
  return 0;
}
int32_t content_has_compound_assign_syntax(uint8_t * content, int64_t n) {
  if ((content ==0)) {
    return 0;
  }
  if ((n < 3)) {
    return 0;
  }
  int32_t ni = ((int32_t)(n));
  int32_t pos = 0;
  while ((pos < ni)) {
    if (((pos + 1) < ni)) {
      if ((((content)[pos] ==47) && ((content)[(pos + 1)] ==47))) {
        (void)((pos = (pos + 2)));
        while ((pos < ni)) {
          if (((content)[pos] ==10)) {
            break;
          }
          (void)((pos = (pos + 1)));
        }
        continue;
      }
      if ((((content)[pos] ==47) && ((content)[(pos + 1)] ==42))) {
        (void)((pos = (pos + 2)));
        while (((pos + 1) < ni)) {
          if ((((content)[pos] ==42) && ((content)[(pos + 1)] ==47))) {
            break;
          }
          (void)((pos = (pos + 1)));
        }
        if (((pos + 1) < ni)) {
          (void)((pos = (pos + 2)));
        }
        continue;
      }
    }
    if (((content)[pos] ==34)) {
      (void)((pos = (pos + 1)));
      while ((pos < ni)) {
        if (((content)[pos] ==34)) {
          break;
        }
        if (((content)[pos] ==92)) {
          if (((pos + 1) < ni)) {
            (void)((pos = (pos + 2)));
            continue;
          }
        }
        (void)((pos = (pos + 1)));
      }
      if ((pos < ni)) {
        (void)((pos = (pos + 1)));
      }
      continue;
    }
    if (((pos + 3) <=ni)) {
      if (((((content)[pos] ==60) && ((content)[(pos + 1)] ==60)) && ((content)[(pos + 2)] ==61))) {
        return 1;
      }
      if (((((content)[pos] ==62) && ((content)[(pos + 1)] ==62)) && ((content)[(pos + 2)] ==61))) {
        return 1;
      }
    }
    if (((pos + 2) <=ni)) {
      uint8_t a = (content)[pos];
      uint8_t b = (content)[(pos + 1)];
      if ((b ==61)) {
        if ((a ==43)) {
          return 1;
        }
        if ((a ==45)) {
          return 1;
        }
        if ((a ==42)) {
          return 1;
        }
        if ((a ==47)) {
          return 1;
        }
        if ((a ==37)) {
          return 1;
        }
        if ((a ==38)) {
          return 1;
        }
        if ((a ==124)) {
          return 1;
        }
        if ((a ==94)) {
          return 1;
        }
      }
    }
    (void)((pos = (pos + 1)));
  }
  return 0;
}
int32_t driver_run_x_emit_c_set_emit_extern(int32_t v) {
  return 0;
}
int32_t driver_run_x_emit_c_set_n_lib_roots(int32_t n) {
  return 0;
}
extern int32_t main_run_compiler_c(int32_t argc, uint8_t * argv);
extern int32_t driver_run_fmt(int32_t argc, uint8_t * argv);
extern int32_t driver_run_compiler_check(int32_t argc, uint8_t * argv);
int32_t run_compiler_c(int32_t argc, uint8_t * argv) {
  return main_run_compiler_c(argc, argv);
  return -1;
}
int32_t runtime_run_fmt_c(int32_t argc, uint8_t * argv) {
  return driver_run_fmt(argc, argv);
  return -1;
}
int32_t runtime_run_compiler_check_c(int32_t argc, uint8_t * argv) {
  return driver_run_compiler_check(argc, argv);
  return -1;
}
int32_t driver_x_emit_asm_direct_import_only(uint8_t * input_path) {
  if ((input_path ==0)) {
    return 0;
  }
  int32_t plen = 0;
  while ((plen < 4096)) {
    if (((input_path)[plen] ==0)) {
      break;
    }
    (void)((plen = (plen + 1)));
  }
  int32_t s = 0;
  while (((s + 13) <=plen)) {
    if (((((((((((((((input_path)[s] ==115) && ((input_path)[(s + 1)] ==114)) && ((input_path)[(s + 2)] ==99)) && ((input_path)[(s + 3)] ==47)) && ((input_path)[(s + 4)] ==97)) && ((input_path)[(s + 5)] ==115)) && ((input_path)[(s + 6)] ==109)) && ((input_path)[(s + 7)] ==47)) && ((input_path)[(s + 8)] ==97)) && ((input_path)[(s + 9)] ==115)) && ((input_path)[(s + 10)] ==109)) && ((input_path)[(s + 11)] ==46)) && ((input_path)[(s + 12)] ==120))) {
      return 1;
    }
    (void)((s = (s + 1)));
  }
  (void)((s = 0));
  while (((s + 10) <=plen)) {
    if ((((((((((((input_path)[s] ==47) && ((input_path)[(s + 1)] ==97)) && ((input_path)[(s + 2)] ==115)) && ((input_path)[(s + 3)] ==109)) && ((input_path)[(s + 4)] ==47)) && ((input_path)[(s + 5)] ==97)) && ((input_path)[(s + 6)] ==115)) && ((input_path)[(s + 7)] ==109)) && ((input_path)[(s + 8)] ==46)) && ((input_path)[(s + 9)] ==120))) {
      return 1;
    }
    (void)((s = (s + 1)));
  }
  (void)((s = 0));
  while (((s + 23) <=plen)) {
    if (((((((((((((((((((((((((input_path)[s] ==115) && ((input_path)[(s + 1)] ==114)) && ((input_path)[(s + 2)] ==99)) && ((input_path)[(s + 3)] ==47)) && ((input_path)[(s + 4)] ==97)) && ((input_path)[(s + 5)] ==115)) && ((input_path)[(s + 6)] ==109)) && ((input_path)[(s + 7)] ==47)) && ((input_path)[(s + 8)] ==97)) && ((input_path)[(s + 9)] ==115)) && ((input_path)[(s + 10)] ==109)) && ((input_path)[(s + 11)] ==95)) && ((input_path)[(s + 12)] ==115)) && ((input_path)[(s + 13)] ==101)) && ((input_path)[(s + 14)] ==101)) && ((input_path)[(s + 15)] ==100)) && ((input_path)[(s + 16)] ==95)) && ((input_path)[(s + 17)] ==102)) && ((input_path)[(s + 18)] ==117)) && ((input_path)[(s + 19)] ==108)) && ((input_path)[(s + 20)] ==108)) && ((input_path)[(s + 21)] ==46)) && ((input_path)[(s + 22)] ==120))) {
      return 1;
    }
    (void)((s = (s + 1)));
  }
  (void)((s = 0));
  while (((s + 20) <=plen)) {
    if ((((((((((((((((((((((input_path)[s] ==47) && ((input_path)[(s + 1)] ==97)) && ((input_path)[(s + 2)] ==115)) && ((input_path)[(s + 3)] ==109)) && ((input_path)[(s + 4)] ==47)) && ((input_path)[(s + 5)] ==97)) && ((input_path)[(s + 6)] ==115)) && ((input_path)[(s + 7)] ==109)) && ((input_path)[(s + 8)] ==95)) && ((input_path)[(s + 9)] ==115)) && ((input_path)[(s + 10)] ==101)) && ((input_path)[(s + 11)] ==101)) && ((input_path)[(s + 12)] ==100)) && ((input_path)[(s + 13)] ==95)) && ((input_path)[(s + 14)] ==102)) && ((input_path)[(s + 15)] ==117)) && ((input_path)[(s + 16)] ==108)) && ((input_path)[(s + 17)] ==108)) && ((input_path)[(s + 18)] ==46)) && ((input_path)[(s + 19)] ==120))) {
      return 1;
    }
    (void)((s = (s + 1)));
  }
  return 0;
}
int32_t driver_x_emit_asm_dep_parse_skip_typeck_ok(uint8_t * input_path, uint8_t * dep_path) {
  if ((driver_x_emit_asm_direct_import_only(input_path) ==0)) {
    return 0;
  }
  if ((dep_path ==0)) {
    return 0;
  }
  if ((((((((((dep_path)[0] ==98) && ((dep_path)[1] ==97)) && ((dep_path)[2] ==99)) && ((dep_path)[3] ==107)) && ((dep_path)[4] ==101)) && ((dep_path)[5] ==110)) && ((dep_path)[6] ==100)) && ((dep_path)[7] ==0))) {
    return 1;
  }
  return 0;
}
int32_t driver_x_emit_asm_dep_parse_only_ok(uint8_t * input_path, uint8_t * dep_path) {
  if ((input_path ==0)) {
    return 0;
  }
  if ((dep_path ==0)) {
    return 0;
  }
  int32_t plen = 0;
  while ((plen < 4096)) {
    if (((input_path)[plen] ==0)) {
      break;
    }
    (void)((plen = (plen + 1)));
  }
  int32_t hit = 0;
  int32_t s = 0;
  while (((s + 13) <=plen)) {
    if (((((((((((((((input_path)[s] ==115) && ((input_path)[(s + 1)] ==114)) && ((input_path)[(s + 2)] ==99)) && ((input_path)[(s + 3)] ==47)) && ((input_path)[(s + 4)] ==97)) && ((input_path)[(s + 5)] ==115)) && ((input_path)[(s + 6)] ==109)) && ((input_path)[(s + 7)] ==47)) && ((input_path)[(s + 8)] ==97)) && ((input_path)[(s + 9)] ==115)) && ((input_path)[(s + 10)] ==109)) && ((input_path)[(s + 11)] ==46)) && ((input_path)[(s + 12)] ==120))) {
      (void)((hit = 1));
      break;
    }
    (void)((s = (s + 1)));
  }
  if ((hit ==0)) {
    (void)((s = 0));
    while (((s + 10) <=plen)) {
      if ((((((((((((input_path)[s] ==47) && ((input_path)[(s + 1)] ==97)) && ((input_path)[(s + 2)] ==115)) && ((input_path)[(s + 3)] ==109)) && ((input_path)[(s + 4)] ==47)) && ((input_path)[(s + 5)] ==97)) && ((input_path)[(s + 6)] ==115)) && ((input_path)[(s + 7)] ==109)) && ((input_path)[(s + 8)] ==46)) && ((input_path)[(s + 9)] ==120))) {
        (void)((hit = 1));
        break;
      }
      (void)((s = (s + 1)));
    }
  }
  if ((hit ==0)) {
    return 0;
  }
  if ((((((dep_path)[0] ==97) && ((dep_path)[1] ==115)) && ((dep_path)[2] ==116)) && ((dep_path)[3] ==0))) {
    return 1;
  }
  if ((((((((((dep_path)[0] ==99) && ((dep_path)[1] ==111)) && ((dep_path)[2] ==100)) && ((dep_path)[3] ==101)) && ((dep_path)[4] ==103)) && ((dep_path)[5] ==101)) && ((dep_path)[6] ==110)) && ((dep_path)[7] ==0))) {
    return 1;
  }
  if ((((((((((dep_path)[0] ==98) && ((dep_path)[1] ==97)) && ((dep_path)[2] ==99)) && ((dep_path)[3] ==107)) && ((dep_path)[4] ==101)) && ((dep_path)[5] ==110)) && ((dep_path)[6] ==100)) && ((dep_path)[7] ==0))) {
    return 1;
  }
  if (((((((((((dep_path)[0] ==112) && ((dep_path)[1] ==101)) && ((dep_path)[2] ==101)) && ((dep_path)[3] ==112)) && ((dep_path)[4] ==104)) && ((dep_path)[5] ==111)) && ((dep_path)[6] ==108)) && ((dep_path)[7] ==101)) && ((dep_path)[8] ==0))) {
    return 1;
  }
  if ((((((dep_path)[0] ==97) && ((dep_path)[1] ==115)) && ((dep_path)[2] ==109)) && ((dep_path)[3] ==46))) {
    return 1;
  }
  if (((((((dep_path)[0] ==97) && ((dep_path)[1] ==114)) && ((dep_path)[2] ==99)) && ((dep_path)[3] ==104)) && ((dep_path)[4] ==46))) {
    return 1;
  }
  if (((((((((((dep_path)[0] ==112) && ((dep_path)[1] ==108)) && ((dep_path)[2] ==97)) && ((dep_path)[3] ==116)) && ((dep_path)[4] ==102)) && ((dep_path)[5] ==111)) && ((dep_path)[6] ==114)) && ((dep_path)[7] ==109)) && ((dep_path)[8] ==46))) {
    return 1;
  }
  return 0;
}
