/* seeds/rt_run_exec.from_x.c — G-02f-297～299/311 P2 runtime R7 (run/exec gates)
 * Logic source: src/runtime/rt_run_exec.x
 * Hybrid: XLANG_RT_RUN_EXEC_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：8 公共业务符号均由 .x 提供；
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务符号 H=0）。
 * Cap residual：driver_print_usage_write 在 driver_abi（巨型 usage 字面量）。
 * 冷启动/无 PREFER 时仍编译完整 C 体。
 *
 * f-297: want_asm_emit_to_file + print_usage
 * f-298: runtime_test_status_to_rc + print_target_cpu_features
 * f-299: exec pure path helpers + driver_exec_compiled (spawn)
 * f-311: driver_run_test（bash tests/run-all.sh；wave226 → link_abi_system）
 */
#include <stddef.h>
#include <stdint.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: run-test cmd path → Cap snprintf */
/* G.7: Cap snprintf mapping (no libc stdio since 9.7.2). */
#undef snprintf
#define snprintf xlang_snprintf
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <process.h>
#endif

#include "runtime_diag_codes.h"

#include <stdlib.h>

extern int driver_get_argv_i(int argc, char **argv, int i, char *buf, int max);
extern void runtime_diag_errno_path(const char *file, const char *kind, const char *op, const char *path);
extern void diag_reportf_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                   const char *detail, const char *fmt, ...);
extern void diag_reportf(const char *file, int line, int col, const char *kind, const char *detail, const char *fmt,
                         ...);
extern void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                  const char *msg, const char *detail);
/* Cap residual 9.7.2: fd-handle face — print goes through driver_stdio_stdout
 * (encoded fd 1), no libc FILE star / stdout. */
extern void xlang_target_cpu_print(uint8_t *out, uint32_t features);
extern uint8_t *driver_stdio_stdout(void);
extern int xlang_waitpid_retry(pid_t pid, int *status_out);
extern const char *xlang_repo_root_from_argv0(const char *argv0);
/* wave226 G.7: bash test shell via public pure thin link_abi_system (wave224 → _impl host system). */
extern int link_abi_system(const char *cmd);
extern void driver_print_usage_write(void);

#ifndef XLANG_RT_RUN_EXEC_FROM_X

/**
 * 是否与 driver_run_compiler_full 默认一致：默认可走 asm 后端；
 * 仅当 argv 含 `-backend c` 时为 0。
 */
int driver_want_asm_emit_to_file(int argc, char **argv) {
  int want_asm = 1;
  char cur[512];
  char nx[512];
  int i;
  if (!argv || argc < 2)
    return 0;
  for (i = 1; i < argc; i++) {
    if (driver_get_argv_i(argc, argv, i, cur, (int)sizeof cur) < 0)
      continue;
    if (strcmp(cur, "-backend") != 0)
      continue;
    if (i + 1 >= argc)
      break;
    if (driver_get_argv_i(argc, argv, i + 1, nx, (int)sizeof nx) < 0) {
      i++;
      continue;
    }
    if (strcmp(nx, "c") == 0)
      want_asm = 0;
    if (strcmp(nx, "asm") == 0)
      want_asm = 1;
    i++;
  }
  return want_asm ? 1 : 0;
}

/**
 * 打印 xlang 用法摘要（fd 1）。
 * Cap residual driver_print_usage_write 持巨型字面量。
 */
void driver_print_usage_c(void) {
  driver_print_usage_write();
}

/* --- G-02f-298 --- */

/** wait/system 状态 → 进程 rc；失败路径写诊断（diag 仍 extern）。 */
int runtime_test_status_to_rc(const char *script, int st) {
  if (st == -1) {
    runtime_diag_errno_path(script, "process error", "system(xlang test)", script);
    return 1;
  }
  if (WIFEXITED(st))
    return WEXITSTATUS(st) != 0 ? 1 : 0;
  if (WIFSIGNALED(st)) {
    diag_reportf_with_code(script, 0, 0, "process error", XLANG_DIAG_CODE_PROCESS_PRC001, NULL,
                           "test script terminated by signal %d: '%s'", WTERMSIG(st), script ? script : "?");
    return 1;
  }
  diag_reportf_with_code(script, 0, 0, "process error", XLANG_DIAG_CODE_PROCESS_PRC001, NULL,
                         "test script terminated abnormally: '%s'", script ? script : "?");
  return 1;
}

/** X run_compiler_full_x：`--print-target-cpu` 早退打印 feature。 */
int32_t driver_print_target_cpu_features_c(int32_t features) {
  xlang_target_cpu_print(driver_stdio_stdout(), (uint32_t)features);
  return 0;
}

/* --- G-02f-299: exec path pure + driver_exec_compiled --- */

/** 从 argv 扫描 `-o` 下一参数；缺省 `"a.out"`（可能指向 argv 槽或静态字面量）。 */
const char *driver_exec_scan_out_path(int argc, char **argv) {
  int i;
  if (!argv || argc < 1)
    return "a.out";
  for (i = 1; i < argc - 1; i++) {
    if (argv[i] && strcmp(argv[i], "-o") == 0 && argv[i + 1] && argv[i + 1][0])
      return argv[i + 1];
  }
  return "a.out";
}

/**
 * 路径是否为不应 exec 的对象/汇编产物（.o/.O/.obj/.s）。
 * 与 xlang_output_want_exe 后缀规则对齐。
 */
int driver_exec_path_is_non_exe(const char *exe) {
  size_t n;
  if (!exe)
    return 1;
  n = strlen(exe);
  if (n >= 2 && exe[n - 2] == '.' && (exe[n - 1] == 'o' || exe[n - 1] == 'O'))
    return 1;
  if (n >= 4 && exe[n - 4] == '.' && exe[n - 3] == 'o' && exe[n - 2] == 'b' && exe[n - 1] == 'j')
    return 1;
  if (n >= 2 && exe[n - 2] == '.' && exe[n - 1] == 's')
    return 1;
  return 0;
}

/**
 * cmd_run：编译成功后 exec 产物。spawn/fork 为 🔒 OS 路径，留在本 seed（冷启动）。
 */
int driver_exec_compiled(int argc, uint8_t *argv_opaque) {
  char **argv = (char **)argv_opaque;
  const char *exe;

  if (!argv || argc < 1)
    return 1;
  exe = driver_exec_scan_out_path(argc, argv);
  if (driver_exec_path_is_non_exe(exe))
    return 0;
  {
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    char *av[2];
    intptr_t rc;
    av[0] = (char *)exe;
    av[1] = NULL;
    rc = _spawnvp(_P_WAIT, exe, (const char *const *)av);
    if (rc == -1) {
      runtime_diag_errno_path(NULL, "process error", "spawnvp (driver_exec_compiled)", exe);
      return 1;
    }
    return (int)rc;
#else
    pid_t pid = fork();
    if (pid < 0) {
      runtime_diag_errno_path(NULL, "process error", "fork (driver_exec_compiled)", exe);
      return 1;
    }
    if (pid == 0) {
      char *av[2];
      av[0] = (char *)exe;
      av[1] = NULL;
      execv(exe, av);
      runtime_diag_errno_path(NULL, "process error", "execv (driver_exec_compiled)", exe);
      _exit(127);
    }
    {
      int st = 0;
      if (xlang_waitpid_retry(pid, &st) != 0)
        return 1;
      if (WIFEXITED(st))
        return WEXITSTATUS(st);
      return 1;
    }
#endif
  }
}

/**
 * xlang test：在仓库根执行 bash 测试脚本。
 * wave226 G.7: public pure thin link_abi_system (not raw libc system);
 * Cap residual host system stays only link_abi_system_impl.
 * PLATFORM: SHARED orch / host shell boundary.
 */
int driver_run_test(int argc, char **argv) {
  const char *root = xlang_repo_root_from_argv0(argc > 0 ? argv[0] : NULL);
  const char *rel = "tests/run-all.sh";
  char script[768];
  char cmd[1024];
  if (argc >= 2 && argv[1] && argv[1][0] != '-') {
    rel = argv[1];
  }
  if (rel[0] == '/')
    snprintf(script, sizeof script, "%s", rel);
  else
    snprintf(script, sizeof script, "%s/%s", root, rel);
  snprintf(cmd, sizeof cmd, "cd \"%s\" && bash \"%s\"", root, script);
  diag_reportf(NULL, 0, 0, "info", NULL, "test script: %s", script);
  /* wave226 G.7: link_abi_system (not raw system). */
  return runtime_test_status_to_rc(script, link_abi_system(cmd));
}

#else /* XLANG_RT_RUN_EXEC_FROM_X：产品 rest 仅 marker；业务符号由 full .x 提供 */

int driver_want_asm_emit_to_file(int argc, char **argv);
void driver_print_usage_c(void);
int runtime_test_status_to_rc(const char *script, int st);
int32_t driver_print_target_cpu_features_c(int32_t features);
const char *driver_exec_scan_out_path(int argc, char **argv);
int driver_exec_path_is_non_exe(const char *exe);
int driver_exec_compiled(int argc, uint8_t *argv_opaque);
int driver_run_test(int argc, char **argv);

#endif /* XLANG_RT_RUN_EXEC_FROM_X */

int labi_rt_run_exec_slice_marker(void) {
  return 1;
}
