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
//     freestanding / sanitize / fmt_check_only / skip_typeck / skip_codegen / skip_dep0 /
// See implementation.
// See implementation.
// See implementation.
//   + wave3 Cap residual pure：format print（check_ok / fail rc·path / smoke parse·typeck）
// See implementation.
//     print/fail format _impl。
//   + wave4 Cap residual pure：defines_set_at（G.7 xlang_ptr_slot_set）+ os_define_lit
// See implementation.
//   + wave5 Cap residual pure：phase timing BSS + begin/end（f64 acc/start + active i32）
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
//     xlang_driver_path_read_preprocess_malloc（no file-view/preprocess in .x）；
// See implementation.
// See implementation.
//     xlang_driver_run_thread_on_large_stack_pthread（no pthread_attr/posix_memalign in .x）；
// See implementation.
// See implementation.
//     （XLANG_DEBUG_PIPE truthy → append_* + diag_report；no va_list reportf）；
// See implementation.
// Cap residual pure leaf closed for driver_abi debug_pipe note（OS rest _impl already 0）。
//   + wave14 Cap residual pure：rt_asm_stub GAS line table + out_append_cstr
//     (host OutBuf layout: data[9MiB] then i32 len; LE load/store local to this TU).
//   + wave15 Cap residual pure：rt_entry buffer slots + path_max/entry_dir slots
//     (BSS u8[N]; fmt_argv closed in wave21).
//   + wave16 Cap residual pure：driver_x_emit work BSS + get/set/reset/cleanup
//     (p: G.7 xlang_ptr_slot_* on LP64 raw u8[208]; i32[17]/usize[5]; free+dep_ctx destroy).
//   + wave17 Cap residual pure：driver_asm_work BSS + get/set/reset/cleanup
//     (p: raw u8[200] 25×ptr; i32[16]/usize[4]; free+dep_ctx+fclose asm_out; clear tmp_path[0]).
//   + wave18 Cap residual pure：driver_parsed_work BSS + get/set/reset/cleanup
//     (p: raw u8[192] 24×ptr; i32[14]/usize[4]; free+dep_ctx+fclose cf; unlink tmp_c; clear tmp slots).
//   + wave19 Cap residual pure：driver_pipeline_dep_ctx field get/set (LP64 fixed offsets
//     + wave14 LE load/store; no C struct in .x).
//   + wave20 Cap residual pure：driver_preamble_{io_net,fs_path}_line_at/count
//     (G.7 xlang_ptr_slot_get on Cap-giant-string table raw base; tables stay in rt_preamble).
//   + wave21 Cap residual pure：driver_entry_fmt_argv_slot
//     (u8 lit BSS "xlang"/"fmt" + 2× LP64 ptr slots via G.7 xlang_ptr_slot_set; no *u8[2] lit).
//   + wave22 Cap residual pure：driver_preamble_fputs
//     (null guard + g05 prologue xlang_driver_fputs_opaque FILE* cast; no FILE* in .x).
//   + wave23 Cap residual pure：calloc family + driver_asm_pctx_apply_host_defaults
//     (libc calloc/malloc/memset + pipeline_sizeof_*; host #ifdef → OS residual helpers).
//   + wave24 Cap residual pure：outbuf free/len/data + ptr/size table free/get/set
//     + diag_snapshot_free (pairs wave23 calloc; G.7 xlang_ptr_slot_* + LE usize; free).
//   + wave25 Cap residual pure：tmp path BSS slots (asm 64B + parsed 64B/256B)
//     (open_out seed always uses accessors; no dual BSS under hybrid).
//   + wave26 Cap residual pure：driver_parsed_fclose / fclose_rc / write_out
//     (g05 stdout_ptr + fclose/fwrite opaque; min preamble via fputs; io_net/fs_path seed).
//   + wave27 Cap residual pure：driver_parsed_open_out_file
//     (stdout gate pure; mkstemp/rename/close + g05 fopen_write; seed tmp_prefix residual).
//   + wave28 Cap residual pure：driver_parsed_invoke_cc
//     (std .o path pack + set/clear user .o + xlang_invoke_cc + fail/KEEP_C cleanup;
//      no va_list reportf; c_paths[1] via G.7 xlang_ptr_slot_set).
//   + wave31 Cap residual pure：driver_parsed_deps_has_std_io_{core,driver}
//     + apply_preamble_skip + maybe_dump_prep
//     (G.7 xlang_ptr_slot_get on dep_paths; strcmp lit; codegen skip mask bits;
//      dump via xlang_write_path_bytes + fixed-arity diag, no va_list reportf).
//   + wave32 Cap residual pure：driver_parsed field accessors + try_c_after_pp
//     (LP64 fixed offsetof on DriverCompileParsedAbi + LE i32 / G.7 ptr load;
//      lib_roots = base+16 embedded array; opt default BSS lit "2";
//      try_c_after_pp product NO_C stub returns -2).
//   + wave33 Cap residual pure：driver_x_emit clear/bind/take/get/lib_root_at/
//     effective_lib_roots + try_extern_via_cparser
//     (G.7 xlang_ptr_slot_* on always-seed c_path_cell / lib_roots_raw / path+lib slots).
//   + wave34 Cap residual pure：driver_asm try_c stubs + use_compiler_impl_c +
//     bind_lib_roots + argv0 + collect_defines/defines_as_u8/ndefines_get
//     (product NO_C fixed -2/-1/0; one_root BSS + G.7; defines table BSS 64×LP64 +
//      pure driver_argv_collect_defines; no FILE*/fopen residual).
//   + wave35 Cap residual pure：driver_typeck_ndep_set / dep_ptrs_set +
//     driver_diag_push_file / restore + driver_dispatch_lib_root_at / opt_default
//     (G.7 typeck_ndep_store + dep_module/arena_set; diag_push_file/restore;
//      G.7 xlang_ptr_slot_get on roots; opt default reuses wave32 BSS lit "2").
//   + wave36 Cap residual pure：driver_dispatch_lib_roots_from_key +
//     driver_dispatch_run_compiler_parsed
//     (BSS 16×512 bufs + 16×LP64 root slots; G.7 driver_lib_roots_from_key;
//      BSS pack DriverCompileParsedAbi 176B LP64 + driver_run_compiler_parsed;
//      opt default reuses wave32 lit "2").
//   + wave37 Cap residual pure：driver_arena/module_static_{slot,size} +
//     driver_run_stack_esc_gate_on_large_stack + driver_parser_diag_fail_tok_kind
//     (Cap-global BSS base residual; Cap-fn-ptr residual; BSS pack xlang_slice_uint8_t
//      + parser_diag_fail_at_token_kind; fixed 128MiB/2MiB sizes).
//   + wave38 Cap residual pure：driver_asm_elf_ctx_free + driver_parse_into_buf_rc
//     (free pairs wave23 elf_ctx_calloc; Cap-struct-return residual
//      xlang_parser_parse_into_buf_rc hides parser_ParseIntoResult from .x).
//   + wave39 Cap residual pure：driver_stdio_stdout + driver_asm_fwrite +
//     driver_x_emit_fwrite_stdout
//     (g05 stdout_ptr + fwrite_opaque; Cap OS residual xlang_driver_fwrite_stdout_n
//      for count+fflush ABI; FILE* cast stays harness / seed).
//   + wave40 Cap residual pure：driver_stdio_stderr + driver_asm_fflush_stdout +
//     driver_asm_fopen_wb + driver_asm_write_metric_o
//     (g05 stderr_ptr / fflush_stdout / fopen_wb_opaque; write_metric pure orch:
//      fopen_wb + fwrite one 0 byte + fclose_opaque).
//   + wave41 Cap residual pure：driver_asm_mkstemp_fdopen
//     (null + WINDOWS gate residual; template pure via tmp_prefix + "xlang_asm_XXXXXX";
//      mkstemp/close/unlink libc; g05 fdopen_wb_opaque).
//   + wave42 Cap residual pure：driver_exec_compiled_body
//     (null/argc + G.7 path_is_non_exe pure; Cap residual scan opaque cast + spawn_wait).
//   + wave43 Cap residual pure：driver_dispatch_sibling_try_spawn
//     (null/argc + G.7 driver_argv0_basename_is pure; path pure BSS 512;
//      Cap residual argv0 get + access/spawn OS residual).
//   + wave44 Cap residual pure：driver_print_usage_write
//     (color policy pure: NO_COLOR nonnull / FORCE truthy / isatty;
//      Cap residual xlang_driver_usage_write_stdout holds giant plain/color lit +
//      via xlang_io_write(1, ...) Cap io face; .x cannot host multi-line \\n lits).
//

/* wave228 G.7: env lookup via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl. */
export extern "C" function link_abi_getenv(name: *u8): *u8;
/** POSIX isatty(fd): non-zero if fd is a terminal. Color policy default path.
 * PLATFORM: SHARED prototype (POSIX isatty / CRT _isatty on Windows via libc). */
export extern "C" function isatty(fd: i32): i32;
/** libc string compare for fixed dep import-path lits (std.io.core / std.io.driver).
 * PLATFORM: SHARED — string.h prototype; product -E skips conflicting redecl. */
export extern "C" function strcmp(a: *u8, b: *u8): i32;
/** Codegen preamble skip mask authority (codegen.x / seed). Wave31 pure applies bits. */
export extern "C" function codegen_reset_preamble_skip_mask(): void;
/** OR bits into preamble skip mask. Bits: 1=CORE_MACROS, 2=DRIVER_HANDLE, 4=UNDEF_REDEFINE, 8=WEAK_IO_BATCH. */
export extern "C" function codegen_or_preamble_skip_mask(mask: i32): void;
/** Permanent IO residual: write bytes to path (runtime_io_abi). 0 = success. */
export extern "C" function xlang_write_path_bytes(path: *u8, data: *u8, len: i64): i32;
/** Pipeline authority: store typeck_ndep (G.7; used by wave35 driver_typeck_ndep_set). */
export extern "C" function typeck_ndep_store(n: i32): void;
/** Pipeline authority: typeck_dep_module_ptrs[i] = mod (G.7; wave35 dep_ptrs_set). */
export extern "C" function typeck_dep_module_set(i: i32, mod: *u8): void;
/** Pipeline authority: typeck_dep_arena_ptrs[i] = arena (G.7; wave35 dep_ptrs_set). */
export extern "C" function typeck_dep_arena_set(i: i32, arena: *u8): void;
/** Diag authority: push file context into snapshot + apply (diag_thin / seed). */
export extern "C" function diag_push_file(
  snapshot: *u8, path: *u8, source: *u8, source_len: i64
): void;
/** Diag authority: restore DiagContextSnapshot (diag_thin / seed). */
export extern "C" function diag_restore(snapshot: *u8): void;
/** Lib-root expand authority (rt_lib_root / seed). Fills out_arr + contiguous 16×512 bufs. */
export extern "C" function driver_lib_roots_from_key(lib_key: *u8, out_arr: *u8, bufs: *u8): i32;
/** Parsed compile authority (rt_run_compiler_parsed / seed). p = DriverCompileParsedAbi*. */
export extern "C" function driver_run_compiler_parsed(p: *u8, argc: i32, argv: *u8): i32;
/** Permanent OS wall-clock surface (seed rest). Returns seconds as f64.
 * PLATFORM: POSIX gettimeofday / WINDOWS time — hides timeval layout from .x. */
export extern "C" function xlang_driver_wall_clock_sec(): f64;
/** Permanent OS indirect call surface (seed rest). Invokes fn(arg) when fn != null.
 * PLATFORM: SHARED — .x cannot safely perform indirect function calls; hide cast in rest. */
export extern "C" function xlang_driver_call_fn_void_arg(fn: *u8, arg: *u8): void;
/** Permanent OS RLIMIT_STACK raise surface (seed rest).
 * PLATFORM: POSIX getrlimit/setrlimit; WINDOWS no-op — hides struct rlimit from .x. */
export extern "C" function xlang_driver_bump_stack_limit(want_bytes: i64): void;
/** Permanent OS path-read + preprocess surface (seed rest).
 * PLATFORM: SHARED — runtime file view + xlang_preprocess; hides IO/preprocess ABI from .x. */
export extern "C" function xlang_driver_path_read_preprocess_malloc(path: *u8): *u8;
/** Permanent OS large-stack pthread create/join surface (seed rest).
 * PLATFORM: POSIX pthread_attr / posix_memalign / pthread_create+join; hides OS layouts from .x.
 * Default stack 256MiB; XLANG_STACK_LIMIT_MB (64..8192) overrides. Falls back to current-stack path. */
export extern "C" function xlang_driver_run_thread_on_large_stack_pthread(fn: *u8, arg: *u8): void;
// Wave3 format print pure: reuse diagnostic append authority (G.7) + fixed-arity diag report.
export extern "C" function diag_report(file: *u8, line: i32, col: i32, kind: *u8, msg: *u8, detail: *u8): void;
export extern "C" function diag_report_with_code(file: *u8, line: i32, col: i32, kind: *u8, code: *u8, msg: *u8, detail: *u8): void;
export extern "C" function driver_diag_append_cstr(dst: *u8, cap: i32, at: i32, src: *u8): i32;
export extern "C" function driver_diag_append_i32(dst: *u8, cap: i32, at: i32, val: i32): i32;
// Wave4/16: G.7 reuse pipeline pointer-slot authority (defines / work_p raw / void** tables).
export extern "C" function xlang_ptr_slot_set(arr: *u8, i: i32, p: *u8): void;
export extern "C" function xlang_ptr_slot_get(arr: *u8, i: i32): *u8;
/** Destroy heap PipelineDepCtx (ast_pool authority). Used by work cleanup pure.
 * PLATFORM: SHARED — rest/cold free path; null-safe in C body. */
export extern "C" function pipeline_dep_ctx_heap_destroy(ctx: *u8): void;
/** Seed rest: fclose asm FILE* (stdout → fflush only). Used by asm_work cleanup pure.
 * PLATFORM: SHARED — wraps driver_asm_fclose_asm_out; null-safe in C body. */
export extern "C" function driver_asm_fclose(fp: *u8): void;
/* wave26: driver_parsed_fclose is pure in this TU (no seed extern under hybrid). */
/** Always-seed Cap-giant-string data residual: address of driver_preamble_io_net_lines[]
 * (pointer table in seeds/rt_preamble.from_x.c). Pure line_at indexes via xlang_ptr_slot_get.
 * PLATFORM: SHARED — table text stays C; only base address is seed surface. */
export extern "C" function driver_preamble_io_net_lines_raw(): *u8;
/** Always-seed Cap-giant-string data residual: address of driver_preamble_fs_path_lines[].
 * PLATFORM: SHARED — same pattern as io_net_lines_raw. */
export extern "C" function driver_preamble_fs_path_lines_raw(): *u8;
/** Always-seed Cap-global-bss data residual: address of driver_arena_static[] (rt_arena_buf TU).
 * Wave37 pure slot/size wraps this; pure does not own the 128MiB array body.
 * PLATFORM: SHARED — base address only. */
export extern "C" function driver_arena_static_base(): *u8;
/** Always-seed Cap-global-bss data residual: address of driver_module_static[] (2MiB).
 * PLATFORM: SHARED — base address only. */
export extern "C" function driver_module_static_base(): *u8;
/** Always-seed Cap-fn-ptr residual: opaque address of driver_stack_esc_gate_thread_fn.
 * Wave37 pure orch binds this then calls driver_run_thread_on_large_stack.
 * PLATFORM: SHARED — .x cannot form function-pointer constants. */
export extern "C" function driver_stack_esc_gate_thread_fn_ptr(): *u8;
/** Cap-struct-return residual: call parser_parse_into_buf and unpack ok/main_idx.
 * Wave38 pure driver_parse_into_buf_rc owns null guards then calls this.
 * PLATFORM: SHARED — .x cannot safely consume C struct returns; hide in seed rest. */
export extern "C" function xlang_parser_parse_into_buf_rc(
  arena: *u8, module: *u8, data: *u8, len: i32, out_main_idx: *i32
): i32;
/** Parser authority: fail token kind from xlang_slice_uint8_t* source (LP64 pack).
 * Wave37 pure packs data+length into BSS slice then calls this.
 * PLATFORM: SHARED — G.7 single authority parser_diag_fail_at_token_kind. */
export extern "C" function parser_diag_fail_at_token_kind(source: *u8): i32;
/** POSIX unlink for tmp .c paths held in parsed work slots.
 * PLATFORM: POSIX (Linux/macOS product path); Windows uses same surface via seed pin. */
export extern "C" function unlink(path: *u8): i32;

// ---- Wave1 Cap residual pure: driver flag-slot BSS (PLATFORM: SHARED) ----
// Authority lives in this thin TU under PREFER hybrid; cold seed keeps C static BSS.
// Use i32[1] so &g[0] is a stable *i32 (scalar let address form is less portable in -E).
// nostdlib: plain BSS (not TLS) — see seed comment on large_stack_thread flag.
let g_driver_check_only_flag: i32[1] = [0];
let g_driver_check_diag_emitted_flag: i32[1] = [0];
let g_driver_freestanding_flag: i32[1] = [0];
let g_driver_sanitize_address_flag: i32[1] = [0];
let g_driver_fmt_check_only_flag: i32[1] = [0];
let g_driver_x_pipeline_skip_typeck_flag: i32[1] = [0];
let g_driver_x_pipeline_skip_codegen_flag: i32[1] = [0];
let g_driver_skip_codegen_dep_0_flag: i32[1] = [0];
let g_driver_on_large_stack_thread_flag: i32[1] = [0];

// ---- Wave2 Cap residual pure: path/len BSS (PLATFORM: SHARED) ----
// dep path: owned 128-byte BSS copy. Callers historically passed stack `dst`
// (pipeline_prepare_dep_codegen_path_c) and only stored the pointer; after
// that frame returned, glue_asm_build_dep_export_sym_c prefixed entry `main`
// with dangling bytes (Ubuntu hello.o `af 02 _main` / undefined main).
// entry_source_len / path_last_preprocess_len: i64[1] so store/load use [0] without &scalar.
// Rest path_read_impl writes preprocess len via driver_path_last_preprocess_len_store.
// Wave13 pure: load_and_maybe_debug emits XLANG_DEBUG_PIPE note via append + diag_report.
let g_driver_current_dep_path_buf: u8[128] = [];
let g_driver_current_dep_path: *u8 = 0 as *u8;
let g_pipeline_entry_source_len: i64[1] = [0];
let g_driver_path_last_preprocess_len: i64[1] = [0];

// ---- Wave5 Cap residual pure: compile phase timing BSS (PLATFORM: SHARED) ----
// phase 0=parse 1=typeck 2=codegen. Hybrid thin owns acc_ms/start_sec/active cells;
// cold seed keeps C static BSS. flush Cap (diag_reportf floats) reads via
// driver_compile_phase_acc_ms_get + driver_compile_phase_timing_clear.
let g_compile_phase_acc_ms: f64[3] = [0.0, 0.0, 0.0];
let g_compile_phase_start_sec: f64[3] = [0.0, 0.0, 0.0];
let g_compile_phase_active: i32[3] = [0, 0, 0];

// See implementation.
// See implementation.
// driver_env_flag_truthy: G.7 single env truthiness for XLANG_* gates / color force.
/**
 * Truthiness for a process env flag name (G.7 single path for driver env gates).
 * True when the value is non-null, non-empty, and not ASCII '0'.
 * @param name *u8 — NUL-terminated env var name; null/empty rejected as false
 * @return i32 — 1 truthy, 0 falsy
 * wave228 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED orch; host residual only link_abi_getenv_impl.
 */
function driver_env_flag_truthy(name: *u8): i32 {
  unsafe {
    let e: *u8 = link_abi_getenv(name);
    if (e == 0 as *u8) {
      return 0;
    }
    if (e[0] == 0) {
      return 0;
    }
    if (e[0] == 48) {
      return 0;
    }
    return 1;
  }
  return 0;
}

// driver_env_nonnull: presence-only env gate (compile phase timing, NO_COLOR, …).
/**
 * Whether a process env name is set (non-null pointer from env lookup).
 * @param name *u8 — NUL-terminated env var name
 * @return i32 — 1 if set (pointer non-null), 0 if unset
 * wave228 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED orch; host residual only link_abi_getenv_impl.
 */
function driver_env_nonnull(name: *u8): i32 {
  unsafe {
    let e: *u8 = link_abi_getenv(name);
    if (e == 0 as *u8) {
      return 0;
    }
    return 1;
  }
  return 0;
}

// driver_parse_u32_cstr: see function docblock below.
/** Internal function `driver_parse_u32_cstr`.
 * Implements `driver_parse_u32_cstr`.
 * @param s *u8
 * @return i64
 */
function driver_parse_u32_cstr(s: *u8): i64 {
  if (s == 0 as *u8) {
    return 0 - 1;
  }
  if (s[0] == 0) {
    return 0 - 1;
  }
  let n: i64 = 0;
  let i: i32 = 0;
  while (i < 20) {
    if (s[i] == 0) {
      break;
    }
    let c: i32 = s[i] as i32;
    if (c < 48) {
      return 0 - 1;
    }
    if (c > 57) {
      return 0 - 1;
    }
    n = n * 10 + (c - 48) as i64;
    i = i + 1;
  }
  if (i == 0) {
    return 0 - 1;
  }
  return n;
}

// See implementation.
// See implementation.
export extern "C" function driver_check_quiet_ok_get(): i32;

export extern "C" function driver_argv_at(argv: *u8, i: i32): *u8;
export extern "C" function xlang_cstr_offset(s: *u8, off: i32): *u8;
/** Permanent OS uname host-define surface (seed rest).
 * PLATFORM: POSIX uname(struct utsname) — hides utsname layout from .x; appends XLANG_OS_*/XLANG_ARCH_*. */
export extern "C" function xlang_driver_argv_append_uname(defines: *u8, ndefines: i32, max_defines: i32): i32;
export extern "C" function driver_get_module_num_funcs(m: *u8): i32;
export extern "C" function driver_get_module_main_func_index(m: *u8): i32;
export extern "C" function xlang_read_file_into_path(path: *u8, buf: *u8, cap: i64): i32;
export extern "C" function free(p: *u8): void;
/** Free ArenaSidecar GrowVecs for arena before free(arena).
 * PLATFORM: SHARED — required for batch xlang check (see driver_parsed_work_cleanup). */
export extern "C" function ast_pool_arena_release(a: *u8): void;
/** Free ModuleSidecar GrowVecs for module before free(module). PLATFORM: SHARED. */
export extern "C" function ast_pool_module_release(m: *u8): void;
export extern "C" function bootstrap_nostdlib_pthread_is_stub(): i32;

// pure: return address of module BSS flag cell (cold seed keeps C static + flag_slot).
/** Exported function `driver_check_only_flag_slot`.
 * Implements `driver_check_only_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_check_only_flag_slot(): *i32 {
  return &g_driver_check_only_flag[0];
}

/** Exported function `driver_check_diag_emitted_flag_slot`.
 * Implements `driver_check_diag_emitted_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_check_diag_emitted_flag_slot(): *i32 {
  return &g_driver_check_diag_emitted_flag[0];
}

/** Exported function `driver_freestanding_flag_slot`.
 * Memory management helper `driver_freestanding_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_freestanding_flag_slot(): *i32 {
  return &g_driver_freestanding_flag[0];
}

/** Exported function `driver_sanitize_address_flag_slot`.
 * Implements `driver_sanitize_address_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_sanitize_address_flag_slot(): *i32 {
  return &g_driver_sanitize_address_flag[0];
}

/** Exported function `driver_fmt_check_only_flag_slot`.
 * Implements `driver_fmt_check_only_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_fmt_check_only_flag_slot(): *i32 {
  return &g_driver_fmt_check_only_flag[0];
}

/** Exported function `driver_x_pipeline_skip_typeck_flag_slot`.
 * Implements `driver_x_pipeline_skip_typeck_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_x_pipeline_skip_typeck_flag_slot(): *i32 {
  return &g_driver_x_pipeline_skip_typeck_flag[0];
}

/** Exported function `driver_x_pipeline_skip_codegen_flag_slot`.
 * Implements `driver_x_pipeline_skip_codegen_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_x_pipeline_skip_codegen_flag_slot(): *i32 {
  return &g_driver_x_pipeline_skip_codegen_flag[0];
}

/** Exported function `driver_skip_codegen_dep_0_flag_slot`.
 * Implements `driver_skip_codegen_dep_0_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_skip_codegen_dep_0_flag_slot(): *i32 {
  return &g_driver_skip_codegen_dep_0_flag[0];
}

/** Exported function `driver_large_stack_thread_flag_slot`.
 * Read path helper `driver_large_stack_thread_flag_slot`.
 * @return *i32
 */
#[no_mangle]
export function driver_large_stack_thread_flag_slot(): *i32 {
  return &g_driver_on_large_stack_thread_flag[0];
}

/**
 * Store the current codegen dep import path into owned BSS (copy, not alias).
 * Null or empty path clears the slot so entry-module emit uses no C prefix.
 * @param path *u8 — NUL-terminated import path; null/empty clears
 * @return void
 * PLATFORM: SHARED — hybrid pure authority; cold seed store_impl must copy too.
 */
#[no_mangle]
export function driver_current_dep_path_store(path: *u8): void {
  if (path == 0 as *u8) {
    g_driver_current_dep_path_buf[0] = 0;
    g_driver_current_dep_path = 0 as *u8;
    return;
  }
  unsafe {
    if (path[0] == 0) {
      g_driver_current_dep_path_buf[0] = 0;
      g_driver_current_dep_path = 0 as *u8;
      return;
    }
    let i: i32 = 0;
    while (i < 127) {
      let c: u8 = path[i];
      g_driver_current_dep_path_buf[i] = c;
      if (c == 0) {
        break;
      }
      i = i + 1;
    }
    g_driver_current_dep_path_buf[127] = 0;
  }
  g_driver_current_dep_path = &g_driver_current_dep_path_buf[0];
}

/**
 * Load the current codegen dep path.
 * Always returns the owned BSS buffer (empty ⇒ buf[0]==0). Do not return the
 * pointer cell: host-C -E of `return g_driver_current_dep_path` on Ubuntu
 * loaded an uninitialized stack slot (hello.o `af 02 _main`).
 * @return *u8 — BSS path; first byte 0 means no prefix
 * PLATFORM: SHARED — hybrid pure authority.
 */
#[no_mangle]
export function driver_current_dep_path_load(): *u8 {
  return &g_driver_current_dep_path_buf[0];
}

/** Store pipeline entry source byte length into thin BSS.
 * Parameters: len — preprocess-or-entry source size in bytes (saturated by callers if needed).
 * PLATFORM: SHARED — hybrid pure authority. */
#[no_mangle]
export function driver_pipeline_entry_source_len_store(len: i64): void {
  g_pipeline_entry_source_len[0] = len;
}

/** Store last path_read_preprocess result length into thin BSS.
 * Called by rest path_read_impl after preprocess (and reset to 0 on entry/fail paths).
 * PLATFORM: SHARED — hybrid pure authority; cold seed keeps C static + store. */
#[no_mangle]
export function driver_path_last_preprocess_len_store(len: i64): void {
  g_driver_path_last_preprocess_len[0] = len;
}

/** Return last path_read_preprocess length from thin BSS.
 * PLATFORM: SHARED — hybrid pure authority. */
#[no_mangle]
export function driver_path_last_preprocess_len(): i64 {
  return g_driver_path_last_preprocess_len[0];
}

/** Pure orch: path-read + preprocess via permanent OS surface.
 * Wave11 pure: forwards to xlang_driver_path_read_preprocess_malloc (no path_read _impl residual).
 * PLATFORM: SHARED pure orch; file view + preprocess stay in seed rest. */
#[no_mangle]
export function driver_path_read_preprocess_malloc(path: *u8): *u8 {
  unsafe { return xlang_driver_path_read_preprocess_malloc(path); }
  return 0 as *u8;
}

/** Exported function `driver_fmt_check_only_set`.
 * Implements `driver_fmt_check_only_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_fmt_check_only_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_fmt_check_only_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_large_stack_thread_mark`.
 * Read path helper `driver_large_stack_thread_mark`.
 * @param on i32
 * @return void
 */
#[no_mangle]
export function driver_large_stack_thread_mark(on: i32): void {
  unsafe {
    let p: *i32 = driver_large_stack_thread_flag_slot();
    p[0] = on;
  }
}

/** Exported function `driver_is_large_stack_thread`.
 * Read path helper `driver_is_large_stack_thread`.
 * @return i32
 */
#[no_mangle]
export function driver_is_large_stack_thread(): i32 {
  unsafe {
    let p: *i32 = driver_large_stack_thread_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_check_only_set`.
 * Implements `driver_check_only_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_check_only_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_check_only_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_skip_codegen_dep_0_get`.
 * Implements `driver_skip_codegen_dep_0_get`.
 * @return i32
 */
#[no_mangle]
export function driver_skip_codegen_dep_0_get(): i32 {
  unsafe {
    let p: *i32 = driver_skip_codegen_dep_0_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_x_pipeline_skip_typeck_get`.
 * Implements `driver_x_pipeline_skip_typeck_get`.
 * @return i32
 */
#[no_mangle]
export function driver_x_pipeline_skip_typeck_get(): i32 {
  unsafe {
    let p: *i32 = driver_x_pipeline_skip_typeck_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_freestanding_get`.
 * Memory management helper `driver_freestanding_get`.
 * @return i32
 */
#[no_mangle]
export function driver_freestanding_get(): i32 {
  unsafe {
    let p: *i32 = driver_freestanding_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_check_only_get`.
 * Implements `driver_check_only_get`.
 * @return i32
 */
#[no_mangle]
export function driver_check_only_get(): i32 {
  unsafe {
    let p: *i32 = driver_check_only_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Alias for driver_current_dep_path_store (pipeline codegen loop per-dep).
 * PLATFORM: SHARED — pure forward to path BSS store. */
#[no_mangle]
export function driver_set_current_dep_path_for_codegen(path: *u8): void {
  driver_current_dep_path_store(path);
}

// driver_argv_is_D_alone: see function docblock below.
/** Exported function `driver_argv_is_D_alone`.
 * Implements `driver_argv_is_D_alone`.
 * @param arg *u8
 * @return i32
 */
export function driver_argv_is_D_alone(arg: *u8): i32 {
  if (arg == 0 as *u8) { return 0; }
  unsafe {
    if (arg[0] != 45) { return 0; }
    if (arg[1] != 68) { return 0; }
    if (arg[2] != 0) { return 0; }
    return 1;
  }
  return 0;
}
/** Exported function `driver_argv_is_D_inline`.
 * Implements `driver_argv_is_D_inline`.
 * @param arg *u8
 * @return i32
 */
export function driver_argv_is_D_inline(arg: *u8): i32 {
  if (arg == 0 as *u8) { return 0; }
  unsafe {
    if (arg[0] != 45) { return 0; }
    if (arg[1] != 68) { return 0; }
    if (arg[2] == 0) { return 0; }
    return 1;
  }
  return 0;
}
/** Exported function `driver_argv_is_target_flag`.
 * Implements `driver_argv_is_target_flag`.
 * @param arg *u8
 * @return i32
 */
export function driver_argv_is_target_flag(arg: *u8): i32 {
  if (arg == 0 as *u8) { return 0; }
  unsafe {
    if (arg[0] != 45) { return 0; }
    if (arg[1] != 116) { return 0; }
    if (arg[2] != 97) { return 0; }
    if (arg[3] != 114) { return 0; }
    if (arg[4] != 103) { return 0; }
    if (arg[5] != 101) { return 0; }
    if (arg[6] != 116) { return 0; }
    if (arg[7] != 0) { return 0; }
    return 1;
  }
  return 0;
}
/** Exported function `driver_argv_is_value_skip_flag`.
 * Implements `driver_argv_is_value_skip_flag`.
 * @param arg *u8
 * @return i32
 */
export function driver_argv_is_value_skip_flag(arg: *u8): i32 {
  if (arg == 0 as *u8) { return 0; }
  unsafe {
    if (arg[0] != 45) { return 0; }
    if (arg[1] == 111) { if (arg[2] == 0) { return 1; } }
    if (arg[1] == 76) { if (arg[2] == 0) { return 1; } }
    if (arg[1] == 79) { if (arg[2] == 0) { return 1; } }
    if (arg[1] == 98) {
      if (arg[2] == 97) {
        if (arg[3] == 99) {
          if (arg[4] == 107) {
            if (arg[5] == 101) {
              if (arg[6] == 110) {
                if (arg[7] == 100) {
                  if (arg[8] == 0) { return 1; }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
/** Exported function `driver_cstr_contains_bytes`.
 * Implements `driver_cstr_contains_bytes`.
 * @param hay *u8
 * @param n0 u8
 * @param n1 u8
 * @param n2 u8
 * @param n3 u8
 * @param n4 u8
 * @param nlen i32
 * @return i32
 */
export function driver_cstr_contains_bytes(hay: *u8, n0: u8, n1: u8, n2: u8, n3: u8, n4: u8, nlen: i32): i32 {
  if (hay == 0 as *u8) { return 0; }
  if (nlen <= 0) { return 0; }
  unsafe {
    let i: i32 = 0;
    while (i < 4096) {
      if (hay[i] == 0) { return 0; }
      if (hay[i] == n0) {
        if (nlen == 1) { return 1; }
        if (hay[i + 1] == n1) {
          if (nlen == 2) { return 1; }
          if (hay[i + 2] == n2) {
            if (nlen == 3) { return 1; }
            if (hay[i + 3] == n3) {
              if (nlen == 4) { return 1; }
              if (hay[i + 4] == n4) { return 1; }
            }
          }
        }
      }
      i = i + 1;
    }
  }
  return 0;
}
/** Exported function `driver_target_arg_os_kind`.
 * Implements `driver_target_arg_os_kind`.
 * @param target *u8
 * @return i32
 */
#[no_mangle]
export function driver_target_arg_os_kind(target: *u8): i32 {
  if (target == 0 as *u8) { return 0; }
  if (driver_cstr_contains_bytes(target, 108, 105, 110, 117, 120, 5) != 0) { return 1; }
  if (driver_cstr_contains_bytes(target, 100, 97, 114, 119, 105, 5) != 0) { return 2; }
  if (driver_cstr_contains_bytes(target, 97, 112, 112, 108, 101, 5) != 0) { return 2; }
  if (driver_cstr_contains_bytes(target, 102, 114, 101, 101, 98, 5) != 0) { return 3; }
  if (driver_cstr_contains_bytes(target, 119, 105, 110, 100, 111, 5) != 0) { return 4; }
  return 0;
}

/** Exported function `driver_x_pipeline_skip_typeck_set`.
 * Implements `driver_x_pipeline_skip_typeck_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_x_pipeline_skip_typeck_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_x_pipeline_skip_typeck_flag_slot();
    p[0] = v;
  }
}

// See implementation.
// driver_x_pipeline_skip_codegen_set: see function docblock below.

/** Exported function `driver_x_pipeline_skip_codegen_set`.
 * Implements `driver_x_pipeline_skip_codegen_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_x_pipeline_skip_codegen_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_x_pipeline_skip_codegen_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_sanitize_address_set`.
 * Implements `driver_sanitize_address_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_sanitize_address_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_sanitize_address_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_x_pipeline_skip_codegen_get`.
 * Implements `driver_x_pipeline_skip_codegen_get`.
 * @return i32
 */
#[no_mangle]
export function driver_x_pipeline_skip_codegen_get(): i32 {
  unsafe {
    let p: *i32 = driver_x_pipeline_skip_codegen_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_skip_codegen_dep_0_set`.
 * Implements `driver_skip_codegen_dep_0_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_skip_codegen_dep_0_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_skip_codegen_dep_0_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_freestanding_set`.
 * Memory management helper `driver_freestanding_set`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_freestanding_set(v: i32): void {
  unsafe {
    let p: *i32 = driver_freestanding_flag_slot();
    p[0] = v;
  }
}

/** Exported function `driver_check_diag_emitted_note`.
 * Implements `driver_check_diag_emitted_note`.
 * @return void
 */
#[no_mangle]
export function driver_check_diag_emitted_note(): void {
  unsafe {
    let p: *i32 = driver_check_diag_emitted_flag_slot();
    p[0] = 1;
  }
}

/** Exported function `driver_check_diag_emitted_reset`.
 * Implements `driver_check_diag_emitted_reset`.
 * @return void
 */
#[no_mangle]
export function driver_check_diag_emitted_reset(): void {
  unsafe {
    let p: *i32 = driver_check_diag_emitted_flag_slot();
    p[0] = 0;
  }
}

/** Exported function `driver_fmt_check_only_get`.
 * Implements `driver_fmt_check_only_get`.
 * @return i32
 */
#[no_mangle]
export function driver_fmt_check_only_get(): i32 {
  unsafe {
    let p: *i32 = driver_fmt_check_only_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/** Exported function `driver_check_diag_emitted_get`.
 * Implements `driver_check_diag_emitted_get`.
 * @return i32
 */
#[no_mangle]
export function driver_check_diag_emitted_get(): i32 {
  unsafe {
    let p: *i32 = driver_check_diag_emitted_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return 0;
  }
  return 0;
}

// ---- G-02f-343 gates (permanent OS surfaces; pure orch above) ----

/** Append non-negative i64 decimal into dst (for size_t-style fields such as codegen_bytes).
 * Values in [0, INT_MAX] delegate to driver_diag_append_i32 (G.7 reuse). Larger values use a
 * local 20-digit stack so message text matches cold seed %zu for typical module sizes.
 * PLATFORM: SHARED — local helper for wave3 format print pure only. */
function driver_abi_append_i64(dst: *u8, cap: i32, at: i32, val: i64): i32 {
  unsafe {
    if (dst == 0 as *u8) {
      return at;
    }
    if (val < 0) {
      // Smoke/codegen lengths are non-negative; keep sign for defensive completeness.
      if (at + 1 >= cap) {
        return at;
      }
      dst[at] = 45;
      at = at + 1;
      val = 0 - val;
    }
    if (val <= 2147483647) {
      return driver_diag_append_i32(dst, cap, at, val as i32);
    }
    // Digit stack (least-significant first); up to 20 decimal digits for i64.
    let d0: i32 = 0;
    let d1: i32 = 0;
    let d2: i32 = 0;
    let d3: i32 = 0;
    let d4: i32 = 0;
    let d5: i32 = 0;
    let d6: i32 = 0;
    let d7: i32 = 0;
    let d8: i32 = 0;
    let d9: i32 = 0;
    let d10: i32 = 0;
    let d11: i32 = 0;
    let d12: i32 = 0;
    let d13: i32 = 0;
    let d14: i32 = 0;
    let d15: i32 = 0;
    let d16: i32 = 0;
    let d17: i32 = 0;
    let d18: i32 = 0;
    let d19: i32 = 0;
    let dn: i32 = 0;
    let t: i64 = val;
    while (t > 0) {
      if (dn >= 20) {
        break;
      }
      let dig: i32 = (t % 10) as i32;
      if (dn == 0) { d0 = dig; }
      if (dn == 1) { d1 = dig; }
      if (dn == 2) { d2 = dig; }
      if (dn == 3) { d3 = dig; }
      if (dn == 4) { d4 = dig; }
      if (dn == 5) { d5 = dig; }
      if (dn == 6) { d6 = dig; }
      if (dn == 7) { d7 = dig; }
      if (dn == 8) { d8 = dig; }
      if (dn == 9) { d9 = dig; }
      if (dn == 10) { d10 = dig; }
      if (dn == 11) { d11 = dig; }
      if (dn == 12) { d12 = dig; }
      if (dn == 13) { d13 = dig; }
      if (dn == 14) { d14 = dig; }
      if (dn == 15) { d15 = dig; }
      if (dn == 16) { d16 = dig; }
      if (dn == 17) { d17 = dig; }
      if (dn == 18) { d18 = dig; }
      if (dn == 19) { d19 = dig; }
      t = t / 10;
      dn = dn + 1;
    }
    if (dn == 0) {
      d0 = 0;
      dn = 1;
    }
    let i: i32 = dn - 1;
    while (i >= 0) {
      if (at + 1 >= cap) {
        break;
      }
      let dig2: i32 = 0;
      if (i == 0) { dig2 = d0; }
      if (i == 1) { dig2 = d1; }
      if (i == 2) { dig2 = d2; }
      if (i == 3) { dig2 = d3; }
      if (i == 4) { dig2 = d4; }
      if (i == 5) { dig2 = d5; }
      if (i == 6) { dig2 = d6; }
      if (i == 7) { dig2 = d7; }
      if (i == 8) { dig2 = d8; }
      if (i == 9) { dig2 = d9; }
      if (i == 10) { dig2 = d10; }
      if (i == 11) { dig2 = d11; }
      if (i == 12) { dig2 = d12; }
      if (i == 13) { dig2 = d13; }
      if (i == 14) { dig2 = d14; }
      if (i == 15) { dig2 = d15; }
      if (i == 16) { dig2 = d16; }
      if (i == 17) { dig2 = d17; }
      if (i == 18) { dig2 = d18; }
      if (i == 19) { dig2 = d19; }
      dst[at] = (48 + dig2) as u8;
      at = at + 1;
      i = i - 1;
    }
    if (at < cap) {
      dst[at] = 0;
    }
    return at;
  }
  return at;
}

/** Emit quiet-gated "check OK: <path>" info line (deno check stays silent when quiet).
 * Assembles via driver_diag_append_cstr then diag_report; no va_list diag_reportf.
 * Message text matches cold seed reportf format. PLATFORM: SHARED — pure authority in thin;
 * cold seed keeps C _impl; FROM_X rest drops pure-dup format _impl. */
#[no_mangle]
export function driver_print_check_ok(input_path: *u8): void {
  unsafe {
    if (driver_check_quiet_ok_get() != 0) {
      return;
    }
    let msg: u8[512] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 512, 0, "check OK: ");
    if (input_path != 0 as *u8) {
      at = driver_diag_append_cstr(&msg[0], 512, at, input_path);
    } else {
      at = driver_diag_append_cstr(&msg[0], 512, at, "?");
    }
    diag_report(0 as *u8, 0, 0, "info", &msg[0], 0 as *u8);
  }
}

/** Wall-clock seconds for compile-phase timing (begin/end).
 * Wave7 pure: forwards to permanent OS surface xlang_driver_wall_clock_sec (no timeval in .x).
 * PLATFORM: SHARED pure authority in thin; OS layout stays in seed rest; FROM_X no pure-dup. */
#[no_mangle]
export function compile_phase_now_sec(): f64 {
  unsafe {
    return xlang_driver_wall_clock_sec();
  }
  return 0.0;
}

/** Run fn(arg) on the current thread under large-stack mark + stack limit bump.
 * Wave8 pure orch: null gate + mark/bump; indirect call via permanent OS surface
 * xlang_driver_call_fn_void_arg (no call_fn _impl residual).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C twin; FROM_X no pure-dup. */
#[no_mangle]
export function driver_run_fn_on_current_large_stack(fn: *u8, arg: *u8): void {
  if (fn == 0 as *u8) {
    return;
  }
  driver_large_stack_thread_mark(1);
  driver_bump_stack_limit();
  unsafe {
    xlang_driver_call_fn_void_arg(fn, arg);
  }
  driver_large_stack_thread_mark(0);
}

// ---- G-02f-344 / wave5–6：timing BSS + begin/end + flush pure ----

/** Exported function `driver_compile_phase_index_ok`.
 * Implements `driver_compile_phase_index_ok`.
 * @param phase i32
 * @return i32
 */
#[no_mangle]
export function driver_compile_phase_index_ok(phase: i32): i32 {
  if (phase < 0) {
    return 0;
  }
  if (phase >= 3) {
    return 0;
  }
  return 1;
}

// driver_compile_phase_timing_enabled: see function docblock below.
/** Exported function `driver_compile_phase_timing_enabled`.
 * Implements `driver_compile_phase_timing_enabled`.
 * @return i32
 */
#[no_mangle]
export function driver_compile_phase_timing_enabled(): i32 {
  return driver_env_nonnull("XLANG_COMPILE_PHASE_TIMING");
}

/** Load accumulated phase ms from thin BSS (0 if phase out of range).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C twin; FROM_X rest flush Cap uses this. */
#[no_mangle]
export function driver_compile_phase_acc_ms_get(phase: i32): f64 {
  if (driver_compile_phase_index_ok(phase) == 0) {
    return 0.0;
  }
  return g_compile_phase_acc_ms[phase];
}

/** Clear phase timing accumulators and active flags (same cells as cold seed memset).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C twin; FROM_X rest flush Cap uses this. */
#[no_mangle]
export function driver_compile_phase_timing_clear(): void {
  g_compile_phase_acc_ms[0] = 0.0;
  g_compile_phase_acc_ms[1] = 0.0;
  g_compile_phase_acc_ms[2] = 0.0;
  g_compile_phase_active[0] = 0;
  g_compile_phase_active[1] = 0;
  g_compile_phase_active[2] = 0;
}

/** Mark compile phase start (wall-clock via compile_phase_now_sec Cap).
 * Wave5 pure: stores start_sec + active in thin BSS (no begin_impl).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C _impl; FROM_X no pure-dup. */
#[no_mangle]
export function driver_compile_phase_timing_begin(phase: i32): void {
  if (driver_compile_phase_timing_enabled() == 0) {
    return;
  }
  if (driver_compile_phase_index_ok(phase) == 0) {
    return;
  }
  g_compile_phase_start_sec[phase] = compile_phase_now_sec();
  g_compile_phase_active[phase] = 1;
}

/** Accumulate phase duration into acc_ms (ms) and clear active.
 * Wave5 pure: f64 arithmetic on thin BSS (no end_impl).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C _impl; FROM_X no pure-dup. */
#[no_mangle]
export function driver_compile_phase_timing_end(phase: i32): void {
  if (driver_compile_phase_timing_enabled() == 0) {
    return;
  }
  if (driver_compile_phase_index_ok(phase) == 0) {
    return;
  }
  if (g_compile_phase_active[phase] == 0) {
    return;
  }
  let now: f64 = compile_phase_now_sec();
  // PLATFORM: SHARED — use (1000 as f64); decimal f64 lit 1000.0 lowers to 0.0 under -E.
  g_compile_phase_acc_ms[phase] =
    g_compile_phase_acc_ms[phase] + (now - g_compile_phase_start_sec[phase]) * (1000 as f64);
  g_compile_phase_active[phase] = 0;
}

/** Print compile phase timing note then clear thin BSS.
 * Wave6 pure: whole milliseconds via driver_diag_append_* + diag_report (no va_list reportf).
 * Fractional sub-ms is truncated (f64→i32); sufficient for XLANG_COMPILE_PHASE_TIMING notes.
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps integer-ms twin; FROM_X no pure-dup. */
#[no_mangle]
export function driver_compile_phase_timing_flush(): void {
  if (driver_compile_phase_timing_enabled() == 0) {
    return;
  }
  unsafe {
    let a0: i32 = driver_compile_phase_acc_ms_get(0) as i32;
    let a1: i32 = driver_compile_phase_acc_ms_get(1) as i32;
    let a2: i32 = driver_compile_phase_acc_ms_get(2) as i32;
    let total: i32 = a0 + a1 + a2;
    let msg: u8[192] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 192, 0, "compile phase timing: parse_ms=");
    at = driver_diag_append_i32(&msg[0], 192, at, a0);
    at = driver_diag_append_cstr(&msg[0], 192, at, " typeck_ms=");
    at = driver_diag_append_i32(&msg[0], 192, at, a1);
    at = driver_diag_append_cstr(&msg[0], 192, at, " codegen_ms=");
    at = driver_diag_append_i32(&msg[0], 192, at, a2);
    at = driver_diag_append_cstr(&msg[0], 192, at, " total_ms=");
    at = driver_diag_append_i32(&msg[0], 192, at, total);
    diag_report(0 as *u8, 0, 0, "note", &msg[0], 0 as *u8);
  }
  driver_compile_phase_timing_clear();
}

// ---- G-02f-345：ascii_toupper / typeck_skip / sanitize_get ----
// driver_ascii_toupper: see function docblock below.
/** Exported function `driver_ascii_toupper`.
 * Implements `driver_ascii_toupper`.
 * @param c i32
 * @return i32
 */
#[no_mangle]
export function driver_ascii_toupper(c: i32): i32 {
  if (c < 97) {
    return c;
  }
  if (c > 122) {
    return c;
  }
  return c - 32;
}

/** Exported function `driver_typeck_skip_large_entry`.
 * Implements `driver_typeck_skip_large_entry`.
 * @return i32
 */
#[no_mangle]
export function driver_typeck_skip_large_entry(): i32 {
  let len: i32 = driver_pipeline_entry_source_len_i32();
  if (len > 150000) {
    return 1;
  }
  return 0;
}

// driver_sanitize_address_get: see function docblock below.
/** Exported function `driver_sanitize_address_get`.
 * Implements `driver_sanitize_address_get`.
 * @return i32
 */
#[no_mangle]
export function driver_sanitize_address_get(): i32 {
  unsafe {
    let p: *i32 = driver_sanitize_address_flag_slot();
    if (p[0] != 0) {
      return 1;
    }
    return driver_env_flag_truthy("XLANG_SANITIZE_ADDRESS");
  }
  return 0;
}

// driver_typeck_force_c_enabled: see function docblock below.
/** Exported function `driver_typeck_force_c_enabled`.
 * Implements `driver_typeck_force_c_enabled`.
 * @return i32
 */
#[no_mangle]
export function driver_typeck_force_c_enabled(): i32 {
  return driver_env_flag_truthy("XLANG_TYPECK_FORCE_C");
}

/** Exported function `driver_asm_build_skip_typeck`.
 * Implements `driver_asm_build_skip_typeck`.
 * @return i32
 */
#[no_mangle]
export function driver_asm_build_skip_typeck(): i32 {
  return driver_env_flag_truthy("XLANG_ASM_BUILD_SKIP_TYPECK");
}

/** Exported function `driver_asm_entry_emit_heavy`.
 * Implements `driver_asm_entry_emit_heavy`.
 * @return i32
 */
#[no_mangle]
export function driver_asm_entry_emit_heavy(): i32 {
  return driver_env_flag_truthy("XLANG_ASM_ENTRY_EMIT_HEAVY");
}

/** Exported function `driver_pipeline_no_large_stack_env`.
 * Implements `driver_pipeline_no_large_stack_env`.
 * @return i32
 */
#[no_mangle]
export function driver_pipeline_no_large_stack_env(): i32 {
  return driver_env_flag_truthy("XLANG_PIPELINE_NO_LARGE_STACK");
}

/** Exported function `driver_asm_entry_module_only_from_env`.
 * Implements `driver_asm_entry_module_only_from_env`.
 * @return i32
 */
#[no_mangle]
export function driver_asm_entry_module_only_from_env(): i32 {
  return driver_env_flag_truthy("XLANG_ASM_ENTRY_MODULE_ONLY");
}

/** Exported function `driver_asm_parse_metric_only_from_env`.
 * Implements `driver_asm_parse_metric_only_from_env`.
 * @return i32
 */
#[no_mangle]
export function driver_asm_parse_metric_only_from_env(): i32 {
  return driver_env_flag_truthy("XLANG_ASM_PARSE_METRIC_ONLY");
}

// driver_pipeline_entry_source_len_i32: see function docblock below.
/** Exported function `driver_pipeline_entry_source_len_i32`.
 * Implements `driver_pipeline_entry_source_len_i32`.
 * @return i32
 */
#[no_mangle]
export function driver_pipeline_entry_source_len_i32(): i32 {
  unsafe {
    let len: i64 = driver_pipeline_entry_source_len_load_and_maybe_debug();
    if (len > 2147483647) {
      return 2147483647;
    }
    if (len < 0) {
      return 0;
    }
    return len as i32;
  }
  return 0;
}

// ---- G-02f-400 / wave4 pure：defines_set_at via xlang_ptr_slot_set (G.7); path_last pure wave2 ----
/** Store defines[i] = s for argv -D table (defines is opaque *u8 for **char).
 * Null defines or negative i is a no-op. Uses pipeline xlang_ptr_slot_set as the single
 * pointer-slot write authority (G.7) — no second **write path in driver rest.
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C _impl; FROM_X no pure-dup. */
#[no_mangle]
export function driver_defines_set_at(defines: *u8, i: i32, s: *u8): void {
  if (defines == 0 as *u8) {
    return;
  }
  if (i < 0) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(defines, i, s);
  }
}

/**
 * Desired RLIMIT_STACK soft size in bytes from XLANG_STACK_LIMIT_MB (or default).
 * Default is 512 MiB. Env must parse as u32 in [64, 8192] MiB; otherwise default.
 * @return i64 — want bytes (> 0)
 * wave228 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED orch; host residual only link_abi_getenv_impl.
 */
#[no_mangle]
export function driver_stack_limit_want_bytes(): i64 {
  let def: i64 = 512 as i64 * 1024 as i64 * 1024 as i64;
  unsafe {
    let e: *u8 = link_abi_getenv("XLANG_STACK_LIMIT_MB");
    if (e == 0 as *u8) {
      return def;
    }
    if (e[0] == 0) {
      return def;
    }
    let mb: i64 = driver_parse_u32_cstr(e);
    if (mb < 64) {
      return def;
    }
    if (mb > 8192) {
      return def;
    }
    return mb * (1024 as i64 * 1024 as i64);
  }
  return def;
}

// ---- G-02f-402 / wave9：bump_stack orch pure / set_entry_len / phase_timing enabled pure / os_define_lit wave4 ----
/** Raise RLIMIT_STACK soft limit using env-derived want bytes.
 * Wave9 pure: want pure in thin; setrlimit via permanent OS surface xlang_driver_bump_stack_limit.
 * PLATFORM: SHARED pure orch; OS layout stays in seed rest; FROM_X no pure-dup setrlimit _impl. */
#[no_mangle]
export function driver_bump_stack_limit(): void {
  unsafe {
    xlang_driver_bump_stack_limit(driver_stack_limit_want_bytes());
  }
}

/** Alias for driver_pipeline_entry_source_len_store (large-stack entry before pipeline).
 * PLATFORM: SHARED — pure forward to entry-len BSS store. */
#[no_mangle]
export function driver_set_pipeline_entry_source_len(len: i64): void {
  driver_pipeline_entry_source_len_store(len);
}

// compile_phase_timing_enabled: see function docblock below.
/** Exported function `compile_phase_timing_enabled`.
 * Implements `compile_phase_timing_enabled`.
 * @return i32
 */
#[no_mangle]
export function compile_phase_timing_enabled(): i32 {
  return driver_env_nonnull("XLANG_COMPILE_PHASE_TIMING");
}

/** Map target OS kind (1..4) to a static define literal pointer (OS_LINUX/…).
 * kind 0 or unknown → null. Wave4 pure: string-lit table in thin (same text as cold seed).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C _impl; FROM_X no pure-dup. */
#[no_mangle]
export function driver_os_define_lit(kind: i32): *u8 {
  if (kind == 1) {
    return "OS_LINUX";
  }
  if (kind == 2) {
    return "OS_MACOS";
  }
  if (kind == 3) {
    return "OS_FREEBSD";
  }
  if (kind == 4) {
    return "OS_WINDOWS";
  }
  return 0 as *u8;
}

// ---- G-02f-413：fail_code / smoke / peek / get_dep / argv_defines → seed impl ----

/** Emit XP003 "pipeline failed rc=N"; when rc==-7 also XP004 "resolve path tried: P".
 * Wave3 pure: append_i32/cstr + diag_report_with_code (codes XP003/XP004 match cold seed
 * XLANG_DIAG_CODE_X_PIPELINE_*). No va_list reportf. PLATFORM: SHARED — pure authority in thin;
 * cold seed keeps C format _impl; FROM_X rest drops pure-dup. */
#[no_mangle]
export function driver_pipeline_fail_code(rc: i32, path: *u8): void {
  unsafe {
    let msg: u8[96] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 96, 0, "pipeline failed rc=");
    at = driver_diag_append_i32(&msg[0], 96, at, rc);
    diag_report_with_code(0 as *u8, 0, 0, "pipeline error", "XP003", &msg[0], 0 as *u8);
    if (rc != 0 - 7) {
      return;
    }
    if (path == 0 as *u8) {
      return;
    }
    let msg2: u8[512] = [];
    let at2: i32 = driver_diag_append_cstr(&msg2[0], 512, 0, "resolve path tried: ");
    at2 = driver_diag_append_cstr(&msg2[0], 512, at2, path);
    diag_report_with_code(0 as *u8, 0, 0, "pipeline error", "XP004", &msg2[0], 0 as *u8);
  }
}

/** Emit smoke summary: parse OK line; if no funcs, P001 empty-module error and return;
 * else typeck OK. Wave3 pure: assemble via append_* + diag_report / diag_report_with_code;
 * no va_list reportf. Prefix strings match cold seed for run-import gate grep.
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C format _impl; FROM_X no pure-dup. */
#[no_mangle]
export function driver_print_x_smoke_summary(module: *u8, codegen_len: i64): void {
  if (module == 0 as *u8) {
    return;
  }
  unsafe {
    if (driver_check_diag_emitted_get() != 0) {
      return;
    }
    let num_funcs: i32 = driver_get_module_num_funcs(module);
    let main_ix: i32 = driver_get_module_main_func_index(module);
    let msg: u8[160] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 160, 0, "parse OK: num_funcs=");
    at = driver_diag_append_i32(&msg[0], 160, at, num_funcs);
    at = driver_diag_append_cstr(&msg[0], 160, at, " main_idx=");
    at = driver_diag_append_i32(&msg[0], 160, at, main_ix);
    at = driver_diag_append_cstr(&msg[0], 160, at, " codegen_bytes=");
    at = driver_abi_append_i64(&msg[0], 160, at, codegen_len);
    diag_report(0 as *u8, 0, 0, "info", &msg[0], 0 as *u8);
    if (num_funcs <= 0) {
      diag_report_with_code(0 as *u8, 0, 0, "parse error", "P001",
        "parse produced no functions in module", 0 as *u8);
      return;
    }
    diag_report(0 as *u8, 0, 0, "info", "typeck OK", 0 as *u8);
  }
}

// driver_peek_source_file: see function docblock below.
/** Exported function `driver_peek_source_file`.
 * Implements `driver_peek_source_file`.
 * @param path *u8
 * @param content *u8
 * @param cap i64
 * @return i32
 */
#[no_mangle]
export function driver_peek_source_file(path: *u8, content: *u8, cap: i64): i32 {
  if (path == 0 as *u8) {
    return 0 - 1;
  }
  if (content == 0 as *u8) {
    return 0 - 1;
  }
  if (cap <= 1) {
    return 0 - 1;
  }
  unsafe {
    let n: i32 = xlang_read_file_into_path(path, content, cap - 1);
    return n;
  }
  return 0 - 1;
}

/** Alias for driver_current_dep_path_load (codegen prefix reads current dep).
 * PLATFORM: SHARED — pure forward to path BSS load. */
#[no_mangle]
export function driver_get_current_dep_path_for_codegen(): *u8 {
  return driver_current_dep_path_load();
}

/** Collect -D / -target defines from argv; append host uname defines when room.
 * Wave10 pure orch: main loop pure; host OS/arch via permanent OS surface
 * xlang_driver_argv_append_uname (no struct utsname in .x; no append_uname _impl residual).
 * PLATFORM: SHARED pure orch; uname layout stays in seed rest. */
#[no_mangle]
export function driver_argv_collect_defines(argc: i32, argv: *u8, defines: *u8, max_defines: i32): i32 {
  if (argv == 0 as *u8) { return 0; }
  if (defines == 0 as *u8) { return 0; }
  if (max_defines <= 0) { return 0; }
  if (argc <= 0) { return 0; }
  let ndefines: i32 = 0;
  let target_arg: *u8 = 0 as *u8;
  let i: i32 = 1;
  while (i < argc) {
    unsafe {
      let arg: *u8 = driver_argv_at(argv, i);
      if (arg == 0 as *u8) {
        i = i + 1;
      } else {
        if (driver_argv_is_D_alone(arg) != 0) {
          if (i + 1 >= argc) {
            i = i + 1;
          } else {
            let v: *u8 = driver_argv_at(argv, i + 1);
            if (v != 0 as *u8) {
              if (ndefines < max_defines) {
                driver_defines_set_at(defines, ndefines, v);
                ndefines = ndefines + 1;
              }
            }
            i = i + 2;
          }
        } else {
          if (driver_argv_is_D_inline(arg) != 0) {
            let def: *u8 = xlang_cstr_offset(arg, 2);
            if (def != 0 as *u8) {
              if (ndefines < max_defines) {
                driver_defines_set_at(defines, ndefines, def);
                ndefines = ndefines + 1;
              }
            }
            i = i + 1;
          } else {
            if (driver_argv_is_target_flag(arg) != 0) {
              if (i + 1 < argc) {
                target_arg = driver_argv_at(argv, i + 1);
                i = i + 2;
              } else {
                i = i + 1;
              }
            } else {
              if (driver_argv_is_value_skip_flag(arg) != 0) {
                if (i + 1 < argc) {
                  i = i + 2;
                } else {
                  i = i + 1;
                }
              } else {
                i = i + 1;
              }
            }
          }
        }
      }
    }
  }
  if (target_arg != 0 as *u8) {
    if (ndefines < max_defines) {
      let k: i32 = driver_target_arg_os_kind(target_arg);
      if (k != 0) {
        unsafe {
          let lit: *u8 = driver_os_define_lit(k);
          if (lit != 0 as *u8) {
            driver_defines_set_at(defines, ndefines, lit);
            ndefines = ndefines + 1;
          }
        }
      }
    }
  }
  if (ndefines + 2 <= max_defines) {
    unsafe {
      ndefines = xlang_driver_argv_append_uname(defines, ndefines, max_defines);
    }
  }
  return ndefines;
}

// ---- G-02f-414：import scan + large-stack entry → seed impl ----

// driver_source_scan_top_level_import: see function docblock below.
/** Exported function `driver_source_scan_top_level_import`.
 * Implements `driver_source_scan_top_level_import`.
 * @param src *u8
 * @param src_len i64
 * @return i32
 */
#[no_mangle]
export function driver_source_scan_top_level_import(src: *u8, src_len: i64): i32 {
  if (src == 0 as *u8) { return 0; }
  if (src_len < 8) { return 0; }
  unsafe {
    let i: i64 = 0;
    while (i + 8 <= src_len) {
      if (src[i] == 105) {
        if (src[i + 1] == 109) {
          if (src[i + 2] == 112) {
            if (src[i + 3] == 111) {
              if (src[i + 4] == 114) {
                if (src[i + 5] == 116) {
                  if (src[i + 6] == 40) {
                    if (src[i + 7] == 34) {
                      return 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (i + 9 <= src_len) {
        if (src[i] == 61) {
          if (src[i + 1] == 32) {
            if (src[i + 2] == 105) {
              if (src[i + 3] == 109) {
                if (src[i + 4] == 112) {
                  if (src[i + 5] == 111) {
                    if (src[i + 6] == 114) {
                      if (src[i + 7] == 116) {
                        if (src[i + 8] == 40) {
                          return 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      i = i + 1;
    }
  }
  return 0;
}

// driver_source_has_top_level_import: see function docblock below.
/** Exported function `driver_source_has_top_level_import`.
 * Implements `driver_source_has_top_level_import`.
 * @param src *u8
 * @param src_len i64
 * @return i32
 */
#[no_mangle]
export function driver_source_has_top_level_import(src: *u8, src_len: i64): i32 {
  if (src == 0 as *u8) { return 0; }
  if (src_len < 9) { return 0; }
  return driver_source_scan_top_level_import(src, src_len);
}

// driver_source_has_top_level_import_path: see function docblock below.
/** Exported function `driver_source_has_top_level_import_path`.
 * Implements `driver_source_has_top_level_import_path`.
 * @param path *u8
 * @return i32
 */
#[no_mangle]
export function driver_source_has_top_level_import_path(path: *u8): i32 {
  if (path == 0 as *u8) { return 0; }
  unsafe {
    let src: *u8 = driver_path_read_preprocess_malloc(path);
    if (src == 0 as *u8) { return 0; }
    let len: i64 = driver_path_last_preprocess_len();
    let has: i32 = driver_source_has_top_level_import(src, len);
    free(src);
    return has;
  }
  return 0;
}

/** Orchestrate large-stack run: pure early exits; pthread create via permanent OS surface.
 * Wave8: already-on-large-stack path uses xlang_driver_call_fn_void_arg (no call_fn _impl).
 * Wave12 pure: pthread body via xlang_driver_run_thread_on_large_stack_pthread (no pthread _impl residual).
 * PLATFORM: SHARED pure orch; pthread_attr / memalign / create+join stay in seed rest. */
#[no_mangle]
export function driver_run_thread_on_large_stack(fn: *u8, arg: *u8): void {
  if (fn == 0 as *u8) {
    return;
  }
  if (driver_is_large_stack_thread() != 0) {
    unsafe {
      xlang_driver_call_fn_void_arg(fn, arg);
    }
    return;
  }
  driver_bump_stack_limit();
  unsafe {
    if (bootstrap_nostdlib_pthread_is_stub() != 0) {
      driver_run_fn_on_current_large_stack(fn, arg);
      return;
    }
  }
  if (driver_pipeline_no_large_stack_env() != 0) {
    driver_run_fn_on_current_large_stack(fn, arg);
    return;
  }
  unsafe {
    xlang_driver_run_thread_on_large_stack_pthread(fn, arg);
  }
}

// driver_run_on_large_stack_pthread: see function docblock below.
/** Exported function `driver_run_on_large_stack_pthread`.
 * Read path helper `driver_run_on_large_stack_pthread`.
 * @param fn *u8
 * @param arg *u8
 * @return void
 */
#[no_mangle]
export function driver_run_on_large_stack_pthread(fn: *u8, arg: *u8): void {
  if (fn == 0 as *u8) {
    return;
  }
  driver_run_thread_on_large_stack(fn, arg);
}

/** Load pipeline entry source length from thin BSS; optionally emit a debug note.
 * Wave13 pure: when XLANG_DEBUG_PIPE is truthy (non-empty and not '0'), assemble
 * "pipeline debug: entry_source_len_global=<len>" via driver_diag_append_cstr +
 * driver_abi_append_i64 + diag_report (no va_list diag_reportf). Env gate reuses
 * driver_env_flag_truthy (same shape as driver_diag_env_debug_pipe / G.7).
 * Cold seed keeps an integer-note twin under #ifndef FROM_X.
 * PLATFORM: SHARED — hybrid pure authority for the length cell + debug note. */
#[no_mangle]
export function driver_pipeline_entry_source_len_load_and_maybe_debug(): i64 {
  unsafe {
    let len: i64 = g_pipeline_entry_source_len[0];
    if (driver_env_flag_truthy("XLANG_DEBUG_PIPE") != 0) {
      let msg: u8[96] = [0];
      let at: i32 = driver_diag_append_cstr(&msg[0], 96, 0, "pipeline debug: entry_source_len_global=");
      at = driver_abi_append_i64(&msg[0], 96, at, len);
      diag_report(0 as *u8, 0, 0, "note", &msg[0], 0 as *u8);
    }
    return len;
  }
  return 0;
}

/** Query entry source length (delegates to load_and_maybe_debug; may emit debug note).
 * PLATFORM: SHARED. */
#[no_mangle]
export function driver_pipeline_entry_source_len(): i64 {
  return driver_pipeline_entry_source_len_load_and_maybe_debug();
}

// ---- Wave14 Cap residual pure: rt_asm_stub GAS table + OutBuf append (PLATFORM: SHARED) ----
// Host layout (seeds/runtime_driver_abi.from_x.c driver_codegen_outbuf_abi):
//   unsigned char data[X_CODEGEN_OUTBUF_CAP_ABI];  // CAP = 9 * 1024 * 1024
//   int32_t len;                                   // little-endian i32 at offset CAP
// Cold seed keeps C table/append under #ifndef XLANG_L2_RDABI_THIN_FROM_X.
// G.7: single product authority for gas_line_* / out_append under PREFER hybrid thin.

/** Codegen OutBuf capacity in bytes (matches X_CODEGEN_OUTBUF_CAP_ABI in seed).
 * PLATFORM: SHARED — must stay identical to cold C define. */
function driver_abi_codegen_outbuf_cap(): i32 {
  return 9 * 1024 * 1024;
}

/** Load little-endian i32 at base+off (null-safe; off < 0 → 0).
 * Module-local host layout helper for wave14 OutBuf len cell.
 * PLATFORM: SHARED. */
function driver_abi_load_i32_le(p: *u8, off: i32): i32 {
  if (p == 0 as *u8) {
    return 0;
  }
  if (off < 0) {
    return 0;
  }
  unsafe {
    let m: i32 = 256;
    let a: i32 = p[off] as i32;
    a = a + (p[off + 1] as i32) * m;
    a = a + (p[off + 2] as i32) * m * m;
    a = a + (p[off + 3] as i32) * m * m * m;
    return a;
  }
  return 0;
}

/** Store little-endian i32 at base+off (null / off < 0 no-op).
 * Module-local host layout helper for wave14 OutBuf len cell.
 * PLATFORM: SHARED. */
function driver_abi_store_i32_le(p: *u8, off: i32, v: i32): void {
  if (p == 0 as *u8) {
    return;
  }
  if (off < 0) {
    return;
  }
  unsafe {
    let u: u32 = v as u32;
    p[off] = (u & 255) as u8;
    p[off + 1] = ((u / 256) & 255) as u8;
    p[off + 2] = ((u / 65536) & 255) as u8;
    p[off + 3] = ((u / 16777216) & 255) as u8;
  }
}

/** C-string length in bytes (no trailing NUL counted); null → 0.
 * PLATFORM: SHARED — pure helper for gas append. */
function driver_abi_cstr_len(s: *u8): i32 {
  if (s == 0 as *u8) {
    return 0;
  }
  let n: i32 = 0;
  unsafe {
    while (s[n] != 0) {
      n = n + 1;
      if (n > 100000000) {
        return n;
      }
    }
  }
  return n;
}

/** Return the i-th fixed GAS stub line for asm_codegen_ast (rv=42 skeleton).
 * Wave14 pure: string-lit table in thin (same text as cold seed g_asm_stub_gas_lines).
 * Out-of-range or negative i → null.
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C table; FROM_X no pure-dup. */
#[no_mangle]
export function driver_asm_stub_gas_line_at(i: i32): *u8 {
  if (i == 0) {
    return ".text";
  }
  if (i == 1) {
    return ".globl main";
  }
  if (i == 2) {
    return "main:";
  }
  if (i == 3) {
    return "pushq %rbp";
  }
  if (i == 4) {
    return "movq %rsp, %rbp";
  }
  if (i == 5) {
    return "subq $0, %rsp";
  }
  if (i == 6) {
    return "movl $42, %eax";
  }
  if (i == 7) {
    return "movq %rsp, %rbp";
  }
  if (i == 8) {
    return "popq %rbp";
  }
  if (i == 9) {
    return "ret";
  }
  return 0 as *u8;
}

/** Number of fixed GAS stub lines (matches cold seed g_asm_stub_gas_lines_n = 10).
 * PLATFORM: SHARED — wave14 pure. */
#[no_mangle]
export function driver_asm_stub_gas_line_count(): i32 {
  return 10;
}

/** Append C-string s plus a trailing newline into driver codegen OutBuf at out.
 * Host layout: data[CAP] then i32 len (LE) at offset CAP. Bounds-check before write.
 * Returns 0 on success; -1 on null args, oversize len cell, or capacity overflow.
 * Wave14 pure: LE load/store of len + byte copy (no memcpy/strlen libc).
 * PLATFORM: SHARED — pure authority in thin; cold seed keeps C append; FROM_X no pure-dup. */
#[no_mangle]
export function driver_asm_stub_out_append_cstr(out: *u8, s: *u8): i32 {
  if (out == 0 as *u8) {
    return 0 - 1;
  }
  if (s == 0 as *u8) {
    return 0 - 1;
  }
  let cap: i32 = driver_abi_codegen_outbuf_cap();
  let cur: i32 = driver_abi_load_i32_le(out, cap);
  if (cur < 0) {
    return 0 - 1;
  }
  if (cur > cap) {
    return 0 - 1;
  }
  let slen: i32 = driver_abi_cstr_len(s);
  // need room for slen bytes + one newline
  if (cur > cap - slen - 1) {
    return 0 - 1;
  }
  unsafe {
    let j: i32 = 0;
    while (j < slen) {
      out[cur + j] = s[j];
      j = j + 1;
    }
    out[cur + slen] = 10; // '\n'
  }
  driver_abi_store_i32_le(out, cap, cur + slen + 1);
  return 0;
}

// ---- Wave15 Cap residual pure: rt_entry + path buffer slots (PLATFORM: SHARED) ----
// Cold seed: static char buffers + slot getters (always present for surface R2).
// PREFER hybrid: authority in this thin TU; FROM_X rest drops pure-dup BSS/slots (H↓).
// G.7: single product authority for entry_*_slot (buf) / path_max / entry_dir under hybrid.
// Note: local u8[N] is banned in product .x (-E init_globals); module BSS is OK (diagnostic thin pattern).
// Wave21 closed fmt_argv (see section below): byte-lit BSS + G.7 ptr slots, no *u8[2] lit.

let g_driver_entry_ab: u8[256] = [];
let g_driver_entry_code: u8[256] = [];
let g_driver_entry_suggest: u8[16] = [];
let g_driver_entry_msg: u8[256] = [];
let g_driver_entry_tmp: u8[16] = [];
let g_driver_entry_tmp2: u8[16] = [];
let g_driver_path_max_slot_buf: u8[4096] = [];
let g_driver_entry_dir_slot_buf: u8[512] = [];

/** Return BSS scratch for entry diagnostic / argv buffer (256 bytes).
 * Wave15 pure: thin owns slot; cold seed keeps C static char[256].
 * PLATFORM: SHARED — pure buffer authority under PREFER hybrid. */
#[no_mangle]
export function driver_entry_ab_slot(): *u8 {
  return &g_driver_entry_ab[0];
}

/** Return BSS scratch for entry diagnostic code string (256 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_code_slot(): *u8 {
  return &g_driver_entry_code[0];
}

/** Return BSS scratch for entry suggestion short string (16 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_suggest_slot(): *u8 {
  return &g_driver_entry_suggest[0];
}

/** Return BSS scratch for entry diagnostic message (256 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_msg_slot(): *u8 {
  return &g_driver_entry_msg[0];
}

/** Return BSS scratch for entry temporary small string (16 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_tmp_slot(): *u8 {
  return &g_driver_entry_tmp[0];
}

/** Return second entry temporary small string slot (16 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_tmp2_slot(): *u8 {
  return &g_driver_entry_tmp2[0];
}

/** Return BSS path buffer for import resolve / path_max (4096 bytes).
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_path_max_slot(): *u8 {
  return &g_driver_path_max_slot_buf[0];
}

/** Return BSS entry directory buffer (512 bytes) used by x_emit dep layout.
 * Wave15 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_entry_dir_slot(): *u8 {
  return &g_driver_entry_dir_slot_buf[0];
}

// ---- Wave16 Cap residual pure: driver_x_emit work BSS + cleanup (PLATFORM: SHARED) ----
// Slot map (must match seed comment + rt_run_x_emit.x consumers):
//   p[26]: 0 path 1 src 2 raw 3 arena 4 module 5 entry_dir 6 dep_sources 7 dep_paths
//          8 dep_lens 9 dep_arenas 10 dep_modules 11 out_buf 12 pctx 13 one_ctx
//          14 dep_out 15 dep_src 16 resolved 17 snap 18 dep_diag_file 19 kind
//          20 code 21 msg 22 cpaths 23 out_data 24 lib_roots 25 tmp_p
//   i[17]: 0 want_extern 1 n_lib 2 n_deps 3 asm_direct 4 n_imports 5 main_idx
//          6 pr_ok 7 ec 8 ec_dep 9 emit_ret 10 out_len 11 j 12 i 13 fail_tok
//          14 n_closure 15 rc 16 free_src_flag
//   z[5]:  0 src_len 1 raw_len 2 arena_sz 3 module_sz 4 dep_len
// Pointer table: .x has no *u8[N] product array type for BSS (fmt_argv XT001 history);
//   store 26× LP64 pointer slots in raw u8[208] via G.7 xlang_ptr_slot_get/set.
// Cold seed keeps C static arrays + memset reset; FROM_X drops pure-dup (no dual BSS).
// G.7: single hybrid authority for driver_x_emit_work_* under PREFER.

let g_xe_work_p_raw: u8[208] = [];
let g_xe_work_i: i32[17] = [];
let g_xe_work_z: usize[5] = [];

/** Zero all x_emit work pointer / i32 / size_t slots (same effect as cold memset).
 * Wave16 pure. PLATFORM: SHARED — hybrid pure authority. */
#[no_mangle]
export function driver_x_emit_work_reset(): void {
  unsafe {
    let j: i32 = 0;
    while (j < 26) {
      xlang_ptr_slot_set(&g_xe_work_p_raw[0], j, 0 as *u8);
      j = j + 1;
    }
    j = 0;
    while (j < 17) {
      g_xe_work_i[j] = 0;
      j = j + 1;
    }
    j = 0;
    while (j < 5) {
      g_xe_work_z[j] = 0 as usize;
      j = j + 1;
    }
  }
}

/** Load work pointer slot i (0..25); out of range → null.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_p_get(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= 26) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_ptr_slot_get(&g_xe_work_p_raw[0], i);
  }
  return 0 as *u8;
}

/** Store work pointer slot i (0..25); out of range is a no-op.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_p_set(i: i32, v: *u8): void {
  if (i < 0) {
    return;
  }
  if (i >= 26) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(&g_xe_work_p_raw[0], i, v);
  }
}

/** Load work i32 slot i (0..16); out of range → 0.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_i_get(i: i32): i32 {
  if (i < 0) {
    return 0;
  }
  if (i >= 17) {
    return 0;
  }
  return g_xe_work_i[i];
}

/** Store work i32 slot i (0..16); out of range is a no-op.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_i_set(i: i32, v: i32): void {
  if (i < 0) {
    return;
  }
  if (i >= 17) {
    return;
  }
  g_xe_work_i[i] = v;
}

/** Load work size_t slot i (0..4); out of range → 0.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_z_get(i: i32): usize {
  if (i < 0) {
    return 0 as usize;
  }
  if (i >= 5) {
    return 0 as usize;
  }
  return g_xe_work_z[i];
}

/** Store work size_t slot i (0..4); out of range is a no-op.
 * Wave16 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_x_emit_work_z_set(i: i32, v: usize): void {
  if (i < 0) {
    return;
  }
  if (i >= 5) {
    return;
  }
  g_xe_work_z[i] = v;
}

/** Free x_emit pipeline temporaries held in work slots, then reset all slots.
 * Frees per-dep arena/module/src/path rows (n_deps = i[2]), the five dep table
 * bases (p[6..10]), out_buf (p[11]), pctx via pipeline_dep_ctx_heap_destroy (p[12]),
 * arena/module/src (p[3]/p[4]/p[1]), and kind/code/msg (p[19..21]).
 * free(null) is safe. Wave16 pure; matches cold seed order.
 * PLATFORM: SHARED — hybrid pure authority under PREFER. */
#[no_mangle]
export function driver_x_emit_work_cleanup(): void {
  unsafe {
    let n: i32 = g_xe_work_i[2];
    let ds: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 6);
    let dp: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 7);
    let dl: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 8);
    let da: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 9);
    let dm: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 10);
    let i: i32 = 0;
    while (i < n) {
      if (da != 0 as *u8) {
        free(xlang_ptr_slot_get(da, i));
      }
      if (dm != 0 as *u8) {
        free(xlang_ptr_slot_get(dm, i));
      }
      if (ds != 0 as *u8) {
        free(xlang_ptr_slot_get(ds, i));
      }
      if (dp != 0 as *u8) {
        free(xlang_ptr_slot_get(dp, i));
      }
      i = i + 1;
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 11));
    let pctx: *u8 = xlang_ptr_slot_get(&g_xe_work_p_raw[0], 12);
    if (pctx != 0 as *u8) {
      pipeline_dep_ctx_heap_destroy(pctx);
    }
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 3));
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 4));
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 1));
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 19));
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 20));
    free(xlang_ptr_slot_get(&g_xe_work_p_raw[0], 21));
  }
  driver_x_emit_work_reset();
}

// ---- Wave25 Cap residual pure: tmp path BSS slots (PLATFORM: SHARED) ----
// open_out (wave27 pure) writes only via accessors; hybrid pure owns BSS (no dual static).
// Caps: asm 64 bytes (mkstemp path); parsed slot 64; parsed buf 256 (Windows long TEMP).
// Cold seed keeps C static + accessor twins under #ifndef XLANG_L2_RDABI_THIN_FROM_X.
// Defined before work_reset so pure reset can call same-TU accessors.

let g_driver_asm_tmp_path_slot: u8[128] = [];
let g_driver_parsed_tmp_c_slot: u8[128] = [];
let g_driver_parsed_tmp_c_buf: u8[256] = [];

/**
 * Return the 64-byte BSS slot used as mkstemp path for asm want-exe temp object.
 * @return *u8 — base of g_driver_asm_tmp_path_slot (never null); capacity 64 including NUL
 * Caller (rt_ab_step_open_out / driver_asm_mkstemp_fdopen) fills the template and path.
 * Wave25 pure. Work reset clears byte 0. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_asm_tmp_path_slot(): *u8 {
  return &g_driver_asm_tmp_path_slot[0];
}

/**
 * Return the 64-byte parsed tmp slot (parity with cold memset path; work reset clears [0]).
 * @return *u8 — base of g_driver_parsed_tmp_c_slot (never null); capacity 64
 * Wave25 pure. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_parsed_tmp_c_slot(): *u8 {
  return &g_driver_parsed_tmp_c_slot[0];
}

/**
 * Return the 256-byte path buffer filled by driver_parsed_open_out_file (wave27 pure).
 * @return *u8 — base of g_driver_parsed_tmp_c_buf (never null); capacity 256 including NUL
 * open_out writes only through this accessor (wave25); cleanup may unlink when p[20] empty.
 * Wave25 pure. PLATFORM: SHARED — size matches Windows long TEMP paths.
 */
#[no_mangle]
export function driver_parsed_tmp_c_buf(): *u8 {
  return &g_driver_parsed_tmp_c_buf[0];
}

// ---- Wave17 Cap residual pure: driver_asm_work BSS + cleanup (PLATFORM: SHARED) ----
// Slot map (must match seed comment + rt_run_asm_backend.x consumers):
//   p[25]: 0 path 1 src 2 out_path 3 arena 4 module 5 entry 6 dsrc 7 dpath 8 dlens
//          9 dar 10 dmod 11 out_buf 12 pctx 13 kind 14 code 15 msg 16 lib 17 target
//          18 argv 19 asm_out 20 elf 21 defines 22 tmp_path 23 one_ctx 24 dep_out
//   i[16]: 0 nlib 1 ndeps 2 nimp 3 main 4 emit_elf 5 want_exe 6 smoke 7 ndef 8 argc
//          9 ec 10 j 11 entry_only 12 skip_dep_load 13 rc 14 n_closure 15 num_funcs
//   z[4]:  0 src_len 1 asz 2 msz 3 dep_len
// Pointer table: 25× LP64 slots in raw u8[200] via G.7 xlang_ptr_slot_get/set.
// reset also clears driver_asm_tmp_path_slot()[0] (wave25 pure owns 64-byte BSS).
// cleanup: ndeps=i[1]; free dep rows; free table bases; free out_buf; destroy pctx;
//   fclose asm_out (p[19]); free elf/arena/module/src/kind/code/msg; then reset.
// Cold seed keeps C static arrays + memset twin; FROM_X drops pure-dup (no dual BSS).
// G.7: single hybrid authority for driver_asm_work_* under PREFER.

let g_asm_work_p_raw: u8[200] = [];
let g_asm_work_i: i32[16] = [];
let g_asm_work_z: usize[4] = [];

/** Zero all asm work pointer / i32 / size_t slots and clear tmp-path first byte.
 * Wave17 pure. PLATFORM: SHARED — hybrid pure authority. */
#[no_mangle]
export function driver_asm_work_reset(): void {
  unsafe {
    let j: i32 = 0;
    while (j < 25) {
      xlang_ptr_slot_set(&g_asm_work_p_raw[0], j, 0 as *u8);
      j = j + 1;
    }
    j = 0;
    while (j < 16) {
      g_asm_work_i[j] = 0;
      j = j + 1;
    }
    j = 0;
    while (j < 4) {
      g_asm_work_z[j] = 0 as usize;
      j = j + 1;
    }
    // Match cold: clear first byte of asm tmp-path BSS (wave25 pure slot).
    let tmp: *u8 = driver_asm_tmp_path_slot();
    if (tmp != 0 as *u8) {
      tmp[0] = 0;
    }
  }
}

/** Load asm work pointer slot i (0..24); out of range → null.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_p_get(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= 25) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_ptr_slot_get(&g_asm_work_p_raw[0], i);
  }
  return 0 as *u8;
}

/** Store asm work pointer slot i (0..24); out of range is a no-op.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_p_set(i: i32, v: *u8): void {
  if (i < 0) {
    return;
  }
  if (i >= 25) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(&g_asm_work_p_raw[0], i, v);
  }
}

/** Load asm work i32 slot i (0..15); out of range → 0.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_i_get(i: i32): i32 {
  if (i < 0) {
    return 0;
  }
  if (i >= 16) {
    return 0;
  }
  return g_asm_work_i[i];
}

/** Store asm work i32 slot i (0..15); out of range is a no-op.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_i_set(i: i32, v: i32): void {
  if (i < 0) {
    return;
  }
  if (i >= 16) {
    return;
  }
  g_asm_work_i[i] = v;
}

/** Load asm work size_t slot i (0..3); out of range → 0.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_z_get(i: i32): usize {
  if (i < 0) {
    return 0 as usize;
  }
  if (i >= 4) {
    return 0 as usize;
  }
  return g_asm_work_z[i];
}

/** Store asm work size_t slot i (0..3); out of range is a no-op.
 * Wave17 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_asm_work_z_set(i: i32, v: usize): void {
  if (i < 0) {
    return;
  }
  if (i >= 4) {
    return;
  }
  g_asm_work_z[i] = v;
}

/** Free asm pipeline temporaries held in work slots, then reset all slots.
 * Frees per-dep arena/module/src/path rows (n_deps = i[1]), the five dep table
 * bases (p[6..10]), out_buf (p[11]), pctx via pipeline_dep_ctx_heap_destroy (p[12]),
 * asm_out via driver_asm_fclose (p[19]), elf (p[20]), arena/module/src (p[3]/p[4]/p[1]),
 * and kind/code/msg (p[13..15]). free(null)/fclose(null) are safe.
 * Wave17 pure; matches cold seed order. PLATFORM: SHARED — hybrid pure under PREFER. */
#[no_mangle]
export function driver_asm_work_cleanup(): void {
  unsafe {
    let n: i32 = g_asm_work_i[1];
    let ds: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 6);
    let dp: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 7);
    let dl: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 8);
    let da: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 9);
    let dm: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 10);
    let i: i32 = 0;
    while (i < n) {
      if (da != 0 as *u8) {
        free(xlang_ptr_slot_get(da, i));
      }
      if (dm != 0 as *u8) {
        free(xlang_ptr_slot_get(dm, i));
      }
      if (ds != 0 as *u8) {
        free(xlang_ptr_slot_get(ds, i));
      }
      if (dp != 0 as *u8) {
        free(xlang_ptr_slot_get(dp, i));
      }
      i = i + 1;
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 11));
    let pctx: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 12);
    if (pctx != 0 as *u8) {
      pipeline_dep_ctx_heap_destroy(pctx);
    }
    let asm_out: *u8 = xlang_ptr_slot_get(&g_asm_work_p_raw[0], 19);
    if (asm_out != 0 as *u8) {
      driver_asm_fclose(asm_out);
    }
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 20));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 3));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 4));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 1));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 13));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 14));
    free(xlang_ptr_slot_get(&g_asm_work_p_raw[0], 15));
  }
  driver_asm_work_reset();
}

// ---- Wave18 Cap residual pure: driver_parsed_work BSS + cleanup (PLATFORM: SHARED) ----
// Slot map (must match seed comment + rt_run_compiler_parsed.x consumers):
//   p[24]: 0 path 1 src 2 out_path 3 arena 4 module 5 entry 6 dsrc 7 dpath 8 dlens
//          9 dar 10 dmod 11 out_buf 12 pctx 13 kind 14 code 15 msg 16 lib 17 opt
//          18 argv 19 cf 20 tmp_c 21 target 22 defs 23 (reserved / NP pad)
//   i[14]: 0 nlib 1 ndeps 2 nimp 3 main 4 want_asm 5 emit_stdout 6 ndef 7 use_lto
//          8 argc 9 ec 10 j 11 check 12 n_funcs 13 (pad)
//   z[4]:  0 src_len 1 asz 2 msz 3 (pad)
// Pointer table: 24× LP64 slots in raw u8[192] via G.7 xlang_ptr_slot_get/set.
// reset also clears driver_parsed_tmp_c_slot()[0] + driver_parsed_tmp_c_buf()[0] (wave25 pure).
// cleanup: ndeps=i[1]; free dep rows; free table bases; free out_buf; destroy pctx;
//   if !emit_stdout (i[5]): fclose cf (p[19]), unlink tmp_c (p[20] or pure/seed buf);
//   free arena/module/src/kind/code/msg/tmp_c heap; then reset.
// Cold seed keeps C static arrays + memset twin; FROM_X drops pure-dup (no dual BSS).
// G.7: single hybrid authority for driver_parsed_work_* under PREFER.

let g_parsed_work_p_raw: u8[192] = [];
let g_parsed_work_i: i32[14] = [];
let g_parsed_work_z: usize[4] = [];

/** Zero all parsed work pointer / i32 / size_t slots and clear tmp path first bytes.
 * Wave18 pure. PLATFORM: SHARED — hybrid pure authority. */
#[no_mangle]
export function driver_parsed_work_reset(): void {
  unsafe {
    let j: i32 = 0;
    while (j < 24) {
      xlang_ptr_slot_set(&g_parsed_work_p_raw[0], j, 0 as *u8);
      j = j + 1;
    }
    j = 0;
    while (j < 14) {
      g_parsed_work_i[j] = 0;
      j = j + 1;
    }
    j = 0;
    while (j < 4) {
      g_parsed_work_z[j] = 0 as usize;
      j = j + 1;
    }
    // Match cold: clear first bytes of parsed tmp slots (wave25 pure BSS).
    let slot: *u8 = driver_parsed_tmp_c_slot();
    if (slot != 0 as *u8) {
      slot[0] = 0;
    }
    let buf: *u8 = driver_parsed_tmp_c_buf();
    if (buf != 0 as *u8) {
      buf[0] = 0;
    }
  }
}

/** Load parsed work pointer slot i (0..23); out of range → null.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_p_get(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= 24) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_ptr_slot_get(&g_parsed_work_p_raw[0], i);
  }
  return 0 as *u8;
}

/** Store parsed work pointer slot i (0..23); out of range is a no-op.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_p_set(i: i32, v: *u8): void {
  if (i < 0) {
    return;
  }
  if (i >= 24) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(&g_parsed_work_p_raw[0], i, v);
  }
}

/** Load parsed work i32 slot i (0..13); out of range → 0.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_i_get(i: i32): i32 {
  if (i < 0) {
    return 0;
  }
  if (i >= 14) {
    return 0;
  }
  return g_parsed_work_i[i];
}

/** Store parsed work i32 slot i (0..13); out of range is a no-op.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_i_set(i: i32, v: i32): void {
  if (i < 0) {
    return;
  }
  if (i >= 14) {
    return;
  }
  g_parsed_work_i[i] = v;
}

/** Load parsed work size_t slot i (0..3); out of range → 0.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_z_get(i: i32): usize {
  if (i < 0) {
    return 0 as usize;
  }
  if (i >= 4) {
    return 0 as usize;
  }
  return g_parsed_work_z[i];
}

/** Store parsed work size_t slot i (0..3); out of range is a no-op.
 * Wave18 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_parsed_work_z_set(i: i32, v: usize): void {
  if (i < 0) {
    return;
  }
  if (i >= 4) {
    return;
  }
  g_parsed_work_z[i] = v;
}

/** Free parsed pipeline temporaries held in work slots, then reset all slots.
 * Frees per-dep arena/module/src/path rows (n_deps = i[1]), the five dep table
 * bases (p[6..10]), out_buf (p[11]), pctx via pipeline_dep_ctx_heap_destroy (p[12]),
 * then if emit_stdout (i[5]) is 0: driver_parsed_fclose(cf p[19]) and unlink tmp_c
 * (p[20] if non-empty, else seed driver_parsed_tmp_c_buf). Finally free arena/module/src
 * (p[3]/p[4]/p[1]), kind/code/msg (p[13..15]), and tmp_c heap (p[20]).
 *
 * CRITICAL: call ast_pool_arena_release / ast_pool_module_release before free on
 * every arena/module pointer. free alone leaves process-wide g_arena_sc /
 * g_module_sc slots used with dangling keys; the next malloc may reuse the same
 * address and reattach stale GrowVec data. That is why single-file
 * `xlang check file.x` is green while `xlang check compiler` truncates large
 * files (e.g. runtime_pipeline_abi num_funcs 363→111). Safe no-op if already
 * released or null. Wave18 pure + wave1225 release-before-free; matches cold seed.
 * PLATFORM: SHARED — hybrid pure under PREFER.
 */
#[no_mangle]
export function driver_parsed_work_cleanup(): void {
  unsafe {
    let n: i32 = g_parsed_work_i[1];
    let emit_stdout: i32 = g_parsed_work_i[5];
    let ds: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 6);
    let dp: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 7);
    let dl: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 8);
    let da: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 9);
    let dm: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 10);
    let i: i32 = 0;
    while (i < n) {
      if (da != 0 as *u8) {
        let dep_a: *u8 = xlang_ptr_slot_get(da, i);
        if (dep_a != 0 as *u8) {
          ast_pool_arena_release(dep_a);
          free(dep_a);
        }
      }
      if (dm != 0 as *u8) {
        let dep_m: *u8 = xlang_ptr_slot_get(dm, i);
        if (dep_m != 0 as *u8) {
          ast_pool_module_release(dep_m);
          free(dep_m);
        }
      }
      if (ds != 0 as *u8) {
        free(xlang_ptr_slot_get(ds, i));
      }
      if (dp != 0 as *u8) {
        free(xlang_ptr_slot_get(dp, i));
      }
      i = i + 1;
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 11));
    let pctx: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 12);
    if (pctx != 0 as *u8) {
      pipeline_dep_ctx_heap_destroy(pctx);
    }
    // Match cold: only fclose+unlink when not writing to stdout.
    if (emit_stdout == 0) {
      let cf: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 19);
      if (cf != 0 as *u8) {
        driver_parsed_fclose(cf);
        let tmpc: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 20);
        if (tmpc != 0 as *u8) {
          if (tmpc[0] != 0) {
            unlink(tmpc);
          } else {
            let seed_tmp: *u8 = driver_parsed_tmp_c_buf();
            if (seed_tmp != 0 as *u8) {
              if (seed_tmp[0] != 0) {
                unlink(seed_tmp);
              }
            }
          }
        } else {
          let seed_tmp2: *u8 = driver_parsed_tmp_c_buf();
          if (seed_tmp2 != 0 as *u8) {
            if (seed_tmp2[0] != 0) {
              unlink(seed_tmp2);
            }
          }
        }
      }
    }
    {
      let arena: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 3);
      let module: *u8 = xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 4);
      if (arena != 0 as *u8) {
        ast_pool_arena_release(arena);
        free(arena);
      }
      if (module != 0 as *u8) {
        ast_pool_module_release(module);
        free(module);
      }
    }
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 1));
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 13));
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 14));
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 15));
    free(xlang_ptr_slot_get(&g_parsed_work_p_raw[0], 20));
  }
  driver_parsed_work_reset();
}

// ---- Wave19 Cap residual pure: PipelineDepCtx i32 field get/set (PLATFORM: SHARED LP64) ----
// Cold seed: ((struct ast_PipelineDepCtx *)ctx)->field = v.
// PREFER hybrid: authority in this thin TU via fixed LP64 offsetof + driver_abi_{load,store}_i32_le
//   (same host-layout pattern as wave14 OutBuf len cell).
// Layout authority: compiler/src/runtime_pipeline_abi.h struct ast_PipelineDepCtx
//   (must stay identical to ast.x PipelineDepCtx). Offsets verified with offsetof on LP64.
// wave23: calloc + host_defaults pure (pipeline_sizeof_* / OS residual for host #ifdef).
// G.7: single product authority for driver_pipeline_dep_ctx_{set,get}_* under hybrid;
//   typed pipeline.x path still uses pipeline_dep_ctx_* in ast_pool (typed *PipelineDepCtx).
// PLATFORM: SHARED LP64 (Ubuntu x86_64 + Darwin arm64/x86_64). Not MS64 field packing.

/** offsetof(ast_PipelineDepCtx, use_asm_backend) on LP64 host layout. */
function driver_abi_pctx_off_use_asm(): i32 {
  return 8389660;
}

/** offsetof(ast_PipelineDepCtx, target_arch) on LP64. */
function driver_abi_pctx_off_target_arch(): i32 {
  return 8389664;
}

/** offsetof(ast_PipelineDepCtx, target_cpu_features) on LP64. */
function driver_abi_pctx_off_target_cpu_features(): i32 {
  return 8389668;
}

/** offsetof(ast_PipelineDepCtx, use_macho_o) on LP64. */
function driver_abi_pctx_off_use_macho_o(): i32 {
  return 8389672;
}

/** offsetof(ast_PipelineDepCtx, use_coff_o) on LP64. */
function driver_abi_pctx_off_use_coff_o(): i32 {
  return 8389676;
}

/** offsetof(ast_PipelineDepCtx, skip_codegen_dep_0) on LP64. */
function driver_abi_pctx_off_skip_codegen_dep_0(): i32 {
  return 8389692;
}

/** offsetof(ast_PipelineDepCtx, entry_already_parsed) on LP64. */
function driver_abi_pctx_off_entry_already_parsed(): i32 {
  return 8389696;
}

/** offsetof(ast_PipelineDepCtx, asm_entry_module_only) on LP64. */
function driver_abi_pctx_off_asm_entry_module_only(): i32 {
  return 8389808;
}

/** Store pctx->use_asm_backend = v. Null ctx is a no-op.
 * Wave19 pure: LP64 offsetof + LE i32 store (no C struct in .x).
 * PLATFORM: SHARED LP64 — pure under PREFER hybrid; cold seed keeps C field write. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_use_asm(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_use_asm(), v);
}

/** Store pctx->target_arch = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_target_arch(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_target_arch(), v);
}

/** Store pctx->target_cpu_features = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_target_cpu_features(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_target_cpu_features(), v);
}

/** Store pctx->use_macho_o = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_use_macho_o(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_use_macho_o(), v);
}

/** Store pctx->use_coff_o = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_use_coff_o(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_use_coff_o(), v);
}

/** Store pctx->entry_already_parsed = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_entry_already_parsed(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_entry_already_parsed(), v);
}

/** Store pctx->asm_entry_module_only = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_asm_entry_module_only(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_asm_entry_module_only(), v);
}

/** Read pctx->asm_entry_module_only. Null ctx → 0.
 * Wave19 pure: LP64 offsetof + LE i32 load. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_get_asm_entry_module_only(ctx: *u8): i32 {
  if (ctx == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(ctx, driver_abi_pctx_off_asm_entry_module_only());
}

/** Read pctx->use_macho_o. Null ctx → 0.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_get_use_macho_o(ctx: *u8): i32 {
  if (ctx == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(ctx, driver_abi_pctx_off_use_macho_o());
}

/** Read pctx->use_coff_o. Null ctx → 0.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_get_use_coff_o(ctx: *u8): i32 {
  if (ctx == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(ctx, driver_abi_pctx_off_use_coff_o());
}

/** Store pctx->skip_codegen_dep_0 = v. Null ctx is a no-op.
 * Wave19 pure. PLATFORM: SHARED LP64. */
#[no_mangle]
export function driver_pipeline_dep_ctx_set_skip_codegen_dep_0(ctx: *u8, v: i32): void {
  if (ctx == 0 as *u8) {
    return;
  }
  driver_abi_store_i32_le(ctx, driver_abi_pctx_off_skip_codegen_dep_0(), v);
}

// ---- Wave20 Cap residual pure: rt_preamble line_at/count bridge (PLATFORM: SHARED) ----
// Cap-giant-string data authority stays in seeds/rt_preamble.from_x.c
//   (driver_preamble_io_net_lines[] / fs_path_lines[] + _n). .x cannot host giant string tables.
// Hybrid pure owns the public line_at/count surface used by rt_preamble.x write_* loops.
// Always-seed residual: driver_preamble_*_lines_raw() = base of pointer table (LP64 *u8 slots).
// Index via G.7 xlang_ptr_slot_get (same authority as defines_set_at / work_p).
// Counts are fixed to match sizeof(...)/sizeof(*...) in rt_preamble.from_x.c
// (wave29 re-count: io_net=224 / fs_path=21; was 219 after preamble rows grew).
// When adding/removing a table row, update N here in the same commit as the C table.
// Cold seed keeps C line_at/count twins (uses *_lines_n from sizeof); FROM_X rest drops pure-dup (H↓).
// Wave22 pure: driver_preamble_fputs (g05 FILE* cast helper). Still seed: giant string text tables.

/**
 * Fixed io_net preamble line count (must match driver_preamble_io_net_lines_n).
 * @return i32 — 224 (wave29; sizeof table / sizeof slot)
 * PLATFORM: SHARED — wave20 pure; wave29 N sync with seeds/rt_preamble.from_x.c.
 */
function driver_abi_preamble_io_net_n(): i32 {
  return 224;
}

/** Fixed fs_path preamble line count (must match driver_preamble_fs_path_lines_n).
 * PLATFORM: SHARED — wave20 pure; keep in sync with seeds/rt_preamble.from_x.c. */
function driver_abi_preamble_fs_path_n(): i32 {
  return 21;
}

/** Return the i-th io_net Cap-giant-string preamble line (C string as *u8).
 * Out-of-range or negative i → null. Null table base → null.
 * Wave20 pure: bounds + G.7 xlang_ptr_slot_get on always-seed raw base.
 * extern calls (raw + ptr_slot) require unsafe (same as wave16 work_p_get).
 * PLATFORM: SHARED — pure authority under PREFER hybrid; cold seed keeps C index. */
#[no_mangle]
export function driver_preamble_io_net_line_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= driver_abi_preamble_io_net_n()) {
    return 0 as *u8;
  }
  unsafe {
    let base: *u8 = driver_preamble_io_net_lines_raw();
    if (base == 0 as *u8) {
      return 0 as *u8;
    }
    return xlang_ptr_slot_get(base, i);
  }
  return 0 as *u8;
}

/**
 * Number of io_net Cap-giant-string preamble lines (224).
 * @return i32 — fixed N; must match seeds/rt_preamble.from_x.c table size
 * Wave20 pure; wave29 N sync. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_preamble_io_net_line_count(): i32 {
  return driver_abi_preamble_io_net_n();
}

/** Return the i-th fs_path Cap-giant-string preamble line (C string as *u8).
 * Out-of-range or negative i → null. Null table base → null.
 * Wave20 pure: bounds + G.7 xlang_ptr_slot_get on always-seed raw base.
 * extern calls require unsafe. PLATFORM: SHARED. */
#[no_mangle]
export function driver_preamble_fs_path_line_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= driver_abi_preamble_fs_path_n()) {
    return 0 as *u8;
  }
  unsafe {
    let base: *u8 = driver_preamble_fs_path_lines_raw();
    if (base == 0 as *u8) {
      return 0 as *u8;
    }
    return xlang_ptr_slot_get(base, i);
  }
  return 0 as *u8;
}

/** Number of fs_path Cap-giant-string preamble lines (21).
 * Wave20 pure. PLATFORM: SHARED. */
#[no_mangle]
export function driver_preamble_fs_path_line_count(): i32 {
  return driver_abi_preamble_fs_path_n();
}

// ---- Wave21 Cap residual pure: driver_entry_fmt_argv_slot (PLATFORM: SHARED) ----
// Cold seed: static char *[2] = {"xlang","fmt"} + slot getter.
// Product .x cannot host *u8[2] / char*[2] lit-array init (typeck XT001 history).
// Pure path (same as fmt_check_cmd_thin check_argv / wave16 work_p):
//   - C strings as module BSS byte arrays (ASCII, trailing NUL)
//   - argv table as 2× LP64 pointer slots in raw u8[16]
//   - first call: G.7 xlang_ptr_slot_set slots 0/1 → lit bases
//   - return base of raw table (ABI = char ** / **u8 for driver_run_fmt)
// G.7: single hybrid authority under PREFER; FROM_X rest drops pure-dup.
// Return type *u8 is the opaque base of the pointer table (same ABI width as char **).

// ASCII "xlang\0"
let g_driver_entry_fmt_argv_lit0: u8[6] = [120, 108, 97, 110, 103, 0];
// ASCII "fmt\0"
let g_driver_entry_fmt_argv_lit1: u8[4] = [102, 109, 116, 0];
// 2 × 8-byte LP64 pointer slots (char *[2] layout)
let g_driver_entry_fmt_argv_raw: u8[16] = [];
// 0 = not yet filled; 1 = slots 0/1 point at lit0/lit1
let g_driver_entry_fmt_argv_ready: i32 = 0;

/** Return fixed argv table for driver_run_fmt when no user paths (argc=2).
 * Layout: [0]="xlang", [1]="fmt" as *u8 C strings (NUL-terminated BSS lits).
 * Wave21 pure: no char*[2] lit init; lazy G.7 xlang_ptr_slot_set into raw u8[16].
 * Returns base of the 2-slot pointer table (ABI-compatible with char ** / **u8).
 * PLATFORM: SHARED — pure authority under PREFER hybrid; cold seed keeps C static. */
#[no_mangle]
export function driver_entry_fmt_argv_slot(): *u8 {
  if (g_driver_entry_fmt_argv_ready == 0) {
    unsafe {
      xlang_ptr_slot_set(&g_driver_entry_fmt_argv_raw[0], 0, &g_driver_entry_fmt_argv_lit0[0]);
      xlang_ptr_slot_set(&g_driver_entry_fmt_argv_raw[0], 1, &g_driver_entry_fmt_argv_lit1[0]);
    }
    g_driver_entry_fmt_argv_ready = 1;
  }
  return &g_driver_entry_fmt_argv_raw[0];
}

// ---- Wave22 Cap residual pure: driver_preamble_fputs (PLATFORM: SHARED) ----
// G.7 authority for opaque *u8 stream → libc fputs (rt_preamble + async emit pure).
// .x cannot name FILE*; direct fputs(*u8,*u8) fails host-cc under
// -Werror=incompatible-pointer-types. Cast residual lives in g05_try_x_to_o prologue
// as static inline xlang_driver_fputs_opaque (same pattern as xlang_fmt_opendir/DIR*).
// Cold seed keeps C twin with (FILE*)(void*) cast; FROM_X rest drops pure-dup (H↓).

/** g05 prologue: cast opaque *u8 args to const char* / FILE* then fputs.
 * PLATFORM: SHARED — harness residual only; not a second product authority. */
export extern "C" function xlang_driver_fputs_opaque(s: *u8, stream: *u8): i32;

/** Write C string s to opaque FILE* stream via fputs.
 * Null s or stream → -1. Otherwise returns libc fputs result (EOF → negative).
 * Wave22 pure: null guard in .x; FILE* cast via g05 xlang_driver_fputs_opaque.
 * G.7 single authority for Cap residual fputs (async/rt_preamble call this symbol).
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin. */
#[no_mangle]
export function driver_preamble_fputs(s: *u8, stream: *u8): i32 {
  if (s == 0 as *u8) {
    return -1;
  }
  if (stream == 0 as *u8) {
    return -1;
  }
  unsafe {
    return xlang_driver_fputs_opaque(s, stream);
  }
  return -1;
}

// ---- Wave23 Cap residual pure: calloc family + host_defaults (PLATFORM: SHARED LP64) ----
// G.7: product authority under PREFER hybrid thin; cold seed keeps C twins (sizeof / #ifdef).
// Sizes: outbuf = 9MiB data + i32 len (wave14 layout); dep_ctx/elf via pipeline_sizeof_*;
//   ptr/size table element = 8 on LP64; DiagContextSnapshot = 32 on LP64.
// host_defaults: field writes via wave19 setters; target substr via strstr + BSS needles;
//   host #ifdef arch/macho/coff via permanent OS residual helpers (seed rest always linked).
// Still seed: free/get/set/len/data table accessors; tmp path slots; giant tables.

/** libc zero-fill alloc. PLATFORM: SHARED. */
export extern "C" function calloc(nmemb: usize, size: usize): *u8;
/** libc heap alloc. PLATFORM: SHARED. */
export extern "C" function malloc(sz: usize): *u8;
/** libc memset. PLATFORM: SHARED. */
export extern "C" function memset(p: *u8, c: i32, n: usize): *u8;
/** libc strstr. PLATFORM: SHARED — target triple substring parse in host_defaults. */
export extern "C" function strstr(hay: *u8, needle: *u8): *u8;
/** Authority size of ast_PipelineDepCtx (pipeline_glue). PLATFORM: SHARED LP64. */
export extern "C" function pipeline_sizeof_dep_ctx(): usize;
/** Authority size of ElfCodegenCtx (0 when ELF ctx disabled). PLATFORM: SHARED. */
export extern "C" function pipeline_sizeof_elf_ctx(): usize;
/** Pending -mcpu feature bits from target_cpu pure. PLATFORM: SHARED. */
export extern "C" function driver_get_pending_target_cpu_features(): u32;
/** Host default target_arch when -target is null (1 = aarch64 on Apple arm64 host).
 * Permanent OS residual: seed #if __APPLE__ && __aarch64__. PLATFORM: MACOS arm64 vs SHARED.
 */
export extern "C" function xlang_driver_host_default_target_arch(): i32;
/** Prefer Mach-O object when emit_elf_o on Apple host. Permanent OS residual. PLATFORM: MACOS. */
export extern "C" function xlang_driver_host_prefer_macho(emit_elf_o: i32): i32;
/** Prefer COFF object when emit_elf_o on Windows/Cygwin host. Permanent OS residual. PLATFORM: WINDOWS. */
export extern "C" function xlang_driver_host_prefer_coff(emit_elf_o: i32): i32;

// Target-triple needles (NUL-terminated) for strstr in host_defaults.
// ASCII "aarch64\0"
let g_driver_host_needle_aarch64: u8[8] = [97, 97, 114, 99, 104, 54, 52, 0];
// ASCII "arm64\0"
let g_driver_host_needle_arm64: u8[6] = [97, 114, 109, 54, 52, 0];
// ASCII "riscv64\0"
let g_driver_host_needle_riscv64: u8[8] = [114, 105, 115, 99, 118, 54, 52, 0];
// ASCII "windows\0"
let g_driver_host_needle_windows: u8[8] = [119, 105, 110, 100, 111, 119, 115, 0];

/** Fixed sizeof(driver_codegen_outbuf_abi) on product LP64: 9*1024*1024 + 4.
 * Must match seed X_CODEGEN_OUTBUF_CAP_ABI + int32_t len (wave14 OutBuf layout).
 */
function driver_abi_sizeof_codegen_outbuf(): usize {
  return 9437188 as usize;
}

/** Fixed sizeof(DiagContextSnapshot) on LP64 (3×ptr + size_t + int + pad = 32). */
function driver_abi_sizeof_diag_snapshot(): usize {
  return 32 as usize;
}

/** LP64 pointer / size_t width in bytes. */
function driver_abi_sizeof_lp64_word(): usize {
  return 8 as usize;
}

/** Allocate zeroed CodegenOutBuf (9MiB data + i32 len).
 * Wave23 pure: calloc(1, fixed sizeof). PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_codegen_outbuf_calloc(): *u8 {
  unsafe {
    return calloc(1 as usize, driver_abi_sizeof_codegen_outbuf());
  }
  return 0 as *u8;
}

/** Allocate zeroed PipelineDepCtx via pipeline_sizeof_dep_ctx.
 * Wave23 pure: no C struct in .x. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_pipeline_dep_ctx_calloc(): *u8 {
  unsafe {
    let sz: usize = pipeline_sizeof_dep_ctx();
    if (sz == 0 as usize) {
      return 0 as *u8;
    }
    return calloc(1 as usize, sz);
  }
  return 0 as *u8;
}

/** Allocate zeroed void*[n] pointer table (LP64 element size 8).
 * n <= 0 → null. Wave23 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_ptr_table_calloc(n: i32): *u8 {
  if (n <= 0) {
    return 0 as *u8;
  }
  unsafe {
    return calloc(n as usize, driver_abi_sizeof_lp64_word());
  }
  return 0 as *u8;
}

/** Allocate zeroed size_t[n] table (LP64 element size 8).
 * n <= 0 → null. Wave23 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_size_table_calloc(n: i32): *u8 {
  if (n <= 0) {
    return 0 as *u8;
  }
  unsafe {
    return calloc(n as usize, driver_abi_sizeof_lp64_word());
  }
  return 0 as *u8;
}

/** Allocate zeroed DiagContextSnapshot (LP64 size 32).
 * Wave23 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_diag_snapshot_alloc(): *u8 {
  unsafe {
    return calloc(1 as usize, driver_abi_sizeof_diag_snapshot());
  }
  return 0 as *u8;
}

/** Allocate zeroed ElfCodegenCtx via pipeline_sizeof_elf_ctx + malloc/memset.
 * sz==0 (no ELF) → null. Wave23 pure. PLATFORM: SHARED (ELF size 0 on non-ELF builds).
 */
#[no_mangle]
export function driver_asm_elf_ctx_calloc(): *u8 {
  unsafe {
    let sz: usize = pipeline_sizeof_elf_ctx();
    if (sz == 0 as usize) {
      return 0 as *u8;
    }
    let p: *u8 = malloc(sz);
    if (p != 0 as *u8) {
      memset(p, 0, sz);
    }
    return p;
  }
  return 0 as *u8;
}

/**
 * Free an ElfCodegenCtx from driver_asm_elf_ctx_calloc.
 * @param p *u8 — heap pointer from elf_ctx_calloc; null is safe (free no-op)
 * @return void
 * Wave38 pure: pairs wave23 calloc; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_asm_elf_ctx_free(p: *u8): void {
  unsafe {
    free(p);
  }
}

/** Fill PipelineDepCtx host defaults from -target string and emit_elf_o flag.
 * Logic (matches cold seed twin):
 *   1) target_arch: 0 default; aarch64|arm64 → 1; riscv64 → 2
 *   2) target_cpu_features from driver_get_pending_target_cpu_features
 *   3) if target is null, host default arch (Apple aarch64 host → 1) via OS residual
 *   4) use_macho_o / use_coff_o: host #ifdef via OS residual when emit_elf_o;
 *      plus target contains "windows" → coff=1 when emit_elf_o
 * Field writes: wave19 pure setters (G.7). No C struct in .x.
 * PLATFORM: SHARED orch; MACOS/WINDOWS residual helpers only for host #ifdef.
 */
#[no_mangle]
export function driver_asm_pctx_apply_host_defaults(ctx: *u8, target: *u8, emit_elf_o: i32): void {
  let arch: i32 = 0;
  let feats: i32 = 0;
  let macho: i32 = 0;
  let coff: i32 = 0;
  let ha: i32 = 0;
  if (ctx == 0 as *u8) {
    return;
  }
  // Parse arch from -target triple (substring match).
  if (target != 0 as *u8) {
    unsafe {
      if (strstr(target, &g_driver_host_needle_aarch64[0]) != 0 as *u8) {
        arch = 1;
      }
      if (strstr(target, &g_driver_host_needle_arm64[0]) != 0 as *u8) {
        arch = 1;
      }
      if (strstr(target, &g_driver_host_needle_riscv64[0]) != 0 as *u8) {
        arch = 2;
      }
    }
  }
  driver_pipeline_dep_ctx_set_target_arch(ctx, arch);
  unsafe {
    feats = driver_get_pending_target_cpu_features() as i32;
  }
  driver_pipeline_dep_ctx_set_target_cpu_features(ctx, feats);
  // Host default arch only when -target is absent (seed: if (!t) on Apple aarch64).
  if (target == 0 as *u8) {
    unsafe {
      ha = xlang_driver_host_default_target_arch();
    }
    if (ha != 0) {
      driver_pipeline_dep_ctx_set_target_arch(ctx, ha);
    }
  }
  // Object format prefs: host platform residual + windows in triple.
  unsafe {
    macho = xlang_driver_host_prefer_macho(emit_elf_o);
    coff = xlang_driver_host_prefer_coff(emit_elf_o);
  }
  if (emit_elf_o != 0) {
    if (target != 0 as *u8) {
      unsafe {
        if (strstr(target, &g_driver_host_needle_windows[0]) != 0 as *u8) {
          coff = 1;
        }
      }
    }
  }
  driver_pipeline_dep_ctx_set_use_macho_o(ctx, macho);
  driver_pipeline_dep_ctx_set_use_coff_o(ctx, coff);
}

// ---- Wave24 Cap residual pure: table free/get/set + outbuf free/len/data (PLATFORM: SHARED) ----
// Pairs wave23 calloc family. Cold seed keeps C twins under #ifndef XLANG_L2_RDABI_THIN_FROM_X.
// Layout: CodegenOutBuf = data[9MiB] then i32 len at offset CAP (wave14 LE helpers).
// ptr table: void*[n] → G.7 xlang_ptr_slot_get/set. size table: size_t[n] → LE usize at i*8.

/**
 * Load little-endian usize at base+off (null / off < 0 → 0).
 * Module-local host layout helper for size_t tables (LP64 8-byte cells).
 * @param p *u8 — base address of the table or buffer; null-safe
 * @param off i32 — byte offset from p; negative → 0
 * @return usize — LE-decoded value, or 0 on invalid base/offset
 * PLATFORM: SHARED LP64.
 */
function driver_abi_load_usize_le(p: *u8, off: i32): usize {
  if (p == 0 as *u8) {
    return 0 as usize;
  }
  if (off < 0) {
    return 0 as usize;
  }
  unsafe {
    let m: usize = 256 as usize;
    let m2: usize = m * m;
    let m4: usize = m2 * m2;
    let a0: usize = p[off] as usize;
    let a1: usize = a0 + (p[off + 1] as usize) * m;
    let a2: usize = a1 + (p[off + 2] as usize) * m2;
    let a3: usize = a2 + (p[off + 3] as usize) * (m2 * m);
    let a4: usize = a3 + (p[off + 4] as usize) * m4;
    let a5: usize = a4 + (p[off + 5] as usize) * (m4 * m);
    let a6: usize = a5 + (p[off + 6] as usize) * (m4 * m2);
    let a7: usize = a6 + (p[off + 7] as usize) * (m4 * m2 * m);
    return a7;
  }
  return 0 as usize;
}

/**
 * Store little-endian usize at base+off (null / off < 0 no-op).
 * Module-local host layout helper for size_t tables (LP64 8-byte cells).
 * @param p *u8 — base address of the table or buffer; null-safe
 * @param off i32 — byte offset from p; negative → no-op
 * @param v usize — value to store little-endian
 * @return void
 * PLATFORM: SHARED LP64.
 */
function driver_abi_store_usize_le(p: *u8, off: i32, v: usize): void {
  if (p == 0 as *u8) {
    return;
  }
  if (off < 0) {
    return;
  }
  unsafe {
    // Same successive /256 + low-byte extract pattern as wave14 i32 LE store (no % op).
    let m: usize = 256 as usize;
    let b255: usize = 255 as usize;
    let u0: usize = v;
    p[off] = (u0 & b255) as u8;
    let u1: usize = u0 / m;
    p[off + 1] = (u1 & b255) as u8;
    let u2: usize = u1 / m;
    p[off + 2] = (u2 & b255) as u8;
    let u3: usize = u2 / m;
    p[off + 3] = (u3 & b255) as u8;
    let u4: usize = u3 / m;
    p[off + 4] = (u4 & b255) as u8;
    let u5: usize = u4 / m;
    p[off + 5] = (u5 & b255) as u8;
    let u6: usize = u5 / m;
    p[off + 6] = (u6 & b255) as u8;
    let u7: usize = u6 / m;
    p[off + 7] = (u7 & b255) as u8;
  }
}

/**
 * Free a CodegenOutBuf previously allocated by driver_codegen_outbuf_calloc.
 * @param p *u8 — heap pointer from outbuf_calloc; null is safe (free no-op)
 * @return void
 * Wave24 pure. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_codegen_outbuf_free(p: *u8): void {
  unsafe {
    free(p);
  }
}

/**
 * Read the live byte length of a CodegenOutBuf (i32 len after the 9MiB data[]).
 * @param p *u8 — outbuf pointer; null → 0
 * @return i32 — current len field (LE at offset CAP), or 0 if p is null
 * Wave24 pure: wave14 LE load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_codegen_outbuf_len(p: *u8): i32 {
  if (p == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(p, driver_abi_codegen_outbuf_cap());
}

/**
 * Return pointer to the data[] base of a CodegenOutBuf (first byte of the buffer).
 * @param p *u8 — outbuf pointer; null → null
 * @return *u8 — &data[0], same address as p on product layout (data is first field)
 * Wave24 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_codegen_outbuf_data(p: *u8): *u8 {
  if (p == 0 as *u8) {
    return 0 as *u8;
  }
  // Host layout: unsigned char data[CAP] is the first field; p is already data base.
  return p;
}

/**
 * Free a void* table from driver_ptr_table_calloc.
 * @param t *u8 — heap table; null is safe
 * @return void
 * Wave24 pure. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_ptr_table_free(t: *u8): void {
  unsafe {
    free(t);
  }
}

/**
 * Load pointer table slot i (LP64 void* element).
 * @param t *u8 — table from ptr_table_calloc; null → null
 * @param i i32 — index; i < 0 → null (no upper bound check; caller owns n)
 * @return *u8 — stored pointer at slot i, or null
 * Wave24 pure: G.7 xlang_ptr_slot_get. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_ptr_table_get(t: *u8, i: i32): *u8 {
  if (t == 0 as *u8) {
    return 0 as *u8;
  }
  if (i < 0) {
    return 0 as *u8;
  }
  // FFI: G.7 authority lives in pipeline C; Cap-T001 unsafe at call site.
  unsafe {
    return xlang_ptr_slot_get(t, i);
  }
  return 0 as *u8;
}

/**
 * Store pointer table slot i (LP64 void* element).
 * @param t *u8 — table from ptr_table_calloc; null → no-op
 * @param i i32 — index; i < 0 → no-op
 * @param p *u8 — value to store (may be null)
 * @return void
 * Wave24 pure: G.7 xlang_ptr_slot_set. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_ptr_table_set(t: *u8, i: i32, p: *u8): void {
  if (t == 0 as *u8) {
    return;
  }
  if (i < 0) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(t, i, p);
  }
}

/**
 * Free a size_t table from driver_size_table_calloc.
 * @param t *u8 — heap table; null is safe
 * @return void
 * Wave24 pure. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_size_table_free(t: *u8): void {
  unsafe {
    free(t);
  }
}

/**
 * Load size_t table slot i (LP64 8-byte LE cell at offset i*8).
 * @param t *u8 — table from size_table_calloc; null → 0
 * @param i i32 — index; i < 0 → 0
 * @return usize — stored size at slot i, or 0
 * Wave24 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_size_table_get(t: *u8, i: i32): usize {
  if (t == 0 as *u8) {
    return 0 as usize;
  }
  if (i < 0) {
    return 0 as usize;
  }
  // Element size 8: byte offset = i * 8.
  return driver_abi_load_usize_le(t, i * 8);
}

/**
 * Store size_t table slot i (LP64 8-byte LE cell at offset i*8).
 * @param t *u8 — table from size_table_calloc; null → no-op
 * @param i i32 — index; i < 0 → no-op
 * @param v usize — value to store
 * @return void
 * Wave24 pure. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_size_table_set(t: *u8, i: i32, v: usize): void {
  if (t == 0 as *u8) {
    return;
  }
  if (i < 0) {
    return;
  }
  driver_abi_store_usize_le(t, i * 8, v);
}

/**
 * Free a DiagContextSnapshot from driver_diag_snapshot_alloc.
 * @param s *u8 — heap snapshot; null is safe
 * @return void
 * Wave24 pure. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_diag_snapshot_free(s: *u8): void {
  unsafe {
    free(s);
  }
}

// ---- Wave26 Cap residual pure: parsed fclose + write_out (PLATFORM: SHARED) ----
// G.7 authority under PREFER hybrid thin; cold seed keeps C twins (FILE* cast).
// .x cannot name FILE* or compare to stdout — g05 prologue injects:
//   xlang_driver_stdout_ptr / xlang_driver_fclose_opaque / xlang_driver_fwrite_opaque
// (same harness pattern as wave22 xlang_driver_fputs_opaque).
// write_out calls write_io_net_abi_inline + write_fs_path_map_error_abi_inline
// (R2 pure in rt_preamble.x under PREFER; Cap-giant-string *data* + skip still seed-backed).
// min preamble via driver_preamble_fputs
// short lits (avoid long -E string cap). wave27 open_out; wave28 invoke_cc; still seed: giant tables.

/** g05 prologue: opaque identity of host stdout as *u8.
 * PLATFORM: SHARED — harness residual; product pure compares pointers only. */
export extern "C" function xlang_driver_stdout_ptr(): *u8;
/** g05 prologue: fclose((FILE*)stream); 0 success, 1 failure; null → 0.
 * PLATFORM: SHARED — harness FILE* cast residual. */
export extern "C" function xlang_driver_fclose_opaque(stream: *u8): i32;
/** g05 prologue: fwrite(data,1,len,FILE*); 0 full write, 1 fail; len==0 → 0.
 * @param data *u8 — bytes to write
 * @param len i32 — byte count; negative rejected as fail
 * @param stream *u8 — opaque FILE*
 * PLATFORM: SHARED — harness FILE* cast residual. */
export extern "C" function xlang_driver_fwrite_opaque(data: *u8, len: i32, stream: *u8): i32;
/** Always-seed rt_preamble: write io/net Cap-giant-string ABI block to opaque FILE*.
 * @param cf *u8 — FILE* as *u8 (product C ABI pointer-compatible with FILE*)
 * @return i32 — 0 success, non-zero fail
 * PLATFORM: SHARED — table+skip authority remains seeds/rt_preamble.from_x.c. */
export extern "C" function write_io_net_abi_inline(cf: *u8): i32;
/** Always-seed rt_preamble: write fs/path/map/error Cap-giant-string ABI block.
 * @param cf *u8 — FILE* as *u8
 * @return i32 — 0 success, non-zero fail
 * PLATFORM: SHARED. */
export extern "C" function write_fs_path_map_error_abi_inline(cf: *u8): i32;

/**
 * Close a parsed-pipeline C output FILE* (opaque *u8).
 * Null or stdout → no-op (stdout must stay open for -E emit-to-stdout).
 * @param fp *u8 — opaque FILE* from open_out / work slot; may be null or stdout
 * @return void
 * Wave26 pure: stdout identity via g05 xlang_driver_stdout_ptr; fclose via opaque.
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_fclose(fp: *u8): void {
  if (fp == 0 as *u8) {
    return;
  }
  unsafe {
    let so: *u8 = xlang_driver_stdout_ptr();
    if (fp == so) {
      return;
    }
    xlang_driver_fclose_opaque(fp);
  }
}

/**
 * Close a parsed-pipeline C output FILE* and report status.
 * Null or stdout → 0 (success no-op). Otherwise 0 if fclose succeeds, 1 on fail.
 * @param fp *u8 — opaque FILE*; may be null or stdout
 * @return i32 — 0 success / no-op, 1 fclose failure
 * Wave26 pure. PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_fclose_rc(fp: *u8): i32 {
  if (fp == 0 as *u8) {
    return 0;
  }
  unsafe {
    let so: *u8 = xlang_driver_stdout_ptr();
    if (fp == so) {
      return 0;
    }
    return xlang_driver_fclose_opaque(fp);
  }
  return 0;
}

/**
 * Write min-preamble include block used when generated C lacks leading # or comment.
 * Split into short fputs lits so -E string cap (~63) cannot truncate a single lit.
 * @param fp *u8 — opaque FILE*; non-null (caller validated)
 * @return i32 — 0 success, 1 if any fputs failed
 * Wave26 pure helper (not product export surface beyond write_out). PLATFORM: SHARED.
 */
function driver_parsed_write_min_preamble(fp: *u8): i32 {
  // Each lit is short; driver_preamble_fputs returns libc fputs result (EOF → negative).
  if (driver_preamble_fputs("/* generated */\n", fp) < 0) {
    return 1;
  }
  if (driver_preamble_fputs("#include <stdint.h>\n", fp) < 0) {
    return 1;
  }
  if (driver_preamble_fputs("#include <stddef.h>\n", fp) < 0) {
    return 1;
  }
  if (driver_preamble_fputs("#include <stdlib.h>\n", fp) < 0) {
    return 1;
  }
  if (driver_preamble_fputs("#include <stdio.h>\n", fp) < 0) {
    return 1;
  }
  if (driver_preamble_fputs("#include <string.h>\n", fp) < 0) {
    return 1;
  }
  return 0;
}

/**
 * Write pipeline C product to open FILE*: optional min preamble, first source line,
 * then io_net + fs_path Cap residual ABI tables, then remainder of data.
 * @param fp *u8 — opaque FILE* from open_out; null rejected
 * @param data *u8 — full generated C bytes; null rejected
 * @param len i32 — byte count of data; negative → fail; 0 still inserts preamble path
 * @return i32 — 0 success, 1 I/O or table-write failure
 * Wave26 pure: first-line scan + need_preamble gate in .x; fwrite via g05 opaque;
 * write_io_net / write_fs_path pure in rt_preamble.x; table data always seed (wave29).
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_write_out(fp: *u8, data: *u8, len: i32): i32 {
  if (fp == 0 as *u8) {
    return 1;
  }
  if (data == 0 as *u8) {
    return 1;
  }
  if (len < 0) {
    return 1;
  }
  // first_line = index just past first '\n' (or len if no newline).
  let first_line: i32 = 0;
  while (first_line < len) {
    if (data[first_line] == 10) {
      first_line = first_line + 1;
      break;
    }
    first_line = first_line + 1;
  }
  // need_preamble when body does not already start with '#' or '/*'.
  let need_preamble: i32 = 0;
  if (len > 0) {
    if (data[0] != 35) {
      // not '#'
      if (len < 2) {
        need_preamble = 1;
      } else {
        if (data[0] != 47) {
          // not '/'
          need_preamble = 1;
        } else {
          if (data[1] != 42) {
            // not '*'
            need_preamble = 1;
          }
        }
      }
    }
  }
  if (need_preamble != 0) {
    if (driver_parsed_write_min_preamble(fp) != 0) {
      return 1;
    }
  }
  unsafe {
    if (xlang_driver_fwrite_opaque(data, first_line, fp) != 0) {
      return 1;
    }
    if (write_io_net_abi_inline(fp) != 0) {
      return 1;
    }
    if (write_fs_path_map_error_abi_inline(fp) != 0) {
      return 1;
    }
    let rest: i32 = len - first_line;
    if (rest > 0) {
      // data + first_line as *u8 without pointer arithmetic type issues.
      let rest_p: *u8 = &data[first_line];
      if (xlang_driver_fwrite_opaque(rest_p, rest, fp) != 0) {
        return 1;
      }
    }
  }
  return 0;
}

// ---- Wave27 Cap residual pure: driver_parsed_open_out_file (PLATFORM: SHARED) ----
// G.7 authority under PREFER hybrid thin; cold seed keeps C twin (FILE* + snprintf).
// Cap residual split:
//   - seed always: xlang_driver_tmp_prefix (XLANG_TMP_PREFIX #ifdef; no platform ifdef in .x)
//   - g05 prologue: xlang_driver_fopen_write_opaque (FILE* cast; same pattern as wave22/26)
//   - libc via g05 unistd/stdio: mkstemp, close, rename, unlink
//   - pure orch: stdout gate, template build, close-before-rename (BLD001), path copy
// wave29: rt_preamble write pure already R2; residual = Cap-giant-string *data* only.
// wave29 also: pure io_net N 219→224 + WEAK_IO_BATCH skip 178..181 (seed/.x/surface).

/** Permanent OS residual: host temp path prefix for mkstemp templates.
 * @return *u8 — NUL-terminated C string; POSIX "/tmp/xlang_"; WINDOWS "xlang_"
 * PLATFORM: SHARED surface; body is #ifdef in seed rest (not pure-dup). */
export extern "C" function xlang_driver_tmp_prefix(): *u8;
/** POSIX mkstemp: mutate template ending in XXXXXX; return fd or -1.
 * PLATFORM: POSIX product path (win32_compat may provide on WINDOWS probes). */
export extern "C" function mkstemp(path: *u8): i32;
/** POSIX close(fd). PLATFORM: POSIX / win32_compat. */
export extern "C" function close(fd: i32): i32;
/** POSIX rename(old, new). PLATFORM: SHARED rename surface. */
export extern "C" function rename(old_path: *u8, new_path: *u8): i32;
/** g05 prologue: fopen(path, "w") as opaque *u8; null path → null.
 * PLATFORM: SHARED — harness FILE* cast residual. */
export extern "C" function xlang_driver_fopen_write_opaque(path: *u8): *u8;
/** Diag with single path + errno (runtime authority). */
export extern "C" function runtime_diag_errno_path(
  file: *u8, kind: *u8, op: *u8, path: *u8): void;
/** Diag with from/to path pair + errno (runtime authority). */
export extern "C" function runtime_diag_errno_path_pair(
  file: *u8, kind: *u8, op: *u8, from_path: *u8, to_path: *u8): void;

/**
 * Copy NUL-terminated src into dst with capacity cap (writes trailing NUL).
 * @param dst *u8 — destination; null → no-op
 * @param cap i32 — capacity including NUL; cap <= 0 → no-op
 * @param src *u8 — source C string; null treated as empty
 * @return void
 * Wave27 pure helper. PLATFORM: SHARED.
 */
function driver_open_out_cstr_copy(dst: *u8, cap: i32, src: *u8): void {
  if (dst == 0 as *u8) {
    return;
  }
  if (cap <= 0) {
    return;
  }
  if (cap == 1) {
    dst[0] = 0;
    return;
  }
  let i: i32 = 0;
  let max: i32 = cap - 1;
  if (src == 0 as *u8) {
    dst[0] = 0;
    return;
  }
  while (i < max) {
    let b: u8 = src[i];
    if (b == 0) {
      break;
    }
    dst[i] = b;
    i = i + 1;
  }
  dst[i] = 0;
}

/**
 * Append NUL-terminated src onto dst (dst must already be NUL-terminated).
 * @param dst *u8 — destination buffer; null → no-op
 * @param cap i32 — total capacity including NUL
 * @param src *u8 — suffix to append; null → no-op
 * @return void
 * Wave27 pure helper. PLATFORM: SHARED.
 */
function driver_open_out_cstr_cat(dst: *u8, cap: i32, src: *u8): void {
  if (dst == 0 as *u8) {
    return;
  }
  if (cap <= 0) {
    return;
  }
  if (src == 0 as *u8) {
    return;
  }
  let i: i32 = 0;
  while (i < cap) {
    if (dst[i] == 0) {
      break;
    }
    i = i + 1;
  }
  // i is current length; append until cap-1.
  let j: i32 = 0;
  while (i < (cap - 1)) {
    let b: u8 = src[j];
    if (b == 0) {
      break;
    }
    dst[i] = b;
    i = i + 1;
    j = j + 1;
  }
  if (i < cap) {
    dst[i] = 0;
  } else {
    dst[cap - 1] = 0;
  }
}

/**
 * Open pipeline C output: null out_path → stdout (emit_stdout=1); else mkstemp + rename .c + fopen "w".
 * @param out_path *u8 — product output path (diag file field); null means emit-to-stdout (-E style)
 * @param tmp_c_out64 *u8 — optional buffer for resulting .c path (cap >= 256 recommended); may be null
 * @param emit_stdout *i32 — out flag: 1 when returning stdout, else 0; may be null
 * @return *u8 — opaque FILE* (or stdout) on success; null on failure (diag already emitted)
 * Wave27 pure: stdout identity via g05 stdout_ptr; path BSS via wave25 accessor;
 * template = xlang_driver_tmp_prefix() + "xlang_x.XXXXXX"; close(fd) before rename (BLD001);
 * fopen via g05 opaque. PLATFORM: SHARED orch; WINDOWS|POSIX close-before-rename contract.
 */
#[no_mangle]
export function driver_parsed_open_out_file(
  out_path: *u8, tmp_c_out64: *u8, emit_stdout: *i32): *u8 {
  unsafe {
    if (emit_stdout != 0 as *i32) {
      emit_stdout[0] = 0;
    }
    let tbuf: *u8 = driver_parsed_tmp_c_buf();
    if (tbuf != 0 as *u8) {
      tbuf[0] = 0;
    }
    if (tmp_c_out64 != 0 as *u8) {
      tmp_c_out64[0] = 0;
    }
    // Emit-to-stdout path: no temp file; caller must not fclose stdout.
    if (out_path == 0 as *u8) {
      if (emit_stdout != 0 as *i32) {
        emit_stdout[0] = 1;
      }
      return xlang_driver_stdout_ptr();
    }
    if (tbuf == 0 as *u8) {
      return 0 as *u8;
    }
    // Stack template for mkstemp (mutates XXXXXX in place). Cap 128 matches cold twin.
    let tmp: u8[128] = [];
    let prefix: *u8 = xlang_driver_tmp_prefix();
    driver_open_out_cstr_copy(&tmp[0], 128, prefix);
    // Suffix is short; keep under -E string cap (~63).
    driver_open_out_cstr_cat(&tmp[0], 128, "xlang_x.XXXXXX");
    let fd: i32 = mkstemp(&tmp[0]);
    if (fd < 0) {
      runtime_diag_errno_path(out_path, "build error", "mkstemp", &tmp[0]);
      return 0 as *u8;
    }
    // PLATFORM: WINDOWS | POSIX — must close before rename (Windows sharing violation).
    close(fd);
    // tbuf = tmp + ".c" (cap 256 pure BSS).
    driver_open_out_cstr_copy(tbuf, 256, &tmp[0]);
    driver_open_out_cstr_cat(tbuf, 256, ".c");
    if (rename(&tmp[0], tbuf) != 0) {
      runtime_diag_errno_path_pair(out_path, "build error", "rename", &tmp[0], tbuf);
      unlink(&tmp[0]);
      return 0 as *u8;
    }
    let cf: *u8 = xlang_driver_fopen_write_opaque(tbuf);
    if (cf == 0 as *u8) {
      runtime_diag_errno_path(out_path, "build error", "fopen", tbuf);
      unlink(tbuf);
      return 0 as *u8;
    }
    // Optional copy of final .c path for work slots / invoke_cc.
    if (tmp_c_out64 != 0 as *u8) {
      driver_open_out_cstr_copy(tmp_c_out64, 256, tbuf);
    }
    return cf;
  }
  return 0 as *u8;
}

// ---- Wave28 Cap residual pure: driver_parsed_invoke_cc (PLATFORM: SHARED) ----
// G.7 authority under PREFER hybrid thin; cold seed keeps C twin (c_paths[1] + path pack).
// Cap residual split:
//   - product link authority: xlang_invoke_cc (+ set/clear user .o table)
//   - path resolvers: xlang_std_io_o_path / xlang_rel_o_path_from_argv0 /
//     xlang_runtime_panic_o_path / xlang_repo_root_from_argv0 (same seed surface as cold)
//   - pure orch: null gate, default opt "2", c_paths pack via G.7 ptr_slot,
//     fail unlink+BLD001 (append+diag_report_with_code), KEEP_C note, success unlink tmp
// Cap residual data: rt_preamble giant string tables (io_net / fs_path) always seed.

/** Resolve std/io/io.o (or product empty F-06) from compiler argv0. */
export extern "C" function xlang_std_io_o_path(argv0: *u8): *u8;
/** Resolve repo-relative .o path from argv0 (e.g. "std/process/process.o").
 * @param argv0 *u8 — compiler argv[0]; may be null
 * @param rel *u8 — relative path under repo/compiler layout; non-null
 * @return *u8 — stable path string or null
 * PLATFORM: SHARED — link_abi authority. */
export extern "C" function xlang_rel_o_path_from_argv0(argv0: *u8, rel: *u8): *u8;
/** Resolve runtime_panic.o path from argv0. PLATFORM: SHARED. */
export extern "C" function xlang_runtime_panic_o_path(argv0: *u8): *u8;
/** Repo root directory from compiler argv0 (include_root for invoke_cc).
 * PLATFORM: SHARED. */
export extern "C" function xlang_repo_root_from_argv0(argv0: *u8): *u8;
/** Product C frontend host-cc link: fixed std/core .o list + scan-on-demand.
 * @param c_paths *u8 — opaque const char** (one-slot table from pure pack)
 * @param n i32 — number of .c paths (parsed pipeline uses 1)
 * @param out_path *u8 — product -o path; non-null
 * @param target *u8 — triple or null
 * @param opt_level *u8 — "0".."3"; pure default "2" when caller passes null
 * @param use_lto i32 — LTO flag
 * @param … remaining *u8 — optional std/core .o paths (null ok; impl may scan C)
 * @return i32 — 0 success, non-zero host-cc fail
 * PLATFORM: SHARED — runtime_link_abi authority. */
export extern "C" function xlang_invoke_cc(
  c_paths: *u8, n: i32, out_path: *u8, target: *u8, opt_level: *u8, use_lto: i32,
  io_o: *u8, fs_o: *u8, process_o: *u8, string_o: *u8, heap_o: *u8, path_o: *u8,
  runtime_o: *u8, runtime_panic_o: *u8, net_o: *u8, thread_o: *u8, time_o: *u8,
  random_o: *u8, env_o: *u8, sync_o: *u8, encoding_o: *u8, base64_o: *u8, crypto_o: *u8,
  log_o: *u8, atomic_o: *u8, channel_o: *u8, backtrace_o: *u8, hash_o: *u8, math_o: *u8,
  sort_o: *u8, ffi_o: *u8, db_o: *u8, elf_o: *u8, json_o: *u8, csv_o: *u8, regex_o: *u8,
  compress_o: *u8, unicode_o: *u8, dynlib_o: *u8, http_o: *u8, tar_o: *u8, simd_o: *u8,
  context_o: *u8, datetime_o: *u8, uuid_o: *u8, url_o: *u8, cli_o: *u8, security_o: *u8,
  config_o: *u8, cache_o: *u8, trace_o: *u8, task_o: *u8, schema_o: *u8, test_o: *u8,
  include_root: *u8, async_scheduler_o: *u8): i32;
/** G.7 single authority: plumb CLI user .o files into invoke_cc/ld link line.
 * @param argc i32 — argv length
 * @param argv *u8 — opaque char** (same as process argv)
 * PLATFORM: SHARED — set before invoke; clear after. */
export extern "C" function xlang_invoke_cc_set_user_o_files_from_argv(argc: i32, argv: *u8): void;
/** Clear user .o table after invoke (prevents stale pointers). PLATFORM: SHARED. */
export extern "C" function xlang_invoke_cc_clear_user_o_files(): void;
/** Unlink failed product -o path (best-effort). PLATFORM: SHARED. */
export extern "C" function driver_unlink_failed_output(out_path: *u8): void;

/**
 * Host-cc link step after open_out/write_out: pack std .o paths, invoke xlang_invoke_cc,
 * then unlink failed out or drop/keep generated tmp .c.
 * @param tmp_c *u8 — path to generated .c from open_out; null → fail 1
 * @param out_path *u8 — product -o path; null → fail 1
 * @param opt_level *u8 — opt level string; null → default "2"
 * @param use_lto i32 — LTO flag passed through to xlang_invoke_cc
 * @param argv0 *u8 — compiler argv[0] for path resolution; may be null
 * @param argc i32 — full argv count (user .o scan)
 * @param argv *u8 — opaque char** argv base (user .o scan)
 * @return i32 — 0 success, 1 host-cc fail (BLD001 already reported) or bad args
 * Wave28 pure: c_paths one-slot via G.7 xlang_ptr_slot_set; fail/KEEP_C via
 * append + diag_report(_with_code) (no va_list reportf).
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_invoke_cc(
  tmp_c: *u8, out_path: *u8, opt_level: *u8, use_lto: i32,
  argv0: *u8, argc: i32, argv: *u8): i32 {
  if (tmp_c == 0 as *u8) {
    return 1;
  }
  if (out_path == 0 as *u8) {
    return 1;
  }
  unsafe {
    let opt: *u8 = opt_level;
    if (opt == 0 as *u8) {
      opt = "2";
    }
    // c_paths[1] as raw LP64 pointer table (G.7; .x bans **u8 array lit).
    let c_paths_raw: u8[8] = [];
    xlang_ptr_slot_set(&c_paths_raw[0], 0, tmp_c);
    // Path pack mirrors cold seed twin (F-06 nulls for scan-on-demand modules).
    let a0: *u8 = argv0;
    let io_o: *u8 = xlang_std_io_o_path(a0);
    let fs_o: *u8 = 0 as *u8;
    let process_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/process/process.o");
    let string_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/string/string.o");
    let heap_o: *u8 = 0 as *u8;
    let path_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/path/path.o");
    let runtime_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/runtime/runtime.o");
    let runtime_panic_o: *u8 = xlang_runtime_panic_o_path(a0);
    let net_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/net/net.o");
    let thread_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/thread/thread.o");
    let time_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/time/time.o");
    let random_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/random/random.o");
    let env_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/env/env.o");
    let sync_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/sync/sync.o");
    let encoding_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/encoding/encoding.o");
    let base64_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/base64/base64.o");
    let crypto_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/crypto/crypto.o");
    let log_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/log/log.o");
    let atomic_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/atomic/atomic.o");
    let channel_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/channel/channel.o");
    let backtrace_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/backtrace/backtrace.o");
    let hash_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/hash/hash.o");
    let math_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/math/math.o");
    let sort_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/sort/sort.o");
    let ffi_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/ffi/ffi.o");
    let db_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/db/sqlite/sqlite.o");
    let elf_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/elf/elf.o");
    let json_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/json/json.o");
    let csv_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/csv/csv.o");
    let regex_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/regex/regex.o");
    let compress_o: *u8 = 0 as *u8;
    let unicode_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/unicode/unicode.o");
    let dynlib_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/dynlib/dynlib.o");
    let http_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/http/http.o");
    let tar_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/tar/tar.o");
    let simd_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/simd/simd.o");
    let context_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/context/context.o");
    let datetime_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/datetime/datetime.o");
    let uuid_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/uuid/uuid.o");
    let url_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/url/url.o");
    let cli_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/cli/cli.o");
    let security_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/security/security.o");
    let config_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/config/config.o");
    let cache_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/cache/cache.o");
    let trace_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/trace/trace.o");
    let task_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/task/task.o");
    let schema_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/schema/schema.o");
    let test_o: *u8 = xlang_rel_o_path_from_argv0(a0, "std/test/test.o");
    let include_root: *u8 = xlang_repo_root_from_argv0(a0);
    // G.7: user .o from CLI (e.g. runtime_atomic_glue.o) into the same table as asm ld.
    xlang_invoke_cc_set_user_o_files_from_argv(argc, argv);
    let cc_ret: i32 = xlang_invoke_cc(
      &c_paths_raw[0], 1, out_path, 0 as *u8, opt, use_lto,
      io_o, fs_o, process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o,
      net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o,
      log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, db_o, elf_o,
      json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, simd_o,
      context_o, datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o,
      task_o, schema_o, test_o, include_root, 0 as *u8);
    xlang_invoke_cc_clear_user_o_files();
    if (cc_ret != 0) {
      driver_unlink_failed_output(out_path);
      // BLD001: match cold seed message text without va_list reportf.
      let msg: u8[512] = [];
      let at: i32 = driver_diag_append_cstr(&msg[0], 512, 0, "cc failed, keeping generated C: ");
      at = driver_diag_append_cstr(&msg[0], 512, at, tmp_c);
      diag_report_with_code(0 as *u8, 0, 0, "build error", "BLD001", &msg[0], 0 as *u8);
      return 1;
    }
    // Success: drop tmp .c unless XLANG_KEEP_C is set (dev inspection).
    // wave228 G.7: link_abi_getenv (not raw libc getenv); host residual = _impl.
    if (link_abi_getenv("XLANG_KEEP_C") == 0 as *u8) {
      unlink(tmp_c);
    } else {
      let note: u8[512] = [];
      let atn: i32 = driver_diag_append_cstr(&note[0], 512, 0, "kept generated C: ");
      atn = driver_diag_append_cstr(&note[0], 512, atn, tmp_c);
      diag_report(0 as *u8, 0, 0, "note", &note[0], 0 as *u8);
    }
    return 0;
  }
  return 1;
}

/**
 * Scan dep import-path table for exact "std.io.core".
 * @param dep_paths *u8 — opaque char** base (LP64 pointer table); null → 0
 * @param n_deps i32 — entry count; n_deps <= 0 → 0
 * @return i32 — 1 if any non-null slot equals "std.io.core", else 0
 * Wave31 pure: G.7 xlang_ptr_slot_get + strcmp lit (no C char**).
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_deps_has_std_io_core(dep_paths: *u8, n_deps: i32): i32 {
  if (dep_paths == 0 as *u8) {
    return 0;
  }
  if (n_deps <= 0) {
    return 0;
  }
  unsafe {
    let j: i32 = 0;
    while (j < n_deps) {
      let p: *u8 = xlang_ptr_slot_get(dep_paths, j);
      if (p != 0 as *u8) {
        if (strcmp(p, "std.io.core") == 0) {
          return 1;
        }
      }
      j = j + 1;
    }
  }
  return 0;
}

/**
 * Scan dep import-path table for exact "std.io.driver".
 * @param dep_paths *u8 — opaque char** base (LP64 pointer table); null → 0
 * @param n_deps i32 — entry count; n_deps <= 0 → 0
 * @return i32 — 1 if any non-null slot equals "std.io.driver", else 0
 * Co-emit of driver defines strong submit_*_batch_buf; weak stubs must skip.
 * Wave31 pure: same table walk as core; G.7 ptr_slot + strcmp.
 * PLATFORM: SHARED — pure under PREFER hybrid; cold seed keeps C twin.
 */
#[no_mangle]
export function driver_parsed_deps_has_std_io_driver(dep_paths: *u8, n_deps: i32): i32 {
  if (dep_paths == 0 as *u8) {
    return 0;
  }
  if (n_deps <= 0) {
    return 0;
  }
  unsafe {
    let j: i32 = 0;
    while (j < n_deps) {
      let p: *u8 = xlang_ptr_slot_get(dep_paths, j);
      if (p != 0 as *u8) {
        if (strcmp(p, "std.io.driver") == 0) {
          return 1;
        }
      }
      j = j + 1;
    }
  }
  return 0;
}

/**
 * Reset then OR codegen preamble skip bits from dep closure.
 * @param dep_paths *u8 — opaque char** dep import paths; may be null
 * @param n_deps i32 — entry count
 * No std.io.core → OR (CORE_MACROS|UNDEF_REDEFINE)=5 so preamble does not emit
 * overlapping macros/redefines. Has std.io.driver → OR WEAK_IO_BATCH=8 so weak
 * batch stubs do not redef strong co-emitted symbols (C same-TU redefinition).
 * Wave31 pure: numeric mask bits match codegen.h; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — pure authority in thin; seed rest uses same bits.
 */
#[no_mangle]
export function driver_parsed_apply_preamble_skip(dep_paths: *u8, n_deps: i32): void {
  unsafe {
    codegen_reset_preamble_skip_mask();
    // CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS|UNDEF_REDEFINE = 1|4 = 5
    if (driver_parsed_deps_has_std_io_core(dep_paths, n_deps) == 0) {
      codegen_or_preamble_skip_mask(5);
    }
    // CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH = 8
    if (driver_parsed_deps_has_std_io_driver(dep_paths, n_deps) != 0) {
      codegen_or_preamble_skip_mask(8);
    }
  }
}

/**
 * Optional debug dump of prep entry bytes when XLANG_DUMP_PREP is set.
 * @param input_path *u8 — source path for diag note (may be null)
 * @param src *u8 — prep buffer bytes; null → no-op
 * @param src_len usize — byte count passed to xlang_write_path_bytes
 * Writes /tmp/xlang_prep_entry.bin on success then emits a fixed-arity note
 * (no va_list diag_reportf). Silent if env unset, src null, or write fails.
 * Wave31 pure: env gate + xlang_write_path_bytes + append/diag_report.
 * wave228 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED path text; dump path is fixed /tmp (dev only).
 */
#[no_mangle]
export function driver_parsed_maybe_dump_prep(input_path: *u8, src: *u8, src_len: usize): void {
  unsafe {
    if (link_abi_getenv("XLANG_DUMP_PREP") == 0 as *u8) {
      return;
    }
    if (src == 0 as *u8) {
      return;
    }
    // runtime_io_abi: 0 = success (matches cold seed twin).
    if (xlang_write_path_bytes("/tmp/xlang_prep_entry.bin", src, src_len as i64) == 0) {
      let msg: u8[192] = [];
      let at: i32 = driver_diag_append_cstr(&msg[0], 192, 0, "dumped prep entry (");
      at = driver_abi_append_i64(&msg[0], 192, at, src_len as i64);
      at = driver_diag_append_cstr(&msg[0], 192, at, " bytes) to /tmp/xlang_prep_entry.bin");
      diag_report(input_path, 0, 0, "note", &msg[0], 0 as *u8);
    }
  }
}

// ---- Wave32 Cap residual pure: parsed ABI field accessors + try_c_after_pp ----
// Host layout (seeds/runtime_driver_abi.from_x.c DriverCompileParsedAbi, LP64):
//   input_path *char @0
//   out_path *char @8
//   lib_roots_arr[16] *char @16  (embedded; getter returns &arr[0] = p+16)
//   n_lib_roots i32 @144
//   want_asm_backend i32 @148
//   target *char @152
//   opt_level *char @160
//   use_lto i32 @168
//   sizeof = 176
// Pure path: no C struct in .x; fixed offsetof + LE i32 load + G.7 ptr load at (p+off).
// opt_level null/missing → BSS lit "2" (same as cold g_driver_parsed_opt_default).
// try_c_after_pp: product XLANG_NO_C_FRONTEND always continues .x pipeline (return -2).
// G.7: single hybrid authority under PREFER; cold seed twins under #ifndef FROM_X.
// PLATFORM: SHARED LP64 (Ubuntu x86_64 + Darwin arm64/x86_64). Not MS64 packing.

/** ASCII "2\0" default opt_level when parsed abi is null or field is null. */
let g_driver_parsed_opt_default: u8[2] = [50, 0];

/** offsetof(DriverCompileParsedAbi, input_path) on LP64. */
function driver_abi_parsed_off_input_path(): i32 {
  return 0;
}

/** offsetof(DriverCompileParsedAbi, out_path) on LP64. */
function driver_abi_parsed_off_out_path(): i32 {
  return 8;
}

/** offsetof(DriverCompileParsedAbi, lib_roots_arr) on LP64 (embedded array base). */
function driver_abi_parsed_off_lib_roots(): i32 {
  return 16;
}

/** offsetof(DriverCompileParsedAbi, n_lib_roots) on LP64. */
function driver_abi_parsed_off_n_lib_roots(): i32 {
  return 144;
}

/** offsetof(DriverCompileParsedAbi, want_asm_backend) on LP64. */
function driver_abi_parsed_off_want_asm(): i32 {
  return 148;
}

/** offsetof(DriverCompileParsedAbi, target) on LP64. */
function driver_abi_parsed_off_target(): i32 {
  return 152;
}

/** offsetof(DriverCompileParsedAbi, opt_level) on LP64. */
function driver_abi_parsed_off_opt_level(): i32 {
  return 160;
}

/** offsetof(DriverCompileParsedAbi, use_lto) on LP64. */
function driver_abi_parsed_off_use_lto(): i32 {
  return 168;
}

/**
 * Load an LP64 pointer field at byte offset off from opaque struct base p.
 * @param p *u8 — struct base; null → null
 * @param off i32 — byte offset of pointer field; off < 0 → null
 * @return *u8 — loaded pointer (may be null)
 * Uses G.7 xlang_ptr_slot_get on (p+off) as a 1-slot table (no second load helper).
 * PLATFORM: SHARED LP64 little-endian pointer cells.
 */
function driver_abi_load_ptr_at(p: *u8, off: i32): *u8 {
  if (p == 0 as *u8) {
    return 0 as *u8;
  }
  if (off < 0) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_ptr_slot_get(p + off, 0);
  }
  return 0 as *u8;
}

/**
 * Read DriverCompileParsedAbi.input_path from opaque *p.
 * @param p *u8 — DriverCompileParsedAbi* as opaque; null → null
 * @return *u8 — input path C string pointer (may be null)
 * Wave32 pure: LP64 offsetof 0 + G.7 ptr load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_input_path(p: *u8): *u8 {
  return driver_abi_load_ptr_at(p, driver_abi_parsed_off_input_path());
}

/**
 * Read DriverCompileParsedAbi.out_path from opaque *p.
 * @param p *u8 — DriverCompileParsedAbi* as opaque; null → null
 * @return *u8 — output path C string pointer (may be null = stdout path)
 * Wave32 pure: LP64 offsetof 8 + G.7 ptr load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_out_path(p: *u8): *u8 {
  return driver_abi_load_ptr_at(p, driver_abi_parsed_off_out_path());
}

/**
 * Return address of embedded lib_roots_arr[16] (ABI as const char** / *u8).
 * @param p *u8 — DriverCompileParsedAbi* as opaque; null → null
 * @return *u8 — &p->lib_roots_arr[0] (not a loaded pointer; the array base)
 * Wave32 pure: p + offsetof(lib_roots_arr)=16. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_lib_roots(p: *u8): *u8 {
  if (p == 0 as *u8) {
    return 0 as *u8;
  }
  unsafe {
    return p + driver_abi_parsed_off_lib_roots();
  }
  return 0 as *u8;
}

/**
 * Read DriverCompileParsedAbi.n_lib_roots.
 * @param p *u8 — opaque abi; null → 0
 * @return i32 — number of lib roots (0..16)
 * Wave32 pure: LP64 offsetof 144 + LE i32 load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_n_lib_roots(p: *u8): i32 {
  if (p == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(p, driver_abi_parsed_off_n_lib_roots());
}

/**
 * Read DriverCompileParsedAbi.want_asm_backend.
 * @param p *u8 — opaque abi; null → 0
 * @return i32 — non-zero when asm backend requested
 * Wave32 pure: LP64 offsetof 148 + LE i32 load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_want_asm(p: *u8): i32 {
  if (p == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(p, driver_abi_parsed_off_want_asm());
}

/**
 * Read DriverCompileParsedAbi.target triple string pointer.
 * @param p *u8 — opaque abi; null → null
 * @return *u8 — target C string (may be null)
 * Wave32 pure: LP64 offsetof 152 + G.7 ptr load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_target(p: *u8): *u8 {
  return driver_abi_load_ptr_at(p, driver_abi_parsed_off_target());
}

/**
 * Read DriverCompileParsedAbi.opt_level; default "2" when null field or null p.
 * @param p *u8 — opaque abi; null → BSS lit "2"
 * @return *u8 — opt level C string (never null; default g_driver_parsed_opt_default)
 * Wave32 pure: LP64 offsetof 160 + G.7 ptr load; default matches cold seed.
 * PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_opt_level(p: *u8): *u8 {
  if (p == 0 as *u8) {
    return &g_driver_parsed_opt_default[0];
  }
  let o: *u8 = driver_abi_load_ptr_at(p, driver_abi_parsed_off_opt_level());
  if (o == 0 as *u8) {
    return &g_driver_parsed_opt_default[0];
  }
  return o;
}

/**
 * Read DriverCompileParsedAbi.use_lto.
 * @param p *u8 — opaque abi; null → 0
 * @return i32 — non-zero when LTO requested
 * Wave32 pure: LP64 offsetof 168 + LE i32 load. PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parsed_use_lto(p: *u8): i32 {
  if (p == 0 as *u8) {
    return 0;
  }
  return driver_abi_load_i32_le(p, driver_abi_parsed_off_use_lto());
}

/**
 * Optional C frontend after preprocess (check/smoke/generic C inline).
 * @param input_path *u8 — entry path (unused on product NO_C path)
 * @param src *u8 — prep source bytes (unused)
 * @param src_len usize — prep length (unused)
 * @param lib_roots *u8 — opaque char** (unused)
 * @param n_lib i32 — lib root count (unused)
 * @param out_path *u8 — output path (unused)
 * @param argc i32 — argv count (unused)
 * @param argv *u8 — opaque argv (unused)
 * @param opt_level *u8 — opt string (unused)
 * @param use_lto i32 — LTO flag (unused)
 * @param ndefines i32 — define count (unused)
 * @param defines *u8 — opaque defines table (unused)
 * @return i32 — -2 continue .x pipeline; >=0 would be terminal rc
 * Product XLANG_NO_C_FRONTEND always returns -2 (no C frontend body in pure).
 * Cold full-C seeds may still host a real branch; product hybrid keeps stub.
 * Wave32 pure. PLATFORM: SHARED — product path; permanent NO_C contract.
 */
#[no_mangle]
export function driver_parsed_try_c_after_pp(
  input_path: *u8,
  src: *u8,
  src_len: usize,
  lib_roots: *u8,
  n_lib: i32,
  out_path: *u8,
  argc: i32,
  argv: *u8,
  opt_level: *u8,
  use_lto: i32,
  ndefines: i32,
  defines: *u8
): i32 {
  // Product path: fixed -2 (continue .x). Args retained for ABI parity with cold seed.
  return -2;
}

// ---- Wave33 Cap residual pure: driver_x_emit bind/take/get/effective/try_extern ----
// Cap-global-bss data stays in seeds/rt_emit_state.from_x.c (cross-TU non-static).
// Always-seed residual (this hybrid links them from runtime_driver_abi rest):
//   path_buf_slot / lib_buf_slot / scan_* / c_path_cell / lib_roots_raw /
//   n_lib_roots_slot / want_extern_slot
// Pure authority under PREFER: clear/bind/take/get/lib_root_at/effective/try_extern
// via G.7 xlang_ptr_slot_* (no **u8 write in .x; no dual BSS).
// Permanent OS residual (still seed): stdout_set_unbuffered / fwrite_stdout.
// G.7: single hybrid authority under PREFER; cold seed twins under #ifndef FROM_X.
// PLATFORM: SHARED LP64.

/** Always-seed Cap-global-bss: base of path_buf[512] in rt_emit_state. */
export extern "C" function driver_x_emit_path_buf_slot(): *u8;
/** Always-seed Cap-global-bss: base of lib_bufs[i][256]; null if i OOR. */
export extern "C" function driver_x_emit_lib_buf_slot(i: i32): *u8;
/** Always-seed: &driver_x_emit_c_path as one G.7 pointer-slot cell. */
export extern "C" function driver_x_emit_c_path_cell(): *u8;
/** Always-seed: base of driver_x_emit_lib_roots[16] pointer table. */
export extern "C" function driver_x_emit_lib_roots_raw(): *u8;
/** Always-seed: &driver_x_emit_n_lib_roots as *i32. */
export extern "C" function driver_x_emit_n_lib_roots_slot(): *i32;
/** Always-seed: &driver_x_emit_c_want_extern as *i32. */
export extern "C" function driver_x_emit_want_extern_slot(): *i32;

/** Max -L roots (must match X_EMIT_MAX_LIB_ROOTS_ABI / rt_emit_max_lib_roots). */
function driver_x_emit_max_lib_roots(): i32 {
  return 16;
}

/** ASCII ".\0" fallback lib root when n_lib_roots <= 0. */
let g_driver_x_emit_dot: u8[2] = [46, 0];
/** One LP64 pointer slot for effective_lib_roots fallback table. */
let g_driver_x_emit_one_root_raw: u8[8] = [];

/**
 * Clear the shared emit c_path pointer cell (set to null).
 * @return void
 * Wave33 pure: G.7 xlang_ptr_slot_set on always-seed c_path_cell.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_clear_c_path(): void {
  unsafe {
    let cell: *u8 = driver_x_emit_c_path_cell();
    if (cell == 0 as *u8) {
      return;
    }
    xlang_ptr_slot_set(cell, 0, 0 as *u8);
  }
}

/**
 * Bind c_path cell to the path_buf slot base (after path bytes were copied).
 * @return void
 * Wave33 pure: G.7 set c_path_cell[0] = path_buf_slot().
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_bind_c_path_to_buf(): void {
  unsafe {
    let cell: *u8 = driver_x_emit_c_path_cell();
    let buf: *u8 = driver_x_emit_path_buf_slot();
    if (cell == 0 as *u8) {
      return;
    }
    xlang_ptr_slot_set(cell, 0, buf);
  }
}

/**
 * Bind lib_roots[i] to lib_bufs[i] after bytes were copied into the buffer.
 * @param i i32 — root index; out of range [0,16) is a no-op
 * @return void
 * Wave33 pure: G.7 xlang_ptr_slot_set on lib_roots_raw + lib_buf_slot.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_bind_lib_root(i: i32): void {
  if (i < 0) {
    return;
  }
  if (i >= driver_x_emit_max_lib_roots()) {
    return;
  }
  unsafe {
    let raw: *u8 = driver_x_emit_lib_roots_raw();
    let buf: *u8 = driver_x_emit_lib_buf_slot(i);
    if (raw == 0 as *u8) {
      return;
    }
    if (buf == 0 as *u8) {
      return;
    }
    xlang_ptr_slot_set(raw, i, buf);
  }
}

/**
 * Take (read + clear) the shared emit c_path pointer.
 * @return *u8 — previous c_path (may be null); cell set to null
 * Wave33 pure: G.7 get then set-null on c_path_cell.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_take_c_path(): *u8 {
  unsafe {
    let cell: *u8 = driver_x_emit_c_path_cell();
    if (cell == 0 as *u8) {
      return 0 as *u8;
    }
    let p: *u8 = xlang_ptr_slot_get(cell, 0);
    xlang_ptr_slot_set(cell, 0, 0 as *u8);
    return p;
  }
  return 0 as *u8;
}

/**
 * Take (read + clear) want_extern flag.
 * @return i32 — previous want_extern; slot set to 0
 * Wave33 pure: always-seed want_extern_slot *i32 cell.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_take_want_extern(): i32 {
  unsafe {
    let s: *i32 = driver_x_emit_want_extern_slot();
    if (s == 0 as *i32) {
      return 0;
    }
    let w: i32 = s[0];
    s[0] = 0;
    return w;
  }
  return 0;
}

/**
 * Read current n_lib_roots counter.
 * @return i32 — root count (0..16); 0 if slot null
 * Wave33 pure: always-seed n_lib_roots_slot.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_n_lib_roots_get(): i32 {
  unsafe {
    let s: *i32 = driver_x_emit_n_lib_roots_slot();
    if (s == 0 as *i32) {
      return 0;
    }
    return s[0];
  }
  return 0;
}

/**
 * Return lib_roots[i] pointer (opaque *u8 C string).
 * @param i i32 — index; OOR or i >= n_lib_roots → null
 * @return *u8 — bound root path or null
 * Wave33 pure: G.7 get on lib_roots_raw after n_lib_roots_get bounds.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_lib_root_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  let n: i32 = driver_x_emit_n_lib_roots_get();
  if (i >= n) {
    return 0 as *u8;
  }
  unsafe {
    let raw: *u8 = driver_x_emit_lib_roots_raw();
    if (raw == 0 as *u8) {
      return 0 as *u8;
    }
    return xlang_ptr_slot_get(raw, i);
  }
  return 0 as *u8;
}

/**
 * Effective lib roots table for pipeline: if n_lib_roots <= 0, return ["."];
 * else return the live lib_roots pointer table base.
 * @param n_out *i32 — optional out count; null skips write
 * @return *u8 — opaque const char** (one_root BSS or lib_roots_raw)
 * Wave33 pure: one_root via G.7 ptr_slot_set + BSS "."; no **u8 lit.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_x_emit_effective_lib_roots(n_out: *i32): *u8 {
  let n: i32 = driver_x_emit_n_lib_roots_get();
  if (n <= 0) {
    unsafe {
      xlang_ptr_slot_set(&g_driver_x_emit_one_root_raw[0], 0, &g_driver_x_emit_dot[0]);
      if (n_out != 0 as *i32) {
        n_out[0] = 1;
      }
      return &g_driver_x_emit_one_root_raw[0];
    }
  }
  unsafe {
    if (n_out != 0 as *i32) {
      n_out[0] = n;
    }
    return driver_x_emit_lib_roots_raw();
  }
  return 0 as *u8;
}

/**
 * Product NO_C path for -x -E -E-extern: emit BLD001 and return 1.
 * @param input_path *u8 — unused on product NO_C (ABI parity)
 * @return i32 — always 1 (terminal failure) on product hybrid
 * Wave33 pure: diag_report_with_code with fixed message; no C frontend body.
 * PLATFORM: SHARED — product NO_C contract; cold seed keeps same stub twin.
 */
#[no_mangle]
export function driver_x_emit_try_extern_via_cparser(input_path: *u8): i32 {
  // Product XLANG_NO_C_FRONTEND: fixed diagnostic (input_path unused).
  unsafe {
    diag_report_with_code(
      0 as *u8,
      0,
      0,
      "build error",
      "BLD001",
      "-x -E -E-extern requires C parser/codegen (rebuild without -DXLANG_NO_C_FRONTEND)",
      0 as *u8
    );
  }
  return 1;
}

// ---- Wave34 Cap residual pure: asm try_c stubs + bind_lib_roots + defines BSS ----
// Product XLANG_NO_C_FRONTEND / no XLANG_ASM_USE_COMPILER_IMPL_C:
//   try_c_frontend_early → -2 (continue .x pipeline)
//   try_c_typeck_precheck → -1 (skip C typeck precheck)
//   use_compiler_impl_c → 0
// bind_lib_roots: n<=0 or null → ["."] one_root BSS via G.7; else return caller table.
// argv0: G.7 / driver_argv_at index 0.
// collect_defines: zero 64×LP64 BSS table + pure driver_argv_collect_defines (wave10).
// wave43/44 pure: sibling_try_spawn / print_usage_write (see wave blocks).
// Wave42 pure: exec_compiled_body (scan opaque + spawn residual).
// Wave39–41 pure: fwrite/stdio/fflush/fopen_wb/write_metric/mkstemp_fdopen.
// G.7: single hybrid authority under PREFER; cold seed twins under #ifndef FROM_X.
// PLATFORM: SHARED LP64.

/** MAX_DEFINES for driver_asm_collect_defines (matches seed MAX_DEFINES). */
function driver_abi_asm_max_defines(): i32 {
  return 64;
}

/** LP64 pointer width for defines raw table sizing. */
function driver_abi_asm_defines_raw_bytes(): i32 {
  // 64 slots × 8 bytes.
  return 512;
}

/** ASCII ".\0" fallback lib root when n_lib<=0. */
let g_driver_asm_dot: u8[2] = [46, 0];
/** One-slot raw table for ["."] fallback (G.7 writes slot 0). */
let g_driver_asm_one_root_raw: u8[8] = [];
/** Defines pointer table BSS: 64 × LP64 void* as raw bytes. */
let g_driver_asm_defines_raw: u8[512] = [];
/** Live define count after last collect_defines. */
let g_driver_asm_ndefines: i32 = 0;

/**
 * Product NO_C early C-frontend smoke: always continue .x pipeline.
 * @param input_path *u8 — unused (ABI parity with cold seed)
 * @param src *u8 — unused
 * @param lib_roots *u8 — unused
 * @param n_lib i32 — unused
 * @param out_path *u8 — unused
 * @return i32 — always -2 (continue .x)
 * Wave34 pure: product XLANG_NO_C_FRONTEND contract; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_try_c_frontend_early(
  input_path: *u8,
  src: *u8,
  lib_roots: *u8,
  n_lib: i32,
  out_path: *u8
): i32 {
  return -2;
}

/**
 * Product NO_C C-typeck precheck: always skip.
 * @param input_path *u8 — unused (ABI parity)
 * @param src *u8 — unused
 * @param lib_roots *u8 — unused
 * @param n_lib i32 — unused
 * @return i32 — always -1 (skip)
 * Wave34 pure: product XLANG_NO_C_FRONTEND contract; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_try_c_typeck_precheck(
  input_path: *u8,
  src: *u8,
  lib_roots: *u8,
  n_lib: i32
): i32 {
  return -1;
}

/**
 * Whether XLANG_ASM_USE_COMPILER_IMPL_C is compiled in (dep-only parse path).
 * @return i32 — always 0 on product hybrid (flag never set in product builds)
 * Wave34 pure: product path fixed 0; cold twin uses #ifdef XLANG_ASM_USE_COMPILER_IMPL_C.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_use_compiler_impl_c(): i32 {
  return 0;
}

/**
 * Bind caller lib_roots for asm/parsed pipeline; n<=0 or null → fallback ["."].
 * @param lib_roots *u8 — opaque const char** from caller; may be null
 * @param n i32 — root count; n<=0 triggers fallback
 * @param n_out *i32 — optional out count; null skips write
 * @return *u8 — effective table (one_root BSS or caller lib_roots)
 * Wave34 pure: one_root via G.7 ptr_slot_set + BSS "."; no **u8 lit.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_bind_lib_roots(lib_roots: *u8, n: i32, n_out: *i32): *u8 {
  if (n <= 0 || lib_roots == 0 as *u8) {
    unsafe {
      xlang_ptr_slot_set(&g_driver_asm_one_root_raw[0], 0, &g_driver_asm_dot[0]);
      if (n_out != 0 as *i32) {
        n_out[0] = 1;
      }
      return &g_driver_asm_one_root_raw[0];
    }
  }
  unsafe {
    if (n_out != 0 as *i32) {
      n_out[0] = n;
    }
  }
  return lib_roots;
}

/**
 * Return argv[0] as opaque *u8 (C string), or null.
 * @param argv *u8 — opaque char** table base; null → null
 * @return *u8 — argv[0] or null
 * Wave34 pure: driver_argv_at (G.7-style slot get); cold twin casts char**.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_argv0(argv: *u8): *u8 {
  if (argv == 0 as *u8) {
    return 0 as *u8;
  }
  unsafe {
    return driver_argv_at(argv, 0);
  }
  return 0 as *u8;
}

/**
 * Collect -D / -target / uname defines into internal BSS table.
 * @param argc i32 — argv length
 * @param argv *u8 — opaque char**
 * @return i32 — number of defines written (0 if empty/null)
 * Wave34 pure: zero defines raw BSS + pure driver_argv_collect_defines (wave10).
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_collect_defines(argc: i32, argv: *u8): i32 {
  unsafe {
    memset(&g_driver_asm_defines_raw[0], 0, driver_abi_asm_defines_raw_bytes() as usize);
  }
  g_driver_asm_ndefines = 0;
  if (argv == 0 as *u8 || argc <= 0) {
    return 0;
  }
  unsafe {
    g_driver_asm_ndefines = driver_argv_collect_defines(
      argc,
      argv,
      &g_driver_asm_defines_raw[0],
      driver_abi_asm_max_defines()
    );
  }
  return g_driver_asm_ndefines;
}

/**
 * Base of last collect_defines table as opaque *u8 (const char**).
 * @return *u8 — table base when ndefines>0; else null
 * Wave34 pure: returns BSS raw base; cold twin same semantics.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_defines_as_u8(): *u8 {
  if (g_driver_asm_ndefines <= 0) {
    return 0 as *u8;
  }
  return &g_driver_asm_defines_raw[0];
}

/**
 * Count of defines from last driver_asm_collect_defines.
 * @return i32 — ndefines (>=0)
 * Wave34 pure: BSS load; cold twin same semantics.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_asm_ndefines_get(): i32 {
  return g_driver_asm_ndefines;
}

// ---- Wave35 Cap residual pure: typeck set + diag push/restore + dispatch root/opt ----
// typeck_*: G.7 thin wrappers over pipeline typeck_ndep_store / dep_module_set / dep_arena_set
//   (single table authority remains typeck_dep_*_ptrs[32] in pipeline seed).
// diag_*: null-guard + diag_push_file / diag_restore (diag_thin pure under PREFER).
// dispatch_lib_root_at: G.7 xlang_ptr_slot_get on opaque const char** (max 16).
// dispatch_opt_default: reuses wave32 g_driver_parsed_opt_default lit "2" (G.7 one lit).
// Wave36 pure: dispatch_lib_roots_from_key + run_compiler_parsed (see section below).
// Still seed (OS residual): sibling_try_spawn (access/fork/exec), fopen family.
// G.7: hybrid authority under PREFER; cold seed twins under #ifndef FROM_X.
// PLATFORM: SHARED LP64.

/** X_FULL_MAX_LIB_ROOTS for dispatch lib_root_at bounds (matches seed). */
function driver_abi_dispatch_max_lib_roots(): i32 {
  return 16;
}

/** typeck_dep_*_ptrs array length (matches pipeline seed). */
function driver_abi_typeck_dep_cap(): i32 {
  return 32;
}

/**
 * Set global typeck_ndep for C typeck dep sidecar.
 * @param n i32 — dependency module count (stored as-is via typeck_ndep_store)
 * @return void
 * Wave35 pure: G.7 typeck_ndep_store; cold twin writes typeck_ndep under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_typeck_ndep_set(n: i32): void {
  unsafe {
    typeck_ndep_store(n);
  }
}

/**
 * Set typeck_dep_module_ptrs[j] and typeck_dep_arena_ptrs[j].
 * @param j i32 — index; out of range [0,32) is a no-op
 * @param mod *u8 — opaque ASTModule* (or null)
 * @param arena *u8 — opaque arena* (or null)
 * @return void
 * Wave35 pure: G.7 typeck_dep_module_set + typeck_dep_arena_set; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_typeck_dep_ptrs_set(j: i32, mod: *u8, arena: *u8): void {
  if (j < 0) {
    return;
  }
  if (j >= driver_abi_typeck_dep_cap()) {
    return;
  }
  unsafe {
    typeck_dep_module_set(j, mod);
    typeck_dep_arena_set(j, arena);
  }
}

/**
 * Push diagnostic file context into a DiagContextSnapshot then apply.
 * @param snap *u8 — opaque DiagContextSnapshot*; null → no-op
 * @param path *u8 — file path C string (may be null; diag authority handles)
 * @param src *u8 — source bytes pointer (may be null)
 * @param len usize — source byte length
 * @return void
 * Wave35 pure: null guard + diag_push_file (G.7); cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_diag_push_file(snap: *u8, path: *u8, src: *u8, len: usize): void {
  if (snap == 0 as *u8) {
    return;
  }
  unsafe {
    diag_push_file(snap, path, src, len as i64);
  }
}

/**
 * Restore diagnostic context from a DiagContextSnapshot.
 * @param snap *u8 — opaque DiagContextSnapshot*; null → no-op
 * @return void
 * Wave35 pure: null guard + diag_restore (G.7); cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_diag_restore(snap: *u8): void {
  if (snap == 0 as *u8) {
    return;
  }
  unsafe {
    diag_restore(snap);
  }
}

/**
 * Index into a dispatch lib_roots table (opaque const char**).
 * @param roots *u8 — table base from driver_dispatch_lib_roots_from_key (or equivalent)
 * @param i i32 — root index; null roots or i out of [0,16) → null
 * @return *u8 — C string path at roots[i], or null
 * Wave35 pure: G.7 xlang_ptr_slot_get; cold twin casts const char** under #ifndef FROM_X.
 * PLATFORM: SHARED LP64 — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_dispatch_lib_root_at(roots: *u8, i: i32): *u8 {
  if (roots == 0 as *u8) {
    return 0 as *u8;
  }
  if (i < 0) {
    return 0 as *u8;
  }
  if (i >= driver_abi_dispatch_max_lib_roots()) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_ptr_slot_get(roots, i);
  }
  return 0 as *u8;
}

/**
 * Default opt_level C string for dispatch/parsed ("2").
 * @return *u8 — never null; points at wave32 g_driver_parsed_opt_default BSS lit
 * Wave35 pure: G.7 single "2" lit authority (shared with driver_parsed_opt_level default);
 * cold twin keeps g_dispatch_opt_default under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_dispatch_opt_default(): *u8 {
  return &g_driver_parsed_opt_default[0];
}

// ---- Wave36 Cap residual pure: dispatch lib_roots_from_key + run_compiler_parsed ----
// lib_roots_from_key: product .x cannot host char[16][512] / const char*[16] as typed C
//   arrays; authority is flat BSS (8192 path bytes + 128 root-ptr bytes) + G.7
//   driver_lib_roots_from_key (rt_lib_root / seed) which writes both tables.
// run_compiler_parsed: no C struct in .x; pack DriverCompileParsedAbi into BSS scratch
//   (sizeof 176 LP64; same offsetof map as wave32 accessors) then call
//   driver_run_compiler_parsed (rt_run_compiler_parsed / seed). want_asm fixed 0.
// opt default reuses wave32 g_driver_parsed_opt_default (G.7 one lit; wave35 opt_default).
// Still seed: sibling_try_spawn / fopen OS residual.
// G.7: hybrid authority under PREFER; cold seed twins under #ifndef FROM_X.
// PLATFORM: SHARED LP64 (Ubuntu x86_64 + Darwin arm64/x86_64). Not MS64 packing.

/** Contiguous path storage for driver_lib_roots_from_key (16 roots × 512 bytes). */
let g_dispatch_lib_bufs: u8[8192] = [];

/** Root pointer table (16 × LP64 slots) returned as opaque const char**. */
let g_dispatch_lib_roots_raw: u8[128] = [];

/**
 * Scratch pack for DriverCompileParsedAbi (sizeof 176 on product LP64).
 * Single-threaded product dispatch; module BSS avoids large local u8[N] product -E issues.
 */
let g_dispatch_parsed_pack_raw: u8[176] = [];

/** sizeof(DriverCompileParsedAbi) on product LP64 (wave32 layout). */
function driver_abi_parsed_sizeof(): i32 {
  return 176;
}

/**
 * Store an LP64 pointer field at byte offset off from opaque struct base p.
 * @param p *u8 — struct base; null → no-op
 * @param off i32 — byte offset of pointer field; off < 0 → no-op
 * @param v *u8 — pointer value to store (may be null)
 * @return void
 * G.7: xlang_ptr_slot_set on (p+off) as a 1-slot table (pairs driver_abi_load_ptr_at).
 * PLATFORM: SHARED LP64 little-endian pointer cells.
 */
function driver_abi_store_ptr_at(p: *u8, off: i32, v: *u8): void {
  if (p == 0 as *u8) {
    return;
  }
  if (off < 0) {
    return;
  }
  unsafe {
    xlang_ptr_slot_set(p + off, 0, v);
  }
}

/**
 * Expand lib_key into the dispatch static root table (16×512 path slots).
 * @param lib_key *u8 — opaque key / argv state for driver_lib_roots_from_key (may be null)
 * @param n_out *i32 — optional out count; null → skip write; else *n_out = root count
 * @return *u8 — base of root pointer table (opaque const char**; never null BSS base)
 * Wave36 pure: BSS bufs+roots + G.7 driver_lib_roots_from_key; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED LP64 — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_dispatch_lib_roots_from_key(lib_key: *u8, n_out: *i32): *u8 {
  let n: i32 = 0;
  unsafe {
    n = driver_lib_roots_from_key(
      lib_key,
      &g_dispatch_lib_roots_raw[0],
      &g_dispatch_lib_bufs[0]
    );
  }
  if (n_out != 0 as *i32) {
    unsafe {
      n_out[0] = n;
    }
  }
  return &g_dispatch_lib_roots_raw[0];
}

/**
 * Pack DriverCompileParsedAbi (want_asm=0) and run driver_run_compiler_parsed.
 * @param input_path *u8 — entry source path C string (may be null; authority may reject)
 * @param out_path *u8 — output path; null = stdout / no file out per authority
 * @param lib_roots *u8 — opaque const char** table (may be null when n_lib<=0)
 * @param n_lib i32 — root count; clamped to [0,16]
 * @param target *u8 — target triple; null or empty → null field
 * @param opt_level *u8 — opt string; null or empty → wave32 BSS lit "2"
 * @param use_lto i32 — non-zero → use_lto=1 in pack
 * @param argc i32 — argv count for driver_run_compiler_parsed
 * @param argv *u8 — opaque char** argv
 * @return i32 — return code from driver_run_compiler_parsed
 * Wave36 pure: BSS pack + wave32 offsetof map + G.7 driver_run_compiler_parsed;
 * cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED LP64 — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_dispatch_run_compiler_parsed(
  input_path: *u8,
  out_path: *u8,
  lib_roots: *u8,
  n_lib: i32,
  target: *u8,
  opt_level: *u8,
  use_lto: i32,
  argc: i32,
  argv: *u8
): i32 {
  let p: *u8 = &g_dispatch_parsed_pack_raw[0];
  let n: i32 = n_lib;
  let i: i32 = 0;
  let t: *u8 = 0 as *u8;
  let o: *u8 = &g_driver_parsed_opt_default[0];
  let lto: i32 = 0;
  // Zero full abi pack (matches cold memset(&p, 0, sizeof p)).
  unsafe {
    memset(p, 0, driver_abi_parsed_sizeof() as usize);
  }
  driver_abi_store_ptr_at(p, driver_abi_parsed_off_input_path(), input_path);
  driver_abi_store_ptr_at(p, driver_abi_parsed_off_out_path(), out_path);
  if (n > driver_abi_dispatch_max_lib_roots()) {
    n = driver_abi_dispatch_max_lib_roots();
  }
  if (n < 0) {
    n = 0;
  }
  // Copy n root pointers into embedded lib_roots_arr (p+16).
  if (n > 0) {
    if (lib_roots != 0 as *u8) {
      i = 0;
      while (i < n) {
        unsafe {
          let r: *u8 = xlang_ptr_slot_get(lib_roots, i);
          xlang_ptr_slot_set(p + driver_abi_parsed_off_lib_roots(), i, r);
        }
        i = i + 1;
      }
    }
  }
  driver_abi_store_i32_le(p, driver_abi_parsed_off_n_lib_roots(), n);
  // want_asm_backend fixed 0 for dispatch path (matches cold seed).
  driver_abi_store_i32_le(p, driver_abi_parsed_off_want_asm(), 0);
  if (target != 0 as *u8) {
    unsafe {
      if (target[0] != 0) {
        t = target;
      }
    }
  }
  driver_abi_store_ptr_at(p, driver_abi_parsed_off_target(), t);
  if (opt_level != 0 as *u8) {
    unsafe {
      if (opt_level[0] != 0) {
        o = opt_level;
      }
    }
  }
  driver_abi_store_ptr_at(p, driver_abi_parsed_off_opt_level(), o);
  if (use_lto != 0) {
    lto = 1;
  }
  driver_abi_store_i32_le(p, driver_abi_parsed_off_use_lto(), lto);
  unsafe {
    return driver_run_compiler_parsed(p, argc, argv);
  }
  return 0;
}

// ---- Wave37 Cap residual pure: arena/module static + stack_esc_gate + parser_diag ----

/**
 * Fixed size of Cap-global driver_arena_static (128 MiB).
 * @return usize — DRIVER_ARENA_STATIC_SIZE_ABI bytes
 * Wave37 pure; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — constant; array body stays seeds/rt_arena_buf.from_x.c.
 */
function driver_abi_arena_static_size_const(): usize {
  // 128 * 1024 * 1024
  return 134217728 as usize;
}

/**
 * Fixed size of Cap-global driver_module_static (2 MiB).
 * @return usize — DRIVER_MODULE_STATIC_SIZE_ABI bytes
 * Wave37 pure; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — constant; array body stays seeds/rt_arena_buf.from_x.c.
 */
function driver_abi_module_static_size_const(): usize {
  // 2 * 1024 * 1024
  return 2097152 as usize;
}

/**
 * LP64 sizeof(struct xlang_slice_uint8_t) = 16 (data* + length usize).
 * @return i32 — bytes for BSS pack used by driver_parser_diag_fail_tok_kind
 * PLATFORM: SHARED LP64.
 */
function driver_abi_slice_uint8_sizeof(): i32 {
  return 16;
}

/**
 * offsetof(xlang_slice_uint8_t, data) on LP64.
 * @return i32 — 0
 */
function driver_abi_slice_uint8_off_data(): i32 {
  return 0;
}

/**
 * offsetof(xlang_slice_uint8_t, length) on LP64.
 * @return i32 — 8
 */
function driver_abi_slice_uint8_off_length(): i32 {
  return 8;
}

// BSS pack for parser_diag_fail_tok_kind (not re-entrant; matches cold stack local lifetime
// for product single-threaded driver paths).
let g_driver_parser_diag_slice_raw: u8[16] = [];

/**
 * Address of Cap-global 128MiB arena static buffer (other TU).
 * @return *u8 — base of driver_arena_static[]; never null when rt_arena_buf linked
 * Wave37 pure: always-seed driver_arena_static_base; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap-global-bss residual data; pure owns slot API under PREFER.
 */
#[no_mangle]
export function driver_arena_static_slot(): *u8 {
  unsafe {
    return driver_arena_static_base();
  }
  return 0 as *u8;
}

/**
 * Address of Cap-global 2MiB module static buffer (other TU).
 * @return *u8 — base of driver_module_static[]
 * Wave37 pure; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap-global-bss residual data.
 */
#[no_mangle]
export function driver_module_static_slot(): *u8 {
  unsafe {
    return driver_module_static_base();
  }
  return 0 as *u8;
}

/**
 * Byte capacity of driver_arena_static.
 * @return usize — 134217728 (128 MiB)
 * Wave37 pure constant; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_arena_static_size(): usize {
  return driver_abi_arena_static_size_const();
}

/**
 * Byte capacity of driver_module_static.
 * @return usize — 2097152 (2 MiB)
 * Wave37 pure constant; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_module_static_size(): usize {
  return driver_abi_module_static_size_const();
}

/**
 * Run stack escape-gate thread body on the large-stack path.
 * @param arg *u8 — opaque arg for driver_stack_esc_gate_thread_fn; null → no-op
 * @return void
 * Wave37 pure orch: Cap-fn-ptr residual driver_stack_esc_gate_thread_fn_ptr +
 * G.7 driver_run_thread_on_large_stack (wave12 pure). Cold twin always-seed under seed.
 * PLATFORM: SHARED — fn pointer constant stays seed residual.
 */
#[no_mangle]
export function driver_run_stack_esc_gate_on_large_stack(arg: *u8): void {
  let fn: *u8 = 0 as *u8;
  if (arg == 0 as *u8) {
    return;
  }
  unsafe {
    fn = driver_stack_esc_gate_thread_fn_ptr();
  }
  if (fn == 0 as *u8) {
    return;
  }
  driver_run_thread_on_large_stack(fn, arg);
}

/**
 * Pack source bytes as xlang_slice_uint8_t and query parser fail-at token kind.
 * @param src *u8 — source bytes; null → return 0 (matches cold seed)
 * @param len usize — byte length of src (may be 0)
 * @return i32 — parser_diag_fail_at_token_kind result; 0 on null src
 * Wave37 pure: BSS LP64 slice pack (data@0, length@8) + G.7 parser_diag_fail_at_token_kind.
 * Cold twin under #ifndef FROM_X. Not re-entrant (single BSS pack).
 * PLATFORM: SHARED LP64.
 */
#[no_mangle]
export function driver_parser_diag_fail_tok_kind(src: *u8, len: usize): i32 {
  let p: *u8 = &g_driver_parser_diag_slice_raw[0];
  if (src == 0 as *u8) {
    return 0;
  }
  // Zero pack then store fields (matches cold stack local zero then assign).
  unsafe {
    memset(p, 0, driver_abi_slice_uint8_sizeof() as usize);
  }
  driver_abi_store_ptr_at(p, driver_abi_slice_uint8_off_data(), src);
  driver_abi_store_usize_le(p, driver_abi_slice_uint8_off_length(), len);
  unsafe {
    return parser_diag_fail_at_token_kind(p);
  }
  return 0;
}

/**
 * Parse source buffer into module; return parser ok and optional main index.
 * @param arena *u8 — ASTArena*; null → -1 (and *out_main_idx = -1 when non-null)
 * @param module *u8 — Module*; null → -1
 * @param data *u8 — source bytes; null → -1
 * @param len i32 — byte length of data (passed through to residual)
 * @param out_main_idx *i32 — optional; when non-null set to main_idx or -1 on guard fail
 * @return i32 — ParseIntoResult.ok from residual; -1 on null arena/module/data
 * Wave38 pure: null guards pure; Cap-struct-return residual xlang_parser_parse_into_buf_rc
 * unpacks parser_ParseIntoResult (ok + main_idx). Cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — struct return stays seed residual.
 */
/**
 * wave269: reset sticky unclosed block-comment state before each product parse.
 * PLATFORM: SHARED — G.7 single product parse entry.
 */
export extern "C" function lexer_unclosed_block_comment_reset(): void;
/**
 * wave269: non-zero if lexer saw EOF with block-comment nesting depth > 0.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_unclosed_block_comment_pending(): i32;
/**
 * wave271: reset sticky unclosed string state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_unclosed_string_reset(): void;
/**
 * wave271: non-zero if lexer saw EOF inside a double-quoted string without closer.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_unclosed_string_pending(): i32;
/**
 * wave272: reset sticky illegal-character state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_illegal_char_reset(): void;
/**
 * wave272: non-zero if lexer saw an unknown/illegal source byte.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_illegal_char_pending(): i32;
/**
 * wave273: reset sticky incomplete-hex state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_hex_reset(): void;
/**
 * wave273: non-zero if lexer saw `0x`/`0X` with zero hex digits.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_hex_pending(): i32;
/**
 * wave274: reset sticky incomplete-float-exponent state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_exp_reset(): void;
/**
 * wave274: non-zero if lexer saw `e`/`E` (optional sign) with zero exponent digits.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_exp_pending(): i32;
/**
 * wave276: reset sticky incomplete-binary state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_bin_reset(): void;
/**
 * wave276: non-zero if lexer saw `0b`/`0B` with zero binary digits.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_bin_pending(): i32;
/**
 * wave276: reset sticky incomplete-octal state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_oct_reset(): void;
/**
 * wave276: non-zero if lexer saw `0o`/`0O` with zero octal digits.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_incomplete_oct_pending(): i32;
/**
 * wave278: reset sticky invalid digit-separator state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_digit_sep_reset(): void;
/**
 * wave278: non-zero if lexer saw trailing/consecutive/`_` not followed by radix digit.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_digit_sep_pending(): i32;
/**
 * wave279: reset sticky invalid type-suffix state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_type_suffix_reset(): void;
/**
 * wave279: non-zero if lexer saw alphabetic type suffix after a complete numeric literal.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_type_suffix_pending(): i32;
/**
 * wave281: reset sticky invalid string-escape state before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_escape_reset(): void;
/**
 * wave281: non-zero if lexer saw invalid/incomplete string escape (`\q`, incomplete `\x`).
 * PLATFORM: SHARED
 */
export extern "C" function lexer_invalid_escape_pending(): i32;
/**
 * wave283: reset sticky string-literal capacity overflow (L011) before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_string_lit_overflow_reset(): void;
/**
 * wave283: non-zero if string decode would exceed Expr.var_name cap 127 (L011).
 * PLATFORM: SHARED
 */
export extern "C" function lexer_string_lit_overflow_pending(): i32;
/**
 * wave284: reset sticky identifier-too-long state (L012) before each product parse.
 * PLATFORM: SHARED
 */
export extern "C" function lexer_ident_too_long_reset(): void;
/**
 * wave284: non-zero if non-keyword ident span exceeds AST name cap 127 (L012).
 * PLATFORM: SHARED
 */
export extern "C" function lexer_ident_too_long_pending(): i32;

#[no_mangle]
export function driver_parse_into_buf_rc(
  arena: *u8, module: *u8, data: *u8, len: i32, out_main_idx: *i32
): i32 {
  if (out_main_idx != 0 as *i32) {
    out_main_idx[0] = -1;
  }
  if (arena == 0 as *u8) {
    return -1;
  }
  if (module == 0 as *u8) {
    return -1;
  }
  if (data == 0 as *u8) {
    return -1;
  }
  // wave269–wave284: clear sticky L001–L012 state for this entry.
  unsafe {
    lexer_unclosed_block_comment_reset();
    lexer_unclosed_string_reset();
    lexer_illegal_char_reset();
    lexer_incomplete_hex_reset();
    lexer_incomplete_exp_reset();
    lexer_incomplete_bin_reset();
    lexer_incomplete_oct_reset();
    lexer_invalid_digit_sep_reset();
    lexer_invalid_type_suffix_reset();
    lexer_invalid_escape_reset();
    lexer_string_lit_overflow_reset();
    lexer_ident_too_long_reset();
  }
  let rc: i32 = 0;
  unsafe {
    rc = xlang_parser_parse_into_buf_rc(arena, module, data, len, out_main_idx);
  }
  // Hard-fail when skip swallowed to EOF with unclosed /* ... (L001 already emitted),
  // string lex hit EOF without closer (L002), illegal/unknown byte (L003),
  // incomplete hex (L004), incomplete float exp (L005), incomplete binary (L006),
  // incomplete octal (L007), invalid digit separator (L008), invalid type suffix (L009),
  // invalid string escape (L010), string literal capacity overflow (L011),
  // or identifier too long (L012).
  unsafe {
    if (lexer_unclosed_block_comment_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_unclosed_string_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_illegal_char_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_incomplete_hex_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_incomplete_exp_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_incomplete_bin_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_incomplete_oct_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_invalid_digit_sep_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_invalid_type_suffix_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_invalid_escape_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_string_lit_overflow_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
    if (lexer_ident_too_long_pending() != 0) {
      if (out_main_idx != 0 as *i32) {
        out_main_idx[0] = -1;
      }
      return -1;
    }
  }
  return rc;
}

// ---- Wave39 Cap residual pure: stdio stdout + asm fwrite + x_emit fwrite_stdout ----
// G.7: reuse wave26 g05 harness (xlang_driver_stdout_ptr / xlang_driver_fwrite_opaque).
// driver_x_emit_fwrite_stdout returns written byte count (not 0/1); residual
//   xlang_driver_fwrite_stdout_n hides the xlang_io_write(1, ...) Cap io write
//   and the count ABI (name historical; no libc fwrite since 9.7.1).
// wave40 owns stderr / fflush_stdout / fopen_wb / write_metric_o (see below).
// wave41 owns mkstemp_fdopen. Still seed OS residual: sibling / usage / exec.
// PLATFORM: SHARED — Cap residual pure under PREFER hybrid.

/**
 * Cap OS residual: fwrite to stdout and fflush; return bytes written.
 * @param data *u8 — bytes to write; caller pure rejects null / non-positive len
 * @param len i32 — byte count (must be > 0 when called from pure)
 * @return i32 — fwrite byte count (may be short on partial write)
 * PLATFORM: SHARED — FILE* stdout cast stays seed rest (no FILE* in .x).
 */
export extern "C" function xlang_driver_fwrite_stdout_n(data: *u8, len: i32): i32;

/**
 * Opaque stdout FILE* as *u8 for rt_entry / rt_run_exec diag print paths.
 * @return *u8 — never null on hosted product (stdout stream handle)
 * Wave39 pure: G.7 xlang_driver_stdout_ptr (wave26 g05 harness); cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — Cap residual pure under PREFER hybrid.
 */
#[no_mangle]
export function driver_stdio_stdout(): *u8 {
  unsafe {
    return xlang_driver_stdout_ptr();
  }
  return 0 as *u8;
}

/**
 * Write len bytes to opaque FILE* (or stdout when fp is null).
 * @param fp *u8 — opaque FILE*; null → stdout via g05 stdout_ptr
 * @param data *u8 — bytes; null or len <= 0 → return 0 (success no-op)
 * @param len i32 — byte count; len <= 0 → return 0
 * @return i32 — 0 full write success; 1 short write / stream error
 * Wave39 pure: null/len guards pure; stream select + g05 xlang_driver_fwrite_opaque.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_asm_fwrite(fp: *u8, data: *u8, len: i32): i32 {
  let stream: *u8 = fp;
  if (data == 0 as *u8) {
    return 0;
  }
  if (len <= 0) {
    return 0;
  }
  if (stream == 0 as *u8) {
    unsafe {
      stream = xlang_driver_stdout_ptr();
    }
  }
  unsafe {
    return xlang_driver_fwrite_opaque(data, len, stream);
  }
  return 1;
}

/**
 * Write len bytes to stdout and fflush; return written count (not 0/1).
 * @param data *u8 — bytes; null or len <= 0 → return 0
 * @param len i32 — byte count; len <= 0 → return 0
 * @return i32 — fwrite byte count after residual fflush
 * Wave39 pure: null/len guards pure; Cap OS residual xlang_driver_fwrite_stdout_n.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_x_emit_fwrite_stdout(data: *u8, len: i32): i32 {
  if (data == 0 as *u8) {
    return 0;
  }
  if (len <= 0) {
    return 0;
  }
  unsafe {
    return xlang_driver_fwrite_stdout_n(data, len);
  }
  return 0;
}

// ---- Wave40 Cap residual pure: stderr + fflush_stdout + fopen_wb + write_metric_o ----
// G.7: extend wave26/27 g05 harness (stderr_ptr / fflush_stdout / fopen_wb_opaque).
// fopen_wb uses mode "wb" (binary) — not fopen_write_opaque "w" (text C emit).
// write_metric_o pure orch: open + one-byte 0 fwrite + fclose (no fputc in .x).
// wave41 owns mkstemp_fdopen (see below). Still seed OS residual: sibling/usage/exec.
// PLATFORM: SHARED — Cap residual pure under PREFER hybrid.

/** g05 prologue: opaque identity of host stderr as *u8.
 * PLATFORM: SHARED — harness residual; product pure returns pointer only. */
export extern "C" function xlang_driver_stderr_ptr(): *u8;
/** g05 prologue: fflush(stdout). PLATFORM: SHARED — harness residual. */
export extern "C" function xlang_driver_fflush_stdout(): void;
/** g05 prologue: fopen(path,"wb") as opaque *u8; null path → null.
 * PLATFORM: SHARED — binary write; distinct from fopen_write_opaque "w". */
export extern "C" function xlang_driver_fopen_wb_opaque(path: *u8): *u8;

/** Single zero byte for pure write_metric_o (one-byte metric .o payload).
 * PLATFORM: SHARED — BSS lit array base; read-only payload for fwrite. */
let g_driver_metric_zero_byte: u8[1] = [0];

/**
 * Opaque stderr FILE* as *u8 for rt_entry diag print paths.
 * @return *u8 — never null on hosted product (stderr stream handle)
 * Wave40 pure: G.7 xlang_driver_stderr_ptr (wave26 harness sibling of stdout_ptr).
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_stdio_stderr(): *u8 {
  unsafe {
    return xlang_driver_stderr_ptr();
  }
  return 0 as *u8;
}

/**
 * fflush(stdout) for asm emit-to-stdout paths.
 * @return void
 * Wave40 pure: G.7 xlang_driver_fflush_stdout g05 harness.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_asm_fflush_stdout(): void {
  unsafe {
    xlang_driver_fflush_stdout();
  }
}

/**
 * fopen(path, "wb") as opaque FILE* for asm binary object write.
 * @param path *u8 — NUL-terminated path; null → null
 * @return *u8 — opaque FILE* or null on failure / null path
 * Wave40 pure: null guard pure; g05 xlang_driver_fopen_wb_opaque (mode "wb").
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED — binary mode (not text "w").
 */
#[no_mangle]
export function driver_asm_fopen_wb(path: *u8): *u8 {
  if (path == 0 as *u8) {
    return 0 as *u8;
  }
  unsafe {
    return xlang_driver_fopen_wb_opaque(path);
  }
  return 0 as *u8;
}

/**
 * Write a one-byte 0 metric object file at path (parse-metric-only smoke).
 * @param path *u8 — output path; null → 1 (fail)
 * @return i32 — 0 success; 1 open/write/close failure
 * Wave40 pure: null guard + fopen_wb + fwrite_opaque one 0 byte + fclose_opaque.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED.
 */
#[no_mangle]
export function driver_asm_write_metric_o(path: *u8): i32 {
  let fp: *u8 = 0 as *u8;
  let z: *u8 = 0 as *u8;
  if (path == 0 as *u8) {
    return 1;
  }
  unsafe {
    fp = xlang_driver_fopen_wb_opaque(path);
  }
  if (fp == 0 as *u8) {
    return 1;
  }
  z = &g_driver_metric_zero_byte[0];
  unsafe {
    if (xlang_driver_fwrite_opaque(z, 1, fp) != 0) {
      xlang_driver_fclose_opaque(fp);
      return 1;
    }
    return xlang_driver_fclose_opaque(fp);
  }
  return 1;
}

// ---- Wave41 Cap residual pure: driver_asm_mkstemp_fdopen ----
// G.7: reuse wave27 open_out helpers (tmp_prefix + cstr_copy/cat + mkstemp/close/unlink).
// Cap residual split:
//   - seed always: xlang_driver_asm_mkstemp_fdopen_enabled (SHARED → 1; MinGW mkstemp OK)
//   - g05 prologue: xlang_driver_fdopen_wb_opaque(fd) hides FILE* fdopen("wb")
//   - pure orch: null guard, enable gate, template fill into path_out64, mkstemp,
//     fdopen; fail → close+unlink+clear path[0]
// Wave42 owns exec_compiled_body (see below).
// PLATFORM: SHARED orch; WINDOWS|POSIX enabled (closes want-exe BLD001 host-cc fallback).

/**
 * Host gate for asm mkstemp+fdopen: 1 on all product hosts (incl. Windows MinGW).
 * @return i32 — 1 enabled; 0 disabled (pure returns null without OS calls)
 * PLATFORM: SHARED — WINDOWS|POSIX|LINUX|MACOS return 1. Always-seed residual.
 */
export extern "C" function xlang_driver_asm_mkstemp_fdopen_enabled(): i32;
/**
 * g05 prologue: fdopen(fd, "wb") as opaque *u8; failure → null (caller closes fd).
 * @param fd i32 — open file descriptor from mkstemp
 * @return *u8 — opaque FILE* or null
 * PLATFORM: SHARED — harness FILE* cast residual (no FILE* in .x).
 */
export extern "C" function xlang_driver_fdopen_wb_opaque(fd: i32): *u8;

/**
 * Fill path_out64 with a unique temp path and fdopen it for binary asm object write.
 * @param path_out64 *u8 — caller buffer capacity >= 64 including NUL; null → null
 * @return *u8 — opaque FILE* opened "wb", or null on disable/guard/OS failure
 * On failure after mkstemp: close(fd), unlink(path), clear path_out64[0].
 * Wave41 pure: null + enable gate pure; template = tmp_prefix + "xlang_asm_XXXXXX"
 * (reuses wave27 cstr helpers); mkstemp/close/unlink libc; g05 fdopen_wb_opaque.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED orch (WINDOWS MinGW mkstemp enabled).
 */
#[no_mangle]
export function driver_asm_mkstemp_fdopen(path_out64: *u8): *u8 {
  let fd: i32 = 0;
  let fp: *u8 = 0 as *u8;
  let prefix: *u8 = 0 as *u8;
  if (path_out64 == 0 as *u8) {
    return 0 as *u8;
  }
  unsafe {
    // PLATFORM: SHARED — gate is 1 on Windows MinGW and POSIX; fail soft on OS error.
    if (xlang_driver_asm_mkstemp_fdopen_enabled() == 0) {
      return 0 as *u8;
    }
    prefix = xlang_driver_tmp_prefix();
  }
  // Cap 64 matches cold snprintf(path_out64, 64, ...) and wave25 asm tmp slot.
  driver_open_out_cstr_copy(path_out64, 64, prefix);
  // Short suffix keeps under -E string cap (~63); XXXXXX mutated by mkstemp.
  driver_open_out_cstr_cat(path_out64, 64, "xlang_asm_XXXXXX");
  unsafe {
    fd = mkstemp(path_out64);
  }
  if (fd < 0) {
    return 0 as *u8;
  }
  unsafe {
    fp = xlang_driver_fdopen_wb_opaque(fd);
  }
  if (fp == 0 as *u8) {
    // Match cold: close fd, unlink template path, clear first byte for callers.
    unsafe {
      close(fd);
      unlink(path_out64);
    }
    path_out64[0] = 0;
    return 0 as *u8;
  }
  return fp;
}

// ---- Wave42 Cap residual pure: driver_exec_compiled_body ----
// G.7: reuse pure driver_exec_path_is_non_exe (rt_run_exec.x).
// Cap residual split:
//   - seed always: xlang_driver_exec_scan_out_path_opaque (*u8 argv → cast + scan)
//   - seed always: xlang_driver_exec_spawn_wait (fork/exec or spawnvp + wait)
//   - pure orch: null/argc guard, resolve exe, non-exe early 0, spawn residual
// Wave43 owns sibling_try_spawn; wave44 owns print_usage_write (see below).
// PLATFORM: SHARED orch; WINDOWS spawn vs POSIX fork in residual.

/**
 * Cap residual: cast opaque argv (*u8) to char** and call driver_exec_scan_out_path.
 * @param argc i32 — argv length; pure already rejects argc < 1
 * @param argv_opaque *u8 — opaque char** from cmd_run; null → null
 * @return *u8 — product path (may be "a.out" heap) or null
 * PLATFORM: SHARED — *u8→**u8 cast residual (.x -E drops cast body). Always-seed.
 */
export extern "C" function xlang_driver_exec_scan_out_path_opaque(argc: i32, argv_opaque: *u8): *u8;
/**
 * Cap residual: run product exe and wait for exit status (spawn/fork/exec).
 * 9.4.3 C ABI argv: the child receives [exe] + user positionals after the .x
 * source path in run_argv; driver flags (and the "-o" pair, injected temp or
 * explicit) stay driver-owned and are not forwarded. argv[0] = exe path.
 * @param exe *u8 — NUL-terminated path; null → 1
 * @param argc i32 — run_argv length; out of [1,512] or null argv → exe-only child
 * @param argv_opaque *u8 — opaque char** run_argv from cmd_run; null allowed
 * @return i32 — process exit code, or 1 on spawn/wait failure
 * PLATFORM: WINDOWS _spawnvp; POSIX fork+execv+xlang_waitpid_retry. Always-seed.
 */
export extern "C" function xlang_driver_exec_spawn_wait(exe: *u8, argc: i32, argv_opaque: *u8): i32;
/**
 * G.7: pure non-exe gate already in rt_run_exec.x (suffix .o/.obj/.s).
 * @param exe *u8 — product path; null treated as non-exe
 * @return i32 — 1 if non-executable product suffix (skip spawn); 0 if should exec
 * PLATFORM: SHARED — link-name contract with rt_run_exec.
 */
export extern "C" function driver_exec_path_is_non_exe(exe: *u8): i32;

/**
 * After successful compile, resolve -o path and exec the product binary.
 * @param argc i32 — argv length; argc < 1 → 1
 * @param argv_opaque *u8 — opaque char** (cmd_run ABI); null → 1
 * @return i32 — 0 if path is non-exe (.o/.s); else child exit or 1 on failure
 * Wave42 pure: null/argc guards pure; resolve via scan opaque residual; non-exe via
 * G.7 driver_exec_path_is_non_exe; OS process residual xlang_driver_exec_spawn_wait.
 * Cold twin under #ifndef FROM_X. PLATFORM: SHARED orch; spawn residual OS-split.
 */
#[no_mangle]
export function driver_exec_compiled_body(argc: i32, argv_opaque: *u8): i32 {
  let exe: *u8 = 0 as *u8;
  if (argv_opaque == 0 as *u8) {
    return 1;
  }
  if (argc < 1) {
    return 1;
  }
  // Cap residual: *u8→char** cast + scan; G.7 non-exe gate; OS spawn residual.
  // All three are C/extern surfaces → require unsafe (T001).
  unsafe {
    exe = xlang_driver_exec_scan_out_path_opaque(argc, argv_opaque);
    // G.7: single authority for non-exe suffix gate (rt_run_exec pure).
    if (driver_exec_path_is_non_exe(exe) != 0) {
      return 0;
    }
    // Cap residual: fork/exec or Windows spawnvp + wait (process OS boundary).
    // 9.4.3: run_argv rides along so user positionals after the .x source path
    // become the child's argv (C ABI argc/argv for the compiled program).
    return xlang_driver_exec_spawn_wait(exe, argc, argv_opaque);
  }
  return 1;
}

// ---- Wave43 Cap residual pure: driver_dispatch_sibling_try_spawn ----
// G.7: reuse pure driver_argv0_basename_is (rt_util.x) — no second basename path.
// Cap residual split:
//   - seed always: xlang_driver_sibling_argv0_get (*u8 argv → cast + av[0])
//   - seed always: xlang_driver_sibling_access_spawn (access X_OK + fork/exec or spawnvp)
//   - pure orch: null/argc guard, basename "xlang-c" early -1, path BSS 512 pure, residual
// Wave44 owns print_usage_write (see below). PLATFORM: SHARED orch;
// WINDOWS \\ sep + spawnvp vs POSIX / + fork in residual.

/** Module BSS for sibling path "dir/xlang-c"; capacity matches cold char xlang_c[512]. */
let g_driver_sibling_path_buf: u8[512] = [];

/**
 * Cap residual: cast opaque argv (*u8) to char** and return av[0].
 * @param argv_opaque *u8 — opaque char**; null or av[0] null → null
 * @return *u8 — argv[0] path or null
 * PLATFORM: SHARED — *u8→**u8 cast residual (.x -E drops cast body). Always-seed.
 */
export extern "C" function xlang_driver_sibling_argv0_get(argv_opaque: *u8): *u8;
/**
 * Cap residual: access(path, X_OK) then replace av[0] and spawn/fork wait.
 * @param path *u8 — NUL-terminated sibling xlang-c path; null → -1
 * @param argc i32 — argv length (unused except spawn inherits av)
 * @param argv_opaque *u8 — opaque char**; null → -1
 * @return i32 — child exit status, or -1 if not executable / spawn failure
 * PLATFORM: WINDOWS _spawnvp; POSIX fork+execvp+waitpid. Always-seed.
 */
export extern "C" function xlang_driver_sibling_access_spawn(
  path: *u8, argc: i32, argv_opaque: *u8
): i32;
/**
 * G.7: pure basename compare already in rt_util.x (supports / and \\).
 * @param argv0 *u8 — full path or bare name; null matches only empty base
 * @param base *u8 — expected basename; null → 0
 * @return i32 — 1 if basename equals base; 0 otherwise
 * PLATFORM: SHARED — link-name contract with rt_util.
 */
export extern "C" function driver_argv0_basename_is(argv0: *u8, base: *u8): i32;

/**
 * Build sibling path into out[cap]: dirname(self)+"/xlang-c" or bare "xlang-c".
 * @param self *u8 — argv0 path; null → -1
 * @param out *u8 — destination buffer; null → -1
 * @param cap i32 — capacity including NUL; must be > 8 (room for "/xlang-c")
 * @return i32 — 0 success; -1 null/oversized dirname
 * Scans last '/' (47) or '\\' (92); matches cold strrchr + Windows \\ preference.
 * PLATFORM: SHARED path bytes; always emits '/' before "xlang-c" (cold strcat same).
 */
#[no_mangle]
export function driver_sibling_path_from_self(self: *u8, out: *u8, cap: i32): i32 {
  let i: i32 = 0;
  let last: i32 = 0 - 1;
  let j: i32 = 0;
  let c: u8 = 0;
  if (self == 0 as *u8) {
    return 0 - 1;
  }
  if (out == 0 as *u8) {
    return 0 - 1;
  }
  if (cap <= 8) {
    return 0 - 1;
  }
  // Find last path separator (POSIX / or Windows \\), cap scan 4096.
  while (i < 4096) {
    c = self[i];
    if (c == 0) {
      break;
    }
    if (c == 47) {
      last = i;
    }
    if (c == 92) {
      last = i;
    }
    i = i + 1;
  }
  if (last < 0) {
    // Bare name: cold strcpy(xlang_c, "xlang-c").
    driver_open_out_cstr_copy(out, cap, "xlang-c");
    return 0;
  }
  // Cold: dir_len = slash - self; reject if dir_len >= sizeof - 8.
  if (last >= cap - 8) {
    return 0 - 1;
  }
  // Copy dirname excluding trailing separator, then append "/xlang-c".
  j = 0;
  while (j < last) {
    out[j] = self[j];
    j = j + 1;
  }
  out[j] = 0;
  driver_open_out_cstr_cat(out, cap, "/xlang-c");
  return 0;
}

/**
 * Try spawn same-dir xlang-c sibling with the caller's argv (dispatch via xlang-c).
 * @param argc i32 — argv length; argc < 2 → -1 (need argv0 + at least one more)
 * @param argv_opaque *u8 — opaque char** from entry; null → -1
 * @return i32 — child exit status if delegated; -1 if not delegated
 *   (self is already xlang-c, path not X_OK, spawn fail, or guard fail)
 * Wave43 pure: null/argc pure; argv0 via Cap residual; G.7 basename_is pure;
 * path pure into BSS 512; OS residual access+spawn. Cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED orch; residual holds WIN vs POSIX process boundary.
 */
#[no_mangle]
export function driver_dispatch_sibling_try_spawn(argc: i32, argv_opaque: *u8): i32 {
  let self: *u8 = 0 as *u8;
  let path: *u8 = 0 as *u8;
  let pr: i32 = 0;
  if (argv_opaque == 0 as *u8) {
    return 0 - 1;
  }
  if (argc < 2) {
    return 0 - 1;
  }
  // Cap residual: *u8→char** cast + av[0]; G.7 basename; OS access+spawn.
  // Extern surfaces require unsafe (T001).
  unsafe {
    self = xlang_driver_sibling_argv0_get(argv_opaque);
    if (self == 0 as *u8) {
      return 0 - 1;
    }
    // G.7: single authority for argv0 basename (rt_util pure).
    if (driver_argv0_basename_is(self, "xlang-c") != 0) {
      return 0 - 1;
    }
  }
  path = &g_driver_sibling_path_buf[0];
  pr = driver_sibling_path_from_self(self, path, 512);
  if (pr != 0) {
    return 0 - 1;
  }
  unsafe {
    // Cap residual: access X_OK + fork/exec or Windows spawnvp + wait.
    return xlang_driver_sibling_access_spawn(path, argc, argv_opaque);
  }
  return 0 - 1;
}

// ---- Wave44 Cap residual pure: driver_print_usage_write ----
// Color policy pure (analysis/XLANG 命令行.md §13 / no-color.org):
//   NO_COLOR set (any value, even empty) → no color
//   CLICOLOR_FORCE / XLANG_FORCE_COLOR truthy → force color even when piped
//   otherwise → isatty(1)
// Cap residual always-seed: xlang_driver_usage_write_stdout(use_color)
//   holds giant plain + ANSI color multi-line tables, written to fd 1 via
//   xlang_io_write (Cap io face; no libc FILE star since 9.7.1).
// Root cause for residual: .x -E drops / mis-encodes long \\n string lits — not a
// single-line workaround; table authority stays one seed residual (G.7).
// PLATFORM: SHARED orch; isatty OS surface; lit tables via Cap io write.

/**
 * Cap residual: write usage plain or color table to stdout (fd 1) via
 * xlang_io_write (Cap io; no libc FILE star / stdout).
 * @param use_color i32 — non-zero selects ANSI color table; zero selects plain
 * PLATFORM: SHARED — giant lit tables + Cap io write. Always-seed (no pure-dup).
 */
export extern "C" function xlang_driver_usage_write_stdout(use_color: i32): void;

/**
 * Print xlang CLI usage summary to stdout (fd1 / stdout FILE*).
 * Wave44 pure: color policy orch reuses G.7 driver_env_nonnull / driver_env_flag_truthy
 * (same truthiness as cold getenv checks); isatty(1) for TTY default; Cap residual
 * holds multi-line usage tables + write. Cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED orch; residual owns giant lit + Cap io write.
 */
#[no_mangle]
export function driver_print_usage_write(): void {
  let use_color: i32 = 0;
  // NO_COLOR any presence (including empty) disables color — https://no-color.org
  if (driver_env_nonnull("NO_COLOR") != 0) {
    use_color = 0;
  } else if (driver_env_flag_truthy("CLICOLOR_FORCE") != 0) {
    use_color = 1;
  } else if (driver_env_flag_truthy("XLANG_FORCE_COLOR") != 0) {
    use_color = 1;
  } else {
    // Default: color only when stdout is a TTY.
    unsafe {
      use_color = isatty(1);
    }
  }
  // Cap residual: plain/color tables via xlang_io_write(1, ...) (giant lit authority).
  unsafe {
    xlang_driver_usage_write_stdout(use_color);
  }
}
