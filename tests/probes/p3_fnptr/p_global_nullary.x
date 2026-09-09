// p3 family: `function(): i32` (no params) module-level assign.
// Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function forty(): i32 { return 42; }
let f: function(): i32 = forty;
function main(): i32 {
  return f();
}
