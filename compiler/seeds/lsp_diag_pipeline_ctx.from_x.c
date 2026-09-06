/* Generated from src/lsp/lsp_diag_pipeline_ctx.x (G-02f-28 true .x + C tail; G-02f-74/98 lsp ctx gates).
 * G-02f-331：PREFER_X_O hybrid 时 thin 别名由 .x→-E，rest 用 XLANG_L2_LSP_CTX_THIN_FROM_X。
 * Regen: ./xlang-c -E -L .. src/lsp/lsp_diag_pipeline_ctx.x > /tmp/ldpc.c
 *         then re-apply weak polish + C tail (fill_paths/state/write_all).
 * .x covers: sizeof bridge + typeck_ → bare name aliases.
 */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "diag.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <xlang_io_cap.h>

/* wave244 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED orch / host getenv residual via single face.
 * Compiler-only TU (lsp_diag_pipeline_ctx) — not in user STD_AND_PANIC bag. */
extern char *link_abi_getenv(const char *name);

extern size_t pipeline_sizeof_dep_ctx(void);
extern int32_t typeck_lsp_build_diagnostics_response(int32_t id_val, uint8_t * source, int32_t source_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t typeck_lsp_diag_hover_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, uint8_t * out_buf, int32_t out_cap);
extern int32_t typeck_lsp_diag_references_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_lines, int32_t * out_cols, int32_t max_refs);
extern int32_t typeck_lsp_diag_definition_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_line, int32_t * out_col);
extern int32_t typeck_lsp_build_semantic_tokens_response(int32_t id_val, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern void lsp_diag_invalidate_cache(void);
#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
size_t lsp_diag_x_alloc_dep_ctx_size(void) {
  (void)(({   {
    size_t r = pipeline_sizeof_dep_ctx();
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_build_diagnostics_response(int32_t id_val, uint8_t * source, int32_t source_len, uint8_t * out_buf, int32_t out_cap) {
  (void)(({   {
    int32_t r = typeck_lsp_build_diagnostics_response(id_val, source, source_len, out_buf, out_cap);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_diag_hover_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, uint8_t * out_buf, int32_t out_cap) {
  (void)(({   {
    int32_t r = typeck_lsp_diag_hover_at(source, source_len, line_0, col_0, out_buf, out_cap);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_diag_references_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_lines, int32_t * out_cols, int32_t max_refs) {
  (void)(({   {
    int32_t r = typeck_lsp_diag_references_at(source, source_len, line_0, col_0, out_lines, out_cols, max_refs);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_hover_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, uint8_t * out_buf, int32_t out_cap) {
  (void)(({   {
    int32_t r = typeck_lsp_diag_hover_at(source, source_len, line_0, col_0, out_buf, out_cap);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_references_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_lines, int32_t * out_cols, int32_t max_refs) {
  (void)(({   {
    int32_t r = typeck_lsp_diag_references_at(source, source_len, line_0, col_0, out_lines, out_cols, max_refs);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_diag_definition_at(uint8_t * source, int32_t source_len, int32_t line_0, int32_t col_0, int32_t * out_line, int32_t * out_col) {
  (void)(({   {
    int32_t r = typeck_lsp_diag_definition_at(source, source_len, line_0, col_0, out_line, out_col);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t lsp_build_semantic_tokens_response(int32_t id_val, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap) {
  (void)(({   {
    int32_t r = typeck_lsp_build_semantic_tokens_response(id_val, doc_buf, doc_len, out_buf, out_cap);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK void lsp_io_lsp_diag_invalidate_cache(void) {
  (void)(({   {
    (void)(lsp_diag_invalidate_cache());
  }
 }));
}

#else
/* G-02f-331：thin 由 src/lsp/lsp_diag_pipeline_ctx.x（-E）提供；rest 仅 C 尾 / _impl */
extern size_t lsp_diag_x_alloc_dep_ctx_size(void);
extern int32_t lsp_build_diagnostics_response(int32_t, uint8_t *, int32_t, uint8_t *, int32_t);
extern int32_t lsp_diag_hover_at(uint8_t *, int32_t, int32_t, int32_t, uint8_t *, int32_t);
extern int32_t lsp_diag_references_at(uint8_t *, int32_t, int32_t, int32_t, int32_t *, int32_t *, int32_t);
extern int32_t lsp_hover_at(uint8_t *, int32_t, int32_t, int32_t, uint8_t *, int32_t);
extern int32_t lsp_references_at(uint8_t *, int32_t, int32_t, int32_t, int32_t *, int32_t *, int32_t);
extern int32_t lsp_diag_definition_at(uint8_t *, int32_t, int32_t, int32_t, int32_t *, int32_t *);
extern int32_t lsp_build_semantic_tokens_response(int32_t, uint8_t *, int32_t, uint8_t *, int32_t);
extern void lsp_io_lsp_diag_invalidate_cache(void);
#endif

/* ---- C tail (G-02f-28): fill_paths / state buf / large-stack main / write_all ---- */

struct ast_PipelineDepCtx {
  int32_t ndep;
  uint8_t entry_dir_buf[512];
  int32_t entry_dir_len;
  int32_t num_lib_roots;
  uint8_t path_buf[512];
  uint8_t *loaded_buf;
  ptrdiff_t loaded_len;
  uint8_t *preprocess_buf;
  int32_t preprocess_len;
  int32_t use_asm_backend;
  int32_t target_arch;
  int32_t use_macho_o;
  int32_t use_coff_o;
  int32_t current_block_ref;
  int32_t typeck_loop_depth;
  int32_t typeck_check_depth;
  int32_t current_func_index;
  int32_t skip_codegen_dep_0;
  int32_t check_only_mode;
  int32_t entry_already_parsed;
  int32_t current_func_single_empty_param_index;
  int32_t current_func_empty_param_count;
  int32_t current_emit_empty_var_next_index;
  int32_t emit_expr_as_callee;
  void *current_codegen_module;
  void *current_codegen_arena;
  int32_t current_codegen_dep_index;
  uint8_t current_codegen_prefix_mirror[128];
  int32_t current_codegen_prefix_len;
  int32_t asm_entry_module_only;
  uint8_t entry_module_import_path_mirror[128];
  int32_t entry_module_import_path_len;
};

extern int32_t pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx *ctx, uint8_t *path, int32_t len);
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
void lsp_diag_pipeline_ctx_fill_paths(void *ctx_void, const char *entry_dir, const char **lib_roots, int n_lib_roots)
#else
void lsp_diag_pipeline_ctx_fill_paths_impl(void *ctx_void, const char *entry_dir, const char **lib_roots, int n_lib_roots)
#endif
{
    struct ast_PipelineDepCtx *ctx = (struct ast_PipelineDepCtx *)ctx_void;
    int i;
    if (!ctx) return;
    memset(ctx, 0, sizeof(*ctx));
    if (entry_dir && entry_dir[0]) {
        size_t el = strlen(entry_dir);
        if (el >= 512) el = 511;
        memcpy(ctx->entry_dir_buf, entry_dir, el);
        ctx->entry_dir_buf[el] = '\0';
        ctx->entry_dir_len = (int32_t)el;
    }
    if (lib_roots && n_lib_roots > 0) {
        for (i = 0; i < n_lib_roots && lib_roots[i]; i++) {
            size_t ll = strlen(lib_roots[i]);
            if (ll >= 256) ll = 255;
            (void)pipeline_ctx_append_lib_root(ctx, (uint8_t *)lib_roots[i], (int32_t)ll);
        }
    }
}




/** bootstrap driver：强符号覆盖 lsp_diag.c 内 weak 实现，统一走 parse_into_buf。 */
XLANG_WEAK int lsp_definition_at(const uint8_t *source, int source_len, int line_0, int col_0, int *out_line, int *out_col) {
  int32_t ol = 0;
  int32_t oc = 0;
  if (!typeck_lsp_diag_definition_at((uint8_t *)source, (int32_t)source_len, (int32_t)line_0, (int32_t)col_0, &ol, &oc))
    return 0;
  if (out_line) *out_line = (int)ol;
  if (out_col) *out_col = (int)oc;
  return 1;
}

extern int32_t typeck_lsp_main(void);
extern int32_t typeck_lsp_main_impl(void);
extern int32_t lsp_main_impl(void);
extern void driver_bump_stack_limit(void);
extern void driver_run_on_large_stack_pthread(void *(*fn)(void *), void *arg);

/* PLATFORM: MACOS — tentative COMMON for a 16388-byte object gets size-derived
 * alignment 2^15 (0x8000). Apple ld then warns:
 *   reducing alignment of section __DATA,__common from 0x8000 to 0x4000
 * Zero-init forces a defined zerofill symbol in __DATA,__common with align 2^0
 * (same shape as -fno-common; no 16KiB file bloat). PLATFORM: SHARED seed. */
uint8_t g_lsp_state_buf[16388] = {0};

typedef struct LspMainThreadArgs {
    int32_t result;
} LspMainThreadArgs;

/* G-02f-98：LSP IO policy / debug env gates. */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
void lsp_debug_report_sqpoll_env(void)
#else
void lsp_debug_report_sqpoll_env_impl(void)
#endif
{
    const char *dbg = link_abi_getenv("XLANG_LSP_IO_DEBUG");
    const char *sq = link_abi_getenv("XLANG_IO_URING_SQPOLL");
    if (!dbg || dbg[0] == '\0' || dbg[0] == '0')
        return;
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "lsp io debug: XLANG_IO_URING_SQPOLL=%s",
                 (sq && sq[0]) ? sq : "<unset>");
}
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */




#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
void lsp_apply_default_io_policy(void)
#else
void lsp_apply_default_io_policy_impl(void)
#endif
{
    const char *sq = link_abi_getenv("XLANG_IO_URING_SQPOLL");
    if (!sq || sq[0] == '\0')
        (void)setenv("XLANG_IO_URING_SQPOLL", "0", 1);
}



static void *lsp_main_large_stack_thread_fn(void *arg) {
    LspMainThreadArgs *a = (LspMainThreadArgs *)arg;
    driver_bump_stack_limit();
    /* G-02f-331：大栈线程跑真实 lsp_main（勿调 typeck_lsp_main[_impl] 编排层） */
    a->result = lsp_main_impl();
    return NULL;
}
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
int32_t typeck_lsp_main(void)
#else
/* thin typeck_lsp_main → typeck_lsp_main_impl（本函数为大栈编排） */
int32_t typeck_lsp_main_impl(void)
#endif
{
    LspMainThreadArgs args;
    args.result = -1;
#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
    lsp_apply_default_io_policy();
    lsp_debug_report_sqpoll_env();
#else
    lsp_apply_default_io_policy_impl();
    lsp_debug_report_sqpoll_env_impl();
#endif
    driver_run_on_large_stack_pthread(lsp_main_large_stack_thread_fn, &args);
    return args.result;
}




uint8_t *lsp_state_buf_ptr(void) {
    return g_lsp_state_buf;
}
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

#ifndef XLANG_L2_LSP_CTX_THIN_FROM_X
int32_t lsp_write_all(int32_t fd, const uint8_t *buf, int32_t len)
#else
int32_t lsp_write_all_impl(int32_t fd, const uint8_t *buf, int32_t len)
#endif
{
    int32_t off = 0;
    if (fd < 0 || !buf) {
        return -1;
    }
    if (len <= 0) {
        return 0;
    }
    while (off < len) {
        ssize_t n = (ssize_t)xlang_io_write(fd, buf + (size_t)off, (size_t)(len - off));
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        if (n == 0) {
            return -1;
        }
        off += (int32_t)n;
    }
    return 0;
}



