/* seeds/labi_std_list.from_x.c — G-02f-271 P2 link_abi L8 std list pure → R2 full
 * Logic source: src/runtime/labi_std_list.x
 * Hybrid: XLANG_LABI_STD_LIST_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供：
 *   labi_std_plan_count
 *   labi_std_plan_step_at
 *   labi_std_default_std_rel_count
 *   labi_std_default_std_rel_at
 * Cap residual：IO/ensure/push 仍在 mega xlang_asm_ld_append_std_objs。
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 */
#include <stddef.h>

#ifndef XLANG_LABI_STD_LIST_FROM_X

/* Ops — keep in sync with mega interpreter in runtime_link_abi.from_x.c
 * STD=1 IO_STUBS=2 PRIMARY_PANIC=3 TIME_OS=4 RANDOM_FILL=5 ENV_OS=6
 * GLUE_THREAD=10 SYNC=11 CRYPTO=12 LOG=13 ATOMIC=14 CHANNEL=15 BACKTRACE=16
 * MATH=17 SQLITE=18 DYNLIB=19 HTTP=20 TASK_SPECIAL=30
 */

int labi_std_plan_count(void) {
  /* PLATFORM: SHARED — was 60; +option +result (=heavy return 62). */
  return 62;
}

int labi_std_plan_step_at(int i, int *op_out, const char **rel_out, int *flag_kind_out) {
  if (i < 0)
    return 0;
  if (i >= 62)
    return 0;
  if (i == 0) {
    if (op_out)
      *op_out = 2;
    if (rel_out)
      *rel_out = "compiler/runtime_asm_io_stubs.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 1) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/process/process.o";
    if (flag_kind_out)
      *flag_kind_out = 1;
    return 1;
  }
  if (i == 2) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/string/string.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 3) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/path/path.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 4) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/runtime/runtime.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 5) {
    if (op_out)
      *op_out = 3;
    if (rel_out)
      *rel_out = "compiler/runtime_panic.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 6) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/thread/thread.o";
    if (flag_kind_out)
      *flag_kind_out = 2;
    return 1;
  }
  if (i == 7) {
    if (op_out)
      *op_out = 10;
    if (rel_out)
      *rel_out = "compiler/runtime_thread_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 8) {
    if (op_out)
      *op_out = 4;
    if (rel_out)
      *rel_out = "compiler/runtime_time_os.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 9) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/time/time.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 10) {
    if (op_out)
      *op_out = 5;
    if (rel_out)
      *rel_out = "compiler/runtime_random_fill.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 11) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/random/random.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 12) {
    if (op_out)
      *op_out = 6;
    if (rel_out)
      *rel_out = "compiler/runtime_env_os.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 13) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/env/env.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 14) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/sync/sync.o";
    if (flag_kind_out)
      *flag_kind_out = 3;
    return 1;
  }
  if (i == 15) {
    if (op_out)
      *op_out = 11;
    if (rel_out)
      *rel_out = "compiler/runtime_sync_lock_diag_tls.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 16) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/encoding/encoding.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 17) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/base64/base64.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 18) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/crypto/crypto.o";
    if (flag_kind_out)
      *flag_kind_out = 4;
    return 1;
  }
  if (i == 19) {
    if (op_out)
      *op_out = 12;
    if (rel_out)
      *rel_out = "compiler/runtime_ed25519_ref10_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 20) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/log/log.o";
    if (flag_kind_out)
      *flag_kind_out = 5;
    return 1;
  }
  if (i == 21) {
    if (op_out)
      *op_out = 13;
    if (rel_out)
      *rel_out = "compiler/runtime_log_os.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 22) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/atomic/atomic.o";
    if (flag_kind_out)
      *flag_kind_out = 6;
    return 1;
  }
  if (i == 23) {
    if (op_out)
      *op_out = 14;
    if (rel_out)
      *rel_out = "compiler/runtime_atomic_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 24) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/channel/channel.o";
    if (flag_kind_out)
      *flag_kind_out = 7;
    return 1;
  }
  if (i == 25) {
    if (op_out)
      *op_out = 15;
    if (rel_out)
      *rel_out = "compiler/runtime_channel_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 26) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/backtrace/backtrace.o";
    if (flag_kind_out)
      *flag_kind_out = 8;
    return 1;
  }
  if (i == 27) {
    if (op_out)
      *op_out = 16;
    if (rel_out)
      *rel_out = "compiler/runtime_backtrace_platform.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 28) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/hash/hash.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 29) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/math/math.o";
    if (flag_kind_out)
      *flag_kind_out = 9;
    return 1;
  }
  if (i == 30) {
    if (op_out)
      *op_out = 17;
    if (rel_out)
      *rel_out = "compiler/runtime_math_libm.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 31) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/sort/sort.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 32) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/ffi/ffi.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 33) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/db/sqlite/sqlite.o";
    if (flag_kind_out)
      *flag_kind_out = 10;
    return 1;
  }
  if (i == 34) {
    if (op_out)
      *op_out = 18;
    if (rel_out)
      *rel_out = "compiler/runtime_sqlite_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 35) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/elf/elf.o";
    if (flag_kind_out)
      *flag_kind_out = 11;
    return 1;
  }
  if (i == 36) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/json/json.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 37) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/csv/csv.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 38) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/regex/regex.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 39) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/unicode/unicode.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 40) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/dynlib/dynlib.o";
    if (flag_kind_out)
      *flag_kind_out = 12;
    return 1;
  }
  if (i == 41) {
    if (op_out)
      *op_out = 19;
    if (rel_out)
      *rel_out = "compiler/runtime_dynlib_os.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 42) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/http/http.o";
    if (flag_kind_out)
      *flag_kind_out = 13;
    return 1;
  }
  if (i == 43) {
    if (op_out)
      *op_out = 20;
    if (rel_out)
      *rel_out = "compiler/runtime_http_glue.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 44) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/socketio/socketio.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 45) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/tar/tar.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 46) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/simd/simd.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 47) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/context/context.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 48) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/error/error.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 49) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/datetime/datetime.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 50) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/uuid/uuid.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 51) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/url/url.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 52) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/cli/cli.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 53) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/security/security.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 54) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/config/config.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 55) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/cache/cache.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 56) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/trace/trace.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  /* PLATFORM: SHARED — std.vec link_only product .o; fk0 UNDEF gate in mega. */
  if (i == 57) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/vec/vec.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  /* PLATFORM: SHARED — formal fs.o (mod.x+posix.x); asm skips std.fs co-emit; fk0 gated. */
  if (i == 58) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/fs/fs.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  /* PLATFORM: SHARED — std/option/option.o (STD-080); fk0 gated std_option_*. */
  if (i == 59) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/option/option.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  /* PLATFORM: SHARED — std/result/result.o (STD-081); fk0 gated std_result_*. */
  if (i == 60) {
    if (op_out)
      *op_out = 1;
    if (rel_out)
      *rel_out = "std/result/result.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  if (i == 61) {
    if (op_out)
      *op_out = 30;
    if (rel_out)
      *rel_out = "std/task/task.o";
    if (flag_kind_out)
      *flag_kind_out = 0;
    return 1;
  }
  return 0;
}

/* Pure: count of OP_STD entries with std/ prefix (audit / unit). */
int labi_std_default_std_rel_count(void) {
  /* PLATFORM: SHARED — was 43; +option +result (=heavy return 45). */
  return 45;
}

const char *labi_std_default_std_rel_at(int j) {
  if (j < 0)
    return NULL;
  if (j == 0)
    return "std/process/process.o";
  if (j == 1)
    return "std/string/string.o";
  if (j == 2)
    return "std/path/path.o";
  if (j == 3)
    return "std/runtime/runtime.o";
  if (j == 4)
    return "std/thread/thread.o";
  if (j == 5)
    return "std/time/time.o";
  if (j == 6)
    return "std/random/random.o";
  if (j == 7)
    return "std/env/env.o";
  if (j == 8)
    return "std/sync/sync.o";
  if (j == 9)
    return "std/encoding/encoding.o";
  if (j == 10)
    return "std/base64/base64.o";
  if (j == 11)
    return "std/crypto/crypto.o";
  if (j == 12)
    return "std/log/log.o";
  if (j == 13)
    return "std/atomic/atomic.o";
  if (j == 14)
    return "std/channel/channel.o";
  if (j == 15)
    return "std/backtrace/backtrace.o";
  if (j == 16)
    return "std/hash/hash.o";
  if (j == 17)
    return "std/math/math.o";
  if (j == 18)
    return "std/sort/sort.o";
  if (j == 19)
    return "std/ffi/ffi.o";
  if (j == 20)
    return "std/db/sqlite/sqlite.o";
  if (j == 21)
    return "std/elf/elf.o";
  if (j == 22)
    return "std/json/json.o";
  if (j == 23)
    return "std/csv/csv.o";
  if (j == 24)
    return "std/regex/regex.o";
  if (j == 25)
    return "std/unicode/unicode.o";
  if (j == 26)
    return "std/dynlib/dynlib.o";
  if (j == 27)
    return "std/http/http.o";
  if (j == 28)
    return "std/socketio/socketio.o";
  if (j == 29)
    return "std/tar/tar.o";
  if (j == 30)
    return "std/simd/simd.o";
  if (j == 31)
    return "std/context/context.o";
  if (j == 32)
    return "std/error/error.o";
  if (j == 33)
    return "std/datetime/datetime.o";
  if (j == 34)
    return "std/uuid/uuid.o";
  if (j == 35)
    return "std/url/url.o";
  if (j == 36)
    return "std/cli/cli.o";
  if (j == 37)
    return "std/security/security.o";
  if (j == 38)
    return "std/config/config.o";
  if (j == 39)
    return "std/cache/cache.o";
  if (j == 40)
    return "std/trace/trace.o";
  if (j == 41)
    return "std/vec/vec.o";
  if (j == 42)
    return "std/fs/fs.o";
  if (j == 43)
    return "std/option/option.o";
  if (j == 44)
    return "std/result/result.o";
  return NULL;
}

#else
int labi_std_plan_count(void);
int labi_std_plan_step_at(int i, int *op_out, const char **rel_out, int *flag_kind_out);
int labi_std_default_std_rel_count(void);
const char *labi_std_default_std_rel_at(int j);
#endif

int labi_std_list_slice_marker(void) {
  return 1;
}

