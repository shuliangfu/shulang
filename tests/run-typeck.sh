#!/usr/bin/env bash
# 阶段 3 类型检查测试：正例含 typeck OK；负例（边界）须报 typeck error 且退出码非 0

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# 正例：lexer/main.su 通过
out=$(./compiler/shuc tests/lexer/main.su 2>&1)
echo "$out" | grep -q "typeck OK" || { echo "missing 'typeck OK' in output"; exit 1; }

# 边界负例：类型不匹配、条件非 bool、未定义名、隐式 return、三元条件/分支错误
expect_typeck_error() {
  local file="$1" msg="$2"
  err=$(./compiler/shuc "$file" -o /tmp/shuc_typeck_fail 2>&1) || true
  echo "$err" | grep -q "typeck error" || { echo "expected typeck error in $file (e.g. $msg), got: $err"; exit 1; }
}
expect_typeck_error tests/typeck/type_mismatch_assign.su "assignment type mismatch"
expect_typeck_error tests/typeck/if_condition_not_bool.su "if condition must be bool"
expect_typeck_error tests/typeck/undefined_name.su "undefined name"
expect_typeck_error tests/typeck/return_implicit.su "explicit return statement"
expect_typeck_error tests/typeck/ternary_condition_not_bool.su "ternary condition must be bool"
expect_typeck_error tests/typeck/ternary_branches_mismatch.su "ternary branches must have the same type"

echo "typeck test OK"
