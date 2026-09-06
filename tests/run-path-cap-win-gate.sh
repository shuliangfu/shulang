#!/usr/bin/env bash
# PATH-CAP-WIN gate: Stage 9 (9.1.2) Windows Cap residual.
# Host-cc compile+run tests/sys/path_cap_win_smoke.c against
# xlang_path_cap.h.
# Linux/Darwin N/A (skip=1).
#
# Usage: ./tests/run-path-cap-win-gate.sh
# PLATFORM: WINDOWS gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PATH_CAP_WIN_PREFIX:-xlang: [XLANG_PATH_CAP_WIN]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/path_cap_win_smoke.c"
SMOKE_EXE="/tmp/xlang_path_cap_win_smoke.$$"
HEADER="compiler/include/xlang_path_cap.h"

die() {
  echo "path-cap-win gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PATH-CAP-WIN: Windows Cap path residual (9.1.2) ==="

if ! ci_is_windows_msys; then
  SKIP=1
  echo "path-cap-win: N/A (Windows Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_path_cap_win_cc.err; then
  cat /tmp/xlang_path_cap_win_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

if ! "$SMOKE_EXE"; then
  die "smoke execution non-zero exit"
fi
RUN_OK=1

ok_report
