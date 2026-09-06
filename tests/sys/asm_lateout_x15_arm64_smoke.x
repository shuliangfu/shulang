/**
 * Stage10 10.2.2 slice3 probe: in/lateout with AAPCS64 volatile scratch x15.
 * Expect: mov x15, x0; nop; mov x0, x15; store -> x; return 42.
 * PLATFORM: SHARED source · aarch64 emit · MACOS|arm64 native run · LINUX|aarch64 encode.
 */
export function main(): i32 {
  let x: i32 = 0;
  unsafe {
    asm!("nop", in("x15") 15, lateout("x15") x);
  }
  if (x == 15) {
    return 42;
  }
  return 1;
}
