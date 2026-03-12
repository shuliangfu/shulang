/* generated (single-file with deps) */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static void shulang_panic_(int has_msg, int msg_val) {
  if (has_msg) (void)fprintf(stderr, "%d\n", msg_val);
  abort();
}
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_BINOP };
struct ast_Type { enum ast_TypeKind kind; uint8_t name[64]; int32_t name_len; int32_t elem_type_ref; int32_t array_size; };
struct ast_Expr { enum ast_ExprKind kind; int32_t resolved_type_ref; int32_t line; int32_t col; int32_t int_val; double float_val; uint8_t var_name[64]; int32_t var_name_len; int32_t binop_left_ref; int32_t binop_right_ref; int32_t unary_operand_ref; int32_t if_cond_ref; int32_t if_then_ref; int32_t if_else_ref; int32_t block_ref; int32_t match_matched_ref; int32_t match_arm_result_refs[16]; int32_t match_num_arms; int32_t match_arm_is_wildcard[16]; int32_t match_arm_lit_val[16]; int32_t match_arm_is_enum_variant[16]; int32_t match_arm_variant_index[16]; int32_t field_access_base_ref; uint8_t field_access_field_name[64]; int32_t field_access_field_len; int32_t field_access_is_enum_variant; int32_t field_access_offset; int32_t index_base_ref; int32_t index_index_ref; int32_t index_base_is_slice; int32_t call_callee_ref; int32_t call_arg_refs[16]; int32_t call_num_args; int32_t method_call_base_ref; uint8_t method_call_name[64]; int32_t method_call_name_len; int32_t method_call_arg_refs[16]; int32_t method_call_num_args; int32_t const_folded_val; int32_t const_folded_valid; int32_t index_proven_in_bounds; uint8_t struct_lit_struct_name[64]; int32_t struct_lit_struct_name_len; int32_t struct_lit_num_fields; uint8_t struct_lit_field_names[8][64]; int32_t struct_lit_field_lens[8]; int32_t struct_lit_init_refs[8]; int32_t array_lit_num_elems; int32_t array_lit_elem_refs[16]; int32_t float_bits_lo; int32_t float_bits_hi; int32_t enum_variant_tag; };
struct ast_ConstDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_LetDecl { uint8_t name[64]; int32_t name_len; int32_t type_ref; int32_t init_ref; };
struct ast_WhileLoop { int32_t cond_ref; int32_t body_ref; };
struct ast_ForLoop { int32_t init_ref; int32_t cond_ref; int32_t step_ref; int32_t body_ref; };
struct ast_StmtOrderItem { uint8_t kind; int32_t idx; };
struct ast_LabeledStmt { uint8_t label[32]; int32_t label_len; int32_t is_goto; uint8_t goto_target[32]; int32_t goto_target_len; int32_t return_expr_ref; };
struct ast_Block { struct ast_ConstDecl const_decls[24]; int32_t num_consts; struct ast_LetDecl let_decls[24]; int32_t num_lets; int32_t num_early_lets; struct ast_WhileLoop loops[8]; int32_t num_loops; struct ast_ForLoop for_loops[8]; int32_t num_for_loops; int32_t defer_block_refs[8]; int32_t num_defers; struct ast_LabeledStmt labeled_stmts[8]; int32_t num_labeled_stmts; int32_t expr_stmt_refs[32]; int32_t num_expr_stmts; int32_t final_expr_ref; struct ast_StmtOrderItem stmt_order[96]; int32_t num_stmt_order; };
struct ast_Param { uint8_t name[32]; int32_t name_len; int32_t type_ref; };
struct ast_Func { uint8_t name[64]; int32_t name_len; struct ast_Param params[16]; int32_t num_params; int32_t return_type_ref; int32_t body_ref; int32_t body_expr_ref; int32_t is_extern; };
struct ast_StructLayout { uint8_t name[64]; int32_t name_len; int32_t num_fields; uint8_t field_names[8][64]; int32_t field_lens[8]; int32_t field_offsets[8]; };
struct ast_Module { struct ast_Func funcs[256]; int32_t func_refs[256]; int32_t num_funcs; int32_t main_func_index; uint8_t import_path_data[2048]; int32_t import_path_lens[32]; int32_t num_imports; struct ast_StructLayout struct_layouts[32]; int32_t num_struct_layouts; };
struct ast_ASTArena { struct ast_Type types[512]; int32_t num_types; struct ast_Expr exprs[4096]; int32_t num_exprs; struct ast_Block blocks[512]; int32_t num_blocks; struct ast_Func funcs[256]; int32_t num_funcs; };
struct ast_PipelineDepCtx { struct ast_Module * dep_modules[32]; struct ast_ASTArena * dep_arenas[32]; int32_t ndep; uint8_t entry_dir_buf[512]; int32_t entry_dir_len; int32_t num_lib_roots; uint8_t lib_root_bufs[8][256]; int32_t lib_root_lens[8]; uint8_t path_buf[512]; uint8_t loaded_buf[262144]; ptrdiff_t loaded_len; uint8_t preprocess_buf[262144]; int32_t preprocess_len; int32_t use_asm_backend; int32_t target_arch; int32_t use_macho_o; int32_t use_coff_o; int32_t current_block_ref; };
int ast_ref_is_null(int32_t ref);
int32_t ast_ast_placeholder();
void ast_ast_arena_init(struct ast_ASTArena * arena);
int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena);
int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena);
int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena);
struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
void ast_expr_init_match_enum(struct ast_Expr * e);
struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
int32_t ast_ast_arena_func_alloc(struct ast_ASTArena * arena);
struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
int ast_ref_is_null(int32_t ref) {
  return ref == 0;
}
int32_t ast_ast_placeholder() {
  return 0;
}
void ast_ast_arena_init(struct ast_ASTArena * arena) {
  (void)(((arena)->num_types = 0));
  (void)(((arena)->num_exprs = 0));
  (void)(((arena)->num_blocks = 0));
  (void)(((arena)->num_funcs = 0));
}
int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp = 0; if ((arena)->num_types >= 512) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_types = (arena)->num_types + 1));
  return (arena)->num_types;
}
int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp = 0; if ((arena)->num_exprs >= 4096) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_exprs = (arena)->num_exprs + 1));
  return (arena)->num_exprs;
}
int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp = 0; if ((arena)->num_blocks >= 512) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_blocks = (arena)->num_blocks + 1));
  return (arena)->num_blocks;
}
struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), ((arena)->types)[0]) : ((arena)->types)[ref - 1]);
}
void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((arena)->types)[ref - 1] = t, 0))));
}
void ast_expr_init_match_enum(struct ast_Expr * e) {
  int32_t i = 0;
  while (i < 16) {
    (void)(((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), 0) : (((e)->match_arm_is_wildcard)[i] = 0, 0))));
    (void)(((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), 0) : (((e)->match_arm_lit_val)[i] = 0, 0))));
    (void)(((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), 0) : (((e)->match_arm_is_enum_variant)[i] = 0, 0))));
    (void)(((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), 0) : (((e)->match_arm_variant_index)[i] = 0, 0))));
    (void)((i = i + 1));
  }
  (void)(((e)->enum_variant_tag = 0));
}
struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 4096 ? (shulang_panic_(1, 0), ((arena)->exprs)[0]) : ((arena)->exprs)[ref - 1]);
}
void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 4096 ? (shulang_panic_(1, 0), 0) : (((arena)->exprs)[ref - 1] = e, 0))));
}
struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), ((arena)->blocks)[0]) : ((arena)->blocks)[ref - 1]);
}
void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((arena)->blocks)[ref - 1] = b, 0))));
}
int32_t ast_ast_arena_func_alloc(struct ast_ASTArena * arena) {
  (void)(({ int32_t __tmp = 0; if ((arena)->num_funcs >= 256) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((arena)->num_funcs = (arena)->num_funcs + 1));
  return (arena)->num_funcs;
}
struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref) {
  return (ref - 1 < 0 || (ref - 1) >= 256 ? (shulang_panic_(1, 0), ((arena)->funcs)[0]) : ((arena)->funcs)[ref - 1]);
}
void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f) {
  (void)(((ref - 1 < 0 || (ref - 1) >= 256 ? (shulang_panic_(1, 0), 0) : (((arena)->funcs)[ref - 1] = f, 0))));
}
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION };
struct token_Token { enum token_TokenKind kind; int32_t line; int32_t col; int32_t int_val; double float_val; uint8_t * ident; int32_t ident_len; };
int token_token_is_eof(struct token_Token t);
int token_token_is_eof(struct token_Token t) {
  return (t).kind == token_TokenKind_TOKEN_EOF;
}
struct shulang_slice_uint8_t { uint8_t *data; size_t length; };
struct lexer_Lexer { size_t pos; int32_t line; int32_t col; };
struct lexer_LexerResult { struct lexer_Lexer next_lex; struct token_Token tok; };
struct lexer_Lexer lexer_lexer_init();
struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c);
int lexer_is_alpha(uint8_t c);
int lexer_is_digit(uint8_t c);
int lexer_is_alnum_underscore(uint8_t c);
int lexer_match_keyword(struct shulang_slice_uint8_t * data, size_t start, int32_t len, struct shulang_slice_uint8_t * keyword);
int lexer_match_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, int32_t len, struct shulang_slice_uint8_t * keyword);
struct token_Token lexer_try_keyword(struct shulang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0);
struct token_Token lexer_try_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, size_t len, int32_t line0, int32_t col0);
struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data);
struct lexer_Lexer lexer_skip_whitespace_and_comments_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult lexer_lexer_next(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data);
struct lexer_LexerResult lexer_lexer_next_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult lexer_lexer_next_body(struct lexer_Lexer l, struct shulang_slice_uint8_t * data);
struct lexer_LexerResult lexer_lexer_next_body_buf(struct lexer_Lexer l, uint8_t * restrict data, int32_t len);
struct lexer_Lexer lexer_lexer_init() {
  return (struct lexer_Lexer){ .pos = 0, .line = 1, .col = 1 };
}
struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c) {
  (void)(({ int32_t __tmp = 0; if (c == 10) {   return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line + 1, .col = 1 };
 } else (__tmp = 0) ; __tmp; }));
  return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line, .col = (lex).col + 1 };
}
int lexer_is_alpha(uint8_t c) {
  (void)(({ int __tmp = 0; if (c >= 97 && c <= 122) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if (c >= 65 && c <= 90) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  return c == 95;
}
int lexer_is_digit(uint8_t c) {
  return c >= 48 && c <= 57;
}
int lexer_is_alnum_underscore(uint8_t c) {
  return lexer_is_alpha(c) || lexer_is_digit(c);
}
int lexer_match_keyword(struct shulang_slice_uint8_t * data, size_t start, int32_t len, struct shulang_slice_uint8_t * keyword) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int __tmp = 0; if ((start + i < 0 || (size_t)(start + i) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[start + i]) != (i < 0 || (size_t)(i) >= (keyword)->length ? (shulang_panic_(1, 0), (keyword)->data[0]) : (keyword)->data[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 1;
}
int lexer_match_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, int32_t len, struct shulang_slice_uint8_t * keyword) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int __tmp = 0; if (((int32_t)(start)) + i >= data_len) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int __tmp = 0; if ((data)[start + i] != (i < 0 || (size_t)(i) >= (keyword)->length ? (shulang_panic_(1, 0), (keyword)->data[0]) : (keyword)->data[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 1;
}
struct token_Token lexer_try_keyword(struct shulang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0) {
  struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IDENT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = len };
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 8 && lexer_match_keyword(data, start, 8, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 117, 110, 99, 116, 105, 111, 110 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FUNCTION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 108, 101, 116 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LET, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 115, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONST, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 2 && lexer_match_keyword(data, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 102 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 108, 115, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ELSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 119, 104, 105, 108, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_WHILE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 108, 111, 111, 112 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LOOP, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 111, 114 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FOR, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 98, 114, 101, 97, 107 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BREAK, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 8 && lexer_match_keyword(data, start, 8, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 116, 105, 110, 117, 101 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONTINUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 116, 117, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RETURN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 110, 105, 99 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PANIC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 100, 101, 102, 101, 114 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_DEFER, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 109, 97, 116, 99, 104 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_MATCH, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 115, 116, 114, 117, 99, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRUCT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 99, 107, 101, 100 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PACKED, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 110, 117, 109 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ENUM, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 103, 111, 116, 111 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_GOTO, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 97, 105, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRAIT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 115, 101, 108, 102 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SELF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 1 && (start < 0 || (size_t)(start) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[start]) == 95) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_UNDERSCORE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 116, 101, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXTERN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 98, 111, 111, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BOOL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 2 && lexer_match_keyword(data, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 56 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_USIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ISIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 117, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 97, 108, 115, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FALSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 118, 111, 105, 100 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_VOID, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  return t;
}
struct token_Token lexer_try_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, size_t len, int32_t line0, int32_t col0) {
  struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IDENT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = len };
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 8 && lexer_match_keyword_buf(data, data_len, start, 8, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 117, 110, 99, 116, 105, 111, 110 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FUNCTION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 108, 101, 116 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LET, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 115, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONST, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 2 && lexer_match_keyword_buf(data, data_len, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 102 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 108, 115, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ELSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 116, 117, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RETURN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 115, 116, 114, 117, 99, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRUCT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 110, 117, 109 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ENUM, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 109, 97, 116, 99, 104 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_MATCH, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 117, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 97, 108, 115, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FALSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 118, 111, 105, 100 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_VOID, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 98, 111, 111, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BOOL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 2 && lexer_match_keyword_buf(data, data_len, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 56 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_USIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 116, 101, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXTERN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp = (struct token_Token){0}; if (len == 1 && start < ((size_t)(data_len)) && (data)[start] == 95) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_UNDERSCORE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  return t;
}
struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data) {
  struct lexer_Lexer l = lex;
  while ((l).pos < (data)->length) {
    uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)(({ int32_t __tmp = 0; if (c == 32 || c == 9 || c == 10 || c == 13) {   (void)((l = lexer_advance_one(l, c)));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {
  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 42) {   (void)((l = lexer_advance_one(l, 47)));
  (void)((l = lexer_advance_one(l, 42)));
  while ((l).pos + 1 < (data)->length) {
    (void)(({ int32_t __tmp = 0; if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 42 && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {   (void)((l = lexer_advance_one(l, 42)));
  (void)((l = lexer_advance_one(l, 47)));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 35) {
  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    return l;
  }
  return l;
}
struct lexer_Lexer lexer_skip_whitespace_and_comments_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_Lexer l = lex;
  size_t len_u = ((size_t)(len));
  while ((l).pos < len_u) {
    uint8_t c = (data)[(l).pos];
    (void)(({ int32_t __tmp = 0; if (c == 32 || c == 9 || c == 10 || c == 13) {   (void)((l = lexer_advance_one(l, c)));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 47 && (l).pos + 1 < len_u && (data)[(l).pos + 1] == 47) {
  while ((l).pos < len_u && (data)[(l).pos] != 10) {
    (void)((l = lexer_advance_one(l, (data)[(l).pos])));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 47 && (l).pos + 1 < len_u && (data)[(l).pos + 1] == 42) {   (void)((l = lexer_advance_one(l, 47)));
  (void)((l = lexer_advance_one(l, 42)));
  while ((l).pos + 1 < len_u) {
    (void)(({ int32_t __tmp = 0; if ((data)[(l).pos] == 42 && (data)[(l).pos + 1] == 47) {   (void)((l = lexer_advance_one(l, 42)));
  (void)((l = lexer_advance_one(l, 47)));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)((l = lexer_advance_one(l, (data)[(l).pos])));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 35) {
  while ((l).pos < len_u && (data)[(l).pos] != 10) {
    (void)((l = lexer_advance_one(l, (data)[(l).pos])));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    return l;
  }
  return l;
}
struct lexer_LexerResult lexer_lexer_next(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data) {
  fprintf(stderr, "lexer_next: pos=%zu len=%zu\n", (size_t)(lex).pos, (size_t)(data)->length); fflush(stderr);
  struct lexer_Lexer l = lexer_skip_whitespace_and_comments(lex, data);
  (void)(({ int32_t __tmp = 0; if ((l).pos >= (data)->length) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 0) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  return lexer_lexer_next_body(l, data);
}
struct lexer_LexerResult lexer_lexer_next_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_Lexer l = lexer_skip_whitespace_and_comments_buf(lex, data, len);
  size_t len_u = ((size_t)(len));
  (void)(({ int32_t __tmp = 0; if ((l).pos >= len_u) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((data)[(l).pos] == 0) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  return lexer_lexer_next_body_buf(l, data, len);
}
struct lexer_LexerResult lexer_lexer_next_body(struct lexer_Lexer l, struct shulang_slice_uint8_t * data) {
  uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(({ int32_t __tmp = 0; if (lexer_is_alpha(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (void)((l = lexer_advance_one(l, c)));
  while ((l).pos < (data)->length && lexer_is_alnum_underscore(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  size_t len = (l).pos - start;
  struct token_Token tok = lexer_try_keyword(data, start, len, line0, col0);
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lexer_is_digit(c)) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  int32_t ival = 0;
  (void)((l = lexer_advance_one(l, c)));
  (void)((ival = ival * 10 + c - 48));
  while ((l).pos < (data)->length && lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)((l = lexer_advance_one(l, d)));
    (void)((ival = ival * 10 + d - 48));
  }
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   (void)((l = lexer_advance_one(l, 46)));
  double fval = ival;
  double frac = 0.1;
  while ((l).pos < (data)->length && lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)((l = lexer_advance_one(l, d)));
    (void)((fval = fval + frac * (d - 48)));
    (void)((frac = frac * 0.1));
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 101 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 69) {   (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  int32_t exp_sign = 1;
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 45) {   (void)((exp_sign = (-1)));
  (void)((l = lexer_advance_one(l, 45)));
 } else {   __tmp = ({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 43) {   (void)((l = lexer_advance_one(l, 43)));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  int32_t exp = 0;
  while ((l).pos < (data)->length && lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)((l = lexer_advance_one(l, d)));
    (void)((exp = exp * 10 + d - 48));
  }
  (void)((exp = exp * exp_sign));
  double scale = 1;
  int32_t e = 0;
  (void)(({ int32_t __tmp = 0; if (exp > 0) {   while (e < exp) {
    (void)((scale = scale * 10));
    (void)((e = e + 1));
  }
 } else {   while (e > exp) {
    (void)((scale = scale * 0.1));
    (void)((e = e - 1));
  }
 } ; __tmp; }));
  double fval = ival * scale;
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ival, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (void)((l = lexer_advance_one(l, 46)));
  double fval = 0.0;
  double frac = 0.1;
  while ((l).pos < (data)->length && lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)((l = lexer_advance_one(l, d)));
    (void)((fval = fval + frac * (d - 48)));
    (void)((frac = frac * 0.1));
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)((l = lexer_advance_one(l, c)));
  (void)(({ int32_t __tmp = 0; if (c == 40) {   (void)(((tok).kind = token_TokenKind_TOKEN_LPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 41) {   (void)(((tok).kind = token_TokenKind_TOKEN_RPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 123) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 125) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 91) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 93) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 44) {   (void)(((tok).kind = token_TokenKind_TOKEN_COMMA));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 58) {   (void)(((tok).kind = token_TokenKind_TOKEN_COLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 46) {   (void)(((tok).kind = token_TokenKind_TOKEN_DOT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 59) {   (void)(((tok).kind = token_TokenKind_TOKEN_SEMICOLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 43) {   (void)(((tok).kind = token_TokenKind_TOKEN_PLUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 45) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_ARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_MINUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 42) {   (void)(((tok).kind = token_TokenKind_TOKEN_STAR));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 47) {   (void)(((tok).kind = token_TokenKind_TOKEN_SLASH));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 37) {   (void)(((tok).kind = token_TokenKind_TOKEN_PERCENT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 94) {   (void)(((tok).kind = token_TokenKind_TOKEN_CARET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 126) {   (void)(((tok).kind = token_TokenKind_TOKEN_TILDE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 38) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 38) {   (void)((l = lexer_advance_one(l, 38)));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMPAMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 124) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 124) {   (void)((l = lexer_advance_one(l, 124)));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPEPIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 60) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 60) {   (void)((l = lexer_advance_one(l, 60)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_LT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 62) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_GE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_RSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_GT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 33) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_NE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_BANG));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 63) {   (void)(((tok).kind = token_TokenKind_TOKEN_QUESTION));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 61) {   (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_FATARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_ASSIGN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
}
struct lexer_LexerResult lexer_lexer_next_body_buf(struct lexer_Lexer l, uint8_t * restrict data, int32_t len) {
  size_t len_u = ((size_t)(len));
  uint8_t c = (data)[(l).pos];
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(({ int32_t __tmp = 0; if (lexer_is_alpha(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = lexer_advance_one(l, c);
  (void)((l = l2));
  while ((l).pos < len_u && lexer_is_alnum_underscore((data)[(l).pos])) {
    (void)((l = lexer_advance_one(l, (data)[(l).pos])));
  }
  size_t seg_len = (l).pos - start;
  struct token_Token tok = lexer_try_keyword_buf(data, len, start, seg_len, line0, col0);
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lexer_is_digit(c)) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  int32_t ival = 0;
  (void)((l = lexer_advance_one(l, c)));
  (void)((ival = ival * 10 + c - 48));
  while ((l).pos < len_u && lexer_is_digit((data)[(l).pos])) {
    uint8_t d = (data)[(l).pos];
    (void)((l = lexer_advance_one(l, d)));
    (void)((ival = ival * 10 + d - 48));
  }
  (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 46 && (l).pos + 1 < len_u && lexer_is_digit((data)[(l).pos + 1])) {   (void)((l = lexer_advance_one(l, 46)));
  double fval = ival;
  double frac = 0.1;
  while ((l).pos < len_u && lexer_is_digit((data)[(l).pos])) {
    uint8_t d = (data)[(l).pos];
    (void)((l = lexer_advance_one(l, d)));
    (void)((fval = fval + frac * (d - 48)));
    (void)((frac = frac * 0.1));
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ival, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 46 && (l).pos + 1 < len_u && lexer_is_digit((data)[(l).pos + 1])) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (void)((l = lexer_advance_one(l, 46)));
  double fval = 0.0;
  double frac = 0.1;
  while ((l).pos < len_u && lexer_is_digit((data)[(l).pos])) {
    uint8_t d = (data)[(l).pos];
    (void)((l = lexer_advance_one(l, d)));
    (void)((fval = fval + frac * (d - 48)));
    (void)((frac = frac * 0.1));
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)((l = lexer_advance_one(l, c)));
  (void)(({ int32_t __tmp = 0; if (c == 40) {   (void)(((tok).kind = token_TokenKind_TOKEN_LPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 41) {   (void)(((tok).kind = token_TokenKind_TOKEN_RPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 123) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 125) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 91) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 93) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 44) {   (void)(((tok).kind = token_TokenKind_TOKEN_COMMA));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 58) {   (void)(((tok).kind = token_TokenKind_TOKEN_COLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 46) {   (void)(((tok).kind = token_TokenKind_TOKEN_DOT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 59) {   (void)(((tok).kind = token_TokenKind_TOKEN_SEMICOLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 43) {   (void)(((tok).kind = token_TokenKind_TOKEN_PLUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 45) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_ARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_MINUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 42) {   (void)(((tok).kind = token_TokenKind_TOKEN_STAR));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 47) {   (void)(((tok).kind = token_TokenKind_TOKEN_SLASH));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 37) {   (void)(((tok).kind = token_TokenKind_TOKEN_PERCENT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 94) {   (void)(((tok).kind = token_TokenKind_TOKEN_CARET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 126) {   (void)(((tok).kind = token_TokenKind_TOKEN_TILDE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 38) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 38) {   (void)((l = lexer_advance_one(l, 38)));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMPAMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 124) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 124) {   (void)((l = lexer_advance_one(l, 124)));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPEPIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 60) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 60) {   (void)((l = lexer_advance_one(l, 60)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_LT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 62) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_GE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_RSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_GT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 33) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_NE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_BANG));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 63) {   (void)(((tok).kind = token_TokenKind_TOKEN_QUESTION));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 61) {   (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_FATARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((l).pos < len_u && (data)[(l).pos] == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_ASSIGN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
}
extern int32_t open(uint8_t * path, int32_t flags);
extern ptrdiff_t read(int32_t fd, uint8_t * buf, size_t count);
extern ptrdiff_t write(int32_t fd, uint8_t * buf, size_t count);
extern int32_t close(int32_t fd);
int32_t std_fs_placeholder();
int32_t std_fs_fs_invalid_handle();
int32_t std_fs_fs_open_read(uint8_t * path);
int32_t std_fs_fs_close(int32_t fd);
ptrdiff_t std_fs_fs_read(int32_t fd, uint8_t * buf, size_t count);
ptrdiff_t std_fs_fs_write(int32_t fd, uint8_t * buf, size_t count);
int32_t std_fs_placeholder() {
  return 0;
}
int32_t std_fs_fs_invalid_handle() {
  return (-1);
}
int32_t std_fs_fs_open_read(uint8_t * path) {
  return open(path, 0);
}
int32_t std_fs_fs_close(int32_t fd) {
  return close(fd);
}
ptrdiff_t std_fs_fs_read(int32_t fd, uint8_t * buf, size_t count) {
  return read(fd, buf, count);
}
ptrdiff_t std_fs_fs_write(int32_t fd, uint8_t * buf, size_t count) {
  return write(fd, buf, count);
}
extern struct lexer_Lexer lexer_lexer_init();
extern struct lexer_LexerResult lexer_lexer_next(struct lexer_Lexer, struct shulang_slice_uint8_t *);
extern struct lexer_LexerResult lexer_lexer_next_buf(struct lexer_Lexer, uint8_t *, int32_t);
extern void ast_ast_arena_init(struct ast_ASTArena *);
extern int32_t ast_ast_arena_type_alloc(struct ast_ASTArena *);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena *, int32_t);
extern int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena *);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena *, int32_t);
extern int32_t ast_ast_arena_block_alloc(struct ast_ASTArena *);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena *, int32_t);
extern void ast_ast_arena_expr_set(struct ast_ASTArena *, int32_t, struct ast_Expr);
extern void ast_ast_arena_type_set(struct ast_ASTArena *, int32_t, struct ast_Type);
extern void ast_ast_arena_block_set(struct ast_ASTArena *, int32_t, struct ast_Block);
extern int32_t ast_ast_arena_func_alloc(struct ast_ASTArena *);
extern struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena *, int32_t);
extern void ast_ast_arena_func_set(struct ast_ASTArena *, int32_t, struct ast_Func);
extern int32_t std_fs_fs_open_read(uint8_t *);
extern ptrdiff_t std_fs_fs_read(int32_t, uint8_t *, size_t);
extern int32_t std_fs_fs_close(int32_t);
struct parser_ParseResult { int ok; int32_t return_val; };
struct parser_ParseIntoResult { int32_t ok; int32_t main_idx; };
struct parser_CollectImportsResult { struct lexer_Lexer lex; };
struct parser_OneFuncResult { int ok; struct lexer_Lexer next_lex; uint8_t name[64]; int32_t name_len; int32_t num_params; uint8_t param_names[16][32]; int32_t param_name_lens[16]; int32_t num_consts; uint8_t const_names[24][64]; int32_t const_name_lens[24]; int32_t const_init_vals[24]; int32_t num_lets; uint8_t let_names[24][64]; int32_t let_name_lens[24]; int32_t let_init_vals[24]; int has_if_expr; int if_cond_true; int32_t if_then_val; int32_t if_else_val; int has_mul; int32_t mul_right_val; int has_binop; int32_t binop_right_val; int has_unary_neg; int32_t return_val; int has_call_expr; uint8_t call_callee_name[64]; int32_t call_callee_len; };
struct parser_ParseResult parser_parse(struct shulang_slice_uint8_t * source);
int32_t parser_first_token_kind(struct shulang_slice_uint8_t * source);
int32_t parser_diag_first_ident_len(struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_diag_skip_let_const(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_diag_skip_let_const_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult parser_body_skip_let_const_then_if(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_body_skip_let_const_then_if_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_Lexer parser_skip_balanced_parens(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_balanced_parens_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_Lexer parser_skip_balanced_braces(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_balanced_braces_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult parser_skip_one_if_core(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_skip_one_if_statement(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_skip_one_if_core_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult parser_skip_one_if_statement_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_Lexer parser_diag_lex_after_imports(struct shulang_slice_uint8_t * source);
struct lexer_LexerResult parser_diag_after_imports_then_structs(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
int32_t parser_diag_fail_at_token_kind(struct shulang_slice_uint8_t * source);
void parser_copy_slice_to_name64(struct shulang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t out[64]);
void parser_copy_slice_to_name64_buf(uint8_t * restrict source, int32_t source_len, size_t start, int32_t nlen, uint8_t out[64]);
struct parser_OneFuncResult parser_parse_one_function(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
void parser_parse_into_init(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module);
struct lexer_Lexer parser_skip_imports(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
void parser_collect_imports(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source, struct ast_Module * restrict module, struct parser_CollectImportsResult * restrict out);
void parser_collect_imports_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len, struct ast_Module * restrict module, struct parser_CollectImportsResult * restrict out);
struct lexer_Lexer parser_skip_one_struct(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_struct_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct parser_OneFuncResult parser_parse_one_function_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct parser_ParseIntoResult parser_parse_into(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module, struct shulang_slice_uint8_t * source);
struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module, uint8_t * restrict data, int32_t len);
void parser_parse_into_set_main_index(struct ast_Module * restrict module, int32_t main_idx);
int32_t parser_diag_token_after_collect_imports(struct shulang_slice_uint8_t * source, struct ast_Module * restrict module);
int32_t parser_diag_parse_one_after_collect_imports(struct shulang_slice_uint8_t * source, struct ast_Module * restrict module);
int32_t parser_get_module_num_imports(struct ast_Module * restrict module);
void parser_get_module_import_path(struct ast_Module * restrict module, int32_t i, uint8_t out[64]);
struct parser_ParseResult parser_parse(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  int32_t ret_val = ((r).tok).int_val;
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RPAREN) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_I32) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RETURN) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_EOF) {   return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
 } else (__tmp = 0) ; __tmp; }));
  return (struct parser_ParseResult){ .ok = 1, .return_val = ret_val };
}
int32_t parser_first_token_kind(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  return ((r).tok).kind;
}
int32_t parser_diag_first_ident_len(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   return (-2);
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return (-3);
 } else (__tmp = 0) ; __tmp; }));
  return ((r).tok).ident_len;
}
struct lexer_LexerResult parser_diag_skip_let_const(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  while (((r).tok).kind == token_TokenKind_TOKEN_LET || ((r).tok).kind == token_TokenKind_TOKEN_CONST) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   return r;
 } ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_ASSIGN) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
      (void)((lex = (r).next_lex));
      (void)((r = lexer_lexer_next(lex, source)));
    }
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
  }
  return r;
}
struct lexer_LexerResult parser_diag_skip_let_const_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
  while (((r).tok).kind == token_TokenKind_TOKEN_LET || ((r).tok).kind == token_TokenKind_TOKEN_CONST) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else (__tmp = ({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else {   return r;
 } ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_ASSIGN) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
    while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
      (void)((lex = (r).next_lex));
      (void)((r = lexer_lexer_next_buf(lex, data, len)));
    }
    (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
  }
  return r;
}
struct lexer_LexerResult parser_body_skip_let_const_then_if(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = parser_diag_skip_let_const(lex, source);
  while (((r).tok).kind == token_TokenKind_TOKEN_IF) {
    (void)((r = parser_skip_one_if_statement((r).next_lex, source)));
  }
  return r;
}
struct lexer_LexerResult parser_body_skip_let_const_then_if_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_LexerResult r = parser_diag_skip_let_const_buf(lex, data, len);
  while (((r).tok).kind == token_TokenKind_TOKEN_IF) {
    (void)((r = parser_skip_one_if_statement_buf((r).next_lex, data, len)));
  }
  return r;
}
struct lexer_Lexer parser_skip_balanced_parens(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  int32_t depth = 1;
  while (depth > 0) {
    struct lexer_LexerResult r = lexer_lexer_next(lex, source);
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_LPAREN) {   (void)((depth = depth + 1));
 } else (__tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((depth = depth - 1));
  __tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (depth == 0) {   return (r).next_lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; });
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_EOF) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
  }
  return lex;
}
struct lexer_Lexer parser_skip_balanced_parens_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  int32_t depth = 1;
  while (depth > 0) {
    struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_LPAREN) {   (void)((depth = depth + 1));
 } else (__tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((depth = depth - 1));
  __tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (depth == 0) {   return (r).next_lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; });
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_EOF) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
  }
  return lex;
}
struct lexer_Lexer parser_skip_balanced_braces(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  int32_t depth = 1;
  while (depth > 0) {
    struct lexer_LexerResult r = lexer_lexer_next(lex, source);
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((depth = depth + 1));
 } else (__tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((depth = depth - 1));
  __tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (depth == 0) {   return (r).next_lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; });
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_EOF) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
  }
  return lex;
}
struct lexer_Lexer parser_skip_balanced_braces_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  int32_t depth = 1;
  while (depth > 0) {
    struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((depth = depth + 1));
 } else (__tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((depth = depth - 1));
  __tmp = ({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (depth == 0) {   return (r).next_lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; });
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; })) ; __tmp; }));
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind == token_TokenKind_TOKEN_EOF) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
  }
  return lex;
}
struct lexer_LexerResult parser_skip_one_if_core(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
  (void)((lex = parser_skip_balanced_parens((r).next_lex, source)));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((lex = parser_skip_balanced_braces((r).next_lex, source)));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
  }
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  return r;
}
struct lexer_LexerResult parser_skip_one_if_statement(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = parser_skip_one_if_core(lex, source);
  while (((r).tok).kind == token_TokenKind_TOKEN_ELSE) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_IF) {   (void)((lex = (r).next_lex));
  (void)((r = parser_skip_one_if_core(lex, source)));
 } else {   __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((lex = parser_skip_balanced_braces((r).next_lex, source)));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
  }
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } ; __tmp; }));
  }
  return r;
}
struct lexer_LexerResult parser_skip_one_if_core_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
  (void)(({ struct lexer_LexerResult __tmp = (struct lexer_LexerResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return r;
 } else (__tmp = (struct lexer_LexerResult){0}) ; __tmp; }));
  (void)((lex = parser_skip_balanced_parens_buf((r).next_lex, data, len)));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((lex = parser_skip_balanced_braces_buf((r).next_lex, data, len)));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else {   while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
  }
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  return r;
}
struct lexer_LexerResult parser_skip_one_if_statement_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_LexerResult r = parser_skip_one_if_core_buf(lex, data, len);
  while (((r).tok).kind == token_TokenKind_TOKEN_ELSE) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_IF) {   (void)((lex = (r).next_lex));
  (void)((r = parser_skip_one_if_core_buf(lex, data, len)));
 } else {   __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((lex = parser_skip_balanced_braces_buf((r).next_lex, data, len)));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else {   while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf(lex, data, len)));
  }
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } ; __tmp; }));
  }
  return r;
}
struct lexer_Lexer parser_diag_lex_after_imports(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  return parser_skip_imports(lex, source);
}
struct lexer_LexerResult parser_diag_after_imports_then_structs(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  while (((r).tok).kind == token_TokenKind_TOKEN_STRUCT) {
    (void)((lex = parser_skip_one_struct(lex, source)));
    (void)((r = lexer_lexer_next(lex, source)));
  }
  return r;
}
int32_t parser_diag_fail_at_token_kind(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = parser_diag_lex_after_imports(source);
  struct lexer_LexerResult r = parser_diag_after_imports_then_structs(lex, source);
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).ident_len <= 0 || ((r).tok).ident_len > 63) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RPAREN) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  while (((r).tok).kind == token_TokenKind_TOKEN_IDENT) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_U8 || ((r).tok).kind == token_TokenKind_TOKEN_U32 || ((r).tok).kind == token_TokenKind_TOKEN_U64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACKET) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACKET) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_U8) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   return ((r).tok).kind;
 } ; __tmp; })) ; __tmp; })) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_COMMA) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = 0) ; __tmp; }));
  }
 } ; __tmp; }));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_U8 || ((r).tok).kind == token_TokenKind_TOKEN_U32 || ((r).tok).kind == token_TokenKind_TOKEN_U64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   return ((r).tok).kind;
 } ; __tmp; })) ; __tmp; }));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = parser_body_skip_let_const_then_if(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_INT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RETURN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE && ((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ enum token_TokenKind __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  __tmp = ({ enum token_TokenKind __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return ((r).tok).kind;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return ((r).tok).kind;
}
void parser_copy_slice_to_name64(struct shulang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t out[64]) {
  int32_t i = 0;
  while (i < nlen) {
    (void)(({ int32_t __tmp = 0; if (start + i < (source)->length) {   (void)(((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), 0) : ((out)[i] = (start + i < 0 || (size_t)(start + i) >= (source)->length ? (shulang_panic_(1, 0), (source)->data[0]) : (source)->data[start + i]), 0))));
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
}
void parser_copy_slice_to_name64_buf(uint8_t * restrict source, int32_t source_len, size_t start, int32_t nlen, uint8_t out[64]) {
  int32_t i = 0;
  while (i < nlen) {
    (void)(((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), 0) : ((out)[i] = (source)[start + i], 0))));
    (void)((i = i + 1));
  }
}
struct parser_OneFuncResult parser_parse_one_function(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  uint8_t dummy_name[64] = { 0 };
  uint8_t empty32[32] = { 0 };
  uint8_t dummy_pnames[16][32] = { 0 };
  int32_t dummy_plens[16] = { 0 };
  int32_t num_params = 0;
  uint8_t param_names[16][32] ;
  memcpy(param_names, dummy_pnames, sizeof(param_names));
  int32_t param_name_lens[16] ;
  memcpy(param_name_lens, dummy_plens, sizeof(param_name_lens));
  uint8_t empty64[64] = { 0 };
  uint8_t dummy_const_names[24][64] = { 0 };
  int32_t dummy_const_lens[24] = { 0 };
  int32_t dummy_const_vals[24] = { 0 };
  uint8_t dummy_let_names[24][64] = { 0 };
  int32_t dummy_let_lens[24] = { 0 };
  int32_t dummy_let_vals[24] = { 0 };
  int32_t num_consts = 0;
  uint8_t const_names[24][64] ;
  memcpy(const_names, dummy_const_names, sizeof(const_names));
  int32_t const_name_lens[24] ;
  memcpy(const_name_lens, dummy_const_lens, sizeof(const_name_lens));
  int32_t const_init_vals[24] ;
  memcpy(const_init_vals, dummy_const_vals, sizeof(const_init_vals));
  int32_t num_lets = 0;
  uint8_t let_names[24][64] ;
  memcpy(let_names, dummy_let_names, sizeof(let_names));
  int32_t let_name_lens[24] ;
  memcpy(let_name_lens, dummy_let_lens, sizeof(let_name_lens));
  int32_t let_init_vals[24] ;
  memcpy(let_init_vals, dummy_let_vals, sizeof(let_init_vals));
  int has_if_expr = 0;
  int if_cond_true = 0;
  int32_t if_then_val = 0;
  int32_t if_else_val = 0;
  int has_mul = 0;
  int32_t mul_right_val = 0;
  int has_binop = 0;
  int32_t binop_right_val = 0;
  int has_unary_neg = 0;
  int32_t ret_val = 0;
  int has_call_expr = 0;
  uint8_t call_callee_name[64] ;
  memcpy(call_callee_name, dummy_name, sizeof(call_callee_name));
  int32_t call_callee_len = 0;
  size_t name_start = 0;
  int32_t func_name_len_storage[1] = { 0 };
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  uint8_t name[64] ;
  memcpy(name, dummy_name, sizeof(name));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(((func_name_len_storage)[0] = ((r).tok).ident_len));
  (void)(({ int32_t __tmp = 0; if ((func_name_len_storage)[0] <= 0 || (func_name_len_storage)[0] > 63) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((name_start = ((r).next_lex).pos - (func_name_len_storage)[0]));
  (void)(parser_copy_slice_to_name64(source, name_start, (func_name_len_storage)[0], name));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((lex = (r).next_lex));
 } else {   while (1) {
    (void)(({ int32_t __tmp = 0; if (num_params >= 16) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
    size_t pstart = (lex).pos;
    int32_t plen = ((r).tok).ident_len;
    (void)(({ int32_t __tmp = 0; if (plen <= 0 || plen > 31) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
    int32_t pi = 0;
    while (pi < plen) {
      (void)(({ int32_t __tmp = 0; if (pstart + pi < (source)->length) {   (void)(((pi < 0 || (pi) >= 32 ? (shulang_panic_(1, 0), 0) : (((num_params < 0 || (num_params) >= 16 ? (shulang_panic_(1, 0), (param_names)[0]) : (param_names)[num_params]))[pi] = (pstart + pi < 0 || (size_t)(pstart + pi) >= (source)->length ? (shulang_panic_(1, 0), (source)->data[0]) : (source)->data[pstart + pi]), 0))));
 } else (__tmp = 0) ; __tmp; }));
      (void)((pi = pi + 1));
    }
    (void)(((num_params < 0 || (num_params) >= 16 ? (shulang_panic_(1, 0), 0) : ((param_name_lens)[num_params] = plen, 0))));
    (void)((num_params = num_params + 1));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_U8 || ((r).tok).kind == token_TokenKind_TOKEN_U32 || ((r).tok).kind == token_TokenKind_TOKEN_U64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((lex = (r).next_lex));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COMMA) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
  }
 } ; __tmp; }));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_I32 || ((r).tok).kind == token_TokenKind_TOKEN_I64 || ((r).tok).kind == token_TokenKind_TOKEN_BOOL || ((r).tok).kind == token_TokenKind_TOKEN_U8 || ((r).tok).kind == token_TokenKind_TOKEN_U32 || ((r).tok).kind == token_TokenKind_TOKEN_U64 || ((r).tok).kind == token_TokenKind_TOKEN_VOID || ((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LBRACE) {   (void)((lex = (r).next_lex));
  (void)((r = parser_body_skip_let_const_then_if(lex, source)));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_INT) {   (void)((ret_val = ((r).tok).int_val));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RETURN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_IF) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_TRUE && ((r).tok).kind != token_TokenKind_TOKEN_FALSE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((if_cond_true = ((r).tok).kind == token_TokenKind_TOKEN_TRUE));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RPAREN) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((if_then_val = ((r).tok).int_val));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_ELSE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((if_else_val = ((r).tok).int_val));
  (void)((has_if_expr = 1));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_MINUS) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((ret_val = ((r).tok).int_val));
  (void)((has_unary_neg = 1));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_INT) {   (void)((ret_val = ((r).tok).int_val));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_PLUS) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((binop_right_val = ((r).tok).int_val));
  (void)((has_binop = 1));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((mul_right_val = ((r).tok).int_val));
  (void)((has_mul = 1));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STAR) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((mul_right_val = ((r).tok).int_val));
  (void)((has_mul = 1));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((lex = (r).next_lex));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; }));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = (func_name_len_storage)[0]; _t.num_params = num_params; _t.num_consts = num_consts; _t.num_lets = num_lets; _t.has_if_expr = has_if_expr; _t.if_cond_true = if_cond_true; _t.if_then_val = if_then_val; _t.if_else_val = if_else_val; _t.has_mul = has_mul; _t.mul_right_val = mul_right_val; _t.has_binop = has_binop; _t.binop_right_val = binop_right_val; _t.has_unary_neg = has_unary_neg; _t.return_val = ret_val; _t.has_call_expr = has_call_expr; _t.call_callee_len = call_callee_len; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, param_names, sizeof(_t.param_names)); memcpy(_t.param_name_lens, param_name_lens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, const_name_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, const_init_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, let_name_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, let_init_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, call_callee_name, sizeof(_t.call_callee_name)); _t; });
 } else {   (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_IDENT) {   int32_t clen = ((r).tok).ident_len;
  __tmp = ({ int32_t __tmp = 0; if (clen > 0 && clen <= 63) {   size_t cstart = ((r).next_lex).pos - clen;
  (void)(parser_copy_slice_to_name64(source, cstart, clen, call_callee_name));
  (void)((call_callee_len = clen));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_LPAREN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RPAREN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)((has_call_expr = 1));
  (void)((ret_val = 0));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((lex = (r).next_lex));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = (func_name_len_storage)[0]; _t.num_params = num_params; _t.num_consts = num_consts; _t.num_lets = num_lets; _t.has_if_expr = has_if_expr; _t.if_cond_true = if_cond_true; _t.if_then_val = if_then_val; _t.if_else_val = if_else_val; _t.has_mul = has_mul; _t.mul_right_val = mul_right_val; _t.has_binop = has_binop; _t.binop_right_val = binop_right_val; _t.has_unary_neg = has_unary_neg; _t.return_val = ret_val; _t.has_call_expr = has_call_expr; _t.call_callee_len = call_callee_len; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, param_names, sizeof(_t.param_names)); memcpy(_t.param_name_lens, param_name_lens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, const_name_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, const_init_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, let_name_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, let_init_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, call_callee_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  while (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_EOF) {
    (void)((lex = (r).next_lex));
    (void)((r = lexer_lexer_next(lex, source)));
  }
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)((ret_val = 0));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((lex = (r).next_lex));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; }));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = (func_name_len_storage)[0]; _t.num_params = num_params; _t.num_consts = num_consts; _t.num_lets = num_lets; _t.has_if_expr = has_if_expr; _t.if_cond_true = if_cond_true; _t.if_then_val = if_then_val; _t.if_else_val = if_else_val; _t.has_mul = has_mul; _t.mul_right_val = mul_right_val; _t.has_binop = has_binop; _t.binop_right_val = binop_right_val; _t.has_unary_neg = has_unary_neg; _t.return_val = ret_val; _t.has_call_expr = has_call_expr; _t.call_callee_len = call_callee_len; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, param_names, sizeof(_t.param_names)); memcpy(_t.param_name_lens, param_name_lens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, const_name_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, const_init_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, let_name_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, let_init_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, call_callee_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; })) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RBRACE) {   (void)((lex = (r).next_lex));
 } else (__tmp = ({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((lex = (r).next_lex));
 } else {   return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; });
 } else {   (void)((lex = parser_skip_balanced_braces(lex, source)));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = (func_name_len_storage)[0]; _t.num_params = num_params; _t.num_consts = num_consts; _t.num_lets = num_lets; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, param_names, sizeof(_t.param_names)); memcpy(_t.param_name_lens, param_name_lens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, const_name_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, const_init_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, let_name_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, let_init_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } ; __tmp; })) ; __tmp; }));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = (func_name_len_storage)[0]; _t.num_params = num_params; _t.num_consts = num_consts; _t.num_lets = num_lets; _t.has_if_expr = has_if_expr; _t.if_cond_true = if_cond_true; _t.if_then_val = if_then_val; _t.if_else_val = if_else_val; _t.has_mul = has_mul; _t.mul_right_val = mul_right_val; _t.has_binop = has_binop; _t.binop_right_val = binop_right_val; _t.has_unary_neg = has_unary_neg; _t.return_val = ret_val; _t.has_call_expr = has_call_expr; _t.call_callee_len = call_callee_len; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, param_names, sizeof(_t.param_names)); memcpy(_t.param_name_lens, param_name_lens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, const_name_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, const_init_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, let_name_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, let_init_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, call_callee_name, sizeof(_t.call_callee_name)); _t; });
}
void parser_parse_into_init(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module) {
  (void)(ast_ast_arena_init(arena));
  (void)(((module)->num_funcs = 0));
  (void)(((module)->main_func_index = (-1)));
  (void)(((module)->num_imports = 0));
}
struct lexer_Lexer parser_skip_imports(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  while (1) {
    struct lexer_LexerResult r = lexer_lexer_next(lex, source);
    (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IMPORT) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
    (void)((lex = (r).next_lex));
    while (1) {
      struct lexer_LexerResult r2 = lexer_lexer_next(lex, source);
      (void)(({ int32_t __tmp = 0; if (((r2).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r2).next_lex));
  break;
 } else (__tmp = 0) ; __tmp; }));
      (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r2).tok).kind == token_TokenKind_TOKEN_EOF) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
      (void)((lex = (r2).next_lex));
    }
  }
  return lex;
}
void parser_collect_imports(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source, struct ast_Module * restrict module, struct parser_CollectImportsResult * restrict out) {
  fprintf(stderr, "collect_imports: source_len=%zu\n", (size_t)(source)->length); fflush(stderr);
  uint8_t path_buf[64] = { 0 };
  int32_t path_len = 0;
  while (1) {
    struct lexer_LexerResult r = lexer_lexer_next((out)->lex, source);
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IMPORT) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(((out)->lex = (r).next_lex));
    (void)((path_len = 0));
    (void)((r = lexer_lexer_next((out)->lex, source)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).ident_len <= 0 || ((r).tok).ident_len > 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
    size_t ident_start = ((r).next_lex).pos - ((r).tok).ident_len;
    (void)(parser_copy_slice_to_name64(source, ident_start, ((r).tok).ident_len, path_buf));
    (void)((path_len = ((r).tok).ident_len));
    (void)(((out)->lex = (r).next_lex));
    (void)((r = lexer_lexer_next((out)->lex, source)));
    while (((r).tok).kind == token_TokenKind_TOKEN_DOT) {
      (void)(({ int32_t __tmp = 0; if (path_len >= 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
      uint8_t dot_u8 = 46;
      (void)(((path_len < 0 || (path_len) >= 64 ? (shulang_panic_(1, 0), 0) : ((path_buf)[path_len] = dot_u8, 0))));
      (void)((path_len = path_len + 1));
      (void)(((out)->lex = (r).next_lex));
      (void)((r = lexer_lexer_next((out)->lex, source)));
      (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return;
 } else (__tmp = 0) ; __tmp; }));
      (void)(({ int32_t __tmp = 0; if (path_len + ((r).tok).ident_len > 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
      int32_t i = 0;
      while (i < ((r).tok).ident_len) {
      (void)(({ int32_t __tmp = 0; if (((out)->lex).pos + i < (source)->length) {   (void)(((path_len + i < 0 || (path_len + i) >= 64 ? (shulang_panic_(1, 0), 0) : ((path_buf)[path_len + i] = (((out)->lex).pos + i < 0 || (size_t)(((out)->lex).pos + i) >= (source)->length ? (shulang_panic_(1, 0), (source)->data[0]) : (source)->data[((out)->lex).pos + i]), 0))));
 } else (__tmp = 0) ; __tmp; }));
      (void)((i = i + 1));
      }
      (void)((path_len = path_len + ((r).tok).ident_len));
      (void)(((out)->lex = (r).next_lex));
      (void)((r = lexer_lexer_next((out)->lex, source)));
    }
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((module)->num_imports >= 32) {   return;
 } else (__tmp = 0) ; __tmp; }));
    int32_t base = (module)->num_imports * 64;
    int32_t j = 0;
    while (j < 64) {
      (void)(({ int32_t __tmp = 0; if (j < path_len) {   (void)(((base + j < 0 || (base + j) >= 2048 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_data)[base + j] = (j < 0 || (j) >= 64 ? (shulang_panic_(1, 0), (path_buf)[0]) : (path_buf)[j]), 0))));
 } else {   uint8_t z = 0;
  (void)(((base + j < 0 || (base + j) >= 2048 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_data)[base + j] = z, 0))));
 } ; __tmp; }));
      (void)((j = j + 1));
    }
    (void)((((module)->num_imports < 0 || ((module)->num_imports) >= 32 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_lens)[(module)->num_imports] = path_len, 0))));
    (void)(((module)->num_imports = (module)->num_imports + 1));
    (void)(((out)->lex = (r).next_lex));
  }
  (void)(((out)->lex = lex));
}
void parser_collect_imports_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len, struct ast_Module * restrict module, struct parser_CollectImportsResult * restrict out) {
  uint8_t path_buf[64] = { 0 };
  int32_t path_len = 0;
  while (1) {
    struct lexer_LexerResult r = lexer_lexer_next_buf((out)->lex, data, len);
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IMPORT) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(((out)->lex = (r).next_lex));
    (void)((path_len = 0));
    (void)((r = lexer_lexer_next_buf((out)->lex, data, len)));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).ident_len <= 0 || ((r).tok).ident_len > 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
    size_t ident_start = ((r).next_lex).pos - ((r).tok).ident_len;
    (void)(parser_copy_slice_to_name64_buf(data, len, ident_start, ((r).tok).ident_len, path_buf));
    (void)((path_len = ((r).tok).ident_len));
    (void)(((out)->lex = (r).next_lex));
    (void)((r = lexer_lexer_next_buf((out)->lex, data, len)));
    while (((r).tok).kind == token_TokenKind_TOKEN_DOT) {
      (void)(({ int32_t __tmp = 0; if (path_len >= 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
      uint8_t dot_u8 = 46;
      (void)(((path_len < 0 || (path_len) >= 64 ? (shulang_panic_(1, 0), 0) : ((path_buf)[path_len] = dot_u8, 0))));
      (void)((path_len = path_len + 1));
      (void)(((out)->lex = (r).next_lex));
      (void)((r = lexer_lexer_next_buf((out)->lex, data, len)));
      (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return;
 } else (__tmp = 0) ; __tmp; }));
      (void)(({ int32_t __tmp = 0; if (path_len + ((r).tok).ident_len > 63) {   return;
 } else (__tmp = 0) ; __tmp; }));
      int32_t i = 0;
      while (i < ((r).tok).ident_len) {
      (void)(((path_len + i < 0 || (path_len + i) >= 64 ? (shulang_panic_(1, 0), 0) : ((path_buf)[path_len + i] = (data)[((out)->lex).pos + i], 0))));
      (void)((i = i + 1));
      }
      (void)((path_len = path_len + ((r).tok).ident_len));
      (void)(((out)->lex = (r).next_lex));
      (void)((r = lexer_lexer_next_buf((out)->lex, data, len)));
    }
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON) {   return;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((module)->num_imports >= 32) {   return;
 } else (__tmp = 0) ; __tmp; }));
    int32_t base = (module)->num_imports * 64;
    int32_t j = 0;
    while (j < 64) {
      (void)(({ int32_t __tmp = 0; if (j < path_len) {   (void)(((base + j < 0 || (base + j) >= 2048 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_data)[base + j] = (j < 0 || (j) >= 64 ? (shulang_panic_(1, 0), (path_buf)[0]) : (path_buf)[j]), 0))));
 } else {   uint8_t z = 0;
  (void)(((base + j < 0 || (base + j) >= 2048 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_data)[base + j] = z, 0))));
 } ; __tmp; }));
      (void)((j = j + 1));
    }
    (void)((((module)->num_imports < 0 || ((module)->num_imports) >= 32 ? (shulang_panic_(1, 0), 0) : (((module)->import_path_lens)[(module)->num_imports] = path_len, 0))));
    (void)(((module)->num_imports = (module)->num_imports + 1));
    (void)(((out)->lex = (r).next_lex));
  }
  (void)(((out)->lex = lex));
}
struct lexer_Lexer parser_skip_one_struct(struct lexer_Lexer lex, struct shulang_slice_uint8_t * source) {
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_STRUCT) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next(lex, source)));
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = parser_skip_balanced_braces((r).next_lex, source)));
  return lex;
}
struct lexer_Lexer parser_skip_one_struct_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_STRUCT) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct lexer_Lexer __tmp = (struct lexer_Lexer){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return lex;
 } else (__tmp = (struct lexer_Lexer){0}) ; __tmp; }));
  (void)((lex = parser_skip_balanced_braces_buf((r).next_lex, data, len)));
  return lex;
}
struct parser_OneFuncResult parser_parse_one_function_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  uint8_t empty32[32] = { 0 };
  uint8_t dummy_pnames[16][32] = { 0 };
  int32_t dummy_plens[16] = { 0 };
  uint8_t empty64[64] = { 0 };
  uint8_t dummy_name[64] = { 0 };
  uint8_t dummy_const_names[24][64] = { 0 };
  int32_t dummy_const_lens[24] = { 0 };
  int32_t dummy_const_vals[24] = { 0 };
  uint8_t dummy_let_names[24][64] = { 0 };
  int32_t dummy_let_lens[24] = { 0 };
  int32_t dummy_let_vals[24] = { 0 };
  struct parser_OneFuncResult fail = ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 0; _t.next_lex = lex; _t.name_len = 0; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = 0; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, dummy_name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
  struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
  int32_t name_len = ((r).tok).ident_len;
  size_t name_start = ((r).next_lex).pos - name_len;
  uint8_t name[64] ;
  memcpy(name, dummy_name, sizeof(name));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (name_len <= 0 || name_len > 63) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)(parser_copy_slice_to_name64_buf(data, len, name_start, name_len, name));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LPAREN) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_RPAREN) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_COLON) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_I32 && ((r).tok).kind != token_TokenKind_TOKEN_I64 && ((r).tok).kind != token_TokenKind_TOKEN_BOOL && ((r).tok).kind != token_TokenKind_TOKEN_VOID && ((r).tok).kind != token_TokenKind_TOKEN_U8 && ((r).tok).kind != token_TokenKind_TOKEN_U32 && ((r).tok).kind != token_TokenKind_TOKEN_U64 && ((r).tok).kind != token_TokenKind_TOKEN_IDENT) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_LBRACE) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  (void)((r = parser_body_skip_let_const_then_if_buf(lex, data, len)));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_INT) {   int32_t ret_val = ((r).tok).int_val;
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = name_len; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = ret_val; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_RETURN) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_INT) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  int32_t ret_val = ((r).tok).int_val;
  (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_SEMICOLON && ((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)(({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind == token_TokenKind_TOKEN_SEMICOLON) {   (void)((lex = (r).next_lex));
  (void)((r = lexer_lexer_next_buf(lex, data, len)));
  __tmp = ({ struct parser_OneFuncResult __tmp = (struct parser_OneFuncResult){0}; if (((r).tok).kind != token_TokenKind_TOKEN_RBRACE) {   return fail;
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; });
 } else (__tmp = (struct parser_OneFuncResult){0}) ; __tmp; }));
  (void)((lex = (r).next_lex));
  return ({ struct parser_OneFuncResult _t = { 0 }; _t.ok = 1; _t.next_lex = lex; _t.name_len = name_len; _t.num_params = 0; _t.num_consts = 0; _t.num_lets = 0; _t.has_if_expr = 0; _t.if_cond_true = 0; _t.if_then_val = 0; _t.if_else_val = 0; _t.has_mul = 0; _t.mul_right_val = 0; _t.has_binop = 0; _t.binop_right_val = 0; _t.has_unary_neg = 0; _t.return_val = ret_val; _t.has_call_expr = 0; _t.call_callee_len = 0; memcpy(_t.name, name, sizeof(_t.name)); memcpy(_t.param_names, dummy_pnames, sizeof(_t.param_names)); memcpy(_t.param_name_lens, dummy_plens, sizeof(_t.param_name_lens)); memcpy(_t.const_names, dummy_const_names, sizeof(_t.const_names)); memcpy(_t.const_name_lens, dummy_const_lens, sizeof(_t.const_name_lens)); memcpy(_t.const_init_vals, dummy_const_vals, sizeof(_t.const_init_vals)); memcpy(_t.let_names, dummy_let_names, sizeof(_t.let_names)); memcpy(_t.let_name_lens, dummy_let_lens, sizeof(_t.let_name_lens)); memcpy(_t.let_init_vals, dummy_let_vals, sizeof(_t.let_init_vals)); memcpy(_t.call_callee_name, dummy_name, sizeof(_t.call_callee_name)); _t; });
 } else (__tmp = 0) ; __tmp; }));
  return fail;
}
struct parser_ParseIntoResult parser_parse_into(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module, struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  int32_t main_idx = (-1);
  struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
  (void)(parser_collect_imports(lex, source, module, (&(import_res))));
  (void)((lex = (import_res).lex));
  fprintf(stderr, "parse_into: after collect_imports\n"); fflush(stderr);
  int32_t out_idx = main_idx;
  int32_t out_idx_storage[1] = { 0 };
  while (1) {
    struct lexer_LexerResult r = lexer_lexer_next(lex, source);
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STRUCT) {   (void)((lex = parser_skip_one_struct(lex, source)));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   break;
 } else (__tmp = 0) ; __tmp; }));
    fprintf(stderr, "parse_into: before parse_one_function\n"); fflush(stderr);
    struct parser_OneFuncResult res = parser_parse_one_function(lex, source);
    (void)(({ int32_t __tmp = 0; if ((!(res).ok)) {   break;
 } else (__tmp = 0) ; __tmp; }));
    int32_t is_main_storage[1] = { 0 };
    (void)(({ int32_t __tmp = 0; if ((res).name_len == 4 && ((res).name)[0] == 109 && (1 < 0 || (1) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[1]) == 97 && (2 < 0 || (2) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[2]) == 105 && (3 < 0 || (3) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[3]) == 110) {   (void)(((is_main_storage)[0] = 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((module)->num_funcs >= 256) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    int32_t type_ref = ast_ast_arena_type_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (type_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Type t = ast_ast_arena_type_get(arena, type_ref);
    (void)(((t).kind = ast_TypeKind_TYPE_I32));
    (void)(((t).name_len = 0));
    (void)(((t).elem_type_ref = 0));
    (void)(((t).array_size = 0));
    (void)(ast_ast_arena_type_set(arena, type_ref, t));
    int32_t expr_ref = ast_ast_arena_expr_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (expr_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
    (void)(((e).kind = ast_ExprKind_EXPR_LIT));
    (void)(((e).resolved_type_ref = type_ref));
    (void)(((e).line = 0));
    (void)(((e).col = 0));
    (void)(((e).int_val = (res).return_val));
    (void)(((e).binop_left_ref = 0));
    (void)(((e).binop_right_ref = 0));
    (void)(((e).unary_operand_ref = 0));
    (void)(((e).if_cond_ref = 0));
    (void)(((e).if_then_ref = 0));
    (void)(((e).if_else_ref = 0));
    (void)(((e).block_ref = 0));
    (void)(((e).match_matched_ref = 0));
    (void)(((e).match_num_arms = 0));
    (void)(ast_expr_init_match_enum((&(e))));
    (void)(((e).field_access_base_ref = 0));
    (void)(((e).field_access_field_len = 0));
    (void)(((e).field_access_is_enum_variant = 0));
    (void)(((e).field_access_offset = 0));
    (void)(((e).index_base_ref = 0));
    (void)(((e).index_index_ref = 0));
    (void)(((e).index_base_is_slice = 0));
    (void)(((e).call_callee_ref = 0));
    (void)(((e).call_num_args = 0));
    (void)(((e).method_call_base_ref = 0));
    (void)(((e).method_call_name_len = 0));
    (void)(((e).method_call_num_args = 0));
    (void)(((e).const_folded_val = 0));
    (void)(((e).const_folded_valid = 0));
    (void)(((e).index_proven_in_bounds = 0));
    (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
    int32_t final_expr_ref = expr_ref;
    (void)(({ int32_t __tmp = 0; if ((res).has_mul && (!(res).has_binop)) {   int32_t mul_right_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_right_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_right_ref);
  (void)(((mre).kind = ast_ExprKind_EXPR_LIT));
  (void)(((mre).resolved_type_ref = type_ref));
  (void)(((mre).line = 0));
  (void)(((mre).col = 0));
  (void)(((mre).int_val = (res).mul_right_val));
  (void)(((mre).binop_left_ref = 0));
  (void)(((mre).binop_right_ref = 0));
  (void)(((mre).unary_operand_ref = 0));
  (void)(((mre).if_cond_ref = 0));
  (void)(((mre).if_then_ref = 0));
  (void)(((mre).if_else_ref = 0));
  (void)(((mre).block_ref = 0));
  (void)(((mre).match_matched_ref = 0));
  (void)(((mre).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(mre))));
  (void)(((mre).field_access_base_ref = 0));
  (void)(((mre).field_access_field_len = 0));
  (void)(((mre).field_access_is_enum_variant = 0));
  (void)(((mre).field_access_offset = 0));
  (void)(((mre).index_base_ref = 0));
  (void)(((mre).index_index_ref = 0));
  (void)(((mre).index_base_is_slice = 0));
  (void)(((mre).call_callee_ref = 0));
  (void)(((mre).call_num_args = 0));
  (void)(((mre).method_call_base_ref = 0));
  (void)(((mre).method_call_name_len = 0));
  (void)(((mre).method_call_num_args = 0));
  (void)(((mre).const_folded_val = 0));
  (void)(((mre).const_folded_valid = 0));
  (void)(((mre).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_right_ref, mre));
  int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
  (void)(((me).kind = ast_ExprKind_EXPR_MUL));
  (void)(((me).resolved_type_ref = type_ref));
  (void)(((me).line = 0));
  (void)(((me).col = 0));
  (void)(((me).int_val = 0));
  (void)(((me).binop_left_ref = final_expr_ref));
  (void)(((me).binop_right_ref = mul_right_ref));
  (void)(((me).unary_operand_ref = 0));
  (void)(((me).if_cond_ref = 0));
  (void)(((me).if_then_ref = 0));
  (void)(((me).if_else_ref = 0));
  (void)(((me).block_ref = 0));
  (void)(((me).match_matched_ref = 0));
  (void)(((me).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(me))));
  (void)(((me).field_access_base_ref = 0));
  (void)(((me).field_access_field_len = 0));
  (void)(((me).field_access_is_enum_variant = 0));
  (void)(((me).field_access_offset = 0));
  (void)(((me).index_base_ref = 0));
  (void)(((me).index_index_ref = 0));
  (void)(((me).index_base_is_slice = 0));
  (void)(((me).call_callee_ref = 0));
  (void)(((me).call_num_args = 0));
  (void)(((me).method_call_base_ref = 0));
  (void)(((me).method_call_name_len = 0));
  (void)(((me).method_call_num_args = 0));
  (void)(((me).const_folded_val = 0));
  (void)(((me).const_folded_valid = 0));
  (void)(((me).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_ref, me));
  (void)((final_expr_ref = mul_ref));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((res).has_if_expr) {   int32_t bool_type_ref = ast_ast_arena_type_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (bool_type_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Type bt = ast_ast_arena_type_get(arena, bool_type_ref);
  (void)(((bt).kind = ast_TypeKind_TYPE_BOOL));
  (void)(((bt).name_len = 0));
  (void)(((bt).elem_type_ref = 0));
  (void)(((bt).array_size = 0));
  (void)(ast_ast_arena_type_set(arena, bool_type_ref, bt));
  int32_t cond_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (cond_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr ce = ast_ast_arena_expr_get(arena, cond_ref);
  (void)(((ce).kind = ast_ExprKind_EXPR_BOOL_LIT));
  (void)(((ce).resolved_type_ref = bool_type_ref));
  (void)(((ce).line = 0));
  (void)(((ce).col = 0));
  (void)(({ int32_t __tmp = 0; if ((res).if_cond_true) {   (void)(((ce).int_val = 1));
 } else {   (void)(((ce).int_val = 0));
 } ; __tmp; }));
  (void)(((ce).binop_left_ref = 0));
  (void)(((ce).binop_right_ref = 0));
  (void)(((ce).unary_operand_ref = 0));
  (void)(((ce).if_cond_ref = 0));
  (void)(((ce).if_then_ref = 0));
  (void)(((ce).if_else_ref = 0));
  (void)(((ce).block_ref = 0));
  (void)(((ce).match_matched_ref = 0));
  (void)(((ce).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ce))));
  (void)(((ce).field_access_base_ref = 0));
  (void)(((ce).field_access_field_len = 0));
  (void)(((ce).field_access_is_enum_variant = 0));
  (void)(((ce).field_access_offset = 0));
  (void)(((ce).index_base_ref = 0));
  (void)(((ce).index_index_ref = 0));
  (void)(((ce).index_base_is_slice = 0));
  (void)(((ce).call_callee_ref = 0));
  (void)(((ce).call_num_args = 0));
  (void)(((ce).method_call_base_ref = 0));
  (void)(((ce).method_call_name_len = 0));
  (void)(((ce).method_call_num_args = 0));
  (void)(((ce).const_folded_val = 0));
  (void)(((ce).const_folded_valid = 0));
  (void)(((ce).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, cond_ref, ce));
  int32_t then_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (then_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr te = ast_ast_arena_expr_get(arena, then_ref);
  (void)(((te).kind = ast_ExprKind_EXPR_LIT));
  (void)(((te).resolved_type_ref = type_ref));
  (void)(((te).line = 0));
  (void)(((te).col = 0));
  (void)(((te).int_val = (res).if_then_val));
  (void)(((te).binop_left_ref = 0));
  (void)(((te).binop_right_ref = 0));
  (void)(((te).unary_operand_ref = 0));
  (void)(((te).if_cond_ref = 0));
  (void)(((te).if_then_ref = 0));
  (void)(((te).if_else_ref = 0));
  (void)(((te).block_ref = 0));
  (void)(((te).match_matched_ref = 0));
  (void)(((te).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(te))));
  (void)(((te).field_access_base_ref = 0));
  (void)(((te).field_access_field_len = 0));
  (void)(((te).field_access_is_enum_variant = 0));
  (void)(((te).field_access_offset = 0));
  (void)(((te).index_base_ref = 0));
  (void)(((te).index_index_ref = 0));
  (void)(((te).index_base_is_slice = 0));
  (void)(((te).call_callee_ref = 0));
  (void)(((te).call_num_args = 0));
  (void)(((te).method_call_base_ref = 0));
  (void)(((te).method_call_name_len = 0));
  (void)(((te).method_call_num_args = 0));
  (void)(((te).const_folded_val = 0));
  (void)(((te).const_folded_valid = 0));
  (void)(((te).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, then_ref, te));
  int32_t else_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (else_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr ee = ast_ast_arena_expr_get(arena, else_ref);
  (void)(((ee).kind = ast_ExprKind_EXPR_LIT));
  (void)(((ee).resolved_type_ref = type_ref));
  (void)(((ee).line = 0));
  (void)(((ee).col = 0));
  (void)(((ee).int_val = (res).if_else_val));
  (void)(((ee).binop_left_ref = 0));
  (void)(((ee).binop_right_ref = 0));
  (void)(((ee).unary_operand_ref = 0));
  (void)(((ee).if_cond_ref = 0));
  (void)(((ee).if_then_ref = 0));
  (void)(((ee).if_else_ref = 0));
  (void)(((ee).block_ref = 0));
  (void)(((ee).match_matched_ref = 0));
  (void)(((ee).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ee))));
  (void)(((ee).field_access_base_ref = 0));
  (void)(((ee).field_access_field_len = 0));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((res).has_binop) {   int32_t left_ref = final_expr_ref;
  int32_t right_ref = 0;
  (void)(({ int32_t __tmp = 0; if ((res).has_mul) {   int32_t mul_left_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_left_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr mle = ast_ast_arena_expr_get(arena, mul_left_ref);
  (void)(((mle).kind = ast_ExprKind_EXPR_LIT));
  (void)(((mle).resolved_type_ref = type_ref));
  (void)(((mle).line = 0));
  (void)(((mle).col = 0));
  (void)(((mle).int_val = (res).binop_right_val));
  (void)(((mle).binop_left_ref = 0));
  (void)(((mle).binop_right_ref = 0));
  (void)(((mle).unary_operand_ref = 0));
  (void)(((mle).if_cond_ref = 0));
  (void)(((mle).if_then_ref = 0));
  (void)(((mle).if_else_ref = 0));
  (void)(((mle).block_ref = 0));
  (void)(((mle).match_matched_ref = 0));
  (void)(((mle).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(mle))));
  (void)(((mle).field_access_base_ref = 0));
  (void)(((mle).field_access_field_len = 0));
  (void)(((mle).field_access_is_enum_variant = 0));
  (void)(((mle).field_access_offset = 0));
  (void)(((mle).index_base_ref = 0));
  (void)(((mle).index_index_ref = 0));
  (void)(((mle).index_base_is_slice = 0));
  (void)(((mle).call_callee_ref = 0));
  (void)(((mle).call_num_args = 0));
  (void)(((mle).method_call_base_ref = 0));
  (void)(((mle).method_call_name_len = 0));
  (void)(((mle).method_call_num_args = 0));
  (void)(((mle).const_folded_val = 0));
  (void)(((mle).const_folded_valid = 0));
  (void)(((mle).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_left_ref, mle));
  int32_t mul_r_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_r_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_r_ref);
  (void)(((mre).kind = ast_ExprKind_EXPR_LIT));
  (void)(((mre).resolved_type_ref = type_ref));
  (void)(((mre).line = 0));
  (void)(((mre).col = 0));
  (void)(((mre).int_val = (res).mul_right_val));
  (void)(((mre).binop_left_ref = 0));
  (void)(((mre).binop_right_ref = 0));
  (void)(((mre).unary_operand_ref = 0));
  (void)(((mre).if_cond_ref = 0));
  (void)(((mre).if_then_ref = 0));
  (void)(((mre).if_else_ref = 0));
  (void)(((mre).block_ref = 0));
  (void)(((mre).match_matched_ref = 0));
  (void)(((mre).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(mre))));
  (void)(((mre).field_access_base_ref = 0));
  (void)(((mre).field_access_field_len = 0));
  (void)(((mre).field_access_is_enum_variant = 0));
  (void)(((mre).field_access_offset = 0));
  (void)(((mre).index_base_ref = 0));
  (void)(((mre).index_index_ref = 0));
  (void)(((mre).index_base_is_slice = 0));
  (void)(((mre).call_callee_ref = 0));
  (void)(((mre).call_num_args = 0));
  (void)(((mre).method_call_base_ref = 0));
  (void)(((mre).method_call_name_len = 0));
  (void)(((mre).method_call_num_args = 0));
  (void)(((mre).const_folded_val = 0));
  (void)(((mre).const_folded_valid = 0));
  (void)(((mre).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_r_ref, mre));
  int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
  (void)(((me).kind = ast_ExprKind_EXPR_MUL));
  (void)(((me).resolved_type_ref = type_ref));
  (void)(((me).line = 0));
  (void)(((me).col = 0));
  (void)(((me).int_val = 0));
  (void)(((me).binop_left_ref = mul_left_ref));
  (void)(((me).binop_right_ref = mul_r_ref));
  (void)(((me).unary_operand_ref = 0));
  (void)(((me).if_cond_ref = 0));
  (void)(((me).if_then_ref = 0));
  (void)(((me).if_else_ref = 0));
  (void)(((me).block_ref = 0));
  (void)(((me).match_matched_ref = 0));
  (void)(((me).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(me))));
  (void)(((me).field_access_base_ref = 0));
  (void)(((me).field_access_field_len = 0));
  (void)(((me).field_access_is_enum_variant = 0));
  (void)(((me).field_access_offset = 0));
  (void)(((me).index_base_ref = 0));
  (void)(((me).index_index_ref = 0));
  (void)(((me).index_base_is_slice = 0));
  (void)(((me).call_callee_ref = 0));
  (void)(((me).call_num_args = 0));
  (void)(((me).method_call_base_ref = 0));
 } else {   (void)((right_ref = ast_ast_arena_expr_alloc(arena)));
  (void)(({ int32_t __tmp = 0; if (right_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr re = ast_ast_arena_expr_get(arena, right_ref);
  (void)(((re).kind = ast_ExprKind_EXPR_LIT));
  (void)(((re).resolved_type_ref = type_ref));
  (void)(((re).line = 0));
  (void)(((re).col = 0));
  (void)(((re).int_val = (res).binop_right_val));
  (void)(((re).binop_left_ref = 0));
  (void)(((re).binop_right_ref = 0));
  (void)(((re).unary_operand_ref = 0));
  (void)(((re).if_cond_ref = 0));
  (void)(((re).if_then_ref = 0));
  (void)(((re).if_else_ref = 0));
  (void)(((re).block_ref = 0));
  (void)(((re).match_matched_ref = 0));
  (void)(((re).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(re))));
  (void)(((re).field_access_base_ref = 0));
  (void)(((re).field_access_field_len = 0));
  (void)(((re).field_access_is_enum_variant = 0));
  (void)(((re).field_access_offset = 0));
  (void)(((re).index_base_ref = 0));
  (void)(((re).index_index_ref = 0));
  (void)(((re).index_base_is_slice = 0));
  (void)(((re).call_callee_ref = 0));
  (void)(((re).call_num_args = 0));
  (void)(((re).method_call_base_ref = 0));
  (void)(((re).method_call_name_len = 0));
  (void)(((re).method_call_num_args = 0));
  (void)(((re).const_folded_val = 0));
  (void)(((re).const_folded_valid = 0));
  (void)(((re).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, right_ref, re));
 } ; __tmp; }));
  int32_t add_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (add_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr ae = ast_ast_arena_expr_get(arena, add_ref);
  (void)(((ae).kind = ast_ExprKind_EXPR_ADD));
  (void)(((ae).resolved_type_ref = type_ref));
  (void)(((ae).line = 0));
  (void)(((ae).col = 0));
  (void)(((ae).int_val = 0));
  (void)(((ae).binop_left_ref = left_ref));
  (void)(((ae).binop_right_ref = right_ref));
  (void)(((ae).unary_operand_ref = 0));
  (void)(((ae).if_cond_ref = 0));
  (void)(((ae).if_then_ref = 0));
  (void)(((ae).if_else_ref = 0));
  (void)(((ae).block_ref = 0));
  (void)(((ae).match_matched_ref = 0));
  (void)(((ae).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ae))));
  (void)(((ae).field_access_base_ref = 0));
  (void)(((ae).field_access_field_len = 0));
  (void)(((ae).field_access_is_enum_variant = 0));
  (void)(((ae).field_access_offset = 0));
  (void)(((ae).index_base_ref = 0));
  (void)(((ae).index_index_ref = 0));
  (void)(((ae).index_base_is_slice = 0));
  (void)(((ae).call_callee_ref = 0));
  (void)(((ae).call_num_args = 0));
  (void)(((ae).method_call_base_ref = 0));
  (void)(((ae).method_call_name_len = 0));
  (void)(((ae).method_call_num_args = 0));
  (void)(((ae).const_folded_val = 0));
  (void)(((ae).const_folded_valid = 0));
  (void)(((ae).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, add_ref, ae));
  (void)((final_expr_ref = add_ref));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((res).has_unary_neg) {   int32_t operand_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (operand_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr oe = ast_ast_arena_expr_get(arena, operand_ref);
  (void)(((oe).kind = ast_ExprKind_EXPR_LIT));
  (void)(((oe).resolved_type_ref = type_ref));
  (void)(((oe).line = 0));
  (void)(((oe).col = 0));
  (void)(((oe).int_val = (res).return_val));
  (void)(((oe).binop_left_ref = 0));
  (void)(((oe).binop_right_ref = 0));
  (void)(((oe).unary_operand_ref = 0));
  (void)(((oe).if_cond_ref = 0));
  (void)(((oe).if_then_ref = 0));
  (void)(((oe).if_else_ref = 0));
  (void)(((oe).block_ref = 0));
  (void)(((oe).match_matched_ref = 0));
  (void)(((oe).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(oe))));
  (void)(((oe).field_access_base_ref = 0));
  (void)(((oe).field_access_field_len = 0));
  (void)(((oe).field_access_is_enum_variant = 0));
  (void)(((oe).field_access_offset = 0));
  (void)(((oe).index_base_ref = 0));
  (void)(((oe).index_index_ref = 0));
  (void)(((oe).index_base_is_slice = 0));
  (void)(((oe).call_callee_ref = 0));
  (void)(((oe).call_num_args = 0));
  (void)(((oe).method_call_base_ref = 0));
  (void)(((oe).method_call_name_len = 0));
  (void)(((oe).method_call_num_args = 0));
  (void)(((oe).const_folded_val = 0));
  (void)(((oe).const_folded_valid = 0));
  (void)(((oe).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, operand_ref, oe));
  int32_t neg_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (neg_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr ne = ast_ast_arena_expr_get(arena, neg_ref);
  (void)(((ne).kind = ast_ExprKind_EXPR_NEG));
  (void)(((ne).resolved_type_ref = type_ref));
  (void)(((ne).line = 0));
  (void)(((ne).col = 0));
  (void)(((ne).int_val = 0));
  (void)(((ne).binop_left_ref = 0));
  (void)(((ne).binop_right_ref = 0));
  (void)(((ne).unary_operand_ref = operand_ref));
  (void)(((ne).if_cond_ref = 0));
  (void)(((ne).if_then_ref = 0));
  (void)(((ne).if_else_ref = 0));
  (void)(((ne).block_ref = 0));
  (void)(((ne).match_matched_ref = 0));
  (void)(((ne).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ne))));
  (void)(((ne).field_access_base_ref = 0));
  (void)(((ne).field_access_field_len = 0));
  (void)(((ne).field_access_is_enum_variant = 0));
  (void)(((ne).field_access_offset = 0));
  (void)(((ne).index_base_ref = 0));
  (void)(((ne).index_index_ref = 0));
  (void)(((ne).index_base_is_slice = 0));
  (void)(((ne).call_callee_ref = 0));
  (void)(((ne).call_num_args = 0));
  (void)(((ne).method_call_base_ref = 0));
  (void)(((ne).method_call_name_len = 0));
  (void)(((ne).method_call_num_args = 0));
  (void)(((ne).const_folded_val = 0));
  (void)(((ne).const_folded_valid = 0));
  (void)(((ne).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, neg_ref, ne));
  (void)((final_expr_ref = neg_ref));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((res).has_call_expr && (res).call_callee_len > 0 && (res).call_callee_len <= 63) {   int32_t callee_ref = ast_ast_arena_expr_alloc(arena);
  __tmp = ({ int32_t __tmp = 0; if (callee_ref != 0) {   struct ast_Expr ve = ast_ast_arena_expr_get(arena, callee_ref);
  (void)(((ve).kind = ast_ExprKind_EXPR_VAR));
  (void)(((ve).resolved_type_ref = 0));
  (void)(((ve).line = 0));
  (void)(((ve).col = 0));
  (void)(((ve).var_name_len = (res).call_callee_len));
  int32_t ck = 0;
  while (ck < (res).call_callee_len && ck < 64) {
    (void)(((ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), 0) : (((ve).var_name)[ck] = (ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), ((res).call_callee_name)[0]) : ((res).call_callee_name)[ck]), 0))));
    (void)((ck = ck + 1));
  }
  uint8_t z = 0;
  while (ck < 64) {
    (void)(((ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), 0) : (((ve).var_name)[ck] = z, 0))));
    (void)((ck = ck + 1));
  }
  (void)(((ve).binop_left_ref = 0));
  (void)(((ve).binop_right_ref = 0));
  (void)(((ve).unary_operand_ref = 0));
  (void)(((ve).if_cond_ref = 0));
  (void)(((ve).if_then_ref = 0));
  (void)(((ve).if_else_ref = 0));
  (void)(((ve).block_ref = 0));
  (void)(((ve).match_matched_ref = 0));
  (void)(((ve).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ve))));
  (void)(((ve).field_access_base_ref = 0));
  (void)(((ve).field_access_field_len = 0));
  (void)(((ve).field_access_is_enum_variant = 0));
  (void)(((ve).field_access_offset = 0));
  (void)(((ve).index_base_ref = 0));
  (void)(((ve).index_index_ref = 0));
  (void)(((ve).index_base_is_slice = 0));
  (void)(((ve).call_callee_ref = 0));
  (void)(((ve).call_num_args = 0));
  (void)(((ve).method_call_base_ref = 0));
  (void)(((ve).method_call_name_len = 0));
  (void)(((ve).method_call_num_args = 0));
  (void)(((ve).const_folded_val = 0));
  (void)(((ve).const_folded_valid = 0));
  (void)(((ve).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, callee_ref, ve));
  int32_t call_ref = ast_ast_arena_expr_alloc(arena);
  __tmp = ({ int32_t __tmp = 0; if (call_ref != 0) {   struct ast_Expr ce = ast_ast_arena_expr_get(arena, call_ref);
  (void)(((ce).kind = ast_ExprKind_EXPR_CALL));
  (void)(((ce).resolved_type_ref = type_ref));
  (void)(((ce).line = 0));
  (void)(((ce).col = 0));
  (void)(((ce).call_callee_ref = callee_ref));
  (void)(((ce).call_num_args = 0));
  (void)(((ce).binop_left_ref = 0));
  (void)(((ce).binop_right_ref = 0));
  (void)(((ce).unary_operand_ref = 0));
  (void)(((ce).if_cond_ref = 0));
  (void)(((ce).if_then_ref = 0));
  (void)(((ce).if_else_ref = 0));
  (void)(((ce).block_ref = 0));
  (void)(((ce).match_matched_ref = 0));
  (void)(((ce).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(ce))));
  (void)(((ce).field_access_base_ref = 0));
  (void)(((ce).field_access_field_len = 0));
  (void)(((ce).field_access_is_enum_variant = 0));
  (void)(((ce).field_access_offset = 0));
  (void)(((ce).index_base_ref = 0));
  (void)(((ce).index_index_ref = 0));
  (void)(((ce).index_base_is_slice = 0));
  (void)(((ce).method_call_base_ref = 0));
  (void)(((ce).method_call_name_len = 0));
  (void)(((ce).method_call_num_args = 0));
  (void)(((ce).const_folded_val = 0));
  (void)(((ce).const_folded_valid = 0));
  (void)(((ce).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, call_ref, ce));
  (void)((final_expr_ref = call_ref));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    int32_t block_ref = ast_ast_arena_block_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (block_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
    (void)(((b).num_consts = (res).num_consts));
    (void)(((b).num_lets = (res).num_lets));
    (void)(((b).num_early_lets = 0));
    (void)(((b).num_loops = 0));
    (void)(((b).num_for_loops = 0));
    (void)(((b).num_defers = 0));
    (void)(((b).num_labeled_stmts = 0));
    (void)(((b).num_expr_stmts = 0));
    (void)(((b).final_expr_ref = final_expr_ref));
    (void)(((b).num_stmt_order = 0));
    int32_t const_i = 0;
    while (const_i < (res).num_consts && const_i < 24) {
      int32_t cinit_ref = ast_ast_arena_expr_alloc(arena);
      (void)(({ int32_t __tmp = 0; if (cinit_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
      struct ast_Expr ce = ast_ast_arena_expr_get(arena, cinit_ref);
      (void)(((ce).kind = ast_ExprKind_EXPR_LIT));
      (void)(((ce).resolved_type_ref = type_ref));
      (void)(((ce).line = 0));
      (void)(((ce).col = 0));
      (void)(((ce).int_val = (const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), ((res).const_init_vals)[0]) : ((res).const_init_vals)[const_i])));
      (void)(((ce).binop_left_ref = 0));
      (void)(((ce).binop_right_ref = 0));
      (void)(((ce).unary_operand_ref = 0));
      (void)(((ce).if_cond_ref = 0));
      (void)(((ce).if_then_ref = 0));
      (void)(((ce).if_else_ref = 0));
      (void)(((ce).block_ref = 0));
      (void)(((ce).match_matched_ref = 0));
      (void)(((ce).match_num_arms = 0));
      (void)(ast_expr_init_match_enum((&(ce))));
      (void)(((ce).field_access_base_ref = 0));
      (void)(((ce).field_access_field_len = 0));
      (void)(((ce).field_access_is_enum_variant = 0));
      (void)(((ce).field_access_offset = 0));
      (void)(((ce).index_base_ref = 0));
      (void)(((ce).index_index_ref = 0));
      (void)(((ce).index_base_is_slice = 0));
      (void)(((ce).call_callee_ref = 0));
      (void)(((ce).call_num_args = 0));
      (void)(((ce).method_call_base_ref = 0));
      (void)(((ce).method_call_name_len = 0));
      (void)(((ce).method_call_num_args = 0));
      (void)(((ce).const_folded_val = 0));
      (void)(((ce).const_folded_valid = 0));
      (void)(((ce).index_proven_in_bounds = 0));
      (void)(ast_ast_arena_expr_set(arena, cinit_ref, ce));
      struct ast_ConstDecl cd = (const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), ((b).const_decls)[0]) : ((b).const_decls)[const_i]);
      int32_t ck = 0;
      while (ck < (const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), ((res).const_name_lens)[0]) : ((res).const_name_lens)[const_i]) && ck < 64) {
      uint8_t const_row[64] ;
      memcpy(const_row, ((const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), ((res).const_names)[0]) : ((res).const_names)[const_i])), sizeof(const_row));
      (void)(((ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), 0) : (((cd).name)[ck] = (ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), (const_row)[0]) : (const_row)[ck]), 0))));
      (void)((ck = ck + 1));
      }
      uint8_t zero_const = 0;
      while (ck < 64) {
      (void)(((ck < 0 || (ck) >= 64 ? (shulang_panic_(1, 0), 0) : (((cd).name)[ck] = zero_const, 0))));
      (void)((ck = ck + 1));
      }
      (void)(((cd).name_len = (const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), ((res).const_name_lens)[0]) : ((res).const_name_lens)[const_i])));
      (void)(((cd).type_ref = type_ref));
      (void)(((cd).init_ref = cinit_ref));
      (void)(((const_i < 0 || (const_i) >= 24 ? (shulang_panic_(1, 0), 0) : (((b).const_decls)[const_i] = cd, 0))));
      (void)((const_i = const_i + 1));
    }
    int32_t let_i = 0;
    while (let_i < (res).num_lets && let_i < 24) {
      int32_t init_ref = ast_ast_arena_expr_alloc(arena);
      (void)(({ int32_t __tmp = 0; if (init_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
      struct ast_Expr le = ast_ast_arena_expr_get(arena, init_ref);
      (void)(((le).kind = ast_ExprKind_EXPR_LIT));
      (void)(((le).resolved_type_ref = type_ref));
      (void)(((le).line = 0));
      (void)(((le).col = 0));
      (void)(((le).int_val = (let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), ((res).let_init_vals)[0]) : ((res).let_init_vals)[let_i])));
      (void)(((le).binop_left_ref = 0));
      (void)(((le).binop_right_ref = 0));
      (void)(((le).unary_operand_ref = 0));
      (void)(((le).if_cond_ref = 0));
      (void)(((le).if_then_ref = 0));
      (void)(((le).if_else_ref = 0));
      (void)(((le).block_ref = 0));
      (void)(((le).match_matched_ref = 0));
      (void)(((le).match_num_arms = 0));
      (void)(ast_expr_init_match_enum((&(le))));
      (void)(((le).field_access_base_ref = 0));
      (void)(((le).field_access_field_len = 0));
      (void)(((le).field_access_is_enum_variant = 0));
      (void)(((le).field_access_offset = 0));
      (void)(((le).index_base_ref = 0));
      (void)(((le).index_index_ref = 0));
      (void)(((le).index_base_is_slice = 0));
      (void)(((le).call_callee_ref = 0));
      (void)(((le).call_num_args = 0));
      (void)(((le).method_call_base_ref = 0));
      (void)(((le).method_call_name_len = 0));
      (void)(((le).method_call_num_args = 0));
      (void)(((le).const_folded_val = 0));
      (void)(((le).const_folded_valid = 0));
      (void)(((le).index_proven_in_bounds = 0));
      (void)(ast_ast_arena_expr_set(arena, init_ref, le));
      struct ast_LetDecl ld = (let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), ((b).let_decls)[0]) : ((b).let_decls)[let_i]);
      int32_t lk = 0;
      while (lk < (let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), ((res).let_name_lens)[0]) : ((res).let_name_lens)[let_i]) && lk < 64) {
      uint8_t let_row[64] ;
      memcpy(let_row, ((let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), ((res).let_names)[0]) : ((res).let_names)[let_i])), sizeof(let_row));
      (void)(((lk < 0 || (lk) >= 64 ? (shulang_panic_(1, 0), 0) : (((ld).name)[lk] = (lk < 0 || (lk) >= 64 ? (shulang_panic_(1, 0), (let_row)[0]) : (let_row)[lk]), 0))));
      (void)((lk = lk + 1));
      }
      uint8_t zero_let = 0;
      while (lk < 64) {
      (void)(((lk < 0 || (lk) >= 64 ? (shulang_panic_(1, 0), 0) : (((ld).name)[lk] = zero_let, 0))));
      (void)((lk = lk + 1));
      }
      (void)(((ld).name_len = (let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), ((res).let_name_lens)[0]) : ((res).let_name_lens)[let_i])));
      (void)(((ld).type_ref = type_ref));
      (void)(((ld).init_ref = init_ref));
      (void)(((let_i < 0 || (let_i) >= 24 ? (shulang_panic_(1, 0), 0) : (((b).let_decls)[let_i] = ld, 0))));
      (void)((let_i = let_i + 1));
    }
    int32_t so = 0;
    int32_t ci = 0;
    while (ci < (b).num_consts && so < 96) {
      (void)(((so < 0 || (so) >= 96 ? (shulang_panic_(1, 0), 0) : (((b).stmt_order)[so].kind = 0, 0))));
      (void)(((so < 0 || (so) >= 96 ? (shulang_panic_(1, 0), 0) : (((b).stmt_order)[so].idx = ci, 0))));
      (void)((so = so + 1));
      (void)((ci = ci + 1));
    }
    int32_t li = 0;
    while (li < (b).num_lets && so < 96) {
      (void)(((so < 0 || (so) >= 96 ? (shulang_panic_(1, 0), 0) : (((b).stmt_order)[so].kind = 1, 0))));
      (void)(((so < 0 || (so) >= 96 ? (shulang_panic_(1, 0), 0) : (((b).stmt_order)[so].idx = li, 0))));
      (void)((so = so + 1));
      (void)((li = li + 1));
    }
    (void)(((b).num_stmt_order = so));
    (void)(ast_ast_arena_block_set(arena, block_ref, b));
    struct ast_Func f = ((module)->num_funcs < 0 || ((module)->num_funcs) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[(module)->num_funcs]);
    int32_t k = 0;
    while (k < (res).name_len && k < 64) {
      (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((f).name)[k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[k]), 0))));
      (void)((k = k + 1));
    }
    uint8_t zero_u8 = 0;
    while (k < 64) {
      (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((f).name)[k] = zero_u8, 0))));
      (void)((k = k + 1));
    }
    (void)(((f).name_len = (res).name_len));
    (void)(((f).num_params = (res).num_params));
    int32_t p = 0;
    while (p < (res).num_params && p < 16) {
      struct ast_Param param = (p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), ((f).params)[0]) : ((f).params)[p]);
      int32_t pk = 0;
      (void)(((param).name_len = (p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), ((res).param_name_lens)[0]) : ((res).param_name_lens)[p])));
      (void)(((param).type_ref = type_ref));
      (void)(((p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), 0) : (((f).params)[p] = param, 0))));
      (void)((p = p + 1));
      while (pk < (p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), ((res).param_name_lens)[0]) : ((res).param_name_lens)[p]) && pk < 32) {
      uint8_t row[32] ;
      memcpy(row, ((p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), ((res).param_names)[0]) : ((res).param_names)[p])), sizeof(row));
      (void)(((pk < 0 || (pk) >= 32 ? (shulang_panic_(1, 0), 0) : (((param).name)[pk] = (pk < 0 || (pk) >= 32 ? (shulang_panic_(1, 0), (row)[0]) : (row)[pk]), 0))));
      (void)((pk = pk + 1));
      }
      while (pk < 32) {
      (void)(((pk < 0 || (pk) >= 32 ? (shulang_panic_(1, 0), 0) : (((param).name)[pk] = zero_u8, 0))));
      (void)((pk = pk + 1));
      }
    }
    (void)(((f).return_type_ref = type_ref));
    (void)(((f).body_ref = block_ref));
    (void)(((f).is_extern = 0));
    (void)((((module)->num_funcs < 0 || ((module)->num_funcs) >= 256 ? (shulang_panic_(1, 0), 0) : (((module)->funcs)[(module)->num_funcs] = f, 0))));
    (void)(({ int32_t __tmp = 0; if ((is_main_storage)[0] != 0) {   (void)((main_idx = (module)->num_funcs));
 } else (__tmp = 0) ; __tmp; }));
    (void)(((module)->num_funcs = (module)->num_funcs + 1));
    (void)((lex = (res).next_lex));
    (void)((lex = (res).next_lex));
  }
  (void)(({ int32_t __tmp = 0; if ((module)->num_funcs == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_idx < 0) {   (void)((out_idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_idx_storage)[0] = out_idx));
  return (struct parser_ParseIntoResult){ .ok = 0, .main_idx = (out_idx_storage)[0] };
}
struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena * restrict arena, struct ast_Module * restrict module, uint8_t * restrict data, int32_t len) {
  struct lexer_Lexer lex = lexer_lexer_init();
  int32_t main_idx = (-1);
  struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
  (void)(parser_collect_imports_buf(lex, data, len, module, (&(import_res))));
  (void)((lex = (import_res).lex));
  int32_t out_idx = main_idx;
  int32_t out_idx_storage[1] = { 0 };
  while (1) {
    struct lexer_LexerResult r = lexer_lexer_next_buf(lex, data, len);
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind == token_TokenKind_TOKEN_STRUCT) {   (void)((lex = parser_skip_one_struct_buf(lex, data, len)));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (((r).tok).kind != token_TokenKind_TOKEN_FUNCTION) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct parser_OneFuncResult res = parser_parse_one_function_buf(lex, data, len);
    (void)(({ int32_t __tmp = 0; if ((!(res).ok)) {   break;
 } else (__tmp = 0) ; __tmp; }));
    int32_t is_main_storage[1] = { 0 };
    (void)(({ int32_t __tmp = 0; if ((res).name_len == 4 && ((res).name)[0] == 109 && (1 < 0 || (1) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[1]) == 97 && (2 < 0 || (2) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[2]) == 105 && (3 < 0 || (3) >= 64 ? (shulang_panic_(1, 0), ((res).name)[0]) : ((res).name)[3]) == 110) {   (void)(((is_main_storage)[0] = 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((module)->num_funcs >= 256) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    int32_t type_ref = ast_ast_arena_type_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (type_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Type t = ast_ast_arena_type_get(arena, type_ref);
    (void)(((t).kind = ast_TypeKind_TYPE_I32));
    (void)(((t).name_len = 0));
    (void)(((t).elem_type_ref = 0));
    (void)(((t).array_size = 0));
    (void)(ast_ast_arena_type_set(arena, type_ref, t));
    int32_t expr_ref = ast_ast_arena_expr_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (expr_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
    (void)(((e).kind = ast_ExprKind_EXPR_LIT));
    (void)(((e).resolved_type_ref = type_ref));
    (void)(((e).line = 0));
    (void)(((e).col = 0));
    (void)(((e).int_val = (res).return_val));
    (void)(((e).binop_left_ref = 0));
    (void)(((e).binop_right_ref = 0));
    (void)(((e).unary_operand_ref = 0));
    (void)(((e).if_cond_ref = 0));
    (void)(((e).if_then_ref = 0));
    (void)(((e).if_else_ref = 0));
    (void)(((e).block_ref = 0));
    (void)(((e).match_matched_ref = 0));
    (void)(((e).match_num_arms = 0));
    (void)(ast_expr_init_match_enum((&(e))));
    (void)(((e).field_access_base_ref = 0));
    (void)(((e).field_access_field_len = 0));
    (void)(((e).field_access_is_enum_variant = 0));
    (void)(((e).field_access_offset = 0));
    (void)(((e).index_base_ref = 0));
    (void)(((e).index_index_ref = 0));
    (void)(((e).index_base_is_slice = 0));
    (void)(((e).call_callee_ref = 0));
    (void)(((e).call_num_args = 0));
    (void)(((e).method_call_base_ref = 0));
    (void)(((e).method_call_name_len = 0));
    (void)(((e).method_call_num_args = 0));
    (void)(((e).const_folded_val = 0));
    (void)(((e).const_folded_valid = 0));
    (void)(((e).index_proven_in_bounds = 0));
    (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
    int32_t final_expr_ref = expr_ref;
    (void)(({ int32_t __tmp = 0; if ((res).has_mul && (!(res).has_binop)) {   int32_t mul_right_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_right_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_right_ref);
  (void)(((mre).kind = ast_ExprKind_EXPR_LIT));
  (void)(((mre).resolved_type_ref = type_ref));
  (void)(((mre).line = 0));
  (void)(((mre).col = 0));
  (void)(((mre).int_val = (res).mul_right_val));
  (void)(((mre).binop_left_ref = 0));
  (void)(((mre).binop_right_ref = 0));
  (void)(((mre).unary_operand_ref = 0));
  (void)(((mre).if_cond_ref = 0));
  (void)(((mre).if_then_ref = 0));
  (void)(((mre).if_else_ref = 0));
  (void)(((mre).block_ref = 0));
  (void)(((mre).match_matched_ref = 0));
  (void)(((mre).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(mre))));
  (void)(((mre).field_access_base_ref = 0));
  (void)(((mre).field_access_field_len = 0));
  (void)(((mre).field_access_is_enum_variant = 0));
  (void)(((mre).field_access_offset = 0));
  (void)(((mre).index_base_ref = 0));
  (void)(((mre).index_index_ref = 0));
  (void)(((mre).index_base_is_slice = 0));
  (void)(((mre).call_callee_ref = 0));
  (void)(((mre).call_num_args = 0));
  (void)(((mre).method_call_base_ref = 0));
  (void)(((mre).method_call_name_len = 0));
  (void)(((mre).method_call_num_args = 0));
  (void)(((mre).const_folded_val = 0));
  (void)(((mre).const_folded_valid = 0));
  (void)(((mre).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_right_ref, mre));
  int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (mul_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
  (void)(((me).kind = ast_ExprKind_EXPR_BINOP));
  (void)(((me).resolved_type_ref = type_ref));
  (void)(((me).line = 0));
  (void)(((me).col = 0));
  (void)(((me).int_val = 0));
  (void)(((me).binop_left_ref = expr_ref));
  (void)(((me).binop_right_ref = mul_right_ref));
  (void)(((me).unary_operand_ref = 0));
  (void)(((me).if_cond_ref = 0));
  (void)(((me).if_then_ref = 0));
  (void)(((me).if_else_ref = 0));
  (void)(((me).block_ref = 0));
  (void)(((me).match_matched_ref = 0));
  (void)(((me).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(me))));
  (void)(((me).field_access_base_ref = 0));
  (void)(((me).field_access_field_len = 0));
  (void)(((me).field_access_is_enum_variant = 0));
  (void)(((me).field_access_offset = 0));
  (void)(((me).index_base_ref = 0));
  (void)(((me).index_index_ref = 0));
  (void)(((me).index_base_is_slice = 0));
  (void)(((me).call_callee_ref = 0));
  (void)(((me).call_num_args = 0));
  (void)(((me).method_call_base_ref = 0));
  (void)(((me).method_call_name_len = 0));
  (void)(((me).method_call_num_args = 0));
  (void)(((me).const_folded_val = 0));
  (void)(((me).const_folded_valid = 0));
  (void)(((me).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, mul_ref, me));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
 } else (__tmp = ({ int32_t __tmp = 0; if ((res).has_binop) {   int32_t right_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (right_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr re = ast_ast_arena_expr_get(arena, right_ref);
  (void)(((re).kind = ast_ExprKind_EXPR_LIT));
  (void)(((re).resolved_type_ref = type_ref));
  (void)(((re).line = 0));
  (void)(((re).col = 0));
  (void)(((re).int_val = (res).binop_right_val));
  (void)(((re).binop_left_ref = 0));
  (void)(((re).binop_right_ref = 0));
  (void)(((re).unary_operand_ref = 0));
  (void)(((re).if_cond_ref = 0));
  (void)(((re).if_then_ref = 0));
  (void)(((re).if_else_ref = 0));
  (void)(((re).block_ref = 0));
  (void)(((re).match_matched_ref = 0));
  (void)(((re).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(re))));
  (void)(((re).field_access_base_ref = 0));
  (void)(((re).field_access_field_len = 0));
  (void)(((re).field_access_is_enum_variant = 0));
  (void)(((re).field_access_offset = 0));
  (void)(((re).index_base_ref = 0));
  (void)(((re).index_index_ref = 0));
  (void)(((re).index_base_is_slice = 0));
  (void)(((re).call_callee_ref = 0));
  (void)(((re).call_num_args = 0));
  (void)(((re).method_call_base_ref = 0));
  (void)(((re).method_call_name_len = 0));
  (void)(((re).method_call_num_args = 0));
  (void)(((re).const_folded_val = 0));
  (void)(((re).const_folded_valid = 0));
  (void)(((re).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, right_ref, re));
  int32_t binop_ref = ast_ast_arena_expr_alloc(arena);
  (void)(({ int32_t __tmp = 0; if (binop_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr be = ast_ast_arena_expr_get(arena, binop_ref);
  (void)(((be).kind = ast_ExprKind_EXPR_BINOP));
  (void)(((be).resolved_type_ref = type_ref));
  (void)(((be).line = 0));
  (void)(((be).col = 0));
  (void)(((be).int_val = 0));
  (void)(((be).binop_left_ref = expr_ref));
  (void)(((be).binop_right_ref = right_ref));
  (void)(((be).unary_operand_ref = 0));
  (void)(((be).if_cond_ref = 0));
  (void)(((be).if_then_ref = 0));
  (void)(((be).if_else_ref = 0));
  (void)(((be).block_ref = 0));
  (void)(((be).match_matched_ref = 0));
  (void)(((be).match_num_arms = 0));
  (void)(ast_expr_init_match_enum((&(be))));
  (void)(((be).field_access_base_ref = 0));
  (void)(((be).field_access_field_len = 0));
  (void)(((be).field_access_is_enum_variant = 0));
  (void)(((be).field_access_offset = 0));
  (void)(((be).index_base_ref = 0));
  (void)(((be).index_index_ref = 0));
  (void)(((be).index_base_is_slice = 0));
  (void)(((be).call_callee_ref = 0));
  (void)(((be).call_num_args = 0));
  (void)(((be).method_call_base_ref = 0));
  (void)(((be).method_call_name_len = 0));
  (void)(((be).method_call_num_args = 0));
  (void)(((be).const_folded_val = 0));
  (void)(((be).const_folded_valid = 0));
  (void)(((be).index_proven_in_bounds = 0));
  (void)(ast_ast_arena_expr_set(arena, binop_ref, be));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((is_main_storage)[0] != 0) {   (void)((main_idx = (module)->num_funcs));
 } else (__tmp = 0) ; __tmp; }));
    int32_t func_ref = ast_ast_arena_func_alloc(arena);
    (void)(({ int32_t __tmp = 0; if (func_ref == 0) {   return (struct parser_ParseIntoResult){ .ok = (-1), .main_idx = (-1) };
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Func f = ast_ast_arena_func_get(arena, func_ref);
    (void)(((f).name_len = (res).name_len));
    (void)(((f).return_type_ref = type_ref));
    (void)(((f).body_expr_ref = final_expr_ref));
    (void)(((f).num_params = (res).num_params));
    (void)(ast_ast_arena_func_set(arena, func_ref, f));
    (void)((((module)->num_funcs < 0 || ((module)->num_funcs) >= 256 ? (shulang_panic_(1, 0), 0) : (((module)->func_refs)[(module)->num_funcs] = func_ref, 0))));
    (void)(((module)->num_funcs = (module)->num_funcs + 1));
    (void)((lex = (res).next_lex));
    (void)((lex = (res).next_lex));
  }
  (void)(parser_collect_imports_buf(lex, data, len, module, (&(import_res))));
  (void)((lex = (import_res).lex));
  (void)(((out_idx_storage)[0] = out_idx));
  return (struct parser_ParseIntoResult){ .ok = 0, .main_idx = (out_idx_storage)[0] };
}
void parser_parse_into_set_main_index(struct ast_Module * restrict module, int32_t main_idx) {
  (void)(((module)->main_func_index = main_idx));
}
int32_t parser_diag_token_after_collect_imports(struct shulang_slice_uint8_t * source, struct ast_Module * restrict module) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
  struct lexer_LexerResult r = lexer_lexer_next(lex, source);
  (void)(parser_collect_imports(lex, source, module, (&(import_res))));
  (void)((lex = (import_res).lex));
  return ((r).tok).kind;
}
int32_t parser_diag_parse_one_after_collect_imports(struct shulang_slice_uint8_t * source, struct ast_Module * restrict module) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
  struct parser_OneFuncResult res = parser_parse_one_function(lex, source);
  (void)(parser_collect_imports(lex, source, module, (&(import_res))));
  (void)((lex = (import_res).lex));
  return ((res).ok ? 1 : 0);
}
int32_t parser_get_module_num_imports(struct ast_Module * restrict module) {
  return (module)->num_imports;
}
void parser_get_module_import_path(struct ast_Module * restrict module, int32_t i, uint8_t out[64]) {
  int32_t len = (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((module)->import_path_lens)[0]) : ((module)->import_path_lens)[i]);
  int32_t base = i * 64;
  int32_t j = 0;
  while (j <= len) {
    (void)(({ int32_t __tmp = 0; if (j < len) {   (void)(((j < 0 || (j) >= 64 ? (shulang_panic_(1, 0), 0) : ((out)[j] = (base + j < 0 || (base + j) >= 2048 ? (shulang_panic_(1, 0), ((module)->import_path_data)[0]) : ((module)->import_path_data)[base + j]), 0))));
 } else {   uint8_t z = 0;
  (void)(((j < 0 || (j) >= 64 ? (shulang_panic_(1, 0), 0) : ((out)[j] = z, 0))));
 } ; __tmp; }));
    (void)((j = j + 1));
  }
  (void)(({ int32_t __tmp = 0; if (i < 0 || i >= (module)->num_imports) {   uint8_t z = 0;
  (void)(((out)[0] = z));
  return;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (len > 63) {   uint8_t z = 0;
  (void)(((out)[0] = z));
  return;
 } else (__tmp = 0) ; __tmp; }));
}
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena *, int32_t);
extern int32_t ast_ast_arena_type_alloc(struct ast_ASTArena *);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena *, int32_t);
extern void ast_ast_arena_type_set(struct ast_ASTArena *, int32_t, struct ast_Type);
extern int ast_ref_is_null(int32_t);
extern void ast_ast_arena_expr_set(struct ast_ASTArena *, int32_t, struct ast_Expr);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena *, int32_t);
extern int32_t typeck_float64_bits_lo(double d);
extern int32_t typeck_float64_bits_hi(double d);
int typeck_name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len);
int32_t typeck_get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
int32_t typeck_ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_Expr e);
int typeck_expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index);
int32_t typeck_ensure_i32_type_ref(struct ast_ASTArena * arena);
int32_t typeck_get_dep_return_type_in_caller_arena(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
int32_t typeck_ensure_i64_type_ref(struct ast_ASTArena * caller_arena);
int32_t typeck_dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena);
int32_t typeck_find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx);
int32_t typeck_resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx);
int32_t typeck_expr_type_ref_impl(struct ast_ASTArena * arena, int32_t expr_ref);
int32_t typeck_expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref);
int typeck_type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref);
int typeck_type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref);
int typeck_type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b);
int typeck_type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b);
int32_t typeck_check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t typeck_check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t typeck_check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t typeck_check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t typeck_typeck_su_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int32_t typeck_typeck_su_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
int typeck_name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len) {
  int32_t i = 0;
  while (i < a_len) {
    (void)(({ int __tmp = 0; if ((a)[i] != (b)[i]) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int __tmp = 0; if (a_len != b_len || a_len <= 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return 1;
}
int32_t typeck_get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  int32_t k = 0;
  while (k < (module)->num_struct_layouts && k < 32) {
    struct ast_StructLayout sl = (k < 0 || (k) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[k]);
    (void)(({ int32_t __tmp = 0; if (typeck_name_equal((sl).name, (sl).name_len, type_name, type_name_len)) {   int32_t j = 0;
  while (j < (sl).num_fields && j < 8) {
    (void)(({ int32_t __tmp = 0; if (typeck_name_equal((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((sl).field_names)[0]) : ((sl).field_names)[j]), (j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((sl).field_lens)[0]) : ((sl).field_lens)[j]), field_name, field_name_len)) {   return (j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((sl).field_offsets)[0]) : ((sl).field_offsets)[j]);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  return (-1);
}
int32_t typeck_ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_Expr e) {
  int32_t name_len = (e).struct_lit_struct_name_len;
  int32_t k = 0;
  int32_t idx = (module)->num_struct_layouts;
  int32_t i = 0;
  int32_t off = 0;
  int32_t j = 0;
  while (k < (module)->num_struct_layouts && k < 32) {
    struct ast_StructLayout sl = (k < 0 || (k) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[k]);
    (void)(({ int32_t __tmp = 0; if (typeck_name_equal((sl).name, (sl).name_len, (e).struct_lit_struct_name, name_len)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  while (i < 64) {
    (void)(((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), 0) : ((((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[idx])).name)[i] = (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), ((e).struct_lit_struct_name)[0]) : ((e).struct_lit_struct_name)[i]), 0))));
    (void)((i = i + 1));
  }
  while (j < (e).struct_lit_num_fields && j < 8) {
    int32_t fi = 0;
    (void)(((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), 0) : ((((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[idx])).field_lens)[j] = (j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_lens)[0]) : ((e).struct_lit_field_lens)[j]), 0))));
    (void)(((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), 0) : ((((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[idx])).field_offsets)[j] = off, 0))));
    (void)((off = off + 8));
    (void)((j = j + 1));
    while (fi < 64) {
      (void)(((fi < 0 || (fi) >= 64 ? (shulang_panic_(1, 0), 0) : (((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), (((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[idx])).field_names)[0]) : (((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((module)->struct_layouts)[0]) : ((module)->struct_layouts)[idx])).field_names)[j]))[fi] = (fi < 0 || (fi) >= 64 ? (shulang_panic_(1, 0), ((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_names)[0]) : ((e).struct_lit_field_names)[j]))[0]) : ((j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_names)[0]) : ((e).struct_lit_field_names)[j]))[fi]), 0))));
      (void)((fi = fi + 1));
    }
  }
  (void)(({ int32_t __tmp = 0; if ((e).struct_lit_num_fields <= 0 || (e).struct_lit_num_fields > 8) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (name_len <= 0 || name_len > 63) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((module)->num_struct_layouts >= 32) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((module)->num_struct_layouts = (module)->num_struct_layouts + 1));
  (void)(((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), 0) : (((module)->struct_layouts)[idx].name_len = name_len, 0))));
  (void)(((idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), 0) : (((module)->struct_layouts)[idx].num_fields = (e).struct_lit_num_fields, 0))));
  return 0;
}
int typeck_expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index) {
  struct ast_Expr callee = ast_ast_arena_expr_get(arena, callee_expr_ref);
  int32_t b_len = (callee).var_name_len;
  struct ast_Func ff = (func_index < 0 || (func_index) >= 256 ? (shulang_panic_(1, 0), ((mod)->funcs)[0]) : ((mod)->funcs)[func_index]);
  int32_t a_len = (ff).name_len;
  int32_t i = 0;
  while (i < a_len) {
    (void)(({ int __tmp = 0; if ((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), ((ff).name)[0]) : ((ff).name)[i]) != (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), ((callee).var_name)[0]) : ((callee).var_name)[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int __tmp = 0; if (callee_expr_ref <= 0 || callee_expr_ref > (arena)->num_exprs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if ((callee).kind != ast_ExprKind_EXPR_VAR) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if (func_index < 0 || func_index >= (mod)->num_funcs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if (a_len != b_len || a_len <= 0 || a_len > 63) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return 1;
}
int32_t typeck_ensure_i32_type_ref(struct ast_ASTArena * arena) {
  int32_t k = 1;
  int32_t new_ref = ast_ast_arena_type_alloc(arena);
  struct ast_Type ti = ast_ast_arena_type_get(arena, new_ref);
  while (k <= (arena)->num_types) {
    struct ast_Type tk = ast_ast_arena_type_get(arena, k);
    (void)(({ int32_t __tmp = 0; if ((tk).kind == ast_TypeKind_TYPE_I32) {   return k;
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (new_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ti).kind = ast_TypeKind_TYPE_I32));
  (void)(((ti).name_len = 0));
  (void)(((ti).elem_type_ref = 0));
  (void)(((ti).array_size = 0));
  (void)(ast_ast_arena_type_set(arena, new_ref, ti));
  return new_ref;
}
int32_t typeck_get_dep_return_type_in_caller_arena(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx) {
  struct ast_ASTArena * dep_arena = (from_dep_index < 0 || (from_dep_index) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_arenas)[0]) : ((ctx)->dep_arenas)[from_dep_index]);
  (void)(({ int32_t __tmp = 0; if (from_dep_index < 0 || from_dep_index >= 32) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_dep_return_type_to_caller_arena(dep_arena, dep_return_type_ref, caller_arena);
}
int32_t typeck_ensure_i64_type_ref(struct ast_ASTArena * caller_arena) {
  int32_t k = 1;
  int32_t new_ref = ast_ast_arena_type_alloc(caller_arena);
  struct ast_Type ti = ast_ast_arena_type_get(caller_arena, new_ref);
  while (k <= (caller_arena)->num_types) {
    struct ast_Type tk = ast_ast_arena_type_get(caller_arena, k);
    (void)(({ int32_t __tmp = 0; if ((tk).kind == ast_TypeKind_TYPE_I64) {   return k;
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (new_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ti).kind = ast_TypeKind_TYPE_I64));
  (void)(((ti).name_len = 0));
  (void)(((ti).elem_type_ref = 0));
  (void)(((ti).array_size = 0));
  (void)(ast_ast_arena_type_set(caller_arena, new_ref, ti));
  return new_ref;
}
int32_t typeck_dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena) {
  struct ast_Type tt = ast_ast_arena_type_get(dep_arena, dep_return_type_ref);
  (void)(({ int32_t __tmp = 0; if ((tt).kind == ast_TypeKind_TYPE_I32) {   return typeck_ensure_i32_type_ref(caller_arena);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((tt).kind == ast_TypeKind_TYPE_I64) {   return typeck_ensure_i64_type_ref(caller_arena);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t typeck_find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx) {
  int32_t j = 0;
  while (j < (mod)->num_funcs) {
    (void)(({ int32_t __tmp = 0; if (j >= 256) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Func f = (j < 0 || (j) >= 256 ? (shulang_panic_(1, 0), ((mod)->funcs)[0]) : ((mod)->funcs)[j]);
    (void)(({ int32_t __tmp = 0; if (typeck_expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {   (void)(({ int32_t __tmp = 0; if (from_dep_index < 0) {   return (f).return_type_ref;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_get_dep_return_type_in_caller_arena(from_dep_index, (f).return_type_ref, caller_arena, ctx);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  return 0;
}
int32_t typeck_resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t minus_one = -1;
  int32_t ret = typeck_find_func_return_type_in_module(module, arena, arena, arena, callee_expr_ref, minus_one, ctx);
  int32_t i = 0;
  while (i < (ctx)->ndep) {
    (void)(({ int32_t __tmp = 0; if (i >= 32) {   break;
 } else (__tmp = 0) ; __tmp; }));
    const struct ast_Module * dm = (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_modules)[0]) : ((ctx)->dep_modules)[i]);
    (void)((ret = typeck_find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, i, ctx)));
    (void)(({ int32_t __tmp = 0; if (ret != 0) {   return ret;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (ret != 0) {   return ret;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t typeck_expr_type_ref_impl(struct ast_ASTArena * arena, int32_t expr_ref) {
  struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
  return (e).resolved_type_ref;
}
int32_t typeck_expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref) {
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(expr_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (expr_ref <= 0 || expr_ref > (arena)->num_exprs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_expr_type_ref_impl(arena, expr_ref);
}
int typeck_type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref) {
  struct ast_Type t = ast_ast_arena_type_get(arena, type_ref);
  return (t).kind == ast_TypeKind_TYPE_BOOL;
}
int typeck_type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref) {
  (void)(({ int __tmp = 0; if (ast_ref_is_null(type_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if (type_ref <= 0 || type_ref > (arena)->num_types) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_type_ref_is_bool_impl(arena, type_ref);
}
int typeck_type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  struct ast_Type ta = ast_ast_arena_type_get(arena, a);
  struct ast_Type tb = ast_ast_arena_type_get(arena, b);
  (void)(({ int __tmp = 0; if ((ta).kind != (tb).kind) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if ((ta).kind == ast_TypeKind_TYPE_NAMED && (ta).name_len == (tb).name_len) {   int32_t i = 0;
  while (i < (ta).name_len) {
    (void)(({ int __tmp = 0; if ((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), ((ta).name)[0]) : ((ta).name)[i]) != (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), ((tb).name)[0]) : ((tb).name)[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if ((ta).kind == ast_TypeKind_TYPE_PTR || (ta).kind == ast_TypeKind_TYPE_SLICE) {   return typeck_type_refs_equal(arena, (ta).elem_type_ref, (tb).elem_type_ref);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if ((ta).kind == ast_TypeKind_TYPE_ARRAY) {   return (ta).array_size == (tb).array_size && typeck_type_refs_equal(arena, (ta).elem_type_ref, (tb).elem_type_ref);
 } else (__tmp = 0) ; __tmp; }));
  return 1;
}
int typeck_type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  (void)(({ int __tmp = 0; if (ast_ref_is_null(a) || ast_ref_is_null(b)) {   return a == b;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp = 0; if (a == b) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_type_refs_equal_impl(arena, a, b);
}
int32_t typeck_check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FLOAT_LIT) {   (void)(((e).float_bits_lo = typeck_float64_bits_lo((e).float_val)));
  (void)(((e).float_bits_hi = typeck_float64_bits_hi((e).float_val)));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_IF || (e).kind == ast_ExprKind_EXPR_TERNARY) {   (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_cond_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, (e).if_cond_ref)))) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).if_then_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_else_ref)) && typeck_check_expr(module, arena, (e).if_else_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BLOCK) {   return typeck_check_block(module, arena, (e).block_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ASSIGN) {   int32_t left_ref = (e).binop_left_ref;
  int32_t right_ref = (e).binop_right_ref;
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null(left_ref)) && (!ast_ref_is_null(right_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_refs_equal(arena, typeck_expr_type_ref(arena, left_ref), typeck_expr_type_ref(arena, right_ref)))) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, left_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, right_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN) {   (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null(return_type_ref))) {   int32_t op_ref = (e).unary_operand_ref;
  __tmp = ({ int32_t __tmp = 0; if ((!ast_ref_is_null(op_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_refs_equal(arena, typeck_expr_type_ref(arena, op_ref), return_type_ref))) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return typeck_check_expr(module, arena, (e).unary_operand_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_PANIC) {   return typeck_check_expr(module, arena, (e).unary_operand_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MATCH) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).match_matched_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t i = 0;
  while (i < (e).match_num_arms) {
    (void)(({ int32_t __tmp = 0; if (i >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_result_refs)[0]) : ((e).match_arm_result_refs)[i]), return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FIELD_ACCESS) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).field_access_base_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  struct ast_Expr base = ast_ast_arena_expr_get(arena, (e).field_access_base_ref);
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((base).resolved_type_ref)) && (base).resolved_type_ref > 0 && (base).resolved_type_ref <= (arena)->num_types) {   struct ast_Type bt = ast_ast_arena_type_get(arena, (base).resolved_type_ref);
  __tmp = ({ int32_t __tmp = 0; if ((bt).kind == ast_TypeKind_TYPE_NAMED && (bt).name_len > 0) {   int32_t off = typeck_get_field_offset_from_layout(module, (bt).name, (bt).name_len, (e).field_access_field_name, (e).field_access_field_len);
  __tmp = ({ int32_t __tmp = 0; if (off >= 0) {   (void)(((e).field_access_offset = off));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_INDEX) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).index_base_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return typeck_check_expr(module, arena, (e).index_index_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL) {   int32_t j = 0;
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).call_callee_ref))) {   struct ast_Expr callee = ast_ast_arena_expr_get(arena, (e).call_callee_ref);
  __tmp = ({ int32_t __tmp = 0; if ((callee).kind == ast_ExprKind_EXPR_VAR && (callee).var_name_len > 0 && (callee).var_name_len <= 63) {   int32_t ret_ty = typeck_resolve_call_callee_return_type(module, arena, (e).call_callee_ref, ctx);
  __tmp = ({ int32_t __tmp = 0; if (ret_ty != 0) {   (void)(((e).resolved_type_ref = ret_ty));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  while (j < (e).call_num_args) {
    (void)(({ int32_t __tmp = 0; if (j >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (j < 0 || (j) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[j]), return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_METHOD_CALL) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).method_call_base_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t j = 0;
  while (j < (e).method_call_num_args) {
    (void)(({ int32_t __tmp = 0; if (j >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (j < 0 || (j) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[j]), return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ADD || (e).kind == ast_ExprKind_EXPR_SUB || (e).kind == ast_ExprKind_EXPR_MUL || (e).kind == ast_ExprKind_EXPR_DIV || (e).kind == ast_ExprKind_EXPR_MOD || (e).kind == ast_ExprKind_EXPR_SHL || (e).kind == ast_ExprKind_EXPR_SHR || (e).kind == ast_ExprKind_EXPR_BITAND || (e).kind == ast_ExprKind_EXPR_BITOR || (e).kind == ast_ExprKind_EXPR_BITXOR || (e).kind == ast_ExprKind_EXPR_EQ || (e).kind == ast_ExprKind_EXPR_NE || (e).kind == ast_ExprKind_EXPR_LT || (e).kind == ast_ExprKind_EXPR_LE || (e).kind == ast_ExprKind_EXPR_GT || (e).kind == ast_ExprKind_EXPR_GE || (e).kind == ast_ExprKind_EXPR_LOGAND || (e).kind == ast_ExprKind_EXPR_LOGOR) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (e).binop_left_ref, return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return typeck_check_expr(module, arena, (e).binop_right_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NEG || (e).kind == ast_ExprKind_EXPR_BITNOT || (e).kind == ast_ExprKind_EXPR_LOGNOT) {   return typeck_check_expr(module, arena, (e).unary_operand_ref, return_type_ref, ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_VAR && (ctx)->current_block_ref != 0 && (ctx)->current_block_ref <= (arena)->num_blocks) {   struct ast_Block b = ast_ast_arena_block_get(arena, (ctx)->current_block_ref);
  int32_t i = 0;
  (void)((i = 0));
  while (i < (b).num_consts && i < 24) {
    struct ast_ConstDecl cd = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).const_decls)[0]) : ((b).const_decls)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((cd).type_ref)) && typeck_name_equal((cd).name, (cd).name_len, (e).var_name, (e).var_name_len)) {   (void)(((e).resolved_type_ref = (cd).type_ref));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_lets && i < 24) {
    struct ast_LetDecl ld = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).let_decls)[0]) : ((b).let_decls)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((ld).type_ref)) && typeck_name_equal((ld).name, (ld).name_len, (e).var_name, (e).var_name_len)) {   (void)(((e).resolved_type_ref = (ld).type_ref));
  (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_STRUCT_LIT) {   int32_t fi = 0;
  (void)(({ int32_t __tmp = 0; if (typeck_ensure_struct_layout_from_struct_lit(module, e) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  while (fi < (e).struct_lit_num_fields && fi < 8) {
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi]))) && typeck_check_expr(module, arena, (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi]), return_type_ref, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((fi = fi + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t typeck_check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(expr_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (expr_ref <= 0 || expr_ref > (arena)->num_exprs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_check_expr_impl(module, arena, expr_ref, return_type_ref, ctx);
}
int32_t typeck_check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t saved_block_ref = (ctx)->current_block_ref;
  struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
  int32_t i = 0;
  while (i < (b).num_consts) {
    (void)(({ int32_t __tmp = 0; if (i >= 24) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_ConstDecl cd = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).const_decls)[0]) : ((b).const_decls)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((cd).init_ref)) && (!ast_ref_is_null((cd).type_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_refs_equal(arena, (cd).type_ref, typeck_expr_type_ref(arena, (cd).init_ref)))) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (cd).init_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_lets) {
    (void)(({ int32_t __tmp = 0; if (i >= 24) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_LetDecl ld = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).let_decls)[0]) : ((b).let_decls)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((ld).init_ref)) && (!ast_ref_is_null((ld).type_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_refs_equal(arena, (ld).type_ref, typeck_expr_type_ref(arena, (ld).init_ref)))) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (ld).init_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_loops) {
    (void)(({ int32_t __tmp = 0; if (i >= 8) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_WhileLoop w = (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), ((b).loops)[0]) : ((b).loops)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((w).cond_ref)) && (!typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, (w).cond_ref)))) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (w).cond_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_block(module, arena, (w).body_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_for_loops) {
    (void)(({ int32_t __tmp = 0; if (i >= 8) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_ForLoop fl = (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), ((b).for_loops)[0]) : ((b).for_loops)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).cond_ref)) && (!typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, (fl).cond_ref)))) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (fl).init_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (fl).cond_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (fl).step_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_block(module, arena, (fl).body_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_expr_stmts) {
    (void)(({ int32_t __tmp = 0; if (i >= 32) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((b).expr_stmt_refs)[0]) : ((b).expr_stmt_refs)[i]), return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(((ctx)->current_block_ref = block_ref));
  (void)((i = 0));
  (void)((i = 0));
  (void)((i = 0));
  (void)((i = 0));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((b).final_expr_ref))) {   (void)(({ int32_t __tmp = 0; if (typeck_check_expr(module, arena, (b).final_expr_ref, return_type_ref, ctx) != 0) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if ((!ast_ref_is_null(return_type_ref))) {   __tmp = ({ int32_t __tmp = 0; if ((!typeck_type_refs_equal(arena, typeck_expr_type_ref(arena, (b).final_expr_ref), return_type_ref))) {   (void)(((ctx)->current_block_ref = saved_block_ref));
  return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ctx)->current_block_ref = saved_block_ref));
  return 0;
}
int32_t typeck_check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(block_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (block_ref <= 0 || block_ref > (arena)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return typeck_check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}
int32_t typeck_typeck_su_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  struct ast_Func main_f = ((module)->main_func_index < 0 || ((module)->main_func_index) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[(module)->main_func_index]);
  struct ast_Type ret_ty = ast_ast_arena_type_get(arena, (main_f).return_type_ref);
  int32_t i = 0;
  while (i < (module)->num_funcs) {
    (void)(({ int32_t __tmp = 0; if (i >= 256) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Func f = (i < 0 || (i) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[i]);
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((f).body_ref)) && (f).is_extern == 0) {   __tmp = ({ int32_t __tmp = 0; if (typeck_check_block(module, arena, (f).body_ref, (f).return_type_ref, ctx) != 0) {   return (-5);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((main_f).is_extern == 1) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null((main_f).body_ref)) {   return (-2);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null((main_f).return_type_ref)) {   return (-3);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ret_ty).kind != ast_TypeKind_TYPE_I32 && (ret_ty).kind != ast_TypeKind_TYPE_I64) {   return (-4);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t typeck_typeck_su_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if ((module)->main_func_index < 0) {   return (-10);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((module)->main_func_index >= (module)->num_funcs) {   return (-11);
 } else (__tmp = 0) ; __tmp; }));
  return typeck_typeck_su_ast_impl(module, arena, ctx);
}
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena *, int32_t);
extern int ast_ref_is_null(int32_t);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena *, int32_t);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena *, int32_t);
struct codegen_CodegenOutBuf { uint8_t data[262144]; int32_t len; };
int32_t codegen_append_byte_u8(struct codegen_CodegenOutBuf * out, uint8_t b);
int32_t codegen_append_byte(struct codegen_CodegenOutBuf * out, int32_t b);
int32_t codegen_emit_bytes_64(struct codegen_CodegenOutBuf * out, uint8_t buf[64], int32_t len);
int32_t codegen_emit_bytes_32(struct codegen_CodegenOutBuf * out, uint8_t buf[32], int32_t len);
int32_t codegen_emit_bytes_22(struct codegen_CodegenOutBuf * out, uint8_t buf[22], int32_t len);
int32_t codegen_emit_bytes_9(struct codegen_CodegenOutBuf * out, uint8_t buf[9], int32_t len);
int32_t codegen_emit_bytes_8(struct codegen_CodegenOutBuf * out, uint8_t buf[8], int32_t len);
int32_t codegen_emit_bytes_7(struct codegen_CodegenOutBuf * out, uint8_t buf[7], int32_t len);
int32_t codegen_emit_bytes_6(struct codegen_CodegenOutBuf * out, uint8_t buf[6], int32_t len);
int32_t codegen_emit_bytes_5(struct codegen_CodegenOutBuf * out, uint8_t buf[5], int32_t len);
int32_t codegen_emit_bytes_4(struct codegen_CodegenOutBuf * out, uint8_t buf[4], int32_t len);
int32_t codegen_emit_bytes_3(struct codegen_CodegenOutBuf * out, uint8_t buf[3], int32_t len);
int32_t codegen_emit_bytes_2(struct codegen_CodegenOutBuf * out, uint8_t buf[2], int32_t len);
int32_t codegen_format_uint(struct codegen_CodegenOutBuf * out, int32_t val);
int32_t codegen_format_int(struct codegen_CodegenOutBuf * out, int32_t val);
int32_t codegen_emit_indent(struct codegen_CodegenOutBuf * out, int32_t indent);
int32_t codegen_emit_type_kind(struct codegen_CodegenOutBuf * out, enum ast_TypeKind kind);
int32_t codegen_emit_type(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t type_ref);
int32_t codegen_emit_expr(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t expr_ref);
int32_t codegen_emit_block(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t block_ref, int32_t indent);
int32_t codegen_emit_func(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Func f, int is_entry);
int32_t codegen_codegen_su_ast_emit_header(struct codegen_CodegenOutBuf * out);
int32_t codegen_codegen_su_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out);
int32_t codegen_append_byte_u8(struct codegen_CodegenOutBuf * out, uint8_t b) {
  (void)(({ int32_t __tmp = 0; if ((out)->len >= 262144) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = b, 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
}
int32_t codegen_append_byte(struct codegen_CodegenOutBuf * out, int32_t b) {
  int32_t lo = b & 255;
  uint8_t tab[256] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255 };
  (void)(({ int32_t __tmp = 0; if ((out)->len >= 262144) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (lo < 0 || (lo) >= 256 ? (shulang_panic_(1, 0), (tab)[0]) : (tab)[lo]), 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
}
int32_t codegen_emit_bytes_64(struct codegen_CodegenOutBuf * out, uint8_t buf[64], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_32(struct codegen_CodegenOutBuf * out, uint8_t buf[32], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_22(struct codegen_CodegenOutBuf * out, uint8_t buf[22], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 22 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_9(struct codegen_CodegenOutBuf * out, uint8_t buf[9], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 9 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_8(struct codegen_CodegenOutBuf * out, uint8_t buf[8], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_7(struct codegen_CodegenOutBuf * out, uint8_t buf[7], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 7 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_6(struct codegen_CodegenOutBuf * out, uint8_t buf[6], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 6 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_5(struct codegen_CodegenOutBuf * out, uint8_t buf[5], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 5 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_4(struct codegen_CodegenOutBuf * out, uint8_t buf[4], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 4 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_3(struct codegen_CodegenOutBuf * out, uint8_t buf[3], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 3 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_bytes_2(struct codegen_CodegenOutBuf * out, uint8_t buf[2], int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte_u8(out, (i < 0 || (i) >= 2 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_format_uint(struct codegen_CodegenOutBuf * out, int32_t val) {
  (void)(({ int32_t __tmp = 0; if (val >= 10) {   int32_t q = (10 == 0 ? (shulang_panic_(1, 0), val) : (val / 10));
  int32_t r = (10 == 0 ? (shulang_panic_(1, 0), val) : (val % 10));
  (void)(({ int32_t __tmp = 0; if (codegen_format_uint(out, q) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 48 + r) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 48 + val) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t codegen_format_int(struct codegen_CodegenOutBuf * out, int32_t val) {
  int32_t u = 0 - val;
  (void)(({ int32_t __tmp = 0; if (val >= 0) {   return codegen_format_uint(out, val);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (u < 0) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 45) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t d[11] = { 50, 49, 52, 55, 52, 56, 51, 54, 52, 56, 0 };
  int32_t i = 0;
  while (i < 10) {
    int32_t b = (i < 0 || (i) >= 11 ? (shulang_panic_(1, 0), (d)[0]) : (d)[i]);
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, b) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 45) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_format_uint(out, u);
}
int32_t codegen_emit_indent(struct codegen_CodegenOutBuf * out, int32_t indent) {
  int32_t i = 0;
  while (i < indent) {
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t codegen_emit_type_kind(struct codegen_CodegenOutBuf * out, enum ast_TypeKind kind) {
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_I32) {   uint8_t s[8] = { 105, 110, 116, 51, 50, 95, 116, 0 };
  return codegen_emit_bytes_8(out, s, 7);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_I64) {   uint8_t s[8] = { 105, 110, 116, 54, 52, 95, 116, 0 };
  return codegen_emit_bytes_8(out, s, 7);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_BOOL) {   uint8_t s[4] = { 105, 110, 116, 0 };
  return codegen_emit_bytes_4(out, s, 3);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_U8) {   uint8_t s[9] = { 117, 105, 110, 116, 56, 95, 116, 0, 0 };
  return codegen_emit_bytes_9(out, s, 7);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_U32) {   uint8_t s[9] = { 117, 105, 110, 116, 51, 50, 95, 116, 0 };
  return codegen_emit_bytes_9(out, s, 8);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_U64) {   uint8_t s[9] = { 117, 105, 110, 116, 54, 52, 95, 116, 0 };
  return codegen_emit_bytes_9(out, s, 8);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_F32) {   uint8_t s[5] = { 102, 108, 111, 97, 0 };
  return codegen_emit_bytes_5(out, s, 4);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_F64) {   uint8_t s[7] = { 100, 111, 117, 98, 108, 101, 0 };
  return codegen_emit_bytes_7(out, s, 6);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (kind == ast_TypeKind_TYPE_VOID) {   uint8_t s[5] = { 118, 111, 105, 100, 0 };
  return codegen_emit_bytes_5(out, s, 4);
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t codegen_emit_type(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t type_ref) {
  struct ast_Type t = ast_ast_arena_type_get(arena, type_ref);
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(type_ref)) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((t).kind == ast_TypeKind_TYPE_NAMED && (t).name_len > 0) {   return codegen_emit_bytes_64(out, (t).name, (t).name_len);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_emit_type_kind(out, (t).kind);
}
int32_t codegen_emit_expr(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t expr_ref) {
  struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(expr_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (expr_ref <= 0 || expr_ref > (arena)->num_exprs) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LIT) {   return codegen_format_int(out, (e).int_val);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BOOL_LIT) {   (void)(({ int32_t __tmp = 0; if ((e).int_val != 0) {   return codegen_append_byte(out, 49);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 48);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_VAR) {   return codegen_emit_bytes_64(out, (e).var_name, (e).var_name_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN) {   uint8_t op[9] = { 114, 101, 116, 117, 114, 110, 32, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, op, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).unary_operand_ref)) && codegen_emit_expr(arena, out, (e).unary_operand_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BLOCK) {   uint8_t open[4] = { 40, 123, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, open, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).block_ref)) && codegen_emit_block(arena, out, (e).block_ref, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t tail[8] = { 32, 125, 41, 0, 0, 0, 0, 0 };
  return codegen_emit_bytes_8(out, tail, 3);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ADD) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 43, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SUB) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 45, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ASSIGN) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 61, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NEG) {   uint8_t pre[3] = { 45, 40, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, pre, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).unary_operand_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_IF) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_cond_ref)) && codegen_emit_expr(arena, out, (e).if_cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t q[4] = { 32, 63, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, q, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_then_ref)) && codegen_emit_expr(arena, out, (e).if_then_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t colon[4] = { 32, 58, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, colon, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_else_ref)) && codegen_emit_expr(arena, out, (e).if_else_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL) {   (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).call_callee_ref)) && codegen_emit_expr(arena, out, (e).call_callee_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t ai = 0;
  while (ai < (e).call_num_args) {
    (void)(({ int32_t __tmp = 0; if (ai >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (ai > 0) {   uint8_t comma[3] = { 44, 32, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, comma, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[ai]))) && codegen_emit_expr(arena, out, (ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[ai])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((ai = ai + 1));
  }
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 41) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FLOAT_LIT) {   (void)(({ int32_t __tmp = 0; if ((e).float_val == 0.0) {   uint8_t z[4] = { 48, 46, 48, 0 };
  return codegen_emit_bytes_4(out, z, 3);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t z[4] = { 48, 46, 48, 0 };
  return codegen_emit_bytes_4(out, z, 3);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MUL) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 42, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_DIV) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 47, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MOD) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 37, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 61, 61, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NE) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 33, 61, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LT) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 60, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LE) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 60, 61, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GT) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 62, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GE) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 62, 61, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGAND) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[5] = { 32, 38, 38, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, op, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGOR) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[5] = { 32, 124, 124, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, op, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHL) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 60, 60, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHR) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 62, 62, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITAND) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 38, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITOR) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 124, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITXOR) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_left_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t op[4] = { 32, 94, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, op, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).binop_right_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITNOT) {   uint8_t pre[3] = { 126, 40, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, pre, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).unary_operand_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGNOT) {   uint8_t pre[3] = { 33, 40, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, pre, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).unary_operand_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_TERNARY) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_cond_ref)) && codegen_emit_expr(arena, out, (e).if_cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t q[4] = { 32, 63, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, q, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_then_ref)) && codegen_emit_expr(arena, out, (e).if_then_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t colon[4] = { 32, 58, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, colon, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).if_else_ref)) && codegen_emit_expr(arena, out, (e).if_else_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_INDEX) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).index_base_ref)) && codegen_emit_expr(arena, out, (e).index_base_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 41) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).index_base_is_slice != 0) {   uint8_t dot[6] = { 46, 100, 97, 116, 97, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_6(out, dot, 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 91) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).index_index_ref)) && codegen_emit_expr(arena, out, (e).index_index_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 93);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FIELD_ACCESS) {   (void)(({ int32_t __tmp = 0; if ((e).field_access_is_enum_variant != 0) {   return codegen_emit_bytes_64(out, (e).field_access_field_name, (e).field_access_field_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).field_access_base_ref)) && codegen_emit_expr(arena, out, (e).field_access_base_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t dot[2] = { 46, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_2(out, dot, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (e).field_access_field_name, (e).field_access_field_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_PANIC) {   uint8_t p[22] = { 115, 104, 117, 108, 97, 110, 103, 95, 112, 97, 110, 105, 99, 95, 40, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_22(out, p, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null((e).unary_operand_ref)) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 48) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 44) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (codegen_append_byte(out, 48) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 49) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 44) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (e).unary_operand_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BREAK) {   return codegen_append_byte(out, 48);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CONTINUE) {   return codegen_append_byte(out, 48);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_METHOD_CALL) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).method_call_base_ref)) && codegen_emit_expr(arena, out, (e).method_call_base_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t dot[2] = { 46, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_2(out, dot, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (e).method_call_name, (e).method_call_name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t mi = 0;
  while (mi < (e).method_call_num_args) {
    (void)(({ int32_t __tmp = 0; if (mi >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (mi > 0) {   uint8_t comma[3] = { 44, 32, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, comma, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((mi < 0 || (mi) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[mi]))) && codegen_emit_expr(arena, out, (mi < 0 || (mi) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[mi])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((mi = mi + 1));
  }
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 41) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MATCH) {   (void)(({ int32_t __tmp = 0; if ((e).match_num_arms <= 0) {   return codegen_append_byte(out, 48);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null(((e).match_arm_result_refs)[0])) && codegen_emit_expr(arena, out, ((e).match_arm_result_refs)[0]) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_STRUCT_LIT) {   uint8_t open[9] = { 40, 115, 116, 114, 117, 99, 116, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, open, 8) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (e).struct_lit_struct_name, (e).struct_lit_struct_name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t open2[5] = { 41, 123, 32, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, open2, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t fi = 0;
  while (fi < (e).struct_lit_num_fields && fi < 8) {
    (void)(({ int32_t __tmp = 0; if (fi > 0) {   uint8_t comma[3] = { 44, 32, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, comma, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 46) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t flen = (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_lens)[0]) : ((e).struct_lit_field_lens)[fi]);
    (void)(({ int32_t __tmp = 0; if (flen > 64) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_names)[0]) : ((e).struct_lit_field_names)[fi]), 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_field_names)[0]) : ((e).struct_lit_field_names)[fi]), flen) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
    uint8_t eq[4] = { 32, 61, 32, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, eq, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi]))) && codegen_emit_expr(arena, out, (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((fi = fi + 1));
  }
  uint8_t close[4] = { 32, 125, 0, 0 };
  return codegen_emit_bytes_4(out, close, 2);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ARRAY_LIT) {   int32_t n = (e).array_lit_num_elems;
  int32_t elem_type_ref = 0;
  int32_t is_slice = 0;
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((e).resolved_type_ref)) && (e).resolved_type_ref > 0 && (e).resolved_type_ref <= (arena)->num_types) {   struct ast_Type ty = ast_ast_arena_type_get(arena, (e).resolved_type_ref);
  __tmp = ({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_SLICE) {   (void)((is_slice = 1));
  (void)((elem_type_ref = (ty).elem_type_ref));
 } else (__tmp = ({ int32_t __tmp = 0; if ((ty).kind == ast_TypeKind_TYPE_ARRAY) {   (void)((elem_type_ref = (ty).elem_type_ref));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (elem_type_ref == 0 && n > 0) {   int32_t first_ref = ((e).array_lit_elem_refs)[0];
  __tmp = ({ int32_t __tmp = 0; if ((!ast_ref_is_null(first_ref))) {   struct ast_Expr first_e = ast_ast_arena_expr_get(arena, first_ref);
  (void)((elem_type_ref = (first_e).resolved_type_ref));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (is_slice != 0) {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (e).resolved_type_ref) != 0) {   uint8_t fallback[9] = { 117, 105, 110, 116, 56, 95, 116, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, fallback, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t slice_mid[22] = { 41, 123, 32, 46, 100, 97, 116, 97, 32, 61, 32, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_22(out, slice_mid, 11) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null(elem_type_ref)) && codegen_emit_type(arena, out, elem_type_ref) != 0) {   uint8_t fallback[9] = { 117, 105, 110, 116, 56, 95, 116, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, fallback, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t arr[5] = { 93, 93, 41, 123, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, arr, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null(elem_type_ref)) && codegen_emit_type(arena, out, elem_type_ref) != 0) {   uint8_t fallback[9] = { 117, 105, 110, 116, 56, 95, 116, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, fallback, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t arr[5] = { 93, 93, 41, 123, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, arr, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  int32_t ai = 0;
  while (ai < n && ai < 16) {
    (void)(({ int32_t __tmp = 0; if (ai > 0) {   uint8_t comma[3] = { 44, 32, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, comma, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).array_lit_elem_refs)[0]) : ((e).array_lit_elem_refs)[ai]))) && codegen_emit_expr(arena, out, (ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).array_lit_elem_refs)[0]) : ((e).array_lit_elem_refs)[ai])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((ai = ai + 1));
  }
  (void)(({ int32_t __tmp = 0; if (is_slice != 0) {   uint8_t slice_end[22] = { 32, 125, 44, 32, 46, 108, 101, 110, 103, 116, 104, 32, 61, 32, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_22(out, slice_end, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_format_int(out, ai) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 125) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return codegen_append_byte(out, 41);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t close[4] = { 32, 125, 0, 0 };
  return codegen_emit_bytes_4(out, close, 2);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ENUM_VARIANT) {   return codegen_append_byte(out, 48);
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t codegen_emit_block(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t block_ref, int32_t indent) {
  struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
  int32_t i = 0;
  while (i < (b).num_consts) {
    (void)(({ int32_t __tmp = 0; if (i >= 24) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_ConstDecl cd = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).const_decls)[0]) : ((b).const_decls)[i]);
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (cd).type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sp[3] = { 32, 0, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sp, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (cd).name, (cd).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t eq[4] = { 32, 61, 32, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, eq, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (cd).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sc[3] = { 59, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_lets) {
    (void)(({ int32_t __tmp = 0; if (i >= 24) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_LetDecl ld = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((b).let_decls)[0]) : ((b).let_decls)[i]);
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (ld).type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (ld).name, (ld).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t eq[4] = { 32, 61, 32, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, eq, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (ld).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sc[3] = { 59, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_expr_stmts) {
    (void)(({ int32_t __tmp = 0; if (i >= 32) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t v[9] = { 40, 118, 111, 105, 100, 41, 40, 0, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, v, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((b).expr_stmt_refs)[0]) : ((b).expr_stmt_refs)[i])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sc[4] = { 41, 59, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, sc, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_loops) {
    (void)(({ int32_t __tmp = 0; if (i >= 8) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_WhileLoop w = (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), ((b).loops)[0]) : ((b).loops)[i]);
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t wh[8] = { 119, 104, 105, 108, 101, 32, 40, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_8(out, wh, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (w).cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t paren[5] = { 41, 32, 123, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, paren, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_block(arena, out, (w).body_ref, indent + 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t close[3] = { 125, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, close, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  while (i < (b).num_for_loops) {
    (void)(({ int32_t __tmp = 0; if (i >= 8) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_ForLoop fl = (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), ((b).for_loops)[0]) : ((b).for_loops)[i]);
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t fk[6] = { 102, 111, 114, 32, 40, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_6(out, fk, 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).init_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sc1[3] = { 59, 32, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc1, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).cond_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    uint8_t sc2[3] = { 59, 32, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc2, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).step_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).step_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    uint8_t paren[5] = { 41, 32, 123, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, paren, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).body_ref)) && codegen_emit_block(arena, out, (fl).body_ref, indent + 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t close[3] = { 125, 10, 0 };
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, close, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (ast_ref_is_null(block_ref)) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (block_ref <= 0 || block_ref > (arena)->num_blocks) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((b).num_stmt_order > 0) {   int32_t si = 0;
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((b).final_expr_ref))) {   (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t ret[8] = { 114, 101, 116, 117, 114, 110, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_8(out, ret, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (b).final_expr_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc[4] = { 59, 10, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  while (si < (b).num_stmt_order && si < 96) {
    uint8_t k = ((si < 0 || (si) >= 96 ? (shulang_panic_(1, 0), ((b).stmt_order)[0]) : ((b).stmt_order)[si])).kind;
    int32_t idx = ((si < 0 || (si) >= 96 ? (shulang_panic_(1, 0), ((b).stmt_order)[0]) : ((b).stmt_order)[si])).idx;
    (void)(({ int32_t __tmp = 0; if (k == 0) {   __tmp = ({ int32_t __tmp = 0; if (idx >= 0 && idx < (b).num_consts && idx < 24) {   struct ast_ConstDecl cd = (idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((b).const_decls)[0]) : ((b).const_decls)[idx]);
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (cd).type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sp[3] = { 32, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sp, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (cd).name, (cd).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t eq[4] = { 32, 61, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, eq, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (cd).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc[3] = { 59, 10, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (k == 1) {   __tmp = ({ int32_t __tmp = 0; if (idx >= 0 && idx < (b).num_lets && idx < 24) {   struct ast_LetDecl ld = (idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((b).let_decls)[0]) : ((b).let_decls)[idx]);
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (ld).type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (ld).name, (ld).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t eq[4] = { 32, 61, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, eq, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (ld).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc[3] = { 59, 10, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (k == 2) {   __tmp = ({ int32_t __tmp = 0; if (idx >= 0 && idx < (b).num_expr_stmts && idx < 32) {   (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t v[9] = { 40, 118, 111, 105, 100, 41, 40, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, v, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((b).expr_stmt_refs)[0]) : ((b).expr_stmt_refs)[idx])) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc[4] = { 41, 59, 10, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, sc, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (k == 3) {   __tmp = ({ int32_t __tmp = 0; if (idx >= 0 && idx < (b).num_loops && idx < 8) {   struct ast_WhileLoop w = (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), ((b).loops)[0]) : ((b).loops)[idx]);
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t wh[8] = { 119, 104, 105, 108, 101, 32, 40, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_8(out, wh, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (w).cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t paren[5] = { 41, 32, 123, 10, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, paren, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_block(arena, out, (w).body_ref, indent + 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t close[3] = { 125, 10, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, close, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (k == 4) {   __tmp = ({ int32_t __tmp = 0; if (idx >= 0 && idx < (b).num_for_loops && idx < 8) {   struct ast_ForLoop fl = (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), ((b).for_loops)[0]) : ((b).for_loops)[idx]);
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t fk[6] = { 102, 111, 114, 32, 40, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_6(out, fk, 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).init_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).init_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc1[3] = { 59, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc1, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).cond_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).cond_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc2[3] = { 59, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, sc2, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).step_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (fl).step_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  uint8_t paren[5] = { 41, 32, 123, 10, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_5(out, paren, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((fl).body_ref)) && codegen_emit_block(arena, out, (fl).body_ref, indent + 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t close[3] = { 125, 10, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, close, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; }));
    (void)((si = si + 1));
  }
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)((i = 0));
  (void)((i = 0));
  (void)((i = 0));
  (void)((i = 0));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((b).final_expr_ref))) {   (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, indent) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t ret[8] = { 114, 101, 116, 117, 114, 110, 32, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_8(out, ret, 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_expr(arena, out, (b).final_expr_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sc[4] = { 59, 10, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, sc, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t codegen_emit_func(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Func f, int is_entry) {
  uint8_t main_name[4] = { 109, 97, 105, 110 };
  int name_is_main = (f).name_len == 4 && ((f).name)[0] == 109 && (1 < 0 || (1) >= 64 ? (shulang_panic_(1, 0), ((f).name)[0]) : ((f).name)[1]) == 97 && (2 < 0 || (2) >= 64 ? (shulang_panic_(1, 0), ((f).name)[0]) : ((f).name)[2]) == 105 && (3 < 0 || (3) >= 64 ? (shulang_panic_(1, 0), ((f).name)[0]) : ((f).name)[3]) == 110;
  uint8_t lpar[2] = { 40, 0 };
  uint8_t rpar[3] = { 41, 32, 0 };
  uint8_t brace[3] = { 123, 10, 0 };
  int need_fallback_return = 1;
  uint8_t close[3] = { 125, 10, 0 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (f).return_type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (is_entry && name_is_main) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_4(out, main_name, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_64(out, (f).name, (f).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; })) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_2(out, lpar, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((f).num_params == 0) {   uint8_t v[7] = { 118, 111, 105, 100, 0, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_7(out, v, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   int32_t p = 0;
  while (p < (f).num_params) {
    (void)(({ int32_t __tmp = 0; if (p >= 16) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (p > 0) {   uint8_t comma[3] = { 44, 32, 0 };
  __tmp = ({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, comma, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Param param = (p < 0 || (p) >= 16 ? (shulang_panic_(1, 0), ((f).params)[0]) : ((f).params)[p]);
    (void)(({ int32_t __tmp = 0; if (codegen_emit_type(arena, out, (param).type_ref) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_append_byte(out, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_32(out, (param).name, (param).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((p = p + 1));
  }
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, rpar, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, brace, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((f).body_ref))) {   __tmp = ({ int32_t __tmp = 0; if (codegen_emit_block(arena, out, (f).body_ref, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((!ast_ref_is_null((f).body_ref))) {   struct ast_Block b = ast_ast_arena_block_get(arena, (f).body_ref);
  __tmp = ({ int32_t __tmp = 0; if ((!ast_ref_is_null((b).final_expr_ref))) {   (void)((need_fallback_return = 0));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (need_fallback_return) {   (void)(({ int32_t __tmp = 0; if (codegen_emit_indent(out, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t ret0[9] = { 114, 101, 116, 117, 114, 110, 32, 48, 59 };
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_9(out, ret0, 9) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (codegen_append_byte(out, 10) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (codegen_emit_bytes_3(out, close, 2) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t codegen_codegen_su_ast_emit_header(struct codegen_CodegenOutBuf * out) {
  uint8_t h[22] = { 35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 115, 116, 100, 105, 110, 116, 46, 104, 62, 10, 0, 0 };
  return codegen_emit_bytes_22(out, h, 20);
}
int32_t codegen_codegen_su_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out) {
  int32_t i = 0;
  while (i < (module)->num_funcs) {
    (void)(({ int32_t __tmp = 0; if (i == 0 && codegen_codegen_su_ast_emit_header(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i >= 256) {   break;
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Func f = (i < 0 || (i) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[i]);
    int is_entry = i == (module)->main_func_index || (module)->num_funcs == 1;
    (void)(({ int32_t __tmp = 0; if (codegen_emit_func(arena, out, f, is_entry) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
struct preprocess_ParseDirectiveResult { int32_t kind; int32_t sym_len; };
struct preprocess_ParseDirectiveResult preprocess_parse_directive(uint8_t line_buf[512], int32_t line_len, uint8_t sym[64]);
int32_t preprocess_preprocess_su(struct shulang_slice_uint8_t * source, struct shulang_slice_uint8_t * out_buf);
int32_t preprocess_preprocess_su_buf(uint8_t source_buf[262144], ptrdiff_t source_len, uint8_t out_buf[262144], int32_t out_cap);
struct preprocess_ParseDirectiveResult preprocess_parse_directive(uint8_t line_buf[512], int32_t line_len, uint8_t sym[64]) {
  struct preprocess_ParseDirectiveResult zero = (struct preprocess_ParseDirectiveResult){ .kind = 0, .sym_len = 0 };
  int32_t pos = 0;
  while (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9) {
    (void)((pos = pos + 1));
  }
  while (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9) {
    (void)((pos = pos + 1));
  }
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos >= line_len || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 35) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  (void)((pos = pos + 1));
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos >= line_len) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (pos + 2 <= line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 105 && (pos + 1 < 0 || (pos + 1) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 1]) == 102) {   (void)((pos = pos + 2));
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 32 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 9 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 10 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 13 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 0) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  while (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9) {
    (void)((pos = pos + 1));
  }
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos >= line_len) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  int32_t s = 0;
  while (pos < line_len && s < 63) {
    uint8_t ch = (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]);
    (void)(({ int32_t __tmp = 0; if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122 || ch == 95) {   (void)(((s < 0 || (s) >= 64 ? (shulang_panic_(1, 0), 0) : ((sym)[s] = ch, 0))));
  (void)((s = s + 1));
  (void)((pos = pos + 1));
 } else {   break;
 } ; __tmp; }));
  }
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (s == 0) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  return (struct preprocess_ParseDirectiveResult){ .kind = 1, .sym_len = s };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (pos + 6 <= line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 101 && (pos + 1 < 0 || (pos + 1) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 1]) == 108 && (pos + 2 < 0 || (pos + 2) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 2]) == 115 && (pos + 3 < 0 || (pos + 3) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 3]) == 101 && (pos + 4 < 0 || (pos + 4) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 4]) == 105 && (pos + 5 < 0 || (pos + 5) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 5]) == 102) {   (void)((pos = pos + 6));
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 32 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 9 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 10 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 13 && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) != 0) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  while (pos < line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9) {
    (void)((pos = pos + 1));
  }
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos >= line_len) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  int32_t s = 0;
  while (pos < line_len && s < 63) {
    uint8_t ch = (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]);
    (void)(({ int32_t __tmp = 0; if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122 || ch == 95) {   (void)(((s < 0 || (s) >= 64 ? (shulang_panic_(1, 0), 0) : ((sym)[s] = ch, 0))));
  (void)((s = s + 1));
  (void)((pos = pos + 1));
 } else {   break;
 } ; __tmp; }));
  }
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (s == 0) {   return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  return (struct preprocess_ParseDirectiveResult){ .kind = 4, .sym_len = s };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos + 4 <= line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 101 && (pos + 1 < 0 || (pos + 1) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 1]) == 108 && (pos + 2 < 0 || (pos + 2) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 2]) == 115 && (pos + 3 < 0 || (pos + 3) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 3]) == 101) {   (void)((pos = pos + 4));
  (void)(({ int32_t __tmp = 0; if (pos >= line_len || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 10 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 13 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 0) {   return (struct preprocess_ParseDirectiveResult){ .kind = 2, .sym_len = 0 };
 } else (__tmp = 0) ; __tmp; }));
  return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  (void)(({ struct preprocess_ParseDirectiveResult __tmp = (struct preprocess_ParseDirectiveResult){0}; if (pos + 5 <= line_len && (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 101 && (pos + 1 < 0 || (pos + 1) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 1]) == 110 && (pos + 2 < 0 || (pos + 2) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 2]) == 100 && (pos + 3 < 0 || (pos + 3) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 3]) == 105 && (pos + 4 < 0 || (pos + 4) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos + 4]) == 102) {   (void)((pos = pos + 5));
  (void)(({ int32_t __tmp = 0; if (pos >= line_len || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 32 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 9 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 10 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 13 || (pos < 0 || (pos) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[pos]) == 0) {   return (struct preprocess_ParseDirectiveResult){ .kind = 3, .sym_len = 0 };
 } else (__tmp = 0) ; __tmp; }));
  return zero;
 } else (__tmp = (struct preprocess_ParseDirectiveResult){0}) ; __tmp; }));
  return zero;
}
int32_t preprocess_preprocess_su(struct shulang_slice_uint8_t * source, struct shulang_slice_uint8_t * out_buf) {
  int32_t stack[32] = { 0 };
  int32_t depth = 0;
  int32_t out_len = 0;
  int32_t line_len = 0;
  uint8_t line_buf[512] = { 0 };
  int32_t pos = 0;
  while (pos < (source)->length) {
    uint8_t ch = (pos < 0 || (size_t)(pos) >= (source)->length ? (shulang_panic_(1, 0), (source)->data[0]) : (source)->data[pos]);
    (void)(({ int32_t __tmp = 0; if (ch == 10) {   (void)(({ int32_t __tmp = 0; if (line_len > 0 || 1) {   uint8_t sym[64] = { 0 };
  struct preprocess_ParseDirectiveResult res = preprocess_parse_directive(line_buf, line_len, sym);
  int32_t kind = (res).kind;
  __tmp = ({ int32_t __tmp = 0; if (kind != 0) {   (void)(({ int32_t __tmp = 0; if (kind == 1) {   (void)(({ int32_t __tmp = 0; if (depth >= 32) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (depth > 0 && (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth < 0 || (depth) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth] = 0, 0))));
  (void)((depth = depth + 1));
 } else {   (void)(((depth < 0 || (depth) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth] = 0, 0))));
  (void)((depth = depth + 1));
 } ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (kind == 2) {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 0, 0))));
 } else (__tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 2, 0))));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (kind == 4) {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 2) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 3, 0))));
 } else (__tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 0, 0))));
 } else {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 3, 0))));
 } ; __tmp; })) ; __tmp; });
 } else {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((depth = depth - 1));
 } ; __tmp; })) ; __tmp; })) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_len >= (out_buf)->length) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_len < 0 || (size_t)(out_len) >= (out_buf)->length ? (shulang_panic_(1, 0), 0) : ((out_buf)->data[out_len] = 10, 0))));
  (void)((out_len = out_len + 1));
 } else {   int keeping = depth == 0 || depth > 0 && (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1 || (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 2;
  (void)(({ int32_t __tmp = 0; if (keeping) {   int32_t i = 0;
  while (i < line_len) {
    (void)(({ int32_t __tmp = 0; if (out_len >= (out_buf)->length) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(((out_len < 0 || (size_t)(out_len) >= (out_buf)->length ? (shulang_panic_(1, 0), 0) : ((out_buf)->data[out_len] = (i < 0 || (i) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[i]), 0))));
    (void)((out_len = out_len + 1));
    (void)((i = i + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_len >= (out_buf)->length) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_len < 0 || (size_t)(out_len) >= (out_buf)->length ? (shulang_panic_(1, 0), 0) : ((out_buf)->data[out_len] = 10, 0))));
  (void)((out_len = out_len + 1));
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((line_len = 0));
  (void)((pos = pos + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (line_len < 511) {   (void)(((line_len < 0 || (line_len) >= 512 ? (shulang_panic_(1, 0), 0) : ((line_buf)[line_len] = ch, 0))));
  (void)((line_len = line_len + 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)((pos = pos + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((out_buf)->length <= 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (depth != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return out_len;
}
int32_t preprocess_preprocess_su_buf(uint8_t source_buf[262144], ptrdiff_t source_len, uint8_t out_buf[262144], int32_t out_cap) {
  int32_t stack[32] = { 0 };
  int32_t depth = 0;
  int32_t out_len = 0;
  int32_t line_len = 0;
  uint8_t line_buf[512] = { 0 };
  int32_t pos = 0;
  while (pos < source_len && pos < 262144) {
    uint8_t ch = (pos < 0 || (pos) >= 262144 ? (shulang_panic_(1, 0), (source_buf)[0]) : (source_buf)[pos]);
    (void)(({ int32_t __tmp = 0; if (ch == 10) {   (void)(({ int32_t __tmp = 0; if (line_len > 0 || 1) {   uint8_t sym[64] = { 0 };
  struct preprocess_ParseDirectiveResult res = preprocess_parse_directive(line_buf, line_len, sym);
  int32_t kind = (res).kind;
  __tmp = ({ int32_t __tmp = 0; if (kind != 0) {   (void)(({ int32_t __tmp = 0; if (kind == 1) {   (void)(({ int32_t __tmp = 0; if (depth >= 32) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (depth > 0 && (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth < 0 || (depth) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth] = 0, 0))));
  (void)((depth = depth + 1));
 } else {   (void)(((depth < 0 || (depth) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth] = 0, 0))));
  (void)((depth = depth + 1));
 } ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (kind == 2) {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 0, 0))));
 } else (__tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 2, 0))));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if (kind == 4) {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 2) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 3, 0))));
 } else (__tmp = ({ int32_t __tmp = 0; if ((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 0) {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 0, 0))));
 } else {   (void)(((depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((stack)[depth - 1] = 3, 0))));
 } ; __tmp; })) ; __tmp; });
 } else {   (void)(({ int32_t __tmp = 0; if (depth == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((depth = depth - 1));
 } ; __tmp; })) ; __tmp; })) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_len >= out_cap) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_len < 0 || (out_len) >= 262144 ? (shulang_panic_(1, 0), 0) : ((out_buf)[out_len] = 10, 0))));
  (void)((out_len = out_len + 1));
 } else {   int keeping = depth == 0 || depth > 0 && (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 1 || (depth - 1 < 0 || (depth - 1) >= 32 ? (shulang_panic_(1, 0), (stack)[0]) : (stack)[depth - 1]) == 2;
  (void)(({ int32_t __tmp = 0; if (keeping) {   int32_t i = 0;
  while (i < line_len) {
    (void)(({ int32_t __tmp = 0; if (out_len >= out_cap) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(((out_len < 0 || (out_len) >= 262144 ? (shulang_panic_(1, 0), 0) : ((out_buf)[out_len] = (i < 0 || (i) >= 512 ? (shulang_panic_(1, 0), (line_buf)[0]) : (line_buf)[i]), 0))));
    (void)((out_len = out_len + 1));
    (void)((i = i + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (out_len >= out_cap) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_len < 0 || (out_len) >= 262144 ? (shulang_panic_(1, 0), 0) : ((out_buf)[out_len] = 10, 0))));
  (void)((out_len = out_len + 1));
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((line_len = 0));
  (void)((pos = pos + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (line_len < 511) {   (void)(((line_len < 0 || (line_len) >= 512 ? (shulang_panic_(1, 0), 0) : ((line_buf)[line_len] = ch, 0))));
  (void)((line_len = line_len + 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)((pos = pos + 1));
  }
  (void)(({ int32_t __tmp = 0; if (out_cap <= 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (depth != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return out_len;
}
enum types_TargetArch { types_TargetArch_TARGET_X86_64, types_TargetArch_TARGET_ARM64, types_TargetArch_TARGET_RISCV64, types_TargetArch_TARGET_NONE };
int32_t types_append_asm_line(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t len);
int32_t types_format_u32_to_buf(uint8_t * buf, int32_t off, int32_t max, int32_t u);
int32_t types_format_i32_to_buf(uint8_t * buf, int32_t off, int32_t max, int32_t val);
int32_t types_format_u32_hex8_to_buf(uint8_t * buf, int32_t off, int32_t val);
int32_t types_append_asm_line(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t len) {
  int32_t i = 0;
  while (i < len && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (ptr)[i], 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (i < len) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   uint8_t nl[1] = { 10 };
  (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (nl)[0], 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t types_format_u32_to_buf(uint8_t * buf, int32_t off, int32_t max, int32_t u) {
  uint8_t digit_chars[10] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
  uint8_t tmp[10] = { 0 };
  int32_t num_digits = 0;
  int32_t v = u;
  while (v > 0 && num_digits < 10) {
    (void)(((num_digits < 0 || (num_digits) >= 10 ? (shulang_panic_(1, 0), 0) : ((tmp)[num_digits] = ((10 == 0 ? (shulang_panic_(1, 0), v) : (v % 10)) < 0 || ((10 == 0 ? (shulang_panic_(1, 0), v) : (v % 10))) >= 10 ? (shulang_panic_(1, 0), (digit_chars)[0]) : (digit_chars)[(10 == 0 ? (shulang_panic_(1, 0), v) : (v % 10))]), 0))));
    (void)((num_digits = num_digits + 1));
    (void)((v = (10 == 0 ? (shulang_panic_(1, 0), v) : (v / 10))));
  }
  (void)(({ int32_t __tmp = 0; if (max < 1) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (num_digits == 0) {   (void)(((buf)[off] = (digit_chars)[0]));
  (void)((num_digits = 1));
 } else {   (void)(({ int32_t __tmp = 0; if (num_digits > max) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (off + num_digits >= 262144) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t idx = 0;
  while (idx < num_digits) {
    (void)(((buf)[off + idx] = (num_digits - 1 - idx < 0 || (num_digits - 1 - idx) >= 10 ? (shulang_panic_(1, 0), (tmp)[0]) : (tmp)[num_digits - 1 - idx])));
    (void)((idx = idx + 1));
  }
 } ; __tmp; }));
  return num_digits;
}
int32_t types_format_i32_to_buf(uint8_t * buf, int32_t off, int32_t max, int32_t val) {
  (void)(({ int32_t __tmp = 0; if (val < 0) {   int32_t u = 0 - val;
  (void)(({ int32_t __tmp = 0; if (u < 0) {   (void)(({ int32_t __tmp = 0; if (max < 11) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t s[12] = { 45, 50, 49, 52, 55, 52, 56, 51, 54, 52, 56, 0 };
  int32_t k = 0;
  while (k < 11) {
    (void)(((buf)[off + k] = (k < 0 || (k) >= 12 ? (shulang_panic_(1, 0), (s)[0]) : (s)[k])));
    (void)((k = k + 1));
  }
  return 11;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (max < 1) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t minus[1] = { 45 };
  (void)(((buf)[off] = (minus)[0]));
  int32_t n = types_format_u32_to_buf(buf, off + 1, max - 1, u);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return n + 1;
 } else (__tmp = 0) ; __tmp; }));
  return types_format_u32_to_buf(buf, off, max, val);
}
int32_t types_format_u32_hex8_to_buf(uint8_t * buf, int32_t off, int32_t val) {
  uint8_t hex[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102 };
  int32_t i = 0;
  while (i < 8) {
    int32_t shift = (7 - i) * 4;
    int32_t nibble = val >> shift & 15;
    (void)(((buf)[off + i] = (nibble < 0 || (nibble) >= 16 ? (shulang_panic_(1, 0), (hex)[0]) : (hex)[nibble])));
    (void)((i = i + 1));
  }
  return 8;
}
extern int32_t types_format_i32_to_buf(uint8_t *, int32_t, int32_t, int32_t);
extern int32_t types_append_asm_line(struct codegen_CodegenOutBuf *, uint8_t *, int32_t);
extern int32_t types_format_u32_hex8_to_buf(uint8_t *, int32_t, int32_t);
int32_t arch_x86_64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size);
int32_t arch_x86_64_emit_epilogue(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_x86_64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_x86_64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi);
int32_t arch_x86_64_emit_add(struct codegen_CodegenOutBuf * out, uint8_t * dst_reg, int32_t dst_len, uint8_t * src_reg, int32_t src_len);
int32_t arch_x86_64_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k);
int32_t arch_x86_64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_x86_64_emit_section_text(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_x86_64_emit_push_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_pop_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_pop_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_cltd(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_neg_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc);
int32_t arch_x86_64_emit_not_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_x86_64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_x86_64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_x86_64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm);
int32_t arch_x86_64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_x86_64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size);
int32_t arch_x86_64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_x86_64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size) {
  uint8_t line[64] = { 112, 117, 115, 104, 113, 32, 37, 114, 98, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t mov_line[32] = { 109, 111, 118, 113, 32, 37, 114, 115, 112, 44, 32, 37, 114, 98, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t sub_buf[32] = { 115, 117, 98, 113, 32, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(sub_buf, 6, 10, frame_size);
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, line, 11) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, mov_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n] = 44, 0))));
  (void)(((6 + n + 1 < 0 || (6 + n + 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n + 1] = 32, 0))));
  (void)(((6 + n + 2 < 0 || (6 + n + 2) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n + 2] = 37, 0))));
  (void)(((6 + n + 3 < 0 || (6 + n + 3) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n + 3] = 114, 0))));
  (void)(((6 + n + 4 < 0 || (6 + n + 4) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n + 4] = 115, 0))));
  (void)(((6 + n + 5 < 0 || (6 + n + 5) >= 32 ? (shulang_panic_(1, 0), 0) : ((sub_buf)[6 + n + 5] = 112, 0))));
  return types_append_asm_line(out, sub_buf, 6 + n + 6);
}
int32_t arch_x86_64_emit_epilogue(struct codegen_CodegenOutBuf * out) {
  uint8_t line[64] = { 109, 111, 118, 113, 32, 37, 114, 115, 112, 44, 32, 37, 114, 98, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = 15;
  uint8_t ret_line[8] = { 114, 101, 116, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, line, n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, ret_line, 3);
}
int32_t arch_x86_64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 109, 111, 118, 108, 32, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 6, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n] = 44, 0))));
  (void)(((6 + n + 1 < 0 || (6 + n + 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 1] = 32, 0))));
  (void)(((6 + n + 2 < 0 || (6 + n + 2) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 2] = 37, 0))));
  (void)(((6 + n + 3 < 0 || (6 + n + 3) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 3] = 101, 0))));
  (void)(((6 + n + 4 < 0 || (6 + n + 4) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 4] = 97, 0))));
  (void)(((6 + n + 5 < 0 || (6 + n + 5) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 5] = 120, 0))));
  return types_append_asm_line(out, buf, 6 + n + 6);
}
int32_t arch_x86_64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 109, 111, 118, 108, 32, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 6, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n] = 44, 0))));
  (void)(((6 + n + 1 < 0 || (6 + n + 1) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 1] = 32, 0))));
  (void)(((6 + n + 2 < 0 || (6 + n + 2) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 2] = 37, 0))));
  (void)(((6 + n + 3 < 0 || (6 + n + 3) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 3] = 101, 0))));
  (void)(((6 + n + 4 < 0 || (6 + n + 4) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 4] = 98, 0))));
  (void)(((6 + n + 5 < 0 || (6 + n + 5) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n + 5] = 120, 0))));
  return types_append_asm_line(out, buf, 6 + n + 6);
}
int32_t arch_x86_64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi) {
  uint8_t prefix[8] = { 109, 111, 118, 113, 32, 36, 48, 120 };
  uint8_t buf[40] = { 0 };
  int32_t i = 0;
  while (i < 8) {
    (void)(((i < 0 || (i) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[i] = (i < 0 || (i) >= 8 ? (shulang_panic_(1, 0), (prefix)[0]) : (prefix)[i]), 0))));
    (void)((i = i + 1));
  }
  (void)(((24 < 0 || (24) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[24] = 44, 0))));
  (void)(((25 < 0 || (25) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[25] = 32, 0))));
  (void)(((26 < 0 || (26) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[26] = 37, 0))));
  (void)(((27 < 0 || (27) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[27] = 114, 0))));
  (void)(((28 < 0 || (28) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[28] = 97, 0))));
  (void)(((29 < 0 || (29) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[29] = 120, 0))));
  (void)(({ int32_t __tmp = 0; if (types_format_u32_hex8_to_buf(buf, 8, hi) != 8) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_format_u32_hex8_to_buf(buf, 16, lo) != 8) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 26);
}
int32_t arch_x86_64_emit_add(struct codegen_CodegenOutBuf * out, uint8_t * dst_reg, int32_t dst_len, uint8_t * src_reg, int32_t src_len) {
  uint8_t line[64] = { 97, 100, 100, 113, 32, 37, 114, 97, 120, 44, 32, 37, 114, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = 15;
  return types_append_asm_line(out, line, n);
}
int32_t arch_x86_64_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k) {
  uint8_t names[6][4] = { 0 };
  int32_t idx = k;
  int32_t reg_len = 3;
  uint8_t buf[32] = { 109, 111, 118, 113, 32, 37, 114, 97, 120, 44, 32, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t i = 0;
  while (i < reg_len && i < 4) {
    (void)(((12 + i < 0 || (12 + i) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[12 + i] = (i < 0 || (i) >= 4 ? (shulang_panic_(1, 0), ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (names)[0]) : (names)[idx]))[0]) : ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (names)[0]) : (names)[idx]))[i]), 0))));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 4 || idx == 5) {   (void)((reg_len = 2));
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 12 + i);
}
int32_t arch_x86_64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[80] = { 0 };
  int32_t k = 0;
  while (k < name_len && k < 74) {
    (void)(((5 + k < 0 || (5 + k) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[5 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(((buf)[0] = 99));
  (void)(((1 < 0 || (1) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[1] = 97, 0))));
  (void)(((2 < 0 || (2) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = 108, 0))));
  (void)(((3 < 0 || (3) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = 108, 0))));
  (void)(((4 < 0 || (4) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = 32, 0))));
  return types_append_asm_line(out, buf, 5 + name_len);
}
int32_t arch_x86_64_emit_section_text(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 46, 116, 101, 120, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 5);
}
int32_t arch_x86_64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[80] = { 0 };
  int32_t k = 0;
  while (k < name_len && k < 72) {
    (void)(((7 + k < 0 || (7 + k) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(((buf)[0] = 46));
  (void)(((1 < 0 || (1) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[1] = 103, 0))));
  (void)(((2 < 0 || (2) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = 108, 0))));
  (void)(((3 < 0 || (3) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = 111, 0))));
  (void)(((4 < 0 || (4) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = 98, 0))));
  (void)(((5 < 0 || (5) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = 108, 0))));
  (void)(((6 < 0 || (6) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = 32, 0))));
  return types_append_asm_line(out, buf, 7 + name_len);
}
int32_t arch_x86_64_emit_push_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 112, 117, 115, 104, 113, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_x86_64_emit_pop_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 112, 111, 112, 113, 32, 37, 114, 98, 120, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_x86_64_emit_pop_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 112, 111, 112, 113, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_x86_64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 97, 100, 100, 113, 32, 37, 114, 98, 120, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out) {
  uint8_t sub_line[32] = { 115, 117, 98, 113, 32, 37, 114, 97, 120, 44, 32, 37, 114, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t mov_line[32] = { 109, 111, 118, 113, 32, 37, 114, 98, 120, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, sub_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, mov_line, 15);
}
int32_t arch_x86_64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 105, 109, 117, 108, 113, 32, 37, 114, 98, 120, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 16);
}
int32_t arch_x86_64_emit_cltd(struct codegen_CodegenOutBuf * out) {
  uint8_t line[8] = { 99, 108, 116, 100, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 4);
}
int32_t arch_x86_64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 105, 100, 105, 118, 108, 32, 37, 101, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_x86_64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 109, 111, 118, 108, 32, 37, 101, 100, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_neg_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 110, 101, 103, 108, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_x86_64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line1[16] = { 115, 101, 116, 122, 32, 37, 97, 108, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t line2[24] = { 109, 111, 118, 122, 98, 108, 32, 37, 97, 108, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, line1, 8) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, line2, 16);
}
int32_t arch_x86_64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 109, 111, 118, 113, 32, 37, 114, 97, 120, 44, 32, 37, 114, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 109, 111, 118, 113, 32, 37, 114, 98, 120, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 116, 101, 115, 116, 32, 37, 101, 97, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t cmp_line[32] = { 99, 109, 112, 108, 32, 37, 101, 97, 120, 44, 32, 37, 101, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, cmp_line, 15);
}
int32_t arch_x86_64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc) {
  uint8_t cmp_line[32] = { 99, 109, 112, 108, 32, 37, 101, 97, 120, 44, 32, 37, 101, 98, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t setcc_names[6][8] = { 0 };
  int32_t idx = cc;
  int32_t len = 4;
  uint8_t buf[24] = { 115, 101, 116, 0, 0, 0, 32, 37, 97, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  uint8_t line2[24] = { 109, 111, 118, 122, 98, 108, 32, 37, 97, 108, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0 };
  while (k < len && k < 8) {
    (void)(((k < 0 || (k) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[k] = (k < 0 || (k) >= 8 ? (shulang_panic_(1, 0), ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (setcc_names)[0]) : (setcc_names)[idx]))[0]) : ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (setcc_names)[0]) : (setcc_names)[idx]))[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, cmp_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 1 || idx == 3 || idx == 5) {   (void)((len = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(((k < 0 || (k) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[k] = 32, 0))));
  (void)(((k + 1 < 0 || (k + 1) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[k + 1] = 37, 0))));
  (void)(((k + 2 < 0 || (k + 2) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[k + 2] = 97, 0))));
  (void)(((k + 3 < 0 || (k + 3) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[k + 3] = 108, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, buf, k + 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, line2, 16);
}
int32_t arch_x86_64_emit_not_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 110, 111, 116, 108, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_x86_64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 97, 110, 100, 108, 32, 37, 101, 98, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 111, 114, 108, 32, 37, 101, 98, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_x86_64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 120, 111, 114, 108, 32, 37, 101, 98, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 109, 111, 118, 108, 32, 37, 101, 98, 120, 44, 32, 37, 101, 99, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_x86_64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 115, 97, 108, 108, 32, 37, 99, 108, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_x86_64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 115, 104, 114, 108, 32, 37, 99, 108, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_x86_64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 115, 97, 114, 108, 32, 37, 99, 108, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_x86_64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 109, 111, 118, 113, 32, 37, 114, 97, 120, 44, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 12, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((12 + n < 0 || (12 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[12 + n] = 40, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[13 + n] = 37, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[14 + n] = 114, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 98, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 112, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[17 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 18 + n);
}
int32_t arch_x86_64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 109, 111, 118, 113, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 6, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n] = 40, 0))));
  (void)(((7 + n < 0 || (7 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + n] = 37, 0))));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 114, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 98, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 112, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[12 + n] = 44, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[13 + n] = 32, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[14 + n] = 37, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 114, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 97, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[17 + n] = 120, 0))));
  return types_append_asm_line(out, buf, 18 + n);
}
int32_t arch_x86_64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 108, 101, 97, 113, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 6, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n] = 40, 0))));
  (void)(((7 + n < 0 || (7 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + n] = 37, 0))));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 114, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 98, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 112, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[12 + n] = 44, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[13 + n] = 32, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[14 + n] = 37, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 114, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 97, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[17 + n] = 120, 0))));
  return types_append_asm_line(out, buf, 18 + n);
}
int32_t arch_x86_64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out) {
  uint8_t line[48] = { 108, 101, 97, 113, 32, 40, 37, 114, 97, 120, 44, 37, 114, 98, 120, 44, 52, 41, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 24);
}
int32_t arch_x86_64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 109, 111, 118, 108, 32, 40, 37, 114, 97, 120, 41, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 17);
}
int32_t arch_x86_64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm) {
  uint8_t buf[32] = { 97, 100, 100, 113, 32, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 6, 12, imm);
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((6 + n < 0 || (6 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[6 + n] = 44, 0))));
  (void)(((7 + n < 0 || (7 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + n] = 32, 0))));
  (void)(((8 + n < 0 || (8 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 37, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 114, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 97, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 120, 0))));
  return types_append_asm_line(out, buf, 12 + n);
}
int32_t arch_x86_64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 109, 111, 118, 113, 32, 40, 37, 114, 97, 120, 41, 44, 32, 37, 114, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 17);
}
int32_t arch_x86_64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size) {
  uint8_t buf[48] = { 109, 111, 118, 108, 32, 37, 101, 97, 120, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 11, 12, offset);
  (void)(({ int32_t __tmp = 0; if (store_size == 8) {   (void)(((3 < 0 || (3) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = 113, 0))));
  (void)(((6 < 0 || (6) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = 114, 0))));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 40, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[12 + n] = 37, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[13 + n] = 114, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[14 + n] = 98, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 120, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 17 + n);
}
int32_t arch_x86_64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t test_line[32] = { 116, 101, 115, 116, 32, 37, 101, 97, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t buf[40] = { 106, 101, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 32) {
    (void)(((3 + k < 0 || (3 + k) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[3 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, test_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 3 + label_len);
}
int32_t arch_x86_64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t test_line[32] = { 116, 101, 115, 116, 32, 37, 101, 97, 120, 44, 32, 37, 101, 97, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t buf[40] = { 106, 110, 101, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 32) {
    (void)(((4 + k < 0 || (4 + k) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[4 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, test_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 4 + label_len);
}
int32_t arch_x86_64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[40] = { 106, 109, 112, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 32) {
    (void)(((4 + k < 0 || (4 + k) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[4 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 4 + label_len);
}
int32_t arch_x86_64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  int32_t i = 0;
  while (i < name_len && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[i]), 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   uint8_t colon[1] = { 58 };
  (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (colon)[0], 0))));
  (void)(((out)->len = (out)->len + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   uint8_t nl[1] = { 10 };
  (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (nl)[0], 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
extern int32_t types_append_asm_line(struct codegen_CodegenOutBuf *, uint8_t *, int32_t);
extern int32_t types_format_i32_to_buf(uint8_t *, int32_t, int32_t, int32_t);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena *, int32_t);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena *, int32_t);
int32_t arch_arm64_emit_section_text(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_arm64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_arm64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size);
int32_t arch_arm64_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_size);
int32_t arch_arm64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_arm64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_arm64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi);
int32_t arch_arm64_emit_neg_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc);
int32_t arch_arm64_emit_not_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_push_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_pop_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_pop_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_cltd(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_rem_w0_w1(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_arm64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_arm64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_arm64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size);
int32_t arch_arm64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm);
int32_t arch_arm64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i);
int32_t arch_arm64_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n);
int32_t arch_arm64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_arm64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_get_return_lit_ref(struct ast_ASTArena * arena, struct ast_Func * f);
int32_t arch_arm64_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out);
int32_t arch_arm64_emit_section_text(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 46, 116, 101, 120, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 5);
}
int32_t arch_arm64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[96] = { 46, 103, 108, 111, 98, 108, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < name_len && k < 88) {
    (void)(((7 + k < 0 || (7 + k) >= 96 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 7 + name_len);
}
int32_t arch_arm64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  int32_t i = 0;
  while (i < name_len && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[i]), 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = 58, 0))));
  (void)(((out)->len = (out)->len + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = 10, 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t arch_arm64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size) {
  uint8_t stp_line[32] = { 115, 116, 112, 32, 120, 50, 57, 44, 32, 120, 51, 48, 44, 32, 91, 115, 112, 44, 32, 35, 45, 49, 54, 93, 33, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t mov_line[20] = { 109, 111, 118, 32, 120, 50, 57, 44, 32, 115, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t sub_buf[40] = { 115, 117, 98, 32, 115, 112, 44, 32, 115, 112, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(sub_buf, 13, 12, frame_size);
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, stp_line, 25) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, mov_line, 11) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, sub_buf, 13 + n);
}
int32_t arch_arm64_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_size) {
  uint8_t add_buf[40] = { 97, 100, 100, 32, 115, 112, 44, 32, 115, 112, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(add_buf, 13, 12, frame_size);
  uint8_t ldp_line[32] = { 108, 100, 112, 32, 120, 50, 57, 44, 32, 120, 51, 48, 44, 32, 91, 115, 112, 93, 44, 32, 35, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t ret_line[8] = { 114, 101, 116, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, add_buf, 13 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, ldp_line, 23) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, ret_line, 3);
}
int32_t arch_arm64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 109, 111, 118, 32, 119, 48, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 9, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 9 + n);
}
int32_t arch_arm64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 109, 111, 118, 32, 119, 49, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 9, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 9 + n);
}
int32_t arch_arm64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi) {
  int32_t lo0 = lo & 65535;
  int32_t lo1 = lo >> 16 & 65535;
  int32_t hi0 = hi & 65535;
  int32_t hi1 = hi >> 16 & 65535;
  uint8_t buf[40] = { 109, 111, 118, 122, 32, 120, 48, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 10, 6, lo0);
  uint8_t movk[32] = { 109, 111, 118, 107, 32, 120, 48, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, buf, 10 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((n = types_format_i32_to_buf(movk, 10, 6, lo1)));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((10 + n < 0 || (10 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[10 + n] = 44, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[11 + n] = 32, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[12 + n] = 76, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[13 + n] = 83, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[14 + n] = 76, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[15 + n] = 32, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[16 + n] = 35, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[17 + n] = 49, 0))));
  (void)(((18 + n < 0 || (18 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[18 + n] = 54, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, movk, 19 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((n = types_format_i32_to_buf(movk, 10, 6, hi0)));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((10 + n < 0 || (10 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[10 + n] = 44, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[11 + n] = 32, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[12 + n] = 76, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[13 + n] = 83, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[14 + n] = 76, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[15 + n] = 32, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[16 + n] = 35, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[17 + n] = 51, 0))));
  (void)(((18 + n < 0 || (18 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[18 + n] = 50, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, movk, 19 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((n = types_format_i32_to_buf(movk, 10, 6, hi1)));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((10 + n < 0 || (10 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[10 + n] = 44, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[11 + n] = 32, 0))));
  (void)(((12 + n < 0 || (12 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[12 + n] = 76, 0))));
  (void)(((13 + n < 0 || (13 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[13 + n] = 83, 0))));
  (void)(((14 + n < 0 || (14 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[14 + n] = 76, 0))));
  (void)(((15 + n < 0 || (15 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[15 + n] = 32, 0))));
  (void)(((16 + n < 0 || (16 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[16 + n] = 35, 0))));
  (void)(((17 + n < 0 || (17 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[17 + n] = 52, 0))));
  (void)(((18 + n < 0 || (18 + n) >= 32 ? (shulang_panic_(1, 0), 0) : ((movk)[18 + n] = 56, 0))));
  return types_append_asm_line(out, movk, 19 + n);
}
int32_t arch_arm64_emit_neg_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 110, 101, 103, 32, 119, 48, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_arm64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 99, 109, 112, 32, 119, 48, 44, 32, 35, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_arm64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 99, 115, 101, 116, 32, 119, 48, 44, 32, 101, 113, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 11);
}
int32_t arch_arm64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t cmp_line[16] = { 99, 109, 112, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, cmp_line, 10);
}
int32_t arch_arm64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc) {
  uint8_t cmp_line[16] = { 99, 109, 112, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0 };
  uint8_t cond_names[6][4] = { 0 };
  int32_t idx = cc;
  uint8_t buf[24] = { 99, 115, 101, 116, 32, 119, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < 2 && k < 4) {
    (void)(((9 + k < 0 || (9 + k) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + k] = (k < 0 || (k) >= 4 ? (shulang_panic_(1, 0), ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (cond_names)[0]) : (cond_names)[idx]))[0]) : ((idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (cond_names)[0]) : (cond_names)[idx]))[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, cmp_line, 10) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 9 + k);
}
int32_t arch_arm64_emit_not_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 109, 118, 110, 32, 119, 48, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_arm64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 97, 110, 100, 32, 119, 48, 44, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 111, 114, 114, 32, 119, 48, 44, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 101, 111, 114, 32, 119, 48, 44, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 108, 115, 108, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 108, 115, 114, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 97, 115, 114, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_push_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 115, 116, 114, 32, 119, 48, 44, 32, 91, 115, 112, 44, 32, 35, 45, 49, 54, 93, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 19);
}
int32_t arch_arm64_emit_pop_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 108, 100, 114, 32, 119, 49, 44, 32, 91, 115, 112, 93, 44, 32, 35, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 17);
}
int32_t arch_arm64_emit_pop_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 108, 100, 114, 32, 119, 48, 44, 32, 91, 115, 112, 93, 44, 32, 35, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 17);
}
int32_t arch_arm64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 97, 100, 100, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 117, 98, 32, 119, 48, 44, 32, 119, 49, 44, 32, 119, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 109, 117, 108, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_arm64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 109, 111, 118, 32, 120, 49, 44, 32, 120, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_arm64_emit_cltd(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_arm64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 100, 105, 118, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 15);
}
int32_t arch_arm64_emit_rem_w0_w1(struct codegen_CodegenOutBuf * out) {
  uint8_t s1[32] = { 115, 116, 114, 32, 119, 48, 44, 32, 91, 115, 112, 44, 32, 35, 45, 49, 54, 93, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t s2[24] = { 115, 100, 105, 118, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t s3[32] = { 108, 100, 114, 32, 119, 50, 44, 32, 91, 115, 112, 93, 44, 32, 35, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t msub_line[32] = { 109, 115, 117, 98, 32, 119, 48, 44, 32, 119, 48, 44, 32, 119, 49, 44, 32, 119, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, s1, 19) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, s2, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, s3, 17) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, msub_line, 19);
}
int32_t arch_arm64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_arm64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 115, 117, 98, 32, 120, 48, 44, 32, 120, 50, 57, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 15, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 15 + n);
}
int32_t arch_arm64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 108, 100, 114, 32, 119, 48, 44, 32, 91, 120, 50, 57, 44, 32, 35, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 16, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 93, 0))));
  return types_append_asm_line(out, buf, 17 + n);
}
int32_t arch_arm64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 115, 116, 114, 32, 119, 48, 44, 32, 91, 120, 50, 57, 44, 32, 35, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 16, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((16 + n < 0 || (16 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[16 + n] = 93, 0))));
  return types_append_asm_line(out, buf, 17 + n);
}
int32_t arch_arm64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size) {
  uint8_t buf[48] = { 115, 116, 114, 32, 120, 48, 44, 32, 91, 120, 49, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 15, 12, offset);
  (void)(({ int32_t __tmp = 0; if (store_size == 4) {   uint8_t buf[48] = { 115, 116, 114, 32, 119, 48, 44, 32, 91, 120, 49, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 15, 12, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 93, 0))));
  return types_append_asm_line(out, buf, 16 + n);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((15 + n < 0 || (15 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 93, 0))));
  return types_append_asm_line(out, buf, 16 + n);
}
int32_t arch_arm64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 109, 111, 118, 32, 120, 48, 44, 32, 120, 49, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_arm64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out) {
  uint8_t line[32] = { 97, 100, 100, 32, 120, 48, 44, 32, 120, 48, 44, 32, 119, 49, 44, 32, 117, 120, 116, 119, 32, 35, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 23);
}
int32_t arch_arm64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 108, 100, 114, 32, 119, 48, 44, 32, 91, 120, 48, 93, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 12);
}
int32_t arch_arm64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm) {
  uint8_t buf[40] = { 97, 100, 100, 32, 120, 48, 44, 32, 120, 48, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 13, 12, imm);
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 13 + n);
}
int32_t arch_arm64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 108, 100, 114, 32, 120, 48, 44, 32, 91, 120, 48, 93, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 12);
}
int32_t arch_arm64_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i) {
  int32_t idx = i;
  uint8_t reg[6] = { 48, 49, 50, 51, 52, 53 };
  uint8_t buf[40] = { 108, 100, 114, 32, 119, 0, 44, 32, 91, 115, 112, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t off = idx * 16;
  int32_t n = types_format_i32_to_buf(buf, 15, 8, off);
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(((5 < 0 || (5) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = (idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (reg)[0]) : (reg)[idx]), 0))));
  (void)(({ int32_t __tmp = 0; if (idx == 0) {   return types_append_asm_line(out, buf, 12);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((12 < 0 || (12) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[12] = 44, 0))));
  (void)(((13 < 0 || (13) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[13] = 32, 0))));
  (void)(((14 < 0 || (14) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[14] = 35, 0))));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((15 + n < 0 || (15 + n) >= 40 ? (shulang_panic_(1, 0), 0) : ((buf)[15 + n] = 93, 0))));
  return types_append_asm_line(out, buf, 16 + n);
}
int32_t arch_arm64_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n) {
  uint8_t buf[32] = { 97, 100, 100, 32, 115, 112, 44, 32, 115, 112, 44, 32, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = types_format_i32_to_buf(buf, 13, 8, n);
  (void)(({ int32_t __tmp = 0; if (k < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 13 + k);
}
int32_t arch_arm64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[80] = { 98, 108, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < name_len && k < 76) {
    (void)(((3 + k < 0 || (3 + k) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[3 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 3 + name_len);
}
int32_t arch_arm64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 99, 98, 122, 32, 119, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 64) {
    (void)(((8 + k < 0 || (8 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 8 + label_len);
}
int32_t arch_arm64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 99, 98, 110, 122, 32, 119, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 62) {
    (void)(((9 + k < 0 || (9 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 9 + label_len);
}
int32_t arch_arm64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 98, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 70) {
    (void)(((2 + k < 0 || (2 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[2 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 2 + label_len);
}
int32_t arch_arm64_get_return_lit_ref(struct ast_ASTArena * arena, struct ast_Func * f) {
  struct ast_Block block = ast_ast_arena_block_get(arena, (f)->body_ref);
  struct ast_Expr e = ast_ast_arena_expr_get(arena, (block).final_expr_ref);
  (void)(({ int32_t __tmp = 0; if ((f)->body_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((block).final_expr_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LIT || (e).kind == ast_ExprKind_EXPR_BOOL_LIT) {   return (block).final_expr_ref;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN && (e).unary_operand_ref != 0) {   struct ast_Expr inner = ast_ast_arena_expr_get(arena, (e).unary_operand_ref);
  __tmp = ({ int32_t __tmp = 0; if ((inner).kind == ast_ExprKind_EXPR_LIT || (inner).kind == ast_ExprKind_EXPR_BOOL_LIT) {   return (e).unary_operand_ref;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_arm64_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out) {
  int32_t i = 0;
  while (i < (module)->num_funcs && i < 256) {
    struct ast_Func f = (i < 0 || (i) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[i]);
    (void)(({ int32_t __tmp = 0; if ((f).is_extern != 0) {   (void)((i = i + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 0 && arch_arm64_emit_section_text(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_globl(out, (f).name, (f).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_label(out, (f).name, (f).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t frame_sz = 0;
    (void)(({ int32_t __tmp = 0; if ((f).body_ref != 0) {   struct ast_Block blk = ast_ast_arena_block_get(arena, (f).body_ref);
  int32_t n = (blk).num_consts + (blk).num_lets;
  __tmp = ({ int32_t __tmp = 0; if (n > 0) {   (void)((frame_sz = n * 8));
  __tmp = ({ int32_t __tmp = 0; if ((16 == 0 ? (shulang_panic_(1, 0), frame_sz) : (frame_sz % 16)) != 0) {   (void)((frame_sz = frame_sz + 16 - (16 == 0 ? (shulang_panic_(1, 0), frame_sz) : (frame_sz % 16))));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_prologue(out, frame_sz) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t ret_ref = arch_arm64_get_return_lit_ref(arena, (&(f)));
    (void)(({ int32_t __tmp = 0; if (ret_ref == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Expr ret_expr = ast_ast_arena_expr_get(arena, ret_ref);
    (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_ret_imm32(out, (ret_expr).int_val) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_epilogue(out, frame_sz) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
extern int32_t types_append_asm_line(struct codegen_CodegenOutBuf *, uint8_t *, int32_t);
extern int32_t types_format_i32_to_buf(uint8_t *, int32_t, int32_t, int32_t);
int32_t arch_riscv64_emit_section_text(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_riscv64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_riscv64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size);
int32_t arch_riscv64_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_size);
int32_t arch_riscv64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_riscv64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi);
int32_t arch_riscv64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32);
int32_t arch_riscv64_emit_neg_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_push_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_pop_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_pop_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_cltd(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_test_setz(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc);
int32_t arch_riscv64_emit_not_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_riscv64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_riscv64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset);
int32_t arch_riscv64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm);
int32_t arch_riscv64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size);
int32_t arch_riscv64_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k);
int32_t arch_riscv64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len);
int32_t arch_riscv64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i);
int32_t arch_riscv64_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n);
int32_t arch_riscv64_emit_rem_w0_w1(struct codegen_CodegenOutBuf * out);
int32_t arch_riscv64_emit_section_text(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 46, 116, 101, 120, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 5);
}
int32_t arch_riscv64_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[96] = { 46, 103, 108, 111, 98, 108, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < name_len && k < 88) {
    (void)(((7 + k < 0 || (7 + k) >= 96 ? (shulang_panic_(1, 0), 0) : ((buf)[7 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 7 + name_len);
}
int32_t arch_riscv64_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  int32_t i = 0;
  while (i < name_len && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[i]), 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = 58, 0))));
  (void)(((out)->len = (out)->len + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((out)->len < 262144) {   (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = 10, 0))));
  (void)(((out)->len = (out)->len + 1));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t arch_riscv64_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_size) {
  uint8_t addi_buf[48] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(addi_buf, 14, 12, frame_size);
  int32_t off_ra = frame_size - 8;
  uint8_t sd_ra[48] = { 115, 100, 32, 114, 97, 44, 32, 0, 0, 0, 0, 0, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t no = types_format_i32_to_buf(sd_ra, 7, 8, off_ra);
  int32_t off_s0 = frame_size - 16;
  uint8_t sd_s0[48] = { 115, 100, 32, 115, 48, 44, 32, 0, 0, 0, 0, 0, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t addi_s0[48] = { 97, 100, 100, 105, 32, 115, 48, 44, 32, 115, 112, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (frame_size < 16) {   int32_t sz = 16;
  uint8_t addi_buf[48] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(addi_buf, 14, 8, sz);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, addi_buf, 14 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t sd_buf[48] = { 115, 100, 32, 114, 97, 44, 32, 56, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, sd_buf, 12);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, addi_buf, 14 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (no < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((7 + no < 0 || (7 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_ra)[7 + no] = 40, 0))));
  (void)(((8 + no < 0 || (8 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_ra)[8 + no] = 115, 0))));
  (void)(((9 + no < 0 || (9 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_ra)[9 + no] = 112, 0))));
  (void)(((10 + no < 0 || (10 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_ra)[10 + no] = 41, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, sd_ra, 11 + no) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((no = types_format_i32_to_buf(sd_s0, 7, 8, off_s0)));
  (void)(({ int32_t __tmp = 0; if (no < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((7 + no < 0 || (7 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_s0)[7 + no] = 40, 0))));
  (void)(((8 + no < 0 || (8 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_s0)[8 + no] = 115, 0))));
  (void)(((9 + no < 0 || (9 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_s0)[9 + no] = 112, 0))));
  (void)(((10 + no < 0 || (10 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((sd_s0)[10 + no] = 41, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, sd_s0, 11 + no) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((no = types_format_i32_to_buf(addi_s0, 13, 12, frame_size)));
  (void)(({ int32_t __tmp = 0; if (no < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, addi_s0, 13 + no);
}
int32_t arch_riscv64_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_size) {
  uint8_t ret_line[8] = { 114, 101, 116, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (frame_size < 16) {   uint8_t ld_line[16] = { 108, 100, 32, 114, 97, 44, 32, 56, 40, 115, 112, 41, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, ld_line, 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t addi_line[24] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  __tmp = ({ int32_t __tmp = 0; if (types_append_asm_line(out, addi_line, 15) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   int32_t off_s0 = frame_size - 16;
  uint8_t ld_s0[48] = { 108, 100, 32, 115, 48, 44, 32, 0, 0, 0, 0, 0, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t no = types_format_i32_to_buf(ld_s0, 7, 8, off_s0);
  (void)(({ int32_t __tmp = 0; if (no < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((7 + no < 0 || (7 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_s0)[7 + no] = 40, 0))));
  (void)(((8 + no < 0 || (8 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_s0)[8 + no] = 115, 0))));
  (void)(((9 + no < 0 || (9 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_s0)[9 + no] = 112, 0))));
  (void)(((10 + no < 0 || (10 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_s0)[10 + no] = 41, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, ld_s0, 11 + no) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t off_ra = frame_size - 8;
  uint8_t ld_ra[48] = { 108, 100, 32, 114, 97, 44, 32, 0, 0, 0, 0, 0, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)((no = types_format_i32_to_buf(ld_ra, 7, 8, off_ra)));
  (void)(({ int32_t __tmp = 0; if (no < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((7 + no < 0 || (7 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_ra)[7 + no] = 40, 0))));
  (void)(((8 + no < 0 || (8 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_ra)[8 + no] = 115, 0))));
  (void)(((9 + no < 0 || (9 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_ra)[9 + no] = 112, 0))));
  (void)(((10 + no < 0 || (10 + no) >= 48 ? (shulang_panic_(1, 0), 0) : ((ld_ra)[10 + no] = 41, 0))));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, ld_ra, 11 + no) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t addi_buf[48] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t na = types_format_i32_to_buf(addi_buf, 13, 12, frame_size);
  (void)(({ int32_t __tmp = 0; if (na < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (types_append_asm_line(out, addi_buf, 13 + na) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  return types_append_asm_line(out, ret_line, 3);
}
int32_t arch_riscv64_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 108, 105, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 7, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 7 + n);
}
int32_t arch_riscv64_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi) {
  uint8_t buf[32] = { 108, 105, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 7, 12, lo);
  uint8_t slli_line[24] = { 115, 108, 108, 105, 32, 97, 48, 44, 32, 97, 48, 44, 32, 51, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t srli_line[24] = { 115, 114, 108, 105, 32, 97, 48, 44, 32, 97, 48, 44, 32, 51, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t hi20 = hi >> 12 & 1048575;
  int32_t hi12 = hi & 4095;
  uint8_t lui_buf[32] = { 108, 117, 105, 32, 116, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t addi_buf[32] = { 97, 100, 100, 105, 32, 116, 48, 44, 32, 116, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t slli_t0[24] = { 115, 108, 108, 105, 32, 116, 48, 44, 32, 116, 48, 44, 32, 51, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t add_line[16] = { 97, 100, 100, 32, 97, 48, 44, 32, 97, 48, 44, 32, 116, 48, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, buf, 7 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, slli_line, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, srli_line, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi12 >= 2048) {   (void)((hi20 = hi20 + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)((n = types_format_i32_to_buf(lui_buf, 8, 10, hi20)));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, lui_buf, 8 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((n = types_format_i32_to_buf(addi_buf, 13, 10, hi12)));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, addi_buf, 13 + n) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, slli_t0, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, add_line, 15);
}
int32_t arch_riscv64_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm32) {
  uint8_t buf[32] = { 108, 105, 32, 97, 49, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 7, 12, imm32);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 7 + n);
}
int32_t arch_riscv64_emit_neg_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 110, 101, 103, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_riscv64_emit_test_eax_eax(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_riscv64_emit_setz_movzbl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 115, 101, 113, 122, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 11);
}
int32_t arch_riscv64_emit_push_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t l1[32] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 45, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t l2[20] = { 115, 100, 32, 97, 48, 44, 32, 48, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, l1, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, l2, 12);
}
int32_t arch_riscv64_emit_pop_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t l1[20] = { 108, 100, 32, 97, 49, 44, 32, 48, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t l2[32] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, l1, 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, l2, 15);
}
int32_t arch_riscv64_emit_pop_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t l1[20] = { 108, 100, 32, 97, 48, 44, 32, 48, 40, 115, 112, 41, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t l2[32] = { 97, 100, 100, 105, 32, 115, 112, 44, 32, 115, 112, 44, 32, 49, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, l1, 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, l2, 15);
}
int32_t arch_riscv64_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 97, 100, 100, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 117, 98, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 109, 117, 108, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 109, 118, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_riscv64_emit_cltd(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_riscv64_emit_idiv_rbx(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 100, 105, 118, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_mov_edx_to_eax(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_riscv64_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[16] = { 109, 118, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 9);
}
int32_t arch_riscv64_emit_test_setz(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 115, 101, 113, 122, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 11);
}
int32_t arch_riscv64_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t sub_line[24] = { 115, 117, 98, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, sub_line, 14);
}
int32_t arch_riscv64_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc) {
  int32_t idx = cc;
  uint8_t slt_line[24] = { 115, 108, 116, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t xori_line[24] = { 120, 111, 114, 105, 32, 97, 48, 44, 32, 97, 48, 44, 32, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 0) {   uint8_t sub_line[24] = { 115, 117, 98, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, sub_line, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t seqz_line[20] = { 115, 101, 113, 122, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, seqz_line, 11);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 1) {   uint8_t sub_line[24] = { 115, 117, 98, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, sub_line, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t snez_line[20] = { 115, 110, 101, 122, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, snez_line, 11);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 2) {   uint8_t slt_line[24] = { 115, 108, 116, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, slt_line, 14);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 3) {   uint8_t slt_line[24] = { 115, 108, 116, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, slt_line, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t xori_line[24] = { 120, 111, 114, 105, 32, 97, 48, 44, 32, 97, 48, 44, 32, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, xori_line, 14);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 4) {   uint8_t slt_line[24] = { 115, 108, 116, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, slt_line, 14);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, slt_line, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, xori_line, 14);
}
int32_t arch_riscv64_emit_not_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 110, 111, 116, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 10);
}
int32_t arch_riscv64_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 97, 110, 100, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 111, 114, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 120, 111, 114, 32, 97, 48, 44, 32, 97, 49, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out) {
  return 0;
}
int32_t arch_riscv64_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 108, 108, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 114, 108, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 115, 114, 97, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
int32_t arch_riscv64_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 115, 100, 32, 97, 48, 44, 32, 45, 0, 0, 0, 0, 40, 115, 48, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 8, 10, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 40, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 115, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 48, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 12 + n);
}
int32_t arch_riscv64_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 108, 100, 32, 97, 48, 44, 32, 45, 0, 0, 0, 0, 40, 115, 48, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 8, 10, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 40, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 115, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 48, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 12 + n);
}
int32_t arch_riscv64_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t offset) {
  uint8_t buf[48] = { 97, 100, 100, 105, 32, 97, 48, 44, 32, 115, 48, 44, 32, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 14, 10, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 14 + n);
}
int32_t arch_riscv64_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out) {
  uint8_t slli_line[24] = { 115, 108, 108, 105, 32, 97, 49, 44, 32, 97, 49, 44, 32, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t add_line[24] = { 97, 100, 100, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (types_append_asm_line(out, slli_line, 14) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, add_line, 14);
}
int32_t arch_riscv64_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 108, 119, 32, 97, 48, 44, 32, 48, 40, 97, 48, 41, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 12);
}
int32_t arch_riscv64_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm) {
  uint8_t buf[40] = { 97, 100, 100, 105, 32, 97, 48, 44, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 13, 12, imm);
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return types_append_asm_line(out, buf, 13 + n);
}
int32_t arch_riscv64_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t line[20] = { 108, 100, 32, 97, 48, 44, 32, 48, 40, 97, 48, 41, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 12);
}
int32_t arch_riscv64_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size) {
  uint8_t buf[48] = { 115, 100, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 40, 97, 49, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 8, 10, offset);
  (void)(({ int32_t __tmp = 0; if (store_size == 4) {   uint8_t buf[48] = { 115, 119, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 40, 97, 49, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t n = types_format_i32_to_buf(buf, 8, 10, offset);
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 40, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 97, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 49, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 12 + n);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((8 + n < 0 || (8 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + n] = 40, 0))));
  (void)(((9 + n < 0 || (9 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + n] = 97, 0))));
  (void)(((10 + n < 0 || (10 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + n] = 49, 0))));
  (void)(((11 + n < 0 || (11 + n) >= 48 ? (shulang_panic_(1, 0), 0) : ((buf)[11 + n] = 41, 0))));
  return types_append_asm_line(out, buf, 12 + n);
}
int32_t arch_riscv64_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k) {
  int32_t idx = k;
  uint8_t buf[24] = { 109, 118, 32, 97, 48, 44, 32, 97, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t digits[6] = { 48, 49, 50, 51, 52, 53 };
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(((4 < 0 || (4) >= 24 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = (idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (digits)[0]) : (digits)[idx]), 0))));
  return types_append_asm_line(out, buf, 9);
}
int32_t arch_riscv64_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len) {
  uint8_t buf[80] = { 106, 97, 108, 32, 114, 97, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < name_len && k < 72) {
    (void)(((8 + k < 0 || (8 + k) >= 80 ? (shulang_panic_(1, 0), 0) : ((buf)[8 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 8 + name_len);
}
int32_t arch_riscv64_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 98, 101, 113, 122, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 62) {
    (void)(((9 + k < 0 || (9 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[9 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 9 + label_len);
}
int32_t arch_riscv64_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 98, 110, 101, 122, 32, 97, 48, 44, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 61) {
    (void)(((10 + k < 0 || (10 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[10 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 10 + label_len);
}
int32_t arch_riscv64_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len) {
  uint8_t buf[72] = { 106, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t k = 0;
  while (k < label_len && k < 68) {
    (void)(((2 + k < 0 || (2 + k) >= 72 ? (shulang_panic_(1, 0), 0) : ((buf)[2 + k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (label)[0]) : (label)[k]), 0))));
    (void)((k = k + 1));
  }
  return types_append_asm_line(out, buf, 2 + label_len);
}
int32_t arch_riscv64_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i) {
  return 0;
}
int32_t arch_riscv64_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n) {
  return 0;
}
int32_t arch_riscv64_emit_rem_w0_w1(struct codegen_CodegenOutBuf * out) {
  uint8_t line[24] = { 114, 101, 109, 32, 97, 48, 44, 32, 97, 48, 44, 32, 97, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return types_append_asm_line(out, line, 14);
}
struct platform_elf_ElfCodeBuf { uint8_t data[32768]; int32_t len; };
struct platform_elf_ElfLabelEntry { uint8_t name[64]; int32_t name_len; int32_t offset; };
struct platform_elf_ElfPatchEntry { int32_t rel32_offset; uint8_t name[64]; int32_t name_len; int32_t patch_imm_bits; };
struct platform_elf_ElfRelocEntry { int32_t offset; uint8_t name[64]; int32_t name_len; };
struct platform_elf_ElfSymEntry { uint8_t name[64]; int32_t name_len; int32_t offset; };
struct platform_elf_ElfCodegenCtx { struct platform_elf_ElfCodeBuf code; struct platform_elf_ElfLabelEntry labels[64]; int32_t num_labels; struct platform_elf_ElfPatchEntry patches[128]; int32_t num_patches; struct platform_elf_ElfRelocEntry relocs[32]; int32_t num_relocs; struct platform_elf_ElfSymEntry syms[16]; int32_t num_syms; int32_t e_machine; int32_t reloc_type_r_pc32; int32_t current_frame_size; };
uint8_t platform_elf_elf_to_u8(int32_t val);
void platform_elf_elf_ctx_reset(struct platform_elf_ElfCodegenCtx * ctx);
int32_t platform_elf_append_elf_bytes(struct platform_elf_ElfCodegenCtx * ctx, uint8_t * ptr, int32_t n);
int32_t platform_elf_elf_add_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len);
int32_t platform_elf_elf_add_patch(struct platform_elf_ElfCodegenCtx * ctx, int32_t rel32_offset, uint8_t name[64], int32_t name_len);
int32_t platform_elf_elf_add_patch_with_bits(struct platform_elf_ElfCodegenCtx * ctx, int32_t rel32_offset, uint8_t name[64], int32_t name_len, int32_t imm_bits);
int32_t platform_elf_elf_add_reloc(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, uint8_t name[64], int32_t name_len);
int32_t platform_elf_elf_add_sym(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t offset);
int32_t platform_elf_elf_name_eq(uint8_t a[64], int32_t a_len, uint8_t b[64], int32_t b_len);
int32_t platform_elf_elf_resolve_patches(struct platform_elf_ElfCodegenCtx * ctx);
int32_t platform_elf_elf_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n);
int32_t platform_elf_write_elf_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out);
uint8_t platform_elf_elf_to_u8(int32_t val) {
  uint8_t tab[256] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255 };
  int32_t lo = val & 255;
  return (lo < 0 || (lo) >= 256 ? (shulang_panic_(1, 0), (tab)[0]) : (tab)[lo]);
}
void platform_elf_elf_ctx_reset(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)((((ctx)->code).len = 0));
  (void)(((ctx)->num_labels = 0));
  (void)(((ctx)->num_patches = 0));
  (void)(((ctx)->num_relocs = 0));
  (void)(((ctx)->num_syms = 0));
}
int32_t platform_elf_append_elf_bytes(struct platform_elf_ElfCodegenCtx * ctx, uint8_t * ptr, int32_t n) {
  int32_t i = 0;
  while (i < n) {
    (void)(((((ctx)->code).len < 0 || (((ctx)->code).len) >= 32768 ? (shulang_panic_(1, 0), 0) : ((((ctx)->code).data)[((ctx)->code).len] = (ptr)[i], 0))));
    (void)((((ctx)->code).len = ((ctx)->code).len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (n < 0 || ((ctx)->code).len + n > 32768) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t platform_elf_elf_add_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len) {
  int32_t k = 0;
  while (k < name_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((((ctx)->num_labels < 0 || ((ctx)->num_labels) >= 64 ? (shulang_panic_(1, 0), ((ctx)->labels)[0]) : ((ctx)->labels)[(ctx)->num_labels])).name)[k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->num_labels >= 64) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((ctx)->num_labels < 0 || ((ctx)->num_labels) >= 64 ? (shulang_panic_(1, 0), 0) : (((ctx)->labels)[(ctx)->num_labels].name_len = name_len, 0))));
  (void)((((ctx)->num_labels < 0 || ((ctx)->num_labels) >= 64 ? (shulang_panic_(1, 0), 0) : (((ctx)->labels)[(ctx)->num_labels].offset = ((ctx)->code).len, 0))));
  (void)(((ctx)->num_labels = (ctx)->num_labels + 1));
  return 0;
}
int32_t platform_elf_elf_add_patch(struct platform_elf_ElfCodegenCtx * ctx, int32_t rel32_offset, uint8_t name[64], int32_t name_len) {
  return platform_elf_elf_add_patch_with_bits(ctx, rel32_offset, name, name_len, 0);
}
int32_t platform_elf_elf_add_patch_with_bits(struct platform_elf_ElfCodegenCtx * ctx, int32_t rel32_offset, uint8_t name[64], int32_t name_len, int32_t imm_bits) {
  int32_t k = 0;
  while (k < name_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((((ctx)->num_patches < 0 || ((ctx)->num_patches) >= 128 ? (shulang_panic_(1, 0), ((ctx)->patches)[0]) : ((ctx)->patches)[(ctx)->num_patches])).name)[k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->num_patches >= 128) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((ctx)->num_patches < 0 || ((ctx)->num_patches) >= 128 ? (shulang_panic_(1, 0), 0) : (((ctx)->patches)[(ctx)->num_patches].rel32_offset = rel32_offset, 0))));
  (void)((((ctx)->num_patches < 0 || ((ctx)->num_patches) >= 128 ? (shulang_panic_(1, 0), 0) : (((ctx)->patches)[(ctx)->num_patches].name_len = name_len, 0))));
  (void)((((ctx)->num_patches < 0 || ((ctx)->num_patches) >= 128 ? (shulang_panic_(1, 0), 0) : (((ctx)->patches)[(ctx)->num_patches].patch_imm_bits = imm_bits, 0))));
  (void)(((ctx)->num_patches = (ctx)->num_patches + 1));
  return 0;
}
int32_t platform_elf_elf_add_reloc(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, uint8_t name[64], int32_t name_len) {
  int32_t k = 0;
  while (k < name_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((((ctx)->num_relocs < 0 || ((ctx)->num_relocs) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[(ctx)->num_relocs])).name)[k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->num_relocs >= 32) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((ctx)->num_relocs < 0 || ((ctx)->num_relocs) >= 32 ? (shulang_panic_(1, 0), 0) : (((ctx)->relocs)[(ctx)->num_relocs].offset = offset, 0))));
  (void)((((ctx)->num_relocs < 0 || ((ctx)->num_relocs) >= 32 ? (shulang_panic_(1, 0), 0) : (((ctx)->relocs)[(ctx)->num_relocs].name_len = name_len, 0))));
  (void)(((ctx)->num_relocs = (ctx)->num_relocs + 1));
  return 0;
}
int32_t platform_elf_elf_add_sym(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t offset) {
  int32_t k = 0;
  while (k < name_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((((ctx)->num_syms < 0 || ((ctx)->num_syms) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[(ctx)->num_syms])).name)[k] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (name)[0]) : (name)[k]), 0))));
    (void)((k = k + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->num_syms >= 16) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((((ctx)->num_syms < 0 || ((ctx)->num_syms) >= 16 ? (shulang_panic_(1, 0), 0) : (((ctx)->syms)[(ctx)->num_syms].name_len = name_len, 0))));
  (void)((((ctx)->num_syms < 0 || ((ctx)->num_syms) >= 16 ? (shulang_panic_(1, 0), 0) : (((ctx)->syms)[(ctx)->num_syms].offset = offset, 0))));
  (void)(((ctx)->num_syms = (ctx)->num_syms + 1));
  return 0;
}
int32_t platform_elf_elf_name_eq(uint8_t a[64], int32_t a_len, uint8_t b[64], int32_t b_len) {
  int32_t i = 0;
  while (i < a_len) {
    (void)(({ int32_t __tmp = 0; if ((i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (a)[0]) : (a)[i]) != (i < 0 || (i) >= 64 ? (shulang_panic_(1, 0), (b)[0]) : (b)[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (a_len != b_len) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return 1;
}
int32_t platform_elf_elf_resolve_patches(struct platform_elf_ElfCodegenCtx * ctx) {
  int32_t p = 0;
  while (p < (ctx)->num_patches) {
    int32_t rel32_offset = ((p < 0 || (p) >= 128 ? (shulang_panic_(1, 0), ((ctx)->patches)[0]) : ((ctx)->patches)[p])).rel32_offset;
    int32_t target_offset = (-1);
    int32_t l = 0;
    int32_t next_insn;
    int32_t delta;
    while (l < (ctx)->num_labels) {
      (void)(({ int32_t __tmp = 0; if (platform_elf_elf_name_eq(((p < 0 || (p) >= 128 ? (shulang_panic_(1, 0), ((ctx)->patches)[0]) : ((ctx)->patches)[p])).name, ((p < 0 || (p) >= 128 ? (shulang_panic_(1, 0), ((ctx)->patches)[0]) : ((ctx)->patches)[p])).name_len, ((l < 0 || (l) >= 64 ? (shulang_panic_(1, 0), ((ctx)->labels)[0]) : ((ctx)->labels)[l])).name, ((l < 0 || (l) >= 64 ? (shulang_panic_(1, 0), ((ctx)->labels)[0]) : ((ctx)->labels)[l])).name_len) != 0) {   (void)((target_offset = ((l < 0 || (l) >= 64 ? (shulang_panic_(1, 0), ((ctx)->labels)[0]) : ((ctx)->labels)[l])).offset));
  break;
 } else (__tmp = 0) ; __tmp; }));
      (void)((l = l + 1));
    }
    next_insn = rel32_offset + 4; delta = target_offset - next_insn;
  }
  return 0;
}
int32_t platform_elf_elf_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n) {
  int32_t i = 0;
  while (i < n && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (ptr)[i], 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (i < n) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t platform_elf_write_elf_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out) {
  int32_t code_len = ((ctx)->code).len;
  int32_t strtab_off = 1;
  int32_t s = 0;
  int32_t strtab_size = strtab_off;
  uint8_t shstrtab[64] = { 0, 46, 116, 101, 120, 116, 0, 46, 115, 121, 109, 116, 97, 98, 0, 46, 115, 116, 114, 116, 97, 98, 0, 46, 115, 104, 115, 116, 114, 116, 97, 98, 0, 46, 114, 101, 108, 97, 46, 116, 101, 120, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t shstrtab_size = 46;
  int32_t symtab_ents = 1 + (ctx)->num_syms;
  int32_t symtab_size = symtab_ents * 24;
  int32_t rela_size = (ctx)->num_relocs * 24;
  int32_t align4 = code_len + 3 & -4;
  int32_t off_text = 64;
  int32_t off_strtab = off_text + align4;
  int32_t off_shstrtab = off_strtab + strtab_size;
  int32_t off_symtab = off_shstrtab + shstrtab_size;
  int32_t off_rela = off_symtab + symtab_size;
  int32_t off_shdr = off_rela + rela_size;
  uint8_t ehdr[64] = { 127, 69, 76, 70, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 62, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0 };
  uint8_t zero_byte[1] = { 0 };
  int32_t z = 0;
  uint8_t strtab_first[1] = { 0 };
  uint8_t sym0[24] = { 0 };
  int32_t str_off = 1;
  int32_t r = 0;
  uint8_t shdr0[64] = { 0 };
  uint8_t shdr_text[64] = { 1, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0 };
  uint8_t shdr_sym[64] = { 8, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t shdr_str[64] = { 16, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t shdr_shstr[64] = { 24, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t shdr_rela[64] = { 35, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0 };
  while (s < (ctx)->num_syms) {
    (void)((strtab_off = strtab_off + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  while (z < align4 - code_len) {
    (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, zero_byte, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((z = z + 1));
  }
  while (s < (ctx)->num_syms) {
    (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, strtab_first, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((s = s + 1));
  }
  while (s < (ctx)->num_syms) {
    uint8_t ent[24] = { 0 };
    (void)(((4 < 0 || (4) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[4] = 18, 0))));
    (void)(((12 < 0 || (12) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[12] = 1, 0))));
    (void)(((ent)[0] = platform_elf_elf_to_u8(str_off)));
    (void)(((1 < 0 || (1) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[1] = platform_elf_elf_to_u8(str_off >> 8), 0))));
    (void)(((2 < 0 || (2) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[2] = platform_elf_elf_to_u8(str_off >> 16), 0))));
    (void)(((3 < 0 || (3) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[3] = platform_elf_elf_to_u8(str_off >> 24), 0))));
    (void)(((16 < 0 || (16) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[16] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset), 0))));
    (void)(((17 < 0 || (17) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[17] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 8), 0))));
    (void)(((18 < 0 || (18) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[18] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 16), 0))));
    (void)(((19 < 0 || (19) >= 24 ? (shulang_panic_(1, 0), 0) : ((ent)[19] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 24), 0))));
    (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, ent, 24) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((str_off = str_off + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  while (r < (ctx)->num_relocs) {
    uint8_t rela_buf[24] = {0};
    int32_t sym_idx = 0;
    int32_t m = 0;
    (void)(((12 < 0 || (12) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[12] = 252, 0))));
    (void)(((13 < 0 || (13) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[13] = 255, 0))));
    (void)(((14 < 0 || (14) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[14] = 255, 0))));
    (void)(((15 < 0 || (15) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[15] = 255, 0))));
    (void)(((16 < 0 || (16) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[16] = 255, 0))));
    (void)(((17 < 0 || (17) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[17] = 255, 0))));
    (void)(((18 < 0 || (18) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[18] = 255, 0))));
    (void)(((19 < 0 || (19) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[19] = 255, 0))));
    (void)(((rela_buf)[0] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset)));
    (void)(((1 < 0 || (1) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[1] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 8), 0))));
    (void)(((2 < 0 || (2) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[2] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 16), 0))));
    (void)(((3 < 0 || (3) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[3] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 24), 0))));
    (void)(((4 < 0 || (4) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[4] = platform_elf_elf_to_u8((ctx)->reloc_type_r_pc32), 0))));
    (void)(((5 < 0 || (5) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[5] = platform_elf_elf_to_u8((ctx)->reloc_type_r_pc32 >> 8), 0))));
    (void)(((8 < 0 || (8) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[8] = platform_elf_elf_to_u8(sym_idx), 0))));
    (void)(((9 < 0 || (9) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[9] = platform_elf_elf_to_u8(sym_idx >> 8), 0))));
    (void)(((10 < 0 || (10) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[10] = platform_elf_elf_to_u8(sym_idx >> 16), 0))));
    (void)(((11 < 0 || (11) >= 24 ? (shulang_panic_(1, 0), 0) : ((rela_buf)[11] = platform_elf_elf_to_u8(sym_idx >> 24), 0))));
    (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, rela_buf, 24) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((r = r + 1));
    while (m < (ctx)->num_syms) {
      (void)(({ int32_t __tmp = 0; if (platform_elf_elf_name_eq(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name, ((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name_len, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name_len) != 0) {   (void)((sym_idx = m + 1));
  break;
 } else (__tmp = 0) ; __tmp; }));
      (void)((m = m + 1));
    }
    uint8_t rela[24] = { 0 };
  }
  (void)(((out)->len = 0));
  (void)(((18 < 0 || (18) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[18] = platform_elf_elf_to_u8((ctx)->e_machine), 0))));
  (void)(((19 < 0 || (19) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[19] = platform_elf_elf_to_u8((ctx)->e_machine >> 8), 0))));
  (void)(((40 < 0 || (40) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[40] = platform_elf_elf_to_u8(off_shdr), 0))));
  (void)(((41 < 0 || (41) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[41] = platform_elf_elf_to_u8(off_shdr >> 8), 0))));
  (void)(((42 < 0 || (42) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[42] = platform_elf_elf_to_u8(off_shdr >> 16), 0))));
  (void)(((43 < 0 || (43) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[43] = platform_elf_elf_to_u8(off_shdr >> 24), 0))));
  (void)(((44 < 0 || (44) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[44] = 0, 0))));
  (void)(((45 < 0 || (45) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[45] = 0, 0))));
  (void)(((46 < 0 || (46) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[46] = 0, 0))));
  (void)(((47 < 0 || (47) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[47] = 0, 0))));
  (void)(((58 < 0 || (58) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[58] = platform_elf_elf_to_u8(64), 0))));
  (void)(((59 < 0 || (59) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[59] = 0, 0))));
  (void)(((60 < 0 || (60) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[60] = 6, 0))));
  (void)(((61 < 0 || (61) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[61] = 0, 0))));
  (void)(((62 < 0 || (62) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[62] = 4, 0))));
  (void)(((63 < 0 || (63) >= 64 ? (shulang_panic_(1, 0), 0) : ((ehdr)[63] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, ehdr, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, ((ctx)->code).data, code_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, strtab_first, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shstrtab, shstrtab_size) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((4 < 0 || (4) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[4] = 3, 0))));
  (void)(((12 < 0 || (12) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[12] = 1, 0))));
  (void)(((16 < 0 || (16) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[16] = platform_elf_elf_to_u8(code_len), 0))));
  (void)(((17 < 0 || (17) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[17] = platform_elf_elf_to_u8(code_len >> 8), 0))));
  (void)(((18 < 0 || (18) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[18] = platform_elf_elf_to_u8(code_len >> 16), 0))));
  (void)(((19 < 0 || (19) >= 24 ? (shulang_panic_(1, 0), 0) : ((sym0)[19] = platform_elf_elf_to_u8(code_len >> 24), 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, sym0, 24) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr0, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((24 < 0 || (24) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[24] = platform_elf_elf_to_u8(off_text), 0))));
  (void)(((25 < 0 || (25) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[25] = platform_elf_elf_to_u8(off_text >> 8), 0))));
  (void)(((26 < 0 || (26) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[26] = platform_elf_elf_to_u8(off_text >> 16), 0))));
  (void)(((27 < 0 || (27) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[27] = platform_elf_elf_to_u8(off_text >> 24), 0))));
  (void)(((28 < 0 || (28) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[32] = platform_elf_elf_to_u8(code_len), 0))));
  (void)(((33 < 0 || (33) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[33] = platform_elf_elf_to_u8(code_len >> 8), 0))));
  (void)(((34 < 0 || (34) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[34] = platform_elf_elf_to_u8(code_len >> 16), 0))));
  (void)(((35 < 0 || (35) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[35] = platform_elf_elf_to_u8(code_len >> 24), 0))));
  (void)(((36 < 0 || (36) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[36] = 0, 0))));
  (void)(((37 < 0 || (37) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[38] = 0, 0))));
  (void)(((39 < 0 || (39) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_text)[39] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr_text, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((24 < 0 || (24) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[24] = platform_elf_elf_to_u8(off_symtab), 0))));
  (void)(((25 < 0 || (25) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[25] = platform_elf_elf_to_u8(off_symtab >> 8), 0))));
  (void)(((26 < 0 || (26) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[26] = platform_elf_elf_to_u8(off_symtab >> 16), 0))));
  (void)(((27 < 0 || (27) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[27] = platform_elf_elf_to_u8(off_symtab >> 24), 0))));
  (void)(((28 < 0 || (28) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[32] = platform_elf_elf_to_u8(symtab_size), 0))));
  (void)(((33 < 0 || (33) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[33] = platform_elf_elf_to_u8(symtab_size >> 8), 0))));
  (void)(((34 < 0 || (34) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[34] = platform_elf_elf_to_u8(symtab_size >> 16), 0))));
  (void)(((35 < 0 || (35) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[35] = platform_elf_elf_to_u8(symtab_size >> 24), 0))));
  (void)(((36 < 0 || (36) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[36] = 0, 0))));
  (void)(((37 < 0 || (37) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[38] = 0, 0))));
  (void)(((39 < 0 || (39) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_sym)[39] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr_sym, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((24 < 0 || (24) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[24] = platform_elf_elf_to_u8(off_strtab), 0))));
  (void)(((25 < 0 || (25) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[25] = platform_elf_elf_to_u8(off_strtab >> 8), 0))));
  (void)(((26 < 0 || (26) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[26] = platform_elf_elf_to_u8(off_strtab >> 16), 0))));
  (void)(((27 < 0 || (27) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[27] = platform_elf_elf_to_u8(off_strtab >> 24), 0))));
  (void)(((28 < 0 || (28) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[32] = platform_elf_elf_to_u8(strtab_size), 0))));
  (void)(((33 < 0 || (33) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[33] = platform_elf_elf_to_u8(strtab_size >> 8), 0))));
  (void)(((34 < 0 || (34) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[34] = platform_elf_elf_to_u8(strtab_size >> 16), 0))));
  (void)(((35 < 0 || (35) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[35] = platform_elf_elf_to_u8(strtab_size >> 24), 0))));
  (void)(((36 < 0 || (36) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[36] = 0, 0))));
  (void)(((37 < 0 || (37) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[38] = 0, 0))));
  (void)(((39 < 0 || (39) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_str)[39] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr_str, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((24 < 0 || (24) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[24] = platform_elf_elf_to_u8(off_shstrtab), 0))));
  (void)(((25 < 0 || (25) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[25] = platform_elf_elf_to_u8(off_shstrtab >> 8), 0))));
  (void)(((26 < 0 || (26) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[26] = platform_elf_elf_to_u8(off_shstrtab >> 16), 0))));
  (void)(((27 < 0 || (27) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[27] = platform_elf_elf_to_u8(off_shstrtab >> 24), 0))));
  (void)(((28 < 0 || (28) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[32] = platform_elf_elf_to_u8(shstrtab_size), 0))));
  (void)(((33 < 0 || (33) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[33] = platform_elf_elf_to_u8(shstrtab_size >> 8), 0))));
  (void)(((34 < 0 || (34) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[34] = platform_elf_elf_to_u8(shstrtab_size >> 16), 0))));
  (void)(((35 < 0 || (35) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[35] = platform_elf_elf_to_u8(shstrtab_size >> 24), 0))));
  (void)(((36 < 0 || (36) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[36] = 0, 0))));
  (void)(((37 < 0 || (37) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[38] = 0, 0))));
  (void)(((39 < 0 || (39) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_shstr)[39] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr_shstr, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((24 < 0 || (24) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[24] = platform_elf_elf_to_u8(off_rela), 0))));
  (void)(((25 < 0 || (25) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[25] = platform_elf_elf_to_u8(off_rela >> 8), 0))));
  (void)(((26 < 0 || (26) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[26] = platform_elf_elf_to_u8(off_rela >> 16), 0))));
  (void)(((27 < 0 || (27) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[27] = platform_elf_elf_to_u8(off_rela >> 24), 0))));
  (void)(((28 < 0 || (28) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[32] = platform_elf_elf_to_u8(rela_size), 0))));
  (void)(((33 < 0 || (33) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[33] = platform_elf_elf_to_u8(rela_size >> 8), 0))));
  (void)(((34 < 0 || (34) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[34] = platform_elf_elf_to_u8(rela_size >> 16), 0))));
  (void)(((35 < 0 || (35) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[35] = platform_elf_elf_to_u8(rela_size >> 24), 0))));
  (void)(((36 < 0 || (36) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[36] = 0, 0))));
  (void)(((37 < 0 || (37) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[38] = 0, 0))));
  (void)(((39 < 0 || (39) >= 64 ? (shulang_panic_(1, 0), 0) : ((shdr_rela)[39] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_append(out, shdr_rela, 64) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return (out)->len;
}
extern int32_t platform_elf_elf_add_label(struct platform_elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len);
extern int32_t platform_elf_elf_add_sym(struct platform_elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len, int32_t offset);
int32_t arch_x86_64_enc_enc_u8(struct platform_elf_ElfCodegenCtx * ctx, int32_t b);
int32_t arch_x86_64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm);
int32_t arch_x86_64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_size);
int32_t arch_x86_64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi);
int32_t arch_x86_64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc);
int32_t arch_x86_64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_x86_64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm);
int32_t arch_x86_64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size);
int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_x86_64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k);
int32_t arch_x86_64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len);
int32_t arch_x86_64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func);
int32_t arch_x86_64_enc_enc_u8(struct platform_elf_ElfCodegenCtx * ctx, int32_t b) {
  uint8_t buf[1] = { 0 };
  (void)(((buf)[0] = platform_elf_elf_to_u8(b)));
  return platform_elf_append_elf_bytes(ctx, buf, 1);
}
int32_t arch_x86_64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm) {
  uint8_t buf[4] = { 0 };
  (void)(((buf)[0] = platform_elf_elf_to_u8(imm)));
  (void)(((1 < 0 || (1) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[1] = platform_elf_elf_to_u8(imm >> 8), 0))));
  (void)(((2 < 0 || (2) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = platform_elf_elf_to_u8(imm >> 16), 0))));
  (void)(((3 < 0 || (3) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(imm >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
}
int32_t arch_x86_64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_size) {
  uint8_t mov[3] = { 72, 137, 229 };
  uint8_t sub[7] = { 72, 129, 236, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 85) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, mov, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((sub)[3] = platform_elf_elf_to_u8(frame_size), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((sub)[4] = platform_elf_elf_to_u8(frame_size >> 8), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((sub)[5] = platform_elf_elf_to_u8(frame_size >> 16), 0))));
  (void)(((6 < 0 || (6) >= 7 ? (shulang_panic_(1, 0), 0) : ((sub)[6] = platform_elf_elf_to_u8(frame_size >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, sub, 7);
}
int32_t arch_x86_64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t mov[3] = { 72, 137, 229 };
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, mov, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 93) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_u8(ctx, 195);
}
int32_t arch_x86_64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 184) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_u32_le(ctx, imm32);
}
int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 187) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_u32_le(ctx, imm32);
}
int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi) {
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 72) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 184) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u32_le(ctx, lo) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_u32_le(ctx, hi);
}
int32_t arch_x86_64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_x86_64_enc_enc_u8(ctx, 80);
}
int32_t arch_x86_64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_x86_64_enc_enc_u8(ctx, 91);
}
int32_t arch_x86_64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_x86_64_enc_enc_u8(ctx, 88);
}
int32_t arch_x86_64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[3] = { 72, 1, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 3);
}
int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t sub[3] = { 72, 41, 195 };
  uint8_t mov[3] = { 72, 137, 216 };
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, sub, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_append_elf_bytes(ctx, mov, 3);
}
int32_t arch_x86_64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[4] = { 72, 15, 175, 195 };
  return platform_elf_append_elf_bytes(ctx, buf, 4);
}
int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[3] = { 72, 137, 195 };
  return platform_elf_append_elf_bytes(ctx, buf, 3);
}
int32_t arch_x86_64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 247, 208 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 33, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 9, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 49, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 137, 217 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 211, 224 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 211, 232 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 211, 248 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_x86_64_enc_enc_u8(ctx, 153);
}
int32_t arch_x86_64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 247, 251 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 137, 208 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 247, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 133, 192 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t s[3] = { 15, 148, 192 };
  uint8_t m[3] = { 15, 182, 192 };
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, s, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_append_elf_bytes(ctx, m, 3);
}
int32_t arch_x86_64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 57, 195 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc) {
  int32_t op = 148;
  uint8_t s[3] = { 15, platform_elf_elf_to_u8(op), 192 };
  uint8_t m[3] = { 15, 182, 192 };
  (void)(({ int32_t __tmp = 0; if (cc == 1) {   (void)((op = 149));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (cc == 2) {   (void)((op = 156));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (cc == 3) {   (void)((op = 158));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (cc == 4) {   (void)((op = 159));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (cc == 5) {   (void)((op = 157));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, s, 3) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_append_elf_bytes(ctx, m, 3);
}
int32_t arch_x86_64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t disp = 0 - offset;
  uint8_t buf[7] = { 72, 137, 133, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (disp >= (-128) && disp <= (-1)) {   uint8_t buf[4] = { 72, 137, 69, 0 };
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = platform_elf_elf_to_u8(disp >> 8), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = platform_elf_elf_to_u8(disp >> 16), 0))));
  (void)(((6 < 0 || (6) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = platform_elf_elf_to_u8(disp >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 7);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t disp = 0 - offset;
  uint8_t buf[7] = { 72, 139, 133, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (disp >= (-128) && disp <= (-1)) {   uint8_t buf[4] = { 72, 139, 69, 0 };
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = platform_elf_elf_to_u8(disp >> 8), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = platform_elf_elf_to_u8(disp >> 16), 0))));
  (void)(((6 < 0 || (6) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = platform_elf_elf_to_u8(disp >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 7);
}
int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t disp = 0 - offset;
  uint8_t buf[7] = { 72, 141, 133, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (disp >= (-128) && disp <= (-1)) {   uint8_t buf[4] = { 72, 141, 69, 0 };
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(disp), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = platform_elf_elf_to_u8(disp >> 8), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = platform_elf_elf_to_u8(disp >> 16), 0))));
  (void)(((6 < 0 || (6) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = platform_elf_elf_to_u8(disp >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 7);
}
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[4] = { 72, 141, 4, 152 };
  return platform_elf_append_elf_bytes(ctx, buf, 4);
}
int32_t arch_x86_64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[2] = { 139, 0 };
  return platform_elf_append_elf_bytes(ctx, buf, 2);
}
int32_t arch_x86_64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm) {
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 72) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_u32_le(ctx, imm);
}
int32_t arch_x86_64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[3] = { 72, 139, 0 };
  return platform_elf_append_elf_bytes(ctx, buf, 3);
}
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size) {
  uint8_t buf[7] = { 72, 137, 131, 0, 0, 0, 0 };
  (void)(({ int32_t __tmp = 0; if (store_size == 4) {   uint8_t buf[6] = { 137, 131, 0, 0, 0, 0 };
  (void)(((2 < 0 || (2) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = platform_elf_elf_to_u8(offset), 0))));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(offset >> 8), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = platform_elf_elf_to_u8(offset >> 16), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = platform_elf_elf_to_u8(offset >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 6);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((3 < 0 || (3) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(offset), 0))));
  (void)(((4 < 0 || (4) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[4] = platform_elf_elf_to_u8(offset >> 8), 0))));
  (void)(((5 < 0 || (5) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[5] = platform_elf_elf_to_u8(offset >> 16), 0))));
  (void)(((6 < 0 || (6) >= 7 ? (shulang_panic_(1, 0), 0) : ((buf)[6] = platform_elf_elf_to_u8(offset >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 7);
}
int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  uint8_t buf[3] = { 72, 137, 216 };
  return platform_elf_append_elf_bytes(ctx, buf, 3);
}
int32_t arch_x86_64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  uint8_t buf[6] = { 15, 132, 0, 0, 0, 0 };
  int32_t rel32_at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, buf, 6) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch(ctx, rel32_at, label, label_len);
}
int32_t arch_x86_64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  uint8_t buf[6] = { 15, 133, 0, 0, 0, 0 };
  int32_t rel32_at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (platform_elf_append_elf_bytes(ctx, buf, 6) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch(ctx, rel32_at, label, label_len);
}
int32_t arch_x86_64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t rel32_at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 233) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u32_le(ctx, 0) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch(ctx, rel32_at, label, label_len);
}
int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k) {
  uint8_t ins[6][3] = { 0 };
  int32_t idx = k;
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_append_elf_bytes(ctx, (idx < 0 || (idx) >= 6 ? (shulang_panic_(1, 0), (ins)[0]) : (ins)[idx]), 3);
}
int32_t arch_x86_64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len) {
  int32_t rel32_at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u8(ctx, 232) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_enc_enc_u32_le(ctx, 0) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_reloc(ctx, rel32_at, name, name_len);
}
int32_t arch_x86_64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func) {
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(ctx, name, name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (is_func != 0) {   return platform_elf_elf_add_sym(ctx, name, name_len, ((ctx)->code).len);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_arm64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t val);
int32_t arch_arm64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_size);
int32_t arch_arm64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_arm64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_arm64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi);
int32_t arch_arm64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc);
int32_t arch_arm64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_arm64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_arm64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_arm64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm);
int32_t arch_arm64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size);
int32_t arch_arm64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_arm64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_arm64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k);
int32_t arch_arm64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len);
int32_t arch_arm64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func);
int32_t arch_arm64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t val) {
  uint8_t buf[4] = { 0 };
  (void)(((buf)[0] = platform_elf_elf_to_u8(val)));
  (void)(((1 < 0 || (1) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[1] = platform_elf_elf_to_u8(val >> 8), 0))));
  (void)(((2 < 0 || (2) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = platform_elf_elf_to_u8(val >> 16), 0))));
  (void)(((3 < 0 || (3) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(val >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
}
int32_t arch_arm64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_size) {
  int32_t imm12 = frame_size;
  (void)(((ctx)->current_frame_size = frame_size));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -2088963) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -1862270976) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -788529153 | imm12 << 10);
}
int32_t arch_arm64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx) {
  int32_t imm12 = (ctx)->current_frame_size;
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -1862270976 | imm12 << 10) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -1463083009) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -696254464);
}
int32_t arch_arm64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  int32_t lo = imm32 & 65535;
  int32_t hi = imm32 >> 16 & 65535;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 1384120320 | lo << 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi != 0) {   __tmp = ({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 1946157056 | hi << 5 | 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_arm64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  int32_t lo = imm32 & 65535;
  int32_t hi = imm32 >> 16 & 65535;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 1384120352 | lo << 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi != 0) {   __tmp = ({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 1946157088 | hi << 5 | 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_arm64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi) {
  int32_t lo0 = lo & 65535;
  int32_t lo1 = lo >> 16 & 65535;
  int32_t hi0 = hi & 65535;
  int32_t hi1 = hi >> 16 & 65535;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -754974720 | lo0 << 5) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -234881024 | lo1 << 5 | 2097152) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -234881024 | hi0 << 5 | 4194304) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -234881024 | hi1 << 5 | 6291456);
}
int32_t arch_arm64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -788527105) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -117439520);
}
int32_t arch_arm64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -263116832) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1862270944);
}
int32_t arch_arm64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -263116832) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1862270944);
}
int32_t arch_arm64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 185597952);
}
int32_t arch_arm64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 185598240) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, 553648224);
}
int32_t arch_arm64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 447392288);
}
int32_t arch_arm64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 553648224);
}
int32_t arch_arm64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 707796960);
}
int32_t arch_arm64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 138412064);
}
int32_t arch_arm64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 185597984);
}
int32_t arch_arm64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 232783904);
}
int32_t arch_arm64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 553648256);
}
int32_t arch_arm64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 448792640);
}
int32_t arch_arm64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 448793664);
}
int32_t arch_arm64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 448794688);
}
int32_t arch_arm64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, -721216993);
}
int32_t arch_arm64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 448792608);
}
int32_t arch_arm64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 448792672) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, 447392288);
}
int32_t arch_arm64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 185598432);
}
int32_t arch_arm64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 1895825439);
}
int32_t arch_arm64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 1522532352);
}
int32_t arch_arm64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 185598239);
}
int32_t arch_arm64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc) {
  int32_t c = cc;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 185598239) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c < 0) {   (void)((c = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c > 5) {   (void)((c = 5));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, 1522532352 | c << 12);
}
int32_t arch_arm64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t simm9 = 0 - offset;
  int32_t u9 = simm9 & 511;
  (void)(({ int32_t __tmp = 0; if (simm9 < (-256)) {   (void)((simm9 = (-256)));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1201668096 | u9 << 12 | 29 << 5 | 0);
}
int32_t arch_arm64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t simm9 = 0 - offset;
  int32_t u9 = simm9 & 511;
  (void)(({ int32_t __tmp = 0; if (simm9 < (-256)) {   (void)((simm9 = (-256)));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1201668096 | u9 << 12 | 29 << 5 | 0);
}
int32_t arch_arm64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t imm12 = offset;
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -788529152 | imm12 << 10 | 29 << 5 | 0);
}
int32_t arch_arm64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, -1962934272);
}
int32_t arch_arm64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, -1191182336);
}
int32_t arch_arm64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm) {
  int32_t imm12 = imm;
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1862270976 | imm12 << 10 | 0 << 5 | 0);
}
int32_t arch_arm64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, -263116800);
}
int32_t arch_arm64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size) {
  int32_t imm12 = (8 == 0 ? (shulang_panic_(1, 0), offset) : (offset / 8));
  (void)(({ int32_t __tmp = 0; if (store_size == 4) {   int32_t imm12 = (4 == 0 ? (shulang_panic_(1, 0), offset) : (offset / 4));
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -1201668096 | imm12 << 10 | 1 << 5 | 0);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm12 > 4095) {   (void)((imm12 = 4095));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, -263116800 | imm12 << 10 | 1 << 5 | 0);
}
int32_t arch_arm64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_arm64_enc_enc_u32_le(ctx, 553648224);
}
int32_t arch_arm64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 872415232) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 19);
}
int32_t arch_arm64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 872415488) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 19);
}
int32_t arch_arm64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, 1342177280) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 26);
}
int32_t arch_arm64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k) {
  int32_t rd = k;
  (void)(({ int32_t __tmp = 0; if (rd < 0) {   (void)((rd = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (rd > 5) {   (void)((rd = 5));
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_enc_enc_u32_le(ctx, 553648224 | rd << 5);
}
int32_t arch_arm64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_arm64_enc_enc_u32_le(ctx, -1610612736) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_patch_with_bits(ctx, at, name, name_len, 26) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_reloc(ctx, at, name, name_len);
}
int32_t arch_arm64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func) {
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(ctx, name, name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (is_func != 0) {   return platform_elf_elf_add_sym(ctx, name, name_len, ((ctx)->code).len);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_riscv64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t val);
int32_t arch_riscv64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func);
int32_t arch_riscv64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_sz);
int32_t arch_riscv64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_riscv64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32);
int32_t arch_riscv64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi);
int32_t arch_riscv64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc);
int32_t arch_riscv64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_riscv64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_riscv64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset);
int32_t arch_riscv64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm);
int32_t arch_riscv64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size);
int32_t arch_riscv64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx);
int32_t arch_riscv64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len);
int32_t arch_riscv64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k);
int32_t arch_riscv64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len);
int32_t arch_riscv64_enc_enc_u32_le(struct platform_elf_ElfCodegenCtx * ctx, int32_t val) {
  uint8_t buf[4] = { 0 };
  (void)(((buf)[0] = platform_elf_elf_to_u8(val)));
  (void)(((1 < 0 || (1) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[1] = platform_elf_elf_to_u8(val >> 8), 0))));
  (void)(((2 < 0 || (2) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[2] = platform_elf_elf_to_u8(val >> 16), 0))));
  (void)(((3 < 0 || (3) >= 4 ? (shulang_panic_(1, 0), 0) : ((buf)[3] = platform_elf_elf_to_u8(val >> 24), 0))));
  return platform_elf_append_elf_bytes(ctx, buf, 4);
}
int32_t arch_riscv64_enc_enc_label(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len, int32_t is_func) {
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(ctx, name, name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (is_func != 0) {   return platform_elf_elf_add_sym(ctx, name, name_len, ((ctx)->code).len);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t arch_riscv64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx * ctx, int32_t frame_sz) {
  int32_t sz = frame_sz;
  int32_t imm12 = 0 - sz;
  int32_t off_ra = sz - 8;
  int32_t imm_lo = off_ra & 31;
  int32_t imm_hi = off_ra >> 5 & 127;
  int32_t off_s0 = sz - 16;
  (void)(({ int32_t __tmp = 0; if (sz < 16) {   (void)((sz = 16));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (frame_sz >= 16) {   (void)(((ctx)->current_frame_size = sz | 4096));
 } else {   (void)(((ctx)->current_frame_size = sz));
 } ; __tmp; }));
  (void)((imm12 = imm12 & 4095));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 2 << 7 | 0 << 12 | 2 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 35 | imm_lo << 7 | 3 << 12 | 2 << 15 | 1 << 20 | imm_hi << 25) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (frame_sz < 16) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm_lo = off_s0 & 31));
  (void)((imm_hi = off_s0 >> 5 & 127));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 35 | imm_lo << 7 | 3 << 12 | 2 << 15 | 8 << 20 | imm_hi << 25) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm12 = sz & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 8 << 7 | 0 << 12 | 2 << 15 | imm12 << 20);
}
int32_t arch_riscv64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx * ctx) {
  int32_t saved_s0 = (ctx)->current_frame_size & 4096 >> 12;
  int32_t frame_sz = (ctx)->current_frame_size & 4095;
  int32_t off_ra = frame_sz - 8;
  int32_t imm12 = off_ra & 4095;
  (void)(({ int32_t __tmp = 0; if (frame_sz == 0) {   (void)((frame_sz = 16));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (saved_s0 != 0) {   int32_t off_s0 = frame_sz - 16;
  int32_t imm12 = off_s0 & 4095;
  __tmp = ({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 3 | 8 << 7 | 3 << 12 | 2 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 3 | 1 << 7 | 3 << 12 | 2 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm12 = frame_sz & 4095));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 2 << 7 | 0 << 12 | 2 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 103 | 0 << 7 | 0 << 12 | 1 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  int32_t imm12 = imm32 & 4095;
  int32_t hi20 = imm32 >> 12 & 1048575;
  (void)(({ int32_t __tmp = 0; if (imm32 >= 2048 && imm32 < 4096) {   (void)((imm12 = imm32));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm32 >= 0 && imm32 < 4096) {   return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 0 << 15 | imm12 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm32 & 2048 != 0) {   (void)((hi20 = hi20 + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 55 | 10 << 7 | hi20 << 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm12 = imm32 & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 10 << 15 | imm12 << 20);
}
int32_t arch_riscv64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm32) {
  int32_t imm12 = imm32 & 4095;
  int32_t hi20 = imm32 >> 12 & 1048575;
  (void)(({ int32_t __tmp = 0; if (imm32 >= 0 && imm32 < 4096) {   return arch_riscv64_enc_enc_u32_le(ctx, 19 | 11 << 7 | 0 << 12 | 0 << 15 | imm12 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (imm32 & 2048 != 0) {   (void)((hi20 = hi20 + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 55 | 11 << 7 | hi20 << 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm12 = imm32 & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 11 << 7 | 0 << 12 | 11 << 15 | imm12 << 20);
}
int32_t arch_riscv64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t lo, int32_t hi) {
  int32_t imm12 = lo & 4095;
  int32_t hi20 = hi >> 12 & 1048575;
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 0 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 1 << 12 | 10 << 15 | 32 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 5 << 12 | 10 << 15 | 32 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (hi & 2048 != 0) {   (void)((hi20 = hi20 + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 55 | 5 << 7 | hi20 << 12) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((imm12 = hi & 4095));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 5 << 7 | 0 << 12 | 5 << 15 | imm12 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 5 << 7 | 1 << 12 | 5 << 15 | 32 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 10 << 15 | 5 << 20);
}
int32_t arch_riscv64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 2 << 7 | 0 << 12 | 2 << 15 | 4080 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 35 | 0 << 7 | 3 << 12 | 2 << 15 | 10 << 20 | 0 << 25);
}
int32_t arch_riscv64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 3 | 11 << 7 | 3 << 12 | 2 << 15 | 0 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 2 << 7 | 0 << 12 | 2 << 15 | 16 << 20);
}
int32_t arch_riscv64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 3 | 10 << 7 | 3 << 12 | 2 << 15 | 0 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 2 << 7 | 0 << 12 | 2 << 15 | 16 << 20);
}
int32_t arch_riscv64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 10 << 15 | 11 << 20);
}
int32_t arch_riscv64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 11 << 15 | 10 << 20 | 64 << 25);
}
int32_t arch_riscv64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 10 << 15 | 11 << 20 | 1 << 25);
}
int32_t arch_riscv64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 11 << 7 | 0 << 12 | 10 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 4 << 12 | 10 << 15 | 4095 << 20);
}
int32_t arch_riscv64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 7 << 12 | 11 << 15 | 10 << 20);
}
int32_t arch_riscv64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 6 << 12 | 11 << 15 | 10 << 20);
}
int32_t arch_riscv64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 4 << 12 | 11 << 15 | 10 << 20);
}
int32_t arch_riscv64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx * ctx) {
  return 0;
}
int32_t arch_riscv64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 1 << 12 | 10 << 15 | 11 << 20);
}
int32_t arch_riscv64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 5 << 12 | 10 << 15 | 11 << 20);
}
int32_t arch_riscv64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 5 << 12 | 10 << 15 | 11 << 20 | 64 << 25);
}
int32_t arch_riscv64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx * ctx) {
  return 0;
}
int32_t arch_riscv64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 4 << 12 | 10 << 15 | 11 << 20 | 1 << 25);
}
int32_t arch_riscv64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return 0;
}
int32_t arch_riscv64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 0 << 15 | 10 << 20 | 64 << 25);
}
int32_t arch_riscv64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return 0;
}
int32_t arch_riscv64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 3 << 12 | 10 << 15 | 1 << 20);
}
int32_t arch_riscv64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 11 << 15 | 10 << 20 | 64 << 25);
}
int32_t arch_riscv64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx * ctx, int32_t cc) {
  int32_t c = cc;
  (void)(({ int32_t __tmp = 0; if (c < 0) {   (void)((c = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c > 5) {   (void)((c = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 0) {   return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 3 << 12 | 10 << 15 | 1 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 1) {   return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 3 << 12 | 0 << 15 | 10 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 2) {   return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 2 << 12 | 11 << 15 | 10 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 3) {   (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 2 << 12 | 10 << 15 | 11 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 4 << 12 | 10 << 15 | 1 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (c == 4) {   return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 2 << 12 | 10 << 15 | 11 << 20);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 2 << 12 | 11 << 15 | 10 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 4 << 12 | 10 << 15 | 1 << 20);
}
int32_t arch_riscv64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t imm = 0 - offset;
  int32_t imm_lo = imm & 31;
  int32_t imm_hi = imm >> 5 & 127;
  (void)((imm = imm & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 35 | imm_lo << 7 | 3 << 12 | 8 << 15 | 10 << 20 | imm_hi << 25);
}
int32_t arch_riscv64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t imm = 0 - offset;
  (void)((imm = imm & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 3 | 10 << 7 | 3 << 12 | 8 << 15 | imm << 20);
}
int32_t arch_riscv64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset) {
  int32_t imm12 = 0 - offset;
  (void)((imm12 = imm12 & 4095));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 8 << 15 | imm12 << 20);
}
int32_t arch_riscv64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 19 | 11 << 7 | 1 << 12 | 11 << 15 | 2 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 51 | 10 << 7 | 0 << 12 | 10 << 15 | 11 << 20);
}
int32_t arch_riscv64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 3 | 10 << 7 | 2 << 12 | 10 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx * ctx, int32_t imm) {
  int32_t imm12 = imm & 4095;
  (void)(({ int32_t __tmp = 0; if (imm == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 10 << 15 | imm12 << 20);
}
int32_t arch_riscv64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 3 | 10 << 7 | 3 << 12 | 10 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx * ctx, int32_t offset, int32_t store_size) {
  int32_t imm = offset & 4095;
  int32_t imm_lo = imm & 31;
  int32_t imm_hi = imm >> 5 & 127;
  (void)(({ int32_t __tmp = 0; if (store_size == 4) {   return arch_riscv64_enc_enc_u32_le(ctx, 35 | imm_lo << 7 | 2 << 12 | 11 << 15 | 10 << 20 | imm_hi << 25);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 35 | imm_lo << 7 | 3 << 12 | 11 << 15 | 10 << 20 | imm_hi << 25);
}
int32_t arch_riscv64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx * ctx) {
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | 10 << 7 | 0 << 12 | 11 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_jz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 99 | 0 << 12 | 10 << 15 | 0 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 13);
}
int32_t arch_riscv64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 99 | 1 << 12 | 10 << 15 | 0 << 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 13);
}
int32_t arch_riscv64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx * ctx, uint8_t label[64], int32_t label_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 111 | 0 << 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_patch_with_bits(ctx, at, label, label_len, 21);
}
int32_t arch_riscv64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx * ctx, int32_t k) {
  int32_t idx = k;
  int32_t rd = 10 + idx;
  (void)(({ int32_t __tmp = 0; if (idx < 0) {   (void)((idx = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx > 5) {   (void)((idx = 5));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (idx == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_enc_enc_u32_le(ctx, 19 | rd << 7 | 0 << 12 | 10 << 15 | 0 << 20);
}
int32_t arch_riscv64_enc_enc_call(struct platform_elf_ElfCodegenCtx * ctx, uint8_t name[64], int32_t name_len) {
  int32_t at = ((ctx)->code).len - 4;
  (void)(({ int32_t __tmp = 0; if (arch_riscv64_enc_enc_u32_le(ctx, 111 | 1 << 7) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_patch_with_bits(ctx, at, name, name_len, 21) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return platform_elf_elf_add_reloc(ctx, at, name, name_len);
}
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena *, int32_t);
extern int32_t codegen_emit_expr(struct ast_ASTArena *, struct codegen_CodegenOutBuf *, int32_t);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena *, int32_t);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena *, int32_t);
extern int32_t types_format_i32_to_buf(uint8_t *, int32_t, int32_t, int32_t);
struct backend_LocalSlot { uint8_t name[64]; int32_t name_len; int32_t offset; };
struct backend_AsmFuncCtx { int32_t frame_size; int32_t next_offset; struct backend_LocalSlot locals[24]; int32_t num_locals; int32_t label_counter; uint8_t break_label[64]; int32_t break_len; uint8_t continue_label[64]; int32_t continue_len; };
int32_t backend_enc_label_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t name[64], int32_t name_len, int32_t is_func, int32_t ta);
int32_t backend_enc_prologue_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t frame_sz, int32_t ta);
int32_t backend_enc_epilogue_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_ret_imm32_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm32, int32_t ta);
int32_t backend_enc_mov_imm32_to_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm32, int32_t ta);
int32_t backend_enc_mov_imm64_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t lo, int32_t hi, int32_t ta);
int32_t backend_enc_push_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_pop_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_pop_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_add_rax_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_sub_rbx_rax_then_mov_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_imul_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_mov_rax_to_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_not_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_and_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_or_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_xor_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_mov_rbx_to_ecx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_shl_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_shr_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_sar_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_cltd_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_idiv_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_mov_edx_to_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_neg_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_test_eax_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_setz_movzbl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_cmp_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_cmp_setcc_movzbl_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t cc, int32_t ta);
int32_t backend_enc_store_rax_to_rbp_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta);
int32_t backend_enc_load_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta);
int32_t backend_enc_lea_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta);
int32_t backend_enc_rax_plus_rbx_scale4_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_load_32_from_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_add_imm_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm, int32_t ta);
int32_t backend_enc_load_64_from_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_store_rax_to_rbx_offset_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t store_size, int32_t ta);
int32_t backend_enc_mov_rbx_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta);
int32_t backend_enc_jz_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_enc_jnz_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_enc_jmp_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_enc_mov_rax_to_arg_reg_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t k, int32_t ta);
int32_t backend_enc_call_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t name[64], int32_t name_len, int32_t ta);
void backend_ctx_reset(struct backend_AsmFuncCtx * ctx);
int32_t backend_compute_frame_size(struct ast_Block * block);
void backend_fill_local_slots(struct backend_AsmFuncCtx * ctx, struct ast_Block * block);
int32_t backend_local_offset(struct backend_AsmFuncCtx * ctx, uint8_t * name, int32_t name_len);
int32_t backend_arch_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta);
int32_t backend_arch_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi, int32_t ta);
int32_t backend_arch_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta);
int32_t backend_arch_emit_neg_eax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_test_setz(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc, int32_t ta);
int32_t backend_arch_emit_push_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_pop_rbx(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_pop_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_idiv_rbx(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_rem_mod(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta);
int32_t backend_arch_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta);
int32_t backend_arch_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta);
int32_t backend_arch_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta);
int32_t backend_arch_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size, int32_t ta);
int32_t backend_arch_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k, int32_t ta);
int32_t backend_arch_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i, int32_t ta);
int32_t backend_arch_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n, int32_t ta);
int32_t backend_emit_expr_call(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_expr_method_call(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_expr_elf_method_call(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_expr_elf_call(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_arch_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta);
int32_t backend_arch_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_arch_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_arch_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta);
int32_t backend_arch_emit_not_eax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta);
int32_t backend_arch_emit_section_text(struct codegen_CodegenOutBuf * out, int32_t ta);
int32_t backend_arch_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta);
int32_t backend_arch_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_sz, int32_t ta);
int32_t backend_arch_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_sz, int32_t ta);
int32_t backend_get_return_expr_ref(struct ast_ASTArena * arena, struct ast_Func * f);
int32_t backend_emit_expr(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t expr_ref, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_expr_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_block_inits_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_while_loop_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_WhileLoop * wloop, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_for_loop_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_ForLoop * floop, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_block_body_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t ta);
int32_t backend_emit_block_inits(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_next_label(struct backend_AsmFuncCtx * ctx, uint8_t * buf, int32_t buf_size);
int32_t backend_format_label_id(uint8_t * buf, int32_t buf_size, int32_t id);
void backend_ctx_set_loop_labels(struct backend_AsmFuncCtx * ctx, uint8_t * exit_buf, int32_t exit_len, uint8_t * loop_buf, int32_t loop_len);
int32_t backend_emit_loop_body_content(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_while_loop(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_WhileLoop * wloop, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_for_loop(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_ForLoop * floop, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_emit_block_body(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch);
int32_t backend_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_PipelineDepCtx * pipeline_ctx);
int32_t backend_asm_codegen_ast_to_elf(struct ast_Module * module, struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_PipelineDepCtx * pipeline_ctx);
int32_t backend_enc_label_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t name[64], int32_t name_len, int32_t is_func, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_label(elf_ctx, name, name_len, is_func);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_label(elf_ctx, name, name_len, is_func);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_label(elf_ctx, name, name_len, is_func);
}
int32_t backend_enc_prologue_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t frame_sz, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_prologue(elf_ctx, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_prologue(elf_ctx, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_prologue(elf_ctx, frame_sz);
}
int32_t backend_enc_epilogue_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_epilogue(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_epilogue(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_epilogue(elf_ctx);
}
int32_t backend_enc_ret_imm32_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm32, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_ret_imm32(elf_ctx, imm32);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_ret_imm32(elf_ctx, imm32);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_ret_imm32(elf_ctx, imm32);
}
int32_t backend_enc_mov_imm32_to_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm32, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
}
int32_t backend_enc_mov_imm64_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t lo, int32_t hi, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
}
int32_t backend_enc_push_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_push_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_push_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_push_rax(elf_ctx);
}
int32_t backend_enc_pop_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_pop_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_pop_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_pop_rax(elf_ctx);
}
int32_t backend_enc_pop_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_pop_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_pop_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_pop_rbx(elf_ctx);
}
int32_t backend_enc_add_rax_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_add_rax_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_add_rax_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_add_rax_rbx(elf_ctx);
}
int32_t backend_enc_sub_rbx_rax_then_mov_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
}
int32_t backend_enc_imul_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_imul_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_imul_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_imul_rbx_rax(elf_ctx);
}
int32_t backend_enc_mov_rax_to_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_rax_to_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_rax_to_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_rax_to_rbx(elf_ctx);
}
int32_t backend_enc_not_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_not_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_not_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_not_eax(elf_ctx);
}
int32_t backend_enc_and_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_and_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_and_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_and_rbx_rax(elf_ctx);
}
int32_t backend_enc_or_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_or_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_or_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_or_rbx_rax(elf_ctx);
}
int32_t backend_enc_xor_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_xor_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_xor_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_xor_rbx_rax(elf_ctx);
}
int32_t backend_enc_mov_rbx_to_ecx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_rbx_to_ecx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_rbx_to_ecx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_rbx_to_ecx(elf_ctx);
}
int32_t backend_enc_shl_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_shl_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_shl_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_shl_cl_eax(elf_ctx);
}
int32_t backend_enc_shr_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_shr_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_shr_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_shr_cl_eax(elf_ctx);
}
int32_t backend_enc_sar_cl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_sar_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_sar_cl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_sar_cl_eax(elf_ctx);
}
int32_t backend_enc_cltd_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_cltd(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_cltd(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_cltd(elf_ctx);
}
int32_t backend_enc_idiv_rbx_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_idiv_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_idiv_rbx(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_idiv_rbx(elf_ctx);
}
int32_t backend_enc_mov_edx_to_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx);
}
int32_t backend_enc_neg_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_neg_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_neg_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_neg_eax(elf_ctx);
}
int32_t backend_enc_test_eax_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_test_eax_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_test_eax_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_test_eax_eax(elf_ctx);
}
int32_t backend_enc_setz_movzbl_eax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_setz_movzbl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_setz_movzbl_eax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_setz_movzbl_eax(elf_ctx);
}
int32_t backend_enc_cmp_rbx_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_cmp_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_cmp_rbx_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_cmp_rbx_rax(elf_ctx);
}
int32_t backend_enc_cmp_setcc_movzbl_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t cc, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
}
int32_t backend_enc_store_rax_to_rbp_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
}
int32_t backend_enc_load_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
}
int32_t backend_enc_lea_rbp_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
}
int32_t backend_enc_rax_plus_rbx_scale4_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
}
int32_t backend_enc_load_32_from_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_load_32_from_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_load_32_from_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_load_32_from_rax(elf_ctx);
}
int32_t backend_enc_add_imm_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t imm, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_add_imm_to_rax(elf_ctx, imm);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_add_imm_to_rax(elf_ctx, imm);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_add_imm_to_rax(elf_ctx, imm);
}
int32_t backend_enc_load_64_from_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_load_64_from_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_load_64_from_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_load_64_from_rax(elf_ctx);
}
int32_t backend_enc_store_rax_to_rbx_offset_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t offset, int32_t store_size, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
}
int32_t backend_enc_mov_rbx_to_rax_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_rbx_to_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_rbx_to_rax(elf_ctx);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_rbx_to_rax(elf_ctx);
}
int32_t backend_enc_jz_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_jz(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_jz(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_jz(elf_ctx, label, label_len);
}
int32_t backend_enc_jnz_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_jnz(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_jnz(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_jnz(elf_ctx, label, label_len);
}
int32_t backend_enc_jmp_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_jmp(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_jmp(elf_ctx, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_jmp(elf_ctx, label, label_len);
}
int32_t backend_enc_mov_rax_to_arg_reg_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t k, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
}
int32_t backend_enc_call_arch(struct platform_elf_ElfCodegenCtx * elf_ctx, uint8_t name[64], int32_t name_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_enc_enc_call(elf_ctx, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_enc_enc_call(elf_ctx, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_enc_enc_call(elf_ctx, name, name_len);
}
void backend_ctx_reset(struct backend_AsmFuncCtx * ctx) {
  (void)(((ctx)->frame_size = 0));
  (void)(((ctx)->next_offset = 0));
  (void)(((ctx)->num_locals = 0));
  (void)(((ctx)->label_counter = 0));
  (void)(((ctx)->break_len = 0));
  (void)(((ctx)->continue_len = 0));
}
int32_t backend_compute_frame_size(struct ast_Block * block) {
  int32_t n = (block)->num_consts + (block)->num_lets;
  int32_t size = 0;
  (void)(({ int32_t __tmp = 0; if (n > 0) {   (void)((size = n * 8));
  __tmp = ({ int32_t __tmp = 0; if ((16 == 0 ? (shulang_panic_(1, 0), size) : (size % 16)) != 0) {   (void)((size = size + 16 - (16 == 0 ? (shulang_panic_(1, 0), size) : (size % 16))));
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)((size = size + 64));
  return size;
}
void backend_fill_local_slots(struct backend_AsmFuncCtx * ctx, struct ast_Block * block) {
  int32_t off = 8;
  int32_t i = 0;
  while (i < (block)->num_consts && (ctx)->num_locals < 24) {
    struct ast_ConstDecl d = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->const_decls)[0]) : ((block)->const_decls)[i]);
    int32_t idx = (ctx)->num_locals;
    int32_t k = 0;
    (void)(((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), 0) : (((ctx)->locals)[idx].name_len = (d).name_len, 0))));
    (void)(((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), 0) : (((ctx)->locals)[idx].offset = off, 0))));
    (void)(((ctx)->num_locals = (ctx)->num_locals + 1));
    (void)((off = off + 8));
    (void)((i = i + 1));
    while (k < (d).name_len && k < 64) {
      uint8_t ch = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), ((d).name)[0]) : ((d).name)[k]);
      (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : ((((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).name)[k] = ch, 0))));
      (void)((k = k + 1));
    }
  }
  while (i < (block)->num_lets && (ctx)->num_locals < 24) {
    struct ast_LetDecl d = (i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->let_decls)[0]) : ((block)->let_decls)[i]);
    int32_t idx = (ctx)->num_locals;
    int32_t k = 0;
    (void)(((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), 0) : (((ctx)->locals)[idx].name_len = (d).name_len, 0))));
    (void)(((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), 0) : (((ctx)->locals)[idx].offset = off, 0))));
    (void)(((ctx)->num_locals = (ctx)->num_locals + 1));
    (void)((off = off + 8));
    (void)((i = i + 1));
    while (k < (d).name_len && k < 64) {
      uint8_t ch = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), ((d).name)[0]) : ((d).name)[k]);
      (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : ((((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).name)[k] = ch, 0))));
      (void)((k = k + 1));
    }
  }
  (void)((i = 0));
  (void)(((ctx)->next_offset = off));
}
int32_t backend_local_offset(struct backend_AsmFuncCtx * ctx, uint8_t * name, int32_t name_len) {
  int32_t i = 0;
  while (i < (ctx)->num_locals) {
    (void)(({ int32_t __tmp = 0; if (((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[i])).name_len == name_len) {   int32_t eq = 1;
  int32_t k = 0;
  while (k < name_len && eq != 0) {
    (void)(({ int32_t __tmp = 0; if ((name)[k] != (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[i])).name)[0]) : (((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[i])).name)[k])) {   (void)((eq = 0));
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  __tmp = ({ int32_t __tmp = 0; if (eq != 0) {   return ((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[i])).offset;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return (-1);
}
int32_t backend_arch_emit_ret_imm32(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_ret_imm32(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_ret_imm32(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_ret_imm32(out, imm);
}
int32_t backend_arch_emit_mov_imm64_to_rax(struct codegen_CodegenOutBuf * out, int32_t lo, int32_t hi, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_mov_imm64_to_rax(out, lo, hi);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_imm64_to_rax(out, lo, hi);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_imm64_to_rax(out, lo, hi);
}
int32_t backend_arch_emit_mov_imm32_to_rbx(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_mov_imm32_to_rbx(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_imm32_to_rbx(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_imm32_to_rbx(out, imm);
}
int32_t backend_arch_emit_neg_eax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_neg_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_neg_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_neg_eax(out);
}
int32_t backend_arch_emit_test_setz(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   (void)(({ int32_t __tmp = 0; if (arch_arm64_emit_test_eax_eax(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_emit_setz_movzbl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   (void)(({ int32_t __tmp = 0; if (arch_riscv64_emit_test_eax_eax(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_riscv64_emit_setz_movzbl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_emit_test_eax_eax(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_setz_movzbl_eax(out);
}
int32_t backend_arch_emit_cmp_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_cmp_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_cmp_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_cmp_rbx_rax(out);
}
int32_t backend_arch_emit_cmp_setcc(struct codegen_CodegenOutBuf * out, int32_t cc, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_cmp_setcc(out, cc);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_cmp_setcc(out, cc);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_cmp_setcc(out, cc);
}
int32_t backend_arch_emit_push_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_push_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_push_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_push_rax(out);
}
int32_t backend_arch_emit_pop_rbx(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_pop_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_pop_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_pop_rbx(out);
}
int32_t backend_arch_emit_pop_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_pop_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_pop_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_pop_rax(out);
}
int32_t backend_arch_emit_add_rax_rbx(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_add_rax_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_add_rax_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_add_rax_rbx(out);
}
int32_t backend_arch_emit_sub_rbx_rax_then_mov(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_sub_rbx_rax_then_mov(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_sub_rbx_rax_then_mov(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_sub_rbx_rax_then_mov(out);
}
int32_t backend_arch_emit_imul_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_imul_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_imul_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_imul_rbx_rax(out);
}
int32_t backend_arch_emit_mov_rax_to_rbx(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_mov_rax_to_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_rax_to_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_rax_to_rbx(out);
}
int32_t backend_arch_emit_idiv_rbx(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_idiv_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_idiv_rbx(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_emit_cltd(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_idiv_rbx(out);
}
int32_t backend_arch_emit_rem_mod(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_rem_w0_w1(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_rem_w0_w1(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_emit_cltd(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (arch_x86_64_emit_idiv_rbx(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_edx_to_eax(out);
}
int32_t backend_arch_emit_load_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_load_rbp_to_rax(out, off);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_load_rbp_to_rax(out, off);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_load_rbp_to_rax(out, off);
}
int32_t backend_arch_emit_store_rax_to_rbp(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_store_rax_to_rbp(out, off);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_store_rax_to_rbp(out, off);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_store_rax_to_rbp(out, off);
}
int32_t backend_arch_emit_lea_rbp_to_rax(struct codegen_CodegenOutBuf * out, int32_t off, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_lea_rbp_to_rax(out, off);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_lea_rbp_to_rax(out, off);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_lea_rbp_to_rax(out, off);
}
int32_t backend_arch_emit_rax_plus_rbx_scale4(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_rax_plus_rbx_scale4(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_rax_plus_rbx_scale4(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_rax_plus_rbx_scale4(out);
}
int32_t backend_arch_emit_load_32_from_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_load_32_from_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_load_32_from_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_load_32_from_rax(out);
}
int32_t backend_arch_emit_add_imm_to_rax(struct codegen_CodegenOutBuf * out, int32_t imm, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_add_imm_to_rax(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_add_imm_to_rax(out, imm);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_add_imm_to_rax(out, imm);
}
int32_t backend_arch_emit_load_64_from_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_load_64_from_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_load_64_from_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_load_64_from_rax(out);
}
int32_t backend_arch_emit_store_rax_to_rbx_offset(struct codegen_CodegenOutBuf * out, int32_t offset, int32_t store_size, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_store_rax_to_rbx_offset(out, offset, store_size);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_store_rax_to_rbx_offset(out, offset, store_size);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_store_rax_to_rbx_offset(out, offset, store_size);
}
int32_t backend_arch_emit_mov_rbx_to_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_mov_rbx_to_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_rbx_to_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_rbx_to_rax(out);
}
int32_t backend_arch_emit_mov_rax_to_arg_reg(struct codegen_CodegenOutBuf * out, int32_t k, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_rax_to_arg_reg(out, k);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_rax_to_arg_reg(out, k);
}
int32_t backend_arch_emit_ldr_sp_offset_to_wi(struct codegen_CodegenOutBuf * out, int32_t i, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta != 1) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_emit_ldr_sp_offset_to_wi(out, i);
}
int32_t backend_arch_emit_add_sp_imm(struct codegen_CodegenOutBuf * out, int32_t n, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta != 1) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return arch_arm64_emit_add_sp_imm(out, n);
}
int32_t backend_emit_expr_call(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  struct ast_Expr callee = ast_ast_arena_expr_get(arena, (e).call_callee_ref);
  int32_t nargs = (e).call_num_args;
  (void)(({ int32_t __tmp = 0; if ((callee).kind != ast_ExprKind_EXPR_VAR) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (nargs > 6) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (nargs > 0) {   int32_t i = 0;
  while (i < nargs) {
    int32_t arg_ref = 0;
    (void)(({ int32_t __tmp = 0; if (i == 0) {   (void)((arg_ref = ((e).call_arg_refs)[0]));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 1) {   (void)((arg_ref = (1 < 0 || (1) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[1])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 2) {   (void)((arg_ref = (2 < 0 || (2) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[2])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 3) {   (void)((arg_ref = (3 < 0 || (3) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[3])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 4) {   (void)((arg_ref = (4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[4])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 5) {   (void)((arg_ref = (5 < 0 || (5) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[5])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arg_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, arg_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (target_arch == 0 || target_arch == 2) {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_arg_reg(out, i, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  __tmp = ({ int32_t __tmp = 0; if (target_arch == 1) {   int32_t j = 0;
  while (j < nargs) {
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ldr_sp_offset_to_wi(out, j, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_add_sp_imm(out, nargs * 16, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_call(out, (callee).var_name, (callee).var_name_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t backend_emit_expr_method_call(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  int32_t nargs = (e).method_call_num_args;
  int32_t i = 0;
  while (i < nargs && i < 6) {
    int32_t arg_ref = 0;
    (void)(({ int32_t __tmp = 0; if (i == 0) {   (void)((arg_ref = ((e).method_call_arg_refs)[0]));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 1) {   (void)((arg_ref = (1 < 0 || (1) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[1])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 2) {   (void)((arg_ref = (2 < 0 || (2) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[2])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 3) {   (void)((arg_ref = (3 < 0 || (3) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[3])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 4) {   (void)((arg_ref = (4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[4])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arg_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, arg_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (target_arch == 0 || target_arch == 2) {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_arg_reg(out, i + 1, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (nargs > 5) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).method_call_base_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).method_call_base_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (target_arch == 0 || target_arch == 2) {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_arg_reg(out, 0, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (target_arch == 1) {   int32_t total = 1 + nargs;
  int32_t j = 0;
  while (j < total) {
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ldr_sp_offset_to_wi(out, j, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_add_sp_imm(out, total * 16, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_call(out, (e).method_call_name, (e).method_call_name_len, target_arch);
}
int32_t backend_emit_expr_elf_method_call(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  int32_t nargs = (e).method_call_num_args;
  int32_t i = 0;
  while (i < nargs && i < 6) {
    int32_t arg_ref = 0;
    (void)(({ int32_t __tmp = 0; if (i == 0) {   (void)((arg_ref = ((e).method_call_arg_refs)[0]));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 1) {   (void)((arg_ref = (1 < 0 || (1) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[1])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 2) {   (void)((arg_ref = (2 < 0 || (2) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[2])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 3) {   (void)((arg_ref = (3 < 0 || (3) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[3])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 4) {   (void)((arg_ref = (4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), ((e).method_call_arg_refs)[0]) : ((e).method_call_arg_refs)[4])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arg_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, arg_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, i + 1, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (nargs > 5) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).method_call_base_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).method_call_base_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_call_arch(elf_ctx, (e).method_call_name, (e).method_call_name_len, ta);
}
int32_t backend_emit_expr_elf_call(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Expr e, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  struct ast_Expr callee = ast_ast_arena_expr_get(arena, (e).call_callee_ref);
  int32_t nargs = (e).call_num_args;
  (void)(({ int32_t __tmp = 0; if ((callee).kind != ast_ExprKind_EXPR_VAR) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (nargs > 6) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (nargs > 0) {   int32_t i = 0;
  while (i < nargs) {
    int32_t arg_ref = 0;
    (void)(({ int32_t __tmp = 0; if (i == 0) {   (void)((arg_ref = ((e).call_arg_refs)[0]));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 1) {   (void)((arg_ref = (1 < 0 || (1) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[1])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 2) {   (void)((arg_ref = (2 < 0 || (2) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[2])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 3) {   (void)((arg_ref = (3 < 0 || (3) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[3])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 4) {   (void)((arg_ref = (4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[4])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (i == 5) {   (void)((arg_ref = (5 < 0 || (5) >= 16 ? (shulang_panic_(1, 0), ((e).call_arg_refs)[0]) : ((e).call_arg_refs)[5])));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (arg_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, arg_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, i, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_call_arch(elf_ctx, (callee).var_name, (callee).var_name_len, ta);
}
int32_t backend_arch_emit_call(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_call(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_call(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_call(out, name, name_len);
}
int32_t backend_arch_emit_jz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_jz(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_jz(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_jz(out, label, label_len);
}
int32_t backend_arch_emit_jmp(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_jmp(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_jmp(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_jmp(out, label, label_len);
}
int32_t backend_arch_emit_jnz(struct codegen_CodegenOutBuf * out, uint8_t label[64], int32_t label_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_jnz(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_jnz(out, label, label_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_jnz(out, label, label_len);
}
int32_t backend_arch_emit_not_eax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_not_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_not_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_not_eax(out);
}
int32_t backend_arch_emit_and_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_and_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_and_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_and_rbx_rax(out);
}
int32_t backend_arch_emit_or_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_or_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_or_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_or_rbx_rax(out);
}
int32_t backend_arch_emit_xor_rbx_rax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_xor_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_xor_rbx_rax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_xor_rbx_rax(out);
}
int32_t backend_arch_emit_mov_rbx_to_ecx(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_mov_rbx_to_ecx(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_mov_rbx_to_ecx(out);
}
int32_t backend_arch_emit_shl_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_shl_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_shl_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_shl_cl_eax(out);
}
int32_t backend_arch_emit_shr_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_shr_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_shr_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_shr_cl_eax(out);
}
int32_t backend_arch_emit_sar_cl_eax(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_sar_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_sar_cl_eax(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_sar_cl_eax(out);
}
int32_t backend_arch_emit_label(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_label(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_label(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_label(out, name, name_len);
}
int32_t backend_arch_emit_section_text(struct codegen_CodegenOutBuf * out, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_section_text(out);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_section_text(out);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_section_text(out);
}
int32_t backend_arch_emit_globl(struct codegen_CodegenOutBuf * out, uint8_t name[64], int32_t name_len, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_globl(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_globl(out, name, name_len);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_globl(out, name, name_len);
}
int32_t backend_arch_emit_prologue(struct codegen_CodegenOutBuf * out, int32_t frame_sz, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_prologue(out, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_prologue(out, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_prologue(out, frame_sz);
}
int32_t backend_arch_emit_epilogue(struct codegen_CodegenOutBuf * out, int32_t frame_sz, int32_t ta) {
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   return arch_arm64_emit_epilogue(out, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (ta == 2) {   return arch_riscv64_emit_epilogue(out, frame_sz);
 } else (__tmp = 0) ; __tmp; }));
  return arch_x86_64_emit_epilogue(out);
}
int32_t backend_get_return_expr_ref(struct ast_ASTArena * arena, struct ast_Func * f) {
  struct ast_Block block = ast_ast_arena_block_get(arena, (f)->body_ref);
  int32_t j = 0;
  while (j < (block).num_labeled_stmts && j < 8) {
    struct ast_LabeledStmt stmt = (j < 0 || (j) >= 8 ? (shulang_panic_(1, 0), ((block).labeled_stmts)[0]) : ((block).labeled_stmts)[j]);
    (void)(({ int32_t __tmp = 0; if ((stmt).is_goto == 0 && (stmt).return_expr_ref != 0) {   return (stmt).return_expr_ref;
 } else (__tmp = 0) ; __tmp; }));
    (void)((j = j + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((f)->body_ref == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((block).final_expr_ref != 0) {   struct ast_Expr e = ast_ast_arena_expr_get(arena, (block).final_expr_ref);
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN && (e).unary_operand_ref != 0) {   return (e).unary_operand_ref;
 } else (__tmp = 0) ; __tmp; }));
  return (block).final_expr_ref;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t backend_emit_expr(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, int32_t expr_ref, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
  (void)(({ int32_t __tmp = 0; if (expr_ref == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LIT) {   return backend_arch_emit_ret_imm32(out, (e).int_val, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BOOL_LIT) {   return backend_arch_emit_ret_imm32(out, (e).int_val, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FLOAT_LIT) {   return backend_arch_emit_mov_imm64_to_rax(out, (e).float_bits_lo, (e).float_bits_hi, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN && (e).unary_operand_ref != 0) {   return backend_emit_expr(arena, out, (e).unary_operand_ref, ctx, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_PANIC) {   uint8_t panic_name[64] = { 115, 104, 117, 108, 97, 110, 103, 95, 112, 97, 110, 105, 99, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return backend_arch_emit_call(out, panic_name, 15, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BREAK && (ctx)->break_len > 0) {   return backend_arch_emit_jmp(out, (ctx)->break_label, (ctx)->break_len, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CONTINUE && (ctx)->continue_len > 0) {   return backend_arch_emit_jmp(out, (ctx)->continue_label, (ctx)->continue_len, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NEG && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).unary_operand_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_neg_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGNOT && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).unary_operand_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_test_setz(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ADD) {   (void)(({ int32_t __tmp = 0; if ((e).binop_left_ref != 0) {   struct ast_Expr le = ast_ast_arena_expr_get(arena, (e).binop_left_ref);
  __tmp = ({ int32_t __tmp = 0; if ((le).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (le).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_add_rax_rbx(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_add_rax_rbx(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_add_rax_rbx(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SUB) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_sub_rbx_rax_then_mov(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_sub_rbx_rax_then_mov(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MUL) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_imul_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_imul_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_DIV) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_idiv_rbx(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_idiv_rbx(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MOD) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_rem_mod(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_rem_mod(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ || (e).kind == ast_ExprKind_EXPR_NE || (e).kind == ast_ExprKind_EXPR_LT || (e).kind == ast_ExprKind_EXPR_LE || (e).kind == ast_ExprKind_EXPR_GT || (e).kind == ast_ExprKind_EXPR_GE) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t cc = 0;
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ) {   (void)((cc = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NE) {   (void)((cc = 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LT) {   (void)((cc = 2));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LE) {   (void)((cc = 3));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GT) {   (void)((cc = 4));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GE) {   (void)((cc = 5));
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_cmp_setcc(out, cc, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t cc = 0;
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ) {   (void)((cc = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NE) {   (void)((cc = 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LT) {   (void)((cc = 2));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LE) {   (void)((cc = 3));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GT) {   (void)((cc = 4));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GE) {   (void)((cc = 5));
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_cmp_setcc(out, cc, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITNOT && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).unary_operand_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_not_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITAND && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_and_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_and_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_or_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_or_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITXOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_xor_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_xor_rbx_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHL && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rbx_to_ecx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_shl_cl_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rbx_to_ecx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_shl_cl_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, (re).int_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rbx_to_ecx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_shr_cl_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rbx_to_ecx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_shr_cl_eax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ASSIGN && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   struct ast_Expr left = ast_ast_arena_expr_get(arena, (e).binop_left_ref);
  (void)(({ int32_t __tmp = 0; if ((left).kind != ast_ExprKind_EXPR_VAR) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t off = backend_local_offset(ctx, (left).var_name, (left).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbp(out, off, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ struct ast_Type __tmp = (struct ast_Type){0}; if ((e).kind == ast_ExprKind_EXPR_INDEX && (e).index_base_ref != 0 && (e).index_index_ref != 0) {   struct ast_Expr base = ast_ast_arena_expr_get(arena, (e).index_base_ref);
  (void)(({ int32_t __tmp = 0; if ((base).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (base).var_name, (base).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_lea_rbp_to_rax(out, off, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).index_base_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((base).resolved_type_ref != 0) {   struct ast_Type bt = ast_ast_arena_type_get(arena, (base).resolved_type_ref);
  __tmp = ({ int32_t __tmp = 0; if ((bt).kind == ast_TypeKind_TYPE_SLICE) {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_load_64_from_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).index_index_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_rax_plus_rbx_scale4(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_load_32_from_rax(out, target_arch);
 } else (__tmp = (struct ast_Type){0}) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FIELD_ACCESS && (e).field_access_base_ref != 0) {   struct ast_Expr base = ast_ast_arena_expr_get(arena, (e).field_access_base_ref);
  (void)(({ int32_t __tmp = 0; if ((base).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (base).var_name, (base).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_lea_rbp_to_rax(out, off, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).field_access_base_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_add_imm_to_rax(out, (e).field_access_offset, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_load_64_from_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (e).var_name, (e).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_arch_emit_load_rbp_to_rax(out, off, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL) {   return backend_emit_expr_call(arena, out, e, ctx, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_METHOD_CALL && (e).method_call_name_len > 0) {   return backend_emit_expr_method_call(arena, out, e, ctx, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGAND && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   uint8_t false_buf[64] = { 46, 76, 95, 97, 110, 100, 95, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 97, 110, 100, 95, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(false_buf, 9, 8, nc);
  int32_t false_len = 9 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 9, 8, nl);
  int32_t end_len = 9 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, false_buf, false_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, false_buf, false_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ret_imm32(out, 1, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, false_buf, false_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ret_imm32(out, 0, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   uint8_t true_buf[64] = { 46, 76, 95, 111, 114, 95, 116, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 111, 114, 95, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(true_buf, 9, 8, nc);
  int32_t true_len = 9 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 9, 8, nl);
  int32_t end_len = 9 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_left_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jnz(out, true_buf, true_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).binop_right_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jnz(out, true_buf, true_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ret_imm32(out, 0, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, true_buf, true_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_ret_imm32(out, 1, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_IF && (e).if_cond_ref != 0 && (e).if_then_ref != 0) {   uint8_t else_buf[64] = { 46, 76, 95, 101, 108, 115, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 101, 110, 100, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(else_buf, 8, 8, nc);
  int32_t else_len = 8 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 7, 8, nl);
  int32_t end_len = 7 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_cond_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, else_buf, else_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_then_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, else_buf, else_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).if_else_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_else_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_TERNARY && (e).if_cond_ref != 0 && (e).if_then_ref != 0) {   uint8_t else_buf[64] = { 46, 76, 95, 101, 108, 115, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 101, 110, 100, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(else_buf, 8, 8, nc);
  int32_t else_len = 8 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 7, 8, nl);
  int32_t end_len = 7 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_cond_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, else_buf, else_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_then_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, else_buf, else_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).if_else_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).if_else_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BLOCK && (e).block_ref != 0) {   struct ast_Block inner = ast_ast_arena_block_get(arena, (e).block_ref);
  (void)(({ int32_t __tmp = 0; if (backend_emit_block_inits(arena, out, (&(inner)), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((inner).final_expr_ref != 0) {   return backend_emit_expr(arena, out, (inner).final_expr_ref, ctx, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MATCH && (e).match_matched_ref != 0 && (e).match_num_arms > 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (e).match_matched_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t base = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + (e).match_num_arms + 1));
  int32_t end_id = base + (e).match_num_arms;
  uint8_t res_buf[64] = { 0 };
  uint8_t end_buf[64] = { 0 };
  int32_t i = 0;
  while (i < (e).match_num_arms && i < 16) {
    (void)(({ int32_t __tmp = 0; if ((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_is_wildcard)[0]) : ((e).match_arm_is_wildcard)[i]) != 0) {   int32_t r_ref = (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_result_refs)[0]) : ((e).match_arm_result_refs)[i]);
  (void)(({ int32_t __tmp = 0; if (r_ref != 0 && backend_emit_expr(arena, out, r_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   int32_t cmp_val = ((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_is_enum_variant)[0]) : ((e).match_arm_is_enum_variant)[i]) != 0 ? (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_variant_index)[0]) : ((e).match_arm_variant_index)[i]) : (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_lit_val)[0]) : ((e).match_arm_lit_val)[i]));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_push_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_imm32_to_rbx(out, cmp_val, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_pop_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_cmp_rbx_rax(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t res_len = backend_format_label_id(res_buf, 64, base + i);
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, res_buf, res_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)((i = 0));
  while (i < (e).match_num_arms && i < 16) {
    int32_t res_len = backend_format_label_id(res_buf, 64, base + i);
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, res_buf, res_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t r_ref = (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_result_refs)[0]) : ((e).match_arm_result_refs)[i]);
    (void)(({ int32_t __tmp = 0; if (r_ref != 0 && backend_emit_expr(arena, out, r_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, end_buf, end_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_STRUCT_LIT && (e).struct_lit_num_fields > 0 && (e).struct_lit_num_fields <= 8) {   int32_t temp_base = (ctx)->next_offset;
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_lea_rbp_to_rax(out, temp_base, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t fi = 0;
  while (fi < (e).struct_lit_num_fields && fi < 8) {
    int32_t init_ref = (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi]);
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbx_offset(out, fi * 8, 8, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((fi = fi + 1));
  }
  return backend_arch_emit_mov_rbx_to_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ARRAY_LIT && (e).array_lit_num_elems > 0 && (e).array_lit_num_elems <= 16) {   int32_t temp_base = (ctx)->next_offset;
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_lea_rbp_to_rax(out, temp_base, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_mov_rax_to_rbx(out, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t ai = 0;
  while (ai < (e).array_lit_num_elems && ai < 16) {
    int32_t elem_ref = (ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).array_lit_elem_refs)[0]) : ((e).array_lit_elem_refs)[ai]);
    (void)(({ int32_t __tmp = 0; if (elem_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, elem_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbx_offset(out, ai * 4, 4, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((ai = ai + 1));
  }
  return backend_arch_emit_mov_rbx_to_rax(out, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ENUM_VARIANT) {   return backend_arch_emit_ret_imm32(out, (e).enum_variant_tag, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).const_folded_valid != 0) {   return backend_arch_emit_ret_imm32(out, (e).const_folded_val, target_arch);
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t backend_emit_expr_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, int32_t expr_ref, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
  (void)(({ int32_t __tmp = 0; if (expr_ref == 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LIT) {   return backend_enc_ret_imm32_arch(elf_ctx, (e).int_val, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BOOL_LIT) {   return backend_enc_ret_imm32_arch(elf_ctx, (e).int_val, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FLOAT_LIT) {   return backend_enc_mov_imm64_to_rax_arch(elf_ctx, (e).float_bits_lo, (e).float_bits_hi, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_RETURN && (e).unary_operand_ref != 0) {   return backend_emit_expr_elf(arena, elf_ctx, (e).unary_operand_ref, ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_PANIC) {   uint8_t panic_name[64] = { 115, 104, 117, 108, 97, 110, 103, 95, 112, 97, 110, 105, 99, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  return backend_enc_call_arch(elf_ctx, panic_name, 15, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NEG && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).unary_operand_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_neg_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGNOT && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).unary_operand_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_setz_movzbl_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ADD) {   (void)(({ int32_t __tmp = 0; if ((e).binop_left_ref != 0) {   struct ast_Expr le = ast_ast_arena_expr_get(arena, (e).binop_left_ref);
  __tmp = ({ int32_t __tmp = 0; if ((le).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (le).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_add_rax_rbx_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_add_rax_rbx_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_add_rax_rbx_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SUB) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_sub_rbx_rax_then_mov_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_sub_rbx_rax_then_mov_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MUL) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_imul_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_imul_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_DIV) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_idiv_rbx_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_idiv_rbx_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MOD) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_cltd_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_idiv_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_cltd_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_idiv_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ || (e).kind == ast_ExprKind_EXPR_NE || (e).kind == ast_ExprKind_EXPR_LT || (e).kind == ast_ExprKind_EXPR_LE || (e).kind == ast_ExprKind_EXPR_GT || (e).kind == ast_ExprKind_EXPR_GE) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_cmp_rbx_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t cc = 0;
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ) {   (void)((cc = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NE) {   (void)((cc = 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LT) {   (void)((cc = 2));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LE) {   (void)((cc = 3));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GT) {   (void)((cc = 4));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GE) {   (void)((cc = 5));
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_cmp_setcc_movzbl_arch(elf_ctx, cc, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_cmp_rbx_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t cc = 0;
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_EQ) {   (void)((cc = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_NE) {   (void)((cc = 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LT) {   (void)((cc = 2));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LE) {   (void)((cc = 3));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GT) {   (void)((cc = 4));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_GE) {   (void)((cc = 5));
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_cmp_setcc_movzbl_arch(elf_ctx, cc, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITNOT && (e).unary_operand_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).unary_operand_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_not_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITAND && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_and_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_and_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_or_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_or_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BITXOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_xor_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_xor_rbx_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHL && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rbx_to_ecx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_shl_cl_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rbx_to_ecx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_shl_cl_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_SHR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   (void)(({ int32_t __tmp = 0; if ((e).binop_right_ref != 0) {   struct ast_Expr re = ast_ast_arena_expr_get(arena, (e).binop_right_ref);
  __tmp = ({ int32_t __tmp = 0; if ((re).kind == ast_ExprKind_EXPR_LIT) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, (re).int_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rbx_to_ecx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_shr_cl_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rbx_to_ecx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_shr_cl_eax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGAND && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   uint8_t false_buf[64] = { 46, 76, 95, 97, 110, 100, 95, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 97, 110, 100, 95, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(false_buf, 9, 8, nc);
  int32_t false_len = 9 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 9, 8, nl);
  int32_t end_len = 9 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, false_buf, false_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, false_buf, false_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_ret_imm32_arch(elf_ctx, 1, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(elf_ctx, false_buf, false_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_ret_imm32_arch(elf_ctx, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(elf_ctx, end_buf, end_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_LOGOR && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   uint8_t true_buf[64] = { 46, 76, 95, 111, 114, 95, 116, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 111, 114, 95, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(true_buf, 9, 8, nc);
  int32_t true_len = 9 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 9, 8, nl);
  int32_t end_len = 9 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_left_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jnz_arch(elf_ctx, true_buf, true_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jnz_arch(elf_ctx, true_buf, true_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_ret_imm32_arch(elf_ctx, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(elf_ctx, true_buf, true_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_ret_imm32_arch(elf_ctx, 1, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_add_label(elf_ctx, end_buf, end_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ASSIGN && (e).binop_left_ref != 0 && (e).binop_right_ref != 0) {   struct ast_Expr left = ast_ast_arena_expr_get(arena, (e).binop_left_ref);
  (void)(({ int32_t __tmp = 0; if ((left).kind != ast_ExprKind_EXPR_VAR) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t off = backend_local_offset(ctx, (left).var_name, (left).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).binop_right_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_store_rax_to_rbp_arch(elf_ctx, off, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ struct ast_Type __tmp = (struct ast_Type){0}; if ((e).kind == ast_ExprKind_EXPR_INDEX && (e).index_base_ref != 0 && (e).index_index_ref != 0) {   struct ast_Expr base = ast_ast_arena_expr_get(arena, (e).index_base_ref);
  (void)(({ int32_t __tmp = 0; if ((base).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (base).var_name, (base).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).index_base_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((base).resolved_type_ref != 0) {   struct ast_Type bt = ast_ast_arena_type_get(arena, (base).resolved_type_ref);
  __tmp = ({ int32_t __tmp = 0; if ((bt).kind == ast_TypeKind_TYPE_SLICE) {   __tmp = ({ int32_t __tmp = 0; if (backend_enc_load_64_from_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).index_index_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_rax_plus_rbx_scale4_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_load_32_from_rax_arch(elf_ctx, ta);
 } else (__tmp = (struct ast_Type){0}) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_FIELD_ACCESS && (e).field_access_base_ref != 0) {   struct ast_Expr base = ast_ast_arena_expr_get(arena, (e).field_access_base_ref);
  (void)(({ int32_t __tmp = 0; if ((base).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (base).var_name, (base).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).field_access_base_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_add_imm_to_rax_arch(elf_ctx, (e).field_access_offset, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_load_64_from_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_VAR) {   int32_t off = backend_local_offset(ctx, (e).var_name, (e).var_name_len);
  (void)(({ int32_t __tmp = 0; if (off < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return backend_enc_load_rbp_to_rax_arch(elf_ctx, off, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_CALL) {   return backend_emit_expr_elf_call(arena, elf_ctx, e, ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_METHOD_CALL && (e).method_call_name_len > 0) {   return backend_emit_expr_elf_method_call(arena, elf_ctx, e, ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_IF && (e).if_cond_ref != 0 && (e).if_then_ref != 0) {   uint8_t else_buf[64] = { 46, 76, 95, 101, 108, 115, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 101, 110, 100, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(else_buf, 8, 8, nc);
  int32_t else_len = 8 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 7, 8, nl);
  int32_t end_len = 7 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_cond_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, else_buf, else_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_then_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, else_buf, else_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).if_else_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_else_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, end_buf, end_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_TERNARY && (e).if_cond_ref != 0 && (e).if_then_ref != 0) {   uint8_t else_buf[64] = { 46, 76, 95, 101, 108, 115, 101, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t end_buf[64] = { 46, 76, 95, 101, 110, 100, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int32_t nc = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t nl = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  int32_t n1 = types_format_i32_to_buf(else_buf, 8, 8, nc);
  int32_t else_len = 8 + (n1 > 0 ? n1 : 1);
  int32_t n2 = types_format_i32_to_buf(end_buf, 7, 8, nl);
  int32_t end_len = 7 + (n2 > 0 ? n2 : 1);
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_cond_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, else_buf, else_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_then_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, else_buf, else_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).if_else_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).if_else_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, end_buf, end_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_BLOCK && (e).block_ref != 0) {   struct ast_Block inner = ast_ast_arena_block_get(arena, (e).block_ref);
  (void)(({ int32_t __tmp = 0; if (backend_emit_block_inits_elf(arena, elf_ctx, (&(inner)), ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((inner).final_expr_ref != 0) {   return backend_emit_expr_elf(arena, elf_ctx, (inner).final_expr_ref, ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_MATCH && (e).match_matched_ref != 0 && (e).match_num_arms > 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (e).match_matched_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t base = (ctx)->label_counter;
  (void)(((ctx)->label_counter = (ctx)->label_counter + (e).match_num_arms + 1));
  int32_t end_id = base + (e).match_num_arms;
  uint8_t res_buf[64] = { 0 };
  uint8_t end_buf[64] = { 0 };
  int32_t i = 0;
  while (i < (e).match_num_arms && i < 16) {
    (void)(({ int32_t __tmp = 0; if ((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_is_wildcard)[0]) : ((e).match_arm_is_wildcard)[i]) != 0) {   int32_t r_ref = (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_result_refs)[0]) : ((e).match_arm_result_refs)[i]);
  (void)(({ int32_t __tmp = 0; if (r_ref != 0 && backend_emit_expr_elf(arena, elf_ctx, r_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   int32_t cmp_val = ((i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_is_enum_variant)[0]) : ((e).match_arm_is_enum_variant)[i]) != 0 ? (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_variant_index)[0]) : ((e).match_arm_variant_index)[i]) : (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_lit_val)[0]) : ((e).match_arm_lit_val)[i]));
  (void)(({ int32_t __tmp = 0; if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, cmp_val, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_pop_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_cmp_rbx_rax_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t res_len = backend_format_label_id(res_buf, 64, base + i);
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, res_buf, res_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)((i = 0));
  while (i < (e).match_num_arms && i < 16) {
    int32_t res_len = backend_format_label_id(res_buf, 64, base + i);
    (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, res_buf, res_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t r_ref = (i < 0 || (i) >= 16 ? (shulang_panic_(1, 0), ((e).match_arm_result_refs)[0]) : ((e).match_arm_result_refs)[i]);
    (void)(({ int32_t __tmp = 0; if (r_ref != 0 && backend_emit_expr_elf(arena, elf_ctx, r_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
    (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, end_buf, end_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  int32_t end_len = backend_format_label_id(end_buf, 64, end_id);
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, end_buf, end_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_STRUCT_LIT && (e).struct_lit_num_fields > 0 && (e).struct_lit_num_fields <= 8) {   int32_t temp_base = (ctx)->next_offset;
  (void)(({ int32_t __tmp = 0; if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, temp_base, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t fi = 0;
  while (fi < (e).struct_lit_num_fields && fi < 8) {
    int32_t init_ref = (fi < 0 || (fi) >= 8 ? (shulang_panic_(1, 0), ((e).struct_lit_init_refs)[0]) : ((e).struct_lit_init_refs)[fi]);
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, fi * 8, 8, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((fi = fi + 1));
  }
  return backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ARRAY_LIT && (e).array_lit_num_elems > 0 && (e).array_lit_num_elems <= 16) {   int32_t temp_base = (ctx)->next_offset;
  (void)(({ int32_t __tmp = 0; if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, temp_base, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t ai = 0;
  while (ai < (e).array_lit_num_elems && ai < 16) {
    int32_t elem_ref = (ai < 0 || (ai) >= 16 ? (shulang_panic_(1, 0), ((e).array_lit_elem_refs)[0]) : ((e).array_lit_elem_refs)[ai]);
    (void)(({ int32_t __tmp = 0; if (elem_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, elem_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, ai * 4, 4, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((ai = ai + 1));
  }
  return backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).kind == ast_ExprKind_EXPR_ENUM_VARIANT) {   return backend_enc_ret_imm32_arch(elf_ctx, (e).enum_variant_tag, ta);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((e).const_folded_valid != 0) {   return backend_enc_ret_imm32_arch(elf_ctx, (e).const_folded_val, ta);
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t backend_emit_block_inits_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  int32_t idx = 0;
  int32_t i = 0;
  while (i < (block)->num_consts && idx < (ctx)->num_locals) {
    int32_t init_ref = ((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->const_decls)[0]) : ((block)->const_decls)[i])).init_ref;
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((idx = idx + 1));
    (void)((i = i + 1));
  }
  while (i < (block)->num_lets && idx < (ctx)->num_locals) {
    int32_t init_ref = ((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->let_decls)[0]) : ((block)->let_decls)[i])).init_ref;
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((idx = idx + 1));
    (void)((i = i + 1));
  }
  (void)((i = 0));
  return 0;
}
int32_t backend_emit_while_loop_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_WhileLoop * wloop, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  uint8_t loop_buf[64] = { 0 };
  uint8_t exit_buf[64] = { 0 };
  int32_t loop_len = backend_emit_next_label(ctx, loop_buf, 20);
  int32_t exit_len = backend_emit_next_label(ctx, exit_buf, 20);
  struct ast_Block body_block = ast_ast_arena_block_get(arena, (wloop)->body_ref);
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, loop_buf, loop_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (wloop)->cond_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, exit_buf, exit_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((body_block).final_expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (body_block).final_expr_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, loop_buf, loop_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, exit_buf, exit_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t backend_emit_for_loop_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_ForLoop * floop, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  uint8_t loop_buf[64] = { 0 };
  uint8_t exit_buf[64] = { 0 };
  int32_t loop_len = backend_emit_next_label(ctx, loop_buf, 20);
  int32_t exit_len = backend_emit_next_label(ctx, exit_buf, 20);
  struct ast_Block body_block = ast_ast_arena_block_get(arena, (floop)->body_ref);
  (void)(({ int32_t __tmp = 0; if ((floop)->init_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (floop)->init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, loop_buf, loop_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((floop)->cond_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (floop)->cond_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_jz_arch(elf_ctx, exit_buf, exit_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((body_block).final_expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (body_block).final_expr_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((floop)->step_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, (floop)->step_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_jmp_arch(elf_ctx, loop_buf, loop_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, exit_buf, exit_len, 0, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t backend_emit_block_body_elf(struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t ta) {
  int32_t i = 0;
  while (i < (block)->num_stmt_order && i < 96) {
    struct ast_StmtOrderItem item = (i < 0 || (i) >= 96 ? (shulang_panic_(1, 0), ((block)->stmt_order)[0]) : ((block)->stmt_order)[i]);
    (void)(({ int32_t __tmp = 0; if ((item).kind == 0) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_consts && idx < (ctx)->num_locals) {   int32_t init_ref = ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((block)->const_decls)[0]) : ((block)->const_decls)[idx])).init_ref;
  __tmp = ({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 1) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_lets) {   int32_t slot = (block)->num_consts + idx;
  __tmp = ({ int32_t __tmp = 0; if (slot < (ctx)->num_locals) {   int32_t init_ref = ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((block)->let_decls)[0]) : ((block)->let_decls)[idx])).init_ref;
  __tmp = ({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, init_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ((slot < 0 || (slot) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[slot])).offset, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 2) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_expr_stmts) {   int32_t expr_ref = (idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((block)->expr_stmt_refs)[0]) : ((block)->expr_stmt_refs)[idx]);
  __tmp = ({ int32_t __tmp = 0; if (expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, expr_ref, ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 3) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_while_loop_elf(arena, elf_ctx, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->loops)[0]) : &((block)->loops)[idx]), ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 4) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_for_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_for_loop_elf(arena, elf_ctx, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->for_loops)[0]) : &((block)->for_loops)[idx]), ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t backend_emit_block_inits(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  int32_t idx = 0;
  int32_t i = 0;
  while (i < (block)->num_consts && idx < (ctx)->num_locals) {
    int32_t init_ref = ((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->const_decls)[0]) : ((block)->const_decls)[i])).init_ref;
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbp(out, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((idx = idx + 1));
    (void)((i = i + 1));
  }
  while (i < (block)->num_lets && idx < (ctx)->num_locals) {
    int32_t init_ref = ((i < 0 || (i) >= 24 ? (shulang_panic_(1, 0), ((block)->let_decls)[0]) : ((block)->let_decls)[i])).init_ref;
    (void)(({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbp(out, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((idx = idx + 1));
    (void)((i = i + 1));
  }
  (void)((i = 0));
  return 0;
}
int32_t backend_emit_next_label(struct backend_AsmFuncCtx * ctx, uint8_t * buf, int32_t buf_size) {
  int32_t n = types_format_i32_to_buf(buf, 3, buf_size - 3, (ctx)->label_counter);
  (void)(((buf)[0] = 46));
  (void)(((buf)[1] = 76));
  (void)(((buf)[2] = 95));
  (void)(((ctx)->label_counter = (ctx)->label_counter + 1));
  (void)(({ int32_t __tmp = 0; if (n <= 0) {   (void)((n = 1));
 } else (__tmp = 0) ; __tmp; }));
  return 3 + n;
}
int32_t backend_format_label_id(uint8_t * buf, int32_t buf_size, int32_t id) {
  int32_t n = types_format_i32_to_buf(buf, 3, buf_size - 3, id);
  (void)(((buf)[0] = 46));
  (void)(((buf)[1] = 76));
  (void)(((buf)[2] = 95));
  (void)(({ int32_t __tmp = 0; if (n <= 0) {   (void)((n = 1));
 } else (__tmp = 0) ; __tmp; }));
  return 3 + n;
}
void backend_ctx_set_loop_labels(struct backend_AsmFuncCtx * ctx, uint8_t * exit_buf, int32_t exit_len, uint8_t * loop_buf, int32_t loop_len) {
  int32_t k = 0;
  while (k < exit_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((ctx)->break_label)[k] = (exit_buf)[k], 0))));
    (void)((k = k + 1));
  }
  while (k < loop_len && k < 64) {
    (void)(((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), 0) : (((ctx)->continue_label)[k] = (loop_buf)[k], 0))));
    (void)((k = k + 1));
  }
  (void)(((ctx)->break_len = exit_len));
  (void)((k = 0));
  (void)(((ctx)->continue_len = loop_len));
}
int32_t backend_emit_loop_body_content(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  int32_t i = 0;
  while (i < (block)->num_stmt_order && i < 96) {
    struct ast_StmtOrderItem item = (i < 0 || (i) >= 96 ? (shulang_panic_(1, 0), ((block)->stmt_order)[0]) : ((block)->stmt_order)[i]);
    (void)(({ int32_t __tmp = 0; if ((item).kind == 2) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_expr_stmts) {   int32_t expr_ref = (idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((block)->expr_stmt_refs)[0]) : ((block)->expr_stmt_refs)[idx]);
  __tmp = ({ int32_t __tmp = 0; if (expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, expr_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 3) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_while_loop(arena, out, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->loops)[0]) : &((block)->loops)[idx]), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 4) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_for_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_for_loop(arena, out, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->for_loops)[0]) : &((block)->for_loops)[idx]), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; })) ; __tmp; })) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((block)->final_expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (block)->final_expr_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t backend_emit_while_loop(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_WhileLoop * wloop, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  uint8_t loop_buf[64] = { 0 };
  uint8_t exit_buf[64] = { 0 };
  int32_t loop_len = backend_emit_next_label(ctx, loop_buf, 20);
  int32_t exit_len = backend_emit_next_label(ctx, exit_buf, 20);
  struct ast_Block body_block = ast_ast_arena_block_get(arena, (wloop)->body_ref);
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, loop_buf, loop_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (wloop)->cond_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, exit_buf, exit_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(backend_ctx_set_loop_labels(ctx, exit_buf, exit_len, loop_buf, loop_len));
  (void)(({ int32_t __tmp = 0; if (backend_emit_loop_body_content(arena, out, (&(body_block)), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, loop_buf, loop_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, exit_buf, exit_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ctx)->break_len = 0));
  (void)(((ctx)->continue_len = 0));
  return 0;
}
int32_t backend_emit_for_loop(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_ForLoop * floop, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  uint8_t loop_buf[64] = { 0 };
  uint8_t exit_buf[64] = { 0 };
  int32_t loop_len = backend_emit_next_label(ctx, loop_buf, 20);
  int32_t exit_len = backend_emit_next_label(ctx, exit_buf, 20);
  struct ast_Block body_block = ast_ast_arena_block_get(arena, (floop)->body_ref);
  (void)(({ int32_t __tmp = 0; if ((floop)->init_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (floop)->init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, loop_buf, loop_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((floop)->cond_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (floop)->cond_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_jz(out, exit_buf, exit_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(backend_ctx_set_loop_labels(ctx, exit_buf, exit_len, loop_buf, loop_len));
  (void)(({ int32_t __tmp = 0; if (backend_emit_loop_body_content(arena, out, (&(body_block)), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((floop)->step_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, (floop)->step_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_jmp(out, loop_buf, loop_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, exit_buf, exit_len, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ctx)->break_len = 0));
  (void)(((ctx)->continue_len = 0));
  return 0;
}
int32_t backend_emit_block_body(struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_Block * block, struct backend_AsmFuncCtx * ctx, int32_t target_arch) {
  int32_t i = 0;
  while (i < (block)->num_stmt_order && i < 96) {
    struct ast_StmtOrderItem item = (i < 0 || (i) >= 96 ? (shulang_panic_(1, 0), ((block)->stmt_order)[0]) : ((block)->stmt_order)[i]);
    (void)(({ int32_t __tmp = 0; if ((item).kind == 0) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_consts && idx < (ctx)->num_locals) {   int32_t init_ref = ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((block)->const_decls)[0]) : ((block)->const_decls)[idx])).init_ref;
  __tmp = ({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbp(out, ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[idx])).offset, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 1) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_lets) {   int32_t slot = (block)->num_consts + idx;
  __tmp = ({ int32_t __tmp = 0; if (slot < (ctx)->num_locals) {   int32_t init_ref = ((idx < 0 || (idx) >= 24 ? (shulang_panic_(1, 0), ((block)->let_decls)[0]) : ((block)->let_decls)[idx])).init_ref;
  __tmp = ({ int32_t __tmp = 0; if (init_ref != 0) {   (void)(({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, init_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_store_rax_to_rbp(out, ((slot < 0 || (slot) >= 24 ? (shulang_panic_(1, 0), ((ctx)->locals)[0]) : ((ctx)->locals)[slot])).offset, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 2) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_expr_stmts) {   int32_t expr_ref = (idx < 0 || (idx) >= 32 ? (shulang_panic_(1, 0), ((block)->expr_stmt_refs)[0]) : ((block)->expr_stmt_refs)[idx]);
  __tmp = ({ int32_t __tmp = 0; if (expr_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, expr_ref, ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 3) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_while_loop(arena, out, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->loops)[0]) : &((block)->loops)[idx]), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((item).kind == 4) {   int32_t idx = (item).idx;
  __tmp = ({ int32_t __tmp = 0; if (idx < (block)->num_for_loops) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_for_loop(arena, out, (idx < 0 || (idx) >= 8 ? (shulang_panic_(1, 0), &((block)->for_loops)[0]) : &((block)->for_loops)[idx]), ctx, target_arch) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; })) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t backend_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_PipelineDepCtx * pipeline_ctx) {
  int32_t ta = (pipeline_ctx)->target_arch;
  struct backend_LocalSlot z = ({ struct backend_LocalSlot _t = { 0 }; _t.name[0] = 0; _t.name[1] = 0; _t.name[2] = 0; _t.name[3] = 0; _t.name[4] = 0; _t.name[5] = 0; _t.name[6] = 0; _t.name[7] = 0; _t.name[8] = 0; _t.name[9] = 0; _t.name[10] = 0; _t.name[11] = 0; _t.name[12] = 0; _t.name[13] = 0; _t.name[14] = 0; _t.name[15] = 0; _t.name[16] = 0; _t.name[17] = 0; _t.name[18] = 0; _t.name[19] = 0; _t.name[20] = 0; _t.name[21] = 0; _t.name[22] = 0; _t.name[23] = 0; _t.name[24] = 0; _t.name[25] = 0; _t.name[26] = 0; _t.name[27] = 0; _t.name[28] = 0; _t.name[29] = 0; _t.name[30] = 0; _t.name[31] = 0; _t.name[32] = 0; _t.name[33] = 0; _t.name[34] = 0; _t.name[35] = 0; _t.name[36] = 0; _t.name[37] = 0; _t.name[38] = 0; _t.name[39] = 0; _t.name[40] = 0; _t.name[41] = 0; _t.name[42] = 0; _t.name[43] = 0; _t.name[44] = 0; _t.name[45] = 0; _t.name[46] = 0; _t.name[47] = 0; _t.name[48] = 0; _t.name[49] = 0; _t.name[50] = 0; _t.name[51] = 0; _t.name[52] = 0; _t.name[53] = 0; _t.name[54] = 0; _t.name[55] = 0; _t.name[56] = 0; _t.name[57] = 0; _t.name[58] = 0; _t.name[59] = 0; _t.name[60] = 0; _t.name[61] = 0; _t.name[62] = 0; _t.name[63] = 0; _t.name_len = 0; _t.offset = 0; _t; });
  uint8_t lbl[64] = { 0 };
  struct backend_AsmFuncCtx ctx = ({ struct backend_AsmFuncCtx _t = { 0 }; _t.frame_size = 0; _t.next_offset = 0; _t.locals[0] = z; _t.locals[1] = z; _t.locals[2] = z; _t.locals[3] = z; _t.locals[4] = z; _t.locals[5] = z; _t.locals[6] = z; _t.locals[7] = z; _t.locals[8] = z; _t.locals[9] = z; _t.locals[10] = z; _t.locals[11] = z; _t.locals[12] = z; _t.locals[13] = z; _t.locals[14] = z; _t.locals[15] = z; _t.locals[16] = z; _t.locals[17] = z; _t.locals[18] = z; _t.locals[19] = z; _t.locals[20] = z; _t.locals[21] = z; _t.locals[22] = z; _t.locals[23] = z; _t.num_locals = 0; _t.label_counter = 0; _t.break_len = 0; _t.continue_len = 0; memcpy(_t.break_label, lbl, sizeof(_t.break_label)); memcpy(_t.continue_label, lbl, sizeof(_t.continue_label)); _t; });
  int32_t i = 0;
  while (i < (module)->num_funcs && i < 256) {
    (void)(({ int32_t __tmp = 0; if (i == 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_arch_emit_section_text(out, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    struct ast_Func f = (i < 0 || (i) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[i]);
    (void)(({ int32_t __tmp = 0; if ((f).is_extern != 0) {   (void)((i = i + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(backend_ctx_reset((&(ctx))));
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_globl(out, (f).name, (f).name_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_label(out, (f).name, (f).name_len, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t frame_sz = 0;
    (void)(({ int32_t __tmp = 0; if ((f).body_ref != 0) {   struct ast_Block blk = ast_ast_arena_block_get(arena, (f).body_ref);
  (void)((frame_sz = backend_compute_frame_size((&(blk)))));
  (void)(backend_fill_local_slots((&(ctx)), (&(blk))));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_prologue(out, frame_sz, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((f).body_ref != 0) {   struct ast_Block blk = ast_ast_arena_block_get(arena, (f).body_ref);
  __tmp = ({ int32_t __tmp = 0; if ((blk).num_stmt_order > 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_block_body(arena, out, (&(blk)), (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_block_inits(arena, out, (&(blk)), (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    int32_t result_ref = backend_get_return_expr_ref(arena, (&(f)));
    (void)(({ int32_t __tmp = 0; if (result_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr(arena, out, result_ref, (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (backend_arch_emit_epilogue(out, frame_sz, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 0;
}
int32_t backend_asm_codegen_ast_to_elf(struct ast_Module * module, struct ast_ASTArena * arena, struct platform_elf_ElfCodegenCtx * elf_ctx, struct ast_PipelineDepCtx * pipeline_ctx) {
  int32_t ta = (pipeline_ctx)->target_arch;
  struct backend_LocalSlot z = ({ struct backend_LocalSlot _t = { 0 }; _t.name[0] = 0; _t.name[1] = 0; _t.name[2] = 0; _t.name[3] = 0; _t.name[4] = 0; _t.name[5] = 0; _t.name[6] = 0; _t.name[7] = 0; _t.name[8] = 0; _t.name[9] = 0; _t.name[10] = 0; _t.name[11] = 0; _t.name[12] = 0; _t.name[13] = 0; _t.name[14] = 0; _t.name[15] = 0; _t.name[16] = 0; _t.name[17] = 0; _t.name[18] = 0; _t.name[19] = 0; _t.name[20] = 0; _t.name[21] = 0; _t.name[22] = 0; _t.name[23] = 0; _t.name[24] = 0; _t.name[25] = 0; _t.name[26] = 0; _t.name[27] = 0; _t.name[28] = 0; _t.name[29] = 0; _t.name[30] = 0; _t.name[31] = 0; _t.name[32] = 0; _t.name[33] = 0; _t.name[34] = 0; _t.name[35] = 0; _t.name[36] = 0; _t.name[37] = 0; _t.name[38] = 0; _t.name[39] = 0; _t.name[40] = 0; _t.name[41] = 0; _t.name[42] = 0; _t.name[43] = 0; _t.name[44] = 0; _t.name[45] = 0; _t.name[46] = 0; _t.name[47] = 0; _t.name[48] = 0; _t.name[49] = 0; _t.name[50] = 0; _t.name[51] = 0; _t.name[52] = 0; _t.name[53] = 0; _t.name[54] = 0; _t.name[55] = 0; _t.name[56] = 0; _t.name[57] = 0; _t.name[58] = 0; _t.name[59] = 0; _t.name[60] = 0; _t.name[61] = 0; _t.name[62] = 0; _t.name[63] = 0; _t.name_len = 0; _t.offset = 0; _t; });
  uint8_t lbl[64] = { 0 };
  struct backend_AsmFuncCtx ctx = ({ struct backend_AsmFuncCtx _t = { 0 }; _t.frame_size = 0; _t.next_offset = 0; _t.locals[0] = z; _t.locals[1] = z; _t.locals[2] = z; _t.locals[3] = z; _t.locals[4] = z; _t.locals[5] = z; _t.locals[6] = z; _t.locals[7] = z; _t.locals[8] = z; _t.locals[9] = z; _t.locals[10] = z; _t.locals[11] = z; _t.locals[12] = z; _t.locals[13] = z; _t.locals[14] = z; _t.locals[15] = z; _t.locals[16] = z; _t.locals[17] = z; _t.locals[18] = z; _t.locals[19] = z; _t.locals[20] = z; _t.locals[21] = z; _t.locals[22] = z; _t.locals[23] = z; _t.num_locals = 0; _t.label_counter = 0; _t.break_len = 0; _t.continue_len = 0; memcpy(_t.break_label, lbl, sizeof(_t.break_label)); memcpy(_t.continue_label, lbl, sizeof(_t.continue_label)); _t; });
  int32_t i = 0;
  while (i < (module)->num_funcs && i < 256) {
    struct ast_Func f = (i < 0 || (i) >= 256 ? (shulang_panic_(1, 0), ((module)->funcs)[0]) : ((module)->funcs)[i]);
    (void)(({ int32_t __tmp = 0; if ((f).is_extern != 0) {   (void)((i = i + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(backend_ctx_reset((&(ctx))));
    (void)(({ int32_t __tmp = 0; if (backend_enc_label_arch(elf_ctx, (f).name, (f).name_len, 1, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t frame_sz = 0;
    (void)(({ int32_t __tmp = 0; if ((f).body_ref != 0) {   struct ast_Block blk = ast_ast_arena_block_get(arena, (f).body_ref);
  (void)((frame_sz = backend_compute_frame_size((&(blk)))));
  (void)(backend_fill_local_slots((&(ctx)), (&(blk))));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (backend_enc_prologue_arch(elf_ctx, frame_sz, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((f).body_ref != 0) {   struct ast_Block blk = ast_ast_arena_block_get(arena, (f).body_ref);
  __tmp = ({ int32_t __tmp = 0; if ((blk).num_stmt_order > 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_block_body_elf(arena, elf_ctx, (&(blk)), (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_block_inits_elf(arena, elf_ctx, (&(blk)), (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    int32_t result_ref = backend_get_return_expr_ref(arena, (&(f)));
    (void)(({ int32_t __tmp = 0; if (result_ref != 0) {   __tmp = ({ int32_t __tmp = 0; if (backend_emit_expr_elf(arena, elf_ctx, result_ref, (&(ctx)), ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (backend_enc_epilogue_arch(elf_ctx, ta) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (ta == 1) {   (void)(((elf_ctx)->e_machine = 183));
  (void)(((elf_ctx)->reloc_type_r_pc32 = 283));
 } else (__tmp = ({ int32_t __tmp = 0; if (ta == 2) {   (void)(((elf_ctx)->e_machine = 243));
  (void)(((elf_ctx)->reloc_type_r_pc32 = 32));
 } else {   (void)(((elf_ctx)->e_machine = 62));
  (void)(((elf_ctx)->reloc_type_r_pc32 = 2));
 } ; __tmp; })) ; __tmp; }));
  return 0;
}
int32_t peephole_slice_eq(struct codegen_CodegenOutBuf * out, int32_t pos, uint8_t * ptr, int32_t len);
int32_t peephole_peephole_remove_redundant_push_pop(struct codegen_CodegenOutBuf * out);
int32_t peephole_peephole_remove_noop_mov_rax_rax(struct codegen_CodegenOutBuf * out);
int32_t peephole_peephole_remove_empty_lines(struct codegen_CodegenOutBuf * out);
int32_t peephole_peephole_run(struct codegen_CodegenOutBuf * out);
int32_t peephole_slice_eq(struct codegen_CodegenOutBuf * out, int32_t pos, uint8_t * ptr, int32_t len) {
  int32_t i = 0;
  while (i < len) {
    (void)(({ int32_t __tmp = 0; if ((pos + i < 0 || (pos + i) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[pos + i]) != (ptr)[i]) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (pos + len > (out)->len) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  return 1;
}
int32_t peephole_peephole_remove_redundant_push_pop(struct codegen_CodegenOutBuf * out) {
  uint8_t x86_push[11] = { 112, 117, 115, 104, 113, 32, 37, 114, 97, 120, 10 };
  uint8_t x86_pop[10] = { 112, 111, 112, 113, 32, 37, 114, 97, 120, 10 };
  uint8_t arm_push[20] = { 115, 116, 114, 32, 119, 48, 44, 32, 91, 115, 112, 44, 32, 35, 45, 49, 54, 93, 33, 10 };
  uint8_t arm_pop[18] = { 108, 100, 114, 32, 119, 48, 44, 32, 91, 115, 112, 93, 44, 32, 35, 49, 54, 10 };
  int32_t i = 0;
  while (i < (out)->len) {
    int32_t line_end = i;
    (void)(({ int32_t __tmp = 0; if (line_end >= (out)->len) {   break;
 } else (__tmp = 0) ; __tmp; }));
    int32_t line_len = line_end - i;
    int32_t next_start = line_end + 1;
    int32_t remove_len = 0;
    (void)(({ int32_t __tmp = 0; if (line_len == 10 && next_start + 10 <= (out)->len && peephole_slice_eq(out, i, x86_push, 11) != 0 && peephole_slice_eq(out, next_start, x86_pop, 10) != 0) {   (void)((remove_len = 11 + 10));
 } else (__tmp = ({ int32_t __tmp = 0; if (line_len == 19 && next_start + 18 <= (out)->len && peephole_slice_eq(out, i, arm_push, 20) != 0 && peephole_slice_eq(out, next_start, arm_pop, 18) != 0) {   (void)((remove_len = 20 + 18));
 } else (__tmp = 0) ; __tmp; })) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (remove_len > 0) {   int32_t j = i;
  (void)(((out)->len = (out)->len - remove_len));
  continue;
  while (j < (out)->len - remove_len) {
    (void)(((j < 0 || (j) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[j] = (j + remove_len < 0 || (j + remove_len) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[j + remove_len]), 0))));
    (void)((j = j + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = next_start));
    while (line_end < (out)->len && (line_end < 0 || (line_end) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[line_end]) != 10) {
      (void)((line_end = line_end + 1));
    }
  }
  return 0;
}
int32_t peephole_peephole_remove_noop_mov_rax_rax(struct codegen_CodegenOutBuf * out) {
  uint8_t x86_noop[16] = { 109, 111, 118, 113, 32, 37, 114, 97, 120, 44, 32, 37, 114, 97, 120, 10 };
  int32_t i = 0;
  while (i < (out)->len) {
    (void)(({ int32_t __tmp = 0; if (i + 16 <= (out)->len && peephole_slice_eq(out, i, x86_noop, 16) != 0) {   int32_t j = i;
  (void)(((out)->len = (out)->len - 16));
  continue;
  while (j < (out)->len - 16) {
    (void)(((j < 0 || (j) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[j] = (j + 16 < 0 || (j + 16) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[j + 16]), 0))));
    (void)((j = j + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
    int32_t line_end = i;
    while (line_end < (out)->len && (line_end < 0 || (line_end) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[line_end]) != 10) {
      (void)((line_end = line_end + 1));
    }
    (void)(({ int32_t __tmp = 0; if (line_end >= (out)->len) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = line_end + 1));
  }
  return 0;
}
int32_t peephole_peephole_remove_empty_lines(struct codegen_CodegenOutBuf * out) {
  int32_t src = 0;
  int32_t dst = 0;
  int32_t prev_was_nl = 0;
  while (src < (out)->len && dst < 262144) {
    uint8_t ch = (src < 0 || (src) >= 262144 ? (shulang_panic_(1, 0), ((out)->data)[0]) : ((out)->data)[src]);
    (void)(({ int32_t __tmp = 0; if (ch == 10) {   (void)(({ int32_t __tmp = 0; if (prev_was_nl != 0) {   (void)((src = src + 1));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)((prev_was_nl = 1));
 } else {   (void)((prev_was_nl = 0));
 } ; __tmp; }));
    (void)(((dst < 0 || (dst) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[dst] = ch, 0))));
    (void)((dst = dst + 1));
    (void)((src = src + 1));
  }
  (void)(((out)->len = dst));
  return 0;
}
int32_t peephole_peephole_run(struct codegen_CodegenOutBuf * out) {
  (void)(({ int32_t __tmp = 0; if (peephole_peephole_remove_redundant_push_pop(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (peephole_peephole_remove_noop_mov_rax_rax(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (peephole_peephole_remove_empty_lines(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t platform_macho_macho_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n);
int32_t platform_macho_write_macho_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out);
int32_t platform_macho_macho_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n) {
  int32_t i = 0;
  while (i < n && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (ptr)[i], 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (i < n) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t platform_macho_write_macho_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out) {
  int32_t code_len = ((ctx)->code).len;
  int32_t strtab_size = 1;
  int32_t s = 0;
  int32_t symtab_ents = 1 + (ctx)->num_syms;
  int32_t symtab_size = symtab_ents * 16;
  int32_t sizeofcmds = 176;
  int32_t off_text = 32 + sizeofcmds;
  int32_t off_sym = off_text + code_len + 3 & -4;
  int32_t off_str = off_sym + symtab_size;
  int32_t off_reloc = off_str + strtab_size;
  int32_t cputype = 7;
  int32_t cpusubtype = 3;
  uint8_t hdr[32] = { 0 };
  uint8_t seg[152] = { 0 };
  uint8_t lc_sym[24] = { 0 };
  uint8_t zero[1] = { 0 };
  int32_t z = 0;
  uint8_t sym0[16] = { 0 };
  int32_t str_off = 1;
  int32_t rel_type = 2;
  int32_t rel_len = 2;
  int32_t r = 0;
  while (s < (ctx)->num_syms) {
    (void)((strtab_size = strtab_size + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  int32_t pad = off_sym - (off_text + code_len); while (z < pad) {
    (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, zero, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((z = z + 1));
  }
  while (s < (ctx)->num_syms) {
    uint8_t ent[16] = { 0 };
    (void)(((4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[4] = 18, 0))));
    (void)(((6 < 0 || (6) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[6] = 1, 0))));
    (void)(((ent)[0] = platform_elf_elf_to_u8(str_off)));
    (void)(((1 < 0 || (1) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[1] = platform_elf_elf_to_u8(str_off >> 8), 0))));
    (void)(((2 < 0 || (2) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[2] = platform_elf_elf_to_u8(str_off >> 16), 0))));
    (void)(((3 < 0 || (3) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[3] = platform_elf_elf_to_u8(str_off >> 24), 0))));
    (void)(((8 < 0 || (8) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[8] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset), 0))));
    (void)(((9 < 0 || (9) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[9] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 8), 0))));
    (void)(((10 < 0 || (10) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[10] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 16), 0))));
    (void)(((11 < 0 || (11) >= 16 ? (shulang_panic_(1, 0), 0) : ((ent)[11] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 24), 0))));
    (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, ent, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((str_off = str_off + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  while (s < (ctx)->num_syms) {
    (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, zero, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((s = s + 1));
  }
  while (r < (ctx)->num_relocs) {
    uint8_t ri[8] = {0};
    int32_t sym_idx = 0;
    int32_t m = 0;
    (void)(((ri)[0] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset)));
    (void)(((1 < 0 || (1) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[1] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 8), 0))));
    (void)(((2 < 0 || (2) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[2] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 16), 0))));
    (void)(((3 < 0 || (3) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[3] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 24), 0))));
    (void)(((4 < 0 || (4) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[4] = platform_elf_elf_to_u8(sym_idx), 0))));
    (void)(((5 < 0 || (5) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[5] = platform_elf_elf_to_u8(sym_idx >> 8), 0))));
    (void)(((6 < 0 || (6) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[6] = platform_elf_elf_to_u8(sym_idx >> 16), 0))));
    (void)(((7 < 0 || (7) >= 8 ? (shulang_panic_(1, 0), 0) : ((ri)[7] = platform_elf_elf_to_u8(1 << 7 | rel_len << 5 | 1 << 4 | rel_type), 0))));
    (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, ri, 8) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((r = r + 1));
    while (m < (ctx)->num_syms) {
      (void)(({ int32_t __tmp = 0; if (platform_elf_elf_name_eq(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name, ((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name_len, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name_len) != 0) {   (void)((sym_idx = m + 1));
  break;
 } else (__tmp = 0) ; __tmp; }));
      (void)((m = m + 1));
    }
  }
  (void)(((out)->len = 0));
  (void)(({ int32_t __tmp = 0; if ((ctx)->e_machine == 183) {   (void)((cputype = 16777223));
  (void)((cpusubtype = 0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(((hdr)[0] = platform_elf_elf_to_u8(207)));
  (void)(((1 < 0 || (1) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[1] = platform_elf_elf_to_u8(250), 0))));
  (void)(((2 < 0 || (2) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[2] = platform_elf_elf_to_u8(237), 0))));
  (void)(((3 < 0 || (3) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[3] = platform_elf_elf_to_u8(254), 0))));
  (void)(((4 < 0 || (4) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[4] = platform_elf_elf_to_u8(cputype), 0))));
  (void)(((5 < 0 || (5) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[5] = platform_elf_elf_to_u8(cputype >> 8), 0))));
  (void)(((6 < 0 || (6) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[6] = platform_elf_elf_to_u8(cputype >> 16), 0))));
  (void)(((7 < 0 || (7) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[7] = platform_elf_elf_to_u8(cputype >> 24), 0))));
  (void)(((8 < 0 || (8) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[8] = platform_elf_elf_to_u8(cpusubtype), 0))));
  (void)(((9 < 0 || (9) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[9] = platform_elf_elf_to_u8(cpusubtype >> 8), 0))));
  (void)(((10 < 0 || (10) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[10] = platform_elf_elf_to_u8(1), 0))));
  (void)(((11 < 0 || (11) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[11] = 0, 0))));
  (void)(((12 < 0 || (12) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[12] = platform_elf_elf_to_u8(2), 0))));
  (void)(((13 < 0 || (13) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[13] = 0, 0))));
  (void)(((14 < 0 || (14) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[14] = platform_elf_elf_to_u8(sizeofcmds), 0))));
  (void)(((15 < 0 || (15) >= 32 ? (shulang_panic_(1, 0), 0) : ((hdr)[15] = platform_elf_elf_to_u8(sizeofcmds >> 8), 0))));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, hdr, 32) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((seg)[0] = platform_elf_elf_to_u8(25)));
  (void)(((1 < 0 || (1) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[1] = 0, 0))));
  (void)(((2 < 0 || (2) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[2] = 0, 0))));
  (void)(((3 < 0 || (3) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[3] = 0, 0))));
  (void)(((4 < 0 || (4) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[4] = platform_elf_elf_to_u8(152), 0))));
  (void)(((5 < 0 || (5) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[5] = platform_elf_elf_to_u8(152 >> 8), 0))));
  (void)(((6 < 0 || (6) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[6] = 95, 0))));
  (void)(((7 < 0 || (7) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[7] = 95, 0))));
  (void)(((8 < 0 || (8) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[8] = 84, 0))));
  (void)(((9 < 0 || (9) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[9] = 69, 0))));
  (void)(((10 < 0 || (10) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[10] = 88, 0))));
  (void)(((11 < 0 || (11) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[11] = 84, 0))));
  (void)(((40 < 0 || (40) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[40] = platform_elf_elf_to_u8(off_text), 0))));
  (void)(((41 < 0 || (41) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[41] = platform_elf_elf_to_u8(off_text >> 8), 0))));
  (void)(((42 < 0 || (42) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[42] = platform_elf_elf_to_u8(off_text >> 16), 0))));
  (void)(((43 < 0 || (43) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[43] = platform_elf_elf_to_u8(off_text >> 24), 0))));
  (void)(((48 < 0 || (48) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[48] = platform_elf_elf_to_u8(code_len), 0))));
  (void)(((49 < 0 || (49) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[49] = platform_elf_elf_to_u8(code_len >> 8), 0))));
  (void)(((50 < 0 || (50) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[50] = platform_elf_elf_to_u8(code_len >> 16), 0))));
  (void)(((51 < 0 || (51) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[51] = platform_elf_elf_to_u8(code_len >> 24), 0))));
  (void)(((64 < 0 || (64) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[64] = 1, 0))));
  (void)(((65 < 0 || (65) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[65] = 0, 0))));
  (void)(((66 < 0 || (66) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[66] = 0, 0))));
  (void)(((67 < 0 || (67) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[67] = 0, 0))));
  (void)(((72 < 0 || (72) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[72] = 95, 0))));
  (void)(((73 < 0 || (73) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[73] = 95, 0))));
  (void)(((74 < 0 || (74) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[74] = 116, 0))));
  (void)(((75 < 0 || (75) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[75] = 101, 0))));
  (void)(((76 < 0 || (76) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[76] = 120, 0))));
  (void)(((77 < 0 || (77) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[77] = 116, 0))));
  (void)(((88 < 0 || (88) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[88] = 95, 0))));
  (void)(((89 < 0 || (89) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[89] = 95, 0))));
  (void)(((90 < 0 || (90) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[90] = 84, 0))));
  (void)(((91 < 0 || (91) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[91] = 69, 0))));
  (void)(((92 < 0 || (92) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[92] = 88, 0))));
  (void)(((93 < 0 || (93) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[93] = 84, 0))));
  (void)(((120 < 0 || (120) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[120] = platform_elf_elf_to_u8(off_text), 0))));
  (void)(((121 < 0 || (121) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[121] = platform_elf_elf_to_u8(off_text >> 8), 0))));
  (void)(((122 < 0 || (122) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[122] = platform_elf_elf_to_u8(off_text >> 16), 0))));
  (void)(((123 < 0 || (123) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[123] = platform_elf_elf_to_u8(off_text >> 24), 0))));
  (void)(((112 < 0 || (112) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[112] = platform_elf_elf_to_u8(code_len), 0))));
  (void)(((113 < 0 || (113) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[113] = platform_elf_elf_to_u8(code_len >> 8), 0))));
  (void)(((114 < 0 || (114) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[114] = platform_elf_elf_to_u8(code_len >> 16), 0))));
  (void)(((115 < 0 || (115) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[115] = platform_elf_elf_to_u8(code_len >> 24), 0))));
  (void)(((128 < 0 || (128) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[128] = platform_elf_elf_to_u8(off_reloc), 0))));
  (void)(((129 < 0 || (129) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[129] = platform_elf_elf_to_u8(off_reloc >> 8), 0))));
  (void)(((130 < 0 || (130) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[130] = platform_elf_elf_to_u8(off_reloc >> 16), 0))));
  (void)(((131 < 0 || (131) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[131] = platform_elf_elf_to_u8(off_reloc >> 24), 0))));
  (void)(((132 < 0 || (132) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[132] = platform_elf_elf_to_u8((ctx)->num_relocs), 0))));
  (void)(((133 < 0 || (133) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[133] = platform_elf_elf_to_u8((ctx)->num_relocs >> 8), 0))));
  (void)(((136 < 0 || (136) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[136] = 0, 0))));
  (void)(((137 < 0 || (137) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[137] = 0, 0))));
  (void)(((138 < 0 || (138) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[138] = 4, 0))));
  (void)(((139 < 0 || (139) >= 152 ? (shulang_panic_(1, 0), 0) : ((seg)[139] = 128, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, seg, 152) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((lc_sym)[0] = 2));
  (void)(((1 < 0 || (1) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[1] = 0, 0))));
  (void)(((2 < 0 || (2) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[2] = 0, 0))));
  (void)(((3 < 0 || (3) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[3] = 0, 0))));
  (void)(((4 < 0 || (4) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[4] = 24, 0))));
  (void)(((8 < 0 || (8) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[8] = platform_elf_elf_to_u8(off_sym), 0))));
  (void)(((9 < 0 || (9) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[9] = platform_elf_elf_to_u8(off_sym >> 8), 0))));
  (void)(((10 < 0 || (10) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[10] = platform_elf_elf_to_u8(off_sym >> 16), 0))));
  (void)(((11 < 0 || (11) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[11] = platform_elf_elf_to_u8(off_sym >> 24), 0))));
  (void)(((12 < 0 || (12) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[12] = platform_elf_elf_to_u8(symtab_ents), 0))));
  (void)(((13 < 0 || (13) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[13] = platform_elf_elf_to_u8(symtab_ents >> 8), 0))));
  (void)(((16 < 0 || (16) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[16] = platform_elf_elf_to_u8(off_str), 0))));
  (void)(((17 < 0 || (17) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[17] = platform_elf_elf_to_u8(off_str >> 8), 0))));
  (void)(((18 < 0 || (18) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[18] = platform_elf_elf_to_u8(off_str >> 16), 0))));
  (void)(((19 < 0 || (19) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[19] = platform_elf_elf_to_u8(off_str >> 24), 0))));
  (void)(((20 < 0 || (20) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[20] = platform_elf_elf_to_u8(strtab_size), 0))));
  (void)(((21 < 0 || (21) >= 24 ? (shulang_panic_(1, 0), 0) : ((lc_sym)[21] = platform_elf_elf_to_u8(strtab_size >> 8), 0))));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, lc_sym, 24) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, ((ctx)->code).data, code_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((4 < 0 || (4) >= 16 ? (shulang_panic_(1, 0), 0) : ((sym0)[4] = 1, 0))));
  (void)(((8 < 0 || (8) >= 16 ? (shulang_panic_(1, 0), 0) : ((sym0)[8] = platform_elf_elf_to_u8(code_len), 0))));
  (void)(((9 < 0 || (9) >= 16 ? (shulang_panic_(1, 0), 0) : ((sym0)[9] = platform_elf_elf_to_u8(code_len >> 8), 0))));
  (void)(((10 < 0 || (10) >= 16 ? (shulang_panic_(1, 0), 0) : ((sym0)[10] = platform_elf_elf_to_u8(code_len >> 16), 0))));
  (void)(((11 < 0 || (11) >= 16 ? (shulang_panic_(1, 0), 0) : ((sym0)[11] = platform_elf_elf_to_u8(code_len >> 24), 0))));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, sym0, 16) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(({ int32_t __tmp = 0; if (platform_macho_macho_append(out, zero, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(({ int32_t __tmp = 0; if ((ctx)->e_machine == 183) {   (void)((rel_type = 2));
  (void)((rel_len = 2));
 } else (__tmp = 0) ; __tmp; }));
  return (out)->len;
}
int32_t platform_coff_coff_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n);
int32_t platform_coff_write_coff_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out);
int32_t platform_coff_coff_append(struct codegen_CodegenOutBuf * out, uint8_t * ptr, int32_t n) {
  int32_t i = 0;
  while (i < n && (out)->len < 262144) {
    (void)((((out)->len < 0 || ((out)->len) >= 262144 ? (shulang_panic_(1, 0), 0) : (((out)->data)[(out)->len] = (ptr)[i], 0))));
    (void)(((out)->len = (out)->len + 1));
    (void)((i = i + 1));
  }
  (void)(({ int32_t __tmp = 0; if (i < n) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t platform_coff_write_coff_o_to_buf(struct platform_elf_ElfCodegenCtx * ctx, struct codegen_CodegenOutBuf * out) {
  int32_t code_len = ((ctx)->code).len;
  int32_t align4 = code_len + 3 & -4;
  int32_t num_relocs = (ctx)->num_relocs;
  int32_t num_syms = (ctx)->num_syms;
  int32_t reloc_size = num_relocs * 10;
  int32_t num_coff_syms = 2 + num_syms;
  int32_t symtab_size = num_coff_syms * 18;
  int32_t strtab_used = 4;
  int32_t s = 0;
  int32_t ptr_raw = 60;
  int32_t ptr_reloc = ptr_raw + align4;
  int32_t ptr_sym = ptr_reloc + reloc_size;
  uint8_t fh[20] = { 0 };
  uint8_t sh[40] = { 0 };
  uint8_t zero[1] = { 0 };
  int32_t r = 0;
  uint8_t sym_sec[18] = { 0 };
  uint8_t aux[18] = { 0 };
  int32_t str_off = 4;
  uint8_t str_size[4] = { 0 };
  while (s < num_syms) {
    (void)((strtab_used = strtab_used + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  while (s < align4 - code_len) {
    (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, zero, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((s = s + 1));
  }
  while (r < num_relocs) {
    uint8_t rel[10] = {0};
    int32_t sym_idx = 0;
    int32_t m = 0;
    (void)(((rel)[0] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset)));
    (void)(((1 < 0 || (1) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[1] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 8), 0))));
    (void)(((2 < 0 || (2) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[2] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 16), 0))));
    (void)(((3 < 0 || (3) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[3] = platform_elf_elf_to_u8(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).offset >> 24), 0))));
    (void)(((4 < 0 || (4) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[4] = platform_elf_elf_to_u8(sym_idx), 0))));
    (void)(((5 < 0 || (5) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[5] = platform_elf_elf_to_u8(sym_idx >> 8), 0))));
    (void)(((6 < 0 || (6) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[6] = platform_elf_elf_to_u8(sym_idx >> 16), 0))));
    (void)(((7 < 0 || (7) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[7] = platform_elf_elf_to_u8(sym_idx >> 24), 0))));
    (void)(((8 < 0 || (8) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[8] = 4, 0))));
    (void)(((9 < 0 || (9) >= 10 ? (shulang_panic_(1, 0), 0) : ((rel)[9] = 0, 0))));
    (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, rel, 10) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((r = r + 1));
    while (m < num_syms) {
      (void)(({ int32_t __tmp = 0; if (platform_elf_elf_name_eq(((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name, ((r < 0 || (r) >= 32 ? (shulang_panic_(1, 0), ((ctx)->relocs)[0]) : ((ctx)->relocs)[r])).name_len, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name, ((m < 0 || (m) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[m])).name_len) != 0) {   (void)((sym_idx = 2 + m));
  break;
 } else (__tmp = 0) ; __tmp; }));
      (void)((m = m + 1));
    }
  }
  while (s < num_syms) {
    uint8_t ent[18] = { 0 };
    (void)(((ent)[0] = 0));
    (void)(((1 < 0 || (1) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[1] = 0, 0))));
    (void)(((2 < 0 || (2) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[2] = 0, 0))));
    (void)(((3 < 0 || (3) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[3] = 0, 0))));
    (void)(((4 < 0 || (4) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[4] = platform_elf_elf_to_u8(str_off), 0))));
    (void)(((5 < 0 || (5) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[5] = platform_elf_elf_to_u8(str_off >> 8), 0))));
    (void)(((6 < 0 || (6) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[6] = platform_elf_elf_to_u8(str_off >> 16), 0))));
    (void)(((7 < 0 || (7) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[7] = platform_elf_elf_to_u8(str_off >> 24), 0))));
    (void)(((8 < 0 || (8) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[8] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset), 0))));
    (void)(((9 < 0 || (9) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[9] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 8), 0))));
    (void)(((10 < 0 || (10) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[10] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 16), 0))));
    (void)(((11 < 0 || (11) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[11] = platform_elf_elf_to_u8(((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).offset >> 24), 0))));
    (void)(((12 < 0 || (12) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[12] = 1, 0))));
    (void)(((13 < 0 || (13) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[13] = 0, 0))));
    (void)(((14 < 0 || (14) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[14] = 32, 0))));
    (void)(((15 < 0 || (15) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[15] = 0, 0))));
    (void)(((16 < 0 || (16) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[16] = 2, 0))));
    (void)(((17 < 0 || (17) >= 18 ? (shulang_panic_(1, 0), 0) : ((ent)[17] = 0, 0))));
    (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, ent, 18) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((str_off = str_off + ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len + 1));
    (void)((s = s + 1));
  }
  while (s < num_syms) {
    (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name, ((s < 0 || (s) >= 16 ? (shulang_panic_(1, 0), ((ctx)->syms)[0]) : ((ctx)->syms)[s])).name_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, zero, 1) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((s = s + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->e_machine != 62) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out)->len = 0));
  (void)(((fh)[0] = platform_elf_elf_to_u8(100)));
  (void)(((1 < 0 || (1) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[1] = platform_elf_elf_to_u8(134), 0))));
  (void)(((2 < 0 || (2) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[2] = platform_elf_elf_to_u8(1), 0))));
  (void)(((3 < 0 || (3) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[3] = platform_elf_elf_to_u8(0), 0))));
  (void)(((4 < 0 || (4) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[4] = platform_elf_elf_to_u8(0), 0))));
  (void)(((5 < 0 || (5) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[5] = platform_elf_elf_to_u8(0), 0))));
  (void)(((6 < 0 || (6) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[6] = platform_elf_elf_to_u8(0), 0))));
  (void)(((7 < 0 || (7) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[7] = platform_elf_elf_to_u8(0), 0))));
  (void)(((8 < 0 || (8) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[8] = platform_elf_elf_to_u8(ptr_sym), 0))));
  (void)(((9 < 0 || (9) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[9] = platform_elf_elf_to_u8(ptr_sym >> 8), 0))));
  (void)(((10 < 0 || (10) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[10] = platform_elf_elf_to_u8(ptr_sym >> 16), 0))));
  (void)(((11 < 0 || (11) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[11] = platform_elf_elf_to_u8(ptr_sym >> 24), 0))));
  (void)(((12 < 0 || (12) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[12] = platform_elf_elf_to_u8(num_coff_syms), 0))));
  (void)(((13 < 0 || (13) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[13] = platform_elf_elf_to_u8(num_coff_syms >> 8), 0))));
  (void)(((14 < 0 || (14) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[14] = platform_elf_elf_to_u8(num_coff_syms >> 16), 0))));
  (void)(((15 < 0 || (15) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[15] = platform_elf_elf_to_u8(num_coff_syms >> 24), 0))));
  (void)(((16 < 0 || (16) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[16] = 0, 0))));
  (void)(((17 < 0 || (17) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[17] = 0, 0))));
  (void)(((18 < 0 || (18) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[18] = 0, 0))));
  (void)(((19 < 0 || (19) >= 20 ? (shulang_panic_(1, 0), 0) : ((fh)[19] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, fh, 20) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((sh)[0] = 46));
  (void)(((1 < 0 || (1) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[1] = 116, 0))));
  (void)(((2 < 0 || (2) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[2] = 101, 0))));
  (void)(((3 < 0 || (3) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[3] = 120, 0))));
  (void)(((4 < 0 || (4) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[4] = 116, 0))));
  (void)(((5 < 0 || (5) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[5] = 0, 0))));
  (void)(((6 < 0 || (6) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[6] = 0, 0))));
  (void)(((7 < 0 || (7) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[7] = 0, 0))));
  (void)(((8 < 0 || (8) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[8] = 0, 0))));
  (void)(((9 < 0 || (9) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[9] = 0, 0))));
  (void)(((10 < 0 || (10) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[10] = 0, 0))));
  (void)(((11 < 0 || (11) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[11] = 0, 0))));
  (void)(((12 < 0 || (12) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[12] = 0, 0))));
  (void)(((13 < 0 || (13) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[13] = 0, 0))));
  (void)(((14 < 0 || (14) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[14] = 0, 0))));
  (void)(((15 < 0 || (15) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[15] = 0, 0))));
  (void)(((16 < 0 || (16) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[16] = platform_elf_elf_to_u8(align4), 0))));
  (void)(((17 < 0 || (17) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[17] = platform_elf_elf_to_u8(align4 >> 8), 0))));
  (void)(((18 < 0 || (18) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[18] = platform_elf_elf_to_u8(align4 >> 16), 0))));
  (void)(((19 < 0 || (19) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[19] = platform_elf_elf_to_u8(align4 >> 24), 0))));
  (void)(((20 < 0 || (20) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[20] = platform_elf_elf_to_u8(ptr_raw), 0))));
  (void)(((21 < 0 || (21) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[21] = platform_elf_elf_to_u8(ptr_raw >> 8), 0))));
  (void)(((22 < 0 || (22) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[22] = platform_elf_elf_to_u8(ptr_raw >> 16), 0))));
  (void)(((23 < 0 || (23) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[23] = platform_elf_elf_to_u8(ptr_raw >> 24), 0))));
  (void)(((24 < 0 || (24) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[24] = platform_elf_elf_to_u8(ptr_reloc), 0))));
  (void)(((25 < 0 || (25) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[25] = platform_elf_elf_to_u8(ptr_reloc >> 8), 0))));
  (void)(((26 < 0 || (26) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[26] = platform_elf_elf_to_u8(ptr_reloc >> 16), 0))));
  (void)(((27 < 0 || (27) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[27] = platform_elf_elf_to_u8(ptr_reloc >> 24), 0))));
  (void)(((28 < 0 || (28) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[28] = 0, 0))));
  (void)(((29 < 0 || (29) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[29] = 0, 0))));
  (void)(((30 < 0 || (30) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[30] = 0, 0))));
  (void)(((31 < 0 || (31) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[31] = 0, 0))));
  (void)(((32 < 0 || (32) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[32] = platform_elf_elf_to_u8(num_relocs), 0))));
  (void)(((33 < 0 || (33) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[33] = platform_elf_elf_to_u8(num_relocs >> 8), 0))));
  (void)(((34 < 0 || (34) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[34] = 0, 0))));
  (void)(((35 < 0 || (35) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[35] = 0, 0))));
  (void)(((36 < 0 || (36) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[36] = 32, 0))));
  (void)(((37 < 0 || (37) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[37] = 0, 0))));
  (void)(((38 < 0 || (38) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[38] = 80, 0))));
  (void)(((39 < 0 || (39) >= 40 ? (shulang_panic_(1, 0), 0) : ((sh)[39] = 96, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, sh, 40) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, ((ctx)->code).data, code_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(((16 < 0 || (16) >= 18 ? (shulang_panic_(1, 0), 0) : ((sym_sec)[16] = 1, 0))));
  (void)(((17 < 0 || (17) >= 18 ? (shulang_panic_(1, 0), 0) : ((sym_sec)[17] = 0, 0))));
  (void)(((14 < 0 || (14) >= 18 ? (shulang_panic_(1, 0), 0) : ((sym_sec)[14] = 3, 0))));
  (void)(((15 < 0 || (15) >= 18 ? (shulang_panic_(1, 0), 0) : ((sym_sec)[15] = 1, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, sym_sec, 18) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((aux)[0] = platform_elf_elf_to_u8(align4)));
  (void)(((1 < 0 || (1) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[1] = platform_elf_elf_to_u8(align4 >> 8), 0))));
  (void)(((2 < 0 || (2) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[2] = platform_elf_elf_to_u8(align4 >> 16), 0))));
  (void)(((3 < 0 || (3) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[3] = platform_elf_elf_to_u8(align4 >> 24), 0))));
  (void)(((4 < 0 || (4) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[4] = platform_elf_elf_to_u8(num_relocs), 0))));
  (void)(((5 < 0 || (5) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[5] = platform_elf_elf_to_u8(num_relocs >> 8), 0))));
  (void)(((14 < 0 || (14) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[14] = 1, 0))));
  (void)(((15 < 0 || (15) >= 18 ? (shulang_panic_(1, 0), 0) : ((aux)[15] = 0, 0))));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, aux, 18) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  (void)(((str_size)[0] = platform_elf_elf_to_u8(strtab_used)));
  (void)(((1 < 0 || (1) >= 4 ? (shulang_panic_(1, 0), 0) : ((str_size)[1] = platform_elf_elf_to_u8(strtab_used >> 8), 0))));
  (void)(((2 < 0 || (2) >= 4 ? (shulang_panic_(1, 0), 0) : ((str_size)[2] = platform_elf_elf_to_u8(strtab_used >> 16), 0))));
  (void)(((3 < 0 || (3) >= 4 ? (shulang_panic_(1, 0), 0) : ((str_size)[3] = platform_elf_elf_to_u8(strtab_used >> 24), 0))));
  (void)(({ int32_t __tmp = 0; if (platform_coff_coff_append(out, str_size, 4) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)((s = 0));
  return (out)->len;
}
int32_t asm_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_PipelineDepCtx * ctx);
int32_t asm_asm_codegen_elf_o(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, struct platform_elf_ElfCodegenCtx * elf_ctx, struct codegen_CodegenOutBuf * out);
int32_t asm_asm_codegen_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct codegen_CodegenOutBuf * out, struct ast_PipelineDepCtx * ctx) {
  (void)(({ int32_t __tmp = 0; if (backend_asm_codegen_ast(module, arena, out, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (peephole_peephole_run(out) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t asm_asm_codegen_elf_o(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, struct platform_elf_ElfCodegenCtx * elf_ctx, struct codegen_CodegenOutBuf * out) {
  (void)(platform_elf_elf_ctx_reset(elf_ctx));
  (void)(({ int32_t __tmp = 0; if (backend_asm_codegen_ast_to_elf(module, arena, elf_ctx, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (platform_elf_elf_resolve_patches(elf_ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if ((ctx)->use_coff_o != 0) {   __tmp = ({ int32_t __tmp = 0; if (platform_coff_write_coff_o_to_buf(elf_ctx, out) < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = ({ int32_t __tmp = 0; if ((ctx)->use_macho_o != 0) {   __tmp = ({ int32_t __tmp = 0; if (platform_macho_write_macho_o_to_buf(elf_ctx, out) < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   __tmp = ({ int32_t __tmp = 0; if (platform_elf_write_elf_o_to_buf(elf_ctx, out) < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; })) ; __tmp; }));
  return 0;
}
extern int32_t std_fs_fs_open_read(uint8_t *);
extern int32_t std_fs_fs_close(int32_t);
extern ptrdiff_t std_fs_fs_read(int32_t, uint8_t *, size_t);
extern struct lexer_Lexer lexer_lexer_init();
extern struct parser_OneFuncResult parser_parse_one_function(struct lexer_Lexer, struct shulang_slice_uint8_t *);
extern void parser_parse_into_init(struct ast_ASTArena *, struct ast_Module *);
extern void parser_parse_into_set_main_index(struct ast_Module *, int32_t);
extern int32_t parser_get_module_num_imports(struct ast_Module *);
extern int32_t codegen_codegen_su_ast(struct ast_Module *, struct ast_ASTArena *, struct codegen_CodegenOutBuf *);
extern int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);
extern void parser_get_module_import_path(struct ast_Module *, int32_t, uint8_t *);
extern int32_t typeck_typeck_su_ast(struct ast_Module *, struct ast_ASTArena *, struct ast_PipelineDepCtx *);
int32_t pipeline_pipeline_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t buf[262144], int32_t buf_len);
int32_t pipeline_path_append_from_buf_256(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t buf[256], int32_t len);
int32_t pipeline_path_append_from_buf_512(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t buf[512], int32_t len);
int32_t pipeline_path_append_import_path(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t import_path[64], int32_t path_len);
int32_t pipeline_resolve_path_su(struct ast_PipelineDepCtx * ctx, uint8_t import_path[64], int32_t path_len);
int32_t pipeline_read_file_su(struct ast_PipelineDepCtx * ctx);
int32_t pipeline_parse_one_function_ok(struct shulang_slice_uint8_t * source);
struct parser_ParseIntoResult pipeline_parse_into_with_init(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source);
int32_t pipeline_typeck_after_parse_ok(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_run_su_pipeline_impl(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_pipeline_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t buf[262144], int32_t buf_len) {
  struct parser_ParseIntoResult res = parser_parse_into_buf(arena, module, (&((buf)[0])), buf_len);
  (void)(parser_parse_into_init(arena, module));
  (void)(({ int32_t __tmp = 0; if ((res).ok != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t pipeline_path_append_from_buf_256(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t buf[256], int32_t len) {
  int32_t k = 0;
  while (k < len && off < 508) {
    (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = (k < 0 || (k) >= 256 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[k]), 0))));
    (void)((off = off + 1));
    (void)((k = k + 1));
  }
  return off;
}
int32_t pipeline_path_append_from_buf_512(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t buf[512], int32_t len) {
  int32_t k = 0;
  while (k < len && off < 508) {
    (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = (k < 0 || (k) >= 512 ? (shulang_panic_(1, 0), (buf)[0]) : (buf)[k]), 0))));
    (void)((off = off + 1));
    (void)((k = k + 1));
  }
  return off;
}
int32_t pipeline_path_append_import_path(struct ast_PipelineDepCtx * ctx, int32_t off, uint8_t import_path[64], int32_t path_len) {
  int32_t k = 0;
  while (k < path_len && off < 508) {
    (void)(({ int32_t __tmp = 0; if ((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (import_path)[0]) : (import_path)[k]) == 46) {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = 47, 0))));
 } else {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = (k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (import_path)[0]) : (import_path)[k]), 0))));
 } ; __tmp; }));
    (void)((off = off + 1));
    (void)((k = k + 1));
  }
  return off;
}
int32_t pipeline_resolve_path_su(struct ast_PipelineDepCtx * ctx, uint8_t import_path[64], int32_t path_len) {
  int32_t r = 0;
  while (r < (ctx)->num_lib_roots && r < 8) {
    int32_t off = 0;
    (void)(({ int32_t __tmp = 0; if ((r < 0 || (r) >= 8 ? (shulang_panic_(1, 0), ((ctx)->lib_root_lens)[0]) : ((ctx)->lib_root_lens)[r]) > 0) {   (void)((off = pipeline_path_append_from_buf_256(ctx, 0, (r < 0 || (r) >= 8 ? (shulang_panic_(1, 0), ((ctx)->lib_root_bufs)[0]) : ((ctx)->lib_root_bufs)[r]), (r < 0 || (r) >= 8 ? (shulang_panic_(1, 0), ((ctx)->lib_root_lens)[0]) : ((ctx)->lib_root_lens)[r]))));
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (off < 509) {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = 47, 0))));
  (void)((off = off + 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)((off = pipeline_path_append_import_path(ctx, off, import_path, path_len)));
    (void)(({ int32_t __tmp = 0; if (off + 4 <= 512) {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = 46, 0))));
  (void)(((off + 1 < 0 || (off + 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 1] = 115, 0))));
  (void)(((off + 2 < 0 || (off + 2) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 2] = 117, 0))));
  (void)(((off + 3 < 0 || (off + 3) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 3] = 0, 0))));
  int32_t fd = std_fs_fs_open_read((ctx)->path_buf);
  __tmp = ({ int32_t __tmp = 0; if (fd >= 0) {   (void)(std_fs_fs_close(fd));
  return 0;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)((r = r + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((ctx)->entry_dir_len > 0) {   int32_t has_dot = 0;
  int32_t k = 0;
  while (k < path_len && k < 64) {
    (void)(({ int32_t __tmp = 0; if ((k < 0 || (k) >= 64 ? (shulang_panic_(1, 0), (import_path)[0]) : (import_path)[k]) == 46) {   (void)((has_dot = 1));
 } else (__tmp = 0) ; __tmp; }));
    (void)((k = k + 1));
  }
  __tmp = ({ int32_t __tmp = 0; if (has_dot == 0) {   int32_t off = pipeline_path_append_from_buf_512(ctx, 0, (ctx)->entry_dir_buf, (ctx)->entry_dir_len);
  (void)(({ int32_t __tmp = 0; if (off < 509) {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = 47, 0))));
  (void)((off = off + 1));
 } else (__tmp = 0) ; __tmp; }));
  (void)((off = pipeline_path_append_import_path(ctx, off, import_path, path_len)));
  __tmp = ({ int32_t __tmp = 0; if (off + 4 <= 512) {   (void)(((off < 0 || (off) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off] = 46, 0))));
  (void)(((off + 1 < 0 || (off + 1) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 1] = 115, 0))));
  (void)(((off + 2 < 0 || (off + 2) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 2] = 117, 0))));
  (void)(((off + 3 < 0 || (off + 3) >= 512 ? (shulang_panic_(1, 0), 0) : (((ctx)->path_buf)[off + 3] = 0, 0))));
  int32_t fd = std_fs_fs_open_read((ctx)->path_buf);
  __tmp = ({ int32_t __tmp = 0; if (fd >= 0) {   (void)(std_fs_fs_close(fd));
  return 0;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
int32_t pipeline_read_file_su(struct ast_PipelineDepCtx * ctx) {
  int32_t fd = std_fs_fs_open_read((ctx)->path_buf);
  size_t cap = 262144;
  ptrdiff_t n = std_fs_fs_read(fd, (ctx)->loaded_buf, cap);
  (void)(({ int32_t __tmp = 0; if (fd < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(std_fs_fs_close(fd));
  (void)(({ int32_t __tmp = 0; if (n < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((ctx)->loaded_len = n));
  return 0;
}
int32_t pipeline_parse_one_function_ok(struct shulang_slice_uint8_t * source) {
  struct lexer_Lexer lex = lexer_lexer_init();
  struct parser_OneFuncResult res = parser_parse_one_function(lex, source);
  (void)(({ int32_t __tmp = 0; if ((res).ok) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
struct parser_ParseIntoResult pipeline_parse_into_with_init(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source) {
  (void)(parser_parse_into_init(arena, module));
  return parser_parse_into(arena, module, source);
}
int32_t pipeline_typeck_after_parse_ok(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source, struct ast_PipelineDepCtx * ctx) {
  struct parser_ParseIntoResult r = pipeline_parse_into_with_init(arena, module, source);
  (void)(({ int32_t __tmp = 0; if ((r).ok != 0) {   return (-2);
 } else (__tmp = 0) ; __tmp; }));
  (void)(parser_parse_into_set_main_index(module, (r).main_idx));
  return typeck_typeck_su_ast(module, arena, ctx);
}
int32_t pipeline_run_su_pipeline_impl(struct ast_ASTArena * arena, struct ast_Module * module, struct shulang_slice_uint8_t * source, struct codegen_CodegenOutBuf * out_buf, struct ast_PipelineDepCtx * ctx) {
  fprintf(stderr, "pipeline: impl start\n"); fflush(stderr);
  struct parser_ParseIntoResult r = pipeline_parse_into_with_init(arena, module, source);
  fprintf(stderr, "pipeline: after parse\n"); fflush(stderr);
  int32_t n_imports = parser_get_module_num_imports(module);
  int32_t j = 0;
  while (j < (ctx)->ndep) {
    (void)(({ int32_t __tmp = 0; if (j >= 32) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if ((ctx)->use_asm_backend != 0) {   __tmp = ({ int32_t __tmp = 0; if (asm_asm_codegen_ast((j < 0 || (j) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_modules)[0]) : ((ctx)->dep_modules)[j]), (j < 0 || (j) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_arenas)[0]) : ((ctx)->dep_arenas)[j]), out_buf, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   fprintf(stderr, "pipeline: before codegen\n"); fflush(stderr);   __tmp = ({ int32_t __tmp = 0; if (codegen_codegen_su_ast((j < 0 || (j) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_modules)[0]) : ((ctx)->dep_modules)[j]), (j < 0 || (j) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_arenas)[0]) : ((ctx)->dep_arenas)[j]), out_buf) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
    (void)((j = j + 1));
  }
  (void)(({ int32_t __tmp = 0; if ((r).ok != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(parser_parse_into_set_main_index(module, (r).main_idx));
  (void)(((ctx)->ndep = 0));
  (void)(({ int32_t __tmp = 0; if (n_imports > 0) {   int32_t i = 0;
  (void)(((ctx)->ndep = n_imports));
  while (i < n_imports) {
    (void)(({ int32_t __tmp = 0; if (i >= 32) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    uint8_t path_buf[64] = { 0 };
    (void)(parser_get_module_import_path(module, i, path_buf));
    int32_t path_len = 0;
    while (path_len < 64 && (path_len < 0 || (path_len) >= 64 ? (shulang_panic_(1, 0), (path_buf)[0]) : (path_buf)[path_len]) != 0) {
      (void)((path_len = path_len + 1));
    }
    (void)(({ int32_t __tmp = 0; if (pipeline_resolve_path_su(ctx, path_buf, path_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (pipeline_read_file_su(ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    int32_t out_len = preprocess_preprocess_su_buf((ctx)->loaded_buf, (ctx)->loaded_len, (ctx)->preprocess_buf, 262144);
    (void)(({ int32_t __tmp = 0; if (out_len < 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)(((ctx)->preprocess_len = out_len));
    const struct ast_ASTArena * dep_arena = (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_arenas)[0]) : ((ctx)->dep_arenas)[i]);
    const struct ast_Module * dep_module = (i < 0 || (i) >= 32 ? (shulang_panic_(1, 0), ((ctx)->dep_modules)[0]) : ((ctx)->dep_modules)[i]);
    (void)(({ int32_t __tmp = 0; if (pipeline_pipeline_parse_into_buf(dep_arena, dep_module, (ctx)->preprocess_buf, (ctx)->preprocess_len) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
 } else (__tmp = 0) ; __tmp; }));
  fprintf(stderr, "pipeline: before typeck\n"); fflush(stderr);
  (void)(({ int32_t __tmp = 0; if (typeck_typeck_su_ast(module, arena, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(((out_buf)->len = 0));
  (void)(({ int32_t __tmp = 0; if ((ctx)->use_asm_backend != 0) {   __tmp = ({ int32_t __tmp = 0; if (asm_asm_codegen_ast(module, arena, out_buf, ctx) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else {   fprintf(stderr, "pipeline: before codegen\n"); fflush(stderr);   __tmp = ({ int32_t __tmp = 0; if (codegen_codegen_su_ast(module, arena, out_buf) != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  return 0;
}

/* 包装需 int32_t/uint8_t/size_t 与 shulang_slice_uint8_t；-E 已有则只补 include */
#include <stdint.h>
#include <stddef.h>
/* C 包装：main 传 (data, len, ctx)，6.1 dep 通过 ctx 传入；struct ast_PipelineDepCtx 已由 -E 展开 ast 提供 */
int32_t pipeline_run_su_pipeline(struct ast_ASTArena *arena, struct ast_Module *module, const uint8_t *source_data, size_t source_len, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx) {
  struct shulang_slice_uint8_t source;
  source.data = (uint8_t *)source_data;
  source.length = source_len;
  return pipeline_run_su_pipeline_impl(arena, module, &source, out_buf, ctx);
}

#include <stddef.h>
#include "ast.h"
size_t pipeline_sizeof_arena(void) { return sizeof(struct ast_ASTArena); }
size_t pipeline_sizeof_module(void) { return sizeof(struct ast_Module); }

/* sizeof_elf_ctx 需 size_t 与 platform_elf 结构；无前置 include 时补上 */
#include <stddef.h>
size_t pipeline_sizeof_elf_ctx(void) { return sizeof(struct platform_elf_ElfCodegenCtx); }

/* 由 Makefile 追加到 pipeline_gen.c 末尾：调试用，打印 module 中每个函数的 name_len 与 name */
#include <stdio.h>
#include "ast.h"
void pipeline_debug_module_funcs(void *m) {
  struct ast_Module *mod = (struct ast_Module *)m;
  int i, n = (int)mod->num_funcs;
  if (n > 256) n = 256;
  for (i = 0; i < n; i++) {
    int len = (int)mod->funcs[i].name_len;
    fprintf(stderr, "[DEBUG] module func[%d] name_len=%d name=%.*s\n", i, len, len > 0 && len <= 64 ? len : 0, mod->funcs[i].name);
  }
}
