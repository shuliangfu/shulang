#!/usr/bin/env bash
# 验证显式 return expr；块尾可为 return 42 作为返回值。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/return-expr/explicit.su -o /tmp/shuc_return_explicit 2>&1
exitcode=0
/tmp/shuc_return_explicit >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (explicit return), got $exitcode"; exit 1; }

echo "return-expr test OK"
