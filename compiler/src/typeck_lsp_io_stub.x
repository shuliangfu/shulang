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

// typeck_lsp_io_stub — the typeck_* IO symbol stubs lsp_gen.c expects
// (shared by seed xlang / strict_glue). When lsp_io_gen.c goes -E-extern,
// read_message etc. are provided by the typeck module mangling; this TU
// only satisfies the link for asm-only / empty lsp_io builds — the full
// LSP still uses the bootstrap xlang-x.
//
// 7.2.1 sixth knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/typeck_lsp_io_stub.from_x.c, promoted from a retired .inc)
// to this .x source; build_xlang_asm's ensure regenerates via the product
// -x -E. Note: the historical ptrdiff_t return maps to .x isize (emits
// ssize_t — ABI-identical on LP64). PLATFORM: SHARED.

/**
 * lsp.x's typeck-mangled read_message: stub returns -1 (EOF/error).
 * @param fd i32 — file descriptor (ignored)
 * @param body_out *u8 — body buffer (ignored)
 * @param body_cap i32 — body capacity (ignored)
 * @param state_buf *u8 — state buffer (ignored)
 * @return isize — always -1
 * PLATFORM: SHARED.
 */
function typeck_read_message(fd: i32, body_out: *u8, body_cap: i32, state_buf: *u8): isize {
  return 0 - 1;
}

/**
 * lsp_io heap-alloc stub (do NOT use for production LSP).
 * @param size usize — request size (ignored)
 * @return *u8 — always null
 * PLATFORM: SHARED.
 */
function typeck_lsp_alloc(size: usize): *u8 {
  return 0 as *u8;
}

/**
 * lsp_io free stub (no-op).
 * @param p *u8 — pointer (ignored)
 * PLATFORM: SHARED.
 */
function typeck_lsp_free(p: *u8): void {
}

/**
 * lsp_io null-check stub.
 * @param p *u8 — pointer to test
 * @return i32 — 1 when null, 0 otherwise
 * PLATFORM: SHARED.
 */
function typeck_lsp_is_null(p: *u8): i32 {
  if (p == 0 as *u8) {
    return 1;
  }
  return 0;
}
