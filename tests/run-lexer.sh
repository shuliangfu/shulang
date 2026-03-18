#!/usr/bin/env bash
# 文件职责：阶段 1 词法测试——对 tests/lexer/main.su 运行 shu，将输出与 tests/lexer/expected.txt 逐行比对。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shu、tests/lexer/main.su、tests/lexer/expected.txt。
# 使用 shu-c（C 版编译器）以保证无 -o 时输出 token 列表 + parse/typeck OK；若当前 shu 为 pipeline 版则无该行为。
# 当 SHU 已设置（test_su/run-all-su）时仅用 compiler/shu（shu_su），不构建 shu-c，并跳过依赖 token 输出的比对。

set -e
cd "$(dirname "$0")/.."
if [ -n "$SHU" ]; then
  # test_su 路径：用当前 compiler/shu（已为 shu_su），不碰 shu-c；仅跑与 pipeline 兼容的用例
  LEXER_SHU=./compiler/shu
  out=$(mktemp)
  "$LEXER_SHU" tests/lexer/invalid_char.su -o /tmp/shu_lexer_fail 2>/dev/null && { echo "lexer: expected compile failure for invalid char"; exit 1; }
  rm -f "$out"
else
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
  "$LEXER_SHU" tests/lexer/comments.su > "$out"
  diff -u --strip-trailing-cr tests/lexer/expected-comments.txt "$out" || exit 1
  rm -f "$out"
  ./compiler/shu tests/lexer/invalid_char.su -o /tmp/shu_lexer_fail 2>/dev/null && { echo "lexer: expected compile failure for invalid char"; exit 1; }
fi
echo "lexer test OK"
