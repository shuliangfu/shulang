/**
 * std/fs/fs.c — 高性能文件：mmap 只读/可写、munmap、O_DIRECT、fadvise、madvise、copy_file_range（极致压榨）
 *
 * 与 std/fs/mod.su 同目录；供 std.fs 各 API 调用。
 * 链接用户程序时由编译器链入本目录产出的 fs.o；POSIX 需 -lc。
 * 大文件：64 位平台下 st_size 与 size_t 均为 64 位，支持 >2GB 文件。
 */

#define _GNU_SOURCE 1
#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <mswsock.h>
#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#endif

/* Windows 补全：CreateFileMapping + MapViewOfFile、无缓冲打开、copy/readv/writev/TransmitFile/fallocate。符号与 std.fs extern 一致。MinGW 链接 TransmitFile 时需 -lws2_32 -lmswsock。 */

/** 只读内存映射：CreateFile -> CreateFileMapping(PAGE_READONLY) -> MapViewOfFile(FILE_MAP_READ)。*out_size 为文件字节数；失败返回 NULL。 */
void *fs_mmap_ro_c(uint8_t *path, size_t *out_size) {
    HANDLE hFile, hMap;
    LARGE_INTEGER li;
    void *view;
    if (!path || !out_size) return NULL;
    *out_size = 0;
    hFile = CreateFileA((const char *)path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return NULL;
    if (!GetFileSizeEx(hFile, &li) || li.QuadPart <= 0) { CloseHandle(hFile); return NULL; }
    hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(hFile);
    if (!hMap) return NULL;
    view = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(hMap);
    if (!view) return NULL;
    *out_size = (size_t)li.QuadPart;
    return view;
}

/** 可写内存映射：PAGE_READWRITE + FILE_MAP_WRITE；改完 UnmapViewOfFile 即落盘。 */
void *fs_mmap_rw_c(uint8_t *path, size_t *out_size) {
    HANDLE hFile, hMap;
    LARGE_INTEGER li;
    void *view;
    if (!path || !out_size) return NULL;
    *out_size = 0;
    hFile = CreateFileA((const char *)path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return NULL;
    if (!GetFileSizeEx(hFile, &li) || li.QuadPart <= 0) { CloseHandle(hFile); return NULL; }
    hMap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    CloseHandle(hFile);
    if (!hMap) return NULL;
    view = MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
    CloseHandle(hMap);
    if (!view) return NULL;
    *out_size = (size_t)li.QuadPart;
    return view;
}

/** 解除映射；ptr 须为 MapViewOfFile 返回值。返回 0 成功，-1 失败。 */
int32_t fs_munmap_c(void *ptr, size_t size) {
    (void)size;
    return (ptr && UnmapViewOfFile(ptr)) ? 0 : -1;
}

/** 无缓冲只读打开（FILE_FLAG_NO_BUFFERING）；buf 与 offset 须对齐 fs_direct_align()。返回 CRT fd，失败 -1。 */
int32_t fs_open_read_direct_c(uint8_t *path) {
    HANDLE h;
    int fd;
    if (!path) return -1;
    h = CreateFileA((const char *)path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (h == INVALID_HANDLE_VALUE) return -1;
    fd = (int)_open_osfhandle((intptr_t)h, _O_RDONLY);
    if (fd < 0) { CloseHandle(h); return -1; }
    return fd;
}

/** 无缓冲 I/O 对齐要求（扇区/页，通常 4096）。 */
uint64_t fs_direct_align_c(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (uint64_t)si.dwPageSize;
}

int32_t fs_fadvise_sequential_c(int32_t fd) { (void)fd; return 0; }
int32_t fs_fadvise_willneed_c(int32_t fd, int64_t offset, size_t len) { (void)fd; (void)offset; (void)len; return 0; }

/** 从 fd_in 当前偏移复制 len 字节到 fd_out 当前偏移（ReadFile/WriteFile 循环）；两 fd 偏移前进。返回复制字节数，-1 失败。 */
int64_t fs_copy_file_range_c(int32_t fd_in, int32_t fd_out, size_t len) {
    HANDLE hIn, hOut;
    uint8_t *buf;
    size_t chunk, copied = 0;
    DWORD nr, nw;
    const size_t buf_size = 256 * 1024;
    hIn = (HANDLE)_get_osfhandle(fd_in);
    hOut = (HANDLE)_get_osfhandle(fd_out);
    if (hIn == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) return -1;
    buf = (uint8_t *)malloc(buf_size);
    if (!buf) return -1;
    while (copied < len) {
        chunk = len - copied;
        if (chunk > buf_size) chunk = buf_size;
        if (!ReadFile(hIn, buf, (DWORD)chunk, &nr, NULL) || nr == 0) break;
        if (!WriteFile(hOut, buf, nr, &nw, NULL) || nw != nr) { copied = (size_t)-1; break; }
        copied += (size_t)nr;
        if ((DWORD)nr < (DWORD)chunk) break;
    }
    free(buf);
    return (copied != (size_t)-1) ? (int64_t)copied : -1;
}

/** 分散读：两段 ReadFile，返回总字节数，-1 错误。 */
int64_t fs_readv2_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1) {
    HANDLE h;
    DWORD n0, n1;
    h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return -1;
    if (!ReadFile(h, p0, (DWORD)(l0 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l0), &n0, NULL)) return -1;
    if (!ReadFile(h, p1, (DWORD)(l1 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l1), &n1, NULL)) return -1;
    return (int64_t)n0 + (int64_t)n1;
}

/** 集中写：两段 WriteFile，返回总字节数，-1 错误。 */
int64_t fs_writev2_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1) {
    HANDLE h;
    DWORD n0, n1;
    h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return -1;
    if (!WriteFile(h, p0, (DWORD)(l0 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l0), &n0, NULL)) return -1;
    if (!WriteFile(h, p1, (DWORD)(l1 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l1), &n1, NULL)) return -1;
    return (int64_t)n0 + (int64_t)n1;
}

/** 零拷贝文件到 socket：TransmitFile(out_fd=socket, in_fd=file)。out_fd 须为 Winsock SOCKET 对应的 fd，in_fd 为文件 fd。返回发送字节数，-1 失败。 */
int64_t fs_sendfile_c(int32_t out_fd, int32_t in_fd, size_t count) {
    HANDLE hFile;
    SOCKET s;
    BOOL ok;
    hFile = (HANDLE)_get_osfhandle(in_fd);
    if (hFile == INVALID_HANDLE_VALUE) return -1;
    s = (SOCKET)(intptr_t)_get_osfhandle(out_fd);
    ok = TransmitFile(s, hFile, (DWORD)(count > 0x7FFFFFFFu ? 0x7FFFFFFFu : count), 0, NULL, NULL, TF_USE_DEFAULT_WORKER);
    return ok ? (int64_t)count : -1;
}

/** 范围刷盘：Windows 无等价 API，整文件用 FlushFileBuffers；此处 no-op 返回 0 以兼容调用方。 */
int32_t fs_sync_range_c(int32_t fd, int64_t offset, size_t len) {
    (void)fd;
    (void)offset;
    (void)len;
    return 0;
}

/** 预分配 [offset, offset+len)：SetFilePointerEx + SetEndOfFile；仅扩展不收缩。恢复调用前文件位置以兼容 Linux 语义。返回 0 成功，-1 失败。 */
int32_t fs_fallocate_c(int32_t fd, int64_t offset, int64_t len) {
    HANDLE h;
    LARGE_INTEGER cur, need, oldPos, zero;
    if (len <= 0) return 0;
    h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return -1;
    if (!GetFileSizeEx(h, &cur)) return -1;
    need.QuadPart = offset + len;
    if (need.QuadPart <= (int64_t)cur.QuadPart) return 0;
    zero.QuadPart = 0;
    if (!SetFilePointerEx(h, zero, &oldPos, FILE_CURRENT)) return -1;
    if (!SetFilePointerEx(h, need, NULL, FILE_BEGIN)) return -1;
    if (!SetEndOfFile(h)) { SetFilePointerEx(h, oldPos, NULL, FILE_BEGIN); return -1; }
    (void)SetFilePointerEx(h, oldPos, NULL, FILE_BEGIN);
    return 0;
}

/** 追加写打开 path（不存在则创建）；失败返回 -1。 */
int32_t fs_open_append_c(uint8_t *path) {
    HANDLE h;
    int fd;
    if (!path) return -1;
    h = CreateFileA((const char *)path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return -1;
    fd = (int)_open_osfhandle((intptr_t)h, _O_WRONLY | _O_APPEND);
    if (fd < 0) { CloseHandle(h); return -1; }
    return fd;
}

/** 写打开 path，不存在则创建、存在则不截断；失败返回 -1。 */
int32_t fs_open_create_c(uint8_t *path) {
    HANDLE h;
    int fd;
    if (!path) return -1;
    h = CreateFileA((const char *)path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return -1;
    fd = (int)_open_osfhandle((intptr_t)h, _O_WRONLY);
    if (fd < 0) { CloseHandle(h); return -1; }
    return fd;
}

/** 返回上次 fs_* 失败时的平台错误码（Windows GetLastError；POSIX errno）。 */
int32_t fs_last_error_c(void) {
    return (int32_t)(uint32_t)GetLastError();
}

/** 包装 libc read，供 .su 的 fs_read 调用，避免与 std.io 的 read(handle,ptr,len,timeout) 同名。 */
int64_t fs_posix_read_c(int32_t fd, uint8_t *buf, size_t count) {
    unsigned c = (count > 0x7FFFFFFFu) ? 0x7FFFFFFFu : (unsigned)count;
    return (int64_t)_read((int)fd, buf, c);
}

/** 包装 libc write，供 .su 的 fs_write 调用。 */
int64_t fs_posix_write_c(int32_t fd, const uint8_t *buf, size_t count) {
    unsigned c = (count > 0x7FFFFFFFu) ? 0x7FFFFFFFu : (unsigned)count;
    return (int64_t)_write((int)fd, buf, c);
}

/** 分散读：四段 readv；返回总字节数，-1 错误。 */
int64_t fs_readv4_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3) {
    HANDLE h;
    DWORD n0, n1, n2, n3;
    h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return -1;
    if (!ReadFile(h, p0, (DWORD)(l0 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l0), &n0, NULL)) return -1;
    if (!ReadFile(h, p1, (DWORD)(l1 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l1), &n1, NULL)) return -1;
    if (!ReadFile(h, p2, (DWORD)(l2 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l2), &n2, NULL)) return -1;
    if (!ReadFile(h, p3, (DWORD)(l3 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l3), &n3, NULL)) return -1;
    return (int64_t)n0 + (int64_t)n1 + (int64_t)n2 + (int64_t)n3;
}

/** 集中写：四段 writev；返回总字节数，-1 错误。 */
int64_t fs_writev4_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3) {
    HANDLE h;
    DWORD n0, n1, n2, n3;
    h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return -1;
    if (!WriteFile(h, p0, (DWORD)(l0 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l0), &n0, NULL)) return -1;
    if (!WriteFile(h, p1, (DWORD)(l1 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l1), &n1, NULL)) return -1;
    if (!WriteFile(h, p2, (DWORD)(l2 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l2), &n2, NULL)) return -1;
    if (!WriteFile(h, p3, (DWORD)(l3 > 0x7FFFFFFFu ? 0x7FFFFFFFu : l3), &n3, NULL)) return -1;
    return (int64_t)n0 + (int64_t)n1 + (int64_t)n2 + (int64_t)n3;
}

/** 与 Zig/Rust 对齐：按「指针+段数」分散读/集中写；bufs 为 (ptr,len,handle) 布局与 .su Buffer ABI 一致，n 为 1..FS_IOV_BUF_MAX。 */
#define FS_IOV_BUF_MAX 16
typedef struct { uint8_t *ptr; size_t len; size_t handle; } fs_iovec_buf_t;

int64_t fs_readv_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n) {
    if (n <= 0 || n > FS_IOV_BUF_MAX || !bufs) return -1;
    {
        HANDLE h = (HANDLE)_get_osfhandle(fd);
        if (h == INVALID_HANDLE_VALUE) return -1;
        int64_t total = 0;
        int i;
        for (i = 0; i < n; i++) {
            DWORD got;
            size_t len = bufs[i].len;
            if (len > 0x7FFFFFFFu) len = 0x7FFFFFFFu;
            if (!ReadFile(h, bufs[i].ptr, (DWORD)len, &got, NULL)) return -1;
            total += (int64_t)got;
            if ((size_t)got < bufs[i].len) return total;
        }
        return total;
    }
}

int64_t fs_writev_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n) {
    if (n <= 0 || n > FS_IOV_BUF_MAX || !bufs) return -1;
    {
        HANDLE h = (HANDLE)_get_osfhandle(fd);
        if (h == INVALID_HANDLE_VALUE) return -1;
        int64_t total = 0;
        int i;
        for (i = 0; i < n; i++) {
            DWORD written;
            size_t len = bufs[i].len;
            if (len > 0x7FFFFFFFu) len = 0x7FFFFFFFu;
            if (!WriteFile(h, bufs[i].ptr, (DWORD)len, &written, NULL)) return -1;
            total += (int64_t)written;
            if ((size_t)written < bufs[i].len) return total;
        }
        return total;
    }
}
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/uio.h>
#if defined(__linux__)
#include <sys/sendfile.h>
/* O_DIRECT：绕过页缓存，顺序大文件读极致吞吐；buf 与 offset 须对齐（通常 4096）。 */
#ifndef O_DIRECT
#define O_DIRECT 00040000
#endif
#ifndef POSIX_FADV_SEQUENTIAL
#define POSIX_FADV_SEQUENTIAL 2
#endif
#ifndef POSIX_FADV_WILLNEED
#define POSIX_FADV_WILLNEED 3
#endif
#ifndef SYNC_FILE_RANGE_WRITE
#define SYNC_FILE_RANGE_WRITE 2
#endif
#endif
/* posix_fadvise 仅 Linux 提供；macOS/FreeBSD 无此 API，fadvise 包装在 Linux 外为 no-op。 */

/** 只读 mmap 整个文件；path 为 NUL 结尾。返回映射首地址，*out_size 为文件字节数；失败返回 NULL。调用方用毕须 fs_munmap(ptr, *out_size)。madvise(MADV_SEQUENTIAL) 提示内核顺序访问以压榨吞吐。 */
void *fs_mmap_ro_c(uint8_t *path, size_t *out_size) {
    if (!path || !out_size) return NULL;
    *out_size = 0;
    int fd = open((const char *)path, O_RDONLY, 0);
    if (fd < 0) return NULL;
    struct stat st;
    if (fstat(fd, &st) != 0) { (void)close(fd); return NULL; }
    size_t len = (size_t)st.st_size;
    if (len == 0) { (void)close(fd); *out_size = 0; return NULL; }
    void *p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    (void)close(fd);
    if (p == MAP_FAILED) return NULL;
#if defined(MADV_SEQUENTIAL)
    (void)madvise(p, len, MADV_SEQUENTIAL);
#endif
#if defined(__linux__) && defined(MADV_HUGEPAGE)
    if (len >= (size_t)(2 * 1024 * 1024)) (void)madvise(p, len, MADV_HUGEPAGE);
#endif
    *out_size = len;
    return p;
}

/** 可写 mmap 整个文件（MAP_SHARED，写回磁盘）；path 须已存在且可写。用毕 fs_munmap。失败返回 NULL。 */
void *fs_mmap_rw_c(uint8_t *path, size_t *out_size) {
    if (!path || !out_size) return NULL;
    *out_size = 0;
    int fd = open((const char *)path, O_RDWR, 0);
    if (fd < 0) return NULL;
    struct stat st;
    if (fstat(fd, &st) != 0) { (void)close(fd); return NULL; }
    size_t len = (size_t)st.st_size;
    if (len == 0) { (void)close(fd); *out_size = 0; return NULL; }
    void *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    (void)close(fd);
    if (p == MAP_FAILED) return NULL;
#if defined(MADV_SEQUENTIAL)
    (void)madvise(p, len, MADV_SEQUENTIAL);
#endif
    *out_size = len;
    return p;
}

/** 解除 mmap；ptr/size 须为 fs_mmap_ro 返回的值。返回 0 成功，-1 失败。 */
int32_t fs_munmap_c(void *ptr, size_t size) {
    if (!ptr) return 0;
    return munmap(ptr, size) == 0 ? 0 : -1;
}

/** 只读 + O_DIRECT/无缓存 打开 path（Linux O_DIRECT；macOS fcntl F_NOCACHE）；失败返回 -1。调用方读时 buf 与 offset 须对齐 fs_direct_align()。 */
int32_t fs_open_read_direct_c(uint8_t *path) {
#if defined(__linux__)
    if (!path) return -1;
    int fd = open((const char *)path, O_RDONLY | O_DIRECT, 0);
    return fd >= 0 ? fd : -1;
#elif defined(__APPLE__) && defined(F_NOCACHE)
    if (!path) return -1;
    int fd = open((const char *)path, O_RDONLY, 0);
    if (fd < 0) return -1;
    if (fcntl(fd, F_NOCACHE, 1) != 0) { (void)close(fd); return -1; }
    return fd;
#else
    (void)path;
    return -1;
#endif
}

/** O_DIRECT 对齐要求（字节）；buf 与 offset 须为该值的整数倍。通常 4096。 */
uint64_t fs_direct_align_c(void) {
    return 4096;
}

/** 提示内核将 fd 视为顺序访问（POSIX_FADV_SEQUENTIAL），可激进预读与释放；仅 Linux 有效，其他平台 no-op；0 成功，-1 失败。 */
int32_t fs_fadvise_sequential_c(int32_t fd) {
#if defined(__linux__)
    return posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL) == 0 ? 0 : -1;
#else
    (void)fd;
    return 0;
#endif
}

/** 提示内核即将访问 [offset, offset+len)，可预取页；仅 Linux 有效，其他平台 no-op；0 成功，-1 失败。 */
int32_t fs_fadvise_willneed_c(int32_t fd, int64_t offset, size_t len) {
#if defined(__linux__)
    return posix_fadvise(fd, (off_t)offset, len, POSIX_FADV_WILLNEED) == 0 ? 0 : -1;
#else
    (void)fd;
    (void)offset;
    (void)len;
    return 0;
#endif
}

/** 零拷贝：从 fd_in 当前偏移复制 len 字节到 fd_out 当前偏移（Linux copy_file_range；macOS/其他 POSIX 读+写循环回退）；返回复制字节数，-1 失败。两 fd 偏移会前进。 */
int64_t fs_copy_file_range_c(int32_t fd_in, int32_t fd_out, size_t len) {
#if defined(__linux__)
    ssize_t n = copy_file_range(fd_in, NULL, fd_out, NULL, len, 0);
    return n >= 0 ? (int64_t)n : -1;
#else
    uint8_t buf[256 * 1024];
    size_t copied = 0;
    ssize_t nr, nw;
    while (copied < len) {
        size_t chunk = len - copied;
        if (chunk > sizeof(buf)) chunk = sizeof(buf);
        nr = read(fd_in, buf, chunk);
        if (nr <= 0) break;
        nw = write(fd_out, buf, (size_t)nr);
        if (nw != nr) { copied = (size_t)-1; break; }
        copied += (size_t)nr;
        if ((size_t)nr < chunk) break;
    }
    return (copied != (size_t)-1) ? (int64_t)copied : -1;
#endif
}

/** 分散读：一次 syscall 读入两段 [p0,l0] 与 [p1,l1]；返回总字节数，0=EOF，-1 错误。压榨 syscall。 */
int64_t fs_readv2_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1) {
    struct iovec iov[2];
    iov[0].iov_base = p0;
    iov[0].iov_len = l0;
    iov[1].iov_base = p1;
    iov[1].iov_len = l1;
    ssize_t n = readv(fd, iov, 2);
    return n >= 0 ? (int64_t)n : -1;
}

/** 集中写：一次 syscall 写出两段 [p0,l0] 与 [p1,l1]；返回总字节数，-1 错误。压榨 syscall。 */
int64_t fs_writev2_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1) {
    struct iovec iov[2];
    iov[0].iov_base = p0;
    iov[0].iov_len = l0;
    iov[1].iov_base = p1;
    iov[1].iov_len = l1;
    ssize_t n = writev(fd, iov, 2);
    return n >= 0 ? (int64_t)n : -1;
}

/** 零拷贝：从 in_fd 当前偏移发送 count 字节到 out_fd（Linux sendfile，常用于文件→socket）；返回发送字节数，-1 失败。in_fd 偏移会前进。 */
int64_t fs_sendfile_c(int32_t out_fd, int32_t in_fd, size_t count) {
#if defined(__linux__)
    ssize_t n = sendfile(out_fd, in_fd, NULL, count);
    return n >= 0 ? (int64_t)n : -1;
#else
    (void)out_fd;
    (void)in_fd;
    (void)count;
    return -1;
#endif
}

/** 范围刷盘（Linux sync_file_range）：将 [offset, offset+len) 从页缓存写回磁盘，不阻塞全文件 sync；0 成功，-1 失败。大文件顺序写时可重叠写+刷盘压榨吞吐。 */
int32_t fs_sync_range_c(int32_t fd, int64_t offset, size_t len) {
#if defined(__linux__)
    return sync_file_range(fd, (off_t)offset, (off_t)len, SYNC_FILE_RANGE_WRITE) == 0 ? 0 : -1;
#else
    (void)fd;
    (void)offset;
    (void)len;
    return 0;
#endif
}

/** 预分配文件空间 [offset, offset+len)（Linux fallocate）；减少大文件写时的碎片与元数据更新。0 成功，-1 失败。 */
int32_t fs_fallocate_c(int32_t fd, int64_t offset, int64_t len) {
#if defined(__linux__)
    return fallocate(fd, 0, (off_t)offset, (off_t)len) == 0 ? 0 : -1;
#else
    (void)fd;
    (void)offset;
    (void)len;
    return 0;
#endif
}

/** 追加写打开 path（不存在则创建）；失败返回 -1。 */
int32_t fs_open_append_c(uint8_t *path) {
    if (!path) return -1;
    return open((const char *)path, O_WRONLY | O_APPEND | O_CREAT, 0644);
}

/** 写打开 path，不存在则创建、存在则不截断；失败返回 -1。 */
int32_t fs_open_create_c(uint8_t *path) {
    if (!path) return -1;
    return open((const char *)path, O_WRONLY | O_CREAT, 0644);
}

/** 返回上次 fs_* 失败时的平台错误码（POSIX errno）。 */
int32_t fs_last_error_c(void) {
    return (int32_t)errno;
}

/** 包装 libc read，供 .su 的 fs_read 调用，避免与 std.io 的 read(handle,ptr,len,timeout) 同名。 */
int64_t fs_posix_read_c(int32_t fd, uint8_t *buf, size_t count) {
    return (int64_t)read((int)fd, buf, count);
}

/** 包装 libc write，供 .su 的 fs_write 调用。 */
int64_t fs_posix_write_c(int32_t fd, const uint8_t *buf, size_t count) {
    return (int64_t)write((int)fd, buf, count);
}

/** 分散读：一次 syscall 读入四段；返回总字节数，0=EOF，-1 错误。 */
int64_t fs_readv4_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3) {
    struct iovec iov[4];
    iov[0].iov_base = p0; iov[0].iov_len = l0;
    iov[1].iov_base = p1; iov[1].iov_len = l1;
    iov[2].iov_base = p2; iov[2].iov_len = l2;
    iov[3].iov_base = p3; iov[3].iov_len = l3;
    ssize_t n = readv(fd, iov, 4);
    return n >= 0 ? (int64_t)n : -1;
}

/** 集中写：一次 syscall 写出四段；返回总字节数，-1 错误。 */
int64_t fs_writev4_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3) {
    struct iovec iov[4];
    iov[0].iov_base = p0; iov[0].iov_len = l0;
    iov[1].iov_base = p1; iov[1].iov_len = l1;
    iov[2].iov_base = p2; iov[2].iov_len = l2;
    iov[3].iov_base = p3; iov[3].iov_len = l3;
    ssize_t n = writev(fd, iov, 4);
    return n >= 0 ? (int64_t)n : -1;
}

/** 与 Zig/Rust 对齐：按「指针+段数」分散读/集中写；bufs 与 .su Buffer ABI 一致，n 为 1..FS_IOV_BUF_MAX。 */
#define FS_IOV_BUF_MAX 16
typedef struct { uint8_t *ptr; size_t len; size_t handle; } fs_iovec_buf_t;

int64_t fs_readv_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n) {
    if (n <= 0 || n > FS_IOV_BUF_MAX || !bufs) return -1;
    {
        struct iovec iov[FS_IOV_BUF_MAX];
        int i;
        for (i = 0; i < n; i++) {
            iov[i].iov_base = (void *)bufs[i].ptr;
            iov[i].iov_len = bufs[i].len;
        }
        ssize_t r = readv(fd, iov, n);
        return r >= 0 ? (int64_t)r : -1;
    }
}

int64_t fs_writev_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n) {
    if (n <= 0 || n > FS_IOV_BUF_MAX || !bufs) return -1;
    {
        struct iovec iov[FS_IOV_BUF_MAX];
        int i;
        for (i = 0; i < n; i++) {
            iov[i].iov_base = (void *)bufs[i].ptr;
            iov[i].iov_len = bufs[i].len;
        }
        ssize_t r = writev(fd, iov, n);
        return r >= 0 ? (int64_t)r : -1;
    }
}
#endif
