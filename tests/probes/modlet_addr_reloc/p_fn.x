// PLATFORM: SHARED — 9.4.2 ADDR_OF residual: global fn-ptr TABLE bakes
// via absolute64 RELA (no longer COMMON + entry seeder).
//   `let tab: [2]*u8 = [inc, dec];` then call through both elems.
// Expected: exit 42.
function inc(x: i32): i32 { return x + 1; }
function dec(x: i32): i32 { return x - 1; }
let tab: [2]*u8 = [inc, dec];
function main(): i32 {
  let f: function(i32): i32 = tab[0] as function(i32): i32;
  let g2: function(i32): i32 = tab[1] as function(i32): i32;
  if (f(40) != 41) { return 7; }
  if (g2(43) != 42) { return 8; }
  return 42;
}
