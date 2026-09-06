#!/usr/bin/env bash
# PATH-CAP-RAW gate: Stage 9 (9.1.2) Linux raw Cap residual.
# Host-cc compile+run tests/sys/path_cap_raw_smoke.c against
# xlang_path_cap.h.
# Darwin/Windows N/A (skip=1).
#
# Usage: ./tests/run-path-cap-raw-gate.sh
# PLATFORM: LINUX gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PATH_CAP_RAW_PREFIX:-xlang: [XLANG_PATH_CAP_RAW]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/path_cap_raw_smoke.c"
SMOKE_EXE="/tmp/xlang_path_cap_raw_smoke.$$"
HEADER="compiler/include/xlang_path_cap.h"

die() {
  echo "path-cap-raw gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PATH-CAP-RAW: Linux raw Cap path residual (9.1.2) ==="

if ! ci_is_linux; then
  SKIP=1
  echo "path-cap-raw: N/A (Linux raw Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_path_cap_raw_cc.err; then
  cat /tmp/xlang_path_cap_raw_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

# Cap path must not pull libc access/stat/fstat/realpath.
if command -v nm >/dev/null 2>&1; then
  if nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '\b(access|stat|fstat|realpath)\b' >/dev/null 2>&1; then
    nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '\b(access|stat|fstat|realpath)\b' >&2 || true
    die "unexpected access/stat/fstat/realpath libc UNDEF in Linux Cap smoke"
  fi
fi

if ! "$SMOKE_EXE"; then
  die "smoke execution non-zero exit"
fi
RUN_OK=1

ok_report
