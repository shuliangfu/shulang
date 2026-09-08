// wave924 (9.2.4) · rc-gated bit-exact probe: math_sin_c / math_cos_c / math_tan_c
// fdlibm s_sin.c / s_cos.c / s_tan.c .x ports (runtime_math_libm.x) plus
// k_sin/k_cos/k_tan and e_rem_pio2 / k_rem_pio2.
// Pins fdlibm discrete-op semantics (error < 1 ulp). A few cases sit 1 ulp
// off correctly-rounded host libm and are pinned here so both platforms
// assert fdlibm, not host: cos(0.1), tan(1.0), tan(0.1), tan(10.0).
// NaN cases assert NaN-ness because payload through x-x is platform-defined.
// rc: sin failures in bits 0..9, cos in bits 10..19, tan in bits 20..29.
// Decimal expectation literals are Python-converted from the hex shown.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_sin_c(x: f64): f64;
export extern "C" function math_cos_c(x: f64): f64;
export extern "C" function math_tan_c(x: f64): f64;

/// Reads the raw IEEE-754 bit pattern of v as u64 (pointer punning).
function bits_of(v: f64): u64 {
  unsafe {
    let p: *u64 = &v as *u64;
    return *p;
  }
}

/// Returns 1 if v is a NaN (exponent field all-ones, mantissa nonzero).
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
    let tiny10: f64 = 1e-10;
    let pi: f64 = 3.141592653589793;

    // === sin (10 cases; bit k) ===
    if (bits_of(math_sin_c(0.0)) != 0) { rc = rc | 1; }                                    // 0x0000000000000000
    if (bits_of(math_sin_c(nzero)) != 9223372036854775808) { rc = rc | 2; }                 // 0x8000000000000000
    if (bits_of(math_sin_c(1.0)) != 4605754516372524270) { rc = rc | 4; }                   // 0x3feaed548f090cee
    if (bits_of(math_sin_c(0.0 - 1.0)) != 13829126553227300078) { rc = rc | 8; }            // 0xbfeaed548f090cee
    if (bits_of(math_sin_c(0.5)) != 4602308182625945072) { rc = rc | 16; }                  // 0x3feeaee8744b05f0
    if (bits_of(math_sin_c(pi)) != 4368955796522032135) { rc = rc | 32; }                   // sin(pi) ~ 0
    if (bits_of(math_sin_c(10.0)) != 13826447362944618322) { rc = rc | 64; }
    if (isnan_bits(math_sin_c(inf)) != 1) { rc = rc | 128; }
    if (bits_of(math_sin_c(tiny10)) != 4457293557087583675) { rc = rc | 256; }
    if (bits_of(math_sin_c(1.5707963267948966)) != 4607182418800017408) { rc = rc | 512; }  // sin(pi/2)=1

    // === cos (10 cases; bit 10+k) ===
    if (bits_of(math_cos_c(0.0)) != 4607182418800017408) { rc = rc | 1024; }                // 1.0
    if (bits_of(math_cos_c(1.0)) != 4603041830072026764) { rc = rc | 2048; }
    if (bits_of(math_cos_c(0.5)) != 4606079780542709072) { rc = rc | 4096; }
    if (bits_of(math_cos_c(pi)) != 13830554455654793216) { rc = rc | 8192; }                // -1.0
    if (bits_of(math_cos_c(10.0)) != 13829104940851424031) { rc = rc | 16384; }
    if (bits_of(math_cos_c(0.1)) != 4607137420321232832) { rc = rc | 32768; }               // fdlibm 1ulp vs host
    if (isnan_bits(math_cos_c(inf)) != 1) { rc = rc | 65536; }
    if (bits_of(math_cos_c(0.7853981633974483)) != 4604544271217802189) { rc = rc | 131072; }
    if (bits_of(math_cos_c(100.0)) != 4605942297449095135) { rc = rc | 262144; }
    if (bits_of(math_cos_c(nzero)) != 4607182418800017408) { rc = rc | 524288; }

    // === tan (10 cases; bit 20+k) ===
    if (bits_of(math_tan_c(0.0)) != 0) { rc = rc | 1048576; }
    if (bits_of(math_tan_c(nzero)) != 9223372036854775808) { rc = rc | 2097152; }
    if (bits_of(math_tan_c(1.0)) != 4609692760021066662) { rc = rc | 4194304; }              // fdlibm 1ulp vs host
    if (bits_of(math_tan_c(0.5)) != 4603095874924660554) { rc = rc | 8388608; }
    if (bits_of(math_tan_c(pi)) != 13592327833376807943) { rc = rc | 16777216; }
    if (bits_of(math_tan_c(10.0)) != 4604015134707169154) { rc = rc | 33554432; }            // fdlibm 1ulp vs host
    if (isnan_bits(math_tan_c(inf)) != 1) { rc = rc | 67108864; }
    if (bits_of(math_tan_c(0.7853981633974483)) != 4607182418800017407) { rc = rc | 134217728; }
    if (bits_of(math_tan_c(0.1)) != 4591894295732226944) { rc = rc | 268435456; }            // fdlibm 1ulp vs host
    if (bits_of(math_tan_c(0.0 - 1.0)) != 13833064796875842470) { rc = rc | 536870912; }

    return rc;
  }
}
