/**
 * Stage9 Cap residual 9.1.4 probe: spawn_simple + waitpid without libc fork/waitpid.
 * Product: process_*_c → Linux/Darwin raw fork/execve/wait4 (xlang_process_cap).
 * PLATFORM: SHARED gold (Linux + Darwin Cap 9.1.4).
 */
const process = import("std.process");

/**
 * Spawn /usr/bin/true (or /bin/true) and wait for exit 0.
 * @return i32 — 0 ok; 1 spawn fail; 2 wait non-zero
 */
function main(): i32 {
  let usr_true: u8[20] = [
    47, 117, 115, 114, 47, 98, 105, 110, 47, 116, 114, 117, 101, 0, 0, 0, 0, 0, 0, 0
  ];
  let bin_true: u8[16] = [47, 98, 105, 110, 47, 116, 114, 117, 101, 0, 0, 0, 0, 0, 0, 0];
  let pid: i32 = process.spawn_simple(&usr_true[0]);
  if (pid <= 0) {
    pid = process.spawn_simple(&bin_true[0]);
  }
  if (pid <= 0) {
    return 1;
  }
  let rc: i32 = process.waitpid(pid);
  if (rc != 0) {
    return 2;
  }
  return 0;
}
