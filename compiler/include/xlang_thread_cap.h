/*
 * xlang_thread_cap.h — Cap residual 10.6.1: Linux futex + mmap stack + clone
 * without libpthread (x86_64 + aarch64).
 *
 * G.7: single authority for thread-primitive Cap faces. Uses xlang_syscall_cap.h
 * only — no libc futex/mmap/pthread wrappers on the Cap path.
 *
 * Slice0: futex wait/wake + anonymous stack mmap/munmap.
 * Slice1: clone trampoline spawn/join (child never C-continues after clone).
 *         Raw xlang_clone / xlang_clone3 helpers kept for Cap faces.
 * Slice2: product runtime_thread_glue Linux spawn/join/pool → Cap.
 * 10.6.2 slice0: Windows CreateThread / WaitForSingleObject Cap spawn/join.
 *
 * Darwin: Cap residual 10.6.1 POSIX pthread spawn/join.
 *
 * PLATFORM: LINUX primary (x86_64 + aarch64) · WINDOWS Cap spawn/join · DARWIN Cap spawn/join.
 */

#ifndef XLANG_THREAD_CAP_H
#define XLANG_THREAD_CAP_H

#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include <xlang_syscall_cap.h>

/** FUTEX_WAIT — sleep while *uaddr == val. */
#define XLANG_FUTEX_WAIT 0
/** FUTEX_WAKE — wake up to n waiters. */
#define XLANG_FUTEX_WAKE 1

/** PROT_READ|PROT_WRITE */
#define XLANG_PROT_RW 3
/** MAP_PRIVATE|MAP_ANONYMOUS (Linux). */
#define XLANG_MAP_PRIV_ANON 0x22
/** MAP_STACK (Linux) — hint for thread stacks. */
#define XLANG_MAP_STACK 0x20000

/* clone flags (linux/sched.h) — Cap mirror; avoid pulling libc headers. */
#define XLANG_CLONE_VM 0x00000100u
#define XLANG_CLONE_FS 0x00000200u
#define XLANG_CLONE_FILES 0x00000400u
#define XLANG_CLONE_SIGHAND 0x00000800u
#define XLANG_CLONE_THREAD 0x00010000u
#define XLANG_CLONE_SYSVSEM 0x00040000u
#define XLANG_CLONE_PARENT_SETTID 0x00100000u
#define XLANG_CLONE_CHILD_CLEARTID 0x00200000u

/** Default pthread-like thread flags (no TLS). */
#define XLANG_CLONE_THREAD_FLAGS                                               \
  (XLANG_CLONE_VM | XLANG_CLONE_FS | XLANG_CLONE_FILES | XLANG_CLONE_SIGHAND |  \
   XLANG_CLONE_THREAD | XLANG_CLONE_SYSVSEM | XLANG_CLONE_PARENT_SETTID |      \
   XLANG_CLONE_CHILD_CLEARTID)

/**
 * Cap timespec twin (avoid pulling libc time.h layouts into Cap face).
 * PLATFORM: LINUX LP64 — matches kernel timespec.
 */
struct xlang_thread_timespec {
  long tv_sec;
  long tv_nsec;
};

/**
 * clone3 args VER0 (64 bytes) — mirrors linux/sched.h struct clone_args.
 * PLATFORM: LINUX
 */
struct xlang_clone_args {
  uint64_t flags;
  uint64_t pidfd;
  uint64_t child_tid;
  uint64_t parent_tid;
  uint64_t exit_signal;
  uint64_t stack;
  uint64_t stack_size;
  uint64_t tls;
};

/**
 * Join handle filled by xlang_thread_spawn; wait with xlang_thread_join.
 * PLATFORM: LINUX
 */
struct xlang_thread_join {
  uint32_t done; /* 0 running · 1 finished (futex word) */
  int child_tid; /* CLONE_CHILD_CLEARTID / PARENT_SETTID */
  void *stack;
  size_t stack_len;
};

/** Start routine for Cap spawn (pthread-compatible shape). */
typedef void *(*xlang_thread_start_fn)(void *arg);

/**
 * Pack living in shared VM for child after clone (bottom of stack mapping).
 * PLATFORM: LINUX
 */
struct xlang_thread_spawn_pack {
  xlang_thread_start_fn fn;
  void *arg;
  struct xlang_thread_join *join;
};

/**
 * Raw futex(2). Returns 0 on success; -1 with errno on failure.
 * @param uaddr word address (must be 4-byte aligned)
 * @param op XLANG_FUTEX_WAIT / XLANG_FUTEX_WAKE
 * @param val expected value (WAIT) or wake count (WAKE)
 * @param timeout NULL = forever (WAIT only); ignored for WAKE
 * PLATFORM: LINUX
 */
static inline long xlang_futex(uint32_t *uaddr, int op, uint32_t val,
                               const struct xlang_thread_timespec *timeout) {
  long r;
  long nr;
  if (uaddr == 0) {
    errno = EFAULT;
    return -1;
  }
#if defined(__x86_64__)
  nr = 202; /* SYS_futex */
#elif defined(__aarch64__)
  nr = 98; /* SYS_futex */
#endif
  /* futex(uaddr, op, val, timeout, uaddr2=NULL, val3=0) */
  r = xlang_syscall6(nr, (long)uaddr, (long)op, (long)val, (long)timeout, 0, 0);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * FUTEX_WAIT with absolute-ish relative timeout in nanoseconds (best-effort).
 * timeout_ns <= 0 → wait forever.
 * @return 0 woken; -1 with errno (ETIMEDOUT / EAGAIN / …)
 * PLATFORM: LINUX
 */
static inline long xlang_futex_wait_timeout_ns(uint32_t *uaddr, uint32_t expected,
                                              int64_t timeout_ns) {
  struct xlang_thread_timespec ts;
  const struct xlang_thread_timespec *pto = 0;
  if (timeout_ns > 0) {
    ts.tv_sec = (long)(timeout_ns / 1000000000LL);
    ts.tv_nsec = (long)(timeout_ns % 1000000000LL);
    pto = &ts;
  }
  return xlang_futex(uaddr, XLANG_FUTEX_WAIT, expected, pto);
}

/**
 * FUTEX_WAKE — wake up to n waiters on *uaddr.
 * @return number woken (>=0); -1 with errno on failure
 * PLATFORM: LINUX
 */
static inline long xlang_futex_wake(uint32_t *uaddr, int n) {
  if (n < 0) {
    errno = EINVAL;
    return -1;
  }
  return xlang_futex(uaddr, XLANG_FUTEX_WAKE, (uint32_t)n, 0);
}

/**
 * Anonymous RW stack mapping (MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK).
 * @param len bytes (page-rounded by kernel)
 * @return mapped base or NULL with errno
 * PLATFORM: LINUX
 */
static inline void *xlang_thread_mmap_stack(size_t len) {
  long r;
  long nr;
  if (len == 0) {
    errno = EINVAL;
    return 0;
  }
#if defined(__x86_64__)
  nr = 9; /* SYS_mmap */
#elif defined(__aarch64__)
  nr = 222; /* SYS_mmap */
#endif
  r = xlang_syscall6(nr, 0, (long)len, (long)XLANG_PROT_RW,
                     (long)(XLANG_MAP_PRIV_ANON | XLANG_MAP_STACK), (long)-1, 0);
  if (r < 0) {
    errno = (int)(-r);
    return 0;
  }
  return (void *)r;
}

/**
 * Unmap a stack mapping from xlang_thread_mmap_stack.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline long xlang_thread_munmap_stack(void *addr, size_t len) {
  long r;
  long nr;
  if (addr == 0 || len == 0) {
    errno = EINVAL;
    return -1;
  }
#if defined(__x86_64__)
  nr = 11; /* SYS_munmap */
#elif defined(__aarch64__)
  nr = 215; /* SYS_munmap */
#endif
  r = xlang_syscall2(nr, (long)addr, (long)len);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return 0;
}

/**
 * Thread-local exit (SYS_exit) — does not return.
 * PLATFORM: LINUX — use for Cap clone children (not exit_group).
 */
static inline void xlang_thread_exit(long code) {
  long nr;
#if defined(__x86_64__)
  nr = 60; /* SYS_exit */
#elif defined(__aarch64__)
  nr = 93; /* SYS_exit */
#endif
  (void)xlang_syscall1(nr, code);
  for (;;) {
  }
}

/**
 * Raw clone3(2). Returns tid in parent, 0 in child, -1 with errno on failure.
 * @param args VER0 clone_args (64 bytes)
 * @param size sizeof(*args) or CLONE_ARGS_SIZE_VER0
 * PLATFORM: LINUX
 */
static inline long xlang_clone3(struct xlang_clone_args *args, size_t size) {
  long r;
  long nr;
  if (args == 0 || size < 64) {
    errno = EINVAL;
    return -1;
  }
#if defined(__x86_64__)
  nr = 435; /* SYS_clone3 */
#elif defined(__aarch64__)
  nr = 435; /* SYS_clone3 */
#endif
  r = xlang_syscall2(nr, (long)args, (long)size);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Classic clone(2) with pthread-like flags. stack_top = high address (grows down).
 * Returns tid in parent, 0 in child, -1 with errno.
 * PLATFORM: LINUX — x86_64 vs aarch64 arg order differs (kernel ABI).
 */
static inline long xlang_clone(unsigned long flags, void *stack_top, int *parent_tid,
                               int *child_tid, unsigned long tls) {
  long r;
#if defined(__x86_64__)
  /* clone = 56: flags, stack, parent_tid, child_tid, tls */
  r = xlang_syscall6(56, (long)flags, (long)stack_top, (long)parent_tid, (long)child_tid,
                     (long)tls, 0);
#elif defined(__aarch64__)
  /* clone = 220: flags, stack, parent_tid, tls, child_tid */
  r = xlang_syscall6(220, (long)flags, (long)stack_top, (long)parent_tid, (long)tls,
                     (long)child_tid, 0);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Fixed Cap child entry: run user fn then signal join.done (asm exits after return).
 * @param p xlang_thread_spawn_pack*
 * @return 0
 * PLATFORM: LINUX
 */
static inline int xlang_thread_child_entry(void *p) {
  struct xlang_thread_spawn_pack *pack = (struct xlang_thread_spawn_pack *)p;
  if (pack != 0 && pack->fn != 0) {
    (void)pack->fn(pack->arg);
  }
  if (pack != 0 && pack->join != 0) {
    pack->join->done = 1;
    (void)xlang_futex_wake(&pack->join->done, 1);
  }
  return 0;
}

/**
 * Raw clone trampoline: child never returns into C (fn(arg) then SYS_exit).
 * stack_top = high address; fn/arg placed on new stack by Cap.
 * @return tid in parent; does not return in child
 * PLATFORM: LINUX x86_64 | aarch64
 */
static inline long xlang_clone_tramp(int (*fn)(void *), void *stack_top, unsigned long flags,
                                    void *arg, int *ptid, int *ctid) {
  long ret = 0;
  void **sp = (void **)(((uintptr_t)stack_top) & ~(uintptr_t)15);
  if (fn == 0 || stack_top == 0) {
    errno = EINVAL;
    return -1;
  }
  sp -= 2;
  sp[0] = arg;                   /* first pop -> arg */
  sp[1] = (void *)(uintptr_t)fn; /* second pop -> fn */
#if defined(__x86_64__)
  __asm__ __volatile__(
      "mov %[flags], %%rdi\n\t"
      "mov %[stack], %%rsi\n\t"
      "mov %[ptid], %%rdx\n\t"
      "mov %[ctid], %%r10\n\t"
      "xor %%r8, %%r8\n\t"
      "mov $56, %%rax\n\t"
      "syscall\n\t"
      "test %%rax, %%rax\n\t"
      "jnz 1f\n\t"
      "xor %%ebp, %%ebp\n\t"
      "pop %%rdi\n\t"
      "pop %%r9\n\t"
      "call *%%r9\n\t"
      "xor %%edi, %%edi\n\t"
      "mov $60, %%rax\n\t"
      "syscall\n\t"
      "1:\n\t"
      : "=a"(ret)
      : [flags] "r"(flags), [stack] "r"(sp), [ptid] "r"(ptid), [ctid] "r"(ctid)
      : "rcx", "r11", "rdi", "rsi", "rdx", "r8", "r9", "r10", "memory");
#elif defined(__aarch64__)
  __asm__ __volatile__(
      "mov x0, %[flags]\n\t"
      "mov x1, %[stack]\n\t"
      "mov x2, %[ptid]\n\t"
      "mov x3, xzr\n\t"
      "mov x4, %[ctid]\n\t"
      "mov x8, #220\n\t"
      "svc #0\n\t"
      "cbnz x0, 1f\n\t"
      "mov x29, xzr\n\t"
      "mov x30, xzr\n\t"
      "ldp x0, x1, [sp], #16\n\t"
      "blr x1\n\t"
      "mov x0, xzr\n\t"
      "mov x8, #93\n\t"
      "svc #0\n\t"
      "1:\n\t"
      "mov %[ret], x0\n\t"
      : [ret] "=r"(ret)
      : [flags] "r"(flags), [stack] "r"(sp), [ptid] "r"(ptid), [ctid] "r"(ctid)
      : "x0", "x1", "x2", "x3", "x4", "x8", "x29", "x30", "memory");
#endif
  if (ret < 0) {
    errno = (int)(-ret);
    return -1;
  }
  return ret;
}

/**
 * Spawn fn(arg) on a Cap-mapped stack via clone trampoline (no C-continuation).
 * join must be zero-initialized; owns stack until xlang_thread_join.
 * @return 0 parent ok; -1 with errno (never returns in child)
 * PLATFORM: LINUX
 */
static inline int xlang_thread_spawn(xlang_thread_start_fn fn, void *arg,
                                     struct xlang_thread_join *join, size_t stack_len) {
  void *stack = 0;
  struct xlang_thread_spawn_pack *pack = 0;
  unsigned char *base = 0;
  size_t pack_off = 0;
  void *stack_top = 0;
  long r = 0;
  unsigned long flags = (unsigned long)XLANG_CLONE_THREAD_FLAGS;

  if (fn == 0 || join == 0 || stack_len < 16384u) {
    errno = EINVAL;
    return -1;
  }

  join->done = 0;
  join->child_tid = 0;
  join->stack = 0;
  join->stack_len = 0;

  stack = xlang_thread_mmap_stack(stack_len);
  if (stack == 0) {
    return -1;
  }

  base = (unsigned char *)stack;
  pack_off = (sizeof(struct xlang_thread_spawn_pack) + 15u) & ~(size_t)15u;
  if (pack_off + 4096u > stack_len) {
    (void)xlang_thread_munmap_stack(stack, stack_len);
    errno = EINVAL;
    return -1;
  }
  pack = (struct xlang_thread_spawn_pack *)(void *)base;
  pack->fn = fn;
  pack->arg = arg;
  pack->join = join;

  stack_top = (void *)(uintptr_t)(base + stack_len);
  r = xlang_clone_tramp(xlang_thread_child_entry, stack_top, flags, pack, &join->child_tid,
                        &join->child_tid);
  if (r < 0) {
    (void)xlang_thread_munmap_stack(stack, stack_len);
    return -1;
  }

  join->stack = stack;
  join->stack_len = stack_len;
  return 0;
}

/**
 * Wait for Cap-spawned thread, then munmap its stack.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_thread_join(struct xlang_thread_join *join) {
  if (join == 0) {
    errno = EINVAL;
    return -1;
  }
  while (join->done == 0) {
    (void)xlang_futex_wait_timeout_ns(&join->done, 0, 0);
  }
  while (join->child_tid != 0) {
    uint32_t expect = (uint32_t)join->child_tid;
    (void)xlang_futex((uint32_t *)(void *)&join->child_tid, XLANG_FUTEX_WAIT, expect, 0);
  }
  if (join->stack != 0 && join->stack_len != 0) {
    if (xlang_thread_munmap_stack(join->stack, join->stack_len) != 0) {
      return -1;
    }
    join->stack = 0;
    join->stack_len = 0;
  }
  return 0;
}

#elif defined(_WIN32) || defined(_WIN64)

/*
 * Cap residual 10.6.2 slice0 — Windows CreateThread / WaitForSingleObject.
 * Same spawn/join entry names as Linux Cap so product glue has one authority.
 * PLATFORM: WINDOWS
 */

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

typedef void *(*xlang_thread_start_fn)(void *arg);

/**
 * Join handle filled by xlang_thread_spawn; wait with xlang_thread_join.
 * PLATFORM: WINDOWS — handle is CreateThread HANDLE.
 */
struct xlang_thread_join {
  void *handle; /* HANDLE */
  void *stack;  /* unused (CreateThread owns stack); kept for layout kinship */
  size_t stack_len;
};

/**
 * Pack passed to Cap Win trampoline (heap; freed by child).
 * PLATFORM: WINDOWS
 */
struct xlang_thread_spawn_pack {
  xlang_thread_start_fn fn;
  void *arg;
};

/**
 * CreateThread trampoline: run fn(arg), free pack, return 0.
 * @param p xlang_thread_spawn_pack*
 * @return 0
 * PLATFORM: WINDOWS
 */
static DWORD WINAPI xlang_thread_win_tramp(LPVOID p) {
  struct xlang_thread_spawn_pack *pack = (struct xlang_thread_spawn_pack *)p;
  if (pack != 0) {
    if (pack->fn != 0) {
      (void)pack->fn(pack->arg);
    }
    free(pack);
  }
  return 0;
}

/**
 * Spawn fn(arg) via CreateThread (Cap residual; no CRT _beginthreadex).
 * join must be zero-initialized; owns HANDLE until xlang_thread_join.
 * @param stack_len requested stack bytes; 0 → system default
 * @return 0 parent ok; -1 with errno
 * PLATFORM: WINDOWS
 */
static inline int xlang_thread_spawn(xlang_thread_start_fn fn, void *arg,
                                     struct xlang_thread_join *join, size_t stack_len) {
  struct xlang_thread_spawn_pack *pack = 0;
  HANDLE h = NULL;
  if (fn == 0 || join == 0) {
    errno = EINVAL;
    return -1;
  }
  join->handle = 0;
  join->stack = 0;
  join->stack_len = 0;
  pack = (struct xlang_thread_spawn_pack *)malloc(sizeof(*pack));
  if (pack == 0) {
    errno = ENOMEM;
    return -1;
  }
  pack->fn = fn;
  pack->arg = arg;
  h = CreateThread(NULL, (SIZE_T)stack_len, xlang_thread_win_tramp, pack, 0, NULL);
  if (h == NULL) {
    free(pack);
    errno = EAGAIN;
    return -1;
  }
  join->handle = (void *)h;
  join->stack_len = stack_len;
  return 0;
}

/**
 * Wait for Cap-spawned Win thread and CloseHandle.
 * @return 0 ok; -1 with errno
 * PLATFORM: WINDOWS
 */
static inline int xlang_thread_join(struct xlang_thread_join *join) {
  HANDLE h = NULL;
  if (join == 0 || join->handle == 0) {
    errno = EINVAL;
    return -1;
  }
  h = (HANDLE)join->handle;
  if (WaitForSingleObject(h, INFINITE) != WAIT_OBJECT_0) {
    errno = EIO;
    return -1;
  }
  (void)CloseHandle(h);
  join->handle = 0;
  return 0;
}

#elif defined(__APPLE__)

/*
 * Cap residual 10.6.1 — Darwin POSIX pthread spawn/join.
 * Provides xlang_thread_spawn and xlang_thread_join matching Linux/Windows Cap
 * so runtime_thread_glue and client code have a single authority across platforms.
 * PLATFORM: DARWIN / MACOS
 */

#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef void *(*xlang_thread_start_fn)(void *arg);

/**
 * Join handle filled by xlang_thread_spawn; wait with xlang_thread_join.
 * PLATFORM: DARWIN
 */
struct xlang_thread_join {
  pthread_t handle;
  void *stack;
  size_t stack_len;
};

/**
 * Spawn fn(arg) via pthread_create (Darwin Cap residual).
 * join must be zero-initialized; owns handle until xlang_thread_join.
 * @param stack_len requested stack bytes; 0 -> system default
 * @return 0 parent ok; -1 with errno
 * PLATFORM: DARWIN
 */
static inline int xlang_thread_spawn(xlang_thread_start_fn fn, void *arg,
                                     struct xlang_thread_join *join, size_t stack_len) {
  if (fn == 0 || join == 0) {
    errno = EINVAL;
    return -1;
  }
  join->handle = (pthread_t)0;
  join->stack = 0;
  join->stack_len = stack_len;
  if (stack_len == 0) {
    int ret = pthread_create(&join->handle, NULL, (void *(*)(void *))fn, arg);
    if (ret != 0) {
      errno = ret;
      return -1;
    }
    return 0;
  }
  pthread_attr_t attr;
  if (pthread_attr_init(&attr) != 0) {
    errno = EAGAIN;
    return -1;
  }
  if (pthread_attr_setstacksize(&attr, stack_len) != 0) {
    pthread_attr_destroy(&attr);
    errno = EINVAL;
    return -1;
  }
  int ret = pthread_create(&join->handle, &attr, (void *(*)(void *))fn, arg);
  pthread_attr_destroy(&attr);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

/**
 * Wait for Cap-spawned Darwin thread and clean up.
 * @return 0 ok; -1 with errno
 * PLATFORM: DARWIN
 */
static inline int xlang_thread_join(struct xlang_thread_join *join) {
  if (join == 0 || join->handle == (pthread_t)0) {
    errno = EINVAL;
    return -1;
  }
  int ret = pthread_join(join->handle, NULL);
  join->handle = (pthread_t)0;
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

#endif /* LINUX | WINDOWS | DARWIN */

#endif /* XLANG_THREAD_CAP_H */
