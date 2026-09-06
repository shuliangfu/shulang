/**
 * Stage10 10.2.3 probe: int3 breakpoint trap instruction (x86 CC / aarch64 brk #0).
 * Expect: emits int3 on x86_64 or brk #0 on aarch64.
 * PLATFORM: SHARED source · WINDOWS x64 / LINUX|x86_64 / MACOS|arm64.
 */
function debug_trap(): i32 {
  unsafe {
    asm!("int3");
  }
  return 0;
}

export function main(): i32 {
  // Do not execute trap at runtime unless requested.
  let should_trap: i32 = 0;
  if (should_trap != 0) {
    debug_trap();
  }
  return 42;
}
