#!/usr/bin/env bash
# 测试 std.string（string_empty）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/string/main.su -o /tmp/shuc_string 2>&1
exitcode=0; /tmp/shuc_string >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (string_empty), got $exitcode"; exit 1; }

echo "string test OK"
