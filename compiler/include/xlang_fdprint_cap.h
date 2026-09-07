/*
 * xlang_fdprint_cap.h — Cap residual 9.5.4: freestanding format-to-fd write
 * without libc (no <stdio.h>, no FILE*).
 *
 * G.7: single authority for the "vsnprintf + write" combo face. Lifted from
 * bootstrap_nostdlib_stubs.from_x.c bootstrap_vfprintf_fd_impl (bounded face)
 * and runtime_pipeline_abi.from_x.c pabi_trace; both call sites become thin
 * wrappers over this header.
 *
 * Bounded contract (loud): formats into a 512-byte stack buffer — output is
 * truncated at 511 bytes (same bound as the 9.7.1 pabi_trace precedent).
 * Consumers are short diagnostic/trace lines; no heap, freestanding-safe.
 *
 * One write per call: the formatted bytes go out in a single xlang_io_write,
 * so interleaved fd-2 traces from multiple TUs stay line-atomic.
 *
 * PLATFORM: SHARED (xlang_io_cap.h: LINUX/DARWIN raw syscall | WINDOWS CRT |
 * POSIX fallback).
 */

#ifndef XLANG_FDPRINT_CAP_H
#define XLANG_FDPRINT_CAP_H

#include <stddef.h>

#include <xlang_fmt_cap.h>
#include <xlang_io_cap.h>

/**
 * Format fmt/ap and write the bytes to fd in one xlang_io_write call.
 * @param fd target file descriptor (e.g. 1 stdout, 2 stderr)
 * @param fmt printf-style format (xlang_vsnprintf spec coverage)
 * @param ap va_list already started by the caller
 * @return bytes written (>= 0; truncated at 511), or -1 on write error;
 *         0 when fmt is NULL or the format yields no bytes
 * PLATFORM: SHARED
 */
static inline int xlang_vfdprintf(int fd, const char *fmt, xlang_va_list ap) {
  char b[512];
  int n;
  long w;
  if (fmt == 0) {
    return 0;
  }
  n = xlang_vsnprintf(b, sizeof(b), fmt, ap);
  if (n <= 0) {
    return 0;
  }
  if ((size_t)n >= sizeof(b)) {
    /* Bounded face: truncation at 511 bytes is the documented contract. */
    n = (int)sizeof(b) - 1;
  }
  w = xlang_io_write(fd, b, (size_t)n);
  return w == (long)n ? n : -1;
}

/**
 * Cap fdprintf — Cap va_start + xlang_vfdprintf.
 * @param fd target file descriptor
 * @param fmt printf-style format
 * @return bytes written, or -1 on write error; 0 on NULL fmt / empty output
 * PLATFORM: SHARED
 */
static inline int xlang_fdprintf(int fd, const char *fmt, ...) {
  xlang_va_list ap;
  int n;
  xlang_va_start(ap, fmt);
  n = xlang_vfdprintf(fd, fmt, ap);
  xlang_va_end(ap);
  return n;
}

#endif /* XLANG_FDPRINT_CAP_H */
