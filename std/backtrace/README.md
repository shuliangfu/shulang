# std.backtrace

调用栈捕获，对标 Rust std::backtrace。

## API

- **capture(buf, max_frames): i32** — 将当前调用栈写入 `buf`（每帧 `sizeof(void*)` 字节），返回帧数；失败或不支持平台返回 0。
- **symbolicate(...)** — 占位，当前返回 0；后续可对接 `backtrace_symbols` / `dladdr` 等。

## 平台说明

| 平台 | capture | symbolicate |
|------|--------|-------------|
| Linux | `backtrace()` (execinfo.h) | 未实现 |
| macOS | `backtrace()` (execinfo.h) | 未实现 |
| Windows | `CaptureStackBackTrace` | 未实现 |
| 其他 | 返回 0 | 返回 0 |

编译调试版本时建议使用 `-g`（及 Linux 上 `-rdynamic`）以便后续符号化时解析函数名。
