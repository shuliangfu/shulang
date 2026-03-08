#!/usr/bin/env bash
# 测试 std.heap（alloc_size_zero）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/heap/main.su -o /tmp/shuc_heap 2>&1
exitcode=0; /tmp/shuc_heap >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (alloc_size_zero), got $exitcode"; exit 1; }

echo "heap test OK"
