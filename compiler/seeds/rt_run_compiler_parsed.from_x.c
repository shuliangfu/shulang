/* seeds/rt_run_compiler_parsed.from_x.c — G-02f-316 P2 runtime rest (parsed dispatch)
 * Logic source: src/runtime/rt_run_compiler_parsed.x
 * Hybrid: XLANG_RT_RUN_COMPILER_PARSED_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：公共业务符号 driver_run_compiler_parsed 由 full .x 提供；
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual（driver_abi）：Parsed 字段/C 前端块/FILE+invoke_cc/work 槽。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 *
 * Scope: driver_run_compiler_parsed（argv 已解析后的 asm/C/pipeline 编排）。
 */
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: parsed dispatch path → Cap snprintf */
/* G.7: Cap after stdio for rt_run_compiler_parsed cold seed. */
#undef snprintf
#define snprintf xlang_snprintf
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "diag.h"
#include "runtime_diag_codes.h"
#include "runtime_io_abi.h"
#include "runtime_driver_abi.h"
#include "xlang_driver_stream_cap.h" /* Cap residual 9.7.1: opaque FILE* face → fd-handle face */
#include "runtime_pipeline_abi.h"
#include "runtime_link_abi.h"
/* wave238 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — cold seed twin uses same face as product hybrid pure .x peers. */
extern char *link_abi_getenv(const char *name);
#include "runtime_proc_abi.h"
#include "token.h"

#ifndef XLANG_TMP_PREFIX
#if !defined(_WIN32) && !defined(_WIN64)
#define XLANG_TMP_PREFIX "/tmp/xlang_"
#else
#define XLANG_TMP_PREFIX "xlang_"
#endif
#endif

#ifndef MAX_DEFINES
#define MAX_DEFINES 64
#endif
#ifndef MAX_ALL_DEPS
#define MAX_ALL_DEPS 128
#endif
#ifndef X_FULL_MAX_LIB_ROOTS
#define X_FULL_MAX_LIB_ROOTS 16
#endif
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define X_CODEGEN_OUTBUF_CAP (9 * 1024 * 1024)
struct codegen_CodegenOutBuf {
  unsigned char data[X_CODEGEN_OUTBUF_CAP];
  int32_t length;
};

struct parser_ParseIntoResult {
  int32_t ok;
  int32_t main_idx;
};
struct ASTModule;

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

extern void driver_bump_stack_limit(void);
extern int driver_argv_collect_defines(int argc, char **argv, const char **defines, int max_defines);
extern void cfg_apply_compile_target_from_triple(const char *triple, int len);
extern void cfg_reset_compile_target(void);
extern char *xlang_preprocess_with_path(const char *data, size_t len, const char *path, const char **defines, int n_defines, size_t *out_len);
extern char *xlang_preprocess(const char *data, size_t len, const char **defines, int n_defines, size_t *out_len);
extern char *xlang_preprocess_quiet(const char *data, size_t len, const char **defines, int n_defines, size_t *out_len);
extern void pipeline_diag_emitted_reset(void);
extern int pipeline_diag_emitted_get(void);
extern void diag_set_file(const char *path, const char *src, size_t len);
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_module(void);
extern void parser_parse_into_init(void *arena, void *module);
extern struct parser_ParseIntoResult parser_parse_into_buf(void *arena, void *module, uint8_t *data, int32_t len);
extern void parser_parse_into_set_main_index(void *module, int32_t main_idx);
extern int driver_get_module_num_funcs(void *m);
extern int32_t parser_get_module_num_imports(void *module);
extern void xlang_get_entry_dir(const char *path, char *out, size_t out_sz);
/* wave77: G.7 accessors only — pure owns typeck_dep BSS under hybrid; no naked C globals. */
extern void typeck_ndep_store(int32_t n);
extern void typeck_dep_module_set(int32_t i, void *mod);
extern void typeck_dep_arena_set(int32_t i, void *arena);
extern void driver_dep_seeded_clear_all(void);
extern void driver_dep_seed_slots(void **arenas, void **modules, int n);
extern void driver_dep_publish_slot(int j, void *arena, void *module, const char *path);
extern void pipeline_set_dep_slots(void **arenas, void **modules);
extern void codegen_set_dep_slots_for_x_pipeline(struct ASTModule **mods, const char **paths, int n);
extern void codegen_set_preamble_has_core_option_result(int on);
extern void pipeline_dep_ctx_heap_destroy(struct ast_PipelineDepCtx *ctx);
extern int driver_source_has_generic_syntax(const uint8_t *path, int path_len);
extern int driver_source_has_top_level_import(const char *src, size_t len);
extern int driver_source_has_top_level_import_path(const char *path);
extern int driver_run_asm_backend(const char *input_path, const char *out_path, const char **lib_roots_arr, int n_lib_roots,
                                  const char *target, int argc, char **argv);
extern int driver_try_compile_via_shu_c_sibling(int argc, char **argv);
extern int runtime_report_precise_parse_failure_if_known(const char *input_path, const char *src, size_t src_len);
extern int runtime_report_parse_recovery_diagnostics(const char *input_path, const char *src, size_t src_len);
extern void driver_unlink_failed_output(const char *out_path);
extern void driver_print_x_smoke_summary(void *module, size_t codegen_len);
extern void driver_print_check_ok(const char *input_path);
extern int driver_c_typeck_entry(void *module, void *arena, const char *src, size_t len);
extern int driver_c_typeck_entry_large_stack(void *module, void *arena, const char *src, size_t len);
extern void driver_diagnostic_after_entry_parse_module(void *module);
extern int driver_check_diag_emitted_get(void);
extern void driver_set_pipeline_entry_source_len(size_t len);
extern void driver_x_pipeline_skip_typeck_set(int v);
extern void driver_x_pipeline_skip_codegen_set(int v);
extern int32_t driver_freestanding_get(void);
extern int32_t parser_diag_token_after_collect_imports(struct xlang_slice_uint8_t *source, void *module);
extern void runtime_diag_errno_path(const char *file, const char *kind, const char *op, const char *path);
extern void runtime_diag_errno_path_pair(const char *file, const char *kind, const char *op, const char *from_path,
                                         const char *to_path);
extern int driver_deps_are_std_core_closure_only(char **dep_paths, int n_deps);
extern void codegen_reset_preamble_skip_mask(void);
extern void codegen_or_preamble_skip_mask(unsigned mask);
#define CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS    1u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_DRIVER_HANDLE  2u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE 4u
#define CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH         8u
/* Cap residual 9.7.1: ABI writers take an opaque fd handle (see
 * xlang_driver_stream_cap.h); the emitted-C stream may be the stdout handle
 * (fd 1) or a temp-file handle. Twin of the seed bodies in
 * runtime/rt_preamble seed and src/runtime.x codegen_emit_include_pipeline_glue_c
 * (authority signature *u8). PLATFORM: SHARED. */
extern int write_io_net_abi_inline(uint8_t *cf);
extern int write_fs_path_map_error_abi_inline(uint8_t *cf);
extern void codegen_emit_include_pipeline_glue_c(uint8_t *out, const char *argv0);
extern int content_has_generic_syntax(const char *content, size_t n);
extern int content_has_compound_assign_syntax(const char *content, size_t n);
extern const char *xlang_entry_lib_name_from_path(const char *path);
extern void xlang_emit_pipeline_glue_include(void);


/* wave1225: release process-wide AST sidecars before free(arena/module).
 * free alone leaves g_arena_sc / g_module_sc used with dangling keys; the next
 * malloc may reuse the same address and reattach stale GrowVec data. That is
 * why single-file `xlang check file.x` is green while batch/directory check
 * truncates large files (e.g. runtime_pipeline_abi num_funcs 363→111).
 * Safe no-op if pointer never registered or already released.
 * PLATFORM: SHARED — cold mono twin of rt_run_compiler_parsed.x rt_cp_release. */
extern void ast_pool_arena_release(void *a);
extern void ast_pool_module_release(void *m);
static void rt_cp_release_arena_module(void *arena, void *module) {
    if (arena) {
        ast_pool_arena_release(arena);
        free(arena);
    }
    if (module) {
        ast_pool_module_release(module);
        free(module);
    }
}

/**
 * argv 已解析后的编译执行：泛型降级、asm/C 分派、pipeline/cc。
 * 由 driver/compile.x 经 driver_run_compiler_dispatch_c 调用。
 */
#ifndef XLANG_RT_RUN_COMPILER_PARSED_FROM_X

int driver_run_compiler_parsed(DriverCompileParsed *p, int argc, char **argv) {
    /* 【Why 根源】-lib-name 仅 C 前端 RUN_CC_FUNC 路径需要（xlang_compile_std_module.sh --bare-impl）；
     * x-pipeline 路径（xlang-x）不编译 std 模块，用 NULL 走 path-based lib_name。 */
    const char *lib_name_override = NULL;
    const char *defines[MAX_DEFINES];
    int ndefines = 0;
    if (argv && argc > 0)
        ndefines = driver_argv_collect_defines(argc, argv, defines, MAX_DEFINES);
    const char *input_path = p->input_path;
    const char *out_path = p->out_path;
    const char **lib_roots_arr = (const char **)p->lib_roots_arr;
    int n_lib_roots = p->n_lib_roots;
    int want_asm_backend = p->want_asm_backend;
    const char *target = p->target;
    const char *opt_level = p->opt_level ? p->opt_level : "2";
    int use_lto = p->use_lto;
    if (!input_path)
        return 1;
    driver_bump_stack_limit();
    /* xlang check：强制走 X pipeline 的 typeck 路径，不做 asm 后端与链接。 */
    if (driver_check_only_get())
        want_asm_backend = 0;
#if defined(XLANG_USE_X_DRIVER) && defined(XLANG_USE_X_PIPELINE)
    /*
     * PLATFORM: SHARED — PC invoke_cc opt-in (2026-08-12): silent generic→C removed.
     * Prior residual: generic syntax on want_exe forced want_asm_backend=0 → host-cc
     * without `-backend c`. Product C is opt-in only (explicit `-backend c` /
     * check-only / emit-c). G.7 cold twin of rt_run_compiler_parsed.x.
     * Default path: X pipeline + asm; no out_path → asm text to stdout;
     * else .o / .s / exe via driver_run_asm_backend.
     */
#if !defined(XLANG_NO_C_FRONTEND)
    /*
     * xlang-c 路径：顶层 import 时 X asm parse 易 0 func，降级 C；xlang_asm（XLANG_NO_C_FRONTEND）须保留 asm + driver_run_asm_backend。
     */
    if (want_asm_backend) {
        XlangRuntimeFileView imp_raw_view;
        if (runtime_read_file_view(input_path, &imp_raw_view) == 0) {
            size_t imp_src_len = 0;
            pipeline_diag_emitted_reset();
            char *imp_src = xlang_preprocess_quiet(imp_raw_view.data, imp_raw_view.length, NULL, 0, &imp_src_len);
            runtime_release_file_view(&imp_raw_view);
            if (imp_src && driver_source_has_top_level_import(imp_src, imp_src_len))
                want_asm_backend = 0;
            free(imp_src);
        }
    }
#endif
    if (want_asm_backend)
        return driver_run_asm_backend(input_path, out_path, lib_roots_arr, n_lib_roots, target, argc, argv);
#endif
    int emit_to_stdout = (out_path == NULL);

    XlangRuntimeFileView raw_src_view;
    if (runtime_read_file_view(input_path, &raw_src_view) != 0) {
        diag_reportf_with_code(input_path, 0, 0, "io error", XLANG_DIAG_CODE_IO_IO001, NULL,
                               "cannot read file '%s'", input_path ? input_path : "?");
        return 1;
    }
    size_t src_len = 0;
    pipeline_diag_emitted_reset();
    /* 必须传入 -D 收集结果；NULL/0 会使 #if FOO 永不成立（run-preprocess 假走 #else）。 */
    char *src = xlang_preprocess_with_path(raw_src_view.data, raw_src_view.length, input_path,
                                          ndefines > 0 ? defines : NULL, ndefines, &src_len);
    runtime_release_file_view(&raw_src_view);
    if (!src && !pipeline_diag_emitted_get()) {
        diag_reportf_with_code(input_path, 0, 0, "preprocess error", XLANG_DIAG_CODE_PREPROCESS_PP002, NULL,
                     "preprocess failed for '%s'", input_path);
        return 1;
    }
    if (!src)
        return 1;
    diag_set_file(input_path, src, src_len);
#if !defined(XLANG_NO_C_FRONTEND)
    /*
     * xlang check：优先 C parse+typeck（支持库模块、import -L）；X pipeline check 待与 compile 对齐后再切回。
     */
    if (driver_check_only_get()) {
        int ck = driver_check_only_c_typeck(input_path, src, lib_roots_arr, n_lib_roots);
        free(src);
        return ck;
    }
    if (emit_to_stdout && !driver_check_only_get()) {
        int smoke_rc = driver_c_frontend_smoke(input_path, src, lib_roots_arr, n_lib_roots);
        free(src);
        return smoke_rc;
    }
#endif
    /* 若预处理后源码含泛型语法，.x 流水线不解析泛型，改走 C 流水线（parse + typeck_module + codegen）以保证 id<i32>(42) 等正确单态化。
     * `-backend c -o`（want_asm_backend=0）：单文件无泛型亦走 C 前端，与 xlang check 对齐（LANG-007 unsafe 等 S0 规则）。
     * 无 import 时内联 C 路径，避免 run_compiler_c 重入导致崩溃；有 import 时仍调 run_compiler_c。 */
#if !defined(XLANG_NO_C_FRONTEND)
    if (content_has_generic_syntax(src, src_len) || out_path) {
        {
            Lexer *lex = lexer_new(src);
            ASTModule *c_mod = NULL;
            int pr = parse(lex, &c_mod);
            lexer_free(lex);
            if (pr != 0 || !c_mod) {
                if (c_mod) ast_module_free(c_mod);
                free(src);
                return 1;
            }
            /*
             * 有 import 时默认回退 .x pipeline；core.* 仅依赖时内联 C 前端（与 run_compiler_c -o 一致），
             * 避免 pipeline codegen 产出 out_len=0。std/用户 dep 仍走 pipeline。
             */
            int c_inline_o = 0;
            if (c_mod->num_imports > 0) {
                if (out_path && driver_c_mod_imports_are_core_only(c_mod))
                    c_inline_o = 1;
                else {
                    ast_module_free(c_mod);
                    /* 不 free(src)，fall through 到 pipeline */
                }
            } else {
                c_inline_o = 1;
            }
            if (c_inline_o) {
            ASTModule *dep_mods[32];
            ASTModule *all_dep_mods[MAX_ALL_DEPS];
            char *all_dep_paths[MAX_ALL_DEPS];
            int ndep = 0, n_all = 0;
            char c_entry_dir[512];
            xlang_get_entry_dir(input_path, c_entry_dir, sizeof(c_entry_dir));
            if (c_mod->num_imports > 0 &&
                xlang_c_resolve_and_load_imports(c_mod, lib_roots_arr, n_lib_roots, c_entry_dir,
                    ndefines > 0 ? defines : NULL, ndefines, 0, dep_mods, &ndep, all_dep_mods, all_dep_paths,
                    NULL, &n_all, MAX_ALL_DEPS) != 0) {
                ast_module_free(c_mod);
                free(src);
                return 1;
            }
            if (!c_mod->main_func || !c_mod->main_func->body) {
                if (driver_check_only_get() && c_mod->num_funcs > 0) {
                    if (typeck_module(c_mod, ndep > 0 ? dep_mods : NULL, ndep, n_all > 0 ? all_dep_mods : NULL, n_all) != 0) {
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return 1;
                    }
                    while (n_all--) {
                        free(all_dep_paths[n_all]);
                        ast_module_free(all_dep_mods[n_all]);
                    }
                    ast_module_free(c_mod);
                    free(src);
                    driver_print_check_ok(input_path);
                    return 0;
                }
                /* LANG-007 v2：库模块 -backend c -o *.o → codegen_library_module_to_c + cc -c。 */
                if (out_path && xlang_output_is_elf_o(out_path) && c_mod->num_funcs > 0) {
                    if (typeck_module(c_mod, ndep > 0 ? dep_mods : NULL, ndep,
                            n_all > 0 ? all_dep_mods : NULL, n_all) != 0) {
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return 1;
                    }
                    codegen_set_preamble_has_core_option_result(0);
                    char tmp_lib[128]; snprintf(tmp_lib, sizeof(tmp_lib), "%ssXXXXXX", XLANG_TMP_PREFIX);
                    int fd_lib = mkstemp(tmp_lib);
                    if (fd_lib < 0) {
                        runtime_diag_errno_path(input_path, "build error", "mkstemp", tmp_lib);
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return 1;
                    }
                    FILE *cf_lib = fdopen(fd_lib, "w");
                    if (!cf_lib) {
                        runtime_diag_errno_path(input_path, "build error", "fdopen", tmp_lib);
                        close(fd_lib);
                        unlink(tmp_lib);
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return 1;
                    }
                    fprintf(cf_lib, "/* generated (library module) */\n");
                    fprintf(cf_lib, "#include <stdint.h>\n");
                    fprintf(cf_lib, "#include <stddef.h>\n");
                    fprintf(cf_lib, "#include <stdlib.h>\n");
                    fprintf(cf_lib, "#include <stdio.h>\n");
                    fprintf(cf_lib, "#include <string.h>\n");
                    fprintf(cf_lib, "#include <math.h>\n");
                    codegen_emit_fmt_json_helpers_once(cf_lib);
                    codegen_emit_builtin_inline_decls(cf_lib);
                    {
                        const char *lib_name = lib_name_override ? lib_name_override : xlang_entry_lib_name_from_path(input_path);
                        if (codegen_library_module_to_c(c_mod, lib_name, ndep > 0 ? dep_mods : NULL,
                                ndep > 0 ? (const char **)c_mod->import_paths : NULL, ndep,
                                cf_lib, NULL, NULL, NULL, NULL, NULL, NULL, 0, input_path) != 0) {
                            fclose(cf_lib);
                            unlink(tmp_lib);
                            while (n_all--) {
                                free(all_dep_paths[n_all]);
                                ast_module_free(all_dep_mods[n_all]);
                            }
                            ast_module_free(c_mod);
                            free(src);
                            return 1;
                        }
                    }
                    fclose(cf_lib);
                    char tmp_lib_c[256];
                    snprintf(tmp_lib_c, sizeof(tmp_lib_c), "%s.c", tmp_lib);
                    if (rename(tmp_lib, tmp_lib_c) != 0) {
                        runtime_diag_errno_path_pair(input_path, "build error", "rename", tmp_lib, tmp_lib_c);
                        unlink(tmp_lib);
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return 1;
                    }
                    {
                        #ifdef _WIN32
        runtime_diag("build error", "fork not supported on Windows", input_path); return -1;
#else
        pid_t cpid = fork();
                        int cc_ok = 0;
                        if (cpid < 0) {
                            runtime_diag_errno_path(input_path, "build error", "fork (cc -c)", out_path);
                            cc_ok = -1;
                        } else if (cpid == 0) {
                            execlp("cc", "cc", "-std=gnu11", "-Wall", "-Wextra", "-c", "-o", (char *)out_path,
                                tmp_lib_c, (char *)NULL);
                            runtime_diag_errno_path(input_path, "build error", "execlp(cc -c)", tmp_lib_c);
                            _exit(127);
                        } else {
                            int status = 0;
                            #endif
                        if (xlang_waitpid_retry(cpid, &status) != 0 ||
                                !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                                diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001,
                                            "cc -c failed for library module", NULL);
                                cc_ok = -1;
                            }
                        }
                        if (cc_ok != 0)
                            diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                                         "cc failed, keeping generated C: %s", tmp_lib_c);
                        else if (!link_abi_getenv("XLANG_KEEP_C"))
                            unlink(tmp_lib_c);
                        while (n_all--) {
                            free(all_dep_paths[n_all]);
                            ast_module_free(all_dep_mods[n_all]);
                        }
                        ast_module_free(c_mod);
                        free(src);
                        return cc_ok == 0 ? 0 : 1;
                    }
                }
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
            diag_report_with_code(NULL, 0, 0, "codegen error", XLANG_DIAG_CODE_CODEGEN_CG001,
                                  "no main function (cannot emit executable)", NULL);
                return 1;
            }
            if (typeck_module(c_mod, ndep > 0 ? dep_mods : NULL, ndep, n_all > 0 ? all_dep_mods : NULL, n_all) != 0) {
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                return 1;
            }
            if (driver_check_only_get()) {
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                driver_print_check_ok(input_path);
                return 0;
            }
            codegen_set_preamble_has_core_option_result(0);
            char tmp[128]; snprintf(tmp, sizeof(tmp), "%ssXXXXXX", XLANG_TMP_PREFIX);
            int fd = mkstemp(tmp);
            if (fd < 0) {
                runtime_diag_errno_path(input_path, "build error", "mkstemp", tmp);
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                return 1;
            }
            FILE *cf = fdopen(fd, "w");
            if (!cf) {
                runtime_diag_errno_path(input_path, "build error", "fdopen", tmp);
                close(fd);
                unlink(tmp);
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                return 1;
            }
            {
                char emitted_type_buf[128][CODEGEN_EMITTED_TYPE_NAME_MAX];
                int n_emitted = 0;
                const int max_emitted = (int)(sizeof(emitted_type_buf) / sizeof(emitted_type_buf[0]));
                if (n_all > 0) {
                    fprintf(cf, "/* generated (single-file with core deps) */\n");
                    fprintf(cf, "#include <stdint.h>\n");
                    fprintf(cf, "#include <stddef.h>\n");
                    fprintf(cf, "#include <stdlib.h>\n");
                    fprintf(cf, "#include <stdio.h>\n");
                    fprintf(cf, "#include <string.h>\n");
                    codegen_emit_builtin_inline_decls(cf);
                    for (int di = 0; di < n_all; di++) {
                        ASTModule *lib_deps[32];
                        const char *lib_dep_paths[32];
                        int n_lib = 0;
                        for (int dj = 0; dj < all_dep_mods[di]->num_imports && n_lib < 32; dj++) {
                            int idx = xlang_find_loaded_import_index(all_dep_mods[di]->import_paths[dj], all_dep_paths, n_all);
                            if (idx >= 0) {
                                lib_deps[n_lib] = all_dep_mods[idx];
                                lib_dep_paths[n_lib] = all_dep_paths[idx];
                                n_lib++;
                            }
                        }
                        if (codegen_library_module_to_c(all_dep_mods[di], all_dep_paths[di], lib_deps, lib_dep_paths, n_lib,
                                cf, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted, NULL) != 0) {
                            fclose(cf);
                            unlink(tmp);
                            while (n_all--) {
                                free(all_dep_paths[n_all]);
                                ast_module_free(all_dep_mods[n_all]);
                            }
                            ast_module_free(c_mod);
                            free(src);
                            return 1;
                        }
                    }
                }
                if (codegen_module_to_c(c_mod, cf, ndep > 0 ? dep_mods : NULL, ndep > 0 ? (const char **)c_mod->import_paths : NULL,
                        ndep, NULL, NULL, NULL, NULL, n_all > 0 ? emitted_type_buf : NULL, n_all > 0 ? &n_emitted : NULL,
                        n_all > 0 ? max_emitted : 0) != 0) {
                    fclose(cf);
                    unlink(tmp);
                    while (n_all--) {
                        free(all_dep_paths[n_all]);
                        ast_module_free(all_dep_mods[n_all]);
                    }
                    ast_module_free(c_mod);
                    free(src);
                    return 1;
                }
            }
            fclose(cf);
            char tmp_c[256];
            snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
            if (rename(tmp, tmp_c) != 0) {
                runtime_diag_errno_path_pair(input_path, "build error", "rename", tmp, tmp_c);
                unlink(tmp);
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                return 1;
            }
            {
                const char *c_paths[1] = { tmp_c };
                const char *io_o = xlang_std_io_o_path(argv[0]); /* F-03：纯 .x，无 io.o */
                const char *fs_o = NULL; /* F-06 v1：纯 .x，invoke_cc 扫描生成 C 按需 -lc */
                const char *process_o = xlang_rel_o_path_from_argv0(argv[0], "std/process/process.o");
                const char *string_o = xlang_rel_o_path_from_argv0(argv[0], "std/string/string.o");
                const char *heap_o = NULL; /* F-06 v1：纯 .x，invoke_cc 按需扫描 std 各 .o 引用 std.heap API 链入 */
                const char *path_o = xlang_rel_o_path_from_argv0(argv[0], "std/path/path.o");
                const char *runtime_o = xlang_rel_o_path_from_argv0(argv[0], "std/runtime/runtime.o");
                const char *runtime_panic_o = xlang_runtime_panic_o_path(argv[0]);
                const char *net_o = xlang_rel_o_path_from_argv0(argv[0], "std/net/net.o");
                const char *thread_o = xlang_rel_o_path_from_argv0(argv[0], "std/thread/thread.o");
                const char *time_o = xlang_rel_o_path_from_argv0(argv[0], "std/time/time.o");
                const char *random_o = xlang_rel_o_path_from_argv0(argv[0], "std/random/random.o");
                const char *env_o = xlang_rel_o_path_from_argv0(argv[0], "std/env/env.o");
                const char *sync_o = xlang_rel_o_path_from_argv0(argv[0], "std/sync/sync.o");
                const char *encoding_o = xlang_rel_o_path_from_argv0(argv[0], "std/encoding/encoding.o");
                const char *base64_o = xlang_rel_o_path_from_argv0(argv[0], "std/base64/base64.o");
                const char *crypto_o = xlang_rel_o_path_from_argv0(argv[0], "std/crypto/crypto.o");
                const char *log_o = xlang_rel_o_path_from_argv0(argv[0], "std/log/log.o");
                const char *atomic_o = xlang_rel_o_path_from_argv0(argv[0], "std/atomic/atomic.o");
                const char *channel_o = xlang_rel_o_path_from_argv0(argv[0], "std/channel/channel.o");
                const char *backtrace_o = xlang_rel_o_path_from_argv0(argv[0], "std/backtrace/backtrace.o");
                const char *hash_o = xlang_rel_o_path_from_argv0(argv[0], "std/hash/hash.o");
                const char *math_o = xlang_rel_o_path_from_argv0(argv[0], "std/math/math.o");
                const char *sort_o = xlang_rel_o_path_from_argv0(argv[0], "std/sort/sort.o");
                const char *ffi_o = xlang_rel_o_path_from_argv0(argv[0], "std/ffi/ffi.o");
                const char *db_o = xlang_rel_o_path_from_argv0(argv[0], "std/db/sqlite/sqlite.o");
                const char *elf_o = xlang_rel_o_path_from_argv0(argv[0], "std/elf/elf.o");
                const char *json_o = xlang_rel_o_path_from_argv0(argv[0], "std/json/json.o");
                const char *csv_o = xlang_rel_o_path_from_argv0(argv[0], "std/csv/csv.o");
                const char *regex_o = xlang_rel_o_path_from_argv0(argv[0], "std/regex/regex.o");
                const char *compress_o = NULL; /* F-06 v1 / F-04 v7：无 compress.o，user .o / 生成 C 按需压缩库 */
                const char *unicode_o = xlang_rel_o_path_from_argv0(argv[0], "std/unicode/unicode.o");
                const char *dynlib_o = xlang_rel_o_path_from_argv0(argv[0], "std/dynlib/dynlib.o");
                const char *http_o = xlang_rel_o_path_from_argv0(argv[0], "std/http/http.o");
                const char *tar_o = xlang_rel_o_path_from_argv0(argv[0], "std/tar/tar.o");
                const char *simd_o = xlang_rel_o_path_from_argv0(argv[0], "std/simd/simd.o");
                const char *context_o = xlang_rel_o_path_from_argv0(argv[0], "std/context/context.o");
                const char *datetime_o = xlang_rel_o_path_from_argv0(argv[0], "std/datetime/datetime.o");
                const char *uuid_o = xlang_rel_o_path_from_argv0(argv[0], "std/uuid/uuid.o");
                const char *url_o = xlang_rel_o_path_from_argv0(argv[0], "std/url/url.o");
                const char *cli_o = xlang_rel_o_path_from_argv0(argv[0], "std/cli/cli.o");
                const char *security_o = xlang_rel_o_path_from_argv0(argv[0], "std/security/security.o");
                const char *config_o = xlang_rel_o_path_from_argv0(argv[0], "std/config/config.o");
                const char *cache_o = xlang_rel_o_path_from_argv0(argv[0], "std/cache/cache.o");
                const char *trace_o = xlang_rel_o_path_from_argv0(argv[0], "std/trace/trace.o");
                const char *task_o = xlang_rel_o_path_from_argv0(argv[0], "std/task/task.o");
                const char *schema_o = xlang_rel_o_path_from_argv0(argv[0], "std/schema/schema.o");
                const char *test_o = xlang_rel_o_path_from_argv0(argv[0], "std/test/test.o");
                /* Single authority (G.3/G.4): push user .o args from argv to cc link line. */
                xlang_invoke_cc_set_user_o_files_from_argv(argc, argv);
                int cc_ret = xlang_invoke_cc(c_paths, 1, out_path, NULL, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, db_o, elf_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, simd_o, context_o, datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o, task_o, schema_o, test_o, xlang_repo_root_from_argv0(argv[0]), NULL);
                xlang_invoke_cc_clear_user_o_files();
                if (cc_ret != 0) {
                    driver_unlink_failed_output(out_path);
                    diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                                 "cc failed, keeping generated C: %s", tmp_c);
                } else if (!link_abi_getenv("XLANG_KEEP_C"))
                    unlink(tmp_c);
                while (n_all--) {
                    free(all_dep_paths[n_all]);
                    ast_module_free(all_dep_mods[n_all]);
                }
                ast_module_free(c_mod);
                free(src);
                return cc_ret == 0 ? 0 : 1;
            }
            }
        }
    }
#else  /* XLANG_NO_C_FRONTEND */
    /*
     * G-06 seed 链仅 X 前端；泛型/trait 由 typeck.x 单态化。
     * 勿在此拒掉（否则 -E asm.x / build_seed_asm_host 无法冷启动 partial）。
     */
#endif /* !XLANG_NO_C_FRONTEND */
    if (link_abi_getenv("XLANG_DUMP_PREP")) {
        if (xlang_write_path_bytes("/tmp/xlang_prep_entry.bin", src, src_len) == 0) {
            diag_reportf(input_path, 0, 0, "note", NULL,
                         "dumped prep entry (%zu bytes) to /tmp/xlang_prep_entry.bin", src_len);
        }
    }
    size_t arena_sz = pipeline_sizeof_arena();
    size_t module_sz = pipeline_sizeof_module();
    void *arena = malloc(arena_sz);
    void *module = malloc(module_sz);
    if (!arena || !module) {
        rt_cp_release_arena_module(arena, module);
        free(src);
        return 1;
    }
    memset(arena, 0, arena_sz);
    memset(module, 0, module_sz);
    struct xlang_slice_uint8_t src_slice = { (uint8_t *)src, src_len }; /* 仅 diagnostics，入口解析必须与 pipeline 一致走 parse_into_buf */
    if (src_len > (size_t)INT32_MAX) {
        diag_reportf_with_code(input_path, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP007, NULL,
                               "entry source too large for parser (>%d bytes): '%s'",
                               INT32_MAX, input_path ? input_path : "?");
        rt_cp_release_arena_module(arena, module);
        free(src);
        return 1;
    }
    parser_parse_into_init(module, arena);
    struct parser_ParseIntoResult pr = parser_parse_into_buf(arena, module, (uint8_t *)src, (int32_t)src_len);
    if (pr.ok != 0) {
        if (runtime_report_precise_parse_failure_if_known(input_path, src, src_len)) {
            rt_cp_release_arena_module(arena, module);
            free(src);
            return 1;
        }
        /* multi-error recovery 诊断（check/run-parser 闸门） */
        if (runtime_report_parse_recovery_diagnostics(input_path, src, src_len) > 0) {
            rt_cp_release_arena_module(arena, module);
            free(src);
            return 1;
        }
        diag_reportf_with_code(input_path, 0, 0, "parse error", XLANG_DIAG_CODE_PARSE_P001, NULL,
                     "parse failed for '%s' (pr.ok=%d main_idx=%d)",
                     input_path, (int)pr.ok, (int)pr.main_idx);
        {
            int32_t first_tok = parser_diag_token_after_collect_imports(&src_slice, module);
            diag_reportf(input_path, 0, 0, "note", NULL,
                         "first_token_after_imports=%d (1=TOKEN_FUNCTION)", (int)first_tok);
        }
        if (src_len > 0 && src_len < 200)
            diag_reportf(input_path, 0, 0, "note", NULL,
                         "src_len=%zu first_bytes=%.*s",
                         src_len, (int)(src_len > 60 ? 60 : src_len), src);
        rt_cp_release_arena_module(arena, module);
        free(src);
        return 1;
    }
    parser_parse_into_set_main_index(module, pr.main_idx);
    int32_t n_imports = parser_get_module_num_imports(module);
    if (link_abi_getenv("XLANG_DEBUG_PIPE"))
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "pipeline debug: driver post-parse_into_buf num_funcs=%d n_imports=%d pr_ok=%d pr_main_idx=%d src_len=%zu",
                     driver_get_module_num_funcs(module), (int)n_imports, (int)pr.ok, (int)pr.main_idx, src_len);
    char entry_dir_buf[512];
    xlang_get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
    if (n_imports > 0)
        pipeline_set_entry_dir(entry_dir_buf);

    char *dep_sources[MAX_ALL_DEPS];
    size_t dep_lens[MAX_ALL_DEPS];
    char *dep_paths[MAX_ALL_DEPS];
    int n_deps = 0;
    if (n_imports > 0 && n_imports <= 32) {
        if (xlang_collect_deps_transitive(module, arena_sz, module_sz, lib_roots_arr, n_lib_roots, entry_dir_buf, defines,
                ndefines, dep_sources, dep_lens, dep_paths, &n_deps) != 0) {
            rt_cp_release_arena_module(arena, module);
            free(src);
            return 1;
        }
        if (link_abi_getenv("XLANG_DEBUG_PIPE")) {
            diag_reportf(NULL, 0, 0, "note", NULL,
                         "pipeline debug: n_deps=%d", n_deps);
            for (int dj = 0; dj < n_deps; dj++)
                diag_reportf(NULL, 0, 0, "note", NULL,
                             "pipeline debug: dep[%d]=%s", dj, dep_paths[dj] ? dep_paths[dj] : "?");
        }
    }
    typeck_ndep_store((int32_t)(0));
    /* 模板末尾须为 6 个 X，mkstemp 后重命名为 .c 以便 cc/ld 识别 */
    char tmp[128]; snprintf(tmp, sizeof(tmp), "%sxlang_x.XXXXXX", XLANG_TMP_PREFIX);
    char tmp_c[256];
    int fd = -1;
    /* Cap residual 9.7.1: opaque fd handle (stdout handle or temp-file handle);
     * NULL = not opened. PLATFORM: SHARED. */
    uint8_t *cf;
    if (emit_to_stdout) {
        cf = xlang_driver_handle_from_fd(1);
    } else {
        fd = mkstemp(tmp);
        if (fd < 0) {
            runtime_diag_errno_path(input_path, "build error", "mkstemp", tmp);
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
        /* PLATFORM: WINDOWS | POSIX — close fd BEFORE rename; Windows forbids
         * renaming a file held open (POSIX allows it). Reopen after rename. */
        close(fd);
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            runtime_diag_errno_path_pair(input_path, "build error", "rename", tmp, tmp_c);
            unlink(tmp);
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
        /* Cap residual 9.7.1: fopen(tmp_c, "w") → Cap open_write (create/truncate)
         * wrapped as an opaque fd handle. PLATFORM: SHARED. */
        {
            int cf_fd = xlang_io_open_write(tmp_c);
            cf = cf_fd < 0 ? NULL : xlang_driver_handle_from_fd(cf_fd);
        }
        if (!cf) {
            runtime_diag_errno_path(input_path, "build error", "fopen", tmp_c);
            unlink(tmp_c);
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
    }
    /*
     * CodegenOutBuf / PipelineDepCtx 体积大；driver_run_compiler_full 与 run_compiler_x_path 同理，先 dep 再堆上分配二者。
     */
    void *dep_arenas[32];
    void *dep_modules[32];
    for (int j = n_deps - 1; j >= 0; j--) {
        dep_arenas[j] = malloc(arena_sz);
        dep_modules[j] = malloc(module_sz);
        if (!dep_arenas[j] || !dep_modules[j]) {
            diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP005,
                                  ".x path dependency allocation failed", NULL);
            while (j > 0) { j--; rt_cp_release_arena_module(dep_arenas[j], dep_modules[j]); }
            if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
        memset(dep_arenas[j], 0, arena_sz);
        memset(dep_modules[j], 0, module_sz);
    }
    struct codegen_CodegenOutBuf *out_buf = (struct codegen_CodegenOutBuf *)calloc(1, sizeof(*out_buf));
    struct ast_PipelineDepCtx *pctx = (struct ast_PipelineDepCtx *)calloc(1, sizeof(*pctx));
    if (!out_buf || !pctx) {
        diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP006,
                              ".x path output/context allocation failed", NULL);
        for (int jj = 0; jj < n_deps; jj++) { rt_cp_release_arena_module(dep_arenas[jj], dep_modules[jj]); }
        if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
        while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
        rt_cp_release_arena_module(arena, module); free(src);
        if (out_buf) free(out_buf);
        if (pctx) pipeline_dep_ctx_heap_destroy(pctx);
        return 1;
    }
    xlang_pipeline_fill_ctx_path_buffers(pctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
    xlang_pipeline_pctx_seed_dep_slots(pctx, dep_modules, dep_arenas, dep_paths, n_deps);
    pctx->skip_codegen_dep_0 = 0; /* 不再跳过 dep 0：io.o 仅提供 C 层，std.io.driver 的 .x 包装须由 codegen 生成。 */
    /*
     * 【Why 根源】入口模块 codegen 前必须设置 current_codegen_prefix_mirror，否则 codegen
     *   通过 codegen_emit_prefix_len_from_ctx(ctx) 读到空 prefix，库模块函数被发射为裸符号
     *   （core_mem_placeholder → placeholder），调用端期望带前缀符号 → undefined reference。
     *   与 runtime.from_x.c driver_run_compiler_c L5506-5520 完全对称（单一权威路径）。
     * 【Invariant】lib_name 非空且 len ∈ [1,62] → prefix = lib_name + '_'（trailing underscore
     *   匹配 codegen_import_path_to_c_prefix_into 行为）；否则 prefix 保持空（入口模块无前缀）。
     * 【Perf】单次 strlen + memcpy，pipeline 调用前一次性设置，无热路径开销。
     */
    {
        extern const char *xlang_entry_lib_name_from_path(const char *path);
        const char *lib_name = xlang_entry_lib_name_from_path(input_path);
        if (lib_name && lib_name[0]) {
            int32_t plen = (int32_t)strlen(lib_name);
            if (plen > 0 && plen < 63) {
                memcpy(pctx->current_codegen_prefix_mirror, lib_name, (size_t)plen);
                pctx->current_codegen_prefix_mirror[plen] = '_';  /* trailing underscore */
                pctx->current_codegen_prefix_mirror[plen + 1] = 0;
                pctx->current_codegen_prefix_len = plen + 1;
                /* Pin entry prefix: dep codegen overwrites current_* only. */
                memcpy(pctx->entry_module_import_path_mirror, lib_name, (size_t)plen);
                pctx->entry_module_import_path_mirror[plen] = '_';
                pctx->entry_module_import_path_mirror[plen + 1] = 0;
                pctx->entry_module_import_path_len = plen + 1;
            }
        }
    }
    /*
     * 先对每个 dep 跑 parse+typecheck（逆拓扑序，与 emit-C 2104 / asm 1186 一致）。
     * 勿用正序多轮 prerun：coff→[elf,codegen,ast] 时正序先编 elf 导致 import 槽未就绪 ec=-5。
     */
    driver_dep_seeded_clear_all();
    for (int j = n_deps - 1; j >= 0; j--) {
        struct ast_PipelineDepCtx *one_ctx = (struct ast_PipelineDepCtx *)calloc(1, sizeof(*one_ctx));
        struct codegen_CodegenOutBuf *dep_out = (struct codegen_CodegenOutBuf *)calloc(1, sizeof(*dep_out));
        int ec_dep;
        if (!one_ctx || !dep_out) {
            diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP006,
                                  ".x path dependency context/output allocation failed", NULL);
            pipeline_dep_ctx_heap_destroy(one_ctx);
            free(dep_out);
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            for (int k = 0; k < n_deps; k++) { rt_cp_release_arena_module(dep_arenas[k], dep_modules[k]); }
            if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
        xlang_pipeline_fill_ctx_path_buffers(one_ctx, xlang_dep_prerun_entry_dir(entry_dir_buf, lib_roots_arr, n_lib_roots),
                                            lib_roots_arr, n_lib_roots);
        xlang_pipeline_one_ctx_for_dep_prerun(one_ctx, j, dep_modules, dep_arenas, dep_paths, n_deps,
            (const uint8_t *)dep_sources[j], dep_lens[j]);
        driver_set_current_dep_path_for_codegen(dep_paths[j]);
        /*
         * std/core 闭包 dep 仅 parse 填 import 槽；全量 dep_prerun typeck 在 strict 链上对 std.base64 等易 SIGSEGV。
         * xlang check（stage1）：dep 一律 parse-only，避免 typeck_only 在大 std 子模块上 SIGSEGV。
         * 用户 multi-file（need_coemit）仍走 parse+typeck。
         */
        if (driver_check_only_get() ||
            xlang_asm_user_std_dep_skip_x_typeck(dep_paths[j]) ||
            driver_deps_are_std_core_closure_only(dep_paths, n_deps)) {
            ec_dep = xlang_pipeline_dep_prerun_parse_only(dep_modules[j], dep_arenas[j],
                (const uint8_t *)dep_sources[j], dep_lens[j]);
        } else {
            ec_dep = xlang_pipeline_dep_prerun_typeck_only(dep_modules[j], dep_arenas[j],
                (const uint8_t *)dep_sources[j], dep_lens[j], (void *)dep_out, (void *)one_ctx);
        }
        driver_set_current_dep_path_for_codegen(NULL);
        pipeline_dep_ctx_heap_destroy(one_ctx);
        free(dep_out);
        if (ec_dep != 0) {
            diag_reportf_with_code(dep_paths[j], 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP008, NULL,
                                   "pipeline failed for import '%s' (dep prerun rc=%d)",
                                   dep_paths[j] ? dep_paths[j] : "?", ec_dep);
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            for (int k = 0; k < n_deps; k++) { rt_cp_release_arena_module(dep_arenas[k], dep_modules[k]); }
            if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module); free(src);
            return 1;
        }
        driver_dep_publish_slot(j, dep_arenas[j], dep_modules[j], dep_paths[j]);
    }
    typeck_ndep_store((int32_t)(n_deps));
    for (int j = 0; j < n_deps; j++) {
        typeck_dep_module_set((int32_t)(j), dep_modules[j]);
        typeck_dep_arena_set((int32_t)(j), dep_arenas[j]);
    }
    pipeline_set_dep_slots(dep_arenas, dep_modules);
    driver_dep_seed_slots(dep_arenas, dep_modules, n_deps);
    codegen_set_dep_slots_for_x_pipeline((struct ASTModule **)dep_modules, (const char **)dep_paths, n_deps);
    codegen_set_preamble_has_core_option_result(1); /* preamble 已含 Option_i32/Result_i32，codegen 跳过避免重定义 */
    codegen_reset_preamble_skip_mask();
    {
        int has_std_io_core = 0;
        int has_std_io_driver = 0;
        for (int j = 0; j < n_deps; j++) {
            if (dep_paths[j] && strcmp(dep_paths[j], "std.io.core") == 0) has_std_io_core = 1;
            if (dep_paths[j] && strcmp(dep_paths[j], "std.io.driver") == 0) has_std_io_driver = 1;
        }
        if (!has_std_io_core)
            codegen_or_preamble_skip_mask(CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS
                | CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE);
        if (has_std_io_driver)
            codegen_or_preamble_skip_mask(CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH);
    }
    /*
     * emit-C 与 -backend asm 对齐：pipeline 内须完整 parse_into（entry_already_parsed=0）。
     * driver 侧 parse_into_buf 仅用于 collect_deps / pr.main_idx；若此处设置 entry_already_parsed=1
     * 跳过流水线解析，预填 module 与 pipeline 内 struct_layouts/typeck §11.1 等路径不同步时，
     * 隐式 padding 校验会变成空操作（tests/run-struct.sh padding_no_allow）。
     * import 已解析完毕；清零后 pipeline 从同一预处理源码重建 module/arena。
     */
    if (link_abi_getenv("XLANG_DEBUG_PIPE"))
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "pipeline debug: before entry memset arena_sz=%zu", arena_sz);
    /* wave1225: drop first-pass sidecar GrowVecs before reusing the same
     * arena/module heap for pipeline re-parse. parse_into_init resets lens when
     * a sidecar still matches, but release+recreate is the authoritative clean
     * slate (and pairs with free-path release-before-free above). */
    if (arena)
        ast_pool_arena_release(arena);
    if (module)
        ast_pool_module_release(module);
    memset(arena, 0, arena_sz);
    memset(module, 0, module_sz);
    parser_parse_into_init(module, arena);
    pctx->entry_already_parsed = 0;
    if (n_deps > 0 && !driver_check_only_get() && want_asm_backend &&
        driver_deps_are_std_core_closure_only(dep_paths, n_deps))
        pctx->asm_entry_module_only = 1;
    if (link_abi_getenv("XLANG_DEBUG_PIPE"))
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "pipeline debug: before pipeline_run entry=%s src_len=%zu",
                     input_path ? input_path : "?", (size_t)src_slice.length);
#if !defined(XLANG_NO_C_FRONTEND)
    if (n_deps > 0 && !driver_check_only_get() &&
        driver_deps_are_std_core_closure_only(dep_paths, n_deps)) {
        if (driver_c_typeck_entry_large_stack(input_path, src, lib_roots_arr, n_lib_roots, 0) != 0) {
            driver_x_pipeline_skip_typeck_set(0);
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            for (int k = 0; k < n_deps; k++) { rt_cp_release_arena_module(dep_arenas[k], dep_modules[k]); }
            if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            rt_cp_release_arena_module(arena, module);
            free(src);
            return 1;
        }
    }
#endif
    /*
     * PLATFORM: SHARED — xlang check (NO_C_FRONTEND product xlang_asm).
     * Do **not** print_ok + return before the pipeline when deps are a
     * std/core closure. That skip false-greened al06 (`allocator region
     * escape`) because entry typeck never ran. Dep prerun above is already
     * parse-only when check_only (the SIGSEGV guard for sys/fs/heap mods).
     * Fall through: pipeline typechecks the **entry** and skips codegen
     * when driver_check_only_get(). Twin: rt_cp_step_pipeline in
     * src/runtime/rt_run_compiler_parsed.x (product PREFER authority).
     */
    int ec = xlang_pipeline_run_x_pipeline_large_stack(module, arena, src_slice.data, (size_t)src_slice.length, (void *)out_buf, (void *)pctx);
    driver_x_pipeline_skip_typeck_set(0);
    if (link_abi_getenv("XLANG_DEBUG_PIPE"))
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "pipeline debug: after pipeline_run ec=%d", ec);
    driver_dep_seeded_clear_all();
    codegen_set_dep_slots_for_x_pipeline(NULL, NULL, 0);
    for (int j = n_deps - 1; j >= 0; j--) { rt_cp_release_arena_module(dep_arenas[j], dep_modules[j]); }
    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
    if (ec != 0 || (!driver_check_only_get() && out_buf->length == 0)) {
        diag_reportf_with_code(input_path, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP003, NULL,
                     "pipeline failed for '%s' (ec=%d, out_len=%d)",
                     input_path, ec, (int)out_buf->length);
        if (link_abi_getenv("XLANG_DEBUG_PIPE") && out_buf->length > 0) {
            size_t show = (size_t)out_buf->length > 800u ? 800u : (size_t)out_buf->length;
            diag_reportf(NULL, 0, 0, "note", NULL,
                         "pipeline debug: out (first %zu bytes):\n%.*s", show, (int)show,
                         (const char *)out_buf->data);
        }
        if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
        rt_cp_release_arena_module(arena, module);
        free(src);
        free(out_buf);
        pipeline_dep_ctx_heap_destroy(pctx);
        return 1;
    }
    if (driver_check_only_get()) {
        int nfuncs_ck = driver_get_module_num_funcs(module);
        int rec_n = 0;
        int fail_ck = 0;
        /* Why: check_only verifies syntax + types, not function presence.
         * Parse succeeded (pr.ok == 0) reaching here. Empty modules (comment-only
         * skeleton files, declaration-only files) are syntactically valid.
         * Only flag failure when parse recovery found real syntax errors. */
        rec_n = runtime_report_parse_recovery_diagnostics(input_path, src, src_len);
        if (rec_n > 0)
            fail_ck = 1;
        /* nfuncs_ck <= 0 with rec_n <= 0: empty module, not an error. */
        if (driver_check_diag_emitted_get())
            fail_ck = 1;
        if (fail_ck) {
            if (!emit_to_stdout) {
                xlang_driver_handle_close(cf);
                unlink(tmp_c);
            }
            rt_cp_release_arena_module(arena, module);
            free(src);
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            return 1;
        }
        driver_print_check_ok(input_path);
        if (!emit_to_stdout) {
            xlang_driver_handle_close(cf);
            unlink(tmp_c);
        }
        rt_cp_release_arena_module(arena, module);
        free(src);
        free(out_buf);
        pipeline_dep_ctx_heap_destroy(pctx);
        return 0;
    }
    /* 无 -o、将生成的 C 写 stdout 之前：stderr 烟测两行，与 driver_run_x_emit_x 及 run-std/run-stdlib-import 的 grep 一致。 */
    if (emit_to_stdout)
        driver_print_x_smoke_summary(module, (size_t)out_buf->length);
    rt_cp_release_arena_module(arena, module);
    free(src);
    {
        /* 内联 std.io / std.net / fs / path / map / error ABI；不再 #include std/*_abi.h。
         * 若 pipeline 产出首字符非 # 且非注释（如泛型+import 时首行为 extern ...），先写最小 preamble 避免 cc 报 unknown type 'int32_t'。 */
        size_t first_line = 0;
        while (first_line < (size_t)out_buf->length && out_buf->data[first_line] != '\n') first_line++;
        if (first_line < (size_t)out_buf->length) first_line++;
        int need_preamble = (out_buf->length > 0 && out_buf->data[0] != '#' && (out_buf->length < 2 || out_buf->data[0] != '/' || out_buf->data[1] != '*'));
        if (need_preamble) {
            static const char min_preamble[] = "/* generated */\n#include <stdint.h>\n#include <stddef.h>\n#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n";
            if (xlang_io_write(xlang_driver_handle_to_fd(cf), min_preamble,
                               sizeof(min_preamble) - 1) != (long)(sizeof(min_preamble) - 1)) {
                if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
                free(out_buf);
                pipeline_dep_ctx_heap_destroy(pctx);
                return 1;
            }
        }
        if (xlang_io_write(xlang_driver_handle_to_fd(cf), out_buf->data, first_line) != (long)first_line
            || write_io_net_abi_inline(cf) != 0
            || write_fs_path_map_error_abi_inline(cf) != 0
            || xlang_io_write(xlang_driver_handle_to_fd(cf), out_buf->data + first_line,
                              (size_t)out_buf->length - first_line) != (long)((size_t)out_buf->length - first_line)) {
            if (!emit_to_stdout) { xlang_driver_handle_close(cf); unlink(tmp_c); }
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            return 1;
        }
    }
        if (!emit_to_stdout) {
            if (xlang_driver_handle_close(cf) != 0) {
            unlink(tmp_c);
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            return 1;
        }
        {
            const char *c_paths[1] = { tmp_c };
            const char *io_o = xlang_std_io_o_path(argv[0]); /* F-03：纯 .x，无 io.o */
            const char *fs_o = NULL; /* F-06 v1：纯 .x，invoke_cc 扫描生成 C 按需 -lc */
            const char *process_o = xlang_rel_o_path_from_argv0(argv[0], "std/process/process.o");
            const char *string_o = xlang_rel_o_path_from_argv0(argv[0], "std/string/string.o");
            const char *heap_o = NULL; /* F-06 v1：纯 .x，invoke_cc 按需扫描 std 各 .o 引用 std.heap API 链入 */
            const char *path_o = xlang_rel_o_path_from_argv0(argv[0], "std/path/path.o");
            const char *runtime_o = xlang_rel_o_path_from_argv0(argv[0], "std/runtime/runtime.o");
            const char *runtime_panic_o = xlang_runtime_panic_o_path(argv[0]);
            const char *net_o = xlang_rel_o_path_from_argv0(argv[0], "std/net/net.o");
            const char *thread_o = xlang_rel_o_path_from_argv0(argv[0], "std/thread/thread.o");
            const char *time_o = xlang_rel_o_path_from_argv0(argv[0], "std/time/time.o");
            const char *random_o = xlang_rel_o_path_from_argv0(argv[0], "std/random/random.o");
            const char *env_o = xlang_rel_o_path_from_argv0(argv[0], "std/env/env.o");
            const char *sync_o = xlang_rel_o_path_from_argv0(argv[0], "std/sync/sync.o");
            const char *encoding_o = xlang_rel_o_path_from_argv0(argv[0], "std/encoding/encoding.o");
            const char *base64_o = xlang_rel_o_path_from_argv0(argv[0], "std/base64/base64.o");
            const char *crypto_o = xlang_rel_o_path_from_argv0(argv[0], "std/crypto/crypto.o");
            const char *log_o = xlang_rel_o_path_from_argv0(argv[0], "std/log/log.o");
            const char *atomic_o = xlang_rel_o_path_from_argv0(argv[0], "std/atomic/atomic.o");
            const char *channel_o = xlang_rel_o_path_from_argv0(argv[0], "std/channel/channel.o");
            const char *backtrace_o = xlang_rel_o_path_from_argv0(argv[0], "std/backtrace/backtrace.o");
            const char *hash_o = xlang_rel_o_path_from_argv0(argv[0], "std/hash/hash.o");
            const char *math_o = xlang_rel_o_path_from_argv0(argv[0], "std/math/math.o");
            const char *sort_o = xlang_rel_o_path_from_argv0(argv[0], "std/sort/sort.o");
            const char *ffi_o = xlang_rel_o_path_from_argv0(argv[0], "std/ffi/ffi.o");
            const char *db_o = xlang_rel_o_path_from_argv0(argv[0], "std/db/sqlite/sqlite.o");
            const char *elf_o = xlang_rel_o_path_from_argv0(argv[0], "std/elf/elf.o");
            const char *json_o = xlang_rel_o_path_from_argv0(argv[0], "std/json/json.o");
            const char *csv_o = xlang_rel_o_path_from_argv0(argv[0], "std/csv/csv.o");
            const char *regex_o = xlang_rel_o_path_from_argv0(argv[0], "std/regex/regex.o");
            const char *compress_o = NULL; /* F-06 v1 / F-04 v7：无 compress.o，user .o / 生成 C 按需压缩库 */
            const char *unicode_o = xlang_rel_o_path_from_argv0(argv[0], "std/unicode/unicode.o");
            const char *dynlib_o = xlang_rel_o_path_from_argv0(argv[0], "std/dynlib/dynlib.o");
            const char *http_o = xlang_rel_o_path_from_argv0(argv[0], "std/http/http.o");
            const char *tar_o = xlang_rel_o_path_from_argv0(argv[0], "std/tar/tar.o");
            const char *simd_o = xlang_rel_o_path_from_argv0(argv[0], "std/simd/simd.o");
            const char *context_o = xlang_rel_o_path_from_argv0(argv[0], "std/context/context.o");
            const char *datetime_o = xlang_rel_o_path_from_argv0(argv[0], "std/datetime/datetime.o");
            const char *uuid_o = xlang_rel_o_path_from_argv0(argv[0], "std/uuid/uuid.o");
            const char *url_o = xlang_rel_o_path_from_argv0(argv[0], "std/url/url.o");
            const char *cli_o = xlang_rel_o_path_from_argv0(argv[0], "std/cli/cli.o");
            const char *security_o = xlang_rel_o_path_from_argv0(argv[0], "std/security/security.o");
            const char *config_o = xlang_rel_o_path_from_argv0(argv[0], "std/config/config.o");
            const char *cache_o = xlang_rel_o_path_from_argv0(argv[0], "std/cache/cache.o");
            const char *trace_o = xlang_rel_o_path_from_argv0(argv[0], "std/trace/trace.o");
            const char *task_o = xlang_rel_o_path_from_argv0(argv[0], "std/task/task.o");
            const char *schema_o = xlang_rel_o_path_from_argv0(argv[0], "std/schema/schema.o");
            const char *test_o = xlang_rel_o_path_from_argv0(argv[0], "std/test/test.o");
            /* Single authority (G.3/G.4): push user .o args from argv to cc link line. */
            xlang_invoke_cc_set_user_o_files_from_argv(argc, argv);
            int cc_ret = xlang_invoke_cc(c_paths, 1, out_path, NULL, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, path_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, db_o, elf_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, simd_o, context_o, datetime_o, uuid_o, url_o, cli_o, security_o, config_o, cache_o, trace_o, task_o, schema_o, test_o, xlang_repo_root_from_argv0(argv[0]), NULL);
            xlang_invoke_cc_clear_user_o_files();
            if (cc_ret != 0) {
                driver_unlink_failed_output(out_path);
                diag_reportf_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, NULL,
                             "cc failed, keeping generated C: %s", tmp_c);
            } else if (!link_abi_getenv("XLANG_KEEP_C")) {
                unlink(tmp_c);
            } else {
                diag_reportf(NULL, 0, 0, "note", NULL,
                             "kept generated C: %s", tmp_c);
            }
            free(out_buf);
            pipeline_dep_ctx_heap_destroy(pctx);
            return cc_ret == 0 ? 0 : 1;
        }
    }
    free(out_buf);
    pipeline_dep_ctx_heap_destroy(pctx);
    return 0;
}

#else /* XLANG_RT_RUN_COMPILER_PARSED_FROM_X：产品 rest 仅 marker；业务体在 full .x */
int driver_run_compiler_parsed(DriverCompileParsed *p, int argc, char **argv);
#endif /* XLANG_RT_RUN_COMPILER_PARSED_FROM_X */


int labi_rt_run_compiler_parsed_slice_marker(void) {
  return 1;
}
