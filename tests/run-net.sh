#!/usr/bin/env bash
# 测试 std.net 占位：Ipv4Addr、TcpStream、TcpListener、connect、listen、accept
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

./compiler/shuc -L . tests/net/main.su -o /tmp/shuc_net 2>&1
exitcode=0; /tmp/shuc_net >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 0 ] && { echo "expected exit 0, got $exitcode"; exit 1; }

echo "net test OK"
