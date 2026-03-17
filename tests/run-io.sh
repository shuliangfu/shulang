#!/usr/bin/env bash
# 测试 std.io：print_i32 输出 42，print_u32 输出 100
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/io/main.su -o /tmp/shu_io 2>&1
out=$(/tmp/shu_io 2>&1)
echo "$out" | grep -q "42" || { echo "expected stdout to contain 42, got: $out"; exit 1; }

./compiler/shu -L . tests/io/print_u32.su -o /tmp/shu_io_u32 2>&1
out=$(/tmp/shu_io_u32 2>&1)
echo "$out" | grep -q "100" || { echo "expected stdout to contain 100 (print_u32), got: $out"; exit 1; }

./compiler/shu -L . tests/io/print_i64.su -o /tmp/shu_io_i64 2>&1
out=$(/tmp/shu_io_i64 2>&1)
echo "$out" | grep -q "123" || { echo "expected stdout to contain 123 (print_i64), got: $out"; exit 1; }

./compiler/shu -L . tests/io/write_stdout.su -o /tmp/shu_io_write 2>&1
out=$(/tmp/shu_io_write 2>&1)
echo "$out" | grep -q "Hi" || { echo "expected stdout to contain Hi (write_stdout), got: $out"; exit 1; }
ec=0; /tmp/shu_io_write >/dev/null 2>&1 || ec=$?
[ "$ec" -ne 0 ] && { echo "expected exit 0 (write_stdout), got $ec"; exit 1; }

./compiler/shu -L . tests/io/write_with_timeout.su -o /tmp/shu_io_wto 2>&1
out=$(/tmp/shu_io_wto 2>&1)
echo "$out" | grep -q "Hi" || { echo "expected stdout to contain Hi (write_with_timeout), got: $out"; exit 1; }
ec=0; /tmp/shu_io_wto >/dev/null 2>&1 || ec=$?
[ "$ec" -ne 0 ] && { echo "expected exit 0 (write_with_timeout), got $ec"; exit 1; }

./compiler/shu -L . tests/io/print_str.su -o /tmp/shu_io_print_str 2>&1
out=$(/tmp/shu_io_print_str 2>&1)
echo "$out" | grep -q "ok" || { echo "expected stdout to contain ok (print_str), got: $out"; exit 1; }

# 零拷贝读 read_stdin_ptr / read_ptr_len（管道喂入 "AB"）
./compiler/shu -L . tests/io/read_ptr.su -o /tmp/shu_io_read_ptr 2>&1
echo -n "AB" | /tmp/shu_io_read_ptr
ec=$?
[ "$ec" -ne 0 ] && { echo "expected exit 0 (read_stdin_ptr), got $ec"; exit 1; }

echo "io test OK"
