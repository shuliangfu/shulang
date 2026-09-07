// wave942 (9.4.2 slice) · global scalar fn-ptr regression guard:
//   `let h: *u8 = inc;` — bare same-module fn into *u8 global.
// Expected: exit 42 (h non-zero; call path covered by q6).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let h: *u8 = inc;
function main(): i32 {
  if (h == 0) { return 7; }
  return 42;
}
