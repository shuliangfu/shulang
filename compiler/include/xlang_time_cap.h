/*
 * xlang_time_cap.h — Cap residual 9.1.5: clock_gettime / nanosleep / gmtime_r
 * without libc on Linux (x86_64 + aarch64), Darwin (raw syscalls), and Windows (Win32).
 *
 * Single authority for runtime_time_os OS bridges and neighbor C call sites
 * (scheduler trace, channel timedwait, sync smoke sleep, driver wall).
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Win32).
 */

#ifndef XLANG_TIME_CAP_H
#define XLANG_TIME_CAP_H

#include <stddef.h>
#include <stdint.h>
#include <time.h>

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

/* ============================================================================
 * SHARED: Pure civil calendar math (Howard Hinnant algorithm, zero OS calls)
 * ============================================================================ */

/**
 * Days since Unix epoch from civil (y, m, d) UTC.
 * Algorithm: Howard Hinnant days_from_civil.
 * PLATFORM: SHARED math
 */
static inline long xlang_time_days_from_civil(int y, unsigned m, unsigned d) {
  long era;
  unsigned yoe;
  unsigned doy;
  unsigned doe;
  y -= (m <= 2U);
  era = (y >= 0 ? y : y - 399) / 400;
  yoe = (unsigned)(y - era * 400);
  doy = (153U * (m > 2U ? m - 3U : m + 9U) + 2U) / 5U + d - 1U;
  doe = yoe * 365U + yoe / 4U - yoe / 100U + doy;
  return (long)era * 146097L + (long)doe - 719468L;
}

/**
 * Civil calendar from days since Unix epoch (UTC).
 * Algorithm: Howard Hinnant civil_from_days.
 * PLATFORM: SHARED math (used by all platform Cap gmtime_r implementations)
 */
static inline void xlang_time_civil_from_days(long z, int *y, unsigned *m, unsigned *d) {
  long era;
  unsigned doe;
  unsigned yoe;
  unsigned doy;
  unsigned mp;
  long yy;
  z += 719468L;
  era = (z >= 0 ? z : z - 146096L) / 146097L;
  doe = (unsigned)(z - era * 146097L);
  yoe = (doe - doe / 1460U + doe / 36524U - doe / 146096U) / 365U;
  yy = (long)yoe + era * 400L;
  doy = doe - (365U * yoe + yoe / 4U - yoe / 100U);
  mp = (5U * doy + 2U) / 153U;
  *d = (unsigned)(doy - (153U * mp + 2U) / 5U + 1U);
  *m = (unsigned)(mp < 10U ? mp + 3U : mp - 9U);
  *y = (int)(yy + (*m <= 2U ? 1 : 0));
}

/**
 * Cap residual gmtime_r: UTC broken-down time without libc gmtime_r.
 * @param t seconds since Unix epoch
 * @param out struct tm (fields filled; tm_isdst=0)
 * @return out on success, NULL on null args
 * PLATFORM: SHARED Cap (pure civil math)
 */
static inline struct tm *xlang_time_gmtime_r(const time_t *t, struct tm *out) {
  long sec;
  long days;
  long tod;
  int y;
  unsigned m;
  unsigned d;
  if (!t || !out)
    return NULL;
  sec = (long)(*t);
  days = sec / 86400L;
  tod = sec % 86400L;
  if (tod < 0) {
    tod += 86400L;
    days -= 1;
  }
  xlang_time_civil_from_days(days, &y, &m, &d);
  out->tm_year = y - 1900;
  out->tm_mon = (int)m - 1;
  out->tm_mday = (int)d;
  out->tm_hour = (int)(tod / 3600L);
  out->tm_min = (int)((tod % 3600L) / 60L);
  out->tm_sec = (int)(tod % 60L);
  /* 1970-01-01 was Thursday -> (days+4) % 7 */
  out->tm_wday = (int)((days + 4L) % 7L);
  if (out->tm_wday < 0)
    out->tm_wday += 7;
  out->tm_yday = (int)(days - xlang_time_days_from_civil(y, 1U, 1U));
  out->tm_isdst = 0;
  return out;
}

/* ============================================================================
 * PLATFORM: WINDOWS (Win32 API)
 * ============================================================================ */
#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

#ifndef _TIMESPEC_DEFINED
#define _TIMESPEC_DEFINED
struct timespec {
  time_t tv_sec;
  long tv_nsec;
};
#endif

#define UNIX_EPOCH_100NS 116444736000000000ULL

/**
 * Cap residual clock_gettime for Windows.
 * REALTIME: GetSystemTimePreciseAsFileTime
 * MONOTONIC: QueryPerformanceCounter / QueryPerformanceFrequency
 * PLATFORM: WINDOWS Win32
 */
static inline int xlang_time_clock_gettime(int clk_id, struct timespec *ts) {
  if (!ts)
    return -1;
  if (clk_id == CLOCK_REALTIME || clk_id == 0) {
    FILETIME ft;
    ULARGE_INTEGER u;
    GetSystemTimePreciseAsFileTime(&ft);
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    uint64_t ns100 = u.QuadPart - UNIX_EPOCH_100NS;
    ts->tv_sec = (time_t)(ns100 / 10000000ULL);
    ts->tv_nsec = (long)((ns100 % 10000000ULL) * 100ULL);
    return 0;
  } else {
    static LARGE_INTEGER freq = { { 0 } };
    LARGE_INTEGER counter;
    if (freq.QuadPart == 0) {
      if (!QueryPerformanceFrequency(&freq) || freq.QuadPart == 0)
        return -1;
    }
    if (!QueryPerformanceCounter(&counter))
      return -1;
    uint64_t sec = (uint64_t)counter.QuadPart / (uint64_t)freq.QuadPart;
    uint64_t rem = (uint64_t)counter.QuadPart % (uint64_t)freq.QuadPart;
    ts->tv_sec = (time_t)sec;
    ts->tv_nsec = (long)((rem * 1000000000ULL) / (uint64_t)freq.QuadPart);
    return 0;
  }
}

/**
 * Cap residual nanosleep for Windows.
 * PLATFORM: WINDOWS Win32
 */
static inline int xlang_time_nanosleep(const struct timespec *req, struct timespec *rem) {
  (void)rem;
  if (!req)
    return -1;
  DWORD ms = (DWORD)(req->tv_sec * 1000 + (req->tv_nsec + 999999) / 1000000);
  if (ms == 0 && (req->tv_sec > 0 || req->tv_nsec > 0))
    ms = 1;
  Sleep(ms);
  return 0;
}

/* ============================================================================
 * PLATFORM: LINUX (Raw Syscall)
 * ============================================================================ */
#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <xlang_syscall_cap.h>

/** Cap residual 9.1.9: alias -> single syscall authority. */
#define xlang_time_syscall3 xlang_syscall3

/**
 * Cap residual clock_gettime(2).
 * @param clk_id CLOCK_REALTIME (0) or CLOCK_MONOTONIC (1)
 * @param ts out timespec (Linux LP64 layout)
 * @return 0 ok, -1 fail
 * PLATFORM: LINUX
 */
static inline int xlang_time_clock_gettime(int clk_id, struct timespec *ts) {
  long r;
  if (!ts)
    return -1;
#if defined(__x86_64__)
  /* clock_gettime = 228 */
  r = xlang_time_syscall3(228, (long)clk_id, (long)ts, 0);
#elif defined(__aarch64__)
  /* clock_gettime = 113 */
  r = xlang_time_syscall3(113, (long)clk_id, (long)ts, 0);
#endif
  return r == 0 ? 0 : -1;
}

/**
 * Cap residual nanosleep(2). Caller retries on EINTR with rem.
 * @return 0 ok, -1 fail (errno may be EINTR)
 * PLATFORM: LINUX
 */
static inline int xlang_time_nanosleep(const struct timespec *req, struct timespec *rem) {
  long r;
  if (!req)
    return -1;
#if defined(__x86_64__)
  /* nanosleep = 35 */
  r = xlang_time_syscall3(35, (long)req, (long)rem, 0);
#elif defined(__aarch64__)
  /* nanosleep = 101 */
  r = xlang_time_syscall3(101, (long)req, (long)rem, 0);
#endif
  if (r == 0)
    return 0;
  /* Kernel returns -errno; surface POSIX errno for EINTR loops. */
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return -1;
}

/* ============================================================================
 * PLATFORM: MACOS|DARWIN (Raw Syscall)
 * ============================================================================ */
#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <sys/time.h>

/**
 * Raw Darwin syscall SYS_gettimeofday (116).
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_darwin_time_gettimeofday(struct timeval *tv) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 116; /* SYS_gettimeofday */
  register long x0 __asm__("x0") = (long)tv;
  register long x1 __asm__("x1") = 0;
  register long x2 __asm__("x2") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %3, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -1 : 0;
#elif defined(__x86_64__)
  long ret;
  __asm__ __volatile__(
      "movq $0x2000074, %%rax\n\t" /* 0x2000000 + 116 */
      "syscall\n\t"
      "jnc 1f\n\t"
      "movq $-1, %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "D"(tv), "S"(0), "d"(0)
      : "rcx", "r11", "memory", "cc"
  );
  return (int)ret;
#endif
}

/**
 * Raw Darwin syscall SYS_pselect (394).
 * Used for nanosecond precision sleep without libc nanosleep.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_darwin_time_pselect(const struct timespec *req) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 394; /* SYS_pselect */
  register long x0 __asm__("x0") = 0;     /* nfds */
  register long x1 __asm__("x1") = 0;     /* readfds */
  register long x2 __asm__("x2") = 0;     /* writefds */
  register long x3 __asm__("x3") = 0;     /* exceptfds */
  register long x4 __asm__("x4") = (long)req; /* timeout */
  register long x5 __asm__("x5") = 0;     /* sigmask */
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %6, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "+r"(x3), "+r"(x4), "+r"(x5), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -1 : 0;
#elif defined(__x86_64__)
  long ret;
  register long r10 __asm__("r10") = 0;
  register long r8  __asm__("r8")  = (long)req;
  register long r9  __asm__("r9")  = 0;
  __asm__ __volatile__(
      "movq $0x200018a, %%rax\n\t" /* 0x2000000 + 394 */
      "syscall\n\t"
      "jnc 1f\n\t"
      "movq $-1, %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "D"(0), "S"(0), "d"(0), "r"(r10), "r"(r8), "r"(r9)
      : "rcx", "r11", "memory", "cc"
  );
  return (int)ret;
#endif
}

/**
 * Cap residual clock_gettime for Darwin.
 * REALTIME: SYS_gettimeofday raw syscall.
 * MONOTONIC: ARM64 cntvct_el0 / SYS_gettimeofday raw syscall.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_time_clock_gettime(int clk_id, struct timespec *ts) {
  if (!ts)
    return -1;
  if (clk_id == CLOCK_REALTIME || clk_id == 0) {
    struct timeval tv = {0, 0};
    if (xlang_darwin_time_gettimeofday(&tv) != 0)
      return -1;
    ts->tv_sec = tv.tv_sec;
    ts->tv_nsec = (long)tv.tv_usec * 1000L;
    return 0;
  }
#if defined(__aarch64__)
  uint64_t ticks;
  uint64_t frq;
  __asm__ __volatile__("isb\n\tmrs %0, cntvct_el0" : "=r"(ticks));
  __asm__ __volatile__("mrs %0, cntfrq_el0" : "=r"(frq));
  if (frq == 1000000000ULL) {
    ts->tv_sec = (time_t)(ticks / 1000000000ULL);
    ts->tv_nsec = (long)(ticks % 1000000000ULL);
    return 0;
  } else if (frq > 0) {
    ts->tv_sec = (time_t)(ticks / frq);
    ts->tv_nsec = (long)(((ticks % frq) * 1000000000ULL) / frq);
    return 0;
  }
#endif
  struct timeval tv = {0, 0};
  if (xlang_darwin_time_gettimeofday(&tv) != 0)
    return -1;
  ts->tv_sec = tv.tv_sec;
  ts->tv_nsec = (long)tv.tv_usec * 1000L;
  return 0;
}

/**
 * Cap residual nanosleep for Darwin via raw SYS_pselect.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_time_nanosleep(const struct timespec *req, struct timespec *rem) {
  if (!req)
    return -1;
  (void)rem;
  int r = xlang_darwin_time_pselect(req);
  if (r == 0)
    return 0;
  errno = EINTR;
  return -1;
}

/* ============================================================================
 * PLATFORM: Generic POSIX fallback
 * ============================================================================ */
#else

#include <errno.h>

/** PLATFORM: POSIX fallback — libc clock_gettime. */
static inline int xlang_time_clock_gettime(int clk_id, struct timespec *ts) {
  return clock_gettime(clk_id, ts);
}

/** PLATFORM: POSIX fallback — libc nanosleep. */
static inline int xlang_time_nanosleep(const struct timespec *req, struct timespec *rem) {
  return nanosleep(req, rem);
}

#endif /* Platform branches */

/**
 * Sleep ns with retry on EINTR (Cap residual sleep loop helper).
 * @param ns duration; <=0 is no-op
 * PLATFORM: SHARED via xlang_time_nanosleep
 */
static inline void xlang_time_sleep_ns(long long ns) {
  struct timespec req;
  struct timespec rem;
  if (ns <= 0)
    return;
  req.tv_sec = (time_t)(ns / 1000000000LL);
  req.tv_nsec = (long)(ns % 1000000000LL);
  for (;;) {
    if (xlang_time_nanosleep(&req, &rem) == 0)
      return;
#if defined(EINTR)
    if (errno != EINTR)
      return;
#endif
    req = rem;
  }
}

#endif /* XLANG_TIME_CAP_H */
