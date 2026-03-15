#!/usr/bin/env bash
# 全量回归套件：运行所有 run-*.sh（与 compiler/Makefile 的 test 目标一致）。
# 自举测试不跑：run-su-pipeline、run-su-multi-file、run-asm、run-without-c、run-bootstrap-verify 均不执行。
# 入口：./tests/run-all.sh；C 版编译器由 make -C compiler 产出（不设 SHUC 时用 compiler/shuc）。

set -e
cd "$(dirname "$0")/.."
if [ -n "$SHUC" ]; then
    [ -f compiler/shuc ] && mv compiler/shuc compiler/shuc.bak
    cp "$SHUC" compiler/shuc
    trap '[ -f compiler/shuc.bak ] && mv compiler/shuc.bak compiler/shuc' EXIT
else
    # 无 SHUC 时构建 compiler：显式目标 all，否则 make 默认只构建 Makefile 第一个目标（io.o）。
    make -C compiler -q all 2>/dev/null || make -C compiler all
fi

# 无 shuc 则直接失败，避免整次跑完仍打印 all tests OK
if [ ! -f compiler/shuc ] || [ ! -x compiler/shuc ]; then
    echo "run-all.sh: compiler/shuc not found or not executable (run 'make -C compiler' first)." >&2
    exit 127
fi

# CI 下单个脚本失败时打印 SKIP 并继续，但统计失败数；结束时若有失败则报错并 exit 1，不再误报 all tests OK
RUN_FAILED_COUNT=0
run() {
    local script="$1"
    if [ ! -f "tests/$script" ]; then return 0; fi
    chmod +x "tests/$script"
    if [ -n "${GITHUB_ACTIONS:-}" ] || [ -n "${CI:-}" ]; then
        if ! ./tests/$script; then
            echo "run-all: $script failed in CI (exit $?); SKIP to keep running"
            RUN_FAILED_COUNT=$((RUN_FAILED_COUNT + 1))
        fi
    else
        ./tests/$script
    fi
}

# 在 CI 下也必须通过的脚本（失败则 run-all 失败，不 SKIP）
run_required() {
    local script="$1"
    if [ ! -f "tests/$script" ]; then return 0; fi
    chmod +x "tests/$script"
    ./tests/$script
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
run run-env.sh
run run-sync.sh
run run-encoding.sh
run run-base64.sh
run run-crypto.sh
run run-log.sh
run run-stdtest.sh
run run-set.sh
run run-queue.sh
run run-atomic.sh
run run-channel.sh
run run-backtrace.sh
run run-hash.sh
run run-math.sh
run run-sort.sh
run run-ffi.sh
run run-json.sh
run run-csv.sh
run run-unicode.sh
run run-dynlib.sh
run run-compress.sh
run run-thread.sh
run run-random.sh
run run-http.sh
run run-tar.sh
run run-time.sh
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
# 自举测试不执行：run-su-pipeline / run-su-multi-file / run-asm / run-without-c / run-bootstrap-verify 已全部排除
run run-vector.sh
# core/std 与标准库
run run-fmt.sh
run run-fmt-std.sh
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

if [ -n "${GITHUB_ACTIONS:-}" ] || [ -n "${CI:-}" ]; then
    if [ "$RUN_FAILED_COUNT" -gt 0 ]; then
        echo "run-all: $RUN_FAILED_COUNT test(s) failed (buffer overflow / abort / segfault etc.); not OK" >&2
        exit 1
    fi
fi
echo "all tests OK"
