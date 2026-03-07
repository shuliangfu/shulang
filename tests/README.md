# tests/ — 测试用例与测试脚本

**编译器与标准库的测试**。

- **用途**：回归测试、CI；用当前 shuc 编译指定 .su 并运行，对比预期输出。
- **内容**：
  - 用例：.su 源文件或子目录（如 `tests/unit/`、`tests/integration/` 等，按需建）
  - 脚本：如 `run-tests.sh`，驱动「编译 → 运行 → 比对」
- **使用**：顶层 `make test` 会进入本目录或调用此处脚本执行测试。

测试多了可将单元测试与集成测试分子目录；见 `analysis/architecture.md` 2.1 节。
