#!/usr/bin/env bash
# PROCESS-CAP-WIN gate: Stage 9 (9.1.3) Windows Win32 process Cap.
# Host-cc compile+run tests/sys/process_cap_win_smoke.c against xlang_process_cap.h.
# Non-MSYS hosts: skip=1.
#
# Usage: ./tests/run-process-cap-win-gate.sh
# PLATFORM: WINDOWS gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PROCESS_CAP_WIN_PREFIX:-xlang: [XLANG_PROCESS_CAP_WIN]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/process_cap_win_smoke.c"
SMOKE_EXE="/tmp/xlang_process_cap_win_smoke.$$"
HEADER="compiler/include/xlang_process_cap.h"

die() {
  echo "process-cap-win gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PROCESS-CAP-WIN: Windows Win32 process Cap (9.1.3) ==="

if ! ci_is_windows_msys; then
  SKIP=1
  echo "process-cap-win: N/A (Windows Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-gcc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_process_cap_win_cc.err; then
  cat /tmp/xlang_process_cap_win_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

if ! "$SMOKE_EXE"; then
  die "smoke exit nonzero"
fi
RUN_OK=$((RUN_OK + 1))

echo "process-cap-win: step 1..7 OK (Win32 getpid/getppid/getcwd/chdir/pipe)"
ok_report
exit 0
