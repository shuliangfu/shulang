// wave925 (9.2.5) · rc-gated probe: arrow SIMD kernels via std.db.arrow
// Standing C intrinsic bridge (same domain as 9.3.5):
//   arrow_f32_sum_kernel / arrow_f32_dot_kernel /
//   arrow_i32_sum_valid_kernel / arrow_f32_sum_valid_kernel
// live in runtime_arrow_simd_glue rest as *_impl (SSE2 / NEON target
// attributes). Thin .x only wraps. This probe does NOT port the
// kernels — it pins product-path results at SIMD width and scalar tail.
// Inputs are integer / dyadic f32 (1,2,3,4,5,0.5) so pairwise SIMD add
// and sequential add match exactly (no ulp card). Unix $? is 8-bit:
// pack rc!=0 → return 1.
// PLATFORM: SHARED — Darwin NEON and Ubuntu SSE2 must agree on these pins.
const dbarrow = import("std.db.arrow");

/**
 * Append f32 values 1.0 .. n.0 into col (exact integer f32).
 * @param col ArrowColumn — f32 column with capacity >= n
 * @param n i32 — count; n <= 0 is a no-op success
 * @return i32 — 0 on success, -1 if any append fails
 */
function fill_f32_1n(col: ArrowColumn, n: i32): i32 {
  let i: i32 = 1;
  while (i <= n) {
    if (dbarrow.append(col, i as f32) != 0) {
      return 0 - 1;
    }
    i = i + 1;
  }
  return 0;
}

/**
 * Append the f32 value one, n times.
 * @param col ArrowColumn — f32 column with capacity >= n
 * @param one f32 — value to repeat
 * @param n i32 — count
 * @return i32 — 0 on success, -1 if any append fails
 */
function fill_f32_repeat(col: ArrowColumn, one: f32, n: i32): i32 {
  let i: i32 = 0;
  while (i < n) {
    if (dbarrow.append(col, one) != 0) {
      return 0 - 1;
    }
    i = i + 1;
  }
  return 0;
}

/**
 * Append i32 values 1 .. n, all valid (hits the 4-wide SIMD i32 path when n>=4).
 * @param col ArrowColumn — i32 column with capacity >= n
 * @param n i32 — count
 * @return i32 — 0 on success, -1 if any append fails
 */
function fill_i32_1n(col: ArrowColumn, n: i32): i32 {
  let i: i32 = 1;
  while (i <= n) {
    if (dbarrow.append(col, i) != 0) {
      return 0 - 1;
    }
    i = i + 1;
  }
  return 0;
}

/**
 * Product-path kernel matrix. Return 0 if every pin matches, 1 otherwise.
 * @return i32 — 0 all pass, 1 any fail (8-bit-safe)
 */
function main(): i32 {
  let rc: i32 = 0;
  let ten: f32 = 10.0 as f32;
  let fifteen: f32 = 15.0 as f32;
  let eight: f32 = 8.0 as f32;
  let six: f32 = 6.0 as f32;
  let seven: f32 = 7.0 as f32;
  let five: f32 = 5.0 as f32;
  let zero: f32 = 0.0 as f32;
  let half: f32 = 0.5 as f32;
  let one: f32 = 1.0 as f32;
  let c: ArrowColumn = { handle: 0 };
  let d: ArrowColumn = { handle: 0 };
  let bm: *u8 = 0 as *u8;

  /* 1. f32 sum n=4 → 10 (exactly one SSE2/NEON vector). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_1n(c, 4) != 0) { rc = rc | 1; }
  if (dbarrow.sum(c, 4) != ten) { rc = rc | 1; }
  dbarrow.free(c);

  /* 2. f32 sum n=5 → 15 (one vector + scalar tail). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_1n(c, 5) != 0) { rc = rc | 2; }
  if (dbarrow.sum(c, 5) != fifteen) { rc = rc | 2; }
  dbarrow.free(c);

  /* 3. f32 sum n=8 ones → 8 (two vectors). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_repeat(c, one, 8) != 0) { rc = rc | 4; }
  if (dbarrow.sum(c, 8) != eight) { rc = rc | 4; }
  dbarrow.free(c);

  /* 4. f32 sum n=0 → 0. */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (dbarrow.sum(c, 0) != zero) { rc = rc | 8; }
  dbarrow.free(c);

  /* 5. f32 sum n=1 → 7 (scalar-only, no SIMD). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (dbarrow.append(c, seven) != 0) { rc = rc | 16; }
  if (dbarrow.sum(c, 1) != seven) { rc = rc | 16; }
  dbarrow.free(c);

  /* 6. f32 sum n=3 → 6 (scalar remainder, width < 4). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_1n(c, 3) != 0) { rc = rc | 32; }
  if (dbarrow.sum(c, 3) != six) { rc = rc | 32; }
  dbarrow.free(c);

  /* 7. f32 dot n=4 [1,2,3,4]·[1,1,1,1] → 10. */
  c = dbarrow.new_f32(16);
  d = dbarrow.new_f32(16);
  if (c.handle == 0 || d.handle == 0) { return 1; }
  if (fill_f32_1n(c, 4) != 0) { rc = rc | 64; }
  if (fill_f32_repeat(d, one, 4) != 0) { rc = rc | 64; }
  if (dbarrow.dot(c, d, 4) != ten) { rc = rc | 64; }
  dbarrow.free(c);
  dbarrow.free(d);

  /* 8. f32 dot n=4 [1,2,3,4]·[0.5,0.5,0.5,0.5] → 5 (0.5 is exact f32). */
  c = dbarrow.new_f32(16);
  d = dbarrow.new_f32(16);
  if (c.handle == 0 || d.handle == 0) { return 1; }
  if (fill_f32_1n(c, 4) != 0) { rc = rc | 128; }
  if (fill_f32_repeat(d, half, 4) != 0) { rc = rc | 128; }
  if (dbarrow.dot(c, d, 4) != five) { rc = rc | 128; }
  dbarrow.free(c);
  dbarrow.free(d);

  /* 9. i32 sum_valid mixed nulls: 10 + skip + 20 → 30. */
  c = dbarrow.new_i32(16);
  if (c.handle == 0) { return 1; }
  if (dbarrow.append_null(c, 10, 1) != 0) { rc = rc | 256; }
  if (dbarrow.append_null(c, 0, 0) != 0) { rc = rc | 256; }
  if (dbarrow.append_null(c, 20, 1) != 0) { rc = rc | 256; }
  if (dbarrow.sum_valid_i32(c, 3) != 30) { rc = rc | 256; }
  dbarrow.free(c);

  /* 10. i32 sum_valid n=4 all valid → 10 (4-wide SIMD when mask nibble 0xF). */
  c = dbarrow.new_i32(16);
  if (c.handle == 0) { return 1; }
  if (fill_i32_1n(c, 4) != 0) { rc = rc | 512; }
  if (dbarrow.sum_valid_i32(c, 4) != 10) { rc = rc | 512; }
  dbarrow.free(c);

  /* 11. i32 sum_valid n=5 all valid → 15 (SIMD + scalar tail). */
  c = dbarrow.new_i32(16);
  if (c.handle == 0) { return 1; }
  if (fill_i32_1n(c, 5) != 0) { rc = rc | 1024; }
  if (dbarrow.sum_valid_i32(c, 5) != 15) { rc = rc | 1024; }
  dbarrow.free(c);

  /* 12. i32 sum_valid n=4 all-null → 0. */
  c = dbarrow.new_i32(16);
  if (c.handle == 0) { return 1; }
  if (dbarrow.append_null(c, 1, 0) != 0) { rc = rc | 2048; }
  if (dbarrow.append_null(c, 2, 0) != 0) { rc = rc | 2048; }
  if (dbarrow.append_null(c, 3, 0) != 0) { rc = rc | 2048; }
  if (dbarrow.append_null(c, 4, 0) != 0) { rc = rc | 2048; }
  if (dbarrow.sum_valid_i32(c, 4) != 0) { rc = rc | 2048; }
  dbarrow.free(c);

  /* 13. f32 sum_valid n=4 all valid → 10 (same as sum). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_1n(c, 4) != 0) { rc = rc | 4096; }
  if (dbarrow.sum_valid_f32(c, 4) != ten) { rc = rc | 4096; }
  dbarrow.free(c);

  /* 14. f32 sum_valid n=4 with index 1 invalid → 1+3+4 = 8.
   * Create sets the bitmap to 0xFF; clear bit 1 (value 2). */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_1n(c, 4) != 0) { rc = rc | 8192; }
  bm = dbarrow.null_bitmap(c);
  if (bm == 0 as *u8) {
    rc = rc | 8192;
  } else {
    unsafe {
      bm[0] = bm[0] & ((255 as u8) ^ (2 as u8));
    }
    if (dbarrow.sum_valid_f32(c, 4) != eight) { rc = rc | 8192; }
  }
  dbarrow.free(c);

  /* 15. f32 sum_valid n=8 ones all valid → 8. */
  c = dbarrow.new_f32(16);
  if (c.handle == 0) { return 1; }
  if (fill_f32_repeat(c, one, 8) != 0) { rc = rc | 16384; }
  if (dbarrow.sum_valid_f32(c, 8) != eight) { rc = rc | 16384; }
  dbarrow.free(c);

  if (rc != 0) { return 1; }
  return 0;
}
