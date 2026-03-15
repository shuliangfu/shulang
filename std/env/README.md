# std.env — 环境变量与临时目录

**模块路径**：`std/env/`（mod.su + env.c）  
**依赖**：core（extern C），无其它 .su 模块。  
**对标**：Zig 通过 std.process 等、Rust std::env。

## API 概览

| 函数 | 说明 |
|------|------|
| `getenv(key: *u8, key_len: i32, out: *u8, out_cap: i32): i32` | 取环境变量 key[0..key_len) 的值写入 out，NUL 结尾；返回写入字节数（不含 NUL），不存在/错误返回 -1。 |
| `getenv_ptr(key: *u8, key_len: i32, out_len: *i32): *u8` | **零拷贝**：返回 value 只读指针（NUL 结尾）或 0；可选 out_len 写入长度。指针在 setenv/unsetenv 或下次 getenv_ptr/getenv_z 前有效。 |
| `getenv_z(key_z: *u8, out_len: *i32): *u8` | **零拷贝（key+value）**：key_z 须 NUL 结尾，无 key 拷贝；返回 value 指针或 0。适合字面量如 `getenv_z("PATH", &len)`。 |
| `getenv_exists(key: *u8, key_len: i32): i32` | 判断 key 是否存在；1 存在，0 不存在。 |
| `setenv(name: *u8, value: *u8, overwrite: i32): i32` | 设置 name=value（NUL 结尾）；overwrite 非 0 覆盖。返回 0 成功，-1 失败。 |
| `unsetenv(name: *u8): i32` | 删除 name（NUL 结尾）。返回 0 成功，-1 失败。 |
| `temp_dir(out: *u8, cap: i32): i32` | 将临时目录路径写入 out（NUL 结尾）。返回写入字节数，失败 -1。TMPDIR/TEMP/TMP → /tmp。 |

## 与 std.process 的关系

- **当前工作目录**：建议继续使用 **std.process.getcwd** / getcwd_ptr，不在此重复实现。
- **getenv/setenv/unsetenv**：std.env 提供 **key 为 (ptr, len)** 的 getenv/getenv_exists，与 std.string/StrView 友好；setenv/unsetenv 与 std.process 语义一致（NUL 结尾 name/value），可任选其一使用。

## 实现说明

- key 支持 (ptr, len)，无需 NUL 结尾，适合切片/StrView。
- **零拷贝**：`getenv_ptr` / `getenv_z` 返回 C 运行时 getenv() 的 value 指针，无 value 拷贝；`getenv_z` 在 key 已 NUL 结尾时也无 key 拷贝。指针勿长期持有（setenv/unsetenv 会失效）。
- **零拷贝平台**：**Linux / macOS / Windows 均支持**。实现上统一使用各平台 C 运行时的 getenv()（Linux glibc、macOS libSystem、Windows MSVCRT/MinGW CRT），均返回指向环境块中 value 的指针，故三平台语义一致。
- POSIX：getenv/setenv/unsetenv；temp_dir 为 TMPDIR → TEMP → TMP → /tmp。
- Windows：拷贝路径用 GetEnvironmentVariableA / _putenv / GetTempPathA；零拷贝路径用 CRT getenv()。

## 性能（极致压榨）

- **getenv / getenv_exists**：key 栈缓冲 256 字节（POSIX 名长≤255），无堆分配；热路径仅 key 拷贝 + 系统 getenv + 必要时 value 拷贝。
- **setenv（Windows）**：name=value 拼接用 strlen + memcpy，避免逐字节循环。
- **temp_dir（POSIX）**：线程局部缓存首次结果，重复调用仅 memcpy，无额外 getenv。详见 `analysis/std_env性能分析与优化.md`。

## 功能完整性（P1 规格）

与 `analysis/std标准库全量清单与优先级.md` 3.3 一致：

- getenv(key, key_len, out, cap)、getenv_exists(key, key_len)
- setenv、unsetenv
- temp_dir（TMPDIR/TEMP/TMP + /tmp）

## 构建与测试

- 编译：`make -C compiler ../std/env/env.o`（或 `make -C compiler all`）。
- 用户 `import std.env` 且 `-o exe` 时自动链入 `std/env/env.o`。
- 测试：`./tests/run-env.sh`。
