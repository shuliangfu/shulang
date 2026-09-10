#!/usr/bin/env python3
# sync_stretch_audit_harness.py — regenerate the B-minus equivalence harness
# twin set + dispatch table from the current migrated surface.
#
# Inputs (authorities):
#   src/asm/pthin_stretch_audit.x                          — migrated exports
#   seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc — gated twins
#   seeds/parser_asm_lex_step_bridge.from_x.c + suite skip helpers — link faces
#
# Outputs (fully regenerated each run):
#   scripts/pthin_stretch_audit_eq_twins.h — c_ref_* static twins (verbatim
#     gated C bodies, renamed) + helper authority copies
#   scripts/pthin_stretch_audit_eq_table.h — shims + k_cases[] for every
#     migrated 2-arg audit (3-arg flag audits get both polarities)
#
# PLATFORM: SHARED (host-side generator; output compiled on both ends).
import re
import sys

SUITE = "seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc"
XFILE = "src/asm/pthin_stretch_audit.x"
TWINS = "scripts/pthin_stretch_audit_eq_twins.h"
TABLE = "scripts/pthin_stretch_audit_eq_table.h"

# helper authority copies (link faces used by twins; refresh with sources)
HELPERS = '''
/* ── helper authority copies (verbatim from their slices; refresh together) ── */
extern void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r);
void parser_asm_lex_from_result_val_into(struct parser_asm_lexer *out, struct parser_asm_lexer_result r) {
  if (!out)
    return;
  out->pos = r.next_lex.pos;
  out->line = r.next_lex.line;
  out->col = r.next_lex.col;
}
int32_t parser_asm_stretch_is_type_start_kind_c(int32_t kind) {
  return kind == (int32_t)TOKEN_I32 || kind == (int32_t)TOKEN_I64 || kind == (int32_t)TOKEN_BOOL
      || kind == (int32_t)TOKEN_U8 || kind == (int32_t)TOKEN_U32 || kind == (int32_t)TOKEN_U64
      || kind == (int32_t)TOKEN_USIZE || kind == (int32_t)TOKEN_VOID || kind == (int32_t)TOKEN_IDENT;
}

static int32_t parser_asm_stretch_ident_byte_ok_c(uint8_t c, int32_t is_first) {
  int alpha = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
  if (is_first != 0)
    return alpha ? 1 : 0;
  return alpha || (c >= '0' && c <= '9') ? 1 : 0;
}
int32_t parser_asm_stretch_bind_name_validate_c(const uint8_t *name, int32_t len) {
  int32_t i;
  if (!name || len <= 0 || len > 63)
    return 0;
  if (parser_asm_stretch_ident_byte_ok_c(name[0], 1) == 0)
    return 0;
  for (i = 1; i < len; i++) {
    if (parser_asm_stretch_ident_byte_ok_c(name[i], 0) == 0)
      return 0;
  }
  return 1;
}
int32_t parser_asm_is_compound_assign_token_c(int32_t kind) {
  return kind == (int32_t)TOKEN_PLUS_EQ || kind == (int32_t)TOKEN_MINUS_EQ || kind == (int32_t)TOKEN_STAR_EQ
      || kind == (int32_t)TOKEN_SLASH_EQ || kind == (int32_t)TOKEN_PERCENT_EQ || kind == (int32_t)TOKEN_AMP_EQ
      || kind == (int32_t)TOKEN_PIPE_EQ || kind == (int32_t)TOKEN_CARET_EQ || kind == (int32_t)TOKEN_LSHIFT_EQ
      || kind == (int32_t)TOKEN_RSHIFT_EQ;
}
'''


SUITE_HELPER_SIGS = [
    "static int32_t parser_asm_stretch_expr_binop_kinds_probe_c(",
    "void parser_asm_skip_balanced_parens_into_slice_c(",
    "void parser_asm_stretch_skip_balanced_brackets_into_c(",
    "struct parser_asm_lexer parser_asm_stretch_skip_type_suffix_c(",
    "struct parser_asm_lexer parser_asm_stretch_skip_one_param_type_c(",
]


def suite_helper_defs(suite):
    out = []
    extra = ""
    for sig in SUITE_HELPER_SIGS:
        m = re.search(r"^" + re.escape(sig) + r"[^\n]*$(.*?)^}$", suite, re.S | re.M)
        if not m:
            # try the lex_skip slice for non-static helpers living there
            try:
                extra_src = open("seeds/parser_asm/parser_asm_lex_skip_slice.inc").read()
            except FileNotFoundError:
                extra_src = ""
            m = re.search(r"^" + re.escape(sig) + r"[^\n]*$(.*?)^}$", extra_src, re.S | re.M)
        if not m:
            raise SystemExit(f"helper def not found: {sig}")
        body = m.group(0)
        # strip audit-gate macros (daily no-op semantics) and their inner calls
        body = re.sub(r"PARSER_ASM_STRETCH_AUDIT_CALL\([^;]*\);", "(void)0;", body)
        out.append(body + "\n")
    return "\n".join(out)


def main():
    suite = open(SUITE).read()
    xsrc = open(XFILE).read()

    # 1) migrated exports (2-arg audits; flag audits detected by param count)
    exports = re.findall(r"export function (parser_asm_stretch_\w+_c)\(", xsrc)
    flag3 = set()
    buf3 = set()
    for m in re.finditer(r"export function (parser_asm_stretch_\w+_c)\(([^)]*)\): i32 \{", xsrc):
        params = m.group(2)
        if params.count(",") == 2:
            if "data: *u8" in params and "len: i32" in params:
                buf3.add(m.group(1))
            else:
                flag3.add(m.group(1))

    # 2) twins from the suite (gated pointer-ABI bodies)
    twins = []
    have = set()
    for m in re.finditer(
        r"^int32_t (parser_asm_stretch_\w+_c)\(void \*lex_inout([^\n]*)\) \{$(.*?)^\}$\n#endif",
        suite, re.S | re.M,
    ):
        name, extra, body = m.group(1), m.group(2), m.group(3)
        if name not in exports or name in have:
            continue
        have.add(name)
        base = name[len("parser_asm_stretch_"):-2]  # strip prefix and _c
        fm = re.search(name + r"\(void \*lex_inout, void \*source, int32_t (\w+)\)", suite)
        flagname = fm.group(1) if fm else "flag"
        if name in buf3:
            twin_extra = ", uint8_t *data, int32_t len"
        elif name in flag3:
            twin_extra = f", int32_t {flagname}"
        else:
            twin_extra = ""
        body = body.replace(f"{name}(", f"c_ref_{base}(", 0)  # no self-calls
        # internal calls to other migrated audits → c_ref_ forms
        for other in exports:
            if other != name:
                body = body.replace(f"{other}(", f"c_ref_{other[len('parser_asm_stretch_'):-2]}(")
        sig_line = (f"static int32_t c_ref_{base}(void *lex_inout, uint8_t *data, int32_t len) {{\n"
                    if name in buf3 else
                    f"static int32_t c_ref_{base}(void *lex_inout, void *source{twin_extra}) {{\n")
        twins.append(
            f"/* Reference twin — verbatim copy of the gated C authority for {name}. */\n"
            + sig_line
            + f"{body}\n}}\n"
        )
    missing = [n for n in exports if n not in have]
    if missing:
        print("WARN: no gated twin found for:", ", ".join(missing))

    open(TWINS, "w").write(
        "/* AUTO-GENERATED by sync_stretch_audit_harness.py — do not edit.\n"
        " * Reference twins for every migrated audit; refreshed each wave. */\n"
        + HELPERS + suite_helper_defs(suite) + "\n" + "\n".join(twins)
    )

    # 3) table: shims + rows
    rows = []
    for name in sorted(exports):
        base = name[len("parser_asm_stretch_"):-2]
        if name in buf3:
            rows.append(f'    {{"{base}", r_{base}, x_{base}, 0, 0}},')
        elif name in flag3:
            rows.append(f'    {{"{base}/1", c_ref_{base}, x_{base}, 1, 0}},')
            rows.append(f'    {{"{base}/0", c_ref_{base}, x_{base}, 0, 0}},')
        else:
            inout = 1 if name in INOUT_SET else 0
            rows.append(f'    {{"{base}", r_{base}, x_{base}, 0, {inout}}},')
    shims = []
    for name in sorted(exports):
        base = name[len("parser_asm_stretch_"):-2]
        if name in buf3:
            shims.append(
                f"static int32_t x_{base}(void *l, void *s, int32_t f) {{ (void)f; struct parser_asm_slice_u8 *sl_ = (struct parser_asm_slice_u8 *)s; if (!sl_) return 0; return {name}(l, sl_->data, (int32_t)sl_->length); }}")
            shims.append(
                f"static int32_t r_{base}(void *l, void *s, int32_t f) {{ (void)f; struct parser_asm_slice_u8 *sl_ = (struct parser_asm_slice_u8 *)s; if (!sl_) return 0; return c_ref_{base}(l, sl_->data, (int32_t)sl_->length); }}")
        elif name in flag3:
            shims.append(
                f"static int32_t x_{base}(void *l, void *s, int32_t f) {{ return {name}(l, s, f); }}")
        else:
            shims.append(
                f"static int32_t x_{base}(void *l, void *s, int32_t f) {{ (void)f; return {name}(l, s); }}")
            shims.append(
                f"static int32_t r_{base}(void *l, void *s, int32_t f) {{ (void)f; return c_ref_{base}(l, s); }}")
    externs = []
    for name in sorted(exports):
        if name in buf3:
            externs.append(f"extern int32_t {name}(void *lex_inout, uint8_t *data, int32_t len);")
        elif name in flag3:
            externs.append(f"extern int32_t {name}(void *lex_inout, void *source, int32_t flag);")
        else:
            externs.append(f"extern int32_t {name}(void *lex_inout, void *source);")
    open(TABLE, "w").write(
        "/* AUTO-GENERATED by sync_stretch_audit_harness.py — do not edit. */\n"
        + "\n".join(externs) + "\n\n"
        + "\n".join(shims)
        + "\n\nstatic const audit_case k_cases[] = {\n"
        + "\n".join(rows)
        + "\n};\n"
    )
    print(f"twins: {len(twins)}, table rows: {len(rows)} (exports {len(exports)})")
    return 0


# inout-contract audits (compare post-call end states, not immobility)
INOUT_SET = {
    "parser_asm_stretch_fn_param_list_audit_c",
    "parser_asm_stretch_skip_return_type_audit_c",
}


if __name__ == "__main__":
    sys.exit(main())
