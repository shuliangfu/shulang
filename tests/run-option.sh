#!/usr/bin/env bash
# 测试 core.option 的 Option_i32 API（none_i32、some_i32、unwrap_or_i32）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/option/main.su -o /tmp/shuc_option 2>&1
exitcode=0; /tmp/shuc_option >/dev/null 2>&1 || exitcode=$?
# none 用默认 10，some(42) 用 42 → 10+42=52
[ "$exitcode" -ne 52 ] && { echo "expected exit 52, got $exitcode"; exit 1; }

echo "option test OK"
