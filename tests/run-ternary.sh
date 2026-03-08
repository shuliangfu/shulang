#!/usr/bin/env bash
# 三元运算符 cond ? then : else
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# return a > 10 ? 10 : a; a=15 -> 10
./compiler/shuc tests/ternary/main.su -o /tmp/shuc_ternary_main 2>&1
exitcode=0; /tmp/shuc_ternary_main >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 10 ] && { echo "expected 10 (main), got $exitcode"; exit 1; }

# clamp -3 -> 0
./compiler/shuc tests/ternary/clamp.su -o /tmp/shuc_ternary_clamp 2>&1
exitcode=0; /tmp/shuc_ternary_clamp >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (clamp), got $exitcode"; exit 1; }

echo "ternary test OK"
