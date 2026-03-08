#!/usr/bin/env bash
# match 表达式：整数字面量分支与 _
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/match/main.su -o /tmp/shuc_match 2>&1
exitcode=0; /tmp/shuc_match >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 2 ] && { echo "expected 2 (match 1 => 2), got $exitcode"; exit 1; }

echo "match test OK"
