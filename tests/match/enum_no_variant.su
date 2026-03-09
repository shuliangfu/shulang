// 边界：match 分支使用枚举不存在的变体，应报 enum has no variant
enum E { A, B }
function main(): i32 {
  let e: E = E.A;
  return match e { E.C => 1; _ => 0; }
}
