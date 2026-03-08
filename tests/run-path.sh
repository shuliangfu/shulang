#!/usr/bin/env bash
# 测试 std.path（path_empty_len）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/path/main.su -o /tmp/shuc_path 2>&1
exitcode=0; /tmp/shuc_path >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (path_empty_len), got $exitcode"; exit 1; }

echo "path test OK"
