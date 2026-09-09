/* Call unprefixed asm_codegen_elf_o and the asm_asm_ prefix alias.
 * Expect both 42 from provider.c after the bridge -1 stub is gone. */
#include <stdint.h>
#include <stdio.h>

int32_t asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf);
int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf);

int main(void) {
  int32_t direct;
  int32_t via_alias;
  direct = asm_codegen_elf_o(0, 0, 0, 0, 0);
  via_alias = asm_asm_codegen_elf_o(0, 0, 0, 0, 0);
  printf("direct=%d alias=%d\n", direct, via_alias);
  if (direct != 42)
    return 1;
  if (via_alias != 42)
    return 2;
  return 0;
}
