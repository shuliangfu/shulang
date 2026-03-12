# driver/ — 编译器驱动（文档与预留）

**入口已与 C 一一对应**：程序入口与驱动编排在 **src/main.su**（对应 main.c），不再使用 driver/driver.su。C 侧仅保留极简 main() 调 main_entry()；全部驱动与 I/O 在 **src/runtime.c**。

- **职责**：解析命令行、调 lexer→parser→typeck→codegen、多文件协调、调系统链接器。
- **.su 实现**：见 src/main.su（entry 生成 main_entry，与 main.c 的 main()→main_entry() 对应）。
- **构建**：默认 `make` 得到 shuc（main.o + runtime.o）；`make bootstrap-driver` 编 main.su + pipeline 得到 driver_su.o + pipeline_su.o，与 main.o + runtime_driver.o 链接为 shuc。
