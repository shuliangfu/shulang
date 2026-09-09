// PLATFORM: SHARED — adjacent concat 80+80=160 (was L011 at 63, then 127).

function main(): i32 {
  let s: *u8 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  unsafe {
    if (s == (0 as *u8)) {
      return 10;
    }
    if (*s != 120) {
      return 1;
    }
    if (*(s + 159) != 120) {
      return 2;
    }
  }
  return 0;
}
