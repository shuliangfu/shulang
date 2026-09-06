/*
 * path_cap_darwin_smoke.c — Stage 9 (9.1.2) Darwin Cap residual probe.
 *
 * Host-cc smoke for xlang_path_cap.h on Darwin:
 *   - access via raw syscall 33 (no libc access)
 *   - stat via raw syscall 338 (SYS_stat64, no libc stat)
 *   - fstat via raw syscall 339 (SYS_fstat64, no libc fstat)
 *   - realpath via raw open + fcntl(F_GETPATH) + close (no libc realpath)
 *
 * PLATFORM: MACOS|DARWIN gold.
 * Exit: 0 ok; 1..9 step failure.
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <xlang_path_cap.h>

#ifndef __APPLE__
int main(void) {
  fprintf(stderr, "path_cap_darwin_smoke: Darwin only\n");
  return 0;
}
#else

int main(void) {
  const char *target = "compiler/include/xlang_path_cap.h";
  const char *missing = "/no_such_file_or_dir_path_cap_912";
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
#if defined(__aarch64__)
  fd = (int)xlang_darwin_path_sys3(5 /* SYS_open */, (long)target, O_RDONLY, 0);
#elif defined(__x86_64__)
  fd = (int)xlang_darwin_path_sys3(0x2000005L, (long)target, O_RDONLY, 0);
#else
  fd = open(target, O_RDONLY);
#endif
  if (fd < 0) {
    fprintf(stderr, "open(%s) failed\n", target);
    return 5;
  }
  memset(&fst, 0, sizeof(fst));
  if (xlang_path_fstat(fd, &fst) != 0 || fst.st_size != st.st_size) {
    fprintf(stderr, "xlang_path_fstat failed: size=%lld vs %lld\n",
            (long long)fst.st_size, (long long)st.st_size);
#if defined(__aarch64__)
    (void)xlang_darwin_path_sys1(6 /* SYS_close */, fd);
#elif defined(__x86_64__)
    (void)xlang_darwin_path_sys1(0x2000006L, fd);
#else
    close(fd);
#endif
    return 5;
  }
#if defined(__aarch64__)
  (void)xlang_darwin_path_sys1(6 /* SYS_close */, fd);
#elif defined(__x86_64__)
  (void)xlang_darwin_path_sys1(0x2000006L, fd);
#else
  close(fd);
#endif

  /* Step 6: Cap realpath on "." returns absolute path */
  memset(buf, 0, sizeof(buf));
  if (!xlang_path_realpath(".", buf) || buf[0] != '/') {
    fprintf(stderr, "xlang_path_realpath(\".\") failed: %s\n", buf);
    return 6;
  }

  /* Step 7: Cap realpath on relative path with .. normalizes correctly */
  memset(buf, 0, sizeof(buf));
  if (!xlang_path_realpath("compiler/../tests", buf) || buf[0] != '/') {
    fprintf(stderr, "xlang_path_realpath(\"compiler/../tests\") failed: %s\n", buf);
    return 7;
  }
  size_t blen = strlen(buf);
  if (blen < 6 || strcmp(buf + blen - 6, "/tests") != 0) {
    fprintf(stderr, "xlang_path_realpath output does not end in /tests: %s\n", buf);
    return 7;
  }

  /* Step 8: Cap realpath on non-existing path returns NULL */
  if (xlang_path_realpath(missing, buf) != NULL) {
    fprintf(stderr, "xlang_path_realpath(%s) should have returned NULL\n", missing);
    return 8;
  }

  /* Step 9: Edge cases */
  if (xlang_path_access(NULL, 0) == 0) return 9;
  if (xlang_path_access("", 0) == 0) return 9;
  if (xlang_path_stat(NULL, &st) == 0) return 9;
  if (xlang_path_stat("", &st) == 0) return 9;
  if (xlang_path_fstat(-1, &fst) == 0) return 9;
  if (xlang_path_realpath(NULL, buf) != NULL) return 9;
  if (xlang_path_realpath("", buf) != NULL) return 9;
  if (xlang_path_realpath(".", NULL) != NULL) return 9;

  return 0;
}
#endif
