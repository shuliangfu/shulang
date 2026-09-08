// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// R2 thin of runtime_sqlite_glue: sqlite3 C API TU anchor (Cap 9.2.6).
//
// Architecture (thin + rest):
//   - thin (.x): codegen discovery anchor only. This TU cannot
//     #include <sqlite3.h>, so it does not wrap sqlite3_open / bind /
//     column. Product wrappers live in std/db/sqlite/*.x and call
//     xlang_sqlite3_*_c via extern "C".
//   - rest (seeds/runtime_sqlite_glue.from_x.c): standing C rest.
//     -DXLANG_DB_USE_SQLITE3 includes sqlite3.h and forwards to
//     sqlite3_open / sqlite3_exec / sqlite3_prepare_v2 / sqlite3_step /
//     sqlite3_bind_* / sqlite3_column_* / sqlite3_free. bind_text uses
//     SQLITE_TRANSIENT (a sqlite3.h function-pointer macro, same class
//     as zlib.h deflateInit2). Without the define, rest is a stub that
//     returns DB_NOT_IMPL (-9) so Ubuntu gold still links when
//     libsqlite3-dev is absent.
//
// Why rest stays C (G.7): sqlite3 is an extern system library, not an
// in-tree port. .x cannot expand SQLITE_TRANSIENT or see sqlite3 /
// sqlite3_stmt layouts. Do not add a second scalar / stub authority.
//
// PLATFORM: SHARED — libsqlite3 is portable; glue has no OS branch.
// Product -o appends -lsqlite3 only when glue.o UNDEF sqlite3_open.

// runtime_sqlite_glue_x_doc_anchor: see function docblock below.

/**
 * Codegen discovery anchor for this TU. No sqlite3 calls.
 * @return i32 — always 0
 */
export function runtime_sqlite_glue_x_doc_anchor(): i32 {
  return 0;
}
