/* seeds/runtime_net_sock_fast.from_x.c — G-02f-20 product TU
 * G-02f-104 helper gates.
 * Product: ../std/net/net_sock_fast.o; logic still C until full .x port.
 *
 * Cap residual 9.1.7: Linux, Darwin, and Windows socket/connect/bind/listen/accept/poll/close
 * via xlang_net_cap.h (zero libc net symbols on Linux & Darwin). Completes xlang_sys_* net bodies.
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock Cap).
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <xlang_net_cap.h>

#ifndef AF_INET
#define AF_INET 2
#endif
#ifndef SOCK_STREAM
#define SOCK_STREAM 1
#endif
#ifndef SOCK_DGRAM
#define SOCK_DGRAM 2
#endif
#ifndef IPPROTO_TCP
#define IPPROTO_TCP 6
#endif
#ifndef IPPROTO_UDP
#define IPPROTO_UDP 17
#endif
#ifndef SOL_SOCKET
#if defined(__APPLE__)
#define SOL_SOCKET 0xffff
#elif defined(_WIN32) || defined(_WIN64)
#define SOL_SOCKET 0xffff
#else
#define SOL_SOCKET 1
#endif
#endif
#ifndef SO_REUSEADDR
#if defined(_WIN32) || defined(_WIN64)
#define SO_REUSEADDR 0x0004
#elif defined(__APPLE__)
#define SO_REUSEADDR 0x0004
#else
#define SO_REUSEADDR 2
#endif
#endif

/* 前向声明：net_tcp_set_addr_port_buf_c / net_udp_set_addr_port_buf_c 由 runtime_net_addr_fast.c 提供。 */
extern void net_tcp_set_addr_port_buf_c(uint8_t *sin, uint32_t addr_u32, uint32_t port_u32);
extern void net_udp_set_addr_port_buf_c(uint8_t *sin, uint32_t addr_u32, uint32_t port_u32);

/*
 * PLATFORM: LINUX|MACOS — errno TLS pointer for std/net tcp/udp/ipv6.
 * Why: product .x cfg bodies may emit calls to bare net_*_errno_ptr[_c] while
 * the same-name cfg export is missing or mangles to std_net_*_net_*_errno_ptr;
 * host-cc gen C on Darwin may call __error without a prototype. Authority for
 * short C link names lives here (merged into net.o via sock_fast).
 * Weak so a future full .x no_mangle body can override without duplicate hard.
 */
#if defined(_WIN32) || defined(_WIN64)
/* Winsock: errno via WSAGetLastError — not used by POSIX net_*_errno_ptr paths. */
#else
#if defined(__APPLE__)
extern int *__error(void);
static int32_t *xlang_net_errno_ptr(void) { return (int32_t *)__error(); }
#else
#include <errno.h>
static int32_t *xlang_net_errno_ptr(void) { return (int32_t *)__errno_location(); }
#endif
XLANG_WEAK int32_t *net_tcp_errno_ptr(void) { return xlang_net_errno_ptr(); }
XLANG_WEAK int32_t *net_tcp_errno_ptr_c(void) { return xlang_net_errno_ptr(); }
XLANG_WEAK int32_t *net_udp_errno_ptr(void) { return xlang_net_errno_ptr(); }
XLANG_WEAK int32_t *net_udp_errno_ptr_c(void) { return xlang_net_errno_ptr(); }
XLANG_WEAK int32_t *net_ipv6_errno_ptr(void) { return xlang_net_errno_ptr(); }
XLANG_WEAK int32_t *net_ipv6_errno_ptr_c(void) { return xlang_net_errno_ptr(); }
#endif

/*
 * 【Why 根源】std/net 下 .x 经 -backend asm 出 .o 时，extern xlang_sys_poll 为真 U 符号；
 * C 前端 user TU 靠 preamble static inline，不会导出给 net.o。
 * 权威体放 net.o 合并的 sock_fast（与 net_close_socket_c 同层），asm/C 两路径可链。
 * Cap residual 9.1.7: poll via xlang_net_cap.h (raw syscall on Linux & Darwin, WSAPoll on Windows).
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_poll(uint8_t *fds, int32_t nfds, int32_t timeout) {
    if (fds == 0 || nfds <= 0)
        return -1;
    return (int32_t)xlang_net_poll((void *)fds, (unsigned int)nfds, (int)timeout);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_socket body for std.sys.linux wrappers.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_socket(int32_t domain, int32_t sock_type, int32_t protocol) {
    return (int32_t)xlang_net_socket((int)domain, (int)sock_type, (int)protocol);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_connect body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_connect(int32_t sockfd, uint8_t *addr, int32_t addrlen) {
    if (addr == 0 || addrlen <= 0)
        return -1;
    return xlang_net_connect((int)sockfd, (const void *)addr, (unsigned int)addrlen);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_bind body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_bind(int32_t sockfd, uint8_t *addr, int32_t addrlen) {
    if (addr == 0 || addrlen <= 0)
        return -1;
    return xlang_net_bind((int)sockfd, (const void *)addr, (unsigned int)addrlen);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_listen body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_listen(int32_t sockfd, int32_t backlog) {
    return xlang_net_listen((int)sockfd, (int)backlog);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_accept body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_accept(int32_t sockfd, uint8_t *addr, int32_t *addrlen) {
    unsigned int al = addrlen ? (unsigned int)(*addrlen) : 0;
    int r = xlang_net_accept((int)sockfd, (void *)addr, addrlen ? &al : NULL);
    if (addrlen)
        *addrlen = (int32_t)al;
    return (int32_t)r;
}

/**
 * Cap residual 9.1.7: complete xlang_sys_sendto body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_sendto(int32_t sockfd, const uint8_t *buf, int32_t len, int32_t flags, const uint8_t *addr, int32_t addrlen) {
    if (len < 0) return -1;
    return (int32_t)xlang_net_sendto((int)sockfd, (const void *)buf, (size_t)len, (int)flags, (const void *)addr, (unsigned int)addrlen);
}

/**
 * Cap residual 9.1.7: complete xlang_sys_recvfrom body.
 * PLATFORM: SHARED Cap
 */
int32_t xlang_sys_recvfrom(int32_t sockfd, uint8_t *buf, int32_t len, int32_t flags, uint8_t *addr, int32_t *addrlen) {
    if (len < 0) return -1;
    unsigned int al = addrlen ? (unsigned int)(*addrlen) : 0;
    long r = xlang_net_recvfrom((int)sockfd, (void *)buf, (size_t)len, (int)flags, (void *)addr, addrlen ? &al : NULL);
    if (addrlen)
        *addrlen = (int32_t)al;
    return (int32_t)r;
}

/* 【Why 根源】Windows Winsock 须先 WSAStartup 才能 socket/bind/listen。
 * 从 net_import_alias.c 迁入（F-闭合消除 *_import_alias.c 命名）。
 * 【Invariant】net_ensure_wsa 防重复初始化；由 Cap 统一维护。
 * 【Asm/Perf】constructor 仅执行一次，热路径无开销。
 * PLATFORM: SHARED Cap */
void net_ensure_wsa_impl_c(void) {
    xlang_net_ensure_wsa();
}

#ifndef XLANG_RUNTIME_NET_SOCK_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
void net_ensure_wsa(void) {
    net_ensure_wsa_impl_c();
}
#endif

__attribute__((constructor(65534)))
void net_wsa_ctor_impl_c(void) {
    net_ensure_wsa_impl_c();
}

#ifndef XLANG_RUNTIME_NET_SOCK_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
void net_wsa_ctor(void) {
    net_ensure_wsa();
}
#endif

int32_t net_set_blocking_c(int32_t fd, int32_t blocking) {
    if (fd < 0)
        return -1;
    long flags = blocking != 0 ? 0 : O_NONBLOCK;
    return xlang_net_fcntl((int)fd, F_SETFL, flags) == 0 ? 0 : -1;
}

/* 【Why 根源】sock.x 单文件 co-emit 时 net_close_socket_c 可能被 WPO 剔除；C 实现保证 net.o 可链。
 * Cap residual 9.1.7: close via xlang_net_cap.h.
 * 【Invariant】fd < 0 时 no-op 返回 0；成功返回 0，失败返回 -1。
 * PLATFORM: SHARED Cap */
int32_t net_close_socket_c(int32_t fd) {
    if (fd < 0)
        return 0;
    return xlang_net_close((int)fd) == 0 ? 0 : -1;
}

/* 【Why 根源】asm codegen 对 socket/bind/listen/setsockopt 字面量实参有误；listen 烟测须走 C。
 * Cap residual 9.1.7: socket/bind/listen/setsockopt via xlang_net_cap.h.
 * 【Invariant】fd < 0 表示失败；成功返回的 fd 已设为非阻塞。
 * 【Asm/Perf】setsockopt(SO_REUSEADDR) 仅 listen 前一次调用，非热路径。
 * PLATFORM: SHARED Cap */
int32_t net_tcp_listen_c(uint32_t addr_u32, uint32_t port_u32) {
    uint8_t sin[16];
    int32_t fd;
    int one = 1;
    net_tcp_set_addr_port_buf_c(sin, addr_u32, port_u32);
    fd = (int32_t)xlang_net_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0)
        return -1;
    if (xlang_net_setsockopt((int)fd, SOL_SOCKET, SO_REUSEADDR, &one, (unsigned int)sizeof(one)) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_bind((int)fd, (const void *)sin, 16) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_listen((int)fd, 128) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_fcntl((int)fd, F_SETFL, O_NONBLOCK) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    return fd;
}

/* 【Why 根源】asm codegen 对 socket/bind/setsockopt 字面量实参有误；UDP bind 须走 C。
 * Cap residual 9.1.7: socket/bind/setsockopt via xlang_net_cap.h.
 * 【Invariant】fd < 0 表示失败；成功返回的 fd 已设为非阻塞。
 * PLATFORM: SHARED Cap */
int32_t net_udp_bind_c(uint32_t addr_u32, uint32_t port_u32) {
    uint8_t sin[16];
    int32_t fd;
    int one = 1;
    net_udp_set_addr_port_buf_c(sin, addr_u32, port_u32);
    fd = (int32_t)xlang_net_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0)
        return -1;
    if (xlang_net_setsockopt((int)fd, SOL_SOCKET, SO_REUSEADDR, &one, (unsigned int)sizeof(one)) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_bind((int)fd, (const void *)sin, 16) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    if (xlang_net_fcntl((int)fd, F_SETFL, O_NONBLOCK) != 0) {
        net_close_socket_c(fd);
        return -1;
    }
    return fd;
}
