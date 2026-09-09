/**
 * Defect D neighborhood: u8 vs INT_LIT still uses lit coerce (wave666).
 * Expect exit 0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let a: u8 = 3;
  if (a == 3) {
    return 0;
  }
  return 1;
}
