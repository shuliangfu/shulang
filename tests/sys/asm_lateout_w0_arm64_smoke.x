/**
 * Stage10 10.2.2 slice3 probe: in/lateout with AAPCS64 32-bit register w0.
 * Expect: value already in x0; nop; store -> x; return 42.
 * PLATFORM: SHARED source · aarch64 emit · MACOS|arm64 native run · LINUX|aarch64 encode.
 */
export function main(): i32 {
  let x: i32 = 0;
  unsafe {
    asm!("nop", in("w0") 42, lateout("w0") x);
  }
  if (x == 42) {
    return 42;
  }
  return 1;
}
