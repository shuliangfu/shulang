/* seeds/rt_compile.from_x.c — G-02f-291～296 P2 runtime R6 compile helpers
 * Logic source: src/runtime/rt_compile.x
 * Hybrid: XLANG_RT_COMPILE_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：25 公共业务符号均由 .x 提供；
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 *
 * f-291～295: deps / flags / apply_* / init-ensure / step-scan
 * f-296: parse_argv_impl + resolve_target_cpu + cfg_sync + state_alloc/free
 */
#if !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Layout matches seeds/runtime.from_x.c DriverCompileStateSU (fields used here). */
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

extern void driver_freestanding_set(int on);
extern void cfg_set_freestanding(int on);
extern void driver_sanitize_address_set(int on);
extern int driver_get_argv_i(int argc, char **argv, int i, char *buf, int max);
extern void cfg_reset_compile_target(void);
extern int32_t driver_emit_lib_root_count(uint8_t *state);
extern int32_t driver_emit_append_lib_root(uint8_t *state, uint8_t *path, int32_t len);
extern void driver_emit_lib_root_reset(uint8_t *state);
/* From rt_argv seed when hybrid; else mega rest. */
extern int drv_eq_minus_o(const char *buf, int len);
extern int drv_eq_minus_L(const char *buf, int len);
extern int drv_eq_minus_O(const char *buf, int len);
extern int drv_eq_flto(const char *buf, int len);
extern int drv_eq_minus_freestanding(const char *buf, int len);
extern int drv_eq_legacy_f32_abi(const char *buf, int len);
extern int drv_eq_fsanitize_address(const char *buf, int len);
extern int drv_eq_minus_backend(const char *buf, int len);
extern int drv_eq_minus_target(const char *buf, int len);
extern int drv_eq_minus_target_cpu(const char *buf, int len);
extern int drv_eq_print_target_cpu(const char *buf, int len);
extern int drv_eq_asm_word(const char *buf, int len);
extern int drv_eq_c_word(const char *buf, int len);
extern int drv_path_ends_x(const char *buf, int len);
extern int drv_target_has_arm(const char *buf, int len);
extern int xlang_target_cpu_resolve(const char *spec, size_t spec_len, uint32_t *out);
extern uint32_t xlang_target_cpu_generic_for_host(void);
extern void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt,
                         ...);
extern void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                  const char *msg, const char *detail);
extern void cfg_apply_compile_target_from_triple(const char *triple, int32_t len);
extern int32_t driver_resolve_target_arch(int32_t parsed_target, int32_t saw_target_flag);

#ifndef XLANG_RT_COMPILE_FROM_X

/**
 * dep 列表是否全为 std./core. 闭包（符号由预编 .o / preamble 提供，勿 dep_prerun 全量 typeck）。
 * tests/multi-file 的 import("foo") 等用户 dep 返回 0，仍走 typeck_only。
 */
int driver_deps_are_std_core_closure_only(char **dep_paths, int n_deps) {
  int k;
  if (!dep_paths || n_deps <= 0)
    return 0;
  for (k = 0; k < n_deps; k++) {
    const char *p = dep_paths[k];
    if (!p || p[0] == '\0')
      return 0;
    if (strncmp(p, "std.", 4) == 0 || strncmp(p, "core.", 5) == 0)
      continue;
    return 0;
  }
  return 1;
}

/**
 * `-E src/asm/asm.x` 的 compiler-internal 闭包仅需 parse 填 import/签名槽；
 * 对 `ast` 等大模块做 dep_prerun typeck 会显著拖慢甚至卡住 seed host 构建。
 */
int driver_x_emit_asm_dep_parse_only_ok(const char *input_path, const char *dep_path) {
  if (!input_path || !dep_path)
    return 0;
  if (strstr(input_path, "src/asm/asm.x") == NULL && strstr(input_path, "/asm/asm.x") == NULL)
    return 0;
  if (strcmp(dep_path, "ast") == 0 || strcmp(dep_path, "codegen") == 0 || strcmp(dep_path, "backend") == 0 ||
      strcmp(dep_path, "peephole") == 0)
    return 1;
  if (strncmp(dep_path, "asm.", 4) == 0 || strncmp(dep_path, "arch.", 5) == 0 ||
      strncmp(dep_path, "platform.", 9) == 0)
    return 1;
  return 0;
}

int driver_x_emit_asm_direct_import_only(const char *input_path) {
  if (!input_path)
    return 0;
  if (strstr(input_path, "src/asm/asm.x") != NULL || strstr(input_path, "/asm/asm.x") != NULL)
    return 1;
  if (strstr(input_path, "src/asm/asm_seed_full.x") != NULL ||
      strstr(input_path, "/asm/asm_seed_full.x") != NULL)
    return 1;
  return 0;
}

int driver_x_emit_asm_dep_parse_skip_typeck_ok(const char *input_path, const char *dep_path) {
  if (!driver_x_emit_asm_direct_import_only(input_path) || !dep_path)
    return 0;
  return strcmp(dep_path, "backend") == 0;
}

/* --- G-02f-292: argv state field helpers --- */

void driver_compile_argv_copy_path_c(DriverCompileStateSU *state, uint8_t *arg_buf, int32_t plen) {
  int32_t k;
  int32_t n;
  if (!state || !arg_buf || plen <= 0)
    return;
  n = plen;
  if (n > 511)
    n = 511;
  for (k = 0; k < n; k++)
    state->path_buf[k] = arg_buf[k];
  state->path_len = n;
}

/** `-freestanding`：置 use_freestanding 并同步 driver_freestanding_set（S4 nostdlib 链）。 */
void driver_compile_argv_set_use_freestanding_c(DriverCompileStateSU *state) {
  if (!state)
    return;
  state->use_freestanding = 1;
  driver_freestanding_set(1);
  cfg_set_freestanding(1);
}

/** `-legacy-f32-abi`：等价 XLANG_ABI_F32_XMM=0。 */
void driver_compile_argv_set_legacy_f32_abi_c(void) {
  setenv("XLANG_ABI_F32_XMM", "0", 1);
}

/** `-fsanitize=address`：M-6 debug 边界插桩。 */
void driver_compile_argv_set_sanitize_address_c(void) {
  driver_sanitize_address_set(1);
}

/**
 * 扫描 argv 是否含 `-h` 或 `--help`。
 * 返回 1 表示应打印用法并 exit 0。
 */
int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t *argv_opaque) {
  char **argv = (char **)argv_opaque;
  char buf[16];
  int len;
  int i;

  if (argc < 2 || !argv)
    return 0;
  for (i = 1; i < argc; i++) {
    len = driver_get_argv_i(argc, argv, i, buf, (int)sizeof(buf));
    if (len == 2 && buf[0] == '-' && buf[1] == 'h')
      return 1;
    if (len == 6 && !memcmp(buf, "--help", 6))
      return 1;
  }
  return 0;
}

/* --- G-02f-294: init / ensure_default_lib / append_lib_root --- */

/** parse_argv -L 分支：直接用 state 指针作 sidecar 键。 */
void driver_compile_append_lib_root_c(DriverCompileStateSU *state, uint8_t *path, int32_t len) {
  if (!state || !path || len <= 0)
    return;
  (void)driver_emit_append_lib_root((uint8_t *)state, path, len);
}

/**
 * 无显式 -L 时向 sidecar 追加默认 lib_root "."。
 */
void driver_compile_ensure_default_lib_c(uint8_t *key) {
  static const uint8_t dot[1] = {46};
  if (!key)
    return;
  if (driver_emit_lib_root_count(key) == 0)
    (void)driver_emit_append_lib_root(key, (uint8_t *)dot, 1);
}

/**
 * 重置 DriverCompileState 默认值并清空 lib_root sidecar。
 */
void driver_compile_parse_argv_init_c(DriverCompileStateSU *state) {
  if (!state)
    return;
  cfg_reset_compile_target();
  state->path_len = 0;
  state->out_path_len = 0;
  state->use_asm_backend = 1;
  state->target_arch = 0;
  state->target_len = 0;
  state->opt_level_len = 1;
  state->opt_level_buf[0] = (uint8_t)'2';
  state->use_lto = 0;
  state->backend_asm_explicit = 0;
  state->use_freestanding = 0;
  state->parse_saw_target = 0;
  state->target_cpu_len = 0;
  state->target_cpu_features = 0;
  state->print_target_cpu = 0;
  state->parse_saw_target_cpu = 0;
  driver_freestanding_set(0);
  cfg_set_freestanding(0);
  driver_emit_lib_root_reset((uint8_t *)state);
}

/* --- G-02f-293: apply next-token argv helpers --- */

/* Dangling-value guard shared by every value-taking driver-flag parse branch
 * (twin of src/runtime/rt_compile.x driver_compile_argv_next_is_value_c):
 * returns 1 iff argv[i+1] exists, is non-empty, and does not start with '-'.
 * Documented flag values (paths/levels/dirs/triples/cpu names) are never
 * flag-shaped; the run path appends the injected "-o <temp>" pair at the argv
 * tail, so an unconditional i+2 advance would eat it and the product never
 * links (execv ENOENT; reproducer tests/probes/wave943/m6.x). Fetching
 * argv[i+1] clobbers arg_buf — call only after the flag matched.
 * PLATFORM: SHARED. */
int driver_compile_argv_next_is_value_c(int argc, char **argv, int i, char *arg_buf, int arg_cap) {
  int nlen;

  if (!arg_buf || arg_cap <= 0)
    return 0;
  nlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
  if (nlen >= 1 && arg_buf[0] != '-')
    return 1;
  return 0;
}

/** -o：下一 argv 写入 out_path_buf/out_path_len。 */
void driver_compile_argv_apply_minus_o_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i) {
  char **argv = (char **)argv_opaque;
  int32_t olen;

  if (!state || i + 1 >= argc)
    return;
  olen = driver_get_argv_i(argc, argv, i + 1, (char *)state->out_path_buf, 512);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a path — leave state untouched. */
  if (olen >= 1 && state->out_path_buf[0] == '-')
    return;
  if (olen >= 0)
    state->out_path_len = olen;
}

/** -L：下一 argv 经 arg_buf 追加 lib_root sidecar。 */
void driver_compile_argv_apply_minus_L_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                               int32_t i, uint8_t *arg_buf, int32_t arg_cap) {
  char **argv = (char **)argv_opaque;
  int32_t llen;

  if (!state || !arg_buf || arg_cap <= 0 || i + 1 >= argc)
    return;
  llen = driver_get_argv_i(argc, argv, i + 1, (char *)arg_buf, arg_cap);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a lib dir — leave state untouched. */
  if (llen >= 1 && arg_buf[0] == '-')
    return;
  if (llen >= 0)
    driver_compile_append_lib_root_c(state, arg_buf, llen);
}

/** -O：下一 argv 写入 opt_level_buf/opt_level_len。 */
void driver_compile_argv_apply_minus_O_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i) {
  char **argv = (char **)argv_opaque;
  int32_t olen;

  if (!state || i + 1 >= argc)
    return;
  olen = driver_get_argv_i(argc, argv, i + 1, (char *)state->opt_level_buf, 8);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not an opt level — leave state untouched. */
  if (olen >= 1 && state->opt_level_buf[0] == '-')
    return;
  if (olen >= 0)
    state->opt_level_len = olen;
}

/** -backend <asm|c>：更新 use_asm_backend/backend_asm_explicit。 */
void driver_compile_argv_apply_backend_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i, uint8_t *arg_buf, int32_t arg_cap) {
  char **argv = (char **)argv_opaque;
  int32_t vlen;

  if (!state || !arg_buf || arg_cap <= 0 || i + 1 >= argc)
    return;
  vlen = driver_get_argv_i(argc, argv, i + 1, (char *)arg_buf, arg_cap);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not "asm"/"c" — leave state untouched. */
  if (vlen >= 1 && arg_buf[0] == '-')
    return;
  if (vlen >= 0 && drv_eq_asm_word((char *)arg_buf, vlen)) {
    state->use_asm_backend = 1;
    state->backend_asm_explicit = 1;
  }
  if (vlen >= 0 && drv_eq_c_word((char *)arg_buf, vlen)) {
    state->use_asm_backend = 0;
    state->backend_asm_explicit = 0;
  }
}

/** -target：写入 target_buf/target_len/parse_saw_target/target_arch。 */
void driver_compile_argv_apply_target_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                             int32_t i) {
  char **argv = (char **)argv_opaque;
  int32_t tlen;

  if (!state || i + 1 >= argc)
    return;
  tlen = driver_get_argv_i(argc, argv, i + 1, (char *)state->target_buf, 512);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a triple — leave state untouched. */
  if (tlen >= 1 && state->target_buf[0] == '-')
    return;
  state->parse_saw_target = 1;
  if (tlen >= 0) {
    state->target_len = tlen;
    if (drv_target_has_arm((char *)state->target_buf, tlen))
      state->target_arch = 1;
  }
}

/** `-target-cpu`：下一 argv 写入 target_cpu_buf/target_cpu_len。 */
void driver_compile_argv_apply_target_cpu_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                                  int32_t i) {
  char **argv = (char **)argv_opaque;
  int32_t tlen;

  if (!state || i + 1 >= argc)
    return;
  tlen = driver_get_argv_i(argc, argv, i + 1, (char *)state->target_cpu_buf, 64);
  /* Dangling guard (twin of driver_compile_argv_next_is_value_c): a
   * flag-shaped next entry is not a cpu name — leave state untouched. */
  if (tlen >= 1 && state->target_cpu_buf[0] == '-')
    return;
  state->parse_saw_target_cpu = 1;
  if (tlen >= 0)
    state->target_cpu_len = tlen;
}

/* --- G-02f-295: parse_argv_step + scan --- */

/**
 * 处理 argv[i] 一项；返回下一 argv 下标。
 */
int driver_compile_parse_argv_step_c(int argc, char **argv, DriverCompileStateSU *state, int i, char *arg_buf,
                                     int arg_cap) {
  int len = driver_get_argv_i(argc, argv, i, arg_buf, arg_cap);
  if (len < 0)
    return i + 1;
  if (drv_eq_minus_o(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-o" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int olen = driver_get_argv_i(argc, argv, i + 1, (char *)state->out_path_buf, 512);
    if (olen >= 0)
      state->out_path_len = olen;
    return i + 2;
  }
  if (drv_eq_minus_L(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-L" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int llen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
    if (llen >= 0)
      driver_compile_append_lib_root_c(state, (uint8_t *)arg_buf, llen);
    return i + 2;
  }
  if (drv_eq_minus_O(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-O" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int olen = driver_get_argv_i(argc, argv, i + 1, (char *)state->opt_level_buf, 8);
    if (olen >= 0)
      state->opt_level_len = olen;
    return i + 2;
  }
  if (drv_eq_flto(arg_buf, len)) {
    state->use_lto = 1;
    return i + 1;
  }
  if (drv_eq_minus_freestanding(arg_buf, len)) {
    driver_compile_argv_set_use_freestanding_c(state);
    return i + 1;
  }
  if (drv_eq_legacy_f32_abi(arg_buf, len)) {
    driver_compile_argv_set_legacy_f32_abi_c();
    return i + 1;
  }
  if (drv_eq_fsanitize_address(arg_buf, len)) {
    driver_sanitize_address_set(1);
    return i + 1;
  }
  if (drv_eq_minus_backend(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-backend" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int vlen = driver_get_argv_i(argc, argv, i + 1, arg_buf, arg_cap);
    if (vlen >= 0 && drv_eq_asm_word(arg_buf, vlen)) {
      state->use_asm_backend = 1;
      state->backend_asm_explicit = 1;
    }
    if (vlen >= 0 && drv_eq_c_word(arg_buf, vlen)) {
      state->use_asm_backend = 0;
      state->backend_asm_explicit = 0;
    }
    return i + 2;
  }
  if (drv_eq_minus_target(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-target" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int tlen;
    state->parse_saw_target = 1;
    tlen = driver_get_argv_i(argc, argv, i + 1, (char *)state->target_buf, 512);
    if (tlen >= 0) {
      state->target_len = tlen;
      if (drv_target_has_arm((char *)state->target_buf, tlen))
        state->target_arch = 1;
    }
    return i + 2;
  }
  if (drv_eq_minus_target_cpu(arg_buf, len) && i + 1 < argc) {
    /* Dangling guard: flag-shaped/missing next → skip "-target-cpu" standalone. */
    if (!driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap))
      return i + 1;
    int tlen;
    state->parse_saw_target_cpu = 1;
    tlen = driver_get_argv_i(argc, argv, i + 1, (char *)state->target_cpu_buf, 64);
    if (tlen >= 0)
      state->target_cpu_len = tlen;
    return i + 2;
  }
  if (drv_eq_print_target_cpu(arg_buf, len)) {
    state->print_target_cpu = 1;
    return i + 1;
  }
  if (arg_buf[0] != '-' && drv_path_ends_x(arg_buf, len))
    driver_compile_argv_copy_path_c(state, (uint8_t *)arg_buf, len);
  return i + 1;
}

void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t *argv_opaque, DriverCompileStateSU *state) {
  char **argv = (char **)argv_opaque;
  char arg_buf[512];
  int i;

  if (argc < 2 || !state)
    return;
  for (i = 1; i < argc;)
    i = driver_compile_parse_argv_step_c(argc, argv, state, i, arg_buf, (int)sizeof arg_buf);
}

/* --- G-02f-296: impl + resolve + cfg_sync + state alloc/free --- */

/**
 * finalize：按 target_cpu_buf（空则 native）解析 feature 掩码。
 */
void driver_compile_resolve_target_cpu_c(DriverCompileStateSU *state) {
  const char *spec;
  size_t spec_len;
  uint32_t feats = 0;

  if (!state)
    return;
  spec = "native";
  spec_len = 6;
  if (state->target_cpu_len > 0) {
    spec = (const char *)state->target_cpu_buf;
    spec_len = (size_t)state->target_cpu_len;
  }
  if (xlang_target_cpu_resolve(spec, spec_len, &feats) != 0) {
    diag_report_with_code(NULL, 0, 0, "note", NULL, "unknown -target-cpu; using generic baseline", NULL);
    feats = xlang_target_cpu_generic_for_host();
  }
  state->target_cpu_features = (int32_t)feats;
}

/** B-02：按 DriverCompileState 的 -target 同步 #[cfg] 求值上下文。 */
void cfg_sync_compile_target_from_state_c(void *state) {
  DriverCompileStateSU *st = (DriverCompileStateSU *)state;
  if (st && st->parse_saw_target && st->target_len > 0)
    cfg_apply_compile_target_from_triple((const char *)st->target_buf, st->target_len);
  else
    cfg_reset_compile_target();
}

/**
 * 完整 argv 解析：init → scan → finalize。
 */
int32_t driver_compile_parse_argv_impl_c(int32_t argc, uint8_t *argv_opaque, DriverCompileStateSU *state) {
  if (argc < 2 || !state)
    return 1;
  driver_compile_parse_argv_init_c(state);
  driver_compile_parse_argv_scan_c(argc, argv_opaque, state);
  driver_compile_resolve_target_cpu_c(state);
  if (state->print_target_cpu)
    return 0;
  if (state->path_len <= 0)
    return 1;
  state->target_arch = driver_resolve_target_arch(state->target_arch, state->parse_saw_target);
  cfg_sync_compile_target_from_state_c(state);
  driver_compile_ensure_default_lib_c((uint8_t *)state);
  return 0;
}

DriverCompileStateSU *driver_compile_state_alloc_c(void) {
  DriverCompileStateSU *state;

  state = (DriverCompileStateSU *)malloc(sizeof(DriverCompileStateSU));
  if (!state)
    return NULL;
  memset(state, 0, sizeof(*state));
  state->use_asm_backend = 1;
  state->opt_level_buf[0] = (uint8_t)'2';
  state->opt_level_len = 1;
  return state;
}

void driver_compile_state_free_c(DriverCompileStateSU *state) {
  if (state)
    free(state);
}

#else /* XLANG_RT_COMPILE_FROM_X：产品 rest 仅前向声明；业务体在 .x */

int driver_deps_are_std_core_closure_only(char **dep_paths, int n_deps);
int driver_x_emit_asm_dep_parse_only_ok(const char *input_path, const char *dep_path);
int driver_x_emit_asm_direct_import_only(const char *input_path);
int driver_x_emit_asm_dep_parse_skip_typeck_ok(const char *input_path, const char *dep_path);
void driver_compile_argv_copy_path_c(DriverCompileStateSU *state, uint8_t *arg_buf, int32_t plen);
void driver_compile_argv_set_use_freestanding_c(DriverCompileStateSU *state);
void driver_compile_argv_set_legacy_f32_abi_c(void);
void driver_compile_argv_set_sanitize_address_c(void);
int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t *argv_opaque);
void driver_compile_append_lib_root_c(DriverCompileStateSU *state, uint8_t *path, int32_t len);
void driver_compile_ensure_default_lib_c(uint8_t *key);
void driver_compile_parse_argv_init_c(DriverCompileStateSU *state);
void driver_compile_argv_apply_minus_o_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i);
void driver_compile_argv_apply_minus_L_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                               int32_t i, uint8_t *arg_buf, int32_t arg_cap);
void driver_compile_argv_apply_minus_O_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i);
void driver_compile_argv_apply_backend_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                              int32_t i, uint8_t *arg_buf, int32_t arg_cap);
void driver_compile_argv_apply_target_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                             int32_t i);
void driver_compile_argv_apply_target_cpu_next_c(DriverCompileStateSU *state, int32_t argc, uint8_t *argv_opaque,
                                                  int32_t i);
int driver_compile_parse_argv_step_c(int argc, char **argv, DriverCompileStateSU *state, int i, char *arg_buf,
                                     int arg_cap);
void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t *argv_opaque, DriverCompileStateSU *state);
void driver_compile_resolve_target_cpu_c(DriverCompileStateSU *state);
void cfg_sync_compile_target_from_state_c(void *state);
int32_t driver_compile_parse_argv_impl_c(int32_t argc, uint8_t *argv_opaque, DriverCompileStateSU *state);
DriverCompileStateSU *driver_compile_state_alloc_c(void);
void driver_compile_state_free_c(DriverCompileStateSU *state);

#endif /* XLANG_RT_COMPILE_FROM_X */

int labi_rt_compile_slice_marker(void) {
  return 1;
}
