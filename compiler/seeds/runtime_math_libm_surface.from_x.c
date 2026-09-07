/* seeds/runtime_math_libm_surface.from_x.c
 * G-02f runtime_math_libm R2 mixed surface - isomorphic with src/asm/runtime_math_libm.x
 * Product PREFER_X_O: xlang-c -E(.x) -> thin.o + ld -r with rest (seeds/runtime_math_libm.from_x.c)
 * Prove: full.x vs this surface -> nm IDENTICAL (34 #[no_mangle])
 * Mode: mixed - 2 DIRECT compute + 30 thin+rest forwards to _impl
 *   + 2 full implementations (9.2.4 Wave A 2026-09-08: math_exp_c / math_log_c
 *   fdlibm e_exp.c / e_log.c ports, isomorphic with the .x authority; the two
 *   math_exp_impl / math_log_impl bridges are gone from both ends).
 * Cap residual: 30 extern bridges (math_*_impl)
 * No doc_anchor (runtime_math_libm.x has none).
 * Note: math_ prefix not trigger ast_ (confirmed wave545+).
 * Logic: 34 functions = 2 DIRECT (math_signum_c + math_special_near)
 *   + 30 thin+rest forwards to math_*_impl + 2 full impls (exp/log fdlibm).
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
extern double math_sqrt_impl(double x);
extern double math_cbrt_impl(double x);
extern double math_pow_impl(double base, double exp);
/* math_exp_impl / math_log_impl bridges removed (9.2.4 Wave A 2026-09-08):
 * exp/log are full fdlibm implementations on both ends now. */
extern double math_fabs_impl(double x);
extern double math_fmin_impl(double a, double b);
extern double math_fmax_impl(double a, double b);
extern double math_erf_impl(double x);
extern double math_erfc_impl(double x);
extern double math_log1p_impl(double x);
extern double math_expm1_impl(double x);
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
double math_sqrt_c(double x) {
  return math_sqrt_impl(x);
}
double math_cbrt_c(double x) {
  return math_cbrt_impl(x);
}
double math_pow_c(double base, double exp) {
  return math_pow_impl(base, exp);
}
/* math_exp_c (9.2.4 Wave A 2026-09-08): full fdlibm e_exp.c port, isomorphic
 * with src/asm/runtime_math_libm.x math_exp_c (same constants bit-for-bit;
 * decimal literals are Python-verified against the hex comments shown).
 * Surface style keeps the -E lowering shape (pointer-cast punning); unlike
 * raw -E output the literals here are FULL PRECISION — the -E emitter's %f
 * literal printing is lossy (standing compiler-root card) and must not be
 * pasted verbatim for float-constant code.
 * PLATFORM: SHARED — FP contraction OFF (see seeds/runtime_math_libm.from_x.c
 * twin note): arm64 clang fmadd fusion would shift results by 1 ulp vs the
 * .x authority's discrete mul/add. */
#pragma STDC FP_CONTRACT OFF
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
double math_log1p_c(double x) {
  return math_log1p_impl(x);
}
double math_expm1_c(double x) {
  return math_expm1_impl(x);
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
