/**
 * Defect D: u8 vs i32 compare of unequal values still typecks.
 * 3==4 is false → exit 1.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: u8 = 3;
  let n: i32 = 4;
  if (a == n) {
    return 0;
  }
  return 1;
}
