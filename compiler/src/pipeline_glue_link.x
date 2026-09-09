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

// pipeline_glue_link — minimal C bridge for the Target-B experimental chain
// (does not pull in the whole pipeline_gen.c). runtime_driver.o calls
// pipeline_run_x_pipeline with a buf+len; the impl lives in pipeline_x.o
// (pipeline_run_x_pipeline_impl) or via pipeline_run_impl_alias.o.
//
// 7.2.1 third knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/pipeline_glue_link.from_x.c, promoted from a retired .inc)
// to this .x source; build_xlang_asm's ensure regenerates via the product
// -x -E into a stable worktree gen. Note: the historical C declared
// source_data as const uint8_t* and cast away const at the forwarding
// call; the .x emits uint8_t* uniformly (const-buf face is the caller's
// concern — same ABI, no cast needed). PLATFORM: SHARED.

/** The real pipeline body (pipeline_x.o / alias lane). Opaque pointers. */
export extern function pipeline_run_x_pipeline_impl(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32;

/**
 * runtime.c's const-buf entry into the pipeline: forward verbatim to the
 * .x pipeline implementation symbol.
 * @param module *u8 — opaque ast_Module
 * @param arena *u8 — opaque ast_ASTArena
 * @param source_data *u8 — preprocessed source bytes (caller may hold const)
 * @param source_len usize — source byte length
 * @param out_buf *u8 — opaque codegen_CodegenOutBuf
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @return i32 — pipeline exit code (0 ok)
 * PLATFORM: SHARED.
 */
function pipeline_run_x_pipeline(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32 {
  unsafe {
    return pipeline_run_x_pipeline_impl(module, arena, source_data, source_len, out_buf, ctx);
  }
  return 0;
}
