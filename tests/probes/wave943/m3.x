// wave943 (9.4.3 slice) · argv[0] is non-null at program start (C convention:
// av[0] = product exe path; run path execs with av[0] = exe as well).
// Expected: exit 42 on any invocation. PLATFORM: SHARED.
function main(argc: i32, argv: **u8): i32 {
  if (argc < 1) { return 6; }
  unsafe {
    if (argv[0] == 0 as *u8) { return 9; }
  }
  return 42;
}
