#!/usr/bin/env bash
# 文件职责：验证 codegen 使用 main 体字面量作为程序退出码；编译 fn main() -> i32 { 42 } 并检查退出码为 42。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shu、tests/return-value/main.su。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
./compiler/shu tests/return-value/main.su -o /tmp/shu_return_value 2>&1
# 运行生成的可执行文件并捕获退出码（set -e 下非零会退出，故用 || 保存到变量）
exitcode=0
/tmp/shu_return_value >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42, got $exitcode"
    exit 1
fi
echo "return value test OK"
