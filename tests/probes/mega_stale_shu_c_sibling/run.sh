#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for retired mega sibling _impl wrapper.
# src/runtime.x + runtime_surface.from_x.c used to export
# driver_try_compile_via_shu_c_sibling as a thin forward to a
# never-defined *_impl. Product authority is rt_dispatch_thin.x →
# driver_dispatch_sibling_try_spawn (HAS a real fork/exec body).
# Leftover consume site retired at residual 6. After retirement: mega
# surface must not define the wrapper / _impl; product xlang_asm must
# still T sibling + spawn and must not T sibling_impl.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_mega_stale_shu_c_sibling_$$"
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

# Mega surface must not mention the retired wrapper / never-defined _impl
# (no T/W and no U). The public name lives on rt_dispatch_thin, not here.
for name in \
  driver_try_compile_via_shu_c_sibling \
  driver_try_compile_via_shu_c_sibling_impl
do
  if nm_has "$WORKDIR/surface.o" 'TWwUu' "$name"; then
    echo "FAIL: runtime_surface.o still has $name" >&2
    nm "$WORKDIR/surface.o" | grep -E "shu_c_sibling" >&2 || true
    exit 1
  fi
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

# Product spawn authority (HAS a real fork/exec body — keep it).
if ! nm_has "$XLANG" 'TWw' "driver_try_compile_via_shu_c_sibling"; then
  echo "FAIL: product xlang_asm missing T driver_try_compile_via_shu_c_sibling (body must stay)" >&2
  nm "$XLANG" | grep -E "shu_c_sibling" >&2 || true
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_dispatch_sibling_try_spawn"; then
  echo "FAIL: product xlang_asm missing T driver_dispatch_sibling_try_spawn (body must stay)" >&2
  nm "$XLANG" | grep -E "sibling_try_spawn" >&2 || true
  exit 1
fi

# Never-defined mega _impl must stay off the product binary.
if nm_has "$XLANG" 'TWwUu' "driver_try_compile_via_shu_c_sibling_impl"; then
  echo "FAIL: product xlang_asm still has driver_try_compile_via_shu_c_sibling_impl" >&2
  nm "$XLANG" | grep -E "shu_c_sibling_impl" >&2 || true
  exit 1
fi

echo "mega_stale_shu_c_sibling probe OK surface=0 product_sibling=1 product_spawn=1 product_impl=0"
