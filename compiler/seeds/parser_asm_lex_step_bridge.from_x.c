/* seeds/parser_asm_lex_step_bridge.from_x.c — 7.2.1 B-minus lexer-step bridge
 *
 * Minimal C bridge (~80 lines, one-time, never grows) that lets .x carry all
 * suite audit-probe logic. Every audit function's struct dependency funnels
 * through lexer_next_into (246 call sites in the 28k suite slice); these
 * externs encapsulate that single primitive + the few scalar field reads,
 * so .x never sees struct lexer_result / lexer / token.
 *
 * Authority: the .x callers (src/asm/pthin_*.x) own the audit logic; this
 * bridge owns only the lexer step and field peeks. G.7: single bridge face,
 * no second lexer implementation.
 * PLATFORM: SHARED freestanding.
 */
#include <stddef.h>
#include <stdint.h>

/* Struct layout mirrors seeds/parser_asm_thin_c.from_x.c / parser_asm_parse_bootstrap_obj.inc.
 * Layout-mirror discipline (same as the whole parser_asm suite): these mirrors
 * must stay field-for-field identical to the lexer family authority structs in
 * seeds/lexer_gen.linux.x86_64.c (lexer_Lexer / token_Token / lexer_LexerResult);
 * any authority layout change must update every mirror in the same commit.
 * lexer_next_into itself is .x authority (lexer_x.o) and resolves at final link. */
struct parser_asm_slice_u8 {
  uint8_t *data;
  size_t length;
};

struct parser_asm_lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};

struct parser_asm_token {
  int32_t kind;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t *ident;
  int32_t ident_len;
};

struct parser_asm_lexer_result {
  struct parser_asm_lexer next_lex;
  struct parser_asm_token tok;
  size_t token_start;
};

/* Provided by the thin glue TU (lexer family). */
extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                           struct parser_asm_slice_u8 *source);

/**
 * Advance the lexer one step and return the next token's kind.
 * The lexer state is updated in place through the opaque pointer.
 * @param lex_inout *u8 — opaque struct parser_asm_lexer* (updated in place)
 * @param source *u8 — opaque struct parser_asm_slice_u8*
 * @return i32 — next token kind
 * PLATFORM: SHARED.
 */
int32_t parser_asm_lex_step_kind_c(void *lex_inout, void *source) {
  struct parser_asm_lexer_result r;
  struct parser_asm_lexer *lex = (struct parser_asm_lexer *)lex_inout;
  if (!lex || !source)
    return 0;
  lexer_next_into(&r, *lex, (struct parser_asm_slice_u8 *)source);
  *lex = r.next_lex;
  return r.tok.kind;
}

/**
 * Read the lexer's current pos (cursor offset into source).
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @return usize — pos
 * PLATFORM: SHARED.
 */
size_t parser_asm_lex_pos_c(void *lex) {
  if (!lex)
    return 0;
  return ((struct parser_asm_lexer *)lex)->pos;
}

/**
 * Write the lexer's pos (rewind / skip). Together with set_line_c/set_col_c
 * forms the full restore trio: the C audit family takes the lexer BY VALUE
 * (caller state never advances), so a .x port over an opaque pointer must
 * snapshot pos+line+col on entry and restore all three before every return.
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @param pos usize — new pos
 * PLATFORM: SHARED.
 */
void parser_asm_lex_set_pos_c(void *lex, size_t pos) {
  if (!lex)
    return;
  ((struct parser_asm_lexer *)lex)->pos = pos;
}

/**
 * Write the lexer's line (second third of the by-value state restore trio;
 * see parser_asm_lex_set_pos_c for why all three setters exist).
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @param line i32 — new line
 * PLATFORM: SHARED.
 */
void parser_asm_lex_set_line_c(void *lex, int32_t line) {
  if (!lex)
    return;
  ((struct parser_asm_lexer *)lex)->line = line;
}

/**
 * Write the lexer's col (last third of the by-value state restore trio).
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @param col i32 — new col
 * PLATFORM: SHARED.
 */
void parser_asm_lex_set_col_c(void *lex, int32_t col) {
  if (!lex)
    return;
  ((struct parser_asm_lexer *)lex)->col = col;
}

/**
 * Read the lexer's current line.
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @return i32 — line
 * PLATFORM: SHARED.
 */
int32_t parser_asm_lex_line_c(void *lex) {
  if (!lex)
    return 0;
  return ((struct parser_asm_lexer *)lex)->line;
}

/**
 * Read the lexer's current col.
 * @param lex *u8 — opaque struct parser_asm_lexer*
 * @return i32 — col
 * PLATFORM: SHARED.
 */
int32_t parser_asm_lex_col_c(void *lex) {
  if (!lex)
    return 0;
  return ((struct parser_asm_lexer *)lex)->col;
}

/**
 * Read the source slice's data pointer (for byte-compare in .x).
 * @param source *u8 — opaque struct parser_asm_slice_u8*
 * @return *u8 — data bytes (may be null)
 * PLATFORM: SHARED.
 */
uint8_t *parser_asm_lex_source_data_c(void *source) {
  if (!source)
    return 0;
  return ((struct parser_asm_slice_u8 *)source)->data;
}

/**
 * Read the source slice's length.
 * @param source *u8 — opaque struct parser_asm_slice_u8*
 * @return usize — length
 * PLATFORM: SHARED.
 */
size_t parser_asm_lex_source_length_c(void *source) {
  if (!source)
    return 0;
  return ((struct parser_asm_slice_u8 *)source)->length;
}

/**
 * Peeking variant: advance a COPY of the lexer, return kind, don't mutate
 * the caller's lexer. Used by .x lookahead probes (kind chain checks).
 * @param lex *u8 — opaque struct parser_asm_lexer* (read-only)
 * @param source *u8 — opaque struct parser_asm_slice_u8*
 * @return i32 — next token kind
 * PLATFORM: SHARED.
 */
int32_t parser_asm_lex_peek_kind_c(void *lex, void *source) {
  struct parser_asm_lexer_result r;
  if (!lex || !source)
    return 0;
  lexer_next_into(&r, *(struct parser_asm_lexer *)lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind;
}
