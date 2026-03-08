#!/usr/bin/env bash
# 测试 std.process.exit(code)：程序以指定退出码终止
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/process/main.su -o /tmp/shuc_process 2>&1
exitcode=0; /tmp/shuc_process >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 99 ] && { echo "expected exit 99, got $exitcode"; exit 1; }

echo "process test OK"
