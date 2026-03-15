# std.random — 密码学安全随机数（CSPRNG）

**模块路径**：`std/random/`（mod.su + random.c）  
**依赖**：core（extern C），无其它 .su 模块。  
**对标**：Zig std.crypto / getentropy、Rust getrandom / rand::rngs::OsRng。

## API 概览

| 函数 | 说明 |
|------|------|
| `fill_bytes(buf: *u8, len: i32): i32` | 用密码学安全随机字节填满 buf[0..len)；返回写入长度（成功为 len），失败为负值。 |
| `u32(): u32` | 生成一个密码学安全的随机 u32。 |
| `u64(): u64` | 生成一个密码学安全的随机 u64。 |
| `range_u32(lo: u32, hi: u32): u32` | 生成 [lo, hi] 闭区间内均匀分布的 u32（含两端）；拒绝采样法避免 bias。 |
| `bool(): i32` | 生成均匀随机布尔，返回 0 或 1。 |

## 与 Zig / Rust 对标

| 我们的 API | Zig 对应 | Rust 对应 |
|------------|----------|-----------|
| `fill_bytes(buf, len)` | `std.crypto.random.bytes(buf)` | `OsRng::fill_bytes(&mut [u8])` / getrandom crate |
| `u32()` / `u64()` | `std.crypto.random.int(u32)` 等 | `OsRng::next_u32()` / `next_u64()` |
| `range_u32(lo, hi)` | `intRangeAtMost(R, T, at_most)`（或 uintLessThan 派生） | `gen_range(lo..=hi)`（闭区间） |
| `bool()` | `std.Random.boolean()` | `gen_bool(p)`（p=0.5 时等价） |

语义对齐：字节填充一次填满、u32/u64 按平台字节序；有界整数为**闭区间 [lo, hi]**，与 Rust `gen_range(..=)` 一致；布尔为均匀 0/1。

## 实现说明

- **CSPRNG 仅**：仅提供操作系统提供的密码学安全随机源，不引入 PRNG 引擎（如 xorshift、PCG 等可放 P2/P3）。
- **平台**：
  - Linux：`getrandom(buf, len, 0)`，不足时循环直至填满或错误。
  - macOS / *BSD：`getentropy(buf, len)`，单次最多 256 字节，大 buf 内部分段调用。
  - Windows：`BCryptGenRandom`（bcrypt.dll），链接时需 `-lbcrypt`（或 MSVC 下 #pragma comment(lib, "bcrypt.lib")）。
- **u32/u64**：内部 fill 4/8 字节后按本机字节序解释；小调用延迟可接受。
- **range_u32**：拒绝采样法，保证 [lo, hi] 上均匀、无 bias；若 lo > hi 返回 lo。

## 功能完整性（P1 规格）

与 `analysis/std标准库全量清单与优先级.md` 3.2 一致，已全部实现：

- 密码学安全随机字节：`fill_bytes(buf, len)`（一次/多次系统调用填满）
- 密码学安全 u32/u64：`u32()`、`u64()`
- 有界整数 [lo, hi]：`range_u32(lo, hi)`
- 布尔：`bool()`（0/1）

## 性能

- **fill_bytes**：大块（如 1MB）吞吐目标 ≥ Zig/Rust 的 OsRng/getentropy；一次或多次系统调用填满，避免逐字节。
- **u32/u64**：单次 fill 4/8 字节，延迟可接受。
- **Windows 优化**：BCrypt 算法句柄进程内仅初始化一次（`InitOnceExecuteOnce`），后续 `fill_bytes`/`u32`/`u64` 仅调用 `BCryptGenRandom`，避免每次 Open/Close 带来的开销，显著降低小调用延迟。

## 构建与链接

- 编译 random.o：`make -C compiler ../std/random/random.o`（或 `make -C compiler all`）。
- 用户 `import std.random` 且 `-o exe` 时，编译器自动链入 `std/random/random.o`；Windows 下会传 `-lbcrypt`。

## 测试

在仓库根目录执行：`./tests/run-random.sh`。
