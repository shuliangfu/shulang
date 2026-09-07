/* seeds/runtime_process_argv.from_x.c — G-02f-20 product TU
 * G-02f-106 helper gates.
 * Product: runtime_process_argv.o; logic still C until full .x port.
 */
/**
 * runtime_process_argv.c — codegen 入口 argc/argv 全局（F-ZC：自 std/process/process_arg_glue.c 迁入）
 *
 * C codegen 路径：main(int argc, char **argv) 在入口处赋值。
 * asm 用户程序 main() 无参时：constructor 从 CRT 读取 argc/argv（macOS _NSGetArgc、Linux /proc/self/cmdline）。
 * std/process/process.x 经 process_xlang_argc_get / process_xlang_argv_get 读取。
 */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_proc_cap.h> /* Cap residual 9.5.5: /proc read face (bounded, seek-free) */
#if defined(__APPLE__)
#include <crt_externs.h>
#endif


/** 由 codegen 或 xlang_process_argv_bind_from_crt 写入；供 process.x 经 getter 读取。 */
int xlang_process_argc = 0;
char **xlang_process_argv = NULL;

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
void xlang_process_argv_bind_from_crt(void);

/**
 * Bind argc/argv from the C runtime (asm user main without parameters, or
 * gcc -pie linked images). No-op when codegen already wrote both globals.
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void xlang_process_argv_bind_from_crt_impl(void) {
  if (xlang_process_argc > 0 && xlang_process_argv != NULL)
    return;
#if defined(__APPLE__)
  xlang_process_argc = *_NSGetArgc();
  xlang_process_argv = *_NSGetArgv();
#elif defined(__linux__)
  {
    /* /proc/self/cmdline does not support SEEK_END/ftell (reports 0), so the
     * former fopen/fread loop had to read in chunks; the old silent no-op on
     * ftell==0 left argc permanently 0 (bstrict31 run-process args).
     * Cap residual 9.5.5: the chunked read now comes from the 9.1.12 Cap
     * authority xlang_proc_read_file_bounded (seek-free, 1 MiB bound); -2
     * (cmdline larger than the bound) aborts loudly-ish exactly like the old
     * hand-rolled over-1MiB bailout — argc/argv stay unbound. */
    char *cmdline;
    long n;
    int argc;
    char **argv;
    char *p;
    cmdline = (char *)malloc(1024 * 1024);
    if (!cmdline)
      return;
    n = xlang_proc_read_file_bounded("/proc/self/cmdline", cmdline, 1024 * 1024);
    if (n <= 0) {
      free(cmdline);
      return;
    }
    argc = 0;
    for (p = cmdline; p < cmdline + n; p++) {
      if (*p != '\0')
        continue;
      argc++;
      if (p + 1 >= cmdline + n)
        break;
    }
    if (argc <= 0) {
      free(cmdline);
      return;
    }
    argv = (char **)calloc((size_t)argc + 1, sizeof(char *));
    if (!argv) {
      free(cmdline);
      return;
    }
    {
      int i = 0;
      p = cmdline;
      while (p < cmdline + n && i < argc) {
        argv[i++] = p;
        while (p < cmdline + n && *p != '\0')
          p++;
        p++;
      }
      xlang_process_argc = argc;
      xlang_process_argv = argv;
      /* cmdline buffer is kept alive: argv[] points into it, never freed. */
    }
  }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_ARGV_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/runtime_process_argv.x）提供 wrapper 调用 _impl */
void xlang_process_argv_bind_from_crt(void) { xlang_process_argv_bind_from_crt_impl(); }
#endif /* XLANG_RUNTIME_PROCESS_ARGV_FROM_X */




/** asm 用户程序：main 前绑定 argc/argv（优先级低于 codegen 显式赋值）。 */
__attribute__((constructor(65535))) static void xlang_process_argv_ctor_bind(void) {
  xlang_process_argv_bind_from_crt();
}

/**
 * 供 process.x 读取 argc（避免 .x 直接绑全局符号）。
 * 返回值：当前进程 argc（int32）。
 */
int32_t process_xlang_argc_get(void) {
    return (int32_t)xlang_process_argc;
}

/**
 * 供 process.x 读取 argv[i]；越界返回 NULL。
 * 参数：i 参数索引。
 * 返回值：argv[i] 指针或 NULL。
 */
uint8_t *process_xlang_argv_get(int32_t i) {
    if (xlang_process_argv == NULL || i < 0 || (int)i >= xlang_process_argc)
        return NULL;
    return (uint8_t *)xlang_process_argv[i];
}

/**
 * std/process/process.x 同名热路径；weak fallback 供 minimal 链（C -o 路径不经 process.x 编译时）。
 * 【Why 根源】process.x 编译出强符号 process_args_count_c；本 TU 经 ld -r 合并进 process.o
 * 时若也是强符号 → duplicate symbol。weak 让链接器优先选 process.x 强符号，本定义仅在
 * 未链 process.o 的 minimal 场景下被解析。
 * 【Invariant】weak 定义与 process.x 强符号实现等价（都转调 process_xlang_argc_get），
 * 覆盖与否不影响行为。
 * 返回值：命令行参数个数（含 argv[0]）。
 */
XLANG_WEAK int32_t process_args_count_c(void) {
    return process_xlang_argc_get();
}

/**
 * std/process/process.x 同名热路径；weak fallback（见上 process_args_count_c 说明）。
 * 【Why】同上 — 让 process.x 强符号覆盖，避免 ld -r 合并 duplicate symbol。
 * 参数：i — 参数索引。
 * 返回值：argv[i] C 字符串指针；越界返回 NULL。
 */
XLANG_WEAK uint8_t *process_arg_c(int32_t i) {
    return process_xlang_argv_get(i);
}
