// 复合赋值测试：+=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
function main(): i32 {
  let x: i32 = 10;
  x += 2;
  if (x != 12) { return 1; }
  x -= 3;
  if (x != 9) { return 2; }
  x *= 2;
  if (x != 18) { return 3; }
  x /= 3;
  if (x != 6) { return 4; }
  x %= 4;
  if (x != 2) { return 5; }
  let y: i32 = 255;
  y &= 15;
  if (y != 15) { return 6; }
  y |= 240;
  if (y != 255) { return 7; }
  let z: i32 = 1;
  z ^= 3;
  if (z != 2) { return 8; }
  let a: i32 = 4;
  a <<= 2;
  if (a != 16) { return 9; }
  a >>= 1;
  if (a != 8) { return 10; }
  return 0;
}
