/* scripts/pthin_stretch_audit_eq_harness.c — 7.2.1 B-minus equivalence harness
 *
 * Proves every .x port in src/asm/pthin_stretch_audit.x is behaviorally
 * identical to its gated C twin in the suite slice: same return value on the
 * same lexer state AND the caller's lexer untouched after the call (by-value
 * net semantics). Drives all audit functions on identical lexer states —
 * synthetic sources at every token offset, plus real .x files (argv) at every
 * token offset (capped) — through a table of (C reference twin, .x version)
 * pairs; 3-arg audits run with each flag polarity.
 *
 * Lexer authority under test: seeds/lexer_gen.linux.x86_64.c pin (same T-symbol
 * face as product lexer_x.o). Struct mirrors follow the layout-mirror
 * discipline (field-for-field identical to the lexer authority structs).
 *
 * PLATFORM: SHARED (built+run on Darwin and Ubuntu by the driver script).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h" /* single authority for TOKEN_* kind values */

/* --- parser_asm layout mirrors (identical to the suite family) --- */
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

/* Lexer authority (pin .c object provides the definition). */
extern void lexer_next_into(struct parser_asm_lexer_result *out, struct parser_asm_lexer lex,
                            struct parser_asm_slice_u8 *source);

/* .x ports under test (pointer ABI, B-minus). */
extern int32_t parser_asm_stretch_if_header_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_loop_header_audit_c(void *lex_inout, void *source, int32_t expect_while);
extern int32_t parser_asm_stretch_break_continue_audit_c(void *lex_inout, void *source, int32_t want_break);
extern int32_t parser_asm_stretch_else_stmt_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_else_if_chain_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_let_const_decl_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_enum_header_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_match_kw_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_return_stmt_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_import_stmt_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_fn_param_list_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_skip_return_type_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_fn_sig_audit_c(void *lex_inout, void *source);
extern int32_t parser_asm_stretch_function_header_audit_c(void *lex_inout, void *source);

/* Pin .c extern stubs (only reached on cfg-attr / malformed-literal paths the
 * harness corpus never exercises; stubs keep the link self-contained). */
char *link_abi_getenv(const char *name) { return getenv(name); }
int32_t cfg_eval_expr_c(char *buf, int32_t expr_len) {
  (void)buf;
  (void)expr_len;
  return 1;
}
void diag_report_with_code(void *ctx, const char *code, int32_t line, int32_t col, const char *fmt,
                           ...) {
  (void)ctx;
  (void)code;
  (void)line;
  (void)col;
  (void)fmt;
}
int32_t lexer_parser_slice_from_buf(void) { return 0; }

/* lex_skip family primitive used by the import_stmt twin (def below). */
void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);

/* --- reference twins (generated from the suite slice; refresh in the same
 * commit whenever a suite twin changes) --- */
#include "pthin_stretch_audit_eq_twins.h"

/* Authority twin of parser_asm_lex_from_result_val_into (lex_skip slice:9);
 * the import_stmt C twin calls it — verbatim semantics, refresh together). */
void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r) {
  if (!out)
    return;
  out->pos = r.next_lex.pos;
  out->line = r.next_lex.line;
  out->col = r.next_lex.col;
}

/* 2-arg to uniform 3-arg shims (dispatch table needs one fn type). */
#define AUDIT2_SHIM(cname) \
  static int32_t x_##cname(void *l, void *s, int32_t f) { (void)f; return cname(l, s); }
AUDIT2_SHIM(parser_asm_stretch_if_header_audit_c)
AUDIT2_SHIM(parser_asm_stretch_else_stmt_audit_c)
AUDIT2_SHIM(parser_asm_stretch_else_if_chain_audit_c)
AUDIT2_SHIM(parser_asm_stretch_let_const_decl_audit_c)
AUDIT2_SHIM(parser_asm_stretch_enum_header_audit_c)
AUDIT2_SHIM(parser_asm_stretch_match_kw_audit_c)
AUDIT2_SHIM(parser_asm_stretch_return_stmt_audit_c)
AUDIT2_SHIM(parser_asm_stretch_import_stmt_audit_c)
static int32_t x_loop_header(void *l, void *s, int32_t f) { return parser_asm_stretch_loop_header_audit_c(l, s, f); }
static int32_t x_break_continue(void *l, void *s, int32_t f) { return parser_asm_stretch_break_continue_audit_c(l, s, f); }
#define CREF2_SHIM(cname) \
  static int32_t r_##cname(void *l, void *s, int32_t f) { (void)f; return c_ref_##cname(l, s); }
CREF2_SHIM(if_header)
CREF2_SHIM(else_stmt)
CREF2_SHIM(else_if_chain)
CREF2_SHIM(let_const_decl)
CREF2_SHIM(enum_header)
CREF2_SHIM(match_kw)
CREF2_SHIM(return_stmt)
CREF2_SHIM(import_stmt)
static int32_t r_loop_header(void *l, void *s, int32_t f) { return c_ref_loop_header(l, s, f); }
static int32_t r_break_continue(void *l, void *s, int32_t f) { return c_ref_break_continue(l, s, f); }
#define AUDIT2_SHIM2(cname) \
  static int32_t x2_##cname(void *l, void *s, int32_t f) { (void)f; return cname(l, s); }
AUDIT2_SHIM2(parser_asm_stretch_fn_sig_audit_c)
AUDIT2_SHIM2(parser_asm_stretch_function_header_audit_c)
#define CREF2_SHIM2(cname) \
  static int32_t r2_##cname(void *l, void *s, int32_t f) { (void)f; return c_ref_##cname(l, s); }
CREF2_SHIM2(fn_sig)
CREF2_SHIM2(function_header)
static int32_t xi_fn_param_list(void *l, void *s, int32_t f) { (void)f; return parser_asm_stretch_fn_param_list_audit_c(l, s); }
static int32_t xi_skip_return_type(void *l, void *s, int32_t f) { (void)f; return parser_asm_stretch_skip_return_type_audit_c(l, s); }
static int32_t ri_fn_param_list(void *l, void *s, int32_t f) { (void)f; return c_ref_fn_param_list(l, s); }
static int32_t ri_skip_return_type(void *l, void *s, int32_t f) { (void)f; return c_ref_skip_return_type(l, s); }

/* --- dispatch table --- */
typedef int32_t (*audit_fn)(void *lex_inout, void *source, int32_t flag);

typedef struct {
  const char *name;
  audit_fn c_ref;
  audit_fn x_ver;
  int32_t flag;
  int inout; /* 1: inout contract — compare post-call lexer states */
} audit_case;

static const audit_case k_cases[] = {
    {"if_header", r_if_header, x_parser_asm_stretch_if_header_audit_c, 0, 0},
    {"loop_header/w", r_loop_header, x_loop_header, 1, 0},
    {"loop_header/f", r_loop_header, x_loop_header, 0, 0},
    {"break_continue/b", r_break_continue, x_break_continue, 1, 0},
    {"break_continue/c", r_break_continue, x_break_continue, 0, 0},
    {"else_stmt", r_else_stmt, x_parser_asm_stretch_else_stmt_audit_c, 0, 0},
    {"else_if_chain", r_else_if_chain, x_parser_asm_stretch_else_if_chain_audit_c, 0, 0},
    {"let_const_decl", r_let_const_decl, x_parser_asm_stretch_let_const_decl_audit_c, 0, 0},
    {"enum_header", r_enum_header, x_parser_asm_stretch_enum_header_audit_c, 0, 0},
    {"match_kw", r_match_kw, x_parser_asm_stretch_match_kw_audit_c, 0, 0},
    {"return_stmt", r_return_stmt, x_parser_asm_stretch_return_stmt_audit_c, 0, 0},
    {"import_stmt", r_import_stmt, x_parser_asm_stretch_import_stmt_audit_c, 0, 0},
    {"fn_param_list", ri_fn_param_list, xi_fn_param_list, 0, 1},
    {"skip_return_type", ri_skip_return_type, xi_skip_return_type, 0, 1},
    {"fn_sig", r2_fn_sig, x2_parser_asm_stretch_fn_sig_audit_c, 0, 0},
    {"function_header", r2_function_header, x2_parser_asm_stretch_function_header_audit_c, 0, 0},
};
static int g_fail = 0;
static long g_checks = 0;

/** Compare one (C ref, .x) pair on one lexer state; verify no caller movement. */
static void check_one(const audit_case *ac, struct parser_asm_lexer lex,
                      struct parser_asm_slice_u8 *src) {
  struct parser_asm_lexer for_c = lex;
  struct parser_asm_lexer for_x = lex;
  int32_t rc_c;
  int32_t rc_x;
  rc_c = ac->c_ref(&for_c, src, ac->flag);
  rc_x = ac->x_ver(&for_x, src, ac->flag);
  g_checks++;
  if (rc_c != rc_x) {
    printf("FAIL %s: rc mismatch c=%d x=%d (pos=%zu line=%d col=%d)\n", ac->name, rc_c, rc_x,
           lex.pos, lex.line, lex.col);
    g_fail++;
    return;
  }
  if (ac->inout) {
    /* inout contract: both twins must leave the caller's lexer at the SAME
     * end state — compare the two directly (advancement allowed). */
    if (memcmp(&for_c, &for_x, sizeof(lex)) != 0) {
      printf("FAIL %s: inout end-state mismatch c=(%zu/%d/%d) x=(%zu/%d/%d)\n", ac->name,
             for_c.pos, for_c.line, for_c.col, for_x.pos, for_x.line, for_x.col);
      g_fail++;
    }
    return;
  }
  if (memcmp(&for_x, &lex, sizeof(lex)) != 0) {
    printf("FAIL %s: .x moved caller lexer (%zu/%d/%d -> %zu/%d/%d)\n", ac->name, lex.pos, lex.line,
           lex.col, for_x.pos, for_x.line, for_x.col);
    g_fail++;
  }
  if (memcmp(&for_c, &lex, sizeof(lex)) != 0) {
    printf("FAIL %s: c ref moved caller lexer (%zu/%d/%d -> %zu/%d/%d)\n", ac->name, lex.pos,
           lex.line, lex.col, for_c.pos, for_c.line, for_c.col);
    g_fail++;
  }
}

/** Run all audit cases at every token offset of one source buffer. */
static void battery(const char *tag, const char *text, size_t len, int max_steps) {
  struct parser_asm_slice_u8 src;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  size_t ci;
  int step;
  src.data = (uint8_t *)(uintptr_t)text;
  src.length = len;
  lex.pos = 0;
  lex.line = 1;
  lex.col = 1;
  for (step = 0; step <= max_steps; step++) {
    for (ci = 0; ci < sizeof(k_cases) / sizeof(k_cases[0]); ci++)
      check_one(&k_cases[ci], lex, &src);
    lexer_next_into(&r, lex, &src);
    if ((int32_t)r.tok.kind == (int32_t)TOKEN_EOF)
      break;
    lex = r.next_lex;
  }
  (void)tag;
}

int main(int argc, char **argv) {
  static const char *const k_synth[] = {
      "if (x) { }",       "if(x",                 "iff (x)",      "while (x)",
      "while(x",          "for (i) { }",          "for(;)",       "break;",
      "break ;",          "continue;",            "continue",     "else { }",
      "else if (y)",      "else x",               "let x: i32 = 1;", "let x = 1;",
      "const y: u8 = 2;", "let : i32",            "enum E { }",   "enum { }",
      "enum E",           "match v { 1 => 2 }",   "match v;",     "match",
      "return;",          "return 1 + 2;",        "return",       "import a.b;",
      "import a.b as c;", "import ;",             "import",       "function f(a: i32) : i32 { 1 }",
      "function g(x: i32, y: *u8) : [u8] { }",
      "async function h() : **u8 { }",
      "function bad(,) : i32 { }",
      "function noparens",
      "function f() : { }",
      "function f() { }",
      "\n\nif (a)\n{",   "let x\n:\ni32",        "return\n1;",
  };
  size_t i;
  int f;
  for (i = 0; i < sizeof(k_synth) / sizeof(k_synth[0]); i++) {
    char tag[32];
    snprintf(tag, sizeof(tag), "synth%zu", i);
    battery(tag, k_synth[i], strlen(k_synth[i]), 64);
  }
  for (f = 1; f < argc; f++) {
    FILE *fp = fopen(argv[f], "rb");
    char *buf;
    long sz;
    if (!fp) {
      printf("FAIL open %s\n", argv[f]);
      g_fail++;
      continue;
    }
    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = (char *)malloc((size_t)sz + 1);
    if (!buf || fread(buf, 1, (size_t)sz, fp) != (size_t)sz) {
      printf("FAIL read %s\n", argv[f]);
      g_fail++;
      fclose(fp);
      free(buf);
      continue;
    }
    fclose(fp);
    buf[sz] = 0;
    battery(argv[f], buf, (size_t)sz, 2500);
    free(buf);
  }
  /* Null-guard parity: every pair must answer 0 without dereferencing. */
  {
    struct parser_asm_lexer lex;
    size_t ci;
    lex.pos = 0;
    lex.line = 1;
    lex.col = 1;
    for (ci = 0; ci < sizeof(k_cases) / sizeof(k_cases[0]); ci++) {
      g_checks++;
      if (k_cases[ci].x_ver(&lex, 0, k_cases[ci].flag) != 0) {
        printf("FAIL null-source guard (.x %s)\n", k_cases[ci].name);
        g_fail++;
      }
      g_checks++;
      if (k_cases[ci].x_ver(0, 0, k_cases[ci].flag) != 0) {
        printf("FAIL null-lex guard (.x %s)\n", k_cases[ci].name);
        g_fail++;
      }
    }
  }
  if (g_fail) {
    printf("pthin_stretch_audit_eq: %ld checks, %d FAIL\n", g_checks, g_fail);
    return 1;
  }
  printf("pthin_stretch_audit_eq: %ld checks OK\n", g_checks);
  return 0;
}
