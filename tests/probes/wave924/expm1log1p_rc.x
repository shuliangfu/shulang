// wave924 (9.2.4) · rc-gated bit-exact probe: math_expm1_c / math_log1p_c
// fdlibm s_expm1.c / s_log1p.c .x ports (runtime_math_libm.x).
// Both pin fdlibm discrete-op semantics (error < 1 ulp). Two cases in this
// probe sit 1 ulp off correctly-rounded host libm and are pinned here so
// both platforms assert fdlibm, not host: expm1(1.0) and log1p(2.0).
// NaN cases assert NaN-ness because payload propagation through fp add/div
// is platform-defined.
// rc: expm1 failures in bits 0..14, log1p failures in bits 16..30.
// Decimal expectation literals are Python-converted from the hex shown.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_expm1_c(x: f64): f64;
export extern "C" function math_log1p_c(x: f64): f64;

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

    // === expm1 (15 cases; bit k) ===
    if (bits_of(math_expm1_c(0.0)) != 0) { rc = rc | 1; }                                   // 0x0000000000000000
    if (bits_of(math_expm1_c(nzero)) != 9223372036854775808) { rc = rc | 2; }                // 0x8000000000000000
    if (bits_of(math_expm1_c(1.0)) != 4610417272575012562) { rc = rc | 4; }                  // 0x3ffb7e151628aed2 (fdlibm 1ulp)
    if (bits_of(math_expm1_c(0.0 - 1.0)) != 13827240892226439268) { rc = rc | 8; }           // 0xbfe43a54e4e98864
    if (bits_of(math_expm1_c(0.5)) != 4604018381291261240) { rc = rc | 16; }                 // 0x3fe4c2531c3c0d38
    if (bits_of(math_expm1_c(0.0 - 0.5)) != 13824131770269881324) { rc = rc | 32; }          // 0xbfd92e9a0720d3ec
    if (bits_of(math_expm1_c(0.1)) != 4592242783982456122) { rc = rc | 64; }                 // 0x3fbaec7b35a00d3a
    if (bits_of(math_expm1_c(2.0)) != 4618879456093986222) { rc = rc | 128; }                // 0x40198e64b8d4ddae
    if (bits_of(math_expm1_c(10.0)) != 4671783527892976992) { rc = rc | 256; }               // 0x40d5825dcf950560
    if (bits_of(math_expm1_c(0.0 - 10.0)) != 13830554046728579694) { rc = rc | 512; }        // 0xbfefffa0ca192a6e
    if (bits_of(math_expm1_c(tiny10)) != 4457293557087970531) { rc = rc | 1024; }            // 0x3ddb7cdfd9dda4e3
    if (bits_of(math_expm1_c(inf)) != 9218868437227405312) { rc = rc | 2048; }               // 0x7ff0000000000000
    if (bits_of(math_expm1_c(0.0 - inf)) != 13830554455654793216) { rc = rc | 4096; }        // 0xbff0000000000000
    if (isnan_bits(math_expm1_c(nan)) != 1) { rc = rc | 8192; }                              // expm1(NaN)=NaN
    if (bits_of(math_expm1_c(3.141592653589793)) != 4626925268625298233) { rc = rc | 16384; } // 0x403624046eb09339

    // === log1p (15 cases; bit 16+k) ===
    if (bits_of(math_log1p_c(0.0)) != 0) { rc = rc | 65536; }                                // 0x0000000000000000
    if (bits_of(math_log1p_c(1.0)) != 4604418534313441775) { rc = rc | 131072; }             // 0x3fe62e42fefa39ef
    if (bits_of(math_log1p_c(0.0 - 0.5)) != 13827790571168217583) { rc = rc | 262144; }      // 0xbfe62e42fefa39ef
    if (bits_of(math_log1p_c(0.5)) != 4600975829957056588) { rc = rc | 524288; }             // 0x3fd9f323ecbf984c
    if (bits_of(math_log1p_c(0.1)) != 4591532242907186887) { rc = rc | 1048576; }            // 0x3fb8663f793c46c7
    if (bits_of(math_log1p_c(2.0)) != 4607626529066517258) { rc = rc | 2097152; }            // 0x3ff193ea7aad030a (fdlibm 1ulp)
    if (bits_of(math_log1p_c(9.0)) != 4612367379483415830) { rc = rc | 4194304; }            // 0x40026bb1bbb55516
    if (bits_of(math_log1p_c(0.0 - 0.9)) != 13835739416338191638) { rc = rc | 8388608; }     // 0xc0026bb1bbb55516
    if (bits_of(math_log1p_c(0.0 - 1.0)) != 18442240474082181120) { rc = rc | 16777216; }    // 0xfff0000000000000
    if (isnan_bits(math_log1p_c(0.0 - 1.1)) != 1) { rc = rc | 33554432; }                    // log1p(x<-1)=NaN
    if (bits_of(math_log1p_c(tiny10)) != 4457293557087196819) { rc = rc | 67108864; }        // 0x3ddb7cdfd9d1d693
    if (bits_of(math_log1p_c(inf)) != 9218868437227405312) { rc = rc | 134217728; }          // 0x7ff0000000000000
    if (isnan_bits(math_log1p_c(nan)) != 1) { rc = rc | 268435456; }                         // log1p(NaN)=NaN
    if (bits_of(math_log1p_c(3.141592653589793)) != 4609078796390170799) { rc = rc | 536870912; } // 0x3ff6bcbed09f00af
    if (bits_of(math_log1p_c(0.0 - 0.3)) != 13823468941351141198) { rc = rc | 1073741824; }  // 0xbfd6d3c324e13f4e

    return rc;
  }
}
