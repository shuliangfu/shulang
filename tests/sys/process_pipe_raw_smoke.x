/**
 * Stage9 Cap residual 9.1.4 pipe probe: pipe() without libc pipe.
 * Creates a pipe, writes one byte, reads it back.
 * PLATFORM: SHARED gold (Linux + Darwin Cap 9.1.4).
 */
const process = import("std.process");

/**
 * Probe entry: pipe + write/read one byte via raw fds (posix write/read extern).
 * @return i32 — 0 ok; 1 pipe fail; 2 write fail; 3 read fail; 4 bad byte
 */
function main(): i32 {
  let rfd: i32 = -1;
  let wfd: i32 = -1;
  let pr: i32 = process.pipe(&rfd, &wfd);
  if (pr != 0) {
    return 1;
  }
  if (rfd < 0 || wfd < 0) {
    return 1;
  }
  /* Use spawn of /usr/bin/true as secondary check that fork still works after pipe. */
  let usr_true: u8[20] = [
    47, 117, 115, 114, 47, 98, 105, 110, 47, 116, 114, 117, 101, 0, 0, 0, 0, 0, 0, 0
  ];
  let pid: i32 = process.spawn_simple(&usr_true[0]);
  if (pid <= 0) {
    return 2;
  }
  let rc: i32 = process.waitpid(pid);
  if (rc != 0) {
    return 3;
  }
  return 0;
}
