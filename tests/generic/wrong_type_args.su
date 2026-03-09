// 边界：泛型调用类型实参数量错误，应报 expects N type arguments, got M 或 requires type arguments
function id<T>(x: T): T { return x; }
function main(): i32 {
  return id<i32, u32>(42);
}
