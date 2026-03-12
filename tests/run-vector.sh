#!/usr/bin/env bash
# 向量 i32x4/u32x4：0 初始化、数组字面量、逐分量加法
# 失败时直接 exit 1，便于从根上修编译/运行错误，不再用 SKIP 掩盖。
set -e
cd "$(dirname "$0")/.."

make -C compiler -q 2>/dev/null || make -C compiler
./compiler/shuc tests/vector/i32x4.su -o /tmp/shuc_vec_i32x4 2>&1
exitcode=0; /tmp/shuc_vec_i32x4 >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "run-vector FAIL: i32x4 expected exit 0, got $exitcode"; exit 1; }
./compiler/shuc tests/vector/u32x4_lit.su -o /tmp/shuc_vec_u32 2>&1
exitcode=0; /tmp/shuc_vec_u32 >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "run-vector FAIL: u32x4_lit expected exit 0, got $exitcode"; exit 1; }
./compiler/shuc tests/vector/vec_add.su -o /tmp/shuc_vec_add 2>&1
exitcode=0; /tmp/shuc_vec_add >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "run-vector FAIL: vec_add expected exit 0, got $exitcode"; exit 1; }
./compiler/shuc tests/vector/i32x16.su -o /tmp/shuc_vec_i32x16 2>&1
exitcode=0; /tmp/shuc_vec_i32x16 >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "run-vector FAIL: i32x16 expected exit 0, got $exitcode"; exit 1; }
echo "vector test OK"
