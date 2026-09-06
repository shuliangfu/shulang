/* seeds/runtime_net_udp_batch.from_x.c — G-02f-20 product TU
 * G-02f-102 helper gates.
 * Product: runtime_net_udp_batch.o; logic still C until full .x port.
 *
 * Cap residual 9.1.7 slice1: mmsg + poll via xlang_net_cap.h (no libc recvmmsg/sendmmsg).
 * mmsghdr/iovec batch syscalls; product paths in udp_batch.x.
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock Cap).
 */
#define _GNU_SOURCE

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#endif

#include <xlang_net_cap.h>

#ifndef XLANG_NET_UDP_GLUE_WEAK
#define XLANG_NET_UDP_GLUE_WEAK
#endif

#define XLANG_NET_UDP_GLUE_API XLANG_NET_UDP_GLUE_WEAK

#define XLANG_UDP_BATCH_MAX 2
#define XLANG_UDP_BATCH_BUF_MAX 8

/** 与 std.io.driver Buffer / net.c xlang_net_buf_t ABI 一致。 */
typedef struct {
    uint8_t *ptr;
    size_t length;
    size_t handle;
} xlang_net_buf_t;

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
void xlang_udp_batch_set_addr_port(struct sockaddr_in *sin, uint32_t addr_u32, uint32_t port_u32);
int xlang_udp_batch_poll_readable(int fd, uint32_t timeout_ms);

/** 填充 IPv4 sockaddr_in。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_udp_batch.x）提供 public wrapper */
void xlang_udp_batch_set_addr_port_impl(struct sockaddr_in *sin, uint32_t addr_u32, uint32_t port_u32) {
    memset(sin, 0, sizeof(*sin));
#if defined(__APPLE__)
    sin->sin_len = (uint8_t)sizeof(*sin);
#endif
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = htonl(addr_u32);
    sin->sin_port = htons((uint16_t)(port_u32 & 0xFFFFu));
}

#ifndef XLANG_RUNTIME_NET_UDP_BATCH_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
void xlang_udp_batch_set_addr_port(struct sockaddr_in *sin, uint32_t addr_u32, uint32_t port_u32) {
    xlang_udp_batch_set_addr_port_impl(sin, addr_u32, port_u32);
}
#endif

/** poll 可读；失败 -1。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_udp_batch.x）提供 public wrapper */
int xlang_udp_batch_poll_readable_impl(int fd, uint32_t timeout_ms) {
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    /* Cap residual 9.1.7: poll via xlang_net_cap.h (slice0). PLATFORM: SHARED Cap */
    int n = xlang_net_poll((void *)&pfd, 1u, (int)(timeout_ms ? timeout_ms : (-1)));
    if (n <= 0 || (pfd.revents & (POLLERR | POLLHUP)))
        return -1;
    return 0;
}

#ifndef XLANG_RUNTIME_NET_UDP_BATCH_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int xlang_udp_batch_poll_readable(int fd, uint32_t timeout_ms) {
    return xlang_udp_batch_poll_readable_impl(fd, timeout_ms);
}
#endif

/**
 * recvmmsg：最多 2 段；timeout_ms 非 0 时先 poll。
 * 返回收到报文数；EAGAIN 返回 0；其它错误 -1。
 * PLATFORM: SHARED Cap
 */
XLANG_NET_UDP_GLUE_API int xlang_net_udp_recvmmsg2_c(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, int n,
    uint32_t timeout_ms, int32_t *out_sizes, uint32_t *out_addrs, uint32_t *out_ports) {
    struct iovec iov[XLANG_UDP_BATCH_MAX];
    struct sockaddr_in addrs[XLANG_UDP_BATCH_MAX];
    struct mmsghdr msgvec[XLANG_UDP_BATCH_MAX];
    unsigned int i;
    int r;

    if (n <= 0 || n > XLANG_UDP_BATCH_MAX || !out_sizes || !out_addrs || !out_ports)
        return -1;
    for (i = 0; i < (unsigned int)n; i++) {
        socklen_t addrlen = (socklen_t)sizeof(addrs[0]);
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
        if (xlang_udp_batch_poll_readable((int)fd, timeout_ms) != 0)
            return -1;
    }
    r = xlang_net_recvmmsg((int)fd, (void *)msgvec, (unsigned int)n, 0, NULL);
    if (r < 0)
        return (errno == EAGAIN) ? 0 : -1;
    for (i = 0; i < (unsigned int)r; i++) {
        out_sizes[i] = (int32_t)msgvec[i].msg_len;
        out_addrs[i] = ntohl(addrs[i].sin_addr.s_addr);
        out_ports[i] = (uint32_t)ntohs(addrs[i].sin_port);
    }
    for (i = (unsigned int)r; i < (unsigned int)n; i++)
        out_sizes[i] = 0;
    return r;
}

/**
 * sendmmsg：最多 2 条目标报文。
 * PLATFORM: SHARED Cap
 */
XLANG_NET_UDP_GLUE_API int xlang_net_udp_sendmmsg2_c(int32_t fd, uint32_t a0, uint32_t port0, const uint8_t *p0, size_t l0,
    uint32_t a1, uint32_t port1, const uint8_t *p1, size_t l1, int n) {
    struct sockaddr_in addrs[XLANG_UDP_BATCH_MAX];
    struct iovec iov[XLANG_UDP_BATCH_MAX];
    struct mmsghdr msgvec[XLANG_UDP_BATCH_MAX];
    unsigned int i;
    int r;

    if (n <= 0 || n > XLANG_UDP_BATCH_MAX)
        return -1;
    for (i = 0; i < (unsigned int)n; i++) {
        xlang_udp_batch_set_addr_port(&addrs[i], (i == 0) ? a0 : a1, (i == 0) ? port0 : port1);
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
    r = xlang_net_sendmmsg((int)fd, (void *)msgvec, (unsigned int)n, 0);
    return (r < 0) ? -1 : r;
}

/**
 * recvmmsg：Buffer 切片，n 为 1..8。
 * PLATFORM: SHARED Cap
 */
XLANG_NET_UDP_GLUE_API int xlang_net_udp_recvmmsg_buf_c(int32_t fd, xlang_net_buf_t *bufs, int n, uint32_t timeout_ms,
    int32_t *out_sizes, uint32_t *out_addrs, uint32_t *out_ports) {
    struct iovec iov[XLANG_UDP_BATCH_BUF_MAX];
    struct sockaddr_in addrs[XLANG_UDP_BATCH_BUF_MAX];
    struct mmsghdr msgvec[XLANG_UDP_BATCH_BUF_MAX];
    unsigned int i;
    int r;

    if (n <= 0 || n > XLANG_UDP_BATCH_BUF_MAX || !bufs || !out_sizes || !out_addrs || !out_ports)
        return -1;
    for (i = 0; i < (unsigned int)n; i++) {
        socklen_t addrlen = (socklen_t)sizeof(addrs[0]);
        iov[i].iov_base = bufs[i].ptr;
        iov[i].iov_len  = bufs[i].length;
        msgvec[i].msg_hdr.msg_name = &addrs[i];
        msgvec[i].msg_hdr.msg_namelen = addrlen;
        msgvec[i].msg_hdr.msg_iov = &iov[i];
        msgvec[i].msg_hdr.msg_iovlen = 1;
        msgvec[i].msg_hdr.msg_control = NULL;
        msgvec[i].msg_hdr.msg_controllen = 0;
        msgvec[i].msg_hdr.msg_flags = 0;
    }
    if (timeout_ms != 0) {
        if (xlang_udp_batch_poll_readable((int)fd, timeout_ms) != 0)
            return -1;
    }
    r = xlang_net_recvmmsg((int)fd, (void *)msgvec, (unsigned int)n, 0, NULL);
    if (r < 0)
        return (errno == EAGAIN) ? 0 : -1;
    for (i = 0; i < (unsigned int)r; i++) {
        out_sizes[i] = (int32_t)msgvec[i].msg_len;
        out_addrs[i] = ntohl(addrs[i].sin_addr.s_addr);
        out_ports[i] = (uint32_t)ntohs(addrs[i].sin_port);
    }
    for (i = (unsigned int)r; i < (unsigned int)n; i++)
        out_sizes[i] = 0;
    return r;
}

/**
 * sendmmsg：Buffer 切片，n 为 1..8。
 * PLATFORM: SHARED Cap
 */
XLANG_NET_UDP_GLUE_API int xlang_net_udp_sendmmsg_buf_c(int32_t fd, const uint32_t *addrs_u32, const uint32_t *ports,
    const xlang_net_buf_t *bufs, int n) {
    struct sockaddr_in addrs[XLANG_UDP_BATCH_BUF_MAX];
    struct iovec iov[XLANG_UDP_BATCH_BUF_MAX];
    struct mmsghdr msgvec[XLANG_UDP_BATCH_BUF_MAX];
    unsigned int i;
    int r;

    if (n <= 0 || n > XLANG_UDP_BATCH_BUF_MAX || !addrs_u32 || !ports || !bufs)
        return -1;
    for (i = 0; i < (unsigned int)n; i++) {
        xlang_udp_batch_set_addr_port(&addrs[i], addrs_u32[i], ports[i]);
        iov[i].iov_base = bufs[i].ptr;
        iov[i].iov_len  = bufs[i].length;
        msgvec[i].msg_hdr.msg_name = &addrs[i];
        msgvec[i].msg_hdr.msg_namelen = sizeof(addrs[i]);
        msgvec[i].msg_hdr.msg_iov = &iov[i];
        msgvec[i].msg_hdr.msg_iovlen = 1;
        msgvec[i].msg_hdr.msg_control = NULL;
        msgvec[i].msg_hdr.msg_controllen = 0;
        msgvec[i].msg_hdr.msg_flags = 0;
    }
    r = xlang_net_sendmmsg((int)fd, (void *)msgvec, (unsigned int)n, 0);
    return (r < 0) ? -1 : r;
}
