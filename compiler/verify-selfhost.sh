#!/bin/sh
# verify-selfhost.sh — Xlang 语义自举验证（Stage2 X；完全自举 = D+E+F，见 SELFHOST.md）
# 用法: cd compiler && sh verify-selfhost.sh

set -e
cd "$(dirname "$0")"

echo "============================================"
echo " Xlang 自举验证"
echo "============================================"

# ── Step 0: Cold Bootstrap ──────────────────
echo ""
echo "── Step 0: 冷启动 ──"
rm -f *.o src/*.o src/*/*.o _x_stubs.* _xlang2_* xlang xlang-c xlang-x *_gen.c *_x.o 2>/dev/null || true

SRCS="src/main.c src/runtime.c src/asm/runtime_lexer_glue.c seeds/runtime_ast_glue.from_x.c seeds/runtime_lsp_glue.from_x.c"
OBJS=""
for src in $SRCS; do
  obj="${src%.c}.o"
  OBJS="$OBJS $obj"
  cc -Wall -Wextra -I. -Iinclude -Isrc -c -o "$obj" "$src"
done
cc -Wall -Wextra -I. -Iinclude -Isrc -o xlang $OBJS
echo "xlang built: $(ls -lh xlang | awk '{print $5}')"

# invoke_cc 会链 ./runtime_panic.o（见 runtime.c get_runtime_panic_o_path）；冷启动未跑 Makefile 时需先产出。
if [ -f seeds/runtime_panic_arm64.from_x.c ] && [ "$(uname -m 2>/dev/null)" = arm64 ]; then
  sh scripts/cc_inc_tu.sh seeds/runtime_panic_arm64.from_x.c runtime_panic.o
else
  sh scripts/cc_inc_tu.sh seeds/runtime_panic.from_x.c runtime_panic.o
fi
echo "runtime_panic.o ready"

# ── Step 1: Generate all X _gen.c ──────────
echo ""
echo "── Step 1: 生成所有 X 模块 _gen.c ──"

echo "  token..."
./xlang build -L src/lexer -E -E-extern src/lexer/token.x > token_gen.c && echo "    $(wc -l < token_gen.c) lines"

echo "  ast..."
./xlang build -E -E-extern src/ast/ast.x > ast_gen.c && echo "    $(wc -l < ast_gen.c) lines"

echo "  lexer..."
./xlang build -L src/lexer -E -E-extern src/lexer/lexer.x > lexer_gen.c && echo "    $(wc -l < lexer_gen.c) lines"

echo "  parser..."
./xlang build -L .. -L src/lexer -L src/ast -E -E-extern src/parser/parser.x > parser_gen.c && echo "    $(wc -l < parser_gen.c) lines"

echo "  typeck..."
./xlang build -L .. -L src/lexer -L src/ast -E -E-extern src/typeck/typeck.x > typeck_gen.c && echo "    $(wc -l < typeck_gen.c) lines"

echo "  codegen..."
./xlang build -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -E -E-extern src/codegen/codegen.x > codegen_gen.c && echo "    $(wc -l < codegen_gen.c) lines"

echo "  preprocess..."
./xlang build -L src/lexer -E -E-extern src/preprocess/preprocess.x > preprocess_gen.c && echo "    $(wc -l < preprocess_gen.c) lines"

echo "  pipeline..."
./xlang build -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess -L src/asm -E -E-extern src/pipeline/pipeline.x > pipeline_gen.c && echo "    $(wc -l < pipeline_gen.c) lines"

echo "  driver (main.x)..."
./xlang build -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess -E -E-extern src/main.x > driver_gen.c && echo "    $(wc -l < driver_gen.c) lines"

# ── Step 2: Fix generated C files ───────────
echo ""
echo "── Step 2: 修复 _gen.c ──"

# 去重 xlang_slice_uint8_t
for f in parser_gen.c typeck_gen.c codegen_gen.c pipeline_gen.c driver_gen.c preprocess_gen.c; do
  perl -i -ne 'print unless /^struct xlang_slice_uint8_t/ && $seen++' "$f" 2>/dev/null || true
done

# pipeline_gen.c: 确保 parser_parse_into_buf extern 在文件头部
# 删除所有已有 extern 声明（可能在文件末尾），在第一个 xlang_panic_ 前置声明前插入一次
perl -i -ne 'print unless /^extern.*parser_parse_into_buf/' pipeline_gen.c 2>/dev/null || true
perl -i -pe 's/^(static inline void xlang_panic_.*__attribute__)/extern struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena *, struct ast_Module *, uint8_t *, int32_t);\n\n$1/' pipeline_gen.c
echo "  pipeline_gen.c: ensured parser_parse_into_buf extern at top"
echo "  修复完成"

# ── Step 3: Compile all _x.o ──────────────
echo ""
echo "── Step 3: 编译 _x.o (fno-stack-protector) ──"
CFLAGS="-fno-stack-protector -Wall -Wextra -I. -Iinclude -Isrc -w"

echo "  token_x.o..."
cc $CFLAGS -c token_gen.c -o token_x.o

echo "  ast_x.o..."
cc $CFLAGS -c ast_gen.c -o ast_x.o

echo "  lexer_x.o..."
cc $CFLAGS -c lexer_gen.c -o lexer_x.o

echo "  parser_x.o (-include ast.h)..."
cc $CFLAGS -include ast.h -c parser_gen.c -o parser_x.o

echo "  typeck_x.o..."
cc $CFLAGS -c typeck_gen.c -o typeck_x.o

echo "  codegen_x.o..."
cc $CFLAGS -c codegen_gen.c -o codegen_x.o

echo "  preprocess_x.o..."
cc $CFLAGS -c preprocess_gen.c -o preprocess_x.o

echo "  pipeline_x.o..."
perl -i -ne 'print unless /^struct xlang_slice_uint8_t/ && $seen++' pipeline_gen.c 2>/dev/null || true
cc $CFLAGS -c pipeline_gen.c -o pipeline_x.o

echo "  driver_x.o..."
cc $CFLAGS -c driver_gen.c -o driver_x.o

# 编译 C 侧模块
echo ""
echo "  编译 C 侧模块..."
cc $CFLAGS -c seeds/runtime_ast_glue.from_x.c -o ast_c.o
cc $CFLAGS -c src/asm/runtime_lexer_glue.c -o lexer_c.o
cc $CFLAGS -c seeds/runtime_lsp_glue.from_x.c -o lsp_diag_c.o
cc $CFLAGS -c src/std_fs_shim.c -o std_fs_shim_c.o

# 编译桩文件
echo "  编译桩文件..."
# PLATFORM: SHARED — do not emit PREFIX asm_asm_codegen_elf_o
# or PREFIX asm_asm_codegen_ast -1. Product PREFIX emit/ast is
# strong user_asm_seed_bridge; a second PREFIX def is first-wins
# / CG002. Missing provider → link UNDEF, not silent -1.
cat > _x_stubs.c << 'STUBEOF'
#include <stdint.h>
#include <stddef.h>
int io_read_batch_buf(void) { return -1; }
int io_write_batch_buf(void) { return -1; }
int typeck_lsp_main(void) { return -1; }
extern int32_t typeck_preprocess_x_buf(const uint8_t *src, ptrdiff_t src_len, uint8_t *out_buf, int32_t out_cap);
int32_t preprocess_x_buf(const uint8_t *src, ptrdiff_t src_len, uint8_t *out_buf, int32_t out_cap) {
    return typeck_preprocess_x_buf(src, src_len, out_buf, out_cap);
}
STUBEOF
cc $CFLAGS -c _x_stubs.c -o _x_stubs.o

# ── Step 4: Compile runtime_driver ──────────
echo ""
echo "── Step 4: 编译 runtime_driver ──"
cc $CFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_FRONTEND -DXLANG_USE_X_PREPROCESS \
  -c src/runtime.c -o runtime_driver.o
cc $CFLAGS -c src/main.c -o main.o

# ── Step 5: Link xlang-x ─────────────────────
echo ""
echo "── Step 5: 链接 xlang-x ──"
cc -fno-stack-protector -o xlang-x \
  main.o runtime_driver.o \
  lexer_c.o ast_c.o lsp_diag_c.o std_fs_shim_c.o \
  token_x.o ast_x.o lexer_x.o parser_x.o typeck_x.o codegen_x.o preprocess_x.o pipeline_x.o driver_x.o \
  _x_stubs.o

echo "xlang-x linked: $(ls -lh xlang-x | awk '{print $5}')"

# ── Step 6: Typeck 测试 ─────────────────────
echo ""
echo "============================================"
echo "── Step 6: Typeck 测试 ──"
echo "============================================"

# 测试 1: 简单程序编译
cat > /tmp/hello.x << 'EOF'
function main(): i32 { return 42; }
EOF

echo "Test: C 编译器编译 hello.x"
./xlang build /tmp/hello.x -o /tmp/hello_c
chmod +x /tmp/hello_c 2>/dev/null || true
set +e
/tmp/hello_c >/dev/null 2>&1
r1=$?
set -e
echo " 返回值: $r1 (期望: 42)"
if [ "$r1" = "42" ]; then echo "  ✓"; else echo "  ✗"; fi

# 测试 2: 类型错误检测
echo ""
echo "Test: 类型错误检测"
cat > /tmp/test_bad.x << 'EOF'
function main(): i32 { let x: i32 = true; return 0; }
EOF

./xlang build /tmp/test_bad.x -o /tmp/test_bad_c 2>/tmp/test_bad_stderr; rc=$?
if [ $rc -ne 0 ] && (grep -q "typeck error" /tmp/test_bad_stderr 2>/dev/null || [ $rc -ne 0 ]); then
  echo "  ✓ C compiler: type error caught (rc=$rc)"
else
  echo "  ! C compiler: rc=$rc"
  head -3 /tmp/test_bad_stderr 2>/dev/null || true
fi

# 测试 3: X 管线编译
echo ""
echo "Test: X 管线编译 hello.x"
./xlang-x -x -E /tmp/hello.x > /tmp/hello_x_E 2>/tmp/hello_x_stderr; rc=$?
echo "  -x -E: rc=$rc output=$(wc -c < /tmp/hello_x_E 2>/dev/null || echo 0) bytes"
if [ $rc -ne 0 ]; then
  echo "  stderr: $(head -3 /tmp/hello_x_stderr 2>/dev/null || true)"
fi

# ── Summary ─────────────────────────────────
echo ""
echo "============================================"
echo " 自举验证完成"
echo "============================================"
echo " 编译器:"
echo "   xlang      — C 编译器 ($(ls -lh xlang 2>/dev/null | awk '{print $5}' || echo 'N/A'))"
echo "   xlang-x   — X 自举编译器 ($(ls -lh xlang-x 2>/dev/null | awk '{print $5}' || echo 'N/A'))"
echo ""
echo " 下一步: 逐阶段调试 xlang-x -x 管线"
echo "============================================"
