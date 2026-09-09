// p3 family regression: function-scope TYPE_FN ← bare fn already green
// via typeck_check_block_one_let. Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
function main(): i32 {
  let f: function(i32): i32 = inc;
  return f(41);
}
