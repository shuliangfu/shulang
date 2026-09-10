// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// pthin_stretch — parser EMIT_HEAVY second-pass thin_glue stretch face:
// TokenKind metadata tables, import-path validation/normalization, label
// probing, comment/whitespace skipping, keyword spelling verification.
// Symbol names carry the parser_asm_stretch_* prefix (never clash with
// parser_x.o / seed slice faces).
//
// 7.2.1 main-debt Route C pilot (2026-09-10, RFC
// analysis/7.2.1-parser-inc-port-ABI-RFC.md): this slice has zero
// struct-by-value params, zero struct field access, zero Cap-header
// inline / memcpy / getenv — a pure byte/integer domain, the ideal first
// proof that .inc C parser logic can live as real .x function bodies.
// Hybrid position P9: XLANG_PTHIN_STRETCH_FROM_X + ld -r into
// parser_asm_thin_glue.o; the cold twin (seeds/pthin_stretch.from_x.c)
// keeps the .inc fallback for no-PREFER cold builds.
// PLATFORM: SHARED freestanding.

// --- TokenKind metadata tables (indices align with the lexer's TOKEN_*). ---

/** run_len by kind when token_start==0 (keywords/literals); 0 = fallback 1. */
let g_stretch_run_len: u8[64] = [
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 5, 3, 2,
  4, 5, 3, 6, 4, 6, 6, 0, 0, 0, 0, 0, 0, 5, 5, 4,
  5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];

/** ident first-byte class (a-z A-Z _). */
let g_stretch_ident_start: u8[256] = [
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];

/** ident continue-byte class (a-z A-Z 0-9 _). */
let g_stretch_ident_continue: u8[256] = [
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];

// --- TokenKind constants (aligned with the C enum in the .inc). ---
const STRETCH_TOKEN_IDENT: i32 = 1;
const STRETCH_TOKEN_COLON: i32 = 10;
const STRETCH_TOKEN_RETURN: i32 = 11;
const STRETCH_TOKEN_FUNCTION: i32 = 12;
const STRETCH_TOKEN_CONST: i32 = 13;
const STRETCH_TOKEN_LET: i32 = 14;
const STRETCH_TOKEN_STRUCT: i32 = 19;
const STRETCH_TOKEN_ENUM: i32 = 20;
const STRETCH_TOKEN_IMPORT: i32 = 21;
const STRETCH_TOKEN_EXTERN: i32 = 22;
const STRETCH_TOKEN_ALIGN: i32 = 33;
// TOKEN_TYPE = 23, TOKEN_PACKED = 17, TOKEN_SOA = 18 (lexer canonical).

/**
 * Byte length of a keyword/literal token by kind when token_start==0;
 * unlisted kinds return 1 (fallback semantics identical to the C table).
 * @param kind i32 — lexer token kind
 * @return i32 — literal byte length (>= 1)
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_token_run_len_c(kind: i32): i32 {
  if (kind >= 0 && kind < 64) {
    let v: i32 = g_stretch_run_len[kind] as i32;
    if (v > 0) {
      return v;
    }
  }
  return 1;
}

/**
 * Import path validation: every byte must be ident_start/ident_continue
 * class or '.' (dot separator); empty or null fails.
 * @param path *u8 — import path bytes (need not be NUL-terminated)
 * @param path_len i32 — byte length; <= 0 fails
 * @return i32 — 1 valid; 0 invalid
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_import_path_validate_c(path: *u8, path_len: i32): i32 {
  let i: i32 = 0;
  if (path == 0 as *u8 || path_len <= 0) {
    return 0;
  }
  if (path_len > 63) {
    path_len = 63;
  }
  while (i < path_len) {
    let c: u8 = 0;
    unsafe { c = path[i]; }
    if (c == 0) {
      break;
    }
    if (c == 46) {
      i = i + 1;
      continue;
    }
    unsafe {
      if (g_stretch_ident_continue[c] == 0) {
        return 0;
      }
    }
    i = i + 1;
  }
  return 1;
}

/**
 * Struct field-name keyword check: ident / type / packed / soa / align
 * (field names may reuse keyword tokens — std/schema root fix).
 * @param kind i32 — current token kind
 * @return i32 — 1 when the kind can start a field name; 0 otherwise
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_struct_field_name_kind_c(kind: i32): i32 {
  if (kind == STRETCH_TOKEN_IDENT) {
    return 1;
  }
  if (kind == 17 || kind == 18 || kind == 23) {
    return 1;
  }
  if (kind == STRETCH_TOKEN_ALIGN) {
    return 1;
  }
  return 0;
}

/**
 * Struct field-list continuation: field-name kind or align(N) prefix.
 * @param kind i32 — current token kind
 * @return i32 — 1 when the field list continues; 0 otherwise
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_struct_field_continues_kind_c(kind: i32): i32 {
  if (parser_asm_stretch_struct_field_name_kind_c(kind) != 0) {
    return 1;
  }
  if (kind == STRETCH_TOKEN_ALIGN) {
    return 1;
  }
  return 0;
}

/**
 * Label-statement probe: current IDENT and lookahead COLON.
 * @param cur_kind i32 — current token kind
 * @param next_kind i32 — lookahead token kind
 * @return i32 — 1 when this looks like `ident:`; 0 otherwise
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_token_is_label_start_c(cur_kind: i32, next_kind: i32): i32 {
  if (cur_kind != STRETCH_TOKEN_IDENT) {
    return 0;
  }
  if (next_kind == STRETCH_TOKEN_COLON) {
    return 1;
  }
  return 0;
}

/**
 * Diagnostic coarse filter: is the first token after `import` a
 * declaration keyword (struct/enum/function/import/extern/const/let)?
 * @param kind i32 — token kind
 * @return i32 — 1 declaration keyword; 0 otherwise
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_diag_after_imports_kind_c(kind: i32): i32 {
  if (kind == STRETCH_TOKEN_STRUCT || kind == STRETCH_TOKEN_ENUM) {
    return 1;
  }
  if (kind == STRETCH_TOKEN_FUNCTION || kind == STRETCH_TOKEN_IMPORT) {
    return 1;
  }
  if (kind == STRETCH_TOKEN_EXTERN || kind == STRETCH_TOKEN_CONST) {
    return 1;
  }
  if (kind == STRETCH_TOKEN_LET) {
    return 1;
  }
  return 0;
}

/**
 * Normalize path_buf[0..path_len) into a module import slot: drop
 * invalid bytes, truncate at NUL, strip trailing dots. Caps at 63.
 * @param path_buf *u8 — in/out buffer (normalized in place)
 * @param path_len i32 — input byte length
 * @return i32 — normalized valid length (may be < path_len; 0 on invalid)
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_import_path_normalize_c(path_buf: *u8, path_len: i32): i32 {
  let i: i32 = 0;
  let out_len: i32 = 0;
  if (path_buf == 0 as *u8 || path_len <= 0) {
    return 0;
  }
  if (path_len > 63) {
    path_len = 63;
  }
  if (parser_asm_stretch_import_path_validate_c(path_buf, path_len) == 0) {
    return 0;
  }
  while (i < path_len) {
    let c: u8 = 0;
    unsafe { c = path_buf[i]; }
    if (c == 0) {
      break;
    }
    if (c == 46) {
      unsafe { path_buf[out_len] = c; }
      out_len = out_len + 1;
    } else {
      unsafe {
        if (g_stretch_ident_continue[c] != 0) {
          path_buf[out_len] = c;
          out_len = out_len + 1;
        }
      }
    }
    i = i + 1;
  }
  while (out_len > 0) {
    let last: u8 = 0;
    unsafe { last = path_buf[out_len - 1]; }
    if (last != 46) {
      break;
    }
    out_len = out_len - 1;
  }
  return out_len;
}

/**
 * Skip a line (//) or block comment when data[pos] points at '/'.
 * @param data *u8 — source bytes
 * @param len usize — source length
 * @param pos usize — current position
 * @return usize — updated position (or pos when not a comment)
 * PLATFORM: SHARED.
 */
function parser_asm_stretch_skip_comment_at_c(data: *u8, len: usize, pos: usize): usize {
  let i: usize = 0;
  if (data == 0 as *u8) {
    return pos;
  }
  if (pos + 1 >= len) {
    return pos;
  }
  unsafe {
    if (data[pos] == 47 && data[pos + 1] == 47) {
      i = pos + 2;
      while (i < len) {
        if (data[i] == 10 || data[i] == 13) {
          break;
        }
        i = i + 1;
      }
      return i;
    }
    if (data[pos] == 47 && data[pos + 1] == 42) {
      i = pos + 2;
      while (i + 1 < len) {
        if (data[i] == 42 && data[i + 1] == 47) {
          return i + 2;
        }
        i = i + 1;
      }
      return len;
    }
  }
  return pos;
}

/**
 * Advance past whitespace and comments without mutating lexer state.
 * @param data *u8 — source bytes
 * @param len usize — source length
 * @param pos usize — starting position
 * @return usize — first non-ws non-comment position
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_skip_ws_and_comments_c(data: *u8, len: usize, pos: usize): usize {
  let p: usize = pos;
  let moved: i32 = 0;
  if (data == 0 as *u8 || len == 0) {
    return pos;
  }
  while (true) {
    moved = 0;
    while (p < len) {
      let c: u8 = 0;
      unsafe { c = data[p]; }
      if (c == 32 || c == 9 || c == 10 || c == 13) {
        p = p + 1;
        moved = 1;
        continue;
      }
      break;
    }
    let np: usize = parser_asm_stretch_skip_comment_at_c(data, len, p);
    if (np != p) {
      p = np;
      moved = 1;
    }
    if (moved == 0) {
      break;
    }
  }
  return p;
}

// --- Keyword spelling verification (coarse, table-driven). ---

// 35 keywords x 10 bytes each (longest is "function"=8 + NUL; row-major).
let g_stretch_kw_spell: u8[350] = [
  114, 101, 116, 117, 114, 110, 0, 0, 0, 0,
  102, 117, 110, 99, 116, 105, 111, 110, 0, 0,
   99, 111, 110, 115, 116, 0, 0, 0, 0, 0,
  119, 104, 105, 108, 101, 0, 0, 0, 0, 0,
  102, 97, 108, 115, 101, 0, 0, 0, 0, 0,
  115, 116, 114, 117, 99, 116, 0, 0, 0, 0,
  105, 109, 112, 111, 114, 116, 0, 0, 0, 0,
  101, 120, 116, 101, 114, 110, 0, 0, 0, 0,
   97, 115, 121, 110, 99, 0, 0, 0, 0, 0,
  108, 101, 116, 0, 0, 0, 0, 0, 0, 0,
  105, 102, 0, 0, 0, 0, 0, 0, 0, 0,
  102, 111, 114, 0, 0, 0, 0, 0, 0, 0,
  101, 108, 115, 101, 0, 0, 0, 0, 0, 0,
  116, 114, 117, 101, 0, 0, 0, 0, 0, 0,
  101, 110, 117, 109, 0, 0, 0, 0, 0, 0,
  109, 97, 116, 99, 104, 0, 0, 0, 0, 0,
  112, 97, 99, 107, 101, 100, 0, 0, 0, 0,
  115, 111, 97, 0, 0, 0, 0, 0, 0, 0,
   97, 108, 105, 103, 110, 0, 0, 0, 0, 0,
  116, 114, 97, 105, 116, 0, 0, 0, 0, 0,
  105, 109, 112, 108, 0, 0, 0, 0, 0, 0,
  116, 121, 112, 101, 0, 0, 0, 0, 0, 0,
   97, 115, 0, 0, 0, 0, 0, 0, 0, 0,
   98, 114, 101, 97, 107, 0, 0, 0, 0, 0,
   99, 111, 110, 116, 105, 110, 117, 101, 0, 0,
  100, 101, 102, 101, 114, 0, 0, 0, 0, 0,
   97, 119, 97, 105, 116, 0, 0, 0, 0, 0,
  112, 117, 98, 0, 0, 0, 0, 0, 0, 0,
  109, 117, 116, 0, 0, 0, 0, 0, 0, 0,
  117, 110, 115, 97, 102, 101, 0, 0, 0, 0,
  102, 110, 0, 0, 0, 0, 0, 0, 0, 0,
  109, 111, 100, 0, 0, 0, 0, 0, 0, 0,
  117, 115, 101, 0, 0, 0, 0, 0, 0, 0,
  119, 104, 101, 114, 101, 0, 0, 0, 0, 0,
  108, 111, 111, 112, 0, 0, 0, 0, 0, 0,
  108, 97, 98, 101, 108, 0, 0, 0, 0, 0,
];

const STRETCH_KW_COUNT: i32 = 35;
const STRETCH_KW_ROW: i32 = 10;

/**
 * Coarse keyword-spelling check: does any table keyword match exactly
 * run_len bytes at data[token_start]? Matches return 1; no match also
 * returns 1 (coarse pass — kind unused, mirrors C semantics).
 * @param data *u8 — source bytes
 * @param len usize — source length
 * @param token_start usize — token byte offset
 * @param kind i32 — token kind (unused; C parity)
 * @param run_len i32 — literal length; <= 0 or overflow fails
 * @return i32 — 1 coarse-ok; 0 hard-fail
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_verify_kw_spelling_c(data: *u8, len: usize, token_start: usize, kind: i32, run_len: i32): i32 {
  let ki: i32 = 0;
  let i: i32 = 0;
  if (data == 0 as *u8 || run_len <= 0) {
    return 0;
  }
  if (token_start + run_len as usize > len) {
    return 0;
  }
  while (ki < STRETCH_KW_COUNT) {
    let base: i32 = ki * STRETCH_KW_ROW;
    i = 0;
    while (i < run_len) {
      let kw_c: u8 = 0;
      let src_c: u8 = 0;
      unsafe {
        kw_c = g_stretch_kw_spell[base + i];
        src_c = data[token_start + i as usize];
      }
      if (kw_c == 0) {
        break;
      }
      if (src_c != kw_c) {
        break;
      }
      i = i + 1;
    }
    let kw_end: u8 = 0;
    unsafe { kw_end = g_stretch_kw_spell[base + i]; }
    if (kw_end == 0 && i == run_len) {
      return 1;
    }
    ki = ki + 1;
  }
  return 1;
}

/**
 * Import path finalize: normalize then re-validate (optionally skip ws
 * and comments at source start first — coarse audit hook).
 * @param path_buf *u8 — in/out path buffer
 * @param path_len i32 — input length
 * @param source *u8 — source bytes (optional; may be null)
 * @param source_len usize — source length
 * @return i32 — normalized length when valid; 0 otherwise
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_import_path_finalize_c(path_buf: *u8, path_len: i32, source: *u8, source_len: usize): i32 {
  let nlen: i32 = 0;
  if (path_buf == 0 as *u8 || path_len <= 0) {
    return 0;
  }
  nlen = parser_asm_stretch_import_path_normalize_c(path_buf, path_len);
  if (nlen <= 0) {
    return 0;
  }
  if (source != 0 as *u8 && source_len > 0) {
    let np: usize = parser_asm_stretch_skip_ws_and_comments_c(source, source_len, 0);
    if (np == source_len) {
      return 0;
    }
  }
  if (parser_asm_stretch_import_path_validate_c(path_buf, nlen) != 0) {
    return nlen;
  }
  return 0;
}

/**
 * Ident byte class check: first byte ident_start, others ident_continue.
 * @param c u8 — byte to check
 * @param is_first i32 — 1 for the first byte; 0 for continuation
 * @return i32 — 1 ok; 0 rejected
 * PLATFORM: SHARED.
 */
function parser_asm_stretch_ident_byte_ok_c(c: u8, is_first: i32): i32 {
  if (is_first != 0) {
    unsafe {
      if (g_stretch_ident_start[c] != 0) {
        return 1;
      }
    }
    return 0;
  }
  unsafe {
    if (g_stretch_ident_continue[c] != 0) {
      return 1;
    }
  }
  return 0;
}

/**
 * collect_imports bind-name audit: the const bind of `bind = import ...`
 * must be a valid identifier (first ident_start, rest ident_continue).
 * @param name *u8 — bind name bytes
 * @param len i32 — name length; <= 0 or > 63 fails
 * @return i32 — 1 valid ident; 0 invalid
 * PLATFORM: SHARED.
 */
export function parser_asm_stretch_bind_name_validate_c(name: *u8, len: i32): i32 {
  let i: i32 = 0;
  let c0: u8 = 0;
  if (name == 0 as *u8 || len <= 0 || len > 63) {
    return 0;
  }
  unsafe { c0 = name[0]; }
  if (parser_asm_stretch_ident_byte_ok_c(c0, 1) == 0) {
    return 0;
  }
  i = 1;
  while (i < len) {
    let c: u8 = 0;
    unsafe { c = name[i]; }
    if (parser_asm_stretch_ident_byte_ok_c(c, 0) == 0) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}
