# std.process — 进程控制、命令行参数、环境变量、工作目录、spawn/exec

本模块提供与 Rust std::process、Go os、Zig std.process 对齐的常用 API。实现分为：

- **mod.su**：对外 API
- **process.c**：平台实现（POSIX + Windows），链接用户程序时由编译器链入 **process.o**

---

## API 一览

### 进程终止

| API | 说明 |
|-----|------|
| `exit(code: i32)` | 终止当前进程，退出码 code（noreturn；由 codegen 生成 C exit()）。 |

### 命令行参数

| API | 说明 |
|-----|------|
| `args_count(): i32` | 返回 argc（含程序名）。 |
| `arg(i: i32): *u8` | 返回 argv[i]（NUL 结尾）；越界返回 0。 |

### 环境变量

| API | 说明 |
|-----|------|
| `getenv(name: *u8): *u8` | 查询环境变量；不存在返回 0。 |
| `setenv(name: *u8, value: *u8, overwrite: i32): i32` | 设置 name=value；overwrite≠0 时覆盖。返回 0 成功，-1 失败。 |
| `unsetenv(name: *u8): i32` | 删除环境变量。返回 0 成功，-1 失败。 |

### 进程 ID

| API | 说明 |
|-----|------|
| `getpid(): i32` | 当前进程 ID。 |
| `getppid(): i32` | 父进程 ID；Windows 返回 -1。 |

### 当前工作目录

| API | 说明 |
|-----|------|
| `getcwd(buf: *u8, buf_size: i32): i32` | 将当前目录写入 buf（NUL 结尾）。返回写入字节数（不含 NUL），失败 -1。 |
| `getcwd_ptr(): *u8` | **零拷贝**：返回指向内部缓存的只读指针（NUL 结尾）；失败 0。指针在下次 chdir/getcwd 前有效。 |
| `getcwd_cached_len(): i32` | 返回 getcwd 缓存长度（不含 NUL）；与 getcwd_ptr 配套使用。 |
| `chdir(path: *u8): i32` | 切换当前工作目录。返回 0 成功，-1 失败。 |

### 可执行路径

| API | 说明 |
|-----|------|
| `self_exe_path(buf: *u8, buf_size: i32): i32` | 将当前可执行文件路径写入 buf（NUL 结尾）。返回写入字节数，失败 -1。 |
| `self_exe_path_ptr(): *u8` | **零拷贝**：返回指向内部缓存的只读指针（NUL 结尾）；失败 0。指针在进程生命周期内有效。 |
| `self_exe_path_cached_len(): i32` | 返回 self_exe_path 缓存长度（不含 NUL）；与 self_exe_path_ptr 配套使用。 |

### 子进程与替换

| API | 说明 |
|-----|------|
| `spawn(program: *u8, argv: *u8): i32` | 创建子进程执行 program，参数 argv（C 侧 char**，以 NULL 结尾）。返回子进程 pid，失败 -1。 |
| `exec(program: *u8, argv: *u8): i32` | 用 program 替换当前进程（成功不返回）。Windows 不支持，返回 -1。 |

---

## 约定

- **入口 main**：仅入口模块的 `main` 由 codegen 生成 `int main(int argc, char **argv)` 并写入全局 argc/argv，`args_count()` / `arg(i)` 在此之后才有意义。
- **spawn/exec 的 argv**：在 C 侧为 `char **`（指针数组，以 NULL 结尾）。.su 侧传 `*u8` 表示该指针；调用方需自行在内存中构造 argv 数组（如 `[ptr0, ptr1, ..., 0]`）并传其首地址。
- **链接**：使用本模块时编译器会自动链入 process.o，无需用户指定。

---

## 测试（全量覆盖）

| 文件 | 覆盖 API |
|------|----------|
| main.su | exit(code) |
| args.su | args_count、arg、getenv |
| setenv_unsetenv.su | setenv、getenv、unsetenv |
| getpid.su | getpid |
| getppid.su | getppid |
| getcwd.su | getcwd |
| chdir.su | chdir、getcwd |
| self_exe_path.su | self_exe_path |
| spawn_wait.su | spawn_simple、waitpid |
| exec_fail.su | exec_simple 失败路径（不存在的程序返回 -1） |

运行：`./tests/run-process.sh`（spawn_wait 在 Windows 上无 /usr/bin/true 会 SKIP）

---

## 性能（压榨到极致）

- **热路径零成本**：args_count、arg、getenv、getpid、getppid 仅读全局或单次 syscall，零分配；用户以 **-O2/-O3 且 -flto** 链接时，编译器可跨 TU 内联，消除调用开销。
- **getcwd**：首次或 chdir 后走 syscall 并缓存；后续调用仅 memcpy，避免重复 getcwd/GetCurrentDirectory。chdir 时自动使缓存失效。
- **self_exe_path**：可执行路径在进程生命周期内不变，首次 syscall 后缓存，后续仅 memcpy，避免重复 readlink/GetModuleFileName 等。
- **零拷贝**：`getcwd_ptr()`、`self_exe_path_ptr()` 直接返回指向内部缓存的只读指针，无 memcpy；需长度时配合 `getcwd_cached_len()`、`self_exe_path_cached_len()`。getcwd 指针在下次 chdir/getcwd 前有效，self_exe_path 指针在进程生命周期内有效；调用方只读、勿写。
- 缓存拷贝统一用 memcpy，便于编译器优化；缓存区 4K，满足常见路径长度。
