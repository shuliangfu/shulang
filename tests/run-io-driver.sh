#!/usr/bin/env bash
# 测试 std.io.driver 占位：Buffer、Completion、IO_Result、register、submit_read、submit_write
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/io-driver/main.su -o /tmp/shuc_io_driver 2>&1
exitcode=0; /tmp/shuc_io_driver >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0, got $exitcode"; exit 1; }

echo "io-driver test OK"
