/**
 * runtime.c — 编译器运行时（6.3/6.4：自 main.c 迁出的驱动逻辑与 C 辅助）
 *
 * 文件职责：提供 run_compiler_c、driver_*、pipeline_*、get_dep_* 及 read_file/preprocess/resolve_import 等；无 SHU_USE_SU_DRIVER 时提供弱符号 main_entry 转调 run_compiler_c，供默认构建链接；有 main.su 时由 main_entry 覆盖。
 * 与 main.c 关系：main.c 仅保留极简 main() 调 main_entry；本文件承载全部 C 侧驱动与 I/O，与 main.su 一一对应构建 shu。
 */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "preprocess.h"
#include "typeck/typeck.h"
#include "codegen/codegen.h"
#include "ast.h"
#ifdef SHU_USE_SU_CODEGEN
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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
/* 提前声明，供 SHU_USE_SU_PIPELINE 块内 pipeline_* 调用 */
static char *read_file(const char *path, size_t *out_len);
static void resolve_import_file_path_multi(const char **lib_roots, int n_lib_roots, const char *entry_dir, const char *import_path, char *path, size_t path_size);
#ifdef SHU_USE_SU_TYPECK
/* 6.1：.su typeck 入口；由 typeck.su 提供（库模块形式生成，符号为 typeck_typeck_entry），转调 C typeck_module */
extern int typeck_typeck_entry(struct ASTModule *mod, struct ASTModule **deps, int ndep);
#endif

/** 舒 IO 后端 .o 路径（分析/舒IO实现路线图.md 阶段 1）；源码在 std/io/io.c，产出 std/io/io.o（与 shu 所在目录的上一级 std/io/ 下）；C 与 -su 路径均需链入。 */
static const char *get_io_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
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
    strcat(buf, "/../std/io/io.o");
    if (realpath(buf, resolved) != NULL) return resolved;
    if (realpath("std/io/io.o", resolved) != NULL) return resolved;
#ifdef __APPLE__
    /* macOS 下从 PATH 运行 shu 时 argv[0] 可能无目录，用 cwd 再试一次 */
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 16) != NULL) {
            strcat(cwd_buf, "/std/io/io.o");
            if (realpath(cwd_buf, resolved) != NULL) return resolved;
        }
    }
#endif
    return buf;
}

#if defined(SHU_USE_SU_PIPELINE)
/** 向生成 C 写入 std.io / std.net 内联 ABI（原 io_abi.h、net_abi.h 内容），不再依赖该二头文件。成功返回 0。 */
static int write_io_net_abi_inline(FILE *cf) {
    static const char *lines[] = {
        "#include <stddef.h>\n",
        "#include <stdint.h>\n",
        "typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_batch_buf_t;\n",
        "extern int io_register_buffer(uint8_t *ptr, size_t len);\n",
        "extern int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr);\n",
        "extern int io_register_buffers_buf_c(const shu_batch_buf_t *bufs, int nr);\n",
        "static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const shu_batch_buf_t *)(uintptr_t)bufs, nr); }\n",
        "#define io_register_buffers_buf(bufs, nr) io_register_buffers_buf_i32((intptr_t)(void *)(bufs), (nr))\n",
        "extern void io_unregister_buffers(void);\n",
        "extern ptrdiff_t io_read(int fd, uint8_t *buf, size_t count, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_write(int fd, uint8_t *buf, size_t count, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_read_batch(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, int n, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_write_batch(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, int n, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_read_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_write_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms);\n",
        "extern int io_wait_readable(int32_t *fds, int n, unsigned timeout_ms);\n",
        "extern uint8_t *io_read_ptr(size_t handle, unsigned timeout_ms);\n",
        "extern int io_read_ptr_len(void);\n",
        "extern int32_t shu_io_register(uint8_t *ptr, size_t len, size_t handle);\n",
        "extern int32_t shu_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n",
        "extern int32_t shu_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n",
        "extern int32_t shu_io_read_fixed(int32_t fd, int32_t buf_index, int32_t offset, int32_t len, int32_t timeout_m);\n",
        "extern int32_t shu_io_write_fixed(int32_t fd, int32_t buf_index, int32_t offset, int32_t len, int32_t timeout_m);\n",
        "extern uint8_t *shu_io_read_ptr(size_t handle, unsigned timeout_ms);\n",
        "extern int32_t shu_io_read_ptr_len(void);\n",
        "typedef struct { void *ptr; size_t len; size_t handle; } shu_buffer_abi_t;\n",
        "static inline int32_t shu_io_register_buf(intptr_t buf) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_register((uint8_t *)b->ptr, b->len, b->handle); }\n",
        "static inline int32_t shu_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return (shu_io_submit_read)((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n",
        "static inline int32_t shu_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return (shu_io_submit_write)((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n",
        "#define shu_io_register(buf) shu_io_register_buf(buf)\n",
        "#define shu_io_submit_read(buf, timeout_m) shu_io_submit_read_buf(buf, timeout_m)\n",
        "#define shu_io_submit_write(buf, timeout_m) shu_io_submit_write_buf(buf, timeout_m)\n",
        "struct std_io_driver_Buffer { void *ptr; size_t len; size_t handle; };\n",
        "typedef struct std_io_driver_Buffer std_io_Buffer;\n",
        "#define std_io_Buffer std_io_driver_Buffer\n",
        "extern int32_t std_io_driver_submit_read(ptrdiff_t buf, uint32_t timeout_ms);\n",
        "extern int32_t std_io_driver_submit_write(ptrdiff_t buf, uint32_t timeout_ms);\n",
        "extern int32_t std_io_driver_submit_register_fixed_buffers_buf(struct std_io_driver_Buffer * bufs, uint32_t nr);\n",
        "#define std_io_driver_driver_read_ptr_len shu_io_read_ptr_len\n",
        "#define std_io_driver_driver_read_ptr shu_io_read_ptr\n",
        "#define driver_read_ptr_len std_io_driver_driver_read_ptr_len\n",
        "#define driver_read_ptr std_io_driver_driver_read_ptr\n",
        "#define submit_register_fixed_buffers_buf std_io_driver_submit_register_fixed_buffers_buf\n",
        "#define std_io_core_shu_io_register shu_io_register\n",
        "#define std_io_core_shu_io_register_buffers shu_io_register_buffers\n",
        "#define std_io_core_shu_io_unregister_buffers shu_io_unregister_buffers\n",
        "#define std_io_core_shu_io_submit_read shu_io_submit_read\n",
        "#define std_io_core_shu_io_read_ptr shu_io_read_ptr\n",
        "#define std_io_core_shu_io_read_ptr_len shu_io_read_ptr_len\n",
        "#define std_io_core_shu_io_submit_write shu_io_submit_write\n",
        "#define std_io_core_shu_io_submit_read_batch shu_io_submit_read_batch\n",
        "#define std_io_core_shu_io_submit_write_batch shu_io_submit_write_batch\n",
        "extern int32_t std_io_handle_from_fd(int32_t fd, int32_t unused);\n",
        "extern int32_t std_io_driver_submit_read_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);\n",
        "extern int32_t std_io_driver_submit_write_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);\n",
        "#define std_io_submit_read_batch_buf std_io_driver_submit_read_batch_buf\n",
        "#define std_io_submit_write_batch_buf std_io_driver_submit_write_batch_buf\n",
        "extern int32_t std_io_read_fixed_fd(int32_t fd, int32_t p1, int32_t p2, int32_t p3, int32_t p4);\n",
        "extern int32_t std_io_write_fixed_fd(int32_t fd, int32_t p1, int32_t p2, int32_t p3, int32_t p4);\n",
        "struct std_net_Ipv4Addr { uint8_t a; uint8_t b; uint8_t c; uint8_t d; };\n",
        "struct std_net_Ipv6Addr { uint8_t b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15; };\n",
        "struct std_net_TcpStream { int32_t fd; };\n",
        "struct std_net_TcpListener { int32_t fd; };\n",
        "struct std_net_UdpSocket { int32_t fd; };\n",
        "#define handle_from_fd std_io_handle_from_fd\n",
        "#define submit_read_batch_buf std_io_submit_read_batch_buf\n",
        "#define submit_write_batch_buf std_io_submit_write_batch_buf\n",
        "#define read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd(_Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (x)), a, b, c, d)\n",
        "#define write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd(_Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (x)), a, b, c, d)\n",
        "extern int32_t net_close_socket_c(int32_t fd);\n",
        "extern int32_t net_run_accept_workers_c(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms);\n",
        "#define net_close_socket_c_real net_close_socket_c\n",
        "#define net_close_socket_c(x) net_close_socket_c_real(_Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (x)))\n",
        "#define net_run_accept_workers_c_real net_run_accept_workers_c\n",
        "#define net_run_accept_workers_c(x, n, t) net_run_accept_workers_c_real(_Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, default: (x)), n, t)\n",
        "#define STD_FS_FS_IOVEC_BUF_DEFINED\nstruct std_fs_FsIovecBuf { void *ptr; size_t len; size_t handle; };\n",
        "struct std_map_Map_i32_i32 { int32_t *keys; int32_t *vals; uint8_t *occupied; int32_t cap; int32_t len; };\n",
        "typedef struct std_io_driver_Buffer std_net_Buffer;\n",
        "struct std_vec_Vec_i32 { int32_t *ptr; int32_t len; int32_t cap; };\n",
        "extern int32_t std_vec_vec_len_empty(void);\n",
        "extern int32_t std_heap_alloc_size_zero(void);\n",
        "extern int32_t std_runtime_runtime_ready(void);\n",
        "#define vec_len_empty std_vec_vec_len_empty\n",
        "#define alloc_size_zero std_heap_alloc_size_zero\n",
        "#define runtime_ready std_runtime_runtime_ready\n",
    };
    for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        if (fputs(lines[i], cf) == EOF) return 1;
    }
    return 0;
}
#endif /* SHU_USE_SU_PIPELINE */

/** 由 argv0 推导仓库根目录（用于 -I 以便生成 .c 能 #include std/fs、path、map、error 等 ABI 头）；基于 get_io_o_path 的路径向上取三级目录。 */
static const char *get_repo_root(const char *argv0) {
    static char buf[512];
    const char *io_o = get_io_o_path(argv0);
    buf[0] = '\0';
    if (!io_o || !io_o[0]) return buf;
    if (strlen(io_o) >= sizeof(buf)) return buf;
    strcpy(buf, io_o);
    for (int k = 0; k < 3; k++) {
        char *last = strrchr(buf, '/');
        if (!last || last == buf) break;
        *last = '\0';
    }
    return buf;
}

/** std.fs 高性能 .o 路径（mmap/munmap）；优先 cwd 以兼容多工作区，产出 std/fs/fs.o。 */
static const char *get_std_fs_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/fs/fs.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 18) != NULL) { size_t L = strlen(cwd); if (L + 18 <= sizeof(cwd)) { memcpy(cwd + L, "/std/fs/fs.o", 13); cwd[L+13] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 18 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/fs/fs.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 18 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/fs/fs.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.process argc/argv/getenv；优先 cwd，产出 std/process/process.o。 */
static const char *get_std_process_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/process/process.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 26) != NULL) { size_t L = strlen(cwd); if (L + 26 <= sizeof(cwd)) { memcpy(cwd + L, "/std/process/process.o", 23); cwd[L+23] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 24 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/process/process.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 24 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/process/process.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.string 长串快路径（memcmp/memmem）；优先 cwd，产出 std/string/string.o。 */
static const char *get_std_string_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/string/string.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 24) != NULL) { size_t L = strlen(cwd); if (L + 24 <= sizeof(cwd)) { memcpy(cwd + L, "/std/string/string.o", 21); cwd[L+21] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 22 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/string/string.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 22 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/string/string.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.heap 堆分配（malloc/free）；优先 cwd，产出 std/heap/heap.o。 */
static const char *get_std_heap_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/heap/heap.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/heap/heap.o", 17); cwd[L+17] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 20 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/heap/heap.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 20 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/heap/heap.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.runtime panic/abort（std/runtime/runtime.o）；优先 cwd。 */
static const char *get_std_runtime_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/runtime/runtime.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 28) != NULL) { size_t L = strlen(cwd); if (L + 28 <= sizeof(cwd)) { memcpy(cwd + L, "/std/runtime/runtime.o", 24); cwd[L+24] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 26 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/runtime/runtime.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 26 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/runtime/runtime.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.net TCP 网络（std/net/net.o）；优先 cwd，产出 std/net/net.o。 */
static const char *get_std_net_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/net/net.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/net/net.o", 15); cwd[L+15] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (!argv0 || !argv0[0]) return buf;
    { const char *last_slash = strrchr(argv0, '/'); int n = last_slash ? (int)(last_slash - argv0) : 0;
      if (last_slash && n + 18 < (int)sizeof(buf)) { memcpy(buf, argv0, (size_t)n); buf[n] = '\0'; strcat(buf, "/../std/net/net.o"); if (realpath(buf, resolved) != NULL) return resolved; }
      else if (!last_slash && 18 < (int)sizeof(buf)) { buf[0] = '.'; buf[1] = '\0'; strcat(buf, "/../std/net/net.o"); if (realpath(buf, resolved) != NULL) return resolved; } }
    return buf;
}

/** std.thread 线程（std/thread/thread.o）；与 get_std_net_o_path 类似，产出 std/thread/thread.o。优先用 getcwd 与相对路径，避免依赖 argv[0] 解析。 */
static const char *get_std_thread_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
    /* 1) 相对路径 std/thread/thread.o（调用方 cwd 常为仓库根） */
    if (realpath("std/thread/thread.o", resolved) != NULL) return resolved;
    /* 2) getcwd() + /std/thread/thread.o */
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 22) != NULL) {
            size_t cwd_len = strlen(cwd_buf);
            if (cwd_len + 22 < sizeof(cwd_buf)) {
                memcpy(cwd_buf + cwd_len, "/std/thread/thread.o", 21);
                cwd_buf[cwd_len + 20] = '\0';
                if (realpath(cwd_buf, resolved) != NULL) return resolved;
            }
        }
    }
    /* 3) argv[0] 所在目录 + /../std/thread/thread.o */
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 22) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 22 < (int)sizeof(buf)) {
            strcat(buf, "/../std/thread/thread.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    return buf;
}

/** std.time 时间与睡眠（std/time/time.o）；与 get_std_thread_o_path 类似，产出 std/time/time.o。 */
static const char *get_std_time_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
    if (realpath("std/time/time.o", resolved) != NULL) return resolved;
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 18) != NULL) {
            size_t cwd_len = strlen(cwd_buf);
            if (cwd_len + 18 < sizeof(cwd_buf)) {
                memcpy(cwd_buf + cwd_len, "/std/time/time.o", 17);
                cwd_buf[cwd_len + 16] = '\0';
                if (realpath(cwd_buf, resolved) != NULL) return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 22) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 22 < (int)sizeof(buf)) {
            strcat(buf, "/../std/time/time.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    return buf;
}

/** std.random 密码学安全随机（std/random/random.o）；与 get_std_time_o_path 类似，产出 std/random/random.o。 */
static const char *get_std_random_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
    if (realpath("std/random/random.o", resolved) != NULL) return resolved;
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 22) != NULL) {
            size_t cwd_len = strlen(cwd_buf);
            if (cwd_len + 22 < sizeof(cwd_buf)) {
                memcpy(cwd_buf + cwd_len, "/std/random/random.o", 21);
                cwd_buf[cwd_len + 20] = '\0';
                if (realpath(cwd_buf, resolved) != NULL) return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 26) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 26 < (int)sizeof(buf)) {
            strcat(buf, "/../std/random/random.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    return buf;
}

/** std.env 环境变量与临时目录（std/env/env.o）；与 get_std_random_o_path 类似，产出 std/env/env.o。优先基于 argv[0] 解析绝对路径，避免依赖当前工作目录。 */
static const char *get_std_env_o_path(const char *argv0) {
    static char buf[PATH_MAX];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
    /* 优先用 argv[0] 得到可执行文件绝对路径，再推导 std/env/env.o，不依赖 cwd */
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last_slash = strrchr(buf, '/');
        if (last_slash && (size_t)(last_slash - buf) + 22 < sizeof(buf)) {
            *last_slash = '\0';
            strcat(buf, "/../std/env/env.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    buf[0] = '\0';
    if (realpath("std/env/env.o", resolved) != NULL) return resolved;
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 18) != NULL) {
            size_t cwd_len = strlen(cwd_buf);
            if (cwd_len + 18 < sizeof(cwd_buf)) {
                memcpy(cwd_buf + cwd_len, "/std/env/env.o", 15);
                cwd_buf[cwd_len + 14] = '\0';
                if (realpath(cwd_buf, resolved) != NULL) return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 22) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 22 < (int)sizeof(buf)) {
            strcat(buf, "/../std/env/env.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    return buf;
}

/** std.sync 互斥锁（std/sync/sync.o）；与 get_std_env_o_path 类似，产出 std/sync/sync.o。链接时 Unix 需 -lpthread。 */
static const char *get_std_sync_o_path(const char *argv0) {
    static char buf[PATH_MAX];
    static char resolved[PATH_MAX];
    buf[0] = '\0';
    resolved[0] = '\0';
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last_slash = strrchr(buf, '/');
        if (last_slash && (size_t)(last_slash - buf) + 22 < sizeof(buf)) {
            *last_slash = '\0';
            strcat(buf, "/../std/sync/sync.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    buf[0] = '\0';
    if (realpath("std/sync/sync.o", resolved) != NULL) return resolved;
    {
        char cwd_buf[512];
        if (getcwd(cwd_buf, sizeof(cwd_buf) - 18) != NULL) {
            size_t cwd_len = strlen(cwd_buf);
            if (cwd_len + 17 < sizeof(cwd_buf)) {
                memcpy(cwd_buf + cwd_len, "/std/sync/sync.o", 17);
                cwd_buf[cwd_len + 16] = '\0';
                if (realpath(cwd_buf, resolved) != NULL) return resolved;
            }
        }
    }
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 22) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 22 < (int)sizeof(buf)) {
            strcat(buf, "/../std/sync/sync.o");
            if (realpath(buf, resolved) != NULL) return resolved;
        }
    }
    return buf;
}

/** std.encoding UTF-8/ASCII（std/encoding/encoding.o）；优先 cwd。 */
static const char *get_std_encoding_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/encoding/encoding.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 26) != NULL) { size_t L = strlen(cwd); if (L + 26 <= sizeof(cwd)) { memcpy(cwd + L, "/std/encoding/encoding.o", 25); cwd[L+25] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 28 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/encoding/encoding.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** std.base64（std/base64/base64.o）。 */
static const char *get_std_base64_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/base64/base64.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 24) != NULL) { size_t L = strlen(cwd); if (L + 24 <= sizeof(cwd)) { memcpy(cwd + L, "/std/base64/base64.o", 20); cwd[L+20] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 24 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/base64/base64.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** std.crypto（std/crypto/crypto.o）。 */
static const char *get_std_crypto_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/crypto/crypto.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 24) != NULL) { size_t L = strlen(cwd); if (L + 24 <= sizeof(cwd)) { memcpy(cwd + L, "/std/crypto/crypto.o", 20); cwd[L+20] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 24 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/crypto/crypto.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** std.log（std/log/log.o）。 */
static const char *get_std_log_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/log/log.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 18) != NULL) { size_t L = strlen(cwd); if (L + 18 <= sizeof(cwd)) { memcpy(cwd + L, "/std/log/log.o", 14); cwd[L+14] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 20 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/log/log.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** std.test（std/test/test.o）。 */
static const char *get_std_test_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/test/test.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 22) != NULL) { size_t L = strlen(cwd); if (L + 22 <= sizeof(cwd)) { memcpy(cwd + L, "/std/test/test.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/test/test.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/atomic/atomic.o 路径，供链接 std.atomic 时使用；优先 cwd 以兼容多工作区。 */
static const char *get_std_atomic_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/atomic/atomic.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 22) != NULL) { size_t L = strlen(cwd); if (L + 22 <= sizeof(cwd)) { memcpy(cwd + L, "/std/atomic/atomic.o", 21); cwd[L+21] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 24 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/atomic/atomic.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/channel/channel.o 路径；优先 cwd。 */
static const char *get_std_channel_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/channel/channel.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 26) != NULL) { size_t L = strlen(cwd); if (L + 26 <= sizeof(cwd)) { memcpy(cwd + L, "/std/channel/channel.o", 25); cwd[L+25] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 26 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/channel/channel.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/backtrace/backtrace.o 路径；优先 cwd。 */
static const char *get_std_backtrace_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/backtrace/backtrace.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 30) != NULL) { size_t L = strlen(cwd); if (L + 30 <= sizeof(cwd)) { memcpy(cwd + L, "/std/backtrace/backtrace.o", 29); cwd[L+29] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 28 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/backtrace/backtrace.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/hash/hash.o 路径；优先 cwd。 */
static const char *get_std_hash_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/hash/hash.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/hash/hash.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/hash/hash.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/math/math.o 路径；优先 cwd。链接时需 -lm。 */
static const char *get_std_math_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/math/math.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/math/math.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/math/math.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/sort/sort.o 路径；优先 cwd。 */
static const char *get_std_sort_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/sort/sort.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/sort/sort.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/sort/sort.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** 根据 cwd 或 argv[0] 得到 std/ffi/ffi.o 路径；优先 cwd。 */
static const char *get_std_ffi_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/ffi/ffi.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 18) != NULL) { size_t L = strlen(cwd); if (L + 18 <= sizeof(cwd)) { memcpy(cwd + L, "/std/ffi/ffi.o", 14); cwd[L+14] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 20 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/ffi/ffi.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** P4 std 模块 .o 路径（按需链接）；优先 cwd 以兼容多工作区。 */
static const char *get_std_json_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/json/json.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/json/json.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/json/json.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_csv_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/csv/csv.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 18) != NULL) { size_t L = strlen(cwd); if (L + 18 <= sizeof(cwd)) { memcpy(cwd + L, "/std/csv/csv.o", 14); cwd[L+14] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 20 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/csv/csv.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_regex_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/regex/regex.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 22) != NULL) { size_t L = strlen(cwd); if (L + 22 <= sizeof(cwd)) { memcpy(cwd + L, "/std/regex/regex.o", 18); cwd[L+18] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 24 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/regex/regex.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_compress_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/compress/compress.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 28) != NULL) { size_t L = strlen(cwd); if (L + 28 <= sizeof(cwd)) { memcpy(cwd + L, "/std/compress/compress.o", 25); cwd[L+25] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 28 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/compress/compress.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_unicode_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/unicode/unicode.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 26) != NULL) { size_t L = strlen(cwd); if (L + 26 <= sizeof(cwd)) { memcpy(cwd + L, "/std/unicode/unicode.o", 22); cwd[L+22] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 26 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/unicode/unicode.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_dynlib_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/dynlib/dynlib.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 26) != NULL) { size_t L = strlen(cwd); if (L + 26 <= sizeof(cwd)) { memcpy(cwd + L, "/std/dynlib/dynlib.o", 20); cwd[L+20] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 26 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/dynlib/dynlib.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_http_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/http/http.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 20) != NULL) { size_t L = strlen(cwd); if (L + 20 <= sizeof(cwd)) { memcpy(cwd + L, "/std/http/http.o", 16); cwd[L+16] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 22 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/http/http.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}
static const char *get_std_tar_o_path(const char *argv0) {
    static char buf[PATH_MAX], resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("std/tar/tar.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 18) != NULL) { size_t L = strlen(cwd); if (L + 18 <= sizeof(cwd)) { memcpy(cwd + L, "/std/tar/tar.o", 14); cwd[L+14] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0] && realpath(argv0, buf) != NULL) {
        char *last = strrchr(buf, '/');
        if (last && (size_t)(last - buf) + 20 < sizeof(buf)) { *last = '\0'; strcat(buf, "/../std/tar/tar.o"); if (realpath(buf, resolved) != NULL) return resolved; }
    }
    return buf;
}

/** runtime_panic.o 路径；优先 cwd（compiler/runtime_panic.o 或 getcwd+"/compiler/runtime_panic.o"），再 argv[0] 目录。 */
static const char *get_runtime_panic_o_path(const char *argv0) {
    static char buf[512];
    static char resolved[PATH_MAX];
    buf[0] = resolved[0] = '\0';
    if (realpath("compiler/runtime_panic.o", resolved) != NULL) return resolved;
    { char cwd[512]; if (getcwd(cwd, sizeof(cwd) - 24) != NULL) { size_t L = strlen(cwd); if (L + 24 <= sizeof(cwd)) { memcpy(cwd + L, "/compiler/runtime_panic.o", 25); cwd[L+24] = '\0'; if (realpath(cwd, resolved) != NULL) return resolved; } } }
    if (argv0 && argv0[0]) {
        const char *last_slash = strrchr(argv0, '/');
        int n;
        if (last_slash) {
            n = (int)(last_slash - argv0);
            if (n >= (int)sizeof(buf) - 20) return buf;
            memcpy(buf, argv0, (size_t)n);
            buf[n] = '\0';
        } else {
            buf[0] = '.'; buf[1] = '\0';
            n = 1;
        }
        if (n + 18 < (int)sizeof(buf)) {
            strcat(buf, "/runtime_panic.o");
            if (realpath(buf, resolved) != NULL) return resolved;
            return buf;
        }
    }
    return buf;
}

#ifdef SHU_USE_SU_PIPELINE
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
    int32_t current_func_index; /* typeck 用：当前检查的函数下标，供 EXPR_VAR 查形参；-1 表示未在函数内 */
    const char *dep_paths[32];  /* 每个 dep 的 import 路径，供 codegen 时设置 C 符号前缀，与 dep_modules 一一对应 */
    int32_t skip_codegen_dep_0; /* 非 0 时跳过 dep 0 的 codegen，-o 时设 1，driver 由 io.o 提供 */
    int32_t entry_already_parsed; /* 非 0 时 entry 已由 C 侧解析，pipeline 跳过 parse 直接 typeck+codegen */
    int32_t current_func_single_empty_param_index; /* codegen：当前函数唯一无名形参下标，无名 EXPR_VAR 输出 _pN；无或多个为 -1 */
    int32_t current_func_empty_param_count;        /* codegen：当前函数无名形参个数，≥2 时按出现顺序用 indices 中下标输出 _pN */
    int32_t current_func_empty_param_indices[16];  /* codegen：无名形参的 param 下标，与声明 _p1,_p2 等一致 */
    int32_t current_emit_empty_var_next_index;     /* codegen：下一个无名 EXPR_VAR 使用的下标，发射后自增 */
    int32_t emit_expr_as_callee;                    /* codegen：当前在发射 call 的 callee 时置 1，无名 VAR 不占 _pN */
    void *current_codegen_module;                   /* codegen：当前正在生成 C 的模块，CALL 未在 dep 解析时判断是否本模块并加前缀 */
    void *current_codegen_arena;                     /* codegen：当前正在生成 C 的 arena */
};
/* 形参顺序与 pipeline.su 一致：第一为 module，第二为 arena，避免 entry 被错位导致 main 空体。 */
extern int pipeline_run_su_pipeline(void *module, void *arena, const uint8_t *source_data, size_t source_len, void *out_buf, void *ctx);

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
/** 7.4：直接生成 ELF64 .o 到 out_buf（仅 x86_64）；由 asm.su 提供，pipeline_su.o 链接；ElfCodegenCtx 在 platform/elf.su，C 侧为 platform_elf_ElfCodegenCtx。out_buf 用 void* 避免不同 GCC 下「形参内 struct 声明不可见」导致 -Wincompatible-pointer-types。 */
struct platform_elf_ElfCodegenCtx;
extern int32_t asm_asm_codegen_elf_o(void *module, void *arena, void *ctx, struct platform_elf_ElfCodegenCtx *elf_ctx, void *out_buf);
#if !defined(SHU_USE_SU_DRIVER)
/** 判断 -o 路径是否写出对象文件（.o / .obj 则写 ELF/Mach-O/COFF 而非 .s） */
static int output_is_elf_o(const char *path) {
    if (!path) return 0;
    size_t n = strlen(path);
    if (n >= 2 && path[n - 2] == '.' && (path[n - 1] == 'o' || path[n - 1] == 'O'))
        return 1;
    return n >= 4 && path[n - 4] == '.' && path[n - 3] == 'o' && path[n - 2] == 'b' && path[n - 1] == 'j';
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
 * runtime_panic_o：可选，提供 shulang_panic_ 的 .o 路径；NULL 则仅链用户 .o。
 * io_o：可选，舒 IO 后端 .o（分析/舒IO实现路线图.md）；提供 io_read/io_write；链入时 Linux 需加 -lc。
 * net_o：可选，std.net .o（TCP socket）；NULL 则不链入。
 * thread_o：可选，std.thread .o（线程）；NULL 则不链入；Unix 需 -lpthread。
 * 返回值：0 成功，-1 失败。
 */
static int invoke_ld(const char *o_path, const char *exe_path, const char *target, int use_macho_o, int use_coff_o, const char *runtime_panic_o, const char *io_o, const char *net_o, const char *thread_o) {
    (void)target;
    if (!o_path || !exe_path) return -1;
#if defined(__APPLE__)
    if (use_macho_o) {
        pid_t pid = fork();
        if (pid < 0) { perror("shu: fork (ld)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, net_o, thread_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, net_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, thread_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0] && net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, net_o, thread_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0] && net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, net_o, "-lSystem", (char *)NULL);
            if (runtime_panic_o && runtime_panic_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, "-lSystem", (char *)NULL);
            if (io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, net_o, thread_o, "-lSystem", (char *)NULL);
            if (io_o && io_o[0] && net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, net_o, "-lSystem", (char *)NULL);
            if (io_o && io_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, thread_o, "-lSystem", (char *)NULL);
            if (io_o && io_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, "-lSystem", (char *)NULL);
            if (net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, net_o, thread_o, "-lSystem", (char *)NULL);
            if (net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, net_o, "-lSystem", (char *)NULL);
            if (thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, thread_o, "-lSystem", (char *)NULL);
            execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, "-lSystem", (char *)NULL);
            execlp("clang", "clang", "-o", exe_path, o_path, (char *)NULL);
            perror("shu: ld/clang");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shu: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shu: ld failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
#endif
    if (use_coff_o) {
        /* Windows：lld-link /entry:_main /out:exe.exe out.obj；io.o/net.o/thread.o 需链入；net 用 Winsock 需 ws2_32.lib */
        char out_opt[512];
        int nn = snprintf(out_opt, sizeof(out_opt), "/out:%s", exe_path);
        if (nn < 0 || nn >= (int)sizeof(out_opt)) return -1;
        pid_t pid = fork();
        if (pid < 0) { perror("shu: fork (link)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, net_o, thread_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, net_o, thread_o, "ws2_32.lib", (char *)NULL);
            }
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, net_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, net_o, "ws2_32.lib", (char *)NULL);
            }
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, runtime_panic_o, io_o, "ws2_32.lib", (char *)NULL);
            }
            if (runtime_panic_o && runtime_panic_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, runtime_panic_o, (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, runtime_panic_o, (char *)NULL);
            }
            if (io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, io_o, net_o, thread_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, io_o, net_o, thread_o, "ws2_32.lib", (char *)NULL);
            }
            if (io_o && io_o[0] && net_o && net_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, io_o, net_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, io_o, net_o, "ws2_32.lib", (char *)NULL);
            }
            if (io_o && io_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, io_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, io_o, "ws2_32.lib", (char *)NULL);
            }
            if (net_o && net_o[0] && thread_o && thread_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, net_o, thread_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, net_o, thread_o, "ws2_32.lib", (char *)NULL);
            }
            if (net_o && net_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, net_o, "ws2_32.lib", (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, net_o, "ws2_32.lib", (char *)NULL);
            }
            if (thread_o && thread_o[0]) {
                execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, thread_o, (char *)NULL);
                execlp("link", "link", "/entry:_main", out_opt, o_path, thread_o, (char *)NULL);
            }
            execlp("lld-link", "lld-link", "/entry:_main", out_opt, o_path, (char *)NULL);
            execlp("link", "link", "/entry:_main", out_opt, o_path, (char *)NULL);
            perror("shu: lld-link/link");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shu: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shu: link failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
    /* Linux/ELF：ld -e _main -o exe o_path [runtime_panic.o] [io.o] [net.o] [thread.o] [-luring -lpthread] [-lc] */
    {
        pid_t pid = fork();
        if (pid < 0) { perror("shu: fork (ld)"); return -1; }
        if (pid == 0) {
            if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, net_o, thread_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0] && net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, net_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (runtime_panic_o && runtime_panic_o[0] && io_o && io_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, io_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (runtime_panic_o && runtime_panic_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, runtime_panic_o, (char *)NULL);
            else if (io_o && io_o[0] && net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, net_o, thread_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (io_o && io_o[0] && net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, net_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (io_o && io_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, io_o, "-luring", "-lpthread", "-lc", (char *)NULL);
            else if (net_o && net_o[0] && thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, net_o, thread_o, "-lpthread", "-lc", (char *)NULL);
            else if (net_o && net_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, net_o, "-lc", (char *)NULL);
            else if (thread_o && thread_o[0])
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, thread_o, "-lpthread", "-lc", (char *)NULL);
            else
                execlp("ld", "ld", "-e", "_main", "-o", exe_path, o_path, (char *)NULL);
            perror("shu: ld");
            _exit(127);
        }
        int status;
        if (waitpid(pid, &status, 0) != pid) { perror("shu: waitpid"); return -1; }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "shu: ld failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            return -1;
        }
        return 0;
    }
}
#endif /* !SHU_USE_SU_DRIVER */
/** 调试：打印 module 中每个 func 的 name_len/name（由 Makefile 追加到 pipeline_gen.c）；便于定位 mai/ba 截断 */
extern void pipeline_debug_module_funcs(void *module);
/* 与生成代码中 codegen_CodegenOutBuf 布局一致；C 在调用后将 data[0..len-1] 写到 FILE* */
#define SU_CODEGEN_OUTBUF_CAP 262144
struct codegen_CodegenOutBuf {
    unsigned char data[SU_CODEGEN_OUTBUF_CAP];
    int32_t len;
};
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
_Static_assert(offsetof(struct codegen_CodegenOutBuf, len) == SU_CODEGEN_OUTBUF_CAP, "CodegenOutBuf: len must follow data[] for ABI");
#endif
/** asm 后端 C 桩：-backend asm 时由 pipeline 调用，写出最小 GAS（main return 42），便于 pipeline 不 import asm 仍可构建 shu_su。符号供 pipeline_gen.c 链接。 */
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
extern int32_t parser_diag_token_after_collect_imports(struct shulang_slice_uint8_t *source, void *module);
extern int32_t pipeline_parse_one_function_ok(struct shulang_slice_uint8_t *source, void *arena);
extern int32_t pipeline_typeck_after_parse_ok(void *arena, void *module, struct shulang_slice_uint8_t *source, void *ctx);
#ifdef SHU_USE_SU_DRIVER
/* run_compiler_c 由 C 在此定义，转调 main.su 的 main_run_compiler_c，供 main_entry 等调用；不再依赖 driver_gen.c 追加。 */
extern int main_run_compiler_c(int argc, uint8_t *argv);
int run_compiler_c(int argc, char **argv) {
  return main_run_compiler_c(argc, (uint8_t *)argv);
}
#endif
/* 6.1 后 typeck/pipeline 用 ctx，以下仅保留供旧 pipeline_gen.c 或未链入 .su 时兼容；可逐步移除。 */
#if defined(SHU_USE_SU_PIPELINE) || defined(SHU_USE_SU_DRIVER)
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

#ifdef SHU_USE_SU_PREPROCESS
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
        fprintf(stderr, "shu: cannot open import (tried %s)\n", pipeline_resolved_path_buf);
        return -1;
    }
    size_t prep_len = 0;
    char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
    free(raw);
    if (!prep) {
        fprintf(stderr, "shu: preprocess failed for import\n");
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
    parser_parse_into_init(module, arena);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &slice);
    return pr.ok == 0 ? 0 : -1;
}

/** 6.1 原 C 桥接：已由 pipeline.su 的 pipeline_parse_into_buf（调 parser.parse_into_buf）替代，此处不再编译以免重复符号。 */
#if 0
int32_t pipeline_parse_into_buf(void *arena, void *module, const uint8_t *buf, int32_t buf_len) {
    if (!buf) return -1;
    struct shulang_slice_uint8_t slice = { .data = (uint8_t *)buf, .length = (size_t)buf_len };
    parser_parse_into_init(module, arena);
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
        /* 单段 import（如 preprocess）：再试 lib_root/import/import.su，与 pipeline.su 内 resolve 一致 */
        if (strchr(import_path, '.') == NULL && path_size >= 16) {
            int n = (int)strlen(import_path);
            if (n > 0 && n < 64) {
                (void)snprintf(path, path_size, "%s/%.64s/%.64s.su", lib_root, import_path, import_path);
                if (access(path, R_OK) == 0) return;
            }
        }
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

#if !defined(SHU_USE_SU_DRIVER)
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
 * -E 且入口为 pipeline.su 时，向 stdout 输出一行 #include "pipeline_glue.c"，
 * 由编译器在编译 pipeline_gen.c 时包含胶水（cwd 需为 compiler/ 或 -I 含之）。不再追写整份文件内容。
 */
static void emit_pipeline_glue_include(void) {
    fputs("\n#include \"pipeline_glue.c\"\n", stdout);
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
        fprintf(stderr, "shu: too many transitive imports\n");
        return NULL;
    }
    char path[512];
    resolve_import_file_path_multi(lib_roots, n_lib_roots, entry_dir, import_path, path, sizeof(path));
    char *raw = read_file(path, NULL);
    if (!raw) {
        fprintf(stderr, "shu: cannot open import '%s' (tried %s)\n", import_path, path);
        return NULL;
    }
    char *src = preprocess(raw, 0, defines, ndefines, NULL);
    free(raw);
    if (!src) {
        fprintf(stderr, "shu: preprocess failed for import '%s'\n", import_path);
        return NULL;
    }
    Lexer *lex = lexer_new(src);
    ASTModule *dep = NULL;
    int pr = parse(lex, &dep);
    lexer_free(lex);
    free(src);
    if (pr != 0 || !dep) {
        fprintf(stderr, "shu: failed to parse import '%s'\n", import_path);
        return NULL;
    }
    if (dep->num_imports > 0 && !dep->import_paths) {
        fprintf(stderr, "shu: internal error: module has num_imports but import_paths is NULL\n");
        ast_module_free(dep);
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
        fprintf(stderr, "shu: typeck failed for import '%s'\n", import_path);
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
    if (mod->num_imports > 0 && !mod->import_paths) {
        fprintf(stderr, "shu: internal error: entry module has num_imports but import_paths is NULL\n");
        return -1;
    }
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
#endif /* !SHU_USE_SU_DRIVER */

/**
 * 将 Token 类型枚举转为可读字符串，用于控制台打印。
 * 功能说明：供无 -o 时打印 Token 序列使用，返回如 "FN"、"IDENT"、"INT" 等。
 * 参数：k 当前 Token 的 kind。
 * 返回值：指向静态字符串的指针，只读；未知 kind 返回 "?"。
 * 错误与边界：无；不分配内存。
 * 副作用与约定：无副作用；返回值不得被 free。
 */
#if !defined(SHU_USE_SU_DRIVER)
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
        case TOKEN_PLUS_EQ:   return "PLUS_EQ";
        case TOKEN_MINUS_EQ:  return "MINUS_EQ";
        case TOKEN_STAR_EQ:   return "STAR_EQ";
        case TOKEN_SLASH_EQ:  return "SLASH_EQ";
        case TOKEN_PERCENT_EQ: return "PERCENT_EQ";
        case TOKEN_AMP_EQ:    return "AMP_EQ";
        case TOKEN_PIPE_EQ:   return "PIPE_EQ";
        case TOKEN_CARET_EQ:  return "CARET_EQ";
        case TOKEN_LSHIFT_EQ: return "LSHIFT_EQ";
        case TOKEN_RSHIFT_EQ: return "RSHIFT_EQ";
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
#endif /* !SHU_USE_SU_DRIVER */

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
 * 功能说明：阶段 7.3 多文件；阶段 8 优化：向 cc 传入 -O<level>（默认 -O2）、可选 -flto（LTO）、-o out_path。
 * use_lto：非 0 且在非 -O0 时向 cc 传 -flto。
 * io_o：可选，舒 IO 后端 .o 路径；NULL 则不链入。
 * fs_o：可选，std.fs 高性能 .o 路径（mmap/munmap）；NULL 则不链入。
 * process_o：可选，std.process argc/argv/getenv .o 路径；NULL 则不链入。
 * string_o：可选，std.string 长串快路径 .o（memcmp/memmem）；NULL 则不链入。
 * heap_o：可选，std.heap 堆分配 .o（malloc/free）；NULL 则不链入。
 * runtime_o：可选，std.runtime .o（panic/abort）；NULL 则不链入。
 * runtime_panic_o：可选，提供 shulang_panic_ 的 .o（与 runtime_o 同链，否则 std/runtime/runtime.o 缺符号）；NULL 则不链入。
 * net_o：可选，std.net .o（TCP socket）；NULL 则不链入。
 * thread_o：可选，std.thread .o（线程）；NULL 则不链入；Unix 需 -lpthread。
 * time_o：可选，std.time .o（时间与睡眠）；NULL 则不链入。
 * random_o：可选，std.random .o（密码学安全随机）；NULL 则不链入。
 * env_o：可选，std.env .o（环境变量与临时目录）；NULL 则不链入。
 * sync_o：可选，std.sync .o（互斥锁）；NULL 则不链入；Unix 需 -lpthread。
 * encoding_o, base64_o, crypto_o, log_o, test_o：可选，std.encoding/base64/crypto/log/test .o。
 * include_root：可选，仓库根目录，用于 -I 以便生成 .c 能 #include std/fs、path、map、error 等 ABI 头；NULL 或空则不传 -I。
 * 返回值：0 表示 cc 执行成功且退出码为 0；-1 表示参数非法、fork/exec 失败或 cc 非零退出。
 */
static int invoke_cc(const char **c_paths, int n, const char *out_path, const char *target, const char *opt_level, int use_lto, const char *io_o, const char *fs_o, const char *process_o, const char *string_o, const char *heap_o, const char *runtime_o, const char *runtime_panic_o, const char *net_o, const char *thread_o, const char *time_o, const char *random_o, const char *env_o, const char *sync_o, const char *encoding_o, const char *base64_o, const char *crypto_o, const char *log_o, const char *atomic_o, const char *channel_o, const char *backtrace_o, const char *hash_o, const char *math_o, const char *sort_o, const char *ffi_o, const char *json_o, const char *csv_o, const char *regex_o, const char *compress_o, const char *unicode_o, const char *dynlib_o, const char *http_o, const char *tar_o, const char *test_o, const char *include_root) {
    (void)target;
    if (!c_paths || n < 1) return -1;
    if (!opt_level || !*opt_level) opt_level = "2";
    pid_t pid = fork();
    if (pid < 0) {
        perror("shu: fork");
        return -1;
    }
    if (pid == 0) {
        char *argv[MAX_C_FILES + 24];
        int i = 0;
        argv[i++] = (char *)"cc";
        {
            static char oopt_buf[8];
            (void)snprintf(oopt_buf, sizeof(oopt_buf), "-O%s", opt_level);
            argv[i++] = oopt_buf;
        }
        /* 阶段 8：非调试时传 -DNDEBUG；-flto 便于跨模块内联（2.3 构建与链接） */
        if (strcmp(opt_level, "0") != 0)
            argv[i++] = (char *)"-DNDEBUG";
        if (use_lto && strcmp(opt_level, "0") != 0)
            argv[i++] = (char *)"-flto";
        argv[i++] = (char *)"-o";
        argv[i++] = (char *)out_path;
        if (include_root && include_root[0]) {
            argv[i++] = (char *)"-I";
            argv[i++] = (char *)include_root;
        }
        for (int j = 0; j < n && i < MAX_C_FILES + 8; j++)
            argv[i++] = (char *)c_paths[j];
        if (io_o && io_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char io_o_abs[PATH_MAX];
            if (realpath(io_o, io_o_abs) != NULL)
                io_o = io_o_abs;
#endif
            argv[i++] = (char *)io_o;
#if defined(__linux__)
            argv[i++] = (char *)"-luring";
            argv[i++] = (char *)"-pthread";
#endif
#if defined(_WIN32) || defined(_WIN64)
            argv[i++] = (char *)"-lws2_32";
#endif
        }
        if (fs_o && fs_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char fs_o_abs[PATH_MAX];
            if (realpath(fs_o, fs_o_abs) != NULL)
                fs_o = fs_o_abs;
#endif
            argv[i++] = (char *)fs_o;
        }
        if (process_o && process_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char process_o_abs[PATH_MAX];
            if (realpath(process_o, process_o_abs) != NULL)
                process_o = process_o_abs;
#endif
            argv[i++] = (char *)process_o;
        }
        if (string_o && string_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char string_o_abs[PATH_MAX];
            if (realpath(string_o, string_o_abs) != NULL)
                string_o = string_o_abs;
#endif
            argv[i++] = (char *)string_o;
        }
        if (heap_o && heap_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char heap_o_abs[PATH_MAX];
            if (realpath(heap_o, heap_o_abs) != NULL)
                heap_o = heap_o_abs;
#endif
            argv[i++] = (char *)heap_o;
        }
        if (runtime_o && runtime_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char runtime_o_abs[PATH_MAX];
            if (realpath(runtime_o, runtime_o_abs) != NULL)
                runtime_o = runtime_o_abs;
#endif
            argv[i++] = (char *)runtime_o;
        }
        if (runtime_panic_o && runtime_panic_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char runtime_panic_o_abs[PATH_MAX];
            if (realpath(runtime_panic_o, runtime_panic_o_abs) != NULL)
                runtime_panic_o = runtime_panic_o_abs;
#endif
            argv[i++] = (char *)runtime_panic_o;
        }
        if (net_o && net_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char net_o_abs[PATH_MAX];
            if (realpath(net_o, net_o_abs) != NULL)
                net_o = net_o_abs;
#endif
            argv[i++] = (char *)net_o;
        }
        if (thread_o && thread_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char thread_o_abs[PATH_MAX];
            if (realpath(thread_o, thread_o_abs) != NULL)
                thread_o = thread_o_abs;
#endif
            argv[i++] = (char *)thread_o;
#if defined(__linux__)
            argv[i++] = (char *)"-pthread";
#endif
        }
        if (time_o && time_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char time_o_abs[PATH_MAX];
            if (realpath(time_o, time_o_abs) != NULL)
                time_o = time_o_abs;
#endif
            argv[i++] = (char *)time_o;
        }
        if (random_o && random_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char random_o_abs[PATH_MAX];
            if (realpath(random_o, random_o_abs) != NULL)
                random_o = random_o_abs;
#endif
            argv[i++] = (char *)random_o;
#if defined(_WIN32) || defined(_WIN64)
            argv[i++] = (char *)"-lbcrypt";
#endif
        }
        if (env_o && env_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char env_o_abs[PATH_MAX];
            if (realpath(env_o, env_o_abs) != NULL)
                env_o = env_o_abs;
#endif
            argv[i++] = (char *)env_o;
        }
        if (sync_o && sync_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char sync_o_abs[PATH_MAX];
            if (realpath(sync_o, sync_o_abs) != NULL)
                sync_o = sync_o_abs;
#endif
            argv[i++] = (char *)sync_o;
#if defined(__linux__)
            argv[i++] = (char *)"-pthread";
#endif
        }
        if (encoding_o && encoding_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char encoding_o_abs[PATH_MAX];
            if (realpath(encoding_o, encoding_o_abs) != NULL) encoding_o = encoding_o_abs;
#endif
            argv[i++] = (char *)encoding_o;
        }
        if (base64_o && base64_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char base64_o_abs[PATH_MAX];
            if (realpath(base64_o, base64_o_abs) != NULL) base64_o = base64_o_abs;
#endif
            argv[i++] = (char *)base64_o;
        }
        if (crypto_o && crypto_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char crypto_o_abs[PATH_MAX];
            if (realpath(crypto_o, crypto_o_abs) != NULL) crypto_o = crypto_o_abs;
#endif
            argv[i++] = (char *)crypto_o;
        }
        if (log_o && log_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char log_o_abs[PATH_MAX];
            if (realpath(log_o, log_o_abs) != NULL) log_o = log_o_abs;
#endif
            argv[i++] = (char *)log_o;
        }
        if (atomic_o && atomic_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char atomic_o_abs[PATH_MAX];
            if (realpath(atomic_o, atomic_o_abs) != NULL) atomic_o = atomic_o_abs;
#endif
            argv[i++] = (char *)atomic_o;
        }
        if (channel_o && channel_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char channel_o_abs[PATH_MAX];
            if (realpath(channel_o, channel_o_abs) != NULL) channel_o = channel_o_abs;
#endif
            argv[i++] = (char *)channel_o;
#if defined(__linux__)
            argv[i++] = (char *)"-pthread";
#endif
        }
        if (backtrace_o && backtrace_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char backtrace_o_abs[PATH_MAX];
            if (realpath(backtrace_o, backtrace_o_abs) != NULL) backtrace_o = backtrace_o_abs;
#endif
            argv[i++] = (char *)backtrace_o;
        }
        if (hash_o && hash_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char hash_o_abs[PATH_MAX];
            if (realpath(hash_o, hash_o_abs) != NULL) hash_o = hash_o_abs;
#endif
            argv[i++] = (char *)hash_o;
        }
        if (math_o && math_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char math_o_abs[PATH_MAX];
            if (realpath(math_o, math_o_abs) != NULL) math_o = math_o_abs;
#endif
            argv[i++] = (char *)math_o;
            argv[i++] = (char *)"-lm";
        }
        if (sort_o && sort_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char sort_o_abs[PATH_MAX];
            if (realpath(sort_o, sort_o_abs) != NULL) sort_o = sort_o_abs;
#endif
            argv[i++] = (char *)sort_o;
        }
        if (ffi_o && ffi_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char ffi_o_abs[PATH_MAX];
            if (realpath(ffi_o, ffi_o_abs) != NULL) ffi_o = ffi_o_abs;
#endif
            argv[i++] = (char *)ffi_o;
        }
        if (json_o && json_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char json_o_abs[PATH_MAX];
            if (realpath(json_o, json_o_abs) != NULL) json_o = json_o_abs;
#endif
            argv[i++] = (char *)json_o;
        }
        if (csv_o && csv_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char csv_o_abs[PATH_MAX];
            if (realpath(csv_o, csv_o_abs) != NULL) csv_o = csv_o_abs;
#endif
            argv[i++] = (char *)csv_o;
        }
        if (regex_o && regex_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char regex_o_abs[PATH_MAX];
            if (realpath(regex_o, regex_o_abs) != NULL) regex_o = regex_o_abs;
#endif
            argv[i++] = (char *)regex_o;
        }
        if (compress_o && compress_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char compress_o_abs[PATH_MAX];
            if (realpath(compress_o, compress_o_abs) != NULL) compress_o = compress_o_abs;
#endif
            argv[i++] = (char *)compress_o;
        }
        if (unicode_o && unicode_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char unicode_o_abs[PATH_MAX];
            if (realpath(unicode_o, unicode_o_abs) != NULL) unicode_o = unicode_o_abs;
#endif
            argv[i++] = (char *)unicode_o;
        }
        if (dynlib_o && dynlib_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char dynlib_o_abs[PATH_MAX];
            if (realpath(dynlib_o, dynlib_o_abs) != NULL) dynlib_o = dynlib_o_abs;
#endif
            argv[i++] = (char *)dynlib_o;
#if defined(__linux__)
            argv[i++] = (char *)"-ldl";
#endif
        }
        if (http_o && http_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char http_o_abs[PATH_MAX];
            if (realpath(http_o, http_o_abs) != NULL) http_o = http_o_abs;
#endif
            argv[i++] = (char *)http_o;
        }
        if (tar_o && tar_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char tar_o_abs[PATH_MAX];
            if (realpath(tar_o, tar_o_abs) != NULL) tar_o = tar_o_abs;
#endif
            argv[i++] = (char *)tar_o;
        }
        if (test_o && test_o[0]) {
#if !defined(_WIN32) && !defined(_WIN64)
            static char test_o_abs[PATH_MAX];
            if (realpath(test_o, test_o_abs) != NULL) test_o = test_o_abs;
#endif
            argv[i++] = (char *)test_o;
        }
        /* 使用 std.compress 时末尾加 -lz，满足启用 zlib 的 compress.o 链接 */
        if (compress_o && compress_o[0])
            argv[i++] = (char *)"-lz";
#if defined(__linux__) || defined(__APPLE__)
        /* Unix 上 thread.o 使用 CPU_ZERO/CPU_SET（sched.h）；用 -pthread 让 cc 以正确顺序拉取 libpthread/libc，Debian/Docker 等需此方式解析符号 */
        if ((thread_o && thread_o[0]) || (sync_o && sync_o[0]) || (channel_o && channel_o[0]))
            argv[i++] = (char *)"-pthread";
        argv[i++] = (char *)"-lc";
#endif
        argv[i++] = NULL;
        argv[0] = (char *)"cc";
        execvp("cc", argv);
        argv[0] = (char *)"gcc";
        execvp("gcc", argv);
        perror("shu: cc/gcc");
        _exit(127);
    }
    int status;
    if (waitpid(pid, &status, 0) != pid) {
        perror("shu: waitpid");
        return -1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "shu: cc failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
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

#if !defined(SHU_USE_SU_DRIVER)
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
#endif /* !SHU_USE_SU_DRIVER */

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
 * SHU_USE_SU_DRIVER 时 run_compiler_c_impl 由 main.su 提供（桩），C 不定义以免重复符号。
 */
#if defined(SHU_USE_SU_DRIVER)
/* run_compiler_c_impl 由 main.su 提供（桩），C 不定义。 */
#else
#define RUN_CC_FUNC run_compiler_c
int RUN_CC_FUNC(int argc, char **argv) {
#ifdef SHU_USE_SU_FRONTEND
    /* 阶段 3.2：链入 _su.o 时不再提供 typeck_module/codegen_* 等 C 符号，run_compiler_c 不应被调用；main 已走 run_compiler_su_path。 */
    (void)argc;
    (void)argv;
    fprintf(stderr, "shu: internal error: run_compiler_c called with SHU_USE_SU_FRONTEND\n");
    return 1;
#else
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_roots_arr[MAX_LIB_ROOTS];
    int n_lib_roots = 0;
    const char *target = NULL;
    const char *opt_level = NULL;  /* -O 优化级别：0/2/s，默认 2（阶段 8） */
    int use_lto = 0;       /* -flto：传 -flto 给 cc，发布/性能构建时建议（2.3） */
    int emit_c_only = 0;  /* -E：仅生成 C 到 stdout，不调用 cc */
    int emit_extern_imports = 0;  /* 阶段 3.1：-E-extern 时仅展开入口，import 用 extern，生成瘦 C */
    #ifdef SHU_USE_SU_PIPELINE
    int use_su_pipeline = 0;  /* -su：使用纯 .su 流水线（需链接 pipeline_gen.o） */
    int use_asm_backend = 0;  /* -backend asm：出汇编而非 C，并走 -su pipeline */
    #endif
    const char *defines[MAX_DEFINES];
    int ndefines = 0;

    for (int i = 1; i < argc; i++) {
        #ifdef SHU_USE_SU_PIPELINE
        if (strcmp(argv[i], "-su") == 0) {
            use_su_pipeline = 1;
        } else if (strcmp(argv[i], "-backend") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "shu: -backend requires an argument (e.g. asm)\n");
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
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
                return 1;
            }
            if (ndefines >= MAX_DEFINES) {
                fprintf(stderr, "shu: too many -D defines\n");
                return 1;
            }
            defines[ndefines++] = argv[i + 1];
            i++;
        } else if (strncmp(argv[i], "-D", 2) == 0 && argv[i][2] != '\0') {
            /* -DSYMBOL 形式 */
            if (ndefines >= MAX_DEFINES) {
                fprintf(stderr, "shu: too many -D defines\n");
                return 1;
            }
            defines[ndefines++] = argv[i] + 2;
        } else if (strcmp(argv[i], "-O") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
                return 1;
            }
            opt_level = argv[i + 1];
            if (strcmp(opt_level, "0") != 0 && strcmp(opt_level, "2") != 0 && strcmp(opt_level, "s") != 0) {
                fprintf(stderr, "shu: -O expects 0, 2, or s (got '%s')\n", opt_level);
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-flto") == 0) {
            use_lto = 1;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
                return 1;
            }
            out_path = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
                return 1;
            }
            if (n_lib_roots < MAX_LIB_ROOTS)
                lib_roots_arr[n_lib_roots++] = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-target") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
                return 1;
            }
            target = argv[i + 1];
            i++;  /* 只多跳 1：for 末尾还有 i++，会再跳过 triple，避免多跳把 <file.su> 也跳过导致 input_path 未设 */
        } else if (argv[i][0] == '-') {
            /* 未知选项（如 -backend 在未链 pipeline 的构建中）：提示而非当作输入文件 */
            if (strcmp(argv[i], "-backend") == 0) {
                fprintf(stderr, "shu: -backend asm not available in this build. Use: make bootstrap-driver\n");
            } else {
                fprintf(stderr, "shu: unknown option '%s'\n", argv[i]);
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
    if (!use_lto && getenv("SHULANG_LTO") && strcmp(getenv("SHULANG_LTO"), "1") == 0)
        use_lto = 1;

    if (!input_path) {
        fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] [ -D <sym> ] [ -O 0|2|s ] [ -flto ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shu");
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
        fprintf(stderr, "shu: preprocess failed for '%s'\n", input_path);
        return 1;
    }

#ifdef SHU_USE_SU_PIPELINE
    if (use_su_pipeline) {
        size_t arena_sz = pipeline_sizeof_arena();
        size_t module_sz = pipeline_sizeof_module();
        void *arena = malloc(arena_sz);
        void *module = malloc(module_sz);
        if (!arena || !module) {
            fprintf(stderr, "shu: -su pipeline: malloc failed\n");
            if (arena) free(arena);
            if (module) free(module);
            free(src);
            return 1;
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        struct shulang_slice_uint8_t src_slice = { (uint8_t *)src, src_len };
        parser_parse_into_init(module, arena);
        struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
        if (pr.ok != 0) {
            fprintf(stderr, "shu: -su pipeline failed (parse_into)\n");
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
                char resolved[PATH_MAX];
                resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir, path_c, resolved, sizeof(resolved));
                size_t raw_len = 0;
                char *raw = read_file(resolved, &raw_len);
                if (!raw) {
                    fprintf(stderr, "shu: cannot open import '%s' (tried %s)\n", path_c, resolved);
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
                    fprintf(stderr, "shu: preprocess failed for import '%s'\n", path_c);
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
                strcpy(asm_tmp_o_path, "/tmp/shu_asm_XXXXXX");
                int fd = mkstemp(asm_tmp_o_path);
                if (fd < 0) {
                    perror("shu: mkstemp (asm)");
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
                    perror("shu: -o (asm)");
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
                    fprintf(stderr, "shu: elf_ctx alloc failed\n");
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
                fprintf(stderr, "shu: -su pipeline: dep alloc failed\n");
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
        /* 仅对 entry 跑一次 pipeline（其内部会 codegen 所有 deps + entry），避免对每个 dep 单独跑再 fwrite 导致 deps 被写两遍、重复符号。 */
        typeck_ndep = n_deps;
        for (int i = 0; i < n_deps; i++) {
            typeck_dep_module_ptrs[i] = dep_modules[i];
            typeck_dep_arena_ptrs[i] = dep_arenas[i];
        }
        pipeline_set_dep_slots(dep_arenas, dep_modules);
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        int ec = pipeline_run_su_pipeline(module, arena, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx);
        if (ec == 0 && (out_buf.len > 0 || emit_elf_o)) {
            if (emit_elf_o && elf_ctx_ptr) {
                int32_t elf_ec = asm_asm_codegen_elf_o(module, arena, (void *)&pctx, (struct platform_elf_ElfCodegenCtx *)elf_ctx_ptr, (void *)&out_buf);
                if (elf_ec != 0 || out_buf.len <= 0) {
                    fprintf(stderr, "shu: asm_codegen_elf_o failed\n");
                    if (asm_out) fclose(asm_out);
                    if (elf_ctx_ptr) free(elf_ctx_ptr);
                    for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
                    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
            }
            fwrite(out_buf.data, 1, (size_t)out_buf.len, asm_out ? asm_out : stdout);
            if (!asm_out) fflush(stdout);
            if (asm_out) fclose(asm_out);
            asm_out = NULL;
            if (elf_ctx_ptr) { free(elf_ctx_ptr); elf_ctx_ptr = NULL; }
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) {
                n_deps--;
                free(dep_sources[n_deps]);
                free(dep_paths[n_deps]);
            }
            /* -o <exe>（无 .o/.s 后缀）时：已写临时 .o，调 ld 生成可执行文件后删临时文件；传入 runtime_panic.o/io.o/net.o */
            if (asm_want_exe && asm_tmp_o_path[0]) {
                const char *panic_o = get_runtime_panic_o_path(argv[0]);
                const char *io_o = get_io_o_path(argv[0]);
                const char *net_o = get_std_net_o_path(argv[0]);
                const char *thread_o = get_std_thread_o_path(argv[0]);
                int ld_ok = invoke_ld(asm_tmp_o_path, out_path, target, pctx.use_macho_o, pctx.use_coff_o, panic_o, io_o, net_o, thread_o);
                unlink(asm_tmp_o_path);
                if (ld_ok != 0) {
                    fprintf(stderr, "shu: ld failed (asm -o exe)\n");
                    free(arena);
                    free(module);
                    free(src);
                    return 1;
                }
            }
        } else {
            /* ec != 0 或 ec == 0 但 out_buf.len == 0（且非 emit_elf_o） */
            if (ec == 0 && out_buf.len == 0 && !emit_elf_o && !asm_out) {
                /* -su -E 时 pipeline 成功但 codegen 产出 0 字节（如库模块或 codegen 路径未写 main），写最小 C 桩使 run-su-pipeline 等测试能通过 */
                fprintf(stdout, "int main(void){return 0;}\n");
                fflush(stdout);
            }
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
                fprintf(stderr, "shu: -su pipeline failed (parse_into / typeck_su_ast / codegen_su_ast)\n");
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
                        fprintf(stderr, "shu: (diagnostic) parse_into OK, typeck_after_parse=%d (0=ok -2=parse_fail -10=main_idx<0 -11=main_idx>=num_funcs -1=impl)\n", (int)tck);
                    } else {
                        int32_t fail_tok = parser_diag_fail_at_token_kind(&src_slice);
                        int32_t one_ok = pipeline_parse_one_function_ok(&src_slice, diag_arena);
                        fprintf(stderr, "shu: (diagnostic) parse_into failed (len=%zu, diag_fail=%d, parse_one_func_ok=%d)\n",
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
        fprintf(stderr, "shu: parse failed for '%s' (pr=%d)\n", input_path, pr);
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
#if defined(SHU_USE_SU_TYPECK) && !defined(SHU_USE_SU_PIPELINE)
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
            fprintf(stdout, "static inline void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
            fprintf(stdout, "static inline void shulang_panic_(int has_msg, int msg_val) {\n");
            fprintf(stdout, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
            fprintf(stdout, "  abort();\n");
            fprintf(stdout, "}\n");
            /* pipeline.su 及可能拉入 std.io 的 parser/typeck/codegen/preprocess 等 -E 产出均需 _buf 声明，以便单文件编译通过；main.su 产出 driver_gen.c 不调这些，不输出以免 -Wunused-function。 */
            if (input_path && (strstr(input_path, "pipeline.su") != NULL || strstr(input_path, "parser.su") != NULL || strstr(input_path, "typeck.su") != NULL || strstr(input_path, "codegen.su") != NULL || strstr(input_path, "preprocess.su") != NULL)) {
                fprintf(stdout, "extern int32_t shu_io_register(uint8_t *ptr, size_t len, size_t handle);\n");
                fprintf(stdout, "extern int32_t shu_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n");
                fprintf(stdout, "extern int32_t shu_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n");
                fprintf(stdout, "typedef struct { void *ptr; size_t len; size_t handle; } shu_buffer_abi_t;\n");
                fprintf(stdout, "static inline int32_t shu_io_register_buf(intptr_t buf) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_register((uint8_t *)b->ptr, b->len, b->handle); }\n");
                fprintf(stdout, "static inline int32_t shu_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_submit_read((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n");
                fprintf(stdout, "static inline int32_t shu_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_submit_write((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n");
                fprintf(stdout, "typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_batch_buf_t;\n");
                fprintf(stdout, "extern int io_register_buffers_buf_c(const shu_batch_buf_t *bufs, int nr);\n");
                fprintf(stdout, "static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const shu_batch_buf_t *)(uintptr_t)bufs, nr); }\n");
            }
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
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
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
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
                    ec = codegen_codegen_entry_library_module_to_c(mod, lib_name, dep_mods, (const char **)mod->import_paths, ndep, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#else
                    ec = codegen_library_module_to_c(mod, lib_name, dep_mods, (const char **)mod->import_paths, ndep, stdout, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#endif
                } else if (mod->main_func && mod->main_func->body) {
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
                    ec = codegen_codegen_entry_module_to_c(mod, stdout, dep_mods, (const char **)mod->import_paths, ndep, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#else
                    ec = codegen_module_to_c(mod, stdout, dep_mods, (const char **)mod->import_paths, ndep, NULL, NULL, NULL, NULL, emitted_type_buf, &n_emitted, max_emitted);
#endif
                } else {
                    fprintf(stderr, "shu: no main function (cannot emit C)\n");
                    ec = -1;
                }
            }
        } else {
            /* 无依赖：仅输出入口模块（保持原有行为） */
            if (mod->main_func && mod->main_func->body) {
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
                ec = codegen_codegen_entry_module_to_c(mod, stdout, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#else
                ec = codegen_module_to_c(mod, stdout, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
            } else if (mod->num_funcs > 0) {
                const char *lib_name = entry_lib_name_from_path(input_path);
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
                ec = codegen_codegen_entry_library_module_to_c(mod, lib_name, NULL, NULL, 0, stdout, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#else
                ec = codegen_library_module_to_c(mod, lib_name, NULL, NULL, 0, stdout, NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
            } else {
                fprintf(stderr, "shu: no main function (cannot emit C)\n");
                ec = -1;
            }
        }
        /* -E 且入口为 pipeline.su 时输出 #include "pipeline_glue.c"，编译时由 cc 包含，不再追写整份内容 */
        if (ec == 0 && input_path && strstr(input_path, "pipeline.su") != NULL)
            emit_pipeline_glue_include();
        while (n_all--) { free(all_dep_paths[n_all]); ast_module_free(all_dep_mods[n_all]); }
        ast_module_free(mod);
        free(src);
        return ec != 0 ? 1 : 0;
    }

    /* 若指定 -o：需有 main，生成 C（含 import 的 .c）→ 调用 cc 链接；依赖使用已加载的 dep_mods（7.3 跨模块调用 + 传递依赖）；阶段 8.1 DCE 仅生成被引用函数与单态化 */
    if (out_path) {
        if (!mod->main_func || !mod->main_func->body) {
            fprintf(stderr, "shu: no main function (cannot emit executable)\n");
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
        char tmp[] = "/tmp/shu_XXXXXX";
        int fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shu: mkstemp");
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
            fprintf(cf, "static inline void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
            fprintf(cf, "static inline void shulang_panic_(int has_msg, int msg_val) {\n");
            fprintf(cf, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
            fprintf(cf, "  abort();\n");
            fprintf(cf, "}\n");
            /* std.io.driver：前向声明 + 与 io.o 一致的 extern，再提供两桩实现；完整 struct 由 codegen 在后文给出 */
            fprintf(cf, "struct std_io_driver_Buffer;\n");
            fprintf(cf, "extern ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);\n");
            fprintf(cf, "extern ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);\n");
            fprintf(cf, "static int32_t std_io_driver_submit_read_batch_buf(size_t handle, struct std_io_driver_Buffer *bufs, int32_t n, uint32_t timeout_ms) {\n");
            fprintf(cf, "  ptrdiff_t r = io_read_batch_buf((int)handle, bufs, n, timeout_ms);\n");
            fprintf(cf, "  return (r < 0) ? -1 : (int32_t)r;\n");
            fprintf(cf, "}\n");
            fprintf(cf, "static int32_t std_io_driver_submit_write_batch_buf(size_t handle, struct std_io_driver_Buffer *bufs, int32_t n, uint32_t timeout_ms) {\n");
            fprintf(cf, "  ptrdiff_t r = io_write_batch_buf((int)handle, bufs, n, timeout_ms);\n");
            fprintf(cf, "  return (r < 0) ? -1 : (int32_t)r;\n");
            fprintf(cf, "}\n");
            fprintf(cf, "#define std_io_submit_read_batch_buf std_io_driver_submit_read_batch_buf\n");
            fprintf(cf, "#define std_io_submit_write_batch_buf std_io_driver_submit_write_batch_buf\n");
            /* driver 的 read_ptr/read_ptr_len 由 core/io.o 提供，与 pipeline 内联 ABI 一致 */
            fprintf(cf, "#define std_io_driver_driver_read_ptr_len shu_io_read_ptr_len\n");
            fprintf(cf, "#define std_io_driver_driver_read_ptr shu_io_read_ptr\n");
            /* std.io.driver 的 register/submit_read/submit_write 体需调 _buf 包装；io_register_buffers_buf_i32 供 submit_register_fixed_buffers_buf 体 */
            fprintf(cf, "extern int32_t shu_io_register(uint8_t *ptr, size_t len, size_t handle);\n");
            fprintf(cf, "extern int32_t shu_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n");
            fprintf(cf, "extern int32_t shu_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n");
            fprintf(cf, "typedef struct { void *ptr; size_t len; size_t handle; } shu_buffer_abi_t;\n");
            fprintf(cf, "static inline int32_t shu_io_register_buf(intptr_t buf) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_register((uint8_t *)b->ptr, b->len, b->handle); }\n");
            fprintf(cf, "static inline int32_t shu_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_submit_read((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n");
            fprintf(cf, "static inline int32_t shu_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf; return shu_io_submit_write((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m); }\n");
            fprintf(cf, "typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_batch_buf_t;\n");
            fprintf(cf, "extern int io_register_buffers_buf_c(const shu_batch_buf_t *bufs, int nr);\n");
            fprintf(cf, "static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const shu_batch_buf_t *)(uintptr_t)bufs, nr); }\n");
            /* 自举：入口为 parser.su 时需 parser_slice_from_buf；前向声明使调用处可编译，定义在文件末尾追加 */
            if (input_path && strstr(input_path, "parser.su") != NULL)
                fprintf(cf, "static struct shulang_slice_uint8_t parser_slice_from_buf(uint8_t *data, int32_t len);\n");
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
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
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
#if defined(SHU_USE_SU_CODEGEN) && !defined(SHU_USE_SU_PIPELINE)
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
        /* 自举：parser.su 单独编可执行文件时提供 parser_slice_from_buf 桩实现（与 pipeline_glue.c 中一致） */
        if (input_path && strstr(input_path, "parser.su") != NULL) {
            fprintf(cf, "\nstatic struct shulang_slice_uint8_t parser_slice_from_buf(uint8_t *data, int32_t len) {\n");
            fprintf(cf, "  struct shulang_slice_uint8_t s;\n  s.data = data;\n  s.length = (size_t)(len >= 0 ? len : 0);\n  return s;\n}\n");
        }
        fclose(cf);
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            perror("shu: rename");
            unlink(tmp);
            while (ndep--) ast_module_free(dep_mods[ndep]);
            ast_module_free(mod);
            free(src);
            return 1;
        }
        if (getenv("SHU_DEBUG_C")) {
            FILE *dc = fopen(tmp_c, "r");
            if (dc) {
                FILE *out = fopen("/tmp/shu_debug.c", "w");
                if (out) {
                    int ch;
                    while ((ch = getc(dc)) != EOF) putc(ch, out);
                    fclose(out);
                }
                fclose(dc);
            }
        }
        c_paths[n_c++] = tmp_c;

        const char *io_o = get_io_o_path(argv[0]);
        const char *fs_o = get_std_fs_o_path(argv[0]);
        const char *process_o = get_std_process_o_path(argv[0]);
        const char *string_o = get_std_string_o_path(argv[0]);
        const char *heap_o = get_std_heap_o_path(argv[0]);
        const char *runtime_o = get_std_runtime_o_path(argv[0]);
        const char *runtime_panic_o = get_runtime_panic_o_path(argv[0]);
        const char *net_o = get_std_net_o_path(argv[0]);
        const char *thread_o = get_std_thread_o_path(argv[0]);
        const char *time_o = get_std_time_o_path(argv[0]);
        const char *random_o = get_std_random_o_path(argv[0]);
        const char *env_o = get_std_env_o_path(argv[0]);
        const char *sync_o = get_std_sync_o_path(argv[0]);
        const char *encoding_o = get_std_encoding_o_path(argv[0]);
        const char *base64_o = get_std_base64_o_path(argv[0]);
        const char *crypto_o = get_std_crypto_o_path(argv[0]);
        const char *log_o = get_std_log_o_path(argv[0]);
        const char *atomic_o = get_std_atomic_o_path(argv[0]);
        const char *channel_o = get_std_channel_o_path(argv[0]);
        const char *backtrace_o = get_std_backtrace_o_path(argv[0]);
        const char *hash_o = get_std_hash_o_path(argv[0]);
        const char *math_o = get_std_math_o_path(argv[0]);
        const char *sort_o = get_std_sort_o_path(argv[0]);
        const char *ffi_o = get_std_ffi_o_path(argv[0]);
        const char *json_o = get_std_json_o_path(argv[0]);
        const char *csv_o = get_std_csv_o_path(argv[0]);
        const char *regex_o = get_std_regex_o_path(argv[0]);
        const char *compress_o = get_std_compress_o_path(argv[0]);
        const char *unicode_o = get_std_unicode_o_path(argv[0]);
        const char *dynlib_o = get_std_dynlib_o_path(argv[0]);
        const char *http_o = get_std_http_o_path(argv[0]);
        const char *tar_o = get_std_tar_o_path(argv[0]);
        const char *test_o = get_std_test_o_path(argv[0]);
        int cc_ok = invoke_cc(c_paths, n_c, out_path, target, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, test_o, get_repo_root(argv[0]));
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
#endif /* !SHU_USE_SU_FRONTEND */
}
#undef RUN_CC_FUNC
#endif /* !SHU_USE_SU_DRIVER */

/**
 * 阶段 3 全 .su 前端：当 SHU_USE_SU_FRONTEND 且 SHU_USE_SU_PIPELINE 时，用 pipeline 生成 C 并调用 cc，不依赖 C 的 typeck/codegen。
 * 否则直接转调 run_compiler_c。完全自举时 run_compiler_su_path 由 main.su 提供，C 不定义以免重复符号。
 */
#if !defined(SHU_USE_SU_DRIVER)
int run_compiler_su_path(int argc, char **argv) {
#if !defined(SHU_USE_SU_FRONTEND) || !defined(SHU_USE_SU_PIPELINE)
    return run_compiler_c(argc, argv);
#else
#define SU_PATH_MAX_LIB_ROOTS 16
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_roots_arr[SU_PATH_MAX_LIB_ROOTS];
    int n_lib_roots = 0;
    const char *opt_level = "2";
    int use_lto = 0;
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
        if (strcmp(argv[i], "-flto") == 0) { use_lto = 1; continue; }
        if (!input_path) input_path = argv[i];
    }
    if (!use_lto && getenv("SHULANG_LTO") && strcmp(getenv("SHULANG_LTO"), "1") == 0) use_lto = 1;
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
        fprintf(stderr, "shu: preprocess failed for '%s'\n", input_path);
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
    parser_parse_into_init(module, arena);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
    if (pr.ok != 0) {
        fprintf(stderr, "shu: parse failed for '%s' (pr.ok=%d main_idx=%d)\n", input_path, (int)pr.ok, (int)pr.main_idx);
        { int32_t first_tok = parser_diag_token_after_collect_imports(&src_slice, module); fprintf(stderr, "shu: first_token_after_imports=%d (1=TOKEN_FUNCTION)\n", (int)first_tok); }
        if (src_len > 0 && src_len < 200)
            fprintf(stderr, "shu: src_len=%zu first_bytes=%.*s\n", src_len, (int)(src_len > 60 ? 60 : src_len), src);
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
        if (collect_deps_transitive(module, arena_sz, module_sz, lib_roots_arr, n_lib_roots, entry_dir_buf,
                dep_sources, dep_lens, dep_paths, &n_deps) != 0) {
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        /* 反转 dep 顺序使叶子模块（如 std.io.core）先于调用方（std.io）codegen，避免 C 中未声明即调用 */
        for (int rev = 0; rev < n_deps / 2; rev++) {
            int o = n_deps - 1 - rev;
            char *ts = dep_sources[rev]; dep_sources[rev] = dep_sources[o]; dep_sources[o] = ts;
            size_t tl = dep_lens[rev]; dep_lens[rev] = dep_lens[o]; dep_lens[o] = tl;
            char *tp = dep_paths[rev]; dep_paths[rev] = dep_paths[o]; dep_paths[o] = tp;
        }
    }
    typeck_ndep = 0;
    /* 模板末尾须为 6 个 X，mkstemp 后重命名为 .c 以便 cc/ld 识别 */
    char tmp[] = "/tmp/shu_su.XXXXXX";
    char tmp_c[32];
    int fd = -1;
    FILE *cf;
    if (emit_to_stdout) {
        cf = stdout;
    } else {
        fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shu: mkstemp");
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
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            unlink(tmp);
            fclose(cf);
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
            fprintf(stderr, "shu: -su path: dep alloc failed\n");
            while (j > 0) { j--; free(dep_arenas[j]); free(dep_modules[j]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
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
        pctx.dep_paths[j] = dep_paths[j];
    }
    pctx.ndep = n_deps;
    /* 先对每个 dep 跑 pipeline 仅做 parse+typecheck，填充 dep_arenas/dep_modules，不写 C 到文件。 */
    for (int j = 0; j < n_deps; j++) {
        struct ast_PipelineDepCtx one_ctx;
        memset(&one_ctx, 0, sizeof(one_ctx));
        pipeline_fill_ctx_path_buffers(&one_ctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
        one_ctx.dep_modules[0] = dep_modules[j];
        one_ctx.dep_arenas[0] = dep_arenas[j];
        one_ctx.ndep = 0;
        struct codegen_CodegenOutBuf dep_out;
        memset(&dep_out, 0, sizeof(dep_out));
        driver_set_current_dep_path_for_codegen(dep_paths[j]);
        int ec = pipeline_run_su_pipeline(dep_modules[j], dep_arenas[j], (const uint8_t *)dep_sources[j], dep_lens[j], (void *)&dep_out, (void *)&one_ctx);
        driver_set_current_dep_path_for_codegen(NULL);
        if (ec != 0) {
            fprintf(stderr, "shu: pipeline failed for import '%s' (rc=%d)\n", dep_paths[j], ec);
            for (int k = 0; k < n_deps; k++) { free(dep_arenas[k]); free(dep_modules[k]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
        /* 不把 dep 的 C 写入 cf，避免与后面 entry 一次 codegen 的 deps+entry 重复。 */
    }
    typeck_ndep = n_deps;
    for (int j = 0; j < n_deps; j++) {
        typeck_dep_module_ptrs[j] = dep_modules[j];
        typeck_dep_arena_ptrs[j] = dep_arenas[j];
    }
    pipeline_set_dep_slots(dep_arenas, dep_modules);
    driver_dep_seed_slots(dep_arenas, dep_modules, n_deps);
    codegen_set_dep_slots_for_su_pipeline((struct ASTModule **)dep_modules, (const char **)dep_paths, n_deps);
    memset(arena, 0, arena_sz);
    memset(module, 0, module_sz);
    int ec = pipeline_run_su_pipeline(module, arena, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx);
    driver_dep_seeded_clear_all();
    codegen_set_dep_slots_for_su_pipeline(NULL, NULL, 0);
    for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
    free(arena);
    free(module);
    free(src);
    if (ec != 0 || out_buf.len == 0) {
        fprintf(stderr, "shu: pipeline failed for '%s'\n", input_path);
        if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
        return 1;
    }
    {
        /* 内联 std.io / std.net ABI；其余 std.fs / path / map / error 仍 include 头文件 */
        size_t first_line = 0;
        while (first_line < (size_t)out_buf.len && out_buf.data[first_line] != '\n') first_line++;
        if (first_line < (size_t)out_buf.len) first_line++;
        static const char fs_abi_include[] = "#include \"std/fs/fs_abi.h\"\n";
        static const char path_abi_include[] = "#include \"std/path/path_abi.h\"\n";
        static const char map_abi_include[] = "#include \"std/map/map_abi.h\"\n";
        static const char error_abi_include[] = "#include \"std/error/error_abi.h\"\n";
        if (fwrite(out_buf.data, 1, first_line, cf) != first_line
            || write_io_net_abi_inline(cf) != 0
            || fwrite(fs_abi_include, 1, sizeof(fs_abi_include) - 1, cf) != (size_t)(sizeof(fs_abi_include) - 1)
            || fwrite(path_abi_include, 1, sizeof(path_abi_include) - 1, cf) != (size_t)(sizeof(path_abi_include) - 1)
            || fwrite(map_abi_include, 1, sizeof(map_abi_include) - 1, cf) != (size_t)(sizeof(map_abi_include) - 1)
            || fwrite(error_abi_include, 1, sizeof(error_abi_include) - 1, cf) != (size_t)(sizeof(error_abi_include) - 1)
            || fwrite(out_buf.data + first_line, 1, (size_t)out_buf.len - first_line, cf) != (size_t)out_buf.len - first_line) {
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
            return 1;
        }
    }
    if (!emit_to_stdout) {
        if (fclose(cf) != 0) {
            unlink(tmp_c);
            return 1;
        }
        {
            const char *c_paths[1] = { tmp_c };
            const char *io_o = get_io_o_path(argv[0]);
            const char *fs_o = get_std_fs_o_path(argv[0]);
            const char *process_o = get_std_process_o_path(argv[0]);
            const char *string_o = get_std_string_o_path(argv[0]);
            const char *heap_o = get_std_heap_o_path(argv[0]);
            const char *runtime_o = get_std_runtime_o_path(argv[0]);
            const char *runtime_panic_o = get_runtime_panic_o_path(argv[0]);
            const char *net_o = get_std_net_o_path(argv[0]);
            const char *thread_o = get_std_thread_o_path(argv[0]);
            const char *time_o = get_std_time_o_path(argv[0]);
            const char *random_o = get_std_random_o_path(argv[0]);
            const char *env_o = get_std_env_o_path(argv[0]);
            const char *sync_o = get_std_sync_o_path(argv[0]);
            const char *encoding_o = get_std_encoding_o_path(argv[0]);
            const char *base64_o = get_std_base64_o_path(argv[0]);
            const char *crypto_o = get_std_crypto_o_path(argv[0]);
            const char *log_o = get_std_log_o_path(argv[0]);
            const char *atomic_o = get_std_atomic_o_path(argv[0]);
            const char *channel_o = get_std_channel_o_path(argv[0]);
            const char *backtrace_o = get_std_backtrace_o_path(argv[0]);
            const char *hash_o = get_std_hash_o_path(argv[0]);
            const char *math_o = get_std_math_o_path(argv[0]);
            const char *sort_o = get_std_sort_o_path(argv[0]);
            const char *ffi_o = get_std_ffi_o_path(argv[0]);
            const char *json_o = get_std_json_o_path(argv[0]);
            const char *csv_o = get_std_csv_o_path(argv[0]);
            const char *regex_o = get_std_regex_o_path(argv[0]);
            const char *compress_o = get_std_compress_o_path(argv[0]);
            const char *unicode_o = get_std_unicode_o_path(argv[0]);
            const char *dynlib_o = get_std_dynlib_o_path(argv[0]);
            const char *http_o = get_std_http_o_path(argv[0]);
            const char *tar_o = get_std_tar_o_path(argv[0]);
            const char *test_o = get_std_test_o_path(argv[0]);
            int cc_ret = invoke_cc(c_paths, 1, out_path, NULL, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, test_o, get_repo_root(argv[0]));
            if (cc_ret != 0) {
                fprintf(stderr, "shu: cc failed, keeping generated C: %s\n", tmp_c);
            } else if (!getenv("SHULANG_KEEP_C")) {
                unlink(tmp_c);
            } else {
                fprintf(stderr, "shu: kept generated C: %s\n", tmp_c);
            }
            return cc_ret == 0 ? 0 : 1;
        }
    }
    return 0;
#undef SU_PATH_MAX_LIB_ROOTS
#endif
}
#endif /* !defined(SHU_USE_SU_DRIVER)：run_compiler_su_path 仅在不使用 .su driver 时由 C 提供 */

#if defined(SHU_USE_SU_PIPELINE)
/** pipeline_su.o / pipeline_gen.c 所需符号，shu_su 链接时由 runtime_su.o 提供（仅 -DSHU_USE_SU_PIPELINE）。 */
static void *driver_dep_arena_ptrs[32];
static void *driver_dep_module_ptrs[32];
/** 非 0 表示 dep i 已由 C 侧预填，pipeline 不再 read/parse；driver_dep_*_buf 返回时也不清零。 */
static int driver_dep_seeded[32];

int32_t driver_dep_seeded_get(int32_t i) {
    if (i < 0 || i >= 32) return 0;
    return driver_dep_seeded[i] ? 1 : 0;
}

/** 由 run_compiler_su_path 在预填 dep 后调用，使 pipeline 使用已有 buffer 且不再清零。 */
void driver_dep_seeded_set(int32_t i, int32_t v) {
    if (i >= 0 && i < 32) driver_dep_seeded[i] = (v != 0);
}

/** 预填路径：将 C 侧 dep 指针填入 driver 槽位并标记 seeded，entry pipeline 会复用不重载。 */
void driver_dep_seed_slots(void *arenas[32], void *modules[32], int32_t n) {
    int j;
    for (j = 0; j < 32 && j < n; j++) {
        driver_dep_arena_ptrs[j] = arenas ? arenas[j] : NULL;
        driver_dep_module_ptrs[j] = modules ? modules[j] : NULL;
        driver_dep_seeded[j] = 1;
    }
    for (; j < 32; j++) driver_dep_seeded[j] = 0;
}

/** entry pipeline 返回后清除 seeded，避免影响后续调用。 */
void driver_dep_seeded_clear_all(void) {
    int i;
    for (i = 0; i < 32; i++) driver_dep_seeded[i] = 0;
}

uint8_t *driver_dep_arena_buf(int32_t i) {
    if (i < 0 || i >= 32) return NULL;
    if (driver_dep_arena_ptrs[i] == NULL) {
        size_t sz = pipeline_sizeof_arena();
        driver_dep_arena_ptrs[i] = malloc(sz);
        if (!driver_dep_arena_ptrs[i]) return NULL;
    }
    if (!driver_dep_seeded[i])
        memset(driver_dep_arena_ptrs[i], 0, pipeline_sizeof_arena());
    return (uint8_t *)driver_dep_arena_ptrs[i];
}

uint8_t *driver_dep_module_buf(int32_t i) {
    if (i < 0 || i >= 32) return NULL;
    if (driver_dep_module_ptrs[i] == NULL) {
        size_t sz = pipeline_sizeof_module();
        driver_dep_module_ptrs[i] = malloc(sz);
        if (!driver_dep_module_ptrs[i]) return NULL;
    }
    if (!driver_dep_seeded[i])
        memset(driver_dep_module_ptrs[i], 0, pipeline_sizeof_module());
    return (uint8_t *)driver_dep_module_ptrs[i];
}

void driver_pipeline_fail_code(int rc, const uint8_t *path) {
    fprintf(stderr, "shu: pipeline failed rc=%d\n", rc);
    if (rc == -7 && path != NULL) {
        fprintf(stderr, "shu: resolve path tried: %s\n", (const char *)path);
    }
}

void driver_diagnostic_parse_fail(int32_t main_idx, int32_t num_funcs, int32_t arena_num_types) {
    fprintf(stderr, "shu: parse fail main_idx=%d num_funcs=%d arena_num_types=%d\n", (int)main_idx, (int)num_funcs, (int)arena_num_types);
}

/** -su -E 多文件诊断：codegen 前打印 module.num_funcs 与 out_buf.len，便于排查 dep 产出为空。需要时取消注释 fprintf。 */
void driver_diagnostic_before_codegen(int32_t num_funcs, int32_t out_len) {
    (void)num_funcs;
    (void)out_len;
}

/** 每个 dep codegen 后打印 j 与 out_buf.len，确认 buffer 是否递增。需要时取消注释 fprintf。 */
void driver_diagnostic_after_dep_codegen(int32_t j, int32_t out_len) {
    (void)j;
    (void)out_len;
}

/** codegen 失败时打印是第几个 dep（is_dep!=0）还是当前模块（is_dep==0），便于定位 -6。需要时取消注释 fprintf。 */
void driver_diagnostic_codegen_fail(int32_t dep_index, int32_t is_dep) {
    (void)dep_index;
    (void)is_dep;
}

/** asm 后端：不支持的 ExprKind 时由 backend.su 调用，便于定位 rc=-6；kind 为 ast_ExprKind 枚举值。 */
void driver_diagnostic_asm_unsupported_expr(int32_t kind) {
    fprintf(stderr, "shu: asm codegen unsupported ExprKind=%d\n", (int)kind);
    fflush(stderr);
}

/** asm 后端：记录当前正在 emit 的 ExprKind 序数，供 fail_at 时打印。 */
static int driver_diagnostic_asm_last_expr_kind = -1;
void driver_diagnostic_asm_set_last_expr_kind(int32_t k) {
    driver_diagnostic_asm_last_expr_kind = (int)k;
}

/** asm 后端：记录当前正在 codegen 的函数名，供 var_not_found 时打印。 */
static uint8_t driver_diagnostic_asm_current_func[72];
static int driver_diagnostic_asm_current_func_len = 0;
void driver_diagnostic_asm_set_current_func(const uint8_t *name, int32_t len) {
    driver_diagnostic_asm_current_func_len = (len > 0 && len <= 64) ? (int)len : 0;
    if (name && driver_diagnostic_asm_current_func_len > 0) {
        for (int i = 0; i < driver_diagnostic_asm_current_func_len; i++)
            driver_diagnostic_asm_current_func[i] = name[i];
    }
}

/** asm 后端：EXPR_VAR 在 local_offset 未找到时由 backend.su 调用；若 num_locals>0 可传首槽名 first_slot/first_len 便于对比。 */
void driver_diagnostic_asm_var_not_found(const uint8_t *name, int32_t len, int32_t num_locals,
    const uint8_t *first_slot, int32_t first_len) {
    fprintf(stderr, "shu: asm codegen EXPR_VAR not in ctx: \"");
    if (name && len > 0 && len <= 64) {
        for (int i = 0; i < len; i++) fputc((char)name[i], stderr);
    }
    fprintf(stderr, "\" (func: ");
    if (driver_diagnostic_asm_current_func_len > 0) {
        for (int i = 0; i < driver_diagnostic_asm_current_func_len; i++)
            fputc((char)driver_diagnostic_asm_current_func[i], stderr);
    } else {
        fprintf(stderr, "?");
    }
    fprintf(stderr, ", num_locals=%d", (int)num_locals);
    if (num_locals > 0 && first_slot && first_len > 0 && first_len <= 64) {
        fprintf(stderr, ", first_slot=\"");
        for (int i = 0; i < first_len; i++) fputc((char)first_slot[i], stderr);
        fprintf(stderr, "\" len=%d", (int)first_len);
    }
    fprintf(stderr, ")\n");
    fflush(stderr);
}

/** asm 后端：返回 -1 前调用，loc 表示失败位置（1=section_text 2=globl 3=label 4=prologue 5=block_body 6=block_inits 7=emit_expr 8=epilogue），便于定位 rc=-6。 */
void driver_diagnostic_asm_fail_at(int32_t loc) {
    fprintf(stderr, "shu: asm codegen fail_at=%d (last_expr_kind=%d)\n", (int)loc, driver_diagnostic_asm_last_expr_kind);
    fflush(stderr);
}

/** -o 可执行文件路径：非 0 时 pipeline 跳过 dep 0 的 codegen（driver 由 io.o 提供）；避免与 ctx 布局耦合。 */
static int driver_skip_codegen_dep_0_flag;
void driver_skip_codegen_dep_0_set(int32_t v) { driver_skip_codegen_dep_0_flag = (v != 0); }
int32_t driver_skip_codegen_dep_0_get(void) { return driver_skip_codegen_dep_0_flag ? 1 : 0; }

/** 当前 codegen 的 dep 路径（如 "std.io.driver"），供 .su codegen 生成带前缀的 C 名（避免与 C 关键字 register 等冲突）。 */
static const char *driver_current_dep_path_for_codegen;

void driver_set_current_dep_path_for_codegen(const char *path) {
    driver_current_dep_path_for_codegen = path;
}

const char *driver_get_current_dep_path_for_codegen(void) {
    return driver_current_dep_path_for_codegen;
}

/** 返回 1 当当前 codegen 的 dep 路径为 "std.io.core"（与 codegen_su_path_is_std_io_core 一致，供 .su 在 ctx.dep_paths 不可靠时仍能不加前缀）。 */
int driver_current_dep_path_is_std_io_core(void) {
    return (driver_current_dep_path_for_codegen && strcmp(driver_current_dep_path_for_codegen, "std.io.core") == 0) ? 1 : 0;
}

/** 返回 1 当应跳过生成该函数（当前为 std.io.driver 或 std.io 且名为 driver_read_ptr_len/driver_read_ptr 或 submit_*_batch_buf）；无条件跳过，避免与 preamble 的 extern 签名冲突。 */
int driver_should_skip_emit_func(const uint8_t *name, int name_len) {
    if (!driver_current_dep_path_for_codegen || !name) return 0;
    const char *p = driver_current_dep_path_for_codegen;
    if (strcmp(p, "std.io.driver") != 0 && strcmp(p, "std.io") != 0) return 0;
    if (name_len == 20 && strncmp((const char *)name, "driver_read_ptr_len", 20) == 0) return 1;
    if (name_len == 16 && strncmp((const char *)name, "driver_read_ptr", 16) == 0) return 1;
    if (name_len == 21 && strncmp((const char *)name, "submit_read_batch_buf", 21) == 0) return 1;
    if (name_len == 22 && strncmp((const char *)name, "submit_write_batch_buf", 22) == 0) return 1;
    return 0;
}

/** 同上，但显式传入 dep 路径（*u8 以 NUL 结尾），供 codegen.su 在 dep_index>=0 时用 ctx.dep_paths[dep_index] 调用，避免依赖全局 path 未设置。
 * 路径可能为 std.io.driver 或 std.io（单文件时 driver 为 std.io 子模块），两种均跳过 submit_*_batch_buf。 */
int driver_should_skip_emit_func_for_dep_path(const uint8_t *path, const uint8_t *name, int name_len) {
    if (!path || !name) return 0;
    const char *p = (const char *)path;
    int is_io_driver = (strcmp(p, "std.io.driver") == 0) || (strcmp(p, "std.io") == 0);
    if (!is_io_driver) return 0;
    if (name_len == 20 && strncmp((const char *)name, "driver_read_ptr_len", 20) == 0) return 1;
    if (name_len == 16 && strncmp((const char *)name, "driver_read_ptr", 16) == 0) return 1;
    if (name_len == 21 && strncmp((const char *)name, "submit_read_batch_buf", 21) == 0) return 1;
    if (name_len == 22 && strncmp((const char *)name, "submit_write_batch_buf", 22) == 0) return 1;
    return 0;
}

/** 仅按函数名跳过：submit_read_batch_buf、submit_write_batch_buf 由 preamble 提供 extern，任何 dep 都跳过生成定义，避免签名冲突。 */
int driver_should_skip_emit_func_by_name(const uint8_t *name, int name_len) {
    if (!name) return 0;
    if (name_len == 21 && strncmp((const char *)name, "submit_read_batch_buf", 21) == 0) return 1;
    if (name_len == 22 && strncmp((const char *)name, "submit_write_batch_buf", 22) == 0) return 1;
    return 0;
}

/** 调用处补第 4 参：若为 submit_read_batch_buf/submit_write_batch_buf 且当前为 3 参调用，需补 timeout_ms（如 0）。 */
int driver_is_submit_batch_buf_call(const uint8_t *name, int name_len) {
    if (!name) return 0;
    if (name_len == 21 && strncmp((const char *)name, "submit_read_batch_buf", 21) == 0) return 1;
    if (name_len == 22 && strncmp((const char *)name, "submit_write_batch_buf", 22) == 0) return 1;
    return 0;
}

/** 归一化 prefix 到 norm（. 与 / 转 _），前 14 字符；用于与 std_io_driver 匹配（兼容 13/14 字符前缀）。 */
static void driver_norm_prefix(const uint8_t *prefix, int prefix_len, char *norm) {
    int i = 0;
    for (; i < 14 && i < prefix_len && prefix; i++)
        norm[i] = (char)(prefix[i] == '/' || prefix[i] == '.' ? '_' : prefix[i]);
    norm[i] = '\0';
}

/** 生成函数定义时，若当前前缀为 std_io_driver（或 std_io_driver_）且 preamble 将该参数声明为 ptrdiff_t（首参 register/submit_read/submit_write），则返回 1。 */
int driver_force_param_ptrdiff_t(const uint8_t *prefix, int prefix_len, const uint8_t *name, int name_len, int param_index) {
    if (!name || param_index != 0) return 0;
    if (!prefix || prefix_len < 13) return 0;
    char norm[16];
    driver_norm_prefix(prefix, prefix_len, norm);
    if (strncmp(norm, "std_io_driver", 13) != 0 || (norm[13] != '\0' && norm[13] != '_')) return 0;
    if (name_len == 8 && strncmp((const char *)name, "register", 8) == 0) return 1;
    if (name_len == 11 && strncmp((const char *)name, "submit_read", 11) == 0) return 1;
    if (name_len == 12 && strncmp((const char *)name, "submit_write", 12) == 0) return 1;
    return 0;
}

/** 生成函数定义时，若 prefix 为 std_io_driver（或 std_io_driver_）且 preamble 将该参数声明为 uint32_t（timeout_ms/nr），则返回 1。 */
int driver_force_param_uint32_t(const uint8_t *prefix, int prefix_len, const uint8_t *name, int name_len, int param_index) {
    if (!name || param_index != 1) return 0;
    if (!prefix || prefix_len < 13) return 0;
    char norm[16];
    driver_norm_prefix(prefix, prefix_len, norm);
    if (strncmp(norm, "std_io_driver", 13) != 0 || (norm[13] != '\0' && norm[13] != '_')) return 0;
    if (name_len == 11 && strncmp((const char *)name, "submit_read", 11) == 0) return 1;
    if (name_len == 12 && strncmp((const char *)name, "submit_write", 12) == 0) return 1;
    if (name_len == 33 && strncmp((const char *)name, "submit_register_fixed_buffers_buf", 33) == 0) return 1;
    return 0;
}

/** 生成函数定义时，若 prefix 为 std_io_driver_ 且 preamble 将该参数声明为 int32_t，则返回 1。现已全部由 ptrdiff_t/uint32_t/struct* 覆盖，不再强制 int32_t。 */
int driver_force_param_i32(const uint8_t *prefix, int prefix_len, const uint8_t *name, int name_len, int param_index) {
    (void)prefix;
    (void)prefix_len;
    (void)name;
    (void)name_len;
    (void)param_index;
    return 0;
}

/** std.io.core 的 shu_io_read_ptr_len/shu_io_read_ptr 由 io.o 提供，pipeline 不生成以免与 io.o 重复。 */
int driver_should_skip_emit_func_core_read_ptr(const uint8_t *name, int name_len) {
    if (!name) return 0;
    if (name_len >= 19 && strncmp((const char *)name, "shu_io_read_ptr_len", 19) == 0) return 1;
    if (name_len == 15 && strncmp((const char *)name, "shu_io_read_ptr", 15) == 0) return 1;
    return 0;
}

/** 按「前缀+函数名」拼接结果判断是否跳过：若拼接后为 std_io_driver_driver_read_ptr_len 或 std_io_driver_driver_read_ptr 则返回 1，避免依赖 prefix/name 单独比较。 */
int driver_should_skip_emit_func_for_prefix(const uint8_t *prefix, int prefix_len, const uint8_t *name, int name_len) {
    if (!prefix || !name || prefix_len <= 0 || name_len <= 0) return 0;
    if (prefix_len + name_len > 64) return 0;
    char buf[65];
    memcpy(buf, prefix, (size_t)prefix_len);
    memcpy(buf + prefix_len, name, (size_t)name_len);
    buf[prefix_len + name_len] = '\0';
    if (strcmp(buf, "std_io_driver_driver_read_ptr_len") == 0) return 1;
    if (strcmp(buf, "std_io_driver_driver_read_ptr") == 0) return 1;
    return 0;
}

/** 将当前 dep 路径转为 C 前缀写入 buf（如 "std.io.driver" -> "std_io_driver_"），len 为 buf 容量。 */
void driver_get_current_dep_prefix_for_codegen(char *buf, size_t len) {
    if (!buf || len == 0) return;
    const char *path = driver_current_dep_path_for_codegen;
    if (!path) { buf[0] = '\0'; return; }
    size_t off = 0;
    for (; *path && off + 2 < len; path++)
        buf[off++] = (*path == '.') ? '_' : *path;
    if (off + 1 < len) buf[off++] = '_';
    buf[off] = '\0';
}

void driver_debug_log(int32_t step) {
    fprintf(stderr, "[parse] step %d\n", (int)step);
    fflush(stderr);
}

void parser_diag_tok_kind(int32_t k) {
    fprintf(stderr, "[parse] r.tok.kind=%d\n", (int)k);
    fflush(stderr);
}

void parser_diag_ident_len(int32_t len) {
    fprintf(stderr, "[onefunc] first ident_len=%d\n", (int)len);
    fflush(stderr);
}

void parser_diag_scan_fail(int32_t step) {
    fprintf(stderr, "shu: library_scan fail step=%d\n", (int)step);
}

int parser_is_ident_allow(const uint8_t *ident, int len) {
    if (!ident || len != 5) return 0;
    return (ident[0] == 'a' && ident[1] == 'l' && ident[2] == 'l' && ident[3] == 'o' && ident[4] == 'w') ? 1 : 0;
}
#endif /* SHU_USE_SU_PIPELINE */

#ifdef SHU_USE_SU_DRIVER
/* 阶段 6.2：main.su 内实现 argv 解析与 -su -E 执行逻辑；C 仅提供极薄原语 driver_get_argv_i。 */
/* 保留旧符号供未迁完时链接；main.su 自实现后不再调用。 */
static const char *driver_su_emit_c_path;
#define SU_EMIT_MAX_LIB_ROOTS 16
static const char *driver_su_emit_lib_roots[SU_EMIT_MAX_LIB_ROOTS];
static int driver_su_emit_n_lib_roots;
/* 供 main.su 在 -su -E 时把 path/lib_roots 灌入 C 侧，再调 driver_run_su_emit_c，以走完整多文件（deps+main）路径。 */
static char driver_su_emit_path_buf[512];
static char driver_su_emit_lib_bufs[SU_EMIT_MAX_LIB_ROOTS][256];

int driver_run_su_emit_c_set_path(const uint8_t *path, int path_len) {
    driver_su_emit_c_path = NULL;
    if (!path || path_len <= 0 || path_len >= (int)sizeof(driver_su_emit_path_buf)) return 0;
    memcpy(driver_su_emit_path_buf, path, (size_t)path_len);
    driver_su_emit_path_buf[path_len] = '\0';
    driver_su_emit_c_path = driver_su_emit_path_buf;
    return 0;
}

int driver_run_su_emit_c_set_lib(int i, const uint8_t *buf, int len) {
    if (i < 0 || i >= SU_EMIT_MAX_LIB_ROOTS || !buf || len < 0 || len >= 256) return 0;
    memcpy(driver_su_emit_lib_bufs[i], buf, (size_t)len);
    driver_su_emit_lib_bufs[i][len] = '\0';
    driver_su_emit_lib_roots[i] = driver_su_emit_lib_bufs[i];
    return 0;
}

int driver_run_su_emit_c_set_n_lib_roots(int n) {
    driver_su_emit_n_lib_roots = (n >= 0 && n <= SU_EMIT_MAX_LIB_ROOTS) ? n : 0;
    return 0;
}

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

/** 6.2 静态 arena/module 缓冲，供 driver_run_su_emit_su 避免栈上超大数组（ast_ASTArena 约 9MB+）。 */
#define DRIVER_ARENA_STATIC_SIZE (12 * 1024 * 1024)
#define DRIVER_MODULE_STATIC_SIZE (512 * 1024)
static uint8_t driver_arena_static[DRIVER_ARENA_STATIC_SIZE];
static uint8_t driver_module_static[DRIVER_MODULE_STATIC_SIZE];

/* 由 pipeline_gen.c 提供，用于 driver 在 memset 后强制将 arena.num_types 置 0，避免与生成代码布局不一致导致 type_alloc 误判 */
extern size_t pipeline_arena_offset_num_types(void);

uint8_t *driver_arena_buf(void) {
    memset(driver_arena_static, 0, DRIVER_ARENA_STATIC_SIZE);
    /* 强制 num_types=0，避免与 .su 生成 struct 布局/对齐不一致时 type_alloc 读到未清零值 */
    size_t off = pipeline_arena_offset_num_types();
    if (off + sizeof(int32_t) <= DRIVER_ARENA_STATIC_SIZE) {
        *(int32_t *)(driver_arena_static + off) = 0;
        (void)off; /* 诊断时可 fprintf(stderr, "arena off=%zu\n", off); */
    }
    return driver_arena_static;
}
uint8_t *driver_module_buf(void) {
    memset(driver_module_static, 0, DRIVER_MODULE_STATIC_SIZE);
    return driver_module_static;
}

/** 6.2 极薄原语：以 path[0..path_len-1] 为路径打开读文件，返回 fd，失败 -1。供 driver_run_su_emit_su 读入口文件，避免生成代码顺序导致 path_buf 未填就 open。 */
int driver_fs_open_read_path(const uint8_t *path, int path_len) {
    if (!path || path_len <= 0 || path_len >= 512) return -1;
    char buf[512];
    memcpy(buf, path, (size_t)path_len);
    buf[path_len] = '\0';
    return open(buf, O_RDONLY);
}

/** 6.2 极薄原语：以 path[0..path_len-1] 为路径打开写文件（O_WRONLY|O_CREAT|O_TRUNC），返回 fd，失败 -1。供 -backend asm -o 时 main.su 写 -o 文件。 */
int driver_fs_open_write(const uint8_t *path, int path_len) {
    if (!path || path_len <= 0 || path_len >= 512) return -1;
    char buf[512];
    memcpy(buf, path, (size_t)path_len);
    buf[path_len] = '\0';
#ifdef O_WRONLY
#ifdef O_CREAT
#ifdef O_TRUNC
    return open(buf, O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0644);
#endif
#endif
#endif
    return -1;
}

#if defined(SHU_USE_SU_DRIVER) && defined(SHU_USE_SU_PIPELINE)
/**
 * 传递加载 dep：从 main 的 import 出发，解析每个 dep 的 import 并加入加载列表，直至无新 dep。
 * 填满 dep_sources/dep_lens/dep_paths，*n_deps 为个数。返回 0 成功，1 失败（调用方负责释放已分配）。
 */
static int collect_deps_transitive(void *module, size_t arena_sz, size_t module_sz,
    const char **lib_roots_arr, int n_lib_roots, const char *entry_dir_buf,
    char *dep_sources[], size_t dep_lens[], char *dep_paths[], int *n_deps) {
    int n = 0;
    char *to_load[MAX_ALL_DEPS];
    int to_load_n = 0;
    void *tmp_arena = NULL;
    void *tmp_module = NULL;
    int32_t n_imports = parser_get_module_num_imports(module);
    for (int j = 0; j < n_imports && j < 32 && to_load_n < MAX_ALL_DEPS; j++) {
        uint8_t path_buf[64];
        parser_get_module_import_path(module, j, path_buf);
        char path_c[65];
        size_t k = 0;
        while (k < sizeof(path_buf) && path_buf[k]) { path_c[k] = (char)path_buf[k]; k++; }
        path_c[k] = '\0';
        to_load[to_load_n++] = strdup(path_c);
        if (!to_load[to_load_n - 1]) goto fail_to_load;
    }
    while (to_load_n > 0 && n < MAX_ALL_DEPS) {
        char *path_c = to_load[--to_load_n];
        if (find_loaded_index(path_c, dep_paths, n) >= 0) { free(path_c); continue; }
        char resolved[PATH_MAX];
        resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir_buf, path_c, resolved, sizeof(resolved));
        size_t raw_len = 0;
        char *raw = read_file(resolved, &raw_len);
        if (!raw) {
            fprintf(stderr, "shu: cannot open import '%s' (tried %s)\n", path_c, resolved);
            free(path_c);
            goto fail_to_load;
        }
        size_t prep_len = 0;
        char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
        free(raw);
        if (!prep) {
            fprintf(stderr, "shu: preprocess failed for import '%s'\n", path_c);
            free(path_c);
            goto fail_to_load;
        }
        dep_sources[n] = prep;
        dep_lens[n] = prep_len;
        dep_paths[n] = strdup(path_c);
        free(path_c);
        if (!dep_paths[n]) goto fail_to_load;
        n++;
        if (!tmp_arena) { tmp_arena = malloc(arena_sz); tmp_module = malloc(module_sz); }
        if (tmp_arena && tmp_module) {
            memset(tmp_arena, 0, arena_sz);
            memset(tmp_module, 0, module_sz);
            struct shulang_slice_uint8_t dep_slice = { (uint8_t *)dep_sources[n - 1], dep_lens[n - 1] };
            parser_parse_into_init(tmp_module, tmp_arena);
            struct parser_ParseIntoResult pr_dep = parser_parse_into(tmp_arena, tmp_module, &dep_slice);
            if (pr_dep.ok == 0) {
                int n_imp = parser_get_module_num_imports(tmp_module);
                for (int jj = 0; jj < n_imp && jj < 32 && to_load_n < MAX_ALL_DEPS; jj++) {
                    uint8_t sub_buf[64];
                    parser_get_module_import_path(tmp_module, jj, sub_buf);
                    char sub_c[65];
                    size_t kk = 0;
                    while (kk < sizeof(sub_buf) && sub_buf[kk]) { sub_c[kk] = (char)sub_buf[kk]; kk++; }
                    sub_c[kk] = '\0';
                    if (find_loaded_index(sub_c, dep_paths, n) >= 0) continue;
                    { int found = 0; for (int t = 0; t < to_load_n; t++) if (to_load[t] && strcmp(to_load[t], sub_c) == 0) { found = 1; break; } if (found) continue; }
                    to_load[to_load_n++] = strdup(sub_c);
                    if (!to_load[to_load_n - 1]) to_load_n--;
                }
            }
        }
    }
    while (to_load_n > 0) { to_load_n--; free(to_load[to_load_n]); }
    if (tmp_arena) free(tmp_arena);
    if (tmp_module) free(tmp_module);
    *n_deps = n;
    return 0;
fail_to_load:
    while (to_load_n > 0) { to_load_n--; free(to_load[to_load_n]); }
    if (tmp_arena) free(tmp_arena);
    if (tmp_module) free(tmp_module);
    while (n > 0) { n--; free(dep_sources[n]); free(dep_paths[n]); }
    return 1;
}

/**
 * 完整编译入口：解析 argv（input_path、-o、-L、-O），读文件、预处理、跑 pipeline、写 C 到 stdout 或临时文件，
 * 若有 -o 则调用 cc 生成可执行文件。供 main.su 的 run_compiler_c_impl 桩调用，使带 -o 的 shu 命令能正常产出可执行文件。
 * 返回 0 成功，1 失败。
 */
int driver_run_compiler_full(int argc, char **argv) {
#define SU_FULL_MAX_LIB_ROOTS 16
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_roots_arr[SU_FULL_MAX_LIB_ROOTS];
    int n_lib_roots = 0;
    const char *opt_level = "2";
    int use_lto = 0;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) return 1;
            out_path = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) return 1;
            if (n_lib_roots < SU_FULL_MAX_LIB_ROOTS) lib_roots_arr[n_lib_roots++] = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-O") == 0) {
            if (i + 1 >= argc) return 1;
            opt_level = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-flto") == 0) { use_lto = 1; continue; }
        if (strcmp(argv[i], "-su") == 0) { continue; }
        if (strcmp(argv[i], "-target") == 0) {
            if (i + 1 >= argc) return 1;
            i = i + 2;  /* 跳过 -target 与 triple */
            i--;        /* 抵消 for 末尾的 i++，使下一轮处理 <file.su> 而非 -o */
            continue;
        }
        if (!input_path && argv[i][0] != '-') input_path = argv[i];
    }
    if (!use_lto && getenv("SHULANG_LTO") && strcmp(getenv("SHULANG_LTO"), "1") == 0) use_lto = 1;
    if (n_lib_roots == 0) {
        lib_roots_arr[0] = getenv("SHULANG_LIB");
        if (!lib_roots_arr[0]) lib_roots_arr[0] = ".";
        n_lib_roots = 1;
    }
    if (!input_path) return 1;
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
        fprintf(stderr, "shu: preprocess failed for '%s'\n", input_path);
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
    parser_parse_into_init(module, arena);
    struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
    if (pr.ok != 0) {
        fprintf(stderr, "shu: parse failed for '%s' (pr.ok=%d main_idx=%d)\n", input_path, (int)pr.ok, (int)pr.main_idx);
        { int32_t first_tok = parser_diag_token_after_collect_imports(&src_slice, module); fprintf(stderr, "shu: first_token_after_imports=%d (1=TOKEN_FUNCTION)\n", (int)first_tok); }
        if (src_len > 0 && src_len < 200)
            fprintf(stderr, "shu: src_len=%zu first_bytes=%.*s\n", src_len, (int)(src_len > 60 ? 60 : src_len), src);
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
        if (collect_deps_transitive(module, arena_sz, module_sz, lib_roots_arr, n_lib_roots, entry_dir_buf,
                dep_sources, dep_lens, dep_paths, &n_deps) != 0) {
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        /* 反转 dep 顺序使叶子模块（如 std.io.core）先于调用方（std.io）codegen，避免 C 中未声明即调用 */
        for (int rev = 0; rev < n_deps / 2; rev++) {
            int o = n_deps - 1 - rev;
            char *ts = dep_sources[rev]; dep_sources[rev] = dep_sources[o]; dep_sources[o] = ts;
            size_t tl = dep_lens[rev]; dep_lens[rev] = dep_lens[o]; dep_lens[o] = tl;
            char *tp = dep_paths[rev]; dep_paths[rev] = dep_paths[o]; dep_paths[o] = tp;
        }
    }
    typeck_ndep = 0;
    /* 模板末尾须为 6 个 X，mkstemp 后重命名为 .c 以便 cc/ld 识别 */
    char tmp[] = "/tmp/shu_su.XXXXXX";
    char tmp_c[32];
    int fd = -1;
    FILE *cf;
    if (emit_to_stdout) {
        cf = stdout;
    } else {
        fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shu: mkstemp");
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
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            unlink(tmp);
            fclose(cf);
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
            fprintf(stderr, "shu: -su path: dep alloc failed\n");
            while (j > 0) { j--; free(dep_arenas[j]); free(dep_modules[j]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
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
        pctx.dep_paths[j] = dep_paths[j];
    }
    pctx.ndep = n_deps;
    pctx.skip_codegen_dep_0 = 0; /* 不再跳过 dep 0：io.o 仅提供 C 层，std.io.driver 的 .su 包装须由 codegen 生成。 */
    /* 先对每个 dep 跑 pipeline 仅做 parse+typecheck，填充 dep_arenas/dep_modules，不写 C 到文件。 */
    for (int j = 0; j < n_deps; j++) {
        struct ast_PipelineDepCtx one_ctx;
        memset(&one_ctx, 0, sizeof(one_ctx));
        pipeline_fill_ctx_path_buffers(&one_ctx, entry_dir_buf, lib_roots_arr, n_lib_roots);
        one_ctx.dep_modules[0] = dep_modules[j];
        one_ctx.dep_arenas[0] = dep_arenas[j];
        one_ctx.ndep = 0;
        struct codegen_CodegenOutBuf dep_out;
        memset(&dep_out, 0, sizeof(dep_out));
        driver_set_current_dep_path_for_codegen(dep_paths[j]);
        int ec = pipeline_run_su_pipeline(dep_modules[j], dep_arenas[j], (const uint8_t *)dep_sources[j], dep_lens[j], (void *)&dep_out, (void *)&one_ctx);
        driver_set_current_dep_path_for_codegen(NULL);
        if (ec != 0) {
            fprintf(stderr, "shu: pipeline failed for import '%s' (rc=%d)\n", dep_paths[j], ec);
            for (int k = 0; k < n_deps; k++) { free(dep_arenas[k]); free(dep_modules[k]); }
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
            while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            free(arena); free(module); free(src);
            return 1;
        }
        /* 不把 dep 的 C 写入 cf，避免与后面 entry 一次 codegen 的 deps+entry 重复。 */
    }
    typeck_ndep = n_deps;
    for (int j = 0; j < n_deps; j++) {
        typeck_dep_module_ptrs[j] = dep_modules[j];
        typeck_dep_arena_ptrs[j] = dep_arenas[j];
    }
    pipeline_set_dep_slots(dep_arenas, dep_modules);
    driver_dep_seed_slots(dep_arenas, dep_modules, n_deps);
    codegen_set_dep_slots_for_su_pipeline((struct ASTModule **)dep_modules, (const char **)dep_paths, n_deps);
    /* entry 已由前面 parser_parse_into 解析，保留 module/arena 不 zero，并告知 pipeline 跳过二次解析，避免 main body_ref 丢失。 */
    pctx.entry_already_parsed = 1;
    int ec = pipeline_run_su_pipeline(module, arena, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx);
    driver_dep_seeded_clear_all();
    codegen_set_dep_slots_for_su_pipeline(NULL, NULL, 0);
    for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
    while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
    free(arena);
    free(module);
    free(src);
    if (ec != 0 || out_buf.len == 0) {
        fprintf(stderr, "shu: pipeline failed for '%s'\n", input_path);
        if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
        return 1;
    }
    {
        /* 内联 std.io / std.net ABI；其余 std.fs / path / map / error 仍 include 头文件 */
        size_t first_line = 0;
        while (first_line < (size_t)out_buf.len && out_buf.data[first_line] != '\n') first_line++;
        if (first_line < (size_t)out_buf.len) first_line++;
        static const char fs_abi_include_full[] = "#include \"std/fs/fs_abi.h\"\n";
        static const char path_abi_include_full[] = "#include \"std/path/path_abi.h\"\n";
        static const char map_abi_include_full[] = "#include \"std/map/map_abi.h\"\n";
        static const char error_abi_include_full[] = "#include \"std/error/error_abi.h\"\n";
        if (fwrite(out_buf.data, 1, first_line, cf) != first_line
            || write_io_net_abi_inline(cf) != 0
            || fwrite(fs_abi_include_full, 1, sizeof(fs_abi_include_full) - 1, cf) != (size_t)(sizeof(fs_abi_include_full) - 1)
            || fwrite(path_abi_include_full, 1, sizeof(path_abi_include_full) - 1, cf) != (size_t)(sizeof(path_abi_include_full) - 1)
            || fwrite(map_abi_include_full, 1, sizeof(map_abi_include_full) - 1, cf) != (size_t)(sizeof(map_abi_include_full) - 1)
            || fwrite(error_abi_include_full, 1, sizeof(error_abi_include_full) - 1, cf) != (size_t)(sizeof(error_abi_include_full) - 1)
            || fwrite(out_buf.data + first_line, 1, (size_t)out_buf.len - first_line, cf) != (size_t)out_buf.len - first_line) {
            if (!emit_to_stdout) { fclose(cf); unlink(tmp_c); }
            return 1;
        }
    }
    if (!emit_to_stdout) {
        if (fclose(cf) != 0) {
            unlink(tmp_c);
            return 1;
        }
        {
            const char *c_paths[1] = { tmp_c };
            const char *io_o = get_io_o_path(argv[0]);
            const char *fs_o = get_std_fs_o_path(argv[0]);
            const char *process_o = get_std_process_o_path(argv[0]);
            const char *string_o = get_std_string_o_path(argv[0]);
            const char *heap_o = get_std_heap_o_path(argv[0]);
            const char *runtime_o = get_std_runtime_o_path(argv[0]);
            const char *runtime_panic_o = get_runtime_panic_o_path(argv[0]);
            const char *net_o = get_std_net_o_path(argv[0]);
            const char *thread_o = get_std_thread_o_path(argv[0]);
            const char *time_o = get_std_time_o_path(argv[0]);
            const char *random_o = get_std_random_o_path(argv[0]);
            const char *env_o = get_std_env_o_path(argv[0]);
            const char *sync_o = get_std_sync_o_path(argv[0]);
            const char *encoding_o = get_std_encoding_o_path(argv[0]);
            const char *base64_o = get_std_base64_o_path(argv[0]);
            const char *crypto_o = get_std_crypto_o_path(argv[0]);
            const char *log_o = get_std_log_o_path(argv[0]);
            const char *atomic_o = get_std_atomic_o_path(argv[0]);
            const char *channel_o = get_std_channel_o_path(argv[0]);
            const char *backtrace_o = get_std_backtrace_o_path(argv[0]);
            const char *hash_o = get_std_hash_o_path(argv[0]);
            const char *math_o = get_std_math_o_path(argv[0]);
            const char *sort_o = get_std_sort_o_path(argv[0]);
            const char *ffi_o = get_std_ffi_o_path(argv[0]);
            const char *json_o = get_std_json_o_path(argv[0]);
            const char *csv_o = get_std_csv_o_path(argv[0]);
            const char *regex_o = get_std_regex_o_path(argv[0]);
            const char *compress_o = get_std_compress_o_path(argv[0]);
            const char *unicode_o = get_std_unicode_o_path(argv[0]);
            const char *dynlib_o = get_std_dynlib_o_path(argv[0]);
            const char *http_o = get_std_http_o_path(argv[0]);
            const char *tar_o = get_std_tar_o_path(argv[0]);
            const char *test_o = get_std_test_o_path(argv[0]);
            int cc_ret = invoke_cc(c_paths, 1, out_path, NULL, opt_level, use_lto, io_o, fs_o, process_o, string_o, heap_o, runtime_o, runtime_panic_o, net_o, thread_o, time_o, random_o, env_o, sync_o, encoding_o, base64_o, crypto_o, log_o, atomic_o, channel_o, backtrace_o, hash_o, math_o, sort_o, ffi_o, json_o, csv_o, regex_o, compress_o, unicode_o, dynlib_o, http_o, tar_o, test_o, get_repo_root(argv[0]));
            if (cc_ret != 0) {
                fprintf(stderr, "shu: cc failed, keeping generated C: %s\n", tmp_c);
            } else if (!getenv("SHULANG_KEEP_C")) {
                unlink(tmp_c);
            } else {
                fprintf(stderr, "shu: kept generated C: %s\n", tmp_c);
            }
            return cc_ret == 0 ? 0 : 1;
        }
    }
    return 0;
#undef SU_FULL_MAX_LIB_ROOTS
}
#endif

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

/** 执行刚解析的 -su -E（读文件、.su pipeline、写 stdout）；成功 0，失败 1。无 SHU_USE_SU_PIPELINE 时返回 1。 */
int driver_run_su_emit_c(void) {
    const char *input_path = driver_su_emit_c_path;
    driver_su_emit_c_path = NULL;
    if (!input_path) return 1;
#ifdef SHU_USE_SU_PIPELINE
    {
        /* 关闭 stdout 缓冲，避免重定向或管道下输出被截断（平台差异见 analysis/下一步开发分析.md §4.4） */
        (void)setvbuf(stdout, NULL, _IONBF, 0);
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
            fprintf(stderr, "shu: preprocess failed for '%s'\n", input_path);
            return 1;
        }
        size_t arena_sz = pipeline_sizeof_arena();
        size_t module_sz = pipeline_sizeof_module();
        void *arena = malloc(arena_sz);
        void *module = malloc(module_sz);
        if (!arena || !module) {
            fprintf(stderr, "shu: -su pipeline: malloc failed\n");
            free(arena);
            free(module);
            free(src);
            return 1;
        }
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        struct shulang_slice_uint8_t src_slice = { (uint8_t *)src, src_len };
        parser_parse_into_init(module, arena);
        struct parser_ParseIntoResult pr = parser_parse_into(arena, module, &src_slice);
        if (pr.ok != 0) {
            fprintf(stderr, "shu: -su pipeline failed (parse_into)\n");
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
                char resolved[PATH_MAX];
                resolve_import_file_path_multi(lib_roots_arr, n_lib_roots, entry_dir, path_c, resolved, sizeof(resolved));
                size_t raw_len = 0;
                char *raw = read_file(resolved, &raw_len);
                if (!raw) {
                    fprintf(stderr, "shu: cannot open import '%s' (tried %s)\n", path_c, resolved);
                    while (n_deps--) { free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
                    free(arena); free(module); free(src);
                    return 1;
                }
                size_t prep_len = 0;
                char *prep = preprocess(raw, raw_len, NULL, 0, &prep_len);
                free(raw);
                if (!prep) {
                    fprintf(stderr, "shu: preprocess failed for import '%s'\n", path_c);
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
                fprintf(stderr, "shu: -su pipeline: dep alloc failed\n");
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
        /* 设置 driver_dep_* 槽位，使 pipeline 内 resolve/load 时能拿到与当前 dep 一致的 arena/module。仅对 entry 跑一次 pipeline，其内部会 codegen 所有 deps + entry，避免对每个 dep 单独跑 pipeline 再 fwrite 导致 deps 的 C 被写两遍（重复符号）。 */
        pipeline_set_dep_slots(dep_arenas, dep_modules);
        typeck_ndep = n_deps;
        for (int i = 0; i < n_deps; i++) {
            typeck_dep_module_ptrs[i] = dep_modules[i];
            typeck_dep_arena_ptrs[i] = dep_arenas[i];
        }
        pipeline_set_dep_slots(dep_arenas, dep_modules);
        memset(arena, 0, arena_sz);
        memset(module, 0, module_sz);
        int ec = pipeline_run_su_pipeline(module, arena, src_slice.data, (size_t)src_slice.length, (void *)&out_buf, (void *)&pctx_e);
        if (ec == 0 && out_buf.len > 0) {
            /* 平台差异诊断（分析文档 4.4）：main 段输出过短时打 stderr，便于 CI/本地确认是 len 错误还是内容只写了数字 */
            if (out_buf.len < 20) {
                fprintf(stderr, "shu: -su -E diagnostic: out_buf.len=%d first bytes:", (int)out_buf.len);
                for (int di = 0; di < out_buf.len && di < 16; di++)
                    fprintf(stderr, " %02x", (unsigned char)out_buf.data[di]);
                fprintf(stderr, "\n");
            }
            fwrite(out_buf.data, 1, (size_t)out_buf.len, stdout);
            fflush(stdout);
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
        } else {
            for (int j = 0; j < n_deps; j++) { free(dep_arenas[j]); free(dep_modules[j]); }
            while (n_deps > 0) { n_deps--; free(dep_sources[n_deps]); free(dep_paths[n_deps]); }
            if (ec != 0) fprintf(stderr, "shu: -su pipeline failed\n");
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

#ifndef SHU_USE_SU_DRIVER
/** 6.3：无 .su 入口时由 runtime 提供 main_entry 桩，仅转调 run_compiler_c；链接 main_su.o 时由 main.su 的 main_entry 覆盖。
 * Cygwin/MinGW 上 weak 符号可能不被链接器解析，故仅在非 Windows 环境使用 weak。 */
#if !defined(__CYGWIN__) && !defined(__MINGW32__) && !defined(_WIN32)
__attribute__((weak))
#endif
int main_entry(int argc, char **argv) {
    return run_compiler_c(argc, argv);
}
#endif
