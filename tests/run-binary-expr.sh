#!/usr/bin/env bash
# 文件职责：验证 main 体二元加减表达式（如 1+2、42-10）；编译并运行，检查退出码与表达式结果一致。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shuc、tests/binary-expr/*.su。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# 测试 1+2 -> 退出码 3
./compiler/shuc tests/binary-expr/main.su -o /tmp/shuc_binary_expr 2>&1
exitcode=0
/tmp/shuc_binary_expr >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 3 ]; then
    echo "expected exit code 3 (1+2), got $exitcode"
    exit 1
fi

# 测试 42-10 -> 退出码 32
./compiler/shuc tests/binary-expr/sub.su -o /tmp/shuc_binary_sub 2>&1
exitcode=0
/tmp/shuc_binary_sub >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 32 ]; then
    echo "expected exit code 32 (42-10), got $exitcode"
    exit 1
fi

echo "binary expr test OK"
