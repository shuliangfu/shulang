/**
 * pipeline_glue.c — 与 -E 产出的 pipeline_gen.c 一起参与编译的 C 胶水代码。
 *
 * 用法：由 Makefile 在生成 pipeline_gen.c 后追加到其末尾（cat pipeline_glue.c >> pipeline_gen.c），
 * 与 -E 产出同属一个翻译单元，故可直接使用上方已定义的 ast_* / codegen_* / platform_elf_* 等类型。
 * 不单独编译；无补丁、无 sed，所有逻辑在此源文件内从根源提供。
 */

/* struct shulang_slice_uint8_t 已由 -E 产出的 pipeline_gen.c 上方定义，不在此重复。 */
#include <stdint.h>
#include <stddef.h>

/* C 包装：以 (data, len) 形式调用 pipeline，内部组 slice 后调 impl；供需要此签名的 C 调用方使用。 */
extern int32_t pipeline_run_su_pipeline_impl(struct ast_Module *module, struct ast_ASTArena *arena, struct shulang_slice_uint8_t *source, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx);

int32_t pipeline_run_su_pipeline(struct ast_ASTArena *arena, struct ast_Module *module, const uint8_t *source_data, size_t source_len, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx) {
  struct shulang_slice_uint8_t source;
  source.data = (uint8_t *)source_data;
  source.length = source_len;
  return pipeline_run_su_pipeline_impl(module, arena, &source, out_buf, ctx);
}

size_t pipeline_sizeof_arena(void) { return sizeof(struct ast_ASTArena); }
size_t pipeline_sizeof_module(void) { return sizeof(struct ast_Module); }
size_t pipeline_arena_offset_num_types(void) { return offsetof(struct ast_ASTArena, num_types); }
size_t pipeline_sizeof_elf_ctx(void) { return sizeof(struct platform_elf_ElfCodegenCtx); }

#include <stdio.h>
void pipeline_debug_module_funcs(void *m) {
  struct ast_Module *mod = (struct ast_Module *)m;
  int i, n = (int)mod->num_funcs;
  if (n > 256) n = 256;
  for (i = 0; i < n; i++) {
    int len = (int)mod->funcs[i].name_len;
    fprintf(stderr, "[DEBUG] module func[%d] name_len=%d name=%.*s\n", i, len, len > 0 && len <= 64 ? len : 0, mod->funcs[i].name);
  }
}
