// wave924 (9.2.4) · rc-gated bit-exact probe: math_pow_c
// fdlibm e_pow.c .x port (runtime_math_libm.x).
// Pins fdlibm discrete-op semantics (error < 1 ulp). Documented diffs vs
// correctly-rounded host libm:
//   * 0.7 ** 1.3 sits 1 ulp off host (pin fdlibm 0x3fe4207e29c0d5e4)
//   * +-1 ** +-inf is NaN in fdlibm; IEEE 754-2008 / host libm return 1
// NaN cases assert NaN-ness because payload through x+y / (x-x)/(x-x) is
// platform-defined.
// rc: failures in bits 0..24.
// Decimal expectation literals are Python-converted from the hex shown.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_pow_c(base: f64, exp: f64): f64;

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
    let pi: f64 = 3.141592653589793;

    if (bits_of(math_pow_c(2.0, 10.0)) != 4652218415073722368) { rc = rc | 1; }              // 0x4090000000000000 = 1024
    if (bits_of(math_pow_c(2.0, 0.5)) != 4609047870845172685) { rc = rc | 2; }               // 0x3ff6a09e667f3bcd
    if (bits_of(math_pow_c(10.0, 3.0)) != 4652007308841189376) { rc = rc | 4; }              // 0x408f400000000000 = 1000
    if (bits_of(math_pow_c(4.0, 0.5)) != 4611686018427387904) { rc = rc | 8; }               // 0x4000000000000000 = 2
    if (bits_of(math_pow_c(3.0, 4.0)) != 4635400285215260672) { rc = rc | 16; }              // 0x4054400000000000 = 81
    if (bits_of(math_pow_c(2.0, 0.0 - 1.0)) != 4602678819172646912) { rc = rc | 32; }        // 0x3fe0000000000000 = 0.5
    if (bits_of(math_pow_c(0.5, 2.0)) != 4598175219545276416) { rc = rc | 64; }              // 0x3fd0000000000000 = 0.25
    if (bits_of(math_pow_c(0.0 - 2.0, 3.0)) != 13844065254536904704) { rc = rc | 128; }      // 0xc020000000000000 = -8
    if (bits_of(math_pow_c(0.0 - 2.0, 4.0)) != 4625196817309499392) { rc = rc | 256; }       // 0x4030000000000000 = 16
    if (bits_of(math_pow_c(7.0, 0.0)) != 4607182418800017408) { rc = rc | 512; }             // 0x3ff0000000000000 = 1
    if (bits_of(math_pow_c(0.0, 5.0)) != 0) { rc = rc | 1024; }                              // +0
    if (bits_of(math_pow_c(0.0, 0.0 - 5.0)) != 9218868437227405312) { rc = rc | 2048; }      // +inf
    if (bits_of(math_pow_c(0.7, 1.3)) != 4603840445317961188) { rc = rc | 4096; }            // 0x3fe4207e29c0d5e4 fdlibm 1ulp
    if (bits_of(math_pow_c(pi, 2.718281828459045)) != 4627014908577845520) { rc = rc | 8192; } // 0x4036758b5c381110
    if (bits_of(math_pow_c(0.0 - 1.0, 3.0)) != 13830554455654793216) { rc = rc | 16384; }    // 0xbff0000000000000 = -1
    if (bits_of(math_pow_c(10.0, 0.5)) != 4614303235046005587) { rc = rc | 32768; }          // 0x40094c583ada5b53
    if (bits_of(math_pow_c(1.5, 2.5)) != 4613387649414743380) { rc = rc | 65536; }           // 0x40060b9fd68a4554
    if (bits_of(math_pow_c(nzero, 3.0)) != 9223372036854775808) { rc = rc | 131072; }        // -0
    if (bits_of(math_pow_c(2.0, 1023.0)) != 9214364837600034816) { rc = rc | 262144; }       // 0x7fe0000000000000
    if (bits_of(math_pow_c(10.0, 1.0)) != 4621819117588971520) { rc = rc | 524288; }         // 0x4024000000000000 = 10
    if (bits_of(math_pow_c(inf, 2.0)) != 9218868437227405312) { rc = rc | 1048576; }         // +inf
    if (isnan_bits(math_pow_c(0.0 - 2.0, 0.5)) != 1) { rc = rc | 2097152; }                 // (-2)**0.5 = NaN
    if (isnan_bits(math_pow_c(1.0, inf)) != 1) { rc = rc | 4194304; }                       // 1**inf = NaN (fdlibm)
    if (isnan_bits(math_pow_c(nan, 2.0)) != 1) { rc = rc | 8388608; }                       // NaN**2 = NaN
    if (bits_of(math_pow_c(2.5, 3.5)) != 4627647139797351727) { rc = rc | 16777216; }       // 0x4038b48e29793d2f

    return rc;
  }
}
