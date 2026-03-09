#!/usr/bin/env bash
# match 表达式：整数字面量分支与 _
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/match/main.su -o /tmp/shuc_match 2>&1
exitcode=0; /tmp/shuc_match >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 2 ] && { echo "expected 2 (match 1 => 2), got $exitcode"; exit 1; }

# 边界：match 分支使用枚举不存在的变体，应报 enum has no variant
err=$(./compiler/shuc tests/match/enum_no_variant.su -o /tmp/shuc_match_fail 2>&1) || true
echo "$err" | grep -q "has no variant" || { echo "expected enum no variant error, got: $err"; exit 1; }

echo "match test OK"
