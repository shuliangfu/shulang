/**
 * std/string/string.c — 长字符串快路径：memcmp / 子串查找
 *
 * 【文件职责】
 * 为 std.string 的 StrView 提供大长度时的 C 快路径，减少逐字节循环：
 * - shulang_string_memcmp_c：等价 memcmp，用于 view_eq / view_compare；
 * - shulang_string_memmem_c：在 haystack 中找 needle 首次出现位置，用于 view_find_slice。
 * 调用方（mod.su）在 len >= STRING_LONG_THRESHOLD 时走此前端，短串仍用 .su 循环以省调用开销。
 *
 * 【约定】
 * 所有指针与长度由 .su 保证不越界；n/hay_len/needle_len 可为 0，不做越界访问。
 */

#include <stdint.h>
#include <string.h>  /* memcmp; memmem on GNU/BSD */

#if defined(__linux__) || defined(__APPLE__) || (defined(__BSD__) && __BSD__)
/* GNU/BSD 扩展：memmem；Windows 无，用自实现 */
#define HAVE_MEMMEM 1
#endif

/** 与 memcmp 一致：<0 / 0 / >0；.su 侧 i32。链接时可用 -flto 内联。 */
int32_t shulang_string_memcmp_c(const uint8_t *a, const uint8_t *b, int32_t n) {
  if (n <= 0) return 0;
  int r = memcmp(a, b, (size_t)n);
  if (r < 0) return -1;
  if (r > 0) return 1;
  return 0;
}

/** 比较 a[off..off+n-1] 与 b[0..n-1]，相等返回 0，否则非 0。供 view_ends_with 等使用。链接时可用 -flto 内联。 */
int32_t shulang_string_memcmp_at_c(const uint8_t *a, int32_t off, const uint8_t *b, int32_t n) {
  if (n <= 0) return 0;
  return memcmp(a + (size_t)off, b, (size_t)n);
}

/** 块拷贝 dst[0..n-1] = src[0..n-1]；n<=0 不写。用于 from_slice/append_slice/copy_to/trim 快路径。链接时可用 -flto 内联。 */
void shulang_string_copy_c(uint8_t *dst, const uint8_t *src, int32_t n) {
  if (n <= 0) return;
  memcpy(dst, src, (size_t)n);
}

/** 在 ptr[0..n-1] 中找字节 c 首次出现，返回下标，无则 -1。用于 find_char 长串快路径。链接时可用 -flto 内联。 */
int32_t shulang_string_memchr_c(const uint8_t *ptr, uint8_t c, int32_t n) {
  if (n <= 0) return -1;
  const uint8_t *p = (const uint8_t *)memchr(ptr, (unsigned char)c, (size_t)n);
  if (!p) return -1;
  return (int32_t)(p - ptr);
}

/** 在 ptr[0..n-1] 中找字节 c 最后一次出现，返回下标，无则 -1。便携实现（memrchr 非普适，macOS 无）。 */
int32_t shulang_string_memrchr_c(const uint8_t *ptr, uint8_t c, int32_t n) {
  if (n <= 0) return -1;
  for (int32_t i = n - 1; i >= 0; i--) {
    if (ptr[i] == c) return i;
  }
  return -1;
}

#if !defined(HAVE_MEMMEM)
/** 便携：在 hay[0..hay_len-1] 中找 needle[0..needle_len-1] 首次出现，返回起始下标，无则 -1。needle_len==1 走 memchr 快路径。 */
static int32_t portable_memmem(const uint8_t *hay, int32_t hay_len,
                                const uint8_t *needle, int32_t needle_len) {
  if (needle_len <= 0) return 0;
  if (hay_len < needle_len) return -1;
  if (needle_len == 1) {
    const uint8_t *p = (const uint8_t *)memchr(hay, needle[0], (size_t)hay_len);
    return p ? (int32_t)(p - hay) : -1;
  }
  for (int32_t i = 0; i <= hay_len - needle_len; i++) {
    if (memcmp(hay + i, needle, (size_t)needle_len) == 0)
      return i;
  }
  return -1;
}
#endif

/** 在 hay[0..hay_len-1] 中找 needle[0..needle_len-1] 首次出现，返回起始下标，无则 -1。needle_len==1 统一走 memchr 快路径。 */
int32_t shulang_string_memmem_c(const uint8_t *hay, int32_t hay_len,
                                 const uint8_t *needle, int32_t needle_len) {
  if (needle_len <= 0) return 0;
  if (hay_len < needle_len) return -1;
  if (needle_len == 1) {
    const uint8_t *p = (const uint8_t *)memchr(hay, needle[0], (size_t)hay_len);
    return p ? (int32_t)(p - hay) : -1;
  }
#if defined(HAVE_MEMMEM)
  const void *p = memmem(hay, (size_t)hay_len, needle, (size_t)needle_len);
  if (!p) return -1;
  return (int32_t)((const uint8_t *)p - hay);
#else
  return portable_memmem(hay, hay_len, needle, needle_len);
#endif
}
