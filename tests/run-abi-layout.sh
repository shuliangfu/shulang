#!/bin/sh
# 运行 ABI/布局断言测试（layout_abi.c），与 analysis/ABI与布局.md、内存契约.md 一致
set -e
cd "$(dirname "$0")"
cc -Wall -Wextra -o /tmp/layout_abi abi/layout_abi.c
/tmp/layout_abi
echo "abi/layout: OK"
