/* seeds/runtime_net_ipv6_fast.from_x.c — G-02f-20 product TU
 * G-02f-104 helper gates.
 * Product: ../std/net/net_ipv6_fast.o; logic still C until full .x port.
 *
 * Cap residual 9.1.7: socket/connect/poll/close via xlang_net_cap.h on Linux, Darwin, and Windows.
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock Cap).
 */
#include <stdint.h>
#include <string.h>
#include <errno.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#endif

#include <xlang_net_cap.h>

#ifndef AF_INET6
#if defined(__APPLE__)
#define AF_INET6 30
#elif defined(_WIN32) || defined(_WIN64)
#define AF_INET6 23
#else
#define AF_INET6 10
#endif
#endif

#ifndef SOCK_STREAM
#define SOCK_STREAM 1
#endif
#ifndef IPPROTO_TCP
#define IPPROTO_TCP 6
#endif
#ifndef SOL_SOCKET
#if defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
#define SOL_SOCKET 0xffff
#else
#define SOL_SOCKET 1
#endif
#endif
#ifndef SO_REUSEADDR
#if defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)
#define SO_REUSEADDR 0x0004
#else
#define SO_REUSEADDR 2
#endif
#endif
#ifndef SO_ERROR
#if defined(__APPLE__)
#define SO_ERROR 0x1007
#elif defined(_WIN32) || defined(_WIN64)
#define SO_ERROR 0x1007
#else
#define SO_ERROR 4
#endif
#endif

#ifndef POLLOUT
#define POLLOUT 4
#endif
#ifndef POLLERR
#define POLLERR 8
#endif
#ifndef POLLHUP
#define POLLHUP 16
#endif

/* 【Why 根源】asm codegen 对 u16 间接 store 会错发 64 位 store；IPv6 sockaddr_in6 填充须走 C。
 * 从 net_import_alias.c 迁入（F-闭合消除 *_import_alias.c 命名）。
 * 【Invariant】sin 指向至少 28 字节可写缓冲（sizeof(sockaddr_in6)==28）；addr_16 为 16 字节 IPv6 地址。
 * 【Asm/Perf】memset/memcpy 编译为向量指令（SSE2/NEON）。
 * PLATFORM: SHARED Cap */
void net_ipv6_set_addr_port_buf_c(uint8_t *sin, uint8_t *addr_16, uint32_t port_u32) {
    struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)(void *)sin;
    memset(sa6, 0, sizeof(*sa6));
#if defined(__APPLE__)
    sa6->sin6_len = (uint8_t)sizeof(*sa6);
#endif
    sa6->sin6_family = AF_INET6;
    sa6->sin6_port = htons((uint16_t)(port_u32 & 0xffffu));
    sa6->sin6_flowinfo = 0;
    memcpy(&sa6->sin6_addr, addr_16, 16);
}

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
int32_t net_ipv6_ensure_wsa_c(void);
int32_t net_ipv6_close_socket_c(int32_t fd);
int32_t net_ipv6_set_nonblock_c(int32_t fd);
int32_t net_ipv6_poll_writable_c(int32_t fd, uint32_t timeout_ms);
int32_t net_ipv6_connect_retry_ok_c(void);

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_ipv6_fast.x）提供 public wrapper */
int32_t net_ipv6_ensure_wsa_c_impl_c(void) {
    return xlang_net_ensure_wsa();
}

#ifndef XLANG_RUNTIME_NET_IPV6_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_ipv6_ensure_wsa_c(void) {
    return net_ipv6_ensure_wsa_c_impl_c();
}
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_ipv6_fast.x）提供 public wrapper */
int32_t net_ipv6_close_socket_c_impl_c(int32_t fd) {
    return xlang_net_close((int)fd) == 0 ? 0 : -1;
}

#ifndef XLANG_RUNTIME_NET_IPV6_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_ipv6_close_socket_c(int32_t fd) {
    return net_ipv6_close_socket_c_impl_c(fd);
}
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_ipv6_fast.x）提供 public wrapper */
int32_t net_ipv6_set_nonblock_c_impl_c(int32_t fd) {
    return xlang_net_fcntl((int)fd, F_SETFL, O_NONBLOCK) == 0 ? 0 : -1;
}

#ifndef XLANG_RUNTIME_NET_IPV6_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_ipv6_set_nonblock_c(int32_t fd) {
    return net_ipv6_set_nonblock_c_impl_c(fd);
}
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_ipv6_fast.x）提供 public wrapper */
int32_t net_ipv6_poll_writable_c_impl_c(int32_t fd, uint32_t timeout_ms) {
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLOUT;
    pfd.revents = 0;
    int n = xlang_net_poll((void *)&pfd, 1u, (int)timeout_ms);
    if (n <= 0 || (pfd.revents & (POLLERR | POLLHUP)) != 0)
        return -1;
    return 0;
}

#ifndef XLANG_RUNTIME_NET_IPV6_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_ipv6_poll_writable_c(int32_t fd, uint32_t timeout_ms) {
    return net_ipv6_poll_writable_c_impl_c(fd, timeout_ms);
}
#endif

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_net_ipv6_fast.x）提供 public wrapper */
int32_t net_ipv6_connect_retry_ok_c_impl_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    return 1;
#else
    return (errno == EINPROGRESS || errno == EAGAIN) ? 1 : 0;
#endif
}

#ifndef XLANG_RUNTIME_NET_IPV6_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_ipv6_connect_retry_ok_c(void) {
    return net_ipv6_connect_retry_ok_c_impl_c();
}
#endif

int32_t net_tcp_connect_ipv6_c(uint8_t *addr_16, uint32_t port_u32, uint32_t timeout_ms) {
    uint8_t sin_mem[28];
    int32_t fd;
    if (net_ipv6_ensure_wsa_c() != 0)
        return -1;
    if (!addr_16)
        return -1;
    net_ipv6_set_addr_port_buf_c(&sin_mem[0], addr_16, port_u32);
    fd = (int32_t)xlang_net_socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0)
        return -1;
    if (net_ipv6_set_nonblock_c(fd) != 0) {
        net_ipv6_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_connect((int)fd, (const void *)&sin_mem[0], 28) != 0) {
        if (net_ipv6_connect_retry_ok_c() == 0) {
            net_ipv6_close_socket_c(fd);
            return -1;
        }
        if (net_ipv6_poll_writable_c(fd, timeout_ms) != 0) {
            net_ipv6_close_socket_c(fd);
            return -1;
        }
    }
    return fd;
}

int32_t net_tcp_listen_ipv6_c(uint8_t *addr_16, uint32_t port_u32) {
    uint8_t sin_mem[28];
    int32_t fd;
    int32_t one = 1;
    if (net_ipv6_ensure_wsa_c() != 0)
        return -1;
    if (!addr_16)
        return -1;
    net_ipv6_set_addr_port_buf_c(&sin_mem[0], addr_16, port_u32);
    fd = (int32_t)xlang_net_socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0)
        return -1;
    (void)xlang_net_setsockopt((int)fd, SOL_SOCKET, SO_REUSEADDR, &one, (unsigned int)sizeof(one));
    if (xlang_net_bind((int)fd, (const void *)&sin_mem[0], 28) != 0) {
        net_ipv6_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_listen((int)fd, 128) != 0) {
        net_ipv6_close_socket_c(fd);
        return -1;
    }
    if (net_ipv6_set_nonblock_c(fd) != 0) {
        net_ipv6_close_socket_c(fd);
        return -1;
    }
    return fd;
}
