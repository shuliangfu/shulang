// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_math_libm.x — R2 full mode public API
// PLATFORM: SHARED
//
// This module provides libm (math library) glue functions for Xlang.
// All functions use f64 (C double) as the primary floating-point type.
//
// Public APIs: #[no_mangle] math_*_c (exact-7 bit-level + fdlibm ports).
// Host-libm math_*_impl splices removed (9.2.4). fenv still bridges to
// C rest (fenv.h; standing, language-limit like 9.3.4).
// C cold twins: seeds/runtime_math_libm.from_x.c under
// #ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X.
//
// libm functions: floor/ceil/trunc/round/sin/cos/tan/asin/acos/atan/atan2/
//   sqrt/cbrt/pow/exp/log/fabs/signum/fmin/fmax/erf/erfc/log1p/expm1
// 9.2.4 exact-7 (floor/ceil/trunc/round/fabs/fmin/fmax): full .x bit-level
//   implementations on the product path (no libm); host-libm math_*_impl
//   splices removed. The seed keeps same-semantics C cold twins guarded
//   by #ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X; rem_pio2 reuses
//   math_floor_c / math_fabs_c (G.7).
// 9.2.4 exp/log (2026-09-08): fdlibm e_exp.c / e_log.c full .x ports (no
//   libm); seed keeps same-semantics fdlibm C cold twins under the same guard
// 9.2.4 sqrt/cbrt (2026-09-08): fdlibm e_sqrt.c / s_cbrt.c full .x ports (no
//   libm); seed keeps same-semantics C cold twins under the same guard
// 9.2.4 expm1/log1p (2026-09-08): fdlibm s_expm1.c / s_log1p.c full .x ports
//   (no libm); seed keeps same-semantics C cold twins under the same guard
// 9.2.4 sin/cos/tan (2026-09-08): fdlibm s_sin.c / s_cos.c / s_tan.c plus
//   k_sin/k_cos/k_tan + e_rem_pio2 / k_rem_pio2 full .x ports (no libm);
//   seed keeps same-semantics C cold twins under the same guard
// 9.2.4 pow (2026-09-08): fdlibm e_pow.c full .x port (no libm); seed keeps
//   a same-semantics C cold twin under the same guard
// 9.2.4 asin/acos/atan (2026-09-08): fdlibm e_asin.c / e_acos.c / s_atan.c
//   full .x ports (no libm); seed keeps same-semantics C cold twins under
//   the same guard.
// 9.2.4 atan2 (2026-09-08): fdlibm e_atan2.c full .x port (no libm); reuses
//   math_atan_c (G.7); seed keeps a same-semantics C cold twin under the
//   same guard.
// 9.2.4 erf/erfc (2026-09-08): fdlibm s_erf.c / s_erfc.c full .x ports (no
//   libm); shared P/Q, P1/Q1, R1/S1, R2/S2 rationals plus the two-exp
//   tail (G.7); seed keeps same-semantics C cold twins under the same
//   guard.
// fenv functions: mask_to_fe/fe_to_mask/emit_cap_report/available/test/clear/raise/smoke
// special: special_near (full .x impl), special_smoke_c (seed test)

// === libm: host-libm math_*_impl splices removed (9.2.4) ===

/* 9.2.4 exact-7 (2026-09-08): bit-level math_floor_c / math_ceil_c /
 * math_trunc_c / math_round_c / math_fabs_c / math_fmin_c / math_fmax_c
 * on the product path; math_*_impl host-libm splices removed
 * (same-semantics C cold twins live in the guarded seed block). */
/* 9.2.4 sin/cos/tan (2026-09-08): fdlibm s_sin.c / s_cos.c / s_tan.c full
 * .x ports on the product path; math_sin_impl / math_cos_impl /
 * math_tan_impl libm splices removed (same-semantics C cold twins live
 * in the guarded seed block). */
/* 9.2.4 asin/acos/atan (2026-09-08): fdlibm e_asin.c / e_acos.c / s_atan.c
 * full .x ports on the product path; math_asin_impl / math_acos_impl /
 * math_atan_impl libm splices removed (same-semantics C cold twins live
 * in the guarded seed block). */
/* 9.2.4 atan2 (2026-09-08): fdlibm e_atan2.c full .x port on the product
 * path; math_atan2_impl libm splice removed (same-semantics C cold twin
 * lives in the guarded seed block). Reuses math_atan_c (G.7). */
/* 9.2.4 erf/erfc (2026-09-08): fdlibm s_erf.c / s_erfc.c full .x ports on
 * the product path; math_erf_impl / math_erfc_impl libm splices removed
 * (same-semantics C cold twins live in the guarded seed block). Shared
 * rationals + exp tail (G.7); reuses math_exp_c / math_fabs_c. */
/* 9.2.4 sqrt/cbrt (2026-09-08): fdlibm e_sqrt.c / s_cbrt.c full .x ports on
 * the product path; math_sqrt_impl / math_cbrt_impl libm splices removed
 * (same-semantics C cold twins live in the guarded seed block). */
/* 9.2.4 pow (2026-09-08): fdlibm e_pow.c full .x port on the product path;
 * math_pow_impl libm splice removed (same-semantics C cold twin lives in
 * the guarded seed block). */
/* 9.2.4 exp/log (2026-09-08): fdlibm e_exp.c / e_log.c full .x ports on the
 * product path; math_exp_impl / math_log_impl libm splices removed (their
 * same-semantics C cold twins live in the guarded seed block). */
/* 9.2.4 expm1/log1p (2026-09-08): fdlibm s_expm1.c / s_log1p.c full .x ports
 * on the product path; math_log1p_impl / math_expm1_impl libm splices
 * removed (same-semantics C cold twins live in the guarded seed block). */

// === fenv bridge declarations ===

export extern "C" function math_fenv_mask_to_fe_impl(mask: i32): i32;
export extern "C" function math_fenv_fe_to_mask_impl(fe: i32): i32;
export extern "C" function math_fenv_emit_cap_report_impl(avail: i32): void;

// === forward declarations for thin functions (called by rest/smoke) ===

export function math_special_near(a: f64, b: f64, eps: f64): i32;
export function math_fenv_mask_to_fe(mask: i32): i32;
export function math_fenv_fe_to_mask(fe: i32): i32;
export function math_fenv_emit_cap_report(avail: i32): void;
export function math_sqrt_c(x: f64): f64;

// === doc anchor ===

export function runtime_math_libm_x_doc_anchor(): i32 {
  return 0;
}

// === math_signum: full .x implementation (no C bridge needed) ===

/// Returns signum of x: 1 if x > 0, -1 if x < 0, 0 if x == 0.
#[no_mangle]
export function math_signum_c(x: f64): f64 {
  if (x > 0.0) {
    return 1.0;
  }
  if (x < 0.0) {
    return -1.0;
  }
  return 0.0;
}

// === math_special_near: full .x implementation ===

/// Returns 1 if |a - b| <= eps, 0 otherwise.
#[no_mangle]
export function math_special_near(a: f64, b: f64, eps: f64): i32 {
  let d: f64 = a - b;
  if (d < 0.0) { d = 0.0 - d; }
  if (d <= eps) { return 1; }
  return 0;
}

// === libm public API wrappers (#[no_mangle]) ===
//
// exact-7 slice (9.2.4): floor/ceil/trunc/round/fabs/fmin/fmax are full .x
// bit-level implementations (fdlibm semantics, no libm call on the product
// path). Punning goes through pointer casts (let p: *u64 = &v as *u64), all
// masks are computed with shifts from a u64 one — no large hex literals.
// Remaining wrappers (erf/erfc) still forward to the C seed _impl
// bridges. exact-7 + exp/log + sqrt/cbrt + expm1/log1p + sin/cos/tan +
// pow + asin/acos/atan + atan2 are full .x; the seed keeps
// same-semantics cold twins under `#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X`
// (G.4: same commit, same semantics on both paths).

/**
 * Computes floor(x): the largest integral value <= x, returned as f64.
 * @param x f64 - input value (any bit pattern: zeros, subnormals, inf, NaN)
 * @return f64 - floor(x); preserves -0.0 for inputs in (-1, 0]; returns x
 *               unchanged for integers, +-inf and NaN
 * Bit-level algorithm: exponent field e = (bits >> 52) & 2047; |x| < 1
 * collapses to -1.0 / +0.0 (with -0.0 preserved); e >= 1075 means the value
 * already has no fractional mantissa bits (>= 2^52, inf, NaN); otherwise
 * clear the low (1075 - e) mantissa bits (truncation toward zero via pure
 * bit subtraction — no borrow), then step one more unit away from zero
 * (f64 subtract/add of 1.0 is exact for every non-integral |x| < 2^52).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_floor_c(x: f64): f64 {
  let v: f64 = x;
  let one: u64 = 1;
  let p: *u64 = &v as *u64;
  let bits: u64 = 0;
  unsafe { bits = *p; }
  let sign_bit: u64 = one << 63;
  let e: i32 = ((bits >> 52) & 2047) as i32;
  // inf / NaN: exponent all ones — nothing to round.
  if (e == 2047) {
    return v;
  }
  // |x| < 1: floor is -1.0 for negative non-zero, +0.0 for positive,
  // and +-0.0 is returned unchanged (sign of zero preserved).
  if (e < 1023) {
    if (bits == 0 || bits == sign_bit) {
      return v;
    }
    if ((bits & sign_bit) != 0) {
      return 0.0 - 1.0;
    }
    return 0.0;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if (e >= 1075) {
    return v;
  }
  // Clear the fractional mantissa bits: truncation toward zero. The low
  // (1075 - e) bits are below the integer boundary, so subtraction of the
  // masked-off part never borrows across the exponent field.
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if ((bits & frac_mask) == 0) {
    return v;
  }
  let t_bits: u64 = bits - (bits & frac_mask);
  unsafe { *p = t_bits; }
  // Negative non-integer: floor moves one unit toward -inf.
  if ((bits & sign_bit) != 0) {
    return v - 1.0;
  }
  return v;
}

/**
 * Computes ceil(x): the smallest integral value >= x, returned as f64.
 * @param x f64 - input value (any bit pattern: zeros, subnormals, inf, NaN)
 * @return f64 - ceil(x); preserves +-0.0 (ceil of (-1, 0) is -0.0); returns
 *               x unchanged for integers, +-inf and NaN
 * Bit-level mirror of math_floor_c: truncation by mantissa masking, then
 * positive non-integers step one unit toward +inf (exact f64 add of 1.0).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_ceil_c(x: f64): f64 {
  let v: f64 = x;
  let one: u64 = 1;
  let p: *u64 = &v as *u64;
  let bits: u64 = 0;
  unsafe { bits = *p; }
  let sign_bit: u64 = one << 63;
  let e: i32 = ((bits >> 52) & 2047) as i32;
  // inf / NaN: exponent all ones — nothing to round.
  if (e == 2047) {
    return v;
  }
  // |x| < 1: ceil is +1.0 for positive non-zero, -0.0 for negative
  // non-zero (sign of zero preserved per IEEE), +-0.0 unchanged.
  if (e < 1023) {
    if (bits == 0 || bits == sign_bit) {
      return v;
    }
    if ((bits & sign_bit) != 0) {
      unsafe { *p = bits & sign_bit; }
      return v;
    }
    return 1.0;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if (e >= 1075) {
    return v;
  }
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if ((bits & frac_mask) == 0) {
    return v;
  }
  let t_bits: u64 = bits - (bits & frac_mask);
  unsafe { *p = t_bits; }
  // Positive non-integer: ceil moves one unit toward +inf.
  if ((bits & sign_bit) == 0) {
    return v + 1.0;
  }
  return v;
}

/**
 * Computes trunc(x): the integral part of x with the fraction discarded
 * (round toward zero), returned as f64.
 * @param x f64 - input value (any bit pattern: zeros, subnormals, inf, NaN)
 * @return f64 - trunc(x); preserves the sign of zero (trunc(-0.5) = -0.0);
 *               returns x unchanged for integers, +-inf and NaN
 * Bit-level: |x| < 1 collapses to a signed zero (sign bit kept); exponent
 * >= 1075 means no fractional mantissa bits; otherwise mask off the low
 * (1075 - e) mantissa bits by pure u64 subtraction (no borrow).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_trunc_c(x: f64): f64 {
  let v: f64 = x;
  let one: u64 = 1;
  let p: *u64 = &v as *u64;
  let bits: u64 = 0;
  unsafe { bits = *p; }
  let sign_bit: u64 = one << 63;
  let e: i32 = ((bits >> 52) & 2047) as i32;
  // inf / NaN: exponent all ones — nothing to round.
  if (e == 2047) {
    return v;
  }
  // |x| < 1: trunc is a signed zero carrying the sign of x.
  if (e < 1023) {
    unsafe { *p = bits & sign_bit; }
    return v;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if (e >= 1075) {
    return v;
  }
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if ((bits & frac_mask) == 0) {
    return v;
  }
  unsafe { *p = bits - (bits & frac_mask); }
  return v;
}

/**
 * Computes round(x): round to the nearest integral value, with ties resolved
 * away from zero (C round semantics), returned as f64.
 * @param x f64 - input value (any bit pattern: zeros, subnormals, inf, NaN)
 * @return f64 - round(x); returns x unchanged for integers, +-inf and NaN
 * Algorithm: t = trunc(x) (bit-level via math_trunc_c), then the fraction
 * f = x - t is exact for every non-integral representable value; f >= 0.5
 * steps +1.0, f <= -0.5 steps -1.0 (both exact f64 adds on integral values
 * < 2^52). For inf/NaN the NaN comparisons are false and x flows through.
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_round_c(x: f64): f64 {
  let t: f64 = math_trunc_c(x);
  let frac: f64 = x - t;
  if (frac >= 0.5) {
    return t + 1.0;
  }
  if (frac <= 0.0 - 0.5) {
    return t - 1.0;
  }
  return t;
}

/**
 * Returns the high 32 bits of x as a signed i32 (fdlibm __HI).
 * @param x f64 - any bit pattern
 * @return i32 - bits 63..32 of x, two's-complement
 * PLATFORM: SHARED — pointer pun; no libm.
 */
function math_trig_hi(x: f64): i32 {
  let r: f64 = x;
  let bits: u64 = 0;
  unsafe {
    let p: *u64 = &r as *u64;
    bits = *p;
  }
  return ((bits >> 32) as u32) as i32;
}

/**
 * Returns the low 32 bits of x as a signed i32 (fdlibm __LO).
 * @param x f64 - any bit pattern
 * @return i32 - bits 31..0 of x, two's-complement
 * PLATFORM: SHARED — pointer pun; no libm.
 */
function math_trig_lo(x: f64): i32 {
  let r: f64 = x;
  let bits: u64 = 0;
  unsafe {
    let p: *u64 = &r as *u64;
    bits = *p;
  }
  return (bits as u32) as i32;
}

/**
 * Returns a copy of x with the high word replaced (fdlibm __HI(x)=h).
 * @param x f64 - source bits
 * @param h i32 - new high word
 * @return f64 - (h << 32) | lo(x)
 * PLATFORM: SHARED
 */
function math_trig_with_hi(x: f64, h: i32): f64 {
  let r: f64 = x;
  unsafe {
    let p: *u64 = &r as *u64;
    let b: u64 = *p;
    *p = (((h as u32) as u64) << 32) | (b & 4294967295);
  }
  return r;
}

/**
 * Returns a copy of x with the low word replaced (fdlibm __LO(x)=l).
 * @param x f64 - source bits
 * @param l i32 - new low word
 * @return f64 - hi(x) | (uint32)l
 * PLATFORM: SHARED
 */
function math_trig_with_lo(x: f64, l: i32): f64 {
  let r: f64 = x;
  unsafe {
    let p: *u64 = &r as *u64;
    let b: u64 = *p;
    *p = (b & 18446744069414584320) | ((l as u32) as u64);
  }
  return r;
}

/**
 * fdlibm s_scalbn.c: return x * 2^n via the exponent field.
 * Used only by kernel rem_pio2 (q0 is a modest integer).
 * @param x f64 - finite or special
 * @param n i32 - binary exponent adjustment
 * @return f64 - scalbn(x, n); overflow/underflow follow fdlibm huge/tiny
 * PLATFORM: SHARED freestanding
 */
function math_trig_scalbn(x: f64, n: i32): f64 {
  let two54: f64 = 18014398509481984 as f64;
  let twom54: f64 = 0.0;
  let huge: f64 = 0.0;
  let tiny: f64 = 0.0;
  unsafe {
    let p54: *u64 = &twom54 as *u64;
    *p54 = 4363988038922010624;     /* 0x3c90000000000000 = 2^-54 */
    let ph: *u64 = &huge as *u64;
    *ph = 9094988921128908188;      /* 0x7e37e43c8800759c = 1e300 */
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;       /* 0x01a56e1fc2f8f359 = 1e-300 */
  }
  let r: f64 = x;
  let bits: u64 = 0;
  unsafe {
    let p: *u64 = &r as *u64;
    bits = *p;
  }
  let hx: i32 = ((bits >> 32) as u32) as i32;
  let lx: i32 = (bits as u32) as i32;
  let k: i32 = (hx & 2146435072) >> 20;   /* 0x7ff00000 */
  if (k == 0) {
    if ((lx | (hx & 2147483647)) == 0) {
      return r;
    }
    r = r * two54;
    unsafe {
      let p2: *u64 = &r as *u64;
      bits = *p2;
    }
    hx = ((bits >> 32) as u32) as i32;
    k = ((hx & 2146435072) >> 20) - 54;
    if (n < (0 - 50000)) {
      return tiny * x;
    }
  }
  if (k == 2047) {
    return r + r;
  }
  k = k + n;
  if (k > 2046) {
    let s: f64 = huge;
    if (hx < 0) {
      s = 0.0 - huge;
    }
    return huge * s;
  }
  if (k > 0) {
    let nhx: u32 = ((hx as u32) & 2148532223) | ((k as u32) << 20); /* 0x800fffff */
    unsafe {
      let p3: *u64 = &r as *u64;
      *p3 = ((nhx as u64) << 32) | (bits & 4294967295);
    }
    return r;
  }
  if (k <= (0 - 54)) {
    if (n > 50000) {
      let s2: f64 = huge;
      if (hx < 0) {
        s2 = 0.0 - huge;
      }
      return huge * s2;
    }
    let s3: f64 = tiny;
    if (hx < 0) {
      s3 = 0.0 - tiny;
    }
    return tiny * s3;
  }
  k = k + 54;
  let nhx2: u32 = ((hx as u32) & 2148532223) | ((k as u32) << 20);
  unsafe {
    let p4: *u64 = &r as *u64;
    *p4 = ((nhx2 as u64) << 32) | (bits & 4294967295);
  }
  return r * twom54;
}

/**
 * 24-bit chunk i of 2/pi (fdlibm two_over_pi[i], 0..65).
 * @param i i32 - index; caller keeps 0 <= i <= 65
 * @return i32 - 24-bit chunk as a positive integer
 * PLATFORM: SHARED
 */
function math_two_over_pi(i: i32): i32 {
  let t: [66]i32 = [10680707, 7228996, 1387004, 2578385, 16069853, 12639074, 9804092, 4427841, 16666979, 11263675, 12935607, 2387514, 4345298, 14681673, 3074569, 13734428, 16653803, 1880361, 10960616, 8533493, 3062596, 8710556, 7349940, 6258241, 3772886, 3769171, 3798172, 8675211, 12450088, 3874808, 9961438, 366607, 15675153, 9132554, 7151469, 3571407, 2607881, 12013382, 4155038, 6285869, 7677882, 13102053, 15825725, 473591, 9065106, 15363067, 6271263, 9264392, 5636912, 4652155, 7056368, 13614112, 10155062, 1944035, 9527646, 15080200, 6658437, 6231200, 6832269, 16767104, 5075751, 3212806, 1398474, 7579849, 6349435, 12618859];
  return t[i];
}

/**
 * High word of n*pi/2 for n=1..32 (fdlibm npio2_hw[n-1]).
 * @param n i32 - n in 1..32
 * @return i32 - high word of n*pi/2
 * PLATFORM: SHARED
 */
function math_npio2_hw(n: i32): i32 {
  let t: [32]i32 = [1073291771, 1074340347, 1074977148, 1075388923, 1075800698, 1076025724, 1076231611, 1076437499, 1076643386, 1076849274, 1076971356, 1077074300, 1077177244, 1077280187, 1077383131, 1077486075, 1077589019, 1077691962, 1077794906, 1077897850, 1077968460, 1078019932, 1078071404, 1078122876, 1078174348, 1078225820, 1078277292, 1078328763, 1078380235, 1078431707, 1078483179, 1078534651];
  return t[n - 1];
}

/**
 * 24-bit chunk i of pi/2 (fdlibm PIo2[i], 0..7). Tiny chunks are
 * bit-punned (decimal literals cannot round-trip below ~1e-20).
 * @param i i32 - index 0..7
 * @return f64 - PIo2[i]
 * PLATFORM: SHARED
 */
function math_pio2_chunk(i: i32): f64 {
  let v: f64 = 0.0;
  let u: u64 = 0;
  if (i == 0) { u = 4609753056584663040; }
  if (i == 1) { u = 4500296887714185216; }
  if (i == 2) { u = 4393339057296375808; }
  if (i == 3) { u = 4285399695318056960; }
  if (i == 4) { u = 4174867106174599168; }
  if (i == 5) { u = 4069606033725587456; }
  if (i == 6) { u = 3955147982449410048; }
  if (i == 7) { u = 3848874662444400640; }
  unsafe {
    let p: *u64 = &v as *u64;
    *p = u;
  }
  return v;
}

/**
 * fdlibm __kernel_sin(x, y, iy): sin on [-pi/4, pi/4].
 * @param x f64 - primary reduced argument, |x| <= pi/4
 * @param y f64 - tail of x (0 when iy == 0)
 * @param iy i32 - 0 if y is zero, else 1
 * @return f64 - sin(x+y) on the primary range
 * PLATFORM: SHARED freestanding
 */
function math_kernel_sin(x: f64, y: f64, iy: i32): f64 {
  let half: f64 = 0.5;
  let s1: f64 = 0.0 - 0.16666666666666632435;            /* 0xbfc5555555555549 */
  let s2: f64 = 0.0083333333333224894612;                /* 0x3f8111111110f8a6 */
  let s3: f64 = 0.0 - 0.00019841269829857949313;         /* 0xbf2a01a019c161d5 */
  let s4: f64 = 0.0000027557313707070067679;             /* 0x3ec71de357b1fe7d */
  let s5: f64 = 0.0 - 0.00000002505076025340686342;      /* 0xbe5ae5e68a2b9ceb */
  let s6: f64 = 0.00000000015896909952115501022;         /* 0x3de5d93a5acfd57c */
  let ix: i32 = math_trig_hi(x) & 2147483647;
  if (ix < 1044381696) {          /* |x| < 2^-27 (0x3e400000) */
    if ((x as i32) == 0) {
      return x;
    }
  }
  let z: f64 = x * x;
  let v: f64 = z * x;
  let r: f64 = s2 + z * (s3 + z * (s4 + z * (s5 + z * s6)));
  if (iy == 0) {
    return x + v * (s1 + z * r);
  }
  return x - ((z * (half * y - v * r) - y) - v * s1);
}

/**
 * fdlibm __kernel_cos(x, y): cos on [-pi/4, pi/4].
 * @param x f64 - primary reduced argument, |x| <= pi/4
 * @param y f64 - tail of x
 * @return f64 - cos(x+y) on the primary range
 * PLATFORM: SHARED freestanding
 */
function math_kernel_cos(x: f64, y: f64): f64 {
  let one: f64 = 1.0;
  let c1: f64 = 0.041666666666666601904;                 /* 0x3fa555555555554c */
  let c2: f64 = 0.0 - 0.0013888888888874109575;          /* 0xbf56c16c16c15177 */
  let c3: f64 = 0.000024801587289476729418;              /* 0x3efa01a019cb1590 */
  let c4: f64 = 0.0 - 0.00000027557314351390663303;      /* 0xbe927e4f809c52ad */
  let c5: f64 = 0.0000000020875723212981748279;          /* 0x3e21ee9ebdb4b1c4 */
  let c6: f64 = 0.0 - 0.000000000011359647557788194826;  /* 0xbda8fae9be8838d4 */
  let ix: i32 = math_trig_hi(x) & 2147483647;
  if (ix < 1044381696) {          /* |x| < 2^-27 */
    if ((x as i32) == 0) {
      return one;
    }
  }
  let z: f64 = x * x;
  let r: f64 = z * (c1 + z * (c2 + z * (c3 + z * (c4 + z * (c5 + z * c6)))));
  if (ix < 1070805811) {          /* |x| < 0.3 (0x3FD33333) */
    return one - (0.5 * z - (z * r - x * y));
  }
  let qx: f64 = 0.28125;
  if (ix <= 1072234496) {         /* x <= 0.78125 (0x3fe90000) */
    qx = math_trig_with_lo(math_trig_with_hi(0.0, ix - 2097152), 0);
  }
  let hz: f64 = 0.5 * z - qx;
  let a: f64 = one - qx;
  return a - (hz - (z * r - x * y));
}

/**
 * fdlibm __kernel_tan(x, y, iy): tan on [-pi/4, pi/4], or -1/tan when iy == -1.
 * @param x f64 - primary reduced argument
 * @param y f64 - tail of x
 * @param iy i32 - 1 -> tan, -1 -> -1/tan (odd quadrant)
 * @return f64 - tan(x+y) or -1/tan(x+y)
 * PLATFORM: SHARED freestanding
 */
function math_kernel_tan(x: f64, y: f64, iy: i32): f64 {
  let t0: f64 = 0.33333333333333409199;                  /* 0x3fd5555555555563 */
  let t1: f64 = 0.1333333333332012427;                   /* 0x3fc111111110fe7a */
  let t2: f64 = 0.053968253976226052138;                 /* 0x3faba1ba1bb341fe */
  let t3: f64 = 0.02186948829485954246;                  /* 0x3f9664f48406d637 */
  let t4: f64 = 0.0088632398235993000574;                /* 0x3f8226e3e96e8493 */
  let t5: f64 = 0.0035920791075913123536;                /* 0x3f6d6d22c9560328 */
  let t6: f64 = 0.0014562094543252902552;                /* 0x3f57dbc8fee08315 */
  let t7: f64 = 0.00058804124082026409687;               /* 0x3f4344d8f2f26501 */
  let t8: f64 = 0.00024646313481846990681;               /* 0x3f3026f71a8d1068 */
  let t9: f64 = 0.00007817944429395570923;               /* 0x3f147e88a03792a6 */
  let t10: f64 = 0.000071407249138260819031;             /* 0x3f12b80f32f0a7e9 */
  let t11: f64 = 0.0 - 0.000018558637485527545665;       /* 0xbef375cbdb605373 */
  let t12: f64 = 0.000025907305186363371288;             /* 0x3efb2a7074bf7ad4 */
  let one: f64 = 1.0;
  let pio4: f64 = 0.785398163397448279;                  /* 0x3fe921fb54442d18 */
  let pio4lo: f64 = 0.0;
  unsafe {
    let pp: *u64 = &pio4lo as *u64;
    *pp = 4359948597267291143;      /* 0x3c81a62633145c07 */
  }
  let xx: f64 = x;
  let yy: f64 = y;
  let hx: i32 = math_trig_hi(xx);
  let ix: i32 = hx & 2147483647;
  if (ix < 1043333120) {          /* |x| < 2^-28 (0x3e300000) */
    if ((xx as i32) == 0) {
      if (((ix | math_trig_lo(xx)) | (iy + 1)) == 0) {
        let ax: f64 = xx;
        unsafe {
          let pa: *u64 = &ax as *u64;
          *pa = *pa & 9223372036854775807;
        }
        return one / ax;
      }
      if (iy == 1) {
        return xx;
      }
      let w0: f64 = xx + yy;
      let z0: f64 = math_trig_with_lo(w0, 0);
      let v0: f64 = yy - (z0 - xx);
      let a0: f64 = (0.0 - one) / w0;
      let tt: f64 = math_trig_with_lo(a0, 0);
      let s0: f64 = one + tt * z0;
      return tt + a0 * (s0 + tt * v0);
    }
  }
  if (ix >= 1072010280) {         /* |x| >= 0.6744 (0x3FE59428) */
    if (hx < 0) {
      xx = 0.0 - xx;
      yy = 0.0 - yy;
    }
    let z1: f64 = pio4 - xx;
    let w1: f64 = pio4lo - yy;
    xx = z1 + w1;
    yy = 0.0;
  }
  let z: f64 = xx * xx;
  let w: f64 = z * z;
  let r: f64 = t1 + w * (t3 + w * (t5 + w * (t7 + w * (t9 + w * t11))));
  let v: f64 = z * (t2 + w * (t4 + w * (t6 + w * (t8 + w * (t10 + w * t12)))));
  let s: f64 = z * xx;
  r = yy + z * (s * (r + v) + yy);
  r = r + t0 * s;
  w = xx + r;
  if (ix >= 1072010280) {
    let vv: f64 = iy as f64;
    let sgn: i32 = 1 - ((((hx as u32) >> 30) & 2) as i32);
    return (sgn as f64) * (vv - 2.0 * (xx - (w * w / (w + vv) - r)));
  }
  if (iy == 1) {
    return w;
  }
  let z2: f64 = math_trig_with_lo(w, 0);
  let v2: f64 = r - (z2 - xx);
  let a2: f64 = (0.0 - 1.0) / w;
  let t2b: f64 = math_trig_with_lo(a2, 0);
  let s2: f64 = 1.0 + t2b * z2;
  return t2b + a2 * (s2 + t2b * v2);
}

/**
 * fdlibm __kernel_rem_pio2 for double precision (prec = 2).
 * Computes y[0]+y[1] = x - n*pi/2 with |y| <= pi/2; returns n mod 8.
 * Local arrays of 20 hold the 24-bit chunks (fdlibm f/q/iq/fq).
 * goto-recompute is a while flag (X has no goto).
 * @param tx0 f64 - 24-bit chunk 0 of |x|
 * @param tx1 f64 - chunk 1
 * @param tx2 f64 - chunk 2
 * @param e0 i32 - exponent of tx0 (ilogb(|x|)-23)
 * @param nx i32 - number of nonzero chunks (1..3)
 * @param y0 *f64 - out: primary reduced argument
 * @param y1 *f64 - out: tail
 * @return i32 - n & 7
 * PLATFORM: SHARED freestanding
 */
function math_kernel_rem_pio2(tx0: f64, tx1: f64, tx2: f64, e0: i32, nx: i32, y0: *f64, y1: *f64): i32 {
  let zero: f64 = 0.0;
  let one: f64 = 1.0;
  let two24: f64 = 16777216 as f64;
  let twon24: f64 = 0.000000059604644775390625;   /* 2^-24 */
  let jk: i32 = 4;   /* init_jk[2] for extended/double-tail */
  let jp: i32 = jk;
  let jx: i32 = nx - 1;
  let jv: i32 = (e0 - 3) / 24;
  if (jv < 0) {
    jv = 0;
  }
  let q0: i32 = e0 - 24 * (jv + 1);
  let f: [20]f64 = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  let q: [20]f64 = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  let fq: [20]f64 = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  let iq: [20]i32 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let j: i32 = jv - jx;
  let m: i32 = jx + jk;
  let i: i32 = 0;
  while (i <= m) {
    if (j < 0) {
      f[i] = zero;
    } else {
      f[i] = math_two_over_pi(j) as f64;
    }
    i = i + 1;
    j = j + 1;
  }
  i = 0;
  while (i <= jk) {
    let fw: f64 = 0.0;
    let jj: i32 = 0;
    while (jj <= jx) {
      let xj: f64 = tx0;
      if (jj == 1) {
        xj = tx1;
      }
      if (jj == 2) {
        xj = tx2;
      }
      fw = fw + xj * f[jx + i - jj];
      jj = jj + 1;
    }
    q[i] = fw;
    i = i + 1;
  }
  let jz: i32 = jk;
  let again: i32 = 1;
  let n: i32 = 0;
  let ih: i32 = 0;
  let z: f64 = 0.0;
  while (again == 1) {
    again = 0;
    i = 0;
    j = jz;
    z = q[jz];
    while (j > 0) {
      let fw2: f64 = ((twon24 * z) as i32) as f64;
      iq[i] = (z - two24 * fw2) as i32;
      z = q[j - 1] + fw2;
      i = i + 1;
      j = j - 1;
    }
    z = math_trig_scalbn(z, q0);
    z = z - 8.0 * math_floor_c(z * 0.125);
    n = z as i32;
    z = z - (n as f64);
    ih = 0;
    if (q0 > 0) {
      let sh: i32 = 24 - q0;
      i = iq[jz - 1] >> sh;
      n = n + i;
      iq[jz - 1] = iq[jz - 1] - (i << sh);
      ih = iq[jz - 1] >> (23 - q0);
    } else {
      if (q0 == 0) {
        ih = iq[jz - 1] >> 23;
      } else {
        if (z >= 0.5) {
          ih = 2;
        }
      }
    }
    if (ih > 0) {
      n = n + 1;
      let carry: i32 = 0;
      i = 0;
      while (i < jz) {
        j = iq[i];
        if (carry == 0) {
          if (j != 0) {
            carry = 1;
            iq[i] = 16777216 - j;
          }
        } else {
          iq[i] = 16777215 - j;
        }
        i = i + 1;
      }
      if (q0 > 0) {
        if (q0 == 1) {
          iq[jz - 1] = iq[jz - 1] & 8388607;
        } else {
          if (q0 == 2) {
            iq[jz - 1] = iq[jz - 1] & 4194303;
          }
        }
      }
      if (ih == 2) {
        z = one - z;
        if (carry != 0) {
          z = z - math_trig_scalbn(one, q0);
        }
      }
    }
    if (z == zero) {
      j = 0;
      i = jz - 1;
      while (i >= jk) {
        j = j | iq[i];
        i = i - 1;
      }
      if (j == 0) {
        let k: i32 = 1;
        while (iq[jk - k] == 0) {
          k = k + 1;
        }
        i = jz + 1;
        while (i <= (jz + k)) {
          f[jx + i] = math_two_over_pi(jv + i) as f64;
          let fw3: f64 = 0.0;
          let jj2: i32 = 0;
          while (jj2 <= jx) {
            let xj2: f64 = tx0;
            if (jj2 == 1) {
              xj2 = tx1;
            }
            if (jj2 == 2) {
              xj2 = tx2;
            }
            fw3 = fw3 + xj2 * f[jx + i - jj2];
            jj2 = jj2 + 1;
          }
          q[i] = fw3;
          i = i + 1;
        }
        jz = jz + k;
        again = 1;
      }
    }
  }
  if (z == 0.0) {
    jz = jz - 1;
    q0 = q0 - 24;
    while (iq[jz] == 0) {
      jz = jz - 1;
      q0 = q0 - 24;
    }
  } else {
    z = math_trig_scalbn(z, 0 - q0);
    if (z >= two24) {
      let fw4: f64 = ((twon24 * z) as i32) as f64;
      iq[jz] = (z - two24 * fw4) as i32;
      jz = jz + 1;
      q0 = q0 + 24;
      iq[jz] = (fw4 as i32);
    } else {
      iq[jz] = z as i32;
    }
  }
  let fw5: f64 = math_trig_scalbn(one, q0);
  i = jz;
  while (i >= 0) {
    q[i] = fw5 * (iq[i] as f64);
    fw5 = fw5 * twon24;
    i = i - 1;
  }
  i = jz;
  while (i >= 0) {
    let fw6: f64 = 0.0;
    let k2: i32 = 0;
    while ((k2 <= jp) && (k2 <= (jz - i))) {
      fw6 = fw6 + math_pio2_chunk(k2) * q[i + k2];
      k2 = k2 + 1;
    }
    fq[jz - i] = fw6;
    i = i - 1;
  }
  let fw7: f64 = 0.0;
  i = jz;
  while (i >= 0) {
    fw7 = fw7 + fq[i];
    i = i - 1;
  }
  if (ih == 0) {
    unsafe { *y0 = fw7; }
  } else {
    unsafe { *y0 = 0.0 - fw7; }
  }
  fw7 = fq[0] - fw7;
  i = 1;
  while (i <= jz) {
    fw7 = fw7 + fq[i];
    i = i + 1;
  }
  if (ih == 0) {
    unsafe { *y1 = fw7; }
  } else {
    unsafe { *y1 = 0.0 - fw7; }
  }
  return n & 7;
}

/**
 * fdlibm __ieee754_rem_pio2: reduce x to y0+y1 = x - n*pi/2 in [-pi/4, pi/4].
 * @param x f64 - argument
 * @param y0 *f64 - out primary
 * @param y1 *f64 - out tail
 * @return i32 - n (quadrant index; sign follows x)
 * PLATFORM: SHARED freestanding
 */
function math_rem_pio2(x: f64, y0: *f64, y1: *f64): i32 {
  let half: f64 = 0.5;
  let two24: f64 = 16777216 as f64;
  let invpio2: f64 = 0.63661977236758138243;             /* 0x3fe45f306dc9c883 */
  let pio2_1: f64 = 1.5707963267341256142;               /* 0x3ff921fb54400000 */
  let pio2_1t: f64 = 0.000000000060771005065061922493;   /* 0x3dd0b4611a626331 */
  let pio2_2: f64 = 0.000000000060771005063039659766;    /* 0x3dd0b4611a600000 */
  let pio2_2t: f64 = 0.0;
  let pio2_3: f64 = 0.0;
  let pio2_3t: f64 = 0.0;
  unsafe {
    let p2t: *u64 = &pio2_2t as *u64;
    *p2t = 4297306550709743731;     /* 0x3ba3198a2e037073 */
    let p3: *u64 = &pio2_3 as *u64;
    *p3 = 4297306550709518336;      /* 0x3ba3198a2e000000 */
    let p3t: *u64 = &pio2_3t as *u64;
    *p3t = 4142048980368378305;     /* 0x397b839a252049c1 */
  }
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  if (ix <= 1072243195) {         /* |x| ~<= pi/4 (0x3fe921fb) */
    unsafe { *y0 = x; *y1 = 0.0; }
    return 0;
  }
  if (ix < 1073928572) {          /* |x| < 3pi/4 (0x4002d97c) */
    if (hx > 0) {
      let z: f64 = x - pio2_1;
      if (ix != 1073291771) {     /* 0x3ff921fb */
        unsafe {
          *y0 = z - pio2_1t;
          *y1 = (z - *y0) - pio2_1t;
        }
      } else {
        z = z - pio2_2;
        unsafe {
          *y0 = z - pio2_2t;
          *y1 = (z - *y0) - pio2_2t;
        }
      }
      return 1;
    }
    let z2: f64 = x + pio2_1;
    if (ix != 1073291771) {
      unsafe {
        *y0 = z2 + pio2_1t;
        *y1 = (z2 - *y0) + pio2_1t;
      }
    } else {
      z2 = z2 + pio2_2;
      unsafe {
        *y0 = z2 + pio2_2t;
        *y1 = (z2 - *y0) + pio2_2t;
      }
    }
    return 0 - 1;
  }
  if (ix <= 1094263291) {         /* |x| ~<= 2^19*(pi/2) (0x413921fb) */
    let t: f64 = x;
    if (hx < 0) {
      t = 0.0 - x;
    }
    let n: i32 = (t * invpio2 + half) as i32;
    let fn: f64 = n as f64;
    let r: f64 = t - fn * pio2_1;
    let w: f64 = fn * pio2_1t;
    if ((n < 32) && (ix != math_npio2_hw(n))) {
      unsafe { *y0 = r - w; }
    } else {
      let jj: i32 = ix >> 20;
      unsafe { *y0 = r - w; }
      let i2: i32 = jj - ((math_trig_hi(unsafe { *y0 }) >> 20) & 2047);
      if (i2 > 16) {
        t = r;
        w = fn * pio2_2;
        r = t - w;
        w = fn * pio2_2t - ((t - r) - w);
        unsafe { *y0 = r - w; }
        i2 = jj - ((math_trig_hi(unsafe { *y0 }) >> 20) & 2047);
        if (i2 > 49) {
          t = r;
          w = fn * pio2_3;
          r = t - w;
          w = fn * pio2_3t - ((t - r) - w);
          unsafe { *y0 = r - w; }
        }
      }
    }
    unsafe { *y1 = (r - *y0) - w; }
    if (hx < 0) {
      unsafe { *y0 = 0.0 - *y0; *y1 = 0.0 - *y1; }
      return 0 - n;
    }
    return n;
  }
  if (ix >= 2146435072) {         /* inf or NaN */
    unsafe { *y0 = x - x; *y1 = x - x; }
    return 0;
  }
  let z3: f64 = math_trig_with_lo(0.0, math_trig_lo(x));
  let e0: i32 = (ix >> 20) - 1046;
  z3 = math_trig_with_hi(z3, ix - (e0 << 20));
  let tx0: f64 = (z3 as i32) as f64;
  z3 = (z3 - tx0) * two24;
  let tx1: f64 = (z3 as i32) as f64;
  z3 = (z3 - tx1) * two24;
  let tx2: f64 = z3;
  let nx: i32 = 3;
  if (tx2 == 0.0) {
    nx = 2;
    if (tx1 == 0.0) {
      nx = 1;
    }
  }
  let n2: i32 = math_kernel_rem_pio2(tx0, tx1, tx2, e0, nx, y0, y1);
  if (hx < 0) {
    unsafe { *y0 = 0.0 - *y0; *y1 = 0.0 - *y1; }
    return 0 - n2;
  }
  return n2;
}

/**
 * Computes sin(x): the sine of x, returned as f64.
 *
 * fdlibm s_sin.c port (Sun reference, error < 1 ulp):
 * 1. |x| ~<= pi/4 uses the degree-13 kernel directly (tail = 0).
 * 2. Inf/NaN returns NaN via x-x.
 * 3. Otherwise rem_pio2 reduces x to y0+y1 in [-pi/4, pi/4] and n = k mod 4
 *    selects (S, C, -S, -C) on the four quadrants.
 * Constants are Python-verified against the fdlibm hex comments.
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_sin_c(x: f64): f64 {
  let ix: i32 = math_trig_hi(x) & 2147483647;
  if (ix <= 1072243195) {         /* |x| ~<= pi/4 */
    return math_kernel_sin(x, 0.0, 0);
  }
  if (ix >= 2146435072) {         /* inf or NaN */
    return x - x;
  }
  let y0: f64 = 0.0;
  let y1: f64 = 0.0;
  let n: i32 = math_rem_pio2(x, &y0 as *f64, &y1 as *f64);
  let q: i32 = n & 3;
  if (q == 0) {
    return math_kernel_sin(y0, y1, 1);
  }
  if (q == 1) {
    return math_kernel_cos(y0, y1);
  }
  if (q == 2) {
    return 0.0 - math_kernel_sin(y0, y1, 1);
  }
  return 0.0 - math_kernel_cos(y0, y1);
}

/**
 * Computes cos(x): the cosine of x, returned as f64.
 *
 * fdlibm s_cos.c port (Sun reference, error < 1 ulp): same reduction as
 * sin; n mod 4 selects (C, -S, -C, S). A few inputs sit 1 ulp off
 * correctly-rounded host libm and are pinned to fdlibm (see trig_rc probe).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_cos_c(x: f64): f64 {
  let ix: i32 = math_trig_hi(x) & 2147483647;
  if (ix <= 1072243195) {
    return math_kernel_cos(x, 0.0);
  }
  if (ix >= 2146435072) {
    return x - x;
  }
  let y0: f64 = 0.0;
  let y1: f64 = 0.0;
  let n: i32 = math_rem_pio2(x, &y0 as *f64, &y1 as *f64);
  let q: i32 = n & 3;
  if (q == 0) {
    return math_kernel_cos(y0, y1);
  }
  if (q == 1) {
    return 0.0 - math_kernel_sin(y0, y1, 1);
  }
  if (q == 2) {
    return 0.0 - math_kernel_cos(y0, y1);
  }
  return math_kernel_sin(y0, y1, 1);
}

/**
 * Computes tan(x): the tangent of x, returned as f64.
 *
 * fdlibm s_tan.c port (Sun reference, error < 1 ulp): |x| ~<= pi/4 uses
 * the degree-27 kernel; otherwise rem_pio2 + kernel with iy = 1-2*(n&1)
 * (odd quadrants return -1/tan). A few inputs sit 1 ulp off host libm
 * and are pinned to fdlibm (see trig_rc probe).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_tan_c(x: f64): f64 {
  let ix: i32 = math_trig_hi(x) & 2147483647;
  if (ix <= 1072243195) {
    return math_kernel_tan(x, 0.0, 1);
  }
  if (ix >= 2146435072) {
    return x - x;
  }
  let y0: f64 = 0.0;
  let y1: f64 = 0.0;
  let n: i32 = math_rem_pio2(x, &y0 as *f64, &y1 as *f64);
  return math_kernel_tan(y0, y1, 1 - ((n & 1) << 1));
}


/**
 * fdlibm asin/acos rational R(t) = p(t)/q(t).
 * Horner evaluation of the degree-5/4 Remez approximant of
 * (asin(s)-s)/s^3 on t = s^2 (or t = (1-|x|)/2 on the |x|>=0.5 path).
 * Shared by math_asin_c and math_acos_c (G.7: one polynomial, two callers).
 * @param t f64 - s^2 or (1-|x|)/2; finite and in [0, 0.5]
 * @return f64 - p/q (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_asin_rational(t: f64): f64 {
  let pS0: f64 = 0.1666666666666666574148081281236954964697360992431640625; /* 0x3FC55555, 0x55555555 */
  let pS1: f64 = 0.0 - 0.325565818622400915405279420156148262321949005126953125; /* 0xBFD4D612, 0x03EB6F7D */
  let pS2: f64 = 0.2012125321348629258810802866719313897192478179931640625; /* 0x3FC9C155, 0x0E884455 */
  let pS3: f64 = 0.0 - 0.040055534500679411402668250730130239389836788177490234375; /* 0xBFA48228, 0xB5688F3B */
  let pS4: f64 = 0.000791534994289814532175686423443039529956877231597900390625; /* 0x3F49EFE0, 0x7501B288 */
  let pS5: f64 = 0.0000347933107596021167569506904460041596394148655235767364501953125; /* 0x3F023DE1, 0x0DFDF709 */
  let qS1: f64 = 0.0 - 2.403394911734414218784650074667297303676605224609375; /* 0xC0033A27, 0x1C8A2D4B */
  let qS2: f64 = 2.020945760233505694714040146209299564361572265625; /* 0x40002AE5, 0x9C598AC8 */
  let qS3: f64 = 0.0 - 0.68828397160545329303005246401880867779254913330078125; /* 0xBFE6066C, 0x1B8D0159 */
  let qS4: f64 = 0.0770381505559019352791239043654059059917926788330078125; /* 0x3FB3B8C5, 0xB12E9282 */
  let one: f64 = 1.0;
  let p: f64 = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
  let q: f64 = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
  return p / q;
}

/**
 * Computes asin(x): the inverse sine of x, returned in radians.
 *
 * fdlibm e_asin.c port (Sun reference, error < 1 ulp):
 * 1. |x| >= 1: asin(+-1) = +-pi/2 (inexact); |x|>1 or NaN -> (x-x)/(x-x).
 * 2. |x| < 0.5: tiny |x| < 2^-27 returns x (inexact if x!=0); else
 *    x + x*R(x^2) with R the shared Remez rational.
 * 3. 0.5 <= |x| < 1: pi/2 - 2*asin(sqrt((1-|x|)/2)). |x| > 0.975 uses the
 *    direct form; otherwise a hi/lo split of sqrt(z) (lo word cleared)
 *    keeps the subtraction exact. Sign of x is restored at the end.
 * Uses math_sqrt_c and math_trig_hi/lo/with_hi/with_lo (G.7). fabs is
 * defined later in this file, so |x| is recovered by clearing the sign
 * bit via math_trig_with_hi(x, ix).
 * A few inputs sit 1 ulp off correctly-rounded host libm and are pinned
 * to fdlibm (see invtrig_rc probe).
 * PLATFORM: SHARED freestanding (no libm).
 * @param x f64 - argument in [-1, 1] for a finite result
 * @return f64 - asin(x) in [-pi/2, pi/2] (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_asin_c(x: f64): f64 {
  let one: f64 = 1.0;
  let pio2_hi: f64 = 1.5707963267948965579989817342720925807952880859375; /* 0x3FF921FB, 0x54442D18 */
  let pio2_lo: f64 = 0.0000000000000000612323399573676603586882014729198302312846062338790032; /* 0x3C91A626, 0x33145C07 */
  let pio4_hi: f64 = 0.78539816339744827899949086713604629039764404296875; /* 0x3FE921FB, 0x54442D18 */
  let huge: f64 = 0.0;
  unsafe {
    let ph: *u64 = &huge as *u64;
    *ph = 9094988921128908188;      /* 0x7e37e43c8800759c = 1e300 */
  }
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  let t: f64 = 0.0;
  let w: f64 = 0.0;
  let c: f64 = 0.0;
  let r: f64 = 0.0;
  let s: f64 = 0.0;
  if (ix >= 1072693248) {           /* |x| >= 1 (0x3ff00000) */
    if (((ix - 1072693248) | math_trig_lo(x)) == 0) {
      return x * pio2_hi + x * pio2_lo;
    }
    return (x - x) / (x - x);
  } else if (ix < 1071644672) {     /* |x| < 0.5 (0x3fe00000) */
    if (ix < 1044381696) {          /* |x| < 2^-27 (0x3e400000) */
      if ((huge + x) > one) {
        return x;
      }
      return x;
    }
    t = x * x;
    w = math_asin_rational(t);
    return x + x * w;
  }
  /* 1 > |x| >= 0.5: restore abs via cleared sign bit (fabs lives later). */
  w = one - math_trig_with_hi(x, ix);
  t = w * 0.5;
  r = math_asin_rational(t);
  s = math_sqrt_c(t);
  if (ix >= 1072640819) {           /* |x| > 0.975 (0x3FEF3333) */
    t = pio2_hi - (2.0 * (s + s * r) - pio2_lo);
  } else {
    w = math_trig_with_lo(s, 0);
    c = (t - w * w) / (s + w);
    r = 2.0 * s * r - (pio2_lo - 2.0 * c);
    t = pio4_hi - (r - (pio4_hi - 2.0 * w));
  }
  if (hx > 0) {
    return t;
  }
  return 0.0 - t;
}

/**
 * Computes acos(x): the inverse cosine of x, returned in radians.
 *
 * fdlibm e_acos.c port (Sun reference, error < 1 ulp). Not implemented
 * as pi/2 - asin(x): the cancellation-safe rearrangement is the
 * authority (G.7: this is the acos path; it only reuses the shared
 * R polynomial and math_sqrt_c).
 * 1. |x| >= 1: acos(1)=0, acos(-1)=pi (via pi+2*pio2_lo), else NaN.
 * 2. |x| < 0.5: tiny |x| < 2^-57 returns pio2_hi+pio2_lo; else
 *    pio2_hi - (x - (pio2_lo - x*R(x^2))).
 * 3. x < -0.5: pi - 2*asin(sqrt((1+x)/2)).
 * 4. x > 0.5: 2*asin(sqrt((1-x)/2)) with a hi/lo split of sqrt(z).
 * PLATFORM: SHARED freestanding (no libm).
 * @param x f64 - argument in [-1, 1] for a finite result
 * @return f64 - acos(x) in [0, pi] (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_acos_c(x: f64): f64 {
  let one: f64 = 1.0;
  let pi: f64 = 3.141592653589793115997963468544185161590576171875; /* 0x400921FB, 0x54442D18 */
  let pio2_hi: f64 = 1.5707963267948965579989817342720925807952880859375; /* 0x3FF921FB, 0x54442D18 */
  let pio2_lo: f64 = 0.0000000000000000612323399573676603586882014729198302312846062338790032; /* 0x3C91A626, 0x33145C07 */
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  let z: f64 = 0.0;
  let r: f64 = 0.0;
  let w: f64 = 0.0;
  let s: f64 = 0.0;
  let c: f64 = 0.0;
  let df: f64 = 0.0;
  if (ix >= 1072693248) {           /* |x| >= 1 (0x3ff00000) */
    if (((ix - 1072693248) | math_trig_lo(x)) == 0) {
      if (hx > 0) {
        return 0.0;
      }
      return pi + 2.0 * pio2_lo;
    }
    return (x - x) / (x - x);
  }
  if (ix < 1071644672) {            /* |x| < 0.5 (0x3fe00000) */
    if (ix <= 1012924416) {         /* |x| < 2^-57 (0x3c600000) */
      return pio2_hi + pio2_lo;
    }
    z = x * x;
    r = math_asin_rational(z);
    return pio2_hi - (x - (pio2_lo - x * r));
  } else if (hx < 0) {
    z = (one + x) * 0.5;
    s = math_sqrt_c(z);
    r = math_asin_rational(z);
    w = r * s - pio2_lo;
    return pi - 2.0 * (s + w);
  }
  z = (one - x) * 0.5;
  s = math_sqrt_c(z);
  df = math_trig_with_lo(s, 0);
  c = (z - df * df) / (s + df);
  r = math_asin_rational(z);
  w = r * s + c;
  return 2.0 * (df + w);
}

/**
 * Computes atan(x): the inverse tangent of x, returned in radians.
 *
 * fdlibm s_atan.c port (Sun reference, error < 1 ulp):
 * 1. Reduce to positive via atan(x) = -atan(-x).
 * 2. Range reduction by chopped 4t+0.25 into five intervals, then a
 *    degree-11 odd polynomial in z=t^2 split into even/odd Horner sums.
 * 3. |x| >= 2^66: NaN stays NaN (x+x); +-inf / huge finite -> +-pi/2.
 * 4. |x| < 2^-29 returns x (inexact).
 * Uses math_trig_hi/lo/with_hi (G.7). fabs lives later, so |x| is
 * recovered by clearing the sign bit. id selects atanhi/atanlo.
 * PLATFORM: SHARED freestanding (no libm).
 * @param x f64 - any bit pattern
 * @return f64 - atan(x) in (-pi/2, pi/2) (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_atan_c(x: f64): f64 {
  let atanhi0: f64 = 0.463647609000806093515478778499527834355831146240234375; /* 0x3FDDAC67, 0x0561BB4F */
  let atanhi1: f64 = 0.78539816339744827899949086713604629039764404296875; /* 0x3FE921FB, 0x54442D18 */
  let atanhi2: f64 = 0.98279372324732905408239957978366874158382415771484375; /* 0x3FEF730B, 0xD281F69B */
  let atanhi3: f64 = 1.5707963267948965579989817342720925807952880859375; /* 0x3FF921FB, 0x54442D18 */
  let atanlo0: f64 = 0.0000000000000000226987774529616870924083441919624105525186829473722333; /* 0x3C7A2B7F, 0x222F65E2 */
  let atanlo1: f64 = 0.0000000000000000306161699786838301793441007364599151156423031169395016; /* 0x3C81A626, 0x33145C07 */
  let atanlo2: f64 = 0.0000000000000000139033110312309984515998633820766532312801858490810061; /* 0x3C700788, 0x7AF0CBBD */
  let atanlo3: f64 = 0.0000000000000000612323399573676603586882014729198302312846062338790032; /* 0x3C91A626, 0x33145C07 */
  let aT0: f64 = 0.333333333333329318026727605683845467865467071533203125; /* 0x3FD55555, 0x5555550D */
  let aT1: f64 = 0.0 - 0.19999999999876483247618352834251709282398223876953125; /* 0xBFC99999, 0x9998EBC4 */
  let aT2: f64 = 0.1428571427250346637105593572414363734424114227294921875; /* 0x3FC24924, 0x920083FF */
  let aT3: f64 = 0.0 - 0.11111110405462355787964412456858553923666477203369140625; /* 0xBFBC71C6, 0xFE231671 */
  let aT4: f64 = 0.0909088713343650656195649162327754311263561248779296875; /* 0x3FB745CD, 0xC54C206E */
  let aT5: f64 = 0.0 - 0.07691876205044829994950106311080162413418292999267578125; /* 0xBFB3B0F2, 0xAF749A6D */
  let aT6: f64 = 0.06661073137387531206687896201401599682867527008056640625; /* 0x3FB10D66, 0xA0D03D51 */
  let aT7: f64 = 0.0 - 0.05833570133790573486454178464555297978222370147705078125; /* 0xBFADDE2D, 0x52DEFD9A */
  let aT8: f64 = 0.049768779946159323601673207804196863435208797454833984375; /* 0x3FA97B4B, 0x24760DEB */
  let aT9: f64 = 0.0 - 0.036531572744216915527015743236916023306548595428466796875; /* 0xBFA2B444, 0x2C6A6C2F */
  let aT10: f64 = 0.0162858201153657823623266409640564233995974063873291015625; /* 0x3F90AD3A, 0xE322DA11 */
  let one: f64 = 1.0;
  let huge: f64 = 0.0;
  unsafe {
    let ph: *u64 = &huge as *u64;
    *ph = 9094988921128908188;      /* 0x7e37e43c8800759c = 1e300 */
  }
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  let id: i32 = 0 - 1;
  let w: f64 = 0.0;
  let s1: f64 = 0.0;
  let s2: f64 = 0.0;
  let z: f64 = 0.0;
  let xx: f64 = x;
  if (ix >= 1141899264) {           /* |x| >= 2^66 (0x44100000) */
    if (ix > 2146435072) {          /* NaN (0x7ff00000) */
      return x + x;
    }
    if ((ix == 2146435072) && (math_trig_lo(x) != 0)) {
      return x + x;
    }
    if (hx > 0) {
      return atanhi3 + atanlo3;
    }
    return (0.0 - atanhi3) - atanlo3;
  }
  if (ix < 1071382528) {            /* |x| < 0.4375 (0x3fdc0000) */
    if (ix < 1042284544) {          /* |x| < 2^-29 (0x3e200000) */
      if ((huge + x) > one) {
        return x;
      }
    }
    id = 0 - 1;
  } else {
    xx = math_trig_with_hi(x, ix);  /* fabs: clear sign bit */
    if (ix < 1072889856) {          /* |x| < 1.1875 (0x3ff30000) */
      if (ix < 1072037888) {        /* 7/16 <= |x| < 11/16 (0x3fe60000) */
        id = 0;
        xx = (2.0 * xx - one) / (2.0 + xx);
      } else {
        id = 1;
        xx = (xx - one) / (xx + one);
      }
    } else {
      if (ix < 1073971200) {        /* |x| < 2.4375 (0x40038000) */
        id = 2;
        xx = (xx - 1.5) / (one + 1.5 * xx);
      } else {
        id = 3;
        xx = (0.0 - 1.0) / xx;
      }
    }
  }
  z = xx * xx;
  w = z * z;
  s1 = z * (aT0 + w * (aT2 + w * (aT4 + w * (aT6 + w * (aT8 + w * aT10)))));
  s2 = w * (aT1 + w * (aT3 + w * (aT5 + w * (aT7 + w * aT9))));
  if (id < 0) {
    return xx - xx * (s1 + s2);
  }
  if (id == 0) {
    z = atanhi0 - ((xx * (s1 + s2) - atanlo0) - xx);
  } else if (id == 1) {
    z = atanhi1 - ((xx * (s1 + s2) - atanlo1) - xx);
  } else if (id == 2) {
    z = atanhi2 - ((xx * (s1 + s2) - atanlo2) - xx);
  } else {
    z = atanhi3 - ((xx * (s1 + s2) - atanlo3) - xx);
  }
  if (hx < 0) {
    return 0.0 - z;
  }
  return z;
}

/**
 * Computes atan2(y, x): the four-quadrant inverse tangent of y/x.
 *
 * fdlibm e_atan2.c port (Sun reference, error < 1 ulp). Reuses
 * math_atan_c for the reduced |y/x| kernel (G.7: one atan). fabs lives
 * later, so |y/x| is recovered by clearing the sign bit via
 * math_trig_with_hi. Quadrant is encoded as m = 2*sign(x)+sign(y).
 * 1. NaN in either argument returns x+y (payload is platform-defined).
 * 2. x == +1.0 is a fast path to atan(y).
 * 3. y == +-0: +-0 when x >= 0, +-pi when x < 0 (preserves signed zero).
 * 4. x == +-0 (y nonzero): +-pi/2 from sign(y). fdlibm does not
 *    distinguish x=-0 from x=+0 here (IEEE 754-2008 wants +-pi for
 *    atan2(+-y, -0); this port pins fdlibm).
 * 5. Inf cases: atan2(+-inf, +-inf) = +-pi/4 or +-3pi/4; atan2(+-y, +inf)
 *    = +-0; atan2(+-y, -inf) = +-pi; atan2(+-inf, finite) = +-pi/2.
 * 6. |y/x| > 2^60 uses pi/2; x < 0 and |y|/|x| < 2^-60 uses 0 before
 *    the quadrant restore.
 * PLATFORM: SHARED freestanding (no libm).
 * @param y f64 - numerator (imaginary part of x+iy)
 * @param x f64 - denominator (real part of x+iy)
 * @return f64 - atan2(y, x) in [-pi, pi] (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_atan2_c(y: f64, x: f64): f64 {
  let pi_o_4: f64 = 0.78539816339744827899949086713604629039764404296875; /* 0x3FE921FB, 0x54442D18 */
  let pi_o_2: f64 = 1.5707963267948965579989817342720925807952880859375; /* 0x3FF921FB, 0x54442D18 */
  let pi: f64 = 3.141592653589793115997963468544185161590576171875; /* 0x400921FB, 0x54442D18 */
  let pi_lo: f64 = 0.00000000000000012246467991473532071737640294583966046256921246775800637962561268; /* 0x3CA1A626, 0x33145C07 */
  let tiny: f64 = 0.0;
  unsafe {
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;       /* 0x01a56e1fc2f8f359 = 1e-300 */
  }
  let hx: i32 = math_trig_hi(x);
  let hy: i32 = math_trig_hi(y);
  let ix: i32 = hx & 2147483647;
  let iy: i32 = hy & 2147483647;
  let lx: i32 = math_trig_lo(x);
  let ly: i32 = math_trig_lo(y);
  let z: f64 = 0.0;
  let ax: f64 = 0.0;
  let k: i32 = 0;
  let m: i32 = 0;
  let zh: u32 = 0;
  /* NaN: exponent all-ones and (hi mantissa or lo) nonzero. Isomorphic
   * to fdlibm (ix|((lx|-lx)>>31))>0x7ff00000 with unsigned lx. */
  if (ix > 2146435072) {            /* 0x7ff00000 */
    return x + y;
  }
  if ((ix == 2146435072) && (lx != 0)) {
    return x + y;
  }
  if (iy > 2146435072) {
    return x + y;
  }
  if ((iy == 2146435072) && (ly != 0)) {
    return x + y;
  }
  if (((hx - 1072693248) | lx) == 0) { /* x == +1.0 (0x3ff00000) */
    return math_atan_c(y);
  }
  m = ((hy >> 31) & 1) | ((hx >> 30) & 2); /* 2*sign(x)+sign(y) */
  if ((iy | ly) == 0) {             /* y == +-0 */
    if (m <= 1) {
      return y;                     /* atan2(+-0, +anything) = +-0 */
    }
    if (m == 2) {
      return pi + tiny;             /* atan2(+0, -anything) = +pi */
    }
    return (0.0 - pi) - tiny;       /* atan2(-0, -anything) = -pi */
  }
  if ((ix | lx) == 0) {             /* x == +-0, y nonzero */
    if (hy < 0) {
      return (0.0 - pi_o_2) - tiny;
    }
    return pi_o_2 + tiny;
  }
  if (ix == 2146435072) {           /* |x| == inf */
    if (iy == 2146435072) {         /* |y| == inf */
      if (m == 0) {
        return pi_o_4 + tiny;
      }
      if (m == 1) {
        return (0.0 - pi_o_4) - tiny;
      }
      if (m == 2) {
        return 3.0 * pi_o_4 + tiny;
      }
      return (0.0 - 3.0 * pi_o_4) - tiny;
    }
    if (m == 0) {
      return 0.0;                   /* atan2(+..., +inf) = +0 */
    }
    if (m == 1) {
      return 0.0 * (0.0 - 1.0);     /* atan2(-..., +inf) = -0 */
    }
    if (m == 2) {
      return pi + tiny;
    }
    return (0.0 - pi) - tiny;
  }
  if (iy == 2146435072) {           /* |y| == inf, x finite */
    if (hy < 0) {
      return (0.0 - pi_o_2) - tiny;
    }
    return pi_o_2 + tiny;
  }
  k = (iy - ix) >> 20;
  if (k > 60) {                     /* |y/x| > 2^60 */
    z = pi_o_2 + 0.5 * pi_lo;
  } else if ((hx < 0) && (k < (0 - 60))) {
    z = 0.0;                        /* |y|/|x| < 2^-60 and x < 0 */
  } else {
    ax = y / x;
    ax = math_trig_with_hi(ax, math_trig_hi(ax) & 2147483647);
    z = math_atan_c(ax);
  }
  if (m == 0) {
    return z;                       /* atan2(+, +) */
  }
  if (m == 1) {
    zh = (math_trig_hi(z) as u32);
    return math_trig_with_hi(z, ((zh ^ 2147483648) as i32)); /* flip sign, keep -0 */
  }
  if (m == 2) {
    return pi - (z - pi_lo);        /* atan2(+, -) */
  }
  return (z - pi_lo) - pi;          /* atan2(-, -) */
}

/**
 * Computes sqrt(x): the correctly-rounded IEEE-754 square root of x.
 *
 * fdlibm e_sqrt.c port (Sun reference, correctly rounded by construction):
 * 1. Special values: sqrt(NaN)=NaN (x*x+x), sqrt(+inf)=+inf,
 *    sqrt(-inf)=NaN; sqrt(+/-0)=+/-0 (identity return); sqrt(-finite)=NaN
 *    (via (x-x)/(x-x) = 0/0, default quiet NaN).
 * 2. Subnormals are normalized with fdlibm's while/for loop (u32 wrap
 *    semantics; the i==0 shift-in corner is pinned to zero-fill — fdlibm
 *    relies on shift-count>=width giving 0, which x86 shl would violate by
 *    masking the count; zero-fill is the mathematically correct semantic).
 * 3. m = exponent-1023 made even (doubling the 52-bit mantissa pair when
 *    odd), m>>=1, then the mantissa square root is generated bit by bit in
 *    two u32 restoring loops (q,q1,s0,s1), with the carry-out detection
 *    (s1 bit31 drop increments s0) exactly as in fdlibm.
 * 4. Rounding: inexactness (remainder != 0) rounds to nearest-even via the
 *    one-tiny/one+tiny probe (under round-to-nearest both collapse to one,
 *    selecting the q1 += q1&1 even-fix path); q1==0xffffffff wraps with a
 *    carry into q.
 * All u32 arithmetic wraps (matching C unsigned); m>>1 is expressed as
 * (m - (m&1))/2 so negative m keeps arithmetic-shift semantics regardless
 * of the .x shift lowering. PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_sqrt_c(x: f64): f64 {
  let one: f64 = 1.0;
  /* tiny = 1.0e-300 (0x01a56e1fc2f8f359): only needs to be far below 2^-53
   * so the one-tiny/one+tiny probes collapse to one under round-to-nearest;
   * built from its exact bit pattern (Python-verified). */
  let tiny: f64 = 0.0;
  unsafe {
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;   /* 0x01a56e1fc2f8f359 = 1.0e-300 */
  }
  /* Local copy (parameter reassignment avoided by style). */
  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let ix0: i32 = (bits >> 32) as i32;              /* high word (signed) */
  let ix1w: u32 = (bits & 4294967295) as u32;      /* low word */

  /* Inf and NaN: x*x+x keeps +inf, quiets NaNs, turns -inf into NaN. */
  if ((ix0 & 2146435072) == 2146435072) {
    return r * r + r;
  }
  /* Zero and negative: +-0 returns identically; -finite returns 0/0 NaN. */
  if (ix0 <= 0) {
    if ((ix0 & 2147483647) == 0 && ix1w == 0) {
      return r;                    /* sqrt(+-0) = +-0 */
    }
    if (ix0 < 0) {
      return (r - r) / (r - r);    /* sqrt(-ve) = NaN */
    }
  }

  /* Normalize: m = unbiased exponent; subnormals shifted up in place. */
  let m: i32 = ix0 >> 20;
  let ix0u: u32 = ix0 as u32;      /* ix0 >= 0 here; bit pattern unchanged */
  if (m == 0) {
    while (ix0u == 0) {
      m = m - 21;
      ix0u = ix0u | (ix1w >> 11);
      ix1w = ix1w << 21;           /* u32 wrap = C unsigned shift */
    }
    /* Shift the 52-bit pair left until bit 20 of the high word is set. */
    let i: i32 = 0;
    while ((ix0u & 1048576) == 0) {
      ix0u = ix0u << 1;
      i = i + 1;
    }
    m = m - (i - 1);
    /* Bring the top i bits of the low word into the high word. When i==0
     * nothing shifts in (fdlibm evaluates ix1>>(32-0) there, which is UB
     * in C; zero-fill is the intended semantic and is pinned here). */
    if (i != 0) {
      ix0u = ix0u | (ix1w >> (32 - i));
    }
    ix1w = ix1w << i;
  }
  m = m - 1023;
  ix0u = (ix0u & 1048575) | 1048576;
  /* Odd exponent: double the mantissa pair (and exponent step) once. */
  if ((m & 1) == 1) {
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
  }
  /* m >>= 1 with arithmetic semantics for negative m (m&1 is 0 here). */
  m = (m - (m & 1)) / 2;

  /* Generate sqrt(x) bit by bit (restoring square root, u32 wrap). */
  ix0u = ix0u + ix0u + (ix1w >> 31);
  ix1w = ix1w + ix1w;
  let q: u32 = 0;
  let q1: u32 = 0;
  let s0: u32 = 0;
  let s1: u32 = 0;
  let rb: u32 = 2097152;           /* 0x00200000: moving bit, integer part */
  while (rb != 0) {
    let t: u32 = s0 + rb;
    if (t <= ix0u) {
      s0 = t + rb;
      ix0u = ix0u - t;
      q = q + rb;
    }
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
    rb = rb >> 1;
  }
  rb = 2147483648;                 /* 0x80000000: fraction bits */
  while (rb != 0) {
    let t1: u32 = s1 + rb;
    let t2: u32 = s0;
    if (t2 < ix0u || (t2 == ix0u && t1 <= ix1w)) {
      s1 = t1 + rb;
      /* Carry out of s1's bit 31 increments the integer-part root. */
      if ((t1 & 2147483648) == 2147483648 && (s1 & 2147483648) == 0) {
        s0 = s0 + 1;
      }
      ix0u = ix0u - t2;
      if (ix1w < t1) {
        ix0u = ix0u - 1;           /* borrow */
      }
      ix1w = ix1w - t1;
      q1 = q1 + rb;
    }
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
    rb = rb >> 1;
  }

  /* Rounding direction via fp probe: under round-to-nearest both one-tiny
   * and one+tiny collapse to one, so the even-fix path runs. */
  if ((ix0u | ix1w) != 0) {
    let z0: f64 = one - tiny;
    if (z0 >= one) {
      let z1: f64 = one + tiny;
      if (q1 == 4294967295) {
        q1 = 0;
        q = q + 1;
      } else if (z1 > one) {
        if (q1 == 4294967294) {
          q = q + 1;
        }
        q1 = q1 + 2;
      } else {
        q1 = q1 + (q1 & 1);        /* round to nearest-even */
      }
    }
  }

  /* Assemble: integer part q>>1 into the exponent field, fraction q1>>1.
   * 0x3fe00000 = 1071644672 (Python-verified). */
  let hi0: u32 = (q >> 1) + 1071644672;
  let lo0: u32 = q1 >> 1;
  if ((q & 1) == 1) {
    lo0 = lo0 | 2147483648;        /* low bit of q becomes sign of frac */
  }
  hi0 = hi0 + ((m << 20) as u32);  /* exponent scale (wraps like C int) */
  let z: f64 = 0.0;
  unsafe {
    let pz: *u64 = &z as *u64;
    *pz = ((hi0 as u64) << 32) | (lo0 as u64);
  }
  return z;
}

/**
 * Computes cbrt(x): the cube root of x, error < 1 ulp.
 *
 * fdlibm s_cbrt.c port (Sun reference): sign is split off, a 5-bit rough
 * root is seeded from the exponent (high word /3 + B1, or B2 for subnormals
 * after scaling by 2^54), refined to 23 bits with one rational step
 * (C,D,E,F,G remez constants), chopped to 20 bits (low word zeroed, high
 * word +1) so the following Newton iteration rounds upward, then one
 * Newton step (error < 0.667 ulp) finishes; the sign bit is restored last.
 * Special values: cbrt(NaN)=NaN, cbrt(+/-inf)=+/-inf (x+x), cbrt(+-0)=+-0
 * (identity). All constants are plain decimal literals Python-verified
 * against the fdlibm hex comments; B1/B2 are the fdlibm decimal integers.
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_cbrt_c(x: f64): f64 {
  let c: f64 = 0.5428571428571428;        /* 19/35      0x3fe15f15f15f15f1 */
  let d: f64 = 0.0 - 0.7053061224489796;  /* -864/1225  0xbfe691de2532c834 */
  let e: f64 = 1.4142857142857144;        /* 99/70      0x3ff6a0ea0ea0ea0f */
  let f: f64 = 1.6071428571428572;        /* 45/28      0x3ff9b6db6db6db6e */
  let g: f64 = 0.35714285714285715;       /* 5/14       0x3fd6db6db6db6db7 */
  let b1: u32 = 715094163;                /* (682-0.03306235651)*2**20 */
  let b2: u32 = 696219795;                /* (664-0.03306235651)*2**20 */
  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let hi: u32 = (bits >> 32) as u32;
  let lo: u32 = (bits & 4294967295) as u32;
  let sign: u32 = hi & 2147483648;
  let hx: u32 = hi ^ sign;                /* high word of |x| */

  if (hx >= 2146435072) {
    return r + r;                  /* cbrt(NaN, +-inf) is itself/quiet */
  }
  if ((hx | lo) == 0) {
    return r;                      /* cbrt(+-0) is itself */
  }

  /* x <- |x| (rewrite the local copy's high word without the sign). */
  unsafe { *pr = ((hx as u64) << 32) | (lo as u64); }

  /* Rough cbrt to 5 bits: seed the exponent field. */
  let t: f64 = 0.0;
  let pt: *u64 = &t as *u64;
  if (hx < 1048576) {
    /* Subnormal: t = 2^54 (exact), t *= x (exact), then hi = hi/3 + B2. */
    unsafe { *pt = (1129316352 as u64) << 32; }   /* 0x4350000000000000 = 2^54 */
    t = t * r;
    unsafe {
      let tb: u64 = *pt;
      let thi: u32 = (tb >> 32) as u32;
      *pt = (((thi / 3 + b2) as u64) << 32) | (tb & 4294967295);
    }
  } else {
    unsafe { *pt = ((hx / 3 + b1) as u64) << 32; }
  }

  /* New cbrt to 23 bits: one rational remez step. */
  let rr: f64 = t * t / r;
  let s: f64 = c + rr * t;
  t = t * (g + f / (s + e + d / s));

  /* Chopped to 20 bits and made larger than cbrt(x). */
  unsafe {
    let tb: u64 = *pt;
    let thi: u32 = (tb >> 32) as u32;
    *pt = (((thi + 1) as u64) << 32);   /* low word zero, high word +1 */
  }

  /* One Newton iteration to 53 bits (error < 0.667 ulp). */
  let s2: f64 = t * t;             /* t*t is exact */
  let r2: f64 = r / s2;
  let w: f64 = t + t;
  let r3: f64 = (r2 - t) / (w + r2);   /* r2 - t is exact */
  t = t + t * r3;

  /* Restore the sign bit. */
  unsafe {
    let tb: u64 = *pt;
    let thi: u32 = (tb >> 32) as u32;
    *pt = (((thi | sign) as u64) << 32) | (tb & 4294967295);
  }
  return t;
}

/**
 * Computes pow(base, exp): base**exp, returned as f64.
 *
 * fdlibm e_pow.c port (Sun reference algorithm, error < 1 ulp):
 * 1. Specials first: y==0 -> 1; any NaN -> x+y; y == +-1 / 2 / 0.5 (sqrt);
 *    y == +-inf; x == 0 / +-1 / +-inf (with odd-integer sign of a negative
 *    base); negative non-integer power of a negative base is NaN.
 * 2. log2(|x|) in two pieces t1+t2 (t1 has 29 trailing zero bits). Subnormal
 *    x is scaled by 2^53 first. The reduction interval is selected by the
 *    top 20 significand bits against sqrt(3/2) / sqrt(3).
 * 3. Multi-precision y*(t1+t2) = n + y' with |y'| <= 0.5, then
 *    2**n * exp(y'*ln2) via a degree-5 minimax on the same P-polynomial
 *    used by math_exp_c. Subnormal outputs go through math_trig_scalbn.
 * 4. fdlibm (not IEEE 754-2008) pins: +-1 ** +-inf is NaN (host libm
 *    returns 1). A few generic values sit 1 ulp off correctly-rounded host
 *    libm; the product probe pins fdlibm.
 * All decimal literals are Python-verified against the fdlibm hex comments
 * (rule: decimal<->hex conversion via Python only; scientific-notation
 * literals are not used anywhere in .x). huge/tiny are bit-punned.
 * PLATFORM: SHARED freestanding (no libm).
 * @param base f64 - the base x
 * @param exp f64 - the exponent y
 * @return f64 - x**y (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_pow_c(base: f64, exp: f64): f64 {
  let x: f64 = base;
  let y: f64 = exp;
  let one: f64 = 1.0;
  let two: f64 = 2.0;
  let zero: f64 = 0.0;
  let two53: f64 = 9007199254740992.0;                   /* 0x4340000000000000 */
  let l1: f64 = 0.59999999999999464872502130674547515809535980224609; /* 0x3fe3333333333303 */
  let l2: f64 = 0.42857142857855018425183857289084699004888534545898; /* 0x3fdb6db6db6fabff */
  let l3: f64 = 0.3333333298183774329181972007063450291752815246582;  /* 0x3fd55555518f264d */
  let l4: f64 = 0.27272812380853400648916817772260401397943496704102; /* 0x3fd17460a91d4101 */
  let l5: f64 = 0.23066074577556175406733984800666803494095802307129; /* 0x3fcd864a93c9db65 */
  let l6: f64 = 0.20697501780033841778383418841258389875292778015137; /* 0x3fca7e284a454eef */
  let p1: f64 = 0.16666666666666601903656896865868475288152694702148; /* 0x3fc555555555553e */
  let p2: f64 = 0.0 - 0.00277777777770155933842466389194214571034535765648; /* 0xbf66c16c16bebd93 */
  let p3: f64 = 0.00006613756321437934361170962738185608031926676631; /* 0x3f11566aaf25de2c */
  let p4: f64 = 0.0 - 0.00000165339022054652515389633424952586793210684846; /* 0xbebbbd41c5d26bf1 */
  let p5: f64 = 0.00000004138136797057238460388487247265665303075366; /* 0x3e66376972bea4d0 */
  let lg2: f64 = 0.69314718055994528622676398299518041312694549560547; /* 0x3fe62e42fefa39ef */
  let lg2_h: f64 = 0.693147182464599609375;              /* 0x3fe62e4300000000 */
  let lg2_l: f64 = 0.0 - 0.00000000190465429995776804525041551497972075468468; /* 0xbe205c610ca86c39 */
  let ovt: f64 = 0.00000000000000008008566259537294101970300253372837; /* 0x3c971547652b82fe */
  let cp: f64 = 0.96179669392597555432899980587535537779331207275391; /* 0x3feec709dc3a03fd */
  let cp_h: f64 = 0.961796700954437255859375;            /* 0x3feec709e0000000 */
  let cp_l: f64 = 0.0 - 0.00000000702846165095275826516275184262412534241804; /* 0xbe3e2fe0145b01f5 */
  let ivln2: f64 = 1.44269504088896338700465094007086008787155151367188; /* 0x3ff71547652b82fe */
  let ivln2_h: f64 = 1.44269502162933349609375;          /* 0x3ff7154760000000 */
  let ivln2_l: f64 = 0.00000001925962991126617468866556595954997455066859; /* 0x3e54ae0bf85ddf44 */
  let dp_h1: f64 = 0.58496248722076416015625;            /* 0x3fe2b80340000000 */
  let dp_l1: f64 = 0.0000000135003920212974897128407517727863296208568; /* 0x3e4cfdeb43cfd006 */
  let third: f64 = 0.33333333333333331482961625624739099293947219848633;
  let huge: f64 = 0.0;
  let tiny: f64 = 0.0;
  unsafe {
    let ph: *u64 = &huge as *u64;
    *ph = 9094988921128908188;      /* 0x7e37e43c8800759c = 1e300 */
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;       /* 0x01a56e1fc2f8f359 = 1e-300 */
  }

  let hx: i32 = math_trig_hi(x);
  let hy: i32 = math_trig_hi(y);
  let lx: u32 = math_trig_lo(x) as u32;
  let ly: u32 = math_trig_lo(y) as u32;
  let ix: i32 = hx & 2147483647;     /* 0x7fffffff */
  let iy: i32 = hy & 2147483647;

  /* y == 0 -> 1 (including 0**0 and inf**0). */
  if ((iy == 0) && (ly == 0)) {
    return one;
  }

  /* Any NaN -> x+y (propagates a NaN payload). */
  if (ix > 2146435072) {            /* 0x7ff00000 */
    return x + y;
  }
  if (ix == 2146435072) {
    if (lx != 0) {
      return x + y;
    }
  }
  if (iy > 2146435072) {
    return x + y;
  }
  if (iy == 2146435072) {
    if (ly != 0) {
      return x + y;
    }
  }

  /* yisint: 0 = not an integer, 1 = odd int, 2 = even int. Only needed
   * when x < 0 (negative**non-int is NaN; negative**odd keeps the sign). */
  let yisint: i32 = 0;
  if (hx < 0) {
    if (iy >= 1128267776) {         /* |y| >= 2^53 (0x43400000): even int */
      yisint = 2;
    } else {
      if (iy >= 1072693248) {       /* |y| >= 1 (0x3ff00000) */
        let ke: i32 = (iy >> 20) - 1023;
        if (ke > 20) {
          let sh: i32 = 52 - ke;
          let ju: u32 = ly >> (sh as u32);
          if ((ju << (sh as u32)) == ly) {
            yisint = 2 - ((ju as i32) & 1);
          }
        } else {
          if (ly == 0) {
            let sh2: i32 = 20 - ke;
            let j2: i32 = iy >> sh2;
            if ((j2 << sh2) == iy) {
              yisint = 2 - (j2 & 1);
            }
          }
        }
      }
    }
  }

  if (ly == 0) {
    if (iy == 2146435072) {         /* y is +-inf */
      if ((ix == 1072693248) && (lx == 0)) {
        return y - y;               /* +-1 ** +-inf = NaN (fdlibm) */
      } else {
        if (ix >= 1072693248) {     /* |x| > 1 */
          if (hy >= 0) {
            return y;
          }
          return zero;
        } else {
          if (hy < 0) {
            return zero - y;
          }
          return zero;
        }
      }
    }
    if (iy == 1072693248) {         /* y is +-1 */
      if (hy < 0) {
        return one / x;
      }
      return x;
    }
    if (hy == 1073741824) {         /* y is 2 */
      return x * x;
    }
    if (hy == 1071644672) {         /* y is +0.5 */
      if (hx >= 0) {
        return math_sqrt_c(x);
      }
    }
  }

  /* ax = |x| via clearing the sign bit of the high word. */
  let ax: f64 = math_trig_with_hi(x, ix);

  if (lx == 0) {
    if ((ix == 2146435072) || (ix == 0) || (ix == 1072693248)) {
      let z0: f64 = ax;             /* x is +-0, +-inf, +-1 */
      if (hy < 0) {
        z0 = one / z0;
      }
      if (hx < 0) {
        if ((ix == 1072693248) && (yisint == 0)) {
          z0 = (z0 - z0) / (z0 - z0); /* (-1)**non-int = NaN */
        } else {
          if (yisint == 1) {
            z0 = zero - z0;
          }
        }
      }
      return z0;
    }
  }

  /* xsign = 0 when x < 0, 1 otherwise (fdlibm n = (hx>>31)+1). */
  let xsign: i32 = 1;
  if (hx < 0) {
    xsign = 0;
  }
  if ((xsign | yisint) == 0) {
    return (x - x) / (x - x);       /* negative ** non-int = NaN */
  }

  let s: f64 = one;                 /* sign of the result */
  if ((xsign | (yisint - 1)) == 0) {
    s = zero - one;                 /* negative ** odd int */
  }

  let t1: f64 = 0.0;
  let t2: f64 = 0.0;
  let n: i32 = 0;

  if (iy > 1105199104) {            /* |y| > 2^31 (0x41e00000) */
    if (iy > 1139802112) {          /* |y| > 2^64 (0x43f00000): o/uflow */
      if (ix <= 1072693247) {       /* 0x3fefffff */
        if (hy < 0) {
          return huge * huge;
        }
        return tiny * tiny;
      }
      if (ix >= 1072693248) {
        if (hy > 0) {
          return huge * huge;
        }
        return tiny * tiny;
      }
    }
    if (ix < 1072693247) {
      if (hy < 0) {
        return s * huge * huge;
      }
      return s * tiny * tiny;
    }
    if (ix > 1072693248) {
      if (hy > 0) {
        return s * huge * huge;
      }
      return s * tiny * tiny;
    }
    /* |1-x| <= 2^-20: log(x) ~ x - x^2/2 + x^3/3 - x^4/4. */
    let th: f64 = ax - one;
    let wh: f64 = (th * th) * (0.5 - th * (third - th * 0.25));
    let uh: f64 = ivln2_h * th;
    let vh: f64 = th * ivln2_l - wh * ivln2;
    t1 = uh + vh;
    t1 = math_trig_with_lo(t1, 0);
    t2 = vh - (t1 - uh);
  } else {
    n = 0;
    if (ix < 1048576) {             /* subnormal |x| (0x00100000) */
      ax = ax * two53;
      n = n - 53;
      ix = math_trig_hi(ax);
    }
    n = n + ((ix >> 20) - 1023);
    let jmant: i32 = ix & 1048575;  /* 0x000fffff */
    ix = jmant | 1072693248;        /* normalize to [1, 2) */
    let k: i32 = 0;
    if (jmant <= 235662) {          /* |x| < sqrt(3/2) (0x3988e) */
      k = 0;
    } else {
      if (jmant < 767610) {         /* |x| < sqrt(3) (0xbb67a) */
        k = 1;
      } else {
        k = 0;
        n = n + 1;
        ix = ix - 1048576;
      }
    }
    ax = math_trig_with_hi(ax, ix);

    let bp_k: f64 = 1.0;
    let dp_h_k: f64 = 0.0;
    let dp_l_k: f64 = 0.0;
    if (k == 1) {
      bp_k = 1.5;
      dp_h_k = dp_h1;
      dp_l_k = dp_l1;
    }
    let u: f64 = ax - bp_k;
    let v: f64 = one / (ax + bp_k);
    let ss: f64 = u * v;
    let s_h: f64 = math_trig_with_lo(ss, 0);
    let t_h: f64 = 0.0;
    let th_hi: i32 = ((ix >> 1) | 536870912) + 524288 + (k << 18);
    t_h = math_trig_with_hi(t_h, th_hi);
    let t_l: f64 = ax - (t_h - bp_k);
    let s_l: f64 = v * ((u - s_h * t_h) - s_h * t_l);
    let s2: f64 = ss * ss;
    let rr: f64 = s2 * s2 * (l1 + s2 * (l2 + s2 * (l3 + s2 * (l4 + s2 * (l5 + s2 * l6)))));
    rr = rr + s_l * (s_h + ss);
    s2 = s_h * s_h;
    t_h = 3.0 + s2 + rr;
    t_h = math_trig_with_lo(t_h, 0);
    t_l = rr - ((t_h - 3.0) - s2);
    u = s_h * t_h;
    v = s_l * t_h + t_l * ss;
    let ph0: f64 = u + v;
    ph0 = math_trig_with_lo(ph0, 0);
    let pl0: f64 = v - (ph0 - u);
    let zh: f64 = cp_h * ph0;
    let zl: f64 = cp_l * ph0 + pl0 * cp + dp_l_k;
    let tn: f64 = n as f64;
    t1 = (((zh + zl) + dp_h_k) + tn);
    t1 = math_trig_with_lo(t1, 0);
    t2 = zl - (((t1 - tn) - dp_h_k) - zh);
  }

  /* Split y = y1+y2 and multiply by t1+t2. */
  let y1: f64 = math_trig_with_lo(y, 0);
  let p_l: f64 = (y - y1) * t1 + y * t2;
  let p_h: f64 = y1 * t1;
  let z: f64 = p_l + p_h;
  let j: i32 = math_trig_hi(z);
  let i: i32 = math_trig_lo(z);
  if (j >= 1083179008) {            /* z >= 1024 (0x40900000) */
    if (((j - 1083179008) | i) != 0) {
      return s * huge * huge;       /* overflow */
    } else {
      if ((p_l + ovt) > (z - p_h)) {
        return s * huge * huge;
      }
    }
  } else {
    if ((j & 2147483647) >= 1083231232) { /* z <= -1075 (0x4090cc00) */
      if (((j + 1064252416) | i) != 0) {  /* j - 0xc090cc00 */
        return s * tiny * tiny;     /* underflow */
      } else {
        if (p_l <= (z - p_h)) {
          return s * tiny * tiny;
        }
      }
    }
  }

  /* 2**(p_h+p_l). */
  i = j & 2147483647;
  let k2: i32 = (i >> 20) - 1023;
  n = 0;
  if (i > 1071644672) {             /* |z| > 0.5 (0x3fe00000) */
    n = j + (1048576 >> (k2 + 1));
    k2 = ((n & 2147483647) >> 20) - 1023;
    let t: f64 = 0.0;
    let nmask: i32 = (n as u32 & (((1048575 >> k2) as u32) ^ 4294967295)) as i32;
    t = math_trig_with_hi(t, nmask);
    n = ((n & 1048575) | 1048576) >> (20 - k2);
    if (j < 0) {
      n = 0 - n;
    }
    p_h = p_h - t;
  }
  let t: f64 = p_l + p_h;
  t = math_trig_with_lo(t, 0);
  let u2: f64 = t * lg2_h;
  let v2: f64 = (p_l - (t - p_h)) * lg2 + t * lg2_l;
  z = u2 + v2;
  let w: f64 = v2 - (z - u2);
  t = z * z;
  t1 = z - t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5))));
  let r: f64 = (z * t1) / (t1 - two) - (w + z * w);
  z = one - (r - z);
  j = math_trig_hi(z);
  j = j + (n << 20);
  if ((j >> 20) <= 0) {
    z = math_trig_scalbn(z, n);
  } else {
    z = math_trig_with_hi(z, math_trig_hi(z) + (n << 20));
  }
  return s * z;
}

/**
 * Computes exp(x): the base-e exponential of x, returned as f64.
 *
 * fdlibm e_exp.c port (Sun reference algorithm, error < 1 ulp):
 * 1. Non-finite filter: |x| >= 709.78... checks NaN (x+x), exp(+inf)=+inf,
 *    exp(-inf)=0, overflow (x > o_threshold -> huge*huge = +inf) and
 *    underflow (x < u_threshold -> twom1000*twom1000 = 0).
 * 2. Argument reduction r = x - k*ln2 with ln2 split into a high (exact)
 *    and low part, so k*ln2hi is exact and hi-lo carries the correction;
 *    k = trunc(x*invln2 +/- 0.5) for |x| > 0.5*ln2 (with the exact
 *    k = +/-1 window for |x| < 1.5*ln2), k = 0 otherwise; |x| < 2^-28
 *    returns 1+x directly (with inexact trigger).
 * 3. Rational approximation exp(r) = 1 + 2r/(R-r) written as
 *    1 - (r*c/(c-2) - r) with c = r - r^2*(P1 + r^2*(...P5)) (degree-5
 *    minimax on R(r) = r*(e^r+1)/(e^r-1) over [0, 0.34658]).
 * 4. Scale back: add k<<20 to the exponent field of the result bits
 *    (two's-complement 32-bit add on the high word); for k < -1021 add
 *    (k+1000)<<20 and multiply by 2^-1000.
 * All constants are plain decimal literals Python-verified against the
 * fdlibm hex comments (rule: decimal<->hex conversion via Python only;
 * scientific-notation literals are not used anywhere in .x).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_exp_c(x: f64): f64 {
  let one: f64 = 1.0;
  let half: f64 = 0.5;
  let ln2hi: f64 = 0.693147180369123816490;               /* 0x3fe62e42fee00000 */
  let ln2lo: f64 = 0.000000000190821492927058770002;      /* 0x3dea39ef35793c76 */
  let invln2: f64 = 1.44269504088896338700;               /* 0x3ff71547652b82fe */
  let p1: f64 = 0.166666666666666019037;                  /* 0x3fc555555555553e */
  let p2: f64 = 0.0 - 0.00277777777770155933842;          /* 0xbf66c16c16bebd93 */
  let p3: f64 = 0.0000661375632143793436117;              /* 0x3f11566aaf25de2c */
  let p4: f64 = 0.0 - 0.00000165339022054652515390;       /* 0xbebbbd41c5d26bf1 */
  let p5: f64 = 0.0000000413813679705723846039;           /* 0x3e66376972bea4d0 */
  let o_threshold: f64 = 709.782712893383973096;          /* 0x40862e42fefa39ef */
  let u_threshold: f64 = 0.0 - 745.133219101941108420;    /* 0xc0874910d52d3051 */
  /* huge = 1.0e300 (0x7e37e43c8800759c) and twom1000 = 2^-1000
   * (0x0170000000000000): scientific literals are banned in .x, so these
   * two are built from their exact bit patterns (Python-verified). */
  let huge: f64 = 0.0;
  let twom1000: f64 = 0.0;
  unsafe {
    let phuge: *u64 = &huge as *u64;
    *phuge = 9094988921128908188;   /* 0x7e37e43c8800759c */
    let ptw: *u64 = &twom1000 as *u64;
    *ptw = 103582791429521408;      /* 0x0170000000000000 */
  }
  /* Operate on a local copy (parameter reassignment is avoided by style). */
  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let hxabs: u64 = (bits >> 32) & 2147483647;  /* high word of |x| */
  let lx: u64 = bits & 4294967295;             /* low word */
  let xsb: i32 = ((bits >> 63) & 1) as i32;    /* sign bit */

  /* Filter out non-finite / overflowing / underflowing arguments. */
  if (hxabs >= 1082535490) {   /* |x| >= 709.78... (high word 0x40862e42) */
    if (hxabs >= 2146435072) { /* inf or NaN (0x7ff00000) */
      if (((hxabs & 1048575) | lx) != 0) {
        return r + r;        /* NaN propagates */
      }
      if (xsb == 0) {
        return r;            /* exp(+inf) = +inf */
      }
      return 0.0;            /* exp(-inf) = 0 */
    }
    if (r > o_threshold) {
      return huge * huge;    /* overflow -> +inf */
    }
    if (r < u_threshold) {
      return twom1000 * twom1000;  /* underflow -> 0 */
    }
  }

  /* Argument reduction. */
  let k: i32 = 0;
  let hi: f64 = 0.0;
  let lo: f64 = 0.0;
  if (hxabs > 1071001154) {    /* |x| > 0.5*ln2 (0x3fd62e42) */
    if (hxabs < 1072734898) {  /* |x| < 1.5*ln2 (0x3ff0a2b2): exact k = 1-xsb*2 */
      if (xsb == 0) {
        hi = r - ln2hi;
        lo = ln2lo;
      } else {
        hi = r + ln2hi;
        lo = 0.0 - ln2lo;
      }
      k = 1 - xsb - xsb;
    } else {
      /* k = trunc(r*invln2 +/- 0.5); t*ln2hi is exact by ln2hi's 21-bit
       * significand, lo carries the residual. */
      let hf: f64 = half;
      if (xsb == 1) {
        hf = 0.0 - half;
      }
      k = (invln2 * r + hf) as i32;
      let t: f64 = k as f64;
      hi = r - t * ln2hi;
      lo = t * ln2lo;
    }
    r = hi - lo;
  } else if (hxabs < 1043333120) {  /* |x| < 2^-28 (0x3e300000) */
    if (huge + r > one) {
      return one + r;        /* trigger inexact */
    }
  }

  /* Primary-range rational approximation. */
  let t2: f64 = r * r;
  let c: f64 = r - t2 * (p1 + t2 * (p2 + t2 * (p3 + t2 * (p4 + t2 * p5))));
  if (k == 0) {
    return one - ((r * c) / (c - 2.0) - r);
  }
  let y: f64 = one - ((lo - (r * c) / (2.0 - c)) - hi);
  /* Scale by 2^k: add k<<20 to the exponent field as a two's-complement
   * 32-bit add on the high word (i32 -> u32 truncate -> u64 zero-extend
   * reproduces C unsigned wrap semantics exactly). */
  let py: *u64 = &y as *u64;
  unsafe {
    let b: u64 = *py;
    if (k >= -1021) {
      let ke: i32 = k << 20;
      *py = b + ((((ke as u32) as u64)) << 32);
    } else {
      let ke: i32 = (k + 1000) << 20;
      *py = b + ((((ke as u32) as u64)) << 32);
    }
  }
  if (k < -1021) {
    return y * twom1000;
  }
  return y;
}

/**
 * Computes log(x): the natural logarithm of x, returned as f64.
 *
 * fdlibm e_log.c port (Sun reference algorithm, error < 1 ulp):
 * 1. Domain edges: log(+/-0) = -inf (via -two54/zero), log(negative) = NaN
 *    (via (x-x)/zero), log(+inf) = +inf (x+x passthrough), subnormals are
 *    scaled up by 2^54 with k -= 54.
 * 2. k = exponent - 1023; the significand is renormalized into
 *    [sqrt(2)/2, sqrt(2)) (the i/hx 0x95f64/0x100000 trick adds 1 to k and
 *    divides the argument by 2 when needed).
 * 3. With f = x - 1: |f| < 2^-20 uses a short form R = f^2*(1/2 - f/3);
 *    otherwise s = f/(2+f), and log(1+f) = f - s*(f - R) with
 *    R = z*(Lg1 + w*(Lg3 + w*(Lg5 + w*Lg7))) + w*(Lg2 + w*(Lg4 + w*Lg6)),
 *    z = s^2, w = z^2 (degree-7/4 minimax split), plus the hfsq correction
 *    branch on the i>0 side.
 * 4. k*ln2 is added via the hi/lo split (dk*ln2_hi + dk*ln2_lo).
 * All constants are plain decimal literals Python-verified against the
 * fdlibm hex comments; the i/j wrap (0x6b851 - hx unsigned) is preserved
 * with u64 arithmetic.
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_log_c(x: f64): f64 {
  let ln2hi: f64 = 0.693147180369123816490;               /* 0x3fe62e42fee00000 */
  let ln2lo: f64 = 0.000000000190821492927058770002;      /* 0x3dea39ef35793c76 */
  /* two54 = 2^54 (0x4350000000000000); integer-valued f64 uses the
   * (N as f64) form (plain `N.0` literals are unreliable under -E). */
  let two54: f64 = 18014398509481984 as f64;
  let zero: f64 = 0.0;
  let lg1: f64 = 0.6666666666666735130;                   /* 0x3fe5555555555593 */
  let lg2: f64 = 0.3999999999940941908;                   /* 0x3fd999999997fa04 */
  let lg3: f64 = 0.2857142874366239149;                   /* 0x3fd2492494229359 */
  let lg4: f64 = 0.2222219843214978396;                   /* 0x3fcc71c51d8e78af */
  let lg5: f64 = 0.1818357216161805012;                   /* 0x3fc7466496cb03de */
  let lg6: f64 = 0.1531383769920937332;                   /* 0x3fc39a09d078c69f */
  let lg7: f64 = 0.1479819860511658591;                   /* 0x3fc2f112df3e5244 */

  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let hx: i32 = (bits >> 32) as i32;   /* SIGNED high word (sign check). */
  let lx: u64 = bits & 4294967295;
  let k: i32 = 0;

  /* x < 2^-1022 (also catches +/-0 and negatives, which compare < 0x100000
   * as signed high words): scale subnormals up, special-case zero/negative. */
  if (hx < 1048576) {
    let hxmask: i32 = hx & 2147483647;
    if (hxmask == 0 && lx == 0) {
      return (0.0 - two54) / zero;   /* log(+/-0) = -inf */
    }
    if (hx < 0) {
      return (r - r) / zero;         /* log(-#) = NaN */
    }
    k -= 54;
    r = r * two54;                   /* subnormal -> normal scale-up */
    unsafe { bits = *pr; }
    hx = (bits >> 32) as i32;
  }
  if (hx >= 2146435072) {
    return r + r;                    /* log(+inf) = +inf; NaN propagates */
  }
  k += (hx >> 20) - 1023;
  let hxu: u64 = (hx & 1048575) as u64;   /* significand bits (0x000fffff) */
  /* Renormalize into [sqrt(2)/2, sqrt(2)): when the top significand bit is
   * set, divide x by 2 (clear the bit, bump the exponent field) and k += 1. */
  let ii: u64 = (hxu + 614244) & 1048576;      /* 0x95f64, 0x100000 */
  unsafe {
    let b: u64 = *pr;
    let newhi: u64 = hxu | (ii ^ 1072693248);  /* i ^ 0x3ff00000 */
    *pr = (newhi << 32) | (b & 4294967295);
  }
  k += (ii >> 20) as i32;
  let f: f64 = r - 1.0;

  /* |f| < 2^-20 (2+hx has no carry into bit 20): short rational form. */
  if (((2 + hxu) & 1048575) < 3) {
    if (f == zero) {
      if (k == 0) {
        return zero;
      }
      let dk0: f64 = k as f64;
      return dk0 * ln2hi + dk0 * ln2lo;
    }
    let rr0: f64 = f * f * (0.5 - 0.33333333333333333 * f);
    if (k == 0) {
      return f - rr0;
    }
    let dk1: f64 = k as f64;
    return dk1 * ln2hi - ((rr0 - dk1 * ln2lo) - f);
  }

  let s: f64 = f / (2.0 + f);
  let dk: f64 = k as f64;
  let z: f64 = s * s;
  let jj: u64 = 440401 - hxu;            /* 0x6b851 - hx (u64 wrap, kept) */
  let w: f64 = z * z;
  let iiw: u64 = hxu - 398458;           /* hx - 0x6147a (u64 wrap, kept) */
  let t1: f64 = w * (lg2 + w * (lg4 + w * lg6));
  let t2: f64 = z * (lg1 + w * (lg3 + w * (lg5 + w * lg7)));
  let ior: u64 = iiw | jj;
  let rr: f64 = t2 + t1;
  if (ior > 0) {
    let hfsq: f64 = 0.5 * f * f;
    if (k == 0) {
      return f - (hfsq - s * (hfsq + rr));
    }
    return dk * ln2hi - ((hfsq - (s * (hfsq + rr) + dk * ln2lo)) - f);
  }
  if (k == 0) {
    return f - s * (f - rr);
  }
  return dk * ln2hi - ((s * (f - rr) - dk * ln2lo) - f);
}

/**
 * Computes fabs(x): the absolute value of x, returned as f64.
 * @param x f64 - input value (any bit pattern: zeros, subnormals, inf, NaN)
 * @return f64 - |x| with the sign bit cleared; fabs(-0.0) = +0.0; NaN keeps
 *               its payload with the sign bit cleared
 * Bit-level: mask off bit 63 via the computed mask (1 << 63) - 1.
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_fabs_c(x: f64): f64 {
  let v: f64 = x;
  let one: u64 = 1;
  let p: *u64 = &v as *u64;
  unsafe { *p = *p & ((one << 63) - 1); }
  return v;
}

/**
 * Computes fmin(a, b): IEEE 754 minimumNum, returned as f64.
 * @param a f64 - first operand
 * @param b f64 - second operand
 * @return f64 - the smaller of a and b; if either operand is NaN the other
 *               operand is returned; for equal operands (including the
 *               fmin(+0,-0) / fmin(-0,+0) pairs) the SECOND operand b is
 *               returned, matching glibc's x86_64 convention — Ubuntu gold;
 *               macOS libm instead returns -0 for both zero pairs (2019-style),
 *               an IEEE-legal platform divergence, tolerated here
 * NaN is detected with the self-inequality test (a != a), which needs no
 * bit inspection. PLATFORM: SHARED freestanding (no libm); zero-pair
 * convention pinned to glibc (LINUX|UBUNTU gold), see note above.
 */
#[no_mangle]
export function math_fmin_c(a: f64, b: f64): f64 {
  // IEEE fmin: a NaN operand yields the other operand.
  if (a != a) {
    return b;
  }
  if (b != b) {
    return a;
  }
  if (a < b) {
    return a;
  }
  return b;
}

/**
 * Computes fmax(a, b): IEEE 754 maximumNum, returned as f64.
 * @param a f64 - first operand
 * @param b f64 - second operand
 * @return f64 - the larger of a and b; if either operand is NaN the other
 *               operand is returned; for equal operands (including the
 *               fmax(-0,+0) / fmax(+0,-0) pairs) the SECOND operand b is
 *               returned, matching glibc's x86_64 convention — Ubuntu gold;
 *               macOS libm instead returns +0 for both zero pairs (2019-style),
 *               an IEEE-legal platform divergence, tolerated here
 * NaN is detected with the self-inequality test (a != a), which needs no
 * bit inspection. PLATFORM: SHARED freestanding (no libm); zero-pair
 * convention pinned to glibc (LINUX|UBUNTU gold), see note above.
 */
#[no_mangle]
export function math_fmax_c(a: f64, b: f64): f64 {
  // IEEE fmax: a NaN operand yields the other operand.
  if (a != a) {
    return b;
  }
  if (b != b) {
    return a;
  }
  if (a > b) {
    return a;
  }
  return b;
}

/**
 * fdlibm erf/erfc rational P/Q on |x| < 0.84375.
 * Horner evaluation of the degree-4/5 Remez approximant of (erf(x)-x)/x
 * on z = x^2. Shared by math_erf_c and math_erfc_c (G.7: one polynomial).
 * @param z f64 - x^2; finite and in [0, 0.84375^2]
 * @return f64 - P/Q (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_erf_pq(z: f64): f64 {
  let pp0: f64 = 0.1283791670955125585606992899556644260883331298828125; /* 0x3FC06EBA, 0x8214DB68 */
  let pp1: f64 = 0.0 - 0.325042107247001499370497867857920937240123748779296875; /* 0xBFD4CD7D, 0x691CB913 */
  let pp2: f64 = 0.0 - 0.0284817495755985104766150328714502393268048763275146484375; /* 0xBF9D2A51, 0xDBD7194F */
  let pp3: f64 = 0.0 - 0.0057702702964894415915697578611798235215246677398681640625; /* 0xBF77A291, 0x236668E4 */
  let pp4: f64 = 0.0 - 0.000023763016656650162608359344584840755487675778567790985107421875; /* 0xBEF8EAD6, 0x120016AC */
  let qq1: f64 = 0.397917223959155352819294648725190199911594390869140625; /* 0x3FD97779, 0xCDDADC09 */
  let qq2: f64 = 0.0650222499887672944485217385590658523142337799072265625; /* 0x3FB0A54C, 0x5536CEBA */
  let qq3: f64 = 0.005081306281875765627764618415085351443849503993988037109375; /* 0x3F74D022, 0xC4D36B0F */
  let qq4: f64 = 0.0001324947380043216445255627178312352043576538562774658203125; /* 0x3F215DC9, 0x221C1A10 */
  let qq5: f64 = 0.0 - 0.00000396022827877536812320180548141479448531754314899444580078125; /* 0xBED09C43, 0x42A26120 */
  let one: f64 = 1.0;
  let r: f64 = pp0 + z * (pp1 + z * (pp2 + z * (pp3 + z * pp4)));
  let s: f64 = one + z * (qq1 + z * (qq2 + z * (qq3 + z * (qq4 + z * qq5))));
  return r / s;
}

/**
 * fdlibm erf/erfc rational P1/Q1 on |x| in [0.84375, 1.25].
 * Horner evaluation of erf(1+s) - erx, s = |x| - 1. Shared by
 * math_erf_c and math_erfc_c (G.7: one polynomial).
 * @param s f64 - |x| - 1; finite and in [-0.15625, 0.25]
 * @return f64 - P1/Q1 (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_erf_paqa(s: f64): f64 {
  let pa0: f64 = 0.0 - 0.0023621185607526594407712394740883610211312770843505859375; /* 0xBF6359B8, 0xBEF77538 */
  let pa1: f64 = 0.414856118683748331665839259585482068359851837158203125; /* 0x3FDA8D00, 0xAD92B34D */
  let pa2: f64 = 0.0 - 0.372207876035701323846893728841678239405155181884765625; /* 0xBFD7D240, 0xFBB8C3F1 */
  let pa3: f64 = 0.3183466199011617536740459399879910051822662353515625; /* 0x3FD45FCA, 0x805120E4 */
  let pa4: f64 = 0.0 - 0.110894694282396677476043578280950896441936492919921875; /* 0xBFBC6398, 0x3D3E28EC */
  let pa5: f64 = 0.035478304325618235937067623808616190217435359954833984375; /* 0x3FA22A36, 0x599795EB */
  let pa6: f64 = 0.0 - 0.0021663755948687908430005943927199041354469954967498779296875; /* 0xBF61BF38, 0x0A96073F */
  let qa1: f64 = 0.10642088040084422828623900159072945825755596160888671875; /* 0x3FBB3E66, 0x18EEE323 */
  let qa2: f64 = 0.54039791770217104893703208290389738976955413818359375; /* 0x3FE14AF0, 0x92EB6F33 */
  let qa3: f64 = 0.07182865441419626628682948421555920504033565521240234375; /* 0x3FB2635C, 0xD99FE9A7 */
  let qa4: f64 = 0.1261712198087616421116052833895082585513591766357421875; /* 0x3FC02660, 0xE763351F */
  let qa5: f64 = 0.013637083912029050736247626218755613081157207489013671875; /* 0x3F8BEDC2, 0x6B51DD1C */
  let qa6: f64 = 0.01198449984679910741702801857400118024088442325592041015625; /* 0x3F888B54, 0x5735151D */
  let one: f64 = 1.0;
  let p: f64 = pa0 + s * (pa1 + s * (pa2 + s * (pa3 + s * (pa4 + s * (pa5 + s * pa6)))));
  let q: f64 = one + s * (qa1 + s * (qa2 + s * (qa3 + s * (qa4 + s * (qa5 + s * qa6)))));
  return p / q;
}

/**
 * fdlibm erfc rational R1/S1 on |x| in [1.25, 1/0.35].
 * Horner evaluation of log(erfc(x)*x) - x*x + 0.5625 on s = 1/x^2.
 * Shared by math_erf_c and math_erfc_c (G.7: one polynomial).
 * @param s f64 - 1/x^2; finite
 * @return f64 - R1/S1 (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_erf_rasa(s: f64): f64 {
  let ra0: f64 = 0.0 - 0.00986494403484714822705203829400488757528364658355712890625; /* 0xBF843412, 0x600D6435 */
  let ra1: f64 = 0.0 - 0.693858572707181764371853205375373363494873046875; /* 0xBFE63416, 0xE4BA7360 */
  let ra2: f64 = 0.0 - 10.558626225323290981350510264746844768524169921875; /* 0xC0251E04, 0x41B0E726 */
  let ra3: f64 = 0.0 - 62.37533245032600603963146568275988101959228515625; /* 0xC04F300A, 0xE4CBA38D */
  let ra4: f64 = 0.0 - 162.39666946257347035498241893947124481201171875; /* 0xC0644CB1, 0x84282266 */
  let ra5: f64 = 0.0 - 184.60509290671103599379421211779117584228515625; /* 0xC067135C, 0xEBCCABB2 */
  let ra6: f64 = 0.0 - 81.287435506306593424596940167248249053955078125; /* 0xC0545265, 0x57E4D2F2 */
  let ra7: f64 = 0.0 - 9.81432934416914548592103528790175914764404296875; /* 0xC023A0EF, 0xC69AC25C */
  let sa1: f64 = 19.651271667439257129217367037199437618255615234375; /* 0x4033A6B9, 0xBD707687 */
  let sa2: f64 = 137.657754143519042600019020028412342071533203125; /* 0x4061350C, 0x526AE721 */
  let sa3: f64 = 434.56587747522922882126295007765293121337890625; /* 0x407B290D, 0xD58A1A71 */
  let sa4: f64 = 645.3872717332678803359158337116241455078125; /* 0x40842B19, 0x21EC2868 */
  let sa5: f64 = 429.008140027567833385546691715717315673828125; /* 0x407AD021, 0x57700314 */
  let sa6: f64 = 108.63500554177943513423088006675243377685546875; /* 0x405B28A3, 0xEE48AE2C */
  let sa7: f64 = 6.57024977031928170134733591112308204174041748046875; /* 0x401A47EF, 0x8E484A93 */
  let sa8: f64 = 0.0 - 0.06042441521485809874381089912276365794241428375244140625; /* 0xBFAEEFF2, 0xEE749A62 */
  let one: f64 = 1.0;
  let r: f64 = ra0 + s * (ra1 + s * (ra2 + s * (ra3 + s * (ra4 + s * (ra5 + s * (ra6 + s * ra7))))));
  let q: f64 = one + s * (sa1 + s * (sa2 + s * (sa3 + s * (sa4 + s * (sa5 + s * (sa6 + s * (sa7 + s * sa8)))))));
  return r / q;
}

/**
 * fdlibm erfc rational R2/S2 on |x| in [1/0.35, 28].
 * Horner evaluation of log(erfc(x)*x) - x*x + 0.5625 on s = 1/x^2.
 * Shared by math_erf_c and math_erfc_c (G.7: one polynomial).
 * @param s f64 - 1/x^2; finite
 * @return f64 - R2/S2 (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_erf_rbsb(s: f64): f64 {
  let rb0: f64 = 0.0 - 0.0098649429247000992859728540906871785409748554229736328125; /* 0xBF843412, 0x39E86F4A */
  let rb1: f64 = 0.0 - 0.7992832376805230065741625367081724107265472412109375; /* 0xBFE993BA, 0x70C285DE */
  let rb2: f64 = 0.0 - 17.75795491775475198892308981157839298248291015625; /* 0xC031C209, 0x555F995A */
  let rb3: f64 = 0.0 - 160.636384855821916062268428504467010498046875; /* 0xC064145D, 0x43C5ED98 */
  let rb4: f64 = 0.0 - 637.5664433683896277216263115406036376953125; /* 0xC083EC88, 0x1375F228 */
  let rb5: f64 = 0.0 - 1025.09513161107724954490549862384796142578125; /* 0xC0900461, 0x6A2E5992 */
  let rb6: f64 = 0.0 - 483.51919160865139701854786835610866546630859375; /* 0xC07E384E, 0x9BDC383F */
  let sb1: f64 = 30.33806074348245829241932369768619537353515625; /* 0x403E568B, 0x261D5190 */
  let sb2: f64 = 325.7925129965739188264706172049045562744140625; /* 0x40745CAE, 0x221B9F0A */
  let sb3: f64 = 1536.729586084436959936283528804779052734375; /* 0x409802EB, 0x189D5118 */
  let sb4: f64 = 3199.8582195085955390823073685169219970703125; /* 0x40A8FFB7, 0x688C246A */
  let sb5: f64 = 2553.0504064331644258345477283000946044921875; /* 0x40A3F219, 0xCEDF3BE6 */
  let sb6: f64 = 474.52854120695536721541429869830608367919921875; /* 0x407DA874, 0xE79FE763 */
  let sb7: f64 = 0.0 - 22.44095244658581833618882228620350360870361328125; /* 0xC03670E2, 0x42712D62 */
  let one: f64 = 1.0;
  let r: f64 = rb0 + s * (rb1 + s * (rb2 + s * (rb3 + s * (rb4 + s * (rb5 + s * rb6)))));
  let q: f64 = one + s * (sb1 + s * (sb2 + s * (sb3 + s * (sb4 + s * (sb5 + s * (sb6 + s * sb7))))));
  return r / q;
}

/**
 * fdlibm erf/erfc asymptotic tail: exp(-z*z-0.5625)*exp((z-x)*(z+x)+R/S)
 * with z = x after the low word is cleared (single-precision split so
 * -z*z is exact). Shared by math_erf_c and math_erfc_c (G.7).
 * Reuses math_exp_c and math_trig_with_lo.
 * @param x f64 - |x| (already fabs'd); finite and >= 1.25
 * @param rs f64 - R/S from math_erf_rasa or math_erf_rbsb
 * @return f64 - the two-exp product (fdlibm discrete-op bits)
 * PLATFORM: SHARED freestanding (no libm).
 */
function math_erf_exp_tail(x: f64, rs: f64): f64 {
  let z: f64 = math_trig_with_lo(x, 0);
  return math_exp_c((0.0 - z * z) - 0.5625) * math_exp_c((z - x) * (z + x) + rs);
}

/**
 * Computes erf(x): the error function of x, returned as f64.
 *
 * fdlibm s_erf.c port (Sun reference, error < 1 ulp):
 * 1. Specials: erf(NaN)=NaN, erf(+-inf)=+-1, erf(+-0)=+-0 (odd).
 * 2. |x| < 0.84375: x + x*R(x^2) with R = P/Q (shared math_erf_pq).
 *    |x| < 2^-28 uses the first series term x + efx*x (subnormals scale
 *    by 1/8 to avoid spurious underflow).
 * 3. |x| in [0.84375, 1.25]: sign(x)*(erx + P1/Q1(|x|-1)) with erx the
 *    24-bit rounding of erf(1).
 * 4. |x| >= 6: sign(x)*(1-tiny) (inexact); |x| in (1.25, 6) uses the
 *    complementary asymptotic (1/x)*exp(-x*x-0.5625+R/S) via
 *    math_erf_exp_tail, then erf = sign(x)*(1 - erfc(|x|)).
 * Threshold 1/0.35 is 0x4006DB6E here (erfc uses 0x4006DB6D; fdlibm
 * original, do not unify). Reuses math_fabs_c / math_exp_c (G.7).
 * PLATFORM: SHARED freestanding (no libm).
 * @param x f64 - any bit pattern
 * @return f64 - erf(x) (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_erf_c(x: f64): f64 {
  let erx: f64 = 0.845062911510467529296875; /* 0x3FEB0AC1, 0x60000000 */
  let efx: f64 = 0.1283791670955125863162749055845779366791248321533203125; /* 0x3FC06EBA, 0x8214DB69 */
  let efx8: f64 = 1.0270333367641006905301992446766234934329986572265625; /* 0x3FF06EBA, 0x8214DB69 */
  let tiny: f64 = 0.0;
  unsafe {
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;       /* 0x01a56e1fc2f8f359 = 1e-300 */
  }
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  if (ix >= 2146435072) {           /* 0x7ff00000 inf/NaN */
    let i: i32 = ((((hx as u32) >> 31) << 1) as i32);
    return ((1 - i) as f64) + 1.0 / x; /* erf(+-inf)=+-1; NaN stays NaN */
  }
  if (ix < 1072365568) {            /* 0x3feb0000 |x|<0.84375 */
    if (ix < 1043333120) {          /* 0x3e300000 |x|<2**-28 */
      if (ix < 8388608) {           /* 0x00800000 subnormal */
        return (8.0 * x + efx8 * x) / 8.0;
      }
      return x + efx * x;
    }
    let y: f64 = math_erf_pq(x * x);
    return x + x * y;
  }
  if (ix < 1072955392) {            /* 0x3ff40000 |x|<1.25 */
    let y: f64 = math_erf_paqa(math_fabs_c(x) - 1.0);
    if (hx >= 0) {
      return erx + y;
    }
    return (0.0 - erx) - y;
  }
  if (ix >= 1075314688) {           /* 0x40180000 |x|>=6 */
    if (hx >= 0) {
      return 1.0 - tiny;
    }
    return tiny - 1.0;
  }
  let ax: f64 = math_fabs_c(x);
  let s: f64 = 1.0 / (ax * ax);
  let rs: f64 = 0.0;
  if (ix < 1074191214) {            /* 0x4006DB6E |x|<1/0.35 */
    rs = math_erf_rasa(s);
  } else {
    rs = math_erf_rbsb(s);
  }
  let r: f64 = math_erf_exp_tail(ax, rs);
  if (hx >= 0) {
    return 1.0 - r / ax;
  }
  return r / ax - 1.0;
}

/**
 * Computes erfc(x): the complementary error function 1-erf(x), as f64.
 *
 * fdlibm s_erfc.c port (Sun reference, error < 1 ulp). Not a naive
 * 1-erf(x) (cancellation for large |x|). Interval split:
 * 1. Specials: erfc(NaN)=NaN, erfc(+inf)=0, erfc(-inf)=2.
 * 2. |x| < 0.84375: 1-(x+x*R) for x < 0.25, else 0.5-((x-0.5)+x*R)
 *    (R = shared math_erf_pq). |x| < 2^-56 returns 1-x.
 * 3. |x| in [0.84375, 1.25]: (1-erx)-P1/Q1 if x>0, else 1+(erx+P1/Q1).
 * 4. |x| < 28: (1/x)*exp(-x*x-0.5625+R/S) via math_erf_exp_tail;
 *    x < -6 returns 2-tiny. |x| >= 28: tiny*tiny (underflow) if x>0,
 *    else 2-tiny.
 * Threshold 1/0.35 is 0x4006DB6D here (erf uses 0x4006DB6E; fdlibm
 * original, do not unify). Reuses math_fabs_c / math_exp_c (G.7).
 * PLATFORM: SHARED freestanding (no libm).
 * @param x f64 - any bit pattern
 * @return f64 - erfc(x) (fdlibm discrete-op bits)
 */
#[no_mangle]
export function math_erfc_c(x: f64): f64 {
  let erx: f64 = 0.845062911510467529296875; /* 0x3FEB0AC1, 0x60000000 */
  let half: f64 = 0.5;
  let tiny: f64 = 0.0;
  unsafe {
    let pt: *u64 = &tiny as *u64;
    *pt = 118622047889322841;       /* 0x01a56e1fc2f8f359 = 1e-300 */
  }
  let hx: i32 = math_trig_hi(x);
  let ix: i32 = hx & 2147483647;
  if (ix >= 2146435072) {           /* 0x7ff00000 inf/NaN */
    let i: i32 = ((((hx as u32) >> 31) << 1) as i32);
    return (i as f64) + 1.0 / x;    /* erfc(+-inf)=0,2; NaN stays NaN */
  }
  if (ix < 1072365568) {            /* 0x3feb0000 |x|<0.84375 */
    if (ix < 1013972992) {          /* 0x3c700000 |x|<2**-56 */
      return 1.0 - x;
    }
    let y: f64 = math_erf_pq(x * x);
    if (hx < 1070596096) {          /* 0x3fd00000 x<1/4 */
      return 1.0 - (x + x * y);
    }
    let r: f64 = x * y;
    r = r + (x - half);
    return half - r;
  }
  if (ix < 1072955392) {            /* 0x3ff40000 |x|<1.25 */
    let y: f64 = math_erf_paqa(math_fabs_c(x) - 1.0);
    if (hx >= 0) {
      return (1.0 - erx) - y;
    }
    return 1.0 + (erx + y);
  }
  if (ix < 1077673984) {            /* 0x403c0000 |x|<28 */
    let ax: f64 = math_fabs_c(x);
    let s: f64 = 1.0 / (ax * ax);
    let rs: f64 = 0.0;
    if (ix < 1074191213) {          /* 0x4006DB6D |x|<1/0.35 */
      rs = math_erf_rasa(s);
    } else {
      if ((hx < 0) && (ix >= 1075314688)) { /* x < -6 */
        return 2.0 - tiny;
      }
      rs = math_erf_rbsb(s);
    }
    let r: f64 = math_erf_exp_tail(ax, rs);
    if (hx > 0) {
      return r / ax;
    }
    return 2.0 - r / ax;
  }
  if (hx > 0) {
    return tiny * tiny;
  }
  return 2.0 - tiny;
}

/**
 * Computes log1p(x): the natural logarithm of 1+x, returned as f64.
 *
 * fdlibm s_log1p.c port (Sun reference algorithm, error < 1 ulp):
 * 1. Domain: log1p(-1) = -inf, log1p(x<-1) = NaN, log1p(+inf) = +inf,
 *    log1p(NaN) propagates. |x| < 2^-54 returns x; |x| < 2^-29 uses
 *    x - x*x/2. For x in (-0.2929, 0.41422) excluding the tiny path,
 *    k=0 and f=x is exact (no 1+x reduction).
 * 2. Otherwise 1+x = 2^k * (1+f) with f in [sqrt(2)/2-1, sqrt(2)-1);
 *    c = ((1+x)-u)/u corrects the rounding of u=1+x. For |x| >= 2^53
 *    the extra 1 is lost so u=x and c=0.
 * 3. log1p(f) = f - (hfsq - s*(hfsq+R)) with s=f/(2+f), z=s^2, and
 *    R a degree-14 even polynomial (Lp1..Lp7, same bits as math_log_c
 *    lg1..lg7). |f| < 2^-20 uses the short form hfsq*(1-2f/3).
 * 4. k*ln2 is added via the hi/lo split plus c.
 * All constants are plain decimal literals Python-verified against the
 * fdlibm hex comments (rule: decimal<->hex conversion via Python only).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_log1p_c(x: f64): f64 {
  let ln2hi: f64 = 0.693147180369123816490;               /* 0x3fe62e42fee00000 */
  let ln2lo: f64 = 0.000000000190821492927058770002;      /* 0x3dea39ef35793c76 */
  let two54: f64 = 18014398509481984 as f64;              /* 0x4350000000000000 */
  let zero: f64 = 0.0;
  let lp1: f64 = 0.6666666666666735130;                   /* 0x3fe5555555555593 */
  let lp2: f64 = 0.3999999999940941908;                   /* 0x3fd999999997fa04 */
  let lp3: f64 = 0.2857142874366239149;                   /* 0x3fd2492494229359 */
  let lp4: f64 = 0.2222219843214978396;                   /* 0x3fcc71c51d8e78af */
  let lp5: f64 = 0.1818357216161805012;                   /* 0x3fc7466496cb03de */
  let lp6: f64 = 0.1531383769920937332;                   /* 0x3fc39a09d078c69f */
  let lp7: f64 = 0.1479819860511658591;                   /* 0x3fc2f112df3e5244 */

  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let hx: i32 = (bits >> 32) as i32;
  let ax: i32 = hx & 2147483647;
  let k: i32 = 1;
  let f: f64 = 0.0;
  let c: f64 = 0.0;
  let hu: i32 = 0;
  let u: f64 = 0.0;

  /* x < 0.41422 (0x3FDA827A = 1071284858). Signed compare also catches
   * negatives, including the x <= -1 domain. */
  if (hx < 1071284858) {
    if (ax >= 1072693248) {            /* |x| >= 1  (0x3ff00000) */
      if (r == (0.0 - 1.0)) {
        return (0.0 - two54) / zero;   /* log1p(-1) = -inf */
      }
      return (r - r) / (r - r);        /* log1p(x < -1) = NaN */
    }
    if (ax < 1042284544) {             /* |x| < 2^-29 (0x3e200000) */
      if ((two54 + r) > zero) {
        if (ax < 1016070144) {         /* |x| < 2^-54 (0x3c900000) */
          return r;
        }
      }
      return r - r * r * 0.5;
    }
    /* -0.2929 < x < 0.41422 uses f=x, k=0 (comment in fdlibm); the
     * actual predicate is hx>0 OR hx<=(int)0xbfd2bec3 = -1076707645. */
    if ((hx > 0) || (hx <= -1076707645)) {
      k = 0;
      f = r;
      hu = 1;
    }
  }
  if (hx >= 2146435072) {
    return r + r;                      /* +inf / NaN */
  }
  if (k != 0) {
    if (hx < 1128267776) {             /* |x| < 2^53 (0x43400000) */
      u = 1.0 + r;
      let pu: *u64 = &u as *u64;
      unsafe { bits = *pu; }
      hu = (bits >> 32) as i32;
      k = (hu >> 20) - 1023;
      if (k > 0) {
        c = 1.0 - (u - r);
      } else {
        c = r - (u - 1.0);
      }
      c = c / u;
    } else {
      u = r;
      let pu2: *u64 = &u as *u64;
      unsafe { bits = *pu2; }
      hu = (bits >> 32) as i32;
      k = (hu >> 20) - 1023;
      c = 0.0;
    }
    hu = hu & 1048575;                 /* significand bits 0x000fffff */
    let pu3: *u64 = &u as *u64;
    if (hu < 434334) {                 /* 0x6a09e: keep u in [1, sqrt2) */
      unsafe {
        let b: u64 = *pu3;
        let nhi: u64 = (hu as u64) | 1072693248;  /* 0x3ff00000 */
        *pu3 = (nhi << 32) | (b & 4294967295);
      }
    } else {
      k = k + 1;
      unsafe {
        let b: u64 = *pu3;
        let nhi: u64 = (hu as u64) | 1071644672;  /* 0x3fe00000 */
        *pu3 = (nhi << 32) | (b & 4294967295);
      }
      hu = (1048576 - hu) >> 2;
    }
    f = u - 1.0;
  }

  let hfsq: f64 = 0.5 * f * f;
  if (hu == 0) {                       /* |f| < 2^-20 */
    if (f == zero) {
      if (k == 0) {
        return zero;
      }
      let dk0: f64 = k as f64;
      c = c + dk0 * ln2lo;
      return dk0 * ln2hi + c;
    }
    let rr0: f64 = hfsq * (1.0 - 0.66666666666666666 * f);
    if (k == 0) {
      return f - rr0;
    }
    let dk1: f64 = k as f64;
    return dk1 * ln2hi - ((rr0 - (dk1 * ln2lo + c)) - f);
  }
  let s: f64 = f / (2.0 + f);
  let z: f64 = s * s;
  let rr: f64 = z * (lp1 + z * (lp2 + z * (lp3 + z * (lp4 + z * (lp5 + z * (lp6 + z * lp7))))));
  if (k == 0) {
    return f - (hfsq - s * (hfsq + rr));
  }
  let dk: f64 = k as f64;
  return dk * ln2hi - ((hfsq - (s * (hfsq + rr) + (dk * ln2lo + c))) - f);
}

/**
 * Computes expm1(x): exp(x)-1, returned as f64.
 *
 * fdlibm s_expm1.c port (Sun reference algorithm, error < 1 ulp):
 * 1. Argument reduction: x = k*ln2 + r with |r| <= 0.5*ln2; c holds
 *    the residual (hi-r)-lo so expm1(r+c) ~ expm1(r)+c+r*c.
 * 2. Primary-range rational: z = r^2/2, R1(z) = 1 + Q1 z + ... + Q5 z^5
 *    (Qi scaled by 2^i per fdlibm note A). Then
 *    expm1(r) = r - (r*e - z) with e from the (R1, 3-R1*r/2) form.
 * 3. Scale-back by k: k=0 returns r-E; k=-1 returns 0.5*(r-E)-0.5;
 *    k=1 uses the r<-0.25 split; |k| large does 2^k*(1-(E-r))-1;
 *    otherwise 2^k*((1-2^-k)-(E-r)) or 2^k*(1-((E+2^-k)-r)).
 * 4. Edges: |x|>=56*ln2 and x<0 returns -1; |x|>=709.78 overflows to
 *    +inf; expm1(+inf)=+inf, expm1(-inf)=-1; |x|<2^-54 returns x.
 * All constants are plain decimal literals Python-verified against the
 * fdlibm hex comments (rule: decimal<->hex conversion via Python only).
 * PLATFORM: SHARED freestanding (no libm).
 */
#[no_mangle]
export function math_expm1_c(x: f64): f64 {
  let one: f64 = 1.0;
  let half: f64 = 0.5;
  let ln2hi: f64 = 0.693147180369123816490;               /* 0x3fe62e42fee00000 */
  let ln2lo: f64 = 0.000000000190821492927058770002;      /* 0x3dea39ef35793c76 */
  let invln2: f64 = 1.44269504088896338700;               /* 0x3ff71547652b82fe */
  let o_threshold: f64 = 709.782712893383973096;          /* 0x40862e42fefa39ef */
  let q1: f64 = 0.0 - 0.03333333333333313;                /* 0xbfa11111111110f4 */
  let q2: f64 = 0.0015873015872548146;                    /* 0x3f5a01a019fe5585 */
  let q3: f64 = 0.0 - 0.0000793650757867488;              /* 0xbf14ce199eaadbb7 */
  let q4: f64 = 0.000004008217827329362;                  /* 0x3ed0cfca86e65239 */
  let q5: f64 = 0.0 - 0.00000020109921818362437;          /* 0xbe8afdb76e09c32d */
  /* huge = 1.0e300 (0x7e37e43c8800759c) and tiny = 1.0e-300
   * (0x01a56e1fc2f8f359): scientific literals are banned in .x. */
  let huge: f64 = 0.0;
  let tiny: f64 = 0.0;
  unsafe {
    let phuge: *u64 = &huge as *u64;
    *phuge = 9094988921128908188;      /* 0x7e37e43c8800759c */
    let ptiny: *u64 = &tiny as *u64;
    *ptiny = 118622047889322841;       /* 0x01a56e1fc2f8f359 */
  }

  let r: f64 = x;
  let pr: *u64 = &r as *u64;
  let bits: u64 = 0;
  unsafe { bits = *pr; }
  let hxabs: u64 = (bits >> 32) & 2147483647;
  let lx: u64 = bits & 4294967295;
  let xsb: i32 = ((bits >> 63) & 1) as i32;

  /* Filter huge / non-finite arguments. */
  if (hxabs >= 1078159482) {           /* |x| >= 56*ln2 (0x4043687A) */
    if (hxabs >= 1082535490) {         /* |x| >= 709.78 (0x40862E42) */
      if (hxabs >= 2146435072) {       /* inf or NaN */
        if (((hxabs & 1048575) | lx) != 0) {
          return r + r;                /* NaN propagates */
        }
        if (xsb == 0) {
          return r;                    /* expm1(+inf) = +inf */
        }
        return 0.0 - 1.0;              /* expm1(-inf) = -1 */
      }
      if (r > o_threshold) {
        return huge * huge;            /* overflow -> +inf */
      }
    }
    if (xsb != 0) {                    /* x < -56*ln2 -> -1 (inexact) */
      if ((r + tiny) < 0.0) {
        return tiny - one;
      }
    }
  }

  /* Argument reduction. */
  let k: i32 = 0;
  let hi: f64 = 0.0;
  let lo: f64 = 0.0;
  let corr: f64 = 0.0;
  if (hxabs > 1071001154) {            /* |x| > 0.5*ln2 (0x3fd62e42) */
    if (hxabs < 1072734898) {          /* |x| < 1.5*ln2 (0x3ff0a2b2) */
      if (xsb == 0) {
        hi = r - ln2hi;
        lo = ln2lo;
        k = 1;
      } else {
        hi = r + ln2hi;
        lo = 0.0 - ln2lo;
        k = 0 - 1;
      }
    } else {
      let hf: f64 = half;
      if (xsb == 1) {
        hf = 0.0 - half;
      }
      k = (invln2 * r + hf) as i32;
      let t0: f64 = k as f64;
      hi = r - t0 * ln2hi;
      lo = t0 * ln2lo;
    }
    r = hi - lo;
    corr = (hi - r) - lo;
  } else if (hxabs < 1016070144) {     /* |x| < 2^-54 (0x3c900000) */
    let t1: f64 = huge + r;
    return r - (t1 - (huge + r));
  }

  /* Primary-range rational approximation. */
  let hfx: f64 = half * r;
  let hxs: f64 = r * hfx;
  let r1: f64 = one + hxs * (q1 + hxs * (q2 + hxs * (q3 + hxs * (q4 + hxs * q5))));
  let t: f64 = 3.0 - r1 * hfx;
  let e: f64 = hxs * ((r1 - t) / (6.0 - r * t));
  if (k == 0) {
    return r - (r * e - hxs);
  }
  e = r * (e - corr) - corr;
  e = e - hxs;
  if (k == (0 - 1)) {
    return half * (r - e) - half;
  }
  if (k == 1) {
    if (r < (0.0 - 0.25)) {
      return (0.0 - 2.0) * (e - (r + half));
    }
    return one + 2.0 * (r - e);
  }
  let y: f64 = 0.0;
  if ((k <= -2) || (k > 56)) {
    y = one - (e - r);
    let py: *u64 = &y as *u64;
    unsafe {
      let b: u64 = *py;
      let ke: i32 = k << 20;
      *py = b + ((((ke as u32) as u64)) << 32);
    }
    return y - one;
  }
  let tt: f64 = one;
  let ptt: *u64 = &tt as *u64;
  if (k < 20) {
    /* tt = 1 - 2^-k via high-word 0x3ff00000 - (0x200000>>k). */
    unsafe {
      let thi: u64 = (1072693248 - (2097152 >> k)) as u64;
      *ptt = thi << 32;
    }
    y = tt - (e - r);
    let py2: *u64 = &y as *u64;
    unsafe {
      let b2: u64 = *py2;
      let ke2: i32 = k << 20;
      *py2 = b2 + ((((ke2 as u32) as u64)) << 32);
    }
  } else {
    /* tt = 2^-k via high-word (0x3ff-k)<<20. */
    unsafe {
      let thi2: u64 = ((1023 - k) << 20) as u64;
      *ptt = thi2 << 32;
    }
    y = r - (e + tt);
    y = y + one;
    let py3: *u64 = &y as *u64;
    unsafe {
      let b3: u64 = *py3;
      let ke3: i32 = k << 20;
      *py3 = b3 + ((((ke3 as u32) as u64)) << 32);
    }
  }
  return y;
}

// === fenv public API wrappers ===

#[no_mangle]
export function math_fenv_mask_to_fe(mask: i32): i32 {
  unsafe { return math_fenv_mask_to_fe_impl(mask); }
}

#[no_mangle]
export function math_fenv_fe_to_mask(fe: i32): i32 {
  unsafe { return math_fenv_fe_to_mask_impl(fe); }
}

#[no_mangle]
export function math_fenv_emit_cap_report(avail: i32): void {
  unsafe { math_fenv_emit_cap_report_impl(avail); }
}

// === fenv public API functions (call rest _impl via C bridge) ===

export extern "C" function math_fenv_available_impl_c(): i32;
export extern "C" function math_fenv_test_impl_c(mask: i32): i32;
export extern "C" function math_fenv_clear_impl_c(mask: i32): i32;
export extern "C" function math_fenv_raise_impl_c(mask: i32): i32;
export extern "C" function math_fenv_smoke_impl_c(): i32;
export extern "C" function math_fenv_capability_smoke_impl_c(): i32;

#[no_mangle]
export function math_fenv_available_c(): i32 {
  unsafe { return math_fenv_available_impl_c(); }
}

#[no_mangle]
export function math_fenv_test_c(mask: i32): i32 {
  unsafe { return math_fenv_test_impl_c(mask); }
}

#[no_mangle]
export function math_fenv_clear_c(mask: i32): i32 {
  unsafe { return math_fenv_clear_impl_c(mask); }
}

#[no_mangle]
export function math_fenv_raise_c(mask: i32): i32 {
  unsafe { return math_fenv_raise_impl_c(mask); }
}

#[no_mangle]
export function math_fenv_smoke_c(): i32 {
  unsafe { return math_fenv_smoke_impl_c(); }
}

#[no_mangle]
export function math_fenv_capability_smoke_c(): i32 {
  unsafe { return math_fenv_capability_smoke_impl_c(); }
}
