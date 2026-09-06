// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// See implementation.
// See implementation.
//
// See implementation.
// See implementation.

const ast = import("ast");

/** See implementation for details. */
export struct DriverCompileState {
  path_buf: u8[512];
  path_len: i32;
  out_path_buf: u8[512];
  out_path_len: i32;
  use_asm_backend: i32;
  target_arch: i32;
  /* See implementation. */
  target_buf: u8[512];
  target_len: i32;
  opt_level_buf: u8[8];
  opt_level_len: i32;
  use_lto: i32;
  /* See implementation. */
  backend_asm_explicit: i32;
  /* See implementation. */
  use_freestanding: i32;
  /* See implementation. */
  parse_saw_target: i32;
  /* See implementation. */
  target_cpu_buf: u8[128];
  target_cpu_len: i32;
  /* See implementation. */
  target_cpu_features: i32;
  /* See implementation. */
  print_target_cpu: i32;
  /* See implementation. */
  parse_saw_target_cpu: i32;
}

export extern function driver_get_argv_i(argc: i32, argv: *u8, i: i32, buf: *u8, max: i32): i32;
/* See implementation. */
export extern function driver_compile_argv_copy_path_c(state: *DriverCompileState, arg_buf: *u8, plen: i32): void;
/* See implementation. */
export extern function driver_compile_ensure_default_lib_c(key: *u8): void;
/* See implementation. */
export extern function driver_compile_parse_argv_init_c(state: *DriverCompileState): void;
/* See implementation. */
export extern function driver_compile_append_lib_root_c(state: *DriverCompileState, path: *u8, len: i32): void;
/* See implementation. */
export extern function driver_compile_argv_apply_minus_o_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32): void;
export extern function driver_compile_argv_apply_minus_L_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void;
export extern function driver_compile_argv_apply_minus_O_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32): void;
export extern function driver_compile_argv_set_use_lto_c(state: *DriverCompileState): void;
/* See implementation. */
export extern function driver_compile_argv_set_use_freestanding_c(state: *DriverCompileState): void;
/* See implementation. */
export extern function driver_compile_argv_set_legacy_f32_abi_c(): void;
/* See implementation. */
export extern function driver_compile_argv_set_sanitize_address_c(): void;
export extern function driver_compile_argv_apply_backend_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32, arg_buf: *u8, arg_cap: i32): void;
export extern function driver_compile_argv_apply_target_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32): void;
/* See implementation. */
export extern function driver_compile_argv_apply_target_cpu_next_c(state: *DriverCompileState, argc: i32, argv: *u8, i: i32): void;
/* See implementation. */
export extern function driver_compile_argv_set_print_target_cpu_c(state: *DriverCompileState): void;
/* See implementation. */
export extern function driver_print_target_cpu_features_c(features: i32): i32;
/* See implementation. */
export extern function driver_compile_resolve_target_cpu_c(state: *DriverCompileState): void;
/* See implementation. */
export extern function driver_compile_parse_argv_impl_c(argc: i32, argv: *u8, state: *DriverCompileState): i32;

/* See implementation. */
export extern function driver_compile_parse_argv_scan_c(argc: i32, argv: *u8, state: *DriverCompileState): void;

/* See implementation. */
export extern function cfg_sync_compile_target_from_state_c(state: *DriverCompileState): void;
export extern function driver_emit_lib_root_reset(key: *u8): void;
export extern function driver_emit_append_lib_root(key: *u8, path: *u8, len: i32): i32;
export extern function driver_emit_lib_root_count(key: *u8): i32;
export extern function driver_resolve_target_arch(parsed: i32, saw_target: i32): i32;
export extern function driver_source_has_generic_syntax(path: *u8, path_len: i32): i32;
/* See implementation. */
export extern function driver_source_has_compound_assign_syntax(path: *u8, path_len: i32): i32;
/** See implementation for details. */
export extern function driver_source_has_top_level_import_path(path: *u8, path_len: i32): i32;
export extern function driver_asm_output_want_exe(out_path: *u8): i32;
export extern function driver_check_only_get(): i32;
export extern function driver_bump_stack_limit(): void;
/* See implementation. */
export extern function driver_asm_entry_module_only_from_env(): i32;

/* See implementation. */
export extern function driver_compile_argv_is_help_c(argc: i32, argv: *u8): i32;
/* See implementation. */
export extern function driver_print_usage_c(): void;

/* See implementation. */
export extern function driver_run_compiler_full_x_impl_c(argc: i32, argv: *u8): i32;

/* See implementation. */
export extern function driver_run_compiler_full_x_post_parse_impl_c(state: *DriverCompileState, argc: i32, argv: *u8): i32;

/* See implementation. */
export extern function driver_compile_state_alloc_c(): *DriverCompileState;

/* See implementation. */
export extern function driver_compile_state_free_c(state: *DriverCompileState): void;

/* See implementation. */
export extern function driver_run_asm_backend_impl_c(
input_path: *u8,
out_path: *u8,
lib_key: *u8,
target: *u8,
argc: i32,
argv: *u8
): i32;

/* See implementation. */
export extern function driver_run_emit_c_path_impl_c(
input_path: *u8,
out_path: *u8,
lib_key: *u8,
target: *u8,
opt_level: *u8,
use_lto: i32,
argc: i32,
argv: *u8
): i32;

/**
 * See implementation.
 */
export function compile_dispatch_asm_backend(
input_path: *u8,
out_path: *u8,
lib_key: *u8,
target: *u8,
argc: i32,
argv: *u8
): i32 {
  if (input_path == 0 as *u8) {
    return 1;
  }
  // See implementation.
  unsafe {
    return driver_run_asm_backend_impl_c(input_path, out_path, lib_key, target, argc, argv);
  }
}

/**
 * See implementation.
 */
export function compile_dispatch_emit_c_path(
input_path: *u8,
out_path: *u8,
lib_key: *u8,
target: *u8,
opt_level: *u8,
use_lto: i32,
argc: i32,
argv: *u8
): i32 {
  if (input_path == 0 as *u8) {
    return 1;
  }
  // See implementation.
  unsafe {
    return driver_run_emit_c_path_impl_c(input_path, out_path, lib_key, target, opt_level, use_lto, argc, argv);
  }
}

/** Exported function `driver_compile_state_key`.
 * Implements `driver_compile_state_key`.
 * @param state *DriverCompileState
 * @return *u8
 */
export function driver_compile_state_key(state: *DriverCompileState): *u8 {
  return state as *u8;
}

/** Exported function `driver_compile_ensure_default_lib`.
 * Implements `driver_compile_ensure_default_lib`.
 * @param key *u8
 * @return void
 */
export function driver_compile_ensure_default_lib(key: *u8): void {
  // See implementation.
  unsafe {
    driver_compile_ensure_default_lib_c(key);
  }
}

/** Exported function `eq_minus_o`.
 * Implements `eq_minus_o`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_o(buf: *u8, len: i32): i32 {
  if (len == 2 && buf[0] == 45 && buf[1] == 111) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_L`.
 * Implements `eq_minus_L`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_L(buf: *u8, len: i32): i32 {
  if (len == 2 && buf[0] == 45 && buf[1] == 76) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_backend`.
 * Implements `eq_minus_backend`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_backend(buf: *u8, len: i32): i32 {
  if (len == 8 && buf[0] == 45 && buf[1] == 98 && buf[2] == 97 && buf[3] == 99 && buf[4] == 107 &&
  buf[5] == 101 && buf[6] == 110 && buf[7] == 100) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_target`.
 * Implements `eq_minus_target`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_target(buf: *u8, len: i32): i32 {
  if (len != 7) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 116 && buf[2] == 97 && buf[3] == 114 && buf[4] == 103 && buf[5] ==
  101 && buf[6] == 116) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_target_cpu`.
 * Implements `eq_minus_target_cpu`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_target_cpu(buf: *u8, len: i32): i32 {
  if (len == 11 && buf[0] == 45 && buf[1] == 116 && buf[2] == 97 && buf[3] == 114 && buf[4] == 103 &&
  buf[5] == 101 && buf[6] == 116 && buf[7] == 45 && buf[8] == 99 && buf[9] == 112 && buf[10] == 117) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_print_target_cpu`.
 * Implements `eq_print_target_cpu`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_print_target_cpu(buf: *u8, len: i32): i32 {
  if (len == 18 && buf[0] == 45 && buf[1] == 45 && buf[2] == 112 && buf[3] == 114 && buf[4] == 105 &&
  buf[5] == 110 && buf[6] == 116 && buf[7] == 45 && buf[8] == 116 && buf[9] == 97 && buf[10] == 114 &&
  buf[11] == 103 && buf[12] == 101 && buf[13] == 116 && buf[14] == 45 && buf[15] == 99 && buf[16] == 112 &&
  buf[17] == 117) {
    return 1;
  }
  if (len == 17 && buf[0] == 45 && buf[1] == 112 && buf[2] == 114 && buf[3] == 105 && buf[4] == 110 &&
  buf[5] == 116 && buf[6] == 45 && buf[7] == 116 && buf[8] == 97 && buf[9] == 114 && buf[10] == 103 &&
  buf[11] == 101 && buf[12] == 116 && buf[13] == 45 && buf[14] == 99 && buf[15] == 112 && buf[16] == 117) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_O`.
 * Implements `eq_minus_O`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_O(buf: *u8, len: i32): i32 {
  if (len == 2 && buf[0] == 45 && buf[1] == 79) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_flto`.
 * Implements `eq_flto`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_flto(buf: *u8, len: i32): i32 {
  if (len == 5 && buf[0] == 45 && buf[1] == 102 && buf[2] == 108 && buf[3] == 116 && buf[4] == 111)
  {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_freestanding`.
 * Memory management helper `eq_minus_freestanding`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_freestanding(buf: *u8, len: i32): i32 {
  if (len == 13 && buf[0] == 45 && buf[1] == 102 && buf[2] == 114 && buf[3] == 101 && buf[4] == 101 &&
  buf[5] == 115 && buf[6] == 116 && buf[7] == 97 && buf[8] == 110 && buf[9] == 100 && buf[10] == 105 &&
  buf[11] == 110 && buf[12] == 103) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_legacy_f32_abi`.
 * Implements `eq_legacy_f32_abi`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_legacy_f32_abi(buf: *u8, len: i32): i32 {
  if (len == 15 && buf[0] == 45 && buf[1] == 108 && buf[2] == 101 && buf[3] == 103 && buf[4] == 97 &&
  buf[5] == 99 && buf[6] == 121 && buf[7] == 45 && buf[8] == 102 && buf[9] == 51 && buf[10] == 50 &&
  buf[11] == 45 && buf[12] == 97 && buf[13] == 98 && buf[14] == 105) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_fsanitize_address`.
 * Implements `eq_fsanitize_address`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_fsanitize_address(buf: *u8, len: i32): i32 {
  if (len == 18 && buf[0] == 45 && buf[1] == 102 && buf[2] == 115 && buf[3] == 97 && buf[4] == 110 &&
  buf[5] == 105 && buf[6] == 116 && buf[7] == 105 && buf[8] == 122 && buf[9] == 101 && buf[10] == 61 &&
  buf[11] == 97 && buf[12] == 100 && buf[13] == 100 && buf[14] == 114 && buf[15] == 101 && buf[16] == 115 &&
  buf[17] == 115) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_asm_word`.
 * Implements `eq_asm_word`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_asm_word(buf: *u8, len: i32): i32 {
  if (len == 3 && buf[0] == 97 && buf[1] == 115 && buf[2] == 109) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_c_word`.
 * Implements `eq_c_word`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_c_word(buf: *u8, len: i32): i32 {
  if (len == 1 && buf[0] == 99) {
    return 1;
  }
  return 0;
}

/** Exported function `path_ends_x`.
 * Implements `path_ends_x`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function path_ends_x(buf: *u8, len: i32): i32 {
  if (len >= 2 && buf[len - 2] == 46 && buf[len - 1] == 120) {
    return 1;
  }
  if (len >= 3 && buf[len - 3] == 46 && buf[len - 2] == 115 && buf[len - 1] == 117) {
    return 1;
  }
  return 0;
}

/** Exported function `target_has_arm`.
 * Implements `target_has_arm`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function target_has_arm(buf: *u8, len: i32): i32 {
  let start: i32 = 0;
  while (start + 5 <= len) {
    if (buf[start] == 97 && buf[start + 1] == 114 && buf[start + 2] == 109 && buf[start + 3] == 54
    &&
    buf[start + 4] == 52) {
      return 1;
    }
    start = start + 1;
  }
  return 0;
}

/**
 * See implementation.
 */
export function driver_compile_parse_argv_init(state: *DriverCompileState): void {
  // See implementation.
  unsafe {
    driver_compile_parse_argv_init_c(state);
  }
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 */
export function driver_compile_parse_argv_step(
  argc: i32,
  argv: *u8,
  state: *DriverCompileState,
  i: i32,
  arg_buf: *u8,
  arg_cap: i32
): i32 {
  unsafe {
    let len: i32 = driver_get_argv_i(argc, argv, i, arg_buf, arg_cap);
    if (len < 0) {
      return i + 1;
    }
    if (eq_minus_o(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_minus_o_next_c(state, argc, argv, i);
      return i + 2;
    }
    if (eq_minus_L(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_minus_L_next_c(state, argc, argv, i, arg_buf, arg_cap);
      return i + 2;
    }
    if (eq_minus_O(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_minus_O_next_c(state, argc, argv, i);
      return i + 2;
    }
    if (eq_flto(arg_buf, len) != 0) {
      driver_compile_argv_set_use_lto_c(state);
      return i + 1;
    }
    if (eq_minus_freestanding(arg_buf, len) != 0) {
      driver_compile_argv_set_use_freestanding_c(state);
      return i + 1;
    }
    if (eq_legacy_f32_abi(arg_buf, len) != 0) {
      driver_compile_argv_set_legacy_f32_abi_c();
      return i + 1;
    }
    if (eq_fsanitize_address(arg_buf, len) != 0) {
      driver_compile_argv_set_sanitize_address_c();
      return i + 1;
    }
    if (eq_minus_backend(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_backend_next_c(state, argc, argv, i, arg_buf, arg_cap);
      return i + 2;
    }
    if (eq_minus_target(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_target_next_c(state, argc, argv, i);
      return i + 2;
    }
    if (eq_minus_target_cpu(arg_buf, len) != 0 && i + 1 < argc) {
      driver_compile_argv_apply_target_cpu_next_c(state, argc, argv, i);
      return i + 2;
    }
    if (eq_print_target_cpu(arg_buf, len) != 0) {
      driver_compile_argv_set_print_target_cpu_c(state);
      return i + 1;
    }
    if (arg_buf[0] != 45 && path_ends_x(arg_buf, len) != 0) {
      driver_compile_argv_copy_path_c(state, arg_buf, len);
      return i + 1;
    }
    return i + 1;
  }
}

/**
 * See implementation.
 */
export function driver_compile_parse_argv_loop(argc: i32, argv: *u8, state: *DriverCompileState): i32 {
  let arg_buf: u8[512] = [];
  let i: i32 = 1;
  while (i < argc) {
    i = driver_compile_parse_argv_step(argc, argv, state, i, &arg_buf[0], 512);
  }
  return 0;
}

/** Exported function `driver_compile_parse_argv_finalize`.
 * Implements `driver_compile_parse_argv_finalize`.
 * @param state *DriverCompileState
 * @return i32
 */
export function driver_compile_parse_argv_finalize(state: *DriverCompileState): i32 {
  // See implementation.
  unsafe {
    driver_compile_resolve_target_cpu_c(state);
    if (state.print_target_cpu != 0) {
      return 0;
    }
    if (state.path_len <= 0) {
      return 1;
    }
    state.target_arch = driver_resolve_target_arch(state.target_arch, state.parse_saw_target);
    /* See implementation. */
    cfg_sync_compile_target_from_state_c(state);
    /* See implementation. */
    driver_compile_ensure_default_lib_c(driver_compile_state_key(state));
    return 0;
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function driver_compile_parse_argv(argc: i32, argv: *u8, state: *DriverCompileState): i32 {
  let one: i32 = 1;
  if (argc < 2) {
    return one;
  }
  driver_compile_parse_argv_init(state);
  driver_compile_parse_argv_loop(argc, argv, state);
  return driver_compile_parse_argv_finalize(state);
}

/**
 * See implementation.
 */
export function run_compiler_full_x_post_parse(state: *DriverCompileState, argc: i32, argv: *u8): i32 {
  // See implementation.
  unsafe {
    let one: i32 = 1;
    let zero: i32 = 0;
    if (state == 0 as *DriverCompileState) {
      return one;
    }
    if (driver_check_only_get() != 0) {
      /* check-only forces C/typeck path (not product -o). */
      state.use_asm_backend = zero;
    }
    /*
     * PLATFORM: SHARED — PC invoke_cc opt-in (2026-08-12): silent generic→C removed.
     * Historical: driver_source_has_generic_syntax on want_exe forced use_asm_backend=0
     * so product -o with generics auto-exec host-cc (invoke_cc) without `-backend c`.
     * That violated PC "C is opt-in only". Root fix: keep asm unless user passed
     * `-backend c` (argv parse) or check-only / emit-c flags. Generics that still
     * need host-C must pass `-backend c` explicitly.
     * Prior residual closed same class: import→C, seed __APPLE__ exe→C.
     * No-import -o still locks backend_asm_explicit for explicit-asm gate consumers.
     */
    let out_ptr: *u8 = 0 as *u8;
    if (state.out_path_len > 0) {
      out_ptr = &state.out_path_buf[0];
    }
    let target_ptr: *u8 = 0 as *u8;
    if (state.target_len > 0) {
      target_ptr = &state.target_buf[0];
    }
    if (state.out_path_len > 0 && state.backend_asm_explicit == 0 &&
        driver_source_has_top_level_import_path(&state.path_buf[0], state.path_len) == 0) {
      state.backend_asm_explicit = one;
    }
    if (state.use_freestanding != 0) {
      state.use_asm_backend = one;
      state.backend_asm_explicit = one;
      driver_compile_argv_set_use_freestanding_c(state);
    }
    let lib_key: *u8 = driver_compile_state_key(state);
    if (state.use_asm_backend != 0) {
      return compile_dispatch_asm_backend(&state.path_buf[0], out_ptr, lib_key, target_ptr, argc, argv);
    }
    return compile_dispatch_emit_c_path(
      &state.path_buf[0],
      out_ptr,
      lib_key,
      target_ptr,
      &state.opt_level_buf[0],
      state.use_lto,
      argc,
      argv
    );
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function run_compiler_full_x(argc: i32, argv: *u8): i32 {
  unsafe {
    let one: i32 = 1;
    let zero: i32 = 0;
    if (driver_compile_argv_is_help_c(argc, argv) != 0) {
      driver_print_usage_c();
      return zero;
    }
    driver_bump_stack_limit();
    let state: *DriverCompileState = driver_compile_state_alloc_c();
    if (state == 0 as *DriverCompileState) {
      return one;
    }
    if (driver_compile_parse_argv(argc, argv, state) != 0) {
      driver_compile_state_free_c(state);
      return one;
    }
    /* See implementation. */
    if (state.print_target_cpu != 0) {
      let rcpu: i32 = driver_print_target_cpu_features_c(state.target_cpu_features);
      driver_compile_state_free_c(state);
      return rcpu;
    }
    let r: i32 = run_compiler_full_x_post_parse(state, argc, argv);
    driver_compile_state_free_c(state);
    return r;
  }
}
