/* seeds/runtime_queue_contention.from_x.c — G-02f-21 product TU
 * R2 migration: OS-level _impl bridges + thin-rest pattern.
 * Thin wrappers (queue_os_*_c, queue_smoke_*, sync_queue_contention_smoke_c)
 * are provided by runtime_queue_contention.x when XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X
 * is defined (R2 path); otherwise this seed provides both _impl and _c wrappers.
 *
 * PLATFORM: SHARED Cap (Linux futex / Darwin pthread / Windows Win32 sync_cap + thread_cap).
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <xlang_sync_cap.h>   /* Cap residual 9.4.4 / 9.4.5: full-closure tri-platform sync primitives */
#include <xlang_thread_cap.h> /* Cap residual 9.4.4 / 9.4.5: full-closure tri-platform thread primitives */

/* Smoke state matching QueueSmokeState layout in runtime_queue_contention.x. */
typedef struct {
  void *mu;
  int32_t *data;
  int32_t cap;
  int32_t length;
  int32_t head;
} QueueSmokeState;

typedef struct xlang_cap_mutex queue_os_mutex_t;

/* POSIX / Cap thread start routine: public trampoline exists in both hybrid thin
 * (runtime_queue_contention.x) and cold seed. Rest must not U the thin-only
 * queue_os_worker_trampoline_impl (mac run-queue Darwin UNDEF after L4). */
void *queue_os_worker_trampoline(void *arg);

/* Thin function forward declarations for rest-only call sites in R2 mode. */
#ifndef XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X
void *queue_os_mutex_create_c(void);
void queue_os_mutex_destroy_c(void *mu);
void queue_os_mutex_lock_c(void *mu);
void queue_os_mutex_unlock_c(void *mu);
int32_t queue_os_run_two_workers_c(void *ctx);
int32_t queue_smoke_at_impl(QueueSmokeState *q, int32_t i);
int32_t queue_smoke_push_back_impl(QueueSmokeState *q, int32_t x);
int32_t queue_contention_worker_push_c(void *ctx);
int32_t sync_queue_contention_smoke_c(void);
#endif

/* ----- OS _impl bridges (always compiled, provide _impl symbols). ----- */

/** Create mutex (xlang_cap_mutex_init). Returns opaque ptr or NULL. */
void *queue_os_mutex_create_impl(void) {
    queue_os_mutex_t *m = (queue_os_mutex_t *)malloc(sizeof(queue_os_mutex_t));
    if (!m)
        return NULL;
    if (xlang_cap_mutex_init(m) != 0) {
        free(m);
        return NULL;
    }
    return (void *)m;
}

/** Destroy mutex and free backing memory. */
void queue_os_mutex_destroy_impl(void *mu) {
    if (!mu)
        return;
    (void)xlang_cap_mutex_destroy((queue_os_mutex_t *)mu);
    free(mu);
}

/** Lock mutex (xlang_cap_mutex_lock). */
void queue_os_mutex_lock_impl(void *mu) {
    if (!mu)
        return;
    (void)xlang_cap_mutex_lock((queue_os_mutex_t *)mu);
}

/** Unlock mutex (xlang_cap_mutex_unlock). */
void queue_os_mutex_unlock_impl(void *mu) {
    if (!mu)
        return;
    (void)xlang_cap_mutex_unlock((queue_os_mutex_t *)mu);
}

/** Launch two worker threads via Cap spawn, join both.
 *  Returns 0 on success, -1 on failure.
 *  Start routine is queue_os_worker_trampoline across all platforms. */
int32_t queue_os_run_two_workers_impl(void *ctx) {
    struct xlang_thread_join j0, j1;
    if (xlang_thread_spawn((xlang_thread_start_fn)queue_os_worker_trampoline, ctx, &j0, 65536u) != 0)
        return -1;
    if (xlang_thread_spawn((xlang_thread_start_fn)queue_os_worker_trampoline, ctx, &j1, 65536u) != 0) {
        (void)xlang_thread_join(&j0);
        return -1;
    }
    if (xlang_thread_join(&j0) != 0) {
        (void)xlang_thread_join(&j1);
        return -1;
    }
    if (xlang_thread_join(&j1) != 0)
        return -1;
    return 0;
}

/* ----- Thin wrappers (guarded in R2 mode: provided by runtime_queue_contention.x). ----- */

#ifndef XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X
/* Cold path: provide _c wrappers that delegate to _impl. */

void *queue_os_mutex_create_c(void) {
    return queue_os_mutex_create_impl();
}

void queue_os_mutex_destroy_c(void *mu) {
    queue_os_mutex_destroy_impl(mu);
}

void queue_os_mutex_lock_c(void *mu) {
    queue_os_mutex_lock_impl(mu);
}

void queue_os_mutex_unlock_c(void *mu) {
    queue_os_mutex_unlock_impl(mu);
}

int32_t queue_os_run_two_workers_c(void *ctx) {
    return queue_os_run_two_workers_impl(ctx);
}

#endif /* !XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X */

/* ----- Smoke test helpers (guarded in R2: provided by .x thin). ----- */

#ifndef XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X
/* Cold path: smoke test logic implemented in seed C. */

int32_t queue_smoke_at_impl(QueueSmokeState *q, int32_t i) {
    int32_t idx = q->head + i;
    if (idx >= q->cap) {
        idx -= q->cap;
    }
    return idx;
}

int32_t queue_smoke_at(QueueSmokeState *q, int32_t i) {
    return queue_smoke_at_impl(q, i);
}

int32_t queue_smoke_push_back_impl(QueueSmokeState *q, int32_t x) {
    int32_t new_cap;
    int32_t *p;
    int32_t i;
    if (!q) {
        return -1;
    }
    if (q->length >= q->cap) {
        if (q->cap <= 0) {
            new_cap = 8;
        } else {
            new_cap = q->cap * 2;
        }
        p = (int32_t *)malloc((size_t)new_cap * sizeof(int32_t));
        if (!p) {
            return -1;
        }
        for (i = 0; i < q->length; i++) {
            p[i] = q->data[queue_smoke_at(q, i)];
        }
        if (q->data) {
            free(q->data);
        }
        q->data = p;
        q->cap = new_cap;
        q->head = 0;
    }
    q->data[queue_smoke_at(q, q->length)] = x;
    q->length++;
    return 0;
}

int32_t queue_smoke_push_back(QueueSmokeState *q, int32_t x) {
    return queue_smoke_push_back_impl(q, x);
}

int32_t queue_contention_worker_push_c(void *ctx) {
    QueueSmokeState *q = (QueueSmokeState *)ctx;
    int32_t i;
    if (!q) {
        return -1;
    }
    for (i = 0; i < 500; i++) {
        queue_os_mutex_lock_c(q->mu);
        queue_smoke_push_back(q, 1);
        queue_os_mutex_unlock_c(q->mu);
    }
    return 0;
}

/* Trampoline (cold path only: thin provides this in R2).
 * Marked static to avoid symbol collision with thin-provided
 * queue_os_worker_trampoline_impl in ld -r merge.
 * PLATFORM: SHARED Cap. */
static void *queue_os_worker_trampoline_impl_cold(void *arg) {
    (void)queue_contention_worker_push_c(arg);
    return NULL;
}

void *queue_os_worker_trampoline(void *arg) {
    return queue_os_worker_trampoline_impl_cold(arg);
}

/** STD-048 sync_queue_contention_smoke_c (cold path). */
int32_t sync_queue_contention_smoke_c(void) {
  QueueSmokeState st;
  int32_t rc = -1;
  memset(&st, 0, sizeof(st));
  st.mu = queue_os_mutex_create_c();
  if (!st.mu) {
    return -1;
  }
  if (queue_os_run_two_workers_c(&st) != 0) {
    queue_os_mutex_destroy_c(st.mu);
    if (st.data) {
      free(st.data);
    }
    return -1;
  }
  rc = (st.length == 1000) ? 0 : -1;
  if (st.data) {
    free(st.data);
  }
  queue_os_mutex_destroy_c(st.mu);
  return rc;
}

#endif /* !XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X */
