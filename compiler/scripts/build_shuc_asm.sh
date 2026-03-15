#!/bin/sh
# build_shuc_asm.sh — 用 asm 后端构建 shuc（Goal 2 完全自举：不依赖 cc 编译任何 .su）
# 用法：在 compiler 目录下执行 SHUC=./shuc ./scripts/build_shuc_asm.sh
# 依赖：已 make bootstrap-driver 得到带 -backend asm 的 shuc；需 cc 编 runtime_asm_build.o、runtime_driver.o。

set -e
cd "$(dirname "$0")/.."
SHUC="${SHUC:-./shuc}"
LIBROOT="-L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -L src/pipeline"
BUILD_DIR="build_asm"
mkdir -p "$BUILD_DIR"

echo "build_shuc_asm: using SHUC=$SHUC"

# 按依赖顺序尝试编译各 .su 为 .o（-o xxx.o 仅产出入口模块，依赖为未定义符号，需全部编出后一起链接）
# 若需看 SKIP 原因，可设 SHUC_ASM_VERBOSE=1 保留 stderr
compile_su() {
  local out="$BUILD_DIR/$1"
  local src="$2"
  printf "  asm %s -> %s ... " "$src" "$out"
  if [ -n "${SHUC_ASM_VERBOSE}" ]; then
    if "$SHUC" -backend asm -o "$out" $LIBROOT "$src"; then echo OK; else echo SKIP; fi
  else
    if "$SHUC" -backend asm -o "$out" $LIBROOT "$src" 2>/dev/null; then echo OK; else echo SKIP; fi
  fi
}

compile_su token.o src/lexer/token.su
compile_su ast.o src/ast/ast.su
compile_su codegen.o src/codegen/codegen.su
compile_su typeck.o src/typeck/typeck.su
compile_su lexer.o src/lexer/lexer.su
compile_su preprocess.o src/preprocess/preprocess.su
compile_su std_fs.o ../std/fs/mod.su
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
    echo "  linking shuc_asm (crt0 + typeck_f64_bits + runtime_panic + asm .o, no runtime_driver) ..."
    if "$CC" $CFLAGS -o shuc_asm src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o $ALL_ASM -lc -lm 2>/dev/null; then
      echo "build_shuc_asm: shuc_asm built (no C runtime driver)."
      USE_CRT0=1
    fi
  fi
  if [ "$USE_CRT0" -ne 1 ]; then
    echo "  linking shuc_asm (all asm .o + runtime_driver.o + runtime_asm_build.o) ..."
    if "$CC" $CFLAGS -DSHUC_USE_SU_DRIVER -DSHUC_USE_SU_PIPELINE -o shuc_asm src/asm/runtime_asm_build.o src/runtime_driver.o $ALL_ASM -lm 2>/dev/null; then
      echo "build_shuc_asm: shuc_asm built."
    else
      echo "build_shuc_asm: link failed (missing symbols). See src/asm/README.md Goal 2."
    fi
  fi
else
  echo "build_shuc_asm: main.o or pipeline.o not built by asm; full asm link skipped. Run with working -backend asm to complete."
fi
exit 0
