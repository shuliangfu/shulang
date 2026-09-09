#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for leftover rt_dispatch_impl
# !XLANG_NO_C_FRONTEND driver_try_compile_via_shu_c_sibling consume site.
# Cold seed used to fork/exec same-dir xlang-c on top-level import
# (HAS a real body in rt_dispatch_thin — different class from
# never-defined mega wrappers). Product authority is
# driver_run_emit_c_path_impl_c → driver_dispatch_run_compiler_parsed
# (rt_dispatch_impl.x never called sibling). After this knife: the
# cold emit_c_path body must not call sibling; even compiling without
# XLANG_NO_C_FRONTEND must not U-ref it. Spawn helper remains T.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_rt_dispatch_stale_shu_c_sibling_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

SEED_DI="$ROOT/compiler/seeds/rt_dispatch_impl.from_x.c"
SEED_CP="$ROOT/compiler/seeds/rt_run_compiler_parsed.from_x.c"

# Real preprocessor guards must be gone. Comment mentions of the macro are OK.
if grep -nE '^[[:space:]]*#if[[:space:]]+!defined\(XLANG_NO_C_FRONTEND\)' "$SEED_DI"; then
  echo "FAIL: rt_dispatch_impl seed still has !XLANG_NO_C_FRONTEND guard" >&2
  exit 1
fi

# Consume-site call/extern must be gone. Comment mentions of the name are OK
# (no '('). Matching a declaration or a call is the fail.
if grep -nE 'extern[[:space:]]+int[[:space:]]+driver_try_compile_via_shu_c_sibling' \
     "$SEED_DI" "$SEED_CP"; then
  echo "FAIL: dispatch/parsed seed still declares leftover sibling extern" >&2
  exit 1
fi
if grep -nE 'driver_try_compile_via_shu_c_sibling\s*\(' "$SEED_DI" "$SEED_CP"; then
  echo "FAIL: dispatch/parsed seed still calls leftover sibling" >&2
  exit 1
fi

# Cold body (no FROM_X) WITHOUT product NO_C: leftover used to U-ref sibling
# (and actually fork xlang-c). After this knife the TU must not pull it.
cflags_no_c=(
  -c -w
  -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src"
  -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS
  -DXLANG_USE_X_TYPECK -DXLANG_USE_X_CODEGEN
)
"$CC" "${cflags_no_c[@]}" "$SEED_DI" -o "$WORKDIR/di_drop_noc.o"
"$CC" "${cflags_no_c[@]}" -DXLANG_NO_C_FRONTEND "$SEED_DI" -o "$WORKDIR/di_with_noc.o"

nm_has() {
  local obj="$1"
  local kind="$2"
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

for obj in "$WORKDIR/di_drop_noc.o" "$WORKDIR/di_with_noc.o"; do
  for name in driver_try_compile_via_shu_c_sibling driver_asm_entry_module_only_from_env
  do
    if nm_has "$obj" 'TWwUu' "$name"; then
      echo "FAIL: $(basename "$obj") still has $name" >&2
      nm "$obj" | grep -E "$name" >&2 || true
      exit 1
    fi
  done
  if ! nm_has "$obj" 'TWwUu' "driver_run_compiler_parsed"; then
    echo "FAIL: $(basename "$obj") missing driver_run_compiler_parsed ref" >&2
    exit 1
  fi
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

if ! nm_has "$XLANG" 'TWw' "driver_run_emit_c_path_impl_c"; then
  echo "FAIL: product xlang_asm missing T driver_run_emit_c_path_impl_c" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_dispatch_run_compiler_parsed"; then
  echo "FAIL: product xlang_asm missing T driver_dispatch_run_compiler_parsed" >&2
  exit 1
fi
# Spawn helper HAS a real body — keep it. This knife is consume-site only.
if ! nm_has "$XLANG" 'TWw' "driver_try_compile_via_shu_c_sibling"; then
  echo "FAIL: product xlang_asm missing T driver_try_compile_via_shu_c_sibling (body must stay)" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_dispatch_sibling_try_spawn"; then
  echo "FAIL: product xlang_asm missing T driver_dispatch_sibling_try_spawn (body must stay)" >&2
  exit 1
fi

echo "rt_dispatch_stale_shu_c_sibling probe OK seed_call=0 product_parsed=1 product_emit_c=1 product_sibling_body=1"
