/* seeds/runtime_math_libm.from_x.c — G-02f-19 product TU
 * G-02f-119 true .x pure helpers.
 * G-02f-100 math helper gates.
 * Product: runtime_math_libm.o; R2 full mode — thin (.x) provides public API, rest (.c) provides OS bridges.
 *
 * libm：floor/ceil/trunc/round/sin/cos/tan/asin/acos/atan/atan2/
 *        sqrt/cbrt/pow/exp/log/fabs/signum/fmin/fmax/erf/erfc/log1p/expm1
 * fenv：mask_to_fe/fe_to_mask/emit_cap_report/available/test/clear/raise/smoke/capability_smoke
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "diag.h"

#ifndef diag_reportf
XLANG_WEAK void diag_reportf(const char *file, int line, int col, const char *tag, const char *code, const char *fmt, ...) {
  (void)file; (void)line; (void)col; (void)tag; (void)code; (void)fmt;
}
#endif

#if defined(__APPLE__) || (defined(__linux__) && !defined(__ANDROID__))
#include <fenv.h>
#define XLANG_MATH_HAVE_FENV 1
#if defined(__APPLE__)
#pragma STDC FENV_ACCESS ON
#endif
#else
#define XLANG_MATH_HAVE_FENV 0
#endif

#define FENV_NOT_IMPL (-9)

/* thin forward declarations: thin functions (.x) called by rest smoke/test */
int math_special_near(double a, double b, double eps);
int math_fenv_mask_to_fe(int32_t mask);
int32_t math_fenv_fe_to_mask(int fe);
void math_fenv_emit_cap_report(int32_t avail);

#ifdef XLANG_RUNTIME_MATH_LIBM_FROM_X
/* In R2 mode, _c functions are provided by thin (.x); rest needs forward decls */
double math_erf_c(double x);
double math_erfc_c(double x);
double math_log1p_c(double x);
double math_expm1_c(double x);
int32_t math_fenv_available_c(void);
#endif

/* === libm _impl functions (called by thin .x wrappers) === */

double math_floor_impl(double x) { return floor(x); }
double math_ceil_impl(double x) { return ceil(x); }
double math_trunc_impl(double x) { return trunc(x); }
double math_round_impl(double x) { return round(x); }
double math_sin_impl(double x) { return sin(x); }
double math_cos_impl(double x) { return cos(x); }
double math_tan_impl(double x) { return tan(x); }
double math_asin_impl(double x) { return asin(x); }
double math_acos_impl(double x) { return acos(x); }
double math_atan_impl(double x) { return atan(x); }
double math_atan2_impl(double y, double x) { return atan2(y, x); }
/* 9.2.4 sqrt/cbrt/exp/log/expm1/log1p: fdlibm .x ports on the product path;
 * math_sqrt_impl / math_cbrt_impl / math_exp_impl / math_log_impl /
 * math_log1p_impl / math_expm1_impl libm splices removed (same-semantics
 * C cold twins live in the guarded block). */
double math_pow_impl(double base, double exp) { return pow(base, exp); }
double math_fabs_impl(double x) { return fabs(x); }
double math_fmin_impl(double a, double b) { return fmin(a, b); }
double math_fmax_impl(double a, double b) { return fmax(a, b); }
double math_erf_impl(double x) { return erf(x); }
double math_erfc_impl(double x) { return erfc(x); }

/* === libm thin wrappers (only when NOT in R2 from_x mode) ===
 * 9.2.4 exact-7 (floor/ceil/trunc/round/fabs/fmin/fmax) removed from this
 * forward block: thin (.x) provides full bit-level implementations on the
 * product path, and same-semantics C cold twins live in the guarded block
 * below (G.4: same commit, same semantics on both paths).
 */

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
double math_sin_c(double x) { return math_sin_impl(x); }
double math_cos_c(double x) { return math_cos_impl(x); }
double math_tan_c(double x) { return math_tan_impl(x); }
double math_asin_c(double x) { return math_asin_impl(x); }
double math_acos_c(double x) { return math_acos_impl(x); }
double math_atan_c(double x) { return math_atan_impl(x); }
double math_atan2_c(double y, double x) { return math_atan2_impl(y, x); }
double math_pow_c(double base, double exp) { return math_pow_impl(base, exp); }
/* math_sqrt_c / math_cbrt_c / math_exp_c / math_log_c / math_log1p_c /
 * math_expm1_c removed from the splice block: fdlibm .x ports + guarded
 * cold twins below (9.2.4). */
double math_erf_c(double x) { return math_erf_impl(x); }
double math_erfc_c(double x) { return math_erfc_impl(x); }
#endif

/* === exact-7 cold twins (9.2.4): same bit-level algorithm as thin .x ===
 * Thin (.x) provides these on the product path; this C twin keeps the cold
 * (non from_x) path semantics-identical (G.4: same commit, same semantics).
 * Punning via union (strict-aliasing safe); masks computed with shifts —
 * no large hex literals, mirroring the .x source.
 */

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
double math_floor_c(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t one = 1;
  uint64_t sign_bit = one << 63;
  int e = (int)((v.u >> 52) & 2047);
  if (e == 2047) return v.d;
  if (e < 1023) {
    if (v.u == 0 || v.u == sign_bit) return v.d;
    if (v.u & sign_bit) return -1.0;
    return 0.0;
  }
  if (e >= 1075) return v.d;
  int frac_bits = 1075 - e;
  uint64_t frac_mask = (one << frac_bits) - 1;
  if ((v.u & frac_mask) == 0) return v.d;
  v.u -= v.u & frac_mask;
  if (x < 0.0) return v.d - 1.0;
  return v.d;
}

double math_ceil_c(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t one = 1;
  uint64_t sign_bit = one << 63;
  int e = (int)((v.u >> 52) & 2047);
  if (e == 2047) return v.d;
  if (e < 1023) {
    if (v.u == 0 || v.u == sign_bit) return v.d;
    if (v.u & sign_bit) { v.u = sign_bit; return v.d; }
    return 1.0;
  }
  if (e >= 1075) return v.d;
  int frac_bits = 1075 - e;
  uint64_t frac_mask = (one << frac_bits) - 1;
  if ((v.u & frac_mask) == 0) return v.d;
  v.u -= v.u & frac_mask;
  if (x > 0.0) return v.d + 1.0;
  return v.d;
}

double math_trunc_c(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t one = 1;
  uint64_t sign_bit = one << 63;
  int e = (int)((v.u >> 52) & 2047);
  if (e == 2047) return v.d;
  if (e < 1023) { v.u = v.u & sign_bit; return v.d; }
  if (e >= 1075) return v.d;
  int frac_bits = 1075 - e;
  uint64_t frac_mask = (one << frac_bits) - 1;
  v.u -= v.u & frac_mask;
  return v.d;
}

double math_round_c(double x) {
  double t = math_trunc_c(x);
  double frac = x - t;
  if (frac >= 0.5) return t + 1.0;
  if (frac <= -0.5) return t - 1.0;
  return t;
}
#endif

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
double math_fabs_c(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t one = 1;
  v.u &= (one << 63) - 1;
  return v.d;
}

/* fmin/fmax zero-pair convention pinned to glibc x86_64 (Ubuntu gold):
 * equal operands (incl. +-0 pairs) return the SECOND operand. macOS libm
 * returns 2019-style min=-0/max=+0 for both zero pairs — IEEE-legal
 * platform divergence, tolerated (PLATFORM: SHARED, glibc-pinned).
 */
double math_fmin_c(double a, double b) {
  if (a != a) return b;
  if (b != b) return a;
  if (a < b) return a;
  return b;
}

double math_fmax_c(double a, double b) {
  if (a != a) return b;
  if (b != b) return a;
  if (a > b) return a;
  return b;
}
#endif

/* === exp/log cold twins (9.2.4, 2026-09-08): fdlibm e_exp.c / e_log.c ===
 * Thin (.x) provides these on the product path; this C twin keeps the cold
 * (non from_x) path semantics-identical (G.4: same commit, same semantics).
 * Constants are the same plain-decimal literals as the .x source, each
 * Python-verified against the fdlibm hex comment shown. Punning via union.
 */

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
/* PLATFORM: SHARED — FP contraction must stay OFF for the fdlibm twins:
 * arm64 clang defaults to -ffp-contract=on and would fuse mul+add into
 * fmadd, shifting results by 1 ulp vs the .x authority (which emits
 * discrete mul/add). The pragma is honored by clang; gcc x86-64 baseline
 * SSE2 has no FMA so contraction is a no-op there, matching this setting. */
#pragma STDC FP_CONTRACT OFF
double math_exp_c(double x) {
  const double one = 1.0, half = 0.5;
  const double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  const double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  const double invln2 = 1.44269504088896338700;           /* 0x3ff71547652b82fe */
  const double p1 = 0.166666666666666019037;              /* 0x3fc555555555553e */
  const double p2 = -0.00277777777770155933842;           /* 0xbf66c16c16bebd93 */
  const double p3 = 0.0000661375632143793436117;          /* 0x3f11566aaf25de2c */
  const double p4 = -0.00000165339022054652515390;        /* 0xbebbbd41c5d26bf1 */
  const double p5 = 0.0000000413813679705723846039;       /* 0x3e66376972bea4d0 */
  const double o_threshold = 709.782712893383973096;      /* 0x40862e42fefa39ef */
  const double u_threshold = -745.133219101941108420;     /* 0xc0874910d52d3051 */
  union { double d; uint64_t u; } huge, tw;                /* 1.0e300 / 2^-1000 */
  huge.u = 9094988921128908188ULL;   /* 0x7e37e43c8800759c */
  tw.u = 103582791429521408ULL;      /* 0x0170000000000000 */
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t hxabs = (v.u >> 32) & 2147483647;
  uint64_t lx = v.u & 4294967295ULL;
  int xsb = (int)((v.u >> 63) & 1);

  /* Non-finite / overflow / underflow filter. */
  if (hxabs >= 1082535490) {
    if (hxabs >= 2146435072) {
      if (((hxabs & 1048575) | lx) != 0) return x + x;
      return (xsb == 0) ? x : 0.0;
    }
    if (x > o_threshold) return huge.d * huge.d;
    if (x < u_threshold) return tw.d * tw.d;
  }

  /* Argument reduction. */
  int k = 0;
  double hi = 0.0, lo = 0.0, r = x;
  if (hxabs > 1071001154) {
    if (hxabs < 1072734898) {
      if (xsb == 0) { hi = r - ln2hi; lo = ln2lo; }
      else { hi = r + ln2hi; lo = -ln2lo; }
      k = 1 - xsb - xsb;
    } else {
      double hf = half;
      if (xsb == 1) hf = -half;
      k = (int)(invln2 * r + hf);
      double t = (double)k;
      hi = r - t * ln2hi;
      lo = t * ln2lo;
    }
    r = hi - lo;
  } else if (hxabs < 1043333120) {
    if (huge.d + r > one) return one + r;
  }

  /* Primary-range rational approximation. */
  double t2 = r * r;
  double c = r - t2 * (p1 + t2 * (p2 + t2 * (p3 + t2 * (p4 + t2 * p5))));
  if (k == 0) return one - ((r * c) / (c - 2.0) - r);
  double y = one - ((lo - (r * c) / (2.0 - c)) - hi);
  /* Scale by 2^k: exponent-field add with C unsigned wrap semantics. */
  union { double d; uint64_t u; } vy; vy.d = y;
  int ke = (k >= -1021) ? (k << 20) : ((k + 1000) << 20);
  vy.u += (uint64_t)(uint32_t)ke << 32;
  if (k < -1021) return vy.d * tw.d;
  return vy.d;
}

double math_log_c(double x) {
  const double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  const double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  const double two54 = 18014398509481984.0;               /* 0x4350000000000000 */
  const double zero = 0.0;
  const double lg1 = 0.6666666666666735130;               /* 0x3fe5555555555593 */
  const double lg2 = 0.3999999999940941908;               /* 0x3fd999999997fa04 */
  const double lg3 = 0.2857142874366239149;               /* 0x3fd2492494229359 */
  const double lg4 = 0.2222219843214978396;               /* 0x3fcc71c51d8e78af */
  const double lg5 = 0.1818357216161805012;               /* 0x3fc7466496cb03de */
  const double lg6 = 0.1531383769920937332;               /* 0x3fc39a09d078c69f */
  const double lg7 = 0.1479819860511658591;               /* 0x3fc2f112df3e5244 */
  union { double d; uint64_t u; } v; v.d = x;
  int hx = (int)(v.u >> 32);
  uint64_t lx = v.u & 4294967295ULL;
  int k = 0;
  double r = x;

  /* x < 2^-1022 (and +/-0 / negatives, signed high-word compare). */
  if (hx < 1048576) {
    if ((hx & 2147483647) == 0 && lx == 0) return -two54 / zero;
    if (hx < 0) return (r - r) / zero;
    k -= 54;
    r *= two54;
    v.d = r;
    hx = (int)(v.u >> 32);
  }
  if (hx >= 2146435072) return r + r;
  k += (hx >> 20) - 1023;
  uint64_t hxu = (uint64_t)(hx & 1048575);
  /* Renormalize into [sqrt(2)/2, sqrt(2)). */
  uint64_t ii = (hxu + 614244) & 1048576;
  v.u = ((hxu | (ii ^ 1072693248ULL)) << 32) | (v.u & 4294967295ULL);
  r = v.d;
  k += (int)(ii >> 20);
  double f = r - 1.0;

  /* |f| < 2^-20: short rational form. */
  if (((2 + hxu) & 1048575) < 3) {
    if (f == zero) {
      if (k == 0) return zero;
      double dk0 = (double)k;
      return dk0 * ln2hi + dk0 * ln2lo;
    }
    double rr0 = f * f * (0.5 - 0.33333333333333333 * f);
    if (k == 0) return f - rr0;
    double dk1 = (double)k;
    return dk1 * ln2hi - ((rr0 - dk1 * ln2lo) - f);
  }

  double s = f / (2.0 + f);
  double dk = (double)k;
  double z = s * s;
  uint64_t jj = 440401 - hxu;             /* 0x6b851 - hx (u64 wrap, kept) */
  double w = z * z;
  uint64_t iiw = hxu - 398458;            /* hx - 0x6147a (u64 wrap, kept) */
  double t1 = w * (lg2 + w * (lg4 + w * lg6));
  double t2 = z * (lg1 + w * (lg3 + w * (lg5 + w * lg7)));
  uint64_t ior = iiw | jj;
  double rr = t2 + t1;
  if (ior > 0) {
    double hfsq = 0.5 * f * f;
    if (k == 0) return f - (hfsq - s * (hfsq + rr));
    return dk * ln2hi - ((hfsq - (s * (hfsq + rr) + dk * ln2lo)) - f);
  }
  if (k == 0) return f - s * (f - rr);
  return dk * ln2hi - ((s * (f - rr) - dk * ln2lo) - f);
}

/* === sqrt/cbrt cold twins (9.2.4, 2026-09-08): fdlibm e_sqrt.c / s_cbrt.c ===
 * Same algorithm as src/asm/runtime_math_libm.x math_sqrt_c / math_cbrt_c.
 * Constants are Python-verified against the hex comments. Punning via union.
 * sqrt is correctly rounded (bit-identical to host libm on the sample set);
 * cbrt pins fdlibm (<1 ulp, may sit 1 ulp off correctly-rounded host cbrt).
 */
double math_sqrt_c(double x) {
  const double one = 1.0;
  union { double d; uint64_t u; } tiny;
  tiny.u = 118622047889322841ULL; /* 0x01a56e1fc2f8f359 = 1.0e-300 */
  union { double d; uint64_t u; } v; v.d = x;
  int32_t ix0 = (int32_t)(v.u >> 32);
  uint32_t ix1w = (uint32_t)(v.u & 4294967295ULL);

  /* Inf and NaN: x*x+x keeps +inf, quiets NaNs, turns -inf into NaN. */
  if ((ix0 & 2146435072) == 2146435072) {
    return v.d * v.d + v.d;
  }
  /* Zero and negative: +-0 returns identically; -finite returns 0/0 NaN. */
  if (ix0 <= 0) {
    if ((ix0 & 2147483647) == 0 && ix1w == 0) return v.d;
    if (ix0 < 0) return (v.d - v.d) / (v.d - v.d);
  }

  int32_t m = ix0 >> 20;
  uint32_t ix0u = (uint32_t)ix0;
  if (m == 0) {
    while (ix0u == 0) {
      m = m - 21;
      ix0u = ix0u | (ix1w >> 11);
      ix1w = ix1w << 21;
    }
    int32_t i = 0;
    while ((ix0u & 1048576u) == 0) {
      ix0u = ix0u << 1;
      i = i + 1;
    }
    m = m - (i - 1);
    /* i==0: pin zero-fill (fdlibm ix1>>(32-0) is C shift UB). */
    if (i != 0) {
      ix0u = ix0u | (ix1w >> (32 - i));
    }
    ix1w = ix1w << (uint32_t)i;
  }
  m = m - 1023;
  ix0u = (ix0u & 1048575u) | 1048576u;
  if ((m & 1) == 1) {
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
  }
  /* m >>= 1 with arithmetic semantics for negative m. */
  m = (m - (m & 1)) / 2;

  ix0u = ix0u + ix0u + (ix1w >> 31);
  ix1w = ix1w + ix1w;
  uint32_t q = 0, q1 = 0, s0 = 0, s1 = 0;
  uint32_t rb = 2097152u;           /* 0x00200000 */
  while (rb != 0) {
    uint32_t t = s0 + rb;
    if (t <= ix0u) {
      s0 = t + rb;
      ix0u = ix0u - t;
      q = q + rb;
    }
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
    rb = rb >> 1;
  }
  rb = 2147483648u;                 /* 0x80000000 */
  while (rb != 0) {
    uint32_t t1 = s1 + rb;
    uint32_t t2 = s0;
    if (t2 < ix0u || (t2 == ix0u && t1 <= ix1w)) {
      s1 = t1 + rb;
      if ((t1 & 2147483648u) == 2147483648u && (s1 & 2147483648u) == 0) {
        s0 = s0 + 1;
      }
      ix0u = ix0u - t2;
      if (ix1w < t1) {
        ix0u = ix0u - 1;
      }
      ix1w = ix1w - t1;
      q1 = q1 + rb;
    }
    ix0u = ix0u + ix0u + (ix1w >> 31);
    ix1w = ix1w + ix1w;
    rb = rb >> 1;
  }

  if ((ix0u | ix1w) != 0) {
    double z0 = one - tiny.d;
    if (z0 >= one) {
      double z1 = one + tiny.d;
      if (q1 == 4294967295u) {
        q1 = 0;
        q = q + 1;
      } else if (z1 > one) {
        if (q1 == 4294967294u) {
          q = q + 1;
        }
        q1 = q1 + 2;
      } else {
        q1 = q1 + (q1 & 1);
      }
    }
  }

  uint32_t hi0 = (q >> 1) + 1071644672u; /* 0x3fe00000, Python-verified */
  uint32_t lo0 = q1 >> 1;
  if ((q & 1) == 1) {
    lo0 = lo0 | 2147483648u;
  }
  hi0 = hi0 + ((uint32_t)m << 20);
  union { double d; uint64_t u; } z;
  z.u = ((uint64_t)hi0 << 32) | (uint64_t)lo0;
  return z.d;
}

double math_cbrt_c(double x) {
  const double c = 0.5428571428571428;        /* 19/35      0x3fe15f15f15f15f1 */
  const double d = -0.7053061224489796;       /* -864/1225  0xbfe691de2532c834 */
  const double e = 1.4142857142857144;        /* 99/70      0x3ff6a0ea0ea0ea0f */
  const double f = 1.6071428571428572;        /* 45/28      0x3ff9b6db6db6db6e */
  const double g = 0.35714285714285715;       /* 5/14       0x3fd6db6db6db6db7 */
  const uint32_t b1 = 715094163;              /* (682-0.03306235651)*2**20 */
  const uint32_t b2 = 696219795;              /* (664-0.03306235651)*2**20 */
  union { double d; uint64_t u; } v; v.d = x;
  uint32_t hi = (uint32_t)(v.u >> 32);
  uint32_t lo = (uint32_t)(v.u & 4294967295ULL);
  uint32_t sign = hi & 2147483648u;
  uint32_t hx = hi ^ sign;

  if (hx >= 2146435072u) return v.d + v.d;    /* NaN / +-inf */
  if ((hx | lo) == 0) return v.d;             /* +-0 */

  v.u = ((uint64_t)hx << 32) | (uint64_t)lo;  /* x <- |x| */

  union { double d; uint64_t u; } t; t.d = 0.0;
  if (hx < 1048576u) {
    t.u = ((uint64_t)1129316352u) << 32;      /* 0x43500000 << 32 = 2^54 */
    t.d = t.d * v.d;
    uint32_t thi = (uint32_t)(t.u >> 32);
    t.u = ((uint64_t)(thi / 3 + b2) << 32) | (t.u & 4294967295ULL);
  } else {
    t.u = ((uint64_t)(hx / 3 + b1)) << 32;
  }

  double rr = t.d * t.d / v.d;
  double s = c + rr * t.d;
  t.d = t.d * (g + f / (s + e + d / s));

  {
    uint32_t thi = (uint32_t)(t.u >> 32);
    t.u = ((uint64_t)(thi + 1) << 32);        /* low word zero, high word +1 */
  }

  double s2 = t.d * t.d;
  double r2 = v.d / s2;
  double w = t.d + t.d;
  double r3 = (r2 - t.d) / (w + r2);
  t.d = t.d + t.d * r3;

  {
    uint32_t thi = (uint32_t)(t.u >> 32);
    t.u = ((uint64_t)(thi | sign) << 32) | (t.u & 4294967295ULL);
  }
  return t.d;
}

/* === expm1/log1p cold twins (9.2.4, 2026-09-08): fdlibm s_expm1.c / s_log1p.c ===
 * Same algorithm as src/asm/runtime_math_libm.x math_expm1_c / math_log1p_c.
 * Constants are Python-verified against the hex comments. Punning via union.
 * Both pin fdlibm (<1 ulp); a few inputs sit 1 ulp off correctly-rounded
 * host libm (expm1(1), expm1(40), log1p(2)) and are pinned in the rc probe.
 */
double math_expm1_c(double x) {
  const double one = 1.0, half = 0.5;
  const double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  const double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  const double invln2 = 1.44269504088896338700;           /* 0x3ff71547652b82fe */
  const double o_threshold = 709.782712893383973096;      /* 0x40862e42fefa39ef */
  const double q1 = -0.03333333333333313;                 /* 0xbfa11111111110f4 */
  const double q2 =  0.0015873015872548146;               /* 0x3f5a01a019fe5585 */
  const double q3 = -0.0000793650757867488;               /* 0xbf14ce199eaadbb7 */
  const double q4 =  0.000004008217827329362;             /* 0x3ed0cfca86e65239 */
  const double q5 = -0.00000020109921818362437;           /* 0xbe8afdb76e09c32d */
  union { double d; uint64_t u; } huge, tiny;
  huge.u = 9094988921128908188ULL;   /* 0x7e37e43c8800759c = 1e300 */
  tiny.u = 118622047889322841ULL;    /* 0x01a56e1fc2f8f359 = 1e-300 */
  union { double d; uint64_t u; } v; v.d = x;
  uint64_t hxabs = (v.u >> 32) & 2147483647;
  uint64_t lx = v.u & 4294967295ULL;
  int xsb = (int)((v.u >> 63) & 1);

  if (hxabs >= 1078159482) {           /* |x| >= 56*ln2 (0x4043687A) */
    if (hxabs >= 1082535490) {         /* |x| >= 709.78 (0x40862E42) */
      if (hxabs >= 2146435072) {
        if (((hxabs & 1048575) | lx) != 0) return x + x;
        return (xsb == 0) ? x : -1.0;
      }
      if (x > o_threshold) return huge.d * huge.d;
    }
    if (xsb != 0) {
      if (x + tiny.d < 0.0) return tiny.d - one;
    }
  }

  int k = 0;
  double hi = 0.0, lo = 0.0, corr = 0.0, r = x;
  if (hxabs > 1071001154) {            /* |x| > 0.5*ln2 */
    if (hxabs < 1072734898) {          /* |x| < 1.5*ln2 */
      if (xsb == 0) { hi = r - ln2hi; lo = ln2lo; k = 1; }
      else { hi = r + ln2hi; lo = -ln2lo; k = -1; }
    } else {
      double hf = half;
      if (xsb == 1) hf = -half;
      k = (int)(invln2 * r + hf);
      double t0 = (double)k;
      hi = r - t0 * ln2hi;
      lo = t0 * ln2lo;
    }
    r = hi - lo;
    corr = (hi - r) - lo;
  } else if (hxabs < 1016070144) {     /* |x| < 2^-54 */
    double t1 = huge.d + r;
    return r - (t1 - (huge.d + r));
  }

  double hfx = half * r;
  double hxs = r * hfx;
  double r1 = one + hxs * (q1 + hxs * (q2 + hxs * (q3 + hxs * (q4 + hxs * q5))));
  double t = 3.0 - r1 * hfx;
  double e = hxs * ((r1 - t) / (6.0 - r * t));
  if (k == 0) return r - (r * e - hxs);
  e = (r * (e - corr) - corr);
  e -= hxs;
  if (k == -1) return half * (r - e) - half;
  if (k == 1) {
    if (r < -0.25) return -2.0 * (e - (r + half));
    return one + 2.0 * (r - e);
  }
  union { double d; uint64_t u; } y;
  if (k <= -2 || k > 56) {
    y.d = one - (e - r);
    y.u += (uint64_t)(uint32_t)(k << 20) << 32;
    return y.d - one;
  }
  union { double d; uint64_t u; } tt;
  tt.d = one;
  if (k < 20) {
    uint32_t thi = 1072693248u - (2097152u >> k);
    tt.u = ((uint64_t)thi) << 32;
    y.d = tt.d - (e - r);
    y.u += (uint64_t)(uint32_t)(k << 20) << 32;
  } else {
    uint32_t thi = (uint32_t)((1023 - k) << 20);
    tt.u = ((uint64_t)thi) << 32;
    y.d = r - (e + tt.d);
    y.d += one;
    y.u += (uint64_t)(uint32_t)(k << 20) << 32;
  }
  return y.d;
}

double math_log1p_c(double x) {
  const double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  const double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  const double two54 = 18014398509481984.0;               /* 0x4350000000000000 */
  const double zero = 0.0;
  const double lp1 = 0.6666666666666735130;               /* 0x3fe5555555555593 */
  const double lp2 = 0.3999999999940941908;               /* 0x3fd999999997fa04 */
  const double lp3 = 0.2857142874366239149;               /* 0x3fd2492494229359 */
  const double lp4 = 0.2222219843214978396;               /* 0x3fcc71c51d8e78af */
  const double lp5 = 0.1818357216161805012;               /* 0x3fc7466496cb03de */
  const double lp6 = 0.1531383769920937332;               /* 0x3fc39a09d078c69f */
  const double lp7 = 0.1479819860511658591;               /* 0x3fc2f112df3e5244 */
  union { double d; uint64_t u; } v; v.d = x;
  int hx = (int)(v.u >> 32);
  int ax = hx & 2147483647;
  int k = 1;
  double f = 0.0, c = 0.0, u = 0.0;
  int hu = 0;

  if (hx < 1071284858) {               /* x < 0.41422 (0x3FDA827A) */
    if (ax >= 1072693248) {            /* x <= -1.0 */
      if (x == -1.0) return -two54 / zero;
      return (x - x) / (x - x);
    }
    if (ax < 1042284544) {             /* |x| < 2^-29 */
      if (two54 + x > zero && ax < 1016070144) return x; /* |x| < 2^-54 */
      return x - x * x * 0.5;
    }
    if (hx > 0 || hx <= -1076707645) { /* (int)0xbfd2bec3 */
      k = 0; f = x; hu = 1;
    }
  }
  if (hx >= 2146435072) return x + x;
  if (k != 0) {
    union { double d; uint64_t u; } vu;
    if (hx < 1128267776) {             /* |x| < 2^53 */
      u = 1.0 + x;
      vu.d = u;
      hu = (int)(vu.u >> 32);
      k = (hu >> 20) - 1023;
      c = (k > 0) ? 1.0 - (u - x) : x - (u - 1.0);
      c /= u;
    } else {
      u = x;
      vu.d = u;
      hu = (int)(vu.u >> 32);
      k = (hu >> 20) - 1023;
      c = 0.0;
    }
    hu &= 1048575;
    if (hu < 434334) {                 /* 0x6a09e */
      uint32_t nhi = (uint32_t)hu | 1072693248u;
      vu.u = ((uint64_t)nhi << 32) | (vu.u & 4294967295ULL);
    } else {
      k += 1;
      uint32_t nhi = (uint32_t)hu | 1071644672u;
      vu.u = ((uint64_t)nhi << 32) | (vu.u & 4294967295ULL);
      hu = (1048576 - hu) >> 2;
    }
    u = vu.d;
    f = u - 1.0;
  }
  double hfsq = 0.5 * f * f;
  if (hu == 0) {
    if (f == zero) {
      if (k == 0) return zero;
      c += (double)k * ln2lo;
      return (double)k * ln2hi + c;
    }
    double rr0 = hfsq * (1.0 - 0.66666666666666666 * f);
    if (k == 0) return f - rr0;
    return (double)k * ln2hi - ((rr0 - ((double)k * ln2lo + c)) - f);
  }
  double s = f / (2.0 + f);
  double z = s * s;
  double rr = z * (lp1 + z * (lp2 + z * (lp3 + z * (lp4 + z * (lp5 + z * (lp6 + z * lp7))))));
  if (k == 0) return f - (hfsq - s * (hfsq + rr));
  return (double)k * ln2hi - ((hfsq - (s * (hfsq + rr) + ((double)k * ln2lo + c))) - f);
}
#endif

/* === signum: thin provides full .x impl; rest keeps C copy for cold path === */

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
double math_signum_c(double x) {
  if (x > 0.0) {
    return 1.0;
  }
  if (x < 0.0) {
    return -1.0;
  }
  return 0.0;
}
#endif

/* === special_near: thin provides full .x impl; rest keeps C copy for cold path === */

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int math_special_near(double a, double b, double eps) {
  double d = a - b;
  if (d < 0.0) {
    d = -d;
  }
  return d <= eps ? 1 : 0;
}
#endif

/* === special_smoke_c: test function, always provided by seed === */

int32_t math_special_smoke_c(void) {
  if (!math_special_near(math_erf_c(0.0), 0.0, 1.0e-12)) {
    return 1;
  }
  if (!math_special_near(math_erf_c(1.0), 0.8427007929497149, 1.0e-6)) {
    return 2;
  }
  if (!math_special_near(math_log1p_c(0.0), 0.0, 1.0e-12)) {
    return 3;
  }
  if (!math_special_near(math_expm1_c(0.0), 0.0, 1.0e-12)) {
    return 4;
  }
  if (!math_special_near(math_erfc_c(0.0), 1.0, 1.0e-12)) {
    return 5;
  }
  return 0;
}

/* === fenv functions === */

#if XLANG_MATH_HAVE_FENV

/* fenv_mask_to_fe_impl: thin calls this via bridge declaration */
int math_fenv_mask_to_fe_impl(int32_t mask) {
  int fe = 0;
  if (mask & 1) fe |= FE_INVALID;
  if (mask & 2) fe |= FE_DIVBYZERO;
  if (mask & 4) fe |= FE_OVERFLOW;
  if (mask & 8) fe |= FE_UNDERFLOW;
  if (mask & 16) fe |= FE_INEXACT;
  return fe;
}

/* fenv_mask_to_fe: thin wrapper in .x; rest keeps C copy for cold path */
#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int math_fenv_mask_to_fe(int32_t mask) {
    return math_fenv_mask_to_fe_impl(mask);
}
#endif

/* fenv_fe_to_mask_impl: thin calls this via bridge declaration */
int32_t math_fenv_fe_to_mask_impl(int fe) {
  int32_t m = 0;
  if (fe & FE_INVALID) m |= 1;
  if (fe & FE_DIVBYZERO) m |= 2;
  if (fe & FE_OVERFLOW) m |= 4;
  if (fe & FE_UNDERFLOW) m |= 8;
  if (fe & FE_INEXACT) m |= 16;
  return m;
}

/* fenv_fe_to_mask: thin wrapper in .x; rest keeps C copy for cold path */
#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_fe_to_mask(int fe) {
    return math_fenv_fe_to_mask_impl(fe);
}
#endif

/* fenv_emit_cap_report_impl: thin calls this via bridge declaration */
void math_fenv_emit_cap_report_impl(int32_t avail) {
  const char *plat = "Unknown";
#if defined(__APPLE__)
  plat = "Darwin";
#elif defined(__linux__)
  plat = "Linux";
#elif defined(_WIN32)
  plat = "Windows";
#endif
  diag_reportf(NULL, 0, 0, "note", NULL,
               "math fenv cap: platform=%s available=%d",
               plat, (int)avail);
}

/* fenv_emit_cap_report: thin wrapper in .x; rest keeps C copy for cold path */
#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
void math_fenv_emit_cap_report(int32_t avail) {
    math_fenv_emit_cap_report_impl(avail);
}
#endif

#endif /* XLANG_MATH_HAVE_FENV */

/* === fenv public API _impl functions (called by thin .x wrappers) === */

int32_t math_fenv_available_impl_c(void) {
#if XLANG_MATH_HAVE_FENV
  math_fenv_emit_cap_report(1);
  return 1;
#else
  math_fenv_emit_cap_report(0);
  return 0;
#endif
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_available_c(void) {
#if XLANG_MATH_HAVE_FENV
  math_fenv_emit_cap_report(1);
  return 1;
#else
  math_fenv_emit_cap_report(0);
  return 0;
#endif
}
#endif

int32_t math_fenv_test_impl_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return math_fenv_fe_to_mask(fetestexcept(math_fenv_mask_to_fe(mask)));
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_test_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return math_fenv_fe_to_mask(fetestexcept(math_fenv_mask_to_fe(mask)));
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}
#endif

int32_t math_fenv_clear_impl_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return feclearexcept(math_fenv_mask_to_fe(mask)) == 0 ? 0 : 1;
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_clear_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return feclearexcept(math_fenv_mask_to_fe(mask)) == 0 ? 0 : 1;
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}
#endif

int32_t math_fenv_raise_impl_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return feraiseexcept(math_fenv_mask_to_fe(mask)) == 0 ? 0 : 1;
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_raise_c(int32_t mask) {
#if XLANG_MATH_HAVE_FENV
  return feraiseexcept(math_fenv_mask_to_fe(mask)) == 0 ? 0 : 1;
#else
  (void)mask;
  return FENV_NOT_IMPL;
#endif
}
#endif

int32_t math_fenv_smoke_impl_c(void) {
#if XLANG_MATH_HAVE_FENV
  feclearexcept(FE_ALL_EXCEPT);
  volatile double nan_val = 0.0 / 0.0;
  (void)nan_val;
  if ((fetestexcept(FE_INVALID) & FE_INVALID) == 0) return 1;
  if (feclearexcept(FE_INVALID) != 0) return 2;
  if ((fetestexcept(FE_INVALID) & FE_INVALID) != 0) return 3;
  if (feraiseexcept(FE_OVERFLOW) != 0) return 4;
  if ((fetestexcept(FE_OVERFLOW) & FE_OVERFLOW) == 0) return 5;
  feclearexcept(FE_ALL_EXCEPT);
  return 0;
#else
  return FENV_NOT_IMPL;
#endif
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_smoke_c(void) {
#if XLANG_MATH_HAVE_FENV
  feclearexcept(FE_ALL_EXCEPT);
  volatile double nan_val = 0.0 / 0.0;
  (void)nan_val;
  if ((fetestexcept(FE_INVALID) & FE_INVALID) == 0) return 1;
  if (feclearexcept(FE_INVALID) != 0) return 2;
  if ((fetestexcept(FE_INVALID) & FE_INVALID) != 0) return 3;
  if (feraiseexcept(FE_OVERFLOW) != 0) return 4;
  if ((fetestexcept(FE_OVERFLOW) & FE_OVERFLOW) == 0) return 5;
  feclearexcept(FE_ALL_EXCEPT);
  return 0;
#else
  return FENV_NOT_IMPL;
#endif
}
#endif

int32_t math_fenv_capability_smoke_impl_c(void) {
  (void)math_fenv_available_c();
  return 0;
}

#ifndef XLANG_RUNTIME_MATH_LIBM_FROM_X
int32_t math_fenv_capability_smoke_c(void) {
  (void)math_fenv_available_c();
  return 0;
}
#endif
