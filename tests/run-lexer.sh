#!/usr/bin/env bash
# 文件职责：阶段 1 词法测试——对 tests/lexer/main.su 运行 shu，将输出与 tests/lexer/expected.txt 逐行比对。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shu、tests/lexer/main.su、tests/lexer/expected.txt。
# 使用 shu-c（C 版编译器）以保证无 -o 时输出 token 列表 + parse/typeck OK；若当前 shu 为 pipeline 版则无该行为。

set -e
cd "$(dirname "$0")/.."
make -C compiler shu-c 2>/dev/null || true
if [ -f ./compiler/shu-c ]; then
  LEXER_SHU=./compiler/shu-c
else
  make -C compiler
  LEXER_SHU=./compiler/shu
fi
out=$(mktemp)
"$LEXER_SHU" tests/lexer/main.su > "$out"
diff -u --strip-trailing-cr tests/lexer/expected.txt "$out" || exit 1
# 三种注释（//、#、/** */）均应被跳过，代码在第 6 行故行号与 main.su 不同
"$LEXER_SHU" tests/lexer/comments.su > "$out"
diff -u --strip-trailing-cr tests/lexer/expected-comments.txt "$out" || exit 1
rm -f "$out"

# 边界：含非法字符（如 $）应报 parse error 或无法编译（预期错误不刷屏）
./compiler/shu tests/lexer/invalid_char.su -o /tmp/shu_lexer_fail 2>/dev/null && { echo "lexer: expected compile failure for invalid char"; exit 1; }
echo "lexer test OK"
