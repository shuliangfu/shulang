#!/usr/bin/env bash
# 文件职责：阶段 1 词法测试——对 tests/lexer/main.su 运行 shuc，将输出与 tests/lexer/expected.txt 逐行比对。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shuc、tests/lexer/main.su、tests/lexer/expected.txt。

set -e
cd "$(dirname "$0")/.."
make -C compiler
out=$(mktemp)
./compiler/shuc tests/lexer/main.su > "$out"
diff -u tests/lexer/expected.txt "$out" && echo "lexer test OK"
rm -f "$out"
