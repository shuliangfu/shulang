/**
 * lsp_codegen_extern.h — LSP -E-extern 跨 TU 符号声明（io.o / heap.o / lsp_io_x.o 桥接）。
 *
 * 声明保留；实现见 runtime_driver_strict_glue_stubs.c（G-02e-11 自 lsp_codegen_extern.c 并入）。
 */
#ifndef XLANG_LSP_CODEGEN_EXTERN_H
#define XLANG_LSP_CODEGEN_EXTERN_H

#include <stdio.h>

struct codegen_CodegenOutBuf;

/** 写入 lsp_io_gen.c 所需的 std.heap typeck 符号别名（C-04 v0：std_io extern 改由 codegen 自动生成）。 */
void lsp_codegen_emit_heap_alias_block(uint8_t *out);

/** @deprecated 使用 codegen import extern + lsp_codegen_emit_heap_alias_block */
void lsp_codegen_emit_io_extern_block(uint8_t *out);

/** 写入 lsp_gen.c 所需的 lsp_io 符号 extern 与 static inline 包装（原 lsp_gen_extern.h 语义）。 */
void lsp_codegen_emit_gen_extern_block(uint8_t *out);

/** 写入 lsp_io_gen.c 所需的 std.heap typeck 链接别名（alloc/free 符号映射）。 */
int lsp_codegen_emit_heap_alias_to_buf(struct codegen_CodegenOutBuf *out);

/** @deprecated 见 lsp_codegen_emit_heap_alias_block */
int lsp_codegen_emit_io_extern_to_buf(struct codegen_CodegenOutBuf *out);

/** 同上 gen 块，写入 CodegenOutBuf。 */
int lsp_codegen_emit_gen_extern_to_buf(struct codegen_CodegenOutBuf *out);

/** entry 路径是否 lsp_io.x 的 -E-extern 入口（C/X 共用判定）。 */
int lsp_codegen_emit_path_is_lsp_io_x(const char *path);

/** entry 路径是否 lsp/lsp.x 的 -E-extern 入口。 */
int lsp_codegen_emit_path_is_lsp_main_x(const char *path);

#endif /* XLANG_LSP_CODEGEN_EXTERN_H */
