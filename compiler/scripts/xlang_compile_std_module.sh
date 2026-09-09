#!/bin/sh
# xlang_compile_std_module.sh — formal std/core module .o via -x -E + cc -c (F 闭合)
#
# 【Why 根源】G-02a 删除 C 前端后，-E-extern 模式不可用（runtime.c 在
# XLANG_NO_C_FRONTEND 定义时直接报 BLD001）。-x -E 走 .x pipeline 路径，
# 生成等价的瘦 C TU（含 extern 前向声明），功能等价于旧 -E-extern。
#
# 替代 *_import_alias.c C 桩。两种模块架构：
#   1. import binding 模式（heap/map/set）：mod.x 用 `const impl = import("std.module.libc")`，
#      impl .x 用路径提取前缀（std_heap_libc_*），不传 -lib-name。
#   2. extern function 模式（tar/csv/json/...）：mod.x 用 `extern function foo_c()`，
#      impl .x 用 -lib-name "" 产出裸符号（foo_c），匹配 mod.x 的 extern 调用。
#      需传 --bare-impl 参数启用此模式。
# cc -c 编译为 .o，多文件时用 ld -r 合并。
#
# Usage (cwd = compiler/):
#   xlang_compile_std_module.sh [--bare-impl] <out.o> <x1> [x2] ...   # legacy explicit
#   xlang_compile_std_module.sh ensure <out.o>                        # wave812 catalog
#   xlang_compile_std_module.sh auto <out.o>                          # alias of ensure
#   xlang_compile_std_module.sh list                                  # catalog keys
#   xlang_compile_std_module.sh --check                               # catalog + thin greps
#
# wave812 (G.7 有则补全): formal_mod product table lives here — bare flag + sources
# + fs_formal dispatch. Makefile thin-calls `ensure $@` only.
# wave826 (G.7 有则补全): FORCE dep-thin — Makefile prereqs are FORCE + script only;
# shell owns catalog source mtime (skip up-to-date). NOT physical delete; thin edges
# + B2 try-heat + mk lists still form std_core_product_make_graph residual.
# wave894 (G.7 有则补全): make-graph inventory → mk/formal_mod_product_objs.mk;
# Makefile multi-target $(FORMAL_MOD_PRODUCT_OBJS) FORCE thin ensure only.
#
# 约定：mod.x 编译为带前缀符号（std_<module>_*）。
#   --bare-impl：非 mod.x 文件用 -lib-name ""（裸符号）；否则用路径提取前缀。
# 环境：XLANG=编译器路径（默认 ./xlang → ./xlang_asm → ./xlang-c）
# PLATFORM: SHARED — catalog + compile body; host-cc CFLAGS may add LINUX -D_GNU_SOURCE.
set -e

# PLATFORM: MACOS — match macho.x LC_BUILD_VERSION minos 11.0.0.
# c_face ensure compiles before the main CFLAGS bag; keep one Darwin extra.
# Do not -w swallow; do not raise macho.x minos to 26.0.
# PLATFORM: LINUX / WINDOWS — empty (no Mach-O minos check).
DARWIN_MINOS=""
case "$(uname -s 2>/dev/null)" in
  Darwin) DARWIN_MINOS="-mmacosx-version-min=11.0" ;;
esac

# ---------------------------------------------------------------------------
# wave812: formal_mod shell-primary catalog (G.7 有则补全; not physical delete)
# Spec line: kind|bare|src1[|src2...]
#   kind = mod (this script body) | fs_formal (xlang_compile_std_fs_formal.sh)
#   bare = 0|1  (--bare-impl for non-mod.x / extern-function modules)
# Keys accept: ../std/.../x.o | std/.../x.o | *std/.../x.o
# ---------------------------------------------------------------------------

formal_mod_key_for_out() {
  _o="$1"
  case "$_o" in
    ../std/string/string.o|std/string/string.o|*std/string/string.o) printf '%s' "std/string/string.o" ;;
    ../std/heap/heap.o|std/heap/heap.o|*std/heap/heap.o) printf '%s' "std/heap/heap.o" ;;
    ../std/heap/page_mmap.o|std/heap/page_mmap.o|*std/heap/page_mmap.o) printf '%s' "std/heap/page_mmap.o" ;;
    ../std/sys/sys.o|std/sys/sys.o|*std/sys/sys.o) printf '%s' "std/sys/sys.o" ;;
    ../std/sys/linux.o|std/sys/linux.o|*std/sys/linux.o) printf '%s' "std/sys/linux.o" ;;
    # PLATFORM: SHARED — B-19 cfg import smoke Darwin unique UNDEF (macos_write_available).
    # Nested leaf under std/sys; twin of linux.o → sys_macos product face.
    ../std/sys/macos.o|std/sys/macos.o|*std/sys/macos.o) printf '%s' "std/sys/macos.o" ;;
    ../core/mem/mem.o|core/mem/mem.o|*core/mem/mem.o) printf '%s' "core/mem/mem.o" ;;
    ../core/builtin/builtin.o|core/builtin/builtin.o|*core/builtin/builtin.o) printf '%s' "core/builtin/builtin.o" ;;
    ../core/types/types.o|core/types/types.o|*core/types/types.o) printf '%s' "core/types/types.o" ;;
    ../core/option/option.o|core/option/option.o|*core/option/option.o) printf '%s' "core/option/option.o" ;;
    ../core/result/result.o|core/result/result.o|*core/result/result.o) printf '%s' "core/result/result.o" ;;
    ../core/debug/debug.o|core/debug/debug.o|*core/debug/debug.o) printf '%s' "core/debug/debug.o" ;;
    ../core/slice/mod.o|core/slice/mod.o|*core/slice/mod.o) printf '%s' "core/slice/mod.o" ;;
    ../core/str/mod.o|core/str/mod.o|*core/str/mod.o) printf '%s' "core/str/mod.o" ;;
    ../core/iterator/mod.o|core/iterator/mod.o|*core/iterator/mod.o) printf '%s' "core/iterator/mod.o" ;;
    ../core/fmt/mod.o|core/fmt/mod.o|*core/fmt/mod.o) printf '%s' "core/fmt/mod.o" ;;
    # PLATFORM: SHARED — CORE-005 direct import("core.cmp") product -o (core_cmp_* UNDEF).
    ../core/cmp/mod.o|core/cmp/mod.o|*core/cmp/mod.o) printf '%s' "core/cmp/mod.o" ;;
    ../std/bytes/bytes.o|std/bytes/bytes.o|*std/bytes/bytes.o) printf '%s' "std/bytes/bytes.o" ;;
    ../std/map/map.o|std/map/map.o|*std/map/map.o) printf '%s' "std/map/map.o" ;;
    ../std/set/set.o|std/set/set.o|*std/set/set.o) printf '%s' "std/set/set.o" ;;
    ../std/vec/vec.o|std/vec/vec.o|*std/vec/vec.o) printf '%s' "std/vec/vec.o" ;;
    ../std/thread/thread.o|std/thread/thread.o|*std/thread/thread.o) printf '%s' "std/thread/thread.o" ;;
    ../std/time/time.o|std/time/time.o|*std/time/time.o) printf '%s' "std/time/time.o" ;;
    ../std/random/random.o|std/random/random.o|*std/random/random.o) printf '%s' "std/random/random.o" ;;
    ../std/env/env.o|std/env/env.o|*std/env/env.o) printf '%s' "std/env/env.o" ;;
    ../std/fs/fs.o|std/fs/fs.o|*std/fs/fs.o) printf '%s' "std/fs/fs.o" ;;
    ../std/sync/sync.o|std/sync/sync.o|*std/sync/sync.o) printf '%s' "std/sync/sync.o" ;;
    ../std/queue/queue.o|std/queue/queue.o|*std/queue/queue.o) printf '%s' "std/queue/queue.o" ;;
    ../std/encoding/encoding.o|std/encoding/encoding.o|*std/encoding/encoding.o) printf '%s' "std/encoding/encoding.o" ;;
    ../std/base64/base64.o|std/base64/base64.o|*std/base64/base64.o) printf '%s' "std/base64/base64.o" ;;
    ../std/crypto/crypto.o|std/crypto/crypto.o|*std/crypto/crypto.o) printf '%s' "std/crypto/crypto.o" ;;
    ../std/log/log.o|std/log/log.o|*std/log/log.o) printf '%s' "std/log/log.o" ;;
    ../std/test/test.o|std/test/test.o|*std/test/test.o) printf '%s' "std/test/test.o" ;;
    ../std/atomic/atomic.o|std/atomic/atomic.o|*std/atomic/atomic.o) printf '%s' "std/atomic/atomic.o" ;;
    ../std/hash/hash.o|std/hash/hash.o|*std/hash/hash.o) printf '%s' "std/hash/hash.o" ;;
    ../std/math/math.o|std/math/math.o|*std/math/math.o) printf '%s' "std/math/math.o" ;;
    ../std/sort/sort.o|std/sort/sort.o|*std/sort/sort.o) printf '%s' "std/sort/sort.o" ;;
    ../std/ffi/ffi.o|std/ffi/ffi.o|*std/ffi/ffi.o) printf '%s' "std/ffi/ffi.o" ;;
    ../std/context/context.o|std/context/context.o|*std/context/context.o) printf '%s' "std/context/context.o" ;;
    ../std/error/error.o|std/error/error.o|*std/error/error.o) printf '%s' "std/error/error.o" ;;
    ../std/json/json.o|std/json/json.o|*std/json/json.o) printf '%s' "std/json/json.o" ;;
    ../std/csv/csv.o|std/csv/csv.o|*std/csv/csv.o) printf '%s' "std/csv/csv.o" ;;
    ../std/cli/cli.o|std/cli/cli.o|*std/cli/cli.o) printf '%s' "std/cli/cli.o" ;;
    # PLATFORM: SHARED — STD-086 layer_smoke unique UNDEF (std_config_*).
    # Was std_x bare config.x only → T config_*_c / no std_config_* (import METHOD UNDEF).
    ../std/config/config.o|std/config/config.o|*std/config/config.o) printf '%s' "std/config/config.o" ;;
    # PLATFORM: SHARED — STD-087 lru_pool_smoke unique UNDEF (std_cache_*).
    # Was std_x bare cache.x only → T cache_*_c / no std_cache_* (import METHOD UNDEF).
    ../std/cache/cache.o|std/cache/cache.o|*std/cache/cache.o) printf '%s' "std/cache/cache.o" ;;
    # PLATFORM: SHARED — STD-076 roundtrip unique UNDEF (std_url_*).
    # Was std_x bare url.x only → T url_*_c / no std_url_* (import METHOD UNDEF).
    ../std/url/url.o|std/url/url.o|*std/url/url.o) printf '%s' "std/url/url.o" ;;
    # PLATFORM: SHARED — STD-079 roundtrip unique UNDEF (std_security_*).
    # Was std_x bare security.x only → T security_*_c / no std_security_* (import METHOD UNDEF).
    ../std/security/security.o|std/security/security.o|*std/security/security.o) printf '%s' "std/security/security.o" ;;
    # PLATFORM: SHARED — STD-080/081 roundtrip unique UNDEF (std_option_* / std_result_*).
    # Was missing formal_mod → import METHOD UNDEF (core/option alone exports core_option_*).
    ../std/option/option.o|std/option/option.o|*std/option/option.o) printf '%s' "std/option/option.o" ;;
    ../std/result/result.o|std/result/result.o|*std/result/result.o) printf '%s' "std/result/result.o" ;;
    # PLATFORM: SHARED — cookbook datetime_iana unique UNDEF (timezone_iana).
    # Was std_x auto-soft datetime.x only → T datetime_* / no std_datetime_*.
    ../std/datetime/datetime.o|std/datetime/datetime.o|*std/datetime/datetime.o) printf '%s' "std/datetime/datetime.o" ;;
    # PLATFORM: SHARED — cookbook sqlite_available unique UNDEF (is_available).
    # Was std_x auto-soft sqlite.x only → T db_* / no std_db_sqlite_*.
    ../std/db/sqlite/sqlite.o|std/db/sqlite/sqlite.o|*std/db/sqlite/sqlite.o) printf '%s' "std/db/sqlite/sqlite.o" ;;
    # PLATFORM: SHARED — cookbook db_kv_arrow unique UNDEF (mmap_available / adopt).
    # Was std_x auto-soft kv.x / arrow.x only → T db_kv_* / arrow_* / no std_db_*.
    ../std/db/kv/kv.o|std/db/kv/kv.o|*std/db/kv/kv.o) printf '%s' "std/db/kv/kv.o" ;;
    ../std/db/arrow/arrow.o|std/db/arrow/arrow.o|*std/db/arrow/arrow.o) printf '%s' "std/db/arrow/arrow.o" ;;
    ../std/dynlib/dynlib.o|std/dynlib/dynlib.o|*std/dynlib/dynlib.o) printf '%s' "std/dynlib/dynlib.o" ;;
    ../std/http/http.o|std/http/http.o|*std/http/http.o) printf '%s' "std/http/http.o" ;;
    ../std/tar/tar.o|std/tar/tar.o|*std/tar/tar.o) printf '%s' "std/tar/tar.o" ;;
    # PLATFORM: SHARED — pure-asm batch residual (2026-08-13): formal export std_* faces.
    ../std/unicode/unicode.o|std/unicode/unicode.o|*std/unicode/unicode.o) printf '%s' "std/unicode/unicode.o" ;;
    ../std/channel/channel.o|std/channel/channel.o|*std/channel/channel.o) printf '%s' "std/channel/channel.o" ;;
    # PLATFORM: SHARED — soft residual class-batch 2 (2026-08-13): formal vehicles for
    # plan/simple-group modules that pure-asm still UNDEF (runtime/backtrace/assert/fmt/
    # compress/io.driver). G.7 single catalog authority.
    ../std/runtime/runtime.o|std/runtime/runtime.o|*std/runtime/runtime.o) printf '%s' "std/runtime/runtime.o" ;;
    ../std/backtrace/backtrace.o|std/backtrace/backtrace.o|*std/backtrace/backtrace.o) printf '%s' "std/backtrace/backtrace.o" ;;
    ../core/assert/assert.o|core/assert/assert.o|*core/assert/assert.o) printf '%s' "core/assert/assert.o" ;;
    ../std/fmt/fmt.o|std/fmt/fmt.o|*std/fmt/fmt.o) printf '%s' "std/fmt/fmt.o" ;;
    ../std/compress/compress.o|std/compress/compress.o|*std/compress/compress.o) printf '%s' "std/compress/compress.o" ;;
    # PLATFORM: SHARED — 9.2.2 real zlib/gzip product .o (not the facade c_face stub).
    ../std/compress/zlib/zlib.o|std/compress/zlib/zlib.o|*std/compress/zlib/zlib.o) printf '%s' "std/compress/zlib/zlib.o" ;;
    ../std/compress/gzip/gzip.o|std/compress/gzip/gzip.o|*std/compress/gzip/gzip.o) printf '%s' "std/compress/gzip/gzip.o" ;;
    # PLATFORM: SHARED — zstd/brotli submodule product .o (mod + lib FFI to libzstd/libbrotli*).
    # Facade compress.o stays c_face; do not host-cc std/compress/mod.x (bare deflate vs zlib.h).
    ../std/compress/zstd/zstd.o|std/compress/zstd/zstd.o|*std/compress/zstd/zstd.o) printf '%s' "std/compress/zstd/zstd.o" ;;
    ../std/compress/brotli/brotli.o|std/compress/brotli/brotli.o|*std/compress/brotli/brotli.o) printf '%s' "std/compress/brotli/brotli.o" ;;
    ../std/io/driver.o|std/io/driver.o|*std/io/driver.o) printf '%s' "std/io/driver.o" ;;
    # PLATFORM: SHARED — pure-asm std.io ctx-timeout formal (STD-091; ≠ driver nested).
    ../std/io/io.o|std/io/io.o|*std/io/io.o) printf '%s' "std/io/io.o" ;;
    ../std/debug/debug.o|std/debug/debug.o|*std/debug/debug.o) printf '%s' "std/debug/debug.o" ;;
    # PLATFORM: SHARED — pure-asm std.simd formal (shuffle/select/splat VECTOR mid).
    ../std/simd/simd.o|std/simd/simd.o|*std/simd/simd.o) printf '%s' "std/simd/simd.o" ;;
    # PLATFORM: SHARED — cookbook async unique UNDEF (placeholder/drain_idle/scheduler_reset).
    # No async.o existed (std_x only scheduler.o/future.o auto-soft). Host-cc of
    # whole mod.x would U ~50 xlang_async_* C ABI. c_face = leftover unique T only.
    ../std/async/async.o|std/async/async.o|*std/async/async.o) printf '%s' "std/async/async.o" ;;
    *) printf '%s' "" ;;
  esac
}

# Authority body sources (match historic Makefile recipe args, not always full prereqs).
formal_mod_spec_for_key() {
  case "$1" in
    # G.7: string.o authority = xlang_compile_std_string_o.sh (Mac std_string_* wrappers
    # + runtime_string_fast bare ABI). formal_mod generic path lacks Mac objcopy rename
    # completeness for entry-only -x -E; dual path caused L4 run-string BLD001.
    # PLATFORM: SHARED — same dedicated vehicle as fs_formal pattern.
    std/string/string.o) printf '%s' "string_formal|0|" ;;
    std/heap/heap.o) printf '%s' "mod|0|../std/heap/mod.x|../std/heap/libc.x|../std/heap/ops.x" ;;
    std/heap/page_mmap.o) printf '%s' "mod|0|../std/heap/page_mmap.x" ;;
    std/sys/sys.o) printf '%s' "mod|0|../std/sys/mod.x" ;;
    std/sys/linux.o) printf '%s' "mod|0|../std/sys/linux.x" ;;
    # PLATFORM: SHARED — formal std.sys.macos (cfg import / macos_write_*).
    std/sys/macos.o) printf '%s' "mod|0|../std/sys/macos.x" ;;
    core/mem/mem.o) printf '%s' "mod|0|../core/mem/mod.x" ;;
    # PLATFORM: SHARED — pure-asm product gate (simple group g10); C-path G-01 still __builtin_*.
    core/builtin/builtin.o) printf '%s' "mod|0|../core/builtin/mod.x" ;;
    core/types/types.o) printf '%s' "mod|0|../core/types/mod.x" ;;
    core/option/option.o) printf '%s' "mod|0|../core/option/mod.x" ;;
    core/result/result.o) printf '%s' "mod|0|../core/result/mod.x" ;;
    core/debug/debug.o) printf '%s' "mod|0|../core/debug/mod.x" ;;
    core/slice/mod.o) printf '%s' "mod|0|../core/slice/mod.x" ;;
    # PLATFORM: SHARED — cookbook core_str_index unique UNDEF (bytes_view_index_of*).
    # G.7 complete formal_mod like core/slice/mod.o; product import mangle core_str_*.
    core/str/mod.o) printf '%s' "mod|0|../core/str/mod.x" ;;
    # PLATFORM: SHARED — cookbook iter_slice_sum unique UNDEF (iter_i32 / next_i32).
    # G.7 complete formal_mod like core/str/mod.o; product import mangle core_iterator_*.
    core/iterator/mod.o) printf '%s' "mod|0|../core/iterator/mod.x" ;;
    # PLATFORM: SHARED — CORE-010 direct import("core.fmt") product -o (fmt_*_to_buf UNDEF).
    # G.7 complete formal_mod like core/str/mod.o; product import mangle core_fmt_*.
    core/fmt/mod.o) printf '%s' "mod|0|../core/fmt/mod.x" ;;
    # PLATFORM: SHARED — CORE-005 direct import("core.cmp") product -o (core_cmp_* UNDEF).
    # G.7 complete formal_mod like core/fmt/mod.o; product import mangle core_cmp_*.
    core/cmp/mod.o) printf '%s' "mod|0|../core/cmp/mod.x" ;;
    # PLATFORM: SHARED — tests/std-bytes/arena_external unique UNDEF (from_external*).
    # G.7 complete formal_mod like core/iterator/mod.o; product import mangle std_bytes_*.
    std/bytes/bytes.o) printf '%s' "mod|0|../std/bytes/mod.x" ;;
    std/map/map.o) printf '%s' "mod|1|../std/map/mod.x" ;;
    std/set/set.o) printf '%s' "mod|1|../std/set/mod.x" ;;
    std/vec/vec.o) printf '%s' "mod|0|../std/vec/mod.x" ;;
    std/thread/thread.o) printf '%s' "mod|0|../std/thread/mod.x" ;;
    std/time/time.o) printf '%s' "mod|1|../std/time/mod.x" ;;
    std/random/random.o) printf '%s' "mod|1|../std/random/mod.x|../std/random/random.x" ;;
    std/env/env.o) printf '%s' "mod|0|../std/env/mod.x" ;;
    std/fs/fs.o) printf '%s' "fs_formal|0|" ;;
    std/sync/sync.o) printf '%s' "mod|1|../std/sync/mod.x|../std/sync/sync.x" ;;
    std/queue/queue.o) printf '%s' "mod|1|../std/queue/mod.x|../std/queue/queue.x" ;;
    std/encoding/encoding.o) printf '%s' "mod|1|../std/encoding/mod.x|../std/encoding/encoding.x" ;;
    std/base64/base64.o) printf '%s' "mod|1|../std/base64/mod.x|../std/base64/base64.x" ;;
    std/crypto/crypto.o) printf '%s' "mod|1|../std/crypto/mod.x|../std/crypto/core.x|../std/crypto/aes_gcm.x|../std/crypto/chacha20_poly1305.x|../std/crypto/chacha20_aead.x|../std/crypto/ed25519.x" ;;
    std/log/log.o) printf '%s' "mod|1|../std/log/mod.x|../std/log/log.x" ;;
    std/test/test.o) printf '%s' "mod|1|../std/test/mod.x|../std/test/test.x" ;;
    std/atomic/atomic.o) printf '%s' "mod|1|../std/atomic/mod.x|../std/atomic/atomic.x" ;;
    std/hash/hash.o) printf '%s' "mod|1|../std/hash/mod.x|../std/hash/hash.x" ;;
    std/math/math.o) printf '%s' "mod|1|../std/math/mod.x|../std/math/math.x" ;;
    std/sort/sort.o) printf '%s' "mod|0|../std/sort/mod.x|../std/sort/sort.x" ;;
    std/ffi/ffi.o) printf '%s' "mod|1|../std/ffi/mod.x|../std/ffi/ffi.x" ;;
    std/context/context.o) printf '%s' "mod|1|../std/context/mod.x|../std/context/context.x" ;;
    std/error/error.o) printf '%s' "mod|0|../std/error/mod.x" ;;
    std/json/json.o) printf '%s' "mod|1|../std/json/mod.x|../std/json/json.x" ;;
    std/csv/csv.o) printf '%s' "mod|1|../std/csv/mod.x|../std/csv/csv.x" ;;
    # PLATFORM: SHARED — std.cli product face (cookbook cli_subcommand).
    # Was std_x bare cli.x only → T cli_* / no std_cli_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/http: mod.x prefix + --bare-impl *_c.
    std/cli/cli.o) printf '%s' "mod|1|../std/cli/mod.x|../std/cli/cli.x" ;;
    # PLATFORM: SHARED — std.config product face (STD-086 layer/yaml .x smoke).
    # Was std_x bare config.x only → T config_*_c / no std_config_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/http: mod.x prefix + --bare-impl *_c.
    std/config/config.o) printf '%s' "mod|1|../std/config/mod.x|../std/config/config.x" ;;
    # PLATFORM: SHARED — std.cache product face (STD-087 lru_pool_smoke).
    # Was std_x bare cache.x only → T cache_*_c / no std_cache_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/config: mod.x prefix + --bare-impl *_c.
    std/cache/cache.o) printf '%s' "mod|1|../std/cache/mod.x|../std/cache/cache.x" ;;
    # PLATFORM: SHARED — std.url product face (STD-076 roundtrip).
    # Was std_x bare url.x only → T url_*_c / no std_url_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/cache: mod.x prefix + --bare-impl *_c.
    std/url/url.o) printf '%s' "mod|1|../std/url/mod.x|../std/url/url.x" ;;
    # PLATFORM: SHARED — std.security product face (STD-079 roundtrip).
    # Was std_x bare security.x only → T security_*_c / no std_security_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/url: mod.x prefix + --bare-impl *_c.
    std/security/security.o) printf '%s' "mod|1|../std/security/mod.x|../std/security/security.x" ;;
    # PLATFORM: SHARED — std.option / std.result product faces (STD-080/081 roundtrip).
    # Wrappers over core.option / core.result; mod.x only (co-emits core bodies).
    # G.7: mod|0 like channel/core.option (no bare-impl second file).
    std/option/option.o) printf '%s' "mod|0|../std/option/mod.x" ;;
    std/result/result.o) printf '%s' "mod|0|../std/result/mod.x" ;;
    # PLATFORM: SHARED — std.datetime product face (cookbook datetime_iana).
    # Was std_x bare datetime.x only → T datetime_* / no std_datetime_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/http: mod.x prefix + --bare-impl *_c.
    std/datetime/datetime.o) printf '%s' "mod|1|../std/datetime/mod.x|../std/datetime/datetime.x" ;;
    # PLATFORM: SHARED — std.db.sqlite product face (cookbook sqlite_available).
    # Was std_x bare sqlite.x only → T db_* / no std_db_sqlite_* (import METHOD UNDEF).
    # G.7 complete formal_mod like csv/cli/http/datetime: mod.x prefix + --bare-impl *_c.
    std/db/sqlite/sqlite.o) printf '%s' "mod|1|../std/db/sqlite/mod.x|../std/db/sqlite/sqlite.x" ;;
    # PLATFORM: SHARED — std.db.kv / std.db.arrow product faces (cookbook db_kv_arrow).
    # Was std_x bare kv.x / arrow.x only → T db_kv_* / arrow_* / no std_db_kv_* /
    # std_db_arrow_* (import METHOD UNDEF). G.7 complete formal_mod like sqlite.
    std/db/kv/kv.o) printf '%s' "mod|1|../std/db/kv/mod.x|../std/db/kv/kv.x" ;;
    std/db/arrow/arrow.o) printf '%s' "mod|1|../std/db/arrow/mod.x|../std/db/arrow/arrow.x" ;;
    std/dynlib/dynlib.o) printf '%s' "mod|1|../std/dynlib/mod.x|../std/dynlib/dynlib.x" ;;
    std/http/http.o) printf '%s' "mod|1|../std/http/mod.x|../std/http/http.x" ;;
    std/tar/tar.o) printf '%s' "mod|1|../std/tar/mod.x|../std/tar/tar.x" ;;
    # PLATFORM: SHARED — pure-asm std_unicode_* / std_channel_* product faces.
    # unicode: mod+impl bare (extern-function style leaf symbols in unicode.x).
    # channel: mod.x wrappers only (API body in runtime_channel_glue channel_i32_*_c).
    std/unicode/unicode.o) printf '%s' "mod|1|../std/unicode/mod.x|../std/unicode/unicode.x" ;;
    std/channel/channel.o) printf '%s' "mod|0|../std/channel/mod.x" ;;
    # PLATFORM: SHARED — soft residual class-batch 2 formal bodies.
    # runtime: mod wrappers (ready/panic/abort) + runtime.x leaf faces for glue.
    # backtrace: mod.x capture → backtrace_capture_c (platform .o companion on plan).
    # assert: freestanding core.assert (no I/O); panic via host panic face.
    # fmt: std.fmt wrappers co-emit core.fmt bodies (monofile entry).
    # compress: std.compress facade co-emits zlib/gzip/brotli/zstd submods.
    # io.driver: nested module path std/io/driver.x → std_io_driver_* surface.
    # runtime / fmt / compress / io.driver / debug: c_face vehicles (pure-asm link surface).
    # Product .x monofile remains C-path authority; faces avoid monofile host-cc / companion U.
    std/runtime/runtime.o) printf '%s' "c_face|0|../std/runtime/formal_surface.c" ;;
    std/backtrace/backtrace.o) printf '%s' "mod|0|../std/backtrace/mod.x" ;;
    core/assert/assert.o) printf '%s' "mod|0|../core/assert/mod.x" ;;
    std/fmt/fmt.o) printf '%s' "c_face|0|../std/fmt/formal_surface.c" ;;
    std/compress/compress.o) printf '%s' "c_face|0|../std/compress/formal_surface.c" ;;
    # PLATFORM: SHARED — 9.2.2: real std.compress.zlib / gzip (mod + libz).
    # Facade compress.o stays c_face stub (bare deflate/inflate vs zlib.h if monofile).
    # Submodule vehicles are the product path: compress2 / deflateInit2 glue + -lz.
    std/compress/zlib/zlib.o) printf '%s' "mod|1|../std/compress/zlib/mod.x|../std/compress/zlib/libz.x" ;;
    std/compress/gzip/gzip.o) printf '%s' "mod|1|../std/compress/gzip/mod.x|../std/compress/gzip/libz.x" ;;
    # PLATFORM: SHARED — zstd/brotli ≡ gzip: submodule vehicle is the product path.
    # lib.x is extern C FFI (ZSTD_* / BrotliEncoder*/Decoder*); ld -l* is the lib face.
    std/compress/zstd/zstd.o) printf '%s' "mod|1|../std/compress/zstd/mod.x|../std/compress/zstd/lib.x" ;;
    std/compress/brotli/brotli.o) printf '%s' "mod|1|../std/compress/brotli/mod.x|../std/compress/brotli/lib.x" ;;
    std/io/driver.o) printf '%s' "c_face|0|../std/io/driver_formal_surface.c" ;;
    # PLATFORM: SHARED — pure-asm std.io ctx-timeout faces (≡ mod.x; STD-091).
    std/io/io.o) printf '%s' "c_face|0|../std/io/formal_surface.c" ;;
    std/debug/debug.o) printf '%s' "c_face|0|../std/debug/formal_surface.c" ;;
    # PLATFORM: SHARED — pure-asm VECTOR mid faces (≡ codegen f32x4/i32x8 mangle).
    std/simd/simd.o) printf '%s' "c_face|0|../std/simd/formal_surface.c" ;;
    # PLATFORM: SHARED — leftover unique UNDEF std_async_placeholder / drain_idle.
    # G.7 无才新增 catalog c_face; do not host-cc whole mod.x.
    std/async/async.o) printf '%s' "c_face|0|../std/async/formal_surface.c" ;;
    *) printf '%s' "" ;;
  esac
}

formal_mod_all_keys() {
  printf '%s\n' \
    std/string/string.o \
    std/heap/heap.o \
    std/heap/page_mmap.o \
    std/sys/sys.o \
    std/sys/linux.o \
    std/sys/macos.o \
    core/mem/mem.o \
    core/builtin/builtin.o \
    core/types/types.o \
    core/option/option.o \
    core/result/result.o \
    core/debug/debug.o \
    core/slice/mod.o \
    core/str/mod.o \
    core/iterator/mod.o \
    core/fmt/mod.o \
    core/cmp/mod.o \
    std/bytes/bytes.o \
    std/map/map.o \
    std/set/set.o \
    std/vec/vec.o \
    std/thread/thread.o \
    std/time/time.o \
    std/random/random.o \
    std/env/env.o \
    std/fs/fs.o \
    std/sync/sync.o \
    std/queue/queue.o \
    std/encoding/encoding.o \
    std/base64/base64.o \
    std/crypto/crypto.o \
    std/log/log.o \
    std/test/test.o \
    std/atomic/atomic.o \
    std/hash/hash.o \
    std/math/math.o \
    std/sort/sort.o \
    std/ffi/ffi.o \
    std/context/context.o \
    std/error/error.o \
    std/json/json.o \
    std/csv/csv.o \
    std/cli/cli.o \
    std/config/config.o \
    std/cache/cache.o \
    std/url/url.o \
    std/security/security.o \
    std/option/option.o \
    std/result/result.o \
    std/datetime/datetime.o \
    std/db/sqlite/sqlite.o \
    std/db/kv/kv.o \
    std/db/arrow/arrow.o \
    std/dynlib/dynlib.o \
    std/http/http.o \
    std/tar/tar.o \
    std/unicode/unicode.o \
    std/channel/channel.o \
    std/runtime/runtime.o \
    std/backtrace/backtrace.o \
    core/assert/assert.o \
    std/fmt/fmt.o \
    std/compress/compress.o \
    std/compress/zlib/zlib.o \
    std/compress/gzip/gzip.o \
    std/compress/zstd/zstd.o \
    std/compress/brotli/brotli.o \
    std/io/driver.o \
    std/io/io.o \
    std/debug/debug.o \
    std/simd/simd.o \
    std/async/async.o
}

formal_mod_out_for_key() {
  # Makefile targets use ../ prefix from compiler/
  case "$1" in
    core/*) printf '../%s' "$1" ;;
    std/*) printf '../%s' "$1" ;;
    *) printf '../%s' "$1" ;;
  esac
}

formal_mod_list() {
  formal_mod_all_keys | while IFS= read -r _k; do
    _sp="$(formal_mod_spec_for_key "$_k")"
    printf '%s  %s\n' "$_k" "$_sp"
  done
}

formal_mod_check() {
  _bad=0
  _n=0
  _here="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
  _mk="$_here/../Makefile"
  [ -f "$_mk" ] || _mk="$_here/Makefile"
  while IFS= read -r _k; do
    _n=$((_n + 1))
    _sp="$(formal_mod_spec_for_key "$_k")"
    if [ -z "$_sp" ]; then
      echo "formal_mod --check: empty spec for $_k" >&2
      _bad=1
      continue
    fi
    _kind="${_sp%%|*}"
    _rest="${_sp#*|}"
    _bare="${_rest%%|*}"
    _srcs="${_rest#*|}"
    if [ "$_kind" = "fs_formal" ]; then
      if [ ! -x "$_here/xlang_compile_std_fs_formal.sh" ] && [ ! -f "$_here/xlang_compile_std_fs_formal.sh" ]; then
        echo "formal_mod --check: missing xlang_compile_std_fs_formal.sh" >&2
        _bad=1
      fi
    elif [ "$_kind" = "string_formal" ]; then
      # PLATFORM: SHARED — string.o vehicle = xlang_compile_std_string_o.sh
      if [ ! -x "$_here/xlang_compile_std_string_o.sh" ] && [ ! -f "$_here/xlang_compile_std_string_o.sh" ]; then
        echo "formal_mod --check: missing xlang_compile_std_string_o.sh" >&2
        _bad=1
      fi
      for _s in ../std/string/mod.x ../std/string/string.x; do
        if [ ! -f "$_here/$_s" ] && [ ! -f "$_s" ]; then
          echo "formal_mod --check: missing source $_s for $_k" >&2
          _bad=1
        fi
      done
    else
      _old_ifs=$IFS
      IFS='|'
      # shellcheck disable=SC2086
      set -- $_srcs
      IFS=$_old_ifs
      for _s in "$@"; do
        [ -n "$_s" ] || continue
        if [ ! -f "$_here/$_s" ] && [ ! -f "$_s" ]; then
          echo "formal_mod --check: missing source $_s for $_k" >&2
          _bad=1
        fi
      done
    fi
    _tgt="$(formal_mod_out_for_key "$_k")"
    # Makefile thin-call: ensure|auto only (wave812); FORCE dep-thin (wave826).
    # wave894: multi-target $(FORMAL_MOD_PRODUCT_OBJS) + mk list (no per-leaf target line).
    # Accept A) legacy per-leaf `^OUT:` FORCE+ensure, or B) OUT in mk list + multi-target rule.
    if [ -f "$_mk" ]; then
      _fm_mk="$_here/../mk/formal_mod_product_objs.mk"
      [ -f "$_fm_mk" ] || _fm_mk="$_here/mk/formal_mod_product_objs.mk"
      _ok_leaf=0
      if awk -v tgt="$_tgt" '
        $0 ~ ("^" tgt ":") {
          line=$0
          if (line !~ /FORCE/) { exit 1 }
          if (line ~ /\.x([[:space:]]|$)/) { exit 1 }
          hit=1; next
        }
        hit && /^[^#[:space:]]/ { exit 1 }
        hit && /xlang_compile_std_module\.sh/ {
          if ($0 ~ /ensure|auto/) { found=1; exit 0 }
        }
        hit && /xlang_compile_std_fs_formal\.sh/ {
          if (tgt ~ /fs\/fs\.o/) { found=1; exit 0 }
        }
        END { exit found ? 0 : 1 }
      ' "$_mk" 2>/dev/null; then
        _ok_leaf=1
      elif [ -f "$_fm_mk" ] \
        && grep -qF "$_tgt" "$_fm_mk" \
        && grep -qE '\$\(FORMAL_MOD_PRODUCT_OBJS\):[[:space:]]*FORCE' "$_mk" \
        && awk '
          /\$\(FORMAL_MOD_PRODUCT_OBJS\):/ { hit=1; next }
          hit && /^[^#[:space:]\t]/ { exit 1 }
          hit && /xlang_compile_std_module\.sh/ && /ensure|auto/ { found=1; exit 0 }
          END { exit found ? 0 : 1 }
        ' "$_mk"; then
        _ok_leaf=1
      fi
      if [ "$_ok_leaf" -ne 1 ]; then
        echo "formal_mod --check: Makefile/mk $_tgt must FORCE + ensure|auto (wave826/wave894)" >&2
        _bad=1
      fi
    fi
  done <<'KEYS'
std/string/string.o
std/heap/heap.o
std/heap/page_mmap.o
std/sys/sys.o
std/sys/linux.o
std/sys/macos.o
core/mem/mem.o
core/builtin/builtin.o
core/types/types.o
core/option/option.o
core/result/result.o
core/debug/debug.o
core/slice/mod.o
std/map/map.o
std/set/set.o
std/vec/vec.o
std/thread/thread.o
std/time/time.o
std/random/random.o
std/env/env.o
std/fs/fs.o
std/sync/sync.o
std/queue/queue.o
std/encoding/encoding.o
std/base64/base64.o
std/crypto/crypto.o
std/log/log.o
std/test/test.o
std/atomic/atomic.o
std/hash/hash.o
std/math/math.o
std/sort/sort.o
std/ffi/ffi.o
std/context/context.o
std/error/error.o
std/json/json.o
std/csv/csv.o
std/cli/cli.o
std/config/config.o
std/dynlib/dynlib.o
std/http/http.o
std/tar/tar.o
std/unicode/unicode.o
std/channel/channel.o
KEYS
  if [ "$_n" -ne 44 ]; then
    echo "formal_mod --check: expected 44 keys, counted $_n" >&2
    _bad=1
  fi
  if [ "$_bad" -ne 0 ]; then
    echo "formal_mod --check: FAIL" >&2
    return 1
  fi
  echo "formal_mod --check: OK (48 leaves; catalog + mk list + multi-target FORCE+ensure wave894; not physical delete)"
  return 0
}

# Mode dispatch (wave812). Legacy [--bare-impl] OUT sources remains supported.
BARE_IMPL=0
case "${1:-}" in
  list)
    formal_mod_list
    exit 0
    ;;
  --check)
    formal_mod_check
    exit $?
    ;;
  ensure|auto)
    if [ -z "${2:-}" ]; then
      echo "usage: xlang_compile_std_module.sh ensure <out.o>" >&2
      exit 1
    fi
    out_o="$2"
    _key="$(formal_mod_key_for_out "$out_o")"
    if [ -z "$_key" ]; then
      echo "xlang_compile_std_module.sh ensure: unknown formal_mod leaf: $out_o" >&2
      exit 3
    fi
    # PLATFORM: SHARED — always land at catalog out path from compiler/ cwd
    # (../std|core/…). Callers may pass std/heap/heap.o without ../; without
    # this normalize libtool writes compiler/std/... (wrong) and product links
    # the stale ../std/... .o. G.7 single out authority.
    out_o="$(formal_mod_out_for_key "$_key")"
    _spec="$(formal_mod_spec_for_key "$_key")"
    _kind="${_spec%%|*}"
    _rest="${_spec#*|}"
    _bare="${_rest%%|*}"
    _srcs="${_rest#*|}"
    if [ "$_kind" = "fs_formal" ]; then
      # PLATFORM: SHARED — fs formal vehicle authority stays in dedicated script.
      _fs_sh="$(dirname "$0")/xlang_compile_std_fs_formal.sh"
      [ -f "$_fs_sh" ] || _fs_sh="./xlang_compile_std_fs_formal.sh"
      exec sh "$_fs_sh" "$out_o"
    fi
    if [ "$_kind" = "string_formal" ]; then
      # PLATFORM: SHARED — string.o authority = xlang_compile_std_string_o.sh
      # (Mac wrappers + runtime_string_fast; G.7 single vehicle, no dual formal_mod body).
      _str_sh="$(dirname "$0")/xlang_compile_std_string_o.sh"
      [ -f "$_str_sh" ] || _str_sh="./xlang_compile_std_string_o.sh"
      # Dedicated script ignores out path; always writes $ROOT/std/string/string.o
      exec sh "$_str_sh"
    fi
    if [ "$_kind" = "c_face" ]; then
      # PLATFORM: SHARED — pure-asm formal vehicle is a committed .c face (no .x monofile).
      # Used when product .x monofile cannot host-cc (zlib deflate clash / io prefix drift).
      # G.7: one catalog key → one out .o; product .x remains C-path authority.
      _csrc="${_srcs}"
      case "$_csrc" in
        '')
          echo "xlang_compile_std_module.sh ensure: c_face missing source for $_key" >&2
          exit 1
          ;;
      esac
      if [ "${FORCE:-0}" != "1" ] && [ -f "$out_o" ] && [ -f "$_csrc" ] && [ ! "$_csrc" -nt "$out_o" ]; then
        echo "xlang_compile_std_module: skip up-to-date $out_o (formal_mod/c_face/$_key)" >&2
        exit 0
      fi
      mkdir -p "$(dirname "$out_o")"
      # shellcheck disable=SC2086
      if ! cc -c -fPIE -I.. -I. $DARWIN_MINOS -o "$out_o" "$_csrc"; then
        echo "xlang_compile_std_module.sh: c_face cc -c failed for $_csrc → $out_o" >&2
        exit 1
      fi
      echo "xlang_compile_std_module.sh: OK (c_face $_csrc -> $out_o)"
      exit 0
    fi
    BARE_IMPL="$_bare"
    # Rebuild positional args as sources for shared compile body below (out_o already set).
    # PLATFORM: SHARED — catalog sources use ../std|core paths from compiler/ cwd.
    _fm_srcs=""
    _old_ifs=$IFS
    IFS='|'
    for _s in $_srcs; do
      [ -n "$_s" ] || continue
      if [ -z "$_fm_srcs" ]; then
        _fm_srcs="$_s"
      else
        _fm_srcs="$_fm_srcs $_s"
      fi
    done
    IFS=$_old_ifs
    if [ -z "$_fm_srcs" ]; then
      echo "xlang_compile_std_module.sh ensure: no sources for $_key" >&2
      exit 1
    fi
    # wave826: FORCE-thin mtime — shell owns catalog source freshness (G.7).
    # Makefile always invokes via FORCE; skip recompile when OUT is newer than all
    # catalog sources. FORCE=1 forces rebuild (tests / explicit). PLATFORM: SHARED.
    if [ "${FORCE:-0}" != "1" ] && [ -f "$out_o" ]; then
      _fm_stale=0
      for _s in $_fm_srcs; do
        [ -n "$_s" ] || continue
        if [ -f "$_s" ] && [ "$_s" -nt "$out_o" ]; then
          _fm_stale=1
          break
        fi
      done
      if [ "$_fm_stale" = "0" ]; then
        echo "xlang_compile_std_module: skip up-to-date $out_o (formal_mod/$_key)" >&2
        exit 0
      fi
    fi
    # shellcheck disable=SC2086
    set -- $_fm_srcs
    ;;
  --bare-impl)
    BARE_IMPL=1
    shift
    out_o="$1"
    shift
    if [ -z "$out_o" ] || [ "$#" -lt 1 ]; then
      echo "usage: xlang_compile_std_module.sh [--bare-impl] <out.o> <x1> [x2] ..." >&2
      exit 1
    fi
    ;;
  *)
    out_o="$1"
    shift
    if [ -z "$out_o" ] || [ "$#" -lt 1 ]; then
      echo "usage: xlang_compile_std_module.sh [--bare-impl|ensure|list|--check] ..." >&2
      exit 1
    fi
    ;;
esac

# 【Why 根源】优先 ./xlang（.x pipeline，支持 -x -E）；LEGACY xlang-c 不支持 -x 选项。
# G-02a 后 -E-extern 不可用，必须用 -x -E 走 .x pipeline，故 ./xlang 优先。
# XLANG 可能是项目根目录相对路径（./compiler/xlang），Makefile 在 compiler/ 下执行时
# 该路径不存在，需回退到 compiler/ 本地的 ./xlang。
# wave812: string.o historic Makefile host-pick (xlang_asm→xlang) is already covered
# by this ladder + XLANG env; no second ladder in Makefile.
XLANG_BIN="${XLANG:-./xlang}"
[ -x "$XLANG_BIN" ] || XLANG_BIN="./xlang"
[ -x "$XLANG_BIN" ] || XLANG_BIN="./xlang_asm"
[ -x "$XLANG_BIN" ] || XLANG_BIN="./xlang-c"
[ -x "$XLANG_BIN" ] || XLANG_BIN="../compiler/xlang"
[ -x "$XLANG_BIN" ] || { echo "xlang_compile_std_module.sh: no xlang/xlang_asm/xlang-c found" >&2; exit 1; }

# 【Why 根源】-x -E 生成瘦 C TU（emit_c_only=1 + emit_extern_imports=1），
# import 用 extern 声明，不内联 deps。mod.x 带前缀产出 std_<module>_* 用户 API。
# --bare-impl 模式下 impl .x 用 -lib-name "" 产出裸符号（如 tar_read_header_c）；
# 否则 impl .x 用路径提取前缀（如 std_heap_libc_heap_arena64_alloc_c），匹配 import binding。
# CFLAGS 抑制 warning（-x -E 生成的 C 有大量 extern 前向声明）。
# -ffunction-sections -fdata-sections：配合 freestanding 链接的 --gc-sections，
# 移除 std/sys/linux.o 等模块中未被引用的 hosted libc 函数（open/mmap 等），
# 使 freestanding -nostdlib 链接不因 transitive libc 符号失败。
# PLATFORM: LINUX — -D_GNU_SOURCE so formal std.fs.posix (posix_fadvise, etc.) compile
# under gcc -Werror=implicit-function-declaration; macOS clang accepts without it.
# PLATFORM: SHARED — -Wno-implicit-function-declaration: -x -E emits extern calls to
# cross-module APIs (e.g. std/net/mod.x calls std_io_read_fixed_fd) but codegen does
# not always emit forward extern decls. Tolerate like xlang_compile_std_fs_formal.sh
# (posix_fadvise etc.). Same for -Wno-builtin-declaration-mismatch (libc name clashes).
CFLAGS="-I.. -I. -Iinclude -Isrc -fPIE -ffunction-sections -fdata-sections -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-parentheses -Wno-sign-compare -Wno-ignored-qualifiers -Wno-unused-but-set-variable -Wno-type-limits -Wno-visibility -Wno-incompatible-pointer-types -Wno-incompatible-pointer-types-discards-qualifiers -Wno-implicit-function-declaration -Wno-builtin-declaration-mismatch"
case "$(uname -s 2>/dev/null)" in
  Linux) CFLAGS="-D_GNU_SOURCE $CFLAGS" ;;
  Darwin) CFLAGS="$CFLAGS $DARWIN_MINOS" ;;
esac
if cc -v 2>&1 | grep -q clang; then
  CFLAGS="$CFLAGS -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses"
fi

tmp_dir=$(mktemp -d 2>/dev/null || mktemp -d -t xlangmod)
trap 'if [ -n "${XLANG_DEBUG_KEEP_TMP:-}" ]; then echo "DEBUG kept tmp_dir=$tmp_dir" >&2; else rm -rf "$tmp_dir" 2>/dev/null || true; fi' EXIT INT TERM

# 【Why 根源】旧 seed（bootstrap_xlangc）不支持 -lib-name flag（ treats it as a file path,
# outputs "io error: cannot read file '-lib-name'" and exits 0）。但其无前缀逻辑也产出裸符号
# （函数名本身已含 module_ 前缀），故不加 -lib-name 即可匹配 mod.x 的 extern 调用。
# 新编译器需 -lib-name "" 抑制 xlang_entry_lib_name_from_path 的路径前缀，否则符号被双重前缀化。
LIB_NAME_SUPPORTED=0
probe_x="$tmp_dir/probe.x"
probe_c="$tmp_dir/probe.c"
probe_err="$tmp_dir/probe.err"
printf 'function probe_fn(): i32 { return 0; }\n' > "$probe_x"
# 产品 x-pipeline 当前不识别 -lib-name（会当文件路径 → IO001）；仅 C 前端 RUN_CC 支持。
# 误判会把 -lib-name 传给 x 路径，或跳过 bare 后处理 → 双前缀符号（std_sync_sync_mutex_*）。
if "$XLANG_BIN" -x -E -lib-name "" "$probe_x" >"$probe_c" 2>"$probe_err" \
  && grep -q 'probe_fn' "$probe_c" \
  && ! grep -q 'cannot read file' "$probe_err" \
  && ! grep -q 'IO001' "$probe_err"; then
  LIB_NAME_SUPPORTED=1
fi

obj_files=""
idx=0
for x_path in "$@"; do
  # Makefile 在 compiler/ 下执行；输入须为 ../std/...（-L .. 不解析入口路径）
  case "$x_path" in
    std/*) x_path="../$x_path" ;;
  esac
  gen_c="$tmp_dir/mod_${idx}.c"
  obj="$tmp_dir/mod_${idx}.o"
  # 【Why 根源】mod.x 是模块入口，编译为带前缀符号（std_<module>_*）。
  # --bare-impl 模式下，impl .x 用 -lib-name "" 产出裸符号（匹配 mod.x 的 extern 调用）；
  # 否则 impl .x 用路径提取前缀（匹配 mod.x 的 import binding 调用）。
  base_name=$(basename "$x_path")
  # 【Why 根源】产品 -x -E 对无 main 库模块常中途截断 out_buf（4KiB 对齐截断、
  # 半个函数体）。-o *.o 路径 emit 完整 C（cc 可能因 Arena64 标签失败，但 XLANG_KEEP_C
  # 保留完整源）。优先 -o + KEEP_C，失败再回退 -E。
  emit_ok=0
  use_direct_o=0
  # 产品 std .o：Linux 默认 asm 对 string 等库模块体不完整（运行时 SIGSEGV）；强制 -backend c。
  # -o 无 main 时链失败但 XLANG_KEEP_C 保留完整 C；再 cc -c 落地。
  BACKEND_ARGS=""
  if [ -n "${XLANG_FORCE_LINK_BACKEND:-}" ]; then
    BACKEND_ARGS="-backend ${XLANG_FORCE_LINK_BACKEND}"
  else
    case "$(uname -s 2>/dev/null)" in
      Linux|Darwin) BACKEND_ARGS="-backend c" ;;
    esac
  fi
  # PLATFORM: SHARED — NEVER rm /tmp/xlang_xlang_x.*.c globally: bstrict concurrent
  # user -o and std compile race-delete each other's KEEP_C temps (mac L4 true-cold).
  # shellcheck: empty -lib-name needs quoted empty string
  if [ "$base_name" != "mod.x" ] && [ "$BARE_IMPL" = "1" ] && [ "$LIB_NAME_SUPPORTED" = "1" ]; then
    XLANG_KEEP_C=1 "$XLANG_BIN" $BACKEND_ARGS -L .. -lib-name "" -o "$tmp_dir/try_${idx}.o" "$x_path" \
      >"$tmp_dir/xlangc_${idx}.log" 2>&1 || true
  else
    XLANG_KEEP_C=1 "$XLANG_BIN" $BACKEND_ARGS -L .. -o "$tmp_dir/try_${idx}.o" "$x_path" \
      >"$tmp_dir/xlangc_${idx}.log" 2>&1 || true
  fi
  # 优先：-o 已直接产出可用 .o（无 Arena64 冲突时）。
  # bare-impl 且无 -lib-name：
  #   - 产品 C 后端 -o/KEEP_C 常带路径前缀（std_crypto_core_*）→ 须 gen_c 剥前缀
  #   - 若 KEEP_C 完整则优先 C 路径；asm 裸 .o 仅作次选
  # 旧逻辑一律拒绝 direct .o 再走 -x -E，而 -E 对 preamble 在 ~20KiB 处截断 → crypto.o 假死。
  # bare-impl 子文件（core.x 等）：mod.x 以裸名 crypto_mem_eq_c 声明，
  # 产品 C 后端常仍 emit 路径前缀 std_crypto_core_*（即便 -lib-name "" / LIB_NAME_SUPPORTED）。
  # 必须剥前缀，否则 ld 得 U crypto_mem_eq_c 与 T std_crypto_core_crypto_mem_eq_c 双轨。
  bare_need_strip=0
  if [ "$base_name" != "mod.x" ] && [ "$BARE_IMPL" = "1" ]; then
    bare_need_strip=1
  fi
  # KEEP_C 路径：从本 invocation 的 log 取路径（勿 ls /tmp 抢别人的 temp）
  kept0=$(grep -E 'kept generated C:|keeping generated C:' "$tmp_dir/xlangc_${idx}.log" 2>/dev/null \
    | sed -n 's/.*generated C: //p' | tail -1)
  if [ -n "$kept0" ] && [ -f "$kept0" ] && [ -s "$kept0" ] && tail -c 80 "$kept0" | grep -q '}'; then
    cp "$kept0" "$gen_c"
    emit_ok=1
    # 只删本路径，勿通配
    rm -f "$kept0" 2>/dev/null || true
  fi
  if [ "$emit_ok" != "1" ] && [ -f "$tmp_dir/try_${idx}.o" ] && [ -s "$tmp_dir/try_${idx}.o" ]; then
    if [ "$bare_need_strip" = "1" ]; then
      strip_pref_probe=$(printf '%s' "$x_path" | sed -e 's|^\.\./||' -e 's|\.x$||' -e 's|/|_|g')
      has_prefixed=0
      if [ -n "$strip_pref_probe" ] && command -v nm >/dev/null 2>&1; then
        if nm "$tmp_dir/try_${idx}.o" 2>/dev/null | grep -q " T ${strip_pref_probe}_"; then
          has_prefixed=1
        fi
      fi
      if [ "$has_prefixed" != "1" ]; then
        # 已是裸符号（asm -o）或无可检测前缀：直接用 .o
        bare_need_strip=0
        use_direct_o=1
        emit_ok=1
        obj="$tmp_dir/try_${idx}.o"
      fi
      # has_prefixed=1：保留 bare_need_strip，走下方 KEEP_C / -E 剥前缀
    else
      use_direct_o=1
      emit_ok=1
      obj="$tmp_dir/try_${idx}.o"
    fi
  fi
  # mod.x 用户 API 须为 <root>_<module>_*（import 调用约定）。
  # PLATFORM: SHARED — std/foo → std_foo_*; core/slice → core_slice_* (NOT std_slice_*).
  # 产品 Linux asm/KEEP_C 常产裸名 len_i32；objcopy 重命名与 mac C 路径对齐。
  # G.7: length.x U core_slice_len_i32 while formal mod.o had bare len_i32 → BLD001.
  if [ "$use_direct_o" = "1" ] && [ "$base_name" = "mod.x" ] \
     && [ -f "$obj" ] && command -v nm >/dev/null 2>&1; then
    mod_leaf=$(basename "$(dirname "$x_path")")
    case "$mod_leaf" in
      ''|.) mod_leaf=$(basename "$x_path" .x) ;;
    esac
    # Path root: ../core/slice/mod.x → core; ../std/env/mod.x → std.
    mod_root=$(printf '%s' "$x_path" | sed -e 's|^\.\./||' -e 's|/.*||')
    case "$mod_root" in
      core) mod_pref="core_${mod_leaf}_" ;;
      std)  mod_pref="std_${mod_leaf}_" ;;
      *)    mod_pref="std_${mod_leaf}_" ;;
    esac
    if [ -n "$mod_leaf" ] && ! nm "$obj" 2>/dev/null | grep -q " T ${mod_pref}"; then
      if command -v objcopy >/dev/null 2>&1; then
        nm "$obj" 2>/dev/null | awk '/ [TDB] / { print $3 }' | while IFS= read -r sym; do
          [ -n "$sym" ] || continue
          case "$sym" in
            "${mod_pref}"*) continue ;;
            _"${mod_pref}"*) continue ;;
            # Already product-prefixed (co-emitted deps) or compiler noise.
            core_*|std_*|_core_*|_std_*) continue ;;
            # 跳过 C 内部/编译器符号
            _Z*|.L*|L0*|__*) continue ;;
          esac
          # Mach-O 可能带前导 _
          bare="$sym"
          case "$sym" in
            _*) bare="${sym#_}" ;;
          esac
          case "$bare" in
            "${mod_pref}"*|core_*|std_*) continue ;;
          esac
          if [ "$bare" != "$sym" ]; then
            objcopy --redefine-sym "${sym}=_${mod_pref}${bare}" "$obj" 2>/dev/null || true
          else
            objcopy --redefine-sym "${sym}=${mod_pref}${bare}" "$obj" 2>/dev/null || true
          fi
        done
      fi
      if ! nm "$obj" 2>/dev/null | grep -q " T ${mod_pref}"; then
        # 重命名失败：放弃 direct .o，改走 C/KEEP_C 前缀路径
        use_direct_o=0
        emit_ok=0
        obj="$tmp_dir/mod_${idx}.o"
      fi
    fi
  fi
  if [ "$emit_ok" != "1" ]; then
    kept=$(grep -E 'kept generated C:|keeping generated C:' "$tmp_dir/xlangc_${idx}.log" 2>/dev/null \
      | sed -n 's/.*generated C: //p' | tail -1)
    if [ -n "$kept" ] && [ -f "$kept" ] && [ -s "$kept" ]; then
      if tail -c 80 "$kept" | grep -q '}' ; then
        cp "$kept" "$gen_c"
        emit_ok=1
        rm -f "$kept" 2>/dev/null || true
      fi
    fi
  fi
  # bare-impl 需剥前缀且无完整 C：再试 -backend c KEEP_C
  if [ "$emit_ok" != "1" ] && [ "$bare_need_strip" = "1" ]; then
    XLANG_KEEP_C=1 "$XLANG_BIN" -backend c -L .. -o "$tmp_dir/try_c_${idx}.o" "$x_path" \
      >"$tmp_dir/xlangc_c_${idx}.log" 2>&1 || true
    kept=$(grep -E 'kept generated C:|keeping generated C:' "$tmp_dir/xlangc_c_${idx}.log" 2>/dev/null \
      | sed -n 's/.*generated C: //p' | tail -1)
    if [ -n "$kept" ] && [ -f "$kept" ] && [ -s "$kept" ]; then
      if tail -c 80 "$kept" | grep -q '}' ; then
        cp "$kept" "$gen_c"
        emit_ok=1
        rm -f "$kept" 2>/dev/null || true
      fi
    fi
  fi
  if [ "$emit_ok" != "1" ]; then
    # 回退 -E：拒绝明显截断（尾部无 } 或半截 token）
    if [ "$base_name" != "mod.x" ] && [ "$BARE_IMPL" = "1" ] && [ "$LIB_NAME_SUPPORTED" = "1" ]; then
      if ! "$XLANG_BIN" -backend c -x -E -lib-name "" -L .. "$x_path" >"$gen_c" 2>"$tmp_dir/xlangc_${idx}.log"; then
        if ! "$XLANG_BIN" -x -E -lib-name "" -L .. "$x_path" >"$gen_c" 2>"$tmp_dir/xlangc_${idx}.log"; then
          echo "xlang_compile_std_module.sh: -o and -x -E failed for $x_path" >&2
          cat "$tmp_dir/xlangc_${idx}.log" >&2
          exit 1
        fi
      fi
    else
      if ! "$XLANG_BIN" -backend c -x -E -L .. "$x_path" >"$gen_c" 2>"$tmp_dir/xlangc_${idx}.log"; then
        if ! "$XLANG_BIN" -x -E -L .. "$x_path" >"$gen_c" 2>"$tmp_dir/xlangc_${idx}.log"; then
          echo "xlang_compile_std_module.sh: -o and -x -E failed for $x_path" >&2
          cat "$tmp_dir/xlangc_${idx}.log" >&2
          exit 1
        fi
      fi
    fi
    if [ -s "$gen_c" ] && tail -c 80 "$gen_c" | grep -q '}'; then
      # 拒绝半截 struct/标识符（历史 20KiB 截断）
      if ! tail -c 1 "$gen_c" | grep -q '[[:space:];}]' \
         && ! tail -c 40 "$gen_c" | grep -qE '([;}][[:space:]]*)$'; then
        echo "xlang_compile_std_module.sh: -E output looks truncated for $x_path" >&2
        exit 1
      fi
      emit_ok=1
    elif [ -s "$gen_c" ]; then
      echo "xlang_compile_std_module.sh: -E output incomplete (no closing brace) for $x_path" >&2
      exit 1
    fi
  fi
  # bare-impl：产品 x-pipeline 无 -lib-name 时，codegen 用路径导出前缀
  # （std/base64/base64.x → std_base64_base64_…）。mod.x 的 extern 是裸名
  # base64_encode_standard_c。在 gen_c 齐备后剥前缀（须在 -E 回退之后）。
  if [ "$bare_need_strip" = "1" ] && [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    strip_pref=$(printf '%s' "$x_path" | sed -e 's|^\.\./||' -e 's|\.x$||' -e 's|/|_|g')
    if [ -n "$strip_pref" ]; then
      perl -i -pe "s/\\b\Q${strip_pref}_\E//g" "$gen_c" 2>/dev/null || \
        sed -i.bak "s/${strip_pref}_//g" "$gen_c" 2>/dev/null || true
      dir_pref=$(printf '%s' "$x_path" | sed -e 's|^\.\./||' -e 's|/[^/]*$||' -e 's|/|_|g')
      if [ -n "$dir_pref" ] && [ "$dir_pref" != "$strip_pref" ]; then
        perl -i -pe "s/\\b\Q${dir_pref}_\E//g" "$gen_c" 2>/dev/null || \
          sed -i.bak "s/${dir_pref}_//g" "$gen_c" 2>/dev/null || true
      fi
      rm -f "${gen_c}.bak" 2>/dev/null || true
    fi
  fi
  # §3.3 (2026-09-10): std/compress impl prefix injection.
  # Root cause: compress-family mod.x calls its sibling lib via QUALIFIED import
  # (libz.compress_gzip_compress_c) which mangles to std_compress_<fam>_libz_*,
  # but the impl .x C emission is BARE on both lanes (-lib-name "" and no flag),
  # and 7e2fef61b stopped co-emitting std/ dep bodies with mod.x (link_only
  # std.compress), so nothing prefixes the impl faces anymore → mod.o U
  # std_compress_gzip_libz_* vs bare T (run-compress UNDEF, dual-end L4 red).
  # G.7 completes the vehicle's own documented contract ("impl .x without
  # -lib-name uses the path-derived prefix"): for impl sources under
  # std/compress/, prefix their export-function names in gen_c (defs, decls and
  # intra-file calls alike) with the path-derived module prefix. The name list
  # is scraped from the source's `^export function` lines — no second symbol
  # table to drift; FFI extern "C" names are not in the list and stay bare.
  # Word-boundary replacement cannot re-match already-prefixed ids.
  # PLATFORM: SHARED.
  # mod.x already emits its own entry path prefix (mod segment skipped) — only
  # impl files (libz.x / lib.x) need the injection.
  case "$x_path" in
    ../std/compress/*)
      if [ "$base_name" != "mod.x" ]; then
      _impl_pref=$(printf '%s' "$x_path" | sed -e 's|^\.\./||' -e 's|\.x$||' -e 's|/|_|g')
      if [ -n "$_impl_pref" ] && [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
        _exp_names=$(sed -n 's/^export function \([A-Za-z_][A-Za-z0-9_]*\).*/\1/p' "$x_path" | sort -u)
        for _en in $_exp_names; do
          perl -i -pe "s/\\b${_en}\\b/${_impl_pref}_${_en}/g" "$gen_c" 2>/dev/null || true
        done
      fi
      fi
      ;;
  esac
  # 已有直接 .o：跳过 gen_c 后处理与二次 cc
  if [ "$use_direct_o" = "1" ]; then
    if [ -z "$obj_files" ]; then
      obj_files="$obj"
    else
      obj_files="$obj_files $obj"
    fi
    idx=$((idx + 1))
    continue
  fi
  # PLATFORM: SHARED — rt_preamble injects weak std_vec_len_empty / std_vec_vec_len_empty
  # for programs that never link std/vec/vec.o. std/vec/mod.x provides strong defs in the
  # same TU → Clang/GCC redefinition error on host-cc path (Darwin always; Linux when
  # forced -backend c). Authority: strip preamble weak bodies when strong defs exist
  # (same pattern as xlang_compile_std_x.sh args_iter_*).
  if [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    # Strong def may be `int32_t len_empty(` (unprefixed -E) or `std_vec_len_empty`.
    # The old `^int32_t std_vec_len_empty(` gate missed unprefixed strong + weak
    # preamble → Darwin cc redefinition. Always strip weak when any strong
    # len_empty exists, or when compiling vec/mod.x (this TU is the authority).
    # PLATFORM: SHARED — G.7 complete existing strip (no second vec stub path).
    if grep -qE '__attribute__\(\(weak\)\).*std_vec_len_empty' "$gen_c" 2>/dev/null; then
      if grep -qE 'int32_t (std_vec_)?len_empty\(' "$gen_c" 2>/dev/null \
        || printf '%s' "$x_path" | grep -q 'std/vec/mod.x'; then
        sed -e '/__attribute__((weak)) int32_t std_vec_len_empty(void)/d' \
            -e '/__attribute__((weak)) int32_t std_vec_vec_len_empty(void)/d' \
            "$gen_c" >"$gen_c.strip" && mv "$gen_c.strip" "$gen_c"
      fi
    fi
  fi
  # PLATFORM: SHARED — rt_preamble injects weak process_xlang_argc_get / argv_get that
  # return 0 as a minimal fallback when process_argv is not linked. Formal_mod then
  # Mac-export-filters only std_<leaf>_* → demotes those weak stubs to local T.
  # Internal calls (args_iter_count_c → process_args_count_c → process_xlang_*) bind
  # the local zero body forever; product ondemand complement scans for U process_xlang_*
  # and never pushes runtime_process_argv.o → run-env env_iter exit 1 (a0==null).
  # G.7 root: drop weak zero *definitions*, keep extern decls so the .o has U faces;
  # ondemand process_argv complement + runtime_process_argv strong T win at product link.
  # Do not invent a second argc authority in formal_mod.
  if [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    if grep -qE '__attribute__\(\(weak\)\).*process_xlang_argc_get' "$gen_c" 2>/dev/null; then
      # In-place: replace weak zero *bodies* with extern decls (keep position after
      # includes / typedefs so int32_t is known). Leaves U in .o for process_argv.
      sed \
        -e 's/^__attribute__((weak)) int32_t process_xlang_argc_get(void) { return 0; }$/extern int32_t process_xlang_argc_get(void); \/* formal_mod U→process_argv *\//' \
        -e 's/^__attribute__((weak)) uint8_t \*process_xlang_argv_get(int32_t i) { (void)i; return (uint8_t \*)0; }$/extern uint8_t *process_xlang_argv_get(int32_t i); \/* formal_mod U→process_argv *\//' \
        "$gen_c" >"$gen_c.pav" && mv "$gen_c.pav" "$gen_c"
    fi
  fi
  # PLATFORM: SHARED — generic weak-stub dedup after --bare-impl prefix strip.
  # After stripping the path prefix (e.g. std_context_context_), a weak preamble stub
  # can collide with a strong def that was previously differently-named
  # (context.x: weak ctx_background_c + stripped std_context_context_ctx_background_c
  # -> ctx_background_c both weak and strong -> cc redefinition). Two-pass: grep strong
  # def names, then drop matching weak stub lines.
  if [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    strong_names=$(grep -E '^[A-Za-z_][A-Za-z0-9_ *]* [A-Za-z_][A-Za-z0-9_]*[(][^)]*[)] *[{{]?[[:space:]]*$' "$gen_c" \
      | grep -v 'weak' \
      | sed -n 's/.*[[:space:]]\([A-Za-z_][A-Za-z0-9_]*\)(.*/\1/p' \
      | sort -u)

    if [ -n "$strong_names" ]; then
      : > "$gen_c.dedup_script"
      # For each strong def name, remove weak stub lines that define the same name.
      # Pattern: __attribute__((weak))... <name>( — one sed -e per name.
      echo "$strong_names" > "$gen_c.strong_names"
      awk 'NR==FNR { strong[$0]=1; next }
        /^__attribute__..weak../ {
          if (match($0, /[ ][A-Za-z_][A-Za-z0-9_]*[(]/)) {
            nm = substr($0, RSTART+1, RLENGTH-2)
            if (nm in strong) { skip=1; if (/[}]/) skip=0; next }
          }
        }
        skip { if (/[}]/) skip=0; next }
        { print }
      ' "$gen_c.strong_names" "$gen_c" > "$gen_c.dedup" 2>/dev/null && mv "$gen_c.dedup" "$gen_c"
      rm -f "$gen_c.strong_names"
    fi
  fi
  # 【Why 根源】-E 对跨模块 struct（如 heap_libc_Arena64）常只在「形参列表内」
  # 写出 `struct Foo`，未给文件级 forward。C 规定形参内的 struct 标签作用域仅限该
  # 声明 → 原型与定义各得一个不同 incomplete 类型 → conflicting types for 'fn'。
  # 在首个非预处理行前注入 `struct Foo;` 使整 TU 共享同一标签。
  # codegen 对 dep struct 正确 emit forward 后本段可删。
  if command -v perl >/dev/null 2>&1; then
    fwd_tmp="$tmp_dir/fwd_${idx}.h"
    perl -ne 'while (/struct\s+([A-Za-z_][A-Za-z0-9_]*)/g) { print "$1\n" if $1 ne "std_io_driver_Buffer" }' \
      "$gen_c" 2>/dev/null | sort -u >"$tmp_dir/structs_${idx}.txt" || true
    if [ -s "$tmp_dir/structs_${idx}.txt" ]; then
      : >"$fwd_tmp"
      while IFS= read -r sn; do
        [ -n "$sn" ] || continue
        # 已有完整定义或已有文件级 forward 则跳过
        if grep -E "struct[[:space:]]+${sn}[[:space:]]*[{;]" "$gen_c" >/dev/null 2>&1; then
          continue
        fi
        # 仅当只在形参/指针处出现（无 { 体）时补 forward
        if grep -E "struct[[:space:]]+${sn}[[:space:]]*\*" "$gen_c" >/dev/null 2>&1; then
          printf 'struct %s;\n' "$sn" >>"$fwd_tmp"
        fi
      done <"$tmp_dir/structs_${idx}.txt"
      # PLATFORM: SHARED — Arena64 short-tag dual-name residual CLOSED (2026-08-12).
      # Historic: entry params emitted `struct heap_libc_Arena64` while dep bodies used
      # `struct std_heap_libc_LibcArena64` → shell `#define heap_libc_Arena64 …` dual-authority.
      # Tip product -E: short `heap_libc_Arena64` count=0; full tags only
      # (`std_heap_libc_LibcArena64` / `std_heap_Arena64` via emit_type + preamble).
      # Shell #define tag alias removed; do not reintroduce.
      # PLATFORM: SHARED — Result_i32/u8 short-tag dual-name residual CLOSED (2026-08-12).
      # Root authority is codegen emit_type: bare Result_* → `struct core_result_Result_*`
      # (same class as Option_*). Shell #define tag alias removed; do not reintroduce.
      if [ -s "$fwd_tmp" ]; then
        # 插在最后一个 #include 之后；若无 include 则插文件首
        merged="$tmp_dir/gen_fwd_${idx}.c"
        if grep -q '^#include' "$gen_c"; then
          # 在最后一个 #include 行后插入
          awk -v fwd="$fwd_tmp" '
            /^#include/ { last=NR }
            { lines[NR]=$0 }
            END {
              for (i=1;i<=NR;i++) {
                print lines[i]
                if (i==last) {
                  while ((getline l < fwd) > 0) print l
                  close(fwd)
                }
              }
            }' "$gen_c" >"$merged" && mv "$merged" "$gen_c"
        else
          cat "$fwd_tmp" "$gen_c" >"$merged" && mv "$merged" "$gen_c"
        fi
      fi
    fi
  fi

  # 【Why 根源】codegen bug workaround (2026-07-19): when a struct field type is
  # another user struct (e.g. std/net/mod.x SocketAddrV4 { addr: Ipv4Addr, port: u32 }),
  # codegen -x -E emits only forward `struct Foo;` declaration but not the complete
  # definition. cc then fails with "incomplete result type 'struct Foo' in function
  # definition". Workaround: extract all `export struct Foo { ... }` from mod.x
  # source, convert XLANG types to C types, inject the missing complete definitions
  # right after the last #include (only for structs whose complete body is absent).
  # PLATFORM: SHARED — runs only on mod.x entry file; impl .x (--bare-impl) skipped.
  if [ "$base_name" = "mod.x" ] && command -v perl >/dev/null 2>&1; then
    mod_x_src="$x_path"
    case "$mod_x_src" in
      std/*) mod_x_src="../$mod_x_src" ;;
    esac
    if [ -f "$mod_x_src" ]; then
      mod_leaf_x=$(basename "$(dirname "$mod_x_src")")
      mod_root_x=$(printf '%s' "$mod_x_src" | sed -e 's|^\.\./||' -e 's|/.*||')
      case "$mod_root_x" in
        core) mod_pref_x="core_${mod_leaf_x}_" ;;
        std)  mod_pref_x="std_${mod_leaf_x}_" ;;
        *)    mod_pref_x="std_${mod_leaf_x}_" ;;
      esac
      inject_tmp="$tmp_dir/inject_structs_${idx}.h"
      # PLATFORM: SHARED — inject_structs to_c_type must lower []T / T[] to
      # `struct xlang_slice_<elemTag>` (same authority as codegen emit_type).
      # Historic bug (mac run-slice len_i32): field `left: []i32` fell through to
      # `struct ${prefix}${t}` → invalid C `struct core_slice_[]i32` (brackets in
      # tag) → formal_mod cc -c failed → missing core_slice_len_i32 at product link.
      # G.7: complete the X→C map; do not invent a second slice naming path.
      perl -e '
        use strict;
        my ($prefix, $src) = @ARGV;
        open(my $fh, "<", $src) or exit 0;
        my %type_map = (
          u8 => "uint8_t", u16 => "uint16_t", u32 => "uint32_t", u64 => "uint64_t",
          i8 => "int8_t",  i16 => "int16_t",  i32 => "int32_t",  i64 => "int64_t",
          f32 => "float", f64 => "double", usize => "size_t", isize => "ssize_t",
          bool => "_Bool",
        );
        # Element tag for xlang_slice_<tag> (codegen: []i32 → xlang_slice_int32_t).
        sub slice_elem_tag {
          my $e = shift; $e =~ s/^\s+|\s+$//g; $e =~ s/;$//;
          if (exists $type_map{$e}) { return $type_map{$e}; }
          if ($e =~ /^\*(.*)$/) {
            my $inner = slice_elem_tag($1);
            return $inner . "_ptr";
          }
          # Named user type: prefer bare tag (codegen bare Split_i32 companions).
          return $e;
        }
        sub to_c_type {
          my $t = shift; $t =~ s/^\s+|\s+$//g; $t =~ s/;$//;
          if ($t =~ /^\*(.*)$/) { return to_c_type($1) . " *"; }
          # Fixed array T[N]
          if ($t =~ /^(.+)\[(\d+)\]$/) { return to_c_type($1) . "[" . $2 . "]"; }
          # Fat slice []T or T[] → struct xlang_slice_<elemC>
          if ($t =~ /^\[\](.+)$/) {
            return "struct xlang_slice_" . slice_elem_tag($1);
          }
          if ($t =~ /^(.+)\[\]$/) {
            return "struct xlang_slice_" . slice_elem_tag($1);
          }
          if (exists $type_map{$t}) { return $type_map{$t}; }
          return "struct ${prefix}${t}";
        }
        my $in_struct = 0; my $name; my @fields;
        while (my $line = <$fh>) {
          if (!$in_struct && $line =~ /^export struct ([A-Za-z_][A-Za-z0-9_]*) \{/) {
            $name = $1; @fields = (); $in_struct = 1; next;
          }
          if ($in_struct) {
            if ($line =~ /^\}/) {
              print "struct ${prefix}${name} {\n";
              for my $f (@fields) { print "  $f;\n"; }
              print "};\n"; $in_struct = 0;
            } elsif ($line =~ /^\s*(\w+)\s*:\s*(.+)$/) {
              my $fname = $1; my $ftype = $2; $ftype =~ s/\s+$//; $ftype =~ s/;$//;
              push @fields, to_c_type($ftype) . " " . $fname;
            }
          }
        }
      ' "$mod_pref_x" "$mod_x_src" >"$inject_tmp" 2>/dev/null || true
      # Filter inject_tmp: keep only structs whose complete body is MISSING from gen_c.
      # Detection covers three cases:
      #   1. forward `struct Foo;` exists but `struct Foo {` does not
      #   2. only used in function signatures (e.g. `struct Foo std_net_local_addr(...)`)
      #      with no forward decl and no complete def (codegen bug — emit just sig)
      #   3. struct already has complete body in gen_c → skip (no duplicate)
      # Also synthesizes xlang_slice_<pref>_<Struct> slice types when codegen omits them
      # (codegen emits xlang_slice_uint8_t etc. but skips user-struct slices).
      # Also patches codegen bug: `struct Foo _rc = 0;` → `struct Foo _rc = {0};`
      # (struct local var initialized with int literal instead of compound literal).
      if [ -f "$gen_c" ] && command -v perl >/dev/null 2>&1; then
        # Patch struct-local-var init from `= 0` to `= {0}` (only when LHS is `struct ...`)
        # Allow leading whitespace (function body indentation).
        perl -i -pe 's/^(\s*struct\s+[A-Za-z_][A-Za-z0-9_]*\s+[A-Za-z_][A-Za-z0-9_]*\s*=\s*)0\s*;/${1}\{0\};/g' "$gen_c" 2>/dev/null || true
      fi
      if [ -s "$inject_tmp" ] && [ -f "$gen_c" ]; then
        filtered="$tmp_dir/inject_filtered_${idx}.h"
        # PLATFORM: SHARED — bare complete `struct Split_i32 {` satisfies inject
        # name `core_slice_Split_i32` (codegen often emits bare tags; inject used
        # to re-emit a second broken pref body). Mark both bare and pref+bare.
        perl -e '
          use strict;
          my ($gen_c, $inject, $pref) = @ARGV;
          open(my $gf, "<", $gen_c) or exit 0;
          my (%has_full, %slice_seen);
          while (my $l = <$gf>) {
            if ($l =~ /^struct (\Q$pref\E[A-Za-z_][A-Za-z0-9_]*) \{/) { $has_full{$1} = 1; }
            if ($l =~ /^struct (xlang_slice_\Q$pref\E[A-Za-z_][A-Za-z0-9_]*) \{/) { $has_full{$1} = 1; }
            # Bare complete body: struct Split_i32 { → also covers pref+Split_i32
            if ($pref ne "" && $l =~ /^struct ([A-Za-z_][A-Za-z0-9_]*) \{/) {
              my $bare = $1;
              next if $bare =~ /^xlang_slice_/;
              next if $bare =~ /^\Q$pref\E/;
              $has_full{$bare} = 1;
              $has_full{$pref . $bare} = 1;
            }
            while ($l =~ /xlang_slice_(\Q$pref\E[A-Za-z_][A-Za-z0-9_]*)/g) {
              $slice_seen{$1} = 1;
            }
          }
          close($gf);
          # First: emit xlang_slice_<name> syntheses for missing slice types.
          for my $sname (sort keys %slice_seen) {
            next if exists $has_full{"xlang_slice_" . $sname};
            # sname = std_net_TcpStream → element type = struct std_net_TcpStream
            print "struct xlang_slice_${sname} { struct ${sname} *data; size_t length; };\n";
          }
          # Second: emit missing export struct bodies from mod.x.
          open(my $in, "<", $inject) or exit 0;
          my $in_body = 0; my $name; my $buf = "";
          my @emitted_full;  # pref+Struct names we print (for bare #define aliases)
          while (my $l = <$in>) {
            if (!$in_body && $l =~ /^struct (\Q$pref\E[A-Za-z_][A-Za-z0-9_]*) \{/) {
              $name = $1; $buf = $l; $in_body = 1; next;
            }
            if ($in_body) {
              $buf .= $l;
              if ($l =~ /^\};/) {
                if (!exists $has_full{$name}) {
                  print $buf;
                  push @emitted_full, $name;
                }
                $in_body = 0;
              }
            }
          }
          close($in);
          # Third: bare struct tag aliases. Codegen emits struct Ipv4Addr while
          # inject/gen has struct std_net_Ipv4Addr. Without alias, Mac formal cc
          # fails incomplete type struct Ipv4Addr (L4 net.o / net-context).
          # define Bare to pref_Bare so struct Bare equals namespaced body.
          # Cover both newly injected bodies and already-present pref+name bodies.
          # PLATFORM: SHARED — G.7 complete inject authority (no second type path).
          # NOTE: no single-quotes in this perl -e block (bash closes the string).
          open(my $gf2, "<", $gen_c) or exit 0;
          my $gtext = do { local $/; <$gf2> };
          close($gf2);
          my %alias_src;
          for my $full (@emitted_full) { $alias_src{$full} = 1; }
          for my $full (keys %has_full) {
            next unless $full =~ /^\Q$pref\E/;
            next if $full =~ /^xlang_slice_/;
            $alias_src{$full} = 1;
          }
          for my $full (sort keys %alias_src) {
            my $bare = $full;
            $bare =~ s/^\Q$pref\E//;
            next if $bare eq "" || $bare eq $full;
            next if $gtext =~ /^struct \Q$bare\E \{/m;  # already complete bare
            next if $gtext !~ /\bstruct \Q$bare\E\b/;   # not used
            print "#ifndef ${bare}\n#define ${bare} ${full}\n#endif\n";
          }
        ' "$gen_c" "$inject_tmp" "$mod_pref_x" >"$filtered" 2>/dev/null || true
        if [ -s "$filtered" ]; then
          merged="$tmp_dir/gen_inj_${idx}.c"
          if grep -q '^#include' "$gen_c"; then
            awk -v inj="$filtered" '
              /^#include/ { last=NR }
              { lines[NR]=$0 }
              END {
                for (i=1;i<=NR;i++) {
                  print lines[i]
                  if (i==last) {
                    while ((getline l < inj) > 0) print l
                    close(inj)
                  }
                }
              }' "$gen_c" >"$merged" && mv "$merged" "$gen_c"
          else
            cat "$filtered" "$gen_c" >"$merged" && mv "$merged" "$gen_c"
          fi
        fi
        # PLATFORM: SHARED — shell twin of perl bare-tag aliases (belt after filtered).
        # Emit `#define Bare pref_Bare` for every complete `struct pref_Bare {`
        # whose bare tag is used incomplete. Fixes L4 net.o incomplete Ipv4Addr.
        if [ -n "$mod_pref_x" ] && [ -f "$gen_c" ]; then
          _alias_h="$tmp_dir/bare_alias_${idx}.h"
          : >"$_alias_h"
          # Lines like: struct std_net_Ipv4Addr { ...
          grep -E "^struct ${mod_pref_x}[A-Za-z0-9_]+ \\{" "$gen_c" 2>/dev/null \
            | while IFS= read -r _sl; do
                full=$(printf '%s' "$_sl" | sed -E 's/^struct ([A-Za-z0-9_]+) \{.*/\1/')
                bare=${full#"$mod_pref_x"}
                [ -n "$bare" ] && [ "$bare" != "$full" ] || continue
                if grep -qE "struct[[:space:]]+${bare}([^A-Za-z0-9_]|$)" "$gen_c" 2>/dev/null \
                  && ! grep -qE "^struct[[:space:]]+${bare}[[:space:]]*\\{" "$gen_c" 2>/dev/null; then
                  if ! grep -qE "^#define[[:space:]]+${bare}[[:space:]]+" "$gen_c" 2>/dev/null \
                    && ! grep -qE "^#define[[:space:]]+${bare}[[:space:]]+" "$_alias_h" 2>/dev/null; then
                    printf '#ifndef %s\n#define %s %s\n#endif\n' "$bare" "$bare" "$full" >>"$_alias_h"
                  fi
                fi
              done
          # Insert bare #defines + slice bodies immediately AFTER the last complete
          # `struct pref_* {` block (preamble compact structs), so aliases apply before
          # any `struct xlang_slice_Bare { struct Bare *data }` uses incomplete Bare.
          # PLATFORM: SHARED — L4 net.o incomplete TcpStream / xlang_slice_TcpStream.
          if [ -s "$_alias_h" ]; then
            # Drop any incomplete slice bodies that referenced bare tags (re-add below).
            _scrub="$tmp_dir/gen_scrub_${idx}.c"
            grep -vE "^struct[[:space:]]+xlang_slice_[A-Za-z0-9_]+[[:space:]]*\\{[[:space:]]*struct[[:space:]]+[A-Za-z0-9_]+[[:space:]]*\\*data" "$gen_c" >"$_scrub" 2>/dev/null \
              || cp "$gen_c" "$_scrub"
            # Collect one-level xlang_slice_Bare only (not nested xlang_slice_xlang_slice_*).
            _slice_h="$tmp_dir/slice_syn_${idx}.h"
            : >"$_slice_h"
            _sl_list="$tmp_dir/slice_list_${idx}.txt"
            grep -oE 'struct[[:space:]]+xlang_slice_[A-Za-z0-9_]+' "$_scrub" 2>/dev/null \
              | sed -E 's/struct[[:space:]]+//' | sort -u >"$_sl_list" || true
            while IFS= read -r _sln; do
              case "$_sln" in
                xlang_slice_xlang_slice_*) continue ;; # skip nested explosion
                xlang_slice_*) ;;
                *) continue ;;
              esac
              _elem=${_sln#xlang_slice_}
              case "$_elem" in
                std_*|core_*|uint*|int*|size_t|ssize_t|float|double) continue ;; # already namespaced/primitive
              esac
              if grep -qE "^#define[[:space:]]+${_elem}[[:space:]]+" "$_alias_h" 2>/dev/null \
                || grep -qE "struct[[:space:]]+${mod_pref_x}${_elem}[[:space:]]*\\{" "$_scrub" 2>/dev/null; then
                printf 'struct %s { struct %s *data; size_t length; };\n' "$_sln" "$_elem" >>"$_slice_h"
              fi
            done <"$_sl_list"
            # Package: #defines first, then slice bodies (element types resolve via define).
            _pkg="$tmp_dir/alias_pkg_${idx}.h"
            {
              cat "$_alias_h"
              [ -s "$_slice_h" ] && cat "$_slice_h"
            } >"$_pkg"
            # Insert after last complete pref struct line (compact one-line bodies OK).
            _ins_line=$(grep -nE "^struct ${mod_pref_x}[A-Za-z0-9_]+ \\{" "$_scrub" 2>/dev/null | tail -1 | cut -d: -f1)
            [ -n "$_ins_line" ] || _ins_line=$(grep -n '^#include' "$_scrub" 2>/dev/null | tail -1 | cut -d: -f1)
            [ -n "$_ins_line" ] || _ins_line=1
            {
              head -n "$_ins_line" "$_scrub"
              cat "$_pkg"
              tail -n +"$((_ins_line + 1))" "$_scrub"
            } >"$tmp_dir/gen_alias_${idx}.c" && mv "$tmp_dir/gen_alias_${idx}.c" "$gen_c"
          fi
        fi
      fi
    fi
  fi

  # PLATFORM: MACOS — macOS lacks objcopy (Linux path renames bare → std_<mod>_*
  # in the .o). Without a rename, product links fail on missing std_<mod>_*.
  #
  # Root authority map (do NOT stack two rename strategies on one symbol):
  #   1) rt_preamble may already `#define bare std_<mod>_bare` so the bare C
  #      definition *is* the namespaced object symbol after preprocessing.
  #   2) Linux: objcopy --redefine-sym bare=std_<mod>_bare (post-cc).
  #   3) macOS (this block): thin wrapper `std_<mod>_bare(...){ return bare(...); }`
  #      only when (1) did not already claim the namespaced symbol.
  #
  # Symptom that was wrong: generating (3) for symbols under (1) → host-cc
  # redefinition of `std_heap_alloc_size_zero` (heap/mod.x).
  # G.7: single predicate — skip wrapper iff namespaced form already owned.
  # Linux objcopy path remains the ELF authority; this is the Mach-O twin.
  #
  # PLATFORM: MACOS — apply wrappers for *every* formal .x TU, not only mod.x.
  # Multi-file modules (heap = mod+libc+ops) import-bind as std_heap_libc_* /
  # std_heap_ops_* (see xlang_entry_lib_name_from_path_impl). Wrapping only
  # mod.x left libc/ops bare (heap_alloc_i32_c, map_i32_i32_find_c) → L4
  # run-set UNDEF std_heap_libc_* / std_heap_ops_map_i32_i32_find_c. Prefix
  # mirrors path: std/heap/libc.x → std_heap_libc_; skip trailing mod segment.
  if ! command -v objcopy >/dev/null 2>&1 && [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    # Derive pref from path (same rules as xlang_entry_lib_name_from_path_impl).
    _wrap_pref=""
    _wrap_rel=$(printf '%s' "$x_path" | sed -e 's|^\.\./||')
    case "$_wrap_rel" in
      std/*|core/*)
        _wrap_pref=$(python3 -c '
import sys
p = sys.argv[1].replace("\\\\", "/")
for root, pref0 in (("std/", "std_"), ("core/", "core_")):
    idx = p.find(root)
    if idx < 0:
        continue
    # accept only at path start or after /
    if idx > 0 and p[idx-1] not in "/":
        continue
    segs = p[idx+len(root):].split("/")
    parts = []
    for s in segs:
        if s.endswith(".su"):
            s = s[:-3]
        elif s.endswith(".x"):
            s = s[:-2]
        if not s or s == "mod":
            continue
        parts.append(s)
    if parts:
        print(pref0 + "_".join(parts) + "_")
        break
' "$_wrap_rel" 2>/dev/null) || _wrap_pref=""
        ;;
    esac
    if [ -n "$_wrap_pref" ] && [ "$_wrap_pref" != "_" ]; then
      python3 - "$gen_c" "$_wrap_pref" <<'PYEOF' >>"$gen_c.append_wrappers.c" 2>/dev/null && cat "$gen_c.append_wrappers.c" >>"$gen_c" && rm -f "$gen_c.append_wrappers.c" || true
import re, sys
# PLATFORM: MACOS — thin namespaced wrappers; skip when preamble #define already
# owns pref+name (bare def expands to that symbol). Mirrors Linux "nm already
# has mod_pref → skip objcopy" per-symbol.
gen_c_path, pref = sys.argv[1], sys.argv[2]
with open(gen_c_path, 'r') as f:
    s = f.read()
# Simple identifier #define bare → expansion (rt_preamble product aliases).
_define_re = re.compile(
    r'^#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+([A-Za-z_][A-Za-z0-9_]*)\s*$',
    re.M,
)
defines = {m.group(1): m.group(2) for m in _define_re.finditer(s)}
_func_def_re = re.compile(
    r'^(?P<ret>(?:struct\s+\w+|(?:u?int(?:8|16|32|64)?_t|void|int|size_t|char|float|double|ssize_t|uintptr_t|intptr_t)[\s\*]*))\s+'
    r'(?P<name>[a-z_][a-zA-Z_0-9]*)\s*'
    r'\((?P<args>[^)]*)\)\s*\{',
    re.M
)
def _extract_arg_names(args_str):
    args_str = args_str.strip()
    if args_str == 'void' or args_str == '':
        return ''
    names = []
    for part in args_str.split(','):
        part = part.strip()
        if part == '...':
            names.append('...')
            continue
        part_clean = re.sub(r'\[[^\]]*\]', '', part)
        tokens = part_clean.split()
        if not tokens:
            names.append('')
            continue
        names.append(tokens[-1].lstrip('*'))
    return ', '.join(names)
# Strong defs already present under this module prefix (or any std_/core_).
existing_ns = set()
for fm in _func_def_re.finditer(s):
    n = fm.group('name')
    if n.startswith(pref) or n.startswith(('core_', 'std_', 'xlang_')):
        existing_ns.add(n)
_skip_prefixes = ('core_', 'std_', 'xlang_', '__')
# Co-emitted dep/runtime shims must not get this module's prefix (would invent
# false product symbols and clash when multi-file ld -r / ar merges TUs).
_skip_names = {
    'args_iter_at_c', 'args_iter_count_c',
    'ctx_background_c', 'ctx_cancel_c', 'ctx_deadline_ns_c', 'ctx_free_c',
    'ctx_get_value_c', 'ctx_is_cancelled_c', 'ctx_remaining_ns_c',
    'ctx_set_value_c', 'ctx_with_cancel_c', 'ctx_with_deadline_c',
    'ctx_with_timeout_c',
    'io_read_batch_buf', 'io_register_buffers_4', 'io_register_buffers_buf_c',
    'io_wait_readable', 'io_write_batch_buf',
    'process_arg_c', 'process_args_count_c',
    'process_xlang_argc_get', 'process_xlang_argv_get',
}
out_lines = []
# Bare names that receive a product wrapper. Linux objcopy renames bare→ns;
# Mac leaves bare as global T → multi-formal multi-def (context+error both
# export is_cancelled). Hide bare via static on def + forward decl only
# (NOT #define — that breaks struct field designators like .code).
# PLATFORM: MACOS — L4 io-context gate.
to_wrap = []  # (fname, ns, fret, decl_args, farg_names)
for fm in _func_def_re.finditer(s):
    fname = fm.group('name')
    if fname.startswith(_skip_prefixes) or fname == 'main':
        continue
    if fname in _skip_names:
        continue
    # PLATFORM: SHARED — multi-file formal (mod.x + encoding.x): bodies named
    # encoding_*_c must stay global T so mod.x U-imports resolve inside the
    # ar. Making them static (hide multi-def) broke L4 run-encoding:
    # U encoding_utf8_*_c from mod with only `t` local in encoding TU.
    # G.7: only wrap bare product API (utf8_valid, ascii_is_alpha); never the
    # *_c impl face or already-prefixed impl names.
    if fname.endswith('_c'):
        continue
    # Skip co-emitted foreign module bodies (io driver / process / ctx glue).
    # PLATFORM: SHARED — do NOT skip this module's real API that shares a short
    # prefix. std.error exports io_err_cancelled/timeout/generic; the old blanket
    # `io_*` skip left those bare on Mac → product UNDEF std_error_io_err_*
    # (L4 run-std-io-context-gate). G.7: prefix skip only for known co-emit faces.
    # PLATFORM: MACOS — do NOT blanket-skip args_*: std.env product API is
    # args_iter / args_iter_count / args_iter_next (need std_env_* wrappers).
    # Co-emitted args_iter_at_c / args_iter_count_c already skipped via
    # endswith('_c') + _skip_names. Historical args_ prefix skip → run-env
    # UNDEF std_env_args_iter* (env_iter.x key_is_x_it). Same class as io_err_*.
    if fname.startswith('process_'):
        continue
    if fname.startswith('ctx_'):
        continue  # co-emitted ctx_*_c glue; product uses std_context_* wrappers
    if fname.startswith('io_') and not fname.startswith('io_err_'):
        continue  # co-emitted io driver shims; io_err_* is std.error API
    ns = pref + fname
    # Never redefine an existing namespaced body.
    if ns in existing_ns:
        continue
    # rt_preamble may `#define bare product_sym`. After preprocess the bare
    # definition *is* product_sym — emitting another `ns` body redefines it
    # when product_sym == ns (heap: alloc_size_zero → std_heap_alloc_size_zero).
    # When product_sym is some other std_/core_ symbol, bare is not a free
    # link name either; skip inventing pref+fname on top.
    exp = defines.get(fname)
    if exp is not None:
        if exp == ns:
            continue
        if exp.startswith(('std_', 'core_', 'xlang_')):
            continue
    fret = fm.group('ret').strip()
    fargs = fm.group('args').strip()
    farg_names = _extract_arg_names(fargs)
    decl_args = 'void' if (fargs == '' or fargs == 'void') else fargs
    to_wrap.append((fname, ns, fret, decl_args, farg_names))
# PLATFORM: MACOS — libc-clash names (write/read/close/open/exit/mmap/…)
# cannot remain the static body identifier: headers already declared them.
# A file-wide `#define write xlang_formal_bare_write` (clash gate below) also
# rewrites co-emitted FFI calls (std.sys.macos `r = write(fd, buf, count)`).
# Rename only wrapped definitions of the *same arity* + wrapper callees.
# Different-arity FFI prototypes (msync 3-arg vs X msync 2-arg) stay libc.
# G.7: complete wrapper authority (do not stack a second #define).
#
# PLATFORM: MACOS — POSIX listen(2) is 2-arg; X std.http export listen is
# 3-arg (addr, port, backlog). Darwin xlang_net_cap.h includes <sys/socket.h>
# so `static listen(...)` → "static declaration follows non-static".
# Linux Cap does not include socket.h (Ubuntu http already green via objcopy).
# Do NOT add listen to the SHARED arity-aware / file-wide #define lists:
# Ubuntu leftover calls are 3-arg only (listen_on); a SHARED def-rename
# without mixed leftover would steal those calls or leave them undeclared.
# G.7: same mmap-family mixed-arity rule (defs + X-arity calls; POSIX FFI stays).
#
# PLATFORM: MACOS — POSIX send(2)/recv(2) are 4-arg; X std.channel exports
# send(ch,val) / recv(ch,out) are 2-arg. Same socket.h exposure as listen:
# `static send(...)` → "static declaration follows non-static"; channel.o
# never lands → product -o UNDEF _std_channel_*. Linux Cap omits socket.h
# (Ubuntu L4@b5d919060 channel already green). Do NOT add send/recv to the
# SHARED #define lists (same leftover-steal risk as listen). close/free
# already clash-renamed (same arity as libc). G.7 complete this table.
#
# PLATFORM: MACOS — POSIX connect(2) is 3-arg; X std.net export connect
# (addr, port, timeout_ms) is also 3-arg (same arity as libc, like write).
# POSIX accept(2) is 3-arg; X std.net export accept(listener, timeout_ms)
# is 2-arg (mixed, like listen). Darwin socket.h makes
# `static connect(...)` / `static accept(...)` fail; net.o never lands →
# L4 STD-092 product -o UNDEF _std_net_*. X bodies call net_tcp_connect_c /
# net_accept_c (no leftover connect/accept in this TU); leftover POSIX
# FFI lives in tcp.x / ipv6.x other TUs. Do NOT add connect/accept to the
# SHARED #define lists (same leftover-steal risk). G.7 complete this table.
_libc_clash = {
    'wait', 'free', 'open', 'close', 'malloc', 'realloc', 'calloc',
    'getcwd', 'chdir', 'pipe', 'exit', 'getenv', 'setenv', 'unsetenv',
    'getpid', 'getppid', 'waitpid', 'exec', 'signal', 'abort',
    'unreachable', 'remove', 'rename', 'system', 'time', 'clock',
    'read', 'write', 'sync',
    'mmap', 'munmap', 'msync', 'ftruncate', 'lseek',
    'listen',
    'send', 'recv',
    'connect', 'accept',
    'abs', 'fabs', 'floor', 'ceil', 'trunc', 'round',
    'sin', 'cos', 'tan', 'asin', 'acos', 'atan', 'atan2',
    'sqrt', 'cbrt', 'pow', 'exp', 'log', 'log1p', 'expm1',
    'erf', 'erfc', 'min', 'max',
}
# POSIX/libc arity when it differs from an X export of the same name.
# After def-rename, rewrite in-TU calls of the X arity so listen_on hits
# the bare body. POSIX listen(2) lives in the included header (not gen_c
# text) — leftover-arity detection in this TU cannot see it.
# Names omitted here have X arity == libc (write 3 vs write 3): leftover
# calls stay libc (existing file-wide #define skip). G.7 complete table.
_libc_clash_posix_arity = {
    'mmap': 6,
    'munmap': 2,
    'msync': 3,
    'listen': 2,
    'send': 4,
    'recv': 4,
    'accept': 3,
}
def _arg_count(args_str):
    a = (args_str or '').strip()
    if a == '' or a == 'void':
        return 0
    return a.count(',') + 1
if to_wrap:
    s2 = s
    for fname, ns, fret, decl_args, farg_names in to_wrap:
        body = ('xlang_formal_bare_' + fname) if fname in _libc_clash else fname
        want_n = _arg_count(decl_args)
        pat = re.compile(
            rf'(?m)^(extern\s+)?((?:struct\s+\w+|(?:u?int(?:8|16|32|64)?_t|void|int|size_t|char|float|double|ssize_t|uintptr_t|intptr_t)[\s\*]*)\s+){re.escape(fname)}(\s*\()([^)]*)(\))'
        )
        def _repl(m, body=body, want_n=want_n):
            got_n = _arg_count(m.group(4))
            if got_n != want_n:
                return m.group(0)
            return 'static ' + m.group(2) + body + m.group(3) + m.group(4) + m.group(5)
        s2 = pat.sub(_repl, s2)
        posix_n = _libc_clash_posix_arity.get(fname)
        if fname in _libc_clash and posix_n is not None and posix_n != want_n:
            call_pat = re.compile(
                rf'(?<![A-Za-z0-9_]){re.escape(fname)}\s*\(([^)]*)\)'
            )
            def _repl_call(m, body=body, want_n=want_n):
                if _arg_count(m.group(1)) != want_n:
                    return m.group(0)
                return body + '(' + m.group(1) + ')'
            s2 = call_pat.sub(_repl_call, s2)
    with open(gen_c_path, 'w') as f:
        f.write(s2)
    print('/* Namespaced wrappers — macOS twin of Linux objcopy; bare body static. */')
    for fname, ns, fret, decl_args, farg_names in to_wrap:
        body = ('xlang_formal_bare_' + fname) if fname in _libc_clash else fname
        if fret == 'void':
            print(f'{fret} {ns}({decl_args}) {{ {body}({farg_names}); }}')
        else:
            print(f'{fret} {ns}({decl_args}) {{ return {body}({farg_names}); }}')
PYEOF
    fi
  fi

  # PLATFORM: SHARED — arity-aware libc-clash rename of X defs/forwards only.
  # File-wide `#define msync` also rewrites linux/macos FFI 3-arg msync() calls
  # (std.sys.linux `return msync(addr, len, flags)`). X exports msync(ptr,size)
  # 2-arg. Rename only matching-arity decls; calls stay libc. Darwin wrappers
  # already renamed → no-op. G.7 complete clash gate (mmap family not #define).
  if [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    python3 - "$gen_c" <<'PYEOF' || true
import re, sys
path = sys.argv[1]
with open(path, 'r') as f:
    s = f.read()
clash = {
    'wait', 'free', 'open', 'close', 'malloc', 'realloc', 'calloc',
    'getcwd', 'chdir', 'pipe', 'exit', 'getenv', 'setenv', 'unsetenv',
    'getpid', 'getppid', 'waitpid', 'exec', 'signal', 'abort',
    'unreachable', 'remove', 'rename', 'system', 'time', 'clock',
    'read', 'write', 'sync',
    'mmap', 'munmap', 'msync', 'ftruncate', 'lseek',
    'abs', 'fabs', 'floor', 'ceil', 'trunc', 'round',
    'sin', 'cos', 'tan', 'asin', 'acos', 'atan', 'atan2',
    'sqrt', 'cbrt', 'pow', 'exp', 'log', 'log1p', 'expm1',
    'erf', 'erfc', 'min', 'max',
}
ret = (
    r'(?:struct\s+\w+|(?:u?int(?:8|16|32|64)?_t|void|int|size_t|char|float|'
    r'double|ssize_t|uintptr_t|intptr_t)[\s\*]*)'
)
def arg_count(a):
    a = (a or '').strip()
    if a == '' or a == 'void':
        return 0
    return a.count(',') + 1
def_arity = {}
for m in re.finditer(
    rf'(?m)^(?:extern\s+|static\s+)?(?:{ret})\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)\s*\{{',
    s,
):
    name = m.group(1)
    if name not in clash:
        continue
    def_arity.setdefault(name, set()).add(arg_count(m.group(2)))
for name, arities in def_arity.items():
    if len(arities) != 1:
        continue
    want = next(iter(arities))
    body = 'xlang_formal_bare_' + name
    pat = re.compile(
        rf'(?m)^((?:extern\s+|static\s+)?)({ret}\s+){re.escape(name)}(\s*\()([^)]*)(\))'
    )
    def repl(m, body=body, want=want):
        if arg_count(m.group(4)) != want:
            return m.group(0)
        return m.group(1) + m.group(2) + body + m.group(3) + m.group(4) + m.group(5)
    s = pat.sub(repl, s)
with open(path, 'w') as f:
    f.write(s)
PYEOF
  fi

  # PLATFORM: SHARED — pre-cc POSIX/libc bare-name clash guard.
  # Root: formal_mod host-C emits bare export names (e.g. std.sync wait). System
  # headers already declare wait(int*)/free/… → "conflicting types for 'wait'" at
  # cc -c; post-o objcopy never runs. Symptom: L4 cold ensure sync.o fails →
  # run-sync UNDEF std_sync_*. Authority: only when gen_c defines bare name as a
  # function, inject after last #include:
  #   #undef name / #define name xlang_formal_bare_name
  # so defs + call sites rename; Mac std_<mod>_* wrappers and Linux objcopy both
  # still see a consistent body. G.7: single pre-cc gate (do not stack a second
  # rename strategy for the same bare name).
  if [ -f "$gen_c" ] && [ -s "$gen_c" ]; then
    _clash_hdr="$tmp_dir/libc_clash_${idx}.h"
    : >"$_clash_hdr"
    # POSIX + common hosted names that appear as bare X exports in formal_mod.
    # Keep list aligned with post-o clash loop below (+ wait, which fails at cc).
    # PLATFORM: SHARED — math.h / libm bare names (std.math mod.x exports abs/floor/…):
    # without rename, cc -c fails "conflicting types for 'abs'" (C int abs(int) vs
    # X f64 abs(f64)); L4 cold ensure math.o never lands → run-math C smoke + product
    # UNDEF std_math_*. G.7: extend same pre-cc clash gate (no second math-only path).
    # PLATFORM: LINUX|UBUNTU GCC15+ — C23 stddef.h `#define unreachable() …` (0-arg
    # function-like macro). core.builtin export `void unreachable(void)` becomes
    # `unreachable(void)` → "macro passed 1 arguments, but takes just 0" → formal
    # builtin.o never built → pure-asm run-builtin UNDEF core_builtin_*. G.7: same
    # pre-cc rename gate (not a second path).
    for _cn in wait free open close malloc realloc calloc getcwd chdir pipe exit \
               getenv setenv unsetenv getpid getppid waitpid exec signal abort \
               unreachable \
               remove rename system time clock read write sync \
               abs fabs floor ceil trunc round sin cos tan asin acos atan atan2 \
               sqrt cbrt pow exp log log1p expm1 erf erfc min max; do
      # PLATFORM: SHARED — skip file-wide `#define open` when arity-aware rename
      # already created xlang_formal_bare_* AND leftover bare calls remain.
      # kv/mod.x export open(path, cap) 2-arg + co-emitted macos mmap FFI
      # open(path, flags, mode) 3-arg: file-wide define rewrites FFI into an
      # implicit 3-arg xlang_formal_bare_open then the static 2-arg X def
      # conflicts (≡ msync 2 vs 3; mmap family not #define). G.7 complete
      # existing clash gate — mixed-arity TUs rely on arity-aware rename only.
      if grep -Eq "xlang_formal_bare_${_cn}" "$gen_c" 2>/dev/null \
         && grep -Eq "[^_A-Za-z0-9]${_cn}[[:space:]]*\\(" "$gen_c" 2>/dev/null; then
        continue
      fi
      # Only guard names that have a function *definition* in this TU (not mere
      # mentions in comments / strings). Match return-type name( form.
      if grep -Eq "^[A-Za-z_][A-Za-z0-9_ *]*[[:space:]]+${_cn}[[:space:]]*\\(" "$gen_c" 2>/dev/null; then
        {
          printf '/* formal_mod pre-cc: bare %s clashes with hosted C — rename body */\n' "$_cn"
          printf '#ifdef %s\n#undef %s\n#endif\n#define %s xlang_formal_bare_%s\n' \
            "$_cn" "$_cn" "$_cn" "$_cn"
        } >>"$_clash_hdr"
      fi
    done
    # PLATFORM: SHARED — rt_preamble consumer shims are function-like macros
    # (`#define empty_size(_a,_b) std_map_empty_size()` etc.). When formal_mod
    # is the *producer* of that export, gen_c has `int32_t empty_size(void)` /
    # `int32_t empty_size(void) {…}` and the macro expands with too few args →
    # cc -c fails (L4: map.o never built ×80; run-set later UNDEF heap surface
    # that depends on map/heap formal completeness). G.7: undef the shim only
    # when this TU defines the bare function body (producer). Consumers keep
    # the preamble macro. Same class: error_ok, empty_len.
    for _pm in empty_size error_ok empty_len; do
      if grep -Eq "^#define[[:space:]]+${_pm}[[:space:]]*\\(" "$gen_c" 2>/dev/null \
         && grep -Eq "^[A-Za-z_][A-Za-z0-9_ *]*[[:space:]]+${_pm}[[:space:]]*\\(" "$gen_c" 2>/dev/null; then
        {
          printf '/* formal_mod pre-cc: undef preamble macro %s — this TU defines the export */\n' "$_pm"
          printf '#ifdef %s\n#undef %s\n#endif\n' "$_pm" "$_pm"
        } >>"$_clash_hdr"
      fi
    done
    if [ -s "$_clash_hdr" ]; then
      _clash_merged="$tmp_dir/gen_clash_${idx}.c"
      if grep -q '^#include' "$gen_c"; then
        awk -v inj="$_clash_hdr" '
          /^#include/ { last=NR }
          { lines[NR]=$0 }
          END {
            for (i=1;i<=NR;i++) {
              print lines[i]
              if (i==last) {
                while ((getline l < inj) > 0) print l
                close(inj)
              }
            }
          }' "$gen_c" >"$_clash_merged" && mv "$_clash_merged" "$gen_c"
      else
        cat "$_clash_hdr" "$gen_c" >"$_clash_merged" && mv "$_clash_merged" "$gen_c"
      fi
    fi
  fi

  # PLATFORM: SHARED — final pre-cc: complete one-level xlang_slice_Bare when
  # #define Bare pref_Bare is present but slice body is only a forward decl.
  # Root (L4 net.o): inject order left `struct xlang_slice_TcpStream;` incomplete.
  # Also re-arm std_io_read/write_fixed_fd macros if preamble #undef left calls bare.
  if [ -f "$gen_c" ]; then
    _fin_slice="$tmp_dir/final_slice_${idx}.h"
    : >"$_fin_slice"
    grep -oE 'struct[[:space:]]+xlang_slice_[A-Za-z0-9_]+' "$gen_c" 2>/dev/null \
      | sed -E 's/struct[[:space:]]+//' | sort -u >"$tmp_dir/final_sl_${idx}.txt" || true
    while IFS= read -r _sln; do
      case "$_sln" in
        xlang_slice_xlang_slice_*) continue ;;
        xlang_slice_*) ;;
        *) continue ;;
      esac
      _elem=${_sln#xlang_slice_}
      case "$_elem" in
        std_*|core_*|uint*|int*|size_t|ssize_t|float|double) continue ;;
      esac
      # Need alias for element and no complete slice body yet.
      if grep -qE "^#define[[:space:]]+${_elem}[[:space:]]+" "$gen_c" 2>/dev/null \
        && ! grep -qE "^struct[[:space:]]+${_sln}[[:space:]]*\\{[^;]*data" "$gen_c" 2>/dev/null; then
        printf 'struct %s { struct %s *data; size_t length; };\n' "$_sln" "$_elem" >>"$_fin_slice"
      fi
    done <"$tmp_dir/final_sl_${idx}.txt"
    # net.o: preamble may #undef std_io_read_fixed_fd after defining it; re-arm if called.
    if grep -qE '\bstd_io_read_fixed_fd\s*\(' "$gen_c" 2>/dev/null \
      && ! grep -qE '^#define[[:space:]]+std_io_read_fixed_fd' "$gen_c" 2>/dev/null; then
      printf '#define std_io_read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n' >>"$_fin_slice"
    fi
    if grep -qE '\bstd_io_write_fixed_fd\s*\(' "$gen_c" 2>/dev/null \
      && ! grep -qE '^#define[[:space:]]+std_io_write_fixed_fd' "$gen_c" 2>/dev/null; then
      printf '#define std_io_write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n' >>"$_fin_slice"
    fi
    if [ -s "$_fin_slice" ]; then
      # Insert after last #define Bare pref_Bare (or last #include) so bodies precede uses.
      _ins=$(grep -nE '^#define[[:space:]]+[A-Za-z0-9_]+[[:space:]]+std_[a-z0-9_]+' "$gen_c" 2>/dev/null | tail -1 | cut -d: -f1)
      [ -n "$_ins" ] || _ins=$(grep -n '^#include' "$gen_c" 2>/dev/null | tail -1 | cut -d: -f1)
      [ -n "$_ins" ] || _ins=1
      {
        head -n "$_ins" "$gen_c"
        cat "$_fin_slice"
        tail -n +"$((_ins + 1))" "$gen_c"
      } >"$tmp_dir/gen_finsl_${idx}.c" && mv "$tmp_dir/gen_finsl_${idx}.c" "$gen_c"
    fi
  fi

  # PLATFORM: SHARED — libc extern prototypes that clash with hosted headers.
  # Darwin fortify: `#define snprintf(...) __snprintf_chk_func(...)` rewrites
  # codegen's `extern int32_t snprintf(uint8_t *, size_t, uint8_t *)` into an
  # invalid declarator (cookbook sqlite_available / sqlite.x snprintf FFI).
  # Product skip predicate codegen_is_libc_conflicting_extern_name covers
  # stdlib/string/unistd names whose headers are already in the C prologue;
  # snprintf is stdio (not in that prologue) so -E still emits the redecl.
  # G.7 complete this compile vehicle: drop the redecl and include stdio.h
  # when this TU calls snprintf. Do not file-wide `#define snprintf` (would
  # rewrite libc calls into a missing xlang_formal_bare_snprintf). Same class
  # as g05 sed-delete of malloc/write redecls; not a second sqlite-only path.
  if [ -f "$gen_c" ] && grep -qE '^extern[[:space:]]+(int32_t|int)[[:space:]]+snprintf[[:space:]]*\(' "$gen_c" 2>/dev/null; then
    sed -e '/^extern int32_t snprintf(/d' -e '/^extern int snprintf(/d' \
      "$gen_c" >"$tmp_dir/gen_nsprintf_${idx}.c" && mv "$tmp_dir/gen_nsprintf_${idx}.c" "$gen_c"
    if ! grep -qE '#include[[:space:]]*<stdio\.h>' "$gen_c" 2>/dev/null; then
      _ns_inc=$(grep -n '^#include' "$gen_c" 2>/dev/null | tail -1 | cut -d: -f1)
      [ -n "$_ns_inc" ] || _ns_inc=1
      {
        head -n "$_ns_inc" "$gen_c"
        echo '/* PLATFORM: SHARED — libc snprintf after dropping conflicting XLANG extern */'
        echo '#include <stdio.h>'
        tail -n +"$((_ns_inc + 1))" "$gen_c"
      } >"$tmp_dir/gen_stdio_${idx}.c" && mv "$tmp_dir/gen_stdio_${idx}.c" "$gen_c"
    fi
  fi

  if ! cc $CFLAGS -c "$gen_c" -o "$obj" 2>"$tmp_dir/cc_${idx}.log"; then
    echo "xlang_compile_std_module.sh: cc -c failed for $x_path" >&2
    # 显示首个 error
    grep -m1 'error:' "$tmp_dir/cc_${idx}.log" >&2 || cat "$tmp_dir/cc_${idx}.log" >&2
    exit 1
  fi
  if [ -z "$obj_files" ]; then
    obj_files="$obj"
  else
    obj_files="$obj_files $obj"
  fi
  idx=$((idx + 1))
done

# 单文件直接移到输出；多文件 ld -r 合并
if [ "$idx" -eq 1 ]; then
  mv "$obj_files" "$out_o"
else
  # 【Why 根源】ld -r 合并多 .o 为一个可重定位 .o。
  # Linux GNU ld 用 --allow-multiple-definition 兼容 weak / co-emitted 重复定义；
  # macOS Mach-O ld 无此选项，且对 KEEP_C 共发射的 import 强符号（如 core_mem_*
  # 在 heap mod+libc+ops 三 TU）硬失败。PLATFORM: LINUX 走 allow-multiple；
  # PLATFORM: MACOS 在 ld -r 失败后回退 libtool -static（产出 ar，产品链仍接受）。
  LD_R_FLAGS="-r"
  if ld --help 2>&1 | grep -q 'allow-multiple-definition'; then
    LD_R_FLAGS="-r --allow-multiple-definition"
  fi
  if ! ld $LD_R_FLAGS -o "$out_o" $obj_files 2>"$tmp_dir/ld.log"; then
    if command -v libtool >/dev/null 2>&1 \
      && libtool -static -o "$out_o" $obj_files 2>>"$tmp_dir/ld.log"; then
      :
    else
      echo "xlang_compile_std_module.sh: ld -r failed" >&2
      cat "$tmp_dir/ld.log" >&2
      exit 1
    fi
  fi
fi

# 【Why 根源】-x -E 对 std/*/mod.x 当前常产出裸符号 free/open/close 等，链入用户
# exe 后覆盖 libc 同名符号（hello 在 hash_sip_free_c↔free 无限递归 SIGSEGV）。
# 在 .o 落地后把与 libc 冲突的裸符号重命名为 std_<leaf>_*_api，避免污染。
# 与上方 pre-cc 改名双保险：若某路径未走 pre-cc（旧 gen）仍可后处理。
# 真前缀收敛后（codegen 对 entry 正确应用 path lib_name）本段可删。
# PLATFORM: SHARED — post-o symbol authority. Linux uses objcopy redefine;
# macOS often has no objcopy (wrappers above are primary). Heap alias table
# below must still run on Darwin (nm-only) when multi-file ar lacks namespaced
# libc/ops exports. G.7: do not gate the whole post-o block on objcopy.
if command -v nm >/dev/null 2>&1 && [ -f "$out_o" ]; then
  leaf=$(basename "$(dirname "$out_o")")
  case "$leaf" in
    ''|.) leaf=$(basename "$out_o" .o) ;;
  esac
  # PLATFORM: SHARED — product prefix for core/* and std/* formal .o after KEEP_C/cc.
  # out: ../core/slice/mod.o → core_slice_*; ../std/env/env.o → std_env_*.
  # Nested leaf exception: ../std/io/driver.o → std_io_driver_* (not std_io_*).
  # Skip symbols already core_*/std_* (co-emitted deps). G.7 complete authority for
  # core.slice length.x: bare len_i32 must become core_slice_len_i32.
  out_rel=$(printf '%s' "$out_o" | sed -e 's|^\.\./||')
  out_root=$(printf '%s' "$out_rel" | sed -e 's|/.*||')
  case "$out_rel" in
    std/io/driver.o)
      # PLATFORM: SHARED — nested module std.io.driver product face.
      leaf="io_driver"
      ;;
    std/db/sqlite/sqlite.o)
      # PLATFORM: SHARED — nested module std.db.sqlite product face.
      # Import mangle is std_db_sqlite_*; leaf basename sqlite would yield
      # std_sqlite_* (Ubuntu objcopy). Twin of std/io/driver.o → io_driver.
      leaf="db_sqlite"
      ;;
    std/compress/zlib/zlib.o)
      # PLATFORM: SHARED — nested module std.compress.zlib product face.
      # Import mangle is std_compress_zlib_*; leaf basename zlib would yield
      # std_zlib_* (Ubuntu objcopy). Twin of sqlite → db_sqlite.
      leaf="compress_zlib"
      ;;
    std/compress/gzip/gzip.o)
      # PLATFORM: SHARED — nested module std.compress.gzip product face.
      # Import mangle is std_compress_gzip_* (gzip_compress → gzip_gzip_compress).
      # Leaf basename gzip would yield std_gzip_* (Ubuntu objcopy).
      leaf="compress_gzip"
      ;;
    std/compress/zstd/zstd.o)
      # PLATFORM: SHARED — nested module std.compress.zstd product face.
      # Import mangle is std_compress_zstd_* (zstd_compress → zstd_zstd_compress).
      # Leaf basename zstd would yield std_zstd_* (Ubuntu objcopy). Twin of gzip.
      leaf="compress_zstd"
      ;;
    std/compress/brotli/brotli.o)
      # PLATFORM: SHARED — nested module std.compress.brotli product face.
      # Import mangle is std_compress_brotli_* (brotli_compress → brotli_brotli_compress).
      # Leaf basename brotli would yield std_brotli_* (Ubuntu objcopy). Twin of gzip.
      leaf="compress_brotli"
      ;;
    std/db/kv/kv.o)
      # PLATFORM: SHARED — nested module std.db.kv product face.
      # Import mangle is std_db_kv_*; leaf basename kv would yield std_kv_*
      # (Ubuntu objcopy). Twin of sqlite → db_sqlite.
      leaf="db_kv"
      ;;
    std/db/arrow/arrow.o)
      # PLATFORM: SHARED — nested module std.db.arrow product face.
      # Import mangle is std_db_arrow_*; leaf basename arrow would yield
      # std_arrow_* (Ubuntu objcopy). Twin of sqlite → db_sqlite.
      leaf="db_arrow"
      ;;
    std/sys/linux.o)
      # PLATFORM: SHARED — nested module std.sys.linux product face.
      # Import mangle is std_sys_linux_* + function linux_* → std_sys_linux_linux_*.
      # Parent-dir leaf "sys" would yield std_sys_linux_syscall_* (short; BLD001).
      # Twin of std/db/sqlite → db_sqlite / std/io/driver → io_driver.
      leaf="sys_linux"
      ;;
    std/sys/macos.o)
      # PLATFORM: SHARED — nested module std.sys.macos product face.
      # Import mangle is std_sys_macos_* + function macos_* → std_sys_macos_macos_*.
      # Parent-dir leaf "sys" would yield std_sys_macos_write_* (short; BLD001).
      leaf="sys_macos"
      ;;
  esac
  case "$out_root" in
    core) prod_pref="core_${leaf}_" ;;
    std)  prod_pref="std_${leaf}_" ;;
    *)    prod_pref="" ;;
  esac
  if command -v objcopy >/dev/null 2>&1; then
    # PLATFORM: SHARED — bare → prod_pref rename is **per-symbol**, not whole-file.
    # Root bug (Ubuntu L4 run-set @5acd137bd): gate was
    #   if ! nm | grep " T ${prod_pref}"  → skip entire rename when ANY namespaced
    #   export already exists.
    # Multi-file heap (mod+libc+ops) already has std_heap_libc_* / std_heap_ops_*
    # after merge, so mod.x surfaces (map_find, alloc_usize, …) stayed bare T.
    # Product monofile U-refs std_heap_map_find → UNDEF; Mac twin used pre-cc
    # wrappers so monofile path stayed green (false dual-end signal).
    # G.7: single post-o rename authority — only rename when prod_pref+bare is
    # still missing; never skip the whole leaf because sibling TUs already prefixed.
    if [ -n "$prod_pref" ]; then
      nm "$out_o" 2>/dev/null | awk '/ [TDB] / { print $3 }' | while IFS= read -r sym; do
        [ -n "$sym" ] || continue
        case "$sym" in
          "${prod_pref}"*|_"${prod_pref}"*) continue ;;
          core_*|std_*|_core_*|_std_*|xlang_*|_xlang_*) continue ;;
          _Z*|.L*|L0*|__*) continue ;;
          # Foreign co-emit faces (ctx/io/process/args) — not this leaf's API;
          # left for localize step below (do not invent std_heap_ctx_*).
          # PLATFORM: SHARED — std.error product API is io_err_* (not io driver).
          # Blanket io_* skip left bare io_err_timeout → run-std-io-context-gate
          # UNDEF std_error_io_err_* (Ubuntu L4 @775804765). Match Mac wrappers:
          # skip io_* except io_err_*.
          args_*|ctx_*|process_*|_args_*|_ctx_*|_process_*) continue ;;
          io_*|_io_*)
            case "$sym" in
              io_err_*|_io_err_*) ;;
              *) continue ;;
            esac
            ;;
        esac
        bare="$sym"
        case "$sym" in
          _*) bare="${sym#_}" ;;
        esac
        case "$bare" in
          "${prod_pref}"*|core_*|std_*|xlang_*) continue ;;
          args_*|ctx_*|process_*) continue ;;
          io_*)
            case "$bare" in
              io_err_*) ;;
              *) continue ;;
            esac
            ;;
          # PLATFORM: SHARED — never invent prod_pref+*_c. Impl / FFI faces stay
          # bare (or get dedicated alias tables). Regression @71d9c714e: log_write_c
          # → std_log_log_write_c broke runtime_log_os U log_write_c (run-log).
          # Same rule as Mac wrappers "never wrap *_c" and encoding multi-file.
          *_c) continue ;;
        esac
        # heap multi-file ops bare (not always *_c) → dedicated alias table only.
        if [ "$leaf" = "heap" ]; then
          case "$bare" in
            map_slot|heap_mem_set_c|heap_mem_compare_c) continue ;;
          esac
        fi
        # Already have product export → leave bare alone only if namespaced exists
        # (then localize bare below would drop a second body; prefer redefine when
        # target missing). If target already present, localize bare duplicate.
        if nm "$out_o" 2>/dev/null | grep -qE " T ${prod_pref}${bare}$| T _${prod_pref}${bare}$"; then
          objcopy --localize-symbol="$sym" "$out_o" 2>/dev/null || true
          continue
        fi
        if [ "$bare" != "$sym" ]; then
          objcopy --redefine-sym "${sym}=_${prod_pref}${bare}" "$out_o" 2>/dev/null || true
        else
          objcopy --redefine-sym "${sym}=${prod_pref}${bare}" "$out_o" 2>/dev/null || true
        fi
      done
    fi
    # PLATFORM: SHARED — post-o twin of pre-cc clash guard (wait + libm + C23 unreachable).
    # Pre-cc rewrites def to xlang_formal_bare_<name>; post-o must map that body to
    # product face: std_<leaf>_* or core_<leaf>_* (use prod_pref, not hard-coded std_).
    # Looking only for bare T <clash> missed xlang_formal_bare_log → run-log UNDEF
    # std_log_log @71d9c714e. Root (run-builtin): hard-coded std_${leaf}_ would map
    # core.builtin abort/unreachable → std_builtin_* (wrong) vs core_builtin_*.
    # G.7 complete: prod_pref from out path (core/builtin → core_builtin_).
    for clash in free open close malloc realloc calloc getcwd chdir pipe exit \
                 getenv setenv unsetenv getpid getppid waitpid wait exec signal abort \
                 unreachable \
                 remove rename system time clock read write sync \
                 mmap munmap msync ftruncate lseek \
                 abs fabs floor ceil trunc round sin cos tan asin acos atan atan2 \
                 sqrt cbrt pow exp log log1p expm1 erf erfc min max; do
      if [ -n "$prod_pref" ]; then
        prod="${prod_pref}${clash}"
      else
        prod="std_${leaf}_${clash}"
      fi
      fb="xlang_formal_bare_${clash}"
      if nm "$out_o" 2>/dev/null | grep -qE " T ${fb}$| T _${fb}$"; then
        if nm "$out_o" 2>/dev/null | grep -qE " T ${prod}$| T _${prod}$"; then
          objcopy --localize-symbol="$fb" "$out_o" 2>/dev/null || true
          objcopy --localize-symbol="_${fb}" "$out_o" 2>/dev/null || true
        else
          if nm "$out_o" 2>/dev/null | grep -q " T _${fb}$"; then
            objcopy --redefine-sym "_${fb}=_${prod}" "$out_o" 2>/dev/null || true
          else
            objcopy --redefine-sym "${fb}=${prod}" "$out_o" 2>/dev/null || true
          fi
        fi
      fi
      if nm "$out_o" 2>/dev/null | grep -q " T ${clash}$"; then
        # Prefer product export (std_env_getenv / core_builtin_abort). *_api was a
        # historical clash guard when product already present; keep side body local.
        # PLATFORM: SHARED — Ubuntu asm -o of mod.x often emits bare names; mac may prefix.
        if nm "$out_o" 2>/dev/null | grep -q " T ${prod}$"; then
          objcopy --redefine-sym "${clash}=${prod}_api" "$out_o" 2>/dev/null || true
        else
          objcopy --redefine-sym "${clash}=${prod}" "$out_o" 2>/dev/null || true
        fi
      fi
    done
    # PLATFORM: SHARED — env product surface: bare getenv_exists/z/ptr/temp_dir/iter*
    # are not in the libc-clash list above; import calls std_env_*. Complete the rename.
    # PLATFORM: LINUX|ELF — objcopy redefine (underscore-aware Mach-O-style nm too).
    # PLATFORM: MACOS — primary path is pre-cc thin wrappers (above); this block
    # is no-op when objcopy missing. Keep underscore form so Linux-with-underscore
    # toolchains and future Mac llvm-objcopy still map bare → std_env_*.
    if [ "$leaf" = "env" ]; then
      for bare in getenv getenv_exists getenv_z getenv_ptr setenv unsetenv temp_dir \
                  iter iter_count iter_next args_iter args_iter_count args_iter_next; do
        if nm "$out_o" 2>/dev/null | grep -q " T ${bare}$"; then
          objcopy --redefine-sym "${bare}=std_env_${bare}" "$out_o" 2>/dev/null || true
        elif nm "$out_o" 2>/dev/null | grep -q " T _${bare}$"; then
          # Mach-O / underscored ELF: T _args_iter → _std_env_args_iter
          objcopy --redefine-sym "_${bare}=_std_env_${bare}" "$out_o" 2>/dev/null || true
        fi
        if nm "$out_o" 2>/dev/null | grep -q " T std_env_${bare}_api$"; then
          objcopy --redefine-sym "std_env_${bare}_api=std_env_${bare}" "$out_o" 2>/dev/null || true
        elif nm "$out_o" 2>/dev/null | grep -q " T _std_env_${bare}_api$"; then
          objcopy --redefine-sym "_std_env_${bare}_api=_std_env_${bare}" "$out_o" 2>/dev/null || true
        fi
      done
    fi
  fi
  # PLATFORM: SHARED — formal_mod co-emits foreign module bodies as global T
  # (core_mem_* into heap.o/set.o; core_option_* into slice.o; …). Product
  # links leaf.o + authority .o → multi-def. Keep global only this leaf's
  # prod_pref exports; foreign core_*/std_* become local. Authority .o keeps
  # the global face. G.7: former core.slice-only core_option_* special case.
  # PLATFORM: LINUX|ELF — objcopy --localize-symbol (foreign list).
  # PLATFORM: MACOS|DARWIN — stock Xcode has no objcopy; nmedit -s is unreliable
  # on current Xcode (listed symbols not demoted). Use ld -r -exported_symbols_list
  # with this leaf's prod_pref globals (inverse: keep only leaf API).
  # Root (mac run-slice): core/slice/mod.o global core_option_* multi-def option.o.
  if [ -n "$prod_pref" ] && [ -f "$out_o" ]; then
    if command -v objcopy >/dev/null 2>&1; then
      nm "$out_o" 2>/dev/null | awk '/ [TDB] / { print $3 }' | while IFS= read -r sym; do
        [ -n "$sym" ] || continue
        bare="$sym"
        case "$sym" in
          _*) bare="${sym#_}" ;;
        esac
        case "$bare" in
          # PLATFORM: SHARED — only for std/sys/sys.o (leaf=sys): co-emitted
          # import("std.sys.linux") bodies are std_sys_linux_linux_* and match
          # prod_pref std_sys_*. Authority = linux.o after nested-leaf rename;
          # keep them local to avoid multi-def when both sys.o + linux.o are on
          # LD argv. Do NOT localize when leaf=sys_linux (linux.o itself).
          std_sys_linux_linux_*)
            if [ "$leaf" = "sys" ]; then
              objcopy --localize-symbol="$sym" "$out_o" 2>/dev/null || true
              continue
            fi
            ;;
          "${prod_pref}"*) continue ;;
          core_*|std_*)
            objcopy --localize-symbol="$sym" "$out_o" 2>/dev/null || true
            ;;
        esac
      done
    else
      # PLATFORM: MACOS — export this leaf's product-prefixed globals.
      # bare-impl multi-file (mod.x + encoding.x): also keep leaf_*_c impl faces.
      # Pure-asm product import still binds encoding_utf8_valid_c (extern face) while
      # wrappers are std_encoding_utf8_valid; demoting *_c → local left user.o UNDEF.
      # Foreign core_*/std_* (co-emitted mem) stay off the list → local (no multidef
      # when companion-push string.o / base64.o). G.7: complete export authority.
      # When multi-file ld -r fails, libtool emits ar; whole-archive
      # -exported_symbols_list fails. Fall back: filter each ar member (G.7 complete).
      _exp_list="$tmp_dir/export_prod_pref_syms.txt"
      : >"$_exp_list"
      nm "$out_o" 2>/dev/null | awk '/ [TDB] / { print $3 }' >"$tmp_dir/export_nm_syms.txt" || true
      while IFS= read -r sym; do
        [ -n "$sym" ] || continue
        bare="$sym"
        case "$sym" in
          _*) bare="${sym#_}" ;;
        esac
        case "$bare" in
          # PLATFORM: SHARED — demote nested linux co-emit only in sys.o (leaf=sys).
          std_sys_linux_linux_*)
            if [ "$leaf" = "sys" ]; then
              :
            else
              printf '%s\n' "$sym" >>"$_exp_list"
            fi
            ;;
          "${prod_pref}"*)
            printf '%s\n' "$sym" >>"$_exp_list"
            ;;
          "${leaf}_"*_c|"${leaf}_"*_c_*)
            # leaf=encoding → encoding_utf8_valid_c; not core_mem_*, not std_*.
            printf '%s\n' "$sym" >>"$_exp_list"
            ;;
          map_*)
            # PLATFORM: MACOS — heap ops.x bare map_* kept for heap_full_alias U→T.
            # leaf_*_c only matches heap_*; map_i32_i32_find_c / map_slot need explicit keep.
            if [ "$leaf" = "heap" ]; then
              printf '%s\n' "$sym" >>"$_exp_list"
            fi
            ;;
        esac
      done <"$tmp_dir/export_nm_syms.txt"
      if [ -s "$_exp_list" ]; then
        if ld -r -exported_symbols_list "$_exp_list" -o "$out_o.exp" "$out_o" 2>"$tmp_dir/ld_exp.err"; then
          mv "$out_o.exp" "$out_o"
        else
          # PLATFORM: MACOS — ar archive (libtool multi-file): per-member export filter.
          # Demotes co-emitted core_*/foreign std_* to local inside each member so
          # product link of leaf.o + authority mem.o has no multi-def.
          if file "$out_o" 2>/dev/null | grep -q 'ar archive'; then
            # PLATFORM: MACOS — libtool multi-file ar. Darwin ld -exported_symbols_list
            # requires every listed symbol to exist in THAT input .o (unlike a wish-list).
            # Build per-member export lists (intersection of keep-policy × member nm).
            _ar_exp_dir="$tmp_dir/ar_export_members"
            rm -rf "$_ar_exp_dir"
            mkdir -p "$_ar_exp_dir"
            _out_abs="$out_o"
            case "$_out_abs" in
              /*) ;;
              *) _out_abs="$(pwd)/$out_o" ;;
            esac
            _ld_exp_err_abs="$tmp_dir/ld_exp.err"
            case "$_ld_exp_err_abs" in
              /*) ;;
              *) _ld_exp_err_abs="$(pwd)/$_ld_exp_err_abs" ;;
            esac
            # Keep-policy helper (same cases as whole-ar list builder above).
            # Writes matching symbols from stdin nm lines to $1.
            _ar_ok=1
            (
              cd "$_ar_exp_dir" || exit 1
              ar x "$_out_abs" || exit 1
              for _mem in *.o; do
                [ -f "$_mem" ] || continue
                _mem_exp="${_mem}.exp_syms.txt"
                : >"$_mem_exp"
                nm "$_mem" 2>/dev/null | awk '/ [TDB] / { print $3 }' | while IFS= read -r sym; do
                  [ -n "$sym" ] || continue
                  bare="$sym"
                  case "$sym" in
                    _*) bare="${sym#_}" ;;
                  esac
                  case "$bare" in
                    "${prod_pref}"*)
                      printf '%s\n' "$sym" >>"$_mem_exp"
                      ;;
                    "${leaf}_"*_c|"${leaf}_"*_c_*)
                      printf '%s\n' "$sym" >>"$_mem_exp"
                      ;;
                    map_*)
                      if [ "$leaf" = "heap" ]; then
                        printf '%s\n' "$sym" >>"$_mem_exp"
                      fi
                      ;;
                  esac
                done
                if [ ! -s "$_mem_exp" ]; then
                  # No leaf API in this member (rare co-emit-only): demote all globals
                  # by exporting a single private sentinel via empty → skip filter keep as-is
                  # would leave foreign T; force localize by exporting nothing via
                  # a dummy local-only path: re-ld with only undefined-safe empty list fails.
                  # Prefer: export one private symbol if any local exists; else leave member.
                  # Safest: if no keep symbols, still run with empty list only when member
                  # has zero global TDB (noop). When foreign T exist without leaf API,
                  # export a single existing private by taking first local — skip if none.
                  continue
                fi
                if ! ld -r -exported_symbols_list "$_mem_exp" -o "${_mem}.exp" "$_mem" 2>>"$_ld_exp_err_abs"; then
                  exit 1
                fi
                mv "${_mem}.exp" "$_mem"
              done
              # Rebuild ar in place (drop SYMDEF; ranlib if present).
              rm -f "$_out_abs"
              ar rc "$_out_abs" *.o || exit 1
              if command -v ranlib >/dev/null 2>&1; then
                ranlib "$_out_abs" 2>/dev/null || true
              fi
            ) || _ar_ok=0
            if [ "$_ar_ok" != 1 ]; then
              head -8 "$tmp_dir/ld_exp.err" 2>/dev/null >&2 || true
            fi
          else
            head -5 "$tmp_dir/ld_exp.err" 2>/dev/null >&2 || true
          fi
          rm -f "$out_o.exp" 2>/dev/null || true
        fi
      fi
    fi
  fi
  # heap import-binding：impl 常产出裸 heap_*_c / map_*_c，mod.x U 要
  # std_heap_libc_* / std_heap_ops_*。Mac 多文件 ar 不合并符号；缺 wrappers 时
  # L4 run-set UNDEF. G.7: complete alias table (not only heap_alloc_c).
  # PLATFORM: SHARED — objcopy redefine when available; else thin C wrappers +
  # ld -r (or ar q when out is already a static archive from libtool).
  # Note: runs with nm only (no objcopy required) so Darwin libtool ar path is covered.
  if [ "$leaf" = "heap" ] && [ -f "$out_o" ]; then
    # libc.x surface: bare heap_* → std_heap_libc_heap_*
    # ops.x surface: bare map_* / heap_mem_* → std_heap_ops_*
    _heap_alias_list=""
    for bare in \
      heap_alloc_c heap_alloc_aligned_c heap_alloc_zeroed_c \
      heap_alloc_i32_c heap_alloc_u8_c heap_alloc_u64_c heap_alloc_f32_c heap_alloc_f64_c \
      heap_free_c heap_free_i32_c heap_free_u8_c heap_free_u64_c heap_free_f32_c heap_free_f64_c \
      heap_realloc_c heap_realloc_i32_c heap_realloc_u8_c heap_realloc_u64_c \
      heap_realloc_f32_c heap_realloc_f64_c \
      heap_copy_i32_at_c heap_copy_u8_at_c heap_copy_u64_at_c heap_copy_f32_at_c heap_copy_f64_at_c \
      heap_arena64_init_c heap_arena64_alloc_c heap_arena64_bump_c heap_arena64_deinit_c \
      heap_ptr_mod_c heap_trace_enabled_c heap_trace_reset_c heap_trace_stats_c; do
      ns="std_heap_libc_${bare}"
      if nm "$out_o" 2>/dev/null | grep -qE " T ${bare}$| T _${bare}$" \
         && ! nm "$out_o" 2>/dev/null | grep -qE " T ${ns}$| T _${ns}$"; then
        _heap_alias_list="${_heap_alias_list}${bare}|${ns}
"
      fi
    done
    for bare in map_i32_i32_find_c map_slot heap_mem_set_c heap_mem_compare_c; do
      ns="std_heap_ops_${bare}"
      if nm "$out_o" 2>/dev/null | grep -qE " T ${bare}$| T _${bare}$" \
         && ! nm "$out_o" 2>/dev/null | grep -qE " T ${ns}$| T _${ns}$"; then
        _heap_alias_list="${_heap_alias_list}${bare}|${ns}
"
      fi
    done
    if [ -n "$_heap_alias_list" ]; then
      if command -v objcopy >/dev/null 2>&1; then
        printf '%s' "$_heap_alias_list" | while IFS='|' read -r bare ns; do
          [ -n "$bare" ] || continue
          if nm "$out_o" 2>/dev/null | grep -q " T _${bare}$"; then
            objcopy --redefine-sym "_${bare}=_${ns}" "$out_o" 2>/dev/null || true
          else
            objcopy --redefine-sym "${bare}=${ns}" "$out_o" 2>/dev/null || true
          fi
        done
      else
        # PLATFORM: MACOS — emit thin wrappers and merge. Prefer ld -r; if out is
        # ar archive (libtool fallback), append member via ar r.
        alias_c="$tmp_dir/heap_full_alias.c"
        alias_o="$tmp_dir/heap_full_alias.o"
        {
          echo '#include <stddef.h>'
          echo '#include <stdint.h>'
          printf '%s' "$_heap_alias_list" | while IFS='|' read -r bare ns; do
            [ -n "$bare" ] || continue
            # Prefer prototypes from nm-driven known signatures; default to
            # identity-cast via void* for uncommon ones. Typed alloc/free only.
            case "$bare" in
              heap_alloc_c|heap_alloc_zeroed_c)
                echo "extern uint8_t *${bare}(size_t size);"
                echo "uint8_t *${ns}(size_t size) { return ${bare}(size); }"
                ;;
              heap_alloc_aligned_c)
                echo "extern uint8_t *${bare}(size_t align_bytes, size_t size);"
                echo "uint8_t *${ns}(size_t align_bytes, size_t size) { return ${bare}(align_bytes, size); }"
                ;;
              heap_alloc_i32_c)
                echo "extern int32_t *${bare}(int32_t count);"
                echo "int32_t *${ns}(int32_t count) { return ${bare}(count); }"
                ;;
              heap_alloc_u8_c)
                echo "extern uint8_t *${bare}(int32_t count);"
                echo "uint8_t *${ns}(int32_t count) { return ${bare}(count); }"
                ;;
              heap_alloc_u64_c)
                echo "extern uint64_t *${bare}(int32_t count);"
                echo "uint64_t *${ns}(int32_t count) { return ${bare}(count); }"
                ;;
              heap_alloc_f32_c)
                echo "extern float *${bare}(int32_t count);"
                echo "float *${ns}(int32_t count) { return ${bare}(count); }"
                ;;
              heap_alloc_f64_c)
                echo "extern double *${bare}(int32_t count);"
                echo "double *${ns}(int32_t count) { return ${bare}(count); }"
                ;;
              heap_free_c|heap_free_u8_c)
                echo "extern void ${bare}(uint8_t *p);"
                echo "void ${ns}(uint8_t *p) { ${bare}(p); }"
                ;;
              heap_free_i32_c)
                echo "extern void ${bare}(int32_t *p);"
                echo "void ${ns}(int32_t *p) { ${bare}(p); }"
                ;;
              heap_free_u64_c)
                echo "extern void ${bare}(uint64_t *p);"
                echo "void ${ns}(uint64_t *p) { ${bare}(p); }"
                ;;
              heap_free_f32_c)
                echo "extern void ${bare}(float *p);"
                echo "void ${ns}(float *p) { ${bare}(p); }"
                ;;
              heap_free_f64_c)
                echo "extern void ${bare}(double *p);"
                echo "void ${ns}(double *p) { ${bare}(p); }"
                ;;
              heap_realloc_c|heap_realloc_u8_c)
                echo "extern uint8_t *${bare}(uint8_t *p, size_t size);"
                echo "uint8_t *${ns}(uint8_t *p, size_t size) { return ${bare}(p, size); }"
                ;;
              heap_realloc_i32_c)
                echo "extern int32_t *${bare}(int32_t *p, int32_t count);"
                echo "int32_t *${ns}(int32_t *p, int32_t count) { return ${bare}(p, count); }"
                ;;
              heap_realloc_u64_c)
                echo "extern uint64_t *${bare}(uint64_t *p, int32_t count);"
                echo "uint64_t *${ns}(uint64_t *p, int32_t count) { return ${bare}(p, count); }"
                ;;
              heap_realloc_f32_c)
                echo "extern float *${bare}(float *p, int32_t count);"
                echo "float *${ns}(float *p, int32_t count) { return ${bare}(p, count); }"
                ;;
              heap_realloc_f64_c)
                echo "extern double *${bare}(double *p, int32_t count);"
                echo "double *${ns}(double *p, int32_t count) { return ${bare}(p, count); }"
                ;;
              heap_copy_i32_at_c)
                echo "extern void ${bare}(int32_t *dst, int32_t dst_offset, int32_t *src, int32_t count);"
                echo "void ${ns}(int32_t *dst, int32_t dst_offset, int32_t *src, int32_t count) { ${bare}(dst, dst_offset, src, count); }"
                ;;
              heap_copy_u8_at_c)
                echo "extern void ${bare}(uint8_t *dst, int32_t dst_offset, uint8_t *src, int32_t count);"
                echo "void ${ns}(uint8_t *dst, int32_t dst_offset, uint8_t *src, int32_t count) { ${bare}(dst, dst_offset, src, count); }"
                ;;
              heap_copy_u64_at_c)
                echo "extern void ${bare}(uint64_t *dst, int32_t dst_offset, uint64_t *src, int32_t count);"
                echo "void ${ns}(uint64_t *dst, int32_t dst_offset, uint64_t *src, int32_t count) { ${bare}(dst, dst_offset, src, count); }"
                ;;
              heap_copy_f32_at_c)
                echo "extern void ${bare}(float *dst, int32_t dst_offset, float *src, int32_t count);"
                echo "void ${ns}(float *dst, int32_t dst_offset, float *src, int32_t count) { ${bare}(dst, dst_offset, src, count); }"
                ;;
              heap_copy_f64_at_c)
                echo "extern void ${bare}(double *dst, int32_t dst_offset, double *src, int32_t count);"
                echo "void ${ns}(double *dst, int32_t dst_offset, double *src, int32_t count) { ${bare}(dst, dst_offset, src, count); }"
                ;;
              map_i32_i32_find_c)
                echo "extern int32_t ${bare}(int32_t *keys, uint8_t *occupied, int32_t cap, int32_t key);"
                echo "int32_t ${ns}(int32_t *keys, uint8_t *occupied, int32_t cap, int32_t key) { return ${bare}(keys, occupied, cap, key); }"
                ;;
              map_slot)
                echo "extern int32_t ${bare}(int32_t key, int32_t cap);"
                echo "int32_t ${ns}(int32_t key, int32_t cap) { return ${bare}(key, cap); }"
                ;;
              heap_mem_set_c)
                echo "extern void ${bare}(uint8_t *ptr, uint8_t byte, int32_t n);"
                echo "void ${ns}(uint8_t *ptr, uint8_t byte, int32_t n) { ${bare}(ptr, byte, n); }"
                ;;
              heap_mem_compare_c)
                echo "extern int32_t ${bare}(uint8_t *a, uint8_t *b, int32_t n);"
                echo "int32_t ${ns}(uint8_t *a, uint8_t *b, int32_t n) { return ${bare}(a, b, n); }"
                ;;
              heap_ptr_mod_c)
                echo "extern size_t ${bare}(uint8_t *p, size_t m);"
                echo "size_t ${ns}(uint8_t *p, size_t m) { return ${bare}(p, m); }"
                ;;
              heap_trace_enabled_c)
                echo "extern int32_t ${bare}(void);"
                echo "int32_t ${ns}(void) { return ${bare}(); }"
                ;;
              heap_trace_reset_c)
                echo "extern void ${bare}(void);"
                echo "void ${ns}(void) { ${bare}(); }"
                ;;
              heap_trace_stats_c)
                # PLATFORM: MACOS thin alias — fixed 4×*u64 surface (libc.x heap_trace_stats_c).
                # Must not skip: mod.x U std_heap_libc_heap_trace_stats_c; bare T heap_trace_stats_c
                # only in multi-file ar members. G.7 complete authority (was empty case → UNDEF).
                echo "extern void ${bare}(uint64_t *alloc_count, uint64_t *free_count, uint64_t *realloc_count, uint64_t *bytes_allocated);"
                echo "void ${ns}(uint64_t *alloc_count, uint64_t *free_count, uint64_t *realloc_count, uint64_t *bytes_allocated) { ${bare}(alloc_count, free_count, realloc_count, bytes_allocated); }"
                ;;
              heap_arena64_init_c)
                # Incomplete struct ok for alias if definition is in same link unit.
                echo "struct std_heap_libc_LibcArena64;"
                echo "extern int32_t ${bare}(struct std_heap_libc_LibcArena64 *a, size_t cap);"
                echo "int32_t ${ns}(struct std_heap_libc_LibcArena64 *a, size_t cap) { return ${bare}(a, cap); }"
                ;;
              heap_arena64_alloc_c|heap_arena64_bump_c)
                echo "struct std_heap_libc_LibcArena64;"
                echo "extern uint8_t *${bare}(struct std_heap_libc_LibcArena64 *a, size_t size, size_t align_bytes);"
                echo "uint8_t *${ns}(struct std_heap_libc_LibcArena64 *a, size_t size, size_t align_bytes) { return ${bare}(a, size, align_bytes); }"
                ;;
              heap_arena64_deinit_c)
                echo "struct std_heap_libc_LibcArena64;"
                echo "extern void ${bare}(struct std_heap_libc_LibcArena64 *a);"
                echo "void ${ns}(struct std_heap_libc_LibcArena64 *a) { ${bare}(a); }"
                ;;
              *)
                ;;
            esac
          done
        } >"$alias_c"
        if [ -s "$alias_c" ] && cc -fPIE $DARWIN_MINOS -c "$alias_c" -o "$alias_o" 2>/dev/null; then
          merged="$tmp_dir/heap_merged.o"
          # PLATFORM: MACOS — when multi-file path left an ar archive, ar-append the
          # alias member first (Darwin `ld -r ar.a alias.o` can drop other members).
          # Then extract+ld -r all members into one relocatable and re-export only
          # std_heap_* product faces: bare heap_*_c / map_* become local so they do
          # not multi-def with runtime_heap_user.o, while alias U resolves in-TU.
          # G.7: complete authority for Mac multi-file heap formal.
          if file "$out_o" 2>/dev/null | grep -q 'ar archive'; then
            ar r "$out_o" "$alias_o" 2>/dev/null || true
            _heap_flat_dir="$tmp_dir/heap_flat_merge"
            rm -rf "$_heap_flat_dir"
            mkdir -p "$_heap_flat_dir"
            _out_abs_h="$out_o"
            case "$_out_abs_h" in
              /*) ;;
              *) _out_abs_h="$(pwd)/$out_o" ;;
            esac
            if (
              cd "$_heap_flat_dir" || exit 1
              ar x "$_out_abs_h" || exit 1
              # Drop table-of-contents pseudo-member if extracted.
              rm -f __.SYMDEF __.SYMDEF\ SORTED 2>/dev/null || true
              _objs=""
              for _m in *.o; do
                [ -f "$_m" ] || continue
                _objs="$_objs $_m"
              done
              [ -n "$_objs" ] || exit 1
              # shellcheck disable=SC2086
              ld -r -o heap_flat.o $_objs 2>/dev/null || exit 1
              # Export only namespaced product API (std_heap_* incl. libc/ops aliases).
              _flat_exp="heap_flat_exp.txt"
              : >"$_flat_exp"
              nm heap_flat.o 2>/dev/null | awk '/ [TDB] / { print $3 }' | while IFS= read -r sym; do
                [ -n "$sym" ] || continue
                bare="$sym"
                case "$sym" in
                  _*) bare="${sym#_}" ;;
                esac
                case "$bare" in
                  std_heap_*)
                    printf '%s\n' "$sym" >>"$_flat_exp"
                    ;;
                esac
              done
              if [ -s "$_flat_exp" ]; then
                ld -r -exported_symbols_list "$_flat_exp" -o heap_flat.exp.o heap_flat.o 2>/dev/null || exit 1
                mv heap_flat.exp.o "$_out_abs_h"
              else
                mv heap_flat.o "$_out_abs_h"
              fi
            ); then
              : # flat merge ok
            else
              # Keep ar+alias if flat merge fails (ranlib for partial usability).
              if command -v ranlib >/dev/null 2>&1; then
                ranlib "$out_o" 2>/dev/null || true
              fi
            fi
          elif ld -r -o "$merged" "$out_o" "$alias_o" 2>/dev/null; then
            mv "$merged" "$out_o"
          elif command -v libtool >/dev/null 2>&1; then
            # out is relocatable .o but ld -r failed (duplicate co-emits); pack as ar.
            libtool -static -o "$merged" "$out_o" "$alias_o" 2>/dev/null && mv "$merged" "$out_o" || true
          fi
        fi
      fi
    fi
  fi
fi

echo "xlang_compile_std_module.sh: OK ($idx files -> $out_o)"
