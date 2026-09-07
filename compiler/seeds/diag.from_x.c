/* Generated from src/diag.x (G-02f-82 +) (G-02f-30/96/97/98 true .x + C tail; G-02f-74/82 diag gates).
 * G-02f-335～347：PREFER_X_O hybrid 时 pure thin 由 src/diag_thin.x→-E；rest 用
 *   XLANG_L2_DIAG_THIN_FROM_X（省略 public；f-347 push apply_impl / restore 全 thin snap）。
 * G-02f-181: P0-1 close-out — code table + reportf/vreportf 🔒 (priority doc §4.3).
 * G-02f-130 true .x pure helpers.
 * G-02f-116 true .x pure helpers.
 * G-02f-109 helper gates.
 * Regen: ./xlang-c -E -L .. src/diag.x > /tmp/diag.c
 *         merge diag_report from .x; keep code table / va_list / JSON C tail.
 * .x covers: report/human/json/print/code-query/levenshtein/…; C: table data + va_list.
 * Cap residual 10.7.2／9.5.3: reportf formats via xlang_vsnprintf (no libc vsnprintf).
 * Cap residual 10.7.1: Cap va face via xlang_va_cap (no <stdarg.h>).
 */
#include "diag.h"
#ifdef XLANG_L2_DIAG_THIN_FROM_X
#define diag_code_eq diag_code_eq_impl
#define diag_levenshtein_ci diag_levenshtein_ci_impl
#define diag_json_write_str diag_json_write_str_impl
#define diag_json_severity diag_json_severity_impl
#define diag_code_suggest diag_code_suggest_impl
#define diag_report_json diag_report_json_impl
int diag_ctx_get_use_color(void);
int diag_code_table_has(const char *code);
int diag_json_get_state(void);
void diag_json_set_state(int v);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2／9.5.3: reportf → xlang_vsnprintf */
/* Cap residual 9.7.1: diag micro-ABI streams are opaque fd handles. */
#include "xlang_driver_stream_cap.h"

/* ---- 9.7.1 local write helpers over the fd-handle face (PLATFORM: SHARED) ----
 * All diag print sites go through these; formatting uses the Cap fmt authority.
 * Byte-exact replacements for the former fputs/fputc/fprintf/fflush calls. */

/** Decode handle → fd (static wrapper keeps call sites short). */
static int diag_o_fd(uint8_t *o) {
    return xlang_driver_handle_to_fd(o);
}

/** Write exactly n bytes; return 0 on success, -1 on error (fputs contract). */
static int diag_o_write(uint8_t *o, const char *s, size_t n) {
    int fd = diag_o_fd(o);
    if (fd < 0 || (!s && n > 0))
        return -1;
    if (n == 0)
        return 0;
    return xlang_io_write(fd, s, n) == (long)n ? 0 : -1;
}

/** Write NUL-terminated string (fputs twin; NULL writes nothing). */
static int diag_o_puts(uint8_t *o, const char *s) {
    return diag_o_write(o, s, s ? strlen(s) : 0);
}

/** Write one char (fputc twin). */
static int diag_o_putc(uint8_t *o, char c) {
    return diag_o_write(o, &c, 1);
}

/** Formatted write via Cap fmt (fprintf twin; 512B cap — diag lines are short). */
static int diag_o_printf(uint8_t *o, const char *fmt, ...) {
    char buf[512];
    xlang_va_list ap;
    int n;
    xlang_va_start(ap, fmt);
    n = xlang_vsnprintf(buf, sizeof(buf), fmt, ap);
    xlang_va_end(ap);
    if (n < 0)
        return -1;
    return diag_o_write(o, buf, ((size_t)n < sizeof(buf)) ? (size_t)n : sizeof(buf) - 1);
}

/** Std stream handles for direct stderr/stdout sites. */
static uint8_t *diag_h_stderr(void) {
    return xlang_driver_handle_from_fd(2);
}

static uint8_t *diag_h_stdout(void) {
    return xlang_driver_handle_from_fd(1);
}

/* wave233 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — product hybrid diag rest uses same face as diag.x full path. */
extern char *link_abi_getenv(const char *name);

#if !defined(_WIN32)
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#endif

typedef struct DiagContext {
    const char *file_path;
    const char *source;
    size_t source_len;
    int use_color;
} DiagContext;

typedef struct DiagCodeExplain {
    const char *code;
    const char *kind;
    const char *summary;
    const char *details;
} DiagCodeExplain;

static DiagContext g_diag_ctx;

/* JSON 诊断模式：-2 = 尚未决定（按 XLANG_DIAG_JSON 环境变量），1 = 开启，0 = 关闭。 */
static int g_diag_json = -2;

static const DiagCodeExplain g_diag_code_table[] = {
    {"P001", "parse error", "Parser detected invalid syntax or unrecoverable parse failure.",
     "Used for parser-side syntax errors and parser fatal conditions such as out-of-memory. "
     "Typical action: inspect the reported token/statement boundary and surrounding source line."},
    {"T001", "typeck error", "Type checker rejected a construct after successful parse.",
     "Used for regular C-path type checking failures such as mismatched types, invalid assignments, "
     "or non-bool conditions. Typical action: compare inferred and expected types at the caret location."},
    {"ARG001", "usage error", "CLI command or option is missing a required argument.",
     "Used when a command such as `--explain` or another CLI option is present but the required value is "
     "missing. Typical action: re-run with the required operand shown in the usage hint."},
    {"ARG002", "argument error", "CLI argument value is unknown or unsupported.",
     "Used when a user-provided CLI argument cannot be recognized, such as an unknown diagnostic code for "
     "`--explain`. Typical action: inspect the suggested valid values and retry with one of them."},
    {"IO001", "io error", "A file operation failed before the requested compiler step could continue.",
     "Used for common runtime file-operation failures such as open, read, write, rename, or temp-file setup. "
     "Typical action: inspect the path in the diagnostic and verify permissions, existence, and parent directories."},
    {"PRC001", "process error", "A child process or system-level process operation failed.",
     "Used for waitpid, system(), or child-process termination failures in compiler helper paths. "
     "Typical action: inspect the named tool or script and any paired stderr emitted before this summary."},
    {"BLD001", "build error", "An external build or link step failed before producing a usable artifact.",
     "Used for compiler/linker/tool invocations and runtime object build failures summarized at the driver layer. "
     "Typical action: inspect the failing tool name, exit status, and any preceding build stderr."},
    {"PP001", "preprocess error", "Preprocessor found an unclosed conditional directive.",
     "Used when `#if` / `#elseif` / `#else` nesting does not terminate cleanly before end-of-file. "
     "Typical action: inspect nearby conditional compilation directives and ensure every `#if` is closed."},
    {"PP002", "preprocess error", "Preprocessor failed before producing a usable source buffer.",
     "Used for directive errors or generic preprocess failures that are not covered by a more specific code. "
     "Typical action: inspect the reported source file and nearby conditional compilation directives."},
    {"L001", "lexer error", "Lexer found an unclosed block comment.",
     "Used when a nested `/* ... */` block comment reaches end-of-file with nesting depth still greater than zero. "
     "Typical action: add the matching `*/` closers for every true nest-open `/*` (path globs like `src/*.x` do not nest-open)."},
    {"L002", "lexer error", "Lexer found an unclosed string literal.",
     "Used when a double-quoted string reaches end-of-file without a closing quote. "
     "Typical action: add the matching `\"` at the end of the string (multi-line strings are allowed if closed)."},
    {"L003", "lexer error", "Lexer found an illegal character.",
     "Used when a source byte is not a recognized token introducer (for example `$`, bare `'`, or other non-ASCII/punct noise). "
     "Typical action: remove or replace the illegal character; character literals are not part of the product lexical surface."},
    {"L004", "lexer error", "Lexer found an incomplete hex literal.",
     "Used when a hex integer introducer `0x` or `0X` is not followed by at least one hex digit (0-9, a-f, A-F). "
     "Typical action: complete the literal (e.g. `0x0`, `0xFF`) or remove the incomplete `0x` prefix."},
    {"L005", "lexer error", "Lexer found an incomplete float exponent.",
     "Used when a float exponent introducer `e` or `E` (optionally followed by `+` or `-`) is not followed by at least one decimal digit. "
     "Typical action: complete the exponent (e.g. `1e0`, `1.5e+2`) or remove the incomplete exponent suffix."},
    {"L006", "lexer error", "Lexer found an incomplete binary literal.",
     "Used when a binary integer introducer `0b` or `0B` is not followed by at least one binary digit (0 or 1). "
     "Typical action: complete the literal (e.g. `0b0`, `0b1010`) or remove the incomplete `0b` prefix."},
    {"L007", "lexer error", "Lexer found an incomplete octal literal.",
     "Used when an octal integer introducer `0o` or `0O` is not followed by at least one octal digit (0-7). "
     "Typical action: complete the literal (e.g. `0o0`, `0o52`) or remove the incomplete `0o` prefix."},
    {"L008", "lexer error", "Lexer found an invalid digit separator.",
     "Used when `_` appears in a numeric literal without a following valid digit for that radix "
     "(trailing `_`, consecutive `__`, or `_` before a non-digit). "
     "Typical action: remove the underscore or place it only between digits (e.g. `1_000`, `0x2_A`)."},
    {"L009", "lexer error", "Lexer found an invalid type suffix on a numeric literal.",
     "Used when a complete integer or float literal is immediately followed by alphabetic characters "
     "(for example `42u32`, `0x2Ai64`, `1.5f32`, or `42foo`). The language has no C/Rust-style type "
     "suffixes on numerics; use context type coerce (e.g. `let n: u32 = 42`) or `as T`. "
     "Typical action: remove the suffix or rewrite with `as` / annotated `let`."},
    {"L010", "lexer error", "Lexer found an invalid escape sequence in a string literal.",
     "Used when a string escape is not one of the product set `\\n \\t \\r \\0 \\\\ \\\" \\xHH` "
     "(for example `\\q`, incomplete `\\x`, or `\\xG`). "
     "Typical action: use a supported escape or write the byte as `\\xHH`."},
    {"L011", "lexer error", "Lexer found a string literal that exceeds AST storage capacity.",
     "Used when a decoded string literal (including C-style adjacent concatenation) would exceed "
     "127 semantic bytes stored in Expr.var_name. Prior soft residual silently truncated. "
     "Typical action: shorten the literal, split into multiple strings with runtime concat "
     "(std.string), or await a future larger AST string pool."},
    {"L012", "lexer error", "Lexer found an identifier that exceeds AST name storage capacity.",
     "Used when a non-keyword identifier span is longer than 127 bytes (AST name[128] content cap). "
     "Prior soft residual could silent-clamp names or fail with opaque XP003/typeck mismatch. "
     "Typical action: shorten the identifier, or await a future larger AST name layout."},
    {"IMP001", "import error", "Import path could not be opened from the resolved candidate path.",
     "Used when an import target cannot be opened after path resolution. Typical action: verify the import name, "
     "library roots, and the resolved on-disk file path shown in the diagnostic."},
    {"IMP002", "preprocess error", "Imported module failed during preprocessing before parse.",
     "Used when an imported file was found but preprocessing of that import failed. Typical action: inspect the "
     "imported file for conditional-compilation errors such as unclosed directives."},
    {"IMP003", "import error", "Imported module failed to parse after preprocessing.",
     "Used when an import file was read and preprocessed successfully but parse still failed. Typical action: "
     "inspect the imported module with the reported parser diagnostics."},
    {"IMP004", "import error", "Import pipeline failed in a later dependency-resolution stage.",
     "Used for import-side failures such as path normalization limits, unresolved dependency closure, or imported "
     "module type-check failure summaries. Typical action: inspect the paired import diagnostics emitted earlier."},
    {"XP001", "pipeline error", ".x pipeline parse stage failed before building a usable module.",
     "Used when the .x pipeline cannot finish parse/module construction. Typical action: inspect the "
     "preceding parse diagnostics and the failing module entry."},
    {"XP002", "pipeline error", ".x pipeline parse commit failed while committing a parsed function.",
     "Used for stricter .x parse/commit failures after a function was tentatively parsed but could not be "
     "committed into the module. Typical action: inspect nearby function boundaries and parse-recovery logs."},
    {"XP003", "pipeline error", ".x pipeline terminated with a non-zero runtime status code.",
     "Used for generic .x pipeline summary failures reported as `pipeline failed rc=...` after a deeper stage "
     "returned an error code. Typical action: inspect preceding parser/typeck/import/codegen diagnostics."},
    {"XP004", "pipeline error", ".x pipeline path resolution trace for a failed import or entry lookup.",
     "Used for the follow-up `resolve path tried:` diagnostic that lists the concrete path attempted before "
     "pipeline failure. Typical action: inspect the shown path and verify library roots and import naming."},
    {"XP005", "pipeline error", ".x pipeline failed while allocating required runtime structures.",
     "Used for allocation failures covering arena/module buffers, ELF context, or dependency-side arena/module "
     "storage before the pipeline can proceed. Typical action: inspect memory pressure and the specific pipeline stage."},
    {"XP006", "pipeline error", ".x pipeline failed while allocating output or dependency context state.",
     "Used when `CodegenOutBuf`, `PipelineDepCtx`, or dependency-local output/context buffers cannot be allocated. "
     "Typical action: inspect memory pressure and whether a large-output path is being exercised."},
    {"XP007", "pipeline error", ".x pipeline refused an input buffer that exceeds parser size limits.",
     "Used for `source too large for parser` failures when the source buffer exceeds the current `int32_t` parser "
     "boundary. Typical action: reduce input size or change the parser limit handling."},
    {"XP008", "pipeline error", ".x dependency sub-pipeline failed while prerunning an imported module.",
     "Used for `pipeline failed for import` summaries emitted after a dependency prerun returns non-zero. "
     "Typical action: inspect earlier diagnostics for the referenced import path and its transitive dependencies."},
    {"XT001", "typeck error", ".x pipeline type checking failed for a specific function.",
     "Used when .x type checking fails inside a concrete function, often with function index/name attached. "
     "Typical action: inspect the named function body and any accompanying type diagnostics."},
    {"CG001", "codegen error", "Code generation could not emit C output because no main entry was available.",
     "Used when executable-oriented C emission requires a `main` function but the module only contains library "
     "items or no callable entry. Typical action: add a `main` entry or switch to a library/module emission path."},
    {"CG002", "codegen error", "ASM object emission failed before producing a usable .o payload.",
     "Used for `asm_codegen_elf_o failed` summaries where the backend or ELF writer returned a failing status or "
     "produced an empty object buffer. Typical action: inspect paired ELF context notes and earlier backend diagnostics."},
    {"CG003", "codegen error", "Code generator failed while emitting a specific function body.",
     "Used for `failed to emit function` summaries tied to a concrete function name or index. Typical action: "
     "inspect that function body and any preceding backend/type diagnostics for unsupported constructs."},
    {"CG004", "codegen error", "Code generation produced an empty output buffer after a non-failing pipeline.",
     "Used when the C-path `.x -E` pipeline returns success but the codegen output buffer is empty, indicating a "
     "codegen/pipeline wiring gap rather than a reported typeck/codegen error. Typical action: inspect the CodegenOutBuf "
     "wiring and any earlier typeck/codegen diagnostics."},
    {"CHK001", "check error", "`xlang check` failed without a more specific structured diagnostic.",
     "Fallback check-mode code used when compilation/check failed but no detailed parser/typeck/import "
     "diagnostic was emitted. Typical action: inspect prior stderr output and the target file path."},
    {"CHK002", "check error", "`xlang check` found no .x files to inspect.",
     "Used when the provided path set, or the current directory, contains no discoverable .x sources. "
     "Typical action: verify input paths and whether ignored filters removed all candidates."},
    {"FMT001", "fmt error", "`xlang fmt` failed or found no format candidates.",
     "Used for format-mode failures such as missing input files, unreadable files, or no .x files found. "
     "Typical action: verify the path list, file accessibility, and whether `--check` reported unformatted files."},
    {"SMOKE001", "info", "Parse-stage smoke summary: source parsed successfully.",
     "Emitted as an info-level smoke marker after a successful parse/typeck pass on the no-`-o` smoke path. "
     "Only emitted when structured smoke output is opted in (`--diag-json` or `XLANG_SMOKE_DIAG=1`); the legacy "
     "`parse OK` stdout line remains for grep/golden compatibility. Typical action: none (success marker)."},
    {"SMOKE002", "info", "Typeck-stage smoke summary: type checking passed.",
     "Emitted as an info-level smoke marker after type checking succeeds on the no-`-o` smoke path. "
     "Only emitted when structured smoke output is opted in (`--diag-json` or `XLANG_SMOKE_DIAG=1`); the legacy "
     "`typeck OK` stdout line remains for grep/golden compatibility. Typical action: none (success marker)."},
};
static const size_t g_diag_code_table_count = sizeof(g_diag_code_table) / sizeof(g_diag_code_table[0]);

/* G-02f-153：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_should_color(void)
#else
int diag_should_color_impl(void)
#endif
{
#if defined(_WIN32)
    /* PLATFORM: WINDOWS — no ANSI color path for host stderr in this twin. */
    return 0;
#else
    /* wave233 G.7: XLANG_NO_COLOR via link_abi_getenv (not raw getenv). */
    if (link_abi_getenv("XLANG_NO_COLOR"))
        return 0;
    /* 9.7.1: fd 2 directly — no stderr FILE* needed for isatty. */
    return isatty(2) ? 1 : 0;
#endif
}


/** 供 .x 读 g_diag_ctx.use_color（G-02f-154）。 */
/* G-02f-386：实现体始终 seed；public PREFER 时 thin forward */
int diag_ctx_get_use_color_impl(void) {
    return g_diag_ctx.use_color ? 1 : 0;
}

#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_ctx_get_use_color(void) {
    return diag_ctx_get_use_color_impl();
}
#endif

/* G-02f-154：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-335：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char * diag_color_prefix(const char *plain, const char *color) {
    return g_diag_ctx.use_color ? color : plain;
}
#else
extern const char *diag_color_prefix(const char *plain, const char *color);
#endif

/* G-02f-154：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char * diag_color_reset(void)
#else
const char * diag_color_reset_impl(void)
#endif
{
    return g_diag_ctx.use_color ? "\x1b[0m" : "";
}
/* G-02f-116：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_code_eq(const char *lhs, const char *rhs)
#else
int diag_code_eq_impl(const char *lhs, const char *rhs)
#endif
{
  size_t i;
  if (!lhs || !rhs)
    return 0;
  for (i = 0; lhs[i] && rhs[i]; i++) {
    unsigned char a = (unsigned char)lhs[i];
    unsigned char b = (unsigned char)rhs[i];
    if (a >= 'a' && a <= 'z')
      a = (unsigned char)(a - 'a' + 'A');
    if (b >= 'a' && b <= 'z')
      b = (unsigned char)(b - 'a' + 'A');
    if (a != b)
      return 0;
  }
  return lhs[i] == '\0' && rhs[i] == '\0' ? 1 : 0;
}



static const DiagCodeExplain *diag_lookup_code_explain(const char *code) {
    size_t i;
    if (!code || code[0] == '\0')
        return NULL;
    for (i = 0; i < g_diag_code_table_count; i++) {
        if (diag_code_eq(g_diag_code_table[i].code, code))
            return &g_diag_code_table[i];
    }
    return NULL;
}

typedef struct DiagPalette {
    const char *kind_color;
    const char *caret_color;
} DiagPalette;
/* G-02f-116：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-335：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_kind_is_exact(const char *kind, const char *needle) {
  if (!kind || !needle)
    return 0;
  return strcmp(kind, needle) == 0 ? 1 : 0;
}
#else
extern int diag_kind_is_exact(const char *kind, const char *needle);
#endif

/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-335：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_kind_contains(const char *kind, const char *needle) {
    if (!kind || !needle || needle[0] == '\0')
        return 0;
    return strstr(kind, needle) != NULL ? 1 : 0;
}
#else
extern int diag_kind_contains(const char *kind, const char *needle);
#endif


static DiagPalette diag_palette_for_kind(const char *kind) {
    DiagPalette pal;
    pal.kind_color = diag_color_prefix("", "\x1b[1;37m");
    pal.caret_color = diag_color_prefix("", "\x1b[37m");
    if (!kind || kind[0] == '\0')
        return pal;
    if (diag_kind_contains(kind, "error")) {
        pal.kind_color = diag_color_prefix("", "\x1b[1;31m");
        pal.caret_color = diag_color_prefix("", "\x1b[31m");
        return pal;
    }
    if (diag_kind_contains(kind, "warning")) {
        pal.kind_color = diag_color_prefix("", "\x1b[1;33m");
        pal.caret_color = diag_color_prefix("", "\x1b[33m");
        return pal;
    }
    if (diag_kind_is_exact(kind, "info")) {
        pal.kind_color = diag_color_prefix("", "\x1b[1;36m");
        pal.caret_color = diag_color_prefix("", "\x1b[36m");
        return pal;
    }
    if (diag_kind_is_exact(kind, "note")) {
        pal.kind_color = diag_color_prefix("", "\x1b[1;34m");
        pal.caret_color = diag_color_prefix("", "\x1b[34m");
        return pal;
    }
    if (diag_kind_is_exact(kind, "help") || diag_kind_is_exact(kind, "hint")) {
        pal.kind_color = diag_color_prefix("", "\x1b[1;32m");
        pal.caret_color = diag_color_prefix("", "\x1b[32m");
        return pal;
    }
    return pal;
}

/** 供 .x stdio 冷路径（G-02f-156）。9.7.1: stream params are opaque fd handles. */
/* G-02f-421：实现体始终 seed；public PREFER 时 thin pure forward */
uint8_t *diag_stderr_impl(void) { return diag_h_stderr(); }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
uint8_t *diag_stderr(void) { return diag_stderr_impl(); }
#endif
/* G-02f-415：实现体始终 seed（stdio/fmt）；public PREFER 时 thin pure forward */
int diag_io_fputc_impl(uint8_t *o, int c) { return diag_o_putc(o, (char)c); }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_io_fputc(uint8_t *o, int c) { return diag_io_fputc_impl(o, c); }
#endif
int diag_io_fputs_impl(const char *s, uint8_t *o) { return diag_o_puts(o, s ? s : ""); }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_io_fputs(const char *s, uint8_t *o) { return diag_io_fputs_impl(s, o); }
#endif
void diag_io_fputs_u04x_impl(uint8_t *o, unsigned c) { diag_o_printf(o, "\\u%04x", c); }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fputs_u04x(uint8_t *o, unsigned c) { diag_io_fputs_u04x_impl(o, c); }
#endif
void diag_io_fflush_impl(uint8_t *o) { (void)o; /* raw fd writes are unbuffered */ }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fflush(uint8_t *o) { diag_io_fflush_impl(o); }
#endif
void diag_io_fprint_line_col_impl(uint8_t *o, int line, int col) {
    diag_o_printf(o, ",\"line\":%d,\"col\":%d,\"message\":", line, col);
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_line_col(uint8_t *o, int line, int col) {
    diag_io_fprint_line_col_impl(o, line, col);
}
#endif
/** 供 .x report_human 位置/gutter 冷路径（G-02f-159）。 */
void diag_io_fprint_loc_file_line_col_impl(uint8_t *o, const char *pc, const char *file, int line, int col, const char *rs) {
    diag_o_printf(o, "%s --> %s:%d:%d%s\n", pc ? pc : "", file ? file : "", line, col, rs ? rs : "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_loc_file_line_col(uint8_t *o, const char *pc, const char *file, int line, int col, const char *rs) {
    diag_io_fprint_loc_file_line_col_impl(o, pc, file, line, col, rs);
}
#endif
void diag_io_fprint_loc_file_line_impl(uint8_t *o, const char *pc, const char *file, int line, const char *rs) {
    diag_o_printf(o, "%s --> %s:%d%s\n", pc ? pc : "", file ? file : "", line, rs ? rs : "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_loc_file_line(uint8_t *o, const char *pc, const char *file, int line, const char *rs) {
    diag_io_fprint_loc_file_line_impl(o, pc, file, line, rs);
}
#endif
void diag_io_fprint_loc_file_impl(uint8_t *o, const char *pc, const char *file, const char *rs) {
    diag_o_printf(o, "%s --> %s%s\n", pc ? pc : "", file ? file : "", rs ? rs : "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_loc_file(uint8_t *o, const char *pc, const char *file, const char *rs) {
    diag_io_fprint_loc_file_impl(o, pc, file, rs);
}
#endif
void diag_io_fprint_loc_line_col_impl(uint8_t *o, const char *pc, int line, int col, const char *rs) {
    diag_o_printf(o, "%s --> %d:%d%s\n", pc ? pc : "", line, col, rs ? rs : "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_loc_line_col(uint8_t *o, const char *pc, int line, int col, const char *rs) {
    diag_io_fprint_loc_line_col_impl(o, pc, line, col, rs);
}
#endif
void diag_io_fprint_gutter_blank_impl(uint8_t *o, int width) {
    diag_o_printf(o, "%*s |\n", width, "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_gutter_blank(uint8_t *o, int width) {
    diag_io_fprint_gutter_blank_impl(o, width);
}
#endif
void diag_io_fprint_src_line_impl(uint8_t *o, int line, const char *start, int len) {
    /* Three-part write keeps arbitrary-length source lines intact (no 512 cap). */
    if (diag_o_printf(o, "%d | ", line) != 0)
        return;
    if (start && len > 0 && diag_o_write(o, start, (size_t)len) != 0)
        return;
    diag_o_puts(o, "\n");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_src_line(uint8_t *o, int line, const char *start, int len) {
    diag_io_fprint_src_line_impl(o, line, start, len);
}
#endif
void diag_io_fprint_gutter_bar_impl(uint8_t *o, int width) {
    diag_o_printf(o, "%*s | ", width, "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_gutter_bar(uint8_t *o, int width) {
    diag_io_fprint_gutter_bar_impl(o, width);
}
#endif
void diag_io_fprint_caret_mark_impl(uint8_t *o, const char *cc, const char *rs, const char *detail) {
    diag_o_printf(o, "%s^%s", cc ? cc : "", rs ? rs : "");
    if (detail && detail[0] != '\0')
        diag_o_printf(o, " %s", detail);
    diag_o_putc(o, '\n');
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_caret_mark(uint8_t *o, const char *cc, const char *rs, const char *detail) {
    diag_io_fprint_caret_mark_impl(o, cc, rs, detail);
}
#endif

/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_print_header(const char *kind, const char *code, const char *msg,
                              const char *kind_color, const char *reset)
#else
void diag_print_header_impl(const char *kind, const char *code, const char *msg,
                              const char *kind_color, const char *reset)
#endif
{
    if (!msg)
        msg = "";
    if (!kind)
        kind = "";
    if (!kind_color)
        kind_color = "";
    if (!reset)
        reset = "";
    if (kind[0] == '\0') {
        diag_o_printf(diag_h_stderr(), "%s\n", msg);
        return;
    }
    if (code && code[0] != '\0')
        diag_o_printf(diag_h_stderr(), "%s%s[%s]%s: %s\n", kind_color, kind, code, reset, msg);
    else
        diag_o_printf(diag_h_stderr(), "%s%s%s: %s\n", kind_color, kind, reset, msg);
}
/* G-02f-116：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-335：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_line_digits(int line) {
  int width = 1;
  while (line >= 10) {
    line /= 10;
    width++;
  }
  return width;
}
#else
extern int diag_line_digits(int line);
#endif

/* G-02f-154：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_extract_line(int line_no, const char **line_start_out, size_t *line_len_out)
#else
int diag_extract_line_impl(int line_no, const char **line_start_out, size_t *line_len_out)
#endif
{
    const char *src = g_diag_ctx.source;
    size_t len = g_diag_ctx.source_len;
    int line = 1;
    size_t i;
    size_t start = 0;

    if (!src || !line_start_out || !line_len_out || line_no <= 0)
        return -1;
    for (i = 0; i < len; i++) {
        if (line == line_no)
            break;
        if (src[i] == '\n') {
            line++;
            start = i + 1;
        }
    }
    if (line != line_no)
        return -1;
    for (; i < len && src[i] != '\n' && src[i] != '\r'; i++) {
    }
    *line_start_out = src + start;
    *line_len_out = i - start;
    return 0;
}


/** 供 .x 写 g_diag_ctx（G-02f-156）。 */
/* G-02f-420：实现体始终 seed；public PREFER 时 thin pure forward */
void diag_ctx_set_all_impl(const char *path, const char *source, size_t source_len, int use_color) {
    g_diag_ctx.file_path = path;
    g_diag_ctx.source = source;
    g_diag_ctx.source_len = source_len;
    g_diag_ctx.use_color = use_color;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_ctx_set_all(const char *path, const char *source, size_t source_len, int use_color) {
    diag_ctx_set_all_impl(path, source, source_len, use_color);
}
#endif

/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-336：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_set_file(const char *path, const char *source, size_t source_len) {
    g_diag_ctx.file_path = path;
    g_diag_ctx.source = source;
    g_diag_ctx.source_len = source_len;
    g_diag_ctx.use_color = diag_should_color();
}
#else
extern void diag_set_file(const char *path, const char *source, size_t source_len);
#endif

/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-337/347：hybrid 时 push = thin snap_save + apply_impl；restore = thin snap_load */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_push_file(DiagContextSnapshot *snapshot, const char *path, const char *source, size_t source_len)
{
    if (snapshot) {
        snapshot->file_path = g_diag_ctx.file_path;
        snapshot->source = g_diag_ctx.source;
        snapshot->source_len = g_diag_ctx.source_len;
        snapshot->use_color = g_diag_ctx.use_color;
    }
    g_diag_ctx.file_path = path ? path : g_diag_ctx.file_path;
    g_diag_ctx.source = source ? source : g_diag_ctx.source;
    g_diag_ctx.source_len = source ? source_len : g_diag_ctx.source_len;
    g_diag_ctx.use_color = diag_should_color();
}
#else
/* thin 负责 snapshot 字节布局；此处仅写 g_diag_ctx（path/source 三元） */
void diag_push_file_apply_impl(const char *path, const char *source, size_t source_len)
{
    g_diag_ctx.file_path = path ? path : g_diag_ctx.file_path;
    g_diag_ctx.source = source ? source : g_diag_ctx.source;
    g_diag_ctx.source_len = source ? source_len : g_diag_ctx.source_len;
    g_diag_ctx.use_color = diag_should_color_impl();
}
#endif

/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-347：hybrid 时 restore 全由 thin snap_load + diag_ctx_set_all */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_restore(const DiagContextSnapshot *snapshot)
{
    if (!snapshot)
        return;
    g_diag_ctx.file_path = snapshot->file_path;
    g_diag_ctx.source = snapshot->source;
    g_diag_ctx.source_len = snapshot->source_len;
    g_diag_ctx.use_color = snapshot->use_color;
}
#endif


/** 供 .x 读 g_diag_ctx 字段（G-02f-155）。 */
/* G-02f-420：实现体始终 seed；public PREFER 时 thin pure forward */
const char *diag_ctx_get_file_impl(void) {
    return g_diag_ctx.file_path;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_ctx_get_file(void) {
    return diag_ctx_get_file_impl();
}
#endif
const char *diag_ctx_get_source_impl(void) {
    return g_diag_ctx.source;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_ctx_get_source(void) {
    return diag_ctx_get_source_impl();
}
#endif
size_t diag_ctx_get_source_len_impl(void) {
    return g_diag_ctx.source_len;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
size_t diag_ctx_get_source_len(void) {
    return diag_ctx_get_source_len_impl();
}
#endif

/* G-02f-155：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-336：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_get_file(void) {
    return g_diag_ctx.file_path;
}

const char *diag_get_source(void) {
    return g_diag_ctx.source;
}

size_t diag_get_source_len(void) {
    return g_diag_ctx.source_len;
}
#else
extern const char *diag_get_file(void);
extern const char *diag_get_source(void);
extern size_t diag_get_source_len(void);
#endif

void diag_report_json(const char *file, int line, int col,
                             const char *kind, const char *code, const char *msg);

/* G-02f-159：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_report_human(const char *file, int line, int col, const char *kind, const char *code, const char *msg, const char *detail)
#else
void diag_report_human_impl(const char *file, int line, int col, const char *kind, const char *code, const char *msg, const char *detail)
#endif
{
    const char *actual_file = file ? file : g_diag_ctx.file_path;
    const char *line_start = NULL;
    size_t line_len = 0;
    int have_line = 0;
    int width = 1;
    int caret_col;
    int i;
    DiagPalette pal = diag_palette_for_kind(kind);
    const char *kind_color = pal.kind_color;
    const char *path_color = diag_color_prefix("", "\x1b[34m");
    const char *caret_color = pal.caret_color;
#ifdef XLANG_L2_DIAG_THIN_FROM_X
    const char *reset = diag_color_reset_impl();
#else
    const char *reset = diag_color_reset();
#endif

#ifdef XLANG_L2_DIAG_THIN_FROM_X
    if (line > 0 && diag_extract_line_impl(line, &line_start, &line_len) == 0)
#else
    if (line > 0 && diag_extract_line(line, &line_start, &line_len) == 0)
#endif
        have_line = 1;

#ifdef XLANG_L2_DIAG_THIN_FROM_X
    diag_print_header_impl(kind, code, msg, kind_color, reset);
#else
    diag_print_header(kind, code, msg, kind_color, reset);
#endif

    /* wave1221: always print line:col even when 0, so typeck errors without
     * expr line/col still show file:0:0 instead of bare file path.
     * This makes check output consistent and helps locate errors. */
    if (actual_file) {
        diag_o_printf(diag_h_stderr(), "%s --> %s:%d:%d%s\n", path_color, actual_file, line, col, reset);
    } else if (line > 0 || col > 0) {
        diag_o_printf(diag_h_stderr(), "%s --> %d:%d%s\n", path_color, line, col, reset);
    }

    if (!have_line || line <= 0 || col <= 0) {
        return; /* raw fd 2 writes are unbuffered — no flush needed (9.7.1) */
    }

    width = diag_line_digits(line);
    diag_o_printf(diag_h_stderr(), "%*s |\n", width, "");
    /* Single formatted write; %.*s keeps the slice bounded by line_len. */
    diag_o_printf(diag_h_stderr(), "%d | %.*s\n", line, (int)line_len, line_start);
    diag_o_printf(diag_h_stderr(), "%*s | ", width, "");

    caret_col = col > 1 ? col - 1 : 0;
    for (i = 0; i < caret_col; i++) {
        if ((size_t)i < line_len && line_start[i] == '\t')
            diag_o_putc(diag_h_stderr(), '\t');
        else
            diag_o_putc(diag_h_stderr(), ' ');
    }
    diag_o_printf(diag_h_stderr(), "%s^%s", caret_color, reset);
    if (detail && detail[0] != '\0')
        diag_o_printf(diag_h_stderr(), " %s", detail);
    diag_o_putc(diag_h_stderr(), '\n');
}

/* G-02f-158：逻辑源 .x（JSON 分流真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl（可再调 thin public 或 _impl） */
#ifdef XLANG_L2_DIAG_THIN_FROM_X
int diag_json_enabled_impl(void); /* defined later in this TU */
#endif
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *msg, const char *detail)
#else
void diag_report_with_code_impl(const char *file, int line, int col, const char *kind, const char *code, const char *msg, const char *detail)
#endif
{
    const char *actual_file = file ? file : g_diag_ctx.file_path;
#ifdef XLANG_L2_DIAG_THIN_FROM_X
    if (diag_json_enabled_impl()) {
        diag_report_json(actual_file, line, col, kind, code, msg);
        return;
    }
    diag_report_human_impl(file, line, col, kind, code, msg, detail);
#else
    if (diag_json_enabled()) {
        diag_report_json(actual_file, line, col, kind, code, msg);
        return;
    }
    diag_report_human(file, line, col, kind, code, msg, detail);
#endif
}

/* G-02f-158：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-336：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_report(const char *file, int line, int col, const char *kind, const char *msg, const char *detail) {
    diag_report_with_code(file, line, col, kind, NULL, msg, detail);
}
#else
extern void diag_report(const char *file, int line, int col, const char *kind, const char *msg, const char *detail);
#endif

void diag_vreportf_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *detail, const char *fmt, xlang_va_list ap) {
    char buf[1024];

    if (!fmt)
        fmt = "";
    /* PLATFORM: SHARED — Cap fmt (10.7.2) + Cap va (10.7.1); no libc stdarg/vsnprintf. */
    (void)xlang_vsnprintf(buf, sizeof(buf), fmt, ap);
    diag_report_with_code(file, line, col, kind, code, buf, detail ? detail : buf);
}

void diag_vreportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt, xlang_va_list ap) {
    diag_vreportf_with_code(file, line, col, kind, NULL, detail, fmt, ap);
}



void diag_reportf_with_code(const char *file, int line, int col, const char *kind, const char *code, const char *detail, const char *fmt, ...) {
    xlang_va_list ap;

    xlang_va_start(ap, fmt);
    diag_vreportf_with_code(file, line, col, kind, code, detail, fmt, ap);
    xlang_va_end(ap);
}





void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt, ...) {
    xlang_va_list ap;

    xlang_va_start(ap, fmt);
    diag_vreportf_with_code(file, line, col, kind, NULL, detail, fmt, ap);
    xlang_va_end(ap);
}



/** 供 .x 查 code 表是否存在（G-02f-155）。 */
/* G-02f-386：实现体始终 seed；public PREFER 时 thin forward */
int diag_code_table_has_impl(const char *code) {
    return diag_lookup_code_explain(code) ? 1 : 0;
}

#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_code_table_has(const char *code) {
    return diag_code_table_has_impl(code);
}
#endif

/* G-02f-155：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-336：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_code_is_known(const char *code) {
    return diag_lookup_code_explain(code) ? 1 : 0;
}
#else
extern int diag_code_is_known(const char *code);
#endif


/** 供 .x 遍历 / 查询 code 表（G-02f-157）。 */
/* G-02f-415：实现体始终 seed；public PREFER 时 thin pure forward */
size_t diag_code_table_len_impl(void) {
    return g_diag_code_table_count;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
size_t diag_code_table_len(void) {
    return diag_code_table_len_impl();
}
#endif
/* G-02f-421：实现体始终 seed；public PREFER 时 thin pure forward */
const char *diag_code_table_code_at_impl(size_t i) {
    if (i >= g_diag_code_table_count)
        return NULL;
    return g_diag_code_table[i].code;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_code_table_code_at(size_t i) {
    return diag_code_table_code_at_impl(i);
}
#endif
const char *diag_code_table_kind_at_impl(size_t i) {
    if (i >= g_diag_code_table_count)
        return NULL;
    return g_diag_code_table[i].kind;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_code_table_kind_at(size_t i) {
    return diag_code_table_kind_at_impl(i);
}
#endif
const char *diag_code_table_summary_at_impl(size_t i) {
    if (i >= g_diag_code_table_count)
        return NULL;
    return g_diag_code_table[i].summary;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_code_table_summary_at(size_t i) {
    return diag_code_table_summary_at_impl(i);
}
#endif
const char *diag_code_table_details_at_impl(size_t i) {
    if (i >= g_diag_code_table_count)
        return NULL;
    return g_diag_code_table[i].details;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_code_table_details_at(size_t i) {
    return diag_code_table_details_at_impl(i);
}
#endif
const char *diag_entry_code_impl(const char *code) {
    const DiagCodeExplain *e = diag_lookup_code_explain(code);
    return e ? e->code : NULL;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_entry_code(const char *code) {
    return diag_entry_code_impl(code);
}
#endif
const char *diag_entry_kind_impl(const char *code) {
    const DiagCodeExplain *e = diag_lookup_code_explain(code);
    return e ? e->kind : NULL;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_entry_kind(const char *code) {
    return diag_entry_kind_impl(code);
}
#endif
const char *diag_entry_summary_impl(const char *code) {
    const DiagCodeExplain *e = diag_lookup_code_explain(code);
    return e ? e->summary : NULL;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_entry_summary(const char *code) {
    return diag_entry_summary_impl(code);
}
#endif
const char *diag_entry_details_impl(const char *code) {
    const DiagCodeExplain *e = diag_lookup_code_explain(code);
    return e ? e->details : NULL;
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_entry_details(const char *code) {
    return diag_entry_details_impl(code);
}
#endif
uint8_t *diag_stdout_impl(void) { return diag_h_stdout(); }
#ifndef XLANG_L2_DIAG_THIN_FROM_X
uint8_t *diag_stdout(void) { return diag_stdout_impl(); }
#endif
/* G-02f-415：code table io → seed impl + thin pure forward (9.7.1 fd handles) */
void diag_io_fprint_unknown_code_impl(uint8_t *out, const char *code) {
    diag_o_printf(out, "Unknown diagnostic code: %s\n", code ? code : "(null)");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_unknown_code(uint8_t *out, const char *code) {
    diag_io_fprint_unknown_code_impl(out, code);
}
#endif
void diag_io_fprint_code_table_hdr_impl(uint8_t *out) {
    diag_o_printf(out, "%-8s %-18s %s\n", "CODE", "KIND", "SUMMARY");
    diag_o_printf(out, "%-8s %-18s %s\n", "----", "----", "-------");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_code_table_hdr(uint8_t *out) {
    diag_io_fprint_code_table_hdr_impl(out);
}
#endif
void diag_io_fprint_code_table_row_impl(uint8_t *out, const char *code, const char *kind, const char *summary) {
    diag_o_printf(out, "%-8s %-18s %s\n", code ? code : "", kind ? kind : "", summary ? summary : "");
}
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_io_fprint_code_table_row(uint8_t *out, const char *code, const char *kind, const char *summary) {
    diag_io_fprint_code_table_row_impl(out, code, kind, summary);
}
#endif

/* G-02f-157：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-336：hybrid 时由 diag_thin.x 提供 */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char *diag_code_kind(const char *code) {
    const DiagCodeExplain *entry = diag_lookup_code_explain(code);
    return entry ? entry->kind : NULL;
}

const char *diag_code_summary(const char *code) {
    const DiagCodeExplain *entry = diag_lookup_code_explain(code);
    return entry ? entry->summary : NULL;
}

const char *diag_code_details(const char *code) {
    const DiagCodeExplain *entry = diag_lookup_code_explain(code);
    return entry ? entry->details : NULL;
}
#else
extern const char *diag_code_kind(const char *code);
extern const char *diag_code_summary(const char *code);
extern const char *diag_code_details(const char *code);
#endif

/* G-02f-157：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_print_known_codes(uint8_t *out)
#else
void diag_print_known_codes_impl(uint8_t *out)
#endif
{
    size_t i;
    if (!out)
        out = diag_h_stdout();
    for (i = 0; i < g_diag_code_table_count; i++)
        diag_o_printf(out, "%s%s", i == 0 ? "" : ", ", g_diag_code_table[i].code);
    diag_o_putc(out, '\n');
}

/* G-02f-157：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_print_code_explain(uint8_t *out, const char *code)
#else
void diag_print_code_explain_impl(uint8_t *out, const char *code)
#endif
{
    const DiagCodeExplain *entry;
    if (!out)
        out = diag_h_stdout();
    entry = diag_lookup_code_explain(code);
    if (!entry) {
        diag_o_printf(out, "Unknown diagnostic code: %s\n", code ? code : "(null)");
        diag_o_puts(out, "Known codes: ");
#ifdef XLANG_L2_DIAG_THIN_FROM_X
        diag_print_known_codes_impl(out);
#else
        diag_print_known_codes(out);
#endif
        return;
    }
    diag_o_printf(out, "%s\n", entry->code);
    diag_o_printf(out, "Kind: %s\n", entry->kind);
    diag_o_printf(out, "Summary: %s\n", entry->summary);
    diag_o_printf(out, "Details: %s\n", entry->details);
}


/**
 * 有界 Levenshtein 编辑距离（大小写不敏感）。
 * 仅用于诊断码建议（码长度很短，O(n*m) 可接受；仅在 --explain 未知码冷路径调用）。
 * max_dist 为上界：一旦当前行最小值超过 max_dist 即可提前判定超过（这里为简洁用完整 DP，码短无妨）。
 * 返回将 a 变换为 b 的最小单字符编辑（插入/删除/替换）次数。
 * G-02f-98：export gate.
 */
/* G-02f-152 / G-02f-158：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_levenshtein_ci(const char *a, const char *b)
#else
int diag_levenshtein_ci_impl(const char *a, const char *b)
#endif
{
    size_t la = a ? strlen(a) : 0;
    size_t lb = b ? strlen(b) : 0;
    size_t i, j;
    int prev[64];
    int cur[64];

    if (!a || !b)
        return 999;
    if (la >= 64 || lb >= 64)
        return 999;
    if (la == 0)
        return (int)lb;
    if (lb == 0)
        return (int)la;

    for (j = 0; j <= lb; j++)
        prev[j] = (int)j;
    for (i = 1; i <= la; i++) {
        cur[0] = (int)i;
        for (j = 1; j <= lb; j++) {
            unsigned char ca = (unsigned char)a[i - 1];
            unsigned char cb = (unsigned char)b[j - 1];
            int cost;
            if (ca >= 'a' && ca <= 'z')
                ca = (unsigned char)(ca - 'a' + 'A');
            if (cb >= 'a' && cb <= 'z')
                cb = (unsigned char)(cb - 'a' + 'A');
            cost = (ca == cb) ? 0 : 1;
            {
                int del = prev[j] + 1;      /* 删除 */
                int ins = cur[j - 1] + 1;   /* 插入 */
                int sub = prev[j - 1] + cost; /* 替换 */
                int m = del < ins ? del : ins;
                if (sub < m)
                    m = sub;
                cur[j] = m;
            }
        }
        memcpy(prev, cur, (lb + 1) * sizeof(int));
    }
    return prev[lb];
}

/**
 * 为未知诊断码找一个最接近的已知码（did-you-mean 建议）。
 *
 * 参数：
 *   out     - 输出缓冲区，写入建议码（NUL 结尾）；可为 NULL（仅查询是否存在建议）。
 *   out_cap - out 容量（字节）。
 *
 * 返回值：找到合理建议时返回 out 指针；无建议（无已知码或距离过大）时返回 NULL，out 不改写。
 *
 * 阈值说明：诊断码长度通常 3~6 字符，距离 <=3 视为「明显拼写偏差」；同时要求建议码
 * 与查询等长或仅差 1，避免把任意短查询都建议成首个已知码。
 */
/* G-02f-158：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
const char *diag_code_suggest(const char *code, char *out, size_t out_cap) {
    size_t i;
    int best_dist = 999;
    const char *best_code = NULL;
    int code_len;

    if (!code || !g_diag_code_table_count)
        return NULL;
    code_len = (int)strlen(code);
    if (code_len <= 0)
        return NULL;

    for (i = 0; i < g_diag_code_table_count; i++) {
        const char *cand = g_diag_code_table[i].code;
        int d = diag_levenshtein_ci(code, cand);
        if (d < best_dist) {
            best_dist = d;
            best_code = cand;
        }
    }
    if (!best_code)
        return NULL;
    /* 距离阈值：码短，<=3 视为拼写偏差；并要求不超过「查询长度 + 1」以免误建议。 */
    if (best_dist > 3 || best_dist > code_len + 1)
        return NULL;
    if (out && out_cap > 0) {
        size_t n = strlen(best_code);
        if (n >= out_cap)
            n = out_cap - 1;
        memcpy(out, best_code, n);
        out[n] = '\0';
    }
    return out ? out : best_code;
}

/**
 * 打印完整诊断码表（用户面：`xlang explain --list` / `xlang --explain --list`）。
 * 格式：列对齐的 CODE / KIND / Summary，便于人工浏览全部已知码。
 */
/* G-02f-157：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_print_code_table(uint8_t *out)
#else
void diag_print_code_table_impl(uint8_t *out)
#endif
{
    size_t i;
    if (!out)
        out = diag_h_stdout();
    diag_o_printf(out, "%-8s %-18s %s\n", "CODE", "KIND", "SUMMARY");
    diag_o_printf(out, "%-8s %-18s %s\n", "----", "----", "-------");
    for (i = 0; i < g_diag_code_table_count; i++) {
        const DiagCodeExplain *e = &g_diag_code_table[i];
        diag_o_printf(out, "%-8s %-18s %s\n", e->code, e->kind, e->summary);
    }
}


/**
 * JSON 诊断输出模式开关。
 * enable 非 0 时强制开启；0 时强制关闭（覆盖 XLANG_DIAG_JSON 环境变量）。
 * 仅供 driver 在解析 --diag-json 等 CLI 标志后调用；冷路径，零性能影响。
 */
/* G-02f-153：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_set_json_mode(int enable)
#else
void diag_set_json_mode_impl(int enable)
#endif
{
    g_diag_json = enable ? 1 : 0;
}

/** 供 .x 读写 g_diag_json 状态（-2=未决）。 */
/* G-02f-386：实现体始终 seed；public PREFER 时 thin forward（set 用 i32 壳） */
int diag_json_get_state_impl(void) {
    return g_diag_json;
}

int diag_json_set_state_impl(int v) {
    g_diag_json = v;
    return 0;
}

#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_json_get_state(void) {
    return diag_json_get_state_impl();
}
void diag_json_set_state(int v) {
    (void)diag_json_set_state_impl(v);
}
#endif

/**
 * 当前是否启用 JSON 诊断输出。首次调用时按 XLANG_DIAG_JSON 环境变量惰性决定，
 * 之后缓存；diag_set_json_mode 的显式设置优先于环境变量。
 */
/* G-02f-153：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
/* G-02f-338：hybrid 时 public 由 thin；本文件出 _impl */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
int diag_json_enabled(void)
#else
int diag_json_enabled_impl(void)
#endif
{
    if (g_diag_json == -2) {
        /* wave233 G.7: XLANG_DIAG_JSON via link_abi_getenv (not raw getenv). */
        const char *e = link_abi_getenv("XLANG_DIAG_JSON");
        g_diag_json = (e && e[0] && e[0] != '0') ? 1 : 0;
    }
    return g_diag_json == 1 ? 1 : 0;
}


/**
 * 将单个字符串以 JSON 字符串字面量形式写入 out（含两端引号）。
 * 转义 "、\ 与控制字符（\\uXXXX）；NULL 视作空串。仅在诊断冷路径调用。
 */
/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_json_write_str(uint8_t *out, const char *s)
#else
void diag_json_write_str_impl(uint8_t *out, const char *s)
#endif
{
    const unsigned char *p = (const unsigned char *)(s ? s : "");
    diag_o_putc(out, '"');
    for (; *p; p++) {
        unsigned char c = *p;
        switch (c) {
        case '"':  diag_o_puts(out, "\\\""); break;
        case '\\': diag_o_puts(out, "\\\\"); break;
        case '\b': diag_o_puts(out, "\\b"); break;
        case '\f': diag_o_puts(out, "\\f"); break;
        case '\n': diag_o_puts(out, "\\n"); break;
        case '\r': diag_o_puts(out, "\\r"); break;
        case '\t': diag_o_puts(out, "\\t"); break;
        default:
            if (c < 0x20)
                diag_o_printf(out, "\\u%04x", c);
            else
                diag_o_putc(out, (char)c);
        }
    }
    diag_o_putc(out, '"');
}


/**
 * 由诊断 kind 推导 JSON severity 字段。
 * 含 "warning" → warning；精确 "info"/"note"/"help"/"hint" → 同名；其余（含 error/parse error/...）→ error。
 */
/* G-02f-124：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
const char * diag_json_severity(const char *kind)
#else
const char * diag_json_severity_impl(const char *kind)
#endif
{
    if (!kind || !kind[0])
        return "error";
    if (strstr(kind, "warning"))
        return "warning";
    if (strcmp(kind, "info") == 0)
        return "info";
    if (strcmp(kind, "note") == 0)
        return "note";
    if (strcmp(kind, "help") == 0 || strcmp(kind, "hint") == 0)
        return "help";
    return "error";
}




/**
 * 以 NDJSON（每条诊断一行 JSON 对象）形式输出到 stderr，供 CI / 工具消费。
 * 字段：severity、code（可能为 null）、file（可能为 null）、line、col、message。
 * line/col 为 0 时仍输出（语义：未知）；调用方按需忽略。
 */
/* G-02f-156：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_DIAG_THIN_FROM_X
void diag_report_json(const char *file, int line, int col,
                             const char *kind, const char *code, const char *msg)
#else
void diag_report_json_impl(const char *file, int line, int col,
                             const char *kind, const char *code, const char *msg)
#endif
{
    const char *sev = diag_json_severity(kind);
    uint8_t *eo = diag_h_stderr();
    diag_o_puts(eo, "{\"severity\":");
    diag_json_write_str(eo, sev);
    diag_o_puts(eo, ",\"code\":");
    if (code && code[0])
        diag_json_write_str(eo, code);
    else
        diag_o_puts(eo, "null");
    diag_o_puts(eo, ",\"file\":");
    if (file && file[0])
        diag_json_write_str(eo, file);
    else
        diag_o_puts(eo, "null");
    diag_o_printf(eo, ",\"line\":%d,\"col\":%d,\"message\":", line, col);
    diag_json_write_str(eo, msg ? msg : "");
    diag_o_puts(eo, "}\n");
    /* raw fd 2 writes are unbuffered — no flush (9.7.1) */
}


