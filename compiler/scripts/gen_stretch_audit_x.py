#!/usr/bin/env python3
# gen_stretch_audit_x.py — 7.2.1 B-minus generator v1 (RFC §5a/§5c/§5d)
#
# Translates LINEAR LEAF audit functions from the suite slice into B-minus
# .x ports (in-place cursor model: peek reads the current token, step
# advances; snapshot/restore trio reproduces the by-value contract).
#
# Coverage (v1): by-value lexer audits whose bodies are a linear chain of
#   lexer_next_into + kind/ident_len checks + returns. Anything else
#   (loops, saved-lexer backtracking, array params, buf params, out params,
#   helper calls, lexer_result params) is REFUSED with a reason — never
#   force-translated. Refused functions stay C and migrate by hand later.
#
# Outputs (in-place):
#   src/asm/pthin_stretch_audit.x            — .x port appended
#   seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc
#                                            — C twin → gated pointer ABI
#   (decl/call-site sync across seeds is done by the wave driver sed, same
#    as waves 1–3; twins.h/harness rows by the driver too)
#
# Completeness pre-check (wave-3 lesson): every TOKEN_* referenced by a
# translated body must exist in the .x constant set — missing ones are
# appended automatically from the include/token.h authority enum.
#
# PLATFORM: SHARED (generator runs on the host; output is SHARED freestanding).

import re
import sys

SUITE = "seeds/parser_asm/parser_asm_emit_heavy_stretch_suite_slice.inc"
XFILE = "src/asm/pthin_stretch_audit.x"
TOKEN_H = "include/token.h"


def parse_suite():
    src = open(SUITE).read()
    lines = src.split("\n")
    funcs = {}
    order = []
    i = 0
    while i < len(lines):
        l = lines[i]
        m = re.match(r"^int32_t (parser_asm_stretch_\w+_c)\((struct parser_asm_lexer lex, "
                     r"struct parser_asm_slice_u8 \*source)\) \{$", l)
        if m:
            j = i + 1
            while lines[j] != "}":
                j += 1
            funcs[m.group(1)] = lines[i + 1 : j]
            order.append((i, j))
            i = j + 1
        else:
            i += 1
    return src, lines, funcs, order


def token_enum():
    src = open(TOKEN_H).read()
    m = re.search(r"typedef enum TokenKind\s*\{(.*?)\}\s*TokenKind;", src, re.S)
    body = re.sub(r"/\*.*?\*/", "", m.group(1), flags=re.S)
    entries = [e.strip() for e in body.split(",") if e.strip()]
    out = {}
    for idx, e in enumerate(entries):
        name = e.split("=")[0].strip()
        out[name] = idx
    return out


class Refuse(Exception):
    pass


def translate(name, body, tokvals):
    """C statement list → .x statement list (inside unsafe). Linear model:
    cursor = caller's lex; first lexer_next_into from `lex` = peek; each
    subsequent step from *.next_lex = step + peek. Returns (x_lines, used_tokens)."""
    x = []
    used = set()
    int_vars = set()
    advanced = set()  # result vars whose .next_lex is "the cursor position"
    first_step_done = False
    cur_results = set()  # result vars holding the CURRENT token

    def emit(s):
        x.append("    " + s)

    def kind_read(res):
        return "kind"

    si = 0
    stmts = body
    while si < len(stmts):
        st = stmts[si].strip()
        # blank / decls
        if not st or st.startswith("/*") or st.startswith("*"):
            si += 1
            continue
        if st.startswith("struct parser_asm_lexer_result "):
            si += 1
            continue
        m = re.match(r"int32_t (\w+);$", st)
        if m:
            int_vars.add(m.group(1))
            x.append(f"  let {m.group(1)}: i32 = 0;")
            si += 1
            continue
        m = re.match(r"(\w+) = 0;$", st)
        if m and m.group(1) in int_vars:
            emit(f"{m.group(1)} = 0;")
            si += 1
            continue
        # null source guard (template covers it)
        if st == "if (!source)":
            if stmts[si + 1].strip() != "return 0;":
                raise Refuse("complex null guard")
            si += 2
            continue
        # lexer step
        m = re.match(r"lexer_next_into\(&(r\w*), ([^,]+), source\);$", st)
        if m:
            res, srcvar = m.group(1), m.group(2)
            reads_ident = any(f"{res}.tok.ident_len" in s for s in stmts)
            if srcvar == "lex" and not first_step_done:
                emit("kind = parser_asm_lex_peek_kind_c(lex, source);")
                if reads_ident:
                    emit("idlen = parser_asm_lex_peek_ident_len_c(lex, source);")
                first_step_done = True
                cur_results = {res}
                si += 1
                continue
            if srcvar == "lex" and first_step_done:
                raise Refuse("second step from original lex (backtrack)")
            m2 = re.match(r"(r\w*)\.next_lex$", srcvar)
            if m2 and m2.group(1) in cur_results:
                emit("parser_asm_lex_step_kind_c(lex, source);")
                emit("kind = parser_asm_lex_peek_kind_c(lex, source);")
                if reads_ident:
                    emit("idlen = parser_asm_lex_peek_ident_len_c(lex, source);")
                cur_results = {res}
                si += 1
                continue
            raise Refuse(f"step from non-cursor var {srcvar}")
        # if conditions on the current token (braced block or single stmt)
        m = re.match(r"if \((.+)\) \{$", st)
        single = False
        if not m:
            m = re.match(r"if \((.+)\)$", st)
            single = True
        if m:
            cond = m.group(1)
            cond_x, ntok = translate_cond(cond, cur_results)
            used |= ntok
            if single:
                # controlled statement = next line only
                block = [stmts[si + 1]]
                j = si + 1
            else:
                depth = 1
                j = si + 1
                block = []
                while depth > 0:
                    t = stmts[j].strip()
                    depth += t.count("{") - t.count("}")
                    if depth == 0:
                        break
                    block.append(stmts[j])
                    j += 1
            body_x, ntok2 = translate_block_returns(block, cur_results, tokvals)
            used |= ntok2
            emit(f"if ({cond_x}) {{")
            x.extend(body_x)
            emit("}")
            si = j + 1
            continue
        if st.startswith("else"):
            raise Refuse("else branch")
        # plain return
        m = re.match(r"return (.+);$", st)
        if m:
            expr = m.group(1)
            rlines, ntok = translate_return(expr, cur_results)
            used |= ntok
            x.extend(rlines)
            si += 1
            continue
        raise Refuse(f"unhandled statement: {st[:60]}")
    return x, used


def tok_of(name):
    return name


def translate_cond(cond, cur_results):
    """C condition on current-token fields → .x condition."""
    used = set()
    c = cond
    c = re.sub(r"\(int32_t\)", "", c)
    for res in cur_results | {"r", "r2"}:
        c = c.replace(f"{res}.tok.kind", "kind")
        c = c.replace(f"{res}.tok.ident_len", "idlen")
    if ".tok." in c or ".next_lex" in c or "source->" in c:
        # maybe references a non-current result var
        raise Refuse(f"cond on stale result: {cond[:50]}")
    for m in re.finditer(r"TOKEN_\w+", c):
        used.add(m.group(0))
    return c.strip(), used


def translate_return(expr, cur_results):
    """return EXPR → restore trio + computed return (2-4 lines)."""
    used = set()
    e = expr.strip()
    tern = re.match(r"(.+)\? 1 : 0$", e)
    if tern:
        cond, ntok = translate_cond(tern.group(1), cur_results)
        used |= ntok
        return (
            [
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      if ({cond}) {{",
                "        return 1;",
                "      }",
                "      return 0;",
            ],
            used,
        )
    if e in ("0", "1"):
        return (
            [
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      return {e};",
            ],
            used,
        )
    raise Refuse(f"return expr: {e[:50]}")


def translate_block_returns(block, cur_results, tokvals):
    """Statements inside an if-block (v1: only plain returns)."""
    used = set()
    out = []
    for raw in block:
        st = raw.strip()
        m = re.match(r"return (.+);$", st)
        if not m:
            raise Refuse(f"non-return stmt in if-block: {st[:50]}")
        rlines, ntok = translate_return(m.group(1), cur_results)
        used |= ntok
        for l in rlines:
            out.append("  " + l)
    return out, used


def gen_x_function(name, body, tokvals, existing_consts):
    lines, used = translate(name, body, tokvals)
    # completeness pre-check: append missing TOKEN_* consts (wave-3 lesson)
    missing = sorted(t for t in used if t not in existing_consts)
    return lines, used, missing


def emit_x(name, x_lines, docline):
    doc = f"""/**
 * {docline}
 * B-minus generated port (gen_stretch_audit_x.py v1) of the suite twin
 * `{name}` — pointer ABI + by-value net semantics via the restore trio;
 * linear peek/step chain over the opaque lexer.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param source *u8 — opaque slice
 * @return i32 — audit verdict (≡ suite twin)
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function {name}(lex: *u8, source: *u8): i32 {{
  let pos0: usize = 0;
  let line0: i32 = 0;
  let col0: i32 = 0;
  let kind: i32 = 0;
  let idlen: i32 = 0;
  if (lex == 0 as *u8 || source == 0 as *u8) {{
    return 0;
  }}
  unsafe {{
    pos0 = parser_asm_lex_pos_c(lex);
    line0 = parser_asm_lex_line_c(lex);
    col0 = parser_asm_lex_col_c(lex);
{chr(10).join(x_lines)}
  }}
  return 0;
}}
"""
    return doc


def main():
    names = sys.argv[1:]
    if not names or names[0] in ("-h", "--help"):
        print("usage: gen_stretch_audit_x.py name1 name2 ... (suite _c names)")
        return 2
    src, lines, funcs, order = parse_suite()
    tokvals = token_enum()
    xsrc = open(XFILE).read()
    existing = set(re.findall(r"const (TOKEN_\w+):", xsrc))

    ok, refused, gen = [], [], []
    all_missing = []
    for n in names:
        if n not in funcs:
            refused.append((n, "not found / non-byval signature"))
            continue
        try:
            x_lines, used, missing = gen_x_function(n, funcs[n], tokvals, existing)
            for t in missing:
                existing.add(t)
            all_missing.extend(missing)
            gen.append((n, x_lines))
            ok.append(n)
        except Refuse as e:
            refused.append((n, str(e)))

    if not gen:
        print("nothing generated")
        for n, why in refused:
            print(f"  REFUSED {n}: {why}")
        return 1

    # 1) append missing constants after the last TOKEN_* const line
    if all_missing:
        last = max(xsrc.rfind(f"const {t}:") for t in re.findall(r"const (TOKEN_\w+):", xsrc)[:1] or ["TOKEN_EOF"])
        # insert after the last existing const line (find last const line end)
        lines_x = xsrc.split("\n")
        lastidx = max(i for i, l in enumerate(lines_x) if l.startswith("const TOKEN_"))
        add = [f"const {t}: i32 = {tokvals[t]};" for t in sorted(set(all_missing))]
        lines_x[lastidx + 1 : lastidx + 1] = add
        xsrc = "\n".join(lines_x)
        print("constants added:", ", ".join(sorted(set(all_missing))))

    # 2) append generated .x functions
    frags = []
    docmap = {}
    for n, x_lines in gen:
        # pull the C docblock line above the def for a short description
        docmap[n] = f"Generated audit port {n}."
        frags.append(emit_x(n, x_lines, docmap[n]))
    xsrc = xsrc.rstrip("\n") + "\n\n/* ── generated leaves (gen_stretch_audit_x.py v1) ── */\n\n" + "\n".join(frags)
    open(XFILE, "w").write(xsrc)

    # 3) C twins → gated pointer ABI (line-anchored splice, wave-2 proven)
    lines_s = open(SUITE).read().split("\n")
    for n, _ in gen:
        body = funcs[n]
        # locate def block: sig line index + body lines + closing '}' line
        sig = f"int32_t {n}(struct parser_asm_lexer lex, struct parser_asm_slice_u8 *source) {{"
        try:
            si_l = lines_s.index(sig)
        except ValueError:
            print(f"FATAL: def line missing for {n}"); sys.exit(1)
        ei_l = si_l + 1 + len(body)  # index of closing '}'
        assert lines_s[ei_l] == "}", n
        # transformed body: strip decls + guard (indent-aware), cast source uses
        nb = []
        skip_ret = False
        for i2, l in enumerate(body):
            ls = l.strip()
            if ls == "if (!source)":
                skip_ret = True
                continue
            if skip_ret and ls == "return 0;":
                skip_ret = False
                continue
            skip_ret = False
            nb.append(l)
        nb_txt = "\n".join(nb)
        nb_txt = re.sub(r"lexer_next_into\((&r\w*), ([^,]+), source\)",
                        r"lexer_next_into(\1, \2, (struct parser_asm_slice_u8 *)source)", nb_txt)
        shim = (
            "/* B-minus twin (7.2.1, generated): hybrid lane compiles this out; .x\n"
            " * authority src/asm/pthin_stretch_audit.x provides the same symbol\n"
            " * (pointer ABI + by-value net semantics). Cold lane keeps this twin. */\n"
            "#ifndef XLANG_PTHIN_STRETCH_AUDIT_FROM_X\n"
            f"int32_t {n}(void *lex_inout, void *source) {{\n"
            "  struct parser_asm_lexer lex;\n"
            "  if (!lex_inout || !source)\n"
            "    return 0;\n"
            "  lex = *(struct parser_asm_lexer *)lex_inout;\n"
            + nb_txt + "\n}\n#endif"
        )
        lines_s[si_l : ei_l + 1] = shim.split("\n")
    open(SUITE, "w").write("\n".join(lines_s))

    # 4) decl + call-site sync across seeds/slices (wave 1-3 proven pattern)
    import glob
    files = ["seeds/parser_asm_thin_c.from_x.c", "seeds/pthin_stretch.from_x.c"] \
            + glob.glob("seeds/pthin_*.from_x.c") + glob.glob("seeds/parser_asm/*.inc")
    for n in ok:
        for fp in files:
            try:
                t = open(fp).read()
            except FileNotFoundError:
                continue
            orig = t
            t = re.sub(
                r"(extern\s+)?int32_t " + re.escape(n) + r"\(struct parser_asm_lexer lex, struct parser_asm_slice_u8 \*source\);",
                lambda m, n=n: (m.group(1) or "") + f"int32_t {n}(void *lex_inout, void *source);", t)
            for var in ("lex", "lex_at_if", "lex_cur", "elif_lex", "fn_lex", "lex_after", "saved_lex"):
                t = t.replace(f"{n}({var},", f"{n}(&{var},")
            if t != orig:
                open(fp, "w").write(t)

    print(f"generated: {len(gen)}")
    for n in ok:
        print(f"  OK {n}")
    for n, why in refused:
        print(f"  REFUSED {n}: {why}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
