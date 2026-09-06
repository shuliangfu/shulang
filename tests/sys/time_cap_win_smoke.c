/**
 * tests/sys/time_cap_win_smoke.c — Windows Win32 time Cap probe (9.1.5).
 *
 * Verifies xlang_time_cap.h primitives without CRT time functions on Windows:
 * 1. REALTIME clock via GetSystemTimePreciseAsFileTime returns plausible epoch (> 2020)
 * 2. MONOTONIC clock via QueryPerformanceCounter returns valid time
 * 3. nanosleep via Sleep sleeps 2ms successfully
 * 4. Monotonic clock advances across nanosleep
 * 5. xlang_time_sleep_ns loop helper functions correctly
 * 6. xlang_time_gmtime_r decomposes 2020-01-01 00:00:00 UTC correctly
 * 7. NULL checks return expected errors
 *
 * PLATFORM: WINDOWS Win32 Cap (9.1.5).
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "compiler/include/xlang_time_cap.h"

int main(void) {
  struct timespec ts_real;
  struct timespec ts1;
  struct timespec ts2;
  struct timespec req;
  struct timespec rem;
  struct tm tm_buf;
  time_t epoch_2020 = 1577836800L; /* 2020-01-01 00:00:00 UTC */
  long long diff_ns;

  /* Step 1: REALTIME clock */
  memset(&ts_real, 0, sizeof(ts_real));
  if (xlang_time_clock_gettime(CLOCK_REALTIME, &ts_real) != 0) {
    return 1;
  }
  if (ts_real.tv_sec < epoch_2020 || ts_real.tv_nsec < 0 || ts_real.tv_nsec >= 1000000000L) {
    return 1;
  }

  /* Step 2: MONOTONIC clock */
  memset(&ts1, 0, sizeof(ts1));
  if (xlang_time_clock_gettime(CLOCK_MONOTONIC, &ts1) != 0) {
    return 2;
  }
  if (ts1.tv_sec < 0 || ts1.tv_nsec < 0 || ts1.tv_nsec >= 1000000000L) {
    return 2;
  }

  /* Step 3: nanosleep 2ms via Win32 Sleep */
  req.tv_sec = 0;
  req.tv_nsec = 2000000L; /* 2ms */
  memset(&rem, 0, sizeof(rem));
  if (xlang_time_nanosleep(&req, &rem) != 0) {
    return 3;
  }

  /* Step 4: Monotonic advances across sleep */
  memset(&ts2, 0, sizeof(ts2));
  if (xlang_time_clock_gettime(CLOCK_MONOTONIC, &ts2) != 0) {
    return 4;
  }
  diff_ns = ((long long)ts2.tv_sec - ts1.tv_sec) * 1000000000LL + (ts2.tv_nsec - ts1.tv_nsec);
  if (diff_ns < 1000000LL) { /* at least 1ms */
    return 4;
  }

  /* Step 5: xlang_time_sleep_ns helper */
  xlang_time_sleep_ns(1000000LL); /* 1ms */
  if (xlang_time_clock_gettime(CLOCK_MONOTONIC, &ts1) != 0) {
    return 5;
  }
  diff_ns = ((long long)ts1.tv_sec - ts2.tv_sec) * 1000000000LL + (ts1.tv_nsec - ts2.tv_nsec);
  if (diff_ns < 500000LL) {
    return 5;
  }

  /* Step 6: pure civil gmtime_r verification */
  memset(&tm_buf, 0, sizeof(tm_buf));
  if (xlang_time_gmtime_r(&epoch_2020, &tm_buf) != &tm_buf) {
    return 6;
  }
  if (tm_buf.tm_year != 120 || tm_buf.tm_mon != 0 || tm_buf.tm_mday != 1 ||
      tm_buf.tm_hour != 0 || tm_buf.tm_min != 0 || tm_buf.tm_sec != 0 ||
      tm_buf.tm_wday != 3) {
    return 6;
  }

  /* Step 7: NULL safety */
  if (xlang_time_clock_gettime(CLOCK_REALTIME, NULL) != -1) {
    return 7;
  }
  if (xlang_time_nanosleep(NULL, NULL) != -1) {
    return 7;
  }
  if (xlang_time_gmtime_r(NULL, &tm_buf) != NULL) {
    return 7;
  }
  if (xlang_time_gmtime_r(&epoch_2020, NULL) != NULL) {
    return 7;
  }

  return 0;
}
