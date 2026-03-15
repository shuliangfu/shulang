/**
 * std/heap/heap.c — 堆分配：malloc / free / realloc / calloc 薄封装
 *
 * 【文件职责】
 * 为 std.heap 提供与 libc 一致的堆分配接口，供 std.vec、std.map 等使用。
 * 所有函数对 .su 通过 extern 暴露；指针与大小由调用方保证合法。
 *
 * 【约定】
 * - 分配失败返回 NULL；free(NULL) 不操作；realloc(ptr, 0) 等价于 free(ptr) 并返回 NULL。
 * - alloc_zeroed 等价于 calloc(1, size)，即分配并清零。
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** 分配 size 字节，未初始化；失败返回 NULL。对应 Zig allocator.alloc、Rust alloc、Go 底层。 */
void *heap_alloc_c(size_t size) {
  if (size == 0) return NULL;
  return malloc(size);
}

/** 释放 ptr；ptr 可为 NULL（无操作）。 */
void heap_free_c(void *ptr) {
  if (ptr) free(ptr);
}

/** 分配 count 个 int32_t，未初始化；失败返回 NULL。供 std.vec Vec_i32 等使用。 */
int32_t *heap_alloc_i32_c(int32_t count) {
  if (count <= 0) return NULL;
  return (int32_t *)malloc((size_t)count * sizeof(int32_t));
}

/** 将 ptr 调整为 new_count 个 int32_t；失败返回 NULL 且原 ptr 未释放。 */
int32_t *heap_realloc_i32_c(int32_t *ptr, int32_t new_count) {
  if (new_count <= 0) {
    if (ptr) free(ptr);
    return NULL;
  }
  return (int32_t *)realloc(ptr, (size_t)new_count * sizeof(int32_t));
}

/** 释放由 heap_alloc_i32_c / heap_realloc_i32_c 分配的 ptr；ptr 可为 NULL。 */
void heap_free_i32_c(int32_t *ptr) {
  if (ptr) free(ptr);
}

/** 分配 count 个 uint8_t，未初始化；失败返回 NULL。供 std.vec Vec_u8 等使用。 */
uint8_t *heap_alloc_u8_c(int32_t count) {
  if (count <= 0) return NULL;
  return (uint8_t *)malloc((size_t)count * sizeof(uint8_t));
}

/** 将 ptr 调整为 new_count 个 uint8_t；失败返回 NULL 且原 ptr 未释放。 */
uint8_t *heap_realloc_u8_c(uint8_t *ptr, int32_t new_count) {
  if (new_count <= 0) {
    if (ptr) free(ptr);
    return NULL;
  }
  return (uint8_t *)realloc(ptr, (size_t)new_count * sizeof(uint8_t));
}

/** 释放由 heap_alloc_u8_c / heap_realloc_u8_c 分配的 ptr；ptr 可为 NULL。 */
void heap_free_u8_c(uint8_t *ptr) {
  if (ptr) free(ptr);
}

/** 将 ptr 调整为 new_size 字节，可能移动块；失败返回 NULL 且原 ptr 未释放。new_size==0 等价于 free 并返回 NULL。 */
void *heap_realloc_c(void *ptr, size_t new_size) {
  if (new_size == 0) {
    if (ptr) free(ptr);
    return NULL;
  }
  return realloc(ptr, new_size);
}

/** 分配 size 字节并清零（calloc 语义）；失败返回 NULL。 */
void *heap_alloc_zeroed_c(size_t size) {
  if (size == 0) return NULL;
  return calloc(1, size);
}

/** 块拷贝：dst[dst_offset..dst_offset+count-1] = src[0..count-1]（按 i32 元素）；count<=0 不写。供 std.vec append_slice/from_slice 快路径。 */
void heap_copy_i32_at_c(int32_t *dst, int32_t dst_offset, const int32_t *src, int32_t count) {
  if (count <= 0) return;
  memcpy(dst + dst_offset, src, (size_t)count * sizeof(int32_t));
}

/** 块拷贝：dst[dst_offset..dst_offset+count-1] = src[0..count-1]（按 u8 元素）；count<=0 不写。 */
void heap_copy_u8_at_c(uint8_t *dst, int32_t dst_offset, const uint8_t *src, int32_t count) {
  if (count <= 0) return;
  memcpy(dst + dst_offset, src, (size_t)count);
}

/** std.map 查找快路径：在 keys/occupied 中线性探测找 key；存在返回下标，否则 -1。与 .su map_i32_i32_slot 一致。 */
static inline int32_t map_slot(int32_t key, int32_t cap) {
  int32_t h = key % cap;
  return h < 0 ? h + cap : h;
}

int32_t map_i32_i32_find_c(const int32_t *keys, const uint8_t *occupied, int32_t cap, int32_t key) {
  if (cap <= 0) return -1;
  int32_t start = map_slot(key, cap);
  int32_t i = start;
  for (;;) {
    if (occupied[i] == 0) return -1;
    if (keys[i] == key) return i;
    i++;
    if (i >= cap) i = 0;
    if (i == start) return -1;
  }
}

/** 供 codegen 生成的 C 调用（模块前缀 std_heap_）；转发到 map_i32_i32_find_c。 */
int32_t std_heap_map_i32_i32_find_c(const int32_t *keys, const uint8_t *occupied, int32_t cap, int32_t key) {
  return map_i32_i32_find_c(keys, occupied, cap, key);
}

/** std.mem 用：将 ptr[0..n-1] 置为 byte；n<=0 不写。对标 Zig std.mem.set、Rust ptr::write_bytes。 */
void heap_mem_set_c(uint8_t *ptr, uint8_t byte, int32_t n) {
  if (n <= 0) return;
  (void)memset(ptr, (unsigned char)byte, (size_t)n);
}

/** std.mem 用：比较 a[0..n-1] 与 b[0..n-1]；返回 <0 / 0 / >0。对标 Zig std.mem.compare、Rust/Golang bytes.Compare。 */
int32_t heap_mem_compare_c(const uint8_t *a, const uint8_t *b, int32_t n) {
  if (n <= 0) return 0;
  int r = memcmp(a, b, (size_t)n);
  if (r < 0) return -1;
  if (r > 0) return 1;
  return 0;
}
