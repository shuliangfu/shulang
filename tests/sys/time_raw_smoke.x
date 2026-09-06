/**
 * Stage9 Cap residual 9.1.5 probe: std.time monotonic/wall/sleep/rfc3339
 * without libc clock_gettime/nanosleep/gmtime_r on the product path
 * (runtime_time_os.o → xlang_time_cap.h Linux/Darwin raw syscalls + civil gmtime).
 *
 * Contract:
 *  - monotonic advances across a short sleep
 *  - wall seconds look like a Unix epoch (after 2020)
 *  - RFC3339 format writes a trailing Z and length >= 20
 *
 * PLATFORM: SHARED gold (Linux + Darwin + Windows Cap 9.1.5).
 */
const time = import("std.time");

/**
 * Probe entry for Cap residual 9.1.5 time face.
 * @return i32 — 0 ok; 1 bad mono; 2 sleep did not advance; 3 bad wall; 4 bad rfc3339
 */
export function main(): i32 {
  let a: i64 = time.now_monotonic_ns();
  if (a <= 0) {
    return 1;
  }
  /* 2ms sleep — Cap nanosleep path */
  time.sleep_ms(2);
  let b: i64 = time.now_monotonic_ns();
  if (b <= a) {
    return 2;
  }
  let wall: i64 = time.now_wall_sec();
  /* After 2020-01-01 UTC */
  if (wall < 1577836800) {
    return 3;
  }
  let buf: u8[32] = [];
  let n: i32 = time.format_wall_rfc3339(&buf[0], 32);
  if (n < 20) {
    return 4;
  }
  /* Expect trailing 'Z' at last written char (index n-1). */
  if (buf[n - 1] != 90) {
    return 4;
  }
  return 0;
}
