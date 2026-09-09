// p3 family regression: global TYPE_FN table already green via array-lit
// coerce (typeck_fnptr_surface_compat per elem). Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
function dec(x: i32): i32 { return x - 1; }
let tab: [2]function(i32): i32 = [inc, dec];
function main(): i32 {
  return tab[0](41);
}
