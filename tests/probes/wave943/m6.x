// wave943 (9.4.3 v1) · REPRODUCER for the carded parse-layer dangling-value
// defect (compile side, NOT a forwarding issue):
//   xlang run m6.x hi -backend   -> 42 expected; 127 today (card open)
// What happens: driver_argv_ensure_run_o appends "-o <temp>" after the user
// argv, and the parse layer (main.x driver_argv_parse_x_path / the rt_compile
// C twins) consumes argv[i+1] UNCONDITIONALLY for value-taking flags, so a
// dangling "-backend"/"-L"/"-target"/"-O" eats the injected "-o" as its value
// at compile time; the product is never linked to the temp path and the exec
// funnel dies with execv ENOENT (127). The forwarding-side consume guard in
// xlang_driver_exec_spawn_wait (next must not start with '-') is already
// correct and becomes load-bearing once the parse card is fixed. This probe
// turns green (42) together with that parse-layer card. PLATFORM: SHARED.
// Discrimination: after the fix, temp path leaked -> argc>2 -> 43; "hi" lost
// -> argc<2 -> 7; argv[1] wrong bytes -> 9/10/11; argv[1] null -> 8.
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
