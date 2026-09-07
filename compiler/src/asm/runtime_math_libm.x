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
export extern "C" function math_sqrt_impl(x: f64): f64;
export extern "C" function math_cbrt_impl(x: f64): f64;
export extern "C" function math_pow_impl(base: f64, exp: f64): f64;
/* 9.2.4 exp/log (2026-09-08): fdlibm e_exp.c / e_log.c full .x ports on the
 * product path; math_exp_impl / math_log_impl libm splices removed (their
 * same-semantics C cold twins live in the guarded seed block). */
export extern "C" function math_fabs_impl(x: f64): f64;
export extern "C" function math_fmin_impl(a: f64, b: f64): f64;
export extern "C" function math_fmax_impl(a: f64, b: f64): f64;
export extern "C" function math_erf_impl(x: f64): f64;
export extern "C" function math_erfc_impl(x: f64): f64;
export extern "C" function math_log1p_impl(x: f64): f64;
export extern "C" function math_expm1_impl(x: f64): f64;

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
  if x > 0.0 {
    return 1.0;
  }
  if x < 0.0 {
    return -1.0;
  }
  return 0.0;
}

// === math_special_near: full .x implementation ===

/// Returns 1 if |a - b| <= eps, 0 otherwise.
#[no_mangle]
export function math_special_near(a: f64, b: f64, eps: f64): i32 {
  let d: f64 = a - b;
  if d < 0.0 { d = 0.0 - d; }
  if d <= eps { return 1; }
  return 0;
}

// === libm public API wrappers (#[no_mangle]) ===
//
// exact-7 slice (9.2.4): floor/ceil/trunc/round/fabs/fmin/fmax are full .x
// bit-level implementations (fdlibm semantics, no libm call on the product
// path). Punning goes through pointer casts (let p: *u64 = &v as *u64), all
// masks are computed with shifts from a u64 one — no large hex literals.
// The remaining wrappers (sin/cos/tan/...) still forward to the C seed
// _impl bridges. The seed keeps same-semantics cold twins of the exact-7
// under `#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X` (G.4: same commit, same
// semantics on both paths).

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
  if e == 2047 {
    return v;
  }
  // |x| < 1: floor is -1.0 for negative non-zero, +0.0 for positive,
  // and +-0.0 is returned unchanged (sign of zero preserved).
  if e < 1023 {
    if bits == 0 || bits == sign_bit {
      return v;
    }
    if (bits & sign_bit) != 0 {
      return 0.0 - 1.0;
    }
    return 0.0;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if e >= 1075 {
    return v;
  }
  // Clear the fractional mantissa bits: truncation toward zero. The low
  // (1075 - e) bits are below the integer boundary, so subtraction of the
  // masked-off part never borrows across the exponent field.
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if (bits & frac_mask) == 0 {
    return v;
  }
  let t_bits: u64 = bits - (bits & frac_mask);
  unsafe { *p = t_bits; }
  // Negative non-integer: floor moves one unit toward -inf.
  if (bits & sign_bit) != 0 {
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
  if e == 2047 {
    return v;
  }
  // |x| < 1: ceil is +1.0 for positive non-zero, -0.0 for negative
  // non-zero (sign of zero preserved per IEEE), +-0.0 unchanged.
  if e < 1023 {
    if bits == 0 || bits == sign_bit {
      return v;
    }
    if (bits & sign_bit) != 0 {
      unsafe { *p = bits & sign_bit; }
      return v;
    }
    return 1.0;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if e >= 1075 {
    return v;
  }
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if (bits & frac_mask) == 0 {
    return v;
  }
  let t_bits: u64 = bits - (bits & frac_mask);
  unsafe { *p = t_bits; }
  // Positive non-integer: ceil moves one unit toward +inf.
  if (bits & sign_bit) == 0 {
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
  if e == 2047 {
    return v;
  }
  // |x| < 1: trunc is a signed zero carrying the sign of x.
  if e < 1023 {
    unsafe { *p = bits & sign_bit; }
    return v;
  }
  // e >= 1075: exponent >= 52 — value is an exact integer (or inf/NaN).
  if e >= 1075 {
    return v;
  }
  let frac_bits: i32 = 1075 - e;
  let frac_mask: u64 = (one << frac_bits) - 1;
  if (bits & frac_mask) == 0 {
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
  if frac >= 0.5 {
    return t + 1.0;
  }
  if frac <= 0.0 - 0.5 {
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

#[no_mangle]
export function math_sqrt_c(x: f64): f64 {
  unsafe { return math_sqrt_impl(x); }
}

#[no_mangle]
export function math_cbrt_c(x: f64): f64 {
  unsafe { return math_cbrt_impl(x); }
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
  if hxabs >= 1082535490 {   /* |x| >= 709.78... (high word 0x40862e42) */
    if hxabs >= 2146435072 { /* inf or NaN (0x7ff00000) */
      if ((hxabs & 1048575) | lx) != 0 {
        return r + r;        /* NaN propagates */
      }
      if xsb == 0 {
        return r;            /* exp(+inf) = +inf */
      }
      return 0.0;            /* exp(-inf) = 0 */
    }
    if r > o_threshold {
      return huge * huge;    /* overflow -> +inf */
    }
    if r < u_threshold {
      return twom1000 * twom1000;  /* underflow -> 0 */
    }
  }

  /* Argument reduction. */
  let k: i32 = 0;
  let hi: f64 = 0.0;
  let lo: f64 = 0.0;
  if hxabs > 1071001154 {    /* |x| > 0.5*ln2 (0x3fd62e42) */
    if hxabs < 1072734898 {  /* |x| < 1.5*ln2 (0x3ff0a2b2): exact k = 1-xsb*2 */
      if xsb == 0 {
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
      if xsb == 1 {
        hf = 0.0 - half;
      }
      k = (invln2 * r + hf) as i32;
      let t: f64 = k as f64;
      hi = r - t * ln2hi;
      lo = t * ln2lo;
    }
    r = hi - lo;
  } else if hxabs < 1043333120 {  /* |x| < 2^-28 (0x3e300000) */
    if huge + r > one {
      return one + r;        /* trigger inexact */
    }
  }

  /* Primary-range rational approximation. */
  let t2: f64 = r * r;
  let c: f64 = r - t2 * (p1 + t2 * (p2 + t2 * (p3 + t2 * (p4 + t2 * p5))));
  if k == 0 {
    return one - ((r * c) / (c - 2.0) - r);
  }
  let y: f64 = one - ((lo - (r * c) / (2.0 - c)) - hi);
  /* Scale by 2^k: add k<<20 to the exponent field as a two's-complement
   * 32-bit add on the high word (i32 -> u32 truncate -> u64 zero-extend
   * reproduces C unsigned wrap semantics exactly). */
  let py: *u64 = &y as *u64;
  unsafe {
    let b: u64 = *py;
    if k >= -1021 {
      let ke: i32 = k << 20;
      *py = b + ((((ke as u32) as u64)) << 32);
    } else {
      let ke: i32 = (k + 1000) << 20;
      *py = b + ((((ke as u32) as u64)) << 32);
    }
  }
  if k < -1021 {
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
  if hx < 1048576 {
    let hxmask: i32 = hx & 2147483647;
    if hxmask == 0 && lx == 0 {
      return (0.0 - two54) / zero;   /* log(+/-0) = -inf */
    }
    if hx < 0 {
      return (r - r) / zero;         /* log(-#) = NaN */
    }
    k -= 54;
    r = r * two54;                   /* subnormal -> normal scale-up */
    unsafe { bits = *pr; }
    hx = (bits >> 32) as i32;
  }
  if hx >= 2146435072 {
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
  if ((2 + hxu) & 1048575) < 3 {
    if f == zero {
      if k == 0 {
        return zero;
      }
      let dk0: f64 = k as f64;
      return dk0 * ln2hi + dk0 * ln2lo;
    }
    let rr0: f64 = f * f * (0.5 - 0.33333333333333333 * f);
    if k == 0 {
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
  if ior > 0 {
    let hfsq: f64 = 0.5 * f * f;
    if k == 0 {
      return f - (hfsq - s * (hfsq + rr));
    }
    return dk * ln2hi - ((hfsq - (s * (hfsq + rr) + dk * ln2lo)) - f);
  }
  if k == 0 {
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
  if a != a {
    return b;
  }
  if b != b {
    return a;
  }
  if a < b {
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
  if a != a {
    return b;
  }
  if b != b {
    return a;
  }
  if a > b {
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

#[no_mangle]
export function math_log1p_c(x: f64): f64 {
  unsafe { return math_log1p_impl(x); }
}

#[no_mangle]
export function math_expm1_c(x: f64): f64 {
  unsafe { return math_expm1_impl(x); }
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
