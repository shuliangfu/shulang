/**
 * std/hash/hash.c — SipHash-2-4 Hasher（对标 Zig std.hash、Rust std::hash::Hasher）
 *
 * 【文件职责】
 * Hasher 状态：hash_sip_new_c（默认 key）、hash_sip_write_u32/u64/bytes、hash_sip_finish_c、hash_sip_free_c。
 * 算法 SipHash-2-4，64-bit 输出；与 HashMap 等可复用。
 *
 * 【所属模块/组件】
 * 标准库 std.hash；与 std/hash/mod.su 同属一模块。无外部依赖。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void hash_sip_write_bytes_c(void *h, const uint8_t *ptr, int32_t len);

#define ROTL64(x, s) (((x) << (s)) | ((x) >> (64 - (s))))

#define SIPROUND do { \
  v0 += v1; v2 += v3; \
  v1 = ROTL64(v1, 13); v3 = ROTL64(v3, 16); \
  v1 ^= v0; v3 ^= v2; \
  v0 = ROTL64(v0, 32); \
  v2 += v1; v0 += v3; \
  v1 = ROTL64(v1, 17); v3 = ROTL64(v3, 21); \
  v1 ^= v2; v3 ^= v0; \
  v2 = ROTL64(v2, 32); \
} while (0)

typedef struct {
  uint64_t v0, v1, v2, v3;
  uint8_t  buf[8];
  int      buflen;
  uint64_t total_len; /* 已写入总字节数，用于 finish 时编码长度 */
} hash_sip_ctx_t;

static uint64_t read64le(const uint8_t *p) {
  return (uint64_t)p[0] | ((uint64_t)p[1]<<8) | ((uint64_t)p[2]<<16) | ((uint64_t)p[3]<<24)
       | ((uint64_t)p[4]<<32) | ((uint64_t)p[5]<<40) | ((uint64_t)p[6]<<48) | ((uint64_t)p[7]<<56);
}

static void sip_compress(hash_sip_ctx_t *ctx, uint64_t m) {
  uint64_t v0 = ctx->v0, v1 = ctx->v1, v2 = ctx->v2, v3 = ctx->v3;
  v3 ^= m;
  SIPROUND; SIPROUND;
  v0 ^= m;
  ctx->v0 = v0; ctx->v1 = v1; ctx->v2 = v2; ctx->v3 = v3;
}

/** 创建 Hasher 状态；默认 key (0,0)。失败返回 NULL。 */
void *hash_sip_new_c(void) {
  hash_sip_ctx_t *ctx = (hash_sip_ctx_t *)malloc(sizeof(hash_sip_ctx_t));
  if (!ctx) return NULL;
  /* SipHash 初始向量 ^ key (k0=0, k1=0) */
  ctx->v0 = 0x736f6d6570736575ULL;
  ctx->v1 = 0x646f72616e646f6dULL;
  ctx->v2 = 0x6c7967656e657261ULL;
  ctx->v3 = 0x7465646279746573ULL;
  ctx->buflen = 0;
  ctx->total_len = 0;
  return (void *)ctx;
}

/** 写入 4 字节（小端）。 */
void hash_sip_write_u32_c(void *h, uint32_t x) {
  hash_sip_ctx_t *ctx = (hash_sip_ctx_t *)h;
  if (!ctx) return;
  uint8_t b[4];
  b[0] = (uint8_t)(x); b[1] = (uint8_t)(x>>8); b[2] = (uint8_t)(x>>16); b[3] = (uint8_t)(x>>24);
  hash_sip_write_bytes_c(h, b, 4);
}

/** 写入 8 字节（小端）。 */
void hash_sip_write_u64_c(void *h, uint64_t x) {
  hash_sip_ctx_t *ctx = (hash_sip_ctx_t *)h;
  if (!ctx) return;
  uint8_t b[8];
  b[0] = (uint8_t)(x); b[1] = (uint8_t)(x>>8); b[2] = (uint8_t)(x>>16); b[3] = (uint8_t)(x>>24);
  b[4] = (uint8_t)(x>>32); b[5] = (uint8_t)(x>>40); b[6] = (uint8_t)(x>>48); b[7] = (uint8_t)(x>>56);
  hash_sip_write_bytes_c(h, b, 8);
}

/** 写入任意字节。 */
void hash_sip_write_bytes_c(void *h, const uint8_t *ptr, int32_t len) {
  hash_sip_ctx_t *ctx = (hash_sip_ctx_t *)h;
  if (!ctx || !ptr || len <= 0) return;
  ctx->total_len += (uint64_t)len;
  int i = 0;
  if (ctx->buflen > 0) {
    while (ctx->buflen < 8 && i < len) { ctx->buf[ctx->buflen++] = ptr[i++]; }
    if (ctx->buflen == 8) {
      sip_compress(ctx, read64le(ctx->buf));
      ctx->buflen = 0;
    }
  }
  while (i + 8 <= len) {
    sip_compress(ctx, read64le(ptr + i));
    i += 8;
  }
  while (i < len) ctx->buf[ctx->buflen++] = ptr[i++];
}

/** 完成哈希，返回 64-bit 结果；调用后 ctx 仍有效可继续写（如需多次 finish 则需重置或新建）。 */
uint64_t hash_sip_finish_c(void *h) {
  hash_sip_ctx_t *ctx = (hash_sip_ctx_t *)h;
  if (!ctx) return 0;
  uint64_t len_bits = ctx->total_len * 8;
  int i;
  for (i = ctx->buflen; i < 8; i++)
    ctx->buf[i] = (uint8_t)(len_bits >> (i * 8));
  sip_compress(ctx, read64le(ctx->buf));
  {
    uint64_t v0 = ctx->v0, v1 = ctx->v1, v2 = ctx->v2, v3 = ctx->v3;
    v2 ^= 0xff;
    SIPROUND; SIPROUND; SIPROUND; SIPROUND;
    return v0 ^ v1 ^ v2 ^ v3;
  }
}

/** 释放 Hasher 状态。 */
void hash_sip_free_c(void *h) {
  free(h);
}

/** 单次调用：对 ptr[0..len) 做 SipHash-2-4，key 默认 0,0，返回 u64。 */
uint64_t hash_sip_bytes_c(const uint8_t *ptr, int32_t len) {
  void *h = hash_sip_new_c();
  if (!h) return 0;
  hash_sip_write_bytes_c(h, ptr, len);
  uint64_t r = hash_sip_finish_c(h);
  hash_sip_free_c(h);
  return r;
}
