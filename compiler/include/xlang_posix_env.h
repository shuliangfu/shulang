/* xlang_posix_env.h — POSIX setenv/unsetenv shims for MinGW.
 * Why: MinGW <stdlib.h> declares _putenv_s but not setenv/unsetenv.
 *      driver_gen.c:559 (generated from src/driver.x main_cmd_run) calls
 *      setenv("XLANG_RUN_QUIET", "1", 1). Multiple seed files (runtime_env_os,
 *      runtime_link_abi, rt_compile, lsp_diag_pipeline_ctx)
 *      also call setenv/unsetenv. On macOS/Linux libc provides these; on MinGW
 *      we provide static inline wrappers calling _putenv_s.
 *
 * Included from two places:
 *   1. include/unistd.h shim (for files that #include <unistd.h>)
 *   2. src/x_stubs.h (force-included via -include for driver_gen.c, lsp_diag_gen.c,
 *      and other .o builds that don't pull <unistd.h>)
 * Guard XLANG_POSIX_ENV_SHIM_DEFINED prevents double static inline definitions
 * when both headers are included in the same translation unit.
 *
 * Invariant: setenv(overwrite=0) + existing var = no-op success (POSIX).
 *            unsetenv via _putenv_s(name, "") sets empty string (close enough
 *            for XLANG usage which only checks getenv != NULL).
 * PLATFORM: WINDOWS | MSYS | MINGW (only effective when _WIN32 defined). */
#ifndef XLANG_POSIX_ENV_H
#define XLANG_POSIX_ENV_H

#if defined(_WIN32) || defined(_WIN64)

#ifndef XLANG_POSIX_ENV_SHIM_DEFINED
#define XLANG_POSIX_ENV_SHIM_DEFINED

/* Forward-declare getenv / _putenv_s (MinGW <stdlib.h>) instead of pulling
 * in <stdlib.h>, which would conflict with XLANG-generated
 *   extern uint8_t * calloc(size_t, size_t)
 *   extern void free(uint8_t *)
 * declarations (uint8_t* vs void* return types; MinGW gcc strictly errors
 * while Apple clang tolerates as builtin-declaration-mismatch warning). */
#ifndef XLANG_POSIX_ENV_GETENV_DECLARED
#define XLANG_POSIX_ENV_GETENV_DECLARED
char *getenv(const char *name);
int _putenv_s(const char *name, const char *value);
#endif

/* setenv — POSIX set environment variable.
 *          Returns 0 on success, -1 on error (POSIX semantics).
 *          `overwrite == 0` and existing variable -> no-op success. */
static inline int setenv(const char *name, const char *value, int overwrite) {
    if (!overwrite && getenv(name) != NULL) return 0;
    return _putenv_s(name, value) == 0 ? 0 : -1;
}

/* unsetenv — POSIX unset environment variable.
 *            Returns 0 on success, -1 on error (POSIX semantics).
 *            Note: MinGW _putenv_s(name, "") sets empty string rather than
 *            removing the variable entirely; acceptable for XLANG usage. */
static inline int unsetenv(const char *name) {
    return _putenv_s(name, "") == 0 ? 0 : -1;
}

#endif /* XLANG_POSIX_ENV_SHIM_DEFINED */

#endif /* _WIN32 */

#endif /* XLANG_POSIX_ENV_H */
