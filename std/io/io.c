/**
 * std/io/io.c — 舒 IO 后端统一入口（分析/舒IO实现路线图.md 阶段 1/2）
 *
 * 与 std.io .su（core/driver/mod）同目录；供 std.io.core 调用的 C 侧读写实现。
 * 阶段 1：按平台接入 io_uring（Linux）/ kqueue（macOS）/ IOCP（Windows）；失败或不可用时回退到 read/write。
 * 链接用户程序（-o exe）时由编译器链入本目录产出的 io.o；Linux 下需 -luring -lpthread。
 *
 * 零拷贝：写路径（io_write）直接使用调用方 buf，无库内拷贝；读零拷贝由 io_read_ptr/io_read_ptr_len 提供，读入内部缓冲后返回只读指针，免用户态二次拷贝。
 */

#include <stddef.h>
#include <stdint.h>

#define IO_FIXED_MAX 8
/* 阶段 2 超越：ring 扩大；SQPOLL + fixed files 一步到位（路线图 §4.2） */
#define IO_URING_RING_ENTRIES 512
#define IO_FILES_MAX 32
/** 与 .su std.io.driver.Buffer ABI 一致（ptr+len+handle），供 io_read_batch_buf/io_write_batch_buf 接收「指针+段数」式调用（对齐 Zig/Rust 切片语义）。 */
#define IO_READV_BUF_MAX 16
typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_batch_buf_t;
#ifndef IOSQE_FIXED_FILE
#define IOSQE_FIXED_FILE 1u
#endif

#if defined(__linux__)
#include <liburing.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#ifndef __kernel_timespec
struct __kernel_timespec { long long tv_sec; long long tv_nsec; };
#endif
/* 极致压榨：每线程一个 io_uring，无全局锁；固定 buffer + 固定 files（SQPOLL 用）。 */
typedef struct {
    struct io_uring ring;
    int ok;
    int use_sqpoll;           /* 1=已用 SQPOLL 初始化并注册了 files，读写须走 fixed file */
    int registered_fds[IO_FILES_MAX];  /* 槽位 i 对应的 fd，-1 表示空 */
    struct iovec fixed_iov[IO_FIXED_MAX];
    unsigned fixed_nr;
    int fixed_ok;
} uring_thread_t;
static pthread_key_t g_uring_key;
static pthread_once_t g_uring_key_once = PTHREAD_ONCE_INIT;
static void uring_destructor(void *v) {
    uring_thread_t *ut = (uring_thread_t *)v;
    if (ut) {
        if (ut->fixed_ok) (void)io_uring_unregister_buffers(&ut->ring);
        ut->fixed_nr = 0;
        if (ut->use_sqpoll) (void)io_uring_unregister_files(&ut->ring);
        if (ut->ok) io_uring_queue_exit(&ut->ring);
        free(ut);
    }
}
static void uring_key_init(void) {
    (void)pthread_key_create(&g_uring_key, uring_destructor);
}
/** 为 SQPOLL 取 fd 对应的已注册槽位下标；若未注册则分配一槽并 register_files_update。无空槽返回 -1。 */
static int uring_get_fd_slot(uring_thread_t *ut, int fd) {
    int i;
    for (i = 0; i < IO_FILES_MAX; i++)
        if (ut->registered_fds[i] == fd) return i;
    for (i = 0; i < IO_FILES_MAX; i++) {
        if (ut->registered_fds[i] != -1) continue;
        if (io_uring_register_files_update(&ut->ring, i, &fd, 1) == 1) {
            ut->registered_fds[i] = fd;
            return i;
        }
        return -1;
    }
    return -1;
}
/** 返回当前线程的 uring；首次调用时尝试 SQPOLL + fixed files，失败则回退普通 ring。 */
static uring_thread_t *uring_get_thread(void) {
    uring_thread_t *ut;
    int i;
    (void)pthread_once(&g_uring_key_once, uring_key_init);
    ut = (uring_thread_t *)pthread_getspecific(g_uring_key);
    if (ut == NULL) {
        ut = (uring_thread_t *)calloc(1, sizeof(*ut));
        if (ut) {
            unsigned flags = 0;
            int r;
            for (i = 0; i < IO_FILES_MAX; i++) ut->registered_fds[i] = -1;
#ifdef IORING_SETUP_DEFER_TASKRUN
            flags = IORING_SETUP_DEFER_TASKRUN;
# ifdef IORING_SETUP_SINGLE_ISSUER
            flags |= IORING_SETUP_SINGLE_ISSUER;
# endif
#endif
#ifdef IORING_SETUP_SQPOLL
            {
                int init_fds[IO_FILES_MAX];
                init_fds[0] = 0; init_fds[1] = 1; init_fds[2] = 2;
                for (i = 3; i < IO_FILES_MAX; i++) init_fds[i] = -1;
                r = io_uring_queue_init(IO_URING_RING_ENTRIES, &ut->ring, flags | IORING_SETUP_SQPOLL);
                if (r >= 0 && io_uring_register_files(&ut->ring, init_fds, IO_FILES_MAX) >= 0) {
                    ut->ok = 1;
                    ut->use_sqpoll = 1;
                    ut->registered_fds[0] = 0; ut->registered_fds[1] = 1; ut->registered_fds[2] = 2;
                    pthread_setspecific(g_uring_key, ut);
                    return ut;
                }
                if (r >= 0) (void)io_uring_queue_exit(&ut->ring);
            }
#endif
            r = io_uring_queue_init(IO_URING_RING_ENTRIES, &ut->ring, flags);
            if (r < 0 && flags != 0)
                r = io_uring_queue_init(IO_URING_RING_ENTRIES, &ut->ring, 0);
            ut->ok = (r >= 0) ? 1 : 0;
            pthread_setspecific(g_uring_key, ut);
        }
    }
    return ut;
}

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
/* 阶段 1 性能压榨：Linux 上 accept/connect 走 io_uring，供 std.net 调用；与 uring 共用同一 ring，超越 Zig 典型用法。 */

/** 单次 accept 走 io_uring；timeout_ms 毫秒（0=无超时）。返回 client fd，失败 -1；client 已设非阻塞。阶段 4：SQPOLL 时 listener 走 fixed file 槽，减少 uring 开销。 */
int32_t io_uring_accept(int listener_fd, unsigned timeout_ms) {
    uring_thread_t *ut = uring_get_thread();
    if (!ut || !ut->ok) return -1;
    struct io_uring *ring = &ut->ring;
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    if (!sqe) return -1;
    io_uring_prep_accept(sqe, listener_fd, NULL, NULL, 0);
    if (ut->use_sqpoll) {
        int slot = uring_get_fd_slot(ut, listener_fd);
        if (slot >= 0) { sqe->fd = (unsigned)slot; sqe->flags |= (unsigned)IOSQE_FIXED_FILE; }
    }
    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)listener_fd);
    struct io_uring_cqe *cqe = NULL;
    struct io_uring_cqe *cqe_ptrs[1];
    if (timeout_ms == 0) {
        if (io_uring_submit_and_wait(ring, 1) != 1) return -1;
        if (io_uring_peek_batch_cqe(ring, cqe_ptrs, 1) < 1) return -1;
        cqe = cqe_ptrs[0];
    } else {
        if (io_uring_submit(ring, 1) != 1) return -1;
        struct __kernel_timespec ts;
        ts.tv_sec = (long long)(timeout_ms / 1000u);
        ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
        if (io_uring_wait_cqe_timeout(ring, &cqe, &ts) != 0) return -1;
    }
    int res = (int)cqe->res;
    io_uring_cqe_seen(ring, cqe);
    if (res < 0) return -1;
    int fd = res;
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0) (void)fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return (int32_t)fd;
}

/** 单次 connect 走 io_uring；addr_u32 主机序 (a<<24)|(b<<16)|(c<<8)|d，port_u32 取低 16 位。返回 fd，失败 -1；socket 已非阻塞。 */
int32_t io_uring_connect(uint32_t addr_u32, uint32_t port_u32, unsigned timeout_ms) {
    int fd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0) { (void)close(fd); return -1; }
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(addr_u32);
    sin.sin_port = htons((uint16_t)(port_u32 & 0xFFFFu));
    uring_thread_t *ut = uring_get_thread();
    if (!ut || !ut->ok) {
        (void)close(fd);
        return -1;
    }
    struct io_uring *ring = &ut->ring;
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    if (!sqe) { (void)close(fd); return -1; }
    io_uring_prep_connect(sqe, fd, (struct sockaddr *)&sin, sizeof(sin));
    if (ut->use_sqpoll) {
        int slot = uring_get_fd_slot(ut, fd);
        if (slot >= 0) { sqe->fd = (unsigned)slot; sqe->flags |= (unsigned)IOSQE_FIXED_FILE; }
    }
    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
    struct io_uring_cqe *cqe = NULL;
    struct io_uring_cqe *cqe_ptrs[1];
    if (timeout_ms == 0) {
        if (io_uring_submit_and_wait(ring, 1) != 1) { (void)close(fd); return -1; }
        if (io_uring_peek_batch_cqe(ring, cqe_ptrs, 1) < 1) { (void)close(fd); return -1; }
        cqe = cqe_ptrs[0];
    } else {
        if (io_uring_submit(ring, 1) != 1) { (void)close(fd); return -1; }
        struct __kernel_timespec ts;
        ts.tv_sec = (long long)(timeout_ms / 1000u);
        ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
        if (io_uring_wait_cqe_timeout(ring, &cqe, &ts) != 0) { (void)close(fd); return -1; }
    }
    int res = (int)cqe->res;
    io_uring_cqe_seen(ring, cqe);
    if (res != 0) { (void)close(fd); return -1; }
    return (int32_t)fd;
}

#define IO_NET_BATCH_MAX 64
/** 阶段 2 性能压榨：一次提交 N 个 accept SQE，一次收割 N 个 CQE；out_fds 填满成功得到的 client fd，已设非阻塞。返回实际数量。阶段 4：SQPOLL 时 listener 走 fixed file。收割用 peek_batch 一次取齐 CQE，减少 wait_cqe 次数。 */
int io_uring_accept_many(int listener_fd, int32_t *out_fds, int n, unsigned timeout_ms) {
    (void)timeout_ms;
    if (n <= 0 || n > IO_NET_BATCH_MAX || !out_fds) return 0;
    uring_thread_t *ut = uring_get_thread();
    if (!ut || !ut->ok) return 0;
    struct io_uring *ring = &ut->ring;
    int listener_slot = -1;
    if (ut->use_sqpoll) listener_slot = uring_get_fd_slot(ut, listener_fd);
    int i;
    for (i = 0; i < n; i++) {
        struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
        if (!sqe) break;
        io_uring_prep_accept(sqe, listener_fd, NULL, NULL, 0);
        if (listener_slot >= 0) { sqe->fd = (unsigned)listener_slot; sqe->flags |= (unsigned)IOSQE_FIXED_FILE; }
        io_uring_sqe_set_data(sqe, (void *)(uintptr_t)i);
    }
    n = i;
    if (n == 0) return 0;
    int submitted = io_uring_submit_and_wait(ring, n);
    if (submitted <= 0) return 0;
    struct io_uring_cqe *cqe_ptrs[IO_NET_BATCH_MAX];
    int reaped = io_uring_peek_batch_cqe(ring, cqe_ptrs, submitted);
    int count = 0;
    for (i = 0; i < reaped; i++) {
        struct io_uring_cqe *cqe = cqe_ptrs[i];
        int res = (int)cqe->res;
        io_uring_cqe_seen(ring, cqe);
        if (res >= 0) {
            int fd = res;
            int flags = fcntl(fd, F_GETFL, 0);
            if (flags >= 0) (void)fcntl(fd, F_SETFL, flags | O_NONBLOCK);
            out_fds[count++] = (int32_t)fd;
        }
    }
    return count;
}

/** 阶段 2 性能压榨：一次提交 N 个 connect SQE，一次收割 N 个 CQE；out_fds 填满成功的 fd。返回实际成功数量。 */
int io_uring_connect_many(uint32_t addr_u32, uint32_t port_u32, int32_t *out_fds, int n, unsigned timeout_ms) {
    if (n <= 0 || n > IO_NET_BATCH_MAX || !out_fds) return 0;
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(addr_u32);
    sin.sin_port = htons((uint16_t)(port_u32 & 0xFFFFu));
    int fds[IO_NET_BATCH_MAX];
    int i;
    for (i = 0; i < n; i++) {
        fds[i] = (int)socket(AF_INET, SOCK_STREAM, 0);
        if (fds[i] < 0) break;
        int flags = fcntl(fds[i], F_GETFL, 0);
        if (flags < 0 || fcntl(fds[i], F_SETFL, flags | O_NONBLOCK) != 0) {
            (void)close(fds[i]);
            break;
        }
    }
    n = i;
    if (n == 0) return 0;
    uring_thread_t *ut = uring_get_thread();
    if (!ut || !ut->ok) {
        for (i = 0; i < n; i++) (void)close(fds[i]);
        return 0;
    }
    struct io_uring *ring = &ut->ring;
    for (i = 0; i < n; i++) {
        struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
        if (!sqe) { for (; i < n; i++) (void)close(fds[i]); return 0; }
        io_uring_prep_connect(sqe, fds[i], (struct sockaddr *)&sin, sizeof(sin));
        if (ut->use_sqpoll) {
            int slot = uring_get_fd_slot(ut, fds[i]);
            if (slot >= 0) { sqe->fd = (unsigned)slot; sqe->flags |= (unsigned)IOSQE_FIXED_FILE; }
        }
        io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fds[i]);
    }
    int submitted = io_uring_submit_and_wait(ring, n);
    if (submitted <= 0) {
        for (i = 0; i < n; i++) (void)close(fds[i]);
        return 0;
    }
    struct io_uring_cqe *cqe_ptrs[IO_NET_BATCH_MAX];
    int reaped = io_uring_peek_batch_cqe(ring, cqe_ptrs, submitted);
    int count = 0;
    for (i = 0; i < reaped; i++) {
        struct io_uring_cqe *cqe = cqe_ptrs[i];
        int res = (int)cqe->res;
        int fd = (int)(intptr_t)io_uring_cqe_get_data(cqe);
        io_uring_cqe_seen(ring, cqe);
        if (res == 0)
            out_fds[count++] = (int32_t)fd;
        else
            (void)close(fd);
    }
    return count;
}

#endif

#if defined(__APPLE__)
#include <sys/event.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
/* 再压榨：每线程一个 kqueue，无全局锁、无竞争；线程退出时 destructor 关闭 fd */
static pthread_key_t g_kq_key;
static pthread_once_t g_kq_key_once = PTHREAD_ONCE_INIT;
static void kq_destructor(void *v) {
    int kq = (v == NULL) ? -1 : ((int)(intptr_t)v) - 1;
    if (kq >= 0) (void)close(kq);
}
static void kq_key_init(void) {
    (void)pthread_key_create(&g_kq_key, kq_destructor);
}
static int kq_get(void) {
    int kq;
    (void)pthread_once(&g_kq_key_once, kq_key_init);
    /* 存 (kq+1) 以区分「未设置」(NULL→0) 与有效 fd 0 */
    kq = (int)(intptr_t)pthread_getspecific(g_kq_key);
    kq = (kq <= 0) ? -1 : (kq - 1);
    if (kq < 0) {
        kq = kqueue();
        if (kq >= 0)
            pthread_setspecific(g_kq_key, (void *)(intptr_t)(kq + 1));
    }
    return kq;
}
#include <sys/uio.h>
/* 固定 buffer 池（最多 IO_FIXED_MAX 块）：非 Linux 无 io_uring_register，仅存 iov[] 供 read_fixed/write_fixed 走普通 read/write */
#define IO_FIXED_MAX_APPLE 8
typedef struct { struct iovec iov[IO_FIXED_MAX_APPLE]; unsigned nr; } fixed_pool_t;
static pthread_key_t g_fixed_key;
static pthread_once_t g_fixed_key_once = PTHREAD_ONCE_INIT;
static void fixed_destructor(void *v) { free(v); }
static void fixed_key_init(void) { (void)pthread_key_create(&g_fixed_key, fixed_destructor); }
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#ifndef FILE_SKIP_COMPLETION_PORT_ON_SUCCESS
#define FILE_SKIP_COMPLETION_PORT_ON_SUCCESS 1
#endif
/* 全局完成端口，首次使用时创建 */
static HANDLE g_iocp = NULL;
static CRITICAL_SECTION g_iocp_cs;
static int g_iocp_cs_init = 0;
/* 阶段 2 超越：OVERLAPPED 池扩为 8，支持更大批量（路线图 §4.4）；与 Linux 8 段 batch 同思路 */
#define IO_BATCH_MAX_WIN 8
typedef struct { OVERLAPPED ov_read[IO_BATCH_MAX_WIN]; OVERLAPPED ov_write[IO_BATCH_MAX_WIN]; } win_ov_thread_t;
static DWORD g_win_tls_idx = TLS_OUT_OF_INDEXES;
static CRITICAL_SECTION g_win_tls_cs;
static int g_win_tls_cs_init = 0;
static win_ov_thread_t *win_get_thread_ov(void) {
    win_ov_thread_t *ov;
    if (g_win_tls_cs_init == 0) { InitializeCriticalSection(&g_win_tls_cs); g_win_tls_cs_init = 1; }
    EnterCriticalSection(&g_win_tls_cs);
    if (g_win_tls_idx == TLS_OUT_OF_INDEXES)
        g_win_tls_idx = TlsAlloc();
    LeaveCriticalSection(&g_win_tls_cs);
    if (g_win_tls_idx == TLS_OUT_OF_INDEXES) return NULL;
    ov = (win_ov_thread_t *)TlsGetValue(g_win_tls_idx);
    if (ov == NULL) {
        ov = (win_ov_thread_t *)calloc(1, sizeof(*ov));
        if (ov) TlsSetValue(g_win_tls_idx, ov);
    }
    return ov;
}
/* 最多缓存 2 个 handle 的 SetFileCompletionNotificationModes */
static HANDLE g_win_skip_handle[2] = { NULL, NULL };
static unsigned g_win_skip_next = 0;
static int win_handle_skip_set(HANDLE h) {
    if (h == g_win_skip_handle[0] || h == g_win_skip_handle[1]) return 1;
    if (SetFileCompletionNotificationModes(h, FILE_SKIP_COMPLETION_PORT_ON_SUCCESS)) {
        g_win_skip_handle[g_win_skip_next] = h;
        g_win_skip_next = 1u - g_win_skip_next;
        return 1;
    }
    return 0;
}
static void win_zero_overlapped(OVERLAPPED *ov, int count) {
    int j;
    for (j = 0; j < count; j++) {
        ov[j].Internal = 0;
        ov[j].InternalHigh = 0;
        ov[j].Offset = 0;
        ov[j].OffsetHigh = 0;
        ov[j].hEvent = NULL;
    }
}
/* 固定 buffer 池（最多 8 块）：Windows 无 io_uring，TLS 存 base[]/len[] 供 read_fixed/write_fixed 走普通 read/write */
#define IO_FIXED_MAX_WIN 8
typedef struct { void *base[IO_FIXED_MAX_WIN]; size_t len[IO_FIXED_MAX_WIN]; unsigned nr; } win_fixed_pool_t;
static DWORD g_win_fixed_tls_idx = TLS_OUT_OF_INDEXES;
static CRITICAL_SECTION g_win_fixed_cs;
static int g_win_fixed_cs_init = 0;
static win_fixed_pool_t *win_get_fixed_pool(void) {
    if (g_win_fixed_cs_init == 0) { InitializeCriticalSection(&g_win_fixed_cs); g_win_fixed_cs_init = 1; }
    EnterCriticalSection(&g_win_fixed_cs);
    if (g_win_fixed_tls_idx == TLS_OUT_OF_INDEXES)
        g_win_fixed_tls_idx = TlsAlloc();
    LeaveCriticalSection(&g_win_fixed_cs);
    if (g_win_fixed_tls_idx == TLS_OUT_OF_INDEXES) return NULL;
    return (win_fixed_pool_t *)TlsGetValue(g_win_fixed_tls_idx);
}
#endif

#if !defined(_WIN32) && !defined(_WIN64)
#include <unistd.h>
#include <sys/uio.h>
#include <poll.h>
#define FALLBACK_READ(fd, buf, count)   ((ptrdiff_t)read((int)(fd), (void *)(buf), (size_t)(count)))
#define FALLBACK_WRITE(fd, buf, count)  ((ptrdiff_t)write((int)(fd), (const void *)(buf), (size_t)(count)))
#else
#define FALLBACK_READ(fd, buf, count)  ((ptrdiff_t)_read((int)(fd), (void *)(buf), (unsigned)(count)))
#define FALLBACK_WRITE(fd, buf, count) ((ptrdiff_t)_write((int)(fd), (const void *)(buf), (unsigned)(count)))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** IO 读：fd 为 handle（0=stdin，≥2 为任意 fd）；timeout_ms 毫秒，0=无超时。返回读入字节数，0=EOF，-1=错误/超时。 */
ptrdiff_t io_read(int fd, uint8_t *buf, size_t count, unsigned timeout_ms) {
#if defined(__linux__)
    {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            int use_idx = -1;
            if (ut->use_sqpoll) {
                use_idx = uring_get_fd_slot(ut, fd);
                if (use_idx < 0) return FALLBACK_READ(fd, buf, count);
            }
            {
                struct io_uring *ring = &ut->ring;
                struct io_uring_sqe *sqe;
                struct io_uring_cqe *cqe;
                struct io_uring_cqe *cqe_ptrs[1];
                struct __kernel_timespec ts;
                if (timeout_ms > 0) {
                    ts.tv_sec = (long long)(timeout_ms / 1000u);
                    ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
                }
                sqe = io_uring_get_sqe(ring);
                if (sqe) {
                    if (use_idx >= 0) {
                        io_uring_prep_read(sqe, use_idx, buf, count, 0);
                        sqe->flags |= (unsigned)IOSQE_FIXED_FILE;
                    } else {
                        io_uring_prep_read(sqe, fd, buf, count, 0);
                    }
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (timeout_ms == 0) {
                    if (io_uring_submit_and_wait(ring, 1) == 1) {
                        unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                        if (got >= 1) {
                            cqe = cqe_ptrs[0];
                            ptrdiff_t res = (ptrdiff_t)cqe->res;
                            io_uring_cqe_seen(ring, cqe);
                            return res >= 0 ? res : -1;
                        }
                        return -1;
                    }
                } else {
                    if (io_uring_submit(ring, 1) == 1) {
                        int wait_ret = io_uring_wait_cqe_timeout(ring, &cqe, &ts);
                        if (wait_ret == 0 && cqe) {
                            ptrdiff_t res = (ptrdiff_t)cqe->res;
                            io_uring_cqe_seen(ring, cqe);
                            return res >= 0 ? res : -1;
                        }
                        if (cqe) io_uring_cqe_seen(ring, cqe);
                        return -1;
                    }
                }
            }
            }
        }
    }
    return FALLBACK_READ(fd, buf, count);
#endif

#if defined(__APPLE__)
    if (fd >= 3) {
        int kq = kq_get();
        if (kq >= 0) {
            struct kevent ev, ev_out;
            struct timespec ts_abs, *pts = NULL;
            if (timeout_ms > 0) {
                ts_abs.tv_sec = (timeout_ms / 1000u);
                ts_abs.tv_nsec = (long)((timeout_ms % 1000u) * 1000000u);
                pts = &ts_abs;
            }
            /* EV_CLEAR：取到事件后自动清除状态，减少重复/伪触发（再压榨） */
            EV_SET(&ev, (uintptr_t)fd, EVFILT_READ, EV_ADD | EV_ONESHOT | EV_CLEAR, 0, 0, 0);
            if (kevent(kq, &ev, 1, NULL, 0, pts) >= 0 &&
                kevent(kq, NULL, 0, &ev_out, 1, pts) >= 0)
                return (ptrdiff_t)read(fd, buf, count);
        }
    }
    return FALLBACK_READ(fd, buf, count);
#endif

#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD wait_ms = (timeout_ms == 0) ? INFINITE : (DWORD)timeout_ms;
        HANDLE h = (HANDLE)_get_osfhandle(fd);
        if (h != INVALID_HANDLE_VALUE) {
            if (g_iocp == NULL) {
                if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
                EnterCriticalSection(&g_iocp_cs);
                if (g_iocp == NULL)
                    g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
                LeaveCriticalSection(&g_iocp_cs);
            }
            if (g_iocp) {
                CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                OVERLAPPED ov = { 0 };
                if (ReadFile(h, buf, (DWORD)(count > 0x7FFFFFFFu ? 0x7FFFFFFFu : count), NULL, &ov)) {
                    DWORD bytes = 0;
                    GetOverlappedResult(h, &ov, &bytes, TRUE);
                    return (ptrdiff_t)bytes;
                }
                if (GetLastError() == ERROR_IO_PENDING) {
                    DWORD bytes = 0;
                    ULONG_PTR key;
                    LPOVERLAPPED pov = NULL;
                    if (GetQueuedCompletionStatus(g_iocp, &bytes, &key, &pov, wait_ms) && pov)
                        return (ptrdiff_t)bytes;
                    return -1; /* 超时或错误 */
                }
            }
        }
    }
    return FALLBACK_READ(fd, buf, count);
#endif

#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    (void)timeout_ms;
    return FALLBACK_READ(fd, buf, count);
#endif
}

/** IO 写：fd 为 handle（1=stdout，≥2 为任意 fd）；timeout_ms 毫秒，0=无超时。返回写入字节数，-1=错误/超时。 */
ptrdiff_t io_write(int fd, const uint8_t *buf, size_t count, unsigned timeout_ms) {
#if defined(__linux__)
    {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            int use_idx = -1;
            if (ut->use_sqpoll) {
                use_idx = uring_get_fd_slot(ut, fd);
                if (use_idx < 0) return FALLBACK_WRITE(fd, buf, count);
            }
            {
                struct io_uring *ring = &ut->ring;
                struct io_uring_sqe *sqe;
                struct io_uring_cqe *cqe;
                struct io_uring_cqe *cqe_ptrs[1];
                struct __kernel_timespec ts;
                if (timeout_ms > 0) {
                    ts.tv_sec = (long long)(timeout_ms / 1000u);
                    ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
                }
                sqe = io_uring_get_sqe(ring);
                if (sqe) {
                    if (use_idx >= 0) {
                        io_uring_prep_write(sqe, use_idx, (void *)buf, count, 0);
                        sqe->flags |= (unsigned)IOSQE_FIXED_FILE;
                    } else {
                        io_uring_prep_write(sqe, fd, (void *)buf, count, 0);
                    }
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (timeout_ms == 0) {
                    if (io_uring_submit_and_wait(ring, 1) == 1) {
                        unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                        if (got >= 1) {
                            cqe = cqe_ptrs[0];
                            ptrdiff_t res = (ptrdiff_t)cqe->res;
                            io_uring_cqe_seen(ring, cqe);
                            return res >= 0 ? res : -1;
                        }
                        return -1;
                    }
                } else {
                    if (io_uring_submit(ring, 1) == 1) {
                        int wait_ret = io_uring_wait_cqe_timeout(ring, &cqe, &ts);
                        if (wait_ret == 0 && cqe) {
                            ptrdiff_t res = (ptrdiff_t)cqe->res;
                            io_uring_cqe_seen(ring, cqe);
                            return res >= 0 ? res : -1;
                        }
                        if (cqe) io_uring_cqe_seen(ring, cqe);
                        return -1;
                    }
                }
            }
            }
        }
    }
    return FALLBACK_WRITE(fd, buf, count);
#endif

#if defined(__APPLE__)
    if (fd >= 3) {
        int kq = kq_get();
        if (kq >= 0) {
            struct kevent ev, ev_out;
            struct timespec ts_abs, *pts = NULL;
            if (timeout_ms > 0) {
                ts_abs.tv_sec = (timeout_ms / 1000u);
                ts_abs.tv_nsec = (long)((timeout_ms % 1000u) * 1000000u);
                pts = &ts_abs;
            }
            EV_SET(&ev, (uintptr_t)fd, EVFILT_WRITE, EV_ADD | EV_ONESHOT | EV_CLEAR, 0, 0, 0);
            if (kevent(kq, &ev, 1, NULL, 0, pts) >= 0 &&
                kevent(kq, NULL, 0, &ev_out, 1, pts) >= 0)
                return (ptrdiff_t)write(fd, buf, count);
        }
    }
    return FALLBACK_WRITE(fd, buf, count);
#endif

#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD wait_ms = (timeout_ms == 0) ? INFINITE : (DWORD)timeout_ms;
        HANDLE h = (HANDLE)_get_osfhandle(fd);
        if (h != INVALID_HANDLE_VALUE && g_iocp) {
            CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
            OVERLAPPED ov = { 0 };
            if (WriteFile(h, buf, (DWORD)(count > 0x7FFFFFFFu ? 0x7FFFFFFFu : count), NULL, &ov)) {
                DWORD bytes = 0;
                GetOverlappedResult(h, &ov, &bytes, TRUE);
                return (ptrdiff_t)bytes;
            }
            if (GetLastError() == ERROR_IO_PENDING) {
                DWORD bytes = 0;
                if (GetOverlappedResultEx(h, &ov, &bytes, wait_ms, 0))
                    return (ptrdiff_t)bytes;
                return -1; /* 超时或错误 */
            }
        }
    }
    return FALLBACK_WRITE(fd, buf, count);
#endif

#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    (void)timeout_ms;
    return FALLBACK_WRITE(fd, buf, count);
#endif
}

/** 批量读：最多 4 段 (p0,l0)..(p3,l3)，n 为实际段数（1..4）。timeout_ms=0 时 Linux 用 io_uring 一次提交 n 个 SQE（阶段 2 起步），POSIX 非 Linux 用 readv。 */
ptrdiff_t io_read_batch(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, int n, unsigned timeout_ms) {
    if (n <= 0 || n > 4) return -1;
    if (n == 1) return io_read(fd, p0, l0, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0 && n >= 2) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[4];
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[1];
            iov[0].iov_base = (void *)p0; iov[0].iov_len = l0;
            iov[1].iov_base = (void *)p1; iov[1].iov_len = l1;
            if (n >= 3) { iov[2].iov_base = (void *)p2; iov[2].iov_len = l2; }
            if (n >= 4) { iov[3].iov_base = (void *)p3; iov[3].iov_len = l3; }
            sqe = io_uring_get_sqe(ring);
            if (sqe) {
                io_uring_prep_readv(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
        }
    }
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[4];
            int i, submitted;
            uint8_t *ps[4] = { p0, p1, p2, p3 };
            size_t ls[4] = { l0, l1, l2, l3 };
            if (io_uring_sq_space_left(ring) >= (unsigned)n) {
                for (i = 0; i < n; i++) {
                    sqe = io_uring_get_sqe(ring);
                    if (!sqe) break;
                    io_uring_prep_read(sqe, fd, ps[i], ls[i], 0);
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)i);
                }
                if (i == n && (submitted = io_uring_submit_and_wait(ring, n)) == n) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, (unsigned)n);
                    if (got >= (unsigned)n) {
                        ptrdiff_t total = 0;
                        for (i = 0; i < n; i++) {
                            if (cqe_ptrs[i]->res < 0) {
                                for (i = 0; i < n; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                                return -1;
                            }
                            total += (ptrdiff_t)cqe_ptrs[i]->res;
                            io_uring_cqe_seen(ring, cqe_ptrs[i]);
                        }
                        return total;
                    }
                    for (i = 0; i < (int)got; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL)
                g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_read, n);
                {
                    uint8_t *ps[4] = { p0, p1, p2, p3 };
                    size_t ls[4] = { l0, l1, l2, l3 };
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(ls[i] > 0x7FFFFFFFu ? 0x7FFFFFFFu : ls[i]);
                        if (ReadFile(h, ps[i], ulen, NULL, &ovt->ov_read[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_read[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING)
                            issued++;
                        else
                            break;
                    }
                    if (issued == n) {
                        int need = n - sync_count;
                        OVERLAPPED_ENTRY entries[4];
                        ULONG removed;
                        int got = 0;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, 4, &removed, INFINITE, FALSE))
                                break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE))
                                    return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need)
                            return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[4];
        iov[0].iov_base = (void *)p0; iov[0].iov_len = l0;
        if (n >= 2) { iov[1].iov_base = (void *)p1; iov[1].iov_len = l1; }
        if (n >= 3) { iov[2].iov_base = (void *)p2; iov[2].iov_len = l2; }
        if (n >= 4) { iov[3].iov_base = (void *)p3; iov[3].iov_len = l3; }
        ptrdiff_t r = (ptrdiff_t)readv(fd, iov, n);
        return r;
    }
#endif
    /* 带超时或非批量路径：逐段读 */
    ptrdiff_t total = 0;
    ptrdiff_t r0 = io_read(fd, p0, l0, timeout_ms);
    if (r0 < 0) return -1;
    total += r0;
    if (n == 1) return total;
    ptrdiff_t r1 = io_read(fd, p1, l1, timeout_ms);
    if (r1 < 0) return -1;
    total += r1;
    if (n == 2) return total;
    ptrdiff_t r2 = io_read(fd, p2, l2, timeout_ms);
    if (r2 < 0) return -1;
    total += r2;
    if (n == 3) return total;
    ptrdiff_t r3 = io_read(fd, p3, l3, timeout_ms);
    if (r3 < 0) return -1;
    return total + r3;
}

/** 批量写：最多 4 段；timeout_ms=0 时 Linux 用 io_uring prep_writev 单 SQE（n>=2）或 n×write，POSIX 用 writev。 */
ptrdiff_t io_write_batch(int fd, const uint8_t *p0, size_t l0, const uint8_t *p1, size_t l1, const uint8_t *p2, size_t l2, const uint8_t *p3, size_t l3, int n, unsigned timeout_ms) {
    if (n <= 0 || n > 4) return -1;
    if (n == 1) return io_write(fd, p0, l0, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0 && n >= 2) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[4];
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[1];
            iov[0].iov_base = (void *)p0; iov[0].iov_len = l0;
            iov[1].iov_base = (void *)p1; iov[1].iov_len = l1;
            if (n >= 3) { iov[2].iov_base = (void *)p2; iov[2].iov_len = l2; }
            if (n >= 4) { iov[3].iov_base = (void *)p3; iov[3].iov_len = l3; }
            sqe = io_uring_get_sqe(ring);
            if (sqe) {
                io_uring_prep_writev(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
        }
    }
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[4];
            int i, submitted;
            const uint8_t *ps[4] = { p0, p1, p2, p3 };
            size_t ls[4] = { l0, l1, l2, l3 };
            if (io_uring_sq_space_left(ring) >= (unsigned)n) {
                for (i = 0; i < n; i++) {
                    sqe = io_uring_get_sqe(ring);
                    if (!sqe) break;
                    io_uring_prep_write(sqe, fd, ps[i], ls[i], 0);
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)i);
                }
                if (i == n && (submitted = io_uring_submit_and_wait(ring, n)) == n) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, (unsigned)n);
                    if (got >= (unsigned)n) {
                        ptrdiff_t total = 0;
                        for (i = 0; i < n; i++) {
                            if (cqe_ptrs[i]->res < 0) {
                                for (i = 0; i < n; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                                return -1;
                            }
                            total += (ptrdiff_t)cqe_ptrs[i]->res;
                            io_uring_cqe_seen(ring, cqe_ptrs[i]);
                        }
                        return total;
                    }
                    for (i = 0; i < (int)got; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL)
                g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_write, n);
                {
                    const uint8_t *ps[4] = { p0, p1, p2, p3 };
                    size_t ls[4] = { l0, l1, l2, l3 };
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(ls[i] > 0x7FFFFFFFu ? 0x7FFFFFFFu : ls[i]);
                        if (WriteFile(h, ps[i], ulen, NULL, &ovt->ov_write[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_write[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING)
                            issued++;
                        else
                            break;
                    }
                    if (issued == n) {
                        int need = n - sync_count;
                        OVERLAPPED_ENTRY entries[4];
                        ULONG removed;
                        int got = 0;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, 4, &removed, INFINITE, FALSE))
                                break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE))
                                    return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need)
                            return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[4];
        iov[0].iov_base = (void *)p0; iov[0].iov_len = l0;
        if (n >= 2) { iov[1].iov_base = (void *)p1; iov[1].iov_len = l1; }
        if (n >= 3) { iov[2].iov_base = (void *)p2; iov[2].iov_len = l2; }
        if (n >= 4) { iov[3].iov_base = (void *)p3; iov[3].iov_len = l3; }
        ptrdiff_t r = (ptrdiff_t)writev(fd, iov, n);
        return r;
    }
#endif
    ptrdiff_t total = 0;
    ptrdiff_t r0 = io_write(fd, p0, l0, timeout_ms);
    if (r0 < 0) return -1;
    total += r0;
    if (n == 1) return total;
    ptrdiff_t r1 = io_write(fd, p1, l1, timeout_ms);
    if (r1 < 0) return -1;
    total += r1;
    if (n == 2) return total;
    ptrdiff_t r2 = io_write(fd, p2, l2, timeout_ms);
    if (r2 < 0) return -1;
    total += r2;
    if (n == 3) return total;
    ptrdiff_t r3 = io_write(fd, p3, l3, timeout_ms);
    if (r3 < 0) return -1;
    return total + r3;
}

/** 阶段 2 超越：批量读最多 8 段（路线图 §4.2 更大批量）；C 侧 API，.su 仍用 4 段 batch。n 为 1..8。 */
ptrdiff_t io_read_batch_8(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3,
    uint8_t *p4, size_t l4, uint8_t *p5, size_t l5, uint8_t *p6, size_t l6, uint8_t *p7, size_t l7,
    int n, unsigned timeout_ms) {
    if (n <= 0 || n > 8) return -1;
    if (n <= 4) return io_read_batch(fd, p0, l0, p1, l1, p2, l2, p3, l3, n, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[8];
            uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
            size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[8];
            int i, submitted;
            for (i = 0; i < n; i++) { iov[i].iov_base = (void *)ps[i]; iov[i].iov_len = ls[i]; }
            sqe = io_uring_get_sqe(ring);
            if (sqe && n >= 2) {
                io_uring_prep_readv(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
            if (io_uring_sq_space_left(ring) >= (unsigned)n) {
                for (i = 0; i < n; i++) {
                    sqe = io_uring_get_sqe(ring);
                    if (!sqe) break;
                    io_uring_prep_read(sqe, fd, ps[i], ls[i], 0);
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)i);
                }
                if (i == n && (submitted = io_uring_submit_and_wait(ring, n)) == n) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, (unsigned)n);
                    if (got >= (unsigned)n) {
                        ptrdiff_t total = 0;
                        for (i = 0; i < n; i++) {
                            if (cqe_ptrs[i]->res < 0) {
                                for (i = 0; i < n; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                                return -1;
                            }
                            total += (ptrdiff_t)cqe_ptrs[i]->res;
                            io_uring_cqe_seen(ring, cqe_ptrs[i]);
                        }
                        return total;
                    }
                    for (i = 0; i < (int)got; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL)
                g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_read, n);
                {
                    uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
                    size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    OVERLAPPED_ENTRY entries[IO_BATCH_MAX_WIN];
                    ULONG removed;
                    int got = 0, need;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(ls[i] > 0x7FFFFFFFu ? 0x7FFFFFFFu : ls[i]);
                        if (ReadFile(h, ps[i], ulen, NULL, &ovt->ov_read[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_read[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING)
                            issued++;
                        else
                            break;
                    }
                    if (issued == n) {
                        need = n - sync_count;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, IO_BATCH_MAX_WIN, &removed, INFINITE, FALSE))
                                break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE))
                                    return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need)
                            return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[8];
        uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
        size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
        int i;
        for (i = 0; i < n; i++) { iov[i].iov_base = (void *)ps[i]; iov[i].iov_len = ls[i]; }
        return (ptrdiff_t)readv(fd, iov, n);
    }
#endif
    {
        ptrdiff_t total = 0, r;
        uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
        size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
        int i;
        for (i = 0; i < n; i++) {
            r = io_read(fd, ps[i], ls[i], timeout_ms);
            if (r < 0) return -1;
            total += r;
        }
        return total;
    }
}

/** 阶段 2 超越：批量写最多 8 段；C 侧 API。n 为 1..8。 */
ptrdiff_t io_write_batch_8(int fd, const uint8_t *p0, size_t l0, const uint8_t *p1, size_t l1, const uint8_t *p2, size_t l2, const uint8_t *p3, size_t l3,
    const uint8_t *p4, size_t l4, const uint8_t *p5, size_t l5, const uint8_t *p6, size_t l6, const uint8_t *p7, size_t l7,
    int n, unsigned timeout_ms) {
    if (n <= 0 || n > 8) return -1;
    if (n <= 4) return io_write_batch(fd, p0, l0, p1, l1, p2, l2, p3, l3, n, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[8];
            const uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
            size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[8];
            int i, submitted;
            for (i = 0; i < n; i++) { iov[i].iov_base = (void *)ps[i]; iov[i].iov_len = ls[i]; }
            sqe = io_uring_get_sqe(ring);
            if (sqe && n >= 2) {
                io_uring_prep_writev(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
            if (io_uring_sq_space_left(ring) >= (unsigned)n) {
                for (i = 0; i < n; i++) {
                    sqe = io_uring_get_sqe(ring);
                    if (!sqe) break;
                    io_uring_prep_write(sqe, fd, (void *)ps[i], ls[i], 0);
                    io_uring_sqe_set_data(sqe, (void *)(uintptr_t)i);
                }
                if (i == n && (submitted = io_uring_submit_and_wait(ring, n)) == n) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, (unsigned)n);
                    if (got >= (unsigned)n) {
                        ptrdiff_t total = 0;
                        for (i = 0; i < n; i++) {
                            if (cqe_ptrs[i]->res < 0) {
                                for (i = 0; i < n; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                                return -1;
                            }
                            total += (ptrdiff_t)cqe_ptrs[i]->res;
                            io_uring_cqe_seen(ring, cqe_ptrs[i]);
                        }
                        return total;
                    }
                    for (i = 0; i < (int)got; i++) io_uring_cqe_seen(ring, cqe_ptrs[i]);
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL)
                g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_write, n);
                {
                    const uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
                    size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    OVERLAPPED_ENTRY entries[IO_BATCH_MAX_WIN];
                    ULONG removed;
                    int got = 0, need;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(ls[i] > 0x7FFFFFFFu ? 0x7FFFFFFFu : ls[i]);
                        if (WriteFile(h, ps[i], ulen, NULL, &ovt->ov_write[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_write[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING)
                            issued++;
                        else
                            break;
                    }
                    if (issued == n) {
                        need = n - sync_count;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, IO_BATCH_MAX_WIN, &removed, INFINITE, FALSE))
                                break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE))
                                    return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need)
                            return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[8];
        const uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
        size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
        int i;
        for (i = 0; i < n; i++) { iov[i].iov_base = (void *)ps[i]; iov[i].iov_len = ls[i]; }
        return (ptrdiff_t)writev(fd, iov, n);
    }
#endif
    {
        ptrdiff_t total = 0, r;
        const uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
        size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
        int i;
        for (i = 0; i < n; i++) {
            r = io_write(fd, ps[i], ls[i], timeout_ms);
            if (r < 0) return -1;
            total += r;
        }
        return total;
    }
}

/** 与 Zig/Rust 对齐：按「指针+段数」批量读；bufs 为 shu_batch_buf_t 数组（ptr/len 有效，handle 可忽略），n 为 1..IO_READV_BUF_MAX。一次 readv/io_uring 覆盖多段，减少 syscall。 */
ptrdiff_t io_read_batch_buf(int fd, const shu_batch_buf_t *bufs, int n, unsigned timeout_ms) {
    if (n <= 0 || n > IO_READV_BUF_MAX || !bufs) return -1;
    if (n == 1) return io_read(fd, bufs[0].ptr, bufs[0].len, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[IO_READV_BUF_MAX];
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[1];
            int i;
            for (i = 0; i < n; i++) { iov[i].iov_base = (void *)bufs[i].ptr; iov[i].iov_len = bufs[i].len; }
            sqe = io_uring_get_sqe(ring);
            if (sqe) {
                io_uring_prep_readv(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0 && n <= IO_BATCH_MAX_WIN) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL) g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_read, n);
                {
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(bufs[i].len > 0x7FFFFFFFu ? 0x7FFFFFFFu : bufs[i].len);
                        if (ReadFile(h, bufs[i].ptr, ulen, NULL, &ovt->ov_read[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_read[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING) issued++;
                        else break;
                    }
                    if (issued == n) {
                        int need = n - sync_count;
                        OVERLAPPED_ENTRY entries[IO_BATCH_MAX_WIN];
                        ULONG removed;
                        int got = 0;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, IO_BATCH_MAX_WIN, &removed, INFINITE, FALSE)) break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE)) return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need) return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[IO_READV_BUF_MAX];
        int i;
        for (i = 0; i < n; i++) { iov[i].iov_base = (void *)bufs[i].ptr; iov[i].iov_len = bufs[i].len; }
        return (ptrdiff_t)readv(fd, iov, n);
    }
#endif
    {
        ptrdiff_t total = 0, r;
        int i;
        for (i = 0; i < n; i++) {
            r = io_read(fd, bufs[i].ptr, bufs[i].len, timeout_ms);
            if (r < 0) return -1;
            total += r;
        }
        return total;
    }
}

/** 与 Zig/Rust 对齐：按「指针+段数」批量写；bufs 同上，n 为 1..IO_READV_BUF_MAX。 */
ptrdiff_t io_write_batch_buf(int fd, const shu_batch_buf_t *bufs, int n, unsigned timeout_ms) {
    if (n <= 0 || n > IO_READV_BUF_MAX || !bufs) return -1;
    if (n == 1) return io_write(fd, bufs[0].ptr, bufs[0].len, timeout_ms);
#if defined(__linux__)
    if (timeout_ms == 0) {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->ok) {
            struct io_uring *ring = &ut->ring;
            struct iovec iov[IO_READV_BUF_MAX];
            struct io_uring_sqe *sqe;
            struct io_uring_cqe *cqe_ptrs[1];
            int i;
            for (i = 0; i < n; i++) { iov[i].iov_base = (void *)bufs[i].ptr; iov[i].iov_len = bufs[i].len; }
            sqe = io_uring_get_sqe(ring);
            if (sqe) {
                io_uring_prep_writev(sqe, fd, iov, (unsigned)n, 0);
                io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                if (io_uring_submit_and_wait(ring, 1) == 1) {
                    unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                    if (got >= 1) {
                        ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                        io_uring_cqe_seen(ring, cqe_ptrs[0]);
                        return res >= 0 ? res : -1;
                    }
                    return -1;
                }
            }
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms == 0 && n <= IO_BATCH_MAX_WIN) {
        HANDLE h = (HANDLE)_get_osfhandle((int)fd);
        win_ov_thread_t *ovt = win_get_thread_ov();
        if (h != INVALID_HANDLE_VALUE && h != NULL && ovt != NULL) {
            if (g_iocp_cs_init == 0) { InitializeCriticalSection(&g_iocp_cs); g_iocp_cs_init = 1; }
            EnterCriticalSection(&g_iocp_cs);
            if (g_iocp == NULL) g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            LeaveCriticalSection(&g_iocp_cs);
            if (g_iocp != NULL) {
                (void)CreateIoCompletionPort(h, g_iocp, (ULONG_PTR)(uintptr_t)fd, 0);
                (void)win_handle_skip_set(h);
                win_zero_overlapped(ovt->ov_write, n);
                {
                    DWORD ulen;
                    int i, issued = 0, sync_count = 0;
                    ptrdiff_t total = 0;
                    for (i = 0; i < n; i++) {
                        ulen = (DWORD)(bufs[i].len > 0x7FFFFFFFu ? 0x7FFFFFFFu : bufs[i].len);
                        if (WriteFile(h, bufs[i].ptr, ulen, NULL, &ovt->ov_write[i])) {
                            issued++;
                            { DWORD bytes = 0; GetOverlappedResult(h, &ovt->ov_write[i], &bytes, FALSE); total += (ptrdiff_t)bytes; sync_count++; }
                        } else if (GetLastError() == ERROR_IO_PENDING) issued++;
                        else break;
                    }
                    if (issued == n) {
                        int need = n - sync_count;
                        OVERLAPPED_ENTRY entries[IO_BATCH_MAX_WIN];
                        ULONG removed;
                        int got = 0;
                        while (got < need) {
                            if (!GetQueuedCompletionStatusEx(g_iocp, entries, IO_BATCH_MAX_WIN, &removed, INFINITE, FALSE)) break;
                            for (ulen = 0; ulen < removed && got < need; ulen++) {
                                DWORD bytes = 0;
                                if (!GetOverlappedResult(h, entries[ulen].lpOverlapped, &bytes, FALSE)) return -1;
                                total += (ptrdiff_t)bytes;
                                got++;
                            }
                        }
                        if (got == need) return total;
                    }
                }
            }
        }
    }
#endif
#if !defined(_WIN32) && !defined(_WIN64)
    if (timeout_ms == 0) {
        struct iovec iov[IO_READV_BUF_MAX];
        int i;
        for (i = 0; i < n; i++) { iov[i].iov_base = (void *)bufs[i].ptr; iov[i].iov_len = bufs[i].len; }
        return (ptrdiff_t)writev(fd, iov, n);
    }
#endif
    {
        ptrdiff_t total = 0, r;
        int i;
        for (i = 0; i < n; i++) {
            r = io_write(fd, bufs[i].ptr, bufs[i].len, timeout_ms);
            if (r < 0) return -1;
            total += r;
        }
        return total;
    }
}

/** 注册当前线程的固定 buffer 池（最多 8 块）：p0..p7 与 l0..l7 为 (ptr,len) 对，nr 为实际数量 1..8。Linux 上 io_uring_register_buffers，它平台仅存 iov 供 read_fixed/write_fixed。返回 1 成功，0 失败。 */
int io_register_buffers(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3,
    uint8_t *p4, size_t l4, uint8_t *p5, size_t l5, uint8_t *p6, size_t l6, uint8_t *p7, size_t l7,
    unsigned nr) {
    if (nr == 0 || nr > IO_FIXED_MAX) return 0;
#if defined(__linux__)
    uring_thread_t *ut = uring_get_thread();
    if (!ut) return 0;
    if (ut->fixed_ok) {
        (void)io_uring_unregister_buffers(&ut->ring);
        ut->fixed_ok = 0;
    }
    {
        uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
        size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
        unsigned i;
        for (i = 0; i < nr; i++) {
            if (!ps[i]) return 0;
            ut->fixed_iov[i].iov_base = (void *)ps[i];
            ut->fixed_iov[i].iov_len = ls[i];
        }
        ut->fixed_nr = nr;
        if (io_uring_register_buffers(&ut->ring, ut->fixed_iov, nr) != 0) {
            ut->fixed_nr = 0;
            return 0;
        }
        ut->fixed_ok = 1;
    }
    return 1;
#endif
#if defined(__APPLE__)
    fixed_pool_t *p;
    uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
    size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
    unsigned i;
    (void)pthread_once(&g_fixed_key_once, fixed_key_init);
    p = (fixed_pool_t *)pthread_getspecific(g_fixed_key);
    if (p) { free(p); p = NULL; }
    for (i = 0; i < nr; i++) if (!ps[i]) return 0;
    p = (fixed_pool_t *)malloc(sizeof(*p));
    if (!p) return 0;
    for (i = 0; i < nr; i++) {
        p->iov[i].iov_base = (void *)ps[i];
        p->iov[i].iov_len = ls[i];
    }
    p->nr = nr;
    pthread_setspecific(g_fixed_key, p);
    return 1;
#endif
#if defined(_WIN32) || defined(_WIN64)
    win_fixed_pool_t *pool;
    uint8_t *ps[8] = { p0, p1, p2, p3, p4, p5, p6, p7 };
    size_t ls[8] = { l0, l1, l2, l3, l4, l5, l6, l7 };
    unsigned i;
    pool = win_get_fixed_pool();
    if (pool) { free(pool); pool = NULL; }
    for (i = 0; i < nr; i++) if (!ps[i]) return 0;
    pool = (win_fixed_pool_t *)malloc(sizeof(*pool));
    if (!pool) return 0;
    for (i = 0; i < nr; i++) {
        pool->base[i] = (void *)ps[i];
        pool->len[i] = ls[i];
    }
    pool->nr = nr;
    TlsSetValue(g_win_fixed_tls_idx, pool);
    return 1;
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    (void)p0; (void)l0; (void)p1; (void)l1; (void)p2; (void)l2; (void)p3; (void)l3;
    (void)p4; (void)l4; (void)p5; (void)l5; (void)p6; (void)l6; (void)p7; (void)l7;
    (void)nr;
    return 0;
#endif
}

/** 注册当前线程的固定 buffer（单 buffer）：等同于 io_register_buffers(ptr,len, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 1)。返回 1 成功，0 失败。 */
int io_register_buffer(uint8_t *ptr, size_t len) {
    return io_register_buffers(ptr, len,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1);
}

/** 供 .su 调用：最多 4 块 buffer（避免 .su 参数个数限制）；内部转调 io_register_buffers，p4..p7 传 0。 */
int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr) {
    if (nr > 4) return 0;
    return io_register_buffers(p0, l0, p1, l1, p2, l2, p3, l3,
        0, 0, 0, 0, 0, 0, 0, 0,
        nr);
}

/** 与 Zig/Rust 对齐：按「指针+块数」注册固定 buffer 池；bufs 为 shu_batch_buf_t 数组，nr 为 1..IO_FIXED_MAX（8）。仅用 ptr/len。返回 1 成功，0 失败。 */
int io_register_buffers_buf(const shu_batch_buf_t *bufs, int nr) {
    if (nr <= 0 || nr > (int)IO_FIXED_MAX || !bufs) return 0;
#if defined(__linux__)
    {
        uring_thread_t *ut = uring_get_thread();
        if (!ut) return 0;
        if (ut->fixed_ok) {
            (void)io_uring_unregister_buffers(&ut->ring);
            ut->fixed_ok = 0;
        }
        {
            unsigned i;
            for (i = 0; i < (unsigned)nr; i++) {
                if (!bufs[i].ptr) return 0;
                ut->fixed_iov[i].iov_base = (void *)bufs[i].ptr;
                ut->fixed_iov[i].iov_len = bufs[i].len;
            }
            ut->fixed_nr = (unsigned)nr;
            if (io_uring_register_buffers(&ut->ring, ut->fixed_iov, (unsigned)nr) != 0) {
                ut->fixed_nr = 0;
                return 0;
            }
            ut->fixed_ok = 1;
        }
    }
    return 1;
#endif
#if defined(__APPLE__)
    {
        fixed_pool_t *p;
        unsigned i;
        (void)pthread_once(&g_fixed_key_once, fixed_key_init);
        p = (fixed_pool_t *)pthread_getspecific(g_fixed_key);
        if (p) { free(p); p = NULL; }
        for (i = 0; i < (unsigned)nr; i++) if (!bufs[i].ptr) return 0;
        p = (fixed_pool_t *)malloc(sizeof(*p));
        if (!p) return 0;
        for (i = 0; i < (unsigned)nr; i++) {
            p->iov[i].iov_base = (void *)bufs[i].ptr;
            p->iov[i].iov_len = bufs[i].len;
        }
        p->nr = (unsigned)nr;
        pthread_setspecific(g_fixed_key, p);
    }
    return 1;
#endif
#if defined(_WIN32) || defined(_WIN64)
    {
        win_fixed_pool_t *pool;
        unsigned i;
        pool = win_get_fixed_pool();
        if (pool) { free(pool); pool = NULL; }
        for (i = 0; i < (unsigned)nr; i++) if (!bufs[i].ptr) return 0;
        pool = (win_fixed_pool_t *)malloc(sizeof(*pool));
        if (!pool) return 0;
        for (i = 0; i < (unsigned)nr; i++) {
            pool->base[i] = (void *)bufs[i].ptr;
            pool->len[i] = bufs[i].len;
        }
        pool->nr = (unsigned)nr;
        TlsSetValue(g_win_fixed_tls_idx, pool);
    }
    return 1;
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    (void)bufs;
    (void)nr;
    return 0;
#endif
}

/** 注销当前线程的固定 buffer 池。 */
void io_unregister_buffers(void) {
#if defined(__linux__)
    uring_thread_t *ut = uring_get_thread();
    if (ut && ut->fixed_ok) {
        (void)io_uring_unregister_buffers(&ut->ring);
        ut->fixed_ok = 0;
        ut->fixed_nr = 0;
    }
#endif
#if defined(__APPLE__)
    fixed_pool_t *p;
    (void)pthread_once(&g_fixed_key_once, fixed_key_init);
    p = (fixed_pool_t *)pthread_getspecific(g_fixed_key);
    if (p) {
        pthread_setspecific(g_fixed_key, NULL);
        free(p);
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    win_fixed_pool_t *p = win_get_fixed_pool();
    if (p) {
        TlsSetValue(g_win_fixed_tls_idx, NULL);
        free(p);
    }
#endif
}

/** 使用已注册固定 buffer 读：buf_index 为已注册池中的下标（0..nr-1）；offset+len 须 ≤ 该 buffer 的注册长度。返回读入字节数，0=EOF，-1=错误/超时。 */
ptrdiff_t io_read_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms) {
    uint8_t *addr = NULL;
#if defined(__linux__)
    {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->fixed_nr > 0 && buf_index < ut->fixed_nr) {
            size_t buf_len = ut->fixed_iov[buf_index].iov_len;
            if (offset <= buf_len && len <= buf_len - offset) {
                addr = (uint8_t *)ut->fixed_iov[buf_index].iov_base + offset;
                if (ut->fixed_ok) {
                    struct io_uring *ring = &ut->ring;
                    struct io_uring_sqe *sqe;
                    struct io_uring_cqe *cqe;
                    struct io_uring_cqe *cqe_ptrs[1];
                    struct __kernel_timespec ts;
                    if (timeout_ms > 0) {
                        ts.tv_sec = (long long)(timeout_ms / 1000u);
                        ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
                    }
                    sqe = io_uring_get_sqe(ring);
                    if (sqe) {
                        io_uring_prep_read_fixed(sqe, fd, (void *)addr, (unsigned)len, (int)buf_index);
                        io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                        if (timeout_ms == 0) {
                            if (io_uring_submit_and_wait(ring, 1) == 1) {
                                unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                                if (got >= 1) {
                                    ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                                    io_uring_cqe_seen(ring, cqe_ptrs[0]);
                                    return res >= 0 ? res : -1;
                                }
                                return -1;
                            }
                        } else {
                            if (io_uring_submit(ring, 1) == 1) {
                                int wait_ret = io_uring_wait_cqe_timeout(ring, &cqe, &ts);
                                if (wait_ret == 0 && cqe) {
                                    ptrdiff_t res = (ptrdiff_t)cqe->res;
                                    io_uring_cqe_seen(ring, cqe);
                                    return res >= 0 ? res : -1;
                                }
                                if (cqe) io_uring_cqe_seen(ring, cqe);
                                return -1;
                            }
                        }
                    }
                    return FALLBACK_READ(fd, addr, len);
                }
            }
        }
    }
#endif
#if defined(__APPLE__)
    {
        fixed_pool_t *p;
        (void)pthread_once(&g_fixed_key_once, fixed_key_init);
        p = (fixed_pool_t *)pthread_getspecific(g_fixed_key);
        if (p && buf_index < p->nr) {
            size_t buf_len = p->iov[buf_index].iov_len;
            if (offset <= buf_len && len <= buf_len - offset)
                addr = (uint8_t *)p->iov[buf_index].iov_base + offset;
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    {
        win_fixed_pool_t *p = win_get_fixed_pool();
        if (p && buf_index < p->nr) {
            size_t buf_len = p->len[buf_index];
            if (offset <= buf_len && len <= buf_len - offset)
                addr = (uint8_t *)p->base[buf_index] + offset;
        }
    }
#endif
    if (!addr) return -1;
#if defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    return io_read(fd, addr, len, timeout_ms);
#endif
#if defined(__linux__)
    return FALLBACK_READ(fd, addr, len);
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    return -1;
#endif
}

/** 使用已注册固定 buffer 写：buf_index 为已注册池中的下标（0..nr-1）；offset+len 须 ≤ 该 buffer 的注册长度。返回写入字节数，-1=错误/超时。 */
ptrdiff_t io_write_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms) {
    const uint8_t *addr = NULL;
#if defined(__linux__)
    {
        uring_thread_t *ut = uring_get_thread();
        if (ut && ut->fixed_nr > 0 && buf_index < ut->fixed_nr) {
            size_t buf_len = ut->fixed_iov[buf_index].iov_len;
            if (offset <= buf_len && len <= buf_len - offset) {
                addr = (const uint8_t *)ut->fixed_iov[buf_index].iov_base + offset;
                if (ut->fixed_ok) {
                    struct io_uring *ring = &ut->ring;
                    struct io_uring_sqe *sqe;
                    struct io_uring_cqe *cqe;
                    struct io_uring_cqe *cqe_ptrs[1];
                    struct __kernel_timespec ts;
                    if (timeout_ms > 0) {
                        ts.tv_sec = (long long)(timeout_ms / 1000u);
                        ts.tv_nsec = (long long)((timeout_ms % 1000u) * 1000000u);
                    }
                    sqe = io_uring_get_sqe(ring);
                    if (sqe) {
                        io_uring_prep_write_fixed(sqe, fd, (const void *)addr, (unsigned)len, (int)buf_index);
                        io_uring_sqe_set_data(sqe, (void *)(uintptr_t)fd);
                        if (timeout_ms == 0) {
                            if (io_uring_submit_and_wait(ring, 1) == 1) {
                                unsigned got = io_uring_peek_batch_cqe(ring, cqe_ptrs, 1);
                                if (got >= 1) {
                                    ptrdiff_t res = (ptrdiff_t)cqe_ptrs[0]->res;
                                    io_uring_cqe_seen(ring, cqe_ptrs[0]);
                                    return res >= 0 ? res : -1;
                                }
                                return -1;
                            }
                        } else {
                            if (io_uring_submit(ring, 1) == 1) {
                                int wait_ret = io_uring_wait_cqe_timeout(ring, &cqe, &ts);
                                if (wait_ret == 0 && cqe) {
                                    ptrdiff_t res = (ptrdiff_t)cqe->res;
                                    io_uring_cqe_seen(ring, cqe);
                                    return res >= 0 ? res : -1;
                                }
                                if (cqe) io_uring_cqe_seen(ring, cqe);
                                return -1;
                            }
                        }
                    }
                    return FALLBACK_WRITE(fd, addr, len);
                }
            }
        }
    }
#endif
#if defined(__APPLE__)
    {
        fixed_pool_t *p;
        (void)pthread_once(&g_fixed_key_once, fixed_key_init);
        p = (fixed_pool_t *)pthread_getspecific(g_fixed_key);
        if (p && buf_index < p->nr) {
            size_t buf_len = p->iov[buf_index].iov_len;
            if (offset <= buf_len && len <= buf_len - offset)
                addr = (const uint8_t *)p->iov[buf_index].iov_base + offset;
        }
    }
#endif
#if defined(_WIN32) || defined(_WIN64)
    {
        win_fixed_pool_t *p = win_get_fixed_pool();
        if (p && buf_index < p->nr) {
            size_t buf_len = p->len[buf_index];
            if (offset <= buf_len && len <= buf_len - offset)
                addr = (const uint8_t *)p->base[buf_index] + offset;
        }
    }
#endif
    if (!addr) return -1;
#if defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
    return io_write(fd, addr, len, timeout_ms);
#endif
#if defined(__linux__)
    return FALLBACK_WRITE(fd, addr, len);
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    return -1;
#endif
}

/** 阶段 2 超越（路线图 §4.3）：多 fd 就绪等待；一次系统调用等待 n 个 fd 中任意可读。返回第一个就绪的 fd 在下标 0..n-1，超时/错误返回 -1。n 建议 ≤8。 */
int io_wait_readable(const int *fds, int n, unsigned timeout_ms) {
    if (!fds || n <= 0 || n > 8) return -1;
#if defined(__APPLE__)
    {
        int kq = kq_get();
        if (kq >= 0) {
            struct kevent ev_in[8], ev_out;
            struct timespec ts, *pts = NULL;
            int i;
            if (timeout_ms > 0) {
                ts.tv_sec = (timeout_ms / 1000u);
                ts.tv_nsec = (long)((timeout_ms % 1000u) * 1000000u);
                pts = &ts;
            }
            for (i = 0; i < n; i++)
                EV_SET(&ev_in[i], (uintptr_t)fds[i], EVFILT_READ, EV_ADD | EV_ONESHOT | EV_CLEAR, 0, 0, 0);
            if (kevent(kq, ev_in, n, &ev_out, 1, pts) >= 1) {
                for (i = 0; i < n; i++)
                    if ((int)(intptr_t)ev_out.ident == fds[i]) return i;
                return 0;
            }
        }
    }
    return -1;
#endif
#if defined(__linux__)
    {
        struct pollfd pfd[8];
        int i, r;
        for (i = 0; i < n; i++) {
            pfd[i].fd = fds[i];
            pfd[i].events = POLLIN;
            pfd[i].revents = 0;
        }
        r = poll(pfd, (nfds_t)n, timeout_ms == 0 ? -1 : (int)timeout_ms);
        if (r <= 0) return -1;
        for (i = 0; i < n; i++)
            if (pfd[i].revents & (POLLIN | POLLHUP | POLLERR)) return i;
    }
    return -1;
#endif
#if defined(_WIN32) || defined(_WIN64)
    {
        static int g_wsa_ready = 0;
        WSADATA wsa;
        fd_set read_fds;
        struct timeval tv, *ptv = NULL;
        int i, r;
        if (!g_wsa_ready) {
            if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
            g_wsa_ready = 1;
        }
        FD_ZERO(&read_fds);
        for (i = 0; i < n; i++)
            FD_SET((SOCKET)(intptr_t)fds[i], &read_fds);
        if (timeout_ms > 0) {
            tv.tv_sec = (long)(timeout_ms / 1000u);
            tv.tv_usec = (long)((timeout_ms % 1000u) * 1000u);
            ptv = &tv;
        }
        r = select(0, &read_fds, NULL, NULL, ptv);
        if (r <= 0) return -1;
        for (i = 0; i < n; i++)
            if (FD_ISSET((SOCKET)(intptr_t)fds[i], &read_fds)) return i;
    }
    return -1;
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(_WIN64)
    {
        struct pollfd pfd[8];
        int i, r;
        for (i = 0; i < n; i++) {
            pfd[i].fd = fds[i];
            pfd[i].events = POLLIN;
            pfd[i].revents = 0;
        }
        r = poll(pfd, (nfds_t)n, timeout_ms == 0 ? -1 : (int)timeout_ms);
        if (r <= 0) return -1;
        for (i = 0; i < n; i++)
            if (pfd[i].revents & (POLLIN | POLLHUP | POLLERR)) return i;
    }
    return -1;
#endif
}

/* ——— 零拷贝读：内部缓冲，返回指针+长度，无用户态二次拷贝；指针在下次 read_ptr 前有效；多线程并发 read_ptr 不保证隔离（单缓冲）。 ——— */
#define IO_READ_PTR_BUF_SIZE 65536
static uint8_t g_io_read_ptr_buf[IO_READ_PTR_BUF_SIZE];
static int32_t g_io_read_ptr_len;

/** 零拷贝读：从 handle（0=stdin，≥2=fd）读入内部缓冲，返回指向该缓冲的只读指针；失败返回 NULL。调用方只读、勿写；指针在下次 read_ptr 前有效。配套 io_read_ptr_len() 取长度。 */
uint8_t *io_read_ptr(unsigned int handle, unsigned int timeout_ms) {
    int fd = (int)handle;
    ptrdiff_t r = io_read(fd, g_io_read_ptr_buf, (size_t)IO_READ_PTR_BUF_SIZE, timeout_ms);
    if (r < 0) {
        g_io_read_ptr_len = 0;
        return NULL;
    }
    g_io_read_ptr_len = (int32_t)r;
    return g_io_read_ptr_buf;
}

/** 返回最近一次 io_read_ptr 成功读入的字节数（0 表示 EOF 或尚未调用/失败）。与 io_read_ptr 配套使用。 */
int32_t io_read_ptr_len(void) {
    return g_io_read_ptr_len;
}

#ifdef __cplusplus
}
#endif
