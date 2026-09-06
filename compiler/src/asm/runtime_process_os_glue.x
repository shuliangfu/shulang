// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_process_os_glue.x — OS process glue public API
// R2 migration: all public API functions defined here with #[no_mangle]
// OS bridge implementations (_impl) are in seeds/runtime_process_os_glue.from_x.c

export extern "C" function process_getenv_impl(name: *u8): *u8;
export extern "C" function process_setenv_impl(name: *u8, value: *u8, overwrite: i32): i32;
export extern "C" function process_unsetenv_impl(name: *u8): i32;
export extern "C" function process_getpid_impl(): i32;
export extern "C" function process_getppid_impl(): i32;
export extern "C" function process_getcwd_impl(buf: *u8, buf_size: i32): i32;
export extern "C" function process_getcwd_ptr_impl(): *u8;
export extern "C" function process_getcwd_cached_len_impl(): i32;
export extern "C" function process_chdir_impl(path: *u8): i32;
export extern "C" function process_self_exe_path_impl(buf: *u8, buf_size: i32): i32;
export extern "C" function process_self_exe_path_ptr_impl(): *u8;
export extern "C" function process_self_exe_path_cached_len_impl(): i32;
export extern "C" function process_nop_sigchld_impl(sig: i32): void;
export extern "C" function process_spawn_impl(program: *u8, argv_ptr: *u8): i32;
export extern "C" function process_exec_impl(program: *u8, argv_ptr: *u8): i32;
export extern "C" function process_waitpid_impl(pid: i32): i32;
export extern "C" function process_spawn_simple_impl(program: *u8): i32;
export extern "C" function process_exec_simple_impl(program: *u8): i32;
export extern "C" function process_dup_stdio_posix_impl(fd: i32, slot: i32): i32;
export extern "C" function process_spawn_io_impl(program: *u8, argv_ptr: *u8, io: *u8): i32;
export extern "C" function process_pipe_impl(read_fd: *i32, write_fd: *i32): i32;

/** Exported function `runtime_process_os_glue_x_doc_anchor`.
 * Implements `runtime_process_os_glue_x_doc_anchor`.
 * @return i32
 */
export function runtime_process_os_glue_x_doc_anchor(): i32 {
  return 0;
}

/** Get environment variable value.
 * @param name Environment variable name.
 * @return Value string pointer or null if not found. */
#[no_mangle]
export function process_getenv_c(name: *u8): *u8 {
  unsafe { return process_getenv_impl(name); }
}

/** Set environment variable.
 * Cap residual 9.1.1: process_setenv_impl via unified xlang_environ_setenv (POSIX walk / Win32 dual block, no libc setenv).
 * PLATFORM: SHARED Cap (9.1.1).
 * @param name Variable name.
 * @param value Variable value.
 * @param overwrite If non-zero, overwrite existing value.
 * @return 0 on success, -1 on failure. */
#[no_mangle]
export function process_setenv_c(name: *u8, value: *u8, overwrite: i32): i32 {
  unsafe { return process_setenv_impl(name, value, overwrite); }
}

/** Delete environment variable.
 * Cap residual 9.1.1: process_unsetenv_impl via unified xlang_environ_unsetenv (POSIX walk / Win32 dual block, no libc unsetenv).
 * PLATFORM: SHARED Cap (9.1.1).
 * @param name Variable name.
 * @return 0 on success, -1 on failure. */
#[no_mangle]
export function process_unsetenv_c(name: *u8): i32 {
  unsafe { return process_unsetenv_impl(name); }
}

/**
 * Bridge: get current process ID via Cap (no libc getpid).
 * Linux: raw syscall (nr 39/172) / Darwin: raw syscall (nr 0x2000014/20) /
 * Windows: GetCurrentProcessId.
 * PLATFORM: SHARED Cap (9.1.3).
 * @return Process ID.
 */
#[no_mangle]
export function process_getpid_c(): i32 {
  unsafe { return process_getpid_impl(); }
}

/**
 * Bridge: get parent process ID via Cap (no libc getppid).
 * Linux: raw syscall (nr 110/173) / Darwin: raw syscall (nr 0x2000027/39) /
 * Windows: -1 (unsupported).
 * PLATFORM: SHARED Cap (9.1.3).
 * @return Parent process ID or -1 if unsupported.
 */
#[no_mangle]
export function process_getppid_c(): i32 {
  unsafe { return process_getppid_impl(); }
}

/**
 * Bridge: get current working directory into buffer via Cap (no libc getcwd).
 * Linux: raw getcwd syscall / Darwin: raw open+fcntl(F_GETPATH)+close /
 * Windows: GetCurrentDirectoryA.
 * PLATFORM: SHARED Cap (9.1.3).
 * @param buf Output buffer.
 * @param buf_size Buffer capacity.
 * @return Bytes written (excluding NUL) on success, -1 on failure.
 */
#[no_mangle]
export function process_getcwd_c(buf: *u8, buf_size: i32): i32 {
  unsafe { return process_getcwd_impl(buf, buf_size); }
}

/**
 * Bridge: get zero-copy pointer to internal cached current working directory.
 * Fills cache on miss via Cap (no libc getcwd).
 * PLATFORM: SHARED Cap (9.1.3).
 * @return Pointer to internal cache or null on failure.
 */
#[no_mangle]
export function process_getcwd_ptr_c(): *u8 {
  unsafe { return process_getcwd_ptr_impl(); }
}

/**
 * Bridge: get cached cwd string length.
 * PLATFORM: SHARED Cap (9.1.3).
 * @return Length in bytes (excluding NUL), 0 if not cached.
 */
#[no_mangle]
export function process_getcwd_cached_len_c(): i32 {
  unsafe { return process_getcwd_cached_len_impl(); }
}

/**
 * Bridge: change current working directory via Cap (no libc chdir).
 * Linux: raw chdir syscall (nr 80/49) / Darwin: raw chdir syscall (nr 0x200000c/12) /
 * Windows: SetCurrentDirectoryA.
 * Invalidates internal cwd cache.
 * PLATFORM: SHARED Cap (9.1.3).
 * @param path Target directory path (NUL-terminated).
 * @return 0 on success, -1 on failure.
 */
#[no_mangle]
export function process_chdir_c(path: *u8): i32 {
  unsafe { return process_chdir_impl(path); }
}

/** Get current executable path into buffer.
 * @param buf Output buffer.
 * @param buf_size Buffer capacity.
 * @return Bytes written (excluding NUL) on success, -1 on failure. */
#[no_mangle]
export function process_self_exe_path_c(buf: *u8, buf_size: i32): i32 {
  unsafe { return process_self_exe_path_impl(buf, buf_size); }
}

/** Get zero-copy pointer to executable path.
 * @return Pointer to internal cache or null on failure. */
#[no_mangle]
export function process_self_exe_path_ptr_c(): *u8 {
  unsafe { return process_self_exe_path_ptr_impl(); }
}

/** Get cached executable path string length.
 * @return Length in bytes (excluding NUL), 0 if not cached. */
#[no_mangle]
export function process_self_exe_path_cached_len_c(): i32 {
  unsafe { return process_self_exe_path_cached_len_impl(); }
}

/** Empty SIGCHLD handler for spawn.
 * @param sig Signal number. */
#[no_mangle]
export function process_nop_sigchld(sig: i32): void {
  unsafe { process_nop_sigchld_impl(sig); }
}

/** Spawn child process.
 * Cap residual 9.1.4: process_spawn_impl uses Cap xlang_proc_fork + xlang_proc_execve (no libc fork/execve).
 * PLATFORM: SHARED Cap (Linux/Darwin raw syscall; Windows CreateProcess).
 * @param program Program path.
 * @param argv_ptr Argument vector pointer.
 * @return Child PID (>0) on success, -1 on failure. */
#[no_mangle]
export function process_spawn_c(program: *u8, argv_ptr: *u8): i32 {
  unsafe { return process_spawn_impl(program, argv_ptr); }
}

/** Replace current process with program (exec).
 * Cap residual 9.1.4: process_exec_impl uses Cap xlang_proc_execve (no libc execve).
 * PLATFORM: SHARED Cap (Linux/Darwin raw syscall; Windows unsupported).
 * @param program Program path.
 * @return -1 on failure (success doesn't return). */
#[no_mangle]
export function process_exec_c(program: *u8, argv_ptr: *u8): i32 {
  unsafe { return process_exec_impl(program, argv_ptr); }
}

/** Wait for child process to exit.
 * Cap residual 9.1.4: process_waitpid_impl uses Cap xlang_proc_waitpid (no libc waitpid).
 * PLATFORM: SHARED Cap (Linux/Darwin raw wait4; Windows WaitForSingleObject).
 * @param pid Child process ID.
 * @return Exit code (low 8 bits) on success, -1 on failure. */
#[no_mangle]
export function process_waitpid_c(pid: i32): i32 {
  unsafe { return process_waitpid_impl(pid); }
}

/** Simplified spawn with argv = [program, NULL].
 * Cap residual 9.1.4: routes to process_spawn_impl (Linux/Darwin raw fork+execve).
 * PLATFORM: SHARED Cap.
 * @param program Program path.
 * @return Child PID (>0) on success, -1 on failure. */
#[no_mangle]
export function process_spawn_simple_c(program: *u8): i32 {
  unsafe { return process_spawn_simple_impl(program); }
}

/** Duplicate file descriptor to stdio slot (POSIX only).
 * Cap residual 9.1.4: uses Cap xlang_proc_dup2 (no libc dup2).
 * PLATFORM: SHARED Cap (Linux/Darwin raw syscall).
 * @param fd Source file descriptor.
 * @param slot Target slot (STDIN_FILENO, etc.).
 * @return 0 on success, -1 on failure, 0 if fd < 0. */
#[no_mangle]
export function process_dup_stdio_posix(fd: i32, slot: i32): i32 {
  unsafe { return process_dup_stdio_posix_impl(fd, slot); }
}

/** Spawn child process with stdio redirection.
 * Cap residual 9.1.4: POSIX fork + dup2 + execve via Cap (no libc).
 * PLATFORM: SHARED Cap (Linux/Darwin raw syscall; Windows CreateProcess).
 * @param program Program path.
 * @param argv_ptr Argument vector pointer.
 * @param io SpawnIo struct pointer (stdin/stdout/stderr fds).
 * @return Child PID (>0) on success, -1 on failure. */
#[no_mangle]
export function process_spawn_io_c(program: *u8, argv_ptr: *u8, io: *u8): i32 {
  unsafe { return process_spawn_io_impl(program, argv_ptr, io); }
}

/** Simplified exec with argv = [program, NULL].
 * Cap residual 9.1.4: routes to process_exec_impl (Linux/Darwin raw execve).
 * PLATFORM: SHARED Cap.
 * @param program Program path.
 * @return -1 on failure (success doesn't return). */
#[no_mangle]
export function process_exec_simple_c(program: *u8): i32 {
  unsafe { return process_exec_simple_impl(program); }
}

/** Create pipe.
 * Cap residual 9.1.4: Linux/Darwin raw syscall pipe via xlang_proc_pipe (no libc pipe).
 * PLATFORM: SHARED Cap (Linux/Darwin raw syscall; Windows CreatePipe).
 * @param read_fd Output read file descriptor.
 * @param write_fd Output write file descriptor.
 * @return 0 on success, -1 on failure. */
#[no_mangle]
export function process_pipe_c(read_fd: *i32, write_fd: *i32): i32 {
  unsafe { return process_pipe_impl(read_fd, write_fd); }
}
