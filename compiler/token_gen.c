/* generated from token */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION };
struct token_Token { enum token_TokenKind kind; int32_t line; int32_t col; int32_t int_val; double float_val; uint8_t * ident; int32_t ident_len; };
static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static void shulang_panic_(int has_msg, int msg_val) {
  if (has_msg) (void)fprintf(stderr, "%d\n", msg_val);
  abort();
}
int token_token_is_eof(struct token_Token t);
int token_token_is_eof(struct token_Token t) {
  return (t).kind == token_TokenKind_TOKEN_EOF;
}
