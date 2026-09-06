/*
 * xlang_process_cap.h — Cap residual 9.1.3 / 9.1.4: process OS primitives
 * (getpid, getppid, chdir, getcwd, fork, execve, wait4, pipe, dup2, exit, execvp)
 * without libc.
 *
 * Single authority for std.process OS glue (process_*_impl) and runtime linker.
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Win32).
 */

#ifndef XLANG_PROCESS_CAP_H
#define XLANG_PROCESS_CAP_H

#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <xlang_syscall_cap.h>

#ifndef SIGCHLD
#define SIGCHLD 17
#endif

/** Cap residual 9.1.9: aliases → single syscall authority. */
#define xlang_proc_syscall6 xlang_syscall6
#define xlang_proc_syscall3 xlang_syscall3
#define xlang_proc_syscall1 xlang_syscall1

/**
 * Cap residual pipe(2): create pipe ends into fd[2].
 * @return 0 ok, -1 fail
 * PLATFORM: LINUX
 */
static inline int xlang_proc_pipe(int fd[2]) {
  long r;
  if (!fd)
    return -1;
#if defined(__x86_64__)
  /* pipe = 22; fills int fd[2] */
  r = xlang_proc_syscall1(22, (long)fd);
#elif defined(__aarch64__)
  /* pipe2 = 59, flags=0 */
  r = xlang_proc_syscall3(59, (long)fd, 0, 0);
#endif
  return r == 0 ? 0 : -1;
}

/**
 * Cap residual fork(2): return child pid in parent, 0 in child, -1 on error.
 * PLATFORM: LINUX — x86_64 fork; aarch64 clone(SIGCHLD).
 */
static inline long xlang_proc_fork(void) {
#if defined(__x86_64__)
  /* fork = 57 */
  return xlang_proc_syscall1(57, 0);
#elif defined(__aarch64__)
  /* clone = 220; flags=SIGCHLD, stack=0 → fork-like */
  return xlang_proc_syscall6(220, (long)SIGCHLD, 0, 0, 0, 0, 0);
#endif
}

/**
 * Cap residual execve(2). Does not return on success.
 * @return -1 on failure (caller should _exit)
 * PLATFORM: LINUX
 */
static inline int xlang_proc_execve(const char *path, char *const argv[], char *const envp[]) {
  long r;
#if defined(__x86_64__)
  /* execve = 59 */
  r = xlang_proc_syscall3(59, (long)path, (long)argv, (long)envp);
#elif defined(__aarch64__)
  /* execve = 221 */
  r = xlang_proc_syscall3(221, (long)path, (long)argv, (long)envp);
#endif
  (void)r;
  return -1;
}

/**
 * Cap residual wait4 → waitpid(pid, status, options) semantics (rusage ignored).
 * @return pid on success, -1 on failure
 * PLATFORM: LINUX
 */
static inline long xlang_proc_waitpid(long pid, int *status, int options) {
#if defined(__x86_64__)
  /* wait4 = 61 */
  return xlang_proc_syscall6(61, pid, (long)status, (long)options, 0, 0, 0);
#elif defined(__aarch64__)
  /* wait4 = 260 */
  return xlang_proc_syscall6(260, pid, (long)status, (long)options, 0, 0, 0);
#endif
}

/**
 * Cap residual _exit(2) / exit_group — never returns.
 * PLATFORM: LINUX
 */
static inline void xlang_proc_exit(int code) {
#if defined(__x86_64__)
  /* exit_group = 231 */
  (void)xlang_proc_syscall1(231, (long)code);
#elif defined(__aarch64__)
  /* exit_group = 94 */
  (void)xlang_proc_syscall1(94, (long)code);
#endif
  for (;;) {
  }
}

/**
 * Cap residual dup2(oldfd, newfd).
 * @return newfd on success, -1 on failure
 * PLATFORM: LINUX
 */
static inline int xlang_proc_dup2(int oldfd, int newfd) {
  long r;
#if defined(__x86_64__)
  /* dup2 = 33 */
  r = xlang_proc_syscall3(33, (long)oldfd, (long)newfd, 0);
#elif defined(__aarch64__)
  /* dup3 = 24, flags=0 */
  r = xlang_proc_syscall3(24, (long)oldfd, (long)newfd, 0);
#endif
  return (r < 0) ? -1 : (int)r;
}

#include <string.h>
#include <xlang_environ_cap.h>

/**
 * Cap residual execvp: PATH search then execve (no libc execvp/execlp).
 * @param file program name or path
 * @param argv NULL-terminated argv (argv[0] conventionally = file)
 * @return -1 on failure (does not return on success)
 * PLATFORM: LINUX — uses environ walk for PATH (9.1.1).
 */
static inline int xlang_proc_execvp(const char *file, char *const argv[]) {
  char buf[4096];
  const char *path;
  const char *p;
  const char *q;
  size_t flen;
  size_t dlen;
  extern char **environ;
  if (!file || !file[0])
    return -1;
  if (strchr(file, '/')) {
    (void)xlang_proc_execve(file, argv, environ);
    return -1;
  }
  path = xlang_environ_getenv("PATH");
  if (!path || !path[0])
    path = "/bin:/usr/bin";
  flen = strlen(file);
  p = path;
  for (;;) {
    q = p;
    while (*q && *q != ':')
      q++;
    dlen = (size_t)(q - p);
    if (dlen + 1 + flen + 1 <= sizeof(buf)) {
      if (dlen == 0) {
        memcpy(buf, file, flen + 1);
      } else {
        memcpy(buf, p, dlen);
        buf[dlen] = '/';
        memcpy(buf + dlen + 1, file, flen + 1);
      }
      (void)xlang_proc_execve(buf, argv, environ);
    }
    if (*q != ':')
      break;
    p = q + 1;
  }
  return -1;
}

/** Linux EINTR raw errno value for wait4 retry loops. */
#ifndef EINTR
#define EINTR 4
#endif

/**
 * Cap residual 9.1.3: getpid(2).
 * @return current process ID
 * PLATFORM: LINUX
 */
static inline long xlang_proc_getpid(void) {
#if defined(__x86_64__)
  /* getpid = 39 */
  return xlang_proc_syscall1(39, 0);
#elif defined(__aarch64__)
  /* getpid = 172 */
  return xlang_proc_syscall1(172, 0);
#endif
}

/**
 * Cap residual 9.1.3: getppid(2).
 * @return parent process ID
 * PLATFORM: LINUX
 */
static inline long xlang_proc_getppid(void) {
#if defined(__x86_64__)
  /* getppid = 110 */
  return xlang_proc_syscall1(110, 0);
#elif defined(__aarch64__)
  /* getppid = 173 */
  return xlang_proc_syscall1(173, 0);
#endif
}

/**
 * Cap residual 9.1.3: chdir(2).
 * @param path directory path
 * @return 0 on success, -1 on failure
 * PLATFORM: LINUX
 */
static inline int xlang_proc_chdir(const char *path) {
  long r;
  if (!path || !path[0])
    return -1;
#if defined(__x86_64__)
  /* chdir = 80 */
  r = xlang_proc_syscall1(80, (long)path);
#elif defined(__aarch64__)
  /* chdir = 49 */
  r = xlang_proc_syscall1(49, (long)path);
#endif
  return (r == 0) ? 0 : -1;
}

/**
 * Cap residual 9.1.3: getcwd(2).
 * @param buf output buffer
 * @param size buffer capacity
 * @return bytes placed into buf including NUL on success, -1 on failure
 * PLATFORM: LINUX
 */
static inline long xlang_proc_getcwd(char *buf, size_t size) {
  long r;
  if (!buf || size < 2)
    return -1;
#if defined(__x86_64__)
  /* getcwd = 79 */
  r = xlang_syscall2(79, (long)buf, (long)size);
#elif defined(__aarch64__)
  /* getcwd = 17 */
  r = xlang_syscall2(17, (long)buf, (long)size);
#endif
  return (r <= 0) ? -1 : r;
}

#elif defined(_WIN32) || defined(_WIN64)

#include <fcntl.h>
#include <io.h>
#include <stddef.h>
#include <stdint.h>
#include <windows.h>

#ifndef WIFEXITED
#define WIFEXITED(status) (((status) & 0x7f) == 0)
#endif
#ifndef WEXITSTATUS
#define WEXITSTATUS(status) (((status) >> 8) & 0xff)
#endif

/**
 * Cap residual 9.1.4: pipe on Windows via Win32 CreatePipe + _open_osfhandle.
 * @return 0 ok, -1 fail
 * PLATFORM: WINDOWS
 */
static inline int xlang_proc_pipe(int fd[2]) {
  SECURITY_ATTRIBUTES sa;
  HANDLE r = NULL;
  HANDLE w = NULL;
  if (!fd)
    return -1;
  memset(&sa, 0, sizeof(sa));
  sa.nLength = sizeof(sa);
  sa.bInheritHandle = TRUE;
  if (!CreatePipe(&r, &w, &sa, 0))
    return -1;
  SetHandleInformation(r, HANDLE_FLAG_INHERIT, 0);
  fd[0] = (int)_open_osfhandle((intptr_t)r, _O_RDONLY);
  fd[1] = (int)_open_osfhandle((intptr_t)w, _O_WRONLY);
  if (fd[0] < 0 || fd[1] < 0)
    return -1;
  return 0;
}

/**
 * Cap residual 9.1.4: waitpid on Windows via OpenProcess + WaitForSingleObject + GetExitCodeProcess.
 * @return pid on success, -1 on failure
 * PLATFORM: WINDOWS
 */
static inline long xlang_proc_waitpid(long pid, int *status, int options) {
  HANDLE h;
  DWORD code = 0;
  (void)options;
  if (pid <= 0)
    return -1;
  h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE, FALSE, (DWORD)(uint32_t)pid);
  if (h == NULL)
    return -1;
  if (WaitForSingleObject(h, INFINITE) != WAIT_OBJECT_0) {
    CloseHandle(h);
    return -1;
  }
  if (!GetExitCodeProcess(h, &code)) {
    CloseHandle(h);
    return -1;
  }
  CloseHandle(h);
  if (status)
    *status = ((int)code & 0xff) << 8; /* POSIX WEXITSTATUS compat: (status >> 8) & 0xff */
  return pid;
}

/**
 * Cap residual 9.1.4: exit on Windows via Win32 ExitProcess.
 * PLATFORM: WINDOWS
 */
static inline void xlang_proc_exit(int code) {
  ExitProcess((UINT)code);
  for (;;) {
  }
}

/**
 * Cap residual 9.1.3: getpid on Windows via Win32 GetCurrentProcessId.
 * @return current process ID
 * PLATFORM: WINDOWS
 */
static inline long xlang_proc_getpid(void) {
  return (long)(intptr_t)GetCurrentProcessId();
}

/**
 * Cap residual 9.1.3: getppid on Windows (unsupported; returns -1).
 * @return -1
 * PLATFORM: WINDOWS
 */
static inline long xlang_proc_getppid(void) {
  return -1;
}

/**
 * Cap residual 9.1.3: chdir on Windows via Win32 SetCurrentDirectoryA.
 * @param path directory path
 * @return 0 on success, -1 on failure
 * PLATFORM: WINDOWS
 */
static inline int xlang_proc_chdir(const char *path) {
  if (!path || !path[0])
    return -1;
  return SetCurrentDirectoryA(path) ? 0 : -1;
}

/**
 * Cap residual 9.1.3: getcwd on Windows via Win32 GetCurrentDirectoryA.
 * @param buf output buffer
 * @param size buffer capacity
 * @return bytes placed into buf including NUL on success, -1 on failure
 * PLATFORM: WINDOWS
 */
static inline long xlang_proc_getcwd(char *buf, size_t size) {
  DWORD n;
  if (!buf || size < 2)
    return -1;
  n = GetCurrentDirectoryA((DWORD)size, buf);
  if (n == 0 || n >= (DWORD)size)
    return -1;
  return (long)(n + 1);
}

#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <xlang_environ_cap.h>

#ifndef SIGCHLD
#define SIGCHLD 20
#endif

#ifndef EINTR
#define EINTR 4
#endif

#ifndef WIFEXITED
#define WIFEXITED(status) (((status) & 0x7f) == 0)
#endif
#ifndef WEXITSTATUS
#define WEXITSTATUS(status) (((status) >> 8) & 0xff)
#endif

#if defined(__aarch64__)
static inline long xlang_darwin_proc_sys0(long nr) {
  register long x16 __asm__("x16") = nr;
  register long x0 __asm__("x0") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %1, cs"
                       : "+r"(x0), "=r"(failed)
                       : "r"(x16)
                       : "memory", "cc");
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_proc_sys1(long nr, long a1) {
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

static inline long xlang_darwin_proc_sys3(long nr, long a1, long a2, long a3) {
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

static inline long xlang_darwin_proc_sys4(long nr, long a1, long a2, long a3, long a4) {
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
static inline long xlang_darwin_proc_sys0(long nr) {
  long r;
  long sys_nr = (nr >= 0x2000000L) ? nr : (0x2000000L | nr);
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "neg %%rax\n\t"
                       "1:"
                       : "=a"(r)
                       : "a"(sys_nr)
                       : "rcx", "r11", "memory", "cc");
  return r;
}

static inline long xlang_darwin_proc_sys1(long nr, long a1) {
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

static inline long xlang_darwin_proc_sys3(long nr, long a1, long a2, long a3) {
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

static inline long xlang_darwin_proc_sys4(long nr, long a1, long a2, long a3, long a4) {
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

/**
 * Cap residual 9.1.4: pipe(2) on Darwin via raw syscall 42 / 0x200002aL (no libc pipe).
 * @return 0 ok, -1 fail
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_pipe(int fd[2]) {
  if (!fd)
    return -1;
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 42; /* SYS_pipe */
  register long x0 __asm__("x0") = 0;
  register long x1 __asm__("x1") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %2, cs"
                       : "+r"(x0), "+r"(x1), "=r"(failed)
                       : "r"(x16)
                       : "memory", "cc");
  if (failed)
    return -1;
  fd[0] = (int)x0;
  fd[1] = (int)x1;
  return 0;
#elif defined(__x86_64__)
  long rax = 0x200002aL; /* SYS_pipe */
  long rdx = 0;
  int err = 0;
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "mov $1, %2\n\t"
                       "1:"
                       : "+a"(rax), "=d"(rdx), "=r"(err)
                       :
                       : "rcx", "r11", "memory", "cc");
  if (err)
    return -1;
  fd[0] = (int)rax;
  fd[1] = (int)rdx;
  return 0;
#endif
}

/**
 * Cap residual 9.1.4: fork(2) on Darwin via raw syscall 2 / 0x2000002L (no libc fork).
 * @return child pid in parent, 0 in child, -1 on error
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_proc_fork(void) {
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 2; /* SYS_fork */
  register long x0 __asm__("x0") = 0;
  register long x1 __asm__("x1") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__("svc #0x80\n\t"
                       "cset %2, cs"
                       : "+r"(x0), "+r"(x1), "=r"(failed)
                       : "r"(x16)
                       : "memory", "cc");
  if (failed)
    return -1;
  if (x1 == 1)
    return 0; /* child */
  return x0;  /* parent: child pid */
#elif defined(__x86_64__)
  long rax = 0x2000002L; /* SYS_fork */
  long rdx = 0;
  int err = 0;
  __asm__ __volatile__("syscall\n\t"
                       "jnc 1f\n\t"
                       "mov $1, %2\n\t"
                       "1:"
                       : "+a"(rax), "=d"(rdx), "=r"(err)
                       :
                       : "rcx", "r11", "memory", "cc");
  if (err)
    return -1;
  if (rdx == 1)
    return 0; /* child */
  return rax; /* parent: child pid */
#endif
}

/**
 * Cap residual 9.1.4: execve(2) on Darwin via raw syscall 59 / 0x200003bL (no libc execve).
 * @return -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_execve(const char *path, char *const argv[], char *const envp[]) {
  long r;
#if defined(__aarch64__)
  r = xlang_darwin_proc_sys3(59, (long)path, (long)argv, (long)envp);
#elif defined(__x86_64__)
  r = xlang_darwin_proc_sys3(0x200003bL, (long)path, (long)argv, (long)envp);
#endif
  (void)r;
  return -1;
}

/**
 * Cap residual 9.1.4: wait4 on Darwin via raw syscall 7 / 0x2000007L (no libc waitpid).
 * @return pid on success, -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_proc_waitpid(long pid, int *status, int options) {
#if defined(__aarch64__)
  return xlang_darwin_proc_sys4(7, pid, (long)status, (long)options, 0);
#elif defined(__x86_64__)
  return xlang_darwin_proc_sys4(0x2000007L, pid, (long)status, (long)options, 0);
#endif
}

/**
 * Cap residual 9.1.4: _exit(2) on Darwin via raw syscall 1 / 0x2000001L (no libc _exit).
 * PLATFORM: MACOS|DARWIN
 */
static inline void xlang_proc_exit(int code) {
#if defined(__aarch64__)
  (void)xlang_darwin_proc_sys1(1, (long)code);
#elif defined(__x86_64__)
  (void)xlang_darwin_proc_sys1(0x2000001L, (long)code);
#endif
  for (;;) {
  }
}

/**
 * Cap residual 9.1.4: dup2(2) on Darwin via raw syscall 90 / 0x200005aL (no libc dup2).
 * @return newfd on success, -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_dup2(int oldfd, int newfd) {
  long r;
#if defined(__aarch64__)
  r = xlang_darwin_proc_sys3(90, (long)oldfd, (long)newfd, 0);
#elif defined(__x86_64__)
  r = xlang_darwin_proc_sys3(0x200005aL, (long)oldfd, (long)newfd, 0);
#endif
  return (r < 0) ? -1 : (int)r;
}

/**
 * Cap residual 9.1.4: execvp on Darwin via PATH search + execve (no libc execvp).
 * @return -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_execvp(const char *file, char *const argv[]) {
  char buf[4096];
  const char *path;
  const char *p;
  const char *q;
  size_t flen;
  size_t dlen;
  if (!file || !file[0])
    return -1;
  if (strchr(file, '/')) {
    (void)xlang_proc_execve(file, argv, environ);
    return -1;
  }
  path = xlang_environ_getenv("PATH");
  if (!path || !path[0])
    path = "/usr/bin:/bin:/usr/sbin:/sbin";
  flen = strlen(file);
  p = path;
  for (;;) {
    q = p;
    while (*q && *q != ':')
      q++;
    dlen = (size_t)(q - p);
    if (dlen + 1 + flen + 1 <= sizeof(buf)) {
      if (dlen == 0) {
        memcpy(buf, file, flen + 1);
      } else {
        memcpy(buf, p, dlen);
        buf[dlen] = '/';
        memcpy(buf + dlen + 1, file, flen + 1);
      }
      (void)xlang_proc_execve(buf, argv, environ);
    }
    if (*q != ':')
      break;
    p = q + 1;
  }
  return -1;
}

/**
 * Cap residual 9.1.3: getpid(2) on Darwin via raw syscall (no libc getpid).
 * @return current process ID
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_proc_getpid(void) {
#if defined(__x86_64__)
  return xlang_darwin_proc_sys0(0x2000014L);
#elif defined(__aarch64__)
  return xlang_darwin_proc_sys0(20);
#endif
}

/**
 * Cap residual 9.1.3: getppid(2) on Darwin via raw syscall (no libc getppid).
 * @return parent process ID
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_proc_getppid(void) {
#if defined(__x86_64__)
  return xlang_darwin_proc_sys0(0x2000027L);
#elif defined(__aarch64__)
  return xlang_darwin_proc_sys0(39);
#endif
}

/**
 * Cap residual 9.1.3: chdir(2) on Darwin via raw syscall (no libc chdir).
 * @param path directory path
 * @return 0 on success, -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline int xlang_proc_chdir(const char *path) {
  long r;
  if (!path || !path[0])
    return -1;
#if defined(__x86_64__)
  r = xlang_darwin_proc_sys1(0x200000cL, (long)path);
#elif defined(__aarch64__)
  r = xlang_darwin_proc_sys1(12, (long)path);
#endif
  return (r == 0) ? 0 : -1;
}

/**
 * Cap residual 9.1.3: getcwd on Darwin via raw syscall open(".") + fcntl(F_GETPATH) + close (no libc getcwd).
 * @param buf output buffer
 * @param size buffer capacity
 * @return bytes placed into buf including NUL on success, -1 on failure
 * PLATFORM: MACOS|DARWIN
 */
static inline long xlang_proc_getcwd(char *buf, size_t size) {
  long fd;
  long r;
  size_t len;
  if (!buf || size < 2)
    return -1;
#if defined(__x86_64__)
  fd = xlang_darwin_proc_sys3(0x2000005L, (long)".", O_RDONLY, 0);
  if (fd < 0)
    return -1;
  r = xlang_darwin_proc_sys3(0x200005cL, fd, 50 /* F_GETPATH */, (long)buf);
  (void)xlang_darwin_proc_sys1(0x2000006L, fd);
#elif defined(__aarch64__)
  fd = xlang_darwin_proc_sys3(5, (long)".", O_RDONLY, 0);
  if (fd < 0)
    return -1;
  r = xlang_darwin_proc_sys3(92, fd, 50 /* F_GETPATH */, (long)buf);
  (void)xlang_darwin_proc_sys1(6, fd);
#endif
  if (r < 0)
    return -1;
  len = strlen(buf);
  if (len + 1 > size)
    return -1;
  return (long)(len + 1);
}

#else /* POSIX fallback */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xlang_environ_cap.h>

#ifndef EINTR
#define EINTR 4
#endif

#ifndef WIFEXITED
#define WIFEXITED(status) (((status) & 0x7f) == 0)
#endif
#ifndef WEXITSTATUS
#define WEXITSTATUS(status) (((status) >> 8) & 0xff)
#endif

static inline int xlang_proc_pipe(int fd[2]) {
  if (!fd)
    return -1;
  return pipe(fd);
}

static inline long xlang_proc_fork(void) {
  return (long)fork();
}

static inline int xlang_proc_execve(const char *path, char *const argv[], char *const envp[]) {
  return execve(path, argv, envp);
}

static inline long xlang_proc_waitpid(long pid, int *status, int options) {
  return (long)waitpid((pid_t)pid, status, options);
}

static inline void xlang_proc_exit(int code) {
  _exit(code);
}

static inline int xlang_proc_dup2(int oldfd, int newfd) {
  return dup2(oldfd, newfd);
}

static inline int xlang_proc_execvp(const char *file, char *const argv[]) {
  char buf[4096];
  const char *path;
  const char *p;
  const char *q;
  size_t flen;
  size_t dlen;
  if (!file || !file[0])
    return -1;
  if (strchr(file, '/')) {
    (void)xlang_proc_execve(file, argv, environ);
    return -1;
  }
  path = xlang_environ_getenv("PATH");
  if (!path || !path[0])
    path = "/bin:/usr/bin";
  flen = strlen(file);
  p = path;
  for (;;) {
    q = p;
    while (*q && *q != ':')
      q++;
    dlen = (size_t)(q - p);
    if (dlen + 1 + flen + 1 <= sizeof(buf)) {
      if (dlen == 0) {
        memcpy(buf, file, flen + 1);
      } else {
        memcpy(buf, p, dlen);
        buf[dlen] = '/';
        memcpy(buf + dlen + 1, file, flen + 1);
      }
      (void)xlang_proc_execve(buf, argv, environ);
    }
    if (*q != ':')
      break;
    p = q + 1;
  }
  return -1;
}

static inline long xlang_proc_getpid(void) {
  return (long)getpid();
}

static inline long xlang_proc_getppid(void) {
  return (long)getppid();
}

static inline int xlang_proc_chdir(const char *path) {
  if (!path || !path[0])
    return -1;
  return chdir(path) == 0 ? 0 : -1;
}

static inline long xlang_proc_getcwd(char *buf, size_t size) {
  char *p;
  size_t len;
  if (!buf || size < 2)
    return -1;
  p = getcwd(buf, size);
  if (!p)
    return -1;
  len = strlen(buf);
  return (long)(len + 1);
}

#endif /* platform */

#endif /* XLANG_PROCESS_CAP_H */
