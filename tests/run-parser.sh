#!/usr/bin/env bash
# 分号统一：语句结束必须加分号；仅 } 后可不加（} 后加也不报错）。正例：带分号通过；负例：return 后缺分号报错。
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

# 正例：return 0; 带分号应能编译
./compiler/shuc tests/parser/semicolon_required.su -o /tmp/shuc_parser_ok 2>&1 || { echo "parser: semicolon_required.su (with semicolon) should compile"; exit 1; }
/tmp/shuc_parser_ok || { echo "parser: semicolon_required binary should exit 0"; exit 1; }

# 负例：return 后无分号应报 parse error
if ./compiler/shuc tests/parser/semicolon_missing.su -o /tmp/shuc_parser_fail 2>&1 | grep -q "expected ';' after return expr"; then
  : # 预期报错
else
  echo "parser: expected parse error for missing semicolon after return"
  exit 1
fi

echo "parser test OK"
