#!/usr/bin/env bash
# 文件职责：阶段 5 import 测试——含 import core.types 的 .su 能解析、typeck 通过，并能 -o 产出可执行文件且运行输出含 "Hello World"。
# 与其它文件的关系：由 compiler/Makefile 的 test 目标调用；依赖 compiler/shuc、tests/import/main.su、core/types.su（-L .）。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
# 库根为仓库根，以便找到 core/types.su
out=$(./compiler/shuc -L . tests/import/main.su 2>&1)
echo "$out" | grep -q "parse OK" || { echo "expected parse OK"; echo "$out"; exit 1; }
echo "$out" | grep -q "typeck OK" || { echo "expected typeck OK"; echo "$out"; exit 1; }
# 能产出可执行文件
./compiler/shuc -L . tests/import/main.su -o /tmp/shuc_import_hello 2>&1
/tmp/shuc_import_hello | grep -q "Hello World" || { echo "expected Hello World"; exit 1; }

# 边界：import 不存在的模块，应报错且退出非 0
err=$(./compiler/shuc -L . tests/import/missing_module.su -o /tmp/shuc_import_bad 2>&1) || true
echo "$err" | grep -qE "cannot open import|failed to parse import" || { echo "expected import error for missing module, got: $err"; exit 1; }

echo "import test OK"
