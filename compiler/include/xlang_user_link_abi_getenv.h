/*
 * xlang_user_link_abi_getenv.h — user-domain link_abi_getenv face for STD_AND_PANIC
 *
 * wave252–253 G.7: residual STD_AND_PANIC leaves (backtrace/env_os/process_os/log_os/http_glue)
 * must not call raw libc getenv; authority name is link_abi_getenv (≡ wave222 pure thin
 * null/empty gate → link_abi_getenv_impl Cap residual environ walk / Win CRT).
 *
 * Product host g05 authority remains labi_diag_pure.x + mega link_abi_getenv_impl —
 * this header / user_env.o are NEVER compiled into the g05 60/62-obj bag.
 *
 * Dual-end co-link policy (PLATFORM: SHARED user/STD_AND_PANIC only):
 * - Strong twin: runtime_panic C seeds (wave251) when that TU is linked (mac / non-x86_64 C).
 * - Linux x86_64 product panic is freestanding .s (no face, must not pull libc getenv).
 * - wave253: sole residual-domain body is compiler/runtime_link_abi_user_env.o
 *   (weak face; strong panic C wins when co-linked). Residual leaves declare only.
 * - PRIMARY_PANIC / push_minimal companion-push user_env.o so face is on the product
 *   -o line when panic is linked (always on append_std plan).
 *
 * Usage (residual leaves — declaration only):
 *   #include <xlang_user_link_abi_getenv.h>
 *   // then call link_abi_getenv("KEY") instead of getenv("KEY")
 *
 * Optional weak twin body in-header (legacy / tests only; product residual do not use):
 *   #define XLANG_USER_LINK_ABI_GETENV_PROVIDE_WEAK_TWIN 1
 *   #include <xlang_user_link_abi_getenv.h>
 */

#ifndef XLANG_USER_LINK_ABI_GETENV_H
#define XLANG_USER_LINK_ABI_GETENV_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__) || defined(__clang__)
#define XLANG_USER_ENV_WEAK __attribute__((weak))
#else
#define XLANG_USER_ENV_WEAK
#endif

#if defined(XLANG_USER_LINK_ABI_GETENV_PROVIDE_WEAK_TWIN)

#include <stdlib.h>
#include <xlang_environ_cap.h>

/**
 * Cap residual host getenv (legacy in-header weak twin; prefer runtime_link_abi_user_env.o).
 * @param name NUL-terminated environment key; may be null
 * @return value pointer from process env block, or NULL
 * PLATFORM: SHARED Cap (9.1.1) — unified xlang_environ_getenv.
 */
XLANG_USER_ENV_WEAK
const char *link_abi_getenv_impl(const char *name) {
  return xlang_environ_getenv(name);
}

/**
 * Public face twin (legacy in-header weak twin; prefer runtime_link_abi_user_env.o).
 * @param name NUL-terminated environment key
 * @return NULL on null/empty; else link_abi_getenv_impl value
 */
XLANG_USER_ENV_WEAK
const char *link_abi_getenv(const char *name) {
  if (!name || !name[0])
    return NULL;
  return link_abi_getenv_impl(name);
}

#else

const char *link_abi_getenv(const char *name);
const char *link_abi_getenv_impl(const char *name);

#endif /* XLANG_USER_LINK_ABI_GETENV_PROVIDE_WEAK_TWIN */

#ifdef __cplusplus
}
#endif

#endif /* XLANG_USER_LINK_ABI_GETENV_H */
