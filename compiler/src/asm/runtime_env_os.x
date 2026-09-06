// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_env_os.x — R2 public API layer for environment variable OS glue.
// Thin layer: #[no_mangle] wrappers delegate to _impl OS bridges in
// runtime_env_os.from_x.c (rest.o). Pure computation (env_build_key) stays
// here; all OS syscalls remain in C _impl functions.
// PLATFORM: SHARED Cap (9.1.1) — Cap xlang_environ_* convergence (no libc getenv/setenv/unsetenv)
//           is encapsulated in _impl functions.

export extern "C" function env_getenv_c_impl(key: *u8, key_len: i32, out: *u8, out_cap: i32): i32;
export extern "C" function env_getenv_ptr_c_impl(key: *u8, key_len: i32, out_len: *i32): *u8;
export extern "C" function env_getenv_z_c_impl(key_z: *u8, out_len: *i32): *u8;
export extern "C" function env_getenv_exists_c_impl(key: *u8, key_len: i32): i32;
export extern "C" function env_setenv_c_impl(name: *u8, value: *u8, overwrite: i32): i32;
export extern "C" function env_unsetenv_c_impl(name: *u8): i32;
export extern "C" function env_temp_dir_c_impl(out: *u8, out_cap: i32): i32;
export extern "C" function env_iter_count_c_impl(): i32;
export extern "C" function env_iter_at_c_impl(index: i32, key_out: *u8, key_cap: i32, val_out: *u8, val_cap: i32): i32;

/** Exported function `runtime_env_os_x_doc_anchor`.
 * Implements `runtime_env_os_x_doc_anchor`.
 * @return i32
 */
export function runtime_env_os_x_doc_anchor(): i32 {
  return 0;
}

// env_build_key: see function docblock below.

/** Exported function `env_build_key`.
 * Implements `env_build_key`.
 * @param key *u8
 * @param key_len i32
 * @param key_buf *u8
 * @return i32
 */
#[no_mangle]
export function env_build_key(key: *u8, key_len: i32, key_buf: *u8): i32 {
  // ENV_KEY_MAX = 256
  if (key == 0) { return 0 - 1; }
  if (key_buf == 0) { return 0 - 1; }
  if (key_len <= 0) { return 0 - 1; }
  if (key_len >= 256) { return 0 - 1; }
  let i: i32 = 0;
  while (i < key_len) {
    key_buf[i] = key[i];
    i = i + 1;
  }
  key_buf[key_len] = 0;
  return 0;
}

/** Get environment variable value into a caller-provided buffer.
 * Reads env var `key[0..key_len)`, writes value (NUL-terminated) to `out`.
 * @param key environment variable name (raw bytes, not NUL-terminated)
 * @param key_len length of key in bytes
 * @param out output buffer for value (NUL-terminated on success)
 * @param out_cap output buffer capacity in bytes
 * @return bytes written (excluding NUL), or -1 on error/not-found, or needed size if buffer too small
 */
#[no_mangle]
export function env_getenv_c(key: *u8, key_len: i32, out: *u8, out_cap: i32): i32 {
  unsafe {
    return env_getenv_c_impl(key, key_len, out, out_cap);
  }
  return 0;
}

/** Zero-copy getenv: returns read-only pointer to value (NUL-terminated).
 * @param key environment variable name (raw bytes)
 * @param key_len length of key in bytes
 * @param out_len optional: receives value length (excluding NUL)
 * @return pointer to value bytes, or null if not found
 */
#[no_mangle]
export function env_getenv_ptr_c(key: *u8, key_len: i32, out_len: *i32): *u8 {
  unsafe {
    return env_getenv_ptr_c_impl(key, key_len, out_len);
  }
  return 0;
}

/** Zero-copy getenv with NUL-terminated key (avoids key copy).
 * @param key_z NUL-terminated environment variable name
 * @param out_len optional: receives value length (excluding NUL)
 * @return pointer to value bytes, or null if not found
 */
#[no_mangle]
export function env_getenv_z_c(key_z: *u8, out_len: *i32): *u8 {
  unsafe {
    return env_getenv_z_c_impl(key_z, out_len);
  }
  return 0;
}

/** Check if environment variable exists.
 * @param key environment variable name (raw bytes)
 * @param key_len length of key in bytes
 * @return 1 if exists, 0 if not
 */
#[no_mangle]
export function env_getenv_exists_c(key: *u8, key_len: i32): i32 {
  unsafe {
    return env_getenv_exists_c_impl(key, key_len);
  }
  return 0;
}

/** Set environment variable name=value.
 * @param name NUL-terminated variable name
 * @param value NUL-terminated value (null to set empty string)
 * @param overwrite non-zero to overwrite existing value
 * @return 0 on success, -1 on failure
 */
#[no_mangle]
export function env_setenv_c(name: *u8, value: *u8, overwrite: i32): i32 {
  unsafe {
    return env_setenv_c_impl(name, value, overwrite);
  }
  return 0;
}

/** Remove environment variable.
 * @param name NUL-terminated variable name
 * @return 0 on success, -1 on failure
 */
#[no_mangle]
export function env_unsetenv_c(name: *u8): i32 {
  unsafe {
    return env_unsetenv_c_impl(name);
  }
  return 0;
}

/** Get temporary directory path.
 * @param out output buffer (NUL-terminated on success)
 * @param out_cap output buffer capacity
 * @return bytes written (excluding NUL), or -1 on error
 */
#[no_mangle]
export function env_temp_dir_c(out: *u8, out_cap: i32): i32 {
  unsafe {
    return env_temp_dir_c_impl(out, out_cap);
  }
  return 0;
}

/** Count environment variable entries.
 * @return number of entries, or 0 on failure
 */
#[no_mangle]
export function env_iter_count_c(): i32 {
  unsafe {
    return env_iter_count_c_impl();
  }
  return 0;
}

/** Iterate environment variable at given index.
 * @param index zero-based index into environment
 * @param key_out output buffer for key (NUL-terminated)
 * @param key_cap key output buffer capacity
 * @param val_out output buffer for value (NUL-terminated)
 * @param val_cap value output buffer capacity
 * @return 1 on success, 0 if index out of bounds, -1 on error
 */
#[no_mangle]
export function env_iter_at_c(index: i32, key_out: *u8, key_cap: i32, val_out: *u8, val_cap: i32): i32 {
  unsafe {
    return env_iter_at_c_impl(index, key_out, key_cap, val_out, val_cap);
  }
  return 0;
}