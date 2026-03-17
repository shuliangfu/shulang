# compiler/ — 编译器实现

本目录为 **shulang 编译器** 的源码与构建入口。

- **阶段**：自举前用 **C** 实现（`src/*.c`、`include/*.h`），自举后逐步改为 **.su**（`src/*.su`）。
- **产出**：可执行文件 **shu**（或 su），将 .su 源码编译为目标码/IR。
- **子目录**：
  - `src/` — 编译器源码（lexer、parser、ast、typeck、ir、codegen、driver）
  - `include/` — C 头文件（若用 C 实现时使用）

### 构建（与根目录 README 一致）

| 场景 | 命令 |
|------|------|
| **首次 / 从零** | `make build-tool` 或 `make first-time`（会先产出 shu 再产出 build_tool，一条命令）。 |
| **日常与自举** | `./build_tool ./shu`（本目录下执行，产出 shu，不依赖 Makefile）。 |

Makefile 仅作从零构建/首次；日常推荐仅用 `./build_tool ./shu`。生成 C（pipeline_gen.c / driver_gen.c）后无补丁，由 runtime/codegen 从根源产出。验收：仓库根执行 `./tests/run-all.sh`。

详见项目根目录下 `analysis/architecture.md` 第三章「编译器架构」。
