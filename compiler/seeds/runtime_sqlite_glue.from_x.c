/* seeds/runtime_sqlite_glue.from_x.c — G-02f-21 product TU
 * Logic still C until full .x port.
 */
/**
 * runtime_sqlite_glue.c — F-ZC：自 std/db 胶层迁入
 *
 * 从 sqlite.c 迁出 sqlite3 调用；业务逻辑见 std/db/sqlite/sqlite.x。
 * -DXLANG_DB_USE_SQLITE3：真实 libsqlite3；否则 stub（无 sqlite3.h）。
 */

#include <stddef.h>
#include <stdint.h>

/** SQLite 结果码（与 sqlite3.h 一致）。 */
enum {
    XLANG_SQLITE_OK = 0,
    XLANG_SQLITE_ROW = 100,
    XLANG_SQLITE_DONE = 101,
};

#ifdef XLANG_DB_USE_SQLITE3

#include <sqlite3.h>

/** 返回 1 表示已链接 libsqlite3 后端。 */
int32_t xlang_db_use_sqlite3_c(void) {
    return 1;
}

/** sqlite3_open；成功 out_db 写入句柄并返回 XLANG_SQLITE_OK。 */
int32_t xlang_sqlite3_open_c(const uint8_t *path, int64_t *out_db) {
    sqlite3 *db = NULL;
    int rc;
    if (!out_db) {
        return -1;
    }
    *out_db = 0;
    if (!path) {
        return -1;
    }
    rc = sqlite3_open((const char *)path, &db);
    if (rc != SQLITE_OK) {
        if (db) {
            *out_db = (int64_t)(intptr_t)db;
        }
        return rc;
    }
    *out_db = (int64_t)(intptr_t)db;
    return XLANG_SQLITE_OK;
}

/** sqlite3_close；成功返回 XLANG_SQLITE_OK。 */
int32_t xlang_sqlite3_close_c(int64_t db_h) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    if (!db) {
        return -1;
    }
    return sqlite3_close(db);
}

/** sqlite3_exec（无回调）；errmsg 经 out_errmsg 返回，须 xlang_sqlite3_free_c 释放。 */
int32_t xlang_sqlite3_exec_c(int64_t db_h, const uint8_t *sql, int64_t *out_errmsg) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    char *errmsg = NULL;
    int rc;
    if (out_errmsg) {
        *out_errmsg = 0;
    }
    if (!db || !sql) {
        return -1;
    }
    rc = sqlite3_exec(db, (const char *)sql, NULL, NULL, &errmsg);
    if (out_errmsg) {
        *out_errmsg = (int64_t)(intptr_t)errmsg;
    } else if (errmsg) {
        sqlite3_free(errmsg);
    }
    return rc;
}

/** exec 行计数回调：每行 ctx 指向的 i32 加 1。 */
static int xlang_sqlite3_count_cb(void *ctx, int ncol, char **row, char **col) {
    (void)ncol;
    (void)row;
    (void)col;
    if (ctx) {
        (*(int32_t *)ctx) += 1;
    }
    return 0;
}

/** sqlite3_exec + 行计数；out_count 写入匹配行数；errmsg 须 free。 */
int32_t xlang_sqlite3_exec_count_c(int64_t db_h, const uint8_t *sql, int32_t *out_count,
                                 int64_t *out_errmsg) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    char *errmsg = NULL;
    int32_t count = 0;
    int rc;
    if (out_count) {
        *out_count = 0;
    }
    if (out_errmsg) {
        *out_errmsg = 0;
    }
    if (!db || !sql) {
        return -1;
    }
    rc = sqlite3_exec(db, (const char *)sql, xlang_sqlite3_count_cb, &count, &errmsg);
    if (out_count) {
        *out_count = count;
    }
    if (out_errmsg) {
        *out_errmsg = (int64_t)(intptr_t)errmsg;
    } else if (errmsg) {
        sqlite3_free(errmsg);
    }
    return rc;
}

/** sqlite3_prepare_v2；成功 out_stmt 写入语句句柄。 */
int32_t xlang_sqlite3_prepare_v2_c(int64_t db_h, const uint8_t *sql, int64_t *out_stmt) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    sqlite3_stmt *stmt = NULL;
    int rc;
    if (out_stmt) {
        *out_stmt = 0;
    }
    if (!db || !sql) {
        return -1;
    }
    rc = sqlite3_prepare_v2(db, (const char *)sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK && out_stmt) {
        *out_stmt = (int64_t)(intptr_t)stmt;
    }
    return rc;
}

/** sqlite3_step。 */
int32_t xlang_sqlite3_step_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_step(stmt);
}

/** sqlite3_finalize。 */
int32_t xlang_sqlite3_finalize_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_finalize(stmt);
}

/** sqlite3_reset。 */
int32_t xlang_sqlite3_reset_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_reset(stmt);
}

/** sqlite3_clear_bindings。 */
int32_t xlang_sqlite3_clear_bindings_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_clear_bindings(stmt);
}

/** sqlite3_column_count。 */
int32_t xlang_sqlite3_column_count_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return 0;
    }
    return sqlite3_column_count(stmt);
}

/** sqlite3_column_int。 */
int32_t xlang_sqlite3_column_int_c(int64_t stmt_h, int32_t col) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return 0;
    }
    return sqlite3_column_int(stmt, col);
}

/** sqlite3_column_text；返回文本指针（intptr），NULL 列返回 0。 */
int64_t xlang_sqlite3_column_text_c(int64_t stmt_h, int32_t col) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    const unsigned char *txt;
    if (!stmt) {
        return 0;
    }
    txt = sqlite3_column_text(stmt, col);
    return txt ? (int64_t)(intptr_t)txt : 0;
}

/** sqlite3_column_blob；返回 BLOB 指针（intptr）。 */
int64_t xlang_sqlite3_column_blob_c(int64_t stmt_h, int32_t col) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    const void *blob;
    if (!stmt) {
        return 0;
    }
    blob = sqlite3_column_blob(stmt, col);
    return blob ? (int64_t)(intptr_t)blob : 0;
}

/** sqlite3_column_bytes。 */
int32_t xlang_sqlite3_column_bytes_c(int64_t stmt_h, int32_t col) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return 0;
    }
    return (int32_t)sqlite3_column_bytes(stmt, col);
}

/** sqlite3_bind_int（idx 从 1 起）。 */
int32_t xlang_sqlite3_bind_int_c(int64_t stmt_h, int32_t idx, int32_t val) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_bind_int(stmt, idx, val);
}

/* PLATFORM: SHARED — SQLITE_TRANSIENT is a sqlite3.h macro that expands
 * to ((sqlite3_destructor_type)-1). Cap 9.2.6 standing C rest: .x cannot
 * expand that destructor typedef, so bind_text stays here (peer of zlib
 * deflateInit2_impl_c). Do not invent a second destructor constant. */
int32_t xlang_sqlite3_bind_text_c(int64_t stmt_h, int32_t idx, const uint8_t *text) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    if (!stmt) {
        return -1;
    }
    return sqlite3_bind_text(stmt, idx, text ? (const char *)text : NULL, -1, SQLITE_TRANSIENT);
}

/** sqlite3_errmsg；返回 C 串指针（intptr）。 */
int64_t xlang_sqlite3_errmsg_c(int64_t db_h) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    const char *em;
    if (!db) {
        return 0;
    }
    em = sqlite3_errmsg(db);
    return em ? (int64_t)(intptr_t)em : 0;
}

/** sqlite3_db_handle(stmt)；返回 db 指针（intptr）。 */
int64_t xlang_sqlite3_db_handle_c(int64_t stmt_h) {
    sqlite3_stmt *stmt = (sqlite3_stmt *)(intptr_t)stmt_h;
    sqlite3 *db;
    if (!stmt) {
        return 0;
    }
    db = sqlite3_db_handle(stmt);
    return db ? (int64_t)(intptr_t)db : 0;
}

/** sqlite3_changes。 */
int32_t xlang_sqlite3_changes_c(int64_t db_h) {
    sqlite3 *db = (sqlite3 *)(intptr_t)db_h;
    if (!db) {
        return 0;
    }
    return (int32_t)sqlite3_changes(db);
}

/** sqlite3_free。 */
void xlang_sqlite3_free_c(int64_t ptr) {
    if (ptr) {
        sqlite3_free((void *)(intptr_t)ptr);
    }
}

#else /* !XLANG_DB_USE_SQLITE3 */

/** stub 构建：无 libsqlite3。 */
int32_t xlang_db_use_sqlite3_c(void) {
    return 0;
}

int32_t xlang_sqlite3_open_c(const uint8_t *path, int64_t *out_db) {
    (void)path;
    if (out_db) {
        *out_db = 0;
    }
    return -9;
}

int32_t xlang_sqlite3_close_c(int64_t db_h) {
    (void)db_h;
    return -9;
}

int32_t xlang_sqlite3_exec_c(int64_t db_h, const uint8_t *sql, int64_t *out_errmsg) {
    (void)db_h;
    (void)sql;
    if (out_errmsg) {
        *out_errmsg = 0;
    }
    return -9;
}

int32_t xlang_sqlite3_exec_count_c(int64_t db_h, const uint8_t *sql, int32_t *out_count,
                                 int64_t *out_errmsg) {
    (void)db_h;
    (void)sql;
    if (out_count) {
        *out_count = 0;
    }
    if (out_errmsg) {
        *out_errmsg = 0;
    }
    return -9;
}

int32_t xlang_sqlite3_prepare_v2_c(int64_t db_h, const uint8_t *sql, int64_t *out_stmt) {
    (void)db_h;
    (void)sql;
    if (out_stmt) {
        *out_stmt = 0;
    }
    return -9;
}

int32_t xlang_sqlite3_step_c(int64_t stmt_h) {
    (void)stmt_h;
    return -9;
}

int32_t xlang_sqlite3_finalize_c(int64_t stmt_h) {
    (void)stmt_h;
    return -9;
}

int32_t xlang_sqlite3_reset_c(int64_t stmt_h) {
    (void)stmt_h;
    return -9;
}

int32_t xlang_sqlite3_clear_bindings_c(int64_t stmt_h) {
    (void)stmt_h;
    return -9;
}

int32_t xlang_sqlite3_column_count_c(int64_t stmt_h) {
    (void)stmt_h;
    return 0;
}

int32_t xlang_sqlite3_column_int_c(int64_t stmt_h, int32_t col) {
    (void)stmt_h;
    (void)col;
    return 0;
}

int64_t xlang_sqlite3_column_text_c(int64_t stmt_h, int32_t col) {
    (void)stmt_h;
    (void)col;
    return 0;
}

int64_t xlang_sqlite3_column_blob_c(int64_t stmt_h, int32_t col) {
    (void)stmt_h;
    (void)col;
    return 0;
}

int32_t xlang_sqlite3_column_bytes_c(int64_t stmt_h, int32_t col) {
    (void)stmt_h;
    (void)col;
    return 0;
}

int32_t xlang_sqlite3_bind_int_c(int64_t stmt_h, int32_t idx, int32_t val) {
    (void)stmt_h;
    (void)idx;
    (void)val;
    return -9;
}

int32_t xlang_sqlite3_bind_text_c(int64_t stmt_h, int32_t idx, const uint8_t *text) {
    (void)stmt_h;
    (void)idx;
    (void)text;
    return -9;
}

int64_t xlang_sqlite3_errmsg_c(int64_t db_h) {
    (void)db_h;
    return 0;
}

int64_t xlang_sqlite3_db_handle_c(int64_t stmt_h) {
    (void)stmt_h;
    return 0;
}

int32_t xlang_sqlite3_changes_c(int64_t db_h) {
    (void)db_h;
    return 0;
}

void xlang_sqlite3_free_c(int64_t ptr) {
    (void)ptr;
}

#endif /* XLANG_DB_USE_SQLITE3 */
