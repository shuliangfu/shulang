/**
 * std_fs_shim.c — 提供 std_fs_fs_* 符号供 -E-extern 生成的 pipeline/driver 链接。
 * 实现为调用 libc open/read/write/close。
 */

#include <stdint.h>
#include <stddef.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define open(path, flags) _open((path), _O_RDONLY)
#define read(fd, buf, count) _read((fd), (buf), (unsigned)(count))
#define write(fd, buf, count) _write((fd), (buf), (unsigned)(count))
#define close(fd) _close(fd)
#else
#include <unistd.h>
#include <fcntl.h>
#endif

int32_t std_fs_fs_open_read(uint8_t *path) {
  if (!path) return -1;
  return (int32_t)open((char *)path, 0);
}

int32_t std_fs_fs_close(int32_t fd) {
  return (int32_t)close(fd);
}

int32_t std_fs_fs_invalid_handle(void) {
  return -1;
}

ptrdiff_t std_fs_fs_read(int32_t fd, uint8_t *buf, size_t count) {
  if (!buf) return -1;
  return (ptrdiff_t)read(fd, buf, count);
}

ptrdiff_t std_fs_fs_write(int32_t fd, uint8_t *buf, size_t count) {
  if (!buf) return -1;
  return (ptrdiff_t)write(fd, buf, count);
}
