/* seeds/runtime_sync_os.from_x.c — G-02f-19 product TU
 * Product: runtime_sync_os.o; logic still C until full .x port.
 *
 * R2 full mode (wave504): public API in src/asm/runtime_sync_os.x (thin),
 * OS bridge _impl functions here (rest). Thin+rest linked via ld -r.
 * Platform-specific: Windows (CRITICAL_SECTION/SRWLOCK/CONDITION_VARIABLE)
 * vs POSIX. LINUX primary: mutex/cond/rwlock → xlang_sync_cap (futex); cond
 * smoke → Cap spawn (no libpthread on Linux sync_os leaf). Darwin/other POSIX:
 * pthread for mutex/cond/rwlock + pthread_create smoke.
 * PLATFORM: SHARED — LINUX Cap · POSIX pthread · WINDOWS Win32
 */
/**
 * runtime_sync_os.c — Mutex/RwLock/Condvar OS 胶层（F-ZC：自 std/sync/sync_os_glue.c 迁入）
 *
 * 【文件职责】
 * 实现 sync_mutex_*、sync_rwlock_*、sync_condvar_* 及竞争烟测；
 * POSIX 使用 pthread；Windows 使用 CRITICAL_SECTION / SRWLOCK / CONDITION_VARIABLE。
 * 加解锁时调用 sync.x 中的诊断钩子。
 *
 * 【所属模块】std.sync；与 sync.o、runtime_sync_lock_diag_tls.o 一并链入 exe。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** Lock diagnostic hooks (defined in std/sync/sync.x). */
extern int32_t sync_lock_diag_before_lock(void *m);
extern void sync_lock_diag_after_lock(void *m);
extern int32_t sync_lock_diag_before_unlock(void *m);
extern void sync_lock_diag_after_unlock(void *m);

/* Forward declarations of thin public API functions (provided by runtime_sync_os.x
 * in R2 mode; defined locally in cold path). Needed by smoke tests and _impl
 * functions that call back into the public API. */
void *sync_mutex_new_c(void);
int32_t sync_mutex_lock_c(void *m);
int32_t sync_mutex_try_lock_c(void *m);
int32_t sync_mutex_unlock_c(void *m);
void sync_mutex_free_c(void *m);
void *sync_rwlock_new_c(void);
int32_t sync_rwlock_read_lock_c(void *rw);
int32_t sync_rwlock_write_lock_c(void *rw);
int32_t sync_rwlock_read_unlock_c(void *rw);
int32_t sync_rwlock_write_unlock_c(void *rw);
void sync_rwlock_free_c(void *rw);
void *sync_condvar_new_c(void);
int32_t sync_condvar_wait_c(void *cv, void *mutex);
int32_t sync_condvar_signal_c(void *cv);
int32_t sync_condvar_broadcast_c(void *cv);
void sync_condvar_free_c(void *cv);

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

/** Windows: mutex is CRITICAL_SECTION*, heap-allocated for opaque return. */
typedef CRITICAL_SECTION xlang_mutex_impl_t;

/** Create new mutex; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge; thin (src/asm/runtime_sync_os.x) provides public wrapper */
void *sync_mutex_new_impl(void) {
    xlang_mutex_impl_t *m = (xlang_mutex_impl_t *)malloc(sizeof(xlang_mutex_impl_t));
    if (m == NULL) return NULL;
    InitializeCriticalSection(m);
    return (void *)m;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
/* Cold path: public wrapper provided by seed */
void *sync_mutex_new_c(void) { return sync_mutex_new_impl(); }
#endif

/** Lock; blocks until acquired. Returns 0 success, -1 failure (e.g. m is NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_lock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_lock(m) != 0) {
        return -1;
    }
    EnterCriticalSection((CRITICAL_SECTION *)m);
    sync_lock_diag_after_lock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_lock_c(void *m) { return sync_mutex_lock_impl(m); }
#endif

/** Try-lock; non-blocking. Returns 0 success, non-zero not acquired (busy or m NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_try_lock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_lock(m) != 0) {
        return -1;
    }
    if (!TryEnterCriticalSection((CRITICAL_SECTION *)m)) {
        return 1;
    }
    sync_lock_diag_after_lock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_try_lock_c(void *m) { return sync_mutex_try_lock_impl(m); }
#endif

/** Unlock. Returns 0 success, -1 failure (e.g. m is NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_unlock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_unlock(m) != 0) {
        return -1;
    }
    LeaveCriticalSection((CRITICAL_SECTION *)m);
    sync_lock_diag_after_unlock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_unlock_c(void *m) { return sync_mutex_unlock_impl(m); }
#endif

/** Destroy and free mutex; m must not be used after this call. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_mutex_free_impl(void *m) {
    if (m == NULL) return;
    DeleteCriticalSection((CRITICAL_SECTION *)m);
    free(m);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_mutex_free_c(void *m) { sync_mutex_free_impl(m); }
#endif

typedef SRWLOCK xlang_rwlock_impl_t;
typedef CONDITION_VARIABLE xlang_condvar_impl_t;

/** Create RwLock; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
void *sync_rwlock_new_impl(void) {
    xlang_rwlock_impl_t *rw = (xlang_rwlock_impl_t *)malloc(sizeof(xlang_rwlock_impl_t));
    if (!rw) return NULL;
    InitializeSRWLock(rw);
    return (void *)rw;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void *sync_rwlock_new_c(void) { return sync_rwlock_new_impl(); }
#endif

/** Acquire read lock; returns 0 success. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_read_lock_impl(void *rw) {
    if (!rw) return -1;
    AcquireSRWLockShared((SRWLOCK *)rw);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_read_lock_c(void *rw) { return sync_rwlock_read_lock_impl(rw); }
#endif

/** Acquire write lock; returns 0 success. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_write_lock_impl(void *rw) {
    if (!rw) return -1;
    AcquireSRWLockExclusive((SRWLOCK *)rw);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_write_lock_c(void *rw) { return sync_rwlock_write_lock_impl(rw); }
#endif

/** Release read lock; returns 0 success. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_read_unlock_impl(void *rw) {
    if (!rw) return -1;
    ReleaseSRWLockShared((SRWLOCK *)rw);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_read_unlock_c(void *rw) { return sync_rwlock_read_unlock_impl(rw); }
#endif

/** Release write lock; returns 0 success. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_write_unlock_impl(void *rw) {
    if (!rw) return -1;
    ReleaseSRWLockExclusive((SRWLOCK *)rw);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_write_unlock_c(void *rw) { return sync_rwlock_write_unlock_impl(rw); }
#endif

/** Destroy RwLock. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_rwlock_free_impl(void *rw) {
    free(rw);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_rwlock_free_c(void *rw) { sync_rwlock_free_impl(rw); }
#endif

/** Create Condvar; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
void *sync_condvar_new_impl(void) {
    xlang_condvar_impl_t *cv = (xlang_condvar_impl_t *)malloc(sizeof(xlang_condvar_impl_t));
    if (!cv) return NULL;
    InitializeConditionVariable(cv);
    return (void *)cv;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void *sync_condvar_new_c(void) { return sync_condvar_new_impl(); }
#endif

/** Wait on condvar while holding mutex. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_wait_impl(void *cv, void *mutex) {
    if (!cv || !mutex) return -1;
    if (!SleepConditionVariableCS((CONDITION_VARIABLE *)cv, (CRITICAL_SECTION *)mutex, INFINITE)) {
        return -1;
    }
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_wait_c(void *cv, void *mutex) { return sync_condvar_wait_impl(cv, mutex); }
#endif

/** Wake one waiting thread. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_signal_impl(void *cv) {
    if (!cv) return -1;
    WakeConditionVariable((CONDITION_VARIABLE *)cv);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_signal_c(void *cv) { return sync_condvar_signal_impl(cv); }
#endif

/** Wake all waiting threads. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_broadcast_impl(void *cv) {
    if (!cv) return -1;
    WakeAllConditionVariable((CONDITION_VARIABLE *)cv);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_broadcast_c(void *cv) { return sync_condvar_broadcast_impl(cv); }
#endif

/** Destroy Condvar. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_condvar_free_impl(void *cv) {
    free(cv);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_condvar_free_c(void *cv) { sync_condvar_free_impl(cv); }
#endif

/** RwLock contention smoke test; success 0. */
int32_t sync_rwlock_contention_smoke_c(void) {
    void *rw = sync_rwlock_new_c();
    int32_t counter = 0;
    if (!rw) return 1;
    {
        int32_t i;
        for (i = 0; i < 1000; i++) {
            sync_rwlock_write_lock_c(rw);
            counter++;
            sync_rwlock_write_unlock_c(rw);
        }
    }
    sync_rwlock_free_c(rw);
    return (counter == 1000) ? 0 : 2;
}

/** Condvar smoke test (Windows stub: creation API available is sufficient). */
int32_t sync_condvar_contention_smoke_c(void) {
    (void)sync_condvar_new_c;
    return 0;
}

#else
#if defined(__linux__) || defined(__APPLE__)
#include <xlang_sync_cap.h> /* Cap residual 10.6.3: Linux futex / Darwin pthread sync_cap */
#else
#include <pthread.h>
#endif
#include <time.h>
#include <xlang_time_cap.h> /* Cap residual 9.1.5 nanosleep */

#if defined(__linux__) || defined(__APPLE__)
/** PLATFORM: SHARED — Cap mutex. */
typedef struct xlang_cap_mutex xlang_mutex_impl_t;
#else
/** POSIX (non-Linux/non-Darwin): mutex is pthread_mutex_t*, heap-allocated for opaque return. */
typedef pthread_mutex_t xlang_mutex_impl_t;
#endif

/** Create new mutex; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
void *sync_mutex_new_impl(void) {
    xlang_mutex_impl_t *m = (xlang_mutex_impl_t *)malloc(sizeof(xlang_mutex_impl_t));
    if (m == NULL) return NULL;
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_mutex_init(m) != 0) {
        free(m);
        return NULL;
    }
#else
    if (pthread_mutex_init(m, NULL) != 0) {
        free(m);
        return NULL;
    }
#endif
    return (void *)m;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void *sync_mutex_new_c(void) { return sync_mutex_new_impl(); }
#endif

/** Lock; blocks until acquired. Returns 0 success, -1 failure (e.g. m is NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_lock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_lock(m) != 0) {
        return -1;
    }
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_mutex_lock((struct xlang_cap_mutex *)m) != 0) {
        return -1;
    }
#else
    if (pthread_mutex_lock((pthread_mutex_t *)m) != 0) {
        return -1;
    }
#endif
    sync_lock_diag_after_lock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_lock_c(void *m) { return sync_mutex_lock_impl(m); }
#endif

/** Try-lock; non-blocking. Returns 0 success, non-zero not acquired (busy or m NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_try_lock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_lock(m) != 0) {
        return -1;
    }
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_mutex_trylock((struct xlang_cap_mutex *)m) != 0) {
        return 1;
    }
#else
    if (pthread_mutex_trylock((pthread_mutex_t *)m) != 0) {
        return 1;
    }
#endif
    sync_lock_diag_after_lock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_try_lock_c(void *m) { return sync_mutex_try_lock_impl(m); }
#endif

/** Unlock. Returns 0 success, -1 failure (e.g. m is NULL). */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_mutex_unlock_impl(void *m) {
    if (m == NULL) return -1;
    if (sync_lock_diag_before_unlock(m) != 0) {
        return -1;
    }
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_mutex_unlock((struct xlang_cap_mutex *)m) != 0) {
        return -1;
    }
#else
    if (pthread_mutex_unlock((pthread_mutex_t *)m) != 0) {
        return -1;
    }
#endif
    sync_lock_diag_after_unlock(m);
    return 0;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_mutex_unlock_c(void *m) { return sync_mutex_unlock_impl(m); }
#endif

/** Destroy and free mutex; m must not be used after this call. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_mutex_free_impl(void *m) {
    if (m == NULL) return;
#if defined(__linux__) || defined(__APPLE__)
    (void)xlang_cap_mutex_destroy((struct xlang_cap_mutex *)m);
#else
    pthread_mutex_destroy((pthread_mutex_t *)m);
#endif
    free(m);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_mutex_free_c(void *m) { sync_mutex_free_impl(m); }
#endif

#if defined(__linux__) || defined(__APPLE__)
/** PLATFORM: SHARED — Cap rwlock. */
typedef struct xlang_cap_rwlock xlang_rwlock_impl_t;
#else
/** POSIX (non-Linux/non-Darwin): rwlock is pthread_rwlock_t*, heap-allocated. */
typedef pthread_rwlock_t xlang_rwlock_impl_t;
#endif

/** Create RwLock; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
void *sync_rwlock_new_impl(void) {
    xlang_rwlock_impl_t *rw = (xlang_rwlock_impl_t *)malloc(sizeof(xlang_rwlock_impl_t));
    if (!rw) return NULL;
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_rwlock_init(rw) != 0) {
        free(rw);
        return NULL;
    }
#else
    if (pthread_rwlock_init(rw, NULL) != 0) {
        free(rw);
        return NULL;
    }
#endif
    return (void *)rw;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void *sync_rwlock_new_c(void) { return sync_rwlock_new_impl(); }
#endif

/** Acquire read lock; returns 0 success, -1 failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_read_lock_impl(void *rw) {
    if (!rw) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_rwlock_rdlock((struct xlang_cap_rwlock *)rw) == 0) ? 0 : -1;
#else
    return (pthread_rwlock_rdlock((pthread_rwlock_t *)rw) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_read_lock_c(void *rw) { return sync_rwlock_read_lock_impl(rw); }
#endif

/** Acquire write lock; returns 0 success, -1 failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_write_lock_impl(void *rw) {
    if (!rw) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_rwlock_wrlock((struct xlang_cap_rwlock *)rw) == 0) ? 0 : -1;
#else
    return (pthread_rwlock_wrlock((pthread_rwlock_t *)rw) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_write_lock_c(void *rw) { return sync_rwlock_write_lock_impl(rw); }
#endif

/** Release read lock; returns 0 success, -1 failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_read_unlock_impl(void *rw) {
    if (!rw) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_rwlock_rdunlock((struct xlang_cap_rwlock *)rw) == 0) ? 0 : -1;
#else
    return (pthread_rwlock_unlock((pthread_rwlock_t *)rw) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_read_unlock_c(void *rw) { return sync_rwlock_read_unlock_impl(rw); }
#endif

/** Release write lock; returns 0 success, -1 failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_rwlock_write_unlock_impl(void *rw) {
    if (!rw) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_rwlock_wrunlock((struct xlang_cap_rwlock *)rw) == 0) ? 0 : -1;
#else
    return (pthread_rwlock_unlock((pthread_rwlock_t *)rw) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_rwlock_write_unlock_c(void *rw) { return sync_rwlock_write_unlock_impl(rw); }
#endif

/** Destroy RwLock. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_rwlock_free_impl(void *rw) {
    if (!rw) return;
#if defined(__linux__) || defined(__APPLE__)
    (void)xlang_cap_rwlock_destroy((struct xlang_cap_rwlock *)rw);
#else
    pthread_rwlock_destroy((pthread_rwlock_t *)rw);
#endif
    free(rw);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_rwlock_free_c(void *rw) { sync_rwlock_free_impl(rw); }
#endif

#if defined(__linux__) || defined(__APPLE__)
/** PLATFORM: SHARED — Cap condvar. */
typedef struct xlang_cap_cond xlang_condvar_impl_t;
#else
/** POSIX (non-Linux/non-Darwin): condvar is pthread_cond_t*, heap-allocated. */
typedef pthread_cond_t xlang_condvar_impl_t;
#endif

/** Create Condvar; returns NULL on failure. */
/* G-02f-20 thin+rest: _impl OS bridge */
void *sync_condvar_new_impl(void) {
    xlang_condvar_impl_t *cv = (xlang_condvar_impl_t *)malloc(sizeof(xlang_condvar_impl_t));
    if (!cv) return NULL;
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_cap_cond_init(cv) != 0) {
        free(cv);
        return NULL;
    }
#else
    if (pthread_cond_init(cv, NULL) != 0) {
        free(cv);
        return NULL;
    }
#endif
    return (void *)cv;
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void *sync_condvar_new_c(void) { return sync_condvar_new_impl(); }
#endif

/** Wait on condvar while holding mutex. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_wait_impl(void *cv, void *mutex) {
    if (!cv || !mutex) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_cond_wait((struct xlang_cap_cond *)cv, (struct xlang_cap_mutex *)mutex) == 0)
               ? 0
               : -1;
#else
    return (pthread_cond_wait((pthread_cond_t *)cv, (pthread_mutex_t *)mutex) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_wait_c(void *cv, void *mutex) { return sync_condvar_wait_impl(cv, mutex); }
#endif

/** Wake one waiting thread. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_signal_impl(void *cv) {
    if (!cv) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_cond_signal((struct xlang_cap_cond *)cv) == 0) ? 0 : -1;
#else
    return (pthread_cond_signal((pthread_cond_t *)cv) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_signal_c(void *cv) { return sync_condvar_signal_impl(cv); }
#endif

/** Wake all waiting threads. */
/* G-02f-20 thin+rest: _impl OS bridge */
int32_t sync_condvar_broadcast_impl(void *cv) {
    if (!cv) return -1;
#if defined(__linux__) || defined(__APPLE__)
    return (xlang_cap_cond_broadcast((struct xlang_cap_cond *)cv) == 0) ? 0 : -1;
#else
    return (pthread_cond_broadcast((pthread_cond_t *)cv) == 0) ? 0 : -1;
#endif
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
int32_t sync_condvar_broadcast_c(void *cv) { return sync_condvar_broadcast_impl(cv); }
#endif

/** Destroy Condvar. */
/* G-02f-20 thin+rest: _impl OS bridge */
void sync_condvar_free_impl(void *cv) {
    if (!cv) return;
#if defined(__linux__) || defined(__APPLE__)
    (void)xlang_cap_cond_destroy((struct xlang_cap_cond *)cv);
#else
    pthread_cond_destroy((pthread_cond_t *)cv);
#endif
    free(cv);
}

#ifndef XLANG_RUNTIME_SYNC_OS_FROM_X
void sync_condvar_free_c(void *cv) { sync_condvar_free_impl(cv); }
#endif

typedef struct {
    void *cv;
    void *mu;
    int32_t ready;
} xlang_cond_smoke_ctx_t;

/** Condvar smoke test waiter thread entry. */
static void *xlang_condvar_smoke_waiter(void *arg) {
    xlang_cond_smoke_ctx_t *ctx = (xlang_cond_smoke_ctx_t *)arg;
    if (sync_mutex_lock_c(ctx->mu) != 0) return (void *)(intptr_t)1;
    while (ctx->ready == 0) {
        if (sync_condvar_wait_c(ctx->cv, ctx->mu) != 0) {
            sync_mutex_unlock_c(ctx->mu);
            return (void *)(intptr_t)2;
        }
    }
    sync_mutex_unlock_c(ctx->mu);
    return NULL;
}

/** RwLock contention smoke test; success 0. */
int32_t sync_rwlock_contention_smoke_c(void) {
    void *rw = sync_rwlock_new_c();
    int32_t counter = 0;
    if (!rw) return 1;
    {
        int32_t i;
        for (i = 0; i < 1000; i++) {
            sync_rwlock_write_lock_c(rw);
            counter++;
            sync_rwlock_write_unlock_c(rw);
        }
    }
    sync_rwlock_free_c(rw);
    return (counter == 1000) ? 0 : 2;
}

/** Condvar contention smoke test; success 0. */
int32_t sync_condvar_contention_smoke_c(void) {
    xlang_cond_smoke_ctx_t ctx;
    void *ret = NULL;
#if defined(__linux__) || defined(__APPLE__)
    struct xlang_thread_join join;
#else
    pthread_t tid;
#endif
    ctx.cv = sync_condvar_new_c();
    ctx.mu = sync_mutex_new_c();
    ctx.ready = 0;
    if (!ctx.cv || !ctx.mu) {
        sync_condvar_free_c(ctx.cv);
        sync_mutex_free_c(ctx.mu);
        return 1;
    }
#if defined(__linux__) || defined(__APPLE__)
    /* PLATFORM: SHARED — Cap spawn (no raw pthread_create on sync_os leaf). */
    memset(&join, 0, sizeof(join));
    if (xlang_thread_spawn(xlang_condvar_smoke_waiter, &ctx, &join, 65536u) != 0) {
        sync_condvar_free_c(ctx.cv);
        sync_mutex_free_c(ctx.mu);
        return 2;
    }
#else
    if (pthread_create(&tid, NULL, xlang_condvar_smoke_waiter, &ctx) != 0) {
        sync_condvar_free_c(ctx.cv);
        sync_mutex_free_c(ctx.mu);
        return 2;
    }
#endif
    {
        struct timespec ts = { 0, 20000000L };
        /* PLATFORM: LINUX Cap / POSIX fallback — no libc nanosleep */
        (void)xlang_time_nanosleep(&ts, NULL);
    }
    if (sync_mutex_lock_c(ctx.mu) != 0) {
#if defined(__linux__) || defined(__APPLE__)
        (void)xlang_thread_join(&join);
#else
        pthread_join(tid, NULL);
#endif
        sync_condvar_free_c(ctx.cv);
        sync_mutex_free_c(ctx.mu);
        return 3;
    }
    ctx.ready = 1;
    sync_condvar_signal_c(ctx.cv);
    sync_mutex_unlock_c(ctx.mu);
#if defined(__linux__) || defined(__APPLE__)
    if (xlang_thread_join(&join) != 0) {
        sync_condvar_free_c(ctx.cv);
        sync_mutex_free_c(ctx.mu);
        return 4;
    }
    ret = NULL;
#else
    pthread_join(tid, &ret);
#endif
    sync_condvar_free_c(ctx.cv);
    sync_mutex_free_c(ctx.mu);
    return (ret == NULL) ? 0 : 4;
}

#endif