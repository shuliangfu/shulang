/* seeds/labi_invoke_cc_list.from_x.c — G-02f-274/L P2 link_abi L5 invoke_cc list pure → R2 full
 * Logic source: src/runtime/labi_invoke_cc_list.x
 * Hybrid: XLANG_LABI_INVOKE_CC_LIST_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full：公共业务符号由 full .x 提供：
 *   labi_linux_harden_flag_{count,at}
 *   labi_invoke_cc_skip_native_env_{count,at} + invoke_cc_skip_native_tuning
 *   labi_icc_rel_* (12) + labi_icc_needs_rel_{count,at}
 *   xlang_append_linux_link_harden_impl (wave155 pure orch over harden table)
 *   invoke_cc_append_early_needs (wave198 pure orch early needs scan+push)
 *   invoke_cc_scan_std_module_needs (wave199 pure table scan std need flags)
 *   invoke_cc_append_std_ensure_push_front (wave200 pure ensure-push front string→env)
 *   invoke_cc_append_std_ensure_push_mid (wave201 pure ensure-push mid sync→hash)
 *   invoke_cc_append_std_ensure_push_heavy_a (wave202 pure ensure-push heavy_a math…compress)
 *   invoke_cc_append_std_ensure_push_heavy_b (wave203 pure ensure-push heavy_b unicode…process_argv)
 *   invoke_cc_append_heap_f06_ondemand (wave204 pure heap F-06 on-demand + page_mmap)
 *   invoke_cc_run_cc_argv + invoke_cc_maybe_strip_out (wave205 pure fork-exec shell + strip)
 *   invoke_cc_append_argv_head_flags (wave206 pure argv head quiet/O/native/NDEBUG/flto/harden/gc/-I)
 *   invoke_cc_append_argv_tail_flags (wave207 pure argv tail -pthread/-lc/allow-multiple/user_extra+NULL)
 *   invoke_cc_append_minimal_cc_link_tail (wave208 pure MINIMAL_CC_LINK Win process_argv + POSIX -lc + NULL)
 * Cap residual：link_abi_getenv（wave223 G.7；非 raw getenv）；host_is_*；needs/ensure/path/push peers；
 *   xlang_spawn_sync / setenv / invoke_cc_strip_out_x / link_diag_tool_status；
 *   asm_link_obj_skip_missing；link_abi_user_extra_o_{count,at}；process_argv path (MINIMAL Windows)。
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef XLANG_LABI_INVOKE_CC_LIST_FROM_X

/* wave223 G.7: env lookup authority = public pure thin link_abi_getenv (labi_diag_pure). */
const char *link_abi_getenv(const char *name);

/* Peer pure / Cap residual for wave198 early needs (provided by other labi_* / mega). */
int link_abi_generated_c_needs_core_builtin(const char *c_path);
int link_abi_generated_c_needs_core_mem(const char *c_path);
int link_abi_generated_c_needs_core_slice(const char *c_path);
int link_abi_generated_c_needs_db_kv(const char *c_path);
int link_abi_generated_c_needs_db_arrow(const char *c_path);
int link_abi_generated_c_needs_fs(const char *c_path);
int link_abi_generated_c_needs_random(const char *c_path);
int link_abi_generated_c_needs_time(const char *c_path);
int link_abi_generated_c_needs_runtime(const char *c_path);
int link_abi_generated_c_needs_win32(const char *c_path);
int link_abi_generated_c_needs_win32_wsa(const char *c_path);
int link_abi_generated_c_needs_libc_heap(const char *c_path);
int invoke_cc_argv_push_existing(char **argv, int *ia, int max_ia, const char *path);
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0);
const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0);
int xlang_ensure_runtime_random_fill_o(const char *argv0);
const char *xlang_runtime_random_fill_o_path(const char *argv0);
int xlang_ensure_runtime_time_os_o(const char *argv0);
const char *xlang_runtime_time_os_o_path(const char *argv0);
int xlang_ensure_runtime_panic_o(const char *argv0);
const char *xlang_runtime_panic_o_path(const char *argv0);
/* wave288 L4: residual face companion (never g05 host bag). */
int xlang_ensure_runtime_link_abi_user_env_o(const char *argv0);
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0);
int xlang_host_is_linux(void);
int link_abi_host_is_apple(void);
int link_abi_host_is_windows(void);
const char *labi_ld_flag_lc(void);
/* wave200 ensure-push front peers */
int xlang_ensure_runtime_process_argv_o(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
int invoke_cc_append_net_tls_ld(char **argv, int *ia, int argv_cap, const char *net_o, const char *repo_root);
int xlang_ensure_runtime_net_udp_batch_o(const char *argv0);
const char *xlang_runtime_net_udp_batch_o_path(const char *argv0);
int xlang_ensure_runtime_net_workers_o(const char *argv0);
const char *xlang_runtime_net_workers_o_path(const char *argv0);
int xlang_ensure_runtime_asm_io_stubs_o(const char *argv0);
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
int xlang_ensure_runtime_thread_glue_o(const char *argv0);
const char *xlang_runtime_thread_glue_o_path(const char *argv0);
int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo, const char *make_target);
int xlang_ensure_runtime_env_os_o(const char *argv0);
const char *xlang_runtime_env_os_o_path(const char *argv0);
const char *labi_ld_flag_lbcrypt(void);
const char *labi_ld_flag_lws2_32(void);
/* wave201 ensure-push mid peers */
int xlang_ensure_runtime_sync_lock_diag_tls_o(const char *argv0);
const char *xlang_runtime_sync_lock_diag_tls_o_path(const char *argv0);
int xlang_ensure_runtime_sync_os_o(const char *argv0);
const char *xlang_runtime_sync_os_o_path(const char *argv0);
int xlang_ensure_runtime_ed25519_ref10_glue_o(const char *argv0);
const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0);
int xlang_ensure_runtime_crypto_inc_glue_o(const char *argv0);
const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0);
int xlang_ensure_runtime_log_os_o(const char *argv0);
const char *xlang_runtime_log_os_o_path(const char *argv0);
int xlang_ensure_runtime_atomic_glue_o(const char *argv0);
const char *xlang_runtime_atomic_glue_o_path(const char *argv0);
int xlang_ensure_runtime_channel_glue_o(const char *argv0);
const char *xlang_runtime_channel_glue_o_path(const char *argv0);
int xlang_ensure_runtime_backtrace_platform_o(const char *argv0);
const char *xlang_runtime_backtrace_platform_o_path(const char *argv0);
/* wave202 ensure-push heavy_a peers */
int xlang_ensure_runtime_math_libm_o(const char *argv0);
const char *xlang_runtime_math_libm_o_path(const char *argv0);
int xlang_ensure_runtime_sqlite_glue_o(const char *argv0);
const char *xlang_runtime_sqlite_glue_o_path(const char *argv0);
int xlang_ensure_runtime_compress_zlib_glue_o(const char *argv0);
const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0);
int link_abi_generated_c_provides_core_mem(const char *c_path);
int link_abi_generated_c_provides_std_heap(const char *c_path);
int link_abi_generated_c_needs_zlib(const char *c_path);
int link_abi_generated_c_needs_zstd(const char *c_path);
int link_abi_generated_c_needs_brotli(const char *c_path);
void invoke_cc_append_compress_ld(char **argv, int *ia, int argv_cap, const char *compress_o, const char *user_o);
void ld_append_brew_lib_paths(const char **argv, int *la, int max_la);
int link_abi_generated_c_contains_substr(const char *c_path, const char *needle);
int link_abi_generated_c_contains_substr_use_line(const char *c_path, const char *needle);
const char *labi_icc_rel_json_o(void);
const char *labi_icc_rel_csv_o(void);
const char *labi_icc_rel_heap_o(void);
const char *labi_icc_rel_core_mem_o(void);
void labi_icc_argv_try_push_flag(char **argv, int *ia, int cap, const char *flag);
/* wave203 ensure-push heavy_b peers */
int xlang_ensure_runtime_dynlib_os_o(const char *argv0);
const char *xlang_runtime_dynlib_os_o_path(const char *argv0);
int xlang_ensure_runtime_http_glue_o(const char *argv0);
const char *xlang_runtime_http_glue_o_path(const char *argv0);
int xlang_ensure_runtime_test_fn_invoke_o(const char *argv0);
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0);
int xlang_ensure_runtime_scheduler_glue_o(const char *argv0);
const char *xlang_runtime_scheduler_glue_o_path(const char *argv0);
const char *xlang_std_async_scheduler_o_path(const char *argv0);
int xlang_generated_c_needs_async_scheduler(const char *c_path);
const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler);
int xlang_link_obj_needs_undef_sym(const char *user_o, const char *sym);
const char *labi_icc_rel_error_o(void);
const char *labi_icc_rel_socketio_o(void);
/* wave204 heap F-06 peers */
int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la);
const char *labi_od_rel_page_mmap(void);
int link_abi_generated_c_provides_core_mem(const char *c_path);
int link_abi_generated_c_provides_std_heap(const char *c_path);
/* wave205 fork-exec shell peers */
int xlang_spawn_sync(const char *prog, const char *const *argv);
void link_diag_tool_status(const char *tool, int status);
void invoke_cc_strip_out_x(const char *out_path);
/* wave207 argv tail peers */
const char *asm_link_obj_skip_missing(const char *path);
int link_abi_user_extra_o_count(void);
const char *link_abi_user_extra_o_at(int i);

int labi_linux_harden_flag_count(void) {
  return 5;
}

const char *labi_linux_harden_flag_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "-pie";
  if (i == 1)
    return "-fpie";
  if (i == 2)
    return "-Wl,-z,noexecstack";
  if (i == 3)
    return "-Wl,-z,relro";
  if (i == 4)
    return "-Wl,--allow-multiple-definition";
  return NULL;
}

int labi_invoke_cc_skip_native_env_count(void) {
  return 3;
}

const char *labi_invoke_cc_skip_native_env_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "CI";
  if (i == 1)
    return "XLANG_CI_DOCKER";
  if (i == 2)
    return "XLANG_NO_MARCH_NATIVE";
  return NULL;
}

int invoke_cc_skip_native_tuning(void) {
  int n = labi_invoke_cc_skip_native_env_count();
  int i;
  for (i = 0; i < n; i++) {
    const char *name = labi_invoke_cc_skip_native_env_at(i);
    /* wave223 G.7: link_abi_getenv (not raw getenv). */
    if (name && name[0] && link_abi_getenv(name) != NULL)
      return 1;
  }
  return 0;
}

const char *labi_icc_rel_core_builtin_o(void) { return "core/builtin/builtin.o"; }
const char *labi_icc_rel_core_builtin_abi_h(void) { return "core/builtin/builtin_abi.h"; }
const char *labi_icc_rel_core_mem_o(void) { return "core/mem/mem.o"; }
const char *labi_icc_rel_core_slice_o(void) { return "core/slice/slice.o"; }
const char *labi_icc_rel_db_kv_o(void) { return "std/db/kv/kv.o"; }
const char *labi_icc_rel_db_arrow_o(void) { return "std/db/arrow/arrow.o"; }
const char *labi_icc_rel_csv_o(void) { return "std/csv/csv.o"; }
const char *labi_icc_rel_error_o(void) { return "std/error/error.o"; }
const char *labi_icc_rel_heap_o(void) { return "std/heap/heap.o"; }
const char *labi_icc_rel_json_o(void) { return "std/json/json.o"; }
const char *labi_icc_rel_log_o(void) { return "std/log/log.o"; }
const char *labi_icc_rel_socketio_o(void) { return "std/socketio/socketio.o"; }

int labi_icc_needs_rel_count(void) {
  return 12;
}

const char *labi_icc_needs_rel_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "core/builtin/builtin.o";
  if (i == 1)
    return "core/builtin/builtin_abi.h";
  if (i == 2)
    return "core/mem/mem.o";
  if (i == 3)
    return "core/slice/slice.o";
  if (i == 4)
    return "std/db/kv/kv.o";
  if (i == 5)
    return "std/db/arrow/arrow.o";
  if (i == 6)
    return "std/csv/csv.o";
  if (i == 7)
    return "std/error/error.o";
  if (i == 8)
    return "std/heap/heap.o";
  if (i == 9)
    return "std/json/json.o";
  if (i == 10)
    return "std/log/log.o";
  if (i == 11)
    return "std/socketio/socketio.o";
  return NULL;
}

/* wave155: xlang_append_linux_link_harden_impl pure orch (cold twin ≡ .x). */
void xlang_append_linux_link_harden_impl(char *argv[], int *la, int cap) {
  int n;
  int k;
  if (!argv || !la || *la < 0)
    return;
  n = labi_linux_harden_flag_count();
  for (k = 0; k < n; k++) {
    const char *f = labi_linux_harden_flag_at(k);
    if (!f || !f[0])
      continue;
    if (*la < cap - 1)
      argv[(*la)++] = (char *)f;
  }
}

/* wave198: labi_icc_argv_try_push_flag + invoke_cc_append_early_needs pure orch (cold twin ≡ .x). */
void labi_icc_argv_try_push_flag(char **argv, int *ia, int cap, const char *flag) {
  if (!argv || !ia || *ia < 0 || !flag || !flag[0])
    return;
  if (*ia < cap - 1)
    argv[(*ia)++] = (char *)flag;
}

/* Stage 12.2.3: full ALLOW path skips freestanding random/time/runtime here
 * (ensure-push front need_flags[8/7/4] is G.7 authority). MINIMAL keeps them
 * because ensure-push is skipped entirely under XLANG_MINIMAL_CC_LINK. */
void invoke_cc_append_early_needs(char **argv, int *ia, int argv_cap,
    const char **c_paths, int n, const char *include_root,
    const char *random_o, const char *time_o, const char *runtime_o, const char *runtime_panic_o) {
  int needs_core_builtin = 0, needs_core_mem = 0, needs_core_slice = 0;
  int needs_db_kv = 0, needs_db_arrow = 0, needs_fs = 0;
  int needs_random = 0, needs_time = 0, needs_runtime = 0;
  int needs_win32 = 0, needs_win32_wsa = 0, needs_libc_heap = 0;
  int minimal_cc = 0;
  int j;
  if (!argv || !ia || *ia < 0)
    return;
  {
    const char *menv = link_abi_getenv("XLANG_MINIMAL_CC_LINK");
    if (menv && menv[0])
      minimal_cc = 1;
  }
  if (c_paths && n > 0) {
    for (j = 0; j < n; j++) {
      const char *cp = c_paths[j];
      if (!cp)
        continue;
      if (link_abi_generated_c_needs_core_builtin(cp))
        needs_core_builtin = 1;
      if (link_abi_generated_c_needs_core_mem(cp))
        needs_core_mem = 1;
      if (link_abi_generated_c_needs_core_slice(cp))
        needs_core_slice = 1;
      if (link_abi_generated_c_needs_db_kv(cp))
        needs_db_kv = 1;
      if (link_abi_generated_c_needs_db_arrow(cp))
        needs_db_arrow = 1;
      if (link_abi_generated_c_needs_fs(cp))
        needs_fs = 1;
      /* MINIMAL-only freestanding rtr; full path → ensure-push front. */
      if (minimal_cc) {
        if (link_abi_generated_c_needs_random(cp))
          needs_random = 1;
        if (link_abi_generated_c_needs_time(cp))
          needs_time = 1;
        if (link_abi_generated_c_needs_runtime(cp))
          needs_runtime = 1;
      }
      if (link_abi_generated_c_needs_win32(cp))
        needs_win32 = 1;
      if (link_abi_generated_c_needs_win32_wsa(cp))
        needs_win32_wsa = 1;
      if (link_abi_generated_c_needs_libc_heap(cp))
        needs_libc_heap = 1;
    }
  }
  if (needs_core_builtin) {
    const char *abi_h = xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_builtin_abi_h());
    if (abi_h && abi_h[0] && *ia < argv_cap - 2) {
      argv[(*ia)++] = (char *)"-include";
      argv[(*ia)++] = (char *)abi_h;
    }
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_builtin_o()));
  }
  if (needs_core_mem)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o()));
  if (needs_core_slice)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_slice_o()));
  if (needs_db_kv) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_db_kv_o()));
    {
      const char *rkv = xlang_runtime_kv_mmap_glue_o_path(NULL);
      if (rkv && rkv[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rkv);
    }
  }
  if (needs_db_arrow) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_db_arrow_o()));
    {
      const char *rar = xlang_runtime_arrow_simd_glue_o_path(NULL);
      if (rar && rar[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rar);
    }
  }
  if (needs_fs) {
    if (xlang_host_is_linux() || link_abi_host_is_apple())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lc());
  }
  if (needs_random) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, random_o);
    (void)xlang_ensure_runtime_random_fill_o(NULL);
    {
      const char *rrf = xlang_runtime_random_fill_o_path(NULL);
      if (rrf && rrf[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rrf);
    }
    if (link_abi_host_is_windows())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lbcrypt());
  }
  if (needs_time) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, time_o);
    (void)xlang_ensure_runtime_time_os_o(NULL);
    {
      const char *rto = xlang_runtime_time_os_o_path(NULL);
      if (rto && rto[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rto);
    }
  }
  if (needs_runtime) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, runtime_o);
    (void)xlang_ensure_runtime_panic_o(NULL);
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, runtime_panic_o);
    {
      const char *rp = xlang_runtime_panic_o_path(NULL);
      if (rp && rp[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rp);
    }
  }
  if (needs_win32 && link_abi_host_is_windows())
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lkernel32");
  if (needs_win32_wsa && link_abi_host_is_windows())
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lws2_32());
  if (needs_libc_heap) {
    if (xlang_host_is_linux() || link_abi_host_is_apple())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lc());
  }
}

/* wave199: labi_icc_std_need_* tables + invoke_cc_scan_std_module_needs pure orch (cold twin ≡ .x). */
int labi_icc_std_need_count(void) { return 52; }

int labi_icc_std_need_needle_count(int mid) {

  if (mid == 0) return 5;
  if (mid == 1) return 8;
  if (mid == 2) return 2;
  if (mid == 3) return 3;
  if (mid == 4) return 1;
  if (mid == 5) return 18;
  if (mid == 6) return 3;
  if (mid == 7) return 3;
  if (mid == 8) return 2;
  if (mid == 9) return 3;
  if (mid == 10) return 3;
  if (mid == 11) return 1;
  if (mid == 12) return 3;
  if (mid == 13) return 5;
  if (mid == 14) return 3;
  if (mid == 15) return 4;
  if (mid == 16) return 3;
  if (mid == 17) return 2;
  if (mid == 18) return 3;
  if (mid == 19) return 3;
  if (mid == 20) return 3;
  if (mid == 21) return 10;
  if (mid == 22) return 2;
  if (mid == 23) return 3;
  if (mid == 24) return 2;
  if (mid == 25) return 2;
  if (mid == 26) return 2;
  if (mid == 27) return 2;
  if (mid == 28) return 4;
  if (mid == 29) return 2;
  if (mid == 30) return 2;
  if (mid == 31) return 3;
  if (mid == 32) return 3;
  if (mid == 33) return 1;
  if (mid == 34) return 8;
  if (mid == 35) return 2;
  if (mid == 36) return 1;
  if (mid == 37) return 3;
  if (mid == 38) return 3;
  if (mid == 39) return 2;
  if (mid == 40) return 1;
  if (mid == 41) return 1;
  if (mid == 42) return 1;
  if (mid == 43) return 1;
  if (mid == 44) return 1;
  if (mid == 45) return 1;
  if (mid == 46) return 2;
  if (mid == 47) return 3;
  if (mid == 48) return 1;
  if (mid == 49) return 1;
  if (mid == 50) return 1;
  if (mid == 51) return 1;
  return 0;
}

const char *labi_icc_std_need_needle_at(int mid, int i) {
  if (i < 0) return NULL;

  if (mid == 0) {
    if (i == 0) return "std_process_";
    if (i == 1) return "xlang_process_spawn";
    if (i == 2) return "xlang_process_wait";
    if (i == 3) return "process_spawn";
    if (i == 4) return "process_exec";
    return NULL;
  }
  if (mid == 1) {
    if (i == 0) return "process_xlang_argc_get";
    if (i == 1) return "process_xlang_argv_get";
    if (i == 2) return "process_args_count_c";
    if (i == 3) return "process_arg_c";
    if (i == 4) return "args_iter_count_c";
    if (i == 5) return "args_iter_at_c";
    if (i == 6) return "std_process_args";
    if (i == 7) return "std_env_args_iter";
    return NULL;
  }
  if (mid == 2) {
    if (i == 0) return "std_string_";
    if (i == 1) return "xlang_string_";
    return NULL;
  }
  if (mid == 3) {
    if (i == 0) return "std_path_";
    if (i == 1) return "path_join";
    if (i == 2) return "path_dirname";
    return NULL;
  }
  if (mid == 4) {
    if (i == 0) return "std_runtime_";
    return NULL;
  }
  if (mid == 5) {
    if (i == 0) return "std_net_listen";
    if (i == 1) return "std_net_connect";
    if (i == 2) return "std_net_udp_bind";
    if (i == 3) return "std_net_udp_recv";
    if (i == 4) return "std_net_udp_send";
    if (i == 5) return "std_net_addr_to_u32";
    if (i == 6) return "std_net_close_udp";
    if (i == 7) return "net_tcp_connect_c";
    if (i == 8) return "net_tcp_listen_c";
    if (i == 9) return "net_udp_bind_c";
    if (i == 10) return "net_udp_recv_many_buf_c";
    if (i == 11) return "net_udp_send_many_buf_c";
    if (i == 12) return "net_udp_send_c";
    if (i == 13) return "net_dns_resolve_c";
    if (i == 14) return "net_sock_create_c";
    if (i == 15) return "net_stream_write_batch_c";
    if (i == 16) return "net_close_socket_c_real";
    if (i == 17) return "net_run_accept_workers_c_real";
    return NULL;
  }
  if (mid == 6) {
    if (i == 0) return "std_thread_";
    if (i == 1) return "thread_create_c";
    if (i == 2) return "thread_join_c";
    return NULL;
  }
  if (mid == 7) {
    if (i == 0) return "std_time_";
    if (i == 1) return "time_now_";
    if (i == 2) return "time_sleep_";
    return NULL;
  }
  if (mid == 8) {
    if (i == 0) return "std_random_";
    if (i == 1) return "random_fill_";
    return NULL;
  }
  if (mid == 9) {
    if (i == 0) return "std_env_";
    if (i == 1) return "env_get_";
    if (i == 2) return "env_set_";
    return NULL;
  }
  if (mid == 10) {
    if (i == 0) return "std_sync_";
    if (i == 1) return "sync_mutex_";
    if (i == 2) return "sync_rwlock_";
    return NULL;
  }
  if (mid == 11) {
    if (i == 0) return "std_encoding_";
    return NULL;
  }
  if (mid == 12) {
    if (i == 0) return "std_base64_";
    if (i == 1) return "base64_encode";
    if (i == 2) return "base64_decode";
    return NULL;
  }
  if (mid == 13) {
    if (i == 0) return "std_crypto_";
    if (i == 1) return "core_crypto_mem_eq";
    if (i == 2) return "core_crypto_sha";
    if (i == 3) return "crypto_sha";
    if (i == 4) return "ed25519_";
    return NULL;
  }
  if (mid == 14) {
    if (i == 0) return "std_log_";
    if (i == 1) return "log_write_c";
    if (i == 2) return "log_info_";
    return NULL;
  }
  if (mid == 15) {
    if (i == 0) return "std_atomic_";
    if (i == 1) return "atomic_load_i32_c";
    if (i == 2) return "atomic_store_i32_c";
    if (i == 3) return "atomic_fetch_";
    return NULL;
  }
  if (mid == 16) {
    if (i == 0) return "std_channel_";
    if (i == 1) return "channel_send";
    if (i == 2) return "channel_recv";
    return NULL;
  }
  if (mid == 17) {
    if (i == 0) return "std_backtrace_";
    if (i == 1) return "backtrace_capture";
    return NULL;
  }
  if (mid == 18) {
    if (i == 0) return "std_hash_";
    if (i == 1) return "hash_fnv";
    if (i == 2) return "hash_sip";
    return NULL;
  }
  if (mid == 19) {
    if (i == 0) return "std_math_";
    if (i == 1) return "math_sin";
    if (i == 2) return "math_cos";
    return NULL;
  }
  if (mid == 20) {
    if (i == 0) return "std_sort_";
    if (i == 1) return "sort_i32";
    if (i == 2) return "sort_stable";
    return NULL;
  }
  if (mid == 21) {
    if (i == 0) return "std_vec_new";
    if (i == 1) return "std_vec_push";
    if (i == 2) return "std_vec_length_Vec";
    if (i == 3) return "std_vec_len_ptr";
    if (i == 4) return "std_vec_with_capacity";
    if (i == 5) return "std_vec_from_slice";
    if (i == 6) return "std_vec_append";
    if (i == 7) return "std_vec_reserve";
    if (i == 8) return "std_vec_clear";
    if (i == 9) return "std_vec_free";
    return NULL;
  }
  if (mid == 22) {
    if (i == 0) return "std_ffi_";
    if (i == 1) return "ffi_call";
    return NULL;
  }
  if (mid == 23) {
    if (i == 0) return "std_db_";
    if (i == 1) return "sqlite3_";
    if (i == 2) return "db_sqlite_";
    return NULL;
  }
  if (mid == 24) {
    if (i == 0) return "std_elf_";
    if (i == 1) return "elf_parse";
    return NULL;
  }
  if (mid == 25) {
    if (i == 0) return "std_json_";
    if (i == 1) return "json_parse_";
    return NULL;
  }
  if (mid == 26) {
    if (i == 0) return "std_csv_";
    if (i == 1) return "csv_next_field";
    return NULL;
  }
  if (mid == 27) {
    if (i == 0) return "std_regex_";
    if (i == 1) return "regex_match";
    return NULL;
  }
  if (mid == 28) {
    if (i == 0) return "std_compress_";
    if (i == 1) return "compress_gzip";
    if (i == 2) return "compress_zstd";
    if (i == 3) return "compress_brotli";
    return NULL;
  }
  if (mid == 29) {
    if (i == 0) return "std_unicode_";
    if (i == 1) return "unicode_utf8";
    return NULL;
  }
  if (mid == 30) {
    if (i == 0) return "std_dynlib_";
    if (i == 1) return "dynlib_open";
    return NULL;
  }
  if (mid == 31) {
    if (i == 0) return "std_http_";
    if (i == 1) return "http_request";
    if (i == 2) return "http2_";
    return NULL;
  }
  if (mid == 32) {
    if (i == 0) return "std_tar_";
    if (i == 1) return "tar_open";
    if (i == 2) return "tar_extract";
    return NULL;
  }
  if (mid == 33) {
    if (i == 0) return "std_simd_";
    return NULL;
  }
  if (mid == 34) {
    if (i == 0) return "std_context_background(";
    if (i == 1) return "std_context_with_cancel(";
    if (i == 2) return "std_context_with_deadline(";
    if (i == 3) return "std_context_with_timeout(";
    if (i == 4) return "std_context_cancel(";
    if (i == 5) return "std_context_set_value(";
    if (i == 6) return "std_context_get_value(";
    if (i == 7) return "std_context_free(";
    return NULL;
  }
  if (mid == 35) {
    if (i == 0) return "std_error_";
    if (i == 1) return "error_wrap_";
    return NULL;
  }
  if (mid == 36) {
    if (i == 0) return "std_datetime_";
    return NULL;
  }
  if (mid == 37) {
    if (i == 0) return "std_uuid_";
    if (i == 1) return "uuid_v4";
    if (i == 2) return "uuid_parse";
    return NULL;
  }
  if (mid == 38) {
    if (i == 0) return "std_url_";
    if (i == 1) return "url_parse";
    if (i == 2) return "url_join";
    return NULL;
  }
  if (mid == 39) {
    if (i == 0) return "std_cli_";
    if (i == 1) return "cli_parse";
    return NULL;
  }
  if (mid == 40) {
    if (i == 0) return "std_security_";
    return NULL;
  }
  if (mid == 41) {
    if (i == 0) return "std_config_";
    return NULL;
  }
  if (mid == 42) {
    if (i == 0) return "std_cache_";
    return NULL;
  }
  if (mid == 43) {
    if (i == 0) return "std_trace_";
    return NULL;
  }
  if (mid == 44) {
    if (i == 0) return "std_task_";
    return NULL;
  }
  if (mid == 45) {
    if (i == 0) return "std_schema_";
    return NULL;
  }
  if (mid == 46) {
    if (i == 0) return "std_test_";
    if (i == 1) return "test_call_";
    return NULL;
  }
  if (mid == 47) {
    if (i == 0) return "std_socketio_";
    if (i == 1) return "socketio_emit";
    if (i == 2) return "socketio_on";
    return NULL;
  }
  if (mid == 48) {
    if (i == 0) return "std_set_";
    return NULL;
  }
  if (mid == 49) {
    if (i == 0) return "std_map_";
    return NULL;
  }
  if (mid == 50) {
    if (i == 0) return "std_queue_";
    return NULL;
  }
  if (mid == 51) {
    if (i == 0) return "xlang_panic_(";
    return NULL;
  }
  return NULL;
}


void invoke_cc_scan_std_module_needs(const char **c_paths, int n, int *flags, int flags_cap) {
  int k, j, mid, ni, nc;
  const char *cp;
  const char *nd;
  if (!flags || flags_cap < 52)
    return;
  for (k = 0; k < 52; k++)
    flags[k] = 0;
  if (!c_paths || n < 1)
    return;
  for (j = 0; j < n; j++) {
    cp = c_paths[j];
    if (!cp)
      continue;
    for (mid = 0; mid < 52; mid++) {
      if (mid == 51) {
        if (link_abi_generated_c_contains_substr_use_line(cp, "xlang_panic_(")
            && !link_abi_generated_c_contains_substr(cp, "void xlang_panic_(int has_msg, int msg_val) {")
            && !link_abi_generated_c_contains_substr(cp, "void xlang_panic_(int has_msg, int msg_val){"))
          flags[51] = 1;
        continue;
      }
      nc = labi_icc_std_need_needle_count(mid);
      for (ni = 0; ni < nc; ni++) {
        nd = labi_icc_std_need_needle_at(mid, ni);
        if (!nd)
          continue;
        if (link_abi_generated_c_contains_substr_use_line(cp, nd)) {
          flags[mid] = 1;
          break;
        }
      }
    }
  }
}

/* wave200: invoke_cc_append_std_ensure_push_front pure orch (cold twin ≡ .x).
 * Ensure-push front string→env; mutates need_flags[6] when net links thread. */
void invoke_cc_append_std_ensure_push_front(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char *process_o, const char *string_o, const char *heap_o, const char *path_o,
    const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o,
    const char *time_o, const char *random_o, const char *env_o) {
  int need_process, need_process_argv_glue, need_string, need_path, need_runtime;
  int need_net, need_thread, need_time, need_random, need_env, need_panic;
  int pushed_process_o = 0;
  if (!argv || !ia || *ia < 0 || !need_flags || flags_cap < 52)
    return;
  need_process = need_flags[0];
  need_process_argv_glue = need_flags[1];
  need_string = need_flags[2];
  need_path = need_flags[3];
  need_runtime = need_flags[4];
  need_net = need_flags[5];
  need_thread = need_flags[6];
  need_time = need_flags[7];
  need_random = need_flags[8];
  need_env = need_flags[9];
  need_panic = need_flags[51];

  if (need_string)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, string_o);

  if (need_process && invoke_cc_argv_push_existing(argv, ia, argv_cap, process_o)) {
    pushed_process_o = 1;
    if (xlang_host_is_linux())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-pthread");
  }
  if (!pushed_process_o && (need_process || need_env || need_process_argv_glue)) {
    (void)xlang_ensure_runtime_process_argv_o(NULL);
    {
      const char *rpa = xlang_runtime_process_argv_o_path(NULL);
      if (rpa && rpa[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rpa);
    }
  }

  /* Stage 12.2.3 ALLOW ensure slim: heap.o need-gated by invoke_cc_append_heap_f06_ondemand
   * (nm argv + use_line + provides). Do not always-push when path non-empty (rv/hello waste).
   * heap_o remains in signature for G.7 mega call-site ABI. PLATFORM: SHARED. */
  (void)heap_o;
  if (need_path)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, path_o);
  if (need_runtime)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, runtime_o);
  if (need_panic || need_runtime) {
    (void)xlang_ensure_runtime_panic_o(NULL);
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, runtime_panic_o);
    {
      const char *rp = xlang_runtime_panic_o_path(NULL);
      if (rp && rp[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rp);
    }
  }
  /* wave288 L4 G.7: residual face companion — process/env/panic U link_abi_getenv.
   * PLATFORM: SHARED — ≡ PRIMARY_PANIC user_env on asm ld; invoke_cc was lagging. */
  if (need_process || need_env || need_panic || need_runtime) {
    (void)xlang_ensure_runtime_link_abi_user_env_o(NULL);
    {
      const char *rue = xlang_runtime_link_abi_user_env_o_path(NULL);
      if (rue && rue[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rue);
    }
  }

  if (need_net && invoke_cc_argv_push_existing(argv, ia, argv_cap, net_o)) {
    (void)invoke_cc_append_net_tls_ld(argv, ia, argv_cap, net_o, include_root);
    (void)xlang_ensure_runtime_net_udp_batch_o(NULL);
    {
      const char *rnub = xlang_runtime_net_udp_batch_o_path(NULL);
      if (rnub && rnub[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rnub);
    }
    (void)xlang_ensure_runtime_net_workers_o(NULL);
    {
      const char *rnw = xlang_runtime_net_workers_o_path(NULL);
      if (rnw && rnw[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rnw);
    }
    need_thread = 1;
    need_flags[6] = 1;
    if (xlang_host_is_linux()) {
      (void)xlang_ensure_runtime_asm_io_stubs_o(NULL);
      {
        const char *ris = xlang_runtime_asm_io_stubs_o_path(NULL);
        if (ris && ris[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, ris);
      }
    }
    if (link_abi_host_is_windows())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lws2_32());
  }

  /* thread.o + thread_glue: always push glue when need_thread (co-emit may skip thread.o UNDEFs). */
  if (need_thread) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, thread_o);
    (void)xlang_ensure_runtime_thread_glue_o(NULL);
    {
      const char *rtg = xlang_runtime_thread_glue_o_path(NULL);
      if (rtg && rtg[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rtg);
    }
  }

  if (need_time) {
    if (include_root && include_root[0])
      (void)xlang_ensure_formal_std_make_o(include_root, "std/time/time.o", "../std/time/time.o");
    {
      const char *time_push = xlang_rel_o_path_from_argv0(include_root, "std/time/time.o");
      if ((!time_push || !time_push[0]) && time_o && time_o[0])
        time_push = time_o;
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, time_push);
    }
    (void)xlang_ensure_runtime_time_os_o(NULL);
    {
      const char *rto = xlang_runtime_time_os_o_path(NULL);
      if (rto && rto[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rto);
    }
  }

  if (need_random) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, random_o);
    (void)xlang_ensure_runtime_random_fill_o(NULL);
    {
      const char *rrf = xlang_runtime_random_fill_o_path(NULL);
      if (rrf && rrf[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rrf);
    }
    if (link_abi_host_is_windows())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lbcrypt());
  }

  if (need_env) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, env_o);
    (void)xlang_ensure_runtime_env_os_o(NULL);
    {
      const char *reo = xlang_runtime_env_os_o_path(NULL);
      if (reo && reo[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, reo);
    }
  }
}

/* wave201: invoke_cc_append_std_ensure_push_mid pure orch (cold twin ≡ .x).
 * Ensure-push mid sync→hash; host_is_* for backtrace ld flags. */
void invoke_cc_append_std_ensure_push_mid(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o,
    const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o) {
  int need_sync, need_encoding, need_base64, need_crypto, need_log;
  int need_atomic, need_channel, need_backtrace, need_hash;
  if (!argv || !ia || *ia < 0 || !need_flags || flags_cap < 52)
    return;
  need_sync = need_flags[10];
  need_encoding = need_flags[11];
  need_base64 = need_flags[12];
  need_crypto = need_flags[13];
  need_log = need_flags[14];
  need_atomic = need_flags[15];
  need_channel = need_flags[16];
  need_backtrace = need_flags[17];
  need_hash = need_flags[18];

  if (need_sync && invoke_cc_argv_push_existing(argv, ia, argv_cap, sync_o)) {
    (void)xlang_ensure_runtime_sync_lock_diag_tls_o(NULL);
    {
      const char *rsld = xlang_runtime_sync_lock_diag_tls_o_path(NULL);
      if (rsld && rsld[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rsld);
    }
    (void)xlang_ensure_runtime_sync_os_o(NULL);
    {
      const char *rso = xlang_runtime_sync_os_o_path(NULL);
      if (rso && rso[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rso);
    }
  }
  if (need_encoding)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, encoding_o);
  if (need_base64)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, base64_o);
  if (need_crypto) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, crypto_o);
    (void)xlang_ensure_runtime_ed25519_ref10_glue_o(NULL);
    {
      const char *red = xlang_runtime_ed25519_ref10_glue_o_path(NULL);
      if (red && red[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, red);
    }
    (void)xlang_ensure_runtime_crypto_inc_glue_o(NULL);
    {
      const char *rci = xlang_runtime_crypto_inc_glue_o_path(NULL);
      if (rci && rci[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rci);
    }
  }
  if (need_log && invoke_cc_argv_push_existing(argv, ia, argv_cap,
      xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_log_o()))) {
    (void)xlang_ensure_runtime_log_os_o(NULL);
    {
      const char *rlo = xlang_runtime_log_os_o_path(NULL);
      if (rlo && rlo[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rlo);
    }
    /* wave288 L4: log_os residual U link_abi_getenv → user_env face. */
    (void)xlang_ensure_runtime_link_abi_user_env_o(NULL);
    {
      const char *rue = xlang_runtime_link_abi_user_env_o_path(NULL);
      if (rue && rue[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rue);
    }
  }
  if (need_atomic && invoke_cc_argv_push_existing(argv, ia, argv_cap, atomic_o)) {
    (void)xlang_ensure_runtime_atomic_glue_o(NULL);
    {
      const char *rag = xlang_runtime_atomic_glue_o_path(NULL);
      if (rag && rag[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rag);
    }
  }
  if (need_channel) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, channel_o);
    (void)xlang_ensure_runtime_channel_glue_o(NULL);
    {
      const char *rcg = xlang_runtime_channel_glue_o_path(NULL);
      if (rcg && rcg[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rcg);
    }
  }
  if (need_backtrace) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, backtrace_o);
    (void)xlang_ensure_runtime_backtrace_platform_o(NULL);
    {
      const char *rbp = xlang_runtime_backtrace_platform_o_path(NULL);
      if (rbp && rbp[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rbp);
    }
    /* wave288 L4: backtrace residual U link_abi_getenv → user_env face. */
    (void)xlang_ensure_runtime_link_abi_user_env_o(NULL);
    {
      const char *rue = xlang_runtime_link_abi_user_env_o_path(NULL);
      if (rue && rue[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rue);
    }
    if (xlang_host_is_linux()) {
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-rdynamic");
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-ldl");
    } else if (link_abi_host_is_apple()) {
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-Wl,-export_dynamic");
    }
    /* Cap residual 9.1.11 Win: no -ldbghelp (PE export Cap). */
  }
  if (need_hash)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, hash_o);
}

/* wave202: invoke_cc_append_std_ensure_push_heavy_a pure orch (cold twin ≡ .x).
 * Ensure-push heavy_a math…compress; co-emit scans + formal ensure + compress_ld. */
void invoke_cc_append_std_ensure_push_heavy_a(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char **c_paths, int n,
    const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o,
    const char *elf_o, const char *regex_o, const char *compress_o, const char *hash_o) {
  int need_math, need_sort, need_vec, need_ffi, need_db, need_elf;
  int need_json, need_csv, need_regex, need_compress;
  int need_set, need_map, need_queue;
  int jscan;
  if (!argv || !ia || *ia < 0 || !need_flags || flags_cap < 52)
    return;
  need_math = need_flags[19];
  need_sort = need_flags[20];
  need_vec = need_flags[21];
  need_ffi = need_flags[22];
  need_db = need_flags[23];
  need_elf = need_flags[24];
  need_json = need_flags[25];
  need_csv = need_flags[26];
  need_regex = need_flags[27];
  need_compress = need_flags[28];
  need_set = need_flags[48];
  need_map = need_flags[49];
  need_queue = need_flags[50];

  if (need_math) {
    if (include_root && include_root[0])
      (void)xlang_ensure_formal_std_make_o(include_root, "std/math/math.o", "../std/math/math.o");
    {
      const char *math_push = xlang_rel_o_path_from_argv0(include_root, "std/math/math.o");
      if ((!math_push || !math_push[0]) && math_o && math_o[0])
        math_push = math_o;
      if (invoke_cc_argv_push_existing(argv, ia, argv_cap, math_push)) {
        (void)xlang_ensure_runtime_math_libm_o(NULL);
        {
          const char *rml = xlang_runtime_math_libm_o_path(NULL);
          if (rml && rml[0])
            (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rml);
        }
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lm");
      }
    }
  }
  if (need_sort) {
    int have_sort_body = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp)
        continue;
      if (link_abi_generated_c_contains_substr(cp, "void std_sort_sort_") != 0 ||
          link_abi_generated_c_contains_substr(cp, "void std_sort_sort(") != 0) {
        have_sort_body = 1;
        break;
      }
    }
    if (!have_sort_body)
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, sort_o);
  }
  if (need_vec) {
    int have_vec_body = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp)
        continue;
      if (link_abi_generated_c_contains_substr(cp, "std_vec_new_retVec_u8(void) {") != 0 ||
          link_abi_generated_c_contains_substr(cp, "std_vec_new_retVec_u8(void){") != 0 ||
          link_abi_generated_c_contains_substr(cp, "std_vec_push_Vec_u8_ptr_u8(struct std_vec_Vec_u8 * v, uint8_t x) {") != 0 ||
          link_abi_generated_c_contains_substr(cp, "std_vec_push_Vec_u8_ptr_u8(struct std_vec_Vec_u8 *v, uint8_t x){") != 0) {
        have_vec_body = 1;
        break;
      }
    }
    if (!have_vec_body) {
      int c_prov_cm_v = 0;
      int c_prov_sh_v = 0;
      for (jscan = 0; jscan < n; jscan++) {
        const char *cp = c_paths ? c_paths[jscan] : NULL;
        if (!cp) continue;
        if (link_abi_generated_c_provides_core_mem(cp)) c_prov_cm_v = 1;
        if (link_abi_generated_c_provides_std_heap(cp)) c_prov_sh_v = 1;
      }
      if (include_root && include_root[0]) {
        (void)xlang_ensure_formal_std_make_o(include_root, "std/vec/vec.o", "../std/vec/vec.o");
        if (!c_prov_sh_v) (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
        if (!c_prov_cm_v) (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
      }
      if (invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, "std/vec/vec.o"))) {
        if (!c_prov_sh_v) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
            xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_heap_o()));
        if (!c_prov_cm_v) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
            xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o()));
      }
    }
  }
  if (need_ffi)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, ffi_o);
  if (need_db && invoke_cc_argv_push_existing(argv, ia, argv_cap, db_o)) {
    (void)xlang_ensure_runtime_sqlite_glue_o(NULL);
    {
      const char *rsg = xlang_runtime_sqlite_glue_o_path(NULL);
      if (rsg && rsg[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rsg);
    }
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lsqlite3");
  }
  if (need_elf)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, elf_o);
  if (need_json)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_json_o()));
  if (need_csv)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_csv_o()));
  if (need_set) {
    int c_prov_cm_s = 0, c_prov_sh_s = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp) continue;
      if (link_abi_generated_c_provides_core_mem(cp)) c_prov_cm_s = 1;
      if (link_abi_generated_c_provides_std_heap(cp)) c_prov_sh_s = 1;
    }
    if (include_root && include_root[0]) {
      (void)xlang_ensure_formal_std_make_o(include_root, "std/set/set.o", "../std/set/set.o");
      if (!c_prov_sh_s) (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
      if (!c_prov_cm_s) (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
    }
    if (invoke_cc_argv_push_existing(argv, ia, argv_cap,
            xlang_rel_o_path_from_argv0(include_root, "std/set/set.o"))) {
      if (!c_prov_sh_s) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_heap_o()));
      if (!c_prov_cm_s) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o()));
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, hash_o);
    }
  }
  if (need_map) {
    int c_prov_cm_m = 0, c_prov_sh_m = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp) continue;
      if (link_abi_generated_c_provides_core_mem(cp)) c_prov_cm_m = 1;
      if (link_abi_generated_c_provides_std_heap(cp)) c_prov_sh_m = 1;
    }
    if (include_root && include_root[0]) {
      (void)xlang_ensure_formal_std_make_o(include_root, "std/map/map.o", "../std/map/map.o");
      if (!c_prov_sh_m) (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
      if (!c_prov_cm_m) (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
    }
    if (invoke_cc_argv_push_existing(argv, ia, argv_cap,
            xlang_rel_o_path_from_argv0(include_root, "std/map/map.o"))) {
      if (!c_prov_sh_m) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_heap_o()));
      if (!c_prov_cm_m) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o()));
    }
  }
  if (need_queue && invoke_cc_argv_push_existing(argv, ia, argv_cap,
          xlang_rel_o_path_from_argv0(include_root, "std/queue/queue.o"))) {
    int c_prov_cm_q = 0, c_prov_sh_q = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp) continue;
      if (link_abi_generated_c_provides_core_mem(cp)) c_prov_cm_q = 1;
      if (link_abi_generated_c_provides_std_heap(cp)) c_prov_sh_q = 1;
    }
    if (!c_prov_sh_q) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_heap_o()));
    if (!c_prov_cm_q) (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o()));
  }
  if (need_regex)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, regex_o);
  if (need_compress && invoke_cc_argv_push_existing(argv, ia, argv_cap, compress_o))
    invoke_cc_append_compress_ld(argv, ia, argv_cap, compress_o, NULL);
  else {
    int needs_zlib = 0, needs_zstd = 0, needs_brotli = 0, j;
    for (j = 0; j < n; j++) {
      const char *cp = c_paths ? c_paths[j] : NULL;
      if (!cp) continue;
      if (link_abi_generated_c_needs_zlib(cp))
        needs_zlib = 1;
      if (link_abi_generated_c_needs_zstd(cp))
        needs_zstd = 1;
      if (link_abi_generated_c_needs_brotli(cp))
        needs_brotli = 1;
    }
    if (needs_zlib || needs_zstd || needs_brotli) {
      ld_append_brew_lib_paths((const char **)argv, ia, argv_cap);
      if (needs_zlib) {
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lz");
        (void)xlang_ensure_runtime_compress_zlib_glue_o(NULL);
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
            xlang_runtime_compress_zlib_glue_o_path(NULL));
      }
      if (needs_zstd)
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lzstd");
      if (needs_brotli) {
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lbrotlienc");
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lbrotlidec");
      }
    }
  }
}

/* wave203: invoke_cc_append_std_ensure_push_heavy_b pure orch (cold twin ≡ .x).
 * Ensure-push heavy_b unicode…process_argv complement; co-emit + UNDEF scan. */
void invoke_cc_append_std_ensure_push_heavy_b(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char **c_paths, int n,
    const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o,
    const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o,
    const char *url_o, const char *cli_o, const char *security_o, const char *config_o,
    const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o,
    const char *test_o, const char *async_scheduler_o) {
  int need_unicode, need_dynlib, need_http, need_tar, need_simd, need_context;
  int need_error, need_datetime, need_uuid, need_url, need_cli, need_security;
  int need_config, need_cache, need_trace, need_task, need_schema, need_test, need_socketio;
  int jscan;
  const char *sched_link;
  int task_linked = 0;
  if (!argv || !ia || *ia < 0 || !need_flags || flags_cap < 52)
    return;
  need_unicode = need_flags[29];
  need_dynlib = need_flags[30];
  need_http = need_flags[31];
  need_tar = need_flags[32];
  need_simd = need_flags[33];
  need_context = need_flags[34];
  need_error = need_flags[35];
  need_datetime = need_flags[36];
  need_uuid = need_flags[37];
  need_url = need_flags[38];
  need_cli = need_flags[39];
  need_security = need_flags[40];
  need_config = need_flags[41];
  need_cache = need_flags[42];
  need_trace = need_flags[43];
  need_task = need_flags[44];
  need_schema = need_flags[45];
  need_test = need_flags[46];
  need_socketio = need_flags[47];
  sched_link = async_scheduler_o;

  if (need_unicode) {
    int have_unicode_body = 0;
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp)
        continue;
      if (link_abi_generated_c_contains_substr(cp, "int32_t std_unicode_category(") != 0 ||
          link_abi_generated_c_contains_substr(cp, "int32_t std_unicode_unicode_category(") != 0) {
        have_unicode_body = 1;
        break;
      }
    }
    if (!have_unicode_body)
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, unicode_o);
  }
  if (need_dynlib && invoke_cc_argv_push_existing(argv, ia, argv_cap, dynlib_o)) {
    (void)xlang_ensure_runtime_dynlib_os_o(NULL);
    {
      const char *rdo = xlang_runtime_dynlib_os_o_path(NULL);
      if (rdo && rdo[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rdo);
    }
    if (xlang_host_is_linux())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-ldl");
  }
  if (need_http && invoke_cc_argv_push_existing(argv, ia, argv_cap, http_o)) {
    (void)xlang_ensure_runtime_http_glue_o(NULL);
    {
      const char *rhg = xlang_runtime_http_glue_o_path(NULL);
      if (rhg && rhg[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rhg);
    }
    /* wave288 L4: http_glue residual U link_abi_getenv → user_env face. */
    (void)xlang_ensure_runtime_link_abi_user_env_o(NULL);
    {
      const char *rue = xlang_runtime_link_abi_user_env_o_path(NULL);
      if (rue && rue[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rue);
    }
    if (link_abi_host_is_windows())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, labi_ld_flag_lws2_32());
    need_error = 1;
  }
  if (need_socketio)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_socketio_o()));
  if (need_tar)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, tar_o);
  if (need_simd)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, simd_o);
  /* PLATFORM: SHARED — context.o U atomic_*_c + time_now_*; ensure companions. */
  if (need_context) {
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, context_o);
    (void)xlang_ensure_runtime_atomic_glue_o(NULL);
    {
      const char *rag = xlang_runtime_atomic_glue_o_path(NULL);
      if (rag && rag[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rag);
    }
    (void)xlang_ensure_runtime_time_os_o(NULL);
    {
      const char *rto = xlang_runtime_time_os_o_path(NULL);
      if (rto && rto[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rto);
    }
  }
  if (need_error)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap,
        xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_error_o()));
  if (need_datetime)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, datetime_o);
  if (need_uuid)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, uuid_o);
  if (need_url)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, url_o);
  if (need_cli)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, cli_o);
  if (need_security)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, security_o);
  if (need_config)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, config_o);
  if (need_cache)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, cache_o);
  if (need_trace)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, trace_o);
  if (need_task)
    task_linked = invoke_cc_argv_push_existing(argv, ia, argv_cap, task_o);
  if (need_schema)
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, schema_o);
  if (need_test) {
    /* PLATFORM: SHARED — do not gate companions on first-time test.o push.
     * Dedup of already-pushed test.o used to skip test_fn_invoke / env_os /
     * time_os (mac L4 run-stdtest UNDEF). G.7 ≡ labi_od_push_test_monofile_companions. */
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, test_o);
    (void)xlang_ensure_runtime_test_fn_invoke_o(NULL);
    {
      const char *rtfi = xlang_runtime_test_fn_invoke_o_path(NULL);
      if (rtfi && rtfi[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rtfi);
    }
    (void)xlang_ensure_runtime_env_os_o(NULL);
    {
      const char *reo = xlang_runtime_env_os_o_path(NULL);
      if (reo && reo[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, reo);
    }
    (void)xlang_ensure_runtime_time_os_o(NULL);
    {
      const char *rto = xlang_runtime_time_os_o_path(NULL);
      if (rto && rto[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rto);
    }
  }
  if (!(sched_link && sched_link[0])) {
    for (jscan = 0; jscan < n; jscan++) {
      const char *cp = c_paths ? c_paths[jscan] : NULL;
      if (!cp)
        continue;
      if (xlang_generated_c_needs_async_scheduler(cp)) {
        sched_link = xlang_std_async_scheduler_o_path(include_root);
        break;
      }
    }
  }
  if (task_linked) {
    const char *sched = scheduler_o_for_task_link(task_o, sched_link);
    if (invoke_cc_argv_push_existing(argv, ia, argv_cap, sched)) {
      if (xlang_host_is_linux())
        labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-pthread");
      (void)xlang_ensure_runtime_scheduler_glue_o(NULL);
      {
        const char *rsg = xlang_runtime_scheduler_glue_o_path(NULL);
        if (rsg && rsg[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rsg);
      }
    }
  } else if (sched_link && sched_link[0] &&
             invoke_cc_argv_push_existing(argv, ia, argv_cap, sched_link)) {
    if (xlang_host_is_linux())
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-pthread");
    (void)xlang_ensure_runtime_scheduler_glue_o(NULL);
    {
      const char *rsg = xlang_runtime_scheduler_glue_o_path(NULL);
      if (rsg && rsg[0])
        (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rsg);
    }
  }
  // process_argv complement after std/*.o pushes
  // (C seed: // form — gcc is non-nested and -Wcomment on /* inside /* */;
  //  Xlang .x accepts the same prose as a nested path-safe block comment.)
  // PLATFORM: SHARED — also complement runtime_panic.o when any argv .o has
  // U xlang_panic_ (error.o co-emits core_result_expect_*_or_panic; mid=51 is
  // gen-C use_line only). export_dynamic (backtrace) freezes those T symbols.
  // G.7: peer of .x heavy_b end scan; seed twin must stay same-commit.
  {
    int need_pav = 0;
    int have_process_o = 0;
    int have_pav = 0;
    int need_panic_u = 0;
    int have_panic_o = 0;
    int ai;
    for (ai = 0; ai < *ia && argv[ai]; ai++) {
      const char *e = argv[ai];
      if (!e || e[0] == '-')
        continue;
      if (strstr(e, "process.o") && !strstr(e, "process_argv"))
        have_process_o = 1;
      if (strstr(e, "runtime_process_argv.o") || strstr(e, "process_argv.o"))
        have_pav = 1;
      if (xlang_link_obj_needs_undef_sym(e, "process_xlang_argc_get") ||
          xlang_link_obj_needs_undef_sym(e, "process_xlang_argv_get"))
        need_pav = 1;
      if (strstr(e, "runtime_panic.o"))
        have_panic_o = 1;
      if (xlang_link_obj_needs_undef_sym(e, "xlang_panic_"))
        need_panic_u = 1;
    }
    if (need_pav && !have_process_o && !have_pav) {
      (void)xlang_ensure_runtime_process_argv_o(NULL);
      {
        const char *rpa = xlang_runtime_process_argv_o_path(NULL);
        if (rpa && rpa[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rpa);
      }
    }
    if (need_panic_u && !have_panic_o) {
      (void)xlang_ensure_runtime_panic_o(NULL);
      {
        const char *rp = xlang_runtime_panic_o_path(NULL);
        if (rp && rp[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rp);
      }
      (void)xlang_ensure_runtime_link_abi_user_env_o(NULL);
      {
        const char *rue = xlang_runtime_link_abi_user_env_o_path(NULL);
        if (rue && rue[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rue);
      }
    }
  }
}

/* wave204: heap F-06 use_line needle table (cold twin ≡ .x). */
int labi_icc_heap_f06_needle_count(void) {
  return 11;
}

const char *labi_icc_heap_f06_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_heap_alloc_size_zero";
  if (i == 1)
    return "std_heap_alloc_usize";
  if (i == 2)
    return "std_heap_default_alloc";
  if (i == 3)
    return "std_heap_kind_arena";
  if (i == 4)
    return "std_heap_heap_alloc";
  if (i == 5)
    return "std_heap_alloc_Allocator";
  if (i == 6)
    return "std_heap_realloc_Allocator";
  if (i == 7)
    return "std_heap_free_Allocator";
  if (i == 8)
    return "std_heap_arena64_alloc";
  if (i == 9)
    return "std_heap_map_find";
  if (i == 10)
    return "std_heap_libc_heap_alloc";
  return NULL;
}

/* wave204: invoke_cc_append_heap_f06_ondemand pure orch (cold twin ≡ .x). */
void invoke_cc_append_heap_f06_ondemand(char **argv, int *ia, int argv_cap,
    const char **c_paths, int n, const char *include_root) {
  int need_heap = 0;
  int c_provides_core_mem = 0;
  int c_provides_std_heap = 0;
  int cj;
  int has_c_paths = (c_paths != NULL && n > 0);
  if (!argv || !ia || *ia < 0)
    return;
  if (link_abi_link_needs_std_heap_import(NULL, (const char **)argv, *ia))
    need_heap = 1;
  if (!need_heap && has_c_paths) {
    int nc = labi_icc_heap_f06_needle_count();
    for (cj = 0; cj < n && !need_heap; cj++) {
      const char *cp = c_paths[cj];
      int ki;
      if (!cp)
        continue;
      for (ki = 0; ki < nc; ki++) {
        const char *nd = labi_icc_heap_f06_needle_at(ki);
        if (!nd)
          continue;
        if (link_abi_generated_c_contains_substr_use_line(cp, nd)) {
          need_heap = 1;
          break;
        }
      }
    }
  }
  if (!need_heap)
    return;
  if (has_c_paths) {
    for (cj = 0; cj < n; cj++) {
      if (link_abi_generated_c_provides_core_mem(c_paths[cj]))
        c_provides_core_mem = 1;
      if (link_abi_generated_c_provides_std_heap(c_paths[cj]))
        c_provides_std_heap = 1;
    }
  }
  if (!c_provides_core_mem) {
    const char *mem_o = xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_core_mem_o());
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, mem_o);
  }
  if (!c_provides_std_heap) {
    const char *heap_o = xlang_rel_o_path_from_argv0(include_root, labi_icc_rel_heap_o());
    (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, heap_o);
  }
  /* PLATFORM: SHARED / LINUX gold — page_mmap + asm_io_stubs companions for heap.o. */
  {
    const char *pm_o = xlang_rel_o_path_from_argv0(include_root, labi_od_rel_page_mmap());
    if (invoke_cc_argv_push_existing(argv, ia, argv_cap, pm_o)) {
      (void)xlang_ensure_runtime_asm_io_stubs_o(NULL);
      {
        const char *ris = xlang_runtime_asm_io_stubs_o_path(NULL);
        if (ris && ris[0])
          (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, ris);
      }
    }
  }
}

/* wave206: durable -O{level} slot (≡ .x g_labi_icc_oopt_buf / mega static oopt_buf[8]). */
static char g_labi_icc_oopt_buf[8];

/* Cap 10.7.1 slice11: durable <repo>/compiler/include (≡ .x g_labi_icc_cap_inc_buf). */
static char g_labi_icc_cap_inc_buf[512];

/* Cap 10.7.1 slice11: fill Cap include path BSS (≡ .x invoke_cc_fill_cap_include_path). */
static char *invoke_cc_fill_cap_include_path(const char *include_root) {
  int ri = 0;
  int si;
  const char *suf = "/compiler/include";
  g_labi_icc_cap_inc_buf[0] = '\0';
  if (!include_root || !include_root[0])
    return g_labi_icc_cap_inc_buf;
  while (ri < 494 && include_root[ri]) {
    g_labi_icc_cap_inc_buf[ri] = include_root[ri];
    ri++;
  }
  if (ri > 0) {
    char last = g_labi_icc_cap_inc_buf[ri - 1];
    if (last == '/' || last == '\\')
      ri--;
  }
  for (si = 0; suf[si] && ri < 511; si++, ri++)
    g_labi_icc_cap_inc_buf[ri] = suf[si];
  g_labi_icc_cap_inc_buf[ri] = '\0';
  return g_labi_icc_cap_inc_buf;
}

/* wave206: invoke_cc_append_argv_head_flags pure orch (cold twin ≡ .x). */
void invoke_cc_append_argv_head_flags(char **argv, int *ia, int argv_cap,
    const char *out_path, const char *opt_level, int use_lto, const char *include_root) {
  const char *ol;
  int is_linux;
  int is_apple;
  int skip_nat;
  int is0, is2, is3;
  int k;
  if (!argv || !ia || *ia < 0)
    return;
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, "cc");
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-std=gnu11");
  /* wave223 G.7: link_abi_getenv (not raw getenv). */
  if (link_abi_getenv("XLANG_RUN_QUIET")) {
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-w");
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-Wl,-w");
  }
  is_linux = xlang_host_is_linux();
  if (is_linux)
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-B/usr/bin");
  ol = opt_level;
  if (!ol || !ol[0])
    ol = "2";
  g_labi_icc_oopt_buf[0] = '-';
  g_labi_icc_oopt_buf[1] = 'O';
  for (k = 0; k < 5 && ol[k]; k++)
    g_labi_icc_oopt_buf[2 + k] = ol[k];
  g_labi_icc_oopt_buf[2 + k] = '\0';
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, g_labi_icc_oopt_buf);
  skip_nat = invoke_cc_skip_native_tuning();
  is2 = strcmp(ol, "2");
  is3 = strcmp(ol, "3");
  if (!skip_nat && (is2 == 0 || is3 == 0)) {
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-march=native");
    if (is3 == 0)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-mtune=native");
  }
  is0 = strcmp(ol, "0");
  if (is0 != 0)
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-DNDEBUG");
  if (use_lto && is0 != 0 && !skip_nat)
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-flto");
  if (is_linux && is0 != 0)
    xlang_append_linux_link_harden_impl(argv, ia, argv_cap);
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-o");
  if (out_path && out_path[0])
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, out_path);
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-ffunction-sections");
  labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-fdata-sections");
  /* Skip dead_strip/--gc-sections at -O 0 (≡ NDEBUG/harden/maybe_strip).
   * PLATFORM: MACOS|DARWIN / LINUX — TOOL-005 debug symtab honesty. */
  is_apple = link_abi_host_is_apple();
  if (is0 != 0) {
    if (is_apple)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-Wl,-dead_strip");
    else if (is_linux)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-Wl,--gc-sections");
  }
  /* Cap 10.7.1 slice11: repo -I + Cap <repo>/compiler/include -I. */
  if (include_root && include_root[0]) {
    const char *cap_inc;
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-I");
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, include_root);
    cap_inc = invoke_cc_fill_cap_include_path(include_root);
    if (cap_inc && cap_inc[0]) {
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-I");
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, cap_inc);
    }
  }
}

/* wave207: invoke_cc_append_argv_tail_flags pure orch (cold twin ≡ .x). */
void invoke_cc_append_argv_tail_flags(char **argv, int *ia, int argv_cap,
    const char *thread_o, const char *sync_o, const char *channel_o) {
  int is_linux;
  int is_apple;
  int is_win;
  int need_pth;
  int n_extra;
  int ui;
  int cur;
  const char *ht;
  const char *hs;
  const char *hc;
  const char *flc;
  const char *p;
  if (!argv || !ia || *ia < 0)
    return;
  is_linux = xlang_host_is_linux();
  is_apple = link_abi_host_is_apple();
  is_win = link_abi_host_is_windows();
  /* PLATFORM: POSIX (linux|apple) — optional -pthread + always -lc. */
  if (is_linux || is_apple) {
    need_pth = 0;
    ht = asm_link_obj_skip_missing(thread_o);
    hs = asm_link_obj_skip_missing(sync_o);
    hc = asm_link_obj_skip_missing(channel_o);
    if (ht)
      need_pth = 1;
    if (hs)
      need_pth = 1;
    if (hc)
      need_pth = 1;
    if (need_pth)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-pthread");
    flc = labi_ld_flag_lc();
    if (flc)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, flc);
    else
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lc");
  }
  /* PLATFORM: WINDOWS — PE multi-def (weak alias) alignment flag. */
  if (is_win)
    labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-Wl,--allow-multiple-definition");
  /* User extra .o after std/core + flags (single authority count/at). */
  n_extra = link_abi_user_extra_o_count();
  for (ui = 0; ui < n_extra; ui++) {
    p = link_abi_user_extra_o_at(ui);
    if (p)
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, p);
  }
  /* NULL-terminate for spawn. */
  cur = *ia;
  if (cur < argv_cap) {
    argv[cur] = NULL;
    *ia = cur + 1;
  }
}

/* wave208: invoke_cc_append_minimal_cc_link_tail pure orch (cold twin ≡ .x). */
void invoke_cc_append_minimal_cc_link_tail(char **argv, int *ia, int argv_cap) {
  int is_linux;
  int is_apple;
  int is_win;
  int cur;
  const char *rpav;
  const char *flc;
  if (!argv || !ia || *ia < 0)
    return;
  is_linux = xlang_host_is_linux();
  is_apple = link_abi_host_is_apple();
  is_win = link_abi_host_is_windows();
  /* PLATFORM: WINDOWS — process_argv.o for xlang_process_argc/argv (extern not weak). */
  if (is_win) {
    rpav = xlang_runtime_process_argv_o_path(NULL);
    if (rpav && rpav[0])
      (void)invoke_cc_argv_push_existing(argv, ia, argv_cap, rpav);
  }
  /* PLATFORM: POSIX (linux|apple) — only -lc on minimal path. */
  if (is_linux || is_apple) {
    flc = labi_ld_flag_lc();
    if (flc)
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, flc);
    else
      labi_icc_argv_try_push_flag(argv, ia, argv_cap, "-lc");
  }
  /* NULL-terminate for spawn. */
  cur = *ia;
  if (cur < argv_cap) {
    argv[cur] = NULL;
    *ia = cur + 1;
  }
}

/* Stage 12.2.3: G.7 single env-gate authority (cold twin ≡ .x).
 * FORBID exact "1" hard-deny unless LOG_ONLY; ALLOW exact "1" required.
 * Callers: xlang_invoke_cc early entry, xlang_invoke_cc_impl top (ensure/argv
 * isolation), invoke_cc_run_cc_argv spawn shell.
 * PLATFORM: SHARED — dual-end ALLOW/FORBID. */
int invoke_cc_host_cc_spawn_gate(void) {
  const char *forbid;
  const char *log_only;
  const char *allow;
  /* PLATFORM: SHARED — product FORBID gate (exact "1"; LOG_ONLY fallthrough). */
  forbid = link_abi_getenv("XLANG_FORBID_HOST_CC");
  if (forbid && forbid[0] == '1' && forbid[1] == '\0') {
    log_only = link_abi_getenv("XLANG_FORBID_HOST_CC_LOG_ONLY");
    if (!(log_only && log_only[0] == '1' && log_only[1] == '\0')) {
      link_diag_tool_status("forbid-host-cc", -1);
      return 0;
    }
    /* LOG_ONLY=1: discovery — fall through to ALLOW then spawn (no diag noise). */
  }
  /* PLATFORM: SHARED — Stage 12.2.3 experimental ALLOW (exact "1" required). */
  allow = link_abi_getenv("XLANG_ALLOW_HOST_CC");
  if (!(allow && allow[0] == '1' && allow[1] == '\0')) {
    link_diag_tool_status("host-cc-requires-allow", -1);
    return 0;
  }
  return 1;
}

/* wave205: invoke_cc_run_cc_argv pure orch (cold twin ≡ .x).
 * Host-cc env gates: invoke_cc_host_cc_spawn_gate (G.7).
 * PLATFORM: WINDOWS — never clobber PATH with /usr/local/bin:/usr/bin:/bin before
 * _spawnvp("gcc"); that Unix PATH hides MinGW and yields BLD001 exit 255.
 * POSIX freestanding may still need the setenv when PATH is empty. */
int invoke_cc_run_cc_argv(char **argv) {
  int is_win;
  int is_linux;
  int rc;
  if (!argv)
    return -1;
  if (!invoke_cc_host_cc_spawn_gate())
    return -1;
  is_win = link_abi_host_is_windows();
  if (!is_win)
    (void)setenv("PATH", "/usr/local/bin:/usr/bin:/bin", 1);
  if (is_win) {
    argv[0] = (char *)"gcc";
    rc = xlang_spawn_sync("gcc", (const char *const *)argv);
    if (rc == 0)
      return 0;
    link_diag_tool_status("cc", rc);
    return -1;
  }
  is_linux = xlang_host_is_linux();
  if (is_linux) {
    static const char *cands[6] = {
      "gcc", "cc", "/usr/bin/gcc", "/usr/bin/cc",
      "/usr/local/bin/gcc", "/usr/local/bin/cc"
    };
    int i;
    for (i = 0; i < 6; i++) {
      argv[0] = (char *)cands[i];
      rc = xlang_spawn_sync(cands[i], (const char *const *)argv);
      if (rc == 0)
        return 0;
    }
    link_diag_tool_status("cc", -1);
    return -1;
  }
  /* PLATFORM: APPLE / other POSIX */
  argv[0] = (char *)"cc";
  rc = xlang_spawn_sync("cc", (const char *const *)argv);
  if (rc == 0)
    return 0;
  argv[0] = (char *)"gcc";
  rc = xlang_spawn_sync("gcc", (const char *const *)argv);
  if (rc == 0)
    return 0;
  link_diag_tool_status("cc", -1);
  return -1;
}

/* wave205: invoke_cc_maybe_strip_out pure orch (cold twin ≡ .x). */
void invoke_cc_maybe_strip_out(const char *out_path, const char *opt_level) {
  if (!out_path || !out_path[0])
    return;
  if (!opt_level || !opt_level[0])
    return;
  if (strcmp(opt_level, "0") == 0)
    return;
  if (link_abi_host_is_windows())
    return;
  invoke_cc_strip_out_x(out_path);
}


#else
int labi_linux_harden_flag_count(void);
const char *labi_linux_harden_flag_at(int i);
int labi_invoke_cc_skip_native_env_count(void);
const char *labi_invoke_cc_skip_native_env_at(int i);
int invoke_cc_skip_native_tuning(void);
const char *labi_icc_rel_core_builtin_o(void);
const char *labi_icc_rel_core_builtin_abi_h(void);
const char *labi_icc_rel_core_mem_o(void);
const char *labi_icc_rel_core_slice_o(void);
const char *labi_icc_rel_db_kv_o(void);
const char *labi_icc_rel_db_arrow_o(void);
const char *labi_icc_rel_csv_o(void);
const char *labi_icc_rel_error_o(void);
const char *labi_icc_rel_heap_o(void);
const char *labi_icc_rel_json_o(void);
const char *labi_icc_rel_log_o(void);
const char *labi_icc_rel_socketio_o(void);
int labi_icc_needs_rel_count(void);
const char *labi_icc_needs_rel_at(int i);
void xlang_append_linux_link_harden_impl(char *argv[], int *la, int cap);
void labi_icc_argv_try_push_flag(char **argv, int *ia, int cap, const char *flag);
void invoke_cc_append_early_needs(char **argv, int *ia, int argv_cap,
    const char **c_paths, int n, const char *include_root,
    const char *random_o, const char *time_o, const char *runtime_o, const char *runtime_panic_o);
int labi_icc_std_need_count(void);
int labi_icc_std_need_needle_count(int mid);
const char *labi_icc_std_need_needle_at(int mid, int i);
void invoke_cc_scan_std_module_needs(const char **c_paths, int n, int *flags, int flags_cap);
void invoke_cc_append_std_ensure_push_front(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char *process_o, const char *string_o, const char *heap_o, const char *path_o,
    const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o,
    const char *time_o, const char *random_o, const char *env_o);
void invoke_cc_append_std_ensure_push_mid(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o,
    const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o);
void invoke_cc_append_std_ensure_push_heavy_a(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char **c_paths, int n,
    const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o,
    const char *elf_o, const char *regex_o, const char *compress_o, const char *hash_o);
void invoke_cc_append_std_ensure_push_heavy_b(char **argv, int *ia, int argv_cap,
    int *need_flags, int flags_cap, const char *include_root,
    const char **c_paths, int n,
    const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o,
    const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o,
    const char *url_o, const char *cli_o, const char *security_o, const char *config_o,
    const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o,
    const char *test_o, const char *async_scheduler_o);
int labi_icc_heap_f06_needle_count(void);
const char *labi_icc_heap_f06_needle_at(int i);
void invoke_cc_append_heap_f06_ondemand(char **argv, int *ia, int argv_cap,
    const char **c_paths, int n, const char *include_root);
int invoke_cc_run_cc_argv(char **argv);
void invoke_cc_maybe_strip_out(const char *out_path, const char *opt_level);
void invoke_cc_append_argv_head_flags(char **argv, int *ia, int argv_cap,
    const char *out_path, const char *opt_level, int use_lto, const char *include_root);
void invoke_cc_append_argv_tail_flags(char **argv, int *ia, int argv_cap,
    const char *thread_o, const char *sync_o, const char *channel_o);
void invoke_cc_append_minimal_cc_link_tail(char **argv, int *ia, int argv_cap);
#endif

int labi_invoke_cc_list_slice_marker(void) {
  return 1;
}
