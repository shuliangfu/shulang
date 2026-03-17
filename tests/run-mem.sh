#!/usr/bin/env bash
# 测试 core.mem（align_of_i32）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/mem/main.su -o /tmp/shu_mem 2>&1
exitcode=0; /tmp/shu_mem >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (align_of_i32 == 4), got $exitcode"; exit 1; }

echo "mem test OK"
