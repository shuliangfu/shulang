/**
 * std/ffi/ffi.c — C 字符串互操作（对标 Zig std.cstr、Rust std::ffi）
 *
 * 【文件职责】
 * cstr_len：NUL 结尾字符串长度；cstring_new：复制 ptr[0..len] 并加 NUL，返回 owned 指针；
 * cstring_free：释放 cstring_new 的指针。
 *
 * 【所属模块/组件】
 * 标准库 std.ffi；与 std/ffi/mod.su 同属一模块。无外部依赖（仅 malloc/free）。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** 返回 NUL 结尾字符串的字节长度（不含 NUL）；ptr 为 0 返回 -1。 */
int32_t ffi_cstr_len_c(const uint8_t *ptr) {
  if (!ptr) return -1;
  const char *s = (const char *)ptr;
  size_t n = strlen(s);
  return (int32_t)(n <= 0x7fffffff ? n : 0x7fffffff);
}

/** 分配 len+1 字节，复制 ptr[0..len] 并写入 NUL；失败返回 0。调用方用 cstring_free 释放。 */
uint8_t *ffi_cstring_new_c(const uint8_t *ptr, int32_t len) {
  if (len < 0) return NULL;
  size_t n = (size_t)len + 1;
  uint8_t *p = (uint8_t *)malloc(n);
  if (!p) return NULL;
  if (ptr && len > 0)
    memcpy(p, ptr, (size_t)len);
  p[len] = 0;
  return p;
}

/** 释放由 cstring_new 返回的指针；ptr 可为 0。 */
void ffi_cstring_free_c(uint8_t *ptr) {
  if (ptr) free(ptr);
}
