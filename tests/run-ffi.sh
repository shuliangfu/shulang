#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_ffi_$$"
if ! $SHU -L . tests/ffi/main.su -o "$exe" 2>&1; then echo "ffi test: compile failed"; rm -f "$exe"; exit 1; fi
exitcode=0; $exe 2>/dev/null || exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "ffi test: expected exit 0, got $exitcode"; exit 1; fi
echo "ffi test OK"
