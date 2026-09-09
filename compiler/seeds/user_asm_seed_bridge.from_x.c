/* seeds/user_asm_seed_bridge.from_x.c — G-02f-15 product TU
 * G-02f-120 true .x pure helpers.
 * G-02f-97 pure helper gates; G-02f-98 reject/empty/macho/coff writer gates.
 * Product object from this seed; logic still C until full .x port.
 */
/**
 * user_asm_seed_bridge.c — bootstrap-driver-seed 用户程序 asm 后端桥
 *
 * pipeline_x.o（-E-extern 瘦编排）经 extern 调用 asm_asm_codegen_ast / asm_asm_codegen_elf_o；
 * 本文件提供强符号实现，并链入 build_asm/seed_host/asm_backend_partial.o（xlang-c -E asm.x 抽出）。
 * 无 C codegen 回退、无 cc -c 汇编 GAS 兜底：asm 失败即返回错误。
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "diag.h"
#include "runtime_diag_codes.h"

/**
 * CodegenOutBuf layout — must match driver_codegen_outbuf_abi /
 * codegen_outbuf_abi.x (CAP = 9 * 1024 * 1024 = 9437184).
 * Historical 8MiB (8388608) here made COFF writer store length at the wrong
 * offset; driver_codegen_outbuf_len read 0 → CG002 after coff_write>0.
 * PLATFORM: SHARED — LP64 product outbuf ABI.
 */
struct codegen_CodegenOutBuf {
  uint8_t data[9437184];
  int32_t length;
};
/* G-02f-442 / wave236：thin+rest PREFER_X_O
 *   thin .x provides #[no_mangle] pure:
 *     - seed_asm_debug_enabled / seed_asm_emit_trace_enabled (wave236 pure orch →
 *       link_abi_getenv; no *_impl residual for these two)
 *     - 4 thin wrappers call *_impl in rest + seed_elf_ctx_code_len real .x
 *   rest seed C (compiled with -DXLANG_USER_ASM_SEED_BRIDGE_FROM_X):
 *     - 4 functions renamed to *_impl via macros (real C implementations stay).
 *     - debug/emit_trace cold twins only under #ifndef FROM_X (pure owns hybrid).
 *     - seed_elf_ctx_code_len guarded out (real .x in thin).
 *   Forward decls always visible: rest mode resolves from pure thin; cold defines
 *   bodies below. Missing extern under FROM_X → ISO C99 implicit-decl hard fail
 *   on rest -c (hybrid residual 2026-08-11; pure_asm thin already OK).
 * PLATFORM: SHARED — hybrid thin+rest face must match cold monofile.
 */
extern int32_t seed_elf_ctx_code_len(const void *elf_ctx);
/* wave236 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — cold seed twins use same face as product hybrid pure .x. */
extern char *link_abi_getenv(const char *name);
/* Always-visible face decls (mirror seed_elf_ctx_code_len). Under FROM_X the
 * bodies live in pure thin .x; rest only calls. Cold monofile defines below. */
extern int seed_asm_debug_enabled(void);
extern int seed_asm_emit_trace_enabled(void);
#ifdef XLANG_USER_ASM_SEED_BRIDGE_FROM_X
/* wave236: debug/emit_trace pure orch in .x (no rest *_impl rename). */
#define seed_elf_ctx_set_macho_leading_underscore  seed_elf_ctx_set_macho_leading_underscore_impl
#define seed_asm_reject_empty_elf_text       seed_asm_reject_empty_elf_text_impl
#define seed_platform_macho_write_macho_o_to_buf  seed_platform_macho_write_macho_o_to_buf_impl
#define seed_platform_coff_write_coff_o_to_buf   seed_platform_coff_write_coff_o_to_buf_impl
#endif
/* G-02f-116 / wave236：逻辑源 .x（真迁）；cold seed 保留同语义 C 供无 PREFER 冷路径。
 * wave236 G.7: XLANG_ASM_DEBUG / XLANG_ASM_EMIT_TRACE via link_abi_getenv (not raw getenv). */
#ifndef XLANG_USER_ASM_SEED_BRIDGE_FROM_X
int seed_asm_debug_enabled(void) {
  return link_abi_getenv("XLANG_ASM_DEBUG") != NULL;
}
int seed_asm_emit_trace_enabled(void) {
  return link_abi_getenv("XLANG_ASM_EMIT_TRACE") != NULL;
}
#endif /* XLANG_USER_ASM_SEED_BRIDGE_FROM_X */



struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;
struct platform_elf_ElfLabelEntry {
  uint8_t name[128];
  int32_t name_len;
  int32_t offset;
};
struct platform_elf_ElfPatchEntry {
  int32_t rel32_offset;
  uint8_t name[128];
  int32_t name_len;
  int32_t patch_imm_bits;
};
struct platform_elf_ElfRelocEntry {
  int32_t offset;
  int32_t name_len;
};
struct platform_elf_ElfRelocSymName64 {
  uint8_t bytes[128];
};
struct platform_elf_ElfSymEntry {
  uint8_t name[128];
  int32_t name_len;
  int32_t offset;
  int32_t sym_shndx;
};
struct platform_elf_ElfCodegenCtx {
  int32_t code_len;
  struct platform_elf_ElfLabelEntry labels[16384];
  int32_t num_labels;
  struct platform_elf_ElfPatchEntry patches[16384];
  int32_t num_patches;
  struct platform_elf_ElfRelocEntry relocs[16384];
  struct platform_elf_ElfRelocSymName64 reloc_sym_names[16384];
  int32_t num_relocs;
  struct platform_elf_ElfSymEntry syms[16384];
  int32_t num_syms;
  int32_t sym_name_len;
  int32_t e_machine;
  int32_t reloc_type_r_pc32;
  int32_t current_frame_size;
  int32_t macho_leading_underscore;
  int32_t code_hot_len;
  int32_t emit_hot;
  uint8_t code_data[8716288];
  uint8_t code_hot_data[1048576];
  uint8_t sym_name_data[131072];
};

/** runtime_pipeline_abi / pipeline orch（勿在此 TU 自建截断 PipelineDepCtx，含 4MiB 内嵌缓冲；
 * ast_pool.c / pipeline_x mega left wave309） */
extern int32_t pipeline_dep_ctx_use_macho_o(struct ast_PipelineDepCtx *ctx);
extern int32_t pipeline_dep_ctx_use_coff_o(struct ast_PipelineDepCtx *ctx);
extern int32_t pipeline_dep_ctx_asm_entry_module_only(struct ast_PipelineDepCtx *ctx);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx *ctx);
extern struct ast_Module *pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx *ctx, int32_t idx);
extern struct ast_ASTArena *pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx *ctx, int32_t idx);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx *ctx, int32_t idx, uint8_t *dst);
extern int32_t pipeline_module_num_funcs(struct ast_Module *m);
extern void pipeline_elf_label_mod_scope_reset(void);
extern void pipeline_elf_ctx_reloc_sidecar_reset(uint8_t *ctx_bytes);
extern int32_t pipeline_elf_ctx_resolve_patches(uint8_t *ctx_bytes);
extern void driver_set_current_dep_path_for_codegen(const char *path);
extern int32_t driver_skip_codegen_dep_0_get(void);
/** freestanding 标志：nostdlib 链无预编译 std .o，dep 须全部 co-emit（跳过 skip 检查）。 */
extern int32_t driver_freestanding_get(void);
/** std.io 族由 io.o + 本文件桩提供；seed asm 跳过整族 dep 的机器码生成。 */
extern int32_t pipeline_codegen_dep_skip_asm_user_std_io(uint8_t *path);
extern int32_t pipeline_codegen_dep_skip_asm_user_std_fs(uint8_t *path);
extern int32_t pipeline_codegen_dep_skip_asm_user_std_process(uint8_t *path);
extern int32_t pipeline_codegen_dep_skip_asm_user_std_fmt(uint8_t *path);
extern int32_t pipeline_codegen_dep_skip_asm_user_std_misc(uint8_t *path);
extern int32_t pipeline_codegen_dep_skip_asm_user_core_lib(uint8_t *path);
extern int32_t pipeline_asm_user_dep_is_in_tree_core(uint8_t *path);
/* Hosted std with a formal .o: skip co-emit (same table as C-path codegen). */
extern int pipeline_codegen_std_dep_link_only(uint8_t *path);
extern int32_t pipeline_asm_user_std_net_dep_path(uint8_t *path);
extern int32_t pipeline_asm_user_deps_need_coemit(char **dep_paths, int32_t n);
extern void pipeline_asm_seed_std_net_struct_layouts(struct ast_Module *m);
extern int32_t pipeline_asm_redirect_std_c_wrapper_sym(uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                         int32_t sym_cap);
extern int32_t pipeline_expr_call_arg_ref(void *arena, int32_t expr_ref, int32_t idx);

struct ast_Expr;

extern struct ast_Expr *pipeline_arena_expr_ptr(struct ast_ASTArena *a, int32_t expr_ref);

/** EXPR_FLOAT_LIT 的 float_val；供 asm 后端 emit 时重算位模式（strict_core 旧 glue 无此路径）。 */
double pipeline_expr_float_val_at(struct ast_ASTArena *a, int32_t expr_ref) {
  struct ast_Expr *p;
  if (!a || expr_ref <= 0)
    return 0.0;
  p = pipeline_arena_expr_ptr(a, expr_ref);
  if (!p)
    return 0.0;
  /** 与 ast_Expr 布局一致：kind..int_val(16) + pad(4) → float_val @ +24。 */
  return *(double *)((char *)p + 24);
}

/** ast.x extern 前缀转发。 */
double ast_pipeline_expr_float_val_at(struct ast_ASTArena *a, int32_t expr_ref) {
  return pipeline_expr_float_val_at(a, expr_ref);
}

/** build_asm/seed_host/asm_backend_partial.o（asm.x 全量 -E 抽出） */
extern int32_t backend_asm_emit_one_call_arg_elf_arm64_push(void *arena, void *elf_ctx, int32_t expr_ref, int32_t arg_idx, void *ctx, int32_t ta);

/**
 * ARM64 ELF call 实参 push 阶段：宿主 C for 循环逐参调用 backend，避免 .x 递归/展开叠加深 emit 栈帧 SIGSEGV。
 */
int32_t pipeline_seed_asm_emit_call_args_elf_arm64_push_loop(void *arena, void *elf_ctx, int32_t expr_ref, int32_t reg_n, void *ctx, int32_t ta) {
  int32_t i;
  for (i = 0; i < reg_n; i++) {
    if (seed_asm_debug_enabled()) {
      int32_t arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      diag_reportf(NULL, 0, 0, "note", NULL,
                   "asm debug: arm64_push_loop i=%d reg_n=%d call_ref=%d arg_ref=%d",
                   (int)i, (int)reg_n, (int)expr_ref, (int)arg_ref);
    }
    if (backend_asm_emit_one_call_arg_elf_arm64_push(arena, elf_ctx, expr_ref, i, ctx, ta) != 0)
      return -1;
  }
  return 0;
}

/** ast.x -E 前缀转发（backend partial.o 经 ast_pipeline_* 调用）。 */
int32_t ast_pipeline_seed_asm_emit_call_args_elf_arm64_push_loop(void *arena, void *elf_ctx, int32_t expr_ref, int32_t reg_n, void *ctx, int32_t ta) {
  return pipeline_seed_asm_emit_call_args_elf_arm64_push_loop(arena, elf_ctx, expr_ref, reg_n, ctx, ta);
}

/** build_asm/seed_host/asm_backend_partial.o（asm.x 全量 -E 抽出） */
extern int32_t backend_asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx);
extern int32_t backend_asm_codegen_ast_to_elf(void *module, void *arena, void *elf_ctx, void *ctx);
extern int32_t peephole_run(void *out_buf);
extern int32_t peephole_elf_run(void *elf_ctx);
/**
 * Darwin -o: call/reloc symbols need leading `_` (same as asm_codegen_elf_o).
 * wave580 Cap residual: NEVER hardcode offsetof (pre-Cap 598052 is stale after
 * name[64]→[128] tables; real offsetof is ~9e6). G.7: write the field via the
 * local ElfCodegenCtx mirror (layout must match elf.x / ast_pool PipelineElfCtxAccess).
 * PLATFORM: MACOS|DARWIN product pure-asm; no-op effect on LINUX when flag left 0.
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void seed_elf_ctx_set_macho_leading_underscore(void *elf_ctx, int32_t on) {
  struct platform_elf_ElfCodegenCtx *ctx = (struct platform_elf_ElfCodegenCtx *)elf_ctx;
  if (!ctx)
    return;
  ctx->macho_leading_underscore = on ? 1 : 0;
}



/** asm 失败时打印 backend.x 记录的当前函数名。 */
extern void driver_diagnostic_asm_print_current_func(void);
extern int32_t pipeline_asm_patch_module_parent_links(struct ast_Module *m, struct ast_ASTArena *a);
extern void pipeline_asm_wpo_reach_compute_for_elf(struct ast_Module *entry, struct ast_ASTArena *entry_arena,
                                                     struct ast_PipelineDepCtx *ctx);
extern void pipeline_asm_wpo_reach_clear(void);
extern int32_t pipeline_elf_write_o_standard_to_buf_c(uint8_t *ctx_bytes, struct codegen_CodegenOutBuf *out);

void platform_elf_elf_ctx_reset(void *elf_ctx) {
  struct platform_elf_ElfCodegenCtx *ctx = (struct platform_elf_ElfCodegenCtx *)elf_ctx;
  if (!ctx)
    return;
  ctx->code_len = 0;
  ctx->code_hot_len = 0;
  ctx->emit_hot = 0;
  ctx->num_labels = 0;
  ctx->num_patches = 0;
  ctx->num_relocs = 0;
  ctx->num_syms = 0;
  ctx->sym_name_len = 0;
  ctx->macho_leading_underscore = 0;
  pipeline_elf_label_mod_scope_reset();
  pipeline_elf_ctx_reloc_sidecar_reset((uint8_t *)ctx);
}

int32_t platform_elf_elf_resolve_patches(void *elf_ctx) {
  return pipeline_elf_ctx_resolve_patches((uint8_t *)elf_ctx);
}

/** 读 ElfCodegenCtx.code_len（前缀字段；与 platform/elf.x / PipelineElfCtxAccess 一致）。 */
/* G-02f-120：逻辑源 .x（真迁）；G-02f-442 thin+rest：真 .x 实现，rest 下 guard 掉 */
#ifndef XLANG_USER_ASM_SEED_BRIDGE_FROM_X
int32_t seed_elf_ctx_code_len(const void *elf_ctx) {
  if (!elf_ctx)
    return 0;
  return *(const int32_t *)elf_ctx;
}
#endif




extern int32_t pipeline_elf_ctx_total_code_len(uint8_t *ctx_bytes);

/**
 * 用户 .o 须含非空 __text；code_len==0 时拒绝写出（避免 576B 空 .o + U main 误导 ld）。
 * G-02f-98：export gate.
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int32_t seed_asm_reject_empty_elf_text(void *module, void *elf_ctx) {
  int32_t nf;
  int32_t clen;
  int32_t total_code_len;
  if (!module || !elf_ctx)
    return 0;
  nf = pipeline_module_num_funcs((struct ast_Module *)module);
  if (nf <= 0)
    return 0;
  clen = seed_elf_ctx_code_len(elf_ctx);
  if (clen > 0)
    return 0;
  total_code_len = pipeline_elf_ctx_total_code_len((uint8_t *)elf_ctx);
  if (total_code_len > 0)
    return 0;
  return XLANG_ASM_CODEGEN_ELF_EMPTY_TEXT_RC;
}



/*
 * Seed bridge 仅消费 seed_host/asm_backend_partial.o 提供的真实 writer。
 * 这里不能再定义同名 fallback，否则同一 TU 内调用会静态绑定到本地 stub，
 * 直接把真实的 Mach-O/COFF writer 全部遮蔽掉。
 */
#if defined(__APPLE__)
extern int32_t platform_macho_write_macho_o_to_buf(void *elf_ctx, void *out_buf) __attribute__((weak_import));
#endif
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

int32_t seed_platform_macho_write_macho_o_to_buf(void *elf_ctx, void *out_buf) {
#if defined(__APPLE__)
  if (!platform_macho_write_macho_o_to_buf)
    return -1;
  return platform_macho_write_macho_o_to_buf(elf_ctx, out_buf);
#else
  (void)elf_ctx;
  (void)out_buf;
  return -1;
#endif
}
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */

/* Reloc sidecar accessors (same faces coff.x uses via pipeline_elf_ctx_*). */
extern void pipeline_elf_ctx_reloc_sym_name_copy64(uint8_t *ctx_bytes, int32_t idx, uint8_t *dst);
extern int32_t pipeline_elf_ctx_reloc_name_len(uint8_t *ctx_bytes, int32_t idx);
extern int32_t pipeline_elf_ctx_reloc_offset_at(uint8_t *ctx_bytes, int32_t idx);

/**
 * Append n bytes into CodegenOutBuf (cap 9MiB product ABI).
 * PLATFORM: SHARED — COFF writer helper.
 */
static int32_t seed_coff_append(struct codegen_CodegenOutBuf *out, const uint8_t *ptr, int32_t n) {
  int32_t i;
  if (!out || (!ptr && n > 0) || n < 0)
    return -1;
  for (i = 0; i < n && out->length < 9437184; i++) {
    out->data[out->length] = ptr[i];
    out->length = out->length + 1;
  }
  return (i < n) ? -1 : 0;
}

/**
 * Sym names live in ElfCodegenCtx.sym_name_data (elf_add_sym /
 * pipeline_elf_ctx_add_sym); ElfSymEntry.name[] is unused. Twin of
 * elf.x::elf_sym_name_ptr. PLATFORM: SHARED.
 */
static uint8_t *seed_elf_sym_name_ptr(struct platform_elf_ElfCodegenCtx *ctx, int32_t sym_idx) {
  int32_t off = 0;
  int32_t i;
  if (!ctx || sym_idx < 0)
    return NULL;
  for (i = 0; i < sym_idx && i < ctx->num_syms; i++)
    off = off + ctx->syms[i].name_len;
  if (off < 0 || off >= 131072)
    return NULL;
  return &ctx->sym_name_data[off];
}

/**
 * Product Windows COFF .obj writer (cross-host).
 * Twin of compiler/src/asm/platform/coff.x::write_coff_o_to_buf.
 * Historical false root: this face was `#if _WIN32` only and returned -1 on
 * Darwin/Linux, so `-target x86_64-pc-windows-msvc -o out.obj` always CG002
 * while use_coff_o was already set — COMP-011 observational SKIP soft-green.
 * PLATFORM: SHARED — cross-emit from Darwin/Linux/Windows hosts; e_machine must
 * be EM_X86_64 (62). build_asm/coff.o remains a ci_text stub; this seed is the
 * product authority until coff.x pure-asm non-stub lands.
 */
int32_t seed_platform_coff_write_coff_o_to_buf(void *elf_ctx, void *out_buf) {
  struct platform_elf_ElfCodegenCtx *ctx;
  struct codegen_CodegenOutBuf *out;
  int32_t code_len;
  int32_t align4;
  int32_t num_relocs;
  int32_t num_syms;
  int32_t reloc_size;
  int32_t num_coff_syms;
  int32_t symtab_size;
  int32_t strtab_used;
  int32_t ptr_raw;
  int32_t ptr_reloc;
  int32_t ptr_sym;
  int32_t s;
  int32_t r;
  uint8_t fh[20];
  uint8_t sh[40];
  uint8_t zero[1];
  uint8_t *ctx_bytes;

  if (!elf_ctx || !out_buf)
    return -1;
  ctx = (struct platform_elf_ElfCodegenCtx *)elf_ctx;
  out = (struct codegen_CodegenOutBuf *)out_buf;
  ctx_bytes = (uint8_t *)elf_ctx;

  /* coff.x: only AMD64 COFF (IMAGE_FILE_MACHINE_AMD64 = 0x8664). */
  if (ctx->e_machine != 62)
    return -1;

  code_len = ctx->code_len;
  if (code_len < 0)
    return -1;
  align4 = (code_len + 3) & (-4);
  num_relocs = ctx->num_relocs;
  num_syms = ctx->num_syms;
  if (num_relocs < 0 || num_syms < 0)
    return -1;
  reloc_size = num_relocs * 10;
  num_coff_syms = 2 + num_syms;
  symtab_size = num_coff_syms * 18;
  strtab_used = 4;
  for (s = 0; s < num_syms; s++)
    strtab_used = strtab_used + ctx->syms[s].name_len + 1;
  ptr_raw = 60;
  ptr_reloc = ptr_raw + align4;
  ptr_sym = ptr_reloc + reloc_size;

  out->length = 0;
  memset(fh, 0, sizeof(fh));
  /* Machine 0x8664 little-endian: 0x64, 0x86 */
  fh[0] = 100;
  fh[1] = 134;
  fh[2] = 1; /* NumberOfSections = 1 */
  fh[3] = 0;
  fh[8] = (uint8_t)(ptr_sym);
  fh[9] = (uint8_t)(ptr_sym >> 8);
  fh[10] = (uint8_t)(ptr_sym >> 16);
  fh[11] = (uint8_t)(ptr_sym >> 24);
  fh[12] = (uint8_t)(num_coff_syms);
  fh[13] = (uint8_t)(num_coff_syms >> 8);
  fh[14] = (uint8_t)(num_coff_syms >> 16);
  fh[15] = (uint8_t)(num_coff_syms >> 24);
  if (seed_coff_append(out, fh, 20) != 0)
    return -1;

  memset(sh, 0, sizeof(sh));
  /* Name ".text" */
  sh[0] = 46;
  sh[1] = 116;
  sh[2] = 101;
  sh[3] = 120;
  sh[4] = 116;
  sh[16] = (uint8_t)(align4);
  sh[17] = (uint8_t)(align4 >> 8);
  sh[18] = (uint8_t)(align4 >> 16);
  sh[19] = (uint8_t)(align4 >> 24);
  sh[20] = (uint8_t)(ptr_raw);
  sh[21] = (uint8_t)(ptr_raw >> 8);
  sh[22] = (uint8_t)(ptr_raw >> 16);
  sh[23] = (uint8_t)(ptr_raw >> 24);
  sh[24] = (uint8_t)(ptr_reloc);
  sh[25] = (uint8_t)(ptr_reloc >> 8);
  sh[26] = (uint8_t)(ptr_reloc >> 16);
  sh[27] = (uint8_t)(ptr_reloc >> 24);
  sh[32] = (uint8_t)(num_relocs);
  sh[33] = (uint8_t)(num_relocs >> 8);
  sh[36] = 32;  /* Characteristics low */
  sh[38] = 80;
  sh[39] = 96;
  if (seed_coff_append(out, sh, 40) != 0)
    return -1;

  if (code_len > 0 && seed_coff_append(out, ctx->code_data, code_len) != 0)
    return -1;
  zero[0] = 0;
  for (s = 0; s < align4 - code_len; s++) {
    if (seed_coff_append(out, zero, 1) != 0)
      return -1;
  }

  for (r = 0; r < num_relocs; r++) {
    uint8_t rel[10];
    int32_t sym_idx = 0;
    int32_t m;
    uint8_t r_sym_buf[128];
    int32_t rlen;
    int32_t roff;
    memset(r_sym_buf, 0, sizeof(r_sym_buf));
    pipeline_elf_ctx_reloc_sym_name_copy64(ctx_bytes, r, r_sym_buf);
    rlen = pipeline_elf_ctx_reloc_name_len(ctx_bytes, r);
    for (m = 0; m < num_syms; m++) {
      uint8_t *sym_nm = seed_elf_sym_name_ptr(ctx, m);
      if (sym_nm != NULL &&
          rlen == ctx->syms[m].name_len &&
          rlen > 0 &&
          memcmp(r_sym_buf, sym_nm, (size_t)rlen) == 0) {
        sym_idx = 2 + m;
        break;
      }
    }
    roff = pipeline_elf_ctx_reloc_offset_at(ctx_bytes, r);
    memset(rel, 0, sizeof(rel));
    rel[0] = (uint8_t)(roff);
    rel[1] = (uint8_t)(roff >> 8);
    rel[2] = (uint8_t)(roff >> 16);
    rel[3] = (uint8_t)(roff >> 24);
    rel[4] = (uint8_t)(sym_idx);
    rel[5] = (uint8_t)(sym_idx >> 8);
    rel[6] = (uint8_t)(sym_idx >> 16);
    rel[7] = (uint8_t)(sym_idx >> 24);
    rel[8] = 4; /* IMAGE_REL_AMD64_REL32 */
    if (seed_coff_append(out, rel, 10) != 0)
      return -1;
  }

  {
    uint8_t sym_sec[18];
    uint8_t aux[18];
    int32_t str_off;
    uint8_t str_size[4];
    /* IMAGE_SYMBOL (18B): Name[8] | Value[4] | SectionNumber[2] | Type[2] |
     * StorageClass[1] | NumberOfAuxSymbols[1]. Prior layout put SectionNumber at
     * byte 16 and left SectionNumber=0 → lld-link "special section 0". */
    memset(sym_sec, 0, sizeof(sym_sec));
    /* ShortName ".text" */
    sym_sec[0] = 46;
    sym_sec[1] = 116;
    sym_sec[2] = 101;
    sym_sec[3] = 120;
    sym_sec[4] = 116;
    sym_sec[12] = 1; /* SectionNumber = 1 */
    sym_sec[13] = 0;
    sym_sec[14] = 0; /* Type */
    sym_sec[15] = 0;
    sym_sec[16] = 3; /* IMAGE_SYM_CLASS_STATIC */
    sym_sec[17] = 1; /* NumberOfAuxSymbols */
    if (seed_coff_append(out, sym_sec, 18) != 0)
      return -1;
    memset(aux, 0, sizeof(aux));
    aux[0] = (uint8_t)(align4);
    aux[1] = (uint8_t)(align4 >> 8);
    aux[2] = (uint8_t)(align4 >> 16);
    aux[3] = (uint8_t)(align4 >> 24);
    aux[4] = (uint8_t)(num_relocs);
    aux[5] = (uint8_t)(num_relocs >> 8);
    aux[14] = 1;
    if (seed_coff_append(out, aux, 18) != 0)
      return -1;

    str_off = 4;
    for (s = 0; s < num_syms; s++) {
      uint8_t ent[18];
      int32_t is_common;
      memset(ent, 0, sizeof(ent));
      /* Long name: Zeroes + string-table offset */
      ent[4] = (uint8_t)(str_off);
      ent[5] = (uint8_t)(str_off >> 8);
      ent[6] = (uint8_t)(str_off >> 16);
      ent[7] = (uint8_t)(str_off >> 24);
      /* Value: function = .text offset; COMMON = payload size
       * (pipeline_elf_ctx_add_common_sym stores size in offset). */
      ent[8] = (uint8_t)(ctx->syms[s].offset);
      ent[9] = (uint8_t)(ctx->syms[s].offset >> 8);
      ent[10] = (uint8_t)(ctx->syms[s].offset >> 16);
      ent[11] = (uint8_t)(ctx->syms[s].offset >> 24);
      /* ELF SHN_COMMON = 0xfff2. PE/COFF has no SHN_COMMON: IMAGE_SYM_UNDEFINED
       * (SectionNumber=0) + Value=size + IMAGE_SYM_CLASS_EXTERNAL is the
       * Microsoft common-block convention (GNU ld / MinGW allocate writable
       * BSS). Twin of ELF SHN_COMMON / Mach-O N_UNDF|N_EXT (wave405).
       * Prior: every symbol was SectionNumber=1 + Type=FUNCTION, so leftover-PE
       * TYPE_FN let-init `Lxlang_al_*` landed in RX .text (store/call SEGV).
       * PLATFORM: WINDOWS leftover-PE / SHARED COFF cross-emit. */
      is_common = (ctx->syms[s].sym_shndx == (int32_t)0xfff2) ? 1 : 0;
      if (is_common != 0) {
        ent[12] = 0;
        ent[13] = 0;
        ent[14] = 0;
        ent[15] = 0;
        ent[16] = 2; /* IMAGE_SYM_CLASS_EXTERNAL */
        ent[17] = 0;
      } else {
        ent[12] = 1; /* SectionNumber = .text */
        ent[13] = 0;
        /* Type = IMAGE_SYM_DTYPE_FUNCTION << 4 */
        ent[14] = 32;
        ent[15] = 0;
        ent[16] = 2; /* IMAGE_SYM_CLASS_EXTERNAL */
        ent[17] = 0;
      }
      if (seed_coff_append(out, ent, 18) != 0)
        return -1;
      str_off = str_off + ctx->syms[s].name_len + 1;
    }

    str_size[0] = (uint8_t)(strtab_used);
    str_size[1] = (uint8_t)(strtab_used >> 8);
    str_size[2] = (uint8_t)(strtab_used >> 16);
    str_size[3] = (uint8_t)(strtab_used >> 24);
    if (seed_coff_append(out, str_size, 4) != 0)
      return -1;
    for (s = 0; s < num_syms; s++) {
      uint8_t *sym_nm = seed_elf_sym_name_ptr(ctx, s);
      if (ctx->syms[s].name_len > 0 && sym_nm != NULL &&
          seed_coff_append(out, sym_nm, ctx->syms[s].name_len) != 0)
        return -1;
      if (seed_coff_append(out, zero, 1) != 0)
        return -1;
    }
  }
  return out->length;
}



/** .x 模块名修饰后的 pipeline_module_num_funcs 转发（asm/backend 分 TU 链接）。 */
int32_t asm_pipeline_module_num_funcs(struct ast_Module *m) {
  return pipeline_module_num_funcs(m);
}
int32_t backend_pipeline_module_num_funcs(struct ast_Module *m) {
  return pipeline_module_num_funcs(m);
}

/**
 * pipeline 调用的 asm 文本 codegen：backend 产出 GAS，再窥孔优化。
 * 任一步失败返回 -1。
 */
int32_t asm_asm_codegen_ast(void *module, void *arena, void *out_buf, void *ctx) {
  if (backend_asm_codegen_ast(module, arena, out_buf, ctx) != 0)
    return -1;
  if (peephole_run(out_buf) != 0)
    return -1;
  return 0;
}

/**
 * 写出 -o .o / -o exe：先各 dep 再入口（与 asm.x::asm_codegen_elf_o 一致），再 reloc + 写 Mach-O/ELF。
 */
int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, void *elf_ctx, void *out_buf) {
  struct ast_PipelineDepCtx *pctx = (struct ast_PipelineDepCtx *)ctx;
  int32_t jdep;
  int32_t ndep_elf;

  if (elf_ctx) {
    platform_elf_elf_ctx_reset(elf_ctx);
    if (pctx && pipeline_dep_ctx_use_macho_o(pctx) != 0)
      seed_elf_ctx_set_macho_leading_underscore(elf_ctx, 1);
    /* PLATFORM: WINDOWS | PE/COFF — no Mach-O leading underscore.
     * Historical twin wrongly set underscore on use_coff_o → export `_main`
     * while MinGW CRT / MSVC expect `main`; lld `/entry:_main` papered over it. */
  }
  /** WPO v0：elf 全程序 emit 前构建 reach，供 backend 跳过 dead export。 */
  pipeline_asm_wpo_reach_compute_for_elf((struct ast_Module *)module, (struct ast_ASTArena *)arena, pctx);
  if (pctx && pipeline_dep_ctx_asm_entry_module_only(pctx) == 0) {
    ndep_elf = pipeline_dep_ctx_ndep(pctx);
    for (jdep = 0; jdep < ndep_elf; jdep++) {
      struct ast_Module *dep_mod;
      struct ast_ASTArena *dep_ar;
      uint8_t dep_path_buf[128];
      int pk;
      int dup;
      if (jdep == 0 && driver_skip_codegen_dep_0_get() != 0)
        continue;
      dep_mod = pipeline_dep_ctx_module_at(pctx, jdep);
      if (dep_mod == (struct ast_Module *)module)
        continue;
      dup = 0;
      for (pk = 0; pk < jdep; pk++) {
        if (pipeline_dep_ctx_module_at(pctx, pk) == dep_mod) {
          dup = 1;
          break;
        }
      }
      if (dup)
        continue;
      memset(dep_path_buf, 0, sizeof(dep_path_buf));
      pipeline_dep_ctx_import_path_copy64(pctx, jdep, dep_path_buf);
      if (seed_asm_emit_trace_enabled())
        diag_reportf(NULL, 0, 0, "note", NULL,
                     "asm emit trace: co-emit dep[%d] path=%s funcs=%d",
                     (int)jdep, (char *)dep_path_buf,
                     dep_mod ? (int)pipeline_module_num_funcs(dep_mod) : -1);
      /** freestanding 模式：nostdlib 链无预编译 std .o，跳过 skip（dep 须全部 co-emit）。
       * hosted 模式：std.io/fs/process/fmt 等族符号由预编译 .o 提供，skip 整库 co-emit。 */
      if (driver_freestanding_get() == 0) {
        if (pipeline_codegen_dep_skip_asm_user_std_io(dep_path_buf) != 0)
          continue;
        if (pipeline_codegen_dep_skip_asm_user_std_fs(dep_path_buf) != 0)
          continue;
        if (pipeline_codegen_dep_skip_asm_user_std_process(dep_path_buf) != 0)
          continue;
        if (pipeline_codegen_dep_skip_asm_user_std_fmt(dep_path_buf) != 0)
          continue;
        if (pipeline_codegen_dep_skip_asm_user_std_misc(dep_path_buf) != 0)
          continue;
        if (pipeline_codegen_dep_skip_asm_user_core_lib(dep_path_buf) != 0)
          continue;
        /* PLATFORM: SHARED — mixed scratch core.m6 + in-tree core.slice:
         * need_coemit is already 1; still skip hosted core/ so formal .o
         * stays the single authority (no duplicate T with on-demand). */
        if (pipeline_asm_user_dep_is_in_tree_core(dep_path_buf) != 0)
          continue;
        /* PLATFORM: SHARED — hosted std.compress (and the rest of the
         * link_only table) must not co-emit into user.o. Ubuntu ELF has no
         * -dead_strip: co-emitted lib.x stored s.hdr.inited as movq@0 and
         * wiped gzip magic (process n<0). Darwin Mach-O hid the dup T.
         * G.7: consult the existing link_only table; do not add a second skip. */
        if (pipeline_codegen_std_dep_link_only(dep_path_buf) != 0)
          continue;
      }
      driver_set_current_dep_path_for_codegen((const char *)dep_path_buf);
      dep_ar = pipeline_dep_ctx_arena_at(pctx, jdep);
      if (dep_mod != NULL && dep_ar != NULL && pipeline_module_num_funcs(dep_mod) > 0) {
        if (backend_asm_codegen_ast_to_elf(dep_mod, dep_ar, elf_ctx, ctx) != 0) {
          driver_set_current_dep_path_for_codegen(NULL);
          pipeline_asm_wpo_reach_clear();
          return -1;
        }
      }
      driver_set_current_dep_path_for_codegen(NULL);
    }
  }
  driver_set_current_dep_path_for_codegen(NULL);
  if (seed_asm_emit_trace_enabled())
    diag_reportf(NULL, 0, 0, "note", NULL,
                 "asm emit trace: asm_codegen_ast_to_elf entry module funcs=%d",
                 (int)pipeline_module_num_funcs(module));
  pipeline_asm_patch_module_parent_links(module, arena);
  if (backend_asm_codegen_ast_to_elf(module, arena, elf_ctx, ctx) != 0) {
    if (seed_asm_debug_enabled()) {
      diag_report(NULL, 0, 0, "note", "asm debug: asm_codegen_elf_o fail at backend entry", NULL);
      driver_diagnostic_asm_print_current_func();
    }
    pipeline_asm_wpo_reach_clear();
    return -1;
  }
  if (seed_asm_reject_empty_elf_text(module, elf_ctx) != 0) {
    pipeline_asm_wpo_reach_clear();
    return -1;
  }
  if (elf_ctx && peephole_elf_run(elf_ctx) != 0) {
    if (seed_asm_debug_enabled())
      diag_report(NULL, 0, 0, "note", "asm debug: asm_codegen_elf_o fail at peephole_elf", NULL);
    pipeline_asm_wpo_reach_clear();
    return -1;
  }
  if (elf_ctx && platform_elf_elf_resolve_patches(elf_ctx) != 0) {
    if (seed_asm_debug_enabled())
      diag_report(NULL, 0, 0, "note", "asm debug: asm_codegen_elf_o fail at resolve_patches", NULL);
    pipeline_asm_wpo_reach_clear();
    return -1;
  }
  if (pctx && pipeline_dep_ctx_use_coff_o(pctx) != 0) {
    int32_t cw = seed_platform_coff_write_coff_o_to_buf(elf_ctx, out_buf);
    if (seed_asm_debug_enabled())
      diag_reportf(NULL, 0, 0, "note", NULL,
                   "asm debug: asm_codegen_elf_o coff_write=%d out_len=%d",
                   (int)cw, (int)((struct codegen_CodegenOutBuf *)out_buf)->length);
    pipeline_asm_wpo_reach_clear();
    return cw < 0 ? -1 : 0;
  }
  if (pctx && pipeline_dep_ctx_use_macho_o(pctx) != 0) {
    int32_t mw = seed_platform_macho_write_macho_o_to_buf(elf_ctx, out_buf);
    if (seed_asm_debug_enabled())
      diag_reportf(NULL, 0, 0, "note", NULL,
                   "asm debug: asm_codegen_elf_o macho_write=%d out_len=%d",
                   (int)mw, (int)((struct codegen_CodegenOutBuf *)out_buf)->length);
    pipeline_asm_wpo_reach_clear();
    return mw < 0 ? -1 : 0;
  }
  {
    int32_t ew = pipeline_elf_write_o_standard_to_buf_c((uint8_t *)elf_ctx, (struct codegen_CodegenOutBuf *)out_buf);
    if (seed_asm_debug_enabled())
      diag_reportf(NULL, 0, 0, "note", NULL,
                   "asm debug: asm_codegen_elf_o elf_write=%d out_len=%d",
                   (int)ew, (int)((struct codegen_CodegenOutBuf *)out_buf)->length);
    pipeline_asm_wpo_reach_clear();
    return ew < 0 ? -1 : 0;
  }
}
