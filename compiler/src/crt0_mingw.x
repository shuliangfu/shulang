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

// crt0_mingw — Win64 PE process entry for the MinGW/MSYS2 bootstrap lane
// (Phase E-04 v21). The default MinGW CRT resolves the command line and
// calls main; this TU replaces main.c / main_driver.o on Windows hosts and
// forwards to main.x's main_entry via the runtime_abi trampoline.
// driver_get_argv_i stays provided by runtime_abi.c.
//
// 7.2.1 second knife (2026-09-10): authority moved from the hand-written C
// seed (seeds/crt0_mingw.from_x.c, promoted from a retired .inc) to this
// .x source; the cc_inc_tu --auto lane regenerates via the product -x -E
// and fixes the emitted main signature to char** (C main requirement; .x
// has no char type — u8 maps to uint8_t). PLATFORM: WINDOWS|MINGW entry;
// regeneration lane is host-portable.

/** runtime_abi trampoline into main.x's main_entry (argc/argv pass through). */
export extern function xlang_forward_main_to_main_entry(argc: i32, argv: **u8): i32;

/**
 * PE link entry: equivalent to main.c but dedicated to Windows-host
 * bootstrap (does not link main_driver.o). Forwards to main_entry.
 * @param argc i32 — argc from the MinGW CRT
 * @param argv **u8 — argv from the MinGW CRT (emitted as char** after the
 *        lane's signature fixup)
 * @return i32 — main_entry's exit code
 * PLATFORM: WINDOWS|MINGW.
 */
function main(argc: i32, argv: **u8): i32 {
  unsafe {
    return xlang_forward_main_to_main_entry(argc, argv);
  }
  return 0;
}
