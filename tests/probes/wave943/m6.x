// wave943 (9.4.3 v1) · dangling value-taking flag must not eat the injected
// "-o <temp>" tail pair (parse-layer dangling-value guard):
//   xlang run m6.x hi -L   -> argc==2, argv[1]=="hi" -> 42
// Why: driver_argv_ensure_run_o appends "-o <temp>" AFTER the user argv; the
// parse layers (main.x driver_argv_parse_x_path/_x, rt_compile step_c, the
// apply_*_next_c helpers, and their C twins/pins) now consult
// driver_compile_argv_next_is_value_c — argv[i+1] must exist, be non-empty,
// and not start with '-' before a value-taking flag consumes it — so the
// dangling "-L" is skipped standalone, the injected -o pair stays
// driver-owned, and the child argv keeps only "hi". PLATFORM: SHARED.
// Discrimination: temp path leaked -> argc>2 -> 43; "hi" lost -> argc<2 -> 7;
// argv[1] wrong bytes -> 9/10/11; argv[1] null -> 8.
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
