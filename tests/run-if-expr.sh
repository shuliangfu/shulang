#!/usr/bin/env bash
# 验证 if/else 条件表达式；then/else 分支为单表达式，else 可省略（生成 0）。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# if 1<2 { 10 } else { 20 } -> 10
./compiler/shu tests/if-expr/simple.su -o /tmp/shu_if_simple 2>&1
exitcode=0; /tmp/shu_if_simple >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 10 ] && { echo "expected 10 (simple), got $exitcode"; exit 1; }

# let x = if 0 { 1 } else { 2 }; x -> 2
./compiler/shu tests/if-expr/with_else.su -o /tmp/shu_if_else 2>&1
exitcode=0; /tmp/shu_if_else >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 2 ] && { echo "expected 2 (with_else), got $exitcode"; exit 1; }

# if 1 { 42 } (无 else) -> 42
./compiler/shu tests/if-expr/no_else.su -o /tmp/shu_if_no_else 2>&1
exitcode=0; /tmp/shu_if_no_else >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (no_else), got $exitcode"; exit 1; }

# else if 链：if 0 { 1 } else if 0 { 2 } else { 3 } -> 3
./compiler/shu tests/if-expr/else_if.su -o /tmp/shu_if_else_if 2>&1
exitcode=0; /tmp/shu_if_else_if >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 3 ] && { echo "expected 3 (else_if), got $exitcode"; exit 1; }

echo "if-expr test OK"
