/* Generated from src/runtime_io_abi.x (G-02f-29/44/57..59 true .x + C tail).
 * G-02f-334：PREFER_X_O hybrid 时 thin 由 .x→-E；rest 用 XLANG_L2_RIO_THIN_FROM_X
 *   + XLANG_RUNTIME_IO_ABI_FROM_X（省略已真迁 _impl；仅 slice_marker）。
 * Cap residual pure (2026-07-21)：4 平台 _impl 真迁 .x
 *   （flags_impl / write_path_bytes_impl / release_file_view_impl / read_file_view_impl）。
 * Cold seed 仍保留 mmap/fstat C 体（无 FROM_X）。
 * Regen: ./xlang-c -E -L .. src/runtime_io_abi.x > /tmp/io.c
 * .x covers: std.fs/posix + path/file_view 门闩 + Cap residual pure _impl。
 */
#include "win32_compat.h"
#include "runtime_io_abi.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <sys/stat.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#include <xlang_io_cap.h>
/* 【Why 根源】MinGW open() 默认文本模式，read/write 做 CRLF↔LF 转换，
 * 导致 fstat 报告的 st_size（物理字节数）与 read 实际返回字节数不一致。
 * 例：fmt 写入 37 字节 LF，文本模式 write 磁盘为 40 字节 CRLF；
 * fstat 报告 40，但 read 文本模式转换后只返回 37 → read mismatch → IO001。
 * 【Invariant】所有编译器 I/O 路径必须用二进制模式，保证 read/write 透明传输。
 * 【Asm/Perf】_O_BINARY 是 MinGW _open 的 flag，零运行时开销。 */
#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#ifndef _O_BINARY
#define _O_BINARY 0x8000
#endif
#define XLANG_O_BINARY _O_BINARY
#else
#define XLANG_O_BINARY 0
#endif

/**
 * B-20：POSIX read 循环读 fd 到 buf[0..cap-1]；成功返回读入字节数，失败 -1。
 * 参数：fd 已打开描述符；buf/cap 输出缓冲与容量。
 * Cap residual 9.1.8: Linux via xlang_io_cap.h (no libc read); Win keeps read().
 * G-02f-334：hybrid 时作 _impl（.x thin 门闩调 _impl）。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-rest：rest→.x 迁移：_impl 真迁 .x，PREFER_X_O 路径下整体跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
#ifndef XLANG_L2_RIO_THIN_FROM_X
int xlang_read_fd_into_buf(int fd, void *buf, size_t cap)
#else
int xlang_read_fd_into_buf_impl(int fd, void *buf, size_t cap)
#endif
{
    size_t off;
    ssize_t n;

    if (fd < 0 || !buf || cap == 0 || cap > (size_t)INT32_MAX)
        return -1;
    off = 0;
    while (off < cap) {
        n = (ssize_t)xlang_io_read(fd, (char *)buf + off, cap - off);
        if (n < 0)
            return -1;
        if (n == 0)
            break;
        off += (size_t)n;
    }
    return (int)off;
}
#endif /* XLANG_RUNTIME_IO_ABI_FROM_X */


/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-334：hybrid 时作 _impl */
/* G-02f-rest：rest→.x 迁移：_impl 真迁 .x，PREFER_X_O 路径下整体跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
#ifndef XLANG_L2_RIO_THIN_FROM_X
int xlang_runtime_file_view_read_malloc(int fd, size_t size, XlangRuntimeFileView *out)
#else
int xlang_runtime_file_view_read_malloc_impl(int fd, size_t size, XlangRuntimeFileView *out)
#endif
{
    size_t off;
    char *buf;
    ssize_t n;

    buf = (char *)malloc(size + 1);
    if (!buf) {
        close(fd);
        return -1;
    }
    off = 0;
    while (off < size) {
        n = (ssize_t)xlang_io_read(fd, buf + off, size - off);
        if (n < 0) {
            free(buf);
            close(fd);
            return -1;
        }
        if (n == 0)
            break;
        off += (size_t)n;
    }
    close(fd);
    if (off != size) {
        free(buf);
        return -1;
    }
    buf[size] = '\0';
    out->data = buf;
    out->length = size;
    out->needs_free = 1;
    out->needs_munmap = 0;
    return 0;
}
#endif /* XLANG_RUNTIME_IO_ABI_FROM_X */


/* G-02f-59 io helper protos（hybrid 时 flags 由 thin 调 flags_impl） */
#ifndef XLANG_L2_RIO_THIN_FROM_X
int32_t xlang_fs_open_write_flags(void);
#else
int32_t xlang_fs_open_write_flags_impl(void);
#endif
/* G-02f-58 helper protos */
int runtime_read_file_view_impl(const char *path, XlangRuntimeFileView *out);
char *runtime_read_file_malloc_impl(const char *path, size_t *out_len);
int32_t std_sys_os_read_file_into_impl(uint8_t *path, uint8_t *buf, int32_t cap);

/* G-02f-57 helper protos */
int xlang_read_file_into_path_impl(const char *path, void *buf, size_t cap);
int xlang_write_path_bytes_impl(const char *path, const void *data, size_t len);
void runtime_release_file_view_impl(XlangRuntimeFileView *view);

/* G-02f-rest：5 个 pure _impl 已在 .x；FROM_X 时 seed 仅声明供 cold 互调。
 * Cap residual pure (2026-07-21)：4 平台 _impl 亦真迁 .x（flags/write/release/read_view）。
 * Cold (no FROM_X) 仍保留下方 C 体（mmap/fstat 路径）。 */
int xlang_read_fd_into_buf_impl(int fd, void *buf, size_t cap);
int xlang_runtime_file_view_read_malloc_impl(int fd, size_t size, XlangRuntimeFileView *out);

#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
int runtime_read_file_view_impl(const char *path, XlangRuntimeFileView *out) {
    int fd;
    int fd_fallback;
    struct stat st;
    size_t size;
    void *mapped;

    if (!path || !out)
        return -1;
    memset(out, 0, sizeof(*out));
    fd = open(path, O_RDONLY | XLANG_O_BINARY, 0);
    if (fd < 0)
        return -1;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size < 0) {
        close(fd);
        return -1;
    }
    size = (size_t)st.st_size;
    if (size == 0) {
        out->data = "";
        out->length = 0;
        close(fd);
        return 0;
    }
    mapped = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (mapped == MAP_FAILED) {
        fd_fallback = open(path, O_RDONLY | XLANG_O_BINARY, 0);
        if (fd_fallback < 0)
            return -1;
#ifdef XLANG_L2_RIO_THIN_FROM_X
        return xlang_runtime_file_view_read_malloc_impl(fd_fallback, size, out);
#else
        return xlang_runtime_file_view_read_malloc(fd_fallback, size, out);
#endif
    }
    out->data = (const char *)mapped;
    out->length = size;
    out->needs_free = 0;
    out->needs_munmap = 1;
    return 0;
}
#endif /* !XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
int runtime_read_file_view(const char *path, XlangRuntimeFileView *out) {
  if (path == NULL) {
    return -1;
  }
  if (out == NULL) {
    return -1;
  }
  {
    return runtime_read_file_view_impl(path, out);
  }
  return -1;
}
#endif

#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
void runtime_release_file_view_impl(XlangRuntimeFileView *view) {
    if (view->needs_munmap && view->data && view->length > 0)
        munmap((void *)view->data, view->length);
    if (view->needs_free && view->data)
        free((void *)view->data);
    view->data = NULL;
    view->length = 0;
    view->needs_free = 0;
    view->needs_munmap = 0;
}
#endif /* !XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
void runtime_release_file_view(XlangRuntimeFileView *view) {
  if (view == NULL) {
    return;
  }
  {
    runtime_release_file_view_impl(view);
  }
}
#endif

/**
 * B-20：POSIX open/fstat/read 读整文件到堆缓冲。
 * 参数：见 runtime_io_abi.h。
 */
/* G-02f-rest：rest→.x 迁移：_impl 真迁 .x，PREFER_X_O 路径下整体跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
char *runtime_read_file_malloc_impl(const char *path, size_t *out_len) {
    XlangRuntimeFileView view;
    char *buf;

#ifdef XLANG_L2_RIO_THIN_FROM_X
    if (runtime_read_file_view_impl(path, &view) != 0)
#else
    if (runtime_read_file_view(path, &view) != 0)
#endif
        return NULL;
    buf = (char *)malloc(view.length + 1);
    if (!buf) {
#ifdef XLANG_L2_RIO_THIN_FROM_X
        runtime_release_file_view_impl(&view);
#else
        runtime_release_file_view(&view);
#endif
        return NULL;
    }
    if (view.length > 0)
        memcpy(buf, view.data, view.length);
    buf[view.length] = '\0';
    if (out_len)
        *out_len = view.length;
#ifdef XLANG_L2_RIO_THIN_FROM_X
    runtime_release_file_view_impl(&view);
#else
    runtime_release_file_view(&view);
#endif
    return buf;
}
#endif /* XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
char *runtime_read_file_malloc(const char *path, size_t *out_len) {
  if (path == NULL) {
    return NULL;
  }
  {
    return runtime_read_file_malloc_impl(path, out_len);
  }
  return NULL;
}
#endif

/**
 * B-20：open/read/close 将文件读入 buf；供 ast_pool 与 driver 语法探测。
 * 参数：见 runtime_io_abi.h。
 */
/* G-02f-rest：rest→.x 迁移：_impl 真迁 .x，PREFER_X_O 路径下整体跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
int xlang_read_file_into_path_impl(const char *path, void *buf, size_t cap) {
    int fd;
    int n;

    if (cap > (size_t)INT32_MAX)
        return -1;
    fd = open(path, O_RDONLY | XLANG_O_BINARY, 0);
    if (fd < 0)
        return -1;
#ifdef XLANG_L2_RIO_THIN_FROM_X
    n = xlang_read_fd_into_buf_impl(fd, buf, cap);
#else
    n = xlang_read_fd_into_buf(fd, buf, cap);
#endif
    close(fd);
    return n;
}
#endif /* XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
int xlang_read_file_into_path(const char *path, void *buf, size_t cap) {
  if (path == NULL) {
    return -1;
  }
  if (buf == NULL) {
    return -1;
  }
  if (cap == 0) {
    return -1;
  }
  {
    return xlang_read_file_into_path_impl(path, buf, cap);
  }
  return -1;
}
#endif

/**
 * B-20：open(O_WRONLY|O_CREAT|O_TRUNC)/write 写整文件。
 * 参数：见 runtime_io_abi.h。
 * Cap residual 9.1.8: Linux via xlang_io_cap.h (no libc write); .x twin same.
 * Cap residual pure：.x 真迁；FROM_X 时由 .x 提供。
 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
int xlang_write_path_bytes_impl(const char *path, const void *data, size_t len) {
    int fd;
    size_t off;
    ssize_t n;

    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | XLANG_O_BINARY, (mode_t)0644);
    if (fd < 0)
        return -1;
    off = 0;
    while (off < len) {
        n = (ssize_t)xlang_io_write(fd, (const char *)data + off, len - off);
        if (n < 0) {
            close(fd);
            return -1;
        }
        if (n == 0)
            break;
        off += (size_t)n;
    }
    close(fd);
    return off == len ? 0 : -1;
}
#endif /* !XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
int xlang_write_path_bytes(const char *path, const void *data, size_t len) {
  if (path == NULL) {
    return -1;
  }
  if (data == NULL) {
    return -1;
  }
  {
    return xlang_write_path_bytes_impl(path, data, len);
  }
  return -1;
}
#endif

/* -------------------------------------------------------------------------- */
/* G-02e：原 std_fs_shim.c / std_sys_shim.c 并入本 TU（产品链减 2 个手写 C 文件）。 */
/* -------------------------------------------------------------------------- */


/** G-02f-44：open_write 平台 flags/mode 槽（.x 调 open）。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-334：hybrid 时作 flags_impl（.x thin 门闩调 _impl） */
/* Cap residual pure：flags_impl 真迁 .x；FROM_X 时整段跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
#ifndef XLANG_L2_RIO_THIN_FROM_X
int32_t xlang_fs_open_write_flags(void)
#else
int32_t xlang_fs_open_write_flags_impl(void)
#endif
{
    return (int32_t)(O_WRONLY | O_CREAT | O_TRUNC | XLANG_O_BINARY);
}
#endif /* !XLANG_RUNTIME_IO_ABI_FROM_X */

/* G-02f-120：逻辑源 .x（真迁）；hybrid 时 mode 由 .x thin 提供 */
#ifndef XLANG_L2_RIO_THIN_FROM_X
int32_t xlang_fs_open_write_mode(void) {
    return (int32_t)0644;
}
#endif

/* G-02f-334：std.fs / posix 公共门闩由 .x thin；默认 seed 保留 */
#ifndef XLANG_L2_RIO_THIN_FROM_X

int32_t std_fs_fs_open_read(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  (void)(({   {
    int32_t r = open(path, 0, 0);
    return r;
  }
 }));
  return (0 - 1);
}

int32_t std_fs_fs_open_write(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  (void)(({   {
    int32_t fl = xlang_fs_open_write_flags();
    int32_t md = xlang_fs_open_write_mode();
    int32_t r = open(path, fl, md);
    return r;
  }
 }));
  return (0 - 1);
}

int32_t std_fs_fs_close(int32_t fd) {
  (void)(({   {
    int32_t r = close(fd);
    return r;
  }
 }));
  return (0 - 1);
}

int32_t std_fs_fs_invalid_handle(void) {
  return (0 - 1);
}

ssize_t std_fs_fs_read(int32_t fd, uint8_t * buf, size_t count) {
  if ((buf ==((uint8_t *)(0)))) {
    ssize_t neg = ((ssize_t)((0 - 1)));
    return neg;
  }
  (void)(({   {
    ssize_t n = (ssize_t)xlang_io_read((int)fd, (void *)buf, count);
    return n;
  }
 }));
  ssize_t neg2 = ((ssize_t)((0 - 1)));
  return neg2;
}

ssize_t std_fs_fs_write(int32_t fd, uint8_t * buf, size_t count) {
  if ((buf ==((uint8_t *)(0)))) {
    ssize_t neg = ((ssize_t)((0 - 1)));
    return neg;
  }
  (void)(({   {
    ssize_t n = (ssize_t)xlang_io_write((int)fd, (const void *)buf, count);
    return n;
  }
 }));
  ssize_t neg2 = ((ssize_t)((0 - 1)));
  return neg2;
}

/* Surface short name fs_open_read_c — twin of runtime_io_abi.x #[no_mangle].
 * PLATFORM: SHARED — std/fs mangles to std_fs_fs_open_read_c; config/elf need bare name. */
int32_t fs_open_read_c(uint8_t * path) {
  return std_fs_fs_open_read(path);
}

int32_t fs_posix_close_c(int32_t fd) {
  return std_fs_fs_close(fd);
}

ssize_t fs_posix_write_c(int32_t fd, uint8_t * buf, size_t count) {
  return std_fs_fs_write(fd, buf, count);
}

ssize_t fs_posix_read_c(int32_t fd, uint8_t * buf, size_t count) {
  return std_fs_fs_read(fd, buf, count);
}

#endif /* !XLANG_L2_RIO_THIN_FROM_X */

/**
 * std.sys.os_read_file_into 的 C 链接符号（-E-extern import 名）。
 * 成功返回读入字节数；失败 -1。
 */
/* G-02f-rest：rest→.x 迁移：_impl 真迁 .x，PREFER_X_O 路径下整体跳过 */
#ifndef XLANG_RUNTIME_IO_ABI_FROM_X
int32_t std_sys_os_read_file_into_impl(uint8_t *path, uint8_t *buf, int32_t cap) {
  int32_t fd;
  int32_t total;
  if (!path || !buf || cap <= 0)
    return -1;
  fd = (int32_t)open((const char *)path, O_RDONLY | XLANG_O_BINARY, 0);
  if (fd < 0)
    return -1;
  total = 0;
  while (total < cap) {
    int32_t chunk = cap - total;
    ssize_t r = (ssize_t)xlang_io_read(fd, buf + total, (size_t)chunk);
    if (r < 0) {
      close(fd);
      return -1;
    }
    if (r == 0)
      break;
    total += (int32_t)r;
  }
  close(fd);
  return total;
}
#endif /* XLANG_RUNTIME_IO_ABI_FROM_X */

#ifndef XLANG_L2_RIO_THIN_FROM_X
int32_t std_sys_os_read_file_into(uint8_t *path, uint8_t *buf, int32_t cap) {
  if (path == NULL) {
    return -1;
  }
  if (buf == NULL) {
    return -1;
  }
  if (cap <= 0) {
    return -1;
  }
  {
    return std_sys_os_read_file_into_impl(path, buf, cap);
  }
  return -1;
}
#endif

/* R2：PREFER_X_O + FROM_X 下 rest 业务 H=0（仅 slice marker；4 平台 Cap residual pure 已闭） */
int runtime_io_abi_slice_marker(void) {
    return 1;
}

