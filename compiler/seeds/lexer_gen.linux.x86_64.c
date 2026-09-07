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
#include <string.h>
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
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_TRY, token_TokenKind_TOKEN_CATCH, token_TokenKind_TOKEN_REGION, token_TokenKind_TOKEN_WITH_ARENA, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_TYPE, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_SOA, token_TokenKind_TOKEN_ATTR_SOA, token_TokenKind_TOKEN_ATTR_CFG, token_TokenKind_TOKEN_ATTR_REPR_C, token_TokenKind_TOKEN_ATTR_REPR_COMPATIBLE, token_TokenKind_TOKEN_ATTR_ALLOC, token_TokenKind_TOKEN_ATTR_LINK_SECTION, token_TokenKind_TOKEN_ATTR_NAKED, token_TokenKind_TOKEN_ATTR_ENTRY, token_TokenKind_TOKEN_ATTR_USED, token_TokenKind_TOKEN_ATTR_NO_MANGLE, token_TokenKind_TOKEN_ATTR_LINK_NAME, token_TokenKind_TOKEN_ATTR_MAX_STACK, token_TokenKind_TOKEN_ATTR_INTERRUPT, token_TokenKind_TOKEN_ATTR_SEND, token_TokenKind_TOKEN_ATTR_SYNC, token_TokenKind_TOKEN_ATTR_GLOBAL_ALLOCATOR, token_TokenKind_TOKEN_ATTR_COLD, token_TokenKind_TOKEN_ATTR_INLINE_NEVER, token_TokenKind_TOKEN_ATTR_INLINE_ALWAYS, token_TokenKind_TOKEN_ATTR_EXPORT_NAME, token_TokenKind_TOKEN_ATTR_PANIC_HANDLER, token_TokenKind_TOKEN_ATTR_THREAD_LOCAL, token_TokenKind_TOKEN_ATTR_PERCPU, token_TokenKind_TOKEN_ALIGN, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_ASYNC, token_TokenKind_TOKEN_AWAIT, token_TokenKind_TOKEN_RUN, token_TokenKind_TOKEN_SPAWN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_F32X4, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_DOTDOT, token_TokenKind_TOKEN_ELLIPSIS, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_PLUS_EQ, token_TokenKind_TOKEN_MINUS_EQ, token_TokenKind_TOKEN_STAR_EQ, token_TokenKind_TOKEN_SLASH_EQ, token_TokenKind_TOKEN_PERCENT_EQ, token_TokenKind_TOKEN_AMP_EQ, token_TokenKind_TOKEN_PIPE_EQ, token_TokenKind_TOKEN_CARET_EQ, token_TokenKind_TOKEN_LSHIFT_EQ, token_TokenKind_TOKEN_RSHIFT_EQ, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION, token_TokenKind_TOKEN_AS, token_TokenKind_TOKEN_AT, token_TokenKind_TOKEN_STRING, token_TokenKind_TOKEN_EXPORT, token_TokenKind_TOKEN_NULL };
struct token_Token { enum token_TokenKind kind; int32_t line; int32_t col; int64_t int_val; double float_val; uint8_t * ident; int32_t ident_len; };
/* slim arena grow pool glue (C-04 codegen; linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);

struct xlang_slice_uint8_t { uint8_t *data; size_t length; };
struct lexer_Lexer { size_t pos; int32_t line; int32_t col; };
struct lexer_LexerResult { struct lexer_Lexer next_lex; struct token_Token tok; size_t token_start; };
extern int32_t cfg_eval_expr_c(uint8_t * restrict start, int32_t len);
extern struct xlang_slice_uint8_t lexer_parser_slice_from_buf(uint8_t * restrict data, int32_t len);
/* wave269: L001 unclosed block comment hard diag */
extern void diag_report_with_code(const char *file, int32_t line, int32_t col,
                                  const char *kind, const char *code,
                                  const char *msg, const char *detail);
struct lexer_Lexer lexer_init();
struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c);
int lexer_is_alpha(uint8_t c);
int lexer_is_hex_digit(uint8_t c);
int lexer_is_digit_sep(struct xlang_slice_uint8_t * data, size_t pos, int32_t kind);
int32_t lexer_hex_digit_value(uint8_t c);
int lexer_is_digit(uint8_t c);
int lexer_is_alnum_underscore(uint8_t c);
int lexer_match_keyword(struct xlang_slice_uint8_t * data, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword);
int lexer_match_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword);
static void lexer_note_ident_too_long(int32_t line, int32_t col);
struct token_Token lexer_try_keyword(struct xlang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0);
struct token_Token lexer_try_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, size_t len, int32_t line0, int32_t col0);
struct lexer_Lexer lexer_skip_repr_c_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
struct lexer_Lexer lexer_skip_cfg_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
int32_t lexer_try_cfg_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_repr_c_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_repr_compatible_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_soa_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_alloc_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_used_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_naked_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_entry_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_no_mangle_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_interrupt_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_send_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
int32_t lexer_try_sync_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
struct lexer_Lexer lexer_skip_whitespace_and_comments_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult lexer_next_slice(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
int32_t lexer_apply_optional_exponent(struct lexer_Lexer l, struct xlang_slice_uint8_t * data, double fval, struct lexer_Lexer * restrict out_l, double * restrict out_f);
int32_t lexer_dot_continues_float(struct xlang_slice_uint8_t * data, size_t pos);
void lexer_next_body_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
void lexer_write_next_lex_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l);
void lexer_write_tok_into(struct lexer_LexerResult * restrict out, struct token_Token t);
void lexer_next_impl(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
void lexer_next_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
void lexer_next_buf_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult lexer_next_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len);
struct lexer_LexerResult lexer_next_body(struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
XLANG_LIB_WEAK struct lexer_Lexer lexer_init() {
  return (struct lexer_Lexer){ .pos = 0, .line = 1, .col = 1 };
}
XLANG_LIB_WEAK struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c) {
  if (c == 10) {   return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line + 1, .col = 1 };
 }
  return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line, .col = (lex).col + 1 };
}
XLANG_LIB_WEAK int lexer_is_alpha(uint8_t c) {
  if (c >= 97 && c <= 122) {   return 1;
 }
  if (c >= 65 && c <= 90) {   return 1;
 }
  return c == 95;
}
XLANG_LIB_WEAK int lexer_is_hex_digit(uint8_t c) {
  if (c >= 48 && c <= 57) {   return 1;
 }
  if (c >= 97 && c <= 102) {   return 1;
 }
  if (c >= 65 && c <= 70) {   return 1;
 }
  return 0;
}
XLANG_LIB_WEAK int lexer_is_bin_digit(uint8_t c) {
  return c == 48 || c == 49;
}
XLANG_LIB_WEAK int lexer_is_oct_digit(uint8_t c) {
  return c >= 48 && c <= 55;
}
/* wave277 Cap residual: numeric `_` separator (G.7 ≡ lexer.x lexer_is_digit_sep).
 * kind: 0=decimal, 1=hex, 2=bin, 3=oct. Requires next byte valid for kind. */
XLANG_LIB_WEAK int lexer_is_digit_sep(struct xlang_slice_uint8_t * data, size_t pos, int32_t kind) {
  if (data == 0 || pos >= (data)->length) { return 0; }
  uint8_t c = (data)->data[pos];
  if (c != 95) { return 0; }
  if (pos + 1 >= (data)->length) { return 0; }
  uint8_t n = (data)->data[pos + 1];
  if (kind == 1) { return lexer_is_hex_digit(n); }
  if (kind == 2) { return lexer_is_bin_digit(n); }
  if (kind == 3) { return lexer_is_oct_digit(n); }
  return lexer_is_digit(n);
}

XLANG_LIB_WEAK int32_t lexer_hex_digit_value(uint8_t c) {
  if (c >= 48 && c <= 57) {   return ((int32_t)(c - 48));
 }
  if (c >= 97 && c <= 102) {   return ((int32_t)((c - 97) + 10));
 }
  if (c >= 65 && c <= 70) {   return ((int32_t)((c - 65) + 10));
 }
  return 0;
}
XLANG_LIB_WEAK int lexer_is_digit(uint8_t c) {
  return c >= 48 && c <= 57;
}
XLANG_LIB_WEAK int lexer_is_alnum_underscore(uint8_t c) {
  return lexer_is_alpha(c) || lexer_is_digit(c);
}
XLANG_LIB_WEAK int lexer_match_keyword(struct xlang_slice_uint8_t * data, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword) {
  int32_t i = 0;
  while (i < len) {
    if ((start + i < 0 || (size_t)(start + i) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[start + i]) != (i < 0 || (size_t)(i) >= (keyword)->length ? (xlang_panic_(1, 0), (keyword)->data[0]) : (keyword)->data[i])) {   return 0;
 }
    ++i;
  }
  return 1;
}
XLANG_LIB_WEAK int lexer_match_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword) {
  int32_t i = 0;
  while (i < len) {
    if (((int32_t)(start)) + i >= data_len) {   return 0;
 }
    if ((data)[start + i] != (i < 0 || (size_t)(i) >= (keyword)->length ? (xlang_panic_(1, 0), (keyword)->data[0]) : (keyword)->data[i])) {   return 0;
 }
    ++i;
  }
  return 1;
}
XLANG_LIB_WEAK struct token_Token lexer_try_keyword(struct xlang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0) {
  if (len == 8 && lexer_match_keyword(data, start, 8, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 117, 110, 99, 116, 105, 111, 110 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FUNCTION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 108, 101, 116 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LET, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 115, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONST, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword(data, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 102 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 108, 115, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ELSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 119, 104, 105, 108, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_WHILE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 108, 111, 111, 112 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LOOP, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 111, 114 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FOR, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 98, 114, 101, 97, 107 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BREAK, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 8 && lexer_match_keyword(data, start, 8, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 116, 105, 110, 117, 101 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONTINUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 116, 117, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RETURN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 110, 105, 99 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PANIC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 100, 101, 102, 101, 114 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_DEFER, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 103, 105, 111, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_REGION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 10 && lexer_match_keyword(data, start, 10, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 119, 105, 116, 104, 95, 97, 114, 101, 110, 97 }, .length = 10 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_WITH_ARENA, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 109, 97, 116, 99, 104 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_MATCH, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 116, 114, 117, 99, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRUCT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 116, 121, 112, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TYPE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 99, 107, 101, 100 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PACKED, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 111, 97 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SOA, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 108, 105, 103, 110 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ALIGN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 110, 117, 109 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ENUM, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 103, 111, 116, 111 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_GOTO, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 97, 105, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRAIT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 101, 108, 102 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SELF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 1 && (start < 0 || (size_t)(start) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[start]) == 95) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_UNDERSCORE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 116, 101, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXTERN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 115, 121, 110, 99 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ASYNC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 119, 97, 105, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_AWAIT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 114, 117, 110 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RUN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 112, 97, 119, 110 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SPAWN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 98, 111, 111, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BOOL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword(data, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 56 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_USIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ISIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 117, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 97, 108, 115, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FALSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  /* wave668: null → TOKEN_NULL */
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 110, 117, 108, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_NULL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword(data, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword(data, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 118, 111, 105, 100 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_VOID, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword(data, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword(data, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword(data, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 115 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_AS, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len > 127) {
    lexer_note_ident_too_long(line0, col0);
  }
  struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IDENT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = len };
  return t;
}
XLANG_LIB_WEAK struct token_Token lexer_try_keyword_buf(uint8_t * restrict data, int32_t data_len, size_t start, size_t len, int32_t line0, int32_t col0) {
  if (len == 8 && lexer_match_keyword_buf(data, data_len, start, 8, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 117, 110, 99, 116, 105, 111, 110 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FUNCTION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 108, 101, 116 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LET, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 115, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONST, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword_buf(data, data_len, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 102 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 108, 115, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ELSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 116, 117, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RETURN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 116, 114, 117, 99, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRUCT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 116, 121, 112, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TYPE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 110, 117, 109 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ENUM, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 109, 97, 116, 99, 104 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_MATCH, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 117, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 97, 108, 115, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FALSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  /* wave668: null → TOKEN_NULL */
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 110, 117, 108, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_NULL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 102, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 118, 111, 105, 100 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_VOID, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 4 && lexer_match_keyword_buf(data, data_len, start, 4, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 98, 111, 111, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BOOL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword_buf(data, data_len, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 56 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 117, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_USIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ISIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 2 && lexer_match_keyword_buf(data, data_len, start, 2, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 115 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_AS, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 116, 101, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXTERN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 115, 121, 110, 99 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ASYNC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 97, 119, 97, 105, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_AWAIT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 3 && lexer_match_keyword_buf(data, data_len, start, 3, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 114, 117, 110 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RUN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 5 && lexer_match_keyword_buf(data, data_len, start, 5, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 115, 112, 97, 119, 110 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SPAWN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 6 && lexer_match_keyword_buf(data, data_len, start, 6, &((struct xlang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len == 1 && start < ((size_t)(data_len)) && (data)[start] == 95) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_UNDERSCORE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 }
  if (len > 127) {
    lexer_note_ident_too_long(line0, col0);
  }
  struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IDENT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = len };
  return t;
}
XLANG_LIB_WEAK struct lexer_Lexer lexer_skip_repr_c_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  struct lexer_Lexer l = lex;
  if ((l).pos + 10 > (data)->length) {   return l;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return l;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 114 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 101 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 112 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 114) {   return l;
 }
  if (((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 40 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 67 || ((l).pos + 8 < 0 || (size_t)((l).pos + 8) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 8]) != 41 || ((l).pos + 9 < 0 || (size_t)((l).pos + 9) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 9]) != 93) {   return l;
 }
  return (struct lexer_Lexer){ .pos = (l).pos + 10, .line = (l).line, .col = (l).col };
}
XLANG_LIB_WEAK struct lexer_Lexer lexer_skip_cfg_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  struct lexer_Lexer l = lex;
  size_t p = 0;
  int32_t depth = 0;
  if ((l).pos + 6 > (data)->length) {   return l;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return l;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 99 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 102 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 103) {   return l;
 }
  if (((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 40) {   return l;
 }
  (p = ((l).pos + 6));
  (depth = (1));
  while (p < (data)->length && depth > 0) {
    if ((p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) == 40) {   ++depth;
 } else     if ((p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) == 41) {   (depth = (depth - 1));
 }

    ++p;
  }
  if (p >= (data)->length || (p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) != 93) {   return lex;
 }
  ++p;
  return (struct lexer_Lexer){ .pos = p, .line = (l).line, .col = (l).col };
}
XLANG_LIB_WEAK int32_t lexer_try_cfg_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  size_t p = 0;
  int32_t depth = 0;
  size_t expr_start = 0;
  if ((l).pos + 6 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 99 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 102 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 103) {   return 0;
 }
  if (((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 40) {   return 0;
 }
  (p = ((l).pos + 6));
  (depth = (1));
  (expr_start = (p));
  while (p < (data)->length && depth > 0) {
    if ((p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) == 40) {   ++depth;
 } else     if ((p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) == 41) {   (depth = (depth - 1));
 }

    ++p;
  }
  if (p >= (data)->length || (p < 0 || (size_t)(p) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[p]) != 93) {   return 0;
 }
  int32_t expr_len = (((int32_t)(p)) - ((int32_t)(expr_start))) - 1;
  if (expr_len <= 0 || expr_len > 127) {   return 0;
 }
  uint8_t tmp[128] = { 0 };
  int32_t ti = 0;
  while (ti < expr_len) {
    ((ti < 0 || (ti) >= 128 ? (xlang_panic_(1, 0), 0) : ((tmp)[ti] = (expr_start + ((size_t)(ti)) < 0 || (size_t)(expr_start + ((size_t)(ti))) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[expr_start + ((size_t)(ti))]), 0)));
    ++ti;
  }
  int32_t enabled = cfg_eval_expr_c((&((tmp)[0])), expr_len);
  ++p;
  struct lexer_Lexer l2 = (struct lexer_Lexer){ .pos = p, .line = (l).line, .col = (l).col };
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_CFG, .line = line0, .col = col0, .int_val = enabled, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_repr_c_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 10 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 114 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 101 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 112 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 114) {   return 0;
 }
  if (((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 40 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 67 || ((l).pos + 8 < 0 || (size_t)((l).pos + 8) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 8]) != 41 || ((l).pos + 9 < 0 || (size_t)((l).pos + 9) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 9]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  size_t np = (l).pos + 10;
  struct lexer_Lexer l2 = (struct lexer_Lexer){ .pos = np, .line = line0, .col = col0 };
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_REPR_C, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_repr_compatible_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 19 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 114 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 101 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 112 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 114) {   return 0;
 }
  if (((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 40) {   return 0;
 }
  if (((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 99 || ((l).pos + 8 < 0 || (size_t)((l).pos + 8) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 8]) != 111 || ((l).pos + 9 < 0 || (size_t)((l).pos + 9) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 9]) != 109 || ((l).pos + 10 < 0 || (size_t)((l).pos + 10) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 10]) != 112 || ((l).pos + 11 < 0 || (size_t)((l).pos + 11) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 11]) != 97 || ((l).pos + 12 < 0 || (size_t)((l).pos + 12) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 12]) != 116 || ((l).pos + 13 < 0 || (size_t)((l).pos + 13) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 13]) != 105 || ((l).pos + 14 < 0 || (size_t)((l).pos + 14) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 14]) != 98 || ((l).pos + 15 < 0 || (size_t)((l).pos + 15) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 15]) != 108 || ((l).pos + 16 < 0 || (size_t)((l).pos + 16) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 16]) != 101) {   return 0;
 }
  if (((l).pos + 17 < 0 || (size_t)((l).pos + 17) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 17]) != 41 || ((l).pos + 18 < 0 || (size_t)((l).pos + 18) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 18]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  size_t np = (l).pos + 19;
  struct lexer_Lexer l2 = (struct lexer_Lexer){ .pos = np, .line = line0, .col = col0 };
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_REPR_COMPATIBLE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_soa_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 6 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 115 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 111 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 97 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 115)));
  (l2 = (lexer_advance_one(l2, 111)));
  (l2 = (lexer_advance_one(l2, 97)));
  (l2 = (lexer_advance_one(l2, 93)));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_SOA, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_alloc_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 8 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 97 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 108 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 108 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 111 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 99 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 97)));
  (l2 = (lexer_advance_one(l2, 108)));
  (l2 = (lexer_advance_one(l2, 108)));
  (l2 = (lexer_advance_one(l2, 111)));
  (l2 = (lexer_advance_one(l2, 99)));
  (l2 = (lexer_advance_one(l2, 93)));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_ALLOC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_used_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 7 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 117 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 115 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 101 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 100 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 117)));
  (l2 = (lexer_advance_one(l2, 115)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 100)));
  (l2 = (lexer_advance_one(l2, 93)));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_USED, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_naked_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 8 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 110 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 97 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 107 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 101 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 100 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 97)));
  (l2 = (lexer_advance_one(l2, 107)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 100)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_NAKED, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_entry_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 8 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 101 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 110 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 116 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 114 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 121 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 116)));
  (l2 = (lexer_advance_one(l2, 114)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_ENTRY, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_no_mangle_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 12 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 110 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 111 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 95 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 109 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 97 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 110 || ((l).pos + 8 < 0 || (size_t)((l).pos + 8) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 8]) != 103 || ((l).pos + 9 < 0 || (size_t)((l).pos + 9) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 9]) != 108 || ((l).pos + 10 < 0 || (size_t)((l).pos + 10) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 10]) != 101 || ((l).pos + 11 < 0 || (size_t)((l).pos + 11) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 11]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 111)));
  (l2 = (lexer_advance_one(l2, 95)));
  (l2 = (lexer_advance_one(l2, 109)));
  (l2 = (lexer_advance_one(l2, 97)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 103)));
  (l2 = (lexer_advance_one(l2, 108)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_NO_MANGLE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_interrupt_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 13 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 105 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 110 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 116 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 101 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 114 || ((l).pos + 7 < 0 || (size_t)((l).pos + 7) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 7]) != 114 || ((l).pos + 8 < 0 || (size_t)((l).pos + 8) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 8]) != 117 || ((l).pos + 9 < 0 || (size_t)((l).pos + 9) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 9]) != 112 || ((l).pos + 10 < 0 || (size_t)((l).pos + 10) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 10]) != 116 || ((l).pos + 11 < 0 || (size_t)((l).pos + 11) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 11]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 105)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 116)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 114)));
  (l2 = (lexer_advance_one(l2, 114)));
  (l2 = (lexer_advance_one(l2, 117)));
  (l2 = (lexer_advance_one(l2, 112)));
  (l2 = (lexer_advance_one(l2, 116)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_INTERRUPT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_send_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 8 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 115 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 101 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 110 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 100 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 115)));
  (l2 = (lexer_advance_one(l2, 101)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 100)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_SEND, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_try_sync_attr_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  if ((l).pos + 8 > (data)->length) {   return 0;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 35 || ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) != 91) {   return 0;
 }
  if (((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]) != 115 || ((l).pos + 3 < 0 || (size_t)((l).pos + 3) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 3]) != 121 || ((l).pos + 4 < 0 || (size_t)((l).pos + 4) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 4]) != 110 || ((l).pos + 5 < 0 || (size_t)((l).pos + 5) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 5]) != 99 || ((l).pos + 6 < 0 || (size_t)((l).pos + 6) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 6]) != 93) {   return 0;
 }
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct lexer_Lexer l2 = l;
  (l2 = (lexer_advance_one(l2, 35)));
  (l2 = (lexer_advance_one(l2, 91)));
  (l2 = (lexer_advance_one(l2, 115)));
  (l2 = (lexer_advance_one(l2, 121)));
  (l2 = (lexer_advance_one(l2, 110)));
  (l2 = (lexer_advance_one(l2, 99)));
  (l2 = (lexer_advance_one(l2, 93)));
  (void)(lexer_write_next_lex_into(out, l2));
  (void)(lexer_write_tok_into(out, (struct token_Token){ .kind = token_TokenKind_TOKEN_ATTR_SYNC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }));
  ((out)->token_start = (((size_t)(0))));
  return 1;
}
/* PLATFORM: SHARED — nested block comments; path-safe nest-open; lockstep with lexer.x.
 * wave269: EOF depth>0 → L001 unclosed block comment hard diag + sticky pending. */
static int lexer_block_comment_prev_is_path_like(uint8_t prev) {
  if (prev >= 65 && prev <= 90)
    return 1;
  if (prev >= 97 && prev <= 122)
    return 1;
  if (prev >= 48 && prev <= 57)
    return 1;
  if (prev == 95 || prev == 46 || prev == 125 || prev == 41 || prev == 93 || prev == 62
      || prev == 34 || prev == 39)
    return 1;
  return 0;
}
/* wave269 Cap residual: sticky unclosed block-comment state (≡ lexer.x). */
static int32_t g_lexer_unclosed_bc = 0;
static int32_t g_lexer_unclosed_line = 0;
static int32_t g_lexer_unclosed_col = 0;
static int32_t g_lexer_unclosed_reported = 0;
/* wave271 Cap residual: sticky unclosed string state (≡ lexer.x). */
static int32_t g_lexer_unclosed_str = 0;
static int32_t g_lexer_unclosed_str_line = 0;
static int32_t g_lexer_unclosed_str_col = 0;
static int32_t g_lexer_unclosed_str_reported = 0;
/* wave272 Cap residual: sticky illegal character state (≡ lexer.x). */
static int32_t g_lexer_illegal_ch = 0;
static int32_t g_lexer_illegal_ch_line = 0;
static int32_t g_lexer_illegal_ch_col = 0;
static int32_t g_lexer_illegal_ch_reported = 0;
/* wave273 Cap residual: sticky incomplete hex state (≡ lexer.x). */
static int32_t g_lexer_incomplete_hex = 0;
static int32_t g_lexer_incomplete_hex_line = 0;
static int32_t g_lexer_incomplete_hex_col = 0;
static int32_t g_lexer_incomplete_hex_reported = 0;

/* wave274 Cap residual: sticky incomplete float-exponent state (≡ lexer.x). */
static int32_t g_lexer_incomplete_exp = 0;
static int32_t g_lexer_incomplete_exp_line = 0;
static int32_t g_lexer_incomplete_exp_col = 0;
static int32_t g_lexer_incomplete_exp_reported = 0;
/* wave276 Cap residual: sticky incomplete binary state (≡ lexer.x). */
static int32_t g_lexer_incomplete_bin = 0;
static int32_t g_lexer_incomplete_bin_line = 0;
static int32_t g_lexer_incomplete_bin_col = 0;
static int32_t g_lexer_incomplete_bin_reported = 0;
/* wave276 Cap residual: sticky incomplete octal state (≡ lexer.x). */
static int32_t g_lexer_incomplete_oct = 0;
static int32_t g_lexer_incomplete_oct_line = 0;
static int32_t g_lexer_incomplete_oct_col = 0;
static int32_t g_lexer_incomplete_oct_reported = 0;
/* wave278: invalid digit separator sticky (G.7 ≡ lexer.x). */
static int32_t g_lexer_invalid_digit_sep = 0;
static int32_t g_lexer_invalid_digit_sep_line = 0;
static int32_t g_lexer_invalid_digit_sep_col = 0;
static int32_t g_lexer_invalid_digit_sep_reported = 0;

/* wave279: invalid type suffix sticky (G.7 ≡ lexer.x). */
static int32_t g_lexer_invalid_type_suffix = 0;
static int32_t g_lexer_invalid_type_suffix_line = 0;
static int32_t g_lexer_invalid_type_suffix_col = 0;
static int32_t g_lexer_invalid_type_suffix_reported = 0;
/* wave281 Cap residual: L010 invalid string escape sticky (G.7 ≡ lexer.x). */
static int32_t g_lexer_invalid_escape = 0;
static int32_t g_lexer_invalid_escape_line = 0;
static int32_t g_lexer_invalid_escape_col = 0;
static int32_t g_lexer_invalid_escape_reported = 0;
/* wave283 Cap residual: L011 string literal capacity overflow sticky (G.7 ≡ lexer.x). */
static int32_t g_lexer_string_lit_overflow = 0;
static int32_t g_lexer_string_lit_overflow_line = 0;
static int32_t g_lexer_string_lit_overflow_col = 0;
static int32_t g_lexer_string_lit_overflow_reported = 0;

/* wave284 Cap residual: L012 identifier too long sticky (G.7 ≡ lexer.x). */
static int32_t g_lexer_ident_too_long = 0;
static int32_t g_lexer_ident_too_long_line = 0;
static int32_t g_lexer_ident_too_long_col = 0;
static int32_t g_lexer_ident_too_long_reported = 0;

void lexer_unclosed_block_comment_reset(void) {
  g_lexer_unclosed_bc = 0;
  g_lexer_unclosed_line = 0;
  g_lexer_unclosed_col = 0;
  g_lexer_unclosed_reported = 0;
}
int32_t lexer_unclosed_block_comment_pending(void) {
  return g_lexer_unclosed_bc;
}
void lexer_unclosed_string_reset(void) {
  g_lexer_unclosed_str = 0;
  g_lexer_unclosed_str_line = 0;
  g_lexer_unclosed_str_col = 0;
  g_lexer_unclosed_str_reported = 0;
}
int32_t lexer_unclosed_string_pending(void) {
  return g_lexer_unclosed_str;
}
void lexer_illegal_char_reset(void) {
  g_lexer_illegal_ch = 0;
  g_lexer_illegal_ch_line = 0;
  g_lexer_illegal_ch_col = 0;
  g_lexer_illegal_ch_reported = 0;
}
int32_t lexer_illegal_char_pending(void) {
  return g_lexer_illegal_ch;
}
void lexer_incomplete_hex_reset(void) {
  g_lexer_incomplete_hex = 0;
  g_lexer_incomplete_hex_line = 0;
  g_lexer_incomplete_hex_col = 0;
  g_lexer_incomplete_hex_reported = 0;
}
int32_t lexer_incomplete_hex_pending(void) {
  return g_lexer_incomplete_hex;
}

void lexer_incomplete_exp_reset(void) {
  g_lexer_incomplete_exp = 0;
  g_lexer_incomplete_exp_line = 0;
  g_lexer_incomplete_exp_col = 0;
  g_lexer_incomplete_exp_reported = 0;
}
int32_t lexer_incomplete_exp_pending(void) {
  return g_lexer_incomplete_exp;
}
void lexer_incomplete_bin_reset(void) {
  g_lexer_incomplete_bin = 0;
  g_lexer_incomplete_bin_line = 0;
  g_lexer_incomplete_bin_col = 0;
  g_lexer_incomplete_bin_reported = 0;
}
int32_t lexer_incomplete_bin_pending(void) {
  return g_lexer_incomplete_bin;
}
void lexer_incomplete_oct_reset(void) {
  g_lexer_incomplete_oct = 0;
  g_lexer_incomplete_oct_line = 0;
  g_lexer_incomplete_oct_col = 0;
  g_lexer_incomplete_oct_reported = 0;
}
int32_t lexer_incomplete_oct_pending(void) {
  return g_lexer_incomplete_oct;
}
/* wave278 Cap residual: clear invalid digit-sep sticky (≡ lexer.x). */
void lexer_invalid_digit_sep_reset(void) {
  g_lexer_invalid_digit_sep = 0;
  g_lexer_invalid_digit_sep_line = 0;
  g_lexer_invalid_digit_sep_col = 0;
  g_lexer_invalid_digit_sep_reported = 0;
}
int32_t lexer_invalid_digit_sep_pending(void) {
  return g_lexer_invalid_digit_sep;
}

/* wave279 Cap residual: clear invalid type-suffix sticky (≡ lexer.x). */
void lexer_invalid_type_suffix_reset(void) {
  g_lexer_invalid_type_suffix = 0;
  g_lexer_invalid_type_suffix_line = 0;
  g_lexer_invalid_type_suffix_col = 0;
  g_lexer_invalid_type_suffix_reported = 0;
}
int32_t lexer_invalid_type_suffix_pending(void) {
  return g_lexer_invalid_type_suffix;
}
/* wave281 Cap residual: clear invalid string-escape sticky (≡ lexer.x). */
void lexer_invalid_escape_reset(void) {
  g_lexer_invalid_escape = 0;
  g_lexer_invalid_escape_line = 0;
  g_lexer_invalid_escape_col = 0;
  g_lexer_invalid_escape_reported = 0;
}
int32_t lexer_invalid_escape_pending(void) {
  return g_lexer_invalid_escape;
}

/* wave283 Cap residual: L011 string lit capacity overflow (G.7 ≡ lexer.x). */
void lexer_string_lit_overflow_reset(void) {
  g_lexer_string_lit_overflow = 0;
  g_lexer_string_lit_overflow_line = 0;
  g_lexer_string_lit_overflow_col = 0;
  g_lexer_string_lit_overflow_reported = 0;
}
int32_t lexer_string_lit_overflow_pending(void) {
  return g_lexer_string_lit_overflow;
}
static void lexer_note_incomplete_bin(int32_t line, int32_t col) {
  if (g_lexer_incomplete_bin == 0) {
    g_lexer_incomplete_bin = 1;
    g_lexer_incomplete_bin_line = line;
    g_lexer_incomplete_bin_col = col;
  }
  if (g_lexer_incomplete_bin_reported != 0)
    return;
  g_lexer_incomplete_bin_reported = 1;
  /* kind="lexer error" code="L006" msg="incomplete binary literal" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '6'; code[4] = 0;
    msg[0] = 'i'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'o'; msg[4] = 'm';
    msg[5] = 'p'; msg[6] = 'l'; msg[7] = 'e'; msg[8] = 't'; msg[9] = 'e';
    msg[10] = ' '; msg[11] = 'b'; msg[12] = 'i'; msg[13] = 'n'; msg[14] = 'a';
    msg[15] = 'r'; msg[16] = 'y'; msg[17] = ' '; msg[18] = 'l'; msg[19] = 'i';
    msg[20] = 't'; msg[21] = 'e'; msg[22] = 'r'; msg[23] = 'a'; msg[24] = 'l';
    msg[25] = 0;
    diag_report_with_code(NULL, g_lexer_incomplete_bin_line, g_lexer_incomplete_bin_col,
                          kind, code, msg, NULL);
  }
}
static void lexer_note_incomplete_oct(int32_t line, int32_t col) {
  if (g_lexer_incomplete_oct == 0) {
    g_lexer_incomplete_oct = 1;
    g_lexer_incomplete_oct_line = line;
    g_lexer_incomplete_oct_col = col;
  }
  if (g_lexer_incomplete_oct_reported != 0)
    return;
  g_lexer_incomplete_oct_reported = 1;
  /* kind="lexer error" code="L007" msg="incomplete octal literal" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '7'; code[4] = 0;
    msg[0] = 'i'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'o'; msg[4] = 'm';
    msg[5] = 'p'; msg[6] = 'l'; msg[7] = 'e'; msg[8] = 't'; msg[9] = 'e';
    msg[10] = ' '; msg[11] = 'o'; msg[12] = 'c'; msg[13] = 't'; msg[14] = 'a';
    msg[15] = 'l'; msg[16] = ' '; msg[17] = 'l'; msg[18] = 'i'; msg[19] = 't';
    msg[20] = 'e'; msg[21] = 'r'; msg[22] = 'a'; msg[23] = 'l'; msg[24] = 0;
    diag_report_with_code(NULL, g_lexer_incomplete_oct_line, g_lexer_incomplete_oct_col,
                          kind, code, msg, NULL);
  }
}
/* wave278 Cap residual: L008 invalid digit separator (G.7 ≡ lexer.x). */
static void lexer_note_invalid_digit_sep(int32_t line, int32_t col) {
  if (g_lexer_invalid_digit_sep == 0) {
    g_lexer_invalid_digit_sep = 1;
    g_lexer_invalid_digit_sep_line = line;
    g_lexer_invalid_digit_sep_col = col;
  }
  if (g_lexer_invalid_digit_sep_reported != 0) {
    return;
  }
  g_lexer_invalid_digit_sep_reported = 1;
  {
    char kind[] = "lexer error";
    char code[] = "L008";
    char msg[] = "invalid digit separator";
    diag_report_with_code(NULL, g_lexer_invalid_digit_sep_line, g_lexer_invalid_digit_sep_col,
                          (uint8_t *)kind, (uint8_t *)code, (uint8_t *)msg, (uint8_t *)0);
  }
}

/* wave279 Cap residual: L009 invalid type suffix (G.7 ≡ lexer.x). */
static void lexer_note_invalid_type_suffix(int32_t line, int32_t col) {
  if (g_lexer_invalid_type_suffix == 0) {
    g_lexer_invalid_type_suffix = 1;
    g_lexer_invalid_type_suffix_line = line;
    g_lexer_invalid_type_suffix_col = col;
  }
  if (g_lexer_invalid_type_suffix_reported != 0) {
    return;
  }
  g_lexer_invalid_type_suffix_reported = 1;
  {
    char kind[] = "lexer error";
    char code[] = "L009";
    char msg[] = "invalid type suffix";
    diag_report_with_code(NULL, g_lexer_invalid_type_suffix_line, g_lexer_invalid_type_suffix_col,
                          (uint8_t *)kind, (uint8_t *)code, (uint8_t *)msg, (uint8_t *)0);
  }
}
/* wave281 Cap residual: L010 invalid string escape (G.7 ≡ lexer.x). */
static void lexer_note_invalid_escape(int32_t line, int32_t col) {
  if (g_lexer_invalid_escape == 0) {
    g_lexer_invalid_escape = 1;
    g_lexer_invalid_escape_line = line;
    g_lexer_invalid_escape_col = col;
  }
  if (g_lexer_invalid_escape_reported != 0) {
    return;
  }
  g_lexer_invalid_escape_reported = 1;
  {
    char kind[] = "lexer error";
    char code[] = "L010";
    char msg[] = "invalid escape sequence";
    diag_report_with_code(NULL, g_lexer_invalid_escape_line, g_lexer_invalid_escape_col,
                          (uint8_t *)kind, (uint8_t *)code, (uint8_t *)msg, (uint8_t *)0);
  }
}

/* wave283 Cap residual: L011 string literal too long (G.7 ≡ lexer.x export). */
void lexer_note_string_lit_overflow(int32_t line, int32_t col) {
  if (g_lexer_string_lit_overflow == 0) {
    g_lexer_string_lit_overflow = 1;
    g_lexer_string_lit_overflow_line = line;
    g_lexer_string_lit_overflow_col = col;
  }
  if (g_lexer_string_lit_overflow_reported != 0) {
    return;
  }
  g_lexer_string_lit_overflow_reported = 1;
  {
    char kind[] = "lexer error";
    char code[] = "L011";
    char msg[] = "string literal too long";
    diag_report_with_code(NULL, g_lexer_string_lit_overflow_line, g_lexer_string_lit_overflow_col,
                          (uint8_t *)kind, (uint8_t *)code, (uint8_t *)msg, (uint8_t *)0);
  }
}

/* wave284 Cap residual: L012 identifier capacity overflow (G.7 ≡ lexer.x). */
void lexer_ident_too_long_reset(void) {
  g_lexer_ident_too_long = 0;
  g_lexer_ident_too_long_line = 0;
  g_lexer_ident_too_long_col = 0;
  g_lexer_ident_too_long_reported = 0;
}
int32_t lexer_ident_too_long_pending(void) {
  return g_lexer_ident_too_long;
}
/* wave284 Cap residual: L012 identifier too long (G.7 ≡ lexer.x). */
static void lexer_note_ident_too_long(int32_t line, int32_t col) {
  if (g_lexer_ident_too_long == 0) {
    g_lexer_ident_too_long = 1;
    g_lexer_ident_too_long_line = line;
    g_lexer_ident_too_long_col = col;
  }
  if (g_lexer_ident_too_long_reported != 0) {
    return;
  }
  g_lexer_ident_too_long_reported = 1;
  {
    char kind[] = "lexer error";
    char code[] = "L012";
    char msg[] = "identifier too long";
    diag_report_with_code(NULL, g_lexer_ident_too_long_line, g_lexer_ident_too_long_col,
                          (uint8_t *)kind, (uint8_t *)code, (uint8_t *)msg, (uint8_t *)0);
  }
}


static void lexer_note_incomplete_exp(int32_t line, int32_t col) {
  if (g_lexer_incomplete_exp == 0) {
    g_lexer_incomplete_exp = 1;
    g_lexer_incomplete_exp_line = line;
    g_lexer_incomplete_exp_col = col;
  }
  if (g_lexer_incomplete_exp_reported != 0)
    return;
  g_lexer_incomplete_exp_reported = 1;
  /* kind="lexer error" code="L005" msg="incomplete float exponent" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '5'; code[4] = 0;
    msg[0] = 'i'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'o'; msg[4] = 'm';
    msg[5] = 'p'; msg[6] = 'l'; msg[7] = 'e'; msg[8] = 't'; msg[9] = 'e';
    msg[10] = ' '; msg[11] = 'f'; msg[12] = 'l'; msg[13] = 'o'; msg[14] = 'a';
    msg[15] = 't'; msg[16] = ' '; msg[17] = 'e'; msg[18] = 'x'; msg[19] = 'p';
    msg[20] = 'o'; msg[21] = 'n'; msg[22] = 'e'; msg[23] = 'n'; msg[24] = 't';
    msg[25] = 0;
    diag_report_with_code(NULL, g_lexer_incomplete_exp_line, g_lexer_incomplete_exp_col,
                          kind, code, msg, NULL);
  }
}
static void lexer_note_unclosed_block_comment(int32_t line, int32_t col) {
  if (g_lexer_unclosed_bc == 0) {
    g_lexer_unclosed_bc = 1;
    g_lexer_unclosed_line = line;
    g_lexer_unclosed_col = col;
  }
  if (g_lexer_unclosed_reported != 0)
    return;
  g_lexer_unclosed_reported = 1;
  /* kind="lexer error" code="L001" msg="unclosed block comment" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '1'; code[4] = 0;
    msg[0] = 'u'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'l'; msg[4] = 'o';
    msg[5] = 's'; msg[6] = 'e'; msg[7] = 'd'; msg[8] = ' '; msg[9] = 'b';
    msg[10] = 'l'; msg[11] = 'o'; msg[12] = 'c'; msg[13] = 'k'; msg[14] = ' ';
    msg[15] = 'c'; msg[16] = 'o'; msg[17] = 'm'; msg[18] = 'm'; msg[19] = 'e';
    msg[20] = 'n'; msg[21] = 't'; msg[22] = 0;
    diag_report_with_code(NULL, g_lexer_unclosed_line, g_lexer_unclosed_col,
                          kind, code, msg, NULL);
  }
}
static void lexer_note_unclosed_string(int32_t line, int32_t col) {
  if (g_lexer_unclosed_str == 0) {
    g_lexer_unclosed_str = 1;
    g_lexer_unclosed_str_line = line;
    g_lexer_unclosed_str_col = col;
  }
  if (g_lexer_unclosed_str_reported != 0)
    return;
  g_lexer_unclosed_str_reported = 1;
  /* kind="lexer error" code="L002" msg="unclosed string literal" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '2'; code[4] = 0;
    msg[0] = 'u'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'l'; msg[4] = 'o';
    msg[5] = 's'; msg[6] = 'e'; msg[7] = 'd'; msg[8] = ' '; msg[9] = 's';
    msg[10] = 't'; msg[11] = 'r'; msg[12] = 'i'; msg[13] = 'n'; msg[14] = 'g';
    msg[15] = ' '; msg[16] = 'l'; msg[17] = 'i'; msg[18] = 't'; msg[19] = 'e';
    msg[20] = 'r'; msg[21] = 'a'; msg[22] = 'l'; msg[23] = 0;
    diag_report_with_code(NULL, g_lexer_unclosed_str_line, g_lexer_unclosed_str_col,
                          kind, code, msg, NULL);
  }
}
static void lexer_note_illegal_char(int32_t line, int32_t col) {
  if (g_lexer_illegal_ch == 0) {
    g_lexer_illegal_ch = 1;
    g_lexer_illegal_ch_line = line;
    g_lexer_illegal_ch_col = col;
  }
  if (g_lexer_illegal_ch_reported != 0)
    return;
  g_lexer_illegal_ch_reported = 1;
  /* kind="lexer error" code="L003" msg="illegal character" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '3'; code[4] = 0;
    msg[0] = 'i'; msg[1] = 'l'; msg[2] = 'l'; msg[3] = 'e'; msg[4] = 'g';
    msg[5] = 'a'; msg[6] = 'l'; msg[7] = ' '; msg[8] = 'c'; msg[9] = 'h';
    msg[10] = 'a'; msg[11] = 'r'; msg[12] = 'a'; msg[13] = 'c'; msg[14] = 't';
    msg[15] = 'e'; msg[16] = 'r'; msg[17] = 0;
    diag_report_with_code(NULL, g_lexer_illegal_ch_line, g_lexer_illegal_ch_col,
                          kind, code, msg, NULL);
  }
}
static void lexer_note_incomplete_hex(int32_t line, int32_t col) {
  if (g_lexer_incomplete_hex == 0) {
    g_lexer_incomplete_hex = 1;
    g_lexer_incomplete_hex_line = line;
    g_lexer_incomplete_hex_col = col;
  }
  if (g_lexer_incomplete_hex_reported != 0)
    return;
  g_lexer_incomplete_hex_reported = 1;
  /* kind="lexer error" code="L004" msg="incomplete hex literal" */
  {
    char kind[16];
    char code[8];
    char msg[32];
    kind[0] = 'l'; kind[1] = 'e'; kind[2] = 'x'; kind[3] = 'e'; kind[4] = 'r';
    kind[5] = ' '; kind[6] = 'e'; kind[7] = 'r'; kind[8] = 'r'; kind[9] = 'o';
    kind[10] = 'r'; kind[11] = 0;
    code[0] = 'L'; code[1] = '0'; code[2] = '0'; code[3] = '4'; code[4] = 0;
    msg[0] = 'i'; msg[1] = 'n'; msg[2] = 'c'; msg[3] = 'o'; msg[4] = 'm';
    msg[5] = 'p'; msg[6] = 'l'; msg[7] = 'e'; msg[8] = 't'; msg[9] = 'e';
    msg[10] = ' '; msg[11] = 'h'; msg[12] = 'e'; msg[13] = 'x'; msg[14] = ' ';
    msg[15] = 'l'; msg[16] = 'i'; msg[17] = 't'; msg[18] = 'e'; msg[19] = 'r';
    msg[20] = 'a'; msg[21] = 'l'; msg[22] = 0;
    diag_report_with_code(NULL, g_lexer_incomplete_hex_line, g_lexer_incomplete_hex_col,
                          kind, code, msg, NULL);
  }
}
XLANG_LIB_WEAK struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  struct lexer_Lexer l = lex;
  int32_t depth = 0;
  while ((l).pos < (data)->length) {
    uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    if (c == 32 || c == 9 || c == 10 || c == 13) {
      (l = (lexer_advance_one(l, c)));
    } else if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {
      while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
        (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
      }
    } else if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 42) {
      int32_t open_line = (l).line;
      int32_t open_col = (l).col;
      (l = (lexer_advance_one(l, 47)));
      (l = (lexer_advance_one(l, 42)));
      depth = 1;
      while ((l).pos < (data)->length && depth > 0) {
        if ((l).pos + 1 < (data)->length
            && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 47
            && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 42) {
          /* Path-safe nest-open: suppress src star-slash globs and brace globs. */
          int nest_ok = 1;
          if ((l).pos > 0) {
            uint8_t prev = ((l).pos - 1 < 0 || (size_t)((l).pos - 1) >= (data)->length
                                ? (xlang_panic_(1, 0), (data)->data[0])
                                : (data)->data[(l).pos - 1]);
            if (lexer_block_comment_prev_is_path_like(prev))
              nest_ok = 0;
          }
          if (nest_ok && (l).pos + 2 < (data)->length) {
            uint8_t after = ((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length
                                 ? (xlang_panic_(1, 0), (data)->data[0])
                                 : (data)->data[(l).pos + 2]);
            if (after == 46) /* '.' after open: path-style star-dot extension */
              nest_ok = 0;
          }
          if (nest_ok) {
            (l = (lexer_advance_one(l, 47)));
            (l = (lexer_advance_one(l, 42)));
            depth = depth + 1;
          } else {
            (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
          }
        } else if ((l).pos + 1 < (data)->length
            && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 42
            && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {
          (l = (lexer_advance_one(l, 42)));
          (l = (lexer_advance_one(l, 47)));
          depth = depth - 1;
        } else {
          (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
        }
      }
      /* wave269: EOF with depth > 0 → L001 hard diag + sticky pending. */
      if (depth > 0)
        lexer_note_unclosed_block_comment(open_line, open_col);
      depth = 0;
    } else if (c == 35) {
      if ((l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 91) {
        return l;
      } else {
        while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
          (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
        }
      }
    } else {
      return l;
    }
  }
  return l;
}
XLANG_LIB_WEAK struct lexer_Lexer lexer_skip_whitespace_and_comments_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct xlang_slice_uint8_t source = lexer_parser_slice_from_buf(data, len);
  return lexer_skip_whitespace_and_comments(lex, &(source));
}
XLANG_LIB_WEAK struct lexer_LexerResult lexer_next_slice(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  struct lexer_Lexer l = lexer_skip_whitespace_and_comments(lex, data);
  if ((l).pos >= (data)->length) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t, .token_start = ((size_t)(0)) };
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 0) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t, .token_start = ((size_t)(0)) };
 }
  struct lexer_LexerResult attr_out = (struct lexer_LexerResult){ .next_lex = l, .tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = ((size_t)(0)) };
  if (lexer_try_cfg_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_repr_c_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_repr_compatible_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_soa_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_alloc_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_used_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_naked_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_entry_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_no_mangle_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_interrupt_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_send_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  if (lexer_try_sync_attr_into((&(attr_out)), l, data) != 0) {   return attr_out;
 }
  return lexer_next_body(l, data);
}

/* wave275 Cap residual: empty-fraction float after `.` (≡ lexer.x lexer_dot_continues_float).
 * PLATFORM: SHARED — seed pin twin of product lexer.x. */
XLANG_LIB_WEAK int32_t lexer_dot_continues_float(struct xlang_slice_uint8_t * data, size_t pos) {
  uint8_t n;
  if (!data || pos >= (size_t)(data)->length)
    return 0;
  if (((pos < 0 || (size_t)(pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[pos])) != 46)
    return 0;
  if (pos + 1 >= (size_t)(data)->length)
    return 1;
  n = ((pos + 1 < 0 || (size_t)(pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[pos + 1]));
  if (n == 46)
    return 0;
  if (lexer_is_digit(n))
    return 1;
  if (n == 101 || n == 69)
    return 1;
  if (lexer_is_alpha(n) || n == 95)
    return 0;
  return 1;
}
XLANG_LIB_WEAK int32_t lexer_apply_optional_exponent(struct lexer_Lexer l, struct xlang_slice_uint8_t * data, double fval, struct lexer_Lexer * restrict out_l, double * restrict out_f) {
  struct lexer_Lexer lex = l;
  double cur = fval;
  if ((lex).pos < (data)->length && (((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]) == 101 || ((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]) == 69)) {
  int32_t e_line = (lex).line;
  int32_t e_col = (lex).col;
  (lex = (lexer_advance_one(lex, ((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]))));
  int32_t exp_sign = 1;
  if ((lex).pos < (data)->length && ((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]) == 45) {   (exp_sign = ((-1)));
  (lex = (lexer_advance_one(lex, 45)));
 } else {   if ((lex).pos < (data)->length && ((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]) == 43) {   (lex = (lexer_advance_one(lex, 43)));
 }
 }
  int32_t exp = 0;
  int32_t exp_digits = 0;
  /* wave277: `_` optional-exponent digit separators (≡ lexer.x). */
  while ((lex).pos < (data)->length) {
    if (lexer_is_digit(((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]))) {
      uint8_t d = ((lex).pos < 0 || (size_t)((lex).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(lex).pos]);
      (lex = (lexer_advance_one(lex, d)));
      (exp = (exp * 10 + (d - 48)));
      exp_digits = exp_digits + 1;
    } else if (lexer_is_digit_sep(data, (lex).pos, 0)) {
      (lex = (lexer_advance_one(lex, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` in optional exp → sticky L008. */
  if (((lex).pos < (data)->length) && (((uint8_t *)(data)->data)[(lex).pos] == 95)) {
    lexer_note_invalid_digit_sep((lex).line, (lex).col);
    ((out_l)[0] = (lex));
    ((out_f)[0] = (cur));
    return -1;
  }
  /* wave274: require ≥1 exp digit after e/E (≡ lexer.x L005). */
  if (exp_digits == 0) {
    lexer_note_incomplete_exp(e_line, e_col);
    ((out_l)[0] = (lex));
    ((out_f)[0] = (cur));
    return -1;
  }
  (exp = (exp * exp_sign));
  double scale = 1;
  int32_t e = 0;
  if (exp > 0) {   while (e < exp) {
    (scale = (scale * 10));
    ++e;
  }
 } else {   while (e > exp) {
    (scale = (scale * 0.1));
    (e = (e - 1));
  }
 }
  (cur = (fval * scale));
 }
  ((out_l)[0] = (lex));
  ((out_f)[0] = (cur));
  return 0;
}
XLANG_LIB_WEAK void lexer_next_body_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
  if (lexer_try_cfg_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_repr_c_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_repr_compatible_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_soa_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_alloc_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_used_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_naked_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_entry_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_no_mangle_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_interrupt_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_send_attr_into(out, l, data) != 0) {   return;
 }
  if (lexer_try_sync_attr_into(out, l, data) != 0) {   return;
 }
  if (c == 34) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  size_t start = (l).pos + 1;
  (l = (lexer_advance_one(l, 34)));
  /* wave281: validate escapes; product set \n \t \r \0 \\ \" \xHH; else sticky L010. */
  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 34) {
    uint8_t ch = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    if (ch == 92) {
      if ((l).pos + 1 >= (data)->length) {
        (l = (lexer_advance_one(l, 92)));
        continue;
      }
      int32_t esc_line = (l).line;
      int32_t esc_col = (l).col;
      (l = (lexer_advance_one(l, 92)));
      uint8_t e = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      if (e == 110 || e == 116 || e == 114 || e == 48 || e == 92 || e == 34) {
        (l = (lexer_advance_one(l, e)));
        continue;
      }
      if (e == 120) {
        if ((l).pos + 2 < (data)->length &&
            lexer_is_hex_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1])) &&
            lexer_is_hex_digit(((l).pos + 2 < 0 || (size_t)((l).pos + 2) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 2]))) {
          (l = (lexer_advance_one(l, 120)));
          (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
          (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
          continue;
        }
        lexer_note_invalid_escape(esc_line, esc_col);
        struct token_Token tok_eof_hex = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = esc_line, .col = esc_col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
        (void)(lexer_write_next_lex_into(out, l));
        (void)(lexer_write_tok_into(out, tok_eof_hex));
        ((out)->token_start = (start));
        return;
      }
      lexer_note_invalid_escape(esc_line, esc_col);
      struct token_Token tok_eof_esc = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = esc_line, .col = esc_col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
      (void)(lexer_write_next_lex_into(out, l));
      (void)(lexer_write_tok_into(out, tok_eof_esc));
      ((out)->token_start = (start));
      return;
    }
    (l = (lexer_advance_one(l, ch)));
  }
  if ((l).pos >= (data)->length) {
  /* wave271: unclosed string at EOF → L002 hard diag + sticky pending. */
  lexer_note_unclosed_string(line0, col0);
  struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok_eof));
  ((out)->token_start = (start));
  return;
 }
  int32_t slen = ((int32_t)((l).pos - start));
  (l = (lexer_advance_one(l, 34)));
  struct token_Token tok_str = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRING, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = slen };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok_str));
  ((out)->token_start = (start));
  return;
 }
  if (lexer_is_alpha(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, c)));
  while ((l).pos < (data)->length && lexer_is_alnum_underscore(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  size_t len = (l).pos - start;
  struct token_Token tok = lexer_try_keyword(data, start, len, line0, col0);
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (lexer_is_digit(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  int64_t ival = 0;
  (l = (lexer_advance_one(l, c)));
  if (c == 48 && (l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 120 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 88) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  /* wave273: require ≥1 hex digit after 0x/0X (≡ lexer.x L004). */
  uint64_t hval = ((uint64_t)(0));
  int32_t hex_digits = 0;
  /* wave277: `_` hex digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_hex_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t hd = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (hval = (hval * 16 + ((uint64_t)(lexer_hex_digit_value(hd)))));
      (l = (lexer_advance_one(l, hd)));
      hex_digits = hex_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 1)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  if (hex_digits == 0) {
    lexer_note_incomplete_hex(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(hval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  
 /* wave276: binary 0b/0B (≥1 bin digit → TOKEN_INT; else L006). */
 if (c == 48 && (l).pos < (data)->length && (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 98 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 66)) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  uint64_t bval = ((uint64_t)(0));
  int32_t bin_digits = 0;
  /* wave277: `_` bin digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_bin_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t bd = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (bval = (bval * 2 + ((uint64_t)(bd - 48))));
      (l = (lexer_advance_one(l, bd)));
      bin_digits = bin_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 2)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  if (bin_digits == 0) {
    lexer_note_incomplete_bin(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok_b = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(bval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok_b));
  ((out)->token_start = (start));
  return;
 }
 /* wave276: octal 0o/0O (≥1 oct digit → TOKEN_INT; else L007). */
 if (c == 48 && (l).pos < (data)->length && (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 111 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 79)) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  uint64_t oval = ((uint64_t)(0));
  int32_t oct_digits = 0;
  /* wave277: `_` oct digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_oct_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t od = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (oval = (oval * 8 + ((uint64_t)(od - 48))));
      (l = (lexer_advance_one(l, od)));
      oct_digits = oct_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 3)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  if (oct_digits == 0) {
    lexer_note_incomplete_oct(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok_o = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(oval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok_o));
  ((out)->token_start = (start));
  return;
 }
(ival = (ival * 10 + (c - 48)));
  /* wave277: `_` decimal digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (ival = (ival * 10 + (d - 48)));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && lexer_dot_continues_float(data, (l).pos) != 0) {   (l = (lexer_advance_one(l, 46)));
  double fval = ((double)(ival));
  double frac = 0.1;
  /* wave277: `_` float fraction digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (fval = (fval + frac * (d - 48)));
      (frac = (frac * 0.1));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  /* wave274: incomplete exp after fraction → L005 + TOKEN_EOF. */
  if (lexer_apply_optional_exponent(l, data, fval, (&(l)), (&(fval))) != 0) {
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 101 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 69) {
  /* wave274: require ≥1 exp digit after e/E (≡ lexer.x L005). */
  int32_t e_line = (l).line;
  int32_t e_col = (l).col;
  (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  int32_t exp_sign = 1;
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 45) {   (exp_sign = ((-1)));
  (l = (lexer_advance_one(l, 45)));
 } else {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 43) {   (l = (lexer_advance_one(l, 43)));
 }
 }
  int32_t exp = 0;
  int32_t exp_digits = 0;
  /* wave277: `_` float exponent digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (exp = (exp * 10 + (d - 48)));
      exp_digits = exp_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  if (exp_digits == 0) {
    lexer_note_incomplete_exp(e_line, e_col);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  (exp = (exp * exp_sign));
  double scale = 1;
  int32_t e = 0;
  if (exp > 0) {   while (e < exp) {
    (scale = (scale * 10));
    ++e;
  }
 } else {   while (e > exp) {
    (scale = (scale * 0.1));
    (e = (e - 1));
  }
 }
  double fval = ((double)(ival)) * scale;
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ival, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, 46)));
  double fval = 0.0;
  double frac = 0.1;
  /* wave277: `_` float fraction digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (fval = (fval + frac * (d - 48)));
      (frac = (frac * 0.1));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sep));
    ((out)->token_start = (start));
    return;
  }
  /* wave274: incomplete exp after fraction → L005 + TOKEN_EOF. */
  if (lexer_apply_optional_exponent(l, data, fval, (&(l)), (&(fval))) != 0) {
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof));
    ((out)->token_start = (start));
    return;
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    (void)(lexer_write_next_lex_into(out, l));
    (void)(lexer_write_tok_into(out, tok_eof_sfx));
    ((out)->token_start = (start));
    return;
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, c)));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  if (c == 40) {   ((tok).kind = (token_TokenKind_TOKEN_LPAREN));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 41) {   ((tok).kind = (token_TokenKind_TOKEN_RPAREN));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 123) {   ((tok).kind = (token_TokenKind_TOKEN_LBRACE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 125) {   ((tok).kind = (token_TokenKind_TOKEN_RBRACE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 91) {   ((tok).kind = (token_TokenKind_TOKEN_LBRACKET));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 93) {   ((tok).kind = (token_TokenKind_TOKEN_RBRACKET));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 44) {   ((tok).kind = (token_TokenKind_TOKEN_COMMA));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 58) {   ((tok).kind = (token_TokenKind_TOKEN_COLON));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 46) {
    if ((l).pos + 1 < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 46) {
      (l = (lexer_advance_one(l, 46)));
      (l = (lexer_advance_one(l, 46)));
      ((tok).kind = (token_TokenKind_TOKEN_ELLIPSIS));
    } else {
      ((tok).kind = (token_TokenKind_TOKEN_DOT));
    }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 59) {   ((tok).kind = (token_TokenKind_TOKEN_SEMICOLON));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 43) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PLUS_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_PLUS));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 45) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  ((tok).kind = (token_TokenKind_TOKEN_ARROW));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_MINUS_EQ));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_MINUS));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 42) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_STAR_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_STAR));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 47) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_SLASH_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_SLASH));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 37) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PERCENT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_PERCENT));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 94) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_CARET_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_CARET));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 126) {   ((tok).kind = (token_TokenKind_TOKEN_TILDE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 38) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 38) {   (l = (lexer_advance_one(l, 38)));
  ((tok).kind = (token_TokenKind_TOKEN_AMPAMP));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_AMP_EQ));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_AMP));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 124) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 124) {   (l = (lexer_advance_one(l, 124)));
  ((tok).kind = (token_TokenKind_TOKEN_PIPEPIPE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PIPE_EQ));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_PIPE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 60) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_LE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 60) {   (l = (lexer_advance_one(l, 60)));
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_LSHIFT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_LSHIFT));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_LT));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 62) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_GE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_RSHIFT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_RSHIFT));
 }
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_GT));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 33) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_NE));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_BANG));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 63) {   ((tok).kind = (token_TokenKind_TOKEN_QUESTION));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 64) {   ((tok).kind = (token_TokenKind_TOKEN_AT));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if (c == 61) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  ((tok).kind = (token_TokenKind_TOKEN_FATARROW));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_EQ));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  ((tok).kind = (token_TokenKind_TOKEN_ASSIGN));
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, tok));
  ((out)->token_start = (start));
  return;
 }
  /* wave272: unknown byte → L003 hard diag + sticky pending (≡ lexer.x). */
  /* wave1222: use current lexer position — line0/col0/start from if-blocks
   * above are block-scoped and may hold stale values from a prior parse file
   * when the X codegen hoists let-decls to function level. */
  { int32_t ill_line = (l).line; int32_t ill_col = (l).col; size_t ill_start = (l).pos;
  lexer_note_illegal_char(ill_line, ill_col);
  { struct token_Token unk = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = ill_line, .col = ill_col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, unk));
  ((out)->token_start = (ill_start)); } }
}
XLANG_LIB_WEAK void lexer_write_next_lex_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer l) {
  (((out)->next_lex).pos = ((l).pos));
  (((out)->next_lex).line = ((l).line));
  (((out)->next_lex).col = ((l).col));
  ((out)->token_start = (((size_t)(0))));
}
XLANG_LIB_WEAK void lexer_write_tok_into(struct lexer_LexerResult * restrict out, struct token_Token t) {
  (((out)->tok).kind = ((t).kind));
  (((out)->tok).line = ((t).line));
  (((out)->tok).col = ((t).col));
  (((out)->tok).int_val = ((t).int_val));
  (((out)->tok).float_val = ((t).float_val));
  (((out)->tok).ident = ((t).ident));
  (((out)->tok).ident_len = ((t).ident_len));
}
XLANG_LIB_WEAK void lexer_next_impl(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  struct lexer_Lexer l = lexer_skip_whitespace_and_comments(lex, data);
  if ((l).pos >= (data)->length) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, t));
  return;
 }
  if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 0) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(lexer_write_next_lex_into(out, l));
  (void)(lexer_write_tok_into(out, t));
  return;
 }
  (void)(lexer_next_body_into(out, l, data));
}
XLANG_LIB_WEAK void lexer_next_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data) {
  (void)(lexer_next_impl(out, lex, data));
}
XLANG_LIB_WEAK void lexer_next_buf_into(struct lexer_LexerResult * restrict out, struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct xlang_slice_uint8_t source = lexer_parser_slice_from_buf(data, len);
  (void)(lexer_next_into(out, lex, &(source)));
}
XLANG_LIB_WEAK struct lexer_LexerResult lexer_next_buf(struct lexer_Lexer lex, uint8_t * restrict data, int32_t len) {
  struct xlang_slice_uint8_t source = lexer_parser_slice_from_buf(data, len);
  return lexer_next_slice(lex, &(source));
}
XLANG_LIB_WEAK struct lexer_LexerResult lexer_next_body(struct lexer_Lexer l, struct xlang_slice_uint8_t * data) {
  uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
  if (lexer_is_alpha(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, c)));
  while ((l).pos < (data)->length && lexer_is_alnum_underscore(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  size_t len = (l).pos - start;
  struct token_Token tok = lexer_try_keyword(data, start, len, line0, col0);
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (lexer_is_digit(c)) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  int64_t ival = 0;
  (l = (lexer_advance_one(l, c)));
  if (c == 48 && (l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 120 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 88) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  /* wave273: require ≥1 hex digit after 0x/0X (≡ lexer.x L004). */
  uint64_t hval = ((uint64_t)(0));
  int32_t hex_digits = 0;
  /* wave277: `_` hex digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_hex_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t hd = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (hval = (hval * 16 + ((uint64_t)(lexer_hex_digit_value(hd)))));
      (l = (lexer_advance_one(l, hd)));
      hex_digits = hex_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 1)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (hex_digits == 0) {
    lexer_note_incomplete_hex(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start };
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(hval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  
 /* wave276: binary 0b/0B (≥1 bin digit → TOKEN_INT; else L006). */
 if (c == 48 && (l).pos < (data)->length && (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 98 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 66)) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  uint64_t bval = ((uint64_t)(0));
  int32_t bin_digits = 0;
  /* wave277: `_` bin digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_bin_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t bd = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (bval = (bval * 2 + ((uint64_t)(bd - 48))));
      (l = (lexer_advance_one(l, bd)));
      bin_digits = bin_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 2)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (bin_digits == 0) {
    lexer_note_incomplete_bin(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start };
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok_b = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(bval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_b, .token_start = start };
 }
 /* wave276: octal 0o/0O (≥1 oct digit → TOKEN_INT; else L007). */
 if (c == 48 && (l).pos < (data)->length && (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 111 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 79)) {   (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  uint64_t oval = ((uint64_t)(0));
  int32_t oct_digits = 0;
  /* wave277: `_` oct digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_oct_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t od = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (oval = (oval * 8 + ((uint64_t)(od - 48))));
      (l = (lexer_advance_one(l, od)));
      oct_digits = oct_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 3)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (oct_digits == 0) {
    lexer_note_incomplete_oct(line0, col0);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start };
  }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok_o = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ((int64_t)(oval)), .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_o, .token_start = start };
 }
(ival = (ival * 10 + (c - 48)));
  /* wave277: `_` decimal digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (ival = (ival * 10 + (d - 48)));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && lexer_dot_continues_float(data, (l).pos) != 0) {   (l = (lexer_advance_one(l, 46)));
  double fval = ((double)(ival));
  double frac = 0.1;
  /* wave277: `_` float fraction digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (fval = (fval + frac * (d - 48)));
      (frac = (frac * 0.1));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (lexer_apply_optional_exponent(l, data, fval, (&(l)), (&(fval))) != 0) { struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }; return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start }; }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 101 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 69) {
  /* wave274: require ≥1 exp digit after e/E (≡ lexer.x L005). */
  int32_t e_line = (l).line;
  int32_t e_col = (l).col;
  (l = (lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  int32_t exp_sign = 1;
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 45) {   (exp_sign = ((-1)));
  (l = (lexer_advance_one(l, 45)));
 } else {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 43) {   (l = (lexer_advance_one(l, 43)));
 }
 }
  int32_t exp = 0;
  int32_t exp_digits = 0;
  /* wave277: `_` float exponent digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (exp = (exp * 10 + (d - 48)));
      exp_digits = exp_digits + 1;
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (exp_digits == 0) {
    lexer_note_incomplete_exp(e_line, e_col);
    struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start };
  }
  (exp = (exp * exp_sign));
  double scale = 1;
  int32_t e = 0;
  if (exp > 0) {   while (e < exp) {
    (scale = (scale * 10));
    ++e;
  }
 } else {   while (e > exp) {
    (scale = (scale * 0.1));
    (e = (e - 1));
  }
 }
  double fval = ((double)(ival)) * scale;
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_INT, .line = line0, .col = col0, .int_val = ival, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, 46)));
  double fval = 0.0;
  double frac = 0.1;
  /* wave277: `_` float fraction digit separators (≡ lexer.x). */
  while ((l).pos < (data)->length) {
    if (lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
      uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
      (l = (lexer_advance_one(l, d)));
      (fval = (fval + frac * (d - 48)));
      (frac = (frac * 0.1));
    } else if (lexer_is_digit_sep(data, (l).pos, 0)) {
      (l = (lexer_advance_one(l, 95)));
    } else {
      break;
    }
  }
  /* wave278: invalid `_` digit separator → sticky L008. */
  if (((l).pos < (data)->length) && (((uint8_t *)(data)->data)[(l).pos] == 95)) {
    lexer_note_invalid_digit_sep((l).line, (l).col);
    struct token_Token tok_eof_sep = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sep, .token_start = start };
  }
  if (lexer_apply_optional_exponent(l, data, fval, (&(l)), (&(fval))) != 0) { struct token_Token tok_eof = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }; return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof, .token_start = start }; }
  /* wave279: alphabetic type suffix → sticky L009. */
  if (((l).pos < (data)->length) && lexer_is_alpha(((uint8_t *)(data)->data)[(l).pos])) {
    lexer_note_invalid_type_suffix((l).line, (l).col);
    struct token_Token tok_eof_sfx = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
    return (struct lexer_LexerResult){ .next_lex = l, .tok = tok_eof_sfx, .token_start = start };
  }
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_FLOAT, .line = line0, .col = col0, .int_val = 0, .float_val = fval, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  size_t start = (l).pos;
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  (l = (lexer_advance_one(l, c)));
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  if (c == 40) {   ((tok).kind = (token_TokenKind_TOKEN_LPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 41) {   ((tok).kind = (token_TokenKind_TOKEN_RPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 123) {   ((tok).kind = (token_TokenKind_TOKEN_LBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 125) {   ((tok).kind = (token_TokenKind_TOKEN_RBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 91) {   ((tok).kind = (token_TokenKind_TOKEN_LBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 93) {   ((tok).kind = (token_TokenKind_TOKEN_RBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 44) {   ((tok).kind = (token_TokenKind_TOKEN_COMMA));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 58) {   ((tok).kind = (token_TokenKind_TOKEN_COLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 46) {
    if ((l).pos + 1 < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 46) {
      (l = (lexer_advance_one(l, 46)));
      (l = (lexer_advance_one(l, 46)));
      ((tok).kind = (token_TokenKind_TOKEN_ELLIPSIS));
    } else {
      ((tok).kind = (token_TokenKind_TOKEN_DOT));
    }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 59) {   ((tok).kind = (token_TokenKind_TOKEN_SEMICOLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 43) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PLUS_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_PLUS));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 45) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  ((tok).kind = (token_TokenKind_TOKEN_ARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_MINUS_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_MINUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 42) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_STAR_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_STAR));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 47) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_SLASH_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_SLASH));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 37) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PERCENT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_PERCENT));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 94) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_CARET_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_CARET));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 126) {   ((tok).kind = (token_TokenKind_TOKEN_TILDE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 38) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 38) {   (l = (lexer_advance_one(l, 38)));
  ((tok).kind = (token_TokenKind_TOKEN_AMPAMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_AMP_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_AMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 124) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 124) {   (l = (lexer_advance_one(l, 124)));
  ((tok).kind = (token_TokenKind_TOKEN_PIPEPIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_PIPE_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_PIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 60) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_LE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 60) {   (l = (lexer_advance_one(l, 60)));
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_LSHIFT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_LSHIFT));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_LT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 62) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_GE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_RSHIFT_EQ));
 } else {   ((tok).kind = (token_TokenKind_TOKEN_RSHIFT));
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_GT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 33) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_NE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_BANG));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 63) {   ((tok).kind = (token_TokenKind_TOKEN_QUESTION));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 64) {   ((tok).kind = (token_TokenKind_TOKEN_AT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if (c == 61) {   if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (l = (lexer_advance_one(l, 62)));
  ((tok).kind = (token_TokenKind_TOKEN_FATARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (xlang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (l = (lexer_advance_one(l, 61)));
  ((tok).kind = (token_TokenKind_TOKEN_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  ((tok).kind = (token_TokenKind_TOKEN_ASSIGN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
 }
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok, .token_start = start };
}
