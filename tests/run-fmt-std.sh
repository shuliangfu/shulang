#!/usr/bin/env bash
#
# 【文件职责】std.fmt 模块的回归测试脚本；编译并运行 tests/fmt-std/main.su，校验退出码。
# 【运行方式】在仓库根目录执行 bash tests/run-fmt-std.sh
#
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

SHUC="${SHUC:-./compiler/shuc}"
exe="/tmp/shuc_fmt_std_$$_main"
if ! $SHUC -L . tests/fmt-std/main.su -o "$exe" 2>&1; then
  echo "fmt-std test: compile failed"
  rm -f "$exe"
  exit 1
fi
exitcode=0; $exe >/dev/null 2>&1 || exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then
  echo "fmt-std test: expected exit 0, got $exitcode"
  exit 1
fi
echo "fmt-std test OK"
