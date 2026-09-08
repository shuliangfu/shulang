// wave922 (9.2.2) · rc-gated probe: zlib C API via std.compress.zlib
// Standing C rest (same domain as 9.3.2 zlib.h macros):
//   deflateInit2_impl_c / inflateInit2_impl_c live in
//   runtime_compress_zlib_glue rest because they #include <zlib.h>,
//   #undef the Init2 macros, and call deflateInit2_ / inflateInit2_
//   with ZLIB_VERSION + sizeof(z_stream). Thin .x only wraps.
//   One-shot zlib.deflate / zlib.inflate bind system compress2 /
//   uncompress (-lz). gzip_compress / gzip_decompress hit the Init2
//   glue (gzip wrapper, windowBits=31). This probe does NOT port
//   zlib — it pins product-path roundtrip against system -lz.
// Unix $? is 8-bit: case numbers stay in 1..12.
// PLATFORM: SHARED — Darwin + Ubuntu must both hit the real backend
// (n>0 compressed bytes). A stub / missing -lz is fail, not skip.

const zlib = import("std.compress.zlib");
const gzip = import("std.compress.gzip");

/**
 * Product-path zlib / gzip C API matrix. Return 0 if every pin matches.
 * @return i32 — 0 all pass, 1..12 the first failing pin (8-bit-safe)
 */
function main(): i32 {
  let raw: u8[12] = [72, 101, 108, 108, 111, 44, 32, 122, 108, 105, 98, 33];
  let z_out: u8[256] = [];
  let z_dec: u8[256] = [];
  let g_out: u8[256] = [];
  let g_dec: u8[256] = [];
  let n: i32 = 0;
  let m: i32 = 0;
  let i: i32 = 0;

  n = zlib.deflate(&raw[0], 12, &z_out[0], 256);
  if (n <= 0) {
    return 1;
  }
  if (n >= 256) {
    return 2;
  }
  m = zlib.inflate(&z_out[0], n, &z_dec[0], 256);
  if (m != 12) {
    return 3;
  }
  i = 0;
  while (i < 12) {
    if (z_dec[i] != raw[i]) {
      return 4;
    }
    i = i + 1;
  }

  n = gzip.gzip_compress(&raw[0], 12, &g_out[0], 256);
  if (n <= 0) {
    return 5;
  }
  if (n >= 256) {
    return 6;
  }
  m = gzip.gzip_decompress(&g_out[0], n, &g_dec[0], 256);
  if (m != 12) {
    return 7;
  }
  i = 0;
  while (i < 12) {
    if (g_dec[i] != raw[i]) {
      return 8;
    }
    i = i + 1;
  }

  if (zlib.deflate(0 as *u8, 12, &z_out[0], 256) != (0 - 1)) {
    return 9;
  }
  if (zlib.inflate(&z_out[0], 12, 0 as *u8, 256) != (0 - 1)) {
    return 10;
  }
  if (gzip.gzip_compress(&raw[0], 12, &g_out[0], 0) != (0 - 1)) {
    return 11;
  }
  if (gzip.gzip_decompress(0 as *u8, 12, &g_dec[0], 256) != (0 - 1)) {
    return 12;
  }
  return 0;
}
