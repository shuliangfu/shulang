/* Generated from x_frontend_link_alias.x (G-02f-26 true .x + C tail).
 * Regen: ./xlang-c -E -L .. x_frontend_link_alias.x > /tmp/xfla.c
 *         then re-apply weak polish + lexer C tail (see G-02f-26).
 * lexer_* struct returns remain C; other forwards are .x.
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <stddef.h>
extern int32_t typeck_x_ast(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern int32_t typeck_x_ast_library(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern void typeck_merge_dep_struct_layouts_into_entry(uint8_t * mod, uint8_t * arena, uint8_t * ctx);
extern void typeck_wpo_unify_soa_layouts(uint8_t * entry, uint8_t * ctx);
extern int32_t pipeline_typeck_check_block_impl_c(uint8_t * module, uint8_t * arena, int32_t block_ref, int32_t return_type_ref, uint8_t * ctx);
extern int32_t pipeline_typeck_check_expr_impl_c(uint8_t * module, uint8_t * arena, int32_t expr_ref, int32_t return_type_ref, uint8_t * ctx);
extern int32_t typeck_find_or_alloc_ptr_type_ref(uint8_t * arena, int32_t elem_ref);
extern int32_t pipeline_module_num_funcs(uint8_t * module);
extern int32_t pipeline_module_main_func_index(uint8_t * module);
extern void pipeline_module_struct_layout_set_soa(uint8_t * m, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_soa_at(uint8_t * m, int32_t idx);
extern int32_t pipeline_module_struct_layout_packed_at(uint8_t * m, int32_t idx);
extern int32_t pipeline_module_struct_layout_field_align_at(uint8_t * m, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_align(uint8_t * m, int32_t li, int32_t j, int32_t al);
extern int32_t codegen_x_ast_emit_header(uint8_t * out);
extern int32_t codegen_x_ast(uint8_t * module, uint8_t * arena, uint8_t * out, uint8_t * ctx, int32_t dep_index);
int32_t typeck_pipeline_module_num_funcs(uint8_t * module) {
  (void)(({   {
    int32_t r = pipeline_module_num_funcs(module);
    return r;
  }
 }));
  return 0;
}
int32_t typeck_pipeline_module_main_func_index(uint8_t * module) {
  (void)(({   {
    int32_t r = pipeline_module_main_func_index(module);
    return r;
  }
 }));
  return 0;
}
int32_t typeck_typeck_x_ast(uint8_t * module, uint8_t * arena, uint8_t * ctx) {
  (void)(({   {
    int32_t r = typeck_x_ast(module, arena, ctx);
    return r;
  }
 }));
  return 0;
}
int32_t typeck_typeck_x_ast_library(uint8_t * module, uint8_t * arena, uint8_t * ctx) {
  (void)(({   {
    int32_t r = typeck_x_ast_library(module, arena, ctx);
    return r;
  }
 }));
  return 0;
}
void typeck_typeck_merge_dep_struct_layouts_into_entry(uint8_t * mod, uint8_t * arena, uint8_t * ctx) {
  (void)(({   {
    (void)(typeck_merge_dep_struct_layouts_into_entry(mod, arena, ctx));
  }
 }));
}
void typeck_typeck_wpo_unify_soa_layouts(uint8_t * entry, uint8_t * ctx) {
  (void)(({   {
    (void)(typeck_wpo_unify_soa_layouts(entry, ctx));
  }
 }));
}
XLANG_WEAK int32_t check_block_impl(uint8_t * module, uint8_t * arena, int32_t block_ref, int32_t return_type_ref, uint8_t * ctx) {
  (void)(({   {
    int32_t r = pipeline_typeck_check_block_impl_c(module, arena, block_ref, return_type_ref, ctx);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t check_expr_impl(uint8_t * module, uint8_t * arena, int32_t expr_ref, int32_t return_type_ref, uint8_t * ctx) {
  (void)(({   {
    int32_t r = pipeline_typeck_check_expr_impl_c(module, arena, expr_ref, return_type_ref, ctx);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK int32_t find_or_alloc_ptr_type_ref(uint8_t * arena, int32_t elem_ref) {
  (void)(({   {
    int32_t r = typeck_find_or_alloc_ptr_type_ref(arena, elem_ref);
    return r;
  }
 }));
  return 0;
}
XLANG_WEAK void pipeline_typeck_set_active_ctx_c(uint8_t * module, uint8_t * ctx) {
  (void)(0);
}
XLANG_WEAK int32_t pipeline_typeck_ptr_for_addr_of_operand_c(uint8_t * arena, int32_t op_ref, int32_t elem_ty, uint8_t * module, uint8_t * ctx) {
  return 0;
}
void ast_pipeline_module_struct_layout_set_soa(uint8_t * m, int32_t idx, int32_t v) {
  (void)(({   {
    (void)(pipeline_module_struct_layout_set_soa(m, idx, v));
  }
 }));
}
int32_t ast_pipeline_module_struct_layout_soa_at(uint8_t * m, int32_t idx) {
  (void)(({   {
    int32_t r = pipeline_module_struct_layout_soa_at(m, idx);
    return r;
  }
 }));
  return 0;
}
int32_t ast_pipeline_module_struct_layout_packed_at(uint8_t * m, int32_t idx) {
  (void)(({   {
    int32_t r = pipeline_module_struct_layout_packed_at(m, idx);
    return r;
  }
 }));
  return 0;
}
int32_t ast_pipeline_module_struct_layout_field_align_at(uint8_t * m, int32_t li, int32_t j) {
  (void)(({   {
    int32_t r = pipeline_module_struct_layout_field_align_at(m, li, j);
    return r;
  }
 }));
  return 0;
}
void ast_pipeline_module_struct_layout_set_field_align(uint8_t * m, int32_t li, int32_t j, int32_t al) {
  (void)(({   {
    (void)(pipeline_module_struct_layout_set_field_align(m, li, j, al));
  }
 }));
}
int32_t codegen_codegen_x_ast_emit_header(uint8_t * out) {
  (void)(({   {
    int32_t r = codegen_x_ast_emit_header(out);
    return r;
  }
 }));
  return 0;
}
int32_t codegen_codegen_x_ast(uint8_t * module, uint8_t * arena, uint8_t * out, uint8_t * ctx, int32_t dep_index) {
  (void)(({   {
    int32_t r = codegen_x_ast(module, arena, out, ctx, dep_index);
    return r;
  }
 }));
  return 0;
}

/* ---- lexer C tail (G-02f-26): struct-return ABI not yet from .x ---- */
struct lexer_Lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};
struct lexer_LexerResult {
  int32_t tok;
  int64_t int_val;
  double float_val;
  struct lexer_Lexer next_lex;
};
struct xlang_slice_uint8_t;
extern struct lexer_Lexer lexer_init(void);
extern void lexer_next_into(struct lexer_LexerResult *out, struct lexer_Lexer lex,
                            struct xlang_slice_uint8_t *data);
extern struct lexer_LexerResult lexer_next_buf(struct lexer_Lexer lex,
                                               struct xlang_slice_uint8_t *data);

struct lexer_Lexer lexer_lexer_init(void) {
  return lexer_init();
}
void lexer_lexer_next_into(struct lexer_LexerResult *out, struct lexer_Lexer lex,
                         struct xlang_slice_uint8_t *data) {
  lexer_next_into(out, lex, data);
}
struct lexer_LexerResult lexer_lexer_next_buf(struct lexer_Lexer lex,
                                            struct xlang_slice_uint8_t *data) {
  return lexer_next_buf(lex, data);
}

/* R2 full try_inline/call_dispatch：.x -E 对 extern "C" 仍发 ABI 后缀名；
 * 产品 pipeline 导出无后缀符号。弱别名桥接（非业务双权威）。 */
extern int32_t pipeline_expr_field_access_name_len(uint8_t *a, int32_t er);
extern void pipeline_expr_field_access_name_into(uint8_t *a, int32_t er, uint8_t *dst);
extern int32_t pipeline_expr_field_access_base_ref(uint8_t *a, int32_t er);
extern int32_t pipeline_expr_binop_left_ref_at(uint8_t *a, int32_t er);
extern int32_t pipeline_expr_binop_right_ref_at(uint8_t *a, int32_t er);
extern int32_t pipeline_dep_ctx_ndep(uint8_t *ctx);
extern uint8_t *pipeline_dep_ctx_module_at(uint8_t *ctx, int32_t i);
extern uint8_t *pipeline_asm_emit_dep_pipe_c(void);
extern uint8_t pipeline_module_import_path_byte_at(uint8_t *m, int32_t i, int32_t j);

XLANG_WEAK int32_t pipeline_expr_field_access_name_len_u8_ptr_i32_reti32(uint8_t *a, int32_t er) {
  return pipeline_expr_field_access_name_len(a, er);
}
XLANG_WEAK void pipeline_expr_field_access_name_into_u8_ptr_i32_u8_ptr(uint8_t *a, int32_t er, uint8_t *dst) {
  pipeline_expr_field_access_name_into(a, er, dst);
}
XLANG_WEAK int32_t pipeline_expr_field_access_base_ref_u8_ptr_i32_reti32(uint8_t *a, int32_t er) {
  return pipeline_expr_field_access_base_ref(a, er);
}
XLANG_WEAK int32_t pipeline_expr_binop_left_ref_at_u8_ptr_i32_reti32(uint8_t *a, int32_t er) {
  return pipeline_expr_binop_left_ref_at(a, er);
}
XLANG_WEAK int32_t pipeline_expr_binop_right_ref_at_u8_ptr_i32_reti32(uint8_t *a, int32_t er) {
  return pipeline_expr_binop_right_ref_at(a, er);
}
XLANG_WEAK int32_t pipeline_dep_ctx_ndep_u8_ptr_reti32(uint8_t *ctx) {
  return pipeline_dep_ctx_ndep(ctx);
}
XLANG_WEAK uint8_t *pipeline_dep_ctx_module_at_u8_ptr_i32_retu8_ptr(uint8_t *ctx, int32_t i) {
  return pipeline_dep_ctx_module_at(ctx, i);
}
XLANG_WEAK uint8_t *pipeline_asm_emit_dep_pipe_c_retu8_ptr(void) {
  return pipeline_asm_emit_dep_pipe_c();
}
XLANG_WEAK uint8_t pipeline_module_import_path_byte_at_u8_ptr_i32_i32_retu8(uint8_t *m, int32_t i, int32_t j) {
  return pipeline_module_import_path_byte_at(m, i, j);
}

/* wave L7-check residual: backend_call_dispatch X-ABI mangled faces → C product symbols.
 * Needed when call_dispatch.o expects mangled names not produced by host-cc seed path.
 * PLATFORM: SHARED link residual (G.7 alias face; not dual implementation). */
extern int32_t glue_asm_build_func_export_sym_c(void *a, void *b, int32_t c, void *d, int32_t e);
int32_t glue_asm_build_func_export_sym_c_u8_ptr_u8_ptr_i32_u8_ptr_i32_reti32(
    void *a, void *b, int32_t c, void *d, int32_t e) {
  return glue_asm_build_func_export_sym_c(a, b, c, d, e);
}
extern int32_t glue_asm_build_import_binding_call_sym(void *a, int32_t b, void *c, int32_t d, void *e);
int32_t glue_asm_build_import_binding_call_sym_u8_ptr_i32_u8_ptr_i32_u8_ptr_reti32(
    void *a, int32_t b, void *c, int32_t d, void *e) {
  return glue_asm_build_import_binding_call_sym(a, b, c, d, e);
}
extern void glue_codegen_import_path_to_c_prefix_into(void *a, void *b, int32_t c);
void glue_codegen_import_path_to_c_prefix_into_u8_ptr_u8_ptr_i32(void *a, void *b, int32_t c) {
  glue_codegen_import_path_to_c_prefix_into(a, b, c);
}
extern int32_t pipeline_type_kind_ord_at(void *a, int32_t r);
int32_t pipeline_type_kind_ord_at_u8_ptr_i32_reti32(void *a, int32_t r) {
  return pipeline_type_kind_ord_at(a, r);
}
/* X-ABI mangled face for the 4-param heap-redirect local (name, nlen, out,
 * out_cap): the -E'd backend_call_dispatch.x emits signature-suffixed calls
 * to it, and the strong plain-name body lives in backend_call_dispatch.o
 * (seed + prefer lanes alike). Replaces the stale pre-cap 3-param weak stub
 * (fossil of the old signature, satisfied nobody). Without this face the
 * seed-phase1 / g05 pure-ld links fail on
 * glue_try_std_heap_redirect_sym_local_u8_ptr_i32_u8_ptr_i32_reti32 unless
 * the generated asm_full_link_stubs scan happens to cover the gap.
 * PLATFORM: SHARED. */
extern int32_t glue_try_std_heap_redirect_sym_local(void *name, int32_t nlen, void *out, int32_t out_cap);
int32_t glue_try_std_heap_redirect_sym_local_u8_ptr_i32_u8_ptr_i32_reti32(
    void *name, int32_t nlen, void *out, int32_t out_cap) {
  return glue_try_std_heap_redirect_sym_local(name, nlen, out, out_cap);
}
