# std/ — 标准库 std（依赖 OS）

**标准库的 std 层**：依赖操作系统或运行时（进程、文件、网络等），在 core 之上提供统一 API。

- **用途**：用户通过 `import std.xxx` 引用；编译器解析到本目录下对应模块（如 `std/io.su`）。
- **内容**：按模块单文件或子目录，例如：
  - 运行时、进程、环境（runtime, process, env）
  - I/O、文件系统、路径（io, fs, path, dir）
  - 字符串、格式化、集合（string, fmt, vec, map）
  - 线程、同步、时间、网络、加密等
- **原则**：内部按目标平台条件编译，**用户只写一套 API**；按需链接，未用模块不进入二进制。嵌入式可用最小 std 子集或仅 core。

详见根目录 `analysis/README.md` 第五章「要实现的标准库」中 std 清单。

---

## 阶段 7 扩展清单（自举前必须的最小实现）

以下模块在阶段 6 已占位（空或注释）；阶段 7 需有**最小实现**或至少可 import 的声明，并与泛型/trait/多文件配合：

| 模块       | 内容概要 |
|------------|----------|
| std.runtime | 运行时初始化、panic 钩子等 |
| std.io     | Read/Write 最小接口、标准输入输出 |
| std.fs     | open/read/write/close、文件路径 |
| std.path   | 路径拼接、分解、规范化 |
| std.process | exit、args、环境变量 |
| std.heap   | 堆分配、Box 等 |
| std.string | 字符串类型与基本操作 |
| std.vec    | 动态数组 Vec |
| std.map    | 映射/字典 |
| std.error  | 错误类型与传播 |

另：std.fmt（格式化）、std.thread、std.mutex、std.time 等可在 7.4 后期或阶段 8 前补齐。实现顺序与 `compiler/docs/阶段7-泛型与trait设计.md` 一致。
