#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_unicode_$$"
if ! $SHU -L . tests/unicode/main.su -o "$exe" 2>&1; then echo "unicode test: compile failed"; rm -f "$exe"; exit 1; fi
$exe 2>/dev/null; exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "unicode test: expected exit 0, got $exitcode"; exit 1; fi
echo "unicode test OK"
