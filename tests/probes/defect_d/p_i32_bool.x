/**
 * wave666 keep: i32 vs bool compare stays mixed-type T001.
 * Expect compile fail (T001 / XT001).
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: i32 = 1;
  let b: bool = true;
  if (a == b) {
    return 0;
  }
  return 1;
}
