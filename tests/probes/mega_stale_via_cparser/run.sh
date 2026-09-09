#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for retired mega -E-extern cparser wrapper.
# src/runtime.x + runtime_surface.from_x.c used to export
# driver_run_x_emit_c_extern_via_cparser as a thin forward to a
# never-defined *_impl. C frontend is gone; leftover consume site
# retired at residual 7. Product -E-extern authority is
# driver_run_x_emit_c → driver_x_emit_try_extern_via_cparser
# (always BLD001). After retirement: mega surface must not define
# those names; product xlang_asm must still T try_extern + emit_c
# and must not T the retired via_cparser names.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_mega_stale_via_cparser_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

# -w: surface is -E codegen (parentheses-equality noise); nm is the gate.
cflags=(-c -w -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src")
"$CC" "${cflags[@]}" "$ROOT/compiler/seeds/runtime_surface.from_x.c" -o "$WORKDIR/surface.o"

nm_has() {
  local obj="$1"
  local kind="$2" # TWw or Uu
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

# Mega surface must not mention the retired names (no T/W and no U _impl).
for name in \
  driver_run_x_emit_c_extern_via_cparser \
  driver_run_x_emit_c_extern_via_cparser_impl
do
  if nm_has "$WORKDIR/surface.o" 'TWwUu' "$name"; then
    echo "FAIL: runtime_surface.o still has $name" >&2
    nm "$WORKDIR/surface.o" | grep -E "via_cparser" >&2 || true
    exit 1
  fi
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

# Product -E-extern authority (always BLD001 refuse).
if ! nm_has "$XLANG" 'TWw' "driver_x_emit_try_extern_via_cparser"; then
  echo "FAIL: product xlang_asm missing T driver_x_emit_try_extern_via_cparser" >&2
  nm "$XLANG" | grep -E "try_extern|via_cparser" >&2 || true
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_run_x_emit_c"; then
  echo "FAIL: product xlang_asm missing T driver_run_x_emit_c" >&2
  nm "$XLANG" | grep -E "driver_run_x_emit_c" >&2 || true
  exit 1
fi

# Retired mega wrapper names must stay off the product binary.
for name in \
  driver_run_x_emit_c_extern_via_cparser \
  driver_run_x_emit_c_extern_via_cparser_impl
do
  if nm_has "$XLANG" 'TWwUu' "$name"; then
    echo "FAIL: product xlang_asm still has $name" >&2
    nm "$XLANG" | grep -E "via_cparser" >&2 || true
    exit 1
  fi
done

echo "mega_stale_via_cparser probe OK surface=0 product_try_extern=1 product_emit_c=1 product_retired=0"
