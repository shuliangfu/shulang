// 内存契约：packed 结构体无填充，与 C __attribute__((packed)) 一致
struct Header packed {
  tag: u8;
  len: u32;
}

function main(): i32 {
  let h: Header = Header { tag: 1, len: 42 };
  return 0;
}
