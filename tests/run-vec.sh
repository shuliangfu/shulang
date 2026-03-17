#!/usr/bin/env bash
# 测试 std.vec（vec_len_empty、vec_placeholder）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/vec/main.su -o /tmp/shu_vec 2>&1
exitcode=0; /tmp/shu_vec >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (vec_len_empty), got $exitcode"; exit 1; }

echo "vec test OK"
