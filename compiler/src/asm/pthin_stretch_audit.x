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

// Lexer canonical TokenKind values (enum token_TokenKind indices; authority
// include/token.h == seeds/lexer_gen.linux.x86_64.c, verified identical 133
// entries — see pthin_stretch.x for the rest of the constant set).
const TOKEN_EOF: i32 = 0;
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
