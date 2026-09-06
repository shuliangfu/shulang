/* seeds/runtime_link_abi_user_env.from_x.c — wave253 G.7 user-domain face TU
 *
 * Sole compiled body of user/STD_AND_PANIC link_abi_getenv face for residual
 * leaves (backtrace/env_os/process_os/log_os/http_glue). Closes wave252 multi-copy
 * weak twins that lived in each residual TU via xlang_user_link_abi_getenv.h
 * PROVIDE_WEAK_TWIN.
 *
 * Semantics ≡ wave222 pure thin (null/empty → null) + Cap residual 9.1.1
 * environ walk (≡ product mega / wave251 panic twin). This TU is **weak** so
 * strong twin from runtime_panic C seeds (mac / non-x86_64) wins when co-linked;
 * Linux x86_64 product panic is freestanding .s (no face) — this .o supplies the
 * face when residual or PRIMARY_PANIC companion path links it.
 *
 * NEVER in g05 60/62-obj host bag (labi_diag_pure + mega link_abi_getenv_impl
 * remain product host authority). User / STD_AND_PANIC / test_c only.
 *
 * PLATFORM: SHARED — user-domain residual face; host residual via single face.
 */

#include <stdlib.h>
#include <xlang_environ_cap.h>

#if defined(__GNUC__) || defined(__clang__)
#define XLANG_USER_ENV_WEAK __attribute__((weak))
#else
#define XLANG_USER_ENV_WEAK
#endif

/**
 * Cap residual host getenv for user-linked residual / companion face (≡ product _impl).
 * Weak: strong may come from runtime_panic C seed (wave251).
 * @param name NUL-terminated environment key; may be null
 * @return value pointer from process env block, or NULL
 * PLATFORM: SHARED Cap (9.1.1) — unified xlang_environ_getenv.
 */
XLANG_USER_ENV_WEAK
const char *link_abi_getenv_impl(const char *name) {
  return xlang_environ_getenv(name);
}

/**
 * Public face twin: null/empty gate then host residual (≡ product pure thin / wave251).
 * Weak: strong may come from runtime_panic C seed (wave251).
 * @param name NUL-terminated environment key
 * @return NULL on null/empty; else link_abi_getenv_impl value
 */
XLANG_USER_ENV_WEAK
const char *link_abi_getenv(const char *name) {
  if (!name || !name[0])
    return NULL;
  return link_abi_getenv_impl(name);
}
