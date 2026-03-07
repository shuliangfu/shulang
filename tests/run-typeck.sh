#!/usr/bin/env bash
# 阶段 3 类型检查测试：运行 shuc 并确认输出含 typeck OK、退出码 0

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
out=$(./compiler/shuc tests/lexer/main.su 2>&1)
echo "$out" | grep -q "typeck OK" || { echo "missing 'typeck OK' in output"; exit 1; }
echo "typeck test OK"
