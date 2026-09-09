/* Weak 4-arg asm_codegen_ast stand-in (returns 42).
 * Linked after the experimental symbol bridge: before the 4-arg -1 stub
 * was deleted, ELF/Mach-O first-weak-wins picked the stub (rc=-1). */
#include <xlang_weak.h>
#include <stdint.h>

XLANG_WEAK int32_t asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx) {
  (void)module;
  (void)arena;
  (void)out_buf;
  (void)ctx;
  return 42;
}
