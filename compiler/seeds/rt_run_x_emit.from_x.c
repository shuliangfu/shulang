/* seeds/rt_run_x_emit.from_x.c — G-02f-314 P2 runtime rest (-x -E emit)
 * Logic source: src/runtime/rt_run_x_emit.x
 * Hybrid: XLANG_RT_RUN_X_EMIT_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：公共业务符号 driver_run_x_emit_c 由 full .x 提供；
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual（driver_abi）：stdout/OutBuf/指针表/parse/diag/typeck/work 槽。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 *
 * Scope: driver_run_x_emit_c（读源 → pipeline → stdout）。
 * Leftover !XLANG_NO_C_FRONTEND -E-extern cparser branch retired
 * (this knife). Product PREFER already refuses via
 * driver_x_emit_try_extern_via_cparser (always BLD001). Mega wrapper
 * of driver_run_x_emit_c_extern_via_cparser stays (never-defined
 * _impl; different class).
 * run_asm_backend / run_compiler_parsed 仍 mega rest。
 */
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diag.h"
#include "runtime_diag_codes.h"
#include "runtime_io_abi.h"
#include "runtime_driver_abi.h"
#include "xlang_driver_stream_cap.h" /* Cap residual 9.7.1: opaque FILE* face → fd-handle face */
#include "runtime_pipeline_abi.h"
#include "token.h"

#ifndef X_EMIT_MAX_LIB_ROOTS
#define X_EMIT_MAX_LIB_ROOTS 16
#endif
#ifndef MAX_ALL_DEPS
#define MAX_ALL_DEPS 128
#endif
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef XLANG_RT_RUN_X_EMIT_FROM_X

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

extern const char *driver_x_emit_c_path;
extern int driver_x_emit_c_want_extern;
extern int driver_x_emit_n_lib_roots;
extern const char *driver_x_emit_lib_roots[X_EMIT_MAX_LIB_ROOTS];

extern char *xlang_preprocess_with_path(const char *data, size_t len, const char *path, const char **defines, int n_defines, size_t *out_len);
extern char *xlang_preprocess(const char *data, size_t len, const char **defines, int n_defines, size_t *out_len);
extern void pipeline_diag_emitted_reset(void);
extern int pipeline_diag_emitted_get(void);
extern void diag_set_file(const char *path, const char *src, size_t len);
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_module(void);
extern void parser_parse_into_init(void *arena, void *module);
extern struct parser_ParseIntoResult parser_parse_into_buf(void *arena, void *module, uint8_t *data, int32_t len);
extern void parser_parse_into_set_main_index(void *module, int32_t main_idx);
extern int driver_get_module_num_funcs(void *m);
extern int32_t parser_diag_fail_at_token_kind(struct xlang_slice_uint8_t *source);
extern int32_t parser_get_module_num_imports(void *module);
extern void xlang_get_entry_dir(const char *path, char *out, size_t out_sz);
extern void pipeline_set_entry_dir(const char *dir);
extern int driver_x_emit_asm_direct_import_only(const char *input_path);
extern int driver_x_emit_asm_dep_parse_only_ok(const char *input_path, const char *dep_path);
extern int driver_x_emit_asm_dep_parse_skip_typeck_ok(const char *input_path, const char *dep_path);
/* wave77: G.7 accessors only — pure owns typeck_dep BSS under hybrid; no naked C globals. */
extern void typeck_ndep_store(int32_t n);
extern void typeck_dep_module_set(int32_t i, void *mod);
extern void typeck_dep_arena_set(int32_t i, void *arena);
extern void driver_dep_seeded_clear_all(void);
extern void driver_set_current_dep_path_for_codegen(const char *path);
extern int xlang_pipeline_dep_prerun_parse_skip_typeck(void *mod, void *arena, const uint8_t *src, size_t len, void *out, void *ctx);
extern int xlang_pipeline_dep_prerun_parse_only(void *mod, void *arena, const uint8_t *src, size_t len);
extern int xlang_pipeline_dep_prerun_typeck_only(void *mod, void *arena, const uint8_t *src, size_t len, void *out, void *ctx);
extern void driver_dep_publish_slot(int j, void *arena, void *module, const char *path);
extern void pipeline_set_dep_slots(void **arenas, void **modules);
extern void driver_dep_seed_slots(void **arenas, void **modules, int n);
extern void codegen_set_dep_slots_for_x_pipeline(struct ASTModule **mods, const char **paths, int n);
extern int runtime_report_precise_parse_failure_if_known(const char *input_path, const char *src, size_t src_len);
extern void pipeline_dep_ctx_heap_destroy(struct ast_PipelineDepCtx *ctx);
extern int typeck_set_allow_legacy_extern_calls(int allow);
/**
 * Release GrowVec data buffers backing the arena/module sidecar pools.
 * Declared with `void *` params to avoid pulling struct definitions here;
 * runtime_pipeline_abi defines them with `struct ast_ASTArena *` /
 * `struct ast_Module *` which are pointer-compatible (ast_pool.c left wave309).
 * Safe no-op if no sidecar slot matches.
 * PLATFORM: SHARED — see runtime_pipeline_abi arena_sidecar_free / module_sidecar_free.
 */
extern void ast_pool_arena_release(void *arena);
extern void ast_pool_module_release(void *module);

/** Run parsed -x -E (read file, .x pipeline, write stdout); 0 ok, 1 fail.
 * Leftover !XLANG_NO_C_FRONTEND -E-extern cparser branch retired (this knife).
 * Product PREFER rt_run_x_emit.x already refuses via
 * driver_x_emit_try_extern_via_cparser (always BLD001).
 * PLATFORM: SHARED — consume-site hygiene; product PREFER rest is FROM_X
 * marker (H=0); this body compiles only on cold/no-PREFER.
 */
int driver_run_x_emit_c(void) {
    const char *input_path = driver_x_emit_c_path;
    int old_allow_legacy_extern = 0;
    driver_x_emit_c_path = NULL;
    if (!input_path) return 1;
    /* LANG-007：-E 路径允许裸 extern（与 mega runtime 同意图） */
    old_allow_legacy_extern = typeck_set_allow_legacy_extern_calls(1);
#ifdef XLANG_USE_X_PIPELINE
    {
        /* Cap residual 9.7.1: emitted C goes out through raw fd writes
         * (xlang_io_write), which are unbuffered — no stdio setvbuf needed. */
#if defined(XLANG_USE_X_DRIVER) && defined(XLANG_USE_X_PIPELINE)
        {
            const int want_extern = driver_x_emit_c_want_extern;
            driver_x_emit_c_want_extern = 0;
            if (want_extern) {
                /*
                 * Retired leftover !XLANG_NO_C_FRONTEND -E-extern cparser
                 * branch (this knife): used to call
                 * driver_run_x_emit_c_extern_via_cparser. Product PREFER
                 * rt_run_x_emit.x always refuses via
                 * driver_x_emit_try_extern_via_cparser (BLD001). Mega
                 * wrapper of via_cparser stays (never-defined _impl;
                 * different class). Dropping XLANG_NO_C_FRONTEND now
                 * matches that refuse; it does not resurrect a C frontend.
                 * PLATFORM: SHARED — consume-site hygiene; product PREFER
                 * rest is FROM_X marker (H=0); this body compiles only on
                 * cold/no-PREFER.
                 */
                int r = (int)driver_x_emit_try_extern_via_cparser((uint8_t *)input_path);
                typeck_set_allow_legacy_extern_calls(old_allow_legacy_extern);
                return r;
            }
        }
#endif
        XlangRuntimeFileView raw_src_view;
        if (runtime_read_file_view(input_path, &raw_src_view) != 0) {
            diag_reportf_with_code(input_path, 0, 0, "io error", XLANG_DIAG_CODE_IO_IO001, NULL,
                                   "cannot read file '%s'", input_path ? input_path : "?");
            return 1;
        }
        size_t src_len = 0;
        pipeline_diag_emitted_reset();
        char *src = xlang_preprocess_with_path(raw_src_view.data, raw_src_view.length, input_path, NULL, 0, &src_len);
        runtime_release_file_view(&raw_src_view);
        if (!src && !pipeline_diag_emitted_get()) {
            diag_reportf_with_code(input_path, 0, 0, "preprocess error", XLANG_DIAG_CODE_PREPROCESS_PP002, NULL,
                         "preprocess failed for '%s'", input_path);
            return 1;
        }
        if (!src)
            return 1;
        diag_set_file(input_path, src, src_len);
        size_t arena_sz = pipeline_sizeof_arena();
        size_t module_sz = pipeline_sizeof_module();
        void *arena = malloc(arena_sz);
        void *module = malloc(module_sz);
        if (!arena || !module) {
            diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP005,
                                  ".x pipeline allocation failed", NULL);
            ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
            free(module);
            free(src);
            return 1;
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        if (src_len > (size_t)INT32_MAX) {
            diag_reportf_with_code(input_path, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP007, NULL,
                                   ".x -E source too large for parser (>%d bytes): '%s'",
                                   INT32_MAX, input_path ? input_path : "?");
            ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
            free(module);
            free(src);
            return 1;
        }
        parser_parse_into_init(module, arena);
        struct parser_ParseIntoResult pr =
            parser_parse_into_buf(arena, module, (uint8_t *)src, (int32_t)src_len);
        if (pr.ok != 0) {
            if (runtime_report_precise_parse_failure_if_known(input_path, src, src_len)) {
                ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
                free(module);
                free(src);
                return 1;
            }
            diag_reportf_with_code(input_path, 0, 0, "parse error", XLANG_DIAG_CODE_PARSE_P001, NULL,
                         ".x -E parse_into failed for '%s'",
                         input_path ? input_path : "?");
            ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
            free(module);
            free(src);
            return 1;
        }
        parser_parse_into_set_main_index(module, pr.main_idx);
        if (driver_get_module_num_funcs(module) <= 0) {
            struct xlang_slice_uint8_t diag_src_slice = {(uint8_t *)src, src_len};
            int32_t fail_tok = parser_diag_fail_at_token_kind(&diag_src_slice);
            if (fail_tok == TOKEN_STRING) {
                diag_reportf_with_code(input_path, 0, 0, "parse error", XLANG_DIAG_CODE_PARSE_P001, NULL,
                                       "expected integer literal, float literal, identifier, 'true', 'false', 'if', "
                                       "'break', 'continue', 'return', 'panic', 'match', or '('");
                ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
                free(module);
                free(src);
                return 1;
            }
        }
        int32_t n_imports = parser_get_module_num_imports(module);
        char entry_dir_buf[512];
        xlang_get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
        const char *entry_dir = entry_dir_buf;
        if (n_imports > 0)
            pipeline_set_entry_dir(entry_dir_buf);
        const char *lib_roots_arr[X_EMIT_MAX_LIB_ROOTS];
        int n_lib_roots = driver_x_emit_n_lib_roots;
        if (n_lib_roots == 0) {
            lib_roots_arr[0] = ".";
            n_lib_roots = 1;
        } else {
            for (int k = 0; k < n_lib_roots; k++) lib_roots_arr[k] = driver_x_emit_lib_roots[k];
        }
        char *dep_sources[MAX_ALL_DEPS];
        size_t dep_lens[MAX_ALL_DEPS];
        char *dep_paths[MAX_ALL_DEPS];
        int n_deps = 0;
        int asm_direct_import_only = driver_x_emit_asm_direct_import_only(input_path);
        for (int i = 0; i < MAX_ALL_DEPS; i++) {
            dep_sources[i] = NULL;
            dep_lens[i] = 0;
            dep_paths[i] = NULL;
        }
        if (n_imports > 0 && n_imports <= 32) {
            if (asm_direct_import_only) {
                if (xlang_load_direct_imports_for_asm_layout(module, lib_roots_arr, n_lib_roots, entry_dir, NULL, 0,
                        dep_sources, dep_lens, dep_paths, &n_deps) != 0) {
                    ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
            } else {
                char *cpaths[MAX_ALL_DEPS];
                int n_closure = 0;
                for (int i = 0; i < MAX_ALL_DEPS; i++)
                    cpaths[i] = NULL;
                if (xlang_collect_dep_paths_transitive(module, arena_sz, module_sz, lib_roots_arr, n_lib_roots, entry_dir,
                        NULL, 0, cpaths, &n_closure) != 0) {
                    ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                if (xlang_merge_direct_then_transitive_dep_paths(module, n_imports, cpaths, n_closure, dep_paths, &n_deps) != 0) {
                    while (n_closure > 0) {
                        n_closure--;
                        free(cpaths[n_closure]);
                    }
                    ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
            }
        }
        typeck_ndep_store((int32_t)(0));
        void *dep_arenas[32];
        void *dep_modules[32];
        for (int i = 0; i < n_deps; i++) {
            dep_arenas[i] = malloc(arena_sz);
            dep_modules[i] = malloc(module_sz);
            if (!dep_arenas[i] || !dep_modules[i]) {
                diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP005,
                                      ".x pipeline dependency allocation failed", NULL);
                while (i > 0) { i--; ast_pool_arena_release(dep_arenas[i]); ast_pool_module_release(dep_modules[i]); free(dep_arenas[i]); free(dep_modules[i]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
                return 1;
            }
            memset(dep_arenas[i], 0, arena_sz);
            memset(dep_modules[i], 0, module_sz);
        }
        struct codegen_CodegenOutBuf *out_buf = (struct codegen_CodegenOutBuf *)calloc(1, sizeof(*out_buf));
        struct ast_PipelineDepCtx *pctx_e = (struct ast_PipelineDepCtx *)calloc(1, sizeof(*pctx_e));
        if (!out_buf || !pctx_e) {
            diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP006,
                                  ".x -E output/context allocation failed", NULL);
            for (int di = 0; di < n_deps; di++) { ast_pool_arena_release(dep_arenas[di]); ast_pool_module_release(dep_modules[di]); free(dep_arenas[di]); free(dep_modules[di]); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
            if (out_buf) free(out_buf);
            if (pctx_e) pipeline_dep_ctx_heap_destroy(pctx_e);
            return 1;
        }
        xlang_pipeline_fill_ctx_path_buffers(pctx_e, entry_dir_buf, lib_roots_arr, n_lib_roots);
        if (asm_direct_import_only)
            xlang_pipeline_pctx_seed_dep_import_paths_only(pctx_e, dep_paths, n_deps);
        else
            xlang_pipeline_pctx_seed_dep_slots(pctx_e, dep_modules, dep_arenas, dep_paths, n_deps);
        pctx_e->use_asm_backend = 0;
        driver_dep_seeded_clear_all();
        for (int j = n_deps - 1; j >= 0; j--) {
            struct ast_PipelineDepCtx *one_ctx = (struct ast_PipelineDepCtx *)calloc(1, sizeof(*one_ctx));
            struct codegen_CodegenOutBuf *dep_out = (struct codegen_CodegenOutBuf *)calloc(1, sizeof(*dep_out));
            char *dep_src = NULL;
            size_t dep_len = 0;
            int ec_dep;
            if (!one_ctx || !dep_out) {
                diag_report_with_code(NULL, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP006,
                                      ".x -E dependency context/output allocation failed", NULL);
                pipeline_dep_ctx_heap_destroy(one_ctx);
                free(dep_out);
                for (int di = 0; di < n_deps; di++) { ast_pool_arena_release(dep_arenas[di]); ast_pool_module_release(dep_modules[di]); free(dep_arenas[di]); free(dep_modules[di]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(out_buf);
                pipeline_dep_ctx_heap_destroy(pctx_e);
                ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
                return 1;
            }
            xlang_pipeline_fill_ctx_path_buffers(one_ctx, xlang_dep_prerun_entry_dir(entry_dir_buf, lib_roots_arr, n_lib_roots),
                                                lib_roots_arr, n_lib_roots);
            char resolved[PATH_MAX];
            resolved[0] = '\0';
            if (asm_direct_import_only) {
                dep_src = dep_sources[j];
                dep_len = dep_lens[j];
            } else {
                XlangRuntimeFileView raw_view;
                xlang_resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir, dep_paths[j], resolved, sizeof(resolved));
                if (runtime_read_file_view(resolved, &raw_view) != 0) {
                    pipeline_diag_import_open_fail_once(dep_paths[j], resolved);
                    pipeline_dep_ctx_heap_destroy(one_ctx);
                    free(dep_out);
                    for (int di = 0; di < n_deps; di++) { ast_pool_arena_release(dep_arenas[di]); ast_pool_module_release(dep_modules[di]); free(dep_arenas[di]); free(dep_modules[di]); }
                    while (n_deps > 0) {
                        n_deps--;
                        if (dep_sources[n_deps]) free(dep_sources[n_deps]);
                        free(dep_paths[n_deps]);
                    }
                    free(out_buf);
                    pipeline_dep_ctx_heap_destroy(pctx_e);
                    ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
                    return 1;
                }
                dep_src = xlang_preprocess(raw_view.data, raw_view.length, NULL, 0, &dep_len);
                runtime_release_file_view(&raw_view);
                if (!dep_src) {
                    diag_reportf_with_code(resolved, 0, 0, "preprocess error", XLANG_DIAG_CODE_PREPROCESS_PP002, NULL,
                                 "preprocess failed for import '%s'", dep_paths[j]);
                    pipeline_dep_ctx_heap_destroy(one_ctx);
                    free(dep_out);
                    for (int di = 0; di < n_deps; di++) { ast_pool_arena_release(dep_arenas[di]); ast_pool_module_release(dep_modules[di]); free(dep_arenas[di]); free(dep_modules[di]); }
                    while (n_deps > 0) {
                        n_deps--;
                        if (dep_sources[n_deps]) free(dep_sources[n_deps]);
                        free(dep_paths[n_deps]);
                    }
                    free(out_buf);
                    pipeline_dep_ctx_heap_destroy(pctx_e);
                    ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
                    return 1;
                }
            }
            xlang_pipeline_one_ctx_for_dep_prerun(one_ctx, j, dep_modules, dep_arenas, dep_paths, n_deps,
            (const uint8_t *)dep_src, dep_len);
            driver_set_current_dep_path_for_codegen(dep_paths[j]);
            DiagContextSnapshot dep_diag_snapshot;
            const char *dep_diag_file = dep_paths[j];
            if (!asm_direct_import_only)
                dep_diag_file = resolved;
            diag_push_file(&dep_diag_snapshot, dep_diag_file, dep_src, dep_len);
            if (driver_x_emit_asm_dep_parse_skip_typeck_ok(input_path, dep_paths[j])) {
                ec_dep = xlang_pipeline_dep_prerun_parse_skip_typeck(dep_modules[j], dep_arenas[j],
                                                                    (const uint8_t *)dep_src, dep_len,
                                                                    (void *)dep_out, (void *)one_ctx);
            } else if (asm_direct_import_only || driver_x_emit_asm_dep_parse_only_ok(input_path, dep_paths[j])) {
                ec_dep = xlang_pipeline_dep_prerun_parse_only(dep_modules[j], dep_arenas[j],
                                                             (const uint8_t *)dep_src, dep_len);
            } else {
                ec_dep = xlang_pipeline_dep_prerun_typeck_only(dep_modules[j], dep_arenas[j],
                                                              (const uint8_t *)dep_src, dep_len,
                                                              (void *)dep_out, (void *)one_ctx);
            }
            diag_restore(&dep_diag_snapshot);
            driver_set_current_dep_path_for_codegen(NULL);
            pipeline_dep_ctx_heap_destroy(one_ctx);
            free(dep_out);
            if (!asm_direct_import_only)
                free(dep_src);
            if (ec_dep != 0) {
                diag_reportf_with_code(dep_diag_file, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP008, NULL,
                                       "pipeline failed for import '%s' (dep prerun rc=%d)",
                                       dep_paths[j] ? dep_paths[j] : "?", ec_dep);
                for (int di = 0; di < n_deps; di++) { ast_pool_arena_release(dep_arenas[di]); ast_pool_module_release(dep_modules[di]); free(dep_arenas[di]); free(dep_modules[di]); }
                while (n_deps > 0) {
                    n_deps--;
                    if (dep_sources[n_deps]) free(dep_sources[n_deps]);
                    free(dep_paths[n_deps]);
                }
                free(out_buf);
                pipeline_dep_ctx_heap_destroy(pctx_e);
                ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena); free(module); free(src);
                return 1;
            }
            driver_dep_publish_slot(j, dep_arenas[j], dep_modules[j], dep_paths[j]);
        }
        {
            int32_t tc_ndep = asm_direct_import_only ? 0 : n_deps;
            typeck_ndep_store(tc_ndep);
            for (int j = 0; j < tc_ndep; j++) {
                typeck_dep_module_set((int32_t)(j), dep_modules[j]);
                typeck_dep_arena_set((int32_t)(j), dep_arenas[j]);
            }
        }
        if (asm_direct_import_only) {
            pipeline_set_dep_slots(dep_arenas, dep_modules);
            driver_dep_seed_slots(NULL, NULL, 0);
            codegen_set_dep_slots_for_x_pipeline(NULL, NULL, 0);
        } else {
            pipeline_set_dep_slots(dep_arenas, dep_modules);
            driver_dep_seed_slots(dep_arenas, dep_modules, n_deps);
            /* PLATFORM: SHARED — re-seed pctx after dep pre-parse (NL-07 L8; G.7 pctx_seed). */
            xlang_pipeline_pctx_seed_dep_slots(pctx_e, dep_modules, dep_arenas, dep_paths, n_deps);
            codegen_set_dep_slots_for_x_pipeline((struct ASTModule **)dep_modules, (const char **)dep_paths, n_deps);
            pipeline_set_dep_slots(dep_arenas, dep_modules);
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        int ec = xlang_pipeline_run_x_pipeline_large_stack(module, arena, (uint8_t *)src, src_len, (void *)out_buf, (void *)pctx_e);
        if (ec == 0 && out_buf->length > 0) {
            /* Emit smoke summary (parse OK / typeck OK) before C body so run-typeck.sh
             * gate grep finds the marker on the -E path. Mirrors driver/emit.x:413
             * and rt_run_compiler_parsed.from_x.c:1055. PLATFORM: SHARED. */
            driver_print_x_smoke_summary(module, (size_t)out_buf->length);
            /* Cap residual 9.7.1: fwrite(stdout)+fflush → single raw fd-1 write
             * (unbuffered; no flush needed). PLATFORM: SHARED. */
            (void)xlang_io_write(1, out_buf->data, (size_t)out_buf->length);
            for (int j = n_deps - 1; j >= 0; j--) { ast_pool_arena_release(dep_arenas[j]); ast_pool_module_release(dep_modules[j]); free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) {
                n_deps--;
                if (dep_sources[n_deps]) free(dep_sources[n_deps]);
                free(dep_paths[n_deps]);
            }
        } else {
            for (int j = n_deps - 1; j >= 0; j--) { ast_pool_arena_release(dep_arenas[j]); ast_pool_module_release(dep_modules[j]); free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) {
                n_deps--;
                if (dep_sources[n_deps]) free(dep_sources[n_deps]);
                free(dep_paths[n_deps]);
            }
            if (ec != 0) {
                diag_reportf_with_code(input_path, 0, 0, "pipeline error", XLANG_DIAG_CODE_X_PIPELINE_XP003, NULL,
                             ".x pipeline failed for '%s'",
                             input_path ? input_path : "?");
            } else if (out_buf->length <= 0) {
                if (driver_get_module_num_funcs(module) <= 0) {
                    if (!runtime_report_precise_parse_failure_if_known(input_path, src, src_len)) {
                        diag_reportf_with_code(input_path, 0, 0, "parse error", XLANG_DIAG_CODE_PARSE_P001, NULL,
                                               "parse produced no functions in '%s'",
                                               input_path ? input_path : "?");
                    }
                    goto x_emit_c_done;
                }
                diag_reportf_with_code(input_path, 0, 0, "codegen error", XLANG_DIAG_CODE_CODEGEN_CG004, NULL,
                             "-x -E pipeline succeeded but codegen buffer is empty (ec=0 out_buf.length=%d); "
                             "check typeck/codegen/pipeline CodegenOutBuf",
                             (int)out_buf->length);
            }
        }
        int emit_ret = (ec != 0 || out_buf->length <= 0) ? 1 : 0;
x_emit_c_done:
        if (ec == 0 && out_buf->length <= 0)
            emit_ret = 1;
        free(out_buf);
        pipeline_dep_ctx_heap_destroy(pctx_e);
        ast_pool_arena_release(arena); ast_pool_module_release(module); free(arena);
        free(module);
        free(src);
        typeck_set_allow_legacy_extern_calls(old_allow_legacy_extern);
        return emit_ret;
    }
#else
    (void)input_path;
    typeck_set_allow_legacy_extern_calls(old_allow_legacy_extern);
    return 1;
#endif
}

#else /* XLANG_RT_RUN_X_EMIT_FROM_X：产品 rest 仅 marker；业务体在 full .x */
int driver_run_x_emit_c(void);
#endif /* XLANG_RT_RUN_X_EMIT_FROM_X */

int labi_rt_run_x_emit_slice_marker(void) {
  return 1;
}
