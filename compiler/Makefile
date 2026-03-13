# Shulang 编译器（compiler）构建
# 【兜底/可选】日常构建请用 build_tool：cd compiler && ./build_tool ./shuc（见 analysis/完全脱离C与Makefile路线图.md 阶段 5）。
# 本 Makefile 仅用于：从零构建时得到初始 shuc、build_tool，或执行 make test / bootstrap-verify 等目标。
# 阶段 1：main.c + lexer，产出 shuc；阶段 8：可选 OPT=1 为 shuc 启用 -O2

CC      ?= cc
CFLAGS  ?= -Wall -Wextra -I. -Iinclude -Isrc
# 仅编译 pipeline_gen.c 时加：生成代码难以逐处改，静默已知警告类别，使 bootstrap-driver 整次 0 警告
# -Wno-logical-op-parentheses 等部分选项仅 Clang 支持，GCC 会报 unrecognized，无害；-Wno-type-limits 静默 (pos < 0) 对 size_t 的警告
PIPELINE_GEN_CFLAGS = -Wno-logical-op-parentheses -Wno-unused-variable -Wno-unused-parameter -Wno-bitwise-op-parentheses -Wno-parentheses -Wno-sign-compare -Wno-incompatible-pointer-types-discards-qualifiers -Wno-discarded-qualifiers -Wno-unused-but-set-variable -Wno-type-limits
# 阶段 8：make OPT=1 时为 shuc 启用 -O2，便于开发时快速运行测试
ifeq ($(OPT),1)
  CFLAGS += -O2
endif
TARGET  = shuc
SRCS    = src/main.c src/runtime.c src/preprocess.c src/lexer/lexer.c src/ast/ast.c src/parser/parser.c src/typeck/typeck.c src/codegen/codegen.c
OBJS    = src/main.o src/runtime.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

# C 仅版 shuc：无 main_su/pipeline_su，供 bootstrap-pipeline 用 -E 生成 pipeline_gen.c（避免用已链 main_su 的 $(TARGET) 导致走 .su 路径失败）
SHUC_C = shuc-c
.PHONY: all clean test size-baseline perf-baseline bootstrap-token bootstrap-lexer bootstrap-parser bootstrap-parse-file bootstrap-typeck bootstrap-codegen bootstrap-driver bootstrap-asm check-6.4 bootstrap-self check-7.2 bootstrap-verify build-tool build-tool-su build-via-tool first-time

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SHUC_C): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 6.3：runtime.c 提供 run_compiler_c 与弱符号 main_entry；带 .su 入口时用 runtime_driver.o（含 driver_*/pipeline_*）
src/runtime.o: src/runtime.c
	$(CC) $(CFLAGS) -c -o $@ $<
src/runtime_driver.o: src/runtime.c
	$(CC) $(CFLAGS) -DSHUC_USE_SU_DRIVER -DSHUC_USE_SU_PIPELINE -c -o $@ $<
# shuc_su 用：仅 -DSHUC_USE_SU_PIPELINE，提供 asm_codegen_ast、pipeline_parse_into_buf、main_entry（弱符号）等
src/runtime_su.o: src/runtime.c
	$(CC) $(CFLAGS) -DSHUC_USE_SU_PIPELINE -c -o $@ $<

src/preprocess.o: src/preprocess.c src/preprocess.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/lexer/lexer.o: src/lexer/lexer.c src/lexer/lexer.h include/token.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/ast/ast.o: src/ast/ast.c include/ast.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/parser/parser.o: src/parser/parser.c src/parser/parser.h src/lexer/lexer.h include/ast.h include/token.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/typeck/typeck.o: src/typeck/typeck.c src/typeck/typeck.h include/ast.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/codegen/codegen.o: src/codegen/codegen.c src/codegen/codegen.h include/ast.h
	$(CC) $(CFLAGS) -c -o $@ $<

# shuc_su 使用带 -DSHUC_USE_SU_PIPELINE 编译的 main，否则 #ifdef 块不会生效
src/main_su.o: src/main.c
	$(CC) $(CFLAGS) -DSHUC_USE_SU_PIPELINE -c -o $@ $<

PIPELINE_OBJS = src/main_su.o src/runtime_su.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

# asm 后端 -o <exe> 时链接用：提供 shulang_panic_；Linux 用 .s（syscall exit 不链 libc），其它用 .c（调 abort 链 libc）
UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)
ifeq ($(UNAME_S),Linux)
runtime_panic.o: src/asm/runtime_panic_x86_64.s
	$(CC) -c -o $@ $<
else
runtime_panic.o: src/asm/runtime_panic.c
	$(CC) $(CFLAGS) -c -o $@ $<
endif

# 无 C 自举：crt0 提供 _start 与 driver_get_argv_i（仅 Linux x86_64）；链接 asm 版 shuc 时用本 .o 替代 main.o / runtime_asm_build.o
ifeq ($(UNAME_S),Linux)
src/asm/crt0_x86_64.o: src/asm/crt0_x86_64.s
	$(CC) -c -o $@ $<
endif

# asm 链接无 runtime_driver 时：提供 typeck_float64_bits_lo/hi。Linux 优先用 asm 实现（完全无 C），无 .s 时用 .c
ifeq ($(UNAME_S),Linux)
src/typeck/typeck_f64_bits.o: src/typeck/typeck_f64_bits_x86_64.s
	$(CC) -c -o $@ $<
else
src/typeck/typeck_f64_bits.o: src/typeck/typeck_f64_bits.c
	$(CC) $(CFLAGS) -c -o $@ $<
endif

clean:
	rm -f $(OBJS) src/main_driver.o src/runtime_driver.o src/runtime_su.o src/main_su.o src/asm/runtime_asm_build.o src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o $(TARGET) $(SHUC_C) $(TARGET)_stage1 $(TARGET)_stage2 $(TARGET)_su $(TARGET)_su_stage2 typeck_gen.c typeck_su.o codegen_gen.c codegen_su.o parser_gen.c parser_su.o driver_gen.c driver_su.o pipeline_gen.c pipeline_su.o typeck_su_su.c typeck_su_su.o codegen_su_su.c codegen_su_su.o build_gen.c build_runner_gen.c build_runtime_su_gen.c build_tool.o build_runner.o build_runtime.o build_runtime_su.o build_tool runtime_panic.o

# 阶段 1 词法 + 阶段 3 类型检查 + 阶段 4 Hello World + 阶段 5 import + 阶段 6 std/target
test:
	@if [ -f ../tests/run-lexer.sh ]; then (cd .. && ./tests/run-lexer.sh); fi
	@if [ -f ../tests/run-typeck.sh ]; then (cd .. && chmod +x tests/run-typeck.sh && ./tests/run-typeck.sh); fi
	@if [ -f ../tests/run-hello.sh ]; then (cd .. && chmod +x tests/run-hello.sh && ./tests/run-hello.sh); fi
	@if [ -f ../tests/run-import.sh ]; then (cd .. && chmod +x tests/run-import.sh && ./tests/run-import.sh); fi
	@if [ -f ../tests/run-std.sh ]; then (cd .. && chmod +x tests/run-std.sh && ./tests/run-std.sh); fi
	@if [ -f ../tests/run-stdlib-import.sh ]; then (cd .. && chmod +x tests/run-stdlib-import.sh && ./tests/run-stdlib-import.sh); fi
	@if [ -f ../tests/run-target.sh ]; then (cd .. && chmod +x tests/run-target.sh && ./tests/run-target.sh); fi
	@if [ -f ../tests/run-return-value.sh ]; then (cd .. && chmod +x tests/run-return-value.sh && ./tests/run-return-value.sh); fi
	@if [ -f ../tests/run-multi-func.sh ]; then (cd .. && chmod +x tests/run-multi-func.sh && ./tests/run-multi-func.sh); fi
	@if [ -f ../tests/run-generic.sh ]; then (cd .. && chmod +x tests/run-generic.sh && ./tests/run-generic.sh); fi
	@if [ -f ../tests/run-trait.sh ]; then (cd .. && chmod +x tests/run-trait.sh && ./tests/run-trait.sh); fi
	@if [ -f ../tests/run-multi-file.sh ]; then (cd .. && chmod +x tests/run-multi-file.sh && ./tests/run-multi-file.sh); fi
	@if [ -f ../tests/run-multi-file-generic.sh ]; then (cd .. && chmod +x tests/run-multi-file-generic.sh && ./tests/run-multi-file-generic.sh); fi
	@if [ -f ../tests/run-binary-expr.sh ]; then (cd .. && chmod +x tests/run-binary-expr.sh && ./tests/run-binary-expr.sh); fi
	@if [ -f ../tests/run-let-const.sh ]; then (cd .. && chmod +x tests/run-let-const.sh && ./tests/run-let-const.sh); fi
	@if [ -f ../tests/run-bool.sh ]; then (cd .. && chmod +x tests/run-bool.sh && ./tests/run-bool.sh); fi
	@if [ -f ../tests/run-if-expr.sh ]; then (cd .. && chmod +x tests/run-if-expr.sh && ./tests/run-if-expr.sh); fi
	@if [ -f ../tests/run-ternary.sh ]; then (cd .. && chmod +x tests/run-ternary.sh && ./tests/run-ternary.sh); fi
	@if [ -f ../tests/run-option.sh ]; then (cd .. && chmod +x tests/run-option.sh && ./tests/run-option.sh); fi
	@if [ -f ../tests/run-result.sh ]; then (cd .. && chmod +x tests/run-result.sh && ./tests/run-result.sh); fi
	@if [ -f ../tests/run-process.sh ]; then (cd .. && chmod +x tests/run-process.sh && ./tests/run-process.sh); fi
	@if [ -f ../tests/run-io.sh ]; then (cd .. && chmod +x tests/run-io.sh && ./tests/run-io.sh); fi
	@if [ -f ../tests/run-while.sh ]; then (cd .. && chmod +x tests/run-while.sh && ./tests/run-while.sh); fi
	@if [ -f ../tests/run-return-expr.sh ]; then (cd .. && chmod +x tests/run-return-expr.sh && ./tests/run-return-expr.sh); fi
	@if [ -f ../tests/run-for.sh ]; then (cd .. && chmod +x tests/run-for.sh && ./tests/run-for.sh); fi
	@if [ -f ../tests/run-float.sh ]; then (cd .. && chmod +x tests/run-float.sh && ./tests/run-float.sh); fi
	@if [ -f ../tests/run-parser.sh ]; then (cd .. && chmod +x tests/run-parser.sh && ./tests/run-parser.sh); fi
	@if [ -f ../tests/run-struct.sh ]; then (cd .. && chmod +x tests/run-struct.sh && ./tests/run-struct.sh); fi
	@if [ -f ../tests/run-slice.sh ]; then (cd .. && chmod +x tests/run-slice.sh && ./tests/run-slice.sh); fi
	@if [ -f ../tests/run-array.sh ]; then (cd .. && chmod +x tests/run-array.sh && ./tests/run-array.sh); fi
	@if [ -f ../tests/run-pointer.sh ]; then (cd .. && chmod +x tests/run-pointer.sh && ./tests/run-pointer.sh); fi
	@if [ -f ../tests/run-enum.sh ]; then (cd .. && chmod +x tests/run-enum.sh && ./tests/run-enum.sh); fi
	@if [ -f ../tests/run-match.sh ]; then (cd .. && chmod +x tests/run-match.sh && ./tests/run-match.sh); fi
	@if [ -f ../tests/run-panic.sh ]; then (cd .. && chmod +x tests/run-panic.sh && ./tests/run-panic.sh); fi
	@if [ -f ../tests/run-defer.sh ]; then (cd .. && chmod +x tests/run-defer.sh && ./tests/run-defer.sh); fi
	@if [ -f ../tests/run-goto.sh ]; then (cd .. && chmod +x tests/run-goto.sh && ./tests/run-goto.sh); fi
	@if [ -f ../tests/run-preprocess.sh ]; then (cd .. && chmod +x tests/run-preprocess.sh && ./tests/run-preprocess.sh); fi
	@if [ -f ../tests/run-su-pipeline.sh ]; then (cd .. && chmod +x tests/run-su-pipeline.sh && ./tests/run-su-pipeline.sh); fi
	@if [ -f ../tests/run-vector.sh ]; then (cd .. && chmod +x tests/run-vector.sh && ./tests/run-vector.sh); fi
	@if [ -f ../tests/run-fmt.sh ]; then (cd .. && chmod +x tests/run-fmt.sh && ./tests/run-fmt.sh); fi
	@if [ -f ../tests/run-debug.sh ]; then (cd .. && chmod +x tests/run-debug.sh && ./tests/run-debug.sh); fi
	@if [ -f ../tests/run-core-types.sh ]; then (cd .. && chmod +x tests/run-core-types.sh && ./tests/run-core-types.sh); fi
	@if [ -f ../tests/run-builtin.sh ]; then (cd .. && chmod +x tests/run-builtin.sh && ./tests/run-builtin.sh); fi
	@if [ -f ../tests/run-mem.sh ]; then (cd .. && chmod +x tests/run-mem.sh && ./tests/run-mem.sh); fi
	@if [ -f ../tests/run-string.sh ]; then (cd .. && chmod +x tests/run-string.sh && ./tests/run-string.sh); fi
	@if [ -f ../tests/run-vec.sh ]; then (cd .. && chmod +x tests/run-vec.sh && ./tests/run-vec.sh); fi
	@if [ -f ../tests/run-heap.sh ]; then (cd .. && chmod +x tests/run-heap.sh && ./tests/run-heap.sh); fi
	@if [ -f ../tests/run-runtime.sh ]; then (cd .. && chmod +x tests/run-runtime.sh && ./tests/run-runtime.sh); fi
	@if [ -f ../tests/run-fs.sh ]; then (cd .. && chmod +x tests/run-fs.sh && ./tests/run-fs.sh); fi
	@if [ -f ../tests/run-path.sh ]; then (cd .. && chmod +x tests/run-path.sh && ./tests/run-path.sh); fi
	@if [ -f ../tests/run-map.sh ]; then (cd .. && chmod +x tests/run-map.sh && ./tests/run-map.sh); fi
	@if [ -f ../tests/run-error.sh ]; then (cd .. && chmod +x tests/run-error.sh && ./tests/run-error.sh); fi
	@if [ -f ../tests/run-net.sh ]; then (cd .. && chmod +x tests/run-net.sh && ./tests/run-net.sh); fi
	@if [ -f ../tests/run-io-driver.sh ]; then (cd .. && chmod +x tests/run-io-driver.sh && ./tests/run-io-driver.sh); fi
	@if [ -f ../tests/run-ub.sh ]; then (cd .. && chmod +x tests/run-ub.sh && ./tests/run-ub.sh); fi
	@if [ -f ../tests/run-abi-layout.sh ]; then (cd .. && chmod +x tests/run-abi-layout.sh && ./tests/run-abi-layout.sh); fi

# 自举 9.1：用 shuc 编译 token 模块（库）+ token_standalone.su（入口），验证 .su 前端数据定义可由宿主编译
bootstrap-token: $(TARGET)
	./$(TARGET) -L src/lexer src/lexer/token_standalone.su -o /tmp/shuc_token_test && /tmp/shuc_token_test && echo "bootstrap-token OK"

# 自举 9.1：用 shuc 编译 lexer.su（入口，import token），验证多文件 + 跨模块 enum 可编译链接
bootstrap-lexer: $(TARGET)
	./$(TARGET) -L src/lexer src/lexer/lexer.su -o /tmp/shuc_lexer_test && /tmp/shuc_lexer_test && echo "bootstrap-lexer OK"

# 自举 9.1：用 shuc 编译 parser.su（import lexer + token + ast + std.fs），解析 function main(): i32 { return 0; } 并验证；-L .. 供 std.fs，-L src/lexer 供 token，-L src/ast 供 ast
bootstrap-parser: $(TARGET)
	rm -f /tmp/shu_parse_test.su && ./$(TARGET) -L .. -L src/lexer -L src/ast src/parser/parser.su -o /tmp/shuc_parser_test && /tmp/shuc_parser_test && echo "bootstrap-parser OK"

# 9.1 联调：.su 前端能处理示例 .su 并与 C 版结果一致；写示例（NUL 结尾）到 /tmp/shu_parse_test.su，跑 .su 解析器与 shuc 对比，二者均 parse OK 则通过
bootstrap-parse-file: $(TARGET) bootstrap-parser
	@printf 'function main(): i32 { return 0; }\0' > /tmp/shu_parse_test.su && \
	/tmp/shuc_parser_test && echo "su parser: parse OK" && \
	(out=$$(./$(TARGET) -L .. /tmp/shu_parse_test.su 2>&1); echo "$$out" | grep -q "parse OK") && echo "C parser: parse OK" && \
	echo "bootstrap-parse-file OK"

# 迁移到 .su：由 parser.su 生成 parser_gen.c 并编出 parser_su.o，供后续「仅链 .su 版 parser/typeck/codegen」使用（当前 pipeline_gen.c 已内联 .su 逻辑，此处先建产线）
parser_gen.c: $(TARGET) src/parser/parser.su
	./$(TARGET) -L .. -L src/lexer -L src/ast src/parser/parser.su -E > parser_gen.c
	@echo "parser_gen.c: from parser.su"
parser_su.o: parser_gen.c
	$(CC) $(CFLAGS) -c parser_gen.c -o parser_su.o
	@echo "parser_su.o OK"

# 迁移到 .su：一次性生成 parser_su.o、typeck_su.o、codegen_su.o，供后续「仅链 .su 版」流水线使用（当前 bootstrap-driver 仍用 pipeline_gen.c 内联版）
migrate-su-objs: parser_su.o typeck_su.o codegen_su.o
	@echo "migrate-su-objs OK (parser_su.o typeck_su.o codegen_su.o 已就绪)"
typeck_su.o: $(TARGET) src/typeck/typeck.su
	./$(TARGET) -L .. -L src/lexer -L src/ast src/typeck/typeck.su -E > typeck_gen.c && $(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
codegen_su.o: $(TARGET) src/codegen/codegen.su
	./$(TARGET) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck src/codegen/codegen.su -E > codegen_gen.c && $(CC) $(CFLAGS) -c codegen_gen.c -o codegen_su.o

# 6.1：.su typeck 入口与 C AST 对接；用 C-only shuc 编译 typeck.su 生成 typeck_gen.c，再链接进 shuc，使 typeck 由 .su 入口转调 C
bootstrap-typeck: $(TARGET)
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
	$(CC) $(CFLAGS) -DSHUC_USE_SU_TYPECK -o $(TARGET) $(OBJS) typeck_su.o
	@echo "bootstrap-typeck OK"

# 6.2：.su codegen 入口与 C AST 对接；编译 typeck.su + codegen.su 生成 _gen.c，链接进 shuc，使 typeck 与 codegen 均由 .su 入口转调 C
bootstrap-codegen: $(TARGET)
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c
	./$(TARGET) src/codegen/codegen.su -E > codegen_gen.c
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
	$(CC) $(CFLAGS) -c codegen_gen.c -o codegen_su.o
	$(CC) $(CFLAGS) -DSHUC_USE_SU_TYPECK -DSHUC_USE_SU_CODEGEN -o $(TARGET) $(OBJS) typeck_su.o codegen_su.o
	@echo "bootstrap-codegen OK"

# 6.3/6.4：入口在 main.su；链接时用 main_driver.o（带 SHUC_USE_SU_DRIVER/PIPELINE 以启用 -backend asm）+ runtime_driver.o + ...
src/main_driver.o: src/main.c
	$(CC) $(CFLAGS) -DSHUC_USE_SU_DRIVER -DSHUC_USE_SU_PIPELINE -c -o $@ $<
DRIVER_OBJS = src/main_driver.o src/runtime_driver.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

# 6.3：.su 入口与 main.c 一一对应；pipeline_su.o 已含 typeck/codegen（单文件展开），故仅链 driver_su.o + pipeline_su.o，不链 typeck_su/codegen_su 避免重复符号。用 $(SHUC_C) 生成 driver_gen.c 保证始终用当前 main.su 展开（否则已链 main_su 的 $(TARGET) 会带旧逻辑）。
bootstrap-driver: $(TARGET) $(SHUC_C) $(DRIVER_OBJS) pipeline_gen.c
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -c pipeline_gen.c -o pipeline_su.o
	./$(SHUC_C) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.su -E -E-extern > driver_gen.c
	@# 与 pipeline_gen.c 一致：修正 preprocess 展开后 slice 用 . 访问（应为 ->）及 preprocess_su_buf 的 extern 签名
	@sed -i.bak -e 's/(out_buf)\.length/(out_buf)->length/g' -e 's/(out_buf)\.data/(out_buf)->data/g' -e 's/(source)\.length/(source)->length/g' -e 's/(source)\.data/(source)->data/g' -e 's/extern int32_t preprocess_preprocess_su_buf(uint8_t, ptrdiff_t, uint8_t, int32_t);/extern int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);/' driver_gen.c 2>/dev/null || (sed -e 's/(out_buf)\.length/(out_buf)->length/g' -e 's/(out_buf)\.data/(out_buf)->data/g' -e 's/(source)\.length/(source)->length/g' -e 's/(source)\.data/(source)->data/g' -e 's/extern int32_t preprocess_preprocess_su_buf(uint8_t, ptrdiff_t, uint8_t, int32_t);/extern int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);/' driver_gen.c > driver_gen.c.tmp && mv driver_gen.c.tmp driver_gen.c)
	@# 消除 -Wincompatible-pointer-types：main.su 中 pipeline_run_su_pipeline_impl 的 out_buf/ctx 为 *u8，生成 extern 为 uint8_t*，调用处传 struct*，改为 void* 即匹配
	@sed -e 's/pipeline_run_su_pipeline_impl(uint8_t \* arena, uint8_t \* module, struct main_PipelineSourceSlice \* source, uint8_t \* out_buf, uint8_t \* ctx)/pipeline_run_su_pipeline_impl(uint8_t * arena, uint8_t * module, struct main_PipelineSourceSlice * source, void * out_buf, void * ctx)/' driver_gen.c > driver_gen.c.tmp 2>/dev/null && mv driver_gen.c.tmp driver_gen.c || true
	@# 消除 -Wsign-compare：ptrdiff_t written 与 size_t len/262144 比较，改为 (written)<0 || (size_t)(written)!=(len)
	@sed -e 's/written != 262144/(written) < 0 || (size_t)(written) != 262144/g' -e 's/written != len/(written) < 0 || (size_t)(written) != (len)/g' driver_gen.c > driver_gen.c.tmp 2>/dev/null && mv driver_gen.c.tmp driver_gen.c || true
	@grep -q 'int run_compiler_c(int argc,' driver_gen.c 2>/dev/null || (echo "" >> driver_gen.c; echo "/* C 符号 run_compiler_c 供 runtime.c 调用，转调 main.su 的 main_run_compiler_c */" >> driver_gen.c; echo "int run_compiler_c(int argc, char **argv) { return main_run_compiler_c(argc, (uint8_t *)argv); }" >> driver_gen.c)
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o
	$(CC) $(CFLAGS) -DSHUC_USE_SU_DRIVER -DSHUC_USE_SU_PIPELINE -o $(TARGET) $(DRIVER_OBJS) driver_su.o pipeline_su.o
	@echo "bootstrap-driver OK"

# Goal 2（用 asm 后端构建 shuc）：构建最小 C 桩 + 可选执行 asm 自举脚本（需先 bootstrap-driver）
bootstrap-asm: $(TARGET) src/asm/runtime_asm_build.o src/runtime_driver.o
	@echo "bootstrap-asm: runtime_asm_build.o + runtime_driver.o ready."
	@echo "  Full asm build: SHUC=./$(TARGET) ./scripts/build_shuc_asm.sh (requires bootstrap-driver first)"
bootstrap-asm-full: bootstrap-driver bootstrap-asm
	@SHUC=./$(TARGET) ./scripts/build_shuc_asm.sh

# 6.4 验收：宿主编译器（C-only shuc）能编译整机 .su（typeck+codegen+driver）并产出新 shuc，且新 shuc 能编译运行测试（return-value 返回 42 视为成功）
check-6.4: $(TARGET)
	@$(MAKE) bootstrap-driver && ./$(TARGET) ../tests/return-value/main.su -o /tmp/check64 && /tmp/check64; [ $$? -eq 42 ] && echo "check-6.4 OK"

# 首次/从零构建：一条命令得到 shuc + build_tool（build-tool 依赖 $(TARGET) 会先产出 shuc）。与 README「读者一次做对」一致。
first-time: build-tool

# 阶段 7：build.su 在仓库根目录，用 shuc 编成 build_tool（在 compiler 目录下），运行 build_tool 即完成一次编译器构建
build-tool: $(TARGET)
	./$(TARGET) ../build.su -E > build_gen.c
	$(CC) $(CFLAGS) -c build_gen.c -o build_tool.o
	$(CC) $(CFLAGS) -c src/build_runtime.c -o build_runtime.o
	$(CC) $(CFLAGS) -o build_tool build_tool.o build_runtime.o
	@echo "build_tool OK（在 compiler 目录下运行 ./build_tool ./shuc 可产出 shuc）"

# build_tool 完全无 C（仅 Linux）：crt0 + build_runner.su + build.su + build_runtime_su.su，不再链接 build_runtime.c
ifeq ($(UNAME_S),Linux)
build-tool-su: $(TARGET) src/asm/crt0_x86_64.o
	./$(TARGET) ../build.su -E > build_gen.c
	$(CC) $(CFLAGS) -c build_gen.c -o build_tool.o
	./$(TARGET) ../build_runner.su -E > build_runner_gen.c
	$(CC) $(CFLAGS) -c build_runner_gen.c -o build_runner.o
	./$(TARGET) ../build_runtime_su.su -E > build_runtime_su_gen.c
	$(CC) $(CFLAGS) -ffreestanding -c build_runtime_su_gen.c -o build_runtime_su.o
	$(CC) $(CFLAGS) -o build_tool src/asm/crt0_x86_64.o build_runner.o build_tool.o build_runtime_su.o -lc
	@echo "build_tool OK (no C runtime; run ./build_tool ./shuc)"
endif

# 运行 build_tool 产出 shuc（等价于 make bootstrap-driver，无需执行 Makefile bootstrap-driver 目标）
build-via-tool: build-tool
	./build_tool ./$(TARGET)
	@echo "build-via-tool OK（shuc 已由 build_tool 产出）"

# 阶段 8.1/8.2：bootstrap-driver 产出 shuc₁；用 shuc₁ 再编 pipeline + main.su 得到 shuc₂（与 6.3 链路一致：driver_su.o + pipeline_su.o）
bootstrap-self: bootstrap-driver
	@cp $(TARGET) $(TARGET)_stage1 && \
	$(MAKE) -s pipeline_gen.c 2>/dev/null || true && \
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -c pipeline_gen.c -o pipeline_su.o && \
	./$(TARGET) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.su -E -E-extern > driver_gen.c && \
	sed -e 's/int32_t __tmp;/int32_t __tmp = 0;/g' driver_gen.c > driver_gen.c.tmp && mv driver_gen.c.tmp driver_gen.c && \
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o && \
	$(CC) $(CFLAGS) -DSHUC_USE_SU_DRIVER -DSHUC_USE_SU_PIPELINE -o $(TARGET)_stage2 $(DRIVER_OBJS) driver_su.o pipeline_su.o && \
	./$(TARGET)_stage2 -su -E ../tests/return-value/main.su > /tmp/out_self.c && $(CC) $(CFLAGS) -o /tmp/out_self /tmp/out_self.c -I. -Iinclude -Isrc && /tmp/out_self; EX=$$?; [ $$EX -eq 42 ] && echo "bootstrap-self OK (shuc1 -> shuc2)" || (echo "bootstrap-self FAIL: stage2 or out_self exit=$$EX"; exit 1)

# 阶段 8.3：两代 shuc 对同一测试套件（run-all.sh）行为一致；run-all 含 run-su-pipeline/run-su-multi-file，需先各自编出 shuc_su
check-7.2: bootstrap-self
	@ROOT=$$(pwd)/..; \
	cp $(TARGET)_stage1 $(TARGET) && cd $$ROOT && SHUC=$$ROOT/compiler/$(TARGET)_stage1 ./tests/run-all.sh > /tmp/run_shuc1.log 2>&1; E1=$$?; \
	cd $$ROOT/compiler && cp $(TARGET)_stage2 $(TARGET) && cd $$ROOT && SHUC=$$ROOT/compiler/$(TARGET)_stage2 ./tests/run-all.sh > /tmp/run_shuc2.log 2>&1; E2=$$?; \
	if [ $$E1 -eq 0 ] && [ $$E2 -eq 0 ]; then echo "check-7.2 OK (both shuc generations passed full test suite)"; else echo "shuc1 exit=$$E1 shuc2 exit=$$E2"; exit 1; fi

# 9.1 自举：纯 .su 流水线（parse_into → typeck_su_ast → codegen_su_ast）；生成 pipeline_gen.c 便于联调；-L 与 pipeline 依赖一致。用 $(SHUC_C) 保证 -E 走 C 路径（parse/codegen），否则已链 main_su 的 $(TARGET) 会走 .su 路径且可能无输出。
bootstrap-pipeline: $(SHUC_C)
	./$(SHUC_C) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess src/pipeline/pipeline.su -E > pipeline_gen.c 2>/dev/null || true
	@echo "bootstrap-pipeline: pipeline_gen.c generated (if failed check parser/typeck/codegen/ast/lexer/preprocess and std.fs paths)"

# 在 pipeline_gen.c 末尾追加 slice 指针包装（C 传 &slice 避免跨单元按值传 struct 导致 length 错乱）与 sizeof 获取函数
pipeline_gen.c: bootstrap-pipeline
	@if grep -q 'pipeline_run_su_pipeline(struct ast_ASTArena' pipeline_gen.c 2>/dev/null && ! grep -q 'pipeline_run_su_pipeline_impl' pipeline_gen.c 2>/dev/null; then \
	  sed 's/int32_t pipeline_run_su_pipeline(struct ast_ASTArena/int32_t pipeline_run_su_pipeline_impl(struct ast_ASTArena/g' pipeline_gen.c > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c; \
	  echo "pipeline_gen.c: renamed run_su_pipeline to _impl (exported for main.su)"; fi
	@grep -q 'source_data.*source_len' pipeline_gen.c 2>/dev/null || \
	(echo "" >> pipeline_gen.c; \
	echo "/* 包装需 int32_t/uint8_t/size_t 与 shulang_slice_uint8_t；-E 已有则只补 include */" >> pipeline_gen.c; \
	echo "#include <stdint.h>" >> pipeline_gen.c; \
	echo "#include <stddef.h>" >> pipeline_gen.c; \
	grep -q 'struct shulang_slice_uint8_t' pipeline_gen.c 2>/dev/null || \
	(echo "#ifndef SHULANG_SLICE_UINT8_T_DEFINED" >> pipeline_gen.c; \
	echo "#define SHULANG_SLICE_UINT8_T_DEFINED" >> pipeline_gen.c; \
	echo "struct shulang_slice_uint8_t { uint8_t *data; size_t length; };" >> pipeline_gen.c; \
	echo "#endif" >> pipeline_gen.c); \
	echo "/* C 包装：main 传 (data, len, ctx)，6.1 dep 通过 ctx 传入；struct ast_PipelineDepCtx 已由 -E 展开 ast 提供 */" >> pipeline_gen.c; \
	echo "int32_t pipeline_run_su_pipeline(struct ast_ASTArena *arena, struct ast_Module *module, const uint8_t *source_data, size_t source_len, struct codegen_CodegenOutBuf *out_buf, struct ast_PipelineDepCtx *ctx) {" >> pipeline_gen.c; \
	echo "  struct shulang_slice_uint8_t source;" >> pipeline_gen.c; \
	echo "  source.data = (uint8_t *)source_data;" >> pipeline_gen.c; \
	echo "  source.length = source_len;" >> pipeline_gen.c; \
	echo '  return pipeline_run_su_pipeline_impl(arena, module, &source, out_buf, ctx);' >> pipeline_gen.c; \
	echo "}" >> pipeline_gen.c; \
	echo "pipeline_gen.c: appended (data,len,ctx) wrapper")
	@grep -q 'pipeline_sizeof_arena' pipeline_gen.c 2>/dev/null || \
	(echo "" >> pipeline_gen.c; echo "#include <stddef.h>" >> pipeline_gen.c; echo "#include \"ast.h\"" >> pipeline_gen.c; \
	echo "size_t pipeline_sizeof_arena(void) { return sizeof(struct ast_ASTArena); }" >> pipeline_gen.c; \
	echo "size_t pipeline_sizeof_module(void) { return sizeof(struct ast_Module); }" >> pipeline_gen.c; \
	echo "pipeline_gen.c: appended size getters")
	@grep -q 'pipeline_sizeof_elf_ctx' pipeline_gen.c 2>/dev/null || \
	(echo "" >> pipeline_gen.c; echo "/* sizeof_elf_ctx 需 size_t 与 platform_elf 结构；无前置 include 时补上 */" >> pipeline_gen.c; \
	echo "#include <stddef.h>" >> pipeline_gen.c; \
	echo "size_t pipeline_sizeof_elf_ctx(void) { return sizeof(struct platform_elf_ElfCodegenCtx); }" >> pipeline_gen.c; \
	echo "pipeline_gen.c: appended sizeof_elf_ctx")
	@# 6.3：修正生成代码中两处问题（extern 第三参应为指针；ndep 未声明改为 get_ndep()）
	@sed -e 's/parser_get_module_import_path(struct ast_Module \*, int32_t, uint8_t);/parser_get_module_import_path(struct ast_Module *, int32_t, uint8_t *);/' \
	    -e 's/while (j < ndep)/while (j < get_ndep())/' pipeline_gen.c > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c 2>/dev/null || true
	@# 仅将「if (EXPR_CALL){ struct ast_Expr callee... } else (struct ast_Expr){0}」处的 __tmp 改为 struct ast_Expr（codegen 可能打成 int32_t）
	@sed -e 's/int32_t __tmp; if ((e)\.kind == ast_ExprKind_EXPR_CALL) {   struct ast_Expr callee/struct ast_Expr __tmp; if ((e).kind == ast_ExprKind_EXPR_CALL) {   struct ast_Expr callee/' pipeline_gen.c > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c 2>/dev/null || true
	@# 6.1 完全自举：修正 preprocess 展开后 slice 用 . 访问（应为 ->）；preprocess_su_buf 的 extern 数组改为指针
	@sed -i.bak -e 's/(out_buf)\.length/(out_buf)->length/g' -e 's/(out_buf)\.data/(out_buf)->data/g' \
	    -e 's/(source)\.length/(source)->length/g' -e 's/(source)\.data/(source)->data/g' \
	    -e 's/extern int32_t preprocess_preprocess_su_buf(uint8_t, ptrdiff_t, uint8_t, int32_t);/extern int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);/' \
	    pipeline_gen.c 2>/dev/null || (sed -e 's/(out_buf)\.length/(out_buf)->length/g' -e 's/(out_buf)\.data/(out_buf)->data/g' -e 's/(source)\.length/(source)->length/g' -e 's/(source)\.data/(source)->data/g' -e 's/extern int32_t preprocess_preprocess_su_buf(uint8_t, ptrdiff_t, uint8_t, int32_t);/extern int32_t preprocess_preprocess_su_buf(uint8_t *source_buf, ptrdiff_t source_len, uint8_t *out_buf, int32_t out_cap);/' pipeline_gen.c > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c)
	@# 7.4 ELF：修正 elf/platform_elf 模块 [64]u8 参数在 extern 中被错误生成为 uint8_t 的问题
	@sed -e 's/extern int32_t elf_elf_add_label(struct elf_ElfCodegenCtx \*, uint8_t, int32_t);/extern int32_t elf_elf_add_label(struct elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len);/g' \
	    -e 's/extern int32_t elf_elf_add_sym(struct elf_ElfCodegenCtx \*, uint8_t, int32_t, int32_t);/extern int32_t elf_elf_add_sym(struct elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len, int32_t offset);/g' \
	    -e 's/extern int32_t platform_elf_elf_add_label(struct platform_elf_ElfCodegenCtx \*, uint8_t, int32_t);/extern int32_t platform_elf_elf_add_label(struct platform_elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len);/g' \
	    -e 's/extern int32_t platform_elf_elf_add_sym(struct platform_elf_ElfCodegenCtx \*, uint8_t, int32_t, int32_t);/extern int32_t platform_elf_elf_add_sym(struct platform_elf_ElfCodegenCtx *, uint8_t name[64], int32_t name_len, int32_t offset);/g' \
	    pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# 7.4 限定类型名：codegen 对 import platform.elf 的模块会生成 xxx.elf.ElfCodegenCtx，C 需 struct platform_elf_ElfCodegenCtx
	@sed -E 's/[a-zA-Z0-9_]+\.elf\.ElfCodegenCtx/struct platform_elf_ElfCodegenCtx/g' \
	    pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# codegen 将 EXPR_INDEX 分支的 __tmp 打成 int32_t，但 else 赋 (struct ast_Type){0}，需改为 struct ast_Type __tmp（含 codegen 初值 __tmp=0 或 = (struct ast_Type){0}）
	@sed -e 's/int32_t __tmp = 0; if ((e)\.kind == ast_ExprKind_EXPR_INDEX && (e)\.index_base_ref != 0 && (e)\.index_index_ref != 0)/struct ast_Type __tmp = (struct ast_Type){0}; if ((e).kind == ast_ExprKind_EXPR_INDEX \&\& (e).index_base_ref != 0 \&\& (e).index_index_ref != 0)/' \
	    pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# macho write：preprocess/codegen 漏掉 let pad，补上 pad 声明
	@sed -e 's/  while (z < pad) {/  int32_t pad = off_sym - (off_text + code_len); while (z < pad) {/' \
	    pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# 若文件首行以 size_t 开头（-E 曾产出异常或仅追加块），则前置 stddef.h 与 ast.h 以便通过编译
	@head -1 pipeline_gen.c | grep -q '^size_t' && (echo "/* Makefile 前置：保证 size_t 与 struct 可见 */"; echo "#include <stddef.h>"; echo "#include \"ast.h\""; cat pipeline_gen.c) > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# parse_into：当 C 前端未将 collect_imports/lex= 纳入 stmt_order 或 expr_stmts 时，将这两行移到 import_res 后、while 前
	@(grep -q 'int32_t out_idx = main_idx;' pipeline_gen.c && grep -q 'struct parser_CollectImportsResult import_res' pipeline_gen.c) && sed -e '/struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };/ { n; s/^  int32_t out_idx = main_idx;$$/  (void)(parser_collect_imports(lex, source, module, (\&(import_res))));\n  (void)((lex = (import_res).lex));\n  int32_t out_idx = main_idx;/; }' pipeline_gen.c > pipeline_gen.c.tmp && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@sed -e '/^  }$$/ { N; N; N; s/^  }\n  (void)(parser_collect_imports(lex, source, module, (\&(import_res))));\n  (void)((lex = (import_res).lex));\n/  }\n/; }' pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# parse_into_buf 内误插入了 collect_imports(lex, source, ...)，该函数只有 data/len，须改为 collect_imports_buf(lex, data, len, ...)
	@awk '/parser_parse_into_buf\(.*\) \{/{ in_buf=1 } in_buf && /parser_collect_imports\(lex, source, module/{ gsub(/parser_collect_imports\(lex, source, module/, "parser_collect_imports_buf(lex, data, len, module"); in_buf=0 } { print }' pipeline_gen.c > pipeline_gen.c.tmp 2>/dev/null && mv pipeline_gen.c.tmp pipeline_gen.c || true
	@# 最后追加 debug 函数（避免前面 sed 影响），保证闭合括号完整
	@grep -q 'pipeline_debug_module_funcs' pipeline_gen.c 2>/dev/null || (echo "" >> pipeline_gen.c; cat pipeline_debug_module_funcs.c.append >> pipeline_gen.c; echo "pipeline_gen.c: appended debug_module_funcs")
	@# 修正 -E 生成代码中声明顺序与命名冲突：zero_u8_p、delta/next_insn、rela→rela_buf
	@$(if $(wildcard scripts/fix_pipeline_gen.py),python3 scripts/fix_pipeline_gen.py pipeline_gen.c,true)

# 链接带 -su 流水线的 shuc（需 main_su.o 用 -DSHUC_USE_SU_PIPELINE 编译，否则 -su -E 不生效）
shuc-su-pipeline: $(PIPELINE_OBJS) pipeline_gen.c
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -c pipeline_gen.c -o pipeline_su.o
	$(CC) $(CFLAGS) -o $(TARGET)_su $(PIPELINE_OBJS) pipeline_su.o
	@echo "shuc_su built; use ./shuc_su -su -E <file.su> to test .su pipeline"

# 4.5（.su 流水线编译 compiler 自身）：用 shuc_su 的 -su -E 生成 typeck.su / codegen.su 对应的 C，再由 cc 链接得到新的 shuc_su_stage2。
# 这一目标的目的，是验证「完整前端（parse_into + typeck_su_ast + codegen_su_ast）」全部跑在 .su 上时，仍能产出能工作的编译器。
bootstrap-su-compiler: shuc-su-pipeline
	./$(TARGET)_su -su -E src/typeck/typeck.su > typeck_su_su.c
	./$(TARGET)_su -su -E src/codegen/codegen.su > codegen_su_su.c
	$(CC) $(CFLAGS) -c typeck_su_su.c -o typeck_su_su.o
	$(CC) $(CFLAGS) -c codegen_su_su.c -o codegen_su_su.o
	$(CC) $(CFLAGS) -DSHUC_USE_SU_TYPECK -DSHUC_USE_SU_CODEGEN -o $(TARGET)_su_stage2 $(OBJS) typeck_su_su.o codegen_su_su.o
	@echo "bootstrap-su-compiler OK (.su 流水线生成 typeck/codegen C 并链接 shuc_su_stage2)"

# 7.3：自举验证通过（7.1+7.2 + 可选记录）。依赖 check-7.2，通过则视为自举验证通过
bootstrap-verify: check-7.2
	@echo "bootstrap-verify OK"

# 阶段 8 体积基线：编译固定用例并输出可执行文件大小
size-baseline:
	@if [ -f ../tests/run-size-baseline.sh ]; then (cd .. && chmod +x tests/run-size-baseline.sh && ./tests/run-size-baseline.sh); fi

# 阶段 8 性能基线：编译并多次运行 perf-baseline，输出耗时
perf-baseline:
	@if [ -f ../tests/run-perf-baseline.sh ]; then (cd .. && chmod +x tests/run-perf-baseline.sh && ./tests/run-perf-baseline.sh); fi
