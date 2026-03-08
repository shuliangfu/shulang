#!/usr/bin/env bash
# 固定长数组 [N]T：初值 0、字面量初始化、下标
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/array/main.su -o /tmp/shuc_array_main 2>&1
exitcode=0; /tmp/shuc_array_main >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (array main), got $exitcode"; exit 1; }

./compiler/shuc tests/array/literal.su -o /tmp/shuc_array_lit 2>&1
exitcode=0; /tmp/shuc_array_lit >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 1 ] && { echo "expected 1 (array literal a[0]), got $exitcode"; exit 1; }

echo "array test OK"
