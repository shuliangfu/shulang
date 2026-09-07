/* Generated from src/runtime_driver_strict_glue_stubs.x (G-02f-32/33 true .x + C tail).
 * G-02f-105 helper gates.
 * G-02f-258：XLANG_L2_STRICT_GLUE_THIN_FROM_X 时省略 thin 转发
 *           （由 src/runtime_driver_strict_glue_thin.x → .o 提供，再 ld -r）。
 * Regen: ./xlang-c -E -L .. src/runtime_driver_strict_glue_stubs.x > /tmp/sgs.c
 *         merge thin forwards/metrics peek; weak polish; heap_user/slot arrays C.
 * .x covers: asm_driver_*, i32_ptr_*, metrics init/read, call_resolve peek.
 */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <xlang_io_cap.h>
/* Cap residual 9.7.1: stream params are opaque fd handles. */
#include "xlang_driver_stream_cap.h"

#include "token.h"
#include "codegen/codegen.h"
#include <string.h>
#include "seeds/runtime_heap_user.from_x.c"


struct ASTModule;
struct ASTFunc;
typedef struct ASTModule ASTModule;

typedef struct Lexer Lexer;

XLANG_WEAK void codegen_emit_fmt_json_helpers_once(FILE *out) {
  (void)out;
}

XLANG_WEAK void codegen_emit_builtin_inline_decls(FILE *out) {
  (void)out;
}

XLANG_WEAK int codegen_emit_dep_types_only(struct ASTModule **mods, const char **import_paths, int n, FILE *out,
                                                      char (*emitted_type_names)[64], int *n_emitted_inout,
                                                      int max_emitted) {
  (void)mods;
  (void)import_paths;
  (void)n;
  (void)out;
  (void)emitted_type_names;
  (void)n_emitted_inout;
  (void)max_emitted;
  return -1;
}

XLANG_WEAK void codegen_set_eextern_entry_path(const char *entry_path) {
  (void)entry_path;
}

XLANG_WEAK Lexer *lexer_new(const char *source) {
  (void)source;
  return NULL;
}

XLANG_WEAK void lexer_free(Lexer *l) {
  (void)l;
}

XLANG_WEAK void lexer_next(Lexer *l, Token *out) {
  (void)l;
  if (!out)
    return;
  out->kind = TOKEN_EOF;
  out->line = 1;
  out->col = 1;
  out->ident_len = 0;
}

XLANG_WEAK int parse(Lexer *lex, ASTModule **out) {
  (void)lex;
  (void)out;
  return -1;
}

XLANG_WEAK int typeck_module(ASTModule *m, ASTModule **dep_mods, int num_deps, ASTModule **all_dep_mods, int n_all_deps) {
  (void)m;
  (void)dep_mods;
  (void)num_deps;
  (void)all_dep_mods;
  (void)n_all_deps;
  return -1;
}

/** G-02e：原 typeck_c_module_stubs.c 的 typeck_one_function，并入本 TU 以便产品链去掉独立 stubs.o。 */
XLANG_WEAK int typeck_one_function(ASTModule *m, ASTModule **dep_mods, int num_deps, ASTModule **all_dep_mods, int n_all_deps,
                                  int only_func_index) {
  (void)m;
  (void)dep_mods;
  (void)num_deps;
  (void)all_dep_mods;
  (void)n_all_deps;
  (void)only_func_index;
  return -1;
}

XLANG_WEAK int typeck_set_allow_legacy_extern_calls(int allow) {
  (void)allow;
  return 0;
}

XLANG_WEAK char *preprocess(const char *source, size_t source_len, const char **defines, int ndefines,
                                       size_t *out_length) {
  (void)source;
  (void)source_len;
  (void)defines;
  (void)ndefines;
  if (out_length)
    *out_length = 0;
  return NULL;
}

XLANG_WEAK void driver_print_usage_c(void) {
  static const char msg[] = "Xlang (stub)\nUsage: xlang [options] file.x\n";
  (void)xlang_io_write(STDOUT_FILENO, msg, sizeof(msg) - 1u);
}

XLANG_WEAK int xlang_c_resolve_and_load_imports(ASTModule *mod, const char **lib_roots, int n_lib_roots,
                                                         const char *entry_dir, const char **defines, int ndefines,
                                                         int allow_legacy_extern, ASTModule **dep_mods, int *ndep_out,
                                                         ASTModule **all_dep_mods, char **all_dep_paths, char all_dep_fs[][512],
                                                         int *n_all_out, int max_deps) {
  (void)mod;
  (void)lib_roots;
  (void)n_lib_roots;
  (void)entry_dir;
  (void)defines;
  (void)ndefines;
  (void)allow_legacy_extern;
  (void)dep_mods;
  (void)ndep_out;
  (void)all_dep_mods;
  (void)all_dep_paths;
  (void)all_dep_fs;
  (void)n_all_out;
  (void)max_deps;
  return -1;
}

XLANG_WEAK int xlang_lsp_resolve_and_load_imports(ASTModule *mod, const char **lib_roots, int n_lib_roots,
                                                           const char *entry_dir, ASTModule **dep_mods, int *ndep_out,
                                                           ASTModule **all_dep_mods, char **all_dep_paths,
                                                           char all_dep_fs[][512], int *n_all_out, int max_deps) {
  (void)mod;
  (void)lib_roots;
  (void)n_lib_roots;
  (void)entry_dir;
  (void)dep_mods;
  (void)ndep_out;
  (void)all_dep_mods;
  (void)all_dep_paths;
  (void)all_dep_fs;
  (void)n_all_out;
  (void)max_deps;
  return -1;
}

XLANG_WEAK int32_t pipeline_typeck_module_for_ctx(void *module, void *arena, void *ctx_void) {
  (void)module;
  (void)arena;
  (void)ctx_void;
  return -1;
}

XLANG_WEAK void ast_module_free(ASTModule *mod) {
  (void)mod;
}

/* -------------------------------------------------------------------------- */
/* G-02e：原 codegen_pipeline_stubs.c 并入本 TU。 */
/* -------------------------------------------------------------------------- */

XLANG_WEAK void codegen_set_preamble_has_core_option_result(int on) { (void)on; }

XLANG_WEAK void codegen_reset_preamble_skip_mask(void) { }

XLANG_WEAK void codegen_or_preamble_skip_mask(unsigned mask) { (void)mask; }

XLANG_WEAK unsigned codegen_get_preamble_skip_mask(void) { return 0; }

XLANG_WEAK void codegen_set_dep_slots_for_x_pipeline(struct ASTModule **mods, const char **paths, int n) {
  (void)mods;
  (void)paths;
  (void)n;
}

XLANG_WEAK int codegen_wpo_mono_sym_format(const char *base, int nargs, const int *args, char *out, int cap) {
  (void)base;
  (void)nargs;
  (void)args;
  (void)out;
  (void)cap;
  return -1;
}

XLANG_WEAK int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted) {
  (void)m; (void)out; (void)dep_mods; (void)dep_import_paths; (void)ndep;
  (void)is_func_used; (void)is_mono_used; (void)is_type_used; (void)dce_ctx;
  (void)emitted_type_names; (void)n_emitted_inout; (void)max_emitted;
  return -1;
}

XLANG_WEAK int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted,
    const char *emit_entry_path) {
  (void)m; (void)import_path; (void)lib_dep_mods; (void)lib_dep_paths; (void)n_lib_dep;
  (void)out; (void)is_func_used; (void)is_mono_used; (void)is_type_used; (void)dce_ctx;
  (void)emitted_type_names; (void)n_emitted_inout; (void)max_emitted; (void)emit_entry_path;
  return -1;
}

XLANG_WEAK void codegen_compute_used(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs_out, int *n_used_out, int max_used, int used_mono[][64]) {
  (void)entry; (void)dep_mods; (void)ndep; (void)used_funcs_out; (void)max_used; (void)used_mono;
  if (n_used_out) *n_used_out = 0;
}

XLANG_WEAK struct ASTFunc *codegen_entry_root_func(struct ASTModule *entry) {
  (void)entry;
  return NULL;
}

XLANG_WEAK void codegen_wpo_reach_compute(CodegenWpoReach *out,
    struct ASTModule *entry,
    struct ASTModule **all_mods, int n_all) {
  (void)entry; (void)all_mods; (void)n_all;
  if (!out) return;
  memset(out, 0, sizeof(*out));
  out->root_id = -1;
}

XLANG_WEAK int codegen_wpo_reach_is_reachable(const CodegenWpoReach *wpo, const struct ASTModule *mod,
    const struct ASTFunc *func) {
  (void)wpo; (void)mod; (void)func;
  return 0;
}

XLANG_WEAK void codegen_compute_used_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs, int n_used, const char **used_type_names_out, int *n_out, int max_types) {
  (void)entry; (void)dep_mods; (void)ndep; (void)used_funcs; (void)n_used;
  (void)used_type_names_out; (void)max_types;
  if (n_out) *n_out = 0;
}

XLANG_WEAK void codegen_dump_wpo_callgraph_json(uint8_t *out,
    struct ASTModule *entry, const char *entry_path,
    struct ASTModule **all_mods, const char **all_paths, int n_all) {
  (void)entry; (void)entry_path; (void)all_mods; (void)all_paths; (void)n_all;
  if (out) {
    static const char json[] = "{\"version\":2,\"nodes\":[]}\n";
    (void)xlang_io_write(xlang_driver_handle_to_fd(out), json, sizeof(json) - 1);
  }
}

/* ---- G-02e-10：原 _stubs_driver.c（pipeline_gen asm_driver_* → driver_*）---- */

extern int32_t driver_skip_codegen_dep_0_get(void);
extern void driver_set_current_dep_path_for_codegen(const char *path);

#ifndef XLANG_L2_STRICT_GLUE_THIN_FROM_X
int32_t asm_driver_skip_codegen_dep_0_get(void) {
  (void)(({   {
    int32_t r = driver_skip_codegen_dep_0_get();
    return r;
  }
 }));
  return 0;
}

void asm_driver_set_current_dep_path_for_codegen(uint8_t * path) {
  (void)(({   {
    (void)(driver_set_current_dep_path_for_codegen((const char *)path));
  }
 }));
}
#endif

/* ---- G-02e-11：原 lsp_codegen_extern（LSP -E-extern 字符串块）---- */

/** 与 runtime.c 中 codegen_CodegenOutBuf 布局一致。 */
struct codegen_CodegenOutBuf {
  unsigned char data[9 * 1024 * 1024];
  int32_t length;
};

/** 路径是否 lsp_io.x 的 -E-extern 入口。 */
int lsp_codegen_emit_path_is_lsp_io_x(const char *path) {
  return path != NULL && strstr(path, "lsp_io.x") != NULL;
}

/** 路径是否 lsp/lsp.x 的 -E-extern 入口（排除 lsp_io 等子路径误匹配）。 */
int lsp_codegen_emit_path_is_lsp_main_x(const char *path) {
  if (!path)
    return 0;
  if (strstr(path, "/lsp/lsp.x") != NULL || strstr(path, "\\lsp\\lsp.x") != NULL)
    return 1;
  if (strstr(path, "lsp/lsp.x") != NULL && strstr(path, "lsp_io") == NULL)
    return 1;
  return 0;
}

static const char *lsp_heap_alias_block =
    "\n/* lsp_codegen_extern: std.heap typeck 链接别名（C-04 v0；std_io extern 由 codegen 自动生成） */\n"
    "extern uint8_t *typeck_std_heap_alloc(size_t size);\n"
    "extern void typeck_std_heap_free(uint8_t *ptr);\n"
    "#define std_heap_alloc typeck_std_heap_alloc\n"
    "#define std_heap_free typeck_std_heap_free\n";

static const char *lsp_io_extern_block =
    "\n/* lsp_codegen_extern: deprecated full io block — 保留给旧 bootstrap 路径 */\n"
    "extern int32_t std_io_read(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);\n"
    "extern int32_t std_io_write(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);\n"
    "extern void lsp_debug_u32(uint32_t n);\n"
    "#define typeck_lsp_debug_u32 lsp_debug_u32\n"
    "extern void lsp_debug_ptr(uint8_t *p);\n"
    "#define typeck_lsp_debug_ptr lsp_debug_ptr\n"
    "extern uint8_t *typeck_std_heap_alloc(size_t size);\n"
    "extern void typeck_std_heap_free(uint8_t *ptr);\n"
    "#define std_heap_alloc typeck_std_heap_alloc\n"
    "#define std_heap_free typeck_std_heap_free\n";

static const char *lsp_gen_extern_block =
    "\n/* lsp_codegen_extern: lsp.x -E-extern stubs (lsp_io_x.o 符号桥接) */\n"
    "extern ptrdiff_t typeck_read_message(int32_t fd, uint8_t *body_out, int32_t body_cap, uint8_t *state_buf);\n"
    "extern ptrdiff_t typeck_write_fd(int32_t fd, uint8_t *ptr, size_t count);\n"
    "extern uint8_t *typeck_lsp_alloc(size_t size);\n"
    "extern void typeck_lsp_free(uint8_t *ptr);\n"
    "extern int32_t typeck_lsp_is_null(uint8_t *ptr);\n"
    "extern int32_t typeck_extract_document_text(uint8_t *body, int32_t body_len, uint8_t *out_buf, int32_t out_cap);\n"
    "static inline ptrdiff_t lsp_io_read_message(int32_t fd, uint8_t *body_out, int32_t body_cap, uint8_t *state_buf) {\n"
    "  return typeck_read_message(fd, body_out, body_cap, state_buf);\n"
    "}\n"
    "static inline ptrdiff_t lsp_io_write_fd(int32_t fd, uint8_t *ptr, size_t count) {\n"
    "  return typeck_write_fd(fd, ptr, count);\n"
    "}\n"
    "static inline uint8_t *lsp_io_lsp_alloc(size_t size) {\n"
    "  return typeck_lsp_alloc(size);\n"
    "}\n"
    "static inline void lsp_io_lsp_free(uint8_t *ptr) {\n"
    "  typeck_lsp_free(ptr);\n"
    "}\n"
    "static inline int32_t lsp_io_lsp_is_null(uint8_t *ptr) {\n"
    "  return typeck_lsp_is_null(ptr);\n"
    "}\n"
    "static inline int32_t lsp_io_extract_document_text(uint8_t *body, int32_t body_len, uint8_t *out_buf, int32_t out_cap) {\n"
    "  return typeck_extract_document_text(body, body_len, out_buf, out_cap);\n"
    "}\n";

/** 追加文本到 CodegenOutBuf；容量不足返回 -1。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int append_text_to_codegen_buf(struct codegen_CodegenOutBuf *out, const char *text) {
  size_t n;
  if (!out || !text)
    return -1;
  n = strlen(text);
  if (out->length < 0 || (size_t)out->length + n >= sizeof(out->data))
    return -1;
  memcpy(out->data + (size_t)out->length, text, n);
  out->length += (int32_t)n;
  return 0;
}




void lsp_codegen_emit_heap_alias_block(uint8_t *out) {
  if (out)
    (void)xlang_io_write(xlang_driver_handle_to_fd(out), lsp_heap_alias_block,
                         strlen(lsp_heap_alias_block));
}

void lsp_codegen_emit_io_extern_block(uint8_t *out) {
  if (out)
    (void)xlang_io_write(xlang_driver_handle_to_fd(out), lsp_io_extern_block,
                         strlen(lsp_io_extern_block));
}

void lsp_codegen_emit_gen_extern_block(uint8_t *out) {
  if (out)
    (void)xlang_io_write(xlang_driver_handle_to_fd(out), lsp_gen_extern_block,
                         strlen(lsp_gen_extern_block));
}

int lsp_codegen_emit_heap_alias_to_buf(struct codegen_CodegenOutBuf *out) {
  return append_text_to_codegen_buf(out, lsp_heap_alias_block);
}

int lsp_codegen_emit_io_extern_to_buf(struct codegen_CodegenOutBuf *out) {
  return append_text_to_codegen_buf(out, lsp_io_extern_block);
}

int lsp_codegen_emit_gen_extern_to_buf(struct codegen_CodegenOutBuf *out) {
  return append_text_to_codegen_buf(out, lsp_gen_extern_block);
}

/* ---- G-02e-12：原 runtime_pipeline_abi_xlang_c_stubs（xlang-c 冷启动 X 管线弱桩）---- */

struct parser_ParseIntoResult {
    int32_t ok;
    int32_t main_idx;
};

struct xlang_slice_uint8_t {
    const uint8_t *ptr;
    size_t length;
};

struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;

/** asm 后端 ELF 生成桩；冷启动 xlang-c 不走 asm 分支。 */
XLANG_WEAK int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf) {
    (void)module;
    (void)arena;
    (void)ctx;
    (void)elf_ctx;
    (void)out_buf;
    return -1;
}

/** driver 模块查询桩。 */
XLANG_WEAK int32_t driver_get_module_num_funcs(void *module) {
    (void)module;
    return 0;
}

XLANG_WEAK int32_t driver_get_module_main_func_index(void *module) {
    (void)module;
    return -1;
}

/** pipeline 模块函数查询桩。 */
XLANG_WEAK int32_t pipeline_module_num_funcs(void *module) {
    (void)module;
    return 0;
}

XLANG_WEAK int32_t pipeline_module_func_is_extern_at(void *module, int32_t idx) {
    (void)module;
    (void)idx;
    return 0;
}

/** parser 模块 import 计数桩。 */
XLANG_WEAK int32_t parser_get_module_num_imports(void *module) {
    (void)module;
    return 0;
}

/** parser import 路径写入桩。 */
XLANG_WEAK void parser_get_module_import_path(void *module, int32_t idx, uint8_t *path_buf) {
    (void)module;
    (void)idx;
    if (path_buf)
        path_buf[0] = '\0';
}

/** parser parse 初始化桩。 */
XLANG_WEAK void parser_parse_into_init(void *module, void *arena) {
    (void)module;
    (void)arena;
}

/** parser parse 桩；返回失败。 */
XLANG_WEAK struct parser_ParseIntoResult parser_parse_into(void *arena, void *module,
                                                                      struct xlang_slice_uint8_t *source) {
    (void)arena;
    (void)module;
    (void)source;
    struct parser_ParseIntoResult pr = { 0, -1 };
    return pr;
}

/** pipeline X 入口桩。 */
XLANG_WEAK int pipeline_run_x_pipeline(void *module, void *arena, const uint8_t *source_data,
                                                   size_t source_len, void *out_buf, void *ctx) {
    (void)module;
    (void)arena;
    (void)source_data;
    (void)source_len;
    (void)out_buf;
    (void)ctx;
    return -1;
}

/** pipeline dep ctx 桩。 */
XLANG_WEAK void ast_pipeline_dep_ctx_reset(struct ast_PipelineDepCtx *ctx) {
    (void)ctx;
}

XLANG_WEAK int32_t ast_pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx *ctx, uint8_t *path,
                                                               int32_t len) {
    (void)ctx;
    (void)path;
    (void)len;
    return 0;
}

XLANG_WEAK void ast_pipeline_dep_ctx_set_module(struct ast_PipelineDepCtx *ctx, int32_t idx,
                                                           struct ast_Module *m) {
    (void)ctx;
    (void)idx;
    (void)m;
}

XLANG_WEAK void ast_pipeline_dep_ctx_set_arena(struct ast_PipelineDepCtx *ctx, int32_t idx,
                                                          struct ast_ASTArena *a) {
    (void)ctx;
    (void)idx;
    (void)a;
}

XLANG_WEAK void ast_pipeline_dep_ctx_set_ndep(struct ast_PipelineDepCtx *ctx, int32_t n) {
    (void)ctx;
    (void)n;
}

XLANG_WEAK void ast_pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx *ctx, int32_t idx,
                                                                uint8_t *bytes, int32_t len) {
    (void)ctx;
    (void)idx;
    (void)bytes;
    (void)len;
}

XLANG_WEAK int32_t pipeline_asm_user_dep_skip_x_typeck(uint8_t *path) {
    (void)path;
    return 0;
}

XLANG_WEAK int32_t pipeline_asm_user_std_net_dep_path(uint8_t *path) {
    (void)path;
    return 0;
}

XLANG_WEAK int32_t pipeline_codegen_path_is_std_io_driver_bytes(uint8_t *path) {
    (void)path;
    return 0;
}

XLANG_WEAK void asm_skip_heavy_set_pipeline_ctx(void *ctx) {
    (void)ctx;
}

XLANG_WEAK void pipeline_fill_array_lit_types_for_skipped_typeck(void *module, void *arena) {
    (void)module;
    (void)arena;
}

XLANG_WEAK void pipeline_fill_soa_field_access_for_asm_emit(void *module, void *arena) {
    (void)module;
    (void)arena;
}

XLANG_WEAK size_t pipeline_sizeof_arena(void) {
    return 4096u;
}

XLANG_WEAK size_t pipeline_sizeof_module(void) {
    return 4096u;
}

/** pipeline 解析/typeck 依赖；冷启动 C 前端 check 不走 X dep prerun，弱桩返回失败。 */
XLANG_WEAK int32_t pipeline_parse_set_main_from_buf_c(struct ast_Module *module, struct ast_ASTArena *arena,
                                                                 uint8_t *data, int32_t len) {
    (void)module;
    (void)arena;
    (void)data;
    (void)len;
    return -1;
}

XLANG_WEAK int32_t pipeline_load_and_sync_direct_import_deps_c(struct ast_Module *module,
                                                                            struct ast_ASTArena *arena,
                                                                            struct ast_PipelineDepCtx *ctx) {
    (void)module;
    (void)arena;
    (void)ctx;
    return -1;
}

XLANG_WEAK int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx *ctx) {
    (void)ctx;
    return 0;
}

XLANG_WEAK void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx *ctx, int32_t idx,
                                                               uint8_t *dst) {
    (void)ctx;
    (void)idx;
    if (!dst)
        return;
    for (int i = 0; i < 64; i++)
        dst[i] = 0;
}

XLANG_WEAK int32_t pipeline_module_main_func_index(struct ast_Module *m) {
    (void)m;
    return -1;
}

/**
 * wave89: pure runtime_pipeline_abi owns product pipeline_typeck_dep_prerun_module_c.
 * This stub is only for cold/empty-surface links without pure or pipeline_glue.
 * pipeline_glue also keeps a full XLANG_WEAK cold twin (set_dep_ctx + typeck_x_ast_library).
 * PLATFORM: SHARED — pure strong wins under hybrid PREFER.
 */
XLANG_WEAK int32_t pipeline_typeck_dep_prerun_module_c(struct ast_Module *module, struct ast_ASTArena *arena,
                                                                  struct ast_PipelineDepCtx *ctx) {
    (void)module;
    (void)arena;
    (void)ctx;
    return -1;
}

XLANG_WEAK void pipeline_module_fixup_with_arena_stmt_orders(struct ast_Module *m, struct ast_ASTArena *a) {
    (void)m;
    (void)a;
}

XLANG_WEAK int32_t pipeline_module_func_name_len_at(struct ast_Module *m, int32_t func_index) {
    (void)m;
    (void)func_index;
    return 0;
}

XLANG_WEAK uint8_t pipeline_module_func_name_byte_at(struct ast_Module *m, int32_t fi, int32_t i) {
    (void)m;
    (void)fi;
    (void)i;
    return 0;
}

XLANG_WEAK void pipeline_module_func_name_copy64(struct ast_Module *m, int32_t fi, uint8_t *dst) {
    int i;
    (void)m;
    (void)fi;
    if (!dst)
        return;
    for (i = 0; i < 64; i++)
        dst[i] = 0;
}

XLANG_WEAK int32_t pipeline_module_func_body_ref_at(struct ast_Module *m, int32_t func_index) {
    (void)m;
    (void)func_index;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_num_consts(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_num_lets(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_num_regions(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

XLANG_WEAK int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena *a, int32_t br) {
    (void)a;
    (void)br;
    return 0;
}

/* ---- G-02e-13：原 ast_pool_l5_bridge（preprocess -D / labeled / typeck slots）---- */

/** #[cfg] 表达式求值（cfg_eval.x / bootstrap stub）；供 target_os == "linux" 等 #if 条件。 */
extern int cfg_eval_expr_c(const char *start, int len);

struct ast_LabeledStmt {
  uint8_t label[128];
  int32_t label_len;
  int32_t is_goto;
  uint8_t goto_target[128];
  int32_t goto_target_len;
  int32_t return_expr_ref;
};

struct ast_ASTArena;
struct ast_Module;
struct ast_PipelineDepCtx;

extern struct ast_LabeledStmt *pipeline_block_labeled_ptr(struct ast_ASTArena *a, int32_t br, int32_t li);
extern void driver_diagnostic_pipe_marker(int32_t id);
extern int32_t parser_copy_module_import_path64(struct ast_Module *module, int32_t i, uint8_t out[128]);
extern void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx *ctx, int32_t idx, uint8_t *bytes, int32_t len);

XLANG_WEAK struct ast_LabeledStmt *pipeline_block_labeled_ptr(struct ast_ASTArena *a, int32_t br, int32_t li) {
  (void)a;
  (void)br;
  (void)li;
  return NULL;
}

XLANG_WEAK void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx *ctx, int32_t idx, uint8_t *bytes,
                                                            int32_t len) {
  ast_pipeline_dep_ctx_set_import_path(ctx, idx, bytes, len);
}

/* wave99: product pure owns path64; this XLANG_WEAK is cold twin when pure not linked.
 * G.7: ImportEntry path storage = pipeline_module_import_path_copy (ast_pool).
 * PLATFORM: SHARED — semantics ≡ pure / parser_gen weak cold twin. */
extern void pipeline_module_import_path_copy(struct ast_Module *m, int32_t idx, uint8_t *dst, int32_t dst_cap);

XLANG_WEAK int32_t parser_copy_module_import_path64(struct ast_Module *module, int32_t i, uint8_t out[128]) {
  int32_t path_len;
  if (!out)
    return 0;
  if (!module) {
    out[0] = 0;
    return 0;
  }
  pipeline_module_import_path_copy(module, i, out, 64);
  path_len = 0;
  while (path_len < 64 && out[path_len] != 0)
    path_len++;
  return path_len;
}

/** 旧硬顶 32：pool-limits deep_if_nest 需 40 层 -DL；uname 等还会再占几槽。 */
#define PREPROCESS_MAX_DEFINES 128
static char g_preprocess_defines[PREPROCESS_MAX_DEFINES][64];
static int g_preprocess_ndefines;
static uint8_t g_typeck_scratch64[16][128];
static int32_t g_typeck_layout_metrics_sz_slot;
static int32_t g_typeck_layout_metrics_al_slot = 1;
static int32_t g_typeck_layout_metrics_sz_depth[64];
static int32_t g_typeck_layout_metrics_al_depth[64];
static int32_t g_typeck_call_resolve_dep_idx_slot;
static int32_t g_typeck_call_resolve_func_idx_slot;
/* PLATFORM: SHARED — weak fallback; strong def in runtime_pipeline_abi on product link
 * (ast_pool.c left wave309). */
static int32_t g_typeck_overload_expected_ret_slot;

XLANG_WEAK uint8_t *typeck_scratch64_slot(int32_t slot) {
  if (slot < 0)
    slot = 0;
  if (slot >= 16)
    slot = 15;
  return &g_typeck_scratch64[slot][0];
}

XLANG_WEAK int32_t *typeck_layout_metrics_sz_slot(void) {
  return &g_typeck_layout_metrics_sz_slot;
}

XLANG_WEAK int32_t *typeck_layout_metrics_al_slot(void) {
  return &g_typeck_layout_metrics_al_slot;
}

XLANG_WEAK int32_t *typeck_layout_metrics_sz_slot_depth(int32_t depth) {
  if (depth < 0)
    depth = 0;
  if (depth >= 64)
    depth = 63;
  return &g_typeck_layout_metrics_sz_depth[depth];
}

XLANG_WEAK int32_t *typeck_layout_metrics_al_slot_depth(int32_t depth) {
  if (depth < 0)
    depth = 0;
  if (depth >= 64)
    depth = 63;
  return &g_typeck_layout_metrics_al_depth[depth];
}

#ifndef XLANG_L2_STRICT_GLUE_THIN_FROM_X
XLANG_WEAK void typeck_layout_metrics_init_depth(int32_t depth) {
  int32_t *sz = typeck_layout_metrics_sz_slot_depth(depth);
  int32_t *al = typeck_layout_metrics_al_slot_depth(depth);
  if (sz)
    *sz = 0;
  if (al)
    *al = 1;
}

XLANG_WEAK int32_t typeck_layout_metrics_al_read_depth(int32_t depth) {
  return *typeck_layout_metrics_al_slot_depth(depth);
}

XLANG_WEAK int32_t typeck_layout_metrics_sz_read_depth(int32_t depth) {
  return *typeck_layout_metrics_sz_slot_depth(depth);
}

XLANG_WEAK void typeck_layout_metrics_init_slot(void) {
  *typeck_layout_metrics_sz_slot() = 0;
  *typeck_layout_metrics_al_slot() = 1;
}

XLANG_WEAK void typeck_i32_ptr_store(int32_t *p, int32_t v) {
  if (p)
    *p = v;
}

XLANG_WEAK int32_t typeck_i32_ptr_read(int32_t *p) {
  return p ? *p : 0;
}

XLANG_WEAK void typeck_driver_diagnostic_pipe_marker(int32_t id) {
  driver_diagnostic_pipe_marker(id);
}
#endif

XLANG_WEAK int32_t *typeck_call_resolve_dep_idx_slot(void) {
  return &g_typeck_call_resolve_dep_idx_slot;
}

XLANG_WEAK int32_t *typeck_call_resolve_func_idx_slot(void) {
  return &g_typeck_call_resolve_func_idx_slot;
}

XLANG_WEAK int32_t *typeck_overload_expected_ret_slot(void) {
  return &g_typeck_overload_expected_ret_slot;
}

#ifndef XLANG_L2_STRICT_GLUE_THIN_FROM_X
XLANG_WEAK int32_t typeck_call_resolve_dep_idx_peek(void) {
  return *typeck_call_resolve_dep_idx_slot();
}

XLANG_WEAK int32_t typeck_call_resolve_func_idx_peek(void) {
  return *typeck_call_resolve_func_idx_slot();
}

XLANG_WEAK int32_t typeck_overload_expected_ret_peek(void) {
  return *typeck_overload_expected_ret_slot();
}
#endif

XLANG_WEAK int32_t run_x_pipeline_fill_dep_import_path_c(struct ast_Module *module,
                                                                     struct ast_PipelineDepCtx *ctx, int32_t dep_j) {
  uint8_t path_buf[128];
  int32_t path_len;
  if (!module || !ctx || dep_j < 0)
    return -1;
  memset(path_buf, 0, sizeof(path_buf));
  (void)parser_copy_module_import_path64(module, dep_j, path_buf);
  path_len = 0;
  while (path_len < 64 && path_buf[path_len] != 0)
    path_len = path_len + 1;
  if (path_len > 0)
    pipeline_dep_ctx_set_import_path(ctx, dep_j, path_buf, path_len);
  return 0;
}

/**
 * wave85: pure runtime_pipeline_abi owns product preprocess_define_* (G.7 single -D table).
 * Glue keeps XLANG_WEAK cold fallback for links without pure pipeline_abi / PREFER hybrid.
 * PLATFORM: SHARED — same table semantics as pure (128 × 64).
 */
/** Clear -D macro table (weak cold fallback). */
XLANG_WEAK void preprocess_define_reset(void) {
  g_preprocess_ndefines = 0;
}

/** Append one -D macro name (weak cold fallback). */
XLANG_WEAK void preprocess_define_add(const char *name) {
  size_t n;
  if (!name || g_preprocess_ndefines >= PREPROCESS_MAX_DEFINES)
    return;
  n = strlen(name);
  if (n == 0 || n >= 64)
    return;
  memcpy(g_preprocess_defines[g_preprocess_ndefines], name, n + 1);
  g_preprocess_ndefines++;
}

/** True if sym[0..sym_len) is in -D table (weak cold fallback). */
XLANG_WEAK int32_t preprocess_define_has(const uint8_t *sym, int32_t sym_len) {
  int i, k;
  if (!sym || sym_len <= 0)
    return 0;
  for (i = 0; i < g_preprocess_ndefines; i++) {
    for (k = 0; k < sym_len; k++) {
      if (g_preprocess_defines[i][k] != (char)sym[k])
        break;
      if (g_preprocess_defines[i][k] == '\0')
        break;
    }
    if (k == sym_len && g_preprocess_defines[i][k] == '\0')
      return 1;
  }
  return 0;
}

/**
 * wave88: pure runtime_pipeline_abi owns product preprocess_eval_condition_c
 * (G.7 single authority: trim + simple → pure define_has; complex → cfg_eval_expr_c).
 * Glue keeps XLANG_WEAK cold fallback for links without pure pipeline_abi / PREFER hybrid.
 * PLATFORM: SHARED — same semantics as pure (space/tab trim; complex ops → cfg_eval).
 */
XLANG_WEAK int32_t preprocess_eval_condition_c(const uint8_t *cond, int32_t cond_len) {
  int k;

  if (!cond || cond_len <= 0)
    return 0;
  /* Trim leading/trailing whitespace. */
  while (cond_len > 0 && (cond[0] == ' ' || cond[0] == '\t')) {
    cond++;
    cond_len--;
  }
  while (cond_len > 0 && (cond[cond_len - 1] == ' ' || cond[cond_len - 1] == '\t'))
    cond_len--;
  if (cond_len <= 0)
    return 0;
  /* Complex conditions (spaces/operators) use Cap residual cfg_eval_expr_c. */
  for (k = 0; k < cond_len; k++) {
    char c = (char)cond[k];
    if (c == ' ' || c == '\t' || c == '=' || c == '!' || c == '(' || c == ')')
      return cfg_eval_expr_c((const char *)cond, cond_len) ? 1 : 0;
  }
  return preprocess_define_has(cond, cond_len) ? 1 : 0;
}

/** 写 labeled 槽的标签名与 goto 目标名。 */
void pipeline_block_labeled_set_names(struct ast_ASTArena *a, int32_t br, int32_t li, uint8_t *label, int32_t label_len,
                                      uint8_t *goto_target, int32_t goto_target_len) {
  struct ast_LabeledStmt *ls;
  if (!a || li < 0)
    return;
  ls = pipeline_block_labeled_ptr(a, br, li);
  if (!ls)
    return;
  if (label && label_len > 0) {
    /* wave586 Cap residual: label content ≤127 (LabeledStmt.label[128]). */
    if (label_len > 127)
      label_len = 127;
    memcpy(ls->label, label, (size_t)label_len);
    ls->label[label_len] = 0;
    ls->label_len = label_len;
  }
  if (goto_target && goto_target_len > 0) {
    /* wave586 Cap residual: goto target content ≤127. */
    if (goto_target_len > 127)
      goto_target_len = 127;
    memcpy(ls->goto_target, goto_target, (size_t)goto_target_len);
    ls->goto_target[goto_target_len] = 0;
    ls->goto_target_len = goto_target_len;
  }
}
