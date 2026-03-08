# Shulang 编译器（compiler）构建
# 阶段 1：main.c + lexer，产出 shuc；支持 shuc file.su 打印 Token

CC      ?= cc
CFLAGS  ?= -Wall -Wextra -I. -Iinclude -Isrc
TARGET  = shuc
SRCS    = src/main.c src/lexer/lexer.c src/ast/ast.c src/parser/parser.c src/typeck/typeck.c src/codegen/codegen.c
OBJS    = src/main.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
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
	@if [ -f ../tests/run-target.sh ]; then (cd .. && chmod +x tests/run-target.sh && ./tests/run-target.sh); fi
	@if [ -f ../tests/run-return-value.sh ]; then (cd .. && chmod +x tests/run-return-value.sh && ./tests/run-return-value.sh); fi
	@if [ -f ../tests/run-binary-expr.sh ]; then (cd .. && chmod +x tests/run-binary-expr.sh && ./tests/run-binary-expr.sh); fi
	@if [ -f ../tests/run-let-const.sh ]; then (cd .. && chmod +x tests/run-let-const.sh && ./tests/run-let-const.sh); fi
	@if [ -f ../tests/run-bool.sh ]; then (cd .. && chmod +x tests/run-bool.sh && ./tests/run-bool.sh); fi
	@if [ -f ../tests/run-if-expr.sh ]; then (cd .. && chmod +x tests/run-if-expr.sh && ./tests/run-if-expr.sh); fi
	@if [ -f ../tests/run-while.sh ]; then (cd .. && chmod +x tests/run-while.sh && ./tests/run-while.sh); fi
	@if [ -f ../tests/run-return-expr.sh ]; then (cd .. && chmod +x tests/run-return-expr.sh && ./tests/run-return-expr.sh); fi
	@if [ -f ../tests/run-for.sh ]; then (cd .. && chmod +x tests/run-for.sh && ./tests/run-for.sh); fi
