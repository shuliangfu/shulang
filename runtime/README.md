# runtime/ — 最小运行时（可选）

**最小运行时**：与 std 解耦的极薄一层，用于启动、栈、panic、backtrace 等。

- **用途**：部分目标（尤其嵌入式）需要 crt0、栈初始化、或 panic 时采集 backtrace；若与 std.runtime / std.panic 强相关，也可将逻辑并入 `std/`，此处仅保留与平台强绑定的少量 C/汇编。
- **内容**：例如 startup/crt0、栈检查、可选 backtrace 采集；具体随实现取舍。
- **原则**：保持「小」；能放进 std 的尽量放 std，此处只放必须与编译器/链接脚本配合的底层片段。

详见 `analysis/architecture.md` 第二章与第六章。
