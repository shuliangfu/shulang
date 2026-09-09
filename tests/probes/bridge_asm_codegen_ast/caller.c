/* Call unprefixed asm_codegen_ast and the backend_ prefix alias.
 * Expect both 42 from provider.c after the bridge -1 stub is gone. */
#include <stdint.h>
#include <stdio.h>

int32_t asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx);
int32_t backend_asm_codegen_ast(void *module, void *arena, void *out, void *ctx);

int main(void) {
  int32_t direct;
  int32_t via_alias;
  direct = asm_codegen_ast(0, 0, 0, 0);
  via_alias = backend_asm_codegen_ast(0, 0, 0, 0);
  printf("direct=%d alias=%d\n", direct, via_alias);
  if (direct != 42)
    return 1;
  if (via_alias != 42)
    return 2;
  return 0;
}
