// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_sync_os_x_doc_anchor: see function docblock below.

/** Exported function `runtime_sync_os_x_doc_anchor`.
 * Implements `runtime_sync_os_x_doc_anchor`.
 * @return i32
 */
export function runtime_sync_os_x_doc_anchor(): i32 {
  return 0;
}

/* extern bridge declarations — OS-specific _impl functions in runtime_sync_os.from_x.c.
 * PLATFORM: SHARED — Windows: CRITICAL_SECTION/SRWLOCK/CONDITION_VARIABLE.
 * LINUX: mutex/cond/rwlock → Cap futex (xlang_sync_cap); cond smoke Cap spawn.
 * DARWIN: mutex/cond/rwlock → Cap pthread (xlang_sync_cap); cond smoke Cap spawn.
 * Other POSIX: pthread mutex/rwlock/cond. */

export extern "C" function sync_mutex_new_impl(): *u8;
export extern "C" function sync_mutex_lock_impl(m: *u8): i32;
export extern "C" function sync_mutex_try_lock_impl(m: *u8): i32;
export extern "C" function sync_mutex_unlock_impl(m: *u8): i32;
export extern "C" function sync_mutex_free_impl(m: *u8): void;

export extern "C" function sync_rwlock_new_impl(): *u8;
export extern "C" function sync_rwlock_read_lock_impl(rw: *u8): i32;
export extern "C" function sync_rwlock_write_lock_impl(rw: *u8): i32;
export extern "C" function sync_rwlock_read_unlock_impl(rw: *u8): i32;
export extern "C" function sync_rwlock_write_unlock_impl(rw: *u8): i32;
export extern "C" function sync_rwlock_free_impl(rw: *u8): void;

export extern "C" function sync_condvar_new_impl(): *u8;
export extern "C" function sync_condvar_wait_impl(cv: *u8, mutex: *u8): i32;
export extern "C" function sync_condvar_signal_impl(cv: *u8): i32;
export extern "C" function sync_condvar_broadcast_impl(cv: *u8): i32;
export extern "C" function sync_condvar_free_impl(cv: *u8): void;

/* Public API — thin wrappers that delegate to _impl OS bridges.
 * PLATFORM: SHARED — same public API on all platforms; platform-specific logic
 *           isolated in _impl functions in the C seed. */

/** Create a new mutex. Returns opaque pointer on success, null on failure. */
#[no_mangle]
export function sync_mutex_new_c(): *u8 {
  unsafe { return sync_mutex_new_impl(); }
}

/** Lock mutex. Blocks until acquired. Returns 0 on success, -1 on failure (e.g. null). */
#[no_mangle]
export function sync_mutex_lock_c(m: *u8): i32 {
  unsafe { return sync_mutex_lock_impl(m); }
}

/** Try-lock mutex. Non-blocking. Returns 0 on success, non-zero if busy or null. */
#[no_mangle]
export function sync_mutex_try_lock_c(m: *u8): i32 {
  unsafe { return sync_mutex_try_lock_impl(m); }
}

/** Unlock mutex. Returns 0 on success, -1 on failure (e.g. null). */
#[no_mangle]
export function sync_mutex_unlock_c(m: *u8): i32 {
  unsafe { return sync_mutex_unlock_impl(m); }
}

/** Destroy and free mutex. Caller must not use m after this call. */
#[no_mangle]
export function sync_mutex_free_c(m: *u8): void {
  unsafe { sync_mutex_free_impl(m); }
}

/** Create a new read-write lock. Returns opaque pointer on success, null on failure. */
#[no_mangle]
export function sync_rwlock_new_c(): *u8 {
  unsafe { return sync_rwlock_new_impl(); }
}

/** Acquire shared (read) lock. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_rwlock_read_lock_c(rw: *u8): i32 {
  unsafe { return sync_rwlock_read_lock_impl(rw); }
}

/** Acquire exclusive (write) lock. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_rwlock_write_lock_c(rw: *u8): i32 {
  unsafe { return sync_rwlock_write_lock_impl(rw); }
}

/** Release shared (read) lock. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_rwlock_read_unlock_c(rw: *u8): i32 {
  unsafe { return sync_rwlock_read_unlock_impl(rw); }
}

/** Release exclusive (write) lock. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_rwlock_write_unlock_c(rw: *u8): i32 {
  unsafe { return sync_rwlock_write_unlock_impl(rw); }
}

/** Destroy and free read-write lock. */
#[no_mangle]
export function sync_rwlock_free_c(rw: *u8): void {
  unsafe { sync_rwlock_free_impl(rw); }
}

/** Create a new condition variable. Returns opaque pointer on success, null on failure. */
#[no_mangle]
export function sync_condvar_new_c(): *u8 {
  unsafe { return sync_condvar_new_impl(); }
}

/** Wait on condition variable while holding mutex. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_condvar_wait_c(cv: *u8, mutex: *u8): i32 {
  unsafe { return sync_condvar_wait_impl(cv, mutex); }
}

/** Wake one waiting thread. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_condvar_signal_c(cv: *u8): i32 {
  unsafe { return sync_condvar_signal_impl(cv); }
}

/** Wake all waiting threads. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function sync_condvar_broadcast_c(cv: *u8): i32 {
  unsafe { return sync_condvar_broadcast_impl(cv); }
}

/** Destroy and free condition variable. */
#[no_mangle]
export function sync_condvar_free_c(cv: *u8): void {
  unsafe { sync_condvar_free_impl(cv); }
}