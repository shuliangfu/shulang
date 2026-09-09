#!/usr/bin/env bash
# PLATFORM: SHARED — parser slen>127 L011 complete (overflow chain + jmp-skip E9).
# Behavioral: p_127/p_128/p_200/p_adj/p_global run 0; p_keep compile L011.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_p_string_lit_long_$$"
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

run_one p_127 0
run_one p_128 0
run_one p_200 0
run_one p_adj 0
run_one p_global 0

# Keep-red: 4096 semantic bytes still L011.
if "$XLANG" "$DIR/p_keep.x" -o "$WORKDIR/p_keep" >"$WORKDIR/p_keep.log" 2>&1; then
  echo "FAIL: p_keep compiled (expected L011)" >&2
  cat "$WORKDIR/p_keep.log" >&2
  exit 1
fi
if ! grep -q 'L011' "$WORKDIR/p_keep.log"; then
  echo "FAIL: p_keep missing L011" >&2
  cat "$WORKDIR/p_keep.log" >&2
  exit 1
fi
echo "p_keep=L011"

echo "p_string_lit_long probe OK p_127=0 p_128=0 p_200=0 p_adj=0 p_global=0 p_keep=L011"
