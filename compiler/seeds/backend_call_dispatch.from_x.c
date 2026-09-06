/* G-02f-9 / R2 full（2026-07-14）：backend_call_dispatch 真迁
 * Logic source: src/asm/backend_call_dispatch.x
 * Product PREFER_X_O: g05_try_x_to_o(full.x) + rest (-DXLANG_BACKEND_CALL_DISPATCH_FROM_X) ld -r
 *   → src/asm/backend_call_dispatch.o
 * R2: full.x 吃满 CALL/emit/import 公共业务；FROM_X 下 rest 业务 T=0（仅 slice_marker）
 * 冷启动/无 PREFER：本文件完整 C 体（含 L2 thin hybrid 的 _impl 尾）
 * L2 thin hybrid（XLANG_L2_CALL_DISPATCH_THIN_FROM_X）仍作 full.x 失败时的回退路径。
 *
 * seeds/backend_call_dispatch.from_x.c — product backend dispatch TU (cold full C)
 */
#ifndef XLANG_BACKEND_CALL_DISPATCH_FROM_X
/* G-02f-364/368：PREFER hybrid thin 由 src/asm/backend_call_dispatch_thin.x；rest XLANG_L2_CALL_DISPATCH_THIN_FROM_X。
 * seeds/backend_call_dispatch.from_x.c — G-02f-9 product backend dispatch TU
 * G-02f-134 true .x pure helpers.
 * G-02f-133 true .x pure helpers.
 * G-02f-125 true .x pure helpers.
 * G-02f-123 true .x pure helpers.
 * G-02f-122 true .x pure helpers.
 * G-02f-121 true .x pure helpers.
 * G-02f-120 true .x pure helpers.
 * G-02f-114 true .x pure helpers.
 * G-02f-113 true .x pure helpers.
 * G-02f-110 helper gates.
 * G-02f-109 helper gates.
 * G-02f-108 helper gates.
 * G-02f-184: f32 xmm flags true .x; residual mega emit still dual.
 * Source intent: src/asm/backend_call_dispatch.x + this seed (product C body).
 * Product: → src/asm/backend_call_dispatch.o.
 */
/**
 * backend_call_dispatch.c — EXPR_CALL ELF 发射与 import 限定符号解析（C 实现）
 *
 * M8 自举：emit_expr_elf_call / emit_expr_elf_method_call / asm_emit_call_args_elf 等在 mega_entry 下为 ret0 桩；
 * 本 TU 供 pipeline_asm_emit_call_elf_c / pipeline_asm_emit_method_call_elf_c / pipeline_asm_emit_call_args_elf_c 真 emit。
 */
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* also Cap va via xlang_va_cap (10.7.1) */ /* Cap residual 10.7.2: call_dispatch debugf → xlang_vsnprintf */

#include "diag.h"
#include "runtime_pipeline_abi.h"
#ifdef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
struct ast_ASTArena;
struct ast_Module;
struct platform_elf_ElfCodegenCtx;
struct backend_AsmFuncCtx;
struct codegen_CodegenOutBuf;
int32_t glue_asm_call_reg_max(int32_t ta);
int32_t glue_asm_call_stack_cleanup_bytes(int32_t ta, int32_t nargs);
int32_t glue_asm_append_export_c_suffix(uint8_t *sym, int32_t sym_len, int32_t cap);
int32_t glue_asm_string_lit_len(struct ast_ASTArena *arena, int32_t expr_ref);
int32_t glue_call_param_type_ref_at(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t param_index);
int32_t glue_call_param_is_f32_c(struct ast_ASTArena *arena, int32_t type_ref);
int32_t glue_asm_c_prefix_redundant_with_name(const uint8_t *prefix, int32_t prefix_len, const uint8_t *name, int32_t name_len);
int32_t glue_asm_import_path_segment_count(const uint8_t *path, int32_t path_len);
int32_t glue_asm_import_path_slice_equal(struct ast_Module *module, int32_t imp_ix, int32_t off, int32_t seg_len, const uint8_t *nm, int32_t nm_len);
int32_t glue_asm_import_binding_name_equal(struct ast_Module *module, int32_t imp_ix, const uint8_t *nm, int32_t nm_len);
int32_t pipeline_asm_emit_get_call_f32_xmm_c(void);
int32_t glue_module_func_overload_count_c(struct ast_Module *m, const uint8_t *name, int32_t name_len);
int32_t glue_asm_std_c_wrapper_fname_needs_export_c_suffix(const uint8_t *fname, int32_t fname_len);
int32_t glue_asm_fill_c_prefix_from_module_import(struct ast_Module *cur_mod, int32_t imp_ix, uint8_t *pre_buf);
int32_t glue_asm_prefix_is_fmt_or_debug(const uint8_t *pre, int32_t pre_len);
int32_t glue_asm_import_segment_at(struct ast_Module *module, int32_t imp_ix, int32_t want_seg, int32_t *ostr, int32_t *olen);
int32_t glue_asm_build_import_binding_call_sym(const uint8_t *pre, int32_t pre_len, const uint8_t *field_name, int32_t field_len, uint8_t *out_name);
int32_t glue_try_std_string_xlang_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out, int32_t out_cap);
int32_t glue_try_std_encoding_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out, int32_t out_cap);
int32_t glue_type_kind_to_suffix_c(int32_t kind_ord, uint8_t *out, int32_t out_cap);
int32_t glue_asm_emit_string_lit_ptr_rax_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t str_expr_ref, int32_t ta);
int32_t glue_sysv_x86_call_n_stack_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs);
int32_t glue_asm_build_dep_export_sym_c(const uint8_t *name, int32_t name_len, uint8_t *out, int32_t out_cap);
int32_t glue_asm_enc_call_redirected(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len, int32_t ta);
int32_t glue_try_std_heap_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out, int32_t out_cap);
int32_t pipeline_asm_abi_f32_xmm_enabled_c(void);
int32_t glue_asm_build_func_export_sym_c(struct ast_Module *m, struct ast_ASTArena *a, int32_t func_ix, uint8_t *out, int32_t out_cap);
int32_t glue_asm_emit_jmp_skip_string_then_lea(uint8_t *ctx_bytes, int32_t ta, int32_t reg_k, const uint8_t *sbuf, int32_t slen);
int32_t glue_spill_struct16_call_arg_to_lea_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, struct backend_AsmFuncCtx *ctx, int32_t pty, int32_t ta);
int32_t pipeline_asm_resolve_whole_import_qualified_symbol_c(struct ast_ASTArena *arena, struct ast_Module *cur_mod, int32_t callee_expr_ref, uint8_t *sym_flat, int32_t *out_match_imp_j);
int32_t pipeline_asm_emit_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
int32_t pipeline_asm_emit_method_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
int32_t pipeline_asm_emit_call_args_text_c(struct ast_ASTArena *arena, struct codegen_CodegenOutBuf *out, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t target_arch, int32_t nargs);
int32_t pipeline_asm_emit_call_args_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t nargs);
int32_t glue_emit_call_args_elf_sysv_f32_xmm_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t nargs);
int32_t glue_asm_emit_call_with_cleanup(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t nargs, uint8_t *cname, int32_t clen);
int32_t glue_emit_one_call_arg_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t call_expr_ref, int32_t arg_ref, int32_t arg_index, struct backend_AsmFuncCtx *ctx, int32_t ta);
int32_t glue_asm_build_call_export_sym_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t callee_ref, struct ast_Module *mod, struct ast_PipelineDepCtx *dep_pipe, uint8_t *out, int32_t out_cap);
int32_t glue_asm_try_emit_fmt_string_lit_import_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t call_expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta, const uint8_t *pre_buf, int32_t pre_len, const uint8_t *field_name, int32_t field_len);
int32_t glue_asm_try_emit_fmt_any_import_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t call_expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta, const uint8_t *pre_buf, int32_t pre_len, const uint8_t *field_name, int32_t field_len);
void pipeline_asm_emit_set_call_f32_xmm(int32_t on);
void glue_codegen_import_path_to_c_prefix_into(const uint8_t *path, uint8_t *buf, int32_t buf_cap);
void glue_asm_string_lit_into(struct ast_ASTArena *arena, int32_t expr_ref, uint8_t *out64);
void glue_sysv_x86_call_arg_slot_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs, int32_t arg_index, int32_t *out_kind, int32_t *out_reg_k, int32_t *out_stack_k);
int32_t glue_f32_xmm_flag_get_body(void);
#endif


/* wave231 G.7: env lookup authority = public pure thin link_abi_getenv (labi_diag_pure).
 * Cap residual host getenv stays only link_abi_getenv_impl. Cold twin of backend_call_dispatch.x. */
extern char *link_abi_getenv(const char *name);
/**
 * Returns 1 if the ELF codegen ctx targets Mach-O (Darwin) so symbol names need
 * a leading underscore prefix; 0 otherwise. Authority: pipeline_elf_ctx_macho_leading_underscore
 * in runtime_pipeline_abi.x. Used by vtable static emit to decide whether to prepend
 * `_` to wrapper/vtable symbol names. PLATFORM: SHARED.
 */
extern int32_t pipeline_elf_ctx_macho_leading_underscore(uint8_t *ctx);

static void backend_call_debugf(const char *fmt, ...) {
  char buf[256];
  xlang_va_list ap;
  /* wave231 G.7: XLANG_ASM_DEBUG via link_abi_getenv (not raw getenv). */
  if (!link_abi_getenv("XLANG_ASM_DEBUG"))
    return;
  xlang_va_start(ap, fmt);
  /* PLATFORM: SHARED — Cap fmt (10.7.2) + Cap va (10.7.1); no libc stdarg. */
  (void)xlang_vsnprintf(buf, sizeof buf, fmt ? fmt : "asm call debug", ap);
  xlang_va_end(ap);
  buf[sizeof buf - 1] = '\0';
  diag_report(NULL, 0, 0, "note", buf, NULL);
}

extern const char *driver_get_current_dep_path_for_codegen(void);
extern int32_t pipeline_expr_call_resolved_dep_index_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_call_resolved_func_index_at(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx *ctx, int32_t idx, uint8_t *dst);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx *ctx);
extern struct ast_Module *pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx *ctx, int32_t j);
extern struct ast_ASTArena *pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx *ctx, int32_t j);
extern int32_t pipeline_module_num_funcs(struct ast_Module *m);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module *m, int32_t fi, uint8_t *name, int32_t name_len);
extern int32_t pipeline_asm_module_func_is_extern_at(struct ast_Module *m, int32_t fi);
extern int32_t pipeline_asm_module_func_name_len_at(struct ast_Module *m, int32_t func_index);
extern void pipeline_asm_module_func_name_copy64(struct ast_Module *m, int32_t func_index, uint8_t *dst);
extern int32_t pipeline_module_func_num_params_at(struct ast_Module *m, int32_t func_idx);
extern int32_t pipeline_module_func_param_type_ref_at(struct ast_Module *m, int32_t fi, int32_t pi);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module *m, int32_t fi);
extern int32_t pipeline_type_elem_ref_at(struct ast_ASTArena *arena, int32_t type_ref);
/* TYPE_ARRAY size for mid `_aN` (align codegen wave687). PLATFORM: SHARED. */
extern int32_t pipeline_type_array_size_at(struct ast_ASTArena *arena, int32_t type_ref);
extern int32_t pipeline_typeck_type_refs_equal_c(struct ast_ASTArena *arena, int32_t a, int32_t b);
/* ctx is AsmFuncCtx*; void* avoids incomplete-type visibility warning before full layout. */
extern int32_t pipeline_asm_emit_lvalue_eff_addr_elf_c(struct ast_ASTArena *arena,
                                                      struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                      int32_t lval_ref, void *ctx, int32_t ta);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena *arena, int32_t type_ref, uint8_t *out64);
extern struct ast_PipelineDepCtx *pipeline_asm_emit_dep_pipe_c(void);
extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena *arena, int32_t block_ref, uint8_t *vname,
                                                    int32_t vlen);
extern int32_t asm_ctx_scope_block_ref_at(uint8_t *ctx);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_var_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out64);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx *ctx, int32_t idx);
extern int32_t pipeline_module_import_path_len(struct ast_Module *m, int32_t idx);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module *m, int32_t idx, int32_t off);

struct ast_ASTArena;
struct ast_Module;
struct ast_Expr;
struct platform_elf_ElfCodegenCtx;
struct backend_AsmFuncCtx;
struct codegen_CodegenOutBuf;

/** 与 backend.x AsmFuncCtx 前缀一致（module_ref + dep_pipe）。 */
struct glue_AsmFuncCtxCall {
  int32_t frame_size;
  int32_t next_offset;
  int32_t num_locals;
  int32_t label_counter;
  struct ast_Module *module_ref;
  uint8_t loop_break_label_stack[512];
  int32_t loop_break_len_stack[8];
  uint8_t loop_continue_label_stack[512];
  int32_t loop_continue_len_stack[8];
  uint8_t break_label[128];
  int32_t break_len;
  uint8_t continue_label[128];
  int32_t continue_len;
  int32_t loop_label_depth;
  void *dep_pipe;
};

/** import ast.x ImportKind.IMPORT_BINDING */
#define GLUE_IMPORT_KIND_BINDING 1
/** parser_asm_primary_slice / ast.h AST_EXPR_STRING_LIT；内容在 var_name。 */
#define GLUE_EXPR_STRING_LIT_ORD 59
#define GLUE_EXPR_FIELD_ACCESS_ORD 44
#define GLUE_EXPR_VAR_ORD 3
/** ast.x ExprKind.EXPR_ADDR_OF — &v for push(&v, x) arg typing. */
#define GLUE_EXPR_ADDR_OF_ORD 51
/** ast.x ExprKind.EXPR_INDEX / EXPR_AS — sort(&b[0]) / cast arg typing. */
#define GLUE_EXPR_INDEX_ORD 47
#define GLUE_EXPR_AS_ORD 54
/** ast.x ExprKind.EXPR_CALL / EXPR_METHOD_CALL — hello `fmt.println` is METHOD_CALL. */
#define GLUE_EXPR_CALL_ORD 48
#define GLUE_EXPR_METHOD_CALL_ORD 49
/** ast.x TypeKind.TYPE_PTR / TYPE_ARRAY / TYPE_SLICE */
#define GLUE_TYPE_PTR_ORD 9
#define GLUE_TYPE_ARRAY_ORD 10
#define GLUE_TYPE_SLICE_ORD 11

extern int32_t pipeline_elf_ctx_append_bytes(uint8_t *ctx_bytes, uint8_t *ptr, int32_t n);
/* stage10 10.2.1 slice9: block truncate after options(noreturn) ud2. */
extern void glue_asm_block_diverged_set(int32_t v);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena *arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_callee_ref_at(struct ast_ASTArena *arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena *arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena *arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena *arena, int32_t expr_ref);
extern void pipeline_expr_var_name_into(struct ast_ASTArena *arena, int32_t expr_ref, uint8_t *out);
extern struct ast_Expr *pipeline_arena_expr_ptr(struct ast_ASTArena *a, int32_t ref);
extern int32_t pipeline_expr_var_name_len_for_string_lit_c(struct ast_ASTArena *arena, int32_t expr_ref);

/** STRING_LIT（kind 59）字节长度。 */
/* G-02f-122：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_string_lit_len(struct ast_ASTArena *arena, int32_t expr_ref) {
  if (!arena || expr_ref <= 0)
    return 0;
  if (pipeline_expr_kind_ord_at(arena, expr_ref) != GLUE_EXPR_STRING_LIT_ORD)
    return 0;
  return pipeline_expr_var_name_len_for_string_lit_c(arena, expr_ref);
}
#endif




/** 拷贝 STRING_LIT 内容到 out64（至多 63 字节）。 */
/* G-02f-139：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-380 call：_impl 返回 i32（供 thin -E）；public void 仍 seed-only 非 PREFER */
int32_t glue_asm_string_lit_into_impl(struct ast_ASTArena *arena, int32_t expr_ref, uint8_t *out64) {
  if (!out64)
    return 0;
  /* out is u8[128]; pipeline_expr_var_name_into zeros/copies up to 127. Empty lit OK. */
  memset(out64, 0, 128);
  if (glue_asm_string_lit_len(arena, expr_ref) < 0)
    return 0;
  if (glue_asm_string_lit_len(arena, expr_ref) == 0)
    return 0;
  pipeline_expr_var_name_into(arena, expr_ref, out64);
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
void glue_asm_string_lit_into(struct ast_ASTArena *arena, int32_t expr_ref, uint8_t *out64) {
  (void)glue_asm_string_lit_into_impl(arena, expr_ref, out64);
}
#endif


/**
 * Embed a short string in the text stream and load its address into a GP reg.
 *
 * PLATFORM: SHARED (emit shape) / x86_64 + aarch64 (encodings):
 * - ta==0 (x86_64): short jmp over bytes + lea reg,[rip+disp]
 *   reg_k 0→rdi (fmt arg0 ptr), 1→rax (*u8 result)
 * - ta==1 (aarch64): B over 4-byte-aligned bytes + ADR x0, string
 *   reg_k 0 and 1 both map to x0 (AAPCS arg0 / result alias of "rax")
 * Wave108: open arm64 residual (Darwin pure-asm hello CG002).
 */
/* G-02f-143：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-375 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_emit_jmp_skip_string_then_lea_impl(uint8_t *ctx_bytes, int32_t ta, int32_t reg_k,
    const uint8_t *sbuf, int32_t slen) {
  uint8_t jmp2[2];
  uint8_t lea7[7];
  uint8_t z;
  uint8_t pad_z;
  uint8_t b4[4];
  uint8_t adr4[4];
  int32_t disp32;
  int32_t raw;
  int32_t pad;
  int32_t skip;
  int32_t imm26;
  int32_t imm;
  uint32_t b_inst;
  uint32_t adr_inst;
  uint32_t imm_bits;
  uint32_t immlo;
  uint32_t immhi;
  int32_t i;
  /* Stage 12.2.5: slen==0 empty ""; max 126 for x86 short-jmp (eb + len+1 ≤127). */
  if (!ctx_bytes || !sbuf || slen < 0 || slen > 126)
    return -1;
  if (ta != 0 && ta != 1)
    return -1;
  /* PLATFORM: MACOS/LINUX aarch64 — B + ADR PC-relative string embed (wave108). */
  if (ta == 1) {
    raw = slen + 1; /* +NUL */
    pad = (4 - (raw & 3)) & 3;
    skip = raw + pad;
    /* B imm26 units of 4: from B to after string = 4+skip bytes → 1+skip/4 words. */
    imm26 = 1 + (skip / 4);
    if (imm26 <= 0 || imm26 >= (1 << 25))
      return -1;
    b_inst = 0x14000000u | ((uint32_t)imm26 & 0x3FFFFFFu);
    b4[0] = (uint8_t)(b_inst);
    b4[1] = (uint8_t)(b_inst >> 8);
    b4[2] = (uint8_t)(b_inst >> 16);
    b4[3] = (uint8_t)(b_inst >> 24);
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, b4, 4) != 0)
      return -1;
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, (uint8_t *)sbuf, slen) != 0)
      return -1;
    z = 0;
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, &z, 1) != 0)
      return -1;
    pad_z = 0;
    for (i = 0; i < pad; i++) {
      if (pipeline_elf_ctx_append_bytes(ctx_bytes, &pad_z, 1) != 0)
        return -1;
    }
    /* ADR x0, string: imm = -skip (string is skip bytes before this insn). */
    imm = -skip;
    imm_bits = (uint32_t)imm & 0x1FFFFFu;
    immlo = imm_bits & 3u;
    immhi = (imm_bits >> 2) & 0x7FFFFu;
    /* Rd = x0 for both reg_k (arg0 / result). */
    (void)reg_k;
    adr_inst = 0x10000000u | (immlo << 29) | (immhi << 5);
    adr4[0] = (uint8_t)(adr_inst);
    adr4[1] = (uint8_t)(adr_inst >> 8);
    adr4[2] = (uint8_t)(adr_inst >> 16);
    adr4[3] = (uint8_t)(adr_inst >> 24);
    return pipeline_elf_ctx_append_bytes(ctx_bytes, adr4, 4);
  }
  /* PLATFORM: LINUX+MACOS x86_64 — short jmp + lea [rip]. */
  if (slen + 1 > 127)
    return -1;
  jmp2[0] = 0xeb;
  jmp2[1] = (uint8_t)(slen + 1);
  if (pipeline_elf_ctx_append_bytes(ctx_bytes, jmp2, 2) != 0)
    return -1;
  if (pipeline_elf_ctx_append_bytes(ctx_bytes, (uint8_t *)sbuf, slen) != 0)
    return -1;
  z = 0;
  if (pipeline_elf_ctx_append_bytes(ctx_bytes, &z, 1) != 0)
    return -1;
  disp32 = -slen - 8;
  lea7[0] = 0x48;
  lea7[1] = 0x8d;
  lea7[2] = (uint8_t)(reg_k == 0 ? 0x3d : 0x05);
  lea7[3] = (uint8_t)(disp32);
  lea7[4] = (uint8_t)((uint32_t)disp32 >> 8);
  lea7[5] = (uint8_t)((uint32_t)disp32 >> 16);
  lea7[6] = (uint8_t)((uint32_t)disp32 >> 24);
  return pipeline_elf_ctx_append_bytes(ctx_bytes, lea7, 7);
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_emit_jmp_skip_string_then_lea(uint8_t *ctx_bytes, int32_t ta, int32_t reg_k,
    const uint8_t *sbuf, int32_t slen) {
  return glue_asm_emit_jmp_skip_string_then_lea_impl(ctx_bytes, ta, reg_k, sbuf, slen);
}
#endif

extern int32_t pipeline_expr_field_access_base_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_field_access_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out);

extern int32_t pipeline_module_import_kind_at(struct ast_Module *m, int32_t idx);
extern int32_t pipeline_module_import_path_len(struct ast_Module *m, int32_t idx);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module *m, int32_t idx, int32_t off);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module *m, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module *m, int32_t idx, int32_t off);
extern int32_t pipeline_codegen_call_num_args_override(uint8_t *prefix, int32_t prefix_len, uint8_t *name,
                                                       int32_t name_len, int32_t num_args);
extern int32_t pipeline_asm_redirect_std_c_wrapper_sym(uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                         int32_t sym_cap);

extern void parser_get_module_import_path(void *module, int32_t i, uint8_t *out);
extern int32_t parser_get_module_num_imports(void *module);

extern void asm_qual_sym_layer_reset(void);
extern int32_t asm_qual_sym_layer_push(uint8_t *bytes, int32_t len);
extern int32_t asm_qual_sym_layer_count(void);
extern int32_t asm_qual_sym_layer_len(int32_t i);
extern void asm_qual_sym_layer_copy(int32_t i, uint8_t *dst, int32_t cap);

extern int32_t pipeline_asm_emit_expr_elf_for_call_args(struct ast_ASTArena *arena,
                                                        struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                        struct backend_AsmFuncCtx *ctx, int32_t ta);
extern void pipeline_asm_emit_set_call_param_type_ref(int32_t type_ref);
extern void pipeline_asm_emit_call_arg_begin_c(void);
extern void pipeline_asm_emit_call_arg_end_c(void);
extern int32_t pipeline_asm_call_param_type_ref_at_c(struct ast_ASTArena *arena, int32_t call_expr_ref,
                                                     int32_t param_index);
extern int32_t pipeline_asm_call_return_type_kind_ord_c(struct ast_ASTArena *arena, int32_t call_expr_ref);
extern int32_t pipeline_asm_emit_expr_c(struct ast_ASTArena *arena, struct codegen_CodegenOutBuf *out, int32_t expr_ref,
                                        struct backend_AsmFuncCtx *ctx, int32_t target_arch);
extern int32_t backend_arch_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf *out, int32_t k, int32_t ta);
extern int32_t backend_arch_emit_push_rax(struct codegen_CodegenOutBuf *out, int32_t ta);
extern int32_t backend_arch_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf *out, int32_t i, int32_t ta);
extern int32_t backend_arch_emit_add_sp_imm(struct codegen_CodegenOutBuf *out, int32_t n, int32_t ta);

extern int32_t try_inline_param0_single_field_call_elf(struct ast_ASTArena *arena,
                                                       struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                       struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t try_inline_param0_field_sum_call_elf(struct ast_ASTArena *arena,
                                                    struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                    struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t try_inline_x_plus_k_call_elf(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t try_inline_wpo_const_scalar_binop_call_elf(struct ast_ASTArena *arena,
                                                          struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                          struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t try_inline_wpo_const_vector_lane_of_binop_call_elf(struct ast_ASTArena *arena,
                                                                  struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                                  int32_t expr_ref, struct backend_AsmFuncCtx *ctx,
                                                                  int32_t ta);
extern int32_t try_call_wpo_mono_symbol_elf(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t try_call_wpo_mono_vector_lane_of_binop_call_elf(struct ast_ASTArena *arena,
                                                               struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                               int32_t expr_ref, struct backend_AsmFuncCtx *ctx,
                                                               int32_t ta);

extern int32_t backend_enc_mov_rax_to_arg_reg_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k, int32_t ta);
/* stage10 10.2.1 slice5: out/lateout from SysV GP → rax before store. */
extern int32_t backend_enc_mov_arg_reg_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k, int32_t ta);
/* wave359: freestanding i32.double → x*2 (mov+add self). */
extern int32_t backend_enc_mov_rax_to_rbx_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_rbx_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t pipeline_module_num_struct_layouts_at(struct ast_Module *m);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module *m, int32_t idx);
extern void pipeline_module_struct_layout_name_into(struct ast_Module *m, int32_t idx, uint8_t *out);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module *m, int32_t li);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module *m, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module *m, int32_t li, int32_t j, uint8_t *out);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module *m, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module *m, int32_t li, int32_t j);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena *a, int32_t tr, uint8_t *out);
extern int32_t pipeline_type_array_size_at(struct ast_ASTArena *a, int32_t tr);
extern int32_t pipeline_type_elem_ref_at(struct ast_ASTArena *a, int32_t tr);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena *a, int32_t tr);
extern int32_t backend_enc_add_rax_rbx_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t backend_enc_call_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len,
                                     int32_t ta);
/* F7 dyn Trait vtable dispatch — indirect call + 64-bit load cross-arch encoders. */
extern int32_t backend_enc_blr_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg, int32_t ta);
extern int32_t backend_enc_ldr_xreg_xreg_imm_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t dst_reg,
                                                   int32_t base_reg, int32_t offset, int32_t ta);
extern int32_t backend_enc_lea_sym_to_reg_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg,
                                               uint8_t *name, int32_t name_len, int32_t ta);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena *arena, int32_t block_ref, int32_t idx);
extern int32_t pipeline_typeck_resolve_type_alias_ref_c(struct ast_ASTArena *arena, int32_t type_ref);
extern int32_t pipeline_asm_emit_expr_elf_rec(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                              int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
/* Cap-fn-ptr (10.3.2): emit callee expr into rax/x0 before blr. */
extern int32_t pipeline_asm_emit_expr_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                           int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena *arena, int32_t type_ref, uint8_t *out);
extern int32_t pipeline_type_elem_ref_at(struct ast_ASTArena *arena, int32_t type_ref);
extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena *arena, int32_t expr_ref);
extern int32_t pipeline_elf_ctx_macho_leading_underscore(uint8_t *ctx);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena *arena, int32_t er);
extern int32_t pipeline_expr_int_val_at(struct ast_ASTArena *arena, int32_t er);
extern void pipeline_module_func_set_is_used(void *module, int32_t fi, int32_t is_used);
extern int32_t backend_enc_push_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_imm32_to_w0_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm32, int32_t ta);
extern int32_t backend_enc_mov_imm32_to_rbx_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm32, int32_t ta);
extern int32_t backend_enc_call_stack_cleanup_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t nbytes,
                                                   int32_t ta);
extern int32_t backend_enc_call_stack_reserve_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t nbytes,
                                                   int32_t ta);
extern int32_t backend_enc_store_x0_sp_offset_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off_bytes,
                                                   int32_t ta);

/** bench stream_*_batch 等最多 11 实参；与 backend.x 6 参上限解耦。 */
/** 与 grow 池一致：>64 实参边界见 tests/pool-limits/many_call_args.x。 */
#define GLUE_ASM_MAX_CALL_ARGS 96

extern int32_t backend_enc_store_x0_sp_offset_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off_bytes,
                                                   int32_t ta);
extern int32_t backend_enc_mov_eax_to_xmm_arg_reg_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k,
                                                       int32_t ta);
extern int32_t backend_enc_mov_rax_to_xmm_arg_reg_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k,
                                                       int32_t ta);
extern int32_t backend_enc_mov_xmm_arg_reg_to_eax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k,
                                                       int32_t ta);
extern int32_t backend_enc_mov_xmm_arg_reg_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k,
                                                       int32_t ta);
extern int32_t pipeline_asm_type_ref_byte_size_c(struct ast_ASTArena *arena, int32_t ty_ref);
extern int32_t pipeline_asm_call_arg_value_byte_size_c(struct ast_ASTArena *arena, struct backend_AsmFuncCtx *ctx,
                                                       int32_t arg_ref, int32_t pty);
extern int32_t glue_call_return_byte_size_c(struct ast_ASTArena *arena, int32_t call_expr_ref);
extern int32_t glue_type_named_layout_size_any_module_elf_c(struct ast_ASTArena *arena, int32_t ty_ref);
extern int32_t glue_arm64_mov_x8_to_x0_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t pipeline_asm_deref_struct16_rax_ptr_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t pipeline_asm_call_struct16_ret_needs_rax_deref_c(struct ast_ASTArena *arena, int32_t call_expr_ref);
extern int32_t pipeline_asm_emit_call_sret_reg_shift_c(void);
/** SysV MEMORY by-value push (pipeline_glue authority; >16B aggregates). */
extern int32_t pipeline_asm_push_sysv_memory_by_value_elf_c(struct ast_ASTArena *arena,
                                                            struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                            struct backend_AsmFuncCtx *ctx, int32_t arg_ref,
                                                            int32_t sz, int32_t ta);
/* wave603: arm64 MEMORY by-value → [sp+#sp_off] multi-word (VAR). */
extern int32_t pipeline_asm_store_memory_by_value_to_sp_elf_c(struct ast_ASTArena *arena,
                                                              struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                              struct backend_AsmFuncCtx *ctx, int32_t arg_ref,
                                                              int32_t sz, int32_t ta, int32_t sp_off);
extern int32_t backend_enc_store_rdx_to_rbp_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                                 int32_t ta);
extern int32_t backend_enc_store_rax_to_rbp_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                                 int32_t ta);
/* wave600: AAPCS64 dual-GP high half is x1 (store_rdx is x86-only). */
extern int32_t backend_enc_store_x_reg_to_rbp_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg,
                                                   int32_t offset, int32_t ta);
extern int32_t backend_enc_lea_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                               int32_t ta);
extern int32_t backend_enc_mov_rdx_to_arg_reg_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k,
                                                   int32_t ta);
extern int32_t backend_enc_load_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                                int32_t ta);
/* Incoming stack formals: [rbp+#off] x86 / [x29,#off] ARM64. G.7 param_home twins. */
extern int32_t backend_enc_load_rbp_pos_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off_pos,
                                                    int32_t ta);
extern int32_t backend_enc_load_x29_pos_to_rax_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off_pos,
                                                    int32_t ta);
extern int32_t backend_enc_load_rbp_to_rdx_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                                int32_t ta);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena *arena, int32_t type_ref);

/* G-02e：原 pipeline_abi_f32_xmm.c 并入本 TU，去掉独立手写 C 文件。 */
/* G-02f-184：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-366 thin get */ int32_t g_pipeline_asm_emit_call_f32_xmm;

/** 默认开启 f32 xmm ABI；XLANG_ABI_F32_XMM=0 回落 legacy f64 widen。 */
/* G-02f-184：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-374 call：实现体始终 seed；public PREFER 时 thin forward */
/* wave231 G.7: XLANG_ABI_F32_XMM via link_abi_getenv (not raw getenv). */
int32_t pipeline_asm_abi_f32_xmm_enabled_c_impl(void) {
  const char *env = link_abi_getenv("XLANG_ABI_F32_XMM");
  if (env && env[0] == '0' && env[1] == '\0')
    return 0;
  return 1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_abi_f32_xmm_enabled_c(void) {
  return pipeline_asm_abi_f32_xmm_enabled_c_impl();
}
#endif

/* G-02f-380 call：_impl 返回 i32（供 thin -E）；public void 仍 seed-only 非 PREFER */
int32_t pipeline_asm_emit_set_call_f32_xmm_impl(int32_t on) {
  g_pipeline_asm_emit_call_f32_xmm = on != 0 ? 1 : 0;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
void pipeline_asm_emit_set_call_f32_xmm(int32_t on) {
  (void)pipeline_asm_emit_set_call_f32_xmm_impl(on);
}
#endif

/* G-02f-381 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_f32_xmm_flag_get_body_impl(void) {
  return g_pipeline_asm_emit_call_f32_xmm;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_f32_xmm_flag_get_body(void) {
  return glue_f32_xmm_flag_get_body_impl();
}
#endif

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_emit_get_call_f32_xmm_c(void) {
  return glue_f32_xmm_flag_get_body();
}
#endif

#define GLUE_TYPE_F32_ORD 14
#define GLUE_TYPE_F64_ORD 15

int32_t glue_call_param_type_ref_at(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t param_index);
int32_t glue_emit_one_call_arg_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t call_expr_ref, int32_t arg_ref, int32_t arg_index,
                                            struct backend_AsmFuncCtx *ctx, int32_t ta);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena *a, int32_t expr_ref);

/** 形参/实参 type_ref 是否走 SysV SSE 浮点寄存器类（f32 或 f64）。
 * Historical name is_f32; f64 shares xmm0–7 (G.7 complete, not a second gate).
 * PLATFORM: SHARED kind check / LINUX+MACOS x86_64 SysV xmm slotting. */
/* G-02f-120：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_call_param_is_f32_c(struct ast_ASTArena *arena, int32_t type_ref) {
  int32_t k;
  if (!arena || type_ref <= 0)
    return 0;
  k = pipeline_type_kind_ord_at(arena, type_ref);
  return (k == GLUE_TYPE_F32_ORD || k == GLUE_TYPE_F64_ORD) ? 1 : 0;
}
#endif

/**
 * True if this arg_ref should use SysV xmm (param type f32/f64, FLOAT_LIT, or resolved float).
 * PLATFORM: SHARED classification / LINUX+MACOS x86_64 SysV placement.
 * G.7: single helper for CALL and METHOD_CALL import paths (math.floor is METHOD_CALL).
 */
static int32_t glue_arg_ref_is_sse_float_c(struct ast_ASTArena *arena, int32_t arg_ref, int32_t pty) {
  int32_t ko;
  int32_t atr;
  int32_t ak;
  if (glue_call_param_is_f32_c(arena, pty))
    return 1;
  if (!arena || arg_ref <= 0)
    return 0;
  ko = pipeline_expr_kind_ord_at(arena, arg_ref);
  if (ko == 1) /* FLOAT_LIT → default f64 bits / SysV xmm */
    return 1;
  atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
  if (atr <= 0)
    return 0;
  ak = pipeline_type_kind_ord_at(arena, atr);
  return (ak == 14 || ak == 15) ? 1 : 0;
}

/**
 * True if call arg should use SysV xmm (param type f32/f64, or arg is FLOAT_LIT / resolved float).
 * Completes import callees when dep param type_ref mapping is missing.
 */
static int32_t glue_call_arg_is_sse_float_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t arg_index,
                                            int32_t pty) {
  int32_t arg_ref;
  if (!arena || call_expr_ref <= 0 || arg_index < 0)
    return glue_arg_ref_is_sse_float_c(arena, 0, pty);
  arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, arg_index);
  return glue_arg_ref_is_sse_float_c(arena, arg_ref, pty);
}

/** f64 width for movq vs movd when placing into xmm. */
static int32_t glue_arg_ref_is_f64_width_c(struct ast_ASTArena *arena, int32_t arg_ref, int32_t pty) {
  int32_t atr;
  int32_t ak;
  if (pty > 0 && arena) {
    int32_t pk = pipeline_type_kind_ord_at(arena, pty);
    if (pk == 15)
      return 1;
    /* Formal f32 wins over unstamped FLOAT_LIT default-f64. */
    if (pk == 14)
      return 0;
  }
  if (!arena || arg_ref <= 0)
    return 0;
  /* FLOAT_LIT: honor typeck stamp (f32=14 / f64=15). Unstamped default f64.
   * Dyn extras pass pty=0 (slot ≠ func) so formal-kind cannot win above. */
  if (pipeline_expr_kind_ord_at(arena, arg_ref) == 1) {
    atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
    if (atr > 0) {
      ak = pipeline_type_kind_ord_at(arena, atr);
      if (ak == 15)
        return 1;
      if (ak == 14)
        return 0;
    }
    return 1;
  }
  atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
  if (atr <= 0)
    return 0;
  ak = pipeline_type_kind_ord_at(arena, atr);
  return ak == 15 ? 1 : 0;
}

static int32_t glue_call_arg_is_f64_width_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t arg_index,
                                            int32_t pty) {
  int32_t arg_ref;
  if (!arena || call_expr_ref <= 0)
    return glue_arg_ref_is_f64_width_c(arena, 0, pty);
  arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, arg_index);
  return glue_arg_ref_is_f64_width_c(arena, arg_ref, pty);
}

/**
 * PLATFORM: LINUX+MACOS x86_64 SysV — how many integer arg registers a value of size sz needs.
 * 9–16B POD → 2; else 1 (scalars / pointers / ≤8B).
 * wave601: >16B is MEMORY by-value on the stack (0 GP). Historical comment "caller lea → 1
 * pointer" mismatched formal C / param_home (callee reads [rbp+0x10..], not rdi).
 */
static int32_t glue_sysv_arg_gp_units_from_size_c(int32_t sz) {
  if (sz > 16)
    return 0; /* MEMORY class — no GP; stack words via n_stack / push_sysv_memory */
  if (sz > 8 && sz <= 16)
    return 2;
  return 1;
}

/** SysV MEMORY by-value: aggregate size >16 (not a pointer in a GP). */
static int32_t glue_sysv_arg_is_memory_by_value_c(int32_t sz) {
  return sz > 16 ? 1 : 0;
}

/** Stack words for one SysV arg: MEMORY → ceil(sz/8); integer stack excess → units. */
static int32_t glue_sysv_arg_stack_words_c(int32_t sz, int32_t gp_units) {
  if (sz > 16)
    return (sz + 7) / 8;
  if (gp_units < 1)
    return 1;
  return gp_units;
}

/**
 * Byte size of a call/method arg for SysV packing.
 * Take max of call_arg_value / formal / resolved / nested CALL return size.
 * Root (ErrorChain nested CALL-as-MEMORY Cap): call_arg_value floors to 8 for
 * non-VAR args and early-return blocked formal ErrorChain (20B) → is_mem≠2 → SEGV.
 * Root (bare CALL formal size): x86 slot/n_stack classifiers pass ctx=NULL, so
 * call_arg cannot recover VAR decl; soft sz=8 → lea→rdi while callee expects
 * SysV stack MEMORY. Widen non-CALL soft sizes only when formal/resolved
 * named_layout (or type_ref size) is true MEMORY (>16). Do NOT max ≤16 layouts
 * (SLICE fat=16 would undo E* pack → slice_oob).
 * G.7: one packer; max() not first-wins. PLATFORM: SHARED freestanding dual-GP.
 */
static int32_t glue_sysv_arg_byte_size_c(struct ast_ASTArena *arena, struct backend_AsmFuncCtx *ctx, int32_t pty,
                                         int32_t arg_ref) {
  int32_t sz = 0;
  int32_t alt = 0;
  int32_t ko = 0;
  int32_t tr = 0;
  if (arena)
    sz = pipeline_asm_call_arg_value_byte_size_c(arena, ctx, arg_ref, pty);
  /*
   * Preserve call_arg SLICE/ARRAY→8 pointer packing for VAR/FIELD/etc.
   * Widen nested CALL/METHOD when soft (≤16): formal/resolved named layout +
   * callee return (ErrorChain 20B). Widen non-CALL soft only to MEMORY (>16).
   * PLATFORM: SHARED freestanding · MACOS|ARM64 host-indirect · LINUX SysV.
   */
  if (arg_ref > 0 && arena) {
    ko = pipeline_expr_kind_ord_at(arena, arg_ref);
    if (ko == 48 || ko == 49) {
      if (sz <= 16) {
        if (pty > 0) {
          alt = pipeline_asm_type_ref_byte_size_c(arena, pty);
          if (alt > sz)
            sz = alt;
          alt = glue_type_named_layout_size_any_module_elf_c(arena, pty);
          if (alt > sz)
            sz = alt;
        }
        tr = pipeline_expr_resolved_type_ref(arena, arg_ref);
        if (tr > 0) {
          alt = pipeline_asm_type_ref_byte_size_c(arena, tr);
          if (alt > sz)
            sz = alt;
          alt = glue_type_named_layout_size_any_module_elf_c(arena, tr);
          if (alt > sz)
            sz = alt;
        }
        alt = glue_call_return_byte_size_c(arena, arg_ref);
        if (alt > sz)
          sz = alt;
      }
    } else if (sz <= 16) {
      /*
       * Non-CALL VAR/FIELD/…: MEMORY-class widen when soft (ctx may be null).
       * Only TYPE_NAMED named_layout >16 (ErrorChain 20B). Do NOT use
       * type_ref_byte_size — ARRAY payload (e.g. [2]Wide=40) would undo E*
       * pack (ret_idx(a) / slice_oob). PLATFORM: SHARED · LINUX SysV gold.
       */
      if (pty > 0 && pipeline_type_kind_ord_at(arena, pty) == 8) {
        alt = glue_type_named_layout_size_any_module_elf_c(arena, pty);
        if (alt > 16 && alt > sz)
          sz = alt;
      }
      tr = pipeline_expr_resolved_type_ref(arena, arg_ref);
      if (tr > 0 && pipeline_type_kind_ord_at(arena, tr) == 8) {
        alt = glue_type_named_layout_size_any_module_elf_c(arena, tr);
        if (alt > 16 && alt > sz)
          sz = alt;
      }
    }
  } else if (sz <= 0 && pty > 0 && arena) {
    sz = pipeline_asm_type_ref_byte_size_c(arena, pty);
  }
  if (sz <= 0)
    return 8;
  return sz;
}

/**
 * Place rax/x0 (+ rdx/x1 for 9–16B) into consecutive integer arg regs starting at gp.
 * PLATFORM: LINUX+MACOS x86_64 SysV (rax+rdx) · MACOS|ARM64 AAPCS64 (x0+x1, wave600).
 */
static int32_t glue_sysv_place_rax_rdx_arg_regs_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta,
                                                      int32_t gp, int32_t gp_units) {
  if (!elf_ctx || gp < 0)
    return -1;
  if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, gp, ta) != 0)
    return -1;
  if (gp_units >= 2) {
    if (ta == 0) {
      if (backend_enc_mov_rdx_to_arg_reg_arch(elf_ctx, gp + 1, ta) != 0)
        return -1;
    } else if (ta == 1) {
      /*
       * wave600: AAPCS64 dual-GP high half is x1. Product call-arg path uses
       * spill-then-load (not place). Direct place only valid when gp==0 so
       * x0/x1 already match the first dual-GP formal pair.
       */
      if (gp != 0)
        return -1;
    }
  }
  return 0;
}

/**
 * Spill rax/x0 [+ rdx/x1 for 9–16B] to a fresh frame slot; leave next_offset advanced.
 * PLATFORM: LINUX+MACOS x86_64 SysV — multi-arg packing: emit all values to memory first so
 * dual-load (uses rdx) does not clobber already-placed higher arg regs (e.g. index in rdx).
 * wave392: also AAPCS64 (ta==1) for nested CALL while placing xN (make1 destroys x1 holding make2).
 * wave600: AAPCS64 9–16B INTEGER dual-GP — spill x1 high half @ off+8 (low-end polarity ≡
 * store_retval_pair / param_home); prior units=1 left only x0 → multi dual-GP take2 wrong.
 * Returns spill offset (low half), or -1.
 */
static int32_t glue_sysv_spill_rax_rdx_to_frame_c(struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                   struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t gp_units) {
  struct glue_AsmFuncCtxCall *ly;
  int32_t off;
  if (!elf_ctx || !ctx || (ta != 0 && ta != 1))
    return -1;
  ly = (struct glue_AsmFuncCtxCall *)ctx;
  off = ly->next_offset + 16;
  if (off < 16)
    off = 16;
  if (backend_enc_store_rax_to_rbp_arch(elf_ctx, off, ta) != 0)
    return -1;
  if (gp_units >= 2) {
    if (ta == 0) {
      /* SysV high-end: high half @ home-8 (rdx). */
      if (backend_enc_store_rdx_to_rbp_arch(elf_ctx, off - 8, ta) != 0)
        return -1;
    } else if (ta == 1) {
      /* AAPCS64 low-end: high half @ home+8 (x1). PLATFORM: MACOS|ARM64. */
      if (backend_enc_store_x_reg_to_rbp_arch(elf_ctx, 1, off + 8, ta) != 0)
        return -1;
    }
  }
  ly->next_offset = off + 16;
  return off;
}

/**
 * Load spilled arg from frame into integer arg regs starting at gp.
 * PLATFORM: LINUX+MACOS x86_64 SysV (high@spill-8) · MACOS|ARM64 (high@spill+8, wave600).
 *
 * wave600: when gp==0 and dual-GP, load **high half first** then low into x0/rax.
 * Loading low→x0 then high→x0→x1 overwrites low (mac take2 x0 ended as high half only).
 * When gp>0, x0/rax is a pure temp so low-then-high is fine.
 */
static int32_t glue_sysv_load_spill_to_arg_regs_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta,
                                                      int32_t spill_off, int32_t gp, int32_t gp_units) {
  int32_t half2;
  if (!elf_ctx || spill_off < 0 || gp < 0)
    return -1;
  if (gp_units >= 2 && gp == 0) {
    half2 = (ta == 1) ? (spill_off + 8) : (spill_off - 8);
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, half2, ta) != 0)
      return -1;
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0)
      return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off, ta) != 0)
      return -1;
    /* low → arg0: arm64 x0 is already arg0 (no-op mov); x86 must rax→rdi. */
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0)
      return -1;
    return 0;
  }
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off, ta) != 0)
    return -1;
  if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, gp, ta) != 0)
    return -1;
  if (gp_units >= 2) {
    half2 = (ta == 1) ? (spill_off + 8) : (spill_off - 8);
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, half2, ta) != 0)
      return -1;
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, gp + 1, ta) != 0)
      return -1;
  }
  return 0;
}

/** SysV x86_64：第 arg_index 个实参的寄存器/栈归属（0=gp 1=xmm 2=stack）。
 * PLATFORM: LINUX+MACOS x86_64 SysV — 9–16B INTEGER aggregates consume 2 GP slots. */
/* G-02f-141：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-380 call：_impl 返回 i32（供 thin -E）；public void 仍 seed-only 非 PREFER */
int32_t glue_sysv_x86_call_arg_slot_c_impl(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs,
                                          int32_t arg_index, int32_t *out_kind, int32_t *out_reg_k,
                                          int32_t *out_stack_k) {
  int32_t gp;
  int32_t xmm;
  int32_t stk;
  int32_t j;
  int32_t pty;
  int32_t arg_ref;
  int32_t units;
  int32_t sz;
  int32_t words;
  if (!out_kind || !out_reg_k || !out_stack_k)
    return 0;
  gp = 0;
  xmm = 0;
  stk = 0;
  for (j = 0; j <= arg_index && j < nargs; j++) {
    pty = glue_call_param_type_ref_at(arena, call_expr_ref, j);
    arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, j);
    sz = glue_sysv_arg_byte_size_c(arena, 0, pty, arg_ref);
    units = glue_sysv_arg_gp_units_from_size_c(sz);
    words = glue_sysv_arg_stack_words_c(sz, units);
    if (j == arg_index) {
      if (glue_call_arg_is_sse_float_c(arena, call_expr_ref, j, pty)) {
        if (xmm < 8) {
          *out_kind = 1;
          *out_reg_k = xmm;
        } else {
          *out_kind = 2;
          *out_stack_k = stk;
        }
      } else if (glue_sysv_arg_is_memory_by_value_c(sz)) {
        /* wave601: MEMORY by-value — stack only, never a GP pointer. */
        *out_kind = 2;
        *out_stack_k = stk;
      } else if (units > 0 && gp + units <= 6) {
        *out_kind = 0;
        *out_reg_k = gp;
      } else {
        *out_kind = 2;
        *out_stack_k = stk;
      }
      return 0;
    }
    if (glue_call_arg_is_sse_float_c(arena, call_expr_ref, j, pty)) {
      if (xmm < 8)
        xmm++;
      else
        stk++;
    } else if (glue_sysv_arg_is_memory_by_value_c(sz)) {
      stk += words;
    } else if (units > 0 && gp + units <= 6) {
      gp += units;
    } else {
      stk += words;
    }
  }
  *out_kind = 2;
  *out_reg_k = 0;
  *out_stack_k = 0;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
void glue_sysv_x86_call_arg_slot_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs,
                                          int32_t arg_index, int32_t *out_kind, int32_t *out_reg_k,
                                          int32_t *out_stack_k) {
  (void)glue_sysv_x86_call_arg_slot_c_impl(arena, call_expr_ref, nargs, arg_index, out_kind, out_reg_k, out_stack_k);
}
#endif


/** SysV x86_64：统计走栈的实参个数（gp/xmm 寄存器用尽后的余量）。 */
/* G-02f-121：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-373 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_sysv_x86_call_n_stack_c_impl(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs) {
  int32_t gp;
  int32_t xmm;
  int32_t stk;
  int32_t j;
  int32_t pty;
  int32_t arg_ref;
  int32_t units;
  int32_t sz;
  int32_t words;
  gp = 0;
  xmm = 0;
  stk = 0;
  for (j = 0; j < nargs; j++) {
    pty = glue_call_param_type_ref_at(arena, call_expr_ref, j);
    arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, j);
    sz = glue_sysv_arg_byte_size_c(arena, 0, pty, arg_ref);
    units = glue_sysv_arg_gp_units_from_size_c(sz);
    words = glue_sysv_arg_stack_words_c(sz, units);
    if (glue_call_arg_is_sse_float_c(arena, call_expr_ref, j, pty)) {
      if (xmm < 8)
        xmm++;
      else
        stk++;
    } else if (glue_sysv_arg_is_memory_by_value_c(sz)) {
      /* wave601: MEMORY multi-word on stack (not 1 GP). */
      stk += words;
    } else if (units > 0 && gp + units <= 6) {
      gp += units;
    } else {
      stk += words;
    }
  }
  return stk;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_sysv_x86_call_n_stack_c(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t nargs) {
  return glue_sysv_x86_call_n_stack_c_impl(arena, call_expr_ref, nargs);
}
#endif




/**
 * 9–16B struct call-arg post-process (historical name: spill+lea).
 *
 * PLATFORM: LINUX+MACOS x86_64 SysV — INTEGER-class aggregates 9–16B pass by value in two
 * consecutive GPRs. Nested CALL already returns them in rax+rdx; converting to a stack pointer
 * (lea) mismatches formal C (e.g. std_string_length_StrView takes rdi=ptr, rsi=len).
 * Authority: leave rax/rdx intact; placement uses mov_rax/mov_rdx_to_arg_reg.
 * (G.7: single path with call-arg VAR dual load in pipeline_glue.)
 */
/* G-02f-145：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-375 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_spill_struct16_call_arg_to_lea_elf_c_impl(struct ast_ASTArena *arena,
                                                          struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                          struct backend_AsmFuncCtx *ctx, int32_t pty,
                                                          int32_t ta) {
  (void)arena;
  (void)elf_ctx;
  (void)ctx;
  (void)pty;
  (void)ta;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_spill_struct16_call_arg_to_lea_elf_c(struct ast_ASTArena *arena,
                                                          struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                          struct backend_AsmFuncCtx *ctx, int32_t pty,
                                                          int32_t ta) {
  return glue_spill_struct16_call_arg_to_lea_elf_c_impl(arena, elf_ctx, ctx, pty, ta);
}
#endif


/** x86 SysV f32 xmm CALL 实参：gp/xmm 分轨 + 栈实参（XLANG_ABI_F32_XMM=1）。 */
/* G-02f-145：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-377 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_emit_call_args_elf_sysv_f32_xmm_c_impl(struct ast_ASTArena *arena,
                                                      struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                      struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t nargs) {
  int32_t n_stack;
  int32_t stack_reserve;
  int32_t i;
  int32_t arg_ref;
  int32_t kind;
  int32_t reg_k;
  int32_t stack_k;
  int32_t stk_push[GLUE_ASM_MAX_CALL_ARGS];
  int32_t n_stk_push;
  int32_t si;

  n_stack = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
  stack_reserve = 0;
  if (n_stack > 0) {
    stack_reserve = n_stack * 8;
    if (n_stack & 1)
      stack_reserve += 8;
  }
  if (backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve, ta) != 0)
    return -1;
  n_stk_push = 0;
  for (i = 0; i < nargs; i++) {
    glue_sysv_x86_call_arg_slot_c(arena, expr_ref, nargs, i, &kind, &reg_k, &stack_k);
    if (kind == 2)
      stk_push[n_stk_push++] = i;
  }
  if (n_stack > 0 && (n_stack & 1)) {
    if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0)
      return -1;
    if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
      return -1;
  }
  for (si = n_stk_push - 1; si >= 0; si--) {
    int32_t pty_i;
    int32_t sz_i;
    int32_t pushed;
    i = stk_push[si];
    arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
    if (arg_ref == 0)
      continue;
    pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
    sz_i = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, arg_ref);
    /*
     * wave601: >16B MEMORY by-value — multi-qword push (not single lea→push).
     * Matches method-import path + formal param_home [rbp+0x10..].
     */
    if (glue_sysv_arg_is_memory_by_value_c(sz_i)) {
      pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(arena, elf_ctx, ctx, arg_ref, sz_i, ta);
      if (pushed < 0)
        return -1;
      continue;
    }
    if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
      return -1;
    if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
      return -1;
  }
  pipeline_asm_emit_set_call_f32_xmm(1);
  /**
   * PLATFORM: LINUX+MACOS x86_64 SysV — spill each reg arg to frame, then load into final
   * GPs/xmm. Dual-load of 9–16B POD uses rdx; reverse place without spill clobbers index.
   */
  {
    int32_t spill_off[GLUE_ASM_MAX_CALL_ARGS];
    int32_t spill_kind[GLUE_ASM_MAX_CALL_ARGS];
    int32_t spill_reg[GLUE_ASM_MAX_CALL_ARGS];
    int32_t spill_units[GLUE_ASM_MAX_CALL_ARGS];
    int32_t spill_is_f64[GLUE_ASM_MAX_CALL_ARGS];
    for (i = 0; i < nargs; i++) {
      spill_off[i] = -1;
      spill_kind[i] = 2;
      spill_reg[i] = 0;
      spill_units[i] = 1;
      spill_is_f64[i] = 0;
    }
    for (i = 0; i < nargs; i++) {
      int32_t pty;
      int32_t arg_ko;
      int32_t use_xmm;
      int32_t units;
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      if (arg_ref == 0)
        continue;
      glue_sysv_x86_call_arg_slot_c(arena, expr_ref, nargs, i, &kind, &reg_k, &stack_k);
      if (kind == 2)
        continue;
      if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0) {
        pipeline_asm_emit_set_call_f32_xmm(0);
        return -1;
      }
      pty = glue_call_param_type_ref_at(arena, expr_ref, i);
      arg_ko = pipeline_expr_kind_ord_at(arena, arg_ref);
      use_xmm = (kind == 1) || glue_call_arg_is_sse_float_c(arena, expr_ref, i, pty);
      units = glue_sysv_arg_gp_units_from_size_c(glue_sysv_arg_byte_size_c(arena, ctx, pty, arg_ref));
      if (use_xmm)
        units = 1;
      spill_off[i] = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, units);
      if (spill_off[i] < 0) {
        pipeline_asm_emit_set_call_f32_xmm(0);
        return -1;
      }
      spill_kind[i] = use_xmm ? 1 : 0;
      spill_reg[i] = reg_k;
      spill_units[i] = units;
      spill_is_f64[i] = glue_call_arg_is_f64_width_c(arena, expr_ref, i, pty) || arg_ko == 1 ||
                       (pty > 0 && pipeline_type_kind_ord_at(arena, pty) == 15);
    }
    for (i = 0; i < nargs; i++) {
      int32_t mov_rc;
      if (spill_off[i] < 0)
        continue;
      if (spill_kind[i] == 0) {
        if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], spill_reg[i],
                                                   spill_units[i]) != 0) {
          pipeline_asm_emit_set_call_f32_xmm(0);
          return -1;
        }
      } else {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off[i], ta) != 0) {
          pipeline_asm_emit_set_call_f32_xmm(0);
          return -1;
        }
        if (spill_is_f64[i])
          mov_rc = backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, spill_reg[i], ta);
        else
          mov_rc = backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, spill_reg[i], ta);
        if (mov_rc != 0) {
          pipeline_asm_emit_set_call_f32_xmm(0);
          return -1;
        }
      }
    }
  }
  pipeline_asm_emit_set_call_f32_xmm(0);
  pipeline_asm_emit_set_call_param_type_ref(0);
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_emit_call_args_elf_sysv_f32_xmm_c(struct ast_ASTArena *arena,
                                                      struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                      struct backend_AsmFuncCtx *ctx, int32_t ta, int32_t nargs) {
  return glue_emit_call_args_elf_sysv_f32_xmm_c_impl(arena, elf_ctx, expr_ref, ctx, ta, nargs);
}
#endif


/**
 * 当前架构整数 CALL 寄存器实参个数（x86_64 SysV=6，AAPCS64/RISC-V=8）。
 */
/* G-02f-113：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_call_reg_max(int32_t ta) {
  if (ta == 0)
    return 6;
  return 8;
}
#endif



/**
 * call 完成后须回收的 outgoing 栈字节数（含 16 字节对齐垫层）。
 */
/* G-02f-113：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_call_stack_cleanup_bytes(int32_t ta, int32_t nargs) {
  int32_t reg_max;
  int32_t n_stack;
  if (nargs <= 0)
    return 0;
  reg_max = glue_asm_call_reg_max(ta);
  n_stack = nargs - reg_max;
  if (n_stack <= 0)
    return 0;
  if (ta == 0) {
    int32_t bytes = n_stack * 8;
    if (n_stack & 1)
      bytes += 8;
    return bytes;
  }
  if (ta == 2)
    return -1;
  return (n_stack * 8 + 15) & ~15;
}
#endif



/**
 * 将 import 路径转为 C 符号前缀（`.`→`_`，末尾再补 `_`），与 codegen.x codegen_import_path_to_c_prefix_into 一致。
 */
/* G-02f-139：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-380 call：_impl 返回 i32（供 thin -E）；public void 仍 seed-only 非 PREFER */
int32_t glue_codegen_import_path_to_c_prefix_into_impl(const uint8_t *path, uint8_t *buf, int32_t buf_cap) {
  int32_t off;
  int32_t pi;
  if (!buf || buf_cap <= 0)
    return 0;
  off = 0;
  pi = 0;
  while (path) {
    uint8_t ch = path[pi];
    if (ch == 0)
      break;
    if (off + 2 >= buf_cap)
      break;
    buf[off] = (ch == 46) ? 95 : ch;
    off++;
    pi++;
  }
  if (off + 1 < buf_cap) {
    buf[off] = 95;
    off++;
  }
  buf[off] = 0;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
void glue_codegen_import_path_to_c_prefix_into(const uint8_t *path, uint8_t *buf, int32_t buf_cap) {
  (void)glue_codegen_import_path_to_c_prefix_into_impl(path, buf, buf_cap);
}
#endif


/** 前缀为 ASCII 「build_」（6 字节）且 name 已含此前缀时返回 1。 */
/* G-02f-121：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_c_prefix_redundant_with_name(const uint8_t *prefix, int32_t prefix_len, const uint8_t *name,
                                                     int32_t name_len) {
  int32_t i;
  if (!prefix || !name || prefix_len != 6 || name_len < prefix_len)
    return 0;
  if (prefix[0] != 98 || prefix[1] != 117 || prefix[2] != 105 || prefix[3] != 108 || prefix[4] != 100 ||
      prefix[5] != 95)
    return 0;
  for (i = 0; i < prefix_len; i++) {
    if (name[i] != prefix[i])
      return 0;
  }
  return 1;
}
#endif




/** 将 C 前缀与字段名拼成至多 63 字节的 call 符号；成功返回长度，失败 -1。 */
/* G-02f-122：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-371 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_build_import_binding_call_sym_impl(const uint8_t *pre, int32_t pre_len, const uint8_t *field_name,
                                                      int32_t field_len, uint8_t *out_name) {
  int32_t pos;
  int32_t pi;
  pos = 0;
  if (pre_len > 0 && !glue_asm_c_prefix_redundant_with_name(pre, pre_len, field_name, field_len)) {
    pi = 0;
    while (pi < pre_len && pos < 63) {
      out_name[pos++] = pre[pi++];
    }
  }
  pi = 0;
  while (pi < field_len && pos < 63)
    out_name[pos++] = field_name[pi++];
  return pos > 0 ? pos : -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_build_import_binding_call_sym(const uint8_t *pre, int32_t pre_len, const uint8_t *field_name,
                                                      int32_t field_len, uint8_t *out_name) {
  return glue_asm_build_import_binding_call_sym_impl(pre, pre_len, field_name, field_len, out_name);
}
#endif




/**
 * co-emit dep 模块时函数标签与同模块 call 须带 import 路径前缀（与 import 限定 call 一致）。
 * 无 dep 路径时返回裸函数名；成功返回符号字节长度，失败 -1。
 */
/* G-02f-144：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-373 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_build_dep_export_sym_c_impl(const uint8_t *name, int32_t name_len, uint8_t *out, int32_t out_cap) {
  const char *dep_path;
  uint8_t prefix[128];
  int32_t plen;
  int32_t pos;
  int32_t i;
  if (!name || name_len <= 0 || !out || out_cap <= 0)
    return -1;
  dep_path = driver_get_current_dep_path_for_codegen();
  pos = 0;
  if (dep_path && dep_path[0]) {
    glue_codegen_import_path_to_c_prefix_into((const uint8_t *)dep_path, prefix, 128);
    plen = 0;
    while (plen < 127 && prefix[plen])
      plen++;
    if (plen > 0 && !glue_asm_c_prefix_redundant_with_name(prefix, plen, name, name_len)) {
      /* wave580 Cap: fill out[0..out_cap) without reserved NUL (length-returned API). */
      for (i = 0; i < plen && pos < out_cap; i++)
        out[pos++] = prefix[i];
    }
  }
  /* wave580 Cap: allow full content cap 127 into out_cap 128 (was out_cap-1 → truncate 64→63). */
  for (i = 0; i < name_len && pos < out_cap; i++)
    out[pos++] = name[i];
  return pos > 0 ? pos : -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_build_dep_export_sym_c(const uint8_t *name, int32_t name_len, uint8_t *out, int32_t out_cap) {
  return glue_asm_build_dep_export_sym_c_impl(name, name_len, out, out_cap);
}
#endif

/** 将 TypeKind 序数写成 overload mangled 后缀（对齐 codegen.c type_to_suffix 标量子集）。 */
/* G-02f-121：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-372 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_type_kind_to_suffix_c_impl(int32_t kind_ord, uint8_t *out, int32_t out_cap) {
  /* PLATFORM: SHARED — scalar TypeKind → overload mid only.
   * TYPE_I32=0 is explicit (not a silent default). Unknown kinds (SLICE/ARRAY/…)
   * return 0 so callers use compound paths; never map u8[] → "i32" (run-io UNDEF
   * println_i32_reti32 false collision with println(u8[])). Align codegen_type_ref_to_suffix. */
  static const uint8_t lit_i32[3] = { 105, 51, 50 };
  static const uint8_t lit_i64[3] = { 105, 54, 52 };
  static const uint8_t lit_u8[2] = { 117, 56 };
  static const uint8_t lit_u32[3] = { 117, 51, 50 };
  static const uint8_t lit_u64[3] = { 117, 54, 52 };
  static const uint8_t lit_usize[5] = { 117, 115, 105, 122, 101 };
  static const uint8_t lit_isize[5] = { 105, 115, 105, 122, 101 };
  static const uint8_t lit_f32[3] = { 102, 51, 50 };
  static const uint8_t lit_f64[3] = { 102, 54, 52 };
  static const uint8_t lit_bool[4] = { 98, 111, 111, 108 };
  const uint8_t *src;
  int32_t slen;
  int32_t i;
  if (!out || out_cap <= 0)
    return 0;
  src = 0;
  slen = 0;
  if (kind_ord == 0) {
    /* TYPE_I32 */
    src = lit_i32;
    slen = 3;
  } else if (kind_ord == 5) {
    src = lit_i64;
    slen = 3;
  } else if (kind_ord == 2) {
    src = lit_u8;
    slen = 2;
  } else if (kind_ord == 3) {
    src = lit_u32;
    slen = 3;
  } else if (kind_ord == 4) {
    src = lit_u64;
    slen = 3;
  } else if (kind_ord == 6) {
    src = lit_usize;
    slen = 5;
  } else if (kind_ord == 7) {
    src = lit_isize;
    slen = 5;
  } else if (kind_ord == 14) {
    src = lit_f32;
    slen = 3;
  } else if (kind_ord == 15) {
    src = lit_f64;
    slen = 3;
  } else if (kind_ord == 1) {
    src = lit_bool;
    slen = 4;
  } else {
    return 0;
  }
  for (i = 0; i < slen && i < out_cap - 1; i++)
    out[i] = src[i];
  return slen;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_type_kind_to_suffix_c(int32_t kind_ord, uint8_t *out, int32_t out_cap) {
  return glue_type_kind_to_suffix_c_impl(kind_ord, out, out_cap);
}
#endif

/* Forward: overload mid / export builders need helpers before their definitions. */
int32_t glue_module_func_overload_count_c_impl(struct ast_Module *m, const uint8_t *name, int32_t name_len);
static int32_t glue_asm_overload_param_sig_count_c(struct ast_ASTArena *a, struct ast_Module *m, int32_t func_ix);
static struct ast_Module *glue_asm_res_mod_for_import_binding_c(struct ast_PipelineDepCtx *dp,
                                                                struct ast_Module *user_mod, int32_t imp_j,
                                                                int32_t r_dep, struct ast_ASTArena **out_arena,
                                                                struct ast_ASTArena *fallback_arena);
extern int32_t pipeline_expr_method_call_num_args_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);

extern int32_t pipeline_expr_unary_operand_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_index_base_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_as_target_type_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_type_find_or_alloc_compound(struct ast_ASTArena *a, int32_t kind_ord, int32_t elem_ref,
                                                     int32_t array_size);
extern int32_t pipeline_asm_call_expected_ret_ty_c(void);

/**
 * PLATFORM: SHARED — resolve arg type for import overload mangle.
 * Prefer expr.resolved_type; for VAR fall back to scope-block let type
 * (g_pipeline_asm_emit_scope_block path used by FIELD_ACCESS layout).
 * ADDR_OF(VAR|INDEX): *T from operand (push(&v) / sort(&b[0]) when resolved missing).
 * INDEX: array/slice/ptr elem type. AS: target type. G.7 single authority for asm arg types.
 */
static int32_t glue_asm_call_arg_type_ref_c(struct ast_ASTArena *arena, struct backend_AsmFuncCtx *ctx,
                                           int32_t arg_ref) {
  int32_t ty;
  int32_t ko;
  int32_t scope_br;
  uint8_t vname[128];
  int32_t vlen;
  if (!arena || arg_ref <= 0)
    return 0;
  ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
  if (ty > 0)
    return ty;
  ko = pipeline_expr_kind_ord_at(arena, arg_ref);
  /** `x as *T` / cast: use target type when typeck did not stick resolved_type. */
  if (ko == GLUE_EXPR_AS_ORD) {
    int32_t as_tgt = pipeline_expr_as_target_type_ref_at(arena, arg_ref);
    if (as_tgt > 0)
      return as_tgt;
    return 0;
  }
  /**
   * a[i]: recover elem type from base array/slice/ptr so &a[i] → *elem in ADDR_OF path.
   * Root residual: sort.sort(&b[0], n) asm bound i32 when INDEX resolved_type was 0.
   */
  if (ko == GLUE_EXPR_INDEX_ORD) {
    int32_t base_ref = pipeline_expr_index_base_ref(arena, arg_ref);
    int32_t base_ty;
    int32_t bk;
    int32_t elem;
    if (base_ref <= 0)
      return 0;
    base_ty = glue_asm_call_arg_type_ref_c(arena, ctx, base_ref);
    if (base_ty <= 0)
      base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (base_ty <= 0)
      return 0;
    bk = pipeline_type_kind_ord_at(arena, base_ty);
    if (bk != GLUE_TYPE_ARRAY_ORD && bk != GLUE_TYPE_SLICE_ORD && bk != GLUE_TYPE_PTR_ORD)
      return 0;
    elem = pipeline_type_elem_ref_at(arena, base_ty);
    return elem > 0 ? elem : 0;
  }
  /** &local / &a[i]: build *T so push(&v) / sort(&b[0]) score *u8 not first *i32. */
  if (ko == GLUE_EXPR_ADDR_OF_ORD) {
    int32_t op = pipeline_expr_unary_operand_ref_at(arena, arg_ref);
    int32_t elem;
    if (op <= 0)
      return 0;
    elem = glue_asm_call_arg_type_ref_c(arena, ctx, op);
    if (elem <= 0)
      return 0;
    return pipeline_type_find_or_alloc_compound(arena, GLUE_TYPE_PTR_ORD, elem, 0);
  }
  if (ko != GLUE_EXPR_VAR_ORD || !ctx) /* VAR */
    return 0;
  vlen = pipeline_expr_var_name_len(arena, arg_ref);
  if (vlen <= 0 || vlen > 63)
    return 0;
  pipeline_expr_var_name_into(arena, arg_ref, vname);
  scope_br = asm_ctx_scope_block_ref_at((uint8_t *)ctx);
  if (scope_br > 0) {
    ty = pipeline_block_resolve_var_type_ref(arena, scope_br, vname, vlen);
    if (ty > 0)
      return ty;
  }
  return 0;
}

/**
 * PLATFORM: SHARED — expected return for zero-arg import overload (vec.new).
 * Prefer typeck-resolved expr type; else let-init install (pipeline_asm_call_expected_ret_ty_c).
 */
static int32_t glue_asm_call_expected_ret_ty_c(struct ast_ASTArena *arena, int32_t expr_ref) {
  int32_t ty;
  if (arena && expr_ref > 0) {
    ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    if (ty > 0)
      return ty;
  }
  return pipeline_asm_call_expected_ret_ty_c();
}

/**
 * PLATFORM: SHARED — type_ref → overload mangle suffix (align codegen_type_ref_to_suffix).
 * PTR: elem + "_ptr"; SLICE: elem + "_slc" (u8[] → u8_slc; wave687/C twin);
 * ARRAY: elem + "_aN"; NAMED: type name ('.'→'_'); scalars: glue_type_kind_to_suffix.
 * Authority for asm call/export symbols that must match formal std .o
 * (std_fmt_println_i32 vs println_u8_slc — never collide via default-i32).
 * G.7: single mid authority with host-C codegen_type_ref_to_suffix.
 */
static int32_t glue_asm_type_ref_to_suffix_c(struct ast_ASTArena *a, int32_t type_ref, uint8_t *out,
                                            int32_t out_cap) {
  int32_t tk;
  int32_t n;
  int32_t si;
  if (!a || type_ref <= 0 || !out || out_cap <= 0)
    return 0;
  tk = pipeline_type_kind_ord_at(a, type_ref);
  /* TYPE_PTR = 9 */
  if (tk == 9) {
    int32_t elem = pipeline_type_elem_ref_at(a, type_ref);
    n = glue_asm_type_ref_to_suffix_c(a, elem, out, out_cap);
    if (n > 0 && n + 4 < out_cap) {
      out[n] = (uint8_t)'_';
      out[n + 1] = (uint8_t)'p';
      out[n + 2] = (uint8_t)'t';
      out[n + 3] = (uint8_t)'r';
      return n + 4;
    }
    return n;
  }
  /* TYPE_SLICE = 11 → <elem>_slc (std_fmt_println_u8_slc). */
  if (tk == 11) {
    int32_t elem = pipeline_type_elem_ref_at(a, type_ref);
    n = glue_asm_type_ref_to_suffix_c(a, elem, out, out_cap);
    if (n > 0 && n + 4 < out_cap) {
      out[n] = (uint8_t)'_';
      out[n + 1] = (uint8_t)'s';
      out[n + 2] = (uint8_t)'l';
      out[n + 3] = (uint8_t)'c';
      return n + 4;
    }
    return 0;
  }
  /* TYPE_ARRAY = 10 → <elem>_aN (align codegen wave687). */
  if (tk == 10) {
    int32_t elem = pipeline_type_elem_ref_at(a, type_ref);
    int32_t asz = pipeline_type_array_size_at(a, type_ref);
    int32_t digs[8];
    int32_t nd;
    int32_t v;
    int32_t di;
    n = glue_asm_type_ref_to_suffix_c(a, elem, out, out_cap);
    if (n <= 0 || asz <= 0)
      return 0;
    if (n + 2 >= out_cap)
      return 0;
    out[n] = (uint8_t)'_';
    out[n + 1] = (uint8_t)'a';
    n += 2;
    nd = 0;
    v = asz;
    while (v > 0 && nd < 6) {
      digs[nd++] = v % 10;
      v /= 10;
    }
    if (nd <= 0 || n + nd >= out_cap)
      return 0;
    for (di = nd - 1; di >= 0; di--)
      out[n++] = (uint8_t)('0' + digs[di]);
    return n;
  }
  /* TYPE_VECTOR = 13 → <elem>x<lanes> (f32x4 / i32x8). G.7 ≡ codegen + pure .x.
   * P0 soft: run-perf-simd-xlangffle-select UNDEF short mid without vector suffix. */
  if (tk == 13) {
    int32_t elem = pipeline_type_elem_ref_at(a, type_ref);
    int32_t lanes = pipeline_type_array_size_at(a, type_ref);
    int32_t ek;
    int32_t pos = 0;
    if (elem <= 0 || lanes <= 0)
      return 0;
    ek = pipeline_type_kind_ord_at(a, elem);
    if (ek == 0) { /* i32 */
      if (out_cap < 4)
        return 0;
      out[0] = (uint8_t)'i';
      out[1] = (uint8_t)'3';
      out[2] = (uint8_t)'2';
      pos = 3;
    } else if (ek == 3) { /* u32 */
      if (out_cap < 4)
        return 0;
      out[0] = (uint8_t)'u';
      out[1] = (uint8_t)'3';
      out[2] = (uint8_t)'2';
      pos = 3;
    } else if (ek == 14) { /* f32 */
      if (out_cap < 4)
        return 0;
      out[0] = (uint8_t)'f';
      out[1] = (uint8_t)'3';
      out[2] = (uint8_t)'2';
      pos = 3;
    } else {
      return 0;
    }
    if (pos >= out_cap)
      return 0;
    out[pos++] = (uint8_t)'x';
    if (lanes == 4) {
      if (pos >= out_cap)
        return 0;
      out[pos++] = (uint8_t)'4';
      return pos;
    }
    if (lanes == 8) {
      if (pos >= out_cap)
        return 0;
      out[pos++] = (uint8_t)'8';
      return pos;
    }
    if (lanes == 16) {
      if (pos + 1 >= out_cap)
        return 0;
      out[pos++] = (uint8_t)'1';
      out[pos++] = (uint8_t)'6';
      return pos;
    }
    return 0;
  }
  /* Named / user types: always try type name (String, Vec_u8, …). */
  n = pipeline_type_named_name_into(a, type_ref, out);
  if (n > 0 && n < out_cap) {
    for (si = 0; si < n && si < out_cap; si++) {
      if (out[si] == (uint8_t)'.')
        out[si] = (uint8_t)'_';
    }
    return n;
  }
  return glue_type_kind_to_suffix_c(tk, out, out_cap);
}

/**
 * PLATFORM: SHARED — overload mid name only (no module / current_dep path).
 * Aligns codegen_emit_func_link_name: bare when overload_count<=1; else name_t1_t2[_ret_T].
 * CALL-site authority must NOT use glue_asm_build_dep_export_sym_c (that prefixes the
 * *user* current_dep_path, not std.string → wrong mid or 64-byte overflow → bare).
 * G.7: single mid builder for import-binding mangle.
 */
static int32_t glue_asm_build_func_overload_mid_c(struct ast_Module *m, struct ast_ASTArena *a, int32_t func_ix,
                                                   uint8_t *out, int32_t out_cap) {
  uint8_t fname[128];
  int32_t fname_len;
  int32_t pos;
  int32_t np;
  int32_t pi;
  int32_t pty;
  int32_t sl;
  int32_t sig_count;
  uint8_t suf[128];
  if (!m || !a || func_ix < 0 || !out || out_cap <= 0)
    return -1;
  fname_len = pipeline_asm_module_func_name_len_at(m, func_ix);
  if (fname_len <= 0 || fname_len >= out_cap || fname_len > 127)
    return -1;
  pipeline_asm_module_func_name_copy64(m, func_ix, fname);
  memcpy(out, fname, (size_t)fname_len);
  pos = fname_len;
  /* Use _impl: mid builder lives in seed rest (may compile under THIN_FROM_X). */
  if (glue_module_func_overload_count_c_impl(m, fname, fname_len) <= 1)
    return pos;
  np = pipeline_module_func_num_params_at(m, func_ix);
  for (pi = 0; pi < np && pos < out_cap - 2; pi++) {
    pty = pipeline_module_func_param_type_ref_at(m, func_ix, pi);
    if (pty <= 0)
      continue;
    sl = glue_asm_type_ref_to_suffix_c(a, pty, suf, 64);
    if (sl <= 0)
      continue;
    if (pos + 1 + sl >= out_cap)
      return -1;
    out[pos++] = (uint8_t)'_';
    memcpy(out + pos, suf, (size_t)sl);
    pos += sl;
  }
  sig_count = glue_asm_overload_param_sig_count_c(a, m, func_ix);
  if (sig_count > 1) {
    int32_t ret_ref = pipeline_module_func_return_type_at(m, func_ix);
    int32_t rsl = ret_ref > 0 ? glue_asm_type_ref_to_suffix_c(a, ret_ref, suf, 64) : 0;
    if (rsl > 0) {
      if (pos + 4 + rsl >= out_cap)
        return -1;
      out[pos++] = (uint8_t)'_';
      out[pos++] = (uint8_t)'r';
      out[pos++] = (uint8_t)'e';
      out[pos++] = (uint8_t)'t';
      memcpy(out + pos, suf, (size_t)rsl);
      pos += rsl;
    }
  }
  return pos > 0 ? pos : -1;
}

/**
 * PLATFORM: SHARED — score field_name candidates in res_mod (want_np + arg/ret mid).
 * Returns best func_ix or -1. Used by import-binding formal mid path (G.7 one authority).
 * best_score_out: optional; 1=name+arity only, +10/arg match, +20 zero-arg ret. Override r_func
 * only when score >= 11 (typed arg evidence) so bare residual does not clobber correct resolve.
 * ARRAY T vs *T is a +10 hit (≡ typeck_overload_arg_param_score ak==10 && pk==9) so
 * from_slice(u64[4], n) beats first-wins from_slice_i32. FLOAT_LIT splat stays score==1.
 */
static int32_t glue_asm_score_import_binding_func_ix_ex_c(struct ast_ASTArena *arena,
                                                           struct backend_AsmFuncCtx *ctx, int32_t expr_ref,
                                                           struct ast_Module *res_mod,
                                                           struct ast_ASTArena *res_arena,
                                                           const uint8_t *field_name, int32_t field_len,
                                                           int32_t want_np, int32_t is_method,
                                                           int32_t *best_score_out) {
  int32_t fi;
  int32_t exp_ty;
  int32_t best;
  int32_t best_score;
  if (best_score_out)
    *best_score_out = -1;
  if (!arena || !res_mod || !field_name || field_len <= 0)
    return -1;
  if (!res_arena)
    res_arena = arena;
  exp_ty = glue_asm_call_expected_ret_ty_c(arena, expr_ref);
  best = -1;
  best_score = -1;
  for (fi = 0; fi < pipeline_module_num_funcs(res_mod); fi++) {
    int32_t np;
    int32_t score;
    int32_t pi;
    if (pipeline_asm_module_func_is_extern_at(res_mod, fi) != 0)
      continue;
    if (!pipeline_module_func_name_equal_at(res_mod, fi, (uint8_t *)field_name, field_len))
      continue;
    np = pipeline_module_func_num_params_at(res_mod, fi);
    if (np != want_np)
      continue;
    score = 1;
    for (pi = 0; pi < np && pi < 8; pi++) {
      int32_t arg_ref = is_method ? pipeline_expr_method_call_arg_ref(arena, expr_ref, pi)
                                 : pipeline_expr_call_arg_ref(arena, expr_ref, pi);
      int32_t arg_ty = glue_asm_call_arg_type_ref_c(arena, ctx, arg_ref);
      int32_t pty = pipeline_module_func_param_type_ref_at(res_mod, fi, pi);
      uint8_t sa[128];
      uint8_t sb[128];
      int32_t na;
      int32_t nb;
      int32_t k;
      if (arg_ty <= 0 || pty <= 0)
        continue;
      na = glue_asm_type_ref_to_suffix_c(arena, arg_ty, sa, 64);
      nb = glue_asm_type_ref_to_suffix_c(res_arena, pty, sb, 64);
      if (na > 0 && na == nb) {
        int32_t eq = 1;
        for (k = 0; k < na; k++) {
          if (sa[k] != sb[k]) {
            eq = 0;
            break;
          }
        }
        if (eq)
          score += 10;
      } else if (na > 0 && nb > 0) {
        /* PLATFORM: SHARED — ARRAY T → *T decay ≡ typeck ak==10 pk==9.
         * Product -o mangle: from_slice(src: u64[4], n) must pick from_slice_u64_ptr
         * not first-name from_slice_i32 (score==1 cannot pass sc_best>=11). */
        int32_t ak = pipeline_type_kind_ord_at(arena, arg_ty);
        int32_t pk = pipeline_type_kind_ord_at(res_arena, pty);
        if (ak == 10 && pk == 9) {
          int32_t ae = pipeline_type_elem_ref_at(arena, arg_ty);
          int32_t pe = pipeline_type_elem_ref_at(res_arena, pty);
          if (ae > 0 && pe > 0) {
            uint8_t sea[64];
            uint8_t seb[64];
            int32_t nea = glue_asm_type_ref_to_suffix_c(arena, ae, sea, 64);
            int32_t neb = glue_asm_type_ref_to_suffix_c(res_arena, pe, seb, 64);
            if (nea > 0 && nea == neb) {
              int32_t eqe = 1;
              int32_t ke;
              for (ke = 0; ke < nea; ke++) {
                if (sea[ke] != seb[ke]) {
                  eqe = 0;
                  break;
                }
              }
              if (eqe)
                score += 10;
            }
          }
        }
      }
    }
    if (want_np == 0 && exp_ty > 0) {
      int32_t rty = pipeline_module_func_return_type_at(res_mod, fi);
      uint8_t sa[128];
      uint8_t sb[128];
      int32_t na = glue_asm_type_ref_to_suffix_c(arena, exp_ty, sa, 64);
      int32_t nb = rty > 0 ? glue_asm_type_ref_to_suffix_c(res_arena, rty, sb, 64) : 0;
      int32_t k;
      if (na > 0 && na == nb) {
        int32_t eq = 1;
        for (k = 0; k < na; k++) {
          if (sa[k] != sb[k]) {
            eq = 0;
            break;
          }
        }
        if (eq)
          score += 20;
      } else if (na > 0 && nb > 0) {
        /** Last-segment NAMED only on '.': bare vs module-qualified (not '_' — Vec_u8). */
        int32_t sa0 = 0, sb0 = 0, i2;
        for (i2 = 0; i2 < na; i2++)
          if (sa[i2] == (uint8_t)'.')
            sa0 = i2 + 1;
        for (i2 = 0; i2 < nb; i2++)
          if (sb[i2] == (uint8_t)'.')
            sb0 = i2 + 1;
        if ((sa0 > 0 || sb0 > 0) && (na - sa0) == (nb - sb0) && (na - sa0) > 0) {
          int32_t eq = 1;
          for (i2 = 0; i2 < na - sa0; i2++) {
            if (sa[sa0 + i2] != sb[sb0 + i2]) {
              eq = 0;
              break;
            }
          }
          if (eq)
            score += 20;
        }
      }
    }
    if (score > best_score) {
      best_score = score;
      best = fi;
    }
  }
  if (best_score_out)
    *best_score_out = best_score;
  return best;
}

static int32_t glue_asm_score_import_binding_func_ix_c(struct ast_ASTArena *arena,
                                                        struct backend_AsmFuncCtx *ctx, int32_t expr_ref,
                                                        struct ast_Module *res_mod, struct ast_ASTArena *res_arena,
                                                        const uint8_t *field_name, int32_t field_len,
                                                        int32_t want_np, int32_t is_method) {
  return glue_asm_score_import_binding_func_ix_ex_c(arena, ctx, expr_ref, res_mod, res_arena, field_name,
                                                    field_len, want_np, is_method, 0);
}

/**
 * PLATFORM: SHARED — G.7 single authority for import-binding CALL/METHOD_CALL mangle.
 * Builds pre+mid into sym_flat. is_method: 0=EXPR_CALL arg refs; 1=METHOD_CALL arg refs.
 * Formal param mid (path-matched res_mod + func_ix) first.
 * Recovery: bad typeck r_dep → path match → scan all deps (freestanding co-emit heap/page_mmap).
 * Caller-suffix only when formal found an *overloaded* name; unique → bare field (export mid).
 * Returns symbol length or -1.
 */
static int32_t glue_asm_mangle_import_binding_call_sym_c(struct ast_ASTArena *arena,
                                                          struct backend_AsmFuncCtx *ctx, int32_t expr_ref,
                                                          struct glue_AsmFuncCtxCall *ly, struct ast_Module *mod_ref,
                                                          int32_t imp_j, const uint8_t *pre_buf, int32_t pre_len,
                                                          const uint8_t *field_name, int32_t field_len,
                                                          int32_t is_method, uint8_t *sym_flat) {
  int32_t r_func;
  int32_t r_dep;
  struct ast_PipelineDepCtx *dp;
  uint8_t mid[128];
  int32_t mid_len;
  int32_t sym_len;
  int32_t want_np;
  int32_t formal_overloads;
  struct ast_ASTArena *res_arena;
  struct ast_Module *res_mod;
  int32_t use_fi;
  if (!arena || !mod_ref || !pre_buf || pre_len <= 0 || !field_name || field_len <= 0 || !sym_flat)
    return -1;
  r_func = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
  r_dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
  dp = pipeline_asm_emit_dep_pipe_c();
  mid_len = -1;
  sym_len = -1;
  formal_overloads = 0;
  res_arena = arena;
  res_mod = 0;
  use_fi = -1;
  if (!dp && ly && ly->dep_pipe)
    dp = (struct ast_PipelineDepCtx *)ly->dep_pipe;
  want_np = is_method ? pipeline_expr_method_call_num_args_at(arena, expr_ref)
                      : pipeline_expr_call_num_args_at(arena, expr_ref);
  if (dp) {
    int32_t attempt;
    /**
     * Three recoveries for freestanding multi-dep co-emit:
     *  0) typeck r_dep (when valid)
     *  1) import-path match (ignore wrong r_dep — typeck residual)
     *  2) scan all deps for field_name+want_np
     */
    for (attempt = 0; attempt < 3 && use_fi < 0; attempt++) {
      if (attempt == 0) {
        res_arena = arena;
        res_mod = glue_asm_res_mod_for_import_binding_c(dp, mod_ref, imp_j, r_dep, &res_arena, arena);
      } else if (attempt == 1) {
        res_arena = arena;
        res_mod = glue_asm_res_mod_for_import_binding_c(dp, mod_ref, imp_j, -1, &res_arena, arena);
      } else {
        int32_t nd = pipeline_dep_ctx_ndep(dp);
        int32_t di;
        int32_t best_global = -1;
        int32_t best_hits = 0;
        struct ast_Module *best_mod = 0;
        struct ast_ASTArena *best_arena = arena;
        res_mod = 0;
        res_arena = arena;
        for (di = 0; di < nd; di++) {
          struct ast_Module *rm = pipeline_dep_ctx_module_at(dp, di);
          struct ast_ASTArena *ra = pipeline_dep_ctx_arena_at(dp, di);
          int32_t cand;
          if (!rm)
            continue;
          if (!ra)
            ra = arena;
          cand = glue_asm_score_import_binding_func_ix_c(arena, ctx, expr_ref, rm, ra, field_name, field_len,
                                                        want_np, is_method);
          if (cand < 0)
            continue;
          best_hits++;
          if (best_global < 0) {
            best_global = cand;
            best_mod = rm;
            best_arena = ra;
          }
        }
        /* Prefer unique dep hit; multi-hit still take first (stable) rather than invent mid. */
        if (best_global >= 0 && best_mod) {
          res_mod = best_mod;
          res_arena = best_arena;
          use_fi = best_global;
          (void)best_hits;
        }
        break;
      }
      if (!res_mod)
        continue;
      use_fi = r_func;
      if (use_fi >= 0 && use_fi < pipeline_module_num_funcs(res_mod)) {
        int32_t ok = 1;
        if (pipeline_module_func_num_params_at(res_mod, use_fi) != want_np)
          ok = 0;
        else if (!pipeline_module_func_name_equal_at(res_mod, use_fi, (uint8_t *)field_name, field_len))
          ok = 0;
        if (!ok)
          use_fi = -1;
      } else {
        use_fi = -1;
      }
      if (use_fi < 0)
        use_fi = glue_asm_score_import_binding_func_ix_c(arena, ctx, expr_ref, res_mod, res_arena, field_name,
                                                        field_len, want_np, is_method);
      /*
       * PLATFORM: SHARED — overloaded names: re-score when arg types give evidence (score>=11).
       * typeck may leave first-name residual for ADDR_OF(INDEX) while C re-scores via suffix;
       * asm must re-score with INDEX/AS recovery (sort *u8). Do not override on score==1 only.
       * G.7: complete same mangle authority.
       */
      if (use_fi >= 0 && res_mod &&
          glue_module_func_overload_count_c_impl(res_mod, (uint8_t *)field_name, field_len) > 1) {
        int32_t sc_best = -1;
        int32_t scored = glue_asm_score_import_binding_func_ix_ex_c(
            arena, ctx, expr_ref, res_mod, res_arena, field_name, field_len, want_np, is_method, &sc_best);
        if (scored >= 0 && sc_best >= 11)
          use_fi = scored;
      }
    }
    if (res_mod && use_fi >= 0 && use_fi < pipeline_module_num_funcs(res_mod)) {
      formal_overloads = glue_module_func_overload_count_c_impl(res_mod, (uint8_t *)field_name, field_len);
      mid_len = glue_asm_build_func_overload_mid_c(res_mod, res_arena, use_fi, mid, 64);
      if (mid_len > 0) {
        /* Bare mid (unique name) is intentional formal link name — do not caller-suffix. */
        sym_len = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, mid, mid_len, sym_flat);
        if (sym_len <= 0)
          mid_len = -1;
      }
    }
  }
  /**
   * Caller-arena arg/ret mid only when formal path failed AND the name is overloaded.
   * Unique names: bare field matches co-emit/export mid (heap_alloc_c, page_mmap_heap_*).
   * Prior path always caller-suffixed on formal miss → std_heap_libc_heap_free_c_u8_ptr UNDEF
   * while T std_heap_libc_heap_free_c (unique export).
   */
  if (sym_len <= 0 && formal_overloads > 1) {
    int32_t n_args = want_np;
    int32_t pos;
    int32_t pi;
    int32_t alen = 0;
    if (field_len > 0 && field_len < 64) {
      memcpy(mid, field_name, (size_t)field_len);
      alen = field_len;
    }
    for (pi = 0; pi < n_args && alen < 60; pi++) {
      int32_t arg_ref = is_method ? pipeline_expr_method_call_arg_ref(arena, expr_ref, pi)
                                 : pipeline_expr_call_arg_ref(arena, expr_ref, pi);
      int32_t arg_ty = glue_asm_call_arg_type_ref_c(arena, ctx, arg_ref);
      uint8_t suf[128];
      int32_t sl = arg_ty > 0 ? glue_asm_type_ref_to_suffix_c(arena, arg_ty, suf, 64) : 0;
      if (sl <= 0)
        continue;
      if (alen + 1 + sl >= 64)
        break;
      mid[alen++] = (uint8_t)'_';
      memcpy(mid + alen, suf, (size_t)sl);
      alen += sl;
    }
    if (n_args == 0) {
      int32_t exp_ty = glue_asm_call_expected_ret_ty_c(arena, expr_ref);
      uint8_t suf[128];
      int32_t sl = exp_ty > 0 ? glue_asm_type_ref_to_suffix_c(arena, exp_ty, suf, 64) : 0;
      if (sl > 0 && alen + 4 + sl < 64) {
        mid[alen++] = (uint8_t)'_';
        mid[alen++] = (uint8_t)'r';
        mid[alen++] = (uint8_t)'e';
        mid[alen++] = (uint8_t)'t';
        memcpy(mid + alen, suf, (size_t)sl);
        alen += sl;
      }
    }
    if (alen > field_len) {
      pos = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, mid, alen, sym_flat);
      if (pos > 0)
        sym_len = pos;
    }
  }
  if (sym_len <= 0)
    sym_len = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, field_name, field_len, sym_flat);
  return sym_len;
}

/**
 * PLATFORM: SHARED — resolve dep module for import-binding CALL.
 * Prefer typeck dep_ix; else match dep import_path to user import j (not index j==dep_ix).
 */
static struct ast_Module *glue_asm_res_mod_for_import_binding_c(struct ast_PipelineDepCtx *dp,
                                                                struct ast_Module *user_mod, int32_t imp_j,
                                                                int32_t r_dep, struct ast_ASTArena **out_arena,
                                                                struct ast_ASTArena *fallback_arena) {
  int32_t nd;
  int32_t iplen;
  int32_t di;
  if (out_arena)
    *out_arena = fallback_arena;
  if (!dp)
    return 0;
  nd = pipeline_dep_ctx_ndep(dp);
  if (r_dep >= 0 && r_dep < nd) {
    struct ast_Module *rm = pipeline_dep_ctx_module_at(dp, r_dep);
    struct ast_ASTArena *ra = pipeline_dep_ctx_arena_at(dp, r_dep);
    if (out_arena && ra)
      *out_arena = ra;
    return rm;
  }
  if (!user_mod || imp_j < 0)
    return 0;
  iplen = pipeline_module_import_path_len(user_mod, imp_j);
  if (iplen <= 0 || iplen > 63)
    return 0;
  for (di = 0; di < nd; di++) {
    uint8_t dpath[128];
    int32_t dplen;
    int32_t k;
    int32_t eq;
    dplen = pipeline_dep_ctx_import_path_len(dp, di);
    if (dplen != iplen)
      continue;
    pipeline_dep_ctx_import_path_copy64(dp, di, dpath);
    eq = 1;
    for (k = 0; k < iplen; k++) {
      if (dpath[k] != pipeline_module_import_path_byte_at(user_mod, imp_j, k)) {
        eq = 0;
        break;
      }
    }
    if (eq) {
      struct ast_Module *rm = pipeline_dep_ctx_module_at(dp, di);
      struct ast_ASTArena *ra = pipeline_dep_ctx_arena_at(dp, di);
      if (out_arena && ra)
        *out_arena = ra;
      return rm;
    }
  }
  return 0;
}

/** Count overloads that share the same param-type suffix signature as func_ix (for _ret_ mangle). */
static int32_t glue_asm_overload_param_sig_count_c(struct ast_ASTArena *a, struct ast_Module *m, int32_t func_ix) {
  uint8_t fname[128];
  int32_t fname_len;
  int32_t np0;
  int32_t i;
  int32_t c;
  if (!a || !m || func_ix < 0)
    return 0;
  fname_len = pipeline_asm_module_func_name_len_at(m, func_ix);
  if (fname_len <= 0 || fname_len > 127)
    return 0;
  pipeline_asm_module_func_name_copy64(m, func_ix, fname);
  np0 = pipeline_module_func_num_params_at(m, func_ix);
  c = 0;
  for (i = 0; i < pipeline_module_num_funcs(m); i++) {
    int32_t npi;
    int32_t pi;
    int32_t same;
    if (pipeline_asm_module_func_is_extern_at(m, i) != 0)
      continue;
    if (!pipeline_module_func_name_equal_at(m, i, fname, fname_len))
      continue;
    npi = pipeline_module_func_num_params_at(m, i);
    if (npi != np0)
      continue;
    same = 1;
    for (pi = 0; pi < np0; pi++) {
      uint8_t sa[128];
      uint8_t sb[128];
      int32_t na;
      int32_t nb;
      int32_t k;
      na = glue_asm_type_ref_to_suffix_c(a, pipeline_module_func_param_type_ref_at(m, func_ix, pi), sa, 64);
      nb = glue_asm_type_ref_to_suffix_c(a, pipeline_module_func_param_type_ref_at(m, i, pi), sb, 64);
      if (na != nb) {
        same = 0;
        break;
      }
      for (k = 0; k < na; k++) {
        if (sa[k] != sb[k]) {
          same = 0;
          break;
        }
      }
      if (!same)
        break;
    }
    if (same)
      c++;
  }
  return c;
}

/** 统计模块内同名函数个数（>1 时 emit/call 须 mangled 符号）。 */
/* G-02f-134：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-370 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_module_func_overload_count_c_impl(struct ast_Module *m, const uint8_t *name, int32_t name_len) {
  int32_t i;
  int32_t c;
  if (!m || !name || name_len <= 0)
    return 0;
  c = 0;
  for (i = 0; i < pipeline_module_num_funcs(m); i++) {
    if (pipeline_asm_module_func_is_extern_at(m, i) != 0)
      continue;
    if (pipeline_module_func_name_equal_at(m, i, (uint8_t *)name, name_len))
      c++;
  }
  return c;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_module_func_overload_count_c(struct ast_Module *m, const uint8_t *name, int32_t name_len) {
  return glue_module_func_overload_count_c_impl(m, name, name_len);
}
#endif


/**
 * net_/fs_ 模块函数定义符号与 pipeline_asm_redirect_std_c_wrapper_sym 一致：补 _c 后缀。
 * 调用侧 net_foo → net_foo_c；定义侧须同名，否则 net.o ld -r 合并后内部 U 符号无法解析。
 */
/* G-02f-120：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-370 call：实现体始终 seed；public PREFER 时 thin forward（-E 丢 pure 嵌套） */
int32_t glue_asm_std_c_wrapper_fname_needs_export_c_suffix_impl(const uint8_t *fname, int32_t fname_len) {
  if (!fname || fname_len <= 0)
    return 0;
  if (fname_len >= 2 && fname[fname_len - 2] == '_' && fname[fname_len - 1] == 'c')
    return 0;
  if (fname_len >= 4 && memcmp(fname, "net_", 4) == 0)
    return 1;
  if (fname_len >= 3 && memcmp(fname, "fs_", 3) == 0)
    return 1;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_std_c_wrapper_fname_needs_export_c_suffix(const uint8_t *fname, int32_t fname_len) {
  return glue_asm_std_c_wrapper_fname_needs_export_c_suffix_impl(fname, fname_len);
}
#endif




/** 在 sym[sym_len] 处追加 _c；空间不足则返回原 sym_len。 */
/* G-02f-120：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_append_export_c_suffix(uint8_t *sym, int32_t sym_len, int32_t cap) {
  if (!sym || sym_len <= 0 || sym_len + 2 >= cap)
    return sym_len;
  sym[sym_len] = '_';
  sym[sym_len + 1] = 'c';
  return sym_len + 2;
}
#endif




/**
 * 函数定义/ CALL 导出符号：无 overload 时用裸名+dep 前缀；有 overload 时用 name_t1_t2（如 pick_i32）。
 * PLATFORM: SHARED — G.7 complete authority: named/ptr suffixes + _ret_ when param-sig collides
 * (align codegen_emit_func_link_name). string.length → len_String; vec.new → new_retVec_u8.
 */
/* G-02f-144：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-374 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_build_func_export_sym_c_impl(struct ast_Module *m, struct ast_ASTArena *a, int32_t func_ix,
                                         uint8_t *out, int32_t out_cap) {
  uint8_t fname[128];
  int32_t fname_len;
  int32_t pos;
  int32_t np;
  int32_t pi;
  int32_t pty;
  int32_t sl;
  int32_t sig_count;
  uint8_t suf[128];
  if (!m || !a || func_ix < 0 || !out || out_cap <= 0)
    return -1;
  fname_len = pipeline_asm_module_func_name_len_at(m, func_ix);
  if (fname_len <= 0 || fname_len > 127)
    return -1;
  pipeline_asm_module_func_name_copy64(m, func_ix, fname);
  if (glue_module_func_overload_count_c(m, fname, fname_len) <= 1) {
    pos = glue_asm_build_dep_export_sym_c(fname, fname_len, out, out_cap);
    if (pos <= 0)
      return -1;
    if (glue_asm_std_c_wrapper_fname_needs_export_c_suffix(fname, fname_len))
      pos = glue_asm_append_export_c_suffix(out, pos, out_cap);
    return pos > 0 ? pos : -1;
  }
  pos = glue_asm_build_dep_export_sym_c(fname, fname_len, out, out_cap);
  if (pos <= 0)
    return -1;
  np = pipeline_module_func_num_params_at(m, func_ix);
  for (pi = 0; pi < np && pos < out_cap - 2; pi++) {
    pty = pipeline_module_func_param_type_ref_at(m, func_ix, pi);
    if (pty <= 0)
      continue;
    sl = glue_asm_type_ref_to_suffix_c(a, pty, suf, 64);
    if (sl <= 0)
      continue;
    if (pos < out_cap - 1)
      out[pos++] = (uint8_t)'_';
    if (pos + sl >= out_cap)
      return -1;
    memcpy(out + pos, suf, (size_t)sl);
    pos += sl;
  }
  /* Same param-sig overloads: append _ret_<T> (e.g. new_retVec_u8). */
  sig_count = glue_asm_overload_param_sig_count_c(a, m, func_ix);
  if (sig_count > 1) {
    int32_t ret_ref = pipeline_module_func_return_type_at(m, func_ix);
    int32_t rsl = glue_asm_type_ref_to_suffix_c(a, ret_ref, suf, 64);
    if (rsl > 0) {
      if (pos + 4 + rsl >= out_cap)
        return -1;
      out[pos++] = (uint8_t)'_';
      out[pos++] = (uint8_t)'r';
      out[pos++] = (uint8_t)'e';
      out[pos++] = (uint8_t)'t';
      memcpy(out + pos, suf, (size_t)rsl);
      pos += rsl;
    }
  }
  if (glue_asm_std_c_wrapper_fname_needs_export_c_suffix(fname, fname_len))
    pos = glue_asm_append_export_c_suffix(out, pos, out_cap);
  return pos > 0 ? pos : -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_build_func_export_sym_c(struct ast_Module *m, struct ast_ASTArena *a, int32_t func_ix,
                                         uint8_t *out, int32_t out_cap) {
  return glue_asm_build_func_export_sym_c_impl(m, a, func_ix, out, out_cap);
}
#endif

/** import 路径缓冲区中 '.' 分段数。 */
/* G-02f-120：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-368：循环体始终在 seed；public 符号 PREFER 时由 thin forward */
int32_t glue_asm_import_path_segment_count_impl(const uint8_t *path, int32_t path_len) {
  int32_t n;
  int32_t ii;
  if (!path || path_len <= 0)
    return 0;
  n = 1;
  for (ii = 0; ii < path_len; ii++) {
    if (path[ii] == 46)
      n++;
  }
  return n;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_import_path_segment_count(const uint8_t *path, int32_t path_len) {
  return glue_asm_import_path_segment_count_impl(path, path_len);
}
#endif




/** 比较 module import 路径切片与外部字节序列是否相等。 */
/* G-02f-121：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-369 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_import_path_slice_equal_impl(struct ast_Module *module, int32_t imp_ix, int32_t off, int32_t seg_len, const uint8_t *nm, int32_t nm_len) {
  int32_t i;
  if (seg_len != nm_len || seg_len <= 0)
    return 0;
  for (i = 0; i < seg_len; i++) {
    if (pipeline_module_import_path_byte_at(module, imp_ix, off + i) != nm[i])
      return 0;
  }
  return 1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_import_path_slice_equal(struct ast_Module *module, int32_t imp_ix, int32_t off, int32_t seg_len, const uint8_t *nm, int32_t nm_len) {
  return glue_asm_import_path_slice_equal_impl(module, imp_ix, off, seg_len, nm, nm_len);
}
#endif




/** 比较 import 绑定名与外部字节序列是否相等。 */
/* G-02f-121：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-369 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_import_binding_name_equal_impl(struct ast_Module *module, int32_t imp_ix, const uint8_t *nm, int32_t nm_len) {
  int32_t bl;
  int32_t i;
  bl = pipeline_module_import_binding_name_len(module, imp_ix);
  if (bl != nm_len || nm_len <= 0)
    return 0;
  for (i = 0; i < nm_len; i++) {
    if (pipeline_module_import_binding_name_byte_at(module, imp_ix, i) != nm[i])
      return 0;
  }
  return 1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_import_binding_name_equal(struct ast_Module *module, int32_t imp_ix, const uint8_t *nm, int32_t nm_len) {
  return glue_asm_import_binding_name_equal_impl(module, imp_ix, nm, nm_len);
}
#endif




/** pipeline_module_import_path 内第 want_seg 段起点偏移与长度。 */
/* G-02f-134：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-371 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_import_segment_at_impl(struct ast_Module *module, int32_t imp_ix, int32_t want_seg, int32_t *ostr,
                                          int32_t *olen) {
  int32_t pl;
  int32_t ci;
  int32_t ss;
  int32_t k;
  if (!module || imp_ix < 0 || imp_ix >= parser_get_module_num_imports(module))
    return 0;
  pl = pipeline_module_import_path_len(module, imp_ix);
  if (pl <= 0 || pl > 63)
    return 0;
  ci = 0;
  ss = 0;
  for (k = 0; k <= pl; k++) {
    int32_t at_end = (k == pl);
    int32_t dot = (!at_end && k < pl && pipeline_module_import_path_byte_at(module, imp_ix, k) == 46);
    if (at_end || dot) {
      int32_t seg_len_here = k - ss;
      if (seg_len_here <= 0)
        return 0;
      if (ci == want_seg) {
        *ostr = ss;
        *olen = seg_len_here;
        return 1;
      }
      if (dot)
        ss = k + 1;
      ci++;
    }
  }
  return 0;

}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_import_segment_at(struct ast_Module *module, int32_t imp_ix, int32_t want_seg, int32_t *ostr,
                                          int32_t *olen) {
  return glue_asm_import_segment_at_impl(module, imp_ix, want_seg, ostr, olen);
}
#endif


/** 将 module 第 imp_ix 槽 import 逻辑路径转成 C ABI 前缀；成功返回前缀字节长度。 */
/* G-02f-133：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-370 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_fill_c_prefix_from_module_import_impl(struct ast_Module *cur_mod, int32_t imp_ix, uint8_t *pre_buf) {
  uint8_t path_bytes[128];
  int32_t pre_len;
  parser_get_module_import_path(cur_mod, imp_ix, path_bytes);
  if (path_bytes[0] == 0)
    return -1;
  glue_codegen_import_path_to_c_prefix_into(path_bytes, pre_buf, 128);
  pre_len = 0;
  while (pre_len < 128 && pre_buf[pre_len] != 0)
    pre_len++;
  return pre_len > 0 ? pre_len : -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_fill_c_prefix_from_module_import(struct ast_Module *cur_mod, int32_t imp_ix, uint8_t *pre_buf) {
  return glue_asm_fill_c_prefix_from_module_import_impl(cur_mod, imp_ix, pre_buf);
}
#endif


/**
 * `import a.b…` + `a.b….method(args)` 形式解析 C ABI 符号；成功写 sym_flat 并返回长度。
 * pipe 参数保留兼容，查找一律基于 cur_mod->imports。
 */
/* G-02f-147：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-375 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t pipeline_asm_resolve_whole_import_qualified_symbol_c_impl(struct ast_ASTArena *arena, struct ast_Module *cur_mod,
                                                              int32_t callee_expr_ref, uint8_t *sym_flat,
                                                              int32_t *out_match_imp_j) {
  int32_t cur_ref;
  uint8_t layer_buf[128];
  int32_t nstack;
  int32_t dep_j;
  if (!arena || !cur_mod || !sym_flat || callee_expr_ref <= 0)
    return -1;
  if (pipeline_expr_kind_ord_at(arena, callee_expr_ref) != 44)
    return -1;
  asm_qual_sym_layer_reset();
  cur_ref = callee_expr_ref;
  while (1) {
    int32_t falen;
    if (cur_ref <= 0)
      return -1;
    falen = pipeline_expr_field_access_name_len(arena, cur_ref);
    if (pipeline_expr_kind_ord_at(arena, cur_ref) != 44 || falen <= 0 || falen > 63)
      break;
    pipeline_expr_field_access_name_into(arena, cur_ref, layer_buf);
    if (asm_qual_sym_layer_push(layer_buf, falen) < 0)
      return -1;
    cur_ref = pipeline_expr_field_access_base_ref(arena, cur_ref);
  }
  nstack = asm_qual_sym_layer_count();
  if (cur_ref <= 0)
    return -1;
  {
    int32_t vnlen;
    uint8_t vname_buf[128];
    vnlen = pipeline_expr_var_name_len(arena, cur_ref);
    if (pipeline_expr_kind_ord_at(arena, cur_ref) != 3 || vnlen <= 0 || vnlen > 127)
      return -1;
    pipeline_expr_var_name_into(arena, cur_ref, vname_buf);
    dep_j = 0;
    while (dep_j < parser_get_module_num_imports(cur_mod)) {
      int32_t plen;
      uint8_t path_cnt_buf[128];
      int32_t pci;
      int32_t pseg;
      int32_t s0_rel;
      int32_t s0_ln;
      plen = pipeline_module_import_path_len(cur_mod, dep_j);
      if (plen <= 0 || plen > 63) {
        dep_j++;
        continue;
      }
      for (pci = 0; pci < plen && pci < 64; pci++)
        path_cnt_buf[pci] = pipeline_module_import_path_byte_at(cur_mod, dep_j, pci);
      pseg = glue_asm_import_path_segment_count(path_cnt_buf, plen);
      if (pseg <= 0 || nstack != pseg) {
        dep_j++;
        continue;
      }
      if (!glue_asm_import_segment_at(cur_mod, dep_j, 0, &s0_rel, &s0_ln) ||
          !glue_asm_import_path_slice_equal(cur_mod, dep_j, s0_rel, s0_ln, vname_buf, vnlen)) {
        dep_j++;
        continue;
      }
      {
        int32_t bad_mid = 0;
        int32_t sm;
        for (sm = 1; sm <= pseg - 1; sm++) {
          int32_t srv;
          int32_t slv;
          int32_t lay_ix;
          if (!glue_asm_import_segment_at(cur_mod, dep_j, sm, &srv, &slv)) {
            bad_mid = 1;
            break;
          }
          lay_ix = pseg - sm;
          asm_qual_sym_layer_copy(lay_ix, layer_buf, 64);
          if (!glue_asm_import_path_slice_equal(cur_mod, dep_j, srv, slv, layer_buf, asm_qual_sym_layer_len(lay_ix))) {
            bad_mid = 1;
            break;
          }
        }
        if (bad_mid) {
          dep_j++;
          continue;
        }
      }
      {
        uint8_t pre_buf[128];
        int32_t pre_len;
        int32_t blt;
        pre_len = glue_asm_fill_c_prefix_from_module_import(cur_mod, dep_j, pre_buf);
        if (pre_len <= 0) {
          dep_j++;
          continue;
        }
        asm_qual_sym_layer_copy(0, layer_buf, 64);
        blt = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, layer_buf, asm_qual_sym_layer_len(0), sym_flat);
        if (out_match_imp_j)
          *out_match_imp_j = dep_j;
        return blt;
      }
    }
  }
  return -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_resolve_whole_import_qualified_symbol_c(struct ast_ASTArena *arena, struct ast_Module *cur_mod,
                                                              int32_t callee_expr_ref, uint8_t *sym_flat,
                                                              int32_t *out_match_imp_j) {
  return pipeline_asm_resolve_whole_import_qualified_symbol_c_impl(arena, cur_mod, callee_expr_ref, sym_flat, out_match_imp_j);
}
#endif

/**
 * text 路径：为 call 准备至多 6 个实参（与 backend.x asm_emit_call_args_text 语义一致）。
 * 供 backend.x 薄包装 bl 委托（M8-tail）。
 */
/* G-02f-147：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-376 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t pipeline_asm_emit_call_args_text_c_impl(struct ast_ASTArena *arena, struct codegen_CodegenOutBuf *out,
                                           int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t target_arch,
                                           int32_t nargs) {
  int32_t i;
  int32_t arg_ref;
  if (!arena || !out || !ctx || expr_ref <= 0)
    return -1;
  if (nargs < 0 || nargs > 6)
    return -1;
  if (nargs <= 0)
    return 0;
  for (i = 0; i < nargs; i++) {
    arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
    if (arg_ref == 0)
      continue;
    if (pipeline_asm_emit_expr_c(arena, out, arg_ref, ctx, target_arch) != 0)
      return -1;
    if (target_arch == 0 || target_arch == 2) {
      if (backend_arch_emit_mov_rax_to_arg_reg(out, i, target_arch) != 0)
        return -1;
    } else if (backend_arch_emit_push_rax(out, target_arch) != 0) {
      return -1;
    }
  }
  if (target_arch == 1) {
    for (i = 0; i < nargs; i++) {
      if (backend_arch_emit_ldr_sp_offset_to_wi(out, i, target_arch) != 0)
        return -1;
    }
    if (backend_arch_emit_add_sp_imm(out, nargs * 16, target_arch) != 0)
      return -1;
  }
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_emit_call_args_text_c(struct ast_ASTArena *arena, struct codegen_CodegenOutBuf *out,
                                           int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t target_arch,
                                           int32_t nargs) {
  return pipeline_asm_emit_call_args_text_c_impl(arena, out, expr_ref, ctx, target_arch, nargs);
}
#endif

/**
 * ELF 路径：为 enc_call 准备实参（寄存器 + outgoing 栈；经 pipeline_asm_emit_expr_elf_for_call_args）。
 * 供 backend.x asm_emit_call_args_elf 薄包装（M8-tail）。
 */
/* G-02f-122：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_call_param_type_ref_at(struct ast_ASTArena *arena, int32_t call_expr_ref, int32_t param_index) {
  return pipeline_asm_call_param_type_ref_at_c(arena, call_expr_ref, param_index);
}
#endif




/** 设置 callee 形参 type_ref 后 emit 单个 CALL 实参。 */
/* G-02f-144：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-378 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_emit_one_call_arg_elf_c_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t call_expr_ref, int32_t arg_ref, int32_t arg_index,
                                            struct backend_AsmFuncCtx *ctx, int32_t ta) {
  if (!arena || !elf_ctx || !ctx || arg_ref == 0)
    return 0;
  pipeline_asm_emit_set_call_param_type_ref(glue_call_param_type_ref_at(arena, call_expr_ref, arg_index));
  pipeline_asm_emit_call_arg_begin_c();
  if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
    pipeline_asm_emit_call_arg_end_c();
    pipeline_asm_emit_set_call_param_type_ref(0);
    return -1;
  }
  {
    int32_t pty = glue_call_param_type_ref_at(arena, call_expr_ref, arg_index);
    /** 嵌套 CALL 实参：C struct 返回 rax=指针，须 deref 后再 spill/lea。 */
    if (pipeline_expr_kind_ord_at(arena, arg_ref) == 48 &&
        pipeline_asm_call_struct16_ret_needs_rax_deref_c(arena, arg_ref) != 0) {
      if (pipeline_asm_deref_struct16_rax_ptr_elf_c(elf_ctx, ta) != 0) {
        pipeline_asm_emit_call_arg_end_c();
        pipeline_asm_emit_set_call_param_type_ref(0);
        return -1;
      }
    }
    /** 仅嵌套 CALL 返回 16B struct（rax+rdx）；VAR lea 已在 rax 中，勿 spill（rdx 可能已失效）。 */
    if (pipeline_expr_kind_ord_at(arena, arg_ref) == 48 &&
        glue_spill_struct16_call_arg_to_lea_elf_c(arena, elf_ctx, ctx, pty, ta) != 0) {
      pipeline_asm_emit_call_arg_end_c();
      pipeline_asm_emit_set_call_param_type_ref(0);
      return -1;
    }
  }
  pipeline_asm_emit_call_arg_end_c();
  pipeline_asm_emit_set_call_param_type_ref(0);
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_emit_one_call_arg_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t call_expr_ref, int32_t arg_ref, int32_t arg_index,
                                            struct backend_AsmFuncCtx *ctx, int32_t ta) {
  return glue_emit_one_call_arg_elf_c_impl(arena, elf_ctx, call_expr_ref, arg_ref, arg_index, ctx, ta);
}
#endif


/* G-02f-146：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-377 call：实现体始终 seed；public PREFER 时 thin forward */

/*
 * PLATFORM: MACOS|ARM64 AAPCS64 — when set, emit_call_args treats >16B MEMORY
 * args as host-indirect (lea into GP), matching import METHOD / std_* export
 * wrappers. Pure→pure local calls leave this 0 (stack MEMORY ↔ param_home).
 * Set only around glue_asm_emit_call_with_cleanup for std_/core_ symbols.
 */
static int32_t g_emit_call_args_arm64_host_mem = 0;

static int32_t glue_asm_call_sym_is_host_export_c(const uint8_t *cname, int32_t clen) {
  if (!cname || clen < 4)
    return 0;
  /* "std_" */
  if (cname[0] == 115 && cname[1] == 116 && cname[2] == 100 && cname[3] == 95)
    return 1;
  /* "core_" */
  if (clen >= 5 && cname[0] == 99 && cname[1] == 111 && cname[2] == 114 && cname[3] == 101 &&
      cname[4] == 95)
    return 1;
  return 0;
}

extern int32_t glue_arm64_mov_x0_to_x8_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern void pipeline_asm_emit_ctx_sret_active_set(int32_t v);
extern void pipeline_asm_emit_ctx_sret_home_off_set(int32_t v);
extern void pipeline_asm_emit_ctx_sret_ret_sz_set(int32_t v);

/**
 * PLATFORM: MACOS|ARM64 — address of host-indirect MEMORY arg into rax/x0.
 * VAR: lea. Nested CALL/METHOD: sret into frame temp (save/restore outer x8), then lea.
 * Root (ErrorChain nested chain_wrap SEGV): bare lvalue_eff_addr on CALL fails;
 * outer let sret in x8 must survive inner materialize (≡ store_memory_by_value).
 * G.7: one materialize for CALL host + METHOD is_mem=2.
 */
static int32_t glue_emit_arm64_host_mem_arg_addr_to_rax_c(struct ast_ASTArena *arena,
                                                           struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                           void *ctx, int32_t arg_ref, int32_t sz,
                                                           int32_t ta) {
  int32_t ko;
  int32_t nbytes;
  int32_t off;
  int32_t save_off;
  int32_t ret_sz;
  struct glue_AsmFuncCtxCall *ly;
  if (!arena || !elf_ctx || !ctx || arg_ref <= 0 || sz <= 16 || ta != 1)
    return -1;
  ko = pipeline_expr_kind_ord_at(arena, arg_ref);
  /* EXPR_VAR = 3 */
  if (ko == 3)
    return pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, arg_ref, ctx, ta);
  ly = (struct glue_AsmFuncCtxCall *)ctx;
  nbytes = (sz + 7) & ~7;
  off = ly->next_offset;
  if (off < 16)
    off = 16;
  save_off = off + nbytes;
  if (save_off + 8 < off)
    return -1;
  ly->next_offset = save_off + 8;
  /* Save incoming x8 (outer let/call sret dest) before inner IRLR overwrite. */
  if (glue_arm64_mov_x8_to_x0_elf_c(elf_ctx) != 0)
    return -1;
  if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off, ta) != 0)
    return -1;
  if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta) != 0)
    return -1;
  if (glue_arm64_mov_x0_to_x8_elf_c(elf_ctx) != 0)
    return -1;
  if (ko == 48 || ko == 49) {
    ret_sz = glue_call_return_byte_size_c(arena, arg_ref);
    if (ret_sz <= 16)
      ret_sz = sz;
  } else {
    ret_sz = sz;
  }
  if (ret_sz <= 16)
    return -1;
  pipeline_asm_emit_ctx_sret_active_set(1);
  pipeline_asm_emit_ctx_sret_home_off_set(off);
  pipeline_asm_emit_ctx_sret_ret_sz_set(ret_sz);
  if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
    pipeline_asm_emit_ctx_sret_active_set(0);
    return -1;
  }
  pipeline_asm_emit_ctx_sret_active_set(0);
  /* Restore outer x8, then lea temp for host-indirect arg pointer. */
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, save_off, ta) != 0)
    return -1;
  if (glue_arm64_mov_x0_to_x8_elf_c(elf_ctx) != 0)
    return -1;
  return backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta);
}

int32_t pipeline_asm_emit_call_args_elf_c_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                          int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta,
                                          int32_t nargs) {
  int32_t reg_max;
  int32_t n_stack;
  int32_t stack_reserve;
  int32_t i;
  int32_t arg_ref;
  int32_t f32_on;
  int32_t sret_sh0;

  if (nargs < 0 || nargs > GLUE_ASM_MAX_CALL_ARGS)
    return -1;
  reg_max = glue_asm_call_reg_max(ta);
  f32_on = pipeline_asm_abi_f32_xmm_enabled_c();
  sret_sh0 = pipeline_asm_emit_call_sret_reg_shift_c();
  /** hidden sret 时 rdi 已预装 dest；走下方 gp 位移路径，勿进 f32-xmm 分轨（未实现 sret 位移）。 */
  if (ta == 0 && f32_on && sret_sh0 == 0)
    return glue_emit_call_args_elf_sysv_f32_xmm_c(arena, elf_ctx, expr_ref, ctx, ta, nargs);
  {
    int32_t sret_sh = (ta == 0) ? pipeline_asm_emit_call_sret_reg_shift_c() : 0;
    int32_t eff_reg_max = reg_max - sret_sh;
    n_stack = nargs - eff_reg_max;
    if (n_stack < 0)
      n_stack = 0;
    if (n_stack > 0 && ta == 2)
      return -1;

    /*
     * wave601: x86 outgoing words include MEMORY multi-word (not nargs-reg_max alone).
     * Cleanup twin: glue_asm_emit_call_with_cleanup uses glue_sysv_x86_call_n_stack_c.
     */
    if (ta == 0 && arena && expr_ref > 0) {
      int32_t nw = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
      stack_reserve = nw * 8;
      if (nw > 0 && (nw & 1))
        stack_reserve += 8;
    } else if (ta == 1 && arena && expr_ref > 0) {
      /*
       * wave603: AAPCS64 stack words include MEMORY multi-word (≡ x86 wave601),
       * not nargs-reg_max alone. Align 16 for arm64 SP.
       * Host-export (g_emit_call_args_arm64_host_mem): MEMORY is lea→GP, not
       * stack — skip MEMORY words in reserve (matches import METHOD is_mem=2).
       */
      int32_t nw = 0;
      int32_t gp_tmp = 0;
      int32_t j;
      int32_t host_mem = g_emit_call_args_arm64_host_mem;
      for (j = 0; j < nargs; j++) {
        int32_t ar_j = pipeline_expr_call_arg_ref(arena, expr_ref, j);
        int32_t pty_j = glue_call_param_type_ref_at(arena, expr_ref, j);
        int32_t sz_j = glue_sysv_arg_byte_size_c(arena, ctx, pty_j, ar_j);
        int32_t u_j = glue_sysv_arg_gp_units_from_size_c(sz_j);
        int32_t w_j = glue_sysv_arg_stack_words_c(sz_j, u_j);
        if (glue_sysv_arg_is_memory_by_value_c(sz_j)) {
          if (host_mem) {
            /* host-indirect: 1 GP, no stack words */
            if (gp_tmp + 1 <= reg_max)
              gp_tmp += 1;
          } else {
            nw += w_j;
          }
        } else if (u_j > 0 && gp_tmp + u_j <= reg_max)
          gp_tmp += u_j;
        else
          nw += w_j > 0 ? w_j : 1;
      }
      stack_reserve = nw * 8;
      if (stack_reserve > 0)
        stack_reserve = (stack_reserve + 15) & ~15;
    } else {
      stack_reserve = glue_asm_call_stack_cleanup_bytes(ta, nargs);
    }
    if (stack_reserve < 0)
      return -1;
    if (backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve, ta) != 0)
      return -1;

    /**
     * x86_64：先 pad（16 对齐），再右到左 push 栈实参。
     * wave601: MEMORY (sz>16) uses push_sysv_memory multi-qword; also any arg that
     * classification places on stack (excess GP), not only index>=eff_reg_max.
     */
    if (ta == 0) {
      int32_t nw = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
      int32_t kind_i;
      int32_t reg_k_i;
      int32_t stack_k_i;
      if (nw > 0 && (nw & 1)) {
        if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0)
          return -1;
        if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
          return -1;
      }
      for (i = nargs - 1; i >= 0; i--) {
        int32_t pty_i;
        int32_t sz_i;
        int32_t pushed;
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref == 0)
          continue;
        glue_sysv_x86_call_arg_slot_c(arena, expr_ref, nargs, i, &kind_i, &reg_k_i, &stack_k_i);
        if (kind_i != 2)
          continue;
        pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
        sz_i = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, arg_ref);
        if (glue_sysv_arg_is_memory_by_value_c(sz_i)) {
          pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(arena, elf_ctx, ctx, arg_ref, sz_i, ta);
          if (pushed < 0)
            return -1;
        } else {
          if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
            return -1;
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
            return -1;
        }
      }
      (void)eff_reg_max;
      (void)n_stack;
      (void)sret_sh;
    }

    /**
     * AAPCS64 (wave392 + wave600): spill-then-load for register args — same discipline
     * as SysV x86, including 9–16B INTEGER dual-GP (2 consecutive Xn).
     * Root wave392: high-to-low direct place into xN was insufficient when an earlier
     * arg was a nested CALL (make2 → x1; make1 clobbers x1 → take2 got y=x).
     * Root wave600: units hard-coded 1 + spill only x0 → multi dual-GP
     * `take2(mkA(), mkB())` / `f(n, s12, m)` placed only lows (mac fs take2=63≠41).
     * G.7: gp_units from arg size (≡ x86 path); spill x0+x1; load into gp_start[+1].
     * PLATFORM: MACOS|ARM64 product pure-asm · SHARED frame next_offset.
     */
    if (ta == 1) {
      int32_t gp_start_a64[GLUE_ASM_MAX_CALL_ARGS];
      int32_t gp_units_a64[GLUE_ASM_MAX_CALL_ARGS];
      int32_t spill_off_a64[GLUE_ASM_MAX_CALL_ARGS];
      int32_t arg_sz_a64[GLUE_ASM_MAX_CALL_ARGS];
      /* is_mem_a64: 0=reg/int, 1=stack MEMORY, 2=host-indirect lea (std_/core_ exports). */
      int32_t is_mem_a64[GLUE_ASM_MAX_CALL_ARGS];
      int32_t gp_cur_a64 = 0; /* AAPCS64 sret uses x8 — no GP shift */
      int32_t stk_slot = 0;
      int32_t host_mem = g_emit_call_args_arm64_host_mem;
      /*
       * wave603: MEMORY (sz>16) is stack-only for pure→pure (units=0) — do NOT
       * coerce to u=1 (lea while param_home expects by-value words).
       * Host-export (std_/core_): match import METHOD is_mem=2 lea→GP — export
       * wrappers copy from [x0] (ErrorChain 20B bare CALL residual / SEGV).
       * G.7: one discipline with METHOD host-indirect for host ABI symbols.
       */
      for (i = 0; i < nargs; i++) {
        int32_t pty_i;
        int32_t ar_i;
        int32_t u;
        int32_t sz_i;
        ar_i = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
        sz_i = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, ar_i);
        arg_sz_a64[i] = sz_i;
        is_mem_a64[i] = 0;
        spill_off_a64[i] = -1;
        u = glue_sysv_arg_gp_units_from_size_c(sz_i);
        if (glue_sysv_arg_is_memory_by_value_c(sz_i)) {
          if (host_mem) {
            is_mem_a64[i] = 2;
            if (gp_cur_a64 + 1 <= reg_max) {
              gp_start_a64[i] = gp_cur_a64;
              gp_units_a64[i] = 1;
              gp_cur_a64 += 1;
            } else {
              gp_start_a64[i] = -1;
              gp_units_a64[i] = 0;
            }
          } else {
            is_mem_a64[i] = 1;
            gp_start_a64[i] = -1;
            gp_units_a64[i] = 0;
          }
          continue;
        }
        if (u < 1)
          u = 1;
        if (u > 2)
          u = 2;
        gp_start_a64[i] = gp_cur_a64;
        gp_units_a64[i] = u;
        if (gp_cur_a64 + u <= reg_max)
          gp_cur_a64 += u;
        else
          gp_start_a64[i] = -1; /* stack / excess */
      }
      for (i = 0; i < nargs; i++) {
        int32_t so;
        if (gp_start_a64[i] < 0)
          continue;
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref == 0)
          continue;
        if (is_mem_a64[i] == 2) {
          /* PLATFORM: MACOS|ARM64 — host export large POD addr into GP. */
          if (glue_emit_arm64_host_mem_arg_addr_to_rax_c(arena, elf_ctx, ctx, arg_ref, arg_sz_a64[i],
                                                          ta) != 0)
            return -1;
        } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0) {
          return -1;
        }
        so = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units_a64[i]);
        if (so < 0)
          return -1;
        spill_off_a64[i] = so;
      }
      /*
       * Stage 12.0.5: materialize stack/MEMORY places *before* final GP load.
       * Skip is_mem==2 (already lea'd into GP). PLATFORM: MACOS|ARM64 AAPCS64.
       */
      for (i = 0; i < nargs; i++) {
        int32_t words;
        int32_t stored;
        if (gp_start_a64[i] >= 0)
          continue;
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref == 0)
          continue;
        if (is_mem_a64[i] == 2)
          continue;
        if (is_mem_a64[i] == 1) {
          /* wave603: multi-word MEMORY by-value at [sp+stk*8]. */
          stored = pipeline_asm_store_memory_by_value_to_sp_elf_c(arena, elf_ctx, ctx, arg_ref,
                                                                   arg_sz_a64[i], ta, stk_slot * 8);
          if (stored < 0)
            return -1;
          words = stored / 8;
          if (words < 1)
            words = 1;
          stk_slot += words;
          continue;
        }
        if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
          return -1;
        if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0)
          return -1;
        stk_slot++;
        /* dual-GP stack residual: only low half when excess GP */
        if (gp_units_a64[i] >= 2) {
          /* high half soft when stack-spilled dual — rare on probes */
        }
      }
      /*
       * Load high→low by *arg index*: x0 is spill temp and may be arg0.
       * Loading lower GPs first would clobber them when materializing higher ones
       * through x0 (wave392 reent2). Dual-GP loads write gp and gp+1 atomically
       * relative to later lower-index loads.
       * Must run *after* stack place so emit-to-x0 for stack does not wipe final GPs.
       */
      for (i = nargs - 1; i >= 0; i--) {
        if (spill_off_a64[i] < 0)
          continue;
        if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off_a64[i], gp_start_a64[i],
                                                     gp_units_a64[i]) != 0)
          return -1;
      }
      pipeline_asm_emit_set_call_param_type_ref(0);
      return 0;
    }

    /**
     * x86 寄存器实参：9–16B struct 占 2 个连续 GP；spill then load (SysV dual-load safety).
     * PLATFORM: LINUX+MACOS x86_64 SysV — SSE float args (param type / FLOAT_LIT / resolved)
     * go to xmm0–7 even on this legacy path (f32_xmm path is preferred when sret==0).
     */
    {
      int32_t gp_start[GLUE_ASM_MAX_CALL_ARGS];
      int32_t gp_units[GLUE_ASM_MAX_CALL_ARGS];
      int32_t spill_off[GLUE_ASM_MAX_CALL_ARGS];
      int32_t is_sse[GLUE_ASM_MAX_CALL_ARGS];
      int32_t is_f64[GLUE_ASM_MAX_CALL_ARGS];
      int32_t xmm_cur = 0;
      int32_t gp_cur = sret_sh;
      for (i = 0; i < nargs; i++) {
        int32_t pty_i;
        int32_t ar_i;
        int32_t u;
        ar_i = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
        is_sse[i] = glue_call_arg_is_sse_float_c(arena, expr_ref, i, pty_i);
        is_f64[i] = glue_call_arg_is_f64_width_c(arena, expr_ref, i, pty_i);
        if (is_sse[i]) {
          gp_start[i] = xmm_cur < 8 ? xmm_cur : -1;
          gp_units[i] = 1;
          spill_off[i] = -1;
          if (xmm_cur < 8)
            xmm_cur++;
          continue;
        }
        {
          int32_t sz_i = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, ar_i);
          /* wave601: MEMORY → stack only (already pushed above); skip GP place. */
          if (glue_sysv_arg_is_memory_by_value_c(sz_i)) {
            gp_start[i] = -1;
            gp_units[i] = 0;
            spill_off[i] = -1;
            continue;
          }
          u = glue_sysv_arg_gp_units_from_size_c(sz_i);
        }
        gp_start[i] = gp_cur;
        gp_units[i] = u;
        spill_off[i] = -1;
        if (u > 0 && gp_cur + u <= reg_max)
          gp_cur += u;
        else
          gp_start[i] = -1;
      }
      for (i = 0; i < nargs; i++) {
        int32_t so;
        if (gp_start[i] < 0)
          continue;
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref == 0)
          continue;
        if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
          return -1;
        so = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units[i]);
        if (so < 0)
          return -1;
        spill_off[i] = so;
      }
      for (i = 0; i < nargs; i++) {
        int32_t mov_rc;
        if (spill_off[i] < 0)
          continue;
        if (is_sse[i]) {
          if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off[i], ta) != 0)
            return -1;
          if (is_f64[i])
            mov_rc = backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, gp_start[i], ta);
          else
            mov_rc = backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, gp_start[i], ta);
          if (mov_rc != 0)
            return -1;
        } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], gp_start[i],
                                                           gp_units[i]) != 0) {
          return -1;
        }
      }
    }
    pipeline_asm_emit_set_call_param_type_ref(0);
    return 0;
  }
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_emit_call_args_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                          int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta,
                                          int32_t nargs) {
  return pipeline_asm_emit_call_args_elf_c_impl(arena, elf_ctx, expr_ref, ctx, ta, nargs);
}
#endif

/**
 * std.heap 薄包装 → heap_*_c / libc 符号。
 * co-emit 时 std.heap 模块常仅含 allocator_*（无 alloc/arena64_alloc 体）；须 redirect 避免 std_heap_* UND。
 */
/* G-02f-125：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-374 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_try_std_heap_redirect_sym_local_impl(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                    int32_t out_cap) {
  static const struct {
    const char *from;
    const char *to;
  } k_tab[] = {
      /** 核心堆 API：co-emit 薄模块缺函数体，链 runtime_heap_user.o（heap_*_c）。
       * PLATFORM: SHARED — do NOT map bare free/realloc (collide with libc free/realloc
       * in std.heap.libc co-emit → U heap_free_c under freestanding). Typed free_* /
       * realloc_* remain; usize alloc/realloc use explicit mid or heap_*_c names. */
      {"alloc", "heap_alloc_c"},
      /* bare realloc/free removed: libc FFI names in heap.libc (G.7 complete, no dual). */
      {"alloc_i32", "heap_alloc_i32_c"},
      {"alloc_i32_ret_i32_ptr", "heap_alloc_i32_c"},
      {"alloc_i32_ret_u8_ptr", "heap_alloc_u8_c"},
      {"alloc_i32_ret_u64_ptr", "heap_alloc_u64_c"},
      {"alloc_i32_ret_f64_ptr", "heap_alloc_f64_c"},
      {"alloc_i32_ret_f32_ptr", "heap_alloc_f32_c"},
      {"realloc_i32", "heap_realloc_i32_c"},
      {"realloc_i32_ret_i32_ptr", "heap_realloc_i32_c"},
      {"realloc_u64_ret_u64_ptr", "heap_realloc_u64_c"},
      {"realloc_f64_ret_f64_ptr", "heap_realloc_f64_c"},
      {"realloc_f32_ret_f32_ptr", "heap_realloc_f32_c"},
      {"realloc_u8_ret_u8_ptr", "heap_realloc_u8_c"},
      {"free_i32", "heap_free_i32_c"},
      {"free_i32_ptr", "heap_free_i32_c"},
      {"free_u64_ptr", "heap_free_u64_c"},
      {"free_f64_ptr", "heap_free_f64_c"},
      {"free_f32_ptr", "heap_free_f32_c"},
      {"alloc_u8", "heap_alloc_u8_c"},
      {"realloc_u8", "heap_realloc_u8_c"},
      {"free_u8", "heap_free_u8_c"},
      {"alloc_f32", "heap_alloc_f32_c"},
      {"realloc_f32", "heap_realloc_f32_c"},
      {"free_f32", "heap_free_f32_c"},
      {"copy_i32_at", "heap_copy_i32_at_c"},
      {"copy_u8_at", "heap_copy_u8_at_c"},
      {"copy_f32_at", "heap_copy_f32_at_c"},
      {"copy_u64_at", "heap_copy_u64_at_c"},
      {"copy_f64_at", "heap_copy_f64_at_c"},
      {"copy_i32_ptr_i32_i32_ptr_i32", "heap_copy_i32_at_c"},
      {"copy_u8_ptr_i32_u8_ptr_i32", "heap_copy_u8_at_c"},
      {"copy_f32_ptr_i32_f32_ptr_i32", "heap_copy_f32_at_c"},
      {"copy_u64_ptr_i32_u64_ptr_i32", "heap_copy_u64_at_c"},
      {"copy_f64_ptr_i32_f64_ptr_i32", "heap_copy_f64_at_c"},
      {"arena64_init", "heap_arena64_init_c"},
      {"arena64_alloc", "heap_arena64_alloc_c"},
      {"arena64_deinit", "heap_arena64_deinit_c"},
      {"ptr_mod", "heap_ptr_mod_c"},
  };
  size_t i;
  if (!name || name_len <= 0 || !sym_out || out_cap <= 0)
    return 0;
  for (i = 0; i < sizeof(k_tab) / sizeof(k_tab[0]); i++) {
    size_t flen = strlen(k_tab[i].from);
    size_t tlen = strlen(k_tab[i].to);
    if ((int32_t)flen != name_len || memcmp(name, k_tab[i].from, flen) != 0)
      continue;
    if ((int32_t)tlen + 1 > out_cap)
      return 0;
    memcpy(sym_out, k_tab[i].to, tlen);
    return (int32_t)tlen;
  }
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_try_std_heap_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                    int32_t out_cap) {
  return glue_try_std_heap_redirect_sym_local_impl(name, name_len, sym_out, out_cap);
}
#endif




/**
 * co-emit std.string 时 extern xlang_string_* 带 std_string_ 前缀；redirect 到 string.o 符号。
 */
/* G-02f-123：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-371 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_try_std_string_xlang_redirect_sym_local_impl(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                            int32_t out_cap) {
  int32_t suffix_len;
  if (!name || name_len <= 11 || !sym_out || out_cap <= 0)
    return 0;
  if (memcmp(name, "std_string_", 11) != 0)
    return 0;
  suffix_len = name_len - 11;
  if (suffix_len < 12 || memcmp(name + 11, "xlang_string_", 12) != 0)
    return 0;
  if (suffix_len + 1 > out_cap)
    return 0;
  memcpy(sym_out, name + 11, (size_t)suffix_len);
  return suffix_len;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_try_std_string_xlang_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                            int32_t out_cap) {
  return glue_try_std_string_xlang_redirect_sym_local_impl(name, name_len, sym_out, out_cap);
}
#endif




/**
 * VAR callee 导出符号：overload mangled → std.heap redirect → typeck dep 前缀 → co-emit dep 前缀。
 */
extern int32_t pipeline_typeck_resolve_call_func_index_for_emit_c(struct ast_Module *m, struct ast_ASTArena *a,
                                                                  int32_t call_expr_ref);
/** 查询函数是否为 extern 声明（无函数体，定义由外部桩/libc 提供）。 */
extern int32_t pipeline_module_func_is_extern_at(struct ast_Module *module, int32_t fi);

/* G-02f-145：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-378 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_build_call_export_sym_c_impl(struct ast_ASTArena *arena, int32_t call_expr_ref,
                                                int32_t callee_ref, struct ast_Module *mod,
                                                struct ast_PipelineDepCtx *dep_pipe, uint8_t *out, int32_t out_cap) {
  uint8_t cname[128];
  int32_t clen;
  int32_t dep_ix;
  uint8_t path[128];
  uint8_t prefix[128];
  int32_t plen;
  int32_t rlen;

  if (!arena || callee_ref <= 0 || !out || out_cap <= 0)
    return -1;
  clen = pipeline_expr_var_name_len(arena, callee_ref);
  /* wave577 Cap / wave580: AST name slots u8[128] content cap 127 (was 63). */
  if (clen <= 0 || clen > 127)
    return -1;
  pipeline_expr_var_name_into(arena, callee_ref, cname);
  /*
   * PLATFORM: SHARED — heap thin redirect (alloc/free → heap_*_c) must NOT
   * steal:
   *  - libc free/realloc/malloc when co-emitting std.heap.libc (free→heap_free_c)
   *  - same-module local exports when co-emit has real bodies
   * G.7: complete existing redirect authority (guards before table).
   * Note: extern "C" free may be absent from module_num_funcs; path gate is required.
   */
  {
    const char *dep_path = driver_get_current_dep_path_for_codegen();
    int32_t skip_heap_redirect = 0;
    int32_t has_local = 0;
    /* std.heap.libc — bare free/malloc/realloc are libc FFI, not heap_*_c. */
    if (dep_path && dep_path[0]
        && (strstr(dep_path, "heap.libc") != NULL || strstr(dep_path, "heap/libc") != NULL))
      skip_heap_redirect = 1;
    if (mod) {
      int32_t efi;
      for (efi = 0; efi < pipeline_module_num_funcs(mod); efi++) {
        if (!pipeline_module_func_name_equal_at(mod, efi, cname, clen))
          continue;
        if (pipeline_module_func_is_extern_at(mod, efi) != 0) {
          /* Prefer bare extern name (even if also listed with a body elsewhere). */
          if (clen > 0 && clen < out_cap) {
            memcpy(out, cname, (size_t)clen);
            return clen;
          }
          return -1;
        }
        has_local = 1;
      }
    }
    if (!skip_heap_redirect && !has_local) {
      rlen = glue_try_std_heap_redirect_sym_local(cname, clen, out, out_cap);
      if (rlen > 0)
        return rlen;
    }
  }
  dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
  if (dep_ix < 0 && dep_pipe) {
    int32_t nd = pipeline_dep_ctx_ndep(dep_pipe);
    int32_t j;
    int32_t fi;
    for (j = 0; j < nd; j++) {
      struct ast_Module *dm = pipeline_dep_ctx_module_at(dep_pipe, j);
      if (!dm)
        continue;
      for (fi = 0; fi < pipeline_module_num_funcs(dm); fi++) {
        if (pipeline_module_func_name_equal_at(dm, fi, cname, clen)) {
          dep_ix = j;
          break;
        }
      }
      if (dep_ix >= 0)
        break;
    }
  }
  if (dep_ix >= 0 && dep_pipe) {
    /* 【Why extern 裸名】dep 池匹配到 extern function（xlang_sys_* / libc open/lseek 等）时，
     * 定义由 freestanding_io 桩或 libc 提供（裸名），勿加 dep 前缀（否则 ld 缺符号
     * std_sys_linux_xlang_sys_listen / std_sys_linux_open）。 */
    struct ast_Module *dep_mod = pipeline_dep_ctx_module_at(dep_pipe, dep_ix);
    struct ast_ASTArena *dep_arena = pipeline_dep_ctx_arena_at(dep_pipe, dep_ix);
    if (dep_mod) {
      int32_t fi2;
      int32_t saw_non_extern = 0;
      for (fi2 = 0; fi2 < pipeline_module_num_funcs(dep_mod); fi2++) {
        if (pipeline_module_func_name_equal_at(dep_mod, fi2, cname, clen)) {
          if (pipeline_module_func_is_extern_at(dep_mod, fi2) != 0) {
            /* Keep scanning: overloads may mix extern FFI + local bodies. */
            continue;
          }
          saw_non_extern = 1;
          break;
        }
      }
      if (!saw_non_extern) {
        /* Only extern hit(s) for this name in dep_mod → bare libc/syscall face. */
        for (fi2 = 0; fi2 < pipeline_module_num_funcs(dep_mod); fi2++) {
          if (pipeline_module_func_name_equal_at(dep_mod, fi2, cname, clen)
              && pipeline_module_func_is_extern_at(dep_mod, fi2) != 0) {
            if (clen > 0 && clen < out_cap) {
              memcpy(out, cname, (size_t)clen);
              return clen;
            }
            return -1;
          }
        }
      }
    }
    memset(path, 0, sizeof(path));
    pipeline_dep_ctx_import_path_copy64(dep_pipe, dep_ix, path);
    if (path[0] && dep_mod) {
      int32_t want_np = pipeline_expr_call_num_args_at(arena, call_expr_ref);
      int32_t use_fi = -1;
      int32_t r_func = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref);
      int32_t r_dep = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
      uint8_t mid[128];
      int32_t mid_len;
      if (!dep_arena)
        dep_arena = arena;
      /*
       * PLATFORM: SHARED — freestanding co-emit overload CALL residual:
       * prior path always used bare field mid (prefix+cname) → U std_vec_reserve
       * while T std_vec_reserve_Vec_i32_ptr (formal export mid).
       * G.7: complete call-export authority with formal/score mid (same as import-binding).
       * Resolve must use the caller arena (CALL stamp lives there). Dep arena
       * at the same expr_ref is a different node (STD-091 io_err_cancelled →
       * std_error_base_fs). Name+arity gate matches the .x twin.
       */
      use_fi = pipeline_typeck_resolve_call_func_index_for_emit_c(dep_mod, arena, call_expr_ref);
      if (use_fi >= 0 && (use_fi >= pipeline_module_num_funcs(dep_mod)
                          || pipeline_module_func_is_extern_at(dep_mod, use_fi) != 0
                          || !pipeline_module_func_name_equal_at(dep_mod, use_fi, cname, clen)
                          || pipeline_module_func_num_params_at(dep_mod, use_fi) != want_np))
        use_fi = -1;
      if (use_fi < 0 && r_dep == dep_ix && r_func >= 0 && r_func < pipeline_module_num_funcs(dep_mod)
          && pipeline_module_func_is_extern_at(dep_mod, r_func) == 0
          && pipeline_module_func_name_equal_at(dep_mod, r_func, cname, clen)
          && pipeline_module_func_num_params_at(dep_mod, r_func) == want_np)
        use_fi = r_func;
      if (use_fi < 0)
        use_fi = glue_asm_score_import_binding_func_ix_c(arena, 0, call_expr_ref, dep_mod, dep_arena, cname,
                                                         clen, want_np, 0);
      glue_codegen_import_path_to_c_prefix_into(path, prefix, 128);
      plen = 0;
      while (plen < 127 && prefix[plen])
        plen++;
      if (plen > 0) {
        if (use_fi >= 0) {
          mid_len = glue_asm_build_func_overload_mid_c(dep_mod, dep_arena, use_fi, mid, 64);
          if (mid_len > 0)
            return glue_asm_build_import_binding_call_sym(prefix, plen, mid, mid_len, out);
        }
        return glue_asm_build_import_binding_call_sym(prefix, plen, cname, clen, out);
      }
    }
  }
  if (mod) {
    int32_t func_ix = pipeline_typeck_resolve_call_func_index_for_emit_c(mod, arena, call_expr_ref);
    int32_t want_np = pipeline_expr_call_num_args_at(arena, call_expr_ref);
    if (func_ix < 0) {
      /* typeck residual (freestanding XT001): score same-module overloads. */
      func_ix = glue_asm_score_import_binding_func_ix_c(arena, 0, call_expr_ref, mod, arena, cname, clen,
                                                       want_np, 0);
    }
    if (func_ix >= 0) {
      /* extern 函数（xlang_sys_* / libc）用裸名：定义由 freestanding_io 桩或 libc 提供，
       * 勿加 dep 前缀（否则 ld 缺符号 std_heap_page_mmap_xlang_sys_mmap）。 */
      if (pipeline_module_func_is_extern_at(mod, func_ix) != 0) {
        if (clen > 0 && clen < out_cap) {
          memcpy(out, cname, (size_t)clen);
          return clen;
        }
        return -1;
      }
      return glue_asm_build_func_export_sym_c(mod, arena, func_ix, out, out_cap);
    }
  }
  /* 兜底：被调用函数既不在 dep 列表也不在当前模块 → extern 函数（xlang_sys_*, libc）。
   * extern 定义由 freestanding_io 桩或 libc 提供（裸名），勿加 dep 前缀
   *（否则 ld 缺符号 std_heap_page_mmap_xlang_sys_mmap）。 */
  if (clen > 0 && clen < out_cap) {
    memcpy(out, cname, (size_t)clen);
    return clen;
  }
  return -1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_build_call_export_sym_c(struct ast_ASTArena *arena, int32_t call_expr_ref,
                                                int32_t callee_ref, struct ast_Module *mod,
                                                struct ast_PipelineDepCtx *dep_pipe, uint8_t *out, int32_t out_cap) {
  return glue_asm_build_call_export_sym_c_impl(arena, call_expr_ref, callee_ref, mod, dep_pipe, out, out_cap);
}
#endif


/**
 * co-emit std.encoding/mod.x：std_encoding_utf8_valid -> encoding_utf8_valid_c（链 std/encoding/encoding.o）。
 */
/* G-02f-123：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-372 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_try_std_encoding_redirect_sym_local_impl(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                        int32_t out_cap) {
  const int32_t prefix_len = 13; /* "std_encoding_" */
  int32_t suffix_len;
  int32_t out_len;
  if (!name || name_len <= prefix_len || !sym_out || out_cap <= 0)
    return 0;
  if (memcmp(name, "std_encoding_", (size_t)prefix_len) != 0)
    return 0;
  suffix_len = name_len - prefix_len;
  if (suffix_len <= 0)
    return 0;
  out_len = 9 + suffix_len + 2; /* encoding_ + suffix + _c */
  if (out_len >= out_cap)
    return 0;
  memcpy(sym_out, "encoding_", 9);
  memcpy(sym_out + 9, name + prefix_len, (size_t)suffix_len);
  sym_out[9 + suffix_len] = '_';
  sym_out[9 + suffix_len + 1] = 'c';
  return out_len;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_try_std_encoding_redirect_sym_local(const uint8_t *name, int32_t name_len, uint8_t *sym_out,
                                                        int32_t out_cap) {
  return glue_try_std_encoding_redirect_sym_local_impl(name, name_len, sym_out, out_cap);
}
#endif




/** 经 std.fs/net/std.heap 薄包装重定向表发射 call；无命中则直调 name。 */
/* G-02f-141：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-373 call：实现体始终 seed；public PREFER 时 thin forward */
/**
 * Emit redirected or direct call by symbol name.
 * PLATFORM: LINUX+MACOS x86_64 SysV — float arg/ret xmm is type-driven only:
 *   args: glue_emit_call_args / f32_xmm path (param type + FLOAT_LIT + resolved)
 *   ret:  glue_asm_harvest_call_ret_to_gpr_c (pipeline_asm_call_return_type_kind_ord_c)
 * G.7: no std_math_* symbol-name pre/post xmm choke (import FIELD_ACCESS + dep type map
 * are the authority; name gates hide missing type resolve on other callees).
 */
int32_t glue_asm_enc_call_redirected_impl(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len,
                                            int32_t ta) {
  uint8_t redir[128];
  int32_t rlen;
  int32_t rc;
  if (!name || name_len <= 0)
    return -1;
  rlen = glue_try_std_heap_redirect_sym_local(name, name_len, redir, 64);
  if (rlen <= 0)
    rlen = glue_try_std_string_xlang_redirect_sym_local(name, name_len, redir, 64);
  if (rlen <= 0)
    rlen = glue_try_std_encoding_redirect_sym_local(name, name_len, redir, 64);
  if (rlen <= 0)
    rlen = pipeline_asm_redirect_std_c_wrapper_sym(name, name_len, redir, 64);
  if (rlen > 0) {
    backend_call_debugf("call redirect %.*s -> %.*s", (int)name_len, (char *)name, (int)rlen, (char *)redir);
    rc = backend_enc_call_arch(elf_ctx, redir, rlen, ta);
  } else {
    rc = backend_enc_call_arch(elf_ctx, name, name_len, ta);
  }
  return rc;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_enc_call_redirected(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len,
                                            int32_t ta) {
  return glue_asm_enc_call_redirected_impl(elf_ctx, name, name_len, ta);
}
#endif


/**
 * import 路径前缀是否为 std.fmt / std.debug（println/print 字符串字面量特化）。
 */
/* G-02f-114：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-370 call：实现体始终 seed；public PREFER 时 thin forward（-E 丢 pure 嵌套） */
int32_t glue_asm_prefix_is_fmt_or_debug_impl(const uint8_t *pre, int32_t pre_len) {
  if (!pre || pre_len < 8)
    return 0;
  if (pre_len >= 8 && memcmp(pre, "std_fmt_", 8) == 0)
    return 1;
  if (pre_len >= 10 && memcmp(pre, "std_debug_", 10) == 0)
    return 1;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_prefix_is_fmt_or_debug(const uint8_t *pre, int32_t pre_len) {
  return glue_asm_prefix_is_fmt_or_debug_impl(pre, pre_len);
}
#endif



/**
 * 将 STRING_LIT 字节追加到 .text 尾（紧跟 lea [rip+0]），结果指针装入 rax（x86_64）。
 * 供 fmt.println 特化与其它须 *u8 实参的路径复用。
 */
/* G-02f-146：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-372 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_emit_string_lit_ptr_rax_elf_c_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                               int32_t str_expr_ref, int32_t ta) {
  uint8_t sbuf[128];
  int32_t slen;
  /* PLATFORM: SHARED — ta 0/1 via glue_asm_emit_jmp_skip_string_then_lea (wave108 arm64). */
  if (!arena || !elf_ctx || str_expr_ref <= 0 || (ta != 0 && ta != 1))
    return -1;
  if (pipeline_expr_kind_ord_at(arena, str_expr_ref) != GLUE_EXPR_STRING_LIT_ORD)
    return -1;
  slen = glue_asm_string_lit_len(arena, str_expr_ref);
  /* Stage 12.2.5: empty OK; long diag msgs up to 126 (was wrong hard-cap 63). */
  if (slen < 0 || slen > 126)
    return -1;
  glue_asm_string_lit_into(arena, str_expr_ref, sbuf);
  if (glue_asm_emit_jmp_skip_string_then_lea((uint8_t *)elf_ctx, ta, 1, sbuf, slen) != 0)
    return -1;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_emit_string_lit_ptr_rax_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                               int32_t str_expr_ref, int32_t ta) {
  return glue_asm_emit_string_lit_ptr_rax_elf_c_impl(arena, elf_ctx, str_expr_ref, ta);
}
#endif

/**
 * fmt/debug binding.print / println("…"): embed rodata + call std_fmt_print or
 * std_fmt_println(ptr,len). Avoid generic emit_expr on STRING_LIT (hello.x SIGSEGV).
 *
 * PLATFORM: SHARED — product parses `fmt.println("…")` as METHOD_CALL (kind 49), not
 * CALL+FIELD_ACCESS. G.7: accept both CALL and METHOD_CALL arg accessors (same leaf).
 * ta==0 x86_64: lea rdi + mov eax,len + mov rsi,rax.
 * ta==1 aarch64: ADR x0 + mov_imm w1 (rbx alias) so len does not clobber ptr in x0 (wave108).
 */
/* G-02f-144：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-378 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_try_emit_fmt_string_lit_import_call_elf_c_impl(struct ast_ASTArena *arena,
                                                                  struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                                  int32_t call_expr_ref, struct backend_AsmFuncCtx *ctx,
                                                                  int32_t ta, const uint8_t *pre_buf, int32_t pre_len,
                                                                  const uint8_t *field_name, int32_t field_len) {
  int32_t is_ln;
  int32_t nargs;
  int32_t arg_ref;
  int32_t slen;
  int32_t expr_ko;
  uint8_t sym_flat[128];
  int32_t sym_len;
  uint8_t sbuf[128];
  /* PLATFORM: SHARED — x86_64 (0) + aarch64 (1) string-embed fmt path (wave108). */
  if (!arena || !elf_ctx || !ctx || call_expr_ref <= 0 || (ta != 0 && ta != 1))
    return 0;
  /* PLATFORM: SHARED — METHOD_CALL vs CALL arg table (hello.x pure-asm wave105). */
  expr_ko = pipeline_expr_kind_ord_at(arena, call_expr_ref);
  if (expr_ko == GLUE_EXPR_METHOD_CALL_ORD) {
    nargs = pipeline_expr_method_call_num_args_at(arena, call_expr_ref);
    arg_ref = (nargs == 1) ? pipeline_expr_method_call_arg_ref(arena, call_expr_ref, 0) : 0;
  } else {
    nargs = pipeline_expr_call_num_args_at(arena, call_expr_ref);
    arg_ref = (nargs == 1) ? pipeline_expr_call_arg_ref(arena, call_expr_ref, 0) : 0;
  }
  backend_call_debugf("try fmt lit pre=%.*s field=%.*s nargs=%d arg_ko=%d expr_ko=%d", (int)pre_len,
                      pre_len > 0 ? (char *)pre_buf : "", (int)field_len, field_len > 0 ? (char *)field_name : "",
                      (int)nargs, arg_ref > 0 ? (int)pipeline_expr_kind_ord_at(arena, arg_ref) : -1, (int)expr_ko);
  if (!glue_asm_prefix_is_fmt_or_debug(pre_buf, pre_len))
    return 0;
  if (field_len == 7 && memcmp(field_name, "println", 7) == 0)
    is_ln = 1;
  else if (field_len == 5 && memcmp(field_name, "print", 5) == 0)
    is_ln = 0;
  else
    return 0;
  if (nargs != 1)
    return 0;
  if (arg_ref <= 0 || pipeline_expr_kind_ord_at(arena, arg_ref) != GLUE_EXPR_STRING_LIT_ORD)
    return 0;
  slen = glue_asm_string_lit_len(arena, arg_ref);
  /* Stage 12.2.5: empty OK; string lit embed cap 126. */
  if (slen < 0 || slen > 126)
    return -1;
  glue_asm_string_lit_into(arena, arg_ref, sbuf);
  /*
   * Link name: bare std_fmt_println / std_fmt_print (runtime_asm_io_stubs T symbols).
   * Do not overload-mangle string lit → println_i32_reti32 UNDEF (wave105 root).
   */
  sym_len = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, field_name, field_len, sym_flat);
  if (sym_len <= 0)
    return -1;
  (void)is_ln;
  backend_call_debugf("fmt string lit call %.*s slen=%d ta=%d", (int)sym_len, (char *)sym_flat, (int)slen, (int)ta);
  if (glue_asm_emit_jmp_skip_string_then_lea((uint8_t *)elf_ctx, ta, 0, sbuf, slen) != 0)
    return -1;
  if (ta == 1) {
    /*
     * PLATFORM: aarch64 AAPCS — ptr already in x0 from ADR.
     * mov_imm32_to_w0 would clobber x0; load len into w1 via rbx alias instead.
     */
    if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, slen, ta) != 0)
      return -1;
  } else {
    /** arg1 = len (i32/size_t low 32; SysV zero-extends): eax then → rsi. */
    if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, slen, ta) != 0)
      return -1;
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0)
      return -1;
  }
  if (glue_asm_enc_call_redirected(elf_ctx, sym_flat, sym_len, ta) != 0)
    return -1;
  return 1;
}

/* ---- fmt-any JSON schema emit (print_any) — G.7 twin of backend_call_dispatch.x ---- */

static int32_t glue_asm_fmt_any_append_dec_c(uint8_t *out, int32_t cap, int32_t pos, int32_t v) {
  char digs[12];
  int nd = 0;
  int i;
  if (!out || cap <= 0 || pos < 0 || v < 0)
    return -1;
  if (v == 0) {
    if (pos >= cap)
      return -1;
    out[pos] = '0';
    return pos + 1;
  }
  while (v > 0 && nd < 11) {
    digs[nd++] = (char)('0' + (v % 10));
    v /= 10;
  }
  for (i = nd - 1; i >= 0; i--) {
    if (pos >= cap)
      return -1;
    out[pos++] = (uint8_t)digs[i];
  }
  return pos;
}

static int32_t glue_asm_fmt_any_find_layout_c(struct ast_Module *m, const uint8_t *nm, int32_t nlen) {
  int32_t n, k, ln, i;
  uint8_t buf[128];
  if (!m || !nm || nlen <= 0)
    return -1;
  n = pipeline_module_num_struct_layouts_at(m);
  for (k = 0; k < n; k++) {
    ln = pipeline_module_struct_layout_name_len(m, k);
    if (ln == nlen && ln > 0 && ln <= 127) {
      pipeline_module_struct_layout_name_into(m, k, buf);
      for (i = 0; i < nlen; i++) {
        if (buf[i] != nm[i])
          break;
      }
      if (i == nlen)
        return k;
    }
  }
  return -1;
}

static int32_t glue_asm_fmt_any_build_schema_c(struct ast_Module *m, struct ast_ASTArena *arena, int32_t ty,
                                              uint8_t *out, int32_t cap, int32_t base_off, int32_t depth) {
  int32_t tk, pos = 0, elem, asz, etk, nlen, li, nf, j, fnl, fty, foff, ftk, sub;
  int32_t is_some_j = -1, value_j = -1, is_opt = 0;
  uint8_t nm[128], fnm[64], scratch[128];
  if (!m || !arena || !out || ty <= 0 || cap <= 0 || depth > 4)
    return -1;
  tk = pipeline_type_kind_ord_at(arena, ty);
  if (tk == 0) { /* I32 */
    if (pos + 2 >= cap)
      return -1;
    out[pos++] = 'i';
    out[pos++] = '@';
    return glue_asm_fmt_any_append_dec_c(out, cap, pos, base_off);
  }
  if (tk == 1) { /* BOOL */
    if (pos + 2 >= cap)
      return -1;
    out[pos++] = 'b';
    out[pos++] = '@';
    return glue_asm_fmt_any_append_dec_c(out, cap, pos, base_off);
  }
  if (tk == 10) { /* ARRAY */
    elem = pipeline_type_elem_ref_at(arena, ty);
    asz = pipeline_type_array_size_at(arena, ty);
    if (elem <= 0 || asz <= 0)
      return -1;
    etk = pipeline_type_kind_ord_at(arena, elem);
    if (etk == 2 || etk == 0) {
      if (pos + 2 >= cap)
        return -1;
      out[pos++] = (etk == 2) ? 'u' : 'a';
      out[pos++] = '@';
      pos = glue_asm_fmt_any_append_dec_c(out, cap, pos, base_off);
      if (pos < 0 || pos >= cap)
        return -1;
      out[pos++] = ',';
      return glue_asm_fmt_any_append_dec_c(out, cap, pos, asz);
    }
    return -1;
  }
  /* TYPE_SLICE=11 — i32[] → A@off (fat); u8[] → -1 (u8_slc mid). PLATFORM: SHARED. */
  if (tk == 11) {
    elem = pipeline_type_elem_ref_at(arena, ty);
    if (elem <= 0)
      return -1;
    etk = pipeline_type_kind_ord_at(arena, elem);
    if (etk == 2) /* u8[] keeps mid std_fmt_*_u8_slc */
      return -1;
    if (etk == 0) { /* i32[] */
      if (pos + 2 >= cap)
        return -1;
      out[pos++] = 'A';
      out[pos++] = '@';
      return glue_asm_fmt_any_append_dec_c(out, cap, pos, base_off);
    }
    return -1;
  }
  if (tk != 8) /* NAMED */
    return -1;
  nlen = pipeline_type_named_name_into(arena, ty, nm);
  if (nlen <= 0 || nlen > 127)
    return -1;
  li = glue_asm_fmt_any_find_layout_c(m, nm, nlen);
  if (li < 0)
    return -1;
  nf = pipeline_module_struct_layout_num_fields(m, li);
  if (nf <= 0)
    return -1;
  if (nlen >= 7 && memcmp(nm, "Option_", 7) == 0)
    is_opt = 1;
  if (is_opt) {
    for (j = 0; j < nf; j++) {
      fnl = pipeline_module_struct_layout_field_name_len(m, li, j);
      if (fnl > 0 && fnl <= 63) {
        pipeline_module_struct_layout_field_name_into(m, li, j, fnm);
        if (fnl == 7 && memcmp(fnm, "is_some", 7) == 0)
          is_some_j = j;
        if (fnl == 5 && memcmp(fnm, "value", 5) == 0)
          value_j = j;
      }
    }
    if (is_some_j >= 0 && value_j >= 0) {
      int si;
      foff = pipeline_module_struct_layout_field_offset_at(m, li, is_some_j);
      if (pos >= cap)
        return -1;
      out[pos++] = '?';
      pos = glue_asm_fmt_any_append_dec_c(out, cap, pos, base_off + foff);
      if (pos < 0 || pos >= cap)
        return -1;
      out[pos++] = ':';
      fty = pipeline_module_struct_layout_field_type_ref(m, li, value_j);
      foff = pipeline_module_struct_layout_field_offset_at(m, li, value_j);
      sub = glue_asm_fmt_any_build_schema_c(m, arena, fty, scratch, 128, base_off + foff, depth + 1);
      if (sub < 0 || pos + sub > cap)
        return -1;
      for (si = 0; si < sub; si++)
        out[pos++] = scratch[si];
      return pos;
    }
  }
  if (pos >= cap)
    return -1;
  out[pos++] = '{';
  for (j = 0; j < nf; j++) {
    int ci, sj;
    if (j > 0) {
      if (pos >= cap)
        return -1;
      out[pos++] = ',';
    }
    fnl = pipeline_module_struct_layout_field_name_len(m, li, j);
    if (fnl <= 0 || fnl > 63)
      return -1;
    pipeline_module_struct_layout_field_name_into(m, li, j, fnm);
    if (pos + fnl + 1 >= cap)
      return -1;
    for (ci = 0; ci < fnl; ci++)
      out[pos++] = fnm[ci];
    out[pos++] = ':';
    fty = pipeline_module_struct_layout_field_type_ref(m, li, j);
    foff = pipeline_module_struct_layout_field_offset_at(m, li, j);
    ftk = pipeline_type_kind_ord_at(arena, fty);
    if (ftk != 0 && ftk != 1 && ftk != 8 && ftk != 10 && ftk != 11)
      return -1;
    sub = glue_asm_fmt_any_build_schema_c(m, arena, fty, scratch, 128, base_off + foff, depth + 1);
    if (sub < 0 || pos + sub > cap)
      return -1;
    for (sj = 0; sj < sub; sj++)
      out[pos++] = scratch[sj];
  }
  if (pos >= cap)
    return -1;
  out[pos++] = '}';
  return pos;
}

/**
 * PLATFORM: SHARED — print_any JSON emit. Calls std_fmt_json_println_schema / _print_schema.
 * G.7 twin of glue_asm_try_emit_fmt_any_import_call_elf_c in backend_call_dispatch.x.
 */
int32_t glue_asm_try_emit_fmt_any_import_call_elf_c(struct ast_ASTArena *arena,
                                                     struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                     int32_t call_expr_ref, struct backend_AsmFuncCtx *ctx,
                                                     int32_t ta, const uint8_t *pre_buf, int32_t pre_len,
                                                     const uint8_t *field_name, int32_t field_len) {
  int32_t is_ln, nargs, arg_ref, expr_ko, arg_ty, atk, slen, sn;
  uint8_t sch[128], sym[40];
  struct glue_AsmFuncCtxCall *ly;
  struct ast_Module *mod_ref;
  if (!arena || !elf_ctx || !ctx || call_expr_ref <= 0 || (ta != 0 && ta != 1))
    return 0;
  if (!glue_asm_prefix_is_fmt_or_debug(pre_buf, pre_len))
    return 0;
  if (field_len == 7 && memcmp(field_name, "println", 7) == 0)
    is_ln = 1;
  else if (field_len == 5 && memcmp(field_name, "print", 5) == 0)
    is_ln = 0;
  else
    return 0;
  expr_ko = pipeline_expr_kind_ord_at(arena, call_expr_ref);
  if (expr_ko == GLUE_EXPR_METHOD_CALL_ORD) {
    nargs = pipeline_expr_method_call_num_args_at(arena, call_expr_ref);
    arg_ref = (nargs == 1) ? pipeline_expr_method_call_arg_ref(arena, call_expr_ref, 0) : 0;
  } else {
    nargs = pipeline_expr_call_num_args_at(arena, call_expr_ref);
    arg_ref = (nargs == 1) ? pipeline_expr_call_arg_ref(arena, call_expr_ref, 0) : 0;
  }
  if (nargs != 1 || arg_ref <= 0)
    return 0;
  if (pipeline_expr_kind_ord_at(arena, arg_ref) == GLUE_EXPR_STRING_LIT_ORD)
    return 0;
  arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
  if (arg_ty <= 0)
    return 0;
  atk = pipeline_type_kind_ord_at(arena, arg_ty);
  /* NAMED/ARRAY/SLICE(non-u8) → schema; u8[] build_schema -1 → u8_slc mid. */
  if (atk != 8 && atk != 10 && atk != 11)
    return 0;
  if (pipeline_expr_kind_ord_at(arena, arg_ref) != 3) /* VAR */
    return 0;
  ly = (struct glue_AsmFuncCtxCall *)ctx;
  mod_ref = ly ? ly->module_ref : 0;
  if (!mod_ref)
    return 0;
  slen = glue_asm_fmt_any_build_schema_c(mod_ref, arena, arg_ty, sch, 126, 0, 0);
  if (slen <= 0 || slen > 126)
    return 0;
  /*
   * Spill base to frame: aarch64 mov_rax_to_rbx also writes x1, and
   * mov_rax_to_arg_reg(1) overwrites x1 — mov_rbx_to_rax reads x1, not x19.
   * Frame spill is SHARED-safe (x86_64 + aarch64).
   */
  {
    int32_t spill;
    int32_t cur = (int32_t)ly->next_offset;
    if (cur < 16)
      cur = 16;
    spill = cur;
    ly->next_offset = cur + 8;
    if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0)
      return -1;
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, spill, ta) != 0)
      return -1;
    if (glue_asm_emit_jmp_skip_string_then_lea((uint8_t *)elf_ctx, ta, 1, sch, slen) != 0)
      return -1;
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0)
      return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill, ta) != 0)
      return -1;
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0)
      return -1;
  }
  if (is_ln) {
    memcpy(sym, "std_fmt_json_println_schema", 27);
    sn = 27;
  } else {
    memcpy(sym, "std_fmt_json_print_schema", 25);
    sn = 25;
  }
  if (glue_asm_enc_call_redirected(elf_ctx, sym, sn, ta) != 0)
    return -1;
  return 1;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_try_emit_fmt_string_lit_import_call_elf_c(struct ast_ASTArena *arena,
                                                                  struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                                  int32_t call_expr_ref, struct backend_AsmFuncCtx *ctx,
                                                                  int32_t ta, const uint8_t *pre_buf, int32_t pre_len,
                                                                  const uint8_t *field_name, int32_t field_len) {
  return glue_asm_try_emit_fmt_string_lit_import_call_elf_c_impl(arena, elf_ctx, call_expr_ref, ctx, ta, pre_buf, pre_len, field_name, field_len);
}
#endif


extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);

/* G.7 integer ret sxt/zxt (same as VAR load glue_load_var path). Product pure-asm. */
extern int32_t glue_enc_sxt_i32_result_to_rax_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t glue_enc_zxt_u32_result_to_rax_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t glue_enc_zxt_u8_result_to_rax_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);

/**
 * PLATFORM: SHARED — after CALL, canonicalize return into GPR x0/rax.
 * G.7 single authority name: glue_asm_harvest_call_ret_to_gpr_c
 *   (was static glue_asm_harvest_sse_call_ret_to_gpr_c; pure .x twin owns product PREFER).
 * Authority: pipeline_asm_call_return_type_kind_ord_c (resolved_type + dep map + dep-arena kind).
 * Type-driven only:
 *   · kind 14=f32 / 15=f64 → xmm0 harvest (x86_64 only; ta==0)
 *   · kind 0=I32 → sxtw/cdqe (AAPCS64 `mov w0,imm` zero-extends; pure-asm
 *     compares full x0 vs sign-ext -2 → false without this — hybrid
 *     ONLY=rt_run_compiler_parsed try_c returned 254)
 *   · kind 3=U32 → zxt; kind 1=BOOL / 2=U8 → zxt8
 * Cold seed twin when pure .x not linked; product PREFER uses .x body.
 */
#ifndef XLANG_BACKEND_CALL_DISPATCH_FROM_X
int32_t glue_asm_harvest_call_ret_to_gpr_c(struct ast_ASTArena *arena,
                                           struct platform_elf_ElfCodegenCtx *elf_ctx,
                                           int32_t call_expr_ref, int32_t ta) {
  int32_t kind;
  if (!arena || !elf_ctx || call_expr_ref <= 0)
    return 0;
  kind = pipeline_asm_call_return_type_kind_ord_c(arena, call_expr_ref);
  /* SSE harvest remains x86-only (xmm). */
  if (ta == 0) {
    if (kind == 14)
      return backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta);
    if (kind == 15)
      return backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta);
  }
  /* Integer GP ret: both x86_64 and arm64 (sxtw / cdqe / uxt). */
  if (kind == 0)
    return glue_enc_sxt_i32_result_to_rax_elf_c(elf_ctx, ta);
  if (kind == 3)
    return glue_enc_zxt_u32_result_to_rax_elf_c(elf_ctx, ta);
  if (kind == 1 || kind == 2)
    return glue_enc_zxt_u8_result_to_rax_elf_c(elf_ctx, ta);
  return 0;
}
#else
extern int32_t glue_asm_harvest_call_ret_to_gpr_c(struct ast_ASTArena *arena,
                                                  struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                  int32_t call_expr_ref, int32_t ta);
#endif

/**
 * 发射实参、call 目标符号，并按 ABI 回收 outgoing 栈区。
 */
/* G-02f-141：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-377 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t glue_asm_emit_call_with_cleanup_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                               int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta,
                                               int32_t nargs, uint8_t *cname, int32_t clen) {
  int32_t cleanup;
  int32_t host_mem = 0;
  /*
   * PLATFORM: MACOS|ARM64 — bare import CALL to std_ / core_ export wrappers
   * must use host-indirect MEMORY (lea into GP), same as import METHOD. Local
   * pure-to-pure keeps stack MEMORY (flag 0).
   */
  if (ta == 1 && glue_asm_call_sym_is_host_export_c(cname, clen))
    host_mem = 1;
  g_emit_call_args_arm64_host_mem = host_mem;
  if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, nargs) != 0) {
    g_emit_call_args_arm64_host_mem = 0;
    return -1;
  }
  g_emit_call_args_arm64_host_mem = 0;
  if (glue_asm_enc_call_redirected(elf_ctx, cname, clen, ta) != 0)
    return -1;
  /*
   * wave601: x86 cleanup must include MEMORY multi-word + pad, not nargs-only.
   * glue_sysv_x86_call_n_stack_c returns stack *words* (MEMORY ceil(sz/8)).
   */
  if (ta == 0 && arena && expr_ref > 0) {
    int32_t nw = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
    cleanup = nw * 8;
    if (nw > 0 && (nw & 1))
      cleanup += 8;
  } else if (ta == 1 && arena && expr_ref > 0) {
    /* wave603: arm64 cleanup twin of MEMORY-aware reserve (16-aligned).
     * Host-export: MEMORY is GP lea — omit MEMORY stack words. */
    int32_t nw = 0;
    int32_t gp_tmp = 0;
    int32_t j;
    int32_t reg_max_a = glue_asm_call_reg_max(1);
    for (j = 0; j < nargs; j++) {
      int32_t ar_j = pipeline_expr_call_arg_ref(arena, expr_ref, j);
      int32_t pty_j = glue_call_param_type_ref_at(arena, expr_ref, j);
      int32_t sz_j = glue_sysv_arg_byte_size_c(arena, ctx, pty_j, ar_j);
      int32_t u_j = glue_sysv_arg_gp_units_from_size_c(sz_j);
      int32_t w_j = glue_sysv_arg_stack_words_c(sz_j, u_j);
      if (glue_sysv_arg_is_memory_by_value_c(sz_j)) {
        if (host_mem) {
          if (gp_tmp + 1 <= reg_max_a)
            gp_tmp += 1;
        } else {
          nw += w_j;
        }
      } else if (u_j > 0 && gp_tmp + u_j <= reg_max_a)
        gp_tmp += u_j;
      else
        nw += w_j > 0 ? w_j : 1;
    }
    cleanup = nw * 8;
    if (cleanup > 0)
      cleanup = (cleanup + 15) & ~15;
  } else {
    cleanup = glue_asm_call_stack_cleanup_bytes(ta, nargs);
  }
  if (cleanup < 0)
    return -1;
  if (backend_enc_call_stack_cleanup_arch(elf_ctx, cleanup, ta) != 0)
    return -1;
  /* G.7: single harvest authority (pure .x / cold seed twin). */
  if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0)
    return -1;
  return 0;
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t glue_asm_emit_call_with_cleanup(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                               int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta,
                                               int32_t nargs, uint8_t *cname, int32_t clen) {
  return glue_asm_emit_call_with_cleanup_impl(arena, elf_ctx, expr_ref, ctx, ta, nargs, cname, clen);
}
#endif


/* CORE-001 asm fold: type-arg sidecars + layout size/align (G.7 twins of host-C). */
extern int32_t pipeline_expr_call_num_type_args_at(struct ast_ASTArena *arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_type_arg_ref_at(struct ast_ASTArena *arena, int32_t expr_ref, int32_t idx);
extern int32_t glue_type_size_simple(void *mod, struct ast_ASTArena *arena, int32_t ty_ref, int32_t depth);
extern int32_t glue_type_align_simple(void *mod, struct ast_ASTArena *arena, int32_t ty_ref, int32_t depth);

/**
 * CORE-001 asm twin of codegen_try_emit_size_align_of_call (host-C sizeof/_Alignof).
 *
 * Product surface (`core.types`): free `size_of<T>()` / import `types.size_of<T>()`.
 * Zero-arg generics skip mono mangling → bare `core_types_size_of` → BLD001 UNDEF on
 * default `-backend asm` -o. Fold here to imm in w0/eax (i32 return ABI).
 *
 * @return 1 folded, 0 not applicable, -1 emit error
 * PLATFORM: SHARED — layout via glue_type_size_simple / glue_type_align_simple
 */
static int32_t try_fold_size_align_of_call_elf(struct ast_ASTArena *arena,
                                               struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                               void *mod_ref, int32_t ta) {
  int32_t callee_ref;
  int32_t callee_ko;
  int32_t n_ta;
  int32_t ty_ref;
  int32_t is_size = 0;
  int32_t is_align = 0;
  int32_t nlen = 0;
  int32_t val = 0;
  uint8_t name[128];

  if (!arena || !elf_ctx || expr_ref <= 0)
    return 0;
  /* Zero value args; at least one type arg (turbofish). */
  if (pipeline_expr_call_num_args_at(arena, expr_ref) != 0)
    return 0;
  n_ta = pipeline_expr_call_num_type_args_at(arena, expr_ref);
  if (n_ta < 1)
    return 0;
  callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
  if (callee_ref <= 0)
    return 0;
  callee_ko = pipeline_expr_kind_ord_at(arena, callee_ref);
  memset(name, 0, sizeof(name));
  if (callee_ko == GLUE_EXPR_FIELD_ACCESS_ORD) {
    nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
    if (nlen <= 0 || nlen > 127)
      return 0;
    pipeline_expr_field_access_name_into(arena, callee_ref, name);
  } else if (callee_ko == 3) { /* EXPR_VAR */
    nlen = pipeline_expr_var_name_len(arena, callee_ref);
    if (nlen <= 0 || nlen > 127)
      return 0;
    pipeline_expr_var_name_into(arena, callee_ref, name);
  } else {
    return 0;
  }
  /* Exact bare name: size_of (7) / align_of (8). Not size_of_i32 etc. */
  if (nlen == 7 && name[0] == 's' && name[1] == 'i' && name[2] == 'z' && name[3] == 'e' && name[4] == '_' &&
      name[5] == 'o' && name[6] == 'f') {
    is_size = 1;
  } else if (nlen == 8 && name[0] == 'a' && name[1] == 'l' && name[2] == 'i' && name[3] == 'g' && name[4] == 'n' &&
             name[5] == '_' && name[6] == 'o' && name[7] == 'f') {
    is_align = 1;
  } else {
    return 0;
  }
  ty_ref = pipeline_expr_call_type_arg_ref_at(arena, expr_ref, 0);
  if (ty_ref <= 0)
    return 0;
  if (is_size)
    val = glue_type_size_simple(mod_ref, arena, ty_ref, 0);
  else if (is_align)
    val = glue_type_align_simple(mod_ref, arena, ty_ref, 0);
  else
    return 0;
  if (val < 0)
    return -1;
  if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, val, ta) != 0)
    return -1;
  return 1;
}

extern int32_t arch_x86_64_enc_enc_syscall(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_r10(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_r10_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
/* stage10 10.2.3: Windows x64 volatile scratch r11 in/lateout, pause and int3. */
extern int32_t arch_x86_64_enc_enc_mov_rax_to_r11(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_r11_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_pause(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_int3(struct platform_elf_ElfCodegenCtx *elf_ctx);
/* 10.4.1 slice1: atomic_load/store/cas i32 encoders (twin of backend_x86_64_enc_c.x). */
extern int32_t arch_x86_64_enc_enc_movl_mem_rax_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movl_mem_rcx_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_xchg_edx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movl_eax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_sete_al(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movzbl_al_eax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_eax_to_edx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movq_mem_rax_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_xchg_rdx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_rdx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movq_mem_rcx_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movq_rax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mfence(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_lfence(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_sfence(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_xchg_dx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_ax_to_dx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_movw_ax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_svc(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x8(struct platform_elf_ElfCodegenCtx *elf_ctx);
/* stage10 10.2.1 slice10: lateout/out("x8") → x0. */
extern int32_t arch_arm64_enc_enc_mov_x8_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
/* stage10 10.2.2 slice3: x9..x15 aarch64 volatile scratch in/lateout registers. */
extern int32_t arch_arm64_enc_enc_mov_rax_to_x9(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x9_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x10(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x10_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x11(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x11_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x12(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x12_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x13(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x13_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x14(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x14_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rax_to_x15(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x15_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_dmb_ish(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_dmb_ishld(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_dmb_ishst(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldar_w0_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_stlr_w1_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x0_to_x1(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x0_to_x2(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x0_to_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldr_w0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_str_w0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_w0_to_w4(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_casal_w0_w1_x2(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_cmp_w0_w4(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_cset_eq_w0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldar_x0_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_stlr_x1_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldr_x0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_str_x0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_x0_to_x4(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_casal_x0_x1_x2(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_cmp_x0_x4(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldarh_w0_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_stlrh_w1_x0(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_ldrh_w0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_strh_w0_x3(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t arch_arm64_enc_enc_casalh_w0_w1_x2(struct platform_elf_ElfCodegenCtx *elf_ctx);
extern int32_t pipeline_expr_method_call_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_method_call_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out64);
extern int32_t pipeline_expr_method_call_num_args_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);

/**
 * Stage 10 S3.1 slice 2 (10.1.1): raw_syscall0..6 ELF direct-encode lowering.
 * Twin of try_emit_raw_syscall_call_elf_c in backend_call_dispatch.x.
 * G.7: spill via glue_sysv_spill_rax_rdx_to_frame_c (same cursor as .x
 * next_offset@4 +16 stride). ta==0 → x86_64 syscall; ta==1 && !macho →
 * Linux ELF aarch64 svc #0 (nr x8, args x0..x5); Darwin Mach-O returns 0.
 * @return 1 emitted; 0 not applicable; -1 emit error
 * PLATFORM: LINUX x86_64 or LINUX aarch64 ELF runtime; SHARED emit code.
 */
static int32_t try_emit_raw_syscall_call_elf_c(struct ast_ASTArena *arena,
                                              struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                              struct backend_AsmFuncCtx *ctx, int32_t ta) {
  int32_t ko;
  int32_t nlen = 0;
  int32_t n_args = 0;
  int32_t is_method = 0;
  int32_t arity;
  int32_t i;
  int32_t j;
  int32_t k;
  int32_t arg_ref;
  int32_t off[8];
  uint8_t name[128];
  static const uint8_t pfx[11] = {114, 97, 119, 95, 115, 121, 115, 99, 97, 108, 108};

  if (!arena || !elf_ctx || !ctx || expr_ref <= 0)
    return 0;
  /* x86_64, or Linux ELF aarch64. Darwin Mach-O (x16 + svc #0x80) falls
   * through to the panic body — linux.raw_syscall is the Linux ABI. */
  if (ta != 0) {
    if (ta != 1)
      return 0;
    if (pipeline_elf_ctx_macho_leading_underscore((uint8_t *)elf_ctx) != 0)
      return 0;
  }
  ko = pipeline_expr_kind_ord_at(arena, expr_ref);
  memset(name, 0, sizeof(name));
  if (ko == GLUE_EXPR_METHOD_CALL_ORD) {
    nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (nlen != 12)
      return 0;
    pipeline_expr_method_call_name_into(arena, expr_ref, name);
    n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    is_method = 1;
  } else if (ko == GLUE_EXPR_CALL_ORD) {
    int32_t callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    int32_t cko;
    if (callee_ref <= 0)
      return 0;
    cko = pipeline_expr_kind_ord_at(arena, callee_ref);
    if (cko == GLUE_EXPR_FIELD_ACCESS_ORD) {
      nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
      if (nlen != 12)
        return 0;
      pipeline_expr_field_access_name_into(arena, callee_ref, name);
    } else if (cko == GLUE_EXPR_VAR_ORD) {
      nlen = pipeline_expr_var_name_len(arena, callee_ref);
      if (nlen != 12)
        return 0;
      pipeline_expr_var_name_into(arena, callee_ref, name);
    } else {
      return 0;
    }
    n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
  } else {
    return 0;
  }
  for (i = 0; i < 11; i++) {
    if (name[i] != pfx[i])
      return 0;
  }
  arity = (int32_t)name[11] - 48;
  if (arity < 0 || arity > 6)
    return 0;
  if (n_args != arity + 1)
    return 0;
  for (i = 0; i < n_args; i++) {
    if (is_method)
      arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
    else
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
    if (arg_ref == 0)
      return -1;
    if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0)
      return -1;
    /* G.7 complete existing spill (same +16 stride as .x next_offset@4). */
    off[i] = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
    if (off[i] < 0)
      return -1;
  }
  if (ta == 0) {
    for (j = 1; j < n_args; j++) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[j], ta) != 0)
        return -1;
      if (j == 1)
        k = 0;
      else if (j == 2)
        k = 1;
      else if (j == 3)
        k = 2;
      else if (j == 4)
        k = -1;
      else if (j == 5)
        k = 4;
      else
        k = 5;
      if (k == -1) {
        if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0)
          return -1;
      } else {
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, k, ta) != 0)
          return -1;
      }
    }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0)
      return -1;
    if (arch_x86_64_enc_enc_syscall(elf_ctx) != 0)
      return -1;
  } else {
    /* LINUX ELF aarch64: a2..a6 → x1..x5, nr → x8, a1 LAST → x0. */
    for (j = 2; j < n_args; j++) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[j], ta) != 0)
        return -1;
      if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, j - 1, ta) != 0)
        return -1;
    }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0)
      return -1;
    if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0)
      return -1;
    if (n_args > 1) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0)
        return -1;
    }
    if (arch_arm64_enc_enc_svc(elf_ctx) != 0)
      return -1;
  }
  return 1;
}

/**
 * Cap 10.7.1 slice18: twin of try_emit_va_cap_ov_select_elf_c (.x).
 * rax=class_cursor, rcx/x3=class_cell, header in r10/x8.
 * Post: rax=slot, rcx/x3=writeback (class or shared OV).
 * PLATFORM: SHARED emit · LINUX|x86_64 · LINUX|aarch64
 */
static int32_t try_emit_va_cap_ov_select_elf_c(struct platform_elf_ElfCodegenCtx *elf_ctx,
                                              struct backend_AsmFuncCtx *ctx, int32_t ta,
                                              int32_t is_fp, int32_t gp_n) {
  int32_t end_delta;
  uint8_t lbl_sv[64];
  uint8_t lbl_dn[64];
  int32_t n_sv;
  int32_t n_dn;
  extern int32_t pipeline_asm_emit_next_label_c(void *ctx, uint8_t *buf, int32_t buf_size);
  extern int32_t backend_enc_cmp_rbx_rax_arch(void *elf_ctx, int32_t ta);
  extern int32_t backend_enc_cmp_setcc_movzbl_arch(void *elf_ctx, int32_t cc, int32_t ta);
  extern int32_t backend_enc_test_eax_eax_arch(void *elf_ctx, int32_t ta);
  extern int32_t backend_enc_jz_arch(void *elf_ctx, uint8_t *label, int32_t label_len, int32_t ta);
  extern int32_t backend_enc_jmp_arch(void *elf_ctx, uint8_t *label, int32_t label_len, int32_t ta);
  extern int32_t backend_enc_label_arch(void *elf_ctx, uint8_t *name, int32_t name_len,
                                       int32_t is_func, int32_t ta);
  extern int32_t backend_enc_add_imm_to_rax_arch(void *elf_ctx, int32_t imm, int32_t ta);
  if (!elf_ctx || !ctx)
    return -1;
  if (gp_n < 6)
    gp_n = 6;
  end_delta = 24 + gp_n * 8;
  if (is_fp)
    end_delta += 64;
  memset(lbl_sv, 0, sizeof(lbl_sv));
  memset(lbl_dn, 0, sizeof(lbl_dn));
  n_sv = pipeline_asm_emit_next_label_c(ctx, lbl_sv, 64);
  n_dn = pipeline_asm_emit_next_label_c(ctx, lbl_dn, 64);
  if (n_sv <= 0 || n_dn <= 0)
    return -1;
  if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
    return -1;
  if (ta == 1) {
    if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0)
      return -1;
  } else if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) {
    return -1;
  }
  if (backend_enc_add_imm_to_rax_arch(elf_ctx, -end_delta, ta) != 0)
    return -1;
  if (backend_enc_cmp_rbx_rax_arch(elf_ctx, ta) != 0)
    return -1;
  if (backend_enc_cmp_setcc_movzbl_arch(elf_ctx, 3, ta) != 0)
    return -1;
  if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0)
    return -1;
  if (backend_enc_jz_arch(elf_ctx, lbl_sv, n_sv, ta) != 0)
    return -1;
  if (ta == 1) {
    if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0)
      return -1;
  } else if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) {
    return -1;
  }
  if (backend_enc_add_imm_to_rax_arch(elf_ctx, -16, ta) != 0)
    return -1;
  if (ta == 1) {
    if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0)
      return -1;
    if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0)
      return -1;
  } else {
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0)
      return -1;
    if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0)
      return -1;
  }
  if (backend_enc_jmp_arch(elf_ctx, lbl_dn, n_dn, ta) != 0)
    return -1;
  if (backend_enc_label_arch(elf_ctx, lbl_sv, n_sv, 0, ta) != 0)
    return -1;
  if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
    return -1;
  if (backend_enc_label_arch(elf_ctx, lbl_dn, n_dn, 0, ta) != 0)
    return -1;
  return 0;
}

/**
 * Cap 10.7.1 slice12–18: twin of try_emit_va_cap_builtin_call_elf_c (.x).
 * Cap-private VaList header (GP + FP + shared OV cursor) + GP/XMM spill.
 * x86_64: 6 SysV GP + 8 xmm; aarch64: 8 AAPCS GP + 8 v. typed va_arg<T>
 * including f32/f64. slice17–18: copy incoming stack extras once into OV[8];
 * va_arg past class_end consumes the shared overflow cursor.
 * PLATFORM: SHARED emit · LINUX|x86_64 · LINUX|aarch64
 */
static int32_t try_emit_va_cap_builtin_call_elf_c(struct ast_ASTArena *arena,
                                                  struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                  struct backend_AsmFuncCtx *ctx, int32_t ta) {
  int32_t ko;
  int32_t nlen = 0;
  int32_t n_args = 0;
  int32_t is_method = 0;
  int32_t which = 0;
  int32_t i;
  int32_t ap_ref;
  int32_t ap_off;
  int32_t save_off;
  int32_t np = 0;
  int32_t fi;
  int32_t k;
  int32_t gp_n = 6;
  int32_t fp_n = 8;
  int32_t np_gp = 0;
  int32_t np_fp = 0;
  int32_t gp_save;
  int32_t fp_save;
  int32_t ov;
  int32_t ov_n = 8;
  int32_t named_stk = 0;
  int32_t stk_pos = 0;
  int32_t pty;
  int32_t is_fp = 0;
  uint8_t name[128];
  struct glue_AsmFuncCtxCall *ly;
  static const uint8_t nm_start[8] = {118, 97, 95, 115, 116, 97, 114, 116};
  static const uint8_t nm_end[6] = {118, 97, 95, 101, 110, 100};
  static const uint8_t nm_argi32[10] = {118, 97, 95, 97, 114, 103, 95, 105, 51, 50};
  static const uint8_t nm_argi64[10] = {118, 97, 95, 97, 114, 103, 95, 105, 54, 52};
  static const uint8_t nm_argptr[10] = {118, 97, 95, 97, 114, 103, 95, 112, 116, 114};
  static const uint8_t nm_arg_typed[6] = {118, 97, 95, 97, 114, 103};
  extern int32_t glue_asm_local_var_stack_off_scoped(void *arena, void *ctx, int32_t var_expr_ref);
  extern int32_t pipeline_asm_emit_func_index_c(void);
  extern int32_t backend_enc_add_imm_to_rax_arch(void *elf_ctx, int32_t imm, int32_t ta);
  extern int32_t arch_x86_64_enc_enc_mov_edx_to_eax(void *elf_ctx);
  /* movq_mem_rax / mov_rax_to_r10 / mov_r10_to_rax: file-scope ElfCodegenCtx* decls above. */

  if (!arena || !elf_ctx || !ctx || expr_ref <= 0)
    return 0;
  if (ta != 0 && ta != 1)
    return 0;
  ko = pipeline_expr_kind_ord_at(arena, expr_ref);
  memset(name, 0, sizeof(name));
  if (ko == GLUE_EXPR_METHOD_CALL_ORD) {
    nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (nlen <= 0 || nlen > 127)
      return 0;
    pipeline_expr_method_call_name_into(arena, expr_ref, name);
    n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    is_method = 1;
  } else if (ko == GLUE_EXPR_CALL_ORD) {
    int32_t callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    int32_t cko;
    if (callee_ref <= 0)
      return 0;
    cko = pipeline_expr_kind_ord_at(arena, callee_ref);
    if (cko == GLUE_EXPR_FIELD_ACCESS_ORD) {
      nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
      if (nlen <= 0 || nlen > 127)
        return 0;
      pipeline_expr_field_access_name_into(arena, callee_ref, name);
    } else if (cko == GLUE_EXPR_VAR_ORD) {
      nlen = pipeline_expr_var_name_len(arena, callee_ref);
      if (nlen <= 0 || nlen > 127)
        return 0;
      pipeline_expr_var_name_into(arena, callee_ref, name);
    } else {
      return 0;
    }
    n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
  } else {
    return 0;
  }
  if (nlen == 8) {
    for (i = 0; i < 8; i++) {
      if (name[i] != nm_start[i]) { which = -1; break; }
    }
    if (which == 0) which = 1; else which = 0;
  }
  if (which == 0 && nlen == 6) {
    for (i = 0; i < 6; i++) {
      if (name[i] != nm_end[i]) { which = -1; break; }
    }
    if (which == 0) {
      which = 2;
    } else {
      which = 0;
      for (i = 0; i < 6; i++) {
        if (name[i] != nm_arg_typed[i]) { which = -1; break; }
      }
      if (which == 0) which = 6; else which = 0;
    }
  }
  if (which == 0 && nlen == 10) {
    for (i = 0; i < 10; i++) {
      if (name[i] != nm_argi32[i]) { which = -1; break; }
    }
    if (which == 0) {
      which = 3;
    } else {
      which = 0;
      for (i = 0; i < 10; i++) {
        if (name[i] != nm_argi64[i]) { which = -1; break; }
      }
      if (which == 0) {
        which = 4;
      } else {
        which = 0;
        for (i = 0; i < 10; i++) {
          if (name[i] != nm_argptr[i]) { which = -1; break; }
        }
        if (which == 0) which = 5; else which = 0;
      }
    }
  }
  if (which == 0)
    return 0;
  if (which == 2) {
    if (n_args != 1)
      return 0;
    return 1;
  }
  ly = (struct glue_AsmFuncCtxCall *)ctx;
  if (!ly)
    return -1;
  if (which == 1) {
    if (n_args != 2)
      return 0;
    ap_ref = is_method ? pipeline_expr_method_call_arg_ref(arena, expr_ref, 0)
                       : pipeline_expr_call_arg_ref(arena, expr_ref, 0);
    if (ap_ref <= 0)
      return -1;
    if (pipeline_expr_kind_ord_at(arena, ap_ref) != GLUE_EXPR_VAR_ORD)
      return 0;
    ap_off = glue_asm_local_var_stack_off_scoped(arena, ctx, ap_ref);
    if (ap_off < 16)
      return -1;
    fi = pipeline_asm_emit_func_index_c();
    if (ly->module_ref && fi >= 0)
      np = pipeline_module_func_num_params_at(ly->module_ref, fi);
    if (np < 0)
      np = 0;
    gp_n = (ta == 1) ? 8 : 6;
    fp_n = 8;
    np_gp = 0;
    np_fp = 0;
    for (k = 0; k < np; k++) {
      pty = 0;
      if (ly->module_ref && fi >= 0)
        pty = pipeline_module_func_param_type_ref_at(ly->module_ref, fi, k);
      if (glue_call_param_is_f32_c(arena, pty))
        np_fp++;
      else
        np_gp++;
    }
    named_stk = 0;
    if (np_gp > gp_n)
      named_stk += np_gp - gp_n;
    if (np_fp > fp_n)
      named_stk += np_fp - fp_n;
    if (np_gp > gp_n)
      np_gp = gp_n;
    if (np_fp > fp_n)
      np_fp = fp_n;
    save_off = ly->next_offset + 16;
    if (save_off < 16)
      save_off = 16;
    gp_save = save_off + 24;
    ov_n = 8;
    fp_save = gp_save + gp_n * 8;
    ov = fp_save + fp_n * 8;
    ly->next_offset = ov + ov_n * 8;
    for (k = 0; k < gp_n; k++) {
      if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, k, ta) != 0)
        return -1;
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, gp_save + k * 8, ta) != 0)
        return -1;
    }
    for (k = 0; k < fp_n; k++) {
      if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, k, ta) != 0)
        return -1;
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, fp_save + k * 8, ta) != 0)
        return -1;
    }
    /* Incoming stack extras → shared OV. PLATFORM: LINUX x86 [rbp+16];
     * aarch64 [x29,#frame+16] after x19 pad (param_home twin). */
    stk_pos = 16;
    if (ta == 1) {
      if (ly->frame_size > 16)
        stk_pos = ly->frame_size;
      stk_pos += 16;
    }
    stk_pos += named_stk * 8;
    for (k = 0; k < ov_n; k++) {
      if (ta == 1) {
        if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, stk_pos + k * 8, ta) != 0)
          return -1;
      } else {
        if (backend_enc_load_rbp_pos_to_rax_arch(elf_ctx, stk_pos + k * 8, ta) != 0)
          return -1;
      }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ov + k * 8, ta) != 0)
        return -1;
    }
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, gp_save + np_gp * 8, ta) != 0)
      return -1;
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off, ta) != 0)
      return -1;
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, fp_save + np_fp * 8, ta) != 0)
      return -1;
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off + 8, ta) != 0)
      return -1;
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ov, ta) != 0)
      return -1;
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off + 16, ta) != 0)
      return -1;
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, save_off, ta) != 0)
      return -1;
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
      return -1;
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ap_off, ta) != 0)
      return -1;
    if (ta == 1) {
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0)
        return -1;
      if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
        return -1;
      if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0)
        return -1;
      return 1;
    }
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0)
      return -1;
    if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
      return -1;
    if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0)
      return -1;
    return 1;
  }
  /* which == 6: typed va_arg<T>(ap) → classify T into 3/4/5/7/8. Twin .x. */
  if (which == 6) {
    int32_t ty_ref;
    int32_t tk;
    int32_t tsz;
    if (n_args != 1)
      return 0;
    if (pipeline_expr_call_num_type_args_at(arena, expr_ref) < 1)
      return 0;
    ty_ref = pipeline_expr_call_type_arg_ref_at(arena, expr_ref, 0);
    if (ty_ref <= 0)
      return 0;
    tk = pipeline_type_kind_ord_at(arena, ty_ref);
    if (tk == 14)
      which = 7;
    else if (tk == 15)
      which = 8;
    else {
      tsz = glue_type_size_simple(ly->module_ref, arena, ty_ref, 0);
      if (tk == 9)
        which = 5;
      else if (tsz >= 8)
        which = 4;
      else
        which = 3;
    }
  }
  /* 3=i32 4=i64 5=ptr (GP) · 7=f32 8=f64 (FP) */
  if (which < 3 || which == 6 || which > 8)
    return 0;
  is_fp = (which >= 7);
  if (n_args != 1)
    return 0;
  ap_ref = is_method ? pipeline_expr_method_call_arg_ref(arena, expr_ref, 0)
                     : pipeline_expr_call_arg_ref(arena, expr_ref, 0);
  if (ap_ref <= 0)
    return -1;
  if (pipeline_expr_kind_ord_at(arena, ap_ref) != GLUE_EXPR_VAR_ORD)
    return 0;
  ap_off = glue_asm_local_var_stack_off_scoped(arena, ctx, ap_ref);
  if (ap_off < 16)
    return -1;
  gp_n = (ta == 1) ? 8 : 6;
  if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ap_off, ta) != 0)
    return -1;
  if (ta == 1) {
    if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0)
      return -1;
    if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0)
      return -1;
    if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0)
      return -1;
    /* header+8 rbp-off = lower addr = pointer-8. Twin .x. */
    if (is_fp && backend_enc_add_imm_to_rax_arch(elf_ctx, -8, ta) != 0)
      return -1;
    if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0)
      return -1;
    if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0)
      return -1;
    if (try_emit_va_cap_ov_select_elf_c(elf_ctx, ctx, ta, is_fp, gp_n) != 0)
      return -1;
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
      return -1;
    if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 1, 0, ta) != 0)
      return -1;
    if (arch_arm64_enc_enc_mov_x0_to_x4(elf_ctx) != 0)
      return -1;
    if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
      return -1;
    if (backend_enc_add_imm_to_rax_arch(elf_ctx, -8, ta) != 0)
      return -1;
    if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0)
      return -1;
    if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, 4, ta) != 0)
      return -1;
    return 1;
  }
  if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0)
    return -1;
  if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0)
    return -1;
  if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0)
    return -1;
  /* header+8 rbp-off = lower addr = pointer-8. Twin .x. */
  if (is_fp && backend_enc_add_imm_to_rax_arch(elf_ctx, -8, ta) != 0)
    return -1;
  if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0)
    return -1;
  if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0)
    return -1;
  if (try_emit_va_cap_ov_select_elf_c(elf_ctx, ctx, ta, is_fp, gp_n) != 0)
    return -1;
  if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
    return -1;
  if (which == 3 || which == 7) {
    if (arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx) != 0)
      return -1;
    if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0)
      return -1;
  } else {
    if (arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx) != 0)
      return -1;
    if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0)
      return -1;
  }
  if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
    return -1;
  /* Spill layout: save+k*8 is rbp-(save_off+k*8); next slot is lower addr → -8. */
  if (backend_enc_add_imm_to_rax_arch(elf_ctx, -8, ta) != 0)
    return -1;
  if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0)
    return -1;
  if (which == 3 || which == 7) {
    if (arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx) != 0)
      return -1;
  } else {
    if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0)
      return -1;
  }
  return 1;
}

/**
 * Stage 10 (10.4.1) slice1–3 + (10.4.2) fences + arm64 i32/fence:
 * Twin of try_emit_atomic_builtin_call_elf_c in backend_call_dispatch.x.
 * ta==0 x86_64; ta==1 aarch64 (i32+fence); other → 0.
 * @return 1 emitted; 0 not applicable; -1 emit error
 * PLATFORM: SHARED emit · LINUX|x86_64 / aarch64 runtime
 */
static int32_t try_emit_atomic_builtin_call_elf_c(struct ast_ASTArena *arena,
                                                  struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t expr_ref,
                                                  struct backend_AsmFuncCtx *ctx, int32_t ta) {
  int32_t ko;
  int32_t nlen = 0;
  int32_t n_args = 0;
  int32_t is_method = 0;
  int32_t which = 0;
  int32_t i;
  int32_t arg_ref;
  int32_t off[4];
  uint8_t name[128];
  static const uint8_t nm_load32[15] = {97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 51, 50};
  static const uint8_t nm_store32[16] = {97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 51, 50};
  static const uint8_t nm_cas32[14] = {97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 51, 50};
  static const uint8_t nm_load64[15] = {97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 54, 52};
  static const uint8_t nm_store64[16] = {97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 54, 52};
  static const uint8_t nm_cas64[14] = {97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 54, 52};
  static const uint8_t nm_load16[15] = {97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 49, 54};
  static const uint8_t nm_store16[16] = {97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 49, 54};
  static const uint8_t nm_cas16[14] = {97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 49, 54};
  static const uint8_t nm_fseq[20] = {97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 115, 101, 113, 95, 99, 115, 116};
  static const uint8_t nm_facq[20] = {97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 97, 99, 113, 117, 105, 114, 101};
  static const uint8_t nm_frel[20] = {97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 114, 101, 108, 101, 97, 115, 101};

  if (!arena || !elf_ctx || !ctx || expr_ref <= 0)
    return 0;
  if (ta != 0 && ta != 1)
    return 0;
  ko = pipeline_expr_kind_ord_at(arena, expr_ref);
  memset(name, 0, sizeof(name));
  if (ko == GLUE_EXPR_METHOD_CALL_ORD) {
    nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (nlen <= 0 || nlen > 127)
      return 0;
    pipeline_expr_method_call_name_into(arena, expr_ref, name);
    n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    is_method = 1;
  } else if (ko == GLUE_EXPR_CALL_ORD) {
    int32_t callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    int32_t cko;
    if (callee_ref <= 0)
      return 0;
    cko = pipeline_expr_kind_ord_at(arena, callee_ref);
    if (cko == GLUE_EXPR_FIELD_ACCESS_ORD) {
      nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
      if (nlen <= 0 || nlen > 127)
        return 0;
      pipeline_expr_field_access_name_into(arena, callee_ref, name);
    } else if (cko == GLUE_EXPR_VAR_ORD) {
      nlen = pipeline_expr_var_name_len(arena, callee_ref);
      if (nlen <= 0 || nlen > 127)
        return 0;
      pipeline_expr_var_name_into(arena, callee_ref, name);
    } else {
      return 0;
    }
    n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
  } else {
    return 0;
  }
  which = 0;
  if (nlen == 15) {
    for (i = 0; i < 15; i++) {
      if (name[i] != nm_load32[i]) { which = -1; break; }
    }
    if (which == 0) which = 1; else which = 0;
    if (which == 0) {
      for (i = 0; i < 15; i++) {
        if (name[i] != nm_load64[i]) { which = -1; break; }
      }
      if (which == 0) which = 4; else which = 0;
    }
    if (which == 0) {
      for (i = 0; i < 15; i++) {
        if (name[i] != nm_load16[i]) { which = -1; break; }
      }
      if (which == 0) which = 10; else which = 0;
    }
  }
  if (which == 0 && nlen == 16) {
    for (i = 0; i < 16; i++) {
      if (name[i] != nm_store32[i]) { which = -1; break; }
    }
    if (which == 0) which = 2; else which = 0;
    if (which == 0) {
      for (i = 0; i < 16; i++) {
        if (name[i] != nm_store64[i]) { which = -1; break; }
      }
      if (which == 0) which = 5; else which = 0;
    }
    if (which == 0) {
      for (i = 0; i < 16; i++) {
        if (name[i] != nm_store16[i]) { which = -1; break; }
      }
      if (which == 0) which = 11; else which = 0;
    }
  }
  if (which == 0 && nlen == 14) {
    for (i = 0; i < 14; i++) {
      if (name[i] != nm_cas32[i]) { which = -1; break; }
    }
    if (which == 0) which = 3; else which = 0;
    if (which == 0) {
      for (i = 0; i < 14; i++) {
        if (name[i] != nm_cas64[i]) { which = -1; break; }
      }
      if (which == 0) which = 6; else which = 0;
    }
    if (which == 0) {
      for (i = 0; i < 14; i++) {
        if (name[i] != nm_cas16[i]) { which = -1; break; }
      }
      if (which == 0) which = 12; else which = 0;
    }
  }

  if (which == 0 && nlen == 20) {
    for (i = 0; i < 20; i++) {
      if (name[i] != nm_fseq[i]) { which = -1; break; }
    }
    if (which == 0) which = 7; else which = 0;
    if (which == 0) {
      for (i = 0; i < 20; i++) {
        if (name[i] != nm_facq[i]) { which = -1; break; }
      }
      if (which == 0) which = 8; else which = 0;
    }
    if (which == 0) {
      for (i = 0; i < 20; i++) {
        if (name[i] != nm_frel[i]) { which = -1; break; }
      }
      if (which == 0) which = 9; else which = 0;
    }
  }
  if (which == 0)
    return 0;
  if ((which == 1 || which == 4 || which == 10) && n_args != 1)
    return 0;
  if ((which == 2 || which == 5 || which == 11) && n_args != 2)
    return 0;
  if ((which == 3 || which == 6 || which == 12) && n_args != 3)
    return 0;
  if ((which == 7 || which == 8 || which == 9) && n_args != 0)
    return 0;
  for (i = 0; i < n_args; i++) {
    if (is_method)
      arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
    else
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
    if (arg_ref == 0)
      return -1;
    if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0)
      return -1;
    off[i] = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
    if (off[i] < 0)
      return -1;
  }
  if (ta == 1) {
    if (which == 1) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_ldar_w0_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 4) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_ldar_x0_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 10) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_ldarh_w0_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 2) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_stlr_w1_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 5) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_stlr_x1_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 11) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_stlrh_w1_x0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 3) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_ldr_w0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_mov_w0_to_w4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_casal_w0_w1_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_str_w0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cmp_w0_w4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 6) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_casal_x0_x1_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cmp_x0_x4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 12) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) return -1;
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
      if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_ldrh_w0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_mov_w0_to_w4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_casalh_w0_w1_x2(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_strh_w0_x3(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cmp_w0_w4(elf_ctx) != 0) return -1;
      if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) return -1;
      return 1;
    }
    if (which == 7 || which == 8 || which == 9) {
      if (which == 7) {
        if (arch_arm64_enc_enc_dmb_ish(elf_ctx) != 0) return -1;
      } else if (which == 8) {
        if (arch_arm64_enc_enc_dmb_ishld(elf_ctx) != 0) return -1;
      } else {
        if (arch_arm64_enc_enc_dmb_ishst(elf_ctx) != 0) return -1;
      }
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) return -1;
      return 1;
    }
    return 0;
  }
  if (which == 1) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 4) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 10) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 2) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_xchg_edx_mem_rax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 5) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_xchg_rdx_mem_rax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 11) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_xchg_dx_mem_rax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 3) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) return -1;
    if (arch_x86_64_enc_enc_movl_mem_rcx_to_eax(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_movl_eax_to_mem_rcx(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 12) {
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) return -1;
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) return -1;
    if (arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_movw_ax_to_mem_rcx(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) return -1;
    if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) return -1;
    return 1;
  }
  if (which == 7 || which == 8 || which == 9) {
    if (which == 7) {
      if (arch_x86_64_enc_enc_mfence(elf_ctx) != 0) return -1;
    } else if (which == 8) {
      if (arch_x86_64_enc_enc_lfence(elf_ctx) != 0) return -1;
    } else {
      if (arch_x86_64_enc_enc_sfence(elf_ctx) != 0) return -1;
    }
    if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) return -1;
    return 1;
  }
  /* cas i64 */
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) return -1;
  if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) return -1;
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) return -1;
  if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) return -1;
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) return -1;
  if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) return -1;
  if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0) return -1;
  if (arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(elf_ctx) != 0) return -1;
  if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0) return -1;
  if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) return -1;
  if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) return -1;
  return 1;
}

/**
 * Stage10 10.2.1 slice2–4: twin helpers + try_emit (in / out / syscall).
 * int_val = num_in; outs store rax→local VAR (rax/eax/x0 only).
 * PLATFORM: SHARED.
 */
static int32_t pipeline_asm_inline_in_reg_mov_kind_c(const uint8_t *reg, int32_t ta) {
  if (!reg)
    return -1;
  if (ta == 0) {
    if (reg[0] == 'r' && reg[1] == 'a' && reg[2] == 'x' && reg[3] == 0)
      return 0;
    if (reg[0] == 'e' && reg[1] == 'a' && reg[2] == 'x' && reg[3] == 0)
      return 0;
    if (reg[0] == 'r' && reg[1] == 'd' && reg[2] == 'i' && reg[3] == 0)
      return 1;
    if (reg[0] == 'e' && reg[1] == 'd' && reg[2] == 'i' && reg[3] == 0)
      return 1;
    if (reg[0] == 'r' && reg[1] == 's' && reg[2] == 'i' && reg[3] == 0)
      return 2;
    if (reg[0] == 'e' && reg[1] == 's' && reg[2] == 'i' && reg[3] == 0)
      return 2;
    if (reg[0] == 'r' && reg[1] == 'd' && reg[2] == 'x' && reg[3] == 0)
      return 3;
    if (reg[0] == 'e' && reg[1] == 'd' && reg[2] == 'x' && reg[3] == 0)
      return 3;
    if (reg[0] == 'r' && reg[1] == 'c' && reg[2] == 'x' && reg[3] == 0)
      return 4;
    if (reg[0] == 'e' && reg[1] == 'c' && reg[2] == 'x' && reg[3] == 0)
      return 4;
    if (reg[0] == 'r' && reg[1] == '8' && reg[2] == 0)
      return 5;
    if (reg[0] == 'r' && reg[1] == '8' && reg[2] == 'd' && reg[3] == 0)
      return 5;
    if (reg[0] == 'r' && reg[1] == '9' && reg[2] == 0)
      return 6;
    if (reg[0] == 'r' && reg[1] == '9' && reg[2] == 'd' && reg[3] == 0)
      return 6;
    if (reg[0] == 'r' && reg[1] == '1' && reg[2] == '0' && reg[3] == 0)
      return 101;
    if (reg[0] == 'r' && reg[1] == '1' && reg[2] == '0' && reg[3] == 'd' && reg[4] == 0)
      return 101;
    /* Stage10 10.2.3: r11 / r11d Windows x64 / SysV volatile scratch */
    if (reg[0] == 'r' && reg[1] == '1' && reg[2] == '1' && reg[3] == 0)
      return 103;
    if (reg[0] == 'r' && reg[1] == '1' && reg[2] == '1' && reg[3] == 'd' && reg[4] == 0)
      return 103;
    if (reg[0] == 'r' && reg[1] == 'b' && reg[2] == 'x' && reg[3] == 0)
      return 100;
    if (reg[0] == 'e' && reg[1] == 'b' && reg[2] == 'x' && reg[3] == 0)
      return 100;
    return -1;
  }
  if (ta == 1) {
    /* Stage10 10.2.2 slice1-3: aarch64 x0..x15 and w0..w15 registers. */
    if (reg[0] == 'x' || reg[0] == 'w') {
      if (reg[2] == 0) {
        if (reg[1] == '0') return 0;
        if (reg[1] == '1') return 2;
        if (reg[1] == '2') return 3;
        if (reg[1] == '3') return 4;
        if (reg[1] == '4') return 5;
        if (reg[1] == '5') return 6;
        if (reg[1] == '6') return 7;
        if (reg[1] == '7') return 8;
        if (reg[1] == '8') return 102;
        if (reg[1] == '9') return 109;
      } else if (reg[3] == 0 && reg[1] == '1') {
        if (reg[2] == '0') return 110;
        if (reg[2] == '1') return 111;
        if (reg[2] == '2') return 112;
        if (reg[2] == '3') return 113;
        if (reg[2] == '4') return 114;
        if (reg[2] == '5') return 115;
      }
    }
    return -1;
  }
  return -1;
}

static int32_t pipeline_asm_inline_regpack_field_c(const uint8_t *pack, int32_t idx, uint8_t *out,
                                                   int32_t out_cap) {
  int32_t i = 0;
  int32_t field = 0;
  int32_t o = 0;
  uint8_t c;
  if (!pack || !out || out_cap < 2 || idx < 0)
    return -1;
  for (;;) {
    c = pack[i];
    if (field == idx) {
      if (c == 0 || c == ',') {
        if (o >= out_cap)
          return -1;
        out[o] = 0;
        return 0;
      }
      if (o + 1 >= out_cap)
        return -1;
      out[o++] = c;
      i++;
    } else {
      if (c == 0)
        return -1;
      if (c == ',') {
        field++;
        i++;
      } else {
        i++;
      }
    }
  }
}

extern int32_t asm_ctx_local_find_offset_scoped(void *ctx, void *arena, uint8_t *name, int32_t name_len);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_var_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out);
extern int32_t backend_enc_store_rax_to_rbp_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off,
                                                 int32_t ta);

/**
 * Stage10 10.2.1: twin of pipeline_asm_try_emit_inline_asm_expr_elf_c (.x).
 * Templates: "nop" / "syscall"; in + lateout/out (VAR or "_" clobber).
 * Slice12: preserves_flags → pushfq/popfq around template (x86).
 * Slice13: nostack skips that wrap (pushfq uses stack); alone accept-only.
 * Slice14: nomem forbids out/lateout local stores (`_` discard OK).
 * Slice15: readonly same store forbid. Slice16: pure same + pure+noreturn fail.
 * PLATFORM: SHARED · LINUX|x86_64 gold out-GP.
 */
int32_t pipeline_asm_try_emit_inline_asm_expr_elf_c(struct ast_ASTArena *arena,
                                                    struct platform_elf_ElfCodegenCtx *elf_ctx,
                                                    int32_t expr_ref, struct backend_AsmFuncCtx *ctx,
                                                    int32_t ta) {
  int32_t ko;
  uint8_t tmpl[128];
  uint8_t nop1 = 0x90u;
  uint8_t a64[4];
  int32_t nargs;
  int32_t num_in;
  int32_t arg_ref;
  uint8_t pack[128];
  uint8_t reg[32];
  uint8_t vname[128];
  int32_t i;
  int32_t mk;
  int32_t erc;
  int32_t is_nop = 0;
  int32_t is_sys = 0;
  int32_t is_pause = 0;
  int32_t is_int3 = 0;
  int32_t pko;
  int32_t vlen;
  int32_t voff;
  int32_t opt_bits;
  uint8_t pfq;
  if (!arena || !elf_ctx || expr_ref <= 0)
    return -1;
  ko = pipeline_expr_kind_ord_at(arena, expr_ref);
  if (ko != 60)
    return -1;
  pipeline_expr_var_name_into(arena, expr_ref, tmpl);
  if (tmpl[0] == (uint8_t)'n' && tmpl[1] == (uint8_t)'o' && tmpl[2] == (uint8_t)'p' && tmpl[3] == 0)
    is_nop = 1;
  if (tmpl[0] == (uint8_t)'s' && tmpl[1] == (uint8_t)'y' && tmpl[2] == (uint8_t)'s'
      && tmpl[3] == (uint8_t)'c' && tmpl[4] == (uint8_t)'a' && tmpl[5] == (uint8_t)'l'
      && tmpl[6] == (uint8_t)'l' && tmpl[7] == 0)
    is_sys = 1;
  if (tmpl[0] == (uint8_t)'p' && tmpl[1] == (uint8_t)'a' && tmpl[2] == (uint8_t)'u'
      && tmpl[3] == (uint8_t)'s' && tmpl[4] == (uint8_t)'e' && tmpl[5] == 0)
    is_pause = 1;
  if (tmpl[0] == (uint8_t)'i' && tmpl[1] == (uint8_t)'n' && tmpl[2] == (uint8_t)'t'
      && tmpl[3] == (uint8_t)'3' && tmpl[4] == 0)
    is_int3 = 1;
  if (!is_nop && !is_sys && !is_pause && !is_int3)
    return -1;
  nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
  if (nargs < 0 || nargs > 6)
    return -1;
  num_in = pipeline_expr_int_val_at(arena, expr_ref);
  if (num_in < 0 || num_in > nargs)
    return -1;
  /* Options bitfield once (slice8–16 options family). */
  opt_bits = pipeline_expr_call_num_type_args_at(arena, expr_ref);
  /* Slice16: pure + noreturn conflict (side effect beyond outputs). */
  if ((opt_bits & 16) != 0 && (opt_bits & 32) != 0)
    return -1;
  if (nargs > 0) {
    if (!ctx)
      return -1;
    pipeline_expr_method_call_name_into(arena, expr_ref, pack);
    for (i = 0; i < num_in; i++) {
      if (pipeline_asm_inline_regpack_field_c(pack, i, reg, 32) != 0)
        return -1;
      mk = pipeline_asm_inline_in_reg_mov_kind_c(reg, ta);
      if (mk < 0)
        return -1;
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      if (arg_ref <= 0)
        return -1;
      erc = pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, arg_ref, ctx, ta);
      if (erc != 0)
        return -1;
      if (mk >= 1 && mk <= 8) {
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, mk - 1, ta) != 0)
          return -1;
      }
      if (mk == 100) {
        if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
          return -1;
      }
      if (mk == 101) {
        if (ta != 0)
          return -1;
        if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0)
          return -1;
      }
      if (mk == 102) {
        if (ta != 1)
          return -1;
        if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0)
          return -1;
      }
      /* Stage10 10.2.3: r11 Windows x64 / SysV volatile scratch in-reg */
      if (mk == 103) {
        if (ta != 0)
          return -1;
        if (arch_x86_64_enc_enc_mov_rax_to_r11(elf_ctx) != 0)
          return -1;
      }
      /* Stage10 10.2.2 slice3: x9..x15 aarch64 volatile scratch in-reg */
      if (mk >= 109 && mk <= 115) {
        if (ta != 1)
          return -1;
        if (mk == 109) {
          if (arch_arm64_enc_enc_mov_rax_to_x9(elf_ctx) != 0) return -1;
        } else if (mk == 110) {
          if (arch_arm64_enc_enc_mov_rax_to_x10(elf_ctx) != 0) return -1;
        } else if (mk == 111) {
          if (arch_arm64_enc_enc_mov_rax_to_x11(elf_ctx) != 0) return -1;
        } else if (mk == 112) {
          if (arch_arm64_enc_enc_mov_rax_to_x12(elf_ctx) != 0) return -1;
        } else if (mk == 113) {
          if (arch_arm64_enc_enc_mov_rax_to_x13(elf_ctx) != 0) return -1;
        } else if (mk == 114) {
          if (arch_arm64_enc_enc_mov_rax_to_x14(elf_ctx) != 0) return -1;
        } else if (mk == 115) {
          if (arch_arm64_enc_enc_mov_rax_to_x15(elf_ctx) != 0) return -1;
        }
      }
    }
    /* Slice14–16: nomem/readonly/pure forbid out/lateout stores to locals. */
    if ((opt_bits & 28) != 0) {
      for (i = num_in; i < nargs; i++) {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref <= 0)
          return -1;
        pko = pipeline_expr_kind_ord_at(arena, arg_ref);
        if (pko != 3)
          return -1;
        vlen = pipeline_expr_var_name_len(arena, arg_ref);
        if (vlen <= 0 || vlen > 127)
          return -1;
        pipeline_expr_var_name_into(arena, arg_ref, vname);
        /* `_` clobber discard does not store — allowed. */
        if (!(vlen == 1 && vname[0] == (uint8_t)'_'))
          return -1;
      }
    }
  }
  /* Slice12/13: preserves_flags wrap unless nostack (pushfq uses stack). */
  if ((opt_bits & 2) != 0 && (opt_bits & 1) == 0 && ta == 0) {
    pfq = 0x9cu;
    if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, &pfq, 1) != 0)
      return -1;
  }
  if (is_nop) {
    if (ta == 0) {
      if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, &nop1, 1) != 0)
        return -1;
    } else if (ta == 1) {
      a64[0] = 0x1fu;
      a64[1] = 0x20u;
      a64[2] = 0x03u;
      a64[3] = 0xd5u;
      if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, a64, 4) != 0)
        return -1;
    } else {
      return -1;
    }
  } else if (is_pause) {
    if (ta == 0) {
      if (arch_x86_64_enc_enc_pause(elf_ctx) != 0)
        return -1;
    } else if (ta == 1) {
      /* aarch64 yield: 0xd503203f */
      a64[0] = 0x3fu;
      a64[1] = 0x20u;
      a64[2] = 0x03u;
      a64[3] = 0xd5u;
      if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, a64, 4) != 0)
        return -1;
    } else {
      return -1;
    }
  } else if (is_int3) {
    if (ta == 0) {
      if (arch_x86_64_enc_enc_int3(elf_ctx) != 0)
        return -1;
    } else if (ta == 1) {
      /* aarch64 brk #0: 0xd4200000 */
      a64[0] = 0x00u;
      a64[1] = 0x00u;
      a64[2] = 0x20u;
      a64[3] = 0xd4u;
      if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, a64, 4) != 0)
        return -1;
    } else {
      return -1;
    }
  } else {
    if (ta == 0) {
      if (arch_x86_64_enc_enc_syscall(elf_ctx) != 0)
        return -1;
    } else if (ta == 1) {
      if (arch_arm64_enc_enc_svc(elf_ctx) != 0)
        return -1;
    } else {
      return -1;
    }
  }
  /* Slice12/13: popfq after template unless nostack. */
  if ((opt_bits & 2) != 0 && (opt_bits & 1) == 0 && ta == 0) {
    pfq = 0x9du;
    if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, &pfq, 1) != 0)
      return -1;
  }
  for (i = num_in; i < nargs; i++) {
    if (!ctx)
      return -1;
    if (pipeline_asm_inline_regpack_field_c(pack, i, reg, 32) != 0)
      return -1;
    mk = pipeline_asm_inline_in_reg_mov_kind_c(reg, ta);
    if (mk < 0)
      return -1;
    arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
    if (arg_ref <= 0)
      return -1;
    pko = pipeline_expr_kind_ord_at(arena, arg_ref);
    if (pko != 3)
      return -1;
    vlen = pipeline_expr_var_name_len(arena, arg_ref);
    if (vlen <= 0 || vlen > 127)
      return -1;
    pipeline_expr_var_name_into(arena, arg_ref, vname);
    /* Slice6: VAR "_" = clobber discard — validate reg, no store. */
    if (vlen == 1 && vname[0] == (uint8_t)'_')
      continue;
    voff = asm_ctx_local_find_offset_scoped(ctx, arena, vname, vlen);
    if (voff < 0)
      return -1;
    /* mk==0: already in rax/x0. */
    if (mk >= 1 && mk <= 8) {
      if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, mk - 1, ta) != 0)
        return -1;
    }
    if (mk == 100) {
      if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0)
        return -1;
    }
    if (mk == 101) {
      if (ta != 0)
        return -1;
      if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0)
        return -1;
    }
    /* Slice10: lateout/out("x8") → x0 before store (mirror r10). */
    if (mk == 102) {
      if (ta != 1)
        return -1;
      if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0)
        return -1;
    }
    /* Stage10 10.2.3: lateout/out("r11") → rax before store */
    if (mk == 103) {
      if (ta != 0)
        return -1;
      if (arch_x86_64_enc_enc_mov_r11_to_rax(elf_ctx) != 0)
        return -1;
    }
    /* Stage10 10.2.2 slice3: lateout/out("x9".."x15") → x0 before store */
    if (mk >= 109 && mk <= 115) {
      if (ta != 1)
        return -1;
      if (mk == 109) {
        if (arch_arm64_enc_enc_mov_x9_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 110) {
        if (arch_arm64_enc_enc_mov_x10_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 111) {
        if (arch_arm64_enc_enc_mov_x11_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 112) {
        if (arch_arm64_enc_enc_mov_x12_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 113) {
        if (arch_arm64_enc_enc_mov_x13_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 114) {
        if (arch_arm64_enc_enc_mov_x14_to_rax(elf_ctx) != 0) return -1;
      } else if (mk == 115) {
        if (arch_arm64_enc_enc_mov_x15_to_rax(elf_ctx) != 0) return -1;
      }
    }
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, voff, ta) != 0)
      return -1;
  }
  /* Slice8: options(noreturn) → ud2 after asm (trap if template returns). */
  /* Slice9: stamp diverged so parent block skips unreachable stmts/final_expr. */
  {
    uint8_t ud2[2];
    if ((opt_bits & 32) != 0) {
      if (ta != 0)
        return -1;
      ud2[0] = 0x0fu;
      ud2[1] = 0x0bu;
      if (pipeline_elf_ctx_append_bytes((uint8_t *)elf_ctx, ud2, 2) != 0)
        return -1;
      glue_asm_block_diverged_set(1);
    }
  }
  return 0;
}

/**
 * EXPR_CALL ELF 全路径：IMPORT_BINDING / whole-import FIELD_ACCESS callee、VAR callee、try_inline。
 * 供 pipeline_asm_emit_expr_elf_rec 与 backend.x emit_expr_elf_call 委托。
 */
/* G-02f-147：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-376 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t pipeline_asm_emit_call_elf_c_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                     int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta) {
  struct glue_AsmFuncCtxCall *ly;
  struct ast_Module *mod_ref;
  int32_t callee_ref;
  int32_t callee_ko;
  int32_t nargs;
  int32_t inline_rc;
  uint8_t cname[128];
  int32_t clen;

  callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
  if (callee_ref <= 0)
    return -1;
  ly = (struct glue_AsmFuncCtxCall *)ctx;
  mod_ref = ly ? ly->module_ref : 0;
  callee_ko = pipeline_expr_kind_ord_at(arena, callee_ref);
  backend_call_debugf("emit call elf callee_ko=%d call_nargs=%d", (int)callee_ko,
                      (int)pipeline_expr_call_num_args_at(arena, expr_ref));

  /* CORE-001: size_of<T>/align_of<T> → imm (before import mangle → core_types_size_of). */
  {
    int32_t sa_rc = try_fold_size_align_of_call_elf(arena, elf_ctx, expr_ref, mod_ref, ta);
    if (sa_rc < 0)
      return -1;
    if (sa_rc > 0)
      return 0;
  }
  /* stage10 S3.1 slice2 (10.1.1): raw_syscall0..6 → direct syscall
   * (before import mangle; same slot as the size_of fold). */
  {
    int32_t rs_rc = try_emit_raw_syscall_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (rs_rc < 0)
      return -1;
    if (rs_rc > 0)
      return 0;
  }
  /* Cap 10.7.1 slice12: va_start/end/va_arg_i32 Cap (x86_64). */
  {
    int32_t va_rc = try_emit_va_cap_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (va_rc < 0)
      return -1;
    if (va_rc > 0)
      return 0;
  }
  /* 10.4.1 slice1: atomic_load/store/cas_i32 CALL (x86_64 only). */
  {
    int32_t at_rc = try_emit_atomic_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (at_rc < 0)
      return -1;
    if (at_rc > 0)
      return 0;
  }

  /* Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): CALL through *u8 or TYPE_FN —
   * spill fn + emit_call_args + blr. Twin of backend_call_dispatch.x.
   * PLATFORM: SHARED. */
  {
    int32_t cap_tr = 0;
    int32_t cap_ko = 0;
    int32_t cap_er = 0;
    int32_t cap_eko = 0;
    int32_t cap_nargs = 0;
    int32_t cap_eff = callee_ref;
    int32_t cap_fn_off = 0;
    int32_t cap_ok = 0;
    if (callee_ko == 51 || callee_ko == 52) {
      /* EXPR_ADDR_OF / EXPR_DEREF — Cap (*f)() peels to VAR. */
      int32_t inn = pipeline_expr_unary_operand_ref_at(arena, callee_ref);
      if (inn > 0)
        cap_eff = inn;
    }
    cap_tr = pipeline_expr_resolved_type_ref(arena, cap_eff);
    if (cap_tr > 0) {
      cap_ko = pipeline_type_kind_ord_at(arena, cap_tr);
      /* TYPE_FN (18) shares Cap opaque fn-ptr ABI with *u8. */
      if (cap_ko == 18) {
        cap_ok = 1;
      } else if (cap_ko == GLUE_TYPE_PTR_ORD) {
        cap_er = pipeline_type_elem_ref_at(arena, cap_tr);
        if (cap_er > 0) {
          cap_eko = pipeline_type_kind_ord_at(arena, cap_er);
          if (cap_eko == 2)
            cap_ok = 1;
        }
      }
      if (cap_ok != 0) {
            cap_nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
            if (cap_nargs < 0)
              return -1;
            /* slice4: allow stack args via emit_call_args (no reg_max hard-fail). */
            if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, cap_eff, ctx, ta) != 0)
              return -1;
            if (cap_nargs == 0) {
              if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0)
                return -1;
              return 0;
            }
            cap_fn_off = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
            if (cap_fn_off < 0)
              return -1;
            if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, cap_nargs) != 0)
              return -1;
            /* PLATFORM: MACOS|ARM64 uses non-arg volatile scratch x9 (ta==1)
             * so reloading the fn ptr does not clobber argument x0. SysV x86_64
             * uses rax (ta==0) as rax is not an argument register. */
            if (ta == 1) {
              if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 9, 29, cap_fn_off, ta) != 0)
                return -1;
              if (backend_enc_blr_arch(elf_ctx, 9, ta) != 0)
                return -1;
            } else {
              if (backend_enc_load_rbp_to_rax_arch(elf_ctx, cap_fn_off, ta) != 0)
                return -1;
              if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0)
                return -1;
            }
            return 0;
      }
    }
  }

  /** hello.x: fmt.print/println string lit → call std_fmt_print / std_fmt_println. */
  if (callee_ko == GLUE_EXPR_FIELD_ACCESS_ORD) {
    int32_t fa_lit = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta,
                                                                        (const uint8_t *)"std_fmt_", 8, (const uint8_t *)"println",
                                                                        7);
    if (fa_lit < 0)
      return -1;
    if (fa_lit > 0)
      return 0;
    fa_lit = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta,
                                                                (const uint8_t *)"std_fmt_", 8, (const uint8_t *)"print", 5);
    if (fa_lit < 0)
      return -1;
    if (fa_lit > 0)
      return 0;
    /* print_any composite JSON (hardcoded std_fmt_ prefix path). */
    fa_lit = glue_asm_try_emit_fmt_any_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta,
                                                         (const uint8_t *)"std_fmt_", 8, (const uint8_t *)"println", 7);
    if (fa_lit < 0)
      return -1;
    if (fa_lit > 0)
      return 0;
    fa_lit = glue_asm_try_emit_fmt_any_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta,
                                                         (const uint8_t *)"std_fmt_", 8, (const uint8_t *)"print", 5);
    if (fa_lit < 0)
      return -1;
    if (fa_lit > 0)
      return 0;
  }

  /** import binding + `binding.field(args)` callee。 */
  if (mod_ref && callee_ko == 44) {
    int32_t base_ref = pipeline_expr_field_access_base_ref(arena, callee_ref);
    if (base_ref > 0 && pipeline_expr_kind_ord_at(arena, base_ref) == 3) {
      uint8_t base_name[128];
      int32_t base_len = pipeline_expr_var_name_len(arena, base_ref);
      if (base_len > 0 && base_len <= 127) {
        int32_t j;
        uint8_t field_name[128];
        int32_t field_len;
        pipeline_expr_var_name_into(arena, base_ref, base_name);
        field_len = pipeline_expr_field_access_name_len(arena, callee_ref);
        if (field_len > 0 && field_len <= 127) {
          pipeline_expr_field_access_name_into(arena, callee_ref, field_name);
          for (j = 0; j < parser_get_module_num_imports(mod_ref); j++) {
            if (pipeline_module_import_kind_at(mod_ref, j) == GLUE_IMPORT_KIND_BINDING &&
                glue_asm_import_binding_name_equal(mod_ref, j, base_name, base_len)) {
              uint8_t pre_buf[128];
              uint8_t sym_flat[128];
              int32_t pre_len;
              int32_t sym_len;
              int32_t call_nargs;
              int32_t n_ov;
              pre_len = glue_asm_fill_c_prefix_from_module_import(mod_ref, j, pre_buf);
              if (pre_len <= 0)
                return -1;
              /* PLATFORM: SHARED — G.7 import-binding CALL mangle (shared with METHOD_CALL). */
              sym_len = glue_asm_mangle_import_binding_call_sym_c(arena, ctx, expr_ref, ly, mod_ref, j, pre_buf,
                                                                  pre_len, field_name, field_len, 0, sym_flat);
              if (sym_len <= 0)
                return -1;
              {
                int32_t fmt_lit =
                    glue_asm_try_emit_fmt_string_lit_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta, pre_buf,
                                                                       pre_len, field_name, field_len);
                if (fmt_lit < 0)
                  return -1;
                if (fmt_lit > 0)
                  return 0;
                fmt_lit = glue_asm_try_emit_fmt_any_import_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta, pre_buf,
                                                                      pre_len, field_name, field_len);
                if (fmt_lit < 0)
                  return -1;
                if (fmt_lit > 0)
                  return 0;
              }
              call_nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
              n_ov = pipeline_codegen_call_num_args_override(pre_buf, pre_len, field_name, field_len, call_nargs);
              if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, n_ov) != 0)
                return -1;
              if (glue_asm_enc_call_redirected(elf_ctx, sym_flat, sym_len, ta) != 0)
                return -1;
              {
                int32_t cln = glue_asm_call_stack_cleanup_bytes(ta, n_ov);
                if (cln < 0 || backend_enc_call_stack_cleanup_arch(elf_ctx, cln, ta) != 0)
                  return -1;
              }
              if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0)
                return -1;
              /* PLATFORM: MACOS|ARM64 AAPCS64 — host-C import-binding CALL f32/f64 in s0/d0.
               * Same-pattern twin of import METHOD harvest. Do not put this in the
               * shared helper (local xlang f32 CALL stays GP). */
              if (ta == 1) {
                int32_t rk_ib = pipeline_asm_call_return_type_kind_ord_c(arena, expr_ref);
                if (rk_ib == 14) {
                  if (backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta) != 0)
                    return -1;
                } else if (rk_ib == 15) {
                  if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta) != 0)
                    return -1;
                }
              }
              return 0;
            }
          }
        }
      }
    }
  }

  /** `import a.b` + `a.b.c.method(args)` whole-import 限定 callee。 */
  if (mod_ref && callee_ko == 44) {
    int32_t imp_elt = 0;
    uint8_t sym_eh[128];
    int32_t elen;
    uint8_t field_name[128];
    int32_t field_len;
    elen = pipeline_asm_resolve_whole_import_qualified_symbol_c(arena, mod_ref, callee_ref, sym_eh, &imp_elt);
    if (elen > 0 && imp_elt >= 0 && imp_elt < parser_get_module_num_imports(mod_ref)) {
      uint8_t pre_eb[128];
      int32_t pre_el;
      int32_t call_nargs2;
      int32_t n_wo_elf;
      field_len = pipeline_expr_field_access_name_len(arena, callee_ref);
      if (field_len <= 0 || field_len > 63)
        return -1;
      pipeline_expr_field_access_name_into(arena, callee_ref, field_name);
      pre_el = glue_asm_fill_c_prefix_from_module_import(mod_ref, imp_elt, pre_eb);
      if (pre_el <= 0)
        return -1;
      call_nargs2 = pipeline_expr_call_num_args_at(arena, expr_ref);
      n_wo_elf = pipeline_codegen_call_num_args_override(pre_eb, pre_el, field_name, field_len, call_nargs2);
      if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, n_wo_elf) != 0)
        return -1;
      if (glue_asm_enc_call_redirected(elf_ctx, sym_eh, elen, ta) != 0)
        return -1;
      {
        int32_t cln2 = glue_asm_call_stack_cleanup_bytes(ta, n_wo_elf);
        if (cln2 < 0 || backend_enc_call_stack_cleanup_arch(elf_ctx, cln2, ta) != 0)
          return -1;
      }
      if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0)
        return -1;
      /* PLATFORM: MACOS|ARM64 AAPCS64 — host-C whole-import CALL f32/f64 in s0/d0.
       * Same-pattern twin of import METHOD harvest. */
      if (ta == 1) {
        int32_t rk_wi = pipeline_asm_call_return_type_kind_ord_c(arena, expr_ref);
        if (rk_wi == 14) {
          if (backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta) != 0)
            return -1;
        } else if (rk_wi == 15) {
          if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta) != 0)
            return -1;
        }
      }
      return 0;
    }
  }

  /** 同模块 VAR callee。 */
  if (callee_ko != 3)
    return -1;
  nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
  if (nargs < 0 || nargs > GLUE_ASM_MAX_CALL_ARGS)
    return -1;
  if (nargs == 1)
    backend_call_debugf("emit call1 ref=%d callee_ko=%d", (int)expr_ref, (int)callee_ko);
  inline_rc = try_inline_param0_single_field_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
  if (inline_rc != 0) {
    backend_call_debugf("emit call inline param0_field rc=%d ref=%d", (int)inline_rc, (int)expr_ref);
    return inline_rc < 0 ? -1 : 0;
  }
  inline_rc = try_inline_param0_field_sum_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
  if (inline_rc != 0) {
    backend_call_debugf("emit call inline field_sum rc=%d ref=%d", (int)inline_rc, (int)expr_ref);
    return inline_rc < 0 ? -1 : 0;
  }
  inline_rc = try_inline_x_plus_k_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
  if (inline_rc != 0) {
    backend_call_debugf("emit call inline x_plus_k rc=%d ref=%d", (int)inline_rc, (int)expr_ref);
    return inline_rc < 0 ? -1 : 0;
  }
  inline_rc = try_call_wpo_mono_symbol_elf(arena, elf_ctx, expr_ref, ctx, ta);
  if (inline_rc != 0) {
    backend_call_debugf("emit call inline wpo_mono rc=%d ref=%d", (int)inline_rc, (int)expr_ref);
    return inline_rc < 0 ? -1 : 0;
  }
  inline_rc = try_call_wpo_mono_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
  if (inline_rc != 0)
    return inline_rc < 0 ? -1 : 0;
  /* wave231 G.7: XLANG_WPO_MONO / XLANG_WPO_NO_FOLD via link_abi_getenv (not raw getenv). */
  if (!link_abi_getenv("XLANG_WPO_MONO") && !link_abi_getenv("XLANG_WPO_NO_FOLD")) {
    /* XLANG_WPO_NO_FOLD=1：bench/对照时禁用常量实参 fold（仍允许 mono 路径）。 */
    inline_rc = try_inline_wpo_const_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0)
      return inline_rc < 0 ? -1 : 0;
    inline_rc = try_inline_wpo_const_scalar_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0)
      return inline_rc < 0 ? -1 : 0;
  }
  clen = pipeline_expr_var_name_len(arena, callee_ref);
  /* wave580 Cap residual: long callee idents (64..127) must build call symbols. */
  if (clen <= 0 || clen > 127)
    return -1;
  clen = glue_asm_build_call_export_sym_c(arena, expr_ref, callee_ref, mod_ref, ly ? ly->dep_pipe : 0, cname, 128);
  if (clen <= 0)
    return -1;
  backend_call_debugf("call elf c %.*s nargs=%d", (int)clen, (char *)cname, (int)nargs);
  return glue_asm_emit_call_with_cleanup(arena, elf_ctx, expr_ref, ctx, ta, nargs, cname, clen);
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_emit_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                     int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta) {
  return pipeline_asm_emit_call_elf_c_impl(arena, elf_ctx, expr_ref, ctx, ta);
}
#endif

extern int32_t pipeline_expr_method_call_base_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_num_args_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_method_call_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out64);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);

/**
 * EXPR_METHOD_CALL ELF：receiver 作 arg0，实参 arg1..argN，enc_call(method_name)。
 * 供 backend.x emit_expr_elf_method_call 薄包装（M8-tail）。
 */
/* G-02f-147：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-376 call：实现体始终 seed；public PREFER 时 thin forward */
int32_t pipeline_asm_emit_method_call_elf_c_impl(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta) {
  struct glue_AsmFuncCtxCall *ly;
  struct ast_Module *mod_ref;
  int32_t nargs;
  int32_t base_ref;
  int32_t i;
  int32_t name_len;
  uint8_t name[128];

  ly = (struct glue_AsmFuncCtxCall *)ctx;
  mod_ref = ly ? ly->module_ref : 0;
  nargs = pipeline_expr_method_call_num_args_at(arena, expr_ref);
  /**
   * PLATFORM: SHARED — product parses `core.xlang_io_submit_read_batch(...)` as METHOD_CALL with
   * 11 scalar args. Historical `nargs > 5` hard-fail → freestanding co-emit CG002 on
   * submit_read_batch final_expr. G.7: complete same multi-arg path as EXPR_CALL (regs + stack).
   */
  if (nargs < 0 || nargs > GLUE_ASM_MAX_CALL_ARGS)
    return -1;
  base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref);
  name_len = pipeline_expr_method_call_name_len(arena, expr_ref);
  if (name_len <= 0 || name_len > 127)
    return -1;
  pipeline_expr_method_call_name_into(arena, expr_ref, name);
  /* stage10 S3.1 slice2 (10.1.1): dot-call raw_syscall0..6 shape
   * (linux.raw_syscall3(...) parses here; before dyn/UFCS/try_inline). */
  {
    int32_t rs_mc = try_emit_raw_syscall_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (rs_mc < 0)
      return -1;
    if (rs_mc > 0)
      return 0;
  }
  /* Cap 10.7.1 slice12: va_* Cap METHOD_CALL (x86_64). */
  {
    int32_t va_mc = try_emit_va_cap_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (va_mc < 0)
      return -1;
    if (va_mc > 0)
      return 0;
  }
  /* 10.4.1 slice1: atomic_load/store/cas_i32 METHOD_CALL (x86_64 only). */
  {
    int32_t at_mc = try_emit_atomic_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
    if (at_mc < 0)
      return -1;
    if (at_mc > 0)
      return 0;
  }
  /* 10.3.3 slice3: METHOD_CALL Cap/TYPE_FN field → load + blr (twin of .x). */
  {
    int32_t ff_base_ty = 0;
    int32_t ff_ty = 0;
    int32_t ff_ko = 0;
    int32_t ff_er = 0;
    int32_t ff_eko = 0;
    int32_t ff_ok = 0;
    int32_t ff_nlen = 0;
    int32_t ff_li = 0;
    int32_t ff_nf = 0;
    int32_t ff_j = 0;
    int32_t ff_fnl = 0;
    int32_t ff_foff = 0;
    int32_t ff_hit = 0;
    int32_t ff_eq = 0;
    int32_t ff_k = 0;
    int32_t ff_nlays = 0;
    int32_t ff_fi = 0;
    int32_t ff_spill = 0;
    int32_t ff_reg_max = 0;
    uint8_t ff_nm[128];
    uint8_t ff_fnm[128];
    uint8_t ff_lnm[128];
    ff_base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (ff_base_ty > 0) {
      ff_ty = ff_base_ty;
      ff_ko = pipeline_type_kind_ord_at(arena, ff_ty);
      if (ff_ko == 9) {
        ff_er = pipeline_type_elem_ref_at(arena, ff_ty);
        if (ff_er > 0) {
          ff_ty = ff_er;
          ff_ko = pipeline_type_kind_ord_at(arena, ff_ty);
        }
      }
      if (ff_ko == 8 && mod_ref != 0) {
        ff_nlen = pipeline_type_named_name_into(arena, ff_ty, ff_nm);
        if (ff_nlen > 0 && ff_nlen <= 127) {
          ff_nlays = pipeline_module_num_struct_layouts_at(mod_ref);
          for (ff_li = 0; ff_li < ff_nlays && !ff_hit; ff_li++) {
            int32_t ln = pipeline_module_struct_layout_name_len(mod_ref, ff_li);
            ff_eq = 1;
            if (ln != ff_nlen)
              ff_eq = 0;
            else {
              pipeline_module_struct_layout_name_into(mod_ref, ff_li, ff_lnm);
              for (ff_k = 0; ff_k < ff_nlen; ff_k++) {
                if (ff_lnm[ff_k] != ff_nm[ff_k])
                  ff_eq = 0;
              }
            }
            if (ff_eq) {
              ff_nf = pipeline_module_struct_layout_num_fields(mod_ref, ff_li);
              for (ff_j = 0; ff_j < ff_nf && !ff_hit; ff_j++) {
                ff_fnl = pipeline_module_struct_layout_field_name_len(mod_ref, ff_li, ff_j);
                if (ff_fnl == name_len && ff_fnl > 0 && ff_fnl <= 127) {
                  pipeline_module_struct_layout_field_name_into(mod_ref, ff_li, ff_j, ff_fnm);
                  ff_eq = 1;
                  for (ff_k = 0; ff_k < ff_fnl; ff_k++) {
                    if (ff_fnm[ff_k] != name[ff_k])
                      ff_eq = 0;
                  }
                  if (ff_eq) {
                    ff_er = pipeline_module_struct_layout_field_type_ref(mod_ref, ff_li, ff_j);
                    ff_foff = pipeline_module_struct_layout_field_offset_at(mod_ref, ff_li, ff_j);
                    ff_hit = 1;
                  }
                }
              }
            }
          }
        }
      }
      if (ff_hit && ff_er > 0) {
        ff_ko = pipeline_type_kind_ord_at(arena, ff_er);
        if (ff_ko == 18)
          ff_ok = 1;
        else if (ff_ko == 9) {
          int32_t ff_pointee = pipeline_type_elem_ref_at(arena, ff_er);
          if (ff_pointee > 0) {
            ff_eko = pipeline_type_kind_ord_at(arena, ff_pointee);
            if (ff_eko == 2)
              ff_ok = 1;
          }
        }
      }
      if (ff_ok) {
        if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0)
          return -1;
        if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, ff_foff, ta) != 0)
          return -1;
        if (nargs == 0) {
          if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0)
            return -1;
          return 0;
        }
        ff_reg_max = glue_asm_call_reg_max(ta);
        if (ff_reg_max < 1)
          ff_reg_max = 6;
        if (nargs > ff_reg_max)
          ff_ok = 0;
      }
      if (ff_ok && nargs > 0) {
        ff_spill = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
        if (ff_spill < 0)
          return -1;
        for (ff_fi = 0; ff_fi < nargs; ff_fi++) {
          int32_t ff_ar = pipeline_expr_method_call_arg_ref(arena, expr_ref, ff_fi);
          if (ff_ar <= 0)
            return -1;
          if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, ff_ar, ctx, ta) != 0)
            return -1;
          if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, ff_fi, ta) != 0)
            return -1;
        }
        /* PLATFORM: MACOS|ARM64 uses non-arg volatile scratch x9 (ta==1)
         * so reloading the fn ptr does not clobber argument x0. SysV x86_64
         * uses rax (ta==0) as rax is not an argument register. */
        if (ta == 1) {
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 9, 29, ff_spill, ta) != 0)
            return -1;
          if (backend_enc_blr_arch(elf_ctx, 9, ta) != 0)
            return -1;
        } else {
          if (backend_enc_load_rbp_to_rax_arch(elf_ctx, ff_spill, ta) != 0)
            return -1;
          if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0)
            return -1;
        }
        return 0;
      }
    }
  }
  /*
   * wave359 Cap residual pure — freestanding i32.double() → x*2.
   * Root: host codegen expands `(x * 2)`; freestanding called bare `double`
   * → Ubuntu UNDEF (mac often host-C or dead_strip hid).
   * G.7 authority: same bootstrap leaf as host METHOD_CALL double expand;
   * only when typeck did NOT resolve UFCS free fn (call_resolved_func_index < 0).
   * Emit: base → rax; mov rax→rbx; add rax,rbx → 2*base in rax (no new encoder).
   * PLATFORM: SHARED — mac + Ubuntu freestanding L2.
   */
  {
    int32_t r_fn = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    /*
     * F7: dyn Trait dispatch via vtable indirect call.
     * typeck sets call_resolved_dep_index = DYN_DISPATCH_DEP_SENTINEL (-2) when
     * the receiver is TYPE_DYN (kind=17), and stores the trait method slot
     * index in call_resolved_func_index (r_fn here). The dyn_obj layout is
     * { void* data; void* vtable; } (16 bytes), so:
     *   1. receiver addr in x0 (base_ref expression emit)
     *   2. ldr x1, [x0, #8]      — x1 = dyn_obj.vtable
     *   3. ldr x2, [x1, #slot*8] — x2 = vtable[slot] (wrapper fn ptr)
     *   4. ldr x0, [x0, #0]      — x0 = dyn_obj.data (self arg to wrapper)
     *   5. extras: GP 1..(reg_max-1) and/or xmm0–7 (x86 SysV); overflow on stack
     *   6. blr x2 (or scratch)   — indirect call through wrapper fn ptr
     * PLATFORM: SHARED — arm64 blr / x86_64 call rN / riscv64 jalr.
     */
    {
      int32_t dep_idx = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
      if (dep_idx == -2) {
        int32_t slot = r_fn;
        if (slot < 0) { return -1; }
        /*
         * Extra method args: integer GP 1..(reg_max-1) after self in GP0.
         * Overflow extras go on the stack (x86 push / ARM64 [sp+slot]).
         * x86 SysV f32/f64 extras go xmm0–7 then stack (impl param_home).
         * ARM64 local callee homes GP — do not copy import METHOD s0/d0.
         * Wrapper copies incoming stack extras before call impl (not tail-jmp).
         * Do NOT glue_emit_one_call_arg — resolved_func_index is the vtable slot.
         * G.7: emit_expr_elf_for_call_args + glue_arg_ref_is_sse_float_c
         * + glue_asm_call_reg_max (not a hardcoded 5).
         * PLATFORM: LINUX x86_64 SysV xmm · MACOS ARM64 extras stay GP.
         */
        {
          int32_t extra_off[96];
          int32_t is_sse_e[96];
          int32_t is_f64_e[96];
          int32_t place_e[96];
          int32_t on_stk_e[96];
          int32_t xmm_cur;
          int32_t gp_cur;
          int32_t n_stk;
          int32_t reg_max_e;
          int32_t ei;
          int32_t arg_ex;
          int32_t so_ex;
          int32_t data_off;
          int32_t fn_off;
          int32_t cur_fn;
          int32_t stk_bytes;
          int32_t stk_slot;
          xmm_cur = 0;
          gp_cur = 1;
          n_stk = 0;
          reg_max_e = glue_asm_call_reg_max(ta);
          if (reg_max_e < 2)
            reg_max_e = 6;
          for (ei = 0; ei < nargs; ei++) {
            extra_off[ei] = -1;
            is_sse_e[ei] = 0;
            is_f64_e[ei] = 0;
            place_e[ei] = 0;
            on_stk_e[ei] = 0;
            arg_ex = pipeline_expr_method_call_arg_ref(arena, expr_ref, ei);
            if (arg_ex == 0)
              return -1;
            if (ta == 0) {
              is_sse_e[ei] = glue_arg_ref_is_sse_float_c(arena, arg_ex, 0);
              is_f64_e[ei] = glue_arg_ref_is_f64_width_c(arena, arg_ex, 0);
            }
            if (is_sse_e[ei] != 0) {
              if (xmm_cur < 8) {
                place_e[ei] = xmm_cur;
                xmm_cur = xmm_cur + 1;
              } else {
                on_stk_e[ei] = 1;
                place_e[ei] = n_stk;
                n_stk = n_stk + 1;
              }
            } else {
              if (gp_cur < reg_max_e) {
                place_e[ei] = gp_cur;
                gp_cur = gp_cur + 1;
              } else {
                on_stk_e[ei] = 1;
                place_e[ei] = n_stk;
                n_stk = n_stk + 1;
              }
            }
            if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ex, ctx, ta) != 0)
              return -1;
            so_ex = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
            if (so_ex < 0)
              return -1;
            extra_off[ei] = so_ex;
          }
          /* F7: &dyn_obj via lvalue LEA, not emit_expr (which loads .data). */
          if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
            return -1;
          }
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 1, 0, 8, ta) != 0) { return -1; }
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 2, 1, slot * 8, ta) != 0) { return -1; }
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, 0, ta) != 0) { return -1; }
          /* SysV first arg is rdi. Do not change wrapper rdi=data. */
          if (ta == 0) {
            if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) { return -1; }
          }
          if (nargs <= 0) {
            if (backend_enc_blr_arch(elf_ctx, 2, ta) != 0) { return -1; }
            return 0;
          }
          data_off = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
          if (data_off < 0)
            return -1;
          fn_off = -1;
          if (nargs >= 2) {
            cur_fn = ly->next_offset + 16;
            if (cur_fn < 16)
              cur_fn = 16;
            fn_off = cur_fn;
            if (backend_enc_store_x_reg_to_rbp_arch(elf_ctx, 2, fn_off, ta) != 0)
              return -1;
            ly->next_offset = fn_off + 16;
          }
          /* Stack extras from spills. PLATFORM: LINUX x86_64 SysV push · MACOS|ARM64 [sp]. */
          stk_bytes = 0;
          if (n_stk > 0) {
            if (ta == 0) {
              if ((n_stk & 1) != 0) {
                if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0)
                  return -1;
                if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
                  return -1;
                stk_bytes = stk_bytes + 8;
              }
              for (ei = nargs - 1; ei >= 0; ei--) {
                if (on_stk_e[ei] != 0) {
                  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0)
                    return -1;
                  if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
                    return -1;
                  stk_bytes = stk_bytes + 8;
                }
              }
            } else {
              stk_bytes = n_stk * 8;
              stk_bytes = (stk_bytes + 15) & -16;
              if (backend_enc_call_stack_reserve_arch(elf_ctx, stk_bytes, ta) != 0)
                return -1;
              stk_slot = 0;
              for (ei = 0; ei < nargs; ei++) {
                if (on_stk_e[ei] != 0) {
                  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0)
                    return -1;
                  if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0)
                    return -1;
                  stk_slot = stk_slot + 1;
                }
              }
            }
          }
          for (ei = 0; ei < nargs; ei++) {
            if (on_stk_e[ei] == 0) {
              if (is_sse_e[ei] != 0) {
                if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0)
                  return -1;
                if (is_f64_e[ei] != 0) {
                  if (backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, place_e[ei], ta) != 0)
                    return -1;
                } else if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, place_e[ei], ta) != 0) {
                  return -1;
                }
              } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, extra_off[ei], place_e[ei], 1) != 0) {
                return -1;
              }
            }
          }
          if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, data_off, 0, 1) != 0)
            return -1;
          if (nargs >= 2) {
            /* Non-arg scratch: x86 r11 / ARM64 x9. PLATFORM: LINUX x86 · MACOS ARM64. */
            if (ta == 0) {
              if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 11, 5, 0 - fn_off, ta) != 0)
                return -1;
              if (backend_enc_blr_arch(elf_ctx, 11, ta) != 0) { return -1; }
            } else {
              if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 9, 29, fn_off, ta) != 0)
                return -1;
              if (backend_enc_blr_arch(elf_ctx, 9, ta) != 0) { return -1; }
            }
          } else {
            if (backend_enc_blr_arch(elf_ctx, 2, ta) != 0) { return -1; }
          }
          if (stk_bytes > 0) {
            if (backend_enc_call_stack_cleanup_arch(elf_ctx, stk_bytes, ta) != 0)
              return -1;
          }
          return 0;
        }
      }
    }
    if (r_fn < 0 && nargs == 0 && name_len == 6 && base_ref != 0 && name[0] == (uint8_t)'d' &&
        name[1] == (uint8_t)'o' && name[2] == (uint8_t)'u' && name[3] == (uint8_t)'b' &&
        name[4] == (uint8_t)'l' && name[5] == (uint8_t)'e') {
      if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, base_ref, ctx, ta) != 0)
        return -1;
      if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0)
        return -1;
      if (backend_enc_add_rax_rbx_arch(elf_ctx, ta) != 0)
        return -1;
      return 0;
    }
  }
  /** import binding：encoding.foo(args) 静态调用，receiver 不入参。 */
  if (mod_ref && base_ref > 0 && pipeline_expr_kind_ord_at(arena, base_ref) == GLUE_EXPR_VAR_ORD) {
    uint8_t base_name[128];
    int32_t base_len = pipeline_expr_var_name_len(arena, base_ref);
    if (base_len > 0 && base_len <= 127) {
      int32_t j;
      pipeline_expr_var_name_into(arena, base_ref, base_name);
      for (j = 0; j < parser_get_module_num_imports(mod_ref); j++) {
        if (pipeline_module_import_kind_at(mod_ref, j) == GLUE_IMPORT_KIND_BINDING &&
            glue_asm_import_binding_name_equal(mod_ref, j, base_name, base_len)) {
          uint8_t pre_buf[128];
          uint8_t sym_flat[128];
          int32_t pre_len;
          int32_t sym_len;
          int32_t n_ov;
          pre_len = glue_asm_fill_c_prefix_from_module_import(mod_ref, j, pre_buf);
          if (pre_len <= 0)
            return -1;
          /*
           * PLATFORM: SHARED — hello.x `fmt.println("…")` is METHOD_CALL (not CALL+FIELD_ACCESS).
           * G.7: same fmt string-lit special as pipeline_asm_emit_call_elf_c (ptr+len → std_fmt_println).
           * Without this leaf, overload mangle invents println_i32_reti32 → pure-asm BLD001 UNDEF.
           */
          {
            int32_t fmt_lit = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
                arena, elf_ctx, expr_ref, ctx, ta, pre_buf, pre_len, name, name_len);
            if (fmt_lit < 0)
              return -1;
            if (fmt_lit > 0)
              return 0;
            fmt_lit = glue_asm_try_emit_fmt_any_import_call_elf_c(
                arena, elf_ctx, expr_ref, ctx, ta, pre_buf, pre_len, name, name_len);
            if (fmt_lit < 0)
              return -1;
            if (fmt_lit > 0)
              return 0;
          }
          /*
           * PLATFORM: SHARED — import-binding METHOD_CALL mangle (G.7 same authority as CALL).
           * Parser emits METHOD_CALL for string.length(v); bare pre+name → U std_string_len.
           */
          sym_len = glue_asm_mangle_import_binding_call_sym_c(arena, ctx, expr_ref, ly, mod_ref, j, pre_buf,
                                                              pre_len, name, name_len, 1, sym_flat);
          if (sym_len <= 0)
            return -1;
          n_ov = pipeline_codegen_call_num_args_override(pre_buf, pre_len, name, name_len, nargs);
          /**
           * PLATFORM: LINUX+MACOS x86_64 SysV — import METHOD_CALL args (math.floor / vec.push / len /
           * xlang_io_submit_*_batch). f32/f64 extras go xmm0–7 (host-C gcc).
           * PLATFORM: MACOS|ARM64 AAPCS64 — same extras go s0–s7 / d0–d7 (host-C gcc reads FP regs).
           * Root: product parses `math.floor(x)` / `core.fn(…)` as METHOD_CALL, not CALL+FIELD_ACCESS.
           * G.7: same SSE class as CALL / prefer backend_call_dispatch.x import METHOD (ta==0||ta==1).
           * Do NOT classify UFCS extras as SSE on arm64 (local xlang callee homes GP).
           * 9–16B POD → 2 GPs; >16B MEMORY by-value on stack (formal C);
           * excess integer args after glue_asm_call_reg_max GPs go on stack
           * (SysV 6 = rdi..r9; AAPCS64 8 = x0–x7). Hardcoded 6 here sent
           * csv.parse_row's 7th GP (`&cnt`) to [sp] while the host-C wrapper
           * reads x6 → SIGSEGV. Free CALL / UFCS already use glue_asm_call_reg_max.
           * sret shift reserves rdi on x86 only.
           */
          {
            int32_t reg_start[GLUE_ASM_MAX_CALL_ARGS];
            int32_t reg_units[GLUE_ASM_MAX_CALL_ARGS];
            int32_t spill_off[GLUE_ASM_MAX_CALL_ARGS];
            int32_t is_sse[GLUE_ASM_MAX_CALL_ARGS];
            int32_t is_f64[GLUE_ASM_MAX_CALL_ARGS];
            int32_t is_mem[GLUE_ASM_MAX_CALL_ARGS];
            int32_t is_stk[GLUE_ASM_MAX_CALL_ARGS];
            int32_t arg_sz[GLUE_ASM_MAX_CALL_ARGS];
            int32_t sret_sh = (ta == 0) ? pipeline_asm_emit_call_sret_reg_shift_c() : 0;
            int32_t gp_cur = sret_sh;
            int32_t xmm_cur = 0;
            int32_t mem_stack = 0;
            int32_t n_place = nargs;
            /* PLATFORM: SHARED — same GP file as EXPR_CALL / UFCS / prefer .x. */
            int32_t reg_max = glue_asm_call_reg_max(ta);
            if (reg_max < 1)
              reg_max = 6;
            for (i = 0; i < n_place; i++) {
              int32_t arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
              int32_t pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
              int32_t u;
              int32_t sz;
              is_sse[i] = 0;
              is_f64[i] = 0;
              is_mem[i] = 0;
              is_stk[i] = 0;
              arg_sz[i] = 0;
              reg_start[i] = -1;
              reg_units[i] = 0;
              spill_off[i] = -1;
              if (arg_ref == 0)
                continue;
              sz = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, arg_ref);
              arg_sz[i] = sz;
              /* PLATFORM: LINUX+MACOS x86_64 SysV — f32/f64 extras → xmm0–7.
               * PLATFORM: MACOS|ARM64 AAPCS64 — same extras → s0–s7 (encoder fmov sK,w0).
               * Darwin product L2 lives in this seed (try-heat / r3-prefer cc -c seed).
               * G.7: same gate as prefer backend_call_dispatch.x import METHOD (ta==0||ta==1).
               * UFCS places[] below stays ta==0 only (local X callee homes x0). */
              is_sse[i] = (ta == 0 || ta == 1) ? glue_arg_ref_is_sse_float_c(arena, arg_ref, pty_i) : 0;
              is_f64[i] = glue_arg_ref_is_f64_width_c(arena, arg_ref, pty_i);
              if (is_sse[i]) {
                if (xmm_cur >= 8)
                  return -1;
                reg_start[i] = xmm_cur++;
                reg_units[i] = 1;
                continue;
              }
              /*
               * Import METHOD → host-C std .o large POD (String ~260B):
               * - PLATFORM: LINUX|x86_64 SysV — MEMORY by-value on stack (is_mem=1).
               *   Host-C gcc formals read [rbp+0x10..]; pure lea→rdi residual run-string
               *   length(String) exit≠1 (len_ptr OK, by-value length garbage).
               * - PLATFORM: MACOS|ARM64 AAPCS64 — large composite as pointer in GP (is_mem=2 lea).
               * Pure→pure UFCS still uses MEMORY stack on its own path (wave602).
               * G.7: pure .x import METHOD same split (x86 stack / arm64 lea).
               */
              if (sz > 16) {
                if (ta == 0) {
                  is_mem[i] = 1; /* x86 SysV MEMORY stack multi-word */
                  continue;
                }
                if (gp_cur + 1 > reg_max) {
                  is_stk[i] = 1;
                  continue;
                }
                reg_start[i] = gp_cur;
                reg_units[i] = 1;
                gp_cur += 1;
                is_mem[i] = 2; /* arm64 host-indirect lea → GP */
                continue;
              }
              /*
               * G.7: size→units on both SysV and AAPCS64 (9–16B INTEGER dual-GP).
               * Historic `if (ta != 0) u = 1` left only x0/x1 lows for Result_i32 import
               * METHOD (or_i32/and_i32) → host expects x0:x1+x2:x3 (run-result -3 residual).
               * Free CALL / pure import METHOD use the same units classification.
               * PLATFORM: SHARED freestanding · MACOS|ARM64 AAPCS64 · LINUX+MACOS x86 SysV.
               */
              u = glue_sysv_arg_gp_units_from_size_c(sz);
              if (u < 1)
                u = 1;
              if (u > 2)
                u = 2;
              if (gp_cur + u > reg_max) {
                /* Excess integer: SysV stack (push) / AAPCS64 [sp]. Dual-GP that does not fit: fail. */
                if (u > 1)
                  return -1;
                is_stk[i] = 1;
                continue;
              }
              reg_start[i] = gp_cur;
              reg_units[i] = u;
              gp_cur += u;
            }
            /**
             * Push MEMORY by-value and excess integer stack args before reg loads.
             * SysV: aggregate at lowest stack address ([rsp+0]=byte0). Pad for 16-align must sit at
             * higher addresses → push pad first, then struct/stack high→low. (Pad-after shifts fields.)
             */
            if (ta == 0) {
              int32_t raw_mem = 0;
              int32_t pushed_total = 0;
              for (i = 0; i < n_place; i++) {
                if (is_mem[i] == 1)
                  raw_mem += (arg_sz[i] + 7) & ~7;
                else if (is_stk[i])
                  raw_mem += 8;
              }
              while (((raw_mem + pushed_total) & 15) != 0) {
                if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0)
                  return -1;
                if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
                  return -1;
                pushed_total += 8;
              }
              for (i = n_place - 1; i >= 0; i--) {
                int32_t arg_ref;
                int32_t pushed;
                if (is_mem[i] == 1) {
                  arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
                  if (arg_ref == 0)
                    return -1;
                  pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(arena, elf_ctx, ctx, arg_ref, arg_sz[i], ta);
                  if (pushed < 0)
                    return -1;
                  pushed_total += pushed;
                } else if (is_stk[i]) {
                  arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
                  if (arg_ref == 0)
                    return -1;
                  if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
                    return -1;
                  if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
                    return -1;
                  pushed_total += 8;
                }
              }
              mem_stack = pushed_total;
            } else if (ta == 1) {
              /* arm64: only true stack MEMORY (is_mem==1) / excess GP (is_stk); not host-indirect lea. */
              int32_t nw = 0;
              int32_t stack_reserve;
              for (i = 0; i < n_place; i++) {
                if (is_mem[i] == 1)
                  nw += glue_sysv_arg_stack_words_c(arg_sz[i], 0);
                else if (is_stk[i])
                  nw += 1;
              }
              stack_reserve = nw * 8;
              if (stack_reserve > 0)
                stack_reserve = (stack_reserve + 15) & ~15;
              mem_stack = stack_reserve;
              if (stack_reserve > 0 &&
                  backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve, ta) != 0)
                return -1;
            }
            /*
             * PLATFORM: SHARED freestanding multi-arg.
             * Root (mac arm64 option unwrap_or/some): import-binding METHOD_CALL used to
             * direct-place on ta!=0 (mov imm→w0 then mov x1,x0) after nested CALL left the
             * Option in x0 — clobber → is_some=0 / value lost (full option run residual 252).
             * Ubuntu x86 already spill-then-load here; arm64 must match free CALL / UFCS
             * wave602 (G.7 one discipline). Load high→low so x0 temp does not wipe lower GPs.
             * is_mem==2: host-C large POD invisible ref — lea into GP (not stack MEMORY).
             */
            for (i = 0; i < n_place; i++) {
              int32_t arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
              int32_t so;
              if (arg_ref == 0 || is_mem[i] == 1 || is_stk[i])
                continue;
              if (is_mem[i] == 2) {
                /* >16B host-C: pass &arg in GP (nested CALL sret→temp then lea). */
                if (glue_emit_arm64_host_mem_arg_addr_to_rax_c(arena, elf_ctx, ctx, arg_ref, arg_sz[i],
                                                                ta) != 0)
                  return -1;
              } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0) {
                return -1;
              }
              so = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, reg_units[i]);
              if (so < 0)
                return -1;
              spill_off[i] = so;
            }
            /* arm64 true MEMORY stack (is_mem==1) before final GP load. */
            if (ta == 1) {
              int32_t stk_slot = 0;
              for (i = 0; i < n_place; i++) {
                int32_t arg_ref;
                int32_t words;
                int32_t stored;
                if (is_mem[i] != 1 && !is_stk[i])
                  continue;
                arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
                if (arg_ref == 0)
                  return -1;
                if (is_mem[i] == 1) {
                  stored = pipeline_asm_store_memory_by_value_to_sp_elf_c(arena, elf_ctx, ctx, arg_ref,
                                                                           arg_sz[i], ta, stk_slot * 8);
                  if (stored < 0)
                    return -1;
                  words = stored / 8;
                  if (words < 1)
                    words = 1;
                  stk_slot += words;
                  continue;
                }
                if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0)
                  return -1;
                if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0)
                  return -1;
                stk_slot += 1;
              }
            }
            /* Load spills: high place index first (AAPCS64 x0 temp + SysV rax temp). */
            for (i = n_place - 1; i >= 0; i--) {
              int32_t mov_rc;
              if (spill_off[i] < 0)
                continue;
              if (is_sse[i]) {
                if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off[i], ta) != 0)
                  return -1;
                if (is_f64[i])
                  mov_rc = backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, reg_start[i], ta);
                else
                  mov_rc = backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, reg_start[i], ta);
                if (mov_rc != 0)
                  return -1;
              } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], reg_start[i],
                                                                reg_units[i]) != 0) {
                return -1;
              }
            }
            if (glue_asm_enc_call_redirected(elf_ctx, sym_flat, sym_len, ta) != 0)
              return -1;
            {
              int32_t cln = mem_stack;
              if (cln <= 0)
                cln = glue_asm_call_stack_cleanup_bytes(ta, n_ov);
              if (cln < 0 || (cln > 0 && backend_enc_call_stack_cleanup_arch(elf_ctx, cln, ta) != 0))
                return -1;
            }
          }
          /* Type-driven f32/f64 ret harvest (same authority as EXPR_CALL). */
          if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0)
            return -1;
          /*
           * PLATFORM: MACOS|ARM64 AAPCS64 — host-C returns f32/f64 in s0/d0.
           * Shared harvest is x86-only so local xlang f32 CALL stays GP-in/GP-out.
           * Import METHOD callee is gcc: move s0/d0 → w0/x0 after the no-op harvest.
           * G.7: same block as prefer backend_call_dispatch.x after import METHOD.
           * Darwin product L2 lives in this seed (try-heat / r3-prefer cc -c seed).
           */
          if (ta == 1) {
            int32_t rk_m = pipeline_asm_call_return_type_kind_ord_c(arena, expr_ref);
            if (rk_m == 14) {
              if (backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta) != 0)
                return -1;
            } else if (rk_m == 15) {
              if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta) != 0)
                return -1;
            }
          }
          return 0;
        }
      }
    }
  }
  /* G.7: same param0.field / field-sum / x+K / wpo_mono-symbol / wpo_mono-vector_lane
   * / wpo_const-scalar / vector_lane folds as CALL emit
   * (recv.first() ≡ take_a(recv); recv.pair_sum() ≡ field_sum(recv);
   *  recv.plus_one() ≡ add_one(recv); recv.fold_add(K) ≡ fold_add_call(recv, K);
   *  XLANG_WPO_MONO: recv.fold_add(K) ≡ fold_add_call(recv, K) via zero-arg thunk;
   *  XLANG_WPO_MONO: recv.lane0() ≡ lane0_call(recv) via zero-arg thunk
   *  when recv is const vec_binop;
   *  recv.lane0() ≡ lane0_call(recv) when recv is const vec_binop).
   * After import-binding so import methods never enter lookup/fold. */
  {
    int32_t inline_sf = try_inline_param0_single_field_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_sf != 0)
      return inline_sf < 0 ? -1 : 0;
  }
  {
    int32_t inline_fs = try_inline_param0_field_sum_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_fs != 0)
      return inline_fs < 0 ? -1 : 0;
  }
  {
    int32_t inline_xk = try_inline_x_plus_k_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_xk != 0)
      return inline_xk < 0 ? -1 : 0;
  }
  /* Same order as CALL emit: mono symbol then vector_lane mono
   * (both self-gate on XLANG_WPO_MONO) then const fold only when
   * neither mono nor no-fold env is set. */
  {
    int32_t inline_ms = try_call_wpo_mono_symbol_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_ms != 0)
      return inline_ms < 0 ? -1 : 0;
  }
  {
    int32_t inline_mv = try_call_wpo_mono_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_mv != 0)
      return inline_mv < 0 ? -1 : 0;
  }
  /* Same env gate as CALL emit: XLANG_WPO_MONO / XLANG_WPO_NO_FOLD skip const fold.
   * Order matches CALL emit: vector_lane then scalar. */
  if (!link_abi_getenv("XLANG_WPO_MONO") && !link_abi_getenv("XLANG_WPO_NO_FOLD")) {
    int32_t inline_vl = try_inline_wpo_const_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_vl != 0)
      return inline_vl < 0 ? -1 : 0;
    int32_t inline_wc = try_inline_wpo_const_scalar_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_wc != 0)
      return inline_wc < 0 ? -1 : 0;
  }
  /*
   * wave602 Cap residual pure — freestanding UFCS method self SysV dual-GP / MEMORY.
   * Root: receiver was always 1 GP (`mov rax→rdi`); 9–16B self dropped high half (rdx);
   * >16B self used lea→rdi while callee `param_home` reads `[rbp+0x10..]` (wave599 MEMORY).
   * Ubuntu pure-asm `s.sum()` Pair=16B → 59; S24=24B → 57 (mac arm64 often host-C/const-fold hid).
   * Import-binding METHOD path already packs dual-GP/MEMORY; free CALL wave601 same.
   * G.7: complete same-module UFCS leaf — logical places [receiver, arg0..] with formal
   * param types 0..n_place-1 (self is formal 0). wave360 auto-ref (*T self → lea) stays.
   * PLATFORM: LINUX+MACOS x86_64 SysV; arm64 dual-GP self via spill/load (wave600 twin).
   *
   * wave606 Cap residual pure — arm64 UFCS method MEMORY by-value (self + args).
   * Root: wave602 classified MEMORY only for ta==0; arm64 coerced u=0→1 (lea→x0) while
   * callee param_home reads stack words (wave599/603). free CALL arm64 fixed in wave603
   * (store_memory_to_sp); method UFCS still lea residual → mac fs s.sum()=234≠42.
   * G.7: same places[] classification as free CALL — MEMORY stack-only on ta==0 and ta==1;
   * arm64 reserve + store_memory_to_sp + cleanup ≡ emit_call_args wave603 path.
   * PLATFORM: MACOS|ARM64 AAPCS64 + SHARED freestanding · LINUX|x86 push path unchanged.
   */
  {
    int32_t has_recv = (base_ref != 0) ? 1 : 0;
    int32_t n_place;
    int32_t need_aref = 0;
    int32_t reg_start[GLUE_ASM_MAX_CALL_ARGS];
    int32_t reg_units[GLUE_ASM_MAX_CALL_ARGS];
    int32_t spill_off[GLUE_ASM_MAX_CALL_ARGS];
    int32_t is_sse[GLUE_ASM_MAX_CALL_ARGS];
    int32_t is_f64[GLUE_ASM_MAX_CALL_ARGS];
    int32_t is_mem[GLUE_ASM_MAX_CALL_ARGS];
    int32_t is_stk[GLUE_ASM_MAX_CALL_ARGS];
    int32_t arg_sz[GLUE_ASM_MAX_CALL_ARGS];
    int32_t sret_sh;
    int32_t gp_cur;
    int32_t xmm_cur;
    int32_t mem_stack;
    int32_t reg_max;
    /*
     * Associated Type.method(): resolved callee nparams == nargs (no implicit
     * self). `P.mk()` / `P.id(7)` / `P.get(p)` — type-name receiver is not
     * an argument. Instance `p.get()` keeps nparams == nargs+1 so has_recv
     * stays 1. PLATFORM: SHARED — G.7 complete UFCS leave; twin
     * src/asm/backend_call_dispatch.x.
     */
    if (has_recv) {
      int32_t assoc_fn = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
      int32_t assoc_dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
      if (assoc_fn >= 0 && assoc_dep < 0 && mod_ref) {
        int32_t assoc_np = pipeline_module_func_num_params_at(mod_ref, assoc_fn);
        if (assoc_np == nargs)
          has_recv = 0;
      }
    }
    n_place = has_recv + nargs;

    if (n_place < 0 || n_place > GLUE_ASM_MAX_CALL_ARGS)
      return -1;

    /* wave360: value.method when free fn is method(self: *T,...) → pass &receiver. */
    if (has_recv) {
      int32_t r_fn = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
      int32_t r_dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
      if (r_fn >= 0 && r_dep < 0 && mod_ref) {
        int32_t p0 = pipeline_module_func_param_type_ref_at(mod_ref, r_fn, 0);
        int32_t bty = pipeline_expr_resolved_type_ref(arena, base_ref);
        if (p0 > 0 && bty > 0 &&
            pipeline_type_kind_ord_at(arena, p0) == GLUE_TYPE_PTR_ORD &&
            pipeline_typeck_type_refs_equal_c(arena, bty, p0) == 0) {
          int32_t pe = pipeline_type_elem_ref_at(arena, p0);
          if (pe > 0 && pipeline_typeck_type_refs_equal_c(arena, bty, pe) != 0)
            need_aref = 1;
        }
      }
    }

    sret_sh = (ta == 0) ? pipeline_asm_emit_call_sret_reg_shift_c() : 0;
    gp_cur = sret_sh;
    xmm_cur = 0;
    mem_stack = 0;
    reg_max = glue_asm_call_reg_max(ta);
    if (reg_max < 1)
      reg_max = 6;

    for (i = 0; i < n_place; i++) {
      int32_t arg_ref;
      int32_t pty_i;
      int32_t u;
      int32_t sz;
      is_sse[i] = 0;
      is_f64[i] = 0;
      is_mem[i] = 0;
      is_stk[i] = 0;
      arg_sz[i] = 0;
      reg_start[i] = -1;
      reg_units[i] = 0;
      spill_off[i] = -1;
      if (has_recv && i == 0)
        arg_ref = base_ref;
      else
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i - has_recv);
      if (arg_ref == 0)
        continue;
      /* Formal index == place index when receiver is formal 0. */
      pty_i = glue_call_param_type_ref_at(arena, expr_ref, i);
      if (has_recv && i == 0 && need_aref)
        sz = 8;
      else
        sz = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, arg_ref);
      arg_sz[i] = sz;
      is_sse[i] = (ta == 0) ? glue_arg_ref_is_sse_float_c(arena, arg_ref, pty_i) : 0;
      is_f64[i] = glue_arg_ref_is_f64_width_c(arena, arg_ref, pty_i);
      if (is_sse[i]) {
        if (xmm_cur >= 8)
          return -1;
        reg_start[i] = xmm_cur++;
        reg_units[i] = 1;
        continue;
      }
      /*
       * wave606: MEMORY by-value is stack-only on both SysV x86 and AAPCS64.
       * Do NOT coerce units=0 → 1 on arm64 (lea pointer vs callee stack words).
       */
      if (glue_sysv_arg_is_memory_by_value_c(sz)) {
        is_mem[i] = 1;
        continue;
      }
      u = glue_sysv_arg_gp_units_from_size_c(sz);
      if (ta != 0) {
        /* AAPCS64: dual-GP for 9–16B INTEGER; units already 1–2 after MEMORY filter. */
        if (u < 1)
          u = 1;
        if (u > 2)
          u = 2;
      }
      if (gp_cur + u > reg_max) {
        if (u > 1)
          return -1;
        is_stk[i] = 1;
        continue;
      }
      reg_start[i] = gp_cur;
      reg_units[i] = u;
      gp_cur += u;
    }

    /* Push MEMORY / stack excess before reg loads (pad first for 16-align). */
    if (ta == 0) {
      int32_t raw_mem = 0;
      int32_t pushed_total = 0;
      for (i = 0; i < n_place; i++) {
        if (is_mem[i])
          raw_mem += (arg_sz[i] + 7) & ~7;
        else if (is_stk[i])
          raw_mem += 8;
      }
      while (((raw_mem + pushed_total) & 15) != 0) {
        if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0)
          return -1;
        if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
          return -1;
        pushed_total += 8;
      }
      for (i = n_place - 1; i >= 0; i--) {
        int32_t arg_ref;
        int32_t pushed;
        if (is_mem[i]) {
          if (has_recv && i == 0)
            arg_ref = base_ref;
          else
            arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i - has_recv);
          if (arg_ref == 0)
            return -1;
          pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(arena, elf_ctx, ctx, arg_ref, arg_sz[i], ta);
          if (pushed < 0)
            return -1;
          pushed_total += pushed;
        } else if (is_stk[i]) {
          int32_t formal_ix = i;
          if (has_recv && i == 0) {
            arg_ref = base_ref;
            if (need_aref) {
              if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0)
                return -1;
            } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
              /* G.7: receiver uses same pty=formal0 path as extra args (ARRAY_LIT i32x4). */
              return -1;
            }
          } else {
            arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i - has_recv);
            if (arg_ref == 0)
              return -1;
            if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, formal_ix, ctx, ta) != 0)
              return -1;
          }
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0)
            return -1;
          pushed_total += 8;
        }
      }
      mem_stack = pushed_total;
    } else if (ta == 1) {
      /*
       * wave606: AAPCS64 MEMORY / excess stack for UFCS method places — ≡ free CALL
       * wave603 (reserve → GP spill/load → store_memory_to_sp → call → cleanup).
       * Low-end multi-word at [sp+#off]; SP 16-align.
       */
      int32_t nw = 0;
      int32_t stack_reserve;
      for (i = 0; i < n_place; i++) {
        if (is_mem[i])
          nw += glue_sysv_arg_stack_words_c(arg_sz[i], 0);
        else if (is_stk[i])
          nw += 1;
      }
      stack_reserve = nw * 8;
      if (stack_reserve > 0)
        stack_reserve = (stack_reserve + 15) & ~15;
      mem_stack = stack_reserve;
      if (backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve, ta) != 0)
        return -1;
    }

    /* Materialize register places → spill → load (dual-GP safe). */
    for (i = 0; i < n_place; i++) {
      int32_t arg_ref;
      int32_t so;
      int32_t formal_ix = i;
      if (reg_start[i] < 0 || is_mem[i] || is_stk[i])
        continue;
      if (has_recv && i == 0) {
        if (need_aref) {
          if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0)
            return -1;
        } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
          /* G.7: receiver pty=formal0 so ARRAY_LIT SIMD packs dual-GP. */
          return -1;
        }
      } else {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i - has_recv);
        if (arg_ref == 0)
          continue;
        if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, formal_ix, ctx, ta) != 0)
          return -1;
      }
      so = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, reg_units[i]);
      if (so < 0)
        return -1;
      spill_off[i] = so;
    }

    /*
     * Stage 12.0.5: arm64 stack/MEMORY places *before* final GP load (≡ free CALL).
     * wave606 originally placed after load; that clobbered x0 when >8 places
     * (emit stack arg through x0). PLATFORM: MACOS|ARM64 AAPCS64.
     */
    if (ta == 1) {
      int32_t stk_slot = 0;
      for (i = 0; i < n_place; i++) {
        int32_t arg_ref;
        int32_t formal_ix = i;
        int32_t words;
        int32_t stored;
        if (!is_mem[i] && !is_stk[i])
          continue;
        if (has_recv && i == 0)
          arg_ref = base_ref;
        else
          arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i - has_recv);
        if (arg_ref == 0)
          return -1;
        if (is_mem[i]) {
          stored = pipeline_asm_store_memory_by_value_to_sp_elf_c(arena, elf_ctx, ctx, arg_ref,
                                                                   arg_sz[i], ta, stk_slot * 8);
          if (stored < 0)
            return -1;
          words = stored / 8;
          if (words < 1)
            words = 1;
          stk_slot += words;
          continue;
        }
        /* is_stk: single GP excess → store x0 at [sp+off]. */
        if (has_recv && i == 0) {
          if (need_aref) {
            if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0)
              return -1;
          } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
            /* G.7: receiver pty=formal0 so ARRAY_LIT SIMD packs dual-GP. */
            return -1;
          }
        } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, formal_ix, ctx, ta) != 0) {
          return -1;
        }
        if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0)
          return -1;
        stk_slot++;
      }
    }

    /* Load high place index first so lower GPs are not clobbered via x0/rax temp. */
    for (i = n_place - 1; i >= 0; i--) {
      int32_t mov_rc;
      if (spill_off[i] < 0)
        continue;
      if (is_sse[i]) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off[i], ta) != 0)
          return -1;
        if (is_f64[i])
          mov_rc = backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, reg_start[i], ta);
        else
          mov_rc = backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, reg_start[i], ta);
        if (mov_rc != 0)
          return -1;
      } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], reg_start[i],
                                                         reg_units[i]) != 0) {
        return -1;
      }
    }

    /*
     * wave683 Cap residual pure — freestanding multi-method call-site mangle.
     * Root: def side glue_asm_build_func_export_sym_c emits get_S / get_T when
     * overload_count>1 (two impl methods share bare name "get"); UFCS METHOD_CALL
     * still called bare "get" → Ubuntu ld UNDEF get (mac -c .o same U _get; host-C
     * uses codegen_emit_func_link_name and was green).
     * G.7: complete same export-sym authority as def/free CALL mid — no third mangle.
     * Prefer typeck call_resolved_func_index (UFCS stamp, r_dep=-1 local module).
     * Fallback bare method name when unresolved (unique-name / bootstrap leaves).
     * PLATFORM: SHARED freestanding · LINUX gold full link · MACOS -c exposes U get.
     */
    {
      int32_t r_fn_call = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
      int32_t r_dep_call = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
      uint8_t call_sym[128];
      int32_t call_sym_len = -1;
      if (r_fn_call >= 0 && r_dep_call < 0 && mod_ref) {
        call_sym_len = glue_asm_build_func_export_sym_c(mod_ref, arena, r_fn_call, call_sym, 128);
      } else if (r_fn_call >= 0 && r_dep_call >= 0 && ly && ly->dep_pipe) {
        struct ast_Module *dm = pipeline_dep_ctx_module_at(ly->dep_pipe, r_dep_call);
        struct ast_ASTArena *da = pipeline_dep_ctx_arena_at(ly->dep_pipe, r_dep_call);
        if (dm) {
          if (!da)
            da = arena;
          call_sym_len = glue_asm_build_func_export_sym_c(dm, da, r_fn_call, call_sym, 128);
        }
      }
      if (call_sym_len > 0) {
        if (glue_asm_enc_call_redirected(elf_ctx, call_sym, call_sym_len, ta) != 0)
          return -1;
      } else if (glue_asm_enc_call_redirected(elf_ctx, name, name_len, ta) != 0) {
        return -1;
      }
    }
    {
      int32_t cln = mem_stack;
      if (cln > 0 && backend_enc_call_stack_cleanup_arch(elf_ctx, cln, ta) != 0)
        return -1;
    }
    if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0)
      return -1;
    return 0;
  }
}

#ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X
int32_t pipeline_asm_emit_method_call_elf_c(struct ast_ASTArena *arena, struct platform_elf_ElfCodegenCtx *elf_ctx,
                                            int32_t expr_ref, struct backend_AsmFuncCtx *ctx, int32_t ta) {
  return pipeline_asm_emit_method_call_elf_c_impl(arena, elf_ctx, expr_ref, ctx, ta);
}
#endif

/* F7: asm backend native vtable statics + wrapper function emission.
 * Logic source: src/asm/backend_call_dispatch.x (G.7 twin product seed).
 * PLATFORM: SHARED — mirrors codegen.x vtable naming (G.7 single authority).
 */
extern int32_t xlang_skip_impl_seen_count_c(void);
extern int32_t xlang_skip_impl_trait_name_into_c(int32_t si, uint8_t *out64);
extern int32_t xlang_skip_impl_for_type_into_c(int32_t si, int32_t *out_kind,
        int32_t *out_is_ptr, uint8_t *out_name64, int32_t *out_nlen_ptr);
extern int32_t xlang_skip_trait_method_count_c(uint8_t *trait_nm, int32_t trait_nlen);
extern int32_t xlang_skip_trait_method_name_into_c(uint8_t *trait_nm, int32_t trait_nlen,
        int32_t slot_i, uint8_t *out);
extern int32_t codegen_find_impl_method_for_type(struct ast_Module *module, struct ast_ASTArena *arena,
        uint8_t *method_name, int32_t method_name_len, int32_t receiver_type_ref);
extern int32_t codegen_builtin_type_name_into(int32_t kind_ord, uint8_t *out);
extern int32_t pipeline_type_find_or_alloc_named(struct ast_ASTArena *arena, uint8_t *name, int32_t nlen);
extern int32_t pipeline_elf_ctx_add_label(uint8_t *ctx, uint8_t *name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_add_sym(uint8_t *ctx, uint8_t *name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_append_reloc(uint8_t *ctx, int32_t offset, uint8_t *name, int32_t name_len);
/* F7: absolute 64-bit pointer reloc for vtable static data slots. Mirrors .x
 * backend_call_dispatch.x — sent through _typed with r_type=200 sentinel so
 * Mach-O/ELF writers map to ARM64_RELOC_UNSIGNED / R_X86_64_64 / R_AARCH64_ABS64.
 * Without this the default BRANCH26 is applied to data bytes and ld rejects
 * ("relocation on non-b/bl instruction"). G.7 single authority. */
extern int32_t pipeline_elf_ctx_append_reloc_absolute64(uint8_t *ctx, int32_t offset, uint8_t *name, int32_t name_len);
extern int32_t pipeline_elf_ctx_emit_code_len(uint8_t *ctx);
/* F7: data section helpers for vtable static data (__DATA,__const). */
extern int32_t pipeline_elf_ctx_emit_data_len(uint8_t *ctx);
extern int32_t pipeline_elf_ctx_append_data_u32_le(uint8_t *ctx, uint32_t word);
extern void pipeline_elf_ctx_set_shndx_override(uint8_t *ctx, int32_t shndx);
extern int32_t backend_enc_prologue_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t frame_sz, int32_t ta);
extern int32_t backend_enc_epilogue_arch(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta);
extern int32_t backend_enc_append_u32_le_c(struct platform_elf_ElfCodegenCtx *elf_ctx, uint32_t word);

/* F7: outside #ifndef XLANG_L2_CALL_DISPATCH_THIN_FROM_X so thin hybrid path also
 * compiles vtable statics + wrapper functions (must be present in all build profiles). */
int32_t pipeline_asm_emit_vtable_static_name_into(uint8_t *trait_nm, int32_t trait_nlen,
        uint8_t *for_nm, int32_t for_nlen, int32_t is_ptr, uint8_t *out) {
  int32_t w, k, ti, fi;
  uint8_t b;
  static const uint8_t stem[13] = {0x78,0x6c,0x61,0x6e,0x67,0x5f,0x76,0x74,0x61,0x62,0x6c,0x65,0x5f};
  static const uint8_t fk[5] = {0x5f,0x66,0x6f,0x72,0x5f};
  static const uint8_t pk[4] = {0x50,0x74,0x72,0x5f};
  if (!trait_nm || !for_nm || !out) { return -1; }
  if (trait_nlen <= 0 || for_nlen <= 0) { return -1; }
  if (trait_nlen > 64 || for_nlen > 64) { return -1; }
  w = 0;
  for (k = 0; k < 13; k++) { out[w++] = stem[k]; }
  for (ti = 0; ti < trait_nlen; ti++) {
    b = trait_nm[ti];
    out[w++] = (b == '_' || (b >= '0' && b <= '9') || (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) ? b : '_';
  }
  for (k = 0; k < 5; k++) { out[w++] = fk[k]; }
  if (is_ptr) { for (k = 0; k < 4; k++) { out[w++] = pk[k]; } }
  for (fi = 0; fi < for_nlen; fi++) {
    b = for_nm[fi];
    out[w++] = (b == '_' || (b >= '0' && b <= '9') || (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) ? b : '_';
  }
  return w;
}

int32_t pipeline_asm_emit_vtable_wrapper_name_into(uint8_t *trait_nm, int32_t trait_nlen,
        uint8_t *for_nm, int32_t for_nlen, int32_t is_ptr, int32_t slot_i, uint8_t *out) {
  int32_t w, k, ti, fi, n, v, j;
  uint8_t b;
  uint8_t tmp[10];
  static const uint8_t stem[18] = {0x78,0x6c,0x61,0x6e,0x67,0x5f,0x76,0x74,0x61,0x62,0x6c,0x65,0x5f,0x77,0x72,0x61,0x70,0x5f};
  static const uint8_t fk[5] = {0x5f,0x66,0x6f,0x72,0x5f};
  static const uint8_t pk[4] = {0x50,0x74,0x72,0x5f};
  if (!trait_nm || !for_nm || !out) { return -1; }
  if (trait_nlen <= 0 || for_nlen <= 0) { return -1; }
  if (trait_nlen > 64 || for_nlen > 64) { return -1; }
  if (slot_i < 0) { return -1; }
  w = 0;
  for (k = 0; k < 18; k++) { out[w++] = stem[k]; }
  for (ti = 0; ti < trait_nlen; ti++) {
    b = trait_nm[ti];
    out[w++] = (b == '_' || (b >= '0' && b <= '9') || (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) ? b : '_';
  }
  for (k = 0; k < 5; k++) { out[w++] = fk[k]; }
  if (is_ptr) { for (k = 0; k < 4; k++) { out[w++] = pk[k]; } }
  for (fi = 0; fi < for_nlen; fi++) {
    b = for_nm[fi];
    out[w++] = (b == '_' || (b >= '0' && b <= '9') || (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) ? b : '_';
  }
  out[w++] = '_';
  if (slot_i == 0) { out[w++] = '0'; }
  else {
    n = 0; v = slot_i;
    while (v > 0 && n < 10) { tmp[n++] = '0' + (uint8_t)(v % 10); v /= 10; }
    for (j = n - 1; j >= 0; j--) { out[w++] = tmp[j]; }
  }
  return w;
}

int32_t pipeline_asm_emit_vtable_wrapper_def(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta,
        struct ast_Module *module, struct ast_ASTArena *arena,
        uint8_t *trait_nm, int32_t trait_nlen, uint8_t *for_nm, int32_t for_nlen,
        int32_t for_ptr, int32_t slot_i, int32_t recv_rt) {
  uint8_t meth_nm[64]; int32_t meth_nlen;
  int32_t impl_fi; uint8_t impl_nm[128]; int32_t impl_nlen;
  uint8_t wrap_nm[168]; int32_t wrap_nlen;
  int32_t macho; uint8_t sym_nm[170]; int32_t sym_nlen;
  int32_t entry_off, k;
  int32_t nparams_w, reg_max_w, n_stk_w, stk_bytes_w, si_w;
  if (!elf_ctx || !module || !arena) { return -1; }
  if (!trait_nm || !for_nm) { return -1; }
  if (trait_nlen <= 0 || for_nlen <= 0 || slot_i < 0) { return -1; }
  meth_nlen = xlang_skip_trait_method_name_into_c(trait_nm, trait_nlen, slot_i, meth_nm);
  if (meth_nlen <= 0) { return 0; }
  impl_fi = codegen_find_impl_method_for_type(module, arena, meth_nm, meth_nlen, recv_rt);
  if (impl_fi < 0) { return 0; }
  pipeline_module_func_set_is_used(module, impl_fi, 1);
  impl_nlen = glue_asm_build_func_export_sym_c(module, arena, impl_fi, impl_nm, 128);
  if (impl_nlen <= 0) { return -1; }
  wrap_nlen = pipeline_asm_emit_vtable_wrapper_name_into(trait_nm, trait_nlen,
          for_nm, for_nlen, for_ptr, slot_i, wrap_nm);
  if (wrap_nlen <= 0) { return -1; }
  macho = pipeline_elf_ctx_macho_leading_underscore((uint8_t *)elf_ctx);
  sym_nlen = wrap_nlen;
  if (macho) {
    sym_nm[0] = '_';
    for (k = 0; k < wrap_nlen && k < 168; k++) { sym_nm[k + 1] = wrap_nm[k]; }
    sym_nlen = wrap_nlen + 1;
  } else {
    for (k = 0; k < wrap_nlen && k < 169; k++) { sym_nm[k] = wrap_nm[k]; }
  }
  entry_off = pipeline_elf_ctx_emit_code_len((uint8_t *)elf_ctx);
  if (entry_off < 0) { return -1; }
  if (pipeline_elf_ctx_add_label((uint8_t *)elf_ctx, sym_nm, sym_nlen, entry_off) != 0) { return -1; }
  if (pipeline_elf_ctx_add_sym((uint8_t *)elf_ctx, sym_nm, sym_nlen, entry_off) != 0) { return -1; }
  if (backend_enc_prologue_arch(elf_ctx, 16, ta) != 0) { return -1; }
  if (for_ptr == 0) {
    if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, 0, ta) != 0) { return -1; }
    if (ta == 0) {
      if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) { return -1; }
    }
  }
  /* Copy incoming stack extras to impl outgoing stack. rdi/x0 stays data.
   * PLATFORM: LINUX x86_64 SysV [rbp+16] · MACOS|ARM64 [x29,#32] after prologue(16). */
  nparams_w = pipeline_module_func_num_params_at(module, impl_fi);
  reg_max_w = glue_asm_call_reg_max(ta);
  if (reg_max_w < 2)
    reg_max_w = 6;
  n_stk_w = 0;
  if (nparams_w > reg_max_w)
    n_stk_w = nparams_w - reg_max_w;
  stk_bytes_w = 0;
  if (n_stk_w > 0) {
    if (ta == 0) {
      if ((n_stk_w & 1) != 0) {
        if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return -1; }
        if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return -1; }
        stk_bytes_w = stk_bytes_w + 8;
      }
      for (si_w = n_stk_w - 1; si_w >= 0; si_w--) {
        if (backend_enc_load_rbp_pos_to_rax_arch(elf_ctx, 16 + si_w * 8, ta) != 0)
          return -1;
        if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return -1; }
        stk_bytes_w = stk_bytes_w + 8;
      }
    } else {
      /* PLATFORM: MACOS|ARM64 — load_x29_pos writes x0 (arg0). Save remapped
       * self at [sp,#24]==[x29,#24] before reserve; restore after copy.
       * Slot 24 is prologue(16) pad after x19. Do not use mov_rax_to_rbx
       * (also writes x1). G.7 complete this wrapper. */
      if (backend_enc_store_x0_sp_offset_arch(elf_ctx, 24, ta) != 0)
        return -1;
      stk_bytes_w = n_stk_w * 8;
      stk_bytes_w = (stk_bytes_w + 15) & -16;
      if (backend_enc_call_stack_reserve_arch(elf_ctx, stk_bytes_w, ta) != 0)
        return -1;
      for (si_w = 0; si_w < n_stk_w; si_w++) {
        if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, 32 + si_w * 8, ta) != 0)
          return -1;
        if (backend_enc_store_x0_sp_offset_arch(elf_ctx, si_w * 8, ta) != 0)
          return -1;
      }
      if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, 24, ta) != 0)
        return -1;
    }
  }
  if (backend_enc_call_arch(elf_ctx, impl_nm, impl_nlen, ta) != 0) { return -1; }
  if (stk_bytes_w > 0) {
    if (backend_enc_call_stack_cleanup_arch(elf_ctx, stk_bytes_w, ta) != 0)
      return -1;
  }
  if (backend_enc_epilogue_arch(elf_ctx, ta) != 0) { return -1; }
  return 1;
}

int32_t pipeline_asm_emit_module_vtable_statics(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t ta,
        struct ast_Module *module, struct ast_ASTArena *arena) {
  int32_t n_impl, si, for_k, for_ptr, for_nlen, is_builtin;
  int32_t recv_rt, meth_count, wi, rc, macho, vt_nlen, vt_sym_nlen;
  int32_t vt_off, slot_i, slot_off, wrap_nlen, wrap_sym_nlen, k;
  uint8_t trait_nm[64]; int32_t trait_nlen;
  uint8_t for_nm[64];
  uint8_t vt_nm[150]; uint8_t vt_sym[152];
  uint8_t wrap_nm[168]; uint8_t wrap_sym[170];
  int32_t has_impl[64];
  const int32_t PTR_KIND = 9;
  if (!elf_ctx || !module || !arena) { return -1; }
  n_impl = xlang_skip_impl_seen_count_c();
  if (n_impl <= 0) { return 0; }
  for (si = 0; si < n_impl; si++) {
    trait_nlen = xlang_skip_impl_trait_name_into_c(si, trait_nm);
    if (trait_nlen <= 0) { continue; }
    for_k = 0; for_ptr = 0; for_nlen = 0;
    if (xlang_skip_impl_for_type_into_c(si, &for_k, &for_ptr, for_nm, &for_nlen) == 0) { continue; }
    is_builtin = 0;
    if (for_nlen <= 0) {
      int32_t blen = codegen_builtin_type_name_into(for_k, for_nm);
      if (blen <= 0) { continue; }
      for_nlen = blen; is_builtin = 1;
    }
    recv_rt = 0;
    if (is_builtin) {
      recv_rt = pipeline_type_find_or_alloc_compound(arena, for_k, 0, 0);
    } else {
      recv_rt = pipeline_type_find_or_alloc_named(arena, for_nm, for_nlen);
    }
    if (recv_rt <= 0) { continue; }
    if (for_ptr) {
      recv_rt = pipeline_type_find_or_alloc_compound(arena, PTR_KIND, recv_rt, 0);
      if (recv_rt <= 0) { continue; }
    }
    meth_count = xlang_skip_trait_method_count_c(trait_nm, trait_nlen);
    if (meth_count <= 0) { continue; }
    for (wi = 0; wi < meth_count && wi < 64; wi++) { has_impl[wi] = 0; }
    for (wi = 0; wi < meth_count && wi < 64; wi++) {
      rc = pipeline_asm_emit_vtable_wrapper_def(elf_ctx, ta, module, arena,
              trait_nm, trait_nlen, for_nm, for_nlen, for_ptr, wi, recv_rt);
      if (rc < 0) { return -1; }
      has_impl[wi] = rc;
    }
    vt_nlen = pipeline_asm_emit_vtable_static_name_into(trait_nm, trait_nlen,
            for_nm, for_nlen, for_ptr, vt_nm);
    if (vt_nlen <= 0) { continue; }
    macho = pipeline_elf_ctx_macho_leading_underscore((uint8_t *)elf_ctx);
    vt_sym_nlen = vt_nlen;
    if (macho) {
      vt_sym[0] = '_';
      for (k = 0; k < vt_nlen && k < 150; k++) { vt_sym[k + 1] = vt_nm[k]; }
      vt_sym_nlen = vt_nlen + 1;
    } else {
      for (k = 0; k < vt_nlen && k < 151; k++) { vt_sym[k] = vt_nm[k]; }
    }
    /* F7: vtable static data goes to __DATA,__const section (separate from
     * __TEXT,__text which rejects absolute pointer relocations). Override the
     * current shndx so all new labels/syms/relocs are tagged as data section.
     * Single-threaded compile; restore to 0 before returning. */
    pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 4);
    vt_off = pipeline_elf_ctx_emit_data_len((uint8_t *)elf_ctx);
    if (vt_off < 0) {
      pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
      return -1;
    }
    if (pipeline_elf_ctx_add_label((uint8_t *)elf_ctx, vt_sym, vt_sym_nlen, vt_off) != 0) {
      pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
      return -1;
    }
    if (pipeline_elf_ctx_add_sym((uint8_t *)elf_ctx, vt_sym, vt_sym_nlen, vt_off) != 0) {
      pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
      return -1;
    }
    for (slot_i = 0; slot_i < meth_count && slot_i < 64; slot_i++) {
      slot_off = pipeline_elf_ctx_emit_data_len((uint8_t *)elf_ctx);
      if (slot_off < 0) {
        pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
        return -1;
      }
      if (pipeline_elf_ctx_append_data_u32_le((uint8_t *)elf_ctx, 0) != 0) {
        pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
        return -1;
      }
      if (pipeline_elf_ctx_append_data_u32_le((uint8_t *)elf_ctx, 0) != 0) {
        pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
        return -1;
      }
      if (has_impl[slot_i]) {
        wrap_nlen = pipeline_asm_emit_vtable_wrapper_name_into(trait_nm, trait_nlen,
                for_nm, for_nlen, for_ptr, slot_i, wrap_nm);
        if (wrap_nlen <= 0) {
          pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
          return -1;
        }
        wrap_sym_nlen = wrap_nlen;
        if (macho) {
          wrap_sym[0] = '_';
          for (k = 0; k < wrap_nlen && k < 168; k++) { wrap_sym[k + 1] = wrap_nm[k]; }
          wrap_sym_nlen = wrap_nlen + 1;
        } else {
          for (k = 0; k < wrap_nlen && k < 169; k++) { wrap_sym[k] = wrap_nm[k]; }
        }
        if (pipeline_elf_ctx_append_reloc_absolute64((uint8_t *)elf_ctx, slot_off, wrap_sym, wrap_sym_nlen) != 0) {
          pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
          return -1;
        }
      }
    }
    /* F7: restore shndx override to 0 (text section) after vtable static emit. */
    pipeline_elf_ctx_set_shndx_override((uint8_t *)elf_ctx, 0);
  }
  return 0;
}

/* F7: TYPE_DYN let-init fat-pointer materialize. Twin of .x. */
int32_t pipeline_asm_try_emit_dyn_coerce_let(struct ast_ASTArena *arena,
        struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t block_ref, int32_t idx,
        int32_t init_ref, int32_t slot_off, struct backend_AsmFuncCtx *ctx, int32_t ta) {
  int32_t let_ty, lt_dyn, rhs_rt, recv_kind, is_ptr, name_rt, trait_nlen, for_nlen;
  int32_t vt_nlen, macho, vt_sym_nlen, k, elem_rt;
  uint8_t trait_nm[64];
  uint8_t for_nm[64];
  uint8_t vt_nm[160];
  uint8_t vt_sym[162];
  if (arena == 0 || elf_ctx == 0 || ctx == 0) return -1;
  if (block_ref <= 0 || idx < 0 || init_ref <= 0) return 0;
  let_ty = pipeline_block_let_type_ref(arena, block_ref, idx);
  if (let_ty <= 0) return 0;
  lt_dyn = pipeline_typeck_resolve_type_alias_ref_c(arena, let_ty);
  if (lt_dyn <= 0) return 0;
  if (pipeline_type_kind_ord_at(arena, lt_dyn) != 17) return 0;
  if (pipeline_expr_kind_ord_at(arena, init_ref) == 0 &&
      pipeline_expr_int_val_at(arena, init_ref) == 0)
    return 0;
  rhs_rt = pipeline_expr_resolved_type_ref(arena, init_ref);
  if (rhs_rt <= 0) return -1;
  recv_kind = pipeline_type_kind_ord_at(arena, rhs_rt);
  is_ptr = 0;
  name_rt = rhs_rt;
  if (recv_kind == 9) {
    elem_rt = pipeline_type_elem_ref_at(arena, rhs_rt);
    if (elem_rt > 0 && pipeline_type_kind_ord_at(arena, elem_rt) == 8) {
      is_ptr = 1;
      name_rt = elem_rt;
    }
  }
  trait_nlen = pipeline_type_named_name_into(arena, lt_dyn, trait_nm);
  if (trait_nlen <= 0) return -1;
  for_nlen = pipeline_type_named_name_into(arena, name_rt, for_nm);
  /* F7 neighborhood / F6 twin: impl Trait for builtin.
   * G.7: codegen_builtin_type_name_into is the sole kind→name map.
   * PLATFORM: SHARED. */
  {
    int32_t is_builtin = 0;
    if (for_nlen <= 0) {
      int32_t bk = pipeline_type_kind_ord_at(arena, name_rt);
      for_nlen = codegen_builtin_type_name_into(bk, for_nm);
      if (for_nlen <= 0) return -1;
      is_builtin = 1;
    }
    /* PTR: data IS the pointer. NAMED: LEA local. Builtin rvalue (INT_LIT):
     * emit+spill+LEA. Wrapper rdi/x0 = data — do not change that ABI.
     * EXPR_VAR ordinal is 3. PLATFORM: SHARED. */
    if (is_ptr != 0) {
      if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, init_ref, ctx, ta) != 0) return -1;
    } else if (is_builtin != 0) {
      int32_t ek = pipeline_expr_kind_ord_at(arena, init_ref);
      if (ek == 3) {
        if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, init_ref, ctx, ta) != 0) return -1;
      } else {
        int32_t spill;
        if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, init_ref, ctx, ta) != 0) return -1;
        spill = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
        if (spill < 0) return -1;
        if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, spill, ta) != 0) return -1;
      }
    } else {
      if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, init_ref, ctx, ta) != 0) return -1;
    }
  }
  if (backend_enc_store_rax_to_rbp_arch(elf_ctx, slot_off, ta) != 0) return -1;
  vt_nlen = pipeline_asm_emit_vtable_static_name_into(trait_nm, trait_nlen, for_nm, for_nlen, is_ptr, vt_nm);
  if (vt_nlen <= 0) return -1;
  macho = pipeline_elf_ctx_macho_leading_underscore((uint8_t *)elf_ctx);
  if (macho != 0) {
    vt_sym[0] = 95;
    for (k = 0; k < vt_nlen && k < 160; k++) vt_sym[k + 1] = vt_nm[k];
    vt_sym_nlen = vt_nlen + 1;
  } else {
    for (k = 0; k < vt_nlen && k < 161; k++) vt_sym[k] = vt_nm[k];
    vt_sym_nlen = vt_nlen;
  }
  if (backend_enc_lea_sym_to_reg_arch(elf_ctx, 1, vt_sym, vt_sym_nlen, ta) != 0) return -1;
  /* Fat {data,vtable}: ARM64 [x29,#off+8] is +8 in address space.
   * x86 [rbp,#-off] so +8 field is slot_off-8. PLATFORM: LINUX x86_64 rbp-down. */
  {
    int32_t vt_home = slot_off + 8;
    if (ta == 0) {
      if (slot_off <= 8) return -1;
      vt_home = slot_off - 8;
    }
    if (backend_enc_store_x_reg_to_rbp_arch(elf_ctx, 1, vt_home, ta) != 0) return -1;
  }
  return 1;
}

#else /* XLANG_BACKEND_CALL_DISPATCH_FROM_X：产品 rest 业务 H=0 */
int backend_call_dispatch_slice_marker(void) {
  return 0;
}
#endif /* XLANG_BACKEND_CALL_DISPATCH_FROM_X */
