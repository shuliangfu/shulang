/*
 * dir_cap_win_smoke.c — Stage 9 (9.1.10) Windows Cap residual probe.
 *
 * Host-cc smoke for xlang_dir_cap.h on Windows:
 *   - opendir via _findfirst
 *   - readdir via _findnext
 *   - closedir via _findclose
 *
 * PLATFORM: WINDOWS gold.
 * Exit: 0 ok; 1..9 step failure.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_dir_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)
int main(void) {
  fprintf(stderr, "dir_cap_win_smoke: Windows only\n");
  return 0;
}
#else

int main(void) {
  const char *target_dir = "compiler/include";
  const char *missing_dir = "C:\\no_such_directory_dir_cap_9110";
  const char *expected_file = "xlang_dir_cap.h";
  void *dirp;
  int found = 0;
  int count = 0;

  /* Step 1: Open existing directory */
  dirp = xlang_dir_open(target_dir);
  if (!dirp) {
    fprintf(stderr, "xlang_dir_open(%s) failed\n", target_dir);
    return 1;
  }

  /* Step 2: Read entries */
  for (;;) {
    char *name = xlang_dir_readdir_name(dirp);
    if (!name)
      break;
    count++;
    if (strcmp(name, expected_file) == 0) {
      found = 1;
    }
  }

  if (count < 5) {
    fprintf(stderr, "Too few entries found in %s: %d\n", target_dir, count);
    xlang_dir_close(dirp);
    return 2;
  }

  if (!found) {
    fprintf(stderr, "Expected file %s not found in %s\n", expected_file, target_dir);
    xlang_dir_close(dirp);
    return 3;
  }

  /* Step 3: Close directory */
  if (xlang_dir_close(dirp) != 0) {
    fprintf(stderr, "xlang_dir_close failed\n");
    return 4;
  }

  /* Step 4: Open non-existing directory fails */
  if (xlang_dir_open(missing_dir) != NULL) {
    fprintf(stderr, "xlang_dir_open(%s) should have returned NULL\n", missing_dir);
    return 5;
  }

  /* Step 5: Edge cases */
  if (xlang_dir_open(NULL) != NULL) return 6;
  if (xlang_dir_open("") != NULL) return 6;
  if (xlang_dir_read(NULL) != NULL) return 6;
  if (xlang_dir_readdir_name(NULL) != NULL) return 6;
  if (xlang_dir_close(NULL) == 0) return 6;

  return 0;
}
#endif
