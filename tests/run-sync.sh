#!/usr/bin/env bash
#
# 【文件职责】std.sync 模块的回归测试脚本；编译并运行 tests/sync/main.su，校验退出码。
# 【测试目的】覆盖 mutex_new、mutex_lock、mutex_try_lock、mutex_unlock、mutex_free，确保 API 行为符合预期。
# 【运行方式】在仓库根目录执行 bash tests/run-sync.sh 或 ./tests/run-sync.sh；可选环境变量 SHU 指定编译器路径。
#
set -e
cd "$(dirname "$0")/.."
# 确保 compiler 与 std/sync/sync.o 已构建（链接阶段需要 sync.o）
make -C compiler -q 2>/dev/null || make -C compiler

SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_sync_$$_main"
if ! $SHU -L . tests/sync/main.su -o "$exe" 2>&1; then
  echo "sync test: compile failed"
  rm -f "$exe"
  exit 1
fi
exitcode=0; $exe 2>/dev/null || exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then
  echo "sync test: expected exit 0, got $exitcode"
  exit 1
fi
echo "sync test OK (all)"
rm -f /tmp/shu_sync_$$_*
