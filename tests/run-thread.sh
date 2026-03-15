#!/usr/bin/env bash
# 测试 std.thread：thread_self、thread_create、thread_join
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/thread/main.su -o /tmp/shuc_thread 2>&1
exitcode=0; /tmp/shuc_thread >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0, got $exitcode"; exit 1; }

echo "thread test OK"
