/* generated from ast */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: CRASH_EVIDENCE path → Cap snprintf */
/* G.7: Cap after stdio for compiler-only gen seed pin crash evidence. */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_io_cap.h>   /* Cap residual 9.5.3: xlang_io_write / xlang_io_open_write */
#include <xlang_proc_cap.h> /* Cap residual 9.5.3: xlang_proc_close_fd (single close authority) */
#include <string.h>
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[64]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; uint8_t region_label[64]; int32_t region_label_len; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t var_name[64]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_base; int32_t match_num_arms; int32_t field_access_base_ref; uint8_t field_access_field_name[64]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t field_access_soa_stride; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_base; int32_t call_num_args; int32_t call_num_type_args; int32_t method_call_base_ref; uint8_t method_call_name[64]; int32_t method_call_name_len; int32_t method_call_arg_base; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[64]; int32_t struct_lit_struct_name_len; int32_t struct_lit_field_base; int32_t struct_lit_num_fields; int32_t array_lit_elem_base; int32_t array_lit_num_elems; int32_t float_bits_lo; int32_t float_bits_hi; int32_t enum_variant_tag; int32_t as_operand_ref; int32_t as_target_type_ref; int32_t call_resolved_func_index; int32_t call_resolved_dep_index; };
struct ast_ConstDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_IfStmt { int32_t cond_ref; int32_t then_body_ref; int32_t else_body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[32]; int32_t label_len; int32_t is_goto; uint8_t goto_target[32]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { int32_t const_base; int32_t num_consts; int32_t let_base; int32_t num_lets; int32_t num_early_lets; int32_t loop_base; int32_t num_loops; int32_t for_loop_base; int32_t num_for_loops; int32_t if_base; int32_t num_if_stmts; int32_t region_base; int32_t num_regions; int32_t defer_base; int32_t num_defers; int32_t labeled_base; int32_t num_labeled_stmts; int32_t expr_stmt_base; int32_t num_expr_stmts; int32_t final_expr_ref; int32_t stmt_order_base; int32_t num_stmt_order; int32_t parent_block_ref; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[64]; int32_t name_len; int32_t param_base; int32_t num_params; int32_t num_generic_params; int32_t return_type_ref; int32_t body_ref; int32_t body_expr_ref; int32_t is_extern; int32_t is_async; int32_t is_used; int32_t is_naked; int32_t is_entry; int32_t is_no_mangle; int32_t is_interrupt; int32_t abi_kind; int32_t is_variadic; int32_t is_export; };
struct ast_StructLayout { uint8_t name[64]; int32_t name_len; int32_t field_base; int32_t num_fields; int32_t allow_padding; int32_t soa; int32_t packed; int32_t repr_compatible; int32_t is_export; };
struct ast_Module { int32_t num_funcs; int32_t main_func_index; int32_t num_imports; int32_t num_top_level_lets; int32_t num_struct_layouts; int32_t pending_allow_padding; int32_t pending_soa_struct; int32_t pending_cfg_skip; int32_t pending_repr_c_struct; int32_t pending_repr_compatible_struct; int32_t pending_used; int32_t pending_naked; int32_t pending_entry; int32_t pending_no_mangle; int32_t pending_interrupt; int32_t pending_export; int32_t num_module_enums; };
struct ast_ASTArena { int32_t num_types; int32_t num_exprs; int32_t num_blocks; int32_t num_funcs; };

/* slim arena grow pool glue (linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);
extern void ast_ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);

struct ast_PipelineDepCtx { int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t path_buf[512]; uint8_t loaded_buf[4194304]; ptrdiff_t loaded_len; uint8_t preprocess_buf[4194304]; int32_t preprocess_len; int32_t use_asm_backend; int32_t target_arch; int32_t target_cpu_features; int32_t use_macho_o; int32_t use_coff_o; int32_t current_block_ref; int32_t typeck_loop_depth; int32_t current_func_index; int32_t skip_codegen_dep_0; int32_t entry_already_parsed; int32_t current_func_single_empty_param_index; int32_t current_func_empty_param_count; int32_t current_emit_empty_var_next_index; int32_t emit_expr_as_callee; struct ast_Module * current_codegen_module; struct ast_ASTArena * current_codegen_arena; int32_t current_codegen_dep_index; uint8_t current_codegen_prefix_mirror[64]; int32_t current_codegen_prefix_len; int32_t asm_entry_module_only; uint8_t entry_module_import_path_mirror[64]; int32_t entry_module_import_path_len; int32_t typeck_scope_region_len; uint8_t typeck_scope_region_label[64]; };
extern char *link_abi_getenv(const char *name);
extern int getpid(void);
static inline void xlang_crash_evidence_collect_inline(int has_msg, int msg_val) {
  const char *_ev = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  char _note[192];
  if (!_ev || _ev[0] != '1') return;
  int _pid = (int)getpid();
  { int _n = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val, _pid);
    if (_n > 0) (void)xlang_io_write(2, _note, (size_t)_n); }
  { const char *_dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (_dir && _dir[0]) { char _p[1024]; snprintf(_p, sizeof _p, "%s/xlang-crash-%d.txt", _dir, _pid);
      { int _fd = xlang_io_open_write(_p);
        if (_fd >= 0) { char _body[160];
          int _bl = snprintf(_body, sizeof _body, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, _pid);
          if (_bl > 0) (void)xlang_io_write(_fd, _body, (size_t)_bl);
          (void)xlang_proc_close_fd(_fd);
          { int _bn = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] bundle=%s\n", _p);
            if (_bn > 0) (void)xlang_io_write(2, _note, (size_t)_bn); } } } } }
}
static inline void xlang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static inline void xlang_panic_(int has_msg, int msg_val) {
  xlang_crash_evidence_collect_inline(has_msg, msg_val);
  if (has_msg) { char _mb[32]; int _mn = snprintf(_mb, sizeof _mb, "%d\n", msg_val);
    if (_mn > 0) (void)xlang_io_write(2, _mb, (size_t)_mn); }
  abort();
}
extern void ast_pool_block_on_alloc(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_block_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_type_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_expr_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_block_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_func_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern int32_t pipeline_arena_type_cap();
extern int32_t pipeline_arena_expr_cap();
extern int32_t pipeline_arena_block_cap();
extern int32_t pipeline_arena_func_cap();
extern int32_t pipeline_module_import_alloc(struct ast_Module * module);
extern void pipeline_module_import_set_path(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_path_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_path_copy(struct ast_Module * module, int32_t idx, uint8_t * dst, int32_t dst_cap);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_kind(struct ast_Module * module, int32_t idx, int32_t kind);
extern int32_t pipeline_module_import_kind_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_binding_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_select_count(struct ast_Module * module, int32_t idx, int32_t n);
extern int32_t pipeline_module_import_append_select_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_count_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_select_name(struct ast_Module * module, int32_t idx, int32_t sel, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_name_len(struct ast_Module * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(struct ast_Module * module, int32_t idx, int32_t sel, int32_t off);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t li, int32_t j, uint8_t * fname_bytes, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_name_into(struct ast_Module * module, int32_t idx, uint8_t * out64);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module * module, int32_t li, int32_t j, uint8_t * out64);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t idx, int32_t nf);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_top_level_let_alloc(struct ast_Module * module);
extern void pipeline_module_top_level_let_set(struct ast_Module * module, int32_t idx, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref, int32_t is_const);
extern int32_t pipeline_module_top_level_let_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_top_level_let_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_top_level_let_type_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_init_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_is_const(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_enum_alloc(struct ast_Module * module);
extern void pipeline_module_enum_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_enum_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_allow_padding_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern void pipeline_module_struct_layout_set_packed(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_packed_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_soa_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_offset(struct ast_Module * module, int32_t li, int32_t j, int32_t foff);
extern int32_t pipeline_onefunc_append_const_name(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val);
extern int32_t pipeline_onefunc_const_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_const_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_const_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_consts(uint8_t * out);
extern int32_t pipeline_onefunc_append_let(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t pipeline_onefunc_let_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_let_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_let_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_type_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_lets(uint8_t * out);
extern void pipeline_onefunc_const_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_let_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_copy_sidecar(uint8_t * dst, uint8_t * src);
extern void ast_pool_onefunc_reset(uint8_t * out);
extern int32_t pipeline_block_append_const(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_let(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_if(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_block_append_region(struct ast_ASTArena * arena, int32_t br, uint8_t * label, int32_t label_len, int32_t body_ref);
extern int32_t pipeline_block_append_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t body_ref);
extern int32_t pipeline_block_region_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern int32_t pipeline_block_append_expr_stmt(struct ast_ASTArena * arena, int32_t br, int32_t expr_ref);
extern int32_t pipeline_block_append_stmt_order(struct ast_ASTArena * arena, int32_t br, uint8_t kind, int32_t idx);
extern int32_t pipeline_block_const_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_name_len(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern void pipeline_block_const_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t ci, uint8_t * dst);
extern int32_t pipeline_block_let_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_name_len(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern void pipeline_block_let_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t li, uint8_t * dst);
extern int32_t pipeline_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t br, int32_t ei);
extern uint8_t pipeline_block_stmt_order_kind(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_stmt_order_idx(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_if_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_then_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_else_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void pipeline_block_fill_ifs_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_stmt_order_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_expr_stmts_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_while(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_block_append_for(struct ast_ASTArena * arena, int32_t br, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_block_while_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_while_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_for_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_step_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern void pipeline_block_fill_whiles_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_fors_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_labeled(struct ast_ASTArena * arena, int32_t br, int32_t label_len, int32_t is_goto, int32_t goto_target_len, int32_t return_expr_ref);
extern int32_t pipeline_block_labeled_return_expr_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_onefunc_append_while(uint8_t * out, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_while_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_while_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_whiles(uint8_t * out);
extern int32_t pipeline_onefunc_append_for(uint8_t * out, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_for_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_step_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_fors(uint8_t * out);
extern void pipeline_dep_ctx_set_module(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_Module * m);
extern void pipeline_dep_ctx_set_arena(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_ASTArena * a);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern uint8_t pipeline_dep_ctx_import_path_byte_at(struct ast_PipelineDepCtx * ctx, int32_t idx, int32_t off);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_set_ndep(struct ast_PipelineDepCtx * ctx, int32_t n);
extern int32_t pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx * ctx, uint8_t * path, int32_t len);
extern int32_t pipeline_ctx_lib_root_count(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_ctx_lib_root_len(struct ast_PipelineDepCtx * ctx, int32_t i);
extern void pipeline_ctx_lib_root_copy(struct ast_PipelineDepCtx * ctx, int32_t i, uint8_t * dst, int32_t cap);
extern int32_t pipeline_module_func_alloc_slot(struct ast_Module * module);
extern int32_t pipeline_module_func_ref_at(struct ast_Module * module, int32_t func_index);
extern void pipeline_module_func_ref_set(struct ast_Module * module, int32_t func_index, int32_t func_ref);
extern void pipeline_module_func_set_return_type(struct ast_Module * module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(struct ast_Module * module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(struct ast_Module * module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(struct ast_Module * module, int32_t fi, int32_t is_extern);
extern void pipeline_module_func_set_num_params(struct ast_Module * module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_num_generic_params(struct ast_Module * module, int32_t fi, int32_t n);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_num_generic_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern struct ast_Type ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern int32_t pipeline_expr_append_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_type_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_append_method_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_append_match_arm(struct ast_ASTArena * arena, int32_t expr_ref, int32_t result_ref, int32_t is_wildcard, int32_t lit_val, int32_t is_enum_variant, int32_t variant_index);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern void pipeline_expr_match_arm_set_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t is_var, int32_t variant_index);
extern int32_t pipeline_expr_append_struct_lit_field(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * name_bytes, int32_t name_len, int32_t init_ref);
extern int32_t pipeline_expr_append_array_lit_elem(struct ast_ASTArena * arena, int32_t expr_ref, int32_t elem_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_init_call_resolve_at_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern struct ast_Expr ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
extern int implicit_tail_expr_disallowed_by_glue(struct ast_ASTArena * a, int32_t expr_ref);
extern void ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern struct ast_Func ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
extern struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
int ast_ref_is_null(int32_t ref);
int32_t ast_placeholder();
void ast_expr_layout_prime_call_resolved();
void ast_func_layout_prime_generic_params();
void ast_arena_init(struct ast_ASTArena * arena);
int32_t ast_arena_type_alloc(struct ast_ASTArena * arena);
int32_t ast_arena_expr_alloc(struct ast_ASTArena * arena);
int32_t ast_arena_block_alloc(struct ast_ASTArena * arena);
void ast_expr_init_match_enum(struct ast_Expr * e);
void ast_expr_init_call_resolve(struct ast_ASTArena * arena, int32_t expr_ref);
void ast_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
int ast_name_bytes_equal(uint8_t * a_nm, int32_t a_len, uint8_t * b_nm, int32_t b_len);
int32_t ast_block_final_expr_ref(struct ast_ASTArena * a, int32_t body_ref);
int ast_expr_disallows_implicit_tail(struct ast_ASTArena * a, int32_t expr_ref);
int32_t ast_block_num_consts(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_lets(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_loops(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_for_loops(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_if_stmts(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_regions(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_region_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ri);
int32_t ast_block_num_expr_stmts(struct ast_ASTArena * a, int32_t br);
int32_t ast_block_num_stmt_order(struct ast_ASTArena * a, int32_t br);
uint8_t ast_block_stmt_order_kind(struct ast_ASTArena * a, int32_t br, int32_t si);
int32_t ast_block_stmt_order_idx(struct ast_ASTArena * a, int32_t br, int32_t si);
int32_t ast_block_const_init_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
int32_t ast_block_const_type_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
int32_t ast_block_let_init_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
int32_t ast_block_let_type_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
int32_t ast_block_expr_stmt_ref(struct ast_ASTArena * a, int32_t br, int32_t ei);
int32_t ast_block_while_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
int32_t ast_block_while_body_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
int32_t ast_block_for_init_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
int32_t ast_block_for_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
int32_t ast_block_for_step_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
int32_t ast_block_for_body_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
int32_t ast_block_if_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
int32_t ast_block_if_then_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
int32_t ast_block_if_else_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
int32_t ast_block_resolve_var_to_type_ref(struct ast_ASTArena * a, int32_t block_ref, uint8_t * vname, int32_t vlen);
void ast_arena_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
int32_t ast_arena_func_alloc(struct ast_ASTArena * arena);
__attribute__((weak)) int ast_ref_is_null(int32_t ref) {
  return ref == 0;
}
int32_t ast_placeholder() {
  return 0;
}
__attribute__((weak)) void ast_expr_layout_prime_call_resolved() {
  struct ast_Expr _tail = (struct ast_Expr){ .kind = ast_ExprKind_EXPR_LIT, .resolved_type_ref = 0, .line = 0, .col = 0, .as_operand_ref = 0, .as_target_type_ref = 0, .call_resolved_func_index = (-1), .call_resolved_dep_index = (-1) };
  ((_tail).call_num_type_args = (0));
  ((_tail).call_resolved_func_index = ((-1)));
}
void ast_func_layout_prime_generic_params() {
  uint8_t name0[64] = { 0 };
  struct ast_Func f0 = ({ struct ast_Func _t = { 0 }; _t.name_len = 0; _t.param_base = 0; _t.num_params = 0; _t.num_generic_params = 0; _t.return_type_ref = 0; _t.body_ref = 0; _t.body_expr_ref = 0; _t.is_extern = 0; _t.is_async = 0; memcpy(_t.name, name0, sizeof(_t.name)); _t; });
  ((f0).num_generic_params = (0));
}
void ast_arena_init(struct ast_ASTArena * arena) {
  (void)(ast_expr_layout_prime_call_resolved());
  (void)(ast_func_layout_prime_generic_params());
  ((arena)->num_types = (0));
  ((arena)->num_exprs = (0));
  ((arena)->num_blocks = (0));
  ((arena)->num_funcs = (0));
}
int32_t ast_arena_type_alloc(struct ast_ASTArena * arena) {
  int32_t ref = 0;
  {
    (ref = (pipeline_arena_type_alloc(arena)));
  }
  (void)(({ int32_t __tmp = 0; if (ref <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return ref;
}
int32_t ast_arena_expr_alloc(struct ast_ASTArena * arena) {
  int32_t ref = 0;
  {
    (ref = (pipeline_arena_expr_alloc(arena)));
  }
  (void)(({ int32_t __tmp = 0; if (ref <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return ref;
}
int32_t ast_arena_block_alloc(struct ast_ASTArena * arena) {
  int32_t ref = 0;
  {
    (ref = (pipeline_arena_block_alloc(arena)));
  }
  (void)(({ int32_t __tmp = 0; if (ref <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return ref;
}
__attribute__((weak)) void ast_expr_init_match_enum(struct ast_Expr * e) {
  ((e)->match_arm_base = (0));
  ((e)->enum_variant_tag = (0));
}
__attribute__((weak)) void ast_expr_init_call_resolve(struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    (void)(pipeline_expr_init_call_resolve_at_ref(arena, expr_ref));
  }
}
void ast_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix) {
  {
    (void)(pipeline_expr_apply_call_resolve(arena, call_expr_ref, dep_ix, func_ix));
  }
}
int ast_name_bytes_equal(uint8_t * a_nm, int32_t a_len, uint8_t * b_nm, int32_t b_len) {
  (void)(({ int __tmp = 0; if (a_len != b_len || a_len <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  int32_t j = 0;
  while (j < a_len) {
    (void)(({ int __tmp = 0; if ((a_nm)[j] != (b_nm)[j]) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    ++j;
  }
  return 1;
}
int32_t ast_block_final_expr_ref(struct ast_ASTArena * a, int32_t body_ref) {
  (void)(({ int32_t __tmp = 0; if (body_ref <= 0 || body_ref > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk = {0};
  {
    (blk = (ast_arena_block_get(a, body_ref)));
  }
  return (blk).final_expr_ref;
}
int ast_expr_disallows_implicit_tail(struct ast_ASTArena * a, int32_t expr_ref) {
  {
    return implicit_tail_expr_disallowed_by_glue(a, expr_ref);
  }
}
int32_t ast_block_num_consts(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nc = {0};
  {
    (blk_nc = (ast_arena_block_get(a, br)));
  }
  return (blk_nc).num_consts;
}
int32_t ast_block_num_lets(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nl = {0};
  {
    (blk_nl = (ast_arena_block_get(a, br)));
  }
  return (blk_nl).num_lets;
}
int32_t ast_block_num_loops(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nlp = {0};
  {
    (blk_nlp = (ast_arena_block_get(a, br)));
  }
  return (blk_nlp).num_loops;
}
int32_t ast_block_num_for_loops(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nfp = {0};
  {
    (blk_nfp = (ast_arena_block_get(a, br)));
  }
  return (blk_nfp).num_for_loops;
}
int32_t ast_block_num_if_stmts(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nif = {0};
  {
    (blk_nif = (ast_arena_block_get(a, br)));
  }
  return (blk_nif).num_if_stmts;
}
int32_t ast_block_num_regions(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nr = {0};
  {
    (blk_nr = (ast_arena_block_get(a, br)));
  }
  return (blk_nr).num_regions;
}
int32_t ast_block_region_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ri) {
  {
    return pipeline_block_region_body_ref(a, br, ri);
  }
}
int32_t ast_block_num_expr_stmts(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nes = {0};
  {
    (blk_nes = (ast_arena_block_get(a, br)));
  }
  return (blk_nes).num_expr_stmts;
}
int32_t ast_block_num_stmt_order(struct ast_ASTArena * a, int32_t br) {
  (void)(({ int32_t __tmp = 0; if (br <= 0 || br > (a)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Block blk_nso = {0};
  {
    (blk_nso = (ast_arena_block_get(a, br)));
  }
  return (blk_nso).num_stmt_order;
}
uint8_t ast_block_stmt_order_kind(struct ast_ASTArena * a, int32_t br, int32_t si) {
  {
    return pipeline_block_stmt_order_kind(a, br, si);
  }
}
int32_t ast_block_stmt_order_idx(struct ast_ASTArena * a, int32_t br, int32_t si) {
  {
    return pipeline_block_stmt_order_idx(a, br, si);
  }
}
int32_t ast_block_const_init_ref(struct ast_ASTArena * a, int32_t br, int32_t ci) {
  {
    return pipeline_block_const_init_ref(a, br, ci);
  }
}
int32_t ast_block_const_type_ref(struct ast_ASTArena * a, int32_t br, int32_t ci) {
  {
    return pipeline_block_const_type_ref(a, br, ci);
  }
}
int32_t ast_block_let_init_ref(struct ast_ASTArena * a, int32_t br, int32_t li) {
  {
    return pipeline_block_let_init_ref(a, br, li);
  }
}
int32_t ast_block_let_type_ref(struct ast_ASTArena * a, int32_t br, int32_t li) {
  {
    return pipeline_block_let_type_ref(a, br, li);
  }
}
int32_t ast_block_expr_stmt_ref(struct ast_ASTArena * a, int32_t br, int32_t ei) {
  {
    return pipeline_block_expr_stmt_ref(a, br, ei);
  }
}
int32_t ast_block_while_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t wi) {
  {
    return pipeline_block_while_cond_ref(a, br, wi);
  }
}
int32_t ast_block_while_body_ref(struct ast_ASTArena * a, int32_t br, int32_t wi) {
  {
    return pipeline_block_while_body_ref(a, br, wi);
  }
}
int32_t ast_block_for_init_ref(struct ast_ASTArena * a, int32_t br, int32_t fi) {
  {
    return pipeline_block_for_init_ref(a, br, fi);
  }
}
int32_t ast_block_for_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t fi) {
  {
    return pipeline_block_for_cond_ref(a, br, fi);
  }
}
int32_t ast_block_for_step_ref(struct ast_ASTArena * a, int32_t br, int32_t fi) {
  {
    return pipeline_block_for_step_ref(a, br, fi);
  }
}
int32_t ast_block_for_body_ref(struct ast_ASTArena * a, int32_t br, int32_t fi) {
  {
    return pipeline_block_for_body_ref(a, br, fi);
  }
}
int32_t ast_block_if_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t ii) {
  {
    return pipeline_block_if_cond_ref(a, br, ii);
  }
}
int32_t ast_block_if_then_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii) {
  {
    return pipeline_block_if_then_body_ref(a, br, ii);
  }
}
int32_t ast_block_if_else_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii) {
  {
    return pipeline_block_if_else_body_ref(a, br, ii);
  }
}
int32_t ast_block_resolve_var_to_type_ref(struct ast_ASTArena * a, int32_t block_ref, uint8_t * vname, int32_t vlen) {
  {
    return pipeline_block_resolve_var_type_ref(a, block_ref, vname, vlen);
  }
}
void ast_arena_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref) {
  int32_t stack_blk[256] = { 0 };
  int32_t stack_par[256] = { 0 };
  int32_t sp = 0;
  int32_t cur = 0;
  int32_t par = 0;
  int32_t wb = 0;
  int32_t fb = 0;
  int32_t tb = 0;
  int32_t eb = 0;
  int32_t rgb = 0;
  int32_t i = 0;
  (void)(({ int32_t __tmp = 0; if (block_ref <= 0 || block_ref > (arena)->num_blocks) {   return;
 } else (__tmp = 0) ; __tmp; }));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = block_ref, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = parent_ref, 0)));
  ++sp;
  while (sp > 0) {
    (sp = (sp - 1));
    (cur = ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), (stack_blk)[0]) : (stack_blk)[sp])));
    (par = ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), (stack_par)[0]) : (stack_par)[sp])));
    (void)(({ int32_t __tmp = 0; if (cur <= 0 || cur > (arena)->num_blocks) {   continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (par != 0) {   struct ast_Block b_head = {0};
  {
    (b_head = (ast_arena_block_get(arena, cur)));
  }
  __tmp = ({ int32_t __tmp = 0; if ((b_head).parent_block_ref == 0) {   ((b_head).parent_block_ref = (par));
  {
    (void)(ast_arena_block_set(arena, cur, b_head));
  }
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Block b = {0};
    {
      (b = (ast_arena_block_get(arena, cur)));
    }
    (i = (0));
    while (i < (b).num_loops) {
      (wb = (ast_block_while_body_ref(arena, cur, i)));
      (void)(({ int32_t __tmp = 0; if (wb > 0 && sp < 256) {   ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = wb, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = cur, 0)));
  ++sp;
 } else (__tmp = 0) ; __tmp; }));
      ++i;
    }
    (i = (0));
    while (i < (b).num_for_loops) {
      (fb = (ast_block_for_body_ref(arena, cur, i)));
      (void)(({ int32_t __tmp = 0; if (fb > 0 && sp < 256) {   ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = fb, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = cur, 0)));
  ++sp;
 } else (__tmp = 0) ; __tmp; }));
      ++i;
    }
    (i = (0));
    while (i < (b).num_if_stmts) {
      (tb = (ast_block_if_then_body_ref(arena, cur, i)));
      (void)(({ int32_t __tmp = 0; if (tb > 0 && sp < 256) {   ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = tb, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = cur, 0)));
  ++sp;
 } else (__tmp = 0) ; __tmp; }));
      (eb = (ast_block_if_else_body_ref(arena, cur, i)));
      (void)(({ int32_t __tmp = 0; if (eb > 0 && sp < 256) {   ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = eb, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = cur, 0)));
  ++sp;
 } else (__tmp = 0) ; __tmp; }));
      ++i;
    }
    (i = (0));
    while (i < (b).num_regions) {
      (rgb = (ast_block_region_body_ref(arena, cur, i)));
      (void)(({ int32_t __tmp = 0; if (rgb > 0 && sp < 256) {   ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_blk)[sp] = rgb, 0)));
  ((sp < 0 || (sp) >= 256 ? (xlang_panic_(1, 0), 0) : ((stack_par)[sp] = cur, 0)));
  ++sp;
 } else (__tmp = 0) ; __tmp; }));
      ++i;
    }
  }
}
int32_t ast_arena_func_alloc(struct ast_ASTArena * arena) {
  int32_t ref = 0;
  {
    (ref = (pipeline_arena_func_alloc(arena)));
  }
  (void)(({ int32_t __tmp = 0; if (ref <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return ref;
}


/* wave330 archaeological cold-seed pin (Stage 8 Track L retirement egg) — G.7 SINGLE COPY SEMANTICS: mirror of compiler/ast_gen2.c committed snapshot. * Do NOT edit manually: next regen pin → cp ast_gen2.c → seeds/ast_gen2.linux.x86_64.c same commit. * Track L: driver_leaf_x_to_o.sh PREFER_X_O times out (src/ast/ast.x large -E) → * fallback this archaeology cold seed direct cc (bypasses assemble chain). * PLATFORM: SHARED (committed C copy; freestanding single-TU; builds on Darwin arm64 + Ubuntu x86_64 gold). */
