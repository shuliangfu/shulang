/* seeds/runtime_time_os.from_x.c — G-02f-19 product TU
 * Product: runtime_time_os.o; logic migrating to .x (wave501 R2).
 *
 * wave501 R2 migration pattern:
 *   - When XLANG_RUNTIME_TIME_OS_FROM_X is defined:
 *     This seed file provides ONLY the OS bridge _impl functions
 *     (time_monotonic_ns_impl, time_wall_ns_impl, time_sleep_ns_impl,
 *     time_format_rfc3339_impl, time_local_offset_min_impl).
 *     The public API (time_now_monotonic_ns_c, etc.) comes from
 *     src/asm/runtime_time_os.x compiled into runtime_time_os_thin.o.
 *   - When NOT defined (cold bootstrap / fallback):
 *     This seed provides both _impl bridges AND public API wrappers.
 *     The .x file exists as source anchor only.
 *
 * PLATFORM: SHARED (POSIX Cap clock via xlang_time_cap.h + Windows QPC)
 *
 * Cap residual 9.1.5: Linux clock_gettime/nanosleep/gmtime_r via
 * compiler/include/xlang_time_cap.h (no libc those symbols).
 * Cap residual 10.7.2: RFC3339 format via xlang_snprintf (no libc snprintf).
 */
#include <stdint.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: time_format_rfc3339 → xlang_snprintf */
#include <xlang_time_cap.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/* === OS bridge _impl functions (always compiled) === */

/**
 * Bridge: monotonic clock in nanoseconds.
 * PLATFORM: SHARED Cap (xlang_time_clock_gettime).
 * @return nanoseconds; 0 on failure
 */
int64_t time_monotonic_ns_impl(void) {
    struct timespec ts;
    if (xlang_time_clock_gettime(CLOCK_MONOTONIC, &ts) != 0) return 0;
    return (int64_t)ts.tv_sec * 1000000000 + (int64_t)ts.tv_nsec;
}

/**
 * Bridge: wall clock in nanoseconds (UTC).
 * PLATFORM: SHARED Cap (xlang_time_clock_gettime).
 * @return nanoseconds since epoch; 0 on failure
 */
int64_t time_wall_ns_impl(void) {
    struct timespec ts;
    if (xlang_time_clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0;
    return (int64_t)ts.tv_sec * 1000000000 + (int64_t)ts.tv_nsec;
}

/**
 * Bridge: sleep for nanoseconds.
 * PLATFORM: SHARED Cap (xlang_time_sleep_ns).
 * @param ns duration in nanoseconds; <=0 is no-op
 */
void time_sleep_ns_impl(int64_t ns) {
    if (ns <= 0) return;
    xlang_time_sleep_ns((long long)ns);
}

/**
 * Bridge: format current UTC wall clock as RFC3339 (trailing Z).
 * PLATFORM: SHARED Cap (xlang_time_clock_gettime + xlang_time_gmtime_r + xlang_snprintf).
 * @param buf output buffer
 * @param cap buffer capacity in bytes
 * @return written length; -1 on failure
 */
int32_t time_format_rfc3339_impl(uint8_t *buf, int32_t cap) {
    if (!buf || cap <= 0) return -1;
    struct timespec ts;
    if (xlang_time_clock_gettime(CLOCK_REALTIME, &ts) != 0) return -1;
    time_t now = (time_t)ts.tv_sec;
    struct tm tm;
    if (xlang_time_gmtime_r(&now, &tm) == NULL) return -1;
    /* PLATFORM: SHARED — Cap fmt (10.7.2). */
    int n = xlang_snprintf((char *)buf, (size_t)cap, "%04d-%02d-%02dT%02d:%02d:%02dZ",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                 tm.tm_hour, tm.tm_min, tm.tm_sec);
    if (n <= 0 || n >= cap) return -1;
    return (int32_t)n;
}

/**
 * Bridge: local timezone offset from UTC in minutes (east positive).
 * POSIX: localtime_r + Cap gmtime_r + mktime diff
 *   (localtime_r/mktime remain Cap residual — tzdb)
 * Windows: GetTimeZoneInformation.Bias negated
 * @return offset minutes; 0 on failure
 */
int32_t time_local_offset_min_impl(void) {
#if defined(_WIN32) || defined(_WIN64)
    TIME_ZONE_INFORMATION tzi;
    DWORD r = GetTimeZoneInformation(&tzi);
    (void)r;
    return -(int32_t)tzi.Bias;
#else
    time_t now;
    struct tm local_tm;
    struct tm gmt_tm;
    time_t local_sec;
    time_t gmt_sec;
    struct timespec ts;
    /* PLATFORM: SHARED Cap wall sec; localtime_r/mktime still libc (tz residual) */
    if (xlang_time_clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0;
    now = (time_t)ts.tv_sec;
    if (localtime_r(&now, &local_tm) == NULL) return 0;
    if (xlang_time_gmtime_r(&now, &gmt_tm) == NULL) return 0;
    local_tm.tm_isdst = 0;
    gmt_tm.tm_isdst = 0;
    local_sec = mktime(&local_tm);
    gmt_sec = mktime(&gmt_tm);
    if (local_sec == (time_t)-1 || gmt_sec == (time_t)-1) return 0;
    return (int32_t)((local_sec - gmt_sec) / 60);
#endif
}

/* === Public API wrappers (only when NOT in FROM_X mode) === */

#ifndef XLANG_RUNTIME_TIME_OS_FROM_X

/**
 * Public: monotonic clock in nanoseconds.
 * Cold bootstrap wrapper; FROM_X mode uses .x source.
 */
int64_t time_now_monotonic_ns_c(void) {
    return time_monotonic_ns_impl();
}

/**
 * Public: wall clock in nanoseconds since epoch (UTC).
 * Cold bootstrap wrapper; FROM_X mode uses .x source.
 */
int64_t time_now_wall_ns_c(void) {
    return time_wall_ns_impl();
}

/**
 * Public: sleep for nanoseconds. No-op if ns <= 0.
 * Cold bootstrap wrapper; FROM_X mode uses .x source.
 */
void time_sleep_ns_c(int64_t ns) {
    if (ns <= 0) return;
    time_sleep_ns_impl(ns);
}

/**
 * Public: format current UTC wall clock as RFC3339 string.
 * Cold bootstrap wrapper; FROM_X mode uses .x source.
 */
int32_t time_format_wall_rfc3339_c(uint8_t *buf, int32_t cap) {
    if (!buf || cap <= 0) return -1;
    return time_format_rfc3339_impl(buf, cap);
}

/**
 * Public: local timezone offset from UTC in minutes (east positive).
 * Cold bootstrap wrapper; FROM_X mode uses .x source.
 */
int32_t time_wall_local_offset_min_c(void) {
    return time_local_offset_min_impl();
}

#endif /* !XLANG_RUNTIME_TIME_OS_FROM_X */