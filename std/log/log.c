/**
 * std/log/log.c — 日志写入 stderr，带级别前缀（零分配，对标 Zig std.log / Rust log）
 *
 * 【文件职责】log_write_c(level, ptr, len) 写 "[LEVEL] " + 消息 + 换行到 fd 2；set_min_level_c 过滤。
 * 【性能】无 malloc；单次 write 调用；级别比较在 C 层避免 .su 分支。
 */

#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#define STDERR_FILENO 2
static int log_write_fd(int fd, const void *buf, size_t len) { return (int)_write((int)fd, buf, (unsigned)len); }
#else
#include <unistd.h>
static int log_write_fd(int fd, const void *buf, size_t len) { return (int)write(fd, buf, len); }
#endif

static int32_t s_min_level = 0; /* 0=debug, 1=info, 2=warn, 3=error；仅 >= 的级别才写 */

void log_set_min_level_c(int32_t level) {
  if (level >= 0 && level <= 3) s_min_level = level;
}

/* 级别 0=DEBUG, 1=INFO, 2=WARN, 3=ERROR */
static const char *const level_prefix[] = { "[DEBUG] ", "[INFO] ", "[WARN] ", "[ERROR] " };
static const int level_prefix_len[] = { 8, 7, 7, 8 };

int32_t log_write_c(int32_t level, const uint8_t *ptr, int32_t len) {
  if (level < 0 || level > 3 || ptr == 0) return -1;
  if (level < s_min_level) return 0;
  int pl = level_prefix_len[level];
  if (log_write_fd(STDERR_FILENO, level_prefix[level], (size_t)pl) != pl) return -1;
  if (len > 0 && log_write_fd(STDERR_FILENO, ptr, (size_t)len) != len) return -1;
  if (log_write_fd(STDERR_FILENO, "\n", 1) != 1) return -1;
  return 0;
}
