// p3 family regression: module-level explicit `as function` already stamps
// TYPE_FN so the equal-ref gate passes. Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i32 = inc as function(i32): i32;
function main(): i32 {
  return f(41);
}
