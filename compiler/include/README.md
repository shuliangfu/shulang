# compiler/include/ — C 头文件

当编译器用 **C** 实现时，本目录存放 **.h 头文件**。

- **用途**：声明 lexer、parser、ast、typeck、ir、codegen、driver 等模块的对外接口，供 `src/` 下 .c 文件包含。
- **自举后**：若编译器全部改为 .su，本目录可废弃或仅保留与 C 互操作相关的少量头文件。

若使用 C++，也可将 .h 放在此处或与 src 按模块分目录对应。
