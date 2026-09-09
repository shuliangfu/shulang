// PLATFORM: SHARED — empty [] stays COMMON BSS zero (9.6.2 p9 regression).
let Z: u8[4] = [];

function main(): i32 {
  return Z[0] as i32;
}
