/**
 * codegen.h — 代码生成接口
 *
 * 文件职责：声明将 AST 生成 C 源码的两个入口（入口模块含 main、库模块占位），供 Driver 在 typeck 之后调用并交给 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；被 src/main 引用。
 * 与其它文件的关系：依赖 ASTModule（前向声明），实现时包含 ast.h；不依赖 lexer/parser/typeck；输出流由 main 管理。
 * 重要约定：阶段 4 方案 B，入口模块生成 Hello World 的 printf 且 return 使用 main 体表达式的值（当前仅整数字面量）；库模块仅生成注释行（阶段 7.3）。阶段 8.1 DCE：可选传入 is_func_used/is_mono_used 仅生成被引用的函数与单态化实例。
 */

#ifndef XLANG_CODEGEN_H
#define XLANG_CODEGEN_H

#include <stdio.h>
#include <stdint.h>

struct ASTModule;
struct ASTFunc;

/** 阶段 8.1 DCE：可选回调，若非 NULL 则仅生成被引用函数/单态化/类型。ctx 由调用方传入。 */
typedef int (*codegen_is_func_used_fn)(void *ctx, const struct ASTModule *mod, const struct ASTFunc *func);
typedef int (*codegen_is_mono_used_fn)(void *ctx, const struct ASTModule *mod, int mono_k);
/** 阶段 8.1 DCE 扩展：若提供则仅生成被引用的结构体/枚举定义；NULL 表示全部输出。 */
typedef int (*codegen_is_type_used_fn)(void *ctx, const struct ASTModule *mod, const char *type_name);

/** 单文件多模块时避免 enum/struct 重定义：调用方提供 emitted_type_names[][64] 与 *n_emitted_inout；codegen 输出前检查、输出后追加 C 类型名。NULL 表示不启用。 */
#define CODEGEN_EMITTED_TYPE_NAME_MAX 64

/** pipeline 单文件时 preamble（write_io_net_abi_inline）已输出 core.option/core.result 的 Option_i32/Result_i32；置 1 时 codegen_library_module_to_c 跳过二者避免重定义。 */
void codegen_set_preamble_has_core_option_result(int on);

/** write_io_net_abi_inline 可选段：codegen.x 在 emit 与 preamble 重叠符号时 OR 入 mask，runtime 写 preamble 时跳过对应行。 */
#define CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS    1u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_DRIVER_HANDLE  2u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE 4u
#define CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH         8u
void codegen_reset_preamble_skip_mask(void);
void codegen_or_preamble_skip_mask(unsigned mask);
unsigned codegen_get_preamble_skip_mask(void);

/**
 * 将入口模块（含 main）生成 C 源码写入 out。
 * 若 is_func_used/is_mono_used 非 NULL，仅生成被引用函数与单态化实例；若 is_type_used 非 NULL 则仅生成被引用 struct/enum（阶段 8.1 DCE）。
 * emitted_type_names/n_emitted_inout/max_emitted 非 NULL 时用于单文件去重：已出现的 C 类型名不再输出。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);

/**
 * 将库模块（无 main 或仅 import）生成 C 写入 out；若 is_*_used 非 NULL 则仅生成被引用部分（阶段 8.1 DCE）。
 * lib_dep_mods / lib_dep_paths / n_lib_dep 为该库模块的 import 依赖，用于生成跨模块调用时的 C 前缀（传递依赖）。
 * emitted_type_names/n_emitted_inout/max_emitted 非 NULL 时用于单文件去重。
 * emit_entry_path：单文件 -E-extern 时传入入口 .x 路径（如 src/lsp/lsp_io.x），用于内嵌原 lsp_*_extern.h 等价块；其它情况传 NULL。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep,
    FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted,
    const char *emit_entry_path);

/**
 * 阶段 8.1 DCE：从 main 起算可达性，填充 used_funcs 与 used_mono。used_funcs 与 used_mono 由调用方分配。
 * used_mono 为 (1+ndep) 行、每行 AST_MODULE_MAX_MONO_INSTANCES 的 int 数组，used_mono[0] 为入口模块，used_mono[1+i] 为 dep_mods[i]。
 */
void codegen_compute_used(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs_out, int *n_used_out, int max_used,
    int used_mono[][64]);

/** 入口根函数：main_func 或名为 entry/main 的顶层函数。 */
struct ASTFunc *codegen_entry_root_func(struct ASTModule *entry);

/**
 * WPO v0（S5 前置）：全程序 call graph 可达性；`XLANG_WPO_DCE=1` 时 runtime 用于跨模块 dead export 剔除。
 */
#define CODEGEN_WPO_REACH_MAX_FUNCS 4096
typedef struct CodegenWpoReach {
    struct ASTFunc *funcs[CODEGEN_WPO_REACH_MAX_FUNCS];
    struct ASTModule *mod_of[CODEGEN_WPO_REACH_MAX_FUNCS];
    unsigned char reachable[CODEGEN_WPO_REACH_MAX_FUNCS];
    int nfuncs;
    int root_id;
    int valid;
} CodegenWpoReach;

void codegen_wpo_reach_compute(CodegenWpoReach *out,
    struct ASTModule *entry,
    struct ASTModule **all_mods, int n_all);

/** 函数是否在 WPO 图从 entry/main 可达；mod 用于指针不一致时按模块+名字兜底。 */
int codegen_wpo_reach_is_reachable(const CodegenWpoReach *wpo, const struct ASTModule *mod, const struct ASTFunc *func);

/**
 * 阶段 8.1 DCE 扩展：从已用函数与 mono 中收集被引用的类型名（struct/enum），并做结构体字段传递闭包；结果写入 used_type_names_out，供 is_type_used 使用。
 */
void codegen_compute_used_types(struct ASTModule *entry, struct ASTModule **dep_mods, int ndep,
    struct ASTFunc **used_funcs, int n_used, const char **used_type_names_out, int *n_out, int max_types);

/**
 * 阶段 3.1（完全脱离 C 路线图）：仅输出依赖模块的类型定义（enum/struct，带 import 前缀），不输出函数体。
 * 供 -E-extern 生成「瘦」pipeline_gen.c 时先输出 ast/parser/typeck/codegen 等类型，再输出入口模块（extern + 本体）。
 * emitted_type_names：与入口模块共享去重表，避免 xlang_slice_* 等跨阶段重复定义（C-04 v3）。
 */
int codegen_emit_dep_types_only(struct ASTModule **mods, const char **import_paths, int n, FILE *out,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);

/**
 * C-04 -E-extern：设置入口 .x 路径（parser.x 等），供 dep 阶段 post-struct extern 与 import 剪枝。
 * runtime/driver 在 emit_extern_imports 写 dep 类型前调用；传 NULL 清空。
 */
void codegen_set_eextern_entry_path(const char *entry_path);

/**
 * .x pipeline 用：在调用 pipeline_run_x_pipeline 前设置 dep 模块与路径，使 codegen 生成跨 dep 调用时使用正确 C 符号前缀（如 std_io_driver_）；调用后由 pipeline 或 driver 在适当时机清空。
 */
void codegen_set_dep_slots_for_x_pipeline(struct ASTModule **mods, const char **paths, int n);

/**
 * WPO-S1/S2：从 entry + 全部传递依赖模块构建 call graph 并输出 JSON（version 2）。
 * 节点=函数、边=静态 CALL/METHOD_CALL；call_sites 含全整型常量实参 profile（WPO-S2 特化前置）。
 * 由 runtime 在 typeck 通过后、XLANG_WPO_DUMP_CALLGRAPH 指向路径（或 "-"=stdout）时调用。
 */
void codegen_dump_wpo_callgraph_json(uint8_t *out,
    struct ASTModule *entry, const char *entry_path,
    struct ASTModule **all_mods, const char **all_paths, int n_all);

/**
 * WPO-S2 monomorphize：全常量实参 + callee 为 `return param0 binop param1`（i32 标量）时，
 * 收集需生成的单态 thunk（如 scale__wpo_1024_64 → mov imm; ret）。
 */
#define CODEGEN_WPO_MAX_MONO_THUNKS 256
#define CODEGEN_WPO_MONO_SYM_MAX 128
#define CODEGEN_WPO_MONO_MAX_ARGS 8

typedef struct CodegenWpoMonoThunk {
    char sym[CODEGEN_WPO_MONO_SYM_MAX];
    char base_name[64];
    int nargs;
    int args[CODEGEN_WPO_MONO_MAX_ARGS];
    int32_t result_imm;
    unsigned char valid;
} CodegenWpoMonoThunk;

typedef struct CodegenWpoMonoThunks {
    CodegenWpoMonoThunk thunks[CODEGEN_WPO_MAX_MONO_THUNKS];
    int n;
} CodegenWpoMonoThunks;

void codegen_wpo_collect_mono_thunks(CodegenWpoMonoThunks *out,
    struct ASTModule *entry,
    struct ASTModule **dep_mods, int ndep,
    const char *entry_path);

/** 格式化单态符号：base + __wpo + _arg0 + _arg1（负实参用 _n123）。成功返回 sym 长度，失败 -1。 */
int codegen_wpo_mono_sym_format(const char *base, int nargs, const int *args, char *out, int cap);

/** std.fmt / std.debug 任意类型 JSON 打印：非 0 时生成 C 须注入 runtime_fmt_any.h。 */
extern int codegen_fmt_json_helpers_needed;
void codegen_emit_fmt_json_helpers_once(FILE *out);

/** CORE-009：emit xlang_builtin_* static inline 包装器（clz/ctz/popcount/bswap/rotl/rotr）。
 * 在每个生成 C 翻译单元 includes 之后调用一次，避免调用点经 builtin_intrinsic_name 重映射后无声明。 */
void codegen_emit_builtin_inline_decls(FILE *out);

#endif /* XLANG_CODEGEN_H */
