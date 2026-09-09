#!/usr/bin/env bash
# PLATFORM: SHARED — 9.6.2 residual RELA + string-pool probe.
# Behavioral: p3 pointers non-NULL + first bytes; p2 integer bake=42;
# p9 empty [] = 0; p_empty interned NUL; p_long 126-byte STRING_LIT.
# Discriminator: interned payload lives in .data / __DATA (not jmp-skip .text).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_modlet_string_pool_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing XLANG=$XLANG" >&2
  exit 1
fi

run_one() {
  local name="$1"
  local expect="$2"
  local src="$DIR/${name}.x"
  local out="$WORKDIR/${name}"
  if ! "$XLANG" "$src" -o "$out" >"$WORKDIR/${name}.log" 2>&1; then
    echo "FAIL: $name compile" >&2
    cat "$WORKDIR/${name}.log" >&2
    exit 1
  fi
  set +e
  "$out"
  local rc=$?
  set -e
  if [ "$rc" != "$expect" ]; then
    echo "FAIL: $name rc=$rc expect=$expect" >&2
    exit 1
  fi
  echo "${name}=${rc}"
}

run_one p3 0
run_one p2 42
run_one p9 0
run_one p_empty 0
run_one p_long 0

# Discriminator: interned strings get TU-unique Lxmls_* labels in .data
# (Darwin nm shows _Lxmls_; ELF shows Lxmls_). Seeder leftover has none
# (jmp-skip embeds bytes in .text with no pool label).
p3bin="$WORKDIR/p3"
pool_n="$(nm "$p3bin" 2>/dev/null | grep -cE ' [Dd] _?Lxmls_' || true)"
if [ "${pool_n:-0}" -lt 2 ]; then
  echo "FAIL: p3 missing Lxmls_ pool labels (nm count=${pool_n:-0}; seeder path?)" >&2
  nm "$p3bin" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
  exit 1
fi
echo "pool_labels=${pool_n}"

# Produce-point leftover: bake must intern ek==59, not loud-fail.
if grep -n 'if (ek == 59)' "$ROOT/compiler/src/runtime_pipeline_abi.x" \
    | grep -q 'return 0 - 1'; then
  echo "FAIL: bake still loud-fails STRING_LIT" >&2
  exit 1
fi

echo "modlet_string_pool probe OK p3=0 p2=42 p9=0 p_empty=0 p_long=0 pool_labels=${pool_n}"
