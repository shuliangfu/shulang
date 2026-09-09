/* Weak 5-arg elf_o stand-in (returns 42) for both the unprefixed
 * name and the product PREFIX asm_asm_codegen_elf_o.
 * Before the bridge -1 stub (and its prefix alias) were deleted,
 * ELF/Mach-O first-weak-wins picked the stub (rc=-1). */
#include <xlang_weak.h>
#include <stdint.h>

XLANG_WEAK int32_t asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf) {
  (void)module;
  (void)arena;
  (void)ctx;
  (void)elf_ctx;
  (void)out_buf;
  return 42;
}

XLANG_WEAK int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf) {
  return asm_codegen_elf_o(module, arena, ctx, elf_ctx, out_buf);
}
