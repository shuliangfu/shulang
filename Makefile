# Shulang 顶层 Makefile
# 委托 compiler 目录构建，产出 shu；测试等目标在此统一入口

.PHONY: all clean test test_c test_su bootstrap-lexer bootstrap-token

# 默认目标：构建编译器 shu
all:
	$(MAKE) -C compiler

# 清理构建产物
clean:
	$(MAKE) -C compiler clean

# 测试（阶段 1：词法测试；后续接入 Parser 等）
test:
	$(MAKE) -C compiler test

# 仅 C 路径测试（run-*.sh，不含 su 自举）
test_c:
	$(MAKE) -C compiler test_c

# 仅 su 自举测试（bootstrap-driver-seed + run-lsp + run-all-su 全量）
test_su:
	$(MAKE) -C compiler test_su

# 自举：用当前 shu 编译 .su 词法分析器并运行，验证通过则打印 bootstrap-lexer OK
bootstrap-lexer:
	$(MAKE) -C compiler bootstrap-lexer

# 自举：用当前 shu 编译 token.su 并运行（若 compiler 有该目标）
bootstrap-token:
	$(MAKE) -C compiler bootstrap-token
