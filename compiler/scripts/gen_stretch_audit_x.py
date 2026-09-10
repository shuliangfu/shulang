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
    buf_sigs = {}
    order = []
    i = 0
    while i < len(lines):
        l = lines[i]
        m = re.match(r"^int32_t (parser_asm_stretch_\w+_c)\(struct parser_asm_lexer (\w+), "
                     r"struct parser_asm_slice_u8 \*source\) \{$", l)
        sig_extra = 0
        is_buf = False
        if not m:
            m2 = re.match(r"^int32_t (parser_asm_stretch_\w+_c)\(struct parser_asm_lexer (\w+),$", l)
            if m2 and i + 1 < len(lines):
                if re.match(r"^\s*struct parser_asm_slice_u8 \*source\) \{$", lines[i + 1]):
                    m = m2
                    sig_extra = 1
                elif re.match(r"^\s*uint8_t \*data, int32_t len\) \{$", lines[i + 1]):
                    m = m2
                    sig_extra = 1
                    is_buf = True
        if not m:
            m3 = re.match(r"^int32_t (parser_asm_stretch_\w+_c)\(struct parser_asm_lexer (\w+), "
                          r"uint8_t \*data, int32_t len\) \{$", l)
            if m3:
                m = m3
                is_buf = True
        if m:
            j = i + 1 + sig_extra
            while lines[j] != "}":
                j += 1
            funcs[m.group(1)] = lines[i + 1 + sig_extra : j]
            buf_sigs[m.group(1)] = is_buf
            order.append((i, j))
            i = j + 1
        else:
            i += 1
    return src, lines, funcs, buf_sigs, order


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


class Delegation(Exception):
    """Body is a pure delegation to another (already .x-migrated) audit."""



MIGRATED_EXPORTS_CACHE = set()


def lines_strip(l):
    return l.strip()


def translate_call(callee, arg, flag=None):
    """A sub-audit call on the caller's lexer → .x call expr (checks migrated)."""
    if callee not in MIGRATED_EXPORTS_CACHE:
        raise Refuse(f"sub-call to unmigrated {callee}")
    if arg.lstrip("&") not in ("lex", "lex_at_if"):
        raise Refuse(f"sub-call on non-cursor var {arg}")
    tail = f", {flag}" if flag is not None else ""
    return f"{callee}(lex, source{tail})", set()


def translate_loop_body(block, cur_results):
    """Uniform kind-loop body: VAR++; if (VAR > N) return VAR|0; advance; refresh."""
    used = set()
    out = []
    # counter pattern: two/three/four lines
    lines = [l.strip() for l in block if l.strip()]
    m0 = re.match(r"(\w+)\+\+;$", lines[0])
    if not (m0 and len(lines) >= 2):
        raise Refuse(f"loop body head: {lines[0][:40] if lines else 'empty'}")
    var = m0.group(1)
    out.append(f"      {var} = {var} + 1;")
    m1 = re.match(r"if \((\w+) > (\d+)\)$", lines[1])
    if not m1:
        m1 = re.match(r"if \((\w+) > (\d+)\) return (\w+|\d+);$", " ".join(lines[1:2]))
        if m1:
            lines = lines[:1] + [f"if ({m1.group(1)} > {m1.group(2)})", f"return {m1.group(3)};"] + lines[2:]
    if m1 and m1.group(1) == var:
        if lines[2] in ("return %s;" % var, "return 0;"):
            out.append(f"      if ({var} > {m1.group(2)}) {{")
            out.append("        parser_asm_lex_set_pos_c(lex, pos0);")
            out.append("        parser_asm_lex_set_line_c(lex, line0);")
            out.append("        parser_asm_lex_set_col_c(lex, col0);")
            out.append(f"        return {lines[2].replace('return ', '').rstrip(';')};")
            out.append("      }")
            rest = lines[3:]
        else:
            raise Refuse("loop bail form")
    else:
        rest = lines[1:]
    for t in rest:
        if t == "parser_asm_lex_from_result_val_into(&lex, r);":
            out.append("      parser_asm_lex_step_kind_c(lex, source);")
            out.append("      kind = parser_asm_lex_peek_kind_c(lex, source);")
            continue
        if t == "lexer_next_into(&r, lex, source);":
            out.append("      kind = parser_asm_lex_peek_kind_c(lex, source);")
            continue
        raise Refuse(f"loop body stmt: {t[:40]}")
    return out, used


def translate_guard_loop(block, cur_results):
    """for(;;) { if (guard++ > N) ...; <standard statements> } → while(guard<=N){guard++;...}"""
    used = set()
    lines = [l.strip() for l in block if l.strip()]
    m = re.match(r"if \((\w+)\+\+ > (\d+)\) return (\w+|\d+);$", lines[0])
    if m:
        gvar, limit = m.group(1), m.group(2)
        lines = [f"if ({gvar}++ > {limit})", f"return {m.group(3)};"] + lines[1:]
    m = re.match(r"if \((\w+)\+\+ > (\d+)\)$", lines[0])
    if not (m and lines[1] in ("return 0;", "return guard;", "return %s;" % m.group(1))):
        raise Refuse("guard loop head")
    gvar, limit = m.group(1), m.group(2)
    out = [f"    while ({gvar} <= {limit}) {{", f"      {gvar} = {gvar} + 1;"]
    body_x, ntok = translate_block(block[2:], cur_results, indent=3)
    used |= ntok
    out.extend(body_x)
    out.append("    }")
    out.append("    parser_asm_lex_set_pos_c(lex, pos0);")
    out.append("    parser_asm_lex_set_line_c(lex, line0);")
    out.append("    parser_asm_lex_set_col_c(lex, col0);")
    out.append("    return 0;")
    return out, used


def translate_switch(groups):
    """Case groups → if/else-if chain over `kind`."""
    used = set()
    out = []
    for gi, (kinds, body) in enumerate(groups):
        if not kinds and not body:
            continue  # empty default
        cond = " || ".join(f"kind == {k}" for k in kinds)
        for k in kinds:
            used.add(k)
        head = f"if ({cond}) {{" if gi == 0 else f"}} else if ({cond}) {{"
        out.append("    " + head)
        for raw in body:
            t = raw.strip()
            m = re.match(r"(\w+) \+= (\d+);$", t)
            if m:
                out.append(f"      {m.group(1)} = {m.group(1)} + {m.group(2)};")
                continue
            m = re.match(r"\(void\)(parser_asm_stretch_\w+_c)\((&?\w+), source(?:, (\d+))?\);$", t)
            if m:
                x2, ntok = translate_call(m.group(1), m.group(2), m.group(3))
                used |= ntok
                out.append(f"      {x2};")
                continue
            m = re.match(r"\(void\)(parser_asm_stretch_bind_name_validate_c)\(source->data \+ "
                         r"(r\w*)\.token_start, (r\w*)\.tok\.ident_len\);$", t)
            if m:
                out.append("      idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);")
                out.append("      parser_asm_stretch_bind_name_validate_c(idptr, idlen);")
                continue
            raise Refuse(f"switch body stmt: {t[:50]}")
    if out:
        out.append("    }")
    return out, used


def join_logical(body):
    """Merge continuation lines: a logical statement ends at a line whose
    stripped form ends with ; { or } (or is a case/default label)."""
    out = []
    buf = []
    for l in body:
        if not l.strip() and not buf:
            out.append(l)
            continue
        buf.append(l)
        t = " ".join(x.strip() for x in buf).strip()
        if t.endswith(";") or t.endswith("{") or t.endswith("}") or t.endswith(":"):
            out.append(" ".join(x.strip() for x in buf))
            buf = []
    if buf:
        out.append(" ".join(x.strip() for x in buf))
    return out


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
    cursor_names = {"lex"}
    # accept any by-value lexer param name as the cursor (lex_at_if etc.)
    for ln in body[:0]:
        pass

    def emit(s):
        x.append("    " + s)

    def kind_read(res):
        return "kind"

    si = 0
    stmts = join_logical(body)
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
            si += 1
            continue
        m = re.match(r"(\w+) = 0;$", st)
        if m and m.group(1) in int_vars:
            emit(f"{m.group(1)} = 0;")
            si += 1
            continue
        # null source guard (template covers it)
        if st == "if (!source) return 0;":
            si += 1
            continue
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
            body_x, ntok2 = translate_block(block, cur_results, indent=2)
            used |= ntok2
            emit(f"if ({cond_x}) {{")
            x.extend(body_x)
            emit("}")
            si = j + 1
            continue
        if st.startswith("else"):
            raise Refuse("else branch")
        # v2: score arithmetic from sub-audit calls or literals
        m = re.match(r"(\w+) (\+=|=) (parser_asm_stretch_\w+_c)\((&?\w+), source(?:, (\d+))?\);$", st)
        if m and m.group(1) in int_vars:
            var, op, callee, arg = m.group(1), m.group(2), m.group(3), m.group(4)
            x2, ntok = translate_call(callee, arg, m.group(5))
            used |= ntok
            if op == "+=":
                emit(f"{var} = {var} + {x2};")
            else:
                emit(f"{var} = {x2};")
            si += 1
            continue
        m = re.match(r"(\w+) \+= (\d+);$", st)
        if m and m.group(1) in int_vars:
            emit(f"{m.group(1)} = {m.group(1)} + {m.group(2)};")
            si += 1
            continue
        # v2: discarded sub-audit call
        m = re.match(r"\(void\)(parser_asm_stretch_\w+_c)\((&?\w+|r\w*\.next_lex), source(?:, (\d+))?\);$", st)
        if m:
            arg = m.group(2)
            if arg.startswith("r"):  # rX.next_lex → step to that position first
                emit("parser_asm_lex_step_kind_c(lex, source);")
                arg = "lex"
                cur_results = set()
            x2, ntok = translate_call(m.group(1), arg, m.group(3))
            used |= ntok
            emit(f"{x2};")
            si += 1
            continue
        # v2: bind_name_validate on the current ident
        m = re.match(r"\(void\)(parser_asm_stretch_bind_name_validate_c)\(source->data \+ "
                     r"(r\w*)\.token_start, (r\w*)\.tok\.ident_len\);$", st)
        if m and m.group(2) in cur_results and m.group(3) in cur_results:
            emit("idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);");
            emit("parser_asm_stretch_bind_name_validate_c(idptr, idlen);")
            si += 1
            continue
        # v2: helper adapter with discarded result (`after` unused later)
        m = re.match(r"parser_asm_stretch_skip_balanced_brackets_into_c\(&\w+, (r\w*)\.next_lex, source\);$", st)
        if m and m.group(1) in cur_results:
            emit("parser_asm_lex_step_kind_c(lex, source);")
            emit("parser_asm_lex_skip_balanced_brackets_inplace_c(lex, source);")
            emit("kind = parser_asm_lex_peek_kind_c(lex, source);")
            cur_results = set()
            si += 1
            continue
        # v2.1: kinds-array delegator (delegates to expr_binop_kinds_probe with a
        # static kind list) → inline the probe's uniform loop, OR-cond unrolled
        m = re.match(r"static const int32_t kinds\[\d+\] = \{((?:\(int32_t\)TOKEN_\w+(?:, )?)+)\};$", st)
        if m:
            kinds = re.findall(r"TOKEN_\w+", m.group(1))
            if si + 1 < len(stmts):
                nxt = stmts[si + 1].strip()
                m2 = re.match(r"return parser_asm_stretch_expr_binop_kinds_probe_c\(lex, source, kinds, \d+\);$", nxt)
                if m2:
                    used |= set(kinds)
                    cond = " || ".join(f"kind == {k}" for k in kinds)
                    emit("kind = parser_asm_lex_peek_kind_c(lex, source);")
                    emit(f"while ({cond}) {{")
                    emit("  n = n + 1;")
                    emit("  if (n > 32) {")
                    emit("    parser_asm_lex_set_pos_c(lex, pos0);")
                    emit("    parser_asm_lex_set_line_c(lex, line0);")
                    emit("    parser_asm_lex_set_col_c(lex, col0);")
                    emit("    return n;")
                    emit("  }")
                    emit("  parser_asm_lex_step_kind_c(lex, source);")
                    emit("  kind = parser_asm_lex_peek_kind_c(lex, source);")
                    emit("}")
                    emit("parser_asm_lex_set_pos_c(lex, pos0);")
                    emit("parser_asm_lex_set_line_c(lex, line0);")
                    emit("parser_asm_lex_set_col_c(lex, col0);")
                    emit("return n;")
                    int_vars.add("n")
                    si += 2
                    continue
            raise Refuse("kinds array without probe delegation")
        # v2.1: from_result advance (≡ step + refresh)
        m = re.match(r"parser_asm_lex_from_result_val_into\(&(\w+), (r\w*)\);$", st)
        if m and m.group(2) in cur_results and m.group(1) in cursor_names:
            emit("parser_asm_lex_step_kind_c(lex, source);")
            emit("kind = parser_asm_lex_peek_kind_c(lex, source);")
            if any(f"{m.group(2)}.tok.ident_len" in s2 for s2 in stmts):
                emit("idlen = parser_asm_lex_peek_ident_len_c(lex, source);")
            cur_results = set()
            si += 1
            continue
        # v2.1: kind-membership while loop (uniform counter pattern)
        m = re.match(r"while \((r\w*)\.tok\.kind == (.+)\) \{$", st)
        if m and m.group(1) in cur_results:
            cond_rest = m.group(2)
            # loop body until lone '}'
            j = si + 1
            depth = 1
            body_l = []
            while depth > 0:
                t = stmts[j].strip()
                depth += t.count("{") - t.count("}")
                if depth == 0:
                    break
                body_l.append(stmts[j])
                j += 1
            cond_x, ntok = translate_cond(f"{m.group(1)}.tok.kind == " + cond_rest, cur_results)
            used |= ntok
            body_x, ntok2 = translate_loop_body(body_l, cur_results)
            used |= ntok2
            emit(f"while ({cond_x}) {{")
            x.extend(body_x)
            emit("}")
            si = j + 1
            continue
        # v2.1: guard bail loop for (;;) { if (guard++ > N) return 0; ... }
        if st == "for (;;) {":
            j = si + 1
            depth = 1
            body_l = []
            while depth > 0:
                t = stmts[j].strip()
                depth += t.count("{") - t.count("}")
                if depth == 0:
                    break
                body_l.append(stmts[j])
                j += 1
            body_x, ntok2 = translate_guard_loop(body_l, cur_results)
            used |= ntok2
            x.extend(body_x)
            si = j + 1
            continue
        # v2: switch on the current token kind → if/else chain
        m = re.match(r"switch \((r\w*)\.tok\.kind\) \{$", st)
        if m and m.group(1) in cur_results:
            j = si + 1
            groups = []  # [([kinds], [body lines])]
            while stmts[j].strip() != "}":
                t = stmts[j].strip()
                cm = re.match(r"case \(int32_t\)(TOKEN_\w+):$", t)
                if cm:
                    if groups and not groups[-1][1]:
                        groups[-1][0].append(cm.group(1))  # fallthrough group
                    else:
                        groups.append(([cm.group(1)], []))
                elif t == "default:":
                    if not groups or groups[-1][1]:
                        groups.append(([], []))  # default marker (empty kinds)
                elif t == "break;":
                    pass
                else:
                    if not groups:
                        raise Refuse(f"switch stmt before case: {t[:40]}")
                    groups[-1][1].append(stmts[j])
                j += 1
            sw_lines, ntok = translate_switch(groups)
            used |= ntok
            x.extend(sw_lines)
            si = j + 1
            continue
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
    return x, used, int_vars


def tok_of(name):
    return name


def translate_cond(cond, cur_results):
    """C condition on current-token fields → .x condition."""
    used = set()
    c = cond
    c = re.sub(r"\(int32_t\)", "", c)
    # suite helper names → bridge faces callable from .x
    # bare int-returning helper call as condition → wrap with != 0
    # (.x: if condition must be bool, no implicit int-to-bool)
    c = re.sub(r"(?<![\w!!=])parser_asm_stretch_is_type_start_kind_c\([^()]*\)(?!\s*!=)",
               lambda m: "(" + m.group(0).replace(
                   "parser_asm_stretch_is_type_start_kind_c",
                   "parser_asm_lex_is_type_start_kind_c") + " != 0)", c)
    for res in cur_results | {"r", "r2"}:
        c = c.replace(f"{res}.tok.kind", "kind")
        c = c.replace(f"{res}.tok.ident_len", "idlen")
    if ".tok." in c or ".next_lex" in c or "source->" in c:
        # maybe references a non-current result var
        raise Refuse(f"cond on stale result: {cond[:50]}")
    for m in re.finditer(r"TOKEN_\w+", c):
        used.add(m.group(0))
    return c.strip(), used


PURE_HELPERS = {
    # pure scalar helpers the .x side may extern directly (no struct params)
    "parser_asm_is_compound_assign_token_c": ("kind: i32", "i32"),
    "parser_asm_stretch_bind_name_validate_c": ("name: *u8, name_len: i32", "i32"),
    "parser_asm_stretch_ident_byte_ok_c": ("c: u8, is_first: i32", "i32"),
}


def translate_return(expr, cur_results):
    """return EXPR → restore trio + computed return (2-4 lines)."""
    used = set()
    e = expr.strip()
    # delegation: return CALLEE(ARG, source);  where ARG is lex/&lex/lex_at_if...
    m = re.match(r"(parser_asm_stretch_\w+_c)\((r\w*)\.next_lex, source(?:, (\d+))?\)$", e)
    if m and m.group(2) in cur_results:
        x2, ntok = translate_call(m.group(1), "lex", m.group(3))
        used |= ntok
        return (
            [
                "      parser_asm_lex_step_kind_c(lex, source);",
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      return {x2};",
            ],
            used,
        )
    m = re.match(r"(parser_asm_stretch_\w+_c)\((?:&?lex|&?lex_at_if), source(?:, (\d+))?\)$", e)
    if m and m.group(2) is None:
        raise Delegation(m.group(1))
    m2 = re.match(r"(\w+) \+ (parser_asm_stretch_\w+_c)\((r\w*)\.next_lex, source(?:, (\d+))?\)$", e)
    if m2 and m2.group(3) in cur_results:
        x2, ntok = translate_call(m2.group(2), "lex", m2.group(4))
        used |= ntok
        return (
            [
                "      parser_asm_lex_step_kind_c(lex, source);",
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      return {m2.group(1)} + {x2};",
            ],
            used,
        )
    # pure-call ternary: return HELPER(args) ? 1 : 0;
    m = re.match(r"(\w+)\(([^()]*)\) \? 1 : 0$", e)
    if m and m.group(1) in PURE_HELPERS:
        fn, args = m.group(1), m.group(2)
        ax = []
        for a in args.split(","):
            a = a.strip()
            a = a.replace("r.tok.kind", "kind").replace("r2.tok.kind", "kind")
            a = re.sub(r"^&", "", a)
            ax.append(a)
        sig_args = " ".join(
            f"p{i}" for i in range(len(ax))
        )
        return (
            [
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      if ({fn}({', '.join(ax)}) != 0) {{",
                "        return 1;",
                "      }",
                "      return 0;",
            ],
            used,
        )
    # score-expression returns: score / score + N / score + CALL(lex)
    m = re.match(r"(\w+)(?: \+ (\d+))?$", e)
    if m and m.group(1) not in ("0", "1"):
        var, add = m.group(1), m.group(2)
        expr = var if not add else f"{var} + {add}"
        return (
            [
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      return {expr};",
            ],
            used,
        )
    m = re.match(r"(\w+) \+ (parser_asm_stretch_\w+_c)\((&?\w+), source(?:, (\d+))?\)$", e)
    if m:
        x2, ntok = translate_call(m.group(2), m.group(3), m.group(4))
        used |= ntok
        return (
            [
                "      parser_asm_lex_set_pos_c(lex, pos0);",
                "      parser_asm_lex_set_line_c(lex, line0);",
                "      parser_asm_lex_set_col_c(lex, col0);",
                f"      return {m.group(1)} + {x2};",
            ],
            used,
        )
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


def translate_block(block, cur_results, indent=2):
    """Statements inside an if-branch: returns (with restore), score ops,
    discarded sub-audit calls, bind-validate on current ident."""
    used = set()
    out = []
    pad = "    " * indent
    for raw in block:
        st = raw.strip()
        m = re.match(r"return (.+);$", st)
        if m:
            rlines, ntok = translate_return(m.group(1), cur_results)
            used |= ntok
            for l in rlines:
                out.append(pad + l.strip() if l.strip() else l)
            continue
        m = re.match(r"(\w+) \+= (\d+);$", st)
        if m:
            out.append(f"{pad}{m.group(1)} = {m.group(1)} + {m.group(2)};")
            continue
        m = re.match(r"\(void\)(parser_asm_stretch_\w+_c)\((&?\w+), source(?:, (\d+))?\);$", st)
        if m:
            x2, ntok = translate_call(m.group(1), m.group(2), m.group(3))
            used |= ntok
            out.append(f"{pad}{x2};")
            continue
        m = re.match(r"\(void\)(parser_asm_stretch_bind_name_validate_c)\(source->data \+ "
                     r"(r\w*)\.token_start, (r\w*)\.tok\.ident_len\);$", st)
        if m and m.group(2) in cur_results and m.group(3) in cur_results:
            out.append(f"{pad}idptr = parser_asm_lex_peek_ident_ptr_c(lex, source);")
            out.append(f"{pad}parser_asm_stretch_bind_name_validate_c(idptr, idlen);")
            continue
        if st == "lexer_next_into(&r2, r.next_lex, source);" or st == "lexer_next_into(&r, r.next_lex, source);":
            out.append(f"{pad}parser_asm_lex_step_kind_c(lex, source);")
            out.append(f"{pad}kind = parser_asm_lex_peek_kind_c(lex, source);")
            continue
        m = re.match(r"(\w+)\+\+;$", st)
        if m:
            out.append(f"{pad}{m.group(1)} = {m.group(1)} + 1;")
            continue
        # nested single-stmt if: if (rX.tok.kind COND) VAR++;
        m = re.match(r"if \((r\w*)\.tok\.kind (.+?)\) (\w+)\+\+;$", st)
        if m:
            cond_x, ntok = translate_cond(f"{m.group(1)}.tok.kind {m.group(2)}", {m.group(1)})
            used |= ntok
            out.append(f"{pad}if ({cond_x}) {{")
            out.append(f"{pad}  {m.group(3)} = {m.group(3)} + 1;")
            out.append(f"{pad}}}")
            continue
        raise Refuse(f"stmt in if-block: {st[:50]}")
    return out, used


def gen_x_function(name, body, tokvals, existing_consts, buftail_mode=False):
    if buftail_mode:
        body = [l.replace("&sl)", "source)").replace(", source);", ", source);")
                for l in body]
        body = [re.sub(r"lexer_next_into\(&(r\w*), ([^,]+), source\)",
                       r"lexer_next_into(\1, \2, source)", l) for l in body]
    lines, used, int_vars = translate(name, body, tokvals)
    # completeness pre-check: append missing TOKEN_* consts (wave-3 lesson)
    missing = sorted(t for t in used if t not in existing_consts)
    return lines, used, missing, int_vars


def gen_buf_function(name, body, tokvals, existing_consts):
    """buf-signature audit: strip the sl-construction prologue, translate the
    rest with source = wrap(data,len). Pure shims return (…, buftail=callee)."""
    txt = "\n".join(body)
    # pure shim: sl decl + guard + assigns + return CALLEE(&lex, &sl);
    m = re.fullmatch(
        r"\s*struct parser_asm_slice_u8 sl;\s*if \(!data \|\| len <= 0\)\s*return 0;\s*"
        r"sl\.data = data;\s*sl\.length = \(size_t\)len;\s*"
        r"return (parser_asm_stretch_\w+_c)\(&\w+, &sl\);\s*", txt)
    if m:
        raise Delegation(m.group(1))
    raise Refuse("thick buf body (v3.1 scope)")


def emit_buf_x(name, callee, docline):
    """Thin buf shim: wrap + delegate to the slice-based .x audit."""
    return f"""/**
 * {docline}
 * Generated buf-shim port: wraps (data,len) via the bridge ring and
 * delegates to the slice-based .x audit `{callee}`.
 * @param lex *u8 — opaque lexer (read-only net effect)
 * @param data *u8 — source bytes
 * @param len i32 — byte length; <=0 returns 0
 * @return i32 — callee verdict
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function {name}(lex: *u8, data: *u8, len: i32): i32 {{
  let source: *u8 = 0 as *u8;
  unsafe {{
    source = parser_asm_lex_wrap_buf_c(data, len);
    if (source == 0 as *u8) {{
      return 0;
    }}
    return {callee}(lex, source);
  }}
  return 0;
}}
"""


def emit_x(name, x_lines, docline, int_vars=()):
    int_lets = "".join(f"  let {v}: i32 = 0;\n" for v in sorted(int_vars))
    int_lets = "  let idptr: *u8 = 0 as *u8;\n" + int_lets
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
{int_lets}  if (lex == 0 as *u8 || source == 0 as *u8) {{
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
    src, lines, funcs, buf_sigs, order = parse_suite()
    tokvals = token_enum()
    xsrc = open(XFILE).read()
    existing = set(re.findall(r"const (TOKEN_\w+):", xsrc))

    ok, refused, gen, deleg = [], [], [], []
    all_missing = []
    # set of .x-migrated exports (hand + generated) for delegation unlocking
    migrated_exports = set(re.findall(r"export function (parser_asm_stretch_\w+_c)", xsrc))
    MIGRATED_EXPORTS_CACHE.clear()
    MIGRATED_EXPORTS_CACHE.update(migrated_exports)
    for n in names:
        if n not in funcs:
            refused.append((n, "not found / non-byval signature"))
            continue
        is_buf = buf_sigs.get(n, False)
        try:
            if is_buf:
                x_lines, used, missing, ivars, buftail = gen_buf_function(
                    n, funcs[n], tokvals, existing)
            else:
                x_lines, used, missing, ivars = gen_x_function(n, funcs[n], tokvals, existing)
                buftail = None
            for t in missing:
                existing.add(t)
            all_missing.extend(missing)
            gen.append((n, x_lines, ivars, buftail))
            ok.append(n)
        except Delegation as d:
            if str(d) in migrated_exports:
                deleg.append((n, str(d), buf_sigs.get(n, False)))
                ok.append(n)
            else:
                refused.append((n, f"delegation to unmigrated {d}"))
        except Refuse as e:
            refused.append((n, str(e)))

    if not gen and not deleg:
        print("nothing generated")
        for n, why in refused:
            print(f"  REFUSED {n}: {why}")
        return 1

    # 1a) bridge externs used by generated bodies but not yet declared
    BRIDGE_EXTERNS = {
        "parser_asm_lex_peek_ident_ptr_c": "lex: *u8, source: *u8): *u8",
        "parser_asm_lex_wrap_buf_c": "data: *u8, len: i32): *u8",
        "parser_asm_lex_source_data_c": "source: *u8): *u8",
        "parser_asm_lex_source_length_c": "source: *u8): usize",
    }
    for bname, bsig in BRIDGE_EXTERNS.items():
        if bname in xsrc:
            continue
        if any(bname in line for item in gen for line in item[1]):
            lines_x = xsrc.split("\n")
            lastext = max(i for i, l in enumerate(lines_x) if l.startswith("export extern"))
            lines_x.insert(lastext + 1,
                           f'export extern "C" function {bname}({bsig};')
            xsrc = "\n".join(lines_x)
            print("bridge extern added:", bname)

    # 1b) pure-helper externs used by generated bodies
    used_helpers = sorted(
        h for h in PURE_HELPERS if any(h in line for item in gen for line in item[1])
    )
    if used_helpers:
        lines_x = xsrc.split("\n")
        lastext = max(i for i, l in enumerate(lines_x) if l.startswith("export extern"))
        add = [
            f'export extern "C" function {h}({PURE_HELPERS[h][0]}): {PURE_HELPERS[h][1]};'
            for h in used_helpers
        ]
        lines_x[lastext + 1 : lastext + 1] = add
        xsrc = "\n".join(lines_x)
        print("helper externs added:", ", ".join(used_helpers))

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
    for n, x_lines, ivars, buftail in gen:
        docmap[n] = f"Generated audit port {n}."
        if buftail:
            frags.append(emit_buf_x(n, buftail, docmap[n]))
        else:
            sig_extra = ""
            frags.append(emit_x(n, x_lines, docmap[n], ivars))
    for n, callee, is_b in list(deleg):
        if is_b:
            frags.append(emit_buf_x(n, callee, f"Generated buf-shim port {n}."))
            continue
        frags.append(
            f"/**\n"
            f" * Generated delegation port: {n} forwards to {callee}.\n"
            f" * Pointer ABI + by-value net semantics (callee restores).\n"
            f" * @param lex *u8 — opaque lexer (read-only net effect)\n"
            f" * @param source *u8 — opaque slice\n"
            f" * @return i32 — callee verdict\n"
            f" * PLATFORM: SHARED.\n"
            f" */\n"
            f"#[no_mangle]\n"
            f"export function {n}(lex: *u8, source: *u8): i32 {{\n"
            f"  unsafe {{\n"
            f"    return {callee}(lex, source);\n"
            f"  }}\n"
            f"  return 0;\n"
            f"}}\n"
        )
    if frags:
        xsrc = xsrc.rstrip("\n") + "\n\n/* ── generated (gen_stretch_audit_x.py) ── */\n\n" + "\n".join(frags)
    open(XFILE, "w").write(xsrc)

    # 3) C twins → gated pointer ABI (line-anchored splice, wave-2 proven)
    lines_s = open(SUITE).read().split("\n")
    for n, *_rest in list(gen) + [(d[0], d[1]) for d in deleg]:
        body = funcs[n]
        # locate def block (single- or multi-line signature)
        si_l = sig_extra = None
        for i2, l in enumerate(lines_s):
            if l.startswith(f"int32_t {n}(struct parser_asm_lexer "):
                if l.rstrip().endswith("{"):
                    si_l, sig_extra = i2, 0
                elif (i2 + 1 < len(lines_s)
                      and lines_s[i2 + 1].rstrip().endswith("{")
                      and not l.rstrip().endswith(";")):
                    si_l, sig_extra = i2, 1
                if si_l is not None:
                    break
        is_buf_def = n in buf_sigs and buf_sigs[n]
        if si_l is None:
            print(f"FATAL: def line missing for {n}"); sys.exit(1)
        param_name = lines_s[si_l].split("(")[1].split(",")[0].replace("struct parser_asm_lexer", "").strip()
        ei_l = si_l + 1 + sig_extra + len(body)  # index of closing '}'
        assert lines_s[ei_l] == "}", (n, lines_s[ei_l])
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
        nb_txt = nb_txt.replace("source->data", "((struct parser_asm_slice_u8 *)source)->data")
        nb_txt = nb_txt.replace("source->length", "((struct parser_asm_slice_u8 *)source)->length")
        shim = (
            "/* B-minus twin (7.2.1, generated): hybrid lane compiles this out; .x\n"
            " * authority src/asm/pthin_stretch_audit.x provides the same symbol\n"
            " * (pointer ABI + by-value net semantics). Cold lane keeps this twin. */\n"
            "#ifndef XLANG_PTHIN_STRETCH_AUDIT_FROM_X\n"
            + (f"int32_t {n}(void *lex_inout, uint8_t *data, int32_t len) {{\n" if is_buf_def
               else f"int32_t {n}(void *lex_inout, void *source) {{\n")
            + f"  struct parser_asm_lexer {param_name};\n"
            + ("  if (!lex_inout || !data || len <= 0)\n    return 0;\n" if is_buf_def
               else "  if (!lex_inout || !source)\n    return 0;\n")
            + f"  {param_name} = *(struct parser_asm_lexer *)lex_inout;\n"
            + nb_txt + "\n}\n#endif"
        )
        lines_s[si_l : ei_l + 1] = shim.split("\n")
    # 3b) ensure fwd decls exist for every generated function (hybrid callers)
    need = []
    for n, *_rest in list(gen) + list(deleg):
        decl = (f"int32_t {n}(void *lex_inout, uint8_t *data, int32_t len);"
                if buf_sigs.get(n) else f"int32_t {n}(void *lex_inout, void *source);")
        if decl not in "\n".join(lines_s):
            need.append(decl)
    if need:
        anchor_line = "int32_t parser_asm_stretch_if_header_audit_c(void *lex_inout, void *source);"
        ai = lines_s.index(anchor_line)
        lines_s[ai + 1 : ai + 1] = need
    open(SUITE, "w").write("\n".join(lines_s))

    # 4) decl + call-site sync across seeds/slices (wave 1-3 proven pattern)
    import glob
    files = ["seeds/parser_asm_thin_c.from_x.c", "seeds/pthin_stretch.from_x.c"] \
            + glob.glob("seeds/pthin_*.from_x.c") + glob.glob("seeds/parser_asm/*.inc")
    for n in ok:
        is_buf_def = buf_sigs.get(n, False)
        for fp in files:
            try:
                t = open(fp).read()
            except FileNotFoundError:
                continue
            orig = t
            t = re.sub(
                r"(extern\s+)?int32_t " + re.escape(n) + r"\(struct parser_asm_lexer lex, struct parser_asm_slice_u8 \*source\);",
                lambda m, n=n: (m.group(1) or "") + f"int32_t {n}(void *lex_inout, void *source);", t)
            # generic: call sites with a by-value first arg (not &x, not a decl)
            t = re.sub(
                re.escape(n) + r"\((?!&|struct|void )([^,()]+),",
                lambda m: f"{n}(&{m.group(1)},", t)
            if is_buf_def:
                t = re.sub(
                    r"(extern\s+)?int32_t\s+" + re.escape(n) + r"\(struct\s+parser_asm_lexer\s+\w+,\s*uint8_t\s+\*data,\s*int32_t\s+len\);",
                    lambda m, n=n: (m.group(1) or "") + f"int32_t {n}(void *lex_inout, uint8_t *data, int32_t len);", t)
            # decl fixups (single- and multi-line, byval + inout forms)
            t = re.sub(
                r"(extern\s+)?int32_t\s+" + re.escape(n) + r"\(struct\s+parser_asm_lexer\s+\w+,\s*struct\s+parser_asm_slice_u8\s+\*source\);",
                lambda m, n=n: (m.group(1) or "") + f"int32_t {n}(void *lex_inout, void *source);", t)
            t = re.sub(
                r"(extern\s+)?int32_t\s+" + re.escape(n) + r"\(struct\s+parser_asm_lexer\s+\*inout_lex,\s*struct\s+parser_asm_slice_u8\s+\*source\);",
                lambda m, n=n: (m.group(1) or "") + f"int32_t {n}(void *lex_inout, void *source);", t)
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
