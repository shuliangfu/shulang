/**
 * std/sort/sort.c — 排序（对标 Zig std.sort、Rust Vec::sort）
 *
 * 【文件职责】
 * sort_i32_c(ptr, len)、sort_u8_c(ptr, len) 原地不稳定排序；内部用 qsort 或手写快排。
 *
 * 【所属模块/组件】
 * 标准库 std.sort；与 std/sort/mod.su 同属一模块。无外部依赖。
 */

#include <stdint.h>
#include <stdlib.h>

static int cmp_i32(const void *a, const void *b) {
  int32_t x = *(const int32_t *)a;
  int32_t y = *(const int32_t *)b;
  if (x < y) return -1;
  if (x > y) return 1;
  return 0;
}

static int cmp_u8(const void *a, const void *b) {
  uint8_t x = *(const uint8_t *)a;
  uint8_t y = *(const uint8_t *)b;
  if (x < y) return -1;
  if (x > y) return 1;
  return 0;
}

/** 原地排序 ptr[0..len]（i32 升序）；不稳定。 */
void sort_i32_c(int32_t *ptr, int32_t len) {
  if (!ptr || len <= 1) return;
  qsort(ptr, (size_t)len, sizeof(int32_t), cmp_i32);
}

/** 原地排序 ptr[0..len]（u8 升序）；不稳定。 */
void sort_u8_c(uint8_t *ptr, int32_t len) {
  if (!ptr || len <= 1) return;
  qsort(ptr, (size_t)len, sizeof(uint8_t), cmp_u8);
}
