/**
 * std/csv/csv.c — CSV 按行解析与写回（P4 可选）
 *
 * 【文件职责】next_field：在 ptr[0..len] 内找下一字段（逗号或换行分隔），写回 start 与 field_len；escape：引号包裹并转义。
 *
 * 【所属模块/组件】标准库 std.csv；依赖 std.string、std.io；与 std/csv/mod.su 同属一模块。
 */

#include <stdint.h>

/**
 * 从 offset 起找下一字段（RFC 4180）。
 * - 若以 " 开头：字段到下一个未转义的 " 结束，内部 "" 表示一个 "，可含逗号与换行。
 * - 否则：到逗号或 \\n 或 \\r\\n 结束。
 * *out_start=字段内容起始，*out_len=内容长度（引号内为 raw，含 "" 两字节）；返回下一 offset。
 */
int32_t csv_next_field_c(const uint8_t *ptr, int32_t len, int32_t offset, int32_t *out_start, int32_t *out_len) {
  if (!ptr || len < 0 || offset < 0 || !out_start || !out_len) return offset >= 0 && offset <= len ? offset : len;
  if (offset >= len) { *out_start = len; *out_len = 0; return len; }

  /* RFC 4180 引号字段：以 " 开始，到未转义 " 结束，"" 为转义引号 */
  if (ptr[offset] == '"') {
    int32_t start = offset + 1;
    int32_t pos = start;
    while (pos < len) {
      if (ptr[pos] == '"') {
        if (pos + 1 < len && ptr[pos + 1] == '"') { pos += 2; continue; }
        break;
      }
      pos++;
    }
    *out_start = start;
    *out_len = pos - start;
    offset = pos + 1;
    if (offset < len && (ptr[offset] == ',' || ptr[offset] == '\n' || ptr[offset] == '\r')) {
      if (ptr[offset] == ',') offset++;
      else if (ptr[offset] == '\r') { offset++; if (offset < len && ptr[offset] == '\n') offset++; }
      else offset++;
    }
    return offset;
  }

  *out_start = offset;
  while (offset < len && ptr[offset] != ',' && ptr[offset] != '\n' && ptr[offset] != '\r') offset++;
  *out_len = offset - *out_start;
  if (offset < len) {
    if (ptr[offset] == ',') offset++;
    else if (ptr[offset] == '\r') { offset++; if (offset < len && ptr[offset] == '\n') offset++; }
    else if (ptr[offset] == '\n') offset++;
  }
  return offset;
}

/** 将 ptr[0..len] 转义写入 buf（含引号、内部 " 双写）；最多写 buf_cap 字节。返回写入长度，不足返回 -1。 */
int32_t csv_escape_c(const uint8_t *ptr, int32_t len, uint8_t *buf, int32_t buf_cap) {
  if (!ptr || !buf || buf_cap < 2) return -1;
  int32_t i = 0;
  buf[i++] = '"';
  for (int32_t j = 0; j < len && i < buf_cap - 1; j++) {
    if (ptr[j] == '"') { if (i + 2 > buf_cap) return -1; buf[i++] = '"'; buf[i++] = '"'; }
    else buf[i++] = ptr[j];
  }
  if (i >= buf_cap - 1) return -1;
  buf[i++] = '"';
  return i;
}

/** 将 RFC 4180 引号字段的 raw 内容（"" → "）写入 buf，返回写入长度，不足返回 -1。 */
int32_t csv_unescape_c(const uint8_t *ptr, int32_t len, uint8_t *buf, int32_t buf_cap) {
  if (!ptr || !buf || buf_cap < 0) return -1;
  int32_t i = 0;
  for (int32_t j = 0; j < len; j++) {
    if (ptr[j] == '"' && j + 1 < len && ptr[j + 1] == '"') { if (i >= buf_cap) return -1; buf[i++] = '"'; j++; }
    else { if (i >= buf_cap) return -1; buf[i++] = ptr[j]; }
  }
  return i;
}
