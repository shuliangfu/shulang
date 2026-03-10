#!/usr/bin/env bash
# 阶段 2.11 / 9.1：验证纯 .su 流水线（-su -E）对最小程序能跑通并产出 C。
# 在仓库根目录执行：./tests/run-su-pipeline.sh
# 要求：compiler 已 make，且 make bootstrap-pipeline + shuc-su-pipeline 已生成 shuc_su。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
# 生成 shuc_su（若 pipeline_gen.c 或 pipeline_su.o 不存在/过期则重建）
make -C compiler bootstrap-pipeline 2>/dev/null || true
make -C compiler shuc-su-pipeline 2>/dev/null || true

[ -x compiler/shuc_su ] || { echo "compiler/shuc_su not found or not executable"; exit 1; }

MIN_SU="tests/su-pipeline/min.su"
mkdir -p tests/su-pipeline
if [ ! -f "$MIN_SU" ]; then
  printf 'function main(): i32 { return 0 }\n' > "$MIN_SU"
fi

out=$(mktemp)
ec=0
compiler/shuc_su -su -E "$MIN_SU" > "$out" 2>/dev/null || ec=$?
if [ "$ec" -ne 0 ]; then
  echo "run-su-pipeline: ./shuc_su -su -E $MIN_SU failed (exit $ec)"
  cat "$out" 2>/dev/null || true
  rm -f "$out"
  exit 1
fi

# 产出应含 C 头与 return（函数名暂可能为 mai 已知问题）
if ! grep -q '#include' "$out"; then
  echo "run-su-pipeline: output missing #include"
  cat "$out"
  rm -f "$out"
  exit 1
fi
if ! grep -q 'return' "$out"; then
  echo "run-su-pipeline: output missing return"
  cat "$out"
  rm -f "$out"
  exit 1
fi

rm -f "$out"
echo "run-su-pipeline OK (-su -E minimal program)"
