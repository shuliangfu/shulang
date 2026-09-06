// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_queue_contention_x_doc_anchor: see function docblock below.

/** Exported function `runtime_queue_contention_x_doc_anchor`.
 * Implements `runtime_queue_contention_x_doc_anchor`.
 * @return i32
 */
export function runtime_queue_contention_x_doc_anchor(): i32 {
  return 0;
}

/* libc bridge declarations. */
export extern "C" function malloc(size: usize): *u8;
export extern "C" function free(ptr: *u8): void;

/* OS bridge declarations — OS-specific _impl functions in runtime_queue_contention.from_x.c.
 * PLATFORM: SHARED Cap — unified xlang_cap_mutex + xlang_thread_spawn/join across
 *           Linux, Darwin, and Windows. */
export extern "C" function queue_os_mutex_create_impl(): *u8;
export extern "C" function queue_os_mutex_destroy_impl(mu: *u8): void;
export extern "C" function queue_os_mutex_lock_impl(mu: *u8): void;
export extern "C" function queue_os_mutex_unlock_impl(mu: *u8): void;
export extern "C" function queue_os_run_two_workers_impl(ctx: *u8): i32;

/** Opaque queue smoke state matching C layout (allow(padding) ensures no extra fields). */
allow(padding) struct QueueSmokeState {
  mu: *u8;
  data: *i32;
  cap: i32;
  length: i32;
  head: i32;
}

/* Public API — thin wrappers that delegate to _impl OS bridges.
 * PLATFORM: SHARED — same public API on all platforms; unified Cap primitives
 *           implemented in the C seed. */

/** Create OS mutex (xlang_cap_mutex). Returns opaque pointer or null. */
#[no_mangle]
export function queue_os_mutex_create_c(): *u8 {
  unsafe { return queue_os_mutex_create_impl(); }
}

/** Destroy OS mutex and free backing memory. */
#[no_mangle]
export function queue_os_mutex_destroy_c(mu: *u8): void {
  unsafe { queue_os_mutex_destroy_impl(mu); }
}

/** Lock OS mutex. Blocks until acquired. */
#[no_mangle]
export function queue_os_mutex_lock_c(mu: *u8): void {
  unsafe { queue_os_mutex_lock_impl(mu); }
}

/** Unlock OS mutex. */
#[no_mangle]
export function queue_os_mutex_unlock_c(mu: *u8): void {
  unsafe { queue_os_mutex_unlock_impl(mu); }
}

/** Launch two OS worker threads and wait for both to complete.
 * Returns 0 on success, -1 on failure. */
#[no_mangle]
export function queue_os_run_two_workers_c(ctx: *u8): i32 {
  unsafe { return queue_os_run_two_workers_impl(ctx); }
}

/** Logical index i -> physical index in circular buffer. */
#[no_mangle]
export function queue_smoke_at_impl(q: *QueueSmokeState, i: i32): i32 {
  let idx: i32 = q.head + i;
  if (idx >= q.cap) {
    idx = idx - q.cap;
  }
  return idx;
}

/** Public wrapper for queue_smoke_at_impl. */
#[no_mangle]
export function queue_smoke_at(q: *QueueSmokeState, i: i32): i32 {
  return queue_smoke_at_impl(q, i);
}

/** Push element to queue back; grows buffer when full. Returns 0 on success, -1 on failure. */
#[no_mangle]
export function queue_smoke_push_back_impl(q: *QueueSmokeState, x: i32): i32 {
  if (q == 0 as *QueueSmokeState) {
    return -1;
  }
  if (q.length >= q.cap) {
    let new_cap: i32 = 8;
    if (q.cap > 0) {
      new_cap = q.cap * 2;
    }
    let p: *i32 = 0 as *i32;
    unsafe {
      p = malloc((new_cap as usize) * 4) as *i32;
    }
    if (p == 0 as *i32) {
      return -1;
    }
    let i: i32 = 0;
    while (i < q.length) {
      p[i] = q.data[queue_smoke_at(q, i)];
      i = i + 1;
    }
    if (q.data != 0 as *i32) {
      unsafe {
        free(q.data as *u8);
      }
    }
    q.data = p;
    q.cap = new_cap;
    q.head = 0;
  }
  q.data[queue_smoke_at(q, q.length)] = x;
  q.length = q.length + 1;
  return 0;
}

/** Public wrapper for queue_smoke_push_back_impl. */
#[no_mangle]
export function queue_smoke_push_back(q: *QueueSmokeState, x: i32): i32 {
  return queue_smoke_push_back_impl(q, x);
}

/** Worker body: push 500 elements under mutex lock. Returns 0 on success, -1 on null ctx. */
#[no_mangle]
export function queue_contention_worker_push_c(ctx: *u8): i32 {
  let q: *QueueSmokeState = ctx as *QueueSmokeState;
  if (q == 0 as *QueueSmokeState) {
    return -1;
  }
  let i: i32 = 0;
  while (i < 500) {
    unsafe {
      queue_os_mutex_lock_c(q.mu);
      queue_smoke_push_back(q, 1);
      queue_os_mutex_unlock_c(q.mu);
    }
    i = i + 1;
  }
  return 0;
}

/** POSIX trampoline body for worker threads.
 *  Note: Windows uses __stdcall trampoline in rest (queue_os_worker_trampoline_win_impl).
 *  On POSIX this .x trampoline satisfies the symbol; on Windows rest provides the
 *  stdcall variant and .x's cdecl variant is a fallback (ld -r merges). */
#[no_mangle]
export function queue_os_worker_trampoline_impl(arg: *u8): *u8 {
  queue_contention_worker_push_c(arg);
  return 0 as *u8;
}

/** Public trampoline wrapper. */
#[no_mangle]
export function queue_os_worker_trampoline(arg: *u8): *u8 {
  return queue_os_worker_trampoline_impl(arg);
}

/** STD-048 sync_queue_contention_smoke_c: dual-thread concurrent push smoke test.
 *  Returns 0 on success (length == 1000), -1 on failure. */
#[no_mangle]
export function sync_queue_contention_smoke_c(): i32 {
  let st: QueueSmokeState = {
    mu: 0 as *u8,
    data: 0 as *i32,
    cap: 0,
    length: 0,
    head: 0,
  };
  let rc: i32 = -1;
  unsafe {
    st.mu = queue_os_mutex_create_c();
  }
  if (st.mu == 0 as *u8) {
    return -1;
  }
  let workers_rc: i32 = 0;
  unsafe {
    workers_rc = queue_os_run_two_workers_c(&st as *u8);
  }
  if (workers_rc != 0) {
    unsafe {
      queue_os_mutex_destroy_c(st.mu);
    }
    if (st.data != 0 as *i32) {
      unsafe {
        free(st.data as *u8);
      }
    }
    return -1;
  }
  if (st.length == 1000) {
    rc = 0;
  }
  if (st.data != 0 as *i32) {
    unsafe {
      free(st.data as *u8);
    }
  }
  unsafe {
    queue_os_mutex_destroy_c(st.mu);
  }
  return rc;
}
