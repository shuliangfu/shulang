# Shulang 开发时序文档

> 本文档说明**先开发什么、再开发什么**，按**依赖关系**排序，避免出现「下一步依赖尚未就绪」的情况。与 `architecture.md`、项目里程碑（M0–M5）对应，此处细化到可执行的开发顺序。

---

## 构建方式（唯一推荐）

**构建配置入口 = build.su**（与 Zig 的 **build.zig** 一致：用项目语言描述「怎么编、编什么」；根目录 Makefile 仅做委托，**可由 build.su 完全替代**）。

### 读者一次做对

| 场景 | 命令 | 说明 |
|------|------|------|
| **首次 / 从零构建** | `make -C compiler build-tool` | 一条命令：先产出 **shuc**（依赖），再产出 **build_tool**。等价目标 `first-time`。 |
| **日常与自举** | `cd compiler && ./build_tool ./shuc` | 用 build_tool 重新产出 shuc，不依赖 Makefile。 |
| **验收** | `./tests/run-all.sh` | 在仓库根执行；全过即自举验证等价通过。 |

- 仅需 shuc 跑测试时可直接 `make -C compiler`；首次建议 `make -C compiler build-tool` 以便日后用 `./build_tool ./shuc`。CI 与本地回归均可用 `make -C compiler test` 或 `./tests/run-all.sh`。
- 详见 `analysis/完全脱离C与Makefile路线图.md` 阶段 5；无 C/无 Makefile 时用 build.su 作唯一入口见 `analysis/完全自举-无C无Makefile.md`。

---

## 当前进度小结（便于快速对照）

| 阶段 | 状态 | 说明 |
|------|------|------|
| 0–6 | ✅ 已完成 | 流水线、import、core/std 最小子集、多目标已打通 |
| 7 | ✅ 已完成 | 泛型、trait/impl、多文件、core/std 扩展（最小实现） |
| 8 | 部分完成 | 8.1 DCE ✅；8.2 后端 -O2/-Os、strip、NDEBUG、shuc OPT=1 ✅；8.3 体积/性能基线脚本 ✅ |
| 9 | ✅ 已完成 | 自举（typeck/codegen/driver 由 .su 实现；验收：`cd compiler && ./build_tool ./shuc` 后 `./tests/run-all.sh`，或 `make -C compiler bootstrap-verify` 兜底） |
| 10 | 规划中 | 见 **`analysis/下一步开发分析.md`**：修 -su -E 多文件、pipeline 在 CI 可跑、asm 策略、脱离 C/Makefile。 |

---

## 一、依赖关系总览

### 1.1 编译器流水线依赖（谁依赖谁）

```
                    ┌─────────┐
                    │  AST    │  仅数据结构，无上游
                    └────┬────┘
                         │
  ┌─────────┐      ┌─────▼─────┐
  │ Lexer   │─────►│  Parser   │  依赖 Lexer + AST
  └─────────┘      └─────┬─────┘
                          │
                    ┌─────▼─────┐
                    │  Typeck   │  依赖 Parser 产出的 AST
                    └─────┬─────┘
                          │
  ┌─────────┐        ┌────▼────┐
  │  IR     │◄───────│ (可选)  │  IR 结构可先定义；生成 IR 依赖 Typeck
  └────┬────┘        └─────────┘
       │
  ┌────▼─────┐
  │ Codegen  │  依赖 IR（或直接依赖带类型 AST）
  └────┬─────┘
       │
  ┌────▼─────┐
  │  Driver  │  依赖上述全部，只做串联与调用链接器
  └──────────┘
```

- **结论**：开发顺序必须满足 **AST → Lexer → Parser → Typeck → IR/Codegen → Driver**；其中 AST 与 Lexer 无编译器内部依赖，可最先做。

### 1.2 标准库与编译器的依赖

- **编译器**在「编译用户程序」时需要能**解析 import** 并**编译 core/std 模块**，因此：
  - 先有「能生成可运行程序」的流水线（至少到 Codegen + Driver），再谈「用户程序 import core/std」；
  - 第一版可运行程序（如 Hello World）可以**不 import**，由 codegen 直接生成调用 libc printf 的 C 或 LLVM IR，这样**不依赖任何 .su 标准库**；
  - 之后再实现 **import 解析** 与 **core/std 的编译与链接**，此时才需要先实现「自举前必须」的 core/std 子集。

- **标准库自身**：core 不依赖 std；std 依赖 core。因此开发顺序为 **先 core 子集，再 std 子集**。当前 **core/** 与 **std/** 采用「目录即模块」布局：每模块对应一目录，入口为 `mod.su`（如 `core/result/mod.su`、`std/io/mod.su`），便于按目录拆分与扩展代码。

### 1.3 与里程碑的对应

| 里程碑 | 开发时序中的阶段 |
|--------|------------------|
| M0     | 阶段 1–2（Lexer、AST、Parser） |
| M1     | 阶段 3–4（Typeck、IR、Codegen、Driver，首版可运行） |
| M2     | 阶段 5–6（最小 core/std、import、多目标） |
| M3     | 阶段 7（泛型、trait、模块系统、标准库扩展） |
| M4     | 阶段 8（优化、体积与性能） |
| M5     | 阶段 9（自举） |

---

## 二、开发阶段与顺序（按依赖严格排序）

以下各阶段**必须按顺序**进行（或同一阶段内可并行的小项一起做）；每阶段末尾给出「完成标志」与「下一步前置条件」。

---

### 阶段 0：基础设施（无编译器依赖）

**目标**：构建与仓库可工作，无「写代码」依赖。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 0.1 | 顶层 Makefile（至少能进 compiler 并执行空构建或占位目标） | 无 | `make` 不报错 | ✅ |
| 0.2 | compiler 目录下 Makefile 或 CMake，能编译单个 .c 占位（如 main 空实现） | 无 | 产出可执行文件 shuc（哪怕只做 return 0） | ✅ |
| 0.3 | 确定「阶段 1–2 要支持的 .su 语法子集」（如：仅整数字面量、加减、main 无参返回 int） | 无 | 文档或注释写清子集 | ✅ |

**下一步前置**：执行 `make` 得到 shuc；有明确的最小语法子集。

---

### 阶段 1：AST 定义 + Lexer

**目标**：有 AST 数据结构；能从 .su 源码得到 Token 流。**不依赖** Parser/Typeck/后端。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 1.1 | **AST 节点定义**（compiler/src/ast/）：表达式、语句、函数、模块等，与阶段 0 确定的语法子集一致；仅数据结构，不依赖 Lexer/Parser | 无 | 可编译的 AST 类型（C 的 struct 或 .su 的 type） | ✅ |
| 1.2 | **Lexer**（compiler/src/lexer/）：读入源码，产出 Token 流（关键字、标识符、字面量、运算符、括号等） | 无 | 对给定 .su 文件输出 Token 序列（可打印或写测试断言） | ✅ |
| 1.3 | **单元测试**：若干 .su 片段只做词法，检查 Token 序列符合预期 | Lexer | tests/ 下用例通过 | ✅ |

**下一步前置**：AST 类型已定；Lexer 对子集语法能稳定输出 Token；有测试可回归。

---

### 阶段 2：Parser（语法分析）

**目标**：Token 流 → AST。**依赖** Lexer + AST。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 2.1 | **Parser**（compiler/src/parser/）：递归下降（或等价）将 Token 流解析为 AST；覆盖阶段 0 的语法子集 | Lexer, AST | 对「合法子集」源码得到一棵 AST | ✅ |
| 2.2 | **错误恢复**（可选最小）：未匹配括号、缺少分号等报错并带位置 | Parser | 错误信息含行号/列号 | ✅ |
| 2.3 | **测试**：多组 .su 源码 → 解析 → 对比 AST 或解析结果（dump AST 或与预期结构比对） | Parser | tests/ 中解析用例通过 | ✅ |

**下一步前置**：对子集内任意合法 .su 能产出正确 AST；非法输入能报错不崩溃。

---

### 阶段 3：最小 Typeck + IR 设计

**目标**：能对 AST 做**最小类型检查**并得到可被后端使用的信息；定义 **IR** 结构（或约定「直接由带类型 AST 生成代码」）。**依赖** Parser 产出之 AST。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 3.1 | **IR 数据结构设计**（compiler/src/ir/）：若采用「先生成 C」则 IR 可极简（如线性指令或树形 C 片段）；若采用 LLVM 则定义到 LLVM IR 的映射；仅定义与构建，不要求优化 | 无（与 Typeck 可并行设计） | 文档或代码中 IR 形态确定 | ✅ |
| 3.2 | **最小 Typeck**（compiler/src/typeck/）：对子集做类型推断/检查（如 main 返回 int、表达式有类型、函数调用参数个数与类型匹配）；产出「带类型 AST」或直接产出 IR | Parser, AST | 合法程序通过，非法程序报类型错误 | ✅ |
| 3.3 | **测试**：仅类型检查的用例（合法/非法） | Typeck | 类型错误用例被正确拒绝 | ✅ |

**下一步前置**：对子集程序能给出类型信息或 IR；类型错误能报出且不崩溃。

---

### 阶段 4：Codegen + Driver（首版可运行）

**目标**：从「带类型 AST 或 IR」生成**可运行程序**；**Driver** 串联 Lexer → Parser → Typeck → Codegen，并调用系统编译器/链接器。本阶段**不要求**用户 .su 里 import core/std，可生成「直接调 libc」的 C 或 LLVM IR，以最小化依赖。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 4.1 | **Codegen**（compiler/src/codegen/）：  
  - 方案 A：带类型 AST / IR → **C 代码**（如 main 里调 printf），再调用系统 cc 编译 C；  
  - 方案 B：→ **LLVM IR**，再调用 clang/llc 或 LLVM API 生成 .o 并链接。  
  任选其一，先打通一条路 | Typeck, IR 或带类型 AST | 对「仅 main + 一两个表达式」的 .su 能产出 C 或 LLVM IR | ✅ |
| 4.2 | **Driver**（compiler/src/driver/）：命令行解析（如 `shuc file.su -o out`）；按序调用 lexer→parser→typeck→codegen；若 codegen 出 C，则调用系统 C 编译器；若出 .o，则调用链接器；输出可执行文件 | Lexer, Parser, Typeck, Codegen | `shuc hello.su -o hello && ./hello` 能运行 | ✅ |
| 4.3 | **Hello World**：编写 examples/hello.su（子集内，如 main 里调内置 print 或等价），编译并运行输出 "Hello World" | 上述全部 | Hello World 通过 | ✅ |

**下一步前置**：存在一条从 .su 到可执行文件的完整链路；无 import、无标准库依赖。

---

### 阶段 5：import 与最小 core（无 OS）

**目标**：编译器支持 **import core.xxx**；实现 **core** 的最小子集（types、mem、option、result、slice、fmt 等自举前必须的一部分），使「用户程序或后续编译器」能引用 core。**依赖** 阶段 4 的完整链路。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 5.1 | **Import 解析**：driver 解析 `import core.xxx` / `import std.xxx`，根据标准库根路径找模块：先试单文件 `core/xxx.su`，若无则试目录模块 `core/xxx/mod.su`（std 同理）；对该文件做 lex→parse→typeck，纳入同一编译单元 | Driver, 标准库路径配置 | 能编译含 `import core.types` 的 .su（若 types 已实现） | ✅ 已完成 |
| 5.2 | **core 最小子集**（**目录即模块**：每模块一目录，入口为 `mod.su`，如 `core/result/mod.su`）：core.types、core.mem、core.option、core.result、core.slice、core.fmt、core.builtin、core.debug；可先做「仅类型与函数声明 + 少量实现」，保证编译器能解析、类型检查通过 | 无（标准库与编译器可并行开发，但需 import 先通） | 至少 core.types + core.mem 可被 import 且通过 typeck | ✅ 已完成 |
| 5.3 | **测试**：examples 或 tests 中「import core.xxx 并调用」的用例能编译通过 | Import + core 子集 | 用例通过 | ✅ 已完成 |

**下一步前置**：用户 .su 可 import core 的若干模块；编译器能解析并类型检查多文件/多模块。

---

### 阶段 6：最小 std + 多目标（可选顺序微调）

**目标**：实现 **std** 的最小子集（runtime、io、fs、path、process、env、heap、string、vec、map、error）；支持**多目标**（如 x86_64-linux、arm64-macos）。**依赖** import 与 core 可用；codegen/driver 能生成并链接多模块。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 6.1 | **std 最小子集**（**目录即模块**：每模块一目录，入口为 `mod.su`，如 `std/io/mod.su`，同目录可放 `driver.su` 等拆分文件）：std.runtime、std.io、std.fs、std.path、std.process、std.heap、std.string、std.vec、std.map、std.error；实现可先「单平台」（当前 OS），内部条件编译留好接口 | core 可用, import | 能编译「import std.io; 打开文件读一行」之类用例 | ✅ 已完成 |
| 6.2 | **多目标**：driver 支持 `-target`（如 x86_64-pc-linux-gnu）；codegen 与链接根据 target 选工具链与库；标准库内按 target 条件编译 | Codegen, Driver | 同一 .su 可编译出 linux/macos 可执行文件（或至少两个目标之一） | ✅ 已完成 |
| 6.3 | **测试**：多目标各编一例并运行（或交叉编译后交目标机运行） | 6.1, 6.2 | 多目标用例通过 | ✅ 已完成 |

**下一步前置**：用户程序可 import std 并做简单 I/O、文件、进程；可针对不同目标编译。

---

### 阶段 7：泛型、trait、模块系统与标准库扩展

**目标**：语言上支持**泛型**与 **trait/接口**；**模块系统**完善（多文件、可见性）；标准库扩展到 M3 水平（core 其余、std.string/fmt/vec/map/thread/mutex/time/heap/error/test）。**依赖** 阶段 5–6；Typeck 需扩展以支持泛型与 trait。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 7.1 | **泛型**：typeck 支持泛型函数/结构体与单态化；IR/codegen 能正确生成单态化后的代码 | Typeck, IR, Codegen | 泛型 .su 程序能编译并运行 | ✅ |
| 7.2 | **Trait/接口**：类型系统支持 trait 与 impl；满足「自举前必须」的语法需求 | Typeck | 带 trait 的 .su 能通过 typeck 并编译 | ✅ |
| 7.3 | **模块系统**：多文件、export/import、可见性规则；与现有 import core/std 一致 | Driver, Parser, Typeck | 多文件项目能正确编译与链接 | ✅ |
| 7.4 | **标准库扩展**：core 其余模块；std 的 string、fmt、vec、map、thread、mutex、time、heap、error、test 等 | 7.1–7.3 | 文档「自举前必须的库」全部可 import 并有最小实现 | ✅ |

**下一步前置**：语言子集达到「可写编译器」所需；标准库达到自举前必须集合。

---

### 阶段 8：优化与体积/性能（M4）

**目标**：内联、DCE、LTO、strip；可执行文件小、性能达标。**依赖** 阶段 7；中端/后端需有优化 pass 或交给系统 cc 优化。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 8.1 | **死代码消除（DCE）**：未使用函数、未实例化泛型不进入目标码；未引用模块中的代码不进入二进制 | IR 或 Codegen | 从 main 做可达性分析，codegen 按 used 集合仅输出被引用函数与单态化实例 | ✅ |
| 8.2 | **后端优化与 strip**：invoke_cc 默认 -O2，支持 -O 0/2/s、SHULANG_OPT；非 -O0 时 strip 产出并传 -DNDEBUG；Makefile 支持 OPT=1 编译 shuc | Codegen, Driver, Makefile | 用户产物可 -O2/-Os；体积可测 | ✅ |
| 8.3 | **体积与性能基线**：run-size-baseline.sh（-O0/-O2/-Os 对比）、run-perf-baseline.sh；make size-baseline / perf-baseline | 8.2 | 有体积与耗时数字可对比 | ✅ |

**下一步前置**：发布构建稳定；体积与性能满足「轻量级、比肩 C」目标。

---

### 阶段 9：自举（M5）

**目标**：用 **.su** 重写编译器（前端→中端→后端），由宿主编译器（C 实现的 shuc）或上一代 .su 编译器编译，产出的新 shuc **能编译自己的源码**。**依赖** 阶段 7 的语言与标准库；阶段 8 可选但建议有。

| 序号 | 内容 | 依赖 | 完成标志 | 状态 |
|------|------|------|----------|------|
| 9.1 | **用 .su 写编译器前端**：lexer、parser、ast、typeck、IR 生成改为 .su 实现；宿主编译器编译该 .su，与现有 C 后端或占位后端联调 | 阶段 7 的 .su 子集 + core/std 自举子集 | 宿主编译器 + .su 前端能编译示例 .su | ✅ |
| 9.2 | **用 .su 写中端与后端**：优化、codegen、driver 改为 .su；整机「.su 编译器」由宿主编译器或上一代 shuc 编译 | 9.1 | 用 .su 写的完整编译器能编译任意 .su（含自身源码） | ✅ |
| 9.3 | **自举验证**：上述 .su 编译器编译自身源码，得到新 shuc；新 shuc 再编译自身，得到第二代；两代行为一致（测试套件通过） | 9.2 | 自举成功；之后开发全在 .su 内迭代 | ✅ |

**自举验收命令**：在仓库根目录执行 `make -C compiler bootstrap-verify`。通过则输出 `bootstrap-verify OK (自举验证通过)`，表示 shuc₁（宿主编译）与 shuc₂（shuc₁ 编出）对同一测试套件行为一致。

**下一步前置**：无；自举已完成，后续开发可在 .su 内迭代（typeck/codegen 逻辑可继续迁入 .su，见 analysis/自举实现分析.md §7.2.1）。

---

## 三、阶段依赖简表（便于核对）

| 阶段 | 依赖阶段 | 必须就绪的产出 |
|------|----------|----------------|
| 0    | 无       | Makefile，shuc 占位，语法子集文档 |
| 1    | 0        | AST 定义，Lexer 可测 |
| 2    | 1        | Parser：Token → AST |
| 3    | 2        | Typeck 最小，IR 设计确定 |
| 4    | 3        | Codegen + Driver，Hello World 可运行 |
| 5    | 4        | import 解析，core 最小子集 |
| 6    | 5        | std 最小子集，多目标 |
| 7    | 6        | 泛型、trait、模块系统，标准库自举子集完整 |
| 8    | 7        | DCE、内联、LTO，体积与性能达标 |
| 9    | 7（8 建议） | .su 编译器可编译自身，自举成功 |

---

## 四、建议的「第一次可运行」最小路径

若希望**尽快看到「.su 编译并运行」**，可严格按以下最小路径推进，避免提前做依赖未就绪的事：

1. **阶段 0**：Makefile + shuc 占位 + 语法子集（仅 main 返回 0 或 main 调 print 一个字符串）。
2. **阶段 1**：AST（仅 main + 字面量 + 一个 print 调用）+ Lexer。
3. **阶段 2**：Parser 对该子集产出 AST。
4. **阶段 3**：Typeck 只检查 main 存在且签名正确；IR 设计为「直接由 AST 生成 C」即可（一条线，无优化）。
5. **阶段 4**：Codegen 将上述 AST 转成一张 C 的 main() 调 printf；Driver 调用 `cc -o out out.c`；examples/hello.su → 编译 → 运行输出 "Hello World"。

完成以上后，再按阶段 5–9 加 import、core、std、泛型、自举。这样可保证**每一步都有明确依赖且不缺失**。
