/**
 * build_runtime.c — 阶段 7：build.su 构建工具的 C 运行时
 *
 * 职责：提供 main() 按 build.su 的步骤配置执行；build_run_step(step_id, shu_path) 执行单步，
 * build_run_asm_build(shu_path) 执行完全自举 asm 路径；argv[1]=shu 路径，argv[2]=asm 时走 asm 路径。
 * 约定：build_tool 应在 compiler 目录下运行，步骤 0～5 依次为：编 C→.o、生成并修正 pipeline_gen.c、
 * 编 pipeline_su.o、生成 driver_gen.c、编 driver_su.o、链接 shu。
 * 阶段 1（完全脱离C与Makefile路线图）：step 1 不再调 make，由本文件用 shu 生成 pipeline_gen.c 并完成与 Makefile 等价的修正。
 * 阶段 3：step 0 仅编 main/runtime/preprocess/lexer/ast，不编 parser/typeck/codegen；step 6 生成并编 parser_su.o/typeck_su.o/codegen_su.o；
 * step 1 的 C 回退用 -E-extern 生成瘦 pipeline_gen.c；step 5 链入 parser_su.o、typeck_su.o、codegen_su.o。
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PIPELINE_GEN_PATCH_BUF_SIZE (512 * 1024)

/**
 * 从源头去补丁：pipeline.su 已用 run_su_pipeline_impl、get_ndep()；codegen 已对 slice/数组形参生成 -> 与 *。
 * 此处仅：必要时插入 parser_parse_into extern，并追加 pipeline_glue.c 内容（包装/sizeof/debug 等）。返回 0 成功，-1 失败。
 */
static int build_patch_pipeline_gen_c(void) {
  FILE *f = fopen("pipeline_gen.c", "rb");
  if (!f) return -1;
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return -1; }
  long sz = ftell(f);
  if (sz <= 0 || sz >= (long)PIPELINE_GEN_PATCH_BUF_SIZE) { fclose(f); return -1; }
  rewind(f);
  size_t cap = (size_t)sz + 4096;
  if (cap > PIPELINE_GEN_PATCH_BUF_SIZE) cap = PIPELINE_GEN_PATCH_BUF_SIZE;
  char *buf = (char *)malloc(cap);
  if (!buf) { fclose(f); return -1; }
  if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; }
  buf[sz] = '\0';
  fclose(f);

  /* 若调用了 parser_parse_into 但缺少其 extern，则插入（codegen 有时未收集到间接调用） */
  if (strstr(buf, "parser_parse_into(arena") != NULL && strstr(buf, "parser_parse_into(struct ast_ASTArena") == NULL) {
    const char *anchor = "extern void parser_parse_into_init(";
    char *pos = strstr(buf, anchor);
    if (pos) {
      const char *ins = "extern struct parser_ParseIntoResult parser_parse_into(struct ast_ASTArena *, struct ast_Module *, struct shulang_slice_uint8_t *);\n";
      size_t ins_len = strlen(ins);
      size_t tail = (size_t)((buf + sz) - pos) + 1;
      if ((size_t)(pos - buf) + ins_len + tail <= cap) {
        memmove(pos + ins_len, pos, tail);
        memcpy(pos, ins, ins_len);
        sz = (long)(strlen(buf));
      }
    }
  }

  /* 追加 #include "pipeline_glue.c"，由 cc 编译时包含，不再读入并追写整份文件 */
  {
    const char *inc = "\n#include \"pipeline_glue.c\"\n";
    size_t inc_len = strlen(inc);
    if ((size_t)sz + inc_len + 1 > cap) { free(buf); return -1; }
    memcpy(buf + sz, inc, inc_len + 1);
    sz += (long)inc_len;
  }

  f = fopen("pipeline_gen.c", "wb");
  if (!f) { free(buf); return -1; }
  if (fwrite(buf, 1, (size_t)sz, f) != (size_t)sz) { fclose(f); free(buf); return -1; }
  fclose(f);
  free(buf);
  return 0;
}

/* build_patch_parser_export 已删除：当前 step 6 用 -E-extern 生成 parser_gen.c，已含 parser_* 符号，不再追写 ABI 包装。 */

/* build.su 仅提供配置：步骤顺序由 getter 暴露；-E 生成 C 时符号为 build_<函数名> */
extern int32_t build_build_get_step_count(void);
extern int32_t build_build_get_step_at(int32_t i);

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
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c -o src/main.o src/main.c && cc -Wall -Wextra -I. -Iinclude -Isrc -c -o src/runtime.o src/runtime.c && cc -Wall -Wextra -I. -Iinclude -Isrc -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -DSHU_USE_SU_FRONTEND -DSHU_USE_SU_PREPROCESS -c -o src/runtime_driver.o src/runtime.c && cc -Wall -Wextra -I. -Iinclude -Isrc -DSHU_USE_SU_PREPROCESS -c -o src/preprocess_fallback.o src/preprocess.c && cc -Wall -Wextra -I. -Iinclude -Isrc -c -o std_fs.o src/std_fs_shim.c && cc -Wall -Wextra -I. -Iinclude -Isrc -c -o preprocess_shim.o src/preprocess_shim.c",
  /* 1: step 1 后缀（前接 shu_path） */
  " -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess -E -E-extern src/pipeline/pipeline.su > pipeline_gen.c",
  /* 2: step 2 */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c pipeline_gen.c -o pipeline_su.o",
  /* 3: step 3 后缀 */
  " -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess src/main.su -E -E-extern > driver_gen.c",
  /* 4: step 4 */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c driver_gen.c -o driver_su.o",
  /* 5: step 5（含 std_fs.o 供 pipeline/driver 的 std.fs 符号） */
  "cc -Wall -Wextra -I. -Iinclude -Isrc -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -DSHU_USE_SU_FRONTEND -o shu src/main.o src/runtime_driver.o src/preprocess_fallback.o preprocess_shim.o preprocess_su.o std_fs.o ast_su.o token_su.o lexer_su.o parser_su.o typeck_su.o codegen_su.o driver_su.o pipeline_su.o",
  /* 6–7: step 6 parser */
  " -L .. -L src/lexer -L src/ast -E -E-extern src/parser/parser.su > parser_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c parser_gen.c -o parser_su.o",
  /* 8–9: typeck */
  " -L .. -L src/lexer -L src/ast -E -E-extern src/typeck/typeck.su > typeck_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c typeck_gen.c -o typeck_su.o",
  /* 10–11: codegen */
  " -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -E -E-extern src/codegen/codegen.su > codegen_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c codegen_gen.c -o codegen_su.o",
  /* 12–13: ast */
  " -E -E-extern src/ast/ast.su > ast_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c ast_gen.c -o ast_su.o",
  /* 14–15: token */
  " -L src/lexer -E -E-extern src/lexer/token.su > token_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c token_gen.c -o token_su.o",
  /* 16–17: lexer */
  " -L src/lexer -E -E-extern src/lexer/lexer.su > lexer_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c lexer_gen.c -o lexer_su.o",
  /* 18–19: preprocess */
  " -L src/lexer -E -E-extern src/preprocess/preprocess.su > preprocess_gen.c",
  "cc -Wall -Wextra -I. -Iinclude -Isrc -c preprocess_gen.c -o preprocess_su.o",
  /* 20–21: 完全自举 asm 路径（build.su 用 argv[2]==asm 时执行） */
  "SHU=",
  " ./scripts/build_shu_asm.sh",
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
 * 6.3 极薄原语：执行 cmd_buf（NUL 结尾）；返回 system() 的返回值或 -1。
 */
int build_exec_cmd(char *cmd_buf) {
  if (!cmd_buf) return -1;
  return system(cmd_buf);
}

/**
 * 6.3：对 driver_gen.c 做与 Makefile 等价的 sed 修正（slice . -> ->；preprocess_su_buf 签名）。
 */
static int build_patch_driver_gen_c(void) {
  FILE *f = fopen("driver_gen.c", "rb");
  if (!f) return -1;
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return -1; }
  long sz = ftell(f);
  if (sz <= 0 || sz >= (long)PIPELINE_GEN_PATCH_BUF_SIZE) { fclose(f); return -1; }
  rewind(f);
  char *buf = (char *)malloc((size_t)sz + 1);
  if (!buf) { fclose(f); return -1; }
  if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; }
  buf[sz] = '\0';
  fclose(f);
  /* slice . -> ->、preprocess_su_buf 签名、run_compiler_c 包装均已从源头产出（codegen 数组形参为 *，runtime.c 在 SHU_USE_SU_DRIVER 下已定义 run_compiler_c），不再补丁 */
  f = fopen("driver_gen.c", "wb");
  if (!f) { free(buf); return -1; }
  if (fwrite(buf, 1, strlen(buf), f) != strlen(buf)) { fclose(f); free(buf); return -1; }
  fclose(f);
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
 * 将 argv[1] 或默认 "./shu" 写入 buf（NUL 结尾），不超过 max-1 字节。
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
    memcpy(buf, "./shu", 5);
    buf[5] = '\0';
  }
  return 0;
}

/**
 * 执行单步构建命令；由 main 按 build.su 的步骤顺序调用。step_id 含义见 build.su 注释。
 */
int build_run_step(int step_id, const char *shu_path) {
  char cmd[4096];
  const char *cc = "cc";
  const char *cflags = "-Wall -Wextra -I. -Iinclude -Isrc";
  const char *cflags_driver = "-Wall -Wextra -I. -Iinclude -Isrc -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -DSHU_USE_SU_FRONTEND -DSHU_USE_SU_PREPROCESS";
  int n;

  switch (step_id) {
  case 0:
    /* 阶段 3.2 / 6.4：编 main、runtime_driver（带 SU_PREPROCESS 使 preprocess() 在 .su 路径）、preprocess_fallback（不覆盖 preprocess.o）。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c -o src/main.o src/main.c && "
      "%s %s -c -o src/runtime.o src/runtime.c && "
      "%s %s -DSHU_USE_SU_PREPROCESS -c -o src/runtime_driver.o src/runtime.c && "
      "%s %s -DSHU_USE_SU_PREPROCESS -c -o src/preprocess_fallback.o src/preprocess.c",
      cc, cflags, cc, cflags, cc, cflags_driver, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  case 6: {
    /* 阶段 3.2：用 -E -E-extern 生成瘦 parser_gen.c/typeck_gen.c/codegen_gen.c（仅类型+入口模块，依赖用 extern），再编成 _su.o。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -E -E-extern src/parser/parser.su > parser_gen.c",
      shu_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    /* -E-extern 已生成 parser_* 符号，不再追加 ABI 包装，避免重复定义。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c parser_gen.c -o parser_su.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -E -E-extern src/typeck/typeck.su > typeck_gen.c && "
      "%s %s -c typeck_gen.c -o typeck_su.o",
      shu_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -E -E-extern src/codegen/codegen.su > codegen_gen.c && "
      "%s %s -c codegen_gen.c -o codegen_su.o",
      shu_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    /* 阶段 3：生成并编 ast_su.o、token_su.o、lexer_su.o，供 parser/typeck/codegen 与 pipeline 链接。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -E -E-extern src/ast/ast.su > ast_gen.c && %s %s -c ast_gen.c -o ast_su.o",
      shu_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/lexer/token.su > token_gen.c && %s %s -c token_gen.c -o token_su.o",
      shu_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/lexer/lexer.su > lexer_gen.c && %s %s -c lexer_gen.c -o lexer_su.o",
      shu_path, cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    /* 6.4：preprocess.su 生成 preprocess_gen.c（codegen 对 slice 形参已生成 ->，无补丁），编成 preprocess_su.o。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L src/lexer -E -E-extern src/preprocess/preprocess.su > preprocess_gen.c",
      shu_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    n = (int)snprintf(cmd, sizeof(cmd), "%s %s -c preprocess_gen.c -o preprocess_su.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  }
  case 1: {
    /* 阶段 1.1/1.2：用 shu 生成 pipeline_gen.c，再由 build_patch_pipeline_gen_c 修正。
     * 阶段 3：C 版 shu 无 -su，一律用 -E -E-extern 生成瘦 pipeline_gen.c，避免与 parser_su/typeck_su/codegen_su 重复符号。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -E -E-extern src/pipeline/pipeline.su > pipeline_gen.c",
      shu_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    if (system(cmd) != 0) return -1;
    return build_patch_pipeline_gen_c() == 0 ? 0 : -1;
  }
  case 2:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c pipeline_gen.c -o pipeline_su.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  case 3:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s -L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen src/main.su -E > driver_gen.c",
      shu_path);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  case 4:
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -c driver_gen.c -o driver_su.o", cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  case 5:
    /* 阶段 3.2/3.3、6.4：链 runtime_driver.o（含 preprocess()，step 0 已带 -DSHU_USE_SU_PREPROCESS）+ preprocess_fallback.o + preprocess_su.o。 */
    n = (int)snprintf(cmd, sizeof(cmd),
      "%s %s -DSHU_USE_SU_DRIVER -DSHU_USE_SU_PIPELINE -DSHU_USE_SU_FRONTEND -o shu "
      "src/main.o src/runtime_driver.o src/preprocess_fallback.o preprocess_su.o ast_su.o token_su.o lexer_su.o parser_su.o typeck_su.o codegen_su.o driver_su.o pipeline_su.o",
      cc, cflags);
    if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
    return system(cmd);
  default:
    return -1;
  }
}

/**
 * 完全自举 asm 路径：执行 SHU=<shu_path> ./scripts/build_shu_asm.sh。
 * 返回 0 成功，非 0 为 system() 返回值或失败。供 build_runner.su 的 entry 调用。
 */
int build_run_asm_build(const char *shu_path) {
  char cmd[4096];
  int n = snprintf(cmd, sizeof(cmd), "SHU=%s ./scripts/build_shu_asm.sh", shu_path ? shu_path : "./shu");
  if (n <= 0 || n >= (int)sizeof(cmd)) return -1;
  return system(cmd);
}

#ifdef BUILD_TOOL_SU_ENTRY
/* 入口由 build_runner.su 提供；crt0 调 entry，此处提供 entry 包装调用 build_runner_entry（.su -E 生成符号为 build_runner_entry）。 */
extern int32_t build_runner_entry(int argc, void *argv);
int entry(int argc, char **argv) {
  return (int)build_runner_entry(argc, (void *)argv);
}
#else
int main(int argc, char **argv) {
  char shu_path[256];
  if (argc >= 2 && argv[1] && argv[1][0]) {
    size_t n = sizeof(shu_path) - 1;
    size_t len = strlen(argv[1]);
    if (len > n) len = n;
    memcpy(shu_path, argv[1], len);
    shu_path[len] = '\0';
  } else {
    memcpy(shu_path, "./shu", 5);
    shu_path[5] = '\0';
  }
  if (argc >= 3 && argv[2] && strcmp(argv[2], "asm") == 0)
    return build_run_asm_build(shu_path) != 0 ? 1 : 0;
  int n = (int)build_build_get_step_count();
  for (int i = 0; i < n; i++) {
    int step_id = (int)build_build_get_step_at((int32_t)i);
    if (step_id < 0) return 1;
    if (build_run_step(step_id, shu_path) != 0) return 1;
  }
  return 0;
}
#endif /* !BUILD_TOOL_SU_ENTRY */
