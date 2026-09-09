/**
 * runtime_driver_abi.h — 编译器 C 侧 driver 状态 ABI 声明（Phase E-04 v22～v29）
 *
 * 文件职责：声明 driver CLI / pipeline 跳过标志、asm 环境、阶段计时与 check 输出辅助。
 * 所属模块：compiler 运行时 ABI；实现于 runtime_driver_abi.c。
 * 与其它文件的关系：runtime.c 仍承载 pipeline/run_compiler_c 主体；本头不依赖 C 前端头。
 */

#ifndef XLANG_RUNTIME_DRIVER_ABI_H
#define XLANG_RUNTIME_DRIVER_ABI_H

#include <stdint.h>
#include <stddef.h>

/** xlang check：非 0 时 typeck 通过后跳过 codegen 与链接。 */
void driver_check_only_set(int32_t v);
int32_t driver_check_only_get(void);
void driver_check_diag_emitted_reset(void);
void driver_check_diag_emitted_note(void);
int32_t driver_check_diag_emitted_get(void);

/** `-freestanding`：用户程序 nostdlib 静态链。 */
void driver_freestanding_set(int32_t v);
int32_t driver_freestanding_get(void);

/** `-fsanitize=address` / XLANG_SANITIZE_ADDRESS=1 时强制边界检查。 */
void driver_sanitize_address_set(int32_t v);
int32_t driver_sanitize_address_get(void);

/** xlang fmt --check：仅校验格式，不写回。 */
void driver_fmt_check_only_set(int32_t v);
int32_t driver_fmt_check_only_get(void);

/** 非 X 链或未链 fmt_check_cmd 时弱符号默认 0（批量 check 成功时静默）。 */
int driver_check_quiet_ok_get(void);

/** 统一 xlang check 成功行；deno 风格批量 check 时由 fmt_check_cmd 保持静默。 */
void driver_print_check_ok(const char *input_path);

/** 非 0 时 pipeline 跳过 .x typeck（C 预检已通过）。 */
void driver_x_pipeline_skip_typeck_set(int32_t v);
int32_t driver_x_pipeline_skip_typeck_get(void);

/** 非 0 时 pipeline 跳过 .x C codegen（用户 asm -o 单路径 emit）。 */
void driver_x_pipeline_skip_codegen_set(int32_t v);
int32_t driver_x_pipeline_skip_codegen_get(void);

/** XLANG_TYPECK_FORCE_C=1 时入口模块 typeck 走 C typeck_module。 */
int32_t driver_typeck_force_c_enabled(void);

/** 当前线程是否已在 driver 大栈 pthread 内（避免 LSP 嵌套再分配大栈）。 */
int driver_is_large_stack_thread(void);

/**
 * 标记当前线程是否处于大栈执行上下文（runtime 内 pthread  trampoline 调用）。
 * 参数：on 非 0 进入大栈上下文，0 退出。
 */
void driver_large_stack_thread_mark(int on);

/** 提升 RLIMIT_STACK 软上限（run_compiler / pipeline 入口前调用）。 */
void driver_bump_stack_limit(void);

/**
 * 在 256MiB 栈 pthread 上执行 fn(arg)；LSP / pipeline / typeck 深栈场景使用。
 * XLANG_PIPELINE_NO_LARGE_STACK=1 时于当前线程直接执行。
 */
void driver_run_thread_on_large_stack(void *(*fn)(void *), void *arg);

/** 对外别名：与 driver_run_thread_on_large_stack 相同（LSP 主循环等）。 */
void driver_run_on_large_stack_pthread(void *(*fn)(void *), void *arg);

/**
 * Cap-fn-ptr residual：绑定 driver_stack_esc_gate_thread_fn 后进大栈。
 * wave37 pure：hybrid thin owns orch（fn_ptr residual + driver_run_thread_on_large_stack）；
 * always-seed：driver_stack_esc_gate_thread_fn_ptr；cold twin under #ifndef FROM_X。
 * .x 无法取函数地址；rt_stack R2 经此入口调用。
 */
void driver_run_stack_esc_gate_on_large_stack(void *arg);
/** Always-seed Cap-fn-ptr residual: opaque address of driver_stack_esc_gate_thread_fn. */
uint8_t *driver_stack_esc_gate_thread_fn_ptr(void);

/**
 * Cap residual：opaque FILE* 给 .x（rt_entry R2 等 diag_print_*）。
 * .x 无 FILE 类型。wave39 pure：driver_stdio_stdout via g05 stdout_ptr；
 * wave40 pure：driver_stdio_stderr via g05 stderr_ptr；cold twins under #ifndef FROM_X。
 */
void *driver_stdio_stdout(void);
void *driver_stdio_stderr(void);

/**
 * Cap residual：rt_entry R2 扫描/消息缓冲与 fmt argv。
 * .x 勿用局部 u8[N]（-E 会抬 init_globals / 丢函数）。
 * wave15 pure：entry_* / path slots（BSS u8[N]）。
 * wave21 pure：fmt_argv_slot — hybrid thin owns fixed {"xlang","fmt"} via
 *   byte-lit BSS + 2× LP64 ptr slots (G.7 xlang_ptr_slot_set); cold seed keeps C static.
 * ABI: returns base of char*[2] (same as opaque *u8 base under thin return type).
 */
uint8_t *driver_entry_ab_slot(void);
uint8_t *driver_entry_code_slot(void);
uint8_t *driver_entry_suggest_slot(void);
uint8_t *driver_entry_msg_slot(void);
uint8_t *driver_entry_tmp_slot(void);
uint8_t *driver_entry_tmp2_slot(void);
char **driver_entry_fmt_argv_slot(void);

/**
 * Cap residual：rt_run_exec R2 usage 写 stdout。
 * wave44 pure under PREFER: color policy orch（NO_COLOR / CLICOLOR_FORCE /
 *   XLANG_FORCE_COLOR / isatty）；cold twin under #ifndef XLANG_L2_RDABI_THIN_FROM_X。
 * Always-seed residual: xlang_driver_usage_write_stdout（巨型 plain/color lit，
 *   经 xlang_io_write(1,…) Cap io 写）。.x 禁含 \\n 长字串字面量（-E 编码/丢体）
 *   → 表留 residual。
 */
void driver_print_usage_write(void);
/** Permanent Cap residual: giant usage tables via xlang_io_write(1, …) Cap io. Always-seed. */
void xlang_driver_usage_write_stdout(int32_t use_color);

/**
 * Cap residual：rt_run_exec R2 driver_exec_compiled 体。
 * wave42 pure under PREFER: null/argc + G.7 path_is_non_exe + residual scan/spawn；
 * cold twin under #ifndef XLANG_L2_RDABI_THIN_FROM_X。
 * Always-seed residual: xlang_driver_exec_scan_out_path_opaque + xlang_driver_exec_spawn_wait。
 * .x 禁 *u8→**u8 cast / let **u8（-E 整函数丢体）→ cast 留 residual。
 */
int driver_exec_compiled_body(int argc, uint8_t *argv_opaque);
/** Permanent Cap residual: *u8 argv → cast + driver_exec_scan_out_path. */
uint8_t *xlang_driver_exec_scan_out_path_opaque(int32_t argc, uint8_t *argv_opaque);
/** Permanent OS residual: spawn/fork product exe and wait. 9.4.3: run_argv
 * rides along; user positionals after the .x source path become the child's
 * argv (C ABI). v1: value-taking driver flags (-o/-O/-L/-backend/-target/
 * -target-cpu) also skip their separate value. PLATFORM: WIN vs POSIX. */
int32_t xlang_driver_exec_spawn_wait(uint8_t *exe, int32_t argc, uint8_t *argv_opaque);

/**
 * Cap-global-bss residual：rt_emit_state R2 经槽写共享 emit 状态。
 * .x export let 会变 static，不能跨 TU 导出 path_buf / lib_roots；数据在 rest seed。
 * Always-seed data residual：path/lib/scan slots + c_path_cell + lib_roots_raw + n/want slots。
 * wave33 pure：clear/bind/take/get/lib_root_at/effective/try_extern under PREFER hybrid thin
 * （G.7 xlang_ptr_slot_*；cold C twins under #ifndef XLANG_L2_RDABI_THIN_FROM_X）。
 */
uint8_t *driver_x_emit_path_buf_slot(void);
uint8_t *driver_x_emit_lib_buf_slot(int i);
uint8_t *driver_x_emit_scan_ab_slot(void);
uint8_t *driver_x_emit_scan_nx_slot(void);
/** Always-seed: &driver_x_emit_c_path as 1-slot G.7 pointer table base. */
uint8_t *driver_x_emit_c_path_cell(void);
/** Always-seed: base of driver_x_emit_lib_roots[16] pointer table. */
uint8_t *driver_x_emit_lib_roots_raw(void);
/** wave33 pure: set c_path cell null via G.7; cold C twin. */
void driver_x_emit_clear_c_path(void);
/** wave33 pure: bind c_path cell to path_buf_slot; cold C twin. */
void driver_x_emit_bind_c_path_to_buf(void);
/** wave33 pure: lib_roots[i] = lib_bufs[i] via G.7; cold C twin. */
void driver_x_emit_bind_lib_root(int i);
int32_t *driver_x_emit_n_lib_roots_slot(void);
int32_t *driver_x_emit_want_extern_slot(void);

/**
 * Cap-global-bss residual：rt_arena_buf R2 经槽访问 128MiB/2MiB 静态缓冲。
 * 数据定义在 seeds/rt_arena_buf.from_x.c（跨 TU 非 static）。
 * wave37 pure：hybrid thin owns slot/size；always-seed base residual；cold twins under #ifndef FROM_X。
 */
uint8_t *driver_arena_static_base(void);
uint8_t *driver_module_static_base(void);
uint8_t *driver_arena_static_slot(void);
uint8_t *driver_module_static_slot(void);
size_t driver_arena_static_size(void);
size_t driver_module_static_size(void);

/**
 * Cap-giant-string residual：rt_preamble R2 巨型 C 字串表行访问。
 * 数据定义在 seeds/rt_preamble.from_x.c（跨 TU 非 static 表）；.x 禁巨型字串表。
 * write_* 业务循环在 .x。
 * wave20 pure：hybrid thin owns line_at/count；always-seed *_lines_raw 表基址；
 * cold C twins under #ifndef XLANG_L2_RDABI_THIN_FROM_X。
 */
uint8_t *driver_preamble_io_net_lines_raw(void);
uint8_t *driver_preamble_fs_path_lines_raw(void);
uint8_t *driver_preamble_io_net_line_at(int32_t i);
int32_t driver_preamble_io_net_line_count(void);
uint8_t *driver_preamble_fs_path_line_at(int32_t i);
int32_t driver_preamble_fs_path_line_count(void);

/**
 * Cap residual G.7 authority：rt_preamble / async emit R2 fputs 经 opaque *u8（FILE*）。
 * wave22 pure：hybrid thin owns body（null 守卫 + g05 xlang_driver_fputs_opaque cast）；
 * cold C twin under #ifndef XLANG_L2_RDABI_THIN_FROM_X。
 * .x 禁 FILE* 类型；直接 fputs(*u8,*u8) 在 -Werror=incompatible-pointer-types 硬失败。
 */
int32_t driver_preamble_fputs(uint8_t *s, uint8_t *stream);

/**
 * Cap residual：rt_run_x_emit R2 平台/巨型布局缺口。
 * 业务控制流在 .x；本层：stdout 无缓冲+写（permanent OS residual）、
 * 9MiB CodegenOutBuf 分配/字段、指针/size 表、parse_into out-param、
 * diag snapshot opaque、typeck 槽、PATH_MAX 槽。
 * wave33 pure：take_c_path / take_want_extern / n_lib_roots_get / lib_root_at
 * under PREFER hybrid thin；cold C twins under #ifndef FROM_X。
 */
uint8_t *driver_x_emit_take_c_path(void);
int32_t driver_x_emit_take_want_extern(void);
int32_t driver_x_emit_n_lib_roots_get(void);
uint8_t *driver_x_emit_lib_root_at(int32_t i);
/** Permanent OS residual: setvbuf(stdout) — always seed. */
void driver_x_emit_stdout_set_unbuffered(void);
/**
 * wave39 pure: hybrid thin owns null/len guards; Cap OS residual
 * xlang_driver_fwrite_stdout_n returns written count via xlang_io_write(1, …)
 * (Cap io face; name is historical, body has no libc fwrite since 9.7.1).
 * cold twin under #ifndef FROM_X.
 */
int32_t driver_x_emit_fwrite_stdout(uint8_t *data, int32_t len);
/** Cap OS residual for pure fwrite_stdout (always linked under FROM_X). */
int32_t xlang_driver_fwrite_stdout_n(uint8_t *data, int32_t len);
/** wave23 pure under PREFER hybrid: calloc(1, 9MiB+4); cold seed sizeof twin. */
void *driver_codegen_outbuf_calloc(void);
/** wave24 pure: free / len(LE@CAP) / data base; cold seed twins. */
void driver_codegen_outbuf_free(void *p);
int32_t driver_codegen_outbuf_len(void *p);
uint8_t *driver_codegen_outbuf_data(void *p);
/** wave23 pure: pipeline_sizeof_dep_ctx + calloc; cold seed sizeof twin. */
void *driver_pipeline_dep_ctx_calloc(void);
/** wave23 pure: calloc(n, 8) LP64; cold seed sizeof(void*) twin. */
void *driver_ptr_table_calloc(int32_t n);
/** wave24 pure: free + get/set via G.7 xlang_ptr_slot_*; cold seed twins. */
void driver_ptr_table_free(void *t);
void *driver_ptr_table_get(void *t, int32_t i);
void driver_ptr_table_set(void *t, int32_t i, void *p);
/** wave23 pure: calloc(n, 8) LP64; cold seed sizeof(size_t) twin. */
void *driver_size_table_calloc(int32_t n);
/** wave24 pure: free + get/set LE usize@i*8; cold seed twins. */
void driver_size_table_free(void *t);
size_t driver_size_table_get(void *t, int32_t i);
void driver_size_table_set(void *t, int32_t i, size_t v);
/**
 * wave38 pure: hybrid thin owns null guards; Cap-struct residual
 * xlang_parser_parse_into_buf_rc always-seed; cold twin under #ifndef FROM_X.
 */
int32_t driver_parse_into_buf_rc(void *arena, void *module, uint8_t *data, int32_t len,
                                 int32_t *out_main_idx);
/** Cap-struct-return residual (always seed): parser_parse_into_buf → ok + *out_main_idx. */
int32_t xlang_parser_parse_into_buf_rc(void *arena, void *module, uint8_t *data, int32_t len,
                                      int32_t *out_main_idx);
/** wave23 pure: calloc(1, 32) LP64; cold seed sizeof(DiagContextSnapshot) twin. */
void *driver_diag_snapshot_alloc(void);
/** wave24 pure: free snapshot; cold seed twin. */
void driver_diag_snapshot_free(void *s);
/** wave35 pure: null-guard + diag_push_file; cold seed twin. */
void driver_diag_push_file(void *snap, uint8_t *path, uint8_t *src, size_t len);
/** wave35 pure: null-guard + diag_restore; cold seed twin. */
void driver_diag_restore(void *snap);
/** wave35 pure: G.7 typeck_ndep_store; cold seed twin. */
void driver_typeck_ndep_set(int32_t n);
/** wave35 pure: G.7 typeck_dep_module/arena_set (j in [0,32)); cold seed twin. */
void driver_typeck_dep_ptrs_set(int32_t j, void *mod, void *arena);
uint8_t *driver_path_max_slot(void);
uint8_t *driver_entry_dir_slot(void);
/** wave33 pure: n=0 → fallback ["."] BSS; else lib_roots_raw; cold C twin.
 * Returns *u8 as const char** （.x 禁 **u8）。 */
uint8_t *driver_x_emit_effective_lib_roots(int32_t *n_out);
/** 构造 slice 调 parser_diag_fail_at_token_kind（.x 无 slice 字面量）。 */
int32_t driver_parser_diag_fail_tok_kind(uint8_t *src, size_t len);
/** pctx->use_asm_backend = v（wave19 pure: LP64 offsetof + LE store under PREFER hybrid）. */
void driver_pipeline_dep_ctx_set_use_asm(void *ctx, int32_t v);

/**
 * Cap residual：rt_run_x_emit 工作槽（避免 .x 巨型函数 ~50 局部被 -E 抬 static/丢体）。
 * 业务步骤仍由 .x 编排；槽仅持跨步骤状态指针/计数。get/set 避免 .x 侧 * 解引用槽。
 */
void driver_x_emit_work_reset(void);
uint8_t *driver_x_emit_work_p_get(int32_t i);
void driver_x_emit_work_p_set(int32_t i, uint8_t *v);
int32_t driver_x_emit_work_i_get(int32_t i);
void driver_x_emit_work_i_set(int32_t i, int32_t v);
size_t driver_x_emit_work_z_get(int32_t i);
void driver_x_emit_work_z_set(int32_t i, size_t v);
/** 释放 work 槽内 dep 表/arena/out/pctx/src/kind 等；调用后 reset。 */
void driver_x_emit_work_cleanup(void);
/**
 * Cap residual: -x -E -E-extern refuse (always BLD001).
 * wave33 pure: product NO_C fixed BLD001 diag + return 1 under PREFER hybrid;
 * cold C twin under #ifndef FROM_X. Leftover !XLANG_NO_C_FRONTEND cparser
 * consume site in rt_run_x_emit.from_x.c retired (residual 7); cold seed
 * now also calls this refuse. Mega wrapper of
 * driver_run_x_emit_c_extern_via_cparser retired (this knife;
 * never-defined _impl).
 * PLATFORM: SHARED — mega-wrapper hygiene.
 */
int32_t driver_x_emit_try_extern_via_cparser(uint8_t *input_path);

/** pipeline 入口源码长度（大模块 typeck 跳过判定）。 */
void driver_set_pipeline_entry_source_len(size_t len);
size_t driver_pipeline_entry_source_len(void);
int32_t driver_typeck_skip_large_entry(void);

/** XLANG_ASM_BUILD_SKIP_TYPECK / XLANG_ASM_ENTRY_EMIT_HEAVY / XLANG_ASM_ENTRY_MODULE_ONLY。 */
int32_t driver_asm_build_skip_typeck(void);
int32_t driver_asm_entry_emit_heavy(void);
int32_t driver_asm_entry_module_only_from_env(void);

/** A-11：XLANG_ASM_PARSE_METRIC_ONLY=1 时 entry parse 后输出 num_defined，跳过 pipeline/asm emit（防 typeck.x OOM）。 */
int32_t driver_asm_parse_metric_only_from_env(void);

/** -o exe 时跳过 dep 0 codegen；当前 dep 路径供 codegen 前缀。 */
void driver_skip_codegen_dep_0_set(int32_t v);
int32_t driver_skip_codegen_dep_0_get(void);
void driver_set_current_dep_path_for_codegen(const char *path);
const char *driver_get_current_dep_path_for_codegen(void);

/** OBS-001：XLANG_COMPILE_PHASE_TIMING 阶段计时（pipeline.x 调用）。 */
void driver_compile_phase_timing_begin(int32_t phase);
void driver_compile_phase_timing_end(int32_t phase);
void driver_compile_phase_timing_flush(void);

/**
 * 从 argv 收集 -D / -DFOO 与 -target 推导 OS_*、uname 的 XLANG_OS_/XLANG_ARCH_。
 * 参数：defines 至少 max_defines 个槽；返回注入宏数量。
 */
int driver_argv_collect_defines(int argc, char **argv, const char **defines, int max_defines);

/** pipeline 失败 rc 诊断；rc==-7 时打印 resolve 尝试路径。 */
void driver_pipeline_fail_code(int rc, const uint8_t *path);

/** .x pipeline 烟测 stderr 摘要（parse OK / typeck OK 前缀供 gate grep）。 */
void driver_print_x_smoke_summary(void *module, size_t codegen_len);

/**
 * B-20：读源文件前缀到 content（最多 cap-1 字节）；成功返回读入字节数，失败 -1。
 */
int driver_peek_source_file(const char *path, char *content, size_t cap);

/** 预处理后源码是否含顶层 import（seed asm 对这类入口 X parse 易 0 func）。 */
int driver_source_has_top_level_import(const char *src, size_t src_len);

/** 读 path 并检测顶层 import（compile.x extern）。 */
int driver_source_has_top_level_import_path(const char *path);

/*
 * Cap residual：rt_run_asm_backend R2 平台/FILE/pctx 布局/指针表缺口。
 * 业务控制流在 .x（step 拆分 + work 槽）；本层仅：
 *   - FILE open/write/close + mkstemp 临时 .o
 *   - PipelineDepCtx 字段 set/get（wave19 pure under PREFER: LP64 offsetof; cold C twin）
 *   - host 默认 macho/coff/arch（wave23 pure orch + OS residual #ifdef helpers）
 *   - defines 与 lib_roots/argv 绑定（wave34 pure under PREFER；cold C twin）
 *   - C frontend smoke / typeck 预检（wave34 pure：产品 NO_C 固定 -2/-1；cold twin）
 *   - elf_ctx 分配（wave23 pure）、metric 写盘、asm work 槽
 * wave40 pure under PREFER: fopen_wb / fflush_stdout / write_metric_o；
 * wave41 pure under PREFER: mkstemp_fdopen（template pure + g05 fdopen_wb_opaque）；
 * wave42 pure under PREFER: exec_compiled_body（scan opaque + spawn residual）；
 * wave43 pure under PREFER: sibling_try_spawn（path pure + argv0/access residual）；
 * wave44 pure under PREFER: print_usage_write（color orch + usage lit residual）。
 */
void driver_pipeline_dep_ctx_set_target_arch(void *ctx, int32_t v);
void driver_pipeline_dep_ctx_set_target_cpu_features(void *ctx, int32_t v);
void driver_pipeline_dep_ctx_set_use_macho_o(void *ctx, int32_t v);
void driver_pipeline_dep_ctx_set_use_coff_o(void *ctx, int32_t v);
void driver_pipeline_dep_ctx_set_entry_already_parsed(void *ctx, int32_t v);
void driver_pipeline_dep_ctx_set_asm_entry_module_only(void *ctx, int32_t v);
int32_t driver_pipeline_dep_ctx_get_asm_entry_module_only(void *ctx);
int32_t driver_pipeline_dep_ctx_get_use_macho_o(void *ctx);
int32_t driver_pipeline_dep_ctx_get_use_coff_o(void *ctx);
/** wave23 pure: target 字符串 + emit_elf_o → arch/macho/coff（host #ifdef via OS residual）. */
void driver_asm_pctx_apply_host_defaults(void *ctx, uint8_t *target, int32_t emit_elf_o);
/** Permanent OS residual for pure host_defaults (always linked). PLATFORM: MACOS/WINDOWS. */
int32_t xlang_driver_host_default_target_arch(void);
int32_t xlang_driver_host_prefer_macho(int32_t emit_elf_o);
int32_t xlang_driver_host_prefer_coff(int32_t emit_elf_o);

/**
 * wave40 pure: hybrid thin owns (null guard + g05 fopen_wb_opaque "wb");
 * cold twin under #ifndef FROM_X. Binary mode — not text fopen_write_opaque "w".
 */
uint8_t *driver_asm_fopen_wb(uint8_t *path);
/**
 * wave41 pure: hybrid thin owns (null + WINDOWS enable residual + template pure +
 * mkstemp + g05 fdopen_wb_opaque "wb"); cold twin under #ifndef FROM_X.
 * path_out64 容量 ≥64B；失败 NULL（fail 后可能 clear path[0]）。
 */
uint8_t *driver_asm_mkstemp_fdopen(uint8_t *path_out64);
/** OS residual gate: SHARED → 1（pure mkstemp_fdopen；Windows MinGW enabled）. */
int32_t xlang_driver_asm_mkstemp_fdopen_enabled(void);
void driver_asm_fclose(uint8_t *fp);
/**
 * wave39 pure: hybrid thin owns (null/len guards + g05 stdout_ptr/fwrite_opaque);
 * fp==NULL 时写 stdout；返回 0 成功 1 短写。cold twin under #ifndef FROM_X.
 */
int32_t driver_asm_fwrite(uint8_t *fp, uint8_t *data, int32_t len);
/**
 * wave40 pure: hybrid thin owns via g05 xlang_driver_fflush_stdout;
 * cold twin under #ifndef FROM_X.
 */
void driver_asm_fflush_stdout(void);
/**
 * wave40 pure: hybrid thin owns (fopen_wb + one-byte 0 fwrite + fclose_opaque);
 * 写单字节 0 的 metric .o；0 成功 1 失败。cold twin under #ifndef FROM_X.
 */
int32_t driver_asm_write_metric_o(uint8_t *path);

/** wave23 pure: pipeline_sizeof_elf_ctx + malloc/memset; cold seed twin. */
uint8_t *driver_asm_elf_ctx_calloc(void);
/** wave38 pure: free pairs wave23 calloc; cold seed twin under #ifndef FROM_X. */
void driver_asm_elf_ctx_free(uint8_t *p);
/** wave25 pure: 64-byte BSS mkstemp path slot; cold seed twin. open_out/mkstemp write via pointer. */
uint8_t *driver_asm_tmp_path_slot(void);

/**
 * 收集 -D 到内部表；argv 为 char** 以 *u8 传入（.x 禁 **u8）。
 * 返回 ndefines；driver_asm_defines_as_u8 取表指针。
 * wave34 pure: hybrid thin owns BSS table + pure argv_collect; cold twin under #ifndef FROM_X.
 */
int32_t driver_asm_collect_defines(int32_t argc, uint8_t *argv);
/** wave34 pure: hybrid thin owns; cold twin. */
uint8_t *driver_asm_defines_as_u8(void);
/** wave34 pure: hybrid thin owns; cold twin. */
int32_t driver_asm_ndefines_get(void);

/**
 * 绑定调用方 lib_roots（*u8 实为 const char**）；n<=0 时回退 ["."]。
 * 返回 effective 表指针（*u8）。
 * wave34 pure: hybrid thin owns one_root BSS + G.7; cold twin under #ifndef FROM_X.
 */
uint8_t *driver_asm_bind_lib_roots(uint8_t *lib_roots, int32_t n, int32_t *n_out);
/** wave34 pure: hybrid thin owns (argv_at/G.7); cold twin. */
uint8_t *driver_asm_argv0(uint8_t *argv);

/**
 * 无 -o 且非 check：C frontend smoke（有 C 时）；check 且无 X pipeline：C typeck。
 * 返回 -2 表示继续 .x pipeline；>=0 为应直接返回的 rc。
 * wave34 pure: product NO_C fixed -2 under PREFER; cold twin under #ifndef FROM_X.
 */
int32_t driver_asm_try_c_frontend_early(uint8_t *input_path, uint8_t *src, uint8_t *lib_roots,
                                        int32_t n_lib, uint8_t *out_path);
/**
 * 用户 asm 编译前 C typeck 预检。0 成功；1 失败；-1 跳过（NO_C / skip env / SKIP_TYPECK）。
 * wave34 pure: product NO_C fixed -1 under PREFER; cold twin under #ifndef FROM_X.
 */
int32_t driver_asm_try_c_typeck_precheck(uint8_t *input_path, uint8_t *src, uint8_t *lib_roots,
                                        int32_t n_lib);
/** XLANG_ASM_USE_COMPILER_IMPL_C 是否启用（dep 仅 parse）。
 * wave34 pure: product fixed 0 under PREFER; cold twin uses #ifdef. */
int32_t driver_asm_use_compiler_impl_c(void);

/**
 * Cap residual：rt_run_asm_backend 工作槽（避免巨型函数局部被 -E 抬 static/丢体）。
 * 与 x_emit 槽独立，避免交错污染。
 */
void driver_asm_work_reset(void);
uint8_t *driver_asm_work_p_get(int32_t i);
void driver_asm_work_p_set(int32_t i, uint8_t *v);
int32_t driver_asm_work_i_get(int32_t i);
void driver_asm_work_i_set(int32_t i, int32_t v);
size_t driver_asm_work_z_get(int32_t i);
void driver_asm_work_z_set(int32_t i, size_t v);
/** 释放 work 槽内资源；不 unlink tmp（由 .x 在 ld 前后处理）。 */
void driver_asm_work_cleanup(void);

/*
 * Cap residual：rt_run_compiler_parsed（R2 full）
 *   - DriverCompileParsed 字段 get（wave32 pure: LP64 offsetof + LE/G.7；cold twin）
 *   - C 前端块（wave32 pure: 产品 NO_C 固定 -2 继续；cold twin）
 *   - FILE open/write/close + mkstemp .c + invoke_cc 整表（.x 禁 **u8 / 巨型字面量）
 *   - pctx skip_codegen_dep_0
 *   - parsed work 槽（与 asm/x_emit 独立）
 */
/** wave32 pure: hybrid thin owns; cold twin under #ifndef FROM_X; LP64 @0. */
uint8_t *driver_parsed_input_path(void *p);
/** wave32 pure: hybrid thin owns; cold twin; LP64 @8. */
uint8_t *driver_parsed_out_path(void *p);
/** wave32 pure: returns &lib_roots_arr[0] (embedded); *u8 实为 const char**. LP64 @16. */
uint8_t *driver_parsed_lib_roots(void *p);
/** wave32 pure: hybrid thin owns; cold twin; LP64 @144 LE i32. */
int32_t driver_parsed_n_lib_roots(void *p);
/** wave32 pure: hybrid thin owns; cold twin; LP64 @148 LE i32. */
int32_t driver_parsed_want_asm(void *p);
/** wave32 pure: hybrid thin owns; cold twin; LP64 @152. */
uint8_t *driver_parsed_target(void *p);
/** wave32 pure: 缺省 "2"（BSS lit）；cold twin. LP64 @160. */
uint8_t *driver_parsed_opt_level(void *p);
/** wave32 pure: hybrid thin owns; cold twin; LP64 @168 LE i32. */
int32_t driver_parsed_use_lto(void *p);

/**
 * 预处理后 C 前端（check/smoke/generic C 内联）。
 * 返回 -2 继续 .x pipeline；>=0 为应直接返回的 rc。
 * 产品 XLANG_NO_C_FRONTEND 固定 -2。
 * wave32 pure: hybrid thin owns stub; cold twin under #ifndef FROM_X.
 */
int32_t driver_parsed_try_c_after_pp(uint8_t *input_path, uint8_t *src, size_t src_len,
                                     uint8_t *lib_roots, int32_t n_lib, uint8_t *out_path,
                                     int32_t argc, uint8_t *argv, uint8_t *opt_level,
                                     int32_t use_lto, int32_t ndefines, uint8_t *defines);

void driver_pipeline_dep_ctx_set_skip_codegen_dep_0(void *ctx, int32_t v);

/**
 * 打开输出：out_path==NULL → stdout（emit_stdout=1）；否则 mkstemp+rename .c。
 * 成功返回 FILE* 作 *u8；tmp_c_out64 写 .c 路径；失败 NULL。
 * wave27 pure: hybrid thin owns; cold twin; tmp_prefix residual + g05 fopen_write_opaque.
 * PLATFORM: SHARED orch; WINDOWS|POSIX close-before-rename (BLD001).
 */
uint8_t *driver_parsed_open_out_file(uint8_t *out_path, uint8_t *tmp_c_out64, int32_t *emit_stdout);
/** Permanent OS residual: XLANG_TMP_PREFIX as C string (POSIX /tmp/xlang_ · WINDOWS xlang_). */
const char *xlang_driver_tmp_prefix(void);
/** wave26 pure: hybrid thin owns; cold twin; stdout skip via g05 stdout_ptr. */
void driver_parsed_fclose(uint8_t *fp);
/** wave26 pure: hybrid thin owns; cold twin; 0 success / 1 fail. */
int32_t driver_parsed_fclose_rc(uint8_t *fp);
/** wave25 pure: 256-byte open_out tmp path; seed open_out writes only via this; cold twin. */
uint8_t *driver_parsed_tmp_c_buf(void);
/** wave25 pure: 64-byte parsed tmp slot; pure/cold reset clears [0]. */
uint8_t *driver_parsed_tmp_c_slot(void);
/** wave26 pure: min preamble + first_line + io_net + fs_path + rest; 0 success.
 * cold twin under #ifndef XLANG_L2_RDABI_THIN_FROM_X; fwrite via g05 opaque. */
int32_t driver_parsed_write_out(uint8_t *fp, uint8_t *data, int32_t len);
/**
 * 链 std .o 调 xlang_invoke_cc；argv0 可为 NULL。
 * 失败时 unlink out_path；成功且无 XLANG_KEEP_C 时 unlink tmp_c。
 * argc/argv：从命令行提取用户 .o 文件（如 runtime_atomic_glue.o）注入 cc 链接行；
 *   单一权威由 xlang_invoke_cc_set_user_o_files_from_argv/clear_user_o_files 承担
 *   （G.7：同一表亦供 asm invoke_ld；历史命名仍为 cc）。
 * wave28 pure: hybrid thin owns orch; cold twin under #ifndef FROM_X;
 *   c_paths[1] via G.7 ptr_slot; BLD001/KEEP_C via fixed-arity diag (no va_list).
 * PLATFORM: SHARED — argv 为普通 char**。
 */
int32_t driver_parsed_invoke_cc(uint8_t *tmp_c, uint8_t *out_path, uint8_t *opt_level,
                                int32_t use_lto, uint8_t *argv0, int32_t argc, uint8_t *argv);
/** wave31 pure: hybrid thin owns; cold twin under #ifndef FROM_X; no va_list. */
void driver_parsed_maybe_dump_prep(uint8_t *input_path, uint8_t *src, size_t src_len);
/** wave31 pure: dep_paths 中是否含 "std.io.core"（G.7 ptr_slot + strcmp）。 */
int32_t driver_parsed_deps_has_std_io_core(uint8_t *dep_paths, int32_t n_deps);
/** wave31 pure: dep_paths 中是否含 "std.io.driver"（co-emit 强符号 → WEAK_IO skip）。 */
int32_t driver_parsed_deps_has_std_io_driver(uint8_t *dep_paths, int32_t n_deps);
/** wave31 pure: preamble skip — 无 core → CORE_MACROS|UNDEF_REDEFINE；有 driver → WEAK_IO_BATCH。 */
void driver_parsed_apply_preamble_skip(uint8_t *dep_paths, int32_t n_deps);

void driver_parsed_work_reset(void);
uint8_t *driver_parsed_work_p_get(int32_t i);
void driver_parsed_work_p_set(int32_t i, uint8_t *v);
int32_t driver_parsed_work_i_get(int32_t i);
void driver_parsed_work_i_set(int32_t i, int32_t v);
size_t driver_parsed_work_z_get(int32_t i);
void driver_parsed_work_z_set(int32_t i, size_t v);
/** 释放 work 资源；emit_stdout=0 时 fclose+unlink tmp_c（若仍持有）。 */
void driver_parsed_work_cleanup(void);

/*
 * Cap residual：rt_dispatch_impl（R2 full）
 *   - lib_key → lib_roots 静态槽（wave36 pure：BSS 16×512 + 16×LP64；cold twin）
 *   - 填 DriverCompileParsed 调 driver_run_compiler_parsed（wave36 pure pack；cold twin）
 *   业务分派逻辑在 rt_dispatch_impl.x，不在 rest。
 *   still always-seed OS residual：sibling_try_spawn / fopen 族。
 */
/** wave36 pure: 从 lib_key 填内部 16×512 槽；*n_out=根数；返回 *u8 实为 const char**；cold twin. */
uint8_t *driver_dispatch_lib_roots_from_key(uint8_t *lib_key, int32_t *n_out);
/** wave35 pure: roots 为 lib_roots_from_key 返回值；取第 i 根（越界/空 → NULL）；cold twin. */
uint8_t *driver_dispatch_lib_root_at(uint8_t *roots, int32_t i);
/**
 * 构造 Parsed（want_asm=0）并调 driver_run_compiler_parsed。
 * lib_roots 为 const char**（可与 driver_dispatch_lib_roots_from_key 同址）。
 * opt_level 空/NULL → 默认 "2"。
 * wave36 pure: BSS pack + driver_run_compiler_parsed；cold twin under #ifndef FROM_X.
 */
int32_t driver_dispatch_run_compiler_parsed(uint8_t *input_path, uint8_t *out_path,
                                           uint8_t *lib_roots, int32_t n_lib,
                                           uint8_t *target, uint8_t *opt_level,
                                           int32_t use_lto, int32_t argc, uint8_t *argv);
/** wave35 pure: 缺省 opt 字面量 "2"（hybrid 共用 wave32 BSS lit）；cold twin. */
uint8_t *driver_dispatch_opt_default(void);

/*
 * Cap residual：rt_asm_stub（R2 full）
 *   - 最小 GAS 行表 line_at/count（.x 禁巨型/多字串表依赖）
 *   - CodegenOutBuf append_cstr（9MiB data[] 布局写）
 *   业务循环在 rt_asm_stub.x，不在 rest。
 */
/** GAS 桩行表（main return 42）；越界 → NULL。 */
uint8_t *driver_asm_stub_gas_line_at(int32_t i);
int32_t driver_asm_stub_gas_line_count(void);
/**
 * 向 opaque CodegenOutBuf* 追加 cstr + '\\n' 并更新 len。
 * 成功 0；out/s 空或溢出 → -1。
 */
int32_t driver_asm_stub_out_append_cstr(void *out, uint8_t *s);

/*
 * Cap residual：rt_dispatch_thin（R2 full）sibling
 * wave43 pure under PREFER: null/argc + G.7 driver_argv0_basename_is + path pure BSS 512；
 * cold twin under #ifndef XLANG_L2_RDABI_THIN_FROM_X。
 * Always-seed residual: xlang_driver_sibling_argv0_get + xlang_driver_sibling_access_spawn。
 *   业务薄门闩 / full 入口在 rt_dispatch_thin.x，不在 rest。
 *   返回 ≥0 子进程 exit；-1 未委托（含 basename 已是 xlang-c / 不可执行等）。
 */
int32_t driver_dispatch_sibling_try_spawn(int32_t argc, uint8_t *argv);
/** Permanent Cap residual: *u8 argv → cast + av[0]. */
uint8_t *xlang_driver_sibling_argv0_get(uint8_t *argv_opaque);
/** Permanent OS residual: access X_OK + spawn/fork wait. PLATFORM: WIN vs POSIX. */
int32_t xlang_driver_sibling_access_spawn(uint8_t *path, int32_t argc, uint8_t *argv_opaque);

#endif /* XLANG_RUNTIME_DRIVER_ABI_H */
