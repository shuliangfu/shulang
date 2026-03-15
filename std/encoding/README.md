# std.encoding — UTF-8/ASCII

**路径**：`std/encoding/`（mod.su + encoding.c）  
**依赖**：core。**性能**：表驱动、单遍、restrict、LIKELY/UNLIKELY，对标 Zig std.unicode.utf8。

| API | 说明 |
|-----|------|
| `utf8_valid(ptr, len): i32` | 校验合法返回 1 |
| `utf8_len_chars(ptr, len): i32` | 码点个数，非法 -1 |
| `utf8_encode_rune(r, out): i32` | 写入 1..4 字节 |
| `utf8_decode_rune(ptr, len, out_r): i32` | 返回消费字节数 |
| `ascii_is_alpha/digit/alnum/lower/upper(c): i32` | 分类 |
| `ascii_to_lower/upper(c): u8` | 转换 |
