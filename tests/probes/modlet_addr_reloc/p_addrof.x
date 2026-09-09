// PLATFORM: SHARED — 9.4.2 ADDR_OF residual: table of `&global` elems
// bakes via absolute64 RELA to each modlet cell label.
// Expected: exit 12 (*tab[0] + *tab[1] == 5+7).
let g: i32 = 5;
let h: i32 = 7;
let tab: [2]*i32 = [&g, &h];
function main(): i32 {
  unsafe { return *tab[0] + *tab[1]; }
}
