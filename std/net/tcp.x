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
// net_accept_c / net_accept_many_c / net_connect_many_c。
//
// See implementation.
//
// See implementation.
// See implementation.

export const AF_INET: i32 = 2;
export const SOCK_STREAM: i32 = 1;
export const IPPROTO_TCP: i32 = 6;
export const SOL_SOCKET: i32 = 1;
export const SO_REUSEADDR: i32 = 2;
export const SO_ERROR: i32 = 4;
export const O_NONBLOCK: i32 = 2048;
/* See implementation. */

#[cfg(target_os = "linux")]
export const ERR_INPROGRESS: i32 = 115;

#[cfg(target_os = "macos")]
export const ERR_INPROGRESS: i32 = 36;

/* See implementation. */
allow(padding) struct SockAddrIn {
  sin_family: u16;
  sin_port: u16;
  sin_addr: u32;
}

#[cfg(not(target_os = "windows"))]
allow(padding) struct PollFd { fd: i32; events: i16; revents: i16; }

/* Cap residual 9.1.7: SHARED product face via sock_fast Cap bodies (not libc socket/connect/accept). */
extern function xlang_sys_socket(domain: i32, sock_type: i32, protocol: i32): i32;
extern function xlang_sys_connect(sockfd: i32, addr: *u8, addrlen: i32): i32;
extern function xlang_sys_accept(sockfd: i32, addr: *u8, addrlen: *u32): i32;
extern "C" function setsockopt(fd: i32, level: i32, optname: i32, optval: *i32, optlen: u32): i32;
extern "C" function getsockopt(fd: i32, level: i32, optname: i32, optval: *i32, optlen: *u32): i32;
extern "C" function htonl(hostlong: u32): u32;
extern "C" function htons(hostshort: u16): u16;

extern function net_set_blocking_c(fd: i32, blocking: i32): i32;

extern function net_close_socket_c(fd: i32): i32;

#[cfg(not(target_os = "windows"))]
extern "C" function fcntl(fd: i32, cmd: i32, arg: i32): i32;

/* See implementation. */
#[cfg(not(target_os = "windows"))]
extern "C" function xlang_sys_poll(fds: *u8, nfds: i32, timeout: i32): i32;

#[cfg(target_os = "linux")]
extern "C" function __errno_location(): *i32;

#[cfg(target_os = "macos")]
extern "C" function __error(): *i32;

/** See implementation for details. */
#[cfg(target_os = "linux")]
export function net_tcp_errno_ptr(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __errno_location(); }
  return p;
}

/** Exported function `net_tcp_errno_ptr`.
 * Implements `net_tcp_errno_ptr`.
 * @return *i32
 */
#[cfg(target_os = "macos")]
export function net_tcp_errno_ptr(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __error(); }
  return p;
}

#[cfg(target_os = "linux")]
extern function io_uring_connect(addr_u32: u32, port_u32: u32, timeout_ms: u32): i32;

#[cfg(target_os = "linux")]
extern function io_uring_accept(listener_fd: i32, timeout_ms: u32): i32;

#[cfg(target_os = "linux")]
extern function io_uring_accept_many(listener_fd: i32, out_fds: *i32, n: i32, timeout_ms: u32): i32;

#[cfg(target_os = "linux")]
extern function io_uring_connect_many(addr_u32: u32, port_u32: u32, out_fds: *i32, n: i32, timeout_ms: u32): i32;

#[cfg(target_os = "linux")]
extern function io_uring_prefetch_fd(fd: i32): i32;

#[cfg(target_os = "windows")]
extern "C" function WSAStartup(wVersionRequested: u16, lpWSAData: *u8): i32;

#[cfg(target_os = "windows")]
extern "C" function ioctlsocket(fd: i32, cmd: i32, arg: *u32): i32;

#[cfg(target_os = "windows")]
extern "C" function closesocket(fd: i32): i32;

#[cfg(target_os = "windows")]
let net_tcp_wsa_done: i32 = 0;

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_ensure_wsa_c(): i32 {
  if (net_tcp_wsa_done != 0) {
    return 0;
  }
  unsafe { if (WSAStartup(514 as u16, 0 as *u8) != 0) {
    return -1;
  } }
  net_tcp_wsa_done = 1;
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_maybe_wsa_fail_c(): i32 {
  if (net_tcp_ensure_wsa_c() != 0) {
    return -1;
  }
  return 0;
}

/** Exported function `net_tcp_maybe_wsa_fail_c`.
 * Implements `net_tcp_maybe_wsa_fail_c`.
 * @return i32
 */
#[cfg(not(target_os = "windows"))]
export function net_tcp_maybe_wsa_fail_c(): i32 {
  return 0;
}

/**
 * See implementation.
 */
export function net_tcp_sin_buf_ptr_c(p: *u8): *u8 {
  return p;
}

/* See implementation. */
extern function net_tcp_set_addr_port_buf_c(sin: *u8, addr_u32: u32, port_u32: u32): void;

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_tcp_set_nonblock_c(fd: i32): i32 {
  let flags: i32 = 0;
  unsafe { flags = fcntl(fd, 3, 0); }
  if (flags < 0) {
    return -1;
  }
  unsafe { if (fcntl(fd, 4, flags | O_NONBLOCK) == 0) {
    return 0;
  } }
  return -1;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_set_nonblock_c(fd: i32): i32 {
  let one: u32 = 1;
  unsafe { if (ioctlsocket(fd, (0x80000000 | 0x40000000) as i32, &one) == 0) {
    return 0;
  } }
  return -1;
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_tcp_poll_writable_c(fd: i32, timeout_ms: u32): i32 {
  let pfd_mem: u8[8] = [];
  let pfd_ptr: *u8 = net_tcp_sin_buf_ptr_c(&pfd_mem[0]);
  let p_fd: *i32 = (pfd_ptr + 0) as *i32;
  let p_events: *i16 = (pfd_ptr + 4) as *i16;
  let p_revents: *i16 = (pfd_ptr + 6) as *i16;
  let to: i32 = (0 - 1);
  let n: i32 = 0;
  p_fd[0] = fd;
  p_events[0] = 4 as i16; /* POLLOUT */
  p_revents[0] = 0 as i16;
  if (timeout_ms != 0) {
    to = timeout_ms as i32;
  }
  unsafe { n = xlang_sys_poll(pfd_ptr, 1, to); }
  if (n <= 0 || (p_revents[0] & (24 as i16)) != 0) { /* POLLERR|POLLHUP */
    return -1;
  }
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_poll_writable_c(fd: i32, timeout_ms: u32): i32 {
  return 0;
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_tcp_poll_readable_c(fd: i32, timeout_ms: u32): i32 {
  let pfd_mem: u8[8] = [];
  let pfd_ptr: *u8 = net_tcp_sin_buf_ptr_c(&pfd_mem[0]);
  let p_fd: *i32 = (pfd_ptr + 0) as *i32;
  let p_events: *i16 = (pfd_ptr + 4) as *i16;
  let p_revents: *i16 = (pfd_ptr + 6) as *i16;
  let to: i32 = (0 - 1);
  let n: i32 = 0;
  p_fd[0] = fd;
  p_events[0] = 1 as i16; /* POLLIN */
  p_revents[0] = 0 as i16;
  if (timeout_ms != 0) {
    to = timeout_ms as i32;
  }
  unsafe { n = xlang_sys_poll(pfd_ptr, 1, to); }
  if (n <= 0 || (p_revents[0] & (24 as i16)) != 0) { /* POLLERR|POLLHUP */
    return -1;
  }
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_poll_readable_c(fd: i32, timeout_ms: u32): i32 {
  return 0;
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_tcp_connect_not_inprogress_c(): i32 {
  let ep: *i32 = 0 as *i32;
  ep = net_tcp_errno_ptr();
  if (ep[0] != ERR_INPROGRESS) {
    return 1;
  }
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_tcp_connect_not_inprogress_c(): i32 {
  return 0;
}

/**
 * Linux：io_uring prefetch fd。
 */
#[cfg(target_os = "linux")]
export function net_tcp_prefetch_fd_c(fd: i32): void {
  if (fd >= 0) {
    unsafe { io_uring_prefetch_fd(fd); }
  }
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "linux"))]
export function net_tcp_prefetch_fd_c(fd: i32): void {
}

/**
 * See implementation.
 */
export function net_tcp_connect_finish_c(fd: i32, timeout_ms: u32): i32 {
  let err: i32 = 0;
  let errlen: u32 = 4;
  if (net_tcp_poll_writable_c(fd, timeout_ms) != 0) {
    unsafe { net_close_socket_c(fd); }
    return -1;
  }
  unsafe { if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) != 0 || err != 0) {
    net_close_socket_c(fd);
    return -1;
  } }
  return fd;
}

/**
 * See implementation.
 */
#[cfg(target_os = "linux")]
#[no_mangle]
export function net_tcp_connect_c(addr_u32: u32, port_u32: u32, timeout_ms: u32): i32 {
  let fd: i32 = 0;
  unsafe { fd = io_uring_connect(addr_u32, port_u32, timeout_ms); }
  if (fd >= 0) {
    net_tcp_prefetch_fd_c(fd);
  }
  return fd;
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "linux"))]
#[no_mangle]
export function net_tcp_connect_c(addr_u32: u32, port_u32: u32, timeout_ms: u32): i32 {
  let sin_mem: u8[16] = [];
  let sin_ptr: *u8 = net_tcp_sin_buf_ptr_c(&sin_mem[0]);
  let fd: i32 = 0;
  if (net_tcp_maybe_wsa_fail_c() != 0) {
    return -1;
  }
  unsafe { net_tcp_set_addr_port_buf_c(sin_ptr, addr_u32, port_u32); }
  unsafe { fd = xlang_sys_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); }
  if (fd < 0) {
    return -1;
  }
  if (net_tcp_set_nonblock_c(fd) != 0) {
    unsafe { net_close_socket_c(fd); }
    return -1;
  }
  unsafe { if (xlang_sys_connect(fd, sin_ptr, 16) != 0) {
    if (net_tcp_connect_not_inprogress_c() != 0) {
      net_close_socket_c(fd);
      return -1;
    }
    return net_tcp_connect_finish_c(fd, timeout_ms);
  } }
  return fd;
}

/**
 * Blocking TCP connect (Linux): Cap socket/connect via xlang_sys_* when
 * timeout_ms==0; otherwise net_tcp_connect_c (io_uring).
 * PLATFORM: LINUX Cap residual 9.1.7
 */
#[cfg(target_os = "linux")]
#[no_mangle]
export function net_tcp_connect_blocking_c(addr_u32: u32, port_u32: u32, timeout_ms: u32): i32 {
  let sin_mem: u8[16] = [];
  let sin_ptr: *u8 = net_tcp_sin_buf_ptr_c(&sin_mem[0]);
  let fd: i32 = 0;
  if (net_tcp_maybe_wsa_fail_c() != 0) {
    return -1;
  }
  unsafe { net_tcp_set_addr_port_buf_c(sin_ptr, addr_u32, port_u32); }
  if (timeout_ms != 0) {
    fd = net_tcp_connect_c(addr_u32, port_u32, timeout_ms);
    if (fd < 0) {
      return -1;
    }
    let set_blk_rc: i32 = 0;
    unsafe { set_blk_rc = net_set_blocking_c(fd, 1); }
    if (set_blk_rc != 0) {
      unsafe { net_close_socket_c(fd); }
      return -1;
    }
    net_tcp_prefetch_fd_c(fd);
    return fd;
  }
  unsafe { fd = xlang_sys_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); }
  if (fd < 0) {
    return -1;
  }
  unsafe { if (xlang_sys_connect(fd, sin_ptr, 16) != 0) {
    net_close_socket_c(fd);
    return -1;
  } }
  net_tcp_prefetch_fd_c(fd);
  return fd;
}

/**
 * Blocking TCP connect (non-Linux): libc/Winsock socket/connect when timeout_ms==0.
 * PLATFORM: MACOS|WINDOWS|other
 */
#[cfg(not(target_os = "linux"))]
#[no_mangle]
export function net_tcp_connect_blocking_c(addr_u32: u32, port_u32: u32, timeout_ms: u32): i32 {
  let sin_mem: u8[16] = [];
  let sin_ptr: *u8 = net_tcp_sin_buf_ptr_c(&sin_mem[0]);
  let fd: i32 = 0;
  if (net_tcp_maybe_wsa_fail_c() != 0) {
    return -1;
  }
  unsafe { net_tcp_set_addr_port_buf_c(sin_ptr, addr_u32, port_u32); }
  if (timeout_ms != 0) {
    fd = net_tcp_connect_c(addr_u32, port_u32, timeout_ms);
    if (fd < 0) {
      return -1;
    }
    let set_blk_rc: i32 = 0;
    unsafe { set_blk_rc = net_set_blocking_c(fd, 1); }
    if (set_blk_rc != 0) {
      unsafe { net_close_socket_c(fd); }
      return -1;
    }
    net_tcp_prefetch_fd_c(fd);
    return fd;
  }
  unsafe { fd = xlang_sys_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); }
  if (fd < 0) {
    return -1;
  }
  unsafe { if (xlang_sys_connect(fd, sin_ptr, 16) != 0) {
    net_close_socket_c(fd);
    return -1;
  } }
  net_tcp_prefetch_fd_c(fd);
  return fd;
}

/**
 * See implementation.
 * See implementation.
 */
extern function net_tcp_listen_c(addr_u32: u32, port_u32: u32): i32;

/**
 * See implementation.
 */
#[cfg(target_os = "linux")]
#[no_mangle]
export function net_accept_c(listener_fd: i32, timeout_ms: u32): i32 {
  unsafe { return io_uring_accept(listener_fd, timeout_ms); }
  return 0; // unreachable — typeck workaround
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "linux"))]
#[no_mangle]
export function net_accept_c(listener_fd: i32, timeout_ms: u32): i32 {
  let peer_mem: u8[16] = [];
  let peer_ptr: *u8 = net_tcp_sin_buf_ptr_c(&peer_mem[0]);
  let peer_len: u32 = 16;
  let fd: i32 = 0;
  if (timeout_ms != 0) {
    if (net_tcp_poll_readable_c(listener_fd, timeout_ms) != 0) {
      return -1;
    }
  }
  unsafe { fd = xlang_sys_accept(listener_fd, peer_ptr, &peer_len); }
  if (fd < 0) {
    return -1;
  }
  if (net_tcp_set_nonblock_c(fd) != 0) {
    unsafe { net_close_socket_c(fd); }
    return -1;
  }
  return fd;
}

/**
 * See implementation.
 */
#[cfg(target_os = "linux")]
#[no_mangle]
export function net_accept_many_c(listener_fd: i32, out_fds: *i32, n: i32, timeout_ms: u32): i32 {
  if (n <= 0 || out_fds == 0) {
    return 0;
  }
  unsafe { return io_uring_accept_many(listener_fd, out_fds, n, timeout_ms); }
  return 0; // unreachable — typeck workaround
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "linux"))]
#[no_mangle]
export function net_accept_many_c(listener_fd: i32, out_fds: *i32, n: i32, timeout_ms: u32): i32 {
  let i: i32 = 0;
  let fd: i32 = 0;
  let tm: u32 = 0;
  if (n <= 0 || out_fds == 0) {
    return 0;
  }
  i = 0;
  while (i < n) {
    tm = 0;
    if (i == 0) {
      tm = timeout_ms;
    }
    fd = net_accept_c(listener_fd, tm);
    if (fd < 0) {
      return i;
    }
    out_fds[i] = fd;
    i = i + 1;
  }
  return n;
}

/**
 * Connect up to n TCP clients in parallel (Linux io_uring path).
 * @param addr_u32 u32 — packed IPv4 address (host byte order as used by net_tcp_connect_c)
 * @param port_u32 u32 — destination port
 * @param out_fds *i32 — output fd array; length >= n
 * @param n i32 — max connects; n<=0 or null out_fds → 0
 * @param timeout_ms u32 — per-connect timeout milliseconds
 * @return i32 — number of successful connects written to out_fds
 * PLATFORM: LINUX — io_uring_connect_many.
 * G.7: #[no_mangle] matches mod.x `extern function net_connect_many_c` (same as net_accept_many_c).
 */
#[cfg(target_os = "linux")]
#[no_mangle]
export function net_connect_many_c(addr_u32: u32, port_u32: u32, out_fds: *i32, n: i32, timeout_ms: u32): i32 {
  if (n <= 0 || out_fds == 0) {
    return 0;
  }
  unsafe { return io_uring_connect_many(addr_u32, port_u32, out_fds, n, timeout_ms); }
  return 0; // unreachable — typeck workaround
}

/**
 * Connect up to n TCP clients sequentially (non-Linux / Darwin fallback).
 * @param addr_u32 u32 — packed IPv4 address
 * @param port_u32 u32 — destination port
 * @param out_fds *i32 — output fd array; length >= n
 * @param n i32 — max connects; n<=0 or null out_fds → 0
 * @param timeout_ms u32 — per-connect timeout milliseconds
 * @return i32 — number of successful connects; stops on first connect failure
 * PLATFORM: MACOS / non-Linux — sequential net_tcp_connect_c loop.
 * G.7: #[no_mangle] matches mod.x extern surface (same as net_accept_many_c).
 */
#[cfg(not(target_os = "linux"))]
#[no_mangle]
export function net_connect_many_c(addr_u32: u32, port_u32: u32, out_fds: *i32, n: i32, timeout_ms: u32): i32 {
  let i: i32 = 0;
  let fd: i32 = 0;
  if (n <= 0 || out_fds == 0) {
    return 0;
  }
  i = 0;
  while (i < n) {
    fd = net_tcp_connect_c(addr_u32, port_u32, timeout_ms);
    if (fd < 0) {
      return i;
    }
    out_fds[i] = fd;
    i = i + 1;
  }
  return n;
}
