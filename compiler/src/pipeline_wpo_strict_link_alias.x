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

// pipeline_wpo_strict_link_alias — strict WPO chain glue: pipeline_wpo.o X
// orchestration + the names the runtime expects. pipeline_wpo.o exports
// run_x_pipeline_impl while glue/driver still reference
// pipeline_run_x_pipeline_impl; the X typecheck_entry thin bl references
// run_x_pipeline_typecheck_entry_emit → ast_pool emit_c. When the strict
// chain does NOT link the C orchestration partial, this TU fills both
// faces — avoiding a duplicate run_x_pipeline_impl definition.
//
// NOTE (lane isolation): this TU and src/pipeline_wpo_typecheck_emit_bridge.x
// both provide run_x_pipeline_typecheck_entry_emit for DIFFERENT strict
// lanes (WPO chain vs strict-WPO chain, gated by STRICT_LINK_BUILD_ASM_WPO
// reach checks) — they are never linked together.
//
// 7.2.1 seventh knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/pipeline_wpo_strict_link_alias.from_x.c, promoted from a
// retired .inc) to this .x source. PLATFORM: SHARED.

/** pipeline_wpo.o's WPO root orchestration (asm emit). */
export extern function run_x_pipeline_impl(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32;
/** ast_pool's entry typecheck emit C glue (wave309 left). */
export extern function run_x_pipeline_typecheck_entry_emit_c(module: *u8, arena: *u8, ctx: *u8): i32;

/**
 * Glue/driver's unified entry name → pipeline_wpo.o's run_x_pipeline_impl.
 * @param module *u8 — opaque ast_Module
 * @param arena *u8 — opaque ast_ASTArena
 * @param source_data *u8 — preprocessed source bytes
 * @param source_len usize — source byte length
 * @param out_buf *u8 — opaque codegen_CodegenOutBuf
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @return i32 — orchestration exit code
 * PLATFORM: SHARED.
 */
export function pipeline_run_x_pipeline_impl(module: *u8, arena: *u8, source_data: *u8, source_len: usize, out_buf: *u8, ctx: *u8): i32 {
  unsafe {
    return run_x_pipeline_impl(module, arena, source_data, source_len, out_buf, ctx);
  }
  return 0;
}

/**
 * X typecheck_entry thin bl → C emit (pipeline_wpo.o has this symbol U).
 * @param module *u8 — opaque ast_Module
 * @param arena *u8 — opaque ast_ASTArena
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @return i32 — emit_c exit code
 * PLATFORM: SHARED.
 */
export function run_x_pipeline_typecheck_entry_emit(module: *u8, arena: *u8, ctx: *u8): i32 {
  unsafe {
    return run_x_pipeline_typecheck_entry_emit_c(module, arena, ctx);
  }
  return 0;
}
