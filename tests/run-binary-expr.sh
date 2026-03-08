#!/usr/bin/env bash
# 文件职责：验证 main 体二元加减乘除表达式（如 1+2、42-10、6*7、20/4）；编译并运行，检查退出码与表达式结果一致。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shuc、tests/binary-expr/*.su。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# 测试 1+2 -> 退出码 3
./compiler/shuc tests/binary-expr/main.su -o /tmp/shuc_binary_expr 2>&1
exitcode=0
/tmp/shuc_binary_expr >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 3 ]; then
    echo "expected exit code 3 (1+2), got $exitcode"
    exit 1
fi

# 测试 42-10 -> 退出码 32
./compiler/shuc tests/binary-expr/sub.su -o /tmp/shuc_binary_sub 2>&1
exitcode=0
/tmp/shuc_binary_sub >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 32 ]; then
    echo "expected exit code 32 (42-10), got $exitcode"
    exit 1
fi

# 测试 6*7 -> 退出码 42
./compiler/shuc tests/binary-expr/mul.su -o /tmp/shuc_binary_mul 2>&1
exitcode=0
/tmp/shuc_binary_mul >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 42 ]; then
    echo "expected exit code 42 (6*7), got $exitcode"
    exit 1
fi

# 测试 20/4 -> 退出码 5
./compiler/shuc tests/binary-expr/div.su -o /tmp/shuc_binary_div 2>&1
exitcode=0
/tmp/shuc_binary_div >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 5 ]; then
    echo "expected exit code 5 (20/4), got $exitcode"
    exit 1
fi

# 测试优先级：1+2*3 = 7（乘除优先于加减）
./compiler/shuc tests/binary-expr/precedence.su -o /tmp/shuc_binary_prec 2>&1
exitcode=0
/tmp/shuc_binary_prec >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 7 ]; then
    echo "expected exit code 7 (1+2*3), got $exitcode"
    exit 1
fi

# 测试括号：(1+2)*3 = 9
./compiler/shuc tests/binary-expr/paren.su -o /tmp/shuc_binary_paren 2>&1
exitcode=0
/tmp/shuc_binary_paren >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 9 ]; then
    echo "expected exit code 9 ((1+2)*3), got $exitcode"
    exit 1
fi

# 测试一元负号：10 + -4 = 6
./compiler/shuc tests/binary-expr/unary_neg.su -o /tmp/shuc_binary_neg 2>&1
exitcode=0
/tmp/shuc_binary_neg >/dev/null 2>&1 || exitcode=$?
if [ "$exitcode" -ne 6 ]; then
    echo "expected exit code 6 (10+-4), got $exitcode"
    exit 1
fi

# 取模 7%3=1、移位 1<<4=16
./compiler/shuc tests/binary-expr/mod.su -o /tmp/shuc_mod 2>&1
exitcode=0; /tmp/shuc_mod >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 1 ] && { echo "expected 1 (7%%3), got $exitcode"; exit 1; }
./compiler/shuc tests/binary-expr/shift.su -o /tmp/shuc_shift 2>&1
exitcode=0; /tmp/shuc_shift >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 16 ] && { echo "expected 16 (1<<4), got $exitcode"; exit 1; }

# 按位 (12&7)|(4^2)=4|6=6
./compiler/shuc tests/binary-expr/bitwise.su -o /tmp/shuc_bit 2>&1
exitcode=0; /tmp/shuc_bit >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 6 ] && { echo "expected 6 (bitwise), got $exitcode"; exit 1; }

# 比较 (3==3)+(2<5)+(5>2)=1+1+1=3
./compiler/shuc tests/binary-expr/compare.su -o /tmp/shuc_cmp 2>&1
exitcode=0; /tmp/shuc_cmp >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 3 ] && { echo "expected 3 (compare), got $exitcode"; exit 1; }

# 逻辑 (1&&1)+(0||1)=2、!0=1
./compiler/shuc tests/binary-expr/logical.su -o /tmp/shuc_log 2>&1
exitcode=0; /tmp/shuc_log >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 2 ] && { echo "expected 2 (logical), got $exitcode"; exit 1; }
./compiler/shuc tests/binary-expr/lognot.su -o /tmp/shuc_lognot 2>&1
exitcode=0; /tmp/shuc_lognot >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 1 ] && { echo "expected 1 (!0), got $exitcode"; exit 1; }

echo "binary expr test OK"
