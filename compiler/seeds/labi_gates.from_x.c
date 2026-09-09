/* seeds/labi_gates.from_x.c — G-02f-277/L P2 link_abi L9 thin gates → R2 full
 * Logic source: src/runtime/labi_gates.x（真迁 thin shell；*u8 不透明透传）
 * Hybrid: XLANG_LABI_GATES_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供（6 thin gates + count）。
 * Cap residual：*_impl 主体仍在 mega runtime_link_abi.from_x.c rest。
 * FROM_X 下本文件仅前向声明 + slice marker（冷启动 seed 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C thin 体。
 *
 */
#include "runtime_link_abi.h"

/* _impl / body provided by runtime_link_abi.from_x.c rest when hybrid. */
const char *xlang_asm_ld_bank_push_impl(ShuAsmLdPathBank *b, const char *path);
int xlang_invoke_cc_impl(const char **c_paths, int n, const char *out_path, const char *target,
    const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o,
    const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o,
    const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o,
    const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o,
    const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o,
    const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o,
    const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o,
    const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o,
    const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o,
    const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o,
    const char *cli_o, const char *security_o, const char *config_o, const char *cache_o,
    const char *trace_o, const char *task_o, const char *schema_o, const char *test_o,
    const char *include_root, const char *async_scheduler_o);
void xlang_asm_ld_append_mach_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, const char **argv, int *la, int max_la, int append_lsystem);
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, int need_pt, const char **argv, int *la, int max_la);
void xlang_append_linux_link_harden_impl(char *argv[], int *la, int cap);
int xlang_invoke_ld_for_exe_impl(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots);

#ifndef XLANG_LABI_GATES_FROM_X

const char *xlang_asm_ld_bank_push(ShuAsmLdPathBank *b, const char *path) {
  if (b == NULL)
    return NULL;
  if (path == NULL)
    return NULL;
  if (path[0] == 0)
    return NULL;
  return xlang_asm_ld_bank_push_impl(b, path);
}

/* Stage 12.2.3: early host-cc gate (G.7 ≡ labi_invoke_cc_list / .x). */
int invoke_cc_host_cc_spawn_gate(void);

int xlang_invoke_cc(const char **c_paths, int n, const char *out_path, const char *target,
    const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o,
    const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o,
    const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o,
    const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o,
    const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o,
    const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o,
    const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o,
    const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o,
    const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o,
    const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o,
    const char *cli_o, const char *security_o, const char *config_o, const char *cache_o,
    const char *trace_o, const char *task_o, const char *schema_o, const char *test_o,
    const char *include_root, const char *async_scheduler_o) {
  if (c_paths == NULL)
    return -1;
  if (out_path == NULL)
    return -1;
  /* Early deny: skip heavy impl ensure/argv when host-cc is not opt-in. */
  if (!invoke_cc_host_cc_spawn_gate())
    return -1;
  return xlang_invoke_cc_impl(c_paths, n, out_path, target, opt_level, use_lto, io_o, fs_o, process_o,
      string_o, heap_o, path_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o,
      sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o,
      sort_o, ffi_o, db_o, elf_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o,
      simd_o, context_o, datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o, task_o,
      schema_o, test_o, include_root, async_scheduler_o);
}

void xlang_asm_ld_append_mach_tail_libs(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, const char **argv, int *la, int max_la, int append_lsystem) {
  if (flags == NULL)
    return;
  if (argv == NULL)
    return;
  if (la == NULL)
    return;
  if (*la < 0)
    return;
  xlang_asm_ld_append_mach_tail_libs_impl(compress_o, user_o, flags, argv, la, max_la, append_lsystem);
}

void xlang_asm_ld_append_unix_gcc_tail_libs(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, int need_pt, const char **argv, int *la, int max_la) {
  if (flags == NULL)
    return;
  if (argv == NULL)
    return;
  if (la == NULL)
    return;
  if (*la < 0)
    return;
  xlang_asm_ld_append_unix_gcc_tail_libs_impl(compress_o, user_o, flags, need_pt, argv, la, max_la);
}

void xlang_append_linux_link_harden(char *argv[], int *la, int cap) {
  if (argv == NULL)
    return;
  if (la == NULL)
    return;
  xlang_append_linux_link_harden_impl(argv, la, cap);
}

int xlang_invoke_ld_for_exe(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots) {
  if (o_path == NULL)
    return -1;
  if (exe_path == NULL)
    return -1;
  return xlang_invoke_ld_for_exe_impl(o_path, exe_path, target, use_macho_o, use_coff_o, link_argv0,
      lib_roots, n_lib_roots);
}

int labi_gates_count(void) {
  return 6;
}

#else
const char *xlang_asm_ld_bank_push(ShuAsmLdPathBank *b, const char *path);
int xlang_invoke_cc(const char **c_paths, int n, const char *out_path, const char *target,
    const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o,
    const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o,
    const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o,
    const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o,
    const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o,
    const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o,
    const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o,
    const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o,
    const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o,
    const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o,
    const char *cli_o, const char *security_o, const char *config_o, const char *cache_o,
    const char *trace_o, const char *task_o, const char *schema_o, const char *test_o,
    const char *include_root, const char *async_scheduler_o);
void xlang_asm_ld_append_mach_tail_libs(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, const char **argv, int *la, int max_la, int append_lsystem);
void xlang_asm_ld_append_unix_gcc_tail_libs(const char *compress_o, const char *user_o,
    const ShuAsmLdStdLinkFlags *flags, int need_pt, const char **argv, int *la, int max_la);
void xlang_append_linux_link_harden(char *argv[], int *la, int cap);
int xlang_invoke_ld_for_exe(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots);
int labi_gates_count(void);
#endif

int labi_gates_slice_marker(void) {
  return 1;
}