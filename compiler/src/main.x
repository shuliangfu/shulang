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
//
// See implementation.
//
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.

const ast = import("ast");
const codegen = import("codegen");
const sys = import("std.sys");
export extern "C" function fs_posix_write_c(fd: i32, buf: *u8, count: usize): isize;
export extern "C" function fs_posix_close_c(fd: i32): i32;
/* See implementation. */
export extern function preprocess_x_buf(source_buf: *u8, source_len: isize, out_buf: *u8, out_cap: i32): i32;
/* See implementation. */
export extern function driver_cmd_fmt(argc: i32, argv: *u8): i32;
export extern function driver_cmd_check(argc: i32, argv: *u8): i32;
export extern function driver_cmd_test(argc: i32, argv: *u8): i32;
export extern function driver_print_usage_write(): void;

/* See implementation. */
export struct DriverXEmitState {
  path_buf: u8[512];
  path_len: i32;
  /* See implementation. */
  emit_extern_imports: i32;
  /* See implementation. */
  use_asm_backend: i32;
  /* See implementation. */
  target_arch: i32;
  /* See implementation. */
  out_path_buf: u8[512];
  out_path_len: i32;
}

/* See implementation. */
export extern function driver_emit_lib_root_reset(state: *u8): void;
export extern function driver_emit_append_lib_root(state: *u8, path: *u8, len: i32): i32;
export extern function driver_emit_lib_root_count(state: *u8): i32;
export extern function driver_emit_lib_root_len(state: *u8, i: i32): i32;
export extern function driver_emit_lib_root_copy(state: *u8, i: i32, dst: *u8, cap: i32): void;

/**
 * Emit surface authority lives in `src/driver/emit.x` → `driver_emit_x.o`
 * (Track L renames `emit_state_key` → `driver_emit_state_key`).
 * G.7: do not re-define here — dual strong T with driver_emit_x.o breaks
 * Darwin pure-ld (ld64: `-multiply_defined` obsolete; 5 duplicate symbols).
 * PLATFORM: SHARED — main.x only declares; emit leaf owns the body.
 */
export extern function driver_emit_state_key(state: *DriverXEmitState): *u8;

/** Exported function `driver_emit_try_append_lib_from_argv`.
 * Implements `driver_emit_try_append_lib_from_argv`.
 * @param argc i32
 * @param argv *u8
 * @param arg_i i32
 * @param state *DriverXEmitState
 * @return i32
 */
export function driver_emit_try_append_lib_from_argv(argc: i32, argv: *u8, arg_i: i32, state: *DriverXEmitState): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    let tmp: u8[256] = [];
    let llen: i32 = driver_get_argv_i(argc, argv, arg_i, &tmp[0], 256);
    if (llen >= 0 && driver_emit_append_lib_root(driver_emit_state_key(state), &tmp[0], llen) >= 0) {
      return 1;
    }
    return 0;
  }
}

/** Exported function `driver_emit_ensure_default_lib_root`.
 * Implements `driver_emit_ensure_default_lib_root`.
 * @param state *DriverXEmitState
 * @return void
 */
export function driver_emit_ensure_default_lib_root(state: *DriverXEmitState): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (driver_emit_lib_root_count(driver_emit_state_key(state)) == 0) {
      let dot: u8[1] = [46];
      driver_emit_append_lib_root(driver_emit_state_key(state), &dot[0], 1);
    }
  }
}

/**
 * Emit surface authority: `emit.x` → `driver_emit_copy_lib_roots_to_ctx`
 * (Track L rename from `emit_copy_lib_roots_to_ctx`).
 * G.7: no body here — dual strong T with driver_emit_x.o.
 * Call sites that need it must link driver_emit_x.o (product bag always does).
 * PLATFORM: SHARED.
 */
export extern function driver_emit_copy_lib_roots_to_ctx(state: *DriverXEmitState, ctx: *PipelineDepCtx): void;

/**
 * See implementation.
 * See implementation.
 */
export function driver_emit_state_default(): DriverXEmitState {
  return {
    path_buf: [],
    path_len: 0,
    emit_extern_imports: 0,
    use_asm_backend: 1,
    target_arch: 0
  };
}

/**
 * See implementation.
 */
export function pipeline_dep_ctx_for_emit(use_asm: i32, target: i32): PipelineDepCtx {
  let ctx: PipelineDepCtx = {
    ndep: 0,
    entry_dir_buf: [],
    entry_dir_len: 0,
    num_lib_roots: 0
  };
  ctx.use_asm_backend = use_asm;
  ctx.target_arch = target;
  ctx.current_func_index = -1;
  ctx.current_func_single_empty_param_index = -1;
  return ctx;
}

/* See implementation. */
export extern function driver_get_argv_i(argc: i32, argv: *u8, i: i32, buf: *u8, max: i32): i32;
/**
 * See implementation.
 * See implementation.
 */
export extern function driver_argv_drop_subcommand(argc: i32, argv: *u8): *u8;
/* See implementation (seed runtime_link_abi.from_x.c). For `xlang run` / bare
   `xlang file.x`: append `-o <temp>` when no -o given so the product is built
   in /tmp and exec'd, with no a.out and no generated C to stdout. */
export extern function driver_argv_ensure_run_o(argc: i32, argv: *u8, out_argc: *i32): *u8;
/* See implementation. */
export extern function driver_build_build_x(): i32;
/* See implementation. */
export extern function driver_exec_compiled(argc: i32, argv: *u8): i32;
export extern "C" function setenv(name: *u8, value: *u8, overwrite: i32): i32;
/* See implementation. */
export extern function driver_fs_open_read_path(path: *u8, path_len: i32): i32;
/* See implementation. */
export extern function driver_arena_buf(): *u8;
export extern function driver_module_buf(): *u8;
/* See implementation. */
export extern function driver_fs_open_write(path: *u8, path_len: i32): i32;
/* See implementation. */
export extern function driver_pipeline_fail_code(rc: i32, path: *u8): void;
/* See implementation. */
export extern function driver_print_x_smoke_summary(module: *u8, codegen_len: usize): void;

/* See implementation. */
export extern function driver_run_x_emit_c_set_path(path: *u8, path_len: i32): i32;
export extern function driver_run_x_emit_c_set_lib(i: i32, buf: *u8, len: i32): i32;
export extern function driver_run_x_emit_c_set_n_lib_roots(n: i32): i32;
/* See implementation. */
export extern function driver_run_x_emit_c_set_emit_extern(v: i32): i32;
export extern function driver_run_x_emit_c(): i32;

/* See implementation. */
export extern function pipeline_run_x_pipeline_impl(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *CodegenOutBuf, ctx: *PipelineDepCtx): i32;
/* See implementation. */
export extern function ast_pipeline_ctx_append_lib_root(ctx: *PipelineDepCtx, path: *u8, len: i32): i32;

/* See implementation. */
export extern function driver_run_compiler_full(argc: i32, argv: *u8): i32;
/** Exported function `run_compiler_c_impl`.
 * Implements `run_compiler_c_impl`.
 * @param argc i32
 * @param argv *u8
 * @return i32
 */
export function run_compiler_c_impl(argc: i32, argv: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return driver_run_compiler_full(argc, argv);
  }
}
/**
 * `run_compiler_c` name authority: `src/runtime/rt_entry.x` (inside
 * runtime_driver_no_c.o) trampolines to `main_run_compiler_c`.
 * G.7: main.x must NOT also export `run_compiler_c` — dual strong T with
 * runtime_driver_no_c.o fails Darwin pure-ld. Real work stays in
 * `run_compiler_c_impl` / `main_run_compiler_c`.
 * PLATFORM: SHARED.
 */
export extern function run_compiler_c(argc: i32, argv: *u8): i32;

/**
 * Product-side body for the runtime trampoline `run_compiler_c` → here.
 * Calls `run_compiler_c_impl` directly (not the runtime trampoline) so the
 * chain cannot recurse when both TUs are linked.
 * PLATFORM: SHARED.
 */
export function main_run_compiler_c(argc: i32, argv: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    return run_compiler_c_impl(argc, argv);
  }
}

/** Exported function `eq_minus_L`.
 * Implements `eq_minus_L`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_L(buf: *u8, len: i32): i32 {
  if (len < 2) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 76) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_x`.
 * Implements `eq_minus_x`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_x(buf: *u8, len: i32): i32 {
  if (len < 3) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 115 && buf[2] == 120) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_E`.
 * Implements `eq_minus_E`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_E(buf: *u8, len: i32): i32 {
  if (len < 2) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 69) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_E_extern`.
 * Implements `eq_minus_E_extern`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_E_extern(buf: *u8, len: i32): i32 {
  if (len < 9) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 69 && buf[2] == 45 && buf[3] == 101 && buf[4] == 120 && buf[5] == 116 && buf[6] == 101 && buf[7] == 114 && buf[8] == 110) {
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
  if (len < 8) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 98 && buf[2] == 97 && buf[3] == 99 && buf[4] == 107 && buf[5] == 101 && buf[6] == 110 && buf[7] == 100) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_asm`.
 * Implements `eq_asm`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_asm(buf: *u8, len: i32): i32 {
  if (len < 3) {
    return 0;
  }
  if (buf[0] == 97 && buf[1] == 115 && buf[2] == 109) {
    return 1;
  }
  return 0;
}

/** Exported function `eq_minus_lsp`.
 * Implements `eq_minus_lsp`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function eq_minus_lsp(buf: *u8, len: i32): i32 {
  if (len < 5) {
    return 0;
  }
  if (buf[0] == 45 && buf[1] == 45 && buf[2] == 108 && buf[3] == 115 && buf[4] == 112) {
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
  if (buf[0] == 45 && buf[1] == 116 && buf[2] == 97 && buf[3] == 114 && buf[4] == 103 && buf[5] == 101 && buf[6] == 116) {
    return 1;
  }
  return 0;
}

/** Exported function `str_eq`.
 * Implements `str_eq`.
 * @param a *u8
 * @param a_len i32
 * @param b *u8
 * @param b_len i32
 * @return i32
 */
export function str_eq(a: *u8, a_len: i32, b: *u8, b_len: i32): i32 {
  if (a_len != b_len) {
    return 0;
  }
  let i: i32 = 0;
  while (i < a_len) {
    if (a[i] != b[i]) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}

/** Exported function `target_contains_arm`.
 * Implements `target_contains_arm`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function target_contains_arm(buf: *u8, len: i32): i32 {
  let start: i32 = 0;
  while (start + 7 <= len) {
    if (buf[start] == 97 && buf[start + 1] == 97 && buf[start + 2] == 114 && buf[start + 3] == 99 && buf[start + 4] == 104 && buf[start + 5] == 54 && buf[start + 6] == 52) {
      return 1;
    }
    start = start + 1;
  }
  start = 0;
  while (start + 5 <= len) {
    if (buf[start] == 97 && buf[start + 1] == 114 && buf[start + 2] == 109 && buf[start + 3] == 54 && buf[start + 4] == 52) {
      return 1;
    }
    start = start + 1;
  }
  return 0;
}

/** Exported function `target_contains_riscv`.
 * Implements `target_contains_riscv`.
 * @param buf *u8
 * @param len i32
 * @return i32
 */
export function target_contains_riscv(buf: *u8, len: i32): i32 {
  let start: i32 = 0;
  while (start + 7 <= len) {
    if (buf[start] == 114 && buf[start + 1] == 105 && buf[start + 2] == 115 && buf[start + 3] == 99 && buf[start + 4] == 118 && buf[start + 5] == 54 && buf[start + 6] == 52) {
      return 1;
    }
    start = start + 1;
  }
  return 0;
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 */
export function driver_argv_parse_x_path(argc: i32, argv: *u8, state: *DriverXEmitState): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    state.path_len = 0;
    driver_emit_lib_root_reset(driver_emit_state_key(state));
    state.emit_extern_imports = 0;
    /* See implementation. */
    state.use_asm_backend = 1;
    state.target_arch = 0;
    state.out_path_len = 0;
    if (argc < 2) {
      return 2;
    }
    let arg_buf: u8[512] = [];
    let i: i32 = 1;
    let has_o: i32 = 0;
    while (i < argc) {
      let len: i32 = driver_get_argv_i(argc, argv, i, arg_buf, 512);
      if (len < 0) {
        i = i + 1;
        continue;
      }
      if (eq_minus_target(arg_buf, len) != 0 && i + 1 < argc) {
        let tlen: i32 = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
        if (tlen >= 0 && target_contains_arm(arg_buf, tlen) != 0) {
          state.target_arch = 1;
        }
        if (tlen >= 0 && target_contains_riscv(arg_buf, tlen) != 0) {
          state.target_arch = 2;
        }
        i = i + 2;
        continue;
      }
      if (eq_minus_L(arg_buf, len) != 0) {
        if (i + 1 >= argc) {
          return 2;
        }
        driver_emit_try_append_lib_from_argv(argc, argv, i + 1, state);
        i = i + 2;
        continue;
      }
      if (eq_minus_backend(arg_buf, len) != 0 && i + 1 < argc) {
        let vlen: i32 = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
        /* See implementation. */
        if (vlen >= 0 && vlen == 1 && arg_buf[0] == 99) {
          state.use_asm_backend = 0;
        }
        if (vlen >= 0 && eq_asm(arg_buf, vlen) != 0) {
          state.use_asm_backend = 1;
        }
        i = i + 2;
        continue;
      }
      /* See implementation. */
      if (len == 2 && arg_buf[0] == 45 && arg_buf[1] == 111) {
        if (i + 1 < argc) {
          let olen: i32 = driver_get_argv_i(argc, argv, i + 1, state.out_path_buf, 512);
          if (olen >= 0) {
            state.out_path_len = olen;
          }
          i = i + 2;
        } else {
          has_o = 1;
          i = i + 1;
        }
        continue;
      }
      if (len == 2 && arg_buf[0] == 45 && arg_buf[1] == 79) {
        i = i + 1;
        if (i < argc) {
          i = i + 1;
        }
        continue;
      }
      if (eq_minus_x(arg_buf, len) != 0) {
        i = i + 1;
        continue;
      }
      if (eq_minus_E(arg_buf, len) != 0) {
        i = i + 1;
        continue;
      }
      if (eq_minus_E_extern(arg_buf, len) != 0) {
        i = i + 1;
        continue;
      }
      if (state.path_len == 0 && len > 0) {
        let k: i32 = 0;
        while (k < len && k < 512) {
          state.path_buf[k] = arg_buf[k];
          k = k + 1;
        }
        state.path_len = len;
      }
      i = i + 1;
    }
    if (has_o != 0) {
      return 1;
    }
    if (state.path_len == 0) {
      return 2;
    }
    /* See implementation. */
    driver_emit_ensure_default_lib_root(state);
    return 0;
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function driver_argv_parse_x(argc: i32, argv: *u8, state: *DriverXEmitState): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    state.path_len = 0;
    driver_emit_lib_root_reset(driver_emit_state_key(state));
    state.emit_extern_imports = 0;
    state.use_asm_backend = 0;
    state.target_arch = 0;
    state.out_path_len = 0;
    if (argc < 3) {
      return 0;
    }
    let arg_buf: u8[512] = [];
    let i: i32 = 1;
    while (i < argc) {
      let len: i32 = driver_get_argv_i(argc, argv, i, arg_buf, 512);
      if (len < 0) {
        i = i + 1;
        continue;
      }
      if (eq_minus_L(arg_buf, len) != 0 && i + 1 < argc) {
        driver_emit_try_append_lib_from_argv(argc, argv, i + 1, state);
        i = i + 2;
        continue;
      }
      if (eq_minus_backend(arg_buf, len) != 0 && i + 1 < argc) {
        let vlen: i32 = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
        if (vlen >= 0 && eq_asm(arg_buf, vlen) != 0) {
          state.use_asm_backend = 1;
        }
        i = i + 2;
        continue;
      }
      if (eq_minus_target(arg_buf, len) != 0 && i + 1 < argc) {
        let tlen: i32 = driver_get_argv_i(argc, argv, i + 1, arg_buf, 512);
        if (tlen >= 0 && target_contains_arm(arg_buf, tlen) != 0) {
          state.target_arch = 1;
        }
        if (tlen >= 0 && target_contains_riscv(arg_buf, tlen) != 0) {
          state.target_arch = 2;
        }
        i = i + 2;
        continue;
      }
      if (eq_minus_x(arg_buf, len) != 0) {
        i = i + 1;
        continue;
      }
      if (eq_minus_E(arg_buf, len) != 0) {
        let pi: i32 = i + 1;
        while (pi < argc) {
          let plen_temp: i32 = driver_get_argv_i(argc, argv, pi, arg_buf, 512);
          if (plen_temp > 0 && eq_minus_L(arg_buf, plen_temp) != 0 && pi + 1 < argc) {
            driver_emit_try_append_lib_from_argv(argc, argv, pi + 1, state);
            pi = pi + 2;
            continue;
          }
          if (plen_temp > 0 && eq_minus_x(arg_buf, plen_temp) != 0) {
            pi = pi + 1;
            continue;
          }
          break;
        }
        if (pi < argc) {
          let opt_len: i32 = driver_get_argv_i(argc, argv, pi, arg_buf, 512);
          if (opt_len >= 0 && eq_minus_E_extern(arg_buf, opt_len) != 0) {
            state.emit_extern_imports = 1;
            pi = pi + 1;
          }
        }
        if (pi < argc) {
          let plen: i32 = driver_get_argv_i(argc, argv, pi, state.path_buf, 512);
          if (plen >= 0) {
            state.path_len = plen;
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Emit path authority: `src/driver/emit.x` `run_x_emit_x` → Track L rename
 * `driver_run_x_emit_x` in `driver_emit_x.o`.
 * G.7: historic monorepo body removed from main.x so pure-ld has a single
 * strong definition (Darwin ld64 rejects multidef; Linux hid this via
 * `--allow-multiple-definition` first-wins).
 * PLATFORM: SHARED — product bag always links driver_emit_x.o.
 */
export extern function driver_run_x_emit_x(state: *DriverXEmitState): i32;

/**
 * See implementation.
 * See implementation.
 */
export function main_run_compiler_x_path_impl(argc: i32, argv: *u8): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let state: DriverXEmitState = driver_emit_state_default();
    let r: i32 = driver_argv_parse_x_path(argc, argv, &state);
    if (r == 1) {
      return run_compiler_c_impl(argc, argv);
    }
    if (r == 2) {
      return run_compiler_c_impl(argc, argv);
    }
    if (state.use_asm_backend != 0) {
      return run_compiler_c_impl(argc, argv);
    }
    /*
     * See implementation.
     * See implementation.
     * See implementation.
     * See implementation.
     */
    if (state.out_path_len > 0) {
      return run_compiler_c_impl(argc, argv);
    }
    return driver_run_x_emit_x(&state);
  }
}

/**
 * See implementation.
 */
export function main_cmd_build(argc: i32, argv: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (argc < 2) {
      return driver_build_build_x();
    }
    return main_run_compiler_x_path_impl(argc, argv);
  }
}

/**
 * `xlang run file.x` (and bare `xlang file.x` via main_entry): compile in memory and
 * run the product directly. No a.out in the cwd and no generated C to stdout.
 * When no -o is given, driver_argv_ensure_run_o injects a temp /tmp path as
 * -o so the C/asm backend links a real executable (instead of the no-`-o`
 * stdout/smoke fallback); driver_exec_compiled then execs that temp. An
 * explicit -o is honored as compile-only (write to the requested path, do
 * not exec) so callers like tests/run-*.sh can inspect the binary's exit
 * code themselves. PLATFORM: SHARED.
 */
export function main_cmd_run(argc: i32, argv: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (argc < 2) {
      return 1;
    }
    /* Detect an explicit user-supplied -o before driver_argv_ensure_run_o runs.
     * Why: driver_argv_ensure_run_o silently injects a temp -o when none is
     * present, so run_argv alone cannot tell whether the user asked for
     * compile-only. When -o is explicit, skip the exec path so the compiled
     * program's exit code does not leak through xlang's own exit status. */
    let has_explicit_o: i32 = main_argv_has_o_flag(argc, argv);
    let run_argc: i32 = argc;
    let run_argv: *u8 = driver_argv_ensure_run_o(argc, argv, &run_argc);
    if (has_explicit_o != 0) {
      /* Compile-only: do not set XLANG_RUN_QUIET (let cc warnings surface, since
       * the user explicitly requested an output path) and do not exec. */
      return main_run_compiler_x_path_impl(run_argc, run_argv);
    }
    /* mute generated-C warning noise so only program output is printed; cc
       errors still surface (XLANG_RUN_QUIET only adds -w / -Wl,-w in invoke_cc). */
    /* "XLANG_RUN_QUIET" (14 bytes) + NUL terminator; setenv needs a C string. */
    let _q: u8[16] = [88, 76, 65, 78, 71, 95, 82, 85, 78, 95, 81, 85, 73, 69, 84, 0];
    let _one: u8[2] = [49, 0];
    unsafe { setenv(&_q[0], &_one[0], 1); }
    let rc: i32 = main_run_compiler_x_path_impl(run_argc, run_argv);
    if (rc == 0) {
      return driver_exec_compiled(run_argc, run_argv);
    }
    return rc;
  }
}

/* Returns 1 if any argv[i] (i in [1, argc)) equals "-o" (the canonical short
 * form for output path), 0 otherwise. Used by main_cmd_run to distinguish
 * compile-only invocations from in-memory compile-and-run. PLATFORM: SHARED.
 * Contract: argc >= 1; argv may be null only when argc < 1 (returns 0). */
function main_argv_has_o_flag(argc: i32, argv: *u8): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let i: i32 = 1;
    let buf: u8[8] = [];
    while (i < argc) {
      let len: i32 = driver_get_argv_i(argc, argv, i, &buf[0], 8);
      /* "-o" == bytes [45 ('-'), 111 ('o')] */
      if (len == 2 && buf[0] == 45 && buf[1] == 111) {
        return 1;
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Return 1 if argv[1] looks like a source path rather than a named subcommand.
 * Heuristic (PLATFORM: SHARED): ends with ".x", or contains '/' or '\\'.
 * Used by main_entry() so bare `xlang file.x [-o out]` is not rejected as an unknown
 * command (historical product UX; many gates still invoke this form).
 * Contract: path may be truncated to path_cap-1 bytes by the caller; scan only
 * the provided len bytes. Null path or len <= 0 → 0.
 */
function main_arg_looks_like_source_path(path: *u8, len: i32): i32 {
  if (path == 0 as *u8 || len <= 0) {
    return 0;
  }
  /* Ends with ".x" (46 = '.', 120 = 'x'). */
  if (len >= 2 && path[len - 2] == 46 && path[len - 1] == 120) {
    return 1;
  }
  let i: i32 = 0;
  while (i < len) {
    /* '/' = 47, '\\' = 92 */
    if (path[i] == 47 || path[i] == 92) {
      return 1;
    }
    i = i + 1;
  }
  return 0;
}

/* See implementation. */
export extern function typeck_lsp_main(): i32;

/**
 * Product CLI entry symbol (ABI name: main_entry).
 *
 * Single authority for the freestanding / pure-ld product entry:
 * crt0 `_start` and `xlang_forward_main_to_main_entry` both call `main_entry`.
 * Track L PREFER_X_O (`src/main.x` → driver_x.o) and cold seed
 * `seeds/driver_gen.linux.x86_64.c` must export the same symbol — never emit
 * a bare `entry` from .x while the seed / link ABI expect `main_entry`
 * (L4 Darwin pure-ld UNDEF `_main_entry` when names diverged).
 *
 * Named subcommands: build | run | fmt | check | test.
 * Bare source path (ends with .x or contains a path separator): treat as
 * `run` semantics without requiring the word "run" — with explicit -o this is
 * compile-only (main_cmd_run); without -o compile-and-exec.
 * Unknown non-flag argv[1] that is not a path → usage and exit 1.
 * PLATFORM: SHARED — mac + Ubuntu product binary must accept the same bare form.
 */
export function main_entry(argc: i32, argv: *u8): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let arg_buf: u8[128] = [];
    let i: i32 = 1;
    while (i < argc) {
      let len: i32 = driver_get_argv_i(argc, argv, i, arg_buf, 64);
      if (len >= 0 && eq_minus_lsp(arg_buf, len) != 0) {
        return typeck_lsp_main();
      }
      i = i + 1;
    }
    /* Dispatch named subcommands; bare .x path falls through to main_cmd_run. */
    if (argc >= 2) {
      let alen: i32 = driver_get_argv_i(argc, argv, 1, arg_buf, 64);
      if (alen > 0 && arg_buf[0] != 45) {
        let w_build: u8[5] = [98, 117, 105, 108, 100];
        let w_run: u8[3] = [114, 117, 110];
        let w_fmt: u8[3] = [102, 109, 116];
        let w_check: u8[5] = [99, 104, 101, 99, 107];
        let w_test: u8[4] = [116, 101, 115, 116];
        if (str_eq(&arg_buf[0], alen, &w_build[0], 5) != 0) {
          return main_cmd_build(argc - 1, driver_argv_drop_subcommand(argc, argv));
        }
        if (str_eq(&arg_buf[0], alen, &w_run[0], 3) != 0) {
          return main_cmd_run(argc - 1, driver_argv_drop_subcommand(argc, argv));
        }
        if (str_eq(&arg_buf[0], alen, &w_fmt[0], 3) != 0) {
          return driver_cmd_fmt(argc - 1, driver_argv_drop_subcommand(argc, argv));
        }
        if (str_eq(&arg_buf[0], alen, &w_check[0], 5) != 0) {
          return driver_cmd_check(argc - 1, driver_argv_drop_subcommand(argc, argv));
        }
        if (str_eq(&arg_buf[0], alen, &w_test[0], 4) != 0) {
          return driver_cmd_test(argc - 1, driver_argv_drop_subcommand(argc, argv));
        }
        /* Bare path: do not drop argv[1]; it is the input file. */
        if (main_arg_looks_like_source_path(&arg_buf[0], alen) != 0) {
          return main_cmd_run(argc, argv);
        }
        driver_print_usage_write();
        return 1;
      }
    }
    let state: DriverXEmitState = driver_emit_state_default();
    if (driver_argv_parse_x(argc, argv, &state) != 0) {
      /* See implementation. */
      /* See implementation. */
      driver_run_x_emit_c_set_emit_extern(state.emit_extern_imports);
      driver_run_x_emit_c_set_path(state.path_buf, state.path_len);
      let k: i32 = 0;
      let n_roots: i32 = driver_emit_lib_root_count(driver_emit_state_key(&state));
      let lib_tmp: u8[256] = [];
      while (k < n_roots) {
        let llen: i32 = driver_emit_lib_root_len(driver_emit_state_key(&state), k);
        driver_emit_lib_root_copy(driver_emit_state_key(&state), k, &lib_tmp[0], 256);
        driver_run_x_emit_c_set_lib(k, &lib_tmp[0], llen);
        k = k + 1;
      }
      driver_run_x_emit_c_set_n_lib_roots(n_roots);
      return driver_run_x_emit_c();
    }
    /* See implementation. */
    return main_run_compiler_x_path_impl(argc, argv);
  }
}
