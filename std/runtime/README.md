# std.runtime — 运行时与 panic

与 **Zig** @panic、**Rust** std::panic / std::process::abort、**Go** runtime/panic 对标。

## API

| 函数 | 说明 |
|------|------|
| `panic()` | 无参 panic，终止程序（noreturn）。用于断言失败、不可达分支。对标 Rust panic!()、Zig @panic、Go panic()。 |
| `abort()` | 终止程序（noreturn）；与 panic 同义。对标 C abort()、Rust std::process::abort。 |
| `runtime_ready()` | 运行时已就绪（占位）；返回 0。可用于初始化检查。对标 Go runtime 初始化语义。 |

## 实现

- panic/abort 经 `std/runtime/runtime.c` 调用 `shulang_panic_(0, 0)`，该符号由编译器链接时提供的 runtime_panic.o（或 libc abort）提供。

## 对标说明

- **Zig**：无独立 runtime 模块，@panic 为内建。
- **Rust**：std::panic::panic!、set_hook、catch_unwind；std::process::abort。我们提供最小集 panic/abort。
- **Go**：panic()、recover()、runtime.Goexit、runtime.NumCPU 等；我们提供 panic/abort/ready，recover 可后续扩展。
