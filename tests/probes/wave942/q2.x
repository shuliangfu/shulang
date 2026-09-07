// wave942 (9.4.2 slice) · global fn-ptr TABLE, bare fn elems:
//   `let tab: [2]*u8 = [inc, dec];` — prepare keeps the table COMMON
//   (bake cannot express relocations) and the entry seeder LEAs each
//   fn symbol into the cell.
// Expected: exit 42 (both elems non-zero links).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function inc(x: i32): i32 { return x + 1; }
function dec(x: i32): i32 { return x - 1; }
let tab: [2]*u8 = [inc, dec];
function main(): i32 {
  if (tab[0] == 0) { return 7; }
  if (tab[1] == 0) { return 8; }
  return 42;
}
