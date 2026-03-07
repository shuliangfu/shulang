#!/usr/bin/env bash
# 阶段 4 Hello World：编译 examples/hello.su 并运行，检查输出含 "Hello World"

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
./compiler/shuc examples/hello.su -o /tmp/shuc_hello
out=$(/tmp/shuc_hello)
echo "$out" | grep -q "Hello World" || { echo "expected 'Hello World' in output, got: $out"; exit 1; }
echo "Hello World test OK"
