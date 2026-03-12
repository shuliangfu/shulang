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
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION };
struct token_Token { enum token_TokenKind kind; int32_t line; int32_t col; int32_t int_val; double float_val; uint8_t * ident; int32_t ident_len; };
struct shulang_slice_uint8_t { uint8_t *data; size_t length; };
struct lexer_Lexer { size_t pos; int32_t line; int32_t col; };
struct lexer_LexerResult { struct lexer_Lexer next_lex; struct token_Token tok; };
struct lexer_Lexer lexer_lexer_init();
struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c);
int lexer_is_alpha(uint8_t c);
int lexer_is_digit(uint8_t c);
int lexer_is_alnum_underscore(uint8_t c);
int lexer_match_keyword(struct shulang_slice_uint8_t * data, size_t start, int32_t len, struct shulang_slice_uint8_t * keyword);
struct token_Token lexer_try_keyword(struct shulang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0);
struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data);
struct lexer_LexerResult lexer_lexer_next(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data);
struct lexer_LexerResult lexer_lexer_next_body(struct lexer_Lexer l, struct shulang_slice_uint8_t * data);
struct lexer_Lexer lexer_lexer_init() {
  return (struct lexer_Lexer){ .pos = 0, .line = 1, .col = 1 };
}
struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c) {
  (void)(({ int32_t __tmp; if (c == 10) {   return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line + 1, .col = 1 };
 } else (__tmp = 0) ; __tmp; }));
  return (struct lexer_Lexer){ .pos = (lex).pos + 1, .line = (lex).line, .col = (lex).col + 1 };
}
int lexer_is_alpha(uint8_t c) {
  (void)(({ int __tmp; if (c >= 97 && c <= 122) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int __tmp; if (c >= 65 && c <= 90) {   return 1;
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
    (void)(({ int __tmp; if ((start + i < 0 || (size_t)(start + i) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[start + i]) != (i < 0 || (size_t)(i) >= (keyword)->length ? (shulang_panic_(1, 0), (keyword)->data[0]) : (keyword)->data[i])) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
    (void)((i = i + 1));
  }
  return 1;
}
struct token_Token lexer_try_keyword(struct shulang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0) {
  struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IDENT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = len };
  (void)(({ struct token_Token __tmp; if (len == 8 && lexer_match_keyword(data, start, 8, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 117, 110, 99, 116, 105, 111, 110 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FUNCTION, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 108, 101, 116 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LET, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 115, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONST, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 2 && lexer_match_keyword(data, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 102 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 108, 115, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ELSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 119, 104, 105, 108, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_WHILE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 108, 111, 111, 112 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_LOOP, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 111, 114 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FOR, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 98, 114, 101, 97, 107 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BREAK, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 8 && lexer_match_keyword(data, start, 8, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 99, 111, 110, 116, 105, 110, 117, 101 }, .length = 8 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_CONTINUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 114, 101, 116, 117, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_RETURN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 110, 105, 99 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PANIC, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 100, 101, 102, 101, 114 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_DEFER, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 109, 97, 116, 99, 104 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_MATCH, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 115, 116, 114, 117, 99, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_STRUCT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 112, 97, 99, 107, 101, 100 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_PACKED, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 110, 117, 109 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ENUM, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 103, 111, 116, 111 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_GOTO, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 97, 105, 116 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRAIT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 115, 101, 108, 102 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_SELF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 1 && (start < 0 || (size_t)(start) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[start]) == 95) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_UNDERSCORE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 109, 112, 111, 114, 116 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_IMPORT, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 101, 120, 116, 101, 114, 110 }, .length = 6 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EXTERN, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 98, 111, 111, 108 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_BOOL, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 2 && lexer_match_keyword(data, start, 2, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 56 }, .length = 2 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_USIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 115, 105, 122, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_ISIZE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 116, 114, 117, 101 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_TRUE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 97, 108, 115, 101 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_FALSE, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 51, 50 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F32, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 3 && lexer_match_keyword(data, start, 3, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 102, 54, 52 }, .length = 3 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_F64, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 4 && lexer_match_keyword(data, start, 4, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 118, 111, 105, 100 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_VOID, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 105, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_I32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 52 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X4, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 5 && lexer_match_keyword(data, start, 5, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 56 }, .length = 4 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X8, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  (void)(({ struct token_Token __tmp; if (len == 6 && lexer_match_keyword(data, start, 6, &((struct shulang_slice_uint8_t){ .data = (uint8_t[]){ 117, 51, 120, 49, 54 }, .length = 5 }))) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_U32X16, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return t;
 } else (__tmp = (struct token_Token){0}) ; __tmp; }));
  return t;
}
struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data) {
  struct lexer_Lexer l = lex;
  while ((l).pos < (data)->length) {
    uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)(({ int32_t __tmp; if (c == 32 || c == 9 || c == 10 || c == 13) {   (void)((l = lexer_advance_one(l, c)));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp; if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {   while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp; if (c == 47 && (l).pos + 1 < (data)->length && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 42) {   (void)((l = lexer_advance_one(l, 47)));
  (void)((l = lexer_advance_one(l, 42)));
  while ((l).pos + 1 < (data)->length) {
    (void)(({ int32_t __tmp; if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 42 && ((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]) == 47) {   (void)((l = lexer_advance_one(l, 42)));
  (void)((l = lexer_advance_one(l, 47)));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp; if (c == 35) {   while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {
    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  }
  continue;
 } else (__tmp = 0) ; __tmp; }));
    return l;
  }
  return l;
}
struct lexer_LexerResult lexer_lexer_next(struct lexer_Lexer lex, struct shulang_slice_uint8_t * data) {
  struct lexer_Lexer l = lexer_skip_whitespace_and_comments(lex, data);
  (void)(({ int32_t __tmp; if ((l).pos >= (data)->length) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 0) {   struct token_Token t = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = (l).line, .col = (l).col, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  return (struct lexer_LexerResult){ .next_lex = l, .tok = t };
 } else (__tmp = 0) ; __tmp; }));
  return lexer_lexer_next_body(l, data);
}
struct lexer_LexerResult lexer_lexer_next_body(struct lexer_Lexer l, struct shulang_slice_uint8_t * data) {
  uint8_t c = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
  int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  struct token_Token tok = (struct token_Token){ .kind = token_TokenKind_TOKEN_EOF, .line = line0, .col = col0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 };
  (void)(({ int32_t __tmp; if (lexer_is_alpha(c)) {   size_t start = (l).pos;
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
  (void)(({ int32_t __tmp; if (lexer_is_digit(c)) {   int32_t line0 = (l).line;
  int32_t col0 = (l).col;
  int32_t ival = 0;
  (void)((l = lexer_advance_one(l, c)));
  (void)((ival = ival * 10 + c - 48));
  while ((l).pos < (data)->length && lexer_is_digit(((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))) {
    uint8_t d = ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]);
    (void)((l = lexer_advance_one(l, d)));
    (void)((ival = ival * 10 + d - 48));
  }
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   (void)((l = lexer_advance_one(l, 46)));
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
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 101 || ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 69) {   (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));
  int32_t exp_sign = 1;
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 45) {   (void)((exp_sign = (-1)));
  (void)((l = lexer_advance_one(l, 45)));
 } else {   __tmp = ({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 43) {   (void)((l = lexer_advance_one(l, 43)));
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
  (void)(({ int32_t __tmp; if (exp > 0) {   while (e < exp) {
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
  (void)(({ int32_t __tmp; if (c == 46 && (l).pos + 1 < (data)->length && lexer_is_digit(((l).pos + 1 < 0 || (size_t)((l).pos + 1) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos + 1]))) {   int32_t line0 = (l).line;
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
  (void)(({ int32_t __tmp; if (c == 40) {   (void)(((tok).kind = token_TokenKind_TOKEN_LPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 41) {   (void)(((tok).kind = token_TokenKind_TOKEN_RPAREN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 123) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 125) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 91) {   (void)(((tok).kind = token_TokenKind_TOKEN_LBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 93) {   (void)(((tok).kind = token_TokenKind_TOKEN_RBRACKET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 44) {   (void)(((tok).kind = token_TokenKind_TOKEN_COMMA));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 58) {   (void)(((tok).kind = token_TokenKind_TOKEN_COLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 46) {   (void)(((tok).kind = token_TokenKind_TOKEN_DOT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 59) {   (void)(((tok).kind = token_TokenKind_TOKEN_SEMICOLON));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 43) {   (void)(((tok).kind = token_TokenKind_TOKEN_PLUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 45) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_ARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_MINUS));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 42) {   (void)(((tok).kind = token_TokenKind_TOKEN_STAR));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 47) {   (void)(((tok).kind = token_TokenKind_TOKEN_SLASH));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 37) {   (void)(((tok).kind = token_TokenKind_TOKEN_PERCENT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 94) {   (void)(((tok).kind = token_TokenKind_TOKEN_CARET));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 126) {   (void)(((tok).kind = token_TokenKind_TOKEN_TILDE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 38) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 38) {   (void)((l = lexer_advance_one(l, 38)));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMPAMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_AMP));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 124) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 124) {   (void)((l = lexer_advance_one(l, 124)));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPEPIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_PIPE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 60) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 60) {   (void)((l = lexer_advance_one(l, 60)));
  (void)(((tok).kind = token_TokenKind_TOKEN_LSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_LT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 62) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_GE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_RSHIFT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_GT));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 33) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_NE));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_BANG));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 63) {   (void)(((tok).kind = token_TokenKind_TOKEN_QUESTION));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if (c == 61) {   (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 62) {   (void)((l = lexer_advance_one(l, 62)));
  (void)(((tok).kind = token_TokenKind_TOKEN_FATARROW));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp; if ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) == 61) {   (void)((l = lexer_advance_one(l, 61)));
  (void)(((tok).kind = token_TokenKind_TOKEN_EQ));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  (void)(((tok).kind = token_TokenKind_TOKEN_ASSIGN));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
 } else (__tmp = 0) ; __tmp; }));
  return (struct lexer_LexerResult){ .next_lex = l, .tok = tok };
}
