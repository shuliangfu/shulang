/*
 * dir_cap_darwin_smoke.c — Stage 9 (9.1.10) Darwin Cap residual probe.
 *
 * Host-cc smoke for xlang_dir_cap.h on Darwin:
 *   - opendir via raw syscall open(O_DIRECTORY) (no libc opendir)
 *   - readdir via raw syscall 344 (SYS_getdirentries64, no libc readdir)
 *   - closedir via raw syscall close (no libc closedir)
 *   - layout verification: d_name at offset 21 (matching DIRENT_D_NAME_OFF)
 *   - regular file must return NULL (POSIX opendir / fmt_path_stat_kind)
 *
 * PLATFORM: MACOS|DARWIN gold.
 * Exit: 0 ok; 1..10 step failure.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_dir_cap.h>

#ifndef __APPLE__
int main(void) {
  fprintf(stderr, "dir_cap_darwin_smoke: Darwin only\n");
  return 0;
}
#else

int main(void) {
  const char *target_dir = "compiler/include";
  const char *missing_dir = "/no_such_directory_dir_cap_9110";
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

  /* Step 2: Read entries and verify offset 21 */
  for (;;) {
    void *de = xlang_dir_read(dirp);
    if (!de)
      break;
    count++;
    /* Verify Darwin layout: d_name is at offset 21 */
    const char *name_via_offset = ((const char *)de) + 21;
    struct xlang_darwin_dirent64 *de_s = (struct xlang_darwin_dirent64 *)de;
    if (strcmp(name_via_offset, de_s->d_name) != 0) {
      fprintf(stderr, "name mismatch at offset 21: '%s' vs '%s'\n",
              name_via_offset, de_s->d_name);
      xlang_dir_close(dirp);
      return 2;
    }
    if (strcmp(name_via_offset, expected_file) == 0) {
      found = 1;
    }
  }

  if (count < 5) {
    fprintf(stderr, "Too few entries found in %s: %d\n", target_dir, count);
    xlang_dir_close(dirp);
    return 3;
  }

  if (!found) {
    fprintf(stderr, "Expected file %s not found in %s\n", expected_file, target_dir);
    xlang_dir_close(dirp);
    return 4;
  }

  /* Step 3: Close directory */
  if (xlang_dir_close(dirp) != 0) {
    fprintf(stderr, "xlang_dir_close failed\n");
    return 5;
  }

  /* Step 4: Reopen and test xlang_dir_readdir_name */
  dirp = xlang_dir_open(target_dir);
  if (!dirp) {
    fprintf(stderr, "reopen %s failed\n", target_dir);
    return 6;
  }
  int found2 = 0;
  char *n;
  while ((n = xlang_dir_readdir_name(dirp)) != NULL) {
    if (strcmp(n, expected_file) == 0) {
      found2 = 1;
    }
  }
  xlang_dir_close(dirp);
  if (!found2) {
    fprintf(stderr, "xlang_dir_readdir_name did not find %s\n", expected_file);
    return 7;
  }

  /* Step 5: Open non-existing directory fails */
  if (xlang_dir_open(missing_dir) != NULL) {
    fprintf(stderr, "xlang_dir_open(%s) should have returned NULL\n", missing_dir);
    return 8;
  }

  /* Step 5b: POSIX opendir(file) is NULL. Without O_DIRECTORY, SYS_open
   * succeeds and fmt_path_stat_kind classifies every .x file as a directory
   * (Darwin FMT001 empty collect). PLATFORM: MACOS|DARWIN */
  if (xlang_dir_open("compiler/include/xlang_dir_cap.h") != NULL) {
    fprintf(stderr, "xlang_dir_open(regular file) should have returned NULL\n");
    return 10;
  }

  /* Step 6: Edge cases */
  if (xlang_dir_open(NULL) != NULL) return 9;
  if (xlang_dir_open("") != NULL) return 9;
  if (xlang_dir_read(NULL) != NULL) return 9;
  if (xlang_dir_readdir_name(NULL) != NULL) return 9;
  if (xlang_dir_close(NULL) == 0) return 9;

  return 0;
}
#endif
