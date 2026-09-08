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
/* math_sin_impl / math_cos_impl / math_tan_impl / math_asin_impl /
 * math_acos_impl / math_atan_impl / math_atan2_impl libm splices
 * removed (9.2.4). */
/* 9.2.4 sqrt/cbrt/exp/log/expm1/log1p/sin/cos/tan/pow/asin/acos/atan/atan2:
 * fdlibm .x ports on the product path; matching math_*_impl libm splices
 * removed (same-semantics C cold twins live in the guarded block). */
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
/* math_sin_c / math_cos_c / math_tan_c / math_asin_c / math_acos_c /
 * math_atan_c / math_atan2_c removed from splice: fdlibm .x ports +
 * guarded cold twins below (9.2.4). */
/* math_sqrt_c / math_cbrt_c / math_exp_c / math_log_c / math_log1p_c /
 * math_expm1_c / math_pow_c / math_asin_c / math_acos_c / math_atan_c /
 * math_atan2_c removed from the splice block: fdlibm .x ports + guarded
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

/* === 9.2.4 sin/cos/tan cold twins: fdlibm s_sin/s_cos/s_tan + kernels + rem_pio2 ===
 * Same algorithm as src/asm/runtime_math_libm.x. Helpers are static (not
 * part of the public math_*_c ABI). PLATFORM: SHARED — FP_CONTRACT already
 * OFF above this block.
 */
static int32_t hi_of(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  return (int32_t)(v.u >> 32);
}
static int32_t lo_of(double x) {
  union { double d; uint64_t u; } v; v.d = x;
  return (int32_t)(v.u & 0xffffffffu);
}
static void set_hi(double *x, int32_t h) {
  union { double d; uint64_t u; } v; v.d = *x;
  v.u = ((uint64_t)(uint32_t)h << 32) | (v.u & 0xffffffffull);
  *x = v.d;
}
static void set_lo(double *x, int32_t l) {
  union { double d; uint64_t u; } v; v.d = *x;
  v.u = (v.u & 0xffffffff00000000ull) | (uint32_t)l;
  *x = v.d;
}
/* fdlibm s_scalbn.c (needed by k_rem_pio2). */
static double twin_scalbn(double x, int n) {
  const double two54 = 18014398509481984.0;
  const double twom54 = 5.5511151231257827e-17;
  union { double d; uint64_t u; } huge, tiny;
  huge.u = 9094988921128908188ull; /* 1e300 */
  tiny.u = 118622047889322841ull;  /* 1e-300 */
  union { double d; uint64_t u; } v; v.d = x;
  int32_t hx = (int32_t)(v.u >> 32);
  int32_t lx = (int32_t)(v.u & 0xffffffffu);
  int32_t k = (hx & 0x7ff00000) >> 20;
  if (k == 0) {
    if ((lx | (hx & 0x7fffffff)) == 0) return x;
    v.d = x * two54;
    hx = (int32_t)(v.u >> 32);
    k = ((hx & 0x7ff00000) >> 20) - 54;
    if (n < -50000) return tiny.d * x;
  }
  if (k == 0x7ff) return x + x;
  k = k + n;
  if (k > 0x7fe) {
    double s = (hx < 0) ? -huge.d : huge.d;
    return huge.d * s;
  }
  if (k > 0) {
    uint32_t nhx = ((uint32_t)hx & 0x800fffffu) | ((uint32_t)k << 20);
    v.u = ((uint64_t)nhx << 32) | (v.u & 0xffffffffull);
    return v.d;
  }
  if (k <= -54) {
    if (n > 50000) {
      double s = (hx < 0) ? -huge.d : huge.d;
      return huge.d * s;
    }
    double s = (hx < 0) ? -tiny.d : tiny.d;
    return tiny.d * s;
  }
  k += 54;
  {
    uint32_t nhx = ((uint32_t)hx & 0x800fffffu) | ((uint32_t)k << 20);
    v.u = ((uint64_t)nhx << 32) | (v.u & 0xffffffffull);
    return v.d * twom54;
  }
}

static double twin_floor(double x) { return floor(x); }

/* ---- two_over_pi 24-bit chunks (all fit in positive i32) ---- */
static const int32_t two_over_pi[66] = {
  10680707, 7228996, 1387004, 2578385, 16069853, 12639074,
  9804092, 4427841, 16666979, 11263675, 12935607, 2387514,
  4345298, 14681673, 3074569, 13734428, 16653803, 1880361,
  10960616, 8533493, 3062596, 8710556, 7349940, 6258241,
  3772886, 3769171, 3798172, 8675211, 12450088, 3874808,
  9961438, 366607, 15675153, 9132554, 7151469, 3571407,
  2607881, 12013382, 4155038, 6285869, 7677882, 13102053,
  15825725, 473591, 9065106, 15363067, 6271263, 9264392,
  5636912, 4652155, 7056368, 13614112, 10155062, 1944035,
  9527646, 15080200, 6658437, 6231200, 6832269, 16767104,
  5075751, 3212806, 1398474, 7579849, 6349435, 12618859
};
static const int32_t npio2_hw[32] = {
  1073291771, 1074340347, 1074977148, 1075388923, 1075800698, 1076025724,
  1076231611, 1076437499, 1076643386, 1076849274, 1076971356, 1077074300,
  1077177244, 1077280187, 1077383131, 1077486075, 1077589019, 1077691962,
  1077794906, 1077897850, 1077968460, 1078019932, 1078071404, 1078122876,
  1078174348, 1078225820, 1078277292, 1078328763, 1078380235, 1078431707,
  1078483179, 1078534651
};

/* ---- k_sin ---- */
static double kernel_sin(double x, double y, int iy) {
  const double half = 0.5;
  const double S1 = -1.66666666666666324348e-01;
  const double S2 =  8.33333333332248946124e-03;
  const double S3 = -1.98412698298579493134e-04;
  const double S4 =  2.75573137070700676789e-06;
  const double S5 = -2.50507602534068634195e-08;
  const double S6 =  1.58969099521155010221e-10;
  int32_t ix = hi_of(x) & 0x7fffffff;
  if (ix < 0x3e400000) {
    if ((int)x == 0) return x;
  }
  double z = x * x;
  double v = z * x;
  double r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
  if (iy == 0) return x + v * (S1 + z * r);
  return x - ((z * (half * y - v * r) - y) - v * S1);
}

/* ---- k_cos ---- */
static double kernel_cos(double x, double y) {
  const double one = 1.0;
  const double C1 =  4.16666666666666019037e-02;
  const double C2 = -1.38888888888741095749e-03;
  const double C3 =  2.48015872894767294178e-05;
  const double C4 = -2.75573143513906633035e-07;
  const double C5 =  2.08757232129817482790e-09;
  const double C6 = -1.13596475577881948265e-11;
  int32_t ix = hi_of(x) & 0x7fffffff;
  if (ix < 0x3e400000) {
    if ((int)x == 0) return one;
  }
  double z = x * x;
  double r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
  if (ix < 0x3FD33333) return one - (0.5 * z - (z * r - x * y));
  double qx;
  if (ix > 0x3fe90000) {
    qx = 0.28125;
  } else {
    qx = 0.0;
    set_hi(&qx, ix - 0x00200000);
    set_lo(&qx, 0);
  }
  double hz = 0.5 * z - qx;
  double a = one - qx;
  return a - (hz - (z * r - x * y));
}

/* ---- k_tan ---- */
static double kernel_tan(double x, double y, int iy) {
  const double T0 =  3.33333333333334091986e-01;
  const double T1 =  1.33333333333201242699e-01;
  const double T2 =  5.39682539762260521377e-02;
  const double T3 =  2.18694882948595424599e-02;
  const double T4 =  8.86323982359930005737e-03;
  const double T5 =  3.59207910759131235356e-03;
  const double T6 =  1.45620945432529025516e-03;
  const double T7 =  5.88041240820264096874e-04;
  const double T8 =  2.46463134818469906812e-04;
  const double T9 =  7.81794442939557092300e-05;
  const double T10 = 7.14072491382608190305e-05;
  const double T11 = -1.85586374855275456654e-05;
  const double T12 = 2.59073051863633712884e-05;
  const double one = 1.0;
  const double pio4 = 7.85398163397448278999e-01;
  const double pio4lo = 3.06161699786838301793e-17;
  int32_t hx = hi_of(x);
  int32_t ix = hx & 0x7fffffff;
  if (ix < 0x3e300000) {
    if ((int)x == 0) {
      if (((ix | lo_of(x)) | (iy + 1)) == 0) return one / fabs(x);
      else {
        if (iy == 1) return x;
        else {
          double z, w, v, t, a, s;
          z = w = x + y;
          set_lo(&z, 0);
          v = y - (z - x);
          t = a = -one / w;
          set_lo(&t, 0);
          s = one + t * z;
          return t + a * (s + t * v);
        }
      }
    }
  }
  if (ix >= 0x3FE59428) {
    if (hx < 0) { x = -x; y = -y; }
    double z = pio4 - x;
    double w = pio4lo - y;
    x = z + w;
    y = 0.0;
  }
  {
    double z = x * x;
    double w = z * z;
    double r = T1 + w * (T3 + w * (T5 + w * (T7 + w * (T9 + w * T11))));
    double v = z * (T2 + w * (T4 + w * (T6 + w * (T8 + w * (T10 + w * T12)))));
    double s = z * x;
    r = y + z * (s * (r + v) + y);
    r += T0 * s;
    w = x + r;
    if (ix >= 0x3FE59428) {
      double vv = (double)iy;
      return (double)(1 - ((hx >> 30) & 2)) * (vv - 2.0 * (x - (w * w / (w + vv) - r)));
    }
    if (iy == 1) return w;
    {
      double a, t, z2, v2, s2;
      z2 = w;
      set_lo(&z2, 0);
      v2 = r - (z2 - x);
      t = a = -1.0 / w;
      set_lo(&t, 0);
      s2 = 1.0 + t * z2;
      return t + a * (s2 + t * v2);
    }
  }
}

/* ---- k_rem_pio2 (prec=2 path used by e_rem_pio2) ---- */
static const double PIo2[8] = {
  1.57079625129699707031e+00,
  7.54978941586159635335e-08,
  5.39030252995776476554e-15,
  3.28200341580791294123e-22,
  1.27065575308067607349e-29,
  1.22933308981111328932e-36,
  2.73370053816464559624e-44,
  2.16741683877804819444e-51
};

static int kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int32_t *ipio2) {
  const double zero = 0.0, one = 1.0;
  const double two24 = 16777216.0;
  const double twon24 = 5.9604644775390625e-08;
  const int init_jk[4] = {2, 3, 4, 6};
  int jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
  double z, fw, f[20], fq[20], q[20];
  jk = init_jk[prec];
  jp = jk;
  jx = nx - 1;
  jv = (e0 - 3) / 24; if (jv < 0) jv = 0;
  q0 = e0 - 24 * (jv + 1);
  j = jv - jx; m = jx + jk;
  for (i = 0; i <= m; i++, j++) f[i] = (j < 0) ? zero : (double)ipio2[j];
  for (i = 0; i <= jk; i++) {
    for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j];
    q[i] = fw;
  }
  jz = jk;
recompute:
  for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
    fw = (double)((int)(twon24 * z));
    iq[i] = (int)(z - two24 * fw);
    z = q[j - 1] + fw;
  }
  z = twin_scalbn(z, q0);
  z -= 8.0 * twin_floor(z * 0.125);
  n = (int)z;
  z -= (double)n;
  ih = 0;
  if (q0 > 0) {
    i = (iq[jz - 1] >> (24 - q0)); n += i;
    iq[jz - 1] -= i << (24 - q0);
    ih = iq[jz - 1] >> (23 - q0);
  } else if (q0 == 0) ih = iq[jz - 1] >> 23;
  else if (z >= 0.5) ih = 2;
  if (ih > 0) {
    n += 1; carry = 0;
    for (i = 0; i < jz; i++) {
      j = iq[i];
      if (carry == 0) {
        if (j != 0) { carry = 1; iq[i] = 0x1000000 - j; }
      } else iq[i] = 0xffffff - j;
    }
    if (q0 > 0) {
      if (q0 == 1) iq[jz - 1] &= 0x7fffff;
      else if (q0 == 2) iq[jz - 1] &= 0x3fffff;
    }
    if (ih == 2) {
      z = one - z;
      if (carry != 0) z -= twin_scalbn(one, q0);
    }
  }
  if (z == zero) {
    j = 0;
    for (i = jz - 1; i >= jk; i--) j |= iq[i];
    if (j == 0) {
      for (k = 1; iq[jk - k] == 0; k++);
      for (i = jz + 1; i <= jz + k; i++) {
        f[jx + i] = (double)ipio2[jv + i];
        for (j = 0, fw = 0.0; j <= jx; j++) fw += x[j] * f[jx + i - j];
        q[i] = fw;
      }
      jz += k;
      goto recompute;
    }
  }
  if (z == 0.0) {
    jz -= 1; q0 -= 24;
    while (iq[jz] == 0) { jz--; q0 -= 24; }
  } else {
    z = twin_scalbn(z, -q0);
    if (z >= two24) {
      fw = (double)((int)(twon24 * z));
      iq[jz] = (int)(z - two24 * fw);
      jz += 1; q0 += 24;
      iq[jz] = (int)fw;
    } else iq[jz] = (int)z;
  }
  fw = twin_scalbn(one, q0);
  for (i = jz; i >= 0; i--) {
    q[i] = fw * (double)iq[i]; fw *= twon24;
  }
  for (i = jz; i >= 0; i--) {
    for (fw = 0.0, k = 0; k <= jp && k <= jz - i; k++) fw += PIo2[k] * q[i + k];
    fq[jz - i] = fw;
  }
  /* prec is 2 for double */
  fw = 0.0;
  for (i = jz; i >= 0; i--) fw += fq[i];
  y[0] = (ih == 0) ? fw : -fw;
  fw = fq[0] - fw;
  for (i = 1; i <= jz; i++) fw += fq[i];
  y[1] = (ih == 0) ? fw : -fw;
  return n & 7;
}

/* ---- e_rem_pio2 ---- */
static int rem_pio2(double x, double *y) {
  const double half = 0.5;
  const double two24 = 16777216.0;
  const double invpio2 = 6.36619772367581382433e-01;
  const double pio2_1  = 1.57079632673412561417e+00;
  const double pio2_1t = 6.07710050650619224932e-11;
  const double pio2_2  = 6.07710050630396597660e-11;
  const double pio2_2t = 2.02226624879595063154e-21;
  const double pio2_3  = 2.02226624871116645580e-21;
  const double pio2_3t = 8.47842766036889956997e-32;
  double z, w, t, r, fn;
  double tx[3];
  int e0, i, j, nx, n, ix, hx;
  hx = hi_of(x);
  ix = hx & 0x7fffffff;
  if (ix <= 0x3fe921fb) { y[0] = x; y[1] = 0; return 0; }
  if (ix < 0x4002d97c) {
    if (hx > 0) {
      z = x - pio2_1;
      if (ix != 0x3ff921fb) {
        y[0] = z - pio2_1t;
        y[1] = (z - y[0]) - pio2_1t;
      } else {
        z -= pio2_2;
        y[0] = z - pio2_2t;
        y[1] = (z - y[0]) - pio2_2t;
      }
      return 1;
    } else {
      z = x + pio2_1;
      if (ix != 0x3ff921fb) {
        y[0] = z + pio2_1t;
        y[1] = (z - y[0]) + pio2_1t;
      } else {
        z += pio2_2;
        y[0] = z + pio2_2t;
        y[1] = (z - y[0]) + pio2_2t;
      }
      return -1;
    }
  }
  if (ix <= 0x413921fb) {
    t = fabs(x);
    n = (int)(t * invpio2 + half);
    fn = (double)n;
    r = t - fn * pio2_1;
    w = fn * pio2_1t;
    if (n < 32 && ix != npio2_hw[n - 1]) {
      y[0] = r - w;
    } else {
      j = ix >> 20;
      y[0] = r - w;
      i = j - ((hi_of(y[0]) >> 20) & 0x7ff);
      if (i > 16) {
        t = r;
        w = fn * pio2_2;
        r = t - w;
        w = fn * pio2_2t - ((t - r) - w);
        y[0] = r - w;
        i = j - ((hi_of(y[0]) >> 20) & 0x7ff);
        if (i > 49) {
          t = r;
          w = fn * pio2_3;
          r = t - w;
          w = fn * pio2_3t - ((t - r) - w);
          y[0] = r - w;
        }
      }
    }
    y[1] = (r - y[0]) - w;
    if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
    else return n;
  }
  if (ix >= 0x7ff00000) { y[0] = y[1] = x - x; return 0; }
  z = 0.0;
  set_lo(&z, lo_of(x));
  e0 = (ix >> 20) - 1046;
  set_hi(&z, ix - (e0 << 20));
  for (i = 0; i < 2; i++) {
    tx[i] = (double)((int)(z));
    z = (z - tx[i]) * two24;
  }
  tx[2] = z;
  nx = 3;
  while (tx[nx - 1] == 0.0) nx--;
  n = kernel_rem_pio2(tx, y, e0, nx, 2, two_over_pi);
  if (hx < 0) { y[0] = -y[0]; y[1] = -y[1]; return -n; }
  return n;
}

double math_sin_c(double x) {
  double y[2], z = 0.0;
  int n, ix;
  ix = hi_of(x);
  ix &= 0x7fffffff;
  if (ix <= 0x3fe921fb) return kernel_sin(x, z, 0);
  else if (ix >= 0x7ff00000) return x - x;
  else {
    n = rem_pio2(x, y);
    switch (n & 3) {
      case 0: return kernel_sin(y[0], y[1], 1);
      case 1: return kernel_cos(y[0], y[1]);
      case 2: return -kernel_sin(y[0], y[1], 1);
      default: return -kernel_cos(y[0], y[1]);
    }
  }
}

double math_cos_c(double x) {
  double y[2], z = 0.0;
  int n, ix;
  ix = hi_of(x);
  ix &= 0x7fffffff;
  if (ix <= 0x3fe921fb) return kernel_cos(x, z);
  else if (ix >= 0x7ff00000) return x - x;
  else {
    n = rem_pio2(x, y);
    switch (n & 3) {
      case 0: return kernel_cos(y[0], y[1]);
      case 1: return -kernel_sin(y[0], y[1], 1);
      case 2: return -kernel_cos(y[0], y[1]);
      default: return kernel_sin(y[0], y[1], 1);
    }
  }
}

double math_tan_c(double x) {
  double y[2], z = 0.0;
  int n, ix;
  ix = hi_of(x);
  ix &= 0x7fffffff;
  if (ix <= 0x3fe921fb) return kernel_tan(x, z, 1);
  else if (ix >= 0x7ff00000) return x - x;
  else {
    n = rem_pio2(x, y);
    return kernel_tan(y[0], y[1], 1 - ((n & 1) << 1));
  }
}

/* fdlibm e_pow.c cold twin — isomorphic with math_pow_c in
 * src/asm/runtime_math_libm.x. Decimal literals are the fdlibm source
 * constants (Python-verified against the hex comments). huge/tiny are
 * the same bit-puns as the .x authority. y==+0.5 uses math_sqrt_c;
 * subnormal 2**n uses twin_scalbn. PLATFORM: SHARED. */
double math_pow_c(double base, double exp) {
  static const double bp0 = 1.0, bp1 = 1.5;
  static const double dp_h0 = 0.0, dp_h1 = 5.84962487220764160156e-01;
  static const double dp_l0 = 0.0, dp_l1 = 1.35003920212974897128e-08;
  static const double zero = 0.0, one = 1.0, two = 2.0;
  static const double two53 = 9007199254740992.0;
  static const double L1 = 5.99999999999994648725e-01;
  static const double L2 = 4.28571428578550184252e-01;
  static const double L3 = 3.33333329818377432918e-01;
  static const double L4 = 2.72728123808534006489e-01;
  static const double L5 = 2.30660745775561754067e-01;
  static const double L6 = 2.06975017800338417784e-01;
  static const double P1 = 1.66666666666666019037e-01;
  static const double P2 = -2.77777777770155933842e-03;
  static const double P3 = 6.61375632143793436117e-05;
  static const double P4 = -1.65339022054652515390e-06;
  static const double P5 = 4.13813679705723846039e-08;
  static const double lg2 = 6.93147180559945286227e-01;
  static const double lg2_h = 6.93147182464599609375e-01;
  static const double lg2_l = -1.90465429995776804525e-09;
  static const double ovt = 8.0085662595372944372e-17;
  static const double cp = 9.61796693925975554329e-01;
  static const double cp_h = 9.61796700954437255859e-01;
  static const double cp_l = -7.02846165095275826516e-09;
  static const double ivln2 = 1.44269504088896338700e+00;
  static const double ivln2_h = 1.44269502162933349609e+00;
  static const double ivln2_l = 1.92596299112661746887e-08;
  union { double d; uint64_t u; } hugeu, tinyu;
  hugeu.u = 9094988921128908188ull; /* 1e300 */
  tinyu.u = 118622047889322841ull;  /* 1e-300 */
  double huge = hugeu.d, tiny = tinyu.d;
  double x = base, y = exp;
  double z, ax, z_h, z_l, p_h, p_l;
  double y1, t1, t2, r, s, t, u, v, w;
  int i, j, k, yisint, n, xsign;
  int hx, hy, ix, iy;
  unsigned lx, ly;

  hx = hi_of(x); lx = (unsigned)lo_of(x);
  hy = hi_of(y); ly = (unsigned)lo_of(y);
  ix = hx & 0x7fffffff; iy = hy & 0x7fffffff;

  if ((iy | ly) == 0) return one;

  if (ix > 0x7ff00000 || ((ix == 0x7ff00000) && (lx != 0)) ||
      iy > 0x7ff00000 || ((iy == 0x7ff00000) && (ly != 0)))
    return x + y;

  yisint = 0;
  if (hx < 0) {
    if (iy >= 0x43400000) yisint = 2;
    else if (iy >= 0x3ff00000) {
      k = (iy >> 20) - 0x3ff;
      if (k > 20) {
        j = (int)(ly >> (52 - k));
        if (((unsigned)(j << (52 - k))) == ly) yisint = 2 - (j & 1);
      } else if (ly == 0) {
        j = iy >> (20 - k);
        if ((j << (20 - k)) == iy) yisint = 2 - (j & 1);
      }
    }
  }

  if (ly == 0) {
    if (iy == 0x7ff00000) {
      if ((ix == 0x3ff00000) && (lx == 0))
        return y - y;
      else if (ix >= 0x3ff00000)
        return (hy >= 0) ? y : zero;
      else
        return (hy < 0) ? -y : zero;
    }
    if (iy == 0x3ff00000) {
      if (hy < 0) return one / x; else return x;
    }
    if (hy == 0x40000000) return x * x;
    if (hy == 0x3fe00000) {
      if (hx >= 0) return math_sqrt_c(x);
    }
  }

  ax = x;
  set_hi(&ax, ix);
  if (lx == 0) {
    if (ix == 0x7ff00000 || ix == 0 || ix == 0x3ff00000) {
      z = ax;
      if (hy < 0) z = one / z;
      if (hx < 0) {
        if ((ix == 0x3ff00000) && (yisint == 0))
          z = (z - z) / (z - z);
        else if (yisint == 1)
          z = -z;
      }
      return z;
    }
  }

  xsign = (hx < 0) ? 0 : 1;
  if ((xsign | yisint) == 0) return (x - x) / (x - x);

  s = one;
  if ((xsign | (yisint - 1)) == 0) s = -one;

  if (iy > 0x41e00000) {
    if (iy > 0x43f00000) {
      if (ix <= 0x3fefffff) return (hy < 0) ? huge * huge : tiny * tiny;
      if (ix >= 0x3ff00000) return (hy > 0) ? huge * huge : tiny * tiny;
    }
    if (ix < 0x3fefffff) return (hy < 0) ? s * huge * huge : s * tiny * tiny;
    if (ix > 0x3ff00000) return (hy > 0) ? s * huge * huge : s * tiny * tiny;
    t = ax - one;
    w = (t * t) * (0.5 - t * (0.3333333333333333333333 - t * 0.25));
    u = ivln2_h * t;
    v = t * ivln2_l - w * ivln2;
    t1 = u + v;
    set_lo(&t1, 0);
    t2 = v - (t1 - u);
  } else {
    double ss, s2, s_h, s_l, t_h, t_l;
    double bp_k, dp_h_k, dp_l_k;
    n = 0;
    if (ix < 0x00100000) {
      ax *= two53; n -= 53; ix = hi_of(ax);
    }
    n += (ix >> 20) - 0x3ff;
    j = ix & 0x000fffff;
    ix = j | 0x3ff00000;
    if (j <= 0x3988E) k = 0;
    else if (j < 0xBB67A) k = 1;
    else { k = 0; n += 1; ix -= 0x00100000; }
    set_hi(&ax, ix);

    if (k == 0) { bp_k = bp0; dp_h_k = dp_h0; dp_l_k = dp_l0; }
    else { bp_k = bp1; dp_h_k = dp_h1; dp_l_k = dp_l1; }

    u = ax - bp_k;
    v = one / (ax + bp_k);
    ss = u * v;
    s_h = ss;
    set_lo(&s_h, 0);
    t_h = zero;
    set_hi(&t_h, ((ix >> 1) | 0x20000000) + 0x00080000 + (k << 18));
    t_l = ax - (t_h - bp_k);
    s_l = v * ((u - s_h * t_h) - s_h * t_l);
    s2 = ss * ss;
    r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
    r += s_l * (s_h + ss);
    s2 = s_h * s_h;
    t_h = 3.0 + s2 + r;
    set_lo(&t_h, 0);
    t_l = r - ((t_h - 3.0) - s2);
    u = s_h * t_h;
    v = s_l * t_h + t_l * ss;
    p_h = u + v;
    set_lo(&p_h, 0);
    p_l = v - (p_h - u);
    z_h = cp_h * p_h;
    z_l = cp_l * p_h + p_l * cp + dp_l_k;
    t = (double)n;
    t1 = (((z_h + z_l) + dp_h_k) + t);
    set_lo(&t1, 0);
    t2 = z_l - (((t1 - t) - dp_h_k) - z_h);
  }

  y1 = y;
  set_lo(&y1, 0);
  p_l = (y - y1) * t1 + y * t2;
  p_h = y1 * t1;
  z = p_l + p_h;
  j = hi_of(z);
  i = lo_of(z);
  if (j >= 0x40900000) {
    if (((j - 0x40900000) | i) != 0)
      return s * huge * huge;
    else {
      if (p_l + ovt > z - p_h) return s * huge * huge;
    }
  } else if ((j & 0x7fffffff) >= 0x4090cc00) {
    if (((j + 1064252416) | i) != 0)
      return s * tiny * tiny;
    else {
      if (p_l <= z - p_h) return s * tiny * tiny;
    }
  }

  i = j & 0x7fffffff;
  k = (i >> 20) - 0x3ff;
  n = 0;
  if (i > 0x3fe00000) {
    n = j + (0x00100000 >> (k + 1));
    k = ((n & 0x7fffffff) >> 20) - 0x3ff;
    t = zero;
    set_hi(&t, n & ~(0x000fffff >> k));
    n = ((n & 0x000fffff) | 0x00100000) >> (20 - k);
    if (j < 0) n = -n;
    p_h -= t;
  }
  t = p_l + p_h;
  set_lo(&t, 0);
  u = t * lg2_h;
  v = (p_l - (t - p_h)) * lg2 + t * lg2_l;
  z = u + v;
  w = v - (z - u);
  t = z * z;
  t1 = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
  r = (z * t1) / (t1 - two) - (w + z * w);
  z = one - (r - z);
  j = hi_of(z);
  j += (n << 20);
  if ((j >> 20) <= 0) z = twin_scalbn(z, n);
  else {
    set_hi(&z, hi_of(z) + (n << 20));
  }
  return s * z;
}

/* fdlibm e_asin.c / e_acos.c / s_atan.c cold twins — isomorphic with
 * math_asin_c / math_acos_c / math_atan_c in src/asm/runtime_math_libm.x.
 * Shared R(t)=p/q lives in twin_asin_rational (G.7). |x| via set_hi
 * (fabs lives later). y-range sqrt uses math_sqrt_c. Decimal literals
 * are the fdlibm source constants (Python-verified against the hex
 * comments). PLATFORM: SHARED. */
static double twin_asin_rational(double t) {
  static const double pS0 = 1.66666666666666657415e-01;
  static const double pS1 = -3.25565818622400915405e-01;
  static const double pS2 = 2.01212532134862925881e-01;
  static const double pS3 = -4.00555345006794114027e-02;
  static const double pS4 = 7.91534994289814532176e-04;
  static const double pS5 = 3.47933107596021167570e-05;
  static const double qS1 = -2.40339491173441421878e+00;
  static const double qS2 = 2.02094576023350569471e+00;
  static const double qS3 = -6.88283971605453293030e-01;
  static const double qS4 = 7.70381505559019352791e-02;
  static const double one = 1.0;
  double p = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
  double q = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
  return p / q;
}

double math_asin_c(double x) {
  static const double one = 1.0;
  static const double pio2_hi = 1.57079632679489655800e+00;
  static const double pio2_lo = 6.12323399573676603587e-17;
  static const double pio4_hi = 7.85398163397448278999e-01;
  union { double d; uint64_t u; } huge;
  huge.u = 9094988921128908188ull; /* 1e300 */
  double t, w, c, r, s;
  int32_t hx = hi_of(x);
  int32_t ix = hx & 0x7fffffff;
  if (ix >= 0x3ff00000) {
    if (((ix - 0x3ff00000) | lo_of(x)) == 0)
      return x * pio2_hi + x * pio2_lo;
    return (x - x) / (x - x);
  } else if (ix < 0x3fe00000) {
    if (ix < 0x3e400000) {
      if (huge.d + x > one) return x;
      return x;
    }
    return x + x * twin_asin_rational(x * x);
  }
  w = x;
  set_hi(&w, ix);
  w = one - w;
  t = w * 0.5;
  r = twin_asin_rational(t);
  s = math_sqrt_c(t);
  if (ix >= 0x3FEF3333) {
    t = pio2_hi - (2.0 * (s + s * r) - pio2_lo);
  } else {
    w = s;
    set_lo(&w, 0);
    c = (t - w * w) / (s + w);
    r = 2.0 * s * r - (pio2_lo - 2.0 * c);
    t = pio4_hi - (r - (pio4_hi - 2.0 * w));
  }
  if (hx > 0) return t;
  return -t;
}

double math_acos_c(double x) {
  static const double one = 1.0;
  static const double pi = 3.14159265358979311600e+00;
  static const double pio2_hi = 1.57079632679489655800e+00;
  static const double pio2_lo = 6.12323399573676603587e-17;
  double z, r, w, s, c, df;
  int32_t hx = hi_of(x);
  int32_t ix = hx & 0x7fffffff;
  if (ix >= 0x3ff00000) {
    if (((ix - 0x3ff00000) | lo_of(x)) == 0) {
      if (hx > 0) return 0.0;
      return pi + 2.0 * pio2_lo;
    }
    return (x - x) / (x - x);
  }
  if (ix < 0x3fe00000) {
    if (ix <= 0x3c600000) return pio2_hi + pio2_lo;
    r = twin_asin_rational(x * x);
    return pio2_hi - (x - (pio2_lo - x * r));
  } else if (hx < 0) {
    z = (one + x) * 0.5;
    s = math_sqrt_c(z);
    r = twin_asin_rational(z);
    w = r * s - pio2_lo;
    return pi - 2.0 * (s + w);
  }
  z = (one - x) * 0.5;
  s = math_sqrt_c(z);
  df = s;
  set_lo(&df, 0);
  c = (z - df * df) / (s + df);
  r = twin_asin_rational(z);
  w = r * s + c;
  return 2.0 * (df + w);
}

double math_atan_c(double x) {
  static const double atanhi0 = 4.63647609000806093515e-01;
  static const double atanhi1 = 7.85398163397448278999e-01;
  static const double atanhi2 = 9.82793723247329054082e-01;
  static const double atanhi3 = 1.57079632679489655800e+00;
  static const double atanlo0 = 2.26987774529616870924e-17;
  static const double atanlo1 = 3.06161699786838301793e-17;
  static const double atanlo2 = 1.39033110312309984516e-17;
  static const double atanlo3 = 6.12323399573676603587e-17;
  static const double aT0 = 3.33333333333329318027e-01;
  static const double aT1 = -1.99999999998764832476e-01;
  static const double aT2 = 1.42857142725034663711e-01;
  static const double aT3 = -1.11111104054623557880e-01;
  static const double aT4 = 9.09088713343650656196e-02;
  static const double aT5 = -7.69187620504482999495e-02;
  static const double aT6 = 6.66107313738753120669e-02;
  static const double aT7 = -5.83357013379057348645e-02;
  static const double aT8 = 4.97687799461593236017e-02;
  static const double aT9 = -3.65315727442169155270e-02;
  static const double aT10 = 1.62858201153657823623e-02;
  static const double one = 1.0;
  union { double d; uint64_t u; } huge;
  huge.u = 9094988921128908188ull; /* 1e300 */
  double w, s1, s2, z, xx = x;
  int32_t hx = hi_of(x);
  int32_t ix = hx & 0x7fffffff;
  int32_t id = -1;
  if (ix >= 0x44100000) {
    if (ix > 0x7ff00000 || (ix == 0x7ff00000 && (lo_of(x) != 0)))
      return x + x;
    if (hx > 0) return atanhi3 + atanlo3;
    return -atanhi3 - atanlo3;
  }
  if (ix < 0x3fdc0000) {
    if (ix < 0x3e200000) {
      if (huge.d + x > one) return x;
    }
    id = -1;
  } else {
    set_hi(&xx, ix);
    if (ix < 0x3ff30000) {
      if (ix < 0x3fe60000) {
        id = 0; xx = (2.0 * xx - one) / (2.0 + xx);
      } else {
        id = 1; xx = (xx - one) / (xx + one);
      }
    } else {
      if (ix < 0x40038000) {
        id = 2; xx = (xx - 1.5) / (one + 1.5 * xx);
      } else {
        id = 3; xx = -1.0 / xx;
      }
    }
  }
  z = xx * xx;
  w = z * z;
  s1 = z * (aT0 + w * (aT2 + w * (aT4 + w * (aT6 + w * (aT8 + w * aT10)))));
  s2 = w * (aT1 + w * (aT3 + w * (aT5 + w * (aT7 + w * aT9))));
  if (id < 0) return xx - xx * (s1 + s2);
  if (id == 0) z = atanhi0 - ((xx * (s1 + s2) - atanlo0) - xx);
  else if (id == 1) z = atanhi1 - ((xx * (s1 + s2) - atanlo1) - xx);
  else if (id == 2) z = atanhi2 - ((xx * (s1 + s2) - atanlo2) - xx);
  else z = atanhi3 - ((xx * (s1 + s2) - atanlo3) - xx);
  if (hx < 0) return -z;
  return z;
}

/* fdlibm e_atan2.c cold twin — isomorphic with math_atan2_c in
 * src/asm/runtime_math_libm.x. Reuses math_atan_c (G.7). |y/x| via
 * set_hi (fabs lives later). tiny is 1e-300 bit-pun. PLATFORM: SHARED. */
double math_atan2_c(double y, double x) {
  static const double pi_o_4 = 7.8539816339744827900E-01;
  static const double pi_o_2 = 1.5707963267948965580E+00;
  static const double pi = 3.1415926535897931160E+00;
  static const double pi_lo = 1.2246467991473531772E-16;
  union { double d; uint64_t u; } tiny;
  tiny.u = 118622047889322841ull; /* 1e-300 */
  double z, ax;
  int32_t k, m, hx, hy, ix, iy, lx, ly;
  hx = hi_of(x); ix = hx & 0x7fffffff; lx = lo_of(x);
  hy = hi_of(y); iy = hy & 0x7fffffff; ly = lo_of(y);
  if ((ix > 0x7ff00000) || ((ix == 0x7ff00000) && (lx != 0)) ||
      (iy > 0x7ff00000) || ((iy == 0x7ff00000) && (ly != 0)))
    return x + y;
  if (((hx - 0x3ff00000) | lx) == 0)
    return math_atan_c(y);
  m = ((hy >> 31) & 1) | ((hx >> 30) & 2);
  if ((iy | ly) == 0) {
    if (m <= 1) return y;
    if (m == 2) return pi + tiny.d;
    return -pi - tiny.d;
  }
  if ((ix | lx) == 0)
    return (hy < 0) ? -pi_o_2 - tiny.d : pi_o_2 + tiny.d;
  if (ix == 0x7ff00000) {
    if (iy == 0x7ff00000) {
      if (m == 0) return pi_o_4 + tiny.d;
      if (m == 1) return -pi_o_4 - tiny.d;
      if (m == 2) return 3.0 * pi_o_4 + tiny.d;
      return -3.0 * pi_o_4 - tiny.d;
    }
    if (m == 0) return 0.0;
    if (m == 1) return -0.0;
    if (m == 2) return pi + tiny.d;
    return -pi - tiny.d;
  }
  if (iy == 0x7ff00000)
    return (hy < 0) ? -pi_o_2 - tiny.d : pi_o_2 + tiny.d;
  k = (iy - ix) >> 20;
  if (k > 60)
    z = pi_o_2 + 0.5 * pi_lo;
  else if (hx < 0 && k < -60)
    z = 0.0;
  else {
    ax = y / x;
    set_hi(&ax, hi_of(ax) & 0x7fffffff);
    z = math_atan_c(ax);
  }
  if (m == 0) return z;
  if (m == 1) {
    set_hi(&z, hi_of(z) ^ (int32_t)0x80000000);
    return z;
  }
  if (m == 2) return pi - (z - pi_lo);
  return (z - pi_lo) - pi;
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
