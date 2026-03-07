# examples/ — 示例程序

**示例 .su 程序**，便于上手与回归测试。

- **用途**：用户参考「如何写 .su」；CI/本地测试时编译并运行，验证编译器与标准库。
- **内容**：例如：
  - Hello World
  - 使用 core / std 的简单示例
  - 嵌入式最小可运行示例（若支持 freestanding）
- **使用**：手动用 `shuc examples/hello.su` 编译，或由 `make test` 顺带覆盖。

建议 M1/M2 起就加少量示例，便于验证「能编译、能跑」。
