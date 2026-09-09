// PLATFORM: SHARED — scalar bare-fn global used from a NON-hoist function.
// `let h: *u8 = inc` must bake .data + absolute64 RELA to the fn symbol.
// Expected: exit 42 (h(41) == 42).
function inc(x: i32): i32 { return x + 1; }
let h: *u8 = inc;
function other(): i32 {
  let f: function(i32): i32 = h as function(i32): i32;
  return f(41);
}
function main(): i32 {
  return other();
}
