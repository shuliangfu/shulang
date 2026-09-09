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
    defmatch = re.compile(
        r'^(int32_t|void|uint8_t\s*\*|const char\s*\*|char\s*\*|size_t|int)\s+([a-zA-Z_]\w*)\s*\('
    )
    try:
        with open(src_path, "r") as f:
            lines = f.read().split("\n")
    except OSError as e:
        sys.stderr.write(f"gen_strip_dep_bodies: read {src_path}: {e}\n")
        return 1
    out = []
    stripped = []
    i = 0
    while i < len(lines):
        line = lines[i]
        m = defmatch.match(line)
        if m and not m.group(2).startswith(prefix + "_") and not line.startswith("static"):
            name = m.group(2)
            stripped.append(name)
            j = i + 1
            while j < len(lines) and lines[j] != "}":
                j += 1
            i = j + 1
            continue
        out.append(line)
        i += 1
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
