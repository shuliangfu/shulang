/* generated (single-file with deps) */
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
#include <math.h>
#undef htonl
#undef htons
#undef ntohl
#undef ntohs
#ifdef _WIN32
#define XLANG_LIB_WEAK
#else
#define XLANG_LIB_WEAK __attribute__((weak))
#endif
#ifndef XLANG_BUILTIN_INLINE_DECLS_GUARD
#define XLANG_BUILTIN_INLINE_DECLS_GUARD
/* CORE-009 xlang_builtin_* static inline wrappers (clz/ctz/popcount/bswap/rotl/rotr) */
static inline int xlang_builtin_clz_u32(uint32_t x) { return x == 0 ? 32 : __builtin_clz(x); }
static inline int xlang_builtin_ctz_u32(uint32_t x) { return x == 0 ? 32 : __builtin_ctz(x); }
static inline int xlang_builtin_popcount_u32(uint32_t x) { return __builtin_popcount(x); }
static inline uint32_t xlang_builtin_bswap_u32(uint32_t x) { return __builtin_bswap32(x); }
static inline uint32_t xlang_builtin_rotl_u32(uint32_t x, uint32_t c) {
  c &= 31; return c == 0 ? x : (x << c) | (x >> (32 - c));
}
static inline uint32_t xlang_builtin_rotr_u32(uint32_t x, uint32_t c) {
  c &= 31; return c == 0 ? x : (x >> c) | (x << (32 - c));
}
#endif
/* wave245 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED orch / host getenv residual via single face.
 * Compiler-only gen seed pin (CRASH_EVIDENCE inline) — not user program template
 * (runtime.from_x.c fprintf CRASH_EVIDENCE user C templates use link_abi_getenv since wave254). */
extern char *link_abi_getenv(const char *name);
extern int getpid(void);
static inline void xlang_crash_evidence_collect_inline(int has_msg, int msg_val) {
  const char *_ev = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  char _note[192];
  if (!_ev || _ev[0] != '1') return;
  int _pid = (int)getpid();
  { int _n = snprintf(_note, sizeof _note, "note: crash evidence: panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val, _pid);
    if (_n > 0) (void)xlang_io_write(2, _note, (size_t)_n); }
  { const char *_dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (_dir && _dir[0]) { char _p[1024]; snprintf(_p, sizeof _p, "%s/xlang-crash-%d.txt", _dir, _pid);
      { int _fd = xlang_io_open_write(_p);
        if (_fd >= 0) { char _body[160];
          int _bl = snprintf(_body, sizeof _body, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, _pid);
          if (_bl > 0) (void)xlang_io_write(_fd, _body, (size_t)_bl);
          (void)xlang_proc_close_fd(_fd);
          { int _bn = snprintf(_note, sizeof _note, "note: crash evidence: bundle=%s\n", _p);
            if (_bn > 0) (void)xlang_io_write(2, _note, (size_t)_bn); } } } } }
}
static inline void xlang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static inline void xlang_panic_(int has_msg, int msg_val) {
  xlang_crash_evidence_collect_inline(has_msg, msg_val);
  if (has_msg) { char _mb[32]; int _mn = snprintf(_mb, sizeof _mb, "%d\n", msg_val);
    if (_mn > 0) (void)xlang_io_write(2, _mb, (size_t)_mn); }
  abort();
}
extern int32_t xlang_io_register(uint8_t *ptr, size_t len, size_t handle);
extern int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
extern int32_t xlang_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
typedef struct { void *ptr; size_t length; size_t handle; } xlang_buffer_abi_t;
static inline int32_t xlang_io_register_buf(intptr_t buf) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return xlang_io_register((uint8_t *)b->ptr, b->length, b->handle); }
static inline int32_t xlang_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return xlang_io_submit_read((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }
static inline int32_t xlang_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return xlang_io_submit_write((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }
typedef struct { uint8_t *ptr; size_t length; size_t handle; } xlang_batch_buf_t;
/* wave316 G.7: monofile dual WEAK polyfill → extern-only (pipeline_gen residual sole dual).
 * live STRONG = runtime/product .o. Completes freestanding dual leave after wave310 shell re-pin.
 * PLATFORM: SHARED freestanding dual leave. */
extern int io_register_buffers_buf_c(const xlang_batch_buf_t *bufs, int nr);
static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const xlang_batch_buf_t *)(uintptr_t)bufs, nr); }
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[128]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; uint8_t region_label[128]; int32_t region_label_len; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t var_name[128]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_base; int32_t match_num_arms; int32_t field_access_base_ref; uint8_t field_access_field_name[128]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t field_access_soa_stride; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_base; int32_t call_num_args; int32_t call_num_type_args; int32_t method_call_base_ref; uint8_t method_call_name[128]; int32_t method_call_name_len; int32_t method_call_arg_base; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[128]; int32_t struct_lit_struct_name_len; int32_t struct_lit_field_base; int32_t struct_lit_num_fields; int32_t array_lit_elem_base; int32_t array_lit_num_elems; int32_t float_bits_lo; int32_t float_bits_hi; int32_t enum_variant_tag; int32_t as_operand_ref; int32_t as_target_type_ref; int32_t call_resolved_func_index; int32_t call_resolved_dep_index; };
struct ast_ConstDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[128]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_IfStmt { int32_t cond_ref; int32_t then_body_ref; int32_t else_body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[128]; int32_t label_len; int32_t is_goto; uint8_t goto_target[128]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { int32_t const_base; int32_t num_consts; int32_t let_base; int32_t num_lets; int32_t num_early_lets; int32_t loop_base; int32_t num_loops; int32_t for_loop_base; int32_t num_for_loops; int32_t if_base; int32_t num_if_stmts; int32_t region_base; int32_t num_regions; int32_t defer_base; int32_t num_defers; int32_t labeled_base; int32_t num_labeled_stmts; int32_t expr_stmt_base; int32_t num_expr_stmts; int32_t final_expr_ref; int32_t stmt_order_base; int32_t num_stmt_order; int32_t parent_block_ref; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[128]; int32_t name_len; int32_t param_base; int32_t num_params; int32_t num_generic_params; int32_t return_type_ref; int32_t body_ref; int32_t body_expr_ref; int32_t is_extern; int32_t is_async; int32_t is_used; int32_t is_naked; int32_t is_entry; int32_t is_no_mangle; int32_t is_interrupt; int32_t abi_kind; int32_t is_variadic; int32_t is_export; };
struct ast_StructLayout { uint8_t name[128]; int32_t name_len; int32_t field_base; int32_t num_fields; int32_t allow_padding; int32_t soa; int32_t packed; int32_t repr_compatible; int32_t is_export; };
struct ast_Module { int32_t num_funcs; int32_t main_func_index; int32_t num_imports; int32_t num_top_level_lets; int32_t num_struct_layouts; int32_t pending_allow_padding; int32_t pending_soa_struct; int32_t pending_cfg_skip; int32_t pending_repr_c_struct; int32_t pending_repr_compatible_struct; int32_t pending_used; int32_t pending_naked; int32_t pending_entry; int32_t pending_no_mangle; int32_t pending_interrupt; int32_t pending_export; int32_t num_module_enums; };
struct ast_ASTArena { int32_t num_types; int32_t num_exprs; int32_t num_blocks; int32_t num_funcs; };
struct ast_PipelineDepCtx { int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t path_buf[512]; uint8_t loaded_buf[4194304]; ptrdiff_t loaded_len; uint8_t preprocess_buf[4194304]; int32_t preprocess_len; int32_t use_asm_backend; int32_t target_arch; int32_t target_cpu_features; int32_t use_macho_o; int32_t use_coff_o; int32_t current_block_ref; int32_t typeck_loop_depth; int32_t current_func_index; int32_t skip_codegen_dep_0; int32_t entry_already_parsed; int32_t current_func_single_empty_param_index; int32_t current_func_empty_param_count; int32_t current_emit_empty_var_next_index; int32_t emit_expr_as_callee; struct ast_Module * current_codegen_module; struct ast_ASTArena * current_codegen_arena; int32_t current_codegen_dep_index; uint8_t current_codegen_prefix_mirror[128]; int32_t current_codegen_prefix_len; int32_t asm_entry_module_only; uint8_t entry_module_import_path_mirror[128]; int32_t entry_module_import_path_len; int32_t typeck_scope_region_len; uint8_t typeck_scope_region_label[128]; };
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_TRY, token_TokenKind_TOKEN_CATCH, token_TokenKind_TOKEN_REGION, token_TokenKind_TOKEN_WITH_ARENA, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_TYPE, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_SOA, token_TokenKind_TOKEN_ATTR_SOA, token_TokenKind_TOKEN_ATTR_CFG, token_TokenKind_TOKEN_ATTR_REPR_C, token_TokenKind_TOKEN_ATTR_REPR_COMPATIBLE, token_TokenKind_TOKEN_ATTR_ALLOC, token_TokenKind_TOKEN_ATTR_LINK_SECTION, token_TokenKind_TOKEN_ATTR_NAKED, token_TokenKind_TOKEN_ATTR_ENTRY, token_TokenKind_TOKEN_ATTR_USED, token_TokenKind_TOKEN_ATTR_NO_MANGLE, token_TokenKind_TOKEN_ATTR_LINK_NAME, token_TokenKind_TOKEN_ATTR_MAX_STACK, token_TokenKind_TOKEN_ATTR_INTERRUPT, token_TokenKind_TOKEN_ATTR_SEND, token_TokenKind_TOKEN_ATTR_SYNC, token_TokenKind_TOKEN_ATTR_GLOBAL_ALLOCATOR, token_TokenKind_TOKEN_ATTR_COLD, token_TokenKind_TOKEN_ATTR_INLINE_NEVER, token_TokenKind_TOKEN_ATTR_INLINE_ALWAYS, token_TokenKind_TOKEN_ATTR_EXPORT_NAME, token_TokenKind_TOKEN_ATTR_PANIC_HANDLER, token_TokenKind_TOKEN_ATTR_THREAD_LOCAL, token_TokenKind_TOKEN_ATTR_PERCPU, token_TokenKind_TOKEN_ALIGN, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_ASYNC, token_TokenKind_TOKEN_AWAIT, token_TokenKind_TOKEN_RUN, token_TokenKind_TOKEN_SPAWN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_F32X4, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_DOTDOT, token_TokenKind_TOKEN_ELLIPSIS, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_PLUS_EQ, token_TokenKind_TOKEN_MINUS_EQ, token_TokenKind_TOKEN_STAR_EQ, token_TokenKind_TOKEN_SLASH_EQ, token_TokenKind_TOKEN_PERCENT_EQ, token_TokenKind_TOKEN_AMP_EQ, token_TokenKind_TOKEN_PIPE_EQ, token_TokenKind_TOKEN_CARET_EQ, token_TokenKind_TOKEN_LSHIFT_EQ, token_TokenKind_TOKEN_RSHIFT_EQ, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION, token_TokenKind_TOKEN_AS, token_TokenKind_TOKEN_AT, token_TokenKind_TOKEN_STRING, token_TokenKind_TOKEN_EXPORT, token_TokenKind_TOKEN_NULL };
struct token_Token { enum token_TokenKind kind; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t * ident; int32_t ident_len; };
struct lexer_Lexer { size_t pos; int32_t line; int32_t col; };
struct lexer_LexerResult { struct lexer_Lexer next_lex; struct token_Token tok; size_t token_start; };
struct std_heap_libc_Arena64 { uint8_t * chunk; size_t cap; size_t off; };
struct std_heap_Arena64 { uint8_t * chunk; size_t cap; size_t off; };
struct std_heap_HeapTraceStats { uint64_t alloc_count; uint64_t free_count; uint64_t realloc_count; uint64_t bytes_allocated; };
struct std_heap_Allocator { int32_t kind; struct std_heap_Arena64 * arena; };
struct parser_OneFuncResult { int ok; struct lexer_Lexer next_lex; uint8_t name[128]; int32_t name_len; int32_t num_params; int32_t num_generic_params; int32_t num_consts; int32_t num_lets; int has_if_expr; int if_cond_true; int32_t if_then_val; int32_t if_else_val; int32_t if_cond_expr_ref; int has_mul; int32_t mul_right_val; int has_binop; int32_t binop_right_val; int32_t binop_left_param_idx; int32_t binop_right_param_idx; int has_unary_neg; int32_t return_val; int has_call_expr; uint8_t call_callee_name[128]; int32_t call_callee_len; uint8_t return_var_name[128]; int32_t return_var_name_len; int32_t return_expr_ref; int has_final_expr; int has_explicit_return_kw; int32_t call_num_args; int32_t num_loops; int32_t num_for_loops; int32_t num_if_stmts; int32_t num_src_stmt_order; int32_t num_src_body_expr_stmts; int32_t func_return_type_ref; };
struct parser_ParseResult { int ok; int32_t return_val; };
struct parser_ParseIntoResult { int32_t ok; int32_t main_idx; };
struct parser_TopLevelLetResult { int ok; struct lexer_Lexer next_lex; };
struct parser_TypeAliasResult { int ok; struct lexer_Lexer next_lex; };
struct parser_CollectImportsResult { struct lexer_Lexer lex; };
struct parser_ParseExprResult { int ok; int32_t expr_ref; struct lexer_Lexer next_lex; };
struct parser_ParseBlockResult { int ok; int32_t block_ref; struct lexer_Lexer next_lex; };
struct parser_ExternParseResult { struct lexer_Lexer next_lex; uint8_t name[128]; int32_t name_len; int32_t return_ty_ref; int32_t num_params; int32_t abi_kind; int32_t is_variadic; };
struct parser_TrySkipAllowResult { struct lexer_Lexer lex; int32_t skipped; uint8_t _pad[4]; };
struct parser_LibraryParseResult { int ok; uint8_t _pad[4]; struct lexer_Lexer next_lex; uint8_t name[128]; int32_t name_len; uint8_t _pad_tail[4]; };
struct parser_LibraryParseScanResult { int ok; uint8_t _pad[4]; struct lexer_Lexer next_lex; uint8_t name[128]; int32_t name_len; uint8_t param_name[128]; int32_t param_name_len; uint8_t param_type_name[128]; int32_t param_type_len; uint8_t field_name[128]; int32_t field_len; uint8_t _pad_tail[4]; uint8_t _pad_tail2[4]; };
struct codegen_CodegenOutBuf { uint8_t data[9437184]; int32_t length; };
struct codegen_outbuf_abi_CodegenOutBuf { uint8_t data[9437184]; int32_t length; };
enum asm_types_TargetArch { asm_types_TargetArch_TARGET_X86_64, asm_types_TargetArch_TARGET_ARM64, asm_types_TargetArch_TARGET_RISCV64, asm_types_TargetArch_TARGET_NONE };
struct platform_elf_ElfLabelEntry { uint8_t name[128]; int32_t name_len; int32_t offset; };
struct platform_elf_ElfPatchEntry { int32_t rel32_offset; uint8_t name[128]; int32_t name_len; int32_t patch_imm_bits; };
struct platform_elf_ElfRelocEntry { int32_t offset; int32_t name_len; };
struct platform_elf_ElfRelocSymName64 { uint8_t bytes[128]; };
struct platform_elf_ElfSymEntry { uint8_t name[128]; int32_t name_len; int32_t offset; int32_t sym_shndx; };
struct platform_elf_ElfCodegenCtx { int32_t code_len; struct platform_elf_ElfLabelEntry labels[16384]; int32_t num_labels; struct platform_elf_ElfPatchEntry patches[16384]; int32_t num_patches; struct platform_elf_ElfRelocEntry relocs[16384]; struct platform_elf_ElfRelocSymName64 reloc_sym_names[16384]; int32_t num_relocs; struct platform_elf_ElfSymEntry syms[16384]; int32_t num_syms; int32_t sym_name_len; int32_t e_machine; int32_t reloc_type_r_pc32; int32_t current_frame_size; int32_t macho_leading_underscore; int32_t code_hot_len; int32_t emit_hot; uint8_t code_data[8716288]; uint8_t code_hot_data[1048576]; uint8_t sym_name_data[131072]; };
struct asm_backend_AsmFuncCtx { int32_t frame_size; int32_t next_offset; int32_t num_locals; int32_t label_counter; struct ast_Module * module_ref; uint8_t loop_break_label_stack[512]; int32_t loop_break_len_stack[8]; uint8_t loop_continue_label_stack[512]; int32_t loop_continue_len_stack[8]; uint8_t break_label[128]; int32_t break_len; uint8_t continue_label[128]; int32_t continue_len; int32_t loop_label_depth; struct ast_PipelineDepCtx * dep_pipe; uint8_t tail_join_label[128]; int32_t tail_join_label_len; };
/* slim arena grow pool glue (C-04 codegen; linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);

extern int32_t typeck_pipeline_module_num_funcs(struct ast_Module * module);
extern struct ast_Module * ast_pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void ast_pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern uint8_t * driver_dep_arena_buf(int32_t i);
extern uint8_t * driver_dep_module_buf(int32_t i);
extern int32_t driver_dep_seeded_get(int32_t i);
extern int32_t driver_dep_slot_for_path(uint8_t * path);
extern int32_t get_ndep();
extern int32_t pipeline_driver_asm_build_skip_typeck();
extern int32_t pipeline_driver_x_pipeline_skip_typeck();
extern int32_t parser_parse_one_function_ok_for_pipeline_buf_glue(struct ast_ASTArena * arena, uint8_t * data, int32_t len);
extern void ast_ast_arena_init(struct ast_ASTArena * arena);
extern int32_t asm_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_copy_lib_root_to_buf256(struct ast_PipelineDepCtx * ctx, int32_t lib_idx, uint8_t * dst);
extern int32_t preprocess_x_buf(uint8_t * source_buf, ptrdiff_t source_len, uint8_t * out_buf, int32_t out_cap);
extern void pipeline_dep_ctx_set_path_buf_byte(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t b);
extern uint8_t * pipeline_dep_ctx_path_buf_ptr(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_entry_dir_len(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_entry_dir_copy(struct ast_PipelineDepCtx * ctx, uint8_t * dst, int32_t cap);
extern int32_t pipeline_dep_ctx_asm_entry_module_only(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_use_asm_backend(struct ast_PipelineDepCtx * ctx);
extern uint8_t * pipeline_dep_ctx_loaded_buf_ptr(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_set_loaded_len(struct ast_PipelineDepCtx * ctx, ptrdiff_t n);
extern int32_t pipeline_ctx_lib_root_count(struct ast_PipelineDepCtx * ctx);
extern ptrdiff_t fs_posix_read_c(int32_t fd, uint8_t * buf, size_t count);
extern int32_t fs_posix_close_c(int32_t fd);
extern int32_t run_x_pipeline_last_rc_get();
extern void run_x_pipeline_last_rc_store_c(int32_t rc);
extern int32_t pipeline_typeck_fail_return_c(int32_t fail_mapped);
extern int32_t pipeline_typeck_null_fail_return_c(int32_t fail_mapped);
extern int32_t run_x_pipeline_load_deps_after_parse_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_typecheck_after_load_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern void pipeline_module_set_main_func_index(struct ast_Module * module, int32_t main_idx);
extern int32_t pipeline_module_main_func_index(struct ast_Module * module);
extern int32_t pipeline_arena_num_types(struct ast_ASTArena * arena);
extern int32_t pipeline_parse_into_with_init_buf_scalars_sidecar(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len);
extern int32_t pipeline_parse_scalars_ok_get();
extern int32_t pipeline_parse_scalars_main_idx_get();
extern void pipeline_parse_fail_diag_scalars_c(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t pipeline_parse_apply_main_from_scalars_c(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t pipeline_parse_set_main_from_buf_c(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * data, int32_t len);
extern int32_t pipeline_typeck_parsed_module_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t fail_mapped);
extern int32_t pipeline_typeck_entry_module_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_after_parse_ok_buf_impl_c(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_load_import_resolve_read_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
extern int32_t pipeline_load_import_from_disk_impl_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
extern int32_t pipeline_load_one_import_slot_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
extern int32_t pipeline_sync_dep_slots_from_driver_impl_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_realign_ndep_for_entry_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_load_and_sync_direct_import_deps_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t lsp_diag_typeck_after_load_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t lsp_diag_parse_typeck_buf_c(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, int32_t source_len, struct ast_PipelineDepCtx * ctx);
extern struct parser_ParseIntoResult pipeline_parse_into_with_init_result_c();
extern struct parser_ParseIntoResult pipeline_parse_into_with_init_buf_impl_c(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len);
extern int32_t run_x_pipeline_parse_entry_do_parse_c(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, size_t source_len, struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_parse_entry_if_needed_c(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, size_t source_len, struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_typecheck_entry_emit_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_fill_dep_import_path_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t dep_j);
extern int32_t pipeline_fill_dep_import_path_from_buf_c(struct ast_PipelineDepCtx * ctx, int32_t dep_j, uint8_t * path_buf);
extern int32_t pipeline_resolve_path_x_from_buf64_c(struct ast_PipelineDepCtx * ctx, uint8_t * path_buf);
extern int32_t pipeline_prepare_dep_codegen_path_c(struct ast_PipelineDepCtx * ctx, int32_t dep_j, uint8_t * dst);
extern int32_t pipeline_finish_dep_codegen_diag_c(int32_t dep_j, struct codegen_CodegenOutBuf * out_buf);
extern int32_t run_x_pipeline_codegen_one_dep_prepare_c(struct ast_PipelineDepCtx * ctx, int32_t dep_j);
extern int32_t pipeline_loop_should_continue_ndep_c(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_loop_should_continue_imports_c(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_loop_should_continue_lib_root_c(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_resolve_path_last_off_get_c();
extern int32_t pipeline_resolve_path_lib_root_prefix_off_c(struct ast_PipelineDepCtx * ctx, int32_t lib_idx);
extern int32_t pipeline_path_append_import_path_sidecar_c(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_resolve_path_entry_dir_prefix_off_c(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_flat_import_build_path_c(struct ast_PipelineDepCtx * ctx, int32_t lib_idx, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_flat_import_probe_open_c(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_loop_index_at_or_beyond_ndep_c(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_loop_index_at_or_beyond_imports_c(struct ast_Module * module, int32_t idx);
extern void pipeline_load_and_sync_set_ndep_from_module_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_codegen_deps_c(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx, int32_t skip_asm_dep_codegen);
extern int32_t run_x_pipeline_codegen_entry_c(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
extern void pipeline_strict_parse_into_init(struct ast_ASTArena * arena, struct ast_Module * module);
extern void parser_parse_into_init(struct ast_Module * module, struct ast_ASTArena * arena);
extern struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len);
extern int32_t pipeline_parse_into_buf_c(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * buf, int32_t buf_len);
extern int32_t pipeline_path_append_from_buf_256_c(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * buf, int32_t len);
extern int32_t pipeline_path_append_from_buf_512_c(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * buf, int32_t len);
extern int32_t pipeline_path_append_import_path_c(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_resolve_path_probe_export_c(struct ast_PipelineDepCtx * ctx, int32_t off);
extern int32_t pipeline_read_fd_into_loaded_buf(struct ast_PipelineDepCtx * ctx, int32_t fd);
extern int32_t parser_copy_module_import_path64(struct ast_Module * module, int32_t i, uint8_t out[128]);
extern int32_t parser_get_module_num_imports(struct ast_Module * module);
extern uint8_t * pipeline_dep_ctx_preprocess_buf_ptr(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_preprocess_len_get(struct ast_PipelineDepCtx * ctx);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_set_ndep(struct ast_PipelineDepCtx * ctx, int32_t n);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t typeck_typeck_x_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_typeck_x_ast_library(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_scan_module_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern void typeck_typeck_merge_dep_struct_layouts_into_entry(struct ast_Module * mod, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern void typeck_typeck_wpo_unify_soa_layouts(struct ast_Module * entry, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_preprocess_loaded_into_ctx(struct ast_PipelineDepCtx * ctx);
extern void pipeline_bind_import_dep_buffers(struct ast_PipelineDepCtx * ctx, int32_t import_idx);
extern int32_t pipeline_read_file_x_impl_c(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_try_bind_seeded_import(struct ast_PipelineDepCtx * ctx, int32_t import_idx, int32_t global_slot);
extern int32_t pipeline_sync_one_dep_slot(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t dep_i);
extern void driver_diagnostic_parse_fail(int32_t main_idx, int32_t num_funcs, int32_t arena_num_types);
extern void driver_diagnostic_typeck_fail();
extern void driver_diagnostic_before_codegen(int32_t num_funcs, int32_t out_len);
extern void driver_compile_phase_timing_begin(int32_t phase);
extern void driver_compile_phase_timing_end(int32_t phase);
extern void driver_compile_phase_timing_flush();
extern int32_t pipeline_module_num_funcs(struct ast_Module * module);
extern int32_t codegen_out_buf_len(struct codegen_CodegenOutBuf * out_buf);
extern void codegen_out_buf_set_len(struct codegen_CodegenOutBuf * out_buf, int32_t n);
extern void driver_diagnostic_after_dep_codegen(int32_t j, int32_t out_len);
extern void driver_diagnostic_codegen_fail(int32_t dep_index, int32_t is_dep);
extern int32_t driver_skip_codegen_dep_0_get();
extern int32_t driver_check_only_get();
extern int32_t driver_x_pipeline_skip_codegen_get();
extern void driver_diagnostic_entry_already(int32_t v);
extern void driver_diagnostic_source_len(int32_t len);
extern void driver_diagnostic_after_entry_parse(int32_t num_funcs);
extern void driver_diagnostic_entry_module(struct ast_Module * module, struct ast_ASTArena * arena);
extern void driver_set_current_dep_path_for_codegen(uint8_t * path);
extern int32_t pipeline_dep_ctx_entry_already_parsed(struct ast_PipelineDepCtx * ctx);
extern int32_t run_x_pipeline_codegen_one_dep_emit(struct ast_Module * dep_mod, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx, int32_t dep_j, int32_t skip_asm_dep_codegen, int32_t use_asm_backend);
extern int32_t run_x_pipeline_codegen_entry_emit(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx, int32_t use_asm_backend);

/* C-04 -E-extern TU aliases */
#define ast_arena_init ast_ast_arena_init

int32_t pipeline_should_skip_x_typeck(struct ast_PipelineDepCtx * ctx);
/* wave305 G.7 dual-export leave: sole T/W on runtime_pipeline_abi (pure/seed). */
extern int32_t pipeline_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * buf, int32_t buf_len);
int32_t pipeline_path_append_from_buf_256(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * buf, int32_t len);
int32_t pipeline_path_append_from_buf_512(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * buf, int32_t len);
int32_t pipeline_path_append_import_path(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t * import_path, int32_t path_len);
int32_t pipeline_resolve_path_import_has_dot(uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_resolve_path_probe_dot_x_and_mod(struct ast_PipelineDepCtx * ctx, int32_t off);
int32_t pipeline_resolve_path_try_flat_import_under_lib(struct ast_PipelineDepCtx * ctx, int32_t lib_idx, uint8_t * import_path, int32_t path_len);
int32_t pipeline_resolve_path_try_one_lib_root(struct ast_PipelineDepCtx * ctx, int32_t lib_idx, uint8_t * import_path, int32_t path_len);
int32_t pipeline_resolve_path_try_entry_dir(struct ast_PipelineDepCtx * ctx, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_resolve_path_x(struct ast_PipelineDepCtx * ctx, uint8_t * import_path, int32_t path_len);
size_t pipeline_loaded_buf_cap();
extern int32_t pipeline_read_file_x(struct ast_PipelineDepCtx * ctx);
struct parser_ParseIntoResult pipeline_parse_into_with_init_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len);
int32_t pipeline_parse_apply_main_from_scalars(struct ast_Module * module, struct ast_ASTArena * arena);
int32_t pipeline_parse_set_main_from_buf(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * data, int32_t len);
int32_t pipeline_typeck_parsed_module(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t fail_mapped);
int32_t pipeline_typeck_entry_module(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_load_import_resolve_read(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
int32_t pipeline_load_import_from_disk(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
int32_t pipeline_load_one_import_slot(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t import_idx);
int32_t pipeline_sync_dep_slots_from_driver(struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_load_and_sync_direct_import_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_lsp_diag_parse_entry_buf(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, int32_t source_len);
int32_t pipeline_lsp_diag_typeck_after_load(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_lsp_diag_parse_typeck_buf(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, int32_t source_len, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_parse_entry_do_parse(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, size_t source_len, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_parse_entry_if_needed(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, size_t source_len, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_load_deps_after_parse(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_typecheck_after_load(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_typecheck_entry(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_fill_dep_import_path(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t dep_j);
int32_t pipeline_run_x_pipeline_codegen_one_dep(struct ast_Module * module, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx, int32_t dep_j, int32_t skip_asm_dep_codegen);
int32_t pipeline_run_x_pipeline_codegen_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx, int32_t skip_asm_dep_codegen);
int32_t pipeline_prepare_dep_codegen_path(struct ast_PipelineDepCtx * ctx, int32_t dep_j, uint8_t * dst);
int32_t pipeline_finish_dep_codegen_diag(int32_t dep_j, struct codegen_CodegenOutBuf * out_buf);
int32_t pipeline_run_x_pipeline_codegen_entry(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_x_pipeline_impl(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * source_data, size_t source_len, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
/* wave307: pipeline_should_skip_x_typeck residual pure leave → runtime_pipeline_abi pure (no body here). */
/* wave305: pipeline_parse_into_buf dual leave → runtime_pipeline_abi pure (no body here). */
/* wave305: pipeline_resolve_path_probe_dot_x_and_mod dual leave → pure (no body here). */
/* wave307: pipeline_loaded_buf_cap residual pure leave → runtime_pipeline_abi pure (no body here). */
/* wave305: pipeline_read_file_x dual leave → pure (no body here). */
/* wave308: pipeline_parse_into_with_init_buf Cap-struct leave → seed ALWAYS (no body here). */
/* wave307: pipeline_load_one_import_slot residual pure leave → runtime_pipeline_abi pure (no body here). */
/* wave307: pipeline_lsp_diag_typeck_after_load residual pure leave → runtime_pipeline_abi pure (no body here). */
/* wave307: pipeline_run_x_pipeline_impl residual pure leave → runtime_pipeline_abi pure (no body here). */

/* wave309: pipeline_glue shell retired — no include */
/* wave310 G.7: re-pin this seed to tip residual shell (post wave305–309 leave).
 * Stale pin had ~40 XLANG_LIB_WEAK residual bodies dual vs runtime_pipeline_abi pure.
 * After re-pin: sole T was weak io_register_buffers_buf_c; wave316 left dualW→extern (T=0).
 * PLATFORM: SHARED — product pure-ld does not host-cc pipeline_gen (wave309). */
