// wave927 · std 红簇 skip-emit read_fixed_fd / write_fixed_fd
// Product-path pin: leftover unique asm -o must resolve
// std_io_read_fixed_fd / std_io_write_fixed_fd (std.io is skip-emitted).
// Authority body ≡ std/io/mod.x → xlang_io_{read,write}_fixed(fd as usize).
// Current always-on weak xlang_io_*_fixed returns -1 (no io.o body).
// Unix $? is 8-bit: cases stay in 1..7.
// PLATFORM: SHARED — Darwin + Ubuntu product asm -o.

const io = import("std.io");

/**
 * Pin skip-emit read_fixed_fd / write_fixed_fd link and -1 fallback.
 * @return i32 — 0 pass, 1..7 first failing pin
 */
function main(): i32 {
  // Invalid fd / empty span: weak xlang_io_*_fixed returns -1.
  let r: i32 = io.read_fixed_fd(-1, 0 as u32, 0 as usize, 0 as usize, 0 as u32);
  if (r != (0 - 1)) {
    return 1;
  }
  let w: i32 = io.write_fixed_fd(-1, 0 as u32, 0 as usize, 0 as usize, 0 as u32);
  if (w != (0 - 1)) {
    return 2;
  }
  // Zero-length on fd 0 must still resolve (not UNDEF); same -1 fallback.
  let r0: i32 = io.read_fixed_fd(0, 0 as u32, 0 as usize, 0 as usize, 0 as u32);
  if (r0 != (0 - 1)) {
    return 3;
  }
  let w1: i32 = io.write_fixed_fd(1, 0 as u32, 0 as usize, 0 as usize, 0 as u32);
  if (w1 != (0 - 1)) {
    return 4;
  }
  return 0;
}
