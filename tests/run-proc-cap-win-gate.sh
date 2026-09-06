#!/usr/bin/env bash
# PROC-CAP-WIN gate: Stage 9 (9.1.12) Windows Cap residual.
# Host-cc compile+run tests/sys/proc_cap_win_smoke.c against
# xlang_proc_cap.h.
# Darwin/Linux N/A (skip=1).
#
# Usage: ./tests/run-proc-cap-win-gate.sh
# PLATFORM: WINDOWS gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PROC_CAP_WIN_PREFIX:-xlang: [XLANG_PROC_CAP_WIN]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/proc_cap_win_smoke.c"
SMOKE_EXE="/tmp/xlang_proc_cap_win_smoke.$$.exe"
HEADER="compiler/include/xlang_proc_cap.h"

die() {
  echo "proc-cap-win gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PROC-CAP-WIN: Windows Cap proc residual (9.1.12) ==="

if ! ci_is_windows_msys; then
  SKIP=1
  echo "proc-cap-win: N/A (Windows Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-gcc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_proc_cap_win_cc.err; then
  cat /tmp/xlang_proc_cap_win_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

if ! "$SMOKE_EXE"; then
  die "smoke execution non-zero exit"
fi
RUN_OK=$((RUN_OK + 1))
echo "proc-cap-win smoke OK"
ok_report
