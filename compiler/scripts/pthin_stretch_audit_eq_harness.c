/* scripts/pthin_stretch_audit_eq_harness.c — 7.2.1 B-minus pilot equivalence harness
 *
 * Proves the .x port (src/asm/pthin_stretch_audit.x) of
 * parser_asm_stretch_if_header_audit_c is behaviorally identical to the
 * by-value C twin in seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc.
 *
 * Method: drive BOTH implementations on identical lexer states — synthetic
 * sources at step 0, plus real .x files (argv) at every token offset — and
 * compare (a) return values and (b) the caller's lexer state after the call
 * (the C twin is by-value so the caller must never see movement; the .x port
 * promises the same net effect via the bridge restore trio).
 *
 * Lexer authority under test: seeds/lexer_gen.linux.x86_64.c pin (same T-symbol
 * face as product lexer_x.o; drift-gate 15/5/0 keeps them honest).
 * The struct mirrors below follow the layout-mirror discipline (field-for-field
 * identical to the lexer authority structs — see the bridge file header).
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

/* .x port under test (pointer ABI, B-minus). */
extern int32_t parser_asm_stretch_if_header_audit_c(void *lex_inout, void *source);

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

/* Reference twin — verbatim copy of the gated C authority in
 * seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc
 * (parser_asm_stretch_if_header_audit_c, the #ifndef non-hybrid branch;
 * refresh this copy in the same commit whenever the suite twin changes). */
static int32_t c_ref_if_header(void *lex_inout, void *source) {
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  if (!lex_inout || !source)
    return 0;
  lex = *(struct parser_asm_lexer *)lex_inout;
  lexer_next_into(&r, lex, (struct parser_asm_slice_u8 *)source);
  if (r.tok.kind != (int32_t)TOKEN_IF)
    return 0;
  lexer_next_into(&r, r.next_lex, (struct parser_asm_slice_u8 *)source);
  return r.tok.kind == (int32_t)TOKEN_LPAREN ? 1 : 0;
}

static int g_fail = 0;
static long g_checks = 0;

/** Compare both twins on one (lexer, source) state; verify no caller movement. */
static void check_one(const char *tag, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *src) {
  struct parser_asm_lexer for_c = lex;
  struct parser_asm_lexer for_x = lex;
  int32_t rc_c;
  int32_t rc_x;
  rc_c = c_ref_if_header(&for_c, src);
  rc_x = parser_asm_stretch_if_header_audit_c(&for_x, src);
  g_checks++;
  if (rc_c != rc_x) {
    printf("FAIL %s: rc mismatch c=%d x=%d (pos=%zu line=%d col=%d)\n", tag, rc_c, rc_x, lex.pos,
           lex.line, lex.col);
    g_fail++;
    return;
  }
  if (memcmp(&for_x, &lex, sizeof(lex)) != 0) {
    printf("FAIL %s: .x moved caller lexer (%zu/%d/%d -> %zu/%d/%d)\n", tag, lex.pos, lex.line,
           lex.col, for_x.pos, for_x.line, for_x.col);
    g_fail++;
  }
  if (memcmp(&for_c, &lex, sizeof(lex)) != 0) {
    printf("FAIL %s: c ref moved caller lexer (%zu/%d/%d -> %zu/%d/%d)\n", tag, lex.pos, lex.line,
           lex.col, for_c.pos, for_c.line, for_c.col);
    g_fail++;
  }
  /* Both twins promise by-value net semantics: caller's lexer untouched. */
}

/** Run the battery at every token offset of one source buffer. */
static void battery(const char *tag, const char *text, size_t len, int max_steps) {
  struct parser_asm_slice_u8 src;
  struct parser_asm_lexer lex;
  struct parser_asm_lexer_result r;
  int step;
  src.data = (uint8_t *)(uintptr_t)text;
  src.length = len;
  lex.pos = 0;
  lex.line = 1;
  lex.col = 1;
  for (step = 0; step <= max_steps; step++) {
    check_one(tag, lex, &src);
    lexer_next_into(&r, lex, &src);
    if ((int32_t)r.tok.kind == (int32_t)TOKEN_EOF)
      break;
    lex = r.next_lex;
  }
}

int main(int argc, char **argv) {
  static const char *const k_synth[] = {
      "if (x) { }",       "if(x",          "iff (x)",      "while (x)",   "if",
      "(",                "if  (",         "  if\t(",      "if (",        "xif (",
      "if(x)",            "if(x",          "\n\nif (y)",   "if \n (y)",   "iff",
      "function f() { if (a) { return 1; } }", "let x = 1; if (x) { }",
      "if ((a + b) * c) { }",               "if\x01(",     "ifIF(",
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
    battery(argv[f], buf, (size_t)sz, 4000);
    free(buf);
  }
  /* Null-guard parity: both twins must answer 0 without dereferencing. */
  {
    struct parser_asm_lexer lex;
    lex.pos = 0;
    lex.line = 1;
    lex.col = 1;
    g_checks++;
    if (parser_asm_stretch_if_header_audit_c(&lex, 0) != 0) {
      printf("FAIL null-source guard (.x)\n");
      g_fail++;
    }
    if (c_ref_if_header(&lex, 0) != 0) {
      printf("FAIL null-source guard (c ref)\n");
      g_fail++;
    }
    g_checks++;
    if (parser_asm_stretch_if_header_audit_c(0, 0) != 0) {
      printf("FAIL null-lex guard (.x)\n");
      g_fail++;
    }
  }
  if (g_fail) {
    printf("pthin_stretch_audit_eq: %ld checks, %d FAIL\n", g_checks, g_fail);
    return 1;
  }
  printf("pthin_stretch_audit_eq: %ld checks OK\n", g_checks);
  return 0;
}
