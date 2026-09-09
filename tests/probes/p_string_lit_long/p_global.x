// PLATFORM: SHARED — 128-byte STRING_LIT in a global *u8[1] (RELA intern path).

let s: *u8[1] = ["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"];

function main(): i32 {
  unsafe {
    let p: *u8 = s[0];
    if (p == (0 as *u8)) {
      return 10;
    }
    if (*p != 120) {
      return 1;
    }
    if (*(p + 127) != 120) {
      return 2;
    }
  }
  return 0;
}
