// wave942 (9.4.2 slice) · ADDR_OF global inside a function body:
//   `let q: *i32 = &g;` — same resolver fallback via the local VAR path.
// Expected: exit 5 (*q == g).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
let g: i32 = 5;
function main(): i32 {
  let q: *i32 = &g;
  unsafe { return *q; }
}
