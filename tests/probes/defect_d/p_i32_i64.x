/**
 * wave666 keep: i32 vs i64 compare stays mixed-type T001 (no usual arith conv).
 * Expect compile fail (T001 / XT001).
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: i32 = 3;
  let n: i64 = 3;
  if (a == n) {
    return 0;
  }
  return 1;
}
