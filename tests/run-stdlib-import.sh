#!/usr/bin/env bash
# 测试自举前标准库扩展（5.5）：多个 core/std 模块可 import 并有最小可用实现。
# 依赖：compiler/shu、tests/stdlib-import/main.su、core/*.su、std/*.su（-L .）。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
out=$(./compiler/shu -L . tests/stdlib-import/main.su 2>&1)
echo "$out" | grep -q "parse OK" || { echo "expected parse OK"; echo "$out"; exit 1; }
echo "$out" | grep -q "typeck OK" || { echo "expected typeck OK"; echo "$out"; exit 1; }
./compiler/shu -L . tests/stdlib-import/main.su -o /tmp/shu_stdlib_import 2>&1
/tmp/shu_stdlib_import
echo "stdlib-import test OK"
