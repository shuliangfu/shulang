/* seeds/runtime_math_libm_surface.from_x.c
 * G-02f runtime_math_libm R2 mixed surface - isomorphic with src/asm/runtime_math_libm.x
 * Product PREFER_X_O: xlang-c -E(.x) -> thin.o + ld -r with rest (seeds/runtime_math_libm.from_x.c)
 * Prove: full.x vs this surface -> nm IDENTICAL (34 #[no_mangle])
 * Mode: mixed - 2 DIRECT compute + thin+rest forwards to _impl
 *   + 6 full implementations (9.2.4: math_exp_c / math_log_c / math_sqrt_c /
 *   math_cbrt_c / math_expm1_c / math_log1p_c fdlibm ports, isomorphic with
 *   the .x authority; the six matching math_*_impl bridges are gone).
 * Cap residual: remaining extern bridges (math_*_impl) for sin/pow/erf/...
 * No doc_anchor (runtime_math_libm.x has none).
 * Note: math_ prefix not trigger ast_ (confirmed wave545+).
 * Logic: 34 functions = 2 DIRECT (math_signum_c + math_special_near)
 *   + thin+rest forwards to math_*_impl + 6 full impls
 *   (exp/log/sqrt/cbrt/expm1/log1p).
 * Regen: ./xlang-c -E ... runtime_math_libm.x | filter DBG + polish prologue
 */
#include <stdint.h>
#include <stddef.h>
extern double math_signum_c(double x);
extern int32_t math_special_near(double a, double b, double eps);
extern double math_floor_c(double x);
extern double math_ceil_c(double x);
extern double math_trunc_c(double x);
extern double math_round_c(double x);
extern double math_sin_c(double x);
extern double math_cos_c(double x);
extern double math_tan_c(double x);
extern double math_asin_c(double x);
extern double math_acos_c(double x);
extern double math_atan_c(double x);
extern double math_atan2_c(double y, double x);
extern double math_sqrt_c(double x);
extern double math_cbrt_c(double x);
extern double math_pow_c(double base, double exp);
extern double math_exp_c(double x);
extern double math_log_c(double x);
extern double math_fabs_c(double x);
extern double math_fmin_c(double a, double b);
extern double math_fmax_c(double a, double b);
extern double math_erf_c(double x);
extern double math_erfc_c(double x);
extern double math_log1p_c(double x);
extern double math_expm1_c(double x);
extern int32_t math_fenv_mask_to_fe(int32_t mask);
extern int32_t math_fenv_fe_to_mask(int32_t fe);
extern void math_fenv_emit_cap_report(int32_t avail);
extern int32_t math_fenv_available_c(void);
extern int32_t math_fenv_test_c(int32_t mask);
extern int32_t math_fenv_clear_c(int32_t mask);
extern int32_t math_fenv_raise_c(int32_t mask);
extern int32_t math_fenv_smoke_c(void);
extern int32_t math_fenv_capability_smoke_c(void);
extern double math_floor_impl(double x);
extern double math_ceil_impl(double x);
extern double math_trunc_impl(double x);
extern double math_round_impl(double x);
extern double math_sin_impl(double x);
extern double math_cos_impl(double x);
extern double math_tan_impl(double x);
extern double math_asin_impl(double x);
extern double math_acos_impl(double x);
extern double math_atan_impl(double x);
extern double math_atan2_impl(double y, double x);
extern double math_pow_impl(double base, double exp);
/* math_sqrt_impl / math_cbrt_impl / math_exp_impl / math_log_impl /
 * math_log1p_impl / math_expm1_impl bridges removed (9.2.4): those six
 * are full fdlibm implementations on both ends. */
extern double math_fabs_impl(double x);
extern double math_fmin_impl(double a, double b);
extern double math_fmax_impl(double a, double b);
extern double math_erf_impl(double x);
extern double math_erfc_impl(double x);
extern int32_t math_fenv_mask_to_fe_impl(int32_t mask);
extern int32_t math_fenv_fe_to_mask_impl(int32_t fe);
extern void math_fenv_emit_cap_report_impl(int32_t avail);
double math_signum_c(double x) {
  if ((x > 0.0)) {
    return 1.0;
  }
  if ((x < 0.0)) {
    return -(1.0);
  }
  return 0.0;
}
int32_t math_special_near(double a, double b, double eps) {
  double d = (a - b);
  if ((d < 0.0)) {
    (void)((d = (0.0 - d)));
  }
  if ((d <=eps)) {
    return 1;
  }
  return 0;
}
double math_floor_c(double x) {
  return math_floor_impl(x);
}
double math_ceil_c(double x) {
  return math_ceil_impl(x);
}
double math_trunc_c(double x) {
  return math_trunc_impl(x);
}
double math_round_c(double x) {
  return math_round_impl(x);
}
double math_sin_c(double x) {
  return math_sin_impl(x);
}
double math_cos_c(double x) {
  return math_cos_impl(x);
}
double math_tan_c(double x) {
  return math_tan_impl(x);
}
double math_asin_c(double x) {
  return math_asin_impl(x);
}
double math_acos_c(double x) {
  return math_acos_impl(x);
}
double math_atan_c(double x) {
  return math_atan_impl(x);
}
double math_atan2_c(double y, double x) {
  return math_atan2_impl(y, x);
}
double math_pow_c(double base, double exp) {
  return math_pow_impl(base, exp);
}
/* math_sqrt_c / math_cbrt_c / math_exp_c / math_log_c (9.2.4): full fdlibm
 * ports, isomorphic with src/asm/runtime_math_libm.x (same constants
 * bit-for-bit; decimal literals are Python-verified against the hex comments).
 * Surface style keeps the -E lowering shape (pointer-cast punning); unlike
 * raw -E output the literals here are FULL PRECISION — the -E emitter's %f
 * literal printing is lossy (standing compiler-root card) and must not be
 * pasted verbatim for float-constant code.
 * PLATFORM: SHARED — FP contraction OFF (see seeds/runtime_math_libm.from_x.c
 * twin note): arm64 clang fmadd fusion would shift results by 1 ulp vs the
 * .x authority's discrete mul/add. */
#pragma STDC FP_CONTRACT OFF
double math_sqrt_c(double x) {
  double one = 1.0;
  double tiny = 0.0; /* 1.0e-300: 0x01a56e1fc2f8f359 */
  (void)((*(uint64_t *)(&(tiny)) = 118622047889322841ULL));
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  int32_t ix0 = ((int32_t)(bits >> 32));
  uint32_t ix1w = ((uint32_t)(bits & 4294967295ULL));
  if (((ix0 & 2146435072) == 2146435072)) {
    return ((r * r) + r);
  }
  if ((ix0 <= 0)) {
    if ((((ix0 & 2147483647) == 0) && (ix1w == 0))) {
      return r;
    }
    if ((ix0 < 0)) {
      return ((r - r) / (r - r));
    }
  }
  int32_t m = (ix0 >> 20);
  uint32_t ix0u = ((uint32_t)ix0);
  if ((m == 0)) {
    while ((ix0u == 0)) {
      m = (m - 21);
      ix0u = (ix0u | (ix1w >> 11));
      ix1w = (ix1w << 21);
    }
    int32_t i = 0;
    while (((ix0u & 1048576) == 0)) {
      ix0u = (ix0u << 1);
      i = (i + 1);
    }
    m = (m - (i - 1));
    if ((i != 0)) {
      ix0u = (ix0u | (ix1w >> (32 - i)));
    }
    ix1w = (ix1w << ((uint32_t)i));
  }
  m = (m - 1023);
  ix0u = ((ix0u & 1048575) | 1048576);
  if (((m & 1) == 1)) {
    ix0u = ((ix0u + ix0u) + (ix1w >> 31));
    ix1w = (ix1w + ix1w);
  }
  m = ((m - (m & 1)) / 2);
  ix0u = ((ix0u + ix0u) + (ix1w >> 31));
  ix1w = (ix1w + ix1w);
  uint32_t q = 0;
  uint32_t q1 = 0;
  uint32_t s0 = 0;
  uint32_t s1 = 0;
  uint32_t rb = 2097152; /* 0x00200000 */
  while ((rb != 0)) {
    uint32_t t = (s0 + rb);
    if ((t <= ix0u)) {
      s0 = (t + rb);
      ix0u = (ix0u - t);
      q = (q + rb);
    }
    ix0u = ((ix0u + ix0u) + (ix1w >> 31));
    ix1w = (ix1w + ix1w);
    rb = (rb >> 1);
  }
  rb = 2147483648u; /* 0x80000000 */
  while ((rb != 0)) {
    uint32_t t1 = (s1 + rb);
    uint32_t t2 = s0;
    if (((t2 < ix0u) || ((t2 == ix0u) && (t1 <= ix1w)))) {
      s1 = (t1 + rb);
      if ((((t1 & 2147483648u) == 2147483648u) && ((s1 & 2147483648u) == 0))) {
        s0 = (s0 + 1);
      }
      ix0u = (ix0u - t2);
      if ((ix1w < t1)) {
        ix0u = (ix0u - 1);
      }
      ix1w = (ix1w - t1);
      q1 = (q1 + rb);
    }
    ix0u = ((ix0u + ix0u) + (ix1w >> 31));
    ix1w = (ix1w + ix1w);
    rb = (rb >> 1);
  }
  if (((ix0u | ix1w) != 0)) {
    double z0 = (one - tiny);
    if ((z0 >= one)) {
      double z1 = (one + tiny);
      if ((q1 == 4294967295u)) {
        q1 = 0;
        q = (q + 1);
      } else if ((z1 > one)) {
        if ((q1 == 4294967294u)) {
          q = (q + 1);
        }
        q1 = (q1 + 2);
      } else {
        q1 = (q1 + (q1 & 1));
      }
    }
  }
  uint32_t hi0 = ((q >> 1) + 1071644672u); /* 0x3fe00000 */
  uint32_t lo0 = (q1 >> 1);
  if (((q & 1) == 1)) {
    lo0 = (lo0 | 2147483648u);
  }
  hi0 = (hi0 + (((uint32_t)m) << 20));
  double z = 0.0;
  (void)((*(uint64_t *)(&(z)) = ((((uint64_t)hi0) << 32) | ((uint64_t)lo0))));
  return z;
}
double math_cbrt_c(double x) {
  double c = 0.5428571428571428;       /* 19/35      0x3fe15f15f15f15f1 */
  double d = (0.0 - 0.7053061224489796); /* -864/1225  0xbfe691de2532c834 */
  double e = 1.4142857142857144;       /* 99/70      0x3ff6a0ea0ea0ea0f */
  double f = 1.6071428571428572;       /* 45/28      0x3ff9b6db6db6db6e */
  double g = 0.35714285714285715;      /* 5/14       0x3fd6db6db6db6db7 */
  uint32_t b1 = 715094163;
  uint32_t b2 = 696219795;
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  uint32_t hi = ((uint32_t)(bits >> 32));
  uint32_t lo = ((uint32_t)(bits & 4294967295ULL));
  uint32_t sign = (hi & 2147483648u);
  uint32_t hx = (hi ^ sign);
  if ((hx >= 2146435072u)) {
    return (r + r);
  }
  if (((hx | lo) == 0)) {
    return r;
  }
  (void)((*(pr) = ((((uint64_t)hx) << 32) | ((uint64_t)lo))));
  double t = 0.0;
  uint64_t *pt = ((uint64_t *)(&(t)));
  if ((hx < 1048576u)) {
    (void)((*(pt) = (((uint64_t)1129316352u) << 32)));
    t = (t * r);
    uint64_t tb = *(pt);
    uint32_t thi = ((uint32_t)(tb >> 32));
    (void)((*(pt) = (((((uint64_t)((thi / 3) + b2)) << 32) | (tb & 4294967295ULL)))));
  } else {
    (void)((*(pt) = (((uint64_t)((hx / 3) + b1)) << 32)));
  }
  double rr = ((t * t) / r);
  double s = (c + (rr * t));
  t = (t * (g + (f / ((s + e) + (d / s)))));
  {
    uint64_t tb = *(pt);
    uint32_t thi = ((uint32_t)(tb >> 32));
    (void)((*(pt) = (((uint64_t)(thi + 1)) << 32)));
  }
  double s2 = (t * t);
  double r2 = (r / s2);
  double w = (t + t);
  double r3 = ((r2 - t) / (w + r2));
  t = (t + (t * r3));
  {
    uint64_t tb = *(pt);
    uint32_t thi = ((uint32_t)(tb >> 32));
    (void)((*(pt) = (((((uint64_t)(thi | sign)) << 32) | (tb & 4294967295ULL)))));
  }
  return t;
}
double math_exp_c(double x) {
  double one = 1.0;
  double half = 0.5;
  double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  double invln2 = 1.44269504088896338700;           /* 0x3ff71547652b82fe */
  double p1 = 0.166666666666666019037;              /* 0x3fc555555555553e */
  double p2 = (0.0 - 0.00277777777770155933842);    /* 0xbf66c16c16bebd93 */
  double p3 = 0.0000661375632143793436117;          /* 0x3f11566aaf25de2c */
  double p4 = (0.0 - 0.00000165339022054652515390); /* 0xbebbbd41c5d26bf1 */
  double p5 = 0.0000000413813679705723846039;       /* 0x3e66376972bea4d0 */
  double o_threshold = 709.782712893383973096;      /* 0x40862e42fefa39ef */
  double u_threshold = (0.0 - 745.133219101941108420); /* 0xc0874910d52d3051 */
  double huge = 0.0;      /* 1.0e300: 0x7e37e43c8800759c */
  double twom1000 = 0.0;  /* 2^-1000: 0x0170000000000000 */
  (void)((*(uint64_t *)(&(huge)) = 9094988921128908188));
  (void)((*(uint64_t *)(&(twom1000)) = 103582791429521408));
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  uint64_t hxabs = ((bits >> 32) & 2147483647);
  uint64_t lx = (bits & 4294967295);
  int32_t xsb = ((int32_t)((bits >> 63) & 1));
  if ((hxabs >= 1082535490)) {
    if ((hxabs >= 2146435072)) {
      if ((((hxabs & 1048575) | lx) != 0)) {
        return (r + r);
      }
      if ((xsb == 0)) {
        return r;
      }
      return 0.0;
    }
    if ((r > o_threshold)) {
      return (huge * huge);
    }
    if ((r < u_threshold)) {
      return (twom1000 * twom1000);
    }
  }
  int32_t k = 0;
  double hi = 0.0;
  double lo = 0.0;
  if ((hxabs > 1071001154)) {
    if ((hxabs < 1072734898)) {
      if ((xsb == 0)) {
        hi = (r - ln2hi);
        lo = ln2lo;
      } else {
        hi = (r + ln2hi);
        lo = (0.0 - ln2lo);
      }
      k = ((1 - xsb) - xsb);
    } else {
      double hf = half;
      if ((xsb == 1)) {
        hf = (0.0 - half);
      }
      k = ((int32_t)(((invln2 * r) + hf)));
      double t = ((double)(k));
      hi = (r - (t * ln2hi));
      lo = (t * ln2lo);
    }
    r = (hi - lo);
  } else {
    if ((hxabs < 1043333120)) {
      if (((huge + r) > one)) {
        return (one + r);
      }
    }
  }
  double t2 = (r * r);
  double c = (r - (t2 * (p1 + (t2 * (p2 + (t2 * (p3 + (t2 * (p4 + (t2 * p5))))))))));
  if ((k == 0)) {
    return (one - (((r * c) / (c - 2.0)) - r));
  }
  double y = (one - ((lo - ((r * c) / (2.0 - c))) - hi));
  /* Scale by 2^k: exponent-field add, C unsigned wrap via u32 truncate. */
  uint64_t *py = ((uint64_t *)(&(y)));
  uint64_t b0 = *(py);
  int32_t ke;
  if ((k >= -1021)) {
    ke = (k << 20);
  } else {
    ke = ((k + 1000) << 20);
  }
  *(py) = (b0 + ((((uint64_t)(uint32_t)(ke))) << 32));
  if ((k < -1021)) {
    return (y * twom1000);
  }
  return y;
}

/* math_log_c (9.2.4 Wave A 2026-09-08): full fdlibm e_log.c port, isomorphic
 * with src/asm/runtime_math_libm.x math_log_c (same constants bit-for-bit;
 * full-precision literals per the exp note above). */
double math_log_c(double x) {
  double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  double two54 = 18014398509481984.0;               /* 0x4350000000000000 */
  double zero = 0.0;
  double lg1 = 0.6666666666666735130;               /* 0x3fe5555555555593 */
  double lg2 = 0.3999999999940941908;               /* 0x3fd999999997fa04 */
  double lg3 = 0.2857142874366239149;               /* 0x3fd2492494229359 */
  double lg4 = 0.2222219843214978396;               /* 0x3fcc71c51d8e78af */
  double lg5 = 0.1818357216161805012;               /* 0x3fc7466496cb03de */
  double lg6 = 0.1531383769920937332;               /* 0x3fc39a09d078c69f */
  double lg7 = 0.1479819860511658591;               /* 0x3fc2f112df3e5244 */
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  int32_t hx = ((int32_t)(bits >> 32));
  uint64_t lx = (bits & 4294967295);
  int32_t k = 0;
  if ((hx < 1048576)) {
    if ((((hx & 2147483647) == 0) && (lx == 0))) {
      return ((-two54) / zero);
    }
    if ((hx < 0)) {
      return ((r - r) / zero);
    }
    k -= 54;
    r = (r * two54);
    bits = *(pr);
    hx = ((int32_t)(bits >> 32));
  }
  if ((hx >= 2146435072)) {
    return (r + r);
  }
  k += ((hx >> 20) - 1023);
  uint64_t hxu = ((uint64_t)(hx & 1048575));
  uint64_t ii = ((hxu + 614244) & 1048576);  /* 0x95f64 / 0x100000 */
  uint64_t b1 = *(pr);
  uint64_t newhi = (hxu | (ii ^ 1072693248)); /* i ^ 0x3ff00000 */
  *(pr) = ((newhi << 32) | (b1 & 4294967295));
  k += ((int32_t)(ii >> 20));
  double f = (r - 1.0);
  if (((((2 + hxu) & 1048575)) < 3)) {
    if ((f == zero)) {
      if ((k == 0)) {
        return zero;
      }
      double dk0 = ((double)(k));
      return ((dk0 * ln2hi) + (dk0 * ln2lo));
    }
    double rr0 = ((f * f) * (0.5 - (0.33333333333333333 * f)));
    if ((k == 0)) {
      return (f - rr0);
    }
    double dk1 = ((double)(k));
    return ((dk1 * ln2hi) - ((rr0 - (dk1 * ln2lo)) - f));
  }
  double s = (f / (2.0 + f));
  double dk = ((double)(k));
  double z = (s * s);
  uint64_t jj = (440401 - hxu);  /* 0x6b851 - hx (u64 wrap, kept) */
  double w = (z * z);
  uint64_t iiw = (hxu - 398458); /* hx - 0x6147a (u64 wrap, kept) */
  double t1 = (w * (lg2 + (w * (lg4 + (w * lg6)))));
  double t2 = (z * (lg1 + (w * (lg3 + (w * (lg5 + (w * lg7)))))));
  uint64_t ior = (iiw | jj);
  double rr = (t2 + t1);
  if ((ior > 0)) {
    double hfsq = ((0.5 * f) * f);
    if ((k == 0)) {
      return (f - (hfsq - (s * (hfsq + rr))));
    }
    return ((dk * ln2hi) - ((hfsq - ((s * (hfsq + rr)) + (dk * ln2lo))) - f));
  }
  if ((k == 0)) {
    return (f - (s * (f - rr)));
  }
  return ((dk * ln2hi) - (((s * (f - rr)) - (dk * ln2lo)) - f));
}
double math_fabs_c(double x) {
  return math_fabs_impl(x);
}
double math_fmin_c(double a, double b) {
  return math_fmin_impl(a, b);
}
double math_fmax_c(double a, double b) {
  return math_fmax_impl(a, b);
}
double math_erf_c(double x) {
  return math_erf_impl(x);
}
double math_erfc_c(double x) {
  return math_erfc_impl(x);
}
/* math_log1p_c / math_expm1_c (9.2.4, 2026-09-08): full fdlibm s_log1p.c /
 * s_expm1.c ports, isomorphic with src/asm/runtime_math_libm.x (same
 * constants bit-for-bit; full-precision literals — never paste lossy -E
 * %f). PLATFORM: SHARED — FP contraction already OFF above. */
double math_log1p_c(double x) {
  double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  double two54 = 18014398509481984.0;               /* 0x4350000000000000 */
  double zero = 0.0;
  double lp1 = 0.6666666666666735130;               /* 0x3fe5555555555593 */
  double lp2 = 0.3999999999940941908;               /* 0x3fd999999997fa04 */
  double lp3 = 0.2857142874366239149;               /* 0x3fd2492494229359 */
  double lp4 = 0.2222219843214978396;               /* 0x3fcc71c51d8e78af */
  double lp5 = 0.1818357216161805012;               /* 0x3fc7466496cb03de */
  double lp6 = 0.1531383769920937332;               /* 0x3fc39a09d078c69f */
  double lp7 = 0.1479819860511658591;               /* 0x3fc2f112df3e5244 */
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  int32_t hx = ((int32_t)(bits >> 32));
  int32_t ax = (hx & 2147483647);
  int32_t k = 1;
  double f = 0.0;
  double c = 0.0;
  int32_t hu = 0;
  double u = 0.0;
  if ((hx < 1071284858)) {
    if ((ax >= 1072693248)) {
      if ((r == (0.0 - 1.0))) {
        return ((0.0 - two54) / zero);
      }
      return ((r - r) / (r - r));
    }
    if ((ax < 1042284544)) {
      if (((two54 + r) > zero)) {
        if ((ax < 1016070144)) {
          return r;
        }
      }
      return (r - ((r * r) * 0.5));
    }
    if (((hx > 0) || (hx <= -1076707645))) {
      k = 0;
      f = r;
      hu = 1;
    }
  }
  if ((hx >= 2146435072)) {
    return (r + r);
  }
  if ((k != 0)) {
    if ((hx < 1128267776)) {
      u = (1.0 + r);
      uint64_t *pu = ((uint64_t *)(&(u)));
      bits = *(pu);
      hu = ((int32_t)(bits >> 32));
      k = ((hu >> 20) - 1023);
      if ((k > 0)) {
        c = (1.0 - (u - r));
      } else {
        c = (r - (u - 1.0));
      }
      c = (c / u);
    } else {
      u = r;
      uint64_t *pu2 = ((uint64_t *)(&(u)));
      bits = *(pu2);
      hu = ((int32_t)(bits >> 32));
      k = ((hu >> 20) - 1023);
      c = 0.0;
    }
    hu = (hu & 1048575);
    uint64_t *pu3 = ((uint64_t *)(&(u)));
    if ((hu < 434334)) {
      uint64_t b = *(pu3);
      uint64_t nhi = (((uint64_t)(hu)) | 1072693248);
      (void)((*(pu3) = ((nhi << 32) | (b & 4294967295ULL))));
    } else {
      k = (k + 1);
      uint64_t b = *(pu3);
      uint64_t nhi = (((uint64_t)(hu)) | 1071644672);
      (void)((*(pu3) = ((nhi << 32) | (b & 4294967295ULL))));
      hu = ((1048576 - hu) >> 2);
    }
    f = (u - 1.0);
  }
  double hfsq = ((0.5 * f) * f);
  if ((hu == 0)) {
    if ((f == zero)) {
      if ((k == 0)) {
        return zero;
      }
      double dk0 = ((double)(k));
      c = (c + (dk0 * ln2lo));
      return ((dk0 * ln2hi) + c);
    }
    double rr0 = (hfsq * (1.0 - (0.66666666666666666 * f)));
    if ((k == 0)) {
      return (f - rr0);
    }
    double dk1 = ((double)(k));
    return ((dk1 * ln2hi) - ((rr0 - ((dk1 * ln2lo) + c)) - f));
  }
  double s = (f / (2.0 + f));
  double z = (s * s);
  double rr = (z * (lp1 + (z * (lp2 + (z * (lp3 + (z * (lp4 + (z * (lp5 + (z * (lp6 + (z * lp7)))))))))))));
  if ((k == 0)) {
    return (f - (hfsq - (s * (hfsq + rr))));
  }
  double dk = ((double)(k));
  return ((dk * ln2hi) - ((hfsq - ((s * (hfsq + rr)) + ((dk * ln2lo) + c))) - f));
}
double math_expm1_c(double x) {
  double one = 1.0;
  double half = 0.5;
  double ln2hi = 0.693147180369123816490;           /* 0x3fe62e42fee00000 */
  double ln2lo = 0.000000000190821492927058770002;  /* 0x3dea39ef35793c76 */
  double invln2 = 1.44269504088896338700;           /* 0x3ff71547652b82fe */
  double o_threshold = 709.782712893383973096;      /* 0x40862e42fefa39ef */
  double q1 = (0.0 - 0.03333333333333313);          /* 0xbfa11111111110f4 */
  double q2 = 0.0015873015872548146;                /* 0x3f5a01a019fe5585 */
  double q3 = (0.0 - 0.0000793650757867488);        /* 0xbf14ce199eaadbb7 */
  double q4 = 0.000004008217827329362;              /* 0x3ed0cfca86e65239 */
  double q5 = (0.0 - 0.00000020109921818362437);    /* 0xbe8afdb76e09c32d */
  double huge = 0.0;
  double tiny = 0.0;
  (void)((*(uint64_t *)(&(huge)) = 9094988921128908188ULL));
  (void)((*(uint64_t *)(&(tiny)) = 118622047889322841ULL));
  double r = x;
  uint64_t *pr = ((uint64_t *)(&(r)));
  uint64_t bits = *(pr);
  uint64_t hxabs = ((bits >> 32) & 2147483647);
  uint64_t lx = (bits & 4294967295);
  int32_t xsb = ((int32_t)((bits >> 63) & 1));
  if ((hxabs >= 1078159482)) {
    if ((hxabs >= 1082535490)) {
      if ((hxabs >= 2146435072)) {
        if ((((hxabs & 1048575) | lx) != 0)) {
          return (r + r);
        }
        if ((xsb == 0)) {
          return r;
        }
        return (0.0 - 1.0);
      }
      if ((r > o_threshold)) {
        return (huge * huge);
      }
    }
    if ((xsb != 0)) {
      if (((r + tiny) < 0.0)) {
        return (tiny - one);
      }
    }
  }
  int32_t k = 0;
  double hi = 0.0;
  double lo = 0.0;
  double corr = 0.0;
  if ((hxabs > 1071001154)) {
    if ((hxabs < 1072734898)) {
      if ((xsb == 0)) {
        hi = (r - ln2hi);
        lo = ln2lo;
        k = 1;
      } else {
        hi = (r + ln2hi);
        lo = (0.0 - ln2lo);
        k = (0 - 1);
      }
    } else {
      double hf = half;
      if ((xsb == 1)) {
        hf = (0.0 - half);
      }
      k = ((int32_t)(((invln2 * r) + hf)));
      double t0 = ((double)(k));
      hi = (r - (t0 * ln2hi));
      lo = (t0 * ln2lo);
    }
    r = (hi - lo);
    corr = ((hi - r) - lo);
  } else {
    if ((hxabs < 1016070144)) {
      double t1 = (huge + r);
      return (r - (t1 - (huge + r)));
    }
  }
  double hfx = (half * r);
  double hxs = (r * hfx);
  double r1 = (one + (hxs * (q1 + (hxs * (q2 + (hxs * (q3 + (hxs * (q4 + (hxs * q5))))))))));
  double t = (3.0 - (r1 * hfx));
  double e = (hxs * ((r1 - t) / (6.0 - (r * t))));
  if ((k == 0)) {
    return (r - ((r * e) - hxs));
  }
  e = (((r * (e - corr)) - corr) - hxs);
  if ((k == (0 - 1))) {
    return (((half * (r - e)) - half));
  }
  if ((k == 1)) {
    if ((r < (0.0 - 0.25))) {
      return ((0.0 - 2.0) * (e - (r + half)));
    }
    return (one + (2.0 * (r - e)));
  }
  double y = 0.0;
  if (((k <= -2) || (k > 56))) {
    y = (one - (e - r));
    uint64_t *py = ((uint64_t *)(&(y)));
    uint64_t b = *(py);
    int32_t ke = (k << 20);
    *(py) = (b + ((((uint64_t)(uint32_t)(ke))) << 32));
    return (y - one);
  }
  double tt = one;
  uint64_t *ptt = ((uint64_t *)(&(tt)));
  if ((k < 20)) {
    uint64_t thi = ((uint64_t)(1072693248 - (2097152 >> k)));
    *(ptt) = (thi << 32);
    y = (tt - (e - r));
    uint64_t *py2 = ((uint64_t *)(&(y)));
    uint64_t b2 = *(py2);
    int32_t ke2 = (k << 20);
    *(py2) = (b2 + ((((uint64_t)(uint32_t)(ke2))) << 32));
  } else {
    uint64_t thi2 = ((uint64_t)((1023 - k) << 20));
    *(ptt) = (thi2 << 32);
    y = (r - (e + tt));
    y = (y + one);
    uint64_t *py3 = ((uint64_t *)(&(y)));
    uint64_t b3 = *(py3);
    int32_t ke3 = (k << 20);
    *(py3) = (b3 + ((((uint64_t)(uint32_t)(ke3))) << 32));
  }
  return y;
}
int32_t math_fenv_mask_to_fe(int32_t mask) {
  return math_fenv_mask_to_fe_impl(mask);
}
int32_t math_fenv_fe_to_mask(int32_t fe) {
  return math_fenv_fe_to_mask_impl(fe);
}
void math_fenv_emit_cap_report(int32_t avail) {
  (void)(math_fenv_emit_cap_report_impl(avail));
}
extern int32_t math_fenv_available_impl_c(void);
extern int32_t math_fenv_test_impl_c(int32_t mask);
extern int32_t math_fenv_clear_impl_c(int32_t mask);
extern int32_t math_fenv_raise_impl_c(int32_t mask);
extern int32_t math_fenv_smoke_impl_c(void);
extern int32_t math_fenv_capability_smoke_impl_c(void);
int32_t math_fenv_available_c(void) {
  return math_fenv_available_impl_c();
}
int32_t math_fenv_test_c(int32_t mask) {
  return math_fenv_test_impl_c(mask);
}
int32_t math_fenv_clear_c(int32_t mask) {
  return math_fenv_clear_impl_c(mask);
}
int32_t math_fenv_raise_c(int32_t mask) {
  return math_fenv_raise_impl_c(mask);
}
int32_t math_fenv_smoke_c(void) {
  return math_fenv_smoke_impl_c();
}
int32_t math_fenv_capability_smoke_c(void) {
  return math_fenv_capability_smoke_impl_c();
}
