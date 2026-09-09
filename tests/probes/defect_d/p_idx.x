/**
 * Defect D: u8 INDEX vs i32 var compare inside while.
 * g[i]==3 hits at i=2 → exit 0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let g: u8[4] = [1, 2, 3, 4];
  let n: i32 = 3;
  let i: i32 = 0;
  while (i < 4) {
    if (g[i] == n) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}
