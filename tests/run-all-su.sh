#!/usr/bin/env bash
# 全量回归：仅用 .su 流水线编译器（shu_su）跑所有 run-*.sh，验证 .su 前端/流水线行为。
# 在仓库根目录执行：./tests/run-all-su.sh
# 依赖：make -C compiler shu-su-pipeline 已产出 compiler/shu_su；本脚本会先尝试构建再以 shu_su 运行 run-all.sh。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
make -C compiler bootstrap-pipeline 2>/dev/null || true
make -C compiler shu-su-pipeline 2>/dev/null || true
# 构建 bootstrap-driver 并保存为 shu_driver，供 run-all 里 run-without-c 临时使用（与 run-all-c 一致）
make -C compiler bootstrap-driver 2>/dev/null || true
[ -x compiler/shu ] && cp compiler/shu compiler/shu_driver
if [ ! -x compiler/shu_su ]; then
    echo "run-all-su: compiler/shu_su not found; run 'make -C compiler bootstrap-pipeline' then 'make -C compiler shu-su-pipeline'"
    exit 1
fi
echo "run-all-su: running full test suite with SHU=compiler/shu_su (.su pipeline compiler)"
SHU=compiler/shu_su ./tests/run-all.sh
echo "run-all-su: all tests OK (shu_su)"
