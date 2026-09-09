// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// G-02f-291～296 / R2 full: compile helpers (deps/flags/apply/init/scan/impl/alloc).
// Product PREFER_X_O: full .x + FROM_X rest is marker only (business H=0).
// Layout matches compile.x DriverCompileState / seeds DriverCompileStateSU.
// Discipline: no let **u8 / no local u8[N] / no || / diag_report_with_code (-E body drop).
// PLATFORM: SHARED — surface short names are the link-name contract (Track L).
// Comment rule: never put star-slash sequences inside block comments.

/** Layout matches seeds/rt_compile.from_x.c DriverCompileStateSU field order.
 * PLATFORM: SHARED — ABI layout must stay seed/.x aligned. */
export struct RtCompileState {
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

export extern "C" function driver_freestanding_set(on: i32): void;
export extern "C" function cfg_set_freestanding(on: i32): void;
export extern "C" function driver_sanitize_address_set(on: i32): void;
export extern "C" function driver_get_argv_i(argc: i32, argv: **u8, i: i32, buf: *u8, max: i32): i32;
export extern "C" function cfg_reset_compile_target(): void;
export extern "C" function driver_emit_lib_root_count(state: *u8): i32;
export extern "C" function driver_emit_append_lib_root(state: *u8, path: *u8, len: i32): i32;
export extern "C" function driver_emit_lib_root_reset(state: *u8): void;
export extern "C" function drv_eq_minus_o(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_L(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_O(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_flto(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_freestanding(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_legacy_f32_abi(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_fsanitize_address(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_backend(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_target(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_minus_target_cpu(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_print_target_cpu(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_asm_word(buf: *u8, len: i32): i32;
export extern "C" function drv_eq_c_word(buf: *u8, len: i32): i32;
export extern "C" function drv_path_ends_x(buf: *u8, len: i32): i32;
export extern "C" function drv_target_has_arm(buf: *u8, len: i32): i32;
export extern "C" function xlang_target_cpu_resolve(spec: *u8, spec_len: usize, out: *u32): i32;
export extern "C" function xlang_target_cpu_generic_for_host(): u32;
export extern "C" function diag_report_with_code(
  file: *u8, line: i32, col: i32, kind: *u8, code: *u8, msg: *u8, detail: *u8): void;
export extern "C" function cfg_apply_compile_target_from_triple(triple: *u8, len: i32): void;
export extern "C" function driver_resolve_target_arch(parsed_target: i32, saw_target_flag: i32): i32;
export extern "C" function setenv(name: *u8, value: *u8, overwrite: i32): i32;
export extern "C" function malloc(n: usize): *u8;
export extern "C" function free(p: *u8): void;
export extern "C" function memset(p: *u8, c: i32, n: usize): *u8;
export extern "C" function strstr(hay: *u8, needle: *u8): *u8;
export extern "C" function strncmp(a: *u8, b: *u8, n: usize): i32;
export extern "C" function strcmp(a: *u8, b: *u8): i32;

/** Return 1 if s starts with pref[0..n) via strncmp. Null s/pref → 0.
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_cmp_starts_with_n).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_cmp_starts_with_n(s: *u8, pref: *u8, n: usize): i32 {
  if (s == 0 as *u8) {
    return 0;
  }
  if (pref == 0 as *u8) {
    return 0;
  }
  unsafe {
    if (strncmp(s, pref, n) == 0) {
      return 1;
    }
  }
  return 0;
}

/** Return 1 if s equals lit via strcmp. Null s/lit → 0.
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_cmp_eq).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_cmp_eq(s: *u8, lit: *u8): i32 {
  if (s == 0 as *u8) {
    return 0;
  }
  if (lit == 0 as *u8) {
    return 0;
  }
  unsafe {
    if (strcmp(s, lit) == 0) {
      return 1;
    }
  }
  return 0;
}

/** Return 1 if hay contains needle (strstr). Null hay/needle → 0.
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_cmp_contains).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_cmp_contains(hay: *u8, needle: *u8): i32 {
  let p: *u8 = 0 as *u8;
  if (hay == 0 as *u8) {
    return 0;
  }
  if (needle == 0 as *u8) {
    return 0;
  }
  unsafe {
    p = strstr(hay, needle);
  }
  if (p != 0 as *u8) {
    return 1;
  }
  return 0;
}

/** Return 1 iff every dep path is a std.* or core.* closure name.
 * Track-L: #[no_mangle] keeps public short name.
 * PLATFORM: SHARED — link-name contract. */
#[no_mangle]
export function driver_deps_are_std_core_closure_only(dep_paths: **u8, n_deps: i32): i32 {
  let k: i32 = 0;
  let p: *u8 = 0 as *u8;
  let pref_std: *u8 = 0 as *u8;
  let pref_core: *u8 = 0 as *u8;
  if (n_deps <= 0) {
    return 0;
  }
  unsafe {
    pref_std = "std." as *u8;
    pref_core = "core." as *u8;
  }
  k = 0;
  while (k < n_deps) {
    p = dep_paths[k];
    if (p == 0 as *u8) {
      return 0;
    }
    if (p[0] == 0) {
      return 0;
    }
    if (rt_cmp_starts_with_n(p, pref_std, 4 as usize) != 0) {
      k = k + 1;
      continue;
    }
    if (rt_cmp_starts_with_n(p, pref_core, 5 as usize) != 0) {
      k = k + 1;
      continue;
    }
    return 0;
  }
  return 1;
}

/** Exported function `driver_x_emit_asm_dep_parse_only_ok`.
 * Implements `driver_x_emit_asm_dep_parse_only_ok`.
 * @param input_path *u8
 * @param dep_path *u8
 * @return i32
 */
#[no_mangle]
export function driver_x_emit_asm_dep_parse_only_ok(input_path: *u8, dep_path: *u8): i32 {
  let n_asm: *u8 = 0 as *u8;
  let n_asm2: *u8 = 0 as *u8;
  let d_ast: *u8 = 0 as *u8;
  let d_cg: *u8 = 0 as *u8;
  let d_be: *u8 = 0 as *u8;
  let d_ph: *u8 = 0 as *u8;
  let p_asm: *u8 = 0 as *u8;
  let p_arch: *u8 = 0 as *u8;
  let p_plat: *u8 = 0 as *u8;
  if (input_path == 0 as *u8) {
    return 0;
  }
  if (dep_path == 0 as *u8) {
    return 0;
  }
  unsafe {
    n_asm = "src/asm/asm.x" as *u8;
    n_asm2 = "/asm/asm.x" as *u8;
    d_ast = "ast" as *u8;
    d_cg = "codegen" as *u8;
    d_be = "backend" as *u8;
    d_ph = "peephole" as *u8;
    p_asm = "asm." as *u8;
    p_arch = "arch." as *u8;
    p_plat = "platform." as *u8;
  }
  if (rt_cmp_contains(input_path, n_asm) == 0) {
    if (rt_cmp_contains(input_path, n_asm2) == 0) {
      return 0;
    }
  }
  if (rt_cmp_eq(dep_path, d_ast) != 0) {
    return 1;
  }
  if (rt_cmp_eq(dep_path, d_cg) != 0) {
    return 1;
  }
  if (rt_cmp_eq(dep_path, d_be) != 0) {
    return 1;
  }
  if (rt_cmp_eq(dep_path, d_ph) != 0) {
    return 1;
  }
  if (rt_cmp_starts_with_n(dep_path, p_asm, 4 as usize) != 0) {
    return 1;
  }
  if (rt_cmp_starts_with_n(dep_path, p_arch, 5 as usize) != 0) {
    return 1;
  }
  if (rt_cmp_starts_with_n(dep_path, p_plat, 9 as usize) != 0) {
    return 1;
  }
  return 0;
}

/** Exported function `driver_x_emit_asm_direct_import_only`.
 * Implements `driver_x_emit_asm_direct_import_only`.
 * @param input_path *u8
 * @return i32
 */
#[no_mangle]
export function driver_x_emit_asm_direct_import_only(input_path: *u8): i32 {
  let a1: *u8 = 0 as *u8;
  let a2: *u8 = 0 as *u8;
  let s1: *u8 = 0 as *u8;
  let s2: *u8 = 0 as *u8;
  if (input_path == 0 as *u8) {
    return 0;
  }
  unsafe {
    a1 = "src/asm/asm.x" as *u8;
    a2 = "/asm/asm.x" as *u8;
    s1 = "src/asm/asm_seed_full.x" as *u8;
    s2 = "/asm/asm_seed_full.x" as *u8;
  }
  if (rt_cmp_contains(input_path, a1) != 0) {
    return 1;
  }
  if (rt_cmp_contains(input_path, a2) != 0) {
    return 1;
  }
  if (rt_cmp_contains(input_path, s1) != 0) {
    return 1;
  }
  if (rt_cmp_contains(input_path, s2) != 0) {
    return 1;
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
  let be: *u8 = 0 as *u8;
  if (driver_x_emit_asm_direct_import_only(input_path) == 0) {
    return 0;
  }
  if (dep_path == 0 as *u8) {
    return 0;
  }
  unsafe {
    be = "backend" as *u8;
  }
  if (rt_cmp_eq(dep_path, be) != 0) {
    return 1;
  }
  return 0;
}

/** Exported function `driver_compile_argv_copy_path_c`.
 * Implements `driver_compile_argv_copy_path_c`.
 * @param state *RtCompileState
 * @param arg_buf *u8
 * @param plen i32
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_copy_path_c(state: *RtCompileState, arg_buf: *u8, plen: i32): void {
  let k: i32 = 0;
  let n: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (arg_buf == 0 as *u8) {
    return;
  }
  if (plen <= 0) {
    return;
  }
  n = plen;
  if (n > 511) {
    n = 511;
  }
  k = 0;
  while (k < n) {
    state.path_buf[k] = arg_buf[k];
    k = k + 1;
  }
  state.path_len = n;
}

/** Exported function `driver_compile_argv_set_use_freestanding_c`.
 * Memory management helper `driver_compile_argv_set_use_freestanding_c`.
 * @param state *RtCompileState
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_use_freestanding_c(state: *RtCompileState): void {
  if (state == 0 as *RtCompileState) {
    return;
  }
  state.use_freestanding = 1;
  unsafe {
    driver_freestanding_set(1);
    cfg_set_freestanding(1);
  }
}

/** Exported function `driver_compile_argv_set_legacy_f32_abi_c`.
 * Implements `driver_compile_argv_set_legacy_f32_abi_c`.
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_legacy_f32_abi_c(): void {
  let name: *u8 = 0 as *u8;
  let val: *u8 = 0 as *u8;
  unsafe {
    name = "XLANG_ABI_F32_XMM" as *u8;
    val = "0" as *u8;
    setenv(name, val, 1);
  }
}

/** Exported function `driver_compile_argv_set_sanitize_address_c`.
 * Implements `driver_compile_argv_set_sanitize_address_c`.
 * @return void
 */
#[no_mangle]
export function driver_compile_argv_set_sanitize_address_c(): void {
  unsafe {
    driver_sanitize_address_set(1);
  }
}

/** Return 1 if buf[0..length) is "-h" or "--help" (byte compares, no string lit).
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_help_token_is).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_help_token_is(buf: *u8, len: i32): i32 {
  if (buf == 0 as *u8) {
    return 0;
  }
  if (len == 2) {
    if (buf[0] == 45) {
      if (buf[1] == 104) {
        return 1;
      }
    }
  }
  if (len == 6) {
    if (buf[0] == 45) {
      if (buf[1] == 45) {
        if (buf[2] == 104) {
          if (buf[3] == 101) {
            if (buf[4] == 108) {
              if (buf[5] == 112) {
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

/** Tail-recurse argv[i..] for -h/--help. buf is caller scratch (min 16 bytes).
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_is_help_at).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_is_help_at(argc: i32, argv: **u8, i: i32, buf: *u8): i32 {
  let len: i32 = 0;
  if (i >= argc) {
    return 0;
  }
  if (buf == 0 as *u8) {
    return 0;
  }
  unsafe {
    len = driver_get_argv_i(argc, argv, i, buf, 16);
  }
  if (rt_help_token_is(buf, len) != 0) {
    return 1;
  }
  return rt_is_help_at(argc, argv, i + 1, buf);
}

/** Scan argv for -h / --help (malloc small buf; no local u8[N]).
 * Track-L: #[no_mangle] keeps public short name.
 * PLATFORM: SHARED — link-name contract. */
#[no_mangle]
export function driver_compile_argv_is_help_c(argc: i32, argv: **u8): i32 {
  let buf: *u8 = 0 as *u8;
  let hit: i32 = 0;
  if (argc < 2) {
    return 0;
  }
  unsafe {
    buf = malloc(16 as usize);
  }
  if (buf == 0 as *u8) {
    return 0;
  }
  hit = rt_is_help_at(argc, argv, 1, buf);
  unsafe {
    free(buf);
  }
  return hit;
}

/** Exported function `driver_compile_append_lib_root_c`.
 * Implements `driver_compile_append_lib_root_c`.
 * @param state *RtCompileState
 * @param path *u8
 * @param len i32
 * @return void
 */
#[no_mangle]
export function driver_compile_append_lib_root_c(state: *RtCompileState, path: *u8, len: i32): void {
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (path == 0 as *u8) {
    return;
  }
  if (len <= 0) {
    return;
  }
  unsafe {
    driver_emit_append_lib_root(state as *u8, path, len);
  }
}

/** Exported function `driver_compile_ensure_default_lib_c`.
 * Implements `driver_compile_ensure_default_lib_c`.
 * @param key *u8
 * @return void
 */
#[no_mangle]
export function driver_compile_ensure_default_lib_c(key: *u8): void {
  let ch: u8 = 46;
  if (key == 0 as *u8) {
    return;
  }
  unsafe {
    if (driver_emit_lib_root_count(key) == 0) {
      driver_emit_append_lib_root(key, &ch, 1);
    }
  }
}

/** Exported function `driver_compile_parse_argv_init_c`.
 * Implements `driver_compile_parse_argv_init_c`.
 * @param state *RtCompileState
 * @return void
 */
#[no_mangle]
export function driver_compile_parse_argv_init_c(state: *RtCompileState): void {
  if (state == 0 as *RtCompileState) {
    return;
  }
  unsafe {
    cfg_reset_compile_target();
  }
  state.path_len = 0;
  state.out_path_len = 0;
  state.use_asm_backend = 1;
  state.target_arch = 0;
  state.target_len = 0;
  state.opt_level_len = 1;
  state.opt_level_buf[0] = 50;
  state.use_lto = 0;
  state.backend_asm_explicit = 0;
  state.use_freestanding = 0;
  state.parse_saw_target = 0;
  state.target_cpu_len = 0;
  state.target_cpu_features = 0;
  state.print_target_cpu = 0;
  state.parse_saw_target_cpu = 0;
  unsafe {
    driver_freestanding_set(0);
    cfg_set_freestanding(0);
    driver_emit_lib_root_reset(state as *u8);
  }
}

/**
 * Function `driver_compile_argv_next_is_value_c`.
 * Purpose: dangling-value guard shared by every value-taking driver-flag parse
 * branch — returns 1 iff argv[i+1] exists, is non-empty, and does not start
 * with '-' (45).
 * Contracts: documented flag values (-o/-O/-L/-backend/-target/-target-cpu:
 * paths, levels, dirs, triples, cpu names) are never flag-shaped, so a
 * missing or flag-shaped next entry means the value flag is dangling — the
 * caller must skip it standalone and NOT advance past the next argv slot.
 * Why the guard matters: driver_argv_ensure_run_o appends the injected
 * "-o <temp>" pair at the argv tail, so an unconditional i+2 advance eats it
 * and the product never links (execv ENOENT; reproducer
 * tests/probes/wave943/m6.x). Parse-layer twin of the
 * xlang_driver_exec_spawn_wait consume guard. Fetching argv[i+1] into
 * arg_buf clobbers the current token — call only after the current flag
 * matched. Single authority: main.x / src/driver/compile.x extern this
 * (per-TU *u8 argv typing, ABI-identical pointer); C twins mirror it in the
 * same commit. PLATFORM: SHARED.
 * @param argc i32 — argv length
 * @param argv **u8 — driver argv
 * @param i i32 — index of the value-taking flag
 * @param arg_buf *u8 — scratch buffer for the peeked next entry
 * @param arg_cap i32 — scratch buffer capacity
 * @return i32 — 1 iff argv[i+1] is a consumable value; 0 otherwise
 */
#[no_mangle]
export function driver_compile_argv_next_is_value_c(argc: i32, argv: **u8, i: i32, arg_buf: *u8, arg_cap: i32): i32 {
  let nlen: i32 = 0;
  if (arg_buf == 0 as *u8) {
    return 0;
  }
  if (arg_cap <= 0) {
    return 0;
  }
  unsafe {
    nlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
  }
  if (nlen >= 1) {
    unsafe {
      if (arg_buf[0] != 45) {
        return 1;
      }
    }
  }
  return 0;
}

/** Function `driver_compile_argv_apply_minus_o_next_c`.
 * Purpose: implements `driver_compile_argv_apply_minus_o_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_o_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32): void {
  let olen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    olen = driver_get_argv_i(argc, argv, i + 1, &state.out_path_buf[0], 512);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a path — leave state untouched. */
  if (olen >= 1) {
    unsafe {
      if (state.out_path_buf[0] == 45) {
        return;
      }
    }
  }
  if (olen >= 0) {
    state.out_path_len = olen;
  }
}

/** Function `driver_compile_argv_apply_minus_L_next_c`.
 * Purpose: implements `driver_compile_argv_apply_minus_L_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_L_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32, arg_buf: *u8, arg_cap: i32): void {
  let llen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (arg_buf == 0 as *u8) {
    return;
  }
  if (arg_cap <= 0) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    llen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a lib dir — leave state untouched. */
  if (llen >= 1) {
    unsafe {
      if (arg_buf[0] == 45) {
        return;
      }
    }
  }
  if (llen >= 0) {
    driver_compile_append_lib_root_c(state, arg_buf, llen);
  }
}

/** Function `driver_compile_argv_apply_minus_O_next_c`.
 * Purpose: implements `driver_compile_argv_apply_minus_O_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_minus_O_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32): void {
  let olen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    olen = driver_get_argv_i(argc, argv, i + 1, &state.opt_level_buf[0], 8);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not an opt level — leave state untouched. */
  if (olen >= 1) {
    unsafe {
      if (state.opt_level_buf[0] == 45) {
        return;
      }
    }
  }
  if (olen >= 0) {
    state.opt_level_len = olen;
  }
}

/** Function `driver_compile_argv_apply_backend_next_c`.
 * Purpose: implements `driver_compile_argv_apply_backend_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_backend_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32, arg_buf: *u8, arg_cap: i32): void {
  let vlen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (arg_buf == 0 as *u8) {
    return;
  }
  if (arg_cap <= 0) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    vlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not "asm"/"c" — leave state untouched. */
  if (vlen >= 1) {
    unsafe {
      if (arg_buf[0] == 45) {
        return;
      }
    }
  }
  if (vlen >= 0) {
    unsafe {
      if (drv_eq_asm_word(arg_buf, vlen) != 0) {
        state.use_asm_backend = 1;
        state.backend_asm_explicit = 1;
      }
      if (drv_eq_c_word(arg_buf, vlen) != 0) {
        state.use_asm_backend = 0;
        state.backend_asm_explicit = 0;
      }
    }
  }
}

/** Function `driver_compile_argv_apply_target_next_c`.
 * Purpose: implements `driver_compile_argv_apply_target_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_target_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32): void {
  let tlen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    tlen = driver_get_argv_i(argc, argv, i + 1, &state.target_buf[0], 512);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a triple — leave state untouched. */
  if (tlen >= 1) {
    unsafe {
      if (state.target_buf[0] == 45) {
        return;
      }
    }
  }
  state.parse_saw_target = 1;
  if (tlen >= 0) {
    state.target_len = tlen;
    unsafe {
      if (drv_target_has_arm(&state.target_buf[0], tlen) != 0) {
        state.target_arch = 1;
      }
    }
  }
}

/** Function `driver_compile_argv_apply_target_cpu_next_c`.
 * Purpose: implements `driver_compile_argv_apply_target_cpu_next_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_argv_apply_target_cpu_next_c(
  state: *RtCompileState, argc: i32, argv: **u8, i: i32): void {
  let tlen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (i + 1 >= argc) {
    return;
  }
  unsafe {
    tlen = driver_get_argv_i(argc, argv, i + 1, &state.target_cpu_buf[0], 64);
  }
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a cpu name — leave state untouched. */
  if (tlen >= 1) {
    unsafe {
      if (state.target_cpu_buf[0] == 45) {
        return;
      }
    }
  }
  state.parse_saw_target_cpu = 1;
  if (tlen >= 0) {
    state.target_cpu_len = tlen;
  }
}

/** Function `driver_compile_parse_argv_step_c`.
 * Purpose: implements `driver_compile_parse_argv_step_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function driver_compile_parse_argv_step_c(
  argc: i32, argv: **u8, state: *RtCompileState, i: i32, arg_buf: *u8, arg_cap: i32): i32 {
  let len: i32 = 0;
  let olen: i32 = 0;
  let llen: i32 = 0;
  let vlen: i32 = 0;
  let tlen: i32 = 0;
  if (state == 0 as *RtCompileState) {
    return i + 1;
  }
  if (arg_buf == 0 as *u8) {
    return i + 1;
  }
  if (arg_cap <= 0) {
    return i + 1;
  }
  unsafe {
    len = driver_get_argv_i(argc, argv, i, arg_buf, arg_cap);
  }
  if (len < 0) {
    return i + 1;
  }
  unsafe {
    if (drv_eq_minus_o(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-o" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        olen = driver_get_argv_i(argc, argv, i + 1, &state.out_path_buf[0], 512);
        if (olen >= 0) {
          state.out_path_len = olen;
        }
        return i + 2;
      }
    }
    if (drv_eq_minus_L(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-L" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        llen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
        if (llen >= 0) {
          driver_compile_append_lib_root_c(state, arg_buf, llen);
        }
        return i + 2;
      }
    }
    if (drv_eq_minus_O(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-O" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        olen = driver_get_argv_i(argc, argv, i + 1, &state.opt_level_buf[0], 8);
        if (olen >= 0) {
          state.opt_level_len = olen;
        }
        return i + 2;
      }
    }
    if (drv_eq_flto(arg_buf, len) != 0) {
      state.use_lto = 1;
      return i + 1;
    }
    if (drv_eq_minus_freestanding(arg_buf, len) != 0) {
      driver_compile_argv_set_use_freestanding_c(state);
      return i + 1;
    }
    if (drv_eq_legacy_f32_abi(arg_buf, len) != 0) {
      driver_compile_argv_set_legacy_f32_abi_c();
      return i + 1;
    }
    if (drv_eq_fsanitize_address(arg_buf, len) != 0) {
      driver_sanitize_address_set(1);
      return i + 1;
    }
    if (drv_eq_minus_backend(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-backend" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        vlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
        if (vlen >= 0) {
          if (drv_eq_asm_word(arg_buf, vlen) != 0) {
            state.use_asm_backend = 1;
            state.backend_asm_explicit = 1;
          }
          if (drv_eq_c_word(arg_buf, vlen) != 0) {
            state.use_asm_backend = 0;
            state.backend_asm_explicit = 0;
          }
        }
        return i + 2;
      }
    }
    if (drv_eq_minus_target(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-target" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        state.parse_saw_target = 1;
        tlen = driver_get_argv_i(argc, argv, i + 1, &state.target_buf[0], 512);
        if (tlen >= 0) {
          state.target_len = tlen;
          if (drv_target_has_arm(&state.target_buf[0], tlen) != 0) {
            state.target_arch = 1;
          }
        }
        return i + 2;
      }
    }
    if (drv_eq_minus_target_cpu(arg_buf, len) != 0) {
      if (i + 1 < argc) {
        /* Dangling guard: flag-shaped/missing next → skip "-target-cpu" standalone. */
        if (driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) == 0) {
          return i + 1;
        }
        state.parse_saw_target_cpu = 1;
        tlen = driver_get_argv_i(argc, argv, i + 1, &state.target_cpu_buf[0], 64);
        if (tlen >= 0) {
          state.target_cpu_len = tlen;
        }
        return i + 2;
      }
    }
    if (drv_eq_print_target_cpu(arg_buf, len) != 0) {
      state.print_target_cpu = 1;
      return i + 1;
    }
    if (arg_buf[0] != 45) {
      if (drv_path_ends_x(arg_buf, len) != 0) {
        driver_compile_argv_copy_path_c(state, arg_buf, len);
      }
    }
  }
  return i + 1;
}

/** Tail-recurse argv[i..] via parse_argv_step; arg_buf is caller 512 scratch.
 * Track-L: #[no_mangle] keeps surface short name (not rt_compile_rt_parse_argv_scan_at).
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function rt_parse_argv_scan_at(
  argc: i32, argv: **u8, state: *RtCompileState, i: i32, arg_buf: *u8): void {
  let ni: i32 = 0;
  if (i >= argc) {
    return;
  }
  if (state == 0 as *RtCompileState) {
    return;
  }
  if (arg_buf == 0 as *u8) {
    return;
  }
  ni = driver_compile_parse_argv_step_c(argc, argv, state, i, arg_buf, 512);
  rt_parse_argv_scan_at(argc, argv, state, ni, arg_buf);
}

/** Scan argv (malloc 512 buffer; no local u8[N] / while+argv).
 * Track-L: #[no_mangle] keeps public short name.
 * PLATFORM: SHARED — link-name contract. */
#[no_mangle]
export function driver_compile_parse_argv_scan_c(argc: i32, argv: **u8, state: *RtCompileState): void {
  let arg_buf: *u8 = 0 as *u8;
  if (argc < 2) {
    return;
  }
  if (state == 0 as *RtCompileState) {
    return;
  }
  unsafe {
    arg_buf = malloc(512 as usize);
  }
  if (arg_buf == 0 as *u8) {
    return;
  }
  rt_parse_argv_scan_at(argc, argv, state, 1, arg_buf);
  unsafe {
    free(arg_buf);
  }
}

/** Exported function `driver_compile_resolve_target_cpu_c`.
 * Implements `driver_compile_resolve_target_cpu_c`.
 * @param state *RtCompileState
 * @return void
 */
#[no_mangle]
export function driver_compile_resolve_target_cpu_c(state: *RtCompileState): void {
  let spec: *u8 = 0 as *u8;
  let spec_len: usize = 0 as usize;
  let feats: u32 = 0;
  let rc: i32 = 0;
  let kind: *u8 = 0 as *u8;
  let msg: *u8 = 0 as *u8;
  if (state == 0 as *RtCompileState) {
    return;
  }
  unsafe {
    spec = "native" as *u8;
  }
  spec_len = 6 as usize;
  if (state.target_cpu_len > 0) {
    spec = &state.target_cpu_buf[0];
    spec_len = state.target_cpu_len as usize;
  }
  unsafe {
    rc = xlang_target_cpu_resolve(spec, spec_len, &feats);
  }
  if (rc != 0) {
    unsafe {
      kind = "note" as *u8;
      msg = "unknown -target-cpu; using generic baseline" as *u8;
      diag_report_with_code(0 as *u8, 0, 0, kind, 0 as *u8, msg, 0 as *u8);
      feats = xlang_target_cpu_generic_for_host();
    }
  }
  state.target_cpu_features = feats as i32;
}

/** Exported function `cfg_sync_compile_target_from_state_c`.
 * Implements `cfg_sync_compile_target_from_state_c`.
 * @param state *u8
 * @return void
 */
#[no_mangle]
export function cfg_sync_compile_target_from_state_c(state: *u8): void {
  let st: *RtCompileState = 0 as *RtCompileState;
  if (state == 0 as *u8) {
    unsafe {
      cfg_reset_compile_target();
    }
    return;
  }
  st = state as *RtCompileState;
  if (st.parse_saw_target != 0) {
    if (st.target_len > 0) {
      unsafe {
        cfg_apply_compile_target_from_triple(&st.target_buf[0], st.target_len);
      }
      return;
    }
  }
  unsafe {
    cfg_reset_compile_target();
  }
}

/** Exported function `driver_compile_parse_argv_impl_c`.
 * Implements `driver_compile_parse_argv_impl_c`.
 * @param argc i32
 * @param argv **u8
 * @param state *RtCompileState
 * @return i32
 */
#[no_mangle]
export function driver_compile_parse_argv_impl_c(argc: i32, argv: **u8, state: *RtCompileState): i32 {
  if (argc < 2) {
    return 1;
  }
  if (state == 0 as *RtCompileState) {
    return 1;
  }
  driver_compile_parse_argv_init_c(state);
  driver_compile_parse_argv_scan_c(argc, argv, state);
  driver_compile_resolve_target_cpu_c(state);
  if (state.print_target_cpu != 0) {
    return 0;
  }
  if (state.path_len <= 0) {
    return 1;
  }
  unsafe {
    state.target_arch = driver_resolve_target_arch(state.target_arch, state.parse_saw_target);
  }
  cfg_sync_compile_target_from_state_c(state as *u8);
  driver_compile_ensure_default_lib_c(state as *u8);
  return 0;
}

/** Exported function `driver_compile_state_alloc_c`.
 * Memory management helper `driver_compile_state_alloc_c`.
 * @return *RtCompileState
 */
#[no_mangle]
export function driver_compile_state_alloc_c(): *RtCompileState {
  let state: *RtCompileState = 0 as *RtCompileState;
  let p: *u8 = 0 as *u8;
  /* RtCompileState 总大小=1728B（.x 无 sizeof，须与 seeds DriverCompileStateSU sizeof 对齐）。
   * 旧值 1664 是 target_cpu_buf[64] 时代残留；buf 扩到 128 后 target_cpu_len 落在
   * offset 1712 > 1664 → malloc/memset 越界，读堆残留致 check 段错误。wave1241 修正。 */
  let sz: usize = 1728 as usize;
  unsafe {
    p = malloc(sz);
  }
  if (p == 0 as *u8) {
    return 0 as *RtCompileState;
  }
  unsafe {
    memset(p, 0, sz);
  }
  state = p as *RtCompileState;
  state.use_asm_backend = 1;
  state.opt_level_buf[0] = 50;
  state.opt_level_len = 1;
  return state;
}

/** Release driver_emit lib_root sidecar keyed by compile state pointer.
 * Must run before free(state) so directory `xlang check` does not exhaust the
 * 32/64 emit sidecar table (wave1243 IMP001 after ~32 files). PLATFORM: SHARED. */
export extern function driver_emit_lib_root_release(state: *u8): void;

/** Exported function `driver_compile_state_free_c`.
 * Memory management helper `driver_compile_state_free_c`.
 * Releases emit lib_root sidecar (wave1243) then frees the state heap block.
 * @param state *RtCompileState
 * @return void
 */
#[no_mangle]
export function driver_compile_state_free_c(state: *RtCompileState): void {
  if (state == 0 as *RtCompileState) {
    return;
  }
  unsafe {
    /* wave1243: free emit sidecar before heap free — key is the state pointer. */
    driver_emit_lib_root_release(state as *u8);
    free(state as *u8);
  }
}
