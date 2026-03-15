#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHUC="${SHUC:-./compiler/shuc}"
exe="/tmp/shuc_csv_$$"
if ! $SHUC -L . tests/csv/main.su -o "$exe" 2>&1; then echo "csv test: compile failed"; rm -f "$exe"; exit 1; fi
$exe 2>/dev/null; exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "csv test: expected exit 0, got $exitcode"; exit 1; fi
echo "csv test OK"
