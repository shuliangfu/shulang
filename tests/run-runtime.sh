#!/usr/bin/env bash
# 测试 std.runtime（runtime_ready）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/runtime/main.su -o /tmp/shuc_runtime 2>&1
exitcode=0; /tmp/shuc_runtime >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (runtime_ready), got $exitcode"; exit 1; }

echo "runtime test OK"
