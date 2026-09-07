// wave942 (9.4.2 slice) · LOCAL fn-ptr table + fn-ptr CALL regression
//   guard: `let tab: [2]*u8 = [inc, dec];` in a body, indirect calls via
//   `as function(i32): i32` casts.
// Expected: exit 42 (f(40)==41 && g2(43)==42).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
function dec(x: i32): i32 { return x - 1; }
function main(): i32 {
  let tab: [2]*u8 = [inc, dec];
  let f: function(i32): i32 = tab[0] as function(i32): i32;
  let g2: function(i32): i32 = tab[1] as function(i32): i32;
  if (f(40) != 41) { return 7; }
  if (g2(43) != 42) { return 8; }
  return 42;
}
