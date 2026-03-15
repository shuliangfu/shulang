#!/usr/bin/env bash
# 测试 core.result 的 Result_i32 API（ok_i32、err_i32、unwrap_or_i32、expect_i32、expect_i32_or_panic）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/result/main.su -o /tmp/shuc_result 2>&1
exitcode=0; /tmp/shuc_result >/dev/null 2>&1 || exitcode=$?
# 42+0+3+5=50
[ "$exitcode" -ne 50 ] && { echo "expected exit 50, got $exitcode"; exit 1; }

echo "result test OK"
