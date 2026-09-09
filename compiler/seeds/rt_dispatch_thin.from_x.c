/* seeds/rt_dispatch_thin.from_x.c — G-02f-312 P2 runtime rest → R2 full (dispatch thin)
 * Logic source: src/runtime/rt_dispatch_thin.x
 * Hybrid: XLANG_RT_DISPATCH_THIN_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供：
 *   driver_run_asm_backend_c / driver_run_emit_c_path_c /
 *   driver_run_compiler_full / driver_try_compile_via_shu_c_sibling
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual（driver_abi）：sibling path/access/fork/exec（🔒）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（含非 product ifdef）。
 *
 * Scope:
 *  - driver_run_asm_backend_c / driver_run_emit_c_path_c 兼容旧名薄门闩
 *  - driver_run_compiler_full 入口选择
 *  - driver_try_compile_via_shu_c_sibling（fork/exec 同目录 xlang-c）🔒
 *    mega leftover sibling → _impl wrapper retired (residual 9);
 *    this public name stays here (product T). Do not delete.
 * impl_c / parsed 巨石在其它 R2 切片。
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <process.h>
#endif

extern int driver_argv0_basename_is(const char *argv0, const char *base);
extern int32_t driver_run_asm_backend_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                             int32_t argc, uint8_t *argv);
extern int32_t driver_run_emit_c_path_impl_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                             uint8_t *opt_level, int32_t use_lto, int32_t argc, uint8_t *argv);
extern int32_t driver_run_compiler_full_x_impl_c(int32_t argc, uint8_t *argv);

#ifndef XLANG_RT_DISPATCH_THIN_FROM_X

/** 兼容旧符号名；新路径 compile.x 经 compile_dispatch_* 调 impl_c。 */
int32_t driver_run_asm_backend_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target, int32_t argc,
                                 uint8_t *argv) {
  return driver_run_asm_backend_impl_c(input_path, out_path, lib_key, target, argc, argv);
}

/** 兼容旧符号名；新路径 compile.x 经 compile_dispatch_* 调 impl_c。 */
int32_t driver_run_emit_c_path_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                 uint8_t *opt_level, int32_t use_lto, int32_t argc, uint8_t *argv) {
  return driver_run_emit_c_path_impl_c(input_path, out_path, lib_key, target, opt_level, use_lto, argc, argv);
}

/**
 * 完整编译入口：B-strict / product 走 impl_c。
 */
int driver_run_compiler_full(int argc, char **argv) {
#if defined(XLANG_ASM_USE_COMPILER_IMPL_C)
  return (int)driver_run_compiler_full_x_impl_c((int32_t)argc, (uint8_t *)argv);
#else
  extern int32_t driver_run_compiler_full_x(int32_t argc, uint8_t *argv);
  return (int)driver_run_compiler_full_x((int32_t)argc, (uint8_t *)argv);
#endif
}

/**
 * 含 import 时 seed X codegen 易重复符号；若同目录有 xlang-c 则委托其完成 -o 链接。
 * 返回 ≥0 为子进程 exit；-1 表示未委托（继续本进程路径）。
 * 🔒 fork/exec/_spawnvp。
 */
int driver_try_compile_via_shu_c_sibling(int argc, char **argv) {
  char xlang_c[512];
  const char *self;
  const char *slash;
  if (argc < 2 || !argv || !argv[0])
    return -1;
  /* 已在 xlang-c 内：勿 fork 自身。 */
  if (driver_argv0_basename_is(argv[0], "xlang-c"))
    return -1;
  self = argv[0];
  slash = strrchr(self, '/');
#if defined(_WIN32)
  {
    const char *bs = strrchr(self, '\\');
    if (bs && (!slash || bs > slash))
      slash = bs;
  }
#endif
  if (slash) {
    size_t dir_len = (size_t)(slash - self);
    if (dir_len >= sizeof(xlang_c) - 8)
      return -1;
    memcpy(xlang_c, self, dir_len);
    xlang_c[dir_len] = '\0';
    strcat(xlang_c, "/xlang-c");
  } else {
    strcpy(xlang_c, "xlang-c");
  }
  if (access(xlang_c, X_OK) != 0)
    return -1;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
  {
    argv[0] = xlang_c;
    intptr_t rc = _spawnvp(_P_WAIT, xlang_c, (const char *const *)argv);
    if (rc == -1)
      return -1;
    return (int)rc;
  }
#else
  {
    pid_t pid = fork();
    if (pid < 0)
      return -1;
    if (pid == 0) {
      argv[0] = xlang_c;
      execvp(xlang_c, argv);
      _exit(127);
    }
    {
      int st = 0;
      if (waitpid(pid, &st, 0) < 0)
        return -1;
      if (WIFEXITED(st))
        return WEXITSTATUS(st);
      return 1;
    }
  }
#endif
}

#else
int32_t driver_run_asm_backend_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target, int32_t argc,
                                 uint8_t *argv);
int32_t driver_run_emit_c_path_c(uint8_t *input_path, uint8_t *out_path, uint8_t *lib_key, uint8_t *target,
                                 uint8_t *opt_level, int32_t use_lto, int32_t argc, uint8_t *argv);
int driver_run_compiler_full(int argc, char **argv);
int driver_try_compile_via_shu_c_sibling(int argc, char **argv);
#endif

int labi_rt_dispatch_thin_slice_marker(void) {
  return 1;
}
