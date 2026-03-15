# std.error — 错误类型与传播

与 **Zig** 错误集、**Rust** Result/Error、**Go** error 对标。

## 类型与常量

- **Error**：`{ code: i32 }`；code==0 表示成功。
- `error_ok()`：返回 0（无错误码）。
- `error_code_alloc_fail()` / `error_code_invalid()` / `error_code_not_found()`：常用错误码 -1/-2/-3。

## API

| 函数 | 说明 |
|------|------|
| `error_ok_value()` | 构造“无错误” Error |
| `error_from_code(code)` | 从错误码构造 Error |
| `error_code(e)` | 取错误码 |
| `error_is_ok(e)` / `error_is_err(e)` | 是否成功 / 是否错误 |

## 约定

- 与 std.io、std.fs 等返回的 i32 错误码一致：0 成功，非 0 错误（正/负由各模块约定）。
