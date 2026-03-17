#!/usr/bin/env bash
# 全量回归：仅用 C 版编译器（shu-c）跑所有 run-*.sh，验证 C 构建的 shu 行为。
# 在仓库根目录执行：./tests/run-all-c.sh
# 依赖：make -C compiler 已产出 compiler/shu；本脚本会构建 compiler/shu-c 并以其运行 run-all.sh。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
make -C compiler shu-c 2>/dev/null || true
make -C compiler build-tool 2>/dev/null || true
# 构建 bootstrap-driver 并保存为 shu_driver，供 run-all 里 run-without-c 临时使用（run-without-c 需要 -backend asm）
make -C compiler bootstrap-driver 2>/dev/null || true
[ -x compiler/shu ] && cp compiler/shu compiler/shu_driver
cp compiler/shu-c compiler/shu
if [ ! -x compiler/shu-c ]; then
    echo "run-all-c: compiler/shu-c not found (C-only shu); run 'make -C compiler' then 'make -C compiler shu-c'"
    exit 1
fi
echo "run-all-c: running full test suite with SHU=compiler/shu-c (C-only compiler)"
SHU=compiler/shu-c ./tests/run-all.sh
echo "run-all-c: all tests OK (C compiler)"
