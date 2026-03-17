#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_json_$$"
if ! $SHU -L . tests/json/main.su -o "$exe" 2>&1; then echo "json test: compile failed"; rm -f "$exe"; exit 1; fi
$exe 2>/dev/null; exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "json test: expected exit 0, got $exitcode"; exit 1; fi
echo "json test OK"
