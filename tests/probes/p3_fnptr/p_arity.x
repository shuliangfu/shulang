// p3 family keep-red: arity mismatch stays T001 (surface sig equal).
// Expected: compile fail assignment type mismatch.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32, i32): i32 = inc;
function main(): i32 {
  return 0;
}
