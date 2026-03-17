# asm/ — 直接出机器码（汇编）后端

将 **AST** 转为 **汇编文本 (.s)** 或 **ELF64 可重定位目标文件 (.o)**，不经过 C 或 LLVM。由 pipeline 在 `-backend asm` 时调用。本文档说明「完整实现」需要哪些能力、当前完成情况，以及未完成项的开发计划。

---

## 一、实现状态总表（完成打勾，未完成列说明）

### 1. 输出形式与架构

| 能力 | x86_64 | arm64 | riscv64 | 备注 |
|------|--------|--------|---------|------|
| 出汇编文本 (.s) | ✅ | ✅ | ✅ | 三架构均完整；GAS 语法 |
| 直接出 ELF .o | ✅ | ✅ | ✅ | riscv64_enc 已实现（RV64I、B/J patch） |

### 2. 表达式与语句（文本 asm 路径）

| 类别 | 项 | x86_64 | arm64 | 说明 |
|------|----|--------|--------|------|
| 字面量 | EXPR_LIT / EXPR_BOOL_LIT | ✅ | ✅ | 立即数返回 |
| | EXPR_FLOAT_LIT | ✅ | ✅ | 位模式：typeck 填 float_bits_lo/hi，asm 用 movq/movz+movk 入 rax/x0 |
| 控制 | EXPR_RETURN | ✅ | ✅ | 子表达式求值到 rax/x0 |
| | EXPR_PANIC | ✅ | ✅ | call shulang_panic_（由 runtime_panic.o 提供；Linux 用 syscall exit 不链 libc） |
| | EXPR_BREAK / EXPR_CONTINUE | ✅ | ✅ | 循环内 jmp 到标签 |
| 算术 | ADD / SUB / MUL / DIV / MOD | ✅ | ✅ | 含立即数优化（左或右操作数为字面量时免 push/pop） |
| 比较 | EQ / NE / LT / LE / GT / GE | ✅ | ✅ | cmp + setcc / cset |
| 逻辑/位 | LOGAND / LOGOR / LOGNOT | ✅ | ✅ | 短路与标签 |
| | BITNOT / BITAND / BITOR / BITXOR | ✅ | ✅ | |
| | SHL / SHR（移位） | ✅ | ✅ | 需 rbx/ecx 存计数 |
| 变量与存储 | EXPR_VAR | ✅ | ✅ | 从 [rbp-off]/[x29,#-off] 加载 |
| | EXPR_ASSIGN（左值 VAR） | ✅ | ✅ | store 到栈槽 |
| 复合访问 | EXPR_INDEX | ✅ | ✅ | base 可为任意表达式或 slice（取 ptr 再下标）；元素 4 字节 |
| | EXPR_FIELD_ACCESS | ✅ | ✅ | base 可为任意表达式；使用 field_access_offset（C typeck 已填） |
| 调用 | EXPR_CALL（0～6 参） | ✅ | ✅ | 含 arm64 栈传参 + ldr 入 w0～w5 |
| | EXPR_METHOD_CALL（0～5 额外参） | ✅ | ✅ | receiver 作第一参 |
| 控制流 | EXPR_IF / EXPR_TERNARY | ✅ | ✅ | test + jz + 分支 |
| | EXPR_BLOCK | ✅ | ✅ | const/let 初始化 + stmt_order |
| | while / for 循环 | ✅ | ✅ | 标签 + break/continue |
| 一元 | EXPR_NEG / EXPR_LOGNOT | ✅ | ✅ | |
| 复合值 | EXPR_STRUCT_LIT | ✅ | ✅ | temp 区 64 字节，最多 8 字段×8B |
| | EXPR_ARRAY_LIT | ✅ | ✅ | temp 区，最多 16 元素×4B |
| | EXPR_MATCH | ✅ | ✅ | 多分支：字面量/枚举 variant 比较或通配符，标签分支 |
| | EXPR_ENUM_VARIANT | ✅ | ✅ | 使用 **enum_variant_tag**（由 typeck 填写） |
| 其它 | const_folded | ✅ | ✅ | AST 层常量折叠后直接 ret 立即数 |

图例：✅ 已实现；△ 部分/占位；— 未实现。**riscv64** 与 x86_64、arm64 功能对齐（同一 backend 分派，见 arch/riscv64.su）。

### 3. 直接出 .o（ELF 编码层）

| 能力 | x86_64_enc | arm64_enc | 说明 |
|------|------------|-----------|------|
| prologue / epilogue | ✅ | ✅ | arm64_enc 已实现，按 current_frame_size 生成 |
| ret / mov 立即数 | ✅ | ✅ | ✅ | |
| 栈槽 load/store、lea | ✅ | ✅ | ✅ | |
| 二元运算、比较、setcc | ✅ | ✅ | ✅ | |
| push/pop、call、jz/jnz/jmp | ✅ | ✅ | ✅ | 含 patch（x86/arm imm_bits；riscv64 B/J）与 reloc |
| INDEX（lea+scale4+load32） | ✅ | ✅ | ✅ | |
| FIELD_ACCESS（lea+add_imm+load64） | ✅ | ✅ | ✅ | |
| STRUCT_LIT / ARRAY_LIT（temp 区） | ✅ | ✅ | ✅ | store 4/8 字节 + mov_rbx_to_rax |
| MATCH 多分支 / ENUM_VARIANT 真实 tag | ✅ | ✅ | ✅ | 与文本 asm 逻辑一致 |
| 符号与重定位（ELF） | ✅ | ✅ | ✅ | e_machine 62/183/243；elf.su 含 R_RISCV_* patch |

当前：**x86_64、arm64、riscv64** 均支持 `-o out.o`（ELF）；backend 按 `target_arch` 分派。**平台/对象格式**在 **platform/**：`elf.su`（ELF）、`macho.su`（Mach-O）、`coff.su`（**COFF 仅 x86_64**），与 arch/ 并列。

### 4. 优化与扩展

| 项 | 状态 | 说明 |
|----|------|------|
| 7.3 寄存器分配 | ✅ | 固定 rax/rbx；窥孔消除连续 push/pop；**发射时右操作数为字面量则 mov 到 rbx 免 push/pop**（文本 asm 与 ELF 双路径均已支持）；可进一步做活跃分析 |
| 窥孔优化 | ✅ | peephole_run：去空行 + 消除冗余 push/pop（x86/arm64）+ **消除 no-op movq %rax,%rax** |
| EXPR_FIELD_ACCESS 真实偏移 | ✅ | backend 已用；**C 与 .su typeck 均已填写**（.su 从 STRUCT_LIT 推导布局 + VAR 的 resolved_type_ref） |
| EXPR_INDEX base 为表达式/切片 | ✅ | base 可为任意表达式；slice 已支持（从 (ptr,len) 取 ptr 再下标） |
| FLOAT_LIT 位模式 | ✅ | typeck 填 float_bits_lo/hi，asm 内联 movq/movz+movk |
| MATCH 多分支与模式 | ✅ | 已实现：AST per-arm 模式，backend 发射比较与分支 |
| ENUM_VARIANT 真实 tag | ✅ | 已实现：使用 enum_variant_tag；payload 布局待扩展 |
| 平台/对象格式差异 | 完成 | **Linux**：默认产出 ELF 可重定位 .o，`ld -e _main -o out out.o`。**macOS**：已实现 Mach-O writer，`-o out.o` 自动写 Mach-O 64 位 MH_OBJECT，链接用 `ld -e _main -o out out.o -lSystem` 或 `clang -o out out.o`。**Windows**：已实现 COFF/PE .obj（`platform/coff.su`），`-target *-windows-*` 且 `-o out.o`/`-o out.obj` 时自动写 COFF，链接用 `link /entry:_main out.obj` 或 `lld-link /entry:_main out.obj`。其他（如 *BSD）多为 ELF，与 Linux 一致。 |
| 新架构（riscv64） | ✅ | **已完整实现**：arch/riscv64.su 全部 emit_*（prologue/epilogue 含 s0、算术/比较/位运算/栈/load/store/call/jz/jnz/jmp 等）、arch/riscv64_enc.su 全部 enc_*（RV64I 编码、B/J patch）；-target riscv64 可出 .s 与 .o |

**后续可做**：更多窥孔；可选在 macOS 交叉编译到 riscv64 时仍出 ELF（当前 macOS 一律出 Mach-O）。

### 5. Windows COFF 支持（已实现）

- **platform/coff.su**：实现 `write_coff_o_to_buf(ctx, out)`，复用 `ElfCodegenCtx`（调用前需 `elf_resolve_patches`）；仅支持 x86_64（e_machine 62），写出 PE/COFF .obj（.text、符号表、重定位 IMAGE_REL_AMD64_REL32、字符串表）。
- **driver**：`-target` 含 `windows` 且 `-o out.o`/`-o out.obj` 时设 `use_coff_o = 1`，asm.su 分支调用 `platform.coff.write_coff_o_to_buf`。
- **链接**：Windows 下用 `link /entry:_main out.obj` 或 `lld-link /entry:_main out.obj`。

### 6. 无 C 自举（crt0，仅 Linux x86_64）

- **crt0_x86_64.s**：提供 `_start` 与 `driver_get_argv_i`，用于「无 C」构建时替代 main.o / runtime_asm_build.o。
- **_start**：从栈取 argc、argv，对齐栈后调用 `entry`，再以返回值做 exit(60) 系统调用。
- **driver_get_argv_i**：ABI 为 rdi=argc, rsi=argv, rdx=i, rcx=buf, r8=max；从 argv[i] 拷贝到 buf 并 NUL 结尾，返回长度，越界/失败返回 -1。
- Makefile 中已增加 `src/asm/crt0_x86_64.o` 目标（仅 `uname -s == Linux` 时）；链接 asm 版 shu 时可将该 .o 与各 .su 的 asm .o、runtime_panic.o、-lc 一起链接。

---

## 二、开发计划（建议顺序）

1. **arm64 直接出 .o**  
   新增 `arch/arm64_enc.su`（或等效），实现与 x86_64_enc 对等的 enc_* 接口；`asm_codegen_ast_to_elf` 在 `target_arch==1` 时走 arm64 编码并设置 ELF e_machine 等。  
   → 完成后：双架构均支持「出 .s」与「出 .o」。

2. **EXPR_FIELD_ACCESS 真实字段偏移**  
   已实现：backend/enc 使用 `field_access_offset`；C typeck 已填。.su typeck 从 STRUCT_LIT 推导布局（Module.struct_layouts），EXPR_VAR 填 resolved_type_ref（当前块 const/let），EXPR_FIELD_ACCESS 按 base 类型名与字段名查偏移并写入。

3. **EXPR_FLOAT_LIT**  
   已实现：typeck 填 float_bits_lo/hi，文本 asm 与 ELF 路径均用 64 位立即数入 rax/x0。

4. **EXPR_MATCH 多分支**  
   已实现：AST 提供 match_arm_* 与 match_arm_result_refs，backend 按臂发射 cmp/jz 或通配符 result+jmp end，双路径（文本 asm + ELF）均已支持。

5. **EXPR_ENUM_VARIANT 真实 tag**  
   已实现：Expr.enum_variant_tag 由 typeck 填写，backend 返回该 tag；payload 布局仍待类型/变体扩展。

6. **7.3 寄存器分配**
   已实现：窥孔消除连续 push/pop；**二元运算右操作数为 EXPR_LIT 时**（ADD/SUB/MUL/DIV/MOD、比较、BITAND/BITOR/BITXOR、SHL/SHR）在 emit_expr 与 emit_expr_elf 中直接 mov 立即数到 rbx，避免 push rax + emit right + pop rbx。可进一步做活跃分析减少更多 push/pop。

7. **INDEX/FIELD base 为表达式与 slice**  
   已实现：EXPR_INDEX 与 EXPR_FIELD_ACCESS 的 base 可为任意产生地址的表达式；INDEX 的 base 为 slice 时从 (ptr,len) 取 ptr 再下标（双路径均已支持）。

8. **新架构（riscv64）**
   已完整实现：`arch/riscv64.su` 全部 emit_*（.text/.globl/label、prologue/epilogue 含 s0 帧指针、算术/比较/位运算/栈/load/store/lea/call/jz/jnz/jmp、mov_rax_to_arg_reg 等）、`arch/riscv64_enc.su` 全部 enc_*（RV64I 32 位编码、B-type 13 位/J-type 21 位 patch）；types.su 有 TARGET_RISCV64；driver 解析 -target riscv64；backend/elf 分派 ta==2、e_machine=243；elf.su 中 e_machine==243 时 resolve 分支/跳转立即数。

9. **ELF 平台差异（如 macOS）**  
   当前产出 Linux ELF 可重定位 .o；macOS 使用 Mach-O，需单独实现 Mach-O writer 与链接器调用。

---

## 三、目录与职责

| 文件 | 职责 |
|------|------|
| **asm.su** | 对外入口：`asm_codegen_ast`、`asm_codegen_elf_o`；供 pipeline 调用。 |
| **backend.su** | 函数上下文、帧大小与局部槽、emit_expr/emit_expr_elf；按 target_arch 分派 x86_64 / arm64 / riscv64。 |
| **types.su** | TargetArch、CodegenOutBuf、append_asm_line、format_i32_to_buf 等。 |
| **arch/x86_64.su** | x86-64 文本 asm（GAS AT&T）；prologue/epilogue、全部已支持表达式。 |
| **arch/arm64.su** | ARM64 文本 asm（GAS）；与 x86_64 功能对齐。 |
| **arch/x86_64_enc.su** | x86-64 机器码编码，写入 ElfCodegenCtx.code；jz/jmp patch、call reloc。 |
| **platform/elf.su** | ELF64 可重定位 .o 布局、符号、重定位、write_elf_o_to_buf；elf_resolve_patches。 |
| **platform/macho.su** | Mach-O 64 位 MH_OBJECT 写出（macOS）；write_macho_o_to_buf。 |
| **platform/coff.su** | PE/COFF .obj 写出（Windows x86_64）；write_coff_o_to_buf。 |
| **peephole.su** | 窥孔优化，产出后可选执行。 |

---

## 四、流水线中的位置

```
AST (typeck 后) --[asm_codegen_ast]--> 汇编文本 (.s) --[as]--> .o --[ld]--> 可执行文件
                    --[asm_codegen_elf_o]-----------------> .o (仅 x86_64)
```

## 五、与 codegen 的关系

- **codegen/**：AST → C 源码（默认后端）。
- **asm/**：AST → 汇编或 .o；与 codegen 平级，由 driver 根据 `-backend asm` 选择。

## 六、多平台（target_arch）

- **ctx.target_arch**：0=x86_64，1=arm64（aarch64），2=riscv64。
- **x86_64**：文本 asm 与直接 .o 均支持；GAS AT&T，System V ABI。
- **arm64**：文本 asm 与直接 .o 均支持（arm64_enc 已实现，ELF e_machine 等按 AArch64 设置）。
- **riscv64**：文本 asm 与直接 .o 均支持（riscv64.su / riscv64_enc.su 已实现，ELF e_machine=243，B/J 型 patch）。
- **用法**：  
  - 出 .s：`shu -backend asm -target aarch64-linux-gnu -o out.s file.su` 或 `-target riscv64`  
  - 出 .o：`shu -backend asm -o out.o file.su`（x86_64）；`-target aarch64-linux-gnu` / `-target riscv64` 出对应 .o；再 `ld -e _main -o out out.o`。

## 七、依赖

- **ast**：Module、Func、Expr、Block 等。
- **codegen**：CodegenOutBuf；asm 与 codegen 共用同一缓冲区类型。
- pipeline 根据 `ctx.use_asm_backend` 调用 asm 或 codegen；`ctx.target_arch` 由 driver 按 `-target` 设置。

## 八、用法小结

- 出汇编：`shu -backend asm file.su` 或 `shu -backend asm -o out.s file.su`。
- 出 .o（x86_64 或 arm64）：`shu -backend asm -o out.o file.su`（或 `-target aarch64-linux-gnu` 出 arm64 .o）；再 `ld -e _main -o out out.o`。
- **macOS**：`-o out.o` 自动写出 Mach-O；链接用 `ld -e _main -o out out.o -lSystem` 或 `clang -o out out.o`。
- **Windows**：`-target x86_64-pc-windows-msvc`（或含 `windows` 的 triple）且 `-o out.o`/`-o out.obj` 时写出 COFF .obj；链接用 `link /entry:_main out.obj` 或 `lld-link /entry:_main out.obj`。
- 测试：`./tests/run-asm.sh`（含 x86_64 与 arm64 的 .s、.o；macOS 下会检测 Mach-O 并用 ld/clang 链接）。

## 九、构建

- Makefile 的 bootstrap-pipeline 已加 `-L src/asm`；pipeline import asm、backend；backend import arch.x86_64、arch.arm64。新架构在 arch/ 新增 .su 并分派即可。
- **asm_build_list.su**：asm 自举时各模块的编译顺序与 `-L` 库根（LIBROOT）的唯一定义；`scripts/build_shu_asm.sh` 通过 `// LIBROOT:` 与 `// BUILD:` 行读取，后续可将「逐条编译」逻辑迁入 .su（如 driver 调 spawn 执行 shu -backend asm）。

## 十、如何添加新架构（以 riscv64 为例）

1. **types.su**：在 `TargetArch` 中增加 `TARGET_RISCV64`（例如 2）。
2. **arch/riscv64.su**：实现与 x86_64.su 对等的文本 asm 接口（`emit_prologue`、`emit_epilogue`、`emit_push_rax`、`emit_pop_rax`、各 `emit_*` 等），GAS 语法按 RISC-V 约定。
3. **arch/riscv64_enc.su**：实现与 x86_64_enc.su 对等的机器码编码接口（`enc_*`），写入 `ElfCodegenCtx.code`，重定位用 R_RISCV_*。
4. **backend.su**：`import arch.riscv64` 与 `arch.riscv64_enc`；所有 `arch_*`、`enc_*_arch` 分派中增加 `if (ta == 2) return arch.riscv64.*` / `arch.riscv64_enc.*`。
5. **platform/elf.su**：若出 .o，则 `e_machine` 等按 RISC-V ELF 规范设置；必要时增加 R_RISCV_* 重定位处理。
6. **pipeline/driver**：解析 `-target riscv64-linux-gnu`（或等价）时设置 `ctx.target_arch = TARGET_RISCV64`。

参考现有 `arch/x86_64.su`、`arch/arm64.su` 与对应 enc 文件的导出函数列表，逐项实现即可。

---

## 十一、完全脱离 C 依赖：当前状态与路线图

asm 后端已经实现「AST → 汇编 / .o」，**不经过 C 或 LLVM**。但要达到「完全脱离 C」的目标，需要区分三层：**① 谁在编译 shu 自己**、**② 用户用 shu 编译 .su 时是否还用 C**、**③ 生成的可执行程序运行时是否还用 C 库**。

### 当前状态（简要）

| 层次 | 是否还依赖 C | 说明 |
|------|----------------|------|
| **① 构建 shu** | ✅ 仍依赖 | 当前用 `cc` 编译 main.c、runtime.c、parser.c、codegen.c 等得到 shu；自举时 pipeline 产出 C（pipeline_gen.c）再与 C 对象链接。 |
| **② 用户 `shu -o out file.su`（默认）** | ✅ 仍依赖 | 默认走 codegen 出 C → 调 `cc` 得到可执行文件。 |
| **② 用户 `shu -backend asm -o out.o file.su`** | ❌ 不依赖 C 编译器 | 直接出 .s 或 .o，**不生成 C、不调用 cc**；若要可执行文件需**手动** `ld -e _main -o out out.o`（或 macOS/Windows 下对应链接命令）。 |
| **③ 生成程序的运行时** | ✅ 可脱离 libc（Linux） | asm 后端改为 `call shulang_panic_`，链接时加 `runtime_panic.o`（Linux 为 .s 仅 syscall exit，不链 libc；macOS 等用 .c 调 abort 链 -lSystem）。 |

因此：**只要使用 `-backend asm` 且只产出 .o/.s，编译用户代码这一步已经可以不依赖 C 编译器**；尚未脱离的是「构建 shu 自己」和「生成程序对 libc 的依赖」。

### 完全脱离 C 需要满足的条件（按目标拆分）

- **目标 A：用户用 shu 编译 .su 时不再调用 C 编译器**
  - **已满足**：使用 `shu -backend asm -o out.o file.su`，不再生成 C、不调用 cc。
  - **未满足**：若希望「一条命令直接得到可执行文件」且不用 cc，需要 driver 在 asm 产出 .o 后**自动调用系统链接器 `ld`**（或提供 `-o out` 且 `-backend asm` 时内部调 ld），并约定是否链接 libc（见目标 C）。

- **目标 B：构建 shu 本身不再依赖 C 编译器**
  - **未满足**：当前 shu 由 C 源码（main.c、runtime.c、parser.c、typeck.c、codegen.c 等）编译而成；自举路径仍通过 .su → -E 展开成 C（pipeline_gen.c 等）再与 C 对象文件链接。
  - **条件**：  
    1. 编译器前端（lexer/parser/typeck）与 pipeline 已用 .su 实现并可被当前 shu 编译（✅ 已有）；  
    2. **用 asm 后端编译「编译器 .su 源码」**：即用 `shu -backend asm` 为 compiler 的 .su 模块产出 .o，而不是先展开成 C 再交给 cc；  
    3. 用**系统 ld**（或自研链接器）把上述 .o 与**仅含启动/运行时的最小 C 桩**（或将来用 .su 写的 crt0）链接成 shu 可执行文件；  
    4. 若进一步去掉「用 C 写 shu 的 main/runtime 等」，则需在 .su 中实现 driver（读文件、解析 argv、调 pipeline、写 -o、调 ld 等），并由 asm 产出该可执行文件，此时**构建 shu 仅需：已有 shu + 系统 ld**，不再需要 cc。

- **目标 C：生成的可执行程序不再依赖 libc（freestanding）**  
  - **已部分满足**：asm 中 `EXPR_PANIC` 已改为 `call shulang_panic_`；链接时加 `runtime_panic.o`（Linux 为 .s 仅 syscall exit，可不链 libc）。  
  - **可进一步**：若需 print/alloc 等，用 .su 实现并随程序编成 .o；入口、栈、crt0 等由自有 runtime 提供。

### 建议达成顺序（与「完全脱离 C」直接相关）

1. **可选、体验改进**：在 driver 中为 `-backend asm -o out`（out 为可执行文件名）增加「产出 .o 后自动调用 ld」的逻辑，这样用户一条命令得到可执行文件，且仍可不依赖 cc。  
2. **构建 shu 脱离 cc（核心）**：用 `-backend asm` 为 pipeline、parser、typeck、codegen、driver 等 .su 产出 .o，用 ld 与最少 C 桩（或后续 .su crt0）链接成 shu；去掉「pipeline_gen.c + cc」的构建路径。  
3. **运行时脱离 libc（可选）**：asm 中 panic 改为调自有 runtime；提供最小 .su runtime（或 crt0），链接时不依赖 libc，达成 freestanding 可执行文件。

总结：**已经自己写汇编后端且用 `-backend asm` 时，编译用户代码可以完全不依赖 C 编译器**；要「完全脱离 C」还需要：**用 asm 后端构建 shu 自身**（替代当前 C 编译 + -E 生成 C 再 cc 的链路），以及可选地**去掉生成程序对 libc 的依赖**（panic/runtime 自实现）。

### Goal 2 实现计划（用 asm 后端构建 shu，脱离 cc）

1. **准备宿主 shu**：`make bootstrap-driver` 已可产出带 `-backend asm` 的 shu。pipeline_gen.c 由 `-E` 生成，胶水由 runtime.c 在生成时追加到 stdout，无 Makefile/脚本补丁，问题已从根源修。
2. **用 asm 产出编译器 .o**：`scripts/build_shu_asm.sh` 按依赖顺序对 token、ast、codegen、typeck、lexer、preprocess、std.fs、asm 子树、parser、pipeline、main 执行 `shu -backend asm -o build_asm/xxx.o xxx.su`；若全部成功则链接 `runtime_asm_build.o + runtime_driver.o + build_asm/*.o` 得到 shu_asm。
3. **最小 C 桩**：已提供 `src/asm/runtime_asm_build.c`，仅含 `main()` 转调 `entry(argc, argv)`。`make bootstrap-asm` 会生成 `runtime_asm_build.o` 与依赖的 `runtime_driver.o`；完整 asm 自举：`make bootstrap-asm-full`（内部调 build_shu_asm.sh）。
4. **替换构建链路**：当前仍以「-E 生成 pipeline_gen.c + cc 编 pipeline_su.o」为主；asm 路径为可选，通过 `bootstrap-asm-full` 尝试。
5. **验收**：新 shu（或 shu_asm）能通过 `../tests/run-all.sh`，且可再次用 `-backend asm` 编自身 .su 即自举闭环。
