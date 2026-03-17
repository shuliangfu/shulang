#!/usr/bin/env bash
# 文件职责：阶段 5 import 测试——含 import / const = import / const { } = import 的 .su 能解析、typeck 通过并运行。
# 覆盖：tests/import/main.su（方式 1）、const_binding.su（方式 2）、const_select.su（方式 3）、missing_module.su（边界）。
# 与其它文件的关系：由 run-all.sh 调用；依赖 compiler/shu、tests/import/*.su、core/types.su、std/io（-L .）。

set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler
SHU="${SHU:-./compiler/shu}"

# 方式 1：import path;
out=$($SHU -L . tests/import/main.su 2>&1)
echo "$out" | grep -q "parse OK" || { echo "expected parse OK"; echo "$out"; exit 1; }
echo "$out" | grep -q "typeck OK" || { echo "expected typeck OK"; echo "$out"; exit 1; }
$SHU -L . tests/import/main.su -o /tmp/shu_import_hello 2>&1
/tmp/shu_import_hello | grep -q "Hello World" || { echo "import main: expected Hello World"; exit 1; }

# 方式 2：const xxx = import path;
$SHU -L . tests/import/const_binding.su -o /tmp/shu_import_const_binding 2>&1
/tmp/shu_import_const_binding | grep -q "Hello World" || { echo "const_binding: expected Hello World"; exit 1; }

# 方式 3：const { zzz } = import path;
$SHU -L . tests/import/const_select.su -o /tmp/shu_import_const_select 2>&1
/tmp/shu_import_const_select | grep -q "Hello World" || { echo "const_select: expected Hello World"; exit 1; }

# 边界：import 不存在的模块，应报错且退出非 0
err=$($SHU -L . tests/import/missing_module.su -o /tmp/shu_import_bad 2>&1) || true
echo "$err" | grep -qE "cannot open import|failed to parse import" || { echo "expected import error for missing module, got: $err"; exit 1; }

echo "import test OK"
