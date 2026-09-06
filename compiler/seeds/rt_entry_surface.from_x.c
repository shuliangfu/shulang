/* seeds/rt_entry_surface.from_x.c
 * G-02f rt_entry R2 full surface — isomorphic with src/runtime/rt_entry.x
 * Product PREFER_X_O: g05_try_x_to_o(rt_entry.x) + rest seed marker under FROM_X
 * Prove: full.x vs this seed → nm IDENTICAL (6 public entry symbols + helpers)
 * Regen: ./xlang -E ... src/runtime/rt_entry.x | filter DBG + polish prologue
 * Cap residual: driver_stdio_* / driver_entry_*_slot in driver_abi
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <xlang_io_cap.h>
#include <fcntl.h>
#include <errno.h>
extern int32_t rt_entry_strlen(uint8_t * s);
extern void rt_entry_append(uint8_t * dst, int32_t cap, uint8_t * src);
extern void rt_entry_append_i32(uint8_t * dst, int32_t cap, int32_t v);
extern void rt_entry_write_str(int32_t fd, uint8_t * s);
extern void rt_entry_write_nl(int32_t fd);
extern void rt_entry_write_i32(int32_t fd, int32_t v);
extern int32_t rt_entry_is_explain_eq(uint8_t * s);
extern int32_t rt_entry_explain_mode(uint8_t * ab);
extern int32_t rt_entry_explain_usage_err(void);
extern int32_t rt_entry_explain_list(void);
extern int32_t rt_entry_explain_unknown(uint8_t * code);
extern int32_t rt_entry_explain_known(uint8_t * code);
extern int32_t runtime_try_handle_explain_cli(int32_t argc, uint8_t * * argv);
extern int32_t xlang_smoke_diag_enabled(void);
extern void rt_entry_smoke_write_body(uint8_t * name, int32_t main_final_lit, int32_t has_main_body);
extern void rt_entry_smoke_diag_body(uint8_t * name, int32_t main_final_lit, int32_t has_main_body);
extern void driver_emit_legacy_smoke_summary_stdout(uint8_t * main_name, int32_t main_final_lit, int32_t has_main_body);
extern int32_t driver_fmt_report_no_files(void);
extern int32_t run_compiler_c(int32_t argc, uint8_t * * argv);
extern int32_t driver_build_build_x(void);
extern int32_t diag_json_enabled(void);
extern int32_t driver_get_argv_i(int32_t argc, uint8_t * * argv, int32_t i, uint8_t * buf, int32_t max);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern int32_t diag_code_is_known(uint8_t * code);
extern uint8_t * diag_code_suggest(uint8_t * code, uint8_t * buf, size_t cap);
extern void diag_print_code_table(uint8_t * out);
extern void diag_print_code_explain(uint8_t * out, uint8_t * code);
extern void diag_print_known_codes(uint8_t * out);
extern int32_t driver_run_fmt(int32_t argc, uint8_t * * argv);
extern int32_t main_run_compiler_c(int32_t argc, uint8_t * argv);
extern uint8_t * driver_stdio_stdout(void);
extern uint8_t * driver_stdio_stderr(void);
extern uint8_t * driver_entry_ab_slot(void);
extern uint8_t * driver_entry_code_slot(void);
extern uint8_t * driver_entry_suggest_slot(void);
extern uint8_t * driver_entry_msg_slot(void);
extern uint8_t * driver_entry_tmp_slot(void);
extern uint8_t * driver_entry_tmp2_slot(void);
/* wave226 G.7: shell make via public pure thin link_abi_system (wave224 → _impl). */
extern int32_t link_abi_system(uint8_t * cmd);
/* wave227 G.7: env via public pure thin link_abi_getenv (wave222 → _impl). */
extern uint8_t * link_abi_getenv(uint8_t * name);
extern uint8_t * * driver_entry_fmt_argv_slot(void);
int32_t rt_entry_strlen(uint8_t * s) {
  int32_t i = 0;
  if ((s ==((uint8_t *)(0)))) {
    return 0;
  }
  while ((i < 4096)) {
    if (((s)[i] ==0)) {
      return i;
    }
    (void)((i = (i + 1)));
  }
  return i;
}
void rt_entry_append(uint8_t * dst, int32_t cap, uint8_t * src) {
  int32_t n = 0;
  int32_t i = 0;
  uint8_t c = 0;
  if ((dst ==((uint8_t *)(0)))) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  if ((src ==((uint8_t *)(0)))) {
    return;
  }
  (void)((n = rt_entry_strlen(dst)));
  while (((n + 1) < cap)) {
    (void)((c = (src)[i]));
    if ((c ==0)) {
      break;
    }
    (void)(((dst)[n] = c));
    (void)((n = (n + 1)));
    (void)((i = (i + 1)));
  }
  if ((n < cap)) {
    (void)(((dst)[n] = 0));
  } else {
    (void)(((dst)[(cap - 1)] = 0));
  }
}
void rt_entry_append_i32(uint8_t * dst, int32_t cap, int32_t v) {
  uint8_t * dig = ((uint8_t *)(0));
  int32_t n = v;
  int32_t i = 0;
  int32_t j = 0;
  int32_t neg = 0;
  uint8_t a = 0;
  {
    (void)((dig = driver_entry_tmp2_slot()));
  }
  if ((dig ==((uint8_t *)(0)))) {
    return;
  }
  if ((n ==0)) {
    (void)(((dig)[0] = 48));
    (void)(((dig)[1] = 0));
    (void)(rt_entry_append(dst, cap, dig));
    return;
  }
  if ((n < 0)) {
    (void)((neg = 1));
    (void)((n = (0 - n)));
  }
  while ((n > 0)) {
    if ((i >=15)) {
      break;
    }
    (void)(((dig)[i] = ((uint8_t)((48 + (n - ((n / 10) * 10)))))));
    (void)((n = (n / 10)));
    (void)((i = (i + 1)));
  }
  if ((neg !=0)) {
    if ((i < 15)) {
      (void)(((dig)[i] = 45));
      (void)((i = (i + 1)));
    }
  }
  (void)((j = 0));
  while ((j < (i / 2))) {
    (void)((a = (dig)[j]));
    (void)(((dig)[j] = (dig)[((i - 1) - j)]));
    (void)(((dig)[((i - 1) - j)] = a));
    (void)((j = (j + 1)));
  }
  (void)(((dig)[i] = 0));
  (void)(rt_entry_append(dst, cap, dig));
}
void rt_entry_write_str(int32_t fd, uint8_t * s) {
  int32_t n = 0;
  if ((s ==((uint8_t *)(0)))) {
    return;
  }
  (void)((n = rt_entry_strlen(s)));
  if ((n <=0)) {
    return;
  }
  {
    (void)(xlang_io_write(fd, s, ((size_t)(n))));
  }
}
void rt_entry_write_nl(int32_t fd) {
  uint8_t * tmp = ((uint8_t *)(0));
  {
    (void)((tmp = driver_entry_tmp_slot()));
  }
  if ((tmp ==((uint8_t *)(0)))) {
    return;
  }
  (void)(((tmp)[0] = 10));
  (void)(((tmp)[1] = 0));
  (void)(rt_entry_write_str(fd, tmp));
}
void rt_entry_write_i32(int32_t fd, int32_t v) {
  uint8_t * tmp = ((uint8_t *)(0));
  {
    (void)((tmp = driver_entry_tmp_slot()));
  }
  if ((tmp ==((uint8_t *)(0)))) {
    return;
  }
  (void)(((tmp)[0] = 0));
  (void)(rt_entry_append_i32(tmp, 16, v));
  (void)(rt_entry_write_str(fd, tmp));
}
int32_t rt_entry_is_explain_eq(uint8_t * s) {
  if ((s ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((s)[0] !=45)) {
    return 0;
  }
  if (((s)[1] !=45)) {
    return 0;
  }
  if (((s)[2] !=101)) {
    return 0;
  }
  if (((s)[3] !=120)) {
    return 0;
  }
  if (((s)[4] !=112)) {
    return 0;
  }
  if (((s)[5] !=108)) {
    return 0;
  }
  if (((s)[6] !=97)) {
    return 0;
  }
  if (((s)[7] !=105)) {
    return 0;
  }
  if (((s)[8] !=110)) {
    return 0;
  }
  if (((s)[9] !=61)) {
    return 0;
  }
  if (((s)[10] ==0)) {
    return 0;
  }
  return 1;
}
int32_t rt_entry_explain_mode(uint8_t * ab) {
  if ((ab ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    if ((strcmp(ab, (uint8_t[]){101, 120, 112, 108, 97, 105, 110, 0 }) ==0)) {
      return 1;
    }
  }
  {
    if ((strcmp(ab, (uint8_t[]){45, 45, 101, 120, 112, 108, 97, 105, 110, 0 }) ==0)) {
      return 1;
    }
  }
  if ((rt_entry_is_explain_eq(ab) !=0)) {
    return 2;
  }
  return 0;
}
int32_t rt_entry_explain_usage_err(void) {
  uint8_t * msg = ((uint8_t *)(0));
  uint8_t * kind = ((uint8_t *)(0));
  uint8_t * dcode = ((uint8_t *)(0));
  {
    (void)((msg = driver_entry_msg_slot()));
  }
  if ((msg ==((uint8_t *)(0)))) {
    return 1;
  }
  (void)((kind = (uint8_t[]){117, 115, 97, 103, 101, 32, 101, 114, 114, 111, 114, 0 }));
  (void)((dcode = (uint8_t[]){65, 82, 71, 48, 48, 49, 0 }));
  (void)(((msg)[0] = 0));
  (void)(rt_entry_append(msg, 256, (uint8_t[]){45, 45, 101, 120, 112, 108, 97, 105, 110, 32, 114, 101, 113, 117, 105, 114, 101, 115, 32, 97, 32, 100, 105, 97, 103, 110, 111, 115, 116, 105, 99, 32, 99, 111, 100, 101, 32, 40, 101, 120, 97, 109, 112, 108, 101, 58, 32, 120, 108, 97, 110, 103, 32, 45, 45, 101, 120, 112, 108, 97, 105, 110, 32, 80, 0 }));
  {
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
  }
  return 1;
}
int32_t rt_entry_explain_list(void) {
  uint8_t * out = ((uint8_t *)(0));
  {
    (void)((out = driver_stdio_stdout()));
    if ((out !=((uint8_t *)(0)))) {
      (void)(diag_print_code_table(out));
    }
  }
  return 0;
}
int32_t rt_entry_explain_unknown(uint8_t * code) {
  uint8_t * msg = ((uint8_t *)(0));
  uint8_t * sug_buf = ((uint8_t *)(0));
  uint8_t * sug = ((uint8_t *)(0));
  uint8_t * err = ((uint8_t *)(0));
  uint8_t * kind = ((uint8_t *)(0));
  uint8_t * dcode = ((uint8_t *)(0));
  {
    (void)((msg = driver_entry_msg_slot()));
    (void)((sug_buf = driver_entry_suggest_slot()));
  }
  if ((msg ==((uint8_t *)(0)))) {
    return 1;
  }
  (void)((kind = (uint8_t[]){97, 114, 103, 117, 109, 101, 110, 116, 32, 101, 114, 114, 111, 114, 0 }));
  (void)((dcode = (uint8_t[]){65, 82, 71, 48, 48, 50, 0 }));
  (void)(((msg)[0] = 0));
  (void)(rt_entry_append(msg, 256, (uint8_t[]){117, 110, 107, 110, 111, 119, 110, 32, 100, 105, 97, 103, 110, 111, 115, 116, 105, 99, 32, 99, 111, 100, 101, 32, 39, 0 }));
  (void)(rt_entry_append(msg, 256, code));
  (void)(rt_entry_append(msg, 256, (uint8_t[]){39, 0 }));
  {
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
  }
  if ((sug_buf !=((uint8_t *)(0)))) {
    {
      (void)((sug = diag_code_suggest(code, sug_buf, ((size_t)(16)))));
    }
  }
  if ((sug !=((uint8_t *)(0)))) {
    (void)(((msg)[0] = 0));
    (void)(rt_entry_append(msg, 256, (uint8_t[]){100, 105, 100, 32, 121, 111, 117, 32, 109, 101, 97, 110, 32, 39, 0 }));
    (void)(rt_entry_append(msg, 256, sug));
    (void)(rt_entry_append(msg, 256, (uint8_t[]){39, 63, 0 }));
    (void)((kind = (uint8_t[]){104, 101, 108, 112, 0 }));
    {
      (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, ((uint8_t *)(0)), msg, ((uint8_t *)(0))));
    }
  }
  (void)(((msg)[0] = 0));
  (void)(rt_entry_append(msg, 256, (uint8_t[]){117, 115, 101, 32, 96, 120, 108, 97, 110, 103, 32, 45, 45, 101, 120, 112, 108, 97, 105, 110, 32, 80, 48, 48, 49, 96, 32, 111, 114, 32, 96, 120, 108, 97, 110, 103, 32, 101, 120, 112, 108, 97, 105, 110, 32, 80, 48, 48, 49, 96, 59, 32, 117, 115, 101, 32, 96, 45, 45, 108, 105, 115, 116, 96, 32, 0 }));
  (void)((kind = (uint8_t[]){110, 111, 116, 101, 0 }));
  {
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, ((uint8_t *)(0)), msg, ((uint8_t *)(0))));
  }
  (void)(rt_entry_write_str(2, (uint8_t[]){110, 111, 116, 101, 58, 32, 0 }));
  {
    (void)((err = driver_stdio_stderr()));
    if ((err !=((uint8_t *)(0)))) {
      (void)(diag_print_known_codes(err));
    }
  }
  return 1;
}
int32_t rt_entry_explain_known(uint8_t * code) {
  uint8_t * out = ((uint8_t *)(0));
  {
    (void)((out = driver_stdio_stdout()));
    if ((out !=((uint8_t *)(0)))) {
      (void)(diag_print_code_explain(out, code));
    }
  }
  return 0;
}
int32_t runtime_try_handle_explain_cli(int32_t argc, uint8_t * * argv) {
  uint8_t * ab = ((uint8_t *)(0));
  uint8_t * code_buf = ((uint8_t *)(0));
  uint8_t * code = ((uint8_t *)(0));
  int32_t ln = 0;
  int32_t mode = 0;
  int32_t known = 0;
  int32_t is_list = 0;
  if ((argc < 2)) {
    return (0 - 1);
  }
  if ((((uint8_t *)(argv)) ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    (void)((ab = driver_entry_ab_slot()));
    (void)((code_buf = driver_entry_code_slot()));
  }
  if ((ab ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    (void)((ln = driver_get_argv_i(argc, argv, 1, ab, 256)));
  }
  if ((ln < 0)) {
    return (0 - 1);
  }
  (void)((mode = rt_entry_explain_mode(ab)));
  if ((mode ==0)) {
    return (0 - 1);
  }
  (void)((code = ((uint8_t *)(0))));
  if ((mode ==2)) {
    (void)((code = &((ab)[10])));
  } else {
    if ((argc >=3)) {
      if ((code_buf !=((uint8_t *)(0)))) {
        {
          (void)((ln = driver_get_argv_i(argc, argv, 2, code_buf, 256)));
        }
        if ((ln > 0)) {
          (void)((code = code_buf));
        }
      }
    }
  }
  if ((code ==((uint8_t *)(0)))) {
    return rt_entry_explain_usage_err();
  }
  if (((code)[0] ==0)) {
    return rt_entry_explain_usage_err();
  }
  (void)((is_list = 0));
  {
    if ((strcmp(code, (uint8_t[]){108, 105, 115, 116, 0 }) ==0)) {
      (void)((is_list = 1));
    }
  }
  if ((is_list ==0)) {
    {
      if ((strcmp(code, (uint8_t[]){45, 45, 108, 105, 115, 116, 0 }) ==0)) {
        (void)((is_list = 1));
      }
    }
  }
  if ((is_list !=0)) {
    return rt_entry_explain_list();
  }
  (void)((known = 0));
  {
    (void)((known = diag_code_is_known(code)));
  }
  if ((known ==0)) {
    return rt_entry_explain_unknown(code);
  }
  return rt_entry_explain_known(code);
}
int32_t xlang_smoke_diag_enabled(void) {
  uint8_t * e = ((uint8_t *)(0));
  {
    if ((diag_json_enabled() !=0)) {
      return 1;
    }
    /* wave227 G.7: public pure thin link_abi_getenv (not raw libc getenv). */
    (void)((e = link_abi_getenv((uint8_t[]){83, 72, 85, 88, 95, 83, 77, 79, 75, 69, 95, 68, 73, 65, 71, 0 })));
  }
  if ((e ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((e)[0] ==0)) {
    return 0;
  }
  if (((e)[0] ==48)) {
    return 0;
  }
  return 1;
}
void rt_entry_smoke_write_body(uint8_t * name, int32_t main_final_lit, int32_t has_main_body) {
  if ((has_main_body !=0)) {
    if ((main_final_lit >=0)) {
      (void)(rt_entry_write_str(1, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 58, 32, 0 }));
      (void)(rt_entry_write_str(1, name));
      (void)(rt_entry_write_str(1, (uint8_t[]){40, 41, 58, 32, 105, 51, 50, 32, 123, 32, 0 }));
      (void)(rt_entry_write_i32(1, main_final_lit));
      (void)(rt_entry_write_str(1, (uint8_t[]){32, 125, 0 }));
      (void)(rt_entry_write_nl(1));
    } else {
      (void)(rt_entry_write_str(1, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 58, 32, 0 }));
      (void)(rt_entry_write_str(1, name));
      (void)(rt_entry_write_str(1, (uint8_t[]){40, 41, 58, 32, 105, 51, 50, 32, 123, 32, 101, 120, 112, 114, 32, 125, 0 }));
      (void)(rt_entry_write_nl(1));
    }
  } else {
    (void)(rt_entry_write_str(1, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 32, 40, 108, 105, 98, 114, 97, 114, 121, 32, 109, 111, 100, 117, 108, 101, 41, 0 }));
    (void)(rt_entry_write_nl(1));
  }
  (void)(rt_entry_write_str(1, (uint8_t[]){116, 121, 112, 101, 99, 107, 32, 79, 75, 0 }));
  (void)(rt_entry_write_nl(1));
}
void rt_entry_smoke_diag_body(uint8_t * name, int32_t main_final_lit, int32_t has_main_body) {
  uint8_t * msg = ((uint8_t *)(0));
  uint8_t * kind = ((uint8_t *)(0));
  uint8_t * dcode = ((uint8_t *)(0));
  {
    (void)((msg = driver_entry_msg_slot()));
  }
  if ((msg ==((uint8_t *)(0)))) {
    return;
  }
  (void)((kind = (uint8_t[]){105, 110, 102, 111, 0 }));
  (void)((dcode = (uint8_t[]){83, 77, 79, 75, 69, 48, 48, 49, 0 }));
  if ((has_main_body !=0)) {
    if ((main_final_lit >=0)) {
      (void)(((msg)[0] = 0));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 58, 32, 0 }));
      (void)(rt_entry_append(msg, 256, name));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){40, 41, 58, 32, 105, 51, 50, 32, 123, 32, 0 }));
      (void)(rt_entry_append_i32(msg, 256, main_final_lit));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){32, 125, 0 }));
      {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
      }
    } else {
      (void)(((msg)[0] = 0));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 58, 32, 0 }));
      (void)(rt_entry_append(msg, 256, name));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){40, 41, 58, 32, 105, 51, 50, 32, 123, 32, 101, 120, 112, 114, 32, 125, 0 }));
      {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
      }
    }
  } else {
    (void)(((msg)[0] = 0));
    (void)(rt_entry_append(msg, 256, (uint8_t[]){112, 97, 114, 115, 101, 32, 79, 75, 32, 40, 108, 105, 98, 114, 97, 114, 121, 32, 109, 111, 100, 117, 108, 101, 41, 0 }));
    {
      (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
    }
  }
  (void)((dcode = (uint8_t[]){83, 77, 79, 75, 69, 48, 48, 50, 0 }));
  (void)(((msg)[0] = 0));
  (void)(rt_entry_append(msg, 256, (uint8_t[]){116, 121, 112, 101, 99, 107, 32, 79, 75, 0 }));
  {
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
  }
}
void driver_emit_legacy_smoke_summary_stdout(uint8_t * main_name, int32_t main_final_lit, int32_t has_main_body) {
  uint8_t * name = ((uint8_t *)(0));
  if ((main_name !=((uint8_t *)(0)))) {
    (void)((name = main_name));
  } else {
    (void)((name = (uint8_t[]){63, 0 }));
  }
  (void)(rt_entry_smoke_write_body(name, main_final_lit, has_main_body));
  if ((xlang_smoke_diag_enabled() ==0)) {
    return;
  }
  (void)(rt_entry_smoke_diag_body(name, main_final_lit, has_main_body));
}
int32_t driver_fmt_report_no_files(void) {
  {
    return driver_run_fmt(2, driver_entry_fmt_argv_slot());
  }
  return 1;
}
int32_t run_compiler_c(int32_t argc, uint8_t * * argv) {
  {
    return main_run_compiler_c(argc, ((uint8_t *)(argv)));
  }
  return 1;
}
int32_t driver_build_build_x(void) {
  int32_t rc = 0;
  uint8_t * msg = ((uint8_t *)(0));
  uint8_t * kind = ((uint8_t *)(0));
  uint8_t * dcode = ((uint8_t *)(0));
  {
    (void)((msg = driver_entry_msg_slot()));
    /* wave226 G.7: public pure thin link_abi_system (not raw libc system). */
    (void)((rc = link_abi_system((uint8_t[]){99, 100, 32, 99, 111, 109, 112, 105, 108, 101, 114, 32, 38, 38, 32, 109, 97, 107, 101, 32, 45, 115, 32, 98, 117, 105, 108, 100, 45, 116, 111, 111, 108, 32, 50, 62, 38, 49, 0 })));
  }
  if ((rc !=0)) {
    (void)((kind = (uint8_t[]){98, 117, 105, 108, 100, 32, 101, 114, 114, 111, 114, 0 }));
    (void)((dcode = (uint8_t[]){66, 76, 68, 48, 48, 49, 0 }));
    if ((msg !=((uint8_t *)(0)))) {
      (void)(((msg)[0] = 0));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){109, 97, 107, 101, 32, 98, 117, 105, 108, 100, 45, 116, 111, 111, 108, 32, 102, 97, 105, 108, 101, 100, 32, 40, 101, 120, 105, 116, 32, 0 }));
      (void)(rt_entry_append_i32(msg, 256, rc));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){41, 0 }));
      {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
      }
    }
    return 1;
  }
  {
    /* wave226 G.7: public pure thin link_abi_system (not raw libc system). */
    (void)((rc = link_abi_system((uint8_t[]){99, 100, 32, 99, 111, 109, 112, 105, 108, 101, 114, 32, 38, 38, 32, 46, 47, 98, 117, 105, 108, 100, 95, 116, 111, 111, 108, 32, 46, 47, 120, 108, 97, 110, 103, 32, 50, 62, 38, 49, 0 })));
  }
  if ((rc !=0)) {
    (void)((kind = (uint8_t[]){98, 117, 105, 108, 100, 32, 101, 114, 114, 111, 114, 0 }));
    (void)((dcode = (uint8_t[]){66, 76, 68, 48, 48, 49, 0 }));
    if ((msg !=((uint8_t *)(0)))) {
      (void)(((msg)[0] = 0));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){98, 117, 105, 108, 100, 95, 116, 111, 111, 108, 32, 102, 97, 105, 108, 101, 100, 32, 40, 101, 120, 105, 116, 32, 0 }));
      (void)(rt_entry_append_i32(msg, 256, rc));
      (void)(rt_entry_append(msg, 256, (uint8_t[]){41, 0 }));
      {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, dcode, msg, ((uint8_t *)(0))));
      }
    }
    return 1;
  }
  return 0;
}
