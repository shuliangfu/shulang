// wave943 (9.4.3 slice) · main(int argc) C-ABI signature accepted end to end.
// Build path: ./m1.bin            -> exit 7 (argc==1 < 2)
//             ./m1.bin anything   -> exit 42
// Run  path: `xlang run m1.x`     -> exit 7; `xlang run m1.x anything` -> exit 42
// PLATFORM: SHARED — macOS dyld register main + Ubuntu glibc crt1.
function main(argc: i32, argv: **u8): i32 {
  if (argc < 2) { return 7; }
  return 42;
}
