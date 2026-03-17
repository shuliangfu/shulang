#!/usr/bin/env bash
# 文件职责：验证 let/const 变量与常量；多 let、多 const、混合及常量表达式。
# 依赖：compiler/shu，tests/let-const/*.su

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# let x = 42; x -> 42
./compiler/shu tests/let-const/let_only.su -o /tmp/shu_let_only 2>&1
exitcode=0; /tmp/shu_let_only >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (let_only), got $exitcode"; exit 1; }

# const N = 7; N -> 7
./compiler/shu tests/let-const/const_only.su -o /tmp/shu_const_only 2>&1
exitcode=0; /tmp/shu_const_only >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 7 ] && { echo "expected 7 (const_only), got $exitcode"; exit 1; }

# const N=10; let x=1+2; let y=x+N; y -> 13
./compiler/shu tests/let-const/mixed.su -o /tmp/shu_mixed 2>&1
exitcode=0; /tmp/shu_mixed >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 13 ] && { echo "expected 13 (mixed), got $exitcode"; exit 1; }

# const A=3; const B=A+2; let x=B*2; x -> 10
./compiler/shu tests/let-const/const_expr.su -o /tmp/shu_const_expr 2>&1
exitcode=0; /tmp/shu_const_expr >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 10 ] && { echo "expected 10 (const_expr), got $exitcode"; exit 1; }

# 边界：const 初始化为非常量表达式，应报 const init must be constant expression
err=$(./compiler/shu tests/let-const/const_non_const.su -o /tmp/shu_const_fail 2>&1) || true
echo "$err" | grep -q "const init must be constant expression" || { echo "expected const init error, got: $err"; exit 1; }

echo "let/const test OK"
