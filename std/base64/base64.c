/**
 * std/base64/base64.c — Base64 编解码（标准/URL 变体，单遍无分配，性能压榨）
 *
 * 【文件职责】encode/decode standard 与 URL 变体；单遍、静态表、无 malloc。对标 Zig std.base64。
 */

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__) || defined(__clang__)
#define B64_HOT __attribute__((hot))
#define B64_LIKELY(x)   __builtin_expect(!!(x), 1)
#define B64_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define B64_HOT
#define B64_LIKELY(x)   (x)
#define B64_UNLIKELY(x) (x)
#endif

static const char b64_std_tbl[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char b64_url_tbl[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

/* 标准解码表：0..63 -> 值，255 -> 非法/填充；'=' 视为 254 在逻辑中处理 */
static uint8_t b64_std_dec[256];
static uint8_t b64_url_dec[256];
static int b64_tables_init = 0;

static void b64_init_tables(void) {
  if (b64_tables_init) return;
  for (int i = 0; i < 256; i++) { b64_std_dec[i] = 255; b64_url_dec[i] = 255; }
  for (int i = 0; i < 64; i++) {
    b64_std_dec[(unsigned char)b64_std_tbl[i]] = (uint8_t)i;
    b64_url_dec[(unsigned char)b64_url_tbl[i]] = (uint8_t)i;
  }
  b64_std_dec['='] = 254;
  b64_url_dec['='] = 254;
  b64_tables_init = 1;
}

/* 编码：src_len 字节 -> (src_len+2)/3*4 字节（标准含填充）。返回写入字节数，缓冲区不足返回 -1。 */
B64_HOT
int32_t base64_encode_standard_c(const uint8_t * restrict src, int32_t src_len, uint8_t * restrict out, int32_t out_cap) {
  if (B64_UNLIKELY(src == 0 || out == 0 || out_cap < 0)) return -1;
  int32_t need = (src_len + 2) / 3 * 4;
  if (out_cap < need) return -1;
  const uint8_t *s = src;
  const uint8_t *end = src + (size_t)src_len;
  uint8_t *o = out;
  while ((size_t)(end - s) >= 3) {
    uint32_t v = (uint32_t)s[0] << 16 | (uint32_t)s[1] << 8 | (uint32_t)s[2];
    o[0] = (uint8_t)b64_std_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_std_tbl[(v >> 12) & 63];
    o[2] = (uint8_t)b64_std_tbl[(v >> 6) & 63];
    o[3] = (uint8_t)b64_std_tbl[v & 63];
    s += 3; o += 4;
  }
  size_t rem = (size_t)(end - s);
  if (rem == 1) {
    uint32_t v = (uint32_t)s[0] << 16;
    o[0] = (uint8_t)b64_std_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_std_tbl[(v >> 12) & 63];
    o[2] = '=';
    o[3] = '=';
    o += 4;
  } else if (rem == 2) {
    uint32_t v = (uint32_t)s[0] << 16 | (uint32_t)s[1] << 8;
    o[0] = (uint8_t)b64_std_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_std_tbl[(v >> 12) & 63];
    o[2] = (uint8_t)b64_std_tbl[(v >> 6) & 63];
    o[3] = '=';
    o += 4;
  }
  return (int32_t)(o - out);
}

B64_HOT
int32_t base64_encode_url_c(const uint8_t * restrict src, int32_t src_len, uint8_t * restrict out, int32_t out_cap) {
  if (B64_UNLIKELY(src == 0 || out == 0 || out_cap < 0)) return -1;
  int32_t need = (src_len + 2) / 3 * 4;
  if (src_len % 3 != 0) need -= (3 - (src_len % 3)); /* URL 无填充 */
  if (out_cap < need) return -1;
  const uint8_t *s = src;
  const uint8_t *end = src + (size_t)src_len;
  uint8_t *o = out;
  while ((size_t)(end - s) >= 3) {
    uint32_t v = (uint32_t)s[0] << 16 | (uint32_t)s[1] << 8 | (uint32_t)s[2];
    o[0] = (uint8_t)b64_url_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_url_tbl[(v >> 12) & 63];
    o[2] = (uint8_t)b64_url_tbl[(v >> 6) & 63];
    o[3] = (uint8_t)b64_url_tbl[v & 63];
    s += 3; o += 4;
  }
  size_t rem = (size_t)(end - s);
  if (rem == 1) {
    uint32_t v = (uint32_t)s[0] << 16;
    o[0] = (uint8_t)b64_url_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_url_tbl[(v >> 12) & 63];
    o += 2;
  } else if (rem == 2) {
    uint32_t v = (uint32_t)s[0] << 16 | (uint32_t)s[1] << 8;
    o[0] = (uint8_t)b64_url_tbl[(v >> 18) & 63];
    o[1] = (uint8_t)b64_url_tbl[(v >> 12) & 63];
    o[2] = (uint8_t)b64_url_tbl[(v >> 6) & 63];
    o += 3;
  }
  return (int32_t)(o - out);
}

/* 解码：返回写入 out 的字节数，非法输入返回 -1。 */
B64_HOT
int32_t base64_decode_standard_c(const uint8_t * restrict src, int32_t src_len, uint8_t * restrict out, int32_t out_cap) {
  if (B64_UNLIKELY(src == 0 || out == 0)) return -1;
  b64_init_tables();
  if (src_len % 4 != 0) return -1;
  int32_t out_len = (src_len / 4) * 3;
  if (src_len >= 1 && src[src_len - 1] == '=') { out_len--; if (src_len >= 2 && src[src_len - 2] == '=') out_len--; }
  if (out_cap < out_len) return -1;
  const uint8_t *s = src;
  uint8_t *o = out;
  const uint8_t *end = src + (size_t)src_len;
  for (; (size_t)(end - s) >= 4; s += 4) {
    uint8_t a = b64_std_dec[s[0]], b = b64_std_dec[s[1]], c = b64_std_dec[s[2]], d = b64_std_dec[s[3]];
    if (a == 255 || b == 255) return -1;
    if (c == 254) c = 0;
    if (d == 254) d = 0;
    if (c == 255 || d == 255) return -1;
    o[0] = (uint8_t)((a << 2) | (b >> 4));
    if (s[2] == '=') { o += 1; return out_len; }
    o[1] = (uint8_t)((b << 4) | (c >> 2));
    if (s[3] == '=') { o += 2; return out_len; }
    o[2] = (uint8_t)((c << 6) | d);
    o += 3;
  }
  return (int32_t)(o - out);
}

B64_HOT
int32_t base64_decode_url_c(const uint8_t * restrict src, int32_t src_len, uint8_t * restrict out, int32_t out_cap) {
  if (B64_UNLIKELY(src == 0 || out == 0)) return -1;
  b64_init_tables();
  int32_t out_len = (src_len * 3) / 4;
  if (src_len % 4 == 1) return -1;
  if (src_len % 4 != 0) out_len = (src_len * 3) / 4 + (src_len % 4) - 1; /* 无填充时余 2/3 字符 */
  if (out_len < 0 || out_cap < out_len) return -1;
  const uint8_t *s = src;
  uint8_t *o = out;
  const uint8_t *end = src + (size_t)src_len;
  while ((size_t)(end - s) >= 4) {
    uint8_t a = b64_url_dec[s[0]], b = b64_url_dec[s[1]], c = b64_url_dec[s[2]], d = b64_url_dec[s[3]];
    if (a == 255 || b == 255) return -1;
    if (c == 255) c = 0;
    if (d == 255) d = 0;
    o[0] = (uint8_t)((a << 2) | (b >> 4));
    o[1] = (uint8_t)((b << 4) | (c >> 2));
    o[2] = (uint8_t)((c << 6) | d);
    s += 4; o += 3;
  }
  if ((size_t)(end - s) == 2) {
    uint8_t a = b64_url_dec[s[0]], b = b64_url_dec[s[1]];
    if (a == 255 || b == 255) return -1;
    o[0] = (uint8_t)((a << 2) | (b >> 4));
    o += 1;
  } else if ((size_t)(end - s) == 3) {
    uint8_t a = b64_url_dec[s[0]], b = b64_url_dec[s[1]], c = b64_url_dec[s[2]];
    if (a == 255 || b == 255 || c == 255) return -1;
    o[0] = (uint8_t)((a << 2) | (b >> 4));
    o[1] = (uint8_t)((b << 4) | (c >> 2));
    o += 2;
  } else if ((size_t)(end - s) != 0) return -1;
  return (int32_t)(o - out);
}
