#!/usr/bin/env python3
"""gen_strip_dep_bodies.py — strip co-emitted dep bodies from a -lib-name -E gen.

7.4.4 v3 follow-up (driver_gen regeneration): `xlang_asm -x -E -lib-name
<P> ...` emits the entry module's own functions with the <P>_ prefix while
co-emitted import-dep bodies (std.sys etc.) keep their bare provider names.
Those dep bodies clash with the real providers already on the product link
(seed_link_compat.o / std modules). This tool removes every top-level
NON-STATIC function definition whose name does not start with <PREFIX>_,
keeping the extern declarations so internal calls resolve against the real
providers at link time. The result reproduces the retired -E-extern
semantics from the live product compiler.

Usage: gen_strip_dep_bodies.py <PREFIX> <in.c> <out.c>
Exit: 0 ok (report on stderr); 1 usage/IO error.
PLATFORM: SHARED (python3; repo already ships verify_comment_prefixes.py).
"""
import re
import sys


def main() -> int:
    if len(sys.argv) != 4:
        sys.stderr.write("usage: gen_strip_dep_bodies.py <PREFIX> <in.c> <out.c>\n")
        return 1
    prefix, src_path, dst_path = sys.argv[1], sys.argv[2], sys.argv[3]
    # Generic top-level definition matcher: ANY C return type (identifiers,
    # const, pointer stars) followed by the function name and '('.
    # The original int32_t-only enumeration missed int64_t — the
    # std_sys_linux_raw_syscallN dep bodies leaked through and broke the
    # Ubuntu lane's cc self-check (undeclared xlang_panic_ calls inside
    # un-stripped dep bodies).
    # Header-accumulation stripper (robust against multi-line signatures,
    # any return type, and mixed blocks where extern decls precede defs):
    # a top-level definition = a run of column-0 lines ending in '{' whose
    # first line is not structural (extern/static/preprocessor/typedef/
    # struct/...). The function name is the identifier immediately before
    # the first '(' of the run. Non-<PREFIX>_ definitions are dropped to
    # their column-0 '}'. Replaces the return-type enumeration which missed
    # int64_t (std_sys_linux_raw_syscallN leaked; broke the Ubuntu cc gate).
    skip_prefixes = (
        "extern ", "static ", "#", "typedef ", "struct ", "enum ", "union ",
        "}", "//", "/*", "*", "return ", "if ", "while ", "switch ", "for ",
        "else", "sizeof", "PYEOF",
    )
    import re as _re
    ident_re = _re.compile(r"([A-Za-z_]\w*)\s*\(")

    lines = open(src_path).read().split("\n")
    out = []
    stripped = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        if not line.strip() or line.startswith(skip_prefixes) or line[0] in " \t":
            out.append(line)
            i += 1
            continue
        # accumulate a header run until a line ends with '{'
        run = []
        j = i
        while j < n and not lines[j].rstrip().endswith("{"):
            run.append(lines[j])
            j += 1
        if j >= n:
            out.extend(run)
            break
        run.append(lines[j])  # the '{' line
        header = " ".join(run)
        m = ident_re.search(header)
        if m and not m.group(1).startswith(prefix + "_"):
            stripped.append(m.group(1))
            k = j + 1
            while k < n and lines[k] != "}":
                k += 1
            i = k + 1  # skip past the closing brace
            continue
        out.extend(run)
        # copy the body verbatim up to the col-0 '}'
        k = j + 1
        while k < n and lines[k] != "}":
            out.append(lines[k])
            k += 1
        if k < n:
            out.append(lines[k])
        i = k + 1
    try:
        with open(dst_path, "w") as f:
            f.write("\n".join(out))
    except OSError as e:
        sys.stderr.write(f"gen_strip_dep_bodies: write {dst_path}: {e}\n")
        return 1
    sys.stderr.write(
        f"gen_strip_dep_bodies: stripped {len(stripped)} non-{prefix}_ bodies "
        f"(sample: {', '.join(stripped[:4]) or 'none'})\n"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
