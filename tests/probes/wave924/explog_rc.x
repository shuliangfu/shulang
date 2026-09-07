// wave924 (9.2.4 Wave A) · rc-gated bit-exact probe: math_exp_c / math_log_c
// fdlibm e_exp.c / e_log.c .x ports (runtime_math_libm.x). Expectations are
// pinned to fdlibm discrete-op semantics, cross-verified three ways
// (2026-09-08): the .x binary, the seed C twins, and a Python float64
// discrete-op simulation all produce identical bits on all 48 cases; 45/48
// also equal the correctly-rounded host libm, and the 3 remaining cases
// (exp(1), exp(-10), log(3) — marked below) sit exactly 1 ulp off
// correctly-rounded, which is the documented fdlibm <1ulp characteristic
// (pinned here so both platforms assert fdlibm semantics, not libm).
// The 3 NaN cases assert NaN-ness (exponent all-ones, mantissa nonzero)
// because NaN payload propagation through fp add/div is platform-defined.
// rc accumulates a unique error bit per failed case. Decimal expectation
// literals are Python-converted from the hex shown in comments (repo rule:
// decimal<->hex conversion via Python only).
// PLATFORM: SHARED — deterministic IEEE double ops, same bits on arm64/x86_64.
export extern "C" function math_exp_c(x: f64): f64;
export extern "C" function math_log_c(x: f64): f64;

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
  if ((b >> 52) & 2047) == 2047 {
    if (b & 4503599627370495) != 0 { return 1; }
  }
  return 0;
}

function main(): i32 {
  unsafe {
    let rc: i32 = 0;
    let inf: f64 = 1e308 * 10.0;
    let nz: f64 = 0.0;
    let nan: f64 = nz / nz;
    let tiny10: f64 = 1e-10;
    let sub320: f64 = 1e-320;
    let b: u64 = 0;

    // === exp (26 cases; case k adds error bit 1<<k) ===
    if bits_of(math_exp_c(0.0)) != 4607182418800017408 { rc = rc | 1; }          // 0x3ff0000000000000
    if bits_of(math_exp_c(1.0)) != 4613303445314885482 { rc = rc | 2; }          // 0x4005bf0a8b14576a (fdlibm 1ulp)
    if bits_of(math_exp_c(0.0 - 1.0)) != 4600298746774613816 { rc = rc | 4; }    // 0x3fd78b56362cef38
    if bits_of(math_exp_c(2.0)) != 4620005356000828846 { rc = rc | 8; }          // 0x401d8e64b8d4ddae
    if bits_of(math_exp_c(0.0 - 2.0)) != 4594043987739771340 { rc = rc | 16; }   // 0x3fc152aaa3bf81cc
    if bits_of(math_exp_c(0.5)) != 4610103999673009820 { rc = rc | 32; }         // 0x3ffa61298e1e069c
    if bits_of(math_exp_c(0.0 - 0.5)) != 4603638362051417610 { rc = rc | 64; }   // 0x3fe368b2fc6f960a
    if bits_of(math_exp_c(0.1)) != 4607656066507473108 { rc = rc | 128; }        // 0x3ff1aec7b35a00d4
    if bits_of(math_exp_c(0.0 - 0.1)) != 4606325270462671674 { rc = rc | 256; }  // 0x3fecf46d99d52b3a
    if bits_of(math_exp_c(10.0)) != 4671783802770883936 { rc = rc | 512; }       // 0x40d5829dcf950560
    if bits_of(math_exp_c(0.0 - 10.0)) != 4541824671844433050 { rc = rc | 1024; }        // 0x3f07cd79b5647c9a (fdlibm 1ulp)
    if bits_of(math_exp_c(100.0)) != 5256625774849891317 { rc = rc | 2048; }             // 0x48f3494a9b171bf5
    if bits_of(math_exp_c(0.0 - 100.0)) != 3957129287720677213 { rc = rc | 4096; }       // 0x36ea8c1f14e2af5d
    if bits_of(math_exp_c(700.0)) != 9155136748776909966 { rc = rc | 8192; }             // 0x7f0d945df4f8ec8e
    if bits_of(math_exp_c(0.0 - 700.0)) != 58915316498509951 { rc = rc | 16384; }        // 0x00d14f2b0fb9307f
    if bits_of(math_exp_c(709.0)) != 9213593174447348891 { rc = rc | 32768; }            // 0x7fdd422d2be5dc9b
    if bits_of(math_exp_c(0.0 - 745.0)) != 1 { rc = rc | 65536; }                        // 0x0000000000000001
    if bits_of(math_exp_c(710.0)) != 9218868437227405312 { rc = rc | 131072; }           // 0x7ff0000000000000
    if bits_of(math_exp_c(0.0 - 746.0)) != 0 { rc = rc | 262144; }                       // 0x0000000000000000
    if bits_of(math_exp_c(inf)) != 9218868437227405312 { rc = rc | 524288; }             // exp(+inf)=+inf
    if bits_of(math_exp_c(0.0 - inf)) != 0 { rc = rc | 1048576; }                        // exp(-inf)=+0
    if isnan_bits(math_exp_c(nan)) != 1 { rc = rc | 2097152; }                           // exp(NaN)=NaN
    if bits_of(math_exp_c(tiny10)) != 4607182418800467768 { rc = rc | 4194304; }         // 0x3ff000000006df38
    if bits_of(math_exp_c(sub320)) != 4607182418800017408 { rc = rc | 8388608; }         // 0x3ff0000000000000
    if bits_of(math_exp_c(3.7e-9)) != 4607182418816680727 { rc = rc | 16777216; }        // 0x3ff0000000fe4317
    if bits_of(math_exp_c(1.1)) != 4613947199293019539 { rc = rc | 33554432; }           // 0x400808883244d593

    // === log (22 cases; case k adds error bit 1<<k) ===
    if bits_of(math_log_c(1.0)) != 0 { rc = rc | 1; }                            // 0x0000000000000000
    if bits_of(math_log_c(2.0)) != 4604418534313441775 { rc = rc | 2; }          // 0x3fe62e42fefa39ef
    if bits_of(math_log_c(0.5)) != 13827790571168217583 { rc = rc | 4; }         // 0xbfe62e42fefa39ef
    if bits_of(math_log_c(10.0)) != 4612367379483415830 { rc = rc | 8; }         // 0x40026bb1bbb55516
    if bits_of(math_log_c(0.1)) != 13835739416338191637 { rc = rc | 16; }        // 0xc0026bb1bbb55515
    if bits_of(math_log_c(3.0)) != 4607626529066517258 { rc = rc | 32; }         // 0x3ff193ea7aad030a (fdlibm 1ulp)
    if bits_of(math_log_c(1.5)) != 4600975829957056588 { rc = rc | 64; }         // 0x3fd9f323ecbf984c
    if bits_of(math_log_c(0.8)) != 13820579650861701664 { rc = rc | 128; }       // 0xbfcc8ff7c79a9a20
    if bits_of(math_log_c(1.4142135623730951)) != 4599914934686071280 { rc = rc | 256; }   // 0x3fd62e42fefa39f0
    if bits_of(math_log_c(5.0)) != 4609927083155361075 { rc = rc | 512; }                  // 0x3ff9c041f7ed8d33
    if bits_of(math_log_c(1.0000001)) != 4502148214114968722 { rc = rc | 1024; }           // 0x3e7ad7f2847b6492
    if bits_of(math_log_c(0.9999999)) != 13725520251716934559 { rc = rc | 2048; }          // 0xbe7ad7f2b1049b9f
    if bits_of(math_log_c(1.0000000000000002)) != 4372995238176751615 { rc = rc | 4096; }  // 0x3cafffffffffffff
    if bits_of(math_log_c(1e300)) != 4649287341619838901 { rc = rc | 8192; }               // 0x4085963447f87fb5
    if bits_of(math_log_c(1e-300)) != 13872659378474614709 { rc = rc | 16384; }            // 0xc085963447f87fb5
    if bits_of(math_log_c(sub320)) != 13873064453625931053 { rc = rc | 32768; }            // 0xc087069e3078e52d
    if bits_of(math_log_c(1e10)) != 4627174418536376923 { rc = rc | 65536; }               // 0x4037069e2aa2aa5b
    if bits_of(math_log_c(709.0)) != 4619076262753238869 { rc = rc | 131072; }             // 0x401a416357d87f55
    if bits_of(math_log_c(0.0)) != 18442240474082181120 { rc = rc | 262144; }              // 0xfff0000000000000
    if isnan_bits(math_log_c(0.0 - 1.0)) != 1 { rc = rc | 524288; }                        // log(-#)=NaN
    if bits_of(math_log_c(inf)) != 9218868437227405312 { rc = rc | 1048576; }              // log(+inf)=+inf
    if isnan_bits(math_log_c(nan)) != 1 { rc = rc | 2097152; }                             // log(NaN)=NaN

    b = 0;
    return rc;
  }
}
