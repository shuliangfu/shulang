/**
 * Stage10 10.2.3 probe: pause spinloop hint (x86 F3 90 / aarch64 yield).
 * Expect: emits pause on x86_64 or yield on aarch64, returns 42.
 * PLATFORM: SHARED source · WINDOWS x64 / LINUX|x86_64 / MACOS|arm64.
 */
export function main(): i32 {
  unsafe {
    asm!("pause");
  }
  return 42;
}
