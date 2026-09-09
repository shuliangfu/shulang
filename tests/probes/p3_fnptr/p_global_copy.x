// p3 family: TYPE_FN ← TYPE_FN at module scope (copy of a prior global).
// Expected: exit 42.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i32 = inc;
let g: function(i32): i32 = f;
function main(): i32 {
  return g(41);
}
