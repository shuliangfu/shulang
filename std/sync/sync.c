/**
 * std/sync/sync.c — 互斥锁与同步原语（对标 Zig Thread.Mutex、Rust std::sync::Mutex）
 *
 * 【文件职责】
 * 实现 std.sync 的 C 层：mutex_new、mutex_lock、mutex_try_lock、mutex_unlock、mutex_free。
 * POSIX 使用 pthread_mutex_t；Windows 使用 CRITICAL_SECTION。与 std.thread 配合用于多线程互斥。
 *
 * 【所属模块/组件】
 * 标准库 std.sync；与 std/sync/mod.su 同目录。用户 import std.sync 时链入 std/sync/sync.o；Unix 需 -lpthread。
 *
 * 【与其它文件的关系】
 * - 被依赖：用户 import std.sync 且 -o exe 时链入本 .o。
 * - 依赖：无项目内头文件；POSIX 依赖 pthread，Windows 依赖 kernel32。
 */

#include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

/** Windows：互斥体为 CRITICAL_SECTION*，堆分配以便返回不透明指针。 */
typedef CRITICAL_SECTION shu_mutex_impl_t;

void *sync_mutex_new_c(void) {
    shu_mutex_impl_t *m = (shu_mutex_impl_t *)malloc(sizeof(shu_mutex_impl_t));
    if (m == NULL) return NULL;
    InitializeCriticalSection(m);
    return (void *)m;
}

/** 加锁；阻塞直到获取。返回 0 成功，-1 失败（如 m 为 NULL）。 */
int32_t sync_mutex_lock_c(void *m) {
    if (m == NULL) return -1;
    EnterCriticalSection((CRITICAL_SECTION *)m);
    return 0;
}

/** 尝试加锁；不阻塞。返回 0 成功获取，非 0 未获取（忙或 m 为 NULL）。 */
int32_t sync_mutex_try_lock_c(void *m) {
    if (m == NULL) return -1;
    return TryEnterCriticalSection((CRITICAL_SECTION *)m) ? 0 : 1;
}

/** 解锁。返回 0 成功，-1 失败（如 m 为 NULL）。 */
int32_t sync_mutex_unlock_c(void *m) {
    if (m == NULL) return -1;
    LeaveCriticalSection((CRITICAL_SECTION *)m);
    return 0;
}

/** 销毁并释放互斥体；调用后 m 不可再使用。 */
void sync_mutex_free_c(void *m) {
    if (m == NULL) return;
    DeleteCriticalSection((CRITICAL_SECTION *)m);
    free(m);
}

#else
#include <pthread.h>

/** POSIX：互斥体为 pthread_mutex_t*，堆分配以便返回不透明指针。 */
typedef pthread_mutex_t shu_mutex_impl_t;

void *sync_mutex_new_c(void) {
    shu_mutex_impl_t *m = (shu_mutex_impl_t *)malloc(sizeof(shu_mutex_impl_t));
    if (m == NULL) return NULL;
    if (pthread_mutex_init(m, NULL) != 0) {
        free(m);
        return NULL;
    }
    return (void *)m;
}

/** 加锁；阻塞直到获取。返回 0 成功，-1 失败（如 m 为 NULL）。 */
int32_t sync_mutex_lock_c(void *m) {
    if (m == NULL) return -1;
    return (pthread_mutex_lock((pthread_mutex_t *)m) == 0) ? 0 : -1;
}

/** 尝试加锁；不阻塞。返回 0 成功获取，非 0 未获取（EBUSY 或 m 为 NULL）。 */
int32_t sync_mutex_try_lock_c(void *m) {
    if (m == NULL) return -1;
    int ret = pthread_mutex_trylock((pthread_mutex_t *)m);
    if (ret == 0) return 0;
    return 1; /* EBUSY 或其它 */
}

/** 解锁。返回 0 成功，-1 失败。 */
int32_t sync_mutex_unlock_c(void *m) {
    if (m == NULL) return -1;
    return (pthread_mutex_unlock((pthread_mutex_t *)m) == 0) ? 0 : -1;
}

/** 销毁并释放互斥体；调用后 m 不可再使用。 */
void sync_mutex_free_c(void *m) {
    if (m == NULL) return;
    pthread_mutex_destroy((pthread_mutex_t *)m);
    free(m);
}
#endif
