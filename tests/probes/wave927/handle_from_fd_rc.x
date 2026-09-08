// wave927 · std 红簇 skip-emit handle_from_fd
// Product-path pin: io_backend.handle_from_fd must be a real T in the
// user object (not skip-emitted), and fd identity is the handle.
// Unix $? is 8-bit: cases stay in 1..7.
// PLATFORM: SHARED — Darwin + Ubuntu product asm -o.

const io_backend = import("std.io.backend");

/**
 * Pin handle_from_fd(fd, unused) == fd as usize.
 * @return i32 — 0 pass, 1..7 first failing pin
 */
function main(): i32 {
  let h0: usize = io_backend.handle_from_fd(0, 0);
  if (h0 != 0 as usize) {
    return 1;
  }
  let h1: usize = io_backend.handle_from_fd(1, 0);
  if (h1 != 1 as usize) {
    return 2;
  }
  let h2: usize = io_backend.handle_from_fd(2, 99);
  if (h2 != 2 as usize) {
    return 3;
  }
  let hn: usize = io_backend.handle_from_fd(-1, 0);
  if (hn != (0 as usize - 1 as usize)) {
    return 4;
  }
  return 0;
}
