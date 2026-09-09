/* seeds/rt_asm_stub.from_x.c — G-02f-300 P2 runtime R9 → R2 full (asm GAS stub)
 * Logic source: src/runtime/rt_asm_stub.x
 * Hybrid: XLANG_RT_ASM_STUB_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：want_exe + asm_codegen_ast 由 .x 提供；
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual（driver_abi wave14）：GAS 行表 + CodegenOutBuf append 访问器。
 * 冷启动/无 PREFER 时仍编译完整 C 体（含 XLANG_WEAK asm_codegen_ast）。
 * 9.7.3 G.7：冷体 asm_codegen_ast 与 .x 权威同构——循环 gas_line_count() 次
 * gas_line_at(i) + out_append_cstr(out, line)，不再自持第二份 GAS 表与内联
 * append（行表/append 唯一权威 = wave14 访问器：.x thin + 本文件冷孪生已收敛）。
 *
 * Scope: weak minimal GAS codegen stub + want_exe gate.
 * Full elf/macho asm backend remains mega/backend.
 */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>

extern int xlang_output_want_exe(const char *path);
/* wave14 accessors: authority = runtime_driver_abi_thin.x; cold twin in
 * seeds/runtime_driver_abi.from_x.c (under !XLANG_L2_RDABI_THIN_FROM_X);
 * decls also in src/runtime_driver_abi.h. PLATFORM: SHARED. */
extern uint8_t *driver_asm_stub_gas_line_at(int32_t i);
extern int32_t driver_asm_stub_gas_line_count(void);
extern int32_t driver_asm_stub_out_append_cstr(void *out, uint8_t *s);

#ifndef XLANG_RT_ASM_STUB_FROM_X

/** compile.x extern：-o 后缀是否表示可执行（非 .o/.obj/.s）。 */
int32_t driver_asm_output_want_exe(uint8_t *path) {
  return xlang_output_want_exe(path ? (const char *)path : NULL);
}

/**
 * asm 后端 C 桩：-backend asm 时由 pipeline 调用，写出最小 GAS（main return 42）。
 * 9.7.3 G.7：行表与 append 唯一权威在 wave14 访问器，本 cold twin 与
 * 实验 asm-only 链并入 build_asm/backend.o 时须为 weak，避免与 backend.x 重复定义。
 */
XLANG_WEAK int32_t asm_codegen_ast(void *module, void *arena, void *out) {
  int32_t n;
  int32_t i;
  (void)module;
  (void)arena;
  if (!out)
    return -1;
  n = driver_asm_stub_gas_line_count();
  for (i = 0; i < n; i++) {
    if (driver_asm_stub_out_append_cstr(out, driver_asm_stub_gas_line_at(i)) != 0)
      return -1;
  }
  return 0;
}

#else
int32_t driver_asm_output_want_exe(uint8_t *path);
int32_t asm_codegen_ast(void *module, void *arena, void *out);
#endif

int labi_rt_asm_stub_slice_marker(void) {
  return 1;
}
