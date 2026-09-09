// PLATFORM: SHARED — 9.4.2 ADDR_OF residual: TYPE_FN table elems bake
// via absolute64 RELA; indirect call reads the relocated pointer.
// Expected: exit 42 (tab[0](41) == 42).
function inc(x: i32): i32 { return x + 1; }
function dec(x: i32): i32 { return x - 1; }
let tab: [2]function(i32): i32 = [inc, dec];
function main(): i32 {
  return tab[0](41);
}
