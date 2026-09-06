/* seeds/rt_argv.from_x.c — G-02f-263 P2 R1 argv 令牌比较切片
 * Logic source: src/runtime/rt_argv.x
 * Hybrid: XLANG_RT_ARGV_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2（2026-07-14）：15 公共符号（drv_eq_* / path_ends_x / target_has_arm）
 * 均由 .x 提供；FROM_X 下本文件仅前向声明 + marker（产品 rest 业务 T=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifndef XLANG_RT_ARGV_FROM_X

int drv_eq_minus_o(const char *buf, int len) {
  return len == 2 && buf[0] == '-' && buf[1] == 'o';
}

int drv_eq_minus_L(const char *buf, int len) {
  return len == 2 && buf[0] == '-' && buf[1] == 'L';
}

int drv_eq_minus_O(const char *buf, int len) {
  return len == 2 && buf[0] == '-' && buf[1] == 'O';
}

int drv_eq_flto(const char *buf, int len) {
  return len == 5 && buf[0] == '-' && buf[1] == 'f' && buf[2] == 'l' && buf[3] == 't' && buf[4] == 'o';
}

int drv_eq_minus_freestanding(const char *buf, int len) {
  return len == 13 && !memcmp(buf, "-freestanding", 13);
}

int drv_eq_legacy_f32_abi(const char *buf, int len) {
  return len == 15 && !memcmp(buf, "-legacy-f32-abi", 15);
}

int drv_eq_fsanitize_address(const char *buf, int len) {
  return len == 18 && !memcmp(buf, "-fsanitize=address", 18);
}

int drv_eq_minus_backend(const char *buf, int len) {
  return len == 8 && !memcmp(buf, "-backend", 8);
}

int drv_eq_minus_target(const char *buf, int len) {
  return len == 7 && !memcmp(buf, "-target", 7);
}

int drv_eq_minus_target_cpu(const char *buf, int len) {
  return len == 11 && !memcmp(buf, "-target-cpu", 11);
}

int drv_eq_print_target_cpu(const char *buf, int len) {
  return (len == 18 && !memcmp(buf, "--print-target-cpu", 18)) ||
         (len == 17 && !memcmp(buf, "-print-target-cpu", 17));
}

int drv_eq_asm_word(const char *buf, int len) {
  return len == 3 && buf[0] == 'a' && buf[1] == 's' && buf[2] == 'm';
}

int drv_eq_c_word(const char *buf, int len) {
  return len == 1 && buf[0] == 'c';
}

int drv_path_ends_x(const char *buf, int len) {
  if (len >= 2 && buf[len - 2] == '.' && buf[len - 1] == 'x')
    return 1;
  if (len >= 3 && buf[len - 3] == '.' && buf[len - 2] == 's' && buf[len - 1] == 'u')
    return 1;
  return 0;
}

int drv_target_has_arm(const char *buf, int len) {
  int start;
  for (start = 0; start + 5 <= len; start++) {
    if (buf[start] == 'a' && buf[start + 1] == 'r' && buf[start + 2] == 'm' && buf[start + 3] == '6' &&
        buf[start + 4] == '4')
      return 1;
  }
  return 0;
}

#else
int drv_eq_minus_o(const char *buf, int len);
int drv_eq_minus_L(const char *buf, int len);
int drv_eq_minus_O(const char *buf, int len);
int drv_eq_flto(const char *buf, int len);
int drv_eq_minus_freestanding(const char *buf, int len);
int drv_eq_legacy_f32_abi(const char *buf, int len);
int drv_eq_fsanitize_address(const char *buf, int len);
int drv_eq_minus_backend(const char *buf, int len);
int drv_eq_minus_target(const char *buf, int len);
int drv_eq_minus_target_cpu(const char *buf, int len);
int drv_eq_print_target_cpu(const char *buf, int len);
int drv_eq_asm_word(const char *buf, int len);
int drv_eq_c_word(const char *buf, int len);
int drv_path_ends_x(const char *buf, int len);
int drv_target_has_arm(const char *buf, int len);

int labi_rt_argv_slice_marker(void) {
  return 1;
}
#endif /* !XLANG_RT_ARGV_FROM_X */
