/* seeds/rt_preamble.from_x.c — G-02f-265 P2 R3 preamble ABI 内联
 * Logic source: src/runtime/rt_preamble.x
 * Hybrid: XLANG_RT_PREAMBLE_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full（2026-07-14）：write_io_net / write_fs_path_map_error 由 .x 提供；
 * FROM_X 下本文件：巨型字符串表（Cap-giant-string residual 数据）+ 前向声明 + marker
 * （产品 rest 业务 T=0）。冷启动/无 PREFER 时仍编译完整 C 体。
 * Cap residual 行访问 API 在 runtime_driver_abi（平台层，供 .x 取表）。
 * wave29：io_net n=224；WEAK_IO_BATCH skip i=178..181（与 rt_preamble.x / surface 同权威）。
 */
#include <xlang_weak.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
/* Cap residual 9.7.1: inline ABI writers take the opaque fd-handle stream. */
#include "xlang_driver_stream_cap.h"

#ifndef CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS
#define CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS    1u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_DRIVER_HANDLE  2u
#define CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE 4u
#define CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH         8u
#endif

extern unsigned codegen_get_preamble_skip_mask(void);

/* Cap-giant-string residual 数据：巨型 C 字面量表始终非 static 跨 TU
 * （.x 禁巨型字串表；driver_abi 经 line_at/count 暴露给 .x）。 */
const char *const driver_preamble_io_net_lines[] = {
        "#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L\n#error \"Generated code needs C11. Compile with -std=gnu11 or -std=c11.\"\n#endif\n",
        "#include <stddef.h>\n",
        /* Cap 10.7.1 slice10: fold Cap va header into existing slot (do NOT add a
         * new array row — fixed N=224 skip ranges). Mirrors -E emit_header.
         * PLATFORM: SHARED host-C product -o preamble. */
        "#include <stdint.h>\n#include <xlang_va_cap.h>\n",
        /* PLATFORM: SHARED — host libc prototypes for skip-list symbols
         * (codegen_is_libc_conflicting_extern_name: malloc/free/calloc/realloc/
         * getenv/memcpy/memchr/strtoul/...). XLANG *u8 emits as uint8_t * and
         * clashes with char * / void * in system headers; we skip redecl and
         * rely on these includes. Without them, skipped names become implicit
         * int (heap return malloc -> int-to-pointer).
         * Do NOT include dirent.h: std.fs models DIR* as *u8 opaque; system
         * DIR* prototypes conflict. opendir/closedir are not on the skip list. */
        "#include <stdlib.h>\n",
        "#include <string.h>\n",
        "#if !defined(_WIN32) && !defined(_WIN64)\n#include <unistd.h>\n#else\n#include <io.h>\n#include <sys/types.h>\n#endif\n",
        "#if !defined(_WIN32) && !defined(_WIN64)\n#include <sys/uio.h>\n#endif\n",
        "#if !defined(_WIN32) && !defined(_WIN64)\n#include <poll.h>\n#endif\n",
        /*
         * PLATFORM: POSIX — product -o co-emit of std.fs.posix uses bare O_*, S_IF*,
         * PROT_*, MAP_*, FS_IOV_BUF_MAX, DIRENT_D_NAME_OFF and bare fs_libc_open, plus
         * Darwin __error / Linux __errno_location / fcntl / madvise without prototypes.
         * Do NOT include sys/stat.h or sys/mman.h: they macro-expand st_atime etc. and
         * conflict with Xlang PosixStatBuf / extern open,stat,mmap prototypes (host-cc red).
         * Values match std/fs/posix.x export const (Linux + Darwin shared where equal).
         */
        "#ifndef O_RDONLY\n#define O_RDONLY 0\n#endif\n"
        "#ifndef O_WRONLY\n#define O_WRONLY 1\n#endif\n"
        "#ifndef O_RDWR\n#define O_RDWR 2\n#endif\n"
        "#if defined(__APPLE__)\n"
        "#ifndef O_CREAT\n#define O_CREAT 512\n#endif\n"
        "#ifndef O_TRUNC\n#define O_TRUNC 1024\n#endif\n"
        "#ifndef O_APPEND\n#define O_APPEND 8\n#endif\n"
        "#ifndef F_NOCACHE\n#define F_NOCACHE 48\n#endif\n"
        "#else\n"
        "#ifndef O_CREAT\n#define O_CREAT 64\n#endif\n"
        "#ifndef O_TRUNC\n#define O_TRUNC 512\n#endif\n"
        "#ifndef O_APPEND\n#define O_APPEND 1024\n#endif\n"
        "#endif\n"
        "#ifndef PROT_READ\n#define PROT_READ 1\n#endif\n"
        "#ifndef PROT_WRITE\n#define PROT_WRITE 2\n#endif\n"
        "#ifndef MAP_SHARED\n#define MAP_SHARED 1\n#endif\n"
        "#ifndef MAP_PRIVATE\n#define MAP_PRIVATE 2\n#endif\n"
        "#ifndef MAP_FAILED\n#define MAP_FAILED ((int64_t)-1)\n#endif\n"
        "#ifndef S_IFMT\n#define S_IFMT 61440u\n#endif\n"
        "#ifndef S_IFDIR\n#define S_IFDIR 16384u\n#endif\n"
        "#ifndef S_IFREG\n#define S_IFREG 32768u\n#endif\n"
        "#ifndef FS_IOV_BUF_MAX\n#define FS_IOV_BUF_MAX 16\n#endif\n"
        "#ifndef DIRENT_D_NAME_OFF\n"
        "#if defined(__APPLE__)\n#define DIRENT_D_NAME_OFF ((size_t)21)\n"
        "#else\n#define DIRENT_D_NAME_OFF ((size_t)19)\n#endif\n"
        "#endif\n"
        /* PLATFORM: POSIX — MinGW io.h already declares `int open(const char*, int, ...)`
         * which conflicts with our `extern int32_t open(uint8_t*, int32_t, int32_t)`. MinGW
         * also lacks fcntl/madvise/__error/__errno_location. Gate the whole POSIX extern
         * block (plus fs_libc_open wrapper + fs_note_last_error_posix alias macro) behind
         * _WIN32. Windows std.fs layer uses native Win32 APIs (CreateFile/ReadFile). */
        "#if !defined(_WIN32) && !defined(_WIN64)\n"
        "#if defined(__APPLE__)\nextern int *__error(void);\n"
        "#else\nextern int *__errno_location(void);\n#endif\n"
        "extern int32_t fcntl(int32_t fd, int32_t cmd, int32_t arg);\n"
        "extern int32_t madvise(uint8_t *addr, size_t len, int32_t advice);\n"
        "extern int32_t open(uint8_t *path, int32_t flags, int32_t mode);\n"
        "static inline int32_t fs_libc_open(uint8_t *path, int32_t flags, int32_t mode) {\n"
        "  return open(path, flags, mode);\n"
        "}\n"
        "#define fs_note_last_error_posix std_fs_posix_fs_note_last_error_posix\n"
        "#endif\n",
        /* Cap residual 9.1.8: read/write/writev via xlang_io_cap.h (no libc write).
         * Generated user C needs -I…/compiler/include (Cap 10.7.1 slice11: invoke_cc second -I).
         * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS | POSIX). */
        "#include <xlang_io_cap.h>\n"
        "static inline ssize_t xlang_sys_read(int32_t fd, uint8_t *buf, size_t count) {\n"
        "  return (ssize_t)xlang_io_read((int)fd, (void *)buf, count);\n"
        "}\n"
        "static inline ssize_t xlang_sys_write(int32_t fd, uint8_t *buf, size_t count) {\n"
        "  return (ssize_t)xlang_io_write((int)fd, (const void *)buf, count);\n"
        "}\n",
        /* PLATFORM: POSIX — MinGW lacks readv/poll/pread/pwrite and the types
         * struct pollfd, nfds_t. Gate each inline behind _WIN32.
         * Cap residual 9.1.8: writev via xlang_io_cap.h on all platforms. */
        "#if !defined(_WIN32) && !defined(_WIN64)\n"
        "static inline ssize_t xlang_sys_readv(int32_t fd, uint8_t *iov, int32_t iovcnt) {\n"
        "  return readv((int)fd, (const struct iovec *)(const void *)iov, (int)iovcnt);\n"
        "}\n"
        "#endif\n",
        "static inline ssize_t xlang_sys_writev(int32_t fd, uint8_t *iov, int32_t iovcnt) {\n"
        "  return (ssize_t)xlang_io_writev((int)fd, (const void *)iov, (int)iovcnt);\n"
        "}\n",
        /* Cap residual 9.1.7/9.1.9: poll via xlang_net_cap.h (no libc poll).
         * Co-emit into std.net must not leave U poll (net.o residual). */
        "#if !defined(_WIN32) && !defined(_WIN64)\n"
        "#include <xlang_net_cap.h>\n"
        "static inline int32_t xlang_sys_poll(uint8_t *fds, int32_t nfds, int32_t timeout) {\n"
        "  return (int32_t)xlang_net_poll((void *)fds, (unsigned int)nfds, (int)timeout);\n"
        "}\n"
        "#endif\n",
        "#if !defined(_WIN32) && !defined(_WIN64)\n"
        "static inline ssize_t xlang_sys_pread(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {\n"
        "  return pread((int)fd, (void *)buf, count, (off_t)offset);\n"
        "}\n"
        "#endif\n",
        "#if !defined(_WIN32) && !defined(_WIN64)\n"
        "static inline ssize_t xlang_sys_pwrite(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {\n"
        "  return pwrite((int)fd, (const void *)buf, count, (off_t)offset);\n"
        "}\n"
        "#endif\n",
        "static inline int32_t xlang_fs_unlink(uint8_t *path) {\n"
        "  return (int32_t)unlink((const char *)path);\n"
        "}\n",
        "static inline int32_t xlang_fs_rmdir(uint8_t *path) {\n"
        "  return (int32_t)rmdir((const char *)path);\n"
        "}\n",
        /* PLATFORM: SHARED — host-C TYPE_SLICE fat layouts. Tags = type_to_c_repr
         * (struct xlang_slice_ + elem C name from type_kind_cstr / NAMED stdint map).
         * wave618: float/double. wave619: complete scalar set (bool/int, u32, i64,
         * isize/ssize_t, NAMED i8/i16/u16 → int8_t/int16_t/uint16_t). Incomplete
         * tag → host-cc BLD001 "incomplete type struct xlang_slice_*".
         * wave623: XLANG_SLICE_LAYOUTS guard — bare `-E` also emits the same layouts
         * via codegen_x_ast_emit_header; full `-o` writes this table first then
         * header, so both must share the guard (G.7 single layout authority).
         * wave691: one-level nested [][]T → struct xlang_slice_xlang_slice_<elem>
         * { struct xlang_slice_<elem> *data; size_t length; } (type_to_c_repr nest).
         * wave693: two-level nested [][][]T → struct xlang_slice_xlang_slice_xlang_slice_<elem>
         * { struct xlang_slice_xlang_slice_<elem> *data; size_t length; }.
         * wave694: three-level nested [][][][]T → struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_<elem>
         * { struct xlang_slice_xlang_slice_xlang_slice_<elem> *data; size_t length; }.
         * wave695: four-level nested [][][][][]T → struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_<elem>
         * { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_<elem> *data; size_t length; }.
         * wave696: five-level nested [][][][][][]T → struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_<elem>
         * { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_<elem> *data; size_t length; }.
         * wave697: six-level nested [][][][][][][]T → struct xlang_slice×7 + elem
         * { struct xlang_slice×6 + elem *data; size_t length; }.
         * wave698: seven-level nested [][][][][][][][]T → struct xlang_slice×8 + elem
         * { struct xlang_slice×7 + elem *data; size_t length; }. */
        /* TYPE_DYN fat layout — ≡ codegen emit_header. PLATFORM: SHARED. */
        "#ifndef XLANG_DYN_OBJ\n"
        "#define XLANG_DYN_OBJ\n"
        "struct xlang_dyn_obj { void *data; void *vtable; };\n"
        "#endif\n"
        "#ifndef XLANG_SLICE_LAYOUTS\n"
        "#define XLANG_SLICE_LAYOUTS\n"
        "struct xlang_slice_uint8_t { uint8_t *data; size_t length; };\n"
        "struct xlang_slice_int8_t { int8_t *data; size_t length; };\n"
        "struct xlang_slice_int16_t { int16_t *data; size_t length; };\n"
        "struct xlang_slice_uint16_t { uint16_t *data; size_t length; };\n"
        "struct xlang_slice_int { int *data; size_t length; };\n"
        "struct xlang_slice_int32_t { int32_t *data; size_t length; };\n"
        "struct xlang_slice_uint32_t { uint32_t *data; size_t length; };\n"
        "struct xlang_slice_int64_t { int64_t *data; size_t length; };\n"
        "struct xlang_slice_uint64_t { uint64_t *data; size_t length; };\n"
        "struct xlang_slice_size_t { size_t *data; size_t length; };\n"
        "struct xlang_slice_ssize_t { ssize_t *data; size_t length; };\n"
        "struct xlang_slice_float { float *data; size_t length; };\n"
        "struct xlang_slice_double { double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_uint8_t { struct xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_int8_t { struct xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_int16_t { struct xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_uint16_t { struct xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_int { struct xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_int32_t { struct xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_uint32_t { struct xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_int64_t { struct xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_uint64_t { struct xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_size_t { struct xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_ssize_t { struct xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_float { struct xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_double { struct xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };\n"
        "struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };\n"
        "#endif\n"
        /* §10 向量：codegen 发 i32x4_t / f32x4_t 等；与 emit_vector_c_type_out +
         * pipeline_codegen_vector_type_cstr 对齐。f32x{4,8,16} 供 Vec4f 等 F32 向量使用。
         * PLATFORM: SHARED — XLANG_VECTOR_TYPES shares the set with
         * codegen_x_ast_emit_header (bare -E). Folded into existing slots;
         * do not add rows (N=224 skip ranges). */
        "#ifndef XLANG_VECTOR_TYPES\n#define XLANG_VECTOR_TYPES\n#if defined(__GNUC__) || defined(__clang__)\n"
        "typedef int32_t i32x4_t __attribute__((vector_size(16)));\n"
        "typedef int32_t i32x8_t __attribute__((vector_size(32)));\n"
        "typedef int32_t i32x16_t __attribute__((vector_size(64)));\n"
        "typedef uint32_t u32x4_t __attribute__((vector_size(16)));\n"
        "typedef uint32_t u32x8_t __attribute__((vector_size(32)));\n"
        "typedef uint32_t u32x16_t __attribute__((vector_size(64)));\n"
        "typedef float f32x4_t __attribute__((vector_size(16)));\n"
        "typedef float f32x8_t __attribute__((vector_size(32)));\n"
        "typedef float f32x16_t __attribute__((vector_size(64)));\n"
        "#else\n"
        "typedef struct { int32_t e[4]; } i32x4_t;\n"
        "typedef struct { int32_t e[8]; } i32x8_t;\n"
        "typedef struct { int32_t e[16]; } i32x16_t;\n"
        "typedef struct { uint32_t e[4]; } u32x4_t;\n"
        "typedef struct { uint32_t e[8]; } u32x8_t;\n"
        "typedef struct { uint32_t e[16]; } u32x16_t;\n"
        "typedef struct { float e[4]; } f32x4_t;\n"
        "typedef struct { float e[8]; } f32x8_t;\n"
        "typedef struct { float e[16]; } f32x16_t;\n"
        "#endif\n#endif\n"
        "typedef struct { uint8_t *ptr; size_t length; size_t handle; } xlang_batch_buf_t;\n",
        "extern int io_register_buffer(uint8_t *ptr, size_t len);\n",
        "extern int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr);\n",
        "__attribute__((weak)) int io_register_buffers_buf_c(const xlang_batch_buf_t *bufs, int nr) { (void)bufs; (void)nr; return -1; }\n",
        "static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const xlang_batch_buf_t *)(uintptr_t)bufs, nr); }\n",
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
        "extern int32_t xlang_io_register(uint8_t *ptr, size_t len, size_t handle);\n",
        "extern int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n",
        "extern int32_t xlang_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);\n",
        "extern int32_t xlang_io_read_fixed(size_t handle, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_m);\n",
        "extern int32_t xlang_io_write_fixed(size_t handle, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_m);\n",
        "extern uint8_t *xlang_io_read_ptr(size_t handle, unsigned timeout_ms);\n",
        "extern int32_t xlang_io_read_ptr_len(void);\n",
        "typedef struct { void *ptr; size_t length; size_t handle; } xlang_buffer_abi_t;\n",
        "static inline int32_t xlang_io_register_buf(intptr_t buf) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return xlang_io_register((uint8_t *)b->ptr, b->length, b->handle); }\n",
        "static inline int32_t xlang_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return (xlang_io_submit_read)((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }\n",
        "static inline int32_t xlang_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return (xlang_io_submit_write)((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }\n",
        /* 勿定义 std_io_driver_submit_read/write 同名 inline（与 co-emit Buffer 形参冲突）。 */
        "static inline int32_t std_io_driver_submit_read_via_ptr(ptrdiff_t buf, uint32_t timeout_ms) { return xlang_io_submit_read_buf((intptr_t)buf, (int32_t)timeout_ms); }\n",
        "static inline int32_t std_io_driver_submit_write_via_ptr(ptrdiff_t buf, uint32_t timeout_ms) { return xlang_io_submit_write_buf((intptr_t)buf, (int32_t)timeout_ms); }\n",
        "#define xlang_io_register(buf) xlang_io_register_buf(buf)\n",
        "#define xlang_io_submit_read(buf, timeout_m) xlang_io_submit_read_buf(buf, timeout_m)\n",
        "#define xlang_io_submit_write(buf, timeout_m) xlang_io_submit_write_buf(buf, timeout_m)\n",
        "/* 撤销宏：X codegen 会生成同名函数定义(xlang_io_register/submit_read/submit_write)，宏与多参签名冲突，在函数体前必须 undef。 */\n",
        "#undef xlang_io_register\n",
        "#undef xlang_io_submit_read\n",
        "#undef xlang_io_submit_write\n",
        "struct std_io_driver_Buffer { void *ptr; size_t length; size_t handle; };\n",
        "typedef struct std_io_driver_Buffer std_io_Buffer;\n",
        "#define std_io_Buffer std_io_driver_Buffer\n",
        "extern ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);\n",
        "extern ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);\n",
        "extern int32_t std_io_driver_submit_register_fixed_buffers_buf(struct std_io_driver_Buffer * bufs, uint32_t nr);\n",
        "#define std_io_driver_driver_read_ptr_len xlang_io_read_ptr_len\n",
        "#define std_io_driver_driver_read_ptr xlang_io_read_ptr\n",
        "#define driver_read_ptr_len std_io_driver_driver_read_ptr_len\n",
        "#define driver_read_ptr std_io_driver_driver_read_ptr\n",
        "#define submit_register_fixed_buffers_buf std_io_driver_submit_register_fixed_buffers_buf\n",
        "/* 短名 submit_read/write → via_ptr；全名 std_io_driver_submit_* 由 co-emit 定义。 */\n",
        "#define submit_read(buf, timeout_ms) std_io_driver_submit_read_via_ptr((ptrdiff_t)(uintptr_t)&(buf), (timeout_ms))\n",
        "#define submit_write(buf, timeout_ms) std_io_driver_submit_write_via_ptr((ptrdiff_t)(uintptr_t)&(buf), (timeout_ms))\n",
        "#define std_io_driver_read_ptr driver_read_ptr\n",
        "#define std_io_driver_read_ptr_len driver_read_ptr_len\n",
        "extern size_t std_io_handle_stdin(void);\n",
        "extern size_t std_io_handle_stdout(void);\n",
        "extern size_t std_io_handle_stderr(void);\n",
        "extern size_t std_io_handle_from_fd(int32_t fd, int32_t unused);\n",
        "extern size_t std_io_driver_handle_from_fd(int32_t fd, int32_t unused);\n",
        "extern int32_t std_io_write_stdout(uint8_t *ptr, size_t len);\n",
        "#define std_io_driver_handle_stdin std_io_handle_stdin\n",
        "#define std_io_driver_handle_stdout std_io_handle_stdout\n",
        "#define std_io_driver_handle_stderr std_io_handle_stderr\n",
        "#define std_io_driver_write_stdout std_io_write_stdout\n",
        "/* std.io.core 体内调 extern io_*；codegen 前缀为 std_io_core_io_*，映射到 preamble 已声明的 io_*。 */\n",
        "#define std_io_core_io_read io_read\n",
        "#define std_io_core_io_write io_write\n",
        "#define std_io_core_io_read_batch io_read_batch\n",
        "#define std_io_core_io_write_batch io_write_batch\n",
        "#define std_io_core_io_read_fixed io_read_fixed\n",
        "#define std_io_core_io_write_fixed io_write_fixed\n",
        "#define std_io_core_xlang_io_register xlang_io_register\n",
        "#define std_io_core_xlang_io_register_buffers xlang_io_register_buffers\n",
        "#define std_io_core_xlang_io_unregister_buffers xlang_io_unregister_buffers\n",
        "#define std_io_core_xlang_io_submit_read xlang_io_submit_read\n",
        "#define std_io_core_xlang_io_read_ptr xlang_io_read_ptr\n",
        "#define std_io_core_xlang_io_read_ptr_len xlang_io_read_ptr_len\n",
        "#define std_io_core_xlang_io_submit_write xlang_io_submit_write\n",
        "#define std_io_core_xlang_io_submit_read_batch xlang_io_submit_read_batch\n",
        "#define std_io_core_xlang_io_submit_write_batch xlang_io_submit_write_batch\n",
        "#define std_io_core_xlang_io_read_fixed xlang_io_read_fixed\n",
        "#define std_io_core_xlang_io_write_fixed xlang_io_write_fixed\n",
        /* driver → core 前缀调用：core 未 co-emit 时映到 runtime / 平台符号（与 io.o / backend 一致）。 */
        "#define std_io_core_xlang_io_register_buffers_buf io_register_buffers_buf\n",
        "#define std_io_core_xlang_io_read_ptr_gen xlang_io_read_ptr_gen\n",
        "#define std_io_core_xlang_io_read_ptr_gen_valid xlang_io_read_ptr_gen_valid\n",
        "#define std_io_core_xlang_io_read_ptr_backend xlang_io_read_ptr_backend\n",
        "#define std_io_core_xlang_io_read_ptr_slice xlang_io_read_ptr_slice\n",
        "#define std_io_core_xlang_io_read_batch_buf(fd, bufs, n, t) io_read_batch_buf((fd), (const struct std_io_driver_Buffer *)(const void *)(bufs), (n), (t))\n",
        "#define std_io_core_xlang_io_write_batch_buf(fd, bufs, n, t) io_write_batch_buf((fd), (const struct std_io_driver_Buffer *)(const void *)(bufs), (n), (t))\n",
        "#define std_io_core_xlang_io_register_provided_buffers xlang_io_register_provided_buffers\n",
        /* Cap co-emit of std.io wrappers calls these names; map to runtime/io.o symbols. */
        "#define std_io_core_xlang_io_unregister_provided_buffers xlang_io_unregister_provided_buffers\n",
        "#define std_io_core_xlang_io_provided_buffer_ptr xlang_io_provided_buffer_ptr\n",
        "#define std_io_core_xlang_io_provided_buffer_size xlang_io_provided_buffer_size\n",
        "#define std_io_core_xlang_io_read_provided xlang_io_read_provided\n",
        "#define std_io_core_xlang_io_read_batch_provided xlang_io_read_batch_provided\n",
        "#define std_io_core_xlang_io_submit_read_async xlang_io_submit_read_async\n",
        "#define std_io_core_xlang_io_complete_read_async xlang_io_complete_read_async\n",
        "#define std_io_core_xlang_io_complete_read_async_slot xlang_io_complete_read_async_slot\n",
        "#define std_io_core_xlang_io_submit_write_async xlang_io_submit_write_async\n",
        "#define std_io_core_xlang_io_complete_write_async xlang_io_complete_write_async\n",
        "#define std_io_core_xlang_io_complete_write_async_slot xlang_io_complete_write_async_slot\n",
        "#define std_io_core_xlang_io_poll_async_completions xlang_io_poll_async_completions\n",
        "#define std_io_core_xlang_io_uring_is_available_c xlang_io_uring_is_available_c\n",
        "extern int32_t xlang_io_read_ptr_gen_valid(uint64_t saved);\n",
        "extern int32_t xlang_io_read_ptr_backend(void);\n",
        "extern uint64_t xlang_io_read_ptr_gen(void);\n",
        "extern struct xlang_slice_uint8_t xlang_io_read_ptr_slice(size_t handle, uint32_t timeout_ms);\n",
        "extern int32_t xlang_io_register_provided_buffers(uint32_t nr, uint32_t bufsz);\n",
        "extern void xlang_io_unregister_provided_buffers(void);\n",
        "extern uint8_t *xlang_io_provided_buffer_ptr(uint32_t bid);\n",
        "extern uint32_t xlang_io_provided_buffer_size(void);\n",
        "extern int32_t xlang_io_read_provided(size_t handle, uint32_t timeout_ms, uint32_t *out_bid, uint32_t *out_len);\n",
        "extern int32_t xlang_io_read_batch_provided(size_t handle, int32_t n, uint32_t timeout_ms, uint32_t *out_bids, uint32_t *out_lens);\n",
        "extern int32_t xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle);\n",
        "extern int32_t xlang_io_complete_read_async(void);\n",
        "extern int32_t xlang_io_complete_read_async_slot(int32_t slot);\n",
        "extern int32_t xlang_io_submit_write_async(uint8_t *ptr, size_t len, size_t handle);\n",
        "extern int32_t xlang_io_complete_write_async(void);\n",
        "extern int32_t xlang_io_complete_write_async_slot(int32_t slot);\n",
        "extern uint32_t xlang_io_poll_async_completions(uint32_t timeout_ms);\n",
        "extern int32_t xlang_io_uring_is_available_c(void);\n",
        "#define std_io_driver_io_register_buffers_buf(bufs, nr) io_register_buffers_buf((intptr_t)(void *)(bufs), (int)(nr))\n",
        "extern int32_t std_io_driver_submit_read_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);\n",
        "extern int32_t std_io_driver_submit_write_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);\n",
        "#define std_io_submit_read_batch_buf std_io_driver_submit_read_batch_buf\n",
        "#define std_io_submit_write_batch_buf std_io_driver_submit_write_batch_buf\n",
        "extern int32_t std_io_read_fixed_fd_impl(int32_t fd, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_ms);\n",
        "extern int32_t std_io_write_fixed_fd_impl(int32_t fd, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_ms);\n",
        "/* X 生成代码可能调用 std_io_* / std_net_* 带前缀名且首参为 stream/listener 结构体；以下宏统一转为 .fd 再调 _impl。C 路径下 std.io 仍定义 std_io_read_fixed_fd，故仅 X 需宏。 */\n",
        "struct std_net_TcpStream { int32_t fd; };\n",
        "struct std_net_TcpListener { int32_t fd; };\n",
        "struct std_net_UdpSocket { int32_t fd; };\n",
        "#if defined(__clang__)\n",
        "#define xlang_io_net_fd(x) _Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (int32_t)(x))\n",
        "#elif defined(__GNUC__)\n",
        "/* 仅用 *(int32_t*)&(x)：int32_t 与仅含 .fd 的 struct 首字节相同，且避免 __builtin_types_compatible_p 在部分环境报错、三元分支被全量类型检查。调用方须传 lvalue。 */\n",
        "#define xlang_io_net_fd(x) (*(int32_t*)(void*)&(x))\n",
        "#else\n",
        "#define xlang_io_net_fd(x) _Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (int32_t)(x))\n",
        "#endif\n",
        "#define std_io_read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n",
        "#define std_io_write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n",
        "/* X 内联 std.io 会生成函数定义；撤销与定义/extern 冲突的宏，并补齐 batch 注册符号映射。 */\n",
        "#undef std_io_driver_io_register_buffers_buf\n",
        "#undef std_io_read_fixed_fd\n",
        "#undef std_io_write_fixed_fd\n",
        "#undef std_io_core_xlang_io_register_buffers\n",
        "#undef std_io_core_xlang_io_unregister_buffers\n",
        "#undef std_io_core_xlang_io_read_fixed\n",
        "#undef std_io_core_xlang_io_write_fixed\n",
        "#undef std_io_core_xlang_io_wait_readable\n",
        "#define std_io_core_xlang_io_register_buffers io_register_buffers_4\n",
        "#define std_io_core_xlang_io_unregister_buffers io_unregister_buffers\n",
        "#define std_io_core_xlang_io_read_fixed xlang_io_read_fixed\n",
        "#define std_io_core_xlang_io_write_fixed xlang_io_write_fixed\n",
        "#define std_io_core_xlang_io_wait_readable io_wait_readable\n",
        "/* codegen 体内调 std_io_driver_io_*；#undef 后重绑到 preamble/io.o 的 io_*。 */\n",
        "#define std_io_driver_io_read_batch_buf io_read_batch_buf\n",
        "#define std_io_driver_io_write_batch_buf io_write_batch_buf\n",
        "#define std_io_driver_io_register_buffers_buf(bufs, nr) io_register_buffers_buf((intptr_t)(void *)(bufs), (int)(nr))\n",
        /*
         * 【Why 根源】产品 -o 仅有 extern；co-emit 整包 std.io 时未用到的 read/batch 仍进 .o，
         *   引用 xlang_io_submit_read / std_io_driver_submit_* / io_* / ctx_*。macOS 不能硬链
         *   runtime_asm_io_stubs（与 co-emit std_io_write_stdout 强符号冲突）。
         * 【Invariant】weak：有强符号选强；无则 stdio/占位，hello print 可链。
         */
        "#include <stdio.h>\n"
        "#ifndef __cplusplus\n"
        /*
         * 【Why 根源】勿 weak 桩 xlang_io_submit_read / submit_*_batch / submit_write：
         *   core co-emit 现为权威（调 std_io_backend_*）；同 TU weak+strong 重定义。
         *   旧 weak submit_write_batch 再调裸 io_write_batch，产品 -o 不硬链
         *   runtime_asm_io_stubs → 双端 UNDEF。仅保留无 core 体或仅弱路径的桩。
         * PLATFORM: SHARED.
         */
        "/* 仅补 co-emit 未定义的符号；勿桩 submit_read / submit_*_batch / submit_write（core 强定义）。 */\n"
        "__attribute__((weak)) int32_t xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle) {\n"
        "  (void)ptr; (void)len; (void)handle; return -1;\n"
        "}\n"
        "__attribute__((weak)) int32_t xlang_io_read_fixed(size_t h, uint32_t bi, size_t o, size_t l, uint32_t t) {\n"
        "  (void)h;(void)bi;(void)o;(void)l;(void)t; return -1;\n"
        "}\n"
        "__attribute__((weak)) int32_t xlang_io_write_fixed(size_t h, uint32_t bi, size_t o, size_t l, uint32_t t) {\n"
        "  (void)h;(void)bi;(void)o;(void)l;(void)t; return -1;\n"
        "}\n"
        "__attribute__((weak)) int32_t xlang_io_read_ptr_backend(void) { return 0; }\n"
        "__attribute__((weak)) int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr) {\n"
        "  (void)p0;(void)l0;(void)p1;(void)l1;(void)p2;(void)l2;(void)p3;(void)l3;(void)nr; return -1;\n"
        "}\n"
        "__attribute__((weak)) int io_wait_readable(int32_t *fds, int n, unsigned timeout_ms) {\n"
        "  (void)fds;(void)n;(void)timeout_ms; return -1;\n"
        "}\n"
        "__attribute__((weak)) ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms) {\n"
        "  (void)fd;(void)bufs;(void)n;(void)timeout_ms; return (ptrdiff_t)-1;\n"
        "}\n"
        "__attribute__((weak)) ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms) {\n"
        "  (void)fd;(void)bufs;(void)n;(void)timeout_ms; return (ptrdiff_t)-1;\n"
        "}\n"
        /* std.env mod.x extern args_iter_*_c：formal env.o is mod.x (std_env_*); args_iter body
         * is weak here (env.x no_mangle helpers are not the product formal surface).
         * PLATFORM: SHARED — process_args_* weak-delegate to process_xlang_*.
         * Provide weak process_xlang_* returning 0/NULL so Linux ld resolves refs inside
         * these weak stubs when runtime_process_argv.o is not linked (pure/backtrace).
         * Strong process_xlang_* from runtime_process_argv.o still win when ensure links it
         * (env/process real args). Do NOT empty process_args_* itself (Darwin would
         * dead_strip getters and hide real argc forever). */
        "__attribute__((weak)) int32_t process_xlang_argc_get(void) { return 0; }\n"
        "__attribute__((weak)) uint8_t *process_xlang_argv_get(int32_t i) { (void)i; return (uint8_t *)0; }\n"
        "__attribute__((weak)) int32_t process_args_count_c(void) { return process_xlang_argc_get(); }\n"
        "__attribute__((weak)) uint8_t *process_arg_c(int32_t i) { return process_xlang_argv_get(i); }\n"
        "__attribute__((weak)) int32_t args_iter_count_c(void) { return process_args_count_c(); }\n"
        "__attribute__((weak)) uint8_t *args_iter_at_c(int32_t i) { return process_arg_c(i); }\n"
        /* submit_read/write_batch(_buf)：勿 weak stub。co-emit driver.x 真体为权威；同 TU weak+strong 重定义，
         * 且 stub 返回 -1 使 run-io-driver r4 假红。 */
        "__attribute__((weak)) uint64_t std_io_driver_driver_read_ptr_gen(void) { return 0; }\n"
        "__attribute__((weak)) int64_t ctx_background_c(void) { return 0; }\n"
        "__attribute__((weak)) void ctx_cancel_c(int64_t c) { (void)c; }\n"
        "__attribute__((weak)) int64_t ctx_deadline_ns_c(int64_t c) { (void)c; return 0; }\n"
        "__attribute__((weak)) void ctx_free_c(int64_t c) { (void)c; }\n"
        "__attribute__((weak)) int32_t ctx_get_value_c(int64_t h, uint8_t *key, int64_t *out) {\n"
        "  (void)h;(void)key; if (out) *out = 0; return 0;\n"
        "}\n"
        "__attribute__((weak)) int32_t ctx_is_cancelled_c(int64_t c) { (void)c; return 0; }\n"
        "__attribute__((weak)) int64_t ctx_remaining_ns_c(int64_t c) { (void)c; return 0; }\n"
        "__attribute__((weak)) int32_t ctx_set_value_c(int64_t h, uint8_t *key, int64_t value) {\n"
        "  (void)h;(void)key;(void)value; return 0;\n"
        "}\n"
        "__attribute__((weak)) int64_t ctx_with_cancel_c(int64_t p) { (void)p; return 0; }\n"
        "__attribute__((weak)) int64_t ctx_with_deadline_c(int64_t p, int64_t ns) { (void)p;(void)ns; return 0; }\n"
        "__attribute__((weak)) int64_t ctx_with_timeout_c(int64_t p, int64_t ns) { (void)p;(void)ns; return 0; }\n"
        "#endif\n",
        "struct std_net_Ipv4Addr { uint8_t a; uint8_t b; uint8_t c; uint8_t d; };\n",
        "struct std_net_Ipv6Addr { uint8_t b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15; };\n",
        "#define handle_from_fd std_io_handle_from_fd\n",
        "#define submit_read_batch_buf std_io_submit_read_batch_buf\n",
        "#define submit_write_batch_buf std_io_submit_write_batch_buf\n",
        "#define read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n",
        "#define write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)\n",
        "/* 实际符号用 _real；仅定义 std_net_net_* 宏。\n"
        " * 【Why 勿 #define net_close_socket_c / net_run_accept_workers_c】\n"
        " * link_only 路径会 emit `extern int32_t net_close_socket_c(...)`；\n"
        " * 若宏同名，extern 声明被展开 → expected parameter declarator。 */\n",
        "extern int32_t net_close_socket_c_real(int32_t fd);\n",
        "extern int32_t net_run_accept_workers_c_real(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms);\n",
        "extern int32_t net_close_socket_c(int32_t fd);\n",
        "extern int32_t net_run_accept_workers_c(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms);\n",
        "#define std_net_net_close_socket_c(x) net_close_socket_c_real(xlang_io_net_fd(x))\n",
        "#define std_net_net_run_accept_workers_c(x, n, t) net_run_accept_workers_c_real(xlang_io_net_fd(x), n, t)\n",
        /* FsIovecBuf / Iovec：preamble 为 ABI 权威。
         * 勿用 typedef 吸收 posix 前缀——codegen 发 (struct std_fs_posix_Iovec){...}
         * 与 struct std_fs_posix_FsIovecBuf * 时，typedef 只建别名不建 tag → incomplete type。
         * #define 标签别名：struct std_fs_posix_X → struct 权威 tag。 */
        "#define STD_FS_FS_IOVEC_BUF_DEFINED\nstruct std_fs_FsIovecBuf { void *ptr; size_t length; size_t handle; };\n"
        "#define std_fs_posix_FsIovecBuf std_fs_FsIovecBuf\n"
        "struct std_io_sync_Iovec { uint8_t *base; size_t length; };\n"
        "#define std_fs_posix_Iovec std_io_sync_Iovec\n",
        /* 仅 forward：完整体由 std/map 发射；preamble 全量定义与 map.o -o 双权威 → redefinition */
        "struct std_map_Map_i32_i32;\n",
        "typedef struct std_io_driver_Buffer std_net_Buffer;\n",
        /* Error + ErrorChain：与 codegen_should_skip_emit_struct_layout 同权威（缺则 incomplete type） */
        "struct std_error_Error { int32_t code; };\n",
        "struct std_error_ErrorChain { int32_t depth; int32_t c0; int32_t c1; int32_t c2; int32_t c3; };\n",
        "struct std_string_String { uint8_t data[256]; int32_t length; };\n",
        "typedef struct std_string_String String;\n",
        "struct std_string_StrView { uint8_t *ptr; int32_t length; };\n",
        /* heap.Allocator 须在 Vec 之前完整（codegen 现按模块序 emit，vec 先于 heap 布局） */
        "struct std_heap_Arena64 { uint8_t *chunk; size_t cap; size_t off; };\n",
        "struct std_heap_Allocator { int32_t kind; struct std_heap_Arena64 *arena; };\n",
        /* Vec 完整体由 std/vec 发射（含 al）；勿在此写 3 字段旧布局 */
        "struct std_vec_Vec_i32;\n",
        /* core.option 具象 monomorph：preamble 权威完整布局，避免 co-emit 顺序
         * （core.slice 函数体在 option 体之前）时 incomplete Option_u8/u64。 */
        "struct core_option_Option_i32 { int is_some; int32_t value; };\n",
        "struct core_option_Option_u8 { int is_some; uint8_t value; uint8_t _pad0; uint8_t _pad1; uint8_t _pad2; };\n",
        "struct core_option_Option_u64 { int is_some; int32_t _pad; uint64_t value; };\n",
        "struct core_option_Option_ptr_u8 { int is_some; int32_t _pad; uint8_t *value; };\n",
        /* 与 runtime.from_x.c write_io_net_abi_inline 对齐：产品 XLANG_RT_PREAMBLE_FROM_X 路径必须含 Result_*，
           否则 multi-dep（core.types 幽灵 layout 抢 owner）时 incomplete core_result_Result_*。 */
        "struct core_result_Result_i32 { int32_t value; int32_t _pad1; int32_t err; int32_t _pad2; };\n",
        "struct core_result_Result_u8 { uint8_t value; uint8_t _pad1; uint8_t _pad2; uint8_t _pad3; int32_t err; int32_t _pad4; };\n",
        /* wave386: second arg intptr_t so cstr pointers survive LP64; has_msg 0/1/2. */
        "extern void xlang_panic_(int, intptr_t);\n",
        /* 仅 extern：co-emit core.types 会生成强定义；同 TU weak+强定义 → redefinition。 */
        "extern int32_t core_types_placeholder(void);\n",
        "extern int32_t std_heap_alloc_size_zero(void);\n",
        "extern int32_t std_runtime_runtime_ready(void);\n",
        "#ifndef __cplusplus\n"
        "__attribute__((weak)) int32_t std_vec_vec_len_empty(void) { return 0; }\n"
        "__attribute__((weak)) int32_t std_vec_len_empty(void) { return 0; }\n"
        "#else\n"
        "extern int32_t std_vec_vec_len_empty(void);\n"
        "extern int32_t std_vec_len_empty(void);\n"
        "#endif\n",
        "#define vec_len_empty std_vec_vec_len_empty\n",
        "#define alloc_size_zero std_heap_alloc_size_zero\n",
        "#define runtime_ready std_runtime_runtime_ready\n",
        "#ifndef __cplusplus\n"
        "__attribute__((weak)) int32_t std_string_placeholder(void) { return 0; }\n"
        "#else\n"
        "extern int32_t std_string_placeholder(void);\n"
        "#endif\n",
        /* removed #define placeholder: clobbers entry module function names */
        "extern int32_t fmt_i32(int32_t);\n",
        "extern struct std_string_String std_string_string_new(void);\n",
        /* removed #define string_new: same collision risk */
    };

const int32_t driver_preamble_io_net_lines_n =
    (int32_t)(sizeof(driver_preamble_io_net_lines) / sizeof(driver_preamble_io_net_lines[0]));

const char *const driver_preamble_fs_path_lines[] = {
        "typedef struct std_fs_FsIovecBuf fs_iovec_buf_t;\n",
        "extern int32_t fs_open_read_c(uint8_t *path);\n",
        "extern uint64_t fs_direct_align_c(void);\n",
        "extern int32_t fs_fadvise_sequential_c(int32_t fd);\n",
        "extern int32_t fs_fadvise_willneed_c(int32_t fd, int64_t offset, size_t len);\n",
        "extern int64_t fs_copy_file_range_c(int32_t fd_in, int32_t fd_out, size_t len);\n",
        "extern int64_t fs_sendfile_c(int32_t out_fd, int32_t in_fd, size_t count);\n",
        "extern int64_t fs_pipe_splice_c(int32_t fd_in, int32_t fd_out, size_t len);\n",
        "extern int32_t fs_sync_range_c(int32_t fd, int64_t offset, size_t len);\n",
        "extern int32_t fs_sync_c(int32_t fd);\n",
        "extern int32_t fs_fallocate_c(int32_t fd, int64_t offset, int64_t len);\n",
        "extern int32_t fs_last_error_c(void);\n",
        "extern int64_t fs_readv_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);\n",
        "extern int64_t fs_writev_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);\n",
        "extern int32_t std_path_empty_len(void);\n",
        "#define empty_len() std_path_empty_len()\n",
        /* Match std/heap/ops.x / map_abi.h (non-const): co-emit defining TU must not
         * conflict with this prototype. PLATFORM: SHARED — G.7 single signature. */
        "extern int32_t map_i32_i32_find_c(int32_t *keys, uint8_t *occupied, int32_t cap, int32_t key);\n",
        "extern int32_t std_map_empty_size(void);\n",
        "#define empty_size(_a, _b) std_map_empty_size()\n",
        "extern int32_t std_error_error_ok(void);\n",
        "#define error_ok(_a, _b) std_error_error_ok()\n",
    };

const int32_t driver_preamble_fs_path_lines_n =
    (int32_t)(sizeof(driver_preamble_fs_path_lines) / sizeof(driver_preamble_fs_path_lines[0]));

#ifndef XLANG_RT_PREAMBLE_FROM_X

/** 向生成 C 写入 std.io / std.net 内联 ABI。成功返回 0。
 * 9.7.1: cf is the opaque fd-handle stream (xlang_driver_stream_cap.h). */
int write_io_net_abi_inline(uint8_t *cf) {
    const unsigned skip = codegen_get_preamble_skip_mask();
    int fd = xlang_driver_handle_to_fd(cf);
    if (fd < 0)
        return 1;
    for (int32_t i = 0; i < driver_preamble_io_net_lines_n; i++) {
        int skip_line = 0;
        /* std_io_driver_handle_* 别名：codegen 已 emit handle_stdin 等时跳过。 */
        if ((skip & CODEGEN_PREAMBLE_SKIP_STD_IO_DRIVER_HANDLE) && i >= 60 && i < 64)
            skip_line = 1;
        /* std_io_core_io_* 宏：无 std.io.core 内联时可整段省略。 */
        if ((skip & CODEGEN_PREAMBLE_SKIP_STD_IO_CORE_MACROS) && i >= 64 && i < 82)
            skip_line = 1;
        /* #undef / 重绑 std_io_core_*：X 内联 std.io.core 且 codegen 已 emit 时由 codegen 侧承担。 */
        if ((skip & CODEGEN_PREAMBLE_SKIP_STD_IO_UNDEF_REDEFINE) && i >= 105 && i < 119)
            skip_line = 1;
        /*
         * weak IO batch: table rows 178..181 inclusive (wave29 re-count, n=224):
         *   178 #include <stdio.h> + #ifndef __cplusplus
         *   179 weak xlang_io_* / io_* batch stubs (large)
         *   180 weak process_xlang_* / args_iter_*
         *   181 weak std_io_driver_* / ctx_* + #endif
         * Stale i==174 only hit a comment after rows grew; product .x had 124..134
         * (xlang_io_* externs) — dual authority; both wrong for co-emit redef.
         * PLATFORM: SHARED — align with driver_parsed_apply_preamble_skip(WEAK_IO_BATCH)
         * and src/runtime/rt_preamble.x. Skipping drops process weaks; link
         * runtime_process_argv.o when argv is required.
         */
        if ((skip & CODEGEN_PREAMBLE_SKIP_WEAK_IO_BATCH) && i >= 178 && i <= 181)
            skip_line = 1;
        if (!skip_line && xlang_io_write(fd, driver_preamble_io_net_lines[i],
                                         strlen(driver_preamble_io_net_lines[i])) < 0)
            return 1;
    }
    return 0;
}

/** 向生成 C 写入 std.fs / std.path / std.map / std.error 内联 ABI。成功返回 0。
 * 9.7.1: cf is the opaque fd-handle stream (xlang_driver_stream_cap.h). */
int write_fs_path_map_error_abi_inline(uint8_t *cf) {
    int fd = xlang_driver_handle_to_fd(cf);
    if (fd < 0)
        return 1;
    for (int32_t i = 0; i < driver_preamble_fs_path_lines_n; i++) {
        if (xlang_io_write(fd, driver_preamble_fs_path_lines[i],
                           strlen(driver_preamble_fs_path_lines[i])) < 0)
            return 1;
    }
    return 0;
}

#else
int write_io_net_abi_inline(uint8_t *cf);
int write_fs_path_map_error_abi_inline(uint8_t *cf);
#endif

int labi_rt_preamble_slice_marker(void) {
    return 1;
}
