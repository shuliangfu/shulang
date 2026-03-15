/**
 * std/thread/thread.c — 线程：pthread 封装，供 std.thread 多核易用
 *
 * 职责：提供 thread_self_c、thread_create_c、thread_create_with_stack_c、thread_join_c、thread_set_affinity_self_c、thread_set_affinity_c、thread_set_qos_class_self_c；与 std/thread/mod.su 同目录。
 * 约定：entry 为 C 函数指针 void* (*)(void*)，arg 传入该函数；返回的 thread_id 为 pthread_t（或 Windows 句柄）。
 * 链接：用户程序 import std.thread 时链入本目录产出的 thread.o；Unix 需 -lpthread，Windows 需 kernel32。
 */

#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#define _GNU_SOURCE
#include <sched.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <stdlib.h>
/* Windows：用 CreateThread + WaitForSingleObject；thread_id 存 HANDLE。 */
typedef HANDLE shu_thread_t;
#define SHU_THREAD_ID_INVALID ((int64_t)(uintptr_t)NULL)
#else
#include <pthread.h>
typedef pthread_t shu_thread_t;
#define SHU_THREAD_ID_INVALID ((int64_t)0)
#if defined(__APPLE__)
#include <sys/qos.h>
#endif
#endif

/** 当前线程 ID；用于区分线程、多核压榨时每线程一 io_uring。POSIX 为 pthread_self() 的数值表示，Windows 为 GetCurrentThreadId()。 */
int64_t thread_self_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    return (int64_t)(intptr_t)GetCurrentThreadId();
#else
    return (int64_t)(uintptr_t)pthread_self();
#endif
}

#if defined(_WIN32) || defined(_WIN64)
struct shu_thread_params { void *(*entry)(void *); void *arg; };
static DWORD WINAPI thread_wrap(LPVOID arg) {
    struct shu_thread_params *p = (struct shu_thread_params *)arg;
    void *(*entry)(void *) = p->entry;
    void *a = p->arg;
    free(p);
    return (DWORD)(uintptr_t)entry(a);
}
#endif

/**
 * 创建新线程；entry 为 C 函数 void* (*)(void*)，arg 传入；成功返回 thread_id（用于 join），失败返回 SHU_THREAD_ID_INVALID（约定为 0 或 -1）。
 * 调用方保证 entry 非 NULL。
 */
int64_t thread_create_c(void *entry, void *arg) {
    if (entry == NULL) return SHU_THREAD_ID_INVALID;
#if defined(_WIN32) || defined(_WIN64)
    {
        struct shu_thread_params *params = (struct shu_thread_params *)malloc(sizeof(struct shu_thread_params));
        if (!params) return SHU_THREAD_ID_INVALID;
        params->entry = (void *(*)(void *))entry;
        params->arg = arg;
        HANDLE h = CreateThread(NULL, 0, thread_wrap, params, 0, NULL);
        if (h == NULL) { free(params); return SHU_THREAD_ID_INVALID; }
        return (int64_t)(uintptr_t)h;
    }
#else
    {
        pthread_t tid;
        if (pthread_create(&tid, NULL, (void *(*)(void *))entry, arg) != 0)
            return SHU_THREAD_ID_INVALID;
        return (int64_t)(uintptr_t)tid;
    }
#endif
}

/**
 * 创建新线程并指定栈大小；stack_size 为 0 表示使用默认栈大小。
 * 多 worker 时可用较小栈（如 262144）省内存。成功返回 thread_id，失败返回 SHU_THREAD_ID_INVALID。
 */
int64_t thread_create_with_stack_c(void *entry, void *arg, size_t stack_size) {
    if (entry == NULL) return SHU_THREAD_ID_INVALID;
#if defined(_WIN32) || defined(_WIN64)
    {
        struct shu_thread_params *params = (struct shu_thread_params *)malloc(sizeof(struct shu_thread_params));
        if (!params) return SHU_THREAD_ID_INVALID;
        params->entry = (void *(*)(void *))entry;
        params->arg = arg;
        HANDLE h = CreateThread(NULL, (SIZE_T)stack_size, thread_wrap, params, 0, NULL);
        if (h == NULL) { free(params); return SHU_THREAD_ID_INVALID; }
        return (int64_t)(uintptr_t)h;
    }
#else
    {
        pthread_t tid;
        if (stack_size == 0) {
            if (pthread_create(&tid, NULL, (void *(*)(void *))entry, arg) != 0)
                return SHU_THREAD_ID_INVALID;
            return (int64_t)(uintptr_t)tid;
        }
        pthread_attr_t attr;
        if (pthread_attr_init(&attr) != 0) return SHU_THREAD_ID_INVALID;
        if (pthread_attr_setstacksize(&attr, stack_size) != 0) {
            pthread_attr_destroy(&attr);
            return SHU_THREAD_ID_INVALID;
        }
        int ret = pthread_create(&tid, &attr, (void *(*)(void *))entry, arg);
        pthread_attr_destroy(&attr);
        if (ret != 0) return SHU_THREAD_ID_INVALID;
        return (int64_t)(uintptr_t)tid;
    }
#endif
}

/** 等待线程结束；thread_id 为 thread_create_c 返回值。返回 0 成功，-1 失败（如已 join 或无效 id）。 */
int32_t thread_join_c(int64_t thread_id) {
    if (thread_id == SHU_THREAD_ID_INVALID) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        HANDLE h = (HANDLE)(uintptr_t)thread_id;
        if (WaitForSingleObject(h, INFINITE) != WAIT_OBJECT_0) return -1;
        CloseHandle(h);
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

/**
 * 将当前线程绑定到指定 CPU（绑核）；多 worker 时减少迁移与缓存抖动。
 * cpu_index：逻辑 CPU 编号（从 0 开始）。成功返回 0，失败返回 -1。
 * Linux：pthread_setaffinity_np(self, ...)；Windows：SetThreadAffinityMask(GetCurrentThread(), 1<<cpu_index)；macOS/BSD 暂返回 -1。
 */
int32_t thread_set_affinity_self_c(int32_t cpu_index) {
    if (cpu_index < 0) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD_PTR mask = (DWORD_PTR)(1ULL << (unsigned)cpu_index);
        if (SetThreadAffinityMask(GetCurrentThread(), mask) == 0) return -1;
        return 0;
    }
#elif defined(__linux__)
    {
        cpu_set_t set;
        CPU_ZERO(&set);
        CPU_SET((unsigned)cpu_index, &set);
        if (pthread_setaffinity_np(pthread_self(), sizeof(set), &set) != 0) return -1;
        return 0;
    }
#else
    (void)cpu_index;
    return -1; /* macOS/BSD 暂不实现 */
#endif
}

/**
 * 将指定线程绑定到指定 CPU；thread_id 为 thread_create_c 返回值。
 * 成功返回 0，失败返回 -1（如无效 thread_id 或平台不支持）。
 */
int32_t thread_set_affinity_c(int64_t thread_id, int32_t cpu_index) {
    if (thread_id == SHU_THREAD_ID_INVALID || cpu_index < 0) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD_PTR mask = (DWORD_PTR)(1ULL << (unsigned)cpu_index);
        if (SetThreadAffinityMask((HANDLE)(uintptr_t)thread_id, mask) == 0) return -1;
        return 0;
    }
#elif defined(__linux__)
    {
        cpu_set_t set;
        CPU_ZERO(&set);
        CPU_SET((unsigned)cpu_index, &set);
        if (pthread_setaffinity_np((pthread_t)(uintptr_t)thread_id, sizeof(set), &set) != 0) return -1;
        return 0;
    }
#else
    (void)thread_id;
    (void)cpu_index;
    return -1;
#endif
}

/**
 * 仅 macOS：设置当前线程的 QoS 等级，提升调度优先级（无法绑核时的替代）。
 * qos_class：0=default，1=user_interactive，2=user_initiated，3=utility，4=background。
 * worker 线程建议传 2（user_initiated）。成功返回 0，失败或非 macOS 返回 -1。
 */
int32_t thread_set_qos_class_self_c(int32_t qos_class) {
#if defined(__APPLE__)
    qos_class_t q = QOS_CLASS_DEFAULT;
    switch (qos_class) {
        case 0: q = QOS_CLASS_DEFAULT; break;
        case 1: q = QOS_CLASS_USER_INTERACTIVE; break;
        case 2: q = QOS_CLASS_USER_INITIATED; break;
        case 3: q = QOS_CLASS_UTILITY; break;
        case 4: q = QOS_CLASS_BACKGROUND; break;
        default: return -1;
    }
    if (pthread_set_qos_class_self_np(q, 0) != 0) return -1;
    return 0;
#else
    (void)qos_class;
    return -1;
#endif
}

/** 测试/示例用：供 thread_create_c 的 entry，直接返回 NULL。可用于验证 spawn+join 流程。 */
void *thread_dummy_entry(void *arg) {
    (void)arg;
    return NULL;
}

/** 返回 thread_dummy_entry 的地址（usize），便于 .su 侧无函数指针时仍可测试 thread_create_c(thread_dummy_entry_ptr_c(), 0)。 */
uintptr_t thread_dummy_entry_ptr_c(void) {
    return (uintptr_t)&thread_dummy_entry;
}
