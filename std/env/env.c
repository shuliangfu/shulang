/**
 * std/env/env.c — 环境变量与临时目录（对齐 Zig/Rust std.env）
 *
 * 【文件职责】
 * 实现 std.env 模块的 C 层：getenv(key,key_len,out,cap)、getenv_exists(key,key_len)、
 * setenv、unsetenv、temp_dir。key 支持 (ptr,len) 无需 NUL，与 std.string/StrView 友好。
 *
 * 【所属模块/组件】
 * 标准库 std.env；与 std/env/mod.su 同目录。
 *
 * 【与其它文件的关系】
 * - 被依赖：用户 import std.env 且 -o exe 时链入 std/env/env.o。
 * - 依赖：无项目内头文件；依赖 C 库（stdlib、string）及 Windows API（GetTempPath）。
 *
 * 【性能】
 * getenv 热点路径：栈上 key 缓冲 256（POSIX 名长≤255）+ 一次 getenv + value 拷贝；无堆分配。
 * temp_dir（POSIX）线程局部缓存，重复调用仅 memcpy，无额外 getenv。详见 analysis/std_env性能分析与优化.md。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

/** 热路径共用：校验 key 并写入 key_buf（含 NUL）。key_buf 至少 key_len+1 字节。返回 0 成功，-1 非法。内联后无额外调用开销，仅减重复代码利于 I-cache。 */
static inline int env_build_key(const uint8_t * restrict key, int32_t key_len, char * restrict key_buf) {
    if (key == NULL || key_len <= 0 || key_len >= ENV_KEY_MAX) return -1;
    memcpy(key_buf, key, (size_t)key_len);
    key_buf[key_len] = '\0';
    return 0;
}

/** 将 key[0..key_len) 拷贝到栈上并加 NUL，然后调用系统 getenv；结果写入 out[0..out_cap)，保证 NUL 结尾。返回写入的字节数（不含 NUL），不存在或错误返回 -1。key 缓冲使用 VLA 按 key_len+1 分配，短 key 仅占少量栈。restrict 助编译器优化 memcpy。 */
ENV_HOT
int32_t env_getenv_c(const uint8_t * restrict key, int32_t key_len, uint8_t * restrict out, int32_t out_cap) {
    if (out == NULL || out_cap <= 0) return -1;

#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];  /* 按 key 长度分配，短 key 仅占少量栈 */
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return -1;

#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD need = GetEnvironmentVariableA(key_buf, (char *)out, (DWORD)out_cap);
        if (need == 0) return -1; /* 不存在或错误 */
        if (need > (DWORD)out_cap) return (int32_t)need; /* 缓冲区不足，返回所需长度 */
        return (int32_t)need;
    }
#else
    {
        const char *v = getenv(key_buf);
        if (ENV_UNLIKELY(v == NULL)) return -1;
        size_t len = strlen(v);
        if (ENV_LIKELY(len < (size_t)out_cap)) {
            memcpy(out, v, len + 1);
            return (int32_t)len;
        }
        memcpy(out, v, (size_t)out_cap - 1);
        out[out_cap - 1] = '\0';
        return (int32_t)len; /* 截断，返回真实长度 */
    }
#endif
}

/** 零拷贝：返回 key 对应 value 的只读指针（NUL 结尾），不存在返回 NULL。可选将长度（不含 NUL）写入 out_len。指针在 setenv/unsetenv 或下次 getenv_ptr/getenv_z 前有效，勿长期持有。key 仍拷贝一次以加 NUL。 */
ENV_HOT
uint8_t *env_getenv_ptr_c(const uint8_t * restrict key, int32_t key_len, int32_t *out_len) {
#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return NULL;

    /* Linux / macOS / Windows 均用 CRT getenv()，返回 value 指针，零拷贝三平台一致 */
    const char *v = getenv(key_buf);
    if (v == NULL) return NULL;
    if (out_len) *out_len = (int32_t)strlen(v);  /* 仅需长度时才 strlen，避免热路径多余扫描 */
    return (uint8_t *)v;
}

/** 零拷贝（key+value）：key_z 须 NUL 结尾，直接传 getenv，无 key 拷贝；返回 value 指针或 NULL。out_len 可选。指针语义同 env_getenv_ptr_c。仅需长度时才 strlen。 */
ENV_HOT
uint8_t *env_getenv_z_c(const uint8_t *key_z, int32_t *out_len) {
    if (key_z == NULL) return NULL;
    const char *v = getenv((const char *)key_z);
    if (v == NULL) return NULL;
    if (out_len) *out_len = (int32_t)strlen(v);
    return (uint8_t *)v;
}

/** 判断环境变量 key[0..key_len) 是否存在；存在返回 1，不存在返回 0。不拷贝 value，仅查存在性。key 缓冲使用 VLA 按 key_len+1 分配。 */
ENV_HOT
int32_t env_getenv_exists_c(const uint8_t * restrict key, int32_t key_len) {
#if defined(__STDC_NO_VLA__)
    char key_buf[ENV_KEY_MAX];
#else
    char key_buf[key_len + 1];
#endif
    if (env_build_key(key, key_len, key_buf) != 0) return 0;

#if defined(_WIN32) || defined(_WIN64)
    return GetEnvironmentVariableA(key_buf, NULL, 0) != 0 ? 1 : 0;
#else
    return getenv(key_buf) != NULL ? 1 : 0;
#endif
}

/** 设置环境变量 name=value（name、value 为 NUL 结尾）；overwrite 非 0 时覆盖。返回 0 成功，-1 失败。 */
ENV_COLD
int32_t env_setenv_c(const uint8_t *name, const uint8_t *value, int32_t overwrite) {
    if (name == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    (void)overwrite;
    {
        size_t nlen = strlen((const char *)name);
        size_t vlen = value ? strlen((const char *)value) : 0;
        if (nlen + vlen + 2 > 2048) return -1;
        char buf[2048];
        memcpy(buf, name, nlen);
        buf[nlen] = '=';
        if (value)
            memcpy(buf + nlen + 1, value, vlen + 1);
        else
            buf[nlen + 1] = '\0';
        return _putenv(buf) == 0 ? 0 : -1;
    }
#else
    return setenv((const char *)name, value ? (const char *)value : "", overwrite ? 1 : 0) == 0 ? 0 : -1;
#endif
}

/** 删除环境变量 name（NUL 结尾）。返回 0 成功，-1 失败。 */
ENV_COLD
int32_t env_unsetenv_c(const uint8_t *name) {
    if (name == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        char buf[512];
        size_t n = 0;
        while (n < sizeof(buf) - 2 && name[n]) { buf[n] = (char)name[n]; n++; }
        if (n >= sizeof(buf) - 2) return -1;
        buf[n++] = '=';
        buf[n] = '\0';
        return _putenv(buf) == 0 ? 0 : -1;
    }
#else
    return unsetenv((const char *)name) == 0 ? 0 : -1;
#endif
}

/** 将临时目录路径写入 out（NUL 结尾），最多 out_cap 字节。返回写入字节数（不含 NUL），失败 -1。POSIX: TMPDIR/TEMP/TMP → /tmp；Windows: GetTempPath。POSIX 下使用线程局部缓存，重复调用仅 memcpy。 */
int32_t env_temp_dir_c(uint8_t *out, int32_t out_cap) {
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

        const char *p = NULL;
        const char *tmd = getenv("TMPDIR");
        if (tmd && tmd[0]) p = tmd;
        if (!p) { tmd = getenv("TEMP"); if (tmd && tmd[0]) p = tmd; }
        if (!p) { tmd = getenv("TMP"); if (tmd && tmd[0]) p = tmd; }
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
