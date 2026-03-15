/**
 * std/test/test.c — 测试断言与 runner（对标 Zig std.testing、Rust test）
 *
 * 【文件职责】expect(cond)、expect_eq_i32、expect_ne_i32 返回 0/1；test_run_c(fn) 调用并返回退出码。
 */

#include <stdint.h>

int32_t test_expect_c(int32_t cond) {
  return cond ? 0 : 1;
}

int32_t test_expect_eq_i32_c(int32_t a, int32_t b) {
  return (a == b) ? 0 : 1;
}

int32_t test_expect_eq_u32_c(uint32_t a, uint32_t b) {
  return (a == b) ? 0 : 1;
}

int32_t test_expect_ne_i32_c(int32_t a, int32_t b) {
  return (a != b) ? 0 : 1;
}

/* 调用无参返回 i32 的测试函数，返回其返回值（0=通过，非0=失败）。fn 为函数地址（usize）。 */
int32_t test_run_c(void *fn) {
  if (fn == 0) return -1;
  return ((int32_t (*)(void))fn)();
}
