/**
 * Stage9 Cap residual 9.1.10 probe: directory walk without libc opendir
 * (std.fs → fs formal merge → xlang_dir_cap.h).
 *
 * Contract: open "." ; read at least one entry; close succeeds.
 * PLATFORM: SHARED gold (Linux + Darwin Cap 9.1.10).
 */
const fs = import("std.fs");

/**
 * Probe entry for Cap residual 9.1.10 dir face.
 * @return i32 — 0 ok; 1 bad open; 2 bad read; 3 bad close
 */
export function main(): i32 {
  let h: i64 = 0;
  let rc: i32 = 0;
  let nread: i32 = 0;
  let is_dir: i32 = 0;
  let name: [256]u8;
  let path: [2]u8;
  path[0] = 46; /* '.' */
  path[1] = 0;
  h = fs.dir_open(&path[0]);
  if (h < 0) {
    return 1;
  }
  nread = fs.dir_read(h, &name[0], 256, &is_dir);
  if (nread < 1) {
    rc = fs.dir_close(h);
    return 2;
  }
  rc = fs.dir_close(h);
  if (rc != 0) {
    return 3;
  }
  return 0;
}
