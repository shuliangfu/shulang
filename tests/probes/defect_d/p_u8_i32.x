/**
 * Defect D: u8 vs i32 compare must accept after C integer promotions.
 * Equal 3==3 → exit 0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: u8 = 3;
  let n: i32 = 3;
  if (a == n) {
    return 0;
  }
  return 1;
}
