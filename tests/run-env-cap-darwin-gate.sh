#!/usr/bin/env bash
# ENV-CAP-DARWIN gate: Stage 9 (9.1.1) Darwin Cap residual.
# Host-cc compile+run tests/sys/env_cap_darwin_smoke.c against
# xlang_environ_cap.h.
# Linux/Windows N/A (skip=1).
#
# Usage: ./tests/run-env-cap-darwin-gate.sh
# PLATFORM: DARWIN gold; SHARED harness skip elsewhere.
set -e
cd "$(dirname "$0")/.."
# shellcheck source=tests/lib/ci-host.sh
. tests/lib/ci-host.sh

PREFIX="${XLANG_ENV_CAP_DARWIN_PREFIX:-xlang: [XLANG_ENV_CAP_DARWIN]}"
RUN_OK=0
OBS=0
SKIP=0
SMOKE_SRC="tests/sys/env_cap_darwin_smoke.c"
SMOKE_EXE="/tmp/xlang_env_cap_darwin_smoke.$$"
HEADER="compiler/include/xlang_environ_cap.h"

die() {
  echo "env-cap-darwin gate FAIL: $*" >&2
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=fail run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
  exit 1
}

ok_report() {
  rm -f "$SMOKE_EXE" 2>/dev/null || true
  echo "${PREFIX} status=ok run=${RUN_OK} obs=${OBS} skip=${SKIP} host=$(ci_host_summary)"
}

echo "=== ENV-CAP-DARWIN: Darwin Cap env residual (9.1.1) ==="

if ! ci_is_darwin; then
  SKIP=1
  echo "env-cap-darwin: N/A (Darwin Cap only)"
  ok_report
  exit 0
fi

[ -f "$SMOKE_SRC" ] || die "missing $SMOKE_SRC"
[ -f "$HEADER" ] || die "missing $HEADER"

CC_BIN="${CC:-cc}"
rm -f "$SMOKE_EXE"
if ! "$CC_BIN" -O0 -Wall -Wextra -Icompiler/include -o "$SMOKE_EXE" "$SMOKE_SRC" 2>/tmp/xlang_env_cap_darwin_cc.err; then
  cat /tmp/xlang_env_cap_darwin_cc.err >&2 || true
  die "host-cc compile failed"
fi
[ -x "$SMOKE_EXE" ] || die "missing exe $SMOKE_EXE"

# Cap path must not pull libc getenv/setenv/unsetenv.
if command -v nm >/dev/null 2>&1; then
  if nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '^_(getenv|setenv|unsetenv)$' >/dev/null 2>&1; then
    nm -u "$SMOKE_EXE" 2>/dev/null | grep -E '^_(getenv|setenv|unsetenv)$' >&2 || true
    die "unexpected getenv/setenv/unsetenv libc UNDEF in Darwin Cap smoke"
  fi
fi

if ! "$SMOKE_EXE"; then
  die "smoke run failed"
fi

RUN_OK=1
echo "env-cap-darwin: smoke OK (no libc getenv/setenv/unsetenv, direct (*_NSGetEnviron()) walk/mutate)"
ok_report
