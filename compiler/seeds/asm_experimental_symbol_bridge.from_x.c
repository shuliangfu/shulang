/* seeds/asm_experimental_symbol_bridge.from_x.c — G-02f-80 product cold-start TU
 * Promoted from compiler/src/asm/asm_experimental_symbol_bridge.inc (stub/bridge; retired .inc).
 * Compile: cc -c / cc_inc_tu seeds/asm_experimental_symbol_bridge.from_x.c
 */
/**
 * asm_experimental_symbol_bridge.c — 实验 asm-only 链符号桥
 *
 * build_asm 裸符号名（如 entry、parse_into_buf），runtime 期望
 * main_entry、parser_parse_into_buf、asm_asm_codegen_elf_o 等。
 */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct xlang_slice_uint8_t {
  uint8_t *data;
  size_t length;
};

/** runtime 与 main.c 统一入口名。 */
struct parser_ParseIntoResult {
  int32_t ok;
  int32_t main_idx;
};

extern int32_t entry(int32_t argc, uint8_t *argv);
/** runtime.c 完整编译驱动（-o / -backend asm 等）；实验链无 driver_x.o 时作 main_run_compiler_c 兜底。 */
extern int32_t driver_run_compiler_full(int32_t argc, uint8_t *argv);

/** main.o 链入时其强符号 entry 覆盖本 weak 实现；未链 main.o 时转 runtime run_compiler_c（缺 run_compiler_x_path_impl 会 silent fail）。 */
XLANG_WEAK int32_t entry(int32_t argc, uint8_t *argv) {
  extern int32_t run_compiler_c(int32_t, char **);
  return run_compiler_c(argc, (char **)argv);
}

/** driver_x.o 的 main_entry 引用；B-strict 未链 lsp_x.o 时弱桩。 */
XLANG_WEAK int32_t typeck_lsp_main(void) {
  return -1;
}

/** build_asm/main.o 导出 run_compiler_x_path_impl；driver/build.x 经 -E 期望 main_ 前缀。 */
extern int32_t driver_run_compiler_full(int32_t argc, uint8_t *argv);
XLANG_WEAK int32_t run_compiler_x_path_impl(int32_t argc, uint8_t *argv) {
  return driver_run_compiler_full(argc, (uint8_t *)argv);
}
/** driver/build.x、driver/run.x 引用；experimental 链未并 driver_x.o 时由本弱桩转发 driver_run_compiler_full。 */
XLANG_WEAK int32_t main_run_compiler_x_path_impl(int32_t argc, uint8_t *argv) {
  return driver_run_compiler_full(argc, (uint8_t *)argv);
}

extern uint8_t *driver_argv_drop_subcommand(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_fmt(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_check(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_test(int32_t argc, uint8_t *argv);
/** main.x / driver_x.o 提供；experimental 链未并 driver_x 时由弱桩兜底。 */
extern int32_t main_cmd_build(int32_t argc, uint8_t *argv);
extern int32_t driver_cmd_run(int32_t argc, uint8_t *argv);

/** build 子命令弱桩：experimental 链无 driver_x.o 时返回失败（勿误用 build_cmd_build 旧名）。 */
XLANG_WEAK int32_t main_cmd_build(int32_t argc, uint8_t *argv) {
  (void)argc;
  (void)argv;
  return -1;
}

/**
 * B-strict：build_asm/main.o 为 ENTRY_MODULE_ONLY 桩时，在此路由 check/fmt/test/build/run 到 driver_*_x.o。
 * 与 main.x entry() 子命令语义一致（argc-1 + driver_argv_drop_subcommand）。
 * 弱符号：链入 driver_x.o / build_asm/main.o 真 entry 时由其强符号覆盖。
 */
XLANG_WEAK int32_t main_entry(int32_t argc, char **argv) {
  uint8_t *adj;
  if (argc >= 2 && argv[1] && argv[1][0] != '-') {
    adj = driver_argv_drop_subcommand((int32_t)argc, (uint8_t *)argv);
    if (strcmp(argv[1], "fmt") == 0)
      return driver_cmd_fmt((int32_t)argc - 1, adj);
    if (strcmp(argv[1], "check") == 0)
      return driver_cmd_check((int32_t)argc - 1, adj);
    if (strcmp(argv[1], "test") == 0)
      return driver_cmd_test((int32_t)argc - 1, adj);
    if (strcmp(argv[1], "build") == 0)
      return main_cmd_build((int32_t)argc - 1, adj);
    if (strcmp(argv[1], "run") == 0)
      return driver_cmd_run((int32_t)argc - 1, adj);
  }
  return entry(argc, (uint8_t *)argv);
}

/**
 * runtime.c 的 run_compiler_c 转调本符号；须避免 entry→run_compiler_c→本函数→entry 递归。
 * build_asm/main.o 链入时其强符号覆盖本 weak 实现。
 */
XLANG_WEAK int32_t main_run_compiler_c(int32_t argc, uint8_t *argv) {
  return driver_run_compiler_full(argc, argv);
}

/*
 * The 5-arg weak asm_codegen_elf_o that returned -1 was deleted,
 * and with it the weak asm_asm_codegen_elf_o alias that only
 * forwarded into that -1.
 *
 * Why: ELF and Mach-O pick the first weak definition of a name.
 * Darwin product USER_ASM_LINK includes this bridge.o (Linux
 * product does not; experimental/strict_glue still do). Product
 * emit is PREFIX asm_asm_codegen_elf_o from strong
 * user_asm_seed_bridge — there is no unprefixed product provider.
 * Keeping the alias as a weak forward to unprefixed therefore
 * UNDEFs Darwin product ld (`_asm_codegen_elf_o` referenced from
 * this TU). The -1 body was the Cap trap: without seed_bridge,
 * callers of the prefix name got ok=-1 → CG002 code_len=0.
 * Darwin product nm showed T asm_codegen_elf_o = `mov w0,#-1`
 * next to the real strong prefix. Same class as the
 * typeck_x_ast / parser_parse_into_buf / 4-arg asm_codegen_ast
 * weak stubs deleted in this file.
 *
 * Contrast with 4-arg asm_codegen_ast: product authority there
 * IS the unprefixed name (rt_asm_stub 3-arg GAS), so prefix
 * aliases stay as weak forwarders. Here product authority is
 * the prefix name; a second weak prefix def is the first-wins
 * hazard, not a name-bridge.
 *
 * Invariant: every product/strict/experimental link that needs
 * asm_asm_codegen_elf_o must provide a real body
 * (user_asm_seed_bridge). Missing provider → link UNDEF, not a
 * silent -1.
 *
 * Same-class PREFIX -1 leftovers in strict_glue / x_stubs /
 * verify-selfhost were deleted with this invariant (not a second
 * emit path). Darwin Stage2 filter_o_export omit stays as
 * defense-in-depth against a stale .o.
 *
 * PLATFORM: SHARED — first-weak-wins is ELF + Mach-O. Darwin
 * product g05 links this bridge in USER_ASM_LINK; Linux product
 * USER_ASM_LINK does not (experimental/strict_glue still do).
 */

/** parser.o 在 SKIP_TYPECK 下常缺 parse_into_buf；弱符号供 bridge 转发。 */
XLANG_WEAK struct parser_ParseIntoResult parse_into_buf(void *arena, void *module, uint8_t *data,
                                                                       int32_t len) {
  (void)arena;
  (void)module;
  (void)data;
  (void)len;
  struct parser_ParseIntoResult r;
  r.ok = -1;
  r.main_idx = -1;
  return r;
}

XLANG_WEAK struct parser_ParseIntoResult parse_into(void *arena, void *module,
                                                                 struct xlang_slice_uint8_t *source) {
  (void)source;
  return parse_into_buf(arena, module, NULL, 0);
}

XLANG_WEAK void parse_into_init(void *module, void *arena) {
  (void)module;
  (void)arena;
}

XLANG_WEAK void parse_into_set_main_index(void *module, int32_t main_idx) {
  (void)module;
  (void)main_idx;
}

XLANG_WEAK int32_t get_module_num_imports(void *module) {
  (void)module;
  return 0;
}

/** pipeline.x 直调；强符号转发 parser.x（strict 无 parser_x.o 时由下方 weak 桩清零）。 */
void parser_get_module_import_path(void *module, int32_t i, uint8_t *out);

void get_module_import_path(void *module, int32_t i, uint8_t *out) {
  parser_get_module_import_path(module, i, out);
}

XLANG_WEAK void parser_get_module_import_path(void *module, int32_t i, uint8_t *out) {
  (void)module;
  (void)i;
  if (out)
    out[0] = '\0';
}

/** build_asm/preprocess.o 有真实现时覆盖弱符号（与 runtime.c / x_seed_bridge 一致用 const 源指针）。 */
XLANG_WEAK int32_t preprocess_x_buf(const uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf,
                                                  int32_t out_cap) {
  (void)source_buf;
  (void)source_len;
  (void)out_buf;
  (void)out_cap;
  return -1;
}

/** parser 裸名 → runtime 的 parser_ 前缀 API（pipeline_x.o 链入时弱符号被覆盖）。 */
XLANG_WEAK void parser_parse_into_init(void *arena, void *module) {
  parse_into_init(module, arena);
}

/*
 * parser_parse_into_buf 的 weak stub 已删除。
 *
 * 【Why】Linux ELF 链接器选第一个 weak 定义；bridge.o 在 parser_x.o 之前时，
 * 链接器选了 bridge 的 stub（返回 ok=-1），覆盖 parser_x.o 的真正实现，
 * 导致 runtime.c 调用 parser_parse_into_buf 返回失败，触发 P001。
 *
 * 【Invariant】所有 strict link 路径（xlang_asm_bstrict_relink_runtime_only、
 * 第一个 strict link、fallback strict link）都链入 parser_x.o（通过
 * $ST_PARSER_X_TAIL 或 $ST_STRICT_FB_X_TAIL），提供 parser_parse_into_buf
 * 真正实现。不链入 parser_x.o 的路径（asm_seed_use_x_frontend=false 的
 * fallback）会链接失败，暴露配置问题而非掩盖为运行时 P001。
 */

XLANG_WEAK struct parser_ParseIntoResult parser_parse_into(void *arena, void *module, struct xlang_slice_uint8_t *source) {
  return parse_into(arena, module, source);
}

XLANG_WEAK void parser_parse_into_set_main_index(void *module, int32_t main_idx) {
  parse_into_set_main_index(module, main_idx);
}

XLANG_WEAK int32_t parser_get_module_num_imports(void *module) {
  return get_module_num_imports(module);
}

/** asm.x import peephole.peephole_run → peephole_peephole_run；build_asm/peephole.o 提供强符号。 */
XLANG_WEAK int32_t peephole_peephole_run(void *out) {
  (void)out;
  return 0;
}

/*
 * The 4-arg weak asm_codegen_ast that returned -1 was deleted.
 *
 * Why: ELF and Mach-O pick the first weak definition of a name. This
 * bridge.o often precedes rt_asm_stub's 3-arg GAS writer
 * (runtime_driver_no_c.o / XLANG_WEAK asm_codegen_ast) and any backend.o
 * 4-arg body. The -1 stub then covered the real symbol: callers of the
 * unprefixed name got ok=-1 instead of GAS/backend. Same class as the
 * typeck_x_ast / parser_parse_into_buf weak stubs deleted below in this
 * file. Darwin product nm showed weak asm_codegen_ast = `mov w0,#-1`
 * while the strong 3-arg GAS TU was dead-stripped as unused.
 *
 * Invariant: every product/strict/experimental link that needs
 * asm_codegen_ast must provide a real body (rt_asm_stub 3-arg GAS and/or
 * backend.x 4-arg). Missing provider → link UNDEF, not a silent -1.
 * Prefix aliases stay as weak forwarders (backend_asm_codegen_ast /
 * asm_asm_codegen_ast), matching typeck_typeck_x_ast.
 *
 * PLATFORM: SHARED — first-weak-wins is ELF + Mach-O. Darwin product g05
 * links this bridge in USER_ASM_LINK; Linux product USER_ASM_LINK does
 * not (experimental/strict_glue still do).
 */
extern int32_t asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx);

/** asm.o expects backend_asm_codegen_ast; backend.o strong wins when present. */
XLANG_WEAK int32_t backend_asm_codegen_ast(void *module, void *arena, void *out, void *ctx) {
  return asm_codegen_ast(module, arena, out, ctx);
}

/** pipeline/orchestration expects asm_asm_codegen_ast; strong pipeline_x / user_asm_seed_bridge wins.
 * Same-class PREFIX -1 leftovers in x_stubs / verify-selfhost were
 * deleted (not a second ast path). This WEAK forwarder stays: product
 * unprefixed authority is rt_asm_stub, matching typeck_typeck_x_ast.
 * PLATFORM: SHARED — first-weak-wins is ELF + Mach-O. */
XLANG_WEAK int32_t asm_asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx) {
  return asm_codegen_ast(module, arena, out_buf, ctx);
}

/*
 * typeck_x_ast / typeck_x_ast_library 的 weak stub 已删除。
 *
 * 【Why】Linux ELF 链接器选第一个 weak 定义；bridge.o 在 typeck_x.o 之前时，
 * 链接器选了 bridge 的 stub（返回 -1），覆盖 typeck_x.o 的真正实现。
 * typeck_x_link_alias.o 提供 typeck_typeck_x_ast 强符号转发 typeck_x_ast，
 * 但 typeck_x_ast 解析到 bridge stub → typeck 失败 → XP001。
 *
 * 【Invariant】所有 strict link 路径都链入 typeck_x.o（通过 $ST_TYPECK_X_LINK
 * 加入 $ST_SEED_PARSER_TCK），提供 typeck_x_ast / typeck_x_ast_library 真正实现。
 * 不链入 typeck_x.o 的路径会链接失败，暴露配置问题而非掩盖为运行时 XP001。
 */
extern int32_t typeck_x_ast(void *module, void *arena, void *ctx);
extern int32_t typeck_x_ast_library(void *module, void *arena, void *ctx);

XLANG_WEAK int32_t typeck_typeck_x_ast(void *module, void *arena, void *ctx) {
  return typeck_x_ast(module, arena, ctx);
}

XLANG_WEAK int32_t typeck_typeck_x_ast_library(void *module, void *arena, void *ctx) {
  return typeck_x_ast_library(module, arena, ctx);
}

/** runtime 诊断路径；C parser 未导出时弱符号兜底。 */
XLANG_WEAK int32_t parser_diag_token_after_collect_imports(struct xlang_slice_uint8_t *source, void *module) {
  (void)source;
  (void)module;
  return -1;
}

/** strict 链：build_asm/typeck.o 导出 typeck_struct_layout_metrics；未链 typeck.o 时 weak 桩返回 -1。 */
struct ast_Module;
struct ast_ASTArena;

XLANG_WEAK int32_t typeck_struct_layout_metrics(struct ast_Module *module, struct ast_ASTArena *arena,
                                                           int32_t li, int32_t depth, int32_t check_pad,
                                                           int32_t *out_sz, int32_t *out_al) {
  (void)module;
  (void)arena;
  (void)li;
  (void)depth;
  (void)check_pad;
  (void)out_sz;
  (void)out_al;
  return -1;
}

XLANG_WEAK int32_t typeck_typeck_struct_layout_metrics(struct ast_Module *module, struct ast_ASTArena *arena,
                                                                  int32_t li, int32_t depth, int32_t check_pad,
                                                                  int32_t *out_sz, int32_t *out_al) {
  return typeck_struct_layout_metrics(module, arena, li, depth, check_pad, out_sz, out_al);
}

/** parser_from_gen.o 引用 std.io 读 ptr；strict 链无 driver_x 时弱符号兜底。 */
XLANG_WEAK int32_t std_io_driver_driver_read_ptr(void *out_slice, void *fd) {
  (void)out_slice;
  (void)fd;
  return -1;
}

XLANG_WEAK int32_t std_io_driver_driver_read_ptr_len(void *fd) {
  (void)fd;
  return -1;
}

/* codegen_x_ast：唯一权威在 codegen.o。禁止 weak return(-1) 桩（双权威盖掉真实现）。
 * C 后端路径必须链入真 codegen；asm 后端走 asm_codegen_ast，不依赖本符号桩。 */

/** strict 链：load_and_sync 末尾 merge dep struct layout；typeck.o 未链入时 no-op。 */
XLANG_WEAK void typeck_merge_dep_struct_layouts_into_entry(void *module, void *arena, void *ctx) {
  (void)module;
  (void)arena;
  (void)ctx;
}

/** pipeline.x import 前缀名；typeck_x.o 链入时强符号覆盖。 */
XLANG_WEAK void typeck_typeck_merge_dep_struct_layouts_into_entry(void *module, void *arena, void *ctx) {
  typeck_merge_dep_struct_layouts_into_entry(module, arena, ctx);
}

/** DOD-S3：WPO SoA layout 统一；typeck_x.o 未链入时 no-op。 */
XLANG_WEAK void typeck_wpo_unify_soa_layouts(void *entry, void *ctx) {
  (void)entry;
  (void)ctx;
}

XLANG_WEAK void typeck_typeck_wpo_unify_soa_layouts(void *entry, void *ctx) {
  typeck_wpo_unify_soa_layouts(entry, ctx);
}

/**
 * strict 链：parse_into_with_init_buf 经 import ast 引用 ast_ast_arena_init；
 * build_asm/ast.o 未链入、ast_seed 仅 C 种子时，由本 weak 桥接转发 ast_arena_init；
 * pipeline_x.o / build_asm/ast.o 链入时强符号覆盖。
 */
extern void ast_arena_init(void *arena);

XLANG_WEAK void ast_arena_init(void *arena) {
  (void)arena;
}

XLANG_WEAK void ast_ast_arena_init(void *arena) {
  ast_arena_init(arena);
}

/**
 * Darwin 冷链：user_asm_seed_bridge 经 weak_import 调用 platform_macho_write_macho_o_to_buf。
 * 静态链时 weak_import 无定义对象 → ld 硬失败（Linux 未定义 weak 可置 0）。
 * 【Why 单独立桩于本 TU】不可写在 user_asm_seed_bridge 同文件（同 TU 会静态绑本地 stub，
 * 遮蔽日后真 Mach-O writer）。本 weak 在独立 .o；真 macho 强符号链入时覆盖。
 * build_asm/macho.o 当前常为 CI text stub，不含本符号，故冷/experimental 须本桩。
 */
#if defined(__APPLE__)
XLANG_WEAK int32_t platform_macho_write_macho_o_to_buf(void *elf_ctx, void *out_buf) {
  (void)elf_ctx;
  (void)out_buf;
  return -1;
}
#endif
