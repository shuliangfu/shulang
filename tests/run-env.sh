#!/usr/bin/env bash
#
# 【文件职责】std.env 模块的回归测试脚本；编译并运行 tests/env/main.su，校验退出码。
# 【测试目的】覆盖 getenv、getenv_exists、setenv、unsetenv、temp_dir，确保 API 行为符合预期。
# 【运行方式】在仓库根目录执行 bash tests/run-env.sh 或 ./tests/run-env.sh；可选环境变量 SHU 指定编译器路径。
#
set -e
cd "$(dirname "$0")/.."
# 确保 compiler 与 std/env/env.o 已构建（链接阶段需要 env.o）
make -C compiler -q 2>/dev/null || make -C compiler

SHU="${SHU:-./compiler/shu}"
exe="/tmp/shu_env_$$_main"
if ! $SHU -L . tests/env/main.su -o "$exe" 2>&1; then
  echo "env test: compile failed"
  rm -f "$exe"
  exit 1
fi
exitcode=0; $exe 2>/dev/null || exitcode=$?
rm -f "$exe"
if [ "$exitcode" -ne 0 ]; then
  echo "env test: expected exit 0, got $exitcode"
  exit 1
fi
echo "env test OK (all)"
rm -f /tmp/shu_env_$$_*
