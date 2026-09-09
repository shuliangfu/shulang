// PLATFORM: SHARED — empty STRING_LIT intern (slen=0 → one NUL in the pool).
let e: *u8[1] = [""];

function main(): i32 {
  unsafe {
    let p: *u8 = e[0];
    if (p == (0 as *u8)) {
      return 10;
    }
    if (*p != 0) {
      return 1;
    }
  }
  return 0;
}
