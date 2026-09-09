/**
 * Defect D neighborhood: product-style while ((i + 1) == 3) stays green.
 * i starts 2 so the body runs once; exit 0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let i: i32 = 2;
  while ((i + 1) == 3) {
    i = i + 1;
  }
  if (i == 3) {
    return 0;
  }
  return 1;
}
