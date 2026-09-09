#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for leftover rt_run_x_emit
# !XLANG_NO_C_FRONTEND -E-extern cparser consume site.
# Cold seed used to call driver_run_x_emit_c_extern_via_cparser when
# want_extern (mega wrapper → never-defined _impl). Product authority
# is driver_run_x_emit_c → driver_x_emit_try_extern_via_cparser
# (always BLD001). After this knife: the cold emit body must not call
# via_cparser; even compiling without XLANG_NO_C_FRONTEND must not
# U-ref it. Mega wrapper remains (different class).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_rt_run_stale_e_extern_cparser_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

SEED_XE="$ROOT/compiler/seeds/rt_run_x_emit.from_x.c"

# Real preprocessor guards must be gone. Comment mentions of the macro are OK.
if grep -nE '^[[:space:]]*#if[[:space:]]+!defined\(XLANG_NO_C_FRONTEND\)' "$SEED_XE"; then
  echo "FAIL: rt_run_x_emit seed still has !XLANG_NO_C_FRONTEND guard" >&2
  exit 1
fi

# Consume-site call/extern must be gone. Comment mentions of the name are OK
# (no '('). Matching a declaration or a call is the fail.
if grep -nE 'extern[[:space:]]+int[[:space:]]+driver_run_x_emit_c_extern_via_cparser' \
     "$SEED_XE"; then
  echo "FAIL: rt_run_x_emit seed still declares leftover via_cparser extern" >&2
  exit 1
fi
if grep -nE 'driver_run_x_emit_c_extern_via_cparser\s*\(' "$SEED_XE"; then
  echo "FAIL: rt_run_x_emit seed still calls leftover via_cparser" >&2
  exit 1
fi

# Cold body (no FROM_X) WITHOUT product NO_C: leftover used to U-ref
# via_cparser. After this knife the TU must not pull it, and must still
# refuse via driver_x_emit_try_extern_via_cparser.
cflags_no_c=(
  -c -w
  -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src"
  -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS
  -DXLANG_USE_X_TYPECK -DXLANG_USE_X_CODEGEN
)
"$CC" "${cflags_no_c[@]}" "$SEED_XE" -o "$WORKDIR/xe_drop_noc.o"
"$CC" "${cflags_no_c[@]}" -DXLANG_NO_C_FRONTEND "$SEED_XE" -o "$WORKDIR/xe_with_noc.o"

nm_has() {
  local obj="$1"
  local kind="$2"
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

for obj in "$WORKDIR/xe_drop_noc.o" "$WORKDIR/xe_with_noc.o"; do
  if nm_has "$obj" 'TWwUu' "driver_run_x_emit_c_extern_via_cparser"; then
    echo "FAIL: $(basename "$obj") still has driver_run_x_emit_c_extern_via_cparser" >&2
    nm "$obj" | grep -E "driver_run_x_emit_c_extern_via_cparser" >&2 || true
    exit 1
  fi
  if ! nm_has "$obj" 'TWwUu' "driver_x_emit_try_extern_via_cparser"; then
    echo "FAIL: $(basename "$obj") missing driver_x_emit_try_extern_via_cparser ref" >&2
    exit 1
  fi
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

if ! nm_has "$XLANG" 'TWw' "driver_run_x_emit_c"; then
  echo "FAIL: product xlang_asm missing T driver_run_x_emit_c" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_x_emit_try_extern_via_cparser"; then
  echo "FAIL: product xlang_asm missing T driver_x_emit_try_extern_via_cparser" >&2
  exit 1
fi

echo "rt_run_stale_e_extern_cparser probe OK seed_cparser=0 product_try_extern=1 product_emit_c=1"
