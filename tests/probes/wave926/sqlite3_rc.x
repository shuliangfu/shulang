// wave926 (9.2.6) · rc-gated probe: sqlite3 C API via std.db.sqlite
// Standing C rest (same domain as SQLITE_TRANSIENT / sqlite3.h):
//   xlang_sqlite3_*_c live in runtime_sqlite_glue rest because they
//   #include <sqlite3.h>. Thin .x is a TU anchor only. This probe does
//   NOT port sqlite3 — it pins product-path open/exec/query/bind/close
//   against system -lsqlite3. Handles are INTEGER-class 8B structs
//   (DbConn / DbStmt / DbRowCursor { i64 }), same ABI as ArrowColumn.
// Unix $? is 8-bit: case numbers stay in 1..23.
// PLATFORM: SHARED — Darwin + Ubuntu must both hit the real backend
// (is_available==1). Stub backend (no sqlite3.h at glue compile) is fail 1.

const sqlite = import("std.db.sqlite");

/**
 * Product-path sqlite3 C API matrix. Return 0 if every pin matches.
 * @return i32 — 0 all pass, 1..23 the first failing pin (8-bit-safe)
 */
function main(): i32 {
  let mem: u8[9] = [58, 109, 101, 109, 111, 114, 121, 58, 0];
  let sql_create: u8[38] = [
    67, 82, 69, 65, 84, 69, 32, 84, 65, 66, 76, 69, 32, 116, 40, 107,
    32, 73, 78, 84, 69, 71, 69, 82, 44, 32, 110, 97, 109, 101, 32, 84,
    69, 88, 84, 41, 59, 0
  ];
  let sql_ins42: u8[30] = [
    73, 78, 83, 69, 82, 84, 32, 73, 78, 84, 79, 32, 116, 40, 107, 41,
    32, 86, 65, 76, 85, 69, 83, 32, 40, 52, 50, 41, 59, 0
  ];
  let sql_selk: u8[17] = [
    83, 69, 76, 69, 67, 84, 32, 107, 32, 70, 82, 79, 77, 32, 116, 59, 0
  ];
  let sql_ins: u8[35] = [
    73, 78, 83, 69, 82, 84, 32, 73, 78, 84, 79, 32, 116, 40, 107, 44,
    110, 97, 109, 101, 41, 32, 86, 65, 76, 85, 69, 83, 40, 63, 44, 63,
    41, 59, 0
  ];
  let sql_seln: u8[30] = [
    83, 69, 76, 69, 67, 84, 32, 110, 97, 109, 101, 32, 70, 82, 79, 77,
    32, 116, 32, 87, 72, 69, 82, 69, 32, 107, 61, 63, 59, 0
  ];
  let alice: u8[6] = [97, 108, 105, 99, 101, 0];
  let out: u8[16] = [];
  let c: DbConn = { handle: 0 };
  let cur: DbRowCursor = { cursor: 0 };
  let ins: DbStmt = { handle: 0 };
  let sel: DbStmt = { handle: 0 };
  let n: i32 = 0;
  let st: i32 = 0;
  let v: i32 = 0;

  if (sqlite.is_available() != 1) {
    return 1;
  }

  c = sqlite.open(&mem[0]);
  if (c.handle == 0) {
    return 2;
  }
  if (sqlite.exec(c, &sql_create[0]) != 0) {
    sqlite.close(c);
    return 3;
  }
  if (sqlite.exec(c, &sql_ins42[0]) != 0) {
    sqlite.close(c);
    return 4;
  }
  if (sqlite.changes(c) != 1) {
    sqlite.close(c);
    return 5;
  }
  if (sqlite.rows(c, &sql_selk[0]) != 1) {
    sqlite.close(c);
    return 6;
  }

  cur = sqlite.begin(c, &sql_selk[0]);
  if (cur.cursor == 0) {
    sqlite.close(c);
    return 7;
  }
  st = sqlite.next_row(cur);
  if (st != sqlite.DB_ROW_OK) {
    sqlite.end(cur);
    sqlite.close(c);
    return 8;
  }
  v = sqlite.col(cur, 0);
  if (v != 42) {
    sqlite.end(cur);
    sqlite.close(c);
    return 9;
  }
  st = sqlite.next_row(cur);
  if (st != sqlite.DB_ROW_DONE) {
    sqlite.end(cur);
    sqlite.close(c);
    return 10;
  }
  if (sqlite.end(cur) != 0) {
    sqlite.close(c);
    return 11;
  }

  ins = sqlite.prepare(c, &sql_ins[0]);
  if (ins.handle == 0) {
    sqlite.close(c);
    return 12;
  }
  if (sqlite.bind(ins, 1, 10) != 0) {
    sqlite.finalize(ins);
    sqlite.close(c);
    return 13;
  }
  if (sqlite.bind(ins, 2, &alice[0]) != 0) {
    sqlite.finalize(ins);
    sqlite.close(c);
    return 14;
  }
  if (sqlite.step(ins) != 0) {
    sqlite.finalize(ins);
    sqlite.close(c);
    return 15;
  }
  if (sqlite.finalize(ins) != 0) {
    sqlite.close(c);
    return 16;
  }

  sel = sqlite.prepare(c, &sql_seln[0]);
  if (sel.handle == 0) {
    sqlite.close(c);
    return 17;
  }
  if (sqlite.bind(sel, 1, 10) != 0) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 18;
  }
  st = sqlite.step(sel);
  if (st != sqlite.DB_ROW_OK) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 19;
  }
  n = sqlite.col_text(sel, 0, &out[0], 16);
  if (n != 5) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 20;
  }
  if (out[0] != 97) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 21;
  }
  if (out[1] != 108) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 21;
  }
  if (out[2] != 105) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 21;
  }
  if (out[3] != 99) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 21;
  }
  if (out[4] != 101) {
    sqlite.finalize(sel);
    sqlite.close(c);
    return 21;
  }
  if (sqlite.finalize(sel) != 0) {
    sqlite.close(c);
    return 22;
  }
  if (sqlite.close(c) != 0) {
    return 23;
  }
  return 0;
}
