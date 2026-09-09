#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for retired mega C-frontend wrappers.
# src/runtime.x + runtime_surface.from_x.c used to export
# driver_c_frontend_smoke and driver_check_only_c_typeck as thin
# forwards to never-defined *_impl. C frontend is gone; product
# typeck authority is pipeline_typeck_entry_module. After
# retirement: mega surface must not define those names; product
# xlang_asm must still T the pipeline typeck entry and must not
# T the retired C-frontend names.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_mega_stale_c_frontend_smoke_$$"
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
  driver_c_frontend_smoke \
  driver_check_only_c_typeck \
  driver_c_frontend_smoke_impl \
  driver_check_only_c_typeck_impl
do
  if nm_has "$WORKDIR/surface.o" 'TWwUu' "$name"; then
    echo "FAIL: runtime_surface.o still has $name" >&2
    nm "$WORKDIR/surface.o" | grep -E "c_frontend_smoke|check_only_c_typeck" >&2 || true
    exit 1
  fi
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

# Product typeck authority (X pipeline). Either name is enough; both
# are the live face after C frontend retirement.
if ! nm_has "$XLANG" 'TWw' "pipeline_typeck_entry_module"; then
  echo "FAIL: product xlang_asm missing T pipeline_typeck_entry_module" >&2
  nm "$XLANG" | grep -E "typeck_entry" >&2 || true
  exit 1
fi

# Retired C-frontend names must stay off the product binary.
for name in \
  driver_c_frontend_smoke \
  driver_check_only_c_typeck
do
  if nm_has "$XLANG" 'TWwUu' "$name"; then
    echo "FAIL: product xlang_asm still has $name" >&2
    nm "$XLANG" | grep -E "c_frontend_smoke|check_only_c_typeck" >&2 || true
    exit 1
  fi
done

echo "mega_stale_c_frontend_smoke probe OK surface=0 product_pipeline_typeck=1 product_retired=0"
