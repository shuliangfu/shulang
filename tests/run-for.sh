#!/usr/bin/env bash
# 验证 C 风格 for(init;cond;step){ body }；cond 空表示恒真。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# for ( ; n < 1 ; ) { break }; 42 -> 42
./compiler/shu tests/for/simple.su -o /tmp/shu_for_simple 2>&1
exitcode=0
/tmp/shu_for_simple >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (for simple), got $exitcode"; exit 1; }

# 边界：continue 不在循环内，应报 only allowed inside a loop
err=$(./compiler/shu tests/for/continue_outside.su -o /tmp/shu_for_fail 2>&1) || true
echo "$err" | grep -q "only allowed inside a loop" || { echo "expected continue outside loop error, got: $err"; exit 1; }

echo "for test OK"
