# Shulang 测试说明

本目录包含编译器与运行行为的测试，按功能分子目录；每个子目录下为 `.su` 源码，根目录下 `run-*.sh` 为对应测试脚本。

## 一、测试脚本与覆盖范围

| 脚本 | 覆盖内容 | 用例类型 |
|------|----------|----------|
| `run-lexer.sh` | 词法：Token 序列与 expected.txt 逐行比对 | 正例 |
| `run-typeck.sh` | 类型检查：输出含 `typeck OK` | 正例 |
| `run-hello.sh` | 编译运行 examples/hello.su，输出 "Hello World" | 正例 |
| `run-import.sh` | import 与多文件，输出 "Hello World" | 正例 |
| `run-std.sh` | 标准库路径 -L .，parse/typeck OK 并运行 | 正例 |
| `run-target.sh` | -target 交叉编译（若支持） | 正例 |
| `run-return-value.sh` | main 最后一表达式作为返回值 | 正例 |
| `run-binary-expr.sh` | 二元运算：加减乘除取模、移位、位运算、比较、逻辑等 | 正例 |
| `run-let-const.sh` | let/const 声明与常量表达式 | 正例 |
| `run-bool.sh` | 布尔类型与 true/false | 正例 |
| `run-if-expr.sh` | if/else、else if、无 else | 正例 |
| `run-while.sh` | while/loop、break/continue；**负例**：break 在循环外报错 | 正例 + 负例 |
| `run-return-expr.sh` | 显式 return 表达式 | 正例 |
| `run-for.sh` | for 循环 | 正例 |
| `run-float.sh` | f32/f64、浮点字面量、科学计数法、.5、边界与负例 | 正例 + 边界 + 负例 |
| `run-parser.sh` | 解析负例：return 后缺分号报 parse error | 负例 |
| `run-struct.sh` | 结构体定义、字面量、字段访问、allow(padding)；未 allow 隐式 padding 报错 | 正例 + 负例 |
| `run-slice.sh` | 切片 []T、从数组初始化、下标 | 正例 |
| `run-array.sh` | 固定长数组 [N]T、初值 0、字面量、下标 | 正例 |
| `run-pointer.sh` | 裸指针 *T、0 初始化 | 正例 |
| `run-enum.sh` | 无负载枚举、Name.Variant、match 枚举分支 | 正例 |
| `run-match.sh` | match 表达式（整型分支与 _） | 正例 |
| `run-panic.sh` | panic() / panic(expr)，编译通过且运行非 0 退出 | 正例 |
| `run-defer.sh` | defer 块与块尾返回值 | 正例 |
| `run-goto.sh` | label 与 goto、return | 正例 |
| `run-vector.sh` | 向量 i32x4/u32x4、0 与字面量初始化、逐分量加 | 正例 |

**说明**：`make test`（在 `compiler/` 下执行）或 `./tests/run-all.sh` 会依次执行上表全部脚本。

## 二、边界与负向测试

- **浮点**：`run-float.sh` — 边界 0.0、.25、const 1e2；负例 `let x: f32 = 1` 报 typeck 错误。
- **循环**：`run-while.sh` — break 在循环外报 typeck 错误。
- **结构体**：`run-struct.sh` — `padding_no_allow.su` 未 allow(padding) 时报 typeck 隐式 padding 错误。
- **解析**：`run-parser.sh` — return 后缺分号报 parse error。

## 三、一键运行全部测试

在仓库根目录执行：

```bash
./tests/run-all.sh
```

或在 `compiler/` 目录下执行：

```bash
make test
```

两者都会跑完上表所列全部 `run-*.sh`，并输出各脚本的 OK 或失败信息。
