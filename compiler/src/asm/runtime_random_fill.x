// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_random_fill.x — R2 full wave514
//
// CSPRNG OS glue: random_fill_bytes_c for crypto-secure random byte fill
// (Windows BCryptGenRandom / Linux raw getrandom / macOS raw getentropy
// via xlang_random_cap.h).
// Windows BCrypt algorithm handle lazy init (random_get_alg) is also thin.
// OS API calls are delegated to C bridge functions declared below as
// extern "C", implemented in seeds/runtime_random_fill.from_x.c and linked
// via the product pipeline (thin+rest ld -r pattern).
//
// PLATFORM: SHARED Cap (9.1.6)
// Cap residual 9.1.6: full-closure Cap convergence (no libc getrandom / getentropy).
//
// Wave514 (2026-07-27): R2 migration. random_fill_bytes_c business logic
// moved to .x; the .c seed provides _impl OS bridge implementations only.

/* === C bridge declarations (implemented in runtime_random_fill.from_x.c) === */

/**
 * Bridge: return Windows BCrypt RNG algorithm handle (lazy init).
 * Windows: BCryptOpenAlgorithmProvider via InitOnceExecuteOnce
 * Non-Windows: returns NULL (stub; random_fill_bytes_impl handles platform branch)
 * @return BCRYPT_ALG_HANDLE as *u8 (NULL on non-Windows)
 */
export extern "C" function random_get_alg_impl(): *u8;

/**
 * Bridge: fill buffer with crypto-secure random bytes.
 * Windows: BCryptGenRandom
 * Linux: Cap getrandom loop (xlang_random_cap.h; handles EINTR)
 * macOS: getentropy chunked (≤GETENTROPY_MAX per call)
 * @param buf output buffer
 * @param len byte count (≥0)
 * @return bytes written on success; -1 on failure; partial write count if interrupted
 */
export extern "C" function random_fill_bytes_impl(buf: *u8, len: i32): i32;

/* === Public API (R2 full: thin wrappers in .x, OS calls in rest C) === */

/**
 * Exported function `runtime_random_fill_x_doc_anchor`.
 * Read path helper for codegen discovery; returns 0.
 * @return i32
 */
export function runtime_random_fill_x_doc_anchor(): i32 {
  return 0;
}

/**
 * Exported function `random_get_alg`.
 * Return Windows BCrypt RNG algorithm handle. Thin-only wrapper;
 * non-Windows always returns NULL (handled by rest stub).
 * @return BCRYPT_ALG_HANDLE as *u8
 */
#[no_mangle]
export function random_get_alg(): *u8 {
  unsafe {
    return random_get_alg_impl();
  }
}

/**
 * Exported function `random_fill_bytes_c`.
 * Write `len` bytes of crypto-secure random data into `buf`.
 * Returns bytes written on success (== len); -1 on failure;
 * partial write count if interrupted before completion.
 * @param buf output buffer
 * @param len byte count (≥0)
 * @return bytes written or -1
 */
#[no_mangle]
export function random_fill_bytes_c(buf: *u8, len: i32): i32 {
  if buf == 0 || len < 0 {
    return -1;
  }
  if len == 0 {
    return 0;
  }
  unsafe {
    return random_fill_bytes_impl(buf, len);
  }
}
