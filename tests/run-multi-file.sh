#!/usr/bin/env bash
# 验证多文件与跨模块调用：main.su import foo，main 调用 bar() 解析为 foo.bar，退出码 42。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu tests/multi-file/main.su -o /tmp/shu_multi_file 2>&1
exitcode=0
/tmp/shu_multi_file >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42 (bar() from foo), got $exitcode"
    exit 1
fi
echo "multi-file test OK"
