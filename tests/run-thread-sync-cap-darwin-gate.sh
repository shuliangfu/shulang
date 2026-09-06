#!/usr/bin/env bash
# THREAD-SYNC-CAP-DARWIN gate: Stage 10 (10.6.1 / 10.6.3) Darwin Cap residual.
# Host-cc compile+run tests/sys/thread_sync_cap_darwin_smoke.c against
# xlang_thread_cap.h and xlang_sync_cap.h.
# Linux/Windows N/A (skip=1).
#
# Usage: ./tests/run-thread-sync-cap-darwin-gate.sh
# PLATFORM: DARWIN gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_THREAD_SYNC_CAP_DARWIN_PREFIX:-xlang: [XLANG_THREAD_SYNC_CAP_DARWIN]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/thread_sync_cap_darwin_smoke.c"
SMOKE_EXE="/tmp/xlang_thread_sync_cap_darwin_smoke.$$"
THREAD_HEADER="compiler/include/xlang_thread_cap.h"
SYNC_HEADER="compiler/include/xlang_sync_cap.h"

die() {
  echo "thread-sync-cap-darwin gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== THREAD-SYNC-CAP-DARWIN: Darwin Cap thread/sync residual (10.6.1 / 10.6.3) ==="

if ! ci_is_darwin; then
  SKIP=1
  echo "thread-sync-cap-darwin: N/A (Darwin Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$THREAD_HEADER" ] || die "missing $THREAD_HEADER"
[ -f "$SYNC_HEADER" ] || die "missing $SYNC_HEADER"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_thread_sync_cap_darwin_cc.err; then
  cat /tmp/xlang_thread_sync_cap_darwin_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

if ! "$SMOKE_EXE"; then
  die "smoke exit nonzero"
fi
RUN_OK=$((RUN_OK + 1))

ok_report
exit 0
