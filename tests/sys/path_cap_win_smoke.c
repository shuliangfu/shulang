/*
 * path_cap_win_smoke.c — Stage 9 (9.1.2) Windows Cap residual probe.
 *
 * Host-cc smoke for xlang_path_cap.h on Windows:
 *   - access via _access
 *   - stat via stat
 *   - fstat via fstat
 *   - realpath via _fullpath
 *
 * PLATFORM: WINDOWS gold.
 * Exit: 0 ok; 1..9 step failure.
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <xlang_path_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)
int main(void) {
  fprintf(stderr, "path_cap_win_smoke: Windows only\n");
  return 0;
}
#else

int main(void) {
  const char *target = "compiler/include/xlang_path_cap.h";
  const char *missing = "C:\\no_such_file_or_dir_path_cap_912";
  char buf[1024];
  struct stat st;
  struct stat fst;
  int fd;

  /* Step 1: Cap access existing file succeeds */
  if (xlang_path_access(target, 0 /* F_OK */) != 0) {
    fprintf(stderr, "xlang_path_access(%s) failed\n", target);
    return 1;
  }

  /* Step 2: Cap access non-existing file fails */
  if (xlang_path_access(missing, 0 /* F_OK */) == 0) {
    fprintf(stderr, "xlang_path_access(%s) should have failed\n", missing);
    return 2;
  }

  /* Step 3: Cap stat existing file succeeds and returns non-zero size */
  memset(&st, 0, sizeof(st));
  if (xlang_path_stat(target, &st) != 0 || st.st_size <= 0) {
    fprintf(stderr, "xlang_path_stat(%s) failed: size=%lld\n", target, (long long)st.st_size);
    return 3;
  }

  /* Step 4: Cap stat non-existing file fails */
  if (xlang_path_stat(missing, &st) == 0) {
    fprintf(stderr, "xlang_path_stat(%s) should have failed\n", missing);
    return 4;
  }

  /* Step 5: Cap fstat on open fd succeeds and matches stat size */
  fd = open(target, O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "open(%s) failed\n", target);
    return 5;
  }
  memset(&fst, 0, sizeof(fst));
  if (xlang_path_fstat(fd, &fst) != 0 || fst.st_size != st.st_size) {
    fprintf(stderr, "xlang_path_fstat failed: size=%lld vs %lld\n",
            (long long)fst.st_size, (long long)st.st_size);
    close(fd);
    return 5;
  }
  close(fd);

  /* Step 6: Cap realpath on "." returns non-empty path */
  memset(buf, 0, sizeof(buf));
  if (!xlang_path_realpath(".", buf) || buf[0] == '\0') {
    fprintf(stderr, "xlang_path_realpath(\".\") failed: %s\n", buf);
    return 6;
  }

  /* Step 7: Edge cases */
  if (xlang_path_access(NULL, 0) == 0) return 7;
  if (xlang_path_access("", 0) == 0) return 7;
  if (xlang_path_stat(NULL, &st) == 0) return 7;
  if (xlang_path_stat("", &st) == 0) return 7;
  if (xlang_path_fstat(-1, &fst) == 0) return 7;
  if (xlang_path_realpath(NULL, buf) != NULL) return 7;
  if (xlang_path_realpath("", buf) != NULL) return 7;
  if (xlang_path_realpath(".", NULL) != NULL) return 7;

  return 0;
}
#endif
