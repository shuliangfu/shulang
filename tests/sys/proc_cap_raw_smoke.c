/*
 * proc_cap_raw_smoke.c — Stage 9 (9.1.12) Linux Cap residual probe.
 *
 * Host-cc smoke for xlang_proc_cap.h on Linux:
 *   - open via raw syscall 2 (x86_64) / 56 openat (aarch64) (no libc open)
 *   - read via raw syscall 0 (x86_64) / 63 (aarch64) via xlang_io_read (no libc read)
 *   - close via raw syscall 3 (x86_64) / 57 (aarch64) (no libc close)
 *   - /proc/cpuinfo read and line scanning via xlang_proc_next_line
 *   - error and edge cases
 *
 * PLATFORM: LINUX gold.
 * Exit: 0 ok; 1..12 step failure.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <xlang_proc_cap.h>

#ifndef __linux__
int main(void) {
  return 0;
}
#else

int main(void) {
  /* Step 1: Open /proc/cpuinfo read-only */
  int fd = xlang_proc_open_ro("/proc/cpuinfo");
  if (fd < 0) {
    return 1;
  }

  /* Step 2: Read small amount via xlang_io_read */
  char buf[256];
  memset(buf, 0, sizeof(buf));
  long nr = xlang_io_read(fd, buf, sizeof(buf) - 1);
  if (nr <= 0) {
    xlang_proc_close_fd(fd);
    return 2;
  }
  buf[nr] = '\0';

  /* Step 3: Close fd via xlang_proc_close_fd */
  if (xlang_proc_close_fd(fd) != 0) {
    return 3;
  }

  /* Step 4: High-level xlang_proc_read_file on /proc/cpuinfo */
  char file_buf[2048];
  memset(file_buf, 0, sizeof(file_buf));
  long total = xlang_proc_read_file("/proc/cpuinfo", file_buf, sizeof(file_buf));
  if (total <= 0 || file_buf[total] != '\0') {
    return 4;
  }

  /* Step 5: Test xlang_proc_next_line parsing on synthetic lines */
  char test_lines[] = "line1\nline2\nline3";
  char *l1 = test_lines;
  char *l2 = xlang_proc_next_line(l1);
  if (!l2 || strcmp(l1, "line1") != 0) {
    return 5;
  }
  char *l3 = xlang_proc_next_line(l2);
  if (!l3 || strcmp(l2, "line2") != 0) {
    return 6;
  }
  char *l4 = xlang_proc_next_line(l3);
  if (l4 != NULL || strcmp(l3, "line3") != 0) {
    return 7;
  }

  /* Step 6: Edge cases */
  if (xlang_proc_open_ro("/non_existent_file_xlang_cap_12345") >= 0) {
    return 8;
  }
  if (xlang_proc_read_file(NULL, file_buf, sizeof(file_buf)) != -1) {
    return 9;
  }
  if (xlang_proc_read_file("/proc/cpuinfo", NULL, 100) != -1) {
    return 10;
  }
  if (xlang_proc_read_file("/proc/cpuinfo", file_buf, 1) != -1) {
    return 11;
  }
  if (xlang_proc_next_line(NULL) != NULL) {
    return 12;
  }

  return 0;
}
#endif
