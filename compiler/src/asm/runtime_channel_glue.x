// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// PLATFORM: SHARED — Cap sync (Linux futex / Darwin pthread / Windows Win32 via xlang_sync_cap).
// Channel sync primitives (mutex/cond) unified across all platforms.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.

export extern "C" function channel_sync_init_impl(c: *u8): i32;
export extern "C" function channel_sync_destroy_impl(c: *u8): void;
export extern "C" function channel_lock_impl(c: *u8): void;
export extern "C" function channel_unlock_impl(c: *u8): void;
export extern "C" function channel_signal_not_empty_impl(c: *u8): void;
export extern "C" function channel_signal_not_full_impl(c: *u8): void;
export extern "C" function channel_broadcast_not_empty_impl(c: *u8): void;
export extern "C" function channel_broadcast_not_full_impl(c: *u8): void;

/** Exported function `runtime_channel_glue_x_doc_anchor`.
 * Implements `runtime_channel_glue_x_doc_anchor`.
 * @return i32
 */
export function runtime_channel_glue_x_doc_anchor(): i32 {
  return 0;
}

/* See implementation. */

#[no_mangle]
export function channel_sync_init(c: *u8): i32 {
  unsafe { return channel_sync_init_impl(c); }
  return 0;
}

/** Exported function `channel_sync_destroy`.
 * Implements `channel_sync_destroy`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_sync_destroy(c: *u8): void {
  unsafe { channel_sync_destroy_impl(c); }
}

/** Exported function `channel_lock`.
 * Implements `channel_lock`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_lock(c: *u8): void {
  unsafe { channel_lock_impl(c); }
}

/** Exported function `channel_unlock`.
 * Implements `channel_unlock`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_unlock(c: *u8): void {
  unsafe { channel_unlock_impl(c); }
}

/** Exported function `channel_signal_not_empty`.
 * Implements `channel_signal_not_empty`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_signal_not_empty(c: *u8): void {
  unsafe { channel_signal_not_empty_impl(c); }
}

/** Exported function `channel_signal_not_full`.
 * Implements `channel_signal_not_full`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_signal_not_full(c: *u8): void {
  unsafe { channel_signal_not_full_impl(c); }
}

/** Exported function `channel_broadcast_not_empty`.
 * Implements `channel_broadcast_not_empty`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_broadcast_not_empty(c: *u8): void {
  unsafe { channel_broadcast_not_empty_impl(c); }
}

/** Exported function `channel_broadcast_not_full`.
 * Implements `channel_broadcast_not_full`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_broadcast_not_full(c: *u8): void {
  unsafe { channel_broadcast_not_full_impl(c); }
}

export extern "C" function channel_wait_not_empty_impl(c: *u8): void;
export extern "C" function channel_wait_not_full_impl(c: *u8): void;
export extern "C" function channel_timedwait_not_empty_impl(c: *u8, ms: i32): void;
export extern "C" function channel_timedwait_not_full_impl(c: *u8, ms: i32): void;
export extern "C" function channel_unbounded_grow_impl(c: *u8): i32;
export extern "C" function channel_select_recv_case_live_impl(c: *u8): i32;
export extern "C" function channel_select_send_case_live_impl(c: *u8): i32;
export extern "C" function channel_select_wait_recv_one_impl(c: *u8): void;
export extern "C" function channel_select_wait_send_one_impl(c: *u8): void;

/* See implementation. */

#[no_mangle]
export function channel_wait_not_empty(c: *u8): void { unsafe { channel_wait_not_empty_impl(c); } }

/** Exported function `channel_wait_not_full`.
 * Implements `channel_wait_not_full`.
 * @param c *u8): void { unsafe { channel_wait_not_full_impl(c
 * @return void
 */
#[no_mangle]
export function channel_wait_not_full(c: *u8): void { unsafe { channel_wait_not_full_impl(c); } }

/** Exported function `channel_timedwait_not_empty`.
 * Implements `channel_timedwait_not_empty`.
 * @param c *u8
 * @param ms i32
 * @return void
 */
#[no_mangle]
export function channel_timedwait_not_empty(c: *u8, ms: i32): void {
  unsafe { channel_timedwait_not_empty_impl(c, ms); }
}

/** Exported function `channel_timedwait_not_full`.
 * Implements `channel_timedwait_not_full`.
 * @param c *u8
 * @param ms i32
 * @return void
 */
#[no_mangle]
export function channel_timedwait_not_full(c: *u8, ms: i32): void {
  unsafe { channel_timedwait_not_full_impl(c, ms); }
}

/** Exported function `channel_unbounded_grow`.
 * Implements `channel_unbounded_grow`.
 * @param c *u8
 * @return i32
 */
#[no_mangle]
export function channel_unbounded_grow(c: *u8): i32 {
  unsafe { return channel_unbounded_grow_impl(c); }
  return 0;
}

/** Exported function `channel_select_recv_case_live`.
 * Implements `channel_select_recv_case_live`.
 * @param c *u8
 * @return i32
 */
#[no_mangle]
export function channel_select_recv_case_live(c: *u8): i32 {
  unsafe { return channel_select_recv_case_live_impl(c); }
  return 0;
}

/** Exported function `channel_select_send_case_live`.
 * Implements `channel_select_send_case_live`.
 * @param c *u8
 * @return i32
 */
#[no_mangle]
export function channel_select_send_case_live(c: *u8): i32 {
  unsafe { return channel_select_send_case_live_impl(c); }
  return 0;
}

/** Exported function `channel_select_wait_recv_one`.
 * Implements `channel_select_wait_recv_one`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_select_wait_recv_one(c: *u8): void {
  unsafe { channel_select_wait_recv_one_impl(c); }
}

/** Exported function `channel_select_wait_send_one`.
 * Implements `channel_select_wait_send_one`.
 * @param c *u8
 * @return void
 */
#[no_mangle]
export function channel_select_wait_send_one(c: *u8): void {
  unsafe { channel_select_wait_send_one_impl(c); }
}
