/**
 * lsp_io_extern.h — lsp_io_gen.c 用 -E-extern 生成时，std.io/std.heap 仅生成调用不生成声明，本头提供 extern 声明以便编译通过。
 * std_io_* 由 ../std/io/io.o 提供；std_heap_* 由 lsp_io_std_heap.su 生成（typeck_std_heap_alloc/typeck_std_heap_free），此处宏映射以便链接。
 */
#ifndef LSP_IO_EXTERN_H
#define LSP_IO_EXTERN_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t std_io_read(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);
extern int32_t std_io_write(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);
/** 调试 LSP read_message：LSP_READ_DEBUG 时打 leftover 长度 n（仅当 n>0 时由 lsp_io 调用）。codegen 会加 typeck_ 前缀。 */
extern void lsp_debug_u32(uint32_t n);
#define typeck_lsp_debug_u32 lsp_debug_u32
/** 调试：打 state 指针，确认两次调用是否同一地址 */
extern void lsp_debug_ptr(uint8_t *p);
#define typeck_lsp_debug_ptr lsp_debug_ptr
/* std_heap_* 由 lsp_io_std_heap.su → lsp_io_std_heap_su.o 提供，导出名为 typeck_std_heap_alloc / typeck_std_heap_free */
extern uint8_t *typeck_std_heap_alloc(size_t size);
extern void typeck_std_heap_free(uint8_t *ptr);
#define std_heap_alloc typeck_std_heap_alloc
#define std_heap_free typeck_std_heap_free

#ifdef __cplusplus
}
#endif

#endif
