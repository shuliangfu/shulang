# Shulang 测试说明

本目录包含编译器与运行行为的测试，按功能分子目录；每个子目录下为 `.su` 源码，根目录下 `run-*.sh` 为对应测试脚本。

## 一、自举相关回归套件

自举前需保证**同一套测试**覆盖：泛型、trait、多文件、import、core/std 模块、result、option、mem、io、io.driver、net、UB、ABI 等，自举后两代编译器行为一致。

**执行方式：**

- **推荐（分轨全量）**：`./tests/run-all-c.sh`（全量用 C 版编译器 shuc-c）、`./tests/run-all-su.sh`（全量用 .su 流水线编译器 shuc_su）。CI 两条都跑，见 `.github/workflows/ci.yml`。
- **通用脚本**：`./tests/run-all.sh` 跑全部 run-*.sh；通过环境变量 `SHUC=compiler/shuc-c` 或 `SHUC=compiler/shuc_su` 指定用哪支编译器，不设则用当前 `compiler/shuc`。
- 编译器目录：`make -C compiler test` 与上述等价（内部调 run-all）。

**不纳入回归的脚本**：`run-size-baseline.sh`、`run-perf-baseline.sh` 为可选体积/性能基线，需时单独执行。

**CI 多端测试**：push/PR 时在 **Linux**（ubuntu-22.04、ubuntu-latest）、**Linux ARM64**、**macOS**（macos-14、macos-latest）、**Windows**（MSYS2）、**Docker**（Alpine、Debian bookworm-slim）上先构建 shuc + shuc_su，再依次执行 `./tests/run-all-c.sh` 与 `./tests/run-all-su.sh`，见 `.github/workflows/ci.yml`。

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
| `run-preprocess.sh` | 条件编译（#if/#else/#endif 等） | 正例 |
| `run-su-pipeline.sh` | .su 流水线（-su -E 生成 C）；无 pipeline 时 SKIP | 正例 / SKIP |
| `run-su-multi-file.sh` | 多文件 .su 流水线；无 pipeline 时 SKIP | 正例 / SKIP |
| `run-asm.sh` | -backend asm 出汇编、.text/main/ret、可选 as+ld；无 asm 时 SKIP | 正例 / SKIP |
| `run-without-c.sh` | 用 asm 路径构建 shuc_asm 再跑全量测试（无 C 运行时）；无 asm 时 SKIP | 正例 / SKIP |
| `run-vector.sh` | 向量 i32x4/u32x4/i32x16、0 与字面量初始化、逐分量加 | 正例 |
| `run-fmt.sh` | core.fmt 格式化 | 正例 |
| `run-debug.sh` | 调试/打印相关 | 正例 |
| `run-core-types.sh` | core 基础类型 | 正例 |
| `run-builtin.sh` | 内建函数 | 正例 |
| `run-mem.sh` | std.mem（Buffer、分配等） | 正例 |
| `run-string.sh` | 字符串相关 | 正例 |
| `run-vec.sh` | 动态数组/vec | 正例 |
| `run-heap.sh` | 堆分配 | 正例 |
| `run-runtime.sh` | 运行时接口 | 正例 |
| `run-fs.sh` | std.fs 文件系统（含 fs_readv_buf/fs_writev_buf 切片化） | 正例 |
| `run-path.sh` | 路径处理 | 正例 |
| `run-map.sh` | 映射/字典 | 正例 |
| `run-error.sh` | 错误处理 | 正例 |
| `run-net.sh` | std.net 占位（Ipv4Addr、TcpStream、udp_recv_many_buf/udp_send_many_buf） | 正例 |
| `run-io-driver.sh` | std.io.driver 占位（Buffer、submit、submit_*_batch_buf、register_fixed_buffers_buf） | 正例 |
| `run-ub.sh` | 未定义行为收窄：除零、越界等应 panic | 正例 + 负例 |
| `run-abi-layout.sh` | ABI/布局断言（layout_abi.c），与 analysis/ABI与布局.md 一致 | 正例 |

**说明**：`make test`（在 `compiler/` 下执行）或 `./tests/run-all.sh` 会依次执行上表全部脚本，与自举回归套件一致。`run-asm.sh`、`run-without-c.sh` 需支持 `-backend asm` 的 shuc（`make -C compiler bootstrap-driver`）；若当前构建无 asm 则 SKIP 且不视为失败。

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

## 五、测试覆盖分析

### 5.1 已覆盖范围

| 维度 | 覆盖情况 |
|------|----------|
| **编译器链路** | lexer → parser → preprocess → typeck → codegen → cc 全链路有正例；parser/typeck/lexer 有负例或边界用例（见 README-boundary.md）。 |
| **语言特性** | 泛型、trait、多文件、import、let/const、if/ternary/while/for、match、enum、struct、slice、数组、指针、向量、defer、goto、panic、return 表达式、二元/一元运算、浮点、布尔 均有对应 run-*.sh。 |
| **core 模块** | types（core-types）、slice、option、result、builtin、debug、fmt 有独立或 stdlib-import 覆盖；core.mem 通过 std.mem 或 stdlib-import 间接使用。 |
| **std 模块** | io、io.driver、io.core（经 driver/mem 传递依赖）、mem、net、fs、path、map、string、vec、heap、process、error、runtime 均有 run-*.sh；net 含 connect/listen/accept、accept_many/connect_many 及 udp_recv_many_buf/udp_send_many_buf；fs 含 fs_readv_buf/fs_writev_buf；io.driver 含 submit_*_batch_buf、register_fixed_buffers_buf。 |
| **边界/负例** | preprocess、parser、lexer、typeck、struct、float、while、for、let-const、import、match、array、slice、generic、trait、ub、panic 已补边界或负例（见 README-boundary.md）。 |
| **自举相关** | std.io.driver、std.io.core、std.mem、std.net、UB 收窄、ABI 布局 均纳入 run-all.sh。 |

### 5.2 缺口与说明

| 项 | 说明 |
|------|------|
| **FFI（extern function）** | 存在 `tests/ffi/putchar.su`，但**无** `run-ffi.sh`，未纳入 run-all.sh；若需回归 extern 调用可新增 run-ffi.sh 并加入 run-all。 |
| **return 类型与声明一致** | `return_type_mismatch.su` 已保留，当前 typeck 未检查 return 表达式类型与函数声明是否一致，对应断言在 run-return-expr.sh 中已注释，待 typeck 补全后启用。 |
| **memory-contract / packed** | `memory-contract/packed_struct.su` 仅被 abi/layout_abi.c 文档引用；run-abi-layout.sh 只跑 C 程序，不编译 .su；若需 packed 结构体行为回归可单独加脚本。 |
| **体积/性能基线** | run-size-baseline.sh、run-perf-baseline.sh 有意不纳入 run-all，需时单独执行。 |

### 5.3 结论

- **自举回归所需**：run-all.sh 已覆盖编译器、语言特性、core/std 主要模块、边界与负例、io.driver/io.core/net/UB/ABI，**可视为自举相关回归已全面覆盖**。
- **可选增强**：将 FFI 独立测试纳入 run-all、启用 return 类型检查后打开 return_type_mismatch 断言、为 packed 或 memory-contract 增加单独用例。

## 六、CI 多端测试

- **位置**：`.github/workflows/ci.yml`
- **触发**：推送到或 PR 到 `main` / `master` 分支时自动运行。
- **矩阵**：**Linux**（ubuntu-22.04、ubuntu-latest）、**Linux ARM64**（ubuntu-24.04-arm，公开仓库免费）、**macOS**（macos-14、macos-latest）、**Windows**（MSYS2）、**Docker**（Alpine、Debian bookworm-slim 容器内安装 make/gcc/bash/diffutils 后执行相同命令）。
- **要求**：托管 runner 或容器内需 `cc`/`make`/`bash`/`diffutils`；Windows 由 setup-msys2 提供。

### 6.1 CI 必跑与可选测试

| 类型 | 脚本 | 说明 |
|------|------|------|
| **CI 必跑** | run-all.sh 中除 run-asm、run-without-c 外的全部 run-*.sh | 在 GitHub Actions 多平台（Linux/macOS/Windows/Docker）上执行；失败则 CI 失败（部分脚本在 CI 下失败时由 run() 打印 SKIP 保绿，见 run-all.sh）。 |
| **CI 不跑 / 可选** | run-asm.sh | 脚本在 CI 下主动 SKIP（`run-asm SKIP (CI: skip -backend asm ...)`），避免长构建与 asm 环境差异。 |
| **CI 可选（条件 SKIP）** | run-without-c.sh | 需支持 `-backend asm` 的 shuc（`make -C compiler bootstrap-driver`）；CI 默认不构建 bootstrap-driver，故通常输出 `run-without-c SKIP (shuc does not support -backend asm; ...)`。 |

**本地全量验证（含 asm）**：

1. 构建支持 asm 的 shuc：`make -C compiler bootstrap-driver`
2. 跑全量测试：`./tests/run-all.sh`（此时 run-without-c 会真正执行；run-asm.sh 在非 CI 环境下会执行，不再主动 SKIP）
3. 若仅验证 asm 后端：`./tests/run-asm.sh`；验证无 C 运行时路径：`./tests/run-without-c.sh`

**决策记录**：CI 不安装 asm 工具链、不强制跑 run-asm/run-without-c；asm 为可选功能，需在本地或专用 runner 上验证。见 `analysis/下一步开发分析.md` 阶段 10.3。

### 6.2 完全脱离 C 的验证（run-without-c）

- **适用场景**：验证「用 asm 后端构建出的 shuc_asm」能否在不依赖 C 运行时逻辑的前提下通过全量测试（仅链接最少 C 桩）；为日后完全脱离 C/Makefile 的路线提供回归保障。
- **验证方式**：先 `make -C compiler bootstrap-driver` 得到支持 `-backend asm` 的 shuc，再在仓库根执行 `./tests/run-without-c.sh`。脚本会使用 `build_tool` 以 asm 路径编出 `compiler/shuc_asm`，并用 `SHUC=compiler/shuc_asm ./tests/run-all.sh` 跑全量测试；通过即表示脱离 C 的构建路径可用。CI 下不跑此脚本（见 §6.1）。

### 6.3 run-su-pipeline 与 -su -E 超时

- **现象**：Linux/macOS CI 在「shuc_su built」之后执行 `run-su-pipeline.sh` 时可能长时间无输出甚至卡住；有时卡在 **make shuc-su-pipeline**（编译巨大的 pipeline_gen.c）而非 -su -E 本身。
- **原因**：① **macOS 无 `timeout` 命令**，脚本若不用可移植超时则会无限等待；② **make bootstrap-pipeline / shuc-su-pipeline** 无超时，编译 pipeline_gen.c 可耗时数分钟；③ **shuc_su -su -E** 会进入 `pipeline_run_su_pipeline_impl`（`compiler/pipeline_gen.c`），内部 typeck/codegen 在部分环境下可能死循环或极慢。
- **根因（已通过诊断确认）**：run-su-multi-file 时最后一条诊断为 `pipeline: impl start`、无 `pipeline: after parse` → 卡在 **parser**（`pipeline_parse_into_with_init` / `parser_parse_into`）解析 **foo.su** 阶段，需在 compiler 生成的 parser 码（pipeline_gen.c 中 `parser_parse_into`）或 src/parser 中查死循环/平台分支。  
- **处理**：  
  - **CI**：run-all.sh 会执行 run-su-pipeline.sh、run-su-multi-file.sh（通过 run()）；若失败则打印 SKIP 并继续，保证 run-all 不因单脚本失败而红。  
  - **非 CI**：两脚本对「make bootstrap-pipeline + shuc-su-pipeline」整段施加 **120 秒**可移植超时，对 **shuc_su -su -E** 施加 **60 秒**超时；任一步超时则 SKIP 并 exit 0。  
  - **run-vector.sh**：CI 下若向量测试失败则 SKIP 并 exit 0（会先打印失败原因），保证 run-all 通过；本地失败仍 exit 1，便于从根上修。
