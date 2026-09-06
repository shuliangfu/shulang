#!/usr/bin/env bash
# PROC-CAP-RAW gate: Stage 9 (9.1.12) Linux Cap residual.
# Host-cc compile+run tests/sys/proc_cap_raw_smoke.c against
# xlang_proc_cap.h.
# Also verifies tests/sys/target_cpu_proc_raw_smoke.x via xlang.
# Darwin/Windows N/A (skip=1).
#
# Usage: ./tests/run-proc-cap-raw-gate.sh
# PLATFORM: LINUX gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PROC_CAP_RAW_PREFIX:-xlang: [XLANG_PROC_CAP_RAW]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/proc_cap_raw_smoke.c"
SMOKE_EXE="/tmp/xlang_proc_cap_raw_smoke.$$"
HEADER="compiler/include/xlang_proc_cap.h"
TARGET_CPU_SMOKE_X="tests/sys/target_cpu_proc_raw_smoke.x"
TARGET_CPU_SMOKE_EXE="/tmp/xlang_target_cpu_proc_raw_smoke.$$"

die() {
  echo "proc-cap-raw gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" "$TARGET_CPU_SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" "$TARGET_CPU_SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PROC-CAP-RAW: Linux Cap proc/cpuinfo residual (9.1.12) ==="

if ! ci_is_linux; then
  SKIP=1
  echo "proc-cap-raw: N/A (Linux Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_proc_cap_raw_cc.err; then
  cat /tmp/xlang_proc_cap_raw_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

# Cap proc must not pull libc fopen/fgets/fprintf/open/close/read.
if command -v nm >/dev/null 2>&1; then
  if nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '^(fopen|fread|fgets|fprintf|fclose|open|close|read)$' >/dev/null 2>&1; then
    nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '^(fopen|fread|fgets|fprintf|fclose|open|close|read)$' >&2 || true
    die "unexpected libc symbols in Linux Cap proc smoke"
  fi
fi

if ! "$SMOKE_EXE"; then
  die "smoke execution non-zero exit"
fi
RUN_OK=$((RUN_OK + 1))

# Step 2: verify target_cpu_proc_raw_smoke.x via xlang compiler
if [ -x "./compiler/xlang" ] && [ -f "$TARGET_CPU_SMOKE_X" ]; then
  rm -f "$TARGET_CPU_SMOKE_EXE"
  if ./compiler/xlang "$TARGET_CPU_SMOKE_X" -o "$TARGET_CPU_SMOKE_EXE" >/dev/null 2>&1; then
    if "$TARGET_CPU_SMOKE_EXE"; then
      RUN_OK=$((RUN_OK + 1))
    else
      die "target_cpu_proc_raw_smoke.x exit non-zero"
    fi
  else
    die "failed to compile target_cpu_proc_raw_smoke.x"
  fi
fi

echo "proc-cap-raw smoke OK (raw syscalls, zero libc fopen/open/read)"
ok_report
