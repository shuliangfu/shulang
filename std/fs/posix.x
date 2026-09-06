// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// Full text: LICENSE.Apache-2.0

// See implementation.
//
// See implementation.
// See implementation.
// See implementation.
//
// See implementation.
// See implementation.

/* Cap residual 9.1.2: Linux fs_libc_stat/fstat via raw_syscall (no libc). */
const linux = import("std.sys.linux");

/* See implementation. */
const io_sync = import("std.io.sync");

/* See implementation. */
let fs_saved_last_error: i32 = 0;
let fs_saved_last_error_set: i32 = 0;

/* See implementation. */
allow(padding) struct FsStatOut {
  size: i64;
  mode: u32;
  is_dir: i32;
  is_file: i32;
  mtime_sec: i64;
}

/* See implementation. */

/* See implementation. */
allow(padding) struct FsIovecBuf { ptr: *u8; length: usize; handle: usize; }

/* See implementation. */
allow(padding) struct FsDirHandlePosix { dir: *u8; }

/** See implementation for details. */
#[cfg(target_os = "linux")]
allow(padding) struct PosixStatBuf {
  st_dev: u64;
  st_ino: u64;
  st_nlink: u64;
  st_mode: u32;
  st_uid: u32;
  st_gid: u32;
  pad0: u32;
  st_rdev: u64;
  st_size: i64;
  st_blksize: i64;
  st_blocks: i64;
  st_atime: i64;
  st_atime_nsec: i64;
  st_mtime: i64;
  st_mtime_nsec: i64;
  st_ctime: i64;
  st_ctime_nsec: i64;
  __unused0: i64;
  __unused1: i64;
  __unused2: i64;
}

/* See implementation. */
#[cfg(target_os = "macos")]
allow(padding) struct PosixStatBuf {
  st_dev: i32;
  st_mode: u16;
  st_nlink: u16;
  st_ino: u64;
  st_uid: u32;
  st_gid: u32;
  st_rdev: i32;
  pad0: i32;
  st_atime: i64;
  st_atime_nsec: i64;
  st_mtime: i64;
  st_mtime_nsec: i64;
  st_ctime: i64;
  st_ctime_nsec: i64;
  st_birthtime: i64;
  st_birthtime_nsec: i64;
  st_size: i64;
  st_blocks: i64;
  st_blksize: i32;
  st_flags: i32;
  st_gen: u32;
  st_lspare: i32;
  st_qspare: i64[2];
}

/* See implementation. */

/* See implementation. */
extern "C" function xlang_sys_read(fd: i32, buf: *u8, count: usize): isize;
extern "C" function xlang_sys_write(fd: i32, buf: *u8, count: usize): isize;
extern "C" function xlang_sys_readv(fd: i32, iov: *u8, iovcnt: i32): isize;
extern "C" function xlang_sys_writev(fd: i32, iov: *u8, iovcnt: i32): isize;
extern "C" function xlang_sys_poll(fds: *u8, nfds: i32, timeout: i32): i32;
extern "C" function open(path: *u8, flags: i32, mode: i32): i32;
extern "C" function close(fd: i32): i32;
extern "C" function xlang_sys_pread(fd: i32, buf: *u8, count: usize, offset: i64): isize;
extern "C" function xlang_sys_pwrite(fd: i32, buf: *u8, count: usize, offset: i64): isize;
extern "C" function mmap(addr: *u8, len: usize, prot: i32, flags: i32, fd: i32, offset: i64): *u8;
extern "C" function munmap(addr: *u8, len: usize): i32;
extern "C" function fstat(fd: i32, st: *PosixStatBuf): i32;
extern "C" function stat(path: *u8, st: *PosixStatBuf): i32;
extern "C" function fsync(fd: i32): i32;
extern "C" function fchmod(fd: i32, mode: u32): i32;
extern "C" function chmod(path: *u8, mode: u32): i32;
extern "C" function mkdir(path: *u8, mode: u32): i32;
/* See implementation. */
extern "C" function xlang_fs_unlink(path: *u8): i32;
extern "C" function xlang_fs_rmdir(path: *u8): i32;
extern "C" function umask(mask: u32): u32;
/* Cap residual 9.1.10: POSIX (Linux and Darwin) dir via xlang_dir_cap.h (no libc opendir). */
extern "C" function xlang_dir_opendir(name: *u8): *u8;
extern "C" function xlang_dir_readdir(dirp: *u8): *u8;
extern "C" function xlang_dir_closedir(dirp: *u8): i32;
extern "C" function malloc(size: usize): *u8;
extern "C" function free(ptr: *u8): void;
extern "C" function memcpy(dst: *u8, src: *u8, n: usize): *u8;
extern "C" function strlen(s: *u8): usize;
#[cfg(target_os = "linux")]
extern "C" function __errno_location(): *i32;

#[cfg(target_os = "macos")]
extern "C" function __error(): *i32;
extern "C" function fcntl(fd: i32, cmd: i32, arg: i32): i32;
extern "C" function usleep(usec: u32): i32;
extern "C" function madvise(addr: *u8, len: usize, advice: i32): i32;

/** Exported function `fs_libc_open`.
 * Implements `fs_libc_open`.
 * @param path *u8
 * @param flags i32
 * @param mode i32
 * @return i32
 */
export function fs_libc_open(path: *u8, flags: i32, mode: i32): i32 {
  unsafe { return open(path, flags, mode); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_close`.
 * Implements `fs_libc_close`.
 * @param fd i32
 * @return i32
 */
export function fs_libc_close(fd: i32): i32 {
  unsafe { return close(fd); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_read`.
 * Read path helper `fs_libc_read`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @return isize
 */
export function fs_libc_read(fd: i32, buf: *u8, count: usize): isize {
  unsafe { return xlang_sys_read(fd, buf, count); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_write`.
 * Write path helper `fs_libc_write`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @return isize
 */
export function fs_libc_write(fd: i32, buf: *u8, count: usize): isize {
  unsafe { return xlang_sys_write(fd, buf, count); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_pread`.
 * Read path helper `fs_libc_pread`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @param offset i64
 * @return isize
 */
export function fs_libc_pread(fd: i32, buf: *u8, count: usize, offset: i64): isize {
  unsafe { return xlang_sys_pread(fd, buf, count, offset); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_pwrite`.
 * Write path helper `fs_libc_pwrite`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @param offset i64
 * @return isize
 */
export function fs_libc_pwrite(fd: i32, buf: *u8, count: usize, offset: i64): isize {
  unsafe { return xlang_sys_pwrite(fd, buf, count, offset); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_mmap`.
 * Implements `fs_libc_mmap`.
 * @param addr *u8
 * @param len usize
 * @param prot i32
 * @param flags i32
 * @param fd i32
 * @param offset i64
 * @return *u8
 */
export function fs_libc_mmap(addr: *u8, len: usize, prot: i32, flags: i32, fd: i32, offset: i64): *u8 {
  unsafe { return mmap(addr, len, prot, flags, fd, offset); }
  return 0 as *u8; // unreachable — typeck workaround
}
/** Exported function `fs_libc_munmap`.
 * Implements `fs_libc_munmap`.
 * @param addr *u8
 * @param len usize
 * @return i32
 */
export function fs_libc_munmap(addr: *u8, len: usize): i32 {
  unsafe { return munmap(addr, len); }
  return 0; // unreachable — typeck workaround
}
/**
 * Cap residual 9.1.2: fstat via raw_syscall2 (x86_64 nr=5). No libc fstat.
 * @param fd i32
 * @param st *PosixStatBuf — Linux struct stat layout
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|x86_64
 */
#[cfg(target_os = "linux")]
#[cfg(target_arch = "x86_64")]
export function fs_libc_fstat(fd: i32, st: *PosixStatBuf): i32 {
  let r: i64 = 0;
  unsafe {
    r = linux.raw_syscall2(5, fd as i64, st as i64);
  }
  if (r < 0) {
    return -1;
  }
  return 0;
}

/**
 * Cap residual 9.1.2: fstat via raw_syscall2 (aarch64 nr=80). No libc fstat.
 * @param fd i32
 * @param st *PosixStatBuf
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|aarch64
 */
#[cfg(target_os = "linux")]
#[cfg(target_arch = "aarch64")]
export function fs_libc_fstat(fd: i32, st: *PosixStatBuf): i32 {
  let r: i64 = 0;
  unsafe {
    r = linux.raw_syscall2(80, fd as i64, st as i64);
  }
  if (r < 0) {
    return -1;
  }
  return 0;
}

/**
 * Darwin / non-Linux Cap residual: libc fstat.
 * @param fd i32
 * @param st *PosixStatBuf
 * @return i32
 * PLATFORM: MACOS|DARWIN
 */
#[cfg(target_os = "macos")]
export function fs_libc_fstat(fd: i32, st: *PosixStatBuf): i32 {
  unsafe { return fstat(fd, st); }
  return 0; // unreachable — typeck workaround
}

/**
 * Cap residual 9.1.2: stat via newfstatat (x86_64 nr=262, AT_FDCWD=-100).
 * @param path *u8 — NUL-terminated path
 * @param st *PosixStatBuf
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|x86_64
 */
#[cfg(target_os = "linux")]
#[cfg(target_arch = "x86_64")]
export function fs_libc_stat(path: *u8, st: *PosixStatBuf): i32 {
  let r: i64 = 0;
  unsafe {
    r = linux.raw_syscall4(262, -100 as i64, path as i64, st as i64, 0);
  }
  if (r < 0) {
    return -1;
  }
  return 0;
}

/**
 * Cap residual 9.1.2: stat via fstatat (aarch64 nr=79, AT_FDCWD=-100).
 * @param path *u8
 * @param st *PosixStatBuf
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|aarch64
 */
#[cfg(target_os = "linux")]
#[cfg(target_arch = "aarch64")]
export function fs_libc_stat(path: *u8, st: *PosixStatBuf): i32 {
  let r: i64 = 0;
  unsafe {
    r = linux.raw_syscall4(79, -100 as i64, path as i64, st as i64, 0);
  }
  if (r < 0) {
    return -1;
  }
  return 0;
}

/**
 * Darwin Cap residual: libc stat.
 * @param path *u8
 * @param st *PosixStatBuf
 * @return i32
 * PLATFORM: MACOS|DARWIN
 */
#[cfg(target_os = "macos")]
export function fs_libc_stat(path: *u8, st: *PosixStatBuf): i32 {
  unsafe { return stat(path, st); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_fsync`.
 * Implements `fs_libc_fsync`.
 * @param fd i32
 * @return i32
 */
export function fs_libc_fsync(fd: i32): i32 {
  unsafe { return fsync(fd); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_fchmod`.
 * Implements `fs_libc_fchmod`.
 * @param fd i32
 * @param mode u32
 * @return i32
 */
export function fs_libc_fchmod(fd: i32, mode: u32): i32 {
  unsafe { return fchmod(fd, mode); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_chmod`.
 * Implements `fs_libc_chmod`.
 * @param path *u8
 * @param mode u32
 * @return i32
 */
export function fs_libc_chmod(path: *u8, mode: u32): i32 {
  unsafe { return chmod(path, mode); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_mkdir`.
 * Implements `fs_libc_mkdir`.
 * @param path *u8
 * @param mode u32
 * @return i32
 */
export function fs_libc_mkdir(path: *u8, mode: u32): i32 {
  unsafe { return mkdir(path, mode); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_unlink`.
 * Implements `fs_libc_unlink`.
 * @param path *u8
 * @return i32
 */
export function fs_libc_unlink(path: *u8): i32 {
  unsafe { return xlang_fs_unlink(path); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_rmdir`.
 * Implements `fs_libc_rmdir`.
 * @param path *u8
 * @return i32
 */
export function fs_libc_rmdir(path: *u8): i32 {
  unsafe { return xlang_fs_rmdir(path); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_umask`.
 * Implements `fs_libc_umask`.
 * @param mask u32
 * @return u32
 */
export function fs_libc_umask(mask: u32): u32 {
  unsafe { return umask(mask); }
  return 0 as u32; // unreachable — typeck workaround
}
/** Exported function `fs_libc_readv`.
 * Read path helper `fs_libc_readv`.
 * @param fd i32
 * @param iov *Iovec
 * @param iovcnt i32
 * @return isize
 */
export function fs_libc_readv(fd: i32, iov: *Iovec, iovcnt: i32): isize {
  unsafe { return xlang_sys_readv(fd, iov as *u8, iovcnt); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_writev`.
 * Write path helper `fs_libc_writev`.
 * @param fd i32
 * @param iov *Iovec
 * @param iovcnt i32
 * @return isize
 */
export function fs_libc_writev(fd: i32, iov: *Iovec, iovcnt: i32): isize {
  unsafe { return xlang_sys_writev(fd, iov as *u8, iovcnt); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_opendir`.
 * Cap residual 9.1.10: POSIX (Linux and Darwin) → xlang_dir_opendir (no libc opendir).
 * @param name *u8
 * @return *u8
 */
export function fs_libc_opendir(name: *u8): *u8 {
  unsafe { return xlang_dir_opendir(name); }
  return 0 as *u8; // unreachable — typeck workaround
}
/** Exported function `fs_libc_readdir`.
 * Cap residual 9.1.10: POSIX (Linux and Darwin) → xlang_dir_readdir (no libc readdir).
 * @param dirp *u8
 * @return *u8
 */
export function fs_libc_readdir(dirp: *u8): *u8 {
  unsafe { return xlang_dir_readdir(dirp); }
  return 0 as *u8; // unreachable — typeck workaround
}
/** Exported function `fs_libc_closedir`.
 * Cap residual 9.1.10: POSIX (Linux and Darwin) → xlang_dir_closedir (no libc closedir).
 * @param dirp *u8
 * @return i32
 */
export function fs_libc_closedir(dirp: *u8): i32 {
  unsafe { return xlang_dir_closedir(dirp); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_malloc`.
 * Memory management helper `fs_libc_malloc`.
 * @param size usize
 * @return *u8
 */
export function fs_libc_malloc(size: usize): *u8 {
  unsafe { return malloc(size); }
  return 0 as *u8; // unreachable — typeck workaround
}
/** Exported function `fs_libc_free`.
 * Memory management helper `fs_libc_free`.
 * @param ptr *u8
 * @return void
 */
export function fs_libc_free(ptr: *u8): void {
  unsafe { free(ptr); }
}
/** Exported function `fs_libc_memcpy`.
 * Implements `fs_libc_memcpy`.
 * @param dst *u8
 * @param src *u8
 * @param n usize
 * @return *u8
 */
export function fs_libc_memcpy(dst: *u8, src: *u8, n: usize): *u8 {
  unsafe { return memcpy(dst, src, n); }
  return 0 as *u8; // unreachable — typeck workaround
}
/** Exported function `fs_libc_strlen`.
 * Implements `fs_libc_strlen`.
 * @param s *u8
 * @return usize
 */
export function fs_libc_strlen(s: *u8): usize {
  unsafe { return strlen(s); }
  return 0 as usize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_errno_location`.
 * Implements `fs_libc_errno_location`.
 * @return *i32
 */
#[cfg(target_os = "linux")]
export function fs_libc_errno_location(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __errno_location(); }
  return p;
}

/** Exported function `fs_libc_errno_location`.
 * Implements `fs_libc_errno_location`.
 * @return *i32
 */
#[cfg(target_os = "macos")]
export function fs_libc_errno_location(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __error(); }
  return p;
}
/** Exported function `fs_libc_fcntl`.
 * Implements `fs_libc_fcntl`.
 * @param fd i32
 * @param cmd i32
 * @param arg i32
 * @return i32
 */
export function fs_libc_fcntl(fd: i32, cmd: i32, arg: i32): i32 {
  unsafe { return fcntl(fd, cmd, arg); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_usleep`.
 * Implements `fs_libc_usleep`.
 * @param usec u32
 * @return i32
 */
export function fs_libc_usleep(usec: u32): i32 {
  unsafe { return usleep(usec); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_madvise`.
 * Implements `fs_libc_madvise`.
 * @param addr *u8
 * @param len usize
 * @param advice i32
 * @return i32
 */
export function fs_libc_madvise(addr: *u8, len: usize, advice: i32): i32 {
  unsafe { return madvise(addr, len, advice); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_poll`.
 * Implements `fs_libc_poll`.
 * @param fds *PollFd
 * @param nfds u64
 * @param timeout i32
 * @return i32
 */
export function fs_libc_poll(fds: *PollFd, nfds: u64, timeout: i32): i32 {
  unsafe { return xlang_sys_poll(fds as *u8, nfds as i32, timeout); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_posix_fadvise`.
 * Implements `fs_libc_posix_fadvise`.
 * @param fd i32
 * @param offset i64
 * @param len i64
 * @param advice i32
 * @return i32
 */
#[cfg(target_os = "linux")]
export function fs_libc_posix_fadvise(fd: i32, offset: i64, len: i64, advice: i32): i32 {
  unsafe { return posix_fadvise(fd, offset, len, advice); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_copy_file_range`.
 * Implements `fs_libc_copy_file_range`.
 * @param fd_in i32
 * @param off_in *i64
 * @param fd_out i32
 * @param off_out *i64
 * @param len usize
 * @param flags u32
 * @return isize
 */
#[cfg(target_os = "linux")]
export function fs_libc_copy_file_range(fd_in: i32, off_in: *i64, fd_out: i32, off_out: *i64, len: usize, flags: u32): isize {
  unsafe { return copy_file_range(fd_in, off_in, fd_out, off_out, len, flags); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_sendfile`.
 * Implements `fs_libc_sendfile`.
 * @param out_fd i32
 * @param in_fd i32
 * @param offset *i64
 * @param count usize
 * @return isize
 */
#[cfg(target_os = "linux")]
export function fs_libc_sendfile(out_fd: i32, in_fd: i32, offset: *i64, count: usize): isize {
  unsafe { return sendfile(out_fd, in_fd, offset, count); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_splice`.
 * Implements `fs_libc_splice`.
 * @param fd_in i32
 * @param off_in *i64
 * @param fd_out i32
 * @param off_out *i64
 * @param len usize
 * @param flags u32
 * @return isize
 */
#[cfg(target_os = "linux")]
export function fs_libc_splice(fd_in: i32, off_in: *i64, fd_out: i32, off_out: *i64, len: usize, flags: u32): isize {
  unsafe { return splice(fd_in, off_in, fd_out, off_out, len, flags); }
  return 0 as isize; // unreachable — typeck workaround
}
/** Exported function `fs_libc_pipe`.
 * Implements `fs_libc_pipe`.
 * @param pipefd *i32
 * @return i32
 */
#[cfg(target_os = "linux")]
export function fs_libc_pipe(pipefd: *i32): i32 {
  unsafe { return pipe(pipefd); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_sync_file_range`.
 * Implements `fs_libc_sync_file_range`.
 * @param fd i32
 * @param offset i64
 * @param nbytes i64
 * @param flags u32
 * @return i32
 */
#[cfg(target_os = "linux")]
export function fs_libc_sync_file_range(fd: i32, offset: i64, nbytes: i64, flags: u32): i32 {
  unsafe { return sync_file_range(fd, offset, nbytes, flags); }
  return 0; // unreachable — typeck workaround
}
/** Exported function `fs_libc_fallocate`.
 * Memory management helper `fs_libc_fallocate`.
 * @param fd i32
 * @param mode i32
 * @param offset i64
 * @param len i64
 * @return i32
 */
#[cfg(target_os = "linux")]
export function fs_libc_fallocate(fd: i32, mode: i32, offset: i64, len: i64): i32 {
  unsafe { return fallocate(fd, mode, offset, len); }
  return 0; // unreachable — typeck workaround
}
/**
 * Darwin sendfile(2) wrapper.
 * Purpose: keep a surface for 6-arg Darwin sendfile if callers need it later.
 * Parameters: in_fd/out_fd/offset/len/hdtr/flags match Darwin sendfile(2).
 * Returns: -1 (not wired). Product zero-copy uses fs_sendfile_c read/write fallback.
 * Why not call bare `sendfile`: codegen resolves that name to std.fs.sendfile (3-arg
 * product API) instead of the local extern "C" 6-arg Darwin sendfile → host-cc arity error.
 * PLATFORM: MACOS — Linux uses fs_libc_sendfile / fs_sendfile_c separately.
 */
#[cfg(target_os = "macos")]
export function fs_libc_sendfile_mac(in_fd: i32, out_fd: i32, offset: i64, len: *i64, hdtr: *u8, flags: i32): i32 {
  // Silence unused params; real Darwin sendfile needs a distinct link name (follow-up).
  if (in_fd < 0 || out_fd < 0) {
    return -1;
  }
  if (len == 0 as *i64) {
    return -1;
  }
  if (hdtr == 0 as *u8) {
    // flags/offset reserved for future wiring
    if (offset < 0 || flags < 0) {
      return -1;
    }
  }
  return -1;
}

/** Exported function `fs_errno_get`.
 * Implements `fs_errno_get`.
 * @return i32
 */
export function fs_errno_get(): i32 {
  let ep: *i32 = fs_libc_errno_location();
  return ep[0];
}

/** Exported function `fs_errno_set`.
 * Implements `fs_errno_set`.
 * @param v i32
 * @return void
 */
export function fs_errno_set(v: i32): void {
  let ep: *i32 = fs_libc_errno_location();
  ep[0] = v;
}

/**
 * Snapshot libc errno into module statics for fs_last_error_c.
 * Purpose: open/stat failure paths record errno without re-querying TLS later.
 * Returns: void. Side effect: sets fs_saved_last_error / fs_saved_last_error_set.
 * Placed with fs_errno_* so co-emit keeps the body (mid-file after export-const block
 * previously dropped this symbol while bare call sites remained → Ubuntu run-fs red).
 * PLATFORM: SHARED — uses fs_libc_errno_location (LINUX/MACOS inside that helper).
 */
export function fs_note_last_error_posix(): void {
  let ep: *i32 = fs_libc_errno_location();
  fs_saved_last_error = ep[0];
  fs_saved_last_error_set = 1;
}

#[cfg(target_os = "linux")]
extern "C" function posix_fadvise(fd: i32, offset: i64, len: i64, advice: i32): i32;
#[cfg(target_os = "linux")]
extern "C" function copy_file_range(fd_in: i32, off_in: *i64, fd_out: i32, off_out: *i64, len: usize, flags: u32): isize;
#[cfg(target_os = "linux")]
extern "C" function sendfile(out_fd: i32, in_fd: i32, offset: *i64, count: usize): isize;
#[cfg(target_os = "linux")]
extern "C" function splice(fd_in: i32, off_in: *i64, fd_out: i32, off_out: *i64, len: usize, flags: u32): isize;
#[cfg(target_os = "linux")]
extern "C" function pipe(pipefd: *i32): i32;
#[cfg(target_os = "linux")]
extern "C" function sync_file_range(fd: i32, offset: i64, nbytes: i64, flags: u32): i32;
#[cfg(target_os = "linux")]
extern "C" function fallocate(fd: i32, mode: i32, offset: i64, len: i64): i32;

#[cfg(target_os = "macos")]
extern "C" function sendfile(in_fd: i32, out_fd: i32, offset: i64, len: *i64, hdtr: *u8, flags: i32): i32;

/**
 * Byte offset of `d_name` within libc `struct dirent`.
 *
 * PLATFORM: LINUX — glibc/x86_64 dirent lays `d_type` at 18 and `d_name` at 19.
 * PLATFORM: MACOS|DARWIN — Darwin dirent lays `d_type` at 20 and `d_name` at 21.
 * Hardcoding Linux-only 19 made Darwin `fs_dir_read_c` skip past the real name
 * (STD-123 dirmeta_roundtrip returned 14). Keep in sync with seed preamble
 * `DIRENT_D_NAME_OFF` ifdef (__APPLE__→21, else→19) in rt_preamble.from_x.c.
 */
#[cfg(target_os = "linux")]
export const DIRENT_D_NAME_OFF: usize = 19;
#[cfg(target_os = "macos")]
export const DIRENT_D_NAME_OFF: usize = 21;

export const FS_IOV_BUF_MAX: i32 = 16;
export const O_RDONLY: i32 = 0;
export const O_WRONLY: i32 = 1;
export const O_RDWR: i32 = 2;
export const MAP_PRIVATE: i32 = 2;
export const MAP_SHARED: i32 = 1;
export const PROT_READ: i32 = 1;
export const PROT_WRITE: i32 = 2;
export const MAP_FAILED: i64 = -1;
export const S_IFMT: u32 = 61440;
export const S_IFDIR: u32 = 16384;
export const S_IFREG: u32 = 32768;

#[cfg(target_os = "linux")]
export const O_CREAT: i32 = 64;
#[cfg(target_os = "linux")]
export const O_TRUNC: i32 = 512;
#[cfg(target_os = "linux")]
export const O_APPEND: i32 = 1024;
#[cfg(target_os = "linux")]
export const O_DIRECT: i32 = 16384;
#[cfg(target_os = "linux")]
export const POSIX_FADV_SEQUENTIAL: i32 = 2;
#[cfg(target_os = "linux")]
export const POSIX_FADV_WILLNEED: i32 = 3;
#[cfg(target_os = "linux")]
export const SYNC_FILE_RANGE_WRITE: u32 = 2;
#[cfg(target_os = "linux")]
export const SPLICE_F_MOVE: u32 = 1;
#[cfg(target_os = "linux")]
export const MADV_SEQUENTIAL: i32 = 23;
#[cfg(target_os = "linux")]
export const MADV_HUGEPAGE: i32 = 14;
/* See implementation. */

#[cfg(target_os = "macos")]
export const O_CREAT: i32 = 512;
#[cfg(target_os = "macos")]
export const O_TRUNC: i32 = 1024;
#[cfg(target_os = "macos")]
export const O_APPEND: i32 = 8;
#[cfg(target_os = "macos")]
export const F_NOCACHE: i32 = 48;

/**
 * See implementation.
 */
export function fs_fill_stat_from_st(st: *PosixStatBuf, out: *FsStatOut): void {
  let st_mode: u32 = st[0].st_mode as u32;
  out[0].size = st[0].st_size;
  out[0].mode = (st_mode as u32) & 4095;
  out[0].is_dir = 0;
  out[0].is_file = 0;
  out[0].mtime_sec = st[0].st_mtime;
  if ((st_mode & S_IFMT) == S_IFDIR) {
    out[0].is_dir = 1;
  } else if ((st_mode & S_IFMT) == S_IFREG) {
    out[0].is_file = 1;
  }
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 */
export function fs_mmap_ro_c(path: *u8, out_size: *usize): *u8 {
  if (path == 0 || out_size == 0) {
    return 0 as *u8;
  }
  let fd: i32 = fs_libc_open(path, O_RDONLY, 0);
  if (fd < 0) {
    return 0 as *u8;
  }
  let st: PosixStatBuf;
  if (fs_libc_fstat(fd, &st) != 0) {
    fs_libc_close(fd);
    return 0 as *u8;
  }
  let len: usize = st.st_size as usize;
  if (len == 0) {
    fs_libc_close(fd);
    return 0 as *u8;
  }
  let p: *u8 = fs_libc_mmap(0 as *u8, len, PROT_READ, MAP_PRIVATE, fd, 0 as i64);
  fs_libc_close(fd);
  let p_i: i64 = p as i64;
  if (p_i == MAP_FAILED) {
    return 0 as *u8;
  }
  fs_libc_madvise(p, len, 1);
  out_size[0] = len;
  return p;
}

/**
 * See implementation.
 */
export function fs_mmap_rw_c(path: *u8, out_size: *usize): *u8 {
  if (path == 0 || out_size == 0) {
    return 0 as *u8;
  }
  let fd: i32 = fs_libc_open(path, O_RDWR, 0);
  if (fd < 0) {
    return 0 as *u8;
  }
  let st: PosixStatBuf;
  if (fs_libc_fstat(fd, &st) != 0) {
    fs_libc_close(fd);
    return 0 as *u8;
  }
  let len: usize = st.st_size as usize;
  if (len == 0) {
    fs_libc_close(fd);
    return 0 as *u8;
  }
  let p: *u8 = fs_libc_mmap(0 as *u8, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 as i64);
  fs_libc_close(fd);
  let p_i: i64 = p as i64;
  if (p_i == MAP_FAILED) {
    return 0 as *u8;
  }
  out_size[0] = len;
  return p;
}

/** Exported function `fs_munmap_c`.
 * Implements `fs_munmap_c`.
 * @param ptr *u8
 * @param size usize
 * @return i32
 */
export function fs_munmap_c(ptr: *u8, size: usize): i32 {
  if (ptr == 0) {
    return 0;
  }
  if (fs_libc_munmap(ptr, size) == 0) {
    return 0;
  }
  return -1;
}

/** Exported function `fs_open_read_direct_c`.
 * Read path helper `fs_open_read_direct_c`.
 * @param path *u8
 * @return i32
 */
export function fs_open_read_direct_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  let fd: i32 = fs_libc_open(path, O_RDONLY, 0);
  if (fd < 0) {
    return -1;
  }
  return fd;
}

/** Exported function `fs_direct_align_c`.
 * Implements `fs_direct_align_c`.
 * @return u64
 */
export function fs_direct_align_c(): u64 {
  return 4096 as u64;
}

/** Exported function `fs_fadvise_sequential_c`.
 * Implements `fs_fadvise_sequential_c`.
 * @param fd i32
 * @return i32
 */
export function fs_fadvise_sequential_c(fd: i32): i32 {
  if (fd < 0) {
    return -1;
  }
  return 0;
}

/** Exported function `fs_fadvise_willneed_c`.
 * Implements `fs_fadvise_willneed_c`.
 * @param fd i32
 * @param offset i64
 * @param len usize
 * @return i32
 */
export function fs_fadvise_willneed_c(fd: i32, offset: i64, len: usize): i32 {
  if (fd < 0 || offset < 0 || len == 0) {
    return -1;
  }
  return 0;
}

/** Exported function `fs_copy_rw_fallback`.
 * Implements `fs_copy_rw_fallback`.
 * @param fd_in i32
 * @param fd_out i32
 * @param len usize
 * @return i64
 */
export function fs_copy_rw_fallback(fd_in: i32, fd_out: i32, len: usize): i64 {
  let buf: u8[262144];
  let copied: usize = 0;
  while (copied < len) {
    let chunk: usize = len - copied;
    if (chunk > 262144) {
      chunk = 262144;
    }
    let nr: isize = fs_libc_read(fd_in, &buf[0], chunk);
    if (nr <= 0) {
      break;
    }
    let nw: isize = fs_libc_write(fd_out, &buf[0], nr as usize);
    if (nw != nr) {
      return -1;
    }
    copied = copied + (nr as usize);
    if ((nr) < chunk) {
      break;
    }
  }
  return copied as i64;
}

/** Exported function `fs_copy_file_range_c`.
 * Implements `fs_copy_file_range_c`.
 * @param fd_in i32
 * @param fd_out i32
 * @param len usize
 * @return i64
 */
export function fs_copy_file_range_c(fd_in: i32, fd_out: i32, len: usize): i64 {
  return fs_copy_rw_fallback(fd_in, fd_out, len);
}

/** Exported function `fs_readv2_c`.
 * Read path helper `fs_readv2_c`.
 * @param fd i32
 * @param p0 *u8
 * @param l0 usize
 * @param p1 *u8
 * @param l1 usize
 * @return i64
 */
export function fs_readv2_c(fd: i32, p0: *u8, l0: usize, p1: *u8, l1: usize): i64 {
  let iov: Iovec[2] = [{ base: p0, length: l0 }, { base: p1, length: l1 }];
  let n: isize = fs_libc_readv(fd, &iov[0], 2);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_writev2_c`.
 * Write path helper `fs_writev2_c`.
 * @param fd i32
 * @param p0 *u8
 * @param l0 usize
 * @param p1 *u8
 * @param l1 usize
 * @return i64
 */
export function fs_writev2_c(fd: i32, p0: *u8, l0: usize, p1: *u8, l1: usize): i64 {
  let iov: Iovec[2] = [{ base: p0, length: l0 }, { base: p1, length: l1 }];
  let n: isize = fs_libc_writev(fd, &iov[0], 2);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_sendfile_c`.
 * Implements `fs_sendfile_c`.
 * @param out_fd i32
 * @param in_fd i32
 * @param count usize
 * @return i64
 */
export function fs_sendfile_c(out_fd: i32, in_fd: i32, count: usize): i64 {
  return fs_copy_rw_fallback(in_fd, out_fd, count);
}

/** Exported function `fs_pipe_splice_rw_fallback`.
 * Implements `fs_pipe_splice_rw_fallback`.
 * @param fd_in i32
 * @param fd_out i32
 * @param len usize
 * @return i64
 */
export function fs_pipe_splice_rw_fallback(fd_in: i32, fd_out: i32, len: usize): i64 {
  if (len == 0) {
    return 0;
  }
  return fs_copy_rw_fallback(fd_in, fd_out, len);
}

/** Exported function `fs_pipe_splice_c`.
 * Implements `fs_pipe_splice_c`.
 * @param fd_in i32
 * @param fd_out i32
 * @param len usize
 * @return i64
 */
export function fs_pipe_splice_c(fd_in: i32, fd_out: i32, len: usize): i64 {
  return fs_pipe_splice_rw_fallback(fd_in, fd_out, len);
}

/** Exported function `fs_sync_range_c`.
 * Implements `fs_sync_range_c`.
 * @param fd i32
 * @param offset i64
 * @param len usize
 * @return i32
 */
export function fs_sync_range_c(fd: i32, offset: i64, len: usize): i32 {
  if (fd < 0 || offset < 0) {
    return -1;
  }
  if (len == 0) {
    return 0;
  }
  return 0;
}

/** Exported function `fs_sync_c`.
 * Implements `fs_sync_c`.
 * @param fd i32
 * @return i32
 */
export function fs_sync_c(fd: i32): i32 {
  if (fs_libc_fsync(fd) == 0) {
    return 0;
  }
  return -1;
}

/** Exported function `fs_fallocate_c`.
 * Memory management helper `fs_fallocate_c`.
 * @param fd i32
 * @param offset i64
 * @param len i64
 * @return i32
 */
export function fs_fallocate_c(fd: i32, offset: i64, len: i64): i32 {
  if (fd < 0 || offset < 0 || len < 0) {
    return -1;
  }
  return 0;
}

/** Exported function `fs_open_read_c`.
 * Read path helper `fs_open_read_c`.
 * @param path *u8
 * @return i32
 */
export function fs_open_read_c(path: *u8): i32 {
  if (path == 0) {
    fs_saved_last_error = 22;
    fs_saved_last_error_set = 1;
    return -1;
  }
  let fd: i32 = fs_libc_open(path, O_RDONLY, 0);
  if (fd < 0) {
    fs_note_last_error_posix();
    return -1;
  }
  return fd;
}

/** Exported function `fs_open_write_c`.
 * Write path helper `fs_open_write_c`.
 * @param path *u8
 * @return i32
 */
export function fs_open_write_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  let old: u32 = fs_libc_umask(0);
  let fd: i32 = fs_libc_open(path, O_WRONLY | O_CREAT | O_TRUNC, 420);
  fs_libc_umask(old);
  if (fd >= 0) {
    fs_libc_fchmod(fd, 420);
    return fd;
  }
  return -1;
}

/** Exported function `fs_open_append_c`.
 * Implements `fs_open_append_c`.
 * @param path *u8
 * @return i32
 */
export function fs_open_append_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  return fs_libc_open(path, O_WRONLY | O_APPEND | O_CREAT, 420);
}

/** Exported function `fs_open_create_c`.
 * Implements `fs_open_create_c`.
 * @param path *u8
 * @return i32
 */
export function fs_open_create_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  return fs_libc_open(path, O_WRONLY | O_CREAT, 420);
}

/** Exported function `fs_last_error_c`.
 * Implements `fs_last_error_c`.
 * @return i32
 */
export function fs_last_error_c(): i32 {
  if (fs_saved_last_error_set != 0) {
    return fs_saved_last_error;
  }
  return fs_errno_get();
}

/** Exported function `fs_posix_read_c`.
 * Read path helper `fs_posix_read_c`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @return i64
 */
export function fs_posix_read_c(fd: i32, buf: *u8, count: usize): i64 {
  return fs_libc_read(fd, buf, count) as i64;
}

/** Exported function `fs_posix_write_c`.
 * Write path helper `fs_posix_write_c`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @return i64
 */
export function fs_posix_write_c(fd: i32, buf: *u8, count: usize): i64 {
  return fs_libc_write(fd, buf, count) as i64;
}

/** Exported function `fs_posix_close_c`.
 * Implements `fs_posix_close_c`.
 * @param fd i32
 * @return i32
 */
export function fs_posix_close_c(fd: i32): i32 {
  return fs_libc_close(fd);
}

/** Exported function `fs_posix_pread_c`.
 * Read path helper `fs_posix_pread_c`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @param offset i64
 * @return i64
 */
export function fs_posix_pread_c(fd: i32, buf: *u8, count: usize, offset: i64): i64 {
  let n: isize = fs_libc_pread(fd, buf, count, offset);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_posix_pwrite_c`.
 * Write path helper `fs_posix_pwrite_c`.
 * @param fd i32
 * @param buf *u8
 * @param count usize
 * @param offset i64
 * @return i64
 */
export function fs_posix_pwrite_c(fd: i32, buf: *u8, count: usize, offset: i64): i64 {
  let n: isize = fs_libc_pwrite(fd, buf, count, offset);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_readv4_c`.
 * Read path helper `fs_readv4_c`.
 * @param fd i32
 * @param p0 *u8
 * @param l0 usize
 * @param p1 *u8
 * @param l1 usize
 * @param p2 *u8
 * @param l2 usize
 * @param p3 *u8
 * @param l3 usize
 * @return i64
 */
export function fs_readv4_c(fd: i32, p0: *u8, l0: usize, p1: *u8, l1: usize, p2: *u8, l2: usize, p3: *u8, l3: usize): i64 {
  let iov: Iovec[4] = [
    { base: p0, length: l0 },
    { base: p1, length: l1 },
    { base: p2, length: l2 },
    { base: p3, length: l3 }
  ];
  let n: isize = fs_libc_readv(fd, &iov[0], 4);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_writev4_c`.
 * Write path helper `fs_writev4_c`.
 * @param fd i32
 * @param p0 *u8
 * @param l0 usize
 * @param p1 *u8
 * @param l1 usize
 * @param p2 *u8
 * @param l2 usize
 * @param p3 *u8
 * @param l3 usize
 * @return i64
 */
export function fs_writev4_c(fd: i32, p0: *u8, l0: usize, p1: *u8, l1: usize, p2: *u8, l2: usize, p3: *u8, l3: usize): i64 {
  let iov: Iovec[4] = [
    { base: p0, length: l0 },
    { base: p1, length: l1 },
    { base: p2, length: l2 },
    { base: p3, length: l3 }
  ];
  let n: isize = fs_libc_writev(fd, &iov[0], 4);
  return n >= 0 ? (n as i64) : (-1 as i64);
}

/** Exported function `fs_readv_buf_c`.
 * Read path helper `fs_readv_buf_c`.
 * @param fd i32
 * @param bufs *u8
 * @param n i32
 * @return i64
 */
export function fs_readv_buf_c(fd: i32, bufs: *u8, n: i32): i64 {
  if (n <= 0 || n > FS_IOV_BUF_MAX || bufs == 0) {
    return -1;
  }
  let b: *FsIovecBuf = bufs as *FsIovecBuf;
  let iov: Iovec[16];
  let i: i32 = 0;
  while (i < n) {
    iov[i].base = b[i].ptr;
    iov[i].length = b[i].length;
    i = i + 1;
  }
  let r: isize = fs_libc_readv(fd, &iov[0], n);
  return r >= 0 ? (r as i64) : (-1 as i64);
}

/** Exported function `fs_writev_buf_c`.
 * Write path helper `fs_writev_buf_c`.
 * @param fd i32
 * @param bufs *u8
 * @param n i32
 * @return i64
 */
export function fs_writev_buf_c(fd: i32, bufs: *u8, n: i32): i64 {
  if (n <= 0 || n > FS_IOV_BUF_MAX || bufs == 0) {
    return -1;
  }
  let b: *FsIovecBuf = bufs as *FsIovecBuf;
  let iov: Iovec[16];
  let i: i32 = 0;
  while (i < n) {
    iov[i].base = b[i].ptr;
    iov[i].length = b[i].length;
    i = i + 1;
  }
  let r: isize = fs_libc_writev(fd, &iov[0], n);
  return r >= 0 ? (r as i64) : (-1 as i64);
}

/** Exported function `fs_stat_c`.
 * Implements `fs_stat_c`.
 * @param path *u8
 * @param out *u8
 * @return i32
 */
export function fs_stat_c(path: *u8, out: *u8): i32 {
  let st: PosixStatBuf;
  let o: *FsStatOut = out as *FsStatOut;
  if (path == 0 || out == 0) {
    return -1;
  }
  if (fs_libc_stat(path, &st) != 0) {
    fs_note_last_error_posix();
    return -1;
  }
  let st_mode: u32 = st.st_mode as u32;
  /* See implementation. */
  o[0].size = st.st_size;
  o[0].mode = st_mode & 4095;
  o[0].is_dir = 0;
  o[0].is_file = 0;
  o[0].mtime_sec = st.st_mtime;
  if ((st_mode & S_IFMT) == S_IFDIR) {
    o[0].is_dir = 1;
  } else if ((st_mode & S_IFMT) == S_IFREG) {
    o[0].is_file = 1;
  }
  return 0;
}

/** Exported function `fs_chmod_c`.
 * Implements `fs_chmod_c`.
 * @param path *u8
 * @param mode u32
 * @return i32
 */
export function fs_chmod_c(path: *u8, mode: u32): i32 {
  if (path == 0) {
    return -1;
  }
  if (fs_libc_chmod(path, mode) != 0) {
    fs_note_last_error_posix();
    return -1;
  }
  return 0;
}

/** mkdir。 */
export function fs_mkdir_c(path: *u8, mode: u32): i32 {
  if (path == 0) {
    return -1;
  }
  if (fs_libc_mkdir(path, mode) != 0) {
    fs_note_last_error_posix();
    return -1;
  }
  return 0;
}

/** Exported function `fs_unlink_c`.
 * Implements `fs_unlink_c`.
 * @param path *u8
 * @return i32
 */
export function fs_unlink_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  if (fs_libc_unlink(path) != 0) {
    fs_note_last_error_posix();
    return -1;
  }
  return 0;
}

/** Exported function `fs_rmdir_c`.
 * Implements `fs_rmdir_c`.
 * @param path *u8
 * @return i32
 */
export function fs_rmdir_c(path: *u8): i32 {
  if (path == 0) {
    return -1;
  }
  if (fs_libc_rmdir(path) != 0) {
    fs_note_last_error_posix();
    return -1;
  }
  return 0;
}

/** Exported function `fs_dir_open_c`.
 * Implements `fs_dir_open_c`.
 * @param path *u8
 * @return i64
 */
export function fs_dir_open_c(path: *u8): i64 {
  let d: *u8;
  let h: *FsDirHandlePosix;
  if (path == 0) {
    return -1;
  }
  d = fs_libc_opendir(path);
  if (d == 0) {
    fs_note_last_error_posix();
    return -1;
  }
  h = fs_libc_malloc(8) as *FsDirHandlePosix;
  if (h == 0) {
    fs_libc_closedir(d);
    return -1;
  }
  let dir_ptr: *u8 = d;
  h[0].dir = dir_ptr;
  return h as i64;
}

/**
 * Read the next directory entry into `name_out`.
 *
 * Skips `.` / `..`. Uses `DIRENT_D_NAME_OFF` (PLATFORM LINUX=19 / MACOS=21) to
 * locate `d_name` inside the libc `struct dirent` returned by `readdir`.
 *
 * @param handle Directory handle from `fs_dir_open_c` (negative = invalid).
 * @param name_out Caller buffer for the NUL-terminated entry name.
 * @param name_cap Capacity of `name_out` in bytes (must fit name + NUL).
 * @param is_dir_out Optional; currently always written 0 (d_type not wired).
 * @return 1 on entry, 0 at end-of-dir, -1 on error (errno noted).
 */
export function fs_dir_read_c(handle: i64, name_out: *u8, name_cap: i32, is_dir_out: *i32): i32 {
  let h: *FsDirHandlePosix;
  let de: *u8;
  let name: *u8;
  let nlen: usize;
  if (handle < 0 || name_out == 0 || name_cap <= 0) {
    return -1;
  }
  h = handle as *FsDirHandlePosix;
  while (1 != 0) {
    fs_errno_set(0);
    let h_dir: *u8 = h[0].dir;
    de = fs_libc_readdir(h_dir);
    if (de == 0) {
      if (fs_errno_get() != 0) {
        fs_note_last_error_posix();
        return -1;
      }
      return 0;
    }
    // PLATFORM: SHARED — offset is cfg'd (linux 19 / macos 21); see DIRENT_D_NAME_OFF.
    name = (de as *u8) + DIRENT_D_NAME_OFF;
    if (name[0] == 46 && (name[1] == 0 || (name[1] == 46 && name[2] == 0))) {
      continue;
    }
    nlen = fs_libc_strlen(name);
    let need_cap: i32 = (nlen + 1) as i32;
    if (need_cap > name_cap) {
      return -1;
    }
    fs_libc_memcpy(name_out, name, nlen);
    name_out[nlen] = 0;
    if (is_dir_out != 0) {
      is_dir_out[0] = 0;
    }
    return 1;
  }
  return 0;
}

/** Exported function `fs_dir_close_c`.
 * Implements `fs_dir_close_c`.
 * @param handle i64
 * @return i32
 */
export function fs_dir_close_c(handle: i64): i32 {
  let h: *FsDirHandlePosix;
  if (handle < 0) {
    return -1;
  }
  h = handle as *FsDirHandlePosix;
  let h_dir: *u8 = h[0].dir;
  fs_libc_closedir(h_dir);
  fs_libc_free(h as *u8);
  return 0;
}

/** Exported function `fs_posix_module_anchor`.
 * Implements `fs_posix_module_anchor`.
 * @return i32
 */
export function fs_posix_module_anchor(): i32 {
  return 0;
}
