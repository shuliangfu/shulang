#!/usr/bin/env bash
# 验证 trait/impl 与方法调用：Double for i32，21.double() 返回 42。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/trait/main.su -o /tmp/shuc_trait 2>&1
exitcode=0
/tmp/shuc_trait >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42 (21.double()), got $exitcode"
    exit 1
fi
echo "trait test OK"
