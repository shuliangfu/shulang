#!/usr/bin/env bash
# 测试 std.error（error_ok）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/error/main.su -o /tmp/shu_error 2>&1
exitcode=0; /tmp/shu_error >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (error_ok), got $exitcode"; exit 1; }

echo "error test OK"
