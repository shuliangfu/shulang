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

// pipeline_asm_typecheck_alias — strict asm orchestration chain: only
// pipeline_impl_typecheck. build_asm/pipeline.o's second-pass emit had
// incomplete if/else branches (force_c / typeck_x_ast) that skipped typeck
// or mis-took the library path (null-module smoke failed); this TU is
// ld -r'd in separately, semantically identical to
// pipeline_asm_orchestration_alias.inc / pipeline.x, calling the C-side
// typeck_typeck_x_ast* family.
//
// 7.2.1 eleventh knife (2026-09-10): authority moved from the hand-written
// C seed (seeds/pipeline_asm_typecheck_alias.from_x.c, promoted from a
// retired .inc) to this .x source. PLATFORM: SHARED.

/** Driver/typeck gate + diagnostic externs (C side). */
export extern function driver_typeck_skip_large_entry(): i32;
export extern function driver_asm_build_skip_typeck(): i32;
export extern function driver_typeck_force_c_enabled(): i32;
export extern function driver_diagnostic_typeck_fail(): void;
export extern function pipeline_module_main_func_index(module: *u8): i32;
export extern function typeck_typeck_x_ast(module: *u8, arena: *u8, ctx: *u8): i32;
export extern function typeck_typeck_x_ast_library(module: *u8, arena: *u8, ctx: *u8): i32;
export extern function pipeline_typeck_module_for_ctx(module: *u8, arena: *u8, ctx: *u8): i32;

/**
 * Typecheck phase: negative exit on failure, 0 when skipped or clean.
 * Skip when either large-entry or asm-build-skip gate fires. Library
 * modules (no main) go to the library face (force_c picks the for-ctx
 * variant); main modules to the entry face; both report through
 * driver_diagnostic_typeck_fail on failure.
 * @param module *u8 — opaque ast_Module
 * @param arena *u8 — opaque ast_ASTArena
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @return i32 — 0 ok/skipped; negative or phase code on failure
 * PLATFORM: SHARED.
 */
export function pipeline_impl_typecheck(module: *u8, arena: *u8, ctx: *u8): i32 {
  let tc_lib: i32 = 0;
  let tc_main: i32 = 0;
  unsafe {
    if (driver_typeck_skip_large_entry() != 0) {
      return 0;
    }
    if (driver_asm_build_skip_typeck() != 0) {
      return 0;
    }
    if (pipeline_module_main_func_index(module) < 0) {
      if (driver_typeck_force_c_enabled() != 0) {
        tc_lib = pipeline_typeck_module_for_ctx(module, arena, ctx);
      } else {
        tc_lib = typeck_typeck_x_ast_library(module, arena, ctx);
      }
      if (tc_lib != 0) {
        driver_diagnostic_typeck_fail();
        return tc_lib;
      }
      return 0;
    }
    tc_main = 0;
    if (driver_typeck_force_c_enabled() != 0) {
      tc_main = pipeline_typeck_module_for_ctx(module, arena, ctx);
    } else {
      if (typeck_typeck_x_ast(module, arena, ctx) != 0) {
        tc_main = 0 - 1;
      }
    }
    if (tc_main != 0) {
      driver_diagnostic_typeck_fail();
      return 0 - 1;
    }
    return 0;
  }
  return 0;
}
