#!/usr/bin/env bash
# 切片 []T：从数组初始化、下标访问；core.slice len_i32
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/slice/main.su -o /tmp/shuc_slice 2>&1
exitcode=0; /tmp/shuc_slice >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 20 ] && { echo "expected 20 (slice s[1]), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/slice/length.su -o /tmp/shuc_slice_length 2>&1
exitcode=0; /tmp/shuc_slice_length >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (len_i32), got $exitcode"; exit 1; }

# 边界：对非数组/切片取下标，应报 subscript base must be array or slice
err=$(./compiler/shuc tests/slice/subscript_not_slice.su -o /tmp/shuc_slice_fail 2>&1) || true
echo "$err" | grep -q "subscript base must be array or slice" || { echo "expected subscript base error, got: $err"; exit 1; }

echo "slice test OK"
