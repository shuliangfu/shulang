// PLATFORM: SHARED — scalar `fn as *u8` global used from a NON-hoist function.
// Expected: exit 42.
function inc(x: i32): i32 { return x + 1; }
let h: *u8 = inc as *u8;
function other(): i32 {
  let f: function(i32): i32 = h as function(i32): i32;
  return f(41);
}
function main(): i32 {
  return other();
}
