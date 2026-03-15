/**
 * std/crypto/crypto.c — 常量时间比较、SHA-256/512、HMAC（性能压榨，对标 Zig std.crypto）
 *
 * 【文件职责】mem_eq（常量时间）；SHA-256/512；HMAC-SHA256。无外部依赖，单文件。ChaCha20-Poly1305 占位。
 * 【性能】restrict、热路径内联、SHA 块循环展开友好。
 */

#include <stdint.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#define CRYPTO_HOT  __attribute__((hot))
#define CRYPTO_PURE __attribute__((pure))
#else
#define CRYPTO_HOT
#define CRYPTO_PURE
#endif

/* ---------- 常量时间比较 ---------- */
CRYPTO_PURE
int32_t crypto_mem_eq_c(const uint8_t * restrict a, const uint8_t * restrict b, int32_t len) {
  if (a == 0 || b == 0) return (a == b) ? 1 : 0;
  uint8_t diff = 0;
  for (int32_t i = 0; i < len; i++)
    diff |= a[i] ^ b[i];
  return diff == 0 ? 1 : 0;
}

/* ---------- SHA-256 (FIPS 180-4) ---------- */
static const uint32_t K256[64] = {
  0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
  0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
  0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
  0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
  0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
  0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
  0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
  0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u,
};

#define ROTR32(x,n) (((x) >> (n)) | ((x) << (32 - (n))))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTR32(x,2) ^ ROTR32(x,13) ^ ROTR32(x,22))
#define SIG1(x) (ROTR32(x,6) ^ ROTR32(x,11) ^ ROTR32(x,25))
#define GAM0(x) (ROTR32(x,7) ^ ROTR32(x,18) ^ ((x) >> 3))
#define GAM1(x) (ROTR32(x,17) ^ ROTR32(x,19) ^ ((x) >> 10))

static void sha256_block(uint32_t * restrict H, const uint8_t * restrict block) {
  uint32_t W[64];
  int i;
  for (i = 0; i < 16; i++)
    W[i] = ((uint32_t)block[i*4]<<24)|((uint32_t)block[i*4+1]<<16)|((uint32_t)block[i*4+2]<<8)|(uint32_t)block[i*4+3];
  for (i = 16; i < 64; i++)
    W[i] = GAM1(W[i-2]) + W[i-7] + GAM0(W[i-15]) + W[i-16];
  uint32_t a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
  for (i = 0; i < 64; i++) {
    uint32_t T1 = h + SIG1(e) + CH(e,f,g) + K256[i] + W[i];
    uint32_t T2 = SIG0(a) + MAJ(a,b,c);
    h = g; g = f; f = e; e = d + T1; d = c; c = b; b = a; a = T1 + T2;
  }
  H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;
}

CRYPTO_HOT
void crypto_sha256_c(const uint8_t * restrict msg, int32_t len, uint8_t * restrict out) {
  uint32_t H[8] = { 0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au, 0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u };
  uint8_t block[64];
  uint64_t total_bits = (uint64_t)len * 8;
  const uint8_t *p = msg;
  while (len >= 64) {
    sha256_block(H, p);
    p += 64; len -= 64;
  }
  memcpy(block, p, (size_t)len);
  block[len++] = 0x80;
  if (len > 56) {
    while (len < 64) block[len++] = 0;
    sha256_block(H, block);
    len = 0;
    memset(block, 0, 56);
  } else
    while (len < 56) block[len++] = 0;
  block[56] = (uint8_t)(total_bits >> 56); block[57] = (uint8_t)(total_bits >> 48);
  block[58] = (uint8_t)(total_bits >> 40); block[59] = (uint8_t)(total_bits >> 32);
  block[60] = (uint8_t)(total_bits >> 24); block[61] = (uint8_t)(total_bits >> 16);
  block[62] = (uint8_t)(total_bits >> 8);  block[63] = (uint8_t)total_bits;
  sha256_block(H, block);
  for (int i = 0; i < 8; i++) {
    out[i*4]   = (uint8_t)(H[i] >> 24);
    out[i*4+1] = (uint8_t)(H[i] >> 16);
    out[i*4+2] = (uint8_t)(H[i] >> 8);
    out[i*4+3] = (uint8_t)H[i];
  }
}

/* ---------- SHA-512 ---------- */
static const uint64_t K512[80] = {
  0x428a2f98d728ae22ULL,0x7137449123ef65cdULL,0xb5c0fbcfec4d3b2fULL,0xe9b5dba58189dbbcULL,
  0x3956c25bf348b538ULL,0x59f111f1b605d019ULL,0x923f82a4af194f9bULL,0xab1c5ed5da6d8118ULL,
  0xd807aa98a3030242ULL,0x12835b0145706fbeULL,0x243185be4ee4b28cULL,0x550c7dc3d5ffb4e2ULL,
  0x72be5d74f27b896fULL,0x80deb1fe3b1696b1ULL,0x9bdc06a725c71235ULL,0xc19bf174cf692694ULL,
  0xe49b69c19ef14ad2ULL,0xefbe4786384f25e3ULL,0x0fc19dc68b8cd5b5ULL,0x240ca1cc77ac9c65ULL,
  0x2de92c6f592b0275ULL,0x4a7484aa6ea6e483ULL,0x5cb0a9dcbd41fbd4ULL,0x76f988da831153b5ULL,
  0x983e5152ee66dfabULL,0xa831c66d2db43210ULL,0xb00327c898fb213fULL,0xbf597fc7beef0ee4ULL,
  0xc6e00bf33da88fc2ULL,0xd5a79147930aa725ULL,0x06ca6351e003826fULL,0x142929670a0e6e70ULL,
  0x27b70a8546d22ffcULL,0x2e1b21385c26c926ULL,0x4d2c6dfc5ac42aedULL,0x53380d139d95b3dfULL,
  0x650a73548baf63deULL,0x766a0abb3c77b2a8ULL,0x81c2c92e47edaee6ULL,0x92722c851482353bULL,
  0xa2bfe8a14cf10364ULL,0xa81a664bbc423001ULL,0xc24b8b70d0f89791ULL,0xc76c51a30654be30ULL,
  0xd192e819d6ef5218ULL,0xd69906245565a910ULL,0xf40e35855771202aULL,0x106aa07032bbd1b8ULL,
  0x19a4c116b8d2d0c8ULL,0x1e376c085141ab53ULL,0x2748774cdf8eeb99ULL,0x34b0bcb5e19b48a8ULL,
  0x391c0cb3c5c95a63ULL,0x4ed8aa4ae3418acbULL,0x5b9cca4f7763e373ULL,0x682e6ff3d6b2b8a3ULL,
  0x748f82ee5defb2fcULL,0x78a5636f43172f60ULL,0x84c87814a1f0ab72ULL,0x8cc702081a6439ecULL,
  0x90befffa23631e28ULL,0xa4506cebde82bde9ULL,0xbef9a3f7b2c67915ULL,0xc67178f2e372532bULL,
  0xca273eceea26619cuLL,0xd186b8c721c0c207ULL,0xeada7dd6cde0eb1eULL,0xf57d4f7fee6ed178ULL,
  0x06f067aa72176fbaULL,0x0a637dc5a2c898a6ULL,0x113f9804bef90daeULL,0x1b710b35131c471bULL,
  0x28db77f523047d84ULL,0x32caab7b40c72493ULL,0x3c9ebe0a15c9bebcULL,0x431d67c49c100d4cULL,
  0x4cc5d4becb3e42b6ULL,0x597f299cfc657e2aULL,0x5fcb6fab3ad6faecULL,0x6c44198c4a475817ULL,
};

#define ROTR64(x,n) (((x) >> (n)) | ((x) << (64 - (n))))
#define CH64(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ64(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0_64(x) (ROTR64(x,28) ^ ROTR64(x,34) ^ ROTR64(x,39))
#define SIG1_64(x) (ROTR64(x,14) ^ ROTR64(x,18) ^ ROTR64(x,41))
#define GAM0_64(x) (ROTR64(x,1) ^ ROTR64(x,8) ^ ((x) >> 7))
#define GAM1_64(x) (ROTR64(x,19) ^ ROTR64(x,61) ^ ((x) >> 6))

static void sha512_block(uint64_t * restrict H, const uint8_t * restrict block) {
  uint64_t W[80];
  int i;
  for (i = 0; i < 16; i++) {
    W[i] = ((uint64_t)block[i*8]<<56)|((uint64_t)block[i*8+1]<<48)|((uint64_t)block[i*8+2]<<40)|((uint64_t)block[i*8+3]<<32)|
           ((uint64_t)block[i*8+4]<<24)|((uint64_t)block[i*8+5]<<16)|((uint64_t)block[i*8+6]<<8)|(uint64_t)block[i*8+7];
  }
  for (i = 16; i < 80; i++)
    W[i] = GAM1_64(W[i-2]) + W[i-7] + GAM0_64(W[i-15]) + W[i-16];
  uint64_t a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
  for (i = 0; i < 80; i++) {
    uint64_t T1 = h + SIG1_64(e) + CH64(e,f,g) + K512[i] + W[i];
    uint64_t T2 = SIG0_64(a) + MAJ64(a,b,c);
    h = g; g = f; f = e; e = d + T1; d = c; c = b; b = a; a = T1 + T2;
  }
  H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;
}

CRYPTO_HOT
void crypto_sha512_c(const uint8_t * restrict msg, int32_t len, uint8_t * restrict out) {
  uint64_t H[8] = {
    0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
    0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
  };
  uint8_t block[128];
  uint64_t total_bits = (uint64_t)len * 8;
  const uint8_t *p = msg;
  while (len >= 128) {
    sha512_block(H, p);
    p += 128; len -= 128;
  }
  memcpy(block, p, (size_t)len);
  block[len++] = 0x80;
  if (len > 112) {
    while (len < 128) block[len++] = 0;
    sha512_block(H, block);
    len = 0;
    memset(block, 0, 112);
  } else
    while (len < 112) block[len++] = 0;
  block[112] = (uint8_t)(total_bits >> 56); block[113] = (uint8_t)(total_bits >> 48);
  block[114] = (uint8_t)(total_bits >> 40); block[115] = (uint8_t)(total_bits >> 32);
  block[116] = (uint8_t)(total_bits >> 24); block[117] = (uint8_t)(total_bits >> 16);
  block[118] = (uint8_t)(total_bits >> 8);  block[119] = (uint8_t)total_bits;
  sha512_block(H, block);
  for (int i = 0; i < 8; i++) {
    out[i*8]   = (uint8_t)(H[i] >> 56); out[i*8+1] = (uint8_t)(H[i] >> 48);
    out[i*8+2] = (uint8_t)(H[i] >> 40); out[i*8+3] = (uint8_t)(H[i] >> 32);
    out[i*8+4] = (uint8_t)(H[i] >> 24); out[i*8+5] = (uint8_t)(H[i] >> 16);
    out[i*8+6] = (uint8_t)(H[i] >> 8);  out[i*8+7] = (uint8_t)H[i];
  }
}

/* ---------- HMAC-SHA256 (RFC 2104) ---------- */
#define HMAC_BLOCK 64
#define IPAD 0x36
#define OPAD 0x5c

CRYPTO_HOT
void crypto_hmac_sha256_c(const uint8_t * restrict key, int32_t key_len, const uint8_t * restrict msg, int32_t msg_len, uint8_t * restrict out) {
  uint8_t kbuf[64];
  if (key_len > 64) {
    crypto_sha256_c(key, key_len, kbuf);
    key = kbuf;
    key_len = 32;
  }
  uint8_t ko[64];
  memcpy(ko, key, (size_t)key_len);
  if (key_len < 64) memset(ko + key_len, 0, (size_t)(64 - key_len));
  uint8_t inner[64 + 4096];
  if (64 + msg_len > (int32_t)sizeof(inner)) { memset(out, 0, 32); return; }
  for (int i = 0; i < 64; i++) inner[i] = ko[i] ^ IPAD;
  memcpy(inner + 64, msg, (size_t)msg_len);
  crypto_sha256_c(inner, 64 + msg_len, out);
  uint8_t outer[64 + 32];
  for (int i = 0; i < 64; i++) outer[i] = ko[i] ^ OPAD;
  memcpy(outer + 64, out, 32);
  crypto_sha256_c(outer, 64 + 32, out);
}
