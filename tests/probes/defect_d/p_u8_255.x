/**
 * Defect D: u8 255 vs i32 255 must compare as unsigned-promoted 255, not -1.
 * Equal → exit 0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: u8 = 255;
  let n: i32 = 255;
  if (a == n) {
    return 0;
  }
  return 1;
}
