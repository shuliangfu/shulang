// wave924 (9.2.4) · rc-gated bit-exact probe: exact-7
// math_floor_c / math_ceil_c / math_trunc_c / math_round_c /
// math_fabs_c / math_fmin_c / math_fmax_c
// Product path is the .x bit-level authority (no host libm). Host-libm
// math_*_impl splices removed this knife; rem_pio2 reuses math_floor_c
// / math_fabs_c (G.7). Inputs 2.5 / 0.5 / -2.5 / -0.5 are dyadic so the
// X decimal lexer is bit-exact (no pun needed). round ties-away-from-zero
// (C round). fmin/fmax equal operands (incl. +-0 pairs) return the SECOND
// operand (glibc x86_64 / Ubuntu gold). NaN cases assert NaN-ness.
// rc packed to 32-bit exit: 0 = all 30 cases pass.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_floor_c(x: f64): f64;
export extern "C" function math_ceil_c(x: f64): f64;
export extern "C" function math_trunc_c(x: f64): f64;
export extern "C" function math_round_c(x: f64): f64;
export extern "C" function math_fabs_c(x: f64): f64;
export extern "C" function math_fmin_c(a: f64, b: f64): f64;
export extern "C" function math_fmax_c(a: f64, b: f64): f64;

/**
 * Reads the raw IEEE-754 bit pattern of v as u64 (pointer punning).
 * @param v f64 - any bit pattern
 * @return u64 - bits of v
 */
function bits_of(v: f64): u64 {
  unsafe {
    let p: *u64 = &v as *u64;
    return *p;
  }
}

/**
 * Returns 1 if v is a NaN (exponent field all-ones, mantissa nonzero).
 * @param v f64 - any bit pattern
 * @return i32 - 1 if NaN, 0 otherwise
 */
function isnan_bits(v: f64): i32 {
  let b: u64 = bits_of(v);
  if (((b >> 52) & 2047) == 2047) {
    if ((b & 4503599627370495) != 0) { return 1; }
  }
  return 0;
}

function main(): i32 {
  unsafe {
    let rc: i32 = 0;
    let inf: f64 = 1e308 * 10.0;
    let nz: f64 = 0.0;
    let nan: f64 = nz / nz;
    let nzero: f64 = 0.0 * (0.0 - 1.0);  /* IEEE -0.0 */
    let x25: f64 = 2.5;
    let nx25: f64 = 0.0 - 2.5;
    let x05: f64 = 0.5;
    let nx05: f64 = 0.0 - 0.5;

    /* ---- floor bits 0..7 ---- */
    if (bits_of(math_floor_c(x25)) != 4611686018427387904) { rc = rc | 1; }          // 2
    if (bits_of(math_floor_c(nx25)) != 13837309855095848960) { rc = rc | 2; }         // -3
    if (bits_of(math_floor_c(x05)) != 0) { rc = rc | 4; }                              // +0
    if (bits_of(math_floor_c(nx05)) != 13830554455654793216) { rc = rc | 8; }          // -1
    if (bits_of(math_floor_c(0.0)) != 0) { rc = rc | 16; }
    if (bits_of(math_floor_c(nzero)) != 9223372036854775808) { rc = rc | 32; }
    if (bits_of(math_floor_c(inf)) != 9218868437227405312) { rc = rc | 64; }
    if (isnan_bits(math_floor_c(nan)) == 0) { rc = rc | 128; }

    /* ---- ceil bits 8..11 ---- */
    if (bits_of(math_ceil_c(x25)) != 4613937818241073152) { rc = rc | 256; }           // 3
    if (bits_of(math_ceil_c(nx25)) != 13835058055282163712) { rc = rc | 512; }         // -2
    if (bits_of(math_ceil_c(nx05)) != 9223372036854775808) { rc = rc | 1024; }          // -0
    if (bits_of(math_ceil_c(x05)) != 4607182418800017408) { rc = rc | 2048; }           // 1

    /* ---- trunc bits 12..14 ---- */
    if (bits_of(math_trunc_c(x25)) != 4611686018427387904) { rc = rc | 4096; }          // 2
    if (bits_of(math_trunc_c(nx25)) != 13835058055282163712) { rc = rc | 8192; }        // -2
    if (bits_of(math_trunc_c(nx05)) != 9223372036854775808) { rc = rc | 16384; }         // -0

    /* ---- round (ties away from 0) bits 15..18 ---- */
    if (bits_of(math_round_c(x25)) != 4613937818241073152) { rc = rc | 32768; }         // 3
    if (bits_of(math_round_c(nx25)) != 13837309855095848960) { rc = rc | 65536; }       // -3
    if (bits_of(math_round_c(x05)) != 4607182418800017408) { rc = rc | 131072; }        // 1
    if (bits_of(math_round_c(nx05)) != 13830554455654793216) { rc = rc | 262144; }      // -1

    /* ---- fabs bits 19..20 ---- */
    if (bits_of(math_fabs_c(nx25)) != 4612811918334230528) { rc = rc | 524288; }        // 2.5
    if (bits_of(math_fabs_c(nzero)) != 0) { rc = rc | 1048576; }                        // +0

    /* ---- fmin/fmax bits 21..26 ---- */
    if (bits_of(math_fmin_c(1.0, 2.0)) != 4607182418800017408) { rc = rc | 2097152; }
    if (bits_of(math_fmax_c(1.0, 2.0)) != 4611686018427387904) { rc = rc | 4194304; }
    if (bits_of(math_fmin_c(0.0, nzero)) != 9223372036854775808) { rc = rc | 8388608; } // second = -0
    if (bits_of(math_fmax_c(nzero, 0.0)) != 0) { rc = rc | 16777216; }                  // second = +0
    if (bits_of(math_fmin_c(nan, 1.0)) != 4607182418800017408) { rc = rc | 33554432; }
    if (bits_of(math_fmax_c(nan, 1.0)) != 4607182418800017408) { rc = rc | 67108864; }

    /* ---- identity bits 27..29 ---- */
    if (bits_of(math_ceil_c(0.0)) != 0) { rc = rc | 134217728; }
    if (bits_of(math_trunc_c(0.0)) != 0) { rc = rc | 268435456; }
    if (bits_of(math_round_c(2.0)) != 4611686018427387904) { rc = rc | 536870912; }

    return rc;
  }
}
