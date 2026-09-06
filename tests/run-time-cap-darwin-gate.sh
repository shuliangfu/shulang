#!/usr/bin/env bash
# run-time-cap-darwin-gate.sh — Darwin time Cap convergence gate (9.1.5)
# Verifies Darwin raw syscalls (SYS_gettimeofday, SYS_pselect, cntvct_el0) without libc clock_gettime/nanosleep/gmtime_r.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== TIME-CAP-DARWIN: Darwin raw syscall time Cap (9.1.5) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Darwin" ]; then
  echo "time-cap-darwin: host is $UNAME_S (not Darwin), skipping."
  echo "xlang: [XLANG_TIME_CAP_DARWIN] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_time_cap_darwin_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/time_cap_darwin_smoke.c -o "$TMP_EXE"

# Check no undefined libc clock_gettime/nanosleep/gmtime_r symbols
if nm -u "$TMP_EXE" | grep -E '^_(clock_gettime|nanosleep|gmtime_r)$' >/dev/null 2>&1; then
  echo "time-cap-darwin FAIL: binary contains undefined reference to libc clock_gettime/nanosleep/gmtime_r" >&2
  nm -u "$TMP_EXE" | grep -E '^_(clock_gettime|nanosleep|gmtime_r)$' >&2 || true
  exit 1
fi

"$TMP_EXE"

echo "time-cap-darwin: step 1..7 OK (raw syscalls gettimeofday/pselect/cntvct without libc refs)"
echo "xlang: [XLANG_TIME_CAP_DARWIN] status=ok run=1 obs=0 skip=0 host=Darwin/$(uname -m)"
