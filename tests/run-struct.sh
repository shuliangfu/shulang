#!/usr/bin/env bash
# 结构体：定义、字面量、字段访问、allow(padding)；负例：未 allow 的隐式 padding 报错
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc tests/struct/simple.su -o /tmp/shuc_struct_simple 2>&1
exitcode=0; /tmp/shuc_struct_simple >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 1 ] && { echo "expected 1 (struct simple p.x), got $exitcode"; exit 1; }

./compiler/shuc tests/struct/padding_allow.su -o /tmp/shuc_struct_pad 2>&1
exitcode=0; /tmp/shuc_struct_pad >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 2 ] && { echo "expected 2 (padding_allow x.b), got $exitcode"; exit 1; }

if ./compiler/shuc tests/struct/padding_no_allow.su -o /tmp/shuc_struct_fail 2>&1 | grep -q "implicit padding"; then
  : # 预期 typeck 报错
else
  echo "expected typeck error for struct without allow(padding)"
  exit 1
fi

echo "struct test OK"
