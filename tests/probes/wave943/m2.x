// wave943 (9.4.3 core) · argv content access: argv[1] must equal "hi".
//   argc<2 -> 7; argc>2 -> 43; argv[1] null -> 8; byte mismatches -> 9/10/11.
// Build: ./m2.bin hi -> 42 · ./m2.bin -> 7 · ./m2.bin hi extra -> 43
// Run:   `xlang run m2.x hi` -> 42 (driver forwards user positionals after
//        the .x source path; driver flags and the injected -o pair stay
//        driver-owned). PLATFORM: SHARED.
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
