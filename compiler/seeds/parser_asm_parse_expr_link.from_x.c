/* seeds/parser_asm_parse_expr_link.from_x.c — G-02f-10 product parse_expr bridge
 * G-02f-116 true .x pure helpers.
 * G-02f-102 helper gates.
 * G-02f-333：PREFER_X_O hybrid 时 debug_enabled 由 .x thin 提供，本文件出 _impl。
 * Compile with -DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS for product G05.
 * Product: → src/asm/parser_asm_parse_expr_link.o
 */
/**
 * parser_asm_parse_expr_link.c — parser_asm_thin 与 parser_x.o 的链接桥 + pipeline 别名。
 *
 * 1) parse_expr_into：thin 切片裸名 → parser_parse_expr_into（字段拷贝转发）
 * 2) parse_into* / parser_parse_into* 弱桩：seed 链无 bootstrap .o 时兜底
 * 3) parser_* 前缀别名（可选）：-DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS 时省略
 *    （产品/G05 默认 SKIP：由 thin_glue / parser_x 提供强符号）
 *
 * G-02e-7：原 parser_asm_link_alias.c 并入本 TU。
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
/* Cap residual 9.5.3 slice3b: stderr diagnostics go through xlang_snprintf (10.7.2
 * fmt authority, %zu supported) + xlang_io_write on raw fd 2 — libc <stdio.h>
 * dropped (fflush becomes a no-op concept: raw fd writes are unbuffered). */
#include <xlang_fmt_cap.h>
#include <xlang_io_cap.h>
#undef snprintf
#define snprintf xlang_snprintf

/* Cap stderr write helpers (fd 2). Single authority inside this TU for the
 * parse_expr debug diagnostics. */
static void cap_err_puts(const char *s) {
  if (s)
    (void)xlang_io_write(2, s, strlen(s));
}
static void cap_err_putc(char c) {
  (void)xlang_io_write(2, &c, 1);
}

/** 与 parser_asm / lexer.x Lexer 布局一致。 */
struct parser_asm_lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};

struct parser_asm_slice_u8 {
  uint8_t *data;
  size_t length;
};

/** 与 parser_asm_body_let_slice.inc 中 parser_asm_parse_expr_result 一致。 */
struct parser_asm_parse_expr_result {
  int32_t ok;
  int32_t expr_ref;
  struct parser_asm_lexer next_lex;
};

/** 与 parser_gen / pipeline_gen u8[] 切片 ABI 一致。 */
struct xlang_slice_uint8_t {
  uint8_t *data;
  size_t length;
};

struct lexer_Lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};

struct parser_ParseExprResult {
  int32_t ok;
  int32_t expr_ref;
  struct lexer_Lexer next_lex;
};

/** 与 parser.x ParseIntoResult 布局一致。 */
struct parser_ParseIntoResult {
  int32_t ok;
  int32_t main_idx;
};

struct ASTModule;
struct ast_ASTArena;

extern void parser_parse_expr_into(struct ast_ASTArena *arena, struct lexer_Lexer lex,
                                   struct xlang_slice_uint8_t *source, struct parser_ParseExprResult *out);

extern int32_t parser_asm_copy_module_import_path64_c(struct ASTModule *module, int32_t i, uint8_t *out);
extern int32_t parser_parse_one_function_ok_for_pipeline_glue(void *arena, struct xlang_slice_uint8_t *source);
extern int32_t parser_diag_token_after_collect_imports_glue(struct xlang_slice_uint8_t *source, void *module);
/* wave237 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — cold seed twin uses same face as product hybrid pure .x. */
extern char *link_abi_getenv(const char *name);
/* G-02f-116 / G-02f-333 / wave237：debug_enabled pure orch in .x (hybrid FROM_X);
 * cold seed keeps same-semantics twin under #ifndef (no *_impl residual).
 * Rules: null / empty / leading '0' → 0; any other non-empty → 1. */
#ifndef XLANG_L2_PEL_THIN_FROM_X
int parser_asm_parse_expr_debug_enabled(void) {
  const char *v = link_abi_getenv("XLANG_PARSER_ASM_DEBUG");
  return v && *v && *v != '0';
}
#else
/* wave237: pure orch in .x; no rest *_impl rename for debug_enabled. */
extern int parser_asm_parse_expr_debug_enabled(void);
#endif
/* G-02f-165 / wave237：逻辑源 .x（批折叠）；cold seed 保留同语义 C 供无 PREFER 冷路径。 */



void parser_asm_parse_expr_debug_snippet_c(struct parser_asm_slice_u8 *source, size_t pos) {
  size_t start;
  size_t end;
  size_t i;
  if (!source || !source->data || source->length == 0) {
    cap_err_puts(" snippet=<no-source>\n");
    return;
  }
  start = pos;
  if (start > source->length)
    start = source->length;
  if (start > 12)
    start -= 12;
  else
    start = 0;
  end = pos + 24;
  if (end > source->length)
    end = source->length;
  cap_err_puts(" snippet=");
  for (i = start; i < end; i++) {
    unsigned char ch = source->data[i];
    if (ch == (unsigned char)'\n')
      cap_err_puts("\\n");
    else if (ch == (unsigned char)'\r')
      cap_err_puts("\\r");
    else if (ch == (unsigned char)'\t')
      cap_err_puts("\\t");
    else if (ch < 32 || ch > 126) {
      char _xb[8];
      int _xn = snprintf(_xb, sizeof _xb, "\\x%02x", ch);
      if (_xn > 0)
        (void)xlang_io_write(2, _xb, (size_t)_xn);
    } else
      cap_err_putc((char)ch);
  }
  cap_err_putc('\n');
}




/**
 * asm thin 切片入口：转发至 parser_x.o 的 parser_parse_expr_into。
 */
void parse_expr_into(void *arena, struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source,
                     struct parser_asm_parse_expr_result *out) {
  enum { PARSER_ASM_PARSE_EXPR_SAME_POS_WARN = 4096 };
  static size_t prev_in_pos = (size_t)-1;
  static int32_t same_in_pos_count = 0;
  static int32_t parse_expr_debug_calls = 0;
  int debug_enabled;
  struct lexer_Lexer mega_lex;
  struct xlang_slice_uint8_t mega_src;
  struct parser_ParseExprResult mega_out;
  if (!source || !out) {
    return;
  }
  debug_enabled = parser_asm_parse_expr_debug_enabled();
  parse_expr_debug_calls++;
  if (lex.pos == prev_in_pos) {
    same_in_pos_count++;
  } else {
    prev_in_pos = lex.pos;
    same_in_pos_count = 0;
  }
  if (debug_enabled && (parse_expr_debug_calls <= 64 || (parse_expr_debug_calls % 4096) == 0
      || same_in_pos_count == PARSER_ASM_PARSE_EXPR_SAME_POS_WARN)) {
    {
      char _db[256];
      int _dn = snprintf(_db, sizeof _db,
                         "parser_asm parse_expr enter call=%d in_pos=%zu line=%d col=%d len=%zu same=%d\n",
                         parse_expr_debug_calls, lex.pos, lex.line, lex.col, source->length, same_in_pos_count);
      if (_dn > 0)
        (void)xlang_io_write(2, _db, (size_t)_dn);
    }
    if (parse_expr_debug_calls <= 16)
      parser_asm_parse_expr_debug_snippet_c(source, lex.pos);
  }
  mega_lex.pos = lex.pos;
  mega_lex.line = lex.line;
  mega_lex.col = lex.col;
  mega_src.data = source->data;
  mega_src.length = source->length;
  parser_parse_expr_into((struct ast_ASTArena *)arena, mega_lex, &mega_src, &mega_out);
  if (debug_enabled && (parse_expr_debug_calls <= 64 || (parse_expr_debug_calls % 4096) == 0 || mega_out.next_lex.pos < lex.pos
      || mega_out.next_lex.pos == lex.pos || same_in_pos_count >= PARSER_ASM_PARSE_EXPR_SAME_POS_WARN)) {
    {
      char _db[256];
      int _dn = snprintf(_db, sizeof _db,
                         "parser_asm parse_expr leave call=%d ok=%d in_pos=%zu out_pos=%zu expr=%d out_line=%d out_col=%d\n",
                         parse_expr_debug_calls, mega_out.ok, lex.pos, mega_out.next_lex.pos, mega_out.expr_ref, mega_out.next_lex.line,
                         mega_out.next_lex.col);
      if (_dn > 0)
        (void)xlang_io_write(2, _db, (size_t)_dn);
    }
  }
  out->ok = mega_out.ok;
  out->expr_ref = mega_out.expr_ref;
  out->next_lex.pos = mega_out.next_lex.pos;
  out->next_lex.line = mega_out.next_lex.line;
  out->next_lex.col = mega_out.next_lex.col;
}

/* ---- G-02e-7: parser_asm_link_alias (pipeline/runtime link aliases + weak parse stubs) ----
 *
 * PLATFORM: WINDOWS | PE — XLANG_WEAK is empty (strong defs). Empty parse_into*
 *   stubs MUST NOT ship in product TUs compiled with
 *   -DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS: hybrid link puts this .o before
 *   parser_x.o (GEN_DRIVER_BSTRICT then GEN_DRIVER_X_PIPELINE), so PE
 *   --allow-multiple-definition FIRST-wins selected the empty stub →
 *   num_funcs=0 / XP003 (ec=0, out_len=0). Observed 2026-07-30 hybrid live9.
 * PLATFORM: SHARED ELF — weak stubs remain only for cold seed paths that omit
 *   parser_x / bootstrap (no SKIP define). Product/G05 always passes SKIP.
 */

#ifndef PARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS
/** runtime expects parser_diag_token_after_collect_imports; delegate thin glue. */
int32_t parser_diag_token_after_collect_imports(struct xlang_slice_uint8_t *source, void *module) {
  return parser_diag_token_after_collect_imports_glue(source, module);
}

/**
 * Cold seed without parser_parse_bootstrap.o: empty bare-name stubs.
 * Experimental/product link real bootstrap or parser_x (SKIP path has no stubs).
 */
XLANG_WEAK struct parser_ParseIntoResult parse_into_buf(void *arena, void *module, uint8_t *data,
                                                                   int32_t len) {
  (void)arena;
  (void)module;
  (void)data;
  (void)len;
  struct parser_ParseIntoResult r;
  r.ok = 0;
  r.main_idx = -1;
  return r;
}

XLANG_WEAK struct parser_ParseIntoResult parse_into(void *arena, void *module,
                                                                struct xlang_slice_uint8_t *source) {
  (void)arena;
  (void)module;
  (void)source;
  struct parser_ParseIntoResult r;
  r.ok = 0;
  r.main_idx = -1;
  return r;
}

XLANG_WEAK void parse_into_set_main_index(void *module, int32_t main_idx) {
  (void)module;
  (void)main_idx;
}

/** pipeline expects parser_copy_module_import_path64; delegate thin C copy+len. */
int32_t parser_copy_module_import_path64(struct ASTModule *module, int32_t i, uint8_t out[128]) {
  return parser_asm_copy_module_import_path64_c(module, i, out);
}

/** pipeline expects (arena, source); delegate parse_one_function_ok_for_pipeline_glue. */
int32_t parser_parse_one_function_ok_for_pipeline(void *arena, struct xlang_slice_uint8_t *source) {
  return parser_parse_one_function_ok_for_pipeline_glue(arena, source);
}

/** runtime expects parser_parse_into_*; cold weak defaults (ELF only effective). */
XLANG_WEAK struct parser_ParseIntoResult parser_parse_into_buf(void *arena, void *module, uint8_t *data,
                                                                          int32_t len) {
  return parse_into_buf(arena, module, data, len);
}

XLANG_WEAK struct parser_ParseIntoResult parser_parse_into(void *arena, void *module,
                                                                       struct xlang_slice_uint8_t *source) {
  return parse_into(arena, module, source);
}

XLANG_WEAK void parser_parse_into_set_main_index(void *module, int32_t main_idx) {
  parse_into_set_main_index(module, main_idx);
}
#endif /* !PARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS */
