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

export const AF_INET: i32 = 2;
export const SOCK_DGRAM: i32 = 2;
export const IPPROTO_UDP: i32 = 17;
export const SOL_SOCKET: i32 = 1;
export const SO_REUSEADDR: i32 = 2;
export const O_NONBLOCK: i32 = 2048;
/* See implementation. */

/* See implementation. */
allow(padding) struct SockAddrIn {
  sin_family: u16;
  sin_port: u16;
  sin_addr: u32;
}

#[cfg(not(target_os = "windows"))]
allow(padding) struct PollFd { fd: i32; events: i16; revents: i16; }

/* Cap residual 9.1.7: SHARED product face via sock_fast Cap bodies (not libc sendto/recvfrom). */
extern function xlang_sys_sendto(sockfd: i32, buf: *u8, len: i32, flags: i32, addr: *u8, addrlen: i32): i32;
extern function xlang_sys_recvfrom(sockfd: i32, buf: *u8, len: i32, flags: i32, addr: *u8, addrlen: *u32): i32;
extern "C" function htonl(hostlong: u32): u32;
extern "C" function htons(hostshort: u16): u16;
extern "C" function ntohl(netlong: u32): u32;
extern "C" function ntohs(netshort: u16): u16;

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
export function net_udp_errno_ptr(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __errno_location(); }
  return p;
}

/** Exported function `net_udp_errno_ptr`.
 * Implements `net_udp_errno_ptr`.
 * @return *i32
 */
#[cfg(target_os = "macos")]
export function net_udp_errno_ptr(): *i32 {
  let p: *i32 = 0 as *i32;
  unsafe { p = __error(); }
  return p;
}

#[cfg(target_os = "linux")]
export const ERR_EAGAIN: i32 = 11;

#[cfg(target_os = "macos")]
export const ERR_EAGAIN: i32 = 35;

#[cfg(target_os = "windows")]
extern "C" function WSAStartup(wVersionRequested: u16, lpWSAData: *u8): i32;

#[cfg(target_os = "windows")]
extern "C" function ioctlsocket(fd: i32, cmd: i32, arg: *u32): i32;

#[cfg(target_os = "windows")]
extern "C" function closesocket(fd: i32): i32;

#[cfg(target_os = "windows")]
let net_udp_wsa_done: i32 = 0;

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_udp_ensure_wsa_c(): i32 {
  if (net_udp_wsa_done != 0) {
    return 0;
  }
  unsafe { if (WSAStartup(514 as u16, 0 as *u8) != 0) {
    return -1;
  } }
  net_udp_wsa_done = 1;
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_udp_maybe_wsa_fail_c(): i32 {
  if (net_udp_ensure_wsa_c() != 0) {
    return -1;
  }
  return 0;
}

/** Exported function `net_udp_maybe_wsa_fail_c`.
 * Implements `net_udp_maybe_wsa_fail_c`.
 * @return i32
 */
#[cfg(not(target_os = "windows"))]
export function net_udp_maybe_wsa_fail_c(): i32 {
  return 0;
}

/**
 * See implementation.
 */
export function net_udp_sin_buf_ptr_c(p: *u8): *u8 {
  return p;
}

/* See implementation. */
extern function net_udp_set_addr_port_buf_c(sin: *u8, addr_u32: u32, port_u32: u32): void;

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_udp_set_nonblock_c(fd: i32): i32 {
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
export function net_udp_set_nonblock_c(fd: i32): i32 {
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
export function net_udp_poll_readable_c(fd: i32, timeout_ms: u32): i32 {
  let pfd_mem: u8[8] = [];
  let pfd_ptr: *u8 = net_udp_sin_buf_ptr_c(&pfd_mem[0]);
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
export function net_udp_poll_readable_c(fd: i32, timeout_ms: u32): i32 {
  return 0;
}

/**
 * See implementation.
 */
#[cfg(not(target_os = "windows"))]
export function net_udp_recv_is_eagain_c(): i32 {
  let ep: *i32 = 0 as *i32;
  ep = net_udp_errno_ptr();
  if (ep[0] == ERR_EAGAIN) {
    return 1;
  }
  return 0;
}

/**
 * See implementation.
 */
#[cfg(target_os = "windows")]
export function net_udp_recv_is_eagain_c(): i32 {
  return 0;
}

/**
 * See implementation.
 * See implementation.
 */
extern function net_udp_bind_c(addr_u32: u32, port_u32: u32): i32;

/**
 * See implementation.
 */
#[no_mangle]
export function net_udp_send_to_c(fd: i32, addr_u32: u32, port_u32: u32, buf: *u8, len: usize): i32 {
  let sin_mem: u8[16] = [];
  let sin_ptr: *u8 = net_udp_sin_buf_ptr_c(&sin_mem[0]);
  let n: i32 = 0;
  unsafe { net_udp_set_addr_port_buf_c(sin_ptr, addr_u32, port_u32); }
  unsafe { n = xlang_sys_sendto(fd, buf, len as i32, 0, sin_ptr, 16); }
  if (n >= 0) {
    return n;
  }
  return -1;
}

/**
 * See implementation.
 */
#[no_mangle]
export function net_udp_recv_from_c(fd: i32, buf: *u8, len: usize, timeout_ms: u32, out_addr_u32: *u32, out_port_u32: *u32): i32 {
  let peer_mem: u8[16] = [];
  let peer_ptr: *u8 = net_udp_sin_buf_ptr_c(&peer_mem[0]);
  let peer_len: u32 = 16;
  let p_port: *u16 = (peer_ptr + 2) as *u16;
  let p_addr: *u32 = (peer_ptr + 4) as *u32;
  let n: i32 = 0;
  if (timeout_ms != 0) {
    if (net_udp_poll_readable_c(fd, timeout_ms) != 0) {
      return -1;
    }
  }
  unsafe { n = xlang_sys_recvfrom(fd, buf, len as i32, 0, peer_ptr, &peer_len); }
  if (n < 0) {
    if (net_udp_recv_is_eagain_c() != 0) {
      return 0;
    }
    return -1;
  }
  if (out_addr_u32 != 0) {
    unsafe { out_addr_u32[0] = ntohl(p_addr[0]); }
  }
  if (out_port_u32 != 0) {
    unsafe { out_port_u32[0] = ntohs(p_port[0]) as u32; }
  }
  return n;
}
