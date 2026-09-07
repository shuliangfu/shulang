/* G-02f-343/344/345 / R2 thin full：PREFER hybrid thin 由 src/runtime_driver_abi_thin.x；
 * rest XLANG_L2_RDABI_THIN_FROM_X（无 pure-dup _impl；slice_marker + Cap residual 体）。
 * pure 深迁：scan/has/argv_collect/target_os/fail/smoke/peek/entry_len_i32/large_stack orch
 *   + getenv 门闩（force_c / asm skip / emit_heavy / module_only / metric / no_large_stack /
 *   sanitize_address env）
 *   + 数值 env（parse_u32 + stack_limit_want_bytes + phase_timing_enabled）在 thin.x；
 *   + wave1 Cap residual pure：9× flag-slot BSS 权威在 thin.x；FROM_X 无 pure-dup flag_slot _impl；
 *   + wave2 Cap residual pure：path/len BSS 权威在 thin.x（dep path · entry_source_len ·
 *     path_last_preprocess_len）；FROM_X 无 pure-dup path/len store/load _impl；
 *   + wave3 Cap residual pure：format print 权威在 thin.x（check_ok / fail rc·path /
 *     smoke parse·typeck：append_* + diag_report*，无 va_list reportf）；FROM_X 无 pure-dup
 *     print/fail format _impl；
 *   + wave4 Cap residual pure：defines_set_at（G.7 xlang_ptr_slot_set）+ os_define_lit
 *     字面量表在 thin.x；FROM_X 无 pure-dup set_at/os_lit _impl；
 *   + wave5 Cap residual pure：phase timing BSS + begin/end 在 thin.x；FROM_X 无 pure-dup
 *     begin/end _impl；
 *   + wave6 Cap residual pure：phase_timing_flush 在 thin.x（whole-ms append + diag_report）；
 *     FROM_X 无 pure-dup flush _impl；
 *   + wave7 Cap residual pure：compile_phase_now_sec 在 thin.x（→ xlang_driver_wall_clock_sec）；
 *     FROM_X 无 pure-dup now_sec _impl；gettimeofday/time 永久 OS 面 xlang_driver_wall_clock_sec；
 *   + wave8 Cap residual pure：call_fn 编排 pure；间接调用永久 OS 面 xlang_driver_call_fn_void_arg；
 *     FROM_X rest 无 pure-dup call_fn _impl；
 *   + wave9 Cap residual pure：bump_stack_limit orch pure；setrlimit 永久 OS 面 xlang_driver_bump_stack_limit；
 *     FROM_X rest 无 pure-dup setrlimit/to_impl _impl；
 *   + wave10 Cap residual pure：uname host defines → 永久 OS 面 xlang_driver_argv_append_uname；
 *     FROM_X rest 无 pure-dup append_uname _impl；struct utsname 不进 .x；
 *   + wave11 Cap residual pure：path-read IO → 永久 OS 面 xlang_driver_path_read_preprocess_malloc；
 *     FROM_X rest 无 pure-dup path_read _impl；file view + preprocess 不进 .x；
 *   + wave12 Cap residual pure：pthread 创建 → 永久 OS 面 xlang_driver_run_thread_on_large_stack_pthread；
 *     FROM_X rest 无 pure-dup pthread _impl；pthread_attr/posix_memalign 不进 .x；
 *   + wave13 Cap residual pure：entry_source_len load debug note 在 thin.x
 *     （XLANG_DEBUG_PIPE truthy → append_* + diag_report；no va_list reportf）；
 *     FROM_X rest 无 pure-dup load_and_maybe_debug _impl；cold keeps integer-note twin；
 *   + wave14 Cap residual pure：rt_asm_stub GAS 行表 + out_append_cstr 在 thin.x
 *     （data[9MiB]+i32 len 宿主布局 LE；无 memcpy/strlen）；FROM_X 无 pure-dup gas/append；
 *   + wave15 Cap residual pure：rt_entry 缓冲槽 + path_max/entry_dir 在 thin.x
 *     （u8[N] BSS；fmt_argv 见 wave21）；FROM_X 无 pure-dup entry/path buf slots；
 *   + wave16 Cap residual pure：driver_x_emit work BSS + get/set/reset/cleanup 在 thin.x
 *     （p raw u8[208]+xlang_ptr_slot_* · i32[17] · usize[5]；free+dep_ctx destroy）；FROM_X 无 pure-dup work；
 *   + wave17 Cap residual pure：driver_asm_work BSS + get/set/reset/cleanup 在 thin.x
 *     （p raw u8[200] 25×ptr · i32[16] · usize[4]；free+dep_ctx+fclose；tmp_path[0] clear）；FROM_X 无 pure-dup asm work；
 *   + wave18 Cap residual pure：driver_parsed_work BSS + get/set/reset/cleanup 在 thin.x
 *     （p raw u8[192] 24×ptr · i32[14] · usize[4]；free+dep_ctx+fclose cf；unlink tmp_c；tmp slots clear）；FROM_X 无 pure-dup parsed work；
 *   + wave19 Cap residual pure：driver_pipeline_dep_ctx i32 字段 get/set 在 thin.x
 *     （LP64 固定 offsetof + wave14 LE load/store；无 C 结构体）；
 *     FROM_X 无 pure-dup dep_ctx field _impl；
 *   + wave20 Cap residual pure：driver_preamble_{io_net,fs_path}_line_at/count 在 thin.x
 *     （G.7 xlang_ptr_slot_get + always-seed *_lines_raw；巨型表仍 rt_preamble）；
 *     FROM_X 无 pure-dup line_at/count；
 *   + wave21 Cap residual pure：driver_entry_fmt_argv_slot 在 thin.x
 *     （u8 lit BSS "xlang"/"fmt" + 2× LP64 ptr slots via G.7 xlang_ptr_slot_set；无 *u8[2] lit）；
 *     FROM_X 无 pure-dup fmt_argv；
 *   + wave22 Cap residual pure：driver_preamble_fputs 在 thin.x
 *     （null 守卫 + g05 prologue xlang_driver_fputs_opaque FILE* cast；.x 无 FILE*）；
 *     FROM_X 无 pure-dup fputs；
 *   + wave23 Cap residual pure：calloc 族 + driver_asm_pctx_apply_host_defaults 在 thin.x
 *     （libc calloc/malloc/memset + pipeline_sizeof_*；host #ifdef → 永久 OS residual helper）；
 *     FROM_X 无 pure-dup calloc/host_defaults；
 *   + wave24 Cap residual pure：outbuf free/len/data + ptr/size table free/get/set
 *     + diag_snapshot_free 在 thin.x（配对 wave23 calloc；G.7 xlang_ptr_slot_* + LE usize）；
 *     FROM_X 无 pure-dup free/get/set；
 *   + wave25 Cap residual pure：tmp path BSS 槽（asm 64B + parsed 64B/256B）在 thin.x；
 *     open_out 始终 seed 且只经 accessor 写 buf；FROM_X 无 pure-dup tmp 槽；
 *   + wave26 Cap residual pure：driver_parsed_fclose / fclose_rc / write_out 在 thin.x
 *     （g05 stdout_ptr + fclose/fwrite opaque；write_io_net/fs_path 仍 rt_preamble）；
 *     FROM_X 无 pure-dup fclose/write_out；
 *   + wave27 Cap residual pure：driver_parsed_open_out_file 在 thin.x
 *     （stdout 门控 pure；mkstemp/rename/close/unlink + g05 fopen_write_opaque；
 *      永久 OS residual xlang_driver_tmp_prefix 藏 XLANG_TMP_PREFIX #ifdef）；
 *     FROM_X 无 pure-dup open_out；
 *   + wave28 Cap residual pure：driver_parsed_invoke_cc 在 thin.x
 *   + wave31 Cap residual pure：deps_has_std_io_{core,driver} + apply_preamble_skip
 *     + maybe_dump_prep 在 thin.x（G.7 ptr_slot + strcmp；mask bits=codegen.h；
 *       dump 无 va_list）；FROM_X 无 pure-dup；
 *   + wave32 Cap residual pure：driver_parsed field accessors + try_c_after_pp 在 thin.x
 *     （LP64 offsetof DriverCompileParsedAbi + LE i32 / G.7 ptr；lib_roots=p+16；
 *       opt default BSS "2"；try_c_after_pp 产品 NO_C 固定 -2）；FROM_X 无 pure-dup；
 *     （std .o path pack + set/clear user .o + xlang_invoke_cc + fail/KEEP_C cleanup；
 *      c_paths[1] via G.7 xlang_ptr_slot_set；无 va_list reportf）；
 *     FROM_X 无 pure-dup invoke_cc；
 *   + wave33 Cap residual pure：driver_x_emit clear/bind/take/get/lib_root_at/
 *     effective_lib_roots + try_extern_via_cparser 在 thin.x
 *     （G.7 xlang_ptr_slot_* on always-seed c_path_cell / lib_roots_raw / path+lib slots；
 *       Cap-global-bss data 仍 rt_emit_state；path/scan/n/want slots always-seed）；
 *     FROM_X 无 pure-dup clear/bind/take/get/effective/try_extern；
 *   + wave34 Cap residual pure：driver_asm try_c stubs + use_compiler_impl_c +
 *     bind_lib_roots + argv0 + collect_defines/defines_as_u8/ndefines_get 在 thin.x
 *     （产品 NO_C 固定 -2/-1/0；one_root BSS + G.7；defines 表 BSS 64×LP64 +
 *       pure argv_collect_defines）；FROM_X 无 pure-dup；
 *   + wave35 Cap residual pure：driver_typeck_ndep_set / dep_ptrs_set +
 *     driver_diag_push_file / restore + driver_dispatch_lib_root_at / opt_default 在 thin.x
 *     （G.7 typeck_ndep_store + dep_module/arena_set；diag_push_file/restore；
 *       G.7 xlang_ptr_slot_get；opt default 共用 wave32 BSS lit "2"）；FROM_X 无 pure-dup；
 *   + wave36 Cap residual pure：driver_dispatch_lib_roots_from_key +
 *     driver_dispatch_run_compiler_parsed 在 thin.x
 *     （BSS 16×512 + 16×LP64 roots；G.7 driver_lib_roots_from_key；
 *       BSS pack DriverCompileParsedAbi 176B + driver_run_compiler_parsed；
 *       opt default 共用 wave32 lit "2"）；FROM_X 无 pure-dup；
 *   + wave37 Cap residual pure：driver_arena/module_static_{slot,size} +
 *     driver_run_stack_esc_gate_on_large_stack + driver_parser_diag_fail_tok_kind 在 thin.x
 *     （always-seed Cap-global base + Cap-fn-ptr fn_ptr residual；BSS pack slice +
 *       parser_diag_fail_at_token_kind；固定 128MiB/2MiB）；FROM_X 无 pure-dup；
 *   + wave38 Cap residual pure：driver_asm_elf_ctx_free + driver_parse_into_buf_rc 在 thin.x
 *     （free 配对 wave23 elf_ctx_calloc；Cap-struct-return residual
 *       xlang_parser_parse_into_buf_rc 藏 parser_ParseIntoResult）；FROM_X 无 pure-dup；
 *   + wave39 Cap residual pure：driver_stdio_stdout + driver_asm_fwrite +
 *     driver_x_emit_fwrite_stdout 在 thin.x
 *     （g05 stdout_ptr + fwrite_opaque；Cap OS residual xlang_driver_fwrite_stdout_n
 *       藏 xlang_io_write(1,…) Cap io 写与字节数返回 ABI；9.7.1 起无 libc FILE star）；
 *     FROM_X 无 pure-dup；
 *   + wave40 Cap residual pure：driver_stdio_stderr + driver_asm_fflush_stdout +
 *     driver_asm_fopen_wb + driver_asm_write_metric_o 在 thin.x
 *     （g05 stderr_ptr / fflush_stdout / fopen_wb_opaque；write_metric pure orch
 *       fopen_wb + fwrite 1×0 + fclose_opaque）；FROM_X 无 pure-dup；
 *   + wave41 Cap residual pure：driver_asm_mkstemp_fdopen 在 thin.x
 *     （null + SHARED gate xlang_driver_asm_mkstemp_fdopen_enabled→1；
 *       template pure tmp_prefix+"xlang_asm_XXXXXX"；mkstemp/close/unlink；
 *       g05 xlang_driver_fdopen_wb_opaque）；FROM_X 无 pure-dup；
 *   + wave42 Cap residual pure：driver_exec_compiled_body 在 thin.x
 *     （null/argc + G.7 path_is_non_exe pure；Cap residual
 *       xlang_driver_exec_scan_out_path_opaque + xlang_driver_exec_spawn_wait）；
 *   + wave43 Cap residual pure：driver_dispatch_sibling_try_spawn 在 thin.x
 *     （null/argc + G.7 driver_argv0_basename_is pure；path pure BSS 512；
 *       Cap residual xlang_driver_sibling_argv0_get + access_spawn）；
 *   + wave44 Cap residual pure：driver_print_usage_write 在 thin.x
 *     （color policy pure：NO_COLOR / FORCE / isatty；Cap residual
 *       xlang_driver_usage_write_stdout 持巨型 plain/color lit，
 *       经 xlang_io_write(1,…) Cap io 写，无 libc FILE star）；
 *     wave29：pure io_net N=224 + WEAK_IO skip 178..181；表数据仍 seed；
 * FROM_X 剔 pure-dup _impl（H↓）。
 */
/* Generated from src/runtime_driver_abi.x (G-02f-29/41/45..57/83 true .x + C tail).
 * G-02f-116 true .x pure helpers.
 * G-02f-104 helper gates.
 * G-02f-243: P1-6 open — entry_source_len_i32 saturate + scan_top_level_import pure.
 * G-02f-244: phase index + stack want + path import orchestrate pure.
 * G-02f-245: argv_collect_defines main loop pure; uname host defines locked.
 * G-02f-246: large_stack early-exit/current-stack orch pure; P1-6 soft near-close.
 * Regen: ./xlang-c -E -L .. src/runtime_driver_abi.x > /tmp/dabi.c
 *         merge flags/env/phase/peek/smoke/stack/defines; C uname + pthread create bulk.
 * .x covers: + argv_collect pure + large_stack orch + entry_len/scan/stack want/path.
 */
#include <xlang_weak.h>
#include "win32_compat.h"
#include "runtime_driver_abi.h"
#include "runtime_io_abi.h"
#include "runtime_pipeline_abi.h"
#include "runtime_abi.h"
#include "diag.h"
#include "runtime_diag_codes.h"

#ifdef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_check_quiet_ok_get(void);
int32_t driver_check_diag_emitted_get(void);
int32_t driver_is_large_stack_thread(void);
void driver_large_stack_thread_mark(int on);
void driver_run_fn_on_current_large_stack(void *(*fn)(void *), void *arg);
int32_t driver_compile_phase_index_ok(int32_t phase);
char driver_ascii_toupper(char c);
int32_t driver_typeck_skip_large_entry(void);
int32_t driver_sanitize_address_get(void);
int32_t driver_typeck_force_c_enabled(void);
int32_t driver_asm_build_skip_typeck(void);
int32_t driver_asm_entry_emit_heavy(void);
int32_t driver_pipeline_no_large_stack_env(void);
int32_t driver_asm_entry_module_only_from_env(void);
int32_t driver_asm_parse_metric_only_from_env(void);
int32_t driver_pipeline_entry_source_len_i32(void);
void driver_defines_set_at(const char **defines, int i, const char *s);
int64_t driver_stack_limit_want_bytes(void);
int64_t driver_path_last_preprocess_len(void);
void driver_path_last_preprocess_len_store(int64_t len);
void driver_current_dep_path_store(const char *path);
const char *driver_current_dep_path_load(void);
void driver_pipeline_entry_source_len_store(size_t len);
size_t driver_pipeline_entry_source_len_load_and_maybe_debug(void);
int32_t driver_target_arg_os_kind(const char *target);
void driver_bump_stack_limit(void);
void driver_set_pipeline_entry_source_len(size_t len);
int compile_phase_timing_enabled(void);
int32_t driver_compile_phase_timing_enabled(void);
const char *driver_os_define_lit(int kind);
void driver_run_thread_on_large_stack(void *(*fn)(void *), void *arg);
int driver_argv_collect_defines(int argc, char **argv, const char **defines, int max_defines);
int driver_source_has_top_level_import(const char *src, size_t src_len);
/* wave5: phase timing BSS pure in thin — flush Cap reads via getters. */
double driver_compile_phase_acc_ms_get(int32_t phase);
void driver_compile_phase_timing_clear(void);
/* wave7: compile_phase_now_sec pure in thin → xlang_driver_wall_clock_sec (no pure-dup _impl). */
/* wave1: flag-slot BSS pure in thin — no public→_impl rename (rest drops pure-dup slots). */
/* wave2: path/len BSS pure in thin — path_read rest writes len via thin store. */
/* wave11: path_read body is permanent OS surface xlang_driver_path_read_preprocess_malloc
 * (no pure-dup path_read _impl rename under FROM_X). */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: driver_abi path/uname format → Cap snprintf */
/* G.7: single Cap authority for this cold/rest TU (after stdio). */
#undef snprintf
#define snprintf xlang_snprintf
/* Cap residual 9.7.1: opaque stream face → fd-handle (write/open/close authorities). */
#include "xlang_driver_stream_cap.h"

#ifndef _WIN32
#include <sys/time.h>
#include <sys/utsname.h>
#include <xlang_time_cap.h> /* Cap residual 9.1.5 clock_gettime (wall clock) */
#ifndef _WIN32
#include <sys/resource.h>
#endif
#endif
#include <pthread.h>
/* PLATFORM: SHARED — realpath (opaque surface) on POSIX/Apple; unistd may already
 * be pulled later for Cap residual; include here so WEAK helpers stay self-contained. */
#if !defined(_WIN32) && !defined(_WIN64)
#include <unistd.h>
#endif

/*
 * Stage 12.0.5 pure-asm freestanding surface residual (G.7 有则补全 — single exported
 * authority; peer of fmt_check_cmd.from_x.c xlang_fmt_* WEAK bodies):
 *
 * pure-asm of runtime_pipeline_abi.x / runtime_driver_abi_thin.x leaves U
 * xlang_driver_{fputs,stdout,fclose,fwrite,fopen_*,stderr,fflush,fdopen,realpath}_opaque
 * and xlang_driver_{pipeline_run_x,asm_elf_o}_thread_fn_ptr. Host-cc prologue
 * (rt_prefer_try_x_to_o / g05_ensure) only injects static inline bodies (local `t` —
 * not exported). Without global defs, pure_asm_x_to_o rejected the .o and product
 * pabi prefer forced RT=0 (skip pure-asm install).
 *
 * Always export XLANG_WEAK bodies here for both cold monofile and FROM_X rest so
 * pure-asm thin / mega .o U's resolve at pure-ld against this leaf (always on
 * freestanding bag). Keep prologue static inline for -E inlining only; local `t`
 * does not multidef against these weak globals.
 *
 * Cap residual 9.7.1: the face no longer wraps libc FILE*. Every body encodes
 * raw fds via xlang_driver_stream_cap.h and routes I/O through the Cap
 * authorities (xlang_io_write / xlang_io_open_write / xlang_proc_close_fd), so
 * this TU carries zero stdio UNDEFs. Signatures stay `uint8_t *` (opaque),
 * which keeps every .x consumer source-compatible.
 *
 * PLATFORM: SHARED — fd-handle face (encoding in xlang_driver_stream_cap.h);
 * Win32 realpath null; thread_fn_ptr casts require product pipeline_run_x_thread_fn
 * and xlang_asm_codegen_elf_o_thread_fn T defs at final pure-ld (present on bag).
 */
XLANG_WEAK int32_t xlang_driver_fputs_opaque(uint8_t *s, uint8_t *stream) {
    long n;
    int fd;
    if (!s || !stream) {
        return (int32_t)-1;
    }
    fd = xlang_driver_handle_to_fd(stream);
    if (fd < 0) {
        return (int32_t)-1;
    }
    /* Mirrors fputs contract used by callers (driver_preamble_fputs checks <0):
     * return byte count written, or -1 on error. */
    n = xlang_io_write(fd, s, strlen((const char *)(void *)s));
    return (int32_t)n;
}

XLANG_WEAK uint8_t *xlang_driver_stdout_ptr(void) {
    return xlang_driver_handle_from_fd(1);
}

XLANG_WEAK int32_t xlang_driver_fclose_opaque(uint8_t *stream) {
    return (int32_t)xlang_driver_handle_close(stream);
}

XLANG_WEAK int32_t xlang_driver_fwrite_opaque(uint8_t *data, int32_t len, uint8_t *stream) {
    long n;
    int fd;
    if (!data || len < 0 || !stream) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }
    fd = xlang_driver_handle_to_fd(stream);
    if (fd < 0) {
        return 1;
    }
    n = xlang_io_write(fd, data, (size_t)len);
    return n == (size_t)len ? 0 : 1;
}

XLANG_WEAK uint8_t *xlang_driver_fopen_write_opaque(uint8_t *path) {
    int fd;
    if (!path) {
        return (uint8_t *)0;
    }
    /* fopen(path,"w") ≡ O_WRONLY|O_CREAT|O_TRUNC (0644) — the Cap authority. */
    fd = xlang_io_open_write((const char *)(void *)path);
    return fd < 0 ? (uint8_t *)0 : xlang_driver_handle_from_fd(fd);
}

XLANG_WEAK uint8_t *xlang_driver_stderr_ptr(void) {
    return xlang_driver_handle_from_fd(2);
}

XLANG_WEAK void xlang_driver_fflush_stdout(void) {
    /* Raw fd 1 writes are unbuffered — nothing to flush (9.7.1). */
}

XLANG_WEAK uint8_t *xlang_driver_fopen_wb_opaque(uint8_t *path) {
    int fd;
    if (!path) {
        return (uint8_t *)0;
    }
    /* Binary "wb" face: xlang_io_open_write is _O_BINARY on Windows (9.7.1),
     * so metric .o / asm .o emission cannot be CRLF-corrupted. */
    fd = xlang_io_open_write((const char *)(void *)path);
    return fd < 0 ? (uint8_t *)0 : xlang_driver_handle_from_fd(fd);
}

XLANG_WEAK uint8_t *xlang_driver_fdopen_wb_opaque(int32_t fd) {
    if (fd < 0) {
        return (uint8_t *)0;
    }
    /* fdopen(fd,"wb") consumed the caller's fd (mkstemp); the handle now owns
     * it — fclose_opaque/handle_close releases it, same contract as libc. */
    return xlang_driver_handle_from_fd((int)fd);
}

#if defined(_POSIX_VERSION) || defined(__APPLE__)
XLANG_WEAK uint8_t *xlang_driver_realpath_opaque(uint8_t *path, uint8_t *resolved) {
    char *r;
    if (!path || !resolved) {
        return (uint8_t *)0;
    }
    r = realpath((const char *)(void *)path, (char *)(void *)resolved);
    return (uint8_t *)(void *)r;
}
#else
/* PLATFORM: WINDOWS — no POSIX realpath; pure path_try leaves input path. */
XLANG_WEAK uint8_t *xlang_driver_realpath_opaque(uint8_t *path, uint8_t *resolved) {
    (void)path;
    (void)resolved;
    return (uint8_t *)0;
}
#endif

/* Match pure .x export: *u8 arg / *u8 return (not void* — gcc conflicts with pure body). */
extern uint8_t *pipeline_run_x_thread_fn(uint8_t *);
extern uint8_t *xlang_asm_codegen_elf_o_thread_fn(uint8_t *);

XLANG_WEAK uint8_t *xlang_driver_pipeline_run_x_thread_fn_ptr(void) {
    return (uint8_t *)(void *)pipeline_run_x_thread_fn;
}

XLANG_WEAK uint8_t *xlang_driver_asm_elf_o_thread_fn_ptr(void) {
    return (uint8_t *)(void *)xlang_asm_codegen_elf_o_thread_fn;
}

/* wave228 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv). */
extern char *link_abi_getenv(const char *name);

/** nostdlib 下勿用 glibc ctype 宏（会引用 __ctype_toupper_loc）；本地 ASCII 大写。 */
/* G-02f-119：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
char driver_ascii_toupper(char c) {
    if (c >= 'a' && c <= 'z')
        return (char)(c + ('A' - 'a'));
    return c;
}
/* G-02f：driver_env_flag_truthy 权威定义在 runtime_driver_abi_thin.x；
 *   PREFER_X_O fallback 时 seed 提供同语义 C 供产品 cc。 */
int32_t driver_env_flag_truthy(const char *name) {
    const char *e = link_abi_getenv(name);
    if (!e) return 0;
    if (e[0] == 0) return 0;
    if (e[0] == '0') return 0;
    return 1;
}
#endif





/* G-02f-41: flag slot protos (defs after static storage) */
int32_t *driver_check_only_flag_slot(void);
int32_t *driver_check_diag_emitted_flag_slot(void);
int32_t *driver_freestanding_flag_slot(void);
int32_t *driver_sanitize_address_flag_slot(void);
int32_t *driver_fmt_check_only_flag_slot(void);
int32_t *driver_x_pipeline_skip_typeck_flag_slot(void);
int32_t *driver_x_pipeline_skip_codegen_flag_slot(void);
int32_t *driver_skip_codegen_dep_0_flag_slot(void);
int32_t driver_pipeline_entry_source_len_i32(void);
int32_t *driver_large_stack_thread_flag_slot(void);
void driver_current_dep_path_store(const char *path);
const char *driver_current_dep_path_load(void);
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_check_ok_impl(const char *input_path);
void driver_pipeline_fail_code_rc_impl(int32_t rc);
void driver_pipeline_fail_code_path_impl(const uint8_t *path);
void driver_print_x_smoke_parse_ok_impl(int32_t num_funcs, int32_t main_ix, int64_t codegen_len);
void driver_print_x_smoke_parse_empty_impl(void);
void driver_print_x_smoke_typeck_ok_impl(void);
#endif
void driver_bump_stack_limit(void);
void xlang_driver_bump_stack_limit(int64_t want_bytes);
int64_t driver_stack_limit_want_bytes(void);
void driver_defines_set_at(const char **defines, int i, const char *s);
const char *driver_os_define_lit(int kind);
int xlang_driver_argv_append_uname(const char **defines, int ndefines, int max_defines);
int32_t driver_target_arg_os_kind(const char *target);
void driver_run_thread_on_large_stack(void *(*fn)(void *), void *arg);
void xlang_driver_run_thread_on_large_stack_pthread(void *(*fn)(void *), void *arg);
void xlang_driver_call_fn_void_arg(void *(*fn)(void *), void *arg);
int32_t driver_pipeline_no_large_stack_env(void);
int driver_source_scan_top_level_import(const char *src, size_t src_len);
char *xlang_driver_path_read_preprocess_malloc(const char *path);
char *driver_path_read_preprocess_malloc(const char *path);
int64_t driver_path_last_preprocess_len(void);
void driver_pipeline_entry_source_len_store(size_t len);
size_t driver_pipeline_entry_source_len_load_and_maybe_debug(void);
int32_t driver_compile_phase_timing_enabled(void);
int32_t driver_compile_phase_index_ok(int32_t phase);

/** xlang check：非 0 时 typeck 通过后跳过 codegen 与链接（C 与 X pipeline 共用）。 */
/* wave1 pure：hybrid thin owns BSS; cold seed keeps statics + flag_slot. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_check_only_flag;
static int driver_check_diag_emitted_flag;
#endif

/**
 * 设置 check-only 模式。
 * 参数：v 非 0 启用。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_check_only_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_check_only_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/**
 * 查询 check-only 模式。
 * 返回值：1 表示启用，0 表示否。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_check_only_get(void) {
  (void)(({   {
    int32_t * p = driver_check_only_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_check_diag_emitted_reset(void) {
  (void)(({   {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    (void)(((p)[0] = 0));
  }
 }));
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_check_diag_emitted_note(void) {
  (void)(({   {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    (void)(((p)[0] = 1));
  }
 }));
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_check_diag_emitted_get(void) {
  (void)(({   {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/** `-freestanding` / XLANG_FREESTANDING：用户程序 nostdlib 静态链（S4）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_freestanding_flag;
#endif

/** 设置 freestanding 链接模式。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_freestanding_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_freestanding_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/** 查询 freestanding 链接模式。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_freestanding_get(void) {
  (void)(({   {
    int32_t * p = driver_freestanding_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/** M-6：`-fsanitize=address` 时强制数组/切片 INDEX 边界检查。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_sanitize_address_flag;
#endif

/** 设置 sanitize=address 标志。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_sanitize_address_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_sanitize_address_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/**
 * 查询 sanitize=address；显式标志或 XLANG_SANITIZE_ADDRESS 环境变量。
 * pure 权威：thin.x driver_sanitize_address_get（flag + env 门闩）；
 * 冷启动保留全 C 体；FROM_X 无 pure-dup env_enabled_impl（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_sanitize_address_get(void) {
  (void)(({   {
    int32_t * p = driver_sanitize_address_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    char *e = link_abi_getenv("XLANG_SANITIZE_ADDRESS");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_fmt_check_only_flag;
#endif

/** xlang fmt --check：仅校验格式，不写回。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_fmt_check_only_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_fmt_check_only_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/** 查询 fmt --check 模式。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_fmt_check_only_get(void) {
  (void)(({   {
    int32_t * p = driver_fmt_check_only_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/* 【Why 根源】MinGW PE 格式不真正支持 XLANG_WEAK：weak 函数被当作普通强符号，
 * 与 fmt_check_cmd.c 的强符号并存；--allow-multiple-definition 选第一个遇到的定义，
 * 链接器不保证按 OBJS_CORE 顺序选 fmt_check_cmd.o 的版本。当 weak 版本被选中且返回 0，
 * check 成功后会逐文件打印 "check OK"，与 deno check 静默成功语义矛盾。
 * 【Invariant】deno check 语义：成功时静默。weak 默认值必须返回 1（静默），保证无论
 * Windows 链接器选中哪个版本，driver_print_check_ok 都不输出逐文件 check OK。
 * 【Asm/Perf】macOS/Linux 上 weak 正常工作，强符号覆盖 weak 默认值，此改动无影响。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
XLANG_WEAK int32_t driver_check_quiet_ok_get(void) {
  return 1;
}
#endif

/**
 * 统一 xlang check 成功行；deno 风格批量 check 成功时由 fmt_check_cmd 保持静默。
 * 参数：input_path 被检查文件路径（可为 NULL）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_check_ok(const char *input_path) {
  (void)(({   {
    if ((driver_check_quiet_ok_get() !=0)) {
      return;
    }
    (void)(driver_print_check_ok_impl(input_path));
  }
 }));
}
#endif

/** 非 0 时 pipeline_impl_typecheck 跳过 .x typeck。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_x_pipeline_skip_typeck_flag;
#endif

/** 供 pipeline.x 读取：是否跳过 X typeck。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_x_pipeline_skip_typeck_get(void) {
  (void)(({   {
    int32_t * p = driver_x_pipeline_skip_typeck_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/** 设置 X typeck 跳过标志（C 预检后由 runtime 置位/清位）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_x_pipeline_skip_typeck_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_x_pipeline_skip_typeck_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/** 非 0 时 pipeline_impl_run_all 跳过 .x C codegen。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_x_pipeline_skip_codegen_flag;
#endif

/** 供 pipeline.x 读取：是否跳过 X C codegen。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_x_pipeline_skip_codegen_get(void) {
  (void)(({   {
    int32_t * p = driver_x_pipeline_skip_codegen_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/** 设置 X C codegen 跳过标志。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_x_pipeline_skip_codegen_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_x_pipeline_skip_codegen_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/**
 * 非 0 时入口模块 typeck 走 C 的 typeck_module（大模块 asm 构建时避免 .x typeck 栈过深）。
 * pure 权威：thin.x driver_typeck_force_c_enabled；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_typeck_force_c_enabled_impl(void) {
  (void)(({   {
    char *e = link_abi_getenv("XLANG_TYPECK_FORCE_C");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}

int32_t driver_typeck_force_c_enabled(void) {
  return driver_typeck_force_c_enabled_impl();
}
#endif

/** 当前线程是否已在 driver_run_thread_on_large_stack 创建的大栈 pthread 内。
 * 【Why 逻辑根源】nostdlib 静态链下 pthread 是 stub（bootstrap_nostdlib_pthread_is_stub()=1），
 *                driver_run_thread_on_large_stack 在当前栈运行不创建新线程，全程单线程无需 TLS。
 *                之前用 _Thread_local 时 gcc 对 _impl 生成 `mov %fs:0x0,%rax; add $-16,%rax` 间接访问，
 *                bootstrap_init_static_tls 只把 %fs 设为 &bootstrap_tls（48 字节 block），
 *                %fs:0x0 读到 BSS 默认值 0，0-16=0xfffffffffffffff0 无效地址 → SIGSEGV。
 *                stage1 工作纯属巧合：编译器把 driver_is_large_stack_thread 内联为 `mov %fs:-16,%eax`。
 * 【Invariant 状态不变量】nostdlib 路径下进程内只有 1 个执行流，单变量即正确反映"在大栈线程上下文"标志。
 * 【Asm/Perf 性能预期】普通 static int 在 BSS 中，访问为 RIP-relative 一次 load，比 TLS 间接访问快且无 %fs 依赖。 */
/* wave1 pure：hybrid thin owns large_stack flag BSS; cold seed keeps static + slot. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int g_driver_on_large_stack_thread;

/* G-02f-45 */
int32_t *driver_large_stack_thread_flag_slot(void) {
    return (int32_t *)&g_driver_on_large_stack_thread;
}
#endif


/**
 * 供 ast_pool / pipeline glue 查询：LSP 主循环已在大栈线程上时，typeck 勿再 spawn 嵌套 pthread。
 * 返回值：非 0 表示当前在大栈线程上下文。
 */

#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_is_large_stack_thread(void) {
  (void)(({   {
    int32_t * p = driver_large_stack_thread_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/**
 * 标记当前线程大栈上下文（runtime pthread trampoline 进入/退出时调用）。
 * 参数：on 非 0 进入，0 退出。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_large_stack_thread_mark(int on) {
  (void)(({   {
    int32_t * p = driver_large_stack_thread_flag_slot();
    (void)(((p)[0] = on));
  }
 }));
}
#endif

/* wave2 pure：hybrid thin owns entry_source_len BSS; cold seed keeps static + store/load. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
/** 当前 pipeline 入口源码长度；供 .x 按体积跳过大库 merge/typeck。 */
static size_t g_pipeline_entry_source_len;

/* G-02f-45 / G-02f-243 / G-02f-388：冷路径读 static；FROM_X 权威 = thin.x */
int32_t driver_pipeline_entry_source_len_i32_impl(void) {
    if (g_pipeline_entry_source_len > (size_t)0x7fffffff)
        return 0x7fffffff;
    return (int32_t)g_pipeline_entry_source_len;
}

int32_t driver_pipeline_entry_source_len_i32(void) {
    return driver_pipeline_entry_source_len_i32_impl();
}

void driver_pipeline_entry_source_len_store_impl(size_t len) {
    g_pipeline_entry_source_len = len;
}

void driver_pipeline_entry_source_len_store(size_t len) {
    driver_pipeline_entry_source_len_store_impl(len);
}

/* wave13 pure：hybrid thin owns load+debug note (append + diag_report); cold keeps integer twin.
 * PLATFORM: SHARED — truthy XLANG_DEBUG_PIPE (non-empty and != '0') matches thin driver_env_flag_truthy. */
size_t driver_pipeline_entry_source_len_load_and_maybe_debug_impl(void) {
    const char *e = link_abi_getenv("XLANG_DEBUG_PIPE");
    if (e != NULL && e[0] != '\0' && e[0] != '0') {
        /* Integer twin of thin pure note text (no float; matches driver_abi_append_i64 decimal). */
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "pipeline debug: entry_source_len_global=%lld",
                     (long long)g_pipeline_entry_source_len);
    }
    return g_pipeline_entry_source_len;
}

size_t driver_pipeline_entry_source_len_load_and_maybe_debug(void) {
    return driver_pipeline_entry_source_len_load_and_maybe_debug_impl();
}

/**
 * 记录 pipeline 入口源码字节数（大栈 pthread 进入 pipeline 前调用）。
 * 参数：len 预处理后的入口源码长度。
 */
void driver_set_pipeline_entry_source_len(size_t len) {
  {
    driver_pipeline_entry_source_len_store_impl(len);
  }
}

/**
 * 查询当前记录的入口源码长度；XLANG_DEBUG_PIPE=1 时打印。
 * 返回值：最近一次 driver_set_pipeline_entry_source_len 写入的长度。
 */
size_t driver_pipeline_entry_source_len_impl(void) {
    return driver_pipeline_entry_source_len_load_and_maybe_debug_impl();
}

size_t driver_pipeline_entry_source_len(void) {
    return driver_pipeline_entry_source_len_impl();
}
#endif

/**
 * 非 0 表示入口源码过大，应跳过 merge/library 全量 typeck（.x 路径上易 segfault）。
 * 返回值：len > 150000 时为 1，否则 0。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_typeck_skip_large_entry(void) {
  (void)(({   {
    int32_t len = driver_pipeline_entry_source_len_i32_impl();
    if ((len > 150000)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/**
 * build_xlang_asm 单模块 -o：XLANG_ASM_BUILD_SKIP_TYPECK=1 时跳过 .x typeck。
 * pure 权威：thin.x；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_asm_build_skip_typeck_impl(void) {
  (void)(({   {
    char *e = link_abi_getenv("XLANG_ASM_BUILD_SKIP_TYPECK");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}

int32_t driver_asm_build_skip_typeck(void) {
  return driver_asm_build_skip_typeck_impl();
}
#endif

/**
 * typeck 第二遍 EMIT_HEAVY：XLANG_ASM_ENTRY_EMIT_HEAVY=1 时 pipeline 跳过文本 asm codegen。
 * pure 权威：thin.x；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_asm_entry_emit_heavy_impl(void) {
  (void)(({   {
    char *e = link_abi_getenv("XLANG_ASM_ENTRY_EMIT_HEAVY");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}

int32_t driver_asm_entry_emit_heavy(void) {
  return driver_asm_entry_emit_heavy_impl();
}
#endif

/**
 * build_xlang_asm 单模块 -o：XLANG_ASM_ENTRY_MODULE_ONLY=1 时仅编入口模块。
 * pure 权威：thin.x；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_asm_entry_module_only_from_env_impl(void) {
  (void)(({   {
    char *e = link_abi_getenv("XLANG_ASM_ENTRY_MODULE_ONLY");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}

int32_t driver_asm_entry_module_only_from_env(void) {
  return driver_asm_entry_module_only_from_env_impl();
}
#endif

/**
 * A-11 typeck-parse-count-gate：仅采集 parse 指标，不跑 pipeline/asm_codegen_elf_o。
 * pure 权威：thin.x；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_asm_parse_metric_only_from_env_impl(void) {
  (void)(({   {
    char *e = link_abi_getenv("XLANG_ASM_PARSE_METRIC_ONLY");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}

int32_t driver_asm_parse_metric_only_from_env(void) {
  return driver_asm_parse_metric_only_from_env_impl();
}
#endif

/** -o 可执行文件路径：非 0 时 pipeline 跳过 dep 0 的 codegen。 */
/* wave1 pure：hybrid thin owns flag BSS; cold seed keeps statics + flag_slot bodies. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int driver_skip_codegen_dep_0_flag;

/* G-02f-41: flag slot implementations (cold full C; FROM_X pure authority = thin.x) */
int32_t *driver_check_only_flag_slot(void) { return (int32_t *)&driver_check_only_flag; }
int32_t *driver_check_diag_emitted_flag_slot(void) { return (int32_t *)&driver_check_diag_emitted_flag; }
int32_t *driver_freestanding_flag_slot(void) { return (int32_t *)&driver_freestanding_flag; }
int32_t *driver_sanitize_address_flag_slot(void) { return (int32_t *)&driver_sanitize_address_flag; }
int32_t *driver_fmt_check_only_flag_slot(void) { return (int32_t *)&driver_fmt_check_only_flag; }
int32_t *driver_x_pipeline_skip_typeck_flag_slot(void) { return (int32_t *)&driver_x_pipeline_skip_typeck_flag; }
int32_t *driver_x_pipeline_skip_codegen_flag_slot(void) { return (int32_t *)&driver_x_pipeline_skip_codegen_flag; }
int32_t *driver_skip_codegen_dep_0_flag_slot(void) { return (int32_t *)&driver_skip_codegen_dep_0_flag; }
#endif


/** 设置 skip_codegen_dep_0 标志（driver -o exe 路径）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_skip_codegen_dep_0_set(int32_t v) {
  (void)(({   {
    int32_t * p = driver_skip_codegen_dep_0_flag_slot();
    (void)(((p)[0] = v));
  }
 }));
}
#endif

/** 查询 skip_codegen_dep_0；pipeline.x dep_j==0 时读取。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_skip_codegen_dep_0_get(void) {
  (void)(({   {
    int32_t * p = driver_skip_codegen_dep_0_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
 }));
  return 0;
}
#endif

/* wave2 pure：hybrid thin owns dep-path BSS; cold seed keeps static + store/load. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
/** 当前 codegen 的 dep 逻辑路径（如 std.io.driver），供 .x codegen 前缀 C 符号。 */
static char driver_current_dep_path_buf[128];
static const char *driver_current_dep_path_for_codegen;

/* G-02f-46: dep path store/load + print_check_ok diag impl */
void driver_current_dep_path_store_impl(const char *path) {
    int i;
    if (!path || path[0] == 0) {
        driver_current_dep_path_buf[0] = 0;
        driver_current_dep_path_for_codegen = NULL;
        return;
    }
    for (i = 0; i < 127 && path[i]; i++)
        driver_current_dep_path_buf[i] = path[i];
    driver_current_dep_path_buf[i] = 0;
    driver_current_dep_path_buf[127] = 0;
    driver_current_dep_path_for_codegen = driver_current_dep_path_buf;
}

void driver_current_dep_path_store(const char *path) {
    driver_current_dep_path_store_impl(path);
}

const char *driver_current_dep_path_load_impl(void) {
    return driver_current_dep_path_buf[0] ? driver_current_dep_path_buf : NULL;
}

const char *driver_current_dep_path_load(void) {
    return driver_current_dep_path_load_impl();
}
#endif

/* wave3 pure：hybrid thin owns format print (append + diag_report*); cold keeps reportf _impl. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_check_ok_impl(const char *input_path) {
    diag_reportf(NULL, 0, 0, "info", NULL,
                 "check OK: %s", input_path ? input_path : "?");
}

void driver_pipeline_fail_code_rc_impl(int32_t rc) {
    diag_reportf_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP003, NULL,
                           "pipeline failed rc=%d", (int)rc);
}

void driver_pipeline_fail_code_path_impl(const uint8_t *path) {
    diag_reportf_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP004, NULL,
                           "resolve path tried: %s", path ? (const char *)path : "?");
}

void driver_print_x_smoke_parse_ok_impl(int32_t num_funcs, int32_t main_ix, int64_t codegen_len) {
    diag_reportf(NULL, 0, 0, "info", NULL,
                 "parse OK: num_funcs=%d main_idx=%d codegen_bytes=%zu",
                 (int)num_funcs, (int)main_ix, (size_t)codegen_len);
}

void driver_print_x_smoke_parse_empty_impl(void) {
    diag_report_with_code(NULL, 0, 0, "parse error", XLANG_DIAG_CODE_PARSE_P001,
                "parse produced no functions in module", NULL);
}

void driver_print_x_smoke_typeck_ok_impl(void) {
    diag_report(NULL, 0, 0, "info", "typeck OK", NULL);
}
#endif



/**
 * 设置当前 dep 路径；pipeline codegen 循环每 dep 调用。
 * 参数：path import 逻辑路径或 NULL 清槽。
 * wave2 pure：hybrid thin owns; cold keeps store wrapper.
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_set_current_dep_path_for_codegen(const char *path) {
  (void)(({   {
    (void)(driver_current_dep_path_store_impl(path));
  }
 }));
}
/* G-02f-413：cold get → load_impl；FROM_X pure = thin load. */
const char *driver_get_current_dep_path_for_codegen_impl(void) {
    return driver_current_dep_path_load_impl();
}
const char *driver_get_current_dep_path_for_codegen(void) {
    return driver_get_current_dep_path_for_codegen_impl();
}
#endif



/** OBS-001：编译阶段耗时；phase 0=parse 1=typeck 2=codegen。 */
#define XLANG_COMPILE_PHASE_MAX 3

/* wave5 pure：hybrid thin owns phase timing BSS; cold seed keeps statics + begin/end _impl. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static double g_compile_phase_acc_ms[XLANG_COMPILE_PHASE_MAX];
static double g_compile_phase_start_sec[XLANG_COMPILE_PHASE_MAX];
static int g_compile_phase_active[XLANG_COMPILE_PHASE_MAX];
#endif

/** 是否启用 XLANG_COMPILE_PHASE_TIMING 阶段计时。 */
/* pure 权威：thin.x compile_phase_timing_enabled（getenv 非空）；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int compile_phase_timing_enabled_impl(void) {
  return link_abi_getenv("XLANG_COMPILE_PHASE_TIMING") != NULL;
}

int compile_phase_timing_enabled(void) {
  return compile_phase_timing_enabled_impl();
}
#endif



/**
 * Permanent OS wall-clock surface (seconds as double).
 * PLATFORM: POSIX — Cap clock_gettime(CLOCK_REALTIME); WINDOWS — time(NULL) (usec=0).
 * Always present under FROM_X (thin compile_phase_now_sec calls this; no pure-dup _impl).
 * G.7: single authority for wall clock used by phase timing.
 * Cap residual 9.1.5: no libc gettimeofday on Linux.
 */
double xlang_driver_wall_clock_sec(void)
{
#ifndef _WIN32
    struct timespec ts;
    if (xlang_time_clock_gettime(CLOCK_REALTIME, &ts) != 0)
        return 0.0;
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
#else
    {
        struct timeval tv;
        time_t t = time(NULL);
        tv.tv_sec = (long)t;
        tv.tv_usec = 0;
        return (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
    }
#endif
}

/** Wall-clock seconds for phase timing (cold twin of thin pure wave7). */
/* G-02f-165 / wave7：hybrid thin owns public; cold seed keeps thin twin via OS surface. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
double compile_phase_now_sec(void)
{
    return xlang_driver_wall_clock_sec();
}
#endif




/* G-02f-244：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_compile_phase_index_ok(int32_t phase) {
    if (phase < 0)
        return 0;
    if (phase >= XLANG_COMPILE_PHASE_MAX)
        return 0;
    return 1;
}
#endif

/* wave5：cold seed getters twin thin pure surface (hybrid uses thin symbols). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
double driver_compile_phase_acc_ms_get(int32_t phase) {
    if (!driver_compile_phase_index_ok(phase))
        return 0.0;
    return g_compile_phase_acc_ms[phase];
}

void driver_compile_phase_timing_clear(void) {
    memset(g_compile_phase_acc_ms, 0, sizeof(g_compile_phase_acc_ms));
    memset(g_compile_phase_active, 0, sizeof(g_compile_phase_active));
}
#endif

/**
 * 标记编译阶段开始；由 pipeline.x run_x_pipeline_impl 调用。
 * 参数：phase 0..2。
 * wave5 pure：hybrid thin owns begin；cold keeps _impl；FROM_X 无 pure-dup。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_compile_phase_timing_begin_impl(int32_t phase) {
    if (!driver_compile_phase_index_ok(phase))
        return;
    g_compile_phase_start_sec[phase] = compile_phase_now_sec();
    g_compile_phase_active[phase] = 1;
}
#endif

/**
 * 累加阶段耗时（毫秒）；同 phase 可多次 begin/end 叠加。
 * 参数：phase 0..2。
 * wave5 pure：hybrid thin owns end；cold keeps _impl；FROM_X 无 pure-dup。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_compile_phase_timing_end_impl(int32_t phase) {
    if (!driver_compile_phase_index_ok(phase) || !g_compile_phase_active[phase])
        return;
    g_compile_phase_acc_ms[phase] += (compile_phase_now_sec() - g_compile_phase_start_sec[phase]) * 1000.0;
    g_compile_phase_active[phase] = 0;
}
#endif

/** 打印 parse/typeck/codegen/total 毫秒汇总行并清零；XLANG_COMPILE_PHASE_TIMING 启用时生效。
 * wave6 pure：hybrid thin owns flush（whole-ms append + diag_report）；cold keeps integer-ms twin；
 * FROM_X 无 pure-dup flush _impl。acc 经 driver_compile_phase_acc_ms_get（thin/cold twin）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_compile_phase_timing_flush_impl(void) {
    int a0 = (int)driver_compile_phase_acc_ms_get(0);
    int a1 = (int)driver_compile_phase_acc_ms_get(1);
    int a2 = (int)driver_compile_phase_acc_ms_get(2);
    int total = a0 + a1 + a2;
    /* PLATFORM: SHARED — whole-ms twin of thin pure (wave6); no reportf floats. */
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "compile phase timing: parse_ms=%d typeck_ms=%d codegen_ms=%d total_ms=%d",
                 a0, a1, a2, total);
    driver_compile_phase_timing_clear();
}

void driver_compile_phase_timing_flush(void) {
  (void)(({   {
    if ((driver_compile_phase_timing_enabled() ==0)) {
      return;
    }
    (void)(driver_compile_phase_timing_flush_impl());
  }
 }));
}
#endif

/* G-02f-244：逻辑源 .x（门闩 → index_ok pure）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_compile_phase_timing_end(int32_t phase) {
  (void)(({   {
    if ((driver_compile_phase_timing_enabled() ==0)) {
      return;
    }
    if ((driver_compile_phase_index_ok(phase) ==0)) {
      return;
    }
    (void)(driver_compile_phase_timing_end_impl(phase));
  }
 }));
}
#endif

/* pure 权威：thin.x driver_compile_phase_timing_enabled；冷启动保留 public；FROM_X 无 pure-dup（H↓）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_compile_phase_timing_enabled(void)
{
  (void)(({   {
    char *e = link_abi_getenv("XLANG_COMPILE_PHASE_TIMING");
    if ((e ==((char *)(0)))) {
      return 0;
    }
    return 1;
  }
 }));
  return 0;
}
#endif

/* G-02f-244：逻辑源 .x（门闩 → index_ok pure）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_compile_phase_timing_begin(int32_t phase) {
  (void)(({   {
    if ((driver_compile_phase_timing_enabled() ==0)) {
      return;
    }
    if ((driver_compile_phase_index_ok(phase) ==0)) {
      return;
    }
    (void)(driver_compile_phase_timing_begin_impl(phase));
  }
 }));
}
#endif


/**
 * 从 argv 收集 -D / -DFOO 与 -target 推导 OS_*、uname 的 XLANG_OS_/XLANG_ARCH_（run_compiler_c / asm 后端共用）。
 * 参数：defines 至少 max_defines 个槽；返回 ndefines。
 * G-02f-245：主循环逻辑源 .x pure；uname 🔒。
 */
/* wave4 pure：hybrid thin owns defines_set_at (xlang_ptr_slot_set) + os_define_lit table;
 * cold keeps _impl + public; FROM_X rest drops pure-dup set_at/os_lit _impl. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_defines_set_at_impl(const char **defines, int i, const char *s) {
    if (!defines || i < 0)
        return;
    defines[i] = s;
}

void driver_defines_set_at(const char **defines, int i, const char *s) {
    driver_defines_set_at_impl(defines, i, s);
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
const char *driver_os_define_lit_impl(int kind) {
    if (kind == 1)
        return "OS_LINUX";
    if (kind == 2)
        return "OS_MACOS";
    if (kind == 3)
        return "OS_FREEBSD";
    if (kind == 4)
        return "OS_WINDOWS";
    return NULL;
}

const char *driver_os_define_lit(int kind) {
    return driver_os_define_lit_impl(kind);
}
#endif

/* G-02f-245：逻辑源 .x（真迁 target→OS kind）；seed 保留同语义 C 供产品 cc */
/* G-02f-401：strstr 字面量体始终 seed；public PREFER 时 thin forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_target_arg_os_kind_impl(const char *target) {
    if (!target)
        return 0;
    if (strstr(target, "linux") != NULL)
        return 1;
    if (strstr(target, "darwin") != NULL || strstr(target, "apple") != NULL)
        return 2;
    if (strstr(target, "freebsd") != NULL)
        return 3;
    if (strstr(target, "windows") != NULL)
        return 4;
    return 0;
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_target_arg_os_kind(const char *target) {
    return driver_target_arg_os_kind_impl(target);
}
#endif

/**
 * Permanent OS uname host-define surface (XLANG_OS_* / XLANG_ARCH_*).
 * PLATFORM: POSIX — uname(struct utsname) + static define buffers; hides utsname from .x.
 *            WINDOWS — may no-op via uname stub if present; same signature.
 * Always present under FROM_X (thin argv_collect pure orch calls this;
 * no pure-dup driver_argv_collect_append_uname_impl).
 * G.7: single authority for host OS/arch define append used by argv_collect.
 */
int xlang_driver_argv_append_uname(const char **defines, int ndefines, int max_defines) {
    struct utsname u;
    static char xlang_os_def[80], xlang_arch_def[80];
    if (!defines)
        return ndefines;
    if (ndefines + 2 > max_defines)
        return ndefines;
    if (uname(&u) != 0)
        return ndefines;
    snprintf(xlang_os_def, sizeof xlang_os_def, "XLANG_OS_%s", u.sysname);
    snprintf(xlang_arch_def, sizeof xlang_arch_def, "XLANG_ARCH_%s", u.machine);
    for (char *p = xlang_os_def + 7; *p; p++)
        *p = driver_ascii_toupper(*p);
    for (char *p = xlang_arch_def + 9; *p; p++)
        *p = driver_ascii_toupper(*p);
    defines[ndefines++] = xlang_os_def;
    defines[ndefines++] = xlang_arch_def;
    return ndefines;
}

/* G-02f-245：逻辑源 .x；G-02f-413：实现体始终 seed；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_argv_collect_defines_impl(int argc, char **argv, const char **defines, int max_defines) {
    int ndefines = 0;
    const char *target_arg = NULL;
    int i;
    if (argv == NULL)
        return 0;
    if (defines == NULL)
        return 0;
    if (max_defines <= 0)
        return 0;
    if (argc <= 0)
        return 0;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (!arg)
            continue;
        if (strcmp(arg, "-D") == 0) {
            if (i + 1 >= argc)
                continue;
            if (ndefines < max_defines)
                defines[ndefines++] = argv[i + 1];
            i++;
        } else if (strncmp(arg, "-D", 2) == 0 && arg[2] != '\0') {
            if (ndefines < max_defines)
                defines[ndefines++] = arg + 2;
        } else if (strcmp(arg, "-target") == 0 && i + 1 < argc) {
            target_arg = argv[i + 1];
            i++;
        } else if (strcmp(arg, "-o") == 0 || strcmp(arg, "-L") == 0 || strcmp(arg, "-O") == 0 ||
                   strcmp(arg, "-backend") == 0) {
            if (i + 1 < argc)
                i++;
        }
    }
    if (target_arg && ndefines < max_defines) {
        int k = (int)driver_target_arg_os_kind_impl(target_arg);
        if (k != 0) {
            const char *lit = driver_os_define_lit_impl(k);
            if (lit)
                defines[ndefines++] = lit;
        }
    }
    if (ndefines + 2 <= max_defines)
        ndefines = xlang_driver_argv_append_uname(defines, ndefines, max_defines);
    return ndefines;
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_argv_collect_defines(int argc, char **argv, const char **defines, int max_defines) {
    return driver_argv_collect_defines_impl(argc, argv, defines, max_defines);
}
#endif

/** pipeline_gen.c / main.x：module num_funcs 与 main 下标。 */
extern int driver_get_module_num_funcs(void *m);
extern int driver_get_module_main_func_index(void *m);

/** pipeline 失败 rc 诊断；rc==-7 时打印 resolve 尝试路径。 */
/* G-02f-413：实现体始终 seed；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_pipeline_fail_code_impl(int rc, const uint8_t *path) {
    driver_pipeline_fail_code_rc_impl((int32_t)rc);
    if (rc != -7) {
        return;
    }
    if (path == NULL) {
        return;
    }
    driver_pipeline_fail_code_path_impl(path);
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_pipeline_fail_code(int rc, const uint8_t *path) {
    driver_pipeline_fail_code_impl(rc, path);
}
#endif

/**
 * .x pipeline 烟测 stderr 摘要；保留 parse OK / typeck OK 前缀供 run-import gate grep。
 * 参数：module ASTModule*；codegen_len 产出字节数（可为 0）。
 */
/* G-02f-244/413：实现体始终 seed；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_x_smoke_summary_impl(void *module, size_t codegen_len) {
    int32_t num_funcs;
    int32_t main_ix;
    if (module == NULL) {
        return;
    }
    if (driver_check_diag_emitted_get() != 0) {
        return;
    }
    num_funcs = (int32_t)driver_get_module_num_funcs(module);
    main_ix = (int32_t)driver_get_module_main_func_index(module);
    driver_print_x_smoke_parse_ok_impl(num_funcs, main_ix, (int64_t)codegen_len);
    if (num_funcs <= 0) {
        driver_print_x_smoke_parse_empty_impl();
        return;
    }
    driver_print_x_smoke_typeck_ok_impl();
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_x_smoke_summary(void *module, size_t codegen_len) {
    driver_print_x_smoke_summary_impl(module, codegen_len);
}
#endif

/**
 * B-20：读源文件前缀到 content（最多 cap-1 字节）；成功返回读入字节数，失败 -1。
 * 参数：path 源路径；content/cap 输出缓冲；实现委托 runtime_io_abi。
 */
/* G-02f-413：实现体始终 seed；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_peek_source_file_impl(const char *path, char *content, size_t cap) {
    int32_t n;
    if (path == NULL) {
        return -1;
    }
    if (content == NULL) {
        return -1;
    }
    if (cap <= 1) {
        return -1;
    }
    n = xlang_read_file_into_path(path, content, (size_t)(cap - 1));
    return (int)n;
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_peek_source_file(const char *path, char *content, size_t cap) {
    return driver_peek_source_file_impl(path, content, cap);
}
#endif

/**
 * 大模块 pipeline 栈帧深；macOS 默认 RLIMIT_STACK 约 512KiB～8MiB，进入 pipeline 前抬高软上限。
 * NL-07 nostdlib：pthread 大栈桩无效，须把主线程软上限抬到 256MiB 以免 -o 编译栈溢出 SIGSEGV。
 * G-02f-244：want pure 在 .x；setrlimit / nostdlib 覆盖 🔒 在 to_impl。
 */
/* pure 权威：thin.x driver_parse_u32_cstr + driver_stack_limit_want_bytes；
 * 冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static int64_t driver_parse_u32_cstr(const char *s) {
    int64_t n = 0;
    int i = 0;
    if (!s || !s[0])
        return -1;
    for (i = 0; i < 20 && s[i]; i++) {
        unsigned char c = (unsigned char)s[i];
        if (c < '0' || c > '9')
            return -1;
        n = n * 10 + (int64_t)(c - '0');
    }
    if (i == 0)
        return -1;
    return n;
}

int64_t driver_stack_limit_want_bytes_impl(void) {
    int64_t def = (int64_t)512 * 1024 * 1024;
    const char *e = link_abi_getenv("XLANG_STACK_LIMIT_MB");
    int64_t mb;
    if (!e || !e[0])
        return def;
    mb = driver_parse_u32_cstr(e);
    if (mb < 64 || mb > 8192)
        return def;
    return mb * (int64_t)(1024 * 1024);
}

int64_t driver_stack_limit_want_bytes(void) {
    return driver_stack_limit_want_bytes_impl();
}
#endif

/**
 * Permanent OS RLIMIT_STACK raise surface.
 * PLATFORM: POSIX — getrlimit/setrlimit (struct rlimit hidden from .x);
 *            WINDOWS — no-op (want_bytes unused).
 * Always present under FROM_X (thin driver_bump_stack_limit pure orch calls this;
 * no pure-dup driver_bump_stack_limit_to_impl).
 * G.7: single authority for stack soft-limit raise used by large-stack paths.
 */
void xlang_driver_bump_stack_limit(int64_t want_bytes) {
    #ifndef _WIN32
    struct rlimit rl;
    rlim_t want = (rlim_t)want_bytes;
    if (want_bytes <= 0)
        want = (rlim_t)(512 * 1024 * 1024);
    if (bootstrap_nostdlib_pthread_is_stub())
        want = (rlim_t)(512 * 1024 * 1024);
    if (getrlimit(RLIMIT_STACK, &rl) == 0 && rl.rlim_cur < want) {
        rl.rlim_cur = want;
        if (rl.rlim_max > (rlim_t)0 && rl.rlim_cur > rl.rlim_max)
            rl.rlim_cur = rl.rlim_max;
        (void)setrlimit(RLIMIT_STACK, &rl);
    }
    #else
    (void)want_bytes;
    #endif
}

/* G-02f-244 / wave9：逻辑源 .x（want pure → permanent OS surface）；seed 冷 twin */
/* G-02f-402：public PREFER 时 thin owns driver_bump_stack_limit orch */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_bump_stack_limit(void) {
    xlang_driver_bump_stack_limit(driver_stack_limit_want_bytes_impl());
}
#endif



/** pthread 大栈调用参数（trampoline 解包 fn/arg）。 */
typedef struct {
    void *(*fn)(void *);
    void *arg;
} DriverLargeStackCall;

/** pthread 入口：标记大栈线程并抬高 soft limit 后执行用户 fn。 */
/* G-02f-243：.x 门闩 null 边界；主体 🔒 pthread 解包 */
void * driver_large_stack_thread_trampoline(void *v) {
    DriverLargeStackCall *c;
    if (v == NULL)
        return NULL;
    c = (DriverLargeStackCall *)v;
    driver_large_stack_thread_mark(1);
    driver_bump_stack_limit();
    void *r = c->fn(c->arg);
    driver_large_stack_thread_mark(0);
    return r;
}

/**
 * Permanent OS indirect call surface.
 * PLATFORM: SHARED — invokes fn(arg) when fn != NULL.
 * Always present under FROM_X (thin pure orch calls this; no pure-dup call_fn _impl).
 * G.7: single authority for void*(void*) style driver callbacks (.x cannot cast safely).
 */
void xlang_driver_call_fn_void_arg(void *(*fn)(void *), void *arg) {
    if (fn)
        (void)fn(arg);
}

/* pure 权威：thin.x driver_pipeline_no_large_stack_env；冷启动保留 _impl + public；FROM_X 无 pure-dup（H↓）。 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_pipeline_no_large_stack_env_impl(void) {
    const char *e = link_abi_getenv("XLANG_PIPELINE_NO_LARGE_STACK");
    if (!e || !e[0] || e[0] == '0')
        return 0;
    return 1;
}

int32_t driver_pipeline_no_large_stack_env(void) {
  return driver_pipeline_no_large_stack_env_impl();
}
#endif

/** 在当前线程直接执行 fn(arg)，并临时标记大栈上下文。 */
/* G-02f-246 pure 深迁：PREFER thin 真体；冷启动 full C；FROM_X 无 pure-dup */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_run_fn_on_current_large_stack(void *(*fn)(void *), void *arg)
{
    if (fn == NULL)
        return;
    driver_large_stack_thread_mark(1);
    driver_bump_stack_limit();
    xlang_driver_call_fn_void_arg(fn, arg);
    driver_large_stack_thread_mark(0);
}
#endif

/**
 * Permanent OS large-stack pthread create/join surface.
 * PLATFORM: POSIX — pthread_attr / posix_memalign / pthread_create+join
 *            (hides OS layouts from .x pure orch); falls back to current-stack path.
 * Default stack 256MiB; XLANG_STACK_LIMIT_MB (64..8192) overrides.
 * Always present under FROM_X (thin driver_run_thread_on_large_stack pure orch calls this;
 * no pure-dup driver_run_thread_on_large_stack_pthread_impl).
 * G.7: single authority for driver large-stack pthread body used after pure early exits.
 */
void xlang_driver_run_thread_on_large_stack_pthread(void *(*fn)(void *), void *arg) {
    pthread_attr_t attr;
    pthread_t tid;
    void *stk = NULL;
    size_t stack_sz = (size_t)256 * 1024 * 1024;
    const char *mb_env = link_abi_getenv("XLANG_STACK_LIMIT_MB");
    DriverLargeStackCall call = { fn, arg };
    if (fn == NULL)
        return;
    if (mb_env && mb_env[0]) {
        unsigned long mb = strtoul(mb_env, NULL, 10);
        if (mb >= 64 && mb <= 8192)
            stack_sz = (size_t)mb * (size_t)(1024 * 1024);
    }
    if (pthread_attr_init(&attr) != 0) {
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    (void)pthread_attr_setguardsize(&attr, 0);
    if (posix_memalign(&stk, (size_t)65536, stack_sz) != 0)
        stk = NULL;
    if (stk != NULL && pthread_attr_setstack(&attr, stk, stack_sz) == 0) {
        if (pthread_create(&tid, &attr, driver_large_stack_thread_trampoline, &call) == 0) {
            pthread_join(tid, NULL);
            pthread_attr_destroy(&attr);
            free(stk);
            return;
        }
    }
    pthread_attr_destroy(&attr);
    free(stk);
    if (pthread_attr_init(&attr) != 0) {
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    if (pthread_attr_setstacksize(&attr, stack_sz) != 0) {
        pthread_attr_destroy(&attr);
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    if (pthread_create(&tid, &attr, driver_large_stack_thread_trampoline, &call) != 0) {
        pthread_attr_destroy(&attr);
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    pthread_join(tid, NULL);
    pthread_attr_destroy(&attr);
}

/**
 * Run fn(arg) on the 256MiB-stack pthread; pure early exits then the permanent
 * OS pthread surface (verbatim mirror of the thin wave12 orch body).
 * macOS main-thread RLIMIT_STACK caps around 8MiB; deep pipeline/typeck
 * recursion must share the large pipeline path.
 * G-02f-246/414 / wave12: public PREFER runs the thin pure orch; this cold twin
 * keeps the same early-exit order and the same OS surface.
 * 9.7.7 G.7: the former driver_run_thread_on_large_stack_impl middleman is
 * collapsed — this public twin now holds the orch body directly.
 * PLATFORM: SHARED orch; OS boundary only in xlang_driver_run_thread_on_large_stack_pthread.
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_run_thread_on_large_stack(void *(*fn)(void *), void *arg) {
    if (fn == NULL)
        return;
    if (driver_is_large_stack_thread()) {
        xlang_driver_call_fn_void_arg(fn, arg);
        return;
    }
    driver_bump_stack_limit();
    /*
     * NL-07 nostdlib: the bootstrap pthread stub runs synchronously on the
     * current stack, so a 256MiB posix_memalign stack would not take effect;
     * rely on driver_bump_stack_limit and run the pipeline on the current
     * thread to avoid a stack-overflow SIGSEGV.
     */
    if (bootstrap_nostdlib_pthread_is_stub()) {
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    if (driver_pipeline_no_large_stack_env()) {
        driver_run_fn_on_current_large_stack(fn, arg);
        return;
    }
    xlang_driver_run_thread_on_large_stack_pthread(fn, arg);
}
#endif

/**
 * Public alias: run fn(arg) on the large-stack pthread (LSP main loop etc.).
 * G-02f-414: body always seed; public PREFER uses the thin pure forward.
 * 9.7.7: mirrors the thin alias shape — null guard then direct call; the
 * former driver_run_on_large_stack_pthread_impl middleman is removed.
 * PLATFORM: SHARED orch.
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_run_on_large_stack_pthread(void *(*fn)(void *), void *arg) {
    if (fn == NULL)
        return;
    driver_run_thread_on_large_stack(fn, arg);
}
#endif

/**
 * Cap-fn-ptr residual：.x 无法形成函数指针常量。
 * wave37 pure：hybrid thin owns driver_run_stack_esc_gate_on_large_stack orch
 * （fn_ptr residual + G.7 driver_run_thread_on_large_stack）；cold twin under #ifndef FROM_X。
 * always-seed：driver_stack_esc_gate_thread_fn_ptr（取函数地址）。
 * PLATFORM: SHARED — Cap-fn-ptr residual stays seed.
 */
extern void *driver_stack_esc_gate_thread_fn(void *arg);

uint8_t *driver_stack_esc_gate_thread_fn_ptr(void) {
    return (uint8_t *)(void *)driver_stack_esc_gate_thread_fn;
}

#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_run_stack_esc_gate_on_large_stack(void *arg) {
    if (arg == NULL)
        return;
    driver_run_thread_on_large_stack(driver_stack_esc_gate_thread_fn, arg);
}
#endif

/**
 * Cap residual：opaque FILE* 供 rt_entry R2 full .x 的 diag_print_*。
 * wave39 pure：hybrid thin owns driver_stdio_stdout via fd-handle stdout_ptr；
 * wave40 pure：hybrid thin owns driver_stdio_stderr via fd-handle stderr_ptr；
 * cold twins under #ifndef FROM_X；FROM_X 无 pure-dup。
 * PLATFORM: SHARED — fd-handle face (9.7.1): encoded std fds, .x consumers
 * pass the value to the same opaque face, so identity/typing still holds.
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void *driver_stdio_stdout(void) {
    return (void *)xlang_driver_handle_from_fd(1);
}

void *driver_stdio_stderr(void) {
    return (void *)xlang_driver_handle_from_fd(2);
}
#endif

/**
 * Cap residual：rt_entry R2 缓冲槽 + fmt argv。
 * .x 禁局部 u8[N]（-E 抬 init_globals / 丢函数）；模块 BSS 可 pure（wave15 thin）。
 * wave15 pure：hybrid thin owns entry_*_slot (char buffers) + path slots。
 * wave21 pure：hybrid thin owns fmt_argv_slot (byte-lit BSS + G.7 ptr slots；no *u8[2] lit)。
 * cold keeps C static for buffers + fmt_argv; FROM_X no pure-dup buffer/fmt slots.
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static char driver_entry_ab[256];
static char driver_entry_code_buf[256];
static char driver_entry_suggest[16];
static char driver_entry_msg[256];
static char driver_entry_tmp[16];
static char driver_entry_tmp2[16];

uint8_t *driver_entry_ab_slot(void) {
    return (uint8_t *)driver_entry_ab;
}

uint8_t *driver_entry_code_slot(void) {
    return (uint8_t *)driver_entry_code_buf;
}

uint8_t *driver_entry_suggest_slot(void) {
    return (uint8_t *)driver_entry_suggest;
}

uint8_t *driver_entry_msg_slot(void) {
    return (uint8_t *)driver_entry_msg;
}

uint8_t *driver_entry_tmp_slot(void) {
    return (uint8_t *)driver_entry_tmp;
}

uint8_t *driver_entry_tmp2_slot(void) {
    return (uint8_t *)driver_entry_tmp2;
}

/* Cold only: fixed {"xlang","fmt"} argv for driver_run_fmt (wave21 pure under FROM_X). */
static char *driver_entry_fmt_argv[2] = {"xlang", "fmt"};

char **driver_entry_fmt_argv_slot(void) {
    return driver_entry_fmt_argv;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/**
 * Cap residual：rt_run_exec R2 usage 写 stdout。
 * wave44 pure：hybrid thin owns driver_print_usage_write orch
 *   （NO_COLOR nonnull / CLICOLOR_FORCE|XLANG_FORCE_COLOR truthy / isatty）；
 * cold twin under #ifndef FROM_X；FROM_X 无 pure-dup。
 * always-seed：xlang_driver_usage_write_stdout（巨型 plain/color lit，
 *   经 xlang_io_write(1,…) Cap io 写；9.7.1 起无 libc FILE star）。
 * PLATFORM: SHARED orch；lit 表权威唯一在 residual（G.7，禁 .x 长 \\n 串）。
 */

/* Permanent Cap residual: giant usage tables, written to fd 1 via
 * xlang_io_write (Cap io face, 9.7.1 fd-handle convergence).
 * Pure wave44 owns color policy only; .x -E cannot host multi-line \\n lits.
 * Always linked under FROM_X. PLATFORM: SHARED — Cap io write, raw fd 1. */
void xlang_driver_usage_write_stdout(int32_t use_color) {
    /* Deno-style help layout: yellow section headers, blue subcommand names,
     * yellow flags, two-column alignment with description column. */
static const char usage_plain[] =
    "Xlang compiler\n"
    "\n"
    "Usage: xlang [COMMAND] [OPTIONS]\n"
    "\n"
    "Subcommands:\n"
    "\n"
    "  build\n"
    "    Compile .x to binary/object (default a.out)\n"
    "    Usage: xlang build [options] file.x [-o exe]\n"
    "    Options:\n"
    "      -backend asm|c                    Backend (default asm)\n"
    "      -O <0|1|2|3|s>                    Optimization level (default 2)\n"
    "      -o <path>                         Output binary or .o\n"
    "      -L <dir>                          Library search path\n"
    "      -target <triple>                  Target triple (e.g. aarch64-linux-gnu)\n"
    "      -target-cpu <cpu>                 native|generic|avx2|...\n"
    "      -freestanding                     Nostdlib static link (Linux x86_64 ELF)\n"
    "      -legacy-f32-abi                   Legacy SysV f32 CALL (f64 widen; default xmm ABI)\n"
    "      -E                                Emit C (debug)\n"
    "      -flto                             Link-time optimization (C backend)\n"
    "\n"
    "  run\n"
    "    Compile and run .x\n"
    "    Usage: xlang run [options] file.x\n"
    "    Options:\n"
    "      -backend asm|c                    Backend (default asm)\n"
    "      -O <0|1|2|3|s>                    Optimization level (default 2)\n"
    "      -o <path>                         Output binary or .o\n"
    "      -L <dir>                          Library search path\n"
    "      -target <triple>                  Target triple (e.g. aarch64-linux-gnu)\n"
    "      -target-cpu <cpu>                 native|generic|avx2|...\n"
    "      -legacy-f32-abi                   Legacy SysV f32 CALL (f64 widen; default xmm ABI)\n"
    "\n"
    "  check\n"
    "    Parse + typeck only (no codegen)\n"
    "    Usage: xlang check [paths...]\n"
    "\n"
    "  fmt\n"
    "    Format .x sources\n"
    "    Usage: xlang fmt [--check] [paths...]\n"
    "\n"
    "  explain\n"
    "    Explain a diagnostic code\n"
    "    Usage: xlang explain <CODE>\n"
    "\n"
    "  test\n"
    "    Run test script\n"
    "    Usage: xlang test [script.sh]\n"
    "\n"
    "Global options:\n"
    "  --print-target-cpu                    Print host CPU features and exit\n"
    "  --explain <CODE>                      Print diagnostic code explanation and exit\n"
    "  --help, -h                            Show this help\n"
    "\n"
    "Environment:\n"
    "  XLANG_ABI_F32_XMM=0                    Same as -legacy-f32-abi (x86_64 SysV)\n"
    "  XLANG_OPT                              Default -O level if omitted\n"
    "  NO_COLOR                              Disable color output\n"
    "  CLICOLOR_FORCE=1                      Force color output even when piped\n"
    "  XLANG_FORCE_COLOR=1                    Same as CLICOLOR_FORCE\n"
    "\n"
    "Release default: xlang_asm -backend asm -O2 (f32 xmm ABI on unless legacy).\n"
    "See compiler/docs/F32_XMM_ABI.md for f32 ABI and deprecation timeline.\n";
static const char usage_color[] =
    "\033[32mXlang compiler\033[0m\n"
    "\n"
    "\033[32mUsage:\033[0m xlang [COMMAND] [OPTIONS]\n"
    "\n"
    "\033[32mSubcommands:\033[0m\n"
    "\n"
    "  \033[34mbuild\033[0m\n"
    "    Compile .x to binary/object (default a.out)\n"
    "    Usage: xlang build [options] file.x [-o exe]\n"
    "    Options:\n"
    "      \033[32m-backend\033[0m asm|c                    Backend \033[90m(default asm)\033[0m\n"
    "      \033[32m-O\033[0m <0|1|2|3|s>                    Optimization level \033[90m(default 2)\033[0m\n"
    "      \033[32m-o\033[0m <path>                         Output binary or .o\n"
    "      \033[32m-L\033[0m <dir>                          Library search path\n"
    "      \033[32m-target\033[0m <triple>                  Target triple (e.g. aarch64-linux-gnu)\n"
    "      \033[32m-target-cpu\033[0m <cpu>                 native|generic|avx2|...\n"
    "      \033[32m-freestanding\033[0m                     Nostdlib static link (Linux x86_64 ELF)\n"
    "      \033[32m-legacy-f32-abi\033[0m                   Legacy SysV f32 CALL (f64 widen; default xmm ABI)\n"
    "      \033[32m-E\033[0m                                Emit C (debug)\n"
    "      \033[32m-flto\033[0m                             Link-time optimization (C backend)\n"
    "\n"
    "  \033[34mrun\033[0m\n"
    "    Compile and run .x\n"
    "    Usage: xlang run [options] file.x\n"
    "    Options:\n"
    "      \033[32m-backend\033[0m asm|c                    Backend \033[90m(default asm)\033[0m\n"
    "      \033[32m-O\033[0m <0|1|2|3|s>                    Optimization level \033[90m(default 2)\033[0m\n"
    "      \033[32m-o\033[0m <path>                         Output binary or .o\n"
    "      \033[32m-L\033[0m <dir>                          Library search path\n"
    "      \033[32m-target\033[0m <triple>                  Target triple (e.g. aarch64-linux-gnu)\n"
    "      \033[32m-target-cpu\033[0m <cpu>                 native|generic|avx2|...\n"
    "      \033[32m-legacy-f32-abi\033[0m                   Legacy SysV f32 CALL (f64 widen; default xmm ABI)\n"
    "\n"
    "  \033[34mcheck\033[0m\n"
    "    Parse + typeck only (no codegen)\n"
    "    Usage: xlang check [paths...]\n"
    "\n"
    "  \033[34mfmt\033[0m\n"
    "    Format .x sources\n"
    "    Usage: xlang fmt [--check] [paths...]\n"
    "\n"
    "  \033[34mexplain\033[0m\n"
    "    Explain a diagnostic code\n"
    "    Usage: xlang explain <CODE>\n"
    "\n"
    "  \033[34mtest\033[0m\n"
    "    Run test script\n"
    "    Usage: xlang test [script.sh]\n"
    "\n"
    "\033[32mGlobal options:\033[0m\n"
    "  \033[32m--print-target-cpu\033[0m                    Print host CPU features and exit\n"
    "  \033[32m--explain\033[0m <CODE>                      Print diagnostic code explanation and exit\n"
    "  \033[32m--help, -h\033[0m                            Show this help\n"
    "\n"
    "\033[32mEnvironment:\033[0m\n"
    "  XLANG_ABI_F32_XMM=0                    Same as -legacy-f32-abi (x86_64 SysV)\n"
    "  XLANG_OPT                              Default -O level if omitted\n"
    "  NO_COLOR                              Disable color output\n"
    "  CLICOLOR_FORCE=1                      Force color output even when piped\n"
    "  XLANG_FORCE_COLOR=1                    Same as CLICOLOR_FORCE\n"
    "\n"
    "Release default: xlang_asm -backend asm -O2 (f32 xmm ABI on unless legacy).\n"
    "See \033[4;34mcompiler/docs/F32_XMM_ABI.md\033[0m for f32 ABI and deprecation timeline.\n";
    if (use_color) {
        (void)xlang_io_write(1, usage_color, sizeof(usage_color) - 1u);
    } else {
        (void)xlang_io_write(1, usage_plain, sizeof(usage_plain) - 1u);
    }
}

/* wave44 pure: hybrid thin owns print_usage color orch; cold twin under #ifndef FROM_X. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_print_usage_write(void) {
    /* §13 Color policy (see analysis/XLANG 命令行.md §13):
     *   NO_COLOR (any value, even empty)         -> no color  (https://no-color.org)
     *   CLICOLOR_FORCE / XLANG_FORCE_COLOR truthy -> force color even when piped
     *   otherwise                                -> isatty(STDOUT_FILENO)
     * Forward-declare isatty to avoid pulling <unistd.h> into this TU
     * (prior note: hand-written extern write + #include <unistd.h> trips Darwin asm). */
    extern int isatty(int fd);
    const char *no_color = link_abi_getenv("NO_COLOR");
    const char *force = link_abi_getenv("CLICOLOR_FORCE");
    const char *xlang_force = link_abi_getenv("XLANG_FORCE_COLOR");
    int use_color;
    if (no_color != (const char *)0) {
        use_color = 0;
    } else if ((force != (const char *)0 && force[0] != 0 && force[0] != '0') ||
               (xlang_force != (const char *)0 && xlang_force[0] != 0 && xlang_force[0] != '0')) {
        use_color = 1;
    } else {
        use_color = isatty(1);
    }
    xlang_driver_usage_write_stdout(use_color);
}
#endif

/**
 * Cap residual：rt_run_exec R2 driver_exec_compiled 体。
 * wave42 pure：hybrid thin owns driver_exec_compiled_body orch
 *   （null/argc + G.7 driver_exec_path_is_non_exe + residual scan/spawn）；
 * cold twin under #ifndef FROM_X；FROM_X 无 pure-dup。
 * always-seed：xlang_driver_exec_scan_out_path_opaque（*u8→char** cast + scan）
 *   + xlang_driver_exec_spawn_wait（fork/exec 或 spawnvp）。
 * PLATFORM: SHARED orch；WINDOWS spawn vs POSIX fork in residual.
 */
#if !defined(_WIN32) && !defined(_WIN64)
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif
extern void runtime_diag_errno_path(const char *file, const char *kind, const char *op, const char *path);
extern const char *driver_exec_scan_out_path(int argc, char **argv);
extern int driver_exec_path_is_non_exe(const char *exe);
#if !defined(_WIN32) && !defined(_WIN64)
extern int xlang_waitpid_retry(pid_t pid, int *status_out);
#endif

/* Permanent Cap residual: *u8 argv_opaque → char** + G.7 scan_out_path.
 * Pure wave42 cannot cast *u8→**u8 (-E drops body). Always linked under FROM_X.
 * PLATFORM: SHARED — cast glue only; scan authority remains rt_run_exec. */
uint8_t *xlang_driver_exec_scan_out_path_opaque(int32_t argc, uint8_t *argv_opaque) {
    if (argv_opaque == NULL)
        return NULL;
    return (uint8_t *)(void *)driver_exec_scan_out_path(argc, (char **)(void *)argv_opaque);
}

/* Permanent OS residual: wait for product exe (spawn/fork/exec).
 * Pure wave42 owns null/non_exe orch; this is process boundary only.
 * PLATFORM: WINDOWS _spawnvp; POSIX fork+execv+xlang_waitpid_retry. */
int32_t xlang_driver_exec_spawn_wait(uint8_t *exe) {
    const char *path;
    if (exe == NULL)
        return 1;
    path = (const char *)(void *)exe;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    {
        char *av[2];
        intptr_t rc;
        av[0] = (char *)path;
        av[1] = NULL;
        rc = _spawnvp(_P_WAIT, path, (const char *const *)av);
        if (rc == -1) {
            runtime_diag_errno_path(NULL, "process error", "spawnvp (driver_exec_compiled)", path);
            return 1;
        }
        return (int32_t)rc;
    }
#else
    {
        pid_t pid = fork();
        if (pid < 0) {
            runtime_diag_errno_path(NULL, "process error", "fork (driver_exec_compiled)", path);
            return 1;
        }
        if (pid == 0) {
            char *av[2];
            av[0] = (char *)path;
            av[1] = NULL;
            execv(path, av);
            runtime_diag_errno_path(NULL, "process error", "execv (driver_exec_compiled)", path);
            _exit(127);
        }
        {
            int st = 0;
            if (xlang_waitpid_retry(pid, &st) != 0)
                return 1;
            if (WIFEXITED(st))
                return (int32_t)WEXITSTATUS(st);
            return 1;
        }
    }
#endif
}

/* wave42 pure: hybrid thin owns exec_compiled_body orch; cold twin under #ifndef FROM_X. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_exec_compiled_body(int argc, uint8_t *argv_opaque) {
    char **argv = (char **)argv_opaque;
    const char *exe;
    if (!argv || argc < 1)
        return 1;
    exe = driver_exec_scan_out_path(argc, argv);
    if (driver_exec_path_is_non_exe(exe))
        return 0;
    return (int)xlang_driver_exec_spawn_wait((uint8_t *)(void *)exe);
}
#endif

/**
 * Cap-global-bss residual：rt_emit_state R2 full .x 写共享 emit 槽。
 * 数据定义在 seeds/rt_emit_state.from_x.c（跨 TU 非 static）；本层暴露槽/绑定。
 * Always-seed Cap-global-bss data residual（path/lib/scan slots + c_path_cell +
 * lib_roots_raw + n/want slots）：不随 RDABI thin 宏剥离。
 * wave33 pure：clear/bind/take/get/lib_root_at/effective/try_extern 在 thin.x
 *   （G.7 xlang_ptr_slot_* on c_path_cell/lib_roots_raw；无 **u8 写）；
 *   cold keeps C twins under #ifndef FROM_X；FROM_X 无 pure-dup。
 * PLATFORM: SHARED — BSS authority remains rt_emit_state.from_x.c.
 */
#define X_EMIT_MAX_LIB_ROOTS_ABI 16
extern const char *driver_x_emit_c_path;
extern const char *driver_x_emit_lib_roots[X_EMIT_MAX_LIB_ROOTS_ABI];
extern int driver_x_emit_n_lib_roots;
extern char driver_x_emit_path_buf[512];
extern char driver_x_emit_lib_bufs[X_EMIT_MAX_LIB_ROOTS_ABI][256];
extern int driver_x_emit_c_want_extern;
/* argv 扫描临时缓冲（.x 勿用局部 u8[512]，易被抬成坏 init_globals） */
extern char driver_x_emit_scan_ab[512];
extern char driver_x_emit_scan_nx[512];

/* Always-seed: Cap-global-bss buffer bases (data in rt_emit_state.from_x.c). */
uint8_t *driver_x_emit_path_buf_slot(void) {
    return (uint8_t *)driver_x_emit_path_buf;
}

uint8_t *driver_x_emit_lib_buf_slot(int i) {
    if (i < 0 || i >= X_EMIT_MAX_LIB_ROOTS_ABI)
        return NULL;
    return (uint8_t *)driver_x_emit_lib_bufs[i];
}

uint8_t *driver_x_emit_scan_ab_slot(void) {
    return (uint8_t *)driver_x_emit_scan_ab;
}

uint8_t *driver_x_emit_scan_nx_slot(void) {
    return (uint8_t *)driver_x_emit_scan_nx;
}

/* Always-seed: address of driver_x_emit_c_path pointer cell (1-slot G.7 table). */
uint8_t *driver_x_emit_c_path_cell(void) {
    return (uint8_t *)(void *)&driver_x_emit_c_path;
}

/* Always-seed: base of driver_x_emit_lib_roots[16] pointer table. */
uint8_t *driver_x_emit_lib_roots_raw(void) {
    return (uint8_t *)(void *)driver_x_emit_lib_roots;
}

int32_t *driver_x_emit_n_lib_roots_slot(void) {
    return (int32_t *)&driver_x_emit_n_lib_roots;
}

int32_t *driver_x_emit_want_extern_slot(void) {
    return (int32_t *)&driver_x_emit_c_want_extern;
}

/* wave33 pure: hybrid thin owns clear/bind; cold seed keeps C twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_x_emit_clear_c_path(void) {
    driver_x_emit_c_path = NULL;
}

void driver_x_emit_bind_c_path_to_buf(void) {
    driver_x_emit_c_path = driver_x_emit_path_buf;
}

void driver_x_emit_bind_lib_root(int i) {
    if (i < 0 || i >= X_EMIT_MAX_LIB_ROOTS_ABI)
        return;
    driver_x_emit_lib_roots[i] = driver_x_emit_lib_bufs[i];
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/**
 * Cap-global-bss residual：rt_arena_buf R2 full .x 访问 128MiB/2MiB 静态缓冲。
 * 数据定义在 seeds/rt_arena_buf.from_x.c（跨 TU 非 static）。
 * wave37 pure：hybrid thin owns slot/size；always-seed base residual 供 pure 取址；
 * cold keeps C slot/size twins under #ifndef FROM_X。
 * PLATFORM: SHARED — array body stays rt_arena_buf; pure owns public slot/size API under PREFER.
 */
#define DRIVER_ARENA_STATIC_SIZE_ABI (128 * 1024 * 1024)
#define DRIVER_MODULE_STATIC_SIZE_ABI (2 * 1024 * 1024)
extern uint8_t driver_arena_static[DRIVER_ARENA_STATIC_SIZE_ABI];
extern uint8_t driver_module_static[DRIVER_MODULE_STATIC_SIZE_ABI];

/* Always-seed Cap-global base residual (like preamble_*_lines_raw). */
uint8_t *driver_arena_static_base(void) {
    return driver_arena_static;
}

uint8_t *driver_module_static_base(void) {
    return driver_module_static;
}

#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_arena_static_slot(void) {
    return driver_arena_static;
}

uint8_t *driver_module_static_slot(void) {
    return driver_module_static;
}

size_t driver_arena_static_size(void) {
    return (size_t)DRIVER_ARENA_STATIC_SIZE_ABI;
}

size_t driver_module_static_size(void) {
    return (size_t)DRIVER_MODULE_STATIC_SIZE_ABI;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/**
 * Cap-giant-string residual：rt_preamble R2 full .x 访问巨型 C 字串表。
 * 数据定义在 seeds/rt_preamble.from_x.c（跨 TU 非 static）。
 * wave20 pure：hybrid thin owns line_at/count（xlang_ptr_slot_get + fixed N）；
 *   always-seed residual = *_lines_raw（表基址）；cold keeps C line_at/count twins；
 *   FROM_X 无 pure-dup line_at/count。
 * PLATFORM: SHARED — table text authority remains rt_preamble.from_x.c.
 */
extern const char *const driver_preamble_io_net_lines[];
extern const int32_t driver_preamble_io_net_lines_n;
extern const char *const driver_preamble_fs_path_lines[];
extern const int32_t driver_preamble_fs_path_lines_n;

/* Always seed: Cap-giant-string data residual (base of pointer table for pure line_at). */
uint8_t *driver_preamble_io_net_lines_raw(void) {
    return (uint8_t *)(void *)driver_preamble_io_net_lines;
}

uint8_t *driver_preamble_fs_path_lines_raw(void) {
    return (uint8_t *)(void *)driver_preamble_fs_path_lines;
}

#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_preamble_io_net_line_at(int32_t i) {
    if (i < 0 || i >= driver_preamble_io_net_lines_n)
        return NULL;
    return (uint8_t *)(uintptr_t)driver_preamble_io_net_lines[i];
}

int32_t driver_preamble_io_net_line_count(void) {
    return driver_preamble_io_net_lines_n;
}

uint8_t *driver_preamble_fs_path_line_at(int32_t i) {
    if (i < 0 || i >= driver_preamble_fs_path_lines_n)
        return NULL;
    return (uint8_t *)(uintptr_t)driver_preamble_fs_path_lines[i];
}

int32_t driver_preamble_fs_path_line_count(void) {
    return driver_preamble_fs_path_lines_n;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

#ifndef XLANG_L2_RDABI_THIN_FROM_X
/** Cap residual G.7 authority cold twin：opaque *u8 stream → fd-handle write（error → 负值）。
 * Shared by rt_preamble + async_liveness/async_cps emit pure (.x). No module-local clones.
 * Wave22 pure owns this under PREFER hybrid (thin.x + fd-handle fputs_opaque).
 * PLATFORM: SHARED — single stream-write bridge for product cold seed (9.7.1). */
int32_t driver_preamble_fputs(uint8_t *s, uint8_t *stream) {
    int fd;
    if (s == NULL || stream == NULL)
        return -1;
    fd = xlang_driver_handle_to_fd(stream);
    if (fd < 0)
        return -1;
    return (int32_t)xlang_io_write(fd, s, strlen((const char *)(void *)s));
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* ---------- Cap residual：rt_run_x_emit R2（平台/巨型布局） ---------- */
#ifndef X_CODEGEN_OUTBUF_CAP_ABI
#define X_CODEGEN_OUTBUF_CAP_ABI (9 * 1024 * 1024)
#endif
struct driver_codegen_outbuf_abi {
    unsigned char data[X_CODEGEN_OUTBUF_CAP_ABI];
    int32_t length;
};

extern const char *driver_x_emit_c_path;
extern const char *driver_x_emit_lib_roots[];
extern int driver_x_emit_n_lib_roots;
extern int driver_x_emit_c_want_extern;
/* wave77: G.7 accessors only — pure owns typeck_dep BSS under hybrid; no naked C globals. */
extern void typeck_ndep_store(int32_t n);
extern void typeck_dep_module_set(int32_t i, void *mod);
extern void typeck_dep_arena_set(int32_t i, void *arena);

struct parser_ParseIntoResult {
    int32_t ok;
    int32_t main_idx;
};
extern struct parser_ParseIntoResult parser_parse_into_buf(void *arena, void *module, uint8_t *data,
                                                          int32_t len);

/* wave33 pure: hybrid thin owns take/get/lib_root_at; cold seed keeps C twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_x_emit_take_c_path(void) {
    const char *p = driver_x_emit_c_path;
    driver_x_emit_c_path = NULL;
    return (uint8_t *)(void *)p;
}

int32_t driver_x_emit_take_want_extern(void) {
    int32_t w = (int32_t)driver_x_emit_c_want_extern;
    driver_x_emit_c_want_extern = 0;
    return w;
}

int32_t driver_x_emit_n_lib_roots_get(void) {
    return (int32_t)driver_x_emit_n_lib_roots;
}

uint8_t *driver_x_emit_lib_root_at(int32_t i) {
    if (i < 0 || i >= driver_x_emit_n_lib_roots)
        return NULL;
    return (uint8_t *)(void *)driver_x_emit_lib_roots[i];
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* 9.7.1: stdout writes go through raw fd 1 (unbuffered by nature) — kept as a
 * no-op for .x callers that used to disable libc FILE buffering. */
void driver_x_emit_stdout_set_unbuffered(void) {
}

/**
 * Cap OS residual for wave39 pure driver_x_emit_fwrite_stdout.
 * Pure owns null/len guards; this returns write byte count (fd 1 is unbuffered).
 * Always linked under FROM_X (no pure-dup of public symbol).
 * PLATFORM: SHARED — fd-handle face; raw write(1) via Cap authority (9.7.1).
 */
int32_t xlang_driver_fwrite_stdout_n(uint8_t *data, int32_t len) {
    if (data == NULL || len <= 0)
        return 0;
    return (int32_t)xlang_io_write(1, data, (size_t)len);
}

/* wave39 pure: hybrid thin owns fwrite_stdout; cold twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_x_emit_fwrite_stdout(uint8_t *data, int32_t len) {
    return xlang_driver_fwrite_stdout_n(data, len);
}
#endif

/* wave23 pure：hybrid thin owns calloc family; cold seed keeps sizeof twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void *driver_codegen_outbuf_calloc(void) {
    return calloc(1, sizeof(struct driver_codegen_outbuf_abi));
}
#endif

/* wave24 pure：hybrid thin owns free/len/data; cold seed keeps twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_codegen_outbuf_free(void *p) {
    free(p);
}

int32_t driver_codegen_outbuf_len(void *p) {
    if (p == NULL)
        return 0;
    return ((struct driver_codegen_outbuf_abi *)p)->length;
}

uint8_t *driver_codegen_outbuf_data(void *p) {
    if (p == NULL)
        return NULL;
    return ((struct driver_codegen_outbuf_abi *)p)->data;
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
void *driver_pipeline_dep_ctx_calloc(void) {
    return calloc(1, sizeof(struct ast_PipelineDepCtx));
}

void *driver_ptr_table_calloc(int32_t n) {
    if (n <= 0)
        return NULL;
    return calloc((size_t)n, sizeof(void *));
}
#endif

/* wave24 pure：hybrid thin owns free/get/set; cold seed keeps twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_ptr_table_free(void *t) {
    free(t);
}

void *driver_ptr_table_get(void *t, int32_t i) {
    if (t == NULL || i < 0)
        return NULL;
    return ((void **)t)[i];
}

void driver_ptr_table_set(void *t, int32_t i, void *p) {
    if (t == NULL || i < 0)
        return;
    ((void **)t)[i] = p;
}
#endif

#ifndef XLANG_L2_RDABI_THIN_FROM_X
void *driver_size_table_calloc(int32_t n) {
    if (n <= 0)
        return NULL;
    return calloc((size_t)n, sizeof(size_t));
}

void driver_size_table_free(void *t) {
    free(t);
}

size_t driver_size_table_get(void *t, int32_t i) {
    if (t == NULL || i < 0)
        return 0;
    return ((size_t *)t)[i];
}

void driver_size_table_set(void *t, int32_t i, size_t v) {
    if (t == NULL || i < 0)
        return;
    ((size_t *)t)[i] = v;
}
#endif

/**
 * Cap-struct-return residual：unpack parser_parse_into_buf into rc + out_main_idx.
 * Always-seed (not stripped by FROM_X). Wave38 pure driver_parse_into_buf_rc owns
 * null guards then calls this. PLATFORM: SHARED — struct return stays C.
 *
 * wave269: always-seed also owns L001 sticky hard-fail (reset before parse, pending
 * after). wave271: same for L002 unclosed string. wave272: same for L003 illegal char.
 * wave273: same for L004 incomplete hex.
 * wave274: same for L005 incomplete float exponent.
 * Thin driver_parse_into_buf_rc may also check; this residual is the G.7 single choke
 * that hybrid and cold both pass through.
 */
extern void lexer_unclosed_block_comment_reset(void);
extern int32_t lexer_unclosed_block_comment_pending(void);
extern void lexer_unclosed_string_reset(void);
extern int32_t lexer_unclosed_string_pending(void);
extern void lexer_illegal_char_reset(void);
extern int32_t lexer_illegal_char_pending(void);
extern void lexer_incomplete_hex_reset(void);
extern int32_t lexer_incomplete_hex_pending(void);
extern void lexer_incomplete_exp_reset(void);
extern int32_t lexer_incomplete_exp_pending(void);
extern void lexer_incomplete_bin_reset(void);
extern int32_t lexer_incomplete_bin_pending(void);
extern void lexer_incomplete_oct_reset(void);
extern void lexer_invalid_digit_sep_reset(void);
extern int32_t lexer_invalid_digit_sep_pending(void);
extern void lexer_invalid_type_suffix_reset(void);
extern int32_t lexer_invalid_type_suffix_pending(void);
extern int32_t lexer_incomplete_oct_pending(void);
int32_t xlang_parser_parse_into_buf_rc(void *arena, void *module, uint8_t *data, int32_t len,
                                      int32_t *out_main_idx) {
    struct parser_ParseIntoResult pr;
    lexer_unclosed_block_comment_reset();
    lexer_unclosed_string_reset();
    lexer_illegal_char_reset();
    lexer_incomplete_hex_reset();
    lexer_incomplete_exp_reset();
    lexer_incomplete_bin_reset();
    lexer_incomplete_oct_reset();
    lexer_invalid_digit_sep_reset();
    lexer_invalid_type_suffix_reset();
    pr = parser_parse_into_buf(arena, module, data, len);
    if (lexer_unclosed_block_comment_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_unclosed_string_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_illegal_char_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_hex_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_exp_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_bin_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_oct_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_invalid_digit_sep_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_invalid_type_suffix_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (out_main_idx)
        *out_main_idx = pr.main_idx;
    return pr.ok;
}

/* wave38 pure: hybrid thin owns parse_into_buf_rc orch; cold keeps twin with guards.
 * wave269: reset + hard-fail on unclosed block comment (L001 sticky pending).
 * wave271: reset + hard-fail on unclosed string (L002 sticky pending).
 * wave272: reset + hard-fail on illegal character (L003 sticky pending).
 * wave273: reset + hard-fail on incomplete hex (L004 sticky pending).
 * wave274: reset + hard-fail on incomplete float exponent (L005 sticky pending). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
extern void lexer_unclosed_block_comment_reset(void);
extern int32_t lexer_unclosed_block_comment_pending(void);
extern void lexer_unclosed_string_reset(void);
extern int32_t lexer_unclosed_string_pending(void);
extern void lexer_illegal_char_reset(void);
extern int32_t lexer_illegal_char_pending(void);
extern void lexer_incomplete_hex_reset(void);
extern int32_t lexer_incomplete_hex_pending(void);
extern void lexer_incomplete_exp_reset(void);
extern int32_t lexer_incomplete_exp_pending(void);
extern void lexer_incomplete_bin_reset(void);
extern int32_t lexer_incomplete_bin_pending(void);
extern void lexer_incomplete_oct_reset(void);
extern void lexer_invalid_digit_sep_reset(void);
extern int32_t lexer_invalid_digit_sep_pending(void);
extern void lexer_invalid_type_suffix_reset(void);
extern int32_t lexer_invalid_type_suffix_pending(void);
extern int32_t lexer_incomplete_oct_pending(void);
int32_t driver_parse_into_buf_rc(void *arena, void *module, uint8_t *data, int32_t len,
                                 int32_t *out_main_idx) {
    int32_t rc;
    if (out_main_idx)
        *out_main_idx = -1;
    if (!arena || !module || !data)
        return -1;
    lexer_unclosed_block_comment_reset();
    lexer_unclosed_string_reset();
    lexer_illegal_char_reset();
    lexer_incomplete_hex_reset();
    lexer_incomplete_exp_reset();
    lexer_incomplete_bin_reset();
    lexer_incomplete_oct_reset();
    lexer_invalid_digit_sep_reset();
    lexer_invalid_type_suffix_reset();
    rc = xlang_parser_parse_into_buf_rc(arena, module, data, len, out_main_idx);
    if (lexer_unclosed_block_comment_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_unclosed_string_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_illegal_char_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_hex_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_exp_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_bin_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_incomplete_oct_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_invalid_digit_sep_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    if (lexer_invalid_type_suffix_pending() != 0) {
        if (out_main_idx)
            *out_main_idx = -1;
        return -1;
    }
    return rc;
}
#endif

/* wave23 pure：hybrid thin owns diag snapshot alloc (fixed LP64 size 32). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void *driver_diag_snapshot_alloc(void) {
    return calloc(1, sizeof(DiagContextSnapshot));
}
#endif

/* wave24 pure：hybrid thin owns free; cold seed keeps twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_diag_snapshot_free(void *s) {
    free(s);
}
#endif

/* wave35 pure：hybrid thin owns push/restore + typeck set; cold seed keeps C twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_diag_push_file(void *snap, uint8_t *path, uint8_t *src, size_t len) {
    if (snap == NULL)
        return;
    diag_push_file((DiagContextSnapshot *)snap, (const char *)(void *)path,
                   (const char *)(void *)src, len);
}

void driver_diag_restore(void *snap) {
    if (snap == NULL)
        return;
    diag_restore((const DiagContextSnapshot *)snap);
}

void driver_typeck_ndep_set(int32_t n) {
    typeck_ndep_store((int32_t)((int)n));
}

void driver_typeck_dep_ptrs_set(int32_t j, void *mod, void *arena) {
    if (j < 0 || j >= 32)
        return;
    typeck_dep_module_set((int32_t)(j), mod);
    typeck_dep_arena_set((int32_t)(j), arena);
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave15 pure：hybrid thin owns path_max/entry_dir slots; cold keeps C static; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static char g_driver_path_max_slot[4096];
static char g_driver_entry_dir_slot[512];

uint8_t *driver_path_max_slot(void) {
    return (uint8_t *)g_driver_path_max_slot;
}

uint8_t *driver_entry_dir_slot(void) {
    return (uint8_t *)g_driver_entry_dir_slot;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave33 pure: hybrid thin owns effective_lib_roots; cold seed keeps C twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static const char *g_driver_x_emit_dot = ".";
static const char *g_driver_x_emit_one_root[1];

uint8_t *driver_x_emit_effective_lib_roots(int32_t *n_out) {
    if (driver_x_emit_n_lib_roots <= 0) {
        g_driver_x_emit_one_root[0] = g_driver_x_emit_dot;
        if (n_out)
            *n_out = 1;
        return (uint8_t *)(void *)g_driver_x_emit_one_root;
    }
    if (n_out)
        *n_out = (int32_t)driver_x_emit_n_lib_roots;
    return (uint8_t *)(void *)driver_x_emit_lib_roots;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

extern int32_t parser_diag_fail_at_token_kind(struct xlang_slice_uint8_t *source);

/* wave37 pure：hybrid thin owns pack + call; cold twin under #ifndef FROM_X. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_parser_diag_fail_tok_kind(uint8_t *src, size_t len) {
    struct xlang_slice_uint8_t s;
    if (src == NULL)
        return 0;
    s.data = src;
    s.length = len;
    return parser_diag_fail_at_token_kind(&s);
}
#endif

/* wave19 pure under PREFER：dep_ctx i32 field set/get; cold keeps C struct twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_pipeline_dep_ctx_set_use_asm(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->use_asm_backend = v;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/*
 * Cap residual → wave16 pure under PREFER：rt_run_x_emit 工作槽。
 * hybrid thin owns BSS + get/set/reset/cleanup；cold keeps C static + memset twin；
 * FROM_X no pure-dup (avoid dual BSS under hybrid).
 * 指针槽 i: 0 path 1 src 2 raw 3 arena 4 module 5 entry_dir 6 dep_sources
 *   7 dep_paths 8 dep_lens 9 dep_arenas 10 dep_modules 11 out_buf 12 pctx
 *   13 one_ctx 14 dep_out 15 dep_src 16 resolved 17 snap 18 dep_diag_file
 *   19 kind 20 code 21 msg 22 cpaths 23 out_data 24 lib_roots_as_u8 25 tmp_p
 * i32 槽 i: 0 want_extern 1 n_lib 2 n_deps 3 asm_direct 4 n_imports 5 main_idx
 *   6 pr_ok 7 ec 8 ec_dep 9 emit_ret 10 out_len 11 j 12 i 13 fail_tok
 *   14 n_closure 15 rc 16 free_src_flag
 * size_t 槽 i: 0 src_len 1 raw_len 2 arena_sz 3 module_sz 4 dep_len
 */
/* Always-seed decl before cold work cleanup (wave16/17/18); thin pure also links this. */
extern void pipeline_dep_ctx_heap_destroy(struct ast_PipelineDepCtx *ctx);

#ifndef XLANG_L2_RDABI_THIN_FROM_X
#define DRIVER_X_EMIT_WORK_NP 26
#define DRIVER_X_EMIT_WORK_NI 17
#define DRIVER_X_EMIT_WORK_NZ 5
static uint8_t *g_xe_work_p[DRIVER_X_EMIT_WORK_NP];
static int32_t g_xe_work_i[DRIVER_X_EMIT_WORK_NI];
static size_t g_xe_work_z[DRIVER_X_EMIT_WORK_NZ];

void driver_x_emit_work_reset(void) {
    memset(g_xe_work_p, 0, sizeof g_xe_work_p);
    memset(g_xe_work_i, 0, sizeof g_xe_work_i);
    memset(g_xe_work_z, 0, sizeof g_xe_work_z);
}

uint8_t *driver_x_emit_work_p_get(int32_t i) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NP)
        return NULL;
    return g_xe_work_p[i];
}

void driver_x_emit_work_p_set(int32_t i, uint8_t *v) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NP)
        return;
    g_xe_work_p[i] = v;
}

int32_t driver_x_emit_work_i_get(int32_t i) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NI)
        return 0;
    return g_xe_work_i[i];
}

void driver_x_emit_work_i_set(int32_t i, int32_t v) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NI)
        return;
    g_xe_work_i[i] = v;
}

size_t driver_x_emit_work_z_get(int32_t i) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NZ)
        return 0;
    return g_xe_work_z[i];
}

void driver_x_emit_work_z_set(int32_t i, size_t v) {
    if (i < 0 || i >= DRIVER_X_EMIT_WORK_NZ)
        return;
    g_xe_work_z[i] = v;
}

void driver_x_emit_work_cleanup(void) {
    int32_t n = g_xe_work_i[2]; /* ndeps */
    int32_t i;
    void *p;
    void *ds = g_xe_work_p[6];
    void *dp = g_xe_work_p[7];
    void *dl = g_xe_work_p[8];
    void *da = g_xe_work_p[9];
    void *dm = g_xe_work_p[10];
    for (i = 0; i < n; i++) {
        if (da) {
            p = ((void **)da)[i];
            free(p);
        }
        if (dm) {
            p = ((void **)dm)[i];
            free(p);
        }
        if (ds) {
            p = ((void **)ds)[i];
            free(p);
        }
        if (dp) {
            p = ((void **)dp)[i];
            free(p);
        }
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(g_xe_work_p[11]); /* out_buf */
    if (g_xe_work_p[12])
        pipeline_dep_ctx_heap_destroy((struct ast_PipelineDepCtx *)(void *)g_xe_work_p[12]);
    free(g_xe_work_p[3]);  /* arena */
    free(g_xe_work_p[4]);  /* module */
    free(g_xe_work_p[1]);  /* src */
    free(g_xe_work_p[19]); /* kind */
    free(g_xe_work_p[20]); /* code */
    free(g_xe_work_p[21]); /* msg */
    driver_x_emit_work_reset();
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave33 pure: hybrid thin owns try_extern NO_C diag stub; cold seed keeps C twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_x_emit_try_extern_via_cparser(uint8_t *input_path) {
    /*
     * 产品 runtime_driver_no_c 为 XLANG_NO_C_FRONTEND；driver_abi 本层不带该宏编译，
     * 故固定走 no-C 诊断（与产品 NO_C 语义一致）。
     * 冷启动全 C 体（seeds/rt_run_x_emit.from_x.c 无 FROM_X）仍可走 cparser 分支。
     */
    (void)input_path;
    diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001,
                          "-x -E -E-extern requires C parser/codegen (rebuild without -DXLANG_NO_C_FRONTEND)",
                          NULL);
    return 1;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/**
 * 扫描预处理后源码是否含顶层 import（`import("` 或 `= import(`）。
 * 参数：src 预处理后缓冲；src_len 有效字节数。
 * 返回值：1 含顶层 import；0 否。
 * G-02f-243/414：实现体始终 seed（memcmp 字面量）；public PREFER 时 thin pure forward。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_scan_top_level_import_impl(const char *src, size_t src_len) {
    const char *p;
    const char *end;
    if (src == NULL)
        return 0;
    if (src_len < 8)
        return 0;
    p = src;
    end = src + src_len;
    while (p + 8 <= end) {
        if (memcmp(p, "import(\"", 8) == 0)
            return 1;
        if (p + 9 <= end && memcmp(p, "= import(", 9) == 0)
            return 1;
        p++;
    }
    return 0;
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_scan_top_level_import(const char *src, size_t src_len) {
    return driver_source_scan_top_level_import_impl(src, src_len);
}
#endif

/* G-02f-243/414：实现体始终 seed；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_has_top_level_import_impl(const char *src, size_t src_len) {
    if (src == NULL) {
        return 0;
    }
    if (src_len < 9) {
        return 0;
    }
    return driver_source_scan_top_level_import_impl(src, src_len);
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_has_top_level_import(const char *src, size_t src_len) {
    return driver_source_has_top_level_import_impl(src, src_len);
}
#endif

/**
 * 读入口 .x 并预处理；返回 malloc 缓冲，长度经 driver_path_last_preprocess_len。
 * G-02f-244：IO 🔒；编排在 .x（scan pure + free）。
 * wave2：len BSS 权威 hybrid=thin / cold=seed static；本函数经 store 写入（禁直写 static）。
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static size_t g_driver_path_last_preprocess_len;

void driver_path_last_preprocess_len_store(int64_t len) {
    g_driver_path_last_preprocess_len = (size_t)len;
}

int64_t driver_path_last_preprocess_len_impl(void) {
    return (int64_t)g_driver_path_last_preprocess_len;
}

int64_t driver_path_last_preprocess_len(void) {
    return driver_path_last_preprocess_len_impl();
}
#endif

/**
 * Permanent OS path-read + preprocess surface.
 * PLATFORM: SHARED — runtime_read_file_view + xlang_preprocess + thin/cold len store API;
 *            hides XlangRuntimeFileView and preprocess ABI from .x pure orch.
 * Always present under FROM_X (thin driver_path_read_preprocess_malloc pure orch calls this;
 * no pure-dup driver_path_read_preprocess_malloc_impl).
 * G.7: single authority for entry-path read+preprocess used by has_top_level_import_path.
 */
char *xlang_driver_path_read_preprocess_malloc(const char *path) {
    XlangRuntimeFileView raw_view;
    size_t src_len = 0;
    char *src;

    /* PLATFORM: SHARED — always write len via store API (thin BSS under FROM_X). */
    driver_path_last_preprocess_len_store(0);
    if (!path)
        return NULL;
    if (runtime_read_file_view(path, &raw_view) != 0)
        return NULL;
    src = xlang_preprocess(raw_view.data, raw_view.length, NULL, 0, &src_len);
    runtime_release_file_view(&raw_view);
    if (!src)
        return NULL;
    driver_path_last_preprocess_len_store((int64_t)src_len);
    return src;
}

/* G-02f-244/414：冷启动 public twin；PREFER/FROM_X 时 thin owns public pure orch */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
char *driver_path_read_preprocess_malloc(const char *path) {
    return xlang_driver_path_read_preprocess_malloc(path);
}
#endif

/* G-02f-244/414：实现体始终 seed（IO/preprocess）；public PREFER 时 thin pure forward */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_has_top_level_import_path_impl(const char *path) {
    char *src;
    int has;
    int64_t len;

    if (path == NULL)
        return 0;
    src = driver_path_read_preprocess_malloc(path);
    if (!src)
        return 0;
    len = driver_path_last_preprocess_len();
    has = driver_source_has_top_level_import_impl(src, (size_t)len);
    free(src);
    return has;
}
#endif
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int driver_source_has_top_level_import_path(const char *path) {
    return driver_source_has_top_level_import_path_impl(path);
}
#endif

/* --------------------------------------------------------------------------
 * Cap residual：rt_run_asm_backend R2（FILE* / pctx 字段 / host #ifdef / **u8 / work 槽）
 * -------------------------------------------------------------------------- */

/* wave19 pure under PREFER：asm-path dep_ctx field set/get; cold C twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_pipeline_dep_ctx_set_target_arch(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->target_arch = v;
}

void driver_pipeline_dep_ctx_set_target_cpu_features(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->target_cpu_features = v;
}

void driver_pipeline_dep_ctx_set_use_macho_o(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->use_macho_o = v;
}

void driver_pipeline_dep_ctx_set_use_coff_o(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->use_coff_o = v;
}

void driver_pipeline_dep_ctx_set_entry_already_parsed(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->entry_already_parsed = v;
}

void driver_pipeline_dep_ctx_set_asm_entry_module_only(void *ctx, int32_t v) {
    if (ctx == NULL)
        return;
    ((struct ast_PipelineDepCtx *)ctx)->asm_entry_module_only = v;
}

int32_t driver_pipeline_dep_ctx_get_asm_entry_module_only(void *ctx) {
    if (ctx == NULL)
        return 0;
    return ((struct ast_PipelineDepCtx *)ctx)->asm_entry_module_only;
}

int32_t driver_pipeline_dep_ctx_get_use_macho_o(void *ctx) {
    if (ctx == NULL)
        return 0;
    return ((struct ast_PipelineDepCtx *)ctx)->use_macho_o;
}

int32_t driver_pipeline_dep_ctx_get_use_coff_o(void *ctx) {
    if (ctx == NULL)
        return 0;
    return ((struct ast_PipelineDepCtx *)ctx)->use_coff_o;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

extern uint32_t driver_get_pending_target_cpu_features(void);

/*
 * wave23 permanent OS residual for pure host_defaults orch (always linked under FROM_X).
 * PLATFORM: MACOS — default arch / macho prefer; WINDOWS — coff prefer; else 0.
 * G.7: thin.x owns product orchestration; these helpers only hide host #ifdef.
 */
int32_t xlang_driver_host_default_target_arch(void) {
#if defined(__APPLE__) && defined(__aarch64__)
    return 1;
#else
    return 0;
#endif
}

int32_t xlang_driver_host_prefer_macho(int32_t emit_elf_o) {
#if defined(__APPLE__)
    return emit_elf_o ? 1 : 0;
#else
    (void)emit_elf_o;
    return 0;
#endif
}

int32_t xlang_driver_host_prefer_coff(int32_t emit_elf_o) {
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    return emit_elf_o ? 1 : 0;
#else
    (void)emit_elf_o;
    return 0;
#endif
}

/* wave23 pure：hybrid thin owns host_defaults orch; cold seed keeps #ifdef twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_asm_pctx_apply_host_defaults(void *ctx, uint8_t *target, int32_t emit_elf_o) {
    struct ast_PipelineDepCtx *pctx = (struct ast_PipelineDepCtx *)ctx;
    const char *t = (const char *)(void *)target;
    if (pctx == NULL)
        return;
    pctx->target_arch = 0;
    if (t && (strstr(t, "aarch64") != NULL || strstr(t, "arm64") != NULL))
        pctx->target_arch = 1;
    if (t && strstr(t, "riscv64") != NULL)
        pctx->target_arch = 2;
    pctx->target_cpu_features = (int32_t)driver_get_pending_target_cpu_features();
#if defined(__APPLE__) && defined(__aarch64__)
    if (!t)
        pctx->target_arch = 1;
#endif
    pctx->use_macho_o = 0;
    pctx->use_coff_o = 0;
#if defined(__APPLE__)
    if (emit_elf_o)
        pctx->use_macho_o = 1;
#endif
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    if (emit_elf_o)
        pctx->use_coff_o = 1;
#endif
    if (emit_elf_o && t && strstr(t, "windows") != NULL)
        pctx->use_coff_o = 1;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave40 pure: hybrid thin owns fopen_wb via fd-handle fopen_wb_opaque; cold twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_asm_fopen_wb(uint8_t *path) {
    int fd;
    if (path == NULL)
        return NULL;
    fd = xlang_io_open_write((const char *)(void *)path);
    return fd < 0 ? NULL : xlang_driver_handle_from_fd(fd);
}
#endif

#ifndef XLANG_TMP_PREFIX
#if !defined(_WIN32) && !defined(_WIN64)
#define XLANG_TMP_PREFIX "/tmp/xlang_"
#else
#define XLANG_TMP_PREFIX "xlang_"
#endif
#endif

/* OS residual gate for asm mkstemp+fdopen (always linked under FROM_X).
 * Pure wave41 calls this before template/mkstemp; cold twin uses the same body.
 * MinGW provides mkstemp+fdopen; enabling Windows closes want-exe pure-asm BLD001
 * that previously forced -backend c fallback in win32 gates.
 * PLATFORM: SHARED — WINDOWS|POSIX|LINUX|MACOS → 1. */
int32_t xlang_driver_asm_mkstemp_fdopen_enabled(void) {
    return 1;
}

/* wave41 pure: hybrid thin owns mkstemp_fdopen orch; cold twin under #ifndef FROM_X.
 * PLATFORM: SHARED — mkstemp+fdopen (MinGW/POSIX); XLANG_TMP_PREFIX is host residual. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_asm_mkstemp_fdopen(uint8_t *path_out64) {
    int fd;
    if (path_out64 == NULL)
        return NULL;
    snprintf((char *)(void *)path_out64, 64, "%sxlang_asm_XXXXXX", XLANG_TMP_PREFIX);
    fd = mkstemp((char *)(void *)path_out64);
    if (fd < 0)
        return NULL;
    /* fdopen(fd,"wb") used to consume the fd; the handle owns it now (9.7.1). */
    return xlang_driver_handle_from_fd(fd);
}
#endif

void driver_asm_fclose(uint8_t *fp) {
    driver_asm_fclose_asm_out(fp);
}

/* wave39 pure: hybrid thin owns asm_fwrite via fd-handle fwrite_opaque + stdout_ptr;
 * cold twin under #ifndef FROM_X；FROM_X 无 pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_asm_fwrite(uint8_t *fp, uint8_t *data, int32_t len) {
    int fd;
    long n;
    if (data == NULL || len <= 0)
        return 0;
    fd = fp ? xlang_driver_handle_to_fd(fp) : 1;
    if (fd < 0)
        return 1;
    n = xlang_io_write(fd, data, (size_t)len);
    return (n == (size_t)len) ? 0 : 1;
}
#endif

/* wave40 pure: hybrid thin owns fflush_stdout + write_metric_o; cold twins. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_asm_fflush_stdout(void) {
    /* Raw fd 1 writes are unbuffered — nothing to flush (9.7.1). */
}

int32_t driver_asm_write_metric_o(uint8_t *path) {
    int fd;
    static const char zero_byte[1] = { 0 };
    long n;
    if (path == NULL)
        return 1;
    fd = xlang_io_open_write((const char *)(void *)path);
    if (fd < 0)
        return 1;
    n = xlang_io_write(fd, zero_byte, 1);
    if (n != 1)
        return 1;
    if (xlang_proc_close_fd(fd) != 0)
        return 1;
    return 0;
}
#endif

extern size_t pipeline_sizeof_elf_ctx(void);

/* wave23 pure：hybrid thin owns elf_ctx calloc; cold seed keeps sizeof/malloc twin. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_asm_elf_ctx_calloc(void) {
    size_t sz = pipeline_sizeof_elf_ctx();
    void *p;
    if (sz == 0)
        return NULL;
    p = malloc(sz);
    if (p)
        memset(p, 0, sz);
    return (uint8_t *)p;
}
#endif

/* wave38 pure: hybrid thin owns elf_ctx_free; cold seed twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_asm_elf_ctx_free(uint8_t *p) {
    free(p);
}
#endif

/* wave25 pure: hybrid thin owns asm tmp path BSS; cold seed twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static char g_driver_asm_tmp_path_slot[64];

uint8_t *driver_asm_tmp_path_slot(void) {
    return (uint8_t *)g_driver_asm_tmp_path_slot;
}
#else
extern uint8_t *driver_asm_tmp_path_slot(void);
#endif

/* wave34 pure: hybrid thin owns collect/defines/ndefines/bind/argv0/try_c/use_impl_c;
 * cold seed keeps C BSS + bodies; FROM_X no pure-dup (avoid dual defines BSS). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
#ifndef MAX_DEFINES
#define MAX_DEFINES 64
#endif
static const char *g_driver_asm_defines[MAX_DEFINES];
static int32_t g_driver_asm_ndefines;

int32_t driver_asm_collect_defines(int32_t argc, uint8_t *argv) {
    g_driver_asm_ndefines = 0;
    memset(g_driver_asm_defines, 0, sizeof g_driver_asm_defines);
    if (argv == NULL || argc <= 0)
        return 0;
    g_driver_asm_ndefines = (int32_t)driver_argv_collect_defines(
        (int)argc, (char **)(void *)argv, g_driver_asm_defines, MAX_DEFINES);
    return g_driver_asm_ndefines;
}

uint8_t *driver_asm_defines_as_u8(void) {
    if (g_driver_asm_ndefines <= 0)
        return NULL;
    return (uint8_t *)(void *)g_driver_asm_defines;
}

int32_t driver_asm_ndefines_get(void) {
    return g_driver_asm_ndefines;
}

static const char *g_driver_asm_dot = ".";
static const char *g_driver_asm_one_root[1];
static const char **g_driver_asm_lib_roots_bound;
static int32_t g_driver_asm_n_lib_bound;

uint8_t *driver_asm_bind_lib_roots(uint8_t *lib_roots, int32_t n, int32_t *n_out) {
    g_driver_asm_lib_roots_bound = (const char **)(void *)lib_roots;
    g_driver_asm_n_lib_bound = n;
    if (n <= 0 || lib_roots == NULL) {
        g_driver_asm_one_root[0] = g_driver_asm_dot;
        if (n_out)
            *n_out = 1;
        return (uint8_t *)(void *)g_driver_asm_one_root;
    }
    if (n_out)
        *n_out = n;
    return lib_roots;
}

uint8_t *driver_asm_argv0(uint8_t *argv) {
    char **a = (char **)(void *)argv;
    if (a == NULL || a[0] == NULL)
        return NULL;
    return (uint8_t *)(void *)a[0];
}

int32_t driver_asm_try_c_frontend_early(uint8_t *input_path, uint8_t *src, uint8_t *lib_roots,
                                        int32_t n_lib, uint8_t *out_path) {
    /*
     * 产品 runtime_driver_no_c 为 XLANG_NO_C_FRONTEND；本层固定走 no-C 继续 pipeline。
     * 冷启动全 C 体（seeds/rt_run_asm_backend.from_x.c 无 FROM_X）仍含 #if 分支。
     */
    (void)input_path;
    (void)src;
    (void)lib_roots;
    (void)n_lib;
    (void)out_path;
    return -2;
}

int32_t driver_asm_try_c_typeck_precheck(uint8_t *input_path, uint8_t *src, uint8_t *lib_roots,
                                        int32_t n_lib) {
    (void)input_path;
    (void)src;
    (void)lib_roots;
    (void)n_lib;
    /* 产品 NO_C：跳过 C typeck 预检。 */
    return -1;
}

int32_t driver_asm_use_compiler_impl_c(void) {
#if defined(XLANG_ASM_USE_COMPILER_IMPL_C)
    return 1;
#else
    return 0;
#endif
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/*
 * Wave17: asm work BSS pure package under PREFER thin.
 * hybrid thin owns BSS + get/set/reset/cleanup；cold keeps C static + memset twin；
 * FROM_X no pure-dup (avoid dual BSS under hybrid).
 * asm work 槽：
 * p: 0 path 1 src 2 out_path 3 arena 4 module 5 entry 6 dsrc 7 dpath 8 dlens
 *    9 dar 10 dmod 11 out_buf 12 pctx 13 kind 14 code 15 msg 16 lib 17 target
 *    18 argv 19 asm_out 20 elf 21 defines 22 tmp_path 23 one_ctx 24 dep_out
 * i: 0 nlib 1 ndeps 2 nimp 3 main 4 emit_elf 5 want_exe 6 smoke 7 ndef 8 argc
 *    9 ec 10 j 11 entry_only 12 skip_dep_load 13 rc 14 n_closure 15 num_funcs
 * z: 0 src_len 1 asz 2 msz 3 dep_len
 * reset also clears g_driver_asm_tmp_path_slot[0] (tmp_path BSS cold twin; hybrid = wave25 pure).
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
#define DRIVER_ASM_WORK_NP 25
#define DRIVER_ASM_WORK_NI 16
#define DRIVER_ASM_WORK_NZ 4
static uint8_t *g_asm_work_p[DRIVER_ASM_WORK_NP];
static int32_t g_asm_work_i[DRIVER_ASM_WORK_NI];
static size_t g_asm_work_z[DRIVER_ASM_WORK_NZ];

void driver_asm_work_reset(void) {
    memset(g_asm_work_p, 0, sizeof g_asm_work_p);
    memset(g_asm_work_i, 0, sizeof g_asm_work_i);
    memset(g_asm_work_z, 0, sizeof g_asm_work_z);
    g_driver_asm_tmp_path_slot[0] = 0;
}

uint8_t *driver_asm_work_p_get(int32_t i) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NP)
        return NULL;
    return g_asm_work_p[i];
}

void driver_asm_work_p_set(int32_t i, uint8_t *v) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NP)
        return;
    g_asm_work_p[i] = v;
}

int32_t driver_asm_work_i_get(int32_t i) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NI)
        return 0;
    return g_asm_work_i[i];
}

void driver_asm_work_i_set(int32_t i, int32_t v) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NI)
        return;
    g_asm_work_i[i] = v;
}

size_t driver_asm_work_z_get(int32_t i) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NZ)
        return 0;
    return g_asm_work_z[i];
}

void driver_asm_work_z_set(int32_t i, size_t v) {
    if (i < 0 || i >= DRIVER_ASM_WORK_NZ)
        return;
    g_asm_work_z[i] = v;
}

void driver_asm_work_cleanup(void) {
    int32_t n = g_asm_work_i[1]; /* ndeps */
    int32_t i;
    void *p;
    void *ds = g_asm_work_p[6];
    void *dp = g_asm_work_p[7];
    void *dl = g_asm_work_p[8];
    void *da = g_asm_work_p[9];
    void *dm = g_asm_work_p[10];
    for (i = 0; i < n; i++) {
        if (da) {
            p = ((void **)da)[i];
            free(p);
        }
        if (dm) {
            p = ((void **)dm)[i];
            free(p);
        }
        if (ds) {
            p = ((void **)ds)[i];
            free(p);
        }
        if (dp) {
            p = ((void **)dp)[i];
            free(p);
        }
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(g_asm_work_p[11]); /* out_buf */
    if (g_asm_work_p[12])
        pipeline_dep_ctx_heap_destroy((struct ast_PipelineDepCtx *)(void *)g_asm_work_p[12]);
    if (g_asm_work_p[19])
        driver_asm_fclose_asm_out((uint8_t *)(void *)g_asm_work_p[19]);
    free(g_asm_work_p[20]); /* elf */
    free(g_asm_work_p[3]);  /* arena */
    free(g_asm_work_p[4]);  /* module */
    free(g_asm_work_p[1]);  /* src */
    free(g_asm_work_p[13]); /* kind */
    free(g_asm_work_p[14]); /* code */
    free(g_asm_work_p[15]); /* msg */
    driver_asm_work_reset();
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* ========== Cap residual: rt_run_compiler_parsed R2 full ========== */

#ifndef X_FULL_MAX_LIB_ROOTS
#define X_FULL_MAX_LIB_ROOTS 16
#endif
#ifndef XLANG_TMP_PREFIX
#if !defined(_WIN32) && !defined(_WIN64)
#define XLANG_TMP_PREFIX "/tmp/xlang_"
#else
#define XLANG_TMP_PREFIX "xlang_"
#endif
#endif

typedef struct DriverCompileParsedAbi {
    const char *input_path;
    const char *out_path;
    const char *lib_roots_arr[X_FULL_MAX_LIB_ROOTS];
    int n_lib_roots;
    int want_asm_backend;
    const char *target;
    const char *opt_level;
    int use_lto;
} DriverCompileParsedAbi;

/* 9.7.1: inline ABI writers take the opaque fd-handle stream (rt_preamble seed). */
extern int write_io_net_abi_inline(uint8_t *cf);
extern int write_fs_path_map_error_abi_inline(uint8_t *cf);
extern int xlang_write_path_bytes(const char *path, const void *data, size_t len);
extern void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail,
                         const char *fmt, ...);
extern void diag_reportf_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                   const char *detail, const char *fmt, ...);
extern void runtime_diag_errno_path(const char *file, const char *kind, const char *op, const char *path);
extern void runtime_diag_errno_path_pair(const char *file, const char *kind, const char *op,
                                         const char *from_path, const char *to_path);
extern void driver_unlink_failed_output(const char *out_path);
extern const char *xlang_std_io_o_path(const char *argv0);
extern const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
extern const char *xlang_runtime_panic_o_path(const char *argv0);
extern const char *xlang_repo_root_from_argv0(const char *argv0);
extern int xlang_invoke_cc(const char **c_paths, int n, const char *out_path, const char *target,
                          const char *opt_level, int use_lto, const char *io_o, const char *fs_o,
                          const char *process_o, const char *string_o, const char *heap_o, const char *path_o,
                          const char *runtime_o, const char *runtime_panic_o, const char *net_o,
                          const char *thread_o, const char *time_o, const char *random_o, const char *env_o,
                          const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o,
                          const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o,
                          const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o,
                          const char *db_o, const char *elf_o, const char *json_o, const char *csv_o,
                          const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o,
                          const char *http_o, const char *tar_o, const char *simd_o, const char *context_o,
                          const char *datetime_o, const char *uuid_o, const char *url_o, const char *cli_o,
                          const char *security_o, const char *config_o, const char *cache_o, const char *trace_o,
                          const char *task_o, const char *schema_o, const char *test_o, const char *include_root,
                          const char *async_scheduler_o);
/* User-specified .o files from command line — single authority (G.3/G.4).
 * Why: xlang_invoke_cc takes a fixed variadic std/core .o list, so user .o args
 *   from argv (e.g. runtime_atomic_glue.o) never reach the cc link line.
 *   These setters plumb user .o args through xlang_invoke_cc_impl.
 * Authority: see runtime_link_abi.from_x.c (g_xlang_user_extra_o_files + setters).
 * PLATFORM: SHARED — argv is plain char**. */
extern void xlang_invoke_cc_set_user_o_files_from_argv(int argc, char **argv);
extern void xlang_invoke_cc_clear_user_o_files(void);
extern void codegen_reset_preamble_skip_mask(void);
extern void codegen_or_preamble_skip_mask(unsigned mask);
#ifndef CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS
#define CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS 1u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE 4u
#endif

/* wave32 pure: hybrid thin owns parsed field accessors + try_c_after_pp;
 * cold twins below; FROM_X no pure-dup.
 * PLATFORM: SHARED LP64 — offsetof layout must match thin.x constants. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_parsed_input_path(void *p) {
    if (!p) return NULL;
    return (uint8_t *)(void *)((DriverCompileParsedAbi *)p)->input_path;
}
uint8_t *driver_parsed_out_path(void *p) {
    if (!p) return NULL;
    return (uint8_t *)(void *)((DriverCompileParsedAbi *)p)->out_path;
}
uint8_t *driver_parsed_lib_roots(void *p) {
    if (!p) return NULL;
    return (uint8_t *)(void *)((DriverCompileParsedAbi *)p)->lib_roots_arr;
}
int32_t driver_parsed_n_lib_roots(void *p) {
    if (!p) return 0;
    return (int32_t)((DriverCompileParsedAbi *)p)->n_lib_roots;
}
int32_t driver_parsed_want_asm(void *p) {
    if (!p) return 0;
    return (int32_t)((DriverCompileParsedAbi *)p)->want_asm_backend;
}
uint8_t *driver_parsed_target(void *p) {
    if (!p) return NULL;
    return (uint8_t *)(void *)((DriverCompileParsedAbi *)p)->target;
}
static const char g_driver_parsed_opt_default[] = "2";
uint8_t *driver_parsed_opt_level(void *p) {
    const char *o;
    if (!p) return (uint8_t *)(void *)g_driver_parsed_opt_default;
    o = ((DriverCompileParsedAbi *)p)->opt_level;
    if (!o) return (uint8_t *)(void *)g_driver_parsed_opt_default;
    return (uint8_t *)(void *)o;
}
int32_t driver_parsed_use_lto(void *p) {
    if (!p) return 0;
    return (int32_t)((DriverCompileParsedAbi *)p)->use_lto;
}

int32_t driver_parsed_try_c_after_pp(uint8_t *input_path, uint8_t *src, size_t src_len,
                                     uint8_t *lib_roots, int32_t n_lib, uint8_t *out_path,
                                     int32_t argc, uint8_t *argv, uint8_t *opt_level,
                                     int32_t use_lto, int32_t ndefines, uint8_t *defines) {
    /*
     * 产品 runtime_driver_no_c 为 XLANG_NO_C_FRONTEND：固定继续 .x pipeline。
     * 冷启动全 C 体（seeds/rt_run_compiler_parsed.from_x.c 无 FROM_X）仍含完整 C 分支。
     */
    (void)input_path;
    (void)src;
    (void)src_len;
    (void)lib_roots;
    (void)n_lib;
    (void)out_path;
    (void)argc;
    (void)argv;
    (void)opt_level;
    (void)use_lto;
    (void)ndefines;
    (void)defines;
    return -2;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave19 pure under PREFER：skip_codegen_dep_0; cold C twin; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_pipeline_dep_ctx_set_skip_codegen_dep_0(void *ctx, int32_t v) {
    if (!ctx) return;
    ((struct ast_PipelineDepCtx *)ctx)->skip_codegen_dep_0 = (int)v;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave25 pure: hybrid thin owns parsed tmp BSS; cold seed twin; FROM_X no pure-dup.
 * PLATFORM: SHARED — 256 bytes matches .x rt_cp_step_open_out malloc(256)
 * and accommodates Windows long TEMP paths (C:\xlang_tmp\xlang_xlang_x.YZXDC4.c).
 * open_out (always seed) writes only via driver_parsed_tmp_c_buf() accessor. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static char g_driver_parsed_tmp_c[256];
/* Cold twin: 64-byte slot cleared by parsed work reset (parity). */
static char g_parsed_tmp_c_slot[64];

uint8_t *driver_parsed_tmp_c_buf(void) {
    return (uint8_t *)g_driver_parsed_tmp_c;
}

uint8_t *driver_parsed_tmp_c_slot(void) {
    return (uint8_t *)g_parsed_tmp_c_slot;
}
#else
extern uint8_t *driver_parsed_tmp_c_buf(void);
extern uint8_t *driver_parsed_tmp_c_slot(void);
#endif

/* Permanent OS residual: host temp path prefix for mkstemp templates.
 * PLATFORM: POSIX → "/tmp/xlang_"; WINDOWS → "xlang_" (cwd-relative; TEMP via env elsewhere).
 * Pure open_out concatenates this with "xlang_x.XXXXXX" without #ifdef in .x. */
const char *xlang_driver_tmp_prefix(void) {
    return XLANG_TMP_PREFIX;
}

/* wave27 pure: hybrid thin owns open_out; cold twin; FROM_X no pure-dup.
 * wave25: writes tmp path only via pure/cold driver_parsed_tmp_c_buf().
 * PLATFORM: WINDOWS | POSIX — close mkstemp fd BEFORE rename (BLD001). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
uint8_t *driver_parsed_open_out_file(uint8_t *out_path, uint8_t *tmp_c_out64, int32_t *emit_stdout) {
    char tmp[128];
    int fd;
    /* wave25: never touch BSS static by name — hybrid pure owns the buffer. */
    char *tbuf = (char *)(void *)driver_parsed_tmp_c_buf();
    if (emit_stdout)
        *emit_stdout = 0;
    if (tbuf)
        tbuf[0] = 0;
    if (tmp_c_out64)
        tmp_c_out64[0] = 0;
    if (!out_path) {
        if (emit_stdout)
            *emit_stdout = 1;
        /* Emit-to-stdout: encoded std handle; consumers guard fd 1 on close. */
        return xlang_driver_handle_from_fd(1);
    }
    if (!tbuf)
        return NULL;
    snprintf(tmp, sizeof(tmp), "%sxlang_x.XXXXXX", XLANG_TMP_PREFIX);
    fd = mkstemp(tmp);
    if (fd < 0) {
        runtime_diag_errno_path((const char *)(void *)out_path, "build error", "mkstemp", tmp);
        return NULL;
    }
    /* PLATFORM: WINDOWS | POSIX — Windows forbids renaming a file held open by
     * fdopen/fopen (POSIX allows it). Close the mkstemp fd BEFORE rename, then
     * reopen the renamed .c path. Without this, rename fails with
     * STATUS_SHARING_VIOLATION / "Permission denied" (BLD001). */
    xlang_proc_close_fd(fd);
    /* Cap 256 matches pure/cold BSS; snprintf enforces NUL. */
    snprintf(tbuf, 256, "%s.c", tmp);
    if (rename(tmp, tbuf) != 0) {
        runtime_diag_errno_path_pair((const char *)(void *)out_path, "build error", "rename", tmp, tbuf);
        unlink(tmp);
        return NULL;
    }
    fd = xlang_io_open_write(tbuf);
    if (fd < 0) {
        runtime_diag_errno_path((const char *)(void *)out_path, "build error", "open", tbuf);
        unlink(tbuf);
        return NULL;
    }
    if (tmp_c_out64) {
        size_t n = strlen(tbuf);
        if (n > 255)
            n = 255;
        memcpy(tmp_c_out64, tbuf, n);
        tmp_c_out64[n] = 0;
    }
    return xlang_driver_handle_from_fd(fd);
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave26 pure: hybrid thin owns fclose / fclose_rc / write_out; cold twins; FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_parsed_fclose(uint8_t *fp) {
    if (!fp || xlang_driver_handle_to_fd(fp) == 1)
        return;
    (void)xlang_driver_handle_close(fp);
}

int32_t driver_parsed_fclose_rc(uint8_t *fp) {
    if (!fp || xlang_driver_handle_to_fd(fp) == 1)
        return 0;
    return xlang_driver_handle_close(fp);
}

int32_t driver_parsed_write_out(uint8_t *fp, uint8_t *data, int32_t len) {
    int fd = xlang_driver_handle_to_fd(fp);
    size_t first_line = 0;
    int need_preamble;
    static const char min_preamble[] =
        "/* generated */\n#include <stdint.h>\n#include <stddef.h>\n#include <stdlib.h>\n#include "
        "<stdio.h>\n#include <string.h>\n";
    if (fd < 0 || !data || len < 0)
        return 1;
    while (first_line < (size_t)len && data[first_line] != '\n')
        first_line++;
    if (first_line < (size_t)len)
        first_line++;
    need_preamble =
        (len > 0 && data[0] != '#' && (len < 2 || data[0] != '/' || data[1] != '*'));
    if (need_preamble) {
        if (xlang_io_write(fd, min_preamble, sizeof(min_preamble) - 1) !=
            (long)(sizeof(min_preamble) - 1))
            return 1;
    }
    if (xlang_io_write(fd, data, first_line) != (long)first_line)
        return 1;
    if (write_io_net_abi_inline(fp) != 0)
        return 1;
    if (write_fs_path_map_error_abi_inline(fp) != 0)
        return 1;
    if (xlang_io_write(fd, data + first_line, (size_t)len - first_line) !=
        (long)((size_t)len - first_line))
        return 1;
    return 0;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave28 pure: hybrid thin owns invoke_cc orch; cold twin; FROM_X no pure-dup.
 * PLATFORM: SHARED — path pack + set/clear user .o + xlang_invoke_cc + fail/KEEP_C. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
int32_t driver_parsed_invoke_cc(uint8_t *tmp_c, uint8_t *out_path, uint8_t *opt_level, int32_t use_lto,
                                uint8_t *argv0, int32_t argc, uint8_t *argv) {
    const char *c_paths[1];
    const char *a0 = (const char *)(void *)argv0;
    const char *opt = opt_level ? (const char *)(void *)opt_level : "2";
    const char *io_o = xlang_std_io_o_path(a0);
    const char *fs_o = NULL;
    const char *process_o = xlang_rel_o_path_from_argv0(a0, "std/process/process.o");
    const char *string_o = xlang_rel_o_path_from_argv0(a0, "std/string/string.o");
    const char *heap_o = NULL;
    const char *path_o = xlang_rel_o_path_from_argv0(a0, "std/path/path.o");
    const char *runtime_o = xlang_rel_o_path_from_argv0(a0, "std/runtime/runtime.o");
    const char *runtime_panic_o = xlang_runtime_panic_o_path(a0);
    const char *net_o = xlang_rel_o_path_from_argv0(a0, "std/net/net.o");
    const char *thread_o = xlang_rel_o_path_from_argv0(a0, "std/thread/thread.o");
    const char *time_o = xlang_rel_o_path_from_argv0(a0, "std/time/time.o");
    const char *random_o = xlang_rel_o_path_from_argv0(a0, "std/random/random.o");
    const char *env_o = xlang_rel_o_path_from_argv0(a0, "std/env/env.o");
    const char *sync_o = xlang_rel_o_path_from_argv0(a0, "std/sync/sync.o");
    const char *encoding_o = xlang_rel_o_path_from_argv0(a0, "std/encoding/encoding.o");
    const char *base64_o = xlang_rel_o_path_from_argv0(a0, "std/base64/base64.o");
    const char *crypto_o = xlang_rel_o_path_from_argv0(a0, "std/crypto/crypto.o");
    const char *log_o = xlang_rel_o_path_from_argv0(a0, "std/log/log.o");
    const char *atomic_o = xlang_rel_o_path_from_argv0(a0, "std/atomic/atomic.o");
    const char *channel_o = xlang_rel_o_path_from_argv0(a0, "std/channel/channel.o");
    const char *backtrace_o = xlang_rel_o_path_from_argv0(a0, "std/backtrace/backtrace.o");
    const char *hash_o = xlang_rel_o_path_from_argv0(a0, "std/hash/hash.o");
    const char *math_o = xlang_rel_o_path_from_argv0(a0, "std/math/math.o");
    const char *sort_o = xlang_rel_o_path_from_argv0(a0, "std/sort/sort.o");
    const char *ffi_o = xlang_rel_o_path_from_argv0(a0, "std/ffi/ffi.o");
    const char *db_o = xlang_rel_o_path_from_argv0(a0, "std/db/sqlite/sqlite.o");
    const char *elf_o = xlang_rel_o_path_from_argv0(a0, "std/elf/elf.o");
    const char *json_o = xlang_rel_o_path_from_argv0(a0, "std/json/json.o");
    const char *csv_o = xlang_rel_o_path_from_argv0(a0, "std/csv/csv.o");
    const char *regex_o = xlang_rel_o_path_from_argv0(a0, "std/regex/regex.o");
    const char *compress_o = NULL;
    const char *unicode_o = xlang_rel_o_path_from_argv0(a0, "std/unicode/unicode.o");
    const char *dynlib_o = xlang_rel_o_path_from_argv0(a0, "std/dynlib/dynlib.o");
    const char *http_o = xlang_rel_o_path_from_argv0(a0, "std/http/http.o");
    const char *tar_o = xlang_rel_o_path_from_argv0(a0, "std/tar/tar.o");
    const char *simd_o = xlang_rel_o_path_from_argv0(a0, "std/simd/simd.o");
    const char *context_o = xlang_rel_o_path_from_argv0(a0, "std/context/context.o");
    const char *datetime_o = xlang_rel_o_path_from_argv0(a0, "std/datetime/datetime.o");
    const char *uuid_o = xlang_rel_o_path_from_argv0(a0, "std/uuid/uuid.o");
    const char *url_o = xlang_rel_o_path_from_argv0(a0, "std/url/url.o");
    const char *cli_o = xlang_rel_o_path_from_argv0(a0, "std/cli/cli.o");
    const char *security_o = xlang_rel_o_path_from_argv0(a0, "std/security/security.o");
    const char *config_o = xlang_rel_o_path_from_argv0(a0, "std/config/config.o");
    const char *cache_o = xlang_rel_o_path_from_argv0(a0, "std/cache/cache.o");
    const char *trace_o = xlang_rel_o_path_from_argv0(a0, "std/trace/trace.o");
    const char *task_o = xlang_rel_o_path_from_argv0(a0, "std/task/task.o");
    const char *schema_o = xlang_rel_o_path_from_argv0(a0, "std/schema/schema.o");
    const char *test_o = xlang_rel_o_path_from_argv0(a0, "std/test/test.o");
    int cc_ret;
    if (!tmp_c || !out_path)
        return 1;
    c_paths[0] = (const char *)(void *)tmp_c;
    /* Single authority (G.3/G.4): set user .o files from argv before xlang_invoke_cc
     * so they are pushed to the cc link line (resolves UNDEF symbols from std .o
     * that user glue provides, e.g. runtime_atomic_glue.o provides atomic_load_i32_c). */
    xlang_invoke_cc_set_user_o_files_from_argv((int)argc, (char **)(void *)argv);
    cc_ret = xlang_invoke_cc(c_paths, 1, (const char *)(void *)out_path, NULL, opt, (int)use_lto, io_o,
                            fs_o, process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o, net_o,
                            thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o,
                            atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, db_o, elf_o, json_o,
                            csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, simd_o, context_o,
                            datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o, task_o,
                            schema_o, test_o, xlang_repo_root_from_argv0(a0), NULL);
    /* Always clear after invoke to prevent stale pointers across calls. */
    xlang_invoke_cc_clear_user_o_files();
    if (cc_ret != 0) {
        driver_unlink_failed_output((const char *)(void *)out_path);
        diag_reportf_with_code(NULL, 0, 0, "build error", "BLD001", NULL,
                               "cc failed, keeping generated C: %s", (const char *)(void *)tmp_c);
        return 1;
    }
    if (!link_abi_getenv("XLANG_KEEP_C"))
        unlink((const char *)(void *)tmp_c);
    else
        diag_reportf(NULL, 0, 0, "note", NULL, "kept generated C: %s", (const char *)(void *)tmp_c);
    return 0;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* wave31 pure: hybrid thin owns dump_prep + deps_has_* + apply_preamble_skip;
 * cold twins below; FROM_X no pure-dup.
 * PLATFORM: SHARED — mask bits match codegen.h; dump path /tmp dev-only. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
void driver_parsed_maybe_dump_prep(uint8_t *input_path, uint8_t *src, size_t src_len) {
    if (!link_abi_getenv("XLANG_DUMP_PREP") || !src)
        return;
    if (xlang_write_path_bytes("/tmp/xlang_prep_entry.bin", src, src_len) == 0) {
        diag_reportf((const char *)(void *)input_path, 0, 0, "note", NULL,
                     "dumped prep entry (%zu bytes) to /tmp/xlang_prep_entry.bin", src_len);
    }
}

int32_t driver_parsed_deps_has_std_io_core(uint8_t *dep_paths, int32_t n_deps) {
    int32_t j;
    char **dp = (char **)(void *)dep_paths;
    if (!dp || n_deps <= 0)
        return 0;
    for (j = 0; j < n_deps; j++) {
        if (dp[j] && strcmp(dp[j], "std.io.core") == 0)
            return 1;
    }
    return 0;
}

/** dep 闭包是否含 std.io.driver（co-emit 会 emit submit_*_batch_buf 强符号）。 */
int32_t driver_parsed_deps_has_std_io_driver(uint8_t *dep_paths, int32_t n_deps) {
    int32_t j;
    char **dp = (char **)(void *)dep_paths;
    if (!dp || n_deps <= 0)
        return 0;
    for (j = 0; j < n_deps; j++) {
        if (dp[j] && strcmp(dp[j], "std.io.driver") == 0)
            return 1;
    }
    return 0;
}

void driver_parsed_apply_preamble_skip(uint8_t *dep_paths, int32_t n_deps) {
    codegen_reset_preamble_skip_mask();
    if (!driver_parsed_deps_has_std_io_core(dep_paths, n_deps)) {
        codegen_or_preamble_skip_mask(CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS |
                                      CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE);
    }
    /* co-emit driver 时同 TU 已有强符号定义；weak 桩与之冲突（C 同 TU redefinition）。 */
    if (driver_parsed_deps_has_std_io_driver(dep_paths, n_deps)) {
#ifndef CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH
#define CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH 8u
#endif
        codegen_or_preamble_skip_mask(CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH);
    }
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/*
 * Wave18: parsed work BSS pure package under PREFER thin.
 * hybrid thin owns BSS + get/set/reset/cleanup；cold keeps C static + memset twin；
 * FROM_X no pure-dup (avoid dual BSS under hybrid).
 * wave25: tmp slots pure under hybrid; cold twin still clears statics here.
 * parsed work 槽：
 * p: 0 path 1 src 2 out_path 3 arena 4 module 5 entry 6 dsrc 7 dpath 8 dlens
 *    9 dar 10 dmod 11 out_buf 12 pctx 13 kind 14 code 15 msg 16 lib 17 opt
 *    18 argv 19 cf 20 tmp_c 21 target 22 defs
 * i: 0 nlib 1 ndeps 2 nimp 3 main 4 want_asm 5 emit_stdout 6 ndef 7 use_lto
 *    8 argc 9 ec 10 j 11 check 12 n_funcs
 * z: 0 src_len 1 asz 2 msz
 */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
#define DRIVER_PARSED_WORK_NP 24
#define DRIVER_PARSED_WORK_NI 14
#define DRIVER_PARSED_WORK_NZ 4
static uint8_t *g_parsed_work_p[DRIVER_PARSED_WORK_NP];
static int32_t g_parsed_work_i[DRIVER_PARSED_WORK_NI];
static size_t g_parsed_work_z[DRIVER_PARSED_WORK_NZ];

void driver_parsed_work_reset(void) {
    memset(g_parsed_work_p, 0, sizeof g_parsed_work_p);
    memset(g_parsed_work_i, 0, sizeof g_parsed_work_i);
    memset(g_parsed_work_z, 0, sizeof g_parsed_work_z);
    g_parsed_tmp_c_slot[0] = 0;
    g_driver_parsed_tmp_c[0] = 0;
}

uint8_t *driver_parsed_work_p_get(int32_t i) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NP)
        return NULL;
    return g_parsed_work_p[i];
}
void driver_parsed_work_p_set(int32_t i, uint8_t *v) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NP)
        return;
    g_parsed_work_p[i] = v;
}
int32_t driver_parsed_work_i_get(int32_t i) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NI)
        return 0;
    return g_parsed_work_i[i];
}
void driver_parsed_work_i_set(int32_t i, int32_t v) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NI)
        return;
    g_parsed_work_i[i] = v;
}
size_t driver_parsed_work_z_get(int32_t i) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NZ)
        return 0;
    return g_parsed_work_z[i];
}
void driver_parsed_work_z_set(int32_t i, size_t v) {
    if (i < 0 || i >= DRIVER_PARSED_WORK_NZ)
        return;
    g_parsed_work_z[i] = v;
}

/* wave1225: release AST sidecars before free — see thin.x driver_parsed_work_cleanup. */
extern void ast_pool_arena_release(void *a);
extern void ast_pool_module_release(void *m);

void driver_parsed_work_cleanup(void) {
    int32_t n = g_parsed_work_i[1]; /* ndeps */
    int32_t emit_stdout = g_parsed_work_i[5];
    int32_t i;
    void *p;
    void *ds = g_parsed_work_p[6];
    void *dp = g_parsed_work_p[7];
    void *dl = g_parsed_work_p[8];
    void *da = g_parsed_work_p[9];
    void *dm = g_parsed_work_p[10];
    if (link_abi_getenv && link_abi_getenv("XLANG_DEBUG_SIDECAR")) {
        /* Cap residual 9.7.1: debug trace via raw fd-2 write (no stdio). */
        char sidecar_buf[160];
        xlang_snprintf(sidecar_buf, sizeof(sidecar_buf),
                       "xlang: [SIDECAR] cleanup enter n_deps=%d arena=%p module=%p da=%p dm=%p\n",
                       n, g_parsed_work_p[3], g_parsed_work_p[4], da, dm);
        (void)xlang_io_write(2, sidecar_buf, strlen(sidecar_buf));
    }
    for (i = 0; i < n; i++) {
        if (da) {
            p = ((void **)da)[i];
            if (p) {
                ast_pool_arena_release(p);
                free(p);
            }
        }
        if (dm) {
            p = ((void **)dm)[i];
            if (p) {
                ast_pool_module_release(p);
                free(p);
            }
        }
        if (ds) {
            p = ((void **)ds)[i];
            free(p);
        }
        if (dp) {
            p = ((void **)dp)[i];
            free(p);
        }
    }
    free(ds);
    free(dp);
    free(dl);
    free(da);
    free(dm);
    free(g_parsed_work_p[11]); /* out_buf */
    if (g_parsed_work_p[12])
        pipeline_dep_ctx_heap_destroy((struct ast_PipelineDepCtx *)(void *)g_parsed_work_p[12]);
    if (g_parsed_work_p[19] && !emit_stdout) {
        driver_parsed_fclose(g_parsed_work_p[19]);
        if (g_parsed_work_p[20] && g_parsed_work_p[20][0])
            unlink((const char *)(void *)g_parsed_work_p[20]);
        else if (g_driver_parsed_tmp_c[0])
            unlink(g_driver_parsed_tmp_c);
    }
    /* wave1225: release-before-free (batch check sidecar leak / address reuse). */
    if (g_parsed_work_p[3]) {
        ast_pool_arena_release(g_parsed_work_p[3]);
        free(g_parsed_work_p[3]);
    }
    if (g_parsed_work_p[4]) {
        ast_pool_module_release(g_parsed_work_p[4]);
        free(g_parsed_work_p[4]);
    }
    free(g_parsed_work_p[1]);  /* src */
    free(g_parsed_work_p[13]); /* kind */
    free(g_parsed_work_p[14]); /* code */
    free(g_parsed_work_p[15]); /* msg */
    free(g_parsed_work_p[20]); /* tmp_c heap copy if any */
    driver_parsed_work_reset();
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* ========== Cap residual: rt_dispatch_impl R2 full ========== */

extern int driver_lib_roots_from_key(uint8_t *lib_key, const char **out_arr,
                                     char bufs[X_FULL_MAX_LIB_ROOTS][512]);
extern int driver_run_compiler_parsed(void *p, int argc, char **argv);

/* wave36 pure：hybrid thin owns lib_roots_from_key + run_compiler_parsed +
 * lib_root_at + opt_default; cold seed keeps C twins (static bufs + struct pack).
 * PLATFORM: SHARED LP64 — FROM_X no pure-dup. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static char g_dispatch_lib_bufs[X_FULL_MAX_LIB_ROOTS][512];
static const char *g_dispatch_lib_roots[X_FULL_MAX_LIB_ROOTS];
static const char g_dispatch_opt_default[] = "2";

uint8_t *driver_dispatch_lib_roots_from_key(uint8_t *lib_key, int32_t *n_out) {
    int n = driver_lib_roots_from_key(lib_key, g_dispatch_lib_roots, g_dispatch_lib_bufs);
    if (n_out)
        *n_out = (int32_t)n;
    return (uint8_t *)(void *)g_dispatch_lib_roots;
}

uint8_t *driver_dispatch_lib_root_at(uint8_t *roots, int32_t i) {
    const char **arr;
    if (!roots || i < 0 || i >= X_FULL_MAX_LIB_ROOTS)
        return NULL;
    arr = (const char **)(void *)roots;
    return (uint8_t *)(void *)arr[i];
}

uint8_t *driver_dispatch_opt_default(void) {
    return (uint8_t *)(void *)g_dispatch_opt_default;
}

int32_t driver_dispatch_run_compiler_parsed(uint8_t *input_path, uint8_t *out_path,
                                            uint8_t *lib_roots, int32_t n_lib,
                                            uint8_t *target, uint8_t *opt_level,
                                            int32_t use_lto, int32_t argc, uint8_t *argv) {
    DriverCompileParsedAbi p;
    int n = n_lib;
    memset(&p, 0, sizeof p);
    p.input_path = (const char *)(void *)input_path;
    p.out_path = out_path ? (const char *)(void *)out_path : NULL;
    if (n > X_FULL_MAX_LIB_ROOTS)
        n = X_FULL_MAX_LIB_ROOTS;
    if (n > 0 && lib_roots)
        memcpy(p.lib_roots_arr, lib_roots, (size_t)n * sizeof(const char *));
    p.n_lib_roots = n;
    p.want_asm_backend = 0;
    p.target = (target && target[0]) ? (const char *)(void *)target : NULL;
    p.opt_level = (opt_level && opt_level[0]) ? (const char *)(void *)opt_level : g_dispatch_opt_default;
    p.use_lto = use_lto != 0;
    return (int32_t)driver_run_compiler_parsed((void *)&p, (int)argc, (char **)(void *)argv);
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* ---------- Cap residual：rt_asm_stub R2（GAS 行表 + OutBuf append） ---------- */
/* wave14 pure：hybrid thin owns gas_line_at/count + out_append_cstr (LE OutBuf layout);
 * cold seed keeps C table/append; FROM_X no pure-dup (H↓). */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
static const char *const g_asm_stub_gas_lines[] = {
    ".text",         ".globl main", "main:",       "pushq %rbp", "movq %rsp, %rbp",
    "subq $0, %rsp", "movl $42, %eax", "movq %rsp, %rbp", "popq %rbp", "ret",
};
static const int32_t g_asm_stub_gas_lines_n =
    (int32_t)(sizeof g_asm_stub_gas_lines / sizeof g_asm_stub_gas_lines[0]);

uint8_t *driver_asm_stub_gas_line_at(int32_t i) {
    if (i < 0 || i >= g_asm_stub_gas_lines_n)
        return NULL;
    return (uint8_t *)(uintptr_t)g_asm_stub_gas_lines[i];
}

int32_t driver_asm_stub_gas_line_count(void) {
    return g_asm_stub_gas_lines_n;
}

int32_t driver_asm_stub_out_append_cstr(void *out, uint8_t *s) {
    struct driver_codegen_outbuf_abi *ob;
    size_t n;
    size_t len;
    size_t cur;
    if (!out || !s)
        return -1;
    ob = (struct driver_codegen_outbuf_abi *)out;
    len = strlen((const char *)(void *)s);
    cur = (size_t)ob->length;
    if (cur > (size_t)X_CODEGEN_OUTBUF_CAP_ABI)
        return -1;
    if (cur + len + 1 > (size_t)X_CODEGEN_OUTBUF_CAP_ABI)
        return -1;
    memcpy(ob->data + cur, s, len);
    ob->data[cur + len] = (unsigned char)'\n';
    n = cur + len + 1;
    ob->length = (int32_t)n;
    return 0;
}
#endif /* !XLANG_L2_RDABI_THIN_FROM_X */

/* ---------- Cap residual：rt_dispatch_thin R2（sibling path/access/fork） ---------- */
/* wave43 pure：hybrid thin owns driver_dispatch_sibling_try_spawn orch
 *   （null/argc + G.7 driver_argv0_basename_is + path pure BSS 512 + residual）；
 * cold twin under #ifndef FROM_X；FROM_X 无 pure-dup。
 * always-seed：xlang_driver_sibling_argv0_get（*u8→char** cast + av[0]）
 *   + xlang_driver_sibling_access_spawn（access X_OK + fork/exec 或 spawnvp）。
 * PLATFORM: SHARED orch；WINDOWS spawn vs POSIX fork in residual.
 */
extern int driver_argv0_basename_is(const char *argv0, const char *base);

/* Permanent Cap residual: *u8 argv_opaque → cast + av[0].
 * Pure wave43 cannot cast *u8→**u8 (-E drops body). Always linked under FROM_X.
 * PLATFORM: SHARED — cast glue only. */
uint8_t *xlang_driver_sibling_argv0_get(uint8_t *argv_opaque) {
    char **av;
    if (argv_opaque == NULL)
        return NULL;
    av = (char **)(void *)argv_opaque;
    if (av[0] == NULL)
        return NULL;
    return (uint8_t *)(void *)av[0];
}

/* Permanent OS residual: access(path, X_OK) then spawn/fork with av[0]=path.
 * Pure wave43 owns path build + basename gate; this is process boundary only.
 * PLATFORM: WINDOWS _spawnvp; POSIX fork+execvp+waitpid. */
int32_t xlang_driver_sibling_access_spawn(uint8_t *path, int32_t argc, uint8_t *argv_opaque) {
    char **av;
    char *xlang_c;
    (void)argc;
    if (path == NULL || argv_opaque == NULL)
        return -1;
    xlang_c = (char *)(void *)path;
    av = (char **)(void *)argv_opaque;
    if (access(xlang_c, X_OK) != 0)
        return -1;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    {
        intptr_t rc;
        av[0] = xlang_c;
        rc = _spawnvp(_P_WAIT, xlang_c, (const char *const *)av);
        if (rc == -1)
            return -1;
        return (int32_t)rc;
    }
#else
    {
        pid_t pid = fork();
        if (pid < 0)
            return -1;
        if (pid == 0) {
            av[0] = xlang_c;
            execvp(xlang_c, av);
            _exit(127);
        }
        {
            int st = 0;
            if (waitpid(pid, &st, 0) < 0)
                return -1;
            if (WIFEXITED(st))
                return (int32_t)WEXITSTATUS(st);
            return 1;
        }
    }
#endif
}

/* wave43 pure: hybrid thin owns sibling_try_spawn orch; cold twin under #ifndef FROM_X. */
#ifndef XLANG_L2_RDABI_THIN_FROM_X
/**
 * 与冷启动 seeds/rt_dispatch_thin.from_x.c driver_try_compile_via_shu_c_sibling 同语义。
 * argv 为 char**（*u8）；成功返回子进程 exit；-1 未委托。
 * Cold twin：自洽 path build + G.7 basename + residual access_spawn（无 pure BSS）。
 */
int32_t driver_dispatch_sibling_try_spawn(int32_t argc, uint8_t *argv) {
    char xlang_c[512];
    char **av = (char **)(void *)argv;
    const char *self;
    const char *slash;
    if (argc < 2 || !av || !av[0])
        return -1;
    if (driver_argv0_basename_is(av[0], "xlang-c"))
        return -1;
    self = av[0];
    slash = strrchr(self, '/');
#if defined(_WIN32)
    {
        const char *bs = strrchr(self, '\\');
        if (bs && (!slash || bs > slash))
            slash = bs;
    }
#endif
    if (slash) {
        size_t dir_len = (size_t)(slash - self);
        if (dir_len >= sizeof(xlang_c) - 8)
            return -1;
        memcpy(xlang_c, self, dir_len);
        xlang_c[dir_len] = '\0';
        strcat(xlang_c, "/xlang-c");
    } else {
        strcpy(xlang_c, "xlang-c");
    }
    return xlang_driver_sibling_access_spawn((uint8_t *)(void *)xlang_c, argc, argv);
}
#endif

int runtime_driver_abi_slice_marker(void) {
    return 1;
}
