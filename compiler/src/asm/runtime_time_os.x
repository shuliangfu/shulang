// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_time_os.x — OS time glue R2 full (wave501)
//
// Provides monotonic/wall time, sleep, RFC3339 formatting, and local timezone offset.
// The actual OS API calls (clock_gettime, nanosleep, gmtime_r, etc.) are delegated
// to C bridge functions declared below as extern "C". These are implemented in
// seeds/runtime_time_os.from_x.c via xlang_time_cap.h (SHARED Cap 9.1.5)
// and linked via the product pipeline.
//
// PLATFORM: SHARED — Cap clock (xlang_time_cap) + Cap fmt (xlang_snprintf);
//           Linux/Darwin raw syscalls + Windows Win32 Cap via _impl.
//
// Wave501 (2026-07-27): R2 migration of runtime_time_os.from_x.c business logic to .x.
// Previously the .c seed provided all business logic; now the .x file is the
// authoritative source and the .c seed only provides forward declarations + marker
// in FROM_X mode (see XLANG_RUNTIME_TIME_OS_FROM_X guard).

/* === C bridge declarations (implemented in runtime_time_os.from_x.c) === */

/**
 * Bridge: monotonic clock in nanoseconds.
 * POSIX: clock_gettime(CLOCK_MONOTONIC) → ns
 * Windows: QueryPerformanceCounter → ns
 * @return nanoseconds; 0 on failure
 */
export extern "C" function time_monotonic_ns_impl(): i64;

/**
 * Bridge: wall clock in nanoseconds (UTC).
 * POSIX: clock_gettime(CLOCK_REALTIME) → ns
 * Windows: GetSystemTimePreciseAsFileTime → ns
 * @return nanoseconds since epoch; 0 on failure
 */
export extern "C" function time_wall_ns_impl(): i64;

/**
 * Bridge: sleep for nanoseconds.
 * POSIX: nanosleep loop (handles spurious wakeups)
 * Windows: Sleep (with minimum 1ms clamp)
 * @param ns duration in nanoseconds; <=0 is no-op
 */
export extern "C" function time_sleep_ns_impl(ns: i64): void;

/**
 * Bridge: format current UTC wall clock as RFC3339 (trailing Z).
 * POSIX: Cap gmtime_r + Cap snprintf (10.7.2).
 * Windows: gmtime_s + Cap snprintf.
 * @param buf output buffer
 * @param cap buffer capacity in bytes
 * @return written length; -1 on failure
 * PLATFORM: SHARED
 */
export extern "C" function time_format_rfc3339_impl(buf: *u8, cap: i32): i32;

/**
 * Bridge: local timezone offset from UTC in minutes (east positive).
 * POSIX: localtime_r/gmtime_r + mktime diff
 * Windows: GetTimeZoneInformation.Bias negated
 * @return offset minutes; 0 on failure
 */
export extern "C" function time_local_offset_min_impl(): i32;

/* === Public API (R2 full: business logic in .x) === */

/**
 * Exported function `time_now_monotonic_ns_c`.
 * Returns monotonic clock in nanoseconds.
 * Delegates to C bridge for OS-specific implementation.
 * @return nanoseconds; 0 on failure
 */
#[no_mangle]
export function time_now_monotonic_ns_c(): i64 {
  unsafe {
    return time_monotonic_ns_impl();
  }
}

/**
 * Exported function `time_now_wall_ns_c`.
 * Returns wall clock in nanoseconds since epoch (UTC).
 * Delegates to C bridge for OS-specific implementation.
 * @return nanoseconds; 0 on failure
 */
#[no_mangle]
export function time_now_wall_ns_c(): i64 {
  unsafe {
    return time_wall_ns_impl();
  }
}

/**
 * Exported function `time_sleep_ns_c`.
 * Sleep for the given nanoseconds. No-op if ns <= 0.
 * Delegates to C bridge for OS-specific implementation.
 * @param ns duration in nanoseconds
 */
#[no_mangle]
export function time_sleep_ns_c(ns: i64): void {
  if ns <= 0 {
    return;
  }
  unsafe {
    time_sleep_ns_impl(ns);
  }
}

/**
 * Exported function `time_format_wall_rfc3339_c`.
 * Format current UTC wall clock as RFC3339 string (e.g. "2026-07-27T12:34:56Z").
 * Delegates to C bridge for OS-specific implementation.
 * @param buf output buffer
 * @param cap buffer capacity
 * @return written length; -1 on failure
 */
#[no_mangle]
export function time_format_wall_rfc3339_c(buf: *u8, cap: i32): i32 {
  if buf == 0 || cap <= 0 {
    return -1;
  }
  unsafe {
    return time_format_rfc3339_impl(buf, cap);
  }
}

/**
 * Exported function `time_wall_local_offset_min_c`.
 * Returns local timezone offset from UTC in minutes (east positive).
 * Delegates to C bridge for OS-specific implementation.
 * @return offset minutes; 0 on failure
 */
#[no_mangle]
export function time_wall_local_offset_min_c(): i32 {
  unsafe {
    return time_local_offset_min_impl();
  }
}
