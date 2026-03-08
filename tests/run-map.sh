#!/usr/bin/env bash
# 测试 std.map（map_empty_size）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/map/main.su -o /tmp/shuc_map 2>&1
exitcode=0; /tmp/shuc_map >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (map_empty_size), got $exitcode"; exit 1; }

echo "map test OK"
