# Shulang 顶层 Makefile
# 委托 compiler 目录构建，产出 shuc；测试等目标在此统一入口

.PHONY: all clean test

# 默认目标：构建编译器 shuc
all:
	$(MAKE) -C compiler

# 清理构建产物
clean:
	$(MAKE) -C compiler clean

# 测试（阶段 1：词法测试；后续接入 Parser 等）
test:
	$(MAKE) -C compiler test
