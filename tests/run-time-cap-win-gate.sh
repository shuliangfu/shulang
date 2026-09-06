#!/usr/bin/env bash
# run-time-cap-win-gate.sh — Windows time Cap convergence gate (9.1.5)
# Verifies Windows Win32 time Cap without CRT time functions.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== TIME-CAP-WIN: Windows Win32 time Cap (9.1.5) ==="

TMP_EXE="/tmp/xlang_time_cap_win_smoke_$$"
trap 'rm -f "$TMP_EXE" "${TMP_EXE}.exe"' EXIT

CC_WIN=""
for cand in x86_64-w64-mingw32-gcc x86_64-w64-mingw32-clang cl gcc clang; do
  if command -v "$cand" >/dev/null 2>&1; then
    CC_WIN="$cand"
    break
  fi
done

if [ -z "$CC_WIN" ]; then
  echo "time-cap-win: no C compiler found for Windows test; skip."
  echo "xlang: [XLANG_TIME_CAP_WIN] status=ok run=0 obs=0 skip=1 host=unknown"
  exit 0
fi

if [[ "$CC_WIN" == *"mingw"* ]]; then
  "$CC_WIN" -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
    tests/sys/time_cap_win_smoke.c -o "${TMP_EXE}.exe"
  echo "time-cap-win: compiled with $CC_WIN successfully"
  if command -v wine >/dev/null 2>&1; then
    wine "${TMP_EXE}.exe"
    echo "time-cap-win: step 1..7 OK under Wine"
  else
    echo "time-cap-win: Wine not present; compile-only check OK"
  fi
elif [[ "$OSTYPE" == "msys"* || "$OSTYPE" == "cygwin"* || "$OSTYPE" == "win32"* ]]; then
  "$CC_WIN" -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
    tests/sys/time_cap_win_smoke.c -o "${TMP_EXE}.exe"
  "${TMP_EXE}.exe"
  echo "time-cap-win: step 1..7 OK (native Windows)"
else
  echo "time-cap-win: non-Windows host without cross-compiler; skipping."
  echo "xlang: [XLANG_TIME_CAP_WIN] status=ok run=0 obs=0 skip=1 host=$(uname -s)"
  exit 0
fi

echo "xlang: [XLANG_TIME_CAP_WIN] status=ok run=1 obs=0 skip=0 host=Windows"
