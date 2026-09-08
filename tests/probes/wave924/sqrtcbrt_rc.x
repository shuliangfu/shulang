// wave924 (9.2.4) · rc-gated bit-exact probe: math_sqrt_c / math_cbrt_c
// fdlibm e_sqrt.c / s_cbrt.c .x ports (runtime_math_libm.x).
// sqrt is correctly rounded by construction: expectations equal host libm
// bits on every finite/zero/inf case below. cbrt pins fdlibm discrete-op
// semantics (error < 1 ulp); cbrt(pi) sits 1 ulp off host libm and is
// pinned here so both platforms assert fdlibm, not host cbrt.
// NaN cases (sqrt(-inf), sqrt(NaN), sqrt(-1), cbrt(NaN)) assert NaN-ness
// because payload propagation through fp add/div is platform-defined.
// rc: sqrt failures in bits 0..14, cbrt failures in bits 16..30.
// Decimal expectation literals are Python-converted from the hex shown.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_sqrt_c(x: f64): f64;
export extern "C" function math_cbrt_c(x: f64): f64;

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
    let sub320: f64 = 1e-320;

    // === sqrt (15 cases; bit k) ===
    if (bits_of(math_sqrt_c(0.0)) != 0) { rc = rc | 1; }                                   // 0x0000000000000000
    if (bits_of(math_sqrt_c(nzero)) != 9223372036854775808) { rc = rc | 2; }                // 0x8000000000000000
    if (bits_of(math_sqrt_c(1.0)) != 4607182418800017408) { rc = rc | 4; }                  // 0x3ff0000000000000
    if (bits_of(math_sqrt_c(4.0)) != 4611686018427387904) { rc = rc | 8; }                  // 0x4000000000000000
    if (bits_of(math_sqrt_c(9.0)) != 4613937818241073152) { rc = rc | 16; }                 // 0x4008000000000000
    if (bits_of(math_sqrt_c(2.0)) != 4609047870845172685) { rc = rc | 32; }                 // 0x3ff6a09e667f3bcd
    if (bits_of(math_sqrt_c(0.5)) != 4604544271217802189) { rc = rc | 64; }                 // 0x3fe6a09e667f3bcd
    if (bits_of(math_sqrt_c(0.1)) != 4599368272914696463) { rc = rc | 128; }                // 0x3fd43d136248490f
    if (bits_of(math_sqrt_c(10.0)) != 4614303235046005587) { rc = rc | 256; }               // 0x40094c583ada5b53
    if (bits_of(math_sqrt_c(tiny10)) != 4532020583610935537) { rc = rc | 512; }             // 0x3ee4f8b588e368f1
    if (bits_of(math_sqrt_c(sub320)) != 2213095440444558963) { rc = rc | 1024; }            // 0x1eb67e93ddbc0e73
    if (bits_of(math_sqrt_c(1e300)) != 6850974717710472879) { rc = rc | 2048; }             // 0x5f138d352e5096af
    if (bits_of(math_sqrt_c(inf)) != 9218868437227405312) { rc = rc | 4096; }               // 0x7ff0000000000000
    if (isnan_bits(math_sqrt_c(nan)) != 1) { rc = rc | 8192; }                              // sqrt(NaN)=NaN
    if (isnan_bits(math_sqrt_c(0.0 - 1.0)) != 1) { rc = rc | 16384; }                       // sqrt(-1)=NaN

    // === cbrt (15 cases; bit 16+k) ===
    if (bits_of(math_cbrt_c(0.0)) != 0) { rc = rc | 65536; }                                // 0x0000000000000000
    if (bits_of(math_cbrt_c(nzero)) != 9223372036854775808) { rc = rc | 131072; }            // 0x8000000000000000
    if (bits_of(math_cbrt_c(1.0)) != 4607182418800017408) { rc = rc | 262144; }              // 0x3ff0000000000000
    if (bits_of(math_cbrt_c(8.0)) != 4611686018427387904) { rc = rc | 524288; }              // 0x4000000000000000
    if (bits_of(math_cbrt_c(0.0 - 8.0)) != 13835058055282163712) { rc = rc | 1048576; }      // 0xc000000000000000
    if (bits_of(math_cbrt_c(2.0)) != 4608352999143469707) { rc = rc | 2097152; }             // 0x3ff428a2f98d728b
    if (bits_of(math_cbrt_c(0.0 - 2.0)) != 13831725035998245515) { rc = rc | 4194304; }      // 0xbff428a2f98d728b
    if (bits_of(math_cbrt_c(0.1)) != 4602033163014492147) { rc = rc | 8388608; }             // 0x3fddb4c7760bcff3
    if (bits_of(math_cbrt_c(10.0)) != 4612033774433628239) { rc = rc | 16777216; }           // 0x40013c484138704f
    if (bits_of(math_cbrt_c(tiny10)) != 4557197843775105256) { rc = rc | 33554432; }         // 0x3f3e6b4b396428e8
    if (bits_of(math_cbrt_c(inf)) != 9218868437227405312) { rc = rc | 67108864; }            // 0x7ff0000000000000
    if (bits_of(math_cbrt_c(0.0 - inf)) != 18442240474082181120) { rc = rc | 134217728; }    // 0xfff0000000000000
    if (isnan_bits(math_cbrt_c(nan)) != 1) { rc = rc | 268435456; }                          // cbrt(NaN)=NaN
    if (bits_of(math_cbrt_c(0.0 - 1.0)) != 13830554455654793216) { rc = rc | 536870912; }   // 0xbff0000000000000
    if (bits_of(math_cbrt_c(3.141592653589793)) != 4609274754651718839) { rc = rc | 1073741824; } // 0x3ff76ef7e73104b7 (fdlibm 1ulp)

    return rc;
  }
}
