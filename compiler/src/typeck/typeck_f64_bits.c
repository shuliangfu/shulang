/**
 * typeck_f64_bits.c — 供 asm 链接用：仅提供 typeck_float64_bits_lo/hi（f64 位模式低/高 32 位）
 *
 * 用于「crt0 + build_asm/*.o」无 runtime_driver 链接时，typeck.su 需此二符号。
 * 完全无 C 时可将此逻辑迁至 asm 或 .su。
 */

/** double 的 64 位位模式低 32 位，供 .su typeck 填写 EXPR_FLOAT_LIT（asm 后端用）。 */
int typeck_float64_bits_lo(double d) {
    union { double d; unsigned long long u; } u;
    u.d = d;
    return (int)(u.u & 0xFFFFFFFFULL);
}

/** double 的 64 位位模式高 32 位。 */
int typeck_float64_bits_hi(double d) {
    union { double d; unsigned long long u; } u;
    u.d = d;
    return (int)(u.u >> 32);
}
