# std.time — 时间与睡眠

**模块路径**：`std/time/`（mod.su + time.c）  
**依赖**：core（extern C），无其它 .su 模块。  
**对标**：Zig std.time、Rust std::time::Instant/SystemTime/Duration。

## API 概览

| 函数 | 说明 |
|------|------|
| `now_monotonic_ns(): i64` | 单调时钟，纳秒 |
| `now_monotonic_us(): i64` | 单调时钟，微秒 |
| `now_monotonic_ms(): i64` | 单调时钟，毫秒 |
| `now_monotonic_sec(): i64` | 单调时钟，秒 |
| `now_wall_sec(): i64` | 墙钟，自 Unix 纪元秒 |
| `now_wall_ms(): i64` | 墙钟，毫秒 |
| `now_wall_us(): i64` | 墙钟，微秒 |
| `now_wall_ns(): i64` | 墙钟，纳秒（Windows 粒度 100ns） |
| `sleep_ns(ns: i64): void` | 睡眠，纳秒 |
| `sleep_us(us: i64): void` | 睡眠，微秒 |
| `sleep_ms(ms: i32): void` | 睡眠，毫秒 |
| `sleep_sec(s: i32): void` | 睡眠，秒 |
| `duration_ns(from_ns: i64, to_ns: i64): i64` | 时间差 to_ns - from_ns |

## 实现说明

- **单调时钟**：Linux/macOS 使用 `clock_gettime(CLOCK_MONOTONIC)`；Windows 使用 `QueryPerformanceCounter`。
- **墙钟**：Linux/macOS 使用 `clock_gettime(CLOCK_REALTIME)`；Windows 使用 `GetSystemTimePreciseAsFileTime`（100ns 粒度）。
- **睡眠**：POSIX `nanosleep`；Windows `Sleep(ms)`，不足 1ms 按 1ms 处理。
- 全平台一套 .su API，内部由 time.c 条件编译适配。

## 功能完整性（P1 规格）

与 `analysis/std标准库全量清单与优先级.md` 3.1 一致，已全部实现：

- 单调：`now_monotonic_ns/us/ms/sec`（一次 syscall，us/ms/sec 由 ns 换算）
- 墙钟：`now_wall_sec/ms/us/ns`（墙钟仅实现 _ns，sec/ms/us 由 _ns 派生，减少重复代码）
- 睡眠：`sleep_ns/us/ms/sec`
- 时间差：`duration_ns(from_ns, to_ns)`（纯算术，零 syscall）

## 性能优化

- **单次 syscall**：每个 `now_*` 调用仅一次系统调用（POSIX `clock_gettime` / Windows `QueryPerformanceCounter`、`GetSystemTimePreciseAsFileTime`），无堆分配。
- **墙钟统一实现**：墙钟只实现 `time_now_wall_ns_c`，sec/ms/us 在其上做整数除，避免四处重复 FILETIME/timespec 读取。
- **单调 us/ms/sec**：由 `time_now_monotonic_ns_c` 一次取纳秒再换算，符合「避免多次系统调用」。
- **duration_ns**：仅 `to_ns - from_ns`，链接时 `-flto` 可内联。
- **链接优化**：用户编译时使用 `-O2`/`-O3` 且默认链入的 cc 带 `-flto` 时，跨 TU 内联可进一步压榨调用开销。
- **Linux**：`clock_gettime` 常经 vDSO，内核态切换成本低，已为常见最快路径。

## 构建与链接

- 编译 time.o：`make -C compiler ../std/time/time.o`（或 `make -C compiler all`）。
- 用户 `import std.time` 且 `-o exe` 时，编译器自动链入 `std/time/time.o`。

## 测试

在仓库根目录执行：`./tests/run-time.sh`。
