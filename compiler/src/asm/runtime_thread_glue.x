// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_thread_glue.x — R2 full wave513
//
// Thread OS glue: thread_self/create/join/affinity/QoS/name + worker thread pool.
// The actual OS API calls (Linux Cap spawn/join/pool; Darwin pthread_*;
// Windows CreateThread / SetThreadAffinityMask, etc.) are delegated to C
// bridge functions declared below as extern "C". These are implemented in
// seeds/runtime_thread_glue.from_x.c and linked via the product pipeline
// (thin+rest ld -r pattern).
//
// PLATFORM: SHARED — LINUX Cap (futex); Darwin Cap (pthread residual);
//           WINDOWS Cap (CreateThread spawn/join + Win32 pool 10.6.2/10.6.3).
//
// Wave513 (2026-07-27): R2 migration of runtime_thread_glue.from_x.c business
// logic to .x. Previously the .c seed provided all public wrappers; now the
// .x file is the authoritative source and the .c seed only provides _impl
// implementations + forward declarations + marker in FROM_X mode.

/* === C bridge declarations (implemented in runtime_thread_glue.from_x.c) === */

/**
 * Bridge: zero a Linux cpu_set_t bitmap.
 * Linux: memset(set, 0, sizeof(cpu_set_t))
 * Other platforms: no-op (affinity unsupported)
 * @param set pointer to cpu_set_t (cast to *u8 at ABI boundary)
 */
export extern "C" function xlang_cpu_zero_impl(set: *u8): void;

/**
 * Bridge: set a single CPU bit in a Linux cpu_set_t bitmap.
 * Linux: bitmap bit manipulation
 * Other platforms: no-op
 * @param cpu logical CPU index
 * @param set pointer to cpu_set_t
 */
export extern "C" function xlang_cpu_set_impl(cpu: u32, set: *u8): void;

/**
 * Bridge: return current thread ID (pthread_self / GetCurrentThreadId).
 * @return thread ID as i64 (0 = invalid)
 */
export extern "C" function thread_self_impl(): i64;

/**
 * Bridge: spawn a new thread entry(entry, arg).
 * Entry signature matches C void* (*)(void*). Returns thread_id or invalid.
 * @param entry function pointer (entry must not be NULL; caller guarantees)
 * @param arg opaque argument
 * @return thread_id on success; XLANG_THREAD_ID_INVALID (0 or -1) on failure
 */
export extern "C" function thread_create_impl(entry: *u8, arg: *u8): i64;

/**
 * Bridge: spawn a new thread with explicit stack size.
 * @param entry function pointer
 * @param arg opaque argument
 * @param stack_size 0 = OS default, otherwise bytes
 * @return thread_id on success; invalid on failure
 */
export extern "C" function thread_create_with_stack_impl(entry: *u8, arg: *u8, stack_size: u64): i64;

/**
 * Bridge: join a thread (wait for exit + free OS resources).
 * @param thread_id from thread_create_impl
 * @return 0 success; -1 failure (invalid id, already joined)
 */
export extern "C" function thread_join_impl(thread_id: i64): i32;

/**
 * Bridge: bind current thread to a logical CPU (affinity via Cap).
 * Linux: sched_setaffinity(0) / Windows: SetThreadAffinityMask /
 * macOS: unsupported (-1).
 * PLATFORM: SHARED Cap (9.4.6).
 * @param cpu_index logical CPU index (0-based)
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_set_affinity_self_impl(cpu_index: i32): i32;

/**
 * Bridge: bind a specific thread to a logical CPU (affinity via Cap).
 * Linux: sched_setaffinity(child_tid) / Windows: SetThreadAffinityMask /
 * macOS: unsupported (-1).
 * PLATFORM: SHARED Cap (9.4.6).
 * @param thread_id target thread
 * @param cpu_index logical CPU index
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_set_affinity_impl(thread_id: i64, cpu_index: i32): i32;

/**
 * Bridge: set current thread QoS class via Cap.
 * macOS: pthread_set_qos_class_self_np / Linux & Windows: unsupported (-1).
 * PLATFORM: SHARED Cap (9.4.6).
 * @param qos_class 0=default,1=user_interactive,2=user_initiated,3=utility,4=background
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_set_qos_class_self_impl(qos_class: i32): i32;

/**
 * Bridge: set current thread name (Linux pthread_setname_np / macOS pthread_setname_np).
 * @param name name bytes (≤15 bytes)
 * @param len byte length
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_set_name_self_impl(name: *u8, len: i32): i32;

/**
 * Bridge: return address of thread_dummy_entry (C function pointer target).
 * The actual function stays in rest C (Windows __stdcall trampoline uses it).
 * @return function address as uintptr
 */
export extern "C" function thread_dummy_entry_ptr_impl(): u64;

/**
 * Bridge: start fixed-size worker thread pool (non-Windows only).
 * @param workers 1..8
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_pool_start_impl(workers: i32): i32;

/**
 * Bridge: submit a task to the worker thread pool (non-Windows only).
 * @param entry function pointer as uintptr
 * @param arg opaque argument as uintptr
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_pool_submit_impl(entry: u64, arg: u64): i32;

/**
 * Bridge: block until pool queue + in-flight jobs are empty (non-Windows only).
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_pool_drain_impl(): i32;

/**
 * Bridge: stop the worker thread pool, join all workers (non-Windows only).
 * @return 0 success; -1 failure or unsupported
 */
export extern "C" function thread_pool_stop_impl(): i32;

/**
 * Bridge: observe pending jobs (queue + in-flight).
 * @return pending count; -1 if pool not started
 */
export extern "C" function thread_pool_pending_impl(): i32;

/* === Public API (R2 full: thin wrappers in .x, OS calls in rest C) === */

/**
 * Exported function `runtime_thread_glue_x_doc_anchor`.
 * Read path helper for codegen discovery; returns 0.
 * @return i32
 */
export function runtime_thread_glue_x_doc_anchor(): i32 {
  return 0;
}

/**
 * Exported function `xlang_cpu_zero`.
 * Zero a Linux cpu_set_t bitmap. No-op on non-Linux platforms where
 * affinity is unsupported (caller may still call without side effect).
 * @param set cpu_set_t pointer
 */
#[no_mangle]
export function xlang_cpu_zero(set: *u8): void {
  unsafe {
    xlang_cpu_zero_impl(set);
  }
}

/**
 * Exported function `xlang_cpu_set`.
 * Set a single CPU bit in a Linux cpu_set_t bitmap. No-op otherwise.
 * @param cpu logical CPU index
 * @param set cpu_set_t pointer
 */
#[no_mangle]
export function xlang_cpu_set(cpu: u32, set: *u8): void {
  unsafe {
    xlang_cpu_set_impl(cpu, set);
  }
}

/**
 * Exported function `thread_self_c`.
 * Return current thread ID (pthread_self on POSIX / GetCurrentThreadId on Windows).
 * @return thread_id as i64
 */
#[no_mangle]
export function thread_self_c(): i64 {
  unsafe {
    return thread_self_impl();
  }
}

/**
 * Exported function `thread_create_c`.
 * Spawn a new thread running entry(entry, arg). Caller guarantees entry != NULL.
 * @param entry function pointer
 * @param arg opaque argument
 * @return thread_id or XLANG_THREAD_ID_INVALID
 */
#[no_mangle]
export function thread_create_c(entry: *u8, arg: *u8): i64 {
  unsafe {
    return thread_create_impl(entry, arg);
  }
}

/**
 * Exported function `thread_create_with_stack_c`.
 * Spawn a new thread with explicit stack size (0 = OS default).
 * @param entry function pointer
 * @param arg opaque argument
 * @param stack_size bytes
 * @return thread_id or invalid
 */
#[no_mangle]
export function thread_create_with_stack_c(entry: *u8, arg: *u8, stack_size: u64): i64 {
  unsafe {
    return thread_create_with_stack_impl(entry, arg, stack_size);
  }
}

/**
 * Exported function `thread_join_c`.
 * Wait for thread exit and release OS resources.
 * @param thread_id from thread_create_c
 * @return 0 success; -1 failure
 */
#[no_mangle]
export function thread_join_c(thread_id: i64): i32 {
  unsafe {
    return thread_join_impl(thread_id);
  }
}

/**
 * Exported function `thread_set_affinity_self_c`.
 * Bind current thread to a logical CPU. Returns -1 on unsupported platforms.
 * @param cpu_index logical CPU index
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_set_affinity_self_c(cpu_index: i32): i32 {
  if cpu_index < 0 {
    return -1;
  }
  unsafe {
    return thread_set_affinity_self_impl(cpu_index);
  }
}

/**
 * Exported function `thread_set_affinity_c`.
 * Bind a specific thread to a logical CPU. Returns -1 on unsupported platforms.
 * @param thread_id target thread
 * @param cpu_index logical CPU index
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_set_affinity_c(thread_id: i64, cpu_index: i32): i32 {
  if thread_id == 0 || cpu_index < 0 {
    return -1;
  }
  unsafe {
    return thread_set_affinity_impl(thread_id, cpu_index);
  }
}

/**
 * Exported function `thread_set_qos_class_self_c`.
 * Set macOS QoS class. Returns -1 on non-macOS or failure.
 * @param qos_class 0..4
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_set_qos_class_self_c(qos_class: i32): i32 {
  if qos_class < 0 || qos_class > 4 {
    return -1;
  }
  unsafe {
    return thread_set_qos_class_self_impl(qos_class);
  }
}

/**
 * Exported function `thread_set_name_self_c`.
 * Set current thread name (≤15 bytes on Linux/macOS).
 * @param name bytes pointer
 * @param len byte length
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_set_name_self_c(name: *u8, len: i32): i32 {
  if name == 0 || len < 0 {
    return -1;
  }
  unsafe {
    return thread_set_name_self_impl(name, len);
  }
}

/**
 * Exported function `thread_dummy_entry_ptr_c`.
 * Return address of thread_dummy_entry (for pipeline tests).
 * @return function address as uintptr
 */
#[no_mangle]
export function thread_dummy_entry_ptr_c(): u64 {
  unsafe {
    return thread_dummy_entry_ptr_impl();
  }
}

/**
 * Exported function `thread_pool_start_c`.
 * Start fixed worker thread pool (1..8 workers). No-op on Windows (-1).
 * @param workers count
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_pool_start_c(workers: i32): i32 {
  if workers < 1 || workers > 8 {
    return -1;
  }
  unsafe {
    return thread_pool_start_impl(workers);
  }
}

/**
 * Exported function `thread_pool_submit_c`.
 * Submit a task to the worker thread pool (blocking if queue full).
 * No-op on Windows (-1).
 * @param entry function address as uintptr
 * @param arg opaque argument as uintptr
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_pool_submit_c(entry: u64, arg: u64): i32 {
  if entry == 0 {
    return -1;
  }
  unsafe {
    return thread_pool_submit_impl(entry, arg);
  }
}

/**
 * Exported function `thread_pool_drain_c`.
 * Block until pool queue + in-flight jobs are empty. No-op on Windows (-1).
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_pool_drain_c(): i32 {
  unsafe {
    return thread_pool_drain_impl();
  }
}

/**
 * Exported function `thread_pool_stop_c`.
 * Stop the worker thread pool and join workers. No-op on Windows (-1).
 * @return 0 success; -1 failure/unsupported
 */
#[no_mangle]
export function thread_pool_stop_c(): i32 {
  unsafe {
    return thread_pool_stop_impl();
  }
}

/**
 * Exported function `thread_pool_pending_c`.
 * Observe pending jobs (queue + in-flight). Returns -1 if pool not started.
 * @return pending count; -1 not started / unsupported
 */
#[no_mangle]
export function thread_pool_pending_c(): i32 {
  unsafe {
    return thread_pool_pending_impl();
  }
}

/* === std.thread pipeline wrappers (thin-to-thin resolution) === */

/** std.thread glue wrapper → thin thread_self_c. */
#[no_mangle]
export function std_thread_thread_self_c(): i64 {
  return thread_self_c();
}

/** std.thread glue wrapper → thin thread_create_c. */
#[no_mangle]
export function std_thread_thread_create_c(entry: *u8, arg: *u8): i64 {
  return thread_create_c(entry, arg);
}

/** std.thread glue wrapper → thin thread_create_with_stack_c. */
#[no_mangle]
export function std_thread_thread_create_with_stack_c(entry: *u8, arg: *u8, stack_size: u64): i64 {
  return thread_create_with_stack_c(entry, arg, stack_size);
}

/** std.thread glue wrapper → thin thread_join_c. */
#[no_mangle]
export function std_thread_thread_join_c(thread_id: i64): i32 {
  return thread_join_c(thread_id);
}

/** std.thread glue wrapper → thin thread_set_affinity_self_c. */
#[no_mangle]
export function std_thread_thread_set_affinity_self_c(cpu_index: i32): i32 {
  return thread_set_affinity_self_c(cpu_index);
}

/** std.thread glue wrapper → thin thread_set_affinity_c. */
#[no_mangle]
export function std_thread_thread_set_affinity_c(thread_id: i64, cpu_index: i32): i32 {
  return thread_set_affinity_c(thread_id, cpu_index);
}

/** std.thread glue wrapper → thin thread_set_qos_class_self_c. */
#[no_mangle]
export function std_thread_thread_set_qos_class_self_c(qos_class: i32): i32 {
  return thread_set_qos_class_self_c(qos_class);
}

/** std.thread glue wrapper → thin thread_dummy_entry_ptr_c. */
#[no_mangle]
export function std_thread_thread_dummy_entry_ptr_c(): u64 {
  return thread_dummy_entry_ptr_c();
}
