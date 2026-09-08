/* seeds/labi_invoke_ld_list_surface.from_x.c
 * G-02f labi_invoke_ld_list R2 full surface — isomorphic with src/runtime/labi_invoke_ld_list.x
 * Product PREFER_X_O: g05_try_x_to_o(labi_invoke_ld_list.x) + mega rest under FROM_X
 * Prove: full.x vs this seed → nm IDENTICAL (brew/compress/tail/driver pure table
 *   + wave152 ld_append_brew_lib_paths pure orch
 *   + wave153 asm_ld_append_compress_libs pure orch
 *   + wave154 invoke_cc_append_compress_ld pure orch
 *   + wave156 xlang_asm_ld_append_mach_tail_libs_impl pure orch
 *   + wave157 xlang_asm_ld_append_unix_gcc_tail_libs_impl pure orch
 *   + wave158 invoke_cc_append_net_tls_ld pure orch
 *   + wave179 invoke_cc_argv_push_existing pure orch
 *   + wave215 invoke_cc_argv_resolve_existing_path pure thin orch
 *   + wave187 ensure_std_net_o_auto_tls pure orch
 *   + wave188 xlang_ensure_formal_std_make_o pure orch
 *   + wave191 labi_std_append_formal_ensure_for_rel pure orch
 *   + wave192 labi_std_append_glue_for_op pure orch
 *   + wave193 labi_std_append_primary_for_op + process_argv_if pure orch
 *   + wave194 labi_std_append_task_special pure orch
 *   + wave195 labi_std_append_op_std pure orch
 *   + wave196 xlang_asm_ld_append_std_objs_for_user plan shell pure orch
 *   + wave253/259 PRIMARY_PANIC companion user_env ensure+push (≡ .x/cold)
 *   + wave262 private helper short names: labi_std_glue_push_if / op_std_flag_out /
 *     glue_have_for_op / need_process_argv)
 * Cap residual: host_is_apple; needs + ensure + path; resolve_existing_path_impl pool only
 *   (wave255 pure owns skip_missing);
 *   exports_marker / realpath_cap / xlang_rel_o_path_from_argv0; spawn/ld/cc IO mega;
 *   link_abi_getenv / link_abi_system / path_executable / skip_missing for ensure_std_net + formal_std_make
 *     (wave187/188 Cap residual; wave221 X_OK pure; wave222 getenv pure; wave224 system pure);
 *   repo_root + ensure_runtime_* + push_obj for wave191 formal companions;
 *   ensure_runtime_*_glue + path peers for wave192 OP_GLUE_* leaves;
 *   needs + primary ensure/path + process_argv for wave193 primary/complement;
 *   wave253/259 user_env companion on PRIMARY_PANIC (ensure + path + push_obj);
 *   task/scheduler path peers + bank for wave194 TASK_SPECIAL;
 *   fk0/fk1–13 gate peers for wave195 OP_STD;
 *   plan table accessors (labi_std_list L8) for wave196 plan shell
 * Regen: ./xlang_asm -E ... src/runtime/labi_invoke_ld_list.x | filter DBG + polish prologue
 * PLATFORM: SHARED - pure contract; Ubuntu gold + mac prove.
 */
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
extern int32_t link_abi_host_is_apple(void);
extern int32_t xlang_host_is_linux(void);
extern int32_t link_abi_obj_needs_zlib(uint8_t * obj_o);
extern int32_t link_abi_obj_needs_zstd(uint8_t * obj_o);
extern int32_t link_abi_obj_needs_brotli(uint8_t * obj_o);
extern int32_t link_abi_user_o_needs_compress_libs(uint8_t * user_o);
extern int32_t xlang_ensure_runtime_compress_zlib_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_compress_zlib_glue_o_path(uint8_t * argv0);
/* Cap residual (wave215/255): multi-slot realpath pool body only;
 * pure owns null/empty + skip_missing (wave255). */
extern uint8_t * invoke_cc_argv_resolve_existing_path_impl(uint8_t * path);
extern uint8_t * invoke_cc_argv_resolve_existing_path(uint8_t * path);
extern int32_t link_abi_obj_exports_marker(uint8_t * obj_o, uint8_t * marker);
extern uint8_t * link_abi_realpath_cap(uint8_t * path, uint8_t * out);
extern uint8_t * xlang_rel_o_path_from_argv0(uint8_t * argv0, uint8_t * rel);
/* Cap residual (wave187/188 ensure shell make surface).
 * wave221: X_OK via link_abi_path_executable pure thin.
 * wave222: env via link_abi_getenv pure thin.
 * wave224: shell make via link_abi_system pure thin. */
extern uint8_t * link_abi_getenv(uint8_t * name);
/* wave224 G.7: shell make authority = public pure thin link_abi_system (labi_diag_pure). */
extern int32_t link_abi_system(uint8_t * cmd);
extern int32_t strcmp(uint8_t * a, uint8_t * b);
extern int32_t link_abi_path_executable(uint8_t * path);
extern uint8_t * asm_link_obj_skip_missing(uint8_t * path);
/* Peer pure / Cap residual (wave191 formal companions for append_std OP_STD). */
extern uint8_t * xlang_repo_root_from_argv0(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_env_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_env_os_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_random_fill_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_random_fill_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_time_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_time_os_o_path(uint8_t * argv0);
extern int32_t link_abi_asm_ld_push_obj(uint8_t * primary, uint8_t * link_argv0, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, int32_t * flag_out);
/* Cap residual / peer pure (wave192 OP_GLUE_* ensure+path). */
extern int32_t xlang_ensure_runtime_thread_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_thread_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_sync_lock_diag_tls_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_sync_lock_diag_tls_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_sync_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_sync_os_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_ed25519_ref10_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_ed25519_ref10_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_crypto_inc_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_crypto_inc_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_log_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_log_os_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_atomic_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_atomic_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_channel_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_channel_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_backtrace_platform_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_backtrace_platform_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_math_libm_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_math_libm_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_sqlite_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_sqlite_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_dynlib_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_dynlib_os_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_http_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_http_glue_o_path(uint8_t * argv0);
/* wave193 primary/complement peers (ondemand needs + path_pure + process_argv). */
extern int32_t labi_user_needs_runtime_time_os(uint8_t * user_o);
extern int32_t labi_user_needs_runtime_random_fill(uint8_t * user_o);
extern int32_t labi_user_needs_runtime_env_os(uint8_t * user_o);
extern uint8_t * xlang_runtime_asm_io_stubs_o_path(uint8_t * argv0);
extern uint8_t * xlang_runtime_panic_o_path(uint8_t * argv0);
/* wave253/259: PRIMARY_PANIC companion user-domain face (residual declare-only / Linux .s panic). */
extern int32_t xlang_ensure_runtime_link_abi_user_env_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_link_abi_user_env_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_process_argv_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_process_argv_o_path(uint8_t * argv0);
/* Forward: defined later in this surface; formal env companion calls it. */
void labi_std_append_process_argv_if(int32_t need, uint8_t * link_argv0, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la);
/* wave194 TASK_SPECIAL peers (needs_std_task + scheduler path + push_stable + glue). */
extern int32_t labi_user_needs_std_task(uint8_t * user_o);
extern uint8_t * scheduler_o_for_task_link(uint8_t * task_o, uint8_t * explicit_scheduler);
extern uint8_t * xlang_std_async_scheduler_o_path(uint8_t * argv0);
extern uint8_t * xlang_asm_ld_try_under_lib_roots(uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank);
extern void link_abi_asm_ld_argv_push_stable(uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, uint8_t * p);
extern int32_t xlang_ensure_runtime_scheduler_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_scheduler_glue_o_path(uint8_t * argv0);
/* wave188 formal make peer (exported pure). */
extern int32_t xlang_ensure_formal_std_make_o(uint8_t * repo_root, uint8_t * rel_from_repo, uint8_t * make_target);
/* wave195 OP_STD peers (fk0/fk1–13 gates; formal ensure is surface-local export). */
extern int32_t labi_std_fk0_user_needs_rel(uint8_t * user_o, uint8_t * rel);
extern int32_t labi_std_fk_user_needs(uint8_t * user_o, int32_t fk);
/* wave196 plan shell peers (L8 plan table accessors). */
extern int32_t labi_std_plan_count(void);
extern int32_t labi_std_plan_step_at(int32_t i, int32_t * op_out, size_t * rel_out, int32_t * flag_kind_out);

/* wave215/255: invoke_cc_argv_resolve_existing_path pure thin orch (surface pin ≡ .x).
 * Pure: null/empty + skip_missing; Cap residual _impl = multi-slot realpath pool only. */
uint8_t * invoke_cc_argv_resolve_existing_path(uint8_t * path) {
  uint8_t * use;
  if ((path ==((uint8_t *)(0)))) {
    return ((uint8_t *)(0));
  }
  if (((path)[0] ==0)) {
    return ((uint8_t *)(0));
  }
  use = asm_link_obj_skip_missing(path);
  if ((use ==((uint8_t *)(0)))) {
    return ((uint8_t *)(0));
  }
  {
    return invoke_cc_argv_resolve_existing_path_impl(use);
  }
  return ((uint8_t *)(0));
}

int32_t invoke_cc_argv_push_existing(uint8_t * * argv, int32_t * ia, int32_t max_ia, uint8_t * path) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return 0;
  }
  if ((ia ==0)) {
    return 0;
  }
  if ((path ==0)) {
    return 0;
  }
  if (((path)[0] ==0)) {
    return 0;
  }
  int32_t cur = (ia)[0];
  if ((cur >=(max_ia - 1))) {
    return 0;
  }
  uint8_t * use = 0;
  (void)((use = invoke_cc_argv_resolve_existing_path(path)));
  if ((use ==0)) {
    return 0;
  }
  int32_t k = 0;
  while ((k < cur)) {
    uint8_t * exist = (argv)[k];
    if ((exist !=0)) {
      int32_t eq = 1;
      int32_t i0 = 0;
      while ((i0 < 1048576)) {
        uint8_t ca = (exist)[i0];
        uint8_t cb = (use)[i0];
        if ((ca !=cb)) {
          (void)((eq = 0));
          break;
        }
        if ((ca ==0)) {
          break;
        }
        (void)((i0 = (i0 + 1)));
      }
      if ((eq !=0)) {
        return 0;
      }
    }
    (void)((k = (k + 1)));
  }
  (void)(((argv)[cur] = use));
  (void)(((ia)[0] = (cur + 1)));
  return 1;
}
int32_t labi_ld_brew_lib_path_count(void) {
  return 2;
}
uint8_t * labi_ld_brew_lib_path_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x2d\x4c\x2f\x6f\x70\x74\x2f\x68\x6f\x6d\x65\x62\x72\x65\x77\x2f\x6c\x69\x62");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x2d\x4c\x2f\x75\x73\x72\x2f\x6c\x6f\x63\x61\x6c\x2f\x6c\x69\x62");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_ld_flag_lz(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x7a");
  return p;
}
uint8_t * labi_ld_flag_lzstd(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x7a\x73\x74\x64");
  return p;
}
uint8_t * labi_ld_flag_lbrotlienc(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x62\x72\x6f\x74\x6c\x69\x65\x6e\x63");
  return p;
}
uint8_t * labi_ld_flag_lbrotlidec(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x62\x72\x6f\x74\x6c\x69\x64\x65\x63");
  return p;
}
int32_t labi_ld_compress_flag_count(void) {
  return 4;
}
uint8_t * labi_ld_compress_flag_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x7a");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x7a\x73\x74\x64");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x62\x72\x6f\x74\x6c\x69\x65\x6e\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x62\x72\x6f\x74\x6c\x69\x64\x65\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_ld_flag_lm(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x6d");
  return p;
}
uint8_t * labi_ld_flag_lsqlite3(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x73\x71\x6c\x69\x74\x65\x33");
  return p;
}
uint8_t * labi_ld_flag_pthread(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x70\x74\x68\x72\x65\x61\x64");
  return p;
}
uint8_t * labi_ld_flag_lpthread(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x70\x74\x68\x72\x65\x61\x64");
  return p;
}
uint8_t * labi_ld_flag_ldl(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x64\x6c");
  return p;
}
uint8_t * labi_ld_flag_lc(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x63");
  return p;
}
uint8_t * labi_ld_flag_lSystem(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x53\x79\x73\x74\x65\x6d");
  return p;
}
uint8_t * labi_ld_flag_lws2_32(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x77\x73\x32\x5f\x33\x32");
  return p;
}
uint8_t * labi_ld_flag_lbcrypt(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x62\x63\x72\x79\x70\x74");
  return p;
}
uint8_t * labi_ld_flag_L_hb_openssl(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x4c\x2f\x6f\x70\x74\x2f\x68\x6f\x6d\x65\x62\x72\x65\x77\x2f\x6f\x70\x74\x2f\x6f\x70\x65\x6e\x73\x73\x6c\x2f\x6c\x69\x62");
  return p;
}
uint8_t * labi_ld_flag_L_hb_mbedtls(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x4c\x2f\x6f\x70\x74\x2f\x68\x6f\x6d\x65\x62\x72\x65\x77\x2f\x6f\x70\x74\x2f\x6d\x62\x65\x64\x74\x6c\x73\x2f\x6c\x69\x62");
  return p;
}
uint8_t * labi_ld_flag_lssl(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x73\x73\x6c");
  return p;
}
uint8_t * labi_ld_flag_lcrypto(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x63\x72\x79\x70\x74\x6f");
  return p;
}
uint8_t * labi_ld_flag_lmbedtls(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x6d\x62\x65\x64\x74\x6c\x73");
  return p;
}
uint8_t * labi_ld_flag_lmbedx509(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x6d\x62\x65\x64\x78\x35\x30\x39");
  return p;
}
uint8_t * labi_ld_flag_lmbedcrypto(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6c\x6d\x62\x65\x64\x63\x72\x79\x70\x74\x6f");
  return p;
}
uint8_t * labi_net_tls_openssl_marker(void) {
  uint8_t * p = ((uint8_t *)"\x73\x68\x75\x5f\x6e\x65\x74\x5f\x74\x6c\x73\x5f\x6f\x70\x65\x6e\x73\x73\x6c\x5f\x6d\x61\x72\x6b\x65\x72");
  return p;
}
uint8_t * labi_net_tls_mbedtls_marker(void) {
  uint8_t * p = ((uint8_t *)"\x73\x68\x75\x5f\x6e\x65\x74\x5f\x74\x6c\x73\x5f\x6d\x62\x65\x64\x74\x6c\x73\x5f\x6d\x61\x72\x6b\x65\x72");
  return p;
}
uint8_t * labi_rel_tls_openssl_o(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x74\x6c\x73\x5f\x6f\x70\x65\x6e\x73\x73\x6c\x2e\x6f");
  return p;
}
uint8_t * labi_rel_tls_mbedtls_o(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x74\x6c\x73\x5f\x6d\x62\x65\x64\x74\x6c\x73\x2e\x6f");
  return p;
}
void labi_append_openssl_ld_flags(uint8_t * * argv, int32_t * i, int32_t argv_cap) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((i ==0)) {
    return;
  }
  int32_t is_apple = 0;
  (void)((is_apple = link_abi_host_is_apple()));
  if ((is_apple !=0)) {
    int32_t cur = (i)[0];
    if ((cur < (argv_cap - 1))) {
      uint8_t * fl = labi_ld_flag_L_hb_openssl();
      (void)(((argv)[cur] = fl));
      (void)(((i)[0] = (cur + 1)));
    }
  }
  int32_t cur2 = (i)[0];
  if ((cur2 < (argv_cap - 1))) {
    uint8_t * fssl = labi_ld_flag_lssl();
    (void)(((argv)[cur2] = fssl));
    (void)(((i)[0] = (cur2 + 1)));
  }
  int32_t cur3 = (i)[0];
  if ((cur3 < (argv_cap - 1))) {
    uint8_t * fcr = labi_ld_flag_lcrypto();
    (void)(((argv)[cur3] = fcr));
    (void)(((i)[0] = (cur3 + 1)));
  }
}
void labi_append_mbedtls_ld_flags(uint8_t * * argv, int32_t * i, int32_t argv_cap) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((i ==0)) {
    return;
  }
  int32_t is_apple = 0;
  (void)((is_apple = link_abi_host_is_apple()));
  if ((is_apple !=0)) {
    int32_t cur = (i)[0];
    if ((cur < (argv_cap - 1))) {
      uint8_t * fl = labi_ld_flag_L_hb_mbedtls();
      (void)(((argv)[cur] = fl));
      (void)(((i)[0] = (cur + 1)));
    }
  }
  int32_t cur2 = (i)[0];
  if ((cur2 < (argv_cap - 1))) {
    uint8_t * fmb = labi_ld_flag_lmbedtls();
    (void)(((argv)[cur2] = fmb));
    (void)(((i)[0] = (cur2 + 1)));
  }
  int32_t cur3 = (i)[0];
  if ((cur3 < (argv_cap - 1))) {
    uint8_t * fx = labi_ld_flag_lmbedx509();
    (void)(((argv)[cur3] = fx));
    (void)(((i)[0] = (cur3 + 1)));
  }
  int32_t cur4 = (i)[0];
  if ((cur4 < (argv_cap - 1))) {
    uint8_t * fc = labi_ld_flag_lmbedcrypto();
    (void)(((argv)[cur4] = fc));
    (void)(((i)[0] = (cur4 + 1)));
  }
}
uint8_t * labi_ld_driver_clang(void) {
  uint8_t * p = ((uint8_t *)"\x63\x6c\x61\x6e\x67");
  return p;
}
uint8_t * labi_ld_driver_ld(void) {
  uint8_t * p = ((uint8_t *)"\x6c\x64");
  return p;
}
uint8_t * labi_ld_driver_gcc(void) {
  uint8_t * p = ((uint8_t *)"\x67\x63\x63");
  return p;
}
uint8_t * labi_ld_driver_cc(void) {
  uint8_t * p = ((uint8_t *)"\x63\x63");
  return p;
}
uint8_t * labi_ld_mach_entry_main(void) {
  uint8_t * p = ((uint8_t *)"\x5f\x6d\x61\x69\x6e");
  return p;
}
uint8_t * labi_ld_flag_e(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x65");
  return p;
}
uint8_t * labi_ld_flag_o(void) {
  uint8_t * p = ((uint8_t *)"\x2d\x6f");
  return p;
}
int32_t labi_ld_common_tail_flag_count(void) {
  return 7;
}
uint8_t * labi_ld_common_tail_flag_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x6d");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x73\x71\x6c\x69\x74\x65\x33");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x2d\x70\x74\x68\x72\x65\x61\x64");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x70\x74\x68\x72\x65\x61\x64");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x64\x6c");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x63");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x2d\x6c\x53\x79\x73\x74\x65\x6d");
    return p;
  }
  return ((uint8_t *)(0));
}
void ld_append_brew_lib_paths(uint8_t * * argv, int32_t * la, int32_t max_la) {
  int32_t apple = 0;
  (void)((apple = link_abi_host_is_apple()));
  if ((apple ==0)) {
    return;
  }
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  int32_t n = labi_ld_brew_lib_path_count();
  int32_t k = 0;
  while ((k < n)) {
    int32_t cur = (la)[0];
    if ((cur >=(max_la - 1))) {
      break;
    }
    uint8_t * p = labi_ld_brew_lib_path_at(k);
    (void)((k = (k + 1)));
    if ((p ==0)) {
      continue;
    }
    if (((p)[0] ==0)) {
      continue;
    }
    (void)(((argv)[cur] = p));
    (void)(((la)[0] = (cur + 1)));
  }
}
void asm_ld_append_compress_libs(uint8_t * compress_o, uint8_t * user_o, uint8_t * * argv, int32_t * la, int32_t max_la) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  int32_t need_z = 0;
  int32_t need_zs = 0;
  int32_t need_br = 0;
  (void)((need_z = link_abi_obj_needs_zlib(compress_o)));
  if ((need_z ==0)) {
    (void)((need_z = link_abi_obj_needs_zlib(user_o)));
  }
  (void)((need_zs = link_abi_obj_needs_zstd(compress_o)));
  if ((need_zs ==0)) {
    (void)((need_zs = link_abi_obj_needs_zstd(user_o)));
  }
  (void)((need_br = link_abi_obj_needs_brotli(compress_o)));
  if ((need_br ==0)) {
    (void)((need_br = link_abi_obj_needs_brotli(user_o)));
  }
  if ((need_z !=0)) {
    (void)(ld_append_brew_lib_paths(argv, la, max_la));
    int32_t cur = (la)[0];
    if ((cur < (max_la - 1))) {
      uint8_t * fl = labi_ld_flag_lz();
      (void)(((argv)[cur] = fl));
      (void)(((la)[0] = (cur + 1)));
    }
    {
      int32_t _e = xlang_ensure_runtime_compress_zlib_glue_o(0);
    }
    uint8_t * glue = 0;
    (void)((glue = xlang_runtime_compress_zlib_glue_o_path(0)));
    if ((glue !=0)) {
      if (((glue)[0] !=0)) {
        int32_t cur2 = (la)[0];
        if ((cur2 < (max_la - 1))) {
          (void)(((argv)[cur2] = glue));
          (void)(((la)[0] = (cur2 + 1)));
        }
      }
    }
  }
  if ((need_zs !=0)) {
    (void)(ld_append_brew_lib_paths(argv, la, max_la));
    int32_t curz = (la)[0];
    if ((curz < (max_la - 1))) {
      uint8_t * flz = labi_ld_flag_lzstd();
      (void)(((argv)[curz] = flz));
      (void)(((la)[0] = (curz + 1)));
    }
  }
  if ((need_br !=0)) {
    (void)(ld_append_brew_lib_paths(argv, la, max_la));
    int32_t curb = (la)[0];
    if ((curb < (max_la - 1))) {
      uint8_t * fle = labi_ld_flag_lbrotlienc();
      (void)(((argv)[curb] = fle));
      (void)(((la)[0] = (curb + 1)));
    }
    int32_t curb2 = (la)[0];
    if ((curb2 < (max_la - 1))) {
      uint8_t * fld = labi_ld_flag_lbrotlidec();
      (void)(((argv)[curb2] = fld));
      (void)(((la)[0] = (curb2 + 1)));
    }
  }
}
void invoke_cc_append_compress_ld(uint8_t * * argv, int32_t * i, int32_t argv_cap, uint8_t * compress_o, uint8_t * user_o) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((i ==0)) {
    return;
  }
  if (((i)[0] >=(argv_cap - 1))) {
    return;
  }
  int32_t need_z = 0;
  int32_t need_zs = 0;
  int32_t need_br = 0;
  (void)((need_z = link_abi_obj_needs_zlib(compress_o)));
  if ((need_z ==0)) {
    (void)((need_z = link_abi_obj_needs_zlib(user_o)));
  }
  (void)((need_zs = link_abi_obj_needs_zstd(compress_o)));
  if ((need_zs ==0)) {
    (void)((need_zs = link_abi_obj_needs_zstd(user_o)));
  }
  (void)((need_br = link_abi_obj_needs_brotli(compress_o)));
  if ((need_br ==0)) {
    (void)((need_br = link_abi_obj_needs_brotli(user_o)));
  }
  if ((need_z !=0)) {
    (void)(ld_append_brew_lib_paths(argv, i, argv_cap));
    int32_t cur = (i)[0];
    if ((cur < (argv_cap - 1))) {
      uint8_t * fl = labi_ld_flag_lz();
      (void)(((argv)[cur] = fl));
      (void)(((i)[0] = (cur + 1)));
    }
    {
      int32_t _e = xlang_ensure_runtime_compress_zlib_glue_o(0);
    }
    uint8_t * glue = 0;
    (void)((glue = xlang_runtime_compress_zlib_glue_o_path(0)));
    int32_t _p = invoke_cc_argv_push_existing(argv, i, argv_cap, glue);
  }
  if ((need_zs !=0)) {
    (void)(ld_append_brew_lib_paths(argv, i, argv_cap));
    int32_t curz = (i)[0];
    if ((curz < (argv_cap - 1))) {
      uint8_t * flz = labi_ld_flag_lzstd();
      (void)(((argv)[curz] = flz));
      (void)(((i)[0] = (curz + 1)));
    }
  }
  if ((need_br !=0)) {
    (void)(ld_append_brew_lib_paths(argv, i, argv_cap));
    int32_t curb = (i)[0];
    if ((curb < (argv_cap - 1))) {
      uint8_t * fle = labi_ld_flag_lbrotlienc();
      (void)(((argv)[curb] = fle));
      (void)(((i)[0] = (curb + 1)));
    }
    int32_t curb2 = (i)[0];
    if ((curb2 < (argv_cap - 1))) {
      uint8_t * fld = labi_ld_flag_lbrotlidec();
      (void)(((argv)[curb2] = fld));
      (void)(((i)[0] = (curb2 + 1)));
    }
  }
}
void xlang_asm_ld_append_mach_tail_libs_impl(uint8_t * compress_o, uint8_t * user_o, uint8_t * flags, uint8_t * * argv, int32_t * la, int32_t max_la, int32_t append_lsystem) {
  if ((flags ==0)) {
    return;
  }
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  if (((la)[0] < 0)) {
    return;
  }
  int32_t * f = ((int32_t *)(flags));
  int32_t have_thread = (f)[2];
  int32_t have_sync = (f)[3];
  int32_t have_channel = (f)[4];
  int32_t have_math = (f)[5];
  int32_t have_compress = (f)[6];
  int32_t have_sqlite = (f)[8];
  int32_t need_pt = 0;
  if ((have_thread !=0)) {
    (void)((need_pt = 1));
  }
  if ((have_sync !=0)) {
    (void)((need_pt = 1));
  }
  if ((have_channel !=0)) {
    (void)((need_pt = 1));
  }
  if ((have_math !=0)) {
    int32_t cur = (la)[0];
    if ((cur < (max_la - 1))) {
      uint8_t * fl = labi_ld_flag_lm();
      (void)(((argv)[cur] = fl));
      (void)(((la)[0] = (cur + 1)));
    }
  }
  int32_t need_comp = have_compress;
  if ((need_comp ==0)) {
    (void)((need_comp = link_abi_user_o_needs_compress_libs(user_o)));
  }
  if ((need_comp !=0)) {
    (void)(asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la));
  }
  if ((have_sqlite !=0)) {
    int32_t curs = (la)[0];
    if ((curs < (max_la - 1))) {
      uint8_t * fs = labi_ld_flag_lsqlite3();
      (void)(((argv)[curs] = fs));
      (void)(((la)[0] = (curs + 1)));
    }
  }
  if ((need_pt !=0)) {
    int32_t curp = (la)[0];
    if ((curp < (max_la - 1))) {
      uint8_t * fp = labi_ld_flag_pthread();
      (void)(((argv)[curp] = fp));
      (void)(((la)[0] = (curp + 1)));
    }
  }
  if ((append_lsystem !=0)) {
    int32_t curl = (la)[0];
    if ((curl < (max_la - 1))) {
      uint8_t * fsys = labi_ld_flag_lSystem();
      (void)(((argv)[curl] = fsys));
      (void)(((la)[0] = (curl + 1)));
    }
  }
}
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(uint8_t * compress_o, uint8_t * user_o, uint8_t * flags, int32_t need_pt, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((flags ==0)) {
    return;
  }
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  if (((la)[0] < 0)) {
    return;
  }
  int32_t * f = ((int32_t *)(flags));
  int32_t have_io = (f)[0];
  int32_t have_net = (f)[1];
  int32_t have_math = (f)[5];
  int32_t have_compress = (f)[6];
  int32_t have_dynlib = (f)[7];
  int32_t have_sqlite = (f)[8];
  int32_t have_libc_heap = (f)[10];
  int32_t have_fs = (f)[11];
  if ((have_io !=0)) {
    if ((need_pt !=0)) {
      int32_t cur0 = (la)[0];
      if ((cur0 < (max_la - 1))) {
        uint8_t * fp0 = labi_ld_flag_pthread();
        (void)(((argv)[cur0] = fp0));
        (void)(((la)[0] = (cur0 + 1)));
      }
    }
  } else {
    if ((need_pt !=0)) {
      int32_t cur1 = (la)[0];
      if ((cur1 < (max_la - 1))) {
        uint8_t * fp1 = labi_ld_flag_lpthread();
        (void)(((argv)[cur1] = fp1));
        (void)(((la)[0] = (cur1 + 1)));
      }
    }
  }
  if ((have_math !=0)) {
    int32_t curm = (la)[0];
    if ((curm < (max_la - 1))) {
      uint8_t * fm = labi_ld_flag_lm();
      (void)(((argv)[curm] = fm));
      (void)(((la)[0] = (curm + 1)));
    }
  }
  int32_t need_comp = have_compress;
  if ((need_comp ==0)) {
    (void)((need_comp = link_abi_user_o_needs_compress_libs(user_o)));
  }
  if ((need_comp !=0)) {
    (void)(asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la));
  }
  if ((have_sqlite !=0)) {
    int32_t curs = (la)[0];
    if ((curs < (max_la - 1))) {
      uint8_t * fs = labi_ld_flag_lsqlite3();
      (void)(((argv)[curs] = fs));
      (void)(((la)[0] = (curs + 1)));
    }
  }
  if ((have_dynlib !=0)) {
    int32_t is_linux = 0;
    (void)((is_linux = xlang_host_is_linux()));
    if ((is_linux !=0)) {
      int32_t curd = (la)[0];
      if ((curd < (max_la - 1))) {
        uint8_t * fd = labi_ld_flag_ldl();
        (void)(((argv)[curd] = fd));
        (void)(((la)[0] = (curd + 1)));
      }
    }
  }
  int32_t always_lc = 0;
  if ((have_io !=0)) {
    (void)((always_lc = 1));
  }
  if ((have_net !=0)) {
    (void)((always_lc = 1));
  }
  if ((need_pt !=0)) {
    (void)((always_lc = 1));
  }
  if ((always_lc !=0)) {
    int32_t curc = (la)[0];
    if ((curc < (max_la - 1))) {
      uint8_t * fc = labi_ld_flag_lc();
      (void)(((argv)[curc] = fc));
      (void)(((la)[0] = (curc + 1)));
    }
  } else {
    int32_t want_lc = 0;
    if ((have_libc_heap !=0)) {
      (void)((want_lc = 1));
    }
    if ((have_fs !=0)) {
      (void)((want_lc = 1));
    }
    if ((have_math !=0)) {
      (void)((want_lc = 1));
    }
    if ((have_compress !=0)) {
      (void)((want_lc = 1));
    }
    if ((have_sqlite !=0)) {
      (void)((want_lc = 1));
    }
    if ((have_dynlib !=0)) {
      (void)((want_lc = 1));
    }
    if ((want_lc !=0)) {
      int32_t is_linux2 = 0;
      int32_t is_apple = 0;
      (void)((is_linux2 = xlang_host_is_linux()));
      (void)((is_apple = link_abi_host_is_apple()));
      if (((is_linux2 !=0) || (is_apple !=0))) {
        int32_t curc2 = (la)[0];
        if ((curc2 < (max_la - 1))) {
          uint8_t * fc2 = labi_ld_flag_lc();
          (void)(((argv)[curc2] = fc2));
          (void)(((la)[0] = (curc2 + 1)));
        }
      }
    }
  }
}
int32_t invoke_cc_append_net_tls_ld(uint8_t * * argv, int32_t * i, int32_t argv_cap, uint8_t * net_o, uint8_t * repo_root) {
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return 0;
  }
  if ((i ==0)) {
    return 0;
  }
  if (((i)[0] >=(argv_cap - 1))) {
    return 0;
  }
  uint8_t * mk_ssl = labi_net_tls_openssl_marker();
  uint8_t * mk_mb = labi_net_tls_mbedtls_marker();
  if ((net_o !=0)) {
    if (((net_o)[0] !=0)) {
      uint8_t * use = net_o;
      uint8_t abs_n[4096] = {};
      uint8_t * rn = 0;
      (void)((rn = link_abi_realpath_cap(net_o, &((abs_n)[0]))));
      if ((rn !=0)) {
        (void)((use = rn));
      }
      int32_t hit_ssl = 0;
      (void)((hit_ssl = link_abi_obj_exports_marker(use, mk_ssl)));
      if ((hit_ssl !=0)) {
        (void)(labi_append_openssl_ld_flags(argv, i, argv_cap));
        return 1;
      }
      int32_t hit_mb = 0;
      (void)((hit_mb = link_abi_obj_exports_marker(use, mk_mb)));
      if ((hit_mb !=0)) {
        (void)(labi_append_mbedtls_ld_flags(argv, i, argv_cap));
        return 1;
      }
    }
  }
  if ((repo_root ==0)) {
    return 0;
  }
  if (((repo_root)[0] ==0)) {
    return 0;
  }
  uint8_t * rel_ssl = labi_rel_tls_openssl_o();
  uint8_t * tls_ssl = 0;
  (void)((tls_ssl = xlang_rel_o_path_from_argv0(repo_root, rel_ssl)));
  if ((tls_ssl !=0)) {
    if (((tls_ssl)[0] !=0)) {
      uint8_t * use2 = tls_ssl;
      uint8_t abs_s[4096] = {};
      uint8_t * rs = 0;
      (void)((rs = link_abi_realpath_cap(tls_ssl, &((abs_s)[0]))));
      if ((rs !=0)) {
        (void)((use2 = rs));
      }
      int32_t hit2 = 0;
      (void)((hit2 = link_abi_obj_exports_marker(use2, mk_ssl)));
      if ((hit2 !=0)) {
        int32_t _p = invoke_cc_argv_push_existing(argv, i, argv_cap, tls_ssl);
        (void)(labi_append_openssl_ld_flags(argv, i, argv_cap));
        return 1;
      }
    }
  }
  uint8_t * rel_mb = labi_rel_tls_mbedtls_o();
  uint8_t * tls_mb = 0;
  (void)((tls_mb = xlang_rel_o_path_from_argv0(repo_root, rel_mb)));
  if ((tls_mb !=0)) {
    if (((tls_mb)[0] !=0)) {
      uint8_t * use3 = tls_mb;
      uint8_t abs_m[4096] = {};
      uint8_t * rm = 0;
      (void)((rm = link_abi_realpath_cap(tls_mb, &((abs_m)[0]))));
      if ((rm !=0)) {
        (void)((use3 = rm));
      }
      int32_t hit3 = 0;
      (void)((hit3 = link_abi_obj_exports_marker(use3, mk_mb)));
      if ((hit3 !=0)) {
        int32_t _p2 = invoke_cc_argv_push_existing(argv, i, argv_cap, tls_mb);
        (void)(labi_append_mbedtls_ld_flags(argv, i, argv_cap));
        return 1;
      }
    }
  }
  return 0;
}
int32_t labi_net_tls_buf_append(uint8_t * dst, int32_t cap, int32_t pos, uint8_t * src) {
  if ((dst ==0)) {
    return -1;
  }
  if ((pos < 0)) {
    return -1;
  }
  if ((pos >=cap)) {
    return -1;
  }
  int32_t i = 0;
  if ((src ==0)) {
    (void)(((dst)[((size_t)(pos))] = 0));
    return pos;
  }
  while (1) {
    uint8_t c = (src)[((size_t)(i))];
    if ((c ==0)) {
      break;
    }
    if (((pos + 1) >=cap)) {
      (void)(((dst)[((size_t)(pos))] = 0));
      return -1;
    }
    (void)(((dst)[((size_t)(pos))] = c));
    (void)((pos = (pos + 1)));
    (void)((i = (i + 1)));
  }
  (void)(((dst)[((size_t)(pos))] = 0));
  return pos;
}
int32_t labi_net_tls_build_make_cmd(uint8_t * cmd, int32_t cap, uint8_t * repo_root, uint8_t * target) {
  int32_t pos = 0;
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x6d\x61\x6b\x65\x20\x2d\x43\x20\x27"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x27\x2f\x63\x6f\x6d\x70\x69\x6c\x65\x72\x27\x20"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, target)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x20\x3e\x2f\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x20\x32\x3e\x26\x31"))));
  if ((pos < 0)) {
    return 0;
  }
  return 1;
}
int32_t labi_net_tls_join_repo_rel(uint8_t * path_buf, int32_t cap, uint8_t * repo_root, uint8_t * rel) {
  int32_t pos = 0;
  (void)((pos = labi_net_tls_buf_append(path_buf, cap, pos, repo_root)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(path_buf, cap, pos, ((uint8_t *)"\x2f"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(path_buf, cap, pos, rel)));
  if ((pos < 0)) {
    return 0;
  }
  return 1;
}
void ensure_std_net_o_auto_tls(uint8_t * repo_root) {
  if ((repo_root ==0)) {
    return;
  }
  if (((repo_root)[0] ==0)) {
    return;
  }
  uint8_t * mode = 0;
  (void)((mode = link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x4e\x45\x54\x5f\x54\x4c\x53"))));
  if ((mode ==0)) {
    return;
  }
  if (((mode)[0] ==0)) {
    return;
  }
  uint8_t cmd[640] = {};
  uint8_t path_buf[4096] = {};
  uint8_t resolved[4096] = {};
  uint8_t * mk_ssl = labi_net_tls_openssl_marker();
  uint8_t * mk_mb = labi_net_tls_mbedtls_marker();
  int32_t eq_stub = 0;
  (void)((eq_stub = strcmp(mode, ((uint8_t *)"\x73\x74\x75\x62"))));
  if ((eq_stub ==0)) {
    int32_t ok = labi_net_tls_build_make_cmd(&((cmd)[0]), 640, repo_root, ((uint8_t *)"\x6e\x65\x74\x2d\x6f\x2d\x73\x74\x75\x62"));
    if ((ok !=0)) {
      {
        int32_t _s = link_abi_system(&((cmd)[0]));
      }
    }
    return;
  }
  int32_t j1 = labi_net_tls_join_repo_rel(&((path_buf)[0]), 4096, repo_root, ((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x74\x6c\x73\x5f\x6f\x70\x65\x6e\x73\x73\x6c\x2e\x6f"));
  if ((j1 !=0)) {
    uint8_t * rp1 = 0;
    (void)((rp1 = link_abi_realpath_cap(&((path_buf)[0]), &((resolved)[0]))));
    if ((rp1 !=0)) {
      int32_t hit1 = 0;
      (void)((hit1 = link_abi_obj_exports_marker(rp1, mk_ssl)));
      if ((hit1 !=0)) {
        return;
      }
    }
  }
  int32_t j2 = labi_net_tls_join_repo_rel(&((path_buf)[0]), 4096, repo_root, ((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x74\x6c\x73\x5f\x6d\x62\x65\x64\x74\x6c\x73\x2e\x6f"));
  if ((j2 !=0)) {
    uint8_t * rp2 = 0;
    (void)((rp2 = link_abi_realpath_cap(&((path_buf)[0]), &((resolved)[0]))));
    if ((rp2 !=0)) {
      int32_t hit2 = 0;
      (void)((hit2 = link_abi_obj_exports_marker(rp2, mk_mb)));
      if ((hit2 !=0)) {
        return;
      }
    }
  }
  (void)(((resolved)[0] = 0));
  int32_t j3 = labi_net_tls_join_repo_rel(&((path_buf)[0]), 4096, repo_root, ((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x6e\x65\x74\x2e\x6f"));
  if ((j3 !=0)) {
    uint8_t * rp3 = 0;
    (void)((rp3 = link_abi_realpath_cap(&((path_buf)[0]), &((resolved)[0]))));
    if ((rp3 ==0)) {
      (void)((rp3 = link_abi_realpath_cap(((uint8_t *)"\x73\x74\x64\x2f\x6e\x65\x74\x2f\x6e\x65\x74\x2e\x6f"), &((resolved)[0]))));
    }
    if ((rp3 !=0)) {
      int32_t hit_s = 0;
      int32_t hit_m = 0;
      (void)((hit_s = link_abi_obj_exports_marker(rp3, mk_ssl)));
      (void)((hit_m = link_abi_obj_exports_marker(rp3, mk_mb)));
      if ((hit_s !=0)) {
        return;
      }
      if ((hit_m !=0)) {
        return;
      }
    }
  }
  int32_t eq_ssl = 0;
  (void)((eq_ssl = strcmp(mode, ((uint8_t *)"\x6f\x70\x65\x6e\x73\x73\x6c"))));
  if ((eq_ssl ==0)) {
    int32_t ok2 = labi_net_tls_build_make_cmd(&((cmd)[0]), 640, repo_root, ((uint8_t *)"\x6e\x65\x74\x2d\x6f\x2d\x6f\x70\x65\x6e\x73\x73\x6c"));
    if ((ok2 !=0)) {
      {
        int32_t _s2 = link_abi_system(&((cmd)[0]));
      }
    }
    return;
  }
  int32_t eq_mb = 0;
  (void)((eq_mb = strcmp(mode, ((uint8_t *)"\x6d\x62\x65\x64\x74\x6c\x73"))));
  if ((eq_mb ==0)) {
    int32_t ok3 = labi_net_tls_build_make_cmd(&((cmd)[0]), 640, repo_root, ((uint8_t *)"\x6e\x65\x74\x2d\x6f\x2d\x6d\x62\x65\x64\x74\x6c\x73"));
    if ((ok3 !=0)) {
      {
        int32_t _s3 = link_abi_system(&((cmd)[0]));
      }
    }
    return;
  }
  int32_t eq_auto = 0;
  (void)((eq_auto = strcmp(mode, ((uint8_t *)"\x61\x75\x74\x6f"))));
  if ((eq_auto !=0)) {
    return;
  }
  int32_t ok4 = labi_net_tls_build_make_cmd(&((cmd)[0]), 640, repo_root, ((uint8_t *)"\x6e\x65\x74\x2d\x6f\x2d\x6f\x70\x65\x6e\x73\x73\x6c"));
  if ((ok4 !=0)) {
    int32_t rc = 0;
    (void)((rc = link_abi_system(&((cmd)[0]))));
    if ((rc !=0)) {
      int32_t ok5 = labi_net_tls_build_make_cmd(&((cmd)[0]), 640, repo_root, ((uint8_t *)"\x6e\x65\x74\x2d\x6f\x2d\x6d\x62\x65\x64\x74\x6c\x73"));
      if ((ok5 !=0)) {
        {
          int32_t _s5 = link_abi_system(&((cmd)[0]));
        }
      }
    }
  }
}
int32_t labi_formal_std_build_make_cmd(uint8_t * cmd, int32_t cap, uint8_t * xlang_bin, uint8_t * repo_root, uint8_t * make_target) {
  int32_t pos = 0;
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x53\x48\x55\x58\x5f\x46\x4f\x52\x4d\x41\x4c\x5f\x53\x54\x44\x5f\x45\x4e\x53\x55\x52\x45\x3d\x31\x20\x53\x48\x55\x58\x3d\x27"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, xlang_bin)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x27\x20\x6d\x61\x6b\x65\x20\x2d\x43\x20\x27"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x2f\x63\x6f\x6d\x70\x69\x6c\x65\x72\x27\x20\x27"))));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, make_target)));
  if ((pos < 0)) {
    return 0;
  }
  (void)((pos = labi_net_tls_buf_append(cmd, cap, pos, ((uint8_t *)"\x27"))));
  if ((pos < 0)) {
    return 0;
  }
  return 1;
}
int32_t xlang_ensure_formal_std_make_o(uint8_t * repo_root, uint8_t * rel_from_repo, uint8_t * make_target) {
  if ((repo_root ==0)) {
    return 0;
  }
  if (((repo_root)[0] ==0)) {
    return 0;
  }
  if ((rel_from_repo ==0)) {
    return 0;
  }
  if (((rel_from_repo)[0] ==0)) {
    return 0;
  }
  if ((make_target ==0)) {
    return 0;
  }
  if (((make_target)[0] ==0)) {
    return 0;
  }
  uint8_t abs[4096] = {};
  int32_t j0 = labi_net_tls_join_repo_rel(&((abs)[0]), 4096, repo_root, rel_from_repo);
  if ((j0 ==0)) {
    return 0;
  }
  uint8_t * have0 = 0;
  (void)((have0 = asm_link_obj_skip_missing(&((abs)[0]))));
  if ((have0 !=0)) {
    return 1;
  }
  uint8_t * ensuring = 0;
  (void)((ensuring = link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x46\x4f\x52\x4d\x41\x4c\x5f\x53\x54\x44\x5f\x45\x4e\x53\x55\x52\x45"))));
  if ((ensuring !=0)) {
    if (((ensuring)[0] !=0)) {
      if (((ensuring)[0] !=48)) {
        return 0;
      }
    }
  }
  uint8_t xlang_bin[4096] = {};
  (void)(((xlang_bin)[0] = 0));
  uint8_t * env_xlang = 0;
  (void)((env_xlang = link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58"))));
  /* wave221: X_OK via path_executable (1 = ok); wave222: env via link_abi_getenv. */
  int32_t found = 0;
  if ((env_xlang !=0)) {
    if (((env_xlang)[0] !=0)) {
      int32_t ax = 0;
      (void)((ax = link_abi_path_executable(env_xlang)));
      if ((ax !=0)) {
        uint8_t * rp = 0;
        (void)((rp = link_abi_realpath_cap(env_xlang, &((xlang_bin)[0]))));
        if ((rp ==0)) {
          int32_t cp = labi_net_tls_buf_append(&((xlang_bin)[0]), 4096, 0, env_xlang);
          if ((cp < 0)) {
            return 0;
          }
        }
        (void)((found = 1));
      }
    }
  }
  if ((found ==0)) {
    uint8_t cand[4096] = {};
    int32_t i = 0;
    while ((i < 3)) {
      uint8_t * name = 0;
      if ((i ==0)) {
        (void)((name = ((uint8_t *)"\x73\x68\x75\x78\x5f\x61\x73\x6d")));
      }
      if ((i ==1)) {
        (void)((name = ((uint8_t *)"\x73\x68\x75\x78")));
      }
      if ((i ==2)) {
        (void)((name = ((uint8_t *)"\x73\x68\x75\x78\x2d\x63")));
      }
      int32_t pos = 0;
      (void)((pos = labi_net_tls_buf_append(&((cand)[0]), 4096, pos, repo_root)));
      if ((pos < 0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((pos = labi_net_tls_buf_append(&((cand)[0]), 4096, pos, ((uint8_t *)"\x2f\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f"))));
      if ((pos < 0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((pos = labi_net_tls_buf_append(&((cand)[0]), 4096, pos, name)));
      if ((pos < 0)) {
        (void)((i = (i + 1)));
        continue;
      }
      int32_t ax2 = 0;
      (void)((ax2 = link_abi_path_executable(&((cand)[0]))));
      if ((ax2 !=0)) {
        uint8_t * rp2 = 0;
        (void)((rp2 = link_abi_realpath_cap(&((cand)[0]), &((xlang_bin)[0]))));
        if ((rp2 ==0)) {
          int32_t cp2 = labi_net_tls_buf_append(&((xlang_bin)[0]), 4096, 0, &((cand)[0]));
          if ((cp2 < 0)) {
            return 0;
          }
        }
        (void)((found = 1));
        break;
      }
      (void)((i = (i + 1)));
    }
  }
  if ((found ==0)) {
    return 0;
  }
  if (((xlang_bin)[0] ==0)) {
    return 0;
  }
  uint8_t cmd[768] = {};
  int32_t ok = labi_formal_std_build_make_cmd(&((cmd)[0]), 768, &((xlang_bin)[0]), repo_root, make_target);
  if ((ok ==0)) {
    return 0;
  }
  {
    int32_t _s = link_abi_system(&((cmd)[0]));
  }
  uint8_t * have1 = 0;
  (void)((have1 = asm_link_obj_skip_missing(&((abs)[0]))));
  if ((have1 !=0)) {
    return 1;
  }
  return 0;
}
int32_t labi_std_rel_is_std_or_core(uint8_t * rel) {
  if ((rel ==0)) {
    return 0;
  }
  if (((rel)[0] ==0)) {
    return 0;
  }
  if (((rel)[0] ==115)) {
    if (((rel)[1] ==116)) {
      if (((rel)[2] ==100)) {
        if (((rel)[3] ==47)) {
          return 1;
        }
      }
    }
  }
  if (((rel)[0] ==99)) {
    if (((rel)[1] ==111)) {
      if (((rel)[2] ==114)) {
        if (((rel)[3] ==101)) {
          if (((rel)[4] ==47)) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
void labi_std_append_formal_ensure_for_rel(uint8_t * link_argv0, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((link_argv0 ==0)) {
    return;
  }
  if ((rel ==0)) {
    return;
  }
  if (((rel)[0] ==0)) {
    return;
  }
  int32_t is_sc = labi_std_rel_is_std_or_core(rel);
  if ((is_sc ==0)) {
    return;
  }
  uint8_t * include_root = 0;
  (void)((include_root = xlang_repo_root_from_argv0(link_argv0)));
  if ((include_root ==0)) {
    return;
  }
  if (((include_root)[0] ==0)) {
    return;
  }
  uint8_t make_tgt[4096] = {};
  int32_t pos = 0;
  (void)((pos = labi_net_tls_buf_append(&((make_tgt)[0]), 4096, pos, ((uint8_t *)"\x2e\x2e\x2f"))));
  if ((pos < 0)) {
    return;
  }
  (void)((pos = labi_net_tls_buf_append(&((make_tgt)[0]), 4096, pos, rel)));
  if ((pos < 0)) {
    return;
  }
  int32_t _ens = 0;
  (void)((_ens = xlang_ensure_formal_std_make_o(include_root, rel, &((make_tgt)[0]))));
  uint8_t * ab = ((uint8_t *)(argv));
  uint8_t * lb = ((uint8_t *)(lib_roots));
  int32_t need_heap_mem = 0;
  int32_t eq_vec = 0;
  int32_t eq_set = 0;
  int32_t eq_map = 0;
  (void)((eq_vec = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x76\x65\x63\x2f\x76\x65\x63\x2e\x6f"))));
  (void)((eq_set = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x73\x65\x74\x2f\x73\x65\x74\x2e\x6f"))));
  (void)((eq_map = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x6d\x61\x70\x2f\x6d\x61\x70\x2e\x6f"))));
  if ((eq_vec ==0)) {
    (void)((need_heap_mem = 1));
  }
  if ((eq_set ==0)) {
    (void)((need_heap_mem = 1));
  }
  if ((eq_map ==0)) {
    (void)((need_heap_mem = 1));
  }
  if ((need_heap_mem !=0)) {
    int32_t _h = 0;
    int32_t _m = 0;
    (void)((_h = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"\x73\x74\x64\x2f\x68\x65\x61\x70\x2f\x68\x65\x61\x70\x2e\x6f"), ((uint8_t *)"\x2e\x2e\x2f\x73\x74\x64\x2f\x68\x65\x61\x70\x2f\x68\x65\x61\x70\x2e\x6f"))));
    (void)((_m = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"\x63\x6f\x72\x65\x2f\x6d\x65\x6d\x2f\x6d\x65\x6d\x2e\x6f"), ((uint8_t *)"\x2e\x2e\x2f\x63\x6f\x72\x65\x2f\x6d\x65\x6d\x2f\x6d\x65\x6d\x2e\x6f"))));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _ph = 0;
        int32_t _pm = 0;
        (void)((_ph = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"\x73\x74\x64\x2f\x68\x65\x61\x70\x2f\x68\x65\x61\x70\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        (void)((_pm = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"\x63\x6f\x72\x65\x2f\x6d\x65\x6d\x2f\x6d\x65\x6d\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
  }
  int32_t eq_env = 0;
  (void)((eq_env = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x65\x6e\x76\x2f\x65\x6e\x76\x2e\x6f"))));
  if ((eq_env ==0)) {
    int32_t er = 0;
    (void)((er = xlang_ensure_runtime_env_os_o(link_argv0)));
    if ((er ==0)) {
      if ((ab !=0)) {
        if ((la !=0)) {
          uint8_t * env_p = 0;
          (void)((env_p = xlang_runtime_env_os_o_path(link_argv0)));
          int32_t _pe = 0;
          (void)((_pe = link_abi_asm_ld_push_obj(env_p, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x65\x6e\x76\x5f\x6f\x73\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
          /* PLATFORM: SHARED — env.o U process_xlang_*; mirror .x process_argv companion. */
          (void)(labi_std_append_process_argv_if(1, link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la));
        }
      }
    }
  }
  int32_t eq_rnd = 0;
  (void)((eq_rnd = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x72\x61\x6e\x64\x6f\x6d\x2f\x72\x61\x6e\x64\x6f\x6d\x2e\x6f"))));
  if ((eq_rnd ==0)) {
    int32_t rr = 0;
    (void)((rr = xlang_ensure_runtime_random_fill_o(link_argv0)));
    if ((rr ==0)) {
      if ((ab !=0)) {
        if ((la !=0)) {
          uint8_t * rnd_p = 0;
          (void)((rnd_p = xlang_runtime_random_fill_o_path(link_argv0)));
          int32_t _pr = 0;
          (void)((_pr = link_abi_asm_ld_push_obj(rnd_p, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x69\x6c\x6c\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
  }
  int32_t eq_tm = 0;
  (void)((eq_tm = strcmp(rel, ((uint8_t *)"\x73\x74\x64\x2f\x74\x69\x6d\x65\x2f\x74\x69\x6d\x65\x2e\x6f"))));
  if ((eq_tm ==0)) {
    int32_t tr = 0;
    (void)((tr = xlang_ensure_runtime_time_os_o(link_argv0)));
    if ((tr ==0)) {
      if ((ab !=0)) {
        if ((la !=0)) {
          uint8_t * tm_p = 0;
          (void)((tm_p = xlang_runtime_time_os_o_path(link_argv0)));
          int32_t _pt = 0;
          (void)((_pt = link_abi_asm_ld_push_obj(tm_p, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x74\x69\x6d\x65\x5f\x6f\x73\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
  }
  /* PLATFORM: SHARED — formal fs.o U error/context (+ atomic/time_os). G.7 ≡ net companions. */
  int32_t eq_fs = 0;
  int32_t eq_http = 0;
  (void)((eq_fs = strcmp(rel, ((uint8_t *)"std/fs/fs.o"))));
  (void)((eq_http = strcmp(rel, ((uint8_t *)"std/http/http.o"))));
  if ((eq_fs == 0)) {
    int32_t _fe = 0;
    int32_t _fc = 0;
    (void)((_fe = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"std/error/error.o"), ((uint8_t *)"../std/error/error.o"))));
    (void)((_fc = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"std/context/context.o"), ((uint8_t *)"../std/context/context.o"))));
    if ((ab != 0)) {
      if ((la != 0)) {
        int32_t _pe = 0;
        int32_t _pc = 0;
        (void)((_pe = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"std/error/error.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        (void)((_pc = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"std/context/context.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        int32_t er_ag = 0;
        uint8_t * agp = 0;
        (void)((er_ag = xlang_ensure_runtime_atomic_glue_o(link_argv0)));
        (void)((agp = xlang_runtime_atomic_glue_o_path(link_argv0)));
        if ((er_ag == 0)) {
          int32_t _pag = 0;
          (void)((_pag = link_abi_asm_ld_push_obj(agp, link_argv0, ((uint8_t *)"compiler/runtime_atomic_glue.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
        int32_t er_to = 0;
        uint8_t * top = 0;
        (void)((er_to = xlang_ensure_runtime_time_os_o(link_argv0)));
        (void)((top = xlang_runtime_time_os_o_path(link_argv0)));
        if ((er_to == 0)) {
          int32_t _pto = 0;
          (void)((_pto = link_abi_asm_ld_push_obj(top, link_argv0, ((uint8_t *)"compiler/runtime_time_os.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
  }
  if ((eq_http == 0)) {
    int32_t _fe = 0;
    int32_t _fc = 0;
    (void)((_fe = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"std/error/error.o"), ((uint8_t *)"../std/error/error.o"))));
    (void)((_fc = xlang_ensure_formal_std_make_o(include_root, ((uint8_t *)"std/context/context.o"), ((uint8_t *)"../std/context/context.o"))));
    if ((ab != 0)) {
      if ((la != 0)) {
        int32_t _pe = 0;
        int32_t _pc = 0;
        (void)((_pe = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"std/error/error.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        (void)((_pc = link_abi_asm_ld_push_obj(0, link_argv0, ((uint8_t *)"std/context/context.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        int32_t er_ag = 0;
        uint8_t * agp = 0;
        (void)((er_ag = xlang_ensure_runtime_atomic_glue_o(link_argv0)));
        (void)((agp = xlang_runtime_atomic_glue_o_path(link_argv0)));
        if ((er_ag == 0)) {
          int32_t _pag = 0;
          (void)((_pag = link_abi_asm_ld_push_obj(agp, link_argv0, ((uint8_t *)"compiler/runtime_atomic_glue.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
        int32_t er_to = 0;
        uint8_t * top = 0;
        (void)((er_to = xlang_ensure_runtime_time_os_o(link_argv0)));
        (void)((top = xlang_runtime_time_os_o_path(link_argv0)));
        if ((er_to == 0)) {
          int32_t _pto = 0;
          (void)((_pto = link_abi_asm_ld_push_obj(top, link_argv0, ((uint8_t *)"compiler/runtime_time_os.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
  }
  /* PLATFORM: SHARED — direct OP_STD context.o companions (STD-091). G.7 ≡ C need_context. */
  int32_t eq_ctx = 0;
  (void)((eq_ctx = strcmp(rel, ((uint8_t *)"std/context/context.o"))));
  if ((eq_ctx == 0)) {
    if ((ab != 0)) {
      if ((la != 0)) {
        int32_t er_ag_c = 0;
        uint8_t * agp_c = 0;
        (void)((er_ag_c = xlang_ensure_runtime_atomic_glue_o(link_argv0)));
        (void)((agp_c = xlang_runtime_atomic_glue_o_path(link_argv0)));
        if ((er_ag_c == 0)) {
          int32_t _pag_c = 0;
          (void)((_pag_c = link_abi_asm_ld_push_obj(agp_c, link_argv0, ((uint8_t *)"compiler/runtime_atomic_glue.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
        int32_t er_to_c = 0;
        uint8_t * top_c = 0;
        (void)((er_to_c = xlang_ensure_runtime_time_os_o(link_argv0)));
        (void)((top_c = xlang_runtime_time_os_o_path(link_argv0)));
        if ((er_to_c == 0)) {
          int32_t _pto_c = 0;
          (void)((_pto_c = link_abi_asm_ld_push_obj(top_c, link_argv0, ((uint8_t *)"compiler/runtime_time_os.o"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
  }
  if ((lb ==0)) {
    if ((_ens !=0)) {
      return;
    }
  }
}
void labi_std_glue_push_if(int32_t have, int32_t er, uint8_t * primary, uint8_t * link_argv0, uint8_t * glue_rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((have ==0)) {
    return;
  }
  if ((er !=0)) {
    return;
  }
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  int32_t _p = 0;
  (void)((_p = link_abi_asm_ld_push_obj(primary, link_argv0, glue_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
  if ((_p ==0)) {
    return;
  }
}
void labi_std_append_glue_for_op(int32_t op, int32_t have, uint8_t * link_argv0, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((link_argv0 ==0)) {
    return;
  }
  uint8_t * use_rel = rel;
  int32_t rel_ok = 0;
  if ((rel !=0)) {
    if (((rel)[0] !=0)) {
      (void)((rel_ok = 1));
    }
  }
  if ((have ==0)) {
    return;
  }
  if ((op ==10)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x74\x68\x72\x65\x61\x64\x5f\x67\x6c\x75\x65\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_thread_glue_o(link_argv0)));
    (void)((p = xlang_runtime_thread_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==11)) {
    int32_t er1 = 0;
    uint8_t * p1 = 0;
    int32_t er2 = 0;
    uint8_t * p2 = 0;
    (void)((er1 = xlang_ensure_runtime_sync_lock_diag_tls_o(link_argv0)));
    (void)((p1 = xlang_runtime_sync_lock_diag_tls_o_path(link_argv0)));
    (void)((er2 = xlang_ensure_runtime_sync_os_o(link_argv0)));
    (void)((p2 = xlang_runtime_sync_os_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er1, p1, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x73\x79\x6e\x63\x5f\x6c\x6f\x63\x6b\x5f\x64\x69\x61\x67\x5f\x74\x6c\x73\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la));
    (void)(labi_std_glue_push_if(1, er2, p2, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x73\x79\x6e\x63\x5f\x6f\x73\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==12)) {
    int32_t er1 = 0;
    uint8_t * p1 = 0;
    int32_t er2 = 0;
    uint8_t * p2 = 0;
    (void)((er1 = xlang_ensure_runtime_ed25519_ref10_glue_o(link_argv0)));
    (void)((p1 = xlang_runtime_ed25519_ref10_glue_o_path(link_argv0)));
    (void)((er2 = xlang_ensure_runtime_crypto_inc_glue_o(link_argv0)));
    (void)((p2 = xlang_runtime_crypto_inc_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er1, p1, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x65\x64\x32\x35\x35\x31\x39\x5f\x72\x65\x66\x31\x30\x5f\x67\x6c\x75\x65\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la));
    (void)(labi_std_glue_push_if(1, er2, p2, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x63\x72\x79\x70\x74\x6f\x5f\x69\x6e\x63\x5f\x67\x6c\x75\x65\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==13)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x6c\x6f\x67\x5f\x6f\x73\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_log_os_o(link_argv0)));
    (void)((p = xlang_runtime_log_os_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==14)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x61\x74\x6f\x6d\x69\x63\x5f\x67\x6c\x75\x65\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_atomic_glue_o(link_argv0)));
    (void)((p = xlang_runtime_atomic_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==15)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x63\x68\x61\x6e\x6e\x65\x6c\x5f\x67\x6c\x75\x65\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_channel_glue_o(link_argv0)));
    (void)((p = xlang_runtime_channel_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==16)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x62\x61\x63\x6b\x74\x72\x61\x63\x65\x5f\x70\x6c\x61\x74\x66\x6f\x72\x6d\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_backtrace_platform_o(link_argv0)));
    (void)((p = xlang_runtime_backtrace_platform_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==17)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x6d\x61\x74\x68\x5f\x6c\x69\x62\x6d\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_math_libm_o(link_argv0)));
    (void)((p = xlang_runtime_math_libm_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==18)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x73\x71\x6c\x69\x74\x65\x5f\x67\x6c\x75\x65\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_sqlite_glue_o(link_argv0)));
    (void)((p = xlang_runtime_sqlite_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==19)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x64\x79\x6e\x6c\x69\x62\x5f\x6f\x73\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_dynlib_os_o(link_argv0)));
    (void)((p = xlang_runtime_dynlib_os_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
  if ((op ==20)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x68\x74\x74\x70\x5f\x67\x6c\x75\x65\x2e\x6f")));
    }
    int32_t er = 0;
    uint8_t * p = 0;
    (void)((er = xlang_ensure_runtime_http_glue_o(link_argv0)));
    (void)((p = xlang_runtime_http_glue_o_path(link_argv0)));
    (void)(labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
    return;
  }
}
void labi_std_append_primary_for_op(int32_t op, uint8_t * link_argv0, uint8_t * user_o, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((link_argv0 ==0)) {
    return;
  }
  uint8_t * use_rel = rel;
  int32_t rel_ok = 0;
  if ((rel !=0)) {
    if (((rel)[0] !=0)) {
      (void)((rel_ok = 1));
    }
  }
  if ((op ==2)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x61\x73\x6d\x5f\x69\x6f\x5f\x73\x74\x75\x62\x73\x2e\x6f")));
    }
    uint8_t * p = 0;
    (void)((p = xlang_runtime_asm_io_stubs_o_path(link_argv0)));
    uint8_t * ab = ((uint8_t *)(argv));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _p = 0;
        (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
    return;
  }
  if ((op ==3)) {
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x70\x61\x6e\x69\x63\x2e\x6f")));
    }
    uint8_t * p = 0;
    (void)((p = xlang_runtime_panic_o_path(link_argv0)));
    uint8_t * ab = ((uint8_t *)(argv));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _p = 0;
        (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
    /* wave253/259: companion user-domain face for residual declare-only / Linux .s panic.
     * Surface re-pin ≡ .x / cold twin (G.7 dual-authority close). */
    {
      int32_t _e = 0;
      (void)((_e = xlang_ensure_runtime_link_abi_user_env_o(link_argv0)));
    }
    {
      uint8_t * ue_p = 0;
      (void)((ue_p = xlang_runtime_link_abi_user_env_o_path(link_argv0)));
      uint8_t * ab2 = ((uint8_t *)(argv));
      if ((ab2 !=0)) {
        if ((la !=0)) {
          int32_t _ue = 0;
          (void)((_ue = link_abi_asm_ld_push_obj(ue_p, link_argv0,
              ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x6c\x69\x6e\x6b\x5f\x61\x62\x69\x5f\x75\x73\x65\x72\x5f\x65\x6e\x76\x2e\x6f"),
              lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
        }
      }
    }
    return;
  }
  if ((op ==4)) {
    int32_t need = 0;
    (void)((need = labi_user_needs_runtime_time_os(user_o)));
    if ((need ==0)) {
      return;
    }
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x74\x69\x6d\x65\x5f\x6f\x73\x2e\x6f")));
    }
    uint8_t * p = 0;
    int32_t _e = 0;
    (void)((_e = xlang_ensure_runtime_time_os_o(link_argv0)));
    (void)((p = xlang_runtime_time_os_o_path(link_argv0)));
    uint8_t * ab = ((uint8_t *)(argv));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _p = 0;
        (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
    return;
  }
  if ((op ==5)) {
    int32_t need = 0;
    (void)((need = labi_user_needs_runtime_random_fill(user_o)));
    if ((need ==0)) {
      return;
    }
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x69\x6c\x6c\x2e\x6f")));
    }
    uint8_t * p = 0;
    int32_t _e = 0;
    (void)((_e = xlang_ensure_runtime_random_fill_o(link_argv0)));
    (void)((p = xlang_runtime_random_fill_o_path(link_argv0)));
    uint8_t * ab = ((uint8_t *)(argv));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _p = 0;
        (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
    return;
  }
  if ((op ==6)) {
    /* PLATFORM: SHARED — unique local need_env only (mirror .x); do not rename op4/op5. */
    int32_t need_env = 0;
    (void)((need_env = labi_user_needs_runtime_env_os(user_o)));
    if ((need_env ==0)) {
      return;
    }
    if ((rel_ok ==0)) {
      (void)((use_rel = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x65\x6e\x76\x5f\x6f\x73\x2e\x6f")));
    }
    uint8_t * p = 0;
    int32_t _e = 0;
    (void)((_e = xlang_ensure_runtime_env_os_o(link_argv0)));
    (void)((p = xlang_runtime_env_os_o_path(link_argv0)));
    uint8_t * ab = ((uint8_t *)(argv));
    if ((ab !=0)) {
      if ((la !=0)) {
        int32_t _p = 0;
        (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
      }
    }
    return;
  }
}
void labi_std_append_process_argv_if(int32_t need, uint8_t * link_argv0, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((need ==0)) {
    return;
  }
  if ((link_argv0 ==0)) {
    return;
  }
  uint8_t * p = 0;
  int32_t _e = 0;
  (void)((_e = xlang_ensure_runtime_process_argv_o(link_argv0)));
  (void)((p = xlang_runtime_process_argv_o_path(link_argv0)));
  uint8_t * ab = ((uint8_t *)(argv));
  if ((ab ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  int32_t _p = 0;
  (void)((_p = link_abi_asm_ld_push_obj(p, link_argv0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x76\x2e\x6f"), lib_roots, n_lib_roots, bank, argv, la, max_la, 0)));
  if ((_p ==0)) {
    return;
  }
}
void labi_std_append_task_special(uint8_t * link_argv0, uint8_t * user_o, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la) {
  if ((user_o !=0)) {
    if (((user_o)[0] !=0)) {
      int32_t need = 0;
      (void)((need = labi_user_needs_std_task(user_o)));
      if ((need ==0)) {
        return;
      }
    }
  }
  if ((link_argv0 ==0)) {
    return;
  }
  if ((la ==0)) {
    return;
  }
  if (((la)[0] >=(max_la - 1))) {
    return;
  }
  uint8_t * task_rel = rel;
  int32_t rel_ok = 0;
  if ((rel !=0)) {
    if (((rel)[0] !=0)) {
      (void)((rel_ok = 1));
    }
  }
  if ((rel_ok ==0)) {
    (void)((task_rel = ((uint8_t *)"\x73\x74\x64\x2f\x74\x61\x73\x6b\x2f\x74\x61\x73\x6b\x2e\x6f")));
  }
  if ((user_o !=0)) {
    if (((user_o)[0] !=0)) {
      uint8_t * include_root = 0;
      (void)((include_root = xlang_repo_root_from_argv0(link_argv0)));
      if ((include_root !=0)) {
        if (((include_root)[0] !=0)) {
          uint8_t make_tgt[4096] = {};
          int32_t pos = 0;
          (void)((pos = labi_net_tls_buf_append(&((make_tgt)[0]), 4096, pos, ((uint8_t *)"\x2e\x2e\x2f"))));
          if ((pos >=0)) {
            (void)((pos = labi_net_tls_buf_append(&((make_tgt)[0]), 4096, pos, task_rel)));
          }
          if ((pos >=0)) {
            int32_t _ens = 0;
            (void)((_ens = xlang_ensure_formal_std_make_o(include_root, task_rel, &((make_tgt)[0]))));
            if ((_ens ==0)) {
            }
          }
        }
      }
    }
  }
  uint8_t * p = 0;
  uint8_t * relp = 0;
  (void)((relp = xlang_rel_o_path_from_argv0(link_argv0, task_rel)));
  if ((relp !=0)) {
    (void)((p = asm_link_obj_skip_missing(relp)));
  }
  if ((p ==0)) {
    if ((bank !=0)) {
      (void)((p = xlang_asm_ld_try_under_lib_roots(task_rel, lib_roots, n_lib_roots, bank)));
    }
  }
  if ((p ==0)) {
    return;
  }
  (void)(link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p));
  uint8_t * sched = 0;
  (void)((sched = scheduler_o_for_task_link(p, 0)));
  if ((sched ==0)) {
    uint8_t * sp = 0;
    (void)((sp = xlang_std_async_scheduler_o_path(link_argv0)));
    if ((sp !=0)) {
      (void)((sched = asm_link_obj_skip_missing(sp)));
    }
  }
  if ((sched ==0)) {
    if ((bank !=0)) {
      (void)((sched = xlang_asm_ld_try_under_lib_roots(((uint8_t *)"\x73\x74\x64\x2f\x61\x73\x79\x6e\x63\x2f\x73\x63\x68\x65\x64\x75\x6c\x65\x72\x2e\x6f"), lib_roots, n_lib_roots, bank)));
    }
  }
  if ((sched ==0)) {
    return;
  }
  (void)(link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, sched));
  int32_t _eg = 0;
  (void)((_eg = xlang_ensure_runtime_scheduler_glue_o(link_argv0)));
  uint8_t * rsg = 0;
  uint8_t * gp = 0;
  (void)((gp = xlang_runtime_scheduler_glue_o_path(link_argv0)));
  if ((gp !=0)) {
    (void)((rsg = asm_link_obj_skip_missing(gp)));
  }
  if ((rsg ==0)) {
    if ((bank !=0)) {
      (void)((rsg = xlang_asm_ld_try_under_lib_roots(((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x73\x63\x68\x65\x64\x75\x6c\x65\x72\x5f\x67\x6c\x75\x65\x2e\x6f"), lib_roots, n_lib_roots, bank)));
    }
  }
  if ((rsg !=0)) {
    (void)(link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, rsg));
  }
  if ((_eg !=0)) {
    return;
  }
}
int32_t * labi_std_op_std_flag_out(int32_t fk, uint8_t * flags, int32_t * local_have) {
  if ((local_have !=0)) {
    if ((fk ==1)) {
      return &((local_have)[0]);
    }
    if ((fk ==4)) {
      return &((local_have)[1]);
    }
    if ((fk ==5)) {
      return &((local_have)[2]);
    }
    if ((fk ==6)) {
      return &((local_have)[3]);
    }
    if ((fk ==8)) {
      return &((local_have)[4]);
    }
    if ((fk ==13)) {
      return &((local_have)[5]);
    }
  }
  if ((flags !=0)) {
    int32_t * f = ((int32_t *)(flags));
    if ((fk ==2)) {
      return &((f)[2]);
    }
    if ((fk ==3)) {
      return &((f)[3]);
    }
    if ((fk ==7)) {
      return &((f)[4]);
    }
    if ((fk ==9)) {
      return &((f)[5]);
    }
    if ((fk ==10)) {
      return &((f)[8]);
    }
    if ((fk ==11)) {
      return &((f)[9]);
    }
    if ((fk ==12)) {
      return &((f)[7]);
    }
  }
  return ((int32_t *)(0));
}
void labi_std_append_op_std(uint8_t * link_argv0, uint8_t * user_o, uint8_t * rel, int32_t fk, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, uint8_t * flags, int32_t * local_have) {
  int32_t * flag_out = labi_std_op_std_flag_out(fk, flags, local_have);
  int32_t user_ok = 0;
  if ((user_o !=0)) {
    if (((user_o)[0] !=0)) {
      (void)((user_ok = 1));
    }
  }
  int32_t rel_ok = 0;
  if ((rel !=0)) {
    if (((rel)[0] !=0)) {
      (void)((rel_ok = 1));
    }
  }
  if ((rel_ok !=0)) {
    if ((user_ok !=0)) {
      if ((fk ==0)) {
        int32_t need0 = 0;
        (void)((need0 = labi_std_fk0_user_needs_rel(user_o, rel)));
        if ((need0 ==0)) {
          return;
        }
      }
      if ((fk >=1)) {
        if ((fk <=13)) {
          int32_t needk = 0;
          (void)((needk = labi_std_fk_user_needs(user_o, fk)));
          if ((needk ==0)) {
            return;
          }
        }
      }
    } else {
      if ((fk ==0)) {
        int32_t need0b = 0;
        (void)((need0b = labi_std_fk0_user_needs_rel(user_o, rel)));
        if ((need0b ==0)) {
          return;
        }
      }
    }
  } else {
    return;
  }
  if ((user_ok !=0)) {
    (void)(labi_std_append_formal_ensure_for_rel(link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
  }
  int32_t _push = 0;
  (void)((_push = link_abi_asm_ld_push_obj(0, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la, flag_out)));
  if ((_push !=0)) {
    return;
  }
}
int32_t labi_std_glue_have_for_op(int32_t op, uint8_t * flags, int32_t * local_have) {
  if ((local_have !=0)) {
    if ((op ==12)) {
      return (local_have)[1];
    }
    if ((op ==13)) {
      return (local_have)[2];
    }
    if ((op ==14)) {
      return (local_have)[3];
    }
    if ((op ==16)) {
      return (local_have)[4];
    }
    if ((op ==20)) {
      return (local_have)[5];
    }
  }
  if ((flags !=0)) {
    int32_t * f = ((int32_t *)(flags));
    if ((op ==10)) {
      return (f)[2];
    }
    if ((op ==11)) {
      return (f)[3];
    }
    if ((op ==15)) {
      return (f)[4];
    }
    if ((op ==17)) {
      return (f)[5];
    }
    if ((op ==18)) {
      return (f)[8];
    }
    if ((op ==19)) {
      return (f)[7];
    }
  }
  return 0;
}
int32_t labi_std_need_process_argv(uint8_t * flags, int32_t * local_have) {
  if ((local_have ==0)) {
    return 0;
  }
  if (((local_have)[0] !=0)) {
    return 0;
  }
  int32_t heavy = 0;
  if (((local_have)[3] !=0)) {
    (void)((heavy = 1));
  }
  if (((local_have)[2] !=0)) {
    (void)((heavy = 1));
  }
  if (((local_have)[4] !=0)) {
    (void)((heavy = 1));
  }
  if ((flags !=0)) {
    int32_t * f = ((int32_t *)(flags));
    if (((f)[3] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[2] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[7] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[4] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[5] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[9] !=0)) {
      (void)((heavy = 1));
    }
    if (((f)[8] !=0)) {
      (void)((heavy = 1));
    }
  }
  return heavy;
}
void xlang_asm_ld_append_std_objs_for_user(uint8_t * link_argv0, uint8_t * user_o, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, uint8_t * flags) {
  int32_t local_have[6] = {};
  (void)(((local_have)[0] = 0));
  (void)(((local_have)[1] = 0));
  (void)(((local_have)[2] = 0));
  (void)(((local_have)[3] = 0));
  (void)(((local_have)[4] = 0));
  (void)(((local_have)[5] = 0));
  if ((flags !=0)) {
    int32_t * f = ((int32_t *)(flags));
    int32_t zi = 0;
    while ((zi < 12)) {
      (void)(((f)[zi] = 0));
      (void)((zi = (zi + 1)));
    }
    (void)(((f)[0] = 1));
    (void)(((f)[11] = 1));
  }
  int32_t n_steps = 0;
  (void)((n_steps = labi_std_plan_count()));
  int32_t si = 0;
  while ((si < n_steps)) {
    int32_t op = 0;
    size_t rel_u = 0;
    int32_t fk = 0;
    int32_t ok = 0;
    (void)((ok = labi_std_plan_step_at(si, &(op), &(rel_u), &(fk))));
    if ((ok !=0)) {
      uint8_t * rel = ((uint8_t *)(rel_u));
      if ((op ==2)) {
        (void)(labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
      }
      if ((op ==3)) {
        (void)(labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
      }
      if ((op ==4)) {
        (void)(labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
      }
      if ((op ==5)) {
        (void)(labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
      }
      if ((op ==6)) {
        /* PLATFORM: SHARED — park bank across primary op6 (leftover smash; mirror .x). */
        uint8_t * bank_save = bank;
        (void)(labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
        (void)((bank = bank_save));
      }
      if ((op ==1)) {
        (void)(labi_std_append_op_std(link_argv0, user_o, rel, fk, lib_roots, n_lib_roots, bank, argv, la, max_la, flags, &((local_have)[0])));
      }
      if ((op >=10)) {
        if ((op <=20)) {
          int32_t have = labi_std_glue_have_for_op(op, flags, &((local_have)[0]));
          (void)(labi_std_append_glue_for_op(op, have, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
        }
      }
      if ((op ==30)) {
        (void)(labi_std_append_task_special(link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la));
      }
    }
    (void)((si = (si + 1)));
  }
  int32_t need_pav = labi_std_need_process_argv(flags, &((local_have)[0]));
  (void)(labi_std_append_process_argv_if(need_pav, link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la));
}
