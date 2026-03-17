#!/usr/bin/env bash
# 文件职责：验证 f32/f64 类型与浮点字面量；含边界与负向测试。
# 依赖：compiler/shu，tests/float/*.su

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# 正例：基础 f32/f64、0.0、整字面量 0
./compiler/shu tests/float/f32_f64.su -o /tmp/shu_float 2>&1
exitcode=0; /tmp/shu_float >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (f32_f64), got $exitcode"; exit 1; }

# 正例：科学计数法、.5
./compiler/shu tests/float/scientific_and_dot.su -o /tmp/shu_float2 2>&1
exitcode=0; /tmp/shu_float2 >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (scientific_and_dot), got $exitcode"; exit 1; }

# 正例：边界 0.0、const 1e2、.25
./compiler/shu tests/float/boundary.su -o /tmp/shu_float_boundary 2>&1
exitcode=0; /tmp/shu_float_boundary >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected 0 (boundary), got $exitcode"; exit 1; }

# 负例：f32 初值为非 0 整数应报 typeck 错误
if ./compiler/shu tests/float/init_non_zero_int.su -o /tmp/shu_float_fail 2>&1 | grep -q "f32/f64 init must be float literal or integer 0"; then
  : # 预期报错，通过
else
  echo "expected typeck error for f32 = 1 (non-zero int)"
  exit 1
fi

echo "float test OK"
