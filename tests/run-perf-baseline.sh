#!/usr/bin/env bash
# 阶段 8 性能基线：编译 perf-baseline 用例并以 time 多次运行，输出耗时便于对比与防回退
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

PERF_SU="tests/perf-baseline/main.su"
OUT="/tmp/shu_perf_baseline"
RUNS=3

echo "=== 性能基线（-O2，strip）==="
./compiler/shu "$PERF_SU" -o "$OUT" 2>&1
if [ ! -f "$OUT" ]; then
  echo "编译失败，无产物" >&2
  exit 1
fi

echo "运行 $RUNS 次，取 real 时间："
for i in $(seq 1 "$RUNS"); do
  ( time "$OUT" ) 2>&1 | grep -E '^real' || true
done
echo "=== perf baseline OK ==="
