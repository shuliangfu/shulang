/**
 * pipeline_glue.c — 与 -E 产出的 pipeline_gen.c 同属一个翻译单元的 C 胶水代码。
 *
 * 用法：pipeline_gen.c 末尾有 #include "pipeline_glue.c"（由 runtime.c -E 或 build_patch 追加），
 * 编译 pipeline_gen.c 时由 cc 在同一 TU 内包含本文件，故可直接使用上方已定义的 ast_* / codegen_* 等类型。
 * 不单独编译；无补丁、无 sed，所有逻辑在此源文件内从根源提供。
 */

/* struct shulang_slice_uint8_t 已由 -E 产出的 pipeline_gen.c 上方定义，不在此重复。 */
#include <stdint.h>
#include <stddef.h>

/** 从 (data, len) 构造 slice，供 parser.su 内 parse_into_buf 调 parse_one_function_impl 时使用。 */
struct shulang_slice_uint8_t parser_slice_from_buf(uint8_t *data, int32_t len) {
  struct shulang_slice_uint8_t s;
  s.data = data;
  s.length = (size_t)(len >= 0 ? len : 0);
  return s;
}

/* C 包装：以 (data, len) 形式调用 pipeline，内部组 slice 后调 impl；形参顺序 (module, arena) 与 runtime.c 调用及 _impl 一致。 */
extern int32_t pipeline_run_su_pipeline_impl(struct ast_Module *module, struct ast_ASTArena *arena, struct shulang_slice_uint8_t *source, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx);

int32_t pipeline_run_su_pipeline(struct ast_Module *module, struct ast_ASTArena *arena, const uint8_t *source_data, size_t source_len, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx) {
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

/** 诊断：解析 entry 后打印 main 的 body_ref；日常构建关闭，排查 main 空体时取消下方注释。由 pipeline.su 在 parse 后 / codegen 前调用。 */
void driver_diagnostic_entry_module(struct ast_Module *mod, struct ast_ASTArena *a) {
  (void)a;
  (void)mod;
  /* if (mod->main_func_index >= 0 && mod->main_func_index < mod->num_funcs) {
    int32_t br = mod->funcs[mod->main_func_index].body_ref;
    fprintf(stderr, "[diag] entry num_funcs=%d main_idx=%d body_ref=%d\n",
            (int)mod->num_funcs, (int)mod->main_func_index, (int)br);
  } else {
    fprintf(stderr, "[diag] entry num_funcs=%d main_idx=%d (invalid)\n",
            (int)mod->num_funcs, (int)mod->main_func_index);
  } */
}

/** 诊断：解析后打印 main 对应 body block 的 num_stmt_order（C 侧调用）；日常构建保留实现不调用，排查时在 runtime.c 恢复调用。 */
void driver_diagnostic_entry_block_after_parse(void *mod, void *arena) {
  struct ast_Module *m = (struct ast_Module *)mod;
  struct ast_ASTArena *a = (struct ast_ASTArena *)arena;
  if (!m || !a || m->main_func_index < 0 || m->main_func_index >= m->num_funcs)
    return;
  int32_t br = m->funcs[m->main_func_index].body_ref;
  if (br <= 0 || br > a->num_blocks)
    return;
  (void)br;
  (void)a;
  /* struct ast_Block b = ast_ast_arena_block_get(a, br);
  fprintf(stderr, "[diag] after_parse body_ref=%d num_blocks=%d block.num_stmt_order=%d\n",
          (int)br, (int)a->num_blocks, (int)b.num_stmt_order); */
}

/* std.io.driver 批量读写桩：pipeline_gen.c 同 TU 已定义 struct std_io_driver_Buffer；io.o 提供 io_read_batch_buf/io_write_batch_buf，供 shu_su 链接时解析。 */
extern ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);
extern ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);

int32_t std_io_driver_submit_read_batch_buf(size_t handle, struct std_io_driver_Buffer *bufs, int32_t n, uint32_t timeout_ms) {
  ptrdiff_t r = io_read_batch_buf((int)handle, bufs, n, timeout_ms);
  return (r < 0) ? -1 : (int32_t)r;
}

int32_t std_io_driver_submit_write_batch_buf(size_t handle, struct std_io_driver_Buffer *bufs, int32_t n, uint32_t timeout_ms) {
  ptrdiff_t r = io_write_batch_buf((int)handle, bufs, n, timeout_ms);
  return (r < 0) ? -1 : (int32_t)r;
}
