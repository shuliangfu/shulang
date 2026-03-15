#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHUC="${SHUC:-./compiler/shuc}"
exe="/tmp/shuc_tar_$$"
if ! $SHUC -L . tests/tar/main.su -o "$exe" 2>&1; then echo "tar test: compile failed"; rm -f "$exe"; exit 1; fi
$exe 2>/dev/null; exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "tar test: expected exit 0, got $exitcode"; exit 1; fi
echo "tar test OK"
