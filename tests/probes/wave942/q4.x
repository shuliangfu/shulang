// wave942 (9.4.2 slice) · ADDR_OF global at module scope:
//   `let p: *i32 = &g;` — lvalue/addr_of VAR scoped-miss falls back to
//   the modlet COMMON cell resolver; deref must read the seeded value.
// Expected: exit 5 (*p == g).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
let g: i32 = 5;
let p: *i32 = &g;
function main(): i32 {
  unsafe { return *p; }
}
