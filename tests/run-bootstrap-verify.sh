#!/usr/bin/env bash
# 自举验证：构建 shu₁（bootstrap-driver）、再用 shu₁ 编出 shu₂，两代分别跑全量 run-all.sh，均通过则 OK。
# 与 run-all.sh 关系：run-all.sh 为单编译器全量回归；本脚本为「两代 shu 行为一致」的自举验证。
# 在仓库根目录执行：./tests/run-bootstrap-verify.sh
# 等价于：make -C compiler bootstrap-verify（逻辑在 Makefile 的 check-7.2 / bootstrap-self）。

set -e
cd "$(dirname "$0")/.."
make -C compiler bootstrap-verify
