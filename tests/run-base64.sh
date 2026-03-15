#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHUC="${SHUC:-./compiler/shuc}"
exe="/tmp/shuc_base64_$$"
if ! $SHUC -L . tests/base64/main.su -o "$exe" 2>&1; then echo "base64 test: compile failed"; rm -f "$exe"; exit 1; fi
exitcode=0; $exe 2>/dev/null || exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "base64 test: expected exit 0, got $exitcode"; exit 1; fi
echo "base64 test OK"
