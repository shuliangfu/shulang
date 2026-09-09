// PLATFORM: SHARED — 128-byte STRING_LIT (parser L011 was 127).
// First 127 live in Expr.var_name; byte 127 is the first overflow chunk.

function main(): i32 {
  let s: *u8 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  unsafe {
    if (s == (0 as *u8)) {
      return 10;
    }
    if (*s != 120) {
      return 1;
    }
    if (*(s + 127) != 120) {
      return 2;
    }
  }
  return 0;
}
