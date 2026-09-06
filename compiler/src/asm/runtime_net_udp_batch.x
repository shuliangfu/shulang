// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_net_udp_batch.x — Thin .x exports delegating to
// seeds/runtime_net_udp_batch.from_x.c via xlang_net_cap.h (SHARED Cap 9.1.7).
//
// PLATFORM: SHARED — Linux & Darwin raw syscalls + Windows Winsock Cap.

export extern "C" function xlang_udp_batch_set_addr_port_impl(sin: *u8, addr_u32: u32, port_u32: u32): void;
export extern "C" function xlang_udp_batch_poll_readable_impl(fd: i32, timeout_ms: u32): i32;

/**
 * Anchor function for runtime_net_udp_batch .x module documentation.
 * @return i32 — always 0
 */
export function runtime_net_udp_batch_x_doc_anchor(): i32 {
  return 0;
}

/**
 * Populate IPv4 sockaddr_in buffer with address and port in network order.
 * @param sin *u8 — pointer to sockaddr_in buffer
 * @param addr_u32 u32 — host-order IPv4 address
 * @param port_u32 u32 — host-order port number
 * @return void
 * PLATFORM: SHARED
 */
#[no_mangle]
export function xlang_udp_batch_set_addr_port(sin: *u8, addr_u32: u32, port_u32: u32): void {
  unsafe {
    xlang_udp_batch_set_addr_port_impl(sin, addr_u32, port_u32);
  }
}

/**
 * Poll UDP socket for readability with timeout.
 * @param fd i32 — socket descriptor
 * @param timeout_ms u32 — timeout in milliseconds
 * @return i32 — 0 on success, negative on timeout or error
 * PLATFORM: SHARED
 */
#[no_mangle]
export function xlang_udp_batch_poll_readable(fd: i32, timeout_ms: u32): i32 {
  unsafe {
    return xlang_udp_batch_poll_readable_impl(fd, timeout_ms);
  }
  return 0;
}
