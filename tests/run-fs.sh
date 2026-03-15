#!/usr/bin/env bash
# 测试 std.fs（fs_invalid_handle、fs_open_write/fs_write/fs_read）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/fs/main.su -o /tmp/shuc_fs 2>&1
exitcode=0; /tmp/shuc_fs >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_invalid_handle == -1), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/fs/write_read.su -o /tmp/shuc_fs_wr 2>&1
exitcode=0; /tmp/shuc_fs_wr >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_open_write/write/read), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/fs/mmap_ro.su -o /tmp/shuc_fs_mmap 2>&1
exitcode=0; /tmp/shuc_fs_mmap >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_mmap_ro/fs_munmap), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/fs/readv_writev_buf.su -o /tmp/shuc_fs_rwbuf 2>&1
exitcode=0; /tmp/shuc_fs_rwbuf >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_readv_buf/fs_writev_buf), got $exitcode"; exit 1; }

echo "fs test OK"
