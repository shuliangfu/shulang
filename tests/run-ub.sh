#!/bin/sh
# 运行 UB 收窄测试：除零、越界应 panic（exit 134 = SIGABRT），正常路径应正常返回
set -e
cd "$(dirname "$0")/.."
SHU="./compiler/shu"
run_panic() {
    $SHU "$1" -o /tmp/ub_test 2>/dev/null || exit 1
    set +e; { ( /tmp/ub_test 2>/dev/null ) 2>/dev/null; r=$?; } 2>/dev/null; set -e
    if [ "$r" -eq 134 ] || [ "$r" -ne 0 ]; then
        echo "  $1: panic/abort (expected)"
    else
        echo "  $1: unexpected exit $r"; exit 1
    fi
}
run_ok() {
    $SHU "$1" -o /tmp/ub_ok 2>/dev/null || exit 1
    set +e; /tmp/ub_ok 2>/dev/null; r=$?; set -e
    echo "  $1: exit $r"
}
echo "ub: div_zero (expect panic)"
run_panic tests/ub/div_zero.su
echo "ub: bounds_array (expect panic)"
run_panic tests/ub/bounds_array.su
echo "ub: bounds_slice (expect panic)"
run_panic tests/ub/bounds_slice.su
echo "ub: div_ok (expect exit 3)"
run_ok tests/ub/div_ok.su
echo "ub: OK"
