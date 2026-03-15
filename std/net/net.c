/**
 * std/net/net.c — 高吞吐网络 C 层：TCP socket 创建、连接、监听、接受
 *
 * 与 std/net/mod.su 同目录；供 std.net connect/listen/accept 调用。
 * 约定：所有 socket 创建后立即设为非阻塞，与 std.io.driver 统一调度。
 * 链接用户程序时由编译器链入本目录产出的 net.o；Unix 需 -lc，Windows 需 ws2_32。
 *
 * API：TCP（connect/listen/accept/close、local/peer_addr）、UDP（bind/send_to/recv_from）、
 * IPv6 TCP（connect_ipv6/listen_ipv6）、DNS（resolve_ipv4）。
 * 阶段 5：UDP 批量 recvmmsg/sendmmsg（Linux）需 _GNU_SOURCE。
 * 多核易用：net_run_accept_workers_c 起 n 个线程，每线程循环 accept_many+close；Unix 需 -lpthread。
 */
#if defined(__linux__)
#define _GNU_SOURCE
#endif

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if defined(__linux__)
/* 阶段 1 性能压榨：Linux 上 connect/accept 走 io_uring，由 std/io/io.c 提供；链接时需 io.o。 */
extern int32_t io_uring_accept(int listener_fd, unsigned timeout_ms);
extern int32_t io_uring_connect(uint32_t addr_u32, uint32_t port_u32, unsigned timeout_ms);
/* 阶段 2 性能压榨：一次提交 N 个 accept/connect，一次收割 N 个 CQE。 */
extern int io_uring_accept_many(int listener_fd, int32_t *out_fds, int n, unsigned timeout_ms);
extern int io_uring_connect_many(uint32_t addr_u32, uint32_t port_u32, int32_t *out_fds, int n, unsigned timeout_ms);
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")
#ifndef socklen_t
#define socklen_t int
#endif
#define SHU_NET_ERRNO WSAGetLastError()
#define SHU_NET_EINPROGRESS WSAEWOULDBLOCK
#define SHU_NET_EAGAIN WSAEWOULDBLOCK
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <pthread.h>
#define SHU_NET_ERRNO errno
#define SHU_NET_EINPROGRESS EINPROGRESS
#define SHU_NET_EAGAIN EAGAIN
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <process.h>
#endif

/* 将 IPv4 地址 u32（大端 a.b.c.d = (a<<24)|(b<<16)|(c<<8)|d）与 port_u32（取低 16 位）转为 sockaddr_in */
static void shu_net_set_addr_port(struct sockaddr_in *sin, uint32_t addr_u32, uint32_t port_u32) {
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = htonl(addr_u32);
    sin->sin_port = htons((uint16_t)(port_u32 & 0xFFFFu));
}

#if defined(_WIN32) || defined(_WIN64)
static int shu_net_set_nonblock(int fd) {
    u_long one = 1;
    return ioctlsocket((SOCKET)fd, FIONBIO, &one) == 0 ? 0 : -1;
}
#else
static int shu_net_set_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0 ? 0 : -1;
}
#endif

#if defined(_WIN32) || defined(_WIN64)
static int shu_net_poll_writable(int fd, uint32_t timeout_ms) {
    fd_set wf, ef;
    struct timeval tv;
    FD_ZERO(&wf);
    FD_ZERO(&ef);
    FD_SET((SOCKET)fd, &wf);
    FD_SET((SOCKET)fd, &ef);
    tv.tv_sec = (long)(timeout_ms / 1000u);
    tv.tv_usec = (long)((timeout_ms % 1000u) * 1000u);
    int n = select((int)(fd + 1), NULL, &wf, &ef, timeout_ms ? &tv : NULL);
    if (n <= 0) return -1;
    if (FD_ISSET((SOCKET)fd, &ef)) return -1;
    return 0;
}
static int shu_net_poll_readable(int fd, uint32_t timeout_ms) {
    fd_set rf, ef;
    struct timeval tv;
    FD_ZERO(&rf);
    FD_ZERO(&ef);
    FD_SET((SOCKET)fd, &rf);
    FD_SET((SOCKET)fd, &ef);
    tv.tv_sec = (long)(timeout_ms / 1000u);
    tv.tv_usec = (long)((timeout_ms % 1000u) * 1000u);
    int n = select((int)(fd + 1), &rf, NULL, &ef, timeout_ms ? &tv : NULL);
    if (n <= 0) return -1;
    if (FD_ISSET((SOCKET)fd, &ef)) return -1;
    return 0;
}
#else
static int shu_net_poll_writable(int fd, uint32_t timeout_ms) {
    struct pollfd pfd = { fd, POLLOUT, 0 };
    int n = poll(&pfd, 1, (int)(timeout_ms ? timeout_ms : (-1)));
    if (n <= 0 || (pfd.revents & (POLLERR | POLLHUP))) return -1;
    return 0;
}
static int shu_net_poll_readable(int fd, uint32_t timeout_ms) {
    struct pollfd pfd = { fd, POLLIN, 0 };
    int n = poll(&pfd, 1, (int)(timeout_ms ? timeout_ms : (-1)));
    if (n <= 0 || (pfd.revents & (POLLERR | POLLHUP))) return -1;
    return 0;
}
#endif

/** TCP 连接至 addr:port；addr_u32 为大端 (a<<24)|(b<<16)|(c<<8)|d，port_u32 取低 16 位为主机序端口；timeout_ms 毫秒（0=无超时）。返回 fd，失败 -1。Socket 为非阻塞。 */
int32_t net_tcp_connect_c(uint32_t addr_u32, uint32_t port_u32, uint32_t timeout_ms) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
        wsa_done = 1;
    }
#endif
    struct sockaddr_in sin;
    shu_net_set_addr_port(&sin, addr_u32, port_u32);

#if defined(_WIN32) || defined(_WIN64)
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return -1;
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    if (connect(s, (struct sockaddr *)&sin, (int)sizeof(sin)) != 0) {
        if (SHU_NET_ERRNO != SHU_NET_EINPROGRESS) { closesocket(s); return -1; }
        if (shu_net_poll_writable((int)s, timeout_ms) != 0) { closesocket(s); return -1; }
        int err = 0;
        int errlen = (int)sizeof(err);
        if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &errlen) != 0 || err != 0) {
            closesocket(s);
            return -1;
        }
    }
    return (int32_t)s;
#else
#if defined(__linux__)
    {
        int32_t fd = io_uring_connect(addr_u32, port_u32, (unsigned)timeout_ms);
        return fd;
    }
#else
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) != 0) {
        if (SHU_NET_ERRNO != SHU_NET_EINPROGRESS) { close(fd); return -1; }
        if (shu_net_poll_writable(fd, timeout_ms) != 0) { close(fd); return -1; }
        int err = 0;
        socklen_t errlen = sizeof(err);
        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) != 0 || err != 0) {
            close(fd);
            return -1;
        }
    }
    return (int32_t)fd;
#endif
#endif
}

/** 在 addr:port 上 TCP 监听；addr_u32/port_u32 同上。返回 listener fd，失败 -1。Socket 为非阻塞。 */
int32_t net_tcp_listen_c(uint32_t addr_u32, uint32_t port_u32) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
        wsa_done = 1;
    }
#endif
    struct sockaddr_in sin;
    shu_net_set_addr_port(&sin, addr_u32, port_u32);

#if defined(_WIN32) || defined(_WIN64)
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return -1;
    {
        int one = 1;
        setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(one));
    }
    if (bind(s, (struct sockaddr *)&sin, (int)sizeof(sin)) != 0) { closesocket(s); return -1; }
    if (listen(s, 128) != 0) { closesocket(s); return -1; }
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    return (int32_t)s;
#else
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    {
        int one = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) != 0) { close(fd); return -1; }
    if (listen(fd, 128) != 0) { close(fd); return -1; }
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    return (int32_t)fd;
#endif
}

/** 从 listener_fd 接受一个连接；timeout_ms 毫秒（0=无超时）。返回 client fd，失败 -1。Client socket 为非阻塞。 */
int32_t net_accept_c(int32_t listener_fd, uint32_t timeout_ms) {
#if defined(_WIN32) || defined(_WIN64)
    SOCKET ls = (SOCKET)listener_fd;
    if (timeout_ms != 0) {
        if (shu_net_poll_readable((int)ls, timeout_ms) != 0) return -1;
    }
    struct sockaddr_in peer;
    int peer_len = (int)sizeof(peer);
    SOCKET s = accept(ls, (struct sockaddr *)&peer, &peer_len);
    if (s == INVALID_SOCKET) return -1;
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    return (int32_t)s;
#else
#if defined(__linux__)
    {
        int32_t fd = io_uring_accept(listener_fd, (unsigned)timeout_ms);
        return fd;
    }
#else
    if (timeout_ms != 0) {
        if (shu_net_poll_readable(listener_fd, timeout_ms) != 0) return -1;
    }
    struct sockaddr_in peer;
    socklen_t peer_len = sizeof(peer);
    int fd = accept(listener_fd, (struct sockaddr *)&peer, &peer_len);
    if (fd < 0) return -1;
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    return (int32_t)fd;
#endif
#endif
}

/** 阶段 2：批量接受连接；out_fds 至少 n 个元素，填满成功的 client fd；timeout_ms 毫秒（0=无超时）。返回成功数量。Linux 走 io_uring_accept_many，否则循环 net_accept_c。 */
int net_accept_many_c(int32_t listener_fd, int32_t *out_fds, int n, uint32_t timeout_ms) {
    if (n <= 0 || !out_fds) return 0;
#if defined(__linux__)
    return io_uring_accept_many(listener_fd, out_fds, n, (unsigned)timeout_ms);
#else
    int i;
    for (i = 0; i < n; i++) {
        int32_t fd = net_accept_c(listener_fd, timeout_ms);
        if (fd < 0) return i;
        out_fds[i] = fd;
    }
    return n;
#endif
}

/** 阶段 2：向同一 addr:port 批量建连；out_fds 至少 n 个元素，填满成功的 fd；timeout_ms 毫秒（0=无超时）。返回成功数量。Linux 走 io_uring_connect_many，否则循环 net_tcp_connect_c。 */
int net_connect_many_c(uint32_t addr_u32, uint32_t port_u32, int32_t *out_fds, int n, uint32_t timeout_ms) {
    if (n <= 0 || !out_fds) return 0;
#if defined(__linux__)
    return io_uring_connect_many(addr_u32, port_u32, out_fds, n, (unsigned)timeout_ms);
#else
    int i;
    for (i = 0; i < n; i++) {
        int32_t fd = net_tcp_connect_c(addr_u32, port_u32, timeout_ms);
        if (fd < 0) return i;
        out_fds[i] = fd;
    }
    return n;
#endif
}

/* ---------- 多核易用：多 worker 共享 listener，每线程循环 accept_many + close（压测/多核压榨） ---------- */
#define SHU_NET_ACCEPT_BATCH 64
#define SHU_NET_MAX_WORKERS 64

/* 前向声明：worker 内调用的接口在文件后部定义 */
extern int net_accept_many_c(int32_t listener_fd, int32_t *out_fds, int n, uint32_t timeout_ms);
extern int32_t net_close_socket_c(int32_t fd);

/* 可选：链接 std.thread 时每 worker 绑核；未链 thread.o 时为弱符号 0，不调用。仅 GCC/Clang 支持 weak。 */
#if defined(__GNUC__) || defined(__clang__)
__attribute__((weak)) extern int32_t thread_set_affinity_self_c(int32_t cpu_index);
#endif

struct shu_net_worker_arg {
    int32_t listener_fd;
    uint32_t timeout_ms;
    int32_t worker_index;
};

static void *shu_net_worker_accept_loop(void *arg) {
    struct shu_net_worker_arg *a = (struct shu_net_worker_arg *)arg;
#if defined(__GNUC__) || defined(__clang__)
    if (thread_set_affinity_self_c)
        (void)thread_set_affinity_self_c(a->worker_index);
#endif
    int32_t fds[SHU_NET_ACCEPT_BATCH];
    for (;;) {
        int n = net_accept_many_c(a->listener_fd, fds, SHU_NET_ACCEPT_BATCH, a->timeout_ms);
        int i;
        for (i = 0; i < n; i++)
            (void)net_close_socket_c(fds[i]);
    }
    return NULL;
}

#if defined(_WIN32) || defined(_WIN64)
static DWORD WINAPI shu_net_thread_wrap(LPVOID arg) {
    (void)shu_net_worker_accept_loop(arg);
    return 0;
}
#endif

/**
 * 多核易用：起 n_workers 个线程，每线程循环 accept_many 后立即 close（压测建连吞吐或占位）。
 * 主线程会阻塞直至 join 所有 worker（即永不返回）；失败返回 -1（如 listener_fd 无效、n_workers<=0 或 >64、线程创建失败）。
 * timeout_ms 为每次 accept_many 的超时（建议 5000）；n_workers 建议与核数一致，每线程一 io_uring（Linux）。
 */
int32_t net_run_accept_workers_c(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms) {
    if (listener_fd < 0 || n_workers <= 0) return -1;
    if (n_workers > SHU_NET_MAX_WORKERS) n_workers = SHU_NET_MAX_WORKERS;
    static struct shu_net_worker_arg s_args[SHU_NET_MAX_WORKERS];
    int i;
    for (i = 0; i < n_workers; i++) {
        s_args[i].listener_fd = listener_fd;
        s_args[i].timeout_ms = timeout_ms;
        s_args[i].worker_index = i;
    }
#if defined(_WIN32) || defined(_WIN64)
    {
        HANDLE th[SHU_NET_MAX_WORKERS];
        for (i = 0; i < n_workers; i++) {
            th[i] = CreateThread(NULL, 0, shu_net_thread_wrap, &s_args[i], 0, NULL);
            if (th[i] == NULL) {
                while (i > 0) { CloseHandle(th[--i]); }
                return -1;
            }
        }
        WaitForMultipleObjects((DWORD)n_workers, th, 1, INFINITE);
        for (i = 0; i < n_workers; i++) CloseHandle(th[i]);
    }
#else
    {
        pthread_t th[SHU_NET_MAX_WORKERS];
        for (i = 0; i < n_workers; i++) {
            if (pthread_create(&th[i], NULL, shu_net_worker_accept_loop, &s_args[i]) != 0) {
                while (i > 0) pthread_join(th[--i], NULL);
                return -1;
            }
        }
        for (i = 0; i < n_workers; i++)
            (void)pthread_join(th[i], NULL);
    }
#endif
    return 0;
}

/** 关闭 socket fd；与 std.fs.close 区分：Windows 下须用 closesocket。返回 0 成功，-1 失败。 */
int32_t net_close_socket_c(int32_t fd) {
    if (fd < 0) return 0;
#if defined(_WIN32) || defined(_WIN64)
    return closesocket((SOCKET)fd) == 0 ? 0 : -1;
#else
    return close(fd) == 0 ? 0 : -1;
#endif
}

/* ========== UDP ========== */

/** UDP 在 addr:port 上绑定；addr_u32 为 INADDR_ANY(0) 表示监听所有接口。返回 fd，失败 -1。非阻塞。 */
int32_t net_udp_bind_c(uint32_t addr_u32, uint32_t port_u32) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
        wsa_done = 1;
    }
#endif
    struct sockaddr_in sin;
    shu_net_set_addr_port(&sin, addr_u32, port_u32);

#if defined(_WIN32) || defined(_WIN64)
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) return -1;
    {
        int one = 1;
        setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(one));
    }
    if (bind(s, (struct sockaddr *)&sin, (int)sizeof(sin)) != 0) { closesocket(s); return -1; }
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    return (int32_t)s;
#else
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) return -1;
    {
        int one = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) != 0) { close(fd); return -1; }
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    return (int32_t)fd;
#endif
}

/** UDP 向 addr:port 发送 buf[0..len]。返回发送字节数，失败 -1。 */
int32_t net_udp_send_to_c(int32_t fd, uint32_t addr_u32, uint32_t port_u32, const uint8_t *buf, size_t len) {
    struct sockaddr_in sin;
    shu_net_set_addr_port(&sin, addr_u32, port_u32);
#if defined(_WIN32) || defined(_WIN64)
    int n = sendto((SOCKET)fd, (const char *)buf, (int)(len > 0x7FFFFFFF ? 0x7FFFFFFF : len), 0, (struct sockaddr *)&sin, (int)sizeof(sin));
    return (n >= 0) ? (int32_t)n : -1;
#else
    ssize_t n = sendto(fd, buf, len, 0, (struct sockaddr *)&sin, sizeof(sin));
    return (n >= 0) ? (int32_t)n : -1;
#endif
}

/** UDP 从 fd 接收至 buf[0..len]，timeout_ms 毫秒（0=无超时）。返回接收字节数，0=无数据(EAGAIN)，-1=错误；成功时写入 *out_addr_u32 与 *out_port_u32（主机序）。 */
int32_t net_udp_recv_from_c(int32_t fd, uint8_t *buf, size_t len, uint32_t timeout_ms, uint32_t *out_addr_u32, uint32_t *out_port_u32) {
#if defined(_WIN32) || defined(_WIN64)
    if (timeout_ms != 0) {
        if (shu_net_poll_readable(fd, timeout_ms) != 0) return -1;
    }
    struct sockaddr_in peer;
    int peer_len = (int)sizeof(peer);
    int n = recvfrom((SOCKET)fd, (char *)buf, (int)(len > 0x7FFFFFFF ? 0x7FFFFFFF : len), 0, (struct sockaddr *)&peer, &peer_len);
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (out_addr_u32) *out_addr_u32 = ntohl(peer.sin_addr.s_addr);
    if (out_port_u32) *out_port_u32 = (uint32_t)ntohs(peer.sin_port);
    return (int32_t)n;
#else
    if (timeout_ms != 0) {
        if (shu_net_poll_readable(fd, timeout_ms) != 0) return -1;
    }
    struct sockaddr_in peer;
    socklen_t peer_len = sizeof(peer);
    ssize_t n = recvfrom(fd, buf, len, 0, (struct sockaddr *)&peer, &peer_len);
    if (n < 0) return (SHU_NET_ERRNO == SHU_NET_EAGAIN) ? 0 : -1;
    if (out_addr_u32) *out_addr_u32 = ntohl(peer.sin_addr.s_addr);
    if (out_port_u32) *out_port_u32 = (uint32_t)ntohs(peer.sin_port);
    return (int32_t)n;
#endif
}

/* 阶段 5 性能压榨：UDP 批量 recv/send；最多 2 报文（.su 参数个数限制），C 内仍可用 4 槽扩展。 */
#define UDP_BATCH_MAX 2
/** 与 .su std.io.driver.Buffer ABI 一致，供 udp_recv_many_buf/udp_send_many_buf 按「指针+段数」使用。 */
#define UDP_BATCH_BUF_MAX 8
typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_net_buf_t;

/** 阶段 5：UDP 批量接收；最多 2 段 (p0,l0),(p1,l1)，n 为 1..2。timeout_ms 毫秒（0=无超时）。out_sizes[i]=第 i 条字节数，out_addrs/out_ports 为发送方。返回收到的报文数，-1=错误。Linux 走 recvmmsg。 */
int net_udp_recv_many_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, int n, uint32_t timeout_ms, int32_t *out_sizes, uint32_t *out_addrs, uint32_t *out_ports) {
    if (n <= 0 || n > UDP_BATCH_MAX || !out_sizes || !out_addrs || !out_ports) return -1;
#if defined(__linux__) && defined(__GLIBC__)
    {
        struct iovec iov[UDP_BATCH_MAX];
        struct sockaddr_in addrs[UDP_BATCH_MAX];
        struct mmsghdr msgvec[UDP_BATCH_MAX];
        unsigned int i;
        for (i = 0; i < (unsigned int)n; i++) {
            socklen_t addrlen = sizeof(addrs[0]);
            iov[i].iov_base = (i == 0) ? p0 : p1;
            iov[i].iov_len  = (i == 0) ? l0 : l1;
            msgvec[i].msg_hdr.msg_name = &addrs[i];
            msgvec[i].msg_hdr.msg_namelen = addrlen;
            msgvec[i].msg_hdr.msg_iov = &iov[i];
            msgvec[i].msg_hdr.msg_iovlen = 1;
            msgvec[i].msg_hdr.msg_control = NULL;
            msgvec[i].msg_hdr.msg_controllen = 0;
            msgvec[i].msg_hdr.msg_flags = 0;
        }
        if (timeout_ms != 0) {
            if (shu_net_poll_readable(fd, timeout_ms) != 0) return -1;
        }
        int r = recvmmsg(fd, msgvec, (unsigned int)n, 0, NULL);
        if (r < 0) return (SHU_NET_ERRNO == SHU_NET_EAGAIN) ? 0 : -1;
        for (i = 0; i < (unsigned int)r; i++) {
            out_sizes[i] = (int32_t)msgvec[i].msg_len;
            out_addrs[i] = ntohl(addrs[i].sin_addr.s_addr);
            out_ports[i] = (uint32_t)ntohs(addrs[i].sin_port);
        }
        for (i = (unsigned int)r; i < (unsigned int)n; i++) {
            out_sizes[i] = 0;
        }
        return r;
    }
#else
    {
        int count = 0;
        uint8_t *ps[] = { p0, p1 };
        size_t ls[] = { l0, l1 };
        while (count < n) {
            int32_t got = net_udp_recv_from_c(fd, ps[count], ls[count], (count == 0) ? timeout_ms : 0, &out_addrs[count], &out_ports[count]);
            if (got < 0) return -1;
            if (got == 0) return count;
            out_sizes[count] = got;
            count++;
        }
        return count;
    }
#endif
}

/** 阶段 5：UDP 批量发送；n 条 (addr_i, port_i, p_i, l_i)，n 为 1..2。返回成功发送的报文数，-1=错误。Linux 走 sendmmsg。 */
int net_udp_send_many_c(int32_t fd, uint32_t a0, uint32_t port0, const uint8_t *p0, size_t l0, uint32_t a1, uint32_t port1, const uint8_t *p1, size_t l1, int n) {
    if (n <= 0 || n > UDP_BATCH_MAX) return -1;
#if defined(__linux__) && defined(__GLIBC__)
    {
        struct sockaddr_in addrs[UDP_BATCH_MAX];
        struct iovec iov[UDP_BATCH_MAX];
        struct mmsghdr msgvec[UDP_BATCH_MAX];
        unsigned int i;
        for (i = 0; i < (unsigned int)n; i++) {
            shu_net_set_addr_port(&addrs[i], (i == 0) ? a0 : a1, (i == 0) ? port0 : port1);
            iov[i].iov_base = (void *)((i == 0) ? p0 : p1);
            iov[i].iov_len  = (i == 0) ? l0 : l1;
            msgvec[i].msg_hdr.msg_name = &addrs[i];
            msgvec[i].msg_hdr.msg_namelen = sizeof(addrs[i]);
            msgvec[i].msg_hdr.msg_iov = &iov[i];
            msgvec[i].msg_hdr.msg_iovlen = 1;
            msgvec[i].msg_hdr.msg_control = NULL;
            msgvec[i].msg_hdr.msg_controllen = 0;
            msgvec[i].msg_hdr.msg_flags = 0;
        }
        int r = sendmmsg(fd, msgvec, (unsigned int)n, 0);
        if (r < 0) return -1;
        return r;
    }
#else
    {
        uint32_t as[] = { a0, a1 };
        uint32_t ports[] = { port0, port1 };
        const uint8_t *ps[] = { p0, p1 };
        size_t ls[] = { l0, l1 };
        int i;
        for (i = 0; i < n; i++) {
            int32_t sent = net_udp_send_to_c(fd, as[i], ports[i], (uint8_t *)ps[i], ls[i]);
            if (sent < 0) return -1;
        }
        return n;
    }
#endif
}

/** 与 Zig/Rust 对齐：UDP 批量接收，按「指针+段数」；bufs 为 shu_net_buf_t 数组，n 为 1..UDP_BATCH_BUF_MAX。out_sizes/out_addrs/out_ports 至少 n 个。返回收到报文数，-1=错误。 */
int net_udp_recv_many_buf_c(int32_t fd, shu_net_buf_t *bufs, int n, uint32_t timeout_ms, int32_t *out_sizes, uint32_t *out_addrs, uint32_t *out_ports) {
    if (n <= 0 || n > UDP_BATCH_BUF_MAX || !bufs || !out_sizes || !out_addrs || !out_ports) return -1;
#if defined(__linux__) && defined(__GLIBC__)
    {
        struct iovec iov[UDP_BATCH_BUF_MAX];
        struct sockaddr_in addrs[UDP_BATCH_BUF_MAX];
        struct mmsghdr msgvec[UDP_BATCH_BUF_MAX];
        unsigned int i;
        for (i = 0; i < (unsigned int)n; i++) {
            socklen_t addrlen = sizeof(addrs[0]);
            iov[i].iov_base = bufs[i].ptr;
            iov[i].iov_len  = bufs[i].len;
            msgvec[i].msg_hdr.msg_name = &addrs[i];
            msgvec[i].msg_hdr.msg_namelen = addrlen;
            msgvec[i].msg_hdr.msg_iov = &iov[i];
            msgvec[i].msg_hdr.msg_iovlen = 1;
            msgvec[i].msg_hdr.msg_control = NULL;
            msgvec[i].msg_hdr.msg_controllen = 0;
            msgvec[i].msg_hdr.msg_flags = 0;
        }
        if (timeout_ms != 0) {
            if (shu_net_poll_readable(fd, timeout_ms) != 0) return -1;
        }
        int r = recvmmsg(fd, msgvec, (unsigned int)n, 0, NULL);
        if (r < 0) return (SHU_NET_ERRNO == SHU_NET_EAGAIN) ? 0 : -1;
        for (i = 0; i < (unsigned int)r; i++) {
            out_sizes[i] = (int32_t)msgvec[i].msg_len;
            out_addrs[i] = ntohl(addrs[i].sin_addr.s_addr);
            out_ports[i] = (uint32_t)ntohs(addrs[i].sin_port);
        }
        for (i = (unsigned int)r; i < (unsigned int)n; i++) out_sizes[i] = 0;
        return r;
    }
#else
    {
        int count = 0;
        while (count < n) {
            int32_t got = net_udp_recv_from_c(fd, bufs[count].ptr, bufs[count].len, (count == 0) ? timeout_ms : 0, &out_addrs[count], &out_ports[count]);
            if (got < 0) return -1;
            if (got == 0) return count;
            out_sizes[count] = got;
            count++;
        }
        return count;
    }
#endif
}

/** 与 Zig/Rust 对齐：UDP 批量发送，按「指针+段数」；addrs[i]/ports[i]/bufs[i] 为第 i 条目标与负载，n 为 1..UDP_BATCH_BUF_MAX。返回发送报文数，-1=错误。 */
int net_udp_send_many_buf_c(int32_t fd, const uint32_t *addrs, const uint32_t *ports, const shu_net_buf_t *bufs, int n) {
    if (n <= 0 || n > UDP_BATCH_BUF_MAX || !addrs || !ports || !bufs) return -1;
#if defined(__linux__) && defined(__GLIBC__)
    {
        struct sockaddr_in sa[UDP_BATCH_BUF_MAX];
        struct iovec iov[UDP_BATCH_BUF_MAX];
        struct mmsghdr msgvec[UDP_BATCH_BUF_MAX];
        unsigned int i;
        for (i = 0; i < (unsigned int)n; i++) {
            shu_net_set_addr_port(&sa[i], addrs[i], ports[i]);
            iov[i].iov_base = (void *)bufs[i].ptr;
            iov[i].iov_len  = bufs[i].len;
            msgvec[i].msg_hdr.msg_name = &sa[i];
            msgvec[i].msg_hdr.msg_namelen = sizeof(sa[i]);
            msgvec[i].msg_hdr.msg_iov = &iov[i];
            msgvec[i].msg_hdr.msg_iovlen = 1;
            msgvec[i].msg_hdr.msg_control = NULL;
            msgvec[i].msg_hdr.msg_controllen = 0;
            msgvec[i].msg_hdr.msg_flags = 0;
        }
        int r = sendmmsg(fd, msgvec, (unsigned int)n, 0);
        return r >= 0 ? r : -1;
    }
#else
    {
        int i;
        for (i = 0; i < n; i++) {
            int32_t sent = net_udp_send_to_c(fd, addrs[i], ports[i], bufs[i].ptr, bufs[i].len);
            if (sent < 0) return -1;
        }
        return n;
    }
#endif
}

/* ========== TCP local/peer 地址 ========== */

/** 获取 TCP 连接或 listener 的本地地址与端口。成功返回 (addr_u32<<32)|port_u32（i64），失败返回 -1。 */
int64_t net_tcp_local_addr_c(int32_t fd) {
    struct sockaddr_in sin;
#if defined(_WIN32) || defined(_WIN64)
    int len = (int)sizeof(sin);
    if (getsockname((SOCKET)fd, (struct sockaddr *)&sin, &len) != 0) return -1;
#else
    socklen_t len = (socklen_t)sizeof(sin);
    if (getsockname(fd, (struct sockaddr *)&sin, &len) != 0) return -1;
#endif
    uint32_t a = ntohl(sin.sin_addr.s_addr);
    uint32_t p = (uint32_t)ntohs(sin.sin_port);
    return ((int64_t)(uint64_t)a << 32) | (p & 0xFFFFu);
}

/** 获取 TCP 连接的远端地址与端口；仅对 TcpStream 有效。成功返回 (addr_u32<<32)|port_u32（i64），失败返回 -1。 */
int64_t net_tcp_peer_addr_c(int32_t fd) {
    struct sockaddr_in sin;
#if defined(_WIN32) || defined(_WIN64)
    int len = (int)sizeof(sin);
    if (getpeername((SOCKET)fd, (struct sockaddr *)&sin, &len) != 0) return -1;
#else
    socklen_t len = (socklen_t)sizeof(sin);
    if (getpeername(fd, (struct sockaddr *)&sin, &len) != 0) return -1;
#endif
    uint32_t a = ntohl(sin.sin_addr.s_addr);
    uint32_t p = (uint32_t)ntohs(sin.sin_port);
    return ((int64_t)(uint64_t)a << 32) | (p & 0xFFFFu);
}

/* ========== IPv6 TCP ========== */

/** IPv6 地址 16 字节，网络序；C 层按 uint8_t addr[16] 接收。 */
static void shu_net_set_addr_port_ipv6(struct sockaddr_in6 *sin6, const uint8_t *addr_16, uint32_t port_u32) {
    sin6->sin6_family = AF_INET6;
    memcpy(&sin6->sin6_addr, addr_16, 16);
    sin6->sin6_port = htons((uint16_t)(port_u32 & 0xFFFFu));
}

/** TCP 连接至 IPv6 addr:port；addr_16 为 16 字节。返回 fd，失败 -1。非阻塞。 */
int32_t net_tcp_connect_ipv6_c(const uint8_t *addr_16, uint32_t port_u32, uint32_t timeout_ms) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
        wsa_done = 1;
    }
#endif
    struct sockaddr_in6 sin6;
    shu_net_set_addr_port_ipv6(&sin6, addr_16, port_u32);

#if defined(_WIN32) || defined(_WIN64)
    SOCKET s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return -1;
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    if (connect(s, (struct sockaddr *)&sin6, (int)sizeof(sin6)) != 0) {
        if (SHU_NET_ERRNO != SHU_NET_EINPROGRESS) { closesocket(s); return -1; }
        if (shu_net_poll_writable((int)s, timeout_ms) != 0) { closesocket(s); return -1; }
        int err = 0;
        int errlen = (int)sizeof(err);
        if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &errlen) != 0 || err != 0) { closesocket(s); return -1; }
    }
    return (int32_t)s;
#else
    int fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    if (connect(fd, (struct sockaddr *)&sin6, sizeof(sin6)) != 0) {
        if (SHU_NET_ERRNO != SHU_NET_EINPROGRESS) { close(fd); return -1; }
        if (shu_net_poll_writable(fd, timeout_ms) != 0) { close(fd); return -1; }
        int err = 0;
        socklen_t errlen = sizeof(err);
        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) != 0 || err != 0) { close(fd); return -1; }
    }
    return (int32_t)fd;
#endif
}

/** 在 IPv6 addr:port 上 TCP 监听。addr_16 为 16 字节。返回 listener fd，失败 -1。非阻塞。 */
int32_t net_tcp_listen_ipv6_c(const uint8_t *addr_16, uint32_t port_u32) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
        wsa_done = 1;
    }
#endif
    struct sockaddr_in6 sin6;
    shu_net_set_addr_port_ipv6(&sin6, addr_16, port_u32);

#if defined(_WIN32) || defined(_WIN64)
    SOCKET s = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return -1;
    { int one = 1; setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(one)); }
    if (bind(s, (struct sockaddr *)&sin6, (int)sizeof(sin6)) != 0) { closesocket(s); return -1; }
    if (listen(s, 128) != 0) { closesocket(s); return -1; }
    if (shu_net_set_nonblock((int)s) != 0) { closesocket(s); return -1; }
    return (int32_t)s;
#else
    int fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    { int one = 1; setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)); }
    if (bind(fd, (struct sockaddr *)&sin6, sizeof(sin6)) != 0) { close(fd); return -1; }
    if (listen(fd, 128) != 0) { close(fd); return -1; }
    if (shu_net_set_nonblock(fd) != 0) { close(fd); return -1; }
    return (int32_t)fd;
#endif
}

/* ========== DNS（阻塞解析，返回首个 IPv4）========== */

/** 将 hostname（NUL 结尾）解析为 IPv4 地址；返回 addr_u32，失败返回 0（不可与 0.0.0.0 区分，调用方可用 resolve 后再查错误）。 */
uint32_t net_resolve_ipv4_c(const char *hostname) {
#if defined(_WIN32) || defined(_WIN64)
    static int wsa_done;
    if (!wsa_done) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 0;
        wsa_done = 1;
    }
#endif
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
#ifdef AI_ADDRCONFIG
    hints.ai_flags = AI_ADDRCONFIG;
#endif
    if (getaddrinfo(hostname, NULL, &hints, &res) != 0 || !res) return 0;
    uint32_t addr_u32 = 0;
    if (res->ai_family == AF_INET && res->ai_addr && res->ai_addrlen >= sizeof(struct sockaddr_in)) {
        addr_u32 = ntohl(((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr);
    }
    if (res) freeaddrinfo(res);
    return addr_u32;
}
