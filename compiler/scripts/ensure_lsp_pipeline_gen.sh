#!/usr/bin/env bash
# ensure_lsp_pipeline_gen.sh — body of product LSP + pipeline *_gen.c leaves
# (11.1.6 · wave739 lsp_diag/io/lsp_gen.c + pipeline_gen.c)
#
# Authority (G.7):
#   Single implementation of product LSP/pipeline *_gen.c production for:
#     lsp_diag_gen.c  (pin / seed / xlang-c -E only + C-04 aliases guard)
#     lsp_io_gen.c    (ARCHAEOLOGY — wave1036 Track L retired; product = catalog)
#     lsp_gen.c       (pin / seed / xlang-x|-c -E + g_lsp_state_buf sed post)
#     pipeline_gen.c  (pin / seed / force xlang-c -E + check_pipeline_gen_expr_i64_abi)
#   ./xbuild lsp-gen|pipeline-gen call this script (0× make for the gen body).
#   Missing xlang-c for force -E → scripts/ensure_xlang_c.sh (wave949; not $MAKE).
#   Frontend = ensure_migrate_gen.sh; driver path = ensure_driver_gen.sh.
#   Archaeology gens (lsp_io_std_heap_gen, driver_*_gen subcmds) =
#   ensure_archaeology_gen.sh (wave740; Track L retired product path).
#
# Usage (cwd = compiler/):
#   bash scripts/ensure_lsp_pipeline_gen.sh              # product all (default)
#   bash scripts/ensure_lsp_pipeline_gen.sh all
#   bash scripts/ensure_lsp_pipeline_gen.sh lsp|lsp-all  # three LSP gens
#   bash scripts/ensure_lsp_pipeline_gen.sh lsp_diag|lsp_io|lsp
#   bash scripts/ensure_lsp_pipeline_gen.sh pipeline
#   ./xbuild lsp-gen | pipeline-gen | lsp-pipeline-gen
#
# Env:
#   XLANG_FORCE_REGEN_GEN=1 — force -E regen (ignore local pin)
#   XLANG_C / XLANG_X — binary names (default xlang-c / xlang-x)
#
# PLATFORM: SHARED shell orchestration; product seed pins are host-portable C.
# wave829 (G.7 有则补全): FORCE dep-thin — Makefile prereqs FORCE+script only;
#   shell owns pin/seed/FORCE_REGEN policy. NOT physical delete.
# wave837 (G.7 有则补全): pipeline_gen.c file target also FORCE+script (was empty
#   prereq; sibling of wave834 bootstrap-pipeline phony + wave829 17 gen leaves).
# Wave: 739 Track MG · pairs with Makefile thin leaves + xbuild lsp/pipeline-gen.

set -euo pipefail
cd "$(dirname "$0")/.."

XLANG_C="${XLANG_C:-xlang-c}"
XLANG_X="${XLANG_X:-xlang-x}"
XLANG_FORCE_REGEN_GEN="${XLANG_FORCE_REGEN_GEN:-0}"
MODE="${1:-all}"

# LSP_X_E_DIRS / PIPELINE_X_E_DIRS: G.7 single authority mk/x_e_dirs.mk (wave824).
# Do not hardcode a second -L inventory here.
_X_E_DIRS_MK="mk/x_e_dirs.mk"
_mk_assign_val() {
  # First KEY = value line from mk (strip comments / trailing space).
  # PLATFORM: SHARED — pure text parse; no make.
  local key="$1"
  local line
  line=$(grep -E "^${key}[[:space:]]*=" "$_X_E_DIRS_MK" 2>/dev/null | head -1 | sed "s/^${key}[[:space:]]*=[[:space:]]*//;s/#.*//;s/[[:space:]]*$//")
  printf '%s' "$line"
}
# bash 3.2: read -a from mk-owned lists (wave824; not dual inventory).
# shellcheck disable=SC2206
LSP_X_E_DIRS=($(_mk_assign_val LSP_X_E_DIRS))
# shellcheck disable=SC2206
PIPELINE_X_E_DIRS=($(_mk_assign_val PIPELINE_X_E_DIRS))
if [ "${#LSP_X_E_DIRS[@]}" -lt 2 ] || [ -z "${LSP_X_E_DIRS[0]:-}" ]; then
  echo "ensure-lsp-pipeline-gen: failed to load LSP_X_E_DIRS from $_X_E_DIRS_MK" >&2
  exit 2
fi
if [ "${#PIPELINE_X_E_DIRS[@]}" -lt 2 ] || [ -z "${PIPELINE_X_E_DIRS[0]:-}" ]; then
  echo "ensure-lsp-pipeline-gen: failed to load PIPELINE_X_E_DIRS from $_X_E_DIRS_MK" >&2
  exit 2
fi

log() { echo "ensure-lsp-pipeline-gen: $*" >&2; }

# Product pin seeds (*.linux.x86_64.c) are host-portable generated C.
# PLATFORM: SHARED — cold start on Darwin/Windows uses the same pins.
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
# lsp_diag_gen.c
# Prefer xlang-c -E only (xlang-x -x -E historically produces broken TU).
# Post: require C-04 -E-extern TU aliases marker, else restore seed.
# ---------------------------------------------------------------------------
ensure_lsp_diag_gen() {
  local tmp seed="seeds/lsp_diag_gen.linux.x86_64.c"
  tmp="lsp_diag_gen.c.tmp.$$"
  rm -f "$tmp"

  if [ -s lsp_diag_gen.c ] && [ "$XLANG_FORCE_REGEN_GEN" != "1" ] \
     && ! { [ -e "$seed" ] && [ "$seed" -nt lsp_diag_gen.c ]; }; then
    log "lsp_diag_gen.c: pinned ($(bytes_of lsp_diag_gen.c) bytes; XLANG_FORCE_REGEN_GEN=1 to regen)"
  elif seed_ok "$seed" && { [ ! -s lsp_diag_gen.c ] || [ "$seed" -nt lsp_diag_gen.c ]; }; then
    # 7.4.4 v2: a pin newer than the worktree gen refreshes it (mtime trap).
    cp -f "$seed" lsp_diag_gen.c
    log "lsp_diag_gen.c: restored from $seed (pin newer)"
  else
    log "lsp_diag_gen.c: $XLANG_C -E -E-extern (avoid xlang-x -x -E: broken TU for lsp_diag.x)"
    ensure_xlang_c
    if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" -L src/pipeline src/lsp/lsp_diag.x -E -E-extern >"$tmp" 2>/dev/null \
      && [ -s "$tmp" ]; then
      mv -f "$tmp" lsp_diag_gen.c
    elif seed_ok "$seed"; then
      rm -f "$tmp"
      cp -f "$seed" lsp_diag_gen.c
      log "lsp_diag_gen.c: fallback seed (xlang-c -E failed)"
    else
      rm -f "$tmp"
      log "lsp_diag_gen.c: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi
  rm -f "$tmp" 2>/dev/null || true

  if ! grep -q 'C-04 -E-extern TU aliases' lsp_diag_gen.c 2>/dev/null; then
    if seed_ok "$seed"; then
      cp -f "$seed" lsp_diag_gen.c
      log "lsp_diag_gen.c: restored seed (missing C-04 -E-extern TU aliases)"
    else
      log "lsp_diag_gen.c: FAIL missing C-04 -E-extern TU aliases (need xlang-c -E-extern codegen; no perl fallback)"
      exit 1
    fi
  fi
  log "lsp_diag_gen.c OK ($(bytes_of lsp_diag_gen.c) bytes)"
}

# ---------------------------------------------------------------------------
# lsp_io_gen.c — ARCHAEOLOGY ONLY (wave1036 Track L retirement)
# Product path: lsp_io_x.o built via driver_leaf_x_to_o.sh catalog (.x → -E → .o)
# This function is retained for archaeology/verification only:
#   - Called explicitly: bash ensure_lsp_pipeline_gen.sh lsp_io
#   - Called as fallback: ensure_gen_x_o.sh build_lsp_io_x() when Track L fails
# In the all/lsp-all flow, lsp_io_gen.c is skipped (Track L catalog owns product).
# ---------------------------------------------------------------------------
ensure_lsp_io_gen() {
  # wave1036: Track L retirement — skip in product flow (all/lsp-all).
  # Only regenerate when explicitly requested (archaeology) or as gen.c fallback.
  if [ "$MODE" = "all" ] || [ "$MODE" = "lsp" ] || [ "$MODE" = "lsp-all" ] || [ "$MODE" = "lsp_all" ]; then
    log "lsp_io_gen.c: SKIP (wave1036 Track L retired; product path = driver_leaf_x_to_o.sh catalog)"
    return 0
  fi
  log "lsp_io_gen.c: ARCHAEOLOGY mode (wave1036; product uses Track L catalog)"
  local tmp seed="seeds/lsp_io_gen.linux.x86_64.c"
  tmp="lsp_io_gen.c.tmp.$$"
  rm -f "$tmp"

  if [ -s lsp_io_gen.c ] && [ "$XLANG_FORCE_REGEN_GEN" != "1" ] \
     && ! { [ -e "$seed" ] && [ "$seed" -nt lsp_io_gen.c ]; }; then
    log "lsp_io_gen.c: pinned ($(bytes_of lsp_io_gen.c) bytes)"
  elif seed_ok "$seed" && { [ ! -s lsp_io_gen.c ] || [ "$seed" -nt lsp_io_gen.c ]; }; then
    # 7.4.4 v2: a pin newer than the worktree gen refreshes it (mtime trap).
    cp -f "$seed" lsp_io_gen.c
    log "lsp_io_gen.c: restored from $seed (pin newer)"
  elif [ -f "./$XLANG_X" ]; then
    log "lsp_io_gen.c: ./$XLANG_X -x -E ..."
    "./$XLANG_X" -x -E "${LSP_X_E_DIRS[@]}" -E-extern src/lsp/lsp_io.x >"$tmp" 2>/dev/null || true
    if [ -s "$tmp" ] && ! grep -q 'lsp_io -E-extern stubs (io.o' "$tmp"; then
      mv -f "$tmp" lsp_io_gen.c
    else
      rm -f "$tmp"
      log "lsp_io_gen.c: fallback to xlang-c -E -E-extern (C-04)"
      ensure_xlang_c
      if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" src/lsp/lsp_io.x -E -E-extern >"$tmp" 2>/dev/null \
        && [ -s "$tmp" ]; then
        mv -f "$tmp" lsp_io_gen.c
      elif seed_ok "$seed"; then
        rm -f "$tmp"
        cp -f "$seed" lsp_io_gen.c
        log "lsp_io_gen.c: fallback seed"
      else
        rm -f "$tmp"
        log "lsp_io_gen.c: FAIL (xlang-c -E failed and no seed)"
        exit 1
      fi
    fi
  else
    ensure_xlang_c
    if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" src/lsp/lsp_io.x -E -E-extern >"$tmp" 2>/dev/null \
      && [ -s "$tmp" ]; then
      mv -f "$tmp" lsp_io_gen.c
    elif seed_ok "$seed"; then
      rm -f "$tmp"
      cp -f "$seed" lsp_io_gen.c
      log "lsp_io_gen.c: fallback seed"
    else
      rm -f "$tmp"
      log "lsp_io_gen.c: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi
  rm -f "$tmp" 2>/dev/null || true
  log "lsp_io_gen.c OK ($(bytes_of lsp_io_gen.c) bytes)"
}

# ---------------------------------------------------------------------------
# lsp_gen.c
# Prefer xlang-x with typeck_lsp_main_impl and without old lsp_io_x stub block.
# Post: rewrite state_buf → g_lsp_state_buf (Makefile sed parity).
# ---------------------------------------------------------------------------
ensure_lsp_gen() {
  local tmp seed="seeds/lsp_gen.linux.x86_64.c"
  tmp="lsp_gen.c.tmp.$$"
  rm -f "$tmp"

  if [ -s lsp_gen.c ] && [ "$XLANG_FORCE_REGEN_GEN" != "1" ] \
     && ! { [ -e "$seed" ] && [ "$seed" -nt lsp_gen.c ]; }; then
    log "lsp_gen.c: pinned ($(bytes_of lsp_gen.c) bytes)"
  elif seed_ok "$seed" && { [ ! -s lsp_gen.c ] || [ "$seed" -nt lsp_gen.c ]; }; then
    # 7.4.4 v2: a pin newer than the worktree gen refreshes it (mtime trap).
    cp -f "$seed" lsp_gen.c
    log "lsp_gen.c: restored from $seed (pin newer)"
  elif [ -f "./$XLANG_X" ]; then
    log "lsp_gen.c: ./$XLANG_X -x -E ..."
    "./$XLANG_X" -x -E "${LSP_X_E_DIRS[@]}" -E-extern src/lsp/lsp.x >"$tmp" 2>/dev/null || true
    if [ -s "$tmp" ] && grep -q typeck_lsp_main_impl "$tmp" \
      && ! grep -q 'lsp.x -E-extern stubs (lsp_io_x' "$tmp"; then
      mv -f "$tmp" lsp_gen.c
    else
      rm -f "$tmp"
      log "lsp_gen.c: xlang-x failed or old extern block, fallback to xlang-c -E -E-extern"
      ensure_xlang_c
      if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" src/lsp/lsp.x -E -E-extern >"$tmp" 2>/dev/null \
        && [ -s "$tmp" ]; then
        mv -f "$tmp" lsp_gen.c
      elif seed_ok "$seed"; then
        rm -f "$tmp"
        cp -f "$seed" lsp_gen.c
        log "lsp_gen.c: fallback seed"
      else
        rm -f "$tmp"
        log "lsp_gen.c: FAIL (xlang-c -E failed and no seed)"
        exit 1
      fi
    fi
  else
    ensure_xlang_c
    if "./$XLANG_C" "${LSP_X_E_DIRS[@]}" src/lsp/lsp.x -E -E-extern >"$tmp" 2>/dev/null \
      && [ -s "$tmp" ]; then
      mv -f "$tmp" lsp_gen.c
    elif seed_ok "$seed"; then
      rm -f "$tmp"
      cp -f "$seed" lsp_gen.c
      log "lsp_gen.c: fallback seed"
    else
      rm -f "$tmp"
      log "lsp_gen.c: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi
  rm -f "$tmp" 2>/dev/null || true

  # Post-normalize (Makefile sed parity — runs on pin and regen)
  # PLATFORM: SHARED — sed -i.bak works on GNU sed and BSD sed (Darwin).
  sed -i.bak 's/uint8_t state_buf\[16388\] = { 0 }/extern uint8_t g_lsp_state_buf[16388]/' lsp_gen.c 2>/dev/null || true
  sed -i.bak 's/(state_buf)/(g_lsp_state_buf)/g' lsp_gen.c 2>/dev/null || true
  rm -f lsp_gen.c.bak 2>/dev/null || true
  log "lsp_gen.c OK ($(bytes_of lsp_gen.c) bytes)"
}

# ---------------------------------------------------------------------------
# pipeline_gen.c
# Pin-first; empty → seed; force or missing → xlang-c -E then seed fallback.
# Always finish with check_pipeline_gen_expr_i64_abi.sh (P0-4 int64_t int_val).
# ---------------------------------------------------------------------------
ensure_pipeline_gen() {
  local seed="seeds/pipeline_gen.linux.x86_64.c"

  if [ "$XLANG_FORCE_REGEN_GEN" = "1" ]; then
    ensure_xlang_c
    if "./$XLANG_C" "${PIPELINE_X_E_DIRS[@]}" -E -E-extern src/pipeline/pipeline.x >pipeline_gen.c; then
      log "pipeline_gen.c: forced regen via $XLANG_C -E -E-extern"
    else
      log "pipeline_gen.c: FAIL forced -E"
      exit 1
    fi
  elif [ -s pipeline_gen.c ] \
     && ! { [ -e "$seed" ] && [ "$seed" -nt pipeline_gen.c ]; }; then
    log "pipeline_gen.c: pinned ($(bytes_of pipeline_gen.c) bytes; XLANG_FORCE_REGEN_GEN=1 to regen)"
  elif seed_ok "$seed" && { [ ! -s pipeline_gen.c ] || [ "$seed" -nt pipeline_gen.c ]; }; then
    # 7.4.4 v2: a pin newer than the worktree gen refreshes it (mtime trap).
    cp -f "$seed" pipeline_gen.c
    log "pipeline_gen.c: restored from $seed (pin newer)"
  else
    ensure_xlang_c
    if "./$XLANG_C" "${PIPELINE_X_E_DIRS[@]}" -E -E-extern src/pipeline/pipeline.x >pipeline_gen.c 2>/dev/null \
      && [ -s pipeline_gen.c ]; then
      log "pipeline_gen.c: generated via $XLANG_C -E -E-extern"
    elif seed_ok "$seed"; then
      cp -f "$seed" pipeline_gen.c
      log "pipeline_gen.c: fallback seed (xlang-c -E failed)"
    else
      log "pipeline_gen.c: FAIL (xlang-c -E failed and no seed)"
      exit 1
    fi
  fi

  # PLATFORM: SHARED — ABI guard always runs (stale int32_t int_val = P0-4 L4 red)
  if [ -f scripts/check_pipeline_gen_expr_i64_abi.sh ]; then
    chmod +x scripts/check_pipeline_gen_expr_i64_abi.sh 2>/dev/null || true
    ./scripts/check_pipeline_gen_expr_i64_abi.sh
  fi
  log "pipeline_gen.c OK ($(bytes_of pipeline_gen.c) bytes)"
}

ensure_lsp_all() {
  ensure_lsp_diag_gen
  ensure_lsp_io_gen  # wave1036: skips in product flow (Track L retired)
  ensure_lsp_gen
}

case "$MODE" in
  all|"")
    ensure_lsp_all
    ensure_pipeline_gen
    echo "ensure-lsp-pipeline-gen OK (lsp_diag/lsp + pipeline_gen ready; lsp_io=Track L)"
    ;;
  lsp|lsp-all|lsp_all)
    ensure_lsp_all
    echo "ensure-lsp-pipeline-gen OK (lsp_diag_gen.c lsp_gen.c ready; lsp_io=Track L)"
    ;;
  lsp_diag|lsp_diag_gen.c)
    ensure_lsp_diag_gen
    ;;
  lsp_io|lsp_io_gen.c)
    ensure_lsp_io_gen
    ;;
  lsp_gen|lsp_gen.c|lsp_main)
    ensure_lsp_gen
    ;;
  pipeline|pipeline_gen.c)
    ensure_pipeline_gen
    ;;
  -h|--help|help)
    cat <<'EOF'
Usage: ensure_lsp_pipeline_gen.sh [all|lsp|lsp_diag|lsp_io|lsp_gen|pipeline]
  all (default)   — ensure lsp_diag + lsp_io + lsp_gen + pipeline_gen
  lsp | lsp-all   — three product LSP gens only
  lsp_diag        — lsp_diag_gen.c only
  lsp_io          — lsp_io_gen.c only
  lsp_gen         — lsp_gen.c only
  pipeline        — pipeline_gen.c only (+ i64 ABI check)
Env: XLANG_FORCE_REGEN_GEN=1 XLANG_C XLANG_X
EOF
    ;;
  *)
    log "unknown mode: $MODE (use all|lsp|lsp_diag|lsp_io|lsp_gen|pipeline)"
    exit 2
    ;;
esac
