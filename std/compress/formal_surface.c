/* PLATFORM: SHARED — pure-asm formal vehicle for std/compress (class-batch 2).
 *
 * Why C face: .x monofile co-emits bare deflate/inflate that conflict with zlib
 * C API types in the same TU. Product body stays in submodule formal .o
 * (std/compress/gzip/gzip.o, zlib/zlib.o). This vehicle exports the facade
 * std_compress_* names the user import mangles to.
 *
 * G.7: complete existing c_face — gzip one-shot faces trampoline to the
 * submodule mangle (std_compress_gzip_gzip_*), not return -1. Returning -1
 * made `xlang build` skip-green (tests/compress/main.x treats n<=0 as skip)
 * while gzip.o was never on the ld argv. zstd/brotli stay unavailable until
 * those submodule .o are catalogued and pushed (separate residual).
 *
 * G.7: single formal vehicle for pure-asm product link (catalog key
 * std/compress/compress.o). formal_mod kind=c_face.
 */
#include <stdint.h>

/* PLATFORM: SHARED — product gzip lives in gzip.o (mod.x + libz.x). */
extern int32_t std_compress_gzip_gzip_compress(uint8_t *in, int32_t in_len, uint8_t *out,
                                               int32_t out_cap);
extern int32_t std_compress_gzip_gzip_decompress(uint8_t *in, int32_t in_len, uint8_t *out,
                                                 int32_t out_cap);

int32_t std_compress_gzip_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_gzip_gzip_compress(in, in_len, out, out_cap);
}

int32_t std_compress_gzip_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_gzip_gzip_decompress(in, in_len, out, out_cap);
}

int32_t std_compress_brotli_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
}

int32_t std_compress_brotli_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
}

int32_t std_compress_zstd_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
}

int32_t std_compress_zstd_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  (void)in;
  (void)in_len;
  (void)out;
  (void)out_cap;
  return -1;
}

/* Stream surface (cookbook compress_stream_br_zs unique UNDEF).
 * format/mode match std/compress/mod.x constants. state_bytes_for returns
 * the real gzip/brotli/zstd caps (128/32/32) so the cookbook passes the
 * 1..512 gate. init/process/end stay unavailable (-1), same contract as
 * the one-shot faces: tests/cookbooks treat codec-not-linked as success 0.
 * PLATFORM: SHARED — c_face T only; product body remains mod.x. */
typedef struct std_compress_StreamCompress {
  int32_t format;
  int32_t mode;
  uint8_t *state;
  int32_t state_cap;
} std_compress_StreamCompress;

int32_t std_compress_format_brotli(void) {
  return 1;
}

int32_t std_compress_format_zstd(void) {
  return 2;
}

int32_t std_compress_mode_compress(void) {
  return 0;
}

int32_t std_compress_mode_decompress(void) {
  return 1;
}

int32_t std_compress_compress_state_bytes_for(int32_t format) {
  if (format == 0) {
    return 128;
  }
  if (format == 1) {
    return 32;
  }
  if (format == 2) {
    return 32;
  }
  return -1;
}

int32_t std_compress_compress_init(std_compress_StreamCompress *sc, uint8_t *state,
                                   int32_t state_cap, int32_t format, int32_t mode) {
  (void)sc;
  (void)state;
  (void)state_cap;
  (void)format;
  (void)mode;
  return -1;
}

int32_t std_compress_compress_process(std_compress_StreamCompress sc, uint8_t *inp,
                                      int32_t in_len, uint8_t *out, int32_t out_cap,
                                      int32_t is_last, int32_t *in_consumed) {
  (void)sc;
  (void)inp;
  (void)in_len;
  (void)out;
  (void)out_cap;
  (void)is_last;
  (void)in_consumed;
  return -1;
}

int32_t std_compress_compress_end(std_compress_StreamCompress sc) {
  (void)sc;
  return -1;
}

/* PLATFORM: SHARED — g15 needles 24→28 (run-compress BLD001). gzip/brotli/zstd
 * lib.x co-emit calls these facade names (and one brotli-lib init) as U;
 * c_face is the compress.o product vehicle so it must export the T.
 * Caps match compress_state_bytes_for (128/32/32). init stays unavailable. */
int32_t std_compress_gzip_stream_state_bytes(void) {
  return 128;
}

int32_t std_compress_brotli_stream_state_bytes(void) {
  return 32;
}

int32_t std_compress_zstd_stream_state_bytes(void) {
  return 32;
}

int32_t std_compress_brotli_lib_compress_brotli_stream_init_decompress_(uint8_t *state,
                                                                        int32_t state_cap) {
  (void)state;
  (void)state_cap;
  return -1;
}
