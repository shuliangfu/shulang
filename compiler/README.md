# compiler/ — 编译器实现

本目录为 **shulang 编译器** 的源码与构建入口。

- **阶段**：自举前用 **C** 实现（`src/*.c`、`include/*.h`），自举后逐步改为 **.su**（`src/*.su`）。
- **产出**：可执行文件 **shuc**（或 su），将 .su 源码编译为目标码/IR。
- **子目录**：
  - `src/` — 编译器源码（lexer、parser、ast、typeck、ir、codegen、driver）
  - `include/` — C 头文件（若用 C 实现时使用）
- **构建**：本目录内有 Makefile 或 CMakeLists.txt，顶层 `make` 会进入此处构建 shuc。

详见项目根目录下 `analysis/architecture.md` 第三章「编译器架构」。
