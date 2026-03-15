/**
 * std/compress/compress.c — 压缩封装（P4 可选；zlib / gzip / Brotli，对标 Zig std.compress、Rust flate2）
 *
 * 【文件职责】zlib(deflate/inflate)、gzip、Brotli(.br)；各格式可选编译，未启用为占位返回 -1。
 * 【所属模块/组件】标准库 std.compress；与 std/compress/mod.su 同属一模块。
 */

#include <stdint.h>
#include <stddef.h>

#ifdef SHU_USE_ZLIB
#include <zlib.h>
#endif

#ifdef SHU_USE_BROTLI
#include <brotli/encode.h>
#include <brotli/decode.h>
#endif

/** 压缩：zlib 格式写入 out，返回写入字节数，失败或未启用 zlib 返回 -1。 */
int32_t compress_deflate_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_ZLIB
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  uLongf dest_len = (uLongf)out_cap;
  int ret = compress2(out, &dest_len, in, (uLong)in_len, Z_DEFAULT_COMPRESSION);
  return (ret == Z_OK) ? (int32_t)dest_len : -1;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}

/** 解压：从 in 读 zlib 流，写入 out，返回写入字节数，失败或未启用 zlib 返回 -1。 */
int32_t compress_inflate_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_ZLIB
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  uLongf dest_len = (uLongf)out_cap;
  int ret = uncompress(out, &dest_len, in, (uLong)in_len);
  return (ret == Z_OK) ? (int32_t)dest_len : -1;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}

#ifdef SHU_USE_ZLIB
/* gzip 格式：windowBits=15+16 使 deflate/inflate 使用 gzip 头尾 */
#define GZIP_WBITS (15 + 16)
#endif

/** 压缩为 gzip 格式（.gz）：含 gzip 头与尾，返回写入字节数，失败或未启用 zlib 返回 -1。 */
int32_t compress_gzip_compress_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_ZLIB
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  if (deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, GZIP_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
    return -1;
  strm.avail_in = (uInt)in_len;
  strm.next_in = (z_const Bytef *)in;
  strm.avail_out = (uInt)out_cap;
  strm.next_out = out;
  if (deflate(&strm, Z_FINISH) != Z_STREAM_END) {
    deflateEnd(&strm);
    return -1;
  }
  int32_t written = (int32_t)((uint8_t *)strm.next_out - out);
  deflateEnd(&strm);
  return written;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}

/** 解压 gzip 流，写入 out，返回写入字节数，失败或未启用 zlib 返回 -1。 */
int32_t compress_gzip_decompress_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_ZLIB
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = (uInt)in_len;
  strm.next_in = (z_const Bytef *)in;
  if (inflateInit2(&strm, GZIP_WBITS) != Z_OK) return -1;
  strm.avail_out = (uInt)out_cap;
  strm.next_out = out;
  int ret = inflate(&strm, Z_FINISH);
  int32_t written = (ret == Z_STREAM_END) ? (int32_t)((uint8_t *)strm.next_out - out) : -1;
  inflateEnd(&strm);
  return written;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}

/* ---------- Brotli（.br）：压缩率通常优于 gzip，需 SHU_USE_BROTLI 与 -lbrotlienc -lbrotlidec ---------- */

/** 压缩为 Brotli 格式（.br），返回写入字节数，失败或未启用 Brotli 返回 -1。quality 默认 11。 */
int32_t compress_brotli_compress_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_BROTLI
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  size_t encoded_size = (size_t)out_cap;
  if (!BrotliEncoderCompress(BROTLI_DEFAULT_QUALITY, BROTLI_DEFAULT_WINDOW, BROTLI_DEFAULT_MODE,
                            (size_t)in_len, in, &encoded_size, out))
    return -1;
  return (int32_t)encoded_size;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}

/** 解压 Brotli 流，返回写入字节数，失败或未启用 Brotli 返回 -1。 */
int32_t compress_brotli_decompress_c(const uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
#ifdef SHU_USE_BROTLI
  if (!in || !out || in_len < 0 || out_cap <= 0) return -1;
  size_t decoded_size = (size_t)out_cap;
  if (BrotliDecoderDecompress((size_t)in_len, in, &decoded_size, out) != BROTLI_DECODER_RESULT_SUCCESS)
    return -1;
  return (int32_t)decoded_size;
#else
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
#endif
}
