// PLATFORM: SHARED — 9.6.2 residual: global *u8[N] lit via .data RELA + string pool.
// Exit 10/11 = NULL pointer (bake missed reloc). Exit 1/2 = wrong first byte.
let msgs: *u8[2] = ["ab", "cd"];

function main(): i32 {
  unsafe {
    let p0: *u8 = msgs[0];
    let p1: *u8 = msgs[1];
    if (p0 == (0 as *u8)) {
      return 10;
    }
    if (p1 == (0 as *u8)) {
      return 11;
    }
    if (*p0 != 97) {
      return 1;
    }
    if (*p1 != 99) {
      return 2;
    }
  }
  return 0;
}
