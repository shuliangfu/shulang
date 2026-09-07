/*
 * xlang_proc_cap.h — Cap residual 9.1.12: read small pseudo-files (/proc/cpuinfo, config)
 * without libc fopen/fread across all platforms.
 *
 * Single authority for target_cpu /proc/cpuinfo and similar system file reads.
 * Raw syscalls on Linux and Darwin; _open/_read/_close on Windows.
 *
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS | POSIX)
 */

#ifndef XLANG_PROC_CAP_H
#define XLANG_PROC_CAP_H

#include <stddef.h>
#include <stdint.h>
#include <xlang_io_cap.h>

#if defined(__linux__)
#include <fcntl.h>
#include <xlang_syscall_cap.h>

#if defined(__x86_64__)
#define XLANG_PROC_SYS_open(path) ((int)xlang_syscall3(2, (long)(path), (long)O_RDONLY, 0))
#define XLANG_PROC_SYS_close(fd)  ((int)xlang_syscall1(3, (long)(fd)))
#elif defined(__aarch64__)
#ifndef AT_FDCWD
#define AT_FDCWD (-100)
#endif
#define XLANG_PROC_SYS_open(path) \
  ((int)xlang_syscall4(56, (long)AT_FDCWD, (long)(path), (long)O_RDONLY, 0))
#define XLANG_PROC_SYS_close(fd)  ((int)xlang_syscall1(57, (long)(fd)))
#else
#define XLANG_PROC_SYS_open(path) open((path), O_RDONLY)
#define XLANG_PROC_SYS_close(fd)  close(fd)
#endif

#elif defined(__APPLE__)

/**
 * Raw syscall open on Darwin (SYS_open = 5).
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_darwin_open_ro(const char *path) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 5; /* SYS_open */
  register long x0 __asm__("x0") = (long)path;
  register long x1 __asm__("x1") = 0;   /* O_RDONLY */
  register long x2 __asm__("x2") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %3, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -1 : (int)x0;
#elif defined(__x86_64__)
  long ret;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "movq $-1, %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000005L), "D"(path), "S"(0), "d"(0)
      : "rcx", "r11", "memory", "cc"
  );
  return (int)ret;
#else
  return -1;
#endif
}

/**
 * Raw syscall close on Darwin (SYS_close = 6).
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_darwin_close(int fd) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 6; /* SYS_close */
  register long x0 __asm__("x0") = (long)fd;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %1, cs"
      : "+r"(x0), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -1 : 0;
#elif defined(__x86_64__)
  long ret;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "movq $-1, %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000006L), "D"((long)fd)
      : "rcx", "r11", "memory", "cc"
  );
  return (int)ret;
#else
  return -1;
#endif
}

#elif defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>

/**
 * Open file read-only on Windows via CRT _open.
 * PLATFORM: WINDOWS
 */
static inline int xlang_proc_win_open_ro(const char *path) {
  return _open(path, _O_RDONLY | _O_BINARY);
}

/**
 * Close file descriptor on Windows via CRT _close.
 * PLATFORM: WINDOWS
 */
static inline int xlang_proc_win_close(int fd) {
  return _close(fd);
}

#else
#include <fcntl.h>
#include <unistd.h>

static inline int xlang_proc_posix_open_ro(const char *path) {
  return open(path, O_RDONLY);
}

static inline int xlang_proc_posix_close(int fd) {
  return close(fd);
}

#endif

/**
 * Open path read-only via Cap interface (raw syscall on Linux & Darwin, _open on Windows).
 * @param path File path to open
 * @return File descriptor or -1 on error
 * PLATFORM: SHARED
 */
static inline int xlang_proc_open_ro(const char *path) {
  if (!path || !path[0])
    return -1;
#if defined(__linux__)
  return XLANG_PROC_SYS_open(path);
#elif defined(__APPLE__)
  return xlang_proc_darwin_open_ro(path);
#elif defined(_WIN32) || defined(_WIN64)
  return xlang_proc_win_open_ro(path);
#else
  return xlang_proc_posix_open_ro(path);
#endif
}

/**
 * Close file descriptor via Cap interface.
 * @param fd File descriptor to close
 * @return 0 on success, -1 on error
 * PLATFORM: SHARED
 */
static inline int xlang_proc_close_fd(int fd) {
  if (fd < 0)
    return -1;
#if defined(__linux__)
  return XLANG_PROC_SYS_close(fd);
#elif defined(__APPLE__)
  return xlang_proc_darwin_close(fd);
#elif defined(_WIN32) || defined(_WIN64)
  return xlang_proc_win_close(fd);
#else
  return xlang_proc_posix_close(fd);
#endif
}

/**
 * Read a small pseudo-file (e.g. /proc/cpuinfo, /etc/hosts) into buf; NUL-terminate.
 * Uses xlang_io_read which routes to raw syscall on Linux & Darwin.
 * @param path File path
 * @param buf Output buffer
 * @param cap Capacity of buf in bytes
 * @return bytes read (excluding NUL), or -1 on error
 * PLATFORM: SHARED
 */
static inline long xlang_proc_read_file(const char *path, char *buf, size_t cap) {
  int fd;
  long n;
  long off;
  if (!path || !buf || cap < 2)
    return -1;
  fd = xlang_proc_open_ro(path);
  if (fd < 0)
    return -1;
  off = 0;
  while ((size_t)off + 1 < cap) {
    n = xlang_io_read(fd, buf + off, cap - 1 - (size_t)off);
    if (n < 0) {
      (void)xlang_proc_close_fd(fd);
      return -1;
    }
    if (n == 0)
      break;
    off += n;
  }
  (void)xlang_proc_close_fd(fd);
  buf[off] = '\0';
  return off;
}

/**
 * Bounded whole-file read with loud truncation signal.
 * Like xlang_proc_read_file (chunked, seek-free, NUL-terminated) but a file
 * larger than cap-1 bytes is rejected instead of silently truncated: after
 * the buffer fills to cap-1, one probe byte is read — if it succeeds the
 * file does not fit and -2 is returned so callers fail loudly (generated-code
 * patchers, argv scanners) rather than consume partial content.
 * @param path File path
 * @param buf Output buffer
 * @param cap Capacity of buf in bytes
 * @return bytes read (excluding NUL), -1 on open/read error, -2 if truncated
 * PLATFORM: SHARED
 */
static inline long xlang_proc_read_file_bounded(const char *path, char *buf, size_t cap) {
  int fd;
  long n;
  long off;
  char probe;
  if (!path || !buf || cap < 2)
    return -1;
  fd = xlang_proc_open_ro(path);
  if (fd < 0)
    return -1;
  off = 0;
  while ((size_t)off + 1 < cap) {
    n = xlang_io_read(fd, buf + off, cap - 1 - (size_t)off);
    if (n < 0) {
      (void)xlang_proc_close_fd(fd);
      return -1;
    }
    if (n == 0)
      break;
    off += n;
  }
  /* Truncation probe: buffer filled to cap-1 — one more readable byte means
   * the file exceeds the bound; report -2 and do not hand out partial data. */
  if ((size_t)off + 1 >= cap) {
    n = xlang_io_read(fd, &probe, 1);
    if (n > 0) {
      (void)xlang_proc_close_fd(fd);
      return -2;
    }
  }
  (void)xlang_proc_close_fd(fd);
  buf[off] = '\0';
  return off;
}

/**
 * Split in-place buffer at first '\n'; returns next line or NULL.
 * @param line Pointer to start of current line
 * @return Pointer to next line or NULL if end of string
 * PLATFORM: SHARED
 */
static inline char *xlang_proc_next_line(char *line) {
  char *nl;
  if (!line)
    return NULL;
  nl = line;
  while (*nl && *nl != '\n')
    nl++;
  if (*nl == '\n') {
    *nl = '\0';
    return nl + 1;
  }
  return NULL;
}

#endif /* XLANG_PROC_CAP_H */
