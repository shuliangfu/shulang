# Shulang 编译器（compiler）构建
# 阶段 1：main.c + lexer，产出 shuc；阶段 8：可选 OPT=1 为 shuc 启用 -O2

CC      ?= cc
CFLAGS  ?= -Wall -Wextra -I. -Iinclude -Isrc
# 阶段 8：make OPT=1 时为 shuc 启用 -O2，便于开发时快速运行测试
ifeq ($(OPT),1)
  CFLAGS += -O2
endif
TARGET  = shuc
SRCS    = src/main.c src/preprocess.c src/lexer/lexer.c src/ast/ast.c src/parser/parser.c src/typeck/typeck.c src/codegen/codegen.c
OBJS    = src/main.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

.PHONY: all clean test size-baseline perf-baseline bootstrap-token bootstrap-lexer bootstrap-parser bootstrap-parse-file bootstrap-typeck bootstrap-codegen bootstrap-driver check-6.4 bootstrap-self check-7.2 bootstrap-verify

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

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

PIPELINE_OBJS = src/main_su.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

clean:
	rm -f $(OBJS) src/main_su.o $(TARGET) $(TARGET)_stage1 $(TARGET)_stage2 $(TARGET)_su typeck_gen.c typeck_su.o codegen_gen.c codegen_su.o driver_gen.c driver_su.o pipeline_gen.c pipeline_su.o

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

# 6.3：.su driver 入口；编译 typeck + codegen + driver.su，链接进 shuc，使 main 调用 driver_driver_main 再转调 run_compiler_c
bootstrap-driver: $(TARGET)
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c
	./$(TARGET) src/codegen/codegen.su -E > codegen_gen.c
	./$(TARGET) src/driver/driver.su -E > driver_gen.c
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
	$(CC) $(CFLAGS) -c codegen_gen.c -o codegen_su.o
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o
	$(CC) $(CFLAGS) -DSHUC_USE_SU_TYPECK -DSHUC_USE_SU_CODEGEN -DSHUC_USE_SU_DRIVER -o $(TARGET) $(OBJS) typeck_su.o codegen_su.o driver_su.o
	@echo "bootstrap-driver OK"

# 6.4 验收：宿主编译器（C-only shuc）能编译整机 .su（typeck+codegen+driver）并产出新 shuc，且新 shuc 能编译运行测试（return-value 返回 42 视为成功）
check-6.4: $(TARGET)
	@$(MAKE) bootstrap-driver && ./$(TARGET) ../tests/return-value/main.su -o /tmp/check64 && /tmp/check64; [ $$? -eq 42 ] && echo "check-6.4 OK"

# 6.5 自举：用 bootstrap-driver 产出的 shuc₁ 再编 typeck/codegen/driver.su 得到 shuc₂，验证 shuc₂ 能编译并运行测试
bootstrap-self: bootstrap-driver
	@cp $(TARGET) $(TARGET)_stage1 && \
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c && \
	./$(TARGET) src/codegen/codegen.su -E > codegen_gen.c && \
	./$(TARGET) src/driver/driver.su -E > driver_gen.c && \
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o && \
	$(CC) $(CFLAGS) -c codegen_gen.c -o codegen_su.o && \
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o && \
	$(CC) $(CFLAGS) -DSHUC_USE_SU_TYPECK -DSHUC_USE_SU_CODEGEN -DSHUC_USE_SU_DRIVER -o $(TARGET)_stage2 $(OBJS) typeck_su.o codegen_su.o driver_su.o && \
	./$(TARGET)_stage2 ../tests/return-value/main.su -o /tmp/out_self 2>/dev/null && /tmp/out_self; [ $$? -eq 42 ] && echo "bootstrap-self OK (shuc₁ -> shuc₂)"

# 7.1+7.2：两代 shuc 对同一测试套件行为一致。先 bootstrap-self 得到 shuc_stage1（shuc₁）与 shuc_stage2（shuc₂），再分别用二者跑 run-all.sh，均通过则 OK
check-7.2: bootstrap-self
	@ROOT=$$(pwd)/..; \
	cd $$ROOT && SHUC=$$ROOT/compiler/$(TARGET)_stage1 ./tests/run-all.sh > /tmp/run_shuc1.log 2>&1; E1=$$?; \
	cd $$ROOT && SHUC=$$ROOT/compiler/$(TARGET)_stage2 ./tests/run-all.sh > /tmp/run_shuc2.log 2>&1; E2=$$?; \
	if [ $$E1 -eq 0 ] && [ $$E2 -eq 0 ]; then echo "check-7.2 OK (两代 shuc 测试套件均通过)"; else echo "shuc₁ exit=$$E1 shuc₂ exit=$$E2"; exit 1; fi

# 9.1 自举：纯 .su 流水线（parse_into → typeck_su_ast → codegen_su_ast）；生成 pipeline_gen.c 便于联调；-L 与 pipeline 依赖一致
bootstrap-pipeline: $(TARGET)
	./$(TARGET) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen src/pipeline/pipeline.su -E > pipeline_gen.c 2>/dev/null || true
	@echo "bootstrap-pipeline: pipeline_gen.c generated (若失败请检查 parser/typeck/codegen/ast/lexer 及 std.fs 路径)"

# 在 pipeline_gen.c 末尾追加 sizeof 获取函数（仅当尚未追加时），供 main.c -su 分支分配 arena/module；结构体名与方案 A 全量展开一致（ast_*）
pipeline_gen.c: bootstrap-pipeline
	@grep -q 'pipeline_sizeof_arena' pipeline_gen.c 2>/dev/null || \
	(echo "" >> pipeline_gen.c; echo "#include <stddef.h>" >> pipeline_gen.c; \
	echo "size_t pipeline_sizeof_arena(void) { return sizeof(struct ast_ASTArena); }" >> pipeline_gen.c; \
	echo "size_t pipeline_sizeof_module(void) { return sizeof(struct ast_Module); }" >> pipeline_gen.c; \
	echo "pipeline_gen.c: appended size getters")

# 链接带 -su 流水线的 shuc（需 main_su.o 用 -DSHUC_USE_SU_PIPELINE 编译，否则 -su -E 不生效）
shuc-su-pipeline: $(PIPELINE_OBJS) pipeline_gen.c
	$(CC) $(CFLAGS) -c pipeline_gen.c -o pipeline_su.o
	$(CC) $(CFLAGS) -o $(TARGET)_su $(PIPELINE_OBJS) pipeline_su.o
	@echo "shuc_su 已生成，可用 ./$(TARGET)_su -su -E <file.su> 测试纯 .su 流水线"

# 7.3：自举验证通过（7.1+7.2 + 可选记录）。依赖 check-7.2，通过则视为自举验证通过
bootstrap-verify: check-7.2
	@echo "bootstrap-verify OK (自举验证通过)"

# 阶段 8 体积基线：编译固定用例并输出可执行文件大小
size-baseline:
	@if [ -f ../tests/run-size-baseline.sh ]; then (cd .. && chmod +x tests/run-size-baseline.sh && ./tests/run-size-baseline.sh); fi

# 阶段 8 性能基线：编译并多次运行 perf-baseline，输出耗时
perf-baseline:
	@if [ -f ../tests/run-perf-baseline.sh ]; then (cd .. && chmod +x tests/run-perf-baseline.sh && ./tests/run-perf-baseline.sh); fi
