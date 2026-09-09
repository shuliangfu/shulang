#!/usr/bin/env bash
# ensure_archaeology_gen.sh — body of Track L retired archaeology *_gen.c leaves
# (11.1.6 · wave740 driver_*_gen subcmds + lsp_io_std_heap_gen.c)
#
# Authority (G.7):
#   Single implementation of optional workspace archaeology *_gen.c production.
#   Product link path does NOT consume these files (Track L: PREFER_X_O via
#   driver_leaf_x_to_o.sh + seeds/*_gen.linux.x86_64.c cold fallback only).
#   These gens exist for FORCE_REGEN / manual seed refresh / archaeology only.
#
#   Leaves:
#     driver_fmt_gen.c | driver_check_gen.c | driver_test_gen.c
#     driver_compile_gen.c | driver_build_gen.c | driver_run_gen.c
#     driver_emit_gen.c  (extra -L roots vs other subcmds)
#     lsp_io_std_heap_gen.c  (LSP_X_E_DIRS + strip host malloc/free/calloc extern)
#
#   ./xbuild archaeology-gen call this script (0× make for the gen body).
#   Missing xlang-c for force -E → scripts/ensure_xlang_c.sh (wave949; not $MAKE).
#
#   Product gens remain:
#     ensure_migrate_gen.sh (parser/typeck/codegen/lexer)
#     ensure_driver_gen.sh (driver_gen + preprocess_gen)
#     ensure_lsp_pipeline_gen.sh (lsp_diag/io/lsp + pipeline)
#
# Usage (cwd = compiler/):
#   bash scripts/ensure_archaeology_gen.sh              # all archaeology (default)
#   bash scripts/ensure_archaeology_gen.sh all
#   bash scripts/ensure_archaeology_gen.sh driver-all    # seven driver subcmd gens
#   bash scripts/ensure_archaeology_gen.sh fmt|check|test|compile|build|run|emit
#   bash scripts/ensure_archaeology_gen.sh lsp_io_std_heap|std_heap
#   ./xbuild archaeology-gen | driver-subcmd-gen
#
# Env:
#   XLANG_FORCE_REGEN_GEN=1 — force -E regen (ignore local pin)
#   XLANG_C — binary name (default xlang-c)
#
# PLATFORM: SHARED shell orchestration; seed pins are host-portable C.
# wave829 (G.7 有则补全): FORCE dep-thin — Makefile prereqs FORCE+script only;
#   shell owns pin/FORCE_REGEN archaeology policy. NOT physical delete.
# Wave: 740 Track MG · pairs with Makefile thin leaves + xbuild archaeology-gen.

set -euo pipefail
cd "$(dirname "$0")/.."

XLANG_C="${XLANG_C:-xlang-c}"
XLANG_FORCE_REGEN_GEN="${XLANG_FORCE_REGEN_GEN:-0}"
MODE="${1:-all}"

# DRIVER_SUBCMD_DIRS: product authority mk/driver_subcmd_objs.mk (wave816).
# LSP_X_E_DIRS: product authority mk/x_e_dirs.mk (wave824).
# DRIVER_EMIT_E_DIRS: archaeology-only emit -E roots (not product MAIN/LSP/PIPELINE).
# Load product -L inventories from mk (G.7; not dual hardcode).
_DRIVER_SUBCMD_MK="mk/driver_subcmd_objs.mk"
_X_E_DIRS_MK="mk/x_e_dirs.mk"
_mk_assign_val() {
  # First KEY = value line from mk (strip comments / trailing space).
  # PLATFORM: SHARED — pure text parse; no make.
  local key="$1"
  local mk="$2"
  local line
  line=$(grep -E "^${key}[[:space:]]*=" "$mk" 2>/dev/null | head -1 | sed "s/^${key}[[:space:]]*=[[:space:]]*//;s/#.*//;s/[[:space:]]*$//")
  printf '%s' "$line"
}
# bash 3.2: read -a from mk-owned lists (wave816/wave824; not dual inventory).
# shellcheck disable=SC2206
DRIVER_SUBCMD_DIRS=($(_mk_assign_val DRIVER_SUBCMD_DIRS "$_DRIVER_SUBCMD_MK"))
# shellcheck disable=SC2206
LSP_X_E_DIRS=($(_mk_assign_val LSP_X_E_DIRS "$_X_E_DIRS_MK"))
# emit Makefile: extra roots after DRIVER_SUBCMD_DIRS (archaeology-only; not in product E_DIRS mk).
DRIVER_EMIT_E_DIRS=(-L .. -L src -L src/lexer -L src/ast -L ../std/fs -L src/preprocess -L src/pipeline -L src/codegen)
if [ "${#DRIVER_SUBCMD_DIRS[@]}" -lt 2 ] || [ -z "${DRIVER_SUBCMD_DIRS[0]:-}" ]; then
  echo "ensure-archaeology-gen: failed to load DRIVER_SUBCMD_DIRS from $_DRIVER_SUBCMD_MK" >&2
  exit 2
fi
if [ "${#LSP_X_E_DIRS[@]}" -lt 2 ] || [ -z "${LSP_X_E_DIRS[0]:-}" ]; then
  echo "ensure-archaeology-gen: failed to load LSP_X_E_DIRS from $_X_E_DIRS_MK" >&2
  exit 2
fi

log() { echo "ensure-archaeology-gen: $*" >&2; }

seed_ok() {
  [ -f "$1" ]
}

# G.7 single authority for default xlang-c alias: ensure_xlang_c.sh (wave876/949).
# PLATFORM: SHARED — 0-make; SRC=bootstrap_xlangc must already exist (select seed).
ensure_xlang_c() {
  if [ -x "./$XLANG_C" ] || [ -f "./$XLANG_C" ]; then
    return 0
  fi
  log "ensure $XLANG_C via scripts/ensure_xlang_c.sh (missing binary for force -E)"
  bash scripts/ensure_xlang_c.sh ensure "$XLANG_C"
}

bytes_of() {
  # PLATFORM: SHARED — Darwin wc -c pads; tr -d spaces
  wc -c < "$1" | tr -d ' '
}

# ---------------------------------------------------------------------------
# Generic driver subcmd archaeology gen:
#   pin if non-empty and not FORCE_REGEN
#   else seed restore if empty + seed present
#   else xlang-c -E -E-extern (fallback seed on failure)
# ---------------------------------------------------------------------------
# $1 = out gen file (e.g. driver_fmt_gen.c)
# $2 = source .x (e.g. src/driver/fmt.x)
# $3 = seed path
# $4 = short label for log
# remaining args = -L dirs for -E (passed as array via nameref-style: use global or shift)
ensure_driver_subcmd_gen() {
  local out="$1" src_x="$2" seed="$3" label="$4"
  shift 4
  # remaining: -E lib dirs
  local e_dirs=("$@")
  local tmp
  tmp="${out}.tmp.$$"
  rm -f "$tmp"

  if [ -s "$out" ] && [ "$XLANG_FORCE_REGEN_GEN" != "1" ] \
     && ! { [ -e "$seed" ] && [ "$seed" -nt "$out" ]; }; then
    log "$out: pinned ($(bytes_of "$out") bytes; Track L retired — product uses ${out%_gen.c}_x.o; XLANG_FORCE_REGEN_GEN=1 to regen)"
  elif seed_ok "$seed" && { [ ! -s "$out" ] || [ "$seed" -nt "$out" ]; }; then
    # 7.4.4 v2: a pin newer than the worktree gen refreshes it (mtime trap —
    # existence-only "pinned" left stale gens after pin edits).
    cp -f "$seed" "$out"
    log "$out: restored from seed (pin newer; archaeology)"
  else
    log "$out: $XLANG_C -E -E-extern ($label archaeology)"
    ensure_xlang_c
    if "./$XLANG_C" "${e_dirs[@]}" -E -E-extern "$src_x" >"$tmp" 2>/dev/null \
      && [ -s "$tmp" ]; then
      mv -f "$tmp" "$out"
    elif seed_ok "$seed"; then
      rm -f "$tmp"
      cp -f "$seed" "$out"
      log "$out: fallback seed (xlang-c -E failed)"
    else
      rm -f "$tmp"
      log "$out: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi
  rm -f "$tmp" 2>/dev/null || true
  log "$out OK ($(bytes_of "$out") bytes)"
}

ensure_driver_fmt_gen() {
  ensure_driver_subcmd_gen driver_fmt_gen.c src/driver/fmt.x \
    seeds/driver_fmt_gen.linux.x86_64.c fmt "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_check_gen() {
  ensure_driver_subcmd_gen driver_check_gen.c src/driver/check.x \
    seeds/driver_check_gen.linux.x86_64.c check "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_test_gen() {
  ensure_driver_subcmd_gen driver_test_gen.c src/driver/test.x \
    seeds/driver_test_gen.linux.x86_64.c test "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_compile_gen() {
  ensure_driver_subcmd_gen driver_compile_gen.c src/driver/compile.x \
    seeds/driver_compile_gen.linux.x86_64.c compile "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_build_gen() {
  ensure_driver_subcmd_gen driver_build_gen.c src/driver/build.x \
    seeds/driver_build_gen.linux.x86_64.c build "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_run_gen() {
  ensure_driver_subcmd_gen driver_run_gen.c src/driver/run.x \
    seeds/driver_run_gen.linux.x86_64.c run "${DRIVER_SUBCMD_DIRS[@]}"
}
ensure_driver_emit_gen() {
  ensure_driver_subcmd_gen driver_emit_gen.c src/driver/emit.x \
    seeds/driver_emit_gen.linux.x86_64.c emit "${DRIVER_EMIT_E_DIRS[@]}"
}

# ---------------------------------------------------------------------------
# lsp_io_std_heap_gen.c
# Post: strip host malloc/free/calloc extern decls (sed; same as Makefile)
# ---------------------------------------------------------------------------
ensure_lsp_io_std_heap_gen() {
  local tmp seed="seeds/lsp_io_std_heap_gen.linux.x86_64.c"
  tmp="lsp_io_std_heap_gen.c.tmp.$$"
  rm -f "$tmp"

  if [ -s lsp_io_std_heap_gen.c ] && [ "$XLANG_FORCE_REGEN_GEN" != "1" ]; then
    log "lsp_io_std_heap_gen.c: pinned ($(bytes_of lsp_io_std_heap_gen.c) bytes; Track L retired — product uses lsp_io_std_heap_x.o)"
  elif seed_ok "$seed" && [ ! -s lsp_io_std_heap_gen.c ]; then
    cp -f "$seed" lsp_io_std_heap_gen.c
    log "lsp_io_std_heap_gen.c: restored from seed (archaeology)"
  else
    log "lsp_io_std_heap_gen.c: $XLANG_C -E -E-extern (archaeology)"
    ensure_xlang_c
    if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" src/lsp/lsp_io_std_heap.x -E -E-extern >"$tmp" 2>/dev/null \
      && [ -s "$tmp" ]; then
      mv -f "$tmp" lsp_io_std_heap_gen.c
    elif seed_ok "$seed"; then
      rm -f "$tmp"
      cp -f "$seed" lsp_io_std_heap_gen.c
      log "lsp_io_std_heap_gen.c: fallback seed (xlang-c -E failed)"
    else
      rm -f "$tmp"
      log "lsp_io_std_heap_gen.c: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi
  rm -f "$tmp" 2>/dev/null || true

  # PLATFORM: SHARED — strip host libc externs that -E may inject (parity Makefile)
  if [ -s lsp_io_std_heap_gen.c ]; then
    sed -i.bak '/^extern uint8_t \* malloc/d; /^extern void free(/d; /^extern uint8_t \* calloc/d' \
      lsp_io_std_heap_gen.c 2>/dev/null || true
    rm -f lsp_io_std_heap_gen.c.bak 2>/dev/null || true
  fi
  log "lsp_io_std_heap_gen.c OK ($(bytes_of lsp_io_std_heap_gen.c) bytes)"
}

ensure_driver_all() {
  ensure_driver_fmt_gen
  ensure_driver_check_gen
  ensure_driver_test_gen
  ensure_driver_compile_gen
  ensure_driver_build_gen
  ensure_driver_run_gen
  ensure_driver_emit_gen
}

ensure_all() {
  ensure_driver_all
  ensure_lsp_io_std_heap_gen
  echo "ensure-archaeology-gen OK (7 driver_*_gen + lsp_io_std_heap_gen ready)"
}

case "$MODE" in
  all|"")
    ensure_all
    ;;
  driver-all|driver_all|subcmd-all|subcmds)
    ensure_driver_all
    echo "ensure-archaeology-gen OK (7 driver_*_gen ready)"
    ;;
  fmt|driver_fmt|driver_fmt_gen.c)
    ensure_driver_fmt_gen
    ;;
  check|driver_check|driver_check_gen.c)
    ensure_driver_check_gen
    ;;
  test|driver_test|driver_test_gen.c)
    ensure_driver_test_gen
    ;;
  compile|driver_compile|driver_compile_gen.c)
    ensure_driver_compile_gen
    ;;
  build|driver_build|driver_build_gen.c)
    ensure_driver_build_gen
    ;;
  run|driver_run|driver_run_gen.c)
    ensure_driver_run_gen
    ;;
  emit|driver_emit|driver_emit_gen.c)
    ensure_driver_emit_gen
    ;;
  lsp_io_std_heap|std_heap|lsp_io_std_heap_gen.c|heap)
    ensure_lsp_io_std_heap_gen
    ;;
  -h|--help|help)
    cat <<'EOF'
Usage: ensure_archaeology_gen.sh [all|driver-all|fmt|check|test|compile|build|run|emit|lsp_io_std_heap]
  all (default)     — seven driver_*_gen.c + lsp_io_std_heap_gen.c
  driver-all        — driver subcmd gens only
  fmt|check|…|emit  — single driver subcmd gen
  lsp_io_std_heap   — lsp_io_std_heap_gen.c only
Env: XLANG_FORCE_REGEN_GEN=1 XLANG_C
Note: product link does not use these files (Track L PREFER_X_O).
EOF
    ;;
  *)
    log "unknown mode: $MODE (use all|driver-all|fmt|check|test|compile|build|run|emit|lsp_io_std_heap)"
    exit 2
    ;;
esac
