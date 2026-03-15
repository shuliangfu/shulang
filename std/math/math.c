/**
 * std/math/math.c — 数学常量与函数（对标 Zig std.math、Rust std::f64）
 *
 * 【文件职责】
 * 常量 PI、E、Tau；舍入 floor/ceil/trunc/round；三角函数 sin/cos/tan、asin/acos/atan、atan2；
 * sqrt、cbrt、pow、exp、log、fabs、signum。f64 双精度，对接 libm。
 *
 * 【所属模块/组件】
 * 标准库 std.math；与 std/math/mod.su 同属一模块。链接需 -lm。
 */

#include <stdint.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.7182818284590452354
#endif

double math_pi_c(void) { return M_PI; }
double math_e_c(void) { return M_E; }
double math_tau_c(void) { return M_PI * 2.0; }

double math_floor_c(double x) { return floor(x); }
double math_ceil_c(double x) { return ceil(x); }
double math_trunc_c(double x) { return trunc(x); }
double math_round_c(double x) { return round(x); }

double math_sin_c(double x) { return sin(x); }
double math_cos_c(double x) { return cos(x); }
double math_tan_c(double x) { return tan(x); }
double math_asin_c(double x) { return asin(x); }
double math_acos_c(double x) { return acos(x); }
double math_atan_c(double x) { return atan(x); }
double math_atan2_c(double y, double x) { return atan2(y, x); }

double math_sqrt_c(double x) { return sqrt(x); }
double math_cbrt_c(double x) { return cbrt(x); }
double math_pow_c(double base, double exp) { return pow(base, exp); }
double math_exp_c(double x) { return exp(x); }
double math_log_c(double x) { return log(x); }
double math_fabs_c(double x) { return fabs(x); }

/** signum：x>0 返回 1，x<0 返回 -1，x==0 返回 0。 */
double math_signum_c(double x) {
  if (x > 0.0) return 1.0;
  if (x < 0.0) return -1.0;
  return 0.0;
}

double math_fmin_c(double a, double b) { return fmin(a, b); }
double math_fmax_c(double a, double b) { return fmax(a, b); }
