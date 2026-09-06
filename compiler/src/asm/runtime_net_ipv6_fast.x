// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_net_ipv6_fast.x — Thin .x exports delegating to
// seeds/runtime_net_ipv6_fast.from_x.c via xlang_net_cap.h (SHARED Cap 9.1.7).
//
// PLATFORM: SHARED — Linux & Darwin raw syscalls + Windows Winsock Cap.

export extern "C" function net_ipv6_ensure_wsa_c_impl_c(): i32;
export extern "C" function net_ipv6_close_socket_c_impl_c(fd: i32): i32;
export extern "C" function net_ipv6_set_nonblock_c_impl_c(fd: i32): i32;
export extern "C" function net_ipv6_poll_writable_c_impl_c(fd: i32, timeout_ms: u32): i32;
export extern "C" function net_ipv6_connect_retry_ok_c_impl_c(): i32;

/**
 * Anchor function for runtime_net_ipv6_fast .x module documentation.
 * @return i32 — always 0
 */
export function runtime_net_ipv6_fast_x_doc_anchor(): i32 {
  return 0;
}

/**
 * Ensure Winsock is initialized for IPv6 on Windows; no-op on POSIX.
 * @return i32 — 0 on success
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_ipv6_ensure_wsa_c(): i32 {
  unsafe {
    return net_ipv6_ensure_wsa_c_impl_c();
  }
  return 0;
}

/**
 * Close an IPv6 socket descriptor.
 * @param fd i32 — socket descriptor
 * @return i32 — 0 on success, -1 on error
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_ipv6_close_socket_c(fd: i32): i32 {
  unsafe {
    return net_ipv6_close_socket_c_impl_c(fd);
  }
  return 0 - 1;
}

/**
 * Set an IPv6 socket to nonblocking mode.
 * @param fd i32 — socket descriptor
 * @return i32 — 0 on success, -1 on error
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_ipv6_set_nonblock_c(fd: i32): i32 {
  unsafe {
    return net_ipv6_set_nonblock_c_impl_c(fd);
  }
  return 0 - 1;
}

/**
 * Poll an IPv6 socket for write readiness with timeout.
 * @param fd i32 — socket descriptor
 * @param timeout_ms u32 — timeout in milliseconds
 * @return i32 — 0 on success, -1 on timeout or error
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_ipv6_poll_writable_c(fd: i32, timeout_ms: u32): i32 {
  unsafe {
    return net_ipv6_poll_writable_c_impl_c(fd, timeout_ms);
  }
  return 0;
}

/**
 * Check if the last connect error is retryable (EINPROGRESS or EAGAIN).
 * @return i32 — 1 if retryable, 0 otherwise
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_ipv6_connect_retry_ok_c(): i32 {
  unsafe {
    return net_ipv6_connect_retry_ok_c_impl_c();
  }
  return 0;
}
