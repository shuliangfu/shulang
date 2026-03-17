#!/usr/bin/env bash
#
# 【文件职责】std.time 模块的回归测试脚本；编译并运行 tests/time/*.su，校验退出码。
# 【测试目的】覆盖 now_monotonic_*、now_wall_*、sleep_*、duration_ns，确保 API 行为符合预期。
# 【运行方式】在仓库根目录执行 ./tests/run-time.sh；可选环境变量 SHU 指定编译器路径。
#
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

SHU="${SHU:-./compiler/shu}"
run_one() {
  local name="$1"
  local src="$2"
  local exe="/tmp/shu_time_$$_${name}"
  if ! $SHU -L . "$src" -o "$exe" 2>&1; then
    echo "time test $name: compile failed"
    return 1
  fi
  local exitcode=0
  $exe >/dev/null 2>&1 || exitcode=$?
  rm -f "$exe"
  if [ "$exitcode" -ne 0 ]; then
    echo "time test $name: expected exit 0, got $exitcode"
    return 1
  fi
  return 0
}

run_one "main" "tests/time/main.su" || exit 1

echo "time test OK (all)"
rm -f /tmp/shu_time_$$_*
