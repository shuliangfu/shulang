#!/usr/bin/env bash
# 测试 std.vec（vec_len_empty、vec_placeholder）
# 输出到仓库内目录，避免 /tmp 不可写（macOS 沙箱或 ld 无法写 /tmp）
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

OUT_DIR="${TESTS_OUT_DIR:-tests/.out}"
mkdir -p "$OUT_DIR"
OUT="$OUT_DIR/shu_vec"

./compiler/shu -L . tests/vec/main.su -o "$OUT" 2>&1
exitcode=0; "$OUT" >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (vec_len_empty), got $exitcode"; exit 1; }

echo "vec test OK"
