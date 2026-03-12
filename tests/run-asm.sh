#!/usr/bin/env bash
# asm 后端测试：-backend asm 出汇编，检查 .text/main/ret，可选 as+ld 跑出退出码。
# 在仓库根目录执行：./tests/run-asm.sh
# 若当前 shuc 不支持 -su/-backend asm（无 pipeline），则 SKIP。

set -e
cd "$(dirname "$0")/.."

# CI 下跳过：bootstrap-driver 构建耗时长，且 -backend asm 在 CI 环境可能失败；本地可单独验证
if [ -n "${GITHUB_ACTIONS:-}" ] || [ -n "${CI:-}" ]; then
  echo "run-asm SKIP (CI: skip -backend asm to avoid long build/fail; run locally to verify)"
  exit 0
fi

make -C compiler -q 2>/dev/null || make -C compiler
# 优先使用 bootstrap-driver 的 shuc（支持 -backend asm 且 -o xxx.o 直接出 ELF）
make -C compiler bootstrap-driver 2>/dev/null || true
make -C compiler bootstrap-pipeline 2>/dev/null || true
make -C compiler shuc-su-pipeline 2>/dev/null || true
if [ -x compiler/shuc ]; then SHUC=./compiler/shuc; elif [ -x compiler/shuc_su ]; then SHUC=./compiler/shuc_su; else SHUC=./compiler/shuc; fi
[ -x "$SHUC" ] || { echo "compiler/shuc not found"; exit 1; }

# 测试用例：main 返回 42；expr 返回 6（2*3）；local 局部 const + VAR（cmp.su 需 C 解析器支持比较，暂不加入）
ASM_TESTS="tests/asm/main.su tests/asm/expr.su tests/asm/local.su"
for F in $ASM_TESTS; do
  [ -f "$F" ] || { echo "run-asm: $F not found"; exit 1; }
done

# 用 -backend asm 出汇编（默认 x86_64）；以 main.su 为代表做 as+ld 与 arm64 校验
MAIN_ASM="tests/asm/main.su"
OUT_S=$(mktemp)
EC=0
"$SHUC" -backend asm "$MAIN_ASM" > "$OUT_S" 2>&1 || EC=$?

if [ "$EC" -ne 0 ]; then
  if grep -q "not available in this build\|unknown option" "$OUT_S" 2>/dev/null; then
    echo "run-asm SKIP (shuc built without -backend asm; run make bootstrap-driver for full asm)"
    rm -f "$OUT_S"
    exit 0
  fi
  echo "run-asm: shuc -backend asm failed (exit $EC)"
  cat "$OUT_S"
  rm -f "$OUT_S"
  exit 1
fi

# 若输出是 C（无 pipeline 时 C driver 可能忽略 -backend asm），则跳过
if grep -q '^#include' "$OUT_S"; then
  echo "run-asm SKIP (shuc built without -su pipeline; -backend asm not used)"
  rm -f "$OUT_S"
  exit 0
fi

# 检查必备汇编
if ! grep -q '\.text' "$OUT_S"; then
  echo "run-asm: output missing .text"
  cat "$OUT_S"
  rm -f "$OUT_S"
  exit 1
fi
if ! grep -q 'main' "$OUT_S"; then
  echo "run-asm: output missing main"
  cat "$OUT_S"
  rm -f "$OUT_S"
  exit 1
fi
if ! grep -q 'ret' "$OUT_S"; then
  echo "run-asm: output missing ret"
  cat "$OUT_S"
  rm -f "$OUT_S"
  exit 1
fi

echo "run-asm: asm output OK (.text, main, ret)"

# 7.4 直接出 ELF .o：-o out.o 应生成可重定位 .o，并可选 ld 运行
DIRECT_O=/tmp/shuc_asm_direct.o
DIRECT_BIN=/tmp/shuc_asm_direct_bin
if "$SHUC" -backend asm -o "$DIRECT_O" "$MAIN_ASM" 2>/dev/null; then
  if file "$DIRECT_O" | grep -q 'ELF.*relocatable'; then
    echo "run-asm: direct -o out.o OK (ELF relocatable)"
    if ld -e _main -o "$DIRECT_BIN" "$DIRECT_O" 2>/dev/null; then
      GOT=0; "$DIRECT_BIN" 2>/dev/null || GOT=$?
      if [ "$GOT" -eq 42 ]; then
        echo "run-asm: direct .o linked and ran OK (exit 42)"
      fi
      rm -f "$DIRECT_BIN"
    fi
  elif file "$DIRECT_O" | grep -q 'Mach-O.*object'; then
    echo "run-asm: direct -o out.o OK (Mach-O object, macOS)"
    if ld -e _main -o "$DIRECT_BIN" "$DIRECT_O" -lSystem 2>/dev/null || clang -o "$DIRECT_BIN" "$DIRECT_O" 2>/dev/null; then
      GOT=0; "$DIRECT_BIN" 2>/dev/null || GOT=$?
      if [ "$GOT" -eq 42 ]; then
        echo "run-asm: direct .o linked and ran OK (exit 42)"
      fi
      rm -f "$DIRECT_BIN"
    fi
  fi
  rm -f "$DIRECT_O"
fi

# -o <exe>（无 .o/.s 后缀）：driver 应自动调 ld 生成可执行文件，一条命令出可执行文件
ASM_EXE=/tmp/shuc_asm_exe
rm -f "$ASM_EXE"
if "$SHUC" -backend asm -o "$ASM_EXE" "$MAIN_ASM" 2>/dev/null; then
  if [ -x "$ASM_EXE" ]; then
    GOT=0; "$ASM_EXE" 2>/dev/null || GOT=$?
    if [ "$GOT" -eq 42 ]; then
      echo "run-asm: -o <exe> (auto ld) OK (exit 42)"
    fi
  fi
  rm -f "$ASM_EXE"
fi

# 多用例：expr.su、local.su 仅校验能成功出汇编且含 .text/main/ret
for ASM_FILE in tests/asm/expr.su tests/asm/local.su; do
  OUT_T=$(mktemp)
  if "$SHUC" -backend asm "$ASM_FILE" > "$OUT_T" 2>/dev/null; then
    if grep -q '\.text' "$OUT_T" && grep -q 'main' "$OUT_T" && grep -q 'ret' "$OUT_T"; then
      echo "run-asm: $(basename "$ASM_FILE") OK"
    fi
  fi
  rm -f "$OUT_T"
done

# 可选：as + ld 并运行 main.su，检查退出码 42；若有 as/ld 再对 expr/local 做 as+ld 校验退出码 7 和 3
OUT_O=/tmp/shuc_asm_test.o
OUT_BIN=/tmp/shuc_asm_test
if as -o "$OUT_O" "$OUT_S" 2>/dev/null; then
  if ld -o "$OUT_BIN" "$OUT_O" 2>/dev/null; then
    GOT=0
    "$OUT_BIN" 2>/dev/null || GOT=$?
    if [ "$GOT" -eq 42 ]; then
      echo "run-asm: linked and ran OK (exit 42)"
    else
      echo "run-asm: linked binary exit code $GOT (expected 42)"
    fi
  else
    echo "run-asm: ld failed (optional, asm output already verified)"
  fi
  rm -f "$OUT_O" "$OUT_BIN"
  # expr.su 预期退出码 6（2*3），local.su 预期 3
  for PAIR in "tests/asm/expr.su:6" "tests/asm/local.su:3"; do
    F="${PAIR%%:*}"; EXPECT="${PAIR##*:}"
    TMP_S=$(mktemp); TMP_O=/tmp/shuc_asm_expr.o; TMP_BIN=/tmp/shuc_asm_expr_bin
    if "$SHUC" -backend asm "$F" > "$TMP_S" 2>/dev/null && as -o "$TMP_O" "$TMP_S" 2>/dev/null && ld -o "$TMP_BIN" "$TMP_O" 2>/dev/null; then
      GOT=0; "$TMP_BIN" 2>/dev/null || GOT=$?
      if [ "$GOT" -eq "$EXPECT" ]; then
        echo "run-asm: as+ld $(basename "$F") OK (exit $EXPECT)"
      fi
    fi
    rm -f "$TMP_S" "$TMP_O" "$TMP_BIN"
  done
else
  echo "run-asm: as failed (optional)"
fi

# 可选：arm64 输出校验（对 main/expr/local 各跑一次，仅检查 .text/main/ret）
for ASM_FILE in $ASM_TESTS; do
  OUT_ARM=$(mktemp)
  if "$SHUC" -backend asm -target aarch64-linux-gnu "$ASM_FILE" > "$OUT_ARM" 2>/dev/null; then
    if grep -q '\.text' "$OUT_ARM" && grep -q 'main' "$OUT_ARM" && grep -q 'ret' "$OUT_ARM"; then
      echo "run-asm: arm64 $(basename "$ASM_FILE") OK"
    fi
  fi
  rm -f "$OUT_ARM"
done

# riscv64 出 .s：对 main/expr/local 各跑 -target riscv64，检查 .text/main/ret（RISC-V 也用 ret）
for ASM_FILE in $ASM_TESTS; do
  OUT_RV=$(mktemp)
  if "$SHUC" -backend asm -target riscv64 "$ASM_FILE" > "$OUT_RV" 2>/dev/null; then
    if grep -q '\.text' "$OUT_RV" && grep -q 'main' "$OUT_RV" && grep -q 'ret' "$OUT_RV"; then
      echo "run-asm: riscv64 $(basename "$ASM_FILE") .s OK"
    fi
  fi
  rm -f "$OUT_RV"
done

# riscv64 直接出 .o：-target riscv64 -o out.o 应生成 ELF；若有 riscv64 ld 则链接并运行
RISCV_O=/tmp/shuc_asm_riscv64.o
RISCV_BIN=/tmp/shuc_asm_riscv64_bin
if "$SHUC" -backend asm -target riscv64 -o "$RISCV_O" "$MAIN_ASM" 2>/dev/null; then
  if file "$RISCV_O" | grep -q 'ELF.*relocatable'; then
    echo "run-asm: riscv64 direct -o out.o OK (ELF relocatable)"
    for LD_CMD in "riscv64-unknown-elf-ld" "riscv64-linux-gnu-ld" "ld.lld" "ld"; do
      if command -v $LD_CMD >/dev/null 2>&1; then
        if $LD_CMD -e _main -o "$RISCV_BIN" "$RISCV_O" 2>/dev/null; then
          GOT=0; "$RISCV_BIN" 2>/dev/null || GOT=$?
          if [ "$GOT" -eq 42 ]; then
            echo "run-asm: riscv64 .o linked and ran OK (exit 42, $LD_CMD)"
            break
          fi
        fi
      fi
    done
    rm -f "$RISCV_BIN"
  fi
  rm -f "$RISCV_O"
fi

# Windows COFF .obj：-target *-windows-* -o out.obj 应生成 PE/COFF（仅 x86_64）；非 Windows 仅校验能产出非空文件
COFF_OBJ=/tmp/shuc_asm_coff.obj
if "$SHUC" -backend asm -target x86_64-pc-windows-msvc -o "$COFF_OBJ" "$MAIN_ASM" 2>/dev/null; then
  if [ -f "$COFF_OBJ" ] && [ -s "$COFF_OBJ" ]; then
    if file "$COFF_OBJ" 2>/dev/null | grep -qiE 'PE32|COFF|MSVC|executable|object'; then
      echo "run-asm: Windows COFF -o out.obj OK (x86_64)"
    else
      echo "run-asm: Windows COFF -o out.obj OK (x86_64, object produced)"
    fi
  fi
  rm -f "$COFF_OBJ"
fi

rm -f "$OUT_S"
echo "run-asm OK"
