/**
 * std/regex/regex.c — 最小正则（P4 可选；委托 regex.h）
 *
 * 【文件职责】compile(pat)、match(re, str, len)、free(re)。POSIX regcomp/regexec/regfree；Windows 暂 stub。
 *
 * 【所属模块/组件】标准库 std.regex；与 std/regex/mod.su 同属一模块。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
/* Windows：无 regex.h，暂 stub。 */
void *regex_compile_c(const uint8_t *pat, int32_t pat_len) {
  (void)pat;
  (void)pat_len;
  return NULL;
}
int32_t regex_match_c(void *re, const uint8_t *str, int32_t len) {
  (void)re;
  (void)str;
  (void)len;
  return -1;
}
void regex_free_c(void *re) {
  (void)re;
}
#else
#include <regex.h>

typedef struct { regex_t re; } regex_impl_t;

void *regex_compile_c(const uint8_t *pat, int32_t pat_len) {
  if (!pat || pat_len <= 0) return NULL;
  regex_impl_t *r = (regex_impl_t *)malloc(sizeof(regex_impl_t));
  if (!r) return NULL;
  char *p = (char *)malloc((size_t)pat_len + 1);
  if (!p) { free(r); return NULL; }
  memcpy(p, pat, (size_t)pat_len);
  p[pat_len] = '\0';
  int err = regcomp(&r->re, p, REG_EXTENDED);
  free(p);
  if (err != 0) { free(r); return NULL; }
  return (void *)r;
}

int32_t regex_match_c(void *re, const uint8_t *str, int32_t len) {
  if (!re || !str) return -1;
  char *s = (char *)malloc((size_t)len + 1);
  if (!s) return -1;
  memcpy(s, str, (size_t)len);
  s[len] = '\0';
  int ret = regexec(&((regex_impl_t *)re)->re, s, 0, NULL, 0);
  free(s);
  return (ret == 0) ? 0 : -1;
}

void regex_free_c(void *re) {
  if (!re) return;
  regfree(&((regex_impl_t *)re)->re);
  free(re);
}
#endif
