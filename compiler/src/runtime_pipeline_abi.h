/**
 * runtime_pipeline_abi.h — 编译器 C 侧 pipeline import / dep 槽 ABI 声明（Phase E-04 v24～v30）
 *
 * 文件职责：import 路径解析与 pipeline dep 全局槽（driver_dep_*）；供 pipeline.x / runtime.c 链接。
 * 所属模块：compiler 运行时 pipeline ABI；实现于 runtime_pipeline_abi.c。
 * 与其它文件的关系：不依赖 C 前端；与 pipeline.x 内 resolve 规则对齐。
 */

#ifndef XLANG_RUNTIME_PIPELINE_ABI_H
#define XLANG_RUNTIME_PIPELINE_ABI_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/** 与 ast.x PipelineDepCtx 内嵌源缓冲容量一致。 */
#define XLANG_PIPELINE_CTX_BUF_SIZE 4194304

struct ast_Module;
struct ast_ASTArena;

/**
 * 与 ast.x PipelineDepCtx 布局一致（含内嵌源缓冲）；dep/lib_root sidecar 由
 * runtime_pipeline_abi 堆上 grow（ast_pool.c left wave309）。
 * C 侧 pipeline / dep 预跑通过本结构向 .x pipeline 传路径与 dep 槽。
 */
struct ast_PipelineDepCtx {
    int32_t ndep;
    uint8_t entry_dir_buf[512];
    int32_t entry_dir_len;
    int32_t num_lib_roots;
    uint8_t path_buf[512];
    uint8_t loaded_buf[XLANG_PIPELINE_CTX_BUF_SIZE];
    ptrdiff_t loaded_len;
    uint8_t preprocess_buf[XLANG_PIPELINE_CTX_BUF_SIZE];
    int32_t preprocess_len;
    int32_t use_asm_backend;
    int32_t target_arch;
    int32_t target_cpu_features;
    int32_t use_macho_o;
    int32_t use_coff_o;
    int32_t current_block_ref;
    int32_t typeck_loop_depth;
    int32_t current_func_index;
    int32_t skip_codegen_dep_0;
    int32_t entry_already_parsed;
    int32_t current_func_single_empty_param_index;
    int32_t current_func_empty_param_count;
    int32_t current_emit_empty_var_next_index;
    int32_t emit_expr_as_callee;
    void *current_codegen_module;
    void *current_codegen_arena;
    int32_t current_codegen_dep_index;
    /*
     * wave577 Cap / wave579: name and path mirrors are u8[128] (63→127 usable).
     * Must match ast.x PipelineDepCtx and seed pipeline_gen (G.7 single layout).
     * History: residual [64] made driver_pipeline_dep_ctx_calloc undersized
     * (0x800588 vs 0x800600); typeck stack-escape memset of region_label stomped
     * the following heap chunk (dep_modules grow_vec) → hello SEGV on Ubuntu.
     * PLATFORM: SHARED — mac + Ubuntu product matrix after any size change.
     */
    uint8_t current_codegen_prefix_mirror[128];
    int32_t current_codegen_prefix_len;
    int32_t asm_entry_module_only;
    uint8_t entry_module_import_path_mirror[128];
    int32_t entry_module_import_path_len;
    /** M-3 typeck：与 ast.x PipelineDepCtx.typeck_scope_region_* 对齐。 */
    int32_t typeck_scope_region_len;
    uint8_t typeck_scope_region_label[128];
    /*
     * wave445 C5: monomorphization type-substitution state for generic function
     * body emit. When mono_active=1, emit_type replaces any type_ref matching
     * mono_generic_type_refs[i] with mono_concrete_type_refs[i] (T -> concrete).
     * PLATFORM: SHARED — layout authority; .x mirrors in emit.x + ast.x must match.
     */
    int32_t mono_active;                /* 0 = inactive, 1 = mono body emit active */
    int32_t mono_num_types;             /* count of generic type params to substitute (1..8) */
    int32_t mono_generic_type_refs[8];  /* type refs to replace (T, U, ...) */
    int32_t mono_concrete_type_refs[8]; /* concrete type refs to use (A, B, ...) */
};

/** pipeline dep 全局槽数量（与 pipeline.x / runtime 预跑 dep 上限一致）。 */
#define XLANG_DRIVER_DEP_SLOT_MAX 32

/**
 * 对原始 .x 做 preprocess.x 条件编译，写入新分配 NUL 结尾字符串。
 * 参数：defines/ndefines 为 -D 宏；path_diag 用于错误信息。
 * 返回值：0 成功；失败写 stderr 且不分配 *out_src。
 */
int xlang_preprocess_raw_to_malloc(const unsigned char *raw, size_t raw_len, char **out_src, size_t *out_src_len,
    const char *path_diag, const char **defines, int ndefines);
char *xlang_preprocess_with_path(const char *source, size_t source_len, const char *path_diag,
    const char **defines, int ndefines, size_t *out_length);
char *xlang_preprocess_quiet(const char *source, size_t source_len, const char **defines, int ndefines, size_t *out_length);

/** 预处理/dep import 失败已输出结构化诊断的标志；供上层避免重复补摘要。 */
void pipeline_diag_emitted_reset(void);
void pipeline_diag_emitted_note(void);
int32_t pipeline_diag_emitted_get(void);
void pipeline_diag_import_open_fail_once(const char *import_path, const char *resolved_path);

/** typeck/pipeline 兼容 dep 侧车（pipeline_gen.c / get_dep_*）。 */
extern void *typeck_dep_module_ptrs[32];
extern void *typeck_dep_arena_ptrs[32];
extern int typeck_ndep;
void *get_dep_module(int32_t i);
void *get_dep_arena(int32_t i);
int32_t get_ndep(void);
void *typeck_get_dep_module(int32_t i);
void *typeck_get_dep_arena(int32_t i);
void pipeline_set_dep(int32_t i, void *mod, void *arena);
void pipeline_set_ndep(int32_t n);

/**
 * 清 typeck dep 侧车；由 driver_dep_seeded_clear_all 调用。
 */
void driver_typeck_dep_sidecar_clear(void);

/**
 * 将逻辑 import 路径转为 lib_root 下的 .x 文件路径（'.' → '/'）。
 * 参数：lib_root 库根；import_path 如 "core.types"；path/path_size 输出缓冲。
 */
void xlang_import_path_to_file_path(const char *lib_root, const char *import_path, char *path, size_t path_size);

/**
 * 从入口 .x 路径得到所在目录；无目录时写入 "."。
 */
void xlang_get_entry_dir(const char *input_path, char *entry_dir, size_t size);

/**
 * 判断 import 是否为文件路径（相对/绝对/.x），而非逻辑模块名 std.io。
 * 返回值：非 0 表示文件路径形式。
 */
int xlang_import_path_is_file_path(const char *import_path);

/**
 * 将相对/绝对文件路径解析为可打开的 .x 路径（相对 entry_dir）。
 */
void xlang_resolve_file_import_path(const char *entry_dir, const char *import_path, char *path, size_t path_size);

/**
 * 在 lib_roots 与 entry_dir 下解析 import 到可读 .x 路径（单文件 / mod.x / 同目录 fallback）。
 * 参数：lib_roots/n_lib_roots 与 -L 一致；path 输出；path_size 缓冲容量。
 */
void xlang_resolve_import_file_path_multi(const char **lib_roots, int n_lib_roots, const char *entry_dir,
    const char *import_path, char *path, size_t path_size);

/** pipeline.x extern：dep 槽 seeded 标志与 arena/module 缓冲 getter。 */
int32_t driver_dep_seeded_get(int32_t i);
void driver_dep_seeded_set(int32_t i, int32_t v);
void driver_dep_seed_slots(void *arenas[32], void *modules[32], int32_t n);
void driver_dep_publish_slot(int32_t i, void *arena, void *module, const char *import_path);
int32_t driver_dep_slot_for_path(const char *path);
void driver_dep_seeded_clear_all(void);
uint8_t *driver_dep_arena_buf(int32_t i);
uint8_t *driver_dep_module_buf(int32_t i);

/** typeck.x codegen 导出名；转发至 driver_dep_* 槽。 */
uint8_t *typeck_driver_dep_module_buf(int32_t i);
int32_t typeck_driver_dep_seeded_get(int32_t i);

/**
 * 在已加载 import 列表中查找下标（load_one_import / dep 预读去重）。
 * 返回值：0..n_all-1，未找到 -1。
 */
int xlang_find_loaded_import_index(const char *import_path, char **all_paths, int n_all);

/**
 * dep 预跑 resolve 时 entry_dir：lib_roots[0] 优先于主文件目录。
 */
const char *xlang_dep_prerun_entry_dir(const char *main_entry_dir, const char **lib_roots, int n_lib_roots);

/**
 * 从入口 .x 路径推导 -E 库模块 C 前缀（pipeline/typeck/...）。
 */
const char *xlang_entry_lib_name_from_path(const char *input_path);

/** Historical -E surface; wave309 no-op (pipeline_glue.c shell retired). */
void xlang_emit_pipeline_glue_include(void);

/** asm 后端：stdout 句柄（fd 1）无缓冲无需 flush，其它句柄经 Cap 关闭。
 *  Cap residual 9.7.1: opaque fd handle（见 xlang_driver_stream_cap.h）。 */
void driver_asm_fclose_asm_out(uint8_t *fp);

/** 判断 codegen 输出缓冲是否已为 Mach-O/ELF 对象魔数。 */
int xlang_asm_out_buf_is_object(const unsigned char *data, size_t len);

/**
 * 填充 PipelineDepCtx 的 entry_dir_buf 与 lib_root sidecar，供 .x resolve_path_x 使用。
 */
void xlang_pipeline_fill_ctx_path_buffers(struct ast_PipelineDepCtx *ctx, const char *entry_dir,
    const char **lib_roots, int n_lib_roots);

/**
 * 将 C 侧 dep 槽写入 PipelineDepCtx sidecar（与 ast.x pipeline_dep_ctx_* 对齐）。
 */
void xlang_pipeline_pctx_seed_dep_slots(struct ast_PipelineDepCtx *ctx, void **dep_mods, void **dep_ar,
    char **import_paths, int n);

/** 仅写入 import_path + ndep，不预置 module/arena；供 entry pipeline 自行 load/sync direct imports。 */
void xlang_pipeline_pctx_seed_dep_import_paths_only(struct ast_PipelineDepCtx *ctx, char **import_paths, int n);

/**
 * 单 dep 预跑 ctx：保留 lib_root；dep 槽按该 dep 源码的 import 表过滤（与 entry 全量 dep 表对齐 global 槽）。
 * dep_src/dep_src_len 非空时扫描 import 路径；否则回退写入 entry 全量 dep 槽。
 */
void xlang_pipeline_one_ctx_for_dep_prerun(struct ast_PipelineDepCtx *ctx, int j, void **dep_mods,
                                          void **dep_ars, char **dep_paths, int ndep, const uint8_t *dep_src,
                                          size_t dep_src_len);

/** asm 用户程序：std.io/fs/net dep 是否跳过 .x typeck。 */
int xlang_asm_user_std_dep_skip_x_typeck(const char *dep_path);

/** std.net dep 路径（co-emit 前须 parse 填 funcs）。 */
int xlang_asm_user_std_net_dep_path(const char *dep_path);

/** std.io.driver dep 路径（co-emit submit_* 包装）。 */
int xlang_asm_user_std_io_driver_dep_path(const char *dep_path);

/** dep 预跑 parse+skip typeck 路径（std.net / std.io.driver）。 */
int xlang_asm_user_dep_parse_skip_typeck_path(const char *dep_path);

/** parser / pipeline 切片（与 pipeline.x xlang_slice 一致）。 */
struct xlang_slice_uint8_t {
    uint8_t *data;
    size_t length;
};

/** pipeline.x import 加载缓冲容量（与 runtime 原 PIPELINE_IMPORT_BUF_CAP 一致）。 */
#define XLANG_PIPELINE_IMPORT_BUF_CAP 4194304

/** 阶段 5.3：pipeline.x 编排用最小 C I/O 原语（resolve/read/parse）。 */
void pipeline_set_entry_dir(const char *path);
void pipeline_set_dep_slots(void *arenas[32], void *modules[32]);
int32_t pipeline_resolve_path(const uint8_t *path_ptr, int32_t path_len);
int32_t pipeline_read_file(void);
void *pipeline_get_dep_arena_slot(int32_t i);
void *pipeline_get_dep_module_slot(int32_t i);
int32_t pipeline_parse_into_loaded_import(void *arena, void *module);

/** 大栈 pthread 上跑 pipeline_run_x_pipeline；失败回退当前线程。 */
int xlang_pipeline_run_x_pipeline_large_stack(void *module, void *arena, const uint8_t *source_data, size_t source_len,
    void *out_buf, void *ctx);

/** dep 预跑：parse+skip typeck/codegen（std.net co-emit 前填 funcs）。 */
int xlang_pipeline_dep_prerun_parse_skip_typeck(void *dep_mod, void *dep_arena, const uint8_t *src, size_t len,
    void *dep_out, void *one_ctx);

/** dep 预跑：parse+typeck only，跳过 codegen。 */
int xlang_pipeline_dep_prerun_typeck_only(void *dep_mod, void *dep_arena, const uint8_t *src, size_t len, void *dep_out,
    void *one_ctx);

/** dep 预跑：仅 parse_into（ENTRY_MODULE_ONLY）。 */
int xlang_pipeline_dep_prerun_parse_only(void *dep_mod, void *dep_arena, const uint8_t *src, size_t len);

/** asm 单模块 -o dep 预跑（typeck_only 包装）。 */
int xlang_pipeline_dep_prerun_for_asm_module_o(void *dep_mod, void *dep_arena, const uint8_t *src, size_t len,
    void *dep_out, void *one_ctx);

/** 从源文件 path 提取所在目录（递归 import 时作 dep_dir）；无 slash 时用 "."。 */
int xlang_import_dep_dir_from_path(const char *path, char *dep_dir, size_t dep_dir_size);

/** dep 路径是否已在 out_paths[0..n_out) 中（asm layout merge 去重）。 */
int xlang_merge_deps_path_already_out(const char *path, char *out_paths[], int n_out);

/**
 * build_xlang_asm ENTRY_MODULE_ONLY：仅读 direct import 源码填 dep layout（不递归闭包）。
 * 返回 0 成功；失败释放已写入 dep_sources/dep_paths 并返回 1。
 */
int xlang_load_direct_imports_for_asm_layout(void *module, const char **lib_roots_arr, int n_lib_roots,
    const char *entry_dir, const char **defines, int ndefines, char *dep_sources[], size_t dep_lens[],
    char *dep_paths[], int *out_n);

/** 将传递闭包 merge 为 pipeline/asm_elf dep 列表（direct import 槽对齐 + 路径去重）。 */
int xlang_merge_direct_then_transitive_deps(void *module, int32_t n_imports, char *cls[], size_t clens[], char *cpaths[],
    int n_closure, char *out_src[], size_t out_lens[], char *out_paths[], int *out_n);

/** 将传递闭包 merge 为 pipeline/asm_elf dep 列表（仅路径：direct import 槽对齐 + 路径去重）。 */
int xlang_merge_direct_then_transitive_dep_paths(void *module, int32_t n_imports, char *cpaths[], int n_closure,
    char *out_paths[], int *out_n);

/** 从入口 module import 递归收集传递 dep 源码；返回 0 成功，1 失败。 */
int xlang_collect_deps_transitive(void *module, size_t arena_sz, size_t module_sz, const char **lib_roots_arr,
    int n_lib_roots, const char *entry_dir_buf, const char **defines, int ndefines, char *dep_sources[],
    size_t dep_lens[], char *dep_paths[], int *n_deps);

/** 从入口 module import 递归收集传递 dep 路径（不保留 dep 源码文本，降低峰值内存）；返回 0 成功，1 失败。 */
int xlang_collect_dep_paths_transitive(void *module, size_t arena_sz, size_t module_sz, const char **lib_roots_arr,
    int n_lib_roots, const char *entry_dir_buf, const char **defines, int ndefines, char *dep_paths[], int *n_deps);

/** asm_codegen_elf_o 前：skip_heavy 上下文 + ARRAY_LIT/SoA 类型补全（C typeck 跳过后）。 */
void xlang_driver_asm_prepare_entry_elf_emit(void *module, void *arena, void *pctx);

struct platform_elf_ElfCodegenCtx;

/** 256MiB 栈 pthread 上调用 asm_asm_codegen_elf_o；pthread 失败时回退当前线程。 */
int32_t xlang_asm_codegen_elf_o_large_stack(void *module, void *arena, void *ctx,
    struct platform_elf_ElfCodegenCtx *elf_ctx, void *out_buf);

/** 使用 typeck_ndep / typeck_dep_module_ptrs 对入口模块做 C typecheck（大模块 asm 构建用）。 */
int32_t pipeline_typeck_module_for_ctx(void *module, void *arena, void *ctx_void);

/** 释放 xlang_lsp_resolve_and_load_imports 写入的 all_dep_mods / all_dep_paths。 */
void xlang_lsp_free_loaded_imports(struct ast_Module **all_dep_mods, char **all_dep_paths, int n_all);

/**
 * 对 .x 源码做条件编译预处理（malloc 结果，调用方 free）。
 * bootstrap/driver 默认走 preprocess.x（xlang_preprocess_raw_to_malloc）；XLANG_LEGACY_PREPROCESS_C=1 走 C fallback。
 */
char *xlang_preprocess(const char *source, size_t source_len, const char **defines, int ndefines, size_t *out_length);

/**
 * 传递闭包 seed 的 ctx.ndep 与 entry 直接 import 数不一致时清零 ndep
 * （实现于 runtime_pipeline_abi；ast_pool.c / pipeline_x mega left wave309）。
 */
void pipeline_dep_ctx_realign_ndep_for_entry_c(struct ast_Module *module, struct ast_PipelineDepCtx *ctx);

#endif /* XLANG_RUNTIME_PIPELINE_ABI_H */
