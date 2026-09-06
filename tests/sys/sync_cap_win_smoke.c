/*
 * sync_cap_win_smoke.c — Stage 10 (10.6.3) Windows Cap sync primitives smoke.
 *
 * Host-cc smoke test for xlang_sync_cap.h Windows implementation:
 * - xlang_cap_mutex (CRITICAL_SECTION)
 * - xlang_cap_cond (CONDITION_VARIABLE)
 * - xlang_cap_sem (Semaphore HANDLE)
 * - xlang_cap_rwlock (SRWLOCK)
 *
 * PLATFORM: WINDOWS gold when MSYS/Win host available; non-Win gate skip=1.
 * Exit code: 0 on success, 1..10 on specific failure step.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_sync_cap.h>
#include <xlang_thread_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)

int main(void) {
  fprintf(stderr, "sync_cap_win_smoke: Windows only\n");
  return 0;
}

#else

/* Shared context for condvar test. */
struct cond_test_ctx {
  struct xlang_cap_mutex mu;
  struct xlang_cap_cond cv;
  volatile int ready;
};

/**
 * Worker thread entry for condvar wake test.
 * @param arg pointer to struct cond_test_ctx
 * @return NULL
 * PLATFORM: WINDOWS
 */
static void *cond_worker_entry(void *arg) {
  struct cond_test_ctx *ctx = (struct cond_test_ctx *)arg;
  Sleep(10);
  xlang_cap_mutex_lock(&ctx->mu);
  ctx->ready = 1;
  xlang_cap_cond_signal(&ctx->cv);
  xlang_cap_mutex_unlock(&ctx->mu);
  return NULL;
}

/**
 * Smoke test entry testing mutex, condvar, semaphore, and rwlock on Windows.
 * @return 0 on success, nonzero step failure
 * PLATFORM: WINDOWS
 */
int main(void) {
  /* 1. Test Cap Mutex */
  {
    struct xlang_cap_mutex mu;
    if (xlang_cap_mutex_init(&mu) != 0) {
      fprintf(stderr, "mutex_init failed\n");
      return 1;
    }
    if (xlang_cap_mutex_lock(&mu) != 0) {
      fprintf(stderr, "mutex_lock failed\n");
      return 2;
    }
    if (xlang_cap_mutex_unlock(&mu) != 0) {
      fprintf(stderr, "mutex_unlock failed\n");
      return 3;
    }
    if (xlang_cap_mutex_trylock(&mu) != 0) {
      fprintf(stderr, "mutex_trylock when free failed\n");
      return 4;
    }
    if (xlang_cap_mutex_unlock(&mu) != 0) {
      fprintf(stderr, "mutex_unlock after trylock failed\n");
      return 5;
    }
    if (xlang_cap_mutex_destroy(&mu) != 0) {
      fprintf(stderr, "mutex_destroy failed\n");
      return 6;
    }
  }

  /* 2. Test Cap Condvar */
  {
    struct cond_test_ctx ctx;
    struct xlang_thread_join join;
    memset(&ctx, 0, sizeof(ctx));
    memset(&join, 0, sizeof(join));

    if (xlang_cap_mutex_init(&ctx.mu) != 0 || xlang_cap_cond_init(&ctx.cv) != 0) {
      fprintf(stderr, "cond ctx init failed\n");
      return 7;
    }
    if (xlang_thread_spawn(cond_worker_entry, &ctx, &join, 65536u) != 0) {
      fprintf(stderr, "cond thread spawn failed\n");
      return 8;
    }
    xlang_cap_mutex_lock(&ctx.mu);
    while (!ctx.ready) {
      xlang_cap_cond_wait(&ctx.cv, &ctx.mu);
    }
    xlang_cap_mutex_unlock(&ctx.mu);

    if (xlang_thread_join(&join) != 0) {
      fprintf(stderr, "cond thread join failed\n");
      return 9;
    }
    xlang_cap_cond_destroy(&ctx.cv);
    xlang_cap_mutex_destroy(&ctx.mu);
  }

  /* 3. Test Cap Semaphore */
  {
    struct xlang_cap_sem sem;
    if (xlang_cap_sem_init(&sem, 1) != 0) {
      fprintf(stderr, "sem_init failed\n");
      return 10;
    }
    if (xlang_cap_sem_wait(&sem) != 0) {
      fprintf(stderr, "sem_wait failed\n");
      return 11;
    }
    if (xlang_cap_sem_trywait(&sem) == 0) {
      fprintf(stderr, "sem_trywait unexpectedly succeeded\n");
      return 12;
    }
    if (xlang_cap_sem_post(&sem) != 0) {
      fprintf(stderr, "sem_post failed\n");
      return 13;
    }
    if (xlang_cap_sem_trywait(&sem) != 0) {
      fprintf(stderr, "sem_trywait failed after post\n");
      return 14;
    }
    if (xlang_cap_sem_destroy(&sem) != 0) {
      fprintf(stderr, "sem_destroy failed\n");
      return 15;
    }
  }

  /* 4. Test Cap RWLock */
  {
    struct xlang_cap_rwlock rw;
    if (xlang_cap_rwlock_init(&rw) != 0) {
      fprintf(stderr, "rwlock_init failed\n");
      return 16;
    }
    if (xlang_cap_rwlock_rdlock(&rw) != 0) {
      fprintf(stderr, "rwlock_rdlock failed\n");
      return 17;
    }
    if (xlang_cap_rwlock_rdunlock(&rw) != 0) {
      fprintf(stderr, "rwlock_rdunlock failed\n");
      return 18;
    }
    if (xlang_cap_rwlock_wrlock(&rw) != 0) {
      fprintf(stderr, "rwlock_wrlock failed\n");
      return 19;
    }
    if (xlang_cap_rwlock_wrunlock(&rw) != 0) {
      fprintf(stderr, "rwlock_wrunlock failed\n");
      return 20;
    }
    if (xlang_cap_rwlock_destroy(&rw) != 0) {
      fprintf(stderr, "rwlock_destroy failed\n");
      return 21;
    }
  }

  printf("sync_cap_win_smoke: all tests passed\n");
  return 0;
}

#endif
