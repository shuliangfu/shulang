#!/usr/bin/env bash
# 一键运行所有已接入的测试脚本（与 compiler/Makefile 的 test 目标一致，并包含 run-float.sh）。
# 在仓库根目录执行：./tests/run-all.sh

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

run() {
    local script="$1"
    if [ -f "tests/$script" ]; then
        chmod +x "tests/$script"
        ./tests/$script
    fi
}

run run-lexer.sh
run run-typeck.sh
run run-hello.sh
run run-import.sh
run run-std.sh
run run-target.sh
run run-return-value.sh
run run-multi-func.sh
run run-binary-expr.sh
run run-let-const.sh
run run-bool.sh
run run-if-expr.sh
run run-while.sh
run run-return-expr.sh
run run-for.sh
run run-float.sh
run run-parser.sh
run run-struct.sh
run run-slice.sh
run run-array.sh
run run-pointer.sh
run run-enum.sh
run run-match.sh
run run-panic.sh
run run-defer.sh
run run-goto.sh
run run-vector.sh

echo "all tests OK"
