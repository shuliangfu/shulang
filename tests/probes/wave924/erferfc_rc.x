// wave924 (9.2.4) · rc-gated bit-exact probe: math_erf_c / math_erfc_c
// fdlibm s_erf.c / s_erfc.c .x ports (runtime_math_libm.x). Shared P/Q,
// P1/Q1, R1/S1, R2/S2 rationals + two-exp tail (G.7); reuses math_exp_c
// and math_fabs_c. Pins fdlibm discrete-op semantics (error < 1 ulp).
// Documented diffs vs correctly-rounded host libm (all 1 ulp, pin fdlibm):
//   * erf(1) / erf(-1) / erf(0.25) / erf(1e-10)
//   * erfc(1) / erfc(-1) / erfc(0.7) / erfc(2) / erfc(6)
// Non-integer inputs are bit-punned from Python-verified IEEE u64 (the X
// decimal lexer is 1 ulp off on values such as 0.7 / 0.84375 — standing
// card, not this knife; 0.84375 sits on an interval boundary so a 1-ulp
// miss would take the wrong branch). NaN cases assert NaN-ness because
// payload through 1/x is platform-defined. Asymptotic |x|>=1.25 uses
// math_exp_c (fdlibm exp); erfc(2)/erfc(10) pins are the product path
// (1 ulp off the host-exp standalone twin).
// rc packed to 8-bit exit: 0 = all 30 cases pass, 1 = any fail.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_erf_c(x: f64): f64;
export extern "C" function math_erfc_c(x: f64): f64;

/// Reads the raw IEEE-754 bit pattern of v as u64 (pointer punning).
function bits_of(v: f64): u64 {
  unsafe {
    let p: *u64 = &v as *u64;
    return *p;
  }
}

/// Builds an f64 from a Python-verified IEEE bit pattern.
function f64_from_bits(b: u64): f64 {
  let v: f64 = 0.0;
  unsafe {
    let p: *u64 = &v as *u64;
    *p = b;
  }
  return v;
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
    let x07: f64 = f64_from_bits(4604480259023595110);     /* 0.7     0x3fe6666666666666 */
    let x1em10: f64 = f64_from_bits(4457293557087583675);  /* 1e-10   0x3ddb7cdfd9d7bdbb */
    let x025: f64 = f64_from_bits(4598175219545276416);    /* 0.25    0x3fd0000000000000 */
    let x05: f64 = f64_from_bits(4602678819172646912);     /* 0.5     0x3fe0000000000000 */
    let x084375: f64 = f64_from_bits(4605775043916464128); /* 0.84375 0x3feb000000000000 */
    let x125: f64 = f64_from_bits(4608308318706860032);    /* 1.25    0x3ff4000000000000 */

    /* ---- erf bits 0..14 ---- */
    if (bits_of(math_erf_c(0.0)) != 0) { rc = rc | 1; }                                    // +0
    if (bits_of(math_erf_c(nzero)) != 9223372036854775808) { rc = rc | 2; }                 // -0
    if (bits_of(math_erf_c(inf)) != 4607182418800017408) { rc = rc | 4; }                   // +inf -> +1
    if (bits_of(math_erf_c(0.0 - inf)) != 13830554455654793216) { rc = rc | 8; }            // -inf -> -1
    if (isnan_bits(math_erf_c(nan)) == 0) { rc = rc | 16; }                                 // NaN
    if (bits_of(math_erf_c(1.0)) != 4605765593499502731) { rc = rc | 32; }                  // fdlibm 1ulp
    if (bits_of(math_erf_c(0.0 - 1.0)) != 13829137630354278539) { rc = rc | 64; }           // -erf(1)
    if (bits_of(math_erf_c(x05)) != 4602863465656806866) { rc = rc | 128; }
    if (bits_of(math_erf_c(x07)) != 4604280309953271366) { rc = rc | 256; }
    if (bits_of(math_erf_c(x025)) != 4598649473629083145) { rc = rc | 512; }                 // fdlibm 1ulp
    if (bits_of(math_erf_c(2.0)) != 4607140285508982243) { rc = rc | 1024; }
    if (bits_of(math_erf_c(6.0)) != 4607182418800017408) { rc = rc | 2048; }                 // 1-tiny == 1
    if (bits_of(math_erf_c(x1em10)) != 4458286842782318945) { rc = rc | 4096; }              // fdlibm 1ulp
    if (bits_of(math_erf_c(x084375)) != 4605085773949346528) { rc = rc | 8192; }
    if (bits_of(math_erf_c(x125)) != 4606487964892708352) { rc = rc | 16384; }

    /* ---- erfc bits 15..29 ---- */
    if (bits_of(math_erfc_c(0.0)) != 4607182418800017408) { rc = rc | 32768; }               // 1
    if (bits_of(math_erfc_c(inf)) != 0) { rc = rc | 65536; }                                 // +inf -> 0
    if (bits_of(math_erfc_c(0.0 - inf)) != 4611686018427387904) { rc = rc | 131072; }        // -inf -> 2
    if (isnan_bits(math_erfc_c(nan)) == 0) { rc = rc | 262144; }
    if (bits_of(math_erfc_c(1.0)) != 4594835321492594133) { rc = rc | 524288; }              // fdlibm 1ulp
    if (bits_of(math_erfc_c(0.0 - 1.0)) != 4610977605777130566) { rc = rc | 1048576; }       // fdlibm 1ulp
    if (bits_of(math_erfc_c(x05)) != 4602309526204327004) { rc = rc | 2097152; }
    if (bits_of(math_erfc_c(x07)) != 4599475837611398004) { rc = rc | 4194304; }             // fdlibm 1ulp
    if (bits_of(math_erfc_c(2.0)) != 4572043083406184039) { rc = rc | 8388608; }             // fdlibm exp 1ulp vs host-exp twin
    if (bits_of(math_erfc_c(0.0 - 2.0)) != 4611664951781870322) { rc = rc | 16777216; }
    if (bits_of(math_erfc_c(6.0)) != 4357460793872949431) { rc = rc | 33554432; }            // fdlibm 1ulp
    if (bits_of(math_erfc_c(0.0 - 6.0)) != 4611686018427387904) { rc = rc | 67108864; }      // 2-tiny == 2
    if (bits_of(math_erfc_c(10.0)) != 3938354615001064144) { rc = rc | 134217728; }          // fdlibm exp 1ulp vs host-exp twin
    if (bits_of(math_erfc_c(28.0)) != 0) { rc = rc | 268435456; }
    if (bits_of(math_erfc_c(x025)) != 4604693491944428796) { rc = rc | 536870912; }

    if (rc != 0) { return 1; }
    return 0;
  }
}
