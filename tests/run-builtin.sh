#!/usr/bin/env bash
# 测试 core.builtin（placeholder）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/builtin/main.su -o /tmp/shuc_builtin 2>&1
exitcode=0; /tmp/shuc_builtin >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (core.builtin placeholder), got $exitcode"; exit 1; }

echo "builtin test OK"
