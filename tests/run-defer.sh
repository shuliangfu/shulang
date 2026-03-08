#!/usr/bin/env bash
# defer 块：解析与 codegen，块尾表达式为返回值
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/defer/main.su -o /tmp/shuc_defer 2>&1
exitcode=0; /tmp/shuc_defer >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (defer main), got $exitcode"; exit 1; }

echo "defer test OK"
