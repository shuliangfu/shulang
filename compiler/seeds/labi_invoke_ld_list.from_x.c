/* seeds/labi_invoke_ld_list.from_x.c — G-02f-275 P2 link_abi L6 invoke_ld list pure → R2 full
 * Logic source: src/runtime/labi_invoke_ld_list.x
 * Hybrid: XLANG_LABI_INVOKE_LD_LIST_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full：公共业务符号由 full .x 提供：
 *   labi_ld_brew_lib_path_{count,at}
 *   labi_ld_compress_flag_{count,at} + labi_ld_flag_lz/zstd/brotli*
 *   labi_ld_flag_lm/sqlite3/pthread/ldl/lc/lSystem/lws2_32/lbcrypt
 *   labi_ld_driver_{clang,ld,gcc,cc} + labi_ld_mach_entry_main + labi_ld_flag_{e,o}
 *   labi_ld_common_tail_flag_{count,at}
 *   ld_append_brew_lib_paths (wave152 pure orch; Cap residual link_abi_host_is_apple)
 *   asm_ld_append_compress_libs (wave153 pure orch; Cap residual needs+ensure+path)
 *   invoke_cc_append_compress_ld (wave154 pure orch; Cap residual needs+ensure+path
 *     + pure push_existing for glue realpath/skip/dedup)
 *   xlang_asm_ld_append_mach_tail_libs_impl (wave156 pure orch; flags i32 layout
 *     + pure flag_* + peer compress orch + peer needs_compress)
 *   xlang_asm_ld_append_unix_gcc_tail_libs_impl (wave157 pure orch; host_is_linux
 *     + host_is_apple for -ldl / else -lc gates)
 *   invoke_cc_append_net_tls_ld (wave158 pure orch; Cap residual exports_marker +
 *     realpath_cap + rel_o_path + pure push_existing + host_is_apple for brew -L)
 *   invoke_cc_argv_push_existing (wave179 pure orch; Cap residual resolve pool)
 *   invoke_cc_argv_resolve_existing_path (wave215/255 pure thin; Cap residual
 *     resolve_existing_path_impl = multi-slot realpath pool only; pure owns skip_missing)
 *   ensure_std_net_o_auto_tls (wave187 pure orch; Cap residual link_abi_getenv+link_abi_system+
 *     realpath_cap+exports_marker; shell make net-o-* Cap residual; wave222 getenv pure; wave224 system pure)
 *   xlang_ensure_formal_std_make_o (wave188 pure orch; Cap residual link_abi_getenv+
 *     path_executable+realpath_cap+link_abi_system+skip_missing; wave221 X_OK pure; wave222 getenv pure; wave224 system pure)
 *   labi_std_append_formal_ensure_for_rel (wave191 pure orch; Cap residual repo_root +
 *     ensure_runtime_* + peer push_obj; formal ensure companions for append_std OP_STD)
 *   labi_std_append_glue_for_op (wave192 pure orch; Cap residual ensure_runtime_*_glue +
 *     peer path + push_obj; append_std OP_GLUE_* plan leaves)
 *   labi_std_append_primary_for_op (wave193 pure orch; Cap residual needs_* + ensure/path +
 *     push_obj; append_std IO_STUBS + PRIMARY_* plan leaves)
 *   labi_std_append_process_argv_if (wave193 pure orch; Cap residual process_argv ensure+path;
 *     complement after plan loop when heavy std without process.o)
 *   labi_std_append_task_special (wave194 pure orch; Cap residual skip/path/bank + formal ensure;
 *     append_std TASK_SPECIAL task+scheduler+scheduler_glue)
 *   labi_std_append_op_std (wave195 pure orch; fk→flag_out map + fk0/fk1–13 gate +
 *     formal ensure + push_obj; append_std OP_STD plan leaf)
 *   xlang_asm_ld_append_std_objs_for_user (wave196 pure orch; plan shell init+loop+
 *     dispatch wave190–195 leaves + process_argv complement)
 * Cap residual: host_is_apple; needs+ensure+path Cap;
 *   invoke_cc_argv_resolve_existing_path_impl (realpath pool only; wave215/255 pure owns
 *     null/empty + skip_missing);
 *   exports_marker / realpath_cap / xlang_rel_o_path_from_argv0;
 *   spawn/ld/cc IO; contains_substr / undef_sym / path_io / wait / strerror / ld_debug_argv;
 *   link_abi_getenv / link_abi_system / path_executable for ensure_std_net + formal_std_make
 *     (wave187/188 Cap residual; wave221 X_OK pure; wave222 getenv pure; wave224 system pure);
 *   runtime ensure/path peers for wave191 formal companions + wave192 glue leaves;
 *   needs + primary ensure/path + process_argv for wave193 primary/complement;
 *   task/scheduler path peers + bank for wave194 TASK_SPECIAL;
 *   fk gate peers (wave135/190) for wave195 OP_STD;
 *   plan table accessors (labi_std_list L8) for wave196 plan shell.
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 * Prove：seeds/labi_invoke_ld_list_surface.from_x.c（-E 同构）nm IDENTICAL。
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
/* ShuAsmLdStdLinkFlags for wave156/157 cold twin (standalone seed cc + mega include). */
#include "runtime_link_abi.h"

/* Cap residual / peer pure always provided by mega (or other pure slices); cold twin calls them. */
int link_abi_host_is_apple(void);
int xlang_host_is_linux(void);
int link_abi_obj_needs_zlib(const char *obj_o);
int link_abi_obj_needs_zstd(const char *obj_o);
int link_abi_obj_needs_brotli(const char *obj_o);
int link_abi_user_o_needs_compress_libs(const char *user_o);
int xlang_link_obj_needs_undef_sym(const char *user_o, const char *sym);
int xlang_ensure_runtime_compress_zlib_glue_o(const char *argv0);
const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0);
/* Cap residual always (wave215/255): multi-slot realpath pool body only (mega). */
const char *invoke_cc_argv_resolve_existing_path_impl(const char *path);
/* wave215/255 pure thin public (cold twin under #ifndef; hybrid FROM_X → L6 pure .x). */
const char *invoke_cc_argv_resolve_existing_path(const char *path);
/* Peer pure path_io: skip_missing used by cold twin resolve orch (wave255). */
const char *asm_link_obj_skip_missing(const char *path);
int link_abi_obj_exports_marker(const char *obj_o, const char *marker);
const char *link_abi_realpath_cap(const char *path, char *out);
int32_t link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path);
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
/* Cap residual (wave187/188 ensure shell make): skip_missing (+ shell via link_abi_system).
 * wave221: X_OK via public pure thin link_abi_path_executable.
 * wave222: env via public pure thin link_abi_getenv (labi_diag_pure L1).
 * wave224: shell make via public pure thin link_abi_system (labi_diag_pure L1). */
const char *link_abi_getenv(const char *name);
int link_abi_system(const char *cmd);
int link_abi_path_executable(const char *path);
/* asm_link_obj_skip_missing declared above resolve pure (wave255). */
/* Peer pure / Cap residual (wave191 formal companions + wave192 OP_GLUE_* leaves). */
const char *xlang_repo_root_from_argv0(const char *argv0);
int xlang_ensure_runtime_env_os_o(const char *argv0);
const char *xlang_runtime_env_os_o_path(const char *argv0);
int xlang_ensure_runtime_random_fill_o(const char *argv0);
const char *xlang_runtime_random_fill_o_path(const char *argv0);
int xlang_ensure_runtime_time_os_o(const char *argv0);
const char *xlang_runtime_time_os_o_path(const char *argv0);
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, int *flag_out);
/* Peer pure (ondemand L8b): probe just-ensured formal .o for std.heap API UNDEFs. */
int link_abi_user_o_needs_std_heap_api(const char *user_o);
int xlang_ensure_runtime_queue_contention_o(const char *argv0);
const char *xlang_runtime_queue_contention_o_path(const char *argv0);
void labi_std_append_queue_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, void *flags);
int xlang_ensure_runtime_test_fn_invoke_o(const char *argv0);
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0);
void labi_std_append_test_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la);
/* Peer pure / Cap residual (wave194 TASK_SPECIAL). */
int labi_user_needs_std_task(const char *user_o);
const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler);
const char *xlang_std_async_scheduler_o_path(const char *argv0);
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots,
    void *bank);
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la, const char *p);
int xlang_ensure_runtime_scheduler_glue_o(const char *argv0);
const char *xlang_runtime_scheduler_glue_o_path(const char *argv0);
/* Peer pure (wave135/190 fk gates for wave195 OP_STD). */
int labi_std_fk0_user_needs_rel(const char *user_o, const char *rel);
int labi_std_fk_user_needs(const char *user_o, int fk);
/* wave192 glue ensure+path peers (ensure_list L4 / path_pure L0). */
int xlang_ensure_runtime_thread_glue_o(const char *argv0);
const char *xlang_runtime_thread_glue_o_path(const char *argv0);
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
int xlang_ensure_runtime_math_libm_o(const char *argv0);
const char *xlang_runtime_math_libm_o_path(const char *argv0);
int xlang_ensure_runtime_sqlite_glue_o(const char *argv0);
const char *xlang_runtime_sqlite_glue_o_path(const char *argv0);
int xlang_ensure_runtime_dynlib_os_o(const char *argv0);
const char *xlang_runtime_dynlib_os_o_path(const char *argv0);
int xlang_ensure_runtime_http_glue_o(const char *argv0);
const char *xlang_runtime_http_glue_o_path(const char *argv0);
/* wave193 primary/complement peers (ondemand needs + path_pure + process_argv). */
int labi_user_needs_runtime_time_os(const char *user_o);
int labi_user_needs_runtime_random_fill(const char *user_o);
int labi_user_needs_runtime_env_os(const char *user_o);
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
const char *xlang_runtime_panic_o_path(const char *argv0);
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0);
int xlang_ensure_runtime_link_abi_user_env_o(const char *argv0);
int xlang_ensure_runtime_process_argv_o(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
/* Forward: defined later; formal env companion calls it. */
void labi_std_append_process_argv_if(int need, const char *link_argv0,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);

#ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X

/* wave215/255: pure thin invoke_cc_argv_resolve_existing_path (cold twin ≡ .x).
 * Pure: null/empty + asm_link_obj_skip_missing; Cap residual _impl = multi-slot
 * realpath pool only (always mega). wave255 moved skip_missing out of _impl.
 * PLATFORM: SHARED — included into mega cold path under same ifndef; hybrid FROM_X
 * uses L6 pure .x public and skips this body.
 */
const char *invoke_cc_argv_resolve_existing_path(const char *path) {
  const char *use;
  if (path == NULL)
    return NULL;
  if (path[0] == 0)
    return NULL;
  use = asm_link_obj_skip_missing(path);
  if (!use)
    return NULL;
  return invoke_cc_argv_resolve_existing_path_impl(use);
}

/* wave179: pure orch invoke_cc_argv_push_existing (cold twin ≡ .x).
 * Cap residual resolve (public → _impl) + pure gates/dedup/append. PLATFORM: SHARED.
 */
int invoke_cc_argv_push_existing(char *argv[], int *ia, int max_ia, const char *path) {
  const char *use;
  int cur;
  if (!argv || !ia || !path || !path[0])
    return 0;
  cur = *ia;
  if (cur >= max_ia - 1)
    return 0;
  use = invoke_cc_argv_resolve_existing_path(path);
  if (!use)
    return 0;
  /* G.7: has_obj (string + realpath) — strcmp-only missed CLI relative extra
   * vs auto-pushed compiler-dir absolute. Darwin ld duplicate-symbol. */
  if (link_abi_asm_ld_argv_has_obj((const char **)argv, cur, use))
    return 0;
  if (link_abi_asm_ld_argv_has_obj((const char **)argv, cur, path))
    return 0;
  argv[(*ia)++] = (char *)use;
  return 1;
}

int labi_ld_brew_lib_path_count(void) {
  return 2;
}

const char *labi_ld_brew_lib_path_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "-L/opt/homebrew/lib";
  if (i == 1)
    return "-L/usr/local/lib";
  return NULL;
}

const char *labi_ld_flag_lz(void) { return "-lz"; }
const char *labi_ld_flag_lzstd(void) { return "-lzstd"; }
const char *labi_ld_flag_lbrotlienc(void) { return "-lbrotlienc"; }
const char *labi_ld_flag_lbrotlidec(void) { return "-lbrotlidec"; }

int labi_ld_compress_flag_count(void) {
  return 4;
}

const char *labi_ld_compress_flag_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "-lz";
  if (i == 1)
    return "-lzstd";
  if (i == 2)
    return "-lbrotlienc";
  if (i == 3)
    return "-lbrotlidec";
  return NULL;
}

const char *labi_ld_flag_lm(void) { return "-lm"; }
const char *labi_ld_flag_lsqlite3(void) {
  /* PLATFORM: LINUX — SONAME; no libsqlite3-dev on Ubuntu gold.
   * PLATFORM: MACOS|WINDOWS — -lsqlite3. Twin of labi_invoke_ld_list.x. */
#if defined(__linux__)
  return "-l:libsqlite3.so.0";
#else
  return "-lsqlite3";
#endif
}
const char *labi_ld_flag_pthread(void) { return "-pthread"; }
const char *labi_ld_flag_lpthread(void) { return "-lpthread"; }
const char *labi_ld_flag_ldl(void) { return "-ldl"; }
const char *labi_ld_flag_lc(void) { return "-lc"; }
const char *labi_ld_flag_lSystem(void) { return "-lSystem"; }
const char *labi_ld_flag_lws2_32(void) { return "-lws2_32"; }
const char *labi_ld_flag_lbcrypt(void) { return "-lbcrypt"; }

/* wave158: net_tls pure flag/marker/rel catalog (cold twin ≡ .x). */
const char *labi_ld_flag_L_hb_openssl(void) { return "-L/opt/homebrew/opt/openssl/lib"; }
const char *labi_ld_flag_L_hb_mbedtls(void) { return "-L/opt/homebrew/opt/mbedtls/lib"; }
const char *labi_ld_flag_lssl(void) { return "-lssl"; }
const char *labi_ld_flag_lcrypto(void) { return "-lcrypto"; }
const char *labi_ld_flag_lmbedtls(void) { return "-lmbedtls"; }
const char *labi_ld_flag_lmbedx509(void) { return "-lmbedx509"; }
const char *labi_ld_flag_lmbedcrypto(void) { return "-lmbedcrypto"; }
const char *labi_net_tls_openssl_marker(void) { return "xlang_net_tls_openssl_marker"; }
const char *labi_net_tls_mbedtls_marker(void) { return "xlang_net_tls_mbedtls_marker"; }
const char *labi_rel_tls_openssl_o(void) { return "std/net/tls_openssl.o"; }
const char *labi_rel_tls_mbedtls_o(void) { return "std/net/tls_mbedtls.o"; }

void labi_append_openssl_ld_flags(char *argv[], int *i, int argv_cap) {
  if (!argv || !i)
    return;
  if (link_abi_host_is_apple() && *i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_L_hb_openssl();
  if (*i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_lssl();
  if (*i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_lcrypto();
}

void labi_append_mbedtls_ld_flags(char *argv[], int *i, int argv_cap) {
  if (!argv || !i)
    return;
  if (link_abi_host_is_apple() && *i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_L_hb_mbedtls();
  if (*i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_lmbedtls();
  if (*i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_lmbedx509();
  if (*i < argv_cap - 1)
    argv[(*i)++] = (char *)labi_ld_flag_lmbedcrypto();
}

const char *labi_ld_driver_clang(void) { return "clang"; }
const char *labi_ld_driver_ld(void) { return "ld"; }
const char *labi_ld_driver_gcc(void) { return "gcc"; }
const char *labi_ld_driver_cc(void) { return "cc"; }
const char *labi_ld_mach_entry_main(void) { return "_main"; }
const char *labi_ld_flag_e(void) { return "-e"; }
const char *labi_ld_flag_o(void) { return "-o"; }

int labi_ld_common_tail_flag_count(void) {
  return 7;
}

const char *labi_ld_common_tail_flag_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "-lm";
  if (i == 1)
    return labi_ld_flag_lsqlite3();
  if (i == 2)
    return "-pthread";
  if (i == 3)
    return "-lpthread";
  if (i == 4)
    return "-ldl";
  if (i == 5)
    return "-lc";
  if (i == 6)
    return "-lSystem";
  return NULL;
}

/* wave152: ld_append_brew_lib_paths pure orch (cold twin ≡ .x; Cap residual host_is_apple). */
void ld_append_brew_lib_paths(const char **argv, int *la, int max_la) {
  int n;
  int k;
  if (!link_abi_host_is_apple())
    return;
  if (!argv || !la)
    return;
  n = labi_ld_brew_lib_path_count();
  for (k = 0; k < n; k++) {
    const char *p;
    if (*la >= max_la - 1)
      break;
    p = labi_ld_brew_lib_path_at(k);
    if (!p || !p[0])
      continue;
    argv[(*la)++] = p;
  }
}

/* wave153: asm_ld_append_compress_libs pure orch (cold twin ≡ .x). */
void asm_ld_append_compress_libs(const char *compress_o, const char *user_o, const char **argv, int *la, int max_la) {
  if (!argv || !la)
    return;
  if (link_abi_obj_needs_zlib(compress_o) || link_abi_obj_needs_zlib(user_o)) {
    ld_append_brew_lib_paths(argv, la, max_la);
    if (*la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lz();
    (void)xlang_ensure_runtime_compress_zlib_glue_o(NULL);
    {
      const char *glue = xlang_runtime_compress_zlib_glue_o_path(NULL);
      if (glue && glue[0] && *la < max_la - 1)
        argv[(*la)++] = glue;
    }
  }
  if (link_abi_obj_needs_zstd(compress_o) || link_abi_obj_needs_zstd(user_o)) {
    ld_append_brew_lib_paths(argv, la, max_la);
    if (*la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lzstd();
  }
  if (link_abi_obj_needs_brotli(compress_o) || link_abi_obj_needs_brotli(user_o)) {
    ld_append_brew_lib_paths(argv, la, max_la);
    if (*la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lbrotlienc();
    if (*la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lbrotlidec();
  }
}

/* wave154: invoke_cc_append_compress_ld pure orch (cold twin ≡ .x; Cap residual push_existing). */
void invoke_cc_append_compress_ld(char *argv[], int *i, int argv_cap, const char *compress_o, const char *user_o) {
  if (!argv || !i || *i >= argv_cap - 1)
    return;
  if (link_abi_obj_needs_zlib(compress_o) || link_abi_obj_needs_zlib(user_o)) {
    ld_append_brew_lib_paths((const char **)argv, i, argv_cap);
    if (*i < argv_cap - 1)
      argv[(*i)++] = (char *)labi_ld_flag_lz();
    (void)xlang_ensure_runtime_compress_zlib_glue_o(NULL);
    (void)invoke_cc_argv_push_existing(argv, i, argv_cap,
        xlang_runtime_compress_zlib_glue_o_path(NULL));
  }
  if (link_abi_obj_needs_zstd(compress_o) || link_abi_obj_needs_zstd(user_o)) {
    ld_append_brew_lib_paths((const char **)argv, i, argv_cap);
    if (*i < argv_cap - 1)
      argv[(*i)++] = (char *)labi_ld_flag_lzstd();
  }
  if (link_abi_obj_needs_brotli(compress_o) || link_abi_obj_needs_brotli(user_o)) {
    ld_append_brew_lib_paths((const char **)argv, i, argv_cap);
    if (*i < argv_cap - 1)
      argv[(*i)++] = (char *)labi_ld_flag_lbrotlienc();
    if (*i < argv_cap - 1)
      argv[(*i)++] = (char *)labi_ld_flag_lbrotlidec();
  }
}

/* wave156: xlang_asm_ld_append_mach_tail_libs_impl pure orch (cold twin ≡ .x).
 * Signature keeps ShuAsmLdStdLinkFlags* (mega ABI); pure .x reads same LP64 i32 layout. */
void xlang_asm_ld_append_mach_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, const char **argv, int *la, int max_la, int append_lsystem) {
  int need_pt;
  int need_comp;
  if (!flags || !argv || !la || *la < 0)
    return;
  need_pt = (flags->have_thread || flags->have_sync || flags->have_channel) ? 1 : 0;
  if (flags->have_math && *la < max_la - 1)
    argv[(*la)++] = labi_ld_flag_lm();
  need_comp = flags->have_compress;
  if (!need_comp)
    need_comp = link_abi_user_o_needs_compress_libs(user_o);
  if (need_comp)
    asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la);
  /* PLATFORM: SHARED — -lsqlite3 only when glue.o U sqlite3_open (real lib).
   * Stub glue (no sqlite3.h) must not pull -lsqlite3 (Ubuntu gold). Twin of .x. */
  if (flags->have_sqlite && *la < max_la - 1) {
    const char *gp = asm_link_obj_skip_missing("compiler/runtime_sqlite_glue.o");
    int need_lib = 1;
    if (!gp)
      gp = asm_link_obj_skip_missing("runtime_sqlite_glue.o");
    if (gp)
      need_lib = xlang_link_obj_needs_undef_sym(gp, "sqlite3_open");
    if (need_lib)
      argv[(*la)++] = labi_ld_flag_lsqlite3();
  }
  if (need_pt && *la < max_la - 1)
    argv[(*la)++] = labi_ld_flag_lpthread();
  if (append_lsystem && *la < max_la - 1)
    argv[(*la)++] = labi_ld_flag_lSystem();
}

/* wave157: xlang_asm_ld_append_unix_gcc_tail_libs_impl pure orch (cold twin ≡ .x).
 * Signature keeps ShuAsmLdStdLinkFlags* (mega ABI); pure .x reads same LP64 i32 layout.
 * -ldl gated by peer xlang_host_is_linux; else-branch -lc by linux|apple. */
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, int need_pt, const char **argv, int *la, int max_la) {
  int need_comp;
  int always_lc;
  if (!flags || !argv || !la || *la < 0)
    return;
  /* pthread: have_io uses -pthread; !have_io && need_pt uses -lpthread (≡ mega). */
  if (flags->have_io) {
    if (need_pt && *la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_pthread();
  } else if (need_pt && *la < max_la - 1) {
    argv[(*la)++] = labi_ld_flag_lpthread();
  }
  if (flags->have_math && *la < max_la - 1)
    argv[(*la)++] = labi_ld_flag_lm();
  need_comp = flags->have_compress;
  if (!need_comp)
    need_comp = link_abi_user_o_needs_compress_libs(user_o);
  if (need_comp)
    asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la);
  /* PLATFORM: SHARED — -lsqlite3 only when glue.o U sqlite3_open. Twin of .x. */
  if (flags->have_sqlite && *la < max_la - 1) {
    const char *gp = asm_link_obj_skip_missing("compiler/runtime_sqlite_glue.o");
    int need_lib = 1;
    if (!gp)
      gp = asm_link_obj_skip_missing("runtime_sqlite_glue.o");
    if (gp)
      need_lib = xlang_link_obj_needs_undef_sym(gp, "sqlite3_open");
    if (need_lib)
      argv[(*la)++] = labi_ld_flag_lsqlite3();
  }
  /* -ldl only on Linux when dynlib (mega #if __linux__). */
  if (flags->have_dynlib && xlang_host_is_linux() && *la < max_la - 1)
    argv[(*la)++] = labi_ld_flag_ldl();
  always_lc = (flags->have_io || flags->have_net || need_pt) ? 1 : 0;
  if (always_lc) {
    if (*la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lc();
  } else {
    /* Final else: -lc only on linux|apple when any of heap/fs/math/compress/sqlite/dynlib. */
    if ((flags->have_libc_heap || flags->have_fs || flags->have_math || flags->have_compress
            || flags->have_sqlite || flags->have_dynlib)
        && (xlang_host_is_linux() || link_abi_host_is_apple()) && *la < max_la - 1)
      argv[(*la)++] = labi_ld_flag_lc();
  }
}

/* wave158: invoke_cc_append_net_tls_ld pure orch (cold twin ≡ .x).
 * Cap residual: exports_marker + realpath_cap + rel_o_path + push_existing.
 * Apple brew -L gated by host_is_apple inside append_* helpers. */
int invoke_cc_append_net_tls_ld(char *argv[], int *i, int argv_cap, const char *net_o, const char *repo_root) {
  char abs_buf[4096];
  const char *use;
  const char *rn;
  const char *tls_o;
  const char *mk_ssl;
  const char *mk_mb;
  if (!argv || !i || *i >= argv_cap - 1)
    return 0;
  mk_ssl = labi_net_tls_openssl_marker();
  mk_mb = labi_net_tls_mbedtls_marker();
  /* Phase 1: net_o markers (legacy co-located; rare post F-04 v8). */
  if (net_o && net_o[0]) {
    use = net_o;
    rn = link_abi_realpath_cap(net_o, abs_buf);
    if (rn && rn[0])
      use = rn;
    if (link_abi_obj_exports_marker(use, mk_ssl)) {
      labi_append_openssl_ld_flags(argv, i, argv_cap);
      return 1;
    }
    if (link_abi_obj_exports_marker(use, mk_mb)) {
      labi_append_mbedtls_ld_flags(argv, i, argv_cap);
      return 1;
    }
  }
  if (!repo_root || !repo_root[0])
    return 0;
  /* Phase 2: std/net/tls_openssl.o */
  tls_o = xlang_rel_o_path_from_argv0(repo_root, labi_rel_tls_openssl_o());
  if (tls_o && tls_o[0]) {
    use = tls_o;
    rn = link_abi_realpath_cap(tls_o, abs_buf);
    if (rn && rn[0])
      use = rn;
    if (link_abi_obj_exports_marker(use, mk_ssl)) {
      (void)invoke_cc_argv_push_existing(argv, i, argv_cap, tls_o);
      labi_append_openssl_ld_flags(argv, i, argv_cap);
      return 1;
    }
  }
  /* Phase 2b: std/net/tls_mbedtls.o */
  tls_o = xlang_rel_o_path_from_argv0(repo_root, labi_rel_tls_mbedtls_o());
  if (tls_o && tls_o[0]) {
    use = tls_o;
    rn = link_abi_realpath_cap(tls_o, abs_buf);
    if (rn && rn[0])
      use = rn;
    if (link_abi_obj_exports_marker(use, mk_mb)) {
      (void)invoke_cc_argv_push_existing(argv, i, argv_cap, tls_o);
      labi_append_mbedtls_ld_flags(argv, i, argv_cap);
      return 1;
    }
  }
  return 0;
}

/* wave187: ensure_std_net_o_auto_tls pure orch (cold twin ≡ .x).
 * Cap residual: link_abi_getenv + link_abi_system + realpath_cap + exports_marker.
 * Pure helpers + mode orch. PLATFORM: SHARED. wave222/224 pure faces.
 */
int labi_net_tls_buf_append(char *dst, int cap, int pos, const char *src) {
  int i = 0;
  if (!dst || pos < 0 || pos >= cap)
    return -1;
  if (!src) {
    dst[pos] = '\0';
    return pos;
  }
  while (src[i]) {
    if (pos + 1 >= cap) {
      dst[pos] = '\0';
      return -1;
    }
    dst[pos++] = src[i++];
  }
  dst[pos] = '\0';
  return pos;
}

/* wave944: 0-make hub (tests/lib/compiler-make.sh) after Makefile delete. */
int labi_net_tls_build_make_cmd(char *cmd, int cap, const char *repo_root, const char *target) {
  int pos = 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "bash '");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root);
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "/tests/lib/compiler-make.sh' ");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, target);
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, " >/dev/null 2>&1");
  if (pos < 0)
    return 0;
  return 1;
}

int labi_net_tls_join_repo_rel(char *path_buf, int cap, const char *repo_root, const char *rel) {
  int pos = 0;
  pos = labi_net_tls_buf_append(path_buf, cap, pos, repo_root);
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(path_buf, cap, pos, "/");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(path_buf, cap, pos, rel);
  if (pos < 0)
    return 0;
  return 1;
}

void ensure_std_net_o_auto_tls(const char *repo_root) {
  char cmd[640];
  char path_buf[4096];
  char resolved[4096];
  const char *mode;
  const char *mk_ssl;
  const char *mk_mb;
  const char *rp;
  if (!repo_root || !repo_root[0])
    return;
  mode = link_abi_getenv("XLANG_NET_TLS");
  if (!mode || !mode[0])
    return;
  mk_ssl = labi_net_tls_openssl_marker();
  mk_mb = labi_net_tls_mbedtls_marker();
  if (strcmp(mode, "stub") == 0) {
    if (labi_net_tls_build_make_cmd(cmd, 640, repo_root, "net-o-stub"))
      (void)link_abi_system(cmd); /* wave224 G.7 */
    return;
  }
  if (labi_net_tls_join_repo_rel(path_buf, 4096, repo_root, "std/net/tls_openssl.o")) {
    rp = link_abi_realpath_cap(path_buf, resolved);
    if (rp && link_abi_obj_exports_marker(rp, mk_ssl))
      return;
  }
  if (labi_net_tls_join_repo_rel(path_buf, 4096, repo_root, "std/net/tls_mbedtls.o")) {
    rp = link_abi_realpath_cap(path_buf, resolved);
    if (rp && link_abi_obj_exports_marker(rp, mk_mb))
      return;
  }
  resolved[0] = '\0';
  if (labi_net_tls_join_repo_rel(path_buf, 4096, repo_root, "std/net/net.o")) {
    rp = link_abi_realpath_cap(path_buf, resolved);
    if (!rp)
      rp = link_abi_realpath_cap("std/net/net.o", resolved);
    if (rp && (link_abi_obj_exports_marker(rp, mk_ssl) || link_abi_obj_exports_marker(rp, mk_mb)))
      return;
  }
  if (strcmp(mode, "openssl") == 0) {
    if (labi_net_tls_build_make_cmd(cmd, 640, repo_root, "net-o-openssl"))
      (void)link_abi_system(cmd); /* wave224 G.7 */
    return;
  }
  if (strcmp(mode, "mbedtls") == 0) {
    if (labi_net_tls_build_make_cmd(cmd, 640, repo_root, "net-o-mbedtls"))
      (void)link_abi_system(cmd); /* wave224 G.7 */
    return;
  }
  if (strcmp(mode, "auto") != 0)
    return;
  if (labi_net_tls_build_make_cmd(cmd, 640, repo_root, "net-o-openssl")) {
    if (link_abi_system(cmd) != 0) { /* wave224 G.7 */
      if (labi_net_tls_build_make_cmd(cmd, 640, repo_root, "net-o-mbedtls"))
        (void)link_abi_system(cmd); /* wave224 G.7 */
    }
  }
}

/* wave188: xlang_ensure_formal_std_make_o pure orch (cold twin ≡ .x).
 * Cap residual: link_abi_getenv + path_executable + realpath_cap + link_abi_system + skip_missing.
 * Pure path/XLANG/make-cmd join. PLATFORM: SHARED. wave221/222/224 pure faces.
 */
int labi_formal_std_build_make_cmd(char *cmd, int cap, const char *xlang_bin,
                                   const char *repo_root, const char *make_target) {
  int pos = 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "XLANG_FORMAL_STD_ENSURE=1 XLANG='");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, xlang_bin);
  if (pos < 0)
    return 0;
  /* wave944: 0-make hub after Makefile delete (G.7 single body with tests hub). */
  pos = labi_net_tls_buf_append(cmd, cap, pos, "' bash '");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root);
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "/tests/lib/compiler-make.sh' '");
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, make_target);
  if (pos < 0)
    return 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "'");
  if (pos < 0)
    return 0;
  return 1;
}

int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo,
                                  const char *make_target) {
  char abs[4096];
  char cmd[768];
  char xlang_bin[4096];
  char cand[4096];
  const char *env_xlang;
  const char *ensuring;
  const char *have;
  const char *rp;
  const char *names[3];
  int i;
  int ax;
  int pos;
  if (!repo_root || !repo_root[0] || !rel_from_repo || !rel_from_repo[0] ||
      !make_target || !make_target[0])
    return 0;
  if (!labi_net_tls_join_repo_rel(abs, 4096, repo_root, rel_from_repo))
    return 0;
  have = asm_link_obj_skip_missing(abs);
  if (have)
    return 1;
  ensuring = link_abi_getenv("XLANG_FORMAL_STD_ENSURE");
  if (ensuring && ensuring[0] && ensuring[0] != '0')
    return 0;
  xlang_bin[0] = '\0';
  env_xlang = link_abi_getenv("XLANG");
  /* wave221: X_OK via path_executable (1 = ok); wave222: env via link_abi_getenv. */
  if (env_xlang && env_xlang[0] && link_abi_path_executable(env_xlang) != 0) {
    rp = link_abi_realpath_cap(env_xlang, xlang_bin);
    if (!rp) {
      if (labi_net_tls_buf_append(xlang_bin, 4096, 0, env_xlang) < 0)
        return 0;
    }
  } else {
    names[0] = "xlang_asm";
    names[1] = "xlang";
    names[2] = "xlang-c";
    for (i = 0; i < 3; i++) {
      pos = 0;
      pos = labi_net_tls_buf_append(cand, 4096, pos, repo_root);
      if (pos < 0)
        continue;
      pos = labi_net_tls_buf_append(cand, 4096, pos, "/compiler/");
      if (pos < 0)
        continue;
      pos = labi_net_tls_buf_append(cand, 4096, pos, names[i]);
      if (pos < 0)
        continue;
      ax = link_abi_path_executable(cand);
      if (ax == 0)
        continue;
      rp = link_abi_realpath_cap(cand, xlang_bin);
      if (!rp) {
        if (labi_net_tls_buf_append(xlang_bin, 4096, 0, cand) < 0)
          return 0;
      }
      break;
    }
  }
  if (!xlang_bin[0])
    return 0;
  if (!labi_formal_std_build_make_cmd(cmd, 768, xlang_bin, repo_root, make_target))
    return 0;
  (void)link_abi_system(cmd); /* wave224 G.7 */
  return asm_link_obj_skip_missing(abs) ? 1 : 0;
}

/* G.7 single queue monofile companion body (cold twin ≡ .x). */
void labi_std_append_queue_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, void *flags) {
  const char *include_root;
  int have_sq = 0;
  if (!link_argv0 || !argv || !la)
    return;
  include_root = xlang_repo_root_from_argv0(link_argv0);
  if (include_root && include_root[0]) {
    (void)xlang_ensure_formal_std_make_o(include_root, "std/sync/sync.o", "../std/sync/sync.o");
    (void)xlang_ensure_formal_std_make_o(include_root, "std/atomic/atomic.o", "../std/atomic/atomic.o");
  }
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/sync/sync.o", lib_roots, n_lib_roots,
                                 bank, argv, la, max_la, &have_sq);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/atomic/atomic.o", lib_roots, n_lib_roots,
                                 bank, argv, la, max_la, NULL);
  (void)xlang_ensure_runtime_queue_contention_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_queue_contention.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  (void)xlang_ensure_runtime_process_argv_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_process_argv.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  if (have_sq) {
    int *f;
    if (flags) {
      f = (int *)flags;
      f[3] = 1;
    }
    (void)xlang_ensure_runtime_sync_lock_diag_tls_o(link_argv0);
    (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_sync_lock_diag_tls.o",
                                   lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    (void)xlang_ensure_runtime_sync_os_o(link_argv0);
    (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_sync_os.o",
                                   lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  }
  (void)xlang_ensure_runtime_atomic_glue_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_atomic_glue.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
}

/* G.7 single test monofile companion body (cold twin ≡ .x).
 * PLATFORM: SHARED — defined here so seed-phase1 runtime_link_abi.o has the T.
 * Do not call L8c labi_od_push_test_monofile_companions from this TU. */
void labi_std_append_test_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la) {
  if (!link_argv0 || !argv || !la)
    return;
  (void)xlang_ensure_runtime_test_fn_invoke_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_test_fn_invoke.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  (void)xlang_ensure_runtime_env_os_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_env_os.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  (void)xlang_ensure_runtime_time_os_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "compiler/runtime_time_os.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
}

/* wave191: labi_std_append_formal_ensure_for_rel pure orch (cold twin ≡ .x).
 * Cap residual: repo_root + ensure_runtime_* + path; peer formal_std_make + push_obj.
 * PLATFORM: SHARED — append_std OP_STD formal ensure+companions.
 */
int labi_std_rel_is_std_or_core(const char *rel) {
  if (!rel || !rel[0])
    return 0;
  if (rel[0] == 's' && rel[1] == 't' && rel[2] == 'd' && rel[3] == '/')
    return 1;
  if (rel[0] == 'c' && rel[1] == 'o' && rel[2] == 'r' && rel[3] == 'e' && rel[4] == '/')
    return 1;
  return 0;
}

void labi_std_append_formal_ensure_for_rel(const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  const char *include_root;
  char make_tgt[4096];
  int pos;
  if (!link_argv0 || !rel || !rel[0])
    return;
  if (!labi_std_rel_is_std_or_core(rel))
    return;
  include_root = xlang_repo_root_from_argv0(link_argv0);
  if (!include_root || !include_root[0])
    return;
  pos = 0;
  pos = labi_net_tls_buf_append(make_tgt, 4096, pos, "../");
  if (pos < 0)
    return;
  pos = labi_net_tls_buf_append(make_tgt, 4096, pos, rel);
  if (pos < 0)
    return;
  (void)xlang_ensure_formal_std_make_o(include_root, rel, make_tgt);
  /* PLATFORM: SHARED — vec/set/map whitelist OR probe the just-ensured formal
   * .o (http.o U std_heap_*). User.o typically only U std_http_*; Darwin ld
   * hard-fails if heap.o is not ensured+pushed after L4 wipe. */
  {
    char abs_rel[4096];
    int need_heap_mem = (strcmp(rel, "std/vec/vec.o") == 0
        || strcmp(rel, "std/set/set.o") == 0
        || strcmp(rel, "std/map/map.o") == 0);
    if (!need_heap_mem && labi_net_tls_join_repo_rel(abs_rel, 4096, include_root, rel)
        && link_abi_user_o_needs_std_heap_api(abs_rel))
      need_heap_mem = 1;
    if (need_heap_mem) {
      (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
      (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
      if (argv && la) {
        (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/heap/heap.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
        (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "core/mem/mem.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
    }
  }
  if (strcmp(rel, "std/env/env.o") == 0) {
    if (xlang_ensure_runtime_env_os_o(link_argv0) == 0 && argv && la) {
      (void)link_abi_asm_ld_push_obj(xlang_runtime_env_os_o_path(link_argv0), link_argv0,
                                     "compiler/runtime_env_os.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      /* PLATFORM: SHARED — env.o U process_xlang_*; mirror .x process_argv companion. */
      labi_std_append_process_argv_if(1, link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
    }
  }
  if (strcmp(rel, "std/random/random.o") == 0) {
    if (xlang_ensure_runtime_random_fill_o(link_argv0) == 0 && argv && la) {
      (void)link_abi_asm_ld_push_obj(xlang_runtime_random_fill_o_path(link_argv0), link_argv0,
                                     "compiler/runtime_random_fill.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
    }
  }
  if (strcmp(rel, "std/time/time.o") == 0) {
    if (xlang_ensure_runtime_time_os_o(link_argv0) == 0 && argv && la) {
      (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                     "compiler/runtime_time_os.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
    }
  }
  /* PLATFORM: SHARED — formal datetime.o U time_now_wall_*_c / time_wall_local_offset_min_c
   * (datetime.x now_utc / local_offset) and std_time_sleep_ns / duration_ns (mod.x).
   * User.o for datetime_iana only U std_datetime_timezone_iana so fk0 time needles miss.
   * Companion ≡ time.o → time_os. G.7 complete ensure_for_rel; no second group. */
  if (strcmp(rel, "std/datetime/datetime.o") == 0) {
    (void)xlang_ensure_formal_std_make_o(include_root, "std/time/time.o", "../std/time/time.o");
    if (argv && la) {
      (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/time/time.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      if (xlang_ensure_runtime_time_os_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_time_os.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
    }
  }
  /* PLATFORM: SHARED — formal fs.o U error/context (+ atomic/time_os via context).
   * User needles only std_fs_*; fk0 error/context miss. G.7 ≡ net companions + C need_context. */
  if (strcmp(rel, "std/fs/fs.o") == 0) {
    (void)xlang_ensure_formal_std_make_o(include_root, "std/error/error.o", "../std/error/error.o");
    (void)xlang_ensure_formal_std_make_o(include_root, "std/context/context.o", "../std/context/context.o");
    if (argv && la) {
      (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/error/error.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/context/context.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      if (xlang_ensure_runtime_atomic_glue_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_atomic_glue_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
      if (xlang_ensure_runtime_time_os_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_time_os.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
    }
  }
  /* PLATFORM: SHARED — pure-asm run-http companion ≡ fs/net error/context */
  if (strcmp(rel, "std/http/http.o") == 0) {
    (void)xlang_ensure_formal_std_make_o(include_root, "std/error/error.o", "../std/error/error.o");
    (void)xlang_ensure_formal_std_make_o(include_root, "std/context/context.o", "../std/context/context.o");
    if (argv && la) {
      (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/error/error.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      (void)link_abi_asm_ld_push_obj(NULL, link_argv0, "std/context/context.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
      if (xlang_ensure_runtime_atomic_glue_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_atomic_glue_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
      if (xlang_ensure_runtime_time_os_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_time_os.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
    }
  }
  /* PLATFORM: SHARED — queue.o monofile companions (G.7 single helper). */
  if (strcmp(rel, "std/queue/queue.o") == 0)
    labi_std_append_queue_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  /* PLATFORM: SHARED — test.o monofile companions (G.7 single helper in this TU). */
  if (strcmp(rel, "std/test/test.o") == 0)
    labi_std_append_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
  /* PLATFORM: SHARED — direct OP_STD context.o (user U std_context_* / STD-091).
   * context.o U atomic_*_i32_c + time_now_monotonic_ns_c. G.7 ≡ C need_context. */
  if (strcmp(rel, "std/context/context.o") == 0) {
    if (argv && la) {
      if (xlang_ensure_runtime_atomic_glue_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_atomic_glue_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
      if (xlang_ensure_runtime_time_os_o(link_argv0) == 0) {
        (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                       "compiler/runtime_time_os.o", lib_roots, n_lib_roots,
                                       bank, argv, la, max_la, NULL);
      }
    }
  }
  (void)lib_roots;
  (void)n_lib_roots;
  (void)bank;
  (void)max_la;
}

/* wave192: labi_std_append_glue_for_op pure orch (cold twin ≡ .x).
 * Cap residual ensure_runtime_*_glue + peer path + push_obj.
 * PLATFORM: SHARED — append_std OP_GLUE_* plan leaves (10..20).
 */
static void labi_std_glue_push_if(int have, int er, const char *primary, const char *link_argv0,
    const char *glue_rel, const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  if (!have || er != 0 || !argv || !la)
    return;
  (void)link_abi_asm_ld_push_obj(primary, link_argv0, glue_rel, lib_roots, n_lib_roots,
                                 bank, argv, la, max_la, NULL);
}

void labi_std_append_glue_for_op(int op, int have, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  const char *use_rel;
  int rel_ok;
  if (!link_argv0)
    return;
  /* ≡ push_glue_after_std: have gate before any ensure. */
  if (!have)
    return;
  use_rel = rel;
  rel_ok = (rel && rel[0]) ? 1 : 0;
  if (op == 10) { /* THREAD */
    if (!rel_ok)
      use_rel = "compiler/runtime_thread_glue.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_thread_glue_o(link_argv0),
                          xlang_runtime_thread_glue_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 11) { /* SYNC_PAIR */
    labi_std_glue_push_if(1, xlang_ensure_runtime_sync_lock_diag_tls_o(link_argv0),
                          xlang_runtime_sync_lock_diag_tls_o_path(link_argv0), link_argv0,
                          "compiler/runtime_sync_lock_diag_tls.o",
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    labi_std_glue_push_if(1, xlang_ensure_runtime_sync_os_o(link_argv0),
                          xlang_runtime_sync_os_o_path(link_argv0), link_argv0,
                          "compiler/runtime_sync_os.o",
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 12) { /* CRYPTO_PAIR */
    labi_std_glue_push_if(1, xlang_ensure_runtime_ed25519_ref10_glue_o(link_argv0),
                          xlang_runtime_ed25519_ref10_glue_o_path(link_argv0), link_argv0,
                          "compiler/runtime_ed25519_ref10_glue.o",
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    labi_std_glue_push_if(1, xlang_ensure_runtime_crypto_inc_glue_o(link_argv0),
                          xlang_runtime_crypto_inc_glue_o_path(link_argv0), link_argv0,
                          "compiler/runtime_crypto_inc_glue.o",
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 13) { /* LOG */
    if (!rel_ok)
      use_rel = "compiler/runtime_log_os.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_log_os_o(link_argv0),
                          xlang_runtime_log_os_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 14) { /* ATOMIC */
    if (!rel_ok)
      use_rel = "compiler/runtime_atomic_glue.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_atomic_glue_o(link_argv0),
                          xlang_runtime_atomic_glue_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 15) { /* CHANNEL */
    if (!rel_ok)
      use_rel = "compiler/runtime_channel_glue.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_channel_glue_o(link_argv0),
                          xlang_runtime_channel_glue_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 16) { /* BACKTRACE */
    if (!rel_ok)
      use_rel = "compiler/runtime_backtrace_platform.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_backtrace_platform_o(link_argv0),
                          xlang_runtime_backtrace_platform_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 17) { /* MATH */
    if (!rel_ok)
      use_rel = "compiler/runtime_math_libm.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_math_libm_o(link_argv0),
                          xlang_runtime_math_libm_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 18) { /* SQLITE */
    if (!rel_ok)
      use_rel = "compiler/runtime_sqlite_glue.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_sqlite_glue_o(link_argv0),
                          xlang_runtime_sqlite_glue_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 19) { /* DYNLIB */
    if (!rel_ok)
      use_rel = "compiler/runtime_dynlib_os.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_dynlib_os_o(link_argv0),
                          xlang_runtime_dynlib_os_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  if (op == 20) { /* HTTP */
    if (!rel_ok)
      use_rel = "compiler/runtime_http_glue.o";
    labi_std_glue_push_if(1, xlang_ensure_runtime_http_glue_o(link_argv0),
                          xlang_runtime_http_glue_o_path(link_argv0), link_argv0, use_rel,
                          lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
}

/* wave193: labi_std_append_primary_for_op pure orch (cold twin ≡ .x).
 * Cap residual needs_* + ensure/path + push_obj.
 * PLATFORM: SHARED — append_std IO_STUBS + PRIMARY_* plan leaves (2..6).
 */
void labi_std_append_primary_for_op(int op, const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  const char *use_rel;
  int rel_ok;
  if (!link_argv0)
    return;
  use_rel = rel;
  rel_ok = (rel && rel[0]) ? 1 : 0;
  if (op == 2) { /* IO_STUBS */
    if (!rel_ok)
      use_rel = "compiler/runtime_asm_io_stubs.o";
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_asm_io_stubs_o_path(link_argv0), link_argv0,
                                     use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    return;
  }
  if (op == 3) { /* PRIMARY_PANIC */
    if (!rel_ok)
      use_rel = "compiler/runtime_panic.o";
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_panic_o_path(link_argv0), link_argv0,
                                     use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    /* wave253: companion user-domain face for residual declare-only leaves / Linux .s panic. */
    (void)xlang_ensure_runtime_link_abi_user_env_o(link_argv0);
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_link_abi_user_env_o_path(link_argv0), link_argv0,
                                     "compiler/runtime_link_abi_user_env.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
    return;
  }
  if (op == 4) { /* PRIMARY_TIME_OS */
    if (!labi_user_needs_runtime_time_os(user_o))
      return;
    if (!rel_ok)
      use_rel = "compiler/runtime_time_os.o";
    (void)xlang_ensure_runtime_time_os_o(link_argv0);
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                     use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    return;
  }
  if (op == 5) { /* PRIMARY_RANDOM_FILL */
    if (!labi_user_needs_runtime_random_fill(user_o))
      return;
    if (!rel_ok)
      use_rel = "compiler/runtime_random_fill.o";
    (void)xlang_ensure_runtime_random_fill_o(link_argv0);
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_random_fill_o_path(link_argv0), link_argv0,
                                     use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    return;
  }
  if (op == 6) { /* PRIMARY_ENV_OS */
    if (!labi_user_needs_runtime_env_os(user_o))
      return;
    if (!rel_ok)
      use_rel = "compiler/runtime_env_os.o";
    (void)xlang_ensure_runtime_env_os_o(link_argv0);
    if (argv && la)
      (void)link_abi_asm_ld_push_obj(xlang_runtime_env_os_o_path(link_argv0), link_argv0,
                                     use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    return;
  }
}

/* wave193: labi_std_append_process_argv_if pure orch (cold twin ≡ .x).
 * Cap residual ensure_runtime_process_argv + path + push_obj.
 * PLATFORM: SHARED — complement after plan loop; never dual-link process.o.
 */
void labi_std_append_process_argv_if(int need, const char *link_argv0,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  if (!need || !link_argv0 || !argv || !la)
    return;
  (void)xlang_ensure_runtime_process_argv_o(link_argv0);
  (void)link_abi_asm_ld_push_obj(xlang_runtime_process_argv_o_path(link_argv0), link_argv0,
                                 "compiler/runtime_process_argv.o",
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
}

/* wave194: labi_std_append_task_special pure orch (cold twin ≡ .x).
 * Cap residual skip/path + formal ensure; peer needs_std_task / scheduler / push_stable.
 * PLATFORM: SHARED — append_std TASK_SPECIAL (task + scheduler + scheduler_glue).
 */
void labi_std_append_task_special(const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la) {
  const char *task_rel;
  const char *p;
  const char *relp;
  const char *sched;
  const char *rsg;
  const char *include_root;
  char make_tgt[4096];
  int pos;
  if (user_o && user_o[0] && !labi_user_needs_std_task(user_o))
    return;
  if (!link_argv0 || !la || *la >= max_la - 1)
    return;
  task_rel = (rel && rel[0]) ? rel : "std/task/task.o";
  if (user_o && user_o[0]) {
    include_root = xlang_repo_root_from_argv0(link_argv0);
    if (include_root && include_root[0]) {
      pos = 0;
      pos = labi_net_tls_buf_append(make_tgt, 4096, pos, "../");
      if (pos >= 0)
        pos = labi_net_tls_buf_append(make_tgt, 4096, pos, task_rel);
      if (pos >= 0)
        (void)xlang_ensure_formal_std_make_o(include_root, task_rel, make_tgt);
    }
  }
  p = NULL;
  relp = xlang_rel_o_path_from_argv0(link_argv0, task_rel);
  if (relp)
    p = asm_link_obj_skip_missing(relp);
  if (!p && bank)
    p = xlang_asm_ld_try_under_lib_roots(task_rel, lib_roots, n_lib_roots, bank);
  if (!p)
    return;
  link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
  sched = scheduler_o_for_task_link(p, NULL);
  if (!sched) {
    const char *sp = xlang_std_async_scheduler_o_path(link_argv0);
    if (sp)
      sched = asm_link_obj_skip_missing(sp);
  }
  if (!sched && bank)
    sched = xlang_asm_ld_try_under_lib_roots("std/async/scheduler.o", lib_roots, n_lib_roots, bank);
  if (!sched)
    return;
  link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, sched);
  (void)xlang_ensure_runtime_scheduler_glue_o(link_argv0);
  rsg = NULL;
  {
    const char *gp = xlang_runtime_scheduler_glue_o_path(link_argv0);
    if (gp)
      rsg = asm_link_obj_skip_missing(gp);
  }
  if (!rsg && bank)
    rsg = xlang_asm_ld_try_under_lib_roots("compiler/runtime_scheduler_glue.o", lib_roots, n_lib_roots, bank);
  if (rsg)
    link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, rsg);
  (void)n_lib_roots;
}

/* wave195: labi_std_op_std_flag_out + labi_std_append_op_std pure orch (cold twin ≡ .x).
 * local_have[6]: [0]process [1]crypto [2]log [3]atomic [4]backtrace [5]http.
 * flags: ShuAsmLdStdLinkFlags LP64 i32 layout (thread/sync/channel/math/sqlite/elf/dynlib).
 * Cap residual: undef_sym inside fk gate peers; formal ensure shell make Cap residual.
 * PLATFORM: SHARED — append_std OP_STD (flag map + gate + ensure + push).
 */
static int *labi_std_op_std_flag_out(int fk, ShuAsmLdStdLinkFlags *flags, int *local_have) {
  if (local_have) {
    if (fk == 1)
      return &local_have[0];
    if (fk == 4)
      return &local_have[1];
    if (fk == 5)
      return &local_have[2];
    if (fk == 6)
      return &local_have[3];
    if (fk == 8)
      return &local_have[4];
    if (fk == 13)
      return &local_have[5];
  }
  if (flags) {
    if (fk == 2)
      return &flags->have_thread;
    if (fk == 3)
      return &flags->have_sync;
    if (fk == 7)
      return &flags->have_channel;
    if (fk == 9)
      return &flags->have_math;
    if (fk == 10)
      return &flags->have_sqlite;
    if (fk == 11)
      return &flags->have_elf;
    if (fk == 12)
      return &flags->have_dynlib;
  }
  return NULL;
}

void labi_std_append_op_std(const char *link_argv0, const char *user_o, const char *rel, int fk,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags, int *local_have) {
  int *flag_out = labi_std_op_std_flag_out(fk, flags, local_have);
  int user_ok = (user_o && user_o[0]) ? 1 : 0;
  int rel_ok = (rel && rel[0]) ? 1 : 0;
  if (!rel_ok)
    return;
  if (user_ok) {
    if (fk == 0 && !labi_std_fk0_user_needs_rel(user_o, rel))
      return;
    if (fk >= 1 && fk <= 13 && !labi_std_fk_user_needs(user_o, fk))
      return;
  } else if (fk == 0 && !labi_std_fk0_user_needs_rel(user_o, rel)) {
    return;
  }
  if (user_ok)
    labi_std_append_formal_ensure_for_rel(link_argv0, rel, lib_roots, n_lib_roots,
                                         bank, argv, la, max_la);
  (void)link_abi_asm_ld_push_obj(NULL, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la,
                                 flag_out);
}

/* wave196: plan shell pure orch (cold twin ≡ .x).
 * Cap residual: inside leaf peers + plan table L8. PLATFORM: SHARED.
 * Peer pure: labi_std_plan_count / labi_std_plan_step_at (L8).
 */
int labi_std_plan_count(void);
int labi_std_plan_step_at(int i, int *op_out, const char **rel_out, int *flag_kind_out);

static int labi_std_glue_have_for_op(int op, ShuAsmLdStdLinkFlags *flags, int *local_have) {
  if (local_have) {
    if (op == 12) return local_have[1];
    if (op == 13) return local_have[2];
    if (op == 14) return local_have[3];
    if (op == 16) return local_have[4];
    if (op == 20) return local_have[5];
  }
  if (flags) {
    if (op == 10) return flags->have_thread;
    if (op == 11) return flags->have_sync;
    if (op == 15) return flags->have_channel;
    if (op == 17) return flags->have_math;
    if (op == 18) return flags->have_sqlite;
    if (op == 19) return flags->have_dynlib;
  }
  return 0;
}

static int labi_std_need_process_argv(ShuAsmLdStdLinkFlags *flags, int *local_have) {
  int heavy;
  if (!local_have)
    return 0;
  if (local_have[0])
    return 0;
  heavy = (local_have[3] || local_have[2] || local_have[4]
           || (flags && (flags->have_sync || flags->have_thread || flags->have_dynlib
                         || flags->have_channel || flags->have_math || flags->have_elf
                         || flags->have_sqlite)))
          ? 1 : 0;
  return heavy;
}

void xlang_asm_ld_append_std_objs_for_user(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags) {
  int local_have[6];
  int n_steps;
  int si;
  memset(local_have, 0, sizeof local_have);
  if (flags)
    memset(flags, 0, sizeof *flags);
  if (flags)
    flags->have_fs = 1;
  if (flags)
    flags->have_io = 1;
  n_steps = labi_std_plan_count();
  for (si = 0; si < n_steps; si++) {
    int op = 0;
    const char *rel = NULL;
    int fk = 0;
    if (!labi_std_plan_step_at(si, &op, &rel, &fk))
      continue;
    switch (op) {
    case 2: /* LABI_STD_OP_IO_STUBS */
    case 3: /* LABI_STD_OP_PRIMARY_PANIC */
    case 4: /* LABI_STD_OP_PRIMARY_TIME_OS */
    case 5: /* LABI_STD_OP_PRIMARY_RANDOM_FILL */
    case 6: /* LABI_STD_OP_PRIMARY_ENV_OS */
      labi_std_append_primary_for_op(op, link_argv0, user_o, rel,
          lib_roots, n_lib_roots, bank, argv, la, max_la);
      break;
    case 1: /* LABI_STD_OP_STD */
      labi_std_append_op_std(link_argv0, user_o, rel, fk, lib_roots, n_lib_roots,
          bank, argv, la, max_la, flags, local_have);
      break;
    case 10: /* LABI_STD_OP_GLUE_THREAD */
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20: /* LABI_STD_OP_GLUE_HTTP */
      labi_std_append_glue_for_op(op, labi_std_glue_have_for_op(op, flags, local_have),
          link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      break;
    case 30: /* LABI_STD_OP_TASK_SPECIAL */
      labi_std_append_task_special(link_argv0, user_o, rel, lib_roots, n_lib_roots,
          bank, argv, la, max_la);
      break;
    default:
      break;
    }
  }
  labi_std_append_process_argv_if(labi_std_need_process_argv(flags, local_have),
      link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
}

#else
int invoke_cc_argv_push_existing(char *argv[], int *ia, int max_ia, const char *path);
int labi_ld_brew_lib_path_count(void);
const char *labi_ld_brew_lib_path_at(int i);
const char *labi_ld_flag_lz(void);
const char *labi_ld_flag_lzstd(void);
const char *labi_ld_flag_lbrotlienc(void);
const char *labi_ld_flag_lbrotlidec(void);
int labi_ld_compress_flag_count(void);
const char *labi_ld_compress_flag_at(int i);
const char *labi_ld_flag_lm(void);
const char *labi_ld_flag_lsqlite3(void);
const char *labi_ld_flag_pthread(void);
const char *labi_ld_flag_lpthread(void);
const char *labi_ld_flag_ldl(void);
const char *labi_ld_flag_lc(void);
const char *labi_ld_flag_lSystem(void);
const char *labi_ld_flag_lws2_32(void);
const char *labi_ld_flag_lbcrypt(void);
const char *labi_ld_flag_L_hb_openssl(void);
const char *labi_ld_flag_L_hb_mbedtls(void);
const char *labi_ld_flag_lssl(void);
const char *labi_ld_flag_lcrypto(void);
const char *labi_ld_flag_lmbedtls(void);
const char *labi_ld_flag_lmbedx509(void);
const char *labi_ld_flag_lmbedcrypto(void);
const char *labi_net_tls_openssl_marker(void);
const char *labi_net_tls_mbedtls_marker(void);
const char *labi_rel_tls_openssl_o(void);
const char *labi_rel_tls_mbedtls_o(void);
void labi_append_openssl_ld_flags(char *argv[], int *i, int argv_cap);
void labi_append_mbedtls_ld_flags(char *argv[], int *i, int argv_cap);
const char *labi_ld_driver_clang(void);
const char *labi_ld_driver_ld(void);
const char *labi_ld_driver_gcc(void);
const char *labi_ld_driver_cc(void);
const char *labi_ld_mach_entry_main(void);
const char *labi_ld_flag_e(void);
const char *labi_ld_flag_o(void);
int labi_ld_common_tail_flag_count(void);
const char *labi_ld_common_tail_flag_at(int i);
void ld_append_brew_lib_paths(const char **argv, int *la, int max_la);
void asm_ld_append_compress_libs(const char *compress_o, const char *user_o, const char **argv, int *la, int max_la);
void invoke_cc_append_compress_ld(char *argv[], int *i, int argv_cap, const char *compress_o, const char *user_o);
void xlang_asm_ld_append_mach_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, const char **argv, int *la, int max_la, int append_lsystem);
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, int need_pt, const char **argv, int *la, int max_la);
int invoke_cc_append_net_tls_ld(char *argv[], int *i, int argv_cap, const char *net_o, const char *repo_root);
/* wave187: ensure_std_net_o_auto_tls pure orch + helpers (L6). */
int labi_net_tls_buf_append(char *dst, int cap, int pos, const char *src);
int labi_net_tls_build_make_cmd(char *cmd, int cap, const char *repo_root, const char *target);
int labi_net_tls_join_repo_rel(char *path_buf, int cap, const char *repo_root, const char *rel);
void ensure_std_net_o_auto_tls(const char *repo_root);
/* wave188: xlang_ensure_formal_std_make_o pure orch + helper (L6). */
int labi_formal_std_build_make_cmd(char *cmd, int cap, const char *xlang_bin,
                                   const char *repo_root, const char *make_target);
int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo,
                                  const char *make_target);
/* wave191: formal ensure+companions pure orch for append_std OP_STD (L6). */
int labi_std_rel_is_std_or_core(const char *rel);
void labi_std_append_formal_ensure_for_rel(const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave192: OP_GLUE_* pure orch for append_std plan glue leaves (L6). */
void labi_std_append_glue_for_op(int op, int have, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave193: IO_STUBS + PRIMARY_* + process_argv complement pure orch (L6). */
void labi_std_append_primary_for_op(int op, const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
void labi_std_append_process_argv_if(int need, const char *link_argv0,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave194: TASK_SPECIAL pure orch (L6). */
void labi_std_append_task_special(const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave195: OP_STD pure orch (flag map + gate + ensure + push) (L6). */
void labi_std_append_op_std(const char *link_argv0, const char *user_o, const char *rel, int fk,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags, int *local_have);
/* wave196: plan shell pure orch (init+loop+dispatch+process_argv) (L6). */
void xlang_asm_ld_append_std_objs_for_user(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
#endif

int labi_invoke_ld_list_slice_marker(void) {
  return 1;
}