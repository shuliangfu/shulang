# compiler/src/ — 编译器源码

本目录为编译器的**所有源码**所在位置。

- **入口**：`main.c`（C 实现）或 `main.su`（自举后）。
- **按阶段划分的子目录**（与编译流水线对应）：
  - `lexer/` — 词法分析，.su 源码 → Token 流
  - `parser/` — 语法分析，Token 流 → AST
  - `ast/` — AST 定义与遍历
  - `typeck/` — 类型检查、泛型单态化
  - `ir/` — 中间表示（自定义 IR 或 LLVM IR 生成）
  - `codegen/` — 代码生成，IR → 目标码（.o / 可执行文件）
  - `driver/` — 驱动：命令行解析、多文件、调用链接器等

先实现 lexer → parser → ast，再 typeck → ir → codegen，最后用 driver 串起来。详见 `analysis/architecture.md` 三、编译器架构。
