/**
 * Cap 10.7.1 language slice7–13 smoke: va Cap builtins + arity + host-cc/runtime.
 *
 * Typeck sees export-extern faces; codegen rewrites call sites to xlang_va_*.
 * VaList lowers as xlang_va_list (emit_header includes xlang_va_cap.h).
 * slice8: call sites may pass trailing args beyond named formals.
 * slice9: -E host-cc run must exit 42 (first variadic i32).
 * slice13: also exercise va_arg_i64 + va_arg_ptr (asm Cap qword load).
 * slice14: typed turbofish va_arg<T>(ap) (G.7 size_of<T> type-arg sidecar).
 * slice16: va_arg<f32>/va_arg<f64> (XMM/NEON spill + C float→double promote).
 * slice17: GP stack extras beyond SysV 6 GP / AAPCS 8 GP (copy at va_start).
 * PLATFORM: SHARED — L2 gate; Ubuntu gold.
 */

/**
 * Cap face: initialize ap after named last parameter.
 * Codegen emits xlang_va_start — not a real libc call.
 * @param ap Cap VaList local (host-C xlang_va_list).
 * @param last Named last parameter of the enclosing variadic function.
 */
export extern function va_start(ap: VaList, last: i32): void;

/**
 * Cap face: tear down ap.
 * @param ap Cap VaList local.
 */
export extern function va_end(ap: VaList): void;

/**
 * Cap face: fetch next i32 from ap (typed helper; full va_arg(ap,T) deferred).
 * @param ap Cap VaList local.
 * @return Next variadic i32.
 */
export extern function va_arg_i32(ap: VaList): i32;

/**
 * Cap face: fetch next i64 from ap (typed helper; SysV 8-byte slot).
 * @param ap Cap VaList local.
 * @return Next variadic i64.
 */
export extern function va_arg_i64(ap: VaList): i64;

/**
 * Cap face: fetch next pointer from ap (typed helper; SysV GP slot).
 * @param ap Cap VaList local.
 * @return Next variadic *u8.
 */
export extern function va_arg_ptr(ap: VaList): *u8;

/**
 * Cap 10.7.1 slice14: typed va_arg<T>(ap) — turbofish type arg, not C va_arg(ap,T).
 * Generic body is a typeck/host-C face only (never executed); call sites rewrite
 * to Cap xlang_va_arg. Null-deref return compiles for any T without panic FFI.
 * @param ap Cap VaList local (unused in the face body).
 * @return Next variadic value of T (i32 / i64 / *u8 / f32 / f64; stack extras too).
 */
export function va_arg<T>(ap: VaList): T {
  unsafe {
    let p: *T = 0 as *T;
    return *p;
  }
}

/**
 * Variadic probe: i32, i64, *i32, f32, f64, then four more i32 (two fill
 * remaining SysV GP, two are stack extras). Expect exit 42.
 * @param n Named last parameter (required by Cap va_start).
 * @return 42 on success; 1..9 on mismatch of each slot.
 */
export function lang_va_cap_probe(n: i32, ...): i32 {
  let ap: VaList;
  va_start(ap, n);
  let a: i32 = va_arg<i32>(ap);
  let b: i64 = va_arg<i64>(ap);
  let p: *u8 = va_arg<*u8>(ap);
  let xf: f32 = va_arg<f32>(ap);
  let xd: f64 = va_arg<f64>(ap);
  /* Extra GP slots: same T as `a` (five va_arg<i32> in one TU). host-C must
   * emit one va_arg__VaList_i32 (combo dedup via type_refs_same_for_mono). */
  let e0: i32 = va_arg<i32>(ap);
  let e1: i32 = va_arg<i32>(ap);
  let e2: i32 = va_arg<i32>(ap);
  let e3: i32 = va_arg<i32>(ap);
  va_end(ap);
  if (a != 42) {
    return 1;
  }
  if (b != 42) {
    return 2;
  }
  unsafe {
    let pi: *i32 = p as *i32;
    if (*pi != 7) {
      return 3;
    }
  }
  if ((xf as i32) != 1) {
    return 4;
  }
  if ((xd as i32) != 2) {
    return 5;
  }
  if (e0 != 11) {
    return 6;
  }
  if (e1 != 22) {
    return 7;
  }
  if (e2 != 33) {
    return 8;
  }
  if (e3 != 44) {
    return 9;
  }
  return 42;
}

/**
 * Entry: trailing i32, i64, pointer, f32 1.0, f64 2.0, then 11/22 (GP) + 33/44 (stack).
 * SysV: named n + 42 + 42 + ptr + 11 + 22 fill rdi..r9; 33/44 at [rbp+16]/[rbp+24].
 */
export function main(): i32 {
  let m: i32 = 7;
  let xf: f32 = 1.0;
  let xd: f64 = 2.0;
  return lang_va_cap_probe(1, 42, 42, &m, xf, xd, 11, 22, 33, 44);
}
