#ifndef XLANG_DIAG_H
#define XLANG_DIAG_H

#include <stddef.h>
#include <stdint.h>
#include <xlang_va_cap.h> /* Cap residual 10.7.1: reportf face without <stdarg.h> */
/* Cap residual 9.7.1: print/known-codes faces take the opaque fd-handle stream
 * (xlang_driver_stream_cap.h); .x callers pass *u8 handles. */
#include "xlang_driver_stream_cap.h"

typedef struct DiagContextSnapshot {
    const char *file_path;
    const char *source;
    size_t source_len;
    int use_color;
} DiagContextSnapshot;

void diag_set_file(const char *path, const char *source, size_t source_len);
void diag_push_file(DiagContextSnapshot *snapshot, const char *path, const char *source, size_t source_len);
void diag_restore(const DiagContextSnapshot *snapshot);
const char *diag_get_file(void);
const char *diag_get_source(void);
size_t diag_get_source_len(void);
void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *msg, const char *detail);
void diag_report(const char *file, int line, int col, const char *kind, const char *msg, const char *detail);
void diag_vreportf_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *detail, const char *fmt, xlang_va_list ap);
void diag_vreportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt, xlang_va_list ap);
void diag_reportf_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *detail, const char *fmt, ...);
void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt, ...);
int diag_code_is_known(const char *code);
const char *diag_code_kind(const char *code);
const char *diag_code_summary(const char *code);
const char *diag_code_details(const char *code);
void diag_print_known_codes(uint8_t *out);
void diag_print_code_explain(uint8_t *out, const char *code);
const char *diag_code_suggest(const char *code, char *out, size_t out_cap);
void diag_print_code_table(uint8_t *out);
void diag_set_json_mode(int enable);
int diag_json_enabled(void);

#endif
