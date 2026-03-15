# std.base64 — Base64 编解码

**路径**：`std/base64/`（mod.su + base64.c）  
**依赖**：core。**性能**：单遍、静态表、无分配，对标 Zig std.base64。

| API | 说明 |
|-----|------|
| `encode_standard(src, len, out, cap): i32` | 标准编码，含填充 |
| `encode_url(src, len, out, cap): i32` | URL 变体，无填充 |
| `decode_standard(src, len, out, cap): i32` | 标准解码 |
| `decode_url(src, len, out, cap): i32` | URL 解码 |
