// wave924 (9.2.4) · rc-gated bit-exact probe: math_atan2_c
// fdlibm e_atan2.c .x port (runtime_math_libm.x). Reuses math_atan_c (G.7).
// Pins fdlibm discrete-op semantics (error < 1 ulp). Documented diffs vs
// correctly-rounded host libm:
//   * atan2(1, 10) sits 1 ulp off host (pin fdlibm 0x3fb983e282e2cc4d)
// fdlibm does not distinguish x=-0 from x=+0 when y is nonzero (IEEE
// 754-2008 wants +-pi for atan2(+-y, -0); this probe pins fdlibm = +-pi/2).
// Non-dyadic inputs are bit-punned from Python-verified IEEE u64 (the X
// decimal lexer is 1 ulp off on values such as 0.7 / 0.3 — standing card,
// not this knife). NaN cases assert NaN-ness because payload through
// x+y is platform-defined.
// rc packed to 8-bit exit: 0 = all 30 cases pass, 1 = any fail.
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_atan2_c(y: f64, x: f64): f64;

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
    let x03: f64 = f64_from_bits(4599075939470750515);     /* 0.3  0x3fd3333333333333 */
    let x1em10: f64 = f64_from_bits(4457293557087583675);  /* 1e-10 0x3ddb7cdfd9d7bdbb */

    /* ---- signed zeros / quadrants bits 0..11 ---- */
    if (bits_of(math_atan2_c(0.0, 0.0)) != 0) { rc = rc | 1; }                               // +0,+0
    if (bits_of(math_atan2_c(nzero, 0.0)) != 9223372036854775808) { rc = rc | 2; }            // -0,+0
    if (bits_of(math_atan2_c(0.0, nzero)) != 4614256656552045848) { rc = rc | 4; }            // +0,-0 = +pi
    if (bits_of(math_atan2_c(nzero, nzero)) != 13837628693406821656) { rc = rc | 8; }         // -0,-0 = -pi
    if (bits_of(math_atan2_c(1.0, 0.0)) != 4609753056924675352) { rc = rc | 16; }             // +pi/2
    if (bits_of(math_atan2_c(1.0, nzero)) != 4609753056924675352) { rc = rc | 32; }           // fdlibm +pi/2
    if (bits_of(math_atan2_c(0.0 - 1.0, 0.0)) != 13833125093779451160) { rc = rc | 64; }     // -pi/2
    if (bits_of(math_atan2_c(1.0, 1.0)) != 4605249457297304856) { rc = rc | 128; }            // +pi/4
    if (bits_of(math_atan2_c(1.0, 0.0 - 1.0)) != 4612488097114038738) { rc = rc | 256; }      // +3pi/4
    if (bits_of(math_atan2_c(0.0 - 1.0, 1.0)) != 13828621494152080664) { rc = rc | 512; }     // -pi/4
    if (bits_of(math_atan2_c(0.0 - 1.0, 0.0 - 1.0)) != 13835860133968814546) { rc = rc | 1024; }
    if (bits_of(math_atan2_c(0.5, 0.5)) != 4605249457297304856) { rc = rc | 2048; }

    /* ---- finite / inf / nan bits 12..29 ---- */
    if (bits_of(math_atan2_c(x07, x01)) != 4609114009402435069) { rc = rc | 4096; }
    if (bits_of(math_atan2_c(x01, x07)) != 4594280400468457693) { rc = rc | 8192; }
    if (bits_of(math_atan2_c(2.0, 1.0)) != 4607664973725548100) { rc = rc | 16384; }
    if (bits_of(math_atan2_c(1.0, 2.0)) != 4602023952714414927) { rc = rc | 32768; }
    if (bits_of(math_atan2_c(10.0, 1.0)) != 4609304189218455636) { rc = rc | 65536; }
    if (bits_of(math_atan2_c(1.0, 10.0)) != 4591846303962680397) { rc = rc | 131072; }        // fdlibm 1ulp
    if (bits_of(math_atan2_c(inf, inf)) != 4605249457297304856) { rc = rc | 262144; }         // +pi/4
    if (bits_of(math_atan2_c(inf, 0.0 - inf)) != 4612488097114038738) { rc = rc | 524288; }   // +3pi/4
    if (bits_of(math_atan2_c(inf, 1.0)) != 4609753056924675352) { rc = rc | 1048576; }        // +pi/2
    if (bits_of(math_atan2_c(1.0, inf)) != 0) { rc = rc | 2097152; }                          // +0
    if (bits_of(math_atan2_c(1.0, 0.0 - inf)) != 4614256656552045848) { rc = rc | 4194304; }  // +pi
    if (bits_of(math_atan2_c(0.0 - 1.0, inf)) != 9223372036854775808) { rc = rc | 8388608; }  // -0
    if (isnan_bits(math_atan2_c(nan, 1.0)) != 1) { rc = rc | 16777216; }
    if (isnan_bits(math_atan2_c(1.0, nan)) != 1) { rc = rc | 33554432; }
    if (bits_of(math_atan2_c(x1em10, 1.0)) != 4457293557087583675) { rc = rc | 67108864; }
    if (bits_of(math_atan2_c(1.0, x1em10)) != 4609753056924224992) { rc = rc | 134217728; }
    if (bits_of(math_atan2_c(0.0 - x07, x03)) != 13831301623281612284) { rc = rc | 268435456; }
    if (bits_of(math_atan2_c(x03, 0.0 - x07)) != 4613344921303126410) { rc = rc | 536870912; }

    if (rc != 0) {
      return 1;
    }
    return 0;
  }
}
