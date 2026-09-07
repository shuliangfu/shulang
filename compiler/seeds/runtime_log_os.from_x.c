/* seeds/runtime_log_os.from_x.c — G-02f-19 product TU
 * G-02f-112 helper gates.
 * G-02f-105 helper gates.
 * Product: runtime_log_os.o; R2 full mode (wave505).
 *
 * R2 full mode: public API in src/asm/runtime_log_os.x (thin),
 * OS bridge _impl functions here (rest). Thin+rest linked via ld -r.
 * Platform-specific: _write/write for log_write_fd_impl; OS file ops
 * for set_file_sink/close_file_sink.
 *
 * wave252 G.7: XLANG_LOG_MIN_LEVEL via public face link_abi_getenv (not raw getenv).
 * wave253: face body in runtime_link_abi_user_env.o (declaration only here).
 * Cap residual 10.7.2: rotate path format via xlang_snprintf (no libc snprintf).
 * PLATFORM: SHARED
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_user_link_abi_getenv.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: log rotate path → xlang_snprintf */
#include <xlang_io_cap.h>  /* Cap residual 9.1.8: log write fd → xlang_io_write */
/* Cap residual 9.5.3 slice3a: smoke helpers verify log files via
 * xlang_proc_open_ro/xlang_proc_read_file/xlang_proc_close_fd (9.1.12
 * authorities) — no libc fopen/fread/fclose. */
#include <xlang_proc_cap.h>

/* rename is linked from the nostdlib stub provider (bootstrap_nostdlib_stubs
 * defines it on top of the platform syscall face); its usual declarer
 * <stdio.h> was dropped together with the FILE/fread residual above. */
extern int rename(const char *oldpath, const char *newpath);

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#define STDERR_FILENO 2
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#endif

int log_write_fd_impl(int fd, const void *buf, size_t len) { return (int)xlang_io_write(fd, buf, len); }

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int log_write_fd(int fd, const void *buf, size_t len) { return log_write_fd_impl(fd, buf, len); }
#endif

#define LOG_SINK_STDERR 1
#define LOG_SINK_FILE 2

#define LOG_ASYNC_SLOTS 32
#define LOG_ASYNC_SLOT_SIZE 512

typedef struct {
  int32_t length;
  uint8_t data[LOG_ASYNC_SLOT_SIZE];
} log_async_slot_t;

static int32_t s_min_level = 0;
static int32_t s_sink_mask = LOG_SINK_STDERR;
static int s_file_fd = -1;
static int s_env_applied = 0;
static char s_file_path[512];
static int32_t s_file_path_len = 0;
static int64_t s_file_bytes = 0;
static int32_t s_rotate_max_bytes = 0;
static int32_t s_rotate_max_backups = 0;
static int32_t s_async_enabled = 0;
static log_async_slot_t s_async_queue[LOG_ASYNC_SLOTS];
static int32_t s_async_count = 0;

void log_close_file_sink_c(void);
int32_t log_write_sync(const void *buf, size_t len);
int32_t log_async_flush_c(void);

/* Forward declarations of _c public API functions provided by runtime_log_os.x
 * in R2 mode (thin object). In cold path, these are defined locally under
 * #ifndef XLANG_RUNTIME_LOG_OS_FROM_X guards. */
void log_set_min_level_c(int32_t level);
void log_set_sink_mask_c(int32_t mask);
int32_t log_set_file_sink_c(const uint8_t *path, int32_t len);
int32_t log_set_rotate_c(int32_t max_bytes, int32_t max_backups);
int32_t log_set_async_enabled_c(int32_t enabled);

int log_write_fd(int fd, const void *buf, size_t len);
int32_t log_do_rotate(void);
int32_t log_write_file_sync(const void *buf, size_t len);
int32_t log_async_enqueue(const void *buf, size_t len);
void log_apply_env_once(void);
int32_t log_emit_bytes(const void *buf, size_t len);

/** Read XLANG_LOG_MIN_LEVEL env var on first call. */
void log_apply_env_once_impl(void) {
  if (s_env_applied) return;
  s_env_applied = 1;
  const char *v = link_abi_getenv("XLANG_LOG_MIN_LEVEL");
  if (v && v[0]) {
    int l = atoi(v);
    if (l >= 0 && l <= 3) s_min_level = (int32_t)l;
  }
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
void log_apply_env_once(void) {
  log_apply_env_once_impl();
}
#endif

/** Get current min log level (0-3). */
int32_t log_get_min_level_impl(void) {
  return s_min_level;
}

/** Set min log level (0-3). */
void log_set_min_level_impl(int32_t level) {
  if (level >= 0 && level <= 3) s_min_level = level;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
void log_set_min_level_c(int32_t level) {
  if (level >= 0 && level <= 3) s_min_level = level;
}
#endif

/** Set active sink mask (LOG_SINK_STDERR | LOG_SINK_FILE). */
void log_set_sink_mask_impl(int32_t mask) {
  s_sink_mask = mask;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
void log_set_sink_mask_c(int32_t mask) {
  s_sink_mask = mask;
}
#endif

/** Open file sink for append; path[len] need not be NUL-terminated. Returns 0 success, -1 failure. */
int32_t log_set_file_sink_impl(const uint8_t *path, int32_t len) {
  log_close_file_sink_c();
  if (!path || len <= 0) return -1;
  char tmp[512];
  if (len >= (int32_t)sizeof(tmp)) len = (int32_t)sizeof(tmp) - 1;
  memcpy(tmp, path, (size_t)len);
  tmp[len] = 0;
  s_file_path_len = len;
  memcpy(s_file_path, tmp, (size_t)len + 1);
  s_file_bytes = 0;
#if !defined(_WIN32) && !defined(_WIN64)
  {
    struct stat st;
    if (stat(tmp, &st) == 0 && st.st_size > 0) s_file_bytes = (int64_t)st.st_size;
  }
#endif
#if defined(_WIN32) || defined(_WIN64)
  s_file_fd = _open(tmp, _O_WRONLY | _O_CREAT | _O_APPEND | _O_BINARY, _S_IWRITE);
#else
  s_file_fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
  return (s_file_fd >= 0) ? 0 : -1;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_set_file_sink_c(const uint8_t *path, int32_t len) {
  return log_set_file_sink_impl(path, len);
}
#endif

/** Close file sink if open. */
void log_close_file_sink_impl(void) {
  if (s_file_fd >= 0) {
#if defined(_WIN32) || defined(_WIN64)
    _close(s_file_fd);
#else
    close(s_file_fd);
#endif
    s_file_fd = -1;
  }
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
void log_close_file_sink_c(void) {
  log_close_file_sink_impl();
}
#endif

/** Rotate log file when size threshold reached. Returns 0 success, -1 failure. */
int32_t log_do_rotate_impl(void) {
  char oldpath[520];
  char newpath[520];
  int32_t max_b;

  if (s_rotate_max_bytes <= 0 || s_file_path_len <= 0) return 0;
  max_b = s_rotate_max_backups;
  if (max_b < 0) max_b = 0;
  if (max_b > 8) max_b = 8;

  log_close_file_sink_c();

  if (max_b == 0) {
#if defined(_WIN32) || defined(_WIN64)
    s_file_fd = _open(s_file_path, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IWRITE);
#else
    s_file_fd = open(s_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
#endif
  } else {
    xlang_snprintf(oldpath, sizeof(oldpath), "%s.%d", s_file_path, max_b);
#if !defined(_WIN32) && !defined(_WIN64)
    unlink(oldpath);
#endif
    for (int32_t i = max_b - 1; i >= 1; i--) {
      xlang_snprintf(oldpath, sizeof(oldpath), "%s.%d", s_file_path, i);
      xlang_snprintf(newpath, sizeof(newpath), "%s.%d", s_file_path, i + 1);
      rename(oldpath, newpath);
    }
    xlang_snprintf(newpath, sizeof(newpath), "%s.1", s_file_path);
    rename(s_file_path, newpath);
#if defined(_WIN32) || defined(_WIN64)
    s_file_fd = _open(s_file_path, _O_WRONLY | _O_CREAT | _O_APPEND | _O_BINARY, _S_IWRITE);
#else
    s_file_fd = open(s_file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
  }
  s_file_bytes = 0;
  return (s_file_fd >= 0) ? 0 : -1;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_do_rotate(void) {
  return log_do_rotate_impl();
}
#endif

/** Set rotation threshold; must call set_file_sink first. Returns 0 success, -1 failure. */
int32_t log_set_rotate_impl(int32_t max_bytes, int32_t max_backups) {
  if (max_bytes < 0 || max_backups < 0 || max_backups > 8) return -1;
  s_rotate_max_bytes = max_bytes;
  s_rotate_max_backups = max_backups;
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_set_rotate_c(int32_t max_bytes, int32_t max_backups) {
  if (max_bytes < 0 || max_backups < 0 || max_backups > 8) return -1;
  s_rotate_max_bytes = max_bytes;
  s_rotate_max_backups = max_backups;
  return 0;
}
#endif

/** Enable/disable async buffering; flush before disabling. Returns 0 success, -1 failure. */
int32_t log_set_async_enabled_impl(int32_t enabled) {
  if (enabled) {
    s_async_enabled = 1;
    return 0;
  }
  if (s_async_enabled) {
    if (log_async_flush_c() != 0) return -1;
    s_async_enabled = 0;
  }
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_set_async_enabled_c(int32_t enabled) {
  if (enabled) {
    s_async_enabled = 1;
    return 0;
  }
  if (s_async_enabled) {
    if (log_async_flush_c() != 0) return -1;
    s_async_enabled = 0;
  }
  return 0;
}
#endif

/** Flush async buffer to active sinks. Returns 0 success, -1 failure. */
int32_t log_async_flush_impl(void) {
  int32_t i;
  for (i = 0; i < s_async_count; i++) {
    if (log_write_sync(s_async_queue[i].data, (size_t)s_async_queue[i].length) != 0) return -1;
  }
  s_async_count = 0;
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_async_flush_c(void) {
  int32_t i;
  for (i = 0; i < s_async_count; i++) {
    if (log_write_sync(s_async_queue[i].data, (size_t)s_async_queue[i].length) != 0) return -1;
  }
  s_async_count = 0;
  return 0;
}
#endif

/** Write buffer to file sink, with rotation check. Returns 0 success, -1 failure. */
int32_t log_write_file_sync_impl(const void *buf, size_t len) {
  if (!(s_sink_mask & LOG_SINK_FILE) || s_file_fd < 0) return 0;
  if (s_rotate_max_bytes > 0 && s_file_bytes + (int64_t)len > s_rotate_max_bytes) {
    if (log_do_rotate() != 0) return -1;
  }
  if (log_write_fd(s_file_fd, buf, len) != (int)len) return -1;
  s_file_bytes += (int64_t)len;
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_write_file_sync(const void *buf, size_t len) {
  return log_write_file_sync_impl(buf, len);
}
#endif

/** Write buffer to all active sinks (stderr + file). Returns 0 success, -1 failure. */
int32_t log_write_sync_impl(const void *buf, size_t len) {
  if (s_sink_mask & LOG_SINK_STDERR) {
    if (log_write_fd(STDERR_FILENO, buf, len) != (int)len) return -1;
  }
  if (log_write_file_sync(buf, len) != 0) return -1;
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_write_sync(const void *buf, size_t len) {
  return log_write_sync_impl(buf, len);
}
#endif

/** Enqueue buffer in async ring buffer; flush first if full. Returns 0 success, -1 failure. */
int32_t log_async_enqueue_impl(const void *buf, size_t len) {
  if (len > LOG_ASYNC_SLOT_SIZE) return -1;
  if (s_async_count >= LOG_ASYNC_SLOTS) {
    if (log_async_flush_c() != 0) return -1;
    if (s_async_count >= LOG_ASYNC_SLOTS) return -1;
  }
  s_async_queue[s_async_count].length = (int32_t)len;
  memcpy(s_async_queue[s_async_count].data, buf, len);
  s_async_count++;
  return 0;
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_async_enqueue(const void *buf, size_t len) {
  return log_async_enqueue_impl(buf, len);
}
#endif

/** Write buffer: async queue if enabled, else direct write. Returns 0 success, -1 failure. */
int32_t log_emit_bytes_impl(const void *buf, size_t len) {
  if (s_async_enabled) return log_async_enqueue(buf, len);
  return log_write_sync(buf, len);
}

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_emit_bytes(const void *buf, size_t len) {
  return log_emit_bytes_impl(buf, len);
}
#endif

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
void log_apply_env_once_c(void) {
  log_apply_env_once();
}
#endif

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_get_min_level_c(void) {
  log_apply_env_once();
  return s_min_level;
}
#endif

#ifndef XLANG_RUNTIME_LOG_OS_FROM_X
int32_t log_emit_bytes_c(const uint8_t *buf, int32_t len) {
  if (!buf || len <= 0) return -1;
  return log_emit_bytes(buf, (size_t)len);
}
#endif

extern int32_t log_write_c(int32_t level, const uint8_t *ptr, int32_t len);
extern int32_t log_write_structured_kv_c(const uint8_t *component, int32_t level, const uint8_t *kv_body);

/** STD-053 C smoke test: human line + structured line + level filter golden. */
int32_t log_multi_sink_smoke_c(const char *path) {
  const uint8_t msg_ok[] = "sink_ok";
  const uint8_t filtered[] = "filtered";
  char buf[512];

  if (!path) return 1;

  log_set_min_level_c(0);
  log_set_sink_mask_c(LOG_SINK_FILE);
  if (log_set_file_sink_c((const uint8_t *)path, (int32_t)strlen(path)) != 0) return 2;
  if (log_write_c(1, msg_ok, 7) != 0) return 3;
  if (log_write_structured_kv_c((const uint8_t *)"std_log_smoke", 1, (const uint8_t *)"event=smoke") != 0) {
    return 4;
  }
  log_close_file_sink_c();

  /* Cap residual 9.5.3 slice3a: read-back verification via xlang_proc_read_file
   * (whole-file read + NUL + close in one Cap call). */
  if (xlang_proc_read_file(path, buf, sizeof(buf)) < 0) return 5;
  if (!strstr(buf, "[INFO] sink_ok")) return 6;
  if (!strstr(buf, "xlang: level=info component=std_log_smoke")) return 7;

#if !defined(_WIN32) && !defined(_WIN64)
  unlink(path);
#endif
  log_set_min_level_c(2);
  log_set_sink_mask_c(LOG_SINK_FILE);
  if (log_set_file_sink_c((const uint8_t *)path, (int32_t)strlen(path)) != 0) return 8;
  log_write_c(1, filtered, 8);
  if (log_write_c(2, msg_ok, 7) != 0) return 9;
  log_close_file_sink_c();

  if (xlang_proc_read_file(path, buf, sizeof(buf)) < 0) return 10;
#if !defined(_WIN32) && !defined(_WIN64)
  unlink(path);
#endif
  if (strstr(buf, "filtered")) return 11;
  if (!strstr(buf, "[WARN] sink_ok")) return 12;

  log_set_min_level_c(0);
  log_set_sink_mask_c(LOG_SINK_STDERR);
  return 0;
}

/** STD-106 C smoke test: async defer/flush + file rotation golden. */
int32_t log_rotate_async_smoke_c(const char *path) {
  const uint8_t async_msg[] = "async1";
  const uint8_t rotate_msg[] = "rotate_line_xx";
  char path1[520];
  char buf[512];

  if (!path) return 1;

#if !defined(_WIN32) && !defined(_WIN64)
  unlink(path);
#endif
  xlang_snprintf(path1, sizeof(path1), "%s.1", path);
#if !defined(_WIN32) && !defined(_WIN64)
  unlink(path1);
#endif

  log_set_min_level_c(1);
  log_set_sink_mask_c(LOG_SINK_FILE);
  if (log_set_file_sink_c((const uint8_t *)path, (int32_t)strlen(path)) != 0) return 2;

  if (log_set_async_enabled_c(1) != 0) return 3;
  if (log_write_c(1, async_msg, 6) != 0) return 4;

  /* Read is best-effort here: missing file just means "nothing flushed yet". */
  if (xlang_proc_read_file(path, buf, sizeof(buf)) >= 0) {
    if (strstr(buf, "async1")) return 5;
  }

  if (log_async_flush_c() != 0) return 6;

  if (xlang_proc_read_file(path, buf, sizeof(buf)) < 0) return 7;
  if (!strstr(buf, "[INFO] async1")) return 8;

  log_set_async_enabled_c(0);
  if (log_set_rotate_c(48, 1) != 0) return 9;

  {
    int i;
    for (i = 0; i < 5; i++) {
      if (log_write_c(1, rotate_msg, 14) != 0) return 10;
    }
  }
  log_close_file_sink_c();

  if (xlang_proc_read_file(path1, buf, sizeof(buf)) < 0) return 11;
  if (!strstr(buf, "rotate_line_xx")) return 12;

#if !defined(_WIN32) && !defined(_WIN64)
  unlink(path);
  unlink(path1);
#endif
  log_set_rotate_c(0, 0);
  log_set_min_level_c(0);
  log_set_sink_mask_c(LOG_SINK_STDERR);
  return 0;
}