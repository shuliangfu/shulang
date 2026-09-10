// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// pthin_stretch_audit.x — 7.2.1 B-minus pilot (RFC §5b/§5c).
//
// Authority home for the suite audit-probe family ported from
// seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc. The B-minus
// route keeps every struct behind an opaque *u8: the lexer is driven only
// through the one-time C bridge (seeds/parser_asm_lex_step_bridge.from_x.c,
// externs below), never by field access in .x. This file starts with the
// canonical pilot `if_header_audit` and will accumulate further audit ports
// wave by wave; each port flips the matching C twin in the suite slice under
// #ifndef XLANG_PTHIN_STRETCH_AUDIT_FROM_X when productionized.
//
// G.7: one authority per symbol — in the hybrid lane the C twin is compiled
// out and this file is the sole definition; in the cold/default lane the C
// twin provides the same name with the same pointer ABI and semantics.
// Seed twin must be updated in the same commit as this file (same semantics).
// PLATFORM: SHARED freestanding.

// --- lexer-step bridge externs (seeds/parser_asm_lex_step_bridge.from_x.c) ---

/** Advance the opaque lexer one token step; returns the token kind. */
export extern "C" function parser_asm_lex_step_kind_c(lex_inout: *u8, source: *u8): i32;
/** Read the opaque lexer's pos (cursor offset into source). */
export extern "C" function parser_asm_lex_pos_c(lex: *u8): usize;
/** Write the opaque lexer's pos (restore trio member 1/3). */
export extern "C" function parser_asm_lex_set_pos_c(lex: *u8, pos: usize): void;
/** Read the opaque lexer's line. */
export extern "C" function parser_asm_lex_line_c(lex: *u8): i32;
/** Write the opaque lexer's line (restore trio member 2/3). */
export extern "C" function parser_asm_lex_set_line_c(lex: *u8, line: i32): void;
/** Read the opaque lexer's col. */
export extern "C" function parser_asm_lex_col_c(lex: *u8): i32;
/** Write the opaque lexer's col (restore trio member 3/3). */
export extern "C" function parser_asm_lex_set_col_c(lex: *u8, col: i32): void;

/** Peek the NEXT token's kind without advancing (pure lookahead). */
export extern "C" function parser_asm_lex_peek_kind_c(lex: *u8, source: *u8): i32;
/** Peek the next token's ident_len without advancing (pure, no mutation). */
export extern "C" function parser_asm_lex_peek_ident_len_c(lex: *u8, source: *u8): i32;
/** Peek the next token's start offset into source bytes without advancing. */
export extern "C" function parser_asm_lex_peek_token_start_c(lex: *u8, source: *u8): usize;
/** Read the source slice's data pointer (byte-compare of token text in .x). */
export extern "C" function parser_asm_lex_source_data_c(source: *u8): *u8;
/** Read the source slice's length. */
export extern "C" function parser_asm_lex_source_length_c(source: *u8): usize;
/** Peek the next token's ident pointer (points into source bytes; IDENT only). */
export extern "C" function parser_asm_lex_peek_ident_ptr_c(lex: *u8, source: *u8): *u8;
/** Wrap raw (data,len) into an opaque slice (bridge ring-16 scratch). */
export extern "C" function parser_asm_lex_wrap_buf_c(data: *u8, len: i32): *u8;

/** Suite skip helpers via in-place adapters (C stays authority). */
export extern "C" function parser_asm_lex_is_type_start_kind_c(kind: i32): i32;
export extern "C" function parser_asm_lex_skip_balanced_brackets_inplace_c(lex_inout: *u8, source: *u8): void;
/** In-place skip of a balanced (..) group (caller already consumed '('). */
export extern "C" function parser_asm_lex_skip_balanced_parens_inplace_c(lex_inout: *u8, source: *u8): void;
export extern "C" function parser_asm_lex_skip_type_suffix_inplace_c(lex_inout: *u8, source: *u8): void;
export extern "C" function parser_asm_lex_skip_one_param_type_inplace_c(lex_inout: *u8, source: *u8): void;
export extern "C" function parser_asm_is_compound_assign_token_c(kind: i32): i32;
export extern "C" function parser_asm_stretch_bind_name_validate_c(name: *u8, name_len: i32): i32;

// Lexer canonical TokenKind values (enum token_TokenKind indices; authority
// include/token.h == seeds/lexer_gen.linux.x86_64.c, verified identical 133
// entries — see pthin_stretch.x for the rest of the constant set).
const TOKEN_EOF: i32 = 0;
const TOKEN_FUNCTION: i32 = 1;
const TOKEN_LET: i32 = 2;
const TOKEN_CONST: i32 = 3;
const TOKEN_IF: i32 = 4;
const TOKEN_ELSE: i32 = 5;
const TOKEN_WHILE: i32 = 6;
const TOKEN_FOR: i32 = 8;
const TOKEN_BREAK: i32 = 9;
const TOKEN_CONTINUE: i32 = 10;
const TOKEN_RETURN: i32 = 11;
const TOKEN_MATCH: i32 = 18;
const TOKEN_ENUM: i32 = 47;
const TOKEN_IMPORT: i32 = 53;
const TOKEN_IDENT: i32 = 59;
const TOKEN_LPAREN: i32 = 82;
const TOKEN_LBRACE: i32 = 84;
const TOKEN_COLON: i32 = 91;
const TOKEN_SEMICOLON: i32 = 95;
const TOKEN_RPAREN: i32 = 83;
const TOKEN_LBRACKET: i32 = 86;
const TOKEN_RBRACKET: i32 = 87;
const TOKEN_COMMA: i32 = 90;
const TOKEN_STAR: i32 = 98;
const TOKEN_I32: i32 = 60;
const TOKEN_BOOL: i32 = 61;
const TOKEN_U8: i32 = 62;
const TOKEN_U32: i32 = 63;
const TOKEN_U64: i32 = 64;
const TOKEN_I64: i32 = 65;
const TOKEN_USIZE: i32 = 66;
const TOKEN_VOID: i32 = 79;
const TOKEN_ASYNC: i32 = 55;
const TOKEN_PANIC: i32 = 12;
const TOKEN_STRUCT: i32 = 19;
const TOKEN_ASSIGN: i32 = 117;
const TOKEN_ALIGN: i32 = 46;
const TOKEN_AS: i32 = 128;
const TOKEN_INT: i32 = 80;
const TOKEN_QUESTION: i32 = 127;
const TOKEN_RBRACE: i32 = 85;
const TOKEN_TRAIT: i32 = 49;
const TOKEN_AT: i32 = 129;
const TOKEN_FALSE: i32 = 76;
const TOKEN_FLOAT: i32 = 81;
const TOKEN_TRUE: i32 = 75;
const TOKEN_AMP: i32 = 101;
const TOKEN_AMPAMP: i32 = 124;
const TOKEN_CARET: i32 = 103;
const TOKEN_EQ: i32 = 118;
const TOKEN_GE: i32 = 123;
const TOKEN_GT: i32 = 121;
const TOKEN_LE: i32 = 122;
const TOKEN_LSHIFT: i32 = 104;
const TOKEN_LT: i32 = 120;
const TOKEN_NE: i32 = 119;
const TOKEN_PIPE: i32 = 102;
const TOKEN_PIPEPIPE: i32 = 125;
const TOKEN_RSHIFT: i32 = 105;
const TOKEN_AWAIT: i32 = 56;
const TOKEN_BANG: i32 = 126;
const TOKEN_MINUS: i32 = 97;
const TOKEN_PERCENT: i32 = 100;
const TOKEN_PLUS: i32 = 96;
const TOKEN_RUN: i32 = 57;
const TOKEN_SLASH: i32 = 99;
const TOKEN_SPAWN: i32 = 58;
const TOKEN_IMPL: i32 = 50;
const TOKEN_DOT: i32 = 92;
const TOKEN_PACKED: i32 = 21;
const TOKEN_SOA: i32 = 22;
const TOKEN_EXTERN: i32 = 54;

/**
 * Audit an `if` statement header: exactly `if (` opens a valid header.
 *
 * B-minus port of the suite-slice C twin `parser_asm_stretch_if_header_audit_c`.
 * The C twin takes the lexer BY VALUE (caller's lexer never advances); this
 * port takes the lexer as an opaque pointer and reproduces that contract by
 * snapshotting pos/line/col on entry and restoring all three before every
 * return (bridge restore trio).
 *
 * Semantics (identical to the C twin): step one token — not `if` → 0; step a
 * second token — return 1 iff it is `(`, else 0. Null lex or source → 0.
 *
 * @param lex *u8 — opaque struct parser_asm_lexer* (read-only net effect)
 * @param source *u8 — opaque struct parser_asm_slice_u8* (may be null)
 * @return i32 — 1 if the header is exactly `if (`, else 0
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_if_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_IF) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_LPAREN) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/* ── tier26/27 audit family (B-minus wave 2) ─────────────────────────────
 * All ports follow the pilot contract: pointer ABI, by-value net semantics
 * via the snapshot/restore trio, peek-family inspection of the token about
 * to be consumed (pure — several peeks see the same token), explicit step
 * for advancement. Guard loops replicate the C `if (guard++ > N)` bail
 * exactly: while (guard <= N) { guard++; body } ≡ 65/513-iteration caps. */

/**
 * Audit a loop header: keyword (while or for per expect_while) then `(`.
 * Port of the suite twin `parser_asm_stretch_loop_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @param expect_while i32 — nonzero expects `while`, zero expects `for`
 * @return i32 — 1 iff `<kw> (` opens the header
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_loop_header_audit_c(lex: *u8, source: *u8, expect_while: i32): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let want: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    if (expect_while != 0) {
      want = TOKEN_WHILE;
    } else {
      want = TOKEN_FOR;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != want) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_LPAREN) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit break/continue statements: keyword then `;`.
 * Port of the suite twin `parser_asm_stretch_break_continue_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @param want_break i32 — nonzero audits `break ;`, zero `continue ;`
 * @return i32 — 1 iff `<kw> ;`
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_break_continue_audit_c(lex: *u8, source: *u8, want_break: i32): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let want: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    if (want_break != 0) {
      want = TOKEN_BREAK;
    } else {
      want = TOKEN_CONTINUE;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != want) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_SEMICOLON) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit an else branch: `else {` or `else if (` openers.
 * Port of the suite twin `parser_asm_stretch_else_stmt_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff the token after `else` is `{` or `if`
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_else_stmt_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_ELSE) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_IF || kind == TOKEN_LBRACE) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit an else-if chain opener: `else if (` exactly.
 * Port of the suite twin `parser_asm_stretch_else_if_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff `else if (`
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_else_if_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_ELSE) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_IF) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_step_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_LPAREN) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit a let/const declaration head: `let|const name :` shape (no arena).
 * Port of the suite twin `parser_asm_stretch_let_const_decl_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff `<let|const> <ident with len> <:>`
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_let_const_decl_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_LET && kind != TOKEN_CONST) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_COLON) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit an enum header: `enum Name {` shape.
 * Port of the suite twin `parser_asm_stretch_enum_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff `enum <ident with len> {`
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_enum_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_ENUM) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_LBRACE) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/**
 * Audit a match statement: `match ... {` — scans ahead (guard 512) until
 * the opening brace; `;`/EOF first means not a match statement.
 * Port of the suite twin `parser_asm_stretch_match_kw_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff a `{` is reached before `;`/EOF/512 tokens
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_match_kw_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let guard: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_MATCH) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    while (guard <= 512) {
      guard = guard + 1;
      kind = parser_asm_lex_step_kind_c(lex, source);
      if (kind == TOKEN_LBRACE) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      if (kind == TOKEN_EOF || kind == TOKEN_SEMICOLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
      }
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return 0;
  }
  return 0;
}

/**
 * Audit a return statement: `return ... ;` — scans ahead (guard 256) for
 * the terminating `;`; EOF first means unterminated.
 * Port of the suite twin `parser_asm_stretch_return_stmt_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff a `;` is reached before EOF/256 tokens
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_return_stmt_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let guard: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_RETURN) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    while (guard <= 256) {
      guard = guard + 1;
      kind = parser_asm_lex_step_kind_c(lex, source);
      if (kind == TOKEN_SEMICOLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      if (kind == TOKEN_EOF) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
      }
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return 0;
  }
  return 0;
}

/**
 * Audit an import statement: `import path ;` / `import path as bind ;`
 * coarse check — scans ahead (guard 64) for the `;`. A two-byte IDENT whose
 * bytes are exactly "as" does not advance the scan (legacy branch kept for
 * fidelity; the lexer lexes `as` as TOKEN_AS so this cannot fire today).
 * Port of the suite twin `parser_asm_stretch_import_stmt_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff `;` reached before EOF/65 scanned tokens
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_import_stmt_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let ts: usize = 0;
  let slen: usize = 0;
  let guard: i32 = 0;
  let data: *u8 = 0 as *u8;
  let b0: u8 = 0;
  let b1: u8 = 0;
  let is_as: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_IMPORT) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    while (guard <= 64) {
      guard = guard + 1;
      kind = parser_asm_lex_peek_kind_c(lex, source);
      if (kind == TOKEN_SEMICOLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      if (kind == TOKEN_EOF) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
      }
      is_as = 0;
      if (kind == TOKEN_IDENT) {
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        if (idlen == 2) {
          data = parser_asm_lex_source_data_c(source);
          slen = parser_asm_lex_source_length_c(source);
          ts = parser_asm_lex_peek_token_start_c(lex, source);
          if (data != 0 as *u8 && ts + 1 < slen) {
            b0 = data[ts];
            b1 = data[ts + 1];
            if (b0 == 97 && b1 == 115) {
              is_as = 1;
            }
          }
        }
      }
      if (is_as == 0) {
        parser_asm_lex_step_kind_c(lex, source);
      }
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return 0;
  }
  return 0;
}

/* ── function-signature audit cluster (B-minus wave 3) ────────────────────
 * Two inout-ABI audits (fn_param_list / skip_return_type keep the caller's
 * lexer advanced on success — inout contract, no restore) and two by-value
 * audits (fn_sig / function_header — snapshot/restore trio). Composed calls
 * thread the opaque pointer through; no local lexer struct is ever needed. */

/**
 * Scan a parameter list `(name: type, ...)` starting just after '('.
 * Inout contract (≡ suite twin): on success the caller's lexer is left just
 * after the closing ')'; on any failure the caller's lexer is left UNCHANGED
 * (the C twin only writes back on success).
 * Port of the suite twin `parser_asm_stretch_fn_param_list_audit_c`.
 * @param lex_inout *u8 — opaque lexer, advanced past ')' on success
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff the list is well-formed (or empty `()`)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_fn_param_list_audit_c(lex_inout: *u8, source: *u8): i32 {
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let guard: i32 = 0;
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  if (lex_inout == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex_inout);
    line0 = parser_asm_lex_line_c(lex_inout);
    col0 = parser_asm_lex_col_c(lex_inout);
    kind = parser_asm_lex_peek_kind_c(lex_inout, source);
    if (kind == TOKEN_RPAREN) {
      parser_asm_lex_step_kind_c(lex_inout, source);
      return 1;
    }
    while (guard <= 128) {
      guard = guard + 1;
      idlen = parser_asm_lex_peek_ident_len_c(lex_inout, source);
      if (kind != TOKEN_IDENT || idlen <= 0 || idlen > 63) {
        parser_asm_lex_set_pos_c(lex_inout, pos0);
        parser_asm_lex_set_line_c(lex_inout, line0);
        parser_asm_lex_set_col_c(lex_inout, col0);
        return 0;
      }
      parser_asm_lex_step_kind_c(lex_inout, source);
      kind = parser_asm_lex_peek_kind_c(lex_inout, source);
      if (kind != TOKEN_COLON) {
        parser_asm_lex_set_pos_c(lex_inout, pos0);
        parser_asm_lex_set_line_c(lex_inout, line0);
        parser_asm_lex_set_col_c(lex_inout, col0);
        return 0;
      }
      parser_asm_lex_step_kind_c(lex_inout, source);
      parser_asm_lex_skip_one_param_type_inplace_c(lex_inout, source);
      kind = parser_asm_lex_peek_kind_c(lex_inout, source);
      if (kind == TOKEN_RPAREN) {
        parser_asm_lex_step_kind_c(lex_inout, source);
        return 1;
      }
      if (kind != TOKEN_COMMA) {
        parser_asm_lex_set_pos_c(lex_inout, pos0);
        parser_asm_lex_set_line_c(lex_inout, line0);
        parser_asm_lex_set_col_c(lex_inout, col0);
        return 0;
      }
      parser_asm_lex_step_kind_c(lex_inout, source);
      kind = parser_asm_lex_peek_kind_c(lex_inout, source);
    }
    parser_asm_lex_set_pos_c(lex_inout, pos0);
    parser_asm_lex_set_line_c(lex_inout, line0);
    parser_asm_lex_set_col_c(lex_inout, col0);
    return 0;
  }
  return 0;
}

/**
 * Skip a return-type token sequence (after ':') up to '{'. Inout contract
 * (≡ suite twin): on success the caller's lexer is advanced to the '{' and
 * KEPT there; on any failure the caller's lexer is left UNCHANGED (the C
 * twin only writes back on success). '*' skips itself, a type-start skips
 * its suffix, '[' skips a balanced group, any other token fails.
 * Port of the suite twin `parser_asm_stretch_skip_return_type_audit_c`.
 * @param lex_inout *u8 — opaque lexer (advanced on success only)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff a '{' is reached within the guard budget
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_return_type_audit_c(lex_inout: *u8, source: *u8): i32 {
  let kind: i32 = 0;
  let guard: i32 = 0;
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  if (lex_inout == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex_inout);
    line0 = parser_asm_lex_line_c(lex_inout);
    col0 = parser_asm_lex_col_c(lex_inout);
    kind = parser_asm_lex_peek_kind_c(lex_inout, source);
    while (kind != TOKEN_LBRACE && kind != TOKEN_EOF) {
      if (guard > 96) {
        parser_asm_lex_set_pos_c(lex_inout, pos0);
        parser_asm_lex_set_line_c(lex_inout, line0);
        parser_asm_lex_set_col_c(lex_inout, col0);
        return 0;
      }
      guard = guard + 1;
      if (kind == TOKEN_STAR) {
        parser_asm_lex_step_kind_c(lex_inout, source);
        kind = parser_asm_lex_peek_kind_c(lex_inout, source);
        continue;
      }
      if (parser_asm_lex_is_type_start_kind_c(kind) != 0) {
        parser_asm_lex_step_kind_c(lex_inout, source);
        parser_asm_lex_skip_type_suffix_inplace_c(lex_inout, source);
        kind = parser_asm_lex_peek_kind_c(lex_inout, source);
        continue;
      }
      if (kind == TOKEN_LBRACKET) {
        parser_asm_lex_step_kind_c(lex_inout, source);
        parser_asm_lex_skip_balanced_brackets_inplace_c(lex_inout, source);
        kind = parser_asm_lex_peek_kind_c(lex_inout, source);
        continue;
      }
      parser_asm_lex_set_pos_c(lex_inout, pos0);
      parser_asm_lex_set_line_c(lex_inout, line0);
      parser_asm_lex_set_col_c(lex_inout, col0);
      return 0;
    }
    if (kind != TOKEN_LBRACE) {
      parser_asm_lex_set_pos_c(lex_inout, pos0);
      parser_asm_lex_set_line_c(lex_inout, line0);
      parser_asm_lex_set_col_c(lex_inout, col0);
      return 0;
    }
    return 1;
  }
  return 0;
}

#[no_mangle]
export function parser_asm_stretch_fn_sig_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let ok: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_step_kind_c(lex, source);
    if (kind != TOKEN_FUNCTION) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_LPAREN) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    if (parser_asm_stretch_fn_param_list_audit_c(lex, source) == 0) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_COLON) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    ok = parser_asm_stretch_skip_return_type_audit_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return ok;
  }
  return 0;
}

/**
 * Audit a function header with optional async prefix: `[async] function name (`.
 * By-value net semantics via the restore trio.
 * Port of the suite twin `parser_asm_stretch_function_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — 1 iff `[async] function <ident> (` opens the header
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_function_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_ASYNC) {
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    if (kind != TOKEN_FUNCTION) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    if (kind == TOKEN_LPAREN) {
      return 1;
    }
    return 0;
  }
  return 0;
}

/* ── generated leaves (gen_stretch_audit_x.py v1) ── */

/**
 * Generated audit port parser_asm_stretch_struct_header_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_struct_header_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_struct_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_STRUCT) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_LBRACE) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_panic_kw_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_panic_kw_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_panic_kw_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_PANIC) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_LPAREN || kind == TOKEN_SEMICOLON) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_assign_op_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_assign_op_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_assign_op_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_ASSIGN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (parser_asm_is_compound_assign_token_c(kind) != 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_if_stmt_branch_audit_c forwards to parser_asm_stretch_if_header_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_if_stmt_branch_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_if_header_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_async_fn_prefix_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_async_fn_prefix_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_async_fn_prefix_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_ASYNC) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_FUNCTION) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_trait_header_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_trait_header_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_trait_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_TRAIT) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_LBRACE) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_cond_int_as_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_cond_int_as_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cond_int_as_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_INT && kind != TOKEN_I32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_AS) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_label_stmt_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_label_stmt_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_label_stmt_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_COLON) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_assign_stmt_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_assign_stmt_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_assign_stmt_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_ASSIGN) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_ternary_op_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_ternary_op_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_op_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_QUESTION) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_paren_expr_head_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_paren_expr_head_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_paren_expr_head_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_LPAREN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind != TOKEN_RPAREN) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_balanced_parens_depth_probe_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_balanced_parens_depth_probe_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_parens_depth_probe_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind != TOKEN_RPAREN) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_struct_align_paren_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_struct_align_paren_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_struct_align_paren_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_ALIGN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind == TOKEN_LPAREN) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_balanced_braces_depth_probe_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_balanced_braces_depth_probe_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_braces_depth_probe_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind != TOKEN_RBRACE) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_balanced_brackets_depth_probe_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_balanced_brackets_depth_probe_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_brackets_depth_probe_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (kind != TOKEN_RBRACKET) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_let_in_block_audit_c forwards to parser_asm_stretch_let_const_decl_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_let_in_block_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_let_const_decl_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_if_expr_branch_audit_c forwards to parser_asm_stretch_if_header_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_if_expr_branch_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_if_header_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_primary_head_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_primary_head_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_primary_head_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind == TOKEN_INT || kind == TOKEN_FLOAT) {
      score = score + 1;
    } else if (kind == TOKEN_TRUE || kind == TOKEN_FALSE) {
      score = score + 1;
    } else if (kind == TOKEN_IDENT) {
      idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);
      parser_asm_stretch_bind_name_validate_c(idptr, idlen);
      score = score + 2;
    } else if (kind == TOKEN_LPAREN || kind == TOKEN_LBRACKET) {
      score = score + 1;
    } else if (kind == TOKEN_IF) {
      parser_asm_stretch_if_header_audit_c(lex, source);
      score = score + 3;
    } else if (kind == TOKEN_MATCH) {
      parser_asm_stretch_match_kw_audit_c(lex, source);
      score = score + 3;
    } else if (kind == TOKEN_PANIC) {
      score = score + 2;
    } else if (kind == TOKEN_AT) {
      score = score + 2;
    } else if (kind == TOKEN_BREAK) {
      parser_asm_stretch_break_continue_audit_c(lex, source, 1);
      score = score + 1;
    } else if (kind == TOKEN_CONTINUE) {
      parser_asm_stretch_break_continue_audit_c(lex, source, 0);
      score = score + 1;
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return score;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_diag_fn_header_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_diag_fn_header_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_fn_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_function_header_audit_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_FUNCTION) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return score;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind == TOKEN_IDENT && idlen > 0) {
        idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);
        parser_asm_stretch_bind_name_validate_c(idptr, idlen);
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return score + 1;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_diag_fn_return_type_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_diag_fn_return_type_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_fn_return_type_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_COLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_STAR) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
    if (kind == TOKEN_LBRACKET) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if ((parser_asm_lex_is_type_start_kind_c(kind) != 0)) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_diag_skip_let_const_type_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_diag_skip_let_const_type_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_skip_let_const_type_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_COLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_STAR) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if ((parser_asm_lex_is_type_start_kind_c(kind) != 0)) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_skip_one_if_else_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_skip_one_if_else_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_if_else_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_else_if_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_else_stmt_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_parse_cond_expr_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_parse_cond_expr_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_cond_expr_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_cond_int_as_audit_c(lex, source);
    score = score + parser_asm_stretch_paren_expr_head_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_balanced_delim_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_balanced_delim_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_delim_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_balanced_parens_depth_probe_c(lex, source);
    score = score + parser_asm_stretch_balanced_braces_depth_probe_c(lex, source);
    score = score + parser_asm_stretch_balanced_brackets_depth_probe_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_try_skip_allow_paren_audit_c forwards to parser_asm_stretch_paren_expr_head_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_try_skip_allow_paren_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_paren_expr_head_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_trait_method_paren_audit_c forwards to parser_asm_stretch_paren_expr_head_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_trait_method_paren_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_paren_expr_head_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_try_skip_allow_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_try_skip_allow_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_try_skip_allow_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_try_skip_allow_paren_audit_c(lex, source);
    score = score + parser_asm_stretch_balanced_parens_depth_probe_c(lex, source);
    score = score + parser_asm_stretch_balanced_braces_depth_probe_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_trait_method_return_audit_c forwards to parser_asm_stretch_diag_fn_return_type_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_trait_method_return_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_diag_fn_return_type_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_extern_return_type_audit_c forwards to parser_asm_stretch_diag_fn_return_type_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_extern_return_type_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_diag_fn_return_type_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_impl_fn_return_audit_c forwards to parser_asm_stretch_diag_fn_return_type_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_impl_fn_return_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_diag_fn_return_type_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated delegation port: parser_asm_stretch_body_skip_let_const_type_audit_c forwards to parser_asm_stretch_diag_skip_let_const_type_audit_c.
 * Pointer ABI + by-value net semantics (callee restores).
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_body_skip_let_const_type_audit_c(lex: *u8, source: *u8): i32 {
  unsafe {
    return parser_asm_stretch_diag_skip_let_const_type_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_shift_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_shift_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_shift_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_LSHIFT || kind == TOKEN_RSHIFT) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_rel_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_rel_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_rel_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_LT || kind == TOKEN_LE || kind == TOKEN_GT || kind == TOKEN_GE) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_eq_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_eq_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_eq_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_EQ || kind == TOKEN_NE) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_bitand_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_bitand_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_bitand_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_AMP) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_bitxor_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_bitxor_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_bitxor_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_CARET) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_bitor_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_bitor_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_bitor_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_PIPE) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_logand_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_logand_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_logand_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_AMPAMP) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_logor_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_logor_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_logor_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_PIPEPIPE) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    return n;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_binop_upper_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_binop_upper_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_upper_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_expr_rel_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_eq_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_bitand_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_bitxor_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_bitor_binop_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_binop_mid_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_binop_mid_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_mid_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_expr_logand_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_logor_binop_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_addsub_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_addsub_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_addsub_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    n = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_PLUS || kind == TOKEN_MINUS) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_expr_mul_binop_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_mul_binop_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_mul_binop_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    n = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_STAR || kind == TOKEN_SLASH || kind == TOKEN_PERCENT) {
      n = n + 1;
      if (n > 32) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return n;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return n;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_unary_prefix_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_unary_prefix_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_unary_prefix_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let depth: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    depth = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_AWAIT || kind == TOKEN_RUN || kind == TOKEN_SPAWN || kind == TOKEN_MINUS || kind == TOKEN_BANG) {
      depth = depth + 1;
      if (depth > 16) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return depth;
      }
      parser_asm_lex_step_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
      kind = parser_asm_lex_peek_kind_c(lex, source);
    }
    if (kind == TOKEN_AMP) {
        parser_asm_lex_step_kind_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        if (kind != TOKEN_AMP) {
          depth = depth + 1;
        }
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return depth;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_binop_lower_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_binop_lower_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_lower_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_expr_mul_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_addsub_binop_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_shift_binop_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_binop_full_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_binop_full_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_full_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_expr_binop_lower_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_binop_upper_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_binop_mid_chain_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      if (score > 0) {
        return 1;
      }
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated buf-shim port parser_asm_stretch_balanced_braces_depth_probe_buf_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_balanced_braces_depth_probe_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_braces_depth_probe_buf_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_balanced_braces_depth_probe_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated buf-shim port parser_asm_stretch_body_skip_let_const_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_let_const_decl_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_body_skip_let_const_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_let_const_decl_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_trait_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_trait_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_trait_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_trait_header_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_balanced_parens_depth_probe_buf_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_balanced_parens_depth_probe_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_parens_depth_probe_buf_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_balanced_parens_depth_probe_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_enum_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_enum_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_enum_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_enum_header_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_if_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_if_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_if_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_if_header_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_try_skip_allow_paren_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_try_skip_allow_paren_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_try_skip_allow_paren_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_try_skip_allow_paren_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_imports_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_import_stmt_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_imports_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_import_stmt_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_parse_peek_function_name_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_function_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_peek_function_name_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_function_header_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_if_else_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_skip_one_if_else_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_if_else_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_skip_one_if_else_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_async_fn_prefix_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_async_fn_prefix_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_async_fn_prefix_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_async_fn_prefix_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_cond_int_as_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_cond_int_as_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cond_int_as_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_cond_int_as_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_primary_head_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_primary_head_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_primary_head_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_primary_head_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_parse_cond_expr_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_parse_cond_expr_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_cond_expr_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_parse_cond_expr_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_binop_lower_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_binop_lower_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_lower_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_binop_lower_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_binop_upper_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_binop_upper_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_upper_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_binop_upper_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_binop_mid_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_binop_mid_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_mid_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_binop_mid_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_binop_full_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_binop_full_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_binop_full_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_binop_full_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_try_skip_allow_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_try_skip_allow_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_try_skip_allow_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_try_skip_allow_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_balanced_delim_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_balanced_delim_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_delim_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_balanced_delim_full_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port: balanced_brackets_depth_probe_buf wraps (data,len)
 * via the bridge ring and delegates to balanced_brackets_depth_probe.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_balanced_brackets_depth_probe_buf_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_balanced_brackets_depth_probe_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_type_ref_peek_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_type_ref_peek_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_type_ref_peek_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let adv0: usize = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_STAR) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
    if ((parser_asm_lex_is_type_start_kind_c(kind) == 0)) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    adv0 = parser_asm_lex_pos_c(lex);
    parser_asm_lex_skip_type_suffix_inplace_c(lex, source);
      if (parser_asm_lex_pos_c(lex) != pos0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_array_lit_head_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_array_lit_head_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_array_lit_head_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_LBRACKET) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
      if (kind == TOKEN_RBRACKET || kind == TOKEN_INT || kind == TOKEN_IDENT || kind == TOKEN_TRUE || kind == TOKEN_FALSE) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated thick-buf port of `parser_asm_stretch_skip_one_function_full_buf_audit_c`: wraps (data,len) via the bridge ring,
 * then runs the translated audit body over the opaque slice.
 * @param lex *u8 — opaque lexer (read-only net effect via restore trio)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_function_full_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let source: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || data == 0 as *u8 || len <= 0) {
    return 0;
  }
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_function_header_audit_c(lex, source);
    score = score + parser_asm_stretch_async_fn_prefix_audit_c(lex, source);
    score = score + parser_asm_stretch_fn_sig_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_body_let_bracket_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_body_let_bracket_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_body_let_bracket_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_array_lit_head_audit_c(lex, source);
    score = score + parser_asm_stretch_let_in_block_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_diag_skip_let_const_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_diag_skip_let_const_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_skip_let_const_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_diag_skip_let_const_type_audit_c(lex, source);
    score = score + parser_asm_stretch_body_let_bracket_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_let_in_block_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_impl_header_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_impl_header_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_impl_header_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IMPL) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind == TOKEN_FOR) {
        parser_asm_lex_step_kind_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        if (kind != TOKEN_IDENT || idlen <= 0) {
          parser_asm_lex_set_pos_c(lex, pos0);
          parser_asm_lex_set_line_c(lex, line0);
          parser_asm_lex_set_col_c(lex, col0);
          return 0;
        }
        parser_asm_lex_step_kind_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    }
      if (kind == TOKEN_LBRACE) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_impl_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_impl_header_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_impl_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_impl_header_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_primary_suffix_chain_probe_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_primary_suffix_chain_probe_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_primary_suffix_chain_probe_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let guard: i32 = 0;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = 0;
    guard = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    while (guard < 64) {
      guard = guard + 1;
        if (kind == TOKEN_DOT) {
            score = score + 2;
            parser_asm_lex_step_kind_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
            if (kind != TOKEN_IDENT) {
              break;
            }
            idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);
            parser_asm_stretch_bind_name_validate_c(idptr, idlen);
            parser_asm_lex_step_kind_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        } else if (kind == TOKEN_LBRACKET) {
            score = score + 2;
            parser_asm_lex_step_kind_c(lex, source);
            parser_asm_lex_skip_balanced_brackets_inplace_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        } else if (kind == TOKEN_LPAREN) {
            score = score + 3;
            parser_asm_lex_step_kind_c(lex, source);
            parser_asm_lex_skip_balanced_parens_inplace_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        } else {
            break;
        }
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return score;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_struct_modifiers_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_struct_modifiers_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_struct_modifiers_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let guard: i32 = 0;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = 0;
    guard = 0;
    while (guard <= 12) {
      guard = guard + 1;
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        if (kind == TOKEN_PACKED || kind == TOKEN_SOA || kind == TOKEN_ALIGN) {
            score = score + 8;
            parser_asm_lex_step_kind_c(lex, source);
            continue;
        }
        data2 = parser_asm_lex_source_data_c(source);
        sln2 = parser_asm_lex_source_length_c(source);
        ts2 = parser_asm_lex_peek_token_start_c(lex, source);
        bhit = 0;
        if (data2 != 0 as *u8 && ts2 + 4 < sln2) {
          unsafe {
            if (data2[ts2 + 0] == 97 && data2[ts2 + 1] == 108 && data2[ts2 + 2] == 108 && data2[ts2 + 3] == 111 && data2[ts2 + 4] == 119) {
              bhit = 1;
            }
          }
        }
        if (kind == TOKEN_IDENT && idlen == 5 && bhit == 1) {
            score = score + 4;
            parser_asm_lex_step_kind_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
            if (kind == TOKEN_LPAREN) {
                parser_asm_lex_step_kind_c(lex, source);
                parser_asm_lex_skip_balanced_parens_inplace_c(lex, source);
                score = score + 4;
            }
            continue;
        }
        break;
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return score;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated thick-buf port of `parser_asm_stretch_skip_one_struct_buf_audit_c`: wraps (data,len) via the bridge ring,
 * then runs the translated audit body over the opaque slice.
 * @param lex *u8 — opaque lexer (read-only net effect via restore trio)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_struct_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let source: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || data == 0 as *u8 || len <= 0) {
    return 0;
  }
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_struct_modifiers_audit_c(lex, source);
    score = score + parser_asm_stretch_struct_header_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_extern_fn_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_extern_fn_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_extern_fn_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let adv0: usize = 0;
  let idptr: *u8 = 0 as *u8;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_EXTERN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_FUNCTION) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_IDENT || idlen <= 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_LPAREN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    if ((parser_asm_stretch_fn_param_list_audit_c(lex, source) == 0)) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_COLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    while (kind != TOKEN_SEMICOLON && kind != TOKEN_EOF) {
        if (kind == TOKEN_STAR) {
            parser_asm_lex_step_kind_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
            continue;
        }
        if ((parser_asm_lex_is_type_start_kind_c(kind) != 0)) {
            parser_asm_lex_step_kind_c(lex, source);
            adv0 = parser_asm_lex_pos_c(lex);
            parser_asm_lex_skip_type_suffix_inplace_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
            continue;
        }
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
      if (kind == TOKEN_SEMICOLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_as_suffix_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_as_suffix_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_as_suffix_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let adv0: usize = 0;
  let idptr: *u8 = 0 as *u8;
  let guard: i32 = 0;
  let n: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    n = 0;
    guard = 0;
    kind = parser_asm_lex_peek_kind_c(lex, source);
    while (kind == TOKEN_AS) {
        n = n + 1;
        guard = guard + 1;
        if (n > 16 || (guard - 1) > 32) {
          parser_asm_lex_set_pos_c(lex, pos0);
          parser_asm_lex_set_line_c(lex, line0);
          parser_asm_lex_set_col_c(lex, col0);
          return n;
        }
        parser_asm_lex_step_kind_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        if (kind == TOKEN_STAR) {
            parser_asm_lex_step_kind_c(lex, source);
            kind = parser_asm_lex_peek_kind_c(lex, source);
            idlen = parser_asm_lex_peek_ident_len_c(lex, source);
        }
        if ((parser_asm_lex_is_type_start_kind_c(kind) == 0)) {
          parser_asm_lex_set_pos_c(lex, pos0);
          parser_asm_lex_set_line_c(lex, line0);
          parser_asm_lex_set_col_c(lex, col0);
          return n;
        }
        parser_asm_lex_step_kind_c(lex, source);
        adv0 = parser_asm_lex_pos_c(lex);
        parser_asm_lex_skip_type_suffix_inplace_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return n;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_primary_expr_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_primary_expr_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_primary_expr_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_primary_head_audit_c(lex, source);
    score = score + parser_asm_stretch_unary_prefix_audit_c(lex, source);
    score = score + parser_asm_stretch_primary_suffix_chain_probe_c(lex, source);
    score = score + parser_asm_stretch_as_suffix_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_parse_expr_prefix_chain_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_parse_expr_prefix_chain_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_expr_prefix_chain_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_unary_prefix_audit_c(lex, source);
    score = score + parser_asm_stretch_primary_head_audit_c(lex, source);
    score = score + parser_asm_stretch_as_suffix_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_cast_unary_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_cast_unary_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cast_unary_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_unary_prefix_audit_c(lex, source);
    score = score + parser_asm_stretch_as_suffix_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_primary_head_audit_c(lex, source);
    score = score + parser_asm_stretch_type_ref_peek_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_parse_one_extern_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_extern_fn_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_one_extern_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_extern_fn_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_extern_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_extern_fn_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_extern_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_extern_fn_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_ternary_assign_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_ternary_assign_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_ternary_op_audit_c(lex, source);
    score = score + parser_asm_stretch_assign_op_audit_c(lex, source);
    score = score + parser_asm_stretch_parse_expr_prefix_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_parse_cond_expr_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_parse_cond_expr_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_cond_expr_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_parse_cond_expr_audit_c(lex, source);
    score = score + parser_asm_stretch_parse_expr_prefix_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_binop_lower_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_parse_expr_prefix_chain_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_parse_expr_prefix_chain_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_expr_prefix_chain_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_parse_expr_prefix_chain_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_cast_unary_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_cast_unary_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cast_unary_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_cast_unary_full_deep_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_stmt_full_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_stmt_full_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_stmt_full_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_expr_binop_full_chain_audit_c(lex, source);
    score = score + parser_asm_stretch_ternary_assign_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_parse_expr_prefix_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_return_stmt_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_return_stmt_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_return_stmt_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_return_stmt_audit_c(lex, source);
    score = score + parser_asm_stretch_parse_cond_expr_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_break_continue_audit_c(lex, source, 0);
    score = score + parser_asm_stretch_label_stmt_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_ternary_assign_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_ternary_assign_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_ternary_assign_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_parse_cond_expr_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_parse_cond_expr_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_parse_cond_expr_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_parse_cond_expr_deep_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_ternary_assign_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_ternary_assign_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_ternary_assign_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_stmt_full_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_binop_full_chain_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_stmt_control_mega_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_stmt_control_mega_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_stmt_control_mega_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_return_stmt_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_break_continue_audit_c(lex, source, 1);
    score = score + parser_asm_stretch_break_continue_audit_c(lex, source, 0);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_stmt_full_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_stmt_full_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_stmt_full_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_stmt_full_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_return_stmt_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_return_stmt_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_return_stmt_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_return_stmt_full_deep_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_expr_stmt_mega_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_expr_stmt_mega_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_stmt_mega_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_return_stmt_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_cast_unary_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_ternary_assign_full_deep_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_ternary_assign_mega_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_ternary_assign_mega_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_mega_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_ternary_assign_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_stmt_mega_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_assign_op_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_cast_unary_mega_full_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_cast_unary_mega_full_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cast_unary_mega_full_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_cast_unary_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_expr_stmt_mega_full_deep_audit_c(lex, source);
    score = score + parser_asm_stretch_unary_prefix_audit_c(lex, source);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_expr_stmt_mega_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_expr_stmt_mega_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_expr_stmt_mega_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_expr_stmt_mega_full_deep_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated buf-shim port parser_asm_stretch_diag_skip_let_const_type_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_diag_skip_let_const_type_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_skip_let_const_type_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_diag_skip_let_const_type_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_diag_skip_let_const_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_diag_skip_let_const_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_skip_let_const_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_diag_skip_let_const_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_ternary_assign_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_ternary_assign_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_ternary_assign_full_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_ternary_assign_mega_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_ternary_assign_mega_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_ternary_assign_mega_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_ternary_assign_mega_full_deep_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_cast_unary_mega_full_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `parser_asm_stretch_cast_unary_mega_full_deep_audit_c`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_cast_unary_mega_full_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_cast_unary_mega_full_deep_audit_c(lex, source);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated buf-shim port parser_asm_stretch_skip_one_enum_register_buf_audit_c.
 * Generated buf→buf port: passes (data,len) through to .
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_skip_one_enum_register_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  unsafe {
    if (data == 0 as *u8 || len <= 0) {
      return 0;
    }
    return parser_asm_stretch_skip_one_enum_buf_audit_c(lex, data, len);
  }
  return 0;
}

/* ── generated (gen_stretch_audit_x.py) ── */

/**
 * Generated audit port parser_asm_stretch_library_fn_shape_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_library_fn_shape_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_library_fn_shape_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let rc: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    if (parser_asm_stretch_function_header_audit_c(lex, source) == 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_FUNCTION) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_SPAWN) {
        parser_asm_lex_step_kind_c(lex, source);
        kind = parser_asm_lex_peek_kind_c(lex, source);
        idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    }
    if (kind != TOKEN_IDENT) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_LPAREN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
      rc = parser_asm_stretch_fn_param_list_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return rc;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_type_ref_deep_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_type_ref_deep_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_type_ref_deep_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let adv0: usize = 0;
  let idptr: *u8 = 0 as *u8;
  let rc: i32 = 0;
  let score: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_type_ref_peek_audit_c(lex, source);
    parser_asm_lex_set_pos_c(lex, pos0);
    parser_asm_lex_set_line_c(lex, line0);
    parser_asm_lex_set_col_c(lex, col0);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind == TOKEN_STAR) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return score + 1;
    }
    if (kind == TOKEN_LBRACKET) {
        parser_asm_lex_step_kind_c(lex, source);
        parser_asm_lex_skip_balanced_brackets_inplace_c(lex, source);
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return score + 2;
    }
    if ((parser_asm_lex_is_type_start_kind_c(kind) != 0)) {
        parser_asm_lex_step_kind_c(lex, source);
        adv0 = parser_asm_lex_pos_c(lex);
        parser_asm_lex_skip_type_suffix_inplace_c(lex, source);
        if (parser_asm_lex_pos_c(lex) != adv0) {
          score = score + 2;
        }
    }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return score;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_diag_fn_param_sig_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_diag_fn_param_sig_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_diag_fn_param_sig_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let rc: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    if (kind != TOKEN_LPAREN) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
      rc = parser_asm_stretch_fn_param_list_audit_c(lex, source);
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return rc;
  }
  return 0;
}

/**
 * Generated audit port parser_asm_stretch_library_return_type_audit_c.
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `parser_asm_stretch_library_return_type_audit_c` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_library_return_type_audit_c(lex: *u8, source: *u8): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let data2: *u8 = 0 as *u8;
  let ts2: usize = 0;
  let sln2: usize = 0;
  let bhit: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let rc: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {
    return 0;
  }
  unsafe {
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind != TOKEN_COLON) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 0;
    }
    parser_asm_lex_step_kind_c(lex, source);
    kind = parser_asm_lex_peek_kind_c(lex, source);
    idlen = parser_asm_lex_peek_ident_len_c(lex, source);
    if (kind == TOKEN_BOOL) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
    data2 = parser_asm_lex_source_data_c(source);
    sln2 = parser_asm_lex_source_length_c(source);
    ts2 = parser_asm_lex_peek_token_start_c(lex, source);
    bhit = 0;
    if (data2 != 0 as *u8 && ts2 + 3 < sln2 && data2[ts2 + 0] == 98 && data2[ts2 + 1] == 111 && data2[ts2 + 2] == 111 && data2[ts2 + 3] == 108) {
      bhit = 1;
    }
    if (kind == TOKEN_IDENT && idlen == 4 && bhit == 1) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
    }
      if ((parser_asm_lex_is_type_start_kind_c(kind) != 0)) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated thick-buf port of `parser_asm_stretch_library_scan_buf_audit_c`: wraps (data,len) via the bridge ring,
 * then runs the translated audit body over the opaque slice.
 * @param lex *u8 — opaque lexer (read-only net effect via restore trio)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_library_scan_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  let idptr: *u8 = 0 as *u8;
  let source: *u8 = 0 as *u8;
  let rc: i32 = 0;
  let score: i32 = 0;
  if (lex == 0 as *u8 || data == 0 as *u8 || len <= 0) {
    return 0;
  }
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
    score = parser_asm_stretch_library_fn_shape_buf_audit_c(lex, data, len);
    score = score + parser_asm_stretch_library_return_type_buf_audit_c(lex, data, len);
      if (score > 0) {
        parser_asm_lex_set_pos_c(lex, pos0);
        parser_asm_lex_set_line_c(lex, line0);
        parser_asm_lex_set_col_c(lex, col0);
        return 1;
      }
      parser_asm_lex_set_pos_c(lex, pos0);
      parser_asm_lex_set_line_c(lex, line0);
      parser_asm_lex_set_col_c(lex, col0);
      return 0;
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_library_fn_shape_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit .
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_library_fn_shape_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_library_fn_shape_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_library_return_type_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit .
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_library_return_type_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_library_return_type_audit_c(lex, source);
  }
  return 0;
}

/**
 * Generated buf-shim port parser_asm_stretch_type_ref_deep_buf_audit_c.
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit .
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function parser_asm_stretch_type_ref_deep_buf_audit_c(lex: *u8, data: *u8, len: i32): i32 {
  let source: *u8 = 0 as *u8;
  unsafe {
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {
      return 0;
    }
    return parser_asm_stretch_type_ref_deep_audit_c(lex, source);
  }
  return 0;
}
