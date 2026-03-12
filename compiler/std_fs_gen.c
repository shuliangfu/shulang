/* generated from typeck */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static void shulang_panic_(int has_msg, int msg_val) {
  if (has_msg) (void)fprintf(stderr, "%d\n", msg_val);
  abort();
}
extern int32_t open(uint8_t * path, int32_t flags);
extern ptrdiff_t read(int32_t fd, uint8_t * buf, size_t count);
extern ptrdiff_t write(int32_t fd, uint8_t * buf, size_t count);
extern int32_t close(int32_t fd);
int32_t typeck_placeholder();
int32_t typeck_fs_invalid_handle();
int32_t typeck_fs_open_read(uint8_t * path);
int32_t typeck_fs_close(int32_t fd);
ptrdiff_t typeck_fs_read(int32_t fd, uint8_t * buf, size_t count);
ptrdiff_t typeck_fs_write(int32_t fd, uint8_t * buf, size_t count);
int32_t typeck_placeholder() {
  return 0;
}
int32_t typeck_fs_invalid_handle() {
  return (-1);
}
int32_t typeck_fs_open_read(uint8_t * path) {
  return open(path, 0);
}
int32_t typeck_fs_close(int32_t fd) {
  return close(fd);
}
ptrdiff_t typeck_fs_read(int32_t fd, uint8_t * buf, size_t count) {
  return read(fd, buf, count);
}
ptrdiff_t typeck_fs_write(int32_t fd, uint8_t * buf, size_t count) {
  return write(fd, buf, count);
}
