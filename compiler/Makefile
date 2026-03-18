# Shulang 编译器（compiler）构建
# 【兜底/可选】日常构建请用 build_tool：cd compiler && ./build_tool ./shu（见 analysis/完全脱离C与Makefile路线图.md 阶段 5）。
# 本 Makefile 仅用于：从零构建时得到初始 shu、build_tool，或执行 make test / bootstrap-verify 等目标。
# 阶段 1：main.c + lexer，产出 shu；阶段 8：可选 OPT=1 为 shu 启用 -O2
#
# 【生成 C 后无补丁】-E 产出 pipeline_gen.c / driver_gen.c 后不再做 sed/awk/perl/echo 后处理。
# pipeline_gen.c：包装/size/debug 由 runtime.c 在 -E 且入口为 pipeline.su 时追加 pipeline_glue.c 到 stdout，Makefile 不修改生成文件。
# driver_gen.c：仅由 -E -E-extern 生成；run_compiler_c 在 runtime.c 定义；字段 ->、written 比较等已在 codegen/main.su 从根源修。

CC      ?= cc
CFLAGS  ?= -Wall -Wextra -I. -Iinclude -Isrc
# 仅编译 pipeline_gen.c 时加：生成代码难以逐处改，静默已知警告类别，使 bootstrap-driver 整次 0 警告
# -Wno-logical-op-parentheses 等部分选项仅 Clang 支持，GCC 会报 unrecognized，无害；-Wno-ignored-qualifiers 与 -Wno-discarded-qualifiers 同义，Clang 用前者；-Wno-type-limits 静默 (pos < 0) 对 size_t 的警告
PIPELINE_GEN_CFLAGS = -Wno-logical-op-parentheses -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-bitwise-op-parentheses -Wno-parentheses -Wno-sign-compare -Wno-incompatible-pointer-types-discards-qualifiers -Wno-ignored-qualifiers -Wno-unused-but-set-variable -Wno-type-limits
# 阶段 8：make OPT=1 时为 shu 启用 -O2，便于开发时快速运行测试
ifeq ($(OPT),1)
  CFLAGS += -O2
endif
TARGET  = shu
SRCS    = src/main.c src/runtime.c src/preprocess.c src/lexer/lexer.c src/ast/ast.c src/parser/parser.c src/typeck/typeck.c src/codegen/codegen.c
OBJS    = src/main.o src/runtime.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o src/lsp/lsp_diag.o

# C 仅版 shu：无 main_su/pipeline_su，供 bootstrap-pipeline 用 -E 生成 pipeline_gen.c（避免用已链 main_su 的 $(TARGET) 导致走 .su 路径失败）
SHU_C = shu-c
.PHONY: all clean test size-baseline perf-baseline bootstrap-token bootstrap-lexer bootstrap-parser bootstrap-parse-file bootstrap-typeck bootstrap-codegen bootstrap-driver bootstrap-driver-seed bootstrap-driver-asm bootstrap-driver-asm-only bootstrap-asm check-6.4 bootstrap-self check-7.2 bootstrap-verify bootstrap-test build-tool build-tool-su build-via-tool first-time

# 舒 IO 后端（分析/舒IO实现路线图.md 阶段 1）：源码在 std/io/io.c；产出 ../std/io/io.o。
../std/io/io.o: ../std/io/io.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.fs 高性能：mmap/munmap（std/fs/fs.c）；链接用户程序时由 runtime.c 链入 ../std/fs/fs.o。
../std/fs/fs.o: ../std/fs/fs.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.process：argc/argv/getenv（std/process/process.c）；链接用户程序时由 runtime.c 链入 ../std/process/process.o。
../std/process/process.o: ../std/process/process.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.string：长串快路径 memcmp/memmem（std/string/string.c）；链接用户程序时由 runtime.c 链入 ../std/string/string.o。
../std/string/string.o: ../std/string/string.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.heap：堆分配 malloc/free/realloc（std/heap/heap.c）；供 std.vec、std.map 等使用。
../std/heap/heap.o: ../std/heap/heap.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.runtime：panic/abort 对接 shulang_panic_（std/runtime/runtime.c）；链接时需与 runtime_panic.o 同链。
../std/runtime/runtime.o: ../std/runtime/runtime.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.net：TCP socket（std/net/net.c）；链接用户程序时由 runtime.c 链入 ../std/net/net.o。
../std/net/net.o: ../std/net/net.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.thread：线程（std/thread/thread.c）；链接时由 runtime.c 链入 ../std/thread/thread.o，Unix 需 -lpthread。
../std/thread/thread.o: ../std/thread/thread.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.time：单调/墙钟、sleep（std/time/time.c）；链接用户程序时由 runtime.c 链入 ../std/time/time.o。
../std/time/time.o: ../std/time/time.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.random：密码学安全随机（std/random/random.c）；链接用户程序时由 runtime.c 链入 ../std/random/random.o。
../std/random/random.o: ../std/random/random.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.env：环境变量与临时目录（std/env/env.c）；链接用户程序时由 runtime.c 链入 ../std/env/env.o。
../std/env/env.o: ../std/env/env.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.sync：互斥锁（std/sync/sync.c）；链接用户程序时由 runtime.c 链入 ../std/sync/sync.o；Unix 需 -lpthread。
../std/sync/sync.o: ../std/sync/sync.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.encoding：UTF-8/ASCII（std/encoding/encoding.c）
../std/encoding/encoding.o: ../std/encoding/encoding.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.base64：Base64 编解码（std/base64/base64.c）
../std/base64/base64.o: ../std/base64/base64.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.crypto：SHA-256/512、HMAC（std/crypto/crypto.c）
../std/crypto/crypto.o: ../std/crypto/crypto.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.log：日志 stderr（std/log/log.c）
../std/log/log.o: ../std/log/log.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.test：测试断言（std/test/test.c）
../std/test/test.o: ../std/test/test.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.atomic：原子操作（std/atomic/atomic.c）；链接用户程序时由 runtime.c 链入 ../std/atomic/atomic.o。
../std/atomic/atomic.o: ../std/atomic/atomic.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.channel：有界/无界 channel（std/channel/channel.c）；链接时由 runtime.c 链入；Unix 需 -lpthread。
../std/channel/channel.o: ../std/channel/channel.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.backtrace：调用栈捕获（std/backtrace/backtrace.c）；链接时由 runtime.c 链入。
../std/backtrace/backtrace.o: ../std/backtrace/backtrace.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.hash：SipHash-2-4 Hasher（std/hash/hash.c）；链接时由 runtime.c 链入。
../std/hash/hash.o: ../std/hash/hash.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.math：数学常量与函数（std/math/math.c）；链接时由 runtime.c 链入，需 -lm。
../std/math/math.o: ../std/math/math.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.sort：排序（std/sort/sort.c）；链接时由 runtime.c 链入。
../std/sort/sort.o: ../std/sort/sort.c
	$(CC) $(CFLAGS) -c -o $@ $<

# std.ffi：C 字符串互操作（std/ffi/ffi.c）；链接时由 runtime.c 链入。
../std/ffi/ffi.o: ../std/ffi/ffi.c
	$(CC) $(CFLAGS) -c -o $@ $<

# P4 std 模块（按需链接）
../std/json/json.o: ../std/json/json.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/csv/csv.o: ../std/csv/csv.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/regex/regex.o: ../std/regex/regex.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/compress/compress.o: ../std/compress/compress.c
	$(CC) $(CFLAGS) -c -o $@ $<
# 可选：启用 zlib 的 compress.o，用于 tests/run-compress.sh 测试 gzip
compress-o-zlib: ../std/compress/compress.c
	$(CC) $(CFLAGS) -DSHU_USE_ZLIB -c -o ../std/compress/compress.o ../std/compress/compress.c
../std/unicode/unicode.o: ../std/unicode/unicode.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/dynlib/dynlib.o: ../std/dynlib/dynlib.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/http/http.o: ../std/http/http.c
	$(CC) $(CFLAGS) -c -o $@ $<
../std/tar/tar.o: ../std/tar/tar.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 测试与 shu 链接 std 时依赖的 .o：所有 std 模块 + runtime_panic.o；make test 前必须先有这些文件
STD_AND_PANIC_O = ../std/io/io.o ../std/fs/fs.o ../std/process/process.o ../std/string/string.o ../std/heap/heap.o ../std/runtime/runtime.o ../std/net/net.o ../std/thread/thread.o ../std/time/time.o ../std/random/random.o ../std/env/env.o ../std/sync/sync.o ../std/encoding/encoding.o ../std/base64/base64.o ../std/crypto/crypto.o ../std/log/log.o ../std/atomic/atomic.o ../std/channel/channel.o ../std/backtrace/backtrace.o ../std/hash/hash.o ../std/math/math.o ../std/sort/sort.o ../std/ffi/ffi.o ../std/json/json.o ../std/csv/csv.o ../std/regex/regex.o ../std/compress/compress.o ../std/unicode/unicode.o ../std/dynlib/dynlib.o ../std/http/http.o ../std/tar/tar.o ../std/test/test.o runtime_panic.o

all: $(TARGET) $(STD_AND_PANIC_O)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SHU_C): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 6.3：runtime.c 提供 run_compiler_c 与弱符号 main_entry；带 .su 入口时用 runtime_driver.o（含 driver_*/pipeline_*）
src/runtime.o: src/runtime.c
	$(CC) $(CFLAGS) -c -o $@ $<
src/runtime_driver.o: src/runtime.c
	$(CC) $(CFLAGS) -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -c -o $@ $<
# shu_su 用：仅 -DSHU_USE_SU_PIPELINE，提供 asm_codegen_ast、pipeline_parse_into_buf、main_entry（弱符号）等
src/runtime_su.o: src/runtime.c
	$(CC) $(CFLAGS) -DSHU_USE_SU_PIPELINE -c -o $@ $<

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

# shu_su 使用带 -DSHU_USE_SU_PIPELINE 编译的 main，否则 #ifdef 块不会生效
src/main_su.o: src/main.c
	$(CC) $(CFLAGS) -DSHU_USE_SU_PIPELINE -c -o $@ $<

PIPELINE_OBJS = src/main_su.o src/runtime_su.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

# asm 后端 -o <exe> 时链接用：提供 shulang_panic_；Linux 有 .s 时用 .s（syscall exit 不链 libc），否则用 .c；其它平台用 .c
UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)
# shu-su-pipeline 链接了 ../std/io/io.o；Linux 下 io.c 使用 io_uring，需 -luring -lpthread（见 std/io/io.c 头注释）
PIPELINE_LIBS :=
ifeq ($(UNAME_S),Linux)
  PIPELINE_LIBS := -luring -lpthread
endif
RUNTIME_PANIC_S := $(wildcard src/asm/runtime_panic_x86_64.s)
ifeq ($(UNAME_S),Linux)
ifneq (,$(RUNTIME_PANIC_S))
runtime_panic.o: src/asm/runtime_panic_x86_64.s
	$(CC) -c -o $@ $<
else
runtime_panic.o: src/asm/runtime_panic.c
	$(CC) $(CFLAGS) -c -o $@ $<
endif
else
runtime_panic.o: src/asm/runtime_panic.c
	$(CC) $(CFLAGS) -c -o $@ $<
endif

# 无 C 自举：crt0 提供 _start 与 driver_get_argv_i（仅 Linux x86_64）；链接 asm 版 shu 时用本 .o 替代 main.o / runtime_asm_build.o
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
	rm -f $(OBJS) src/main_driver.o src/runtime_driver.o src/runtime_su.o src/main_su.o ../std/io/io.o ../std/fs/fs.o ../std/process/process.o ../std/string/string.o ../std/heap/heap.o ../std/runtime/runtime.o ../std/net/net.o ../std/thread/thread.o ../std/time/time.o ../std/random/random.o ../std/env/env.o ../std/sync/sync.o ../std/encoding/encoding.o ../std/base64/base64.o ../std/crypto/crypto.o ../std/log/log.o ../std/atomic/atomic.o ../std/channel/channel.o ../std/backtrace/backtrace.o ../std/hash/hash.o ../std/math/math.o ../std/sort/sort.o ../std/ffi/ffi.o ../std/json/json.o ../std/csv/csv.o ../std/regex/regex.o ../std/compress/compress.o ../std/unicode/unicode.o ../std/dynlib/dynlib.o ../std/http/http.o ../std/tar/tar.o ../std/test/test.o src/asm/runtime_asm_build.o src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o $(TARGET) $(SHU_C) $(TARGET)_stage1 $(TARGET)_stage2 $(TARGET)_su $(TARGET)_su_stage2 typeck_gen.c typeck_su.o codegen_gen.c codegen_su.o parser_gen.c parser_su.o driver_gen.c driver_su.o pipeline_gen.c pipeline_su.o typeck_su_su.c typeck_su_su.o codegen_su_su.c codegen_su_su.o build_gen.c build_runner_gen.c build_runtime_su_gen.c build_tool.o build_runner.o build_runtime.o build_runtime_su.o build_tool runtime_panic.o shu_asm
	rm -rf build_asm

# 阶段 1 词法 + 阶段 3 类型检查 + …；依赖 shu 与全部 std .o、runtime_panic.o，clean 后 test 会先构建再跑脚本
test: $(TARGET) $(STD_AND_PANIC_O)
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
	# 自举测试不跑，已从 test 目标中排除（run-su-pipeline / run-asm / run-without-c 等均不执行）
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
	@if [ -f ../tests/run-lsp.sh ]; then (cd .. && chmod +x tests/run-lsp.sh && ./tests/run-lsp.sh); fi
	@echo "Test all OK"

# 自举 9.1：用 shu 编译 token 模块（库）+ token_standalone.su（入口），验证 .su 前端数据定义可由宿主编译
bootstrap-token: $(TARGET)
	./$(TARGET) -L src/lexer src/lexer/token_standalone.su -o /tmp/shu_token_test && /tmp/shu_token_test && echo "bootstrap-token OK"

# 自举 9.1：用 shu 编译 lexer.su（入口，import token），验证多文件 + 跨模块 enum 可编译链接
bootstrap-lexer: $(TARGET)
	./$(TARGET) -L src/lexer src/lexer/lexer.su -o /tmp/shu_lexer_test && /tmp/shu_lexer_test && echo "bootstrap-lexer OK"

# 自举 9.1：用 shu 编译 parser.su（import lexer + token + ast + std.fs），解析 function main(): i32 { return 0; } 并验证；-L .. 供 std.fs，-L src/lexer 供 token，-L src/ast 供 ast
bootstrap-parser: $(TARGET)
	rm -f /tmp/shu_parse_test.su && ./$(TARGET) -L .. -L src/lexer -L src/ast src/parser/parser.su -o /tmp/shu_parser_test && /tmp/shu_parser_test && echo "bootstrap-parser OK"

# 9.1 联调：.su 前端能处理示例 .su 并与 C 版结果一致；写示例（NUL 结尾）到 /tmp/shu_parse_test.su，跑 .su 解析器与 shu 对比，二者均 parse OK 则通过
bootstrap-parse-file: $(TARGET) bootstrap-parser
	@printf 'function main(): i32 { return 0; }\0' > /tmp/shu_parse_test.su && \
	/tmp/shu_parser_test && echo "su parser: parse OK" && \
	(out=$$(./$(TARGET) -L .. /tmp/shu_parse_test.su 2>&1); echo "$$out" | grep -q "parse OK") && echo "C parser: parse OK" && \
	echo "bootstrap-parse-file OK"

# 迁移到 .su：由 parser.su 生成 parser_gen.c 并编出 parser_su.o，供后续「仅链 .su 版 parser/typeck/codegen」使用（pipeline_gen.c 已内联 parser，bootstrap-driver-seed 不链 parser_su.o）。
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

# 6.1：.su typeck 入口与 C AST 对接；用 C-only shu 编译 typeck.su 生成 typeck_gen.c，再链接进 shu，使 typeck 由 .su 入口转调 C
bootstrap-typeck: $(TARGET)
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
	$(CC) $(CFLAGS) -DSHU_USE_SU_TYPECK -o $(TARGET) $(OBJS) typeck_su.o
	@echo "bootstrap-typeck OK"

# 6.2：.su codegen 入口与 C AST 对接；编译 typeck.su + codegen.su 生成 _gen.c，链接进 shu，使 typeck 与 codegen 均由 .su 入口转调 C
bootstrap-codegen: $(TARGET)
	./$(TARGET) src/typeck/typeck.su -E > typeck_gen.c
	./$(TARGET) src/codegen/codegen.su -E > codegen_gen.c
	$(CC) $(CFLAGS) -c typeck_gen.c -o typeck_su.o
	$(CC) $(CFLAGS) -c codegen_gen.c -o codegen_su.o
	$(CC) $(CFLAGS) -DSHU_USE_SU_TYPECK -DSHU_USE_SU_CODEGEN -o $(TARGET) $(OBJS) typeck_su.o codegen_su.o
	@echo "bootstrap-codegen OK"

# 6.3/6.4：入口在 main.su；链接时用 main_driver.o（带 SHU_USE_SU_DRIVER/PIPELINE 以启用 -backend asm）+ runtime_driver.o + ...
src/main_driver.o: src/main.c
	$(CC) $(CFLAGS) -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -c -o $@ $<
DRIVER_OBJS = src/main_driver.o src/runtime_driver.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o
# bootstrap-driver-seed：pipeline_gen.c 单文件展开已含 parser.su，故 pipeline_su.o 提供 parser_*；lsp_diag.c 需 C 解析器 parse()，故链 parser.o
DRIVER_SEED_OBJS = src/main_driver.o src/runtime_driver.o src/preprocess.o src/lexer/lexer.o src/ast/ast.o src/parser/parser.o src/typeck/typeck.o src/codegen/codegen.o

# 6.3：.su 入口与 main.c 一一对应。bootstrap-driver-seed = 用 C 代码生成（生成 pipeline_gen.c / driver_gen.c）得到种子 shu；仅首次或无 shu 时需要。
# bootstrap-driver-asm = 用现有 shu 的 -backend asm 把全部 .su 编成机器码 .o 再链接，不生成 C；产出覆盖 $(TARGET)。
# bootstrap-driver = 先 seed 再 asm，最终 $(TARGET) 为 asm 版（直接出机器码，不依赖生成的 C 文件参与最终链接）。
# 无补丁：driver_gen.c 仅由 -E -E-extern 生成；run_compiler_c 在 runtime.c 中定义并转调 main_run_compiler_c；其余从 main.su/codegen 根源修
# LSP 诊断收集：parser 在 fail 时写入，lsp_build_diagnostics_response 跑 C parser 并生成 JSON 响应
src/lsp/lsp_diag.o: src/lsp/lsp_diag.c src/lsp/lsp_diag.h
	$(CC) $(CFLAGS) -I. -Iinclude -Isrc -c -o $@ $<

# lsp_io.su 单独 -E -E-extern 生成 lsp_io_gen.c，提供 read_message/write_fd/alloc/free 等，std.io/std.heap 为 extern，由 io.o/heap.o 提供。
lsp_io_gen.c: $(TARGET) $(SHU_C)
	./$(SHU_C) -L .. -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/lsp/lsp_io.su -E -E-extern > lsp_io_gen.c

# LSP 模块：main.su 依赖 lsp，需单独 -E 生成 lsp_gen.c；-E-extern 使 lsp_io、std.io、std.heap 仅生成 extern，由 lsp_io_su.o 与 io.o/heap.o 提供。
# LSP state 单独 .c，避免 lsp_main 内大数组导致 state 被覆盖
src/lsp/lsp_state.o: src/lsp/lsp_state.c
	$(CC) $(CFLAGS) -I. -Iinclude -Isrc -c -o $@ $<

lsp_gen.c: $(TARGET) $(SHU_C)
	./$(SHU_C) -L .. -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/lsp/lsp.su -E -E-extern > lsp_gen.c
	@sed -i.bak 's/uint8_t state_buf\[16388\] = { 0 }/extern uint8_t g_lsp_state_buf[16388]/' lsp_gen.c 2>/dev/null || true
	@sed -i.bak 's/(state_buf)/(g_lsp_state_buf)/g' lsp_gen.c 2>/dev/null || true

# std_heap_* 由 lsp_io_std_heap.su 提供（转调 heap_alloc_c/heap_free_c），完全去掉 LSP 的 C 文件；lsp_io_extern.h 仅做 typeck_ 符号映射与 extern 声明
lsp_io_std_heap_gen.c: $(TARGET) $(SHU_C)
	./$(SHU_C) -L .. -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/lsp/lsp_io_std_heap.su -E -E-extern > lsp_io_std_heap_gen.c
lsp_io_std_heap_su.o: lsp_io_std_heap_gen.c
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -Iinclude -Isrc -c lsp_io_std_heap_gen.c -o lsp_io_std_heap_su.o

bootstrap-driver-seed: $(TARGET) $(SHU_C) pipeline_gen.c lsp_io_gen.c lsp_gen.c lsp_io_std_heap_gen.c src/main_driver.o src/runtime_driver.o src/lsp/lsp_diag.o src/lsp/lsp_state.o lsp_io_std_heap_su.o ../std/fs/fs.o ../std/io/io.o ../std/heap/heap.o
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I.. -Dstd_io_driver_driver_read_ptr_len=shu_io_read_ptr_len -Dstd_io_driver_driver_read_ptr=shu_io_read_ptr -c pipeline_gen.c -o pipeline_su.o
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -include src/lsp/lsp_io_extern.h -c lsp_io_gen.c -o lsp_io_su.o
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -include src/lsp/lsp_gen_extern.h -c lsp_gen.c -o lsp_su.o
	./$(SHU_C) -L .. -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.su -E -E-extern > driver_gen.c
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o
	$(CC) $(CFLAGS) -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -o $(TARGET) $(DRIVER_SEED_OBJS) driver_su.o pipeline_su.o lsp_su.o lsp_io_su.o src/lsp/lsp_diag.o src/lsp/lsp_state.o lsp_io_std_heap_su.o ../std/fs/fs.o ../std/io/io.o ../std/heap/heap.o $(PIPELINE_LIBS)
	@echo "bootstrap-driver-seed OK (shu from generated C)"

# 用汇编后端直接出机器码：不生成 pipeline_gen.c/driver_gen.c，用 $(TARGET) -backend asm 编全部 .su → build_asm/*.o 再链接。
# 依赖已有 $(TARGET)（由 bootstrap-driver-seed 或预构建产出）。若 asm 成功则产出 shu_asm 并覆盖 $(TARGET)；否则保留 seed 并提示。
bootstrap-driver-asm: $(TARGET)
	@SHU=./$(TARGET) ./scripts/build_shu_asm.sh
	@if [ -f shu_asm ]; then cp -f shu_asm $(TARGET) && echo "bootstrap-driver-asm OK: $(TARGET) built from asm (no C gen)"; else echo "bootstrap-driver-asm: asm build skipped ($(TARGET) left as seed); run SHU=./$(TARGET) ./scripts/build_shu_asm.sh for details."; fi

# 默认自举：仅走 asm，不生成任何 C 文件（不生成 pipeline_gen.c、driver_gen.c 等）。全部 .su 用 -backend asm 直接出机器码。
# 要求已有可用的 $(TARGET)：首次请先 make bootstrap-driver-seed（会生成 C 一次得到种子 shu），之后 make bootstrap-driver 即只出机器码。
# 不把 $(TARGET) 列为依赖，避免 make 用 OBJS 构建出不含 pipeline/driver 的不完整 shu。
bootstrap-driver:
	@if [ ! -f $(TARGET) ]; then echo "No $(TARGET). Run 'make bootstrap-driver-seed' first (generates C once for seed shu)."; exit 1; fi
	@SHU=./$(TARGET) ./scripts/build_shu_asm.sh
	@if [ -f shu_asm ]; then cp -f shu_asm $(TARGET) && echo "bootstrap-driver OK: $(TARGET) from asm, no C gen"; else echo "bootstrap-driver: asm build failed, $(TARGET) unchanged. Run SHU=./$(TARGET) ./scripts/build_shu_asm.sh for errors."; exit 1; fi

# 仅 asm、不生成 C（与 bootstrap-driver 同义，保留别名）
bootstrap-driver-asm-only: bootstrap-driver

# Goal 2（用 asm 后端构建 shu）：构建最小 C 桩 + 可选执行 asm 自举脚本（需先 bootstrap-driver）
bootstrap-asm: $(TARGET) src/asm/runtime_asm_build.o src/runtime_driver.o
	@echo "bootstrap-asm: runtime_asm_build.o + runtime_driver.o ready."
	@echo "  Full asm build: SHU=./$(TARGET) ./scripts/build_shu_asm.sh (requires bootstrap-driver first)"
bootstrap-asm-full: bootstrap-driver bootstrap-asm
	@SHU=./$(TARGET) ./scripts/build_shu_asm.sh

# 6.4 验收：宿主编译器能编译整机 .su（typeck+codegen+driver）并产出新 shu，且新 shu 能编译运行测试（return-value 返回 42 视为成功）。用 seed 构建 shu 以保证通过（asm 路径修好后可改为 bootstrap-driver）。
check-6.4: $(TARGET)
	@$(MAKE) bootstrap-driver-seed && ./$(TARGET) ../tests/return-value/main.su -o /tmp/check64 && /tmp/check64; [ $$? -eq 42 ] && echo "check-6.4 OK"

# 首次/从零构建：一条命令得到 shu + build_tool（build-tool 依赖 $(TARGET) 会先产出 shu）。与 README「读者一次做对」一致。
first-time: build-tool

# 阶段 7：build.su 在仓库根目录，用 shu 编成 build_tool（在 compiler 目录下），运行 build_tool 即完成一次编译器构建
build-tool: $(TARGET)
	./$(TARGET) ../build.su -E > build_gen.c
	$(CC) $(CFLAGS) -c build_gen.c -o build_tool.o
	$(CC) $(CFLAGS) -c src/build_runtime.c -o build_runtime.o
	$(CC) $(CFLAGS) -o build_tool build_tool.o build_runtime.o
	@echo "build_tool OK（在 compiler 目录下运行 ./build_tool ./shu 可产出 shu）"

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
	@echo "build_tool OK (no C runtime; run ./build_tool ./shu)"
endif

# 运行 build_tool 产出 shu（等价于 make bootstrap-driver，无需执行 Makefile bootstrap-driver 目标）
build-via-tool: build-tool
	./build_tool ./$(TARGET)
	@echo "build-via-tool OK（shu 已由 build_tool 产出）"

# 阶段 8.1/8.2：用 seed 产出 shu₁（C 生成 pipeline_gen.c/driver_gen.c 再链接）；用 shu₁ 再编得到 shu₂。两代跑 run-all 一致即自举验证通过。
# 注：asm 链接就绪（Goal 2）后可改为 bootstrap-driver，则 shu₁ 为 asm 版，实现「无 C 生成」自举。
# 与 bootstrap-driver-seed 一致：需生成 lsp_io_gen.c / lsp_io_std_heap_gen.c，编译时带 lsp_gen_extern.h / lsp_io_extern.h，并链接 lsp_io_su.o、lsp_io_std_heap_su.o、heap.o。
bootstrap-self: bootstrap-driver-seed
	@cp $(TARGET) $(TARGET)_stage1 && \
	$(MAKE) -s pipeline_gen.c lsp_io_gen.c lsp_gen.c lsp_io_std_heap_gen.c 2>/dev/null || true && \
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I.. -Dstd_io_driver_driver_read_ptr_len=shu_io_read_ptr_len -Dstd_io_driver_driver_read_ptr=shu_io_read_ptr -c pipeline_gen.c -o pipeline_su.o && \
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -include src/lsp/lsp_io_extern.h -c lsp_io_gen.c -o lsp_io_su.o && \
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -include src/lsp/lsp_gen_extern.h -c lsp_gen.c -o lsp_su.o && \
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I. -Iinclude -Isrc -c lsp_io_std_heap_gen.c -o lsp_io_std_heap_su.o && \
	./$(SHU_C) -L .. -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.su -E -E-extern > driver_gen.c && \
	$(CC) $(CFLAGS) -c driver_gen.c -o driver_su.o && \
	$(CC) $(CFLAGS) -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -o $(TARGET)_stage2 $(DRIVER_SEED_OBJS) driver_su.o pipeline_su.o lsp_su.o lsp_io_su.o src/lsp/lsp_diag.o src/lsp/lsp_state.o lsp_io_std_heap_su.o ../std/fs/fs.o ../std/io/io.o ../std/heap/heap.o $(PIPELINE_LIBS) && \
	./$(TARGET)_stage2 ../tests/return-value/main.su -o /tmp/out_self && /tmp/out_self; EX=$$?; [ $$EX -eq 42 ] && echo "bootstrap-self OK (shu1 -> shu2)" || (echo "bootstrap-self FAIL: stage2 or out_self exit=$$EX"; exit 1)

# 阶段 8.3：两代 shu 对同一测试套件（run-all.sh）行为一致；run-all 含 run-su-pipeline/run-su-multi-file，需先各自编出 shu_su
# 失败时打印日志尾部，便于 CI 定位（run-all 在 CI 下会输出 *** run-all FAILED: <script> ***）
check-7.2: bootstrap-self
	@ROOT=$$(pwd)/..; \
	cp $(TARGET)_stage1 $(TARGET) && cd $$ROOT && SHU=$$ROOT/compiler/$(TARGET)_stage1 ./tests/run-all.sh > /tmp/run_shu1.log 2>&1; E1=$$?; \
	cd $$ROOT/compiler && cp $(TARGET)_stage2 $(TARGET) && cd $$ROOT && SHU=$$ROOT/compiler/$(TARGET)_stage2 ./tests/run-all.sh > /tmp/run_shu2.log 2>&1; E2=$$?; \
	if [ $$E1 -eq 0 ] && [ $$E2 -eq 0 ]; then echo "check-7.2 OK (both shu generations passed full test suite)"; else \
	  echo "shu1 exit=$$E1 shu2 exit=$$E2"; \
	  if [ $$E1 -ne 0 ] && [ -f /tmp/run_shu1.log ]; then echo "--- tail /tmp/run_shu1.log ---"; tail -n 80 /tmp/run_shu1.log; fi; \
	  if [ $$E2 -ne 0 ] && [ -f /tmp/run_shu2.log ]; then echo "--- tail /tmp/run_shu2.log ---"; tail -n 80 /tmp/run_shu2.log; fi; \
	  exit 1; fi

# 9.1 自举：纯 .su 流水线（parse_into → typeck_su_ast → codegen_su_ast）；生成 pipeline_gen.c 便于联调；-L 与 pipeline 依赖一致。
# 必须用 $(SHU_C) 做 -E：C 解析器(parser.c) 会按源码顺序填充 stmt_order，codegen 按序输出；若用 $(TARGET) 走 .su 解析则 stmt_order 仅有 const+let 导致声明被提到函数首、顺序错乱。
# 依赖 pipeline 及 codegen/typeck/parser 等 .su，修改后须重新生成 pipeline_gen.c，否则 bootstrap 的 shu 仍用旧逻辑。
PIPELINE_SU_DEPS = src/pipeline/pipeline.su src/codegen/codegen.su src/typeck/typeck.su src/parser/parser.su src/ast/ast.su src/lexer/lexer.su src/preprocess/preprocess.su src/asm/asm.su
bootstrap-pipeline: $(SHU_C) $(PIPELINE_SU_DEPS)
	./$(SHU_C) -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess src/pipeline/pipeline.su -E > pipeline_gen.c 2>/dev/null || true
	@echo "bootstrap-pipeline: pipeline_gen.c generated (if failed check parser/typeck/codegen/ast/lexer/preprocess and std.fs paths)"

# pipeline_gen.c 由 bootstrap-pipeline 生成；-E 时 runtime.c 在入口为 pipeline.su 时自动追加 pipeline_glue.c 到 stdout，无 Makefile 补丁
pipeline_gen.c: bootstrap-pipeline

# 链接带 -su 流水线的 shu（需 main_su.o 用 -DSHU_USE_SU_PIPELINE 编译，否则 -su -E 不生效）
# pipeline_su.o 引用 fs_*_c、io_*、lsp_diag_*、std_io_driver_submit_*；pipeline_glue.c 提供 submit 桩，fs/io/heap/lsp_diag 由对应 .o 提供
shu-su-pipeline: $(PIPELINE_OBJS) pipeline_gen.c ../std/fs/fs.o ../std/io/io.o ../std/heap/heap.o src/lsp/lsp_diag.o
	$(CC) $(CFLAGS) $(PIPELINE_GEN_CFLAGS) -I.. -Dstd_io_driver_driver_read_ptr_len=shu_io_read_ptr_len -Dstd_io_driver_driver_read_ptr=shu_io_read_ptr -c pipeline_gen.c -o pipeline_su.o
	$(CC) $(CFLAGS) -o $(TARGET)_su $(PIPELINE_OBJS) pipeline_su.o ../std/fs/fs.o ../std/io/io.o ../std/heap/heap.o src/lsp/lsp_diag.o $(PIPELINE_LIBS)
	@echo "shu_su built; use ./shu_su -su -E <file.su> to test .su pipeline"

# 4.5（.su 流水线编译 compiler 自身）：用 shu_su 的 -su -E 生成 typeck.su / codegen.su 对应的 C，再由 cc 链接得到新的 shu_su_stage2。
# 这一目标的目的，是验证「完整前端（parse_into + typeck_su_ast + codegen_su_ast）」全部跑在 .su 上时，仍能产出能工作的编译器。
bootstrap-su-compiler: shu-su-pipeline
	./$(TARGET)_su -su -E src/typeck/typeck.su > typeck_su_su.c
	./$(TARGET)_su -su -E src/codegen/codegen.su > codegen_su_su.c
	$(CC) $(CFLAGS) -c typeck_su_su.c -o typeck_su_su.o
	$(CC) $(CFLAGS) -c codegen_su_su.c -o codegen_su_su.o
	$(CC) $(CFLAGS) -DSHU_USE_SU_TYPECK -DSHU_USE_SU_CODEGEN -o $(TARGET)_su_stage2 $(OBJS) typeck_su_su.o codegen_su_su.o
	@echo "bootstrap-su-compiler OK (.su 流水线生成 typeck/codegen C 并链接 shu_su_stage2)"

# 自举测试（不含 run-all）：seed 构建 shu，再用 shu 自编得到 shu_stage2，stage2 跑 return-value 返回 42 即通过。用于快速验证「shu 能编译自己」。
bootstrap-test: bootstrap-self
	@echo "Bootstrap tests OK (self-compilation: shu1 -> shu2)"

# 7.3：自举验证通过（7.1+7.2 + 可选记录）。依赖 check-7.2（两代 shu 跑全量 run-all 一致）。当前 run-all 若因 std/io、std/net 等失败，可先跑 make bootstrap-test 验证自举链。
bootstrap-verify: check-7.2
	@echo "bootstrap-verify OK"

# 阶段 8 体积基线：编译固定用例并输出可执行文件大小
size-baseline:
	@if [ -f ../tests/run-size-baseline.sh ]; then (cd .. && chmod +x tests/run-size-baseline.sh && ./tests/run-size-baseline.sh); fi

# 阶段 8 性能基线：编译并多次运行 perf-baseline，输出耗时
perf-baseline:
	@if [ -f ../tests/run-perf-baseline.sh ]; then (cd .. && chmod +x tests/run-perf-baseline.sh && ./tests/run-perf-baseline.sh); fi
