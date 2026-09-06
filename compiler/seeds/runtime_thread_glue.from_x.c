/* seeds/runtime_thread_glue.from_x.c — G-02f-18 product TU
 * G-02f-102 helper gates.
 * Product: runtime_thread_glue.o; OS bridge logic in rest C; public wrappers
 * provided by thin runtime_thread_glue.x in R2 mode (XLANG_RUNTIME_THREAD_GLUE_FROM_X).
 *
 * runtime_thread_glue.c — Thread glue (migrated from std/thread/thread_glue.c)
 *
 * [File role] thread_self/create/join/affinity/QoS/name + worker pool; linked
 *            alongside thread.o into exe.
 *            POSIX requires -lpthread; Windows requires kernel32.
 *
 * Wave513 (2026-07-27): R2 full migration. All public `_c` wrappers moved to
 * .x (thin); this file now provides `_impl` OS bridge implementations only,
 * with cold-mode fallback wrappers under #ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X.
 *
 * PLATFORM: SHARED — LINUX Cap spawn/join/pool (xlang_thread_cap + sync_cap);
 *           Darwin/other POSIX pthread;
 *           WINDOWS Cap CreateThread spawn/join (10.6.2; kernel32).
 */

#if defined(__linux__)
#define _GNU_SOURCE
#endif
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* ========== Linux: cpu_set_t bitmap helpers ========== */
#if defined(__linux__)
#include <sched.h>
#include <string.h>

/* Forward declarations for thin-provided _c functions (R2 / FROM_X mode).
 * In cold mode the _c wrappers are defined below. */
void xlang_cpu_zero(cpu_set_t *set);
void xlang_cpu_set(unsigned int cpu, cpu_set_t *set);

/* R2 rest: _impl implementation; thin (runtime_thread_glue.x) provides public wrapper.
 * Hand-rolled bitmap to avoid dependency on CPU_ZERO/CPU_SET/CPU_ZERO_S/CPU_SET_S
 * link symbols (some glibc versions leave them undefined). */
void xlang_cpu_zero_impl(cpu_set_t *set) {
    memset(set, 0, sizeof(cpu_set_t));
}

void xlang_cpu_set_impl(unsigned int cpu, cpu_set_t *set) {
    if (cpu < sizeof(cpu_set_t) * 8) {
        size_t idx = cpu / (8 * sizeof(unsigned long));
        size_t bit = cpu % (8 * sizeof(unsigned long));
        ((unsigned long *)set)[idx] |= (unsigned long)1 << bit;
    }
}

#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
/* Cold mode fallback: public wrapper provided by seed. */
void xlang_cpu_zero(cpu_set_t *set) {
    xlang_cpu_zero_impl(set);
}
void xlang_cpu_set(unsigned int cpu, cpu_set_t *set) {
    xlang_cpu_set_impl(cpu, set);
}
#endif
#else
/* Non-Linux fallback stubs for CPU set helpers */
void xlang_cpu_zero_impl(void *set) {
    if (set) memset(set, 0, 128);
}
void xlang_cpu_set_impl(unsigned int cpu, void *set) {
    (void)cpu; (void)set;
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
void xlang_cpu_zero(void *set) { xlang_cpu_zero_impl(set); }
void xlang_cpu_set(unsigned int cpu, void *set) { xlang_cpu_set_impl(cpu, set); }
#endif
#endif /* __linux__ */

/* ========== Platform threading base ========== */
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_sync_cap.h> /* Cap residual 10.6.2 / 10.6.3: Win32 sync/thread cap */
#include <xlang_thread_cap.h> /* Cap residual 10.6.2: CreateThread spawn/join */
/* Windows Cap: thread_id is heap `struct xlang_thread_join *` (owned until join). */
#define XLANG_THREAD_ID_INVALID ((int64_t)0)
#define XLANG_THREAD_CAP_DEFAULT_STACK (256u * 1024u)
#elif defined(__linux__)
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <xlang_sync_cap.h> /* Cap mutex/cond + thread spawn (10.6.1 slice2) */
/** Default Cap stack when caller omits size (pthread default is larger; Cap floor 16KiB). */
#define XLANG_THREAD_CAP_DEFAULT_STACK (256u * 1024u)
/** thread_id is heap `struct xlang_thread_join *` (owned until join). */
#define XLANG_THREAD_ID_INVALID ((int64_t)0)
#elif defined(__APPLE__)
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/qos.h>
#include <xlang_sync_cap.h> /* Cap residual 10.6.1 / 10.6.3: Darwin Cap spawn/join/pool */
#define XLANG_THREAD_CAP_DEFAULT_STACK (256u * 1024u)
#define XLANG_THREAD_ID_INVALID ((int64_t)0)
#else
#include <pthread.h>
#include <stdlib.h>
typedef pthread_t xlang_thread_t;
#define XLANG_THREAD_ID_INVALID ((int64_t)0)
#endif

/* Forward declarations for thin-provided _c functions (R2 / FROM_X mode). */
int64_t thread_self_c(void);
int64_t thread_create_c(void *entry, void *arg);
int64_t thread_create_with_stack_c(void *entry, void *arg, size_t stack_size);
int32_t thread_join_c(int64_t thread_id);
int32_t thread_set_affinity_self_c(int32_t cpu_index);
int32_t thread_set_affinity_c(int64_t thread_id, int32_t cpu_index);
int32_t thread_set_qos_class_self_c(int32_t qos_class);
int32_t thread_set_name_self_c(const uint8_t *name, int32_t len);
uintptr_t thread_dummy_entry_ptr_c(void);
int32_t thread_pool_start_c(int32_t workers);
int32_t thread_pool_submit_c(uintptr_t entry, uintptr_t arg);
int32_t thread_pool_drain_c(void);
int32_t thread_pool_stop_c(void);
int32_t thread_pool_pending_c(void);
int64_t std_thread_thread_self_c(void);
int64_t std_thread_thread_create_c(void *entry, void *arg);
int64_t std_thread_thread_create_with_stack_c(void *entry, void *arg, size_t stack_size);
int32_t std_thread_thread_join_c(int64_t thread_id);
int32_t std_thread_thread_set_affinity_self_c(int32_t cpu_index);
int32_t std_thread_thread_set_affinity_c(int64_t thread_id, int32_t cpu_index);
int32_t std_thread_thread_set_qos_class_self_c(int32_t qos_class);
uintptr_t std_thread_thread_dummy_entry_ptr_c(void);

/* ========== _impl: thread_self ========== */
int64_t thread_self_impl(void) {
#if defined(_WIN32) || defined(_WIN64)
    return (int64_t)(intptr_t)GetCurrentThreadId();
#elif defined(__linux__)
    /* PLATFORM: LINUX — Cap path uses gettid (no pthread_self). */
    return (int64_t)syscall(SYS_gettid);
#else
    return (int64_t)(uintptr_t)pthread_self();
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int64_t thread_self_c(void) { return thread_self_impl(); }
#endif

/* ========== _impl: thread_create ========== */
int64_t thread_create_impl(void *entry, void *arg) {
    if (entry == NULL) return XLANG_THREAD_ID_INVALID;
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__) || defined(__APPLE__)
    {
        /* PLATFORM: SHARED Cap (Linux futex / Windows CreateThread / Darwin pthread) — spawn; thread_id = heap join handle. */
        struct xlang_thread_join *join =
            (struct xlang_thread_join *)malloc(sizeof(struct xlang_thread_join));
        if (join == NULL) return XLANG_THREAD_ID_INVALID;
        memset(join, 0, sizeof(*join));
        if (xlang_thread_spawn((xlang_thread_start_fn)entry, arg, join,
                               XLANG_THREAD_CAP_DEFAULT_STACK) != 0) {
            free(join);
            return XLANG_THREAD_ID_INVALID;
        }
        return (int64_t)(uintptr_t)join;
    }
#else
    {
        pthread_t tid;
        if (pthread_create(&tid, NULL, (void *(*)(void *))entry, arg) != 0)
            return XLANG_THREAD_ID_INVALID;
        return (int64_t)(uintptr_t)tid;
    }
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int64_t thread_create_c(void *entry, void *arg) { return thread_create_impl(entry, arg); }
#endif

/* ========== _impl: thread_create_with_stack ========== */
int64_t thread_create_with_stack_impl(void *entry, void *arg, size_t stack_size) {
    if (entry == NULL) return XLANG_THREAD_ID_INVALID;
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__) || defined(__APPLE__)
    {
        /* PLATFORM: SHARED Cap — spawn with explicit stack. */
        struct xlang_thread_join *join =
            (struct xlang_thread_join *)malloc(sizeof(struct xlang_thread_join));
        size_t slen = stack_size;
        if (join == NULL) return XLANG_THREAD_ID_INVALID;
        if (slen == 0) {
            slen = XLANG_THREAD_CAP_DEFAULT_STACK;
        }
#if defined(__linux__)
        else if (slen < 16384u) {
            slen = 16384u;
        }
#endif
        memset(join, 0, sizeof(*join));
        if (xlang_thread_spawn((xlang_thread_start_fn)entry, arg, join, slen) != 0) {
            free(join);
            return XLANG_THREAD_ID_INVALID;
        }
        return (int64_t)(uintptr_t)join;
    }
#else
    {
        pthread_t tid;
        if (stack_size == 0) {
            if (pthread_create(&tid, NULL, (void *(*)(void *))entry, arg) != 0)
                return XLANG_THREAD_ID_INVALID;
            return (int64_t)(uintptr_t)tid;
        }
        pthread_attr_t attr;
        if (pthread_attr_init(&attr) != 0) return XLANG_THREAD_ID_INVALID;
        if (pthread_attr_setstacksize(&attr, stack_size) != 0) {
            pthread_attr_destroy(&attr);
            return XLANG_THREAD_ID_INVALID;
        }
        int ret = pthread_create(&tid, &attr, (void *(*)(void *))entry, arg);
        pthread_attr_destroy(&attr);
        if (ret != 0) return XLANG_THREAD_ID_INVALID;
        return (int64_t)(uintptr_t)tid;
    }
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int64_t thread_create_with_stack_c(void *entry, void *arg, size_t stack_size) {
    return thread_create_with_stack_impl(entry, arg, stack_size);
}
#endif

/* ========== _impl: thread_join ========== */
int32_t thread_join_impl(int64_t thread_id) {
    if (thread_id == XLANG_THREAD_ID_INVALID) return -1;
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__) || defined(__APPLE__)
    {
        /* PLATFORM: SHARED Cap — join then free heap handle. */
        struct xlang_thread_join *join = (struct xlang_thread_join *)(uintptr_t)thread_id;
        if (xlang_thread_join(join) != 0) {
            free(join);
            return -1;
        }
        free(join);
        return 0;
    }
#else
    {
        pthread_t tid = (pthread_t)(uintptr_t)thread_id;
        if (pthread_join(tid, NULL) != 0) return -1;
        return 0;
    }
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_join_c(int64_t thread_id) { return thread_join_impl(thread_id); }
#endif

/* ========== _impl: thread_set_affinity_self (Cap residual 9.4.6) ========== */
int32_t thread_set_affinity_self_impl(int32_t cpu_index) {
    return xlang_thread_set_affinity_self(cpu_index);
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_set_affinity_self_c(int32_t cpu_index) {
    return thread_set_affinity_self_impl(cpu_index);
}
#endif

/* ========== _impl: thread_set_affinity (Cap residual 9.4.6) ========== */
int32_t thread_set_affinity_impl(int64_t thread_id, int32_t cpu_index) {
    if (thread_id == XLANG_THREAD_ID_INVALID) return -1;
    struct xlang_thread_join *join = (struct xlang_thread_join *)(uintptr_t)thread_id;
    return xlang_thread_set_affinity(join, cpu_index);
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_set_affinity_c(int64_t thread_id, int32_t cpu_index) {
    return thread_set_affinity_impl(thread_id, cpu_index);
}
#endif

/* ========== _impl: thread_set_qos_class_self (Cap residual 9.4.6) ========== */
int32_t thread_set_qos_class_self_impl(int32_t qos_class) {
    return xlang_thread_set_qos_self(qos_class);
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_set_qos_class_self_c(int32_t qos_class) {
    return thread_set_qos_class_self_impl(qos_class);
}
#endif

/* ========== _impl: thread_set_name_self ========== */
int32_t thread_set_name_self_impl(const uint8_t *name, int32_t len) {
    char buf[16];
    int32_t i;
    if (!name || len < 0) {
        return -1;
    }
    if (len > 15) {
        len = 15;
    }
    for (i = 0; i < len; i++) {
        buf[i] = (char)name[i];
    }
    buf[len] = '\0';
#if defined(__linux__)
    /* PLATFORM: LINUX — prctl (no pthread_setname_np). */
    if (prctl(PR_SET_NAME, (unsigned long)buf, 0, 0, 0) != 0) {
        return -1;
    }
    return 0;
#elif defined(__APPLE__)
    if (pthread_setname_np(buf) != 0) {
        return -1;
    }
    return 0;
#else
    (void)buf;
    return -1;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_set_name_self_c(const uint8_t *name, int32_t len) {
    return thread_set_name_self_impl(name, len);
}
#endif

/* ========== thread_dummy_entry (real C function; address-taken via ptr_c) ========== */
void *thread_dummy_entry(void *arg) {
    (void)arg;
    return NULL;
}

/* ========== _impl: thread_dummy_entry_ptr (returns address of thread_dummy_entry) ========== */
uintptr_t thread_dummy_entry_ptr_impl(void) {
    return (uintptr_t)&thread_dummy_entry;
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
uintptr_t thread_dummy_entry_ptr_c(void) {
    return thread_dummy_entry_ptr_impl();
}
#endif

/* ========== std.thread pipeline wrappers ========== */
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int64_t std_thread_thread_self_c(void) { return thread_self_c(); }
int64_t std_thread_thread_create_c(void *entry, void *arg) { return thread_create_c(entry, arg); }
int64_t std_thread_thread_create_with_stack_c(void *entry, void *arg, size_t stack_size) {
    return thread_create_with_stack_c(entry, arg, stack_size);
}
int32_t std_thread_thread_join_c(int64_t thread_id) { return thread_join_c(thread_id); }
int32_t std_thread_thread_set_affinity_self_c(int32_t cpu_index) {
    return thread_set_affinity_self_c(cpu_index);
}
int32_t std_thread_thread_set_affinity_c(int64_t thread_id, int32_t cpu_index) {
    return thread_set_affinity_c(thread_id, cpu_index);
}
int32_t std_thread_thread_set_qos_class_self_c(int32_t qos_class) {
    return thread_set_qos_class_self_c(qos_class);
}
uintptr_t std_thread_thread_dummy_entry_ptr_c(void) { return thread_dummy_entry_ptr_c(); }
#endif /* XLANG_RUNTIME_THREAD_GLUE_FROM_X */

/* ========== Worker thread pool (global state in rest C) ========== */

#define XLANG_THREAD_POOL_CAP 128
#define XLANG_THREAD_POOL_MAX_WORKERS 8

typedef struct {
    void *(*entry)(void *);
    void *arg;
} xlang_pool_job_t;

#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
/* PLATFORM: SHARED Cap (Linux futex / Darwin pthread / Windows Win32 sync_cap) — Cap mutex/cond + Cap spawn workers. */
static struct xlang_cap_mutex g_pool_mu;
static struct xlang_cap_cond g_pool_not_empty;
static struct xlang_cap_cond g_pool_idle;
static xlang_pool_job_t g_pool_q[XLANG_THREAD_POOL_CAP];
static int g_pool_head;
static int g_pool_tail;
static int g_pool_count;
static int g_pool_workers;
static int g_pool_started;
static int g_pool_stop_req;
static int g_pool_in_flight;
static struct xlang_thread_join g_pool_joins[XLANG_THREAD_POOL_MAX_WORKERS];

/** Worker main loop: dequeue jobs; stop flag exits. PLATFORM: SHARED Cap. */
static void *xlang_thread_pool_worker(void *arg) {
    (void)arg;
    for (;;) {
        xlang_pool_job_t job;
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        while (g_pool_count == 0 && !g_pool_stop_req) {
            (void)xlang_cap_cond_wait(&g_pool_not_empty, &g_pool_mu);
        }
        if (g_pool_stop_req && g_pool_count == 0) {
            (void)xlang_cap_mutex_unlock(&g_pool_mu);
            break;
        }
        job = g_pool_q[g_pool_head];
        g_pool_head = (g_pool_head + 1) % XLANG_THREAD_POOL_CAP;
        g_pool_count--;
        g_pool_in_flight++;
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        if (job.entry) {
            (void)job.entry(job.arg);
        }
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        g_pool_in_flight--;
        if (g_pool_count == 0 && g_pool_in_flight == 0) {
            (void)xlang_cap_cond_broadcast(&g_pool_idle);
        }
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
    }
    return NULL;
}
#else
static pthread_mutex_t g_pool_mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_pool_not_empty = PTHREAD_COND_INITIALIZER;
static pthread_cond_t g_pool_idle = PTHREAD_COND_INITIALIZER;
static xlang_pool_job_t g_pool_q[XLANG_THREAD_POOL_CAP];
static int g_pool_head;
static int g_pool_tail;
static int g_pool_count;
static int g_pool_workers;
static int g_pool_started;
static int g_pool_stop_req;
static int g_pool_in_flight;
static pthread_t g_pool_tids[XLANG_THREAD_POOL_MAX_WORKERS];

/* worker main loop: dequeue jobs, stop flag exits. */
static void *xlang_thread_pool_worker(void *arg) {
    (void)arg;
    for (;;) {
        xlang_pool_job_t job;
        pthread_mutex_lock(&g_pool_mu);
        while (g_pool_count == 0 && !g_pool_stop_req) {
            pthread_cond_wait(&g_pool_not_empty, &g_pool_mu);
        }
        if (g_pool_stop_req && g_pool_count == 0) {
            pthread_mutex_unlock(&g_pool_mu);
            break;
        }
        job = g_pool_q[g_pool_head];
        g_pool_head = (g_pool_head + 1) % XLANG_THREAD_POOL_CAP;
        g_pool_count--;
        g_pool_in_flight++;
        pthread_mutex_unlock(&g_pool_mu);
        if (job.entry) {
            (void)job.entry(job.arg);
        }
        pthread_mutex_lock(&g_pool_mu);
        g_pool_in_flight--;
        if (g_pool_count == 0 && g_pool_in_flight == 0) {
            pthread_cond_broadcast(&g_pool_idle);
        }
        pthread_mutex_unlock(&g_pool_mu);
    }
    return NULL;
}
#endif /* Cap vs POSIX fallback pool */

/* _impl: thread_pool_start */
int32_t thread_pool_start_impl(int32_t workers) {
#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    {
        static int g_pool_init_once = 0;
        int i;
        if (workers < 1 || workers > XLANG_THREAD_POOL_MAX_WORKERS) {
            return -1;
        }
        if (!g_pool_init_once) {
            (void)xlang_cap_mutex_init(&g_pool_mu);
            (void)xlang_cap_cond_init(&g_pool_not_empty);
            (void)xlang_cap_cond_init(&g_pool_idle);
            g_pool_init_once = 1;
        }
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        if (g_pool_started) {
            (void)xlang_cap_mutex_unlock(&g_pool_mu);
            return 0;
        }
        g_pool_head = 0;
        g_pool_tail = 0;
        g_pool_count = 0;
        g_pool_in_flight = 0;
        g_pool_stop_req = 0;
        g_pool_workers = workers;
        for (i = 0; i < workers; i++) {
            memset(&g_pool_joins[i], 0, sizeof(g_pool_joins[i]));
            if (xlang_thread_spawn(xlang_thread_pool_worker, NULL, &g_pool_joins[i],
                                   XLANG_THREAD_CAP_DEFAULT_STACK) != 0) {
                int j;
                g_pool_stop_req = 1;
                (void)xlang_cap_cond_broadcast(&g_pool_not_empty);
                (void)xlang_cap_mutex_unlock(&g_pool_mu);
                for (j = 0; j < i; j++) {
                    (void)xlang_thread_join(&g_pool_joins[j]);
                }
                (void)xlang_cap_mutex_lock(&g_pool_mu);
                g_pool_workers = 0;
                (void)xlang_cap_mutex_unlock(&g_pool_mu);
                return -1;
            }
        }
        g_pool_started = 1;
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        return 0;
    }
#else
    int i;
    if (workers < 1 || workers > XLANG_THREAD_POOL_MAX_WORKERS) {
        return -1;
    }
    pthread_mutex_lock(&g_pool_mu);
    if (g_pool_started) {
        pthread_mutex_unlock(&g_pool_mu);
        return 0;
    }
    g_pool_head = 0;
    g_pool_tail = 0;
    g_pool_count = 0;
    g_pool_in_flight = 0;
    g_pool_stop_req = 0;
    g_pool_workers = workers;
    for (i = 0; i < workers; i++) {
        if (pthread_create(&g_pool_tids[i], NULL, xlang_thread_pool_worker, NULL) != 0) {
            g_pool_stop_req = 1;
            pthread_cond_broadcast(&g_pool_not_empty);
            while (--i >= 0) {
                pthread_join(g_pool_tids[i], NULL);
            }
            g_pool_workers = 0;
            pthread_mutex_unlock(&g_pool_mu);
            return -1;
        }
    }
    g_pool_started = 1;
    pthread_mutex_unlock(&g_pool_mu);
    return 0;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_pool_start_c(int32_t workers) { return thread_pool_start_impl(workers); }
#endif

/* _impl: thread_pool_submit */
int32_t thread_pool_submit_impl(uintptr_t entry, uintptr_t arg) {
#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    {
        xlang_pool_job_t job;
        if (!g_pool_started || entry == 0) {
            return -1;
        }
        job.entry = (void *(*)(void *))entry;
        job.arg = (void *)arg;
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        while (g_pool_count >= XLANG_THREAD_POOL_CAP && !g_pool_stop_req) {
            (void)xlang_cap_cond_wait(&g_pool_idle, &g_pool_mu);
        }
        if (g_pool_stop_req) {
            (void)xlang_cap_mutex_unlock(&g_pool_mu);
            return -1;
        }
        g_pool_q[g_pool_tail] = job;
        g_pool_tail = (g_pool_tail + 1) % XLANG_THREAD_POOL_CAP;
        g_pool_count++;
        (void)xlang_cap_cond_signal(&g_pool_not_empty);
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        return 0;
    }
#else
    xlang_pool_job_t job;
    if (!g_pool_started || entry == 0) {
        return -1;
    }
    job.entry = (void *(*)(void *))entry;
    job.arg = (void *)arg;
    pthread_mutex_lock(&g_pool_mu);
    while (g_pool_count >= XLANG_THREAD_POOL_CAP && !g_pool_stop_req) {
        pthread_cond_wait(&g_pool_idle, &g_pool_mu);
    }
    if (g_pool_stop_req) {
        pthread_mutex_unlock(&g_pool_mu);
        return -1;
    }
    g_pool_q[g_pool_tail] = job;
    g_pool_tail = (g_pool_tail + 1) % XLANG_THREAD_POOL_CAP;
    g_pool_count++;
    pthread_cond_signal(&g_pool_not_empty);
    pthread_mutex_unlock(&g_pool_mu);
    return 0;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_pool_submit_c(uintptr_t entry, uintptr_t arg) {
    return thread_pool_submit_impl(entry, arg);
}
#endif

/* _impl: thread_pool_drain */
int32_t thread_pool_drain_impl(void) {
#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    if (!g_pool_started) {
        return -1;
    }
    (void)xlang_cap_mutex_lock(&g_pool_mu);
    while (g_pool_count > 0 || g_pool_in_flight > 0) {
        (void)xlang_cap_cond_wait(&g_pool_idle, &g_pool_mu);
    }
    (void)xlang_cap_mutex_unlock(&g_pool_mu);
    return 0;
#else
    if (!g_pool_started) {
        return -1;
    }
    pthread_mutex_lock(&g_pool_mu);
    while (g_pool_count > 0 || g_pool_in_flight > 0) {
        pthread_cond_wait(&g_pool_idle, &g_pool_mu);
    }
    pthread_mutex_unlock(&g_pool_mu);
    return 0;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_pool_drain_c(void) { return thread_pool_drain_impl(); }
#endif

/* _impl: thread_pool_stop */
int32_t thread_pool_stop_impl(void) {
#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    {
        int i;
        if (!g_pool_started) {
            return 0;
        }
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        g_pool_stop_req = 1;
        (void)xlang_cap_cond_broadcast(&g_pool_not_empty);
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        for (i = 0; i < g_pool_workers; i++) {
            (void)xlang_thread_join(&g_pool_joins[i]);
        }
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        g_pool_started = 0;
        g_pool_workers = 0;
        g_pool_stop_req = 0;
        g_pool_head = 0;
        g_pool_tail = 0;
        g_pool_count = 0;
        g_pool_in_flight = 0;
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        return 0;
    }
#else
    int i;
    if (!g_pool_started) {
        return 0;
    }
    pthread_mutex_lock(&g_pool_mu);
    g_pool_stop_req = 1;
    pthread_cond_broadcast(&g_pool_not_empty);
    pthread_mutex_unlock(&g_pool_mu);
    for (i = 0; i < g_pool_workers; i++) {
        pthread_join(g_pool_tids[i], NULL);
    }
    pthread_mutex_lock(&g_pool_mu);
    g_pool_started = 0;
    g_pool_workers = 0;
    g_pool_stop_req = 0;
    g_pool_head = 0;
    g_pool_tail = 0;
    g_pool_count = 0;
    g_pool_in_flight = 0;
    pthread_mutex_unlock(&g_pool_mu);
    return 0;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_pool_stop_c(void) { return thread_pool_stop_impl(); }
#endif

/* _impl: thread_pool_pending */
int32_t thread_pool_pending_impl(void) {
#if defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    {
        int32_t n;
        if (!g_pool_started) {
            return -1;
        }
        (void)xlang_cap_mutex_lock(&g_pool_mu);
        n = g_pool_count + g_pool_in_flight;
        (void)xlang_cap_mutex_unlock(&g_pool_mu);
        return n;
    }
#else
    int32_t n;
    if (!g_pool_started) {
        return -1;
    }
    pthread_mutex_lock(&g_pool_mu);
    n = g_pool_count + g_pool_in_flight;
    pthread_mutex_unlock(&g_pool_mu);
    return n;
#endif
}
#ifndef XLANG_RUNTIME_THREAD_GLUE_FROM_X
int32_t thread_pool_pending_c(void) { return thread_pool_pending_impl(); }
#endif
