#!/usr/bin/env bash
# pin_gen_drift_gate.sh — 7.4.4 v1: pin↔gen symbol-set freshness gate.
#
# Purpose (G.7 seed/pin ↔ .x same-commit-same-semantics acceptance): for every
# seeds/<stem>.linux.x86_64.c pin that has a worktree <stem>.c gen, cc -c both
# and compare the strong-text (T) export symbol sets. Catches the "pin edited
# in git, worktree gen stale" trap — 2026-09-10: the driver_gen pin gained
# driver_compile_argv_next_is_value_c while worktree driver_gen.c stayed stale
# (ensure 'up-to-date vs MAIN_X_DEPS' is mtime-based and does not see pin
# edits); the product then shipped without the parse guard's first layer until
# a manual nm caught it. Pins without a current worktree gen (built on demand:
# cfg_eval_gen, driver_{check,fmt,test}_gen) are SKIPs, not failures.
#
# Text-level drift between pin and gen is EXPECTED (pins regenerate across
# emitter versions with formatting churn); the T symbol set is the semantic
# signal (added/removed/renamed functions).
#
# v2 follow-ups (NOT here): .x ↔ pin semantic drift via product -E (needs a
# fresh product binary and per-family -E flags); CI wiring; staged-diff check
# "touch *.x must not land seed-only changes".
#
# Usage (cwd = compiler/):
#   bash scripts/pin_gen_drift_gate.sh [-v]
# Exit codes: 0 = all pairs PASS/SKIP · 1 = ≥1 FAIL · 2 = env/usage error.
# PLATFORM: SHARED — cc/nm/sed only; Darwin leading underscores normalized.
set -uo pipefail
cd "$(dirname "$0")/.."

VERBOSE=0
[ "${1:-}" = "-v" ] && VERBOSE=1

TMP=$(mktemp -d 2>/dev/null || mktemp -d -t pindrift)
trap 'rm -rf "$TMP" 2>/dev/null || true' EXIT INT TERM

CC_BIN="${CC:-cc}"
command -v "$CC_BIN" >/dev/null 2>&1 || { echo "pin_gen_drift_gate: no cc" >&2; exit 2; }
command -v nm >/dev/null 2>&1 || { echo "pin_gen_drift_gate: no nm" >&2; exit 2; }

# Strong-text export symbol set of a C file (compiled). Darwin's leading
# underscore is stripped so both hosts compare identically.
t_syms() { # $1=src.c $2=out.o
  "$CC_BIN" -c -I. -Iinclude -Isrc "$1" -o "$2" 2>"$TMP/cc.err" || {
    echo "COMPILE-FAIL"
    return 0
  }
  nm -gU "$2" 2>/dev/null | awk '$2=="T"{print $3}' | sed 's/^_//' | sort -u
}

pass=0; fail=0; skip=0
# Archaeology-only stems (product path retired; pin kept for explicit
# archaeology/fallback flows that compile it with lenient flags inside larger
# TUs). Remove from this list if a stem re-enters the product path.
# lsp_io_gen: wave1036 Track L retirement — product = driver_leaf_x_to_o.sh
# catalog; the pin lacks standalone std_heap_* decls by design.
RETIRED_STEMS=" lsp_io_gen "
for pin in seeds/*.linux.x86_64.c; do
  [ -f "$pin" ] || continue
  stem=$(basename "$pin" .linux.x86_64.c)
  gen="$stem.c"
  case "$RETIRED_STEMS" in
    *" $stem "*)
      echo "SKIP  $stem (archaeology-only; product path retired)"
      skip=$((skip + 1))
      continue
      ;;
  esac
  if [ ! -f "$gen" ]; then
    echo "SKIP  $stem (no worktree gen; built on demand)"
    skip=$((skip + 1))
    continue
  fi
  pin_o="$TMP/pin_$stem.o"; gen_o="$TMP/gen_$stem.o"
  pin_syms=$(t_syms "$pin" "$pin_o")
  gen_syms=$(t_syms "$gen" "$gen_o")
  if [ "$pin_syms" = "COMPILE-FAIL" ] || [ "$gen_syms" = "COMPILE-FAIL" ]; then
    echo "FAIL  $stem: compile failed ($([ "$pin_syms" = "COMPILE-FAIL" ] && echo pin || echo gen); see stderr below)"
    [ "$VERBOSE" = "1" ] && cat "$TMP/cc.err" >&2
    fail=$((fail + 1))
    continue
  fi
  only_pin=$(comm -23 <(printf '%s\n' "$pin_syms") <(printf '%s\n' "$gen_syms"))
  only_gen=$(comm -13 <(printf '%s\n' "$pin_syms") <(printf '%s\n' "$gen_syms"))
  if [ -z "$only_pin" ] && [ -z "$only_gen" ]; then
    echo "PASS  $stem ($(printf '%s\n' "$pin_syms" | grep -c .) T syms)"
    pass=$((pass + 1))
  else
    echo "FAIL  $stem: T symbol drift"
    [ -n "$only_pin" ] && printf '      only-in-pin  : %s\n' $(printf '%s\n' "$only_pin" | head -8 |
      tr '\n' ' ') >&2
    [ -n "$only_gen" ] && printf '      only-in-gen  : %s\n' $(printf '%s\n' "$only_gen" | head -8 |
      tr '\n' ' ') >&2
    [ "$VERBOSE" = "1" ] && { printf '%s\n' "$only_pin" "$only_gen" | sed 's/^/      /' >&2; }
    fail=$((fail + 1))
  fi
done

echo "pin_gen_drift_gate: pass=$pass fail=$fail skip=$skip"
[ "$fail" -eq 0 ] || exit 1
exit 0
