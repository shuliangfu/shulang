// PLATFORM: SHARED — 9.4.2 ADDR_OF residual: `fn as *u8` table elems bake
// via the same absolute64 RELA as bare-fn tables.
// Expected: exit 42.
function inc(x: i32): i32 { return x + 1; }
let tab: [2]*u8 = [inc as *u8, inc as *u8];
function main(): i32 {
  let f: function(i32): i32 = tab[0] as function(i32): i32;
  if (f(41) != 42) { return 7; }
  return 42;
}
