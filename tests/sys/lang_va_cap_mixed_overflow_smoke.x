/**
 * Cap 10.7.1 slice18 smoke: mixed GP+FP overflow on the shared stack.
 *
 * SysV: 6 named i32 fill rdi..r9; 8 named f64 fill xmm0..7; trailing
 * i32/f64/i32/f64 sit at [rbp+16] and must share one overflow cursor.
 * Independent GP-ov/FP-ov copies (slice17) would reread the same cells.
 * Two va_arg<f64> in this TU: host-C must emit one va_arg__VaList_f64
 * (combo dedup; same residual as multi va_arg<i32>). Product `-o` + host-C.
 * PLATFORM: SHARED — L2 gate; Ubuntu gold (x86_64 SysV).
 */

/**
 * Cap face: initialize ap after named last parameter.
 * @param ap Cap VaList local.
 * @param last Named last parameter of the enclosing variadic function.
 */
export extern function va_start(ap: VaList, last: f64): void;

/**
 * Cap face: tear down ap.
 * @param ap Cap VaList local.
 */
export extern function va_end(ap: VaList): void;

/**
 * Cap face: fetch next i32 from ap.
 * @param ap Cap VaList local.
 * @return Next variadic i32.
 */
export extern function va_arg_i32(ap: VaList): i32;

/**
 * Cap 10.7.1 slice14: typed va_arg<T>(ap). Used here for f64 extras.
 * @param ap Cap VaList local (unused in the face body).
 * @return Next variadic value of T.
 */
export function va_arg<T>(ap: VaList): T {
  unsafe {
    let p: *T = 0 as *T;
    return *p;
  }
}

/**
 * Mixed overflow probe: 6 GP + 8 FP named, then 33, 3.0, 44, 4.0 on the
 * shared overflow stack. Expect 42.
 * @param a0 First named GP (fills SysV rdi; ignored besides occupancy).
 * @param a1 Named GP.
 * @param a2 Named GP.
 * @param a3 Named GP.
 * @param a4 Named GP.
 * @param a5 Last named GP (SysV r9).
 * @param f0 First named FP (xmm0).
 * @param f1 Named FP.
 * @param f2 Named FP.
 * @param f3 Named FP.
 * @param f4 Named FP.
 * @param f5 Named FP.
 * @param f6 Named FP.
 * @param f7 Last named FP (xmm7); va_start last.
 * @return 42 on success; 10..13 on mixed-slot mismatch.
 */
export function lang_va_cap_probe_mixed(
  a0: i32, a1: i32, a2: i32, a3: i32, a4: i32, a5: i32,
  f0: f64, f1: f64, f2: f64, f3: f64, f4: f64, f5: f64, f6: f64, f7: f64,
  ...
): i32 {
  let ap: VaList;
  va_start(ap, f7);
  let e0: i32 = va_arg_i32(ap);
  let e1: f64 = va_arg<f64>(ap);
  let e2: i32 = va_arg_i32(ap);
  let e3: f64 = va_arg<f64>(ap);
  va_end(ap);
  if (e0 != 33) {
    return 10;
  }
  if ((e1 as i32) != 3) {
    return 11;
  }
  if (e2 != 44) {
    return 12;
  }
  if ((e3 as i32) != 4) {
    return 13;
  }
  return 42;
}

/**
 * Entry: 6 GP + 8 FP named, then mixed extras 33 / 3.0 / 44 / 4.0.
 */
export function main(): i32 {
  let z: f64 = 1.0;
  return lang_va_cap_probe_mixed(
    0, 0, 0, 0, 0, 0,
    z, z, z, z, z, z, z, z,
    33, 3.0, 44, 4.0
  );
}
