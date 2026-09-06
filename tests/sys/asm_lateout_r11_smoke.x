/**
 * Stage10 10.2.3 probe: lateout from Windows x64 / SysV volatile scratch (r11).
 * Expect: mov $7 → rax; mov rax→r11; nop; mov r11→rax; store → x; return 42.
 * PLATFORM: SHARED source · WINDOWS x64 / LINUX|x86_64.
 */
export function main(): i32 {
  let x: i32 = 0;
  unsafe {
    asm!("nop", in("r11") 7, lateout("r11") x);
  }
  if (x == 7) {
    return 42;
  }
  return 1;
}
