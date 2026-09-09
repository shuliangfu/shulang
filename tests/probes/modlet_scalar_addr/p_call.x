// PLATFORM: SHARED — scalar TYPE_FN global used from a NON-hoist function.
// `let f: function(i32): i32 = inc` must bake .data + absolute64 RELA.
// Expected: exit 42.
function inc(x: i32): i32 { return x + 1; }
let f: function(i32): i32 = inc;
function other(): i32 {
  return f(41);
}
function main(): i32 {
  return other();
}
