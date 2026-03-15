/**
 * std/random/random.c — 密码学安全随机数（CSPRNG）
 *
 * 【文件职责】
 * 实现 std.random 模块的 C 层：fill_bytes（getentropy/getrandom/BCryptGenRandom）、
 * u32/u64 由内部 fill 4/8 字节后按平台字节序解释。仅提供 CSPRNG，不引入 PRNG 引擎。
 *
 * 【所属模块/组件】
 * 标准库 std.random；与 std/random/mod.su 同目录，mod.su 为对外 API。
 *
 * 【与其它文件的关系】
 * - 被依赖：用户 import std.random 且 -o exe 时，编译器将本文件产出的 random.o 链入可执行文件。
 * - 依赖：无项目内头文件；依赖系统 C 库或 Windows BCrypt。
 *
 * 【性能】
 * - fill_bytes：一次或多次系统调用填满 buf，避免逐字节；大块吞吐目标 ≥ Zig/Rust OsRng/getentropy。
 * - Windows：算法句柄进程内缓存，仅首次调用打开，后续仅 BCryptGenRandom，显著降低 u32/u64/fill_bytes 延迟。
 * - u32/u64：单次 fill 4/8 字节，延迟可接受。
 */

#include <stdint.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <bcrypt.h>
#include <synchapi.h>
#pragma comment(lib, "bcrypt.lib")
#elif defined(__linux__)
#include <sys/random.h>
#include <errno.h>
#else
/* macOS、*BSD：getentropy；单次最多 256 字节，需循环。macOS 上声明在 <sys/random.h>。 */
#if defined(__APPLE__)
#include <sys/random.h>
#else
#include <unistd.h>
#endif
#include <errno.h>
#ifndef GETENTROPY_MAX
#define GETENTROPY_MAX 256
#endif
#endif

#if defined(_WIN32) || defined(_WIN64)
/** Windows：进程内缓存的 RNG 算法句柄，仅首次使用时打开，避免每次 fill_bytes/u32/u64 都 Open/Close。 */
static INIT_ONCE g_random_init_once = INIT_ONCE_STATIC_INIT;
static BCRYPT_ALG_HANDLE g_random_alg = NULL;

static BOOL CALLBACK random_init_callback(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *Context) {
    (void)InitOnce;
    (void)Parameter;
    BCRYPT_ALG_HANDLE alg = NULL;
    NTSTATUS st = BCryptOpenAlgorithmProvider(&alg, BCRYPT_RNG_ALGORITHM, NULL, 0);
    if (st != 0 || !alg) return FALSE;
    *(BCRYPT_ALG_HANDLE *)Context = alg;
    return TRUE;
}

/** 取得缓存的 BCrypt RNG 句柄；失败返回 NULL。 */
static BCRYPT_ALG_HANDLE random_get_alg(void) {
    if (!InitOnceExecuteOnce(&g_random_init_once, random_init_callback, NULL, (PVOID *)&g_random_alg))
        return NULL;
    return g_random_alg;
}
#endif

/** 向 buf 写入 len 字节密码学安全随机数。返回写入的字节数（成功时为 len），失败时返回负的错误码（如 -1）。一次/多次系统调用填满，避免逐字节。 */
int32_t random_fill_bytes_c(uint8_t *buf, int32_t len) {
    if (!buf || len < 0) return -1;
    if (len == 0) return 0;

#if defined(_WIN32) || defined(_WIN64)
    {
        BCRYPT_ALG_HANDLE alg = random_get_alg();
        if (!alg) return -1;
        return (BCryptGenRandom(alg, buf, (ULONG)(size_t)len, 0) == 0) ? len : -1;
    }
#elif defined(__linux__)
    {
        size_t done = 0;
        size_t want = (size_t)len;
        while (done < want) {
            ssize_t n = getrandom(buf + done, want - done, 0);
            if (n < 0) {
                if (errno == EINTR) continue;
                return (int32_t)(done > 0 ? (int32_t)done : -1);
            }
            done += (size_t)n;
        }
        return len;
    }
#else
    /* macOS / *BSD: getentropy 单次最多 GETENTROPY_MAX（通常 256） */
    {
        size_t done = 0;
        size_t total = (size_t)len;
        while (done < total) {
            size_t chunk = total - done;
            if (chunk > (size_t)GETENTROPY_MAX) chunk = (size_t)GETENTROPY_MAX;
            if (getentropy(buf + done, chunk) != 0)
                return (int32_t)(done > 0 ? (int32_t)done : -1);
            done += chunk;
        }
        return len;
    }
#endif
}

/** 生成一个密码学安全的随机 u32；内部 fill 4 字节后按本机字节序解释。 */
uint32_t random_u32_c(void) {
    uint8_t buf[4];
    if (random_fill_bytes_c(buf, 4) != 4) return 0;
    uint32_t u;
    memcpy(&u, buf, 4);
    return u;
}

/** 生成一个密码学安全的随机 u64；内部 fill 8 字节后按本机字节序解释。 */
uint64_t random_u64_c(void) {
    uint8_t buf[8];
    if (random_fill_bytes_c(buf, 8) != 8) return 0;
    uint64_t u;
    memcpy(&u, buf, 8);
    return u;
}
