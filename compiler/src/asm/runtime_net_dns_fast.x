// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_net_dns_fast.x — Thin .x exports delegating to
// seeds/runtime_net_dns_fast.from_x.c via xlang_dns_cap.h (SHARED Cap 9.1.7).
//
// PLATFORM: SHARED — Linux & Darwin raw syscalls + Windows Winsock Cap.

export extern "C" function net_dns_ai_addconfig_c_impl_c(): i32;
export extern "C" function net_dns_map_gai_error_c_impl_c(err: i32): i32;
export extern "C" function net_dns_ensure_wsa_c_impl_c(): i32;

/**
 * Anchor function for runtime_net_dns_fast .x module documentation.
 * @return i32 — always 0
 */
export function runtime_net_dns_fast_x_doc_anchor(): i32 {
  return 0;
}

/**
 * Return platform-specific addrinfo add-config flags.
 * @return i32 — flags
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_dns_ai_addconfig_c(): i32 {
  unsafe {
    return net_dns_ai_addconfig_c_impl_c();
  }
  return 0;
}

/**
 * Map getaddrinfo error code to normalized internal error (1=NONAME 2=NODATA 3=AGAIN 4=system).
 * @param err i32 — platform error code
 * @return i32 — normalized error code in [1, 4]
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_dns_map_gai_error_c(err: i32): i32 {
  unsafe {
    return net_dns_map_gai_error_c_impl_c(err);
  }
  return 0;
}

/**
 * Ensure Winsock is initialized for DNS queries on Windows; no-op on POSIX.
 * @return i32 — 0 on success, negative on error
 * PLATFORM: SHARED
 */
#[no_mangle]
export function net_dns_ensure_wsa_c(): i32 {
  unsafe {
    return net_dns_ensure_wsa_c_impl_c();
  }
  return 0;
}
