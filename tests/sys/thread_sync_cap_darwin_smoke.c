/*
 * thread_sync_cap_darwin_smoke.c — Stage 10 (10.6.1 / 10.6.3) Darwin Cap residual probe.
 *
 * Host-cc smoke for xlang_thread_cap.h and xlang_sync_cap.h on Darwin/macOS:
 *   1. xlang_thread_spawn + xlang_thread_join
 *   2. xlang_cap_mutex init/lock/trylock/unlock/destroy
 *   3. xlang_cap_cond init/wait/signal/broadcast/destroy
 *   4. xlang_cap_sem init/wait/trywait/post/destroy
 *   5. xlang_cap_rwlock init/rdlock/wrlock/rdunlock/wrunlock/destroy
 *
 * PLATFORM: DARWIN gold; non-Darwin returns 0.
 *
 * Exit: 0 ok; 1..10 step failure.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_sync_cap.h>
#include <xlang_thread_cap.h>

#ifndef __APPLE__
int main(void) {
  fprintf(stderr, "thread_sync_cap_darwin_smoke: Darwin only\n");
  return 0;
}
#else

/* --- Test 1: Basic thread spawn & join --- */
static volatile int g_child_val = 0;

static void *child_fn_1(void *arg) {
  (void)arg;
  g_child_val = 42;
  return 0;
}

/* --- Test 2: Mutex concurrent increment --- */
static struct xlang_cap_mutex g_mu;
static volatile int g_counter = 0;

static void *child_fn_mutex(void *arg) {
  int i;
  (void)arg;
  for (i = 0; i < 500; i++) {
    if (xlang_cap_mutex_lock(&g_mu) != 0) return 0;
    g_counter++;
    (void)xlang_cap_mutex_unlock(&g_mu);
  }
  return 0;
}

/* --- Test 3: Condvar signal --- */
static struct xlang_cap_mutex g_cv_mu;
static struct xlang_cap_cond g_cv;
static volatile int g_ready = 0;

static void *child_fn_cond(void *arg) {
  (void)arg;
  if (xlang_cap_mutex_lock(&g_cv_mu) != 0) return 0;
  while (g_ready == 0) {
    if (xlang_cap_cond_wait(&g_cv, &g_cv_mu) != 0) {
      xlang_cap_mutex_unlock(&g_cv_mu);
      return 0;
    }
  }
  (void)xlang_cap_mutex_unlock(&g_cv_mu);
  return 0;
}

/* --- Test 4: RWLock writer contention --- */
static struct xlang_cap_rwlock g_rw;
static volatile int g_rw_val = 0;

static void *child_fn_rwlock(void *arg) {
  int i;
  (void)arg;
  for (i = 0; i < 200; i++) {
    if (xlang_cap_rwlock_wrlock(&g_rw) != 0) return 0;
    g_rw_val++;
    (void)xlang_cap_rwlock_wrunlock(&g_rw);
  }
  return 0;
}

int main(void) {
  /* Step 1: Thread spawn and join */
  {
    struct xlang_thread_join join;
    memset(&join, 0, sizeof(join));
    g_child_val = 0;
    if (xlang_thread_spawn(child_fn_1, NULL, &join, 65536u) != 0) {
      fprintf(stderr, "FAIL: step 1 spawn\n");
      return 1;
    }
    if (xlang_thread_join(&join) != 0) {
      fprintf(stderr, "FAIL: step 1 join\n");
      return 2;
    }
    if (g_child_val != 42) {
      fprintf(stderr, "FAIL: step 1 val\n");
      return 3;
    }
  }

  /* Step 2: Mutex */
  {
    struct xlang_thread_join join;
    int i;
    memset(&join, 0, sizeof(join));
    if (xlang_cap_mutex_init(&g_mu) != 0) {
      fprintf(stderr, "FAIL: step 2 mutex init\n");
      return 4;
    }
    g_counter = 0;
    if (xlang_thread_spawn(child_fn_mutex, NULL, &join, 65536u) != 0) {
      fprintf(stderr, "FAIL: step 2 spawn\n");
      return 5;
    }
    for (i = 0; i < 500; i++) {
      if (xlang_cap_mutex_lock(&g_mu) != 0) return 6;
      g_counter++;
      (void)xlang_cap_mutex_unlock(&g_mu);
    }
    if (xlang_thread_join(&join) != 0) {
      fprintf(stderr, "FAIL: step 2 join\n");
      return 7;
    }
    if (g_counter != 1000) {
      fprintf(stderr, "FAIL: step 2 counter=%d want 1000\n", g_counter);
      return 8;
    }
    xlang_cap_mutex_destroy(&g_mu);
  }

  /* Step 3: Condvar */
  {
    struct xlang_thread_join join;
    memset(&join, 0, sizeof(join));
    if (xlang_cap_mutex_init(&g_cv_mu) != 0) return 9;
    if (xlang_cap_cond_init(&g_cv) != 0) return 10;
    g_ready = 0;
    if (xlang_thread_spawn(child_fn_cond, NULL, &join, 65536u) != 0) return 11;
    if (xlang_cap_mutex_lock(&g_cv_mu) != 0) return 12;
    g_ready = 1;
    if (xlang_cap_cond_signal(&g_cv) != 0) return 13;
    if (xlang_cap_mutex_unlock(&g_cv_mu) != 0) return 14;
    if (xlang_thread_join(&join) != 0) return 15;
    xlang_cap_cond_destroy(&g_cv);
    xlang_cap_mutex_destroy(&g_cv_mu);
  }

  /* Step 4: Semaphore */
  {
    struct xlang_cap_sem sem;
    if (xlang_cap_sem_init(&sem, 1) != 0) return 16;
    if (xlang_cap_sem_wait(&sem) != 0) return 17;
    if (xlang_cap_sem_trywait(&sem) == 0) return 18; /* Should fail with EAGAIN */
    if (xlang_cap_sem_post(&sem) != 0) return 19;
    if (xlang_cap_sem_wait(&sem) != 0) return 20;
    xlang_cap_sem_destroy(&sem);
  }

  /* Step 5: RWLock */
  {
    struct xlang_thread_join join;
    int i;
    memset(&join, 0, sizeof(join));
    if (xlang_cap_rwlock_init(&g_rw) != 0) return 21;
    g_rw_val = 0;
    if (xlang_thread_spawn(child_fn_rwlock, NULL, &join, 65536u) != 0) return 22;
    for (i = 0; i < 200; i++) {
      if (xlang_cap_rwlock_wrlock(&g_rw) != 0) return 23;
      g_rw_val++;
      (void)xlang_cap_rwlock_wrunlock(&g_rw);
    }
    if (xlang_thread_join(&join) != 0) return 24;
    if (g_rw_val != 400) {
      fprintf(stderr, "FAIL: step 5 g_rw_val=%d want 400\n", g_rw_val);
      return 25;
    }
    /* Verify read lock */
    if (xlang_cap_rwlock_rdlock(&g_rw) != 0) return 26;
    if (xlang_cap_rwlock_rdunlock(&g_rw) != 0) return 27;
    xlang_cap_rwlock_destroy(&g_rw);
  }

  return 0;
}
#endif
