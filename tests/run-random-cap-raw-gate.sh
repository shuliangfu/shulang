#!/usr/bin/env bash
# run-random-cap-raw-gate.sh — Linux raw syscall random Cap gate (9.1.6)
# Verifies Linux raw syscall getrandom without libc getrandom / errno.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== RANDOM-CAP-RAW: Linux raw getrandom Cap (9.1.6) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Linux" ]; then
  echo "random-cap-raw: host is $UNAME_S (not Linux), skipping."
  echo "xlang: [XLANG_RANDOM_CAP_RAW] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_random_cap_raw_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/random_cap_raw_smoke.c -o "$TMP_EXE"

# Check no undefined libc getrandom symbols
if nm -u "$TMP_EXE" | grep -E "^_?getrandom(@.*)?$" >/dev/null 2>&1; then
  echo "random-cap-raw FAIL: binary contains undefined reference to libc getrandom" >&2
  exit 1
fi

"$TMP_EXE"

echo "random-cap-raw: step 1..6 OK (raw syscall getrandom without libc refs)"
echo "xlang: [XLANG_RANDOM_CAP_RAW] status=ok run=1 obs=0 skip=0 host=Linux/$(uname -m)"
