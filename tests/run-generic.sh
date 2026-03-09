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

# 边界：泛型调用类型实参数量错误，应报 expects N type arguments, got M
err=$(./compiler/shuc tests/generic/wrong_type_args.su -o /tmp/shuc_generic_fail 2>&1) || true
echo "$err" | grep -q "typeck error" && echo "$err" | grep -q "type arguments" || { echo "expected generic type args error, got: $err"; exit 1; }

echo "generic test OK"
