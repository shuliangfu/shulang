#!/usr/bin/env bash
# run-net-cap-win-gate.sh — Windows Winsock network Cap convergence gate (9.1.7)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "=== NET-CAP-WIN: Windows Winsock network Cap (9.1.7) ==="

UNAME_S="$(uname -s)"
case "$UNAME_S" in
  MINGW*|MSYS*|CYGWIN*)
    ;;
  *)
    echo "net-cap-win: host is $UNAME_S (not Windows), skipping."
    echo "xlang: [XLANG_NET_CAP_WIN] status=ok run=0 obs=0 skip=1 host=$UNAME_S"
    exit 0
    ;;
esac

TMP_EXE="/tmp/xlang_net_cap_win_smoke_$$.exe"
trap 'rm -f "$TMP_EXE"' EXIT

gcc -O2 -I"$ROOT" -I"$ROOT/compiler/include" \
  tests/sys/net_cap_win_smoke.c -o "$TMP_EXE" -lws2_32

"$TMP_EXE"

echo "net-cap-win: step 1..10 OK (Winsock Cap without manual WSAStartup refs)"
echo "xlang: [XLANG_NET_CAP_WIN] status=ok run=1 obs=0 skip=0 host=Windows"
