// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// G-02f-314/444 → R2 full: -x -E emit body.
// .x owns driver_run_x_emit_c; product PREFER rest is marker only (business H=0).
// Cap residual (driver_abi): stdout/OutBuf/ptr tables/parse/diag/typeck + work slots
//   (avoid 50+ locals lifted static / body drop under -E; ban **u8).
// Steps: read_pp / parse / load_deps / prerun / finish.
// PLATFORM: SHARED — surface short names are the link-name contract (Track L).
// Comment rule: never put star-slash sequences inside block comments.

export extern "C" function malloc(n: usize): *u8;
export extern "C" function free(p: *u8): void;
export extern "C" function memset(p: *u8, c: i32, n: usize): *u8;
export extern "C" function runtime_read_file_malloc(path: *u8, out_len: *usize): *u8;
export extern "C" function xlang_preprocess_with_path(
  data: *u8, len: usize, path: *u8, defines: *u8, n_defines: i32, out_len: *usize): *u8;
export extern "C" function xlang_preprocess(
  data: *u8, len: usize, defines: *u8, n_defines: i32, out_len: *usize): *u8;
export extern "C" function pipeline_diag_emitted_reset(): void;
export extern "C" function pipeline_diag_emitted_get(): i32;
export extern "C" function diag_set_file(path: *u8, src: *u8, len: usize): void;
export extern "C" function pipeline_sizeof_arena(): usize;
export extern "C" function pipeline_sizeof_module(): usize;
export extern "C" function parser_parse_into_init(module: *u8, arena: *u8): void;
export extern "C" function parser_parse_into_set_main_index(module: *u8, main_idx: i32): void;
export extern "C" function driver_get_module_num_funcs(m: *u8): i32;
export extern "C" function parser_get_module_num_imports(module: *u8): i32;
export extern "C" function xlang_get_entry_dir(path: *u8, out: *u8, out_sz: usize): void;
export extern "C" function pipeline_set_entry_dir(dir: *u8): void;
export extern "C" function driver_x_emit_asm_direct_import_only(input_path: *u8): i32;
export extern "C" function driver_x_emit_asm_dep_parse_only_ok(input_path: *u8, dep_path: *u8): i32;
export extern "C" function driver_x_emit_asm_dep_parse_skip_typeck_ok(
  input_path: *u8, dep_path: *u8): i32;
export extern "C" function driver_dep_seeded_clear_all(): void;
export extern "C" function driver_set_current_dep_path_for_codegen(path: *u8): void;
export extern "C" function xlang_pipeline_dep_prerun_parse_skip_typeck(
  mod: *u8, arena: *u8, src: *u8, len: usize, out: *u8, ctx: *u8): i32;
export extern "C" function xlang_pipeline_dep_prerun_parse_only(
  mod: *u8, arena: *u8, src: *u8, len: usize): i32;
export extern "C" function xlang_pipeline_dep_prerun_typeck_only(
  mod: *u8, arena: *u8, src: *u8, len: usize, out: *u8, ctx: *u8): i32;
export extern "C" function driver_dep_publish_slot(j: i32, arena: *u8, module: *u8, path: *u8): void;
export extern "C" function pipeline_set_dep_slots(arenas: *u8, modules: *u8): void;
export extern "C" function driver_dep_seed_slots(arenas: *u8, modules: *u8, n: i32): void;
export extern "C" function codegen_set_dep_slots_for_x_pipeline(
  mods: *u8, paths: *u8, n: i32): void;
export extern "C" function runtime_report_precise_parse_failure_if_known(
  input_path: *u8, src: *u8, src_len: usize): i32;
export extern "C" function driver_x_emit_try_extern_via_cparser(input_path: *u8): i32;
export extern "C" function pipeline_dep_ctx_heap_destroy(ctx: *u8): void;
export extern "C" function xlang_pipeline_run_x_pipeline_large_stack(
  module: *u8, arena: *u8, src: *u8, src_len: usize, out_buf: *u8, pctx: *u8): i32;
export extern "C" function xlang_pipeline_fill_ctx_path_buffers(
  ctx: *u8, entry_dir: *u8, lib_roots: *u8, n_lib: i32): void;
/* Opt-in -lib-name prefix (slot + pctx setter authority in rt_emit_state). */
export extern "C" function xlang_driver_x_emit_lib_name_into(out: *u8, cap: i32): i32;
export extern "C" function xlang_pipeline_pctx_set_entry_lib_prefix(ctx: *u8, name: *u8, name_len: i32): void;
export extern "C" function xlang_pipeline_pctx_seed_dep_import_paths_only(
  ctx: *u8, import_paths: *u8, n: i32): void;
export extern "C" function xlang_pipeline_pctx_seed_dep_slots(
  ctx: *u8, dep_mods: *u8, dep_ar: *u8, dep_paths: *u8, n: i32): void;
export extern "C" function xlang_pipeline_one_ctx_for_dep_prerun(
  ctx: *u8, j: i32, dep_mods: *u8, dep_ar: *u8, dep_paths: *u8, n: i32,
  dep_src: *u8, dep_len: usize): void;
export extern "C" function xlang_load_direct_imports_for_asm_layout(
  module: *u8, lib_roots: *u8, n_lib: i32, entry_dir: *u8,
  defines: *u8, n_defines: i32,
  dep_sources: *u8, dep_lens: *u8, dep_paths: *u8, n_deps: *i32): i32;
export extern "C" function xlang_collect_dep_paths_transitive(
  module: *u8, arena_sz: usize, module_sz: usize, lib_roots: *u8, n_lib: i32,
  entry_dir: *u8, defines: *u8, n_defines: i32, cpaths: *u8, n_closure: *i32): i32;
export extern "C" function xlang_merge_direct_then_transitive_dep_paths(
  module: *u8, n_imports: i32, cpaths: *u8, n_closure: i32,
  dep_paths: *u8, n_deps: *i32): i32;
export extern "C" function xlang_resolve_import_file_path_multi(
  lib_roots: *u8, n_lib: i32, entry_dir: *u8, import_path: *u8,
  resolved: *u8, resolved_sz: usize): void;
export extern "C" function pipeline_diag_import_open_fail_once(dep: *u8, resolved: *u8): void;
export extern "C" function xlang_dep_prerun_entry_dir(
  entry_dir: *u8, lib_roots: *u8, n_lib: i32): *u8;
export extern "C" function diag_report_with_code(
  file: *u8, line: i32, col: i32, kind: *u8, code: *u8, msg: *u8, detail: *u8): void;

export extern "C" function driver_x_emit_take_c_path(): *u8;
export extern "C" function driver_x_emit_take_want_extern(): i32;
export extern "C" function driver_x_emit_stdout_set_unbuffered(): void;
export extern "C" function driver_x_emit_fwrite_stdout(data: *u8, len: i32): i32;
export extern "C" function driver_codegen_outbuf_calloc(): *u8;
export extern "C" function driver_codegen_outbuf_free(p: *u8): void;
export extern "C" function driver_codegen_outbuf_len(p: *u8): i32;
export extern "C" function driver_codegen_outbuf_data(p: *u8): *u8;
export extern "C" function driver_pipeline_dep_ctx_calloc(): *u8;
export extern "C" function driver_ptr_table_calloc(n: i32): *u8;
export extern "C" function driver_ptr_table_free(t: *u8): void;
export extern "C" function driver_ptr_table_get(t: *u8, i: i32): *u8;
export extern "C" function driver_ptr_table_set(t: *u8, i: i32, p: *u8): void;
export extern "C" function driver_size_table_calloc(n: i32): *u8;
export extern "C" function driver_size_table_free(t: *u8): void;
export extern "C" function driver_size_table_get(t: *u8, i: i32): usize;
export extern "C" function driver_parse_into_buf_rc(
  arena: *u8, module: *u8, data: *u8, len: i32, out_main_idx: *i32): i32;
export extern "C" function driver_diag_snapshot_alloc(): *u8;
export extern "C" function driver_diag_snapshot_free(s: *u8): void;
export extern "C" function driver_diag_push_file(
  snap: *u8, path: *u8, src: *u8, len: usize): void;
export extern "C" function driver_diag_restore(snap: *u8): void;
export extern "C" function driver_typeck_ndep_set(n: i32): void;
export extern "C" function driver_typeck_dep_ptrs_set(j: i32, mod: *u8, arena: *u8): void;
export extern "C" function driver_path_max_slot(): *u8;
export extern "C" function driver_entry_dir_slot(): *u8;
export extern "C" function driver_x_emit_effective_lib_roots(n_out: *i32): *u8;
export extern "C" function driver_parser_diag_fail_tok_kind(src: *u8, len: usize): i32;
export extern "C" function driver_pipeline_dep_ctx_set_use_asm(ctx: *u8, v: i32): void;
export extern "C" function driver_x_emit_work_reset(): void;
export extern "C" function driver_x_emit_work_p_get(i: i32): *u8;
export extern "C" function driver_x_emit_work_p_set(i: i32, v: *u8): void;
export extern "C" function driver_x_emit_work_i_get(i: i32): i32;
export extern "C" function driver_x_emit_work_i_set(i: i32, v: i32): void;
export extern "C" function driver_x_emit_work_z_get(i: i32): usize;
export extern "C" function driver_x_emit_work_z_set(i: i32, v: usize): void;
export extern "C" function driver_x_emit_work_cleanup(): void;
export extern "C" function typeck_set_allow_legacy_extern_calls(allow: i32): i32;
/* Used by rt_xe_step_finish before fwrite of -E body (same face as
 * rt_run_compiler_parsed / rt_run_asm_backend). Missing decl → tip T001/XT001
 * on pure-asm / -E of this monofile; product PREFER still cold-seed fallback.
 * PLATFORM: SHARED — link-name contract with runtime_driver_abi. */
export extern "C" function driver_print_x_smoke_summary(module: *u8, codegen_len: usize): void;

/* work pointer indices */
/** Work-slot index for entry path pointer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_path).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_path(): i32 { return 0; }
/** Work-slot index for preprocess source buffer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_src).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_src(): i32 { return 1; }
/** Work-slot index for main parse arena.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_arena).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_arena(): i32 { return 3; }
/** Work-slot index for main module pointer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_module).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_module(): i32 { return 4; }
/** Work-slot index for entry-dir buffer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_entry).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_entry(): i32 { return 5; }
/** Work-slot index for dep source pointer table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_dsrc).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_dsrc(): i32 { return 6; }
/** Work-slot index for dep path pointer table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_dpath).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_dpath(): i32 { return 7; }
/** Work-slot index for dep source-length table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_dlens).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_dlens(): i32 { return 8; }
/** Work-slot index for dep arena pointer table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_dar).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_dar(): i32 { return 9; }
/** Work-slot index for dep module pointer table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_dmod).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_dmod(): i32 { return 10; }
/** Work-slot index for codegen OutBuf.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_out).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_out(): i32 { return 11; }
/** Work-slot index for pipeline dep context.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_pctx).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_pctx(): i32 { return 12; }
/** Work-slot index for diagnostic kind scratch buffer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_kind).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_kind(): i32 { return 19; }
/** Work-slot index for diagnostic code scratch buffer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_code).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_code(): i32 { return 20; }
/** Work-slot index for diagnostic message scratch buffer.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_msg).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_msg(): i32 { return 21; }
/** Work-slot index for lib-roots pointer table.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wp_lib).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wp_lib(): i32 { return 24; }

/** Work-int index for n_lib_roots.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wi_nlib).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wi_nlib(): i32 { return 1; }
/** Work-int index for n_deps.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wi_ndeps).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wi_ndeps(): i32 { return 2; }
/** Work-int index for asm-direct / use_asm flag.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wi_asm).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wi_asm(): i32 { return 3; }
/** Work-int index for module import count.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wi_nimp).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wi_nimp(): i32 { return 4; }
/** Work-int index for main function index.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wi_main).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wi_main(): i32 { return 5; }

/** Work-size index for source length.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wz_slen).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wz_slen(): i32 { return 0; }
/** Work-size index for arena sizeof.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wz_asz).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wz_asz(): i32 { return 2; }
/** Work-size index for module sizeof.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_wz_msz).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function wz_msz(): i32 { return 3; }

/** Fill kind buffer with io error (byte writes; no string lit).
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_kind_io).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_kind_io(k: *u8): void {
  k[0] = 105; k[1] = 111; k[2] = 32; k[3] = 101; k[4] = 114; k[5] = 114;
  k[6] = 111; k[7] = 114; k[8] = 0;
}
/** Fill code buffer with IO001.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_io001).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_io001(c: *u8): void {
  c[0] = 73; c[1] = 79; c[2] = 48; c[3] = 48; c[4] = 49; c[5] = 0;
}
/** Fill kind buffer with preprocess error.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_kind_pp).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_kind_pp(k: *u8): void {
  k[0] = 112; k[1] = 114; k[2] = 101; k[3] = 112; k[4] = 114; k[5] = 111;
  k[6] = 99; k[7] = 101; k[8] = 115; k[9] = 115; k[10] = 32; k[11] = 101;
  k[12] = 114; k[13] = 114; k[14] = 111; k[15] = 114; k[16] = 0;
}
/** Fill code buffer with PP002.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_pp002).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_pp002(c: *u8): void {
  c[0] = 80; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 50; c[5] = 0;
}
/** Fill kind buffer with pipeline error.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_kind_pipe).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_kind_pipe(k: *u8): void {
  k[0] = 112; k[1] = 105; k[2] = 112; k[3] = 101; k[4] = 108; k[5] = 105;
  k[6] = 110; k[7] = 101; k[8] = 32; k[9] = 101; k[10] = 114; k[11] = 114;
  k[12] = 111; k[13] = 114; k[14] = 0;
}
/** Fill code buffer with XP003.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_xp003).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_xp003(c: *u8): void {
  c[0] = 88; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 51; c[5] = 0;
}
/** Fill code buffer with XP005.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_xp005).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_xp005(c: *u8): void {
  c[0] = 88; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 53; c[5] = 0;
}
/** Fill code buffer with XP006.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_xp006).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_xp006(c: *u8): void {
  c[0] = 88; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 54; c[5] = 0;
}
/** Fill code buffer with XP007.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_xp007).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_xp007(c: *u8): void {
  c[0] = 88; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 55; c[5] = 0;
}
/** Fill code buffer with XP008.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_xp008).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_xp008(c: *u8): void {
  c[0] = 88; c[1] = 80; c[2] = 48; c[3] = 48; c[4] = 56; c[5] = 0;
}
/** Fill kind buffer with parse error.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_kind_parse).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_kind_parse(k: *u8): void {
  k[0] = 112; k[1] = 97; k[2] = 114; k[3] = 115; k[4] = 101; k[5] = 32;
  k[6] = 101; k[7] = 114; k[8] = 114; k[9] = 111; k[10] = 114; k[11] = 0;
}
/** Fill code buffer with P001.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_p001).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_p001(c: *u8): void {
  c[0] = 80; c[1] = 48; c[2] = 48; c[3] = 49; c[4] = 0;
}
/** Fill kind buffer with codegen error.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_kind_cg).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_kind_cg(k: *u8): void {
  k[0] = 99; k[1] = 111; k[2] = 100; k[3] = 101; k[4] = 103; k[5] = 101;
  k[6] = 110; k[7] = 32; k[8] = 101; k[9] = 114; k[10] = 114; k[11] = 111;
  k[12] = 114; k[13] = 0;
}
/** Fill code buffer with CG004.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_fill_code_cg004).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_fill_code_cg004(c: *u8): void {
  c[0] = 67; c[1] = 71; c[2] = 48; c[3] = 48; c[4] = 52; c[5] = 0;
}
/** Fill message buffer with cannot read file.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_cannot_read).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_cannot_read(m: *u8): void {
  m[0] = 99; m[1] = 97; m[2] = 110; m[3] = 110; m[4] = 111; m[5] = 116;
  m[6] = 32; m[7] = 114; m[8] = 101; m[9] = 97; m[10] = 100; m[11] = 32;
  m[12] = 102; m[13] = 105; m[14] = 108; m[15] = 101; m[16] = 0;
}
/** Fill message buffer with preprocess failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_pp_failed).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_pp_failed(m: *u8): void {
  m[0] = 112; m[1] = 114; m[2] = 101; m[3] = 112; m[4] = 114; m[5] = 111;
  m[6] = 99; m[7] = 101; m[8] = 115; m[9] = 115; m[10] = 32; m[11] = 102;
  m[12] = 97; m[13] = 105; m[14] = 108; m[15] = 101; m[16] = 100; m[17] = 0;
}
/** Fill message buffer with .x pipeline allocation failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_alloc_failed).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_alloc_failed(m: *u8): void {
  m[0] = 46; m[1] = 120; m[2] = 32; m[3] = 112; m[4] = 105; m[5] = 112;
  m[6] = 101; m[7] = 108; m[8] = 105; m[9] = 110; m[10] = 101; m[11] = 32;
  m[12] = 97; m[13] = 108; m[14] = 108; m[15] = 111; m[16] = 99; m[17] = 97;
  m[18] = 116; m[19] = 105; m[20] = 111; m[21] = 110; m[22] = 32; m[23] = 102;
  m[24] = 97; m[25] = 105; m[26] = 108; m[27] = 101; m[28] = 100; m[29] = 0;
}
/** Fill message buffer with .x -E source too large.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_src_too_large).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_src_too_large(m: *u8): void {
  m[0] = 46; m[1] = 120; m[2] = 32; m[3] = 45; m[4] = 69; m[5] = 32;
  m[6] = 115; m[7] = 111; m[8] = 117; m[9] = 114; m[10] = 99; m[11] = 101;
  m[12] = 32; m[13] = 116; m[14] = 111; m[15] = 111; m[16] = 32; m[17] = 108;
  m[18] = 97; m[19] = 114; m[20] = 103; m[21] = 101; m[22] = 0;
}
/** Fill message buffer with .x -E parse failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_parse_failed).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_parse_failed(m: *u8): void {
  m[0] = 46; m[1] = 120; m[2] = 32; m[3] = 45; m[4] = 69; m[5] = 32;
  m[6] = 112; m[7] = 97; m[8] = 114; m[9] = 115; m[10] = 101; m[11] = 32;
  m[12] = 102; m[13] = 97; m[14] = 105; m[15] = 108; m[16] = 101; m[17] = 100;
  m[18] = 0;
}
/** Fill message buffer with dep alloc failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_dep_alloc).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_dep_alloc(m: *u8): void {
  m[0] = 100; m[1] = 101; m[2] = 112; m[3] = 32; m[4] = 97; m[5] = 108;
  m[6] = 108; m[7] = 111; m[8] = 99; m[9] = 32; m[10] = 102; m[11] = 97;
  m[12] = 105; m[13] = 108; m[14] = 101; m[15] = 100; m[16] = 0;
}
/** Fill message buffer with out/ctx alloc failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_out_ctx_alloc).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_out_ctx_alloc(m: *u8): void {
  m[0] = 111; m[1] = 117; m[2] = 116; m[3] = 47; m[4] = 99; m[5] = 116;
  m[6] = 120; m[7] = 32; m[8] = 97; m[9] = 108; m[10] = 108; m[11] = 111;
  m[12] = 99; m[13] = 32; m[14] = 102; m[15] = 97; m[16] = 105; m[17] = 108;
  m[18] = 101; m[19] = 100; m[20] = 0;
}
/** Fill message buffer with dep prerun failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_dep_prerun).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_dep_prerun(m: *u8): void {
  m[0] = 100; m[1] = 101; m[2] = 112; m[3] = 32; m[4] = 112; m[5] = 114;
  m[6] = 101; m[7] = 114; m[8] = 117; m[9] = 110; m[10] = 32; m[11] = 102;
  m[12] = 97; m[13] = 105; m[14] = 108; m[15] = 101; m[16] = 100; m[17] = 0;
}
/** Fill message buffer with .x pipeline failed.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_pipe_failed).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_pipe_failed(m: *u8): void {
  m[0] = 46; m[1] = 120; m[2] = 32; m[3] = 112; m[4] = 105; m[5] = 112;
  m[6] = 101; m[7] = 108; m[8] = 105; m[9] = 110; m[10] = 101; m[11] = 32;
  m[12] = 102; m[13] = 97; m[14] = 105; m[15] = 108; m[16] = 101; m[17] = 100;
  m[18] = 0;
}
/** Fill message buffer with no functions.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_no_funcs).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_no_funcs(m: *u8): void {
  m[0] = 110; m[1] = 111; m[2] = 32; m[3] = 102; m[4] = 117; m[5] = 110;
  m[6] = 99; m[7] = 116; m[8] = 105; m[9] = 111; m[10] = 110; m[11] = 115;
  m[12] = 0;
}
/** Fill message buffer with cg buf empty.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_empty_buf).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_empty_buf(m: *u8): void {
  m[0] = 99; m[1] = 103; m[2] = 32; m[3] = 98; m[4] = 117; m[5] = 102;
  m[6] = 32; m[7] = 101; m[8] = 109; m[9] = 112; m[10] = 116; m[11] = 121;
  m[12] = 0;
}
/** Fill message buffer with expected literal.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_msg_expected_lit).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_msg_expected_lit(m: *u8): void {
  m[0] = 101; m[1] = 120; m[2] = 112; m[3] = 101; m[4] = 99; m[5] = 116;
  m[6] = 101; m[7] = 100; m[8] = 32; m[9] = 108; m[10] = 105; m[11] = 116;
  m[12] = 101; m[13] = 114; m[14] = 97; m[15] = 108; m[16] = 0;
}

/** Dispatch kind/code/msg fillers by selector ids, then diag_report_with_code. kind_fn/code_fn/msg_fn are integer selectors (not function pointers) for Cap residual. Uses work slots wp_kind/wp_code/wp_msg.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_diag).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_diag(path: *u8, kind_fn: i32, code_fn: i32, msg_fn: i32): void {
  let k: *u8 = 0 as *u8;
  let c: *u8 = 0 as *u8;
  let m: *u8 = 0 as *u8;
  unsafe {
    k = driver_x_emit_work_p_get(wp_kind());
    c = driver_x_emit_work_p_get(wp_code());
    m = driver_x_emit_work_p_get(wp_msg());
  }
  if (k == 0 as *u8) {
    return;
  }
  if (kind_fn == 1) { rt_xe_fill_kind_io(k); }
  if (kind_fn == 2) { rt_xe_fill_kind_pp(k); }
  if (kind_fn == 3) { rt_xe_fill_kind_pipe(k); }
  if (kind_fn == 4) { rt_xe_fill_kind_parse(k); }
  if (kind_fn == 5) { rt_xe_fill_kind_cg(k); }
  if (code_fn == 1) { rt_xe_fill_code_io001(c); }
  if (code_fn == 2) { rt_xe_fill_code_pp002(c); }
  if (code_fn == 3) { rt_xe_fill_code_xp003(c); }
  if (code_fn == 5) { rt_xe_fill_code_xp005(c); }
  if (code_fn == 6) { rt_xe_fill_code_xp006(c); }
  if (code_fn == 7) { rt_xe_fill_code_xp007(c); }
  if (code_fn == 8) { rt_xe_fill_code_xp008(c); }
  if (code_fn == 9) { rt_xe_fill_code_p001(c); }
  if (code_fn == 10) { rt_xe_fill_code_cg004(c); }
  if (msg_fn == 1) { rt_xe_msg_cannot_read(m); }
  if (msg_fn == 2) { rt_xe_msg_pp_failed(m); }
  if (msg_fn == 3) { rt_xe_msg_alloc_failed(m); }
  if (msg_fn == 4) { rt_xe_msg_src_too_large(m); }
  if (msg_fn == 5) { rt_xe_msg_parse_failed(m); }
  if (msg_fn == 6) { rt_xe_msg_dep_alloc(m); }
  if (msg_fn == 7) { rt_xe_msg_out_ctx_alloc(m); }
  if (msg_fn == 8) { rt_xe_msg_dep_prerun(m); }
  if (msg_fn == 9) { rt_xe_msg_pipe_failed(m); }
  if (msg_fn == 10) { rt_xe_msg_no_funcs(m); }
  if (msg_fn == 11) { rt_xe_msg_empty_buf(m); }
  if (msg_fn == 12) { rt_xe_msg_expected_lit(m); }
  unsafe {
    diag_report_with_code(path, 0, 0, k, c, m, 0 as *u8);
  }
}

/** Step: read source + preprocess into work slots. Returns 0 ok / 1 fail.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_step_read_pp).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_step_read_pp(): i32 {
  let path: *u8 = 0 as *u8;
  let raw: *u8 = 0 as *u8;
  let raw_len: usize = 0;
  let src: *u8 = 0 as *u8;
  let src_len: usize = 0;
  let rc: i32 = 0;
  unsafe {
    path = driver_x_emit_work_p_get(wp_path());
    raw = runtime_read_file_malloc(path, &raw_len);
  }
  if (raw == 0 as *u8) {
    rt_xe_diag(path, 1, 1, 1);
    return 1;
  }
  unsafe {
    pipeline_diag_emitted_reset();
    src = xlang_preprocess_with_path(raw, raw_len, path, 0 as *u8, 0, &src_len);
    free(raw);
  }
  if (src == 0 as *u8) {
    unsafe {
      rc = pipeline_diag_emitted_get();
    }
    if (rc == 0) {
      rt_xe_diag(path, 2, 2, 2);
    }
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_src(), src);
    driver_x_emit_work_z_set(wz_slen(), src_len);
    diag_set_file(path, src, src_len);
  }
  return 0;
}

/** Step: parse main module into arena/module work slots. Returns 0 ok / 1 fail.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_step_parse).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_step_parse(): i32 {
  let path: *u8 = 0 as *u8;
  let src: *u8 = 0 as *u8;
  let src_len: usize = 0;
  let arena: *u8 = 0 as *u8;
  let module: *u8 = 0 as *u8;
  let asz: usize = 0;
  let msz: usize = 0;
  let main_idx: i32 = -1;
  let pr_ok: i32 = 0;
  let rc: i32 = 0;
  let fail_tok: i32 = 0;
  unsafe {
    path = driver_x_emit_work_p_get(wp_path());
    src = driver_x_emit_work_p_get(wp_src());
    src_len = driver_x_emit_work_z_get(wz_slen());
    asz = pipeline_sizeof_arena();
    msz = pipeline_sizeof_module();
    arena = malloc(asz);
    module = malloc(msz);
  }
  if (arena == 0 as *u8) {
    rt_xe_diag(0 as *u8, 3, 5, 3);
    return 1;
  }
  if (module == 0 as *u8) {
    unsafe {
      free(arena);
    }
    rt_xe_diag(0 as *u8, 3, 5, 3);
    return 1;
  }
  if (src_len > (2147483647 as usize)) {
    unsafe {
      free(arena);
      free(module);
    }
    rt_xe_diag(path, 3, 7, 4);
    return 1;
  }
  unsafe {
    memset(arena, 0, asz);
    memset(module, 0, msz);
    parser_parse_into_init(module, arena);
    pr_ok = driver_parse_into_buf_rc(arena, module, src, src_len as i32, &main_idx);
  }
  if (pr_ok != 0) {
    unsafe {
      rc = runtime_report_precise_parse_failure_if_known(path, src, src_len);
    }
    if (rc != 0) {
      unsafe {
        free(arena);
        free(module);
      }
      return 1;
    }
    unsafe {
      free(arena);
      free(module);
    }
    rt_xe_diag(path, 4, 9, 5);
    return 1;
  }
  unsafe {
    parser_parse_into_set_main_index(module, main_idx);
    rc = driver_get_module_num_funcs(module);
  }
  if (rc <= 0) {
    unsafe {
      fail_tok = driver_parser_diag_fail_tok_kind(src, src_len);
    }
    if (fail_tok == 130) {
      unsafe {
        free(arena);
        free(module);
      }
      rt_xe_diag(path, 4, 9, 12);
      return 1;
    }
  }
  unsafe {
    driver_x_emit_work_p_set(wp_arena(), arena);
    driver_x_emit_work_p_set(wp_module(), module);
    driver_x_emit_work_z_set(wz_asz(), asz);
    driver_x_emit_work_z_set(wz_msz(), msz);
    driver_x_emit_work_i_set(wi_main(), main_idx);
    rc = parser_get_module_num_imports(module);
    driver_x_emit_work_i_set(wi_nimp(), rc);
  }
  return 0;
}

/** Step: load direct/transitive deps into work tables. Returns 0 ok / 1 fail.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_step_load_deps).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_step_load_deps(): i32 {
  let path: *u8 = 0 as *u8;
  let module: *u8 = 0 as *u8;
  let entry: *u8 = 0 as *u8;
  let lib: *u8 = 0 as *u8;
  let n_lib: i32 = 0;
  let n_imp: i32 = 0;
  let asm_d: i32 = 0;
  let ds: *u8 = 0 as *u8;
  let dp: *u8 = 0 as *u8;
  let dl: *u8 = 0 as *u8;
  let n_deps: i32 = 0;
  let cpaths: *u8 = 0 as *u8;
  let n_cl: i32 = 0;
  let asz: usize = 0;
  let msz: usize = 0;
  let da: *u8 = 0 as *u8;
  let dm: *u8 = 0 as *u8;
  let i: i32 = 0;
  let p: *u8 = 0 as *u8;
  let rc: i32 = 0;
  unsafe {
    path = driver_x_emit_work_p_get(wp_path());
    module = driver_x_emit_work_p_get(wp_module());
    n_imp = driver_x_emit_work_i_get(wi_nimp());
    asz = driver_x_emit_work_z_get(wz_asz());
    msz = driver_x_emit_work_z_get(wz_msz());
    entry = driver_entry_dir_slot();
    xlang_get_entry_dir(path, entry, 512 as usize);
    driver_x_emit_work_p_set(wp_entry(), entry);
  }
  if (n_imp > 0) {
    unsafe {
      pipeline_set_entry_dir(entry);
    }
  }
  unsafe {
    lib = driver_x_emit_effective_lib_roots(&n_lib);
    driver_x_emit_work_p_set(wp_lib(), lib);
    driver_x_emit_work_i_set(wi_nlib(), n_lib);
    asm_d = driver_x_emit_asm_direct_import_only(path);
    driver_x_emit_work_i_set(wi_asm(), asm_d);
    ds = driver_ptr_table_calloc(128);
    dp = driver_ptr_table_calloc(128);
    dl = driver_size_table_calloc(128);
  }
  if (ds == 0 as *u8) {
    return 1;
  }
  if (dp == 0 as *u8) {
    unsafe {
      driver_ptr_table_free(ds);
    }
    return 1;
  }
  if (dl == 0 as *u8) {
    unsafe {
      driver_ptr_table_free(ds);
      driver_ptr_table_free(dp);
    }
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_dsrc(), ds);
    driver_x_emit_work_p_set(wp_dpath(), dp);
    driver_x_emit_work_p_set(wp_dlens(), dl);
  }
  n_deps = 0;
  if (n_imp > 0) {
    if (n_imp <= 32) {
      if (asm_d != 0) {
        unsafe {
          rc = xlang_load_direct_imports_for_asm_layout(
            module, lib, n_lib, entry, 0 as *u8, 0, ds, dl, dp, &n_deps);
        }
        if (rc != 0) {
          return 1;
        }
      } else {
        unsafe {
          cpaths = driver_ptr_table_calloc(128);
        }
        if (cpaths == 0 as *u8) {
          return 1;
        }
        n_cl = 0;
        unsafe {
          rc = xlang_collect_dep_paths_transitive(
            module, asz, msz, lib, n_lib, entry, 0 as *u8, 0, cpaths, &n_cl);
        }
        if (rc != 0) {
          unsafe {
            driver_ptr_table_free(cpaths);
          }
          return 1;
        }
        unsafe {
          rc = xlang_merge_direct_then_transitive_dep_paths(
            module, n_imp, cpaths, n_cl, dp, &n_deps);
          driver_ptr_table_free(cpaths);
        }
        if (rc != 0) {
          return 1;
        }
      }
    }
  }
  unsafe {
    driver_x_emit_work_i_set(wi_ndeps(), n_deps);
    driver_typeck_ndep_set(0);
    da = driver_ptr_table_calloc(32);
    dm = driver_ptr_table_calloc(32);
  }
  if (da == 0 as *u8) {
    return 1;
  }
  if (dm == 0 as *u8) {
    unsafe {
      driver_ptr_table_free(da);
    }
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_dar(), da);
    driver_x_emit_work_p_set(wp_dmod(), dm);
  }
  i = 0;
  while (i < n_deps) {
    unsafe {
      p = malloc(asz);
      driver_ptr_table_set(da, i, p);
      p = malloc(msz);
      driver_ptr_table_set(dm, i, p);
    }
    unsafe {
      if (driver_ptr_table_get(da, i) == 0 as *u8) {
        rc = 1;
      } else {
        if (driver_ptr_table_get(dm, i) == 0 as *u8) {
          rc = 1;
        } else {
          rc = 0;
        }
      }
    }
    if (rc != 0) {
      rt_xe_diag(0 as *u8, 3, 5, 6);
      return 1;
    }
    unsafe {
      memset(driver_ptr_table_get(da, i), 0, asz);
      memset(driver_ptr_table_get(dm, i), 0, msz);
    }
    i = i + 1;
  }
  return 0;
}

/** Step: dep prerun (parse/typeck) + publish slots. Returns 0 ok / 1 fail.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_step_prerun).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_step_prerun(): i32 {
  let path: *u8 = 0 as *u8;
  let entry: *u8 = 0 as *u8;
  let lib: *u8 = 0 as *u8;
  let n_lib: i32 = 0;
  let n_deps: i32 = 0;
  let asm_d: i32 = 0;
  let da: *u8 = 0 as *u8;
  let dm: *u8 = 0 as *u8;
  let ds: *u8 = 0 as *u8;
  let dp: *u8 = 0 as *u8;
  let dl: *u8 = 0 as *u8;
  let out_buf: *u8 = 0 as *u8;
  let pctx: *u8 = 0 as *u8;
  let one: *u8 = 0 as *u8;
  let dep_out: *u8 = 0 as *u8;
  let dep_src: *u8 = 0 as *u8;
  let dep_len: usize = 0;
  let resolved: *u8 = 0 as *u8;
  let snap: *u8 = 0 as *u8;
  let dfile: *u8 = 0 as *u8;
  let j: i32 = 0;
  let p: *u8 = 0 as *u8;
  let rc: i32 = 0;
  let ec: i32 = 0;
  unsafe {
    path = driver_x_emit_work_p_get(wp_path());
    entry = driver_x_emit_work_p_get(wp_entry());
    lib = driver_x_emit_work_p_get(wp_lib());
    n_lib = driver_x_emit_work_i_get(wi_nlib());
    n_deps = driver_x_emit_work_i_get(wi_ndeps());
    asm_d = driver_x_emit_work_i_get(wi_asm());
    da = driver_x_emit_work_p_get(wp_dar());
    dm = driver_x_emit_work_p_get(wp_dmod());
    ds = driver_x_emit_work_p_get(wp_dsrc());
    dp = driver_x_emit_work_p_get(wp_dpath());
    dl = driver_x_emit_work_p_get(wp_dlens());
    out_buf = driver_codegen_outbuf_calloc();
    pctx = driver_pipeline_dep_ctx_calloc();
  }
  if (out_buf == 0 as *u8) {
    rt_xe_diag(0 as *u8, 3, 6, 7);
    return 1;
  }
  if (pctx == 0 as *u8) {
    unsafe {
      driver_codegen_outbuf_free(out_buf);
    }
    rt_xe_diag(0 as *u8, 3, 6, 7);
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_out(), out_buf);
    driver_x_emit_work_p_set(wp_pctx(), pctx);
    xlang_pipeline_fill_ctx_path_buffers(pctx, entry, lib, n_lib);
  }
  // 7.4.4 v3: opt-in -lib-name entry prefix (main_entry dispatch: -x -E →
  // parse_x ret 1 → this lane). Absent/empty → no-op → bare emission.
  {
    let ln_buf: u8[64] = [];
    let ln_len: i32 = xlang_driver_x_emit_lib_name_into(&ln_buf[0], 64);
    if (ln_len > 0) {
      unsafe {
        xlang_pipeline_pctx_set_entry_lib_prefix(pctx, &ln_buf[0], ln_len);
      }
    }
  }
  if (asm_d != 0) {
    unsafe {
      xlang_pipeline_pctx_seed_dep_import_paths_only(pctx, dp, n_deps);
    }
  } else {
    unsafe {
      xlang_pipeline_pctx_seed_dep_slots(pctx, dm, da, dp, n_deps);
    }
  }
  unsafe {
    driver_pipeline_dep_ctx_set_use_asm(pctx, 0);
    driver_dep_seeded_clear_all();
  }
  j = n_deps - 1;
  while (j >= 0) {
    unsafe {
      one = driver_pipeline_dep_ctx_calloc();
      dep_out = driver_codegen_outbuf_calloc();
    }
    if (one == 0 as *u8) {
      unsafe {
        driver_codegen_outbuf_free(dep_out);
      }
      rt_xe_diag(0 as *u8, 3, 6, 7);
      return 1;
    }
    if (dep_out == 0 as *u8) {
      unsafe {
        pipeline_dep_ctx_heap_destroy(one);
      }
      rt_xe_diag(0 as *u8, 3, 6, 7);
      return 1;
    }
    unsafe {
      p = xlang_dep_prerun_entry_dir(entry, lib, n_lib);
      xlang_pipeline_fill_ctx_path_buffers(one, p, lib, n_lib);
      resolved = driver_path_max_slot();
      resolved[0] = 0;
    }
    if (asm_d != 0) {
      unsafe {
        dep_src = driver_ptr_table_get(ds, j);
        dep_len = driver_size_table_get(dl, j);
      }
    } else {
      unsafe {
        p = driver_ptr_table_get(dp, j);
        xlang_resolve_import_file_path_multi(lib, n_lib, entry, p, resolved, 4096 as usize);
        dep_src = runtime_read_file_malloc(resolved, &dep_len);
      }
      if (dep_src == 0 as *u8) {
        unsafe {
          pipeline_diag_import_open_fail_once(p, resolved);
          pipeline_dep_ctx_heap_destroy(one);
          driver_codegen_outbuf_free(dep_out);
        }
        return 1;
      }
      /* preprocess: reuse dep_src buffer via xlang_preprocess — need raw free */
      unsafe {
        p = dep_src;
        dep_src = xlang_preprocess(p, dep_len, 0 as *u8, 0, &dep_len);
        free(p);
      }
      if (dep_src == 0 as *u8) {
        unsafe {
          pipeline_dep_ctx_heap_destroy(one);
          driver_codegen_outbuf_free(dep_out);
        }
        rt_xe_diag(resolved, 2, 2, 2);
        return 1;
      }
    }
    unsafe {
      xlang_pipeline_one_ctx_for_dep_prerun(one, j, dm, da, dp, n_deps, dep_src, dep_len);
      p = driver_ptr_table_get(dp, j);
      driver_set_current_dep_path_for_codegen(p);
      snap = driver_diag_snapshot_alloc();
    }
    dfile = p;
    if (asm_d == 0) {
      dfile = resolved;
    }
    unsafe {
      driver_diag_push_file(snap, dfile, dep_src, dep_len);
      rc = driver_x_emit_asm_dep_parse_skip_typeck_ok(path, p);
    }
    if (rc != 0) {
      unsafe {
        ec = xlang_pipeline_dep_prerun_parse_skip_typeck(
          driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j),
          dep_src, dep_len, dep_out, one);
      }
    } else {
      unsafe {
        rc = driver_x_emit_asm_dep_parse_only_ok(path, p);
      }
      if (asm_d != 0) {
        rc = 1;
      }
      if (rc != 0) {
        unsafe {
          ec = xlang_pipeline_dep_prerun_parse_only(
            driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j),
            dep_src, dep_len);
        }
      } else {
        unsafe {
          ec = xlang_pipeline_dep_prerun_typeck_only(
            driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j),
            dep_src, dep_len, dep_out, one);
        }
      }
    }
    unsafe {
      driver_diag_restore(snap);
      driver_diag_snapshot_free(snap);
      driver_set_current_dep_path_for_codegen(0 as *u8);
      pipeline_dep_ctx_heap_destroy(one);
      driver_codegen_outbuf_free(dep_out);
    }
    if (asm_d == 0) {
      unsafe {
        free(dep_src);
      }
    }
    if (ec != 0) {
      rt_xe_diag(dfile, 3, 8, 8);
      return 1;
    }
    unsafe {
      driver_dep_publish_slot(
        j, driver_ptr_table_get(da, j), driver_ptr_table_get(dm, j),
        driver_ptr_table_get(dp, j));
    }
    j = j - 1;
  }
  return 0;
}

/** Step: run x pipeline large-stack + write C to stdout. Returns 0 ok / 1 fail.
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_rt_xe_step_finish).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_xe_step_finish(): i32 {
  let path: *u8 = 0 as *u8;
  let src: *u8 = 0 as *u8;
  let src_len: usize = 0;
  let arena: *u8 = 0 as *u8;
  let module: *u8 = 0 as *u8;
  let asz: usize = 0;
  let msz: usize = 0;
  let n_deps: i32 = 0;
  let asm_d: i32 = 0;
  let da: *u8 = 0 as *u8;
  let dm: *u8 = 0 as *u8;
  let dp: *u8 = 0 as *u8;
  let out_buf: *u8 = 0 as *u8;
  let pctx: *u8 = 0 as *u8;
  let j: i32 = 0;
  let ec: i32 = 0;
  let out_len: i32 = 0;
  let out_data: *u8 = 0 as *u8;
  let rc: i32 = 0;
  unsafe {
    path = driver_x_emit_work_p_get(wp_path());
    src = driver_x_emit_work_p_get(wp_src());
    src_len = driver_x_emit_work_z_get(wz_slen());
    arena = driver_x_emit_work_p_get(wp_arena());
    module = driver_x_emit_work_p_get(wp_module());
    asz = driver_x_emit_work_z_get(wz_asz());
    msz = driver_x_emit_work_z_get(wz_msz());
    n_deps = driver_x_emit_work_i_get(wi_ndeps());
    asm_d = driver_x_emit_work_i_get(wi_asm());
    da = driver_x_emit_work_p_get(wp_dar());
    dm = driver_x_emit_work_p_get(wp_dmod());
    dp = driver_x_emit_work_p_get(wp_dpath());
    out_buf = driver_x_emit_work_p_get(wp_out());
    pctx = driver_x_emit_work_p_get(wp_pctx());
  }
  if (asm_d != 0) {
    unsafe {
      driver_typeck_ndep_set(0);
      pipeline_set_dep_slots(da, dm);
      driver_dep_seed_slots(0 as *u8, 0 as *u8, 0);
      codegen_set_dep_slots_for_x_pipeline(0 as *u8, 0 as *u8, 0);
    }
  } else {
    unsafe {
      driver_typeck_ndep_set(n_deps);
    }
    j = 0;
    while (j < n_deps) {
      unsafe {
        driver_typeck_dep_ptrs_set(
          j, driver_ptr_table_get(dm, j), driver_ptr_table_get(da, j));
      }
      j = j + 1;
    }
    unsafe {
      pipeline_set_dep_slots(da, dm);
      driver_dep_seed_slots(da, dm, n_deps);
      codegen_set_dep_slots_for_x_pipeline(dm, dp, n_deps);
      pipeline_set_dep_slots(da, dm);
    }
  }
  unsafe {
    memset(arena, 0, asz);
    memset(module, 0, msz);
    ec = xlang_pipeline_run_x_pipeline_large_stack(
      module, arena, src, src_len, out_buf, pctx);
    out_len = driver_codegen_outbuf_len(out_buf);
    out_data = driver_codegen_outbuf_data(out_buf);
  }
  if (ec == 0) {
    if (out_len > 0) {
      /* Emit smoke summary (parse OK / typeck OK) before C body so run-typeck.sh
       * gate grep finds the marker on the -E path. Mirrors driver/emit.x:413
       * and rt_run_compiler_parsed.x:1251. PLATFORM: SHARED. */
      unsafe {
        driver_print_x_smoke_summary(module, out_len as usize);
      }
      unsafe {
        driver_x_emit_fwrite_stdout(out_data, out_len);
      }
      return 0;
    }
    unsafe {
      rc = driver_get_module_num_funcs(module);
    }
    if (rc <= 0) {
      unsafe {
        rc = runtime_report_precise_parse_failure_if_known(path, src, src_len);
      }
      if (rc == 0) {
        rt_xe_diag(path, 4, 9, 10);
      }
      return 1;
    }
    rt_xe_diag(path, 5, 10, 11);
    return 1;
  }
  rt_xe_diag(path, 3, 3, 9);
  return 1;
}

/** Public entry: run -x -E emit pipeline via work slots and five steps. Resets work, seeds path/lib, then read_pp, parse, load_deps, prerun, finish.
 * Leftover !XLANG_NO_C_FRONTEND -E-extern cparser call lived only in the
 * cold seed twin (rt_run_x_emit.from_x.c). This product body always
 * refuses -E-extern via driver_x_emit_try_extern_via_cparser (BLD001).
 * @return i32 — 0 on success, 1 on failure or -E-extern refuse
 * Track-L: #[no_mangle] keeps surface short name (not rt_run_x_emit_driver_run_x_emit_c).
 * PLATFORM: SHARED — product authority; leftover consume site retired in
 * the cold seed twin (this knife). Mega via_cparser wrapper not deleted.
 */
#[no_mangle]
export function driver_run_x_emit_c(): i32 {
  let path: *u8 = 0 as *u8;
  let want: i32 = 0;
  let k: *u8 = 0 as *u8;
  let c: *u8 = 0 as *u8;
  let m: *u8 = 0 as *u8;
  let rc: i32 = 0;
  let old_legacy: i32 = 0;
  /* LANG-007: -E path must set allow_legacy_extern (same intent as mega runtime). */
  unsafe {
    old_legacy = typeck_set_allow_legacy_extern_calls(1);
    driver_x_emit_work_reset();
    path = driver_x_emit_take_c_path();
  }
  if (path == 0 as *u8) {
    unsafe {
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_path(), path);
    driver_x_emit_stdout_set_unbuffered();
    want = driver_x_emit_take_want_extern();
  }
  if (want != 0) {
    // Always refuse -E-extern. Do not re-add driver_run_x_emit_c_extern_via_cparser.
    unsafe {
      rc = driver_x_emit_try_extern_via_cparser(path);
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return rc;
  }
  unsafe {
    k = malloc(32 as usize);
    c = malloc(16 as usize);
    m = malloc(64 as usize);
  }
  if (k == 0 as *u8) {
    unsafe {
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  if (c == 0 as *u8) {
    unsafe {
      free(k);
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  if (m == 0 as *u8) {
    unsafe {
      free(k);
      free(c);
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    driver_x_emit_work_p_set(wp_kind(), k);
    driver_x_emit_work_p_set(wp_code(), c);
    driver_x_emit_work_p_set(wp_msg(), m);
  }
  unsafe {
    rc = rt_xe_step_read_pp();
  }
  if (rc != 0) {
    unsafe {
      driver_x_emit_work_cleanup();
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    rc = rt_xe_step_parse();
  }
  if (rc != 0) {
    unsafe {
      driver_x_emit_work_cleanup();
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    rc = rt_xe_step_load_deps();
  }
  if (rc != 0) {
    unsafe {
      driver_x_emit_work_cleanup();
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    rc = rt_xe_step_prerun();
  }
  if (rc != 0) {
    unsafe {
      driver_x_emit_work_cleanup();
      typeck_set_allow_legacy_extern_calls(old_legacy);
    }
    return 1;
  }
  unsafe {
    rc = rt_xe_step_finish();
    driver_x_emit_work_cleanup();
    typeck_set_allow_legacy_extern_calls(old_legacy);
  }
  return rc;
}
