// wave924 (9.2.4) · rc-gated bit-exact probe: math_asin_c / math_acos_c / math_atan_c
// fdlibm e_asin.c / e_acos.c / s_atan.c .x ports (runtime_math_libm.x).
// Pins fdlibm discrete-op semantics (error < 1 ulp). A few cases sit 1 ulp
// off correctly-rounded host libm and are pinned here so both platforms
// assert fdlibm, not host: asin(+-0.5), acos(0.5), acos(0.999),
// atan(+-0.5), atan(2), atan(10).
// Non-dyadic inputs are bit-punned from Python-verified IEEE u64 (the X
// decimal lexer is 1 ulp off on values such as 0.7 — standing card, not
// this knife). NaN cases assert NaN-ness because payload through
// (x-x)/(x-x) or x+x is platform-defined.
// rc packed to 8-bit exit: 0 = all 30 cases pass, 1 = any fail.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_asin_c(x: f64): f64;
export extern "C" function math_acos_c(x: f64): f64;
export extern "C" function math_atan_c(x: f64): f64;

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
    /* Python-verified input bits (rule: decimal<->hex via Python only). */
    let x07: f64 = f64_from_bits(4604480259023595110);     /* 0.7  0x3fe6666666666666 */
    let x01: f64 = f64_from_bits(4591870180066957722);     /* 0.1  0x3fb999999999999a */
    let x099: f64 = f64_from_bits(4607092346807469998);    /* 0.99 0x3fefae147ae147ae */
    let x09: f64 = f64_from_bits(4606281698874543309);     /* 0.9  0x3feccccccccccccd */
    let x0999: f64 = f64_from_bits(4607173411600762667);   /* 0.999 */
    let x1em10: f64 = f64_from_bits(4457293557087583675);  /* 1e-10 0x3ddb7cdfd9d7bdbb */

    /* ---- asin bits 0..9 ---- */
    if (bits_of(math_asin_c(0.0)) != 0) { rc = rc | 1; }                                    // +0
    if (bits_of(math_asin_c(nzero)) != 9223372036854775808) { rc = rc | 2; }                 // -0
    if (bits_of(math_asin_c(0.5)) != 4602891378046628710) { rc = rc | 4; }                   // fdlibm 1ulp vs host
    if (bits_of(math_asin_c(1.0)) != 4609753056924675352) { rc = rc | 8; }                   // +pi/2
    if (bits_of(math_asin_c(0.0 - 1.0)) != 13833125093779451160) { rc = rc | 16; }           // -pi/2
    if (bits_of(math_asin_c(x01)) != 4591882244033050756) { rc = rc | 32; }
    if (bits_of(math_asin_c(x07)) != 4605159379298876821) { rc = rc | 64; }                  // |x|>=0.5 path
    if (bits_of(math_asin_c(x099)) != 4609115619805353245) { rc = rc | 128; }                // |x|>0.975 path
    if (bits_of(math_asin_c(x1em10)) != 4457293557087583675) { rc = rc | 256; }              // tiny 1e-10
    if (isnan_bits(math_asin_c(1.5)) != 1) { rc = rc | 512; }                                // |x|>1 = NaN

    /* ---- acos bits 10..19 ---- */
    if (bits_of(math_acos_c(0.0)) != 4609753056924675352) { rc = rc | 1024; }                // pi/2
    if (bits_of(math_acos_c(1.0)) != 0) { rc = rc | 2048; }                                  // 0
    if (bits_of(math_acos_c(0.0 - 1.0)) != 4614256656552045848) { rc = rc | 4096; }          // pi
    if (bits_of(math_acos_c(0.5)) != 4607394977673999206) { rc = rc | 8192; }                // fdlibm 1ulp
    if (bits_of(math_acos_c(0.0 - 0.5)) != 4611898577301369702) { rc = rc | 16384; }
    if (bits_of(math_acos_c(x01)) != 4609301942964057488) { rc = rc | 32768; }
    if (bits_of(math_acos_c(x09)) != 4601796596644064920) { rc = rc | 65536; }
    if (bits_of(math_acos_c(x0999)) != 4586606385384825502) { rc = rc | 131072; }             // fdlibm 1ulp
    if (bits_of(math_acos_c(0.0 - x07)) != 4612465577614431730) { rc = rc | 262144; }         // fdlibm 1ulp
    if (isnan_bits(math_acos_c(1.5)) != 1) { rc = rc | 524288; }

    /* ---- atan bits 20..29 ---- */
    if (bits_of(math_atan_c(0.0)) != 0) { rc = rc | 1048576; }
    if (bits_of(math_atan_c(1.0)) != 4605249457297304856) { rc = rc | 2097152; }             // pi/4
    if (bits_of(math_atan_c(0.0 - 1.0)) != 13828621494152080664) { rc = rc | 4194304; }
    if (bits_of(math_atan_c(0.5)) != 4602023952714414927) { rc = rc | 8388608; }             // fdlibm 1ulp
    if (bits_of(math_atan_c(inf)) != 4609753056924675352) { rc = rc | 16777216; }            // +pi/2
    if (bits_of(math_atan_c(0.0 - inf)) != 13833125093779451160) { rc = rc | 33554432; }     // -pi/2
    if (bits_of(math_atan_c(10.0)) != 4609304189218455636) { rc = rc | 67108864; }           // fdlibm 1ulp
    if (bits_of(math_atan_c(x01)) != 4591846303962680397) { rc = rc | 134217728; }
    if (bits_of(math_atan_c(2.0)) != 4607664973725548100) { rc = rc | 268435456; }           // fdlibm 1ulp
    if (isnan_bits(math_atan_c(nan)) != 1) { rc = rc | 536870912; }

    if (rc != 0) {
      return 1;
    }
    return 0;
  }
}
