/*
 * process_cap_raw_smoke.c — Stage 9 (9.1.3 / 9.1.4) Linux Cap residual probe.
 *
 * Host-cc smoke for xlang_process_cap.h on Linux:
 *   - getpid via raw syscall 39/172 (no libc getpid)
 *   - getppid via raw syscall 110/173 (no libc getppid)
 *   - chdir via raw syscall 80/49 (no libc chdir)
 *   - getcwd via raw syscall 79/17 (no libc getcwd)
 *   - pipe via raw syscall 22/59 (no libc pipe)
 *   - dup2 via raw syscall 33/24 (no libc dup2)
 *   - fork via raw syscall 57/220 (no libc fork)
 *   - wait4 via raw syscall 61/260 (no libc waitpid)
 *   - exit via raw syscall 231/94 (no libc exit)
 *   - execvp via PATH search + raw execve (no libc execvp)
 *
 * PLATFORM: LINUX|x86_64|aarch64 gold.
 * Exit: 0 ok; 1..10 step failure.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <xlang_process_cap.h>

#ifndef __linux__
int main(void) {
  fprintf(stderr, "process_cap_raw_smoke: Linux only\n");
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

  /* Step 2: Cap getppid > 0 */
  ppid = xlang_proc_getppid();
  if (ppid <= 0) {
    fprintf(stderr, "xlang_proc_getppid failed: %ld\n", ppid);
    return 2;
  }

  /* Step 3: Cap getcwd fills buffer with absolute path */
  memset(buf1, 0, sizeof(buf1));
  n1 = xlang_proc_getcwd(buf1, sizeof(buf1));
  if (n1 <= 1 || buf1[0] != '/') {
    fprintf(stderr, "xlang_proc_getcwd failed: n=%ld, buf=%s\n", n1, buf1);
    return 3;
  }

  /* Step 4: Cap chdir to current directory succeeds */
  if (xlang_proc_chdir(".") != 0) {
    fprintf(stderr, "xlang_proc_chdir(\".\") failed\n");
    return 4;
  }

  /* Step 5: Cap chdir to invalid directory fails */
  if (xlang_proc_chdir("/non_existent_directory_xlang_cap_test_12345") != -1) {
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
    if (write(fds[1], &wbyte, 1) != 1) {
      fprintf(stderr, "pipe write failed\n");
      return 7;
    }
    if (read(fds[0], &rbyte, 1) != 1 || rbyte != 'K') {
      fprintf(stderr, "pipe read mismatch: %c vs K\n", rbyte);
      return 7;
    }
    close(fds[0]);
    close(fds[1]);
  }

  /* Step 8: Cap dup2 */
  {
    int fds[2] = {-1, -1};
    if (xlang_proc_pipe(fds) != 0) {
      return 8;
    }
    int dup_fd = xlang_proc_dup2(fds[0], 55);
    if (dup_fd != 55) {
      fprintf(stderr, "xlang_proc_dup2 failed: %d\n", dup_fd);
      return 8;
    }
    close(fds[0]);
    close(fds[1]);
    close(55);
  }

  /* Step 9: Cap fork + exit + waitpid */
  {
    long child = xlang_proc_fork();
    if (child < 0) {
      fprintf(stderr, "xlang_proc_fork failed\n");
      return 9;
    }
    if (child == 0) {
      xlang_proc_exit(42);
    }
    int status = 0;
    long w = xlang_proc_waitpid(child, &status, 0);
    if (w != child || !WIFEXITED(status) || WEXITSTATUS(status) != 42) {
      fprintf(stderr, "xlang_proc_waitpid failed: w=%ld, status=%d, exit=%d\n", w, status, WEXITSTATUS(status));
      return 9;
    }
  }

  /* Step 10: Cap fork + execvp + waitpid */
  {
    long child = xlang_proc_fork();
    if (child < 0) {
      fprintf(stderr, "xlang_proc_fork for execvp failed\n");
      return 10;
    }
    if (child == 0) {
      char *argv[] = {(char *)"true", NULL};
      xlang_proc_execvp("true", argv);
      xlang_proc_exit(127);
    }
    int status = 0;
    long w = xlang_proc_waitpid(child, &status, 0);
    if (w != child || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      fprintf(stderr, "xlang_proc_execvp waitpid failed: w=%ld, exit=%d\n", w, WEXITSTATUS(status));
      return 10;
    }
  }

  return 0;
}
#endif
