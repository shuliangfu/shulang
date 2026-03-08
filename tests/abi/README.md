# ABI/布局断言测试

与 `analysis/ABI与布局.md`、`analysis/内存契约.md` 对应：用 C 断言切片与 packed 结构体的布局（大小、偏移）。

- **layout_abi.c**：`struct shulang_slice_u8` 在 64 位下 16 字节、data 偏移 0、len 偏移 8；`struct Header_packed` 5 字节、字段偏移 0 与 1。

运行：`cd tests && sh run-abi-layout.sh`，或 `cc -o /tmp/layout_abi tests/abi/layout_abi.c && /tmp/layout_abi`。
