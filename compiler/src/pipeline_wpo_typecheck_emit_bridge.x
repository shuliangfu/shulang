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

// pipeline_wpo_typecheck_emit_bridge — WPO helper chain bridges: the
// pipeline_wpo.o X typecheck_entry thin bl needs the emit bridge, and
// pipeline_wpo_helpers_partial's bare-name calls need aliasing onto the
// pipeline.x exports. This TU provides exactly two forwarders and nothing
// else — in particular it must NOT provide pipeline_run_x_pipeline_impl
// (pipeline_x.o / the alias lane owns that face).
//
// 7.2.1 fifth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/pipeline_wpo_typecheck_emit_bridge.from_x.c, promoted from a
// retired .inc) to this .x source; build_xlang_asm's ensure regenerates
// via the product -x -E. PLATFORM: SHARED.

/** X typecheck entry emit body (thin bl target for pipeline_wpo.o). */
export extern function run_x_pipeline_typecheck_entry_emit_c(module: *u8, arena: *u8, ctx: *u8): i32;
/** pipeline.x's real resolver (pipeline_wpo_helpers_partial bare-name bridge). */
export extern function pipeline_resolve_path_try_one_lib_root(ctx: *u8, lib_idx: i32, import_path: *u8, path_len: i32): i32;

/**
 * pipeline_wpo.o X typecheck_entry's thin bl target: forward to the emit_c
 * body.
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

/**
 * Bridge pipeline_wpo_helpers_partial's bare-name resolver call onto the
 * pipeline.x-exported real symbol.
 * @param ctx *u8 — opaque ast_PipelineDepCtx
 * @param lib_idx i32 — lib root index
 * @param import_path *u8 — import path bytes
 * @param path_len i32 — import path length
 * @return i32 — resolver exit code
 * PLATFORM: SHARED.
 */
export function resolve_path_try_one_lib_root(ctx: *u8, lib_idx: i32, import_path: *u8, path_len: i32): i32 {
  unsafe {
    return pipeline_resolve_path_try_one_lib_root(ctx, lib_idx, import_path, path_len);
  }
  return 0;
}
