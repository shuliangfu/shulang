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

// pipeline_run_x_link_alias — experimental chain's pipeline X helper
// symbol aliases. pipeline_x.o (C-generated via -E-extern) exports the
// pipeline_run_x_pipeline_* prefixed names while the orchestration expects
// the run_x_pipeline_* bare names. The strict chain gets the bare names
// from build_asm/pipeline.o's real asm emit — do NOT link this TU there.
//
// 7.2.1 tenth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/pipeline_run_x_link_alias.from_x.c, promoted from a retired
// .inc) to this .x source. PLATFORM: SHARED.

/** pipeline_x.o module-prefixed exports. */
export extern function pipeline_run_x_pipeline_fill_dep_import_path(module: *u8, ctx: *u8, dep_j: i32): i32;
export extern function pipeline_run_x_pipeline_codegen_one_dep(module: *u8, out_buf: *u8, ctx: *u8, dep_j: i32, skip_asm_dep_codegen: i32): i32;
export extern function pipeline_run_x_pipeline_codegen_deps(module: *u8, arena: *u8, out_buf: *u8, ctx: *u8, skip_asm_dep_codegen: i32): i32;
export extern function pipeline_run_x_pipeline_codegen_entry(module: *u8, arena: *u8, out_buf: *u8, ctx: *u8): i32;

/**
 * Orchestration bare name → pipeline_x.o module-prefixed export
 * (fill_dep_import_path face).
 * @return i32 — impl exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_fill_dep_import_path(module: *u8, ctx: *u8, dep_j: i32): i32 {
  unsafe {
    return pipeline_run_x_pipeline_fill_dep_import_path(module, ctx, dep_j);
  }
  return 0;
}

/**
 * Orchestration bare name → pipeline_x.o module-prefixed export
 * (codegen_one_dep face).
 * @return i32 — impl exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_codegen_one_dep(module: *u8, out_buf: *u8, ctx: *u8, dep_j: i32, skip_asm_dep_codegen: i32): i32 {
  unsafe {
    return pipeline_run_x_pipeline_codegen_one_dep(module, out_buf, ctx, dep_j, skip_asm_dep_codegen);
  }
  return 0;
}

/**
 * Orchestration bare name → pipeline_x.o module-prefixed export
 * (codegen_deps face).
 * @return i32 — impl exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_codegen_deps(module: *u8, arena: *u8, out_buf: *u8, ctx: *u8, skip_asm_dep_codegen: i32): i32 {
  unsafe {
    return pipeline_run_x_pipeline_codegen_deps(module, arena, out_buf, ctx, skip_asm_dep_codegen);
  }
  return 0;
}

/**
 * Orchestration bare name → pipeline_x.o module-prefixed export
 * (codegen_entry face).
 * @return i32 — impl exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_codegen_entry(module: *u8, arena: *u8, out_buf: *u8, ctx: *u8): i32 {
  unsafe {
    return pipeline_run_x_pipeline_codegen_entry(module, arena, out_buf, ctx);
  }
  return 0;
}
