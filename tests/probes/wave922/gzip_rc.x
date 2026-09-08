// wave922 (9.2.2 gzip Init2) · rc-gated probe: std.compress.gzip
// Product import co-emits libz.x. Standing C rest is deflateInit2 glue
// (9.3.2 zlib.h macros). This probe does NOT port zlib.
// Root: import-merged ZStream field offsets must be the synced table,
// not a caller-arena recompute (that returned 0 → zalloc garbage SEGV).
// Unix $? is 8-bit: case numbers stay in 1..5.
// PLATFORM: SHARED — Darwin + Ubuntu must both roundtrip gzip.

const gzip = import("std.compress.gzip");

/**
 * Product-path gzip Init2 roundtrip. Return 0 if every pin matches.
 * @return i32 — 0 all pass, 1..5 the first failing pin (8-bit-safe)
 */
function main(): i32 {
  let raw: u8[12] = [72, 101, 108, 108, 111, 44, 32, 122, 108, 105, 98, 33];
  let g_out: u8[256] = [];
  let g_dec: u8[256] = [];
  let n: i32 = 0;
  let m: i32 = 0;
  let i: i32 = 0;

  n = gzip.gzip_compress(&raw[0], 12, &g_out[0], 256);
  if (n <= 0) {
    return 1;
  }
  if (n >= 256) {
    return 2;
  }
  m = gzip.gzip_decompress(&g_out[0], n, &g_dec[0], 256);
  if (m != 12) {
    return 3;
  }
  i = 0;
  while (i < 12) {
    if (g_dec[i] != raw[i]) {
      return 4;
    }
    i = i + 1;
  }
  if (gzip.gzip_compress(0 as *u8, 12, &g_out[0], 256) != (0 - 1)) {
    return 5;
  }
  return 0;
}
