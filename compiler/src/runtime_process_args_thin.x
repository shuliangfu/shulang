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

// runtime_process_args_thin — process_args_count_c / process_arg_c argv
// wrappers for std.process. PLATFORM: SHARED — process_merge piece (with
// argv + os_glue + import_alias).
//
// process.o = this TU + runtime_process_argv.o + runtime_process_os_glue.o
// + runtime_process_import_alias.from_x.c (std_process_* product face).
// Pure-asm import METHOD needs the namespaced face in process.o (no
// mod.x co-emit); import_alias is the single product-face vehicle (G.7).
//
// 7.2.1 fourth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/runtime_process_args_thin.from_x.c — the historical cold
// authority existed because library -x -E truncated mid-emit after the
// giant rt_preamble; the product -E now emits this TU completely) to this
// .x source; the process_merge lane regenerates via the product -x -E.
//
// Invariant: bare symbols process_args_count_c / process_arg_c only
// forward argv glue (process_xlang_*). Do NOT add std_process_* here —
// that is import_alias's face.

/** argv glue provider (runtime_process_argv family). */
export extern function process_xlang_argc_get(): i32;
export extern function process_xlang_argv_get(i: i32): *u8;

/**
 * Bare process-args face: forward argc from the argv glue.
 * @return i32 — process argc
 * PLATFORM: SHARED.
 */
export function process_args_count_c(): i32 {
  unsafe {
    return process_xlang_argc_get();
  }
  return 0;
}

/**
 * Bare process-args face: forward argv[i] from the argv glue.
 * @param i i32 — argv index (0-based; bounds are the glue's concern)
 * @return *u8 — argv[i] bytes (NUL-terminated C string)
 * PLATFORM: SHARED.
 */
export function process_arg_c(i: i32): *u8 {
  unsafe {
    return process_xlang_argv_get(i);
  }
  return 0 as *u8;
}
