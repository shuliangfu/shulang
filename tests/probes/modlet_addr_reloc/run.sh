#!/usr/bin/env bash
# PLATFORM: SHARED — 9.4.2 ADDR_OF / fn-ptr table bake via absolute64 RELA.
# Behavioral: p_fn/p_as/p_call=42; p_addrof=12; p_int=42 (integer bake).
# Discriminator: p_fn table cell Lxml_ lives in .data / __DATA,__data
# (not COMMON / __DATA,__common). Seeder leftover would still be common.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_modlet_addr_reloc_$$"
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

run_one p_fn 42
run_one p_as 42
run_one p_addrof 12
run_one p_call 42
run_one p_int 42

# Discriminator: p_fn's table cell is baked .data, not COMMON.
# Darwin nm -m: (__DATA,__data) _Lxml_<hash> and no __common Lxml_ on p_fn
# (p_fn has no scalar COMMON lets). ELF nm: ' D Lxml_' and no ' C '/' B '.
p_fn_bin="$WORKDIR/p_fn"
if [ "$(uname -s)" = Darwin ]; then
  data_n="$(nm -m "$p_fn_bin" 2>/dev/null | grep -cE '\(__DATA,__data\) .*_Lxml_[0-9a-f]' || true)"
  common_n="$(nm -m "$p_fn_bin" 2>/dev/null | grep -cE '\(__DATA,__common\) .*_Lxml_[0-9a-f]' || true)"
  if [ "${data_n:-0}" -lt 1 ]; then
    echo "FAIL: p_fn missing __DATA,__data Lxml_ (nm data=${data_n:-0}; seeder path?)" >&2
    nm -m "$p_fn_bin" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  if [ "${common_n:-0}" -ne 0 ]; then
    echo "FAIL: p_fn still has __DATA,__common Lxml_ (nm common=${common_n}; bake missed)" >&2
    nm -m "$p_fn_bin" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  echo "p_fn_section=data data_n=${data_n} common_n=0"
else
  data_n="$(nm "$p_fn_bin" 2>/dev/null | grep -cE ' [Dd] Lxml_' || true)"
  common_n="$(nm "$p_fn_bin" 2>/dev/null | grep -cE ' [CBb] Lxml_' || true)"
  if [ "${data_n:-0}" -lt 1 ]; then
    echo "FAIL: p_fn missing .data Lxml_ (nm D=${data_n:-0}; seeder path?)" >&2
    nm "$p_fn_bin" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  if [ "${common_n:-0}" -ne 0 ]; then
    echo "FAIL: p_fn still has COMMON/BSS Lxml_ (nm CB=${common_n}; bake missed)" >&2
    nm "$p_fn_bin" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  echo "p_fn_section=data data_n=${data_n} common_n=0"
fi

# Produce-point leftover: prepare must not veto address elems.
if grep -n 'pipe_modlet_array_lit_has_ptr_addr_elem' \
    "$ROOT/compiler/src/runtime_pipeline_abi.x" \
    | grep -q '== 0'; then
  echo "FAIL: prepare still vetoes ptr-addr elems from bake" >&2
  exit 1
fi

echo "modlet_addr_reloc probe OK p_fn=42 p_as=42 p_addrof=12 p_call=42 p_int=42 p_fn_section=data"
