// wave943 (9.4.3 v1) · multiple user positionals survive in order with
// interleaved value-taking driver flags:
//   xlang run m5.x a -O 2 b -backend asm c -> argc==4, argv[1..3]=="a","b","c"
// "2"/"asm" are flag values (driver-owned, skipped); "a","b","c" forwarded.
// Discrimination: wrong argc -> 7 (leak or over-skip); null slot -> 8;
// byte mismatch in argv[1]/argv[2]/argv[3] -> 9/10/11, 12/13/14, 15/16/17.
// PLATFORM: SHARED.
function main(argc: i32, argv: **u8): i32 {
  if (argc != 4) { return 7; }
  let p0: *u8 = 0 as *u8;
  let p1: *u8 = 0 as *u8;
  let p2: *u8 = 0 as *u8;
  unsafe {
    p0 = argv[1];
    p1 = argv[2];
    p2 = argv[3];
  }
  if (p0 == 0 as *u8) { return 8; }
  if (p1 == 0 as *u8) { return 8; }
  if (p2 == 0 as *u8) { return 8; }
  unsafe {
    if (p0[0] != 97) { return 9; }
    if (p0[1] != 0) { return 10; }
    if (p1[0] != 98) { return 12; }
    if (p1[1] != 0) { return 13; }
    if (p2[0] != 99) { return 15; }
    if (p2[1] != 0) { return 16; }
  }
  return 42;
}
