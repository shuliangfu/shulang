#!/usr/bin/env bash
# 裸指针 *T：类型与 0 初始化
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/pointer/main.su -o /tmp/shuc_ptr 2>&1
exitcode=0; /tmp/shuc_ptr >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (pointer main), got $exitcode"; exit 1; }

echo "pointer test OK"
