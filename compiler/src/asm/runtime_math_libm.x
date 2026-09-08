// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// runtime_math_libm.x — R2 full mode public API
// PLATFORM: SHARED
//
// This module provides libm (math library) glue functions for Xlang.
// All functions use f64 (C double) as the primary floating-point type.
//
// Bridge declarations: libm _impl functions implemented in C seed (seeds/runtime_math_libm.from_x.c)
// Public APIs: #[no_mangle] wrappers that call _impl via unsafe extern blocks
//
// libm functions: floor/ceil/trunc/round/sin/cos/tan/asin/acos/atan/atan2/
//   sqrt/cbrt/pow/exp/log/fabs/signum/fmin/fmax/erf/erfc/log1p/expm1
// 9.2.4 exact-7 (floor/ceil/trunc/round/fabs/fmin/fmax): full .x bit-level
//   implementations on the product path (no libm); the seed keeps
//   same-semantics C cold twins guarded by #ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
// 9.2.4 exp/log (2026-09-08): fdlibm e_exp.c / e_log.c full .x ports (no
//   libm); seed keeps same-semantics fdlibm C cold twins under the same guard
// 9.2.4 sqrt/cbrt (2026-09-08): fdlibm e_sqrt.c / s_cbrt.c full .x ports (no
//   libm); seed keeps same-semantics C cold twins under the same guard
// 9.2.4 expm1/log1p (2026-09-08): fdlibm s_expm1.c / s_log1p.c full .x ports
//   (no libm); seed keeps same-semantics C cold twins under the same guard
// fenv functions: mask_to_fe/fe_to_mask/emit_cap_report/available/test/clear/raise/smoke
// special: special_near (full .x impl), special_smoke_c (seed test)

// === libm bridge declarations (extern "C" _impl functions) ===

export extern "C" function math_floor_impl(x: f64): f64;
export extern "C" function math_ceil_impl(x: f64): f64;
export extern "C" function math_trunc_impl(x: f64): f64;
export extern "C" function math_round_impl(x: f64): f64;
export extern "C" function math_sin_impl(x: f64): f64;
export extern "C" function math_cos_impl(x: f64): f64;
export extern "C" function math_tan_impl(x: f64): f64;
export extern "C" function math_asin_impl(x: f64): f64;
export extern "C" function math_acos_impl(x: f64): f64;
export extern "C" function math_atan_impl(x: f64): f64;
export extern "C" function math_atan2_impl(y: f64, x: f64): f64;
/* 9.2.4 sqrt/cbrt (2026-09-08): fdlibm e_sqrt.c / s_cbrt.c full .x ports on
 * the product path; math_sqrt_impl / math_cbrt_impl libm splices removed
 * (same-semantics C cold twins live in the guarded seed block). */
export extern "C" function math_pow_impl(base: f64, exp: f64): f64;
/* 9.2.4 exp/log (2026-09-08): fdlibm e_exp.c / e_log.c full .x ports on the
 * product path; math_exp_impl / math_log_impl libm splices removed (their
 * same-semantics C cold twins live in the guarded seed block). */
export extern "C" function math_fabs_impl(x: f64): f64;
export extern "C" function math_fmin_impl(a: f64, b: f64): f64;
export extern "C" function math_fmax_impl(a: f64, b: f64): f64;
export extern "C" function math_erf_impl(x: f64): f64;
export extern "C" function math_erfc_impl(x: f64): f64;
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
// Remaining wrappers (sin/cos/tan/pow/erf/...) still forward to the C seed
// _impl bridges. exact-7 + exp/log + sqrt/cbrt are full .x; the seed keeps
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

#[no_mangle]
export function math_sin_c(x: f64): f64 {
  unsafe { return math_sin_impl(x); }
}

#[no_mangle]
export function math_cos_c(x: f64): f64 {
  unsafe { return math_cos_impl(x); }
}

#[no_mangle]
export function math_tan_c(x: f64): f64 {
  unsafe { return math_tan_impl(x); }
}

#[no_mangle]
export function math_asin_c(x: f64): f64 {
  unsafe { return math_asin_impl(x); }
}

#[no_mangle]
export function math_acos_c(x: f64): f64 {
  unsafe { return math_acos_impl(x); }
}

#[no_mangle]
export function math_atan_c(x: f64): f64 {
  unsafe { return math_atan_impl(x); }
}

#[no_mangle]
export function math_atan2_c(y: f64, x: f64): f64 {
  unsafe { return math_atan2_impl(y, x); }
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

#[no_mangle]
export function math_pow_c(base: f64, exp: f64): f64 {
  unsafe { return math_pow_impl(base, exp); }
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

#[no_mangle]
export function math_erf_c(x: f64): f64 {
  unsafe { return math_erf_impl(x); }
}

#[no_mangle]
export function math_erfc_c(x: f64): f64 {
  unsafe { return math_erfc_impl(x); }
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
