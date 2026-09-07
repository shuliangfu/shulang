#!/usr/bin/env bash
# preprocess / conditional-compile smoke: -D FOO, #elseif, target_os, NEG PP002
#
# Honesty: soft default `./compiler/xlang` + soft auto-make + soft bootstrap-link
# (false authority) retired. Prefer product xlang_asm; pin XLANG_LINK_XLANG.
# Explicit bad XLANG / missing native = hard die (refuse soft SKIP→OK / soft
# auto-make / prefer-c / soft bootstrap-link). Report: run=/obs=/skip=
# PLATFORM: SHARED archaeology — Ubuntu gold still required.
set -euo pipefail
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh
# shellcheck source=tests/lib/dod-native-exe.sh
. tests/lib/dod-native-exe.sh
# shellcheck source=tests/lib/gate-progress.sh
. tests/lib/gate-progress.sh

PREFIX="${XLANG_PREPROCESS_PREFIX:-xlang: [PREPROCESS]}"
XLANG_CASE_TIMEOUT="${XLANG_CASE_TIMEOUT:-120}"
RUN_OK=0
OBS=0
SKIP=0

die() {
  echo "preprocess FAIL: $*" >&2
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

resolve_shu() {
  local cand abs root
  root=$(pwd)
  if [ -n "${XLANG:-}" ]; then
    case "$XLANG" in
      /*) abs="$XLANG" ;;
      *) abs="$root/$XLANG" ;;
    esac
    if dod_native_exe "$abs"; then
      echo "$abs"
      return 0
    fi
    return 1
  fi
  if [ -n "${XLANG_BSTRICT_USE_ASM2:-}" ] && dod_native_exe ./compiler/xlang_asm2; then
    echo "$(pwd)/compiler/xlang_asm2"
    return 0
  fi
  # Prefer product asm; pin XLANG_LINK_XLANG for dogfood consistency.
  # PLATFORM: SHARED — product path honesty; Ubuntu gold still required.
  for cand in ./compiler/xlang_asm ./compiler/xlang-c ./compiler/xlang; do
    case "$cand" in
      /*) abs="$cand" ;;
      *) abs="$root/$cand" ;;
    esac
    if dod_native_exe "$abs"; then
      echo "$abs"
      return 0
    fi
  done
  return 1
}

# POS: product -o then assert process exit code.
run_exit() {
  local tag="$1" src="$2" want="$3"
  shift 3
  local exe="/tmp/xlang_pp_${tag}_$$"
  local log="/tmp/xlang_pp_${tag}_$$.log"
  local o_ec r_ec
  [ -f "$src" ] || die "missing $src ($tag)"
  rm -f "$exe" "$log"
  set +e
  gate_run_timeout "$XLANG_CASE_TIMEOUT" "$XLANG_BIN" build "$@" "$src" -o "$exe" >"$log" 2>&1
  o_ec=$?
  set -e
  if [ "$o_ec" -eq 124 ]; then
    die "$tag product -o timeout"
  elif [ "$o_ec" -ne 0 ] || [ ! -x "$exe" ]; then
    die "$tag product -o failed (ec=$o_ec); $(tail -5 "$log" 2>/dev/null | tr '\n' ' ')"
  fi
  set +e
  gate_run_timeout "$XLANG_CASE_TIMEOUT" "$exe" >/dev/null 2>&1
  r_ec=$?
  set -e
  rm -f "$exe" "$log"
  if [ "$r_ec" -eq 124 ]; then
    die "$tag run timeout"
  elif [ "$r_ec" -ne "$want" ]; then
    die "$tag expected exit $want, got $r_ec"
  fi
  RUN_OK=$((RUN_OK + 1))
}

# NEG: product -o must fail with needle in diagnostics (hard-asserted → run=).
run_neg() {
  local tag="$1" src="$2" needle="$3"
  local exe="/tmp/xlang_pp_${tag}_$$"
  local log="/tmp/xlang_pp_${tag}_$$.log"
  local o_ec
  [ -f "$src" ] || die "missing $src ($tag)"
  rm -f "$exe" "$log"
  set +e
  gate_run_timeout "$XLANG_CASE_TIMEOUT" "$XLANG_BIN" build "$src" -o "$exe" >"$log" 2>&1
  o_ec=$?
  set -e
  if [ "$o_ec" -eq 124 ]; then
    die "$tag timeout"
  elif [ "$o_ec" -eq 0 ]; then
    die "$tag expected compile fail, got success"
  fi
  grep -q "$needle" "$log" \
    || die "$tag expected '$needle'; $(tail -5 "$log" 2>/dev/null | tr '\n' ' ')"
  rm -f "$exe" "$log"
  RUN_OK=$((RUN_OK + 1))
}

echo "=== preprocess gate (prefer asm; hard) ==="
XLANG_BIN="$(resolve_shu)" || die "no native xlang/xlang_asm/xlang-c (refuse soft SKIP→OK / soft auto-make)"
export XLANG="$XLANG_BIN"
export XLANG_LINK_XLANG="$XLANG_BIN"
echo "XLANG=$XLANG_BIN"

# -D FOO / -DFOO / no -D
run_exit no_d tests/preprocess/main.x 22
run_exit d_foo tests/preprocess/main.x 11 -D FOO
run_exit dfoo tests/preprocess/main.x 11 -DFOO

# 9.3.3: bare decimal #if literals (nonzero true / "0" false)
run_exit if_lit1 tests/preprocess/if_numeric1.x 11
run_exit if_lit0 tests/preprocess/if_numeric0.x 22

# #elseif arms
run_exit elseif_none tests/preprocess/elseif.x 3
run_exit elseif_foo tests/preprocess/elseif.x 1 -D FOO
run_exit elseif_bar tests/preprocess/elseif.x 2 -D BAR

# NEG PP002 family (hard-asserted → run=)
run_neg unclosed_if tests/preprocess/unclosed_if.x "unclosed #if"
run_neg else_without_if tests/preprocess/else_without_if.x "#else without #if"
run_neg endif_without_if tests/preprocess/endif_without_if.x "#endif without #if"
run_neg elseif_without_if tests/preprocess/elseif_without_if.x "#elseif without #if"
run_neg elseif_after_else tests/preprocess/elseif_after_else.x "#elseif after #else"
run_neg duplicate_else tests/preprocess/duplicate_else.x "duplicate #else"
run_neg extra_endif tests/preprocess/extra_endif.x "#endif without #if"

# #if target_os == "..." (host OS exit code)
EXPECT_OS=43
case "$(uname -s)" in
  Linux) EXPECT_OS=41 ;;
  Darwin) EXPECT_OS=42 ;;
esac
run_exit target_os_if tests/preprocess/target_os_if.x "$EXPECT_OS"

ok_report
echo "preprocess (conditional compile) test OK"
