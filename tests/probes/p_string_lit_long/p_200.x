// PLATFORM: SHARED — 200-byte STRING_LIT (two overflow chunks after the head).

function main(): i32 {
  let s: *u8 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  unsafe {
    if (s == (0 as *u8)) {
      return 10;
    }
    if (*s != 120) {
      return 1;
    }
    if (*(s + 199) != 120) {
      return 2;
    }
  }
  return 0;
}
