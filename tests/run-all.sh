#!/usr/bin/env bash
# 全量回归套件：一键运行所有 run-*.sh（与 compiler/Makefile 的 test 目标一致）；不包含自举验证。
# 在仓库根目录执行：./tests/run-all.sh
# 可选：SHUC=/path/to/shuc 时使用该二进制代替 compiler/shuc（用于 7.2 两代 shuc 对比）。
# 自举验证（两代 shuc 全量测试一致）：./tests/run-bootstrap-verify.sh 或 make -C compiler bootstrap-verify。

set -e
cd "$(dirname "$0")/.."
if [ -n "$SHUC" ]; then
    [ -f compiler/shuc ] && mv compiler/shuc compiler/shuc.bak
    cp "$SHUC" compiler/shuc
    trap '[ -f compiler/shuc.bak ] && mv compiler/shuc.bak compiler/shuc' EXIT
else
    make -C compiler -q 2>/dev/null || make -C compiler
fi

run() {
    local script="$1"
    if [ -f "tests/$script" ]; then
        chmod +x "tests/$script"
        ./tests/$script
    fi
}

# 词法 / 类型检查 / 最小可运行
run run-lexer.sh
run run-typeck.sh
run run-hello.sh
run run-import.sh
run run-std.sh
run run-stdlib-import.sh
run run-target.sh
run run-return-value.sh
run run-multi-func.sh
# 泛型 / trait / 多文件
run run-generic.sh
run run-trait.sh
run run-multi-file.sh
run run-multi-file-generic.sh
# 表达式与控制流
run run-binary-expr.sh
run run-let-const.sh
run run-bool.sh
run run-if-expr.sh
run run-ternary.sh
run run-option.sh
run run-result.sh
run run-process.sh
run run-io.sh
run run-while.sh
run run-return-expr.sh
run run-for.sh
run run-float.sh
# 语法 / 结构体 / 类型
run run-parser.sh
run run-struct.sh
run run-slice.sh
run run-array.sh
run run-pointer.sh
run run-enum.sh
run run-match.sh
run run-panic.sh
run run-defer.sh
run run-goto.sh
run run-preprocess.sh
run run-su-pipeline.sh
run run-su-multi-file.sh
run run-asm.sh
run run-without-c.sh
run run-vector.sh
# core/std 与标准库
run run-fmt.sh
run run-debug.sh
run run-core-types.sh
run run-builtin.sh
run run-mem.sh
run run-string.sh
run run-vec.sh
run run-heap.sh
run run-runtime.sh
run run-fs.sh
run run-path.sh
run run-map.sh
run run-error.sh
# 自举相关：net / io.driver / UB / ABI
run run-net.sh
run run-io-driver.sh
run run-ub.sh
run run-abi-layout.sh

echo "all tests OK"
