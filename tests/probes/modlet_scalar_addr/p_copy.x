// PLATFORM: SHARED — TYPE_FN copy of a prior global must KEEP historic hoist
// (`let g = f` is a value copy, not an address literal). Main-only use, as
// p3 p_global_copy. Expected: exit 42.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i32 = inc;
let g: function(i32): i32 = f;
function main(): i32 {
  return g(41);
}
