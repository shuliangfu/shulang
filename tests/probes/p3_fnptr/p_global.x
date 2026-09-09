// p3 family: module-level TYPE_FN ← bare same-module fn.
// `let f: function(i32): i32 = inc` used to T001 expected function, found *u8
// (top-level equal-ref gate missed typeck_fnptr_surface_compat).
// Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i32 = inc;
function main(): i32 {
  return f(41);
}
