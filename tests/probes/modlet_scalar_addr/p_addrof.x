// PLATFORM: SHARED — scalar ADDR_OF global used from a NON-hoist function.
// `let p: *i32 = &g` must bake an 8-byte .data cell + absolute64 RELA;
// hoist-only seed used to leave other() reading an unseeded slot (run=100).
// Expected: exit 5 (*p == g).
let g: i32 = 5;
let p: *i32 = &g;
function other(): i32 {
  unsafe { return *p; }
}
function main(): i32 {
  return other();
}
