#!/usr/bin/env bash
# PLATFORM: SHARED — Defect D typeck: C integer promotions on compare.
# Green: u8 vs i32 var (equal/ne/255/while/INDEX) + lit coerce + while wrap.
# Keep-red: i32 vs i64 / i32 vs bool still T001 (wave666 usual-arith / int↔bool).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_defect_d_$$"
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
    echo "FAIL: $name compiled; expected T001 mixed-type compare" >&2
    exit 1
  fi
  if ! grep -q 'comparison operands have incompatible types' "$WORKDIR/${name}.log"; then
    echo "FAIL: $name missing T001 comparison mismatch" >&2
    cat "$WORKDIR/${name}.log" >&2
    exit 1
  fi
  echo "${name}=T001"
}

run_one p_u8_i32 0
run_one p_u8_i32_ne 1
run_one p_u8_255 0
run_one p_while 3
run_one p_idx 0
run_one p_wrap 0
run_one p_u8_lit 0
expect_typeck_fail p_i32_i64
expect_typeck_fail p_i32_bool

echo "defect_d probe OK p_u8_i32=0 p_u8_i32_ne=1 p_u8_255=0 p_while=3 p_idx=0 p_wrap=0 p_u8_lit=0 p_i32_i64=T001 p_i32_bool=T001"
