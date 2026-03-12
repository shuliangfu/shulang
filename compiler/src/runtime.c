/**
 * runtime.c — 编译器运行时（6.3/6.4：自 main.c 迁出的驱动逻辑与 C 辅助）
 *
 * 文件职责：提供 run_compiler_c、driver_*、pipeline_*、get_dep_* 及 read_file/preprocess/resolve_import 等；无 SHUC_USE_SU_DRIVER 时提供弱符号 main_entry 转调 run_compiler_c，供默认构建链接；有 main.su 时由 main_entry 覆盖。
 * 与 main.c 关系：main.c 仅保留极简 main() 调 main_entry；本文件承载全部 C 侧驱动与 I/O，与 main.su 一一对应构建 shuc。
 */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "preprocess.h"
#include "typeck/typeck.h"
#include "codegen/codegen.h"
#include "ast.h"
#ifdef SHUC_USE_SU_CODEGEN
/* 6.2：.su codegen 入口；由 codegen.su 提供（库模块形式，符号带 codegen_ 前缀），转调 C codegen */
extern int codegen_codegen_entry_module_to_c(struct ASTModule *m, FILE *out, struct ASTModule **dep_mods, const char **dep_import_paths, int ndep,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);
extern int codegen_codegen_entry_library_module_to_c(struct ASTModule *m, const char *import_path,
    struct ASTModule **lib_dep_mods, const char **lib_dep_paths, int n_lib_dep, FILE *out,
    codegen_is_func_used_fn is_func_used, codegen_is_mono_used_fn is_mono_used, codegen_is_type_used_fn is_type_used, void *dce_ctx,
    char (*emitted_type_names)[CODEGEN_EMITTED_TYPE_NAME_MAX], int *n_emitted_inout, int max_emitted);
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
/* 提前声明，供 SHUC_USE_SU_PIPELINE 块内 pipeline_* 调用 */
static char *read_file(const char *path, size_t *out_len);
static void resolve_import_file_path_multi(const char **lib_roots, int n_lib_roots, const char *entry_dir, const char *import_path, char *path, size_t path_size);
#ifdef SHUC_USE_SU_TYPECK
/* 6.1：.su typeck 入口；由 typeck.su 提供（库模块形式生成，符号为 typeck_typeck_entry），转调 C typeck_module */
extern int typeck_typeck_entry(struct ASTModule *mod, struct ASTModule **deps, int ndep);
#endif
#ifdef SHUC_USE_SU_PIPELINE
#include <stdint.h>
#include <stddef.h>
/* 9.1：纯 .su 流水线；由 pipeline_gen.c 提供；6.1 dep 通过 ctx 传入，.su 不再 extern get_dep_*。 */
struct shulang_slice_uint8_t { uint8_t *data; size_t length; };
/* 与 ast.su PipelineDepCtx 布局一致；6.1 完全自举：loaded/preprocess 为固定数组，全部在 .su 内完成 */
#define PIPELINE_CTX_BUF_SIZE 262144
struct ast_PipelineDepCtx {
    void *dep_modules[32];
    void *dep_arenas[32];
    int32_t ndep;
    uint8_t entry_dir_buf[512];
    int32_t entry_dir_len;
    int32_t num_lib_roots;
    uint8_t lib_root_bufs[8][256];
    int32_t lib_root_lens[8];
    uint8_t path_buf[512];
    uint8_t loaded_buf[PIPELINE_CTX_BUF_SIZE];
    int64_t loaded_len;  /* isize */
    uint8_t preprocess_buf[PIPELINE_CTX_BUF_SIZE];
    int32_t preprocess_len;
    int32_t use_asm_backend;  /* 非 0 时 pipeline 出汇编，由 -backend asm 设置 */
    int32_t target_arch;      /* 0=x86_64，1=arm64，2=riscv64；按 -target 设置，asm 后端分派用 */
    int32_t use_macho_o;      /* 非 0 时出 .o 写 Mach-O（macOS）；由 -o xxx.o 且 __APPLE__ 时设置 */
    int32_t use_coff_o;       /* 非 0 时出 .o 写 COFF/PE .obj（Windows 目标）；由 -target *-windows-* 且 -o 时设置 */
    int32_t current_block_ref; /* typeck 用：当前检查的块 ref，供 EXPR_VAR 查 const/let 填 resolved_type_ref；0 表示未在块内 */
};
extern int pipeline_run_su_pipeline(void *arena, void *module, const uint8_t *source_data, size_t source_len, void *out_buf, void *ctx);

/** 6.1：填充 ctx 的 entry_dir_buf、lib_root_bufs，供 .su 内 resolve_path_su 使用；loaded/preprocess 为 ctx 内固定数组。 */
static void pipeline_fill_ctx_path_buffers(struct ast_PipelineDepCtx *ctx, const char *entry_dir, const char **lib_roots, int n_lib_roots) {
    ctx->loaded_len = 0;
    ctx->preprocess_len = 0;
    ctx->entry_dir_len = 0;
    if (entry_dir) {
        size_t el = strlen(entry_dir);
        if (el >= 512) el = 511;
        memcpy(ctx->entry_dir_buf, entry_dir, el);
        ctx->entry_dir_buf[el] = '\0';
        ctx->entry_dir_len = (int32_t)el;
    }
    ctx->num_lib_roots = n_lib_roots <= 8 ? n_lib_roots : 8;
    for (int i = 0; i < ctx->num_lib_roots && lib_roots && lib_roots[i]; i++) {
        size_t ll = strlen(lib_roots[i]);
        if (ll >= 256) ll = 255;
        memcpy(ctx->lib_root_bufs[i], lib_roots[i], ll);
        ctx->lib_root_bufs[i][ll] = '\0';
        ctx->lib_root_lens[i] = (int32_t)ll;
    }
}
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_module(void);
/** 7.4：ELF .o 路径；由 Makefile 追加到 pipeline_gen.c，用于分配 ElfCodegenCtx */
extern size_t pipeline_sizeof_elf_ctx(void);
/** 7.4：直接生成 ELF64 .o 到 out_buf（仅 x86_64）；由 asm.su 提供，pipeline_su.o 链接；ElfCodegenCtx 在 platform/elf.su，C 侧为 platform_elf_ElfCodegenCtx */
struct platform_elf_ElfCodegenCtx;
extern int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, struct platform_elf_ElfCodegenCtx *elf_ctx, struct codegen_CodegenOutBuf *out_buf);
/** 判断 -o 路径是否写出对象文件（.o / .obj 则写 ELF/Mach-O/COFF 而非 .s） */
static int output_is_elf_o(const char *path) {
    if (!path) return 0;
    size_t n = strlen(path);
    if (n >= 2 && path[n - 2] == '.' && (path[n - 1] == 'o' || path[n - 1] == 'O'))
        return 1;
    return n >= 4 && path[n - 4] == '.' && path[n - 3] == 'o' && path[n - 2] == 'b' && path[n - 1] == 'j';
}

/** 根据 argv[0]（shuc 可执行路径）得到同目录下的 runtime_panic.o 路径，用于 -backend asm 链接时提供 shulang_panic_；返回静态缓冲区，可能为空。 */
static const char *get_runtime_panic_o_path(const char *argv0) {
    static char buf[512];
    buf[0] = '\0';
    if (!argv0 || !argv0[0]) return buf;
    const char *last_slash = strrchr(argv0, '/');
    int n;
    if (last_slash) {
        n = (int)(last_slash - argv0);
        if (n >= (int)sizeof(buf) - 20) return buf;
        memcpy(buf, argv0, (size_t)n);
        buf[n] = '\0';
    } else {
        if (sizeof(buf) < 20) return buf;
        buf[0] = '.'; buf[1] = '\0';
        n = 1;
    }
    if (n + 18 >= (int)sizeof(buf)) return buf;
    strcat(buf, "/runtime_panic.o");
    return buf;
}

/** 判断 -o 路径是否表示「要可执行文件」：非 .o/.obj/.s 结尾则视为可执行文件名；-backend asm 时据此自动调 ld。 */
static int output_want_exe(const char *path) {
    if (!path || !*path) return 0;
    size_t n = strlen(path);
    if (n >= 2 && path[n - 2] == '.' && (path[n - 1] == 'o' || path[n - 1] == 'O')) return 0;
    if (n >= 4 && path[n - 4] == '.' && path[n - 3] == 'o' && path[n - 2] == 'b' && path[n - 1] == 'j') return 0;
    if (n >= 2 && path[n - 2] == '.' && path[n - 1] == 's') return 0;
    return 1;
}

/**
 * 调用系统链接器将 .o（或 Mach-O/COFF 对象）链接为可执行文件。
 * 用于 -backend asm -o <exe> 时一条命令出可执行文件，不依赖 cc。
 * runtime_panic_o：可选，提供 shulang_panic_ 的 .o 路径（asm 后端已改为 call shulang_panic_，不链 libc 时须传此 .o）；NULL 则仅链用户 .o（可能未定义 shulang_panic_）。
 * 返回值：0 成功，-1 失败。
 */
static int invoke_ld(const char *o_path, const char *exe_path, const char *target, int use_macho_o, int use_coff_o, const char *runtime_panic_o) {
    (void)target;
    if (!o_path || !exe_path) return -1;
#if defined(__APPLE__)
    if (use_macho_o) {
        pid_t pid = fork();
        if (pid < 0) { perror("shuc: fork (ld)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, "-lSystem", (char *)NULL);
            execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, "-lSystem", (char *)NULL);
            execlp("clang", "clang", "-o", exe_path, o_path, (char *)NULL);
            perror("shuc: ld/clang");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shuc: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shuc: ld failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
#endif
    if (use_coff_o) {
        /* Windows：lld-link /entry:_main /out:exe.exe out.obj 或 link 等价 */
        char out_opt[512];
        int nn = snprintf(out_opt, sizeof(out_opt), "/out:%s", exe_path);
        if (nn < 0 || nn >= (int)sizeof(out_opt)) return -1;
        pid_t pid = fork();
        if (pid < 0) { perror("shuc: fork (link)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, runtime_panic_o, (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, runtime_panic_o, (char *)NULL);
            }
            execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, (char *)NULL);
            execlp("link", "link", "/entry:_main", out_opt, o_path, (char *)NULL);
            perror("shuc: lld-link/link");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shuc: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shuc: link failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
    /* Linux/ELF：ld -e _main -o exe o_path [runtime_panic.o]；asm 后端用 shulang_panic_，链 runtime_panic.o 可不依赖 libc */
    {
        pid_t pid = fork();
        if (pid < 0) { perror("shuc: fork (ld)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, (char *)NULL);
            else
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, (char *)NULL);
            perror("shuc: ld");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shuc: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shuc: ld failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
}
/** 调试：打印 module 中每个 func 的 name_len/name（由 Makefile 追加到 pipeline_gen.c）；便于定位 mai/ba 截断 */
extern void pipeline_debug_module_funcs(void *module);
/* 与生成代码中 codegen_CodegenOutBuf 布局一致；C 在调用后将 data[0..len-1] 写到 FILE* */
#define SU_CODEGEN_OUTBUF_CAP 262144
struct codegen_CodegenOutBuf {
    unsigned char data[SU_CODEGEN_OUTBUF_CAP];
    int32_t len;
};
/** asm 后端 C 桩：-backend asm 时由 pipeline 调用，写出最小 GAS（main return 42），便于 pipeline 不 import asm 仍可构建 shuc_su。符号供 pipeline_gen.c 链接。 */
int32_t asm_codegen_ast(void *module, void *arena, struct codegen_CodegenOutBuf *out) {
    (void)module;
    (void)arena;
    static const char *lines[] = {
        ".text",
        ".globl main",
        "main:",
        "pushq %rbp",
        "movq %rsp, %rbp",
        "subq $0, %rsp",
        "movl $42, %eax",
        "movq %rsp, %rbp",
        "popq %rbp",
        "ret"
    };
    size_t n = 0;
    for (int i = 0; i < (int)(sizeof lines / sizeof lines[0]); i++) {
        size_t len = strlen(lines[i]);
        if (n + len + 1 > (size_t)SU_CODEGEN_OUTBUF_CAP) return -1;
        memcpy(out->data + n, lines[i], len);
        out->data[n + len] = '\n';
        n += len + 1;
    }
    out->len = (int32_t)n;
    return 0;
}
/* 诊断 -su 失败阶段：pipeline_gen.c 中 parser 符号 */
struct parser_ParseIntoResult { int32_t ok; int32_t main_idx; };
extern void parser_parse_into_init(void *arena, void *module);
extern struct parser_ParseIntoResult parser_parse_into(void *arena, void *module, struct shulang_slice_uint8_t *source);
extern void parser_parse_into_set_main_index(void *module, int32_t main_idx);
extern int32_t parser_get_module_num_imports(void *module);
extern void parser_get_module_import_path(void *module, int32_t i, uint8_t *out);
extern int32_t parser_diag_fail_at_token_kind(struct shulang_slice_uint8_t *source);
extern int32_t pipeline_parse_one_function_ok(struct shulang_slice_uint8_t *source);
extern int32_t pipeline_typeck_after_parse_ok(void *arena, void *module, struct shulang_slice_uint8_t *source, void *ctx);
#ifdef SHUC_USE_SU_DRIVER
/* main.su 提供 run_compiler_c（桩），C 仅声明以便 run_compiler_su_path 内调用。 */
extern int run_compiler_c(int argc, char **argv);
#endif
/* 6.1 后 typeck/pipeline 用 ctx，以下仅保留供旧 pipeline_gen.c 或未链入 .su 时兼容；可逐步移除。 */
#if defined(SHUC_USE_SU_PIPELINE) || defined(SHUC_USE_SU_DRIVER)
void *typeck_dep_module_ptrs[32];
void *typeck_dep_arena_ptrs[32];
int typeck_ndep;
void *get_dep_module(int32_t i) {
  if (i < 0 || i >= typeck_ndep) return NULL;
  return typeck_dep_module_ptrs[i];
}
void *get_dep_arena(int32_t i) {
  if (i < 0 || i >= typeck_ndep) return NULL;
  return typeck_dep_arena_ptrs[i];
}
int32_t get_ndep(void) {
  return (int32_t)typeck_ndep;
}
/* pipeline_gen.c 中调用 typeck_get_dep_*，与 get_dep_* 同义 */
void *typeck_get_dep_module(int32_t i) { return get_dep_module(i); }
void *typeck_get_dep_arena(int32_t i) { return get_dep_arena(i); }
#endif

#ifdef SHUC_USE_SU_PREPROCESS
/* 6.4：预处理由 preprocess.su 提供；ndefines==0 时调 .su，否则回退 C。preprocess_su 符号由 -E-extern 生成（当前为 typeck_preprocess_su）。 */
extern int32_t typeck_preprocess_su(struct shulang_slice_uint8_t *source, struct shulang_slice_uint8_t *out_buf);
static char *preprocess_via_su(const char *source, size_t source_len, size_t *out_length) {
    if (!source) return NULL;
    size_t slen = source_len ? source_len : strlen(source);
    size_t out_cap = slen + 65536;
    if (out_cap < slen) return NULL;
    uint8_t *out_buf = (uint8_t *)malloc(out_cap);
    if (!out_buf) return NULL;
    struct shulang_slice_uint8_t src_slice = { (uint8_t *)source, slen };
    struct shulang_slice_uint8_t out_slice = { out_buf, out_cap };
    int32_t ret = typeck_preprocess_su(&src_slice, &out_slice);
    if (ret < 0) {
        free(out_buf);
        return NULL;
    }
    char *result = (char *)malloc((size_t)ret + 1);
    if (!result) {
        free(out_buf);
        return NULL;
    }
    memcpy(result, out_buf, (size_t)ret);
    result[ret] = '\0';
    free(out_buf);
    if (out_length) *out_length = (size_t)ret;
    return result;
}
char *preprocess(const char *source, size_t source_len, const char **defines, int ndefines, size_t *out_length) {
    if (out_length) *out_length = 0;
    if (!source) return NULL;
    if (ndefines == 0) {
        char *r = preprocess_via_su(source, source_len, out_length);
        if (r) return r;
    }
    return preprocess_c_fallback(source, source_len, defines, ndefines, out_length);
}
#endif

/* 阶段 5.3 / 6.2：.su 内写编排逻辑，C 只提供最小 I/O 原语。 */
#define PIPELINE_IMPORT_BUF_CAP 262144
static char pipeline_entry_dir_buf[512];
static const char *pipeline_entry_dir = ".";
static char pipeline_resolved_path_buf[512];
static void *pipeline_dep_arena_slots[32];
static void *pipeline_dep_module_slots[32];
static char *pipeline_loaded_import_buf;
static size_t pipeline_loaded_import_len;
static size_t pipeline_loaded_import_cap;
void pipeline_set_entry_dir(const char *path) {
    if (path && path[0]) {
        (void)snprintf(pipeline_entry_dir_buf, sizeof(pipeline_entry_dir_buf), "%s", path);
        pipeline_entry_dir = pipeline_entry_dir_buf;
    } else {
        pipeline_entry_dir = ".";
    }
}
void pipeline_set_dep_slots(void *arenas[32], void *modules[32]) {
    for (int i = 0; i < 32; i++) {
        pipeline_dep_arena_slots[i] = arenas ? arenas[i] : NULL;
        pipeline_dep_module_slots[i] = modules ? modules[i] : NULL;
    }
}
/** 原语：仅把 import 路径解析成文件系统路径并写入内部 buffer，返回 0 成功 -1 失败。由 .su 决定何时、对谁调用。 */
int32_t pipeline_resolve_path(const uint8_t *path_ptr, int32_t path_len) {
    char path_c[65];
    size_t k = 0;
    if (path_len <= 0 || path_len > 64) path_len = 64;
    while (k < (size_t)path_len && path_ptr[k]) {
        path_c[k] = (char)path_ptr[k];
        k++;
    }
    path_c[k] = '\0';
    const char *lib_roots[1] = { "." };
    resolve_import_file_path_multi(lib_roots, 1, pipeline_entry_dir, path_c, pipeline_resolved_path_buf, sizeof(pipeline_resolved_path_buf));
    return 0;
}
/** 原语：把当前 resolved 路径对应的文件读入并预处理，结果写入 loaded buffer，返回 0 成功 -1 失败。由 .su 在 resolve_path 之后按需调用。 */
int32_t pipeline_read_file(void) {
    size_t raw_len = 0;
    char *raw = read_file(pipeline_resolved_path_buf, &raw_len);
    if (!raw) {
        fprintf(stderr, "shuc: cannot open import (tried %s)\n", pipeline_resolved_path_buf);
        return -1;
    }
    size_t prep_len = 0;
    char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
    free(raw);
    if (!prep) {
        fprintf(stderr, "shuc: preprocess failed for import\n");
        return -1;
    }
    if (prep_len > pipeline_loaded_import_cap || !pipeline_loaded_import_buf) {
        free(pipeline_loaded_import_buf);
        pipeline_loaded_import_cap = prep_len < PIPELINE_IMPORT_BUF_CAP ? PIPELINE_IMPORT_BUF_CAP : prep_len + 65536;
        pipeline_loaded_import_buf = (char *)malloc(pipeline_loaded_import_cap);
        if (!pipeline_loaded_import_buf) {
            free(prep);
            return -1;
        }
    }
    memcpy(pipeline_loaded_import_buf, prep, prep_len);
    pipeline_loaded_import_len = prep_len;
    free(prep);
    return 0;
}
void *pipeline_get_dep_arena_slot(int32_t i) {
    if (i < 0 || i >= 32) return NULL;
    return pipeline_dep_arena_slots[i];
}
void *pipeline_get_dep_module_slot(int32_t i) {
    if (i < 0 || i >= 32) return NULL;
    return pipeline_dep_module_slots[i];
}
void pipeline_set_dep(int32_t i, void *mod, void *arena) {
    if (i < 0 || i >= 32) return;
    typeck_dep_module_ptrs[i] = mod;
    typeck_dep_arena_ptrs[i] = arena;
}
void pipeline_set_ndep(int32_t n) {
    typeck_ndep = n <= 32 ? n : 32;
}
int32_t pipeline_parse_into_loaded_import(void *arena, void *module) {
    struct shulang_slice_uint8_t slice = {
        .data = pipeline_loaded_import_buf ? (uint8_t *)pipeline_loaded_import_buf : NULL,
        .length = pipeline_loaded_import_len
    };
    if (!slice.data) return -1;
    parser_parse_into_init(arena, module);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &slice);
    return pr.ok == 0 ? 0 : -1;
}

/** 6.1 原 C 桥接：已由 pipeline.su 的 pipeline_parse_into_buf（调 parser.parse_into_buf）替代，此处不再编译以免重复符号。 */
#if 0
int32_t pipeline_parse_into_buf(void *arena, void *module, const uint8_t *buf, int32_t buf_len) {
    if (!buf) return -1;
    struct shulang_slice_uint8_t slice = { .data = (uint8_t *)buf, .length = (size_t)buf_len };
    parser_parse_into_init(arena, module);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &slice);
    return pr.ok == 0 ? 0 : -1;
}
#endif
#endif
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>

/**
 * 读入整个文件为 NUL 结尾的堆分配字符串。
 * 功能说明：用于读入 .su 源码或 import 的模块文件，供 Lexer/Parser 使用。
 * 参数：path 文件系统路径，只读；须可访问且为普通文件。
 * 返回值：成功返回 malloc 的缓冲区（含结尾 NUL），调用方须 free；失败（无法打开、seek/read 错误）返回 NULL。
 * 错误与边界：空文件返回非 NULL 且 buf[0]='\0'；path 为 NULL 或不可打开时返回 NULL。
 * 若 out_len 非 NULL，则 *out_len 为读入的字节数（不含结尾 NUL），供 preprocess 按长度扫描避免嵌入 NUL 截断。
 * 副作用与约定：分配内存，无静态状态；不修改 path。
 */
static char *read_file(const char *path, size_t *out_len);

/**
 * 将 import 路径字符串转为库根下的 .su 文件路径。
 * 功能说明：例如 "core.types" 在 lib_root 为 "." 时得到 "./core/types.su"，供 read_file 打开。
 * 参数：lib_root 标准库根目录，若为 NULL 或空则视为 "."；import_path 如 "core.types"；path 输出缓冲区；path_size 缓冲区字节数，建议至少 512。
 * 返回值：无；结果写入 path，保证 NUL 结尾（若 path_size>0）。
 * 错误与边界：path_size 过小可能导致截断；import_path 中的 '.' 均替换为 '/'。
 * 副作用与约定：仅写 path，不分配内存；不修改 lib_root、import_path。
 */
static void import_path_to_file_path(const char *lib_root, const char *import_path, char *path, size_t path_size) {
    const char *r = lib_root && lib_root[0] ? lib_root : ".";
    size_t off = (size_t)snprintf(path, path_size, "%s/", r);
    for (const char *s = import_path; *s && off + 1 < path_size; s++) {
        if (*s == '.')
            path[off++] = '/';
        else
            path[off++] = *s;
    }
    if (off + 4 <= path_size)
        snprintf(path + off, path_size - off, ".su");
}

/**
 * 从入口文件路径得到其所在目录，用于多文件时从同目录解析 import（阶段 7.3）。
 * 参数：input_path 入口 .su 路径；entry_dir 输出缓冲区；size 缓冲区大小。
 * 无目录时写入 "."。
 */
static void get_entry_dir(const char *input_path, char *entry_dir, size_t size) {
    if (!input_path || !entry_dir || size == 0) {
        if (size) entry_dir[0] = '\0';
        return;
    }
    const char *last = strrchr(input_path, '/');
    if (!last) {
        (void)snprintf(entry_dir, size, ".");
        return;
    }
    size_t len = (size_t)(last - input_path);
    if (len >= size) len = size - 1;
    memcpy(entry_dir, input_path, len);
    entry_dir[len] = '\0';
}

/**
 * 解析 import 路径到实际 .su 文件路径：依次在 lib_roots[0..n_lib_roots-1] 下查找；先试单文件再试 mod.su；若均无且为单段路径则试 entry_dir（多文件 7.3）。支持多 -L（9.1 联调 std+lexer）。
 * 参数：lib_roots 库根数组；n_lib_roots 个数；entry_dir 入口所在目录（可为 NULL 或 ""）；import_path 如 "foo" 或 "core.types"；path 输出；path_size 缓冲区大小。
 */
static void resolve_import_file_path_multi(const char **lib_roots, int n_lib_roots, const char *entry_dir, const char *import_path, char *path, size_t path_size) {
    for (int r = 0; r < n_lib_roots; r++) {
        const char *lib_root = lib_roots[r] && lib_roots[r][0] ? lib_roots[r] : ".";
        import_path_to_file_path(lib_root, import_path, path, path_size);
        if (access(path, R_OK) == 0) return;
        if (strchr(import_path, '.') != NULL && path_size >= 16) {
            size_t off = (size_t)snprintf(path, path_size, "%s/", lib_root);
            for (const char *s = import_path; *s && off + 1 < path_size; s++)
                path[off++] = (char)(*s == '.' ? '/' : *s);
            if (off + 9 <= path_size)
                (void)snprintf(path + off, path_size - off, "/mod.su");
            if (access(path, R_OK) == 0) return;
            import_path_to_file_path(lib_root, import_path, path, path_size);
            if (access(path, R_OK) == 0) return;
        }
    }
    if (entry_dir && entry_dir[0] && strchr(import_path, '.') == NULL) {
        (void)snprintf(path, path_size, "%s/%.255s.su", entry_dir, import_path);
    }
}

#define MAX_ALL_DEPS 32

/**
 * 在已加载列表中按 import 路径查找模块下标；用于递归加载时判断是否已加载、以及 typeck 时取 dep 数组。
 * 参数：import_path 如 "std.io.core"；all_paths 已加载路径数组；n_all 个数。
 * 返回值：下标 0..n_all-1，未找到返回 -1。
 */
static int find_loaded_index(const char *import_path, char **all_paths, int n_all) {
    for (int i = 0; i < n_all; i++)
        if (all_paths[i] && strcmp(all_paths[i], import_path) == 0)
            return i;
    return -1;
}

/**
 * 从入口文件路径推导 -E 时库模块的 C 前缀（用于 codegen_library_module_to_c）。
 * 例如 src/pipeline/pipeline.su -> "pipeline"，src/typeck/typeck.su -> "typeck"。
 * 供 -E 单文件展开时入口为无 main 的库模块使用。
 */
static const char *entry_lib_name_from_path(const char *input_path) {
    if (!input_path) return "typeck";
    if (strstr(input_path, "main") != NULL) return "main";   /* src/main.su 与 main.c 一一对应 */
    if (strstr(input_path, "build") != NULL) return "build"; /* 阶段 7：根目录 build.su → build_entry */
    if (strstr(input_path, "pipeline") != NULL) return "pipeline";
    if (strstr(input_path, "driver") != NULL) return "driver";
    if (strstr(input_path, "codegen") != NULL) return "codegen";
    if (strstr(input_path, "typeck") != NULL) return "typeck";
    if (strstr(input_path, "parser") != NULL) return "parser";
    /* token 须在 lexer 前，否则 src/lexer/token.su 会误得 lexer_ 前缀 */
    if (strstr(input_path, "token") != NULL) return "token";
    if (strstr(input_path, "lexer") != NULL) return "lexer";
    if (strstr(input_path, "ast") != NULL) return "ast";
    return "typeck";
}

/**
 * 递归加载单条 import：若已存在于 all_dep_mods/all_dep_paths 则直接返回；否则解析→递归加载其 import→typeck(其 deps)→加入列表。
 * 参数：import_path 如 "std.io.driver"；lib_root、entry_dir、defines/ndefines 同 resolve_import_file_path；all_dep_mods/all_dep_paths 输出列表；n_all 当前个数（会递增）；max_all 上限。
 * 返回值：成功返回对应 ASTModule*；失败返回 NULL（调用方须释放已写入的 all_dep_*）。
 */
static ASTModule *load_one_import(const char *import_path, const char **lib_roots, int n_lib_roots, const char *entry_dir,
    const char **defines, int ndefines,
    ASTModule **all_dep_mods, char **all_dep_paths, int *n_all, int max_all) {
    int idx = find_loaded_index(import_path, all_dep_paths, *n_all);
    if (idx >= 0)
        return all_dep_mods[idx];
    if (*n_all >= max_all) {
        fprintf(stderr, "shuc: too many transitive imports\n");
        return NULL;
    }
    char path[512];
    resolve_import_file_path_multi(lib_roots, n_lib_roots, entry_dir, import_path, path, sizeof(path));
    char *raw = read_file(path, NULL);
    if (!raw) {
        fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", import_path, path);
        return NULL;
    }
    char *src = preprocess(raw, 0, defines, ndefines, NULL);
    free(raw);
    if (!src) {
        fprintf(stderr, "shuc: preprocess failed for import '%s'\n", import_path);
        return NULL;
    }
    Lexer *lex = lexer_new(src);
    ASTModule *dep = NULL;
    int pr = parse(lex, &dep);
    lexer_free(lex);
    free(src);
    if (pr != 0 || !dep) {
        fprintf(stderr, "shuc: failed to parse import '%s'\n", import_path);
        return NULL;
    }
    /* 先递归加载该模块的 import，保证 typeck 时其 deps 已在 all_dep_mods 中 */
    for (int i = 0; i < dep->num_imports; i++) {
        ASTModule *sub = load_one_import(dep->import_paths[i], lib_roots, n_lib_roots, entry_dir, defines, ndefines,
            all_dep_mods, all_dep_paths, n_all, max_all);
        if (!sub) {
            ast_module_free(dep);
            return NULL;
        }
    }
    /* 构建该模块的 dep 数组（与 dep->import_paths 顺序一致），供 typeck */
    ASTModule *deps[32];
    int ndeps = 0;
    for (int j = 0; j < dep->num_imports && ndeps < 32; j++) {
        idx = find_loaded_index(dep->import_paths[j], all_dep_paths, *n_all);
        if (idx >= 0)
            deps[ndeps++] = all_dep_mods[idx];
    }
    if (typeck_module(dep, deps, ndeps, NULL, 0) != 0) {
        fprintf(stderr, "shuc: typeck failed for import '%s'\n", import_path);
        ast_module_free(dep);
        return NULL;
    }
    all_dep_mods[*n_all] = dep;
    all_dep_paths[*n_all] = strdup(import_path);
    if (!all_dep_paths[*n_all]) {
        ast_module_free(dep);
        return NULL;
    }
    (*n_all)++;
    return dep;
}

/**
 * 解析并类型检查所有 import 依赖（含传递依赖）；填入 direct dep_mods（与 mod->import_paths 一一对应）供 typeck/codegen 入口使用，并填入 all_dep_mods/all_dep_paths（拓扑序）供 -o 时为每个依赖生成 .c（阶段 7.3 跨模块调用 + 传递依赖）。
 * 参数：mod 入口模块；lib_root、entry_dir 同 resolve_import_file_path；defines/ndefines 条件编译符号；dep_mods/ndep_out 仅直接依赖；all_dep_mods、all_dep_paths、n_all_out 为全部传递依赖（all_dep_paths 由本函数 strdup，调用方须 free）；max_deps 为 direct 与 all 共用上限。
 * 返回值：0 成功；-1 失败且已释放已写入的 all_dep_*。
 */
static int resolve_and_load_imports(ASTModule *mod, const char **lib_roots, int n_lib_roots, const char *entry_dir,
    const char **defines, int ndefines,
    ASTModule **dep_mods, int *ndep_out,
    ASTModule **all_dep_mods, char **all_dep_paths, int *n_all_out, int max_deps) {
    int n_all = 0;
    for (int i = 0; i < mod->num_imports && i < max_deps; i++) {
        ASTModule *m = load_one_import(mod->import_paths[i], lib_roots, n_lib_roots, entry_dir, defines, ndefines,
            all_dep_mods, all_dep_paths, &n_all, max_deps);
        if (!m) {
            while (n_all--) {
                free(all_dep_paths[n_all]);
                ast_module_free(all_dep_mods[n_all]);
            }
            return -1;
        }
        dep_mods[i] = m;
    }
    *ndep_out = mod->num_imports;
    *n_all_out = n_all;
    return 0;
}

/**
 * 将 Token 类型枚举转为可读字符串，用于控制台打印。
 * 功能说明：供无 -o 时打印 Token 序列使用，返回如 "FN"、"IDENT"、"INT" 等。
 * 参数：k 当前 Token 的 kind。
 * 返回值：指向静态字符串的指针，只读；未知 kind 返回 "?"。
 * 错误与边界：无；不分配内存。
 * 副作用与约定：无副作用；返回值不得被 free。
 */
static const char *token_kind_str(TokenKind k) {
    switch (k) {
        case TOKEN_EOF:     return "EOF";
        case TOKEN_FUNCTION: return "FUNCTION";
        case TOKEN_LET:     return "LET";
        case TOKEN_CONST:   return "CONST";
        case TOKEN_IF:      return "IF";
        case TOKEN_ELSE:    return "ELSE";
        case TOKEN_WHILE:   return "WHILE";
        case TOKEN_LOOP:    return "LOOP";
        case TOKEN_FOR:     return "FOR";
        case TOKEN_BREAK:   return "BREAK";
        case TOKEN_CONTINUE: return "CONTINUE";
        case TOKEN_RETURN:   return "RETURN";
        case TOKEN_PANIC:   return "PANIC";
        case TOKEN_DEFER:   return "DEFER";
        case TOKEN_MATCH:   return "MATCH";
        case TOKEN_STRUCT:  return "STRUCT";
        case TOKEN_PACKED:  return "PACKED";
        case TOKEN_ENUM:    return "ENUM";
        case TOKEN_GOTO:    return "GOTO";
        case TOKEN_TRAIT:   return "TRAIT";
        case TOKEN_IMPL:    return "IMPL";
        case TOKEN_SELF:    return "SELF";
        case TOKEN_UNDERSCORE: return "UNDERSCORE";
        case TOKEN_IDENT:   return "IDENT";
        case TOKEN_I32:     return "I32";
        case TOKEN_BOOL:    return "BOOL";
        case TOKEN_U8:      return "U8";
        case TOKEN_U32:     return "U32";
        case TOKEN_U64:     return "U64";
        case TOKEN_I64:     return "I64";
        case TOKEN_USIZE:   return "USIZE";
        case TOKEN_ISIZE:   return "ISIZE";
        case TOKEN_I32X4:   return "I32X4";
        case TOKEN_I32X8:   return "I32X8";
        case TOKEN_I32X16:  return "I32X16";
        case TOKEN_U32X4:   return "U32X4";
        case TOKEN_U32X8:   return "U32X8";
        case TOKEN_U32X16:  return "U32X16";
        case TOKEN_TRUE:    return "TRUE";
        case TOKEN_FALSE:   return "FALSE";
        case TOKEN_F32:     return "F32";
        case TOKEN_F64:     return "F64";
        case TOKEN_VOID:    return "VOID";
        case TOKEN_INT:     return "INT";
        case TOKEN_FLOAT:   return "FLOAT";
        case TOKEN_LPAREN:  return "LPAREN";
        case TOKEN_RPAREN:  return "RPAREN";
        case TOKEN_LBRACE:  return "LBRACE";
        case TOKEN_RBRACE:  return "RBRACE";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_ARROW:   return "ARROW";
        case TOKEN_FATARROW: return "FATARROW";
        case TOKEN_COMMA:   return "COMMA";
        case TOKEN_COLON:   return "COLON";
        case TOKEN_IMPORT:  return "IMPORT";
        case TOKEN_EXTERN:  return "EXTERN";
        case TOKEN_DOT:     return "DOT";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_PLUS:   return "PLUS";
        case TOKEN_MINUS:  return "MINUS";
        case TOKEN_STAR:   return "STAR";
        case TOKEN_SLASH:  return "SLASH";
        case TOKEN_PERCENT: return "PERCENT";
        case TOKEN_AMP:    return "AMP";
        case TOKEN_PIPE:   return "PIPE";
        case TOKEN_CARET:  return "CARET";
        case TOKEN_LSHIFT: return "LSHIFT";
        case TOKEN_RSHIFT: return "RSHIFT";
        case TOKEN_TILDE:  return "TILDE";
        case TOKEN_EQ:     return "EQ";
        case TOKEN_NE:     return "NE";
        case TOKEN_LT:     return "LT";
        case TOKEN_GT:     return "GT";
        case TOKEN_LE:     return "LE";
        case TOKEN_GE:     return "GE";
        case TOKEN_AMPAMP: return "AMPAMP";
        case TOKEN_PIPEPIPE: return "PIPEPIPE";
        case TOKEN_BANG:   return "BANG";
        case TOKEN_QUESTION: return "QUESTION";
        case TOKEN_ASSIGN: return "ASSIGN";
        default:            return "?";
    }
}

/* read_file 实现：见上方声明处注释 */
static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long size = ftell(f);
    if (size < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)size, f);
    fclose(f);
    if (n != (size_t)size) { free(buf); return NULL; }
    buf[n] = '\0';
    if (out_len) *out_len = n;
    return buf;
}

/** 多文件编译时 C 文件数量上限（入口 + import 闭包） */
#define MAX_C_FILES 33

/**
 * 调用系统 cc 将多个 C 文件编译链接为可执行文件。
 * 功能说明：阶段 7.3 多文件；阶段 8 优化：向 cc 传入 -O<level>（默认 -O2）与 -o out_path。不向 cc 传 -target（仅 Clang 支持，GCC 报错）；shuc 的 -target 仅用于预处理注入 OS_LINUX 等宏。
 * 返回值：0 表示 cc 执行成功且退出码为 0；-1 表示参数非法、fork/exec 失败或 cc 非零退出。
 */
static int invoke_cc(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level) {
    (void)target;
    if (!c_paths || n < 1) return -1;
    if (!opt_level || !*opt_level) opt_level = "2";
    pid_t pid = fork();
    if (pid < 0) {
        perror("shuc: fork");
        return -1;
    }
    if (pid == 0) {
        char *argv[MAX_C_FILES + 10];
        int i = 0;
        argv[i++] = (char *)"cc";
        {
            static char oopt_buf[8];
            (void)snprintf(oopt_buf, sizeof(oopt_buf), "-O%s", opt_level);
            argv[i++] = oopt_buf;
        }
        /* 阶段 8：非调试时传 -DNDEBUG，便于依赖 assert 的代码在发布构建中关闭断言 */
        if (strcmp(opt_level, "0") != 0)
            argv[i++] = (char *)"-DNDEBUG";
        argv[i++] = (char *)"-o";
        argv[i++] = (char *)out_path;
        for (int j = 0; j < n && i < MAX_C_FILES + 8; j++)
            argv[i++] = (char *)c_paths[j];
        argv[i++] = NULL;
        execvp("cc", argv);
        perror("shuc: cc");
        _exit(127);
    }
    int status;
    if (waitpid(pid, &status, 0) != pid) {
        perror("shuc: waitpid");
        return -1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "shuc: cc failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
        return -1;
    }
    /* 阶段 8：非调试（-O0）时对产出执行 strip，减小体积（避免传 -s 给 cc 触发 ld 的 obsolete 警告） */
    if (strcmp(opt_level, "0") != 0) {
        pid_t spid = fork();
        if (spid == 0) {
            execlp("strip", "strip", out_path, (char *)NULL);
            _exit(127);
        }
        if (spid > 0) {
            int sstatus;
            (void)waitpid(spid, &sstatus, 0);
        }
    }
    return 0;
}

/** 阶段 8.1 DCE 上下文：供 dce_is_func_used / dce_is_mono_used / dce_is_type_used 回调使用。 */
struct dce_ctx {
    ASTFunc **used;
    int n;
    int (*mono)[64];
    int mono_rows;
    const char **used_type_names;
    int n_used_types;
    ASTModule *entry;
    ASTModule **deps;
    int nd;
};
static int dce_is_func_used(void *ctx, const ASTModule *mod, const ASTFunc *func) {
    const struct dce_ctx *c = (const struct dce_ctx *)ctx;
    if (!c || !c->used) return 1;
    /* 库模块（非入口）：始终保留符号，避免入口 extern 引用的 import 函数被误删导致链接失败 */
    if (mod != c->entry) return 1;
    for (int i = 0; i < c->n; i++)
        if (c->used[i] == func) return 1;
    return 0;
}
static int dce_is_mono_used(void *ctx, const ASTModule *mod, int k) {
    const struct dce_ctx *c = (const struct dce_ctx *)ctx;
    if (!c || !c->mono || k < 0 || k >= 64) return 1;
    /* 库模块：始终保留单态化实例，避免入口引用的泛型 import 被误删 */
    if (mod != c->entry) return 1;
    int idx = (mod == c->entry) ? 0 : -1;
    if (idx < 0 && c->deps)
        for (int i = 0; i < c->nd; i++)
            if (c->deps[i] == mod) { idx = 1 + i; break; }
    if (idx < 0 || idx >= c->mono_rows) return 1;
    return c->mono[idx][k];
}

/** 阶段 8.1 DCE 扩展：类型名在 used_type_names 中则保留，否则删除；库模块类型始终保留。 */
static int dce_is_type_used(void *ctx, const ASTModule *mod, const char *type_name) {
    const struct dce_ctx *c = (const struct dce_ctx *)ctx;
    if (!c || !type_name) return 1;
    if (mod != c->entry) return 1;
    if (!c->used_type_names) return 1;
    for (int i = 0; i < c->n_used_types; i++)
        if (c->used_type_names[i] && strcmp(c->used_type_names[i], type_name) == 0) return 1;
    return 0;
}

/**
 * 编译器主入口：解析命令行，执行 lexer→parser→typeck，可选 codegen→cc 产出可执行文件。
 * 功能说明：支持 -L、-target、-o；无 -o 时打印 Token 与 parse/typeck OK（供测试）；有 -o 时生成 C（含 import 占位）、调用 cc 链接。
 * 参数：argc、argv 为标准 C 程序参数；argv[0] 为程序名，后续为可选 -L/-target/-o 及其参数与一个输入 .su 路径。
 * 返回值：0 表示成功（含无参数时打印用法）；1 表示读文件失败、解析/typeck 失败、codegen 或 cc 失败。
 * 错误与边界：无输入文件时打印用法并返回 0；-o 指定但无 main 时返回 1；import 数量超过 32 时仅处理前 32 个。
 * 副作用与约定：可能创建/删除 /tmp 下临时文件；依赖 getenv("SHULANG_LIB")；多文件时可能多次解析同一 import 的 .su。
 */
#define MAX_DEFINES 64
#define MAX_LIB_ROOTS 8
/**
 * 编译器 pipeline 实现（原 main 逻辑）；供 C main 直接调用，或由 .su driver 入口转调（6.3）。
 * SHUC_USE_SU_DRIVER 时 run_compiler_c_impl 由 main.su 提供（桩），C 不定义以免重复符号。
 */
#if defined(SHUC_USE_SU_DRIVER)
/* run_compiler_c_impl 由 main.su 提供（桩），C 不定义。 */
#else
#define RUN_CC_FUNC run_compiler_c
int RUN_CC_FUNC(int argc, char **argv) {
#ifdef SHUC_USE_SU_FRONTEND
    /* 阶段 3.2：链入 _su.o 时不再提供 typeck_module/codegen_* 等 C 符号，run_compiler_c 不应被调用；main 已走 run_compiler_su_path。 */
    (void)argc;
    (void)argv;
    fprintf(stderr, "shuc: internal error: run_compiler_c called with SHUC_USE_SU_FRONTEND\n");
    return 1;
#else
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_roots_arr[MAX_LIB_ROOTS];
    int n_lib_roots = 0;
    const char *target = NULL;
    const char *opt_level = NULL;  /* -O 优化级别：0/2/s，默认 2（阶段 8） */
    int emit_c_only = 0;  /* -E：仅生成 C 到 stdout，不调用 cc */
    int emit_extern_imports = 0;  /* 阶段 3.1：-E-extern 时仅展开入口，import 用 extern，生成瘦 C */
    #ifdef SHUC_USE_SU_PIPELINE
    int use_su_pipeline = 0;  /* -su：使用纯 .su 流水线（需链接 pipeline_gen.o） */
    int use_asm_backend = 0;  /* -backend asm：出汇编而非 C，并走 -su pipeline */
    #endif
    const char *defines[MAX_DEFINES];
    int ndefines = 0;

    for (int i = 1; i < argc; i++) {
        #ifdef SHUC_USE_SU_PIPELINE
        if (strcmp(argv[i], "-su") == 0) {
            use_su_pipeline = 1;
        } else if (strcmp(argv[i], "-backend") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "shuc: -backend requires an argument (e.g. asm)\n");
                return 1;
            }
            if (strcmp(argv[i + 1], "asm") == 0) use_asm_backend = 1;
            use_su_pipeline = 1;  /* -backend asm 必须走 .su pipeline */
            i++;
        } else
        #endif
        if (strcmp(argv[i], "-E") == 0) {
            emit_c_only = 1;
        } else if (strcmp(argv[i], "-E-extern") == 0) {
            emit_c_only = 1;
            emit_extern_imports = 1;
        } else if (strcmp(argv[i], "-D") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            if (ndefines >= MAX_DEFINES) {
                fprintf(stderr, "shuc: too many -D defines\n");
                return 1;
            }
            defines[ndefines++] = argv[i + 1];
            i++;
        } else if (strncmp(argv[i], "-D", 2) == 0 && argv[i][2] != '\0') {
            /* -DSYMBOL 形式 */
            if (ndefines >= MAX_DEFINES) {
                fprintf(stderr, "shuc: too many -D defines\n");
                return 1;
            }
            defines[ndefines++] = argv[i] + 2;
        } else if (strcmp(argv[i], "-O") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            opt_level = argv[i + 1];
            if (strcmp(opt_level, "0") != 0 && strcmp(opt_level, "2") != 0 && strcmp(opt_level, "s") != 0) {
                fprintf(stderr, "shuc: -O expects 0, 2, or s (got '%s')\n", opt_level);
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            out_path = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            if (n_lib_roots < MAX_LIB_ROOTS)
                lib_roots_arr[n_lib_roots++] = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-target") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            target = argv[i + 1];
            i++;
        } else if (argv[i][0] == '-') {
            /* 未知选项（如 -backend 在未链 pipeline 的构建中）：提示而非当作输入文件 */
            if (strcmp(argv[i], "-backend") == 0) {
                fprintf(stderr, "shuc: -backend asm not available in this build. Use: make bootstrap-driver\n");
            } else {
                fprintf(stderr, "shuc: unknown option '%s'\n", argv[i]);
            }
            return 1;
        } else if (!input_path) {
            input_path = argv[i];
        }
    }
    /* 由 -target 推导 OS 宏，供 #if OS_LINUX 等使用 */
    if (target && ndefines < MAX_DEFINES) {
        if (strstr(target, "linux") != NULL) {
            defines[ndefines++] = "OS_LINUX";
        } else if (strstr(target, "darwin") != NULL || strstr(target, "apple") != NULL) {
            defines[ndefines++] = "OS_MACOS";
        } else if (strstr(target, "windows") != NULL) {
            defines[ndefines++] = "OS_WINDOWS";
        }
    }
    /* §3.4 条件编译与平台选择：无 -target 时用 uname 注入 SHU_OS_<SYSNAME>、SHU_ARCH_<MACHINE>（全大写）供 .su #if 使用 */
    if (ndefines + 2 <= MAX_DEFINES) {
        struct utsname u;
        /* utsname.sysname/machine can be up to 65 bytes; "SHU_OS_"=7, "SHU_ARCH_"=9, so 80 suffices */
        static char shu_os_def[80], shu_arch_def[80];
        if (uname(&u) == 0) {
            (void)snprintf(shu_os_def, sizeof(shu_os_def), "SHU_OS_%s", u.sysname);
            (void)snprintf(shu_arch_def, sizeof(shu_arch_def), "SHU_ARCH_%s", u.machine);
            for (char *p = shu_os_def + 7; *p; p++) *p = (char)toupper((unsigned char)*p);
            for (char *p = shu_arch_def + 9; *p; p++) *p = (char)toupper((unsigned char)*p);
            defines[ndefines++] = shu_os_def;
            defines[ndefines++] = shu_arch_def;
        }
    }
    if (n_lib_roots == 0) {
        lib_roots_arr[0] = getenv("SHULANG_LIB");
        if (!lib_roots_arr[0]) lib_roots_arr[0] = ".";
        n_lib_roots = 1;
    }
    if (!opt_level) opt_level = getenv("SHULANG_OPT");
    if (!opt_level || !*opt_level) opt_level = "2";

    if (!input_path) {
        fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
        return 0;
    }

    size_t raw_src_len = 0;
    char *raw_src = read_file(input_path, &raw_src_len);
    if (!raw_src) {
        fprintf(stderr, "Error: cannot read file '%s'\n", input_path);
        return 1;
    }
    size_t src_len = 0;
    char *src = preprocess(raw_src, raw_src_len, ndefines > 0 ? defines : NULL, ndefines, &src_len);
    free(raw_src);
    if (!src) {
        fprintf(stderr, "shuc: preprocess failed for '%s'\n", input_path);
        return 1;
    }

#ifdef SHUC_USE_SU_PIPELINE
    if (use_su_pipeline) {
        size_t arena_sz = pipeline_sizeof_arena();
        size_t module_sz = pipeline_sizeof_module();
        void *arena = malloc(arena_sz);
        void *module = malloc(module_sz);
        if (!arena || !module) {
            fprintf(stderr, "shuc: -su pipeline: malloc failed\n");
            if (arena) free(arena);
            if (module) free(module);
            free(src);
            return 1;
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        struct shulang_slice_uint8_t src_slice = { (uint8_t *)src, src_len };
        parser_parse_into_init(arena, module);
        struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
        if (pr.ok != 0) {
            fprintf(stderr, "shuc: -su pipeline failed (parse_into)\n");
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        parser_parse_into_set_main_index(module, pr.main_idx);
        /* pipeline_debug_module_funcs(module);  调试 mai/ba 时取消注释 */
        int32_t n_imports = parser_get_module_num_imports(module);
        char entry_dir_buf[512];
        get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
        const char *entry_dir = entry_dir_buf;
        /* 阶段 5：有 import 时先 resolve 并 pipeline 各依赖，再 pipeline 入口 */
        char *dep_sources[MAX_ALL_DEPS];
        size_t dep_lens[MAX_ALL_DEPS];
        char *dep_paths[MAX_ALL_DEPS];
        int n_deps = 0;
        if (n_imports > 0 && n_imports <= 32) {
            for (int i = 0; i < n_imports && n_deps < MAX_ALL_DEPS; i++) {
                uint8_t path_buf[64];
                parser_get_module_import_path(module, i, path_buf);
                char path_c[65];
                size_t k = 0;
                while (k < sizeof(path_buf) && path_buf[k]) {
                    path_c[k] = (char)path_buf[k];
                    k++;
                }
                path_c[k] = '\0';
                if (find_loaded_index(path_c, dep_paths, n_deps) >= 0)
                    continue;
                char resolved[512];
                resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir, path_c, resolved, sizeof(resolved));
                size_t raw_len = 0;
                char *raw = read_file(resolved, &raw_len);
                if (!raw) {
                    fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", path_c, resolved);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                size_t prep_len = 0;
                char *prep = preprocess(raw, raw_len, ndefines > 0 ? defines : NULL, ndefines, &prep_len);
                free(raw);
                if (!prep) {
                    fprintf(stderr, "shuc: preprocess failed for import '%s'\n", path_c);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                dep_sources[n_deps] = prep;
                dep_lens[n_deps] = prep_len;
                dep_paths[n_deps] = strdup(path_c);
                if (!dep_paths[n_deps]) {
                    free(prep);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                n_deps++;
            }
        }
        typeck_ndep = 0;
        /* -backend asm 且指定 -o 时，将汇编输出写入文件；-o xxx.o 则直接写 ELF/Mach-O/COFF；-o <exe> 无后缀则先写临时 .o 再调 ld 出可执行文件 */
        FILE *asm_out = NULL;
        int emit_elf_o = 0;
        void *elf_ctx_ptr = NULL;
        char asm_tmp_o_path[64];
        int asm_want_exe = 0;
        asm_tmp_o_path[0] = '\0';
        if (use_asm_backend && out_path) {
            asm_want_exe = output_want_exe(out_path);
            if (asm_want_exe) {
                strcpy(asm_tmp_o_path, "/tmp/shuc_asm_XXXXXX");
                int fd = mkstemp(asm_tmp_o_path);
                if (fd < 0) {
                    perror("shuc: mkstemp (asm)");
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                asm_out = fdopen(fd, "wb");
                if (!asm_out) {
                    close(fd);
                    unlink(asm_tmp_o_path);
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                emit_elf_o = 1;
            } else {
                asm_out = fopen(out_path, "wb");
                if (!asm_out) {
                    perror("shuc: -o (asm)");
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                emit_elf_o = output_is_elf_o(out_path);
            }
            if (emit_elf_o) {
                elf_ctx_ptr = malloc(pipeline_sizeof_elf_ctx());
                if (!elf_ctx_ptr) {
                    fprintf(stderr, "shuc: elf_ctx alloc failed\n");
                    fclose(asm_out);
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
                memset(elf_ctx_ptr, 0, pipeline_sizeof_elf_ctx());
            }
        }
        struct codegen_CodegenOutBuf out_buf;
        memset(&out_buf, 0, sizeof(out_buf));
        /* 阶段 5.2：为每个 dep 单独分配 arena/module，先跑完各 dep 的 pipeline 并保留指针，再跑入口 pipeline 时 typeck 可解析跨模块调用 */
        void *dep_arenas[32];
        void *dep_modules[32];
        for (int i = 0; i < n_deps; i++) {
            dep_arenas[i] = malloc(arena_sz);
            dep_modules[i] = malloc(module_sz);
            if (!dep_arenas[i] || !dep_modules[i]) {
                fprintf(stderr, "shuc: -su pipeline: dep alloc failed\n");
                if (asm_out) fclose(asm_out);
                if (elf_ctx_ptr) free(elf_ctx_ptr);
                while (i > 0) { i--; free(dep_arenas[i]); free(dep_modules[i]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena);
                free(module);
                free(src);
                return 1;
            }
            memset(dep_arenas[i], 0, arena_sz);
            memset(dep_modules[i], 0, module_sz);
        }
        struct ast_PipelineDepCtx pctx;
        memset(&pctx, 0, sizeof(pctx));
        pipeline_fill_ctx_path_buffers(&pctx, entry_dir, lib_roots_arr, n_lib_roots);
        for (int i = 0; i < n_deps; i++) {
            pctx.dep_modules[i] = dep_modules[i];
            pctx.dep_arenas[i] = dep_arenas[i];
        }
        pctx.ndep = n_deps;
        pctx.use_asm_backend = use_asm_backend;
        pctx.target_arch = 0;
        if (target && (strstr(target, "aarch64") != NULL || strstr(target, "arm64") != NULL))
            pctx.target_arch = 1;
        if (target && strstr(target, "riscv64") != NULL)
            pctx.target_arch = 2;
        pctx.use_macho_o = 0;
        pctx.use_coff_o = 0;
#if defined(__APPLE__)
        if (emit_elf_o)
            pctx.use_macho_o = 1;
#endif
        if (emit_elf_o && target && strstr(target, "windows") != NULL)
            pctx.use_coff_o = 1;
        for (int i = 0; i < n_deps; i++) {
            struct ast_PipelineDepCtx one_ctx;
            memset(&one_ctx, 0, sizeof(one_ctx));
            pipeline_fill_ctx_path_buffers(&one_ctx, entry_dir, lib_roots_arr, n_lib_roots);
            one_ctx.dep_modules[0] = dep_modules[i];
            one_ctx.dep_arenas[0] = dep_arenas[i];
            one_ctx.ndep = 0;
            one_ctx.use_asm_backend = use_asm_backend;
            one_ctx.target_arch = pctx.target_arch;
            one_ctx.use_macho_o = pctx.use_macho_o;
            one_ctx.use_coff_o = pctx.use_coff_o;
            fprintf(stderr, "shuc: -su -E before pipeline dep %d (%s)\n", i, dep_paths[i]);
            fflush(stderr);
            int ec = pipeline_run_su_pipeline(dep_arenas[i], dep_modules[i], (const uint8_t *)dep_sources[i], dep_lens[i], (void *)&out_buf, (void *)&one_ctx);
            fprintf(stderr, "shuc: -su -E after pipeline dep %d\n", i);
            fflush(stderr);
            if (ec != 0 || out_buf.len == 0) {
                fprintf(stderr, "shuc: -su pipeline failed for import '%s'\n", dep_paths[i]);
                for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena);
                free(module);
                free(src);
                if (asm_out) fclose(asm_out);
                if (elf_ctx_ptr) free(elf_ctx_ptr);
                return 1;
            }
            if (!emit_elf_o)
                fwrite(out_buf.data, 1, (size_t)out_buf.len, asm_out ? asm_out : stdout);
        }
        typeck_ndep = n_deps;
        for (int i = 0; i < n_deps; i++) {
            typeck_dep_module_ptrs[i] = dep_modules[i];
            typeck_dep_arena_ptrs[i] = dep_arenas[i];
        }
        pipeline_set_dep_slots(dep_arenas, dep_modules);
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        fprintf(stderr, "shuc: -su -E before pipeline (main)\n");
        fflush(stderr);
        int ec = pipeline_run_su_pipeline(arena, module, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx);
        fprintf(stderr, "shuc: -su -E after pipeline (main)\n");
        fflush(stderr);
        if (ec == 0 && (out_buf.len > 0 || emit_elf_o)) {
            if (emit_elf_o && elf_ctx_ptr) {
                int32_t elf_ec = asm_asm_codegen_elf_o(module, arena, (void *)&pctx, (struct platform_elf_ElfCodegenCtx *)elf_ctx_ptr, &out_buf);
                if (elf_ec != 0 || out_buf.len <= 0) {
                    fprintf(stderr, "shuc: asm_codegen_elf_o failed\n");
                    if (asm_out) fclose(asm_out);
                    if (elf_ctx_ptr) free(elf_ctx_ptr);
                    for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
                    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
            }
            fwrite(out_buf.data, 1, (size_t)out_buf.len, asm_out ? asm_out : stdout);
            if (asm_out) fclose(asm_out);
            asm_out = NULL;
            if (elf_ctx_ptr) { free(elf_ctx_ptr); elf_ctx_ptr = NULL; }
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) {
                n_deps--;
                free(dep_sources[n_deps]);
                free(dep_paths[n_deps]);
            }
            /* -o <exe>（无 .o/.s 后缀）时：已写临时 .o，调 ld 生成可执行文件后删临时文件；传入 runtime_panic.o 以提供 shulang_panic_（不链 libc） */
            if (asm_want_exe && asm_tmp_o_path[0]) {
                const char *panic_o = get_runtime_panic_o_path(argv[0]);
                int ld_ok = invoke_ld(asm_tmp_o_path, out_path, target, pctx.use_macho_o, pctx.use_coff_o, panic_o);
                unlink(asm_tmp_o_path);
                if (ld_ok != 0) {
                    fprintf(stderr, "shuc: ld failed (asm -o exe)\n");
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
            }
        } else {
            /* ec != 0 或 ec == 0 但 out_buf.len == 0（且非 emit_elf_o） */
            if (asm_out) fclose(asm_out);
            asm_out = NULL;
            if (asm_want_exe && asm_tmp_o_path[0]) unlink(asm_tmp_o_path);
            if (elf_ctx_ptr) { free(elf_ctx_ptr); elf_ctx_ptr = NULL; }
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) {
                n_deps--;
                free(dep_sources[n_deps]);
                free(dep_paths[n_deps]);
            }
            if (ec != 0) {
                fprintf(stderr, "shuc: -su pipeline failed (parse_into / typeck_su_ast / codegen_su_ast)\n");
                /* 诊断：单独试 parse_into 以区分失败阶段 */
                {
                void *diag_arena = malloc(arena_sz);
                void *diag_module = malloc(module_sz);
                if (diag_arena && diag_module) {
                    memset(diag_arena, 0, arena_sz);
                    memset(diag_module, 0, module_sz);
                    struct parser_ParseIntoResult pr = parser_parse_into(diag_arena, diag_module, &src_slice);
                    if (pr.ok == 0) {
                        struct ast_PipelineDepCtx diag_ctx;
                        memset(&diag_ctx, 0, sizeof(diag_ctx));
                        int32_t tck = pipeline_typeck_after_parse_ok(diag_arena, diag_module, &src_slice, (void *)&diag_ctx);
                        fprintf(stderr, "shuc: (diagnostic) parse_into OK, typeck_after_parse=%d (0=ok -2=parse_fail -10=main_idx<0 -11=main_idx>=num_funcs -1=impl)\n", (int)tck);
                    } else {
                        int32_t fail_tok = parser_diag_fail_at_token_kind(&src_slice);
                        int32_t one_ok = pipeline_parse_one_function_ok(&src_slice);
                        fprintf(stderr, "shuc: (diagnostic) parse_into failed (len=%zu, diag_fail=%d, parse_one_func_ok=%d)\n",
                                (size_t)src_slice.length, (int)fail_tok, (int)one_ok);
                    }
                    free(diag_arena);
                    free(diag_module);
                }
            }
            }
        }
        free(arena);
        free(module);
        free(src);
        return (ec != 0) ? 1 : 0;
    }
#endif

    Lexer *lex = lexer_new(src);
    ASTModule *mod = NULL;
    int pr = parse(lex, &mod);
    lexer_free(lex);

    if (pr != 0 || !mod) {
        if (mod) ast_module_free(mod);
        free(src);
        fprintf(stderr, "shuc: parse failed for '%s' (pr=%d)\n", input_path, pr);
        return 1;
    }
    char entry_dir_buf[512];
    get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
    const char *entry_dir = entry_dir_buf;

    ASTModule *dep_mods[32];       /* 入口直接依赖，与 mod->import_paths 一一对应，供 typeck/codegen 入口 */
    ASTModule *all_dep_mods[MAX_ALL_DEPS];
    char *all_dep_paths[MAX_ALL_DEPS];
    int ndep = 0, n_all = 0;
    if (mod->num_imports > 0 && resolve_and_load_imports(mod, lib_roots_arr, n_lib_roots, entry_dir, ndefines > 0 ? defines : NULL, ndefines,
            dep_mods, &ndep, all_dep_mods, all_dep_paths, &n_all, 32) != 0) {
        ast_module_free(mod);
        free(src);
        return 1;
    }
/* 6.3：与 pipeline_su.o 同链时不再链 typeck_su/codegen_su，非 -su 路径用 C typeck/codegen 避免重复符号 */
#if defined(SHUC_USE_SU_TYPECK) && !defined(SHUC_USE_SU_PIPELINE)
    if (typeck_typeck_entry(mod, ndep > 0 ? dep_mods : NULL, ndep) != 0) {
#else
    /* 传入全部传递依赖供布局阶段解析跨模块类型；直接依赖仍为 dep_mods/ndep */
    if (typeck_module(mod, ndep > 0 ? dep_mods : NULL, ndep, n_all > 0 ? all_dep_mods : NULL, n_all) != 0) {
#endif
        while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
        ast_module_free(mod);
        free(src);
        return 1;
    }

    /* -E：生成 C 到 stdout 后退出。方案 A：有 import 时先按拓扑序输出全部依赖再输出入口，使单文件自洽可编译（为自举 pipeline_gen.c 铺路）。 */
    if (emit_c_only) {
        int ec = 0;
        char emitted_type_buf[128][CODEGEN_EMITTED_TYPE_NAME_MAX];
        int n_emitted = 0;
        const int max_emitted = (int)(sizeof(emitted_type_buf) / sizeof(emitted_type_buf[0]));

        if (n_all > 0) {
            /* 有依赖时与 -o 单文件一致：先统一输出 include 与 panic，再按拓扑序写各库，最后写入口，类型名去重避免重定义。
             * 阶段 3.1：-E-extern 时仅输出依赖类型 + 入口模块（extern 由 codegen 生成），不内联各库函数体。 */
            fprintf(stdout, "/* generated (single-file with deps) */\n");
            fprintf(stdout, "#include <stdint.h>\n");
            fprintf(stdout, "#include <stddef.h>\n");
            fprintf(stdout, "#include <stdlib.h>\n");
            fprintf(stdout, "#include <stdio.h>\n");
            fprintf(stdout, "#include <string.h>\n");
            fprintf(stdout, "static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
            fprintf(stdout, "static void shulang_panic_(int has_msg, int msg_val) {\n");
            fprintf(stdout, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
            fprintf(stdout, "  abort();\n");
            fprintf(stdout, "}\n");
            if (emit_extern_imports) {
                if (codegen_emit_dep_types_only(all_dep_mods, (const char **)all_dep_paths, n_all, stdout) != 0) {
                    ec = -1;
                }
            } else {
                for (int i = 0; i < n_all; i++) {
                    ASTModule *lib_deps[32];
                    const char *lib_dep_paths[32];
                    int n_lib = 0;
                    for (int j = 0; j < all_dep_mods[i]->num_imports && n_lib < 32; j++) {
                        int idx = find_loaded_index(all_dep_mods[i]->import_paths[j], all_dep_paths, n_all);
                        if (idx >= 0) {
                            lib_deps[n_lib] = all_dep_mods[idx];
                            lib_dep_paths[n_lib] = all_dep_paths[idx];
                            n_lib++;
                        }
                    }
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                    if (codegen_codegen_entry_library_module_to_c(all_dep_mods[i], all_dep_paths[i], lib_deps, lib_dep_paths, n_lib, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted) != 0) {
#else
                    if (codegen_library_module_to_c(all_dep_mods[i], all_dep_paths[i], lib_deps, lib_dep_paths, n_lib, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted) != 0) {
#endif
                        ec = -1;
                        break;
                    }
                }
            }
            if (ec == 0) {
                /* 阶段 3 -E-extern：入口一律按库模块输出（带 lib 前缀），避免 main 与 main.o 冲突、且仅 extern 依赖不内联。 */
                const char *lib_name = entry_lib_name_from_path(input_path);
                if (mod->num_funcs > 0) {
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                    ec = codegen_codegen_entry_library_module_to_c(mod, lib_name, dep_mods, (const char **)mod->import_paths, ndep, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#else
                    ec = codegen_library_module_to_c(mod, lib_name, dep_mods, (const char **)mod->import_paths, ndep, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#endif
                } else if (mod->main_func && mod->main_func->body) {
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                    ec = codegen_codegen_entry_module_to_c(mod, stdout, dep_mods, (const char **)mod->import_paths, ndep, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#else
                    ec = codegen_module_to_c(mod, stdout, dep_mods, (const char **)mod->import_paths, ndep, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#endif
                } else {
                    fprintf(stderr, "shuc: no main function (cannot emit C)\n");
                    ec = -1;
                }
            }
        } else {
            /* 无依赖：仅输出入口模块（保持原有行为） */
            if (mod->main_func && mod->main_func->body) {
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                ec = codegen_codegen_entry_module_to_c(mod, stdout, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#else
                ec = codegen_module_to_c(mod, stdout, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
            } else if (mod->num_funcs > 0) {
                const char *lib_name = entry_lib_name_from_path(input_path);
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                ec = codegen_codegen_entry_library_module_to_c(mod, lib_name, NULL, NULL, 0, stdout, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#else
                ec = codegen_library_module_to_c(mod, lib_name, NULL, NULL, 0, stdout, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
            } else {
                fprintf(stderr, "shuc: no main function (cannot emit C)\n");
                ec = -1;
            }
        }
        while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
        ast_module_free(mod);
        free(src);
        return ec != 0 ? 1 : 0;
    }

    /* 若指定 -o：需有 main，生成 C（含 import 的 .c）→ 调用 cc 链接；依赖使用已加载的 dep_mods（7.3 跨模块调用 + 传递依赖）；阶段 8.1 DCE 仅生成被引用函数与单态化 */
    if (out_path) {
        if (!mod->main_func || !mod->main_func->body) {
            fprintf(stderr, "shuc: no main function (cannot emit executable)\n");
            while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
            ast_module_free(mod);
            free(src);
            return 1;
        }
        /* 阶段 8.1 DCE：从 main 起算可达性，仅生成已引用函数与 mono 实例；未做 DCE 时传 NULL 避免误删库符号 */
        #define MAX_USED_FUNCS 256
        #define MAX_DCE_MODULES 33
        ASTFunc *used_funcs[MAX_USED_FUNCS];
        int n_used = 0;
        int used_mono[MAX_DCE_MODULES][64];
        const char *used_type_names[64];
        int n_used_types = 0;
        int dce_done = 0;
        if (n_all >= 0 && n_all < MAX_DCE_MODULES - 1) {
            codegen_compute_used(mod, all_dep_mods, n_all, used_funcs, &n_used, MAX_USED_FUNCS, used_mono);
            codegen_compute_used_types(mod, all_dep_mods, n_all, used_funcs, n_used, used_type_names, &n_used_types, 64);
            dce_done = 1;
        }
        struct dce_ctx dce = { used_funcs, n_used, used_mono, 1 + n_all, dce_done ? used_type_names : NULL, n_used_types, mod, all_dep_mods, n_all };
        void *dce_ctx_arg = dce_done ? (void *)&dce : NULL;

        const char *c_paths[MAX_C_FILES];
        int n_c = 0;
        char tmp_c[256];

        /* 入口模块 → 临时 .c（有依赖时同一文件内先写依赖再写入口） */
        char tmp[] = "/tmp/shuc_XXXXXX";
        int fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shuc: mkstemp");
            while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
            ast_module_free(mod);
            free(src);
            return 1;
        }
        FILE *cf = fdopen(fd, "w");
        if (!cf) {
            close(fd);
            unlink(tmp);
            while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
            ast_module_free(mod);
            free(src);
            return 1;
        }
        /* 有依赖时单文件输出：先按拓扑序写依赖再写入口，并传已输出类型名去重，避免 incomplete type 与重定义（见自举实现分析 7.3） */
        char emitted_type_buf[128][CODEGEN_EMITTED_TYPE_NAME_MAX];
        int n_emitted = 0;
        const int max_emitted = (int)(sizeof(emitted_type_buf) / sizeof(emitted_type_buf[0]));

        if (n_all > 0) {
            /* 单文件时在写任何库前统一输出 include 与 panic，避免首库无类型导致 n_emitted 仍为 0、次库再次输出 panic 而重定义（见 run-stdlib-import） */
            fprintf(cf, "/* generated (single-file with deps) */\n");
            fprintf(cf, "#include <stdint.h>\n");
            fprintf(cf, "#include <stddef.h>\n");
            fprintf(cf, "#include <stdlib.h>\n");
            fprintf(cf, "#include <stdio.h>\n");
            fprintf(cf, "#include <string.h>\n"); /* memcpy for array copy (bootstrap parser.su) */
            fprintf(cf, "static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
            fprintf(cf, "static void shulang_panic_(int has_msg, int msg_val) {\n");
            fprintf(cf, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
            fprintf(cf, "  abort();\n");
            fprintf(cf, "}\n");
            for (int i = 0; i < n_all; i++) {
                ASTModule *lib_deps[32];
                const char *lib_dep_paths[32];
                int n_lib = 0;
                for (int j = 0; j < all_dep_mods[i]->num_imports && n_lib < 32; j++) {
                    int idx = find_loaded_index(all_dep_mods[i]->import_paths[j], all_dep_paths, n_all);
                    if (idx >= 0) {
                        lib_deps[n_lib] = all_dep_mods[idx];
                        lib_dep_paths[n_lib] = all_dep_paths[idx];
                        n_lib++;
                    }
                }
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
                if (codegen_codegen_entry_library_module_to_c(all_dep_mods[i], all_dep_paths[i], lib_deps, lib_dep_paths, n_lib, cf, dce_is_func_used, dce_is_mono_used, dce_is_type_used, dce_ctx_arg, emitted_type_buf, &n_emitted, max_emitted) != 0) {
#else
                if (codegen_library_module_to_c(all_dep_mods[i], all_dep_paths[i], lib_deps, lib_dep_paths, n_lib, cf, dce_is_func_used, dce_is_mono_used, dce_is_type_used, dce_ctx_arg, emitted_type_buf, &n_emitted, max_emitted) != 0) {
#endif
                    fclose(cf);
                    unlink(tmp);
                    while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
                    ast_module_free(mod);
                    free(src);
                    return 1;
                }
            }
        }
#if defined(SHUC_USE_SU_CODEGEN) && !defined(SHUC_USE_SU_PIPELINE)
        if (codegen_codegen_entry_module_to_c(mod, cf, dep_mods, (const char **)mod->import_paths, ndep, dce_is_func_used, dce_is_mono_used, dce_is_type_used, dce_ctx_arg, n_all > 0 ? emitted_type_buf : NULL, n_all > 0 ? &n_emitted : NULL, n_all > 0 ? max_emitted : 0) != 0) {
#else
        if (codegen_module_to_c(mod, cf, dep_mods, (const char **)mod->import_paths, ndep, dce_is_func_used, dce_is_mono_used, dce_is_type_used, dce_ctx_arg, n_all > 0 ? emitted_type_buf : NULL, n_all > 0 ? &n_emitted : NULL, n_all > 0 ? max_emitted : 0) != 0) {
#endif
            fclose(cf);
            unlink(tmp);
            while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
            ast_module_free(mod);
            free(src);
            return 1;
        }
        fclose(cf);
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            perror("shuc: rename");
            unlink(tmp);
            while (ndep--) ast_module_free(dep_mods[ndep]);
            ast_module_free(mod);
            free(src);
            return 1;
        }
        if (getenv("SHUC_DEBUG_C")) {
            FILE *dc = fopen(tmp_c, "r");
            if (dc) {
                FILE *out = fopen("/tmp/shuc_debug.c", "w");
                if (out) {
                    int ch;
                    while ((ch = getc(dc)) != EOF) putc(ch, out);
                    fclose(out);
                }
                fclose(dc);
            }
        }
        c_paths[n_c++] = tmp_c;

        int cc_ok = invoke_cc(c_paths, n_c, out_path, target, opt_level);
        unlink(tmp_c);
        while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
        ast_module_free(mod);
        free(src);
        return cc_ok == 0 ? 0 : 1;
    }

    /* 无 -o：保留原有行为：打印 Token，再解析并打印 parse/typeck OK（供测试） */
    /* 先保存 main 名称与字面量，避免后续第二次 lexer 可能覆盖堆后 mod 指针失效 */
    const char *main_name = (mod->main_func && mod->main_func->name) ? mod->main_func->name : "?";
    int main_final_lit = -1;
    if (mod->main_func && mod->main_func->body && mod->main_func->body->final_expr
        && mod->main_func->body->final_expr->kind == AST_EXPR_LIT)
        main_final_lit = mod->main_func->body->final_expr->value.int_val;

    Lexer *lex2 = lexer_new(src);
    Token tok;
    for (;;) {
        lexer_next(lex2, &tok);
        if (tok.kind == TOKEN_EOF) {
            printf("%s\n", token_kind_str(tok.kind));
            break;
        }
        printf("%s", token_kind_str(tok.kind));
        if (tok.kind == TOKEN_INT)
            printf(" %d", tok.value.int_val);
        else if (tok.kind == TOKEN_FLOAT)
            printf(" %g", tok.value.float_val);
        else if ((tok.kind == TOKEN_IDENT || tok.kind == TOKEN_I32 || tok.kind == TOKEN_BOOL
                  || tok.kind == TOKEN_U8 || tok.kind == TOKEN_U32 || tok.kind == TOKEN_U64
                  || tok.kind == TOKEN_I64 || tok.kind == TOKEN_USIZE || tok.kind == TOKEN_ISIZE)
                 && tok.value.ident && tok.ident_len > 0)
            printf(" %.*s", tok.ident_len, tok.value.ident);
        printf(" @%d:%d\n", tok.line, tok.col);
    }
    lexer_free(lex2);

    if (mod->main_func && mod->main_func->body) {
        if (main_final_lit >= 0)
            printf("parse OK: %s(): i32 { %d }\n", main_name, main_final_lit);
        else
            printf("parse OK: %s(): i32 { expr }\n", main_name);
    } else
        printf("parse OK (library module)\n");
    printf("typeck OK\n");
    while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
    ast_module_free(mod);
    free(src);
    return 0;
#endif /* !SHUC_USE_SU_FRONTEND */
}
#undef RUN_CC_FUNC
#endif /* !SHUC_USE_SU_DRIVER */

/**
 * 阶段 3 全 .su 前端：当 SHUC_USE_SU_FRONTEND 且 SHUC_USE_SU_PIPELINE 时，用 pipeline 生成 C 并调用 cc，不依赖 C 的 typeck/codegen。
 * 否则直接转调 run_compiler_c。完全自举时 run_compiler_su_path 由 main.su 提供，C 不定义以免重复符号。
 */
#if !defined(SHUC_USE_SU_DRIVER)
int run_compiler_su_path(int argc, char **argv) {
#if !defined(SHUC_USE_SU_FRONTEND) || !defined(SHUC_USE_SU_PIPELINE)
    return run_compiler_c(argc, argv);
#else
#define SU_PATH_MAX_LIB_ROOTS 16
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_roots_arr[SU_PATH_MAX_LIB_ROOTS];
    int n_lib_roots = 0;
    const char *opt_level = "2";
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) return run_compiler_c(argc, argv);
            out_path = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) return run_compiler_c(argc, argv);
            if (n_lib_roots < SU_PATH_MAX_LIB_ROOTS) lib_roots_arr[n_lib_roots++] = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-O") == 0) {
            if (i + 1 >= argc) return run_compiler_c(argc, argv);
            opt_level = argv[++i];
            continue;
        }
        if (!input_path) input_path = argv[i];
    }
    if (n_lib_roots == 0) {
        lib_roots_arr[0] = getenv("SHULANG_LIB");
        if (!lib_roots_arr[0]) lib_roots_arr[0] = ".";
        n_lib_roots = 1;
    }
    if (!input_path)
        return run_compiler_c(argc, argv);
    /* 无 -o 时：用 pipeline 生成 C 到 stdout，与 run-lexer 等测试一致，不调用 run_compiler_c。 */
    int emit_to_stdout = (out_path == NULL);

    size_t raw_src_len = 0;
    char *raw_src = read_file(input_path, &raw_src_len);
    if (!raw_src) {
        fprintf(stderr, "Error: cannot read file '%s'\n", input_path);
        return 1;
    }
    size_t src_len = 0;
    char *src = preprocess(raw_src, raw_src_len, NULL, 0, &src_len);
    free(raw_src);
    if (!src) {
        fprintf(stderr, "shuc: preprocess failed for '%s'\n", input_path);
        return 1;
    }
    size_t arena_sz = pipeline_sizeof_arena();
    size_t module_sz = pipeline_sizeof_module();
    void *arena = malloc(arena_sz);
    void *module = malloc(module_sz);
    if (!arena || !module) {
        free(arena);
        free(module);
        free(src);
        return 1;
    }
    memset(arena, 0, arena_sz);
    memset(module, 0, module_sz);
    struct shulang_slice_uint8_t src_slice = { (uint8_t *)src, src_len };
    parser_parse_into_init(arena, module);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
    if (pr.ok != 0) {
        fprintf(stderr, "shuc: parse failed for '%s'\n", input_path);
        free(arena);
        free(module);
        free(src);
        return 1;
    }
    parser_parse_into_set_main_index(module, pr.main_idx);
    int32_t n_imports = parser_get_module_num_imports(module);
    char entry_dir_buf[512];
    get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
    if (n_imports > 0)
        pipeline_set_entry_dir(entry_dir_buf);

    char *dep_sources[MAX_ALL_DEPS];
    size_t dep_lens[MAX_ALL_DEPS];
    char *dep_paths[MAX_ALL_DEPS];
    int n_deps = 0;
    if (n_imports > 0 && n_imports <= 32) {
        for (int j = 0; j < n_imports && n_deps < MAX_ALL_DEPS; j++) {
            uint8_t path_buf[64];
            parser_get_module_import_path(module, j, path_buf);
            char path_c[65];
            size_t k = 0;
            while (k < sizeof(path_buf) && path_buf[k]) { path_c[k] = (char)path_buf[k]; k++; }
            path_c[k] = '\0';
            if (find_loaded_index(path_c, dep_paths, n_deps) >= 0) continue;
            char resolved[512];
            resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir_buf, path_c, resolved, sizeof(resolved));
            size_t raw_len = 0;
            char *raw = read_file(resolved, &raw_len);
            if (!raw) {
                fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", path_c, resolved);
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena); free(module); free(src);
                return 1;
            }
            size_t prep_len = 0;
            char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
            free(raw);
            if (!prep) {
                fprintf(stderr, "shuc: preprocess failed for import '%s'\n", path_c);
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena); free(module); free(src);
                return 1;
            }
            dep_sources[n_deps] = prep;
            dep_lens[n_deps] = prep_len;
            dep_paths[n_deps] = strdup(path_c);
            if (!dep_paths[n_deps]) {
                free(prep);
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena); free(module); free(src);
                return 1;
            }
            n_deps++;
        }
    }
    typeck_ndep = 0;
    char tmp[] = "/tmp/shuc_su_XXXXXX.c";
    int fd = -1;
    FILE *cf;
    if (emit_to_stdout) {
        cf = stdout;
    } else {
        fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shuc: mkstemp");
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
        cf = fdopen(fd, "w");
        if (!cf) {
            close(fd);
            unlink(tmp);
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
    }
    struct codegen_CodegenOutBuf out_buf;
    memset(&out_buf, 0, sizeof(out_buf));
    void *dep_arenas[32];
    void *dep_modules[32];
    for (int j = 0; j < n_deps; j++) {
        dep_arenas[j] = malloc(arena_sz);
        dep_modules[j] = malloc(module_sz);
        if (!dep_arenas[j] || !dep_modules[j]) {
            fprintf(stderr, "shuc: -su path: dep alloc failed\n");
            while (j > 0) { j--; free(dep_arenas[j]); free(dep_modules[j]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
        memset(dep_arenas[j], 0, arena_sz);
        memset(dep_modules[j], 0, module_sz);
    }
    struct ast_PipelineDepCtx pctx;
    memset(&pctx, 0, sizeof(pctx));
    pipeline_fill_ctx_path_buffers(&pctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
    for (int j = 0; j < n_deps; j++) {
        pctx.dep_modules[j] = dep_modules[j];
        pctx.dep_arenas[j] = dep_arenas[j];
    }
    pctx.ndep = n_deps;
    for (int j = 0; j < n_deps; j++) {
        struct ast_PipelineDepCtx one_ctx;
        memset(&one_ctx, 0, sizeof(one_ctx));
        pipeline_fill_ctx_path_buffers(&one_ctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
        one_ctx.dep_modules[0] = dep_modules[j];
        one_ctx.dep_arenas[0] = dep_arenas[j];
        one_ctx.ndep = 0;
        int ec = pipeline_run_su_pipeline(dep_arenas[j], dep_modules[j], (const uint8_t *)dep_sources[j], dep_lens[j], (void *)&out_buf, (void *)&one_ctx);
        if (ec != 0 || out_buf.len == 0) {
            fprintf(stderr, "shuc: pipeline failed for import '%s'\n", dep_paths[j]);
            for (int k = 0; k < n_deps; k++) { free(dep_arenas[k]); free(dep_modules[k]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
        if (fwrite(out_buf.data, 1, (size_t)out_buf.len, cf) != (size_t)out_buf.len) {
            for (int k = 0; k < n_deps; k++) { free(dep_arenas[k]); free(dep_modules[k]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
    }
    typeck_ndep = n_deps;
    for (int j = 0; j < n_deps; j++) {
        typeck_dep_module_ptrs[j] = dep_modules[j];
        typeck_dep_arena_ptrs[j] = dep_arenas[j];
    }
    pipeline_set_dep_slots(dep_arenas, dep_modules);
    memset(arena, 0, arena_sz);
    memset(module, 0, module_sz);
    int ec = pipeline_run_su_pipeline(arena, module, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx);
    for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
    free(arena);
    free(module);
    free(src);
    if (ec != 0 || out_buf.len == 0) {
        fprintf(stderr, "shuc: pipeline failed for '%s'\n", input_path);
        if (!emit_to_stdout) { fclose(cf); unlink(tmp); }
        return 1;
    }
    if (fwrite(out_buf.data, 1, (size_t)out_buf.len, cf) != (size_t)out_buf.len) {
        if (!emit_to_stdout) { fclose(cf); unlink(tmp); }
        return 1;
    }
    if (!emit_to_stdout) {
        if (fclose(cf) != 0) {
            unlink(tmp);
            return 1;
        }
        {
            const char *c_paths[1] = { tmp };
            int cc_ret = invoke_cc(c_paths, 1, out_path, NULL, opt_level);
            unlink(tmp);
            return cc_ret == 0 ? 0 : 1;
        }
    }
    return 0;
#undef SU_PATH_MAX_LIB_ROOTS
#endif
}
#endif /* !defined(SHUC_USE_SU_DRIVER)：run_compiler_su_path 仅在不使用 .su driver 时由 C 提供 */

#ifdef SHUC_USE_SU_DRIVER
/* 阶段 6.2：main.su 内实现 argv 解析与 -su -E 执行逻辑；C 仅提供极薄原语 driver_get_argv_i。 */
/* 保留旧符号供未迁完时链接；main.su 自实现后不再调用。 */
static const char *driver_su_emit_c_path;
#define SU_EMIT_MAX_LIB_ROOTS 16
static const char *driver_su_emit_lib_roots[SU_EMIT_MAX_LIB_ROOTS];
static int driver_su_emit_n_lib_roots;

/** 6.2 极薄原语：将 argv[i] 复制到 buf，最多 max-1 字节并加 NUL，返回长度（不含 NUL）；i 越界或失败返回 -1。供 main.su 自实现 argv 解析。 */
int driver_get_argv_i(int argc, char **argv, int i, char *buf, int max) {
    if (!argv || !buf || max <= 0 || i < 0 || i >= argc || !argv[i]) return -1;
    size_t n = (size_t)max - 1;
    size_t j = 0;
    while (argv[i][j] && j < n) {
        buf[j] = argv[i][j];
        j++;
    }
    buf[j] = '\0';
    return (int)j;
}

/** 扫描 argv：若存在 -su -E <path> 则记下 path 及此前出现的 -L path，返回 1，否则返回 0。保留供未迁完时链接。 */
int driver_argv_parse_su_emit_c(int argc, char **argv) {
    driver_su_emit_c_path = NULL;
    driver_su_emit_n_lib_roots = 0;
    if (argc < 4 || !argv) return 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i] && strcmp(argv[i], "-L") == 0 && i + 1 < argc && driver_su_emit_n_lib_roots < SU_EMIT_MAX_LIB_ROOTS) {
            driver_su_emit_lib_roots[driver_su_emit_n_lib_roots++] = argv[i + 1];
            i++;
            continue;
        }
        if (argv[i] && strcmp(argv[i], "-su") == 0 && i + 2 < argc && argv[i + 1] && strcmp(argv[i + 1], "-E") == 0) {
            driver_su_emit_c_path = argv[i + 2];
            return 1;
        }
    }
    return 0;
}

/** 执行刚解析的 -su -E（读文件、.su pipeline、写 stdout）；成功 0，失败 1。无 SHUC_USE_SU_PIPELINE 时返回 1。 */
int driver_run_su_emit_c(void) {
    const char *input_path = driver_su_emit_c_path;
    driver_su_emit_c_path = NULL;
    if (!input_path) return 1;
#ifdef SHUC_USE_SU_PIPELINE
    {
        size_t raw_src_len = 0;
        char *raw_src = read_file(input_path, &raw_src_len);
        if (!raw_src) {
            fprintf(stderr, "Error: cannot read file '%s'\n", input_path);
            return 1;
        }
        size_t src_len = 0;
        char *src = preprocess(raw_src, raw_src_len, NULL, 0, &src_len);
        free(raw_src);
        if (!src) {
            fprintf(stderr, "shuc: preprocess failed for '%s'\n", input_path);
            return 1;
        }
        size_t arena_sz = pipeline_sizeof_arena();
        size_t module_sz = pipeline_sizeof_module();
        void *arena = malloc(arena_sz);
        void *module = malloc(module_sz);
        if (!arena || !module) {
            fprintf(stderr, "shuc: -su pipeline: malloc failed\n");
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        struct shulang_slice_uint8_t src_slice = { (uint8_t *)src, src_len };
        parser_parse_into_init(arena, module);
        struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
        if (pr.ok != 0) {
            fprintf(stderr, "shuc: -su pipeline failed (parse_into)\n");
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        parser_parse_into_set_main_index(module, pr.main_idx);
        int32_t n_imports = parser_get_module_num_imports(module);
        char entry_dir_buf[512];
        get_entry_dir(input_path, entry_dir_buf, sizeof(entry_dir_buf));
        const char *entry_dir = entry_dir_buf;
        /* 供 pipeline 内 resolve/read 单段 import 用；仅在有 import 时设置，避免单文件时影响 */
        if (n_imports > 0)
            pipeline_set_entry_dir(entry_dir_buf);
        /* 阶段 2.1：使用解析到的 -L 库根；无 -L 时退化为当前目录 */
        const char *lib_roots_arr[SU_EMIT_MAX_LIB_ROOTS];
        int n_lib_roots = driver_su_emit_n_lib_roots;
        if (n_lib_roots == 0) {
            lib_roots_arr[0] = ".";
            n_lib_roots = 1;
        } else {
            for (int k = 0; k < n_lib_roots; k++) lib_roots_arr[k] = driver_su_emit_lib_roots[k];
        }
        char *dep_sources[MAX_ALL_DEPS];
        size_t dep_lens[MAX_ALL_DEPS];
        char *dep_paths[MAX_ALL_DEPS];
        int n_deps = 0;
        if (n_imports > 0 && n_imports <= 32) {
            for (int i = 0; i < n_imports && n_deps < MAX_ALL_DEPS; i++) {
                uint8_t path_buf[64];
                parser_get_module_import_path(module, i, path_buf);
                char path_c[65];
                size_t k = 0;
                while (k < sizeof(path_buf) && path_buf[k]) { path_c[k] = (char)path_buf[k]; k++; }
                path_c[k] = '\0';
                if (find_loaded_index(path_c, dep_paths, n_deps) >= 0) continue;
                char resolved[512];
                resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir, path_c, resolved, sizeof(resolved));
                size_t raw_len = 0;
                char *raw = read_file(resolved, &raw_len);
                if (!raw) {
                    fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", path_c, resolved);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
                size_t prep_len = 0;
                char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
                free(raw);
                if (!prep) {
                    fprintf(stderr, "shuc: preprocess failed for import '%s'\n", path_c);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
                dep_sources[n_deps] = prep;
                dep_lens[n_deps] = prep_len;
                dep_paths[n_deps] = strdup(path_c);
                if (!dep_paths[n_deps]) {
                    free(prep);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
                n_deps++;
            }
        }
        typeck_ndep = 0;
        struct codegen_CodegenOutBuf out_buf;
        memset(&out_buf, 0, sizeof(out_buf));
        void *dep_arenas[32];
        void *dep_modules[32];
        for (int i = 0; i < n_deps; i++) {
            dep_arenas[i] = malloc(arena_sz);
            dep_modules[i] = malloc(module_sz);
            if (!dep_arenas[i] || !dep_modules[i]) {
                fprintf(stderr, "shuc: -su pipeline: dep alloc failed\n");
                while (i > 0) { i--; free(dep_arenas[i]); free(dep_modules[i]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena); free(module); free(src);
                return 1;
            }
            memset(dep_arenas[i], 0, arena_sz);
            memset(dep_modules[i], 0, module_sz);
        }
        struct ast_PipelineDepCtx pctx_e;
        memset(&pctx_e, 0, sizeof(pctx_e));
        pipeline_fill_ctx_path_buffers(&pctx_e, entry_dir_buf, lib_roots_arr, n_lib_roots);
        for (int i = 0; i < n_deps; i++) {
            pctx_e.dep_modules[i] = dep_modules[i];
            pctx_e.dep_arenas[i] = dep_arenas[i];
        }
        pctx_e.ndep = n_deps;
        for (int i = 0; i < n_deps; i++) {
            struct ast_PipelineDepCtx one_ctx;
            memset(&one_ctx, 0, sizeof(one_ctx));
            pipeline_fill_ctx_path_buffers(&one_ctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
            one_ctx.dep_modules[0] = dep_modules[i];
            one_ctx.dep_arenas[0] = dep_arenas[i];
            one_ctx.ndep = 0;
            fprintf(stderr, "shuc: -su -E before pipeline dep %d (%s)\n", i, dep_paths[i]);
            fflush(stderr);
            int ec = pipeline_run_su_pipeline(dep_arenas[i], dep_modules[i], (const uint8_t *)dep_sources[i], dep_lens[i], (void *)&out_buf, (void *)&one_ctx);
            fprintf(stderr, "shuc: -su -E after pipeline dep %d\n", i);
            fflush(stderr);
            if (ec != 0 || out_buf.len == 0) {
                fprintf(stderr, "shuc: -su pipeline failed for import '%s'\n", dep_paths[i]);
                for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
                while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                free(arena); free(module); free(src);
                return 1;
            }
            fwrite(out_buf.data, 1, (size_t)out_buf.len, stdout);
        }
        typeck_ndep = n_deps;
        for (int i = 0; i < n_deps; i++) {
            typeck_dep_module_ptrs[i] = dep_modules[i];
            typeck_dep_arena_ptrs[i] = dep_arenas[i];
        }
        pipeline_set_dep_slots(dep_arenas, dep_modules);
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        fprintf(stderr, "shuc: -su -E before pipeline (main)\n");
        fflush(stderr);
        int ec = pipeline_run_su_pipeline(arena, module, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx_e);
        fprintf(stderr, "shuc: -su -E after pipeline (main)\n");
        fflush(stderr);
        if (ec == 0 && out_buf.len > 0) {
            fwrite(out_buf.data, 1, (size_t)out_buf.len, stdout);
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
        } else {
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            if (ec != 0) fprintf(stderr, "shuc: -su pipeline failed\n");
        }
        free(arena);
        free(module);
        free(src);
        return (ec != 0) ? 1 : 0;
    }
#else
    (void)input_path;
    return 1;
#endif
}
#endif

#ifndef SHUC_USE_SU_DRIVER
/** 6.3：无 .su 入口时由 runtime 提供 main_entry 桩，仅转调 run_compiler_c；链接 main_su.o 时由 main.su 的 main_entry 覆盖。
 * Cygwin/MinGW 上 weak 符号可能不被链接器解析，故仅在非 Windows 环境使用 weak。 */
#if !defined(__CYGWIN__) && !defined(__MINGW32__) && !defined(_WIN32)
__attribute__((weak))
#endif
int main_entry(int argc, char **argv) {
    return run_compiler_c(argc, argv);
}
#endif
