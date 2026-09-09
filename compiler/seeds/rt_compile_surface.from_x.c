/* seeds/rt_compile_surface.from_x.c
 * G-02f rt_compile R2 full surface — isomorphic with src/runtime/rt_compile.x
 * Product PREFER_X_O: g05_try_x_to_o(rt_compile.x) + rest seed marker under FROM_X
 * Prove: full.x vs this seed → nm IDENTICAL (25 public + helpers)
 * Regen: ./xlang -E ... src/runtime/rt_compile.x | filter DBG + polish prologue
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
#include <fcntl.h>
#include <errno.h>
struct RtCompileState {
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
};

extern int32_t rt_cmp_starts_with_n(uint8_t * s, uint8_t * pref, size_t n);
extern int32_t rt_cmp_eq(uint8_t * s, uint8_t * lit);
extern int32_t rt_cmp_contains(uint8_t * hay, uint8_t * needle);
extern int32_t driver_deps_are_std_core_closure_only(uint8_t * * dep_paths, int32_t n_deps);
extern int32_t driver_x_emit_asm_dep_parse_only_ok(uint8_t * input_path, uint8_t * dep_path);
extern int32_t driver_x_emit_asm_direct_import_only(uint8_t * input_path);
extern int32_t driver_x_emit_asm_dep_parse_skip_typeck_ok(uint8_t * input_path, uint8_t * dep_path);
extern void driver_compile_argv_copy_path_c(struct RtCompileState * state, uint8_t * arg_buf, int32_t plen);
extern void driver_compile_argv_set_use_freestanding_c(struct RtCompileState * state);
extern void driver_compile_argv_set_legacy_f32_abi_c(void);
extern void driver_compile_argv_set_sanitize_address_c(void);
extern int32_t rt_help_token_is(uint8_t * buf, int32_t len);
extern int32_t rt_is_help_at(int32_t argc, uint8_t * * argv, int32_t i, uint8_t * buf);
extern int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t * * argv);
extern void driver_compile_append_lib_root_c(struct RtCompileState * state, uint8_t * path, int32_t len);
extern void driver_compile_ensure_default_lib_c(uint8_t * key);
extern void driver_compile_parse_argv_init_c(struct RtCompileState * state);
extern void driver_compile_argv_apply_minus_o_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i);
extern void driver_compile_argv_apply_minus_L_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_minus_O_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i);
extern void driver_compile_argv_apply_backend_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void driver_compile_argv_apply_target_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i);
extern void driver_compile_argv_apply_target_cpu_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i);
extern int32_t driver_compile_parse_argv_step_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state, int32_t i, uint8_t * arg_buf, int32_t arg_cap);
extern void rt_parse_argv_scan_at(int32_t argc, uint8_t * * argv, struct RtCompileState * state, int32_t i, uint8_t * arg_buf);
extern void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state);
extern void driver_compile_resolve_target_cpu_c(struct RtCompileState * state);
extern void cfg_sync_compile_target_from_state_c(uint8_t * state);
extern int32_t driver_compile_parse_argv_impl_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state);
extern struct RtCompileState * driver_compile_state_alloc_c(void);
extern void driver_compile_state_free_c(struct RtCompileState * state);
extern void driver_freestanding_set(int32_t on);
extern void cfg_set_freestanding(int32_t on);
extern void driver_sanitize_address_set(int32_t on);
extern int32_t driver_get_argv_i(int32_t argc, uint8_t * * argv, int32_t i, uint8_t * buf, int32_t max);
extern void cfg_reset_compile_target(void);
extern int32_t driver_emit_lib_root_count(uint8_t * state);
extern int32_t driver_emit_append_lib_root(uint8_t * state, uint8_t * path, int32_t len);
extern void driver_emit_lib_root_reset(uint8_t * state);
extern int32_t drv_eq_minus_o(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_L(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_O(uint8_t * buf, int32_t len);
extern int32_t drv_eq_flto(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_freestanding(uint8_t * buf, int32_t len);
extern int32_t drv_eq_legacy_f32_abi(uint8_t * buf, int32_t len);
extern int32_t drv_eq_fsanitize_address(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_backend(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target(uint8_t * buf, int32_t len);
extern int32_t drv_eq_minus_target_cpu(uint8_t * buf, int32_t len);
extern int32_t drv_eq_print_target_cpu(uint8_t * buf, int32_t len);
extern int32_t drv_eq_asm_word(uint8_t * buf, int32_t len);
extern int32_t drv_eq_c_word(uint8_t * buf, int32_t len);
extern int32_t drv_path_ends_x(uint8_t * buf, int32_t len);
extern int32_t drv_target_has_arm(uint8_t * buf, int32_t len);
extern int32_t xlang_target_cpu_resolve(uint8_t * spec, size_t spec_len, uint32_t * out);
extern uint32_t xlang_target_cpu_generic_for_host(void);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern void cfg_apply_compile_target_from_triple(uint8_t * triple, int32_t len);
extern int32_t driver_resolve_target_arch(int32_t parsed_target, int32_t saw_target_flag);
int32_t rt_cmp_starts_with_n(uint8_t * s, uint8_t * pref, size_t n) {
  if ((s ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((pref ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    if ((strncmp(s, pref, n) ==0)) {
      return 1;
    }
  }
  return 0;
}
int32_t rt_cmp_eq(uint8_t * s, uint8_t * lit) {
  if ((s ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((lit ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    if ((strcmp(s, lit) ==0)) {
      return 1;
    }
  }
  return 0;
}
int32_t rt_cmp_contains(uint8_t * hay, uint8_t * needle) {
  uint8_t * p = ((uint8_t *)(0));
  if ((hay ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((needle ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    (void)((p = strstr(hay, needle)));
  }
  if ((p !=((uint8_t *)(0)))) {
    return 1;
  }
  return 0;
}
int32_t driver_deps_are_std_core_closure_only(uint8_t * * dep_paths, int32_t n_deps) {
  int32_t k = 0;
  uint8_t * p = ((uint8_t *)(0));
  uint8_t * pref_std = ((uint8_t *)(0));
  uint8_t * pref_core = ((uint8_t *)(0));
  if ((n_deps <=0)) {
    return 0;
  }
  {
    (void)((pref_std = ((uint8_t *)((uint8_t[]){115, 116, 100, 46, 0 }))));
    (void)((pref_core = ((uint8_t *)((uint8_t[]){99, 111, 114, 101, 46, 0 }))));
  }
  (void)((k = 0));
  while ((k < n_deps)) {
    (void)((p = (dep_paths)[k]));
    if ((p ==((uint8_t *)(0)))) {
      return 0;
    }
    if (((p)[0] ==0)) {
      return 0;
    }
    if ((rt_cmp_starts_with_n(p, pref_std, ((size_t)(4))) !=0)) {
      (void)((k = (k + 1)));
      continue;
    }
    if ((rt_cmp_starts_with_n(p, pref_core, ((size_t)(5))) !=0)) {
      (void)((k = (k + 1)));
      continue;
    }
    return 0;
  }
  return 1;
}
int32_t driver_x_emit_asm_dep_parse_only_ok(uint8_t * input_path, uint8_t * dep_path) {
  uint8_t * n_asm = ((uint8_t *)(0));
  uint8_t * n_asm2 = ((uint8_t *)(0));
  uint8_t * d_ast = ((uint8_t *)(0));
  uint8_t * d_cg = ((uint8_t *)(0));
  uint8_t * d_be = ((uint8_t *)(0));
  uint8_t * d_ph = ((uint8_t *)(0));
  uint8_t * p_asm = ((uint8_t *)(0));
  uint8_t * p_arch = ((uint8_t *)(0));
  uint8_t * p_plat = ((uint8_t *)(0));
  if ((input_path ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((dep_path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    (void)((n_asm = ((uint8_t *)((uint8_t[]){115, 114, 99, 47, 97, 115, 109, 47, 97, 115, 109, 46, 120, 0 }))));
    (void)((n_asm2 = ((uint8_t *)((uint8_t[]){47, 97, 115, 109, 47, 97, 115, 109, 46, 120, 0 }))));
    (void)((d_ast = ((uint8_t *)((uint8_t[]){97, 115, 116, 0 }))));
    (void)((d_cg = ((uint8_t *)((uint8_t[]){99, 111, 100, 101, 103, 101, 110, 0 }))));
    (void)((d_be = ((uint8_t *)((uint8_t[]){98, 97, 99, 107, 101, 110, 100, 0 }))));
    (void)((d_ph = ((uint8_t *)((uint8_t[]){112, 101, 101, 112, 104, 111, 108, 101, 0 }))));
    (void)((p_asm = ((uint8_t *)((uint8_t[]){97, 115, 109, 46, 0 }))));
    (void)((p_arch = ((uint8_t *)((uint8_t[]){97, 114, 99, 104, 46, 0 }))));
    (void)((p_plat = ((uint8_t *)((uint8_t[]){112, 108, 97, 116, 102, 111, 114, 109, 46, 0 }))));
  }
  if ((rt_cmp_contains(input_path, n_asm) ==0)) {
    if ((rt_cmp_contains(input_path, n_asm2) ==0)) {
      return 0;
    }
  }
  if ((rt_cmp_eq(dep_path, d_ast) !=0)) {
    return 1;
  }
  if ((rt_cmp_eq(dep_path, d_cg) !=0)) {
    return 1;
  }
  if ((rt_cmp_eq(dep_path, d_be) !=0)) {
    return 1;
  }
  if ((rt_cmp_eq(dep_path, d_ph) !=0)) {
    return 1;
  }
  if ((rt_cmp_starts_with_n(dep_path, p_asm, ((size_t)(4))) !=0)) {
    return 1;
  }
  if ((rt_cmp_starts_with_n(dep_path, p_arch, ((size_t)(5))) !=0)) {
    return 1;
  }
  if ((rt_cmp_starts_with_n(dep_path, p_plat, ((size_t)(9))) !=0)) {
    return 1;
  }
  return 0;
}
int32_t driver_x_emit_asm_direct_import_only(uint8_t * input_path) {
  uint8_t * a1 = ((uint8_t *)(0));
  uint8_t * a2 = ((uint8_t *)(0));
  uint8_t * s1 = ((uint8_t *)(0));
  uint8_t * s2 = ((uint8_t *)(0));
  if ((input_path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    (void)((a1 = ((uint8_t *)((uint8_t[]){115, 114, 99, 47, 97, 115, 109, 47, 97, 115, 109, 46, 120, 0 }))));
    (void)((a2 = ((uint8_t *)((uint8_t[]){47, 97, 115, 109, 47, 97, 115, 109, 46, 120, 0 }))));
    (void)((s1 = ((uint8_t *)((uint8_t[]){115, 114, 99, 47, 97, 115, 109, 47, 97, 115, 109, 95, 115, 101, 101, 100, 95, 102, 117, 108, 108, 46, 120, 0 }))));
    (void)((s2 = ((uint8_t *)((uint8_t[]){47, 97, 115, 109, 47, 97, 115, 109, 95, 115, 101, 101, 100, 95, 102, 117, 108, 108, 46, 120, 0 }))));
  }
  if ((rt_cmp_contains(input_path, a1) !=0)) {
    return 1;
  }
  if ((rt_cmp_contains(input_path, a2) !=0)) {
    return 1;
  }
  if ((rt_cmp_contains(input_path, s1) !=0)) {
    return 1;
  }
  if ((rt_cmp_contains(input_path, s2) !=0)) {
    return 1;
  }
  return 0;
}
int32_t driver_x_emit_asm_dep_parse_skip_typeck_ok(uint8_t * input_path, uint8_t * dep_path) {
  uint8_t * be = ((uint8_t *)(0));
  if ((driver_x_emit_asm_direct_import_only(input_path) ==0)) {
    return 0;
  }
  if ((dep_path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    (void)((be = ((uint8_t *)((uint8_t[]){98, 97, 99, 107, 101, 110, 100, 0 }))));
  }
  if ((rt_cmp_eq(dep_path, be) !=0)) {
    return 1;
  }
  return 0;
}
void driver_compile_argv_copy_path_c(struct RtCompileState * state, uint8_t * arg_buf, int32_t plen) {
  int32_t k = 0;
  int32_t n = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return;
  }
  if ((plen <=0)) {
    return;
  }
  (void)((n = plen));
  if ((n > 511)) {
    (void)((n = 511));
  }
  (void)((k = 0));
  while ((k < n)) {
    (void)((((state->path_buf))[k] = (arg_buf)[k]));
    (void)((k = (k + 1)));
  }
  (void)(((state->path_len) = n));
}
void driver_compile_argv_set_use_freestanding_c(struct RtCompileState * state) {
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  (void)(((state->use_freestanding) = 1));
  {
    (void)(driver_freestanding_set(1));
    (void)(cfg_set_freestanding(1));
  }
}
void driver_compile_argv_set_legacy_f32_abi_c(void) {
  uint8_t * name = ((uint8_t *)(0));
  uint8_t * val = ((uint8_t *)(0));
  {
    (void)((name = ((uint8_t *)((uint8_t[]){83, 72, 85, 88, 95, 65, 66, 73, 95, 70, 51, 50, 95, 88, 77, 77, 0 }))));
    (void)((val = ((uint8_t *)((uint8_t[]){48, 0 }))));
    (void)(setenv(name, val, 1));
  }
  (void)(0);
  return;
}
void driver_compile_argv_set_sanitize_address_c(void) {
  {
    (void)(driver_sanitize_address_set(1));
  }
  (void)(0);
  return;
}
int32_t rt_help_token_is(uint8_t * buf, int32_t len) {
  if ((buf ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((len ==2)) {
    if (((buf)[0] ==45)) {
      if (((buf)[1] ==104)) {
        return 1;
      }
    }
  }
  if ((len ==6)) {
    if (((buf)[0] ==45)) {
      if (((buf)[1] ==45)) {
        if (((buf)[2] ==104)) {
          if (((buf)[3] ==101)) {
            if (((buf)[4] ==108)) {
              if (((buf)[5] ==112)) {
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
int32_t rt_is_help_at(int32_t argc, uint8_t * * argv, int32_t i, uint8_t * buf) {
  int32_t len = 0;
  if ((i >=argc)) {
    return 0;
  }
  if ((buf ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    (void)((len = driver_get_argv_i(argc, argv, i, buf, 16)));
  }
  if ((rt_help_token_is(buf, len) !=0)) {
    return 1;
  }
  return rt_is_help_at(argc, argv, (i + 1), buf);
}
int32_t driver_compile_argv_is_help_c(int32_t argc, uint8_t * * argv) {
  uint8_t * buf = ((uint8_t *)(0));
  int32_t hit = 0;
  if ((argc < 2)) {
    return 0;
  }
  {
    (void)((buf = malloc(((size_t)(16)))));
  }
  if ((buf ==((uint8_t *)(0)))) {
    return 0;
  }
  (void)((hit = rt_is_help_at(argc, argv, 1, buf)));
  {
    (void)(free(buf));
  }
  return hit;
}
void driver_compile_append_lib_root_c(struct RtCompileState * state, uint8_t * path, int32_t len) {
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if ((path ==((uint8_t *)(0)))) {
    return;
  }
  if ((len <=0)) {
    return;
  }
  {
    (void)(driver_emit_append_lib_root(((uint8_t *)(state)), path, len));
  }
  (void)(0);
  return;
}
void driver_compile_ensure_default_lib_c(uint8_t * key) {
  uint8_t ch = 46;
  if ((key ==((uint8_t *)(0)))) {
    return;
  }
  {
    if ((driver_emit_lib_root_count(key) ==0)) {
      (void)(driver_emit_append_lib_root(key, &(ch), 1));
    }
  }
  (void)(0);
  return;
}
void driver_compile_parse_argv_init_c(struct RtCompileState * state) {
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  {
    (void)(cfg_reset_compile_target());
  }
  (void)(((state->path_len) = 0));
  (void)(((state->out_path_len) = 0));
  (void)(((state->use_asm_backend) = 1));
  (void)(((state->target_arch) = 0));
  (void)(((state->target_len) = 0));
  (void)(((state->opt_level_len) = 1));
  (void)((((state->opt_level_buf))[0] = 50));
  (void)(((state->use_lto) = 0));
  (void)(((state->backend_asm_explicit) = 0));
  (void)(((state->use_freestanding) = 0));
  (void)(((state->parse_saw_target) = 0));
  (void)(((state->target_cpu_len) = 0));
  (void)(((state->target_cpu_features) = 0));
  (void)(((state->print_target_cpu) = 0));
  (void)(((state->parse_saw_target_cpu) = 0));
  {
    (void)(driver_freestanding_set(0));
    (void)(cfg_set_freestanding(0));
    (void)(driver_emit_lib_root_reset(((uint8_t *)(state))));
  }
}
int32_t driver_compile_argv_next_is_value_c(int32_t argc, uint8_t * * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  int32_t nlen = 0;
  if ((arg_buf ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((arg_cap <=0)) {
    return 0;
  }
  {
    (void)((nlen = driver_get_argv_i(argc, argv, (i + 1), arg_buf, arg_cap)));
  }
  if ((nlen >=1)) {
    if ((arg_buf[0] !=45)) {
      return 1;
    }
  }
  return 0;
}
void driver_compile_argv_apply_minus_o_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i) {
  int32_t olen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((olen = driver_get_argv_i(argc, argv, (i + 1), &(((state->out_path_buf))[0]), 512)));
  }
  if ((olen >=1)) {
    if ((state->out_path_buf[0] ==45)) {
      return;
    }
  }
  if ((olen >=0)) {
    (void)(((state->out_path_len) = olen));
  }
  (void)(0);
  return;
}
void driver_compile_argv_apply_minus_L_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  int32_t llen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return;
  }
  if ((arg_cap <=0)) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((llen = driver_get_argv_i(argc, argv, (i + 1), arg_buf, arg_cap)));
  }
  if ((llen >=1)) {
    if ((arg_buf[0] ==45)) {
      return;
    }
  }
  if ((llen >=0)) {
    (void)(driver_compile_append_lib_root_c(state, arg_buf, llen));
  }
  (void)(0);
  return;
}
void driver_compile_argv_apply_minus_O_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i) {
  int32_t olen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((olen = driver_get_argv_i(argc, argv, (i + 1), &(((state->opt_level_buf))[0]), 8)));
  }
  if ((olen >=1)) {
    if ((state->opt_level_buf[0] ==45)) {
      return;
    }
  }
  if ((olen >=0)) {
    (void)(((state->opt_level_len) = olen));
  }
  (void)(0);
  return;
}
void driver_compile_argv_apply_backend_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  int32_t vlen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return;
  }
  if ((arg_cap <=0)) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((vlen = driver_get_argv_i(argc, argv, (i + 1), arg_buf, arg_cap)));
  }
  if ((vlen >=1)) {
    if ((arg_buf[0] ==45)) {
      return;
    }
  }
  if ((vlen >=0)) {
    {
      if ((drv_eq_asm_word(arg_buf, vlen) !=0)) {
        (void)(((state->use_asm_backend) = 1));
        (void)(((state->backend_asm_explicit) = 1));
      }
      if ((drv_eq_c_word(arg_buf, vlen) !=0)) {
        (void)(((state->use_asm_backend) = 0));
        (void)(((state->backend_asm_explicit) = 0));
      }
    }
  }
  (void)(0);
  return;
}
void driver_compile_argv_apply_target_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i) {
  int32_t tlen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((tlen = driver_get_argv_i(argc, argv, (i + 1), &(((state->target_buf))[0]), 512)));
  }
  if ((tlen >=1)) {
    if ((state->target_buf[0] ==45)) {
      return;
    }
  }
  (void)(((state->parse_saw_target) = 1));
  if ((tlen >=0)) {
    (void)(((state->target_len) = tlen));
    {
      if ((drv_target_has_arm(&(((state->target_buf))[0]), tlen) !=0)) {
        (void)(((state->target_arch) = 1));
      }
    }
  }
}
void driver_compile_argv_apply_target_cpu_next_c(struct RtCompileState * state, int32_t argc, uint8_t * * argv, int32_t i) {
  int32_t tlen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if (((i + 1) >=argc)) {
    return;
  }
  {
    (void)((tlen = driver_get_argv_i(argc, argv, (i + 1), &(((state->target_cpu_buf))[0]), 64)));
  }
  if ((tlen >=1)) {
    if ((state->target_cpu_buf[0] ==45)) {
      return;
    }
  }
  (void)(((state->parse_saw_target_cpu) = 1));
  if ((tlen >=0)) {
    (void)(((state->target_cpu_len) = tlen));
  }
}
int32_t driver_compile_parse_argv_step_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state, int32_t i, uint8_t * arg_buf, int32_t arg_cap) {
  int32_t len = 0;
  int32_t olen = 0;
  int32_t llen = 0;
  int32_t vlen = 0;
  int32_t tlen = 0;
  if ((state ==((struct RtCompileState *)(0)))) {
    return (i + 1);
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return (i + 1);
  }
  if ((arg_cap <=0)) {
    return (i + 1);
  }
  {
    (void)((len = driver_get_argv_i(argc, argv, i, arg_buf, arg_cap)));
  }
  if ((len < 0)) {
    return (i + 1);
  }
  {
    if ((drv_eq_minus_o(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        {
          (void)((olen = driver_get_argv_i(argc, argv, (i + 1), &(((state->out_path_buf))[0]), 512)));
        }
        if ((olen >=0)) {
          (void)(((state->out_path_len) = olen));
        }
        return (i + 2);
      }
    }
    if ((drv_eq_minus_L(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        {
          (void)((llen = driver_get_argv_i(argc, argv, (i + 1), arg_buf, arg_cap)));
        }
        if ((llen >=0)) {
          (void)(driver_compile_append_lib_root_c(state, arg_buf, llen));
        }
        return (i + 2);
      }
    }
    if ((drv_eq_minus_O(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        {
          (void)((olen = driver_get_argv_i(argc, argv, (i + 1), &(((state->opt_level_buf))[0]), 8)));
        }
        if ((olen >=0)) {
          (void)(((state->opt_level_len) = olen));
        }
        return (i + 2);
      }
    }
    if ((drv_eq_flto(arg_buf, len) !=0)) {
      (void)(((state->use_lto) = 1));
      return (i + 1);
    }
    if ((drv_eq_minus_freestanding(arg_buf, len) !=0)) {
      (void)(driver_compile_argv_set_use_freestanding_c(state));
      return (i + 1);
    }
    if ((drv_eq_legacy_f32_abi(arg_buf, len) !=0)) {
      (void)(driver_compile_argv_set_legacy_f32_abi_c());
      return (i + 1);
    }
    if ((drv_eq_fsanitize_address(arg_buf, len) !=0)) {
      (void)(driver_sanitize_address_set(1));
      return (i + 1);
    }
    if ((drv_eq_minus_backend(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        {
          (void)((vlen = driver_get_argv_i(argc, argv, (i + 1), arg_buf, arg_cap)));
        }
        if ((vlen >=0)) {
          if ((drv_eq_asm_word(arg_buf, vlen) !=0)) {
            (void)(((state->use_asm_backend) = 1));
            (void)(((state->backend_asm_explicit) = 1));
          }
          if ((drv_eq_c_word(arg_buf, vlen) !=0)) {
            (void)(((state->use_asm_backend) = 0));
            (void)(((state->backend_asm_explicit) = 0));
          }
        }
        return (i + 2);
      }
    }
    if ((drv_eq_minus_target(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        (void)(((state->parse_saw_target) = 1));
        (void)((tlen = driver_get_argv_i(argc, argv, (i + 1), &(((state->target_buf))[0]), 512)));
        if ((tlen >=0)) {
          (void)(((state->target_len) = tlen));
          if ((drv_target_has_arm(&(((state->target_buf))[0]), tlen) !=0)) {
            (void)(((state->target_arch) = 1));
          }
        }
        return (i + 2);
      }
    }
    if ((drv_eq_minus_target_cpu(arg_buf, len) !=0)) {
      if (((i + 1) <argc)) {
        if ((driver_compile_argv_next_is_value_c(argc, argv, i, arg_buf, arg_cap) ==0)) {
          return (i + 1);
        }
        (void)(((state->parse_saw_target_cpu) = 1));
        (void)((tlen = driver_get_argv_i(argc, argv, (i + 1), &(((state->target_cpu_buf))[0]), 64)));
        if ((tlen >=0)) {
          (void)(((state->target_cpu_len) = tlen));
        }
        return (i + 2);
      }
    }
    if ((drv_eq_print_target_cpu(arg_buf, len) !=0)) {
      (void)(((state->print_target_cpu) = 1));
      return (i + 1);
    }
    if (((arg_buf)[0] !=45)) {
      if ((drv_path_ends_x(arg_buf, len) !=0)) {
        (void)(driver_compile_argv_copy_path_c(state, arg_buf, len));
      }
    }
  }
  return (i + 1);
}
void rt_parse_argv_scan_at(int32_t argc, uint8_t * * argv, struct RtCompileState * state, int32_t i, uint8_t * arg_buf) {
  int32_t ni = 0;
  if ((i >=argc)) {
    return;
  }
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return;
  }
  (void)((ni = driver_compile_parse_argv_step_c(argc, argv, state, i, arg_buf, 512)));
  (void)(rt_parse_argv_scan_at(argc, argv, state, ni, arg_buf));
}
void driver_compile_parse_argv_scan_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state) {
  uint8_t * arg_buf = ((uint8_t *)(0));
  if ((argc < 2)) {
    return;
  }
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  {
    (void)((arg_buf = malloc(((size_t)(512)))));
  }
  if ((arg_buf ==((uint8_t *)(0)))) {
    return;
  }
  (void)(rt_parse_argv_scan_at(argc, argv, state, 1, arg_buf));
  {
    (void)(free(arg_buf));
  }
}
void driver_compile_resolve_target_cpu_c(struct RtCompileState * state) {
  uint8_t * spec = ((uint8_t *)(0));
  size_t spec_len = ((size_t)(0));
  uint32_t feats = 0;
  int32_t rc = 0;
  uint8_t * kind = ((uint8_t *)(0));
  uint8_t * msg = ((uint8_t *)(0));
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  {
    (void)((spec = ((uint8_t *)((uint8_t[]){110, 97, 116, 105, 118, 101, 0 }))));
  }
  (void)((spec_len = ((size_t)(6))));
  if (((state->target_cpu_len) > 0)) {
    (void)((spec = &(((state->target_cpu_buf))[0])));
    (void)((spec_len = ((size_t)((state->target_cpu_len)))));
  }
  {
    (void)((rc = xlang_target_cpu_resolve(spec, spec_len, &(feats))));
  }
  if ((rc !=0)) {
    {
      (void)((kind = ((uint8_t *)((uint8_t[]){110, 111, 116, 101, 0 }))));
      (void)((msg = ((uint8_t *)((uint8_t[]){117, 110, 107, 110, 111, 119, 110, 32, 45, 116, 97, 114, 103, 101, 116, 45, 99, 112, 117, 59, 32, 117, 115, 105, 110, 103, 32, 103, 101, 110, 101, 114, 105, 99, 32, 98, 97, 115, 101, 108, 105, 110, 101, 0 }))));
      (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, ((uint8_t *)(0)), msg, ((uint8_t *)(0))));
      (void)((feats = xlang_target_cpu_generic_for_host()));
    }
  }
  (void)(((state->target_cpu_features) = ((int32_t)(feats))));
}
void cfg_sync_compile_target_from_state_c(uint8_t * state) {
  struct RtCompileState * st = ((struct RtCompileState *)(0));
  if ((state ==((uint8_t *)(0)))) {
    {
      (void)(cfg_reset_compile_target());
    }
    return;
  }
  (void)((st = ((struct RtCompileState *)(state))));
  if (((st->parse_saw_target) !=0)) {
    if (((st->target_len) > 0)) {
      {
        (void)(cfg_apply_compile_target_from_triple(&(((st->target_buf))[0]), (st->target_len)));
      }
      return;
    }
  }
  {
    (void)(cfg_reset_compile_target());
  }
}
int32_t driver_compile_parse_argv_impl_c(int32_t argc, uint8_t * * argv, struct RtCompileState * state) {
  if ((argc < 2)) {
    return 1;
  }
  if ((state ==((struct RtCompileState *)(0)))) {
    return 1;
  }
  (void)(driver_compile_parse_argv_init_c(state));
  (void)(driver_compile_parse_argv_scan_c(argc, argv, state));
  (void)(driver_compile_resolve_target_cpu_c(state));
  if (((state->print_target_cpu) !=0)) {
    return 0;
  }
  if (((state->path_len) <=0)) {
    return 1;
  }
  {
    (void)(((state->target_arch) = driver_resolve_target_arch((state->target_arch), (state->parse_saw_target))));
  }
  (void)(cfg_sync_compile_target_from_state_c(((uint8_t *)(state))));
  (void)(driver_compile_ensure_default_lib_c(((uint8_t *)(state))));
  return 0;
}
struct RtCompileState * driver_compile_state_alloc_c(void) {
  struct RtCompileState * state = ((struct RtCompileState *)(0));
  uint8_t * p = ((uint8_t *)(0));
  /* RtCompileState 总大小=1728B（须与 .x rt_compile.x sz 一致；旧值 1664 堆溢出）。 */
  size_t sz = ((size_t)(1728));
  {
    (void)((p = malloc(sz)));
  }
  if ((p ==((uint8_t *)(0)))) {
    return ((struct RtCompileState *)(0));
  }
  {
    (void)(memset(p, 0, sz));
  }
  (void)((state = ((struct RtCompileState *)(p))));
  (void)(((state->use_asm_backend) = 1));
  (void)((((state->opt_level_buf))[0] = 50));
  (void)(((state->opt_level_len) = 1));
  return state;
}
/* wave1243: declare release so seed free path matches product (sidecar leak → IMP001). */
extern void driver_emit_lib_root_release(uint8_t *state);

void driver_compile_state_free_c(struct RtCompileState * state) {
  if ((state ==((struct RtCompileState *)(0)))) {
    return;
  }
  /* wave1243: release driver_emit lib_root sidecar keyed by this state pointer
   * before free — directory check allocs one state per file; without release the
   * table fills after MAX_DRIVER_EMIT_SIDECARS and -L roots stop applying. */
  driver_emit_lib_root_release((uint8_t *)state);
  {
    (void)(free(((uint8_t *)(state))));
  }
  (void)(0);
  return;
}
