#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for experimental → product xlang_asm copies.
# After ddf74296e the relink authority writes xlang_asm.experimental only
# unless XLANG_EXPERIMENTAL_PROMOTE_TO_PRODUCT=1. Darwin strict-fail keep /
# smoke fallback / postlink experimental fallback used to cp onto product
# unconditionally. G.7 completed that same flag at those recoveries.
# This probe does not run the copies (would overwrite product). It asserts
# every remaining experimental→product cp is gated, and docker-ci no longer
# copies. Reverse snapshot (product → experimental) is not a promote.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"

python3 - "$ROOT" <<'PY'
import os
import re
import sys

root = sys.argv[1]
# Promote copies: src is experimental, dest is product xlang_asm (not .experimental).
cp_re = re.compile(
    r"\bcp(?:\s+-f)?\s+"
    r"(?P<src>\S*xlang_asm\.experimental)\s+"
    r"(?P<dst>\S+)"
)
promote_flag = "XLANG_EXPERIMENTAL_PROMOTE_TO_PRODUCT"
allow_flag = "XLANG_ASM_ALLOW_EXPERIMENTAL_FALLBACK"
scan = [
    "compiler/scripts/build_xlang_asm.sh",
    "compiler/scripts/relink_xlang_asm_experimental_bootstrap.sh",
    "compiler/scripts/xlang_asm_postlink_smoke.sh",
    "scripts/docker-ci-local.sh",
]
gated = []
ungated = []
reverse = []
for rel in scan:
    path = os.path.join(root, rel)
    with open(path, encoding="utf-8") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        m = cp_re.search(line)
        if not m:
            continue
        src = m.group("src").strip("\"'")
        dst = m.group("dst").strip("\"'")
        # $ASM is postlink's product path (default ./xlang_asm).
        dst_is_product = (
            dst.endswith("xlang_asm")
            or dst in ("$ASM",)
            or dst.endswith("/xlang_asm")
        )
        dst_is_experimental = "experimental" in dst
        if dst_is_experimental:
            reverse.append(f"{rel}:{i+1}")
            continue
        if not dst_is_product:
            continue
        window = "".join(lines[max(0, i - 30) : i + 1])
        ok = promote_flag in window
        # Smoke-local ALLOW is the same opt-in, not a second promote path.
        if rel.endswith("build_xlang_asm.sh") and allow_flag in window:
            ok = True
        rec = f"{rel}:{i+1}"
        if ok:
            gated.append(rec)
        else:
            ungated.append(rec)

# docker-ci must not still copy experimental onto product.
docker = os.path.join(root, "scripts/docker-ci-local.sh")
with open(docker, encoding="utf-8") as f:
    docker_txt = f.read()
docker_copy = 0
for m in cp_re.finditer(docker_txt):
    dst = m.group("dst")
    if "experimental" not in dst and "xlang_asm" in dst:
        docker_copy += 1

if ungated:
    print("FAIL: ungated experimental→product cp:", file=sys.stderr)
    for rec in ungated:
        print("  " + rec, file=sys.stderr)
    sys.exit(1)
if docker_copy:
    print("FAIL: docker-ci still copies experimental onto product", file=sys.stderr)
    sys.exit(1)
# Expect the three recoveries + relink (4). Darwin keep + smoke + postlink + relink.
if len(gated) < 4:
    print("FAIL: expected >=4 gated experimental→product cp, got %d: %s"
          % (len(gated), gated), file=sys.stderr)
    sys.exit(1)
print(
    "experimental_promote_keep_smoke_postlink probe OK gated=%d ungated=0 docker_copy=0"
    % len(gated)
)
PY
