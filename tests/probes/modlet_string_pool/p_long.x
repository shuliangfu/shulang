// PLATFORM: SHARED — 126-byte STRING_LIT in a global *u8[1] (jmp-skip cap).
// Parser Expr.var_name[128] holds 127; intern accepts slen<=127.
let s: *u8[1] = ["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"];

function main(): i32 {
  unsafe {
    let p: *u8 = s[0];
    if (p == (0 as *u8)) {
      return 10;
    }
    if (*p != 120) {
      return 1;
    }
  }
  return 0;
}
