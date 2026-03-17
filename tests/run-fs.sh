#!/usr/bin/env bash
# 测试 std.fs（fs_invalid_handle、fs_open_write/fs_write/fs_read）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/fs/main.su -o /tmp/shu_fs 2>&1
exitcode=0; /tmp/shu_fs >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_invalid_handle == -1), got $exitcode"; exit 1; }

./compiler/shu -L . tests/fs/write_read.su -o /tmp/shu_fs_wr 2>&1
exitcode=0; /tmp/shu_fs_wr >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_open_write/write/read), got $exitcode"; exit 1; }

rm -f tests/fs/.mmap_ro_tmp
./compiler/shu -L . tests/fs/mmap_ro.su -o /tmp/shu_fs_mmap 2>&1
exitcode=0; /tmp/shu_fs_mmap >/dev/null 2>/tmp/shu_fs_mmap_err || exitcode=$?
if [ "$exitcode" -ne 0 ]; then
  echo "expected exit 0 (fs_mmap_ro/fs_munmap), got $exitcode"
  echo "--- mmap_ro stderr (diagnostic) ---"
  cat /tmp/shu_fs_mmap_err 2>/dev/null || true
  rm -f tests/fs/.mmap_ro_tmp /tmp/shu_fs_mmap_err
  exit 1
fi
rm -f tests/fs/.mmap_ro_tmp /tmp/shu_fs_mmap_err

./compiler/shu -L . tests/fs/readv_writev_buf.su -o /tmp/shu_fs_rwbuf 2>&1
exitcode=0; /tmp/shu_fs_rwbuf >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (fs_readv_buf/fs_writev_buf), got $exitcode"; exit 1; }

echo "fs test OK"
