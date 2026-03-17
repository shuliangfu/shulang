#!/usr/bin/env bash
# 测试 std.path：path_empty_len、path_join、path_basename、path_dirname、path_extension、path_stem、path_is_absolute、path_sep、path_clean
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shu -L . tests/path/main.su -o /tmp/shu_path 2>&1
exitcode=0; /tmp/shu_path >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (path_empty_len), got $exitcode"; exit 1; }

./compiler/shu -L . tests/path/join_basename.su -o /tmp/shu_path_join 2>&1
exitcode=0; /tmp/shu_path_join >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (path_join/basename/dirname), got $exitcode"; exit 1; }

./compiler/shu -L . tests/path/extension_stem_abs_clean.su -o /tmp/shu_path_ext 2>&1
exitcode=0; /tmp/shu_path_ext >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0 (path_extension/stem/is_absolute/sep/clean), got $exitcode"; exit 1; }

echo "path test OK"
