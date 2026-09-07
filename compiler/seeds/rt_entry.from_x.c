/* seeds/rt_entry.from_x.c — G-02f-301/310 P2 runtime R10 entry gates
 * Logic source: src/runtime/rt_entry.x
 * Hybrid: XLANG_RT_ENTRY_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2（2026-07-14）：6 公共符号（explain_cli / smoke_diag / smoke_summary /
 *   fmt_report_no_files / run_compiler_c / build_build_x）均由 .x 提供；
 * FROM_X 下本文件仅前向声明 + marker（产品 rest 业务 H=0）。
 * Cap residual：driver_stdio_{stdout,stderr} 与 driver_entry_*_slot 在 driver_abi。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 * 9.7.4：冷体脱离 libc stdio——explain/smoke 输出走 fd 句柄脸
 *   （driver_stdio_stdout/stderr + xlang_io_write + xlang_snprintf），与 .x
 *   权威一致；diag_print_* extern 脸 FILE*→uint8_t*（与 include/diag.h 对齐，
 *   修复冷启动二进制把 FILE* 当 fd 句柄解码的语义错位）；fmt_report_no_files
 *   本地 argv 数组→wave21 driver_entry_fmt_argv_slot（G.7 单权威）。
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_io_cap.h>   /* Cap residual 9.1.x: raw fd write (no libc stdio) */
#include <xlang_fmt_cap.h>  /* Cap residual 10.7.2: bounded format (no libc stdio) */
/* G.7: Cap snprintf mapping (no libc stdio since 9.7.4). */
#undef snprintf
#define snprintf xlang_snprintf

#include "runtime_diag_codes.h"

extern void diag_reportf_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                   const char *detail, const char *fmt, ...);
extern void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt,
                         ...);
extern void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                  const char *msg, const char *detail);
/* 9.7.4: fd-handle face, matches include/diag.h (out = driver_stdio_stdout() etc.). */
extern void diag_print_code_table(uint8_t *out);
extern int diag_code_is_known(const char *code);
extern const char *diag_code_suggest(const char *code, char *buf, size_t cap);
extern void diag_print_code_explain(uint8_t *out, const char *code);
extern void diag_print_known_codes(uint8_t *out);
extern int diag_json_enabled(void);
extern int driver_run_fmt(int argc, char **argv);
extern int main_run_compiler_c(int argc, uint8_t *argv);
/* wave15/21/39/40 accessors: authority = runtime_driver_abi_thin.x; cold twins
 * in seeds/runtime_driver_abi.from_x.c; decls also in runtime_driver_abi.h. */
extern uint8_t *driver_stdio_stdout(void);
extern uint8_t *driver_stdio_stderr(void);
extern char **driver_entry_fmt_argv_slot(void);
/* wave226 G.7: shell make via public pure thin link_abi_system (wave224 → _impl host system). */
extern int link_abi_system(const char *cmd);
/* wave227 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv). */
extern char *link_abi_getenv(const char *name);

#ifndef XLANG_RT_ENTRY_FROM_X

/**
 * Write entire buffer to fd via Cap io (handles partial writes).
 * Replaces printf/fputs in the cold twin; byte output unchanged.
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS) — Cap io write.
 */
static void rt_entry_cap_write_all(int fd, const char *buf, size_t len) {
  size_t off = 0;
  while (off < len) {
    long n = xlang_io_write(fd, buf + off, len - off);
    if (n <= 0)
      break;
    off += (size_t)n;
  }
}

/** explain 子命令 / --explain：-1=非 explain，0=成功，1=失败。 */
int runtime_try_handle_explain_cli(int argc, char **argv) {
  const char *code = NULL;
  if (argc < 2 || !argv || !argv[1])
    return -1;
  if (strcmp(argv[1], "explain") == 0) {
    if (argc >= 3 && argv[2] && argv[2][0])
      code = argv[2];
    else
      code = NULL;
  } else if (strcmp(argv[1], "--explain") == 0) {
    if (argc >= 3 && argv[2] && argv[2][0])
      code = argv[2];
    else
      code = NULL;
  } else if (strncmp(argv[1], "--explain=", 10) == 0 && argv[1][10] != '\0') {
    code = argv[1] + 10;
  } else {
    return -1;
  }
  if (!code || !code[0]) {
    diag_reportf_with_code(NULL, 0, 0, "usage error", XLANG_DIAG_CODE_ARGUMENT_ARG001, NULL,
                           "--explain requires a diagnostic code (example: xlang --explain P001; use --list to see all)");
    return 1;
  }
  if (strcmp(code, "list") == 0 || strcmp(code, "--list") == 0) {
    diag_print_code_table(driver_stdio_stdout());
    return 0;
  }
  if (!diag_code_is_known(code)) {
    char suggest[16];
    const char *sug;
    diag_reportf_with_code(NULL, 0, 0, "argument error", XLANG_DIAG_CODE_ARGUMENT_ARG002, NULL,
                           "unknown diagnostic code '%s'", code);
    sug = diag_code_suggest(code, suggest, sizeof suggest);
    if (sug)
      diag_reportf(NULL, 0, 0, "help", NULL, "did you mean '%s'?", sug);
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "use `xlang --explain P001` or `xlang explain P001`; use `--list` to see all codes");
    /* raw fd 2 (matches .x rt_entry_write_str(2, "note: ")); no libc fputs/stderr. */
    rt_entry_cap_write_all(2, "note: ", 6);
    diag_print_known_codes(driver_stdio_stderr());
    return 1;
  }
  diag_print_code_explain(driver_stdio_stdout(), code);
  return 0;
}

int xlang_smoke_diag_enabled(void) {
  const char *e;
  if (diag_json_enabled())
    return 1;
  /* wave227 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
  e = link_abi_getenv("XLANG_SMOKE_DIAG");
  return (e && e[0] && e[0] != '0') ? 1 : 0;
}

void driver_emit_legacy_smoke_summary_stdout(const char *main_name, int main_final_lit, int has_main_body) {
  const char *name = main_name ? main_name : "?";
  char line[512];
  int len;
  if (has_main_body) {
    if (main_final_lit >= 0)
      len = snprintf(line, sizeof line, "parse OK: %s(): i32 { %d }\n", name, main_final_lit);
    else
      len = snprintf(line, sizeof line, "parse OK: %s(): i32 { expr }\n", name);
  } else {
    len = snprintf(line, sizeof line, "parse OK (library module)\n");
  }
  if (len > 0)
    rt_entry_cap_write_all(1, line, (size_t)len);
  len = snprintf(line, sizeof line, "typeck OK\n");
  if (len > 0)
    rt_entry_cap_write_all(1, line, (size_t)len);
  if (xlang_smoke_diag_enabled()) {
    if (has_main_body) {
      if (main_final_lit >= 0)
        diag_reportf_with_code(NULL, 0, 0, "info", XLANG_DIAG_CODE_SMOKE_SMOKE001, NULL, "parse OK: %s(): i32 { %d }",
                               name, main_final_lit);
      else
        diag_reportf_with_code(NULL, 0, 0, "info", XLANG_DIAG_CODE_SMOKE_SMOKE001, NULL, "parse OK: %s(): i32 { expr }",
                               name);
    } else {
      diag_reportf_with_code(NULL, 0, 0, "info", XLANG_DIAG_CODE_SMOKE_SMOKE001, NULL, "parse OK (library module)");
    }
    diag_report_with_code(NULL, 0, 0, "info", XLANG_DIAG_CODE_SMOKE_SMOKE002, "typeck OK", NULL);
  }
}

/** 兼容旧 driver_fmt_gen.c：无路径时委托 driver_run_fmt。
 * 9.7.4 G.7：argv 基座用 wave21 driver_entry_fmt_argv_slot（BSS lit "xlang"/"fmt"），
 * 不再本地重建数组。 */
int driver_fmt_report_no_files(void) {
  return driver_run_fmt(2, driver_entry_fmt_argv_slot());
}

/** X driver：转调 main.x main_run_compiler_c。 */
int run_compiler_c(int argc, char **argv) {
  return main_run_compiler_c(argc, (uint8_t *)argv);
}

/**
 * cmd_build：make build-tool 再 build_tool ./xlang。
 * wave226 G.7: public pure thin link_abi_system (not raw libc system);
 * Cap residual host system stays only link_abi_system_impl.
 * PLATFORM: SHARED orch / host shell boundary.
 */
int driver_build_build_x(void) {
  /* wave226 G.7: link_abi_system (not raw system). */
  int rc = link_abi_system("cd compiler && make -s build-tool 2>&1");
  if (rc != 0) {
    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                           "make build-tool failed (exit %d)", rc);
    return 1;
  }
  /* wave226 G.7: link_abi_system (not raw system). */
  rc = link_abi_system("cd compiler && ./build_tool ./xlang 2>&1");
  if (rc != 0) {
    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                           "build_tool failed (exit %d)", rc);
    return 1;
  }
  return 0;
}

int labi_rt_entry_slice_marker(void) {
  return 1;
}

#else
int runtime_try_handle_explain_cli(int argc, char **argv);
int xlang_smoke_diag_enabled(void);
void driver_emit_legacy_smoke_summary_stdout(const char *main_name, int main_final_lit, int has_main_body);
int driver_fmt_report_no_files(void);
int run_compiler_c(int argc, char **argv);
int driver_build_build_x(void);

int labi_rt_entry_slice_marker(void) {
  return 1;
}
#endif /* !XLANG_RT_ENTRY_FROM_X */
