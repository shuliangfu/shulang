# X 语言

> **写底层代码，终于可以又简单、又安全、又快。**
>
> 熟悉的命令式风格 · 接近 Rust 的内存安全、却不靠重型类型论 · 默认代码质量目标**超越**精心编写的 C · 学习成本以**天**计，不以月计。

| | |
|--|--|
| **语言名** | **X 语言**（英文 **X language**） |
| **工具链短名** | `xlang` — 编译器命令、包名、仓库短名 |
| **编译器二进制** | `xlang` / `xlang_asm`（完整构建后的产品二进制） |
| **源文件后缀** | `.x` |
| **项目构建** | `build.x` — 用 X 语言描述构建策略（`xlang build` / `build_tool` / `xlang-build.sh`） |
| **现阶段（2026-09-08）** | **产品 L4 钉盘 `b5be5ed97`**（2026-09-02 双端真冷 + bstrict **129/129**；前序 `e8176cbe5` 2026-08-23 → `f7424ae47` 2026-08-15）。tip 在 **`self-hosting`**：Cap residual **9.x** 进行中（9.1／9.3／9.4.2–6／9.5／9.6／9.7 已闭；**9.2.4 libm** 探针链 Fix A–F + arm64 f64 AAPCS64 根修已闭；fdlibm exp/log 端口已开写）· leftover unique **0** · 写 `let x: Trait = a`（**不要**写 `dyn Trait`，**P013**）· 日常 L2 **不升钉**。MG Makefile **已删**（0-make hub）。**尚未完全自举** — 冷启动仍需 seed / 宿主 `cc`；`pipeline_abi` mega **硬禁** pure-asm 产品路径（`pipeline_x` host-cc residual 仍在）。 |
| **进度仪表盘** | [自举进度](analysis/自举进度.md) · [自举时序](analysis/自举时序.md) · [C 迁移债](analysis/C迁移追踪.md) · [Makefile 映射](analysis/Makefile迁移表.md) · [叶 residual](compiler/docs/LEAF_PATTERN_RESIDUAL.md) · [9 月 7 日归档](analysis/自举进度-归档-2026-09-07.md) · [9 月 6 日归档](analysis/自举进度-归档-2026-09-06.md) |
| **English** | [README.md](README.md) |

---

## 目录

1. [语言特性概览](#一语言特性概览)
2. [快速开始](#二快速开始)
3. [编译器用法](#三编译器用法)
4. [仓库结构](#四仓库结构)
5. [标准库](#五标准库)
6. [编译器架构](#六编译器架构)
7. [自举状态](#七自举状态摘要--2026-09-08)
8. [里程碑](#八里程碑)
9. [测试与质量](#九测试与质量)
10. [性能基准测试](#十性能基准测试)
11. [工具链生态](#十一工具链生态)
12. [为什么是 X 语言 — 三高一低](#十二为什么是-x-语言--三高一低)
13. [贡献](#十三贡献)
14. [许可证](#十四许可证)

### 怎么读这份 README（读者分层）

| 你是… | 先看 | 再看 |
|-------|------|------|
| **应用 / 库作者** | [§二 快速开始](#二快速开始) · Hello World | [§三 CLI](#三编译器用法) · [§五 标准库](#五标准库) · [docs/](docs/README.md) |
| **工具链 / 编译器贡献者** | [§二](#二快速开始) · [§四 仓库结构](#四仓库结构) · [§十三](#十三贡献) | [§七 自举](#七自举状态摘要--2026-09-08) · 实时 [自举进度](analysis/自举进度.md) · [AGENTS.md](AGENTS.md) |
| **放行 / 钉盘审阅** | 文首状态表 · [§七](#七自举状态摘要--2026-09-08) | 仅认 L4 真冷 + 双端 bstrict **129**；L2 绿 ≠ 升钉 |
| **要 residual 实时数字** | **别只看本文** — 打开 [自举进度](analysis/自举进度.md) 或 `./xbuild bc-inventory` | README 是快照；冲突时以仪表盘为准 |

**文档职责（禁止混权威）：** 根 README = 产品与上手着陆页；`analysis/自举进度.md` = 自举实时 KPI；`compiler/docs/SELFHOST.md` = 操作手册；`docs/` = 面向用户的语言语法；`AGENTS.md` + skill `xlang-selfhost-product-gate` = 工程纪律。

---

## 一、语言特性概览

### 类型与语义

- **基础类型** — `i8`/`i16`/`i32`/`i64`，`u8`/`u16`/`u32`/`u64`，`f32`/`f64`，`bool`，`usize`/`isize`
- **结构体与泛型** — 泛型单态化；trait / impl；类型位写 trait 名即为 dyn 对象（`let x: Clone = a`；**不要**写 `dyn Trait`）
- **可空与错误** — `Option<T>`、`Result<T, E>`（优先于 C 式裸可空指针）
- **切片** — `T[]` 带长度；域标注 `T[]<label>` + 逃逸检查
- **模块** — `import("std.io")` / `import("core.mem")`；**目录即模块**，入口 `mod.x`
- **字段访问** — 源语言**只有 `.`**，没有 `->`（指针上的 C `->` 由 codegen 按类型决定）

### 内存与安全

- **无 GC** — 栈 + 堆 + Arena；编译期 region / 线性 / 借用拒错
- **编译期辅助** — `defer`、`owned`、作用域分配器（`with_arena`）、SROA、BCE
- **分级安全** — 默认安全；裸指针与底层 syscall 仅在 `unsafe { ... }`
- **别名分析** — `noalias` 与借用门控，服务 autovec / DCE

详见 [编译时内存与自动向量化](analysis/编译时自动内存管理和自动向量化.md) · [安全与性能](analysis/archive/narrative/安全与性能.md)。

### 平台

- 条件编译（`#if` / target 分支）
- **一套 API，多 OS** — Linux / macOS 为主产品路径；Windows hybrid / 探针
- Freestanding：`-freestanding`（Linux x86_64 nostdlib 静态路径）
- 目标如 `x86_64-linux`、`arm64-macos`（`-target`）

语法索引：[docs/README.md](docs/README.md)。

#### 支持等级（策略）

**不为每个 OS 小版本都准备必测虚拟机。** 用清晰等级管理预期，只对「官方支持」做严格测试：

| 等级 | 含义 | 我们怎么做 |
|------|------|------------|
| **Tier 1 — 官方支持** | 文档保证、CI 覆盖、出问题优先修 | 只覆盖下表中的**代表性**主机 |
| **Tier 2 — 尽力支持** | 能编能跑即可，不保证 | 成本低或有用户反馈时再修 |
| **Tier 3 — 不支持** | 不测试、不承诺 | 文档写明，避免不切实际期望 |

**与工程金标的关系（和等级正交）：**

| 角色 | 主机 | 说明 |
|------|------|------|
| **金标实验室宿主** | **Ubuntu x86_64** | 可复现的 L4 / 产品门禁真值；禁止单靠 macOS 绿结案 SHARED 债 |
| **产品双端** | Ubuntu x86_64 + **macOS** | 放行钉盘须 L4 真冷 + 全量 `run-all-bstrict` |
| **Windows** | MSYS2 / MinGW **hybrid** 探针 | hybrid 绿 ≠ 产品 L4 / 自举完成 |

**产品 vs 宿主（不要混）：**

| 层次 | 政策 |
|------|------|
| **用户产品二进制** | 目标是路径上的 **去 libc / freestanding**（`-freestanding`、crt0、syscall / `std.sys`、Linux x86_64 nostdlib 静态等）。**X 不是「依赖 glibc 的语言」。** 金标选 Ubuntu **不等于**「发货程序依赖 glibc」。 |
| **宿主 OS 实验室** | 仍需要**代表性机器**来编工具链、跑 CI、钉 L4。实验室优先 **Ubuntu x86_64**——为的是可复现，**不是**把 glibc 当成永久产品 ABI。 |
| **自举残留** | 在自举未完成前，部分**编译器构建 / hybrid / seed** 步骤仍可能碰到宿主 `cc`/`ld` 或系统 C 库。那是**工程残留**，不是终态产品契约。问「我的程序要不要 libc？」请优先看 freestanding 门禁。 |

Linux 宿主更关心 **内核年代 + 架构 + 目标格式（ELF）** 以及**用什么宿主工具编出了编译器**，不是「每个 glibc 点版本」。发行版上的 libc（glibc vs musl）仍可能影响**宿主 bootstrap 怪癖**与残留 hosted 链接——**不是**我们对外宣传的产品 ABI。macOS 看 **Darwin 大版本 + 架构**（arm64 优先）。Windows 看 **Win10/11 + x64 工具链**，不是每个 build 号。

**Alpine 是支持的宿主**（CI Docker 烟测、musl 宿主事实）。它**不是**金标**实验室**宿主：放行钉 / L4 真值仍是 **Ubuntu x86_64**。Alpine 上完整 B-strict / L4 自举对齐走自举后轨道（A-13），**不是**「不修」。产品 freestanding 在 Alpine 上与 Ubuntu 一样走 **产品无 libc** 目标，前提是宿主工具链路径本身是绿的。

#### 官方矩阵 — Linux（实验室宿主：Ubuntu + Alpine …）

| 平台 | 架构 | 等级 | 说明 |
|------|------|------|------|
| **Ubuntu 24.04 LTS** | x86_64 | **1** | 当前主流 LTS 实验室；CI（`ubuntu-latest` / 24.04 线） |
| **Ubuntu 22.04 LTS** | x86_64 | **1** | 金标邻近 LTS 实验室；CI `ubuntu-22.04`；Docker gate 常钉 22.04 |
| **Ubuntu 26.04 LTS**（作为主机使用时） | x86_64 | **1** | 新 LTS 纳入主实验室后与 22.04/24.04 同级 |
| **Alpine Linux** | x86_64 | **2** | **支持宿主**；CI `docker-distro`（`alpine:3.x`）；本地 `scripts/docker-ci-local.sh alpine`；宿主事实见 `XLANG_HOST_ALPINE` / platform linker 文档。宿主 bootstrap 可能不同（musl 时代工具、默认栈等）；产品 freestanding 仍目标 **无 libc**。**非金标实验室**：L4 / 放行钉仍 Ubuntu x86_64；Alpine 上完整 B-strict 自举延后（A-13），**不是不支持** |
| **Ubuntu 24.04 / 当前** | aarch64 | **2** | CI 探针（`ubuntu-24.04-arm`）；非产品金标实验室 |
| **Ubuntu 20.04 LTS** | x86_64 | **2** | 后期 LTS；宿主工具链够新时多半可跑 |
| 其他 Linux 发行版（Debian、Fedora、Arch 等） | x86_64 | **2** | 尽力实验室宿主。报 bug 请带：**发行版 + 架构 + 内核**、构建模式（**freestanding vs hosted**）、若是**编编译器**失败再附 **宿主工具链**（`cc`/`ld` 版本）——**不要**把「glibc 版本」当成产品 ABI 必备字段 |
| **Ubuntu 18.04 及更早** / 过旧宿主用户态 | * | **3** | 已 EOL；实验室软件包 / 工具链过旧 |

#### 官方矩阵 — macOS

| 平台 | 架构 | 等级 | 说明 |
|------|------|------|------|
| **macOS 14 Sonoma** | **arm64**（Apple Silicon） | **1** | CI `macos-14` |
| **macOS 15 Sequoia** 与 **macOS 26.x**（当前 Apple 大版本线） | **arm64** | **1** | CI `macos-latest` 跟随 runner 镜像；主要 mac 开发机 |
| macOS 14+ | **x86_64**（Intel） | **2** | 可能可用；非 CI 主路径；Intel Mac 在收缩 |
| **macOS 13 Ventura** | arm64 / x86_64 | **2** | 尽力支持；无专用 CI 钉 |
| **macOS 12 Monterey 及更早** | * | **3** | 不支持（Xcode / SDK / 链接器预期过旧） |
| iOS / iPadOS / tvOS 作为**宿主**构建 OS | * | **3** | 非宿主平台（交叉目标另论） |

**macOS 一句话策略：** 官方支持 = **Apple Silicon + 近 2～3 个大版本（14+）**。更旧 macOS 与 Intel 为尽力或不支持——不为它们长期堆虚拟机。

#### 官方矩阵 — Windows

| 平台 | 架构 | 等级 | 说明 |
|------|------|------|------|
| **Windows 11** | x64 | **1** | 优先 Windows 宿主；CI `windows-latest`；MSYS2 / MinGW hybrid 路径 |
| **Windows 10 22H2+** | x64 | **2** | 用户基数仍大；按需本地/云复现，不保证与 Win11 同级 |
| Windows 10 22H2 之前 | x64 | **3** | 不纳入目标 |
| **Windows 7 / 8 / 8.1** | * | **3** | **明确不支持**（EOL、安全与现代工具链均不成立） |
| Windows 11 / 10 | ARM64 | **2** | 实验 / 尽力；非 CI 主路径 |
| 纯 MSVC PE 产品路径 | * | **2** | 当前门禁锻炼的是 MinGW hybrid |

Windows 现状是**hybrid / min-gate 绿**且 leftover unique **0**，不是「完整自举 L4 金标」。详见 [自举状态](#七自举状态摘要--2026-09-08)；有文档时见 [Windows 平台限制与测试指南](analysis/Windows平台限制与测试指南.md)。

#### 明确不支持（Tier 3 — 勿默认会修）

| 项 | 原因 |
|----|------|
| Windows 7 / 8 / 8.1 | 长期 EOL；无现代安全 / 工具链故事 |
| Windows 10 早于 22H2 | 超出本项目支持窗口 |
| macOS 12 及更早 | SDK / ld64 / 系统预期过旧 |
| Ubuntu 18.04 及更早 | LTS 已 EOL；过旧宿主用户态 / 软件包 |
| 「每个 Ubuntu / Windows / macOS 小版本都要独立 VM」 | **政策明确不做** — 用等级 + 代表性**实验室**宿主 |

**不是 Tier 3：** Alpine — **Tier 2 支持宿主**（见 Linux 矩阵）。金标是 **Ubuntu x86_64 作为 L4 实验室**，不是「产品必须 glibc / musl 不支持」。

#### 测试资源怎么安排（性价比）

| 层级 | 覆盖 |
|------|------|
| **CI 为主** | Ubuntu 22.04 + 当前 Ubuntu LTS 线；**Alpine + Debian slim**（`docker-distro`）；macOS 14 + `macos-latest`；Windows 最新（hybrid gate） |
| **本地 / 实验室（少量即可）** | 1× Ubuntu LTS（金标）、1× macOS arm64、可选 1× Win11（仅在确有 Win10 用户压力时再加 Win10）；Alpine 用 Docker 即可，不必常备 Alpine 虚拟机 |
| **云实例按需** | 出现可疑平台问题再临时开对应版本复现，比长期囤旧 VM 划算 |

**不会**为 Win7/Win8 或每个 Ubuntu 中间版本长期维护官方虚拟机。Tier 2/3 用户不应默认获得与放行钉盘同级的质量承诺。

---

## 二、快速开始

### 环境要求

- 优先使用上文[支持等级与平台矩阵](#支持等级策略)中的 **Tier 1** 主机（Tier 2 请接受「尽力」）：**Ubuntu x86_64（金标）** 或 **macOS arm64（14+）**；Windows 11 x64 用于 hybrid 探针
- 宿主 C 工具链（`cc` / `clang`；Windows 上 hybrid 路径用 MSYS2 / MinGW）
- 可选：Docker 跑 Linux gate（常见 `ubuntu:22.04`；Alpine 用 `scripts/docker-ci-local.sh alpine` / CI `docker-distro`）

### 首次构建

```bash
# 推荐产品入口（Makefile 已删 — wave942；0-make hub wave944）
./xbuild build-tool                  # pinned seeds → build_tool
./xbuild first-time                  # build_tool + 日常 g05
# 或：./xlang-build.sh first-time

# 仅 cc 冷启动（最小）：
#   cd compiler && sh bootstrap.sh

# 完整 seed 驱动（常用产品 / LSP 路径）：
./xbuild bootstrap-driver-seed
FULL=0 bash compiler/scripts/g05_prepare_and_relink.sh
```

### 日常构建

```bash
# 日常：G-05 → xlang_asm relink
./xbuild build
# 或：./xlang-build.sh build

export XLANG=./compiler/xlang_asm   # 本波产品二进制
./tests/run-hello.sh

# 改后端 / seed 后的重型重建
./xbuild full                        # bootstrap-driver-bstrict 路径
```

| 入口 | 用途 |
|------|------|
| `./xbuild build` / `./xlang-build.sh build` | **日常增量**（默认） |
| `./xbuild full` | 全量 B-strict 风格重建 |
| `./xbuild bootstrap-driver-seed` | 冷启动 seed 驱动 / LSP 二进制 |
| `./xbuild compiler-make <target>` | 残余叶 `.o` / CI hub（0-make） |

**产品二进制** — 构建成功后以 **`compiler/xlang_asm`** 为准（常同步为 `compiler/xlang`）。  
`xlang-c` / seed 工具只服务**冷启动与过渡**，不是日常发布面。

### Hello World

```x
// Hello World — void main 隐含 exit 0（Zig 风格）
const fmt = import("std.fmt");

function main(): void {
  fmt.println("Hello World");
}
```

```bash
export XLANG=./compiler/xlang_asm
$XLANG run examples/hello.x
$XLANG build examples/hello.x -o hello && ./hello
$XLANG check examples/hello.x
```

更多示例：[examples/](examples/)（io、net、async、json、compress 等）。

### 验收测试

```bash
export XLANG=./compiler/xlang_asm
./xbuild l2-matrix                 # 日常产品矩阵（rv / option / hello / si / f32）
./tests/run-all.sh
XLANG_BSTRICT_SKIP_BUILD=1 ./tests/run-all-bstrict.sh   # 产品闸门（约 129 脚本）
./tests/run-linux-a09-a11-gate.sh
./tests/run-freestanding-hello.sh  # Linux x86_64 freestanding S4 烟测
```

凡谈**自举 / 产品放行**，项目要求 **L4 真冷**（擦除 `compiler` / `std` / `core` 下**全部** `.o`，用 `./xbuild bootstrap-driver-seed` 重链二进制 — **不是** `make`）+ **双端** `run-all-bstrict` 全绿。

详见 [自举方法](analysis/自举方法.md) · [SELFHOST.md](compiler/docs/SELFHOST.md)。

> **日常双端 L2 绿 ≠ 升 L4 钉盘。**  
> **现行产品 L4 钉盘 = `b5be5ed97`**（双端真冷 + **129/129**，2026-09-02）。residual tip 可只跑 **L2** 推进，**默认不升钉**。  
> 自举收口期间默认 L2/L4 产品节奏下 **`xlang check` 语法闸门暂停**；仅在明确 dogfood check 面时再跑（见 [§七](#七自举状态摘要--2026-09-08)）。

---

## 三、编译器用法

默认 **ASM 后端**（`-backend asm`）。

```bash
xlang [COMMAND] [OPTIONS]
```

### 子命令

| 命令 | 说明 | 用法 |
|------|------|------|
| `build` | 编译 `.x` 到二进制 / 目标文件（默认 `a.out`） | `xlang build [options] file.x [-o exe]` |
| `run` | 编译并运行 `.x` | `xlang run [options] file.x` |
| `check` | 仅 parse + typeck（不生成代码） | `xlang check [paths...]` |
| `fmt` | 格式化 `.x` 源码 | `xlang fmt [--check] [paths...]` |
| `explain` | 解释诊断代码 | `xlang explain <CODE>` |
| `test` | 运行测试脚本 | `xlang test [script.sh]` |

### 构建选项（`build` / `run`）

| 选项 | 说明 |
|------|------|
| `-backend asm\|c` | 后端（默认 `asm`） |
| `-O <0\|1\|2\|3\|s>` | 优化级别（默认 `2`） |
| `-o <path>` | 输出二进制或 `.o` |
| `-L <dir>` | 库搜索路径 |
| `-target <triple>` | 目标三元组（如 `aarch64-linux-gnu`） |
| `-target-cpu <cpu>` | `native` \| `generic` \| `avx2` \| … |
| `-freestanding` | Nostdlib 静态链接（Linux x86_64 ELF） |
| `-legacy-f32-abi` | 传统 SysV f32 CALL（f64 扩展；默认 xmm ABI） |
| `-E` | 输出 C（调试） |
| `-flto` | 链接时优化（C 后端） |

### 全局选项

| 选项 | 说明 |
|------|------|
| `--print-target-cpu` | 打印宿主 CPU 特性并退出 |
| `--explain <CODE>` | 打印诊断代码解释并退出 |
| `--help`、`-h` | 显示帮助 |

### 环境变量

| 变量 | 效果 |
|------|------|
| `XLANG_ABI_F32_XMM=0` | 等同于 `-legacy-f32-abi`（x86_64 SysV） |
| `XLANG_OPT` | 默认 `-O` 级别 |
| `NO_COLOR` | 禁用彩色输出 |
| `CLICOLOR_FORCE=1` | 强制彩色输出（即使管道重定向） |
| `XLANG_FORCE_COLOR=1` | 等同于 `CLICOLOR_FORCE` |

### 示例

```bash
xlang run examples/hello.x
xlang build examples/hello.x -o hello && ./hello
xlang check examples/hello.x
xlang fmt src/
xlang explain XP003
xlang test tests/run-all-bstrict.sh
xlang --lsp                              # 语言服务器（stdio JSON-RPC）
xlang build -backend c file.x
xlang build -freestanding file.x         # Linux x86_64 nostdlib
```

根目录 [build.x](build.x) 描述编什么。日常入口：`./xlang-build.sh` / `build_tool`。

---

## 四、仓库结构

```
xlang/
├── README.md · README_zh-CN.md
├── LICENSE · LICENSE.AGPL-3.0 · LICENSE.Apache-2.0 · NOTICE · CONTRIBUTING.md
├── build.x · xlang-build.sh · xbuild/
├── analysis/                 # 过程文档、RFC、自举仪表盘
├── docs/                     # 语言语法（面向用户）
├── compiler/                 # 编译器（.x + seed C / glue）
│   ├── src/                  # lexer · parser · typeck · codegen · asm · pipeline · driver · lsp
│   ├── seeds/                # 冷启动 pin
│   ├── mk/                   # driver-seed 列表权威（叶 residual 路径）
│   ├── docs/SELFHOST.md
│   └── scripts/              # build_xlang_asm、g05、relink …
├── core/                     # 无 OS 依赖的核心库
├── std/                      # 面向 OS 的标准库（产品 .x；std 下无手写 .c）
├── tests/                    # 回归与产品闸门
├── examples/
├── tools/ · scripts/
├── runtime/                  # freestanding / 底层运行时支持
└── editors/                  # vscode · vim · tree-sitter
    └── vscode/               # VS Code / Cursor / Trae + LSP 客户端
```

- **`core/`** 不依赖 **`std/`**；**`std/`** 可依赖 **`core/`**
- 模块规则：**目录即模块**，入口 `mod.x`

架构说明（历史叙事）：[构架分析.md](analysis/archive/narrative/构架分析.md)。

---

## 五、标准库

### `core`（无 OS）

| 模块 | 职责 |
|------|------|
| `core.types` | `size_of` / `align_of`、布局 |
| `core.mem` | 内存操作 |
| `core.option` / `core.result` | 可空 / 错误 |
| `core.slice` / `core.str` | 切片与字符串视图 |
| `core.fmt` / `core.debug` | 格式化 / 调试 |
| `core.builtin` / `core.iterator` / `core.cmp` | 内置、迭代、比较 |

完整列表：[docs/07-内置与标准库.md](docs/07-内置与标准库.md)。

### `std`（面向 OS）

`std/` 产品源为 **`.x`**（阶段 F：`std/` 下无手写 `.c` / `.h`）。覆盖面包括：

| 类别 | 示例 |
|------|------|
| 基础 | `std.io`、`std.fs`、`std.path`、`std.process`、`std.env` |
| 容器 | `std.vec`、`std.map`、`std.set`、`std.queue` |
| 内存 | `std.heap`、`std.mem` |
| 并发 | `std.thread`、`std.sync`、`std.channel`、`std.async` |
| 网络 | `std.net`、`std.http`、`std.websocket` |
| 数据 | `std.json`、`std.csv`、`std.compress`、`std.db` |
| 系统 | `std.sys`（Linux / macOS；Windows 推进中） |
| 工具 | `std.test`、`std.fmt`、`std.log`、`std.cli`、`std.crypto` 等 |

**按需入链** — 尽量不把未用模块拖进最终链接。

---

## 六、编译器架构

```
.x 源
  → 预处理（#if / import）
  → lexer → parser → AST
  → typeck（泛型、借用、region …）
  → codegen（默认 ASM，或 -E / -backend c）
  → 宿主链接 → 可执行文件 / .o
```

| 路径 | 含义 |
|------|------|
| **用户 / 产品轨** | 本 SHA 的 `xlang_asm` 编用户 `.x` → `-o` / 运行；产品矩阵 + bstrict |
| **自举 / 工程轨** | seed 冷启动 → `build_xlang_asm` / g05 → 可选 Stage2 / WPO dogfood |

### 双轨（读进度时不要混）

| 轨道 | 测什么 | 能否单独说「自举完成」 |
|------|--------|------------------------|
| **产品轨** | L4 真冷 + 产品矩阵 + 双端 `run-all-bstrict` **129** | **必要**，但还不够宣称「永久零 C」 |
| **工程轨** | prove T/N、Cap residual pure、Stage2、WPO 链 / 链接 / text 门 | **否** |

---

## 七、自举状态（摘要 · 2026-09-08）

> **实时数字以** [自举进度.md](analysis/自举进度.md) · [C迁移追踪.md](analysis/C迁移追踪.md) · [LEAF_PATTERN_RESIDUAL.md](compiler/docs/LEAF_PATTERN_RESIDUAL.md) · inventory `./xbuild bc-inventory` **为准**。  
> README 只给摘要；**禁止**把 Stage2 / prove / WPO / **日常 L2 绿**写成 L4 重钉或「完全自举」。  
> **Makefile 物理删除已完成**（wave941/942）。产品入口仅为 **`./xbuild`** — 禁止再引入 `make -C` 编排。冷启动走 **`./xbuild bootstrap-driver-seed`**，不是 `make bootstrap-driver-seed`。

### 产品轨

| 项 | 状态 |
|----|------|
| **L4 放行钉盘（现行）** | **`b5be5ed97`**（2026-09-02）— 双端 **真冷** + 产品矩阵 + bstrict **129/129**；pin 蛋已从本波 `xlang_asm` 刷新；Darwin L4 默认 `JOBS=1` |
| 钉盘谱系（旧 → 新） | `36363b90f` → `d79a368b2` → `e364f4a37` → `f7424ae47`（2026-08-15）→ `e8176cbe5`（2026-08-23）→ **`b5be5ed97`** |
| 产品 bstrict 套件 | **129**（`tests/run-all-bstrict.sh`；日志须 `OK (129 scripts…)`） |
| Ubuntu L4 + 全量 bstrict（钉盘） | ✅ **129/129** @ **`b5be5ed97`**（金标实验室 · wall **17m47s**） |
| macOS L4 + 全量 bstrict（钉盘） | ✅ **129/129** @ **`b5be5ed97`**（wall **137m25s**，`JOBS=1`） |
| 日常闸门（tip） | **双端 L2 产品矩阵** — `./xbuild l2-matrix`（rv42／opt102／hello／si／f32）。SHARED 叶须 **mac + Ubuntu**。 |
| residual tip（≠ 钉盘） | inventory **present 0** · leftover unique **0** · **prefer pure-asm 产品默认** · Cap **9.x** 进行中（见前排）· 日常 L2 **不升钉** |
| Windows hybrid / leftover unique | leftover unique **0** · min-gate **全绿** · leftover-PE hybrid 仅 Windows 在线时额外跑（与 Ubuntu 双系统互斥）。hybrid 绿 ≠ 产品 L4 |
| 金标主机 | **Ubuntu x86_64**（回家局域网：`ubuntu-server`；外地实验室可用 `ubuntu-remote-server`／frp） |
| 验收二进制 | 本波 g05 / pure-ld relink 的 `compiler/xlang_asm` — **禁止**残留 Stage2 `xlang_asm2` 或旧 stage1 |
| `xlang check` 闸门 | 自举收口期间默认 L2/L4 产品节奏下 **暂停**；不是 residual 叶的默认绿/红判据 |
| nest 冻帽 | **64** — 禁止本叶抬到 65；禁止默认 assemble `parser.x`／`pipeline_abi` mega |

### 今天「可用」指什么

在**用户产品路径**（`xlang_asm` → `-o` / 运行 / freestanding / 门禁）上，放行钉盘已覆盖大量已收口面——net PRIMARY、bare struct lit、CTFE match 折叠、X ABI P0b、TYPE_DYN／vtable（写 `let x: Trait = a`）、dest extras dest-stamp、Windows hybrid min-gate、CLI help、freestanding S4 / NL-07、hosted asm 矩阵、**prefer 族 pure-asm 产品默认**等。

**钉盘之后**，`self-hosting` tip 已收 leftover unique 收割、MATCH dest-park 族、Cap **9.1／9.2.1／9.3／9.4.2–6／9.5／9.6／9.7**、9.2.4 **探针链 Fix A–F**（NaN／f64 demote／exact-7 位级 libm／无序比较／SysV movq／fk9 按需 60 面），以及 **mac arm64 f64 AAPCS64 边界**（GP-bits vs host-cc `d0–d7`／`d0`）。**9.2.4 fdlibm 级端口**（exp/log wave A）是当前 Cap 活叶。

**residual tip 的 L2 绿不会自动抬升 L4 钉盘。** tip 上的 Ubuntu 真冷复验（如 `@1c46bef21`）是回归检查，不是升钉。

### 轨道（MG / BC / Stage 8–13 / 终局）

| 轨道 | 状态 |
|------|------|
| **MG**（Makefile 编排） | ✅ **已完成** — `compiler/Makefile` 已删；0-make hub `tests/lib/compiler-make.sh`；产品入口 `./xbuild` / `./xlang-build.sh` |
| **BC**（产品 residual host-cc catalog） | 🟢 **30/30 FULLY CLOSED**（wave332）— PRODUCT RETIRED **23/23 = 100%**；HALF=0；产品 PINNED=0；NON-PRODUCT 7 正确 never-product-chain |
| **M4 五域** | ✅ **5/5** 冷链关 pin（适用处 prefer FROM_X 产品默认）。parser seed **物理删／CI 漂移闸**仍 ⬜ |
| **Stage 8 Track L** | ✅ **30/30 FULLY CLOSED**（Batch 3 · wave332） |
| **Stage 9 Cap residual** | 🟡 — 9.1／9.2.1／9.3／9.4.2–6／9.5／9.6／9.7 ✅；**开项：** 9.2.4 libm（进行中）· 9.2.5 arrow · 9.2.6 sqlite |
| **Stage 10 语言 L2** | 🟡 — 10.1.1–2／10.1.4／10.2.1–3（部分）／10.3.*／10.4.1–2 ✅；残 qemu／10.1.3 NT |
| **Stage12 / PC prefer** | ✅ prefer pure-asm 产品默认 · FORBID／ALLOW_HOST_CC · **`pipeline_abi` mega pure-asm 硬禁**；`pipeline_x` 整 TU 仍 host-cc；`invoke_cc` 未删 |
| **Stage 12 零 cc 冷启** | 🟡 LINK／`.s`／多数门 ✅；最小 seed／全路径零 `cc` ⬜ |
| **PC / G**（无 seed 冷启动 / 全量零 C） | ⬜ 开 — 冷启动仍需 seed + 宿主 `cc` |

### residual inventory（量级）

| 信号 | 值（2026-09-08） |
|------|------------------|
| `./xbuild bc-inventory` present 行 | **0**（catalog 已闭；mega／seed 冷 residual **不**计 present 叶） |
| leftover unique（Windows leftover-PE 收割） | **0** |
| R2 真迁 | ~**120/128**（~85%） |
| `pipeline_x` mega | 仍 **host-cc**（不计 present 叶；纯 asm 产品硬禁） |
| 运维陷阱（2026-09-08） | **陈旧产品 `.o`**：新鲜度只比 `.x` 源时间戳 — 编译器发射修复**不会**自动失效旧 `.o`（防法＝L4 全擦）。mega `.x` 体内改动须 `XLANG_HOST_CC_SEED_FORCE=1`（平日 inject-only thin 捷径不重建 mega 体） |
| 效率纪律 | **按域 / 整类 / 整叶**，禁止一波一个 BSS micro-cell |

### 工程轨（量级）

| KPI / 门禁 | 状态 |
|------------|------|
| **T** | **18/18** |
| **EMPTY** | **18/18** |
| **N** prove IDENTICAL | **111/111** |
| Cap residual pure | 按需 L2；产品 prefer pure-asm 处双导出禁令仍在 |
| **D Stage2** | ✅ freestanding / 行为 parity（**≠** 产品 g05 全链）；双端 Stage2 SHA256 match（Ubuntu `9e60e1290` · macOS `343894709`） |
| Stage2 **WPO** 链 + strict-link + text-gate | ✅ 工程绿（Ubuntu；部分 Darwin N/A） |

### 明确不宣称

- **未**宣称「编译器已 100% `.x`、无 seed」
- **未**把 Stage2 的 `xlang_asm2` 当产品编译器
- **未**把工程 WPO 绿等同 tip 产品 L4
- **未**把「双端 L2／tip Ubuntu 真冷复验」写成升 L4 钉 —— 钉盘仍为 **`b5be5ed97`**，须下次显式双端 **真冷** 才重钉
- **未**把 Windows hybrid／leftover unique 0 当成产品 L4 / 自举完成
- **未**把「Makefile 已删」写成「自举 / 零 host-cc 完成」— seed + `pipeline_abi`／`pipeline_x` mega residual 仍在
- **未**宣称 Cap 9 已全闭 — 9.2.4–6（libm／arrow／sqlite）仍开
- **未**把 mac arm64 f64 卡当仍开 — GP-bits vs AAPCS64 已根修 `@363a68697`＋`@1c46bef21`；Ubuntu 真冷复验 12/12＋L2 5/5
- 终局物理零 C / 彻底去掉 seed（**G**）仍在路线图，不是本周叙事

**完全自举（D+E+F）：** 阶段 **D**（Stage2 freestanding／parity）+ **E**（编译器产品路径无 C/H）+ **F**（阶段 F：仓库 `std/`／产品面无手写 C）。仅 Stage2 **不等于**完全自举。权威：[SELFHOST.md](compiler/docs/SELFHOST.md)。

方法：[自举方法.md](analysis/自举方法.md) · 时序：[自举时序.md](analysis/自举时序.md) · 运维：[SELFHOST.md](compiler/docs/SELFHOST.md) · 纪律：[AGENTS.md](AGENTS.md) + skill `xlang-selfhost-product-gate`。

### 近端前排

1. **Cap 9.2.4 libm** — fdlibm 级 `math_*_impl` 端口（32 桥；wave A exp+log 已开写）。探针链 Fix A–F 与 arm64 f64 AAPCS64 边界 **已闭**。随后 9.2.5 arrow／9.2.6 sqlite extern 系统库大域。**默认不升钉**  
2. **保持 0-make 诚实** — 产品路径只走 `./xbuild`；禁止再引入 `make -C`；prefer pure-asm 默认；禁止 pure-asm `pipeline_abi` mega；nest 帽仍 **64**  
3. **立卡不动（非本周收口）** — `pipeline_x` host-cc mega · Ubuntu std bstrict 红簇（约 21 脚本）· Defect D typeck XT001 · wpo-full-chain Darwin · 10.7.1 va gate · check 闸门暂停（自举后）

---

## 八、里程碑

| 里程碑 | 内容 | 状态 |
|--------|------|------|
| M0 | Lexer、AST、Parser | ✅ |
| M1 | Typeck、Codegen、Driver | ✅ |
| M2 | import、core/std 子集、多目标 | ✅ |
| M3 | 泛型、trait、模块、std 扩张 | ✅ |
| M4 | DCE、`-O2`/`-Os`、体积 / 性能基线 | ✅ 部分 |
| M5 | 自举（编译器可重编自身） | 🟡 **产品路径可用 + 自举推进中**；**冷启动仍需 seed**；MG **已删**（0-make）；BC catalog **present 0**／Track **30/30 CLOSED**；Cap 9 residual **进行中**（9.2.4 libm） |
| **当前** | L4 钉 **`b5be5ed97`**（双端 129 · 2026-09-02）；tip `self-hosting` Cap **9.2.4** + leftover unique **0**；写 `let x: Trait = a`；BC／Stage8 **CLOSED** · MG ✅ · prefer pure-asm 默认 | 见 [仪表盘](analysis/自举进度.md) |

---

## 九、测试与质量

| 套件 | 命令 |
|------|------|
| 日常产品矩阵（L2） | `XLANG=./compiler/xlang_asm ./xbuild l2-matrix` |
| 全量回归 | `./tests/run-all.sh` |
| 产品 bstrict | `XLANG=./compiler/xlang_asm XLANG_BSTRICT_SKIP_BUILD=1 ./tests/run-all-bstrict.sh` |
| 推送前 P0 | `XLANG=./compiler/xlang_asm ./tests/run-pre-push-p0.sh` |
| Linux 金标子集 | `./tests/run-linux-a09-a11-gate.sh` |
| 主题门禁 | `tests/run-*-gate.sh` |
| 编译 dogfood | `XLANG_PERF_FAIL_ON_COMPILE_REGRESSION=1 ./tests/run-perf-compile-dogfood.sh` |

基线目录：`tests/baseline/`。跑 **真冷全测** 时，应把日志路径打印给操作者（如 `/tmp/*true_cold*`、`/tmp/*true_bstrict*`）。

以上正确性闸门是 **通过 / 失败**。与 C / Zig 的墙钟、体积、编译时间对比见 **[§十 性能基准测试](#十性能基准测试)**（`bench/` + `./bench.sh`）；**有意不纳入** `run-all`。

---

## 十、性能基准测试

在**相同算法**下对 **xlang / C / Zig** 做可复现的公平对比。本章是 README 着陆页；操作规则与实时数字以 `bench/` 下方法论文档为准。

| 文档 | 作用 |
|------|------|
| [bench/v1-methodology-zh-CN.md](bench/v1-methodology-zh-CN.md) | **权威** — 公平性规则、工具链钉盘、维度映射、v1.0 快照 |
| [bench/v1-methodology.md](bench/v1-methodology.md) | 同上，英文 |

### v1.0 是什么

- **版本**：**v1.0 自举期基线**（2026-08-02）。编译器仍处于 seed/bootstrap；部分 case 可能 `COMPILE FAIL`（属预期）。**v2.0** 在自举完成后全量重跑；**v3.0** 增加 Evented 异步路径。
- **公平性硬规则**：同算法 / 同数据结构 / 同输入规模；同机同次运行；固定编译选项；多轮统计（中位数 / 均值 / p95 — **禁止只报最快一轮**）；`bench/` 源码公开；禁止跨优化级别偷比；C 侧有防常量折叠的 asm barrier（xlang 尚无等价物 — 异常偏快的 X 数字会标注）。
- **锚点**：C `cc -std=gnu11 -O2` · Zig `zig build-exe -OReleaseFast` · xlang `xlang-c -O 2`。谈产品数字以 **Ubuntu x86_64** 为金标；macOS arm64 仅作趋势观察。
- **语料**：`bench/` 约 155 个源文件，命名 `bench/<维度>_<名称>.{c,x,zig}`。

### 维度映射（前缀 → 领域）

| 前缀 | 领域 | 优先级 |
|------|------|--------|
| `r01_`–`r10_` | 运行时计算 | P0 |
| `m01_`–`m05_` | 内存与分配 | P0 |
| `b01_`–`b05_` | 二进制体积与链接 | P0 |
| `bt01_`–`bt05_` | 构建时间 | P0 |
| `s01_`–`s05_` | 安全开销 | P1 |
| `a01_`–`a05_` | ABI 与调用 | P1 |
| `cc01_`–`cc05_` | 并发 | P1 |
| `i01_`–`i08_` | I/O 与异步 | P1 |
| `e01_`–`e04_` / `l01_`–`l03_` | 嵌入式 / 语言自身 | P2 |

### 如何运行

```bash
./bench.sh                 # 默认 P0+P1 + 工具链矩阵（约 2 分钟快速看数）
./bench.sh --quick         # 更少样本
./bench.sh --dimension r   # 单维度族
# 亦可：tests/run-perf-baseline.sh --bench
#       tests/run-perf-p0-matrix.sh
#       tests/run-perf-toolchain-matrix.sh
```

原始日志一般在 `/tmp/xlang_perf_run.log` 与 `/tmp/xlang_net_perf_run.log`。环境固定：`tests/lib/perf-env.sh`。

### v1.0 快照（仅摘要）

方法论文档中最近一次全量记录：**2026-08-02 · macOS arm64**（趋势用）。颜色图例：✅ X ≤ C 且 X ≤ Zig · 🟡 只赢其中一方 · ❌ 双方都输 · ⚪ X 编译失败 / 无对照。

| 切片 | 汇总（来自 methodology §6） |
|------|---------------------------|
| 摘要表 micro/io/net（§6.0，有数据 13 case） | ✅ 9 · 🟡 2 · ❌ 1 · ⚪ 1 |
| 全局颜色汇总（§6.0–§6.3b） | ✅ 26 · 🟡 6 · ❌ 5 · ⚪ 4 |

当前偏红的主要集中在**编译时间**（自举期预期）与部分**并发回退** case。I/O 与若干 micro 在该主机上已与 C/Zig 持平或领先——谈产品结论前务必再对 Ubuntu。完整表、`vs_c` / `vs_zig` 与备注（含「疑似已折叠」）**只**在方法论文档中维护。

---

## 十一、工具链生态

| 组件 | 路径 |
|------|------|
| VS Code / Cursor / Trae | [editors/vscode/](editors/vscode/) |
| Vim | [editors/vim/](editors/vim/) |
| Tree-sitter | [editors/tree-sitter-xlang/](editors/tree-sitter-xlang/) |
| LSP | `xlang --lsp` · `compiler/src/lsp/` |

插件安装：[editors/vscode/README.md](editors/vscode/README.md)。

---

## 十二、为什么是 X 语言 — **三高一低**

**X 语言**是一门面向内核、驱动、运行时、嵌入式与高性能工具的**系统级编程语言**：无 GC、零成本抽象、显式内存模型，可 freestanding。

多数语言逼你二选一。X 语言拒绝这个假选择：

| 支柱 | 目标 | 落地含义 |
|------|------|----------|
| **高性能** | **默认就比精心写的 C 更快** | 无 GC；默认 ASM 后端（+ 可选 C 后端）；激进别名 / `noalias`、BCE、泛型单态化；Arena / region 热路径零 malloc。性能主要靠**编译器**，不是每个调用点靠人肉优化。 |
| **高安全** | **安全子集内接近 Rust** | 编译期 region / 借用 / 线性类型检查；`Option` / `Result` 优先于静默空指针；带长度切片；`unsafe` 仅用于硬件与 syscall 边界——**可审计**，不是默认可 UB。 |
| **高可读** | **比 C 更简单、更好维护** | `T[]` 自带长度；无头文件地狱（目录即模块）；`defer` / `with_arena` / 作用域分配器；字段访问只有 `.`；诊断带真实位置。 |
| **低学习成本** | **有编程基础，按「天」上手** | 不要求先啃类型论：有一门命令式语言基础（C / C++ / Java / Go / **JS / TS** / …）即可。控制流直观，无 lifetime 注解迷宫；可渐进——先写「类 C」风格，再引入现代安全特性；`xlang build` / `fmt` / LSP 一体。 |

**每条语言特性的评审铁律：**

> *这会让 C 程序员觉得更麻烦吗？*  
> 会 → 砍掉、藏进编译器，或关进 `unsafe`。  
> **「比 C 更简单」是设计评审的第一准则**；安全与性能由编译器智能补齐，而不是把负担推给作者。

### 诚实对照

| 对照 | X 语言的选择 |
|------|-------------|
| **相对 C** | 同样贴近机器 —— 语法更干净、更少脚枪、工具链一体，在 C 常有 UB 的地方给出安全证明。 |
| **相对 Rust** | 同样追求内存安全 —— **不必**过「重型 borrow checker 生活方式」；region + 推断 + 线性类型扛重活。 |
| **相对 Zig** | 同样崇尚简单与显式 —— 再加默认安全子集与更强的静态安全叙事。 |

### 支撑目标

| 目标 | 含义 |
|------|------|
| **轻量** | 依赖少、二进制小、可 freestanding / 嵌入式；标准库按需入链 |
| **标准库** | 完整 `core/` + `std/`；跨平台一套 API（差异收在 `std.sys`） |
| **编译自举** | 终局：编译器与标准库 100% `.x`；宿主 C / seed 仅冷启动（**进行中，未宣称完成**） |

### 设计宗旨

- **目的** — 在关键路径极致压榨性能：**默认代码质量优于「普通认真写的 C」**，而不是「你够小心才一样快」。
- **原则** — 可维护、开发简单、**内存安全**（安全子集无静默 UB）。
- **方法** — region 内存 + 借用门控 + 线性类型；别名分析服务 autovec / DCE；`unsafe` 保持薄且可审。

设计长文：[语法与安全](analysis/语法与类型设计-高性能与内存安全.md) · [需求分析](analysis/需求分析.md) · [安全与性能](analysis/archive/narrative/安全与性能.md)。

---

## 十三、贡献

1. 克隆 → `./xbuild build-tool && ./xbuild first-time`（或 `./xbuild bootstrap-driver-seed`）。  
2. 日常改动 → `./xbuild build`，`XLANG=./compiler/xlang_asm`，跑相关测试 / gate。  
3. 产品 / 链接 / **SHARED** 改动 → **Ubuntu 金标**（SHARED 再加 mac）；谈放行须 **L4 真冷** + 双端 bstrict **129**（现行钉盘 **`b5be5ed97`**，直至显式升钉）。  
4. 日常 residual 叶 → **L2**（pure-ld + 产品矩阵探针）；自举收口期间**不要**默认跑 `xlang check` 闸门。  
5. 提交：Conventional Commits（`feat:` / `fix:` / `docs:` …）；`.x` 新注释用**英文**（见 `AGENTS.md` / G.9）。  
6. **禁止双权威** — seed 与 `.x` 产品面必须**同 commit**对齐。  
7. **禁止假绿** — 不得仅凭 prove / Stage2 / WPO / 日常 L2 宣称自举完成。

**当前决议** — 自举 / 产品闸门优先于大规模 std 新功能；IR v4 架构已冻结，留给自举后阶段。

---

## 十四、许可证

X 语言采用 **分层授权**（语言库宽松；编译器 copyleft）。详见 [LICENSE](LICENSE) 与 [NOTICE](NOTICE)。

| 层 | 路径 | 许可 |
|----|------|------|
| A — 工具链 | `compiler/`、`tools/`、根目录 `build*.x` | **AGPL-3.0-or-later**（[LICENSE.AGPL-3.0](LICENSE.AGPL-3.0)） |
| B — 语言库 | `core/`、`std/` | **Apache-2.0**（[LICENSE.Apache-2.0](LICENSE.Apache-2.0)） |
| 样例 | `examples/`、`tests/` | **Apache-2.0** |
| 编辑器 | `editors/vscode`、`editors/tree-sitter-xlang`、`editors/vim` | **Apache-2.0** |
| 第三方 | `compiler/seeds/crypto/ed25519/`（orlp） | **zlib** |

**意图：** 使用 `core` / `std` 编写的程序**不会**被强制 AGPL；修改或再分发 **编译器 / 工具链** 适用 AGPL（或商业条款）。

贡献约定：[CONTRIBUTING.md](CONTRIBUTING.md)。

### 商业许可（仅 Layer A）

若需对 **编译器 / 工具链** 做 **AGPL 豁免**（闭源嵌入、闭源分发修改后的工具链、修改后的网络服务不提供对应源码等），请联系：

- 舒良府（ShuLiangfu）— [admin@shuliangfu.com](mailto:admin@shuliangfu.com)

---

*X 语言 — 三高一低：比 C 更快 · 接近 Rust 的安全 · 比 C 更简单 · 按天上手。*
