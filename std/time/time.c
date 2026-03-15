/**
 * std/time/time.c — 时间与睡眠（单调时钟、墙钟、sleep）
 *
 * 【文件职责】
 * 实现 std.time 模块的 C 层：单调时间（now_monotonic_ns/us/ms/sec）、墙钟时间（now_wall_sec/ms/us/ns）、
 * 睡眠（sleep_ns/us/ms/sec）、时间差 duration_ns。全平台一套 API，内部条件编译（POSIX / Windows）。
 *
 * 【所属模块/组件】
 * 标准库 std.time；与 std/time/mod.su 同目录，mod.su 为对外 API，本文件为平台实现。
 *
 * 【与其它文件的关系】
 * - 被依赖：用户 import std.time 且 -o exe 时，编译器将本文件产出的 time.o 链入可执行文件。
 * - 依赖：无项目内头文件；依赖系统 C 库（time.h、sys/time.h、unistd.h 或 Windows API）。
 *
 * 【性能】
 * - 单调/墙钟：单次系统调用，无分配；Linux 用 clock_gettime(CLOCK_MONOTONIC/CLOCK_REALTIME)。
 * - Windows：QueryPerformanceCounter（单调）、GetSystemTimePreciseAsFileTime（墙钟，100ns 粒度）。
 */

#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
/* 墙钟：自 1601-01-01 100ns 单位的 FILETIME；Unix 纪元 1970-01-01 对应 11644473600 秒 = 116444736000000000 100ns */
#define UNIX_EPOCH_100NS 116444736000000000ULL
#else
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#endif

/** 单调时钟：纳秒（自任意起点，仅用于差值）。POSIX: clock_gettime(CLOCK_MONOTONIC)；Windows: QueryPerformanceCounter。单次 syscall，无分配。 */
int64_t time_now_monotonic_ns_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    static LARGE_INTEGER freq = { { 0 } };
    LARGE_INTEGER counter;
    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
        if (freq.QuadPart == 0) return 0;
    }
    QueryPerformanceCounter(&counter);
    return (int64_t)((counter.QuadPart * 1000000000) / freq.QuadPart);
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) return 0;
    return (int64_t)ts.tv_sec * 1000000000 + (int64_t)ts.tv_nsec;
#endif
}

/** 单调：微秒。一次 syscall（内部调 _ns 再除）。 */
int64_t time_now_monotonic_us_c(void) {
    return time_now_monotonic_ns_c() / 1000;
}

/** 单调：毫秒。 */
int64_t time_now_monotonic_ms_c(void) {
    return time_now_monotonic_ns_c() / 1000000;
}

/** 单调：秒。 */
int64_t time_now_monotonic_sec_c(void) {
    return time_now_monotonic_ns_c() / 1000000000;
}

/** 墙钟：纳秒。Windows 粒度为 100ns。唯一读墙钟的底层实现，sec/ms/us 由此派生以减重复代码与利于内联。 */
int64_t time_now_wall_ns_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    FILETIME ft;
    GetSystemTimePreciseAsFileTime(&ft);
    ULARGE_INTEGER u;
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    return (int64_t)((u.QuadPart - UNIX_EPOCH_100NS) * 100);
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0;
    return (int64_t)ts.tv_sec * 1000000000 + (int64_t)ts.tv_nsec;
#endif
}

/** 墙钟：秒。由 _ns 派生，一次 syscall。 */
int64_t time_now_wall_sec_c(void) {
    return time_now_wall_ns_c() / 1000000000;
}

/** 墙钟：毫秒。 */
int64_t time_now_wall_ms_c(void) {
    return time_now_wall_ns_c() / 1000000;
}

/** 墙钟：微秒。 */
int64_t time_now_wall_us_c(void) {
    return time_now_wall_ns_c() / 1000;
}

/** 睡眠：纳秒。可能提前唤醒（spurious wakeup），不保证精度。 */
void time_sleep_ns_c(int64_t ns) {
    if (ns <= 0) return;
#if defined(_WIN32) || defined(_WIN64)
    if (ns < 1000000) ns = 1000000;
    Sleep((DWORD)(ns / 1000000));
#else
    struct timespec req, rem;
    req.tv_sec = (time_t)(ns / 1000000000);
    req.tv_nsec = (long)(ns % 1000000000);
    while (nanosleep(&req, &rem) != 0) {
        req = rem;
    }
#endif
}

/** 睡眠：微秒。 */
void time_sleep_us_c(int64_t us) {
    time_sleep_ns_c(us * 1000);
}

/** 睡眠：毫秒。 */
void time_sleep_ms_c(int32_t ms) {
    if (ms <= 0) return;
    time_sleep_ns_c((int64_t)ms * 1000000);
}

/** 睡眠：秒。 */
void time_sleep_sec_c(int32_t s) {
    if (s <= 0) return;
    time_sleep_ns_c((int64_t)s * 1000000000);
}

/** 时间差（纳秒）：to_ns - from_ns。纯算术、无 syscall；链接时 -flto 可内联消除调用开销。 */
int64_t time_duration_ns_c(int64_t from_ns, int64_t to_ns) {
    return to_ns - from_ns;
}
