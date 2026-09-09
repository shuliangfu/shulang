#!/usr/bin/env bash
# compiler_all_ci.sh — R5 CI / compiler-all shell body (wave784 · B6)
#
# Authority (G.7):
#   Owns the *policy and sequence* of historical
#   `make -C compiler OPT=1 all` (host-cc `xlang` + `xlang-c` / seed path).
#   Distinct from product `./xbuild all` (g05 relink via build_tool).
#
#   Residual after this wave (honest):
#     - Leaf .o builds still use the Makefile graph (B7A/B7B)
#     - wave786 B7D: default `make xlang` → g05_prepare_and_relink (product link)
#     - Physical delete of compiler/Makefile still blocked (Windows gate + B7A/B)
#   This wave is NOT physical delete and does NOT re-list .o paths.
#
# Entry points (single body):
#   ./xbuild compiler-all | ci-all   → this script (OPT default 1)
#   make -C compiler [OPT=1] all     → thin-call this script
#   bash compiler/scripts/compiler_all_ci.sh [--check]
#
# Env:
#   OPT — wave880 policy when unset:
#         MAKELEVEL set (bare `make all`) → empty (do not force -O2);
#         direct call (`xbuild compiler-all` / CI) → 1 (historical CI -O2).
#         Explicit OPT=0|1|empty from process env / `make OPT=1 all` always wins
#         (GNU make exports command-line vars into recipe env).
#   MAKE — make binary (default: make)
#   TARGET — product host-cc binary name (default: xlang)
#   XLANG_C — C frontend name (default: xlang-c)
#   XLANG_RUN_ALL_BOOTSTRAP_XLANG=1 — alternate: bootstrap-driver-seed only
#         (run-all seed path; do not overwrite with C-only all)
#   XLANG_SKIP_SUBSCRIPT_MAKE — forwarded to make for xlang-c preserve rules
#
# PLATFORM: SHARED — orchestration identical; leaf recipes keep platform ABI.
# Wave: 784 B6 R5 body swallow (Makefile thin-call only).
# Wave: 880 B7B — drop Makefile multi-token OPT/MAKE/TARGET inject; shell owns defaults.

set -euo pipefail

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname "${BASH_SOURCE[0]:-$0}")" && pwd)"
COMPILER_DIR="$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)"
cd "$COMPILER_DIR"

MODE="run"
if [ "${1:-}" = "--check" ] || [ "${1:-}" = "check" ]; then
  MODE="check"
fi

note() { echo "compiler_all_ci: $*" >&2; }
bad() { echo "compiler_all_ci: FAIL: $*" >&2; fail=1; }

if [ "$MODE" = "check" ]; then
  fail=0
  ROOT="$(CDPATH= cd -- "$COMPILER_DIR/.." && pwd)"
  XCODE="$ROOT/xlang-build.sh"
  MF="$COMPILER_DIR/Makefile"

  if [ ! -f "$XCODE" ]; then
    bad "missing xlang-build.sh"
  else
    # Outer entry must call this script (not bare run_compiler_make OPT=1 all only).
    if ! grep -q 'compiler_all_ci\.sh' "$XCODE"; then
      bad "xlang-build.sh must wire compiler-all → compiler_all_ci.sh (wave784)"
    else
      note "xbuild compiler-all wires compiler_all_ci.sh"
    fi
    if grep -nE 'compiler-all\|ci-all\)' -A6 "$XCODE" 2>/dev/null \
      | grep -q 'run_compiler_make.*OPT=.*all' \
      && ! grep -nE 'compiler-all\|ci-all\)' -A8 "$XCODE" 2>/dev/null \
        | grep -q 'compiler_all_ci\.sh'; then
      bad "xbuild compiler-all still bare run_compiler_make OPT all without shell body"
    fi
  fi

  if [ ! -f "$MF" ]; then
    # wave944 post_ship: Makefile physically deleted (wave941); shell body is authority.
    note "Makefile absent (wave944 post_ship) — compiler_all_ci.sh is CI all authority"
  else
    # all: must thin-call this script (not make-deps graph only).
    if ! awk '
      /^all:/ { in_all=1; body=""; next }
      in_all && /^[^[:space:]#]/ { exit (body ~ /compiler_all_ci\.sh/) ? 0 : 1 }
      in_all { body = body $0 "\n" }
      END { exit (body ~ /compiler_all_ci\.sh/) ? 0 : 1 }
    ' "$MF"; then
      bad "Makefile all must thin-call scripts/compiler_all_ci.sh (wave784)"
    else
      note "Makefile all thin-calls compiler_all_ci.sh"
    fi
    # Must not keep old dependency-style all: TARGET XLANG_C as the only body.
    if grep -E '^all:.*\$\(TARGET\)|all:.*bootstrap-driver-seed' "$MF" \
      | grep -vq 'compiler_all_ci'; then
      # dependency-only all: lines are residual if still present without recipe body
      if grep -qE '^all:[[:space:]]*(\$\(TARGET\)|bootstrap-driver-seed)' "$MF"; then
        bad "Makefile still has dependency-only all: graph (must be thin shell wave784)"
      fi
    fi
  fi

  # Policy markers present in this body (absolute path: we already cd'ed to compiler/)
  _self="$SCRIPT_DIR/compiler_all_ci.sh"
  if ! grep -q 'XLANG_RUN_ALL_BOOTSTRAP_XLANG' "$_self"; then
    bad "body must honor XLANG_RUN_ALL_BOOTSTRAP_XLANG alternate path"
  fi
  if ! grep -qE 'OPT|TARGET|XLANG_C' "$_self"; then
    bad "body must name OPT/TARGET/XLANG_C policy"
  fi
  # wave944: 0-make path must be present in body.
  if ! grep -q 'g05_prepare_and_relink\|_cm_all_shell\|bootstrap_driver_seed' "$_self"; then
    bad "body must own 0-make g05/bootstrap shell path (wave944)"
  fi
  unset _self

  if [ "$fail" -ne 0 ]; then
    echo "compiler_all_ci: CHECK FAILED" >&2
    exit 1
  fi
  echo "compiler_all_ci: CHECK OK (wave784 B6 R5 shell body · wave944 0-make)"
  exit 0
fi

# --- run mode ---
# OPT policy (wave880):
#   unset + MAKELEVEL → empty (bare make all: no force -O2)
#   unset + direct    → 1 (xbuild compiler-all / CI historical)
#   set (incl. empty) → honor as-is (make OPT= / make OPT=1 / env)
if [ -z "${OPT+set}" ]; then
  if [ -n "${MAKELEVEL:-}" ]; then
    OPT=
  else
    OPT=1
  fi
fi
MAKE="${MAKE:-make}"
TARGET="${TARGET:-xlang}"
XLANG_C="${XLANG_C:-xlang-c}"

export MAKE TARGET XLANG_C
# Forward optional flags make recipes still consume.
if [ -n "${XLANG_SKIP_SUBSCRIPT_MAKE+set}" ]; then
  export XLANG_SKIP_SUBSCRIPT_MAKE
fi
if [ -n "${XLANG_RUN_ALL_BOOTSTRAP_XLANG+set}" ]; then
  export XLANG_RUN_ALL_BOOTSTRAP_XLANG
fi

# wave944: 0-make after physical delete. Prefer shell authorities; optional make
# only when compiler/Makefile still exists (legacy mid-migration hosts).
_cm_all_shell() {
  if [ "${XLANG_RUN_ALL_BOOTSTRAP_XLANG:-}" = "1" ]; then
    note "XLANG_RUN_ALL_BOOTSTRAP_XLANG=1 → bootstrap_driver_seed.sh (0-make)"
    bash scripts/bootstrap_driver_seed.sh
    return $?
  fi
  # Default CI: product link via g05 + xlang-c alias sync (wave786 + wave876).
  note "CI → OPT=${OPT:-} $TARGET via g05_prepare_and_relink + ensure_xlang_c (wave944 0-make)"
  if [ -f scripts/g05_prepare_and_relink.sh ]; then
    FULL="${FULL:-0}" bash scripts/g05_prepare_and_relink.sh || return $?
  elif [ -f scripts/build_xlang_asm.sh ]; then
    bash scripts/build_xlang_asm.sh || return $?
  else
    note "FAIL: no g05_prepare_and_relink / build_xlang_asm"
    return 1
  fi
  if [ -f scripts/ensure_xlang_c.sh ]; then
    bash scripts/ensure_xlang_c.sh ensure "$XLANG_C" || return $?
  fi
  # Honor TARGET alias: if xlang_asm requested name differs, leave g05 outputs.
  return 0
}

if [ -f Makefile ] && [ "${XLANG_COMPILER_ALL_FORCE_SHELL:-0}" != "1" ]; then
  # Legacy thin residual (should not run on tip after wave941).
  mk() {
    # shellcheck disable=SC2086
    "$MAKE" "$@"
  }
  if [ "${XLANG_RUN_ALL_BOOTSTRAP_XLANG:-}" = "1" ]; then
    note "XLANG_RUN_ALL_BOOTSTRAP_XLANG=1 → make bootstrap-driver-seed (legacy MF present)"
    mk bootstrap-driver-seed
  else
    note "CI → OPT=${OPT:-} make $TARGET $XLANG_C (legacy MF present)"
    if [ -n "${OPT}" ]; then
      mk OPT="$OPT" "$TARGET" "$XLANG_C"
    else
      mk "$TARGET" "$XLANG_C"
    fi
  fi
else
  _cm_all_shell
fi

# 7.4.4 v2 CI wiring (2026-09-10): pin↔gen T-symbol freshness gate after the
# product link — catches "pin edited in git, worktree gen stale" drift before
# it ships. Non-fatal for now (advisory in the all/CI flow; the standalone
# ./xbuild drift-gate exits 1 on drift). G.7 body = pin_gen_drift_gate.sh.
# PLATFORM: SHARED.
if [ -f scripts/pin_gen_drift_gate.sh ]; then
  note "CI → pin_gen_drift_gate (advisory)"
  bash scripts/pin_gen_drift_gate.sh || note "WARN: drift-gate reported drift — run ./xbuild drift-gate"
else
  note "WARN: pin_gen_drift_gate.sh missing (7.4.4 v2)"
fi

note "done (xlang product g05 link · xlang-c seed; wave944 0-make)"
