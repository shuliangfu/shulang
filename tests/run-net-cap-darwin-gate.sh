#!/usr/bin/env bash
# run-net-cap-darwin-gate.sh — Darwin network Cap convergence gate (9.1.7)
# Verifies Darwin raw syscalls (SYS_socket, SYS_connect, SYS_bind, SYS_listen, SYS_accept,
# SYS_setsockopt, SYS_poll, SYS_fcntl, SYS_close) and pure Cap DNS without libc network symbols.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== NET-CAP-DARWIN: Darwin raw syscall network Cap (9.1.7) ==="

UNAME_S="$(uname -s)"
if [ "$UNAME_S" != "Darwin" ]; then
  echo "net-cap-darwin: host is $UNAME_S (not Darwin), skipping."
  echo "xlang: [XLANG_NET_CAP_DARWIN] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
  exit 0
fi

TMP_EXE="/tmp/xlang_net_cap_darwin_smoke_$$"
trap 'rm -f "$TMP_EXE"' EXIT

cc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/net_cap_darwin_smoke.c -o "$TMP_EXE"

# Check no undefined libc network symbols
if nm -u "$TMP_EXE" | grep -E '^_(socket|connect|bind|listen|accept|setsockopt|poll|sendto|recvfrom|close|getaddrinfo|freeaddrinfo)$' >/dev/null 2>&1; then
  echo "net-cap-darwin FAIL: binary contains undefined reference to libc network symbols" >&2
  nm -u "$TMP_EXE" | grep -E '^_(socket|connect|bind|listen|accept|setsockopt|poll|sendto|recvfrom|close|getaddrinfo|freeaddrinfo)$' >&2 || true
  exit 1
fi

"$TMP_EXE"

echo "net-cap-darwin: step 1..10 OK (raw syscalls socket/bind/listen/poll/fcntl/close/DNS without libc refs)"
echo "xlang: [XLANG_NET_CAP_DARWIN] status=ok run=1 obs=0 skip=0 host=Darwin/$(uname -m)"
