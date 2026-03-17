#!/bin/sh
# 创建 bootstrap_shu：将当前 compiler 目录下的 shu 复制为 bootstrap_shu，供日后「无 make」构建使用。
#
# 用法：在 compiler 目录下执行 ./scripts/bootstrap_shu_create.sh
# 前提：已有 shu（例如刚执行过 make 或 ./build_tool ./shu）。
# 之后：build.sh 在无 shu 时会优先使用 bootstrap_shu；实现「步骤 4」的种子编译器入库（本地等效）。
set -e
cd "$(dirname "$0")/.."
if [ ! -x "./shu" ]; then
  echo "bootstrap_shu_create: no ./shu; run 'make' or './build_tool ./shu' first."
  exit 1
fi
cp ./shu ./bootstrap_shu
chmod +x ./bootstrap_shu
echo "bootstrap_shu created (./bootstrap_shu). Use it with: ./build.sh or SHU=./bootstrap_shu ./scripts/build_shu_asm.sh"
