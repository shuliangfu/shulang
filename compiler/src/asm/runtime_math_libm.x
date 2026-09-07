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
export extern "C" function math_exp_impl(x: f64): f64;
export extern "C" function math_log_impl(x: f64): f64;
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

#[no_mangle]
export function math_exp_c(x: f64): f64 {
  unsafe { return math_exp_impl(x); }
}

#[no_mangle]
export function math_log_c(x: f64): f64 {
  unsafe { return math_log_impl(x); }
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
