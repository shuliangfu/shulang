/**
 * std/tar/tar.c — tar 归档 UStar 头读写（P4 可选；对标 Zig std.tar、Rust tar crate）
 *
 * 【文件职责】read_header/write_header：512 字节 UStar 头，name/size/typeflag/checksum；不处理长名（prefix）。
 * 【所属模块/组件】标准库 std.tar；与 std/tar/mod.su 同属一模块。
 */

#include <stdint.h>
#include <string.h>

#define TAR_HEADER_SIZE 512
#define TAR_NAME_OFF    0
#define TAR_NAME_LEN    100
#define TAR_SIZE_OFF    124
#define TAR_SIZE_LEN    12
#define TAR_CHKSUM_OFF  148
#define TAR_CHKSUM_LEN  8
#define TAR_TYPEFLAG_OFF 156
#define TAR_MAGIC_OFF   257
#define TAR_VERSION_OFF 263

/** 将 12 字节八进制字符串解析为非负整数（可含前导空格）；失败返回 -1。 */
static int64_t parse_octal_12(const uint8_t *p) {
  int i = 0;
  while (i < TAR_SIZE_LEN && (p[i] == ' ' || p[i] == 0)) i++;
  int64_t v = 0;
  for (; i < TAR_SIZE_LEN; i++) {
    if (p[i] == 0 || p[i] == ' ') break;
    if (p[i] < '0' || p[i] > '7') return -1;
    v = v * 8 + (p[i] - '0');
  }
  return v;
}

/** 将 size 写成 12 字节八进制（右对齐，前导空格），不写 NUL。 */
static void write_octal_12(uint8_t *p, int64_t size) {
  if (size < 0) size = 0;
  int i = TAR_SIZE_LEN - 1;
  for (; i >= 0; i--) {
    p[i] = (uint8_t)('0' + (size % 8));
    size /= 8;
    if (size == 0) break;
  }
  while (i > 0) { i--; p[i] = ' '; }
}

/**
 * 从 buf 读取 UStar 头（至少 512 字节）：写入 name_out（最多 name_cap-1 字节 + NUL），*size_out 为文件大小；返回 0 成功，-1 失败。
 */
int32_t tar_read_header_c(const uint8_t *buf, int32_t len, uint8_t *name_out, int32_t name_cap, int32_t *size_out) {
  if (!buf || len < TAR_HEADER_SIZE || !name_out || name_cap <= 0 || !size_out) return -1;
  if (buf[TAR_MAGIC_OFF] != 'u' || buf[TAR_MAGIC_OFF+1] != 's' || buf[TAR_MAGIC_OFF+2] != 't' ||
      buf[TAR_MAGIC_OFF+3] != 'a' || buf[TAR_MAGIC_OFF+4] != 'r' || buf[TAR_MAGIC_OFF+5] != 0)
    return -1;
  if (buf[TAR_VERSION_OFF] != '0' || buf[TAR_VERSION_OFF+1] != '0') return -1;

  /* 校验和：头 512 字节之和，148-156 按空格算；存的是 6 位八进制 + NUL + 空格 */
  uint32_t sum = 0;
  for (int i = 0; i < TAR_HEADER_SIZE; i++) {
    if (i >= TAR_CHKSUM_OFF && i < TAR_CHKSUM_OFF + TAR_CHKSUM_LEN)
      sum += (uint8_t)' ';
    else
      sum += buf[i];
  }
  uint32_t stored_chk = 0;
  for (int i = 0; i < 6 && TAR_CHKSUM_OFF + i < len; i++) {
    if (buf[TAR_CHKSUM_OFF + i] >= '0' && buf[TAR_CHKSUM_OFF + i] <= '7')
      stored_chk = stored_chk * 8 + (buf[TAR_CHKSUM_OFF + i] - '0');
  }
  if (stored_chk != sum) return -1;

  int32_t name_len = 0;
  while (name_len < TAR_NAME_LEN && buf[TAR_NAME_OFF + name_len] != 0) name_len++;
  if (name_len >= name_cap) name_len = name_cap - 1;
  memcpy(name_out, buf + TAR_NAME_OFF, (size_t)name_len);
  name_out[name_len] = '\0';

  int64_t sz = parse_octal_12(buf + TAR_SIZE_OFF);
  if (sz < 0 || sz > 0x7FFFFFFF) return -1;
  *size_out = (int32_t)sz;
  return 0;
}

/**
 * 向 buf 写入 512 字节 UStar 头：name（最多 100 字节）、file_size；typeflag='0'（普通文件）。返回 0 成功，-1 失败。
 */
int32_t tar_write_header_c(uint8_t *buf, int32_t buf_cap, const uint8_t *name, int32_t name_len, int32_t file_size) {
  if (!buf || buf_cap < TAR_HEADER_SIZE || !name || name_len < 0) return -1;
  if (name_len > TAR_NAME_LEN) name_len = TAR_NAME_LEN;

  memset(buf, 0, (size_t)TAR_HEADER_SIZE);
  memcpy(buf + TAR_NAME_OFF, name, (size_t)name_len);
  write_octal_12(buf + TAR_SIZE_OFF, (int64_t)file_size);
  buf[TAR_TYPEFLAG_OFF] = '0';
  memcpy(buf + TAR_MAGIC_OFF, "ustar", 5);
  buf[TAR_MAGIC_OFF + 5] = 0;
  buf[TAR_VERSION_OFF] = '0';
  buf[TAR_VERSION_OFF + 1] = '0';

  /* mode/uid/gid/mtime 可留 0；checksum 最后写 */
  uint32_t sum = 0;
  for (int i = 0; i < TAR_HEADER_SIZE; i++) {
    if (i >= TAR_CHKSUM_OFF && i < TAR_CHKSUM_OFF + TAR_CHKSUM_LEN)
      sum += (uint8_t)' ';
    else
      sum += buf[i];
  }
  /* 6 位八进制 MSB 先：digit_i = (sum/8^(5-i))%8，即 sum/8^5, sum/8^4, ..., sum/8, sum%8 */
  buf[TAR_CHKSUM_OFF + 0] = (uint8_t)('0' + (sum / 0100000 % 8));  /* 8^5 */
  buf[TAR_CHKSUM_OFF + 1] = (uint8_t)('0' + (sum / 010000 % 8));  /* 8^4 */
  buf[TAR_CHKSUM_OFF + 2] = (uint8_t)('0' + (sum / 01000 % 8));   /* 8^3 */
  buf[TAR_CHKSUM_OFF + 3] = (uint8_t)('0' + (sum / 0100 % 8));    /* 8^2 */
  buf[TAR_CHKSUM_OFF + 4] = (uint8_t)('0' + (sum / 010 % 8));     /* 8^1 */
  buf[TAR_CHKSUM_OFF + 5] = (uint8_t)('0' + (sum % 8));           /* 8^0 */
  buf[TAR_CHKSUM_OFF + 6] = 0;
  buf[TAR_CHKSUM_OFF + 7] = ' ';
  return 0;
}
