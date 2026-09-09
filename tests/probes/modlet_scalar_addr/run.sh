#!/usr/bin/env bash
# PLATFORM: SHARED — scalar ADDR_OF / fn-ptr 全局格 bake via absolute64 RELA.
# Behavioral: p_addrof=5; p_fn/p_as/p_call=42; p_copy=42 (hoist copy kept);
# p_int=5 (LIT COMMON regression).
# Discriminator: p_fn cell Lxml_ lives in .data / __DATA,__data (not COMMON).
# p_addrof has g in COMMON (LIT) + p in .data (ADDR_OF).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
DIR="$(cd "$(dirname "$0")" && pwd)"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_modlet_scalar_addr_$$"
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

run_one p_addrof 5
run_one p_fn 42
run_one p_as 42
run_one p_call 42
run_one p_copy 42
run_one p_int 5

# Discriminator: p_fn's scalar cell is baked .data, not COMMON.
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
  # p_addrof: g stays COMMON (LIT); p is .data (ADDR_OF).
  p_ad="$WORKDIR/p_addrof"
  ad_data="$(nm -m "$p_ad" 2>/dev/null | grep -cE '\(__DATA,__data\) .*_Lxml_[0-9a-f]' || true)"
  ad_common="$(nm -m "$p_ad" 2>/dev/null | grep -cE '\(__DATA,__common\) .*_Lxml_[0-9a-f]' || true)"
  if [ "${ad_data:-0}" -lt 1 ] || [ "${ad_common:-0}" -lt 1 ]; then
    echo "FAIL: p_addrof expected 1 .data (p) + 1 common (g); data=${ad_data:-0} common=${ad_common:-0}" >&2
    nm -m "$p_ad" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  echo "p_addrof_section=data+common data_n=${ad_data} common_n=${ad_common}"
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
  p_ad="$WORKDIR/p_addrof"
  ad_data="$(nm "$p_ad" 2>/dev/null | grep -cE ' [Dd] Lxml_' || true)"
  ad_common="$(nm "$p_ad" 2>/dev/null | grep -cE ' [CBb] Lxml_' || true)"
  if [ "${ad_data:-0}" -lt 1 ] || [ "${ad_common:-0}" -lt 1 ]; then
    echo "FAIL: p_addrof expected 1 .data (p) + 1 common (g); data=${ad_data:-0} common=${ad_common:-0}" >&2
    nm "$p_ad" 2>/dev/null | grep -E 'Lxml' | head -20 >&2
    exit 1
  fi
  echo "p_addrof_section=data+common data_n=${ad_data} common_n=${ad_common}"
fi

echo "modlet_scalar_addr probe OK p_addrof=5 p_fn=42 p_as=42 p_call=42 p_copy=42 p_int=5 p_fn_section=data"
