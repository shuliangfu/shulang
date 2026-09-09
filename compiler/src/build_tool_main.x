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

// build_tool_main — thinnest possible process entry for the build_tool
// raw-cc lane (build_tool.sh links build_tool_main.o + build_runner.o +
// build_tool.o + build_runtime_x.o + build_tool_libc_bridge.o with plain
// cc -lc). This TU only forwards to build_runner's entry(). 7.2.1 first
// knife (2026-09-10): authority moved from the hand-written C seed
// (seeds/build_tool_main.from_x.c, promoted from a retired .inc) to this
// .x source; the ensure lane regenerates via the product -x -E and fixes
// the emitted main signature to char** (C main requirement; .x has no
// char type — u8 maps to uint8_t). PLATFORM: SHARED.

/** build_runner entry (compiled separately; C symbol `entry`). */
export extern function entry(argc: i32, argv: **u8): i32;

/**
 * Process entry: forward to build_runner's entry. argc/argv pass through
 * unchanged; the emitted C main signature is lane-fixed to char**.
 * @param argc i32 — process argc from crt
 * @param argv **u8 — process argv (emitted as char** after the lane fixup)
 * @return i32 — entry's exit code
 * PLATFORM: SHARED.
 */
function main(argc: i32, argv: **u8): i32 {
  unsafe {
    return entry(argc, argv);
  }
  return 0;
}
