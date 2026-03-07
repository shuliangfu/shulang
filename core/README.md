# core/ — 标准库 core（无 OS 依赖）

**标准库的 core 层**：不依赖操作系统，可在裸机、内核、嵌入式环境使用。

- **用途**：用户通过 `import core.xxx` 引用；编译器解析到本目录下对应模块（如 `core/types.su`）。
- **内容**：按模块单文件或子目录，例如：
  - 基础类型（types, mem, alloc, atomic）
  - 可选/错误（option, result）、比较（cmp）、格式化核心（fmt）
  - 切片与数组（slice, array）、迭代器（iterator）、字符串视图（str）
  - 哈希、调试、内建等
- **原则**：不依赖 libc/OS；按需链接，用不到的模块不进入最终二进制。嵌入式目标仅链接 core（及可选最小 std）。

详见根目录 `analysis/README.md` 第五章「要实现的标准库」中 core 清单。

---

## 阶段 7 扩展清单（自举前必须的最小实现）

以下模块在阶段 5–6 已占位或待实现；阶段 7 需有**类型与函数声明 + 最小实现**，供编译器与用户程序 import：

| 模块        | 内容概要 |
|-------------|----------|
| core.types  | 基础类型别名、size_of/align_of 等 |
| core.mem    | 内存操作、copy/move、对齐 |
| core.option | Option<T> 与 可空语义 |
| core.result | Result<T,E> 与错误传播 |
| core.slice  | 切片类型与边界安全访问 |
| core.fmt    | 格式化核心（与 std.fmt 对接） |
| core.builtin | 内建函数/ intrinsics |
| core.debug  | assert、debug 打印等 |

实现顺序与 `compiler/docs/阶段7-泛型与trait设计.md` 一致；泛型/trait 就绪后可实现 Option/Result/Vec 等泛型类型。
