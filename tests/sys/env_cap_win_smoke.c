/*
 * env_cap_win_smoke.c — Stage 9 (9.1.1) Windows Cap residual probe.
 *
 * Host-cc smoke for xlang_environ_cap.h on Windows:
 *   - getenv via xlang_environ_getenv
 *   - setenv via xlang_environ_setenv (dual CRT _putenv + SetEnvironmentVariableA)
 *   - unsetenv via xlang_environ_unsetenv (dual CRT _putenv + SetEnvironmentVariableA)
 *
 * PLATFORM: WINDOWS gold.
 * Exit: 0 ok; 1..8 step failure.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_environ_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)
int main(void) {
  fprintf(stderr, "env_cap_win_smoke: Windows only\n");
  return 0;
}
#else

int main(void) {
  const char *val;
  int r;

  /* Step 1: Cap getenv("PATH") must return non-NULL */
  val = xlang_environ_getenv("PATH");
  if (!val || val[0] == '\0') {
    fprintf(stderr, "xlang_environ_getenv(\"PATH\") failed\n");
    return 1;
  }

  /* Step 2: Cap setenv new key */
  r = xlang_environ_setenv("XLANG_WIN_ENV_TEST", "val_alpha", 1);
  if (r != 0) {
    fprintf(stderr, "xlang_environ_setenv step 2 failed: %d\n", r);
    return 2;
  }

  /* Step 3: Cap getenv sees new value */
  val = xlang_environ_getenv("XLANG_WIN_ENV_TEST");
  if (!val || strcmp(val, "val_alpha") != 0) {
    fprintf(stderr, "xlang_environ_getenv step 3 failed: %s\n", val ? val : "NULL");
    return 3;
  }

  /* Step 4: Cap setenv with overwrite=1 replaces existing */
  r = xlang_environ_setenv("XLANG_WIN_ENV_TEST", "val_beta", 1);
  if (r != 0) {
    fprintf(stderr, "xlang_environ_setenv step 4 failed: %d\n", r);
    return 4;
  }
  val = xlang_environ_getenv("XLANG_WIN_ENV_TEST");
  if (!val || strcmp(val, "val_beta") != 0) {
    fprintf(stderr, "xlang_environ_getenv step 4 check failed: %s\n", val ? val : "NULL");
    return 4;
  }

  /* Step 5: Cap unsetenv removes key */
  r = xlang_environ_unsetenv("XLANG_WIN_ENV_TEST");
  if (r != 0) {
    fprintf(stderr, "xlang_environ_unsetenv step 5 failed: %d\n", r);
    return 5;
  }

  /* Step 6: Cap getenv returns NULL after unsetenv */
  val = xlang_environ_getenv("XLANG_WIN_ENV_TEST");
  if (val != NULL) {
    fprintf(stderr, "xlang_environ_getenv step 6 failed (expected NULL, got %s)\n", val);
    return 6;
  }

  /* Step 7: Invalid inputs validation */
  if (xlang_environ_getenv(NULL) != NULL) return 7;
  if (xlang_environ_getenv("") != NULL) return 7;
  if (xlang_environ_setenv(NULL, "foo", 1) == 0) return 7;

  return 0;
}
#endif
