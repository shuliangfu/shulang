#!/bin/sh
# build_shu_asm.sh — 用 asm 后端构建 shu（Goal 2 完全自举：不依赖 cc 编译任何 .su）
# 用法：在 compiler 目录下执行 SHU=./shu ./scripts/build_shu_asm.sh
# 依赖：已 make bootstrap-driver 得到带 -backend asm 的 shu；需 cc 编 runtime_asm_build.o、runtime_driver.o。
# 构建顺序与 LIBROOT 唯一定义在 src/asm/asm_build_list.su，逻辑后续可迁入 .su。

set -e
cd "$(dirname "$0")/.."
SHU="${SHU:-./shu}"
BUILD_LIST_SU="src/asm/asm_build_list.su"
BUILD_DIR="build_asm"
mkdir -p "$BUILD_DIR"

# 从 .su 唯一定义读取 LIBROOT（行格式：// LIBROOT:<tab>-L .. -L src ...）；TAB 用于兼容 BSD sed
TAB=$(printf '\t')
LIBROOT=""
if [ -f "$BUILD_LIST_SU" ]; then
  LIBROOT=$(grep '^// LIBROOT:' "$BUILD_LIST_SU" | sed "s|^// LIBROOT:${TAB}||")
fi
[ -z "$LIBROOT" ] && LIBROOT="-L .. -L src -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -L src/pipeline"

echo "build_shu_asm: using SHU=$SHU (list from $BUILD_LIST_SU)"

# 按依赖顺序尝试编译各 .su 为 .o（顺序由 asm_build_list.su 的 // BUILD: 行定义）
# SKIP 表示该模块 -backend asm -o 失败。常见原因：rc=-2 解析失败（如 main_idx=-1003 循环防护）；rc=-6 asm codegen 失败（库模块中某表达式/函数 asm 后端尚未支持）。见 src/asm/README.md。
# 若需看 SKIP 原因，可设 SHU_ASM_VERBOSE=1 保留 stderr
compile_su() {
  local out="$BUILD_DIR/$1"
  local src="$2"
  printf "  asm %s -> %s ... " "$src" "$out"
  if [ -n "${SHU_ASM_VERBOSE}" ]; then
    if "$SHU" -backend asm -o "$out" $LIBROOT "$src"; then echo OK; else echo SKIP; fi
  else
    if "$SHU" -backend asm -o "$out" $LIBROOT "$src" 2>/dev/null; then echo OK; else echo SKIP; fi
  fi
}

if [ -f "$BUILD_LIST_SU" ]; then
  grep '^// BUILD:' "$BUILD_LIST_SU" | while IFS= read -r line; do
    rest=$(echo "$line" | sed "s|^// BUILD:${TAB}||")
    out=$(echo "$rest" | cut -f1)
    src=$(echo "$rest" | cut -f2)
    [ -n "$out" ] && [ -n "$src" ] && compile_su "$out" "$src"
  done
else
  echo "build_shu_asm: $BUILD_LIST_SU not found, using built-in list."
  compile_su token.o src/lexer/token.su
  compile_su ast.o src/ast/ast.su
  compile_su codegen.o src/codegen/codegen.su
  compile_su typeck.o src/typeck/typeck.su
  compile_su lexer.o src/lexer/lexer.su
  compile_su preprocess.o src/preprocess/preprocess.su
  compile_su std_fs.o ../std/fs/mod.su
  compile_su lsp.o src/lsp/lsp.su
  compile_su types.o src/asm/types.su
  compile_su platform_elf.o src/asm/platform/elf.su
  compile_su x86_64.o src/asm/arch/x86_64.su
  compile_su x86_64_enc.o src/asm/arch/x86_64_enc.su
  compile_su arm64.o src/asm/arch/arm64.su
  compile_su arm64_enc.o src/asm/arch/arm64_enc.su
  compile_su riscv64.o src/asm/arch/riscv64.su
  compile_su riscv64_enc.o src/asm/arch/riscv64_enc.su
  compile_su peephole.o src/asm/peephole.su
  compile_su backend.o src/asm/backend.su
  compile_su asm.o src/asm/asm.su
  compile_su macho.o src/asm/platform/macho.su
  compile_su coff.o src/asm/platform/coff.su
  compile_su parser.o src/parser/parser.su
  compile_su pipeline.o src/pipeline/pipeline.su
  compile_su main.o src/main.su
fi

# 链接：仅当 main.o 与 pipeline.o 均来自 asm 时，用 asm 版链接。
# 优先尝试「无 C 桩」路径（仅 Linux）：crt0_x86_64.o + typeck_f64_bits.o + runtime_panic.o + build_asm/*.o + -lc -lm；
# 失败或非 Linux 时回退到 runtime_asm_build.o + runtime_driver.o。
CC="${CC:-cc}"
CFLAGS="-Wall -Wextra -I. -Iinclude -Isrc"
if [ -f "$BUILD_DIR/main.o" ] && [ -f "$BUILD_DIR/pipeline.o" ]; then
  ALL_ASM=$(find "$BUILD_DIR" -name "*.o" | tr '\n' ' ')
  USE_CRT0=0
  if [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
    for o in src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o; do
      if [ ! -f "$o" ]; then make "$o" 2>/dev/null || true; fi
    done
  fi
  if [ "$(uname -s 2>/dev/null)" = "Linux" ] && [ -f src/asm/crt0_x86_64.o ] && [ -f src/typeck/typeck_f64_bits.o ] && [ -f runtime_panic.o ]; then
    echo "  linking shu_asm (crt0 + typeck_f64_bits + runtime_panic + asm .o, no runtime_driver) ..."
    if "$CC" $CFLAGS -o shu_asm src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o $ALL_ASM -lc -lm 2>/dev/null; then
      echo "build_shu_asm: shu_asm built (no C runtime driver)."
      USE_CRT0=1
    fi
  fi
  if [ "$USE_CRT0" -ne 1 ]; then
    echo "  linking shu_asm (all asm .o + runtime_driver.o + runtime_asm_build.o) ..."
    if "$CC" $CFLAGS -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -o shu_asm src/asm/runtime_asm_build.o src/runtime_driver.o $ALL_ASM -lm 2>/dev/null; then
      echo "build_shu_asm: shu_asm built."
    else
      echo "build_shu_asm: link failed (missing symbols). See src/asm/README.md Goal 2."
    fi
  fi
else
  echo "build_shu_asm: main.o or pipeline.o not built by asm; full asm link skipped. Run with working -backend asm to complete."
fi
exit 0
