/* Generated from src/runtime_link_abi.x (G-02f-34..56/64..70/89/91/92/94 true .x + C tail).
 * G-02f-115 true .x pure helpers.
 * G-02f-112 helper gates.
 * Regen: ./xlang-c -E -L .. src/runtime_link_abi.x > /tmp/labi.c
 *         merge invoke_cc + linux_harden + remaining link gates.
 * .x covers: + xlang_invoke_cc, append_linux_link_harden; link_abi exported set nearly gated.
 * G-02f-89/91/92/94: path/diag/needs + cc_ex/nm/nostdlib helpers gated over _impl.
 */
#include <xlang_weak.h>
#include "win32_compat.h"
#include "runtime_link_abi.h"
#include "runtime_proc_abi.h"
#include "runtime_io_abi.h"
#include "runtime_driver_abi.h"
#include "runtime_abi.h"
#include "diag.h"
#include "runtime_diag_codes.h"
/* Cap residual 9.1.2: Linux path access/stat/fstat/realpath without libc. */
#include <xlang_path_cap.h>
/* Cap residual 9.1.4: Linux fork/execve/wait4/execvp/system without libc. */
#include <xlang_process_cap.h>

/* G-02f-53/65/66: empty C string + path/ld helpers */
const char *xlang_asm_ld_bank_push_impl(ShuAsmLdPathBank *b, const char *path);
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
const char *xlang_asm_ld_effective_link_argv0(const char *link_argv0, char *syn_buf, size_t syn_sz);
int xlang_path_is_nonempty_regular_file_impl(const char *path);
int link_abi_ld_argv_entry_is_obj(const char *s);
int xlang_invoke_ld_for_exe_impl(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots);
void xlang_asm_ld_append_mach_tail_libs_impl(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    const char **argv, int *la, int max_la, int append_lsystem);
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    int need_pt, const char **argv, int *la, int max_la);
/* G-02f-70 invoke_cc + harden */
int xlang_invoke_cc_impl(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o, const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o, const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o, const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o, const char *cli_o, const char *security_o, const char *config_o, const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o, const char *test_o, const char *include_root, const char *async_scheduler_o);
void xlang_append_linux_link_harden_impl(char *argv[], int *la, int cap);
/* G-02f-69 mega link helpers */
int xlang_resolve_compiler_dir(const char *argv0, char *out_dir, size_t out_dir_sz);
int xlang_asm_invoke_ld_platform(const char *o_path, const char *exe_path, const char *target, int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots, int driver_freestanding);
void xlang_asm_ld_append_std_objs(const char *link_argv0, const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
void xlang_asm_ld_append_std_objs_for_user(const char *link_argv0, const char *user_o, const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
void xlang_asm_ld_append_on_demand_user_objs(const char *link_argv0, const char *user_o, const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
/* wave151: CLI extra .o append (path_pure L0 pure orch; Cap residual table+access). */
void xlang_asm_ld_append_user_extra_o_files(const char **argv, int *la, int max_la);
/* wave146: argv dedup used by extra append (mega #ifndef body; proto before first call). */
int link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path);
int link_abi_user_extra_o_count(void);
const char *link_abi_user_extra_o_at(int i);
int link_abi_path_readable(const char *path);
int link_abi_path_readable_impl(const char *path);
/* wave221: X_OK pure thin (labi_path_io) + Cap residual _impl always mega. */
int link_abi_path_executable(const char *path);
int link_abi_path_executable_impl(const char *path);
/* wave222: getenv pure thin (labi_diag_pure) + Cap residual _impl always mega. */
const char *link_abi_getenv(const char *name);
const char *link_abi_getenv_impl(const char *name);
/* wave218/261: realpath pure thin (labi_path_io) + Cap residual _impl always mega.
 * wave261: always-mega residual raw realpath() call sites → this public face (G.7).
 * Host residual realpath stays only in link_abi_realpath_cap_impl (+ freestanding stubs). */
const char *link_abi_realpath_cap(const char *path, char *out);
const char *link_abi_realpath_cap_impl(const char *path, char *out);
int invoke_cc_append_net_tls_ld(char *argv[], int *i, int argv_cap, const char *net_o, const char *repo_root);
void ensure_std_net_o_auto_tls(const char *repo_root);
/* PLATFORM: SHARED — formal std .o after L4 wipe (wave188 pure L6 / cold twin). */
int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo, const char *make_target);
/* wave191: formal ensure+companions pure orch for append_std OP_STD (L6 pure / cold twin). */
int labi_std_rel_is_std_or_core(const char *rel);
void labi_std_append_formal_ensure_for_rel(const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave192: OP_GLUE_* pure orch for append_std plan glue leaves (L6 pure / cold twin). */
void labi_std_append_glue_for_op(int op, int have, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave193: IO_STUBS + PRIMARY_* pure orch + process_argv complement (L6 pure / cold twin). */
void labi_std_append_primary_for_op(int op, const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
void labi_std_append_process_argv_if(int need, const char *link_argv0,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave194: TASK_SPECIAL pure orch (L6 pure / cold twin). */
void labi_std_append_task_special(const char *link_argv0, const char *user_o, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
/* wave195: OP_STD pure orch (fk→flag_out + gate + formal ensure + push; L6 pure / cold twin). */
void labi_std_append_op_std(const char *link_argv0, const char *user_o, const char *rel, int fk,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags, int *local_have);
/* G-02f-68 / wave216: pure thin public (L1) + Cap residual _impl always. */
int xlang_waitpid_retry(pid_t pid, int *status_out);
int xlang_waitpid_retry_impl(pid_t pid, int *status_out);
/* Cap residual always (wave215/255): multi-slot realpath pool body only. */
const char *invoke_cc_argv_resolve_existing_path_impl(const char *path);
int xlang_asm_user_o_has_undef_syms(const char *o_path);
void asm_ld_append_compress_libs(const char *compress_o, const char *user_o, const char **argv, int *la, int max_la);
void invoke_cc_append_compress_ld(char *argv[], int *i, int argv_cap, const char *compress_o, const char *user_o);
/* wave215/255 pure public: null/empty + skip_missing + Cap residual pool. */
const char *invoke_cc_argv_resolve_existing_path(const char *path);
/* wave179: pure orch in L6 (cold twin include / hybrid FROM_X pure .x). */
int invoke_cc_argv_push_existing(char *argv[], int *ia, int max_ia, const char *path);
int xlang_asm_ld_prepare_for_exe_link(const char *link_eff, const char *user_o, int driver_freestanding, int use_macho_o, int use_coff_o);
/* G-02f-67 ensure impls */
int xlang_ensure_freestanding_io_o(const char *argv0, int driver_freestanding);
int xlang_ensure_crt0_user_o(const char *argv0, int driver_freestanding);
int xlang_ensure_runtime_arrow_simd_glue_o(const char *argv0);
int xlang_ensure_runtime_asm_io_stubs_o(const char *argv0);
const char *labi_od_rel_page_mmap(void);
int xlang_ensure_runtime_atomic_glue_o(const char *argv0);
int xlang_ensure_runtime_backtrace_platform_o(const char *argv0);
int xlang_ensure_runtime_channel_glue_o(const char *argv0);
int xlang_ensure_runtime_compress_zlib_glue_o(const char *argv0);
int xlang_ensure_runtime_crypto_inc_glue_o(const char *argv0);
int xlang_ensure_runtime_dynlib_os_o(const char *argv0);
int xlang_ensure_runtime_ed25519_ref10_glue_o(const char *argv0);
int xlang_ensure_runtime_env_os_o(const char *argv0);
int xlang_ensure_runtime_heap_user_o(const char *argv0);
int xlang_link_obj_has_defined_sym(const char *o_path, const char *sym);
int xlang_ensure_runtime_http_glue_o(const char *argv0);
int xlang_ensure_runtime_kv_mmap_glue_o(const char *argv0);
int xlang_ensure_runtime_log_os_o(const char *argv0);
int xlang_ensure_runtime_math_libm_o(const char *argv0);
int xlang_ensure_runtime_net_udp_batch_o(const char *argv0);
int xlang_ensure_runtime_net_workers_o(const char *argv0);
int xlang_ensure_runtime_panic_o(const char *argv0);
int xlang_ensure_runtime_process_argv_o(const char *argv0);
int xlang_ensure_runtime_process_os_glue_o(const char *argv0);
int xlang_ensure_runtime_queue_contention_o(const char *argv0);
int xlang_ensure_runtime_random_fill_o(const char *argv0);
int xlang_ensure_runtime_scheduler_glue_o(const char *argv0);
int xlang_ensure_runtime_sqlite_glue_o(const char *argv0);
int xlang_ensure_runtime_sync_lock_diag_tls_o(const char *argv0);
int xlang_ensure_runtime_sync_os_o(const char *argv0);
int xlang_ensure_runtime_test_fn_invoke_o(const char *argv0);
int xlang_ensure_runtime_thread_glue_o(const char *argv0);
int xlang_ensure_runtime_time_os_o(const char *argv0);
int xlang_ensure_runtime_tls_mbedtls_bio_o(const char *argv0);
/* wave184: pure orch in labi_path_pure L0 (hybrid FROM_X / cold twin include).
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X. PLATFORM: SHARED. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_empty_cstr(void) {
    static char buf[1];
    buf[0] = '\0';
    return buf;
}
#else
const char *xlang_empty_cstr(void);
#endif


#include <errno.h>
#include <limits.h>
#include <stdint.h>
/* Cap residual 9.5.3 slice3b: the FILE/print cluster (.inc wrap writer,
 * debug-env reader, link_only traces) is on the Cap IO/proc faces below.
 * <stdio.h> stays ONLY as the declarer of the popen/pclose/fgets nm-undef
 * scanner (host residual, 9.2 process-pipe domain — its own future slice
 * drops this header). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: link_abi path/cmd format → Cap snprintf */
#include <xlang_io_cap.h>
#include <xlang_proc_cap.h>
/* G.7: single Cap authority for this TU + included labi_* lists (after stdio). */
#undef snprintf
#define snprintf xlang_snprintf
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif
#include <sys/stat.h>
#if defined(__linux__)
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#endif

#if defined(__APPLE__)
#include <fcntl.h>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/mman.h>
#endif
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/** invoke_cc 子进程 realpath 缓冲池：不可共用单块 static，否则多次 push 后 argv 中旧槽指向最后被覆盖的路径。 */
#define INVOKE_CC_ABS_POOL_SZ 80

/**
 * 在字符串 s 中查找最后一个路径分隔符（POSIX '/' 或 Windows '\\')。
 * Windows 上 argv0 / realpath 结果可能含反斜杠，需双分隔符查找；
 * POSIX 上 strchr(s, '\\') 通常为 NULL（文件名极少含反斜杠），行为不变。
 * 返回值：指向最后分隔符的指针，找不到返回 NULL。
 */
/* G-02f-118：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-267 L0 path pure */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
char * xlang_path_last_sep(const char *s) {
    char *p = s ? strrchr(s, '/') : NULL;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    if (s) {
        char *bs = strrchr(s, '\\');
        if (bs && (!p || bs > p))
            p = bs;
    }
#endif
    return p;
}
#else
char *xlang_path_last_sep(const char *s);
#endif





/** 字符串是否包含任意路径分隔符（POSIX '/' 或 Windows '\\')。 */
/* G-02f-118：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-267 L0 path pure */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int xlang_path_has_sep(const char *s) {
    if (!s)
        return 0;
    if (strchr(s, '/'))
        return 1;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    if (strchr(s, '\\'))
        return 1;
#endif
    return 0;
}
#else
int xlang_path_has_sep(const char *s);
#endif





/**
 * 同步执行 cc 编译 .c/.s → .o；POSIX 上 fork+execvp+waitpid，Windows 上 _spawnvp(_P_WAIT,...)。
 * 参数：src 源文件；out_o 输出 .o 路径；inc0/inc1/inc2 三个 -I 包含路径；
 *       from_asm_s != 0 表示源是 .s 汇编，仅传 -c -o out src，不传 -Wall/-Wextra/-I。
 *       extra_flags 可选额外标志数组（NULL 或 NULL-terminated），插在 -I 之后、-c 之前。
 * 返回值：0 成功，非 0 失败（exit code 或 -1）。
 * 设计目的：消除 30+ 处 ensure_runtime_*_o 函数中重复的 fork+execlp+waitpid 三段式，
 *           并让 Windows 宿主走 _spawnvp 同步路径（无 fork）。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_cc_compile_sync_ex(const char *src, const char *out_o,
                                    const char *inc0, const char *inc1, const char *inc2,
                                    int from_asm_s,
                                    const char *const *extra_flags) {
    const char *argv[32];
    int ai = 0;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    argv[ai++] = "gcc";
#else
    argv[ai++] = "cc";
#endif
    /* PLATFORM: MACOS — match macho.x LC_BUILD_VERSION minos 11.0.0 (0x000B0000).
     * Host-cc default SDK stamps LC_BUILD_VERSION minos 26.0; Apple ld then
     * warns when those .o are linked with product-asm objects at 11.0.
     * Applies to .c and .s (from_asm_s) — both get the Mach-O load command from cc.
     * Do not -w swallow; do not raise macho.x minos to 26.0.
     * PLATFORM: LINUX / WINDOWS — no-op (GNU ld / link have no Mach-O minos check). */
#if defined(__APPLE__)
    argv[ai++] = "-mmacosx-version-min=11.0";
#endif
    if (!from_asm_s) {
        argv[ai++] = "-Wall";
        argv[ai++] = "-Wextra";
        argv[ai++] = "-I";
        argv[ai++] = inc0;
        argv[ai++] = "-I";
        argv[ai++] = inc1;
        argv[ai++] = "-I";
        argv[ai++] = inc2;
    }
    if (extra_flags) {
        int i;
        for (i = 0; extra_flags[i] != NULL && ai < 28; i++)
            argv[ai++] = extra_flags[i];
    }
    argv[ai++] = "-c";
    argv[ai++] = "-o";
    argv[ai++] = out_o;
    argv[ai++] = src;
    argv[ai] = NULL;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    {
        intptr_t rc = _spawnvp(_P_WAIT, "gcc", (const char *const *)argv);
        if (rc == -1)
            return -1;
        return (int)rc;
    }
#else
    {
        long pid = xlang_proc_fork();
        if (pid < 0)
            return -1;
        if (pid == 0) {
            (void)xlang_proc_execvp("cc", (char *const *)argv);
            xlang_proc_exit(127);
        }
        {
            int st;
            if (xlang_waitpid_retry((pid_t)pid, &st) != 0)
                return -1;
            if (!WIFEXITED(st) || WEXITSTATUS(st) != 0)
                return -1;
        }
    }
    return 0;
#endif
}




/**
 * xlang_cc_compile_sync 的简化包装：无额外标志。
 * G-02e-17：若 src 以 .inc 结尾，写临时 wrap.c（#include 绝对路径）再 cc，结束后删除 wrap。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_cc_compile_sync(const char *src, const char *out_o,
                                const char *inc0, const char *inc1, const char *inc2,
                                int from_asm_s) {
    size_t n;
    char wrap_c[PATH_MAX];
    int wf_fd;
    int rc;
    if (!src)
        return -1;
    n = strlen(src);
    if (n > 4 && strcmp(src + (n - 4), ".inc") == 0) {
        if ((size_t)snprintf(wrap_c, sizeof wrap_c, "%s.wrap.c", out_o) >= sizeof wrap_c)
            return -1;
        /* Cap residual 9.5.3 slice3b: fd write via xlang_io_open_write (9.5.3
         * authority, O_WRONLY|O_CREAT|O_TRUNC) + xlang_io_write + close
         * (9.1.12). Three exact segments keep the emitted bytes identical to
         * the old fprintf. */
        wf_fd = xlang_io_open_write(wrap_c);
        if (wf_fd < 0)
            return -1;
        {
            static const char wrap_head[] =
                "/* generated by xlang_cc_compile_sync (.inc wrap, G-02e) */\n#include \"";
            (void)xlang_io_write(wf_fd, wrap_head, sizeof wrap_head - 1);
            (void)xlang_io_write(wf_fd, src, n);
            (void)xlang_io_write(wf_fd, "\"\n", 2);
        }
        xlang_proc_close_fd(wf_fd);
        rc = xlang_cc_compile_sync_ex(wrap_c, out_o, inc0, inc1, inc2, from_asm_s, NULL);
        (void)remove(wrap_c);
        return rc;
    }
    return xlang_cc_compile_sync_ex(src, out_o, inc0, inc1, inc2, from_asm_s, NULL);
}

/**
 * wave172 Cap residual: xlang_cc_compile_sync_ex with at most one extra flag string.
 * Pure ensure orch cannot safely build a local NULL-terminated const char** table;
 * this peer packs extra0 into a stack array and calls the authority compile_sync_ex.
 * @param extra0 optional single flag (e.g. "-I/opt/homebrew/opt/mbedtls/include"); NULL → no extra
 * @return 0 success; non-zero failure (same as compile_sync_ex)
 * PLATFORM: SHARED — G.7 complete compile_sync family; used by ensure_runtime_tls_mbedtls_bio pure.
 */
int xlang_cc_compile_sync_one_extra(const char *src, const char *out_o,
                                   const char *inc0, const char *inc1, const char *inc2,
                                   int from_asm_s, const char *extra0) {
    const char *extra_flags[2];
    if (extra0 == NULL)
        return xlang_cc_compile_sync_ex(src, out_o, inc0, inc1, inc2, from_asm_s, NULL);
    extra_flags[0] = extra0;
    extra_flags[1] = NULL;
    return xlang_cc_compile_sync_ex(src, out_o, inc0, inc1, inc2, from_asm_s, extra_flags);
}




/**
 * Cap residual (wave219 + 9.1.4): synchronous spawn body.
 * Pure orch (labi_diag_pure L1) owns public thin null/empty gates; _impl is always mega.
 * Linux: fork+execvp+wait4 via xlang_process_cap (no libc fork/execvp/waitpid).
 * Other POSIX: fork+execvp+waitpid. Windows: _spawnvp(_P_WAIT).
 * G.7 single spawn authority for invoke_cc / ld / strip (no second fork path).
 * PLATFORM: LINUX Cap residual / POSIX fork / WINDOWS _spawnvp.
 */
int xlang_spawn_sync_impl(const char *prog, const char *const *argv) {
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    {
        intptr_t rc = _spawnvp(_P_WAIT, prog, (const char *const *)argv);
        if (rc == -1)
            return -1;
        return (int)rc;
    }
#else
    {
        long pid = xlang_proc_fork();
        if (pid < 0)
            return -1;
        if (pid == 0) {
            (void)xlang_proc_execvp(prog, (char *const *)argv);
            xlang_proc_exit(127);
        }
        {
            int st;
            if (xlang_waitpid_retry((pid_t)pid, &st) != 0)
                return -1;
            if (!WIFEXITED(st) || WEXITSTATUS(st) != 0)
                return -1;
        }
    }
    return 0;
#endif
}

/* wave219: xlang_spawn_sync pure orch lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Pure: null/empty prog + null argv gates; Cap residual xlang_spawn_sync_impl always mega.
 * Why: hybrid still had spawn_sync body always mega C (fork/exec/wait or _spawnvp).
 * PLATFORM: SHARED orch / POSIX fork residual / WINDOWS _spawnvp residual. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
int xlang_spawn_sync(const char *prog, const char *const *argv) {
    if (!prog || !prog[0] || !argv)
        return -1;
    return xlang_spawn_sync_impl(prog, argv);
}
#else
int xlang_spawn_sync(const char *prog, const char *const *argv);
#endif

/**
 * Cap residual (wave220): best-effort `strip -x out_path` body (argv pack + spawn).
 * Pure orch (labi_diag_pure L1) owns public thin null/empty gates; _impl is always mega.
 * Pure orch invoke_cc_maybe_strip_out owns opt_level / Windows skip gates.
 * Must use strip -x (local symbols only): bare strip on Darwin drops _main globals
 * → nm/otool false red. G.7 single strip authority for maybe_strip / invoke_cc.
 * PLATFORM: SHARED residual / POSIX strip via public xlang_spawn_sync / WINDOWS _spawnvp.
 */
void invoke_cc_strip_out_x_impl(const char *out_path) {
    const char *sargv[4];
    if (!out_path || !out_path[0])
        return;
    sargv[0] = "strip";
    sargv[1] = "-x";
    sargv[2] = out_path;
    sargv[3] = NULL;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    (void)_spawnvp(_P_WAIT, "strip", (const char *const *)sargv);
#else
    (void)xlang_spawn_sync("strip", sargv);
#endif
}

/* wave220: invoke_cc_strip_out_x pure orch lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Pure: null/empty out_path gates; Cap residual invoke_cc_strip_out_x_impl always mega.
 * Why: hybrid still had strip_out_x body always mega C (gates+argv pack+spawn).
 * PLATFORM: SHARED orch / POSIX strip residual / WINDOWS _spawnvp residual. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void invoke_cc_strip_out_x(const char *out_path) {
    if (!out_path || !out_path[0])
        return;
    invoke_cc_strip_out_x_impl(out_path);
}
#else
void invoke_cc_strip_out_x(const char *out_path);
#endif

/**
 * Cap residual (wave222 + 9.1.1): host env lookup → value pointer or NULL.
 * Pure orch (wave222 labi_diag_pure L1) owns null/empty name gates; _impl is always mega.
 * PLATFORM: SHARED Cap (9.1.1) — unified xlang_environ_getenv.
 * Product ensure orch (formal_std XLANG / XLANG_FORMAL_STD_ENSURE; ensure_std_net XLANG_NET_TLS).
 */
#include <xlang_environ_cap.h>
const char *link_abi_getenv_impl(const char *name) {
    return xlang_environ_getenv(name);
}

/* wave222: link_abi_getenv pure orch lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Pure: null/empty name gates; Cap residual link_abi_getenv_impl (getenv) always mega.
 * Why: hybrid still had formal_std / ensure_std_net raw getenv under product ensure.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
const char *link_abi_getenv(const char *name) {
    if (!name || !name[0])
        return NULL;
    return link_abi_getenv_impl(name);
}
#else
const char *link_abi_getenv(const char *name);
#endif

/**
 * Cap residual (wave224 + 9.1.4): host system(cmd) → shell status or -1.
 * Pure orch (wave224 labi_diag_pure L1) owns null/empty cmd gates; _impl is always mega.
 * Linux/Darwin: fork+execve(/bin/sh -c)+wait4 (no libc system).
 * PLATFORM: SHARED Cap residual (POSIX fork+execve+waitpid; Windows system).
 * Product ensure orch (ensure_std_net net-o-*; formal_std XLANG make).
 */
int link_abi_system_impl(const char *cmd) {
    if (!cmd || !cmd[0])
        return -1;
#if !defined(_WIN32) && !defined(_WIN64)
    {
        char *argv[4];
        long pid;
        int st;
        argv[0] = (char *)"sh";
        argv[1] = (char *)"-c";
        argv[2] = (char *)cmd;
        argv[3] = NULL;
        pid = xlang_proc_fork();
        if (pid < 0)
            return -1;
        if (pid == 0) {
            (void)xlang_proc_execve("/bin/sh", argv, environ);
            xlang_proc_exit(127);
        }
        if (xlang_waitpid_retry((pid_t)pid, &st) != 0)
            return -1;
        if (!WIFEXITED(st))
            return -1;
        return (int)WEXITSTATUS(st);
    }
#else
    return system(cmd);
#endif
}

/* wave224: link_abi_system pure orch lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Pure: null/empty cmd gates; Cap residual link_abi_system_impl (system) always mega.
 * Why: hybrid still had formal_std / ensure_std_net raw system under product ensure.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
int link_abi_system(const char *cmd) {
    if (!cmd || !cmd[0])
        return -1;
    return link_abi_system_impl(cmd);
}
#else
int link_abi_system(const char *cmd);
#endif


/* G-02f-124：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-268 L1 diag pure：code_for_kind 真迁在 L1 leaf；rest 非 hybrid 自带 */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
const char * link_diag_code_for_kind(const char *kind) {
    if (!kind)
        return XLANG_DIAG_CODE_PROCESS_PRC001;
    if (strcmp(kind, "build error") == 0)
        return XLANG_DIAG_CODE_BUILD_BLD001;
    if (strcmp(kind, "process error") == 0)
        return XLANG_DIAG_CODE_PROCESS_PRC001;
    return NULL;
}
#else
const char * link_diag_code_for_kind(const char *kind);
#endif

/* Cap residual (always _impl, wave217): POSIX wait status decode.
 * Pure orch (labi_diag_pure L1) owns public thin; _impl is always mega.
 * PLATFORM: POSIX (macOS + Linux). Windows hybrid uses win32_compat wait macros. */
int link_diag_wait_is_signaled_impl(int status) {
    return WIFSIGNALED(status) ? 1 : 0;
}
int link_diag_wait_code_impl(int status) {
    if (WIFSIGNALED(status))
        return (int)WTERMSIG(status);
    if (WIFEXITED(status))
        return (int)WEXITSTATUS(status);
    return -1;
}

/* wave217: public pure thin lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Cap residual: wait_is_signaled_impl / wait_code_impl (WIF* always mega).
 * PLATFORM: SHARED orch / POSIX wait residual. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
int link_diag_wait_is_signaled(int status) {
    return link_diag_wait_is_signaled_impl(status);
}
int link_diag_wait_code(int status) {
    return link_diag_wait_code_impl(status);
}
#else
int link_diag_wait_is_signaled(int status);
int link_diag_wait_code(int status);
#endif

/* G-02f-165 / wave112：tool_status pure orch in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X. Cap residual wait decode
 * stays always-linked. PLATFORM: SHARED. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_tool_status(const char *tool, int status) {
    if (!tool)
        tool = "tool";
    if (WIFSIGNALED(status)) {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "%s failed (signal %d)", tool, WTERMSIG(status));
    } else {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "%s failed (exit %d)", tool, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    }
}
#else
void link_diag_tool_status(const char *tool, int status);
#endif


/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* R2 labi_diag_pure：hybrid FROM_X 下公共+消息体由 L1 .x 提供；冷启动仍保留 _impl */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_runtime_obj_resolve_fail_impl(const char *obj_name, const char *hint) {
    if (!obj_name)
        obj_name = "runtime object";
    if (hint && hint[0] != '\0') {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "cannot resolve compiler directory to build %s (%s)",
                               obj_name, hint);
    } else {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "cannot resolve compiler directory to build %s",
                               obj_name);
    }
}
void link_diag_runtime_obj_resolve_fail(const char *obj_name, const char *hint) {
    link_diag_runtime_obj_resolve_fail_impl(obj_name, hint);
}
#else
void link_diag_runtime_obj_resolve_fail(const char *obj_name, const char *hint);
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_runtime_source_missing_impl(const char *obj_name, const char *source_path) {
    if (!obj_name)
        obj_name = "runtime object";
    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                           "%s source not found at %s",
                           obj_name, source_path ? source_path : "?");
}
void link_diag_runtime_source_missing(const char *obj_name, const char *source_path) {
    link_diag_runtime_source_missing_impl(obj_name, source_path);
}
#else
void link_diag_runtime_source_missing(const char *obj_name, const char *source_path);
#endif



/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_runtime_source_missing_under_impl(const char *obj_name, const char *base_dir,
                                                   const char *suffix) {
    if (!obj_name)
        obj_name = "runtime object";
    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                           "%s source not found under %s%s",
                           obj_name, base_dir ? base_dir : "?", suffix ? suffix : "");
}
void link_diag_runtime_source_missing_under(const char *obj_name, const char *base_dir,
                                                   const char *suffix) {
    link_diag_runtime_source_missing_under_impl(obj_name, base_dir, suffix);
}
#else
void link_diag_runtime_source_missing_under(const char *obj_name, const char *base_dir, const char *suffix);
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_runtime_obj_missing_impl(const char *obj_name, const char *out_o) {
    if (!obj_name)
        obj_name = "runtime object";
    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                           "%s missing after cc -c (expected near %s)",
                           obj_name, out_o ? out_o : "?");
}
void link_diag_runtime_obj_missing(const char *obj_name, const char *out_o) {
    link_diag_runtime_obj_missing_impl(obj_name, out_o);
}
#else
void link_diag_runtime_obj_missing(const char *obj_name, const char *out_o);
#endif



/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */


/* wave112：obj_build_status pure orch in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef. Cap residual wait decode always-linked. PLATFORM: SHARED. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_runtime_obj_build_status(const char *obj_name, int status) {
    if (!obj_name)
        obj_name = "runtime object";
    if (WIFSIGNALED(status)) {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "failed to build %s (signal %d)",
                               obj_name, WTERMSIG(status));
    } else {
        diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                               "failed to build %s (exit %d)",
                               obj_name, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    }
}
#else
void link_diag_runtime_obj_build_status(const char *obj_name, int status);
#endif
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */




/* Cap residual (always _impl, wave217): errno capture + strerror.
 * Pure orch (labi_diag_pure L1) owns public thin; _impl is always mega.
 * Message orch is pure L1 (wave113). PLATFORM: SHARED — libc errno/strerror. */
const char *link_diag_strerror_current_impl(void) {
    int saved_errno = errno;
    const char *err = strerror(saved_errno);
    return err ? err : "unknown error";
}

/* wave217: public pure thin lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Cap residual: link_diag_strerror_current_impl (errno+strerror always mega).
 * PLATFORM: SHARED orch / libc strerror residual. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
const char *link_diag_strerror_current(void) {
    return link_diag_strerror_current_impl();
}
#else
const char *link_diag_strerror_current(void);
#endif

/* G-02f-165 / wave113：link_diag_errno / _path pure orch in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X. Cap residual strerror stays
 * always-linked. PLATFORM: SHARED. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_errno(const char *kind, const char *op) {
    const char *err = link_diag_strerror_current();
    const char *resolved_kind = kind ? kind : "process error";
    const char *resolved_op = (op && op[0]) ? op : "system call";
    const char *code = link_diag_code_for_kind(resolved_kind);
    if (code) {
        diag_reportf_with_code(NULL, 0, 0, resolved_kind, code, NULL,
                               "%s failed: %s",
                               resolved_op,
                               err ? err : "unknown error");
    } else {
        diag_reportf(NULL, 0, 0, resolved_kind, NULL,
                     "%s failed: %s",
                     resolved_op,
                     err ? err : "unknown error");
    }
}

void link_diag_errno_path(const char *kind, const char *op, const char *path) {
    const char *err;
    const char *resolved_kind;
    const char *resolved_op;
    const char *code;
    if (!path || path[0] == '\0') {
        link_diag_errno(kind, op);
        return;
    }
    err = link_diag_strerror_current();
    resolved_kind = kind ? kind : "process error";
    resolved_op = (op && op[0]) ? op : "system call";
    code = link_diag_code_for_kind(resolved_kind);
    if (code) {
        diag_reportf_with_code(NULL, 0, 0, resolved_kind, code, NULL,
                               "%s failed for '%s': %s",
                               resolved_op,
                               path,
                               err ? err : "unknown error");
    } else {
        diag_reportf(NULL, 0, 0, resolved_kind, NULL,
                     "%s failed for '%s': %s",
                     resolved_op,
                     path,
                     err ? err : "unknown error");
    }
}
#else
void link_diag_errno(const char *kind, const char *op);
void link_diag_errno_path(const char *kind, const char *op, const char *path);
#endif







#if defined(__GNUC__) || defined(__clang__)
__attribute__((unused))
#endif
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* R2：freestanding_missing 消息体 hybrid 由 L1 .x；冷启动 _impl */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_freestanding_missing_impl(const char *obj_name, const char *symbol_name) {
    if (symbol_name && symbol_name[0]) {
        diag_reportf_with_code(NULL, 0, 0, "link error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                     "freestanding link missing %s (user references %s)",
                     obj_name ? obj_name : "runtime object",
                     symbol_name);
        return;
    }
    diag_reportf_with_code(NULL, 0, 0, "link error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                 "freestanding link missing %s",
                 obj_name ? obj_name : "runtime object");
}
void link_diag_freestanding_missing(const char *obj_name, const char *symbol_name) {
    link_diag_freestanding_missing_impl(obj_name, symbol_name);
}
#else
void link_diag_freestanding_missing(const char *obj_name, const char *symbol_name);
#endif



/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* R2：freestanding_unsupported 消息体 hybrid 由 L1 .x（拆段 ≤64） */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_freestanding_unsupported_impl(void) {
    diag_report_with_code(NULL, 0, 0, "link error", XLANG_DIAG_CODE_BUILD_BLD001,
                "-freestanding / XLANG_FREESTANDING is only supported for Linux ELF x86_64 (-o prog, not .o/.obj on macOS/COFF)",
                NULL);
}
void link_diag_freestanding_unsupported(void) {
    link_diag_freestanding_unsupported_impl();
}
#else
void link_diag_freestanding_unsupported(void);
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* R2：ld_debug_push 消息体 hybrid 由 L1 .x */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_ld_debug_push_impl(const char *rel, const char *stage, const char *path) {
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "ld debug: push %s %s=%s",
                 rel ? rel : "(null)",
                 stage ? stage : "path",
                 path ? path : "(null)");
}
void link_diag_ld_debug_push(const char *rel, const char *stage, const char *path) {
    link_diag_ld_debug_push_impl(rel, stage, path);
}
#else
void link_diag_ld_debug_push(const char *rel, const char *stage, const char *path);
#endif



/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* Cap residual：ld_debug_argv char** 遍历 🔒 常驻 _impl（L1 .x thin 转发） */
void link_diag_ld_debug_argv_impl(const char *label, const char *const *argv) {
    int di;
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "ld debug: %s",
                 label ? label : "argv");
    if (!argv)
        return;
    for (di = 0; argv[di] != NULL; di++) {
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "ld debug argv[%d]=%s",
                     di,
                     argv[di]);
    }
}
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void link_diag_ld_debug_argv(const char *label, const char *const *argv) {
    link_diag_ld_debug_argv_impl(label, argv);
}
#else
void link_diag_ld_debug_argv(const char *label, const char *const *argv);
#endif

/* G-02f-165 / wave111：xlang_link_perror pure orch in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * wave113: pure errno/_path orch; Cap residual is link_diag_strerror_current_impl
 * (wave217: public thin pure under hybrid L1).
 * PLATFORM: SHARED. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
void xlang_link_perror(const char *msg) {
    char op_buf[128];
    char path_buf[160];
    const char *text = msg;
    const char *lparen;
    const char *rparen;
    size_t op_len;
    size_t path_len;
    if (!text || !text[0]) {
        link_diag_errno("process error", "system call");
        return;
    }
    if (strncmp(text, "xlang: ", 6) == 0)
        text += 6;
    lparen = strrchr(text, '(');
    rparen = strrchr(text, ')');
    if (lparen && rparen && lparen < rparen && rparen[1] == '\0') {
        const char *op_end = lparen;
        while (op_end > text && op_end[-1] == ' ')
            op_end--;
        op_len = (size_t)(op_end - text);
        path_len = (size_t)(rparen - lparen - 1);
        if (op_len >= sizeof op_buf)
            op_len = sizeof op_buf - 1;
        if (path_len >= sizeof path_buf)
            path_len = sizeof path_buf - 1;
        memcpy(op_buf, text, op_len);
        op_buf[op_len] = '\0';
        memcpy(path_buf, lparen + 1, path_len);
        path_buf[path_len] = '\0';
        link_diag_errno_path("process error", op_buf, path_buf);
        return;
    }
    link_diag_errno("process error", text);
}
#else
void xlang_link_perror(const char *msg);
#endif

#define perror(msg) xlang_link_perror((msg))

/**
 * 判断 lib root 指针可安全解引用（避开 NULL/low tag/getenv 脏值）。
 * 参数：p 候选 lib root 字符串指针。
 * 返回值：非 0 表示可用。
 */
/* G-02f-115 / wave114：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Semantics: null / (uintptr_t)p < 4096 / empty → 0. PLATFORM: SHARED. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int xlang_asm_ld_lib_root_ptr_usable(const char *p) {
  return p && (uintptr_t)p >= 4096u && p[0] != '\0';
}
#else
int xlang_asm_ld_lib_root_ptr_usable(const char *p);
#endif



/**
 * 写入默认 lib root 到 root_buf（XLANG_LIB 或 "."）。
 * 参数：root_buf 至少 512 字节。
 */
/* G-02f-165 / wave115：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Semantics: "." then link_abi_getenv("XLANG_LIB") if pure usable (wave223 G.7).
 * PLATFORM: SHARED. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
void xlang_asm_ld_lib_root_default(char root_buf[512]) {
    const char *def = link_abi_getenv("XLANG_LIB");
    root_buf[0] = '.';
    root_buf[1] = '\0';
    if (!xlang_asm_ld_lib_root_ptr_usable(def))
        return;
    strncpy(root_buf, def, 511);
    root_buf[511] = '\0';
}
#else
void xlang_asm_ld_lib_root_default(char root_buf[512]);
#endif




#if defined(__linux__)
/** Absolute gcc path for ALLOW invoke_cc only (product -o hosted uses ld, not gcc-as-ld). */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
const char * xlang_linux_host_gcc_path(void) {
    /* Cap residual 9.1.2: faccessat, not libc access. */
    if (xlang_path_access("/usr/bin/gcc", X_OK) == 0)
        return "/usr/bin/gcc";
    if (xlang_path_access("/usr/local/bin/gcc", X_OK) == 0)
        return "/usr/local/bin/gcc";
    return "gcc";
}




/** Linux 链接子进程 PATH：gcc 官方镜像仅提供 /usr/local/bin/gcc。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void xlang_linux_ld_child_path(void) {
    (void)setenv("PATH", "/usr/local/bin:/usr/bin:/bin", 1);
}



#endif

/* #region debug-point A:hello-stage1-segv */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void xlang_debug_hello_stage1_report(const char *hypothesis_id, const char *location,
    const char *msg, int v1, int v2, int v3) {
    char url[256];
    char session[64];
    const char *env_paths[] = { ".dbg/hello-stage1-segv.env", "../.dbg/hello-stage1-segv.env", NULL };
    int path_i;
    url[0] = '\0';
    session[0] = '\0';
    for (path_i = 0; env_paths[path_i]; path_i++) {
        /* Cap residual 9.5.3 slice3b: whole-file read via xlang_proc_read_file
         * (9.1.12 authority); lines split in place with xlang_proc_next_line.
         * The debug env file is a tiny local config, so the 1 KiB cap replaces
         * fgets' 320-byte line window; values strip \r\n exactly as before. */
        char envbuf[1024];
        char *line;
        if (xlang_proc_read_file(env_paths[path_i], envbuf, sizeof envbuf) < 0)
            continue;
        for (line = envbuf; line; line = xlang_proc_next_line(line)) {
            if (strncmp(line, "DEBUG_SERVER_URL=", 17) == 0) {
                strncpy(url, line + 17, sizeof(url) - 1);
                url[sizeof(url) - 1] = '\0';
                url[strcspn(url, "\r\n")] = '\0';
            } else if (strncmp(line, "DEBUG_SESSION_ID=", 17) == 0) {
                strncpy(session, line + 17, sizeof(session) - 1);
                session[sizeof(session) - 1] = '\0';
                session[strcspn(session, "\r\n")] = '\0';
            }
        }
        if (url[0] && session[0])
            break;
    }
    if (!url[0])
        strncpy(url, "http://127.0.0.1:7777/event", sizeof(url) - 1);
    if (!session[0])
        strncpy(session, "hello-stage1-segv", sizeof(session) - 1);
#if !defined(_WIN32) && !defined(_WIN64)
    if (xlang_proc_fork() == 0) {
        char body[768];
        char *cargv[12];
        (void)snprintf(body, sizeof(body),
            "{\"sessionId\":\"%s\",\"runId\":\"pre-fix\",\"hypothesisId\":\"%s\",\"location\":\"%s\","
            "\"msg\":\"[DEBUG] %s\",\"data\":{\"v1\":%d,\"v2\":%d,\"v3\":%d}}",
            session, hypothesis_id ? hypothesis_id : "A", location ? location : "runtime_link_abi.c",
            msg ? msg : "hello-stage1", v1, v2, v3);
        cargv[0] = (char *)"curl";
        cargv[1] = (char *)"-s";
        cargv[2] = (char *)"-X";
        cargv[3] = (char *)"POST";
        cargv[4] = url;
        cargv[5] = (char *)"-H";
        cargv[6] = (char *)"Content-Type: application/json";
        cargv[7] = (char *)"-d";
        cargv[8] = body;
        cargv[9] = NULL;
        (void)xlang_proc_execvp("curl", cargv);
        xlang_proc_exit(0);
    }
#endif
}



/* #endregion */

/**
 * Resolve the directory of the running xlang binary (compiler/), used to place
 * runtime_panic.o next to the driver on cold start.
 * Linux: /proc/self/exe; macOS: _NSGetExecutablePath then link_abi_realpath_cap;
 * fallback: link_abi_realpath_cap(argv0) + strip last sep.
 * wave261 G.7: residual realpath via public pure thin link_abi_realpath_cap
 * (wave218 → _impl host realpath); not raw libc realpath.
 * @param argv0 optional path for fallback; out_dir / out_dir_sz output buffer
 * @return 0 success, -1 failure
 * PLATFORM: SHARED orch / LINUX|MACOS|WINDOWS path sources; realpath face WINDOWS null
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_resolve_compiler_dir(const char *argv0, char *out_dir, size_t out_dir_sz) {
    char buf[PATH_MAX];
    buf[0] = '\0';
    if (!out_dir || out_dir_sz < 2)
        return -1;
#if defined(__linux__)
    {
        ssize_t n = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            char *slash = strrchr(buf, '/');
            if (slash) {
                *slash = '\0';
                if (strlen(buf) >= out_dir_sz)
                    return -1;
                memcpy(out_dir, buf, strlen(buf) + 1);
                return 0;
            }
        }
    }
#endif
#if defined(__APPLE__)
    {
        uint32_t bufsz = (uint32_t)sizeof(buf);
        if (_NSGetExecutablePath(buf, &bufsz) == 0) {
            char resolved[PATH_MAX];
            /* wave261 G.7: link_abi_realpath_cap (not raw realpath). */
            if (link_abi_realpath_cap(buf, resolved) != NULL) {
                char *slash = strrchr(resolved, '/');
                if (slash) {
                    *slash = '\0';
                    if (strlen(resolved) >= out_dir_sz)
                        return -1;
                    memcpy(out_dir, resolved, strlen(resolved) + 1);
                    return 0;
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    {
        /* MinGW process.h 提供 _pgmptr 全局变量（char*），是当前进程可执行文件完整路径
         * （含 .exe 与盘符）。无需 #include <windows.h>，避免与 token.h 的 TOKEN_TYPE 冲突。 */
        extern char *_pgmptr;
        const char *exe_path = _pgmptr;
        if (exe_path && exe_path[0]) {
            size_t n = strlen(exe_path);
            if (n >= sizeof(buf))
                n = sizeof(buf) - 1;
            memcpy(buf, exe_path, n);
            buf[n] = '\0';
            char *slash = xlang_path_last_sep(buf);
            if (slash) {
                *slash = '\0';
                if (strlen(buf) >= out_dir_sz)
                    return -1;
                memcpy(out_dir, buf, strlen(buf) + 1);
                return 0;
            }
        }
    }
#endif
    if (!argv0 || !argv0[0] || !xlang_path_has_sep(argv0))
        return -1;
    /* wave261 G.7: link_abi_realpath_cap (not raw realpath); WINDOWS face → null. */
    if (link_abi_realpath_cap(argv0, buf) == NULL)
        return -1;
    {
        char *slash = xlang_path_last_sep(buf);
        if (!slash)
            return -1;
        *slash = '\0';
        if (strlen(buf) >= out_dir_sz)
            return -1;
        memcpy(out_dir, buf, strlen(buf) + 1);
    }
    return 0;
}




/**
 * argv0 缺失时构造 «compiler-dir/xlang» 供 get_*_path 走 ../std/…；xlang 毋须真实存在。
 * 参数：link_argv0 调用方 argv[0]；syn_buf/syn_sz 合成路径缓冲。
 * 返回值：有效 link argv0 或 NULL。
 * wave184: pure orch in labi_path_pure L0 (hybrid FROM_X / cold twin include).
 * Cap residual: xlang_resolve_compiler_dir. PLATFORM: SHARED.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_asm_ld_effective_link_argv0(const char *link_argv0, char *syn_buf, size_t syn_sz) {
    char comp_dir[PATH_MAX];
    int nn;
    if (link_argv0 && link_argv0[0])
        return link_argv0;
    if (!syn_buf || syn_sz == 0)
        return NULL;
    syn_buf[0] = '\0';
    if (xlang_resolve_compiler_dir(NULL, comp_dir, sizeof comp_dir) != 0)
        return NULL;
    nn = snprintf(syn_buf, syn_sz, "%s/xlang", comp_dir);
    if (nn < 0 || (size_t)nn >= syn_sz)
        return NULL;
    return syn_buf;
}
#else
const char *xlang_asm_ld_effective_link_argv0(const char *link_argv0, char *syn_buf, size_t syn_sz);
#endif



/**
 * F-03 v2/v3：std.io 已纯 .x，无 io.o；保留 API 供 repo root 推导，返回空串。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：空串（调用方应改用 xlang_repo_root_from_argv0 的 process.o 路径）。
 * wave184: pure orch in labi_path_pure L0. PLATFORM: SHARED.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_std_io_o_path(const char *argv0) {
  (void)argv0;
  {
    return xlang_empty_cstr();
  }
  return NULL;
}
#else
const char *xlang_std_io_o_path(const char *argv0);
#endif

/**
 * F-04 v7 + F-06 v1：std.compress 已纯 .x，无 compress.o；保留 API 兼容，返回空串。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：空串（压缩库由 user .o / 生成 C 扫描按需 -lz/-lzstd/-lbrotli*）。
 * wave184: pure orch in labi_path_pure L0. PLATFORM: SHARED.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_std_compress_o_path(const char *argv0) {
  (void)argv0;
  {
    return xlang_empty_cstr();
  }
  return NULL;
}
#else
const char *xlang_std_compress_o_path(const char *argv0);
#endif

/**
 * Derive repo root from the product host binary path.
 * Authority (G.7): xlang_resolve_compiler_dir (compiler/) → parent = repo root.
 * PLATFORM: SHARED — must not depend on formal std/*.o existing.
 *
 * Why: after L4 wipe, std/process/process.o is gone. The old path walked
 * process.o up three seps; when process.o is missing, include_root became ""
 * and xlang_ensure_formal_std_make_o never ran (mac true-cold residual).
 * Fallback: legacy process.o walk when compiler_dir resolve fails but process.o
 * already exists (warm tree).
 *
 * wave162: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: BSS memcpy + path_last_sep strip; Cap residual resolve + rel_o_path.
 *
 * @param argv0 optional xlang path (also used by xlang_resolve_compiler_dir fallback)
 * @return static buffer with repo root, or empty string
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_repo_root_from_argv0(const char *argv0) {
    static char buf[512];
    char comp[PATH_MAX];
    char *last;
    const char *proc_o;
    int k;
    buf[0] = '\0';
    /* Primary: compiler dir from self/exe or argv0 → parent is repo root. */
    if (xlang_resolve_compiler_dir(argv0, comp, sizeof comp) == 0 && comp[0]) {
        if (strlen(comp) < sizeof(buf)) {
            memcpy(buf, comp, strlen(comp) + 1);
            last = xlang_path_last_sep(buf);
            if (last && last != buf) {
                *last = '\0';
                return buf;
            }
            buf[0] = '\0';
        }
    }
    /* Fallback: process.o exists (warm tree) → strip std/process/process.o (3 seps). */
    proc_o = xlang_rel_o_path_from_argv0(argv0, "std/process/process.o");
    if (!proc_o || !proc_o[0])
        return buf;
    if (strlen(proc_o) >= sizeof(buf))
        return buf;
    strcpy(buf, proc_o);
    for (k = 0; k < 3; k++) {
        last = xlang_path_last_sep(buf);
        if (!last || last == buf)
            break;
        *last = '\0';
    }
    return buf;
}
#else
const char *xlang_repo_root_from_argv0(const char *argv0);
#endif

/**
 * 将 path 复制到 bank 下一槽（path 常为栈上 snprintf 结果）；成功返回持久指针；满则返回 NULL。
 * 参数：b bank；path 候选路径。
 */
const char *xlang_asm_ld_bank_push_impl(ShuAsmLdPathBank *b, const char *path) {
    if (!b || b->n >= XLANG_ASM_LD_PATH_BANK_SLOTS)
        return NULL;
    if (snprintf(b->slots[b->n], sizeof(b->slots[0]), "%s", path) >= (int)sizeof(b->slots[0]))
        return NULL;
    return b->slots[b->n++];
}

/* G-02f-277 L9 gates */
#ifndef XLANG_LABI_GATES_FROM_X
const char *xlang_asm_ld_bank_push(ShuAsmLdPathBank *b, const char *path) {
  if (b == NULL) {
    return NULL;
  }
  if (path == NULL) {
    return NULL;
  }
  {
    if (path[0] == 0) {
      return NULL;
    }
    return xlang_asm_ld_bank_push_impl(b, path);
  }
  return NULL;
}
#else
const char *xlang_asm_ld_bank_push(ShuAsmLdPathBank *b, const char *path);
#endif

/**
 * 在每个 -L（lib root）根下尝试 rel（如 std/process/process.o）；命中则拷入 bank 并返回指针。
 * 参数：rel 相对路径；lib_roots/n_lib_roots -L 根；bank 路径持久化。
 */
/* wave116：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: join root/rel without snprintf; Cap residual skip_missing + bank_push.
 * bank is opaque void* (≡ pure .x *u8 / cold twin labi_path_pure / invoke_ld_list decls).
 * PLATFORM: SHARED — G.7 single signature; L4 cold TU must not mix ShuAsmLdPathBank* vs void*. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank) {
    int i;
    char tmp[PATH_MAX];
    if (!rel || (uintptr_t)rel < 4096u)
        return NULL;
    if (!rel[0] || !bank || !lib_roots || (uintptr_t)lib_roots < 4096u || n_lib_roots <= 0)
        return NULL;
    for (i = 0; i < n_lib_roots && i < 24; i++) {
        size_t rn;
        const char *root = lib_roots[i];
        /* nostdlib getenv/environ 异常时 lib_roots 可能为低地址垃圾指针（如 0x1）。 */
        if (!root || (uintptr_t)root < 4096u)
            continue;
        if (!root[0])
            continue;
        rn = strlen(root);
        while (rn > 1 && root[rn - 1] == '/')
            rn--;
        if (rn + 2 + strlen(rel) >= sizeof(tmp))
            continue;
        {
            int nn = rn > 0 ? snprintf(tmp, sizeof tmp, "%.*s/%s", (int)rn, root, rel) : snprintf(tmp, sizeof tmp, "%s", rel);
            if (nn < 0 || nn >= (int)sizeof tmp)
                continue;
        }
        if (!asm_link_obj_skip_missing(tmp))
            continue;
        return xlang_asm_ld_bank_push((ShuAsmLdPathBank *)bank, tmp);
    }
    return NULL;
}
#else
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank);
#endif

/**
 * 对 path 做 realpath，仅当目标为已存在常规文件时返回 resolved（避免 nostdlib realpath 拼出不存在的路径）。
 * 参数：path 候选；resolved 输出缓冲（PATH_MAX）。
 * 返回值：resolved 或 NULL。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-270/L L3：realpath+skip 主体始终在 rest（thin shell 在 labi_path_io）。
 * 注意：impl 调用 asm_link_obj_skip_missing（hybrid 时由 L3 提供）。 */
const char *xlang_runtime_o_realpath_if_exists_impl(const char *path, char *resolved) {
    if (!path || !path[0] || !resolved || link_abi_realpath_cap(path, resolved) == NULL)
        return NULL;
    return asm_link_obj_skip_missing(resolved);
}

/* G-02f-270 L3 path IO public thin（非 hybrid 时 rest 自带；hybrid 时由 L3 提供） */
#ifndef XLANG_LABI_PATH_IO_FROM_X
const char * xlang_runtime_o_realpath_if_exists(const char *path, char *resolved) {
    if (path == NULL)
        return NULL;
    if (path[0] == 0)
        return NULL;
    if (resolved == NULL)
        return NULL;
    return xlang_runtime_o_realpath_if_exists_impl(path, resolved);
}
#else
const char *xlang_runtime_o_realpath_if_exists(const char *path, char *resolved);
#endif





/**
 * runtime_panic.o 路径；优先 cwd（runtime_panic.o / compiler/runtime_panic.o），再 argv0 目录。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 *
 * wave163: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: BSS join + last-sep index; Cap residual realpath_if_exists + getcwd + skip_missing.
 * PLATFORM: SHARED orch POSIX; Windows sep rest stays mega cold when non-hybrid.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_runtime_panic_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    const char *hit;
    buf[0] = resolved[0] = '\0';
    /* cwd 即 compiler/：与 xlang_asm 同目录的 runtime_panic.o */
    hit = xlang_runtime_o_realpath_if_exists("runtime_panic.o", resolved);
    if (hit)
        return hit;
    hit = xlang_runtime_o_realpath_if_exists("compiler/runtime_panic.o", resolved);
    if (hit)
        return hit;
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd) - 24) != NULL) {
            size_t L = strlen(cwd);
            if (L + 24 <= sizeof(cwd)) {
                memcpy(cwd + L, "/compiler/runtime_panic.o", 25);
                cwd[L + 24] = '\0';
                hit = xlang_runtime_o_realpath_if_exists(cwd, resolved);
                if (hit)
                    return hit;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = xlang_path_last_sep(argv0);
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 20)
                return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.';
            buf[1] = '\0';
            n = 1;
        }
        if (n + 18 < (int)sizeof(buf)) {
            strcat(buf, "/runtime_panic.o");
            hit = xlang_runtime_o_realpath_if_exists(buf, resolved);
            if (hit)
                return hit;
            if (asm_link_obj_skip_missing(buf))
                return buf;
        }
    }
    return buf;
}
#else
const char *xlang_runtime_panic_o_path(const char *argv0);
#endif

/**
 * std.async 协作调度内核（std/async/scheduler.o）；调用 coop_pingpong* 时按需链入。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 *
 * wave166: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: BSS join + last-sep index + argv0 realpath then parent+/../std/async;
 * Cap residual link_abi_realpath_cap + getcwd.
 * PLATFORM: SHARED orch POSIX; Windows sep rest stays mega cold when non-hybrid.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_std_async_scheduler_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (link_abi_realpath_cap("std/async/scheduler.o", resolved) != NULL)
        return resolved;
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd) - 26) != NULL) {
            size_t L = strlen(cwd);
            if (L + 26 <= sizeof(cwd)) {
                memcpy(cwd + L, "/std/async/scheduler.o", 22);
                cwd[L + 22] = '\0';
                if (link_abi_realpath_cap(cwd, resolved) != NULL)
                    return resolved;
            }
        }
    }
    if (argv0 && argv0[0] && link_abi_realpath_cap(argv0, buf) != NULL) {
        char *last = xlang_path_last_sep(buf);
        if (last && (size_t)(last - buf) + 26 < sizeof(buf)) {
            *last = '\0';
            strcat(buf, "/../std/async/scheduler.o");
            if (link_abi_realpath_cap(buf, resolved) != NULL)
                return resolved;
        }
    }
    return buf;
}
#else
const char *xlang_std_async_scheduler_o_path(const char *argv0);
#endif

/**
 * crt0_user.o 路径；与 runtime_panic.o 同目录（compiler/），供 XLANG_FREESTANDING 链入。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 *
 * wave164: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: BSS join + last-sep index; Cap residual link_abi_realpath_cap + getcwd.
 * PLATFORM: SHARED orch POSIX; Windows sep rest stays mega cold when non-hybrid.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_crt0_user_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (link_abi_realpath_cap("compiler/crt0_user.o", resolved) != NULL)
        return resolved;
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd) - 22) != NULL) {
            size_t L = strlen(cwd);
            if (L + 22 <= sizeof(cwd)) {
                memcpy(cwd + L, "/compiler/crt0_user.o", 22);
                cwd[L + 21] = '\0';
                if (link_abi_realpath_cap(cwd, resolved) != NULL)
                    return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = xlang_path_last_sep(argv0);
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 16)
                return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.';
            buf[1] = '\0';
            n = 1;
        }
        if (n + 14 < (int)sizeof(buf)) {
            strcat(buf, "/crt0_user.o");
            if (link_abi_realpath_cap(buf, resolved) != NULL)
                return resolved;
            return buf;
        }
    }
    return buf;
}
#else
const char *xlang_crt0_user_o_path(const char *argv0);
#endif

/**
 * freestanding_io.o 路径；与 crt0_user.o 同目录（compiler/），供 XLANG_FREESTANDING syscall write。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 *
 * wave165: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: BSS join + last-sep index; Cap residual link_abi_realpath_cap + getcwd.
 * PLATFORM: SHARED orch POSIX; Windows sep rest stays mega cold when non-hybrid.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_freestanding_io_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (link_abi_realpath_cap("compiler/freestanding_io.o", resolved) != NULL)
        return resolved;
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd) - 28) != NULL) {
            size_t L = strlen(cwd);
            if (L + 28 <= sizeof(cwd)) {
                memcpy(cwd + L, "/compiler/freestanding_io.o", 28);
                cwd[L + 27] = '\0';
                if (link_abi_realpath_cap(cwd, resolved) != NULL)
                    return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = xlang_path_last_sep(argv0);
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 20)
                return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.';
            buf[1] = '\0';
            n = 1;
        }
        if (n + 18 < (int)sizeof(buf)) {
            strcat(buf, "/freestanding_io.o");
            if (link_abi_realpath_cap(buf, resolved) != NULL)
                return resolved;
            return buf;
        }
    }
    return buf;
}
#else
const char *xlang_freestanding_io_o_path(const char *argv0);
#endif
/* wave160: xlang_runtime_compiler_o_path_copy pure orch lives in labi_path_pure
 * (Cap residual xlang_resolve_compiler_dir + pure byte join compiler-dir/leaf).
 * Cold twin via L0 seed / mega #ifndef below; hybrid FROM_X → L0 pure .x.
 * Why: hybrid still had always-mega C body for path join after platform resolve.
 * Cap residual stays: xlang_resolve_compiler_dir (#if LINUX/MACOS/WINDOWS).
 * PLATFORM: SHARED orch. */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int xlang_runtime_compiler_o_path_copy(const char *argv0, const char *leaf, char *out, size_t out_sz) {
    char comp_dir[4096];
    int dn;
    int ln;
    int i;
    int k;
    size_t need;
    if (!out || out_sz == 0 || !leaf || !leaf[0])
        return -1;
    out[0] = '\0';
    if (xlang_resolve_compiler_dir(argv0, comp_dir, sizeof comp_dir) != 0)
        return -1;
    dn = 0;
    while (comp_dir[dn] != 0)
        dn = dn + 1;
    ln = 0;
    while (leaf[ln] != 0)
        ln = ln + 1;
    need = (size_t)dn + 1u + (size_t)ln;
    if (need >= out_sz) {
        out[0] = '\0';
        return -1;
    }
    for (i = 0; i < dn; i++)
        out[i] = comp_dir[i];
    out[dn] = '/';
    for (k = 0; k <= ln; k++)
        out[dn + 1 + k] = leaf[k];
    return 0;
}
#else
int xlang_runtime_compiler_o_path_copy(const char *argv0, const char *leaf, char *out, size_t out_sz);
#endif




/* wave183: thin xlang_runtime_*_o_path pure orch — body removed from mega
 * (lives in labi_path_pure L0 pure / cold twin). Hybrid XLANG_LABI_PATH_PURE_FROM_X → L0 pure;
 * cold path defines via #ifndef below (static PATH_MAX BSS + compiler_o_path_copy).
 * Why: hybrid still had always-mega C bodies for 29 thin runtime path leaves after wave161
 * G.7 join through compiler_o_path_copy (resolve+snprintf already removed).
 * Cap residual: xlang_resolve_compiler_dir inside peer compiler_o_path_copy only.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
/**
 * seed asm 用户程序：std.io 桩 .o（与 io.o 同链）；见 seeds/runtime_asm_io_stubs.from_x.c。
 * 参数：argv0 用于解析 compiler 目录。
 * 返回值：.o 路径或空串。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_asm_io_stubs.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}



/**
 * F-ZC：runtime_process_argv.o 路径；codegen argc/argv 全局，与 process.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
const char *xlang_runtime_process_argv_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_process_argv.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}



/* wave161 G.7 path residual: thin xlang_runtime_*_o_path static-buffer leaves
 * (process_os_glue … ed25519_ref10_glue) route compiler-dir/leaf join through
 * xlang_runtime_compiler_o_path_copy (wave160 pure orch / cold twin). Closes soft
 * residual of per-leaf resolve+snprintf when single join authority exists.
 * Cap residual stays: per-leaf static PATH_MAX buffer (return durable *const).
 * Complex path leaves (async/crt0/freestanding_io) still own cwd/
 * (wave162 repo_root pure; wave163 panic_o_path pure).
 * realpath ladders. PLATFORM: SHARED. */
const char *xlang_runtime_process_os_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_process_os_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_test_fn_invoke.o 路径；std.test fn-ptr，与 test.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_test_fn_invoke.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_random_fill.o 路径；CSPRNG OS fill，与 random.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_random_fill_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_random_fill.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * zlib 宏包装桩路径；deflateInit2/inflateInit2 是宏，此 .o 提供真实函数符号。
 */
const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_compress_zlib_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-03：runtime_heap_user.o 路径；co-emit std.heap redirect 的 heap_*_c 符号。
 */
const char *xlang_runtime_heap_user_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_heap_user.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_time_os.o 路径；time OS syscall，与 time.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_time_os_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_time_os.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_queue_contention.o 路径；queue pthread 胶层，与 queue.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_queue_contention_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_queue_contention.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_dynlib_os.o 路径；dlopen/LoadLibrary，与 dynlib.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_dynlib_os_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_dynlib_os.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_env_os.o 路径；env OS getenv/setenv/iter，与 env.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_env_os_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_env_os.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_backtrace_platform.o 路径；capture/symbolicate，与 backtrace.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_backtrace_platform_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_backtrace_platform.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_log_os.o 路径；log sink/轮转/异步，与 log.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_log_os_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_log_os.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_math_libm.o 路径；libm/fenv，与 math.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_math_libm_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_math_libm.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_atomic_glue.o 路径；原子 load/store/CAS/fence，与 atomic.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_atomic_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_atomic_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_channel_glue.o 路径；channel 有界/无界/select，与 channel.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_channel_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_channel_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_net_udp_batch.o 路径；Linux recvmmsg/sendmmsg，与 net.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_net_udp_batch_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_net_udp_batch.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * F-ZC：runtime_net_workers.o 路径；accept worker 线程入口，与 net.o 同链。
 * 参数：argv0 可选 xlang 路径。
 * 返回值：.o 路径或空串。
 */
const char *xlang_runtime_net_workers_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_net_workers.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_sync_os_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sync_os.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_sync_lock_diag_tls_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sync_lock_diag_tls.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_thread_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_thread_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_scheduler_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_scheduler_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_http_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_http_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_tls_mbedtls_bio_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_tls_mbedtls_bio.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_kv_mmap_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_arrow_simd_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_sqlite_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sqlite_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_crypto_inc_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    /* wave161 G.7: join via pure/wave160 compiler_o_path_copy (no resolve+snprintf). */
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_ed25519_ref10_glue.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

/**
 * wave253: runtime_link_abi_user_env.o path — sole residual-domain face companion (weak).
 * @param argv0 optional product host path
 * @return durable .o path or empty string
 * PLATFORM: SHARED — user/STD_AND_PANIC only; never g05 host bag as TU (path only).
 */
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0) {
    static char resolved[PATH_MAX];
    if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_link_abi_user_env.o", resolved, sizeof resolved) != 0)
        resolved[0] = '\0';
    return resolved;
}

#else
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
const char *xlang_runtime_process_os_glue_o_path(const char *argv0);
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0);
const char *xlang_runtime_random_fill_o_path(const char *argv0);
const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0);
const char *xlang_runtime_heap_user_o_path(const char *argv0);
const char *xlang_runtime_time_os_o_path(const char *argv0);
const char *xlang_runtime_queue_contention_o_path(const char *argv0);
const char *xlang_runtime_dynlib_os_o_path(const char *argv0);
const char *xlang_runtime_env_os_o_path(const char *argv0);
const char *xlang_runtime_backtrace_platform_o_path(const char *argv0);
const char *xlang_runtime_log_os_o_path(const char *argv0);
const char *xlang_runtime_math_libm_o_path(const char *argv0);
const char *xlang_runtime_atomic_glue_o_path(const char *argv0);
const char *xlang_runtime_channel_glue_o_path(const char *argv0);
const char *xlang_runtime_net_udp_batch_o_path(const char *argv0);
const char *xlang_runtime_net_workers_o_path(const char *argv0);
const char *xlang_runtime_sync_os_o_path(const char *argv0);
const char *xlang_runtime_sync_lock_diag_tls_o_path(const char *argv0);
const char *xlang_runtime_thread_glue_o_path(const char *argv0);
const char *xlang_runtime_scheduler_glue_o_path(const char *argv0);
const char *xlang_runtime_http_glue_o_path(const char *argv0);
const char *xlang_runtime_tls_mbedtls_bio_o_path(const char *argv0);
const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0);
const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0);
const char *xlang_runtime_sqlite_glue_o_path(const char *argv0);
const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0);
const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0);
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0);
#endif

/**
 * 若 runtime_panic.o 尚不存在则用 cc -c 从 src/asm 下源码生成到 xlang 同目录，以便 ASM -o exe 链接能提供 xlang_panic_。
 * G-02f-76/83：产品冷启动源统一 seeds/*.from_x.c。Linux 优先 x86_64 .s；Apple arm64 优先 seeds/runtime_panic_arm64.from_x.c；否则 seeds/runtime_panic.from_x.c。
 * 参数：argv0 用于解析 compiler 目录。
 * 返回值：0 成功，-1 失败并已写 stderr。
 */
/* wave169: xlang_ensure_runtime_panic_o pure orch — body removed from mega
 * (lives in labi_ensure_list L4 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_ENSURE_LIST_FROM_X → L4 pure; cold path defines via include.
 * Why: hybrid still had always-mega C body for special panic ensure (multi-source
 * prefer) after panic path pure wave163 and freestanding ensure pair wave167/168.
 * Cap residual: resolve/access/cc/stat + host linux_x86_64 / posix_aarch64.
 * PLATFORM: SHARED orch; LINUX x86_64 asm; LINUX|MACOS aarch64 arm64 seed. */
#ifndef XLANG_LABI_ENSURE_LIST_FROM_X
/* cold twin body is in seeds/labi_ensure_list.from_x.c (#include above). */
#else
int xlang_ensure_runtime_panic_o(const char *argv0);
#endif




/**
 * XLANG_FREESTANDING=1 或 driver -freestanding：Linux x86_64 上用户程序 -nostdlib 静态链（S4）。
 * 参数：driver_freestanding 非 0 表示 driver 已设 -freestanding。
 * 返回值：非 0 表示 freestanding 链启用。
 */
/** G-02f-36：OS 门闩槽 — .x freestanding_enabled 读此，避免 .x 内 #if。 */
/* G-02f-269 / R2 labi_host_lit：#if body Cap residual 常驻 rest（与 path_io stat 同构） */
int xlang_host_is_linux_impl(void) {
#if defined(__linux__)
    return 1;
#else
    return 0;
#endif
}

/* R2：public thin 非 hybrid 时 rest 自带；FROM_X 时由 L2 full .x 提供 */
#ifndef XLANG_LABI_HOST_LIT_FROM_X
int xlang_host_is_linux(void) {
    return xlang_host_is_linux_impl();
}
#else
int xlang_host_is_linux(void);
#endif


/** G-02f-43：Apple aarch64 门闩槽 — .x resolve_target_arch 读此。 */
/* G-02f-269 / R2 labi_host_lit：#if body Cap residual 常驻 rest */
int xlang_host_is_apple_aarch64_impl(void) {
#if defined(__APPLE__) && defined(__aarch64__)
    return 1;
#else
    return 0;
#endif
}

/* R2：public thin 非 hybrid 时 rest 自带；FROM_X 时由 L2 full .x 提供 */
#ifndef XLANG_LABI_HOST_LIT_FROM_X
int xlang_host_is_apple_aarch64(void) {
    return xlang_host_is_apple_aarch64_impl();
}
#else
int xlang_host_is_apple_aarch64(void);
#endif



/* G-02f-276 L7 freestanding list pure */
#ifndef XLANG_LABI_FREESTANDING_LIST_FROM_X
#include "seeds/labi_freestanding_list.from_x.c"
#else
const char *labi_fs_env_freestanding(void);
int labi_fs_io_sym_count(void);
const char *labi_fs_io_sym_at(int i);
const char *labi_fs_panic_sym(void);
int labi_fs_ensure_catalog_count(void);
int labi_fs_ensure_catalog_step_at(int i, const char **stem_out, const char **out_base_out,
                                   const char **src_rel_out);
const char *labi_fs_ensure_out_base(int i);
const char *labi_fs_ensure_src_rel(int i);
const char *labi_fs_ensure_stem(int i);
const char *labi_fs_crt0_out_base(void);
const char *labi_fs_crt0_src_rel(void);
const char *labi_fs_io_out_base(void);
const char *labi_fs_io_src_rel(void);
/* wave117 needs pure orch (bodies in L7 pure .x / cold seed). */
int labi_fs_heap_c_needle_count(void);
const char *labi_fs_heap_c_needle_at(int i);
int labi_fs_heap_o_sym_count(void);
const char *labi_fs_heap_o_sym_at(int i);
int labi_fs_memcpy_face_sym_count(void);
const char *labi_fs_memcpy_face_sym_at(int i);
int link_abi_generated_c_needs_libc_heap(const char *c_path);
int link_abi_user_o_needs_libc_heap(const char *user_o);
int link_abi_user_o_needs_freestanding_nostdlib_face(const char *user_o);
/* wave136: C-path PRIMARY OS/fs generated_c needs pure (L7). */
int labi_fs_gen_fs_needle_count(void);
const char *labi_fs_gen_fs_needle_at(int i);
int labi_fs_gen_random_needle_count(void);
const char *labi_fs_gen_random_needle_at(int i);
int labi_fs_gen_time_needle_count(void);
const char *labi_fs_gen_time_needle_at(int i);
int labi_fs_gen_runtime_needle_count(void);
const char *labi_fs_gen_runtime_needle_at(int i);
int link_abi_generated_c_needs_fs(const char *c_path);
int link_abi_generated_c_needs_random(const char *c_path);
int link_abi_generated_c_needs_time(const char *c_path);
int link_abi_generated_c_needs_runtime(const char *c_path);
/* wave137: compress lib generated_c needs pure (L7). */
int labi_fs_gen_zlib_needle_count(void);
const char *labi_fs_gen_zlib_needle_at(int i);
int labi_fs_gen_zstd_needle_count(void);
const char *labi_fs_gen_zstd_needle_at(int i);
int labi_fs_gen_brotli_needle_count(void);
const char *labi_fs_gen_brotli_needle_at(int i);
int link_abi_generated_c_needs_zlib(const char *c_path);
int link_abi_generated_c_needs_zstd(const char *c_path);
int link_abi_generated_c_needs_brotli(const char *c_path);
/* wave138: core.slice / std.db.kv / std.db.arrow generated_c needs pure (L7). */
int labi_fs_gen_core_slice_needle_count(void);
const char *labi_fs_gen_core_slice_needle_at(int i);
int labi_fs_gen_db_kv_needle_count(void);
const char *labi_fs_gen_db_kv_needle_at(int i);
int labi_fs_gen_db_arrow_needle_count(void);
const char *labi_fs_gen_db_arrow_needle_at(int i);
int link_abi_generated_c_needs_core_slice(const char *c_path);
int link_abi_generated_c_needs_db_kv(const char *c_path);
int link_abi_generated_c_needs_db_arrow(const char *c_path);
/* wave139: co-emit provides_* pure (L7 freestanding). */
int labi_fs_gen_provides_core_mem_needle_count(void);
const char *labi_fs_gen_provides_core_mem_needle_at(int i);
int labi_fs_gen_provides_std_heap_needle_count(void);
const char *labi_fs_gen_provides_std_heap_needle_at(int i);
int link_abi_generated_c_provides_core_mem(const char *c_path);
int link_abi_generated_c_provides_std_heap(const char *c_path);
/* wave159: freestanding_enabled pure orch (L7; hybrid). */
int xlang_link_freestanding_enabled(int driver_freestanding);
/* wave167: ensure_crt0_user_o pure orch (L7; hybrid). */
int xlang_ensure_crt0_user_o(const char *argv0, int driver_freestanding);
/* wave168: ensure_freestanding_io_o pure orch (L7; hybrid). */
int xlang_ensure_freestanding_io_o(const char *argv0, int driver_freestanding);
/* wave175: contains_substr pure orch (L7; hybrid). */
int link_abi_generated_c_contains_substr(const char *c_path, const char *needle);
/* wave176: contains_substr_use_line pure orch (L7; hybrid). */
int link_abi_generated_c_contains_substr_use_line(const char *c_path, const char *needle);
/* wave177: any_substr_use_line pure orch (L7; hybrid). */
int link_abi_generated_c_contains_any_substr_use_line(const char *c_path, const char **needles,
                                                     int n_needles);
/* wave178: any_substr pure orch (L7; hybrid). */
int link_abi_generated_c_contains_any_substr(const char *c_path, const char **needles,
                                            int n_needles);
#endif

/* wave159: xlang_link_freestanding_enabled pure orch — body removed from mega
 * (lives in labi_freestanding_list L7 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_FREESTANDING_LIST_FROM_X → L7 pure; cold path defines via include.
 * Why: hybrid still had always-mega C body for freestanding env gate over pure env name.
 * Cap residual: getenv; peer host_is_linux. PLATFORM: SHARED orch / LINUX consumers. */

/* wave167: xlang_ensure_crt0_user_o pure orch — body removed from mega
 * (lives in labi_freestanding_list L7 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_FREESTANDING_LIST_FROM_X → L7 pure; cold path defines via include.
 * Why: hybrid still had always-mega C body for freestanding crt0 ensure over pure tables.
 * Cap residual: resolve/access/cc/stat. Sibling wave168 ensure_freestanding_io pure.
 * PLATFORM: SHARED orch / LINUX freestanding consumers. */

/* wave168: xlang_ensure_freestanding_io_o pure orch — body removed from mega
 * (lives in labi_freestanding_list L7 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_FREESTANDING_LIST_FROM_X → L7 pure; cold path defines via include.
 * Why: hybrid still had always-mega C body for freestanding_io ensure over pure tables.
 * Cap residual: resolve/access/cc/stat. Peer wave167 ensure_crt0. PLATFORM: SHARED orch. */

/**
 * 若 runtime_asm_io_stubs.o 尚不存在则用 cc -c 从 seeds/runtime_asm_io_stubs.from_x.c 生成到 xlang 同目录，
 * 以便 ASM -o exe 链 hello 等 import std.io 的程序时提供 std_io_print_str。
 * 参数：argv0 用于解析 compiler 目录。
 * 返回值：0 成功，-1 失败并已写 stderr。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-273 L4 ensure catalog pure
 * LABI_ENS_* 索引/flags 必须始终可见：冷启动 #include labi_ensure_list 只提供
 * catalog_* 实现（整数下标），hybrid FROM_X 由 .x 提供实现；下方 mega ensure
 * 包装器两种路径都用枚举名（不可仅放在 #else 分支，否则 clean 冷启动 undeclared）。 */
enum {
  LABI_ENS_FLAG_NONE = 0,
  LABI_ENS_FLAG_PIE = 1,
  LABI_ENS_FLAG_SQLITE = 2,
  /* runtime_http_glue.from_x.c #include "http_*.inc" — need -I seeds/http */
  LABI_ENS_FLAG_HTTP_SEEDS = 3
};
enum {
  LABI_ENS_ASM_IO_STUBS = 0,
  LABI_ENS_PROCESS_ARGV,
  LABI_ENS_PROCESS_OS_GLUE,
  LABI_ENS_RANDOM_FILL,
  LABI_ENS_COMPRESS_ZLIB_GLUE,
  LABI_ENS_TIME_OS,
  LABI_ENS_QUEUE_CONTENTION,
  LABI_ENS_DYNLIB_OS,
  LABI_ENS_ENV_OS,
  LABI_ENS_BACKTRACE_PLATFORM,
  LABI_ENS_LOG_OS,
  LABI_ENS_MATH_LIBM,
  LABI_ENS_ATOMIC_GLUE,
  LABI_ENS_CHANNEL_GLUE,
  LABI_ENS_NET_UDP_BATCH,
  LABI_ENS_NET_WORKERS,
  LABI_ENS_SYNC_OS,
  LABI_ENS_SYNC_LOCK_DIAG_TLS,
  LABI_ENS_THREAD_GLUE,
  LABI_ENS_SCHEDULER_GLUE,
  LABI_ENS_HTTP_GLUE,
  LABI_ENS_KV_MMAP_GLUE,
  LABI_ENS_ARROW_SIMD_GLUE,
  LABI_ENS_SQLITE_GLUE,
  LABI_ENS_CRYPTO_INC_GLUE,
  LABI_ENS_ED25519_REF10_GLUE,
  LABI_ENS_COUNT
};
#ifndef XLANG_LABI_ENSURE_LIST_FROM_X
#include "seeds/labi_ensure_list.from_x.c"
#else
int labi_ensure_catalog_count(void);
int labi_ensure_catalog_step_at(int i, const char **stem_out, const char **out_base_out,
                                const char **seed_base_out, int *flags_out,
                                const char **hint_out);
const char *labi_ensure_catalog_stem(int i);
const char *labi_ensure_catalog_out_base(int i);
const char *labi_ensure_catalog_seed_base(int i);
int labi_ensure_catalog_flags(int i);
/* wave169: ensure_runtime_panic_o pure orch (L4; hybrid). */
int xlang_ensure_runtime_panic_o(const char *argv0);
/* wave170: ensure_runtime_heap_user_o pure orch (L4; hybrid). */
int xlang_ensure_runtime_heap_user_o(const char *argv0);
/* wave171: ensure_runtime_test_fn_invoke_o pure orch (L4; hybrid). */
int xlang_ensure_runtime_test_fn_invoke_o(const char *argv0);
/* wave172: ensure_runtime_tls_mbedtls_bio_o pure orch (L4; hybrid). */
int xlang_ensure_runtime_tls_mbedtls_bio_o(const char *argv0);
/* wave182: ensure_bootstrap_nostdlib_stubs_o pure orch (L4; hybrid). */
int xlang_ensure_bootstrap_nostdlib_stubs_o(const char *argv0);
/* wave173: link_abi_ensure_from_catalog pure orch (L4; hybrid).
 * product_path from peer *_o_path (no path_fn in pure; no .x fnptr ABI). */
int link_abi_ensure_from_catalog(const char *argv0, int catalog_idx, const char *product_path);
/* wave174: catalog thin ensure wraps pure (L4; hybrid). */
int xlang_ensure_runtime_asm_io_stubs_o(const char *argv0);
int xlang_ensure_runtime_process_argv_o(const char *argv0);
int xlang_ensure_runtime_process_os_glue_o(const char *argv0);
int xlang_ensure_runtime_random_fill_o(const char *argv0);
int xlang_ensure_runtime_compress_zlib_glue_o(const char *argv0);
int xlang_ensure_runtime_time_os_o(const char *argv0);
int xlang_ensure_runtime_queue_contention_o(const char *argv0);
int xlang_ensure_runtime_dynlib_os_o(const char *argv0);
int xlang_ensure_runtime_env_os_o(const char *argv0);
int xlang_ensure_runtime_backtrace_platform_o(const char *argv0);
int xlang_ensure_runtime_log_os_o(const char *argv0);
int xlang_ensure_runtime_math_libm_o(const char *argv0);
int xlang_ensure_runtime_atomic_glue_o(const char *argv0);
int xlang_ensure_runtime_channel_glue_o(const char *argv0);
int xlang_ensure_runtime_net_udp_batch_o(const char *argv0);
int xlang_ensure_runtime_net_workers_o(const char *argv0);
int xlang_ensure_runtime_sync_os_o(const char *argv0);
int xlang_ensure_runtime_sync_lock_diag_tls_o(const char *argv0);
int xlang_ensure_runtime_thread_glue_o(const char *argv0);
int xlang_ensure_runtime_scheduler_glue_o(const char *argv0);
int xlang_ensure_runtime_http_glue_o(const char *argv0);
int xlang_ensure_runtime_kv_mmap_glue_o(const char *argv0);
int xlang_ensure_runtime_arrow_simd_glue_o(const char *argv0);
int xlang_ensure_runtime_sqlite_glue_o(const char *argv0);
int xlang_ensure_runtime_crypto_inc_glue_o(const char *argv0);
int xlang_ensure_runtime_ed25519_ref10_glue_o(const char *argv0);
#endif

/*
 * wave173: link_abi_ensure_from_catalog pure orch — body removed from mega
 * (lives in labi_ensure_list L4 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_ENSURE_LIST_FROM_X → L4 pure; cold path defines via include.
 * Cap residual: resolve/access/cc/one_extra/stat. PLATFORM: SHARED orch.
 */

/*
 * wave174: catalog thin ensure wraps pure — bodies removed from mega
 * (lives in labi_ensure_list L4 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_ENSURE_LIST_FROM_X → L4 pure; cold path defines via include.
 * 26× xlang_ensure_runtime_*_o: peer *_o_path + pure ensure_from_catalog.
 * Why: hybrid still had always-mega thin wrap C after ensure_from_catalog pure wave173.
 * Cap residual: only peer path ladders (static PATH_MAX / compiler_o_path_copy).
 * PLATFORM: SHARED thin orch.
 */
/* Catalog thin ensure symbols (hybrid FROM_X → L4 pure; cold → include above):
 *   xlang_ensure_runtime_asm_io_stubs_o
 *   xlang_ensure_runtime_process_argv_o
 *   xlang_ensure_runtime_process_os_glue_o
 *   xlang_ensure_runtime_random_fill_o
 *   xlang_ensure_runtime_compress_zlib_glue_o
 *   xlang_ensure_runtime_time_os_o
 *   xlang_ensure_runtime_queue_contention_o
 *   xlang_ensure_runtime_dynlib_os_o
 *   xlang_ensure_runtime_env_os_o
 *   xlang_ensure_runtime_backtrace_platform_o
 *   xlang_ensure_runtime_log_os_o
 *   xlang_ensure_runtime_math_libm_o
 *   xlang_ensure_runtime_atomic_glue_o
 *   xlang_ensure_runtime_channel_glue_o
 *   xlang_ensure_runtime_net_udp_batch_o
 *   xlang_ensure_runtime_net_workers_o
 *   xlang_ensure_runtime_sync_os_o
 *   xlang_ensure_runtime_sync_lock_diag_tls_o
 *   xlang_ensure_runtime_thread_glue_o
 *   xlang_ensure_runtime_scheduler_glue_o
 *   xlang_ensure_runtime_http_glue_o
 *   xlang_ensure_runtime_kv_mmap_glue_o
 *   xlang_ensure_runtime_arrow_simd_glue_o
 *   xlang_ensure_runtime_sqlite_glue_o
 *   xlang_ensure_runtime_crypto_inc_glue_o
 *   xlang_ensure_runtime_ed25519_ref10_glue_o
 * Special ensures already pure (wave169–172): panic / heap_user / test_fn_invoke / tls_mbedtls_bio.
 */

/* wave170/171/172 special ensure pure — body removed (labi_ensure_list L4 / cold twin).
 * Hybrid decls live in ENSURE_LIST #else above; cold twin defines bodies via include.
 */

/* wave167: xlang_ensure_crt0_user_o pure orch lives in labi_freestanding_list
 * (peer freestanding_enabled + pure tables + Cap residual resolve/access/cc/stat).
 * Was always-mega body. Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED orch / LINUX freestanding consumers — dual-end L2.
 */
int xlang_ensure_crt0_user_o(const char *argv0, int driver_freestanding);

/* wave168: xlang_ensure_freestanding_io_o pure orch lives in labi_freestanding_list
 * (peer freestanding_enabled + pure io tables + Cap residual resolve/access/cc/stat).
 * Was always-mega body. Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED orch / LINUX freestanding consumers — dual-end L2.
 */
int xlang_ensure_freestanding_io_o(const char *argv0, int driver_freestanding);




/**
 * CI/Docker/musl 上 -march=native/-flto 可能导致 cc 异常退出（exit -1）。
 * 参数：无。
 * 返回值：非 0 表示跳过 native 调优。
 */
/* G-02f-274 L5 invoke_cc list pure */
#ifndef XLANG_LABI_INVOKE_CC_LIST_FROM_X
#include "seeds/labi_invoke_cc_list.from_x.c"
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
void invoke_cc_append_heap_f06_ondemand(char **argv, int *ia, int argv_cap,
    const char **c_paths, int n, const char *include_root);
int invoke_cc_run_cc_argv(char **argv);
/* Stage 12.2.3 G.7 single host-cc gate (FORBID+ALLOW); pure body in labi_invoke_cc_list.
 * Decl here so xlang_invoke_cc_impl can isolate ensure/argv before any heavy work.
 * PLATFORM: SHARED — product default deny; experimental ALLOW=1 only. */
int invoke_cc_host_cc_spawn_gate(void);
void invoke_cc_maybe_strip_out(const char *out_path, const char *opt_level);
void invoke_cc_append_argv_head_flags(char **argv, int *ia, int argv_cap,
    const char *out_path, const char *opt_level, int use_lto, const char *include_root);
void invoke_cc_append_argv_tail_flags(char **argv, int *ia, int argv_cap,
    const char *thread_o, const char *sync_o, const char *channel_o);
void invoke_cc_append_minimal_cc_link_tail(char **argv, int *ia, int argv_cap);
#endif

/* wave155: xlang_append_linux_link_harden_impl pure orch lives in labi_invoke_cc_list
 * (pure harden table count/at + append loop). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had always-mega C body for Linux harden -pie/-z* append.
 * PLATFORM: SHARED orch / LINUX consumers. */

/* wave198: invoke_cc_append_early_needs pure orch lives in labi_invoke_cc_list
 * (early needs scan+push inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had early needs block always-mega inside invoke_cc_impl.
 * PLATFORM: SHARED orch / POSIX -lc / WINDOWS -lbcrypt -lkernel32 -lws2_32. */

/* wave199: invoke_cc_scan_std_module_needs pure orch lives in labi_invoke_cc_list
 * (std module need flag scan inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had std need scan loop always-mega inside invoke_cc_impl.
 * PLATFORM: SHARED orch; Cap residual contains_substr(_use_line) peers.
 */

/* wave200: invoke_cc_append_std_ensure_push_front pure orch lives in labi_invoke_cc_list
 * (ensure-push front string→env inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had ensure-push front always-mega after wave199 flags bank.
 * PLATFORM: SHARED orch / LINUX -pthread+asm_io_stubs / WINDOWS -lws2_32 -lbcrypt.
 */

/* wave201: invoke_cc_append_std_ensure_push_mid pure orch lives in labi_invoke_cc_list
 * (ensure-push mid sync→hash inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had ensure-push mid always-mega after wave200 front.
 * PLATFORM: SHARED orch / LINUX -rdynamic -ldl / APPLE -export_dynamic / WINDOWS Cap (no dbghelp).
 */

/* wave202: invoke_cc_append_std_ensure_push_heavy_a pure orch lives in labi_invoke_cc_list
 * (ensure-push heavy_a math…compress inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had ensure-push heavy always-mega after wave201 mid.
 * PLATFORM: SHARED orch; brew -L peer mac-oriented; set/map/queue formal ensure.
 */

/* wave203: invoke_cc_append_std_ensure_push_heavy_b pure orch lives in labi_invoke_cc_list
 * (ensure-push heavy_b unicode…process_argv inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had ensure-push heavy_b always-mega after wave202 heavy_a.
 * PLATFORM: SHARED orch / LINUX -ldl -pthread / WINDOWS -lws2_32 on http.
 */

/* wave204: invoke_cc_append_heap_f06_ondemand pure orch lives in labi_invoke_cc_list
 * (heap F-06 on-demand + page_mmap companions inside xlang_invoke_cc_impl). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Why: hybrid still had heap F-06 always-mega after wave203 heavy_b.
 * PLATFORM: SHARED orch (Ubuntu L4 cold needs page_mmap + asm_io_stubs with heap.o).
 */

/* wave205: invoke_cc_run_cc_argv + invoke_cc_maybe_strip_out pure orch lives in
 * labi_invoke_cc_list (fork-exec shell + strip after argv build). Cold twin via #include
 * labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x (decl in #else).
 * Cap residual peers: xlang_spawn_sync + invoke_cc_strip_out_x_impl + setenv + host_is_* + tool_status.
 * Why: hybrid still had always-mega fork+exec+wait+strip after argv pure (wave198–204).
 * PLATFORM: SHARED orch / parent-side spawn (no fork-first argv build).
 */

/* wave206: invoke_cc_append_argv_head_flags pure orch lives in labi_invoke_cc_list
 * (argv head quiet/O/native/NDEBUG/flto/harden/gc/-I inside xlang_invoke_cc_impl).
 * Cold twin via #include labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x.
 * Cap residual peers: pure skip_native + pure harden_impl + host_is_*.
 * wave223/225 G.7: env lookup via link_abi_getenv (XLANG_RUN_QUIET etc.; not raw getenv).
 * Why: hybrid still had argv head flags always-mega after wave205 fork-exec pure.
 * PLATFORM: SHARED orch / LINUX -B + harden + --gc-sections / APPLE -dead_strip.
 */

/* wave207: invoke_cc_append_argv_tail_flags pure orch lives in labi_invoke_cc_list
 * (-pthread/-lc/allow-multiple/user_extra+NULL inside xlang_invoke_cc_impl).
 * Cold twin via #include labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x.
 * Cap residual: asm_link_obj_skip_missing + link_abi_user_extra_o_{count,at} + push_existing + host_is_*.
 * Why: hybrid still had argv tail always-mega after wave206 head pure.
 * PLATFORM: SHARED orch / POSIX -pthread+-lc / WINDOWS allow-multiple.
 */

/* wave208: invoke_cc_append_minimal_cc_link_tail pure orch lives in labi_invoke_cc_list
 * (XLANG_MINIMAL_CC_LINK branch: Windows process_argv.o + POSIX -lc + NULL).
 * Cold twin via #include labi_invoke_cc_list.from_x.c above; hybrid FROM_X → L5 pure .x.
 * Cap residual: process_argv_o_path + push_existing + host_is_*.
 * wave225 G.7: MINIMAL gate uses link_abi_getenv (not raw getenv); host residual = _impl only.
 * Why: hybrid still had MINIMAL -lc/process_argv+NULL always-mega after wave207 always-tail pure.
 * PLATFORM: SHARED orch / WINDOWS process_argv / POSIX -lc only.
 */


/**
 * Cap residual (wave179 / wave215 / wave255): multi-slot realpath pool only.
 * Pure orch (wave215/255 labi_invoke_ld_list L6) owns null/empty + skip_missing;
 * _impl is always mega (static pool + host realpath).
 * (POSIX) realpath into multi-slot static pool so multiple pushes keep durable
 * pointers (single static slot would overwrite earlier argv).
 * Windows: skip realpath; return validated path as-is.
 * Pure push_existing owns capacity/dedup/append and calls the public resolve face.
 * Why (wave255): soft residual skip_missing still lived inside always-mega _impl.
 * wave261 G.7: pool slots filled via public pure thin link_abi_realpath_cap
 * (not raw libc realpath); host residual stays link_abi_realpath_cap_impl only.
 * PLATFORM: SHARED residual / POSIX realpath pool via face / WINDOWS no realpath.
 */
const char *invoke_cc_argv_resolve_existing_path_impl(const char *path) {
    static char abs_pool[INVOKE_CC_ABS_POOL_SZ][PATH_MAX];
    static int abs_pool_i;
    if (!path || !path[0])
        return NULL;
#if !defined(_WIN32) && !defined(_WIN64)
    /* PLATFORM: SHARED — never recycle slots still referenced by argv.
     * `% SZ` wrap made two argv entries alias one slot: CLI extra
     * `compiler/runtime_atomic_glue.o` + auto-pushed companion became
     * Darwin ld "duplicate symbol in the same .o twice". Ubuntu GNU ld
     * hid the hole. Full pool: keep caller's durable pointer. */
    if (abs_pool_i >= INVOKE_CC_ABS_POOL_SZ)
        return path;
    {
        char *slot = abs_pool[abs_pool_i];
        abs_pool_i++;
        /* wave261: face (gates + _impl), not raw realpath. */
        if (link_abi_realpath_cap(path, slot) != NULL)
            return slot;
    }
#endif
    /* Windows or realpath fail: return caller's durable path pointer as-is. */
    return path;
}

/* wave215/255: invoke_cc_argv_resolve_existing_path pure orch lives in labi_invoke_ld_list.x
 * (hybrid L6); mega cold twin via #include labi_invoke_ld_list.from_x.c under
 * #ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X. Pure: null/empty + skip_missing; Cap residual
 * _impl (pool only) always mega above. Why wave215: hybrid still had resolve_existing
 * body always mega C (gates+skip+pool). Why wave255: skip_missing moved to pure.
 * PLATFORM: SHARED orch. */
#ifdef XLANG_LABI_INVOKE_LD_LIST_FROM_X
const char *invoke_cc_argv_resolve_existing_path(const char *path);
#endif

/**
 * invoke_cc 子进程：仅当 path 指向已存在的 .o 时追加到 argv（可选 realpath）。
 * wave179: pure orch in labi_invoke_ld_list.x (hybrid L6);
 * mega cold twin under #ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X (include below).
 * Pure: gates + Cap residual resolve + pure cstr dedup + pure append.
 * Cap residual: invoke_cc_argv_resolve_existing_path (skip + multi-slot pool).
 * Why: hybrid still had always-mega C body for push_existing.
 * PLATFORM: SHARED.
 */
/* Body: cold twin via #include labi_invoke_ld_list.from_x.c; hybrid L6 pure .x. */
int invoke_cc_argv_push_existing(char *argv[], int *ia, int max_ia, const char *path);




/**
 * task.o 链入时须同时链入 scheduler.o；若调用方未显式传入则从 task_o 路径推导。
 * 参数：见 runtime_link_abi.h。
 * 返回值：scheduler .o 路径或 NULL。
 *
 * wave180: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: cstr copy + needle scan + expand rewrite; Cap residual path_readable + realpath_cap.
 * PLATFORM: SHARED orch — product PREFER uses L0 pure; cold path keeps this body.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler) {
    static char derived[PATH_MAX];
    static char cwd_buf[PATH_MAX];
    const char *from = "std/task/task.o";
    const char *to = "std/async/scheduler.o";
    char *pos;
    if (explicit_scheduler && explicit_scheduler[0])
        return explicit_scheduler;
    if (!task_o || !task_o[0])
        return NULL;
    if (strlen(task_o) >= sizeof(derived))
        return NULL;
    memcpy(derived, task_o, strlen(task_o) + 1);
    pos = strstr(derived, from);
    if (pos) {
        size_t tail = strlen(pos + strlen(from));
        memmove(pos + strlen(to), pos + strlen(from), tail + 1);
        memcpy(pos, to, strlen(to));
        if (xlang_path_access(derived, F_OK) == 0)
            return derived;
    }
    cwd_buf[0] = '\0';
    if (link_abi_realpath_cap("std/async/scheduler.o", cwd_buf) != NULL)
        return cwd_buf;
    return NULL;
}
#else
const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler);
#endif

/* P2 Darwin -o compress sibling: these two _impls share the one-slot
 * per-path cache defined later (UNDEF + T/t + all-names). Forward decls
 * so the public bodies can sit next to their wave210/211 comments. */
static int xlang_undef_cache_load(const char *o_path);
static int xlang_all_cache_has_substr(const char *needle);
static int xlang_undef_cache_has_substr(const char *needle);

/**
 * Cap residual (wave211): export-marker substring probe body.
 * Pure orch (labi_ondemand_list L8b) owns null/empty gates; _impl is always mega.
 * Params: obj_o / marker — caller pure already rejected null/empty (defense in depth here too).
 * Returns: 1 if any symbol name contains marker substring, else 0.
 *
 * P2 Darwin -o compress sibling: hello -o still spawned 11 full-nm after
 * UNDEF + T/t caches (3 markers + 8 UNDEF/prefix needles on one user.o).
 * G.7 complete: same mmap fills an all-names blob; lookup is in-process
 * strstr. Markers are data (`d`/`s`/`b`), not T/t — do not reuse the
 * defined blob. PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O;
 * nm once fallback. realpath via link_abi_realpath_cap (wave261);
 * Windows hybrid via tools (face null → use path as-is).
 */
int link_abi_obj_exports_marker_impl(const char *obj_o, const char *marker) {
    const char *use = obj_o;
    static char resolved[PATH_MAX];
    if (!obj_o || !obj_o[0] || !marker || !marker[0])
        return 0;
#if !defined(_WIN32) && !defined(_WIN64)
    /* wave261 G.7: link_abi_realpath_cap (not raw realpath). */
    if (link_abi_realpath_cap(obj_o, resolved) != NULL)
        use = resolved;
#endif
    if (!xlang_undef_cache_load(use))
        return 0;
    return xlang_all_cache_has_substr(marker);
}

/* wave211: link_abi_obj_exports_marker pure orch lives in labi_ondemand_list.x (hybrid L8b);
 * cold twin under #ifndef ONDEMAND_LIST_FROM_X in seeds/labi_ondemand_list.from_x.c
 * (mega #include when !FROM_X, or L8b cold seed object when pure .x fails).
 * Pure: null/empty gates; Cap residual link_abi_obj_exports_marker_impl
 * (all-names cache substring; same mmap as UNDEF/T/t) always mega.
 * Why: hybrid still had exports_marker body always mega C (gates+nm).
 * PLATFORM: SHARED orch. Do not define public twin here — would double-def with seed include. */
#ifdef XLANG_LABI_ONDEMAND_LIST_FROM_X
int link_abi_obj_exports_marker(const char *obj_o, const char *marker);
#endif




/**
 * Cap residual (wave210): UNDEF substring probe body.
 * Pure orch (labi_ondemand_list L8b) owns null/empty gates; _impl is always mega.
 * Params: obj_o / sym — caller pure already rejected null/empty (defense in depth here too).
 * Returns: 1 if any UNDEF name contains sym, else 0.
 *
 * Historical: popen full nm, require " U " and strstr(line, needle). Needles
 * are prefix (`ZSTD_` / `_ZSTD`) or Darwin-underscore exact (`_compress2`).
 * G.7 complete: substring over the UNDEF cache blob from the same mmap.
 * Darwin reconstructs one leading '_' so `_ZSTD` still hits stripped
 * `ZSTD_compress`; Linux does not (ELF nm has no '_', so `_compress2`
 * historically missed — do not "fix" that). PLATFORM: SHARED residual;
 * LINUX ELF / DARWIN Mach-O; nm once fallback. realpath via
 * link_abi_realpath_cap (wave261); Windows hybrid via tools.
 */
int link_abi_obj_has_undef_sym_impl(const char *obj_o, const char *sym) {
    const char *use = obj_o;
    static char resolved[PATH_MAX];
    if (!obj_o || !obj_o[0] || !sym || !sym[0])
        return 0;
#if !defined(_WIN32) && !defined(_WIN64)
    /* wave261 G.7: link_abi_realpath_cap (not raw realpath). */
    if (link_abi_realpath_cap(obj_o, resolved) != NULL)
        use = resolved;
#endif
    if (!xlang_undef_cache_load(use))
        return 0;
    return xlang_undef_cache_has_substr(sym);
}

/* wave210: link_abi_obj_has_undef_sym pure orch lives in labi_ondemand_list.x (hybrid L8b);
 * cold twin under #ifndef ONDEMAND_LIST_FROM_X in seeds/labi_ondemand_list.from_x.c
 * (mega #include when !FROM_X, or L8b cold seed object when pure .x fails).
 * Pure: null/empty gates; Cap residual link_abi_obj_has_undef_sym_impl
 * (UNDEF cache substring; same mmap as needs_undef) always mega.
 * Why: hybrid still had has_undef_sym body always mega C (gates+nm).
 * PLATFORM: SHARED orch. Do not define public twin here — would double-def with seed include. */
#ifdef XLANG_LABI_ONDEMAND_LIST_FROM_X
int link_abi_obj_has_undef_sym(const char *obj_o, const char *sym);
#endif




/*
 * wave131: compress family pure orch lives in labi_ondemand_list
 * (zlib/zstd/brotli marker + UNDEF/prefix tables + needs_compress_libs).
 * Cap residual: exports_marker pure thin (wave211; _impl Cap); has_undef_sym pure thin (wave210; _impl Cap);
 *   needs_undef_sym pure thin (wave212; _impl Cap).
 * Cold twin: #include labi_ondemand_list.from_x.c (below); hybrid FROM_X → L8b pure.
 * Forward decls: call sites below need symbols before the ondemand include block.
 * PLATFORM: SHARED.
 */
int link_abi_obj_needs_zlib(const char *obj_o);
int link_abi_obj_needs_zstd(const char *obj_o);
int link_abi_obj_needs_brotli(const char *obj_o);
int link_abi_user_o_needs_compress_libs(const char *user_o);

/* G-02f-275 L6 invoke_ld list pure */
#ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X
#include "seeds/labi_invoke_ld_list.from_x.c"
#else
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
/* wave156/157/158/179: pure orch in L6; file-top decl already covers call sites — restate for FROM_X block. */
void xlang_asm_ld_append_mach_tail_libs_impl(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    const char **argv, int *la, int max_la, int append_lsystem);
void xlang_asm_ld_append_unix_gcc_tail_libs_impl(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    int need_pt, const char **argv, int *la, int max_la);
int invoke_cc_append_net_tls_ld(char *argv[], int *i, int argv_cap, const char *net_o, const char *repo_root);
int invoke_cc_argv_push_existing(char *argv[], int *ia, int max_ia, const char *path);
/* wave187: ensure_std_net_o_auto_tls pure orch + helpers (L6). */
int labi_net_tls_buf_append(char *dst, int cap, int pos, const char *src);
int labi_net_tls_build_make_cmd(char *cmd, int cap, const char *repo_root, const char *target);
int labi_net_tls_join_repo_rel(char *path_buf, int cap, const char *repo_root, const char *rel);
void ensure_std_net_o_auto_tls(const char *repo_root);
#endif

/**
 * Cap residual (wave152): return 1 iff host is Apple (any arch).
 * PLATFORM: MACOS — #if defined(__APPLE__); Linux/Windows → 0.
 * Not the same as xlang_host_is_apple_aarch64 (arm64 only; host_lit L2).
 * Pure orch ld_append_brew_lib_paths gates brew -L append on this.
 * Always mega (both cold include path and hybrid FROM_X).
 */
int link_abi_host_is_apple(void) {
#if defined(__APPLE__)
    return 1;
#else
    return 0;
#endif
}

/* Cap residual host #if for wave198 invoke_cc_append_early_needs pure orch.
 * PLATFORM: WINDOWS — #if _WIN32|_WIN64|CYGWIN; Linux/macOS → 0.
 * Gates -lbcrypt / -lkernel32 / -lws2_32 (≡ mega historical #if blocks).
 * Always mega (both cold include path and hybrid FROM_X).
 */
int link_abi_host_is_windows(void) {
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    return 1;
#else
    return 0;
#endif
}

/* Cap residual host #if for wave169 ensure_runtime_panic pure orch.
 * PLATFORM: LINUX x86_64 — prefer src/asm/runtime_panic_x86_64.s (≡ mega historical gate).
 */
int link_abi_host_is_linux_x86_64(void) {
#if defined(__linux__) && (defined(__x86_64__) || defined(__amd64__))
    return 1;
#else
    return 0;
#endif
}

/* Cap residual host #if for wave169 ensure_runtime_panic pure orch.
 * PLATFORM: LINUX|MACOS aarch64 — prefer seeds/runtime_panic_arm64.from_x.c.
 */
int link_abi_host_is_posix_aarch64(void) {
#if (defined(__linux__) || defined(__APPLE__)) && (defined(__aarch64__) || defined(__arm64__))
    return 1;
#else
    return 0;
#endif
}

/* wave152: ld_append_brew_lib_paths pure orch lives in labi_invoke_ld_list
 * (table scan + Cap residual host_is_apple). Cold twin via #include
 * labi_invoke_ld_list.from_x.c above; hybrid FROM_X → L6 pure .x (decl in #else).
 * Why: hybrid still had always-mega C body for brew -L append.
 * PLATFORM: SHARED orch / MACOS consumers. */

/* wave153: asm_ld_append_compress_libs pure orch lives in labi_invoke_ld_list
 * (needs + ensure + path Cap). Cold twin via #include labi_invoke_ld_list.from_x.c
 * above; hybrid FROM_X → L6 pure .x (decl in #else).
 * Why: hybrid still had always-mega C body for asm compress -l* append.
 * PLATFORM: SHARED. */

/* wave154: invoke_cc_append_compress_ld pure orch lives in labi_invoke_ld_list
 * (needs + ensure + path Cap + pure push_existing / Cap residual resolve for glue).
 * Cold twin via #include labi_invoke_ld_list.from_x.c above; hybrid FROM_X → L6 pure
 * .x (decl in #else). Why: hybrid still had always-mega C body for invoke_cc compress.
 * Cap residual stays: invoke_cc_argv_resolve_existing_path (pure skip + pool residual; wave179/255).
 * PLATFORM: SHARED. */

/* wave156: xlang_asm_ld_append_mach_tail_libs_impl pure orch lives in labi_invoke_ld_list
 * (flags i32 layout + pure flag_* + peer compress orch + peer needs_compress).
 * Cold twin via #include labi_invoke_ld_list.from_x.c above; hybrid FROM_X → L6 pure
 * .x (decl in #else). Why: hybrid still had always-mega C body for mach tail -l*.
 * PLATFORM: SHARED orch / MACOS consumers. */

/* wave157: xlang_asm_ld_append_unix_gcc_tail_libs_impl pure orch lives in labi_invoke_ld_list
 * (flags i32 layout + pure flag_* + peer compress + peer host_is_linux + host_is_apple).
 * Cold twin via #include labi_invoke_ld_list.from_x.c above; hybrid FROM_X → L6 pure
 * .x (decl in #else). Why: hybrid still had always-mega C body for unix gcc tail -l*.
 * PLATFORM: SHARED orch / LINUX primary consumers. */

/* wave158: invoke_cc_append_net_tls_ld pure orch lives in labi_invoke_ld_list
 * (pure flag/marker/rel + peer append_openssl/mbedtls + Cap residual exports_marker
 *  + realpath_cap + rel_o_path + push_existing + host_is_apple for brew -L).
 * Cold twin via #include labi_invoke_ld_list.from_x.c above; hybrid FROM_X → L6 pure
 * .x (decl in #else). Why: hybrid still had always-mega C body for net_tls -L/-l.
 * Cap residual stays: ensure_std_net_o_auto_tls shell make via pure orch (wave187;
 * Cap residual getenv+system+realpath_cap+exports_marker).
 * PLATFORM: SHARED orch / MACOS brew -L consumers. */




/* wave178: link_abi_generated_c_contains_any_substr pure orch lives in
 * labi_freestanding_list (pure thin loop → pure contains_substr).
 * Was always-mega file-view multi-needle memcmp. Cold twin under
 * #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * Empty needles skipped (family align; not mega empty→1). PLATFORM: SHARED.
 */
int link_abi_generated_c_contains_any_substr(const char *c_path, const char **needles,
                                            int n_needles);




/**
 * Cap residual (wave175): return 1 iff data[0..data_len) contains needle as raw bytes.
 * Null/empty needle → 0; empty data with nonempty needle → 0.
 * Pure orch link_abi_generated_c_contains_substr loads the file then calls this.
 * PLATFORM: SHARED — host memcmp loop; always mega (cold + hybrid FROM_X).
 */
int link_abi_buf_contains_substr(const char *data, size_t data_len, const char *needle) {
    size_t nlen;
    size_t off;
    if (!data || !needle || !needle[0])
        return 0;
    nlen = strlen(needle);
    if (nlen == 0 || data_len < nlen)
        return 0;
    for (off = 0; off + nlen <= data_len; off++) {
        if (memcmp(data + off, needle, nlen) == 0)
            return 1;
    }
    return 0;
}

/* wave175: link_abi_generated_c_contains_substr pure orch lives in labi_freestanding_list
 * (pure null gates + Cap residual file malloc/free + Cap residual buf_contains_substr).
 * Was always-mega thin wrap over contains_any_substr (file view). Cold twin under
 * #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * Not the same as contains_substr_use_line (line-filter Cap residual).
 * PLATFORM: SHARED — dual-end L2.
 */
int link_abi_generated_c_contains_substr(const char *c_path, const char *needle);

/**
 * Cap residual (wave176): return 1 iff data[0..data_len) contains needle on a
 * "use" line — not bare `extern` / `#define` / comment / struct|typedef name /
 * placeholder / `__attribute__((weak))` preamble stubs.
 * Why: rt_preamble injects `extern ... std_context_background(` and
 * `#define std_net_*`; raw substr would false-link context/net on hello.
 * Pure orch link_abi_generated_c_contains_substr_use_line loads the file then
 * calls this. Nested line-filter scan stays mega (codegen truncates pure deep
 * while over large buffers in freestanding module — same lesson as wave175).
 * PLATFORM: SHARED — host memcmp/line walk; always mega (cold + hybrid FROM_X).
 */
int link_abi_buf_contains_substr_use_line(const char *data, size_t data_len, const char *needle) {
    size_t needle_len;
    size_t off;
    if (!data || !needle || !needle[0])
        return 0;
    needle_len = strlen(needle);
    if (needle_len == 0 || data_len < needle_len)
        return 0;
    for (off = 0; off + needle_len <= data_len; off++) {
        size_t line_start;
        size_t line_end;
        size_t k;
        int is_extern = 0;
        int is_define = 0;
        int is_comment = 0;
        if (memcmp(data + off, needle, needle_len) != 0)
            continue;
        line_start = off;
        while (line_start > 0 && data[line_start - 1] != '\n')
            line_start--;
        line_end = off + needle_len;
        while (line_end < data_len && data[line_end] != '\n')
            line_end++;
        /* Skip leading whitespace then classify extern / #define / // / block-comment. */
        k = line_start;
        while (k < line_end && (data[k] == ' ' || data[k] == '\t'))
            k++;
        if (k + 6 <= line_end && memcmp(data + k, "extern", 6) == 0)
            is_extern = 1;
        if (k < line_end && data[k] == '#') {
            size_t k2 = k + 1;
            while (k2 < line_end && (data[k2] == ' ' || data[k2] == '\t'))
                k2++;
            if (k2 + 6 <= line_end && memcmp(data + k2, "define", 6) == 0)
                is_define = 1;
        }
        if (k + 2 <= line_end && data[k] == '/' && data[k + 1] == '/')
            is_comment = 1;
        if (k + 2 <= line_end && data[k] == '/' && data[k + 1] == '*')
            is_comment = 1;
        /*
         * PLATFORM: SHARED — preamble type decls (struct/typedef std_net_*) are NOT real refs.
         * But variable decls like "struct Foo x = std_net_listen(...)" ARE real refs: the needle
         * is the function call (std_net_listen), not the struct name (Foo). The legacy check
         * "line-startswith struct/typedef" falsely skipped such lines → need_net=0 → net.o not
         * pushed → BLD001 undefined _std_net_listen.
         * Root (2026-07-19): distinguish tag name vs call-site needle.
         * Bug (2026-08-10 L4 Mac run-backtrace): walking whitespace then checking
         * memcmp(p-7,"struct ") FAILED for the common form `struct std_string_String`
         * because the single space of "struct " was consumed by the walk-back, leaving
         * p on the last letter of "struct" (p-7 no longer points at "struct "). Result:
         * need_string/map/error=1 from preamble alone → formals co-emitting core_mem_*
         * linked together with -Wl,-export_dynamic (backtrace) → 33 duplicate symbols
         * (dead_strip cannot drop them). G.7: walk back ws then match keyword *without*
         * trailing space; require p < off (at least one ws between keyword and needle).
         */
        {
            size_t p = off;
            while (p > line_start && (data[p - 1] == ' ' || data[p - 1] == '\t'))
                p--;
            /* Tag form: "struct" + ws + needle  or  "typedef" + ws + needle. */
            if (p < off) {
                if (p >= line_start + 6 && memcmp(data + p - 6, "struct", 6) == 0) {
                    /* Boundary: start-of-line or non-ident before "struct". */
                    if (p == line_start + 6 ||
                        !((data[p - 7] >= 'A' && data[p - 7] <= 'Z') ||
                          (data[p - 7] >= 'a' && data[p - 7] <= 'z') ||
                          (data[p - 7] >= '0' && data[p - 7] <= '9') ||
                          data[p - 7] == '_'))
                        is_extern = 1;
                }
                if (p >= line_start + 7 && memcmp(data + p - 7, "typedef", 7) == 0) {
                    if (p == line_start + 7 ||
                        !((data[p - 8] >= 'A' && data[p - 8] <= 'Z') ||
                          (data[p - 8] >= 'a' && data[p - 8] <= 'z') ||
                          (data[p - 8] >= '0' && data[p - 8] <= '9') ||
                          data[p - 8] == '_'))
                        is_extern = 1;
                }
            }
        }
        /* Skip weak placeholder bodies only when this line contains "placeholder". */
        {
            size_t li;
            for (li = k; li + 11 <= line_end; li++) {
                if (memcmp(data + li, "placeholder", 11) == 0) {
                    is_extern = 1;
                    break;
                }
            }
        }
        /*
         * PLATFORM: SHARED — skip rt_preamble weak stub bodies.
         * Preamble always emits weak process_args_* → process_xlang_* (and similar).
         * Counting those as "use" forced every -o to ensure runtime_process_argv.o
         * (pure rv/hello residual). Real user calls are non-weak use_lines.
         * G.7: complete use_line authority; no second skip table for process only.
         */
        {
            size_t li;
            /* "__attribute__((weak))" is 21 chars */
            for (li = k; li + 21 <= line_end; li++) {
                if (memcmp(data + li, "__attribute__((weak))", 21) == 0) {
                    is_extern = 1;
                    break;
                }
            }
        }
        if (!is_extern && !is_define && !is_comment)
            return 1;
    }
    return 0;
}

/* wave176: link_abi_generated_c_contains_substr_use_line pure orch lives in
 * labi_freestanding_list (pure null gates + Cap residual file malloc/free +
 * Cap residual buf_contains_substr_use_line). Was always-mega file-view scan.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED.
 */
int link_abi_generated_c_contains_substr_use_line(const char *c_path, const char *needle);

/* wave177: link_abi_generated_c_contains_any_substr_use_line pure orch lives in
 * labi_freestanding_list (pure thin loop → pure contains_substr_use_line).
 * Was always-mega thin loop. Cold twin under #ifndef FREESTANDING_LIST_FROM_X;
 * hybrid L7 pure .x. Product: net_api / crypto_api on-demand. PLATFORM: SHARED.
 */
int link_abi_generated_c_contains_any_substr_use_line(const char *c_path, const char **needles,
                                                     int n_needles);


/*
 * wave117: needs_libc_heap / freestanding_nostdlib_face pure orch live in
 * labi_freestanding_list (tables + orch). Full-seed path: bodies via #include above
 * (!FROM_X). Hybrid FROM_X: L7 pure .x provides; decls in #else of freestanding include.
 * wave136: link_abi_generated_c_needs_{fs,random,time,runtime} pure orch same L7
 * wave137: link_abi_generated_c_needs_{zlib,zstd,brotli} pure orch same L7
 * wave138: link_abi_generated_c_needs_{core_slice,db_kv,db_arrow} pure orch same L7
 * wave139: link_abi_generated_c_provides_{core_mem,std_heap} pure orch same L7
 * (C-path PRIMARY OS/fs string needles; Cap residual contains_substr).
 * Cap residual: contains_substr / undef_sym stay mega. PLATFORM: SHARED.
 */
/* (definitions: seeds/labi_freestanding_list.from_x.c or L7 pure .x) */

/**
 * PLATFORM: LINUX — path to bootstrap_nostdlib_stubs.o (mmap bump malloc/free face).
 * Same object as compiler nostdlib bag; freestanding user link pulls it on demand.
 * wave181: pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Cap residual: link_abi_realpath_cap + xlang_resolve_compiler_dir (pure owns leaf join).
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_bootstrap_nostdlib_stubs_o_path(const char *argv0) {
    static char buf[PATH_MAX];
    static char resolved[PATH_MAX];
    char comp_dir[PATH_MAX];
    int nn;
    buf[0] = resolved[0] = '\0';
    if (link_abi_realpath_cap("compiler/src/asm/bootstrap_nostdlib_stubs.o", resolved) != NULL)
        return resolved;
    if (xlang_resolve_compiler_dir(argv0, comp_dir, sizeof comp_dir) == 0) {
        nn = snprintf(buf, sizeof buf, "%s/src/asm/bootstrap_nostdlib_stubs.o", comp_dir);
        if (nn > 0 && (size_t)nn < sizeof buf) {
            if (link_abi_realpath_cap(buf, resolved) != NULL)
                return resolved;
            return buf;
        }
    }
    return buf;
}
#else
const char *xlang_bootstrap_nostdlib_stubs_o_path(const char *argv0);
#endif

/**
 * PLATFORM: LINUX — ensure bootstrap_nostdlib_stubs.o exists (cc seed if missing).
 * G.7: one face for freestanding malloc (page-backed), shared with compiler nostdlib bag.
 * wave182: pure orch in labi_ensure_list.x (hybrid L4);
 * mega cold twin under #ifndef XLANG_LABI_ENSURE_LIST_FROM_X (#include above).
 * Cap residual: resolve/access/cc_one_extra(-fno-builtin)/stat (no system() Cap path).
 */
#ifndef XLANG_LABI_ENSURE_LIST_FROM_X
/* cold twin body is in seeds/labi_ensure_list.from_x.c (#include above). */
#else
int xlang_ensure_bootstrap_nostdlib_stubs_o(const char *argv0);
#endif

/* wave141: link_abi_generated_c_needs_win32 pure orch lives in labi_freestanding_list
 * (9 needles + pure scan; Cap residual contains_substr). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED orch / WINDOWS consumers — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_needs_win32(const char *c_path);

/* wave141: link_abi_generated_c_needs_win32_wsa pure orch (L7 freestanding).
 * Why: F-02 v2 on-demand -lws2_32; no win32_net.inc.c.
 */
int link_abi_generated_c_needs_win32_wsa(const char *c_path);

/* wave142: link_abi_generated_c_needs_core_builtin pure stub0 orch lives in
 * labi_freestanding_list (always 0; G-01 no hard-link builtin.o). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_needs_core_builtin(const char *c_path);

/* wave142: link_abi_generated_c_needs_core_mem pure stub0 orch (L7 freestanding).
 * G-01: pure .x mem; never hard-link core/mem/mem.o from C-path scan.
 */
int link_abi_generated_c_needs_core_mem(const char *c_path);

/**
 * 产品轨 std 模块：预编 std/*.o 为符号权威时，禁止 pipeline co-emit 函数体。
 * 与 ast_pool pipeline_codegen_std_dep_link_only 同形；放 link_abi 保证产品二进制必有符号
 * （Darwin 上 pipeline_x.o 与 glue standalone 双定义时 glue 可能未胜出）。
 */
int pipeline_codegen_std_dep_link_only(uint8_t *path) {
  static const char *const k[] = {
      "std.base64", "std.json", "std.csv", "std.heap", "std.heap.libc", "std.http",
      "std.crypto", "std.encoding", "std.log", "std.net", "std.regex",
      /* 勿 link_only std.unicode：unicode.o 为 std.unicode.unicode 内部符号
       *（std_unicode_unicode_*），与 mod.x API（std_unicode_category）不一致；
       * co-emit mod 再导出 + unicode.x 体为权威。 */
      "std.dynlib", "std.tar",
      /* 勿 link_only std.channel / std.backtrace：*.o 仅为 marker，API 在 mod.x 包装
       * channel_i32_*_c / backtrace_*_c（runtime_*_glue / platform）。 */
      "std.atomic", "std.sync", "std.thread",
      "std.time", "std.random",
      /* 勿 link_only std.env：C 路径仍可 co-emit mod；formal env.o 现为
       * mod.x（std_env_*）+ runtime_env_os.o（env_*_c），asm 由 fk0 按需推入。 */
      "std.math", "std.hash",
      /* 勿 link_only std.sort：C 路径仍可 co-emit mod；formal sort.o 现为
       * mod.x+sort.x（std_sort_sort_*），asm 由 fk0 探针按需推入。 */
      "std.ffi",
      "std.db", "std.test",
      /* 勿 link_only std.compress：纯 .x、无 compress.o；link_only 只留 extern → 未定义符号 */
      /* set/map/queue/vec：预编 .o 权威；-o co-emit 重载/布局易与 preamble 漂移 */
      "std.set", "std.map", "std.queue", "std.vec",
      /* path：path.o = runtime_path_fast 权威；co-emit mod.x 再链 path.o → duplicate */
      "std.path",
      /* error：error.o 权威；co-emit 现仅 extern，须链 .o 补符号 */
      "std.error",
      /* context：context.o (mod.x + context.x) 权威；co-emit mod.x 的 deadline_ns/with_deadline
       * etc. 与 context.o 强符号 duplicate（net-context gate 红）。G.7 single authority. */
      "std.context",
      /* std.simd：simd.o = formal_surface.c (f32x4/i32x8 mangle) 权威；co-emit mod.x
       * overload CALL 在 Ubuntu pure .x 易选错 mul(Vec8i) → dot 算错 / BLD001。
       * PLATFORM: SHARED — STD-SIMD-INTRINSIC product gate. */
      "std.simd", NULL};
  int i;
  size_t n;
  size_t plen;
  if (!path || !path[0])
    return 0;
  /* 安全取长：dep path 缓冲可能无尾 0（仅靠 len）；仍兼容 C 字符串 */
  plen = 0;
  while (plen < 64 && path[plen] != 0)
    plen++;
  for (i = 0; k[i]; i++) {
    n = strlen(k[i]);
    if (n > plen)
      continue;
    if (memcmp(path, k[i], n) == 0 && (n == plen || path[n] == '.' || path[n] == 0)) {
      /* wave225 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
      /* Cap residual 9.5.3 slice3b: debug trace via xlang_snprintf + raw fd 2. */
      if (link_abi_getenv("XLANG_DEBUG_PIPE")) {
        char _db[256];
        int _dn = snprintf(_db, sizeof _db,
                           "xlang: [link_only] hit exact/prefix key=%s path=%s -> 1\n", k[i], path);
        if (_dn > 0)
          (void)xlang_io_write(2, _db, (size_t)_dn);
      }
      return 1;
    }
  }
  /* 前缀兜底：std.heap* / std.json* 等 */
  if (plen >= 8 && memcmp(path, "std.heap", 8) == 0)
    return 1;
  if (plen >= 8 && memcmp(path, "std.json", 8) == 0)
    return 1;
  if (plen >= 7 && memcmp(path, "std.csv", 7) == 0)
    return 1;
  if (plen >= 10 && memcmp(path, "std.base64", 10) == 0)
    return 1;
  /* Cap residual 9.5.3 slice3b: debug trace via xlang_snprintf (%zu now
   * supported by the 10.7.2 fmt authority) + raw fd 2. */
  if (link_abi_getenv("XLANG_DEBUG_PIPE")) {
    char _db[256];
    int _dn = snprintf(_db, sizeof _db, "xlang: [link_only] miss path=%s plen=%zu -> 0\n", path, plen);
    if (_dn > 0)
      (void)xlang_io_write(2, _db, (size_t)_dn);
  }
  return 0;
}

/* wave139: link_abi_generated_c_provides_core_mem pure orch lives in labi_freestanding_list
 * (3 definition-line needles + pure scan; Cap residual contains_substr). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * Why: co-emit core_mem_* bodies in user TU; hard-link mem.o → duplicate.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_provides_core_mem(const char *c_path);

/* wave139: link_abi_generated_c_provides_std_heap pure orch (L7 freestanding).
 * Why: co-emit heap_libc bodies; hard-link heap.o → duplicate.
 */
int link_abi_generated_c_provides_std_heap(const char *c_path);

/* wave138: link_abi_generated_c_needs_db_kv pure orch lives in labi_freestanding_list
 * (7 needles + pure scan; Cap residual contains_substr). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_needs_db_kv(const char *c_path);

/* wave138: link_abi_generated_c_needs_db_arrow pure orch (L7 freestanding). */
int link_abi_generated_c_needs_db_arrow(const char *c_path);

/* wave138: link_abi_generated_c_needs_core_slice pure orch (L7 freestanding). */
int link_abi_generated_c_needs_core_slice(const char *c_path);


/* wave136: link_abi_generated_c_needs_fs pure orch lives in labi_freestanding_list
 * (5 needles + pure scan; Cap residual contains_substr). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_needs_fs(const char *c_path);

/* wave137: link_abi_generated_c_needs_zlib pure orch lives in labi_freestanding_list
 * (7 needles + pure scan; Cap residual contains_substr). Was mega body.
 * Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_generated_c_needs_zlib(const char *c_path);

/* wave137: link_abi_generated_c_needs_zstd pure orch (L7 freestanding). */
int link_abi_generated_c_needs_zstd(const char *c_path);

/* wave137: link_abi_generated_c_needs_brotli pure orch (L7 freestanding). */
int link_abi_generated_c_needs_brotli(const char *c_path);

/* wave136: link_abi_generated_c_needs_random pure orch (L7 freestanding). */
int link_abi_generated_c_needs_random(const char *c_path);

/* wave136: link_abi_generated_c_needs_time pure orch (L7 freestanding). */
int link_abi_generated_c_needs_time(const char *c_path);

/* wave136: link_abi_generated_c_needs_runtime pure orch (L7 freestanding). */
int link_abi_generated_c_needs_runtime(const char *c_path);

/* wave143: xlang_generated_c_needs_async_scheduler pure orch lives in
 * labi_freestanding_list (9 needles + pure scan; Cap residual contains_substr).
 * Was mega body with hard-coded strings. Cold twin under
 * #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
int xlang_generated_c_needs_async_scheduler(const char *c_path);
/** G-02f-47/65：path 为已存在且 size>0 的常规文件。stat 在 _impl；.x 门闩。 */
/* G-02f-270/L L3 path IO：stat 主体始终在 rest（与 gates _impl 同构）；
 * 公共 thin shell 由 labi_path_io seed/.x 在 XLANG_LABI_PATH_IO_FROM_X 时提供。 */
int xlang_path_is_nonempty_regular_file_impl(const char *path) {
    struct stat st;
    if (!path || !path[0])
        return 0;
    /* Cap residual 9.1.2: newfstatat/fstatat, not libc stat. */
    if (xlang_path_stat(path, &st) != 0 || !S_ISREG(st.st_mode))
        return 0;
    if (st.st_size <= 0)
        return 0;
    return 1;
}


/* G-02f-270 L3 path IO */
#ifndef XLANG_LABI_PATH_IO_FROM_X
int xlang_path_is_nonempty_regular_file(const char *path) {
  if (path == NULL) {
    return 0;
  }
  if (path[0] == 0) {
    return 0;
  }
  {
    return xlang_path_is_nonempty_regular_file_impl(path);
  }
  return 0;
}
#else
int xlang_path_is_nonempty_regular_file(const char *path);
#endif


/* G-02f-270 L3 path IO */
#ifndef XLANG_LABI_PATH_IO_FROM_X
const char *asm_link_obj_skip_missing(const char *path) {
  if ((path ==NULL)) {
    return NULL;
  }
  (void)(({   {
    if (((path)[0] ==0)) {
      return NULL;
    }
    if ((xlang_path_is_nonempty_regular_file(path) ==0)) {
      return NULL;
    }
    return path;
  }
 }));
  return NULL;
}
#else
const char *asm_link_obj_skip_missing(const char *path);
#endif


/* F-06 v1 前向声明：invoke_cc 按需链入 heap.o 时复用 ASM 后端检测逻辑 */
int link_abi_user_o_needs_std_heap_api(const char *user_o);
int link_abi_user_o_needs_heap_user_syms(const char *user_o);
int link_abi_user_o_needs_async_scheduler(const char *user_o);
/* wave145 aggregate pure orch (L8b ondemand); always forward decl before call sites. */
int link_abi_link_needs_heap_user_c(const char *user_o, const char **argv, int la);
int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la);

/* ============================================================================
 * User-specified .o files from command line (single authority, G.3/G.4 / G.7).
 *
 * Why: `xlang -o exe file.x extra.o` drops extra.o because:
 *   - C path: xlang_invoke_cc takes a fixed variadic list of std/core .o paths
 *   - ASM path: xlang_invoke_ld_for_exe only receives the temp user object, not
 *     CLI extra .o (e.g. runtime_atomic_glue.o, runtime_time_os.o)
 * Authority: this global + setter/clearer is the SINGLE path for user .o files
 *   to reach BOTH link lines (cc and asm ld). Historical name says "cc" but
 *   G.7 forbids a second parallel table — asm ld consumes the same globals.
 * Callers wrap invoke_cc OR invoke_ld with set/clear:
 *     xlang_invoke_cc_set_user_o_files_from_argv(argc, argv);
 *     xlang_invoke_cc(...)  OR  xlang_invoke_ld_for_exe(...);
 *     xlang_invoke_cc_clear_user_o_files();
 * Invariant: g_xlang_n_user_extra_o_files == 0 means no user .o (safe default).
 * PLATFORM: SHARED — argv is plain char**; macOS/Linux/Windows.
 * ========================================================================== */
#define XLANG_USER_EXTRA_O_FILES_MAX 32
static const char *g_xlang_user_extra_o_files[XLANG_USER_EXTRA_O_FILES_MAX];
static int g_xlang_n_user_extra_o_files = 0;

/**
 * Cap residual (wave151): CLI user-extra .o table size (globals stay mega).
 * Pure orch: xlang_asm_ld_append_user_extra_o_files walks count/at + path_readable.
 * PLATFORM: SHARED — single authority table for cc + asm ld.
 */
int link_abi_user_extra_o_count(void) {
    return g_xlang_n_user_extra_o_files;
}

/**
 * Cap residual (wave151): CLI user-extra .o path at index (null if OOB / unset).
 * No copy — pointer lifetime is the driver argv covering the subsequent spawn.
 * PLATFORM: SHARED.
 */
const char *link_abi_user_extra_o_at(int i) {
    if (i < 0 || i >= g_xlang_n_user_extra_o_files)
        return NULL;
    return g_xlang_user_extra_o_files[i];
}

/**
 * Cap residual (wave151 / wave209 + 9.1.2): host access R_OK == 0 → 1.
 * Pure orch (wave209 labi_path_io L3) owns null/empty gates; _impl is always mega.
 * PLATFORM: SHARED — Linux faccessat Cap residual; Darwin libc access.
 */
int link_abi_path_readable_impl(const char *path) {
    if (!path || !path[0])
        return 0;
    return xlang_path_access(path, R_OK) == 0 ? 1 : 0;
}

/* wave209: link_abi_path_readable pure orch lives in labi_path_io.x (hybrid L3);
 * mega cold twin under #ifndef XLANG_LABI_PATH_IO_FROM_X.
 * Pure: null/empty gates; Cap residual link_abi_path_readable_impl (access R_OK).
 * Why: hybrid still had path_readable body always mega C (gates+access).
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_PATH_IO_FROM_X
int link_abi_path_readable(const char *path) {
    if (!path || !path[0])
        return 0;
    return link_abi_path_readable_impl(path);
}
#else
int link_abi_path_readable(const char *path);
#endif

/**
 * Cap residual (wave221 + 9.1.2): host access X_OK == 0 → 1.
 * Pure orch (wave221 labi_path_io L3) owns null/empty gates; _impl is always mega.
 * PLATFORM: SHARED — Linux faccessat Cap residual; Darwin libc access.
 * Product host binary probe (formal_std XLANG / compiler/{xlang_asm,xlang,xlang-c}).
 */
int link_abi_path_executable_impl(const char *path) {
    if (!path || !path[0])
        return 0;
    return xlang_path_access(path, X_OK) == 0 ? 1 : 0;
}

/* wave221: link_abi_path_executable pure orch lives in labi_path_io.x (hybrid L3);
 * mega cold twin under #ifndef XLANG_LABI_PATH_IO_FROM_X.
 * Pure: null/empty gates; Cap residual link_abi_path_executable_impl (access X_OK).
 * Why: hybrid still had formal_std raw access(path, X_OK) under product ensure.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_PATH_IO_FROM_X
int link_abi_path_executable(const char *path) {
    if (!path || !path[0])
        return 0;
    return link_abi_path_executable_impl(path);
}
#else
int link_abi_path_executable(const char *path);
#endif

/**
 * Append CLI user .o paths (g_xlang_user_extra_o_files) onto an asm ld argv.
 * wave151：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: Cap residual table count/at + path_readable + pure append loop.
 * Cap residual: link_abi_user_extra_o_count / link_abi_user_extra_o_at / link_abi_path_readable.
 * PLATFORM: SHARED — same authority as invoke_cc push loop; skip unreadable paths.
 * Call immediately before terminating argv with NULL on every asm ld branch.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
void xlang_asm_ld_append_user_extra_o_files(const char **argv, int *la, int max_la) {
    int ui;
    int n;
    if (!argv || !la)
        return;
    n = link_abi_user_extra_o_count();
    for (ui = 0; ui < n; ui++) {
        const char *p = link_abi_user_extra_o_at(ui);
        if (!p || !p[0])
            continue;
        if (*la >= max_la - 1)
            break;
        if (!link_abi_path_readable(p))
            continue;
        /* G.7: skip extra .o already on argv (auto companion / earlier extra).
         * has_obj is realpath-equal so relative CLI spelling matches
         * `{compiler_dir}/runtime_*.o`. Cold sat try-r1 compiles this mega
         * TU without FROM_X and overwrites prefer .x; L4 product is this body.
         * PLATFORM: SHARED — Darwin ld rejects the same .o twice; Ubuntu GNU ld hid it. */
        if (link_abi_asm_ld_argv_has_obj(argv, *la, p))
            continue;
        argv[(*la)++] = p;
    }
}
#else
void xlang_asm_ld_append_user_extra_o_files(const char **argv, int *la, int max_la);
#endif

/**
 * Cap residual (wave189): reset CLI user-extra .o table (globals stay mega).
 * Pure orch: xlang_invoke_cc_set_user_o_files_from_argv / clear walk argv then push/reset.
 * PLATFORM: SHARED — single authority table for cc + asm ld.
 */
void link_abi_user_extra_o_reset(void) {
    g_xlang_n_user_extra_o_files = 0;
}

/**
 * Cap residual (wave189): push one CLI user-extra .o path pointer (no copy).
 * @return 1 stored, 0 rejected (null/empty/full).
 * PLATFORM: SHARED.
 */
int link_abi_user_extra_o_push(const char *p) {
    if (!p || !p[0])
        return 0;
    if (g_xlang_n_user_extra_o_files >= XLANG_USER_EXTRA_O_FILES_MAX)
        return 0;
    g_xlang_user_extra_o_files[g_xlang_n_user_extra_o_files++] = p;
    return 1;
}

/**
 * Extract .o file args from argv into user-extra table.
 * wave189：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: option skip + .o suffix scan; Cap residual reset/push.
 * PLATFORM: SHARED — argv lifetime covers subsequent invoke_cc/ld.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
void xlang_invoke_cc_set_user_o_files_from_argv(int argc, char **argv) {
    int i;
    link_abi_user_extra_o_reset();
    if (!argv)
        return;
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        size_t len;
        if (!a || !a[0])
            continue;
        if (a[0] == '-') {
            /* Two-token options: skip the value arg too. */
            if ((!strcmp(a, "-o") || !strcmp(a, "-L") || !strcmp(a, "-I") ||
                 !strcmp(a, "-target") || !strcmp(a, "-backend") ||
                 !strcmp(a, "-O") || !strcmp(a, "-opt")) && i + 1 < argc) {
                i++; /* consume value */
            }
            continue;
        }
        len = strlen(a);
        if (len >= 2 && a[len - 2] == '.' && a[len - 1] == 'o')
            (void)link_abi_user_extra_o_push(a);
    }
}

/* Reset user .o state. Call after xlang_invoke_cc to prevent stale pointers. */
void xlang_invoke_cc_clear_user_o_files(void) {
    link_abi_user_extra_o_reset();
}
#else
void xlang_invoke_cc_set_user_o_files_from_argv(int argc, char **argv);
void xlang_invoke_cc_clear_user_o_files(void);
#endif

/**
 * 调用系统 cc 将多个 C 文件编译链接为可执行文件（parent 建 argv + pure spawn/strip）。
 * 参数：c_paths/n 源文件；各 *_o 可选 std/core .o；include_root 用于 -I 与按需 .o 解析。
 * 返回值：0 成功，-1 失败。
 * wave205: fork/exec/wait/strip 壳迁 pure（invoke_cc_run_cc_argv + maybe_strip_out）；
 * wave206: argv 头 flags 迁 pure（invoke_cc_append_argv_head_flags）；
 * wave207: argv 尾 flags 迁 pure（invoke_cc_append_argv_tail_flags：pthread/-lc/allow-multiple/user_extra+NULL）；
 * wave208: MINIMAL_CC_LINK 尾迁 pure（invoke_cc_append_minimal_cc_link_tail：Win process_argv + POSIX -lc + NULL）；
 *   Cap residual xlang_spawn_sync_impl / invoke_cc_strip_out_x_impl / getenv quiet·MINIMAL / skip_missing / user_extra count·at。
 *
 * Stage 12.2.3 defense-in-depth (G.7): invoke_cc_host_cc_spawn_gate runs at the top of
 * this residual *before* argv head / early_needs / ensure-push / need-gated TLS ensure.
 * Entry wrappers (labi_gates / monofile twin / surface) already early-gate; this isolates
 * the Cap residual body so a direct call to xlang_invoke_cc_impl cannot ensure or build
 * host-cc argv without ALLOW. spawn shell still re-checks the same gate authority.
 * PLATFORM: SHARED — product default deny; experimental XLANG_ALLOW_HOST_CC=1 only.
 *
 * Stage 12.2.3 ALLOW-path ensure slim (G.7 need gate):
 *   · ensure_std_net_o_auto_tls: NOT at entry; only after need scan when need_flags[5] (net).
 *     MINIMAL_CC_LINK skips std ensure-push and never runs TLS ensure.
 *   · heap.o: NOT always-push in ensure-push front when path non-empty; authority is
 *     invoke_cc_append_heap_f06_ondemand (nm argv + use_line + provides + page_mmap).
 *   · early_needs random/time/runtime: only under MINIMAL_CC_LINK (freestanding scan).
 *     Full ALLOW path: ensure-push front need_flags[8/7/4] is sole authority (use_line).
 * Mirrors time_os policy (ensure only under need_*, never warm-tree pre-ensure).
 */
int xlang_invoke_cc_impl(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o, const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o, const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o, const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o, const char *cli_o, const char *security_o, const char *config_o, const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o, const char *test_o, const char *include_root, const char *async_scheduler_o) {
    (void)target;
    (void)json_o;
    (void)csv_o;
    (void)log_o;
    /* #region debug-point B:invoke-cc-enter */
    xlang_debug_hello_stage1_report("B", "runtime_link_abi.c:2954", "invoke_cc_enter", n, use_lto, (include_root && include_root[0]) ? 1 : 0);
    /* #endregion */
    if (!c_paths || n < 1) return -1;
    if (!opt_level || !*opt_level) opt_level = "2";
    /*
     * PLATFORM: SHARED — isolate ensure/argv behind G.7 host-cc spawn gate.
     * Must precede argv / early_needs / ensure-push / need-gated TLS ensure work.
     * Same authority as entry wrappers and invoke_cc_run_cc_argv;
     * deny emits host-cc-requires-allow | forbid-host-cc.
     */
    if (!invoke_cc_host_cc_spawn_gate())
        return -1;
    /*
     * PLATFORM: SHARED — do NOT pre-ensure runtime_time_os.o merely because
     * std/time/time.o exists on a warm tree. That forced every pure rv/hello
     * C link (and Darwin paths that still hit invoke_cc) to rebuild time_os.
     * Authority: ensure only under need_time (below) + ASM PRIMARY/on_demand
     * gated by labi_user_needs_runtime_time_os. G.7 complete existing need path.
     *
     * Same policy for ensure_std_net_o_auto_tls: never pre-ensure at ALLOW entry;
     * only after need scan when need_net (see below). MINIMAL skips entirely.
     *
     * wave205: build argv in parent, then pure invoke_cc_run_cc_argv (spawn_sync
     * candidates) + invoke_cc_maybe_strip_out. No fork-first child argv build.
     * wave206: argv head flags pure (quiet/O/native/NDEBUG/flto/harden/gc/-I).
     * wave207: argv tail pure (-pthread/-lc/allow-multiple/user_extra+NULL).
     * wave208: MINIMAL_CC_LINK tail pure (Win process_argv + POSIX -lc + NULL).
     */
    /* 容量须容纳：cc -O -std... [-DNDEBUG] [-flto] -o out [-I inc] + n 个 .c + 若干 .o + -pthread -lc + XLANG_CC_EXTRA(至多 8) + NULL */
    char *argv[XLANG_INVOKE_CC_MAX_C_FILES + 48];
    int i = 0;
    const int argv_cap = XLANG_INVOKE_CC_MAX_C_FILES + 48;
    /* wave206 pure: argv head (cc, std, quiet, -B, -O level, native, NDEBUG, flto, harden, -o, sections, gc, -I). */
    invoke_cc_append_argv_head_flags(argv, &i, argv_cap, out_path, opt_level, use_lto, include_root);
    for (int j = 0; j < n && i < XLANG_INVOKE_CC_MAX_C_FILES + 8; j++)
        argv[i++] = (char *)c_paths[j];
    /* wave198: early needs scan+push pure orch (L5 invoke_cc_list).
     * G.7 compose peer needs/rel/push/ensure/path + host_is_* platform gates.
     * wave205: fork/exec shell pure after argv complete. */
    invoke_cc_append_early_needs(argv, &i, argv_cap, c_paths, n, include_root,
        random_o, time_o, runtime_o, runtime_panic_o);
    /* CORE-009 / Docker musl：仅链已按需推入的 core/*.o + -lc；xlang_process_* 由生成 C weak 定义。
     * 【Why 根源】Windows codegen 生成 extern 声明（非 weak 定义），minimal 链须显式链入
     * runtime_process_argv.o 提供 xlang_process_argc/argv 定义，否则链接报 undefined reference。
     * Linux/macOS 仍由生成 C 的 weak 定义提供默认值（minimal 链不链 runtime_process_argv.o）。
     * wave208 pure: MINIMAL tail (process_argv / -lc / NULL).
     * wave225 G.7: MINIMAL gate via link_abi_getenv (not raw getenv); host residual = _impl.
     * Stage 12.2.3: MINIMAL skips std need scan + ensure-push + ensure_std_net (no net TLS make). */
    if (link_abi_getenv("XLANG_MINIMAL_CC_LINK")) {
        invoke_cc_append_minimal_cc_link_tail(argv, &i, argv_cap);
        /* wave205 pure: spawn cc candidates + strip (no child exec). */
        if (invoke_cc_run_cc_argv(argv) != 0)
            return -1;
        invoke_cc_maybe_strip_out(out_path, opt_level);
        return 0;
    }
    /*
     * 【权威】std/*.o 仅在生成 C 真正引用「模块 API」时链入。
     * 禁止裸前缀 std_net_/std_context_/std_string_：rt_preamble 恒注入类型/宏/extern，
     * hello 也会假阳性 → 链 net.o/context.o → 再拖 thread/atomic（与用户无关）。
     * 针脚与 ASM 路径 link_abi_user_o_needs_std_net 等同权威（具体 API 名）。
     * 配合上方 -dead_strip/--gc-sections：co-emit 的未引用 io_ctx 体不迫使链 context。
     */
    {
        /* wave199: std module need scan pure orch (L5 invoke_cc_list).
         * G.7 pure needle tables + Cap residual contains_substr(_use_line).
         * Flag map: 0 process 1 process_argv_glue 2 string 3 path 4 runtime 5 net
         * 6 thread 7 time 8 random 9 env 10 sync 11 encoding 12 base64 13 crypto
         * 14 log 15 atomic 16 channel 17 backtrace 18 hash 19 math 20 sort 21 vec
         * 22 ffi 23 db 24 elf 25 json 26 csv 27 regex 28 compress 29 unicode
         * 30 dynlib 31 http 32 tar 33 simd 34 context 35 error 36 datetime 37 uuid
         * 38 url 39 cli 40 security 41 config 42 cache 43 trace 44 task 45 schema
         * 46 test 47 socketio 48 set 49 map 50 queue 51 panic.
         * wave200–204 ensure-push/heap pure; wave205 fork-exec pure. */
        int need_flags[52];
        invoke_cc_scan_std_module_needs(c_paths, n, need_flags, 52);
        /*
         * PLATFORM: SHARED — need-gated TLS auto ensure (ALLOW path only; post-scan).
         * need_flags[5] == net. Skip when include_root empty. G.7 single ensure authority
         * remains ensure_std_net_o_auto_tls; call site moved off entry for on-demand slim.
         * ensure-push front still appends net_tls ld flags when need_net + net.o present.
         */
        if (need_flags[5] && include_root && include_root[0])
            ensure_std_net_o_auto_tls(include_root);
        /* wave200 pure: string/process/heap/path/runtime/panic/net/thread/time/random/env.
         * May set need_flags[6]=1 when net.o links (workers → thread). */
        invoke_cc_append_std_ensure_push_front(argv, &i, argv_cap, need_flags, 52, include_root,
            process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o,
            net_o, thread_o, time_o, random_o, env_o);
        /* wave201 pure: sync/encoding/base64/crypto/log/atomic/channel/backtrace/hash. */
        invoke_cc_append_std_ensure_push_mid(argv, &i, argv_cap, need_flags, 52, include_root,
            sync_o, encoding_o, base64_o, crypto_o, atomic_o, channel_o, backtrace_o, hash_o);
        /* wave202 pure: math/sort/vec/ffi/db/elf/json/csv/set/map/queue/regex/compress. */
        invoke_cc_append_std_ensure_push_heavy_a(argv, &i, argv_cap, need_flags, 52, include_root,
            c_paths, n, math_o, sort_o, ffi_o, db_o, elf_o, regex_o, compress_o, hash_o);
        /* wave203 pure: unicode…process_argv complement (task/scheduler/test/dynlib/http…). */
        invoke_cc_append_std_ensure_push_heavy_b(argv, &i, argv_cap, need_flags, 52, include_root,
            c_paths, n, unicode_o, dynlib_o, http_o, tar_o, simd_o, context_o,
            datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o,
            task_o, schema_o, test_o, async_scheduler_o);
    }
    /* wave204 pure: heap F-06 on-demand (nm argv + use_line + provides + page_mmap companions). */
    invoke_cc_append_heap_f06_ondemand(argv, &i, argv_cap, c_paths, n, include_root);
    /* wave207 pure: argv tail (-pthread when thread|sync|channel .o present, -lc on POSIX,
     * WINDOWS allow-multiple, user_extra .o, NULL terminator). Cap residual peers below. */
    invoke_cc_append_argv_tail_flags(argv, &i, argv_cap, thread_o, sync_o, channel_o);
    /* wave205 pure: parent-side spawn cc candidates + strip -x when opt != 0. */
    /* #region debug-point C:invoke-cc-spawn */
    xlang_debug_hello_stage1_report("C", "runtime_link_abi.c:invoke_cc_spawn", "invoke_cc_spawn", n, use_lto, i);
    /* #endregion */
    if (invoke_cc_run_cc_argv(argv) != 0)
        return -1;
    /* #region debug-point D:invoke-cc-strip */
    xlang_debug_hello_stage1_report("D", "runtime_link_abi.c:invoke_cc_strip", "invoke_cc_strip", 0, 0, 0);
    /* #endregion */
    invoke_cc_maybe_strip_out(out_path, opt_level);
    return 0;
}

/* G-02f-277 L9 gates
 * Stage 12.2.3 / 13.2.4: cold monofile twin must match labi_gates.x early host-cc gate
 * (G.7 single deny path). Without this, LABI=0 cold seed still enters impl; impl now
 * also gates before ensure/argv (defense-in-depth), and invoke_cc_run_cc_argv re-checks.
 * PLATFORM: SHARED — product hybrid uses L9 pure (FROM_X); this body is cold residual. */
#ifndef XLANG_LABI_GATES_FROM_X
int xlang_invoke_cc(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o, const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o, const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o, const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o, const char *cli_o, const char *security_o, const char *config_o, const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o, const char *test_o, const char *include_root, const char *async_scheduler_o) {
  if (c_paths == NULL) {
    return -1;
  }
  if (out_path == NULL) {
    return -1;
  }
  /* Early deny: skip entering impl (and its ensure/argv) when host-cc is not opt-in (≡ labi_gates).
   * impl re-checks the same gate as defense-in-depth for direct residual calls. */
  if (!invoke_cc_host_cc_spawn_gate())
    return -1;
  {
    return xlang_invoke_cc_impl(c_paths, n, out_path, target, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, db_o, elf_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, simd_o, context_o, datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o, task_o, schema_o, test_o, include_root, async_scheduler_o);
  }
  return -1;
}
#else
int xlang_invoke_cc(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o, const char *string_o, const char *heap_o, const char *path_o, const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o, const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o, const char *db_o, const char *elf_o, const char *json_o, const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o, const char *simd_o, const char *context_o, const char *datetime_o, const char *uuid_o, const char *url_o, const char *cli_o, const char *security_o, const char *config_o, const char *cache_o, const char *trace_o, const char *task_o, const char *schema_o, const char *test_o, const char *include_root, const char *async_scheduler_o);
#endif


/* wave188: xlang_ensure_formal_std_make_o pure orch — body removed from mega
 * (lives in labi_invoke_ld_list L6 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_INVOKE_LD_LIST_FROM_X → L6 pure; cold path defines via include.
 * Pure: path/XLANG/make-cmd join; Cap residual getenv+access+realpath_cap+system+skip_missing.
 * Why: hybrid still had always-mega C body for formal std make ensure (system/make orch).
 * PLATFORM: SHARED orch / host shell make. */
/* wave191: labi_std_append_formal_ensure_for_rel pure orch — body removed from mega
 * (append_std OP_STD formal ensure+companions; Cap residual repo_root + ensure_runtime_*).
 * Hybrid → L6 pure; cold twin via include. PLATFORM: SHARED. */
#ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X
/* cold twin body is in seeds/labi_invoke_ld_list.from_x.c (#include above). */
#else
int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo, const char *make_target);
int labi_std_rel_is_std_or_core(const char *rel);
void labi_std_append_formal_ensure_for_rel(const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la);
#endif

/* wave187: ensure_std_net_o_auto_tls pure orch — body removed from mega
 * (lives in labi_invoke_ld_list L6 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_INVOKE_LD_LIST_FROM_X → L6 pure; cold path defines via include.
 * Pure: mode strcmp + path/make-cmd join; Cap residual getenv+system+realpath_cap+exports_marker.
 * Why: hybrid still had always-mega C body for auto TLS ensure (system/make orch).
 * PLATFORM: SHARED orch / host shell make. */
#ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X
/* cold twin body is in seeds/labi_invoke_ld_list.from_x.c (#include above). */
#else
void ensure_std_net_o_auto_tls(const char *repo_root);
#endif

/* wave158: invoke_cc_append_net_tls_ld pure orch — body removed from mega
 * (lives in labi_invoke_ld_list L6 pure / cold twin via #include above).
 * Hybrid XLANG_LABI_INVOKE_LD_LIST_FROM_X → L6 pure; cold path defines via include.
 * wave187/188: ensure_std_net + formal_std_make pure siblings (Cap residual getenv+system).
 * PLATFORM: SHARED orch / MACOS brew -L consumers. */




/**
 * 相对仓库根的 .o 路径解析：realpath(rel)、cwd/rel、argv0/../rel。
 * wave185: pure orch in labi_path_pure L0 (hybrid FROM_X / cold twin include).
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: last-sep index + byte join; Cap residual realpath_cap + getcwd + strdup + skip_missing.
 * Heap return per call (never static BSS) — multi-call independence for invoke_cc 30+ paths.
 * PLATFORM: SHARED orch.
 */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel) {
    /* 【Why 逻辑根源】返回独立堆分配内存而非静态缓冲：runtime.c 中 xlang_invoke_cc 之前
     * 连续调用 30+ 次本函数（path_o/runtime_o/.../crypto_o/.../test_o）保存到局部变量，
     * 若返回静态缓冲则所有指针指向同一缓冲，最终只剩最后一次调用的内容——crypto_o 实际
     * 指向 test.o 路径，链接器找不到 crypto.o 触发 _core_crypto_mem_eq_c 未定义错误。
     * 【Invariant】调用方无需 free；进程退出自动回收（编译器短生命周期）。
     * 【Asm/Perf】strdup 一次 ~50ns，30+ 次仅 ~1.5us，可忽略。 */
    char buf[512];
    char resolved[PATH_MAX];
    size_t rel_len;
    buf[0] = resolved[0] = '\0';
    if (!rel || !rel[0])
        return strdup("");
    rel_len = strlen(rel);
    if (link_abi_realpath_cap(rel, resolved) != NULL)
        return strdup(resolved);
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd) - 2) != NULL) {
            size_t L = strlen(cwd);
            if (L + 1 + rel_len + 1 <= sizeof(cwd)) {
                cwd[L] = '/';
                memcpy(cwd + L + 1, rel, rel_len + 1);
                if (link_abi_realpath_cap(cwd, resolved) != NULL)
                    return strdup(resolved);
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = xlang_path_last_sep(argv0);
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - (int)(3 + rel_len))
                return strdup("");
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.';
            buf[1] = '\0';
            n = 1;
        }
        if ((size_t)n + 3 + rel_len < sizeof(buf)) {
            strcat(buf, "/../");
            strcat(buf, rel);
            if (link_abi_realpath_cap(buf, resolved) != NULL)
                return strdup(resolved);
            /* realpath 失败时勿返回臆造路径：仅当 stat 命中常规文件才返回 buf。 */
            if (asm_link_obj_skip_missing(buf))
                return strdup(buf);
            return strdup("");
        }
    }
    return strdup("");
}
#else
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
#endif

/**
 * PLATFORM: LINUX — freestanding product popen is a NULL stub (bootstrap_nostdlib_stubs).
 * Without this, on_demand never sees U symbols and -backend asm takes minimal gcc only.
 * Scan ELF64 .symtab for SHN_UNDEF. want_sym NULL → any global UNDEF; else match name.
 * Returns 1 on match, 0 on none/error. G.7 authority for freestanding undef probes.
 */
#if defined(__linux__)
static int xlang_elf64_obj_scan_undef(const char *o_path, const char *want_sym) {
    int fd;
    struct stat st;
    unsigned char *map = NULL;
    size_t sz;
    Elf64_Ehdr *eh;
    Elf64_Shdr *sh;
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    Elf64_Sym *syms;
    const char *strs;
    size_t i, nsym;
    int found = 0;
    if (!o_path || !o_path[0])
        return 0;
    fd = open(o_path, O_RDONLY, 0);
    if (fd < 0)
        return 0;
    if (xlang_path_fstat(fd, &st) != 0 || st.st_size < (off_t)sizeof(Elf64_Ehdr)) {
        close(fd);
        return 0;
    }
    sz = (size_t)st.st_size;
    map = (unsigned char *)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == MAP_FAILED)
        return 0;
    eh = (Elf64_Ehdr *)map;
    if (memcmp(eh->e_ident, ELFMAG, SELFMAG) != 0 || eh->e_ident[EI_CLASS] != ELFCLASS64) {
        munmap(map, sz);
        return 0;
    }
    if (eh->e_shoff == 0 || eh->e_shentsize != sizeof(Elf64_Shdr) || eh->e_shnum == 0) {
        munmap(map, sz);
        return 0;
    }
    if ((size_t)eh->e_shoff + (size_t)eh->e_shnum * sizeof(Elf64_Shdr) > sz) {
        munmap(map, sz);
        return 0;
    }
    sh = (Elf64_Shdr *)(map + eh->e_shoff);
    for (i = 0; i < eh->e_shnum; i++) {
        if (sh[i].sh_type == SHT_SYMTAB) {
            symtab = &sh[i];
            if (sh[i].sh_link < eh->e_shnum)
                strtab = &sh[sh[i].sh_link];
            break;
        }
    }
    if (!symtab || !strtab || symtab->sh_entsize != sizeof(Elf64_Sym) ||
        symtab->sh_offset + symtab->sh_size > sz || strtab->sh_offset + strtab->sh_size > sz) {
        munmap(map, sz);
        return 0;
    }
    nsym = symtab->sh_size / sizeof(Elf64_Sym);
    syms = (Elf64_Sym *)(map + symtab->sh_offset);
    strs = (const char *)(map + strtab->sh_offset);
    for (i = 0; i < nsym; i++) {
        const char *name;
        if (syms[i].st_shndx != SHN_UNDEF)
            continue;
        if (ELF64_ST_BIND(syms[i].st_info) == STB_LOCAL)
            continue;
        if (syms[i].st_name >= strtab->sh_size)
            continue;
        name = strs + syms[i].st_name;
        if (!name[0])
            continue;
        if (!want_sym) {
            found = 1;
            break;
        }
        if (strcmp(name, want_sym) == 0) {
            found = 1;
            break;
        }
    }
    munmap(map, sz);
    return found;
}
#endif /* __linux__ */

/*
 * One-slot per-path UNDEF + defined (T/t) + all-names cache.
 *
 * Produce-point (P2 Darwin -o): every product -o walks on_demand std gates
 * (heap / sys / vec / async / …) and each gate calls needs_undef once per
 * symbol. The previous body popen("nm -u") + fgets per probe. Darwin hello
 * -o was ~17s / ~2.3M page-reclaims, sample 100% in posix_spawn+read of nm.
 * Sibling 1: has_defined_sym_impl still popen("nm") T/t per probe.
 * Sibling 2 (this knife): compress orch still popen full nm 11 times per
 * hello -o (exports_marker strstr + has_undef " U "+needle). G.7 complete:
 * one mmap fills UNDEF + T/t + all-names; lookups stay in-process.
 *
 * Blob: concatenated NUL-terminated bare names (leading '_' stripped).
 * Defined blob matches historical nm T/t only (text; not D/S/B/W).
 * All-names blob is every non-debug symbol (markers live in d/s/b).
 * PLATFORM: SHARED cache; loaders LINUX ELF / DARWIN Mach-O / nm once fallback.
 */
#define XLANG_UNDEF_CACHE_BLOB_MAX (256u * 1024u)
static char g_undef_cache_path[PATH_MAX];
static char g_undef_cache_blob[XLANG_UNDEF_CACHE_BLOB_MAX];
static size_t g_undef_cache_blob_len;
static char g_defined_cache_blob[XLANG_UNDEF_CACHE_BLOB_MAX];
static size_t g_defined_cache_blob_len;
static char g_all_cache_blob[XLANG_UNDEF_CACHE_BLOB_MAX];
static size_t g_all_cache_blob_len;
static int g_undef_cache_ready;

static int xlang_nameblob_append(char *blob, size_t *len, const char *name) {
    size_t n;
    if (!name || !name[0])
        return 1;
    if (*name == '_')
        name++;
    n = strlen(name);
    if (n == 0)
        return 1;
    if (*len + n + 1 >= XLANG_UNDEF_CACHE_BLOB_MAX)
        return 0;
    memcpy(blob + *len, name, n);
    *len += n;
    blob[(*len)++] = '\0';
    return 1;
}

static int xlang_nameblob_has(const char *blob, size_t len, const char *sym) {
    size_t i = 0;
    size_t slen;
    if (!sym || !sym[0])
        return 0;
    slen = strlen(sym);
    while (i < len) {
        size_t n = strlen(blob + i);
        if (n == slen && memcmp(blob + i, sym, slen) == 0)
            return 1;
        i += n + 1;
    }
    return 0;
}

/**
 * Substring search over a name blob (historical nm strstr).
 * PLATFORM: DARWIN — stored names are stripped; reconstruct one leading '_'
 * so needles like `_compress2` / `_ZSTD` still hit. LINUX/WINDOWS — no
 * extra '_' (ELF/COFF nm lines have no Mach-O prefix; do not invent one).
 */
static int xlang_nameblob_has_substr(const char *blob, size_t len, const char *needle) {
    size_t i = 0;
    size_t nlen;
    if (!needle || !needle[0] || !blob)
        return 0;
    nlen = strlen(needle);
    while (i < len) {
        const char *name = blob + i;
        size_t n = strlen(name);
        if (n >= nlen && strstr(name, needle) != NULL)
            return 1;
#if defined(__APPLE__)
        if (n + 1 >= nlen && n + 2 <= 512) {
            char rec[512];
            rec[0] = '_';
            memcpy(rec + 1, name, n + 1);
            if (strstr(rec, needle) != NULL)
                return 1;
        }
#endif
        i += n + 1;
    }
    return 0;
}

static void xlang_undef_cache_reset(void) {
    g_undef_cache_path[0] = '\0';
    g_undef_cache_blob_len = 0;
    g_defined_cache_blob_len = 0;
    g_all_cache_blob_len = 0;
    g_undef_cache_ready = 0;
}

static int xlang_undef_cache_append_name(const char *name) {
    return xlang_nameblob_append(g_undef_cache_blob, &g_undef_cache_blob_len, name);
}

static int xlang_defined_cache_append_name(const char *name) {
    return xlang_nameblob_append(g_defined_cache_blob, &g_defined_cache_blob_len, name);
}

static int xlang_all_cache_append_name(const char *name) {
    return xlang_nameblob_append(g_all_cache_blob, &g_all_cache_blob_len, name);
}

static int xlang_undef_cache_has(const char *sym) {
    return xlang_nameblob_has(g_undef_cache_blob, g_undef_cache_blob_len, sym);
}

static int xlang_defined_cache_has(const char *sym) {
    return xlang_nameblob_has(g_defined_cache_blob, g_defined_cache_blob_len, sym);
}

static int xlang_undef_cache_has_substr(const char *needle) {
    return xlang_nameblob_has_substr(g_undef_cache_blob, g_undef_cache_blob_len, needle);
}

static int xlang_all_cache_has_substr(const char *needle) {
    return xlang_nameblob_has_substr(g_all_cache_blob, g_all_cache_blob_len, needle);
}

#if defined(__APPLE__)
/**
 * Fill UNDEF + defined (T/t) + all-names caches from a thin Mach-O 64 object.
 * @return 1 if the file is a parseable Mach-O 64 (even with 0 names); 0 if
 *         not Mach-O / mmap fail — caller falls back to nm.
 * PLATFORM: DARWIN — in-process nlist_64 scan; no popen.
 */
static int xlang_macho64_obj_fill_undef_cache(const char *o_path) {
    int fd;
    struct stat st;
    unsigned char *map = NULL;
    size_t sz;
    const struct mach_header_64 *mh;
    const struct load_command *lc;
    const struct symtab_command *stcmd = NULL;
    const struct nlist_64 *nl;
    const char *strtab;
    uint32_t i;
    uint32_t ncmds;
    uint32_t sect_no;
    size_t off;
    uint8_t is_text[256];
    if (!o_path || !o_path[0])
        return 0;
    fd = open(o_path, O_RDONLY);
    if (fd < 0)
        return 0;
    if (xlang_path_fstat(fd, &st) != 0 || st.st_size < (off_t)sizeof(struct mach_header_64)) {
        close(fd);
        return 0;
    }
    sz = (size_t)st.st_size;
    map = (unsigned char *)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == MAP_FAILED)
        return 0;
    mh = (const struct mach_header_64 *)map;
    if (mh->magic != MH_MAGIC_64) {
        munmap(map, sz);
        return 0;
    }
    if ((size_t)sizeof(struct mach_header_64) + (size_t)mh->sizeofcmds > sz) {
        munmap(map, sz);
        return 0;
    }
    memset(is_text, 0, sizeof is_text);
    ncmds = mh->ncmds;
    off = sizeof(struct mach_header_64);
    sect_no = 1;
    for (i = 0; i < ncmds; i++) {
        if (off + sizeof(struct load_command) > sz)
            break;
        lc = (const struct load_command *)(map + off);
        if (lc->cmdsize < sizeof(struct load_command) || off + lc->cmdsize > sz)
            break;
        if (lc->cmd == LC_SYMTAB && lc->cmdsize >= sizeof(struct symtab_command) && !stcmd)
            stcmd = (const struct symtab_command *)lc;
        if (lc->cmd == LC_SEGMENT_64 && lc->cmdsize >= sizeof(struct segment_command_64)) {
            const struct segment_command_64 *sg = (const struct segment_command_64 *)lc;
            size_t sect_off = off + sizeof(struct segment_command_64);
            uint32_t j;
            for (j = 0; j < sg->nsects; j++) {
                const struct section_64 *sec;
                if (sect_off + sizeof(struct section_64) > sz)
                    break;
                sec = (const struct section_64 *)(map + sect_off);
                if (sect_no < 256) {
                    if ((sec->flags & (S_ATTR_PURE_INSTRUCTIONS | S_ATTR_SOME_INSTRUCTIONS)) != 0)
                        is_text[sect_no] = 1;
                    if (strncmp(sec->sectname, "__text", 16) == 0)
                        is_text[sect_no] = 1;
                }
                sect_no++;
                sect_off += sizeof(struct section_64);
            }
        }
        off += lc->cmdsize;
    }
    if (!stcmd) {
        munmap(map, sz);
        return 1; /* Mach-O with no symtab: treat as 0 names, not nm fallback. */
    }
    if ((size_t)stcmd->symoff + (size_t)stcmd->nsyms * sizeof(struct nlist_64) > sz ||
        (size_t)stcmd->stroff + (size_t)stcmd->strsize > sz) {
        munmap(map, sz);
        return 0;
    }
    nl = (const struct nlist_64 *)(map + stcmd->symoff);
    strtab = (const char *)(map + stcmd->stroff);
    for (i = 0; i < stcmd->nsyms; i++) {
        uint32_t strx;
        const char *name;
        uint8_t nt = nl[i].n_type;
        uint8_t nsect;
        if (nt & N_STAB)
            continue;
        strx = nl[i].n_un.n_strx;
        if (strx >= stcmd->strsize)
            continue;
        name = strtab + strx;
        if (!name[0])
            continue;
        /* All-names: markers are data (d/s/b), not T/t. Fill every non-STAB. */
        if (!xlang_all_cache_append_name(name)) {
            munmap(map, sz);
            return 0;
        }
        if ((nt & N_TYPE) == N_UNDF && (nt & N_EXT) != 0) {
            if (!xlang_undef_cache_append_name(name)) {
                munmap(map, sz);
                return 0;
            }
            continue;
        }
        /* Historical nm T/t: text section. Darwin still prints N_WEAK_DEF as t
         * (not W) — include them so has_defined matches the old nm T/t parser. */
        if ((nt & N_TYPE) != N_SECT)
            continue;
        nsect = nl[i].n_sect;
        /* n_sect is uint8_t (1-based); 0 = NO_SECT. is_text[256] covers 0..255. */
        if (nsect == 0 || !is_text[nsect])
            continue;
        if (!xlang_defined_cache_append_name(name)) {
            munmap(map, sz);
            return 0;
        }
    }
    munmap(map, sz);
    return 1;
}
#endif /* __APPLE__ */

#if defined(__linux__)
/**
 * Fill UNDEF + defined (T/t) + all-names caches from ELF64 SHT_SYMTAB.
 * UNDEF = SHN_UNDEF non-local; T/t = STT_FUNC in a real section, not weak.
 * @return 1 if the file is a parseable ELF64; 0 on error (nm fallback).
 * PLATFORM: LINUX — in-process .symtab scan; no popen.
 */
static int xlang_elf64_obj_fill_undef_cache(const char *o_path) {
    int fd;
    struct stat st;
    unsigned char *map = NULL;
    size_t sz;
    Elf64_Ehdr *eh;
    Elf64_Shdr *sh;
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    Elf64_Sym *syms;
    const char *strs;
    size_t i, nsym;
    if (!o_path || !o_path[0])
        return 0;
    fd = open(o_path, O_RDONLY, 0);
    if (fd < 0)
        return 0;
    if (xlang_path_fstat(fd, &st) != 0 || st.st_size < (off_t)sizeof(Elf64_Ehdr)) {
        close(fd);
        return 0;
    }
    sz = (size_t)st.st_size;
    map = (unsigned char *)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == MAP_FAILED)
        return 0;
    eh = (Elf64_Ehdr *)map;
    if (memcmp(eh->e_ident, ELFMAG, SELFMAG) != 0 || eh->e_ident[EI_CLASS] != ELFCLASS64) {
        munmap(map, sz);
        return 0;
    }
    if (eh->e_shoff == 0 || eh->e_shentsize != sizeof(Elf64_Shdr) || eh->e_shnum == 0) {
        munmap(map, sz);
        return 0;
    }
    if ((size_t)eh->e_shoff + (size_t)eh->e_shnum * sizeof(Elf64_Shdr) > sz) {
        munmap(map, sz);
        return 0;
    }
    sh = (Elf64_Shdr *)(map + eh->e_shoff);
    for (i = 0; i < eh->e_shnum; i++) {
        if (sh[i].sh_type == SHT_SYMTAB) {
            symtab = &sh[i];
            if (sh[i].sh_link < eh->e_shnum)
                strtab = &sh[sh[i].sh_link];
            break;
        }
    }
    if (!symtab || !strtab || symtab->sh_entsize != sizeof(Elf64_Sym) ||
        symtab->sh_offset + symtab->sh_size > sz || strtab->sh_offset + strtab->sh_size > sz) {
        munmap(map, sz);
        return 0;
    }
    nsym = symtab->sh_size / sizeof(Elf64_Sym);
    syms = (Elf64_Sym *)(map + symtab->sh_offset);
    strs = (const char *)(map + strtab->sh_offset);
    for (i = 0; i < nsym; i++) {
        const char *name;
        unsigned bind;
        unsigned type;
        if (syms[i].st_name >= strtab->sh_size)
            continue;
        name = strs + syms[i].st_name;
        if (!name[0])
            continue;
        /* All-names: markers are data (d/s/b), not T/t. Fill every .symtab name. */
        if (!xlang_all_cache_append_name(name)) {
            munmap(map, sz);
            return 0;
        }
        bind = ELF64_ST_BIND(syms[i].st_info);
        type = ELF64_ST_TYPE(syms[i].st_info);
        if (syms[i].st_shndx == SHN_UNDEF) {
            if (bind == STB_LOCAL)
                continue;
            if (!xlang_undef_cache_append_name(name)) {
                munmap(map, sz);
                return 0;
            }
            continue;
        }
        /* Historical nm T/t: STT_FUNC in a real section; skip weak (nm W). */
        if (syms[i].st_shndx == SHN_ABS || syms[i].st_shndx == SHN_COMMON)
            continue;
        if (type != STT_FUNC)
            continue;
        if (bind == STB_WEAK)
            continue;
        if (!xlang_defined_cache_append_name(name)) {
            munmap(map, sz);
            return 0;
        }
    }
    munmap(map, sz);
    return 1;
}
#endif /* __linux__ */

/**
 * One nm -u popen into the UNDEF cache (fallback when in-process scan fails).
 * Same line rules as the historical per-probe parser: skip optional U + '_'.
 * @return 1 if popen succeeded (even 0 names); 0 if nm unavailable.
 * PLATFORM: SHARED residual host nm.
 */
static int xlang_nm_u_fill_undef_cache(const char *o_path) {
    char cmd[PATH_MAX + 160];
    FILE *fp;
    char line[512];
    if (!o_path || !o_path[0])
        return 0;
    if ((size_t)snprintf(cmd, sizeof cmd, "nm -u '%s' 2>/dev/null", o_path) >= sizeof cmd)
        return 0;
    fp = popen(cmd, "r");
    if (!fp)
        return 0;
    while (fgets(line, sizeof line, fp)) {
        char *p = line;
        size_t rest;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p == 'U' && (p[1] == ' ' || p[1] == '\t')) {
            p += 2;
            while (*p == ' ' || *p == '\t')
                p++;
        }
        if (*p == '_')
            p++;
        rest = strlen(p);
        while (rest > 0 && (p[rest - 1] == '\n' || p[rest - 1] == '\r' || p[rest - 1] == ' '))
            rest--;
        if (rest == 0)
            continue;
        p[rest] = '\0';
        if (!xlang_undef_cache_append_name(p)) {
            pclose(fp);
            return 0;
        }
    }
    pclose(fp);
    return 1;
}

/**
 * One nm (no -u) popen into the defined T/t + all-names caches (fallback).
 * T/t: same line rules as the historical per-probe parser (addr + T/t + '_').
 * All-names: last whitespace token of every line (markers are d/s/b, not T/t).
 * @return 1 if popen succeeded (even 0 names); 0 if nm unavailable.
 * PLATFORM: SHARED residual host nm.
 */
static int xlang_nm_t_fill_defined_cache(const char *o_path) {
    char cmd[PATH_MAX + 160];
    FILE *fp;
    char line[512];
    if (!o_path || !o_path[0])
        return 0;
    if ((size_t)snprintf(cmd, sizeof cmd, "nm '%s' 2>/dev/null", o_path) >= sizeof cmd)
        return 0;
    fp = popen(cmd, "r");
    if (!fp)
        return 0;
    while (fgets(line, sizeof line, fp)) {
        char *p = line;
        char *last;
        char *q;
        size_t rest;
        /* All-names: last whitespace token of every full-nm line. */
        last = line;
        q = line;
        while (*q) {
            if (*q == ' ' || *q == '\t') {
                while (*q == ' ' || *q == '\t')
                    q++;
                if (*q)
                    last = q;
            } else {
                q++;
            }
        }
        rest = strlen(last);
        while (rest > 0 && (last[rest - 1] == '\n' || last[rest - 1] == '\r' || last[rest - 1] == ' '))
            rest--;
        if (rest > 0) {
            char saved = last[rest];
            last[rest] = '\0';
            if (!xlang_all_cache_append_name(last)) {
                last[rest] = saved;
                pclose(fp);
                return 0;
            }
            last[rest] = saved;
        }
        while (*p == ' ' || *p == '\t' || (*p >= '0' && *p <= '9') ||
               (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F'))
            p++;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p != 'T' && *p != 't')
            continue;
        p++;
        if (*p != ' ' && *p != '\t')
            continue;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p == '_')
            p++;
        rest = strlen(p);
        while (rest > 0 && (p[rest - 1] == '\n' || p[rest - 1] == '\r' || p[rest - 1] == ' '))
            rest--;
        if (rest == 0)
            continue;
        p[rest] = '\0';
        if (!xlang_defined_cache_append_name(p)) {
            pclose(fp);
            return 0;
        }
    }
    pclose(fp);
    return 1;
}

static int xlang_undef_cache_load(const char *o_path) {
    size_t n;
    if (!o_path || !o_path[0])
        return 0;
    if (g_undef_cache_ready && strcmp(g_undef_cache_path, o_path) == 0)
        return 1;
    xlang_undef_cache_reset();
    n = strlen(o_path);
    if (n >= sizeof(g_undef_cache_path))
        return 0;
    memcpy(g_undef_cache_path, o_path, n + 1);
#if defined(__APPLE__)
    if (xlang_macho64_obj_fill_undef_cache(o_path)) {
        g_undef_cache_ready = 1;
        return 1;
    }
#endif
#if defined(__linux__)
    if (xlang_elf64_obj_fill_undef_cache(o_path)) {
        g_undef_cache_ready = 1;
        return 1;
    }
#endif
    /* In-process scan failed: one nm -u for UNDEF + one nm for T/t and all-names. */
    (void)xlang_nm_u_fill_undef_cache(o_path);
    (void)xlang_nm_t_fill_defined_cache(o_path);
    /* nm unavailable: empty ready cache (same as historical Darwin popen-fail → 0). */
    g_undef_cache_ready = 1;
    return 1;
}

/**
 * Cap residual (wave212): exact UNDEF probe body.
 * Pure orch (labi_ondemand_list L8b) owns null/empty gates; _impl is always mega.
 * Params: o_path / sym — caller pure already rejected null/empty (defense in depth here too).
 * Returns: 1 if UNDEF matches bare sym (optional U type + leading _), else 0.
 *
 * Why root: Darwin `nm -u` is `_sym` alone (no type letter U) with Mach-O leading `_`.
 * Old code used `nm -u --porcelain` (often empty on Apple) and only bare names / lines with U
 * → http.o UNDEF for std_heap_* never hit → on_demand skipped heap.o → link fail.
 * Freestanding: popen stub always NULL → always 0 → minimal gcc never on_demand (si UNDEF).
 * Invariant: skip optional U type field and optional leading `_`, then compare bare sym.
 *
 * P2 Darwin -o: load UNDEF names once per o_path (Mach-O / ELF / one nm -u), then
 * in-process lookup. Do not popen nm per symbol — on_demand walks hundreds of
 * probes against the same user.o on every product -o.
 * PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O in-process; nm fallback.
 */
int xlang_link_obj_needs_undef_sym_impl(const char *o_path, const char *sym) {
    if (!o_path || !o_path[0] || !sym || !sym[0])
        return 0;
    if (!g_undef_cache_ready || strcmp(g_undef_cache_path, o_path) != 0) {
        if (!xlang_undef_cache_load(o_path))
            return 0;
    }
    return xlang_undef_cache_has(sym);
}

/* wave212: xlang_link_obj_needs_undef_sym pure orch lives in labi_ondemand_list.x (hybrid L8b);
 * cold twin under #ifndef ONDEMAND_LIST_FROM_X in seeds/labi_ondemand_list.from_x.c
 * (mega #include when !FROM_X, or L8b cold seed object when pure .x fails).
 * Pure: null/empty gates; Cap residual xlang_link_obj_needs_undef_sym_impl
 * (Mach-O/ELF scan or one nm -u; per-path cache) always mega.
 * Why: hybrid still had needs_undef_sym body always mega C (gates+nm+ELF).
 * PLATFORM: SHARED orch. Do not define public twin here — would double-def with seed include. */
#ifdef XLANG_LABI_ONDEMAND_LIST_FROM_X
int xlang_link_obj_needs_undef_sym(const char *o_path, const char *sym);
#endif

/**
 * Cap residual (wave213): exact defined (T/t) probe body.
 * Pure orch (labi_ondemand_list L8b) owns null/empty gates; _impl is always mega.
 * Params: o_path / sym - caller pure already rejected null/empty (defense in depth here too).
 * Returns: 1 if the object defines bare sym as text (optional leading _), else 0.
 *
 * Why: co-emit after user.o may already define core_mem_* or std_heap_* strongs;
 * skip hard-link mem.o/heap.o. Darwin nm: "0000 T _sym"; ELF: "0000 T sym".
 *
 * P2 Darwin -o sibling: load T/t names once per o_path in the same Mach-O / ELF
 * scan as UNDEF (or one nm T/t fallback), then in-process lookup. Do not popen
 * nm per defined-sym probe — hello -o still spawned 11 full-nm on one user.o
 * after the UNDEF cache closed nm -u.
 * PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O in-process; nm fallback.
 */
int xlang_link_obj_has_defined_sym_impl(const char *o_path, const char *sym) {
    if (!o_path || !o_path[0] || !sym || !sym[0])
        return 0;
    if (!g_undef_cache_ready || strcmp(g_undef_cache_path, o_path) != 0) {
        if (!xlang_undef_cache_load(o_path))
            return 0;
    }
    return xlang_defined_cache_has(sym);
}

/* wave213: xlang_link_obj_has_defined_sym pure orch lives in labi_ondemand_list.x (hybrid L8b);
 * cold twin under #ifndef ONDEMAND_LIST_FROM_X in seeds/labi_ondemand_list.from_x.c
 * (mega #include when !FROM_X, or L8b cold seed object when pure .x fails).
 * Pure: null/empty gates; Cap residual xlang_link_obj_has_defined_sym_impl
 * (Mach-O/ELF T/t scan or one nm; per-path cache) always mega.
 * Why: hybrid still had has_defined_sym body always mega C (gates+nm).
 * PLATFORM: SHARED orch. Do not define public twin here — would double-def with seed include. */
#ifdef XLANG_LABI_ONDEMAND_LIST_FROM_X
int xlang_link_obj_has_defined_sym(const char *o_path, const char *sym);
#endif

/* wave140: link_abi_user_o_provides_core_mem pure orch lives in labi_ondemand_list
 * (2 defined-sym needles + pure scan; Cap residual has_defined_sym pure thin wave213; _impl Cap).
 * Cold twin under #ifndef ONDEMAND_LIST_FROM_X; hybrid L8b pure .x.
 * Why: co-emit core_mem_* strong defs in user.o; hard-link mem.o → duplicate.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int link_abi_user_o_provides_core_mem(const char *user_o);

/* wave140: link_abi_user_o_provides_std_heap pure orch (L8b ondemand).
 * Why: co-emit heap strong defs; hard-link heap.o → duplicate.
 */
int link_abi_user_o_provides_std_heap(const char *user_o);




/** ld argv 项是否为已解析的 .o/.obj 路径（跳过 -o、编译器驱动等）。 */
/* G-02f-65：真逻辑来自 .x（.o / .obj 后缀；原 static 提升为导出）。 */
/* G-02f-267 L0 path pure */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int link_abi_ld_argv_entry_is_obj(const char *s) {
    size_t n;
    if (s == NULL) {
        return 0;
    }
    if (s[0] == 0) {
        return 0;
    }
    n = 0;
    while (s[n] != 0) {
        n = n + 1;
    }
    if (n >= 2) {
        if (s[n - 2] == '.') {
            if (s[n - 1] == 'o') {
                return 1;
            }
        }
    }
    if (n >= 4) {
        if (s[n - 4] == '.') {
            if (s[n - 3] == 'o') {
                if (s[n - 2] == 'b') {
                    if (s[n - 1] == 'j') {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
#else
int link_abi_ld_argv_entry_is_obj(const char *s);
#endif


/* wave145: link_abi_link_needs_heap_user_c pure orch lives in labi_ondemand_list
 * (aggregate user_o + argv .o scan via pure needs_heap_user_syms + ld_argv_entry_is_obj).
 * Was mega body always over pure leaf orch. Cold twin under #ifndef ONDEMAND_LIST_FROM_X;
 * hybrid L8b pure .x. PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
int link_abi_link_needs_heap_user_c(const char *user_o, const char **argv, int la);




/* wave144: xlang_freestanding_user_o_needs_{io,panic} pure orch lives in
 * labi_freestanding_list (io_sym ×13 / panic_sym + pure scan; Cap residual
 * undef_sym). Was mega body always over pure tables. Cold twin under
 * #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
int xlang_freestanding_user_o_needs_io(const char *user_o);
int xlang_freestanding_user_o_needs_panic(const char *user_o);

/* wave159: xlang_link_freestanding_enabled pure orch lives in
 * labi_freestanding_list (peer host_is_linux + pure env name + Cap residual getenv).
 * Was always-mega body. Cold twin under #ifndef FREESTANDING_LIST_FROM_X; hybrid L7 pure .x.
 * PLATFORM: SHARED orch / LINUX freestanding consumers — dual-end L2.
 */
int xlang_link_freestanding_enabled(int driver_freestanding);

/*
 * wave118: needs_std_net pure orch lives in labi_ondemand_list (net sym table + orch).
 * wave119: needs_std_set pure orch lives in labi_ondemand_list (set sym table + orch).
 * wave120: needs_std_map pure orch lives in labi_ondemand_list (map sym table + orch).
 * wave121: needs_std_queue pure orch lives in labi_ondemand_list (queue_api sym table + orch).
 * wave122: needs_std_test pure orch lives in labi_ondemand_list (test sym table + orch).
 * wave123: needs_core_mem pure orch lives in labi_ondemand_list (core_mem sym table + orch).
 * wave124: needs_core_slice pure orch lives in labi_ondemand_list (core_slice sym table + orch).
 * wave125: needs_std_heap_page_mmap pure orch lives in labi_ondemand_list (page_mmap sym table + orch).
 * wave126: needs_std_sys_linux pure orch lives in labi_ondemand_list (sys_linux sym table + orch).
 * wave127: needs_std_sys pure orch lives in labi_ondemand_list (sys facade sym table + orch).
 * wave128: needs_std_heap_api pure orch lives in labi_ondemand_list (heap_api sym table + orch).
 * wave129: needs_heap_user_syms pure orch lives in labi_ondemand_list (heap_user sym table + orch).
 * wave130: needs_async_scheduler pure orch lives in labi_ondemand_list (async_scheduler sym table + orch).
 * wave131: compress family pure orch lives in labi_ondemand_list (zlib/zstd/brotli marker+undef + needs_compress_libs).
 * wave132: labi_user_needs_runtime_{time_os,random_fill,env_os} pure orch lives in labi_ondemand_list
 *   (PRIMARY OS tables; null/empty → 1).
 * wave133: labi_user_needs_runtime_process_argv pure orch (9 needles).
 * wave134: labi_user_needs_std_task pure orch (29 needles; TASK_SPECIAL bulk gate).
 * wave135: labi_std_fk0_user_needs_rel pure orch (16 rel × 106 exact UNDEF).
 * Full-seed path: bodies via #include below (!FROM_X). Hybrid FROM_X: L8b pure .x provides;
 * decls in #else of ondemand include. Cap residual: undef_sym stays mega. PLATFORM: SHARED.
 */

/**
 * wave128: needs_std_heap_api pure orch lives in labi_ondemand_list
 * (labi_od_heap_api_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 * Why: F-闭合删除 import_alias C 桩后 std/*.o 直接引用 std_heap_*；product heap.o gate.
 * wave145: aggregate link_abi_link_needs_std_heap_import pure orch also in L8b.
 */

/**
 * wave129: needs_heap_user_syms pure orch lives in labi_ondemand_list
 * (labi_od_heap_user_sym_* product table ×7 exact + pure scan; not here).
 * Exact symbols only (no prefix probes). Product complete: alloc/free/realloc/arena64_alloc
 * + with_arena heap_arena_init_c / heap_arena64_{init,deinit}_c (G.7 close incomplete mega.x residual).
 * wave145: aggregate link_abi_link_needs_heap_user_c pure orch also in L8b.
 */

/* wave145: link_abi_link_needs_std_heap_import pure orch lives in labi_ondemand_list
 * (aggregate user_o + argv .o scan via pure needs_std_heap_api + ld_argv_entry_is_obj).
 * Was mega body always over pure leaf orch. Cold twin under #ifndef ONDEMAND_LIST_FROM_X;
 * hybrid L8b pure .x. PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la);




/**
 * wave121: needs_std_queue pure orch lives in labi_ondemand_list
 * (labi_od_queue_api_sym_* product table + pure scan; not here).
 * Contention/smoke stays labi_od_queue_sym_* (separate table).
 */

/**
 * wave122: needs_std_test pure orch lives in labi_ondemand_list
 * (labi_od_test_sym_* product table + pure scan; not here).
 * Prefix probes (test_runner_ etc.) rely on Cap residual strstr in undef_sym.
 */

/**
 * wave123: needs_core_mem pure orch lives in labi_ondemand_list
 * (labi_od_core_mem_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 */

/**
 * wave124: needs_core_slice pure orch lives in labi_ondemand_list
 * (labi_od_core_slice_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 */

/**
 * Cap residual (always _impl, wave218 + 9.1.2): resolve path into out; Windows / fail → NULL.
 * Pure orch (wave218 labi_path_io L3) owns public thin + null/empty/out gates;
 * path_pure / invoke_ld / formal_std call the public face (wave146+).
 * PLATFORM: SHARED residual; LINUX open+readlink Cap residual; WINDOWS always NULL.
 */
const char *link_abi_realpath_cap_impl(const char *path, char *out) {
#if defined(_WIN32) || defined(_WIN64)
    (void)path;
    (void)out;
    return NULL;
#else
    if (!path || !path[0] || !out)
        return NULL;
    return xlang_path_realpath(path, out);
#endif
}

/* wave218: public pure thin lives in labi_path_io.x (hybrid L3);
 * mega cold twin under #ifndef XLANG_LABI_PATH_IO_FROM_X.
 * Cap residual: link_abi_realpath_cap_impl (POSIX realpath; Windows null always mega).
 * Why: hybrid still had realpath_cap body always mega C (gates+realpath).
 * PLATFORM: SHARED orch / POSIX realpath residual. */
#ifndef XLANG_LABI_PATH_IO_FROM_X
const char *link_abi_realpath_cap(const char *path, char *out) {
    if (!path || !path[0] || !out)
        return NULL;
    return link_abi_realpath_cap_impl(path, out);
}
#else
const char *link_abi_realpath_cap(const char *path, char *out);
#endif

/**
 * Cap residual (wave185): heap-duplicate a C string for multi-call-independent path returns.
 * Pure orch xlang_rel_o_path_from_argv0 must never return BSS/static — concurrent invoke_cc
 * keeps 30+ pointers; static would alias all to the last call.
 * Null s → strdup(""); never returns a pointer into caller buffers.
 * G.7: single authority wrap of host/freestanding strdup (no .x libc strdup export —
 * uint8_t* vs char* clashes under g05 -E string.h).
 * PLATFORM: SHARED — malloc heap; freestanding bootstrap_nostdlib provides strdup.
 */
const char *link_abi_cstr_dup(const char *s) {
    if (!s)
        return strdup("");
    return strdup(s);
}

/**
 * 检查 path 是否已在 ld argv 中（realpath 去重，避免 /src/std/... 与 -L 解析路径重复入链）。
 */
/* wave146：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: cstr eq + argv scan; Cap residual link_abi_realpath_cap.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path) {
    int k;
    /** 勿放栈上：nostdlib xlang_asm 在 elf emit 后主栈已深，8KiB×递归 realpath 易 SIGSEGV。 */
    static char abs_new[PATH_MAX];
    static char abs_exist[PATH_MAX];
    const char *use_new;
    if (!argv || la <= 0 || !path || !path[0])
        return 0;
    use_new = path;
#if !defined(_WIN32) && !defined(_WIN64)
    if (link_abi_realpath_cap(path, abs_new) != NULL)
        use_new = abs_new;
#endif
    for (k = 0; k < la; k++) {
        const char *exist = argv[k];
        if (!exist || !exist[0])
            continue;
        if (strcmp(exist, path) == 0 || strcmp(exist, use_new) == 0)
            return 1;
#if !defined(_WIN32) && !defined(_WIN64)
        if (link_abi_realpath_cap(exist, abs_exist) != NULL && strcmp(abs_exist, use_new) == 0)
            return 1;
#endif
    }
    return 0;
}
#else
int link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path);
#endif




/**
 * 将已解析 .o 路径拷入 bank 后追加到 ld argv（避免静态路径缓冲被后续解析覆盖）。
 */
/* wave147：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: capacity + has_obj dedup + append; Cap residual bank_push.
 * bank is opaque void* (≡ pure .x *u8 / cold twin / invoke_ld_list decls).
 * PLATFORM: SHARED — G.7 single authority; L4 cold TU signature unify. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la,
    const char *p) {
    if (!p || !p[0] || !la || *la >= max_la - 1)
        return;
    if (bank) {
        const char *bp = xlang_asm_ld_bank_push((ShuAsmLdPathBank *)bank, p);
        if (bp)
            p = bp;
    }
    if (link_abi_asm_ld_argv_has_obj(argv, *la, p))
        return;
    argv[(*la)++] = p;
}
#else
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la,
    const char *p);
#endif




/* wave148：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: capacity + resolve ladder + hard bank + has_obj/append; Cap residual skip/rel/bank/diag.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2. */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, int *flag_out) {
    const char *p = NULL;
    int debug_runtime_obj = 0;
    if (!la || *la >= max_la - 1)
        return 0;
    if (rel && (strcmp(rel, "compiler/runtime_asm_io_stubs.o") == 0
            || strcmp(rel, "compiler/runtime_process_argv.o") == 0))
        debug_runtime_obj = 1;
    /* wave223 G.7: link_abi_getenv (not raw getenv). */
    if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
        link_diag_ld_debug_push(rel, "primary", primary ? primary : "(null)");
    if (primary && primary[0])
        p = asm_link_obj_skip_missing(primary);
    if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
        link_diag_ld_debug_push(rel, "after-primary", p ? p : "(null)");
    if (!p && rel && rel[0])
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, rel));
    if (!p && bank && rel && rel[0])
        p = xlang_asm_ld_try_under_lib_roots(rel, lib_roots, n_lib_roots, bank);
    if (!p)
        return 0;
    /* 路径须拷入 bank：xlang_rel_o_path_from_argv0 / xlang_runtime_*_o_path 用静态缓冲，勿把裸指针留到 argv。 */
    if (bank) {
        const char *bp = xlang_asm_ld_bank_push(bank, p);
        if (bp)
            p = bp;
        else
            return 0;
    }
    if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
        link_diag_ld_debug_push(rel, "final", p ? p : "(null)");
    if (link_abi_asm_ld_argv_has_obj(argv, *la, p))
        return 0;
    argv[(*la)++] = p;
    if (flag_out)
        *flag_out = 1;
    return 1;
}
#else
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, int *flag_out);
#endif




/**
 * F-03：仅当对应 std/*.o 已入链时才追加 runtime_*_glue.o，避免 glue 引用 log_write_c 等未定义符号。
 * ensure_fn 非 NULL 时在 push 前 cc -c 生成 glue .o（Docker/CI 无预编译 glue 时须 ensure）。
 * wave149：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: have_std gate + Cap residual call_ensure + pure peer push_obj.
 * Cap residual: link_abi_call_ensure_argv0 holds C function-pointer call.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
/* Cap residual always: invoke ensure(argv0) through C fnptr (pure cannot form C fnptr calls).
 * ensure_fn is raw pointer bits (void*) so pure .x *u8 and C function pointers both work.
 * PLATFORM: SHARED. */
int link_abi_call_ensure_argv0(void *ensure_fn, const char *link_argv0) {
    if (!ensure_fn)
        return 0;
    return ((int (*)(const char *))ensure_fn)(link_argv0);
}

#ifndef XLANG_LABI_PATH_PURE_FROM_X
void link_abi_asm_ld_push_glue_after_std(int have_std, int (*ensure_fn)(const char *argv0),
    const char *glue_primary, const char *link_argv0, const char *glue_rel, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la) {
    if (!have_std)
        return;
    if (ensure_fn && link_abi_call_ensure_argv0((void *)ensure_fn, link_argv0) != 0)
        return;
    link_abi_asm_ld_push_obj(glue_primary, link_argv0, glue_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
}
#else
/* Hybrid: pure .x authority; ensure_fn pointer-sized (fnptr bits). Keep C fnptr type for call sites. */
void link_abi_asm_ld_push_glue_after_std(int have_std, int (*ensure_fn)(const char *argv0),
    const char *glue_primary, const char *link_argv0, const char *glue_rel, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la);
#endif




/* PLATFORM: POSIX (linux||apple) — block historically opened around needs_async_scheduler;
 * wave130 moved pure orch to labi_ondemand_list; keep #if for push_minimal + nested linux only. */
#if defined(__linux__) || defined(__APPLE__)
/**
 * wave130: needs_async_scheduler pure orch lives in labi_ondemand_list
 * (labi_od_async_scheduler_sym_* product table ×35 exact + pure scan; not here).
 * Exact symbols only (no prefix probes). Product complete: coop/cps/frame/run/task/worker/io
 * + async read/write complete surface (G.7 single product table).
 * Invariant: on_demand push of std/async/scheduler.o still gates via this orch.
 * PLATFORM: SHARED (hybrid L8b; cold twin under ondemand include).
 */

/**
 * wave123: needs_core_mem pure orch lives in labi_ondemand_list
 * (labi_od_core_mem_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 */

/**
 * wave124: needs_core_slice pure orch lives in labi_ondemand_list
 * (labi_od_core_slice_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 */

/**
 * wave125: needs_std_heap_page_mmap pure orch lives in labi_ondemand_list
 * (labi_od_page_mmap_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 * F-no-libc NL-03: freestanding mmap bump heap gate; page_mmap.o + transitive linux/core_mem.
 */

/**
 * wave126: needs_std_sys_linux pure orch lives in labi_ondemand_list
 * (labi_od_sys_linux_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 * F-no-libc: freestanding Linux syscall thin wrappers; product linux.o gate.
 */

/**
 * wave127: needs_std_sys pure orch lives in labi_ondemand_list
 * (labi_od_sys_sym_* product table + pure scan; not here).
 * Exact symbols only (no prefix probes).
 * F-no-libc: std.sys facade (write_stdout/read/close/exit); product sys.o gate.
 * On Linux sys.o may transitively need linux.o via cfg target_os.
 */

/**
 * nostdlib minimal gcc link still needs compiler runtime stubs; hello depends on
 * std_fmt_print / std_fmt_println (runtime_asm_io_stubs; PLATFORM: SHARED).
 * popen 桩恒失败时 has_undef 误判为自包含，勿因此省略 io_stubs。
 * wave150：pure orch in labi_path_pure.x (hybrid L0);
 * mega cold twin under #ifndef XLANG_LABI_PATH_PURE_FROM_X.
 * Pure: Cap residual *_o_path primary + pure peer push_obj ×3.
 * Cap residual: xlang_runtime_asm_io_stubs_o_path / process_argv_o_path / panic_o_path.
 * PLATFORM: SHARED — G.7 single authority; dual-end L2.
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
void link_abi_asm_ld_push_minimal_runtime_objs(const char *link_argv0, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la) {
    /* Cold twin prefers same Cap residual *_o_path as pure .x (static buf ≡ stack copy). */
    const char *io_stubs_p = xlang_runtime_asm_io_stubs_o_path(link_argv0);
    const char *process_argv_p = xlang_runtime_process_argv_o_path(link_argv0);
    link_abi_asm_ld_push_obj(io_stubs_p, link_argv0,
        "compiler/runtime_asm_io_stubs.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    link_abi_asm_ld_push_obj(process_argv_p, link_argv0,
        "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    link_abi_asm_ld_push_obj(xlang_runtime_panic_o_path(link_argv0), link_argv0,
        "compiler/runtime_panic.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    /* wave253: companion user-domain face (weak; residual declare-only; panic C strong wins). */
    link_abi_asm_ld_push_obj(xlang_runtime_link_abi_user_env_o_path(link_argv0), link_argv0,
        "compiler/runtime_link_abi_user_env.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
}
#else
void link_abi_asm_ld_push_minimal_runtime_objs(const char *link_argv0, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la);
#endif




#if defined(__linux__)
/**
 * Capacity-guarded argv push for Linux hosted ld.
 * PLATFORM: LINUX — product -o must not spawn gcc as the linker driver.
 */
static int labi_linux_ld_push(const char **argv, int *la, int cap, const char *s) {
    if (argv == NULL || la == NULL || s == NULL || s[0] == 0)
        return 0;
    if (*la < 0 || *la >= cap - 1)
        return 0;
    argv[(*la)++] = s;
    return 1;
}

static const char *labi_linux_first_readable(const char *const *cands) {
    int i;
    if (cands == NULL)
        return 0;
    for (i = 0; cands[i] != 0; i++) {
        if (link_abi_path_readable(cands[i]) != 0)
            return cands[i];
    }
    return 0;
}

/**
 * Glibc PIE crt + interpreter for hosted product -o (no gcc/cc driver).
 * Historical SIGSEGV: bare `ld -e main` skipped libc `_start` / `__libc_start_main`.
 * G.7: complete existing ld; same multiarch candidates as pure_ld_hosted_crt1
 * (filesystem only — do not spawn gcc -print-file-name / collect2).
 * PLATFORM: LINUX.
 */
static const char *labi_linux_hosted_scrt1(void) {
    static const char *cands[5];
    cands[0] = "/usr/lib/x86_64-linux-gnu/Scrt1.o";
    cands[1] = "/usr/lib/aarch64-linux-gnu/Scrt1.o";
    cands[2] = "/usr/lib64/Scrt1.o";
    cands[3] = "/usr/lib/Scrt1.o";
    cands[4] = 0;
    return labi_linux_first_readable(cands);
}

static const char *labi_linux_hosted_crti(void) {
    static const char *cands[5];
    cands[0] = "/usr/lib/x86_64-linux-gnu/crti.o";
    cands[1] = "/usr/lib/aarch64-linux-gnu/crti.o";
    cands[2] = "/usr/lib64/crti.o";
    cands[3] = "/usr/lib/crti.o";
    cands[4] = 0;
    return labi_linux_first_readable(cands);
}

static const char *labi_linux_hosted_crtn(void) {
    static const char *cands[5];
    cands[0] = "/usr/lib/x86_64-linux-gnu/crtn.o";
    cands[1] = "/usr/lib/aarch64-linux-gnu/crtn.o";
    cands[2] = "/usr/lib64/crtn.o";
    cands[3] = "/usr/lib/crtn.o";
    cands[4] = 0;
    return labi_linux_first_readable(cands);
}

static const char *labi_linux_hosted_dyn_linker(void) {
    static const char *cands[6];
    cands[0] = "/lib64/ld-linux-x86-64.so.2";
    cands[1] = "/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2";
    cands[2] = "/lib/ld-linux-x86-64.so.2";
    cands[3] = "/lib/ld-linux-aarch64.so.1";
    cands[4] = "/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1";
    cands[5] = 0;
    return labi_linux_first_readable(cands);
}

/**
 * Prefix hosted ld argv: driver, PIE/relro/noexecstack/now, --gc-sections,
 * dynamic linker, -o exe, Scrt1, crti, -L glibc dirs.
 * Caller then appends user/std objects and -l* (unix tail). Finish adds crtn.
 * gcc crtbeginS is not required (X emit does not need gcc .ctors wrapper).
 */
static int labi_linux_hosted_ld_begin(const char **argv, int *la, int cap, const char *exe_path) {
    const char *scrt1;
    const char *crti;
    const char *dyn;
    static const char *ldirs[9];
    static char lbufs[8][96];
    int i;
    int nL;

    scrt1 = labi_linux_hosted_scrt1();
    crti = labi_linux_hosted_crti();
    dyn = labi_linux_hosted_dyn_linker();
    if (scrt1 == NULL || crti == NULL || dyn == NULL || exe_path == NULL || exe_path[0] == 0)
        return -1;
    if (!labi_linux_ld_push(argv, la, cap, labi_ld_driver_ld()))
        return -1;
    (void)labi_linux_ld_push(argv, la, cap, "--eh-frame-hdr");
#if defined(__aarch64__)
    (void)labi_linux_ld_push(argv, la, cap, "-m");
    (void)labi_linux_ld_push(argv, la, cap, "aarch64linux");
#elif defined(__x86_64__)
    (void)labi_linux_ld_push(argv, la, cap, "-m");
    (void)labi_linux_ld_push(argv, la, cap, "elf_x86_64");
#endif
    if (!labi_linux_ld_push(argv, la, cap, "-dynamic-linker"))
        return -1;
    if (!labi_linux_ld_push(argv, la, cap, dyn))
        return -1;
    /* ld-native form of labi_linux_harden_flag_* (drop -fpie / -Wl, prefix). */
    (void)labi_linux_ld_push(argv, la, cap, "-pie");
    (void)labi_linux_ld_push(argv, la, cap, "-z");
    (void)labi_linux_ld_push(argv, la, cap, "noexecstack");
    (void)labi_linux_ld_push(argv, la, cap, "-z");
    (void)labi_linux_ld_push(argv, la, cap, "relro");
    (void)labi_linux_ld_push(argv, la, cap, "-z");
    (void)labi_linux_ld_push(argv, la, cap, "now");
    (void)labi_linux_ld_push(argv, la, cap, "--gc-sections");
    (void)labi_linux_ld_push(argv, la, cap, "--allow-multiple-definition");
    if (!labi_linux_ld_push(argv, la, cap, labi_ld_flag_o()))
        return -1;
    if (!labi_linux_ld_push(argv, la, cap, exe_path))
        return -1;
    if (!labi_linux_ld_push(argv, la, cap, scrt1))
        return -1;
    if (!labi_linux_ld_push(argv, la, cap, crti))
        return -1;
    ldirs[0] = "/usr/lib/x86_64-linux-gnu";
    ldirs[1] = "/lib/x86_64-linux-gnu";
    ldirs[2] = "/usr/lib/aarch64-linux-gnu";
    ldirs[3] = "/lib/aarch64-linux-gnu";
    ldirs[4] = "/usr/lib64";
    ldirs[5] = "/lib64";
    ldirs[6] = "/usr/lib";
    ldirs[7] = "/lib";
    ldirs[8] = 0;
    nL = 0;
    for (i = 0; ldirs[i] != 0 && nL < 8; i++) {
        size_t n;
        if (link_abi_path_readable(ldirs[i]) == 0)
            continue;
        n = strlen(ldirs[i]);
        if (n + 3 >= sizeof lbufs[0])
            continue;
        lbufs[nL][0] = '-';
        lbufs[nL][1] = 'L';
        memcpy(lbufs[nL] + 2, ldirs[i], n + 1);
        (void)labi_linux_ld_push(argv, la, cap, lbufs[nL]);
        nL++;
    }
    return 0;
}

/**
 * Rewrite gcc-only `-pthread` (unix tail libs) to `-lpthread`, append crtn, spawn ld.
 * Do not fall back to gcc. PATH: xlang_linux_ld_child_path (nostdlib parent may lack PATH).
 */
static int labi_linux_hosted_ld_finish_and_spawn(const char **argv, int *la, int cap, const char *debug_tag) {
    const char *crtn;
    int i;
    int rc;

    if (argv == NULL || la == NULL)
        return -1;
    for (i = 0; i < *la; i++) {
        if (argv[i] != NULL && strcmp(argv[i], "-pthread") == 0)
            argv[i] = labi_ld_flag_lpthread();
    }
    crtn = labi_linux_hosted_crtn();
    if (crtn == NULL || !labi_linux_ld_push(argv, la, cap, crtn)) {
        link_diag_tool_status("ld", -1);
        return -1;
    }
    argv[*la] = NULL;
    if (debug_tag != NULL && link_abi_getenv("XLANG_DEBUG_LD"))
        link_diag_ld_debug_argv(debug_tag, argv);
    xlang_linux_ld_child_path();
    rc = xlang_spawn_sync(labi_ld_driver_ld(), (const char *const *)argv);
    if (rc != 0) {
        link_diag_tool_status("ld", rc);
        return -1;
    }
    return 0;
}

/**
 * nostdlib xlang_asm: self-contained user.o hosted ld (user.o + runtime stubs + -lc).
 * pipeline/elf emit 后主栈已很深，完整 ld argv 构建（realpath 去重、popen nm）易 SIGSEGV；
 * 固定 argv + static path bank，不扫描 std/*.o。
 * 参数：link_eff 有效 argv0/compiler 目录；lib_roots 与 driver -L 一致。
 * 返回值：0 成功，-1 失败。
 * PLATFORM: LINUX — G.7 same hosted ld as xlang_asm_invoke_ld_platform (no gcc driver).
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_asm_nostdlib_minimal_selfcontained_exe_link(const char *o_path, const char *exe_path,
    const char *link_eff, const char **lib_roots, int n_lib_roots) {
    static ShuAsmLdPathBank bank;
    const char *argv[XLANG_LD_ARGV_CAP];
    int la = 0;

    if (!o_path || !exe_path || !link_eff)
        return -1;
    bank.n = 0;
    memset(bank.slots, 0, sizeof bank.slots);
    if (labi_linux_hosted_ld_begin(argv, &la, XLANG_LD_ARGV_CAP, exe_path) != 0) {
        link_diag_tool_status("ld", -1);
        return -1;
    }
    if (la < XLANG_LD_ARGV_CAP - 1)
        argv[la++] = o_path;
    link_abi_asm_ld_push_minimal_runtime_objs(link_eff, lib_roots, n_lib_roots, &bank, argv, &la,
        XLANG_LD_ARGV_CAP);
    if (la < XLANG_LD_ARGV_CAP - 1)
        argv[la++] = labi_ld_flag_lc();
    /* G.7: CLI user .o on self-contained minimal asm link too. */
    xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
    return labi_linux_hosted_ld_finish_and_spawn(argv, &la, XLANG_LD_ARGV_CAP, "minimal ld argv");
}



#endif /* __linux__ */
#endif
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

/* G-02f-271 L8 std list pure plan (+ accessors) */
#ifndef XLANG_LABI_STD_LIST_FROM_X
enum {
  LABI_STD_OP_STD = 1,
  LABI_STD_OP_IO_STUBS = 2,
  LABI_STD_OP_PRIMARY_PANIC = 3,
  LABI_STD_OP_PRIMARY_TIME_OS = 4,
  LABI_STD_OP_PRIMARY_RANDOM_FILL = 5,
  LABI_STD_OP_PRIMARY_ENV_OS = 6,
  LABI_STD_OP_GLUE_THREAD = 10,
  LABI_STD_OP_GLUE_SYNC_PAIR = 11,
  LABI_STD_OP_GLUE_CRYPTO_PAIR = 12,
  LABI_STD_OP_GLUE_LOG = 13,
  LABI_STD_OP_GLUE_ATOMIC = 14,
  LABI_STD_OP_GLUE_CHANNEL = 15,
  LABI_STD_OP_GLUE_BACKTRACE = 16,
  LABI_STD_OP_GLUE_MATH = 17,
  LABI_STD_OP_GLUE_SQLITE = 18,
  LABI_STD_OP_GLUE_DYNLIB = 19,
  LABI_STD_OP_GLUE_HTTP = 20,
  LABI_STD_OP_TASK_SPECIAL = 30
};
typedef struct LabiStdPlanStep {
  int op;
  const char *rel;
  int flag_kind;
} LabiStdPlanStep;
static const LabiStdPlanStep g_labi_std_plan[] = {
    {LABI_STD_OP_IO_STUBS, "compiler/runtime_asm_io_stubs.o", 0},
    /* 勿无条件硬链 core/mem/mem.o 与 heap.o：用户 co-emit 已提供 core_mem_* 时会 duplicate。
     * heap/core_mem 仅走 on_demand（link_abi_link_needs_std_heap_import /
     * link_abi_user_o_needs_core_mem）；bank/argv 已扩到 192 防漏推。 */
    {LABI_STD_OP_STD, "std/process/process.o", 1},
    {LABI_STD_OP_STD, "std/string/string.o", 0},
    {LABI_STD_OP_STD, "std/path/path.o", 0},
    {LABI_STD_OP_STD, "std/runtime/runtime.o", 0},
    {LABI_STD_OP_PRIMARY_PANIC, "compiler/runtime_panic.o", 0},
    {LABI_STD_OP_STD, "std/thread/thread.o", 2},
    {LABI_STD_OP_GLUE_THREAD, "compiler/runtime_thread_glue.o", 0},
    {LABI_STD_OP_PRIMARY_TIME_OS, "compiler/runtime_time_os.o", 0},
    {LABI_STD_OP_STD, "std/time/time.o", 0},
    {LABI_STD_OP_PRIMARY_RANDOM_FILL, "compiler/runtime_random_fill.o", 0},
    {LABI_STD_OP_STD, "std/random/random.o", 0},
    {LABI_STD_OP_PRIMARY_ENV_OS, "compiler/runtime_env_os.o", 0},
    {LABI_STD_OP_STD, "std/env/env.o", 0},
    /* PLATFORM: SHARED — formal fs.o for asm (std.fs co-emit skipped); fk0 gated. */
    {LABI_STD_OP_STD, "std/fs/fs.o", 0},
    {LABI_STD_OP_STD, "std/sync/sync.o", 3},
    {LABI_STD_OP_GLUE_SYNC_PAIR, "compiler/runtime_sync_lock_diag_tls.o", 0},
    {LABI_STD_OP_STD, "std/encoding/encoding.o", 0},
    {LABI_STD_OP_STD, "std/base64/base64.o", 0},
    {LABI_STD_OP_STD, "std/crypto/crypto.o", 4},
    {LABI_STD_OP_GLUE_CRYPTO_PAIR, "compiler/runtime_ed25519_ref10_glue.o", 0},
    {LABI_STD_OP_STD, "std/log/log.o", 5},
    {LABI_STD_OP_GLUE_LOG, "compiler/runtime_log_os.o", 0},
    {LABI_STD_OP_STD, "std/atomic/atomic.o", 6},
    {LABI_STD_OP_GLUE_ATOMIC, "compiler/runtime_atomic_glue.o", 0},
    {LABI_STD_OP_STD, "std/channel/channel.o", 7},
    {LABI_STD_OP_GLUE_CHANNEL, "compiler/runtime_channel_glue.o", 0},
    {LABI_STD_OP_STD, "std/backtrace/backtrace.o", 8},
    {LABI_STD_OP_GLUE_BACKTRACE, "compiler/runtime_backtrace_platform.o", 0},
    {LABI_STD_OP_STD, "std/hash/hash.o", 0},
    {LABI_STD_OP_STD, "std/math/math.o", 9},
    {LABI_STD_OP_GLUE_MATH, "compiler/runtime_math_libm.o", 0},
    {LABI_STD_OP_STD, "std/sort/sort.o", 0},
    /* PLATFORM: SHARED — std.vec is link_only; on-demand via fk0 UNDEF probes. */
    {LABI_STD_OP_STD, "std/vec/vec.o", 0},
    {LABI_STD_OP_STD, "std/ffi/ffi.o", 0},
    {LABI_STD_OP_STD, "std/db/sqlite/sqlite.o", 10},
    {LABI_STD_OP_GLUE_SQLITE, "compiler/runtime_sqlite_glue.o", 0},
    {LABI_STD_OP_STD, "std/elf/elf.o", 11},
    {LABI_STD_OP_STD, "std/json/json.o", 0},
    {LABI_STD_OP_STD, "std/csv/csv.o", 0},
    {LABI_STD_OP_STD, "std/regex/regex.o", 0},
    {LABI_STD_OP_STD, "std/unicode/unicode.o", 0},
    {LABI_STD_OP_STD, "std/dynlib/dynlib.o", 12},
    {LABI_STD_OP_GLUE_DYNLIB, "compiler/runtime_dynlib_os.o", 0},
    {LABI_STD_OP_STD, "std/http/http.o", 13},
    {LABI_STD_OP_GLUE_HTTP, "compiler/runtime_http_glue.o", 0},
    {LABI_STD_OP_STD, "std/socketio/socketio.o", 0},
    {LABI_STD_OP_STD, "std/tar/tar.o", 0},
    {LABI_STD_OP_STD, "std/simd/simd.o", 0},
    {LABI_STD_OP_STD, "std/context/context.o", 0},
    {LABI_STD_OP_STD, "std/error/error.o", 0},
    {LABI_STD_OP_STD, "std/datetime/datetime.o", 0},
    {LABI_STD_OP_STD, "std/uuid/uuid.o", 0},
    {LABI_STD_OP_STD, "std/url/url.o", 0},
    {LABI_STD_OP_STD, "std/cli/cli.o", 0},
    {LABI_STD_OP_STD, "std/security/security.o", 0},
    {LABI_STD_OP_STD, "std/config/config.o", 0},
    {LABI_STD_OP_STD, "std/cache/cache.o", 0},
    {LABI_STD_OP_STD, "std/trace/trace.o", 0},
    {LABI_STD_OP_TASK_SPECIAL, "std/task/task.o", 0},
};
int labi_std_plan_count(void) {
  return (int)(sizeof g_labi_std_plan / sizeof g_labi_std_plan[0]);
}
int labi_std_plan_step_at(int i, int *op_out, const char **rel_out, int *flag_kind_out) {
  int n = labi_std_plan_count();
  if (i < 0 || i >= n)
    return 0;
  if (op_out)
    *op_out = g_labi_std_plan[i].op;
  if (rel_out)
    *rel_out = g_labi_std_plan[i].rel;
  if (flag_kind_out)
    *flag_kind_out = g_labi_std_plan[i].flag_kind;
  return 1;
}
int labi_std_default_std_rel_count(void) {
  int n = labi_std_plan_count();
  int i;
  int c = 0;
  for (i = 0; i < n; i++) {
    if (g_labi_std_plan[i].op == LABI_STD_OP_STD)
      c = c + 1;
  }
  return c;
}
const char *labi_std_default_std_rel_at(int j) {
  int n = labi_std_plan_count();
  int i;
  int c = 0;
  if (j < 0)
    return NULL;
  for (i = 0; i < n; i++) {
    if (g_labi_std_plan[i].op != LABI_STD_OP_STD)
      continue;
    if (c == j)
      return g_labi_std_plan[i].rel;
    c = c + 1;
  }
  return NULL;
}
#else
enum {
  LABI_STD_OP_STD = 1,
  LABI_STD_OP_IO_STUBS = 2,
  LABI_STD_OP_PRIMARY_PANIC = 3,
  LABI_STD_OP_PRIMARY_TIME_OS = 4,
  LABI_STD_OP_PRIMARY_RANDOM_FILL = 5,
  LABI_STD_OP_PRIMARY_ENV_OS = 6,
  LABI_STD_OP_GLUE_THREAD = 10,
  LABI_STD_OP_GLUE_SYNC_PAIR = 11,
  LABI_STD_OP_GLUE_CRYPTO_PAIR = 12,
  LABI_STD_OP_GLUE_LOG = 13,
  LABI_STD_OP_GLUE_ATOMIC = 14,
  LABI_STD_OP_GLUE_CHANNEL = 15,
  LABI_STD_OP_GLUE_BACKTRACE = 16,
  LABI_STD_OP_GLUE_MATH = 17,
  LABI_STD_OP_GLUE_SQLITE = 18,
  LABI_STD_OP_GLUE_DYNLIB = 19,
  LABI_STD_OP_GLUE_HTTP = 20,
  LABI_STD_OP_TASK_SPECIAL = 30
};
int labi_std_plan_count(void);
int labi_std_plan_step_at(int i, int *op_out, const char **rel_out, int *flag_kind_out);
int labi_std_default_std_rel_count(void);
const char *labi_std_default_std_rel_at(int j);
#endif

/* wave135: labi_std_fk0_user_needs_rel pure orch lives in labi_ondemand_list
 * (16 rel path needles × 106 exact UNDEF; Cap strstr + undef_sym).
 * null/empty user_o → 1; unknown rel → 0. Was static mega body (G-02f-165/271).
 * Cold twin under #ifndef ONDEMAND_LIST_FROM_X; hybrid L8b pure .x.
 * PLATFORM: SHARED — G.7 complete product surface; dual-end L2.
 */
int labi_std_fk0_user_needs_rel(const char *user_o, const char *rel);
/* wave190: labi_std_fk_user_needs pure orch (fk 1–13 plan gates; Cap undef_sym).
 * null/empty user_o → 1; unknown fk → 1. Was always-mega inline in append_std.
 * Cold twin under #ifndef ONDEMAND_LIST_FROM_X; hybrid L8b pure .x.
 * PLATFORM: SHARED — G.7 complete wave135 fk0 sibling; dual-end L2.
 */
int labi_std_fk_user_needs(const char *user_o, int fk);

/*
 * wave132–134: labi_user_needs_runtime_{time_os,random_fill,env_os,process_argv}
 * + labi_user_needs_std_task pure orch live in labi_ondemand_list
 * (product tables + pure scan; null/empty → 1).
 * wave135: labi_std_fk0_user_needs_rel pure (fk0 plan gate; Cap strstr).
 * wave190: labi_std_fk_user_needs pure (fk 1–13 plan gates; Cap undef_sym).
 * Cap residual: undef_sym stays mega. Call sites need forward decls before
 * the ondemand include block. PLATFORM: SHARED.
 */
int labi_user_needs_runtime_time_os(const char *user_o);
int labi_user_needs_runtime_random_fill(const char *user_o);
int labi_user_needs_runtime_env_os(const char *user_o);
int labi_user_needs_runtime_process_argv(const char *user_o);
/* wave134: TASK_SPECIAL bulk gate pure; was static mega body. */
int labi_user_needs_std_task(const char *user_o);

void xlang_asm_ld_append_std_objs(const char *link_argv0, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags) {
    /* 兼容旧调用：无 user_o 时走硬链。新调用经 wrapper 传入 o_path。 */
    xlang_asm_ld_append_std_objs_for_user(link_argv0, NULL, lib_roots, n_lib_roots, bank, argv, la, max_la, flags);
}

/* wave196: xlang_asm_ld_append_std_objs_for_user plan shell pure orch —
 * body removed from mega (lives in labi_invoke_ld_list L6 pure / cold twin via #include).
 * Hybrid XLANG_LABI_INVOKE_LD_LIST_FROM_X → L6 pure; cold path defines via include.
 * Pure: flags/local_have init + plan_count/step_at loop + dispatch wave190–195 leaves
 *   + process_argv complement; Cap residual inside leaf peers / L8 plan table.
 * Why: hybrid still had plan loop shell always-mega inline after wave190–195 leaf pure.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_INVOKE_LD_LIST_FROM_X
/* cold twin body is in seeds/labi_invoke_ld_list.from_x.c (#include above). */
#else
void xlang_asm_ld_append_std_objs_for_user(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
#endif

/* G-02f-272 L8b on_demand list pure */
#ifndef XLANG_LABI_ONDEMAND_LIST_FROM_X
#include "seeds/labi_ondemand_list.from_x.c"
#else
int labi_od_simple_group_count(void);
int labi_od_simple_group_sym_count(int g);
const char *labi_od_simple_group_sym_at(int g, int i);
const char *labi_od_simple_group_rel(int g);
int labi_od_kv_sym_count(void);
const char *labi_od_kv_sym_at(int i);
const char *labi_od_kv_rel(void);
const char *labi_od_kv_glue_rel(void);
int labi_od_arrow_sym_count(void);
const char *labi_od_arrow_sym_at(int i);
const char *labi_od_arrow_rel(void);
const char *labi_od_arrow_glue_rel(void);
int labi_od_time_sym_count(void);
const char *labi_od_time_sym_at(int i);
const char *labi_od_time_rel(void);
const char *labi_od_time_os_rel(void);
int labi_od_queue_sym_count(void);
const char *labi_od_queue_sym_at(int i);
const char *labi_od_queue_rel(void);
const char *labi_od_queue_contention_rel(void);
/* wave118–135 needs_std_net/set/map/queue/test + needs_core_mem/slice + needs_std_heap_page_mmap + needs_std_sys_linux + needs_std_sys + needs_std_heap_api + needs_heap_user_syms + needs_async_scheduler + compress family + labi_user_needs_runtime time_os/random_fill/env_os/process_argv + labi_user_needs_std_task + labi_std_fk0_user_needs_rel pure orch (L8b pure .x / cold seed). */
int labi_od_net_sym_count(void);
const char *labi_od_net_sym_at(int i);
int link_abi_user_o_needs_std_net(const char *user_o);
int labi_od_set_sym_count(void);
const char *labi_od_set_sym_at(int i);
int link_abi_user_o_needs_std_set(const char *user_o);
int labi_od_map_sym_count(void);
const char *labi_od_map_sym_at(int i);
int link_abi_user_o_needs_std_map(const char *user_o);
int labi_od_queue_api_sym_count(void);
const char *labi_od_queue_api_sym_at(int i);
int link_abi_user_o_needs_std_queue(const char *user_o);
int labi_od_test_sym_count(void);
const char *labi_od_test_sym_at(int i);
int link_abi_user_o_needs_std_test(const char *user_o);
int labi_od_core_mem_sym_count(void);
const char *labi_od_core_mem_sym_at(int i);
int link_abi_user_o_needs_core_mem(const char *user_o);
int labi_od_core_slice_sym_count(void);
const char *labi_od_core_slice_sym_at(int i);
int link_abi_user_o_needs_core_slice(const char *user_o);
int labi_od_page_mmap_sym_count(void);
const char *labi_od_page_mmap_sym_at(int i);
int link_abi_user_o_needs_std_heap_page_mmap(const char *user_o);
int labi_od_sys_linux_sym_count(void);
const char *labi_od_sys_linux_sym_at(int i);
int link_abi_user_o_needs_std_sys_linux(const char *user_o);
int link_abi_user_o_needs_std_sys_macos(const char *user_o);
int labi_od_sys_sym_count(void);
const char *labi_od_sys_sym_at(int i);
int link_abi_user_o_needs_std_sys(const char *user_o);
int labi_od_heap_api_sym_count(void);
const char *labi_od_heap_api_sym_at(int i);
int link_abi_user_o_needs_std_heap_api(const char *user_o);
int labi_od_heap_user_sym_count(void);
const char *labi_od_heap_user_sym_at(int i);
int link_abi_user_o_needs_heap_user_syms(const char *user_o);
int labi_od_async_scheduler_sym_count(void);
const char *labi_od_async_scheduler_sym_at(int i);
int link_abi_user_o_needs_async_scheduler(const char *user_o);
int labi_od_zlib_undef_sym_count(void);
const char *labi_od_zlib_undef_sym_at(int i);
const char *labi_od_compress_zlib_marker(void);
int labi_od_zstd_undef_sym_count(void);
const char *labi_od_zstd_undef_sym_at(int i);
const char *labi_od_compress_zstd_marker(void);
int labi_od_brotli_undef_sym_count(void);
const char *labi_od_brotli_undef_sym_at(int i);
const char *labi_od_compress_brotli_marker(void);
int link_abi_obj_needs_zlib(const char *obj_o);
int link_abi_obj_needs_zstd(const char *obj_o);
int link_abi_obj_needs_brotli(const char *obj_o);
int link_abi_user_o_needs_compress_libs(const char *user_o);
int labi_od_runtime_time_os_sym_count(void);
const char *labi_od_runtime_time_os_sym_at(int i);
int labi_user_needs_runtime_time_os(const char *user_o);
int labi_od_runtime_random_fill_sym_count(void);
const char *labi_od_runtime_random_fill_sym_at(int i);
int labi_user_needs_runtime_random_fill(const char *user_o);
int labi_od_runtime_env_os_sym_count(void);
const char *labi_od_runtime_env_os_sym_at(int i);
int labi_user_needs_runtime_env_os(const char *user_o);
int labi_od_runtime_process_argv_sym_count(void);
const char *labi_od_runtime_process_argv_sym_at(int i);
int labi_user_needs_runtime_process_argv(const char *user_o);
int labi_od_std_task_sym_count(void);
const char *labi_od_std_task_sym_at(int i);
int labi_user_needs_std_task(const char *user_o);
int labi_fk0_rel_count(void);
const char *labi_fk0_rel_at(int k);
int labi_fk0_sym_count(int k);
const char *labi_fk0_sym_at(int k, int i);
int labi_std_fk0_user_needs_rel(const char *user_o, const char *rel);
int labi_od_provides_core_mem_sym_count(void);
const char *labi_od_provides_core_mem_sym_at(int i);
int link_abi_user_o_provides_core_mem(const char *user_o);
int labi_od_provides_std_heap_sym_count(void);
const char *labi_od_provides_std_heap_sym_at(int i);
int link_abi_user_o_provides_std_heap(const char *user_o);
/* wave145 aggregate pure orch (L8b). */
int link_abi_link_needs_heap_user_c(const char *user_o, const char **argv, int la);
int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la);
const char *labi_od_rel_net(void);
const char *labi_od_rel_thread(void);
const char *labi_od_rel_heap(void);
const char *labi_od_rel_set(void);
const char *labi_od_rel_map(void);
const char *labi_od_rel_async_scheduler(void);
const char *labi_od_rel_core_mem(void);
const char *labi_od_rel_sys_linux(void);
const char *labi_od_rel_sys_macos(void);
const char *labi_od_rel_page_mmap(void);
const char *labi_od_rel_sys(void);
const char *labi_od_rel_core_slice(void);
const char *labi_od_rel_test(void);
const char *labi_od_rel_heap_user(void);
const char *labi_od_rel_scheduler_glue(void);
const char *labi_od_rel_thread_glue(void);
const char *labi_od_rel_net_udp_batch(void);
const char *labi_od_rel_net_workers(void);
const char *labi_od_rel_test_fn_invoke(void);
#endif

/* wave197: xlang_asm_ld_append_on_demand_user_objs pure orch —
 * body removed from mega (lives in labi_ondemand_list L8b pure / cold twin via #include).
 * Hybrid XLANG_LABI_ONDEMAND_LIST_FROM_X → L8b pure; cold path defines via include.
 * Pure: needs/provides peers + push/path/ensure compose; Cap residual ensure/skip/undef/fs.
 * Why: hybrid still had full on_demand IO shell always-mega after wave118–145 needs pure.
 * PLATFORM: SHARED orch. */
#ifndef XLANG_LABI_ONDEMAND_LIST_FROM_X
/* cold twin body is in seeds/labi_ondemand_list.from_x.c (#include above). */
#else
void xlang_asm_ld_append_on_demand_user_objs(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
#endif



/**
 * invoke_ld / driver_asm_invoke_ld 共用：ensure 链入对象并校验 freestanding 仅 Linux ELF。
 * 参数：link_eff 有效 link argv0；user_o 用户 .o；driver_freestanding 同 xlang_link_freestanding_enabled。
 * 返回值：0 成功，-1 失败。
 * wave186: pure orch in labi_ensure_list.x (hybrid L4);
 * mega cold twin under #ifndef XLANG_LABI_ENSURE_LIST_FROM_X (#include above).
 * Cap residual: freestanding peers + user_needs + ensure_* + debug report Cap.
 * PLATFORM: SHARED orch / LINUX freestanding via freestanding_enabled.
 */
#ifndef XLANG_LABI_ENSURE_LIST_FROM_X
/* cold twin body is in seeds/labi_ensure_list.from_x.c (#include above). */
#else
int xlang_asm_ld_prepare_for_exe_link(const char *link_eff, const char *user_o, int driver_freestanding,
    int use_macho_o, int use_coff_o);
#endif




#if defined(__linux__) || defined(__APPLE__)
/**
 * 用户 .o 是否无任何未定义符号（nm -u 为空）；用于 Linux 最小 hosted ld 链 user.o+-lc。
 * 参数：o_path 用户对象路径。
 * 返回值：1 有未定义符号或 nm 失败（保守），0 完全自包含。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_asm_user_o_has_undef_syms(const char *o_path) {
    char cmd[PATH_MAX + 160];
    FILE *fp;
    char line[512];
    size_t i;
    if (!o_path || !o_path[0])
        return 1;
    if ((size_t)snprintf(cmd, sizeof cmd, "nm -u '%s' 2>/dev/null", o_path) >= sizeof cmd)
        return 1;
    fp = popen(cmd, "r");
    if (!fp) {
#if defined(__linux__)
        /* PLATFORM: LINUX freestanding — popen stub; any ELF UNDEF forces full on_demand path. */
        return xlang_elf64_obj_scan_undef(o_path, NULL) ? 1 : 0;
#else
        return 0; /* nostdlib 无 popen：优先 gcc 最小链 user.o+-lc */
#endif
    }
    while (fgets(line, sizeof line, fp)) {
        for (i = 0; line[i]; i++) {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
                pclose(fp);
                return 1;
            }
        }
    }
    pclose(fp);
    return 0;
}




#endif /* __linux__ || __APPLE__ */

/**
 * macOS asm ld/clang：按 std 链入标记追加 -lm、压缩库、-lsqlite3、-pthread、-lSystem。
 * G-02f-66：主体 _impl；.x 门闩 null 检查后转发。
 */
/* wave156: xlang_asm_ld_append_mach_tail_libs_impl pure orch — body removed from mega
 * (was always-mega C over pure flag tables). Cold twin / hybrid pure always provide
 * the symbol via labi_invoke_ld_list (flags i32 layout + pure flag_* + peer compress).
 * PLATFORM: SHARED orch / MACOS consumers. */

/* G-02f-277 L9 gates */
#ifndef XLANG_LABI_GATES_FROM_X
void xlang_asm_ld_append_mach_tail_libs(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    const char **argv, int *la, int max_la, int append_lsystem) {
  if (flags == NULL) {
    return;
  }
  if (argv == NULL) {
    return;
  }
  if (la == NULL) {
    return;
  }
  if (*la < 0) {
    return;
  }
  {
    xlang_asm_ld_append_mach_tail_libs_impl(compress_o, user_o, flags, argv, la, max_la, append_lsystem);
  }
}
#else
void xlang_asm_ld_append_mach_tail_libs(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    const char **argv, int *la, int max_la, int append_lsystem);
#endif

/* wave157: xlang_asm_ld_append_unix_gcc_tail_libs_impl pure orch — body removed from mega
 * (was multi-branch always-mega with #if __linux__ / linux||apple). Cold twin / hybrid pure
 * always provide the symbol via labi_invoke_ld_list (host_is_linux + host_is_apple peers).
 * PLATFORM: SHARED orch / LINUX consumers. */

/* G-02f-277 L9 gates */
#ifndef XLANG_LABI_GATES_FROM_X
void xlang_asm_ld_append_unix_gcc_tail_libs(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    int need_pt, const char **argv, int *la, int max_la) {
  if (flags == NULL) {
    return;
  }
  if (argv == NULL) {
    return;
  }
  if (la == NULL) {
    return;
  }
  if (*la < 0) {
    return;
  }
  {
    xlang_asm_ld_append_unix_gcc_tail_libs_impl(compress_o, user_o, flags, need_pt, argv, la, max_la);
  }
}
#else
void xlang_asm_ld_append_unix_gcc_tail_libs(const char *compress_o, const char *user_o, const ShuAsmLdStdLinkFlags *flags,
    int need_pt, const char **argv, int *la, int max_la);
#endif

/* wave155: xlang_append_linux_link_harden_impl pure orch — body removed from mega
 * (was #if __linux__ real + #else no-op stub). Cold twin / hybrid pure always provide
 * the symbol via labi_invoke_cc_list (table scan is host-agnostic; callers stay Linux-gated).
 * PLATFORM: SHARED orch / LINUX consumers. */

/* G-02f-277 L9 gates */
#ifndef XLANG_LABI_GATES_FROM_X
void xlang_append_linux_link_harden(char *argv[], int *la, int cap) {
  if (argv == NULL) {
    return;
  }
  if (la == NULL) {
    return;
  }
  {
    xlang_append_linux_link_harden_impl(argv, la, cap);
  }
}
#else
void xlang_append_linux_link_harden(char *argv[], int *la, int cap);
#endif


#if defined(__APPLE__)
/**
 * Durable Darwin SDK path for product -o ld (no clang/cc driver).
 * PLATFORM: MACOS — G.7 same candidate list as compiler/scripts/pure_ld_shared.sh
 * pure_ld_platform_prefix. Prefer SDKROOT; then Xcode; then CommandLineTools.
 * Do not spawn xcrun/cc. Returns static storage; empty string on miss.
 */
static const char *labi_darwin_sdk_path(void) {
    static char buf[512];
    const char *env;
    static const char *cands[3];
    int i;
    size_t n;
    cands[0] = "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk";
    cands[1] = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk";
    cands[2] = 0;
    env = link_abi_getenv("SDKROOT");
    if (env && env[0] && link_abi_path_readable(env) != 0) {
        n = strlen(env);
        if (n < sizeof buf) {
            memcpy(buf, env, n + 1);
            return buf;
        }
    }
    for (i = 0; cands[i] != 0; i++) {
        if (link_abi_path_readable(cands[i]) != 0)
            return cands[i];
    }
    buf[0] = 0;
    return buf;
}
#endif

/*
 * PLATFORM: SHARED — active -O for link strip/gc decisions.
 * Default "2" matches product compile default. -O 0 keeps symtab so TOOL-005
 * Darwin nsyms / Linux "not stripped" smokes are honest (not dead_strip soft SKIP).
 */
static char g_xlang_link_opt_level[8] = {'2', '\0'};

void xlang_link_set_opt_level(const char *opt_level) {
    size_t i;
    if (!opt_level || !opt_level[0]) {
        g_xlang_link_opt_level[0] = '2';
        g_xlang_link_opt_level[1] = '\0';
        return;
    }
    for (i = 0; i < sizeof(g_xlang_link_opt_level) - 1 && opt_level[i]; i++)
        g_xlang_link_opt_level[i] = opt_level[i];
    g_xlang_link_opt_level[i] = '\0';
}

const char *xlang_link_get_opt_level(void) {
    return g_xlang_link_opt_level;
}

void xlang_link_capture_opt_level_from_argv(int argc, char **argv) {
    const char *ol = "2";
    int i;
    if (argv) {
        for (i = 1; i + 1 < argc; i++) {
            if (argv[i] && strcmp(argv[i], "-O") == 0 && argv[i + 1] && argv[i + 1][0]) {
                ol = argv[i + 1];
                break;
            }
        }
    }
    xlang_link_set_opt_level(ol);
}

/**
 * ASM -o exe：fork 子进程执行 ld 或 lld-link；调用方须先 xlang_asm_ld_prepare_for_exe_link。
 * Darwin product -o uses bare ld + syslibroot (no clang/cc driver).
 * Linux hosted product -o uses bare ld + glibc Scrt1/crti/crtn (no gcc/cc driver).
 * 参数：driver_freestanding 同 xlang_link_freestanding_enabled；link_argv0 用于 std/.o 路径解析。
 * 返回值：0 成功，-1 失败。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int xlang_asm_invoke_ld_platform(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots,
    int driver_freestanding) {
    char link_argv_syn[PATH_MAX];
    const char *link_eff;

    (void)target;
#if !defined(__linux__)
    (void)driver_freestanding;
#endif
    if (!o_path || !exe_path)
        return -1;
    link_eff = xlang_asm_ld_effective_link_argv0(link_argv0, link_argv_syn, sizeof link_argv_syn);
    if (!link_eff)
        return -1;

    {
        static char xlang_asm_ld_lib_root_bufs[24][512];
        static const char *xlang_asm_ld_lib_roots[24];
        const char **lib_roots_eff = lib_roots;
        int n_lib_roots_eff = n_lib_roots;
        int li;

        if (!lib_roots_eff || (uintptr_t)lib_roots_eff < 4096u || n_lib_roots_eff <= 0 || n_lib_roots_eff > 24) {
            xlang_asm_ld_lib_root_default(xlang_asm_ld_lib_root_bufs[0]);
            xlang_asm_ld_lib_roots[0] = xlang_asm_ld_lib_root_bufs[0];
            lib_roots_eff = xlang_asm_ld_lib_roots;
            n_lib_roots_eff = 1;
        } else {
            for (li = 0; li < n_lib_roots_eff; li++) {
                const char *r = lib_roots_eff[li];
                if (!r || (uintptr_t)r < 4096u) {
                    xlang_asm_ld_lib_root_default(xlang_asm_ld_lib_root_bufs[li]);
                    xlang_asm_ld_lib_roots[li] = xlang_asm_ld_lib_root_bufs[li];
                } else if (!r[0]) {
                    xlang_asm_ld_lib_root_default(xlang_asm_ld_lib_root_bufs[li]);
                    xlang_asm_ld_lib_roots[li] = xlang_asm_ld_lib_root_bufs[li];
                } else {
                    if (strlen(r) >= sizeof(xlang_asm_ld_lib_root_bufs[li]))
                        r = ".";
                    memcpy(xlang_asm_ld_lib_root_bufs[li], r, strlen(r) + 1);
                    xlang_asm_ld_lib_roots[li] = xlang_asm_ld_lib_root_bufs[li];
                }
            }
            lib_roots_eff = xlang_asm_ld_lib_roots;
        }

        /* slots[42][4096] 勿放栈上：driver 深栈 + ld_bank 易溢出并踩坏 rel/lib_roots。 */
        static ShuAsmLdPathBank xlang_asm_ld_exe_bank;
        ShuAsmLdPathBank *ld_bank = &xlang_asm_ld_exe_bank;
        ShuAsmLdStdLinkFlags ldflags;
        const char *argv[XLANG_LD_ARGV_CAP];
        char out_opt[512];
        int la = 0;
        int need_pt;
        const char *compress_o;
        pid_t pid;

        memset(ld_bank, 0, sizeof *ld_bank);
        compress_o = NULL; /* F-06 v1 / F-04 v7：无 compress.o，tail libs 由 user_o 扫描 */
#if defined(__APPLE__)
        if (use_macho_o) {
            /*
             * PLATFORM: MACOS — product default -o must not spawn clang/cc as
             * the linker driver (PC zero-spawn leftover). G.7 complete the
             * existing ld fallback: -syslibroot + -dynamic + -arch so bare
             * ld finds libSystem. Sit-red: PATH trap clang → FAKE_CC_SPAWN;
             * ld without syslibroot failed. Hello/rv/opt ld+syslibroot run
             * 0/42/102. Same object list as the old clang driver (std +
             * on_demand + extra). Do not fall back to clang.
             */
            const char *sdk;
            const char *arch;
            sdk = labi_darwin_sdk_path();
            if (!sdk || !sdk[0]) {
                link_diag_tool_status("ld", -1);
                return -1;
            }
            arch = "x86_64";
            if (xlang_host_is_apple_aarch64() != 0)
                arch = "arm64";
            argv[la++] = labi_ld_driver_ld();
            argv[la++] = "-syslibroot";
            argv[la++] = sdk;
            argv[la++] = "-dynamic";
            argv[la++] = "-arch";
            argv[la++] = arch;
            /* PLATFORM: MACOS — clang-as-driver implied -dead_strip; keep it
             * on bare ld so product -o size does not jump (rv 55KiB→16KiB).
             * Skip at -O 0 so debug builds keep symtab (TOOL-005 nsyms>300);
             * ≡ invoke_cc -DNDEBUG/harden/maybe_strip already gated on is0. */
            if (strcmp(xlang_link_get_opt_level(), "0") != 0)
                argv[la++] = "-dead_strip";
            argv[la++] = labi_ld_flag_e();
            argv[la++] = labi_ld_mach_entry_main();
            argv[la++] = labi_ld_flag_o();
            argv[la++] = exe_path;
            argv[la++] = o_path;
            xlang_asm_ld_append_std_objs_for_user(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_on_demand_user_objs(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_mach_tail_libs(compress_o, o_path, &ldflags, (const char **)argv, &la, XLANG_LD_ARGV_CAP, 1);
            /* G.7: CLI user .o after std/on_demand (same globals as invoke_cc). */
            xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
            argv[la] = NULL;
            {
                int rc = xlang_spawn_sync(labi_ld_driver_ld(), (const char *const *)argv);
                if (rc != 0) {
                    link_diag_tool_status("ld", rc);
                    return -1;
                }
            }
            return 0;
        }
#endif
        if (use_coff_o) {
#if defined(_WIN32) && (defined(__MINGW32__) || defined(__MINGW64__))
            /* PLATFORM: WINDOWS | MINGW — gcc as link driver pulls UCRT/msvcrt and
             * resolves on-demand std/panic objs. Bare lld-link without /libpath to
             * mingw ucrt left printf/__acrt_iob_func UNDEF after ws2_32 was fixed. */
            la = 0;
            ld_bank->n = 0;
            memset(ld_bank->slots, 0, sizeof ld_bank->slots);
            argv[la++] = "gcc";
            argv[la++] = "-o";
            argv[la++] = exe_path;
            argv[la++] = o_path;
            xlang_asm_ld_append_std_objs_for_user(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_on_demand_user_objs(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
            argv[la] = NULL;
            {
                int rc = xlang_spawn_sync("gcc", (const char *const *)argv);
                if (rc != 0) {
                    link_diag_tool_status("ld", rc);
                    return -1;
                }
            }
            return 0;
#else
            int nn = snprintf(out_opt, sizeof(out_opt), "/out:%s", exe_path);
            if (nn < 0 || nn >= (int)sizeof(out_opt))
                return -1;
            la = 0;
            ld_bank->n = 0;
            memset(ld_bank->slots, 0, sizeof ld_bank->slots);
            argv[la++] = "lld-link";
            /* PLATFORM: WINDOWS | PE — lld-link requires an explicit subsystem for
             * console want-exe (else "subsystem must be defined"). */
            argv[la++] = "/subsystem:console";
            argv[la++] = "/entry:main";
            argv[la++] = out_opt;
            argv[la++] = o_path;
            xlang_asm_ld_append_std_objs_for_user(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_on_demand_user_objs(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
            argv[la++] = "ws2_32.lib";
            argv[la] = NULL;
            {
                int rc = xlang_spawn_sync("lld-link", (const char *const *)argv);
                if (rc != 0) {
                    link_diag_tool_status("ld", rc);
                    return -1;
                }
            }
            return 0;
#endif
        }
        la = 0;
        ld_bank->n = 0;
        memset(ld_bank->slots, 0, sizeof ld_bank->slots);
#if defined(__linux__)
        /* F-no-libc NL-05 BEGIN: freestanding 用户链（ld -nostdlib -static，禁止 -lc） */
        if (xlang_link_freestanding_enabled(driver_freestanding)) {
            const char *crt0_p;
            const char *panic_p;
            const char *io_p;
            const char *stubs_p;
            int need_io = 0;
            int need_panic = 0;
            int need_nostdlib_face = 0;
            need_io = xlang_freestanding_user_o_needs_io(o_path);
            need_panic = xlang_freestanding_user_o_needs_panic(o_path);
            /*
             * PLATFORM: LINUX freestanding product residual —
             * co-emit std.heap.libc → U malloc/free/…; zero-libc face is
             * bootstrap_nostdlib_stubs (mmap bump), same as compiler nostdlib bag.
             * Stubs need xlang_sys_mmap from freestanding_io → force need_io.
             * G.7: complete freestanding ld on_demand (no second malloc path).
             */
            need_nostdlib_face = link_abi_user_o_needs_freestanding_nostdlib_face(o_path);
            if (need_nostdlib_face)
                need_io = 1;
            argv[la++] = "ld";
            argv[la++] = "-nostdlib";
            argv[la++] = "-static";
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = "--gc-sections";
            /*
             * G-03 freestanding co-emit 去重未做：dep 模块（如 linux.x）经多条 import 路径
             * （std.sys → linux, page_mmap → linux, 直接 import linux）被 co-emit 多次，
             * 同一 function 在 user.o 内重复定义（如 syscall_nr_write_amd64/arm64）。
             * 【Why 根源】co-emit 不做 reach 过滤 + 所有函数在同一 .text section，
             * --gc-sections 仅移除未引用 section，无法消除单 .o 内的同名重复定义。
             * --allow-multiple-definition 让 ld 选第一个定义，与项目既有 weak+multi-def
             * 模式（line 3565 PE/COFF、line 4919 core.mem）对齐。重复 function 体相同，安全。
             * 【Invariant】仅 freestanding ld 路径；ELF weak 原生支持但 co-emit 产生强符号重复。
             * 【Asm/Perf】链接期选第一个定义，无运行时开销。
             */
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = "--allow-multiple-definition";
            argv[la++] = "-o";
            argv[la++] = exe_path;
            crt0_p = asm_link_obj_skip_missing(xlang_crt0_user_o_path(link_eff));
            if (!crt0_p) {
                link_diag_freestanding_missing("crt0_user.o", NULL);
                return -1;
            }
            panic_p = NULL;
            if (need_panic)
                panic_p = asm_link_obj_skip_missing(xlang_runtime_panic_o_path(link_eff));
            if (need_panic && !panic_p) {
                link_diag_freestanding_missing("runtime_panic.o", "xlang_panic_");
                return -1;
            }
            io_p = NULL;
            /* PLATFORM: LINUX freestanding (wave592) — G.7: ensure before skip_missing,
             * same pattern as bootstrap_nostdlib_stubs below. prepare may also ensure
             * when needs_io | nostdlib_face; ld still ensures when force need_io so a
             * cold tree without compiler/freestanding_io.o self-heals (cc .s → .o). */
            if (need_io) {
                if (xlang_ensure_freestanding_io_o(link_eff, driver_freestanding) != 0)
                    return -1;
                io_p = asm_link_obj_skip_missing(xlang_freestanding_io_o_path(link_eff));
            }
            if (need_io && !io_p) {
                link_diag_freestanding_missing("freestanding_io.o",
                    need_nostdlib_face ? "memcpy/xlang_sys_mmap" : "xlang_sys_write");
                return -1;
            }
            stubs_p = NULL;
            if (need_nostdlib_face) {
                if (xlang_ensure_bootstrap_nostdlib_stubs_o(link_eff) != 0)
                    return -1;
                stubs_p = asm_link_obj_skip_missing(xlang_bootstrap_nostdlib_stubs_o_path(link_eff));
                if (!stubs_p) {
                    link_diag_freestanding_missing("bootstrap_nostdlib_stubs.o", "malloc");
                    return -1;
                }
            }
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = crt0_p;
            if (need_panic && la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = panic_p;
            if (need_io && la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = io_p;
            if (need_nostdlib_face && stubs_p && la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = stubs_p;
            /*
             * F-no-libc NL-03/04/06：freestanding 按需链入 import 的 std/*.o（page_mmap/sys/linux/core_mem）。
             * 【Why 根源】freestanding -nostdlib 链接默认只链 crt0+panic+io+user.o，不扫描 std 依赖；
             * user.o import std.heap.page_mmap / std.sys / std.sys.linux 时，其 .o 须显式按需链入。
             * 【Invariant】on_demand 在 o_path 之前调用；--gc-sections 从 entry(crt0→main) 做可达性
             * 分析，所有 .o 须在 ld argv 中，未引用的 hosted 函数被 GC 移除。
             */
            xlang_asm_ld_append_on_demand_user_objs(link_eff, o_path, lib_roots_eff, n_lib_roots_eff,
                ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = o_path;
            /* G.7: CLI user .o (atomic_glue/time_os/…) after primary user.o. */
            xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
            argv[la] = NULL;
            {
                /*
                 * nostdlib 链 xlang_asm 的 environ 可能无 PATH：ld 子进程须显式设置 PATH，
                 * 否则 execvp("ld") 找不到 /usr/bin/ld → ENOENT → BLD001。
                 * 【Why】strict link xlang_asm 用 -nostdlib -static 链接，environ 不一定
                 * 继承完整 PATH；gcc 路径用 xlang_linux_host_gcc_path() 绕过，ld 亦须设 PATH。
                 */
                xlang_linux_ld_child_path();
                int rc = xlang_spawn_sync("ld", (const char *const *)argv);
                if (rc != 0) {
                    link_diag_tool_status("ld", rc);
                    return -1;
                }
            }
            return 0;
        }
        /* F-no-libc NL-05 END */
        /*
         * 自包含 .o（nm -u 为空）：hosted ld 仅链 user.o + libc crt。
         * nostdlib xlang_asm 无 popen：保守走全量 hosted ld 链（return-value 等）。
         */
        if (!xlang_asm_user_o_has_undef_syms(o_path)) {
#if defined(__linux__)
            /*
             * nostdlib xlang_asm：popen 恒 NULL 时走自包含最小链；勿再 push string/base64 等
             * （realpath 去重 + 深栈易 SIGSEGV，见 C6 return-value -o）。
             */
            if (bootstrap_nostdlib_pthread_is_stub())
                return xlang_asm_nostdlib_minimal_selfcontained_exe_link(o_path, exe_path, link_eff,
                    lib_roots_eff, n_lib_roots_eff);
#endif
            if (labi_linux_hosted_ld_begin(argv, &la, XLANG_LD_ARGV_CAP, exe_path) != 0) {
                link_diag_tool_status("ld", -1);
                return -1;
            }
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = o_path;
            link_abi_asm_ld_push_minimal_runtime_objs(link_eff, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP);
            /*
             * user.o 无 UNDEF：co-emit 已自洽。勿再硬链 string.o/base64.o/encoding.o
             * （string 入口-only 库 .o 对 heap 有 U，硬链会缺 std_heap_libc_*；且与 co-emit 体重复时 duplicate）。
             * 有 UNDEF 时走下方 full append_std / on_demand。
             */
            if (la < XLANG_LD_ARGV_CAP - 1)
                argv[la++] = labi_ld_flag_lc();
            xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
            return labi_linux_hosted_ld_finish_and_spawn(argv, &la, XLANG_LD_ARGV_CAP, "minimal ld argv");
        }
#endif
#if defined(__linux__)
        /*
         * PLATFORM: LINUX hosted product -o — G.7 complete existing ld (no gcc
         * driver). Historical SIGSEGV was `ld -e main` without glibc crt
         * (_start → __libc_start_main). Prefix Scrt1+crti; suffix crtn; PIE
         * + -z noexecstack/relro/now + --gc-sections. Same object list as the
         * old gcc driver (std + on_demand + extra). Do not spawn gcc/cc.
         */
        if (labi_linux_hosted_ld_begin(argv, &la, XLANG_LD_ARGV_CAP, exe_path) != 0) {
            link_diag_tool_status("ld", -1);
            return -1;
        }
#else
        argv[la++] = "ld";
        argv[la++] = "-e";
        argv[la++] = "_main";
        argv[la++] = "-o";
        argv[la++] = exe_path;
#endif
        argv[la++] = o_path;
        xlang_asm_ld_append_std_objs_for_user(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
        xlang_asm_ld_append_on_demand_user_objs(link_eff, o_path, lib_roots_eff, n_lib_roots_eff, ld_bank, argv, &la, XLANG_LD_ARGV_CAP, &ldflags);
        if (link_abi_user_o_needs_libc_heap(o_path))
            ldflags.have_libc_heap = 1;
        need_pt = ldflags.have_thread || ldflags.have_sync || ldflags.have_channel;
        xlang_asm_ld_append_unix_gcc_tail_libs(compress_o, o_path, &ldflags, need_pt, (const char **)argv, &la, XLANG_LD_ARGV_CAP);
        /* G.7: CLI user .o after std/on_demand/tail libs (mirrors invoke_cc order). */
        xlang_asm_ld_append_user_extra_o_files(argv, &la, XLANG_LD_ARGV_CAP);
#if defined(__linux__)
        return labi_linux_hosted_ld_finish_and_spawn(argv, &la, XLANG_LD_ARGV_CAP, "ld argv");
#endif
        argv[la] = NULL;
        /* wave225 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
        if (link_abi_getenv("XLANG_DEBUG_LD"))
            link_diag_ld_debug_argv("ld argv", argv);
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
        {
            intptr_t rc = _spawnvp(_P_WAIT, argv[0], (const char *const *)argv);
            if (rc == -1) {
                perror("spawnvp (ld)");
                return -1;
            }
            if (rc != 0) {
                link_diag_tool_status("ld", (int)rc);
                return -1;
            }
        }
#else
        pid = (pid_t)xlang_proc_fork();
        if (pid < 0) {
            perror("fork (ld)");
            return -1;
        }
        if (pid == 0) {
#if defined(__linux__)
            xlang_linux_ld_child_path();
#endif
            (void)xlang_proc_execvp(argv[0], (char *const *)argv);
            xlang_proc_exit(127);
        }
        {
            int status;
            if (xlang_waitpid_retry(pid, &status) != 0)
                return -1;
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                link_diag_tool_status("ld", status);
                return -1;
            }
        }
#endif
    }
    return 0;
}




/**
 * 判断 -o 路径是否写出对象文件（.o / .obj 则写 ELF/Mach-O/COFF 而非 .s）。
 * 参数：path 为 -o 参数；NULL 则返回 0。
 * 返回值：非 0 表示对象文件后缀。
 */
/* G-02f-64：真逻辑来自 .x（逐字节后缀；无 _impl）。 */
/* G-02f-267 L0 path pure */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int xlang_output_is_elf_o(const char *path) {
    size_t n;
    if (path == NULL) {
        return 0;
    }
    n = 0;
    while (path[n] != 0) {
        n = n + 1;
    }
    if (n >= 2) {
        if (path[n - 2] == '.') {
            if (path[n - 1] == 'o') {
                return 1;
            }
            if (path[n - 1] == 'O') {
                return 1;
            }
        }
    }
    if (n >= 4) {
        if (path[n - 4] == '.') {
            if (path[n - 3] == 'o') {
                if (path[n - 2] == 'b') {
                    if (path[n - 1] == 'j') {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
#else
int xlang_output_is_elf_o(const char *path);
#endif


/**
 * 判断 -o 路径是否表示可执行文件名（非 .o/.obj/.s 后缀）。
 * 参数：path 为 -o 参数；空串或 NULL 则返回 0。
 * 返回值：非 0 表示 -backend asm 应自动调 ld 出 exe。
 * G-02f-64：真逻辑来自 .x。
 */
/* G-02f-430：.x 真迁到 labi_path_pure.x */
#ifndef XLANG_LABI_PATH_PURE_FROM_X
int xlang_output_want_exe(const char *path) {
    size_t n;
    if (path == NULL) {
        return 0;
    }
    if (path[0] == 0) {
        return 0;
    }
    n = 0;
    while (path[n] != 0) {
        n = n + 1;
    }
    if (n >= 2) {
        if (path[n - 2] == '.') {
            if (path[n - 1] == 'o') {
                return 0;
            }
            if (path[n - 1] == 'O') {
                return 0;
            }
            if (path[n - 1] == 's') {
                return 0;
            }
        }
    }
    if (n >= 4) {
        if (path[n - 4] == '.') {
            if (path[n - 3] == 'o') {
                if (path[n - 2] == 'b') {
                    if (path[n - 1] == 'j') {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
#else
int xlang_output_want_exe(const char *path);
#endif

/**
 * ASM -o exe 薄包装：ensure .o + xlang_asm_ld_prepare_for_exe_link + xlang_asm_invoke_ld_platform。
 * G-02f-66：主体 _impl（PATH_MAX 合成缓冲）；.x 门闩 null 检查后转发。
 */
int xlang_invoke_ld_for_exe_impl(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots) {
    char link_argv_syn[PATH_MAX];
    const char *link_eff;
    int freestanding;

    link_eff = xlang_asm_ld_effective_link_argv0(link_argv0, link_argv_syn, sizeof link_argv_syn);
    if (!link_eff)
        return -1;
    freestanding = driver_freestanding_get();
    if (xlang_asm_ld_prepare_for_exe_link(link_eff, o_path, freestanding, use_macho_o, use_coff_o) != 0)
        return -1;
    return xlang_asm_invoke_ld_platform(o_path, exe_path, target, use_macho_o, use_coff_o, link_argv0, lib_roots, n_lib_roots,
        freestanding);
}

/* G-02f-277 L9 gates */
#ifndef XLANG_LABI_GATES_FROM_X
int xlang_invoke_ld_for_exe(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots) {
  if (o_path == NULL) {
    return -1;
  }
  if (exe_path == NULL) {
    return -1;
  }
  {
    return xlang_invoke_ld_for_exe_impl(o_path, exe_path, target, use_macho_o, use_coff_o, link_argv0, lib_roots, n_lib_roots);
  }
  return -1;
}
#else
int xlang_invoke_ld_for_exe(const char *o_path, const char *exe_path, const char *target,
    int use_macho_o, int use_coff_o, const char *link_argv0, const char **lib_roots, int n_lib_roots);
int labi_gates_count(void);
#endif

/* -------------------------------------------------------------------------- */
/* G-02e：原 runtime_proc_abi.c 并入本 TU（产品链减 1 个手写 C 文件）。 */
/* -------------------------------------------------------------------------- */

/**
 * Cap residual (wave216 + 9.1.4): waitpid with EINTR retry + errno strerror report.
 * Pure orch (labi_diag_pure L1) owns public thin; _impl is always mega.
 * Linux: wait4 via xlang_process_cap (no libc waitpid). Else libc waitpid.
 * PLATFORM: LINUX Cap residual; POSIX waitpid; Windows product uses _spawnvp paths that skip this.
 */
int xlang_waitpid_retry_impl(pid_t pid, int *status_out) {
    int st = 0;
#if !defined(_WIN32) && !defined(_WIN64)
    for (;;) {
        long w = xlang_proc_waitpid((long)pid, &st, 0);
        if (w == (long)pid) {
            if (status_out)
                *status_out = st;
            return 0;
        }
        if (w < 0 && w == -(long)EINTR)
            continue;
        {
            /* Map negative errno for diag; strerror still host residual for message text. */
            int saved_errno = (w < 0) ? (int)(-w) : EINTR;
            const char *err = strerror(saved_errno);
            diag_reportf_with_code(NULL, 0, 0, "process error", XLANG_DIAG_CODE_PROCESS_PRC001, NULL,
                                   "waitpid failed: %s",
                                   err ? err : "unknown error");
        }
        return -1;
    }
#else
    for (;;) {
        pid_t w = waitpid(pid, &st, 0);
        if (w == pid) {
            if (status_out)
                *status_out = st;
            return 0;
        }
        if (w == -1 && errno == EINTR)
            continue;
        {
            int saved_errno = errno;
            const char *err = strerror(saved_errno);
            diag_reportf_with_code(NULL, 0, 0, "process error", XLANG_DIAG_CODE_PROCESS_PRC001, NULL,
                                   "waitpid failed: %s",
                                   err ? err : "unknown error");
        }
        return -1;
    }
#endif
}

/* wave216: xlang_waitpid_retry pure orch lives in labi_diag_pure.x (hybrid L1);
 * mega cold twin under #ifndef XLANG_LABI_DIAG_PURE_FROM_X.
 * Pure: thin public; Cap residual xlang_waitpid_retry_impl (waitpid+EINTR+strerror).
 * Why: hybrid still had waitpid body always mega C (wait+strerror+diag).
 * PLATFORM: SHARED orch / POSIX wait residual. */
#ifndef XLANG_LABI_DIAG_PURE_FROM_X
int xlang_waitpid_retry(pid_t pid, int *status_out) {
    return xlang_waitpid_retry_impl(pid, status_out);
}
#else
int xlang_waitpid_retry(pid_t pid, int *status_out);
#endif




/**
 * 仅当 path 指向已存在且非空的常规文件时返回 path，供 clang/ld argv 追加。
 */




/* -------------------------------------------------------------------------- */
/* G-02e：原 runtime_abi.c 并入本 TU（argv/target 薄原语 + nostdlib weak 桩）。 */
/* -------------------------------------------------------------------------- */


/** G-02f-44：argv 下标与 C 串拷贝（.x driver_get_argv_i 用）。 */
const char *driver_argv_at(char **argv, int i) {
    if (!argv || i < 0 || !argv[i])
        return NULL;
    return argv[i];
}
/* G-02f-118：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int driver_copy_cstr_n(const char *src, char *buf, int max) {
    size_t n;
    size_t j;
    if (!src || !buf || max <= 0)
        return -1;
    n = (size_t)max - 1;
    j = 0;
    while (src[j] && j < n) {
        buf[j] = src[j];
        j++;
    }
    buf[j] = '\0';
    return (int)j;
}




int driver_get_argv_i(int argc, char **argv, int i, char *buf, int max) {
  if ((argv ==NULL)) {
    return (0 - 1);
  }
  if ((buf ==NULL)) {
    return (0 - 1);
  }
  if ((max <=0)) {
    return (0 - 1);
  }
  if ((i < 0)) {
    return (0 - 1);
  }
  if ((i >=argc)) {
    return (0 - 1);
  }
  (void)(({   {
    char *s = driver_argv_at(argv, i);
    if ((s ==NULL)) {
      return (0 - 1);
    }
    int r = driver_copy_cstr_n(s, buf, max);
    return r;
  }
 }));
  return (0 - 1);
}

uint8_t *driver_argv_drop_subcommand(int argc, uint8_t *argv_opaque) {
    static char *adj[512];
    char **argv;
    int i;

    if (argc < 2 || !argv_opaque)
        return argv_opaque;
    argv = (char **)argv_opaque;
    if (argc > 512)
        return argv_opaque;
    adj[0] = argv[0];
    for (i = 2; i < argc; i++)
        adj[i - 1] = argv[i];
    return (uint8_t *)adj;
}

/* Build the argv used by `xlang run` / bare `xlang file.x`: if the user already
 * passed -o, return argv unchanged (and *out_argc = argc) so the explicit
 * product path is compiled and exec'd. Otherwise append `-o <temp>` where
 * <temp> is a unique /tmp path, so the C/asm backend links a real executable
 * (no a.out in cwd, no generated C to stdout) and driver_exec_compiled execs
 * that temp. The temp is a unique name obtained via mkstemp+unlink; the
 * compiler (cc -o / ld -o) creates the actual executable file.
 * PLATFORM: SHARED — /tmp on POSIX, current dir fallback on Windows. */
#ifndef XLANG_RUN_TMP_PREFIX
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#define XLANG_RUN_TMP_PREFIX "xlang_run_"
#else
#define XLANG_RUN_TMP_PREFIX "/tmp/xlang_run_"
#endif
#endif
uint8_t *driver_argv_ensure_run_o(int argc, uint8_t *argv_opaque, int *out_argc) {
    static char *adj[512];
    static char temp_path[96];
    char **argv;
    int has_o = 0;
    int i;
    if (out_argc)
        *out_argc = argc;
    if (!argv_opaque || argc < 1)
        return argv_opaque;
    argv = (char **)argv_opaque;
    /* Respect an explicit -o: scan like driver_exec_scan_out_path. */
    for (i = 1; i < argc - 1; i++) {
        if (argv[i] && strcmp(argv[i], "-o") == 0) {
            has_o = 1;
            break;
        }
    }
    if (has_o)
        return argv_opaque;
    if (argc + 2 > 512)
        return argv_opaque;
    snprintf(temp_path, sizeof temp_path, "%sXXXXXX", XLANG_RUN_TMP_PREFIX);
    {
#if !defined(_WIN32) && !defined(_WIN64) && !defined(__CYGWIN__)
        /* POSIX: mkstemp yields an atomically unique name; free it so cc -o
         * creates the executable itself (mkstemp leaves an empty regular file). */
        int fd = mkstemp(temp_path);
        if (fd >= 0) {
            close(fd);
            unlink(temp_path);
        } else {
            snprintf(temp_path, sizeof temp_path, "%s%ld", XLANG_RUN_TMP_PREFIX, (long)getpid());
        }
#else
        /* Windows: no mkstemp here; use a per-process counter for uniqueness. */
        static long run_counter = 0;
        run_counter = run_counter + 1;
        snprintf(temp_path, sizeof temp_path, "%s%ld", XLANG_RUN_TMP_PREFIX, run_counter);
#endif
    }
    for (i = 0; i < argc; i++)
        adj[i] = argv[i];
    adj[argc] = (char *)"-o";
    adj[argc + 1] = temp_path;
    adj[argc + 2] = (char *)0;
    if (out_argc)
        *out_argc = argc + 2;
    return (uint8_t *)adj;
}

int32_t driver_resolve_target_arch(int parsed_target, int saw_target_flag) {
  if ((saw_target_flag !=0)) {
    return parsed_target;
  }
  (void)(({   {
    if ((xlang_host_is_apple_aarch64() !=0)) {
      return 1;
    }
    return parsed_target;
  }
 }));
  return parsed_target;
}

extern int main_entry(int argc, char **argv);

int xlang_forward_main_to_main_entry(int argc, char **argv) {
  (void)(({   {
    int r = main_entry(argc, argv);
    return r;
  }
 }));
  return 0;
}

XLANG_WEAK void bootstrap_init_static_tls(void) {
  (void)(0);
}

XLANG_WEAK void bootstrap_init_environ(int argc, char **argv) {
  (void)(0);
}

/* PLATFORM: SHARED — pthread large-stack availability gate.
 *   POSIX (Linux/macOS): winpthreads absent; real pthreads support 256MiB
 *     posix_memalign'd custom stack via pthread_attr_setstack. Return 0
 *     so driver_run_thread_on_large_stack takes the pthread path for
 *     deep recursion beyond main thread's 8MiB RLIMIT_STACK.
 *   WINDOWS (MSYS/MinGW): winpthreads exist but pthread_attr_setstack
 *     with 256MiB posix_memalign'd stack crashes during pthread_join
 *     cleanup (exit=127 after thread fn returns). Return 1 to force
 *     driver_run_fn_on_current_large_stack path (driver_bump_stack_limit
 *     raises soft limit; pipeline runs on main thread). See AGENTS.md
 *     "平台边界必须标注" + project memory "Windows/MinGW weak" constraints.
 *   Authority: this XLANG_WEAK def is the sole linked definition on all
 *     platforms; the strong def in bootstrap_nostdlib_stubs.from_x.c
 *     (returns 1) is an orphan target never linked. G.4 single authority. */
XLANG_WEAK int bootstrap_nostdlib_pthread_is_stub(void) {
#if defined(_WIN32) || defined(_WIN64)
  return 1;
#else
  return 0;
#endif
}

