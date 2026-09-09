#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
void xlang_panic_(int has_msg, int msg_val);
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE, ast_ExprKind_EXPR_STRING_LIT };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type {
  int32_t kind;
  uint8_t name[128];
  int32_t name_len;
  int32_t elem_type_ref;
  int32_t array_size;
  uint8_t region_label[128];
  int32_t region_label_len;
};

struct ast_Expr {
  int32_t kind;
  int32_t resolved_type_ref;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t var_name[128];
  int32_t var_name_len;
  int32_t binop_left_ref;
  int32_t binop_right_ref;
  int32_t unary_operand_ref;
  int32_t if_cond_ref;
  int32_t if_then_ref;
  int32_t if_else_ref;
  int32_t block_ref;
  int32_t match_matched_ref;
  int32_t match_arm_base;
  int32_t match_num_arms;
  int32_t field_access_base_ref;
  uint8_t field_access_field_name[128];
  int32_t field_access_field_len;
  int32_t field_access_is_enum_variant;
  int32_t field_access_offset;
  int32_t field_access_soa_stride;
  int32_t index_base_ref;
  int32_t index_index_ref;
  int32_t index_base_is_slice;
  int32_t call_callee_ref;
  int32_t call_arg_base;
  int32_t call_num_args;
  int32_t call_num_type_args;
  int32_t method_call_base_ref;
  uint8_t method_call_name[128];
  int32_t method_call_name_len;
  int32_t method_call_arg_base;
  int32_t method_call_num_args;
  int32_t const_folded_val;
  int32_t const_folded_valid;
  int32_t index_proven_in_bounds;
  uint8_t struct_lit_struct_name[128];
  int32_t struct_lit_struct_name_len;
  int32_t struct_lit_field_base;
  int32_t struct_lit_num_fields;
  int32_t array_lit_elem_base;
  int32_t array_lit_num_elems;
  int32_t float_bits_lo;
  int32_t float_bits_hi;
  int32_t enum_variant_tag;
  int32_t as_operand_ref;
  int32_t as_target_type_ref;
  int32_t call_resolved_func_index;
  int32_t call_resolved_dep_index;
};

struct ast_ConstDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct ast_LetDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct ast_WhileLoop {
  int32_t cond_ref;
  int32_t body_ref;
};

struct ast_ForLoop {
  int32_t init_ref;
  int32_t cond_ref;
  int32_t step_ref;
  int32_t body_ref;
};

struct ast_IfStmt {
  int32_t cond_ref;
  int32_t then_body_ref;
  int32_t else_body_ref;
};

struct ast_StmtOrderItem {
  uint8_t kind;
  int32_t idx;
};

struct ast_LabeledStmt {
  uint8_t label[128];
  int32_t label_len;
  int32_t is_goto;
  uint8_t goto_target[128];
  int32_t goto_target_len;
  int32_t return_expr_ref;
};

struct ast_Block {
  int32_t const_base;
  int32_t num_consts;
  int32_t let_base;
  int32_t num_lets;
  int32_t num_early_lets;
  int32_t loop_base;
  int32_t num_loops;
  int32_t for_loop_base;
  int32_t num_for_loops;
  int32_t if_base;
  int32_t num_if_stmts;
  int32_t region_base;
  int32_t num_regions;
  int32_t defer_base;
  int32_t num_defers;
  int32_t labeled_base;
  int32_t num_labeled_stmts;
  int32_t expr_stmt_base;
  int32_t num_expr_stmts;
  int32_t final_expr_ref;
  int32_t stmt_order_base;
  int32_t num_stmt_order;
  int32_t parent_block_ref;
};

struct ast_Param {
  uint8_t name[32];
  int32_t name_len;
  int32_t type_ref;
};

struct ast_Func {
  uint8_t name[128];
  int32_t name_len;
  int32_t param_base;
  int32_t num_params;
  int32_t num_generic_params;
  int32_t return_type_ref;
  int32_t body_ref;
  int32_t body_expr_ref;
  int32_t is_extern;
  int32_t is_async;
  int32_t is_used;
  int32_t is_naked;
  int32_t is_entry;
  int32_t is_no_mangle;
  int32_t is_interrupt;
  int32_t abi_kind;
  int32_t is_variadic;
  int32_t is_export;
};

struct ast_StructLayout {
  uint8_t name[128];
  int32_t name_len;
  int32_t field_base;
  int32_t num_fields;
  int32_t allow_padding;
  int32_t soa;
  int32_t packed;
  int32_t repr_compatible;
  int32_t is_export;
};

struct ast_Module {
  int32_t num_funcs;
  int32_t main_func_index;
  int32_t num_imports;
  int32_t num_top_level_lets;
  int32_t num_struct_layouts;
  int32_t pending_allow_padding;
  int32_t pending_soa_struct;
  int32_t pending_cfg_skip;
  int32_t pending_repr_c_struct;
  int32_t pending_repr_compatible_struct;
  int32_t pending_used;
  int32_t pending_naked;
  int32_t pending_entry;
  int32_t pending_no_mangle;
  int32_t pending_interrupt;
  int32_t pending_export;
  int32_t num_module_enums;
};

struct ast_ASTArena {
  int32_t num_types;
  int32_t num_exprs;
  int32_t num_blocks;
  int32_t num_funcs;
};

struct ast_PipelineDepCtx {
  int32_t ndep;
  uint8_t entry_dir_buf[512];
  int32_t entry_dir_len;
  int32_t num_lib_roots;
  uint8_t path_buf[512];
  uint8_t loaded_buf[4194304];
  ssize_t loaded_len;
  uint8_t preprocess_buf[4194304];
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
  struct ast_Module * current_codegen_module;
  struct ast_ASTArena * current_codegen_arena;
  int32_t current_codegen_dep_index;
  uint8_t current_codegen_prefix_mirror[128];
  int32_t current_codegen_prefix_len;
  int32_t asm_entry_module_only;
  uint8_t entry_module_import_path_mirror[128];
  int32_t entry_module_import_path_len;
  int32_t typeck_scope_region_len;
  uint8_t typeck_scope_region_label[128];
};

struct ast_Type;
struct ast_Expr;
struct ast_ConstDecl;
struct ast_LetDecl;
struct ast_WhileLoop;
struct ast_ForLoop;
struct ast_IfStmt;
struct ast_StmtOrderItem;
struct ast_LabeledStmt;
struct ast_Block;
struct ast_Param;
struct ast_Func;
struct ast_StructLayout;
struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;
extern void ast_ast_pool_block_on_alloc(struct ast_ASTArena * arena, int32_t block_ref);
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
extern int32_t pipeline_arena_type_cap(void);
extern int32_t pipeline_arena_expr_cap(void);
extern int32_t pipeline_arena_block_cap(void);
extern int32_t pipeline_arena_func_cap(void);
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
extern void ast_ast_pool_onefunc_reset(uint8_t * out);
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
extern void pipeline_module_func_set_is_variadic(struct ast_Module * module, int32_t fi, int32_t is_variadic);
extern int32_t pipeline_module_func_is_variadic_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_set_num_params(struct ast_Module * module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_num_generic_params(struct ast_Module * module, int32_t fi, int32_t n);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_num_generic_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern int ast_ref_is_null(int32_t ref);
extern int32_t ast_ast_placeholder(void);
extern void ast_expr_layout_prime_call_resolved(void);
extern void ast_func_layout_prime_generic_params(void);
extern void ast_ast_arena_init(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern void ast_expr_init_match_enum(struct ast_Expr * e);
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
extern void ast_expr_init_call_resolve(struct ast_ASTArena * arena, int32_t expr_ref);
extern void ast_ast_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
extern int ast_ast_name_bytes_equal(uint8_t * a_nm, int32_t a_len, uint8_t * b_nm, int32_t b_len);
extern int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena * a, int32_t body_ref);
extern int implicit_tail_expr_disallowed_by_glue(struct ast_ASTArena * a, int32_t expr_ref);
extern int ast_ast_expr_disallows_implicit_tail(struct ast_ASTArena * a, int32_t expr_ref);
extern int32_t ast_ast_block_num_consts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_lets(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_for_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_regions(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_region_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ri);
extern int32_t ast_ast_block_num_expr_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena * a, int32_t br);
extern uint8_t ast_ast_block_stmt_order_kind(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_stmt_order_idx(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_const_init_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_const_type_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_let_init_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_let_type_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_expr_stmt_ref(struct ast_ASTArena * a, int32_t br, int32_t ei);
extern int32_t ast_ast_block_while_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_while_body_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_for_init_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_step_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_body_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_if_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_then_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_else_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_resolve_var_to_type_ref(struct ast_ASTArena * a, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void ast_ast_arena_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern int32_t ast_ast_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern int32_t type_kind_ordinal(enum ast_TypeKind k);
extern int name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len);
extern int32_t typeck_resolve_type_alias_ref_local(struct ast_Module * module, struct ast_ASTArena * arena, int32_t type_ref, int32_t depth);
extern int typeck_named_type_matches_name_or_alias(struct ast_Module * module, struct ast_ASTArena * arena, int32_t decl_ty_ref, uint8_t * lit_name, int32_t lit_name_len, int32_t depth);
extern int typeck_layout_name_equal(struct ast_Module * module, int32_t k, uint8_t * nm, int32_t nlen);
extern int typeck_layout_field_name_equal(struct ast_Module * module, int32_t k, int32_t j, uint8_t * nm, int32_t nlen);
extern int32_t typeck_layout_name_into(struct ast_Module * module, int32_t k, uint8_t * buf);
extern int32_t typeck_layout_field_name_into(struct ast_Module * module, int32_t k, int32_t j, uint8_t * buf);
extern int typeck_import_path_slice_equal(struct ast_Module * module, int32_t imp_ix, int32_t off, int32_t seg_len, uint8_t * nm, int32_t nm_len);
extern int typeck_import_binding_name_equal(struct ast_Module * module, int32_t imp_ix, uint8_t * nm, int32_t nm_len);
extern int32_t typeck_module_num_imports(struct ast_Module * module);
extern int typeck_var_is_import_visible_name(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int typeck_import_select_name_equal(struct ast_Module * module, int32_t imp_ix, int32_t sel, uint8_t * nm, int32_t nm_len);
extern int typeck_top_level_let_name_equal(struct ast_Module * module, int32_t tl_ix, uint8_t * nm, int32_t nm_len);
extern int32_t typeck_dep_module_const_idx_named(struct ast_Module * module, uint8_t * nm, int32_t nlen, int32_t tl_ix);
extern int32_t typeck_find_import_const_dep_index(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * nm, int32_t nlen, int32_t dep_ix);
extern int32_t typeck_import_last_segment_into(struct ast_Module * module, int32_t imp_ix, uint8_t * out);
extern int32_t typeck_resolve_dep_index_for_import(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix);
extern int32_t typeck_import_const_binding_hint_at(struct ast_Module * module, int32_t dep_ix, uint8_t * out);
extern int32_t typeck_find_layout_idx_by_type_name(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_named_builtin_align(uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_named_builtin_size(uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_type_align(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_x_type_size(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_struct_layout_metrics(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth, int32_t check_pad, int32_t * out_sz, int32_t * out_al);
extern int32_t typeck_validate_struct_layouts_zero_padding(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t get_field_type_ref_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t get_field_offset_from_layout_deps(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref);
extern int expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index);
extern int32_t find_or_alloc_named_type_ref(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t typeck_field_access_lexer_wrapper_fallback(struct ast_ASTArena * arena, int32_t base_type_ref, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_ensure_primitive_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord);
extern int32_t ensure_i32_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_u8_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_bool_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_f32_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_f64_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_usize_type_ref(struct ast_ASTArena * arena);
extern int32_t ensure_void_type_ref(struct ast_ASTArena * a);
extern int32_t get_dep_return_type_in_caller_arena(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
extern int32_t ensure_i64_type_ref(struct ast_ASTArena * caller_arena);
extern int32_t typeck_find_or_alloc_compound_type_ref(struct ast_ASTArena * a, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t find_or_alloc_array_type_ref(struct ast_ASTArena * a, int32_t elem_ref, int32_t array_size);
extern int32_t ensure_array_type_ref_named_elem(struct ast_ASTArena * a, uint8_t * elem_nm, int32_t elem_nm_len, int32_t array_size);
extern int32_t ensure_kind_only_type_ref(struct ast_ASTArena * w, enum ast_TypeKind kind);
extern int32_t find_or_alloc_ptr_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t find_or_alloc_slice_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t find_or_alloc_linear_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t find_or_alloc_vector_type_ref(struct ast_ASTArena * w, int32_t elem_ref, int32_t array_size);
extern int32_t dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena);
extern int32_t expr_field_access_fallback_scalar_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t get_field_type_ref_from_layout_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_inline_u8_64_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_expr_inline_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t entry_module_find_struct_layout_index(struct ast_Module * mod, uint8_t * nm, int32_t nlen);
extern void typeck_merge_dep_struct_layouts_into_entry(struct ast_Module * mod, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern void typeck_wpo_unify_soa_layouts(struct ast_Module * entry, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_resolve_scan_dep_with_apply(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax, int32_t want_apply);
extern int32_t find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t find_func_return_type_in_module_by_name(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_overload_arg_param_score(struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t arg_i, int32_t param_ty_raw, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx);
extern int32_t find_func_return_type_in_module_by_name_overload(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t find_func_return_type_in_module_overload(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_import_path_segment_count(uint8_t * path, int32_t path_len);
extern int typeck_import_segment_at(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen);
extern int32_t resolve_whole_import_qualified_call_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t resolve_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t resolve_method_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t resolve_call_select_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t resolve_call_callee_try_whole_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord);
extern int32_t resolve_call_callee_try_binding_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord);
extern int32_t resolve_call_callee_local_module(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t resolve_call_callee_scan_dep(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax);
extern int32_t resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern int type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref);
extern int type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_named_unqual_start(uint8_t * buf, int32_t len);
extern int type_refs_equal_named(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int type_refs_equal_same_kind(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord);
extern int type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int typeck_integer_widen_ok(int32_t dest_kind, int32_t src_kind);
extern int typeck_int_family_id(struct ast_ASTArena * arena, int32_t type_ref);
extern int typeck_integer_widen_ok_refs(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref);
extern int typeck_float_widen_ok(int32_t dest_kind, int32_t src_kind);

int typeck_return_operand_matches(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern int32_t typeck_coerce_init_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_float_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_enum_field_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_named_call_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_resolved_alias_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t typeck_coerce_array_lit_elem_types_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_vector_lanes_of_type(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_coerce_init_array_vector_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_vector_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_int_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_slice_from_array(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t typeck_coerce_init_expr_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_diag_append_lit(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len);
extern int32_t typeck_diag_append_u32_dec(uint8_t * out, int32_t pos, int32_t cap, int32_t v);
extern int32_t typeck_diag_fmt_type_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap);
extern int32_t typeck_diag_fmt_type_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap);
extern int32_t typeck_diag_fmt_type_or_question(struct ast_ASTArena * arena, int32_t ref, uint8_t * out);
extern void typeck_ret_coerce_integral_to_expect_i32(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_coerce_integral_widen(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_coerce_null_lit_to_expect(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_fixup_unresolved_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_return_breadcrumb_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern void typeck_emit_return_subexpr_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col);
extern void typeck_emit_return_unresolved_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col);
extern int32_t typeck_check_expr_float_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_int_lit(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref);
extern int32_t typeck_check_expr_bool_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_string_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_break_continue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_if_ternary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_block_expr_value_ref(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t typeck_check_expr_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_panic(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_match_arm(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arm_i, int32_t num_arms, int32_t line, int32_t col);
extern int32_t typeck_check_expr_match(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args);
extern int32_t typeck_check_expr_call_resolve(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_call_arity(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_call_is_fmt_debug_print_any(struct ast_Module * mod, int32_t fi, int32_t dep, struct ast_PipelineDepCtx * ctx, int32_t num_args);
extern int32_t typeck_check_call_arg_types(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_expr_is_null_keyword(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_cmp_promote_subint_to_i32(struct ast_ASTArena * arena, int32_t expr_ref, int32_t ty_ref);
extern 
int32_t typeck_check_expr_binop_cmp(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_binop_arith(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_binop(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_field_access(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_unary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_addr_of(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_deref(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_var_top_level(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * vbuf, int32_t vnlen, int32_t tl);
extern int32_t typeck_check_expr_var(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_method_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args);
extern int32_t typeck_check_expr_method_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_as(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_struct_lit_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t field_i, int32_t num_fields);
extern int32_t typeck_coerce_struct_lit_field_inits_to_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty);
extern int32_t typeck_check_expr_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int typeck_expr_is_any_assign_kind(int32_t kind_ord);
extern int32_t check_expr_impl_mega(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t func_body_tail_expr_ref_for_implicit_rule(struct ast_ASTArena * arena, int32_t body_ref);
extern int func_body_has_implicit_return_tail(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t typeck_loop_depth_push(struct ast_PipelineDepCtx * ctx);
extern void typeck_loop_depth_pop(struct ast_PipelineDepCtx * ctx, int32_t saved);
extern int32_t check_block_as_loop_body(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_block_one_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_let(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_while(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_for(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_if(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_final(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t fin0);
extern int32_t typeck_check_block_one_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_stmt_order_one(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t si, int32_t nso, int32_t nc, int32_t nl, int32_t nes, int32_t nlp, int32_t nfp, int32_t nif, int32_t nreg);
extern int32_t typeck_check_block_legacy_consts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nc);
extern int32_t typeck_check_block_legacy_lets(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nl);
extern int32_t typeck_check_block_legacy_whiles(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nlp);
extern int32_t typeck_check_block_legacy_fors(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nfp);
extern int32_t typeck_check_block_legacy_ifs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nif);
extern int32_t typeck_check_block_legacy_expr_stmts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nes);
extern int32_t check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast_check_one_func(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_idx);
extern int32_t typeck_x_ast_check_all_funcs_loop(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_i, int32_t num_funcs);
extern void typeck_patch_all_body_parent_links(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t typeck_x_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast_library(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_float64_bits_lo(double d);
extern int32_t typeck_float64_bits_hi(double d);
extern void driver_diagnostic_typeck_func_fail(int32_t func_idx, uint8_t * name, int32_t name_len, int32_t kind);
extern void pipeline_typeck_loop_depth_set_c(struct ast_PipelineDepCtx * ctx, int32_t depth);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t parser_get_module_num_imports(struct ast_Module * module);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_current_func_index(struct ast_PipelineDepCtx * ctx, int32_t ix);
extern int32_t pipeline_typeck_check_expr_impl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_impl_mega_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_method_call_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_try_propagate_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_match_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_field_access_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_field_prebind_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_field_known_ptr_types_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, int32_t num_layouts);
extern int32_t pipeline_typeck_field_layout_named_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_field_slice_c(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref);
extern void pipeline_typeck_field_name_fallback_c(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref);
extern void pipeline_typeck_field_lexer_fallback_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern void driver_diagnostic_typeck_ptr_field(int32_t bt_kind, int32_t inner_kind, int32_t inner_nlen, int32_t base_resolved_ref, int32_t num_struct_layouts);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena * arena, int32_t type_ref, uint8_t * out);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_type_array_size_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_type_elem_ref_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_typeck_type_refs_equal_c(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t pipeline_typeck_resolve_type_alias_ref_c(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_module_num_type_aliases_at(struct ast_Module * module);
extern int32_t pipeline_module_type_alias_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_type_alias_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_type_alias_target_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_typeck_coerce_init_int_binop_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_func_body_has_implicit_return_tail_c(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t pipeline_expr_binop_left_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_binop_right_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void driver_diagnostic_typeck_block_enter(int32_t func_idx, int32_t block_ref, int32_t n_const, int32_t n_let, int32_t n_loop, int32_t n_for, int32_t n_expr, int32_t final_ref);
extern void driver_diagnostic_typeck_fn_enter(int32_t func_idx, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_ret_fail(int32_t stage, int32_t op_expr_ref, int32_t expect_ty_ref, int32_t got_ty_ref);
extern void driver_diagnostic_typeck_binop_operands(int32_t expr_ref, int32_t left_ref, int32_t right_ref, int32_t left_kind, int32_t right_kind, int32_t left_block_ref, int32_t right_block_ref, int32_t left_ty_ref, int32_t right_ty_ref, uint8_t * left_ty, int32_t left_ty_len, uint8_t * right_ty, int32_t right_ty_len);
extern void driver_diagnostic_typeck_return_mismatch(int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_return_unresolved(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_return_subexpr(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_assign_mismatch(int32_t is_compound, int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_import_const_must_be_qualified(int32_t line, int32_t col, uint8_t * name, int32_t name_len, uint8_t * binding, int32_t binding_len);
extern void driver_diagnostic_typeck_subscript_base(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_break_continue_outside(int32_t line, int32_t col, int32_t is_break);
/* wave285 Cap residual: illegal pointer arithmetic hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_invalid_ptr_binop(int32_t line, int32_t col);
/* wave286 Cap residual: illegal float bitop/mod/shift hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_invalid_float_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_aggregate_cmp(int32_t line, int32_t col);
/* wave659 Cap residual: illegal as-cast hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_invalid_as_cast(int32_t line, int32_t col);
/* wave660 Cap residual: call arity hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_call_arity_mismatch(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_arg_type_mismatch(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_unresolved(int32_t line, int32_t col);
/* wave664 Cap residual: non-integer subscript index hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_subscript_index(int32_t line, int32_t col);
/* wave665 Cap residual: non-bool &&/||/! operand hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_logical_operand_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_comparison_type_mismatch(int32_t line, int32_t col);
/* wave667 Cap residual: void arith/unary hard diag (G.7 ≡ typeck.x). */
extern void driver_diagnostic_typeck_invalid_void_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_bool_binop(int32_t line, int32_t col);
extern void typeck_driver_diagnostic_pipe_marker(int32_t id);
extern void driver_diagnostic_typeck_if_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_while_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_for_condition_not_bool(int32_t line, int32_t col);
extern uint8_t * driver_typeck_diag_scratch_expect(void);
extern uint8_t * driver_typeck_diag_scratch_found(void);
extern uint8_t * typeck_scratch64_slot(int32_t slot);
extern int32_t * typeck_layout_metrics_sz_slot(void);
extern int32_t * typeck_layout_metrics_al_slot(void);
extern int32_t * typeck_layout_metrics_sz_slot_depth(int32_t depth);
extern int32_t * typeck_layout_metrics_al_slot_depth(int32_t depth);
extern void typeck_i32_ptr_store(int32_t * p, int32_t v);
extern int32_t typeck_i32_ptr_read(int32_t * p);
extern int32_t * typeck_call_resolve_dep_idx_slot(void);
extern int32_t * typeck_call_resolve_func_idx_slot(void);
extern int32_t typeck_call_resolve_dep_idx_peek(void);
extern int32_t typeck_call_resolve_func_idx_peek(void);
extern void typeck_binop_arith_infer_type_c(struct ast_ASTArena * arena, int32_t expr_ref, int32_t bop_l, int32_t bop_r, int32_t expr_kind);
extern void pipeline_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern void typeck_layout_metrics_init_depth(int32_t depth);
extern int32_t typeck_layout_metrics_al_read_depth(int32_t depth);
extern int32_t typeck_layout_metrics_sz_read_depth(int32_t depth);
extern void typeck_layout_metrics_init_slot(void);
extern int32_t typeck_x_type_align_from_layout_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth);
extern int32_t typeck_x_type_size_from_layout_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth);
extern int32_t typeck_soa_array_storage_size_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t elem_type_ref, int32_t array_len, int32_t depth);
extern struct ast_ASTArena * pipeline_get_dep_arena_slot(int32_t ix);
extern int32_t pipeline_module_func_param_type_ref_for_name(struct ast_Module * module, int32_t func_index, uint8_t * vname, int32_t vname_len);
extern int32_t pipeline_module_num_funcs(struct ast_Module * module);
extern int32_t pipeline_module_main_func_index(struct ast_Module * module);
extern int32_t pipeline_module_func_is_extern_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_body_ref_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_len_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_name_copy64(struct ast_Module * module, int32_t fi, uint8_t * dst);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t layout_idx, int32_t j, uint8_t * fname, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_struct_layout_next_field_offset(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module * module, int32_t layout_idx, int32_t j, uint8_t * out);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t layout_idx, int32_t j);
extern void pipeline_module_struct_layout_name_into(struct ast_Module * module, int32_t idx, uint8_t * out);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t layout_idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t layout_idx, int32_t nf);
extern int32_t pipeline_expr_struct_lit_num_fields(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_struct_lit_type_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_struct_lit_type_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern int32_t pipeline_expr_struct_lit_field_name_len(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j);
extern void pipeline_expr_struct_lit_field_name_into(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j, uint8_t * out);
extern int32_t pipeline_expr_struct_lit_init_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j);
extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_resolved_type_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t type_ref);
extern void pipeline_expr_typeck_set_float_bits_from_val(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_line_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_col_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_dep_ctx_typeck_loop_depth_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_current_block_ref_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_current_func_index(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_typeck_unsafe_depth_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_block_impl_bind_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern void pipeline_typeck_block_impl_restore_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref);
extern void pipeline_typeck_block_impl_touch_ctx_block_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern int32_t pipeline_expr_int_val_at(struct ast_ASTArena * arena, int32_t expr_ref);
/* wave307 Cap residual: full i64 EXPR_LIT for u64/usize coerce. */
extern int64_t pipeline_expr_int64_val_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_field_access_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t tag);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_matched_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_module_enum_variant_tag_for_names(struct ast_Module * m, uint8_t * enum_name, int32_t enum_len, uint8_t * variant_name, int32_t variant_len);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern void driver_diagnostic_typeck_enum_no_variant(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_var_resolution(int32_t expr_ref, uint8_t * name, int32_t name_len, int32_t func_idx, int32_t block_ref, int32_t source, int32_t type_ref);
extern int32_t pipeline_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_type_init_primitive_kind_at(struct ast_ASTArena * arena, int32_t ref, int32_t kind_ord);
extern int32_t pipeline_type_init_named_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_type_init_compound_kind_at(struct ast_ASTArena * arena, int32_t ref, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t pipeline_type_ensure_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord);
extern int32_t pipeline_type_find_or_alloc_named(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t pipeline_type_find_or_alloc_compound(struct ast_ASTArena * arena, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t pipeline_type_region_label_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out64);
extern int32_t pipeline_type_region_label_len_at(struct ast_ASTArena * arena, int32_t ref);
extern int32_t pipeline_type_set_region_label_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * label, int32_t label_len);
extern int32_t pipeline_type_find_or_alloc_slice(struct ast_ASTArena * arena, int32_t elem_ref, uint8_t * reg_label, int32_t reg_label_len);
extern int32_t pipeline_typeck_check_slice_region_assign_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref);
extern int32_t pipeline_typeck_check_return_slice_region_c(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref);
extern int32_t pipeline_typeck_check_return_slice_region_in_scope_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_extern_call_unsafe_boundary_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern void driver_diagnostic_typeck_deref_outside_unsafe(int32_t line, int32_t col);
extern int32_t pipeline_typeck_check_call_slice_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_type_stamp_block_let_region_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_block_one_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_block_region_is_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern void pipeline_typeck_linear_reset_c(void);
extern int32_t pipeline_typeck_linear_use_var_c(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_linear_accepts_init_c(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref);
extern int32_t pipeline_typeck_reject_addr_of_linear_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_ptr_for_addr_of_operand_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_struct_stack_escape_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_scope_borrow_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_allocator_region_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_is_read_ptr_slice_callee_c(uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_read_ptr_slice_return_ref_c(struct ast_ASTArena * arena);
extern int32_t pipeline_module_func_param_type_ref_at(struct ast_Module * module, int32_t fi, int32_t pi);
extern int32_t pipeline_module_func_num_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_expr_call_resolved_func_index_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_resolved_dep_index_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_block_const_init_is_const_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx);
extern void pipeline_typeck_const_init_not_constant_c(int32_t line, int32_t col);
extern int32_t pipeline_expr_if_cond_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_if_then_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_if_else_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_block_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_asm_block_final_expr_ref_at(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t block_ref, int32_t ei);
extern int32_t pipeline_block_set_parent_if_zero(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern int32_t pipeline_expr_unary_operand_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_callee_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_index_base_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_index_index_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_index_base_is_slice(struct ast_ASTArena * arena, int32_t expr_ref, int32_t v);
extern void pipeline_expr_set_index_proven_in_bounds(struct ast_ASTArena * arena, int32_t expr_ref, int32_t v);
extern int32_t pipeline_expr_as_operand_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_as_target_type_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_field_access_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern int32_t pipeline_expr_field_access_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_base_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_field_access_offset(struct ast_ASTArena * arena, int32_t expr_ref, int32_t offset);
extern void pipeline_expr_var_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern int32_t pipeline_expr_method_call_base_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_method_call_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out64);
extern void asm_qual_sym_layer_reset(void);
extern int32_t asm_qual_sym_layer_push(uint8_t * bytes, int32_t len);
extern int32_t asm_qual_sym_layer_count(void);
extern int32_t asm_qual_sym_layer_len(int32_t i);
extern void asm_qual_sym_layer_copy(int32_t i, uint8_t * dst, int32_t cap);
extern void driver_diagnostic_typeck_struct_padding_before(uint8_t * sname, int32_t sname_len, int32_t gap, uint8_t * fname, int32_t fname_len);
extern void driver_diagnostic_typeck_struct_padding_trailing(uint8_t * sname, int32_t sname_len, int32_t gap);
extern void driver_diagnostic_typeck_struct_field_bad_size(uint8_t * sname, int32_t sname_len, uint8_t * fname, int32_t fname_len);
extern int32_t pipeline_module_num_struct_layouts_at(struct ast_Module * module);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t layout_idx, int32_t j);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_align_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_align(struct ast_Module * module, int32_t li, int32_t j, int32_t al);
extern int32_t pipeline_struct_layout_next_field_offset_ex(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref, int32_t field_align_req);
extern void pipeline_typeck_pad_fields_warn_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li);
extern void pipeline_typeck_hot_reorder_warn_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_struct_layout_allow_padding_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_packed_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_soa_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_import_path_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_import_kind_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_import_select_count_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_import_select_name_len(struct ast_Module * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(struct ast_Module * module, int32_t idx, int32_t sel, int32_t off);
extern int32_t pipeline_module_top_level_let_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_top_level_let_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_top_level_let_type_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_is_const(struct ast_Module * module, int32_t idx);
int32_t type_kind_ordinal(enum ast_TypeKind k) {
  int32_t o = ((int32_t)(k));
  int32_t lo = ((int32_t)(0));
  int32_t hi = ((int32_t)(16));
  if ((o < lo)) {
    return -(1);
  }
  if ((o > hi)) {
    return -(1);
  }
  return o;
}
int name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len) {
  if (((a_len !=b_len) || (a_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < a_len)) {
    if (((a)[i] !=(b)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t typeck_resolve_type_alias_ref_local(struct ast_Module * module, struct ast_ASTArena * arena, int32_t type_ref, int32_t depth) {
  uint8_t type_name[128] = {};
  int32_t alias_count = 0;
  int32_t alias_i = 0;
  int32_t type_name_len = 0;
  int32_t alias_name_len = 0;
  int32_t alias_off = 0;
  int32_t ord_named = 8;
  int32_t alias_target_ref = 0;
  int32_t max_depth = 32;
  if (((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || ast_ref_is_null(type_ref)) || (depth > max_depth))) {
    return type_ref;
  }
  if ((pipeline_type_kind_ord_at(arena, type_ref) !=ord_named)) {
    return type_ref;
  }
  (void)((type_name_len = pipeline_type_named_name_into(arena, type_ref, &((type_name)[0]))));
  if ((type_name_len <=0)) {
    return type_ref;
  }
  (void)((alias_count = pipeline_module_num_type_aliases_at(module)));
  while ((alias_i < alias_count)) {
    (void)((alias_name_len = pipeline_module_type_alias_name_len(module, alias_i)));
    if ((((alias_name_len ==type_name_len) && (alias_name_len > 0)) && (alias_name_len <=63))) {
      (void)((alias_off = 0));
      while ((alias_off < alias_name_len)) {
        if ((pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off) !=(type_name)[alias_off])) {
          break;
        }
        (void)((alias_off = (alias_off + 1)));
      }
      if ((alias_off ==alias_name_len)) {
        (void)((alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i)));
        if (ast_ref_is_null(alias_target_ref)) {
          return type_ref;
        }
        return typeck_resolve_type_alias_ref_local(module, arena, alias_target_ref, (depth + 1));
      }
    }
    (void)((alias_i = (alias_i + 1)));
  }
  return type_ref;
}
int typeck_named_type_matches_name_or_alias(struct ast_Module * module, struct ast_ASTArena * arena, int32_t decl_ty_ref, uint8_t * lit_name, int32_t lit_name_len, int32_t depth) {
  uint8_t decl_name[128] = {};
  uint8_t alias_name[128] = {};
  int32_t resolved_decl = 0;
  int32_t decl_name_len = 0;
  int32_t alias_count = 0;
  int32_t alias_i = 0;
  int32_t alias_name_len = 0;
  int32_t alias_off = 0;
  int32_t alias_target_ref = 0;
  int32_t ord_named = 8;
  int32_t max_depth = 32;
  if (((((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || ast_ref_is_null(decl_ty_ref)) || (lit_name ==((uint8_t *)(0)))) || (lit_name_len <=0)) || (depth > max_depth))) {
    return 0;
  }
  (void)((resolved_decl = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0)));
  if ((!(ast_ref_is_null(resolved_decl)) && (pipeline_type_kind_ord_at(arena, resolved_decl) ==ord_named))) {
    (void)((decl_name_len = pipeline_type_named_name_into(arena, resolved_decl, &((decl_name)[0]))));
    if (name_equal(&((decl_name)[0]), decl_name_len, lit_name, lit_name_len)) {
      return 1;
    }
  }
  if ((pipeline_type_kind_ord_at(arena, decl_ty_ref) !=ord_named)) {
    return 0;
  }
  (void)((decl_name_len = pipeline_type_named_name_into(arena, decl_ty_ref, &((decl_name)[0]))));
  if (name_equal(&((decl_name)[0]), decl_name_len, lit_name, lit_name_len)) {
    return 1;
  }
  (void)((alias_count = pipeline_module_num_type_aliases_at(module)));
  while ((alias_i < alias_count)) {
    (void)((alias_name_len = pipeline_module_type_alias_name_len(module, alias_i)));
    if ((((alias_name_len ==decl_name_len) && (alias_name_len > 0)) && (alias_name_len <=63))) {
      (void)((alias_off = 0));
      while ((alias_off < alias_name_len)) {
        (void)(((alias_name)[alias_off] = pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off)));
        (void)((alias_off = (alias_off + 1)));
      }
      if (name_equal(&((alias_name)[0]), alias_name_len, &((decl_name)[0]), decl_name_len)) {
        (void)((alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i)));
        return typeck_named_type_matches_name_or_alias(module, arena, alias_target_ref, lit_name, lit_name_len, (depth + 1));
      }
    }
    (void)((alias_i = (alias_i + 1)));
  }
  return 0;
}
int typeck_layout_name_equal(struct ast_Module * module, int32_t k, uint8_t * nm, int32_t nlen) {
  uint8_t * buf = typeck_scratch64_slot(0);
  int32_t slen = pipeline_module_struct_layout_name_len(module, k);
  if (((slen !=nlen) || (nlen <=0))) {
    return 0;
  }
  (void)(pipeline_module_struct_layout_name_into(module, k, buf));
  return name_equal(buf, slen, nm, nlen);
}
int typeck_layout_field_name_equal(struct ast_Module * module, int32_t k, int32_t j, uint8_t * nm, int32_t nlen) {
  uint8_t * buf = typeck_scratch64_slot(1);
  int32_t fl = pipeline_module_struct_layout_field_name_len(module, k, j);
  if (((fl !=nlen) || (nlen <=0))) {
    return 0;
  }
  (void)(pipeline_module_struct_layout_field_name_into(module, k, j, buf));
  return name_equal(buf, fl, nm, nlen);
}
int32_t typeck_layout_name_into(struct ast_Module * module, int32_t k, uint8_t * buf) {
  (void)(pipeline_module_struct_layout_name_into(module, k, buf));
  return pipeline_module_struct_layout_name_len(module, k);
}
int32_t typeck_layout_field_name_into(struct ast_Module * module, int32_t k, int32_t j, uint8_t * buf) {
  (void)(pipeline_module_struct_layout_field_name_into(module, k, j, buf));
  return pipeline_module_struct_layout_field_name_len(module, k, j);
}
int typeck_import_path_slice_equal(struct ast_Module * module, int32_t imp_ix, int32_t off, int32_t seg_len, uint8_t * nm, int32_t nm_len) {
  if (((seg_len !=nm_len) || (seg_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < seg_len)) {
    if ((pipeline_module_import_path_byte_at(module, imp_ix, (off + i)) !=(nm)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int typeck_import_binding_name_equal(struct ast_Module * module, int32_t imp_ix, uint8_t * nm, int32_t nm_len) {
  int32_t bl = pipeline_module_import_binding_name_len(module, imp_ix);
  if (((bl !=nm_len) || (nm_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < nm_len)) {
    if ((pipeline_module_import_binding_name_byte_at(module, imp_ix, i) !=(nm)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t typeck_module_num_imports(struct ast_Module * module) {
  if ((module ==((struct ast_Module *)(0)))) {
    return 0;
  }
  int32_t n_imp = parser_get_module_num_imports(module);
  if ((n_imp > 0)) {
    return n_imp;
  }
  return (module->num_imports);
}
int typeck_var_is_import_visible_name(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  int32_t ii = 0;
  int32_t import_kind = 0;
  int32_t seg_rel = 0;
  int32_t seg_len = 0;
  if ((((module ==((struct ast_Module *)(0))) || (nm ==((uint8_t *)(0)))) || (nlen <=0))) {
    return 0;
  }
  int32_t n_imp = typeck_module_num_imports(module);
  while ((ii < n_imp)) {
    (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
    if (((import_kind ==1) && typeck_import_binding_name_equal(module, ii, nm, nlen))) {
      return 1;
    }
    if ((typeck_import_segment_at(module, ii, 0, &(seg_rel), &(seg_len)) && typeck_import_path_slice_equal(module, ii, seg_rel, seg_len, nm, nlen))) {
      return 1;
    }
    (void)((ii = (ii + 1)));
  }
  return 0;
}
int typeck_import_select_name_equal(struct ast_Module * module, int32_t imp_ix, int32_t sel, uint8_t * nm, int32_t nm_len) {
  int32_t sl = pipeline_module_import_select_name_len(module, imp_ix, sel);
  if (((sl !=nm_len) || (nm_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < nm_len)) {
    if ((pipeline_module_import_select_name_byte_at(module, imp_ix, sel, i) !=(nm)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int typeck_top_level_let_name_equal(struct ast_Module * module, int32_t tl_ix, uint8_t * nm, int32_t nm_len) {
  int32_t tll = pipeline_module_top_level_let_name_len(module, tl_ix);
  if (((tll !=nm_len) || (nm_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < nm_len)) {
    if ((pipeline_module_top_level_let_name_byte_at(module, tl_ix, i) !=(nm)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t typeck_dep_module_const_idx_named(struct ast_Module * module, uint8_t * nm, int32_t nlen, int32_t tl_ix) {
  if ((((module ==((struct ast_Module *)(0))) || (nm ==((uint8_t *)(0)))) || (nlen <=0))) {
    return -(1);
  }
  if ((tl_ix >=(module->num_top_level_lets))) {
    return -(1);
  }
  if (((pipeline_module_top_level_let_is_const(module, tl_ix) !=0) && typeck_top_level_let_name_equal(module, tl_ix, nm, nlen))) {
    return tl_ix;
  }
  return typeck_dep_module_const_idx_named(module, nm, nlen, (tl_ix + 1));
}
int32_t typeck_find_import_const_dep_index(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * nm, int32_t nlen, int32_t dep_ix) {
  struct ast_Module * dm = ((struct ast_Module *)(0));
  if (((((module ==((struct ast_Module *)(0))) || (ctx ==((struct ast_PipelineDepCtx *)(0)))) || (nm ==((uint8_t *)(0)))) || (nlen <=0))) {
    return -(1);
  }
  if ((dep_ix >=typeck_module_num_imports(module))) {
    return -(1);
  }
  (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_ix)));
  if (((dm !=((struct ast_Module *)(0))) && (typeck_dep_module_const_idx_named(dm, nm, nlen, 0) >=0))) {
    return dep_ix;
  }
  return typeck_find_import_const_dep_index(module, ctx, nm, nlen, (dep_ix + 1));
}
int32_t typeck_import_last_segment_into(struct ast_Module * module, int32_t imp_ix, uint8_t * out) {
  int32_t pl = 0;
  int32_t start = 0;
  int32_t i = 0;
  int32_t seg_len = 0;
  if (((((module ==((struct ast_Module *)(0))) || (out ==((uint8_t *)(0)))) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
    return 0;
  }
  (void)((pl = pipeline_module_import_path_len(module, imp_ix)));
  if (((pl <=0) || (pl > 63))) {
    return 0;
  }
  while ((i < pl)) {
    if ((pipeline_module_import_path_byte_at(module, imp_ix, i) ==46)) {
      (void)((start = (i + 1)));
    }
    (void)((i = (i + 1)));
  }
  (void)((seg_len = (pl - start)));
  if (((seg_len <=0) || (seg_len > 63))) {
    return 0;
  }
  (void)((i = 0));
  while ((i < seg_len)) {
    (void)(((out)[i] = pipeline_module_import_path_byte_at(module, imp_ix, (start + i))));
    (void)((i = (i + 1)));
  }
  return seg_len;
}
int32_t typeck_resolve_dep_index_for_import(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix) {
  int32_t plen = 0;
  int32_t dep_i = 0;
  int32_t nd = 0;
  uint8_t path_buf[128] = {};
  if (((((module ==((struct ast_Module *)(0))) || (ctx ==((struct ast_PipelineDepCtx *)(0)))) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
    return -(1);
  }
  (void)((plen = pipeline_module_import_path_len(module, imp_ix)));
  if (((plen <=0) || (plen > 63))) {
    return -(1);
  }
  while ((dep_i < plen)) {
    (void)(((path_buf)[dep_i] = pipeline_module_import_path_byte_at(module, imp_ix, dep_i)));
    (void)((dep_i = (dep_i + 1)));
  }
  (void)((nd = pipeline_dep_ctx_ndep(ctx)));
  (void)((dep_i = 0));
  while ((dep_i < nd)) {
    int32_t dep_plen = pipeline_dep_ctx_import_path_len(ctx, dep_i);
    if ((dep_plen ==plen)) {
      uint8_t dep_buf[128] = {};
      int eq = 1;
      int32_t k = 0;
      (void)(pipeline_dep_ctx_import_path_copy64(ctx, dep_i, &((dep_buf)[0])));
      while ((k < plen)) {
        if (((dep_buf)[k] !=(path_buf)[k])) {
          (void)((eq = 0));
          break;
        }
        (void)((k = (k + 1)));
      }
      if (eq) {
        return dep_i;
      }
    }
    (void)((dep_i = (dep_i + 1)));
  }
  return -(1);
}
int32_t typeck_import_const_binding_hint_at(struct ast_Module * module, int32_t dep_ix, uint8_t * out) {
  int32_t import_kind = 0;
  int32_t bl = 0;
  int32_t i = 0;
  if (((((module ==((struct ast_Module *)(0))) || (out ==((uint8_t *)(0)))) || (dep_ix < 0)) || (dep_ix >=typeck_module_num_imports(module)))) {
    return 0;
  }
  (void)((import_kind = pipeline_module_import_kind_at(module, dep_ix)));
  if ((import_kind ==1)) {
    (void)((bl = pipeline_module_import_binding_name_len(module, dep_ix)));
    if (((bl > 0) && (bl <=63))) {
      while ((i < bl)) {
        (void)(((out)[i] = pipeline_module_import_binding_name_byte_at(module, dep_ix, i)));
        (void)((i = (i + 1)));
      }
      return bl;
    }
  }
  return typeck_import_last_segment_into(module, dep_ix, out);
}
int32_t typeck_find_layout_idx_by_type_name(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  int32_t k = 0;
  while ((k < (module->num_struct_layouts))) {
    if (typeck_layout_name_equal(module, k, nm, nlen)) {
      return k;
    }
    (void)((k = (k + 1)));
  }
  return -(1);
}
int32_t typeck_x_named_builtin_align(uint8_t * nm, int32_t nlen) {
  if (((nm ==((uint8_t *)(0))) || (nlen <=0))) {
    return 0;
  }
  if (((((nlen ==3) && ((nm)[0] ==105)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if (((((nlen ==3) && ((nm)[0] ==117)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if ((((((nlen ==4) && ((nm)[0] ==98)) && ((nm)[1] ==111)) && ((nm)[2] ==111)) && ((nm)[3] ==108))) {
    return 4;
  }
  if ((((nlen ==2) && ((nm)[0] ==117)) && ((nm)[1] ==56))) {
    return 1;
  }
  if (((((nlen ==3) && ((nm)[0] ==105)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  if (((((nlen ==3) && ((nm)[0] ==117)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  if (((((((nlen ==5) && ((nm)[0] ==117)) && ((nm)[1] ==115)) && ((nm)[2] ==105)) && ((nm)[3] ==122)) && ((nm)[4] ==101))) {
    return 8;
  }
  if (((((((nlen ==5) && ((nm)[0] ==105)) && ((nm)[1] ==115)) && ((nm)[2] ==105)) && ((nm)[3] ==122)) && ((nm)[4] ==101))) {
    return 8;
  }
  if (((((nlen ==3) && ((nm)[0] ==102)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if (((((nlen ==3) && ((nm)[0] ==102)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  return 0;
}
int32_t typeck_x_named_builtin_size(uint8_t * nm, int32_t nlen) {
  int32_t a = typeck_x_named_builtin_align(nm, nlen);
  if (((((a ==1) && (nlen ==2)) && ((nm)[0] ==117)) && ((nm)[1] ==56))) {
    return 1;
  }
  if ((a ==4)) {
    return 4;
  }
  if ((a ==8)) {
    return 8;
  }
  return 0;
}
int32_t typeck_x_type_align(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  int32_t ko = 0;
  int32_t er = 0;
  int32_t nm_len = 0;
  int32_t li = 0;
  int32_t ba = 0;
  uint8_t * nm_buf = typeck_scratch64_slot(4);
  if ((((ast_ref_is_null(ty_ref) || (ty_ref <=0)) || (ty_ref > (arena->num_types))) || (depth > 64))) {
    return 1;
  }
  (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
  if ((ko ==2)) {
    return 1;
  }
  if (((((ko ==0) || (ko ==3)) || (ko ==1)) || (ko ==14))) {
    return 4;
  }
  if (((((((ko ==5) || (ko ==4)) || (ko ==6)) || (ko ==7)) || (ko ==15)) || (ko ==9))) {
    return 8;
  }
  if ((ko ==11)) {
    return 8;
  }
  if ((((ko ==10) || (ko ==12)) || (ko ==13))) {
    (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
    if (ast_ref_is_null(er)) {
      return 1;
    }
    return typeck_x_type_align(module, arena, er, (depth + 1));
  }
  if ((ko ==8)) {
    (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf)));
    (void)((li = typeck_find_layout_idx_by_type_name(module, nm_buf, nm_len)));
    if ((li >=0)) {
      return typeck_x_type_align_from_layout_glue(module, arena, li, (depth + 1));
    }
    (void)((ba = typeck_x_named_builtin_align(nm_buf, nm_len)));
    if ((ba > 0)) {
      return ba;
    }
    return 4;
  }
  return 1;
}
/* wave366/368: empty TYPE_NAMED ZST — nf==0 or all fields empty-of-empty; metrics accept fsize==0. */
int32_t typeck_type_is_empty_struct(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  int32_t ko = 0;
  int32_t nm_len = 0;
  int32_t li = 0;
  int32_t nf = 0;
  int32_t j = 0;
  int32_t ftr = 0;
  uint8_t * nm = typeck_scratch64_slot(4);
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (ty_ref <=0))) {
    return 0;
  }
  if (((ty_ref > (arena->num_types)) || (depth >64))) {
    return 0;
  }
  (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
  if ((ko !=8)) {
    return 0;
  }
  (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm)));
  if ((nm_len <=0)) {
    return 0;
  }
  (void)((li = typeck_find_layout_idx_by_type_name(module, nm, nm_len)));
  if ((li < 0)) {
    return 0;
  }
  (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
  if ((nf ==0)) {
    return 1;
  }
  (void)((j = 0));
  while ((j < nf)) {
    (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
    if ((typeck_type_is_empty_struct(module, arena, ftr, (depth + 1)) ==0)) {
      return 0;
    }
    (void)((j = (j + 1)));
  }
  return 1;
}
int32_t typeck_x_type_size(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  int32_t ko = 0;
  int32_t er = 0;
  int32_t asz = 0;
  int32_t es = 0;
  int32_t nm_len = 0;
  int32_t li2 = 0;
  int32_t bsz = 0;
  uint8_t * nm_buf_sz = typeck_scratch64_slot(4);
  if ((((ast_ref_is_null(ty_ref) || (ty_ref <=0)) || (ty_ref > (arena->num_types))) || (depth > 64))) {
    return 0;
  }
  (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
  if ((ko ==16)) {
    return 0;
  }
  if ((ko ==2)) {
    return 1;
  }
  if (((((ko ==0) || (ko ==3)) || (ko ==1)) || (ko ==14))) {
    return 4;
  }
  if (((((((ko ==5) || (ko ==4)) || (ko ==6)) || (ko ==7)) || (ko ==15)) || (ko ==9))) {
    return 8;
  }
  if ((ko ==11)) {
    return 16;
  }
  if ((ko ==12)) {
    (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
    if (ast_ref_is_null(er)) {
      return 0;
    }
    return typeck_x_type_size(module, arena, er, (depth + 1));
  }
  if (((ko ==10) || (ko ==13))) {
    int32_t soa_sz = typeck_soa_array_storage_size_glue(module, arena, er, asz, (depth + 1));
    (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
    (void)((asz = pipeline_type_array_size_at(arena, ty_ref)));
    if ((ast_ref_is_null(er) || (asz <=0))) {
      return 0;
    }
    if ((soa_sz > 0)) {
      return soa_sz;
    }
    (void)((es = typeck_x_type_size(module, arena, er, (depth + 1))));
    if ((es <=0)) {
      return 0;
    }
    return (asz * es);
  }
  if ((ko ==8)) {
    (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf_sz)));
    (void)((li2 = typeck_find_layout_idx_by_type_name(module, nm_buf_sz, nm_len)));
    if ((li2 >=0)) {
      return typeck_x_type_size_from_layout_glue(module, arena, li2, (depth + 1));
    }
    (void)((bsz = typeck_x_named_builtin_size(nm_buf_sz, nm_len)));
    if ((bsz > 0)) {
      return bsz;
    }
    return 4;
  }
  return 0;
}
int32_t typeck_struct_layout_metrics(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth, int32_t check_pad, int32_t * out_sz, int32_t * out_al) {
  int32_t nf = 0;
  int32_t allow = 0;
  int32_t layout_nlen = 0;
  int32_t current = 0;
  int32_t max_align = 1;
  int32_t j = 0;
  int32_t ftr = 0;
  int32_t flen = 0;
  int32_t A = 0;
  int32_t rem = 0;
  int32_t gap = 0;
  int32_t fsize = 0;
  int32_t end_pad = 0;
  int32_t fa = 0;
  uint8_t * layout_nm = typeck_scratch64_slot(2);
  uint8_t * field_nm = typeck_scratch64_slot(3);
  if (((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (out_sz ==((int32_t *)(0)))) || (out_al ==((int32_t *)(0))))) {
    return -(1);
  }
  if ((((li < 0) || (li >=pipeline_module_num_struct_layouts_at(module))) || (depth > 64))) {
    return -(1);
  }
  (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
  (void)((allow = pipeline_module_struct_layout_allow_padding_at(module, li)));
  (void)(typeck_layout_name_into(module, li, layout_nm));
  (void)((layout_nlen = pipeline_module_struct_layout_name_len(module, li)));
  (void)((current = 0));
  (void)((max_align = 1));
  if ((pipeline_module_struct_layout_packed_at(module, li) !=0)) {
    (void)((j = 0));
    while ((j < nf)) {
      (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
      (void)((fsize = typeck_x_type_size(module, arena, ftr, depth)));
      if (((fsize < 0) || ((fsize ==0) && (typeck_type_is_empty_struct(module, arena, ftr, depth) ==0)))) {
        if ((check_pad !=0)) {
          (void)(typeck_layout_field_name_into(module, li, j, field_nm));
          (void)((flen = pipeline_module_struct_layout_field_name_len(module, li, j)));
          (void)(driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen));
        }
        return -(1);
      }
      (void)((current = (current + fsize)));
      (void)((j = (j + 1)));
    }
    (void)(typeck_i32_ptr_store(out_sz, current));
    (void)(typeck_i32_ptr_store(out_al, 1));
    return 0;
  }
  (void)((j = 0));
  while ((j < nf)) {
    (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
    (void)(typeck_layout_field_name_into(module, li, j, field_nm));
    (void)((flen = pipeline_module_struct_layout_field_name_len(module, li, j)));
    (void)((fa = pipeline_module_struct_layout_field_align_at(module, li, j)));
    (void)((A = typeck_x_type_align(module, arena, ftr, depth)));
    if ((A <=0)) {
      (void)((A = 1));
    }
    if ((fa > A)) {
      (void)((A = fa));
    }
    (void)((rem = (current % A)));
    (void)((gap = (A - rem)));
    (void)((gap = (gap % A)));
    if ((((check_pad !=0) && (gap > 0)) && (allow ==0))) {
      (void)(driver_diagnostic_typeck_struct_padding_before(layout_nm, layout_nlen, gap, field_nm, flen));
      return -(1);
    }
    (void)((current = (current + gap)));
    (void)((fsize = typeck_x_type_size(module, arena, ftr, depth)));
    if (((fsize < 0) || ((fsize ==0) && (typeck_type_is_empty_struct(module, arena, ftr, depth) ==0)))) {
      if ((check_pad !=0)) {
        (void)(driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen));
      }
      return -(1);
    }
    (void)((current = (current + fsize)));
    if ((A > max_align)) {
      (void)((max_align = A));
    }
    (void)((j = (j + 1)));
  }
  if (((max_align > 0) && ((current % max_align) !=0))) {
    (void)((end_pad = (max_align - (current % max_align))));
    if ((((check_pad !=0) && (end_pad > 0)) && (allow ==0))) {
      (void)(driver_diagnostic_typeck_struct_padding_trailing(layout_nm, layout_nlen, end_pad));
      return -(1);
    }
    (void)((current = (current + end_pad)));
  }
  (void)(typeck_i32_ptr_store(out_sz, current));
  (void)(typeck_i32_ptr_store(out_al, max_align));
  return 0;
}
int32_t typeck_validate_struct_layouts_zero_padding(struct ast_Module * module, struct ast_ASTArena * arena) {
  int32_t li = 0;
  int32_t nsl = pipeline_module_num_struct_layouts_at(module);
  int32_t * sz_out = typeck_layout_metrics_sz_slot();
  int32_t * al_out = typeck_layout_metrics_al_slot();
  while ((li < nsl)) {
    (void)(typeck_layout_metrics_init_slot());
    if ((typeck_struct_layout_metrics(module, arena, li, 0, 1, sz_out, al_out) !=0)) {
      return -(1);
    }
    (void)(pipeline_typeck_pad_fields_warn_layout(module, arena, li));
    (void)(pipeline_typeck_hot_reorder_warn_layout(module, arena, li));
    (void)((li = (li + 1)));
  }
  return 0;
}
int32_t get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  int32_t k = 0;
  while ((k < (module->num_struct_layouts))) {
    if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
      int32_t j = 0;
      while ((j < pipeline_module_struct_layout_num_fields(module, k))) {
        if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
          return pipeline_module_struct_layout_field_offset_at(module, k, j);
        }
        (void)((j = (j + 1)));
      }
    }
    (void)((k = (k + 1)));
  }
  return -(1);
}
int32_t get_field_type_ref_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  int32_t k = 0;
  while ((k < (module->num_struct_layouts))) {
    if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
      int32_t j = 0;
      while ((j < pipeline_module_struct_layout_num_fields(module, k))) {
        if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
          return pipeline_module_struct_layout_field_type_ref(module, k, j);
        }
        (void)((j = (j + 1)));
      }
    }
    (void)((k = (k + 1)));
  }
  return 0;
}
int32_t get_field_offset_from_layout_deps(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  int32_t r = get_field_offset_from_layout(module, type_name, type_name_len, field_name, field_name_len);
  if ((r >=0)) {
    return r;
  }
  if ((ctx ==((struct ast_PipelineDepCtx *)(0)))) {
    return -(1);
  }
  int32_t nd = pipeline_dep_ctx_ndep(ctx);
  int32_t di = 0;
  while ((di < nd)) {
    struct ast_Module * dm = pipeline_dep_ctx_module_at(ctx, di);
    if ((dm !=((struct ast_Module *)(0)))) {
      (void)((r = get_field_offset_from_layout(dm, type_name, type_name_len, field_name, field_name_len)));
      if ((r >=0)) {
        return r;
      }
    }
    (void)((di = (di + 1)));
  }
  return -(1);
}
int32_t ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref) {
  int32_t num_fields = 0;
  int32_t name_len = 0;
  int32_t k = 0;
  int32_t found_idx = -(1);
  int32_t idx_m = 0;
  int32_t jm = 0;
  int32_t fnlen_m = 0;
  int32_t exists_m = 0;
  int32_t tm = 0;
  int32_t nf_layout = 0;
  int32_t flen_tm = 0;
  int32_t nf_m = 0;
  int32_t ftr_m = 0;
  int32_t init_rm = 0;
  int32_t fr_m = 0;
  int32_t idx = 0;
  int32_t j = 0;
  int32_t fnlen_j = 0;
  int32_t ftr = 0;
  int32_t init_r = 0;
  int32_t fr = 0;
  int32_t foff_m = 0;
  int32_t foff_j = 0;
  int32_t nsl = 0;
  int32_t sname_len = 0;
  uint8_t * lit_nm = typeck_scratch64_slot(4);
  uint8_t * layout_nm = typeck_scratch64_slot(5);
  uint8_t * field_nm = typeck_scratch64_slot(6);
  uint8_t * exist_nm = typeck_scratch64_slot(7);
  if (((expr_ref <=0) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref)));
  if (((num_fields <=0) || (num_fields > 8))) {
    return 0;
  }
  (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
  if (((name_len <=0) || (name_len > 127))) {
    return 0;
  }
  (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, lit_nm));
  (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
  (void)((k = 0));
  (void)((found_idx = -(1)));
  while ((k < nsl)) {
    (void)(pipeline_module_struct_layout_name_into(module, k, layout_nm));
    (void)((sname_len = pipeline_module_struct_layout_name_len(module, k)));
    if (name_equal(layout_nm, sname_len, lit_nm, name_len)) {
      (void)((found_idx = k));
      break;
    }
    (void)((k = (k + 1)));
  }
  if ((found_idx >=0)) {
    /* wave369: parser-complete layout (nf >= lit fields) — do not append (mid Nest scramble). */
    (void)((idx_m = found_idx));
    (void)((nf_layout = pipeline_module_struct_layout_num_fields(module, idx_m)));
    if ((nf_layout >= num_fields)) {
      return 0;
    }
    (void)((jm = 0));
    while ((jm < num_fields)) {
      (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm));
      (void)((fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm)));
      (void)((exists_m = 0));
      (void)((tm = 0));
      (void)((nf_layout = pipeline_module_struct_layout_num_fields(module, idx_m)));
      while ((tm < nf_layout)) {
        (void)(pipeline_module_struct_layout_field_name_into(module, idx_m, tm, exist_nm));
        (void)((flen_tm = pipeline_module_struct_layout_field_name_len(module, idx_m, tm)));
        if (name_equal(exist_nm, flen_tm, field_nm, fnlen_m)) {
          (void)((exists_m = 1));
        }
        (void)((tm = (tm + 1)));
      }
      if ((exists_m ==0)) {
        (void)((nf_m = nf_layout));
        (void)((ftr_m = 0));
        (void)((init_rm = pipeline_expr_struct_lit_init_ref(arena, expr_ref, jm)));
        if (((!(ast_ref_is_null(init_rm)) && (init_rm > 0)) && (init_rm <=(arena->num_exprs)))) {
          (void)((fr_m = expr_type_ref(arena, init_rm)));
          if (!(ast_ref_is_null(fr_m))) {
            (void)((ftr_m = fr_m));
          }
        }
        (void)((foff_m = pipeline_struct_layout_next_field_offset(module, arena, idx_m, ftr_m)));
        (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm));
        (void)((fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm)));
        (void)(pipeline_module_struct_layout_set_field(module, idx_m, nf_m, field_nm, fnlen_m, ftr_m, foff_m));
        (void)(pipeline_module_struct_layout_set_num_fields(module, idx_m, (nf_m + 1)));
      }
      (void)((jm = (jm + 1)));
    }
    return 0;
  }
  (void)((idx = pipeline_module_struct_layout_alloc(module)));
  if ((idx < 0)) {
    return -(1);
  }
  (void)(pipeline_module_struct_layout_reset_slot(module, idx));
  (void)(pipeline_module_struct_layout_set_name(module, idx, lit_nm, name_len));
  (void)(pipeline_module_struct_layout_set_num_fields(module, idx, num_fields));
  (void)((j = 0));
  while ((j < num_fields)) {
    (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_nm));
    (void)((fnlen_j = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j)));
    (void)((ftr = 0));
    (void)((init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j)));
    if (((!(ast_ref_is_null(init_r)) && (init_r > 0)) && (init_r <=(arena->num_exprs)))) {
      (void)((fr = expr_type_ref(arena, init_r)));
      if (!(ast_ref_is_null(fr))) {
        (void)((ftr = fr));
      }
    }
    (void)((foff_j = pipeline_struct_layout_next_field_offset(module, arena, idx, ftr)));
    (void)(pipeline_module_struct_layout_set_field(module, idx, j, field_nm, fnlen_j, ftr, foff_j));
    (void)((j = (j + 1)));
  }
  return 0;
}
int expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index) {
  uint8_t * vbuf = typeck_scratch64_slot(8);
  int32_t b_len = 0;
  int32_t a_len = 0;
  int32_t i = 0;
  if (((callee_expr_ref <=0) || (callee_expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=3)) {
    return 0;
  }
  (void)((b_len = pipeline_expr_var_name_len(arena, callee_expr_ref)));
  if (((func_index < 0) || (func_index >=(mod->num_funcs)))) {
    return 0;
  }
  (void)((a_len = pipeline_module_func_name_len_at(mod, func_index)));
  if ((((a_len !=b_len) || (a_len <=0)) || (a_len > 127))) {
    return 0;
  }
  (void)(pipeline_expr_var_name_into(arena, callee_expr_ref, vbuf));
  while ((i < a_len)) {
    if ((pipeline_module_func_name_byte_at(mod, func_index, i) !=(vbuf)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t find_or_alloc_named_type_ref(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len) {
  int32_t k = 0;
  int32_t ko = 0;
  int32_t exist_len = 0;
  int32_t ord_named = 8;
  uint8_t * nm_scr = typeck_scratch64_slot(12);
  if (((((arena ==((struct ast_ASTArena *)(0))) || (name ==((uint8_t *)(0)))) || (name_len <=0)) || (name_len > 127))) {
    return 0;
  }
  (void)((k = 1));
  while ((k <=(arena->num_types))) {
    (void)((ko = pipeline_type_kind_ord_at(arena, k)));
    if ((ko ==ord_named)) {
      (void)((exist_len = pipeline_type_named_name_into(arena, k, nm_scr)));
      if (((exist_len ==name_len) && name_equal(nm_scr, exist_len, name, name_len))) {
        return k;
      }
    }
    (void)((k = (k + 1)));
  }
  (void)((k = pipeline_arena_type_alloc(arena)));
  if ((k <=0)) {
    return 0;
  }
  if ((pipeline_type_init_named_at(arena, k, name, name_len) ==0)) {
    return 0;
  }
  return k;
}
int32_t typeck_field_access_lexer_wrapper_fallback(struct ast_ASTArena * arena, int32_t base_type_ref, uint8_t * field_name, int32_t field_name_len) {
  if (((ast_ref_is_null(base_type_ref) || (base_type_ref <=0)) || (base_type_ref > (arena->num_types)))) {
    return 0;
  }
  uint8_t bn[128] = {};
  int32_t bn_len = pipeline_type_named_name_into(arena, base_type_ref, &((bn)[0]));
  if (((bn_len <=0) || (bn_len > 63))) {
    return 0;
  }
  uint8_t nm_lexer[5] = {76, 101, 120, 101, 114};
  uint8_t nm_next_lex[8] = {110, 101, 120, 95, 108, 101, 120};
  uint8_t nm_token_start[11] = {116, 111, 107, 101, 110, 95, 115, 116, 97, 114, 116};
  uint8_t nm_lex[3] = {108, 101, 120};
  uint8_t nm_pos[3] = {112, 111, 115};
  uint8_t nm_line[4] = {108, 105, 110, 101};
  uint8_t nm_col[3] = {99, 111, 108};
  uint8_t nm_lres[11] = {76, 101, 120, 101, 114, 82, 101, 115, 117, 108, 116};
  uint8_t nm_cir[21] = {67, 111, 108, 108, 101, 99, 116, 73, 109, 112, 111, 114, 116, 115, 82, 101, 115, 117, 108, 116};
  uint8_t nm_tsar[18] = {84, 114, 121, 83, 107, 105, 112, 65, 108, 108, 111, 119, 82, 101, 115, 117, 108, 116};
  uint8_t nm_lpr[19] = {76, 105, 98, 114, 97, 114, 121, 80, 97, 114, 115, 101, 82, 101, 115, 117, 108, 116};
  uint8_t nm_per[15] = {80, 97, 114, 115, 101, 69, 120, 112, 114, 82, 101, 115, 117, 108, 116};
  uint8_t nm_pbr[16] = {80, 97, 114, 115, 101, 66, 108, 111, 99, 107, 82, 101, 115, 117, 108, 116};
  uint8_t nm_tlr[17] = {84, 111, 112, 76, 101, 118, 101, 108, 76, 101, 116, 82, 101, 115, 117, 108, 116};
  int32_t lex_tr = find_or_alloc_named_type_ref(arena, &((nm_lexer)[0]), 5);
  if ((lex_tr ==0)) {
    return 0;
  }
  if (((field_name_len ==8) && name_equal(field_name, field_name_len, &((nm_next_lex)[0]), 8))) {
    if (((bn_len ==11) && name_equal(&((bn)[0]), bn_len, &((nm_lres)[0]), 11))) {
      return lex_tr;
    }
    if (((bn_len ==19) && name_equal(&((bn)[0]), bn_len, &((nm_lpr)[0]), 19))) {
      return lex_tr;
    }
    if (((bn_len ==15) && name_equal(&((bn)[0]), bn_len, &((nm_per)[0]), 15))) {
      return lex_tr;
    }
    if (((bn_len ==16) && name_equal(&((bn)[0]), bn_len, &((nm_pbr)[0]), 16))) {
      return lex_tr;
    }
    if (((bn_len ==17) && name_equal(&((bn)[0]), bn_len, &((nm_tlr)[0]), 17))) {
      return lex_tr;
    }
  }
  if (((field_name_len ==11) && name_equal(field_name, field_name_len, &((nm_token_start)[0]), 11))) {
    if (((bn_len ==11) && name_equal(&((bn)[0]), bn_len, &((nm_lres)[0]), 11))) {
      return ensure_usize_type_ref(arena);
    }
  }
  if (((field_name_len ==3) && name_equal(field_name, field_name_len, &((nm_lex)[0]), 3))) {
    if (((bn_len ==21) && name_equal(&((bn)[0]), bn_len, &((nm_cir)[0]), 21))) {
      return lex_tr;
    }
    if (((bn_len ==18) && name_equal(&((bn)[0]), bn_len, &((nm_tsar)[0]), 18))) {
      return lex_tr;
    }
  }
  if (((bn_len ==5) && name_equal(&((bn)[0]), bn_len, &((nm_lexer)[0]), 5))) {
    if (((field_name_len ==3) && name_equal(field_name, field_name_len, &((nm_pos)[0]), 3))) {
      return ensure_usize_type_ref(arena);
    }
    if (((field_name_len ==4) && name_equal(field_name, field_name_len, &((nm_line)[0]), 4))) {
      return ensure_i32_type_ref(arena);
    }
    if (((field_name_len ==3) && name_equal(field_name, field_name_len, &((nm_col)[0]), 3))) {
      return ensure_i32_type_ref(arena);
    }
  }
  return 0;
}
/* Stage12.0.5 typeck wall slim — twin of typeck.x g_typeck_prim_* BSS cache. */
static uint8_t *g_typeck_prim_arena = 0;
static int32_t g_typeck_prim_ref[17];

int32_t typeck_ensure_primitive_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord) {
  int32_t k = 0;
  int32_t ko = 0;
  int32_t er = 0;
  int32_t asz = 0;
  uint8_t * a_u8 = 0;
  int32_t ci = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (kind_ord < 0)) || (kind_ord > 16))) {
    return 0;
  }
  a_u8 = (uint8_t *)arena;
  if (g_typeck_prim_arena != a_u8) {
    g_typeck_prim_arena = a_u8;
    ci = 0;
    while (ci <= 16) {
      g_typeck_prim_ref[ci] = 0;
      ci = ci + 1;
    }
  }
  if (g_typeck_prim_ref[kind_ord] > 0) {
    return g_typeck_prim_ref[kind_ord];
  }
  (void)((k = 1));
  while ((k <=(arena->num_types))) {
    (void)((ko = pipeline_type_kind_ord_at(arena, k)));
    if ((ko ==kind_ord)) {
      (void)((er = pipeline_type_elem_ref_at(arena, k)));
      (void)((asz = pipeline_type_array_size_at(arena, k)));
      if (((er ==0) && (asz ==0))) {
        g_typeck_prim_ref[kind_ord] = k;
        return k;
      }
    }
    (void)((k = (k + 1)));
  }
  (void)((k = pipeline_arena_type_alloc(arena)));
  if ((k <=0)) {
    return 0;
  }
  if ((pipeline_type_init_primitive_kind_at(arena, k, kind_ord) ==0)) {
    return 0;
  }
  g_typeck_prim_ref[kind_ord] = k;
  return k;
}
int32_t ensure_i32_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 0);
}
int32_t ensure_u8_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 2);
}
int32_t ensure_bool_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 1);
}
int32_t ensure_f32_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 14);
}
int32_t ensure_f64_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 15);
}
int32_t ensure_usize_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 6);
}
int32_t ensure_void_type_ref(struct ast_ASTArena * a) {
  return typeck_ensure_primitive_by_kind_ord(a, 16);
}
extern int32_t pipeline_typeck_get_dep_return_type_in_caller_arena_c(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_set_entry_module_for_dep_map_c(struct ast_Module * module);
int32_t get_dep_return_type_in_caller_arena(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx) {
  return pipeline_typeck_get_dep_return_type_in_caller_arena_c(from_dep_index, dep_return_type_ref, caller_arena, ctx);
}
int32_t ensure_i64_type_ref(struct ast_ASTArena * caller_arena) {
  return typeck_ensure_primitive_by_kind_ord(caller_arena, 5);
}
/* Stage12.0.5: G.7 thin → pipeline_type_find_or_alloc_compound (typeck.x twin). */
int32_t typeck_find_or_alloc_compound_type_ref(struct ast_ASTArena * a, int32_t kind_ord, int32_t elem_ref, int32_t array_size) {
  if ((((a ==((struct ast_ASTArena *)(0))) || (kind_ord < 0)) || (kind_ord > 15))) {
    return 0;
  }
  return pipeline_type_find_or_alloc_compound(a, kind_ord, elem_ref, array_size);
}
int32_t find_or_alloc_array_type_ref(struct ast_ASTArena * a, int32_t elem_ref, int32_t array_size) {
  if ((elem_ref ==0)) {
    return 0;
  }
  return typeck_find_or_alloc_compound_type_ref(a, 10, elem_ref, array_size);
}
int32_t ensure_array_type_ref_named_elem(struct ast_ASTArena * a, uint8_t * elem_nm, int32_t elem_nm_len, int32_t array_size) {
  int32_t elem_ref = find_or_alloc_named_type_ref(a, elem_nm, elem_nm_len);
  if ((elem_ref ==0)) {
    return 0;
  }
  return find_or_alloc_array_type_ref(a, elem_ref, array_size);
}
int32_t ensure_kind_only_type_ref(struct ast_ASTArena * w, enum ast_TypeKind kind) {
  return typeck_ensure_primitive_by_kind_ord(w, ((int32_t)(kind)));
}
int32_t find_or_alloc_ptr_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return typeck_find_or_alloc_compound_type_ref(w, 9, elem_ref, 0);
}
int32_t find_or_alloc_slice_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return pipeline_type_find_or_alloc_slice(w, elem_ref, ((uint8_t *)(0)), 0);
}
int32_t find_or_alloc_linear_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return typeck_find_or_alloc_compound_type_ref(w, 12, elem_ref, 0);
}
int32_t find_or_alloc_vector_type_ref(struct ast_ASTArena * w, int32_t elem_ref, int32_t array_size) {
  return typeck_find_or_alloc_compound_type_ref(w, 13, elem_ref, array_size);
}
int32_t dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena) {
  int32_t kind = 0;
  int32_t inner_mapped = 0;
  int32_t elem_ref = 0;
  int32_t array_size = 0;
  int32_t nlen = 0;
  uint8_t * nm_buf = typeck_scratch64_slot(0);
  int32_t ord_i32 = 0;
  int32_t ord_bool = 1;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_isize = 7;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_array = 10;
  int32_t ord_slice = 11;
  int32_t ord_linear = 12;
  int32_t ord_vector = 13;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t ord_usize = 6;
  int32_t ord_void = 16;
  if ((dep_return_type_ref <=0)) {
    return 0;
  }
  (void)((kind = pipeline_type_kind_ord_at(dep_arena, dep_return_type_ref)));
  if ((kind < 0)) {
    return 0;
  }
  if ((((((((((((kind ==ord_i32) || (kind ==ord_i64)) || (kind ==ord_bool)) || (kind ==ord_f64)) || (kind ==ord_u8)) || (kind ==ord_u32)) || (kind ==ord_u64)) || (kind ==ord_isize)) || (kind ==ord_f32)) || (kind ==ord_usize)) || (kind ==ord_void))) {
    return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
  }
  if ((kind ==ord_named)) {
    (void)((nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf)));
    if ((nlen <=0)) {
      return 0;
    }
    return find_or_alloc_named_type_ref(caller_arena, nm_buf, nlen);
  }
  (void)((elem_ref = pipeline_type_elem_ref_at(dep_arena, dep_return_type_ref)));
  (void)((inner_mapped = 0));
  if (!(ast_ref_is_null(elem_ref))) {
    (void)((inner_mapped = dep_return_type_to_caller_arena(dep_arena, elem_ref, caller_arena)));
    if ((inner_mapped ==0)) {
      return 0;
    }
  }
  (void)((array_size = pipeline_type_array_size_at(dep_arena, dep_return_type_ref)));
  if ((kind ==ord_slice)) {
    int32_t rlen = pipeline_type_region_label_len_at(dep_arena, dep_return_type_ref);
    uint8_t * rbuf = typeck_scratch64_slot(14);
    if ((rlen > 0)) {
      (void)(pipeline_type_region_label_into(dep_arena, dep_return_type_ref, rbuf));
    }
    return pipeline_type_find_or_alloc_slice(caller_arena, inner_mapped, rbuf, rlen);
  }
  if ((kind ==ord_ptr)) {
    return find_or_alloc_ptr_type_ref(caller_arena, inner_mapped);
  }
  if ((kind ==ord_linear)) {
    return find_or_alloc_linear_type_ref(caller_arena, inner_mapped);
  }
  if ((kind ==ord_vector)) {
    return find_or_alloc_vector_type_ref(caller_arena, inner_mapped, array_size);
  }
  if ((kind ==ord_array)) {
    if ((ast_ref_is_null(elem_ref) || (array_size <=0))) {
      return 0;
    }
    return find_or_alloc_array_type_ref(caller_arena, inner_mapped, array_size);
  }
  if ((!(ast_ref_is_null(elem_ref)) || (array_size !=0))) {
    return 0;
  }
  (void)((nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf)));
  if ((nlen !=0)) {
    return 0;
  }
  return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
}
int32_t expr_field_access_fallback_scalar_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  if ((field_name_len >=4)) {
    int32_t br = (field_name_len - 4);
    if ((((((field_name)[br] ==95) && ((field_name)[(br + 1)] ==114)) && ((field_name)[(br + 2)] ==101)) && ((field_name)[(br + 3)] ==102))) {
      return ensure_i32_type_ref(arena);
    }
  }
  uint8_t nm_match_num_arms[14] = {109, 97, 116, 99, 104, 95, 110, 117, 109, 95, 97, 114, 109, 115};
  uint8_t nm_field_access_is_enum_variant[28] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 105, 115, 95, 101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116};
  uint8_t nm_field_access_field_len[22] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 108, 101, 110};
  uint8_t nm_field_access_offset[19] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 111, 102, 102, 115, 101, 116};
  uint8_t nm_index_base_is_slice[19] = {105, 110, 100, 101, 120, 95, 98, 97, 115, 101, 95, 105, 115, 95, 115, 108, 105, 99, 101};
  uint8_t nm_call_num_args[13] = {99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115};
  uint8_t nm_method_call_name_len[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101, 95, 108, 101, 110};
  uint8_t nm_method_call_num_args[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115};
  uint8_t nm_const_folded_val[16] = {99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95, 118, 97, 108};
  uint8_t nm_const_folded_valid[18] = {99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95, 118, 97, 108, 105, 100};
  uint8_t nm_index_proven_in_bounds[22] = {105, 110, 100, 101, 120, 95, 112, 114, 111, 118, 101, 110, 95, 105, 110, 95, 98, 111, 117, 110, 100, 115};
  uint8_t nm_call_resolved_func_index[24] = {99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 102, 117, 110, 99, 95, 105, 110, 100, 101, 120};
  uint8_t nm_call_resolved_dep_index[22] = {99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 100, 101, 112, 95, 105, 110, 100, 101, 120};
  uint8_t nm_enum_variant_tag[16] = {101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 116, 97, 103};
  if (((field_name_len ==14) && name_equal(field_name, field_name_len, &((nm_match_num_arms)[0]), 14))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==28) && name_equal(field_name, field_name_len, &((nm_field_access_is_enum_variant)[0]), 28))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && name_equal(field_name, field_name_len, &((nm_field_access_field_len)[0]), 22))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==19) && name_equal(field_name, field_name_len, &((nm_field_access_offset)[0]), 19))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==19) && name_equal(field_name, field_name_len, &((nm_index_base_is_slice)[0]), 19))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==13) && name_equal(field_name, field_name_len, &((nm_call_num_args)[0]), 13))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==20) && name_equal(field_name, field_name_len, &((nm_method_call_name_len)[0]), 20))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==20) && name_equal(field_name, field_name_len, &((nm_method_call_num_args)[0]), 20))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==16) && name_equal(field_name, field_name_len, &((nm_const_folded_val)[0]), 16))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==18) && name_equal(field_name, field_name_len, &((nm_const_folded_valid)[0]), 18))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && name_equal(field_name, field_name_len, &((nm_index_proven_in_bounds)[0]), 22))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==24) && name_equal(field_name, field_name_len, &((nm_call_resolved_func_index)[0]), 24))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && name_equal(field_name, field_name_len, &((nm_call_resolved_dep_index)[0]), 22))) {
    return ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==16) && name_equal(field_name, field_name_len, &((nm_enum_variant_tag)[0]), 16))) {
    return ensure_i32_type_ref(arena);
  }
  return 0;
}
int32_t get_field_type_ref_from_layout_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  uint8_t nm_funcs_pool[5] = {102, 117, 110, 99, 115};
  uint8_t nm_func_elem[4] = {70, 117, 110, 99};
  if (((field_name_len ==5) && name_equal(field_name, field_name_len, &((nm_funcs_pool)[0]), 5))) {
    int32_t arr_funcs_pool = ensure_array_type_ref_named_elem(arena, &((nm_func_elem)[0]), 4, 256);
    if ((arr_funcs_pool !=0)) {
      return arr_funcs_pool;
    }
  }
  uint8_t nm_struct_layouts_pool[14] = {115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
  uint8_t nm_sl_elem[12] = {83, 116, 114, 117, 99, 116, 76, 97, 121, 111, 117, 116};
  if (((field_name_len ==14) && name_equal(field_name, field_name_len, &((nm_struct_layouts_pool)[0]), 14))) {
    int32_t arr_sl_pool = ensure_array_type_ref_named_elem(arena, &((nm_sl_elem)[0]), 12, 32);
    if ((arr_sl_pool !=0)) {
      return arr_sl_pool;
    }
  }
  uint8_t nm_num_struct_layouts_pool[18] = {110, 117, 109, 95, 115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
  if (((field_name_len ==18) && name_equal(field_name, field_name_len, &((nm_num_struct_layouts_pool)[0]), 18))) {
    return ensure_i32_type_ref(arena);
  }
  int32_t u8_inline = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
  if ((u8_inline !=0)) {
    return u8_inline;
  }
  int32_t i32_arr_inline = typeck_expr_inline_array_field_type_ref(arena, field_name, field_name_len);
  if ((i32_arr_inline !=0)) {
    return i32_arr_inline;
  }
  int32_t r = get_field_type_ref_from_layout(module, type_name, type_name_len, field_name, field_name_len);
  if ((r !=0)) {
    return r;
  }
  if ((ctx ==((struct ast_PipelineDepCtx *)(0)))) {
    return 0;
  }
  int32_t nd2 = pipeline_dep_ctx_ndep(ctx);
  int32_t di = 0;
  while ((di < nd2)) {
    struct ast_Module * dm = pipeline_dep_ctx_module_at(ctx, di);
    if ((dm !=((struct ast_Module *)(0)))) {
      (void)((r = get_field_type_ref_from_layout(dm, type_name, type_name_len, field_name, field_name_len)));
      if ((r !=0)) {
        struct ast_ASTArena * da = pipeline_dep_ctx_arena_at(ctx, di);
        if ((da !=((struct ast_ASTArena *)(0)))) {
          return dep_return_type_to_caller_arena(da, r, arena);
        }
        return r;
      }
    }
    (void)((di = (di + 1)));
  }
  if ((((((type_name_len ==4) && ((type_name)[0] ==69)) && ((type_name)[1] ==120)) && ((type_name)[2] ==112)) && ((type_name)[3] ==114))) {
    int32_t u8_fb = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
    if ((u8_fb !=0)) {
      return u8_fb;
    }
    int32_t arr_fb = typeck_expr_inline_array_field_type_ref(arena, field_name, field_name_len);
    if ((arr_fb !=0)) {
      return arr_fb;
    }
    int32_t fb = expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
    if ((fb !=0)) {
      return fb;
    }
  }
  if ((((((type_name_len ==4) && ((type_name)[0] ==84)) && ((type_name)[1] ==121)) && ((type_name)[2] ==112)) && ((type_name)[3] ==101))) {
    int32_t u8_ty = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
    if ((u8_ty !=0)) {
      return u8_ty;
    }
  }
  if ((((((type_name_len ==4) && ((type_name)[0] ==70)) && ((type_name)[1] ==117)) && ((type_name)[2] ==110)) && ((type_name)[3] ==99))) {
    int32_t u8_fn = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
    if ((u8_fn !=0)) {
      return u8_fn;
    }
    uint8_t nm_params[6] = {112, 97, 114, 97, 109, 115};
    uint8_t nm_pa[5] = {80, 97, 114, 97, 109};
    if (((field_name_len ==6) && name_equal(field_name, field_name_len, &((nm_params)[0]), 6))) {
      return ensure_array_type_ref_named_elem(arena, &((nm_pa)[0]), 5, 16);
    }
    int32_t fb_fn = expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
    if ((fb_fn !=0)) {
      return fb_fn;
    }
  }
  if (((((((type_name_len ==5) && ((type_name)[0] ==80)) && ((type_name)[1] ==97)) && ((type_name)[2] ==114)) && ((type_name)[3] ==97)) && ((type_name)[4] ==109))) {
    uint8_t nm_pname[4] = {110, 97, 109, 101};
    if (((field_name_len ==4) && name_equal(field_name, field_name_len, &((nm_pname)[0]), 4))) {
      int32_t u8r_p = ensure_u8_type_ref(arena);
      if ((u8r_p !=0)) {
        return find_or_alloc_array_type_ref(arena, u8r_p, 32);
      }
    }
  }
  if ((((((((((((((type_name_len ==12) && ((type_name)[0] ==83)) && ((type_name)[1] ==116)) && ((type_name)[2] ==114)) && ((type_name)[3] ==117)) && ((type_name)[4] ==99)) && ((type_name)[5] ==116)) && ((type_name)[6] ==76)) && ((type_name)[7] ==97)) && ((type_name)[8] ==121)) && ((type_name)[9] ==111)) && ((type_name)[10] ==117)) && ((type_name)[11] ==116))) {
    int32_t u8r_sl = ensure_u8_type_ref(arena);
    int32_t i32r_sl = ensure_i32_type_ref(arena);
    uint8_t nm_sl_name[4] = {110, 97, 109, 101};
    uint8_t nm_sl_field_names[11] = {102, 105, 101, 108, 100, 95, 110, 97, 109, 101, 115};
    uint8_t nm_sl_field_lens[11] = {102, 105, 101, 108, 100, 95, 108, 101, 110, 115};
    uint8_t nm_sl_field_offsets[13] = {102, 105, 101, 108, 100, 95, 111, 102, 102, 115, 101, 116, 115};
    uint8_t nm_sl_field_type_refs[15] = {102, 105, 101, 108, 100, 95, 116, 121, 112, 101, 95, 114, 101, 102, 115};
    uint8_t nm_sl_num_fields[10] = {110, 117, 109, 95, 102, 105, 101, 108, 100, 115};
    uint8_t nm_sl_allow_padding[14] = {97, 108, 108, 111, 119, 95, 112, 97, 100, 100, 105, 110, 103};
    if ((((field_name_len ==4) && name_equal(field_name, field_name_len, &((nm_sl_name)[0]), 4)) && (u8r_sl !=0))) {
      return find_or_alloc_array_type_ref(arena, u8r_sl, 64);
    }
    if ((((field_name_len ==11) && name_equal(field_name, field_name_len, &((nm_sl_field_names)[0]), 11)) && (u8r_sl !=0))) {
      int32_t row_u8 = find_or_alloc_array_type_ref(arena, u8r_sl, 64);
      if ((row_u8 !=0)) {
        return find_or_alloc_array_type_ref(arena, row_u8, 64);
      }
    }
    if ((((field_name_len ==11) && name_equal(field_name, field_name_len, &((nm_sl_field_lens)[0]), 11)) && (i32r_sl !=0))) {
      return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
    }
    if ((((field_name_len ==13) && name_equal(field_name, field_name_len, &((nm_sl_field_offsets)[0]), 13)) && (i32r_sl !=0))) {
      return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
    }
    if ((((field_name_len ==15) && name_equal(field_name, field_name_len, &((nm_sl_field_type_refs)[0]), 15)) && (i32r_sl !=0))) {
      return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
    }
    if (((field_name_len ==10) && name_equal(field_name, field_name_len, &((nm_sl_num_fields)[0]), 10))) {
      return i32r_sl;
    }
    if (((field_name_len ==14) && name_equal(field_name, field_name_len, &((nm_sl_allow_padding)[0]), 14))) {
      return i32r_sl;
    }
    if ((((((((((field_name_len ==8) && ((field_name)[0] ==110)) && ((field_name)[1] ==97)) && ((field_name)[2] ==109)) && ((field_name)[3] ==101)) && ((field_name)[4] ==95)) && ((field_name)[5] ==108)) && ((field_name)[6] ==101)) && ((field_name)[7] ==110))) {
      return i32r_sl;
    }
  }
  return 0;
}
int32_t typeck_inline_u8_64_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  int32_t u8r = ensure_u8_type_ref(arena);
  if ((u8r ==0)) {
    return 0;
  }
  uint8_t nm_name[4] = {110, 97, 109, 101};
  uint8_t nm_var_name[8] = {118, 97, 114, 95, 110, 97, 109, 101};
  uint8_t nm_field_access_field_name[22] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 110, 97, 109, 101};
  uint8_t nm_method_call_name[16] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101};
  uint8_t nm_struct_lit_struct_name[22] = {115, 116, 114, 117, 99, 116, 95, 108, 105, 116, 95, 115, 116, 114, 117, 99, 116, 95, 110, 97, 109, 101};
  if (((field_name_len ==4) && name_equal(field_name, field_name_len, &((nm_name)[0]), 4))) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==8) && name_equal(field_name, field_name_len, &((nm_var_name)[0]), 8))) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==22) && name_equal(field_name, field_name_len, &((nm_field_access_field_name)[0]), 22))) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==16) && name_equal(field_name, field_name_len, &((nm_method_call_name)[0]), 16))) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==22) && name_equal(field_name, field_name_len, &((nm_struct_lit_struct_name)[0]), 22))) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  return 0;
}
int32_t typeck_expr_inline_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  int32_t i32r = ensure_i32_type_ref(arena);
  if ((i32r ==0)) {
    return 0;
  }
  uint8_t nm_call_arg_refs[13] = {99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115};
  uint8_t nm_method_call_arg_refs[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115};
  uint8_t nm_match_arm_result_refs[21] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 114, 101, 115, 117, 108, 116, 95, 114, 101, 102, 115};
  uint8_t nm_array_lit_elem_refs[19] = {97, 114, 114, 97, 121, 95, 108, 105, 116, 95, 101, 108, 101, 109, 95, 114, 101, 102, 115};
  uint8_t nm_match_arm_is_wildcard[21] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 119, 105, 108, 100, 99, 97, 114, 100};
  uint8_t nm_match_arm_lit_val[17] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 108, 105, 116, 95, 118, 97, 108};
  uint8_t nm_match_arm_is_enum_variant[25] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116};
  uint8_t nm_match_arm_variant_index[23] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 105, 110, 100, 101, 120};
  if (((field_name_len ==13) && name_equal(field_name, field_name_len, &((nm_call_arg_refs)[0]), 13))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==20) && name_equal(field_name, field_name_len, &((nm_method_call_arg_refs)[0]), 20))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==21) && name_equal(field_name, field_name_len, &((nm_match_arm_result_refs)[0]), 21))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==19) && name_equal(field_name, field_name_len, &((nm_array_lit_elem_refs)[0]), 19))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==21) && name_equal(field_name, field_name_len, &((nm_match_arm_is_wildcard)[0]), 21))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==17) && name_equal(field_name, field_name_len, &((nm_match_arm_lit_val)[0]), 17))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==25) && name_equal(field_name, field_name_len, &((nm_match_arm_is_enum_variant)[0]), 25))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==23) && name_equal(field_name, field_name_len, &((nm_match_arm_variant_index)[0]), 23))) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  return 0;
}
int32_t entry_module_find_struct_layout_index(struct ast_Module * mod, uint8_t * nm, int32_t nlen) {
  return typeck_find_layout_idx_by_type_name(mod, nm, nlen);
}
void typeck_merge_dep_struct_layouts_into_entry(struct ast_Module * mod, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  int32_t nd_merge = 0;
  int32_t di = 0;
  struct ast_Module * dm = ((struct ast_Module *)(0));
  struct ast_ASTArena * darena = ((struct ast_ASTArena *)(0));
  int32_t k = 0;
  int32_t nl = 0;
  int32_t nf_dep = 0;
  int32_t ex = 0;
  int32_t need = 0;
  int weak_entry = 0;
  int is_expr_nm = 0;
  int32_t ni = 0;
  int32_t j = 0;
  int32_t raw_fr = 0;
  int32_t mapped = 0;
  int32_t fnlen = 0;
  int32_t foff = 0;
  int32_t ndm_sl = 0;
  uint8_t * dep_nm_buf = typeck_scratch64_slot(9);
  uint8_t * fn_buf = typeck_scratch64_slot(10);
  if ((ctx ==((struct ast_PipelineDepCtx *)(0)))) {
    return;
  }
  (void)((nd_merge = pipeline_dep_ctx_ndep(ctx)));
  (void)((di = 0));
  while ((di < nd_merge)) {
    (void)((dm = pipeline_dep_ctx_module_at(ctx, di)));
    (void)((darena = pipeline_dep_ctx_arena_at(ctx, di)));
    if (((dm ==((struct ast_Module *)(0))) || (darena ==((struct ast_ASTArena *)(0))))) {
      (void)((di = (di + 1)));
      continue;
    }
    (void)((ndm_sl = pipeline_module_num_struct_layouts_at(dm)));
    (void)((k = 0));
    while ((k < ndm_sl)) {
      (void)((nl = pipeline_module_struct_layout_name_len(dm, k)));
      if (((nl > 0) && (nl <=63))) {
        (void)((nf_dep = pipeline_module_struct_layout_num_fields(dm, k)));
        if ((nf_dep > 64)) {
          (void)((nf_dep = 64));
        }
        (void)(pipeline_module_struct_layout_name_into(dm, k, dep_nm_buf));
        (void)((ex = entry_module_find_struct_layout_index(mod, dep_nm_buf, nl)));
        (void)((need = 0));
        if ((ex < 0)) {
          (void)((need = 1));
        } else {
          (void)((weak_entry = 0));
          if (((pipeline_module_struct_layout_num_fields(mod, ex) >=2) && (pipeline_module_struct_layout_field_type_ref(mod, ex, 1) ==0))) {
            (void)((weak_entry = 1));
          }
          (void)((is_expr_nm = 0));
          if ((nl ==4)) {
            if (((((pipeline_module_struct_layout_name_byte_at(dm, k, 0) ==69) && (pipeline_module_struct_layout_name_byte_at(dm, k, 1) ==120)) && (pipeline_module_struct_layout_name_byte_at(dm, k, 2) ==112)) && (pipeline_module_struct_layout_name_byte_at(dm, k, 3) ==114))) {
              (void)((is_expr_nm = 1));
            }
          }
          if ((((nf_dep > pipeline_module_struct_layout_num_fields(mod, ex)) || weak_entry) || is_expr_nm)) {
            (void)((need = 1));
          }
          /* wave1220 P5: re-copy when field counts match but types may differ. */
          if (((nf_dep > 0 && (nf_dep >= pipeline_module_struct_layout_num_fields(mod, ex))) && (pipeline_module_struct_layout_num_fields(mod, ex) > 0))) {
            (void)((need = 1));
          }
          if (((pipeline_module_struct_layout_soa_at(dm, k) !=0) && (pipeline_module_struct_layout_soa_at(mod, ex) ==0))) {
            (void)((need = 1));
          }
        }
        if ((need !=0)) {
          (void)((ni = ex));
          if ((ex < 0)) {
            (void)((ni = pipeline_module_struct_layout_alloc(mod)));
            if ((ni < 0)) {
              (void)((k = (k + 1)));
              continue;
            }
          }
          (void)(pipeline_module_struct_layout_reset_slot(mod, ni));
          (void)(pipeline_module_struct_layout_set_name(mod, ni, dep_nm_buf, nl));
          (void)((j = 0));
          while ((j < nf_dep)) {
            (void)((raw_fr = pipeline_module_struct_layout_field_type_ref(dm, k, j)));
            (void)((mapped = 0));
            if ((raw_fr !=0)) {
              (void)((mapped = dep_return_type_to_caller_arena(darena, raw_fr, arena)));
            }
            (void)((fnlen = pipeline_module_struct_layout_field_name_len(dm, k, j)));
            (void)(pipeline_module_struct_layout_field_name_into(dm, k, j, fn_buf));
            (void)((foff = pipeline_module_struct_layout_field_offset_at(dm, k, j)));
            (void)(pipeline_module_struct_layout_set_field(mod, ni, j, fn_buf, fnlen, mapped, foff));
            (void)(pipeline_module_struct_layout_set_field_align(mod, ni, j, pipeline_module_struct_layout_field_align_at(dm, k, j)));
            (void)((j = (j + 1)));
          }
          (void)(pipeline_module_struct_layout_set_num_fields(mod, ni, nf_dep));
          (void)(pipeline_module_struct_layout_set_allow_padding(mod, ni, pipeline_module_struct_layout_allow_padding_at(dm, k)));
          (void)(pipeline_module_struct_layout_set_soa(mod, ni, pipeline_module_struct_layout_soa_at(dm, k)));
          (void)(pipeline_module_struct_layout_set_packed(mod, ni, pipeline_module_struct_layout_packed_at(dm, k)));
        }
      }
      (void)((k = (k + 1)));
    }
    (void)((di = (di + 1)));
  }
}
void typeck_wpo_unify_soa_layouts(struct ast_Module * entry, struct ast_PipelineDepCtx * ctx) {
  int32_t nd = 0;
  int32_t mi = 0;
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t nsl = 0;
  int32_t k = 0;
  int32_t nl = 0;
  int32_t any_soa = 0;
  int32_t mj = 0;
  struct ast_Module * dm2 = ((struct ast_Module *)(0));
  int32_t nsl2 = 0;
  int32_t k2 = 0;
  int32_t nl2 = 0;
  int32_t li = 0;
  uint8_t * nm_buf = typeck_scratch64_slot(11);
  uint8_t * nm2 = typeck_scratch64_slot(12);
  if (((entry ==((struct ast_Module *)(0))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return;
  }
  (void)((nd = pipeline_dep_ctx_ndep(ctx)));
  (void)((mi = -(1)));
  while ((mi < nd)) {
    (void)((dm = entry));
    if ((mi >=0)) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, mi)));
    }
    if ((dm ==((struct ast_Module *)(0)))) {
      (void)((mi = (mi + 1)));
      continue;
    }
    (void)((nsl = pipeline_module_num_struct_layouts_at(dm)));
    (void)((k = 0));
    while ((k < nsl)) {
      (void)((nl = pipeline_module_struct_layout_name_len(dm, k)));
      if (((nl > 0) && (nl <=63))) {
        (void)(pipeline_module_struct_layout_name_into(dm, k, nm_buf));
        (void)((any_soa = pipeline_module_struct_layout_soa_at(dm, k)));
        (void)((mj = -(1)));
        while (((mj < nd) && (any_soa ==0))) {
          (void)((dm2 = entry));
          if ((mj >=0)) {
            (void)((dm2 = pipeline_dep_ctx_module_at(ctx, mj)));
          }
          if ((dm2 !=((struct ast_Module *)(0)))) {
            (void)((nsl2 = pipeline_module_num_struct_layouts_at(dm2)));
            (void)((k2 = 0));
            while (((k2 < nsl2) && (any_soa ==0))) {
              (void)((nl2 = pipeline_module_struct_layout_name_len(dm2, k2)));
              if ((nl2 ==nl)) {
                (void)(pipeline_module_struct_layout_name_into(dm2, k2, nm2));
                if ((name_equal(nm_buf, nl, nm2, nl2) && (pipeline_module_struct_layout_soa_at(dm2, k2) !=0))) {
                  (void)((any_soa = 1));
                }
              }
              (void)((k2 = (k2 + 1)));
            }
          }
          (void)((mj = (mj + 1)));
        }
        if ((any_soa !=0)) {
          (void)((mj = -(1)));
          while ((mj < nd)) {
            (void)((dm2 = entry));
            if ((mj >=0)) {
              (void)((dm2 = pipeline_dep_ctx_module_at(ctx, mj)));
            }
            if ((dm2 !=((struct ast_Module *)(0)))) {
              (void)((li = typeck_find_layout_idx_by_type_name(dm2, nm_buf, nl)));
              if (((li >=0) && (pipeline_module_struct_layout_soa_at(dm2, li) ==0))) {
                (void)(pipeline_module_struct_layout_set_soa(dm2, li, 1));
              }
            }
            (void)((mj = (mj + 1)));
          }
        }
      }
      (void)((k = (k + 1)));
    }
    (void)((mi = (mi + 1)));
  }
}
int32_t typeck_resolve_scan_dep_with_apply(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax, int32_t want_apply) {
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t ret = 0;
  int32_t * fn_slot = typeck_call_resolve_func_idx_slot();
  if ((dep_i >=imax)) {
    return 0;
  }
  (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_i)));
  if ((dm !=((struct ast_Module *)(0)))) {
    (void)(typeck_i32_ptr_store(fn_slot, 0));
    (void)((ret = find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx, fn_slot)));
    if ((ret !=0)) {
      if ((want_apply !=0)) {
        (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek()));
      }
      return ret;
    }
    if ((dep_i < typeck_module_num_imports(module))) {
      (void)((ret = resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord, dep_i, ctx, fn_slot)));
      if ((ret !=0)) {
        if ((want_apply !=0)) {
          (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek()));
        }
        return ret;
      }
    }
  }
  return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord, call_expr_ref, ctx, (dep_i + 1), imax, want_apply);
}
int32_t find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  int32_t j = 0;
  while ((j < (mod->num_funcs))) {
    if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
      int32_t ret_dep = pipeline_module_func_return_type_at(mod, j);
      if ((func_index_out !=((int32_t *)(0)))) {
        (void)(((func_index_out)[0] = j));
      }
      if ((from_dep_index < 0)) {
        return ret_dep;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, ret_dep, caller_arena, ctx);
    }
    (void)((j = (j + 1)));
  }
  return 0;
}
extern int32_t pipeline_visibility_allow_func(struct ast_Module * mod, int32_t fi, int32_t cross_module);
int32_t find_func_return_type_in_module_by_name(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  if (((name_len <=0) || (name_len > 127))) {
    return 0;
  }
  int32_t j = 0;
  while ((j < (mod->num_funcs))) {
    if ((pipeline_module_func_name_equal_at(mod, j, name, name_len) !=0)) {
      int32_t rtr = pipeline_module_func_return_type_at(mod, j);
      if (((from_dep_index >=0) && (pipeline_visibility_allow_func(mod, j, 1) ==0))) {
        (void)((j = (j + 1)));
        continue;
      }
      if ((func_index_out !=((int32_t *)(0)))) {
        (void)(((func_index_out)[0] = j));
      }
      if ((from_dep_index < 0)) {
        return rtr;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, rtr, caller_arena, ctx);
    }
    (void)((j = (j + 1)));
  }
  return 0;
}
int32_t typeck_overload_arg_param_score(struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t arg_i, int32_t param_ty_raw, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx) {
  int32_t arg_ref = 0;
  int32_t arg_ty = 0;
  int32_t param_ty = 0;
  int32_t ord_as = 54;
  int32_t as_tgt = 0;
  if ((((caller_arena ==((struct ast_ASTArena *)(0))) || (call_expr_ref <=0)) || (arg_i < 0))) {
    return -(1);
  }
  (void)((arg_ref = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, arg_i)));
  if ((arg_ref <=0)) {
    return -(1);
  }
  (void)((param_ty = param_ty_raw));
  if ((from_dep_index >=0)) {
    (void)((param_ty = get_dep_return_type_in_caller_arena(from_dep_index, param_ty_raw, caller_arena, ctx)));
    if ((param_ty ==0)) {
      return -(1);
    }
  }
  if ((param_ty <=0)) {
    return -(1);
  }
  (void)((arg_ty = pipeline_expr_resolved_type_ref(caller_arena, arg_ref)));
  if (((arg_ty > 0) && (pipeline_typeck_type_refs_equal_c(caller_arena, arg_ty, param_ty) !=0))) {
    return 1000;
  }
  if ((pipeline_expr_kind_ord_at(caller_arena, arg_ref) ==ord_as)) {
    (void)((as_tgt = pipeline_expr_as_target_type_ref_at(caller_arena, arg_ref)));
    if (((as_tgt > 0) && (pipeline_typeck_type_refs_equal_c(caller_arena, as_tgt, param_ty) !=0))) {
      return 1000;
    }
  }
  if ((pipeline_expr_kind_ord_at(caller_arena, arg_ref) ==0)) {
    int32_t pk_lit = pipeline_type_kind_ord_at(caller_arena, param_ty);
    /* wave670: keyword null only scores for TYPE_PTR. Bare INT 0 keeps integer+ptr. */
    if ((typeck_expr_is_null_keyword(caller_arena, arg_ref) != 0)) {
      if ((pk_lit == 9))
        return 100;
      return -1;
    }
    if ((((((((pk_lit ==0) || (pk_lit ==2)) || (pk_lit ==3)) || (pk_lit ==4)) || (pk_lit ==5)) || (pk_lit ==6)) || (pk_lit ==7))) {
      return 100;
    }
    /* wave668 Cap residual: bare EXPR_LIT 0 → TYPE_PTR. G.7 ≡ typeck.x. */
    if (((pk_lit ==9) && (pipeline_expr_int_val_at(caller_arena, arg_ref) ==0))) {
      return 100;
    }
  }
  /* G.7 ≡ typeck.x: bare FLOAT_LIT / NEG(FLOAT_LIT) weak-match f32/f64. */
  {
    int32_t arg_ko_fl = pipeline_expr_kind_ord_at(caller_arena, arg_ref);
    int32_t fl_inner = arg_ref;
    if (arg_ko_fl == 22) {
      fl_inner = pipeline_expr_unary_operand_ref_at(caller_arena, arg_ref);
      if (fl_inner > 0)
        arg_ko_fl = pipeline_expr_kind_ord_at(caller_arena, fl_inner);
    }
    if (arg_ko_fl == 1) {
      int32_t pk_fl = pipeline_type_kind_ord_at(caller_arena, param_ty);
      if (pk_fl == 14 || pk_fl == 15)
        return 100;
      return -1;
    }
  }
  if ((arg_ty > 0)) {
    int32_t ak = pipeline_type_kind_ord_at(caller_arena, arg_ty);
    int32_t pk = pipeline_type_kind_ord_at(caller_arena, param_ty);
    if (((ak ==10) && (pk ==9))) {
      int32_t ae = pipeline_type_elem_ref_at(caller_arena, arg_ty);
      int32_t pe = pipeline_type_elem_ref_at(caller_arena, param_ty);
      if ((((ae > 0) && (pe > 0)) && (pipeline_typeck_type_refs_equal_c(caller_arena, ae, pe) !=0))) {
        return 1000;
      }
    }
    if (((ak ==9) && (pk ==9))) {
      int32_t ae2 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
      int32_t pe2 = pipeline_type_elem_ref_at(caller_arena, param_ty);
      if ((((ae2 > 0) && (pe2 > 0)) && (pipeline_typeck_type_refs_equal_c(caller_arena, ae2, pe2) !=0))) {
        return 1000;
      }
      return -(1);
    }
    /* wave672: TYPE_ARRAY/SLICE same-kind requires matching elem. */
    if (((ak ==10) && (pk ==10))) {
      int32_t ae_a = pipeline_type_elem_ref_at(caller_arena, arg_ty);
      int32_t pe_a = pipeline_type_elem_ref_at(caller_arena, param_ty);
      int32_t asz = pipeline_type_array_size_at(caller_arena, arg_ty);
      int32_t psz = pipeline_type_array_size_at(caller_arena, param_ty);
      if ((((ae_a > 0) && (pe_a > 0)) && (pipeline_typeck_type_refs_equal_c(caller_arena, ae_a, pe_a) !=0))
          && (((asz <=0) || (psz <=0)) || (asz ==psz))) {
        return 1000;
      }
      return -(1);
    }
    if (((ak ==11) && (pk ==11))) {
      int32_t ae_s = pipeline_type_elem_ref_at(caller_arena, arg_ty);
      int32_t pe_s = pipeline_type_elem_ref_at(caller_arena, param_ty);
      if ((((ae_s > 0) && (pe_s > 0)) && (pipeline_typeck_type_refs_equal_c(caller_arena, ae_s, pe_s) !=0))) {
        return 1000;
      }
      return -(1);
    }
    if (((ak ==pk) && (ak !=0))) {
      return 1;
    }
    return -(1);
  }
  return -(1);
}
int32_t find_func_return_type_in_module_by_name_overload(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  int32_t j = 0;
  int32_t num_args = 0;
  int32_t best_idx = -(1);
  int32_t best_score = -(1);
  int32_t best_ret = 0;
  int32_t first_idx = -(1);
  int32_t first_ret = 0;
  if ((((name_len <=0) || (name_len > 127)) || (mod ==((struct ast_Module *)(0))))) {
    return 0;
  }
  if ((((call_expr_ref <=0) || (caller_arena ==((struct ast_ASTArena *)(0)))) || (call_expr_ref > (caller_arena->num_exprs)))) {
    return find_func_return_type_in_module_by_name(mod, caller_arena, name, name_len, from_dep_index, ctx, func_index_out);
  }
  (void)((num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref)));
  while ((j < (mod->num_funcs))) {
    if ((pipeline_module_func_name_equal_at(mod, j, name, name_len) !=0)) {
      int32_t rtr = pipeline_module_func_return_type_at(mod, j);
      if ((first_idx < 0)) {
        (void)((first_idx = j));
        (void)((first_ret = rtr));
      }
      int32_t nparams = pipeline_module_func_num_params_at(mod, j);
      if ((nparams ==num_args)) {
        int32_t ai = 0;
        int32_t score = 0;
        int32_t matched = 1;
        while ((ai < num_args)) {
          int32_t param_raw = pipeline_module_func_param_type_ref_at(mod, j, ai);
          int32_t sc = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw, from_dep_index, ctx);
          if ((sc < 0)) {
            (void)((matched = 0));
            break;
          }
          (void)((score = (score + sc)));
          (void)((ai = (ai + 1)));
        }
        if (((matched !=0) && (score > best_score))) {
          (void)((best_score = score));
          (void)((best_idx = j));
          (void)((best_ret = rtr));
        }
      }
    }
    (void)((j = (j + 1)));
  }
  if ((best_idx >=0)) {
    if ((func_index_out !=((int32_t *)(0)))) {
      (void)(((func_index_out)[0] = best_idx));
    }
    if ((from_dep_index < 0)) {
      return best_ret;
    }
    return get_dep_return_type_in_caller_arena(from_dep_index, best_ret, caller_arena, ctx);
  }
  /* wave660: pure arity miss → no first_idx bind (G.7 ≡ typeck.x by_name_overload). */
  if ((first_idx >=0)) {
    int32_t any_arity = 0;
    int32_t j2 = 0;
    while ((j2 < (mod->num_funcs))) {
      if ((pipeline_module_func_name_equal_at(mod, j2, name, name_len) !=0)) {
        if ((pipeline_module_func_num_params_at(mod, j2) ==num_args)) {
          (void)((any_arity = 1));
          break;
        }
      }
      (void)((j2 = (j2 + 1)));
    }
    if ((any_arity ==0)) {
      return 0;
    }
    if ((func_index_out !=((int32_t *)(0)))) {
      (void)(((func_index_out)[0] = first_idx));
    }
    if ((from_dep_index < 0)) {
      return first_ret;
    }
    return get_dep_return_type_in_caller_arena(from_dep_index, first_ret, caller_arena, ctx);
  }
  return 0;
}
int32_t find_func_return_type_in_module_overload(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  int32_t j = 0;
  int32_t first_idx = -(1);
  int32_t first_ret = 0;
  int32_t num_args = 0;
  int32_t has_call_info = 0;
  int32_t best_idx = -(1);
  int32_t best_score = -(1);
  int32_t best_ret = 0;
  if (((call_expr_ref > 0) && (call_expr_ref <=(caller_arena->num_exprs)))) {
    (void)((num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref)));
    (void)((has_call_info = 1));
  }
  while ((j < (mod->num_funcs))) {
    if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
      if ((first_idx < 0)) {
        (void)((first_idx = j));
        (void)((first_ret = pipeline_module_func_return_type_at(mod, j)));
      }
      if ((has_call_info !=0)) {
        int32_t nparams = pipeline_module_func_num_params_at(mod, j);
        if ((nparams ==num_args)) {
          int32_t ai = 0;
          int32_t score = 0;
          int32_t matched = 1;
          while ((ai < num_args)) {
            int32_t param_raw = pipeline_module_func_param_type_ref_at(mod, j, ai);
            int32_t sc = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw, from_dep_index, ctx);
            if ((sc < 0)) {
              (void)((matched = 0));
              break;
            }
            (void)((score = (score + sc)));
            (void)((ai = (ai + 1)));
          }
          if (((matched !=0) && (score > best_score))) {
            (void)((best_score = score));
            (void)((best_idx = j));
            (void)((best_ret = pipeline_module_func_return_type_at(mod, j)));
          }
        }
      }
    }
    (void)((j = (j + 1)));
  }
  if ((best_idx >=0)) {
    if ((func_index_out !=((int32_t *)(0)))) {
      (void)(((func_index_out)[0] = best_idx));
    }
    if ((from_dep_index < 0)) {
      return best_ret;
    }
    return get_dep_return_type_in_caller_arena(from_dep_index, best_ret, caller_arena, ctx);
  }
  /* wave660: pure arity miss → no first_idx bind (G.7 ≡ typeck.x module_overload). */
  if ((first_idx >=0)) {
    if ((has_call_info !=0)) {
      int32_t any_arity2 = 0;
      int32_t j3 = 0;
      while ((j3 < (mod->num_funcs))) {
        if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j3)) {
          if ((pipeline_module_func_num_params_at(mod, j3) ==num_args)) {
            (void)((any_arity2 = 1));
            break;
          }
        }
        (void)((j3 = (j3 + 1)));
      }
      if ((any_arity2 ==0)) {
        return 0;
      }
    }
    if ((func_index_out !=((int32_t *)(0)))) {
      (void)(((func_index_out)[0] = first_idx));
    }
    if ((from_dep_index < 0)) {
      return first_ret;
    }
    return get_dep_return_type_in_caller_arena(from_dep_index, first_ret, caller_arena, ctx);
  }
  return 0;
}
int32_t typeck_import_path_segment_count(uint8_t * path, int32_t path_len) {
  if (((path_len <=0) || (path ==((uint8_t *)(0))))) {
    return 0;
  }
  int32_t n = 1;
  int32_t ii = 0;
  while ((ii < path_len)) {
    uint8_t ch_u8 = (path)[ii];
    if ((ch_u8 ==46)) {
      (void)((n = (n + 1)));
    }
    (void)((ii = (ii + 1)));
  }
  return n;
}
int typeck_import_segment_at(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen) {
  if ((((module ==((struct ast_Module *)(0))) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
    return 0;
  }
  int32_t pl = pipeline_module_import_path_len(module, imp_ix);
  if (((pl <=0) || (pl > 63))) {
    return 0;
  }
  int32_t ci = 0;
  int32_t ss = 0;
  int32_t k = 0;
  while ((k <=pl)) {
    int at_end_p = (k ==pl);
    int dot_p = 0;
    if ((!(at_end_p) && (k < pl))) {
      (void)((dot_p = (pipeline_module_import_path_byte_at(module, imp_ix, k) ==46)));
    }
    if ((at_end_p || dot_p)) {
      int32_t seg_len_here = (k - ss);
      if ((seg_len_here <=0)) {
        return 0;
      }
      if ((ci ==want_seg)) {
        (void)(((ostr)[0] = ss));
        (void)(((olen)[0] = seg_len_here));
        return 1;
      }
      if (dot_p) {
        (void)((ss = (k + 1)));
      }
      (void)((ci = (ci + 1)));
    }
    (void)((k = (k + 1)));
  }
  return 0;
}
int32_t resolve_whole_import_qualified_call_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  int32_t ord_field = 44;
  int32_t ord_var = 3;
  if ((ctx ==((struct ast_PipelineDepCtx *)(0)))) {
    return 0;
  }
  if ((((callee_expr_ref <=0) || (callee_expr_ref > (arena->num_exprs))) || (module ==((struct ast_Module *)(0))))) {
    return 0;
  }
  if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=ord_field)) {
    return 0;
  }
  uint8_t layer_buf[128] = {};
  (void)(asm_qual_sym_layer_reset());
  int32_t nstack = 0;
  int32_t cur_ref = callee_expr_ref;
  while (1) {
    int32_t falen = pipeline_expr_field_access_name_len(arena, cur_ref);
    if (((cur_ref <=0) || (cur_ref > (arena->num_exprs)))) {
      return 0;
    }
    if ((((pipeline_expr_kind_ord_at(arena, cur_ref) !=ord_field) || (falen <=0)) || (falen > 63))) {
      break;
    }
    (void)(pipeline_expr_field_access_name_into(arena, cur_ref, &((layer_buf)[0])));
    if ((asm_qual_sym_layer_push(&((layer_buf)[0]), falen) < 0)) {
      return 0;
    }
    (void)((nstack = (nstack + 1)));
    (void)((cur_ref = pipeline_expr_field_access_base_ref(arena, cur_ref)));
  }
  (void)((nstack = asm_qual_sym_layer_count()));
  if (((cur_ref <=0) || (cur_ref > (arena->num_exprs)))) {
    return 0;
  }
  int32_t vnlen = pipeline_expr_var_name_len(arena, cur_ref);
  if ((((pipeline_expr_kind_ord_at(arena, cur_ref) !=ord_var) || (vnlen <=0)) || (vnlen > 127))) {
    return 0;
  }
  uint8_t vname_buf[128] = {};
  (void)(pipeline_expr_var_name_into(arena, cur_ref, &((vname_buf)[0])));
  int32_t dep_j = 0;
  int32_t n_imp = typeck_module_num_imports(module);
  while ((dep_j < n_imp)) {
    int32_t plen = pipeline_module_import_path_len(module, dep_j);
    if (((plen <=0) || (plen > 63))) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    uint8_t path_cnt_buf[128] = {};
    int32_t pci = 0;
    while (((pci < plen) && (pci < 64))) {
      (void)(((path_cnt_buf)[pci] = pipeline_module_import_path_byte_at(module, dep_j, pci)));
      (void)((pci = (pci + 1)));
    }
    int32_t Pseg = typeck_import_path_segment_count(&((path_cnt_buf)[0]), plen);
    if (((Pseg <=0) || (nstack !=Pseg))) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    int32_t s0_rel = 0;
    int32_t s0_ln = 0;
    if (!(typeck_import_segment_at(module, dep_j, 0, &(s0_rel), &(s0_ln)))) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    if (!(typeck_import_path_slice_equal(module, dep_j, s0_rel, s0_ln, &((vname_buf)[0]), vnlen))) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    int bad_mid = 0;
    int32_t sm = 1;
    while ((sm <=(Pseg - 1))) {
      int32_t srv = 0;
      int32_t slv = 0;
      if (!(typeck_import_segment_at(module, dep_j, sm, &(srv), &(slv)))) {
        (void)((bad_mid = 1));
      } else {
        int32_t lay_ix = (Pseg - sm);
        (void)(asm_qual_sym_layer_copy(lay_ix, &((layer_buf)[0]), 64));
        if (!(typeck_import_path_slice_equal(module, dep_j, srv, slv, &((layer_buf)[0]), asm_qual_sym_layer_len(lay_ix)))) {
          (void)((bad_mid = 1));
        }
      }
      if (bad_mid) {
        break;
      }
      (void)((sm = (sm + 1)));
    }
    if (bad_mid) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, dep_j);
    struct ast_Module * dm = ((struct ast_Module *)(0));
    if ((dep_slot < 0)) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
    if ((dm ==((struct ast_Module *)(0)))) {
      (void)((dep_j = (dep_j + 1)));
      continue;
    }
    (void)(asm_qual_sym_layer_copy(0, &((layer_buf)[0]), 64));
    int32_t ret_fn = find_func_return_type_in_module_by_name(dm, arena, &((layer_buf)[0]), asm_qual_sym_layer_len(0), dep_slot, ctx, func_index_out);
    if ((ret_fn !=0)) {
      if ((dep_index_out !=((int32_t *)(0)))) {
        (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
      }
    }
    return ret_fn;
  }
  return 0;
}
int32_t resolve_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  int32_t ord_field = 44;
  int32_t ord_var = 3;
  int32_t ord_import_binding = 1;
  int32_t base_bind_ref = 0;
  int32_t base_bind_len = 0;
  int32_t field_len = 0;
  int32_t ii = 0;
  int32_t ret_b = 0;
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t import_kind = 0;
  uint8_t base_bind_nm[128] = {};
  uint8_t field_nm[128] = {};
  if (((((callee_expr_ref <=0) || (callee_expr_ref > (arena->num_exprs))) || (module ==((struct ast_Module *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return 0;
  }
  if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=ord_field)) {
    return 0;
  }
  (void)((base_bind_ref = pipeline_expr_field_access_base_ref(arena, callee_expr_ref)));
  if (((base_bind_ref <=0) || (base_bind_ref > (arena->num_exprs)))) {
    return 0;
  }
  if ((pipeline_expr_kind_ord_at(arena, base_bind_ref) !=ord_var)) {
    return 0;
  }
  (void)((base_bind_len = pipeline_expr_var_name_len(arena, base_bind_ref)));
  if (((base_bind_len <=0) || (base_bind_len > 127))) {
    return 0;
  }
  (void)(pipeline_expr_var_name_into(arena, base_bind_ref, &((base_bind_nm)[0])));
  (void)((field_len = pipeline_expr_field_access_name_len(arena, callee_expr_ref)));
  (void)(pipeline_expr_field_access_name_into(arena, callee_expr_ref, &((field_nm)[0])));
  (void)((ii = 0));
  int32_t n_imp = typeck_module_num_imports(module);
  while ((ii < n_imp)) {
    (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
    if (((import_kind ==ord_import_binding) && typeck_import_binding_name_equal(module, ii, &((base_bind_nm)[0]), base_bind_len))) {
      int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii);
      if ((dep_slot < 0)) {
        break;
      }
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
      if ((dm !=((struct ast_Module *)(0)))) {
        (void)((ret_b = find_func_return_type_in_module_by_name_overload(dm, arena, &((field_nm)[0]), field_len, call_expr_ref, dep_slot, ctx, func_index_out)));
        if ((ret_b !=0)) {
          if ((dep_index_out !=((int32_t *)(0)))) {
            (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
          }
          return ret_b;
        }
      }
      break;
    }
    (void)((ii = (ii + 1)));
  }
  return 0;
}
int32_t resolve_method_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  int32_t ord_var = 3;
  int32_t ord_import_binding = 1;
  int32_t base_ref = 0;
  int32_t base_len = 0;
  int32_t method_len = 0;
  int32_t ii = 0;
  int32_t ret_b = 0;
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t import_kind = 0;
  uint8_t base_nm[128] = {};
  uint8_t method_nm[128] = {};
  if (((((expr_ref <=0) || (expr_ref > (arena->num_exprs))) || (module ==((struct ast_Module *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return 0;
  }
  (void)((base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref)));
  if (((base_ref <=0) || (base_ref > (arena->num_exprs)))) {
    return 0;
  }
  if ((pipeline_expr_kind_ord_at(arena, base_ref) !=ord_var)) {
    return 0;
  }
  (void)((base_len = pipeline_expr_var_name_len(arena, base_ref)));
  (void)((method_len = pipeline_expr_method_call_name_len(arena, expr_ref)));
  if (((((base_len <=0) || (base_len > 63)) || (method_len <=0)) || (method_len > 63))) {
    return 0;
  }
  (void)(pipeline_expr_var_name_into(arena, base_ref, &((base_nm)[0])));
  (void)(pipeline_expr_method_call_name_into(arena, expr_ref, &((method_nm)[0])));
  int32_t n_imp = typeck_module_num_imports(module);
  while ((ii < n_imp)) {
    (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
    if (((import_kind ==ord_import_binding) && typeck_import_binding_name_equal(module, ii, &((base_nm)[0]), base_len))) {
      int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii);
      if ((dep_slot < 0)) {
        break;
      }
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
      if ((dm !=((struct ast_Module *)(0)))) {
        (void)((ret_b = find_func_return_type_in_module_by_name(dm, arena, &((method_nm)[0]), method_len, dep_slot, ctx, func_index_out)));
        if ((ret_b !=0)) {
          if ((dep_index_out !=((int32_t *)(0)))) {
            (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
          }
          return ret_b;
        }
      }
      break;
    }
    (void)((ii = (ii + 1)));
  }
  return 0;
}
int32_t resolve_call_select_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  int32_t ord_var = 3;
  int32_t ord_import_select = 2;
  int32_t cv_len = 0;
  int32_t k = 0;
  int32_t sel_cnt = 0;
  int32_t import_kind = 0;
  struct ast_Module * dm = ((struct ast_Module *)(0));
  uint8_t cv_nm[128] = {};
  if (((module ==((struct ast_Module *)(0))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return 0;
  }
  if ((((dep_ix < 0) || (dep_ix >=typeck_module_num_imports(module))) || (callee_ord !=ord_var))) {
    return 0;
  }
  (void)((import_kind = pipeline_module_import_kind_at(module, dep_ix)));
  if ((import_kind !=ord_import_select)) {
    return 0;
  }
  (void)((cv_len = pipeline_expr_var_name_len(arena, callee_expr_ref)));
  if ((cv_len <=0)) {
    return 0;
  }
  (void)(pipeline_expr_var_name_into(arena, callee_expr_ref, &((cv_nm)[0])));
  int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, dep_ix);
  if ((dep_slot < 0)) {
    return 0;
  }
  (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
  if ((dm ==((struct ast_Module *)(0)))) {
    return 0;
  }
  (void)((sel_cnt = pipeline_module_import_select_count_at(module, dep_ix)));
  (void)((k = 0));
  while ((k < sel_cnt)) {
    if (typeck_import_select_name_equal(module, dep_ix, k, &((cv_nm)[0]), cv_len)) {
      return find_func_return_type_in_module_by_name(dm, arena, &((cv_nm)[0]), cv_len, dep_slot, ctx, func_index_out);
    }
    (void)((k = (k + 1)));
  }
  return 0;
}
int32_t resolve_call_callee_try_whole_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord) {
  int32_t ord_field = 44;
  int32_t * null_po = ((int32_t *)(0));
  if ((callee_ord !=ord_field)) {
    return 0;
  }
  return resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx, null_po, null_po);
}
int32_t resolve_call_callee_try_binding_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord) {
  int32_t ord_field = 44;
  int32_t * null_po = ((int32_t *)(0));
  if ((callee_ord !=ord_field)) {
    return 0;
  }
  return resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx, null_po, null_po);
}
int32_t resolve_call_callee_local_module(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t minus_one = -(1);
  return find_func_return_type_in_module(module, arena, arena, arena, callee_expr_ref, minus_one, ctx, ((int32_t *)(0)));
}
int32_t resolve_call_callee_scan_dep(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax) {
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t ret = 0;
  int32_t * null_po = ((int32_t *)(0));
  if ((dep_i >=imax)) {
    return 0;
  }
  (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_i)));
  if ((dm !=((struct ast_Module *)(0)))) {
    (void)((ret = find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx, null_po)));
    if ((ret !=0)) {
      return ret;
    }
    if ((dep_i < typeck_module_num_imports(module))) {
      (void)((ret = resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord, dep_i, ctx, null_po)));
      if ((ret !=0)) {
        return ret;
      }
    }
  }
  return resolve_call_callee_scan_dep(module, arena, callee_expr_ref, callee_ord, ctx, (dep_i + 1), imax);
}
int32_t resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t want_apply = 0;
  int32_t callee_ord = 0;
  int32_t ret = 0;
  int32_t imax = 0;
  int32_t nd_scan = 0;
  if (((callee_expr_ref <=0) || (callee_expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  if (((call_expr_ref > 0) && (call_expr_ref <=(arena->num_exprs)))) {
    (void)((want_apply = 1));
  }
  (void)((callee_ord = pipeline_expr_kind_ord_at(arena, callee_expr_ref)));
  (void)((ret = resolve_call_callee_try_whole_import(module, arena, callee_expr_ref, ctx, callee_ord)));
  if ((ret !=0)) {
    if ((want_apply !=0)) {
      (void)(typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0));
      (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
      (void)(resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx, typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot()));
      (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(), typeck_call_resolve_func_idx_peek()));
    }
    return ret;
  }
  (void)((ret = resolve_call_callee_try_binding_import(module, arena, callee_expr_ref, call_expr_ref, ctx, callee_ord)));
  if ((ret !=0)) {
    if ((want_apply !=0)) {
      (void)(typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0));
      (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
      (void)((ret = resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx, typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot())));
      (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(), typeck_call_resolve_func_idx_peek()));
    }
    return ret;
  }
  (void)((ret = resolve_call_callee_local_module(module, arena, callee_expr_ref, ctx)));
  if ((ret !=0)) {
    if ((want_apply !=0)) {
      int32_t minus_one_lm = -(1);
      (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
      (void)((ret = find_func_return_type_in_module_overload(module, arena, arena, arena, callee_expr_ref, call_expr_ref, minus_one_lm, ctx, typeck_call_resolve_func_idx_slot())));
      (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, minus_one_lm, typeck_call_resolve_func_idx_peek()));
    }
    return ret;
  }
  (void)((imax = typeck_module_num_imports(module)));
  (void)((nd_scan = pipeline_dep_ctx_ndep(ctx)));
  if ((nd_scan > imax)) {
    (void)((imax = nd_scan));
  }
  return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord, call_expr_ref, ctx, 0, imax, want_apply);
}
int32_t expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref) {
  if (ast_ref_is_null(expr_ref)) {
    return 0;
  }
  if (((expr_ref <=0) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  return pipeline_expr_resolved_type_ref(arena, expr_ref);
}
int type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref) {
  int32_t ord_bool = 1;
  return (pipeline_type_kind_ord_at(arena, type_ref) ==ord_bool);
}
int type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref) {
  if (ast_ref_is_null(type_ref)) {
    return 0;
  }
  if (((type_ref <=0) || (type_ref > (arena->num_types)))) {
    return 0;
  }
  return type_ref_is_bool_impl(arena, type_ref);
}
int32_t typeck_named_unqual_start(uint8_t * buf, int32_t len) {
  int32_t i = (len - 1);
  while ((i > 0)) {
    if (((buf)[i] ==46)) {
      return (i + 1);
    }
    (void)((i = (i - 1)));
  }
  return 0;
}
int type_refs_equal_named(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  uint8_t * buf_a = typeck_scratch64_slot(0);
  uint8_t * buf_b = typeck_scratch64_slot(1);
  int32_t na = pipeline_type_named_name_into(arena, a, buf_a);
  int32_t nb = pipeline_type_named_name_into(arena, b, buf_b);
  int32_t i = 0;
  int32_t ta = 0;
  int32_t tb = 0;
  int32_t ua = 0;
  int32_t ub = 0;
  if (((na <=0) || (nb <=0))) {
    return 0;
  }
  if ((na ==nb)) {
    (void)((i = 0));
    while ((i < na)) {
      if (((buf_a)[i] !=(buf_b)[i])) {
        break;
      }
      (void)((i = (i + 1)));
    }
    if ((i ==na)) {
      return 1;
    }
  }
  (void)((ta = typeck_named_unqual_start(buf_a, na)));
  (void)((tb = typeck_named_unqual_start(buf_b, nb)));
  (void)((ua = (na - ta)));
  (void)((ub = (nb - tb)));
  if (((ua !=ub) || (ua <=0))) {
    return 0;
  }
  (void)((i = 0));
  while ((i < ua)) {
    if (((buf_a)[(ta + i)] !=(buf_b)[(tb + i)])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int type_refs_equal_same_kind(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord) {
  int32_t ea = 0;
  int32_t eb = 0;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_array = 10;
  int32_t ord_slice = 11;
  int32_t ord_linear = 12;
  int32_t ord_vector = 13;
  if ((kind_ord ==ord_named)) {
    return type_refs_equal_named(arena, a, b);
  }
  if ((((kind_ord ==ord_ptr) || (kind_ord ==ord_slice)) || (kind_ord ==ord_linear))) {
    (void)((ea = pipeline_type_elem_ref_at(arena, a)));
    (void)((eb = pipeline_type_elem_ref_at(arena, b)));
    return type_refs_equal(arena, ea, eb);
  }
  if (((kind_ord ==ord_array) || (kind_ord ==ord_vector))) {
    if ((pipeline_type_array_size_at(arena, a) !=pipeline_type_array_size_at(arena, b))) {
      return 0;
    }
    (void)((ea = pipeline_type_elem_ref_at(arena, a)));
    (void)((eb = pipeline_type_elem_ref_at(arena, b)));
    return type_refs_equal(arena, ea, eb);
  }
  return 1;
}
int type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  int32_t ka = pipeline_type_kind_ord_at(arena, a);
  int32_t kb = pipeline_type_kind_ord_at(arena, b);
  if ((ka !=kb)) {
    return 0;
  }
  return type_refs_equal_same_kind(arena, a, b, ka);
}
int type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  if ((ast_ref_is_null(a) || ast_ref_is_null(b))) {
    return (a ==b);
  }
  return (pipeline_typeck_type_refs_equal_c(arena, a, b) !=0);
}
/* wave309 Cap residual: TYPE_ISIZE identity + i32→isize (align glue / typeck.x).
 * wave312: u8→i64/isize; u32→i64/usize/isize; isize↔i64; usize↔u64. */
int typeck_integer_widen_ok(int32_t dest_kind, int32_t src_kind) {
  int32_t ord_i32 = 0;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  if ((dest_kind ==src_kind)) {
    if ((((((((dest_kind ==ord_i32) || (dest_kind ==ord_i64)) || (dest_kind ==ord_u8)) || (dest_kind ==ord_u32)) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize))) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_u8)) {
    /* wave312: u8→i64/isize (plus prior u32/u64/usize/i32). */
    if ((((((dest_kind ==ord_u32) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_i32)) || (dest_kind ==ord_i64)) || (dest_kind ==ord_isize)) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_i32)) {
    /* wave311: i32→u64 true widen + i32→u8 low-byte narrow; G.7 mirror typeck.x. */
    if ((((((dest_kind ==ord_i64) || (dest_kind ==ord_u32)) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize)) || (dest_kind ==ord_u8)) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_u32)) {
    /* wave312: u32→u64 (prior) + u32→i64/usize/isize. */
    if (((((dest_kind ==ord_u64) || (dest_kind ==ord_i64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize))) {
      return 1;
    }
    return 0;
  }
  /* wave312: LP64 pointer-width ↔ fixed 64-bit. */
  if (((src_kind ==ord_usize) && (dest_kind ==ord_u64))) {
    return 1;
  }
  if (((src_kind ==ord_u64) && (dest_kind ==ord_usize))) {
    return 1;
  }
  if (((src_kind ==ord_isize) && (dest_kind ==ord_i64))) {
    return 1;
  }
  if (((src_kind ==ord_i64) && (dest_kind ==ord_isize))) {
    return 1;
  }
  return 0;
}

/* wave313: family id for first-class ints + NAMED i8/i16/u16. G.7 ≡ typeck.x. */
int typeck_int_family_id(struct ast_ASTArena * arena, int32_t type_ref) {
  int32_t k;
  int32_t nlen;
  uint8_t * buf;
  if (ast_ref_is_null(type_ref) || type_ref <= 0) {
    return -1;
  }
  k = pipeline_type_kind_ord_at(arena, type_ref);
  if (k == 0 || k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7) {
    return k;
  }
  if (k != 8) {
    return -1;
  }
  buf = typeck_scratch64_slot(15);
  nlen = pipeline_type_named_name_into(arena, type_ref, buf);
  /* "i8" */
  if (nlen == 2 && buf[0] == 105 && buf[1] == 56) {
    return 10;
  }
  /* "i16" */
  if (nlen == 3 && buf[0] == 105 && buf[1] == 49 && buf[2] == 54) {
    return 11;
  }
  /* "u16" */
  if (nlen == 3 && buf[0] == 117 && buf[1] == 49 && buf[2] == 54) {
    return 12;
  }
  return -1;
}
/* wave313: refs-based integer widen (first-class + NAMED i8/i16/u16). G.7 ≡ typeck.x. */
int typeck_integer_widen_ok_refs(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref) {
  int32_t dest_f;
  int32_t src_f;
  if (ast_ref_is_null(dest_ref) || ast_ref_is_null(src_ref)) {
    return 0;
  }
  dest_f = typeck_int_family_id(arena, dest_ref);
  src_f = typeck_int_family_id(arena, src_ref);
  if (dest_f < 0 || src_f < 0) {
    return 0;
  }
  if (dest_f == src_f) {
    return 1;
  }
  if (dest_f <= 7 && src_f <= 7) {
    if (typeck_integer_widen_ok(dest_f, src_f)) {
      return 1;
    }
  }
  if (src_f == 10) {
    if (dest_f == 11 || dest_f == 12 || dest_f == 2 || dest_f == 0 || dest_f == 3 ||
        dest_f == 4 || dest_f == 5 || dest_f == 6 || dest_f == 7) {
      return 1;
    }
    return 0;
  }
  if (src_f == 11) {
    if (dest_f == 12 || dest_f == 2 || dest_f == 0 || dest_f == 3 || dest_f == 4 ||
        dest_f == 5 || dest_f == 6 || dest_f == 7) {
      return 1;
    }
    return 0;
  }
  if (src_f == 12) {
    if (dest_f == 2 || dest_f == 0 || dest_f == 3 || dest_f == 4 || dest_f == 5 ||
        dest_f == 6 || dest_f == 7) {
      return 1;
    }
    return 0;
  }
  if (dest_f == 10) {
    if (src_f == 2 || src_f == 0 || src_f == 11 || src_f == 12) {
      return 1;
    }
    return 0;
  }
  if (dest_f == 11) {
    if (src_f == 2 || src_f == 0 || src_f == 12 || src_f == 3) {
      return 1;
    }
    return 0;
  }
  if (dest_f == 12) {
    if (src_f == 2 || src_f == 0 || src_f == 11 || src_f == 3) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/* wave314 Cap residual pure: f32→f64 IEEE float widen. G.7 ≡ typeck.x. */
int typeck_float_widen_ok(int32_t dest_kind, int32_t src_kind) {
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  if ((dest_kind == src_kind)) {
    if (((dest_kind == ord_f32) || (dest_kind == ord_f64))) {
      return 1;
    }
    return 0;
  }
  if (((src_kind == ord_f32) && (dest_kind == ord_f64))) {
    return 1;
  }
  return 0;
}

/* wave671 Cap residual: G.7 ≡ typeck.x — no BOOL_LIT/LOGNOT → i32 return.
 * module is live typeck module (TYPE_FN return recover); unused here — empty
 * surface has no typeck_fnptr_surface_compat. PLATFORM: SHARED signature twin. */
int typeck_return_operand_matches(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  (void)module;
  int32_t got = expr_type_ref(arena, op_ref);
  int32_t expect_kind = 0;
  int32_t got_kind = 0;
  if ((ast_ref_is_null(op_ref) || ast_ref_is_null(expect_ref))) {
    return 1;
  }
  if (ast_ref_is_null(got)) {
    int32_t ord_lit = 0;
    int32_t ord_ptr = 9;
    int32_t kop = pipeline_expr_kind_ord_at(arena, op_ref);
    (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
    if ((((kop ==ord_lit) && (expect_kind ==ord_ptr)) && (pipeline_expr_int_val_at(arena, op_ref) ==0))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
      return 1;
    }
    return 0;
  }
  if (type_refs_equal(arena, got, expect_ref)) {
    return 1;
  }
  (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
  (void)((got_kind = pipeline_type_kind_ord_at(arena, got)));
  if (typeck_integer_widen_ok_refs(arena, expect_ref, got)) {
      return 1;
  }
  /* wave314: f32→f64 on return. */
  if (typeck_float_widen_ok(expect_kind, got_kind)) {
    return 1;
  }
  int32_t ord_linear = 12;
  if ((pipeline_type_kind_ord_at(arena, got) ==ord_linear)) {
    int32_t elem = pipeline_type_elem_ref_at(arena, got);
    if ((!(ast_ref_is_null(elem)) && type_refs_equal(arena, elem, expect_ref))) {
      return 1;
    }
  }
  /* wave671: bool → non-bool return hard-fail. */
  return 0;
}
/* wave670 Cap residual: keyword null — G.7 ≡ typeck.x → pipeline_expr_is_null_keyword_c. */
extern int32_t pipeline_expr_is_null_keyword_c(struct ast_ASTArena * arena, int32_t expr_ref);
int32_t typeck_expr_is_null_keyword(struct ast_ASTArena * arena, int32_t expr_ref) {
  if ((((arena == 0) || (expr_ref <= 0))))
    return 0;
  return pipeline_expr_is_null_keyword_c(arena, expr_ref);
}
/* wave307 Cap residual pure: full i64 lit coerce for u64/usize. */
int32_t typeck_coerce_init_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int64_t int_val = 0;
  int32_t ord_expr_lit = 0;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_array = 10;
  int32_t ord_vector = 13;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  if ((init_kind !=ord_expr_lit)) {
    return 0;
  }
  (void)((int_val = pipeline_expr_int64_val_at(arena, init_ref)));
  /* wave670: keyword null only → TYPE_PTR. Bare INT 0 keeps integer/float coerce. */
  if ((typeck_expr_is_null_keyword(arena, init_ref) != 0)) {
    if ((decl_kind == ord_ptr)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    return 0;
  }
  if (((decl_kind ==ord_ptr) && (int_val ==0))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if (((decl_kind ==ord_array) && (int_val ==0))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((((decl_kind ==ord_u8) && (int_val >=0)) && (int_val <=255))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((decl_kind ==ord_i64)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((decl_kind ==ord_isize)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((decl_kind ==ord_u32)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  /* wave307: any bare EXPR_LIT bit pattern for u64/usize. */
  if (((decl_kind ==ord_usize) || (decl_kind ==ord_u64))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((decl_kind ==ord_named)) {
    uint8_t nm16[128] = {};
    int32_t nlen16 = pipeline_type_named_name_into(arena, decl_ty_ref, &((nm16)[0]));
    if (((((((nlen16 ==3) && ((nm16)[0] ==117)) && ((nm16)[1] ==49)) && ((nm16)[2] ==54)) && (int_val >=0)) && (int_val <=65535))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if (((((((nlen16 ==3) && ((nm16)[0] ==105)) && ((nm16)[1] ==49)) && ((nm16)[2] ==54)) && (int_val >=-(32768))) && (int_val <=32767))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
  }
  /* Integer literal → f32/f64 (incl. non-zero); align typeck.x + run-float. */
  if (((decl_kind ==ord_f32) || (decl_kind ==ord_f64))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if (((int_val ==0) && ((decl_kind ==ord_named) || (decl_kind ==ord_vector)))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  return 0;
}
/* wave316 Cap residual: bare FLOAT_LIT + EXPR_NEG of FLOAT_LIT → f32/f64.
 * PLATFORM: SHARED — mirror typeck.x + pipeline_glue float_lit coerce (G.7). */
int32_t typeck_coerce_init_float_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int32_t ord_expr_float = 1;
  int32_t ord_neg = 22;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t op_ref = 0;
  if (((decl_kind !=ord_f32) && (decl_kind !=ord_f64))) {
    return 0;
  }
  if ((init_kind ==ord_expr_float)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  if ((init_kind ==ord_neg)) {
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, init_ref)));
    if (((!(ast_ref_is_null(op_ref)) && (op_ref > 0)) && (op_ref <=(arena->num_exprs)))) {
      if ((pipeline_expr_kind_ord_at(arena, op_ref) ==ord_expr_float)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, decl_ty_ref));
        (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
        return 1;
      }
    }
  }
  return 0;
}
int32_t typeck_coerce_init_enum_field_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int32_t base_ix = 0;
  int32_t ord_named = 8;
  int32_t ord_expr_var = 3;
  int32_t ord_field_access = 44;
  if (((decl_kind !=ord_named) || (init_kind !=ord_field_access))) {
    return 0;
  }
  (void)((base_ix = pipeline_expr_field_access_base_ref(arena, init_ref)));
  if (((!(ast_ref_is_null(base_ix)) && (base_ix > 0)) && (base_ix <=(arena->num_exprs)))) {
    uint8_t * decl_buf = typeck_scratch64_slot(0);
    uint8_t * vbuf = typeck_scratch64_slot(1);
    uint8_t * field_buf = typeck_scratch64_slot(2);
    int32_t decl_nlen = pipeline_type_named_name_into(arena, decl_ty_ref, decl_buf);
    int32_t vnlen = pipeline_expr_var_name_len(arena, base_ix);
    int32_t i_nm = 0;
    int eq_nm = 1;
    if ((((pipeline_expr_kind_ord_at(arena, base_ix) ==ord_expr_var) && (decl_nlen ==vnlen)) && (decl_nlen > 0))) {
      (void)(pipeline_expr_var_name_into(arena, base_ix, vbuf));
      while ((i_nm < decl_nlen)) {
        if (((decl_buf)[i_nm] !=(vbuf)[i_nm])) {
          (void)((eq_nm = 0));
        }
        (void)((i_nm = (i_nm + 1)));
      }
      if (eq_nm) {
        int32_t field_nlen = pipeline_expr_field_access_name_len(arena, init_ref);
        (void)(pipeline_expr_field_access_name_into(arena, init_ref, field_buf));
        int32_t ev_tag = pipeline_module_enum_variant_tag_for_names(module, decl_buf, decl_nlen, field_buf, field_nlen);
        if ((ev_tag >=0)) {
          (void)(pipeline_expr_set_field_access_enum_variant(arena, init_ref, ev_tag));
          (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
          return 1;
        }
      }
    }
  }
  if ((pipeline_expr_field_access_is_enum_variant(arena, init_ref) !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  return 0;
}
int32_t typeck_coerce_init_named_call_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int32_t ord_type_named = 8;
  int32_t ord_expr_call = 48;
  if ((((decl_kind ==ord_type_named) && (init_kind ==ord_expr_call)) && ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, init_ref)))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  return 0;
}
int32_t typeck_coerce_init_resolved_alias_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  int32_t ord_type_named = 8;
  int32_t init_resolved = 0;
  int32_t decl_resolved = 0;
  if ((decl_kind !=ord_type_named)) {
    return 0;
  }
  (void)((init_resolved = pipeline_expr_resolved_type_ref(arena, init_ref)));
  if (ast_ref_is_null(init_resolved)) {
    return 0;
  }
  (void)((decl_resolved = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0)));
  if (ast_ref_is_null(decl_resolved)) {
    return 0;
  }
  if (!(type_refs_equal(arena, decl_resolved, init_resolved))) {
    return 0;
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
}
int32_t typeck_coerce_array_lit_elem_types_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  int32_t ord_type_array = 10;
  int32_t ord_expr_array_lit = 46;
  int32_t elem_decl_ref = 0;
  int32_t elem_decl_kind = 0;
  int32_t num_elems = 0;
  int32_t i = 0;
  if ((ast_ref_is_null(init_ref) || ast_ref_is_null(decl_ty_ref))) {
    return 0;
  }
  if (((pipeline_expr_kind_ord_at(arena, init_ref) !=ord_expr_array_lit) || (pipeline_type_kind_ord_at(arena, decl_ty_ref) !=ord_type_array))) {
    return 0;
  }
  (void)((elem_decl_ref = pipeline_type_elem_ref_at(arena, decl_ty_ref)));
  if (ast_ref_is_null(elem_decl_ref)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
  (void)((elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl_ref)));
  (void)((num_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref)));
  while ((i < num_elems)) {
    int32_t elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, i);
    int32_t elem_kind = 0;
    int32_t elem_ty = 0;
    if (ast_ref_is_null(elem_ref)) {
      (void)((i = (i + 1)));
      continue;
    }
    (void)((elem_kind = pipeline_expr_kind_ord_at(arena, elem_ref)));
    if (((elem_kind ==ord_expr_array_lit) && (elem_decl_kind ==ord_type_array))) {
      if ((typeck_coerce_array_lit_elem_types_to_decl(module, arena, elem_ref, elem_decl_ref) < 0)) {
        return -(1);
      }
    } else {
      (void)(typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl_ref, elem_decl_kind, elem_kind));
      (void)((elem_ty = expr_type_ref(arena, elem_ref)));
      /* wave672: hard-fail known elem mismatch; do not stamp outer as decl. */
      if (!(ast_ref_is_null(elem_ty)) && (elem_ty > 0)) {
        int32_t got_kind = pipeline_type_kind_ord_at(arena, elem_ty);
        if ((type_refs_equal(arena, elem_ty, elem_decl_ref)
            || typeck_integer_widen_ok_refs(arena, elem_decl_ref, elem_ty)
            || typeck_float_widen_ok(elem_decl_kind, got_kind))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl_ref));
        } else {
          uint8_t *eb = driver_typeck_diag_scratch_expect();
          uint8_t *gb = driver_typeck_diag_scratch_found();
          int32_t el = typeck_diag_fmt_type_into(arena, elem_decl_ref, eb, 96);
          int32_t gl = typeck_diag_fmt_type_into(arena, elem_ty, gb, 96);
          int32_t err_line = pipeline_expr_line_at(arena, elem_ref);
          int32_t err_col = pipeline_expr_col_at(arena, elem_ref);
          driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl);
          return -(1);
        }
      }
    }
    (void)((i = (i + 1)));
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
}
int32_t typeck_vector_lanes_of_type(struct ast_ASTArena * arena, int32_t type_ref) {
  int32_t ord_type_vector = 13;
  int32_t ord_type_named = 8;
  int32_t tk = 0;
  int32_t asz = 0;
  uint8_t nm[128] = {};
  int32_t nlen = 0;
  int32_t i = 0;
  int32_t lanes = 0;
  if ((ast_ref_is_null(type_ref) || (type_ref <=0))) {
    return 0;
  }
  (void)((tk = pipeline_type_kind_ord_at(arena, type_ref)));
  if ((tk ==ord_type_vector)) {
    (void)((asz = pipeline_type_array_size_at(arena, type_ref)));
    if ((asz > 0)) {
      return asz;
    }
    return 0;
  }
  if ((tk !=ord_type_named)) {
    return 0;
  }
  (void)((nlen = pipeline_type_named_name_into(arena, type_ref, &((nm)[0]))));
  (void)((i = 0));
  while ((i < nlen)) {
    if (((nm)[i] ==120)) {
      (void)((i = (i + 1)));
      (void)((lanes = 0));
      while ((((i < nlen) && ((nm)[i] >=48)) && ((nm)[i] <=57))) {
        (void)((lanes = ((lanes * 10) + (((int32_t)((nm)[i])) - 48))));
        (void)((i = (i + 1)));
      }
      if ((((lanes ==4) || (lanes ==8)) || (lanes ==16))) {
        return lanes;
      }
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t typeck_coerce_init_array_vector_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int32_t ord_type_array = 10;
  int32_t ord_type_slice = 11;
  int32_t ord_type_vector = 13;
  int32_t ord_expr_array_lit = 46;
  int32_t lanes = 0;
  int32_t n_elems = 0;
  int32_t elem_decl = 0;
  int32_t elem_decl_kind = 0;
  int32_t i = 0;
  int32_t elem_ref = 0;
  int32_t ek = 0;
  if ((((decl_kind ==ord_type_array) || (decl_kind ==ord_type_slice)) && (init_kind ==ord_expr_array_lit))) {
    return typeck_coerce_array_lit_elem_types_to_decl(module, arena, init_ref, decl_ty_ref);
  }
  if ((init_kind ==ord_expr_array_lit)) {
    n_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref);
    lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref);
    if (lanes <= 0 && decl_kind == ord_type_vector)
      lanes = pipeline_type_array_size_at(arena, decl_ty_ref);
    if (lanes > 0 && n_elems == lanes) {
      elem_decl = typeck_vector_elem_type_ref(arena, decl_ty_ref);
      if (elem_decl > 0) {
        elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl);
        for (i = 0; i < n_elems; i++) {
          elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, i);
          if (elem_ref > 0) {
            int32_t elem_ty = 0;
            int32_t got_kind = 0;
            ek = pipeline_expr_kind_ord_at(arena, elem_ref);
            (void)typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek);
            (void)typeck_coerce_init_float_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek);
            /* G.7 ≡ typeck.x: refuse outer SIMD stamp on known elem mismatch. */
            elem_ty = pipeline_expr_resolved_type_ref(arena, elem_ref);
            if (elem_ty > 0) {
              got_kind = pipeline_type_kind_ord_at(arena, elem_ty);
              if (type_refs_equal(arena, elem_ty, elem_decl)
                  || typeck_integer_widen_ok_refs(arena, elem_decl, elem_ty)
                  || typeck_float_widen_ok(elem_decl_kind, got_kind)) {
                (void)(pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl));
              } else {
                return 0;
              }
            }
          }
        }
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
  }
  return 0;
}
int32_t typeck_coerce_init_vector_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  int32_t lref_c = 0;
  int32_t rref_c = 0;
  int32_t ord_type_vector = 13;
  int32_t ord_add = 4;
  int32_t ord_sub = 5;
  int32_t ord_mul = 6;
  int32_t ord_div = 7;
  int32_t ord_expr_array_lit = 46;
  int32_t lanes = 0;
  (void)((lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref)));
  if (((lanes <=0) && (decl_kind !=ord_type_vector))) {
    return 0;
  }
  if ((lanes <=0)) {
    (void)((lanes = pipeline_type_array_size_at(arena, decl_ty_ref)));
  }
  if ((lanes <=0)) {
    return 0;
  }
  if (((((init_kind !=ord_add) && (init_kind !=ord_sub)) && (init_kind !=ord_mul)) && (init_kind !=ord_div))) {
    return 0;
  }
  (void)((lref_c = pipeline_expr_binop_left_ref_at(arena, init_ref)));
  (void)((rref_c = pipeline_expr_binop_right_ref_at(arena, init_ref)));
  if ((!(ast_ref_is_null(lref_c)) && !(ast_ref_is_null(rref_c)))) {
    int32_t lt_c = expr_type_ref(arena, lref_c);
    int32_t rt_c = expr_type_ref(arena, rref_c);
    int32_t lk_e = pipeline_expr_kind_ord_at(arena, lref_c);
    int32_t rk_e = pipeline_expr_kind_ord_at(arena, rref_c);
    if (((((lk_e ==ord_expr_array_lit) && (rk_e ==ord_expr_array_lit)) && (pipeline_expr_array_lit_num_elems_at(arena, lref_c) ==lanes)) && (pipeline_expr_array_lit_num_elems_at(arena, rref_c) ==lanes))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, lref_c, decl_ty_ref));
      (void)(pipeline_expr_set_resolved_type_ref(arena, rref_c, decl_ty_ref));
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if (((((!(ast_ref_is_null(lt_c)) && !(ast_ref_is_null(rt_c))) && (typeck_vector_lanes_of_type(arena, lt_c) ==lanes)) && (typeck_vector_lanes_of_type(arena, rt_c) ==lanes)) && type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_c), pipeline_type_elem_ref_at(arena, rt_c)))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
  }
  return 0;
}
int32_t typeck_coerce_init_int_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return pipeline_typeck_coerce_init_int_binop_to_decl_c(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t typeck_coerce_init_slice_from_array(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  int32_t ord_type_slice = 11;
  int32_t ord_type_array = 10;
  int32_t decl_elem = 0;
  int32_t init_res = 0;
  int32_t init_kind = 0;
  int32_t init_elem = 0;
  if ((decl_kind !=ord_type_slice)) {
    return 0;
  }
  (void)((decl_elem = pipeline_type_elem_ref_at(arena, decl_ty_ref)));
  (void)((init_res = pipeline_expr_resolved_type_ref(arena, init_ref)));
  if ((ast_ref_is_null(decl_elem) || ast_ref_is_null(init_res))) {
    return 0;
  }
  (void)((init_kind = pipeline_type_kind_ord_at(arena, init_res)));
  if ((init_kind !=ord_type_array)) {
    return 0;
  }
  (void)((init_elem = pipeline_type_elem_ref_at(arena, init_res)));
  if (ast_ref_is_null(init_elem)) {
    return 0;
  }
  if (!(type_refs_equal(arena, init_elem, decl_elem))) {
    return 0;
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
}
int32_t typeck_coerce_init_expr_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  int32_t decl_kind = 0;
  int32_t init_kind = 0;
  if ((ast_ref_is_null(init_ref) || ast_ref_is_null(decl_ty_ref))) {
    return 0;
  }
  if (((((init_ref <=0) || (init_ref > (arena->num_exprs))) || (decl_ty_ref <=0)) || (decl_ty_ref > (arena->num_types)))) {
    return 0;
  }
  (void)((decl_kind = pipeline_type_kind_ord_at(arena, decl_ty_ref)));
  (void)((init_kind = pipeline_expr_kind_ord_at(arena, init_ref)));
  if ((typeck_coerce_init_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_float_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_enum_field_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_named_call_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_resolved_alias_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_array_vector_lit_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_vector_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_int_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
    return 1;
  }
  if ((typeck_coerce_init_slice_from_array(arena, init_ref, decl_ty_ref, decl_kind) !=0)) {
    return 1;
  }
  return 0;
}
int32_t typeck_diag_append_lit(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len) {
  int32_t p = pos;
  int32_t i = 0;
  while ((((i < lit_len) && (p >=0)) && (p < cap))) {
    (void)(((out)[p] = (lit)[i]));
    (void)((p = (p + 1)));
    (void)((i = (i + 1)));
  }
  return p;
}
int32_t typeck_diag_append_u32_dec(uint8_t * out, int32_t pos, int32_t cap, int32_t v) {
  int32_t p = pos;
  if ((((v < 0) || (p < 0)) || (p >=cap))) {
    return p;
  }
  if ((v ==0)) {
    uint8_t zd[1] = {48};
    return typeck_diag_append_lit(out, p, cap, &((zd)[0]), 1);
  }
  int32_t cnt = 0;
  int32_t tc = v;
  while ((tc > 0)) {
    (void)((cnt = (cnt + 1)));
    (void)((tc = (tc / 10)));
  }
  int32_t k = (cnt - 1);
  int32_t tm = v;
  while ((tm > 0)) {
    int32_t d = (tm % 10);
    (void)((tm = (tm / 10)));
    if ((((pos + k) < 0) || ((pos + k) >=cap))) {
      return p;
    }
    (void)(((out)[(pos + k)] = ((uint8_t)((d + 48)))));
    (void)((k = (k - 1)));
  }
  return (pos + cnt);
}
int32_t typeck_diag_fmt_type_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap) {
  uint8_t qmk[1] = {63};
  uint8_t lit_i32[3] = {105, 51, 50};
  uint8_t lit_bool[4] = {98, 111, 111, 108};
  uint8_t lit_u8[2] = {117, 56};
  uint8_t lit_u32[3] = {117, 51, 50};
  uint8_t lit_u64[3] = {117, 54, 52};
  uint8_t lit_i64[3] = {105, 54, 52};
  uint8_t lit_usize[5] = {117, 115, 105, 122, 101};
  uint8_t lit_isize[5] = {105, 115, 105, 122, 101};
  uint8_t lit_f32[3] = {102, 51, 50};
  uint8_t lit_f64[3] = {102, 54, 52};
  uint8_t star[1] = {42};
  uint8_t lbk[1] = {91};
  uint8_t rbk[1] = {93};
  uint8_t slo[2] = {91, 93};
  int32_t kind = 0;
  int32_t nlen = 0;
  int32_t elem_ref = 0;
  int32_t asz = 0;
  int32_t ord_i32 = 0;
  int32_t ord_bool = 1;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_array = 10;
  int32_t ord_slice = 11;
  int32_t ord_linear = 12;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t ord_void = 16;
  uint8_t * nm_buf = typeck_scratch64_slot(0);
  if ((((cur < 0) || (cap <=0)) || (cur >=cap))) {
    return cur;
  }
  if (((ast_ref_is_null(ref) || (ref <=0)) || (ref > (arena->num_types)))) {
    return typeck_diag_append_lit(out, cur, cap, &((qmk)[0]), 1);
  }
  (void)((kind = pipeline_type_kind_ord_at(arena, ref)));
  if ((kind ==ord_named)) {
    (void)((nlen = pipeline_type_named_name_into(arena, ref, nm_buf)));
    if ((nlen > 0)) {
      return typeck_diag_append_lit(out, cur, cap, nm_buf, nlen);
    }
  }
  if ((kind ==ord_i32)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_i32)[0]), 3);
  }
  if ((kind ==ord_bool)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_bool)[0]), 4);
  }
  if ((kind ==ord_u8)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_u8)[0]), 2);
  }
  if ((kind ==ord_u32)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_u32)[0]), 3);
  }
  if ((kind ==ord_u64)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_u64)[0]), 3);
  }
  if ((kind ==ord_i64)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_i64)[0]), 3);
  }
  if ((kind ==ord_usize)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_usize)[0]), 5);
  }
  if ((kind ==ord_isize)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_isize)[0]), 5);
  }
  if ((kind ==ord_f32)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_f32)[0]), 3);
  }
  if ((kind ==ord_f64)) {
    return typeck_diag_append_lit(out, cur, cap, &((lit_f64)[0]), 3);
  }
  if ((kind ==ord_void)) {
    return typeck_diag_append_lit(out, cur, cap, &((qmk)[0]), 1);
  }
  if ((kind ==ord_ptr)) {
    int32_t nex = typeck_diag_append_lit(out, cur, cap, &((star)[0]), 1);
    (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
    return typeck_diag_fmt_type_at(arena, elem_ref, out, nex, cap);
  }
  if ((kind ==ord_slice)) {
    uint8_t lt_ch[1] = {60};
    uint8_t gt_ch[1] = {62};
    int32_t rlen = 0;
    uint8_t * rbuf = typeck_scratch64_slot(15);
    (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
    int32_t nex2 = typeck_diag_append_lit(out, cur, cap, &((slo)[0]), 2);
    (void)((nex2 = typeck_diag_fmt_type_at(arena, elem_ref, out, nex2, cap)));
    (void)((rlen = pipeline_type_region_label_len_at(arena, ref)));
    if (((rlen > 0) && (pipeline_type_region_label_into(arena, ref, rbuf) ==rlen))) {
      int32_t p0 = typeck_diag_append_lit(out, nex2, cap, &((lt_ch)[0]), 1);
      int32_t p1 = typeck_diag_append_lit(out, p0, cap, rbuf, rlen);
      return typeck_diag_append_lit(out, p1, cap, &((gt_ch)[0]), 1);
    }
    return nex2;
  }
  if ((kind ==ord_linear)) {
    uint8_t lpar[7] = {76, 105, 110, 101, 97, 114, 40};
    uint8_t rpar[1] = {41};
    (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
    int32_t p0 = typeck_diag_append_lit(out, cur, cap, &((lpar)[0]), 7);
    int32_t p1 = typeck_diag_fmt_type_at(arena, elem_ref, out, p0, cap);
    return typeck_diag_append_lit(out, p1, cap, &((rpar)[0]), 1);
  }
  if ((kind ==ord_array)) {
    (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
    (void)((asz = pipeline_type_array_size_at(arena, ref)));
    if ((!(ast_ref_is_null(elem_ref)) && (asz > 0))) {
      int32_t p0 = typeck_diag_append_lit(out, cur, cap, &((lbk)[0]), 1);
      int32_t p1 = typeck_diag_append_u32_dec(out, p0, cap, asz);
      int32_t p2 = typeck_diag_append_lit(out, p1, cap, &((rbk)[0]), 1);
      return typeck_diag_fmt_type_at(arena, elem_ref, out, p2, cap);
    }
  }
  return typeck_diag_append_lit(out, cur, cap, &((qmk)[0]), 1);
}
int32_t typeck_diag_fmt_type_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap) {
  return typeck_diag_fmt_type_at(arena, ref, out, 0, cap);
}
int32_t typeck_diag_fmt_type_or_question(struct ast_ASTArena * arena, int32_t ref, uint8_t * out) {
  uint8_t qmk[1] = {63};
  if (((ast_ref_is_null(ref) || (ref <=0)) || (ref > (arena->num_types)))) {
    return typeck_diag_append_lit(out, 0, 96, &((qmk)[0]), 1);
  }
  return typeck_diag_fmt_type_into(arena, ref, out, 96);
}
void typeck_ret_coerce_integral_to_expect_i32(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  int32_t ord_i32 = 0;
  int32_t ord_u8 = 2;
  int32_t ord_usize = 6;
  if ((((ast_ref_is_null(op_ref) || (op_ref <=0)) || (op_ref > (arena->num_exprs))) || ast_ref_is_null(expect_ref))) {
    return;
  }
  if (((expect_ref <=0) || (expect_ref > (arena->num_types)))) {
    return;
  }
  if ((pipeline_type_kind_ord_at(arena, expect_ref) !=ord_i32)) {
    return;
  }
  int32_t got_ref = expr_type_ref(arena, op_ref);
  if (((ast_ref_is_null(got_ref) || (got_ref <=0)) || (got_ref > (arena->num_types)))) {
    return;
  }
  int32_t got_kind = pipeline_type_kind_ord_at(arena, got_ref);
  if (((got_kind !=ord_u8) && (got_kind !=ord_usize))) {
    return;
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
}
void typeck_ret_coerce_integral_widen(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  int32_t got_ref = 0;
  int32_t expect_kind = 0;
  int32_t got_kind = 0;
  if ((((ast_ref_is_null(op_ref) || (op_ref <=0)) || (op_ref > (arena->num_exprs))) || ast_ref_is_null(expect_ref))) {
    return;
  }
  if (((expect_ref <=0) || (expect_ref > (arena->num_types)))) {
    return;
  }
  (void)((got_ref = expr_type_ref(arena, op_ref)));
  if (((ast_ref_is_null(got_ref) || (got_ref <=0)) || (got_ref > (arena->num_types)))) {
    return;
  }
  (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
  (void)((got_kind = pipeline_type_kind_ord_at(arena, got_ref)));
  /* wave313: integer stamp. wave314 f32→f64: no stamp. */
  if (typeck_integer_widen_ok_refs(arena, expect_ref, got_ref)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
    return;
  }
  (void)expect_kind;
  (void)got_kind;
}
void typeck_ret_coerce_null_lit_to_expect(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  int32_t ord_lit = 0;
  int32_t ord_ptr = 9;
  int32_t op_kind = 0;
  int32_t expect_kind = 0;
  int32_t int_val = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || ast_ref_is_null(op_ref)) || ast_ref_is_null(expect_ref))) {
    return;
  }
  (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
  if ((op_kind !=ord_lit)) {
    return;
  }
  (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
  (void)((int_val = pipeline_expr_int_val_at(arena, op_ref)));
  if (((expect_kind ==ord_ptr) && (int_val ==0))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
  }
}
void typeck_ret_fixup_unresolved_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_call = 48;
  int32_t op_kind = 0;
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || ast_ref_is_null(op_ref))) {
    return;
  }
  if (!(ast_ref_is_null(expr_type_ref(arena, op_ref)))) {
    return;
  }
  (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
  if ((op_kind !=ord_call)) {
    return;
  }
  (void)(typeck_check_expr_call_resolve(module, arena, op_ref, ctx));
}
int32_t typeck_return_breadcrumb_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out) {
  int32_t ord_var = 3;
  int32_t ord_field = 44;
  int32_t ord_call = 48;
  int32_t ord_method_call = 49;
  int32_t kind = 0;
  int32_t base_ref = 0;
  int32_t callee_ref = 0;
  int32_t base_len = 0;
  int32_t field_len = 0;
  int32_t callee_len = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
  if ((kind ==ord_var)) {
    (void)((base_len = pipeline_expr_var_name_len(arena, expr_ref)));
    if (((base_len <=0) || (base_len > 60))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, expr_ref, out));
    (void)(((out)[base_len] = 0));
    return base_len;
  }
  if ((kind ==ord_field)) {
    (void)((base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref)));
    if (((base_ref <=0) || (base_ref > (arena->num_exprs)))) {
      return 0;
    }
    (void)((base_len = typeck_return_breadcrumb_into(arena, base_ref, out)));
    (void)((field_len = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if ((((base_len <=0) || (field_len <=0)) || (((base_len + 1) + field_len) > 60))) {
      return 0;
    }
    (void)(((out)[base_len] = 46));
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((out)[(base_len + 1)])));
    (void)(((out)[((base_len + 1) + field_len)] = 0));
    return ((base_len + 1) + field_len);
  }
  if ((kind ==ord_call)) {
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
    (void)((callee_len = typeck_return_breadcrumb_into(arena, callee_ref, out)));
    if (((callee_len <=0) || ((callee_len + 2) > 60))) {
      return 0;
    }
    (void)(((out)[callee_len] = 40));
    (void)(((out)[(callee_len + 1)] = 41));
    (void)(((out)[(callee_len + 2)] = 0));
    return (callee_len + 2);
  }
  if ((kind ==ord_method_call)) {
    (void)((base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref)));
    (void)((base_len = typeck_return_breadcrumb_into(arena, base_ref, out)));
    (void)((field_len = pipeline_expr_method_call_name_len(arena, expr_ref)));
    if ((((base_len <=0) || (field_len <=0)) || (((base_len + 3) + field_len) > 60))) {
      return 0;
    }
    (void)(((out)[base_len] = 46));
    (void)(pipeline_expr_method_call_name_into(arena, expr_ref, &((out)[(base_len + 1)])));
    (void)(((out)[((base_len + 1) + field_len)] = 40));
    (void)(((out)[((base_len + 2) + field_len)] = 41));
    (void)(((out)[((base_len + 3) + field_len)] = 0));
    return ((base_len + 3) + field_len);
  }
  return 0;
}
void typeck_emit_return_subexpr_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col) {
  uint8_t * buf = typeck_scratch64_slot(2);
  int32_t bl = typeck_return_breadcrumb_into(arena, expr_ref, buf);
  if ((bl > 0)) {
    (void)(driver_diagnostic_typeck_return_subexpr(line, col, buf, bl));
  }
  (void)(0);
  return;
}
void typeck_emit_return_unresolved_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col) {
  uint8_t * buf = typeck_scratch64_slot(2);
  int32_t bl = typeck_return_breadcrumb_into(arena, expr_ref, buf);
  if ((bl > 0)) {
    (void)(driver_diagnostic_typeck_return_unresolved(line, col, buf, bl));
  }
  (void)(0);
  return;
}
int32_t typeck_check_expr_float_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  (void)(pipeline_expr_typeck_set_float_bits_from_val(arena, expr_ref));
  int32_t ft = ensure_f64_type_ref(arena);
  if ((ft !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ft));
  }
  return 0;
}
extern int32_t pipeline_typeck_check_expr_int_lit_c(struct ast_ASTArena * arena, int32_t expr_ref);
int32_t typeck_check_expr_int_lit(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref) {
  (void)(typeck_ret_coerce_null_lit_to_expect(arena, expr_ref, return_type_ref));
  return pipeline_typeck_check_expr_int_lit_c(arena, expr_ref);
}
int32_t typeck_check_expr_bool_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  int32_t bt = ensure_bool_type_ref(arena);
  if ((bt !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
  }
  return 0;
}
int32_t typeck_check_expr_string_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  int32_t u8r = ensure_u8_type_ref(arena);
  int32_t ptr_u8 = 0;
  if (ast_ref_is_null(u8r)) {
    return -(1);
  }
  (void)((ptr_u8 = find_or_alloc_ptr_type_ref(arena, u8r)));
  if (!(ast_ref_is_null(ptr_u8))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_u8));
  }
  return 0;
}
int32_t typeck_check_expr_break_continue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_break = 39;
  int32_t ord_continue = 40;
  int32_t line = 0;
  int32_t col = 0;
  int32_t kind = 0;
  int32_t is_break = 1;
  if ((pipeline_dep_ctx_typeck_loop_depth_at(ctx) > 0)) {
    return 0;
  }
  (void)((line = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col = pipeline_expr_col_at(arena, expr_ref)));
  (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
  if ((kind ==ord_continue)) {
    (void)((is_break = 0));
  }
  (void)(driver_diagnostic_typeck_break_continue_outside(line, col, is_break));
  return -(1);
}
int32_t typeck_check_expr_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref) {
  int32_t it = ensure_i32_type_ref(arena);
  if ((it !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, it));
  }
  return 0;
}
int32_t typeck_check_expr_if_ternary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_ternary = 27;
  int32_t ord_named = 8;
  int32_t ord_lit = 0;
  int32_t ord_i32 = 0;
  int32_t ord_u8 = 2;
  int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
  int32_t cond_ref = pipeline_expr_if_cond_ref_at(arena, expr_ref);
  int32_t then_ref = pipeline_expr_if_then_ref_at(arena, expr_ref);
  int32_t else_ref = pipeline_expr_if_else_ref_at(arena, expr_ref);
  int32_t ty_t = 0;
  int32_t ty_e = 0;
  int t_named = 0;
  int e_named = 0;
  int32_t resolved = 0;
  int32_t cond_ty = 0;
  int32_t expect_kind = 0;
  int32_t got_kind = 0;
  int32_t then_k = 0;
  int32_t else_k = 0;
  int32_t tv = 0;
  int32_t ev = 0;
  if ((check_expr(module, arena, cond_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if (!(ast_ref_is_null(cond_ref))) {
    (void)((cond_ty = expr_type_ref(arena, cond_ref)));
    if (!(type_ref_is_bool(arena, cond_ty))) {
      return -(1);
    }
  }
  if ((check_expr(module, arena, then_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if (!(ast_ref_is_null(else_ref))) {
    if ((check_expr(module, arena, else_ref, return_type_ref, ctx) !=0)) {
      return -(1);
    }
  }
  (void)((ty_t = expr_type_ref(arena, then_ref)));
  (void)((ty_e = expr_type_ref(arena, else_ref)));
  if ((!(ast_ref_is_null(ty_t)) && (ty_t > 0))) {
    (void)((t_named = (pipeline_type_kind_ord_at(arena, ty_t) ==ord_named)));
  }
  if ((!(ast_ref_is_null(ty_e)) && (ty_e > 0))) {
    (void)((e_named = (pipeline_type_kind_ord_at(arena, ty_e) ==ord_named)));
  }
  if ((expr_kind ==ord_ternary)) {
    if (ast_ref_is_null(ty_t)) {
      return -(1);
    }
    if (ast_ref_is_null(ty_e)) {
      return -(1);
    }
    if (!(type_refs_equal(arena, ty_t, ty_e))) {
      return -(1);
    }
    (void)((resolved = ty_t));
    if (((!(ast_ref_is_null(return_type_ref)) && (return_type_ref > 0)) && (return_type_ref <=(arena->num_types)))) {
      (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      (void)((got_kind = pipeline_type_kind_ord_at(arena, ty_t)));
      if (typeck_integer_widen_ok_refs(arena, return_type_ref, ty_t)) {
        (void)((resolved = return_type_ref));
      } else if (typeck_float_widen_ok(expect_kind, got_kind)) {
        /* wave314: ternary f32 under f64 expect. */
        (void)((resolved = return_type_ref));
      } else {
        if (((expect_kind ==ord_u8) && (got_kind ==ord_i32))) {
          (void)((then_k = pipeline_expr_kind_ord_at(arena, then_ref)));
          (void)((else_k = pipeline_expr_kind_ord_at(arena, else_ref)));
          if (((then_k ==ord_lit) && (else_k ==ord_lit))) {
            (void)((tv = pipeline_expr_int_val_at(arena, then_ref)));
            (void)((ev = pipeline_expr_int_val_at(arena, else_ref)));
            if (((((tv >=0) && (tv <=255)) && (ev >=0)) && (ev <=255))) {
              (void)((resolved = return_type_ref));
              (void)(pipeline_expr_set_resolved_type_ref(arena, then_ref, return_type_ref));
              (void)(pipeline_expr_set_resolved_type_ref(arena, else_ref, return_type_ref));
            }
          }
        }
      }
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved));
    return 0;
  }
  if ((((!(ast_ref_is_null(ty_t)) && !(ast_ref_is_null(ty_e))) && t_named) && e_named)) {
    if (!(type_refs_equal(arena, ty_t, ty_e))) {
      return -(1);
    }
  }
  if ((!(ast_ref_is_null(ty_t)) && !(ast_ref_is_null(ty_e)))) {
    if ((e_named && !(t_named))) {
      (void)((resolved = ty_e));
    } else {
      (void)((resolved = ty_t));
    }
  } else {
    if (!(ast_ref_is_null(ty_t))) {
      (void)((resolved = ty_t));
    } else {
      if (!(ast_ref_is_null(ty_e))) {
        (void)((resolved = ty_e));
      }
    }
  }
  if (!(ast_ref_is_null(resolved))) {
    if (((!(ast_ref_is_null(return_type_ref)) && (return_type_ref > 0)) && (return_type_ref <=(arena->num_types)))) {
      (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      (void)((got_kind = pipeline_type_kind_ord_at(arena, resolved)));
      if (typeck_integer_widen_ok_refs(arena, return_type_ref, resolved)) {
        (void)((resolved = return_type_ref));
      } else if (typeck_float_widen_ok(expect_kind, got_kind)) {
        /* wave314: if-expr f32 under f64 expect. */
        (void)((resolved = return_type_ref));
      }
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved));
  }
  return 0;
}
int32_t typeck_block_expr_value_ref(struct ast_ASTArena * arena, int32_t block_ref) {
  uint8_t stmt_order_kind_region_c_parser = ((uint8_t)(5));
  uint8_t stmt_order_kind_region_x_parser = ((uint8_t)(6));
  int32_t fin_ref = 0;
  int32_t nso = 0;
  uint8_t last_k = ((uint8_t)(0));
  int32_t ridx = 0;
  int32_t nreg = 0;
  int32_t inner_ref = 0;
  if (((ast_ref_is_null(block_ref) || (block_ref <=0)) || (block_ref > (arena->num_blocks)))) {
    return 0;
  }
  (void)((fin_ref = ast_ast_block_final_expr_ref(arena, block_ref)));
  if (!(ast_ref_is_null(fin_ref))) {
    return fin_ref;
  }
  (void)((nso = ast_ast_block_num_stmt_order(arena, block_ref)));
  if ((nso <=0)) {
    return 0;
  }
  (void)((last_k = ast_ast_block_stmt_order_kind(arena, block_ref, (nso - 1))));
  if (((last_k !=stmt_order_kind_region_c_parser) && (last_k !=stmt_order_kind_region_x_parser))) {
    return 0;
  }
  (void)((ridx = ast_ast_block_stmt_order_idx(arena, block_ref, (nso - 1))));
  (void)((nreg = ast_ast_block_num_regions(arena, block_ref)));
  if (((ridx < 0) || (ridx >=nreg))) {
    return 0;
  }
  if ((pipeline_block_region_is_unsafe(arena, block_ref, ridx) ==0)) {
    return 0;
  }
  (void)((inner_ref = ast_ast_block_region_body_ref(arena, block_ref, ridx)));
  return typeck_block_expr_value_ref(arena, inner_ref);
}
int32_t typeck_check_expr_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_assign = 28;
  int32_t block_ref = pipeline_expr_block_ref_at(arena, expr_ref);
  int32_t fin_blk = 0;
  int32_t ty_fin = 0;
  int32_t nes = 0;
  int32_t fst_es = 0;
  int32_t st_kind = 0;
  int32_t rhs_ref = 0;
  int32_t ty_rhs = 0;
  if ((check_block(module, arena, block_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((ast_ref_is_null(block_ref) || (block_ref <=0))) {
    return 0;
  }
  (void)((fin_blk = typeck_block_expr_value_ref(arena, block_ref)));
  if (!(ast_ref_is_null(fin_blk))) {
    (void)((ty_fin = expr_type_ref(arena, fin_blk)));
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_fin));
    return 0;
  }
  (void)((nes = ast_ast_block_num_expr_stmts(arena, block_ref)));
  if ((nes !=1)) {
    return 0;
  }
  (void)((fst_es = pipeline_block_expr_stmt_ref(arena, block_ref, 0)));
  if ((fst_es <=0)) {
    return 0;
  }
  (void)((st_kind = pipeline_expr_kind_ord_at(arena, fst_es)));
  if (((st_kind !=ord_assign) && ((st_kind < 29) || (st_kind > 39)))) {
    return 0;
  }
  (void)((rhs_ref = pipeline_expr_binop_right_ref_at(arena, fst_es)));
  if (ast_ref_is_null(rhs_ref)) {
    return 0;
  }
  (void)((ty_rhs = expr_type_ref(arena, rhs_ref)));
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_rhs));
  return 0;
}
int32_t typeck_check_expr_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_assign = 28;
  int32_t ord_lit = 0;
  int32_t ord_var = 3;
  int32_t ord_ternary = 27;
  int32_t ord_add = 4;
  int32_t ord_sub = 5;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_type_array = 10;
    int32_t ord_type_slice = 11;
  int32_t ord_field = 44;
  int32_t ord_index = 47;
  int32_t ord_call = 48;
  int32_t ord_expr_array_lit = 46;
  int32_t ord_string_lit = 59;
  int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
  int32_t left_ref = pipeline_expr_binop_left_ref_at(arena, expr_ref);
  int32_t right_ref = pipeline_expr_binop_right_ref_at(arena, expr_ref);
  int32_t line = pipeline_expr_line_at(arena, expr_ref);
  int32_t col = pipeline_expr_col_at(arena, expr_ref);
  if ((pipeline_typeck_check_struct_stack_escape_assign_c(module, arena, expr_ref, left_ref, right_ref, ctx) !=0)) {
    return -(1);
  }
  if ((pipeline_typeck_check_scope_borrow_assign_c(module, arena, expr_ref, left_ref, right_ref, ctx) !=0)) {
    return -(1);
  }
  if ((pipeline_typeck_check_allocator_region_assign_c(module, arena, expr_ref, left_ref, ctx) !=0)) {
    return -(1);
  }
  int32_t lt = 0;
  int32_t rt = 0;
  int32_t rt_after = 0;
  int32_t rhs_ctx = 0;
  int32_t compound_flag = 1;
  int32_t lt_kind = 0;
  int32_t rhs_kind = 0;
  int32_t lhs_kind = 0;
  int32_t int_val = 0;
  int32_t ev = 0;
  int32_t then_r = 0;
  int32_t else_r = 0;
  uint8_t * eb = ((uint8_t *)(0));
  uint8_t * gb = ((uint8_t *)(0));
  int32_t el = 0;
  int32_t gl = 0;
  if ((expr_kind ==ord_assign)) {
    (void)((compound_flag = 0));
  }
  /* wave472 L4: assign LHS expected=0 (not function return ambient). See typeck.x. */
  if ((check_expr(module, arena, left_ref, 0, ctx) !=0)) {
    return -(1);
  }
  /* wave678 Cap residual: const immutable (docs/06). G.7 ≡ typeck.x / pipeline assign. */
  {
    int32_t lhs_kind_c = pipeline_expr_kind_ord_at(arena, left_ref);
    extern int32_t pipeline_block_name_binding_kind(struct ast_ASTArena *a, int32_t block_ref,
                                                   uint8_t *vname, int32_t vlen);
    extern int32_t pipeline_module_top_level_name_is_const(struct ast_Module *m, uint8_t *vname,
                                                          int32_t vlen);
    extern void driver_diagnostic_typeck_assign_to_const(int32_t line, int32_t col);
    extern int32_t pipeline_dep_ctx_current_block_ref_at(struct ast_PipelineDepCtx *ctx);
    if (lhs_kind_c == 3 /* EXPR_VAR */) {
      uint8_t vbuf_c[128];
      int32_t vnlen_c = pipeline_expr_var_name_len(arena, left_ref);
      int32_t bind_kind = -1;
      int32_t br_c = 0;
      int32_t bi = 0;
      if (vnlen_c > 0 && vnlen_c < 128) {
        /* No memset — seed TU may omit string.h; name_into writes vnlen bytes. */
        pipeline_expr_var_name_into(arena, left_ref, &vbuf_c[0]);
        if (ctx) {
          br_c = pipeline_dep_ctx_current_block_ref_at(ctx);
          if (br_c > 0)
            bind_kind = pipeline_block_name_binding_kind(arena, br_c, &vbuf_c[0], vnlen_c);
        }
        if (bind_kind < 0) {
          bi = pipeline_module_top_level_name_is_const(module, &vbuf_c[0], vnlen_c);
          if (bi != 0)
            bind_kind = 1;
        }
        if (bind_kind == 1) {
          driver_diagnostic_typeck_assign_to_const(line, col);
          return -(1);
        }
      }
    }
  }
  (void)((lt = expr_type_ref(arena, left_ref)));
  (void)((rhs_ctx = return_type_ref));
  if (!(ast_ref_is_null(lt))) {
    (void)((rhs_ctx = lt));
  }
  if ((check_expr(module, arena, right_ref, rhs_ctx, ctx) !=0)) {
    return -(1);
  }
  if ((ast_ref_is_null(left_ref) || ast_ref_is_null(right_ref))) {
    return 0;
  }
  if (ast_ref_is_null(lt)) {
    (void)((lt = expr_type_ref(arena, left_ref)));
  }
  (void)((rt_after = expr_type_ref(arena, right_ref)));
  if ((!(ast_ref_is_null(lt)) && (lt > 0))) {
    (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
    (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
    if (((rhs_kind ==ord_expr_array_lit) && ((lt_kind ==ord_type_array) || (lt_kind ==ord_type_slice)))) {
      if ((typeck_coerce_array_lit_elem_types_to_decl(module, arena, right_ref, lt) < 0)) {
        return -(1);
      }
      (void)((rt_after = expr_type_ref(arena, right_ref)));
    }
    /* wave308: assign RHS bare EXPR_LIT — G.7 reuse typeck_coerce_init_lit_to_decl
     * (full i64; drop i32 int_val gate).
     * wave310: assign RHS EXPR_NEG/int binop — G.7 reuse typeck_coerce_init_int_binop_to_decl
     * (u8/u16/u64 =-1 assign; 1-2).
     * wave316: FLOAT_LIT / -float → f32/f64 (G.7 float_lit coerce). PLATFORM: SHARED */
    if (!(type_refs_equal(arena, lt, rt_after))) {
      if ((rhs_kind ==ord_lit)) {
        (void)(typeck_coerce_init_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
      } else {
        (void)(typeck_coerce_init_float_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
        (void)(typeck_coerce_init_int_binop_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
      }
    }
  }
  (void)((rt = expr_type_ref(arena, right_ref)));
  if (((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt))) && !(type_refs_equal(arena, lt, rt)))) {
    int32_t rt_kind_assign = pipeline_type_kind_ord_at(arena, rt);
    (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
    if (typeck_integer_widen_ok_refs(arena, lt, rt)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
      (void)((rt = lt));
    }
    /* wave314: f32→f64 assign — no stamp. */
    (void)rt_kind_assign;
  }
  if (((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt))) && !(type_refs_equal(arena, lt, rt)))) {
    (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
    if ((rhs_kind ==ord_ternary)) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      if ((lt_kind ==ord_u8)) {
        (void)((then_r = pipeline_expr_if_then_ref_at(arena, right_ref)));
        (void)((else_r = pipeline_expr_if_else_ref_at(arena, right_ref)));
        if (((pipeline_expr_kind_ord_at(arena, then_r) ==ord_lit) && (pipeline_expr_kind_ord_at(arena, else_r) ==ord_lit))) {
          (void)((int_val = pipeline_expr_int_val_at(arena, then_r)));
          (void)((ev = pipeline_expr_int_val_at(arena, else_r)));
          if (((((int_val >=0) && (int_val <=255)) && (ev >=0)) && (ev <=255))) {
            (void)(pipeline_expr_set_resolved_type_ref(arena, then_r, lt));
            (void)(pipeline_expr_set_resolved_type_ref(arena, else_r, lt));
            (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
            (void)((rt = lt));
          }
        }
      }
    }
  }
  if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
    (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
    if ((rhs_kind ==ord_call)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
      (void)((rt = lt));
    }
    if ((rhs_kind ==ord_string_lit)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
      (void)((rt = lt));
    }
    if ((rhs_kind ==ord_field)) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      if ((typeck_coerce_init_enum_field_to_decl(module, arena, right_ref, lt, lt_kind, rhs_kind) !=0)) {
        (void)((rt = expr_type_ref(arena, right_ref)));
      }
    }
  }
  if ((ast_ref_is_null(lt) && !(ast_ref_is_null(rt)))) {
    (void)((lhs_kind = pipeline_expr_kind_ord_at(arena, left_ref)));
    if ((((lhs_kind ==ord_var) || (lhs_kind ==ord_field)) || (lhs_kind ==ord_index))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, left_ref, rt));
      (void)((lt = rt));
    }
  }
  if ((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt)))) {
    if (!(type_refs_equal(arena, lt, rt))) {
      int32_t lt_k_mis = pipeline_type_kind_ord_at(arena, lt);
      int32_t rt_k_mis = pipeline_type_kind_ord_at(arena, rt);
      if (!(typeck_float_widen_ok(lt_k_mis, rt_k_mis))) {
        (void)((eb = driver_typeck_diag_scratch_expect()));
        (void)((gb = driver_typeck_diag_scratch_found()));
        (void)((el = typeck_diag_fmt_type_into(arena, lt, eb, 96)));
        (void)((gl = typeck_diag_fmt_type_into(arena, rt, gb, 96)));
        (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
        return -(1);
      }
    }
    if ((pipeline_typeck_check_slice_region_assign_c(arena, expr_ref, lt, rt) !=0)) {
      return -(1);
    }
  }
  if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
    (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
    if (((rhs_kind ==ord_sub) || (rhs_kind ==ord_add))) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      if ((lt_kind ==ord_usize)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
        (void)((rt = lt));
      }
    }
  }
  (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  if ((ast_ref_is_null(lt) && !(ast_ref_is_null(rt)))) {
    (void)((el = typeck_diag_fmt_type_or_question(arena, lt, eb)));
    (void)((gl = typeck_diag_fmt_type_or_question(arena, rt, gb)));
    (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
    return -(1);
  }
  if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
    (void)((el = typeck_diag_fmt_type_or_question(arena, lt, eb)));
    (void)((gl = typeck_diag_fmt_type_or_question(arena, rt, gb)));
    (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
    return -(1);
  }
  return 0;
}
int32_t typeck_check_expr_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_void = 16;
  int32_t ord_lit = 0;
  int32_t ord_as = 54;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_ptr = 9;
  int32_t op_ref = 0;
  int32_t line = 0;
  int32_t col = 0;
  int32_t rt_kind = 0;
  int32_t op_kind = 0;
  int32_t int_val = 0;
  int32_t as_tgt = 0;
  int32_t got = 0;
  uint8_t * eb = ((uint8_t *)(0));
  uint8_t * gb = ((uint8_t *)(0));
  int32_t el = 0;
  int32_t gl = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
  (void)((line = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col = pipeline_expr_col_at(arena, expr_ref)));
  if (ast_ref_is_null(op_ref)) {
    if (!(ast_ref_is_null(return_type_ref))) {
      (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      if ((rt_kind !=ord_void)) {
        (void)(driver_diagnostic_typeck_ret_fail(1, expr_ref, return_type_ref, 0));
        return -(1);
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
    }
    return 0;
  }
  if (!(ast_ref_is_null(return_type_ref))) {
    (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
    if ((rt_kind ==ord_void)) {
      (void)((got = expr_type_ref(arena, op_ref)));
      (void)(driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got));
      return -(1);
    }
  }
  (void)(typeck_ret_fixup_unresolved_call(module, arena, op_ref, ctx));
  if ((check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
    if (ast_ref_is_null(expr_type_ref(arena, op_ref))) {
      (void)(typeck_emit_return_unresolved_breadcrumb(arena, op_ref, line, col));
    } else {
      (void)(typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col));
    }
    (void)(driver_diagnostic_typeck_ret_fail(1, op_ref, return_type_ref, 0));
    return -(1);
  }
  (void)(typeck_ret_coerce_null_lit_to_expect(arena, op_ref, return_type_ref));
  if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
    int32_t rk_ret = pipeline_type_kind_ord_at(arena, return_type_ref);
    int32_t ok_ret = pipeline_expr_kind_ord_at(arena, op_ref);
    /* wave318: return bare int lit → f32/f64 (G.7 reuse lit coerce; let/assign parity).
     * wave319: return EXPR_NEG / int binop → f32/f64 (G.7 reuse int_binop). */
    (void)(typeck_coerce_init_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
    (void)(typeck_coerce_init_int_binop_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
    /* wave316: return float lit / -float → f32/f64. */
    (void)(typeck_coerce_init_float_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
    if ((typeck_coerce_init_enum_field_to_decl(module, arena, op_ref, return_type_ref, rk_ret, ok_ret) !=0)) {
    }
  }
  if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
    (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
    if ((op_kind ==ord_lit)) {
      (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      if ((rt_kind ==ord_i64)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
      } else {
        (void)((int_val = pipeline_expr_int_val_at(arena, op_ref)));
        if (((int_val ==0) && (rt_kind ==ord_ptr))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
        } else {
          if ((int_val >=0)) {
            if ((((rt_kind ==ord_usize) || (rt_kind ==ord_u32)) || (rt_kind ==ord_u64))) {
              (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
            }
          }
        }
      }
    }
  }
  if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
    int32_t ord_type_array = 10;
    int32_t ord_type_vector = 13;
    int32_t ord_expr_array_lit = 46;
    int32_t ret_lanes = 0;
    (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
    (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
    if (((op_kind ==ord_expr_array_lit) && (rt_kind ==ord_type_array))) {
      if ((typeck_coerce_array_lit_elem_types_to_decl(module, arena, op_ref, return_type_ref) < 0)) {
        return -(1);
      }
    }
    if ((op_kind ==ord_expr_array_lit)) {
      (void)((ret_lanes = typeck_vector_lanes_of_type(arena, return_type_ref)));
      if (((ret_lanes > 0) && (pipeline_expr_array_lit_num_elems_at(arena, op_ref) ==ret_lanes))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
      } else {
        if (((rt_kind ==ord_type_vector) && (pipeline_expr_array_lit_num_elems_at(arena, op_ref) ==pipeline_type_array_size_at(arena, return_type_ref)))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
        }
      }
    }
  }
  if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
    (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
    if ((op_kind ==ord_as)) {
      (void)((as_tgt = pipeline_expr_as_target_type_ref_at(arena, op_ref)));
      if ((!(ast_ref_is_null(as_tgt)) && type_refs_equal(arena, as_tgt, return_type_ref))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, as_tgt));
      }
    }
  }
  if ((!(ast_ref_is_null(return_type_ref)) && !(ast_ref_is_null(op_ref)))) {
    int32_t expect_kind = 0;
    int32_t got_kind = 0;
    if ((pipeline_typeck_check_return_slice_region_in_scope_c(arena, expr_ref, return_type_ref, ctx) !=0)) {
      return -(1);
    }
    (void)(typeck_ret_coerce_integral_to_expect_i32(arena, op_ref, return_type_ref));
    (void)(typeck_ret_coerce_integral_widen(arena, op_ref, return_type_ref));
    (void)((got = expr_type_ref(arena, op_ref)));
    if (!(typeck_return_operand_matches(module, arena, op_ref, return_type_ref))) {
      if (((!(ast_ref_is_null(got)) && (got > 0)) && !(ast_ref_is_null(return_type_ref)))) {
        (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
        (void)((got_kind = pipeline_type_kind_ord_at(arena, got)));
        if ((typeck_integer_widen_ok_refs(arena, return_type_ref, got) || typeck_float_widen_ok(expect_kind, got_kind))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
          if ((pipeline_typeck_check_return_slice_region_c(arena, expr_ref, op_ref, return_type_ref) !=0)) {
            return -(1);
          }
          return 0;
        }
      }
      (void)((eb = driver_typeck_diag_scratch_expect()));
      (void)((gb = driver_typeck_diag_scratch_found()));
      (void)((el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb)));
      (void)((gl = typeck_diag_fmt_type_or_question(arena, got, gb)));
      (void)(driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl));
      (void)(typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col));
      (void)(driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got));
      return -(1);
    }
    if ((pipeline_typeck_check_return_slice_region_c(arena, expr_ref, op_ref, return_type_ref) !=0)) {
      return -(1);
    }
  }
  return 0;
}
int32_t typeck_check_expr_panic(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t op_ref = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
  if ((check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if (!(ast_ref_is_null(return_type_ref))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
  }
  return 0;
}
int32_t typeck_check_expr_match_arm(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arm_i, int32_t num_arms, int32_t line, int32_t col) {
  int32_t is_enum = 0;
  int32_t var_ix = 0;
  int32_t arm_res = 0;
  int32_t guard_ref = 0;
  int32_t bool_ty = 0;
  extern int32_t pipeline_expr_match_arm_guard_ref(struct ast_ASTArena *a, int32_t er, int32_t i);
  if ((arm_i >=num_arms)) {
    return 0;
  }
  (void)((is_enum = pipeline_expr_match_arm_is_enum_variant(arena, expr_ref, arm_i)));
  if ((is_enum !=0)) {
    (void)((var_ix = pipeline_expr_match_arm_variant_index(arena, expr_ref, arm_i)));
    if ((var_ix < 0)) {
      (void)(driver_diagnostic_typeck_enum_no_variant(line, col));
      return -(1);
    }
  }
  /* wave700: optional guard as bool ambient (G.7 ≡ typeck.x). */
  (void)((guard_ref = pipeline_expr_match_arm_guard_ref(arena, expr_ref, arm_i)));
  if ((!(ast_ref_is_null(guard_ref)) && (guard_ref > 0))) {
    (void)((bool_ty = ensure_bool_type_ref(arena)));
    if ((check_expr(module, arena, guard_ref, bool_ty, ctx) !=0)) {
      return -(1);
    }
  }
  (void)((arm_res = pipeline_expr_match_arm_result_ref(arena, expr_ref, arm_i)));
  if ((check_expr(module, arena, arm_res, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  return typeck_check_expr_match_arm(module, arena, expr_ref, return_type_ref, ctx, (arm_i + 1), num_arms, line, col);
}
int32_t typeck_check_expr_match(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t matched_ref = pipeline_expr_match_matched_ref_at(arena, expr_ref);
  int32_t num_arms = pipeline_expr_match_num_arms_at(arena, expr_ref);
  int32_t line = pipeline_expr_line_at(arena, expr_ref);
  int32_t col = pipeline_expr_col_at(arena, expr_ref);
  if ((check_expr(module, arena, matched_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((typeck_check_expr_match_arm(module, arena, expr_ref, return_type_ref, ctx, 0, num_arms, line, col) !=0)) {
    return -(1);
  }
  if (!(ast_ref_is_null(return_type_ref))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
  }
  return 0;
}
int32_t typeck_check_expr_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args) {
  int32_t arg_ref = 0;
  if ((arg_i >=num_args)) {
    return 0;
  }
  (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, arg_i)));
  if ((check_expr(module, arena, arg_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  return typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, (arg_i + 1), num_args);
}
int32_t typeck_check_expr_call_resolve(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_addr_of = 51;
  int32_t ord_var = 3;
  int32_t minus_one = -(1);
  int32_t callee_ref = 0;
  int32_t callee_eff = 0;
  int32_t inner_c = 0;
  int32_t ret_ty = 0;
  int32_t cnml = 0;
  uint8_t cnm[128] = {};
  (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
  if (ast_ref_is_null(callee_ref)) {
    return 0;
  }
  (void)((callee_eff = callee_ref));
  if ((pipeline_expr_kind_ord_at(arena, callee_eff) ==ord_addr_of)) {
    (void)((inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff)));
    if (!(ast_ref_is_null(inner_c))) {
      (void)((callee_eff = inner_c));
    }
  }
  (void)((cnml = 0));
  if ((pipeline_expr_kind_ord_at(arena, callee_eff) ==ord_var)) {
    (void)((cnml = pipeline_expr_var_name_len(arena, callee_eff)));
    if ((cnml > 0)) {
      (void)(pipeline_expr_var_name_into(arena, callee_eff, &((cnm)[0])));
    }
  }
  (void)((ret_ty = resolve_call_callee_return_type(module, arena, callee_eff, expr_ref, ctx)));
  if (((ret_ty ==0) && (cnml > 0))) {
    (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
    (void)((ret_ty = find_func_return_type_in_module_by_name(module, arena, &((cnm)[0]), cnml, minus_one, ctx, typeck_call_resolve_func_idx_slot())));
    if ((ret_ty !=0)) {
      (void)(ast_ast_expr_apply_call_resolve(arena, expr_ref, minus_one, typeck_call_resolve_func_idx_peek()));
    }
  }
  if (((cnml > 0) && (pipeline_typeck_is_read_ptr_slice_callee_c(&((cnm)[0]), cnml) !=0))) {
    (void)((ret_ty = pipeline_typeck_read_ptr_slice_return_ref_c(arena)));
  }
  if ((ret_ty !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
  }
  return 0;
}
/* wave660 Cap residual: hard-fail CALL arity (G.7 ≡ typeck.x).
 * wave675: also hard-fail unresolved bare VAR callee (name_hits==0). */
int32_t typeck_check_call_arity(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t num_args = 0;
  int32_t fi = 0;
  int32_t dep = 0;
  struct ast_Module * mod = ((struct ast_Module *)(0));
  struct ast_Module * dm = ((struct ast_Module *)(0));
  int32_t np = 0;
  int32_t line_a = 0;
  int32_t col_a = 0;
  int32_t callee_ref = 0;
  int32_t callee_eff = 0;
  int32_t ord_addr_of = 51;
  int32_t ord_var = 3;
  int32_t inner_c = 0;
  int32_t cnml = 0;
  uint8_t cnm[128];
  int32_t j = 0;
  int32_t name_hits = 0;
  int32_t arity_hits = 0;
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (expr_ref <=0))) {
    return 0;
  }
  (void)((num_args = pipeline_expr_call_num_args_at(arena, expr_ref)));
  (void)((fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref)));
  (void)((dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref)));
  if ((fi >=0)) {
    (void)((mod = module));
    if (((dep >=0) && (ctx !=((struct ast_PipelineDepCtx *)(0))))) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep)));
      if ((dm !=((struct ast_Module *)(0)))) {
        (void)((mod = dm));
      }
    }
    (void)((np = pipeline_module_func_num_params_at(mod, fi)));
    if ((np !=num_args)) {
      (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a));
      return -(1);
    }
    return 0;
  }
  (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
  if (ast_ref_is_null(callee_ref)) {
    return 0;
  }
  (void)((callee_eff = callee_ref));
  if ((pipeline_expr_kind_ord_at(arena, callee_eff) ==ord_addr_of)) {
    (void)((inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff)));
    if (!(ast_ref_is_null(inner_c))) {
      (void)((callee_eff = inner_c));
    }
  }
  if ((pipeline_expr_kind_ord_at(arena, callee_eff) !=ord_var)) {
    return 0;
  }
  (void)((cnml = pipeline_expr_var_name_len(arena, callee_eff)));
  if (((cnml <=0) || (cnml > 127))) {
    return 0;
  }
  (void)(pipeline_expr_var_name_into(arena, callee_eff, &((cnm)[0])));
  if ((pipeline_typeck_is_read_ptr_slice_callee_c(&((cnm)[0]), cnml) !=0)) {
    return 0;
  }
  (void)((name_hits = 0));
  (void)((arity_hits = 0));
  (void)((j = 0));
  while ((j < (module->num_funcs))) {
    if ((pipeline_module_func_name_equal_at(module, j, &((cnm)[0]), cnml) !=0)) {
      (void)((name_hits = (name_hits + 1)));
      if ((pipeline_module_func_num_params_at(module, j) ==num_args)) {
        (void)((arity_hits = (arity_hits + 1)));
      }
    }
    (void)((j = (j + 1)));
  }
  if (((name_hits > 0) && (arity_hits ==0))) {
    (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a));
    return -(1);
  }
  /* wave675: completely unknown bare name → hard-fail (was BLD001 undeclared). */
  if ((name_hits ==0)) {
    (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_call_unresolved(line_a, col_a));
    return -(1);
  }
  return 0;
}
/*
 * wave685 Cap residual: free type-param detect (G.7 ≡ typeck.x typeck_type_is_free_type_param).
 * PLATFORM: SHARED typeck helper.
 */
int32_t typeck_type_is_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  uint8_t nm[128];
  int32_t nlen = 0;
  int32_t nsl = 0;
  int32_t si = 0;
  int32_t snlen = 0;
  uint8_t * snm = 0;
  int32_t n_alias = 0;
  int32_t ai = 0;
  int32_t alen = 0;
  int32_t off = 0;
  int32_t same = 0;
  if ((((module == 0) || (arena == 0)) || (ty_ref <= 0))) {
    return 0;
  }
  if ((pipeline_type_kind_ord_at(arena, ty_ref) != 8)) {
    return 0;
  }
  /* No memset — seed TU may omit string.h; name_into writes nlen bytes. */
  (void)((nlen = pipeline_type_named_name_into(arena, ty_ref, &((nm)[0]))));
  if (((nlen <= 0) || (nlen > 127))) {
    return 0;
  }
  (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
  (void)((si = 0));
  while ((si < nsl)) {
    (void)((snlen = pipeline_module_struct_layout_name_len(module, si)));
    if (((snlen == nlen) && (snlen > 0))) {
      (void)((snm = typeck_scratch64_slot(2)));
      pipeline_module_struct_layout_name_into(module, si, snm);
      if (name_equal(snm, snlen, &((nm)[0]), nlen)) {
        return 0;
      }
    }
    (void)((si = (si + 1)));
  }
  (void)((n_alias = pipeline_module_num_type_aliases_at(module)));
  (void)((ai = 0));
  while ((ai < n_alias)) {
    (void)((alen = pipeline_module_type_alias_name_len(module, ai)));
    if ((((alen == nlen) && (alen > 0)) && (alen <= 127))) {
      (void)((same = 1));
      (void)((off = 0));
      while ((off < alen)) {
        if ((pipeline_module_type_alias_name_byte_at(module, ai, off) != nm[off])) {
          (void)((same = 0));
          break;
        }
        (void)((off = (off + 1)));
      }
      if ((same != 0)) {
        return 0;
      }
    }
    (void)((ai = (ai + 1)));
  }
  return 1;
}
/* wave686: type tree has free type-param (G.7 ≡ typeck.x typeck_type_tree_has_free_type_param). */
int32_t typeck_type_tree_has_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  int32_t kind = 0;
  int32_t elem = 0;
  int32_t n_ta = 0;
  int32_t i = 0;
  int32_t ta = 0;
  int32_t asz = 0;
  extern int32_t pipeline_type_type_arg_ref_at(struct ast_ASTArena *a, int32_t type_ref, int32_t idx);
  if ((((module == 0) || (arena == 0)) || (ty_ref <= 0)) || (depth > 12)) {
    return 0;
  }
  if ((typeck_type_is_free_type_param(module, arena, ty_ref) != 0)) {
    return 1;
  }
  (void)((kind = pipeline_type_kind_ord_at(arena, ty_ref)));
  if (((((kind == 9) || (kind == 10)) || (kind == 11)) || (kind == 13))) {
    (void)((elem = pipeline_type_elem_ref_at(arena, ty_ref)));
    if ((elem > 0)) {
      return typeck_type_tree_has_free_type_param(module, arena, elem, (depth + 1));
    }
    return 0;
  }
  if ((kind == 8)) {
    (void)((asz = pipeline_type_array_size_at(arena, ty_ref)));
    if (((asz > 0) && (asz <= 8))) {
      (void)((n_ta = asz));
    } else {
      (void)((n_ta = 0));
      (void)((i = 0));
      while ((i < 8)) {
        (void)((ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i)));
        if ((ta <= 0)) {
          break;
        }
        (void)((n_ta = (i + 1)));
        (void)((i = (i + 1)));
      }
    }
    (void)((i = 0));
    while ((i < n_ta)) {
      (void)((ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i)));
      if (((ta <= 0) && (i == 0))) {
        (void)((ta = pipeline_type_elem_ref_at(arena, ty_ref)));
      }
      if (((ta > 0) && (typeck_type_tree_has_free_type_param(module, arena, ta, (depth + 1)) != 0))) {
        return 1;
      }
      (void)((i = (i + 1)));
    }
  }
  return 0;
}
/* wave686: structural free-param formal vs concrete arg (G.7 ≡ typeck.x). */
int32_t typeck_generic_formal_matches_arg_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t formal_ty, int32_t arg_ty, int32_t depth) {
  int32_t fk = 0;
  int32_t ak = 0;
  int32_t felem = 0;
  int32_t aelem = 0;
  int32_t fsz = 0;
  int32_t asz = 0;
  uint8_t fnm[128];
  uint8_t anm[128];
  int32_t fnlen = 0;
  int32_t anlen = 0;
  int32_t n_fta = 0;
  int32_t n_ata = 0;
  int32_t i = 0;
  int32_t fta = 0;
  int32_t ata = 0;
  extern int32_t pipeline_type_type_arg_ref_at(struct ast_ASTArena *a, int32_t type_ref, int32_t idx);
  if (((((module == 0) || (arena == 0)) || (formal_ty <= 0)) || (arg_ty <= 0)) || (depth > 12)) {
    return 0;
  }
  if ((typeck_type_is_free_type_param(module, arena, formal_ty) != 0)) {
    return 1;
  }
  if ((pipeline_typeck_type_refs_equal_c(arena, formal_ty, arg_ty) != 0)) {
    return 1;
  }
  (void)((fk = pipeline_type_kind_ord_at(arena, formal_ty)));
  (void)((ak = pipeline_type_kind_ord_at(arena, arg_ty)));
  if (((fk < 0) || (ak < 0))) {
    return 0;
  }
  if ((fk == 8)) {
    if ((ak != 8)) {
      return 0;
    }
    (void)((fnlen = pipeline_type_named_name_into(arena, formal_ty, &((fnm)[0]))));
    (void)((anlen = pipeline_type_named_name_into(arena, arg_ty, &((anm)[0]))));
    if ((((fnlen <= 0) || (anlen <= 0)) || (name_equal(&((fnm)[0]), fnlen, &((anm)[0]), anlen) == 0))) {
      return 0;
    }
    (void)((asz = pipeline_type_array_size_at(arena, formal_ty)));
    if (((asz > 0) && (asz <= 8))) {
      (void)((n_fta = asz));
    } else {
      (void)((n_fta = 0));
      (void)((i = 0));
      while ((i < 8)) {
        if ((pipeline_type_type_arg_ref_at(arena, formal_ty, i) <= 0)) {
          break;
        }
        (void)((n_fta = (i + 1)));
        (void)((i = (i + 1)));
      }
    }
    if ((n_fta <= 0)) {
      return 1;
    }
    (void)((asz = pipeline_type_array_size_at(arena, arg_ty)));
    if (((asz > 0) && (asz <= 8))) {
      (void)((n_ata = asz));
    } else {
      (void)((n_ata = 0));
      (void)((i = 0));
      while ((i < 8)) {
        if ((pipeline_type_type_arg_ref_at(arena, arg_ty, i) <= 0)) {
          break;
        }
        (void)((n_ata = (i + 1)));
        (void)((i = (i + 1)));
      }
    }
    if ((n_ata <= 0)) {
      (void)((aelem = pipeline_type_elem_ref_at(arena, arg_ty)));
      if ((aelem > 0)) {
        (void)((n_ata = 1));
      }
    }
    if ((n_ata < n_fta)) {
      return 0;
    }
    (void)((i = 0));
    while ((i < n_fta)) {
      (void)((fta = pipeline_type_type_arg_ref_at(arena, formal_ty, i)));
      if (((fta <= 0) && (i == 0))) {
        (void)((fta = pipeline_type_elem_ref_at(arena, formal_ty)));
      }
      (void)((ata = pipeline_type_type_arg_ref_at(arena, arg_ty, i)));
      if (((ata <= 0) && (i == 0))) {
        (void)((ata = pipeline_type_elem_ref_at(arena, arg_ty)));
      }
      if (((fta <= 0) || (ata <= 0))) {
        return 0;
      }
      if ((typeck_generic_formal_matches_arg_type(module, arena, fta, ata, (depth + 1)) == 0)) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
  if (((((fk == 9) || (fk == 10)) || (fk == 11)) || (fk == 13))) {
    if ((ak != fk)) {
      return 0;
    }
    (void)((felem = pipeline_type_elem_ref_at(arena, formal_ty)));
    (void)((aelem = pipeline_type_elem_ref_at(arena, arg_ty)));
    if (((felem <= 0) || (aelem <= 0))) {
      return 0;
    }
    if (((fk == 10) || (fk == 13))) {
      (void)((fsz = pipeline_type_array_size_at(arena, formal_ty)));
      (void)((asz = pipeline_type_array_size_at(arena, arg_ty)));
      if ((((fsz > 0) && (asz > 0)) && (fsz != asz))) {
        return 0;
      }
    }
    return typeck_generic_formal_matches_arg_type(module, arena, felem, aelem, (depth + 1));
  }
  if ((fk == ak)) {
    return 1;
  }
  return 0;
}
/* Twin of typeck.x typeck_call_is_fmt_debug_print_any (7.4.9).
 * Product: 1-arg std.fmt / std.debug print/println composite → JSON any, not T001.
 * PLATFORM: SHARED. G.7 complete existing gate; no third scorer.
 */
int32_t typeck_call_is_fmt_debug_print_any(struct ast_Module * mod, int32_t fi, int32_t dep,
    struct ast_PipelineDepCtx * ctx, int32_t num_args) {
  int32_t nlen = 0;
  int32_t plen = 0;
  uint8_t print_nm[8];
  uint8_t println_nm[8];
  uint8_t pb[128] = {};
  if (num_args != 1) {
    return 0;
  }
  if ((mod == 0) || (fi < 0)) {
    return 0;
  }
  if ((dep < 0) || (ctx == 0)) {
    return 0;
  }
  nlen = pipeline_module_func_name_len_at(mod, fi);
  if ((nlen != 5) && (nlen != 7)) {
    return 0;
  }
  print_nm[0] = 112; print_nm[1] = 114; print_nm[2] = 105; print_nm[3] = 110; print_nm[4] = 116;
  println_nm[0] = 112; println_nm[1] = 114; println_nm[2] = 105; println_nm[3] = 110;
  println_nm[4] = 116; println_nm[5] = 108; println_nm[6] = 110;
  if (nlen == 5) {
    if (pipeline_module_func_name_equal_at(mod, fi, &(print_nm[0]), 5) == 0) {
      return 0;
    }
  } else {
    if (pipeline_module_func_name_equal_at(mod, fi, &(println_nm[0]), 7) == 0) {
      return 0;
    }
  }
  plen = pipeline_dep_ctx_import_path_len(ctx, dep);
  if ((plen != 7) && (plen != 9)) {
    return 0;
  }
  pipeline_dep_ctx_import_path_copy64(ctx, dep, &(pb[0]));
  if (plen == 7) {
    if (((pb[0] == 115) && (pb[1] == 116) && (pb[2] == 100) && (pb[3] == 46)
        && (pb[4] == 102) && (pb[5] == 109) && (pb[6] == 116))) {
      return 1;
    }
    return 0;
  }
  if (((pb[0] == 115) && (pb[1] == 116) && (pb[2] == 100) && (pb[3] == 46)
      && (pb[4] == 100) && (pb[5] == 101) && (pb[6] == 98) && (pb[7] == 117)
      && (pb[8] == 103))) {
    return 1;
  }
  return 0;
}
/* wave661 Cap residual: hard-fail CALL arg types (G.7 ≡ typeck.x typeck_check_call_arg_types).
 * wave673: score<0 hard-fails even when arg_ty unknown (was soft-skip → BLD001).
 * wave685: free type-param formals on generic callee accept any present arg.
 * wave686: compound free formals *T/[]T/T[N]/Wrap<T> pre-score structural match.
 * 7.4.9: fmt/debug print any skip after score miss (twin typeck.x). */
int32_t typeck_check_call_arg_types(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t num_args = 0;
  int32_t fi = 0;
  int32_t dep = 0;
  struct ast_Module * mod = 0;
  struct ast_Module * dm = 0;
  int32_t ai = 0;
  int32_t param_raw = 0;
  int32_t sc = 0;
  int32_t arg_ref = 0;
  int32_t line_a = 0;
  int32_t col_a = 0;
  int32_t n_gp = 0;
  int32_t arg_ty = 0;
  if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
    return 0;
  }
  (void)((fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref)));
  if ((fi < 0)) {
    return 0;
  }
  (void)((num_args = pipeline_expr_call_num_args_at(arena, expr_ref)));
  (void)((dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref)));
  (void)((mod = module));
  if (((dep >=0) && (ctx !=0))) {
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep)));
    if ((dm !=0)) {
      (void)((mod = dm));
    }
  }
  (void)((n_gp = pipeline_module_func_num_generic_params_at(mod, fi)));
  (void)((ai = 0));
  while ((ai < num_args)) {
    (void)((param_raw = pipeline_module_func_param_type_ref_at(mod, fi, ai)));
    if ((param_raw > 0)) {
      (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, ai)));
      /* wave670: hard-fail null→non-ptr before score (exact 1000 can skip lit path). */
      if (((arg_ref > 0) && (typeck_expr_is_null_keyword(arena, arg_ref) != 0)
           && (pipeline_type_kind_ord_at(arena, param_raw) != 9))) {
        (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
        return -(1);
      }
      /* wave685: free type-param on generic callee — pre-score accept. */
      if (((n_gp > 0) && (typeck_type_is_free_type_param(mod, arena, param_raw) != 0))) {
        if ((arg_ref <= 0)) {
          (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
          (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
          (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
          return -(1);
        }
        (void)((ai = (ai + 1)));
        continue;
      }
      /* wave686: compound free formals pre-score structural match. */
      if (((n_gp > 0) && (arg_ref > 0))) {
        (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
        if ((((arg_ty > 0)
              && (typeck_type_tree_has_free_type_param(mod, arena, param_raw, 0) != 0))
             && (typeck_generic_formal_matches_arg_type(mod, arena, param_raw, arg_ty, 0) != 0))) {
          (void)((ai = (ai + 1)));
          continue;
        }
      }
      /* G.7 ≡ typeck.x: ARRAY_LIT → SIMD/array/slice formal before score. */
      if (arg_ref > 0) {
        (void)typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref, param_raw,
          pipeline_type_kind_ord_at(arena, param_raw),
          pipeline_expr_kind_ord_at(arena, arg_ref));
      }
      /* wave673: any score miss with known formal → T001 (unknown arg_ty no longer soft-skipped). */
      (void)((sc = typeck_overload_arg_param_score(arena, expr_ref, ai, param_raw, dep, ctx)));
      if ((sc < 0)) {
        /* Twin of typeck.x: fmt/debug print/println(composite) JSON any — not T001.
         * PLATFORM: SHARED typeck seed. */
        if ((typeck_call_is_fmt_debug_print_any(mod, fi, dep, ctx, num_args) != 0)) {
          (void)((ai = (ai + 1)));
          continue;
        }
        (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
        return -(1);
      }
    }
    (void)((ai = (ai + 1)));
  }
  return 0;
}
int32_t typeck_check_expr_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if ((pipeline_typeck_check_extern_call_unsafe_boundary_c(module, arena, expr_ref, ctx) !=0)) {
    return -(1);
  }
  int32_t num_args = pipeline_expr_call_num_args_at(arena, expr_ref);
  if ((typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, 0, num_args) !=0)) {
    return -(1);
  }
  if ((typeck_check_expr_call_resolve(module, arena, expr_ref, ctx) !=0)) {
    return -(1);
  }
  if ((typeck_check_call_arity(module, arena, expr_ref, ctx) !=0)) {
    return -(1);
  }
  if ((typeck_check_call_arg_types(module, arena, expr_ref, ctx) !=0)) {
    return -(1);
  }
  if ((pipeline_typeck_check_call_slice_region_c(module, arena, expr_ref, ctx) !=0)) {
    return -(1);
  }
  return 0;
}

/* wave657 Cap residual: return 1 if ty cannot be scalar ==/!=/relational operand.
 * PLATFORM: SHARED — G.7 ≡ typeck.x typeck_type_is_aggregate_cmp_operand. */
int32_t typeck_type_is_aggregate_cmp_operand(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  int32_t ord_named = 8;
  int32_t ord_array = 10;
  int32_t ord_slice = 11;
  int32_t ord_linear = 12;
  int32_t ord_vector = 13;
  int32_t ko = 0;
  int32_t rty = 0;
  uint8_t nm[128];
  int32_t nlen = 0;
  int32_t nlayouts = 0;
  int32_t k = 0;
  if ((module == 0) || (arena == 0) || ast_ref_is_null(ty_ref)) {
    return 0;
  }
  rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
  if (ast_ref_is_null(rty)) {
    rty = ty_ref;
  }
  ko = pipeline_type_kind_ord_at(arena, rty);
  if ((ko == ord_array) || (ko == ord_slice) || (ko == ord_linear) || (ko == ord_vector)) {
    return 1;
  }
  if (ko != ord_named) {
    return 0;
  }
  nlen = pipeline_type_named_name_into(arena, rty, &nm[0]);
  if ((nlen <= 0) || (nlen > 127)) {
    return 0;
  }
  nlayouts = pipeline_module_num_struct_layouts_at(module);
  k = 0;
  while (k < nlayouts) {
    if (typeck_layout_name_equal(module, k, &nm[0], nlen)) {
      return 1;
    }
    k = k + 1;
  }
  return 0;
}

/* Defect D / 9.6.1 residual: C integer promotions for compare (G.7 ≡ typeck.x).
 * Sub-int (u8 / NAMED i8,i16,u16) that true-widen to i32 are stamped to i32.
 * i32 vs i64 / u32 vs i32 stay mismatch (wave666). PLATFORM: SHARED. */
int32_t typeck_cmp_promote_subint_to_i32(struct ast_ASTArena * arena, int32_t expr_ref, int32_t ty_ref) {
  int32_t fam = 0;
  int32_t i32t = 0;
  if (((arena == 0) || ast_ref_is_null(ty_ref)) || (ty_ref <= 0) || (expr_ref <= 0)) {
    return 0;
  }
  fam = typeck_int_family_id(arena, ty_ref);
  if ((fam == 0) || (fam < 0)) {
    return 0;
  }
  i32t = ensure_i32_type_ref(arena);
  if (i32t <= 0) {
    return 0;
  }
  if (typeck_integer_widen_ok_refs(arena, i32t, ty_ref)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32t));
    return 1;
  }
  return 0;
}

int32_t typeck_check_expr_binop_cmp(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t bop_l = pipeline_expr_binop_left_ref_at(arena, expr_ref);
  int32_t bop_r = pipeline_expr_binop_right_ref_at(arena, expr_ref);
  int32_t bt = 0;
  int32_t lt_cmp = 0;
  int32_t rt_cmp = 0;
  int32_t lko_cmp = 0;
  int32_t rko_cmp = 0;
  int32_t lk_cmp = 0;
  int32_t rk_cmp = 0;
  int32_t ord_f32 = 14;
  int32_t ord_logand = 20;
  int32_t ord_logor = 21;
  int32_t expr_kind_cmp = 0;
  int32_t is_logical = 0;
  int32_t line_ac = 0;
  int32_t col_ac = 0;
  if ((check_expr(module, arena, bop_l, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((check_expr(module, arena, bop_r, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  (void)((expr_kind_cmp = pipeline_expr_kind_ord_at(arena, expr_ref)));
  if (((expr_kind_cmp ==ord_logand) || (expr_kind_cmp ==ord_logor))) {
    (void)((is_logical = 1));
  }
  (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
  (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
  /* wave665 Cap residual: LOGAND/LOGOR operands must be bool (G.7 ≡ typeck.x). */
  if ((is_logical != 0)) {
    if (((!(ast_ref_is_null(lt_cmp)) && (lt_cmp > 0)) && (lt_cmp <=(arena->num_types)))) {
      if (!(type_ref_is_bool(arena, lt_cmp))) {
        (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac));
        return -(1);
      }
    }
    if (((!(ast_ref_is_null(rt_cmp)) && (rt_cmp > 0)) && (rt_cmp <=(arena->num_types)))) {
      if (!(type_ref_is_bool(arena, rt_cmp))) {
        (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac));
        return -(1);
      }
    }
    (void)((bt = ensure_bool_type_ref(arena)));
    if ((bt !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
    }
    return 0;
  }
  /* wave317: f32 peer + bare FLOAT_LIT / -float in cmp (G.7 ≡ typeck.x). */
  if ((!(ast_ref_is_null(lt_cmp)) && !(ast_ref_is_null(rt_cmp)))) {
    (void)((lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp)));
    (void)((rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp)));
    (void)((lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l)));
    (void)((rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r)));
    if ((lko_cmp ==ord_f32)) {
      (void)(typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_cmp, ord_f32, rk_cmp));
    } else {
      if ((rko_cmp ==ord_f32)) {
        (void)(typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_cmp, ord_f32, lk_cmp));
      }
    }
    /* wave657 Cap residual: hard-fail aggregate ==/!=/relational (G.7 ≡ typeck.x). */
    if ((typeck_type_is_aggregate_cmp_operand(module, arena, lt_cmp) != 0)
        || (typeck_type_is_aggregate_cmp_operand(module, arena, rt_cmp) != 0)) {
      (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_ac, col_ac));
      return -(1);
    }
    /* wave666 Cap residual: hard-fail mixed-type comparison (G.7 ≡ typeck.x).
     * Defect D: C integer promotions (sub-int → i32) before equal check. */
    (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
    (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
    if ((!(ast_ref_is_null(lt_cmp)) && !(ast_ref_is_null(rt_cmp)))) {
      int32_t ord_lit = 0;
      (void)((lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp)));
      (void)((rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp)));
      (void)((lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l)));
      (void)((rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r)));
      if (((rk_cmp == ord_lit)
           && (typeck_coerce_init_lit_to_decl(arena, bop_r, lt_cmp, lko_cmp, rk_cmp) != 0))) {
        (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
      } else {
        if (((lk_cmp == ord_lit)
             && (typeck_coerce_init_lit_to_decl(arena, bop_l, rt_cmp, rko_cmp, lk_cmp) != 0))) {
          (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
        }
      }
      if (((((lt_cmp > 0) && (rt_cmp > 0)) && (lt_cmp <= (arena->num_types)))
           && (rt_cmp <= (arena->num_types)))) {
        if (!(type_refs_equal(arena, lt_cmp, rt_cmp))) {
          if ((typeck_cmp_promote_subint_to_i32(arena, bop_l, lt_cmp) != 0)) {
            (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
          }
          if ((typeck_cmp_promote_subint_to_i32(arena, bop_r, rt_cmp) != 0)) {
            (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
          }
        }
        if (!(type_refs_equal(arena, lt_cmp, rt_cmp))) {
          (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
          (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
          (void)(driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac));
          return -(1);
        }
      }
    }
  }
  (void)((bt = ensure_bool_type_ref(arena)));
  if ((bt !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
  }
  return 0;
}
int32_t typeck_check_expr_binop_arith(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_lit = 0;
  int32_t bop_l = pipeline_expr_binop_left_ref_at(arena, expr_ref);
  int32_t bop_r = pipeline_expr_binop_right_ref_at(arena, expr_ref);
  int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
  int32_t lk_expr = 0;
  int32_t rk_expr = 0;
  int32_t lt_ar = 0;
  int32_t rt_ar = 0;
  int32_t lko = 0;
  int32_t rko = 0;
  int32_t out_ar = 0;
  int32_t allow_i32_fallback = 0;
  uint8_t * dbg_left = ((uint8_t *)(0));
  uint8_t * dbg_right = ((uint8_t *)(0));
  int32_t dbg_left_len = 0;
  int32_t dbg_right_len = 0;
  int32_t ord_type_vector = 13;
  int32_t ord_i64 = 5;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t ord_void = 16;
  int32_t ord_bool = 1;
  int32_t ord_i32 = 0;
  int32_t ord_ptr = 9;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  int32_t ord_add = 4;
  int32_t ord_sub = 5;
  int32_t ord_mod = 8;
  int32_t ord_shl = 9;
  int32_t ord_shr = 10;
  int32_t ord_bitand = 11;
  int32_t ord_bitor = 12;
  int32_t ord_bitxor = 13;
  if ((check_expr(module, arena, bop_l, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((check_expr(module, arena, bop_r, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  (void)((lt_ar = pipeline_expr_resolved_type_ref(arena, bop_l)));
  (void)((rt_ar = pipeline_expr_resolved_type_ref(arena, bop_r)));
  if ((!(ast_ref_is_null(lt_ar)) && !(ast_ref_is_null(rt_ar)))) {
    (void)((lk_expr = pipeline_expr_kind_ord_at(arena, bop_l)));
    (void)((rk_expr = pipeline_expr_kind_ord_at(arena, bop_r)));
    (void)((dbg_left = driver_typeck_diag_scratch_expect()));
    (void)((dbg_right = driver_typeck_diag_scratch_found()));
    (void)((dbg_left_len = typeck_diag_fmt_type_or_question(arena, lt_ar, dbg_left)));
    (void)((dbg_right_len = typeck_diag_fmt_type_or_question(arena, rt_ar, dbg_right)));
    (void)(driver_diagnostic_typeck_binop_operands(expr_ref, bop_l, bop_r, lk_expr, rk_expr, pipeline_expr_block_ref_at(arena, bop_l), pipeline_expr_block_ref_at(arena, bop_r), lt_ar, rt_ar, dbg_left, dbg_left_len, dbg_right, dbg_right_len));
    (void)((lko = pipeline_type_kind_ord_at(arena, lt_ar)));
    (void)((rko = pipeline_type_kind_ord_at(arena, rt_ar)));
    /* wave667 Cap residual: hard-fail void arithmetic (G.7 ≡ typeck.x). */
    if (((lko == ord_void) || (rko == ord_void))) {
      int32_t line_vb = pipeline_expr_line_at(arena, expr_ref);
      int32_t col_vb = pipeline_expr_col_at(arena, expr_ref);
      (void)(driver_diagnostic_typeck_invalid_void_binop(line_vb, col_vb));
      return -(1);
    }
    /* wave677 Cap residual: hard-fail bool arithmetic/bitops/shifts (G.7 ≡ typeck.x). */
    if (((lko == ord_bool) || (rko == ord_bool))) {
      int32_t line_bb = pipeline_expr_line_at(arena, expr_ref);
      int32_t col_bb = pipeline_expr_col_at(arena, expr_ref);
      (void)(driver_diagnostic_typeck_invalid_bool_binop(line_bb, col_bb));
      return -(1);
    }
    if (((expr_kind ==ord_add) || (expr_kind ==ord_sub))) {
      if (((lko ==ord_ptr) && (((rko ==ord_i32) || (rko ==ord_usize)) || (rko ==ord_isize)))) {
        (void)((out_ar = lt_ar));
      } else {
        if ((((expr_kind ==ord_add) && (rko ==ord_ptr)) && (((lko ==ord_i32) || (lko ==ord_usize)) || (lko ==ord_isize)))) {
          (void)((out_ar = rt_ar));
        }
      }
    }
    /* wave285 Cap residual: hard-fail illegal pointer arithmetic (G.7 ≡ typeck.x). */
    if (((lko ==ord_ptr) || (rko ==ord_ptr))) {
      int32_t line_pb = pipeline_expr_line_at(arena, expr_ref);
      int32_t col_pb = pipeline_expr_col_at(arena, expr_ref);
      if ((expr_kind ==ord_add)) {
        if (!(ast_ref_is_null(out_ar))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
          return 0;
        }
        (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
        return -(1);
      }
      if ((expr_kind ==ord_sub)) {
        if (((lko ==ord_ptr) && (rko ==ord_ptr))) {
          (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_isize)));
          (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
          return 0;
        }
        if (!(ast_ref_is_null(out_ar))) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
          return 0;
        }
        (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
        return -(1);
      }
      (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
      return -(1);
    }
    /* wave286 Cap residual: hard-fail illegal float bitop/mod/shift (G.7 ≡ typeck.x). */
    if ((((lko ==ord_f32) || (lko ==ord_f64)) || (rko ==ord_f32)) || (rko ==ord_f64)) {
      if ((((((expr_kind ==ord_mod) || (expr_kind ==ord_shl)) || (expr_kind ==ord_shr)) || (expr_kind ==ord_bitand)) || (expr_kind ==ord_bitor)) || (expr_kind ==ord_bitxor)) {
        int32_t line_fb = pipeline_expr_line_at(arena, expr_ref);
        int32_t col_fb = pipeline_expr_col_at(arena, expr_ref);
        (void)(driver_diagnostic_typeck_invalid_float_binop(line_fb, col_fb));
        return -(1);
      }
    }
    /* wave658 Cap residual: hard-fail aggregate arith (G.7 ≡ typeck.x).
     * VECTOR same-size pair still allowed below. */
    if ((((typeck_type_is_aggregate_cmp_operand(module, arena, lt_ar) != 0)
          || (typeck_type_is_aggregate_cmp_operand(module, arena, rt_ar) != 0))
         && !((lko == ord_type_vector) && (rko == ord_type_vector)))) {
      int32_t line_aa = pipeline_expr_line_at(arena, expr_ref);
      int32_t col_aa = pipeline_expr_col_at(arena, expr_ref);
      (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_aa, col_aa));
      return -(1);
    }
    if (ast_ref_is_null(out_ar)) {
      if (((((((((lko ==ord_i32) || (lko ==ord_u8)) || (lko ==ord_u32)) || (lko ==ord_u64)) || (lko ==ord_i64)) || (lko ==ord_usize)) || (lko ==ord_isize)) && (((((((rko ==ord_i32) || (rko ==ord_u8)) || (rko ==ord_u32)) || (rko ==ord_u64)) || (rko ==ord_i64)) || (rko ==ord_usize)) || (rko ==ord_isize)))) {
        if (((expr_kind ==ord_shl) || (expr_kind ==ord_shr))) {
          (void)((out_ar = lt_ar));
        } else {
          if (((((expr_kind ==ord_bitand) || (expr_kind ==ord_bitor)) || (expr_kind ==ord_bitxor)) || (expr_kind ==ord_mod))) {
            if (((rk_expr ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_r, lt_ar, lko, rk_expr) !=0))) {
              (void)((out_ar = lt_ar));
            } else {
              if (((lk_expr ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_l, rt_ar, rko, lk_expr) !=0))) {
                (void)((out_ar = rt_ar));
              }
            }
          }
        }
      }
    }
    if (ast_ref_is_null(out_ar)) {
      if (((((lko ==ord_type_vector) && (rko ==ord_type_vector)) && (pipeline_type_array_size_at(arena, lt_ar) ==pipeline_type_array_size_at(arena, rt_ar))) && type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_ar), pipeline_type_elem_ref_at(arena, rt_ar)))) {
        (void)((out_ar = lt_ar));
      } else {
        if (((lko ==ord_i64) || (rko ==ord_i64))) {
          (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i64)));
        } else {
          /* wave317: f32 + bare FLOAT_LIT / -float stays f32 before f64 usual-arith.
           * G.7 ≡ typeck.x typeck_coerce_init_float_lit_to_decl (wave316). */
          if (((lko ==ord_f32) && (typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_ar, ord_f32, rk_expr) !=0))) {
            (void)((out_ar = lt_ar));
          } else {
          if (((rko ==ord_f32) && (typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_ar, ord_f32, lk_expr) !=0))) {
            (void)((out_ar = rt_ar));
          } else {
          /* wave296 Cap residual: f64 before f32 (usual arithmetic conversion).
           * f32*f64 must resolve as f64 — not f32. G.7 ≡ typeck.x / typeck_gen / ast_pool. */
          if (((lko ==ord_f64) || (rko ==ord_f64))) {
            (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f64)));
          } else {
            if (((lko ==ord_f32) || (rko ==ord_f32))) {
              (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f32)));
            } else {
              if (type_refs_equal(arena, lt_ar, rt_ar)) {
                (void)((out_ar = lt_ar));
              } else {
                if (typeck_integer_widen_ok_refs(arena, lt_ar, rt_ar)) {
                  (void)((out_ar = lt_ar));
                } else {
                  if (typeck_integer_widen_ok_refs(arena, rt_ar, lt_ar)) {
                    (void)((out_ar = rt_ar));
                  } else {
                    if (((lk_expr ==ord_lit) && (rk_expr !=ord_lit))) {
                      (void)((out_ar = rt_ar));
                    } else {
                      if (((rk_expr ==ord_lit) && (lk_expr !=ord_lit))) {
                        (void)((out_ar = lt_ar));
                      } else {
                        if (!(ast_ref_is_null(lt_ar))) {
                          (void)((out_ar = lt_ar));
                        } else {
                          if (!(ast_ref_is_null(rt_ar))) {
                            (void)((out_ar = rt_ar));
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          }
          }
        }
      }
    }
    if (((expr_kind >=4) && (expr_kind <=13))) {
      (void)((allow_i32_fallback = 1));
    }
    if ((((ast_ref_is_null(out_ar) && (lko !=ord_type_vector)) && (rko !=ord_type_vector)) && (allow_i32_fallback !=0))) {
      (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i32)));
    }
    /* wave677: bool→i32 arith promotion removed (hard-fail above). LANG-006 let/const only. */
    if (!(ast_ref_is_null(out_ar))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
    }
  }
  return 0;
}
int32_t typeck_check_expr_binop(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_eq = 14;
  int32_t ord_ne = 15;
  int32_t ord_lt = 16;
  int32_t ord_le = 17;
  int32_t ord_gt = 18;
  int32_t ord_ge = 19;
  int32_t ord_logand = 20;
  int32_t ord_logor = 21;
  int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
  if (((((((((expr_kind ==ord_eq) || (expr_kind ==ord_ne)) || (expr_kind ==ord_lt)) || (expr_kind ==ord_le)) || (expr_kind ==ord_gt)) || (expr_kind ==ord_ge)) || (expr_kind ==ord_logand)) || (expr_kind ==ord_logor))) {
    return typeck_check_expr_binop_cmp(module, arena, expr_ref, return_type_ref, ctx);
  }
  return typeck_check_expr_binop_arith(module, arena, expr_ref, return_type_ref, ctx);
}
int32_t typeck_check_expr_field_access(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return pipeline_typeck_check_expr_field_access_c(module, arena, expr_ref, return_type_ref, ctx);
}
/* wave289 Cap residual: G.7 ≡ typeck.x typeck_check_expr_unary — hard-fail ~float/~ptr/-ptr.
 * wave662 Cap residual: hard-fail unary -/~/! on aggregates (reuse typeck_type_is_aggregate_cmp_operand). */
int32_t typeck_check_expr_unary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_neg = 22;
  int32_t ord_bitnot = 23;
  int32_t ord_lognot = 24;
  int32_t ord_ptr = 9;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
  int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
  int32_t op_tr = 0;
  int32_t bt = 0;
  int32_t op_ko = 0;
  int32_t line_u = 0;
  int32_t col_u = 0;
  if ((check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  (void)((op_tr = expr_type_ref(arena, op_ref)));
  /* wave662: hard-fail aggregate operands for -/~/! before LOGNOT stamps bool. */
  if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=(arena->num_types)))) {
    if ((typeck_type_is_aggregate_cmp_operand(module, arena, op_tr) != 0)) {
      (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_u, col_u));
      return -(1);
    }
  }
  if ((expr_kind ==ord_lognot)) {
    /* wave665 Cap residual: LOGNOT operand must be bool (G.7 ≡ typeck.x). */
    if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=(arena->num_types)))) {
      if (!(type_ref_is_bool(arena, op_tr))) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_u, col_u));
        return -(1);
      }
    }
    (void)((bt = ensure_bool_type_ref(arena)));
    if ((bt !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
    }
    return 0;
  }
  if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=(arena->num_types)))) {
    (void)((op_ko = pipeline_type_kind_ord_at(arena, op_tr)));
    /* wave667 Cap residual: hard-fail unary -/~ on void (G.7 ≡ typeck.x). */
    if ((((expr_kind == ord_neg) || (expr_kind == ord_bitnot)) && (op_ko == 16))) {
      (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_invalid_void_binop(line_u, col_u));
      return -(1);
    }
    /* wave677 Cap residual: hard-fail unary -/~ on bool (G.7 ≡ typeck.x). */
    if ((((expr_kind == ord_neg) || (expr_kind == ord_bitnot)) && (op_ko == 1))) {
      (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_invalid_bool_binop(line_u, col_u));
      return -(1);
    }
    if ((expr_kind ==ord_bitnot)) {
      if (((op_ko ==ord_f32) || (op_ko ==ord_f64))) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_float_binop(line_u, col_u));
        return -(1);
      }
      if ((op_ko ==ord_ptr)) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u));
        return -(1);
      }
    }
    if (((expr_kind ==ord_neg) && (op_ko ==ord_ptr))) {
      (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u));
      return -(1);
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, op_tr));
  }
  return 0;
}
int32_t typeck_check_expr_addr_of(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
  int32_t op_ty = 0;
  int32_t pt = 0;
  if (!(ast_ref_is_null(op_ref))) {
    if ((pipeline_typeck_reject_addr_of_linear_c(arena, op_ref, expr_ref, module, ctx) !=0)) {
      return -(1);
    }
    if ((check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      return -(1);
    }
  }
  (void)((op_ty = expr_type_ref(arena, op_ref)));
  if (((ast_ref_is_null(op_ty) || (op_ty <=0)) || (op_ty > (arena->num_types)))) {
    return -(1);
  }
  (void)((pt = pipeline_typeck_ptr_for_addr_of_operand_c(arena, op_ref, op_ty, module, ctx)));
  if ((pt ==0)) {
    (void)((pt = find_or_alloc_ptr_type_ref(arena, op_ty)));
  }
  if ((pt ==0)) {
    return -(1);
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, pt));
  return 0;
}
int32_t typeck_check_expr_deref(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if ((pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) <=0)) {
    int32_t line = pipeline_expr_line_at(arena, expr_ref);
    int32_t col = pipeline_expr_col_at(arena, expr_ref);
    (void)(driver_diagnostic_typeck_deref_outside_unsafe(line, col));
    return -(1);
  }
  int32_t ord_ptr = 9;
  int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
  int32_t op_ptr = 0;
  int32_t elem_ty = 0;
  if (!(ast_ref_is_null(op_ref))) {
    if ((check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      return -(1);
    }
  }
  (void)((op_ptr = expr_type_ref(arena, op_ref)));
  if (((ast_ref_is_null(op_ptr) || (op_ptr <=0)) || (op_ptr > (arena->num_types)))) {
    return -(1);
  }
  if ((pipeline_type_kind_ord_at(arena, op_ptr) !=ord_ptr)) {
    return -(1);
  }
  (void)((elem_ty = pipeline_type_elem_ref_at(arena, op_ptr)));
  if (ast_ref_is_null(elem_ty)) {
    return -(1);
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty));
  return 0;
}
int32_t typeck_check_expr_var_top_level(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * vbuf, int32_t vnlen, int32_t tl) {
  int32_t tl_tr = 0;
  if ((tl >=(module->num_top_level_lets))) {
    return 0;
  }
  if (typeck_top_level_let_name_equal(module, tl, vbuf, vnlen)) {
    (void)((tl_tr = pipeline_module_top_level_let_type_ref(module, tl)));
    if (!(ast_ref_is_null(tl_tr))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tl_tr));
      return 1;
    }
  }
  return typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, (tl + 1));
}
int32_t typeck_check_expr_var(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t vnlen = 0;
  uint8_t * vbuf = typeck_scratch64_slot(0);
  uint8_t * hint_buf = typeck_scratch64_slot(13);
  int32_t vd_tr = 0;
  int32_t block_ref = 0;
  int32_t func_ix = 0;
  int32_t pr = 0;
  int32_t tk_tr = 0;
  int32_t tg_tr = 0;
  int32_t const_dep_ix = -(1);
  int32_t hint_len = 0;
  int32_t line = 0;
  int32_t col = 0;
  uint8_t nm_tok_kind[9] = {84, 111, 107, 101, 110, 75, 105, 110, 100};
  uint8_t nm_typ_kind[8] = {84, 121, 112, 101, 75, 105, 110, 100};
  if ((((((arena ==((struct ast_ASTArena *)(0))) || (module ==((struct ast_Module *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0)))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((vnlen = pipeline_expr_var_name_len(arena, expr_ref)));
  if (((vnlen <=0) || (vnlen > 127))) {
    return -(1);
  }
  (void)(pipeline_expr_var_name_into(arena, expr_ref, vbuf));
  (void)((block_ref = pipeline_dep_ctx_current_block_ref_at(ctx)));
  (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 99, pipeline_expr_resolved_type_ref(arena, expr_ref)));
  if (((block_ref !=0) && (block_ref <=(arena->num_blocks)))) {
    (void)((vd_tr = pipeline_block_resolve_var_type_ref(arena, block_ref, vbuf, vnlen)));
    if ((vd_tr !=0)) {
      (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 1, vd_tr));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, vd_tr));
      if ((pipeline_typeck_linear_use_var_c(arena, vd_tr, expr_ref, vbuf, vnlen) !=0)) {
        return -(1);
      }
      return 0;
    }
  }
  (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
  if (((func_ix >=0) && (func_ix < (module->num_funcs)))) {
    (void)((pr = pipeline_module_func_param_type_ref_for_name(module, func_ix, vbuf, vnlen)));
    if ((pr !=0)) {
      (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 2, pr));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, pr));
      if ((pipeline_typeck_linear_use_var_c(arena, pr, expr_ref, vbuf, vnlen) !=0)) {
        return -(1);
      }
      return 0;
    }
  }
  (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 100, pipeline_expr_resolved_type_ref(arena, expr_ref)));
  if (((module->num_top_level_lets) > 0)) {
    if ((typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, 0) !=0)) {
      (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 101, pipeline_expr_resolved_type_ref(arena, expr_ref)));
      return 0;
    }
  }
  (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 102, pipeline_expr_resolved_type_ref(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 104, pipeline_expr_resolved_type_ref(arena, expr_ref)));
  if (((vnlen ==9) && name_equal(vbuf, vnlen, &((nm_tok_kind)[0]), 9))) {
    (void)((tk_tr = find_or_alloc_named_type_ref(arena, &((nm_tok_kind)[0]), 9)));
    if ((tk_tr !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tk_tr));
      return 0;
    }
  }
  if (((vnlen ==8) && name_equal(vbuf, vnlen, &((nm_typ_kind)[0]), 8))) {
    (void)((tg_tr = find_or_alloc_named_type_ref(arena, &((nm_typ_kind)[0]), 8)));
    if ((tg_tr !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tg_tr));
      return 0;
    }
  }
  if (typeck_var_is_import_visible_name(module, vbuf, vnlen)) {
    return 0;
  }
  (void)((const_dep_ix = typeck_find_import_const_dep_index(module, ctx, vbuf, vnlen, 0)));
  if ((const_dep_ix >=0)) {
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)((hint_len = typeck_import_const_binding_hint_at(module, const_dep_ix, hint_buf)));
    (void)(driver_diagnostic_typeck_import_const_must_be_qualified(line, col, vbuf, vnlen, hint_buf, hint_len));
    return -(1);
  }
  if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
    return -(1);
  }
  return 0;
}
int32_t typeck_check_expr_method_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args) {
  int32_t arg_ref = 0;
  if ((arg_i >=num_args)) {
    return 0;
  }
  (void)((arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i)));
  if ((check_expr(module, arena, arg_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  return typeck_check_expr_method_call_arg(module, arena, expr_ref, return_type_ref, ctx, (arg_i + 1), num_args);
}
int32_t typeck_check_expr_method_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return pipeline_typeck_check_expr_method_call_c(module, arena, expr_ref, return_type_ref, ctx);
}
/* wave659 Cap residual: cast-eligible type class for `as` (G.7 ≡ typeck.x). */
int32_t typeck_as_cast_type_class_ok(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  int32_t ord_bool = 1;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t ord_void = 16;
  int32_t ko = 0;
  int32_t rty = 0;
  if ((module == 0) || (arena == 0) || ast_ref_is_null(ty_ref)) {
    return 0;
  }
  if (typeck_type_is_aggregate_cmp_operand(module, arena, ty_ref) != 0) {
    return 0;
  }
  rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
  if (ast_ref_is_null(rty)) {
    rty = ty_ref;
  }
  ko = pipeline_type_kind_ord_at(arena, rty);
  if (ko == ord_void) {
    return 0;
  }
  if ((ko == ord_bool) || (ko == ord_ptr) || (ko == ord_f32) || (ko == ord_f64)) {
    return 1;
  }
  if (typeck_int_family_id(arena, rty) >= 0) {
    return 1;
  }
  if (ko == ord_named) {
    return 1;
  }
  return 0;
}

/* wave659 Cap residual: legal `src as tgt` gate (G.7 ≡ typeck.x). */
int32_t typeck_as_cast_allowed(struct ast_Module * module, struct ast_ASTArena * arena, int32_t src_ty, int32_t tgt_ty) {
  int32_t ord_bool = 1;
  int32_t ord_named = 8;
  int32_t ord_ptr = 9;
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  int32_t sk = 0;
  int32_t tk = 0;
  int32_t s_int = 0;
  int32_t t_int = 0;
  int32_t s_float = 0;
  int32_t t_float = 0;
  int32_t s_num = 0;
  int32_t t_num = 0;
  int32_t src_r = 0;
  int32_t tgt_r = 0;
  if ((module == 0) || (arena == 0)) {
    return 0;
  }
  if (ast_ref_is_null(src_ty) || ast_ref_is_null(tgt_ty)) {
    return 0;
  }
  if ((typeck_as_cast_type_class_ok(module, arena, src_ty) == 0)
      || (typeck_as_cast_type_class_ok(module, arena, tgt_ty) == 0)) {
    return 0;
  }
  src_r = typeck_resolve_type_alias_ref_local(module, arena, src_ty, 0);
  if (ast_ref_is_null(src_r)) {
    src_r = src_ty;
  }
  tgt_r = typeck_resolve_type_alias_ref_local(module, arena, tgt_ty, 0);
  if (ast_ref_is_null(tgt_r)) {
    tgt_r = tgt_ty;
  }
  if (type_refs_equal(arena, src_r, tgt_r)) {
    return 1;
  }
  sk = pipeline_type_kind_ord_at(arena, src_r);
  tk = pipeline_type_kind_ord_at(arena, tgt_r);
  s_int = 0;
  t_int = 0;
  if ((typeck_int_family_id(arena, src_r) >= 0) || (sk == ord_bool) || (sk == ord_named)) {
    s_int = 1;
  }
  if ((typeck_int_family_id(arena, tgt_r) >= 0) || (tk == ord_bool) || (tk == ord_named)) {
    t_int = 1;
  }
  s_float = 0;
  t_float = 0;
  if ((sk == ord_f32) || (sk == ord_f64)) {
    s_float = 1;
  }
  if ((tk == ord_f32) || (tk == ord_f64)) {
    t_float = 1;
  }
  if (((s_float != 0) && (tk == ord_ptr)) || ((t_float != 0) && (sk == ord_ptr))) {
    return 0;
  }
  s_num = 0;
  t_num = 0;
  if ((s_int != 0) || (s_float != 0)) {
    s_num = 1;
  }
  if ((t_int != 0) || (t_float != 0)) {
    t_num = 1;
  }
  if ((s_num != 0) && (t_num != 0)) {
    return 1;
  }
  if (((s_int != 0) && (tk == ord_ptr)) || ((t_int != 0) && (sk == ord_ptr))) {
    return 1;
  }
  if ((sk == ord_ptr) && (tk == ord_ptr)) {
    return 1;
  }
  return 0;
}

int32_t typeck_check_expr_as(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t op_ref = pipeline_expr_as_operand_ref_at(arena, expr_ref);
  int32_t tgt = pipeline_expr_as_target_type_ref_at(arena, expr_ref);
  int32_t src_ty = 0;
  int32_t line_as = 0;
  int32_t col_as = 0;
  if ((!(ast_ref_is_null(op_ref)) && (check_expr(module, arena, op_ref, 0, ctx) !=0))) {
    return -(1);
  }
  /* wave659 Cap residual: hard-fail illegal `as` at typeck (G.7 ≡ typeck.x). */
  if ((!(ast_ref_is_null(op_ref))) && (!(ast_ref_is_null(tgt)))) {
    src_ty = pipeline_expr_resolved_type_ref(arena, op_ref);
    if ((!(ast_ref_is_null(src_ty))) && (typeck_as_cast_allowed(module, arena, src_ty, tgt) == 0)) {
      line_as = pipeline_expr_line_at(arena, expr_ref);
      col_as = pipeline_expr_col_at(arena, expr_ref);
      (void)(driver_diagnostic_typeck_invalid_as_cast(line_as, col_as));
      return -(1);
    }
  }
  if (!(ast_ref_is_null(tgt))) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tgt));
  }
  return 0;
}
int32_t typeck_check_expr_struct_lit_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t field_i, int32_t num_fields) {
  int32_t init_sl = 0;
  int32_t no_expected = 0;
  /* PLATFORM: SHARED — do not pass outer function return as field expected type. */
  (void)return_type_ref;
  if ((field_i >=num_fields)) {
    return 0;
  }
  (void)((init_sl = pipeline_expr_struct_lit_init_ref(arena, expr_ref, field_i)));
  if ((!(ast_ref_is_null(init_sl)) && (check_expr(module, arena, init_sl, no_expected, ctx) !=0))) {
    return -(1);
  }
  return typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx, (field_i + 1), num_fields);
}
extern int32_t pipeline_typeck_mono_field_type_from_base_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t field_ty, int32_t base_ty);
int32_t typeck_coerce_struct_lit_field_inits_to_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty) {
  int32_t num_fields = 0;
  int32_t name_len = 0;
  int32_t j = 0;
  int32_t flen = 0;
  int32_t init_r = 0;
  int32_t ftr = 0;
  uint8_t * name_buf = typeck_scratch64_slot(4);
  uint8_t * field_buf = typeck_scratch64_slot(5);
  if (((expr_ref <=0) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref)));
  (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
  if ((((num_fields <=0) || (name_len <=0)) || (name_len > 127))) {
    return 0;
  }
  (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, name_buf));
  while ((j < num_fields)) {
    (void)((flen = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j)));
    if (((flen > 0) && (flen <=63))) {
      (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_buf));
      (void)((ftr = get_field_type_ref_from_layout(module, name_buf, name_len, field_buf, flen)));
      (void)((init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j)));
      if (((((!(ast_ref_is_null(init_r)) && (init_r > 0)) && (init_r <=(arena->num_exprs))) && !(ast_ref_is_null(ftr))) && (ftr > 0))) {
        /* wave682: mono free type-param field types from expected base. */
        if (base_ty > 0) {
          int32_t ftr_mono = pipeline_typeck_mono_field_type_from_base_c(module, arena, ftr, base_ty);
          if (ftr_mono > 0) {
            ftr = ftr_mono;
          }
        }
        (void)(typeck_coerce_init_expr_to_decl(module, arena, init_r, ftr));
      }
    }
    (void)((j = (j + 1)));
  }
  return 0;
}
int32_t typeck_check_expr_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref);
  int32_t name_len = 0;
  uint8_t name_buf[128] = {};
  int32_t tr = 0;
  int32_t ord_named = 8;
  if ((typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx, 0, num_fields) !=0)) {
    return -(1);
  }
  (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
  if ((name_len <=0)) {
    if ((!(ast_ref_is_null(return_type_ref)) && (pipeline_type_kind_ord_at(arena, return_type_ref) ==ord_named))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
    }
    return 0;
  }
  if ((ensure_struct_layout_from_struct_lit(module, arena, expr_ref) !=0)) {
    return -(1);
  }
  (void)(typeck_coerce_struct_lit_field_inits_to_layout(module, arena, expr_ref, return_type_ref));
  if ((name_len > 127)) {
    return 0;
  }
  (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, &((name_buf)[0])));
  (void)((tr = find_or_alloc_named_type_ref(arena, &((name_buf)[0]), name_len)));
  if ((tr !=0)) {
    if (((!(ast_ref_is_null(return_type_ref)) && (pipeline_type_kind_ord_at(arena, return_type_ref) ==ord_named)) && typeck_named_type_matches_name_or_alias(module, arena, return_type_ref, &((name_buf)[0]), name_len, 0))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
    } else {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tr));
    }
  }
  return 0;
}
/* wave664 Cap residual: G.7 ≡ typeck.x typeck_type_is_valid_subscript_index. */
int32_t typeck_type_is_valid_subscript_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  int32_t ord_i32 = 0;
  int32_t ord_bool = 1;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  int32_t ord_named = 8;
  int32_t rty = 0;
  int32_t ko = 0;
  if ((arena == 0) || ast_ref_is_null(ty_ref) || (ty_ref <= 0)) {
    return 1;
  }
  rty = ty_ref;
  if (module != 0) {
    rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
    if (ast_ref_is_null(rty) || (rty <= 0)) {
      rty = ty_ref;
    }
  }
  ko = pipeline_type_kind_ord_at(arena, rty);
  if ((ko == ord_i32) || (ko == ord_u8) || (ko == ord_u32) || (ko == ord_u64)
      || (ko == ord_i64) || (ko == ord_usize) || (ko == ord_isize)) {
    return 1;
  }
  if (ko == ord_named) {
    if (typeck_type_is_aggregate_cmp_operand(module, arena, rty) != 0) {
      return 0;
    }
    return 1;
  }
  if (ko == ord_bool) {
    return 0;
  }
  return 0;
}
int32_t typeck_check_expr_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_lit = 0;
  int32_t ord_ptr = 9;
  int32_t ord_array = 10;
  int32_t ord_slice = 11;
  int32_t ord_vector = 13;
  int32_t base_ref = pipeline_expr_index_base_ref(arena, expr_ref);
  int32_t index_ref = pipeline_expr_index_index_ref(arena, expr_ref);
  int32_t line = pipeline_expr_line_at(arena, expr_ref);
  int32_t col = pipeline_expr_col_at(arena, expr_ref);
  int32_t base_ty = 0;
  int32_t bt_kind = 0;
  int32_t elem_ty = 0;
  int32_t array_sz = 0;
  int32_t index_ty = 0;
  /* wave699: index ambient = i32, not outer return_type_ref (G.7 ≡ typeck.x).
   * PLATFORM: SHARED — &buf[0] under expected *T must not type lit 0 as pointer. */
  int32_t idx_ambient = ensure_i32_type_ref(arena);
  if ((check_expr(module, arena, base_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((check_expr(module, arena, index_ref, idx_ambient, ctx) !=0)) {
    return -(1);
  }
  if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
  if (((ast_ref_is_null(base_ty) || (base_ty <=0)) || (base_ty > (arena->num_types)))) {
    (void)(driver_diagnostic_typeck_subscript_base(line, col));
    return -(1);
  }
  (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
  if (((((bt_kind !=ord_array) && (bt_kind !=ord_slice)) && (bt_kind !=ord_ptr)) && (bt_kind !=ord_vector))) {
    (void)(driver_diagnostic_typeck_subscript_base(line, col));
    return -(1);
  }
  /* wave664: hard-fail non-integer index (G.7 ≡ typeck.x). */
  if (((!(ast_ref_is_null(index_ref)) && (index_ref > 0)) && (index_ref <= (arena->num_exprs)))) {
    (void)((index_ty = pipeline_expr_resolved_type_ref(arena, index_ref)));
    if ((typeck_type_is_valid_subscript_index(module, arena, index_ty) == 0)) {
      (void)(driver_diagnostic_typeck_subscript_index(line, col));
      return -(1);
    }
  }
  (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
  if (ast_ref_is_null(elem_ty)) {
    (void)(driver_diagnostic_typeck_subscript_base(line, col));
    return -(1);
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty));
  if ((bt_kind ==ord_slice)) {
    (void)(pipeline_expr_set_index_base_is_slice(arena, expr_ref, 1));
  } else {
    (void)(pipeline_expr_set_index_base_is_slice(arena, expr_ref, 0));
  }
  if (((!(ast_ref_is_null(index_ref)) && (index_ref > 0)) && (index_ref <=(arena->num_exprs)))) {
    if ((((pipeline_expr_kind_ord_at(arena, index_ref) ==ord_lit) && (pipeline_expr_int_val_at(arena, index_ref) ==0)) && ((bt_kind ==ord_array) || (bt_kind ==ord_vector)))) {
      (void)((array_sz = pipeline_type_array_size_at(arena, base_ty)));
      if ((array_sz >=1)) {
        (void)(pipeline_expr_set_index_proven_in_bounds(arena, expr_ref, 1));
      }
    }
  }
  return 0;
}
int typeck_expr_is_any_assign_kind(int32_t kind_ord) {
  int32_t ord_assign = 28;
  int32_t ord_add_assign = 29;
  int32_t ord_shr_assign = 38;
  if ((kind_ord ==ord_assign)) {
    return 1;
  }
  if (((kind_ord >=ord_add_assign) && (kind_ord <=ord_shr_assign))) {
    return 1;
  }
  return 0;
}
int32_t check_expr_impl_mega(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_return = 41;
  int32_t ord_panic = 42;
  int32_t ord_match = 43;
  int32_t ord_field = 44;
  int32_t ord_struct_lit = 45;
  int32_t ord_index = 47;
  int32_t ord_call = 48;
  int32_t ord_method_call = 49;
  int32_t ord_add = 4;
  int32_t ord_logor = 21;
  int32_t ord_neg = 22;
  int32_t ord_bitnot = 23;
  int32_t ord_lognot = 24;
  int32_t ord_addr_of = 51;
  int32_t ord_deref = 52;
  int32_t ord_var = 3;
  int32_t ord_as = 54;
  int32_t ord_try_propagate = ((int32_t)(58));
  int32_t kind = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
  if (typeck_expr_is_any_assign_kind(kind)) {
    return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_return)) {
    return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_panic)) {
    return typeck_check_expr_panic(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_match)) {
    return pipeline_typeck_check_expr_match_c(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_field)) {
    return typeck_check_expr_field_access(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_index)) {
    return typeck_check_expr_index(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_call)) {
    return typeck_check_expr_call(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_method_call)) {
    return typeck_check_expr_method_call(module, arena, expr_ref, return_type_ref, ctx);
  }
  if (((kind >=ord_add) && (kind <=ord_logor))) {
    return typeck_check_expr_binop(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((((kind ==ord_neg) || (kind ==ord_bitnot)) || (kind ==ord_lognot))) {
    return typeck_check_expr_unary(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_addr_of)) {
    return typeck_check_expr_addr_of(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_deref)) {
    return typeck_check_expr_deref(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_var)) {
    return typeck_check_expr_var(module, arena, expr_ref, ctx);
  }
  if ((kind ==ord_as)) {
    return typeck_check_expr_as(module, arena, expr_ref, ctx);
  }
  if ((kind ==ord_struct_lit)) {
    return typeck_check_expr_struct_lit(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_try_propagate)) {
    return pipeline_typeck_check_expr_try_propagate_c(module, arena, expr_ref, return_type_ref, ctx);
  }
  return 0;
}
int32_t check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t ord_lit = 0;
  int32_t ord_float = 1;
  int32_t ord_bool = 2;
  int32_t ord_string_lit = 59;
  int32_t ord_if = 25;
  int32_t ord_block = 26;
  int32_t ord_ternary = 27;
  int32_t ord_break = 39;
  int32_t ord_continue = 40;
  int32_t ord_enum_var = 50;
  int32_t kind = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
  if ((kind ==ord_float)) {
    return typeck_check_expr_float_lit(arena, expr_ref);
  }
  if ((kind ==ord_lit)) {
    return typeck_check_expr_int_lit(arena, expr_ref, return_type_ref);
  }
  if ((kind ==ord_bool)) {
    return typeck_check_expr_bool_lit(arena, expr_ref);
  }
  if ((kind ==ord_string_lit)) {
    return typeck_check_expr_string_lit(arena, expr_ref);
  }
  if (((kind ==ord_break) || (kind ==ord_continue))) {
    return typeck_check_expr_break_continue(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_enum_var)) {
    return typeck_check_expr_enum_variant(arena, expr_ref);
  }
  if (((kind ==ord_if) || (kind ==ord_ternary))) {
    return typeck_check_expr_if_ternary(module, arena, expr_ref, return_type_ref, ctx);
  }
  if ((kind ==ord_block)) {
    return typeck_check_expr_block(module, arena, expr_ref, return_type_ref, ctx);
  }
  return check_expr_impl_mega(module, arena, expr_ref, return_type_ref, ctx);
}
int32_t check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if (ast_ref_is_null(expr_ref)) {
    return 0;
  }
  if ((((arena ==((struct ast_ASTArena *)(0))) || (expr_ref <=0)) || (expr_ref > (arena->num_exprs)))) {
    return 0;
  }
  return check_expr_impl(module, arena, expr_ref, return_type_ref, ctx);
}
int32_t func_body_tail_expr_ref_for_implicit_rule(struct ast_ASTArena * arena, int32_t body_ref) {
  uint8_t stmt_order_kind_expr_stmt = ((uint8_t)(2));
  uint8_t stmt_order_kind_region_c_parser = ((uint8_t)(5));
  uint8_t stmt_order_kind_region_x_parser = ((uint8_t)(6));
  int32_t ord_break = 39;
  int32_t ord_continue = 40;
  int32_t ord_return = 41;
  int32_t ord_panic = 42;
  int32_t fin_ref = ast_ast_block_final_expr_ref(arena, body_ref);
  int32_t fin_kind = 0;
  int32_t nso = ast_ast_block_num_stmt_order(arena, body_ref);
  if (!(ast_ref_is_null(fin_ref))) {
    (void)((fin_kind = pipeline_expr_kind_ord_at(arena, fin_ref)));
    if (((((fin_kind ==ord_return) || (fin_kind ==ord_panic)) || (fin_kind ==ord_break)) || (fin_kind ==ord_continue))) {
      return fin_ref;
    }
  }
  if ((nso > 0)) {
    uint8_t last_k = ast_ast_block_stmt_order_kind(arena, body_ref, (nso - 1));
    if (((last_k ==stmt_order_kind_region_c_parser) || (last_k ==stmt_order_kind_region_x_parser))) {
      int32_t ridx = ast_ast_block_stmt_order_idx(arena, body_ref, (nso - 1));
      int32_t nreg = ast_ast_block_num_regions(arena, body_ref);
      if (((ridx >=0) && (ridx < nreg))) {
        int32_t unsafe_region = pipeline_block_region_is_unsafe(arena, body_ref, ridx);
        if ((unsafe_region !=0)) {
          int32_t inner_ref = ast_ast_block_region_body_ref(arena, body_ref, ridx);
          if (!(ast_ref_is_null(inner_ref))) {
            return func_body_tail_expr_ref_for_implicit_rule(arena, inner_ref);
          }
        }
      }
    }
  }
  if (!(ast_ref_is_null(fin_ref))) {
    return fin_ref;
  }
  if ((nso > 0)) {
    uint8_t last_k2 = ast_ast_block_stmt_order_kind(arena, body_ref, (nso - 1));
    if ((last_k2 ==stmt_order_kind_expr_stmt)) {
      int32_t idx = ast_ast_block_stmt_order_idx(arena, body_ref, (nso - 1));
      int32_t nes = ast_ast_block_num_expr_stmts(arena, body_ref);
      if (((idx >=0) && (idx < nes))) {
        return ast_ast_block_expr_stmt_ref(arena, body_ref, idx);
      }
    }
    return 0;
  }
  int32_t nes2 = ast_ast_block_num_expr_stmts(arena, body_ref);
  if ((nes2 > 0)) {
    return ast_ast_block_expr_stmt_ref(arena, body_ref, (nes2 - 1));
  }
  return 0;
}
int func_body_has_implicit_return_tail(struct ast_ASTArena * arena, int32_t body_ref) {
  if (((ast_ref_is_null(body_ref) || (body_ref <=0)) || (body_ref > (arena->num_blocks)))) {
    return 0;
  }
  return (pipeline_typeck_func_body_has_implicit_return_tail_c(arena, body_ref) !=0);
}
int32_t typeck_loop_depth_push(struct ast_PipelineDepCtx * ctx) {
  int32_t saved = pipeline_dep_ctx_typeck_loop_depth_at(ctx);
  (void)(pipeline_typeck_loop_depth_set_c(ctx, (saved + 1)));
  return saved;
}
void typeck_loop_depth_pop(struct ast_PipelineDepCtx * ctx, int32_t saved) {
  (void)(pipeline_typeck_loop_depth_set_c(ctx, saved));
}
int32_t check_block_as_loop_body(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t saved_ld = 0;
  int32_t rc = 0;
  if ((ctx ==((struct ast_PipelineDepCtx *)(0)))) {
    return -(1);
  }
  (void)((saved_ld = typeck_loop_depth_push(ctx)));
  (void)((rc = check_block(module, arena, body_ref, return_type_ref, ctx)));
  (void)(typeck_loop_depth_pop(ctx, saved_ld));
  return rc;
}
int32_t typeck_check_block_one_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  int32_t cd_ir = ast_ast_block_const_init_ref(arena, block_ref, idx);
  int32_t cd_tr = ast_ast_block_const_type_ref(arena, block_ref, idx);
  int32_t init_ty = 0;
  int32_t init_ctx = 0;
    /* wave680 Cap residual: same-block const redecl / clash with let / body-param. */
    {
      extern int32_t pipeline_block_const_name_len(struct ast_ASTArena *a, int32_t br, int32_t ci);
      extern void pipeline_block_const_name_copy64(struct ast_ASTArena *a, int32_t br, int32_t ci, uint8_t *dst);
      extern int32_t pipeline_block_local_name_redecl_c(struct ast_ASTArena *a, int32_t block_ref, uint8_t *vname,
          int32_t vlen, int32_t kind, int32_t idx, struct ast_Module *m, int32_t func_index);
      extern int32_t pipeline_dep_ctx_current_func_index(struct ast_PipelineDepCtx *ctx);
      extern void driver_diagnostic_typeck_duplicate_local(int32_t line, int32_t col);
      uint8_t cname_buf[128];
      int32_t cname_len = pipeline_block_const_name_len(arena, block_ref, idx);
      if (cname_len > 0 && cname_len < 128) {
        int32_t func_ix;
        pipeline_block_const_name_copy64(arena, block_ref, idx, cname_buf);
        func_ix = pipeline_dep_ctx_current_func_index(ctx);
        if (pipeline_block_local_name_redecl_c(arena, block_ref, cname_buf, cname_len, 1, idx, module, func_ix) != 0) {
          int32_t err_line = 0;
          int32_t err_col = 0;
          if (!(ast_ref_is_null(cd_ir))) {
            err_line = pipeline_expr_line_at(arena, cd_ir);
            err_col = pipeline_expr_col_at(arena, cd_ir);
          }
          driver_diagnostic_typeck_duplicate_local(err_line, err_col);
          return -(1);
        }
      }
    }
  if (!(ast_ref_is_null(cd_ir))) {
    if ((pipeline_typeck_block_const_init_is_const_c(arena, block_ref, idx) ==0)) {
      int32_t err_line = pipeline_expr_line_at(arena, cd_ir);
      int32_t err_col = pipeline_expr_col_at(arena, cd_ir);
      (void)(pipeline_typeck_const_init_not_constant_c(err_line, err_col));
      return -(1);
    }
  }
  (void)((init_ctx = return_type_ref));
  if (!(ast_ref_is_null(cd_tr))) {
    (void)((init_ctx = cd_tr));
  }
  if ((check_expr(module, arena, cd_ir, init_ctx, ctx) !=0)) {
    return -(1);
  }
  if ((!(ast_ref_is_null(cd_ir)) && !(ast_ref_is_null(cd_tr)))) {
    (void)(typeck_coerce_init_expr_to_decl(module, arena, cd_ir, cd_tr));
    (void)((init_ty = expr_type_ref(arena, cd_ir)));
    if ((!(ast_ref_is_null(init_ty)) && !(type_refs_equal(arena, cd_tr, init_ty)))) {
      return -(1);
    }
  }
  return 0;
}
int32_t typeck_check_block_one_let(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  int32_t ld_ir = ast_ast_block_let_init_ref(arena, block_ref, idx);
  int32_t ld_tr = ast_ast_block_let_type_ref(arena, block_ref, idx);
  int32_t init_ty = 0;
  int32_t init_ctx = 0;
    /* wave680 Cap residual: same-block let redecl / clash with const / body-param. */
    {
      extern int32_t pipeline_block_let_name_len(struct ast_ASTArena *a, int32_t br, int32_t li);
      extern void pipeline_block_let_name_copy64(struct ast_ASTArena *a, int32_t br, int32_t li, uint8_t *dst);
      extern int32_t pipeline_block_local_name_redecl_c(struct ast_ASTArena *a, int32_t block_ref, uint8_t *vname,
          int32_t vlen, int32_t kind, int32_t idx, struct ast_Module *m, int32_t func_index);
      extern int32_t pipeline_dep_ctx_current_func_index(struct ast_PipelineDepCtx *ctx);
      extern void driver_diagnostic_typeck_duplicate_local(int32_t line, int32_t col);
      uint8_t lname_buf[128];
      int32_t lname_len = pipeline_block_let_name_len(arena, block_ref, idx);
      if (lname_len > 0 && lname_len < 128) {
        int32_t func_ix_l;
        pipeline_block_let_name_copy64(arena, block_ref, idx, lname_buf);
        func_ix_l = pipeline_dep_ctx_current_func_index(ctx);
        if (pipeline_block_local_name_redecl_c(arena, block_ref, lname_buf, lname_len, 0, idx, module, func_ix_l) != 0) {
          int32_t err_line = 0;
          int32_t err_col = 0;
          if (!(ast_ref_is_null(ld_ir))) {
            err_line = pipeline_expr_line_at(arena, ld_ir);
            err_col = pipeline_expr_col_at(arena, ld_ir);
          }
          driver_diagnostic_typeck_duplicate_local(err_line, err_col);
          return -(1);
        }
      }
    }
  uint8_t * eb = ((uint8_t *)(0));
  uint8_t * gb = ((uint8_t *)(0));
  int32_t el = 0;
  int32_t gl = 0;
  if (!(ast_ref_is_null(ld_ir))) {
    (void)((init_ctx = return_type_ref));
    if (!(ast_ref_is_null(ld_tr))) {
      (void)((init_ctx = ld_tr));
    }
    /* wave314: bare VAR into f64 let — no expected type (avoid stamp f64 on f32 VAR). */
    if ((!(ast_ref_is_null(ld_tr)) && (pipeline_expr_kind_ord_at(arena, ld_ir) == 3))) {
      int32_t decl_k0 = pipeline_type_kind_ord_at(arena, ld_tr);
      if ((decl_k0 == 15)) {
        (void)((init_ctx = 0));
      }
    }
    if ((check_expr(module, arena, ld_ir, init_ctx, ctx) !=0)) {
      return -(1);
    }
  }
  (void)(pipeline_type_stamp_block_let_region_c(arena, block_ref, idx, ctx));
  (void)((ld_tr = ast_ast_block_let_type_ref(arena, block_ref, idx)));
  if ((!(ast_ref_is_null(ld_ir)) && !(ast_ref_is_null(ld_tr)))) {
    (void)(typeck_coerce_init_expr_to_decl(module, arena, ld_ir, ld_tr));
    (void)((init_ty = expr_type_ref(arena, ld_ir)));
    if ((!(ast_ref_is_null(init_ty)) && !(type_refs_equal(arena, ld_tr, init_ty)))) {
      int32_t decl_k = pipeline_type_kind_ord_at(arena, ld_tr);
      int32_t init_k = pipeline_type_kind_ord_at(arena, init_ty);
      if (typeck_integer_widen_ok_refs(arena, ld_tr, init_ty)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, ld_ir, ld_tr));
        (void)((init_ty = ld_tr));
      }
      /* wave314: f32→f64 no stamp. */
      (void)decl_k;
      (void)init_k;
    }
    if (((!(ast_ref_is_null(init_ty)) && !(type_refs_equal(arena, ld_tr, init_ty))) && (pipeline_typeck_linear_accepts_init_c(arena, ld_tr, init_ty) ==0))) {
      int32_t decl_k2 = pipeline_type_kind_ord_at(arena, ld_tr);
      int32_t init_k2 = pipeline_type_kind_ord_at(arena, init_ty);
      if (!(typeck_float_widen_ok(decl_k2, init_k2))) {
        int32_t err_line = pipeline_expr_line_at(arena, ld_ir);
        int32_t err_col = pipeline_expr_col_at(arena, ld_ir);
        (void)((eb = driver_typeck_diag_scratch_expect()));
        (void)((gb = driver_typeck_diag_scratch_found()));
        (void)((el = typeck_diag_fmt_type_into(arena, ld_tr, eb, 96)));
        (void)((gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96)));
        (void)(driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl));
        return -(1);
      }
    }
    if ((!(ast_ref_is_null(init_ty)) && (pipeline_typeck_check_slice_region_assign_c(arena, ld_ir, ld_tr, init_ty) !=0))) {
      return -(1);
    }
  }
  return 0;
}
int32_t typeck_check_block_one_while(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  int32_t wc = ast_ast_block_while_cond_ref(arena, block_ref, idx);
  int32_t wb = ast_ast_block_while_body_ref(arena, block_ref, idx);
  if (!(ast_ref_is_null(wc))) {
    if ((check_expr(module, arena, wc, return_type_ref, ctx) !=0)) {
      return -(1);
    }
    if (!(type_ref_is_bool(arena, expr_type_ref(arena, wc)))) {
      (void)(driver_diagnostic_typeck_while_condition_not_bool(pipeline_expr_line_at(arena, wc), pipeline_expr_col_at(arena, wc)));
      return -(1);
    }
  }
  return check_block_as_loop_body(module, arena, wb, return_type_ref, ctx);
}
int32_t typeck_check_block_one_for(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  int32_t fi_ir = ast_ast_block_for_init_ref(arena, block_ref, idx);
  int32_t fc_cr = ast_ast_block_for_cond_ref(arena, block_ref, idx);
  int32_t fs_sr = ast_ast_block_for_step_ref(arena, block_ref, idx);
  int32_t fb_br = ast_ast_block_for_body_ref(arena, block_ref, idx);
  if ((check_expr(module, arena, fi_ir, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if (!(ast_ref_is_null(fc_cr))) {
    if ((check_expr(module, arena, fc_cr, return_type_ref, ctx) !=0)) {
      return -(1);
    }
    if (!(type_ref_is_bool(arena, expr_type_ref(arena, fc_cr)))) {
      (void)(driver_diagnostic_typeck_for_condition_not_bool(pipeline_expr_line_at(arena, fc_cr), pipeline_expr_col_at(arena, fc_cr)));
      return -(1);
    }
  }
  if ((check_expr(module, arena, fs_sr, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  return check_block_as_loop_body(module, arena, fb_br, return_type_ref, ctx);
}
int32_t typeck_check_block_one_if(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  int32_t ic_cr = ast_ast_block_if_cond_ref(arena, block_ref, idx);
  int32_t ib_tr = ast_ast_block_if_then_body_ref(arena, block_ref, idx);
  int32_t ib_er = 0;
  if (!(ast_ref_is_null(ic_cr))) {
    if ((check_expr(module, arena, ic_cr, return_type_ref, ctx) !=0)) {
      return -(1);
    }
    if (!(type_ref_is_bool(arena, expr_type_ref(arena, ic_cr)))) {
      (void)(typeck_driver_diagnostic_pipe_marker(pipeline_expr_kind_ord_at(arena, ic_cr)));
      (void)(typeck_driver_diagnostic_pipe_marker(pipeline_type_kind_ord_at(arena, expr_type_ref(arena, ic_cr))));
      (void)(driver_diagnostic_typeck_if_condition_not_bool(pipeline_expr_line_at(arena, ic_cr), pipeline_expr_col_at(arena, ic_cr)));
      return -(1);
    }
  }
  if ((check_block(module, arena, ib_tr, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  (void)((ib_er = ast_ast_block_if_else_body_ref(arena, block_ref, idx)));
  if (!(ast_ref_is_null(ib_er))) {
    return check_block(module, arena, ib_er, return_type_ref, ctx);
  }
  return 0;
}

/* wave663/1227: void fn must not use pure non-void rvalue as stmt/final.
 * wave1227: void-typed expr is not a value; allow IF/BLOCK/MATCH stmts.
 * G.7 authority: typeck.x::typeck_void_reject_value_expr. PLATFORM: SHARED. */
int32_t typeck_void_reject_value_expr(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref) {
  {
    int32_t void_ord = 16;
    int32_t rt_k = 0;
    int32_t ek = 0;
    int32_t void_stmt_ok = 0;
    int32_t got = 0;
    int32_t got_k = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    int32_t line = 0;
    int32_t col = 0;
    if ((((arena == 0) || (expr_ref <= 0)) || ast_ref_is_null(return_type_ref))) {
      return 0;
    }
    (void)((rt_k = pipeline_type_kind_ord_at(arena, return_type_ref)));
    if ((rt_k != void_ord)) {
      return 0;
    }
    (void)((ek = pipeline_expr_kind_ord_at(arena, expr_ref)));
    /* IF=25 BLOCK=26 ASSIGN=28..38 BREAK=39 CONTINUE=40 RETURN=41 PANIC=42 MATCH=43 CALL=48 METHOD=49 */
    if ((ek == 41)) {
      if (ast_ref_is_null(pipeline_expr_unary_operand_ref_at(arena, expr_ref))) {
        void_stmt_ok = 1;
      }
    } else if ((((((ek == 48) || (ek == 49)) || (ek == 39)) || (ek == 40)) || (ek == 42))) {
      void_stmt_ok = 1;
    } else if (((ek >= 28) && (ek <= 38))) {
      void_stmt_ok = 1;
    } else if (((((ek == 25) || (ek == 26)) || (ek == 43)))) {
      void_stmt_ok = 1;
    }
    if ((void_stmt_ok != 0)) {
      return 0;
    }
    (void)((got = typeck_expr_type_ref(arena, expr_ref)));
    /* wave1227: void-typed expression is not a value-producing rvalue. */
    if (!(ast_ref_is_null(got))) {
      (void)((got_k = pipeline_type_kind_ord_at(arena, got)));
      if ((got_k == void_ord)) {
        return 0;
      }
    }
    (void)((eb = driver_typeck_diag_scratch_expect()));
    (void)((gb = driver_typeck_diag_scratch_found()));
    (void)((el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb)));
    (void)((gl = typeck_diag_fmt_type_or_question(arena, got, gb)));
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl));
    (void)(typeck_emit_return_subexpr_breadcrumb(arena, expr_ref, line, col));
    (void)(driver_diagnostic_typeck_ret_fail(2, expr_ref, return_type_ref, got));
    return -1;
  }
}

int32_t typeck_check_block_final(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t fin0) {
  int skip_tail_ty_cmp = 0;
  int32_t fin_k_tail = 0;
  int32_t got = 0;
  int32_t fin_op = 0;
  int32_t fin_k_ret = 0;
  uint8_t * eb_fin = ((uint8_t *)(0));
  uint8_t * gb_fin = ((uint8_t *)(0));
  int32_t el_fin = 0;
  int32_t gl_fin = 0;
  if (ast_ref_is_null(fin0)) {
    return 0;
  }
  if ((check_expr(module, arena, fin0, return_type_ref, ctx) !=0)) {
    return -(1);
  }
    (void)((fin_k_tail = pipeline_expr_kind_ord_at(arena, fin0)));
    if ((typeck_void_reject_value_expr(arena, fin0, return_type_ref) != 0)) {
      return -1;
    }
  if ((fin_k_tail !=41)) {
    (void)((skip_tail_ty_cmp = 1));
  } else {
    if (ast_ref_is_null(pipeline_expr_unary_operand_ref_at(arena, fin0))) {
      (void)((skip_tail_ty_cmp = 1));
    }
  }
  if ((ast_ref_is_null(return_type_ref) || skip_tail_ty_cmp)) {
    return 0;
  }
  (void)((got = expr_type_ref(arena, fin0)));
  (void)((fin_op = fin0));
  (void)((fin_k_ret = pipeline_expr_kind_ord_at(arena, fin0)));
  if ((fin_k_ret ==41)) {
    (void)((fin_op = pipeline_expr_unary_operand_ref_at(arena, fin0)));
  }
  if (((!(ast_ref_is_null(fin_op)) && (fin_op > 0)) && !(ast_ref_is_null(return_type_ref)))) {
    (void)(typeck_ret_coerce_integral_to_expect_i32(arena, fin_op, return_type_ref));
    (void)(typeck_ret_coerce_integral_widen(arena, fin_op, return_type_ref));
  }
  if (typeck_return_operand_matches(module, arena, fin_op, return_type_ref)) {
    return 0;
  }
  if (((!(ast_ref_is_null(fin_op)) && (fin_op > 0)) && !(ast_ref_is_null(return_type_ref)))) {
    int32_t fin_got = expr_type_ref(arena, fin_op);
    int32_t ek_fin = 0;
    int32_t gk_fin = 0;
    if ((!(ast_ref_is_null(fin_got)) && (fin_got > 0))) {
      (void)((ek_fin = pipeline_type_kind_ord_at(arena, return_type_ref)));
      (void)((gk_fin = pipeline_type_kind_ord_at(arena, fin_got)));
      if ((typeck_integer_widen_ok_refs(arena, return_type_ref, fin_got) || typeck_float_widen_ok(ek_fin, gk_fin))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, fin_op, return_type_ref));
        return 0;
      }
    }
  }
  (void)((eb_fin = driver_typeck_diag_scratch_expect()));
  (void)((gb_fin = driver_typeck_diag_scratch_found()));
  (void)((el_fin = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb_fin)));
  (void)((gl_fin = typeck_diag_fmt_type_or_question(arena, got, gb_fin)));
  int32_t err_line = pipeline_expr_line_at(arena, fin0);
  int32_t err_col = pipeline_expr_col_at(arena, fin0);
  (void)(driver_diagnostic_typeck_return_mismatch(err_line, err_col, eb_fin, el_fin, gb_fin, gl_fin));
  (void)(typeck_emit_return_subexpr_breadcrumb(arena, fin0, err_line, err_col));
  return -(1);
}
int32_t typeck_check_block_one_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  return pipeline_typeck_check_block_one_region_c(module, arena, block_ref, idx, return_type_ref, ctx);
}
/* Stage12.0.5: iterative stmt_order (typeck.x twin; no tail recursion). */
int32_t typeck_check_block_stmt_order_one(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t si, int32_t nso, int32_t nc, int32_t nl, int32_t nes, int32_t nlp, int32_t nfp, int32_t nif, int32_t nreg) {
  int32_t i = si;
  uint8_t sk = ((uint8_t)(0));
  int32_t idx = 0;
  int32_t es_ref = 0;
  while (((i < nso) && (i < 96))) {
    (void)(pipeline_typeck_block_impl_touch_ctx_block_c(ctx, block_ref));
    (void)((sk = ast_ast_block_stmt_order_kind(arena, block_ref, i)));
    (void)((idx = ast_ast_block_stmt_order_idx(arena, block_ref, i)));
    if ((sk ==((uint8_t)(0)))) {
      if ((((idx >=0) && (idx < nc)) && (idx < 128))) {
        if ((typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(1)))) {
      if ((((idx >=0) && (idx < nl)) && (idx < 128))) {
        if ((typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(2)))) {
      if (((idx >=0) && (idx < nes))) {
        (void)((es_ref = ast_ast_block_expr_stmt_ref(arena, block_ref, idx)));
        if ((check_expr(module, arena, es_ref, return_type_ref, ctx) !=0)) {
          return -(1);
        }
        if ((typeck_void_reject_value_expr(arena, es_ref, return_type_ref) != 0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(3)))) {
      if (((idx >=0) && (idx < nlp))) {
        if ((typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(4)))) {
      if (((idx >=0) && (idx < nfp))) {
        if ((typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(5)))) {
      if (((idx >=0) && (idx < nif))) {
        if ((typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    } else if ((sk ==((uint8_t)(6)))) {
      if (((idx >=0) && (idx < nreg))) {
        if ((typeck_check_block_one_region(module, arena, block_ref, return_type_ref, ctx, idx) !=0)) {
          return -(1);
        }
      }
    }
    i = i + 1;
  }
  return 0;
}
int32_t typeck_check_block_legacy_consts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nc) {
  if ((i >=nc)) {
    return 0;
  }
  if ((typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -(1);
  }
  return typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, (i + 1), nc);
}
int32_t typeck_check_block_legacy_lets(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nl) {
  if ((i >=nl)) {
    return 0;
  }
  if ((typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -(1);
  }
  return typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, (i + 1), nl);
}
int32_t typeck_check_block_legacy_whiles(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nlp) {
  if ((i >=nlp)) {
    return 0;
  }
  if ((typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -(1);
  }
  return typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, (i + 1), nlp);
}
int32_t typeck_check_block_legacy_fors(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nfp) {
  if ((i >=nfp)) {
    return 0;
  }
  if ((typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -(1);
  }
  return typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, (i + 1), nfp);
}
int32_t typeck_check_block_legacy_ifs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nif) {
  if ((i >=nif)) {
    return 0;
  }
  if ((typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -(1);
  }
  return typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, (i + 1), nif);
}
int32_t typeck_check_block_legacy_expr_stmts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nes) {
  int32_t es_ref = 0;
  if (((i >=nes) || (i >=32))) {
    return 0;
  }
  (void)((es_ref = ast_ast_block_expr_stmt_ref(arena, block_ref, i)));
  if ((check_expr(module, arena, es_ref, return_type_ref, ctx) !=0)) {
    return -(1);
  }
  if ((typeck_void_reject_value_expr(arena, es_ref, return_type_ref) != 0)) {
    return -(1);
  }
  return typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, (i + 1), nes);
}
int32_t check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t saved_block_ref = 0;
  int32_t nc = 0;
  int32_t nl = 0;
  int32_t nlp = 0;
  int32_t nfp = 0;
  int32_t nif = 0;
  int32_t nreg = 0;
  int32_t nes = 0;
  int32_t nso = 0;
  int32_t fin0 = 0;
  int32_t func_ix = 0;
  if ((((arena ==((struct ast_ASTArena *)(0))) || (ctx ==((struct ast_PipelineDepCtx *)(0)))) || (block_ref <=0))) {
    return -(1);
  }
  (void)((saved_block_ref = pipeline_typeck_block_impl_bind_ctx_c(ctx, block_ref)));
  (void)(pipeline_block_set_parent_if_zero(arena, block_ref, saved_block_ref));
  (void)((nc = ast_ast_block_num_consts(arena, block_ref)));
  (void)((nl = ast_ast_block_num_lets(arena, block_ref)));
  (void)((nlp = ast_ast_block_num_loops(arena, block_ref)));
  (void)((nfp = ast_ast_block_num_for_loops(arena, block_ref)));
  (void)((nif = ast_ast_block_num_if_stmts(arena, block_ref)));
  (void)((nreg = ast_ast_block_num_regions(arena, block_ref)));
  (void)((nes = ast_ast_block_num_expr_stmts(arena, block_ref)));
  (void)((nso = ast_ast_block_num_stmt_order(arena, block_ref)));
  (void)((fin0 = ast_ast_block_final_expr_ref(arena, block_ref)));
  (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
  (void)(driver_diagnostic_typeck_block_enter(func_ix, block_ref, nc, nl, nlp, nfp, nes, fin0));
  if ((nso > 0)) {
    if ((typeck_check_block_stmt_order_one(module, arena, block_ref, return_type_ref, ctx, 0, nso, nc, nl, nes, nlp, nfp, nif, nreg) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
  } else {
    if ((typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, 0, nc) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
    if ((typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, 0, nl) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
    if ((typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, 0, nlp) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
    if ((typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, 0, nfp) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
    if ((typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, 0, nif) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
    if ((typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, 0, nes) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
      return -(1);
    }
  }
  if ((typeck_check_block_final(module, arena, block_ref, return_type_ref, ctx, fin0) !=0)) {
    (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
    return -(1);
  }
  (void)(pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref));
  return 0;
}
int32_t check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if (ast_ref_is_null(block_ref)) {
    return 0;
  }
  if ((((arena ==((struct ast_ASTArena *)(0))) || (block_ref <=0)) || (block_ref > (arena->num_blocks)))) {
    return 0;
  }
  return check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}
int32_t typeck_x_ast_check_one_func(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_idx) {
  int32_t body_ref = 0;
  int32_t ret_ty_ref = 0;
  int32_t fn_name_len = 0;
  int32_t num_generic_params = 0;
  int32_t ord_void = 16;
  int32_t rt_kind = 0;
  int32_t err_check_block = 5;
  int32_t err_implicit_tail = 6;
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return 0;
  }
  (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
  (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
  (void)(driver_diagnostic_typeck_fn_enter(func_idx, typeck_scratch64_slot(0), fn_name_len));
  (void)(pipeline_typeck_linear_reset_c());
  /* wave684 Cap residual: typecheck generic function bodies (was skip). */
  (void)((num_generic_params = pipeline_module_func_num_generic_params_at(module, func_idx)));
  (void)num_generic_params;
  (void)((body_ref = pipeline_module_func_body_ref_at(module, func_idx)));
  if ((ast_ref_is_null(body_ref) || (pipeline_module_func_is_extern_at(module, func_idx) !=0))) {
    return 0;
  }
  (void)((ret_ty_ref = pipeline_module_func_return_type_at(module, func_idx)));
  if ((check_block(module, arena, body_ref, ret_ty_ref, ctx) !=0)) {
    int32_t fail_kind_cb = -(5);
    (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
    (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
    (void)(driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb));
    return fail_kind_cb;
  }
  if (!(ast_ref_is_null(ret_ty_ref))) {
    (void)((rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref)));
    if (((rt_kind !=ord_void) && func_body_has_implicit_return_tail(arena, body_ref))) {
      int32_t fail_kind_tail = -(6);
      (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
      (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
      (void)(driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail));
      return fail_kind_tail;
    }
  }
  return 0;
}
/* PLATFORM: SHARED — iterative all-funcs typeck (mega-safe; align typeck.x). */
int32_t typeck_x_ast_check_all_funcs_loop(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_i, int32_t num_funcs) {
  int32_t i = 0;
  int32_t body_ref = 0;
  int32_t ret_ty_ref = 0;
  int32_t fn_name_len = 0;
  int32_t num_generic_params = 0;
  int32_t ord_void = 16;
  int32_t rt_kind = 0;
  int32_t no_func_ix = -(1);
  int32_t fail_kind_cb = -(5);
  int32_t fail_kind_tail = -(6);
  (void)((i = func_i));
  if ((i >= num_funcs)) {
    (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
    return 0;
  }
  if ((i == 0)) {
    (void)(pipeline_typeck_set_entry_module_for_dep_map_c(module));
  }
  while ((i < num_funcs)) {
    (void)(pipeline_dep_ctx_set_current_func_index(ctx, i));
    (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
    (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
    (void)(driver_diagnostic_typeck_fn_enter(i, typeck_scratch64_slot(0), fn_name_len));
    /* wave684: do not skip generic bodies. */
    (void)((num_generic_params = pipeline_module_func_num_generic_params_at(module, i)));
    (void)num_generic_params;
    (void)((body_ref = pipeline_module_func_body_ref_at(module, i)));
    if ((!(ast_ref_is_null(body_ref)) && (pipeline_module_func_is_extern_at(module, i) == 0))) {
      (void)((ret_ty_ref = pipeline_module_func_return_type_at(module, i)));
      if ((check_block(module, arena, body_ref, ret_ty_ref, ctx) != 0)) {
        (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
        (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
        (void)(driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb));
        (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
        return fail_kind_cb;
      }
      if (!(ast_ref_is_null(ret_ty_ref))) {
        (void)((rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref)));
        if (((rt_kind != ord_void) && func_body_has_implicit_return_tail(arena, body_ref))) {
          (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
          (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
          (void)(driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail));
          (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
          return fail_kind_tail;
        }
      }
    }
    (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
    (void)((i = (i + 1)));
  }
  (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
  return 0;
}
void typeck_patch_all_body_parent_links(struct ast_Module * module, struct ast_ASTArena * arena) {
  int32_t i = 0;
  int32_t num = 0;
  int32_t br = 0;
  if (((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0))))) {
    return;
  }
  (void)((num = pipeline_module_num_funcs(module)));
  while ((i < num)) {
    (void)((br = pipeline_module_func_body_ref_at(module, i)));
    if (!(ast_ref_is_null(br))) {
      (void)(pipeline_patch_block_parent_links(arena, br, 0));
    }
    (void)((i = (i + 1)));
  }
}
int32_t typeck_x_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  int32_t mi = 0;
  int32_t ret_kind = 0;
  int32_t ord_i32 = 0;
  int32_t ord_i64 = 5;
  int32_t main_num_generic_params = 0;
  int32_t body_ref = 0;
  int32_t body_expr_ref = 0;
  int32_t ret_ty = 0;
  int32_t num_funcs = 0;
  int32_t pipe_marker_ret_ty_ready = 301;
  int32_t pipe_marker_main_generic_checked = 302;
  int32_t pipe_marker_layout_validated = 303;
  int32_t pipe_marker_parent_links_patched = 304;
  int32_t pipe_marker_main_generic_base = 320;
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return -(2);
  }
  (void)((mi = pipeline_module_main_func_index(module)));
  if (((pipeline_module_func_is_extern_at(module, mi) !=0) && ast_ref_is_null(pipeline_module_func_body_ref_at(module, mi)))) {
    return -(1);
  }
  (void)((body_ref = pipeline_module_func_body_ref_at(module, mi)));
  (void)((body_expr_ref = pipeline_module_func_body_expr_ref_at(module, mi)));
  if ((ast_ref_is_null(body_ref) && ast_ref_is_null(body_expr_ref))) {
    return -(2);
  }
  (void)((ret_ty = pipeline_module_func_return_type_at(module, mi)));
  if (ast_ref_is_null(ret_ty)) {
    return -(3);
  }
  (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_ret_ty_ready));
  (void)((main_num_generic_params = pipeline_module_func_num_generic_params_at(module, mi)));
  (void)(typeck_driver_diagnostic_pipe_marker((pipe_marker_main_generic_base + main_num_generic_params)));
  if ((main_num_generic_params > 0)) {
    return -(12);
  }
  (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_main_generic_checked));
  (void)((ret_kind = pipeline_type_kind_ord_at(arena, ret_ty)));
  /* PLATFORM: SHARED — main may return i32/i64 or void (align typeck.x). */
  if ((((ret_kind !=ord_i32) && (ret_kind !=ord_i64)) && (ret_kind !=16))) {
    return -(4);
  }
  if ((typeck_validate_struct_layouts_zero_padding(module, arena) !=0)) {
    return -(7);
  }
  (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_layout_validated));
  (void)(typeck_patch_all_body_parent_links(module, arena));
  (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_parent_links_patched));
  (void)((num_funcs = pipeline_module_num_funcs(module)));
  return typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
}
int32_t typeck_x_ast_library(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  int32_t num_funcs = 0;
  if ((((module ==((struct ast_Module *)(0))) || (arena ==((struct ast_ASTArena *)(0)))) || (ctx ==((struct ast_PipelineDepCtx *)(0))))) {
    return -(5);
  }
  if ((typeck_validate_struct_layouts_zero_padding(module, arena) !=0)) {
    return -(7);
  }
  (void)(typeck_patch_all_body_parent_links(module, arena));
  (void)((num_funcs = pipeline_module_num_funcs(module)));
  return typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
}
int32_t typeck_x_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  int32_t mi = 0;
  int32_t num_funcs = 0;
  if ((module ==((struct ast_Module *)(0)))) {
    return -(10);
  }
  (void)((mi = pipeline_module_main_func_index(module)));
  (void)((num_funcs = pipeline_module_num_funcs(module)));
  if ((mi < 0)) {
    return -(10);
  }
  if ((mi >=num_funcs)) {
    return -(11);
  }
  return typeck_x_ast_impl(module, arena, ctx);
}
