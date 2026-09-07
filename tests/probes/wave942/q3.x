// wave942 (9.4.2 slice) · global fn-ptr TABLE, `fn as *u8` elems:
//   `let tab: [2]*u8 = [inc as *u8, inc as *u8];` — AS-cast elems take
//   the same COMMON + entry-seed path as q2.
// Expected: exit 42 (elem link non-zero).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
let tab: [2]*u8 = [inc as *u8, inc as *u8];
function main(): i32 {
  if (tab[0] == 0) { return 7; }
  return 42;
}
