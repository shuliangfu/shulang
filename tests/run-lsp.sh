#!/usr/bin/env bash
# LSP 测试：启动 shu --lsp，发送 initialize / didOpen / diagnostics / textDocument/formatting / shutdown / exit，校验 stdout 含预期 JSON-RPC 响应。
# 依赖：带 LSP 的 shu（make -C compiler bootstrap-driver-seed）。

set -e
cd "$(dirname "$0")/.."
SHU="${SHU:-./compiler/shu}"

# 构建带 LSP 的 shu（若尚未构建或无 --lsp 则先 bootstrap-driver-seed）
if ! "$SHU" --help 2>/dev/null | grep -q '\-\-lsp'; then
  make -C compiler bootstrap-driver-seed
  SHU=./compiler/shu
fi

# 发送一条 LSP 消息：Content-Length: N\r\n\r\n<body>
send_lsp() {
  local body="$1"
  local len
  len=$(printf '%s' "$body" | wc -c)
  printf 'Content-Length: %d\r\n\r\n%s' "$len" "$body"
}

# 用 Python 做 JSON 转义（若不可用则用内联写死的短文档）
if command -v python3 >/dev/null 2>&1; then
  DOC_JSON=$(python3 -c "import json; print(json.dumps(open('tests/lsp/main.su').read()))")
else
  DOC_JSON='"function main(): i32 { return 0; }"'
fi

INIT_REQ='{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"processId":null,"rootUri":null,"capabilities":{}}}'
DID_OPEN='{"jsonrpc":"2.0","method":"textDocument/didOpen","params":{"textDocument":{"uri":"file:///tests/lsp/main.su","languageId":"su","version":1,"text":'"$DOC_JSON"'}}}'
DIAG_REQ='{"jsonrpc":"2.0","id":2,"method":"textDocument/diagnostics","params":{"textDocument":{"uri":"file:///tests/lsp/main.su"}}}'
FMT_REQ='{"jsonrpc":"2.0","id":4,"method":"textDocument/formatting","params":{"textDocument":{"uri":"file:///tests/lsp/main.su"},"options":{"tabSize":2,"insertSpaces":true,"maxLineLength":100}}}'
SHUTDOWN='{"jsonrpc":"2.0","id":3,"method":"shutdown"}'
EXIT_NOTIF='{"jsonrpc":"2.0","method":"exit"}'

OUT=$(mktemp)
ERR=$(mktemp)
trap "rm -f $OUT $ERR" EXIT

(
  send_lsp "$INIT_REQ"
  send_lsp "$DID_OPEN"
  send_lsp "$DIAG_REQ"
  send_lsp "$FMT_REQ"
  send_lsp "$SHUTDOWN"
  send_lsp "$EXIT_NOTIF"
) | timeout 5 "$SHU" --lsp 2>"$ERR" >"$OUT"; true

# 至少应收到 initialize 与 shutdown 的响应；stdout 为多条 Content-Length+\r\n\r\n+body
if ! grep -q '"jsonrpc"' "$OUT"; then
  echo "LSP test FAIL: no jsonrpc in output"
  cat "$OUT"
  exit 1
fi
if ! grep -q '"result"' "$OUT"; then
  echo "LSP test FAIL: no result in output"
  cat "$OUT"
  exit 1
fi
if ! grep -q 'capabilities' "$OUT"; then
  echo "LSP test FAIL: initialize response missing capabilities"
  cat "$OUT"
  exit 1
fi
# diagnostics 的 result 应为数组（[] 或 [{...}]）
if ! grep -q '"result":\[' "$OUT"; then
  echo "LSP test FAIL: diagnostics result not an array"
  cat "$OUT"
  exit 1
fi
# capabilities 应包含 documentFormattingProvider
if ! grep -q 'documentFormattingProvider' "$OUT"; then
  echo "LSP test FAIL: capabilities missing documentFormattingProvider"
  cat "$OUT"
  exit 1
fi
# formatting 的 result 应为 TextEdit 数组，且含 newText
if ! grep -q '"newText":' "$OUT"; then
  echo "LSP test FAIL: formatting response missing newText"
  cat "$OUT"
  exit 1
fi

echo "LSP test OK"
