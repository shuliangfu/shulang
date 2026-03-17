#!/usr/bin/env bash
# std.compress 测试：gzip / Brotli 往返。若 compress.o 未启用 zlib/Brotli，对应分支跳过仍通过。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
# 若存在 zlib，用启用 zlib 的 compress.o 以测试 gzip
if (cd compiler && make compress-o-zlib 2>/dev/null); then
  :
fi
SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_compress_$$"
if ! $SHU -L . tests/compress/main.su -o "$exe" 2>&1; then echo "compress test: compile failed"; rm -f "$exe"; exit 1; fi
$exe 2>/dev/null; exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then echo "compress test: expected exit 0, got $exitcode"; exit 1; fi
echo "compress test OK"
