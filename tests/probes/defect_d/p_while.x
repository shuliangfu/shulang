/**
 * Defect D: u8 vs i32 compare inside while cond.
 * Count 0..3 via `while (b != n)`.
 * Expect exit 3.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let b: u8 = 0;
  let n: i32 = 3;
  while (b != n) {
    b = b + 1;
  }
  return b as i32;
}
