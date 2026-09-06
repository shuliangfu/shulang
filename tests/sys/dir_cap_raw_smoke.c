/*
 * dir_cap_raw_smoke.c — Stage 9 (9.1.10) Linux raw Cap residual probe.
 *
 * Host-cc smoke for xlang_dir_cap.h on Linux:
 *   - opendir via raw syscall open(O_DIRECTORY) (no libc opendir)
 *   - readdir via raw syscall getdents64 (no libc readdir)
 *   - closedir via raw syscall close (no libc closedir)
 *   - layout verification: d_name at offset 19 (matching DIRENT_D_NAME_OFF on Linux)
 *
 * PLATFORM: LINUX|x86_64 gold.
 * Exit: 0 ok; 1..9 step failure.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_dir_cap.h>

#if !defined(__linux__)
int main(void) {
  fprintf(stderr, "dir_cap_raw_smoke: Linux only\n");
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

  /* Step 2: Read entries and verify offset 19 */
  for (;;) {
    void *de = xlang_dir_read(dirp);
    if (!de)
      break;
    count++;
    /* Verify Linux glibc layout: d_name is at offset 19 */
    const char *name_via_offset = ((const char *)de) + 19;
    struct xlang_dirent_glibc *de_s = (struct xlang_dirent_glibc *)de;
    if (strcmp(name_via_offset, de_s->d_name) != 0) {
      fprintf(stderr, "name mismatch at offset 19: '%s' vs '%s'\n",
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

  /* Step 6: Edge cases */
  if (xlang_dir_open(NULL) != NULL) return 9;
  if (xlang_dir_open("") != NULL) return 9;
  if (xlang_dir_read(NULL) != NULL) return 9;
  if (xlang_dir_readdir_name(NULL) != NULL) return 9;
  if (xlang_dir_close(NULL) == 0) return 9;

  return 0;
}
#endif
