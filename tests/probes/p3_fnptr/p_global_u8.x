// p3 family regression: wave942 q1 `let h: *u8 = inc` (Cap surface).
// Expected: exit 42 (non-null).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let h: *u8 = inc;
function main(): i32 {
  if (h == 0) { return 7; }
  return 42;
}
