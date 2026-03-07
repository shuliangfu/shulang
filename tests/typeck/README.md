# typeck 测试

- **合法用例**：由 `tests/run-lexer.sh` 覆盖（对 `tests/lexer/main.su` 运行 shuc，输出含 `parse OK` 与 `typeck OK` 即表示解析与类型检查均通过）。
- **非法用例**：当前语法子集下，Parser 仅接受 `fn main() -> i32 { <整数字面量> }`，故所有能解析的程序均能通过 Typeck。待语法扩展（如可选返回类型、多函数）后，再补充「能解析但类型错误」的 .su 用例与预期 stderr/退出码。
