/**
 * std/json/json.c — JSON 最小解析与生成（对标 Zig std.json、Rust serde_json）
 *
 * 【文件职责】解析 number/bool/null/string；生成 number、bool、null、转义字符串。单遍、无 sscanf，性能优先。
 * 【API 对标】Zig parseFromSlice；Rust serde_json::from_str / to_string。仅最小子集，无大依赖。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** 手写 double 解析（单遍、无 sscanf）：[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?。*consumed 写入消费字节数；成功返回 0。 */
int32_t json_parse_number_c(const uint8_t *ptr, int32_t len, double *out_val, int32_t *consumed) {
  if (!ptr || len <= 0 || !out_val || !consumed) return -1;
  *consumed = 0;
  int32_t i = 0;
  int neg = 0;
  if (ptr[i] == '-') { neg = 1; i++; }
  else if (ptr[i] == '+') i++;
  if (i >= len || ptr[i] < '0' || ptr[i] > '9') return -1;
  uint64_t mantissa = 0;
  while (i < len && ptr[i] >= '0' && ptr[i] <= '9') {
    mantissa = mantissa * 10 + (ptr[i] - '0');
    i++;
  }
  double val = (double)mantissa;
  if (i < len && ptr[i] == '.') {
    i++;
    double frac = 0.0;
    double div = 1.0;
    while (i < len && ptr[i] >= '0' && ptr[i] <= '9') {
      frac = frac * 10.0 + (double)(ptr[i] - '0');
      div *= 10.0;
      i++;
    }
    val += frac / div;
  }
  if (i < len && (ptr[i] == 'e' || ptr[i] == 'E')) {
    i++;
    int exp_neg = 0;
    if (i < len && (ptr[i] == '-' || ptr[i] == '+')) { exp_neg = (ptr[i] == '-'); i++; }
    int exp = 0;
    while (i < len && ptr[i] >= '0' && ptr[i] <= '9') { exp = exp * 10 + (ptr[i] - '0'); if (exp > 999) break; i++; }
    if (exp_neg) exp = -exp;
    if (exp > 308) exp = 308;
    if (exp < -308) exp = -308;
    double scale = 1.0;
    while (exp > 0) { scale *= 10.0; exp--; }
    while (exp < 0) { scale *= 0.1; exp++; }
    val *= scale;
  }
  if (neg) val = -val;
  *out_val = val;
  *consumed = i;
  return 0;
}

int32_t json_parse_null_c(const uint8_t *ptr, int32_t len, int32_t *consumed) {
  if (!ptr || len < 4 || !consumed) return 0;
  if (ptr[0]=='n'&&ptr[1]=='u'&&ptr[2]=='l'&&ptr[3]=='l') { *consumed = 4; return 1; }
  return 0;
}

int32_t json_parse_bool_c(const uint8_t *ptr, int32_t len, int32_t *out, int32_t *consumed) {
  if (!ptr || len < 4 || !out || !consumed) return 0;
  if (len >= 4 && ptr[0]=='t'&&ptr[1]=='r'&&ptr[2]=='u'&&ptr[3]=='e') { *out = 1; *consumed = 4; return 1; }
  if (len >= 5 && ptr[0]=='f'&&ptr[1]=='a'&&ptr[2]=='l'&&ptr[3]=='s'&&ptr[4]=='e') { *out = 0; *consumed = 5; return 1; }
  return 0;
}

/** 解析 JSON 字符串 "..."（含 \\ \" \/ \b \f \n \r \t \uXXXX）；*consumed 含前后引号；内容写入 out，最多 out_cap；返回内容长度，失败 -1。 */
int32_t json_parse_string_c(const uint8_t *ptr, int32_t len, uint8_t *out, int32_t out_cap, int32_t *consumed) {
  if (!ptr || len < 2 || ptr[0] != '"' || !consumed) return -1;
  int32_t i = 1;
  int32_t o = 0;
  while (i < len && ptr[i] != '"') {
    if (ptr[i] == '\\') {
      i++;
      if (i >= len) return -1;
      if (o >= out_cap) return -1;
      if (ptr[i] == '"') out[o++] = '"';
      else if (ptr[i] == '\\') out[o++] = '\\';
      else if (ptr[i] == '/') out[o++] = '/';
      else if (ptr[i] == 'b') out[o++] = '\b';
      else if (ptr[i] == 'f') out[o++] = '\f';
      else if (ptr[i] == 'n') out[o++] = '\n';
      else if (ptr[i] == 'r') out[o++] = '\r';
      else if (ptr[i] == 't') out[o++] = '\t';
      else if (ptr[i] == 'u' && i + 4 < len) {
        uint32_t u = 0;
        for (int k = 0; k < 4; k++) {
          uint8_t c = ptr[i+1+k];
          if (c >= '0' && c <= '9') u = (u << 4) + (c - '0');
          else if (c >= 'a' && c <= 'f') u = (u << 4) + (c - 'a' + 10);
          else if (c >= 'A' && c <= 'F') u = (u << 4) + (c - 'A' + 10);
          else return -1;
        }
        i += 4;
        if (u <= 0x7fu) out[o++] = (uint8_t)u;
        else if (u <= 0x7ffu) {
          if (o + 2 > out_cap) return -1;
          out[o++] = (uint8_t)(0xc0u | (u >> 6));
          out[o++] = (uint8_t)(0x80u | (u & 0x3fu));
        } else if (u <= 0xffffu) {
          if (o + 3 > out_cap) return -1;
          out[o++] = (uint8_t)(0xe0u | (u >> 12));
          out[o++] = (uint8_t)(0x80u | ((u >> 6) & 0x3fu));
          out[o++] = (uint8_t)(0x80u | (u & 0x3fu));
        } else return -1;
        i++;
        continue;
      } else return -1;
      i++;
    } else {
      if (ptr[i] < 0x20) return -1;
      if (o >= out_cap) return -1;
      out[o++] = ptr[i++];
    }
  }
  if (i >= len || ptr[i] != '"') return -1;
  *consumed = i + 1;
  return o;
}

/** 将 ptr[0..len] 按 JSON 字符串转义写入 buf（含前后引号）；返回写入长度，不足 -1。 */
int32_t json_escape_c(const uint8_t *ptr, int32_t len, uint8_t *buf, int32_t buf_cap) {
  if (!ptr || !buf || buf_cap < 2) return -1;
  int32_t i = 0;
  buf[i++] = '"';
  for (int32_t j = 0; j < len && i < buf_cap - 1; j++) {
    uint8_t c = ptr[j];
    if (c == '"') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = '"'; }
    else if (c == '\\') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = '\\'; }
    else if (c == '\n') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = 'n'; }
    else if (c == '\r') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = 'r'; }
    else if (c == '\t') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = 't'; }
    else if (c == '\b') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = 'b'; }
    else if (c == '\f') { if (i + 2 > buf_cap) return -1; buf[i++] = '\\'; buf[i++] = 'f'; }
    else buf[i++] = c;
  }
  if (i >= buf_cap - 1) return -1;
  buf[i++] = '"';
  return i;
}

/** 追加 "null" 到 buf；返回 4，不足 -1。 */
int32_t json_append_null_c(uint8_t *buf, int32_t buf_cap) {
  if (!buf || buf_cap < 4) return -1;
  buf[0] = 'n'; buf[1] = 'u'; buf[2] = 'l'; buf[3] = 'l';
  return 4;
}

/** 追加 "true" 或 "false" 到 buf；返回写入长度，不足 -1。 */
int32_t json_append_bool_c(uint8_t *buf, int32_t buf_cap, int32_t val) {
  if (!buf || buf_cap < 5) return -1;
  if (val) { buf[0]='t';buf[1]='r';buf[2]='u';buf[3]='e'; return 4; }
  buf[0]='f';buf[1]='a';buf[2]='l';buf[3]='s';buf[4]='e'; return 5;
}

/** 将 number 追加为 JSON 到 buf（%.16g 风格，无 sscanf）；返回写入长度，不足 -1。 */
int32_t json_append_number_c(uint8_t *buf, int32_t buf_cap, double val) {
  if (!buf || buf_cap <= 0) return -1;
  int32_t i = 0;
  if (val < 0) { buf[i++] = '-'; val = -val; }
  if (val != val) { if (buf_cap - i < 3) return -1; buf[i++]='n';buf[i++]='a';buf[i++]='n'; return i; }
  if (val == 1.0/0.0 || val == -1.0/0.0) { if (buf_cap - i < 3) return -1; buf[i++]='i';buf[i++]='n';buf[i++]='f'; return i; }
  uint64_t u = (uint64_t)val;
  if ((double)u == val && u <= 9999999999999999ULL) {
    uint64_t t = u;
    uint8_t d[20];
    int nd = 0;
    do { d[nd++] = (uint8_t)('0' + (t % 10)); t /= 10; } while (t);
    if (i + nd > buf_cap) return -1;
    while (nd--) buf[i++] = d[nd];
    return i;
  }
  double frac = val - (double)(uint64_t)val;
  if (frac < 0) frac = -frac;
  if (val >= 1e-3 && val < 1e16) {
    uint64_t ip = (uint64_t)val;
    uint8_t d[20];
    int nd = 0;
    uint64_t t = ip;
    do { d[nd++] = (uint8_t)('0' + (t % 10)); t /= 10; } while (t);
    if (i + nd > buf_cap) return -1;
    while (nd--) buf[i++] = d[nd];
    if (frac > 1e-15) {
      if (i >= buf_cap - 1) return -1;
      buf[i++] = '.';
      for (int k = 0; k < 15 && i < buf_cap; k++) {
        frac *= 10;
        int digit = (int)frac;
        buf[i++] = (uint8_t)('0' + digit);
        frac -= digit;
        if (frac < 1e-15) break;
      }
    }
    return i;
  }
  int exp = 0;
  while (val >= 10.0) { val *= 0.1; exp++; }
  while (val < 1.0 && val > 0) { val *= 10.0; exp--; }
  if (i >= buf_cap) return -1;
  buf[i++] = (uint8_t)('0' + (int)val);
  val -= (int)val;
  if (i < buf_cap && (val > 1e-15 || exp != 0)) buf[i++] = '.';
  for (int k = 0; k < 14 && i < buf_cap; k++) {
    val *= 10;
    int digit = (int)val;
    buf[i++] = (uint8_t)('0' + digit);
    val -= digit;
    if (val < 1e-15) break;
  }
  if (exp != 0 && buf_cap - i >= 2) {
    buf[i++] = 'e';
    if (exp < 0) { buf[i++] = '-'; exp = -exp; }
    else buf[i++] = '+';
    int en = 0;
    uint8_t ed[4];
    do { ed[en++] = (uint8_t)('0' + (exp % 10)); exp /= 10; } while (exp && en < 4);
    while (en-- && i < buf_cap) buf[i++] = ed[en];
  }
  return i;
}
