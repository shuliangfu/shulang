# Shulang 测试说明

本目录包含编译器与运行行为的测试，按功能分子目录；每个子目录下为 `.su` 源码，根目录下 `run-*.sh` 为对应测试脚本。

## 一、自举相关回归套件

自举前需保证**同一套测试**覆盖：泛型、trait、多文件、import、core/std 模块、result、option、mem、io、io.driver、net、UB、ABI 等，自举后两代编译器行为一致。

**执行方式（二者等价、全量一致）：**

- 仓库根目录：`./tests/run-all.sh`
- 编译器目录：`make -C compiler test`

**不纳入回归的脚本**：`run-size-baseline.sh`、`run-perf-baseline.sh` 为可选体积/性能基线，需时单独执行。

## 二、测试脚本与覆盖范围

| 脚本 | 覆盖内容 | 用例类型 |
|------|----------|----------|
| `run-lexer.sh` | 词法：Token 序列与 expected.txt 逐行比对 | 正例 |
| `run-typeck.sh` | 类型检查：输出含 `typeck OK` | 正例 |
| `run-hello.sh` | 编译运行 examples/hello.su，输出 "Hello World" | 正例 |
| `run-import.sh` | import 与多文件，输出 "Hello World" | 正例 |
| `run-std.sh` | 标准库路径 -L .，parse/typeck OK 并运行 | 正例 |
| `run-stdlib-import.sh` | 标准库 import（core/std 模块） | 正例 |
| `run-target.sh` | -target 交叉编译（若支持） | 正例 |
| `run-return-value.sh` | main 最后一表达式作为返回值 | 正例 |
| `run-multi-func.sh` | 多函数、调用 | 正例 |
| `run-generic.sh` | 泛型函数/类型、单态化 | 正例 |
| `run-trait.sh` | trait 定义与实现 | 正例 |
| `run-multi-file.sh` | 多文件编译与链接 | 正例 |
| `run-multi-file-generic.sh` | 多文件 + 泛型 | 正例 |
| `run-binary-expr.sh` | 二元运算：加减乘除取模、移位、位运算、比较、逻辑等 | 正例 |
| `run-let-const.sh` | let/const 声明与常量表达式 | 正例 |
| `run-bool.sh` | 布尔类型与 true/false | 正例 |
| `run-if-expr.sh` | if/else、else if、无 else | 正例 |
| `run-ternary.sh` | 三元表达式 | 正例 |
| `run-option.sh` | core.option Option&lt;T&gt; | 正例 |
| `run-result.sh` | core.result Result&lt;T,E&gt; | 正例 |
| `run-process.sh` | 进程/退出码相关 | 正例 |
| `run-io.sh` | std.io 读写等 | 正例 |
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
| `run-fmt.sh` | core.fmt 格式化 | 正例 |
| `run-debug.sh` | 调试/打印相关 | 正例 |
| `run-core-types.sh` | core 基础类型 | 正例 |
| `run-builtin.sh` | 内建函数 | 正例 |
| `run-mem.sh` | std.mem（Buffer、分配等） | 正例 |
| `run-string.sh` | 字符串相关 | 正例 |
| `run-vec.sh` | 动态数组/vec | 正例 |
| `run-heap.sh` | 堆分配 | 正例 |
| `run-runtime.sh` | 运行时接口 | 正例 |
| `run-fs.sh` | std.fs 文件系统 | 正例 |
| `run-path.sh` | 路径处理 | 正例 |
| `run-map.sh` | 映射/字典 | 正例 |
| `run-error.sh` | 错误处理 | 正例 |
| `run-net.sh` | std.net 占位（Ipv4Addr、TcpStream 等） | 正例 |
| `run-io-driver.sh` | std.io.driver 占位（Buffer、submit 等） | 正例 |
| `run-ub.sh` | 未定义行为收窄：除零、越界等应 panic | 正例 + 负例 |
| `run-abi-layout.sh` | ABI/布局断言（layout_abi.c），与 analysis/ABI与布局.md 一致 | 正例 |

**说明**：`make test`（在 `compiler/` 下执行）或 `./tests/run-all.sh` 会依次执行上表全部脚本，与自举回归套件一致。

## 三、边界与负向测试

- **浮点**：`run-float.sh` — 边界 0.0、.25、const 1e2；负例 `let x: f32 = 1` 报 typeck 错误。
- **循环**：`run-while.sh` — break 在循环外报 typeck 错误。
- **结构体**：`run-struct.sh` — `padding_no_allow.su` 未 allow(padding) 时报 typeck 隐式 padding 错误。
- **解析**：`run-parser.sh` — return 后缺分号报 parse error。
- **UB**：`run-ub.sh` — 除零、数组/切片越界应 panic（exit 134），正常路径正常返回。

## 四、一键运行全部测试

在仓库根目录执行：

```bash
./tests/run-all.sh
```

或在 `compiler/` 目录下执行：

```bash
make test
```

两者都会跑完自举相关回归套件中全部 `run-*.sh`，并输出各脚本的 OK 或失败信息。
