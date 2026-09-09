// p3 family keep-red: true opaque Cap *u8 (no recoverable same-module fn)
// must stay T001 (allow_opaque=0 on the let gate).
// Expected: compile fail assignment type mismatch.
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
let c: *u8 = 0;
let f: function(i32): i32 = c;
function main(): i32 {
  return 0;
}
