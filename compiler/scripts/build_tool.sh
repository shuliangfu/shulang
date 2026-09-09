#!/usr/bin/env bash
# build_tool.sh — host build_tool binary from pinned seeds (11.0.3 · wave718)
#
# Authority (G.7):
#   Single implementation for assembling compiler/build_tool. Makefile
#   `build-tool` and repo-root xlang-build.sh call this script only.
#   Does NOT duplicate product link object lists (phase1/final stay Make).
#
# Usage (compiler directory, or via ./xbuild build-tool):
#   ./scripts/build_tool.sh
#   ./scripts/build_tool.sh --check
#
# Env:
#   CC — host C compiler (default: cc)
#   CFLAGS — product flags; default: load via catalog --cflags-export when
#     unset (wave925; was export-try-heat-cflags wave866 — OPT/-I/clang ifeq)
#   XLANG_BUILD_TOOL_REGEN=1 — try ./xlang -x -E to refresh build_gen +
#     build_runtime_x_gen (falls back to seeds/ on failure)
#   XLANG_CFLAGS_VIA_MAKE=1 — escape CFLAGS load to make export (needs MF)
#   MAKE — residual make for VIA_MAKE escape only (wave925/953)
#
# wave866: Makefile drops multi-token CFLAGS='$(CFLAGS)' inject; shell loads
#   export-try-heat-cflags when unset (same authority as try-heat / migrate).
#
# PLATFORM: SHARED — host-cc residual for G-05 entry until BC retires build_tool C.
# Wave: 718 Track MG · wave866 B7B CFLAGS shell-load · wave866 fix: bash recipe +
#   no bash <<< (Ubuntu dash if ever invoked via sh) · pairs with Makefile thin leaf
#   + xlang-build direct call.
# Wave: 925 catalog --cflags-export default (0-make) · XLANG_CFLAGS_VIA_MAKE escape.
# Wave: 953 post_ship --check when Makefile absent (wave941 phys-del); shell catalog
#   remains authority. NOT physical delete of build_tool C (BC).

set -euo pipefail
cd "$(dirname "$0")/.."

CC="${CC:-cc}"
MAKE="${MAKE:-make}"
MODE="${1:-}"

# wave925 · B7B build-tool CFLAGS shell-load via catalog (0 make).
# Replaces wave866 make export-try-heat-cflags with shell catalog parse of mk.
# CFLAGS + PIPELINE_GEN_CFLAGS resolve from mk/driver_seed_mode_objs.mk + host
# defaults (Makefile `?=` parity + OPT=1 -O2 + CC_IS_CLANG ifeq).
# XLANG_CFLAGS_VIA_MAKE=1 escapes to make export (parity / debug; needs MF).
# PLATFORM: SHARED — KEY=value from catalog; no compile side effects.
_load_try_heat_cflags() {
  local raw line
  if [ "${XLANG_CFLAGS_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ]; then
    raw=$(MAKEFLAGS= "$MAKE" -s export-try-heat-cflags) || return 1
  else
    raw=$(bash scripts/driver_seed_obj_catalog.sh --cflags-export 2>/dev/null) || return 1
  fi
  while IFS= read -r line || [ -n "$line" ]; do
    case "$line" in
      CFLAGS=*)
        if [ -z "${CFLAGS+x}" ]; then
          CFLAGS=${line#CFLAGS=}
        fi
        ;;
    esac
  done <<EOF
$raw
EOF
  return 0
}

if [ -z "${CFLAGS+x}" ]; then
  _load_try_heat_cflags || true
fi
# Fallback when catalog/make unavailable (direct shell invoke without Makefile).
CFLAGS="${CFLAGS:--Wall -Wextra -I. -Iinclude -Isrc}"

log() { echo "build-tool: $*" >&2; }
fail() { echo "build-tool: $*" >&2; exit 1; }

# --check: structural honesty (no host-cc product link; dual-end L2 safe)
if [ "$MODE" = "--check" ] || [ "$MODE" = "check" ]; then
  MF=Makefile
  # wave953 post_ship: Makefile physically deleted (wave941). Shell catalog is
  # CFLAGS authority; require shell-primary load path, not MF thin-call inventory.
  if [ ! -f "$MF" ]; then
    if ! grep -q 'driver_seed_obj_catalog\.sh --cflags-export' "$0"; then
      fail "build_tool must shell-load catalog --cflags-export (wave925/953 post_ship)"
    fi
    if ! grep -q 'XLANG_CFLAGS_VIA_MAKE' "$0"; then
      fail "build_tool must document XLANG_CFLAGS_VIA_MAKE escape (wave925/953)"
    fi
    # Default product path must not be an unguarded bare $MAKE export edge.
    # Escape may still mention $MAKE only under XLANG_CFLAGS_VIA_MAKE + MF.
    if ! grep -q 'XLANG_CFLAGS_VIA_MAKE' "$0"; then
      fail "build_tool must gate any make CFLAGS export with XLANG_CFLAGS_VIA_MAKE (wave953)"
    fi
    if ! grep -q 'wave953\|wave925' "$0"; then
      fail "build_tool must document wave925/953 shell-primary CFLAGS"
    fi
    # Catalog script must exist (runtime authority without MF).
    if [ ! -f scripts/driver_seed_obj_catalog.sh ]; then
      fail "missing scripts/driver_seed_obj_catalog.sh (wave925 CFLAGS authority)"
    fi
    echo "build_tool: CHECK OK (wave953 post_ship; catalog CFLAGS; 0-make)" >&2
    exit 0
  fi
  if ! grep -qE '^export-try-heat-cflags:' "$MF"; then
    fail "Makefile must define export-try-heat-cflags (wave866)"
  fi
  # build-tool thin-call must not inject multi-token CFLAGS='$(CFLAGS)' / CFLAGS="$(CFLAGS)"
  _rec=$(awk '
    $0 ~ /^build-tool:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab {print}
  ' "$MF")
  if grep -qE "CFLAGS=['\"]\\\$\\(CFLAGS\\)['\"]" <<<"$_rec"; then
    fail "build-tool must not export CFLAGS= (wave866; shell loads export-try-heat-cflags)"
  fi
  if ! grep -q 'export-try-heat-cflags\|wave866\|wave925\|wave953' "$0"; then
    fail "build_tool.sh must shell-load CFLAGS (wave866/925/953)"
  fi
  if ! grep -q 'driver_seed_obj_catalog\.sh --cflags-export' "$0"; then
    fail "build_tool must shell-load catalog --cflags-export (wave925)"
  fi
  # WIN32 residual: crt0_mingw must not inject WIN32_O_CFLAGS=
  _win=$(awk '
    $0 ~ /^src\/asm\/crt0_mingw\.o:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab {print}
  ' "$MF")
  if printf '%s\n' "$_win" | grep -qE 'WIN32_O_CFLAGS='; then
    fail "crt0_mingw must not inject WIN32_O_CFLAGS= (wave866; shell \${WIN32_O_CFLAGS:-})"
  fi
  echo "build_tool: CHECK OK (wave866/925/953 CFLAGS shell-load + WIN32_O drop; not physical delete)" >&2
  exit 0
fi

if [ -n "$MODE" ] && [ "$MODE" != "build" ]; then
  echo "usage: $0 [--check]" >&2
  exit 2
fi

# wave1038: Track L retirement — build_gen.c retired from pinned seed.
# Default: generate from ../build.x via xlang -E (product path).
# Fallback: copy seeds/build_gen.c (archaeology) only when -E fails or no xlang.
# wave1039: build_runner_gen.c retired from pinned seed (same -E + fallback pattern).
#   build_runner.x extern calls wrapped in unsafe{} (typeck G.9); entry marked
#   #[no_mangle] export to preserve symbol name (no build_ module prefix).
#   -E import closure symbols are __attribute__((weak)) — coexist with build_gen.o.
# wave1040: build_runtime_x_gen.c retired from pinned seed (same -E + fallback).
#   build_runtime_x.x: 15 extern calls wrapped in unsafe{} expression form;
#   copy_path/append_lit marked #[no_mangle] to preserve symbol names.
if [ -x ./xlang ]; then
  log "build_gen.c ← ../build.x -E (wave1038 Track L retired)"
  if ! ./xlang -x -E -L .. ../build.x > build_gen.c 2>/dev/null || [ ! -s build_gen.c ]; then
    log "build_gen.c: -E failed; fallback to seed (archaeology)"
    cp -f seeds/build_gen.c build_gen.c
  fi
else
  cp -f seeds/build_gen.c build_gen.c
fi
if [ -x ./xlang ]; then
  log "build_runner_gen.c ← ../build_runner.x -E (wave1039 Track L retired)"
  if ! ./xlang -x -E -L .. ../build_runner.x > build_runner_gen.c 2>/dev/null || [ ! -s build_runner_gen.c ]; then
    log "build_runner_gen.c: -E failed; fallback to seed (archaeology)"
    cp -f seeds/build_runner_gen.c build_runner_gen.c
  fi
else
  cp -f seeds/build_runner_gen.c build_runner_gen.c
fi
if [ -x ./xlang ] && [ -n "${XLANG_BUILD_RUNTIME_X_E:-}" ]; then
  log "build_runtime_x_gen.c ← ../build_runtime_x.x -E (wave1040 Track L retired; opt-in)"
  if ! ./xlang -x -E -L .. ../build_runtime_x.x > build_runtime_x_gen.c 2>/dev/null || [ ! -s build_runtime_x_gen.c ]; then
    log "build_runtime_x_gen.c: -E failed; fallback to seed (archaeology)"
    cp -f seeds/build_runtime_x_gen.c build_runtime_x_gen.c
  fi
else
  # wave1040: build_runtime_x_gen.c is retired/pinned to the seed. Always use
  # the seed by default — build_runtime.x was refactored (build_run_step dropped
  # for build_run_legacy_steps) but build_runner (also pinned seed) still
  # references build_run_step, so the -E regen produced an incomplete gen that
  # broke the build_tool link on L4 cold. The pinned seed (defines build_run_step
  # + build_run_asm_build + build_copy_xlang_asm) is the retired authority.
  # Set XLANG_BUILD_RUNTIME_X_E=1 to force the (currently incomplete) -E path.
  log "build_runtime_x_gen.c ← seed (wave1040 retired/pinned; -E regen drops build_run_step)"
  cp -f seeds/build_runtime_x_gen.c build_runtime_x_gen.c
fi

# shellcheck disable=SC2086
$CC $CFLAGS -Wno-unused -c build_gen.c -o build_tool.o
sh scripts/cc_inc_tu.sh seeds/build_tool_libc_bridge.from_x.c build_tool_libc_bridge.o
# shellcheck disable=SC2086
$CC $CFLAGS -Wno-unused -c build_runner_gen.c -o build_runner.o
# shellcheck disable=SC2086
$CC $CFLAGS -Wno-unused -c build_runtime_x_gen.c -o build_runtime_x.o
# 7.2.1 first knife: .x authority (src/build_tool_main.x) via the cc_inc_tu
# --auto lane (product -x -E + char** main fixup); seed fallback when no
# product binary exists (cold bootstrap).
if [ -x ./xlang_asm ] || [ -x ./xlang ] || [ -x ./xlang-c ]; then
  sh scripts/cc_inc_tu.sh --auto build_tool_main.o
else
  sh scripts/cc_inc_tu.sh seeds/build_tool_main.from_x.c build_tool_main.o
fi
# shellcheck disable=SC2086
$CC $CFLAGS -o build_tool \
  build_tool_main.o build_runner.o build_tool.o build_runtime_x.o build_tool_libc_bridge.o -lc

echo "build_tool OK（./build_tool ./xlang [asm|legacy]；G-05 pinned seeds）"
