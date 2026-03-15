#!/usr/bin/env bash
# 测试 std.string：string_empty、string_from_slice/eq/len、string_compare/append/find/starts_with/ends_with/copy_to
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/string/main.su -o /tmp/shuc_string 2>&1
exitcode=0; /tmp/shuc_string >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (string_empty), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/string/from_slice_eq.su -o /tmp/shuc_string_fs 2>&1
exitcode=0; /tmp/shuc_string_fs >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (from_slice_eq), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/string/compare_append_find.su -o /tmp/shuc_string_caf 2>&1
exitcode=0; /tmp/shuc_string_caf >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (compare_append_find), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/string/contains_trim_replace.su -o /tmp/shuc_string_ctr 2>&1
exitcode=0; /tmp/shuc_string_ctr >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (contains_trim_replace), got $exitcode"; exit 1; }

./compiler/shuc -L . tests/string/view_zerocopy.su -o /tmp/shuc_string_view 2>&1
exitcode=0; /tmp/shuc_string_view >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (view_zerocopy), got $exitcode"; exit 1; }

echo "string test OK"
