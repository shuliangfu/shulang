#!/usr/bin/env bash
# panic() / panic(expr)：编译通过，运行会 abort（仅验证编译与链接）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/panic/main.su -o /tmp/shuc_panic 2>&1
./compiler/shuc tests/panic/with_msg.su -o /tmp/shuc_panic_msg 2>&1
# 运行预期非 0 退出（abort）；子 shell 重定向避免 shell 打印 Abort trap
exitcode=0; ( /tmp/shuc_panic ) 2>/dev/null || exitcode=$?
[ "$exitcode" -eq 0 ] && { echo "expected non-zero exit (panic abort)"; exit 1; }
exitcode=0; ( /tmp/shuc_panic_msg ) 2>/dev/null || exitcode=$?
[ "$exitcode" -eq 0 ] && { echo "expected non-zero exit (panic(42) abort)"; exit 1; }

echo "panic test OK"
