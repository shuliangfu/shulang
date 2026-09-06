#!/usr/bin/env bash
# PROCESS-CAP-RAW gate: Stage 9 (9.1.3) Linux raw syscall process Cap.
# Host-cc compile+run tests/sys/process_cap_raw_smoke.c against xlang_process_cap.h.
# No libc getpid/getppid/getcwd/chdir. Darwin N/A (skip=1).
#
# Usage: ./tests/run-process-cap-raw-gate.sh
# PLATFORM: LINUX|UBUNTU gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_PROCESS_CAP_RAW_PREFIX:-xlang: [XLANG_PROCESS_CAP_RAW]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/process_cap_raw_smoke.c"
SMOKE_EXE="/tmp/xlang_process_cap_raw_smoke.$$"
HEADER="compiler/include/xlang_process_cap.h"

die() {
  echo "process-cap-raw gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== PROCESS-CAP-RAW: Linux raw syscall process Cap (9.1.3) ==="

if ! ci_is_linux; then
  SKIP=1
  echo "process-cap-raw: N/A (Linux Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"
[ -f "compiler/include/xlang_syscall_cap.h" ] || die "missing xlang_syscall_cap.h"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_process_cap_raw_cc.err; then
  cat /tmp/xlang_process_cap_raw_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

# Cap path must not pull libc getpid/getppid/getcwd/chdir/fork/execve/waitpid/pipe/dup2.
if command -v nm >/dev/null 2>&1; then
  if nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '\b(getpid|getppid|getcwd|chdir|fork|execve|execvp|waitpid|wait4|pipe|dup2)@' >/dev/null 2>&1; then
    nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '\b(getpid|getppid|getcwd|chdir|fork|execve|execvp|waitpid|wait4|pipe|dup2)@' >&2 || true
    die "unexpected getpid/getppid/getcwd/chdir/fork/execve/waitpid/pipe/dup2 libc UNDEF in Linux Cap smoke"
  fi
fi

if ! "$SMOKE_EXE"; then
  die "smoke exit nonzero"
fi
RUN_OK=$((RUN_OK + 1))

echo "process-cap-raw: step 1..10 OK (raw syscall getpid/getppid/getcwd/chdir/pipe/dup2/fork/wait4/exit/execvp; no libc refs)"
ok_report
exit 0
