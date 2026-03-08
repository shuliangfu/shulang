#!/usr/bin/env bash
# 验证泛型单态化：id<T>(x: T) -> T 与 id<i32>(42) 调用；编译并运行，退出码应为 42。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/generic/main.su -o /tmp/shuc_generic 2>&1
exitcode=0
/tmp/shuc_generic >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42 (id<i32>(42)), got $exitcode"
    exit 1
fi
echo "generic test OK"
