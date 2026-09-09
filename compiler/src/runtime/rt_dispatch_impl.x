// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
//   USE_X_DRIVER+PIPELINE + NO_C_FRONTEND + ASM_USE_COMPILER_IMPL_C
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
// Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.

/* See signature and body for contracts. */
export struct RtDispatchState {
  path_buf: u8[512];
  path_len: i32;
  out_path_buf: u8[512];
  out_path_len: i32;
  use_asm_backend: i32;
  target_arch: i32;
  target_buf: u8[512];
  target_len: i32;
  opt_level_buf: u8[8];
  opt_level_len: i32;
  use_lto: i32;
  backend_asm_explicit: i32;
  use_freestanding: i32;
  parse_saw_target: i32;
  target_cpu_buf: u8[128];
  target_cpu_len: i32;
  target_cpu_features: i32;
  print_target_cpu: i32;
  parse_saw_target_cpu: i32;
}

/* wave227 G.7: env lookup via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl. */
export extern "C" function link_abi_getenv(name: *u8): *u8;
export extern "C" function strlen(s: *u8): usize;
export extern "C" function strcmp(a: *u8, b: *u8): i32;
export extern "C" function driver_get_argv_i(argc: i32, argv: *u8, i: i32, buf: *u8, max: i32): i32;
export extern "C" function malloc(n: usize): *u8;
export extern "C" function free(p: *u8): void;

export extern "C" function driver_set_pending_target_cpu_features(features: u32): void;
export extern "C" function driver_run_asm_backend(
  input_path: *u8, out_path: *u8, lib_roots: *u8, n_lib: i32,
  target: *u8, argc: i32, argv: *u8): i32;
export extern "C" function driver_check_only_get(): i32;
export extern "C" function driver_source_has_top_level_import_path(path: *u8): i32;
export extern "C" function driver_asm_entry_module_only_from_env(): i32;
export extern "C" function driver_argv_has_emit_c_flag(argc: i32, argv: *u8): i32;
export extern "C" function driver_asm_output_want_exe(path: *u8): i32;
export extern "C" function driver_source_has_generic_syntax(path: *u8, path_len: i32): i32;
export extern "C" function driver_freestanding_set(v: i32): void;
export extern "C" function cfg_set_freestanding(v: i32): void;
export extern "C" function driver_run_x_emit_c_set_emit_extern(v: i32): i32;
export extern "C" function driver_run_x_emit_c_set_path(path: *u8, path_len: i32): i32;
export extern "C" function driver_run_x_emit_c_set_lib(i: i32, buf: *u8, len: i32): i32;
export extern "C" function driver_run_x_emit_c_set_n_lib_roots(n: i32): i32;
export extern "C" function driver_run_x_emit_c(): i32;
export extern "C" function runtime_try_handle_explain_cli(argc: i32, argv: *u8): i32;
export extern "C" function driver_compile_argv_is_help_c(argc: i32, argv: *u8): i32;
export extern "C" function driver_print_usage_c(): void;
export extern "C" function driver_bump_stack_limit(): void;
export extern "C" function driver_compile_state_alloc_c(): *RtDispatchState;
export extern "C" function driver_compile_state_free_c(state: *RtDispatchState): void;
export extern "C" function driver_compile_parse_argv_impl_c(
  argc: i32, argv: *u8, state: *RtDispatchState): i32;
export extern "C" function xlang_target_cpu_print(out: *u8, features: u32): void;
export extern "C" function driver_stdio_stdout(): *u8;

export extern "C" function driver_dispatch_lib_roots_from_key(lib_key: *u8, n_out: *i32): *u8;
export extern "C" function driver_dispatch_lib_root_at(roots: *u8, i: i32): *u8;
export extern "C" function driver_dispatch_run_compiler_parsed(
  input_path: *u8, out_path: *u8, lib_roots: *u8, n_lib: i32,
  target: *u8, opt_level: *u8, use_lto: i32, argc: i32, argv: *u8): i32;
export extern "C" function driver_dispatch_opt_default(): *u8;

/** Allocate a heap C string "XLANG_LTO\0" (byte-built; no string-literal dependency).
 * Returns malloc'd pointer or null on OOM. Caller must free when done.
 * Track-L: #[no_mangle] keeps surface short name (not rt_dispatch_impl_rt_di_env_xlang_lto).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_di_env_xlang_lto(): *u8 {
  let p: *u8 = 0 as *u8;
  unsafe {
    p = malloc(16 as usize);
  }
  if (p == 0 as *u8) {
    return 0 as *u8;
  }
  // S H U X _ L T O \0
  p[0] = 83;
  p[1] = 72;
  p[2] = 85;
  p[3] = 88;
  p[4] = 95;
  p[5] = 76;
  p[6] = 84;
  p[7] = 79;
  p[8] = 0;
  return p;
}

/** Return 1 if any argv[1..] token equals "-E-extern" (exactly 9 payload bytes).
 * Copies each arg via driver_get_argv_i into a 32-byte malloc buffer, then compares
 * bytes for '-' 'E' '-' 'e' 'x' 't' 'e' 'r' 'n'. Frees the buffer before return.
 * Track-L: #[no_mangle] keeps surface short name (not module-prefixed mangle).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_di_argv_has_e_extern(argc: i32, argv: *u8): i32 {
  let k: i32 = 1;
  let buf: *u8 = 0 as *u8;
  let n: i32 = 0;
  unsafe {
    buf = malloc(32 as usize);
  }
  if (buf == 0 as *u8) {
    return 0;
  }
  while (k < argc) {
    unsafe {
      n = driver_get_argv_i(argc, argv, k, buf, 31);
    }
    // n==9 means nine significant bytes (no room for longer tokens to false-match).
    if (n == 9) {
      if (buf[0] == 45 && buf[1] == 69 && buf[2] == 45 && buf[3] == 101 && buf[4] == 120
          && buf[5] == 116 && buf[6] == 101 && buf[7] == 114 && buf[8] == 110) {
        unsafe {
          free(buf);
        }
        return 1;
      }
    }
    k = k + 1;
  }
  unsafe {
    free(buf);
  }
  return 0;
}

/**
 * Effective LTO enable: explicit use_lto, or XLANG_LTO equal to "1".
 * Frees the temporary env-name buffer from rt_di_env_xlang_lto after lookup.
 * @param use_lto i32 — explicit CLI/driver LTO flag; non-zero forces enable
 * @return i32 — 1 LTO on, 0 off
 * Track-L: #[no_mangle] keeps surface short name (not rt_dispatch_impl_rt_di_effective_use_lto).
 * wave227 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED — link-name contract; host residual only link_abi_getenv_impl.
 */
#[no_mangle]
export function rt_di_effective_use_lto(use_lto: i32): i32 {
  let env_name: *u8 = 0 as *u8;
  let env_val: *u8 = 0 as *u8;
  if (use_lto != 0) {
    return 1;
  }
  env_name = rt_di_env_xlang_lto();
  if (env_name == 0 as *u8) {
    return 0;
  }
  unsafe {
    env_val = link_abi_getenv(env_name);
    free(env_name);
  }
  if (env_val == 0 as *u8) {
    return 0;
  }
  // Exact "1\0" only (ASCII 49 then NUL).
  if (env_val[0] == 49 && env_val[1] == 0) {
    return 1;
  }
  return 0;
}

/* See signature and body for contracts. */
#[no_mangle]
export function driver_run_asm_backend_impl_c(
  input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8,
  argc: i32, argv: *u8
): i32 {
  let n: i32 = 0;
  let roots: *u8 = 0 as *u8;
  let feat: u32 = 0;
  let tgt: *u8 = 0 as *u8;
  unsafe {
    roots = driver_dispatch_lib_roots_from_key(lib_key, &n);
  }
  if (lib_key != 0 as *u8) {
    let st: *RtDispatchState = lib_key as *RtDispatchState;
    feat = st.target_cpu_features as u32;
  }
  unsafe {
    driver_set_pending_target_cpu_features(feat);
  }
  if (target != 0 as *u8) {
    if (target[0] != 0) {
      tgt = target;
    }
  }
  unsafe {
    return driver_run_asm_backend(input_path, out_path, roots, n, tgt, argc, argv);
  }
  return 1;
}

/**
 * C-backend dispatch: lib_key → lib_roots, then driver_dispatch_run_compiler_parsed.
 * Leftover !XLANG_NO_C_FRONTEND sibling xlang-c demote lived only in the
 * cold seed twin (rt_dispatch_impl.from_x.c). This product body never
 * called driver_try_compile_via_shu_c_sibling; the spawn helper stays in
 * rt_dispatch_thin (HAS a real fork/exec body, different class).
 * @param input_path *u8 — entry source path; forwarded to parsed
 * @param out_path *u8 — optional -o path; null allowed
 * @param lib_key *u8 — opaque compile-state / lib_roots sidecar
 * @param target *u8 — optional target triple; empty treated as null
 * @param opt_level *u8 — optional opt; empty falls back to driver_dispatch_opt_default
 * @param use_lto i32 — explicit LTO flag; also honors XLANG_LTO=1
 * @param argc i32 — argv count forwarded to parsed
 * @param argv *u8 — opaque argv pointer forwarded to parsed
 * @return i32 — parsed dispatch status
 * PLATFORM: SHARED — product authority; leftover consume site retired in
 * the cold seed twin (this knife). Spawn body not deleted.
 */
#[no_mangle]
export function driver_run_emit_c_path_impl_c(
  input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8,
  opt_level: *u8, use_lto: i32, argc: i32, argv: *u8
): i32 {
  let n: i32 = 0;
  let roots: *u8 = 0 as *u8;
  let tgt: *u8 = 0 as *u8;
  let opt: *u8 = 0 as *u8;
  let lto: i32 = 0;
  unsafe {
    roots = driver_dispatch_lib_roots_from_key(lib_key, &n);
  }
  if (target != 0 as *u8) {
    if (target[0] != 0) {
      tgt = target;
    }
  }
  if (opt_level != 0 as *u8) {
    if (opt_level[0] != 0) {
      opt = opt_level;
    }
  }
  if (opt == 0 as *u8) {
    unsafe {
      opt = driver_dispatch_opt_default();
    }
  }
  lto = rt_di_effective_use_lto(use_lto);
  // Always parsed. Do not re-add sibling xlang-c demote on top-level import.
  unsafe {
    return driver_dispatch_run_compiler_parsed(
      input_path, out_path, roots, n, tgt, opt, lto, argc, argv);
  }
  return 1;
}

/* See signature and body for contracts. */
#[no_mangle]
export function driver_run_x_emit_c_from_compile_state(
  state: *RtDispatchState, argc: i32, argv: *u8
): i32 {
  let want_extern: i32 = 0;
  let n: i32 = 0;
  let roots: *u8 = 0 as *u8;
  let k: i32 = 0;
  let row: *u8 = 0 as *u8;
  let llen: usize = 0;
  let dot: *u8 = 0 as *u8;
  if (state == 0 as *RtDispatchState) {
    return 1;
  }
  if (state.path_len <= 0) {
    return 1;
  }
  want_extern = rt_di_argv_has_e_extern(argc, argv);
  unsafe {
    driver_run_x_emit_c_set_emit_extern(want_extern);
    driver_run_x_emit_c_set_path(&state.path_buf[0], state.path_len);
    roots = driver_dispatch_lib_roots_from_key(state as *u8, &n);
  }
  if (n <= 0) {
    unsafe {
      dot = malloc(4 as usize);
    }
    if (dot == 0 as *u8) {
      return 1;
    }
    dot[0] = 46;
    dot[1] = 0;
    unsafe {
      driver_run_x_emit_c_set_lib(0, dot, 1);
      driver_run_x_emit_c_set_n_lib_roots(1);
      free(dot);
    }
  } else {
    k = 0;
    while (k < n) {
      unsafe {
        row = driver_dispatch_lib_root_at(roots, k);
      }
      if (row == 0 as *u8) {
        llen = 0 as usize;
      } else {
        unsafe {
          llen = strlen(row);
        }
      }
      unsafe {
        driver_run_x_emit_c_set_lib(k, row, llen as i32);
      }
      k = k + 1;
    }
    unsafe {
      driver_run_x_emit_c_set_n_lib_roots(n);
    }
  }
  unsafe {
    return driver_run_x_emit_c();
  }
  return 1;
}

/* See signature and body for contracts. */
#[no_mangle]
export function driver_run_compiler_full_x_post_parse_impl_c(
  state: *RtDispatchState, argc: i32, argv: *u8
): i32 {
  let out_ptr: *u8 = 0 as *u8;
  let target_ptr: *u8 = 0 as *u8;
  let has_import: i32 = 0;
  if (state == 0 as *RtDispatchState) {
    return 1;
  }
  // Dispatch medium impl (asm/emit/post_parse/full_x); G.9 English; body authoritative.
  unsafe {
    if (driver_argv_has_emit_c_flag(argc, argv) != 0) {
      return driver_run_x_emit_c_from_compile_state(state, argc, argv);
    }
  }
  unsafe {
    if (driver_check_only_get() != 0) {
      state.use_asm_backend = 0;
    }
  }
  /*
   * PLATFORM: SHARED — PC invoke_cc opt-in (2026-08-12): silent generic→C removed.
   * Prior residual: driver_source_has_generic_syntax on want_exe forced C + invoke_cc
   * without `-backend c`. Closed same class as import→C / seed APPLE exe→C.
   * Product host-cc only via explicit `-backend c` (argv) or check-only / emit-c.
   * Keep no-import -o → backend_asm_explicit lock for explicit-asm gate consumers.
   */
  if (state.out_path_len > 0) {
    out_ptr = &state.out_path_buf[0];
  }
  if (state.target_len > 0) {
    target_ptr = &state.target_buf[0];
  }
  if (state.out_path_len > 0) {
    if (state.backend_asm_explicit == 0) {
      unsafe {
        has_import = driver_source_has_top_level_import_path(&state.path_buf[0]);
      }
      if (has_import == 0) {
        state.backend_asm_explicit = 1;
      }
    }
  }
  if (state.use_freestanding != 0) {
    state.use_asm_backend = 1;
    state.backend_asm_explicit = 1;
    unsafe {
      driver_freestanding_set(1);
      cfg_set_freestanding(1);
    }
  }
  if (state.use_asm_backend != 0) {
    return driver_run_asm_backend_impl_c(
      &state.path_buf[0], out_ptr, state as *u8, target_ptr, argc, argv);
  }
  return driver_run_emit_c_path_impl_c(
    &state.path_buf[0], out_ptr, state as *u8, target_ptr,
    &state.opt_level_buf[0], state.use_lto, argc, argv);
}

/** Exported function `driver_run_compiler_full_x_impl_c`.
 * Implements `driver_run_compiler_full_x_impl_c`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
#[no_mangle]
export function driver_run_compiler_full_x_impl_c(argc: i32, argv: *u8): i32 {
  let state: *RtDispatchState = 0 as *RtDispatchState;
  let rc: i32 = 0;
  let explain_rc: i32 = 0;
  let out: *u8 = 0 as *u8;
  unsafe {
    explain_rc = runtime_try_handle_explain_cli(argc, argv);
  }
  if (explain_rc >= 0) {
    return explain_rc;
  }
  unsafe {
    if (driver_compile_argv_is_help_c(argc, argv) != 0) {
      driver_print_usage_c();
      return 0;
    }
  }
  if (argc < 2) {
    unsafe {
      driver_print_usage_c();
    }
    return 0;
  }
  unsafe {
    driver_bump_stack_limit();
    state = driver_compile_state_alloc_c();
  }
  if (state == 0 as *RtDispatchState) {
    return 1;
  }
  unsafe {
    if (driver_compile_parse_argv_impl_c(argc, argv, state) != 0) {
      driver_compile_state_free_c(state);
      return 1;
    }
  }
  if (state.print_target_cpu != 0) {
    unsafe {
      out = driver_stdio_stdout();
      xlang_target_cpu_print(out, state.target_cpu_features as u32);
      driver_compile_state_free_c(state);
    }
    return 0;
  }
  rc = driver_run_compiler_full_x_post_parse_impl_c(state, argc, argv);
  unsafe {
    driver_compile_state_free_c(state);
  }
  return rc;
}
