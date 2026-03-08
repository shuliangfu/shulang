#!/usr/bin/env bash
# 测试 core.fmt（fmt_i32）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/fmt/main.su -o /tmp/shuc_fmt 2>&1
exitcode=0; /tmp/shuc_fmt >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected exit 42 (fmt_i32(42)), got $exitcode"; exit 1; }

echo "fmt test OK"
