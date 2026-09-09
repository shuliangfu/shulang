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

// runtime_process_import_alias — pure-asm product std_process_* face.
// PLATFORM: SHARED — ld -r into std/process/process.o (process_merge
// authority).
//
// Why (G.7 complete process_merge): pure-asm import METHOD mangles
// import("std.process").args_count → std_process_args_count (etc.).
// process_merge historically only carried bare ABI process_*_c (args thin +
// argv + os_glue). C-path product co-emitted mod.x for the namespaced face;
// pure-asm skips that co-emit and links prebuilt process.o → UNDEF
// std_process_*. Authority: thin 1:1 wrappers over the process_*_c already
// T in process.o after merge — import-binding names only, no second OS body.
//
// exit: mod.x stub returns 0; product tests need real terminate —
// Cap residual 9.1.4 uses xlang_proc_exit (Linux/Darwin raw syscall, no
// libc _exit).
//
// 7.2.1 twelfth knife (2026-09-10): authority moved from the hand-written
// C seed (seeds/runtime_process_import_alias.from_x.c) to this .x source;
// process_merge's lane regenerates via the product -x -E. The void* io
// param maps to *u8 (ABI-identical pointer).

/** Bare ABI faces already T in process.o after the merge. */
export extern function process_args_count_c(): i32;
export extern function process_arg_c(i: i32): *u8;
export extern function process_getenv_c(name: *u8): *u8;
export extern function process_setenv_c(name: *u8, value: *u8, overwrite: i32): i32;
export extern function process_unsetenv_c(name: *u8): i32;
export extern function process_getpid_c(): i32;
export extern function process_getppid_c(): i32;
export extern function process_getcwd_c(buf: *u8, buf_size: i32): i32;
export extern function process_getcwd_ptr_c(): *u8;
export extern function process_getcwd_cached_len_c(): i32;
export extern function process_chdir_c(path: *u8): i32;
export extern function process_self_exe_path_c(buf: *u8, buf_size: i32): i32;
export extern function process_self_exe_path_ptr_c(): *u8;
export extern function process_self_exe_path_cached_len_c(): i32;
export extern function process_spawn_c(program: *u8, argv: *u8): i32;
export extern function process_spawn_io_c(program: *u8, argv: *u8, io: *u8): i32;
export extern function process_exec_c(program: *u8, argv: *u8): i32;
export extern function process_waitpid_c(pid: i32): i32;
export extern function process_spawn_simple_c(program: *u8): i32;
export extern function process_exec_simple_c(program: *u8): i32;
export extern function process_pipe_c(read_fd: *i32, write_fd: *i32): i32;
/** Cap residual 9.1.4: raw-syscall terminate (never returns). */
export extern "C" function xlang_proc_exit(code: i32): void;

/**
 * Product std.process.exit — terminate with code (Cap residual 9.1.4:
 * Linux/Darwin raw syscall via xlang_proc_exit, no libc _exit).
 * @param code i32 — process exit status
 * @return i32 — 0 (unreachable; terminate never returns)
 * PLATFORM: SHARED Cap residual.
 */
export function std_process_exit(code: i32): i32 {
  unsafe {
    xlang_proc_exit(code);
  }
  return 0;
}

/**
 * Import-binding 1:1 wrappers (std_process_* → process_*_c). Each mirrors
 * the std/process/mod.x export surface signature; no business logic.
 * PLATFORM: SHARED — ld -r into process.o.
 */
export function std_process_args_count(): i32 {
  unsafe { return process_args_count_c(); }
  return 0;
}

export function std_process_arg(i: i32): *u8 {
  unsafe { return process_arg_c(i); }
  return 0 as *u8;
}

export function std_process_getenv(name: *u8): *u8 {
  unsafe { return process_getenv_c(name); }
  return 0 as *u8;
}

export function std_process_setenv(name: *u8, value: *u8, overwrite: i32): i32 {
  unsafe { return process_setenv_c(name, value, overwrite); }
  return 0;
}

export function std_process_unsetenv(name: *u8): i32 {
  unsafe { return process_unsetenv_c(name); }
  return 0;
}

export function std_process_getpid(): i32 {
  unsafe { return process_getpid_c(); }
  return 0;
}

export function std_process_getppid(): i32 {
  unsafe { return process_getppid_c(); }
  return 0;
}

export function std_process_getcwd(buf: *u8, buf_size: i32): i32 {
  unsafe { return process_getcwd_c(buf, buf_size); }
  return 0;
}

export function std_process_getcwd_ptr(): *u8 {
  unsafe { return process_getcwd_ptr_c(); }
  return 0 as *u8;
}

export function std_process_getcwd_cached_len(): i32 {
  unsafe { return process_getcwd_cached_len_c(); }
  return 0;
}

export function std_process_chdir(path: *u8): i32 {
  unsafe { return process_chdir_c(path); }
  return 0;
}

export function std_process_self_exe_path(buf: *u8, buf_size: i32): i32 {
  unsafe { return process_self_exe_path_c(buf, buf_size); }
  return 0;
}

export function std_process_self_exe_path_ptr(): *u8 {
  unsafe { return process_self_exe_path_ptr_c(); }
  return 0 as *u8;
}

export function std_process_self_exe_path_cached_len(): i32 {
  unsafe { return process_self_exe_path_cached_len_c(); }
  return 0;
}

export function std_process_spawn(program: *u8, argv: *u8): i32 {
  unsafe { return process_spawn_c(program, argv); }
  return 0;
}

export function std_process_spawn_io(program: *u8, argv: *u8, io: *u8): i32 {
  unsafe { return process_spawn_io_c(program, argv, io); }
  return 0;
}

export function std_process_exec(program: *u8, argv: *u8): i32 {
  unsafe { return process_exec_c(program, argv); }
  return 0;
}

export function std_process_waitpid(pid: i32): i32 {
  unsafe { return process_waitpid_c(pid); }
  return 0;
}

export function std_process_spawn_simple(program: *u8): i32 {
  unsafe { return process_spawn_simple_c(program); }
  return 0;
}

export function std_process_exec_simple(program: *u8): i32 {
  unsafe { return process_exec_simple_c(program); }
  return 0;
}

export function std_process_pipe(read_fd: *i32, write_fd: *i32): i32 {
  unsafe { return process_pipe_c(read_fd, write_fd); }
  return 0;
}
