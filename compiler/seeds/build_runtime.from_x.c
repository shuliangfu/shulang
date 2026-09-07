/* seeds/build_runtime.from_x.c — G-02f-81 product cold-start TU
 * G-02f-111 helper gates.
 * G-02f-105 helper gates.
 * Promoted from compiler/src/build_runtime.inc (build.x C backend).
 */
/**
 * build_runtime.inc — build.x（Zig build.zig 类比）的 C 执行后端
 *
 * 职责：提供 main() 按 ../build.x 的 build_get_step_count() 与 build_get_step_at()（见 build_runtime.inc 与 build.x）顺序执行；
 * build_run_step(step_id, xlang_path) 跑「默认路径」（.x → *_gen.c → cc）；build_run_asm_build() 调 scripts/build_xlang_asm.sh（机器码路径）。
 * argv[1]=xlang 可执行路径，argv[2]=asm 时只做 asm 路径、不跑默认步骤。
 * 约定：在 compiler 目录运行 build_tool；具体命令字符串集中在本文件，策略与路线图写在 build.x 顶注释。
 * 长期目标：Makefile 仅兜底；日常以 ./build_tool ./xlang 与 ./build_tool ./xlang asm 为准（见 build.x「去掉 Makefile 的爬梯」）。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: build_runtime cmd format → Cap snprintf */
#include <xlang_io_cap.h>  /* Cap residual 9.5.5: write-back face (open_write/io_write) */
#include <xlang_proc_cap.h> /* Cap residual 9.5.5: bounded whole-file read face */
/* G.7: Cap after stdio for product cold-start build_runtime TU. */
#undef snprintf
#define snprintf xlang_snprintf
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#include "diag.h"

/* wave250 G.7: shell via public pure thin link_abi_system (wave224 → _impl host system);
 * not raw libc system. Cap residual host system stays only link_abi_system_impl.
 * PLATFORM: SHARED — build_runtime cold seed shell face; host residual via single face. */
extern int link_abi_system(const char *cmd);

#define PIPELINE_GEN_PATCH_BUF_SIZE (512 * 1024)

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
void build_runtime_info(const char *msg);
void build_runtime_warn(const char *msg);
int build_patch_pipeline_gen_c(void);
int build_patch_driver_gen_c(void);
int build_run_legacy_steps(const char *xlang_path);

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
void build_runtime_info_impl(const char *msg) {
  diag_report(NULL, 0, 0, "info", msg ? msg : "build step complete", NULL);
}


/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */


void build_runtime_warn_impl(const char *msg) {
  diag_report(NULL, 0, 0, "warning", msg ? msg : "build step degraded", NULL);
}




/**
 * 从源头去补丁：pipeline.x 已用 run_x_pipeline_impl、get_ndep()；codegen 已对 slice/数组形参生成 -> 与 *。
 * 此处仅：必要时插入 parser_parse_into extern；勿再追加已删 pipeline_glue.c
 * （wave309；包装/sizeof/debug 活面在 runtime_pipeline_abi）。返回 0 成功，-1 失败。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int build_patch_pipeline_gen_c_impl(void) {
  /* Cap residual 9.5.5: former fopen/fseek/ftell/fread read + fopen("wb")/
   * fwrite write-back replaced by the Cap authorities — bounded whole-file
   * read (xlang_proc_read_file_bounded, 9.1.12 face) and
   * xlang_io_open_write/xlang_io_write (9.5.3/9.1.8 faces). Contracts kept:
   * unreadable (<=0) and over-sized (-2, file >= PIPELINE_GEN_PATCH_BUF_SIZE)
   * both fail loudly exactly like the old fseek/ftell gate; a file of exactly
   * cap-1 bytes still succeeds via the EOF probe. */
  char *buf = (char *)malloc(PIPELINE_GEN_PATCH_BUF_SIZE);
  long sz;
  size_t cap;
  size_t out_len;
  int fd;
  if (!buf) return -1;
  cap = PIPELINE_GEN_PATCH_BUF_SIZE;
  sz = xlang_proc_read_file_bounded("pipeline_gen.c", buf, PIPELINE_GEN_PATCH_BUF_SIZE);
  if (sz <= 0) { free(buf); return -1; }
  buf[sz] = '\0';

  /* 去重 struct xlang_slice_uint8_t：只保留第一个出现，删除后续重复 */
  {
    const char *pat = "struct xlang_slice_uint8_t { uint8_t *data; size_t length; };";
    size_t pat_len = strlen(pat);
    char *first = strstr(buf, pat);
    if (first) {
      char *next = first + pat_len;
      while ((next = strstr(next, pat)) != NULL) {
        /* 向前找到该行的开头（行首或前一个换行后） */
        char *line_start = next;
        while (line_start > buf && *(line_start - 1) != '\n') line_start--;
        /* 找到该行末尾的换行 */
        char *line_end = next + pat_len;
        while (*line_end && *line_end != '\n') line_end++;
        if (*line_end == '\n') line_end++;
        /* 删除从 line_start 到 line_end 的内容 */
        size_t remove_len = (size_t)(line_end - line_start);
        size_t remaining = (size_t)((buf + sz) - line_end) + 1;
        memmove(line_start, line_end, remaining);
        next = line_start; /* 从删除位置继续搜索 */
      }
    }
  }

  /* 在 #include 块之后立即插入 parser_parse_into_buf 的 extern 声明 */
  {
    const char *extras =
      "extern struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena *, struct ast_Module *, uint8_t *, int32_t);\n";
    /* 找到 xlang_panic_ 函数之前的位置（紧接 #include 块之后） */
    char *ins_point = strstr(buf, "static inline void xlang_panic_");
    if (!ins_point) {
      /* 回退：找最后一个 #include */
      char *p = buf;
      while (*p) {
        if (strncmp(p, "#include", 8) == 0) ins_point = p;
        p++;
      }
      if (ins_point) {
        while (*ins_point && *ins_point != '\n') ins_point++;
        if (*ins_point == '\n') ins_point++;
      }
    }
    if (ins_point) {
      size_t ins_len = strlen(extras);
      size_t remaining = (size_t)((buf + sz) - ins_point) + 1;
      if ((size_t)(ins_point - buf) + ins_len + remaining <= cap) {
        memmove(ins_point + ins_len, ins_point, remaining);
        memcpy(ins_point, extras, ins_len);
      }
    }
  }

  /* 瘦 pipeline_gen.c：外部符号由 parser_x.o / typeck_x.o / codegen_x.o 链接提供 */
  fd = xlang_io_open_write("pipeline_gen.c");
  if (fd < 0) { free(buf); return -1; }
  out_len = strlen(buf);
  if (xlang_io_write(fd, buf, out_len) != (long)out_len) { (void)xlang_proc_close_fd(fd); free(buf); return -1; }
  (void)xlang_proc_close_fd(fd);
  free(buf);
  return 0;
}




/* build_patch_parser_export 已删除：当前 step 6 用 -E-extern 生成 parser_gen.c，已含 parser_* 符号，不再追写 ABI 包装。 */

/* build.x 经 xlang -E 生成：符号为 build_<name>；若源名已含模块前缀则 codegen 去重（见 codegen_c_prefix_redundant_with_name）。 */
extern int32_t build_get_step_count(void);
extern int32_t build_use_asm_only(void);
extern int32_t build_get_step_at(int32_t);

/**
 * 6.3 极薄原语：将 argv[i] 复制到 buf（NUL 结尾），返回长度；越界或失败返回 -1。
 */
int build_get_argv_i(int argc, char **argv, int i, char *buf, int max) {
  if (!buf || max <= 0 || i < 0 || i >= argc || !argv || !argv[i]) return -1;
  size_t n = (size_t)max - 1;
  size_t len = strlen(argv[i]);
  if (len > n) len = n;
  memcpy(buf, argv[i], len);
  buf[len] = '\0';
  return (int)len;
}

/**
 * 6.3 极薄原语：将 literal_id 对应字符串追加到 buf[offset]，返回新 offset；溢出返回 -1。
 */
static const char *const build_literals[] = {
  /* 0: step 0 全命令（含 std_fs_shim.o 供 pipeline/driver 的 std.fs 符号） */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c -o src/main.o seeds/main.from_x.c && cc -Wall -Wextra -I. -Iinclude -Isrc -c -o src/runtime.o seeds/runtime.from_x.c && cc -Wall -Wextra -I. -Iinclude -Isrc -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_FRONTEND -DXLANG_USE_X_PREPROCESS -c -o src/runtime_driver.o seeds/runtime.from_x.c && cc -Wall -Wextra -I. -Iinclude -Isrc -c -o std_fs.o src/std_fs_shim.c && sh scripts/cc_inc_tu.sh seeds/preprocess_shim.from_x.c preprocess_shim.o",
  /* 1: step 1 后缀（前接 xlang_path） */
  " -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -E -E-extern src/pipeline/pipeline.x > pipeline_gen.c",
  /* 2: step 2 */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c pipeline_gen.c -o pipeline_x.o",
  /* 3: step 3 后缀 */
  " -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.x -E -E-extern > driver_gen.c",
  /* 4: step 4 */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c driver_gen.c -o driver_x.o",
  /* 5: step 5（含 std_fs.o 供 pipeline/driver 的 std.fs 符号） */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_FRONTEND -o xlang src/main.o src/runtime_driver.o preprocess_shim.o preprocess_x.o std_fs.o ast_x.o token_x.o lexer_x.o parser_x.o typeck_x.o codegen_x.o driver_x.o pipeline_x.o",
  /* 6–7: step 6 parser */
  " -L .. -L src/lexer -L src/ast -E -E-extern src/parser/parser.x > parser_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c parser_gen.c -o parser_x.o",
  /* 8–9: typeck */
  " -L .. -L src/lexer -L src/ast -E -E-extern src/typeck/typeck.x > typeck_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c typeck_gen.c -o typeck_x.o",
  /* 10–11: codegen */
  " -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -E -E-extern src/codegen/codegen.x > codegen_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c codegen_gen.c -o codegen_x.o",
  /* 12–13: ast */
  " -E -E-extern src/ast/ast.x > ast_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c ast_gen.c -o ast_x.o",
  /* 14–15: token */
  " -L src/lexer -E -E-extern src/lexer/token.x > token_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c token_gen.c -o token_x.o",
  /* 16–17: lexer */
  " -L src/lexer -E -E-extern src/lexer/lexer.x > lexer_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c lexer_gen.c -o lexer_x.o",
  /* 18–19: preprocess */
  " -L src/lexer -E -E-extern src/preprocess/preprocess.x > preprocess_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c preprocess_gen.c -o preprocess_x.o",
  /* 20–21: 完全自举 asm 路径（build.x 用 argv[2]==asm 时执行） */
  "XLANG=",
  " ./scripts/build_xlang_asm.sh",
};
static const int build_literals_n = (int)(sizeof(build_literals) / sizeof(build_literals[0]));

int build_append_literal(char *buf, int size, int offset, int literal_id) {
  if (!buf || size <= 0 || offset < 0 || literal_id < 0 || literal_id >= build_literals_n) return -1;
  const char *s = build_literals[literal_id];
  size_t len = strlen(s);
  if (offset + len >= (size_t)size) return -1;
  memcpy(buf + offset, s, len + 1);
  return (int)(offset + len);
}

/**
 * 6.3 thin primitive: run NUL-terminated cmd_buf; return link_abi_system status or -1.
 * wave250 G.7: public pure thin link_abi_system (not raw libc system).
 */
int build_exec_cmd(char *cmd_buf) {
  if (!cmd_buf) return -1;
  return link_abi_system(cmd_buf);
}

/**
 * 6.3：对 driver_gen.c 做与 Makefile 等价的 sed 修正（slice . -> ->；preprocess_x_buf 签名）。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int build_patch_driver_gen_c_impl(void) {
  /* Cap residual 9.5.5: same bounded-read + Cap write-back contract as
   * build_patch_pipeline_gen_c_impl (see there for the loud-failure gates). */
  char *buf = (char *)malloc(PIPELINE_GEN_PATCH_BUF_SIZE);
  long sz;
  size_t out_len;
  int fd;
  if (!buf) return -1;
  sz = xlang_proc_read_file_bounded("driver_gen.c", buf, PIPELINE_GEN_PATCH_BUF_SIZE);
  if (sz <= 0) { free(buf); return -1; }
  buf[sz] = '\0';
  /* slice . -> ->、preprocess_x_buf 签名、run_compiler_c 包装均已从源头产出（codegen 数组形参为 *，runtime.c 在 XLANG_USE_X_DRIVER 下已定义 run_compiler_c），不再补丁 */
  fd = xlang_io_open_write("driver_gen.c");
  if (fd < 0) { free(buf); return -1; }
  out_len = strlen(buf);
  if (xlang_io_write(fd, buf, out_len) != (long)out_len) { (void)xlang_proc_close_fd(fd); free(buf); return -1; }
  (void)xlang_proc_close_fd(fd);
  free(buf);
  return 0;
}




/**
 * 6.3 极薄原语：执行 step_id 对应的修正（1 pipeline_gen.c，3 driver_gen.c，6 preprocess_gen.c）。返回 0 成功 -1 失败。
 */
int build_patch_after_step(int step_id) {
  if (step_id == 1) return build_patch_pipeline_gen_c() == 0 ? 0 : -1;
  if (step_id == 3) return build_patch_driver_gen_c() == 0 ? 0 : -1;
  /* step 6：preprocess_gen.c 不再补丁，codegen 对 source/out_buf 形参已生成 -> */
  return 0;
}

/**
 * 将 argv[1] 或默认 "./xlang" 写入 buf（NUL 结尾），不超过 max-1 字节。
 * 返回 0 成功，-1 失败（如 max<=0）。保留供兼容。
 */
int build_get_shu_path(char *buf, int max, int argc, char **argv) {
  if (!buf || max <= 0) return -1;
  buf[0] = '\0';
  if (argc >= 2 && argv[1] && argv[1][0]) {
    size_t n = (size_t)max - 1;
    strncat(buf, argv[1], n);
    buf[max - 1] = '\0';
  } else {
    size_t n = (size_t)max - 1;
    if (n > 5) n = 5;
    memcpy(buf, "./xlang", 5);
    buf[5] = '\0';
  }
  return 0;
}

/**
 * 执行单步构建命令；由 main 按 build.x 的步骤顺序调用。step_id 含义见 build.x 注释。
 */
int build_run_step(int step_id, const char *xlang_path) {
  char cmd[4096];
  const char *cc = "cc";
  const char *cflags = "-Wall -Wextra -I. -Iinclude -Isrc";
  const char *cflags_driver = "-Wall -Wextra -I. -Iinclude -Isrc -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_FRONTEND -DXLANG_USE_X_PREPROCESS";
  int n;

  switch (step_id) {
  case 0:
    /* 阶段 3.2 / 6.4：编 main、runtime_driver（带 X_PREPROCESS 使 preprocess() 在 .x 路径）。
     * G-02a: preprocess.c 已物理删除；preprocess 由 preprocess_x.o 提供（step 18-19 生成）。
     * G-02a: typeck.c 已物理删除；typeck 由 typeck_x.o 提供（step 8-9 生成），typeck_c_module_stubs.o 提供 weak 桩。
     * G-02a: codegen.c 已物理删除；codegen 由 codegen_x.o 提供，codegen_pipeline_stubs.o 提供 weak 桩。
     * 同时编译所有 C 侧模块，供 step 5 链接（runtime_driver 仍引用了部分 C 侧函数）。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c -o src/main.o seeds/main.from_x.c && "
      "%s %s -c -o src/runtime.o seeds/runtime.from_x.c && "
      "%s %s -DXLANG_USE_X_PREPROCESS -c -o src/runtime_driver.o seeds/runtime.from_x.c && "
      "%s %s -c -o src/lexer/lexer.o seeds/runtime_lexer_glue.from_x.c && "
      "%s %s -c -o src/ast/ast.o seeds/runtime_ast_glue.from_x.c && "
      "%s %s -c -o src/lsp/lsp_diag.o seeds/runtime_lsp_glue.from_x.c && "
      "%s %s -c -o std_fs_shim.o src/std_fs_shim.c && "
      "sh scripts/cc_inc_tu.sh seeds/x_stubs.from_x.c x_stubs.o",
      cc, cflags, cc, cflags, cc, cflags_driver,
      cc, cflags, cc, cflags,
      cc, cflags, cc, cflags, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  case 6: {
    /* 阶段 3.2：用 -E -E-extern 生成瘦 parser_gen.c/typeck_gen.c/codegen_gen.c（仅类型+入口模块，依赖用 extern），再编成 _x.o。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -E -E-extern src/parser/parser.x > parser_gen.c",
      xlang_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    /* -E-extern 已生成 parser_* 符号，不再追加 ABI 包装，避免重复定义。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "perl -i -ne 'print unless /^struct xlang_slice_uint8_t/ && $seen++' parser_gen.c && %s %s -include ast.h -c parser_gen.c -o parser_x.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -E -E-extern src/typeck/typeck.x > typeck_gen.c && "
      "%s %s -c typeck_gen.c -o typeck_x.o",
      xlang_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -E -E-extern src/codegen/codegen.x > codegen_gen.c && "
      "%s %s -c codegen_gen.c -o codegen_x.o",
      xlang_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    /* 阶段 3：生成并编 ast_x.o、token_x.o、lexer_x.o，供 parser/typeck/codegen 与 pipeline 链接。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -E -E-extern src/ast/ast.x > ast_gen.c && %s %s -c ast_gen.c -o ast_x.o",
      xlang_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/lexer/token.x > token_gen.c && %s %s -c token_gen.c -o token_x.o",
      xlang_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/lexer/lexer.x > lexer_gen.c && %s %s -c lexer_gen.c -o lexer_x.o",
      xlang_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    /* 6.4：preprocess.x 生成 preprocess_gen.c（codegen 对 slice 形参已生成 ->，无补丁），编成 preprocess_x.o。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/preprocess/preprocess.x > preprocess_gen.c",
      xlang_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd), "%s %s -c preprocess_gen.c -o preprocess_x.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  }
  case 1: {
    /* 阶段 1.1/1.2：用 xlang 生成 pipeline_gen.c，再由 build_patch_pipeline_gen_c 修正。
     * 阶段 3：C 版 xlang 无 -x，一律用 -E -E-extern 生成瘦 pipeline_gen.c，避免与 parser_x/typeck_x/codegen_x 重复符号。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -E -E-extern src/pipeline/pipeline.x > pipeline_gen.c",
      xlang_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (link_abi_system(cmd) != 0) return -1;
    return build_patch_pipeline_gen_c() == 0 ? 0 : -1;
  }
  case 2:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c pipeline_gen.c -o pipeline_x.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  case 3:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess -E -E-extern src/main.x > driver_gen.c",
      xlang_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  case 4:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c driver_gen.c -o driver_x.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  case 5:
    /* 阶段 3.2/3.3、6.4：链 runtime_driver.o（含 preprocess()，step 0 已带 -DXLANG_USE_X_PREPROCESS）+ preprocess_x.o
     * + 所有 C 侧 .o（仍被 runtime_driver 的部分路径引用）。
     * G-02a: preprocess.c/parser.c/typeck.c/codegen.c 已物理删除；typeck 由 typeck_x.o + typeck_c_module_stubs.o 提供，codegen 由 codegen_x.o + codegen_pipeline_stubs.o 提供。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_FRONTEND -o xlang "
      "src/main.o src/runtime_driver.o "
      "src/lexer/lexer.o src/ast/ast.o src/lsp/lsp_diag.o std_fs_shim.o x_stubs.o "
      "preprocess_x.o ast_x.o token_x.o lexer_x.o parser_x.o typeck_x.o codegen_x.o driver_x.o pipeline_x.o",
      cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return link_abi_system(cmd);
  default:
    return -1;
  }
}

/**
 * 完全自举 asm 路径：执行 XLANG=<xlang_path> ./scripts/build_xlang_asm.sh。
 * Return 0 on success, non-zero link_abi_system status on failure (main / build_runner).
 * wave250 G.7: shell via link_abi_system (not raw libc system).
 *
 * 语义与「是否仍 cc -c pipeline_gen」以 compiler/docs/SELFHOST.md 为准（Target B-partial /
 * B-hybrid、`XLANG_ASM_LINK_TOPOLOGY`）。
 * 拓扑：未导出 `XLANG_ASM_LINK_TOPOLOGY` 时，脚本在 **Linux/macOS** 且 `check_asm_o_quality.sh` 认定全部
 * __text 非空后自动选 `full_asm`；M7 默认 `XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1` → asm_only_strict。
 * 不在此重复脚本细节，避免与 build_xlang_asm.sh 漂移。
 */
int build_run_asm_build(const char *xlang_path) {
  char cmd[4096];
  /* M7：与 make bootstrap-driver-bstrict 一致，默认 B-strict（SKIP_GEN）。 */
  int n = snprintf(cmd, sizeof(cmd),
                   "XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 XLANG=%s ./scripts/build_xlang_asm.sh",
                   xlang_path ? xlang_path : "./xlang");
  if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
  return link_abi_system(cmd);
}

/** 执行 build.x 配置的 legacy 逐步（生成 *_gen.c 并链接 xlang）。返回 0 成功。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int build_run_legacy_steps_impl(const char *xlang_path) {
  int n = (int)build_get_step_count();
  for (int i = 0; i < n; i++) {
    int step_id = (int)build_get_step_at((int32_t)i);
    if (step_id < 0) return 1;
    if (build_run_step(step_id, xlang_path) != 0) return 1;
  }
  return 0;
}

#ifndef XLANG_BUILD_RUNTIME_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/build_runtime.x）提供 wrapper 调用 _impl */
void build_runtime_info(const char *msg) { build_runtime_info_impl(msg); }
void build_runtime_warn(const char *msg) { build_runtime_warn_impl(msg); }
int build_patch_pipeline_gen_c(void) { return build_patch_pipeline_gen_c_impl(); }
int build_patch_driver_gen_c(void) { return build_patch_driver_gen_c_impl(); }
int build_run_legacy_steps(const char *xlang_path) { return build_run_legacy_steps_impl(xlang_path); }
#endif /* XLANG_BUILD_RUNTIME_FROM_X */




#ifdef BUILD_TOOL_X_ENTRY
/* 入口由 build_runner.x 提供；crt0 调 entry，此处提供 entry 包装调用 build_runner_entry（.x -E 生成符号为 build_runner_entry）。 */
extern int32_t build_runner_entry(int argc, void *argv);
int entry(int argc, char **argv) {
  return (int)build_runner_entry(argc, (void *)argv);
}
#else
int main(int argc, char **argv) {
  char xlang_path[256];
  if (argc >= 2 && argv[1] && argv[1][0]) {
    size_t n = sizeof(xlang_path) - 1;
    size_t len = strlen(argv[1]);
    if (len > n) len = n;
    memcpy(xlang_path, argv[1], len);
    xlang_path[len] = '\0';
  } else {
    memcpy(xlang_path, "./xlang", 5);
    xlang_path[5] = '\0';
  }
  /* 显式 asm：只跑脚本，失败即退出（不回退）。 */
  if (argc >= 3 && argv[2] && strcmp(argv[2], "asm") == 0)
    return build_run_asm_build(xlang_path) != 0 ? 1 : 0;
  /* 显式 legacy：只跑 -E 逐步，忽略 build_use_asm_only。 */
  if (argc >= 3 && argv[2] && strcmp(argv[2], "legacy") == 0)
    return build_run_legacy_steps(xlang_path) != 0 ? 1 : 0;
  /* build.x build_use_asm_only()==1：先试 asm（不生成 pipeline_gen/driver_gen）；失败则回退 legacy。 */
  if (build_use_asm_only() != 0) {
    int ar = build_run_asm_build(xlang_path);
    if (ar == 0) {
      (void)link_abi_system("cp -f xlang_asm xlang");
      build_runtime_info("asm path OK; ./xlang updated from xlang_asm");
      return 0;
    }
    build_runtime_warn("asm build failed; falling back to legacy C codegen steps");
  }
  return build_run_legacy_steps(xlang_path) != 0 ? 1 : 0;
}
#endif /* !BUILD_TOOL_X_ENTRY */
