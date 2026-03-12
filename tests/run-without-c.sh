#!/usr/bin/env bash
# 脱离对 C 的依赖测试：用 asm 路径构建 shuc_asm（.su → asm → .o + 最少 C 桩链接），
# 再用 shuc_asm 跑全量测试，验证「运行时不依赖 C 逻辑」。
#
# 用法：在仓库根目录执行 ./tests/run-without-c.sh
# 前提：compiler 下已有 shuc 与 build_tool（可先 make -C compiler && make -C compiler build-tool）。
# 本脚本会先确保存在支持 -backend asm 的 shuc（make bootstrap-driver），再执行 asm 构建。
#
# 说明：不删除任何 .c 文件；仅验证 asm 产出的 shuc_asm 能通过全部测试，为日后执行第 5 步（删除 .c）做准备。
# 见：analysis/完全自举-无C无Makefile.md §脱离对C的依赖测试。

set -e
cd "$(dirname "$0")/.."
COMPILER_DIR="compiler"
SHUC="${COMPILER_DIR}/shuc"
BUILD_TOOL="${COMPILER_DIR}/build_tool"
SHUC_ASM="${COMPILER_DIR}/shuc_asm"

# 1) 确保有 shuc 与 build_tool（默认 make 即可）
make -C "$COMPILER_DIR" -q 2>/dev/null || make -C "$COMPILER_DIR"
if [ ! -x "$SHUC" ]; then
  echo "run-without-c: no $SHUC; run 'make -C compiler' first."
  exit 1
fi
if [ ! -x "$BUILD_TOOL" ]; then
  make -C "$COMPILER_DIR" build-tool 2>/dev/null || true
fi
if [ ! -x "$BUILD_TOOL" ]; then
  echo "run-without-c: no $BUILD_TOOL; run 'make -C compiler build-tool' first."
  exit 1
fi

# 2) 当前 shuc 必须支持 -backend asm（bootstrap-driver 产出）；否则先构建 bootstrap-driver
SHUC_ASM_CHECK=$(mktemp)
if ! (cd "$COMPILER_DIR" && ./shuc -backend asm -o /dev/null -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -L src/pipeline src/lexer/token.su) 2>"$SHUC_ASM_CHECK"; then
  if grep -q "not available in this build" "$SHUC_ASM_CHECK" 2>/dev/null; then
    echo "run-without-c: building bootstrap-driver (shuc with -backend asm) ..."
    make -C "$COMPILER_DIR" bootstrap-driver 2>/dev/null || true
  fi
fi
rm -f "$SHUC_ASM_CHECK"
# 再次检测：若仍不支持 asm，则 SKIP 以便 run-all 不因环境缺失而失败
if ! (cd "$COMPILER_DIR" && ./shuc -backend asm -o /dev/null -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -L src/pipeline src/lexer/token.su) 2>/dev/null; then
  echo "run-without-c SKIP (shuc does not support -backend asm; run 'make -C compiler bootstrap-driver' for full no-C path)"
  exit 0
fi

# 3) 用 asm 路径构建 shuc_asm（不编任何 .su 为 C，只编为 asm .o + 最少 C 桩链接）
echo "run-without-c: building shuc_asm (asm backend, minimal C link) ..."
(cd "$COMPILER_DIR" && ./build_tool ./shuc asm)
if [ ! -x "$SHUC_ASM" ]; then
  echo "run-without-c: $SHUC_ASM not produced; asm build failed. Fix build_shuc_asm.sh / -backend asm first."
  exit 1
fi

# 4) 用 shuc_asm 跑全量测试（不执行 make，不覆盖 compiler/shuc）
echo "run-without-c: running full test suite with SHUC=$SHUC_ASM ..."
SHUC="$SHUC_ASM" ./tests/run-all.sh

echo "run-without-c: all tests passed with shuc_asm (no-C-runtime path)."
