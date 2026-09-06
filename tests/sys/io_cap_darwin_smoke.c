/*
 * io_cap_darwin_smoke.c — Stage 9 (9.1.8) Darwin Cap residual probe.
 *
 * Host-cc smoke for xlang_io_cap.h on Darwin:
 *   - write via raw syscall 4 (SYS_write, no libc write)
 *   - read via raw syscall 3 (SYS_read, no libc read)
 *   - writev via raw syscall 121 (SYS_writev, no libc writev)
 *   - zero count / null buffer edge handling
 *
 * PLATFORM: MACOS|DARWIN gold.
 * Exit: 0 ok; 1..9 step failure.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>

#include <xlang_io_cap.h>

#ifndef __APPLE__
int main(void) {
  return 0;
}
#else

int main(void) {
  int fds[2];
  if (pipe(fds) != 0) {
    return 1;
  }

  /* Step 1: Single byte write and read */
  uint8_t one_byte = 0x5A;
  long nw = xlang_io_write(fds[1], &one_byte, 1);
  if (nw != 1) {
    close(fds[0]);
    close(fds[1]);
    return 2;
  }
  uint8_t read_byte = 0;
  long nr = xlang_io_read(fds[0], &read_byte, 1);
  if (nr != 1 || read_byte != 0x5A) {
    close(fds[0]);
    close(fds[1]);
    return 3;
  }

  /* Step 2: Multi-byte buffer write and read */
  const char *msg = "hello xlang cap io";
  size_t msg_len = strlen(msg);
  nw = xlang_io_write(fds[1], msg, msg_len);
  if (nw != (long)msg_len) {
    close(fds[0]);
    close(fds[1]);
    return 4;
  }
  char buf[64];
  memset(buf, 0, sizeof(buf));
  nr = xlang_io_read(fds[0], buf, msg_len);
  if (nr != (long)msg_len || memcmp(buf, msg, msg_len) != 0) {
    close(fds[0]);
    close(fds[1]);
    return 5;
  }

  /* Step 3: Vectored I/O writev */
  struct iovec iov[3];
  iov[0].iov_base = (void *)"vectored ";
  iov[0].iov_len = 9;
  iov[1].iov_base = (void *)"cap ";
  iov[1].iov_len = 4;
  iov[2].iov_base = (void *)"ok!";
  iov[2].iov_len = 3;
  long nwv = xlang_io_writev(fds[1], iov, 3);
  if (nwv != 16) {
    close(fds[0]);
    close(fds[1]);
    return 6;
  }
  memset(buf, 0, sizeof(buf));
  nr = xlang_io_read(fds[0], buf, 16);
  if (nr != 16 || memcmp(buf, "vectored cap ok!", 16) != 0) {
    close(fds[0]);
    close(fds[1]);
    return 7;
  }

  /* Step 4: Edge cases: count 0 returns 0 */
  if (xlang_io_write(fds[1], NULL, 0) != 0) {
    close(fds[0]);
    close(fds[1]);
    return 8;
  }
  if (xlang_io_read(fds[0], NULL, 0) != 0) {
    close(fds[0]);
    close(fds[1]);
    return 9;
  }
  if (xlang_io_writev(fds[1], NULL, 0) != 0) {
    close(fds[0]);
    close(fds[1]);
    return 10;
  }

  close(fds[0]);
  close(fds[1]);
  return 0;
}
#endif
