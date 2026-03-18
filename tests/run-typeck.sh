#!/usr/bin/env bash
# 阶段 3 类型检查测试：正例含 typeck OK；负例（边界）须报 typeck error 且退出码非 0
# 当 SHU 已设置（test_su/run-all-su）时仅用 compiler/shu（shu_su），不构建 shu-c，并跳过依赖「typeck OK」输出的正例。

set -e
cd "$(dirname "$0")/.."
expect_typeck_error() {
  local file="$1" msg="$2"
  local shu="${3:-./compiler/shu}"
  err=$("$shu" "$file" -o /tmp/shu_typeck_fail 2>&1) || true
  echo "$err" | grep -q "typeck error" || { echo "expected typeck error in $file (e.g. $msg), got: $err"; exit 1; }
}
if [ -n "$SHU" ]; then
  # test_su 路径：用 compiler/shu（shu_su），不碰 shu-c；仅跑边界负例（-o 时 typeck 报错）
  TYPECK_SHU=./compiler/shu
  expect_typeck_error tests/typeck/type_mismatch_assign.su "assignment type mismatch" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/if_condition_not_bool.su "if condition must be bool" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/undefined_name.su "undefined name" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/return_implicit.su "explicit return statement" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/ternary_condition_not_bool.su "ternary condition must be bool" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/ternary_branches_mismatch.su "ternary branches must have the same type" "$TYPECK_SHU"
else
  make -C compiler -q 2>/dev/null || make -C compiler
  make -C compiler shu-c 2>/dev/null || true
  if [ -f ./compiler/shu-c ]; then
    TYPECK_SHU=./compiler/shu-c
  else
    TYPECK_SHU=./compiler/shu
  fi
  out=$("$TYPECK_SHU" tests/lexer/main.su 2>&1)
  echo "$out" | grep -q "typeck OK" || { echo "missing 'typeck OK' in output"; exit 1; }
  expect_typeck_error tests/typeck/type_mismatch_assign.su "assignment type mismatch" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/if_condition_not_bool.su "if condition must be bool" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/undefined_name.su "undefined name" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/return_implicit.su "explicit return statement" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/ternary_condition_not_bool.su "ternary condition must be bool" "$TYPECK_SHU"
  expect_typeck_error tests/typeck/ternary_branches_mismatch.su "ternary branches must have the same type" "$TYPECK_SHU"
fi
echo "typeck test OK"
