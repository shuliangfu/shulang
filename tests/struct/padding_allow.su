// 有隐式 padding 但写了 allow(padding)，应通过
allow(padding)
struct WithGap {
  a: u8
  b: i32
}

function main(): i32 {
  let x: WithGap = WithGap { a: 1, b: 2 };
  return x.b;
}
