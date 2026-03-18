#!/usr/bin/env bash
# 测试 std.io.driver 占位：Buffer、Completion、IO_Result、register、submit_read、submit_write
# 执行前自动构建 compiler/shu 及全部 std/**.o（Makefile all = TARGET + STD_AND_PANIC_O），make clean 后单独跑本脚本也可链入。
set -e
cd "$(dirname "$0")/.."
make -C compiler all

./compiler/shu -L . tests/io-driver/main.su -o /tmp/shu_io_driver 2>&1
exitcode=0; /tmp/shu_io_driver >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0, got $exitcode"; exit 1; }

echo "io-driver test OK"
