#!/usr/bin/env bash
# 测试 std.io：print_i32 输出 42，print_u32 输出 100
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/io/main.su -o /tmp/shuc_io 2>&1
out=$(/tmp/shuc_io 2>&1)
echo "$out" | grep -q "42" || { echo "expected stdout to contain 42, got: $out"; exit 1; }

./compiler/shuc -L . tests/io/print_u32.su -o /tmp/shuc_io_u32 2>&1
out=$(/tmp/shuc_io_u32 2>&1)
echo "$out" | grep -q "100" || { echo "expected stdout to contain 100 (print_u32), got: $out"; exit 1; }

./compiler/shuc -L . tests/io/print_i64.su -o /tmp/shuc_io_i64 2>&1
out=$(/tmp/shuc_io_i64 2>&1)
echo "$out" | grep -q "123" || { echo "expected stdout to contain 123 (print_i64), got: $out"; exit 1; }

echo "io test OK"
