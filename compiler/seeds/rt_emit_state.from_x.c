/* seeds/rt_emit_state.from_x.c — G-02f-303/304 P2 runtime rest (-E emit state)
 * Logic source: src/runtime/rt_emit_state.x
 * Hybrid: XLANG_RT_EMIT_STATE_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full：set_path/set_lib/set_n/set_extern + argv_parse 由 .x 提供；
 * FROM_X 下本文件：始终保留 BSS 数据（跨 TU 共享；Cap-global-bss）+ 前向声明 + marker
 * （产品 rest 业务 T=0）。冷启动/无 PREFER 时仍编译完整 C 体。
 * Cap residual 槽函数在 runtime_driver_abi（平台层，供 .x 写槽）。
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
/* struct ast_PipelineDepCtx layout authority (ctx prefix setter below). */
#include "runtime_pipeline_abi.h"

#define X_EMIT_MAX_LIB_ROOTS 16

extern int driver_get_argv_i(int argc, char **argv, int i, char *buf, int max);

/* 与 seeds/runtime.from_x.c 原 static 同布局；hybrid 时 rest 定义、mega 以 extern 引用。
 * Cap-global-bss residual：大数组/共享指针必须非 static 跨 TU → 始终在 seed 定义
 * （.x export let 会编成 static，不能替代本块）。 */
const char *driver_x_emit_c_path;
const char *driver_x_emit_lib_roots[X_EMIT_MAX_LIB_ROOTS];
int driver_x_emit_n_lib_roots;
char driver_x_emit_path_buf[512];
char driver_x_emit_lib_bufs[X_EMIT_MAX_LIB_ROOTS][256];
int driver_x_emit_c_want_extern;
/* argv 扫描 scratch（Cap residual 槽经 driver_abi 暴露给 .x） */
char driver_x_emit_scan_ab[512];
char driver_x_emit_scan_nx[512];

/* 7.4.4 v3: dual-set the codegen ctx entry prefix (name + '_') on BOTH
 * current_codegen_prefix and entry_module_import_path mirrors — the .x twin
 * of the C-side writer in rt_run_compiler_parsed (trailing underscore
 * shape). Lives here (not pabi) because the rt-slice lane reliably
 * rebuilds this TU (pabi inject-only does not take new rest bodies, and
 * HOST_CC_SEED_FORCE hybrid is forbidden on Darwin per 392d44cb6).
 * Null ctx / empty / over-long name is a no-op. PLATFORM: SHARED. */
void xlang_pipeline_pctx_set_entry_lib_prefix(struct ast_PipelineDepCtx *ctx, const void *name, int32_t name_len) {
  int32_t k;
  if (!ctx || !name || name_len <= 0 || name_len >= 63)
    return;
  for (k = 0; k < name_len; k++) {
    ctx->current_codegen_prefix_mirror[k] = ((const uint8_t *)name)[k];
    ctx->entry_module_import_path_mirror[k] = ((const uint8_t *)name)[k];
  }
  ctx->current_codegen_prefix_mirror[name_len] = '_';
  ctx->current_codegen_prefix_mirror[name_len + 1] = 0;
  ctx->entry_module_import_path_mirror[name_len] = '_';
  ctx->entry_module_import_path_mirror[name_len + 1] = 0;
  ctx->current_codegen_prefix_len = name_len + 1;
  ctx->entry_module_import_path_len = name_len + 1;
}

/* 7.4.4 v3: opt-in -lib-name for the X-pipeline -E/-o emit lane. parse_x
 * (main.x) stores it via the setter; driver_run_x_emit_c (rt_run_x_emit.x,
 * the hot -x -E lane per main_entry dispatch) reads it and seeds the ctx
 * entry prefix via xlang_pipeline_pctx_set_entry_lib_prefix. Empty/absent =
 * bare emission (today's default; "-lib-name \"\"" stays a tolerated no-op
 * for the xlang_compile_std_module probe). Always-seed: no .x twin.
 * PLATFORM: SHARED. */
char driver_x_emit_lib_name_buf[64];
int driver_x_emit_lib_name_len;

void xlang_driver_x_emit_set_lib_name(const uint8_t *buf, int32_t len) {
  driver_x_emit_lib_name_len = 0;
  driver_x_emit_lib_name_buf[0] = '\0';
  if (!buf || len <= 0 || len >= (int)sizeof(driver_x_emit_lib_name_buf))
    return;
  memcpy(driver_x_emit_lib_name_buf, buf, (size_t)len);
  driver_x_emit_lib_name_buf[len] = '\0';
  driver_x_emit_lib_name_len = len;
}

int32_t xlang_driver_x_emit_lib_name_into(uint8_t *out, int32_t cap) {
  int32_t n = driver_x_emit_lib_name_len;
  if (!out || cap <= 0)
    return 0;
  if (n <= 0) {
    out[0] = '\0';
    return 0;
  }
  if (n > cap - 1)
    n = cap - 1;
  memcpy(out, driver_x_emit_lib_name_buf, (size_t)n);
  out[n] = '\0';
  return n;
}

#ifndef XLANG_RT_EMIT_STATE_FROM_X

int driver_run_x_emit_c_set_path(const uint8_t *path, int path_len) {
  driver_x_emit_c_path = NULL;
  if (!path || path_len <= 0 || path_len >= (int)sizeof(driver_x_emit_path_buf))
    return 0;
  memcpy(driver_x_emit_path_buf, path, (size_t)path_len);
  driver_x_emit_path_buf[path_len] = '\0';
  driver_x_emit_c_path = driver_x_emit_path_buf;
  return 0;
}

int driver_run_x_emit_c_set_lib(int i, const uint8_t *buf, int len) {
  if (i < 0 || i >= X_EMIT_MAX_LIB_ROOTS || !buf || len < 0 || len >= 256)
    return 0;
  memcpy(driver_x_emit_lib_bufs[i], buf, (size_t)len);
  driver_x_emit_lib_bufs[i][len] = '\0';
  driver_x_emit_lib_roots[i] = driver_x_emit_lib_bufs[i];
  return 0;
}

int driver_run_x_emit_c_set_n_lib_roots(int n) {
  driver_x_emit_n_lib_roots = (n >= 0 && n <= X_EMIT_MAX_LIB_ROOTS) ? n : 0;
  return 0;
}

int driver_run_x_emit_c_set_emit_extern(int v) {
  driver_x_emit_c_want_extern = v ? 1 : 0;
  return 0;
}

/**
 * 扫描 argv：若存在 -x -E <path> 则记下 path 及此前出现的 -L path，返回 1，否则返回 0。
 */
int driver_argv_parse_x_emit_c(int argc, char **argv) {
  char ab[512];
  char nx[512];
  driver_x_emit_c_path = NULL;
  driver_x_emit_n_lib_roots = 0;
  if (argc < 4 || !argv)
    return 0;
  for (int i = 1; i < argc; i++) {
    if (driver_get_argv_i(argc, argv, i, ab, (int)sizeof ab) < 0)
      continue;
    if (strcmp(ab, "-L") == 0 && i + 1 < argc) {
      int k = driver_x_emit_n_lib_roots;
      if (k < X_EMIT_MAX_LIB_ROOTS) {
        int ln = driver_get_argv_i(argc, argv, i + 1, driver_x_emit_lib_bufs[k], 256);
        if (ln < 0)
          return 0;
        driver_x_emit_lib_roots[k] = driver_x_emit_lib_bufs[k];
        driver_x_emit_n_lib_roots++;
      }
      i++;
      continue;
    }
    if (strcmp(ab, "-x") == 0 && i + 2 < argc) {
      if (driver_get_argv_i(argc, argv, i + 1, nx, (int)sizeof nx) < 0 || strcmp(nx, "-E") != 0)
        continue;
      if (driver_get_argv_i(argc, argv, i + 2, driver_x_emit_path_buf, (int)sizeof driver_x_emit_path_buf) < 0)
        return 0;
      driver_x_emit_c_path = driver_x_emit_path_buf;
      return 1;
    }
  }
  return 0;
}

#else
int driver_run_x_emit_c_set_path(const uint8_t *path, int path_len);
int driver_run_x_emit_c_set_lib(int i, const uint8_t *buf, int len);
int driver_run_x_emit_c_set_n_lib_roots(int n);
int driver_run_x_emit_c_set_emit_extern(int v);
int driver_argv_parse_x_emit_c(int argc, char **argv);
#endif

int labi_rt_emit_state_slice_marker(void) {
  return 1;
}
