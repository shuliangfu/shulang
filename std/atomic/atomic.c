/**
 * std/atomic/atomic.c — 原子操作（对标 Rust std::sync::atomic、Zig std.atomic）
 *
 * 【文件职责】load/store、compare_exchange、fetch_add/sub/and/or/xor（i32/u32/i64/u64）；C11 或 __atomic_* 封装。
 * 【Ordering】统一使用 seq_cst（顺序一致性），与平台 C11 / GCC 一致。
 */

#include <stdint.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
#include <stdatomic.h>
#define USE_C11_ATOMICS 1
#else
#define USE_C11_ATOMICS 0
#endif

#if defined(__GNUC__) || defined(__clang__)
#define ATOMIC_LOAD32(p)   __atomic_load_n((p), __ATOMIC_SEQ_CST)
#define ATOMIC_STORE32(p,v) __atomic_store_n((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_LOAD64(p)   __atomic_load_n((p), __ATOMIC_SEQ_CST)
#define ATOMIC_STORE64(p,v) __atomic_store_n((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_CAS32(p,e,d) __atomic_compare_exchange_n((p), (e), (d), 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ATOMIC_FADD32(p,v)  __atomic_fetch_add((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FSUB32(p,v)  __atomic_fetch_sub((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FAND32(p,v)  __atomic_fetch_and((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FOR32(p,v)   __atomic_fetch_or((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FXOR32(p,v)  __atomic_fetch_xor((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FADD64(p,v)  __atomic_fetch_add((p), (v), __ATOMIC_SEQ_CST)
#define ATOMIC_FSUB64(p,v)  __atomic_fetch_sub((p), (v), __ATOMIC_SEQ_CST)
#endif

/* ---------- i32 ---------- */
int32_t atomic_load_i32_c(const int32_t *ptr) {
#if defined(ATOMIC_LOAD32)
  return (int32_t)ATOMIC_LOAD32((int32_t *)ptr);
#elif USE_C11_ATOMICS
  return atomic_load_explicit((const _Atomic int32_t *)ptr, memory_order_seq_cst);
#else
  return *ptr;
#endif
}

void atomic_store_i32_c(int32_t *ptr, int32_t val) {
#if defined(ATOMIC_STORE32)
  ATOMIC_STORE32(ptr, val);
#elif USE_C11_ATOMICS
  atomic_store_explicit((_Atomic int32_t *)ptr, val, memory_order_seq_cst);
#else
  *ptr = val;
#endif
}

int32_t atomic_compare_exchange_i32_c(int32_t *ptr, int32_t *expected, int32_t desired) {
#if defined(ATOMIC_CAS32)
  int32_t e = *expected;
  if (ATOMIC_CAS32(ptr, &e, desired)) return 1;
  *expected = e;
  return 0;
#elif USE_C11_ATOMICS
  int32_t e = *expected;
  if (atomic_compare_exchange_strong_explicit((_Atomic int32_t *)ptr, &e, desired, memory_order_seq_cst, memory_order_seq_cst)) return 1;
  *expected = e;
  return 0;
#else
  if (*ptr == *expected) { *ptr = desired; return 1; }
  *expected = *ptr;
  return 0;
#endif
}

int32_t atomic_fetch_add_i32_c(int32_t *ptr, int32_t delta) {
#if defined(ATOMIC_FADD32)
  return (int32_t)ATOMIC_FADD32(ptr, delta);
#elif USE_C11_ATOMICS
  return atomic_fetch_add_explicit((_Atomic int32_t *)ptr, delta, memory_order_seq_cst);
#else
  int32_t old = *ptr;
  *ptr = old + delta;
  return old;
#endif
}

int32_t atomic_fetch_sub_i32_c(int32_t *ptr, int32_t delta) {
#if defined(ATOMIC_FSUB32)
  return (int32_t)ATOMIC_FSUB32(ptr, delta);
#else
  return atomic_fetch_add_i32_c(ptr, -delta);
#endif
}

/* ---------- u32 ---------- */
uint32_t atomic_load_u32_c(const uint32_t *ptr) {
#if defined(ATOMIC_LOAD32)
  return (uint32_t)ATOMIC_LOAD32((uint32_t *)ptr);
#else
  return *ptr;
#endif
}

void atomic_store_u32_c(uint32_t *ptr, uint32_t val) {
#if defined(ATOMIC_STORE32)
  ATOMIC_STORE32(ptr, val);
#else
  *ptr = val;
#endif
}

int32_t atomic_compare_exchange_u32_c(uint32_t *ptr, uint32_t *expected, uint32_t desired) {
#if defined(__GNUC__) || defined(__clang__)
  uint32_t e = *expected;
  if (__atomic_compare_exchange_n(ptr, &e, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) return 1;
  *expected = e;
  return 0;
#elif USE_C11_ATOMICS
  uint32_t e = *expected;
  if (atomic_compare_exchange_strong_explicit((_Atomic uint32_t *)ptr, &e, desired, memory_order_seq_cst, memory_order_seq_cst)) return 1;
  *expected = e;
  return 0;
#else
  if (*ptr == *expected) { *ptr = desired; return 1; }
  *expected = *ptr;
  return 0;
#endif
}

uint32_t atomic_fetch_add_u32_c(uint32_t *ptr, uint32_t delta) {
#if defined(ATOMIC_FADD32)
  return (uint32_t)ATOMIC_FADD32((uint32_t *)ptr, delta);
#else
  uint32_t old = *ptr;
  *ptr = old + delta;
  return old;
#endif
}

/* ---------- i64 / u64 ---------- */
int64_t atomic_load_i64_c(const int64_t *ptr) {
#if defined(ATOMIC_LOAD64)
  return (int64_t)ATOMIC_LOAD64((int64_t *)ptr);
#else
  return *ptr;
#endif
}

void atomic_store_i64_c(int64_t *ptr, int64_t val) {
#if defined(ATOMIC_STORE64)
  ATOMIC_STORE64(ptr, val);
#else
  *ptr = val;
#endif
}

uint64_t atomic_load_u64_c(const uint64_t *ptr) {
#if defined(ATOMIC_LOAD64)
  return (uint64_t)ATOMIC_LOAD64((uint64_t *)ptr);
#else
  return *ptr;
#endif
}

void atomic_store_u64_c(uint64_t *ptr, uint64_t val) {
#if defined(ATOMIC_STORE64)
  ATOMIC_STORE64(ptr, val);
#else
  *ptr = val;
#endif
}

int64_t atomic_fetch_add_i64_c(int64_t *ptr, int64_t delta) {
#if defined(ATOMIC_FADD64)
  return (int64_t)ATOMIC_FADD64(ptr, delta);
#else
  int64_t old = *ptr;
  *ptr = old + delta;
  return old;
#endif
}
