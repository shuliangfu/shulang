// PLATFORM: SHARED — 127-byte STRING_LIT still fits in Expr.var_name[128].
// Pre-fix: parse OK, emit CG002 (jmp-skip 126 cap).

function main(): i32 {
  let s: *u8 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  unsafe {
    if (s == (0 as *u8)) {
      return 10;
    }
    if (*s != 120) {
      return 1;
    }
    if (*(s + 126) != 120) {
      return 2;
    }
  }
  return 0;
}
