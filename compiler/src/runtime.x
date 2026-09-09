// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.

export extern "C" function driver_run_x_emit_c_set_path_impl(path: *u8, path_len: i32): i32;
export extern "C" function driver_run_x_emit_c_set_lib_impl(i: i32, buf: *u8, len: i32): i32;
export extern "C" function driver_fs_open_read_path_impl(path: *u8, path_len: i32): i32;
export extern "C" function driver_run_asm_backend_c_impl(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, argc: i32, argv: *u8): i32;
export extern "C" function driver_run_emit_c_path_c_impl(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, opt_level: *u8, use_lto: i32, argc: i32, argv: *u8): i32;
export extern "C" function driver_compile_state_free_c_impl(state: *u8): void;
export extern "C" function cfg_sync_compile_target_from_state_c_impl(state: *u8): void;
export extern "C" function driver_compile_ensure_default_lib_c_impl(key: *u8): void;
export extern "C" function driver_compile_parse_argv_init_c_impl(state: *u8): void;
export extern "C" function driver_compile_append_lib_root_c_impl(state: *u8, path: *u8, len: i32): void;
export extern "C" function driver_compile_argv_apply_minus_o_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void;
export extern "C" function driver_compile_argv_apply_minus_L_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void;
export extern "C" function driver_compile_argv_apply_minus_O_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void;
export extern "C" function driver_compile_argv_set_use_lto_c_impl(state: *u8): void;
export extern "C" function driver_compile_argv_set_use_freestanding_c_impl(state: *u8): void;
export extern "C" function driver_compile_argv_set_legacy_f32_abi_c_impl(): void;
export extern "C" function driver_compile_argv_set_sanitize_address_c_impl(): void;
export extern "C" function driver_compile_argv_apply_backend_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void;
export extern "C" function driver_compile_argv_apply_target_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void;
export extern "C" function driver_compile_argv_apply_target_cpu_next_c_impl(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void;
export extern "C" function driver_compile_argv_set_print_target_cpu_c_impl(state: *u8): void;
export extern "C" function driver_print_target_cpu_features_c_impl(features: i32): i32;
export extern "C" function driver_compile_resolve_target_cpu_c_impl(state: *u8): void;
export extern "C" function driver_run_compiler_full_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_run_test_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_fmt_report_no_files_impl(): i32;

export extern "C" function run_compiler_x_path_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_want_asm_emit_to_file_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_exec_compiled_impl(argc: i32, argv_opaque: *u8): i32;
export extern "C" function driver_build_build_x_impl(): i32;
export extern "C" function driver_fs_open_write_impl(path: *u8, path_len: i32): i32;
export extern "C" function driver_source_has_generic_syntax_impl(path: *u8, path_len: i32): i32;
export extern "C" function driver_source_has_compound_assign_syntax_impl(path: *u8, path_len: i32): i32;
export extern "C" function driver_run_asm_backend_impl(input_path: *u8, out_path: *u8, lib_roots_arr: *u8, n_lib_roots: i32, target: *u8, argc: i32, argv: *u8): i32;
export extern "C" function driver_compile_parse_argv_scan_c_impl(argc: i32, argv_opaque: *u8, state: *u8): void;
export extern "C" function driver_compile_argv_copy_path_c_impl(state: *u8, arg_buf: *u8, plen: i32): void;
export extern "C" function driver_compile_argv_is_help_c_impl(argc: i32, argv_opaque: *u8): i32;
export extern "C" function driver_print_usage_c_impl(): void;
export extern "C" function driver_argv_parse_x_emit_c_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_run_x_emit_c_impl(): i32;
export extern "C" function driver_fmt_one_file_impl(path: *u8, path_len: i32): i32;
export extern "C" function main_entry_impl(argc: i32, argv: *u8): i32;

/* See implementation. */


export extern "C" function driver_unlink_failed_output_impl(out_path: *u8): void;


export extern "C" function runtime_diag_cli_usage_note_impl(argv0: *u8): void;
export extern "C" function runtime_diag_errno_impl(file: *u8, kind: *u8, op: *u8): void;
export extern "C" function runtime_diag_errno_path_impl(file: *u8, kind: *u8, op: *u8, path: *u8): void;
export extern "C" function runtime_diag_errno_path_pair_impl(file: *u8, kind: *u8, op: *u8, from_path: *u8, to_path: *u8): void;
export extern "C" function runtime_try_handle_explain_cli_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_emit_legacy_smoke_summary_stdout_impl(main_name: *u8, main_final_lit: i32, has_main_body: i32): void;
export extern "C" function runtime_diag_code_for_kind_impl(kind: *u8): *u8;

export extern "C" function driver_lib_root_ptr_usable_impl(p: *u8): i32;
export extern "C" function drv_eq_minus_o_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_L_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_O_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_flto_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_freestanding_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_legacy_f32_abi_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_fsanitize_address_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_backend_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_target_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_target_cpu_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_print_target_cpu_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_asm_word_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_c_word_impl(buf: *u8, len: i32): i32;
export extern "C" function drv_path_ends_x_impl(buf: *u8, len: i32): i32;

export extern "C" function driver_deps_are_std_core_closure_only_impl(dep_paths: *u8, n_deps: i32): i32;
export extern "C" function driver_c_mod_imports_are_core_only_impl(mod: *u8): i32;
export extern "C" function driver_lib_root_default_impl(root_buf: *u8): void;
export extern "C" function runtime_test_status_to_rc_impl(script: *u8, st: i32): i32;

export extern "C" function xlang_get_tmp_prefix_impl(): *u8;
export extern "C" function dce_is_func_used_impl(ctx: *u8, mod: *u8, func: *u8): i32;
export extern "C" function dce_is_mono_used_impl(ctx: *u8, mod: *u8, k: i32): i32;
export extern "C" function dce_is_type_used_impl(ctx: *u8, mod: *u8, type_name: *u8): i32;
export extern "C" function runtime_report_precise_parse_failure_if_known_impl(input_path: *u8, src: *u8, src_len: i64): i32;
export extern "C" function runtime_run_test_c_impl(argc: i32, argv: *u8): i32;
export extern "C" function driver_lib_roots_from_key_impl(lib_key: *u8, out_arr: *u8, bufs: *u8): i32;

export extern "C" function runtime_prepare_dce_ctx_impl(mod: *u8, all_dep_mods: *u8, n_all: i32, used_funcs: *u8, n_used: *i32, used_mono: *u8, used_type_names: *u8, n_used_types: *i32, wpo_reach: *u8, dce: *u8, dce_ready: *i32): void;
export extern "C" function driver_run_x_emit_c_from_compile_state_impl(state: *u8, argc: i32, argv: *u8): i32;

export extern "C" function write_fs_path_map_error_abi_inline_impl(cf: *u8): i32;
export extern "C" function codegen_emit_include_pipeline_glue_c_impl(out: *u8, argv0: *u8): void;
export extern "C" function runtime_pipeline_elf_ctx_diag_note_impl(ctx_bytes: *u8): void;
export extern "C" function driver_compile_parse_argv_step_c_impl(argc: i32, argv: *u8, state: *u8, i: i32, arg_buf: *u8, arg_cap: i32): i32;



/** Exported function `driver_run_x_emit_c_set_path`.
 * Implements `driver_run_x_emit_c_set_path`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c_set_path(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_run_x_emit_c_set_path_impl(path, path_len);
  }
  return 0 - 1;
}

/** Exported function `driver_run_x_emit_c_set_lib`.
 * Implements `driver_run_x_emit_c_set_lib`.
 * @param i i32
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c_set_lib(i: i32, buf: *u8, len: i32): i32 {
  unsafe {
    return driver_run_x_emit_c_set_lib_impl(i, buf, len);
  }
  return 0 - 1;
}





/** Exported function `driver_fs_open_read_path`.
 * Read path helper `driver_fs_open_read_path`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_fs_open_read_path(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_fs_open_read_path_impl(path, path_len);
  }
  return 0 - 1;
}



/** Exported function `driver_run_asm_backend_c`.
 * Implements `driver_run_asm_backend_c`.
 * @param input_path *u8
 * @param out_path *u8
 * @param lib_key *u8
 * @param target *u8
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_asm_backend_c(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_asm_backend_c_impl(input_path, out_path, lib_key, target, argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_run_emit_c_path_c`.
 * Implements `driver_run_emit_c_path_c`.
 * @param input_path *u8
 * @param out_path *u8
 * @param lib_key *u8
 * @param target *u8
 * @param opt_level *u8
 * @param use_lto i32
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_emit_c_path_c(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, opt_level: *u8, use_lto: i32, argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_emit_c_path_c_impl(input_path, out_path, lib_key, target, opt_level, use_lto, argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_compile_state_free_c`.
 * Memory management helper `driver_compile_state_free_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_state_free_c(state: *u8): void {
  unsafe {
    driver_compile_state_free_c_impl(state);
  }
}

/** Exported function `cfg_sync_compile_target_from_state_c`.
 * Implements `cfg_sync_compile_target_from_state_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function cfg_sync_compile_target_from_state_c(state: *u8): void {
  unsafe {
    cfg_sync_compile_target_from_state_c_impl(state);
  }
}

/** Exported function `driver_compile_ensure_default_lib_c`.
 * Implements `driver_compile_ensure_default_lib_c`.
 * @param key *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_ensure_default_lib_c(key: *u8): void {
  unsafe {
    driver_compile_ensure_default_lib_c_impl(key);
  }
}

/** Exported function `driver_compile_parse_argv_init_c`.
 * Implements `driver_compile_parse_argv_init_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_parse_argv_init_c(state: *u8): void {
  unsafe {
    driver_compile_parse_argv_init_c_impl(state);
  }
}

/** Exported function `driver_compile_append_lib_root_c`.
 * Implements `driver_compile_append_lib_root_c`.
 * @param state *u8
 * @param path *u8
 * @param len i32
 * @return void
 */
#[no_mangle]
export function driver_compile_append_lib_root_c(state: *u8, path: *u8, len: i32): void {
  unsafe {
    driver_compile_append_lib_root_c_impl(state, path, len);
  }
}

/** Exported function `driver_compile_argv_apply_minus_o_next_c`.
 * Implements `driver_compile_argv_apply_minus_o_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_o_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void {
  unsafe {
    driver_compile_argv_apply_minus_o_next_c_impl(state, argc, argv_opaque, i);
  }
}

/** Exported function `driver_compile_argv_apply_minus_L_next_c`.
 * Implements `driver_compile_argv_apply_minus_L_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @param arg_buf *u8
 * @param arg_cap i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_L_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void {
  unsafe {
    driver_compile_argv_apply_minus_L_next_c_impl(state, argc, argv_opaque, i, arg_buf, arg_cap);
  }
}

/** Exported function `driver_compile_argv_apply_minus_O_next_c`.
 * Implements `driver_compile_argv_apply_minus_O_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_O_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void {
  unsafe {
    driver_compile_argv_apply_minus_O_next_c_impl(state, argc, argv_opaque, i);
  }
}

/** Exported function `driver_compile_argv_set_use_lto_c`.
 * Implements `driver_compile_argv_set_use_lto_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_use_lto_c(state: *u8): void {
  unsafe {
    driver_compile_argv_set_use_lto_c_impl(state);
  }
}

/** Exported function `driver_compile_argv_set_use_freestanding_c`.
 * Memory management helper `driver_compile_argv_set_use_freestanding_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_use_freestanding_c(state: *u8): void {
  unsafe {
    driver_compile_argv_set_use_freestanding_c_impl(state);
  }
}

/** Exported function `driver_compile_argv_set_legacy_f32_abi_c`.
 * Implements `driver_compile_argv_set_legacy_f32_abi_c`.
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_legacy_f32_abi_c(): void {
  unsafe {
    driver_compile_argv_set_legacy_f32_abi_c_impl();
  }
}

/** Exported function `driver_compile_argv_set_sanitize_address_c`.
 * Implements `driver_compile_argv_set_sanitize_address_c`.
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_sanitize_address_c(): void {
  unsafe {
    driver_compile_argv_set_sanitize_address_c_impl();
  }
}

/** Exported function `driver_compile_argv_apply_backend_next_c`.
 * Implements `driver_compile_argv_apply_backend_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @param arg_buf *u8
 * @param arg_cap i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_backend_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void {
  unsafe {
    driver_compile_argv_apply_backend_next_c_impl(state, argc, argv_opaque, i, arg_buf, arg_cap);
  }
}

/** Exported function `driver_compile_argv_apply_target_next_c`.
 * Implements `driver_compile_argv_apply_target_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_target_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void {
  unsafe {
    driver_compile_argv_apply_target_next_c_impl(state, argc, argv_opaque, i);
  }
}

/** Exported function `driver_compile_argv_apply_target_cpu_next_c`.
 * Implements `driver_compile_argv_apply_target_cpu_next_c`.
 * @param state *u8
 * @param argc i32
 * @param argv_opaque *u8
 * @param i i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_apply_target_cpu_next_c(state: *u8, argc: i32, argv_opaque: *u8, i: i32): void {
  unsafe {
    driver_compile_argv_apply_target_cpu_next_c_impl(state, argc, argv_opaque, i);
  }
}

/** Exported function `driver_compile_argv_set_print_target_cpu_c`.
 * Implements `driver_compile_argv_set_print_target_cpu_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_print_target_cpu_c(state: *u8): void {
  unsafe {
    driver_compile_argv_set_print_target_cpu_c_impl(state);
  }
}

/** Exported function `driver_print_target_cpu_features_c`.
 * Implements `driver_print_target_cpu_features_c`.
 * @param features i32
 * @return i32
 */
#[no_mangle]
export function driver_print_target_cpu_features_c(features: i32): i32 {
  unsafe {
    return driver_print_target_cpu_features_c_impl(features);
  }
  return 0 - 1;
}

/** Exported function `driver_compile_resolve_target_cpu_c`.
 * Implements `driver_compile_resolve_target_cpu_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_resolve_target_cpu_c(state: *u8): void {
  unsafe {
    driver_compile_resolve_target_cpu_c_impl(state);
  }
}

/** Exported function `driver_run_compiler_full`.
 * Implements `driver_run_compiler_full`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_compiler_full(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_compiler_full_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_run_test`.
 * Implements `driver_run_test`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_test(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_test_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_fmt_report_no_files`.
 * Implements `driver_fmt_report_no_files`.
 * @return i32
 */
#[no_mangle]
export function driver_fmt_report_no_files(): i32 {
  unsafe {
    return driver_fmt_report_no_files_impl();
  }
  return 0 - 1;
}

/* ---- G-02f-72：driver mid gates (argv scan / main_entry / emit / fmt) ---- */

#[no_mangle]
export function run_compiler_x_path(argc: i32, argv: *u8): i32 {
  unsafe {
    return run_compiler_x_path_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_want_asm_emit_to_file`.
 * Implements `driver_want_asm_emit_to_file`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_want_asm_emit_to_file(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_want_asm_emit_to_file_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_exec_compiled`.
 * Implements `driver_exec_compiled`.
 * @param argc i32
 * @param argv_opaque *u8
 * @return i32
 */
#[no_mangle]
export function driver_exec_compiled(argc: i32, argv_opaque: *u8): i32 {
  unsafe {
    return driver_exec_compiled_impl(argc, argv_opaque);
  }
  return 0 - 1;
}

/** Exported function `driver_build_build_x`.
 * Implements `driver_build_build_x`.
 * @return i32
 */
#[no_mangle]
export function driver_build_build_x(): i32 {
  unsafe {
    return driver_build_build_x_impl();
  }
  return 0 - 1;
}

/** Exported function `driver_fs_open_write`.
 * Write path helper `driver_fs_open_write`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_fs_open_write(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_fs_open_write_impl(path, path_len);
  }
  return 0 - 1;
}

/** Exported function `driver_source_has_generic_syntax`.
 * Implements `driver_source_has_generic_syntax`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_source_has_generic_syntax(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_source_has_generic_syntax_impl(path, path_len);
  }
  return 0 - 1;
}

/** Exported function `driver_source_has_compound_assign_syntax`.
 * Implements `driver_source_has_compound_assign_syntax`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_source_has_compound_assign_syntax(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_source_has_compound_assign_syntax_impl(path, path_len);
  }
  return 0 - 1;
}

/** Exported function `driver_run_asm_backend`.
 * Implements `driver_run_asm_backend`.
 * @param input_path *u8
 * @param out_path *u8
 * @param lib_roots_arr *u8
 * @param n_lib_roots i32
 * @param target *u8
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_asm_backend(input_path: *u8, out_path: *u8, lib_roots_arr: *u8, n_lib_roots: i32, target: *u8, argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_asm_backend_impl(input_path, out_path, lib_roots_arr, n_lib_roots, target, argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_compile_parse_argv_scan_c`.
 * Implements `driver_compile_parse_argv_scan_c`.
 * @param argc i32
 * @param argv_opaque *u8
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_parse_argv_scan_c(argc: i32, argv_opaque: *u8, state: *u8): void {
  unsafe {
    driver_compile_parse_argv_scan_c_impl(argc, argv_opaque, state);
  }
}

/** Exported function `driver_compile_argv_copy_path_c`.
 * Implements `driver_compile_argv_copy_path_c`.
 * @param state *u8
 * @param arg_buf *u8
 * @param plen i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_copy_path_c(state: *u8, arg_buf: *u8, plen: i32): void {
  unsafe {
    driver_compile_argv_copy_path_c_impl(state, arg_buf, plen);
  }
}

/** Exported function `driver_compile_argv_is_help_c`.
 * Implements `driver_compile_argv_is_help_c`.
 * @param argc i32
 * @param argv_opaque *u8
 * @return i32
 */
#[no_mangle]
export function driver_compile_argv_is_help_c(argc: i32, argv_opaque: *u8): i32 {
  unsafe {
    return driver_compile_argv_is_help_c_impl(argc, argv_opaque);
  }
  return 0 - 1;
}

/** Exported function `driver_print_usage_c`.
 * Implements `driver_print_usage_c`.
 * @return void
 */
#[no_mangle]
export function driver_print_usage_c(): void {
  unsafe {
    driver_print_usage_c_impl();
  }
}

/** Exported function `driver_argv_parse_x_emit_c`.
 * Implements `driver_argv_parse_x_emit_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_argv_parse_x_emit_c(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_argv_parse_x_emit_c_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_run_x_emit_c`.
 * Implements `driver_run_x_emit_c`.
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c(): i32 {
  unsafe {
    return driver_run_x_emit_c_impl();
  }
  return 0 - 1;
}

/** Exported function `driver_fmt_one_file`.
 * Implements `driver_fmt_one_file`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
#[no_mangle]
export function driver_fmt_one_file(path: *u8, path_len: i32): i32 {
  unsafe {
    return driver_fmt_one_file_impl(path, path_len);
  }
  return 0 - 1;
}

/** Exported function `main_entry`.
 * Implements `main_entry`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function main_entry(argc: i32, argv: *u8): i32 {
  unsafe {
    return main_entry_impl(argc, argv);
  }
  return 0 - 1;
}


/* See implementation. */


#[no_mangle]
export function driver_unlink_failed_output(out_path: *u8): void {
  unsafe {
    driver_unlink_failed_output_impl(out_path);
  }
}

// See implementation.


/* See implementation. */

#[no_mangle]
export function runtime_diag_cli_usage_note(argv0: *u8): void {
  unsafe {
    runtime_diag_cli_usage_note_impl(argv0);
  }
}

/** Exported function `runtime_diag_errno`.
 * Implements `runtime_diag_errno`.
 * @param file *u8
 * @param kind *u8
 * @param op *u8
 * @return void
 */
#[no_mangle]
export function runtime_diag_errno(file: *u8, kind: *u8, op: *u8): void {
  unsafe {
    runtime_diag_errno_impl(file, kind, op);
  }
}

/** Exported function `runtime_diag_errno_path`.
 * Implements `runtime_diag_errno_path`.
 * @param file *u8
 * @param kind *u8
 * @param op *u8
 * @param path *u8
 * @return void
 */
#[no_mangle]
export function runtime_diag_errno_path(file: *u8, kind: *u8, op: *u8, path: *u8): void {
  unsafe {
    runtime_diag_errno_path_impl(file, kind, op, path);
  }
}

/** Exported function `runtime_diag_errno_path_pair`.
 * Implements `runtime_diag_errno_path_pair`.
 * @param file *u8
 * @param kind *u8
 * @param op *u8
 * @param from_path *u8
 * @param to_path *u8
 * @return void
 */
#[no_mangle]
export function runtime_diag_errno_path_pair(file: *u8, kind: *u8, op: *u8, from_path: *u8, to_path: *u8): void {
  unsafe {
    runtime_diag_errno_path_pair_impl(file, kind, op, from_path, to_path);
  }
}

/** Exported function `runtime_try_handle_explain_cli`.
 * Implements `runtime_try_handle_explain_cli`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function runtime_try_handle_explain_cli(argc: i32, argv: *u8): i32 {
  unsafe {
    return runtime_try_handle_explain_cli_impl(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `driver_emit_legacy_smoke_summary_stdout`.
 * Implements `driver_emit_legacy_smoke_summary_stdout`.
 * @param main_name *u8
 * @param main_final_lit i32
 * @param has_main_body i32
 * @return void
 */
#[no_mangle]
export function driver_emit_legacy_smoke_summary_stdout(main_name: *u8, main_final_lit: i32, has_main_body: i32): void {
  unsafe {
    driver_emit_legacy_smoke_summary_stdout_impl(main_name, main_final_lit, has_main_body);
  }
}

/** Exported function `runtime_diag_code_for_kind`.
 * Implements `runtime_diag_code_for_kind`.
 * @param kind *u8
 * @return *u8
 */
#[no_mangle]
export function runtime_diag_code_for_kind(kind: *u8): *u8 {
  unsafe {
    return runtime_diag_code_for_kind_impl(kind);
  }
  return 0 as *u8;
}

/* See implementation. */






















/* See implementation. */





#[no_mangle]
export function driver_deps_are_std_core_closure_only(dep_paths: *u8, n_deps: i32): i32 {
  unsafe {
    return driver_deps_are_std_core_closure_only_impl(dep_paths, n_deps);
  }
  return 0;
}

/** Exported function `driver_c_mod_imports_are_core_only`.
 * Implements `driver_c_mod_imports_are_core_only`.
 * @param mod *u8
 * @return i32
 */
#[no_mangle]
export function driver_c_mod_imports_are_core_only(mod: *u8): i32 {
  unsafe {
    return driver_c_mod_imports_are_core_only_impl(mod);
  }
  return 0;
}

/*
 * Retired mega wrapper: driver_check_only_c_typeck forwarded to
 * never-defined driver_check_only_c_typeck_impl. C frontend was
 * physically deleted; product typeck authority is
 * pipeline_typeck_entry_module / pipeline_typeck_entry_module_c.
 * rt_run_* leftover consume sites retired (this knife). Re-adding this export
 * here would first-wins the same class as the deleted
 * smoke_lex_dump / c_typeck_entry / esc_gate stubs. Missing
 * provider → link UNDEF, not a silent _impl -1.
 * PLATFORM: SHARED — prove surface runtime_surface.from_x.c is
 * isomorphic; product g05 does not link this mega.
 */

/** Exported function `driver_lib_root_default`.
 * Implements `driver_lib_root_default`.
 * @param root_buf *u8
 * @return void
 */
#[no_mangle]
export function driver_lib_root_default(root_buf: *u8): void {
  unsafe {
    driver_lib_root_default_impl(root_buf);
  }
}

/** Exported function `runtime_test_status_to_rc`.
 * Implements `runtime_test_status_to_rc`.
 * @param script *u8
 * @param st i32
 * @return i32
 */
#[no_mangle]
export function runtime_test_status_to_rc(script: *u8, st: i32): i32 {
  unsafe {
    return runtime_test_status_to_rc_impl(script, st);
  }
  return 0;
}





/* See implementation. */

#[no_mangle]
export function xlang_get_tmp_prefix(): *u8 {
  unsafe {
    return xlang_get_tmp_prefix_impl();
  }
  return 0 as *u8;
}

/** Exported function `dce_is_func_used`.
 * Implements `dce_is_func_used`.
 * @param ctx *u8
 * @param mod *u8
 * @param func *u8
 * @return i32
 */
#[no_mangle]
export function dce_is_func_used(ctx: *u8, mod: *u8, func: *u8): i32 {
  unsafe {
    return dce_is_func_used_impl(ctx, mod, func);
  }
  return 0;
}

/** Exported function `dce_is_mono_used`.
 * Implements `dce_is_mono_used`.
 * @param ctx *u8
 * @param mod *u8
 * @param k i32
 * @return i32
 */
#[no_mangle]
export function dce_is_mono_used(ctx: *u8, mod: *u8, k: i32): i32 {
  unsafe {
    return dce_is_mono_used_impl(ctx, mod, k);
  }
  return 0;
}

/** Exported function `dce_is_type_used`.
 * Implements `dce_is_type_used`.
 * @param ctx *u8
 * @param mod *u8
 * @param type_name *u8
 * @return i32
 */
#[no_mangle]
export function dce_is_type_used(ctx: *u8, mod: *u8, type_name: *u8): i32 {
  unsafe {
    return dce_is_type_used_impl(ctx, mod, type_name);
  }
  return 0;
}

/** Exported function `runtime_report_precise_parse_failure_if_known`.
 * Implements `runtime_report_precise_parse_failure_if_known`.
 * @param input_path *u8
 * @param src *u8
 * @param src_len i64
 * @return i32
 */
#[no_mangle]
export function runtime_report_precise_parse_failure_if_known(input_path: *u8, src: *u8, src_len: i64): i32 {
  unsafe {
    return runtime_report_precise_parse_failure_if_known_impl(input_path, src, src_len);
  }
  return 0;
}

/** Exported function `runtime_run_test_c`.
 * Implements `runtime_run_test_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function runtime_run_test_c(argc: i32, argv: *u8): i32 {
  unsafe {
    return runtime_run_test_c_impl(argc, argv);
  }
  return 0;
}

/** Exported function `driver_lib_roots_from_key`.
 * Implements `driver_lib_roots_from_key`.
 * @param lib_key *u8
 * @param out_arr *u8
 * @param bufs *u8
 * @return i32
 */
#[no_mangle]
export function driver_lib_roots_from_key(lib_key: *u8, out_arr: *u8, bufs: *u8): i32 {
  unsafe {
    return driver_lib_roots_from_key_impl(lib_key, out_arr, bufs);
  }
  return 0;
}

/*
 * Retired mega wrappers: driver_smoke_lex_dump_{on_large_stack,thread_fn}
 * and driver_c_typeck_entry{,_thread_fn,_large_stack} forwarded to
 * never-defined *_impl. C frontend was physically deleted; product
 * typeck authority is pipeline_typeck_entry_module /
 * pipeline_typeck_entry_module_c. rt_run_* leftover consume sites
 * retired (this knife). Re-adding these export names here would first-wins
 * the same class as the deleted esc_gate / typeck / parser /
 * asm_codegen_ast stubs. Missing provider → link UNDEF, not a
 * silent _impl -1.
 * PLATFORM: SHARED — prove surface runtime_surface.from_x.c is
 * isomorphic; product g05 does not link this mega.
 */

/*
 * Retired mega wrappers: driver_c_frontend_smoke /
 * driver_check_only_c_typeck forwarded to never-defined *_impl.
 * Same class as smoke_lex_dump / c_typeck_entry above (C frontend
 * gone; product typeck = pipeline_typeck_entry_module). rt_run_*
 * leftover consume sites retired (this knife). Re-adding these
 * export names here would
 * first-wins the same class. Missing provider → link UNDEF, not a
 * silent _impl -1.
 * PLATFORM: SHARED — prove surface isomorphic; product g05 does
 * not link this mega.
 */

/*
 * Retired mega wrappers: driver_stack_esc_gate_thread_fn / large_stack
 * forwarded to never-defined *_impl. Product authority is
 * src/runtime/rt_stack.x (+ seeds/rt_stack.from_x.c cold twin).
 * Re-adding these export names here would duplicate rt_stack (ELF/Mach-O
 * first-wins) the same class as the deleted typeck/parser/asm_codegen_ast
 * weak stubs. Missing provider → link UNDEF, not a silent _impl -1.
 * PLATFORM: SHARED — prove surface runtime_surface.from_x.c is isomorphic;
 * product g05 links rt_stack.o, not this mega.
 */

/** Exported function `runtime_prepare_dce_ctx`.
 * Implements `runtime_prepare_dce_ctx`.
 * @param mod *u8
 * @param all_dep_mods *u8
 * @param n_all i32
 * @param used_funcs *u8
 * @param n_used *i32
 * @param used_mono *u8
 * @param used_type_names *u8
 * @param n_used_types *i32
 * @param wpo_reach *u8
 * @param dce *u8
 * @param dce_ready *i32
 * @return void
 */
#[no_mangle]
export function runtime_prepare_dce_ctx(mod: *u8, all_dep_mods: *u8, n_all: i32, used_funcs: *u8, n_used: *i32, used_mono: *u8, used_type_names: *u8, n_used_types: *i32, wpo_reach: *u8, dce: *u8, dce_ready: *i32): void {
  unsafe {
    runtime_prepare_dce_ctx_impl(mod, all_dep_mods, n_all, used_funcs, n_used, used_mono, used_type_names, n_used_types, wpo_reach, dce, dce_ready);
  }
}

/** Exported function `driver_run_x_emit_c_from_compile_state`.
 * Implements `driver_run_x_emit_c_from_compile_state`.
 * @param state *u8
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c_from_compile_state(state: *u8, argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_x_emit_c_from_compile_state_impl(state, argc, argv);
  }
  return 0 - 1;
}

/*
 * Retired mega wrapper: driver_c_frontend_smoke (see
 * driver_c_frontend_smoke / driver_check_only_c_typeck retirement
 * above). PLATFORM: SHARED — do not re-add.
 */

/*
 * Retired mega wrapper: driver_try_compile_via_shu_c_sibling forwarded
 * to never-defined driver_try_compile_via_shu_c_sibling_impl. Product
 * authority is rt_dispatch_thin.x → driver_dispatch_sibling_try_spawn
 * (HAS a real fork/exec body; leftover consume site retired at residual
 * 6). Re-adding this export here would first-wins overlay the spawn
 * body — same class as the deleted smoke / c_typeck / esc_gate /
 * via_cparser stubs. Missing provider → link UNDEF, not a silent
 * _impl -1. Do not delete the spawn body itself.
 * PLATFORM: SHARED — prove surface runtime_surface.from_x.c is
 * isomorphic; product g05 does not link this mega.
 */

/*
 * Retired mega wrapper: driver_smoke_lex_dump_thread_fn (see
 * driver_smoke_lex_dump / driver_c_typeck_entry retirement above).
 * PLATFORM: SHARED — do not re-add.
 */

/* See implementation. */

#[no_mangle]
export function write_fs_path_map_error_abi_inline(cf: *u8): i32 {
  unsafe {
    return write_fs_path_map_error_abi_inline_impl(cf);
  }
  return 0 - 1;
}

/** Exported function `codegen_emit_include_pipeline_glue_c`.
 * Implements `codegen_emit_include_pipeline_glue_c`.
 * @param out *u8
 * @param argv0 *u8
 * @return void
 */
#[no_mangle]
export function codegen_emit_include_pipeline_glue_c(out: *u8, argv0: *u8): void {
  unsafe {
    codegen_emit_include_pipeline_glue_c_impl(out, argv0);
  }
}

/** Exported function `runtime_pipeline_elf_ctx_diag_note`.
 * Implements `runtime_pipeline_elf_ctx_diag_note`.
 * @param ctx_bytes *u8
 * @return void
 */
#[no_mangle]
export function runtime_pipeline_elf_ctx_diag_note(ctx_bytes: *u8): void {
  unsafe {
    runtime_pipeline_elf_ctx_diag_note_impl(ctx_bytes);
  }
}

/** Exported function `driver_compile_parse_argv_step_c`.
 * Implements `driver_compile_parse_argv_step_c`.
 * @param argc i32
 * @param argv *u8
 * @param state *u8
 * @param i i32
 * @param arg_buf *u8
 * @param arg_cap i32
 * @return i32
 */
#[no_mangle]
export function driver_compile_parse_argv_step_c(argc: i32, argv: *u8, state: *u8, i: i32, arg_buf: *u8, arg_cap: i32): i32 {
  unsafe {
    return driver_compile_parse_argv_step_c_impl(argc, argv, state, i, arg_buf, arg_cap);
  }
  return i + 1;
}

// See implementation.
// See implementation.

export extern "C" function write_io_net_abi_inline_impl(cf: *u8): i32;
export extern "C" function driver_run_compiler_parsed_impl(p: *u8, argc: i32, argv: *u8): i32;

/* See implementation. */

#[no_mangle]
export function write_io_net_abi_inline(cf: *u8): i32 { unsafe { return write_io_net_abi_inline_impl(cf); } return 0; }
/** Exported function `driver_run_compiler_parsed`.
 * Implements `driver_run_compiler_parsed`.
 * @param p *u8
 * @param argc i32
 * @param argv *u8): i32 { unsafe { return driver_run_compiler_parsed_impl(p
 * @param argc
 * @param argv
 * @return void
 */
#[no_mangle]
export function driver_run_compiler_parsed(p: *u8, argc: i32, argv: *u8): i32 { unsafe { return driver_run_compiler_parsed_impl(p, argc, argv); } return 0; }

/*
 * Retired mega wrapper: driver_run_x_emit_c_extern_via_cparser forwarded
 * to never-defined driver_run_x_emit_c_extern_via_cparser_impl. C
 * frontend was physically deleted; leftover consume site in
 * rt_run_x_emit.from_x.c retired at residual 7. Product -E-extern
 * authority is driver_run_x_emit_c → driver_x_emit_try_extern_via_cparser
 * (always BLD001). Re-adding this export here would first-wins the
 * same class as the deleted smoke / c_typeck / esc_gate stubs.
 * Missing provider → link UNDEF, not a silent _impl -1.
 * PLATFORM: SHARED — prove surface runtime_surface.from_x.c is
 * isomorphic; product g05 does not link this mega.
 */

// See implementation.

/*
 * Retired mega wrapper: driver_c_typeck_entry (see
 * driver_smoke_lex_dump / driver_c_typeck_entry retirement above).
 * PLATFORM: SHARED — do not re-add.
 */

// drv_eq_minus_o: see function docblock below.

/** Exported function `drv_eq_minus_o`.
 * Implements `drv_eq_minus_o`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_o(buf: *u8, len: i32): i32 {
  if (len != 2) { return 0; }
  if (buf[0] == 45 && buf[1] == 111) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_L`.
 * Implements `drv_eq_minus_L`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_L(buf: *u8, len: i32): i32 {
  if (len != 2) { return 0; }
  if (buf[0] == 45 && buf[1] == 76) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_O`.
 * Implements `drv_eq_minus_O`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_O(buf: *u8, len: i32): i32 {
  if (len != 2) { return 0; }
  if (buf[0] == 45 && buf[1] == 79) { return 1; }
  return 0;
}

/** Exported function `drv_eq_flto`.
 * Implements `drv_eq_flto`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_flto(buf: *u8, len: i32): i32 {
  if (len != 5) { return 0; }
  if (buf[0] == 45 && buf[1] == 102 && buf[2] == 108 && buf[3] == 116 && buf[4] == 111) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_freestanding`.
 * Memory management helper `drv_eq_minus_freestanding`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_freestanding(buf: *u8, len: i32): i32 {
  if (len != 13) { return 0; }
  // -freestanding
  if (buf[0] == 45 && buf[1] == 102 && buf[2] == 114 && buf[3] == 101 && buf[4] == 101
      && buf[5] == 115 && buf[6] == 116 && buf[7] == 97 && buf[8] == 110 && buf[9] == 100
      && buf[10] == 105 && buf[11] == 110 && buf[12] == 103) { return 1; }
  return 0;
}

/** Exported function `drv_eq_legacy_f32_abi`.
 * Implements `drv_eq_legacy_f32_abi`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_legacy_f32_abi(buf: *u8, len: i32): i32 {
  if (len != 15) { return 0; }
  // -legacy-f32-abi
  if (buf[0] == 45 && buf[1] == 108 && buf[2] == 101 && buf[3] == 103 && buf[4] == 97
      && buf[5] == 99 && buf[6] == 121 && buf[7] == 45 && buf[8] == 102 && buf[9] == 51
      && buf[10] == 50 && buf[11] == 45 && buf[12] == 97 && buf[13] == 98 && buf[14] == 105) { return 1; }
  return 0;
}

/** Exported function `drv_eq_fsanitize_address`.
 * Implements `drv_eq_fsanitize_address`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_fsanitize_address(buf: *u8, len: i32): i32 {
  if (len != 18) { return 0; }
  // -fsanitize=address
  if (buf[0] == 45 && buf[1] == 102 && buf[2] == 115 && buf[3] == 97 && buf[4] == 110
      && buf[5] == 105 && buf[6] == 116 && buf[7] == 105 && buf[8] == 122 && buf[9] == 101
      && buf[10] == 61 && buf[11] == 97 && buf[12] == 100 && buf[13] == 100 && buf[14] == 114
      && buf[15] == 101 && buf[16] == 115 && buf[17] == 115) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_backend`.
 * Implements `drv_eq_minus_backend`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_backend(buf: *u8, len: i32): i32 {
  if (len != 8) { return 0; }
  // -backend
  if (buf[0] == 45 && buf[1] == 98 && buf[2] == 97 && buf[3] == 99 && buf[4] == 107
      && buf[5] == 101 && buf[6] == 110 && buf[7] == 100) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_target`.
 * Implements `drv_eq_minus_target`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_target(buf: *u8, len: i32): i32 {
  if (len != 7) { return 0; }
  // -target
  if (buf[0] == 45 && buf[1] == 116 && buf[2] == 97 && buf[3] == 114 && buf[4] == 103
      && buf[5] == 101 && buf[6] == 116) { return 1; }
  return 0;
}

/** Exported function `drv_eq_minus_target_cpu`.
 * Implements `drv_eq_minus_target_cpu`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_minus_target_cpu(buf: *u8, len: i32): i32 {
  if (len != 11) { return 0; }
  // -target-cpu
  if (buf[0] == 45 && buf[1] == 116 && buf[2] == 97 && buf[3] == 114 && buf[4] == 103
      && buf[5] == 101 && buf[6] == 116 && buf[7] == 45 && buf[8] == 99 && buf[9] == 112
      && buf[10] == 117) { return 1; }
  return 0;
}

/** Exported function `drv_eq_print_target_cpu`.
 * Implements `drv_eq_print_target_cpu`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_print_target_cpu(buf: *u8, len: i32): i32 {
  // --print-target-cpu (18) or -print-target-cpu (17)
  if (len == 18) {
    if (buf[0] == 45 && buf[1] == 45 && buf[2] == 112 && buf[3] == 114 && buf[4] == 105
        && buf[5] == 110 && buf[6] == 116 && buf[7] == 45 && buf[8] == 116 && buf[9] == 97
        && buf[10] == 114 && buf[11] == 103 && buf[12] == 101 && buf[13] == 116 && buf[14] == 45
        && buf[15] == 99 && buf[16] == 112 && buf[17] == 117) { return 1; }
  }
  if (len == 17) {
    if (buf[0] == 45 && buf[1] == 112 && buf[2] == 114 && buf[3] == 105 && buf[4] == 110
        && buf[5] == 116 && buf[6] == 45 && buf[7] == 116 && buf[8] == 97 && buf[9] == 114
        && buf[10] == 103 && buf[11] == 101 && buf[12] == 116 && buf[13] == 45 && buf[14] == 99
        && buf[15] == 112 && buf[16] == 117) { return 1; }
  }
  return 0;
}

/** Exported function `drv_eq_asm_word`.
 * Implements `drv_eq_asm_word`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_asm_word(buf: *u8, len: i32): i32 {
  if (len != 3) { return 0; }
  if (buf[0] == 97 && buf[1] == 115 && buf[2] == 109) { return 1; }
  return 0;
}

/** Exported function `drv_eq_c_word`.
 * Implements `drv_eq_c_word`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_eq_c_word(buf: *u8, len: i32): i32 {
  if (len != 1) { return 0; }
  if (buf[0] == 99) { return 1; }
  return 0;
}

/** Exported function `drv_path_ends_x`.
 * Implements `drv_path_ends_x`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_path_ends_x(buf: *u8, len: i32): i32 {
  if (len >= 2) {
    if (buf[len - 2] == 46 && buf[len - 1] == 120) { return 1; }
  }
  if (len >= 3) {
    if (buf[len - 3] == 46 && buf[len - 2] == 115 && buf[len - 1] == 117) { return 1; }
  }
  return 0;
}

/** Exported function `driver_lib_root_ptr_usable`.
 * Implements `driver_lib_root_ptr_usable`.
 * @param p *u8
 * @return i32
 */
#[no_mangle]
export function driver_lib_root_ptr_usable(p: *u8): i32 {
  // See implementation.
  if (p == 0) { return 0; }
  if (p[0] == 0) { return 0; }
  return 1;
}

/* wave242 G.7: dual-anchor env via public pure thin link_abi_getenv (wave222 → _impl host
 * getenv); not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * Product hybrid authority remains rt_entry pure (wave227 already link_abi_getenv); this
 * file is the cold/.x dual anchor and must match pure semantics.
 * PLATFORM: SHARED orch / host getenv residual via single face. */
export extern "C" function link_abi_getenv(name: *u8): *u8;

export extern "C" function diag_json_enabled(): i32;

/**
 * Whether structured smoke diagnostic emission is enabled.
 * Dual-anchor mirror of rt_entry pure orch (wave227 G.7).
 * True when diag JSON mode is on, or XLANG_SMOKE_DIAG is set to a non-empty value
 * other than ASCII '0' (48).
 * @return i32 — 1 enabled, 0 disabled
 * wave242: raw getenv closed — public pure thin link_abi_getenv owns env lookup.
 * PLATFORM: SHARED — process env; host residual only link_abi_getenv_impl.
 */
#[no_mangle]
export function xlang_smoke_diag_enabled(): i32 {
  unsafe {
    let j: i32 = diag_json_enabled();
    if (j != 0) { return 1; }
    let e: *u8 = link_abi_getenv("XLANG_SMOKE_DIAG");
    if (e == 0) { return 0; }
    if (e[0] == 0) { return 0; }
    /* Leading ASCII '0' (48) disables smoke diag. */
    if (e[0] == 48) { return 0; }
    return 1;
  }
  return 0;
}

// See implementation.

export extern "C" function xlang_output_want_exe(path: *u8): i32;

/** Exported function `driver_asm_output_want_exe`.
 * Implements `driver_asm_output_want_exe`.
 * @param path *u8
 * @return i32
 */
#[no_mangle]
export function driver_asm_output_want_exe(path: *u8): i32 {
  unsafe {
    return xlang_output_want_exe(path);
  }
  return 0;
}

// See implementation.

export extern "C" function driver_argv_at(argv: *u8, i: i32): *u8;

/** Exported function `drv_target_has_arm`.
 * Implements `drv_target_has_arm`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function drv_target_has_arm(buf: *u8, len: i32): i32 {
  if (buf == 0) { return 0; }
  let start: i32 = 0;
  while (start + 5 <= len) {
    // arm64
    if (buf[start]==97 && buf[start+1]==114 && buf[start+2]==109 && buf[start+3]==54 && buf[start+4]==52) {
      return 1;
    }
    start = start + 1;
  }
  return 0;
}

/** Exported function `driver_argv_has_emit_c_flag`.
 * Implements `driver_argv_has_emit_c_flag`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_argv_has_emit_c_flag(argc: i32, argv: *u8): i32 {
  if (argc < 2) { return 0; }
  if (argv == 0) { return 0; }
  let i: i32 = 1;
  while (i < argc) {
    unsafe {
      let s: *u8 = driver_argv_at(argv, i);
      if (s != 0) {
        // "-E"
        if (s[0]==45 && s[1]==69 && s[2]==0) { return 1; }
        // "-E-extern"
        if (s[0]==45 && s[1]==69 && s[2]==45 && s[3]==101 && s[4]==120 && s[5]==116
            && s[6]==101 && s[7]==114 && s[8]==110 && s[9]==0) {
          return 1;
        }
      }
    }
    i = i + 1;
  }
  return 0;
}

/** Exported function `driver_argv0_basename_is`.
 * Implements `driver_argv0_basename_is`.
 * @param argv0 *u8
 * @param base *u8
 * @return i32
 */
#[no_mangle]
export function driver_argv0_basename_is(argv0: *u8, base: *u8): i32 {
  if (base == 0) { return 0; }
  // find last / or \
  let name: *u8 = argv0;
  if (argv0 != 0) {
    let i: i32 = 0;
    let last: i32 = 0 - 1;
    while (i < 4096) {
      let c: u8 = argv0[i];
      if (c == 0) { break; }
      if (c == 47) { last = i; }
      if (c == 92) { last = i; }
      i = i + 1;
    }
    if (last >= 0) {
      // name = argv0 + last + 1
      unsafe {
        // compare from last+1
        let j: i32 = 0;
        while (j < 256) {
          let a: u8 = argv0[last + 1 + j];
          let b: u8 = base[j];
          if (a != b) { return 0; }
          if (a == 0) { return 1; }
          j = j + 1;
        }
      }
      return 0;
    }
  } else {
    name = 0 as *u8;
  }
  // no slash: compare argv0 or empty with base
  if (argv0 == 0) {
    if (base[0] == 0) { return 1; }
    return 0;
  }
  let j: i32 = 0;
  while (j < 256) {
    let a: u8 = argv0[j];
    let b: u8 = base[j];
    if (a != b) { return 0; }
    if (a == 0) { return 1; }
    j = j + 1;
  }
  return 0;
}

// content_has_generic_syntax: see function docblock below.

/** Exported function `content_has_generic_syntax`.
 * Implements `content_has_generic_syntax`.
 * @param content *u8
 * @param n i64
 * @return i32
 */
#[no_mangle]
export function content_has_generic_syntax(content: *u8, n: i64): i32 {
  if (content == 0) { return 0; }
  if (n == 0) { return 0; }
  let ni: i32 = n as i32;
  // scan for '<'
  let p: i32 = 0;
  while (p < ni) {
    if (content[p] == 60) { // '<'
      if (p + 1 >= ni) { break; }
      // skip T[]<region> — previous char is ']'
      if (p > 0) {
        if (content[p - 1] == 93) { // ']'
          p = p + 1;
          continue;
        }
      }
      // <T> or <T,
      if (content[p + 1] == 84) { // 'T'
        if (p + 2 >= ni) { return 1; }
        if (content[p + 2] == 62) { return 1; } // '>'
        if (content[p + 2] == 44) { return 1; } // ','
      }
      // generic type tokens
      // <i8> <i16> <i32> <i64> <u8> <u16> <u32> <u64> <f32> <f64> <bool>
      if (p + 4 <= ni) {
        // <i8>
        if (content[p+1]==105 && content[p+2]==56 && content[p+3]==62) { return 1; }
        // <u8>
        if (content[p+1]==117 && content[p+2]==56 && content[p+3]==62) { return 1; }
      }
      if (p + 5 <= ni) {
        // <i16> <i32> <i64> <u16> <u32> <u64> <f32> <f64>
        if (content[p+1]==105 && content[p+2]==49 && content[p+3]==54 && content[p+4]==62) { return 1; }
        if (content[p+1]==105 && content[p+2]==51 && content[p+3]==50 && content[p+4]==62) { return 1; }
        if (content[p+1]==105 && content[p+2]==54 && content[p+3]==52 && content[p+4]==62) { return 1; }
        if (content[p+1]==117 && content[p+2]==49 && content[p+3]==54 && content[p+4]==62) { return 1; }
        if (content[p+1]==117 && content[p+2]==51 && content[p+3]==50 && content[p+4]==62) { return 1; }
        if (content[p+1]==117 && content[p+2]==54 && content[p+3]==52 && content[p+4]==62) { return 1; }
        if (content[p+1]==102 && content[p+2]==51 && content[p+3]==50 && content[p+4]==62) { return 1; }
        if (content[p+1]==102 && content[p+2]==54 && content[p+3]==52 && content[p+4]==62) { return 1; }
      }
      if (p + 6 <= ni) {
        // <bool>
        if (content[p+1]==98 && content[p+2]==111 && content[p+3]==111 && content[p+4]==108 && content[p+5]==62) {
          return 1;
        }
      }
    }
    p = p + 1;
  }
  // "trait " / " impl "
  if (ni >= 6) {
    let i: i32 = 0;
    while (i <= ni - 6) {
      // trait 
      if (content[i]==116 && content[i+1]==114 && content[i+2]==97 && content[i+3]==105
          && content[i+4]==116 && content[i+5]==32) {
        return 1;
      }
      //  impl 
      if (content[i]==32 && content[i+1]==105 && content[i+2]==109 && content[i+3]==112
          && content[i+4]==108 && content[i+5]==32) {
        return 1;
      }
      i = i + 1;
    }
  }
  return 0;
}

/** Exported function `content_has_compound_assign_syntax`.
 * Implements `content_has_compound_assign_syntax`.
 * @param content *u8
 * @param n i64
 * @return i32
 */
#[no_mangle]
export function content_has_compound_assign_syntax(content: *u8, n: i64): i32 {
  if (content == 0) { return 0; }
  if (n < 3) { return 0; }
  let ni: i32 = n as i32;
  let pos: i32 = 0;
  while (pos < ni) {
    // // line comment
    if (pos + 1 < ni) {
      if (content[pos] == 47 && content[pos + 1] == 47) {
        pos = pos + 2;
        while (pos < ni) {
          if (content[pos] == 10) { break; }
          pos = pos + 1;
        }
        continue;
      }
      // /* block */
      if (content[pos] == 47 && content[pos + 1] == 42) {
        pos = pos + 2;
        while (pos + 1 < ni) {
          if (content[pos] == 42 && content[pos + 1] == 47) { break; }
          pos = pos + 1;
        }
        if (pos + 1 < ni) { pos = pos + 2; }
        continue;
      }
    }
    // string "
    if (content[pos] == 34) {
      pos = pos + 1;
      while (pos < ni) {
        if (content[pos] == 34) { break; }
        if (content[pos] == 92) {
          if (pos + 1 < ni) { pos = pos + 2; continue; }
        }
        pos = pos + 1;
      }
      if (pos < ni) { pos = pos + 1; }
      continue;
    }
    // tokens long first: <<= >>= += -= *= /= %= &= |= ^=
    if (pos + 3 <= ni) {
      if (content[pos]==60 && content[pos+1]==60 && content[pos+2]==61) { return 1; }
      if (content[pos]==62 && content[pos+1]==62 && content[pos+2]==61) { return 1; }
    }
    if (pos + 2 <= ni) {
      let a: u8 = content[pos];
      let b: u8 = content[pos + 1];
      if (b == 61) {
        if (a == 43) { return 1; }
        if (a == 45) { return 1; }
        if (a == 42) { return 1; }
        if (a == 47) { return 1; }
        if (a == 37) { return 1; }
        if (a == 38) { return 1; }
        if (a == 124) { return 1; }
        if (a == 94) { return 1; }
      }
    }
    pos = pos + 1;
  }
  return 0;
}

// emit setters: product seed C owns static state; .x documents entry (return 0)
/** Exported function `driver_run_x_emit_c_set_emit_extern`.
 * Implements `driver_run_x_emit_c_set_emit_extern`.
 * @param v i32
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c_set_emit_extern(v: i32): i32 {
  // product: seeds/runtime.from_x.c sets driver_x_emit_c_want_extern
  return 0;
}

/** Exported function `driver_run_x_emit_c_set_n_lib_roots`.
 * Implements `driver_run_x_emit_c_set_n_lib_roots`.
 * @param n i32
 * @return i32
 */
#[no_mangle]
export function driver_run_x_emit_c_set_n_lib_roots(n: i32): i32 {
  // product: seeds/runtime.from_x.c clamps to X_EMIT_MAX_LIB_ROOTS(16)
  return 0;
}

// See implementation.

export extern "C" function main_run_compiler_c(argc: i32, argv: *u8): i32;
export extern "C" function driver_run_fmt(argc: i32, argv: *u8): i32;
export extern "C" function driver_run_compiler_check(argc: i32, argv: *u8): i32;

/** Exported function `run_compiler_c`.
 * Implements `run_compiler_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function run_compiler_c(argc: i32, argv: *u8): i32 {
  unsafe {
    return main_run_compiler_c(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `runtime_run_fmt_c`.
 * Implements `runtime_run_fmt_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function runtime_run_fmt_c(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_fmt(argc, argv);
  }
  return 0 - 1;
}

/** Exported function `runtime_run_compiler_check_c`.
 * Implements `runtime_run_compiler_check_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function runtime_run_compiler_check_c(argc: i32, argv: *u8): i32 {
  unsafe {
    return driver_run_compiler_check(argc, argv);
  }
  return 0 - 1;
}

// driver_x_emit_asm_direct_import_only: see function docblock below.

/** Exported function `driver_x_emit_asm_direct_import_only`.
 * Implements `driver_x_emit_asm_direct_import_only`.
 * @param input_path *u8
 * @return i32
 */
#[no_mangle]
export function driver_x_emit_asm_direct_import_only(input_path: *u8): i32 {
  if (input_path == 0) { return 0; }
  let plen: i32 = 0;
  while (plen < 4096) {
    if (input_path[plen] == 0) { break; }
    plen = plen + 1;
  }
  // "src/asm/asm.x" (13)
  let s: i32 = 0;
  while (s + 13 <= plen) {
    if (input_path[s]==115 && input_path[s+1]==114 && input_path[s+2]==99 && input_path[s+3]==47
        && input_path[s+4]==97 && input_path[s+5]==115 && input_path[s+6]==109 && input_path[s+7]==47
        && input_path[s+8]==97 && input_path[s+9]==115 && input_path[s+10]==109 && input_path[s+11]==46
        && input_path[s+12]==120) {
      return 1;
    }
    s = s + 1;
  }
  // "/asm/asm.x" (10)
  s = 0;
  while (s + 10 <= plen) {
    if (input_path[s]==47 && input_path[s+1]==97 && input_path[s+2]==115 && input_path[s+3]==109
        && input_path[s+4]==47 && input_path[s+5]==97 && input_path[s+6]==115 && input_path[s+7]==109
        && input_path[s+8]==46 && input_path[s+9]==120) {
      return 1;
    }
    s = s + 1;
  }
  // "src/asm/asm_seed_full.x" (23)
  s = 0;
  while (s + 23 <= plen) {
    if (input_path[s]==115 && input_path[s+1]==114 && input_path[s+2]==99 && input_path[s+3]==47
        && input_path[s+4]==97 && input_path[s+5]==115 && input_path[s+6]==109 && input_path[s+7]==47
        && input_path[s+8]==97 && input_path[s+9]==115 && input_path[s+10]==109 && input_path[s+11]==95
        && input_path[s+12]==115 && input_path[s+13]==101 && input_path[s+14]==101 && input_path[s+15]==100
        && input_path[s+16]==95 && input_path[s+17]==102 && input_path[s+18]==117 && input_path[s+19]==108
        && input_path[s+20]==108 && input_path[s+21]==46 && input_path[s+22]==120) {
      return 1;
    }
    s = s + 1;
  }
  // "/asm/asm_seed_full.x" (20)
  s = 0;
  while (s + 20 <= plen) {
    if (input_path[s]==47 && input_path[s+1]==97 && input_path[s+2]==115 && input_path[s+3]==109
        && input_path[s+4]==47 && input_path[s+5]==97 && input_path[s+6]==115 && input_path[s+7]==109
        && input_path[s+8]==95 && input_path[s+9]==115 && input_path[s+10]==101 && input_path[s+11]==101
        && input_path[s+12]==100 && input_path[s+13]==95 && input_path[s+14]==102 && input_path[s+15]==117
        && input_path[s+16]==108 && input_path[s+17]==108 && input_path[s+18]==46 && input_path[s+19]==120) {
      return 1;
    }
    s = s + 1;
  }
  return 0;
}

/** Exported function `driver_x_emit_asm_dep_parse_skip_typeck_ok`.
 * Implements `driver_x_emit_asm_dep_parse_skip_typeck_ok`.
 * @param input_path *u8
 * @param dep_path *u8
 * @return i32
 */
#[no_mangle]
export function driver_x_emit_asm_dep_parse_skip_typeck_ok(input_path: *u8, dep_path: *u8): i32 {
  if (driver_x_emit_asm_direct_import_only(input_path) == 0) { return 0; }
  if (dep_path == 0) { return 0; }
  // strcmp(dep_path, "backend") == 0
  if (dep_path[0]==98 && dep_path[1]==97 && dep_path[2]==99 && dep_path[3]==107
      && dep_path[4]==101 && dep_path[5]==110 && dep_path[6]==100 && dep_path[7]==0) {
    return 1;
  }
  return 0;
}

// driver_x_emit_asm_dep_parse_only_ok: see function docblock below.
/** Exported function `driver_x_emit_asm_dep_parse_only_ok`.
 * Implements `driver_x_emit_asm_dep_parse_only_ok`.
 * @param input_path *u8
 * @param dep_path *u8
 * @return i32
 */
#[no_mangle]
export function driver_x_emit_asm_dep_parse_only_ok(input_path: *u8, dep_path: *u8): i32 {
  if (input_path == 0) { return 0; }
  if (dep_path == 0) { return 0; }
  // must contain "src/asm/asm.x" or "/asm/asm.x"
  let plen: i32 = 0;
  while (plen < 4096) {
    if (input_path[plen] == 0) { break; }
    plen = plen + 1;
  }
  let hit: i32 = 0;
  let s: i32 = 0;
  while (s + 13 <= plen) {
    if (input_path[s]==115 && input_path[s+1]==114 && input_path[s+2]==99 && input_path[s+3]==47
        && input_path[s+4]==97 && input_path[s+5]==115 && input_path[s+6]==109 && input_path[s+7]==47
        && input_path[s+8]==97 && input_path[s+9]==115 && input_path[s+10]==109 && input_path[s+11]==46
        && input_path[s+12]==120) {
      hit = 1;
      break;
    }
    s = s + 1;
  }
  if (hit == 0) {
    s = 0;
    while (s + 10 <= plen) {
      if (input_path[s]==47 && input_path[s+1]==97 && input_path[s+2]==115 && input_path[s+3]==109
          && input_path[s+4]==47 && input_path[s+5]==97 && input_path[s+6]==115 && input_path[s+7]==109
          && input_path[s+8]==46 && input_path[s+9]==120) {
        hit = 1;
        break;
      }
      s = s + 1;
    }
  }
  if (hit == 0) { return 0; }
  // exact: ast / codegen / backend / peephole
  if (dep_path[0]==97 && dep_path[1]==115 && dep_path[2]==116 && dep_path[3]==0) { return 1; }
  if (dep_path[0]==99 && dep_path[1]==111 && dep_path[2]==100 && dep_path[3]==101
      && dep_path[4]==103 && dep_path[5]==101 && dep_path[6]==110 && dep_path[7]==0) {
    return 1;
  }
  if (dep_path[0]==98 && dep_path[1]==97 && dep_path[2]==99 && dep_path[3]==107
      && dep_path[4]==101 && dep_path[5]==110 && dep_path[6]==100 && dep_path[7]==0) {
    return 1;
  }
  if (dep_path[0]==112 && dep_path[1]==101 && dep_path[2]==101 && dep_path[3]==112
      && dep_path[4]==104 && dep_path[5]==111 && dep_path[6]==108 && dep_path[7]==101
      && dep_path[8]==0) {
    return 1;
  }
  // prefixes: asm. / arch. / platform.
  if (dep_path[0]==97 && dep_path[1]==115 && dep_path[2]==109 && dep_path[3]==46) { return 1; }
  if (dep_path[0]==97 && dep_path[1]==114 && dep_path[2]==99 && dep_path[3]==104 && dep_path[4]==46) {
    return 1;
  }
  if (dep_path[0]==112 && dep_path[1]==108 && dep_path[2]==97 && dep_path[3]==116 && dep_path[4]==102
      && dep_path[5]==111 && dep_path[6]==114 && dep_path[7]==109 && dep_path[8]==46) {
    return 1;
  }
  return 0;
}
