/*
 * xlang_environ_cap.h — Cap residual 9.1.1: walk/mutate environ without libc
 * getenv / setenv / unsetenv.
 *
 * Single authority for POSIX process-env block ops and Windows dual-block env ops used by:
 *   link_abi_getenv_impl (product mega + user_env + panic twins + header weak),
 *   process_setenv_impl / process_unsetenv_impl,
 *   env_setenv_c_impl / env_unsetenv_c_impl.
 *
 * Why not syscall: Linux/Darwin have no getenv/setenv syscall; Cap residual = direct
 * environ[] access (same block libc getenv reads).
 * - Linux: direct extern char **environ;
 * - Darwin: (*_NSGetEnviron()) from <crt_externs.h>
 * - Windows: dual CRT (_putenv / getenv) + process env block (SetEnvironmentVariableA)
 *
 * setenv may allocate a new environ vector; per-TU static tracks whether *this*
 * TU owns the current vector so we never free the initial kernel/CRT environ.
 * Cross-TU: only free when owned==environ (no double-free; may leak prior
 * vectors for process lifetime — acceptable Cap residual).
 *
 * PLATFORM: SHARED Cap (9.1.1).
 */

#ifndef XLANG_ENVIRON_CAP_H
#define XLANG_ENVIRON_CAP_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <stdlib.h>

/**
 * Cap residual getenv: query environment via CRT getenv.
 * @param name NUL-terminated key; null/empty -> NULL.
 * @return pointer into CRT environment string, or NULL if absent.
 * PLATFORM: WINDOWS Win32 Cap (9.1.1).
 */
static inline const char *xlang_environ_getenv(const char *name) {
  if (!name || !name[0])
    return NULL;
  return getenv(name);
}

/**
 * Cap residual setenv: set environment variable name=value in both CRT and process env block.
 * @param name NUL-terminated key (non-empty, no '=')
 * @param value NUL-terminated value; NULL treated as ""
 * @param overwrite 0 -> leave existing; non-0 -> replace
 * @return 0 success, -1 failure
 * PLATFORM: WINDOWS Win32 Cap (9.1.1).
 */
static inline int xlang_environ_setenv(const char *name, const char *value, int overwrite) {
  if (!name || !name[0])
    return -1;
  (void)overwrite;
  const char *v = value ? value : "";
  if (v[0] != '\0') {
    size_t nlen = strlen(name);
    size_t vlen = strlen(v);
    if (nlen + vlen + 2 > 2048)
      return -1;
    char buf[2048];
    memcpy(buf, name, nlen);
    buf[nlen] = '=';
    memcpy(buf + nlen + 1, v, vlen + 1);
    if (_putenv(buf) != 0)
      return -1;
  }
  if (SetEnvironmentVariableA(name, v) == 0)
    return -1;
  return 0;
}

/**
 * Cap residual unsetenv: remove environment variable from both CRT and process env block.
 * @param name NUL-terminated key
 * @return 0 success, -1 on null name
 * PLATFORM: WINDOWS Win32 Cap (9.1.1).
 */
static inline int xlang_environ_unsetenv(const char *name) {
  if (!name || !name[0])
    return -1;
  char buf[512];
  size_t n = 0;
  while (n < sizeof(buf) - 2 && name[n]) {
    buf[n] = (char)name[n];
    n++;
  }
  if (n >= sizeof(buf) - 2)
    return -1;
  buf[n++] = '=';
  buf[n] = '\0';
  if (_putenv(buf) != 0)
    return -1;
  if (SetEnvironmentVariableA(name, NULL) == 0)
    return -1;
  return 0;
}

#else /* POSIX: Linux & Darwin */

#include <stdlib.h>

#if defined(__APPLE__)
#include <crt_externs.h>
#if !defined(environ)
#define environ (*_NSGetEnviron())
#endif
#else
extern char **environ;
#endif

/**
 * Cap residual getenv: scan environ for name=…; return pointer to value.
 * @param name NUL-terminated key; null/empty → NULL. Must not contain '='.
 * @return pointer into environ entry after '=', or NULL if absent.
 * PLATFORM: POSIX (Linux / Darwin) — no libc getenv.
 */
static inline const char *xlang_environ_getenv(const char *name) {
  size_t nlen;
  char **e;
  if (!name || !name[0] || !environ)
    return NULL;
  nlen = strlen(name);
  for (e = environ; *e; e++) {
    if (strncmp(*e, name, nlen) == 0 && (*e)[nlen] == '=')
      return *e + nlen + 1;
  }
  return NULL;
}

/**
 * Cap residual setenv: replace or append name=value in environ.
 * @param name NUL-terminated key (non-empty, no '=')
 * @param value NUL-terminated value; NULL treated as ""
 * @param overwrite 0 → leave existing; non-0 → replace
 * @return 0 success, -1 failure
 * PLATFORM: POSIX (Linux / Darwin) — no libc setenv.
 */
static inline int xlang_environ_setenv(const char *name, const char *value, int overwrite) {
  size_t nlen;
  size_t vlen;
  size_t i;
  char *entry;
  char **e;
  char **neu;
  int count;
  int idx;
  /* Per-TU ownership of current environ vector (see file header). */
  static char **owned = NULL;

  if (!name || !name[0])
    return -1;
  for (i = 0; name[i]; i++) {
    if (name[i] == '=')
      return -1;
  }
  if (!environ)
    return -1;
  if (!value)
    value = "";
  nlen = strlen(name);
  vlen = strlen(value);

  idx = -1;
  count = 0;
  for (e = environ; *e; e++, count++) {
    if (strncmp(*e, name, nlen) == 0 && (*e)[nlen] == '=') {
      idx = (int)(e - environ);
      if (!overwrite)
        return 0;
      break;
    }
  }

  entry = (char *)malloc(nlen + 1 + vlen + 1);
  if (!entry)
    return -1;
  memcpy(entry, name, nlen);
  entry[nlen] = '=';
  memcpy(entry + nlen + 1, value, vlen);
  entry[nlen + 1 + vlen] = '\0';

  if (idx >= 0) {
    /* Do not free old slot — may point into initial environ. */
    environ[idx] = entry;
    return 0;
  }

  /* Append: allocate a fresh vector; never realloc the initial environ. */
  neu = (char **)malloc((size_t)(count + 2) * sizeof(char *));
  if (!neu) {
    free(entry);
    return -1;
  }
  for (i = 0; i < (size_t)count; i++)
    neu[i] = environ[i];
  neu[count] = entry;
  neu[count + 1] = NULL;
  if (owned != NULL && owned == environ)
    free(environ);
  environ = neu;
  owned = neu;
  return 0;
}

/**
 * Cap residual unsetenv: remove name=… from environ by shifting slots.
 * @param name NUL-terminated key
 * @return 0 success (including not found), -1 on null name
 * PLATFORM: POSIX (Linux / Darwin) — no libc unsetenv.
 */
static inline int xlang_environ_unsetenv(const char *name) {
  size_t nlen;
  char **e;
  char **dst;
  if (!name || !name[0] || !environ)
    return name ? 0 : -1;
  nlen = strlen(name);
  dst = environ;
  for (e = environ; *e; e++) {
    if (strncmp(*e, name, nlen) == 0 && (*e)[nlen] == '=')
      continue; /* drop matching slot; do not free (may be initial environ) */
    *dst++ = *e;
  }
  *dst = NULL;
  return 0;
}

#endif /* Platform branches */

#endif /* XLANG_ENVIRON_CAP_H */
