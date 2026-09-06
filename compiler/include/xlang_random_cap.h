/*
 * xlang_random_cap.h — Cap residual 9.1.6: getrandom / getentropy / BCryptGenRandom
 * full-closure Cap convergence.
 *
 * Single authority for runtime_random_fill_bytes_impl CSPRNG fill:
 * - Linux: raw syscall getrandom (318 / 278) via xlang_syscall_cap.h without libc (no errno)
 * - Darwin: raw syscall getentropy (500 / 0x20001f4L) without libc getentropy
 * - Windows: BCryptGenRandom (BCRYPT_USE_SYSTEM_PREFERRED_RNG) without CRT rand
 * - POSIX: libc getentropy fallback elsewhere
 *
 * PLATFORM: SHARED Cap (9.1.6).
 */

#ifndef XLANG_RANDOM_CAP_H
#define XLANG_RANDOM_CAP_H

#include <stddef.h>
#include <stdint.h>

#ifndef GETENTROPY_MAX
#define GETENTROPY_MAX 256
#endif

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

#ifndef BCRYPT_USE_SYSTEM_PREFERRED_RNG
#define BCRYPT_USE_SYSTEM_PREFERRED_RNG 0x00000002
#endif

/**
 * Fill buf with CSPRNG bytes via Windows BCryptGenRandom.
 * @return len on full success; -1 on failure
 * PLATFORM: WINDOWS Win32 Cap (9.1.6)
 */
static inline int32_t xlang_random_fill_bytes(uint8_t *buf, int32_t len) {
  if (!buf || len < 0)
    return -1;
  if (len == 0)
    return 0;
  NTSTATUS status = BCryptGenRandom(NULL, (PUCHAR)buf, (ULONG)(size_t)len, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
  return (status == 0) ? len : -1;
}

#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <xlang_syscall_cap.h>

/** Cap residual 9.1.9: alias → single syscall authority. */
#define xlang_random_syscall3 xlang_syscall3

/**
 * Cap residual getrandom(2) raw syscall without libc errno dependency.
 * @param buf output buffer
 * @param buflen bytes requested
 * @param flags 0 = block until entropy available
 * @return bytes written (>=0), or negative errno (-EINTR, etc.)
 * PLATFORM: LINUX raw syscall Cap (9.1.6)
 */
static inline long xlang_random_getrandom(void *buf, size_t buflen, unsigned int flags) {
  if (!buf && buflen != 0)
    return -22; /* -EINVAL */
#if defined(__x86_64__)
  /* getrandom = 318 */
  return xlang_random_syscall3(318, (long)buf, (long)buflen, (long)flags);
#elif defined(__aarch64__)
  /* getrandom = 278 */
  return xlang_random_syscall3(278, (long)buf, (long)buflen, (long)flags);
#else
  return -38; /* -ENOSYS */
#endif
}

/**
 * Fill buf with CSPRNG bytes via Cap getrandom (EINTR restart, no libc errno).
 * @return len on full success; partial >0 or -1 on failure
 * PLATFORM: LINUX raw syscall Cap (9.1.6)
 */
static inline int32_t xlang_random_fill_bytes(uint8_t *buf, int32_t len) {
  size_t done = 0;
  size_t want;
  if (!buf || len < 0)
    return -1;
  if (len == 0)
    return 0;
  want = (size_t)len;
  while (done < want) {
    long n = xlang_random_getrandom(buf + done, want - done, 0);
    if (n < 0) {
      if (n == -4 /* -EINTR */)
        continue;
      return (int32_t)(done > 0 ? (int32_t)done : -1);
    }
    if (n == 0)
      return (int32_t)(done > 0 ? (int32_t)done : -1);
    done += (size_t)n;
  }
  return len;
}

#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

/**
 * Darwin raw syscall for getentropy(2) without libc dependency.
 * Syscall number: SYS_getentropy = 500 (AArch64) / 0x20001f4L (x86_64).
 * @param buf output buffer (chunk <= 256 bytes)
 * @param len requested length (<= 256)
 * @return 0 on success, -1 on failure
 * PLATFORM: MACOS|DARWIN raw syscall Cap (9.1.6)
 */
static inline int xlang_darwin_raw_getentropy(void *buf, size_t len) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 500; /* SYS_getentropy */
  register long x0 __asm__("x0") = (long)buf;
  register long x1 __asm__("x1") = (long)len;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %2, cs"
                       : "+r"(x0), "+r"(x1), "=r"(failed)
                       : "r"(x16)
                       : "memory", "cc");
  return failed ? -1 : 0;
#elif defined(__x86_64__)
  long ret;
  __asm__ __volatile__("syscall"
                       : "=a"(ret)
                       : "a"(0x20001f4L), "D"(buf), "S"(len)
                       : "rcx", "r11", "memory", "cc");
  return (ret < 0) ? -1 : 0;
#else
  return -1;
#endif
}

/**
 * Fill buf via Darwin raw getentropy syscall (chunked <= GETENTROPY_MAX).
 * @return len on full success; partial >0 or -1 on failure
 * PLATFORM: MACOS|DARWIN raw syscall Cap (9.1.6)
 */
static inline int32_t xlang_random_fill_bytes(uint8_t *buf, int32_t len) {
  size_t done = 0;
  size_t total;
  if (!buf || len < 0)
    return -1;
  if (len == 0)
    return 0;
  total = (size_t)len;
  while (done < total) {
    size_t chunk = total - done;
    if (chunk > (size_t)GETENTROPY_MAX)
      chunk = (size_t)GETENTROPY_MAX;
    if (xlang_darwin_raw_getentropy(buf + done, chunk) != 0)
      return (int32_t)(done > 0 ? (int32_t)done : -1);
    done += chunk;
  }
  return len;
}

#else /* Generic POSIX fallback using libc getentropy */

#include <unistd.h>

/**
 * Fill buf via POSIX getentropy fallback.
 * PLATFORM: POSIX fallback (libc getentropy)
 */
static inline int32_t xlang_random_fill_bytes(uint8_t *buf, int32_t len) {
  size_t done = 0;
  size_t total;
  if (!buf || len < 0)
    return -1;
  if (len == 0)
    return 0;
  total = (size_t)len;
  while (done < total) {
    size_t chunk = total - done;
    if (chunk > (size_t)GETENTROPY_MAX)
      chunk = (size_t)GETENTROPY_MAX;
    if (getentropy(buf + done, chunk) != 0)
      return (int32_t)(done > 0 ? (int32_t)done : -1);
    done += chunk;
  }
  return len;
}

#endif /* Platform branches */

#endif /* XLANG_RANDOM_CAP_H */
