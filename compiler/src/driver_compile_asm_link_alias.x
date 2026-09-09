// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// driver_compile_asm_link_alias — strict-chain driver X symbol aliases.
// build_asm/driver_compile.o (EMIT_HEAVY single-shot compile.x) exports
// run_compiler_full_x / compile_dispatch_* bare names; runtime.c and the
// C-gen driver_compile_x.o expect the driver_* link names. ld -r merges
// this TU into build_asm/driver_compile_link.o for
// relink_xlang_asm_strict_glue to swap in place of driver_compile_x.o.
//
// 7.2.1 eighth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/driver_compile_asm_link_alias.from_x.c, promoted from a
// retired .inc) to this .x source. PLATFORM: SHARED.

/** compile.x EMIT_HEAVY thin wrappers (bare names). */
export extern function run_compiler_full_x(argc: i32, argv: *u8): i32;
export extern function run_compiler_full_x_post_parse(state: *u8, argc: i32, argv: *u8): i32;
export extern function compile_dispatch_asm_backend(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, argc: i32, argv: *u8): i32;
export extern function compile_dispatch_emit_c_path(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, opt_level: *u8, use_lto: i32, argc: i32, argv: *u8): i32;

/**
 * runtime's driver_run_compiler_full link entry → asm EMIT_HEAVY thin
 * wrapper.
 * @param argc i32 — argv length
 * @param argv *u8 — opaque char** driver argv
 * @return i32 — run_compiler_full_x exit code
 * PLATFORM: SHARED.
 */
export function driver_run_compiler_full_x(argc: i32, argv: *u8): i32 {
  unsafe {
    return run_compiler_full_x(argc, argv);
  }
  return 0;
}

/**
 * post_parse link name → asm bare name (impl_c calls back via thin
 * delegate).
 * @param state *u8 — opaque DriverCompileState (layout-compatible pass-through)
 * @param argc i32 — argv length
 * @param argv *u8 — opaque char** driver argv
 * @return i32 — post_parse exit code
 * PLATFORM: SHARED.
 */
export function driver_run_compiler_full_x_post_parse(state: *u8, argc: i32, argv: *u8): i32 {
  unsafe {
    return run_compiler_full_x_post_parse(state, argc, argv);
  }
  return 0;
}

/**
 * C-gen / gate dispatch symbol → asm X real-emit bare name.
 * @return i32 — dispatch exit code
 * PLATFORM: SHARED.
 */
export function driver_compile_dispatch_asm_backend(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, argc: i32, argv: *u8): i32 {
  unsafe {
    return compile_dispatch_asm_backend(input_path, out_path, lib_key, target, argc, argv);
  }
  return 0;
}

/**
 * C-gen / gate dispatch symbol → asm X real-emit bare name (emit_c_path
 * face with opt_level/lto).
 * @return i32 — dispatch exit code
 * PLATFORM: SHARED.
 */
export function driver_compile_dispatch_emit_c_path(input_path: *u8, out_path: *u8, lib_key: *u8, target: *u8, opt_level: *u8, use_lto: i32, argc: i32, argv: *u8): i32 {
  unsafe {
    return compile_dispatch_emit_c_path(input_path, out_path, lib_key, target, opt_level, use_lto, argc, argv);
  }
  return 0;
}
