#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for leftover rt_run_compiler_parsed
# C-frontend generic-syntax lexer/parse + import-downgrade blocks.
# Cold seed used to demote top-level import (want_asm_backend=0) and
# run lexer_new/parse/typeck_module/codegen_module_to_c behind
# !XLANG_NO_C_FRONTEND. Product authority is rt_cp_step_try_c →
# driver_parsed_try_c_after_pp (always -2) then parser_parse_into_buf /
# pipeline_typeck_entry_module. After this knife: seed source must not
# call the C lexer/parse path or demote import; even compiling the cold
# body without XLANG_NO_C_FRONTEND must not U-ref lexer_new.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_rt_run_stale_generic_c_frontend_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

SEED_CP="$ROOT/compiler/seeds/rt_run_compiler_parsed.from_x.c"

# Real preprocessor guards must be gone. Comment mentions of the macro are OK.
if grep -nE '^[[:space:]]*#if[[:space:]]+!defined\(XLANG_NO_C_FRONTEND\)' "$SEED_CP"; then
  echo "FAIL: rt_run_compiler_parsed seed still has !XLANG_NO_C_FRONTEND guard" >&2
  exit 1
fi

# Call leftovers must be gone. Comment mentions of the names are OK (no '(').
if grep -nE 'lexer_new\s*\(|lexer_free\s*\(|ast_module_free\s*\(|content_has_generic_syntax\s*\(|driver_source_has_top_level_import\s*\(|xlang_preprocess_quiet\s*\(|typeck_module\s*\(|codegen_module_to_c\s*\(' \
     "$SEED_CP"; then
  echo "FAIL: rt_run_compiler_parsed seed still calls leftover C frontend" >&2
  exit 1
fi

# Import-downgrade must be gone. check_only → want_asm_backend=0 stays live.
if grep -nE 'driver_source_has_top_level_import' "$SEED_CP" | grep -v 'Retired leftover'; then
  echo "FAIL: rt_run_compiler_parsed seed still mentions import-downgrade helper" >&2
  exit 1
fi

# Cold body (no FROM_X) WITHOUT product NO_C: leftover used to U-ref lexer_new.
# After this knife the TU must not pull C frontend parse symbols.
cflags_no_c=(
  -c -w
  -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src"
  -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS
  -DXLANG_USE_X_TYPECK -DXLANG_USE_X_CODEGEN
)
"$CC" "${cflags_no_c[@]}" "$SEED_CP" -o "$WORKDIR/cp_drop_noc.o"
"$CC" "${cflags_no_c[@]}" -DXLANG_NO_C_FRONTEND "$SEED_CP" -o "$WORKDIR/cp_with_noc.o"

nm_has() {
  local obj="$1"
  local kind="$2"
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

for obj in "$WORKDIR/cp_drop_noc.o" "$WORKDIR/cp_with_noc.o"; do
  for name in lexer_new lexer_free ast_module_free content_has_generic_syntax \
              driver_source_has_top_level_import xlang_preprocess_quiet \
              typeck_module codegen_module_to_c
  do
    if nm_has "$obj" 'TWwUu' "$name"; then
      echo "FAIL: $(basename "$obj") still has $name" >&2
      nm "$obj" | grep -E "$name" >&2 || true
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
if ! nm_has "$XLANG" 'TWw' "driver_parsed_try_c_after_pp"; then
  echo "FAIL: product xlang_asm missing T driver_parsed_try_c_after_pp" >&2
  exit 1
fi
if ! nm_has "$XLANG" 'TWw' "rt_cp_step_try_c"; then
  echo "FAIL: product xlang_asm missing T rt_cp_step_try_c" >&2
  exit 1
fi

echo "rt_run_stale_generic_c_frontend probe OK seed_c_lex=0 product_try_c=1 product_pipeline_typeck=1"
