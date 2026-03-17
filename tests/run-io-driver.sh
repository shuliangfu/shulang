#!/usr/bin/env bash
# 测试 std.io.driver 占位：Buffer、Completion、IO_Result、register、submit_read、submit_write
# 需先有 std/io/io.o（bootstrap-driver-seed 会构建）；此处显式构建以便单独跑本脚本时也能链入。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
make -C compiler ../std/io/io.o ../std/fs/fs.o ../std/heap/heap.o 2>/dev/null || true

./compiler/shu -L . tests/io-driver/main.su -o /tmp/shu_io_driver 2>&1
exitcode=0; /tmp/shu_io_driver >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0, got $exitcode"; exit 1; }

echo "io-driver test OK"
