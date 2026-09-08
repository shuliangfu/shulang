// wave922 (9.2.2) · rc-gated probe: zlib C API via std.compress.zlib
// Standing C rest (same domain as 9.3.2 zlib.h macros):
//   One-shot zlib.deflate / zlib.inflate bind system compress2 /
//   uncompress (-lz). This probe does NOT port zlib.
// gzip_compress (deflateInit2 glue) is a separate standing card:
//   x86_64 field stores into allow(padding) ZStream use offset 0, so
//   zalloc is stack garbage and libz deflateInit2_ SIGSEGV. Darwin
//   AAPCS64 stores real field offsets and gzip roundtrip is green.
// Unix $? is 8-bit: case numbers stay in 1..6.
// PLATFORM: SHARED — Darwin + Ubuntu must both hit real -lz
// (n>0 compressed bytes). Missing -lz is fail, not skip.

const zlib = import("std.compress.zlib");

/**
 * Product-path zlib one-shot matrix. Return 0 if every pin matches.
 * @return i32 — 0 all pass, 1..6 the first failing pin (8-bit-safe)
 */
function main(): i32 {
  let raw: u8[12] = [72, 101, 108, 108, 111, 44, 32, 122, 108, 105, 98, 33];
  let z_out: u8[256] = [];
  let z_dec: u8[256] = [];
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

  if (zlib.deflate(0 as *u8, 12, &z_out[0], 256) != (0 - 1)) {
    return 5;
  }
  if (zlib.inflate(&z_out[0], 12, 0 as *u8, 256) != (0 - 1)) {
    return 6;
  }
  return 0;
}
