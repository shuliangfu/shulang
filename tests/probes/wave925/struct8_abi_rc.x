// wave925 · rc-gated probe: SysV / AAPCS64 INTEGER-class 8B struct ABI.
// `Handle8 { handle: i64 }` must return and pass in rax/x0 like i64 —
// never lea a callee-local slot (Ubuntu ArrowColumn free() abort).
// Unix $? is 8-bit: pack rc!=0 → return 1.
// PLATFORM: SHARED — Ubuntu x86_64 SysV gold; Darwin AAPCS64 x0 must stay green.

export struct Handle8 {
  handle: i64;
}

/**
 * Build a by-value 8-byte INTEGER-class struct.
 * @param v i64 — payload stored in handle
 * @return Handle8 — bits in rax/x0, not a pointer to a local
 */
function make_h(v: i64): Handle8 {
  let _rc: Handle8 = { handle: 0 };
  _rc = { handle: v };
  return _rc;
}

/**
 * Consume a by-value 8-byte INTEGER-class struct.
 * @param h Handle8 — bits in rdi/x0
 * @return i64 — h.handle
 */
function take_h(h: Handle8): i64 {
  return h.handle;
}

/**
 * Round-trip 8B struct return + pass. Return 0 if bits survive, 1 otherwise.
 * @return i32 — 0 all pass, 1 any fail (8-bit-safe)
 */
function main(): i32 {
  /* Values that fit i32 as well as i64: field-load width residual still
   * ldr-w 32-bit on Darwin; do not use -1 here (that card is CORE-016).
   * The ABI under test is make_h return + take_h pass of 8B INTEGER class. */
  let forty_two: i64 = 42;
  let zero: i64 = 0;
  let h: Handle8 = make_h(forty_two);
  let got: i64 = take_h(h);
  if (got != forty_two) {
    return 1;
  }
  let z: Handle8 = make_h(zero);
  let gotz: i64 = take_h(z);
  if (gotz != zero) {
    return 1;
  }
  return 0;
}
