#!/usr/bin/env bash
# run-time-cap-raw-gate.sh — Linux raw syscall time Cap convergence gate (9.1.5)
# Verifies Linux raw syscalls (clock_gettime, nanosleep, civil gmtime_r) without libc.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== TIME-CAP-RAW: Linux raw syscall time Cap (9.1.5) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Linux" ]; then
  echo "time-cap-raw: host is $UNAME_S (not Linux), skipping."
  echo "xlang: [XLANG_TIME_CAP_RAW] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_time_cap_raw_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/time_cap_raw_smoke.c -o "$TMP_EXE"

# Check no undefined libc clock_gettime/nanosleep/gmtime_r symbols
if command -v nm >/dev/null 2>&1; then
  if nm -u "$TMP_EXE" 2>/dev/null | grep -E '^ *(U *)?(clock_gettime|nanosleep|gmtime_r)(@.*)?$' >/dev/null 2>&1; then
    echo "time-cap-raw FAIL: binary contains undefined reference to libc clock_gettime/nanosleep/gmtime_r" >&2
    nm -u "$TMP_EXE" 2>/dev/null | grep -E '(clock_gettime|nanosleep|gmtime_r)' >&2 || true
    exit 1
  fi
fi

"$TMP_EXE"

echo "time-cap-raw: step 1..7 OK (raw syscalls clock_gettime/nanosleep without libc refs)"
echo "xlang: [XLANG_TIME_CAP_RAW] status=ok run=1 obs=0 skip=0 host=Linux/$(uname -m)"
