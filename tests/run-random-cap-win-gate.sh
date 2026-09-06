#!/usr/bin/env bash
# run-random-cap-win-gate.sh — Windows random Cap gate (9.1.6)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== RANDOM-CAP-WIN: Windows BCrypt random Cap (9.1.6) ==="

UNAME_S="$(uname -s)"
case "$UNAME_S" in
  MINGW*|MSYS*|CYGWIN*) ;;
  *)
    echo "random-cap-win: host is $UNAME_S (not Windows), skipping."
    echo "xlang: [XLANG_RANDOM_CAP_WIN] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
    exit 0
    ;;
esac

TMP_EXE="/tmp/xlang_random_cap_win_smoke_$$.exe"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/random_cap_win_smoke.c -lbcrypt -o "$TMP_EXE"

"$TMP_EXE"

echo "random-cap-win: step 1..6 OK (Win32 BCrypt random Cap)"
echo "xlang: [XLANG_RANDOM_CAP_WIN] status=ok run=1 obs=0 skip=0 host=$UNAME_S"
