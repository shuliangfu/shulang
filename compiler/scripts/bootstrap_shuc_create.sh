#!/bin/sh
# 创建 bootstrap_shuc：将当前 compiler 目录下的 shuc 复制为 bootstrap_shuc，供日后「无 make」构建使用。
#
# 用法：在 compiler 目录下执行 ./scripts/bootstrap_shuc_create.sh
# 前提：已有 shuc（例如刚执行过 make 或 ./build_tool ./shuc）。
# 之后：build.sh 在无 shuc 时会优先使用 bootstrap_shuc；实现「步骤 4」的种子编译器入库（本地等效）。
set -e
cd "$(dirname "$0")/.."
if [ ! -x "./shuc" ]; then
  echo "bootstrap_shuc_create: no ./shuc; run 'make' or './build_tool ./shuc' first."
  exit 1
fi
cp ./shuc ./bootstrap_shuc
chmod +x ./bootstrap_shuc
echo "bootstrap_shuc created (./bootstrap_shuc). Use it with: ./build.sh or SHUC=./bootstrap_shuc ./scripts/build_shuc_asm.sh"
