/* seeds/runtime_env_os.from_x.c — G-02f-19 product TU
 * G-02f-123 true .x pure helpers.
 * G-02f-103 helper gates.
 * Product: runtime_env_os.o; R2 full mode: .x provides public API (thin),
 * this file provides OS bridge _impl functions (rest).
 *
 * wave252 G.7: POSIX getenv residual via public face link_abi_getenv (not raw getenv).
 * wave253: face body in runtime_link_abi_user_env.o (declaration only here).
 * Windows path keeps GetEnvironmentVariableA (PLATFORM: WINDOWS).
 * PLATFORM: SHARED face name / POSIX host residual via face; never g05 host bag.
 */
/**
 * runtime_env_os.c — 环境变量 OS 胶层（F-ZC：自 std/env/env_os_glue.c 迁入）
 *
 * getenv/setenv/unsetenv/temp_dir/env_iter；env.x 经 extern 调用；与 env.o 一并链入。
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/* wave253: declaration only — face body in runtime_link_abi_user_env.o (weak; panic C strong wins). */
#include <xlang_user_link_abi_getenv.h>
/* Cap residual 9.1.1: POSIX setenv/unsetenv via environ mutate (no libc). */
#include <xlang_environ_cap.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#if defined(_MSC_VER)
#define ENV_TLS __declspec(thread)
#else
#define ENV_TLS __thread
#endif
#else
#define ENV_TLS __thread
#endif

#if defined(__GNUC__) || defined(__clang__)
#define ENV_HOT        __attribute__((hot))
#define ENV_COLD       __attribute__((cold))
#define ENV_LIKELY(x)   __builtin_expect(!!(x), 1)
#define ENV_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define ENV_HOT
#define ENV_COLD
#define ENV_LIKELY(x)   (x)
#define ENV_UNLIKELY(x) (x)
#endif

/** 环境变量名最大长度（POSIX 通常 ≤255），key 超过此长度直接拒绝。 */
#define ENV_KEY_MAX 256

/**
 * 热路径共用：校验 key 并写入 key_buf（含 NUL）。
 * 参数：key/key_len 输入；key_buf 至少 key_len+1 字节。
 * 返回值：0 成功，-1 非法。
 */
/* thin+rest 切割：thin 部分（env_build_key）由 .x 提供,
 * rest 模式下跳过编译避免重复定义; rest 部分（env_getenv/setenv/unsetenv/temp_dir/iter 9 函数）始终编译.
 * 宏边界：XLANG_RUNTIME_ENV_OS_FROM_X
 * rest 跨调用依赖：env_getenv_c/env_getenv_ptr_c/env_getenv_exists_c 调用 env_build_key（thin 提供） */
#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
/* G-02f-123：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int env_build_key(const uint8_t * restrict key, int32_t key_len, char * restrict key_buf) {
    if (key == NULL || key_len <= 0 || key_len >= ENV_KEY_MAX) return -1;
    memcpy(key_buf, key, (size_t)key_len);
    key_buf[key_len] = '\0';
    return 0;
}
#else
/* rest 模式：thin 函数由 .x 提供，extern 声明供 rest 部分调用 */
extern int env_build_key(const uint8_t *key, int32_t key_len, char *key_buf);
#endif /* XLANG_RUNTIME_ENV_OS_FROM_X */



/**
 * getenv：key[0..key_len) 拷贝到栈上并加 NUL，调用系统 getenv；结果写入 out。
 * 返回值：写入字节数（不含 NUL），不存在或错误 -1。
 */
ENV_HOT
int32_t env_getenv_c_impl(const uint8_t * restrict key, int32_t key_len, uint8_t * restrict out, int32_t out_cap) {
    if (out == NULL || out_cap <= 0) return -1;

#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return -1;

#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD need = GetEnvironmentVariableA(key_buf, (char *)out, (DWORD)out_cap);
        if (need == 0) {
            /* 【Why 根源】GetEnvironmentVariableA 对空 value 也返回 0，须用 GetLastError 区分
             * 空值（ERROR_SUCCESS，变量存在但 value 为 ""）与不存在（ERROR_ENVVAR_NOT_FOUND）。
             * POSIX getenv 对空 value 返回非 NULL 指针，此处对齐语义返回 0（写入长度 0）。
             * 【Invariant】out[0] 已 NUL 终止（GetEnvironmentVariableA 失败时不写 out）。 */
            DWORD err = GetLastError();
            if (err == ERROR_SUCCESS) {
                out[0] = '\0';
                return 0;
            }
            return -1;
        }
        if (need > (DWORD)out_cap) return (int32_t)need;
        return (int32_t)need;
    }
#else
    {
        /* wave252 G.7: env via public face link_abi_getenv (not raw libc getenv). */
        const char *v = link_abi_getenv(key_buf);
        if (ENV_UNLIKELY(v == NULL)) return -1;
        size_t len = strlen(v);
        if (ENV_LIKELY(len < (size_t)out_cap)) {
            memcpy(out, v, len + 1);
            return (int32_t)len;
        }
        memcpy(out, v, (size_t)out_cap - 1);
        out[out_cap - 1] = '\0';
        return (int32_t)len;
    }
#endif
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_HOT
int32_t env_getenv_c(const uint8_t * restrict key, int32_t key_len, uint8_t * restrict out, int32_t out_cap) {
    return env_getenv_c_impl(key, key_len, out, out_cap);
}
#endif

/**
 * 零拷贝 getenv：返回 value 只读指针（NUL 结尾），不存在 NULL。
 * 参数：out_len 可选写入长度（不含 NUL）。
 */
ENV_HOT
uint8_t *env_getenv_ptr_c_impl(const uint8_t * restrict key, int32_t key_len, int32_t *out_len) {
#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return NULL;

    /* wave252 G.7: env via public face link_abi_getenv (not raw libc getenv). */
    const char *v = link_abi_getenv(key_buf);
    if (v == NULL) return NULL;
    if (out_len) *out_len = (int32_t)strlen(v);
    return (uint8_t *)v;
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_HOT
uint8_t *env_getenv_ptr_c(const uint8_t * restrict key, int32_t key_len, int32_t *out_len) {
    return env_getenv_ptr_c_impl(key, key_len, out_len);
}
#endif

/**
 * 零拷贝 getenv（key 须 NUL 结尾）：直接 face 查找，无 key 拷贝。
 */
ENV_HOT
uint8_t *env_getenv_z_c_impl(const uint8_t *key_z, int32_t *out_len) {
    if (key_z == NULL) return NULL;
    /* wave252 G.7: env via public face link_abi_getenv (not raw libc getenv). */
    const char *v = link_abi_getenv((const char *)key_z);
    if (v == NULL) return NULL;
    if (out_len) *out_len = (int32_t)strlen(v);
    return (uint8_t *)v;
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_HOT
uint8_t *env_getenv_z_c(const uint8_t *key_z, int32_t *out_len) {
    return env_getenv_z_c_impl(key_z, out_len);
}
#endif

/**
 * 判断环境变量是否存在；存在 1，不存在 0。
 */
ENV_HOT
int32_t env_getenv_exists_c_impl(const uint8_t * restrict key, int32_t key_len) {
#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return 0;

#if defined(_WIN32) || defined(_WIN64)
    return GetEnvironmentVariableA(key_buf, NULL, 0) != 0 ? 1 : 0;
#else
    /* wave252 G.7: env via public face link_abi_getenv (not raw libc getenv). */
    return link_abi_getenv(key_buf) != NULL ? 1 : 0;
#endif
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_HOT
int32_t env_getenv_exists_c(const uint8_t * restrict key, int32_t key_len) {
    return env_getenv_exists_c_impl(key, key_len);
}
#endif

/**
 * Set environment variable name=value (NUL-terminated); overwrite != 0 replaces.
 * Cap residual 9.1.1: unified xlang_environ_setenv (POSIX walk / Win32 dual block).
 * @return 0 success, -1 failure.
 * PLATFORM: SHARED Cap (9.1.1).
 */
ENV_COLD
int32_t env_setenv_c_impl(const uint8_t *name, const uint8_t *value, int32_t overwrite) {
    if (name == NULL) return -1;
    return xlang_environ_setenv((const char *)name, value ? (const char *)value : "",
                                overwrite ? 1 : 0);
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_COLD
int32_t env_setenv_c(const uint8_t *name, const uint8_t *value, int32_t overwrite) {
    return env_setenv_c_impl(name, value, overwrite);
}
#endif

/**
 * Delete environment variable name (NUL-terminated).
 * Cap residual 9.1.1: unified xlang_environ_unsetenv (POSIX walk / Win32 dual block).
 * @return 0 success, -1 failure.
 * PLATFORM: SHARED Cap (9.1.1).
 */
ENV_COLD
int32_t env_unsetenv_c_impl(const uint8_t *name) {
    if (name == NULL) return -1;
    return xlang_environ_unsetenv((const char *)name);
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_COLD
int32_t env_unsetenv_c(const uint8_t *name) {
    return env_unsetenv_c_impl(name);
}
#endif

/**
 * 临时目录路径写入 out（NUL 结尾）；POSIX TMPDIR/TEMP/TMP → /tmp；Windows GetTempPath。
 * 返回值：写入字节数（不含 NUL），失败 -1。
 */
int32_t env_temp_dir_c_impl(uint8_t *out, int32_t out_cap) {
    if (out == NULL || out_cap <= 0) return -1;

#if defined(_WIN32) || defined(_WIN64)
    {
#define WIN_TEMP_CACHE_SIZE (MAX_PATH + 1)
        static ENV_TLS char cached[WIN_TEMP_CACHE_SIZE];
        static ENV_TLS DWORD cached_len = 0;
        static ENV_TLS int cached_valid = 0;

        if (cached_valid && cached_len < (DWORD)out_cap) {
            memcpy(out, cached, cached_len + 1);
            return (int32_t)cached_len;
        }
        cached_valid = 0;

        char buf[MAX_PATH + 1];
        DWORD n = GetTempPathA((DWORD)sizeof(buf), buf);
        if (n == 0 || n >= (DWORD)sizeof(buf)) return -1;
        if (n > (DWORD)out_cap) return -1;
        memcpy(out, buf, n + 1);
        if (n < (DWORD)sizeof(cached)) {
            memcpy(cached, buf, n + 1);
            cached_len = n;
            cached_valid = 1;
        }
        return (int32_t)n;
#undef WIN_TEMP_CACHE_SIZE
    }
#else
    {
        static const char fallback[] = "/tmp";
#define TEMP_DIR_CACHE_SIZE 256
        static ENV_TLS char cached[TEMP_DIR_CACHE_SIZE];
        static ENV_TLS size_t cached_len = 0;
        static ENV_TLS int cached_valid = 0;

        if (cached_valid && cached_len < (size_t)out_cap) {
            memcpy(out, cached, cached_len + 1);
            return (int32_t)cached_len;
        }
        cached_valid = 0;

        /* wave252 G.7: env via public face link_abi_getenv (not raw libc getenv). */
        const char *p = NULL;
        const char *tmd = link_abi_getenv("TMPDIR");
        if (tmd && tmd[0]) p = tmd;
        if (!p) { tmd = link_abi_getenv("TEMP"); if (tmd && tmd[0]) p = tmd; }
        if (!p) { tmd = link_abi_getenv("TMP"); if (tmd && tmd[0]) p = tmd; }
        if (!p) p = fallback;
        size_t len = strlen(p);
        if (len >= (size_t)out_cap) return -1;
        memcpy(out, p, len + 1);
        if (len < TEMP_DIR_CACHE_SIZE) {
            memcpy(cached, p, len + 1);
            cached_len = len;
            cached_valid = 1;
        }
        return (int32_t)len;
#undef TEMP_DIR_CACHE_SIZE
    }
#endif
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
int32_t env_temp_dir_c(uint8_t *out, int32_t out_cap) {
    return env_temp_dir_c_impl(out, out_cap);
}
#endif

#if !defined(_WIN32) && !defined(_WIN64)
extern char **environ;
#endif

/**
 * 统计当前进程环境变量条目数。
 * 返回值：条目数；失败 0。
 */
ENV_COLD
int32_t env_iter_count_c_impl(void) {
#if defined(_WIN32) || defined(_WIN64)
    {
        char *block = GetEnvironmentStringsA();
        int32_t n = 0;
        if (block == NULL) return 0;
        for (const char *p = block; *p; ) {
            if (*p != '=') n++;
            while (*p) p++;
            p++;
        }
        FreeEnvironmentStringsA(block);
        return n;
    }
#else
    {
        int32_t n = 0;
        if (environ == NULL) return 0;
        while (environ[n] != NULL) n++;
        return n;
    }
#endif
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_COLD
int32_t env_iter_count_c(void) {
    return env_iter_count_c_impl();
}
#endif

/**
 * 将 environ[index] 拆为 key/value 写入 out 缓冲。
 * 返回值：成功 1，越界 0，错误 -1。
 */
ENV_COLD
int32_t env_iter_at_c_impl(int32_t index, uint8_t *key_out, int32_t key_cap,
                      uint8_t *val_out, int32_t val_cap) {
    const char *entry = NULL;
    const char *eq;
    int32_t key_len;
    int32_t val_len;
    if (index < 0 || key_out == NULL || val_out == NULL || key_cap <= 0 || val_cap <= 0)
        return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        char *block = GetEnvironmentStringsA();
        int32_t cur = 0;
        if (block == NULL) return -1;
        for (const char *p = block; *p; ) {
            if (*p != '=') {
                if (cur == index) {
                    entry = p;
                    break;
                }
                cur++;
            }
            while (*p) p++;
            p++;
        }
        if (entry == NULL) {
            FreeEnvironmentStringsA(block);
            return 0;
        }
        eq = strchr(entry, '=');
        if (eq == NULL) {
            FreeEnvironmentStringsA(block);
            return -1;
        }
        key_len = (int32_t)(eq - entry);
        val_len = (int32_t)strlen(eq + 1);
        if (key_len + 1 > key_cap || val_len + 1 > val_cap) {
            FreeEnvironmentStringsA(block);
            return -1;
        }
        memcpy(key_out, entry, (size_t)key_len);
        key_out[key_len] = '\0';
        memcpy(val_out, eq + 1, (size_t)val_len);
        val_out[val_len] = '\0';
        FreeEnvironmentStringsA(block);
        return 1;
    }
#else
    {
        if (environ == NULL) return 0;
        entry = environ[index];
        if (entry == NULL) return 0;
        eq = strchr(entry, '=');
        if (eq == NULL) return -1;
        key_len = (int32_t)(eq - entry);
        val_len = (int32_t)strlen(eq + 1);
        if (key_len + 1 > key_cap || val_len + 1 > val_cap) return -1;
        memcpy(key_out, entry, (size_t)key_len);
        key_out[key_len] = '\0';
        memcpy(val_out, eq + 1, (size_t)val_len);
        val_out[val_len] = '\0';
        return 1;
    }
#endif
}

#ifndef XLANG_RUNTIME_ENV_OS_FROM_X
ENV_COLD
int32_t env_iter_at_c(int32_t index, uint8_t *key_out, int32_t key_cap,
                      uint8_t *val_out, int32_t val_cap) {
    return env_iter_at_c_impl(index, key_out, key_cap, val_out, val_cap);
}
#endif