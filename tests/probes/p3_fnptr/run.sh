#!/usr/bin/env bash
# PLATFORM: SHARED — p3 family: module-level `function(i32):i32` assign.
# Green: global/local/as/tab/u8/copy/nullary. Keep-red: arity/ret/opaque T001.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_p3_fnptr_$$"
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

expect_typeck_fail() {
  local name="$1"
  local src="$DIR/${name}.x"
  local out="$WORKDIR/${name}"
  set +e
  "$XLANG" "$src" -o "$out" >"$WORKDIR/${name}.log" 2>&1
  local crc=$?
  set -e
  if [ "$crc" -eq 0 ]; then
    echo "FAIL: $name compiled; expected T001 assignment mismatch" >&2
    exit 1
  fi
  if ! grep -q 'assignment type mismatch' "$WORKDIR/${name}.log"; then
    echo "FAIL: $name missing assignment type mismatch" >&2
    cat "$WORKDIR/${name}.log" >&2
    exit 1
  fi
  echo "${name}=T001"
}

run_one p_global 42
run_one p_local 42
run_one p_global_as 42
run_one p_global_tab 42
run_one p_global_u8 42
run_one p_global_copy 42
run_one p_global_nullary 42
expect_typeck_fail p_arity
expect_typeck_fail p_ret
expect_typeck_fail p_opaque

echo "p3_fnptr probe OK p_global=42 p_local=42 p_global_as=42 p_global_tab=42 p_global_u8=42 p_global_copy=42 p_global_nullary=42 p_arity=T001 p_ret=T001 p_opaque=T001"
