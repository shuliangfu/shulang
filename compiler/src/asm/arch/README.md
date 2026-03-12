# asm/arch/ — 多平台汇编架构

本目录按**目标架构**拆分，每个平台一个 `.su` 文件，由 backend 根据 `ctx.target_arch` 分派，便于扩展且不污染 asm 根目录。

## 当前平台

| 文件 | 架构 | 说明 |
|------|------|------|
| **x86_64.su** | x86-64 (AMD64) | GAS AT&T、System V ABI；完整表达式与控制流。 |
| **arm64.su** | ARM64 (AArch64) | GAS、AAPCS64；与 x86_64 对等的完整表达式、控制流、多函数、局部变量。 |

## 扩展新平台

1. 在本目录新增 `<arch>.su`（如 `riscv64.su`）。
2. 在 `types.su` 的 `TargetArch` 枚举中增加对应值。
3. 在 `backend.su` 中 `import arch.<arch>`，并在各 `arch_*` 辅助函数中增加 `ta == 新枚举值` 分支，调用新模块的对应 emit。
4. 在 driver/runtime 中根据 `-target` 设置 `ctx.target_arch`。

### 新架构须实现的 emit_*（与 backend arch_* 一一对应）

| 类别 | 函数 | 说明 |
|------|------|------|
| 字面/返回 | emit_ret_imm32 | 立即数入返回值寄存器并准备 ret |
| 一元 | emit_neg_eax, emit_test_eax_eax, emit_setz_movzbl_eax | 取负、测零、逻辑非 |
| 栈临时 | emit_push_rax, emit_pop_rax, emit_pop_rbx | 保存/恢复左值（二元运算用） |
| 二元 | emit_add_rax_rbx, emit_sub_rbx_rax_then_mov, emit_imul_rbx_rax | 加/减/乘 |
| 除余 | emit_mov_rax_to_rbx, emit_cltd(可 no-op), emit_idiv_rbx | 除；MOD 另需 emit_rem_w0_w1（或等价） |
| 局部 | emit_load_rbp_to_rax, emit_store_rax_to_rbp | 帧指针偏移存取 |
| 调用/控制流 | emit_call, emit_jz, emit_jmp, emit_label | 调用、条件跳、无条件跳、标签 |
| 框架 | emit_section_text, emit_globl, emit_prologue, emit_epilogue | 段/全局/序言/尾声 |
