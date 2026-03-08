#!/usr/bin/env bash
# 测试 std.fs（fs_invalid_handle）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/fs/main.su -o /tmp/shuc_fs 2>&1
exitcode=0; /tmp/shuc_fs >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_invalid_handle == -1), got $exitcode"; exit 1; }

echo "fs test OK"
