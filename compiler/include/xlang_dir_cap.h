/*
 * xlang_dir_cap.h — Cap residual 9.1.10: opendir/readdir/closedir without libc
 * those symbols on Linux and Darwin.
 *
 * Single authority for:
 *   std.fs posix fs_libc_{opendir,readdir,closedir},
 *   xlang_fmt_{opendir,closedir,readdir_name},
 *   pipeline_abi cold sibling-dir scan.
 *
 * Linux: open(O_DIRECTORY) + getdents64 into a heap DIR stream; readdir fills a
 * glibc-layout dirent so DIRENT_D_NAME_OFF=19 stays valid for std.fs.
 * Darwin: open + getdirentries64 into a heap DIR stream; readdir fills a
 * Darwin-layout dirent so DIRENT_D_NAME_OFF=21 stays valid for std.fs.
 * Windows (MinGW/MSYS leftover PE SAT): _findfirst / _findnext / _findclose.
 *   fmt_check_cmd.from_x.c previously kept a second _findfirst copy
 *   (opendir_win / closedir_win returning void). Casting that void closedir
 *   to int32_t in xlang_fmt_closedir failed MinGW SAT, and full-seed
 *   walk_dir_collect_impl calls xlang_dir_open which the previous
 *   `#if !defined(_WIN32)` wrapper left undeclared. G.7 有则补全 this header —
 *   do not add a third Windows dir probe in the seed.
 *   Product user-fs on Windows stays std/fs/win32.x FindFirstFileA (different
 *   layer). pipeline_abi sibling-dir scan still skips Windows (product
 *   semantic at that layer; not changed here).
 *
 * Heap: malloc/free still host (Cap residual for allocator is separate).
 * Cap residual 9.1.9: syscall asm via xlang_syscall_cap.h (G.7).
 *
 * PLATFORM: SHARED Cap (9.1.10).
 */

#ifndef XLANG_DIR_CAP_H
#define XLANG_DIR_CAP_H

#if !defined(_WIN32) && !defined(_WIN64)

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <xlang_syscall_cap.h>

#ifndef O_RDONLY
#define O_RDONLY 0
#endif
/* Linux O_DIRECTORY */
#ifndef O_DIRECTORY
#define O_DIRECTORY 0200000
#endif

/** Cap residual 9.1.9: aliases → single syscall authority. */
#define xlang_dir_syscall3 xlang_syscall3
#define xlang_dir_syscall1 xlang_syscall1

/** Linux getdents64 directory entry (kernel layout). PLATFORM: LINUX */
struct xlang_linux_dirent64 {
  uint64_t d_ino;
  int64_t d_off;
  unsigned short d_reclen;
  unsigned char d_type;
  char d_name[];
};

/**
 * glibc x86_64/aarch64 struct dirent layout used by std.fs DIRENT_D_NAME_OFF=19.
 * PLATFORM: LINUX
 */
struct xlang_dirent_glibc {
  uint64_t d_ino;
  int64_t d_off;
  unsigned short d_reclen;
  unsigned char d_type;
  char d_name[256];
};

/** Opaque DIR stream (heap). PLATFORM: LINUX */
struct xlang_dir_stream {
  int fd;
  unsigned char *buf;
  size_t buf_cap;
  size_t buf_len;
  size_t buf_pos;
  struct xlang_dirent_glibc ent;
};

/** Map negative kernel ret to -1 + errno. PLATFORM: LINUX */
static inline int xlang_dir_ret(long r) {
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/**
 * Cap residual open(2) for directories (O_RDONLY|O_DIRECTORY).
 * PLATFORM: LINUX
 */
static inline int xlang_dir_sys_open_dir(const char *path) {
  long r;
  if (!path || !path[0])
    return -1;
#if defined(__x86_64__)
  /* open = 2 */
  r = xlang_dir_syscall3(2, (long)path, (long)(O_RDONLY | O_DIRECTORY), 0);
#elif defined(__aarch64__)
  /* openat = 56; AT_FDCWD = -100 */
  r = xlang_syscall4(56, (long)(-100), (long)path, (long)(O_RDONLY | O_DIRECTORY), 0);
#endif
  return xlang_dir_ret(r);
}

/**
 * Cap residual close(2).
 * PLATFORM: LINUX
 */
static inline int xlang_dir_sys_close(int fd) {
  long r;
#if defined(__x86_64__)
  /* close = 3 */
  r = xlang_dir_syscall1(3, (long)fd);
#elif defined(__aarch64__)
  /* close = 57 */
  r = xlang_dir_syscall1(57, (long)fd);
#endif
  return xlang_dir_ret(r);
}

/**
 * Cap residual getdents64(2).
 * @return bytes read, 0 EOF, -1 error
 * PLATFORM: LINUX
 */
static inline long xlang_dir_sys_getdents64(int fd, void *buf, size_t count) {
  long r;
#if defined(__x86_64__)
  /* getdents64 = 217 */
  r = xlang_dir_syscall3(217, (long)fd, (long)buf, (long)count);
#elif defined(__aarch64__)
  /* getdents64 = 61 */
  r = xlang_dir_syscall3(61, (long)fd, (long)buf, (long)count);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual opendir(3) — open + getdents64 buffer.
 * @return opaque DIR* or NULL
 * PLATFORM: LINUX
 */
static inline void *xlang_dir_open(const char *name) {
  struct xlang_dir_stream *d;
  int fd;
  if (!name || !name[0])
    return NULL;
  d = (struct xlang_dir_stream *)calloc(1, sizeof(*d));
  if (!d)
    return NULL;
  fd = xlang_dir_sys_open_dir(name);
  if (fd < 0) {
    free(d);
    return NULL;
  }
  d->fd = fd;
  d->buf_cap = 8192;
  d->buf = (unsigned char *)malloc(d->buf_cap);
  if (!d->buf) {
    (void)xlang_dir_sys_close(d->fd);
    free(d);
    return NULL;
  }
  return (void *)d;
}

/**
 * Cap residual readdir(3) — next glibc-layout dirent, or NULL at EOF/error.
 * d_name at byte 19 (matches std.fs DIRENT_D_NAME_OFF on Linux).
 * PLATFORM: LINUX
 */
static inline void *xlang_dir_read(void *dirp) {
  struct xlang_dir_stream *d = (struct xlang_dir_stream *)dirp;
  struct xlang_linux_dirent64 *de;
  size_t nlen;
  if (!d || d->fd < 0)
    return NULL;
  for (;;) {
    if (d->buf_pos >= d->buf_len) {
      long nr = xlang_dir_sys_getdents64(d->fd, d->buf, d->buf_cap);
      if (nr <= 0)
        return NULL;
      d->buf_len = (size_t)nr;
      d->buf_pos = 0;
    }
    if (d->buf_pos >= d->buf_len)
      return NULL;
    de = (struct xlang_linux_dirent64 *)(d->buf + d->buf_pos);
    d->buf_pos += de->d_reclen;
    if (de->d_name[0] == '\0')
      continue;
    d->ent.d_ino = de->d_ino;
    d->ent.d_off = de->d_off;
    d->ent.d_reclen = de->d_reclen;
    d->ent.d_type = de->d_type;
    nlen = 0;
    while (de->d_name[nlen] && nlen + 1 < sizeof(d->ent.d_name)) {
      d->ent.d_name[nlen] = de->d_name[nlen];
      nlen++;
    }
    d->ent.d_name[nlen] = '\0';
    return (void *)&d->ent;
  }
}

/**
 * Cap residual readdir name only (valid until next read/close).
 * PLATFORM: LINUX
 */
static inline char *xlang_dir_readdir_name(void *dirp) {
  struct xlang_dirent_glibc *ent = (struct xlang_dirent_glibc *)xlang_dir_read(dirp);
  return ent ? ent->d_name : (char *)0;
}

/**
 * Cap residual closedir(3).
 * PLATFORM: LINUX
 */
static inline int xlang_dir_close(void *dirp) {
  struct xlang_dir_stream *d = (struct xlang_dir_stream *)dirp;
  if (!d)
    return -1;
  if (d->fd >= 0)
    (void)xlang_dir_sys_close(d->fd);
  free(d->buf);
  free(d);
  return 0;
}

#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef O_RDONLY
#define O_RDONLY 0
#endif

#if defined(__aarch64__)
static inline long xlang_darwin_dir_sys1(long nr, long a1) {
  register long x16 __asm__("x16") = nr;
  register long x0 __asm__("x0") = a1;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %1, cs"
                       : "+r"(x0), "=r"(failed)
                       : "r"(x16)
                       : "memory", "cc");
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_dir_sys3(long nr, long a1, long a2, long a3) {
  register long x16 __asm__("x16") = nr;
  register long x0 __asm__("x0") = a1;
  register long x1 __asm__("x1") = a2;
  register long x2 __asm__("x2") = a3;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %1, cs"
                       : "+r"(x0), "=r"(failed)
                       : "r"(x16), "r"(x1), "r"(x2)
                       : "memory", "cc");
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_dir_sys4(long nr, long a1, long a2, long a3, long a4) {
  register long x16 __asm__("x16") = nr;
  register long x0 __asm__("x0") = a1;
  register long x1 __asm__("x1") = a2;
  register long x2 __asm__("x2") = a3;
  register long x3 __asm__("x3") = a4;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %1, cs"
                       : "+r"(x0), "=r"(failed)
                       : "r"(x16), "r"(x1), "r"(x2), "r"(x3)
                       : "memory", "cc");
  return failed ? -x0 : x0;
}
#elif defined(__x86_64__)
static inline long xlang_darwin_dir_sys1(long nr, long a1) {
  long r;
  long sys_nr = (nr >= 0x2000000L) ? nr : (0x2000000L | nr);
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "neg %%rax\n\t"
                       "1:"
                       : "=a"(r)
                       : "a"(sys_nr), "D"(a1)
                       : "rcx", "r11", "memory", "cc");
  return r;
}

static inline long xlang_darwin_dir_sys3(long nr, long a1, long a2, long a3) {
  long r;
  long sys_nr = (nr >= 0x2000000L) ? nr : (0x2000000L | nr);
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "neg %%rax\n\t"
                       "1:"
                       : "=a"(r)
                       : "a"(sys_nr), "D"(a1), "S"(a2), "d"(a3)
                       : "rcx", "r11", "memory", "cc");
  return r;
}

static inline long xlang_darwin_dir_sys4(long nr, long a1, long a2, long a3, long a4) {
  long r;
  long sys_nr = (nr >= 0x2000000L) ? nr : (0x2000000L | nr);
  register long r10 __asm__("r10") = a4;
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "neg %%rax\n\t"
                       "1:"
                       : "=a"(r)
                       : "a"(sys_nr), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
                       : "rcx", "r11", "memory", "cc");
  return r;
}
#endif

/** Darwin 64-bit kernel dirent layout. d_name at offset 21 (matches DIRENT_D_NAME_OFF on Darwin). PLATFORM: MACOS|DARWIN */
struct xlang_darwin_dirent64 {
  uint64_t d_ino;
  uint64_t d_seekoff;
  uint16_t d_reclen;
  uint16_t d_namlen;
  uint8_t  d_type;
  char     d_name[1024];
};

/** Opaque DIR stream on Darwin (heap). PLATFORM: MACOS|DARWIN */
struct xlang_dir_stream {
  int fd;
  unsigned char *buf;
  size_t buf_cap;
  size_t buf_len;
  size_t buf_pos;
  long basep;
  struct xlang_darwin_dirent64 ent;
};

/**
 * Cap residual opendir(3) on Darwin via raw syscall open (no libc opendir).
 * @return opaque DIR* or NULL
 * PLATFORM: MACOS|DARWIN
 */
static inline void *xlang_dir_open(const char *name) {
  struct xlang_dir_stream *d;
  long fd;
  if (!name || !name[0])
    return NULL;
  d = (struct xlang_dir_stream *)calloc(1, sizeof(*d));
  if (!d)
    return NULL;
#if defined(__x86_64__)
  fd = xlang_darwin_dir_sys3(0x2000005L, (long)name, O_RDONLY, 0);
#elif defined(__aarch64__)
  fd = xlang_darwin_dir_sys3(5, (long)name, O_RDONLY, 0);
#endif
  if (fd < 0) {
    free(d);
    return NULL;
  }
  d->fd = (int)fd;
  d->buf_cap = 8192;
  d->buf = (unsigned char *)malloc(d->buf_cap);
  if (!d->buf) {
#if defined(__x86_64__)
    (void)xlang_darwin_dir_sys1(0x2000006L, d->fd);
#elif defined(__aarch64__)
    (void)xlang_darwin_dir_sys1(6, d->fd);
#endif
    free(d);
    return NULL;
  }
  d->basep = 0;
  return (void *)d;
}

/**
 * Cap residual readdir(3) on Darwin via raw syscall 344 (SYS_getdirentries64, no libc readdir).
 * d_name at byte 21 (matches std.fs DIRENT_D_NAME_OFF on Darwin).
 * @return pointer to struct with d_name at offset 21, or NULL at EOF/error
 * PLATFORM: MACOS|DARWIN
 */
static inline void *xlang_dir_read(void *dirp) {
  struct xlang_dir_stream *d = (struct xlang_dir_stream *)dirp;
  if (!d || d->fd < 0)
    return NULL;
  for (;;) {
    if (d->buf_pos >= d->buf_len) {
      long nr;
#if defined(__x86_64__)
      nr = xlang_darwin_dir_sys4(0x2000158L, (long)d->fd, (long)d->buf, (long)d->buf_cap, (long)&d->basep);
#elif defined(__aarch64__)
      nr = xlang_darwin_dir_sys4(344, (long)d->fd, (long)d->buf, (long)d->buf_cap, (long)&d->basep);
#endif
      if (nr <= 0)
        return NULL;
      d->buf_len = (size_t)nr;
      d->buf_pos = 0;
    }
    if (d->buf_pos >= d->buf_len)
      return NULL;
    struct xlang_darwin_dirent64 *de = (struct xlang_darwin_dirent64 *)(d->buf + d->buf_pos);
    if (de->d_reclen == 0)
      return NULL;
    d->buf_pos += de->d_reclen;
    if (de->d_ino == 0 || de->d_name[0] == '\0')
      continue;
    memcpy(&d->ent, de, (size_t)de->d_reclen < sizeof(d->ent) ? (size_t)de->d_reclen : sizeof(d->ent));
    d->ent.d_name[sizeof(d->ent.d_name) - 1] = '\0';
    return (void *)&d->ent;
  }
}

/**
 * Cap residual readdir name only on Darwin (valid until next read/close).
 * PLATFORM: MACOS|DARWIN
 */
static inline char *xlang_dir_readdir_name(void *dirp) {
  struct xlang_darwin_dirent64 *ent = (struct xlang_darwin_dirent64 *)xlang_dir_read(dirp);
  return ent ? ent->d_name : (char *)0;
}

/**
 * Cap residual closedir(3) on Darwin via raw syscall close (no libc closedir).
 * @return 0 ok, -1 error
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_dir_close(void *dirp) {
  struct xlang_dir_stream *d = (struct xlang_dir_stream *)dirp;
  if (!d)
    return -1;
  if (d->fd >= 0) {
#if defined(__x86_64__)
    (void)xlang_darwin_dir_sys1(0x2000006L, d->fd);
#elif defined(__aarch64__)
    (void)xlang_darwin_dir_sys1(6, d->fd);
#endif
  }
  free(d->buf);
  free(d);
  return 0;
}

#else /* !LINUX && !DARWIN — POSIX libc thin wrappers fallback */

#include <dirent.h>

/** PLATFORM: POSIX fallback — libc opendir. */
static inline void *xlang_dir_open(const char *name) {
  if (!name)
    return NULL;
  return (void *)opendir(name);
}

/** PLATFORM: POSIX fallback — libc readdir (dirent*). */
static inline void *xlang_dir_read(void *dirp) {
  if (!dirp)
    return NULL;
  return (void *)readdir((DIR *)dirp);
}

/** PLATFORM: POSIX fallback — d_name from libc readdir. */
static inline char *xlang_dir_readdir_name(void *dirp) {
  struct dirent *ent;
  if (!dirp)
    return (char *)0;
  ent = readdir((DIR *)dirp);
  return ent ? ent->d_name : (char *)0;
}

/** PLATFORM: POSIX fallback — libc closedir. */
static inline int xlang_dir_close(void *dirp) {
  if (!dirp)
    return -1;
  return closedir((DIR *)dirp);
}

#endif /* LINUX vs DARWIN vs POSIX fallback */

#else /* _WIN32|_WIN64 — leftover PE / MinGW SAT compiles fmt rest */

/*
 * PLATFORM: WINDOWS — complete the existing dir-cap authority (G.7 有则补全).
 * MinGW CRT: _findfirst / _findnext / _findclose. closedir returns 0/-1
 * (POSIX xlang_dir_close contract) — do not use a void closedir_win helper.
 * Name-only stream: d_name is the first field of the opaque "dirent" so
 * fmt readdir_name consumers do not depend on glibc DIRENT_D_NAME_OFF=19.
 * POSIX gold path above is unchanged.
 */
#include <io.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef _A_SUBDIR
#define _A_SUBDIR 0x10
#endif

struct xlang_dir_win_ent {
  char d_name[260];
  unsigned char d_type;
};

struct xlang_dir_win_stream {
  intptr_t handle;
  struct _finddata_t fd;
  int first;
  int done;
  struct xlang_dir_win_ent ent;
};

/** PLATFORM: WINDOWS — MinGW _findfirst glob `path/*`. */
static inline void *xlang_dir_open(const char *name) {
  struct xlang_dir_win_stream *d;
  char pattern[512];
  size_t n = 0;
  if (!name || !name[0])
    return NULL;
  while (name[n] && n + 3 < sizeof(pattern)) {
    pattern[n] = name[n];
    n++;
  }
  if (name[n])
    return NULL;
  pattern[n++] = '/';
  pattern[n++] = '*';
  pattern[n] = '\0';
  d = (struct xlang_dir_win_stream *)calloc(1, sizeof(*d));
  if (!d)
    return NULL;
  d->handle = _findfirst(pattern, &d->fd);
  if (d->handle == (intptr_t)-1) {
    free(d);
    return NULL;
  }
  d->first = 1;
  d->done = 0;
  return (void *)d;
}

/** PLATFORM: WINDOWS — next d_name, or NULL at EOF/error. */
static inline char *xlang_dir_readdir_name(void *dirp) {
  struct xlang_dir_win_stream *d = (struct xlang_dir_win_stream *)dirp;
  size_t nlen;
  if (!d || d->handle == (intptr_t)-1 || d->done)
    return (char *)0;
  if (d->first) {
    d->first = 0;
  } else {
    if (_findnext(d->handle, &d->fd) != 0) {
      d->done = 1;
      return (char *)0;
    }
  }
  nlen = 0;
  while (d->fd.name[nlen] && nlen + 1 < sizeof(d->ent.d_name)) {
    d->ent.d_name[nlen] = d->fd.name[nlen];
    nlen++;
  }
  d->ent.d_name[nlen] = '\0';
  d->ent.d_type = (unsigned char)((d->fd.attrib & _A_SUBDIR) ? _A_SUBDIR : 0);
  return d->ent.d_name;
}

/** PLATFORM: WINDOWS — opaque dirent* whose first field is d_name. */
static inline void *xlang_dir_read(void *dirp) {
  if (!xlang_dir_readdir_name(dirp))
    return NULL;
  return (void *)&((struct xlang_dir_win_stream *)dirp)->ent;
}

/** PLATFORM: WINDOWS — _findclose + free; 0 ok, -1 null. */
static inline int xlang_dir_close(void *dirp) {
  struct xlang_dir_win_stream *d = (struct xlang_dir_win_stream *)dirp;
  if (!d)
    return -1;
  if (d->handle != (intptr_t)-1)
    (void)_findclose(d->handle);
  free(d);
  return 0;
}

#endif /* !_WIN32 */
#endif /* XLANG_DIR_CAP_H */
