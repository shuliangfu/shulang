/* seeds/runtime_random_fill.from_x.c — G-02f-20 product TU
 * G-02f-104 helper gates.
 * Product: runtime_random_fill.o; OS bridge logic in rest C; public wrappers
 * provided by thin runtime_random_fill.x in R2 mode (XLANG_RUNTIME_RANDOM_FILL_FROM_X).
 *
 * runtime_random_fill.c — CSPRNG OS glue (migrated from std/random/random_os_glue.c)
 *
 * [File role] random_fill_bytes_c: getrandom / getentropy / BCryptGenRandom.
 *             random.x calls via extern; linked alongside random.o into exe.
 *
 * Wave514 (2026-07-27): R2 full migration. random_fill_bytes_c business logic
 * moved to .x (thin); this file now provides _impl OS bridge implementations
 * only, with cold-mode fallback wrappers under #ifndef XLANG_RUNTIME_RANDOM_FILL_FROM_X.
 *
 * PLATFORM: SHARED Cap (9.1.6)
 *
 * Cap residual 9.1.6: SHARED Cap convergence (Linux raw syscall getrandom /
 * Darwin raw syscall getentropy / Windows BCrypt via xlang_random_cap.h; no libc).
 */

#include <stdint.h>
#include <string.h>

/* Forward declarations for thin-provided _c functions (R2 / FROM_X mode). */
void *random_get_alg(void);
int32_t random_fill_bytes_c(uint8_t *buf, int32_t len);

/* ========== Platform includes ========== */
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <bcrypt.h>
#include <synchapi.h>
#pragma comment(lib, "bcrypt.lib")
#endif
#include <xlang_random_cap.h>

/* ========== random_get_alg_impl (Windows: BCrypt lazy init; non-Windows: stub) ========== */
#if defined(_WIN32) || defined(_WIN64)
static INIT_ONCE g_random_init_once = INIT_ONCE_STATIC_INIT;
static BCRYPT_ALG_HANDLE g_random_alg = NULL;

BOOL CALLBACK random_init_callback(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *Context) {
    (void)InitOnce;
    (void)Parameter;
    BCRYPT_ALG_HANDLE alg = NULL;
    NTSTATUS st = BCryptOpenAlgorithmProvider(&alg, BCRYPT_RNG_ALGORITHM, NULL, 0);
    if (st != 0 || !alg) return FALSE;
    *(BCRYPT_ALG_HANDLE *)Context = alg;
    return TRUE;
}

BCRYPT_ALG_HANDLE random_get_alg_impl(void) {
    if (!InitOnceExecuteOnce(&g_random_init_once, random_init_callback, NULL, (PVOID *)&g_random_alg))
        return NULL;
    return g_random_alg;
}
#else
/* Non-Windows stub: .x thin wrapper calls random_get_alg_impl regardless of
 * platform; must provide a definition to avoid ld -r undefined reference. */
void *random_get_alg_impl(void) {
    return NULL;
}
#endif

#ifndef XLANG_RUNTIME_RANDOM_FILL_FROM_X
/* Cold mode fallback: public wrapper provided by seed. */
void *random_get_alg(void) {
    return random_get_alg_impl();
}
#endif

/* ========== random_fill_bytes_impl ========== */
/**
 * OS bridge: fill buffer with CSPRNG bytes via unified Cap xlang_random_fill_bytes.
 * Windows: BCryptGenRandom (xlang_random_cap.h)
 * Linux: Cap raw syscall getrandom (xlang_random_cap.h, no libc)
 * Darwin: Cap raw syscall getentropy (xlang_random_cap.h, no libc)
 * PLATFORM: SHARED Cap (9.1.6)
 */
int32_t random_fill_bytes_impl(uint8_t *buf, int32_t len) {
    return xlang_random_fill_bytes(buf, len);
}

#ifndef XLANG_RUNTIME_RANDOM_FILL_FROM_X
/* Cold mode fallback: public wrapper provided by seed. */
int32_t random_fill_bytes_c(uint8_t *buf, int32_t len) {
    return random_fill_bytes_impl(buf, len);
}
#endif
