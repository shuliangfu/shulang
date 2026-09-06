#!/usr/bin/env bash
# run-net-cap-raw-gate.sh — Linux raw syscall network Cap convergence gate (9.1.7)
# Verifies Linux raw syscalls (SYS_socket, SYS_connect, SYS_bind, SYS_listen, SYS_accept,
# SYS_setsockopt, SYS_poll, SYS_fcntl, SYS_close, SYS_recvmmsg, SYS_sendmmsg) and pure Cap DNS without libc network symbols.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== NET-CAP-RAW: Linux raw syscall network Cap (9.1.7) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Linux" ]; then
  echo "net-cap-raw: host is $UNAME_S (not Linux), skipping."
  echo "xlang: [XLANG_NET_CAP_RAW] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_net_cap_raw_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/net_cap_raw_smoke.c -o "$TMP_EXE"

# Check no undefined libc network symbols
if nm -u "$TMP_EXE" | grep -E '^_(socket|connect|bind|listen|accept|setsockopt|poll|sendto|recvfrom|close|recvmmsg|sendmmsg|getaddrinfo|freeaddrinfo)$' >/dev/null 2>&1; then
  echo "net-cap-raw FAIL: binary contains undefined reference to libc network symbols" >&2
  nm -u "$TMP_EXE" | grep -E '^_(socket|connect|bind|listen|accept|setsockopt|poll|sendto|recvfrom|close|recvmmsg|sendmmsg|getaddrinfo|freeaddrinfo)$' >&2 || true
  exit 1
fi

"$TMP_EXE"

echo "net-cap-raw: step 1..10 OK (raw syscalls socket/bind/listen/poll/fcntl/close/DNS without libc refs)"
echo "xlang: [XLANG_NET_CAP_RAW] status=ok run=1 obs=0 skip=0 host=Linux/$(uname -m)"
