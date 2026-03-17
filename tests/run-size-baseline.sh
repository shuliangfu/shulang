#!/usr/bin/env bash
# 阶段 8 体积基线：编译固定用例，输出可执行文件大小（默认 -O2 -s，便于对比）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

echo "=== 体积基线（-O2，产出已 strip）==="
./compiler/shu examples/hello.su -o /tmp/shu_baseline_hello 2>&1
if [ -f /tmp/shu_baseline_hello ]; then
  ls -l /tmp/shu_baseline_hello | awk '{print "hello.su -> " $5 " bytes"}'
fi

./compiler/shu -L . tests/option/main.su -o /tmp/shu_baseline_option 2>&1
if [ -f /tmp/shu_baseline_option ]; then
  ls -l /tmp/shu_baseline_option | awk '{print "option/main.su -> " $5 " bytes"}'
fi

echo "=== -O 0 / -O 2 / -O s 对比（hello.su）==="
./compiler/shu -O 0 examples/hello.su -o /tmp/shu_baseline_hello_o0 2>&1
./compiler/shu -O 2 examples/hello.su -o /tmp/shu_baseline_hello_o2 2>&1
./compiler/shu -O s examples/hello.su -o /tmp/shu_baseline_hello_os 2>&1
[ -f /tmp/shu_baseline_hello_o0 ] && ls -l /tmp/shu_baseline_hello_o0 | awk '{print "hello.su -O 0 -> " $5 " bytes (no strip)"}'
[ -f /tmp/shu_baseline_hello_o2 ] && ls -l /tmp/shu_baseline_hello_o2 | awk '{print "hello.su -O 2 -> " $5 " bytes"}'
[ -f /tmp/shu_baseline_hello_os ] && ls -l /tmp/shu_baseline_hello_os | awk '{print "hello.su -O s -> " $5 " bytes"}'

echo "=== size baseline OK ==="
