/* seeds/rt_dispatch_impl.from_x.c — G-02f-313 P2 runtime rest (dispatch impl gates)
 * Logic source: src/runtime/rt_dispatch_impl.x
 * Hybrid: XLANG_RT_DISPATCH_IMPL_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供：
 *   driver_run_asm_backend_impl_c / driver_run_emit_c_path_impl_c /
 *   driver_run_x_emit_c_from_compile_state /
 *   driver_run_compiler_full_x_post_parse_impl_c /
 *   driver_run_compiler_full_x_impl_c
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual（driver_abi）：lib_key→lib_roots 槽 + Parsed 填表。
 * 冷启动/无 PREFER 时仍编译完整 C 体（含 sibling / 非 product ifdef）。
 *
 * Scope: asm/emit/full_x/post_parse/x_emit_from_state 中型分派；
 * run_asm_backend / run_compiler_parsed / run_x_emit_c 巨石已 R2。
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef X_FULL_MAX_LIB_ROOTS
#define X_FULL_MAX_LIB_ROOTS 16
#endif
#ifndef X_EMIT_MAX_LIB_ROOTS
#define X_EMIT_MAX_LIB_ROOTS 16
#endif

/** compile.x DriverCompileState 布局（与 mega 一致）。 */
typedef struct DriverCompileStateSU {
  uint8_t path_buf[512];
  int32_t path_len;
  uint8_t out_path_buf[512];
  int32_t out_path_len;
  int32_t use_asm_backend;
  int32_t target_arch;
  uint8_t target_buf[512];
  int32_t target_len;
  uint8_t opt_level_buf[8];
  int32_t opt_level_len;
  int32_t use_lto;
  int32_t backend_asm_explicit;
  int32_t use_freestanding;
  int32_t parse_saw_target;
  uint8_t target_cpu_buf[128];
  int32_t target_cpu_len;
  int32_t target_cpu_features;
  int32_t print_target_cpu;
  int32_t parse_saw_target_cpu;
} DriverCompileStateSU;

typedef struct DriverCompileParsed {
  const char *input_path;
  const char *out_path;
  const char *lib_roots_arr[X_FULL_MAX_LIB_ROOTS];
  int n_lib_roots;
  int want_asm_backend;
  const char *target;
  const char *opt_level;
  int use_lto;
} DriverCompileParsed;

#ifndef XLANG_RT_DISPATCH_IMPL_FROM_X

extern int driver_lib_roots_from_key(uint8_t *lib_key, const char **out_arr, char bufs[X_FULL_MAX_LIB_ROOTS][512]);
/* wave227 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv). */
extern char *link_abi_getenv(const char *name);
extern void driver_set_pending_target_cpu_features(uint32_t features);
extern int driver_run_asm_backend(const char *input_path, const char *out_path, const char **lib_roots_arr, int n_lib_roots,
                                  const char *target, int argc, char **argv);
extern int driver_run_compiler_parsed(DriverCompileParsed *p, int argc, char **argv);
extern int driver_try_compile_via_shu_c_sibling(int argc, char **argv);
extern int32_t driver_check_only_get(void);
extern int driver_source_has_top_level_import_path(const char *path);
extern int32_t driver_asm_entry_module_only_from_env(void);
extern int driver_argv_has_emit_c_flag(int argc, char **argv);
extern int32_t driver_asm_output_want_exe(uint8_t *path);
extern int driver_source_has_generic_syntax(const uint8_t *path, int path_len);
extern void driver_freestanding_set(int32_t v);
extern void cfg_set_freestanding(int v);
extern int driver_run_x_emit_c_set_emit_extern(int v);
extern int driver_run_x_emit_c_set_path(const uint8_t *path, int path_len);
extern int driver_run_x_emit_c_set_lib(int i, const uint8_t *buf, int len);
extern int driver_run_x_emit_c_set_n_lib_roots(int n);
extern int driver_run_x_emit_c(void);
extern int runtime_try_handle_explain_cli(int argc, char **argv);
extern int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t *argv_opaque);
extern void driver_print_usage_c(void);
extern void driver_bump_stack_limit(void);
extern DriverCompileStateSU *driver_compile_state_alloc_c(void);
extern void driver_compile_state_free_c(DriverCompileStateSU *state);
extern int32_t driver_compile_parse_argv_impl_c(int32_t argc, uint8_t *argv, DriverCompileStateSU *state);
/* Cap residual 9.7.2: fd-handle face — print target goes through
 * driver_stdio_stdout (encoded fd 1), no libc FILE star / stdout. */
extern void xlang_target_cpu_print(uint8_t *out, uint32_t features);
extern uint8_t *driver_stdio_stdout(void);
extern uint8_t *driver_dispatch_opt_default(void);

/** asm 后端：lib_key sidecar → lib_roots，委托 driver_run_asm_backend。 */
int32_t driver_run_asm_backend_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                      int32_t argc, uint8_t *argv) {
  static char lib_bufs[X_FULL_MAX_LIB_ROOTS][512];
  static const char *lib_roots[X_FULL_MAX_LIB_ROOTS];
  int n = driver_lib_roots_from_key(lib_key, lib_roots, lib_bufs);
  if (lib_key)
    driver_set_pending_target_cpu_features((uint32_t)((DriverCompileStateSU *)lib_key)->target_cpu_features);
  else
    driver_set_pending_target_cpu_features(0);
  return driver_run_asm_backend((const char *)input_path, out_path ? (const char *)out_path : NULL, lib_roots, n,
                                target && target[0] ? (const char *)target : NULL, (int)argc, (char **)argv);
}

/** C 后端：lib_key→lib_roots；可选 sibling xlang-c；否则 parsed。 */
int32_t driver_run_emit_c_path_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                      uint8_t *opt_level, int32_t use_lto, int32_t argc, uint8_t *argv) {
  const char *lib_roots[X_FULL_MAX_LIB_ROOTS];
  char lib_bufs[X_FULL_MAX_LIB_ROOTS][512];
  int n = driver_lib_roots_from_key(lib_key, lib_roots, lib_bufs);
  DriverCompileParsed p;
  memset(&p, 0, sizeof p);
  p.input_path = (const char *)input_path;
  p.out_path = out_path ? (const char *)out_path : NULL;
  memcpy(p.lib_roots_arr, lib_roots, (size_t)n * sizeof lib_roots[0]);
  p.n_lib_roots = n;
  p.want_asm_backend = 0;
  p.target = target && target[0] ? (const char *)target : NULL;
  p.opt_level = (opt_level && opt_level[0]) ? (const char *)opt_level
                                            : (const char *)driver_dispatch_opt_default();
  p.use_lto = use_lto != 0;
  /* wave227 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
  {
    const char *_lto = link_abi_getenv("XLANG_LTO");
    if (!p.use_lto && _lto && strcmp(_lto, "1") == 0)
      p.use_lto = 1;
  }
#if !defined(XLANG_NO_C_FRONTEND)
  if (!driver_check_only_get() && p.input_path && driver_source_has_top_level_import_path(p.input_path) &&
      !driver_asm_entry_module_only_from_env()) {
    int xlang_c_rc = driver_try_compile_via_shu_c_sibling((int)argc, (char **)argv);
    if (xlang_c_rc >= 0)
      return xlang_c_rc;
  }
#endif
  return driver_run_compiler_parsed(&p, (int)argc, (char **)argv);
}

/** `-E`：compile state → emit state 槽 → driver_run_x_emit_c。 */
int32_t driver_run_x_emit_c_from_compile_state(DriverCompileStateSU *state, int argc, char **argv) {
  const char *lib_roots[X_EMIT_MAX_LIB_ROOTS];
  char lib_bufs[X_FULL_MAX_LIB_ROOTS][512];
  int want_extern = 0;
  int n;
  int k;

  if (!state || state->path_len <= 0)
    return 1;
  for (k = 1; k < argc; k++) {
    if (argv[k] && !strcmp(argv[k], "-E-extern"))
      want_extern = 1;
  }
  driver_run_x_emit_c_set_emit_extern(want_extern);
  driver_run_x_emit_c_set_path(state->path_buf, state->path_len);
  n = driver_lib_roots_from_key((uint8_t *)state, lib_roots, lib_bufs);
  if (n <= 0) {
    driver_run_x_emit_c_set_lib(0, (const uint8_t *)".", 1);
    driver_run_x_emit_c_set_n_lib_roots(1);
  } else {
    for (k = 0; k < n; k++)
      driver_run_x_emit_c_set_lib(k, (const uint8_t *)lib_roots[k], (int)strlen(lib_roots[k]));
    driver_run_x_emit_c_set_n_lib_roots(n);
  }
  return (int32_t)driver_run_x_emit_c();
}

/** parse 完成后后端选择 + 分派。 */
int32_t driver_run_compiler_full_x_post_parse_impl_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv) {
  uint8_t *out_ptr;
  uint8_t *target_ptr;

  if (!state)
    return 1;
#if defined(XLANG_USE_X_DRIVER) && defined(XLANG_USE_X_PIPELINE)
  if (driver_argv_has_emit_c_flag((int)argc, (char **)argv))
    return driver_run_x_emit_c_from_compile_state(state, (int)argc, (char **)argv);
#endif
  if (driver_check_only_get())
    state->use_asm_backend = 0;
  /*
   * PLATFORM: SHARED — PC invoke_cc opt-in (2026-08-12): silent generic→C removed.
   * Prior residual: driver_source_has_generic_syntax on want_exe forced C without
   * `-backend c`. G.7 cold twin of rt_dispatch_impl.x. Product host-cc only via
   * explicit `-backend c` / check-only / emit-c. Import→C + APPLE exe→C already closed.
   * No-import -o still locks backend_asm_explicit. Seed cold twin under !FROM_X only.
   */
  out_ptr = NULL;
  if (state->out_path_len > 0)
    out_ptr = state->out_path_buf;
  target_ptr = NULL;
  if (state->target_len > 0)
    target_ptr = state->target_buf;
#if defined(XLANG_ASM_USE_COMPILER_IMPL_C)
  if (state->out_path_len > 0 && !state->backend_asm_explicit &&
      !driver_source_has_top_level_import_path((const char *)state->path_buf))
    state->backend_asm_explicit = 1;
#endif
  if (state->use_freestanding) {
    state->use_asm_backend = 1;
    state->backend_asm_explicit = 1;
    driver_freestanding_set(1);
    cfg_set_freestanding(1);
  }
  if (state->use_asm_backend) {
    return driver_run_asm_backend_impl_c(state->path_buf, out_ptr, (uint8_t *)state, target_ptr, argc, argv);
  }
  return driver_run_emit_c_path_impl_c(state->path_buf, out_ptr, (uint8_t *)state, target_ptr, state->opt_level_buf,
                                       state->use_lto, argc, argv);
}

/** 完整编译 C 入口：堆 state + parse_argv + post_parse。 */
int32_t driver_run_compiler_full_x_impl_c(int32_t argc, uint8_t *argv) {
  DriverCompileStateSU *state;
  int32_t rc;
  int explain_rc;

  explain_rc = runtime_try_handle_explain_cli((int)argc, (char **)argv);
  if (explain_rc >= 0)
    return explain_rc;

  if (driver_compile_argv_is_help_c(argc, argv)) {
    driver_print_usage_c();
    return 0;
  }
  if (argc < 2) {
    driver_print_usage_c();
    return 0;
  }
  driver_bump_stack_limit();
  state = driver_compile_state_alloc_c();
  if (!state)
    return 1;
  if (driver_compile_parse_argv_impl_c(argc, argv, state) != 0) {
    driver_compile_state_free_c(state);
    return 1;
  }
  if (state->print_target_cpu) {
    xlang_target_cpu_print(driver_stdio_stdout(), (uint32_t)state->target_cpu_features);
    driver_compile_state_free_c(state);
    return 0;
  }
  rc = driver_run_compiler_full_x_post_parse_impl_c(state, argc, argv);
  driver_compile_state_free_c(state);
  return rc;
}

#else /* XLANG_RT_DISPATCH_IMPL_FROM_X：产品 rest 仅 marker；业务体在 full .x */
int32_t driver_run_asm_backend_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                      int32_t argc, uint8_t *argv);
int32_t driver_run_emit_c_path_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                      uint8_t *opt_level, int32_t use_lto, int32_t argc, uint8_t *argv);
int32_t driver_run_x_emit_c_from_compile_state(void *state, int argc, char **argv);
int32_t driver_run_compiler_full_x_post_parse_impl_c(void *state, int32_t argc, uint8_t *argv);
int32_t driver_run_compiler_full_x_impl_c(int32_t argc, uint8_t *argv);
#endif /* XLANG_RT_DISPATCH_IMPL_FROM_X */

int labi_rt_dispatch_impl_slice_marker(void) {
  return 1;
}
