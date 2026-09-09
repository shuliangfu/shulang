// PLATFORM: SHARED — 9.6.1/9.6.2 regression: integer ARRAY_LIT still .data-bakes.
let A: i32[2] = [10, 32];

function main(): i32 {
  return A[0] + A[1];
}
