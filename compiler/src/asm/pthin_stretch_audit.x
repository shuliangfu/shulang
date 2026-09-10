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

// Lexer canonical TokenKind values (enum token_TokenKind indices; authority
// include/token.h == seeds/lexer_gen.linux.x86_64.c, verified identical 133
// entries — see pthin_stretch.x for the rest of the constant set).
const TOKEN_IF: i32 = 4;
const TOKEN_LPAREN: i32 = 82;

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
