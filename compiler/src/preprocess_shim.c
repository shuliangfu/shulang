/**
 * preprocess_shim.c — 提供 preprocess_preprocess_su_buf 符号供 driver/pipeline 链接。
 * -E-extern 生成的 preprocess_gen.c 导出 typeck_preprocess_su_buf，此处做名称桥接。
 */

#include <stdint.h>
#include <stddef.h>

extern int32_t typeck_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);

int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap) {
  return typeck_preprocess_su_buf(source_buf, source_len, out_buf, out_cap);
}
