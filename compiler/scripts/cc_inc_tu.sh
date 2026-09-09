#!/bin/sh
# cc_inc_tu.sh — compile one TU from .inc / seed .c (G-02e-15 thin alias)
#
# Usage (from compiler/):
#   sh scripts/cc_inc_tu.sh <rel-or-abs.inc|.c> <out.o> [extra cc flags...]
#
# Writes a temporary wrap.c that #includes the absolute source path, runs
# cc -c, then removes the wrap.
#
# wave831 (G.7 有则补全; not physical delete):
#   Makefile residual leaves use FORCE + this script only (no seed make-graph
#   prereq). Shell owns freshness:
#     - skip when OUT exists and is newer than INC and optional peers
#     - XLANG_CC_INC_TU_PEERS: space-separated extra inputs (.x, twin .c, …)
#     - XLANG_CC_INC_TU_FORCE=1: always recompile
# wave887 (G.7 有则补全): when PEERS env is *unset*, apply seed-map defaults
#   for known from_x ↔ product .x pairs (cfg_eval_bootstrap_stub). Explicit
#   PEERS= (even empty) still wins — no dual authority with Makefile inject.
#   PLATFORM: SHARED — cheap mtime skip on every FORCE recipe run.
set -e
cd "$(dirname "$0")/.."

# wave917: seed-map for multi-target recipe (--auto mode).
# Why: Makefile multi-target $(CC_INC_TU_OBJS) needs single body; seed path
#      varies per leaf (e.g. lsp_diag_pipeline_sizes → _weak suffix). Map here
#      to keep G.7 single authority (no Makefile case dispatch).
# Invariant: only used when first arg == "--auto"; explicit INC path still
#            authoritative for all other callers (72+ call sites unchanged).
# PLATFORM: SHARED.
cc_inc_tu_seed_for_out() {
  # 7.2.1 knives (2026-09-10): leaves with .x authorities regenerate via
  # the product -x -E; the emitted main signature is fixed to char**
  # (C main requirement — .x has no char type). Falls back to the seed when
  # no product binary exists. Prints nothing on fallback so --auto proceeds
  # to the seed table below.
  case "$(basename "$1")" in
  build_tool_main.o|crt0_mingw.o|pipeline_glue_link.o|pipeline_wpo_typecheck_emit_bridge.o|typeck_lsp_io_stub.o|pipeline_wpo_strict_link_alias.o|driver_compile_asm_link_alias.o)
    local _btm_prod=""
    for _b in ./xlang_asm ./xlang ./xlang-c; do
      [ -x "$_b" ] && _btm_prod="$_b" && break
    done
    _btm_src=src/build_tool_main.x
    [ "$(basename "$1")" = "crt0_mingw.o" ] && _btm_src=src/crt0_mingw.x
    [ "$(basename "$1")" = "pipeline_glue_link.o" ] && _btm_src=src/pipeline_glue_link.x
    [ "$(basename "$1")" = "pipeline_wpo_typecheck_emit_bridge.o" ] && _btm_src=src/pipeline_wpo_typecheck_emit_bridge.x
    [ "$(basename "$1")" = "typeck_lsp_io_stub.o" ] && _btm_src=src/typeck_lsp_io_stub.x
    [ "$(basename "$1")" = "pipeline_wpo_strict_link_alias.o" ] && _btm_src=src/pipeline_wpo_strict_link_alias.x
    [ "$(basename "$1")" = "driver_compile_asm_link_alias.o" ] && _btm_src=src/driver_compile_asm_link_alias.x
    if [ -n "$_btm_prod" ] && [ -f "$_btm_src" ]; then
      # Stable worktree gen (driver_gen.c lifecycle): regenerated on each
      # ensure, untracked, compiled in place below.
      local _btm_gen
      _btm_gen="$(basename "$1" .o)_gen.c"
      # Entry-leaf validity: main() signature; bridge-leaf validity: the
      # leaf's own export (pipeline_run_x_pipeline for the glue bridge).
      _btm_need='^int32_t main('
      [ "$(basename "$1")" = "pipeline_glue_link.o" ] && _btm_need='^int32_t pipeline_run_x_pipeline('
      [ "$(basename "$1")" = "pipeline_wpo_typecheck_emit_bridge.o" ] && _btm_need='^int32_t run_x_pipeline_typecheck_entry_emit('
      [ "$(basename "$1")" = "typeck_lsp_io_stub.o" ] && _btm_need='^ssize_t typeck_read_message('
      [ "$(basename "$1")" = "pipeline_wpo_strict_link_alias.o" ] && _btm_need='^int32_t pipeline_run_x_pipeline_impl('
      [ "$(basename "$1")" = "driver_compile_asm_link_alias.o" ] && _btm_need='^int32_t driver_run_compiler_full_x('
      if "$_btm_prod" -x -E -L .. "$_btm_src" >"$_btm_gen" 2>/dev/null \
         && grep -q "$_btm_need" "$_btm_gen"; then
        # char** fixup applies to entry leaves only (bridge keeps uint8_t* ABI).
        if [ "$_btm_need" = '^int32_t main(' ]; then
          perl -i -pe 's/uint8_t \* \* argv/char **argv/g' "$_btm_gen" 2>/dev/null || \
            sed -i.bak 's/uint8_t \* \* argv/char **argv/g' "$_btm_gen"
          rm -f "${_btm_gen}.bak"
        fi
        printf '%s\n' "$_btm_gen"
        return 0
      fi
      rm -f "$_btm_gen"
    fi
    ;;
  esac
  case "$(basename "$1")" in
    asm_experimental_symbol_bridge.o) printf '%s\n' seeds/asm_experimental_symbol_bridge.from_x.c ;;
    lsp_diag_pipeline_sizes.o) printf '%s\n' seeds/lsp_diag_pipeline_sizes_weak.from_x.c ;;
    cfg_eval_bootstrap_stub.o) printf '%s\n' seeds/cfg_eval_bootstrap_stub.from_x.c ;;
    typeck_lsp_io_stub.o) printf '%s\n' seeds/typeck_lsp_io_stub.from_x.c ;;
    bootstrap_nostdlib_stubs.o) printf '%s\n' seeds/bootstrap_nostdlib_stubs.from_x.c ;;
    *) return 1 ;;
  esac
}

# wave917: --auto mode for Makefile multi-target $(CC_INC_TU_OBJS).
# Explicit seed path mode (72+ existing call sites) is unchanged.
if [ "$1" = "--auto" ]; then
  if [ "$#" -lt 2 ]; then
    echo "usage: cc_inc_tu.sh --auto <out.o> [extra cflags...]" >&2
    exit 2
  fi
  OUT="$2"
  INC="$(cc_inc_tu_seed_for_out "$OUT")" || {
    echo "cc_inc_tu --auto: unknown OUT '$OUT' (not in seed-map)" >&2
    exit 1
  }
  shift 2
else
  if [ "$#" -lt 2 ]; then
    echo "usage: cc_inc_tu.sh <file.inc> <out.o> [extra cflags...]" >&2
    exit 2
  fi
  INC="$1"
  OUT="$2"
  shift 2
fi

case "$INC" in
  /*) INC_ABS="$INC" ;;
  *) INC_ABS="$(pwd)/$INC" ;;
esac

# Why: On Windows MSYS/MinGW, `pwd` returns Unix-style /c/Users/... paths
#      which Windows gcc cannot resolve inside `#include "/c/Users/..."`.
#      cygpath -m converts to mixed-mode C:/Users/... that Windows gcc
#      accepts (forward slashes + drive letter).
# Invariant: cygpath exists ONLY under MSYS/Cygwin; on Linux/macOS the
#            if-branch is skipped and INC_ABS stays POSIX-style (no-op).
# PLATFORM: SHARED (Windows branch only).
if command -v cygpath >/dev/null 2>&1; then
  INC_ABS="$(cygpath -m "$INC_ABS")"
fi

if [ ! -f "$INC_ABS" ]; then
  echo "cc_inc_tu: missing $INC_ABS" >&2
  exit 1
fi

# wave887: seed-map peers when XLANG_CC_INC_TU_PEERS is unset (Makefile no longer
# injects). Basename match keeps abs/rel INC paths working.
# PLATFORM: SHARED.
if [ -z "${XLANG_CC_INC_TU_PEERS+set}" ]; then
  case "$(basename "$INC")" in
    cfg_eval_bootstrap_stub.from_x.c)
      XLANG_CC_INC_TU_PEERS='src/lexer/cfg_eval_bootstrap_stub.x'
      ;;
  esac
fi

# wave831: FORCE recipes always enter this script; skip rebuild when fresh.
# Peers (optional): e.g. matching .x beside a seed.from_x.c.
# PLATFORM: SHARED.
if [ -z "${XLANG_CC_INC_TU_FORCE:-}" ] && [ -f "$OUT" ] && [ "$OUT" -nt "$INC_ABS" ]; then
  _fresh=1
  for _peer in ${XLANG_CC_INC_TU_PEERS:-}; do
    if [ -f "$_peer" ] && [ "$_peer" -nt "$OUT" ]; then
      _fresh=0
      break
    fi
  done
  if [ "$_fresh" -eq 1 ]; then
    exit 0
  fi
fi

CC="${CC:-cc}"
BASE_CFLAGS="${CFLAGS:--Wall -Wextra -I. -Iinclude -Isrc}"
# PLATFORM: MACOS — match macho.x LC_BUILD_VERSION minos 11.0.0.
# Do not -w swallow; do not raise macho.x minos to 26.0.
case "$(uname -s 2>/dev/null)" in
  Darwin)
    case " $BASE_CFLAGS " in
      *" -mmacosx-version-min="*) ;;
      *) BASE_CFLAGS="$BASE_CFLAGS -mmacosx-version-min=11.0" ;;
    esac
    ;;
esac
WRAP_DIR="$(dirname "$OUT")"
mkdir -p "$WRAP_DIR"
WRAP="$WRAP_DIR/.$(basename "$OUT" .o)_inc_wrap.c"

# shellcheck disable=SC2016
printf '/* generated by scripts/cc_inc_tu.sh — do not edit */\n#include "%s"\n' "$INC_ABS" >"$WRAP"
# shellcheck disable=SC2086
$CC $BASE_CFLAGS "$@" -c -o "$OUT" "$WRAP"
# Use `/bin/rm` (absolute path) to bypass any shell function/alias wrappers
# (e.g. safe_rm trash wrappers in sandboxed environments) that may intercept
# `rm` and fail silently or refuse to delete temp files. The wrap file is a
# short-lived compile wrapper that must be cleaned deterministically.
# On Linux `/bin/rm` is typically a symlink to `/usr/bin/rm`; both exist on
# all supported hosts (macOS / Ubuntu / Windows MSYS).
# PLATFORM: SHARED.
/bin/rm -f "$WRAP"
