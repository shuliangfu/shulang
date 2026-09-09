// p3 family keep-red: return-type mismatch stays T001.
// Expected: compile fail assignment type mismatch.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i64 = inc;
function main(): i32 {
  return 0;
}
