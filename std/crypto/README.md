# std.crypto — 常量时间比较、SHA-256/512、HMAC

**路径**：`std/crypto/`（mod.su + crypto.c）  
**依赖**：core。**性能**：restrict、热路径标注，对标 Zig std.crypto。

| API | 说明 |
|-----|------|
| `mem_eq(a, b, len): i32` | 常量时间比较，相等 1 |
| `sha256(msg, len, out): void` | 输出 32 字节 |
| `sha512(msg, len, out): void` | 输出 64 字节 |
| `hmac_sha256(key, key_len, msg, msg_len, out): void` | HMAC-SHA256，out 32 字节 |
