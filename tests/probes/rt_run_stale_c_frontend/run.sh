#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for leftover rt_run_* C-frontend
# consume sites. Cold seeds rt_run_asm_backend.from_x.c and
# rt_run_compiler_parsed.from_x.c used to call
# driver_c_frontend_smoke / driver_check_only_c_typeck /
# driver_c_typeck_entry{,_large_stack} behind !XLANG_NO_C_FRONTEND
# after mega wrappers were deleted. Product early-exit authority is
# driver_asm_try_c_frontend_early / driver_asm_try_c_typeck_precheck
# (thin always -2 / -1); typeck is pipeline_typeck_entry_module.
# After this knife: seed source must not call/extern those names;
# product must still T the try_c + pipeline typeck face.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_rt_run_stale_c_frontend_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

SEED_AB="$ROOT/compiler/seeds/rt_run_asm_backend.from_x.c"
SEED_CP="$ROOT/compiler/seeds/rt_run_compiler_parsed.from_x.c"

# Call/extern leftover must be gone. Comment mentions of the names are OK
# (no '('). Matching a declaration or a call is the fail.
if grep -nE 'extern[[:space:]]+int[[:space:]]+driver_(c_frontend_smoke|check_only_c_typeck|c_typeck_entry)' \
     "$SEED_AB" "$SEED_CP"; then
  echo "FAIL: rt_run_* seed still declares retired C-frontend extern" >&2
  exit 1
fi
if grep -nE 'driver_(c_frontend_smoke|check_only_c_typeck|c_typeck_entry(_large_stack|_thread_fn)?)\s*\(' \
     "$SEED_AB" "$SEED_CP"; then
  echo "FAIL: rt_run_* seed still calls retired C-frontend name" >&2
  exit 1
fi

# Cold body (no FROM_X) with product NO_C: leftover compiled out before
# and after; nm must not U-ref the retired names.
cflags=(
  -c -w
  -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src"
  -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS
  -DXLANG_USE_X_TYPECK -DXLANG_USE_X_CODEGEN -DXLANG_NO_C_FRONTEND
)
"$CC" "${cflags[@]}" "$SEED_AB" -o "$WORKDIR/ab.o"
"$CC" "${cflags[@]}" "$SEED_CP" -o "$WORKDIR/cp.o"

nm_has() {
  local obj="$1"
  local kind="$2"
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

for obj in "$WORKDIR/ab.o" "$WORKDIR/cp.o"; do
  for name in \
    driver_c_frontend_smoke \
    driver_check_only_c_typeck \
    driver_c_typeck_entry \
    driver_c_typeck_entry_large_stack \
    driver_c_typeck_entry_thread_fn
  do
    if nm_has "$obj" 'TWwUu' "$name"; then
      echo "FAIL: $(basename "$obj") still has $name" >&2
      nm "$obj" | grep -E "c_frontend_smoke|check_only_c_typeck|c_typeck_entry" >&2 || true
      exit 1
    fi
  done
done

if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi

if ! nm_has "$XLANG" 'TWw' "pipeline_typeck_entry_module"; then
  echo "FAIL: product xlang_asm missing T pipeline_typeck_entry_module" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_asm_try_c_frontend_early"; then
  echo "FAIL: product xlang_asm missing T driver_asm_try_c_frontend_early" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "driver_asm_try_c_typeck_precheck"; then
  echo "FAIL: product xlang_asm missing T driver_asm_try_c_typeck_precheck" >&2
  exit 1
fi

for name in \
  driver_c_frontend_smoke \
  driver_check_only_c_typeck \
  driver_c_typeck_entry \
  driver_c_typeck_entry_large_stack \
  driver_c_typeck_entry_thread_fn
do
  if nm_has "$XLANG" 'TWwUu' "$name"; then
    echo "FAIL: product xlang_asm still has $name" >&2
    nm "$XLANG" | grep -E "c_frontend_smoke|check_only_c_typeck|c_typeck_entry" >&2 || true
    exit 1
  fi
done

echo "rt_run_stale_c_frontend probe OK seed_call=0 product_try_c=1 product_pipeline_typeck=1 product_retired=0"
