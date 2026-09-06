#!/usr/bin/env bash
# run-random-cap-darwin-gate.sh — Darwin random Cap convergence gate (9.1.6)
# Verifies Darwin raw syscall getentropy without libc getentropy.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== RANDOM-CAP-DARWIN: Darwin raw getentropy Cap (9.1.6) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Darwin" ]; then
  echo "random-cap-darwin: host is $UNAME_S (not Darwin), skipping."
  echo "xlang: [XLANG_RANDOM_CAP_DARWIN] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_random_cap_darwin_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/random_cap_darwin_smoke.c -o "$TMP_EXE"

# Check no undefined libc getentropy symbols
if nm -u "$TMP_EXE" | grep -E "^_?getentropy$" >/dev/null 2>&1; then
  echo "random-cap-darwin FAIL: binary contains undefined reference to libc getentropy" >&2
  exit 1
fi

"$TMP_EXE"

echo "random-cap-darwin: step 1..6 OK (raw syscall getentropy without libc refs)"
echo "xlang: [XLANG_RANDOM_CAP_DARWIN] status=ok run=1 obs=0 skip=0 host=Darwin/$(uname -m)"
