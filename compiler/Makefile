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

.PHONY: all clean test size-baseline perf-baseline bootstrap-token bootstrap-lexer

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

clean:
	rm -f $(OBJS) $(TARGET)

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

# 阶段 8 体积基线：编译固定用例并输出可执行文件大小
size-baseline:
	@if [ -f ../tests/run-size-baseline.sh ]; then (cd .. && chmod +x tests/run-size-baseline.sh && ./tests/run-size-baseline.sh); fi

# 阶段 8 性能基线：编译并多次运行 perf-baseline，输出耗时
perf-baseline:
	@if [ -f ../tests/run-perf-baseline.sh ]; then (cd .. && chmod +x tests/run-perf-baseline.sh && ./tests/run-perf-baseline.sh); fi
