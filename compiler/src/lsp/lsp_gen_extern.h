/**
 * lsp_gen_extern.h — lsp_gen.c 用 -E-extern 生成时，lsp_io 仅生成调用不生成声明；且 lsp_io_su.o 导出 typeck_* 前缀，本头提供 lsp_io_* 的包装声明以便编译并解析到 typeck_*。
 */
#ifndef LSP_GEN_EXTERN_H
#define LSP_GEN_EXTERN_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern ptrdiff_t typeck_read_message(int32_t fd, uint8_t *body_out, int32_t body_cap, uint8_t *state_buf);
extern ptrdiff_t typeck_write_fd(int32_t fd, uint8_t *ptr, size_t count);
extern uint8_t *typeck_lsp_alloc(size_t size);
extern void typeck_lsp_free(uint8_t *ptr);
extern int32_t typeck_lsp_is_null(uint8_t *ptr);
extern int32_t typeck_extract_document_text(uint8_t *body, int32_t body_len, uint8_t *out_buf, int32_t out_cap);

static inline ptrdiff_t lsp_io_read_message(int32_t fd, uint8_t *body_out, int32_t body_cap, uint8_t *state_buf) {
  return typeck_read_message(fd, body_out, body_cap, state_buf);
}
static inline ptrdiff_t lsp_io_write_fd(int32_t fd, uint8_t *ptr, size_t count) {
  return typeck_write_fd(fd, ptr, count);
}
static inline uint8_t *lsp_io_lsp_alloc(size_t size) {
  return typeck_lsp_alloc(size);
}
static inline void lsp_io_lsp_free(uint8_t *ptr) {
  typeck_lsp_free(ptr);
}
static inline int32_t lsp_io_lsp_is_null(uint8_t *ptr) {
  return typeck_lsp_is_null(ptr);
}
static inline int32_t lsp_io_extract_document_text(uint8_t *body, int32_t body_len, uint8_t *out_buf, int32_t out_cap) {
  return typeck_extract_document_text(body, body_len, out_buf, out_cap);
}

#ifdef __cplusplus
}
#endif

#endif
