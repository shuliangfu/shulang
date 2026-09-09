// wave943 (9.4.3 v1) · value-taking driver flags after the .x source path must
// not leak their separate value into the child argv (flag-value table:
// -o/-O/-L/-backend/-target/-target-cpu; parse authorities advance i+2 for
// these). Every shape below must yield argc==2 with argv[1]=="hi".
//   xlang run m4.x -backend asm hi                 -> 42 ("asm" not forwarded)
//   xlang run m4.x -O 2 hi                         -> 42
//   xlang run m4.x -L /tmp hi                      -> 42
//   xlang run m4.x -target <host triple> hi        -> 42 (Darwin aarch64-apple-darwin
//                                                     / Ubuntu x86_64-linux-gnu — a
//                                                     foreign arch triple legitimately
//                                                     cross-emits and fails the host ld)
//   xlang run m4.x -target-cpu native hi           -> 42
// Attached forms stay standalone flags: xlang run m4.x -O1 hi -> 42.
// Discrimination: value leaked -> argc>2 -> 43; nothing forwarded -> argc<2 -> 7;
// argv[1] wrong bytes -> 9/10/11; argv[1] null -> 8. PLATFORM: SHARED.
function main(argc: i32, argv: **u8): i32 {
  if (argc < 2) { return 7; }
  if (argc > 2) { return 43; }
  let p: *u8 = 0 as *u8;
  unsafe { p = argv[1]; }
  if (p == 0 as *u8) { return 8; }
  unsafe {
    if (p[0] != 104) { return 9; }
    if (p[1] != 105) { return 10; }
    if (p[2] != 0) { return 11; }
  }
  return 42;
}
