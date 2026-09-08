// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_log_os_x_doc_anchor: see function docblock below.

/** Exported function `runtime_log_os_x_doc_anchor`.
 * Implements `runtime_log_os_x_doc_anchor`.
 * @return i32
 */
export function runtime_log_os_x_doc_anchor(): i32 {
  return 0;
}

/* extern bridge declarations — OS-specific _impl functions in runtime_log_os.from_x.c.
 * PLATFORM: SHARED — write_fd uses _write on Windows, write on POSIX;
 *           rotate path format via Cap xlang_snprintf (10.7.2).
 * All other _impl functions delegate to OS or manipulate C static state. */

export extern "C" function log_apply_env_once_impl(): void;
export extern "C" function log_do_rotate_impl(): i32;
export extern "C" function log_write_file_sync_impl(buf: *u8, len: usize): i32;
export extern "C" function log_write_sync_impl(buf: *u8, len: usize): i32;
export extern "C" function log_async_enqueue_impl(buf: *u8, len: usize): i32;
export extern "C" function log_emit_bytes_impl(buf: *u8, len: usize): i32;
export extern "C" function log_write_fd_impl(fd: i32, buf: *u8, len: i32): i32;

export extern "C" function log_get_min_level_impl(): i32;
export extern "C" function log_set_min_level_impl(level: i32): void;
export extern "C" function log_set_sink_mask_impl(mask: i32): void;
export extern "C" function log_set_file_sink_impl(path: *u8, len: i32): i32;
export extern "C" function log_close_file_sink_impl(): void;
export extern "C" function log_set_rotate_impl(max_bytes: i32, max_backups: i32): i32;
export extern "C" function log_set_async_enabled_impl(enabled: i32): i32;
export extern "C" function log_async_flush_impl(): i32;

/* Public API — thin wrappers that delegate to _impl OS bridges or other .x functions.
 * PLATFORM: SHARED — same public API on all platforms; platform-specific logic
 *           isolated in _impl functions in the C seed. */

/** Read XLANG_LOG_MIN_LEVEL env var on first call. */
#[no_mangle]
export function log_apply_env_once(): void {
  unsafe { log_apply_env_once_impl(); }
}

/** Rotate log file when size threshold reached. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_do_rotate(): i32 {
  unsafe { return log_do_rotate_impl(); }
}

/** Write buffer to file sink, with rotation check. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_write_file_sync(buf: *u8, len: usize): i32 {
  unsafe { return log_write_file_sync_impl(buf, len); }
}

/** Write buffer to all active sinks (stderr + file). Returns 0 success, -1 failure. */
#[no_mangle]
export function log_write_sync(buf: *u8, len: usize): i32 {
  unsafe { return log_write_sync_impl(buf, len); }
}

/** Enqueue buffer in async ring buffer. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_async_enqueue(buf: *u8, len: usize): i32 {
  unsafe { return log_async_enqueue_impl(buf, len); }
}

/** Write buffer: async queue if enabled, else direct write. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_emit_bytes(buf: *u8, len: usize): i32 {
  unsafe { return log_emit_bytes_impl(buf, len); }
}

/** Write to file descriptor. Returns bytes written.
 * PLATFORM: SHARED — delegates to _write (Windows) or write (POSIX). */
#[no_mangle]
export function log_write_fd(fd: i32, buf: *u8, len: i32): i32 {
  unsafe { return log_write_fd_impl(fd, buf, len); }
}

/* Public API — thin wrappers that call other .x public functions or _impl state accessors. */

/** Apply env once (convenience bridge for log.x). */
#[no_mangle]
export function log_apply_env_once_c(): void {
  log_apply_env_once();
}

/** Get current min log level (applies env first). */
#[no_mangle]
export function log_get_min_level_c(): i32 {
  log_apply_env_once();
  unsafe { return log_get_min_level_impl(); }
}

/** Emit bytes with null/len validation (convenience bridge). */
#[no_mangle]
export function log_emit_bytes_c(buf: *u8, len: i32): i32 {
  if (buf == null or len <= 0) { return -1; }
  return log_emit_bytes(buf, len as usize);
}

/** Set minimum log level (0-3). */
#[no_mangle]
export function log_set_min_level_c(level: i32): void {
  unsafe { log_set_min_level_impl(level); }
}

/** Set active sink mask (LOG_SINK_STDERR | LOG_SINK_FILE). */
#[no_mangle]
export function log_set_sink_mask_c(mask: i32): void {
  unsafe { log_set_sink_mask_impl(mask); }
}

/** Open file sink for append. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_set_file_sink_c(path: *u8, len: i32): i32 {
  unsafe { return log_set_file_sink_impl(path, len); }
}

/** Close file sink if open. */
#[no_mangle]
export function log_close_file_sink_c(): void {
  unsafe { log_close_file_sink_impl(); }
}

/** Set rotation threshold. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_set_rotate_c(max_bytes: i32, max_backups: i32): i32 {
  unsafe { return log_set_rotate_impl(max_bytes, max_backups); }
}

/** Enable/disable async buffering. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_set_async_enabled_c(enabled: i32): i32 {
  unsafe { return log_set_async_enabled_impl(enabled); }
}

/** Flush async buffer to active sinks. Returns 0 success, -1 failure. */
#[no_mangle]
export function log_async_flush_c(): i32 {
  unsafe { return log_async_flush_impl(); }
}