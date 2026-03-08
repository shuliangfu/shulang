#!/usr/bin/env bash
# 测试 core.result 的 Result_i32 API（ok_i32、err_i32、unwrap_or_i32）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/result/main.su -o /tmp/shuc_result 2>&1
exitcode=0; /tmp/shuc_result >/dev/null 2>&1 || exitcode=$?
# ok 取 42，err 取默认 0 → 42+0=42
[ "$exitcode" -ne 42 ] && { echo "expected exit 42, got $exitcode"; exit 1; }

echo "result test OK"
