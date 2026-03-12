#!/bin/sh
# build.sh — 以 build.su 为唯一构建入口（等同 Zig 的 build.zig），不依赖根目录 Makefile
#
# 用法：在仓库根目录执行 ./build.sh
# 流程：进入 compiler，若无 build_tool 则用 shuc 编 build.su 得到 build_tool，再执行 ./build_tool ./shuc。
# 前提：compiler 目录下已有 shuc（首次构建请先 make -C compiler，或使用预置的 compiler/bootstrap_shuc）。
#
# 完全无 C/无 Makefile 自举见：analysis/完全自举-无C无Makefile.md；
# asm 后端编 shuc：compiler/scripts/build_shuc_asm.sh（需 bootstrap-driver，链接可选 crt0_x86_64.o）。

set -e
cd "$(dirname "$0")/compiler"

SHUC="./shuc"
if [ -f "./bootstrap_shuc" ] && [ ! -x "./shuc" ]; then
  SHUC="./bootstrap_shuc"
fi

if [ ! -x "$SHUC" ]; then
  echo "build.sh: no shuc or bootstrap_shuc in compiler/; run 'make -C compiler' first, or add compiler/bootstrap_shuc."
  exit 1
fi

if [ ! -x "./build_tool" ]; then
  echo "build.sh: building build_tool from ../build.su ..."
  "$SHUC" ../build.su -o build_tool
fi

echo "build.sh: running ./build_tool $SHUC ..."
./build_tool "$SHUC"
