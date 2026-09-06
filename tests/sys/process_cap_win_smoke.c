/*
 * process_cap_win_smoke.c — Stage 9 (9.1.3 / 9.1.4) Windows Cap residual probe.
 *
 * Host-cc smoke for xlang_process_cap.h on Windows:
 *   - getpid via GetCurrentProcessId
 *   - getppid returns -1
 *   - chdir via SetCurrentDirectoryA
 *   - getcwd via GetCurrentDirectoryA
 *   - pipe via CreatePipe + _open_osfhandle
 *
 * PLATFORM: WINDOWS gold.
 * Exit: 0 ok; 1..7 step failure.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_process_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)
int main(void) {
  fprintf(stderr, "process_cap_win_smoke: Windows only\n");
  return 0;
}
#else

int main(void) {
  char buf1[1024];
  char buf2[1024];
  long pid = 0;
  long ppid = 0;
  long n1 = 0;
  long n2 = 0;

  /* Step 1: Cap getpid > 0 */
  pid = xlang_proc_getpid();
  if (pid <= 0) {
    fprintf(stderr, "xlang_proc_getpid failed: %ld\n", pid);
    return 1;
  }

  /* Step 2: Cap getppid is -1 on Windows */
  ppid = xlang_proc_getppid();
  if (ppid != -1) {
    fprintf(stderr, "xlang_proc_getppid expected -1, got: %ld\n", ppid);
    return 2;
  }

  /* Step 3: Cap getcwd fills buffer */
  memset(buf1, 0, sizeof(buf1));
  n1 = xlang_proc_getcwd(buf1, sizeof(buf1));
  if (n1 <= 1 || buf1[0] == '\0') {
    fprintf(stderr, "xlang_proc_getcwd failed: n=%ld, buf=%s\n", n1, buf1);
    return 3;
  }

  /* Step 4: Cap chdir to current directory succeeds */
  if (xlang_proc_chdir(".") != 0) {
    fprintf(stderr, "xlang_proc_chdir(\".\") failed\n");
    return 4;
  }

  /* Step 5: Cap chdir to invalid directory fails */
  if (xlang_proc_chdir("Z:\\non_existent_directory_xlang_cap_test_12345") != -1) {
    fprintf(stderr, "xlang_proc_chdir invalid expected -1\n");
    return 5;
  }

  /* Step 6: Cap getcwd matches original path */
  memset(buf2, 0, sizeof(buf2));
  n2 = xlang_proc_getcwd(buf2, sizeof(buf2));
  if (n2 != n1 || strcmp(buf1, buf2) != 0) {
    fprintf(stderr, "xlang_proc_getcwd mismatch: %s vs %s\n", buf1, buf2);
    return 6;
  }

  /* Step 7: Cap pipe create + read/write */
  {
    int fds[2] = {-1, -1};
    if (xlang_proc_pipe(fds) != 0 || fds[0] < 0 || fds[1] < 0) {
      fprintf(stderr, "xlang_proc_pipe failed\n");
      return 7;
    }
    char wbyte = 'K';
    char rbyte = 0;
    if (_write(fds[1], &wbyte, 1) != 1) {
      fprintf(stderr, "pipe write failed\n");
      return 7;
    }
    if (_read(fds[0], &rbyte, 1) != 1 || rbyte != 'K') {
      fprintf(stderr, "pipe read mismatch: %c vs K\n", rbyte);
      return 7;
    }
    _close(fds[0]);
    _close(fds[1]);
  }

  return 0;
}
#endif
