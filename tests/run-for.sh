#!/usr/bin/env bash
# 验证 C 风格 for(init;cond;step){ body }；cond 空表示恒真。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# for ( ; n < 1 ; ) { break }; 42 -> 42
./compiler/shuc tests/for/simple.su -o /tmp/shuc_for_simple 2>&1
exitcode=0
/tmp/shuc_for_simple >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (for simple), got $exitcode"; exit 1; }

echo "for test OK"
