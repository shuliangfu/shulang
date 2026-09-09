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

// pipeline_asm_run_all_alias — strict chain: the C implementation of
// pipeline_impl_run_all / run_x_pipeline_impl. build_asm/pipeline.o's
// second-pass emit of run_all had a cbz-branch bug after a typecheck
// failure (still entered codegen — return-value smoke hung at 100% CPU);
// this TU follows pipeline.x semantics: return immediately on typecheck
// failure.
//
// 7.2.1 ninth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/pipeline_asm_run_all_alias.from_x.c, promoted from a retired
// .inc) to this .x source. PLATFORM: SHARED.

/** Pipeline phase impls (pipeline_x.o / strict_core partial exports). */
export extern function pipeline_impl_phase_parse_load(module: *u8, arena: *u8, source_data: *u8, source_len: usize, ctx: *u8): i32;
export extern function pipeline_impl_typecheck(module: *u8, arena: *u8, ctx: *u8): i32;
export extern function pipeline_impl_should_skip_codegen(ctx: *u8): i32;
export extern function pipeline_impl_codegen_chain(module: *u8, arena: *u8, out_buf: *u8, ctx: *u8): i32;

/**
 * Full pipeline orchestration; identical to pipeline.x's
 * pipeline_impl_run_all — parse/load, typecheck (early return on
 * failure), optional codegen skip, codegen chain.
 * @param module *u8 — opaque ast_Module
 * @param arena *u8 — opaque ast_ASTArena
 * @param source_data *u8 — preprocessed source bytes
 * @param source_len usize — source byte length
 * @param out_buf *u8 — opaque codegen_CodegenOutBuf
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @return i32 — first failing phase's exit code, else codegen's
 * PLATFORM: SHARED.
 */
export function pipeline_impl_run_all(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32 {
  let pl: i32 = 0;
  let tc: i32 = 0;
  unsafe {
    pl = pipeline_impl_phase_parse_load(module, arena, source_data, source_len, ctx);
  }
  if (pl != 0) {
    return pl;
  }
  unsafe {
    tc = pipeline_impl_typecheck(module, arena, ctx);
  }
  if (tc != 0) {
    return tc;
  }
  unsafe {
    if (pipeline_impl_should_skip_codegen(ctx) != 0) {
      return 0;
    }
  }
  unsafe {
    return pipeline_impl_codegen_chain(module, arena, out_buf, ctx);
  }
  return 0;
}

/**
 * Bare-name entry called by glue / pipeline_run_impl_alias.
 * @return i32 — pipeline_impl_run_all's exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_impl(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32 {
  unsafe {
    return pipeline_impl_run_all(module, arena, source_data, source_len, out_buf, ctx);
  }
  return 0;
}
