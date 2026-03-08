#!/usr/bin/env bash
# 验证跨模块泛型调用：main 调用 import 的 id<i32>(42)，退出码 42。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/multi-file-generic/main.su -o /tmp/shuc_multi_file_gen 2>&1
exitcode=0
/tmp/shuc_multi_file_gen >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42 (id<i32>(42) from foo), got $exitcode"
    exit 1
fi
echo "multi-file generic test OK"
