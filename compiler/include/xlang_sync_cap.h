/*
 * xlang_sync_cap.h — Cap residual 10.6.3: OS-agnostic sync primitives.
 * - Linux: futex sync without libpthread (x86_64 + aarch64).
 * - Darwin: POSIX pthread sync primitives.
 * - Windows: Win32 synchronization primitives (CRITICAL_SECTION, CONDITION_VARIABLE,
 *            SRWLOCK, and Semaphore).
 *
 * G.7: single authority for Cap sync primitives across Linux, Darwin, and Windows.
 *
 * Slice0: non-recursive mutex (init/lock/trylock/unlock).
 * Slice1: condition variable (init/wait/signal/broadcast).
 * Slice2: counting semaphore (init/wait/trywait/post).
 * Slice3: runtime_sync_os Linux mutex/cond wired to Cap.
 * Slice4: reader-writer lock (rdlock/wrlock/unlock) + sync_os wire.
 * Later: Windows Cap sync (10.6.3 full-closure).
 *
 * PLATFORM: LINUX primary (x86_64 + aarch64) · DARWIN Cap sync · WINDOWS Cap sync.
 */

#ifndef XLANG_SYNC_CAP_H
#define XLANG_SYNC_CAP_H

#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include <xlang_thread_cap.h>

/** Unlocked. */
#define XLANG_CAP_MUTEX_UNLOCKED 0u
/** Locked (may have waiters). */
#define XLANG_CAP_MUTEX_LOCKED 1u

/**
 * Cap futex mutex — single aligned u32 word (non-recursive).
 * PLATFORM: LINUX
 */
struct xlang_cap_mutex {
  uint32_t state;
};

/**
 * Initialize Cap mutex to unlocked.
 * @param m mutex (must be non-null, 4-byte aligned)
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_mutex_init(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  m->state = XLANG_CAP_MUTEX_UNLOCKED;
  return 0;
}

/**
 * Destroy Cap mutex (no heap; clears state).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_mutex_destroy(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  m->state = XLANG_CAP_MUTEX_UNLOCKED;
  return 0;
}

/**
 * Acquire Cap mutex (block via futex while locked).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_mutex_lock(struct xlang_cap_mutex *m) {
  uint32_t expected = XLANG_CAP_MUTEX_UNLOCKED;
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  for (;;) {
    expected = XLANG_CAP_MUTEX_UNLOCKED;
    if (__atomic_compare_exchange_n(&m->state, &expected, XLANG_CAP_MUTEX_LOCKED, 0,
                                    __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)) {
      return 0;
    }
    /* state is LOCKED — sleep until unlock wakes. */
    (void)xlang_futex(&m->state, XLANG_FUTEX_WAIT, XLANG_CAP_MUTEX_LOCKED, 0);
  }
}

/**
 * Try to acquire Cap mutex without blocking.
 * @return 0 acquired; -1 with errno=EBUSY if held; -1 EINVAL if m null
 * PLATFORM: LINUX
 */
static inline int xlang_cap_mutex_trylock(struct xlang_cap_mutex *m) {
  uint32_t expected = XLANG_CAP_MUTEX_UNLOCKED;
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  if (__atomic_compare_exchange_n(&m->state, &expected, XLANG_CAP_MUTEX_LOCKED, 0,
                                  __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)) {
    return 0;
  }
  errno = EBUSY;
  return -1;
}

/**
 * Release Cap mutex and wake one waiter.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_mutex_unlock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  __atomic_store_n(&m->state, XLANG_CAP_MUTEX_UNLOCKED, __ATOMIC_RELEASE);
  (void)xlang_futex_wake(&m->state, 1);
  return 0;
}

/**
 * Cap futex condvar — sequence word (waiters sleep on seq).
 * PLATFORM: LINUX
 */
struct xlang_cap_cond {
  uint32_t seq;
};

/**
 * Initialize Cap condvar.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_init(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  cv->seq = 0;
  return 0;
}

/**
 * Destroy Cap condvar (no heap).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_destroy(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  cv->seq = 0;
  return 0;
}

/**
 * Wait on Cap condvar: atomically unlock m, sleep until signal/broadcast, relock.
 * Caller must hold m. Spurious wakes possible — recheck predicate.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_wait(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m) {
  uint32_t seq = 0;
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  seq = __atomic_load_n(&cv->seq, __ATOMIC_ACQUIRE);
  if (xlang_cap_mutex_unlock(m) != 0) {
    return -1;
  }
  (void)xlang_futex(&cv->seq, XLANG_FUTEX_WAIT, seq, 0);
  if (xlang_cap_mutex_lock(m) != 0) {
    return -1;
  }
  return 0;
}

/**
 * Wait on Cap condvar with a millisecond timeout.
 * Atomically unlocks m, sleeps up to ms milliseconds, relocks m.
 * @param cv condition variable
 * @param m mutex held by caller
 * @param ms timeout in milliseconds (<=0 returns immediately after unlocking & locking)
 * @return 0 on wake; 1 on timeout; -1 on error
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_timedwait_ms(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m, int32_t ms) {
  uint32_t seq = 0;
  long ret = 0;
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  seq = __atomic_load_n(&cv->seq, __ATOMIC_ACQUIRE);
  if (xlang_cap_mutex_unlock(m) != 0) {
    return -1;
  }
  if (ms > 0) {
    ret = xlang_futex_wait_timeout_ns(&cv->seq, seq, (int64_t)ms * 1000000LL);
  }
  if (xlang_cap_mutex_lock(m) != 0) {
    return -1;
  }
  if (ret < 0 && errno == ETIMEDOUT) {
    return 1;
  }
  return 0;
}

/**
 * Wake one Cap condvar waiter.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_signal(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  (void)__atomic_fetch_add(&cv->seq, 1u, __ATOMIC_RELEASE);
  (void)xlang_futex_wake(&cv->seq, 1);
  return 0;
}

/**
 * Wake all Cap condvar waiters.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_cond_broadcast(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  (void)__atomic_fetch_add(&cv->seq, 1u, __ATOMIC_RELEASE);
  (void)xlang_futex_wake(&cv->seq, 0x7fffffff);
  return 0;
}

/**
 * Cap futex counting semaphore — non-negative count word.
 * PLATFORM: LINUX
 */
struct xlang_cap_sem {
  uint32_t count;
};

/**
 * Initialize Cap semaphore to `value` permits (value may be 0).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_sem_init(struct xlang_cap_sem *sem, uint32_t value) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  sem->count = value;
  return 0;
}

/**
 * Destroy Cap semaphore (no heap).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_sem_destroy(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  sem->count = 0;
  return 0;
}

/**
 * Wait (P/down): decrement count, blocking via futex while count==0.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_sem_wait(struct xlang_cap_sem *sem) {
  uint32_t cur = 0;
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  for (;;) {
    cur = __atomic_load_n(&sem->count, __ATOMIC_ACQUIRE);
    if (cur > 0) {
      if (__atomic_compare_exchange_n(&sem->count, &cur, cur - 1u, 0, __ATOMIC_ACQ_REL,
                                      __ATOMIC_ACQUIRE)) {
        return 0;
      }
      continue;
    }
    (void)xlang_futex(&sem->count, XLANG_FUTEX_WAIT, 0u, 0);
  }
}

/**
 * Try wait: decrement if count>0, else EAGAIN.
 * @return 0 ok; -1 with errno=EAGAIN if empty
 * PLATFORM: LINUX
 */
static inline int xlang_cap_sem_trywait(struct xlang_cap_sem *sem) {
  uint32_t cur = 0;
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  for (;;) {
    cur = __atomic_load_n(&sem->count, __ATOMIC_ACQUIRE);
    if (cur == 0) {
      errno = EAGAIN;
      return -1;
    }
    if (__atomic_compare_exchange_n(&sem->count, &cur, cur - 1u, 0, __ATOMIC_ACQ_REL,
                                    __ATOMIC_ACQUIRE)) {
      return 0;
    }
  }
}

/**
 * Post (V/up): increment count and wake one waiter.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_sem_post(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  (void)__atomic_fetch_add(&sem->count, 1u, __ATOMIC_RELEASE);
  (void)xlang_futex_wake(&sem->count, 1);
  return 0;
}

/** Writer held bit (MSB). Lower bits = reader count when writer clear. */
#define XLANG_CAP_RW_WRITER 0x80000000u
/** Mask for concurrent reader count. */
#define XLANG_CAP_RW_READERS_MASK 0x7fffffffu

/**
 * Cap futex rwlock — single state word.
 *   0              unlocked
 *   1..0x7fffffff  N readers
 *   0x80000000     exclusive writer
 * Waiters sleep on `state`. Reader-biased (writers wait for readers==0).
 * PLATFORM: LINUX
 */
struct xlang_cap_rwlock {
  uint32_t state;
};

/**
 * Initialize Cap rwlock to unlocked.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_init(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  rw->state = 0u;
  return 0;
}

/**
 * Destroy Cap rwlock (no heap; clears state).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_destroy(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  rw->state = 0u;
  return 0;
}

/**
 * Acquire shared read lock (block while a writer holds).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_rdlock(struct xlang_cap_rwlock *rw) {
  uint32_t s = 0;
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  for (;;) {
    s = __atomic_load_n(&rw->state, __ATOMIC_ACQUIRE);
    if ((s & XLANG_CAP_RW_WRITER) != 0u) {
      (void)xlang_futex(&rw->state, XLANG_FUTEX_WAIT, s, 0);
      continue;
    }
    if (__atomic_compare_exchange_n(&rw->state, &s, s + 1u, 0, __ATOMIC_ACQ_REL,
                                    __ATOMIC_ACQUIRE)) {
      return 0;
    }
  }
}

/**
 * Acquire exclusive write lock (block while any reader or writer holds).
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_wrlock(struct xlang_cap_rwlock *rw) {
  uint32_t s = 0;
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  for (;;) {
    s = __atomic_load_n(&rw->state, __ATOMIC_ACQUIRE);
    if (s != 0u) {
      (void)xlang_futex(&rw->state, XLANG_FUTEX_WAIT, s, 0);
      continue;
    }
    if (__atomic_compare_exchange_n(&rw->state, &s, XLANG_CAP_RW_WRITER, 0,
                                    __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
      return 0;
    }
  }
}

/**
 * Release a previously held read lock; wake waiters when last reader exits.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_rdunlock(struct xlang_cap_rwlock *rw) {
  uint32_t prev = 0;
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  prev = __atomic_fetch_sub(&rw->state, 1u, __ATOMIC_RELEASE);
  if ((prev & XLANG_CAP_RW_READERS_MASK) == 1u) {
    (void)xlang_futex_wake(&rw->state, 0x7fffffff);
  }
  return 0;
}

/**
 * Release a previously held write lock; wake all waiters.
 * @return 0 ok; -1 with errno
 * PLATFORM: LINUX
 */
static inline int xlang_cap_rwlock_wrunlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  __atomic_store_n(&rw->state, 0u, __ATOMIC_RELEASE);
  (void)xlang_futex_wake(&rw->state, 0x7fffffff);
  return 0;
}

#elif defined(__APPLE__)

/*
 * Cap residual 10.6.3 — Darwin POSIX pthread sync primitives.
 * Provides xlang_cap_mutex, xlang_cap_cond, xlang_cap_sem, xlang_cap_rwlock
 * matching Linux Cap signatures, eliminating duplication across platforms.
 * PLATFORM: DARWIN / MACOS
 */

#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>

#include <xlang_thread_cap.h>

/**
 * Cap Darwin mutex — pthread_mutex_t wrapper.
 * PLATFORM: DARWIN
 */
struct xlang_cap_mutex {
  pthread_mutex_t mu;
};

static inline int xlang_cap_mutex_init(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_mutex_init(&m->mu, NULL) == 0) ? 0 : -1;
}

static inline int xlang_cap_mutex_destroy(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_mutex_destroy(&m->mu) == 0) ? 0 : -1;
}

static inline int xlang_cap_mutex_lock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_mutex_lock(&m->mu) == 0) ? 0 : -1;
}

static inline int xlang_cap_mutex_trylock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  int ret = pthread_mutex_trylock(&m->mu);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

static inline int xlang_cap_mutex_unlock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_mutex_unlock(&m->mu) == 0) ? 0 : -1;
}

/**
 * Cap Darwin condvar — pthread_cond_t wrapper.
 * PLATFORM: DARWIN
 */
struct xlang_cap_cond {
  pthread_cond_t cv;
};

static inline int xlang_cap_cond_init(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_cond_init(&cv->cv, NULL) == 0) ? 0 : -1;
}

static inline int xlang_cap_cond_destroy(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_cond_destroy(&cv->cv) == 0) ? 0 : -1;
}

static inline int xlang_cap_cond_wait(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m) {
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_cond_wait(&cv->cv, &m->mu) == 0) ? 0 : -1;
}

/**
 * Wait on Cap condvar with a millisecond timeout using pthread_cond_timedwait.
 * @param cv condition variable
 * @param m mutex held by caller
 * @param ms timeout in milliseconds
 * @return 0 on wake; 1 on timeout; -1 on error
 * PLATFORM: DARWIN
 */
static inline int xlang_cap_cond_timedwait_ms(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m, int32_t ms) {
  struct timespec ts;
  struct timeval tv;
  int r;
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  if (gettimeofday(&tv, NULL) != 0) {
    return -1;
  }
  ts.tv_sec = tv.tv_sec + (long)(ms / 1000);
  ts.tv_nsec = (long)(tv.tv_usec * 1000) + (long)((ms % 1000) * 1000000L);
  if (ts.tv_nsec >= 1000000000L) {
    ts.tv_sec += ts.tv_nsec / 1000000000L;
    ts.tv_nsec %= 1000000000L;
  }
  r = pthread_cond_timedwait(&cv->cv, &m->mu, &ts);
  if (r == ETIMEDOUT) {
    return 1;
  }
  if (r != 0) {
    errno = r;
    return -1;
  }
  return 0;
}

static inline int xlang_cap_cond_signal(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_cond_signal(&cv->cv) == 0) ? 0 : -1;
}

static inline int xlang_cap_cond_broadcast(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_cond_broadcast(&cv->cv) == 0) ? 0 : -1;
}

/**
 * Cap Darwin counting semaphore using mutex + condvar.
 * Note: Darwin deprecated POSIX sem_init, so mutex + condvar provides a reliable portable counting sem.
 * PLATFORM: DARWIN
 */
struct xlang_cap_sem {
  pthread_mutex_t mu;
  pthread_cond_t cv;
  uint32_t count;
};

static inline int xlang_cap_sem_init(struct xlang_cap_sem *sem, uint32_t value) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  if (pthread_mutex_init(&sem->mu, NULL) != 0) return -1;
  if (pthread_cond_init(&sem->cv, NULL) != 0) {
    pthread_mutex_destroy(&sem->mu);
    return -1;
  }
  sem->count = value;
  return 0;
}

static inline int xlang_cap_sem_destroy(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  pthread_cond_destroy(&sem->cv);
  pthread_mutex_destroy(&sem->mu);
  sem->count = 0;
  return 0;
}

static inline int xlang_cap_sem_wait(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  if (pthread_mutex_lock(&sem->mu) != 0) return -1;
  while (sem->count == 0) {
    if (pthread_cond_wait(&sem->cv, &sem->mu) != 0) {
      pthread_mutex_unlock(&sem->mu);
      return -1;
    }
  }
  sem->count--;
  pthread_mutex_unlock(&sem->mu);
  return 0;
}

static inline int xlang_cap_sem_trywait(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  if (pthread_mutex_lock(&sem->mu) != 0) return -1;
  if (sem->count == 0) {
    pthread_mutex_unlock(&sem->mu);
    errno = EAGAIN;
    return -1;
  }
  sem->count--;
  pthread_mutex_unlock(&sem->mu);
  return 0;
}

static inline int xlang_cap_sem_post(struct xlang_cap_sem *sem) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  if (pthread_mutex_lock(&sem->mu) != 0) return -1;
  sem->count++;
  pthread_cond_signal(&sem->cv);
  pthread_mutex_unlock(&sem->mu);
  return 0;
}

/**
 * Cap Darwin rwlock — pthread_rwlock_t wrapper.
 * PLATFORM: DARWIN
 */
struct xlang_cap_rwlock {
  pthread_rwlock_t rw;
};

static inline int xlang_cap_rwlock_init(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_init(&rw->rw, NULL) == 0) ? 0 : -1;
}

static inline int xlang_cap_rwlock_destroy(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_destroy(&rw->rw) == 0) ? 0 : -1;
}

static inline int xlang_cap_rwlock_rdlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_rdlock(&rw->rw) == 0) ? 0 : -1;
}

static inline int xlang_cap_rwlock_wrlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_wrlock(&rw->rw) == 0) ? 0 : -1;
}

static inline int xlang_cap_rwlock_rdunlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_unlock(&rw->rw) == 0) ? 0 : -1;
}

static inline int xlang_cap_rwlock_wrunlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return (pthread_rwlock_unlock(&rw->rw) == 0) ? 0 : -1;
}

#elif defined(_WIN32) || defined(_WIN64)

/*
 * Cap residual 10.6.3: Windows Win32 sync primitives.
 * PLATFORM: WINDOWS
 */

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

/**
 * Cap mutex wrapping Win32 CRITICAL_SECTION.
 * PLATFORM: WINDOWS
 */
struct xlang_cap_mutex {
  CRITICAL_SECTION cs;
};

/**
 * Initialize Cap mutex using Win32 InitializeCriticalSection.
 * @param m pointer to mutex
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_mutex_init(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  InitializeCriticalSection(&m->cs);
  return 0;
}

/**
 * Destroy Cap mutex using Win32 DeleteCriticalSection.
 * @param m pointer to mutex
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_mutex_destroy(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  DeleteCriticalSection(&m->cs);
  return 0;
}

/**
 * Lock Cap mutex using Win32 EnterCriticalSection.
 * @param m pointer to mutex
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_mutex_lock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  EnterCriticalSection(&m->cs);
  return 0;
}

/**
 * Try to lock Cap mutex using Win32 TryEnterCriticalSection.
 * @param m pointer to mutex
 * @return 0 if lock acquired, -1 on busy or error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_mutex_trylock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  if (TryEnterCriticalSection(&m->cs)) {
    return 0;
  }
  errno = EBUSY;
  return -1;
}

/**
 * Unlock Cap mutex using Win32 LeaveCriticalSection.
 * @param m pointer to mutex
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_mutex_unlock(struct xlang_cap_mutex *m) {
  if (m == 0) {
    errno = EINVAL;
    return -1;
  }
  LeaveCriticalSection(&m->cs);
  return 0;
}

/**
 * Cap condition variable wrapping Win32 CONDITION_VARIABLE.
 * PLATFORM: WINDOWS
 */
struct xlang_cap_cond {
  CONDITION_VARIABLE cv;
};

/**
 * Initialize Cap condition variable using Win32 InitializeConditionVariable.
 * @param cv pointer to condition variable
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_init(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  InitializeConditionVariable(&cv->cv);
  return 0;
}

/**
 * Destroy Cap condition variable. Win32 condition variables require no explicit cleanup.
 * @param cv pointer to condition variable
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_destroy(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Wait on Cap condition variable and associated Cap mutex.
 * @param cv pointer to condition variable
 * @param m pointer to locked Cap mutex
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_wait(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m) {
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  if (!SleepConditionVariableCS(&cv->cv, &m->cs, INFINITE)) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Wait on Cap condvar with a millisecond timeout using Win32 SleepConditionVariableCS.
 * @param cv pointer to condition variable
 * @param m pointer to locked Cap mutex
 * @param ms timeout in milliseconds
 * @return 0 on wake; 1 on timeout; -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_timedwait_ms(struct xlang_cap_cond *cv, struct xlang_cap_mutex *m, int32_t ms) {
  if (cv == 0 || m == 0) {
    errno = EINVAL;
    return -1;
  }
  if (!SleepConditionVariableCS(&cv->cv, &m->cs, (DWORD)(ms < 0 ? INFINITE : ms))) {
    if (GetLastError() == ERROR_TIMEOUT) {
      return 1;
    }
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Wake single waiter on Cap condition variable using Win32 WakeConditionVariable.
 * @param cv pointer to condition variable
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_signal(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  WakeConditionVariable(&cv->cv);
  return 0;
}

/**
 * Wake all waiters on Cap condition variable using Win32 WakeAllConditionVariable.
 * @param cv pointer to condition variable
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_cond_broadcast(struct xlang_cap_cond *cv) {
  if (cv == 0) {
    errno = EINVAL;
    return -1;
  }
  WakeAllConditionVariable(&cv->cv);
  return 0;
}

/**
 * Cap counting semaphore wrapping Win32 Semaphore HANDLE.
 * PLATFORM: WINDOWS
 */
struct xlang_cap_sem {
  HANDLE h;
};

/**
 * Initialize Cap semaphore using Win32 CreateSemaphoreW.
 * @param sem pointer to semaphore
 * @param value initial semaphore count
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_sem_init(struct xlang_cap_sem *sem, uint32_t value) {
  if (sem == 0) {
    errno = EINVAL;
    return -1;
  }
  sem->h = CreateSemaphoreW(NULL, (LONG)value, 0x7fffffff, NULL);
  if (sem->h == NULL) {
    errno = ENOMEM;
    return -1;
  }
  return 0;
}

/**
 * Destroy Cap semaphore by closing the Win32 HANDLE.
 * @param sem pointer to semaphore
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_sem_destroy(struct xlang_cap_sem *sem) {
  if (sem == 0 || sem->h == NULL) {
    errno = EINVAL;
    return -1;
  }
  CloseHandle(sem->h);
  sem->h = NULL;
  return 0;
}

/**
 * Wait (decrement) on Cap semaphore using Win32 WaitForSingleObject.
 * @param sem pointer to semaphore
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_sem_wait(struct xlang_cap_sem *sem) {
  if (sem == 0 || sem->h == NULL) {
    errno = EINVAL;
    return -1;
  }
  if (WaitForSingleObject(sem->h, INFINITE) != WAIT_OBJECT_0) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Try to wait (decrement) on Cap semaphore without blocking.
 * @param sem pointer to semaphore
 * @return 0 if count decremented, -1 on busy or error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_sem_trywait(struct xlang_cap_sem *sem) {
  DWORD res;
  if (sem == 0 || sem->h == NULL) {
    errno = EINVAL;
    return -1;
  }
  res = WaitForSingleObject(sem->h, 0);
  if (res == WAIT_OBJECT_0) {
    return 0;
  }
  if (res == WAIT_TIMEOUT) {
    errno = EAGAIN;
    return -1;
  }
  errno = EINVAL;
  return -1;
}

/**
 * Post (increment) Cap semaphore using Win32 ReleaseSemaphore.
 * @param sem pointer to semaphore
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_sem_post(struct xlang_cap_sem *sem) {
  if (sem == 0 || sem->h == NULL) {
    errno = EINVAL;
    return -1;
  }
  if (!ReleaseSemaphore(sem->h, 1, NULL)) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Cap reader-writer lock wrapping Win32 SRWLOCK.
 * PLATFORM: WINDOWS
 */
struct xlang_cap_rwlock {
  SRWLOCK rw;
};

/**
 * Initialize Cap reader-writer lock using Win32 InitializeSRWLock.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_init(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  InitializeSRWLock(&rw->rw);
  return 0;
}

/**
 * Destroy Cap reader-writer lock. Win32 SRWLOCK requires no explicit cleanup.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_destroy(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

/**
 * Acquire shared (reader) lock using Win32 AcquireSRWLockShared.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_rdlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  AcquireSRWLockShared(&rw->rw);
  return 0;
}

/**
 * Acquire exclusive (writer) lock using Win32 AcquireSRWLockExclusive.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_wrlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  AcquireSRWLockExclusive(&rw->rw);
  return 0;
}

/**
 * Release shared (reader) lock using Win32 ReleaseSRWLockShared.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_rdunlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  ReleaseSRWLockShared(&rw->rw);
  return 0;
}

/**
 * Release exclusive (writer) lock using Win32 ReleaseSRWLockExclusive.
 * @param rw pointer to rwlock
 * @return 0 on success, -1 on error
 * PLATFORM: WINDOWS
 */
static inline int xlang_cap_rwlock_wrunlock(struct xlang_cap_rwlock *rw) {
  if (rw == 0) {
    errno = EINVAL;
    return -1;
  }
  ReleaseSRWLockExclusive(&rw->rw);
  return 0;
}

#endif /* LINUX x86_64|aarch64 | DARWIN | WINDOWS */

#endif /* XLANG_SYNC_CAP_H */
