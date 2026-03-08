#!/usr/bin/env bash
# 验证 while 循环：条件为假时不执行体，最终表达式作为返回值。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# while 0 { 1 }; 42 -> 42（循环不执行）
./compiler/shuc tests/while/never.su -o /tmp/shuc_while_never 2>&1
exitcode=0
/tmp/shuc_while_never >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (while never), got $exitcode"; exit 1; }

# while 1 { break }; 42 -> 42（break 跳出循环）
./compiler/shuc tests/while/break_out.su -o /tmp/shuc_while_break 2>&1
exitcode=0
/tmp/shuc_while_break >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (while break), got $exitcode"; exit 1; }

# while 0 { continue }; 42 -> 42（循环不执行，continue 不执行）
./compiler/shuc tests/while/continue_never.su -o /tmp/shuc_while_cont 2>&1
exitcode=0
/tmp/shuc_while_cont >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (continue never), got $exitcode"; exit 1; }

# loop { break }; 42 -> 42（无限循环用 break 退出）
./compiler/shuc tests/while/loop_break.su -o /tmp/shuc_loop_break 2>&1
exitcode=0
/tmp/shuc_loop_break >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 42 ] && { echo "expected 42 (loop break), got $exitcode"; exit 1; }

# break 不在循环体内 -> typeck 报错
if ./compiler/shuc tests/while/break_outside.su -o /tmp/shuc_break_out 2>&1 | grep -q "only allowed inside a loop"; then
  : "break outside loop correctly rejected"
else
  echo "expected typeck error for break outside loop"
  exit 1
fi

echo "while test OK"
