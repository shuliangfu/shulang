/*
 * xlang_io_cap.h — Cap residual 9.1.8: write/read/writev without libc.
 * Cap residual 9.5.3: xlang_io_open_write (create/truncate for diagnostics
 * output such as crash evidence bundles).
 *
 * Single authority for rt_preamble xlang_sys_write/read/writev inlines and
 * freestanding_io syscall face (asm twin keeps same numbers).
 *
 * Linux: raw syscalls (x86_64: 1 write, 0 read, 20 writev, 2 open; aarch64: 64 write, 63 read, 66 writev, 56 open).
 * Darwin: raw syscalls (SYS_write=4, SYS_read=3, SYS_writev=121, SYS_open=5).
 * Windows: CRT/Win32 IO Cap (_write, _read, writev loop emulation, _open).
 * Other POSIX: thin libc wrappers.
 *
 * PLATFORM: SHARED (LINUX raw syscall | DARWIN raw syscall | WINDOWS | POSIX fallback).
 */

#ifndef XLANG_IO_CAP_H
#define XLANG_IO_CAP_H

#if defined(_WIN32) || defined(_WIN64)

#include <errno.h>
#include <io.h>
#include <fcntl.h>  /* 9.5.3: _O_WRONLY/_O_CREAT/_O_TRUNC for xlang_io_open_write */
#include <sys/stat.h> /* 9.5.3: _S_IREAD/_S_IWRITE for xlang_io_open_write */
#include <stddef.h>
#include <stdint.h>

#ifndef _IOVEC_DEFINED
#define _IOVEC_DEFINED
struct iovec {
  void *iov_base;
  size_t iov_len;
};
#endif

/**
 * Windows Cap write via _write.
 * @return bytes written, or -1 with errno
 * PLATFORM: WINDOWS
 */
static inline long xlang_io_write(int fd, const void *buf, size_t count) {
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
  int r = _write(fd, buf, (unsigned int)count);
  return (long)r;
}

/**
 * Windows Cap read via _read.
 * @return bytes read, 0 on EOF, or -1 with errno
 * PLATFORM: WINDOWS
 */
static inline long xlang_io_read(int fd, void *buf, size_t count) {
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
  int r = _read(fd, buf, (unsigned int)count);
  return (long)r;
}

/**
 * Cap residual 9.5.3: open/create file for writing via CRT _open
 * (_O_WRONLY|_O_CREAT|_O_TRUNC, mode _S_IREAD|_S_IWRITE ≡ 0644).
 * @param path NUL-terminated file path
 * @return new file descriptor, or -1 with errno
 * PLATFORM: WINDOWS
 */
static inline int xlang_io_open_write(const char *path) {
  if (!path)
    return -1;
  return _open(path, _O_WRONLY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);
}

/**
 * Windows Cap writev simulation via loop of _write.
 * @return total bytes written, or -1 on error
 * PLATFORM: WINDOWS
 */
static inline long xlang_io_writev(int fd, const void *iov_ptr, int iovcnt) {
  if (iovcnt == 0)
    return 0;
  if (!iov_ptr)
    return -1;
  const struct iovec *iov = (const struct iovec *)iov_ptr;
  size_t total = 0;
  for (int i = 0; i < iovcnt; ++i) {
    if (!iov[i].iov_base || iov[i].iov_len == 0)
      continue;
    int n = _write(fd, iov[i].iov_base, (unsigned int)iov[i].iov_len);
    if (n < 0)
      return total > 0 ? (long)total : -1;
    total += (size_t)n;
    if ((size_t)n < (size_t)iov[i].iov_len)
      break;
  }
  return (long)total;
}

#else /* !_WIN32 */

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <xlang_syscall_cap.h>

/** Cap residual 9.1.9: aliases → single syscall authority. */
#define xlang_io_syscall6 xlang_syscall6
#define xlang_io_syscall3 xlang_syscall3

/**
 * Cap residual write(2).
 * @return bytes written, or -1 with errno
 * PLATFORM: LINUX
 */
static inline long xlang_io_write(int fd, const void *buf, size_t count) {
  long r;
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
#if defined(__x86_64__)
  /* write = 1 */
  r = xlang_io_syscall3(1, (long)fd, (long)buf, (long)count);
#elif defined(__aarch64__)
  /* write = 64 */
  r = xlang_io_syscall3(64, (long)fd, (long)buf, (long)count);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual read(2).
 * PLATFORM: LINUX
 */
static inline long xlang_io_read(int fd, void *buf, size_t count) {
  long r;
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
#if defined(__x86_64__)
  /* read = 0 */
  r = xlang_io_syscall3(0, (long)fd, (long)buf, (long)count);
#elif defined(__aarch64__)
  /* read = 63 */
  r = xlang_io_syscall3(63, (long)fd, (long)buf, (long)count);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual 9.5.3: open/create file for writing (O_WRONLY|O_CREAT|O_TRUNC,
 * mode 0644) via raw syscall (open = 2 on x86_64, 56 on aarch64). Linux flag
 * values: O_WRONLY 0x1, O_CREAT 0x40, O_TRUNC 0x200.
 * @param path NUL-terminated file path
 * @return new file descriptor, or -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_io_open_write(const char *path) {
  long r;
  if (!path)
    return -1;
#if defined(__x86_64__)
  /* open = 2 */
  r = xlang_io_syscall3(2, (long)path, 0x241L /* O_WRONLY|O_CREAT|O_TRUNC */, 0644);
#elif defined(__aarch64__)
  /* open = 56 */
  r = xlang_io_syscall3(56, (long)path, 0x241L /* O_WRONLY|O_CREAT|O_TRUNC */, 0644);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/**
 * Cap residual writev(2).
 * PLATFORM: LINUX
 */
static inline long xlang_io_writev(int fd, const void *iov, int iovcnt) {
  long r;
  if (iovcnt == 0)
    return 0;
  if (!iov)
    return -1;
#if defined(__x86_64__)
  /* writev = 20 */
  r = xlang_io_syscall3(20, (long)fd, (long)iov, (long)iovcnt);
#elif defined(__aarch64__)
  /* writev = 66 */
  r = xlang_io_syscall3(66, (long)fd, (long)iov, (long)iovcnt);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

/**
 * Darwin raw write via syscall (SYS_write = 4).
 * @return bytes written, or -1 with errno
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_io_write(int fd, const void *buf, size_t count) {
  long r;
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
#if defined(__x86_64__)
  {
    /* write = 4 → 0x2000004 on macOS x86_64 */
    register long r10 __asm__("r10") = (long)count;
    __asm__ __volatile__("syscall"
                         : "=a"(r)
                         : "a"(0x2000004L), "D"(fd), "S"(buf), "d"(r10)
                         : "rcx", "r11", "memory");
  }
#elif defined(__aarch64__)
  {
    register long x16 __asm__("x16") = 4; /* SYS_write */
    register long x0 __asm__("x0") = (long)fd;
    register long x1 __asm__("x1") = (long)buf;
    register long x2 __asm__("x2") = (long)count;
    register long failed __asm__("x9");
    __asm__ __volatile__("svc #0x80\n\t"
                         "cset %3, cs"
                         : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
                         : "r"(x16)
                         : "memory", "cc");
    if (failed)
      r = -x0;
    else
      r = x0;
  }
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Darwin raw read via syscall (SYS_read = 3).
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline long xlang_io_read(int fd, void *buf, size_t count) {
  long r;
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
#if defined(__x86_64__)
  {
    /* read = 3 → 0x2000003 on macOS x86_64 */
    register long r10 __asm__("r10") = (long)count;
    __asm__ __volatile__("syscall"
                         : "=a"(r)
                         : "a"(0x2000003L), "D"(fd), "S"(buf), "d"(r10)
                         : "rcx", "r11", "memory");
  }
#elif defined(__aarch64__)
  {
    register long x16 __asm__("x16") = 3; /* SYS_read */
    register long x0 __asm__("x0") = (long)fd;
    register long x1 __asm__("x1") = (long)buf;
    register long x2 __asm__("x2") = (long)count;
    register long failed __asm__("x9");
    __asm__ __volatile__("svc #0x80\n\t"
                         "cset %3, cs"
                         : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
                         : "r"(x16)
                         : "memory", "cc");
    if (failed)
      r = -x0;
    else
      r = x0;
  }
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual 9.5.3: open/create file for writing via raw syscall
 * (SYS_open = 5, 0x2000005 on x86_64). Darwin flag values differ from Linux:
 * O_WRONLY 0x1, O_CREAT 0x200, O_TRUNC 0x400; mode 0644.
 * @param path NUL-terminated file path
 * @return new file descriptor, or -1 with errno
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_io_open_write(const char *path) {
  long r;
  if (!path)
    return -1;
#if defined(__x86_64__)
  {
    /* open = 5 → 0x2000005 on macOS x86_64 */
    register long r10 __asm__("r10") = 0644;
    __asm__ __volatile__("syscall"
                         : "=a"(r)
                         : "a"(0x2000005L), "D"(path), "S"(0x601L /* O_WRONLY|O_CREAT|O_TRUNC */), "d"(r10)
                         : "rcx", "r11", "memory");
  }
#elif defined(__aarch64__)
  {
    register long x16 __asm__("x16") = 5; /* SYS_open */
    register long x0 __asm__("x0") = (long)path;
    register long x1 __asm__("x1") = 0x601L; /* O_WRONLY|O_CREAT|O_TRUNC */
    register long x2 __asm__("x2") = 0644;
    register long failed __asm__("x9");
    __asm__ __volatile__("svc #0x80\n\t"
                         "cset %3, cs"
                         : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
                         : "r"(x16)
                         : "memory", "cc");
    if (failed)
      r = -x0;
    else
      r = x0;
  }
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/**
 * Darwin raw writev via syscall (SYS_writev = 121).
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline long xlang_io_writev(int fd, const void *iov, int iovcnt) {
  long r;
  if (iovcnt == 0)
    return 0;
  if (!iov)
    return -1;
#if defined(__x86_64__)
  {
    /* writev = 121 → 0x2000079 on macOS x86_64 */
    register long r10 __asm__("r10") = (long)iovcnt;
    __asm__ __volatile__("syscall"
                         : "=a"(r)
                         : "a"(0x2000079L), "D"(fd), "S"(iov), "d"(r10)
                         : "rcx", "r11", "memory");
  }
#elif defined(__aarch64__)
  {
    register long x16 __asm__("x16") = 121; /* SYS_writev */
    register long x0 __asm__("x0") = (long)fd;
    register long x1 __asm__("x1") = (long)iov;
    register long x2 __asm__("x2") = (long)iovcnt;
    register long failed __asm__("x9");
    __asm__ __volatile__("svc #0x80\n\t"
                         "cset %3, cs"
                         : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
                         : "r"(x16)
                         : "memory", "cc");
    if (failed)
      r = -x0;
    else
      r = x0;
  }
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

#else /* !LINUX Cap && !DARWIN Cap — POSIX libc thin wrappers */

#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h> /* 9.5.3: O_WRONLY/O_CREAT/O_TRUNC for xlang_io_open_write */

/** PLATFORM: POSIX fallback — libc write. */
static inline long xlang_io_write(int fd, const void *buf, size_t count) {
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
  return (long)write(fd, buf, count);
}

/**
 * Cap residual 9.5.3: open/create file for writing via libc open
 * (O_WRONLY|O_CREAT|O_TRUNC, mode 0644).
 * @param path NUL-terminated file path
 * @return new file descriptor, or -1 with errno
 * PLATFORM: POSIX fallback
 */
static inline int xlang_io_open_write(const char *path) {
  if (!path)
    return -1;
  return open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

/** PLATFORM: POSIX fallback — libc read. */
static inline long xlang_io_read(int fd, void *buf, size_t count) {
  if (count == 0)
    return 0;
  if (!buf)
    return -1;
  return (long)read(fd, buf, count);
}

/** PLATFORM: POSIX fallback — libc writev. */
static inline long xlang_io_writev(int fd, const void *iov, int iovcnt) {
  if (iovcnt == 0)
    return 0;
  if (!iov)
    return -1;
  return (long)writev(fd, (const struct iovec *)iov, iovcnt);
}

#endif /* LINUX Cap vs POSIX */

#endif /* !_WIN32 */

#endif /* XLANG_IO_CAP_H */
