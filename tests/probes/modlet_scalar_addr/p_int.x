// PLATFORM: SHARED — mutable scalar LIT still COMMON (not this knife).
// other() must read the seeded cell. Expected: exit 5.
let g: i32 = 5;
function other(): i32 {
  return g;
}
function main(): i32 {
  return other();
}
