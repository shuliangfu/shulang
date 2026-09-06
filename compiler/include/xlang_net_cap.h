/*
 * xlang_net_cap.h — Cap residual 9.1.7: socket/connect/bind/listen/accept/poll/close
 * (slice0) + recvmmsg/sendmmsg (slice1) + sendto/recvfrom (slice2 DNS) without
 * libc those symbols on Linux and Darwin via raw syscalls, and Windows via Winsock Cap.
 * Cap residual 9.1.9: syscall asm via xlang_syscall_cap.h on Linux.
 *
 * Single authority for runtime_net_sock_fast, runtime_net_udp_batch,
 * xlang_dns_cap.h, and xlang_sys_* net symbols.
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock).
 */

#ifndef XLANG_NET_CAP_H
#define XLANG_NET_CAP_H

#include <stddef.h>
#include <stdint.h>

#ifndef F_GETFL
#define F_GETFL 3
#endif
#ifndef F_SETFL
#define F_SETFL 4
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK 0x0004
#endif

/* ============================================================================
 * PLATFORM: WINDOWS (Winsock Cap)
 * ============================================================================ */
#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

struct msghdr {
  void         *msg_name;
  int           msg_namelen;
  struct {
    void   *iov_base;
    size_t  iov_len;
  }            *msg_iov;
  int           msg_iovlen;
  void         *msg_control;
  size_t        msg_controllen;
  int           msg_flags;
};

struct mmsghdr {
  struct msghdr msg_hdr;
  unsigned int  msg_len;
};

/** Ensure WSAStartup has run once. PLATFORM: WINDOWS */
static inline int xlang_net_ensure_wsa(void) {
  static int wsa_inited = 0;
  if (!wsa_inited) {
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d) == 0) {
      wsa_inited = 1;
    } else {
      return -1;
    }
  }
  return 0;
}

/** Cap socket for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_socket(int domain, int type, int protocol) {
  if (xlang_net_ensure_wsa() != 0)
    return -1;
  SOCKET s = socket(domain, type, protocol);
  return s == INVALID_SOCKET ? -1 : (int)s;
}

/** Cap connect for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_connect(int sockfd, const void *addr, unsigned int addrlen) {
  if (connect((SOCKET)sockfd, (const struct sockaddr *)addr, (int)addrlen) != 0)
    return -1;
  return 0;
}

/** Cap bind for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_bind(int sockfd, const void *addr, unsigned int addrlen) {
  if (bind((SOCKET)sockfd, (const struct sockaddr *)addr, (int)addrlen) != 0)
    return -1;
  return 0;
}

/** Cap listen for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_listen(int sockfd, int backlog) {
  if (listen((SOCKET)sockfd, backlog) != 0)
    return -1;
  return 0;
}

/** Cap accept for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_accept(int sockfd, void *addr, unsigned int *addrlen) {
  int al = addrlen ? (int)(*addrlen) : 0;
  SOCKET s = accept((SOCKET)sockfd, (struct sockaddr *)addr, addrlen ? &al : NULL);
  if (addrlen)
    *addrlen = (unsigned int)al;
  return s == INVALID_SOCKET ? -1 : (int)s;
}

/** Cap setsockopt for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_setsockopt(int sockfd, int level, int optname, const void *optval,
                                      unsigned int optlen) {
  return setsockopt((SOCKET)sockfd, level, optname, (const char *)optval, (int)optlen) == 0 ? 0 : -1;
}

/** Cap close (closesocket) for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_close(int fd) {
  if (fd < 0)
    return 0;
  return closesocket((SOCKET)fd) == 0 ? 0 : -1;
}

/** Cap poll (WSAPoll) for Windows. PLATFORM: WINDOWS */
static inline int xlang_net_poll(void *fds, unsigned int nfds, int timeout_ms) {
  if (!fds && nfds != 0)
    return -1;
  return WSAPoll((WSAPOLLFD *)fds, (ULONG)nfds, timeout_ms);
}

/** Cap sendto for Windows. PLATFORM: WINDOWS */
static inline long xlang_net_sendto(int sockfd, const void *buf, size_t len, int flags,
                                   const void *addr, unsigned int addrlen) {
  int r = sendto((SOCKET)sockfd, (const char *)buf, (int)len, flags,
                 (const struct sockaddr *)addr, (int)addrlen);
  return (long)r;
}

/** Cap recvfrom for Windows. PLATFORM: WINDOWS */
static inline long xlang_net_recvfrom(int sockfd, void *buf, size_t len, int flags, void *addr,
                                     unsigned int *addrlen) {
  int al = addrlen ? (int)(*addrlen) : 0;
  int r = recvfrom((SOCKET)sockfd, (char *)buf, (int)len, flags,
                   (struct sockaddr *)addr, addrlen ? &al : NULL);
  if (addrlen)
    *addrlen = (unsigned int)al;
  return (long)r;
}

/** Cap fcntl simulation for Windows (O_NONBLOCK via ioctlsocket FIONBIO). PLATFORM: WINDOWS */
static inline int xlang_net_fcntl(int fd, int cmd, long arg) {
  if (cmd == F_SETFL) {
    u_long mode = (arg & O_NONBLOCK) ? 1UL : 0UL;
    return ioctlsocket((SOCKET)fd, FIONBIO, &mode) == 0 ? 0 : -1;
  }
  return 0;
}

/** Cap recvmmsg simulation for Windows via recvfrom loop. PLATFORM: WINDOWS */
static inline int xlang_net_recvmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags,
                                     void *timeout) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  (void)timeout;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *from = m[i].msg_hdr.msg_name;
    unsigned int fromlen = (unsigned int)m[i].msg_hdr.msg_namelen;
    long r = xlang_net_recvfrom(sockfd, buf, len, flags, from, &fromlen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_hdr.msg_namelen = (int)fromlen;
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/** Cap sendmmsg simulation for Windows via sendto loop. PLATFORM: WINDOWS */
static inline int xlang_net_sendmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *to = m[i].msg_hdr.msg_name;
    unsigned int tolen = (unsigned int)m[i].msg_hdr.msg_namelen;
    long r = xlang_net_sendto(sockfd, buf, len, flags, to, tolen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/* ============================================================================
 * PLATFORM: LINUX (Raw Syscall)
 * ============================================================================ */
#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <xlang_syscall_cap.h>

/** Cap residual 9.1.9: aliases → single syscall authority. */
#define xlang_net_syscall6 xlang_syscall6
#define xlang_net_syscall3 xlang_syscall3
#define xlang_net_syscall1 xlang_syscall1

/** Map negative kernel ret to -1 + errno. PLATFORM: LINUX. */
static inline int xlang_net_ret(long r) {
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/** No-op WSA startup on Linux. PLATFORM: LINUX */
static inline int xlang_net_ensure_wsa(void) {
  return 0;
}

/**
 * Cap residual socket(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_socket(int domain, int type, int protocol) {
  long r;
#if defined(__x86_64__)
  /* socket = 41 */
  r = xlang_net_syscall3(41, (long)domain, (long)type, (long)protocol);
#elif defined(__aarch64__)
  /* socket = 198 */
  r = xlang_net_syscall3(198, (long)domain, (long)type, (long)protocol);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual connect(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_connect(int sockfd, const void *addr, unsigned int addrlen) {
  long r;
  if (!addr && addrlen != 0)
    return -1;
#if defined(__x86_64__)
  /* connect = 42 */
  r = xlang_net_syscall3(42, (long)sockfd, (long)addr, (long)addrlen);
#elif defined(__aarch64__)
  /* connect = 203 */
  r = xlang_net_syscall3(203, (long)sockfd, (long)addr, (long)addrlen);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual bind(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_bind(int sockfd, const void *addr, unsigned int addrlen) {
  long r;
  if (!addr && addrlen != 0)
    return -1;
#if defined(__x86_64__)
  /* bind = 49 */
  r = xlang_net_syscall3(49, (long)sockfd, (long)addr, (long)addrlen);
#elif defined(__aarch64__)
  /* bind = 200 */
  r = xlang_net_syscall3(200, (long)sockfd, (long)addr, (long)addrlen);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual listen(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_listen(int sockfd, int backlog) {
  long r;
#if defined(__x86_64__)
  /* listen = 50 */
  r = xlang_net_syscall3(50, (long)sockfd, (long)backlog, 0);
#elif defined(__aarch64__)
  /* listen = 201 */
  r = xlang_net_syscall3(201, (long)sockfd, (long)backlog, 0);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual accept(2) (addr/addrlen may be NULL).
 * PLATFORM: LINUX
 */
static inline int xlang_net_accept(int sockfd, void *addr, unsigned int *addrlen) {
  long r;
#if defined(__x86_64__)
  /* accept = 43 */
  r = xlang_net_syscall3(43, (long)sockfd, (long)addr, (long)addrlen);
#elif defined(__aarch64__)
  /* accept = 202 */
  r = xlang_net_syscall3(202, (long)sockfd, (long)addr, (long)addrlen);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual setsockopt(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_setsockopt(int sockfd, int level, int optname, const void *optval,
                                      unsigned int optlen) {
  long r;
#if defined(__x86_64__)
  /* setsockopt = 54 */
  r = xlang_net_syscall6(54, (long)sockfd, (long)level, (long)optname, (long)optval, (long)optlen,
                         0);
#elif defined(__aarch64__)
  /* setsockopt = 208 */
  r = xlang_net_syscall6(208, (long)sockfd, (long)level, (long)optname, (long)optval, (long)optlen,
                         0);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual close(2).
 * PLATFORM: LINUX
 */
static inline int xlang_net_close(int fd) {
  long r;
#if defined(__x86_64__)
  /* close = 3 */
  r = xlang_net_syscall1(3, (long)fd);
#elif defined(__aarch64__)
  /* close = 57 */
  r = xlang_net_syscall1(57, (long)fd);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual poll(2).
 * x86_64: SYS_poll; aarch64: SYS_ppoll (no poll syscall).
 * @param timeout_ms -1 infinite; >=0 milliseconds
 * PLATFORM: LINUX
 */
static inline int xlang_net_poll(void *fds, unsigned int nfds, int timeout_ms) {
  long r;
  if (!fds && nfds != 0)
    return -1;
#if defined(__x86_64__)
  /* poll = 7 */
  r = xlang_net_syscall3(7, (long)fds, (long)nfds, (long)timeout_ms);
#elif defined(__aarch64__)
  /* ppoll = 73; convert ms timeout to timespec or NULL */
  {
    struct {
      long tv_sec;
      long tv_nsec;
    } ts;
    long tsp = 0;
    if (timeout_ms >= 0) {
      ts.tv_sec = (long)(timeout_ms / 1000);
      ts.tv_nsec = (long)(timeout_ms % 1000) * 1000000L;
      tsp = (long)&ts;
    }
    r = xlang_net_syscall6(73, (long)fds, (long)nfds, tsp, 0, 0, 0);
  }
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual recvmmsg(2).
 * x86_64 SYS_recvmmsg=299; aarch64 SYS_recvmmsg=243.
 * @param msgvec  struct mmsghdr * (void* to avoid pulling mmsg into Cap)
 * @param timeout struct timespec * or NULL
 * PLATFORM: LINUX
 */
static inline int xlang_net_recvmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags,
                                     void *timeout) {
  long r;
  if (!msgvec && vlen != 0)
    return -1;
#if defined(__x86_64__)
  /* recvmmsg = 299 */
  r = xlang_net_syscall6(299, (long)sockfd, (long)msgvec, (long)vlen, (long)flags, (long)timeout,
                         0);
#elif defined(__aarch64__)
  /* recvmmsg = 243 */
  r = xlang_net_syscall6(243, (long)sockfd, (long)msgvec, (long)vlen, (long)flags, (long)timeout,
                         0);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual sendmmsg(2).
 * x86_64 SYS_sendmmsg=307; aarch64 SYS_sendmmsg=269.
 * @param msgvec struct mmsghdr *
 * PLATFORM: LINUX
 */
static inline int xlang_net_sendmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags) {
  long r;
  if (!msgvec && vlen != 0)
    return -1;
#if defined(__x86_64__)
  /* sendmmsg = 307 */
  r = xlang_net_syscall6(307, (long)sockfd, (long)msgvec, (long)vlen, (long)flags, 0, 0);
#elif defined(__aarch64__)
  /* sendmmsg = 269 */
  r = xlang_net_syscall6(269, (long)sockfd, (long)msgvec, (long)vlen, (long)flags, 0, 0);
#endif
  return xlang_net_ret(r);
}

/**
 * Cap residual sendto(2) — DNS Cap (9.1.7 slice2) UDP query.
 * PLATFORM: LINUX
 */
static inline long xlang_net_sendto(int sockfd, const void *buf, size_t len, int flags,
                                   const void *addr, unsigned int addrlen) {
  long r;
  if (!buf && len != 0)
    return -1;
#if defined(__x86_64__)
  /* sendto = 44 */
  r = xlang_net_syscall6(44, (long)sockfd, (long)buf, (long)len, (long)flags, (long)addr,
                         (long)addrlen);
#elif defined(__aarch64__)
  /* sendto = 206 */
  r = xlang_net_syscall6(206, (long)sockfd, (long)buf, (long)len, (long)flags, (long)addr,
                         (long)addrlen);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual recvfrom(2) — DNS Cap (9.1.7 slice2) UDP reply.
 * PLATFORM: LINUX
 */
static inline long xlang_net_recvfrom(int sockfd, void *buf, size_t len, int flags, void *addr,
                                     unsigned int *addrlen) {
  long r;
  if (!buf && len != 0)
    return -1;
#if defined(__x86_64__)
  /* recvfrom = 45 */
  r = xlang_net_syscall6(45, (long)sockfd, (long)buf, (long)len, (long)flags, (long)addr,
                         (long)addrlen);
#elif defined(__aarch64__)
  /* recvfrom = 207 */
  r = xlang_net_syscall6(207, (long)sockfd, (long)buf, (long)len, (long)flags, (long)addr,
                         (long)addrlen);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual fcntl F_GETFL / F_SETFL (nonblock dial).
 * Only cmd F_GETFL (arg ignored) and F_SETFL (arg = flags) are supported.
 * PLATFORM: LINUX
 */
static inline int xlang_net_fcntl(int fd, int cmd, long arg) {
  long r;
#if defined(__x86_64__)
  /* fcntl = 72 */
  r = xlang_net_syscall3(72, (long)fd, (long)cmd, arg);
#elif defined(__aarch64__)
  /* fcntl = 25 */
  r = xlang_net_syscall3(25, (long)fd, (long)cmd, arg);
#endif
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/* ============================================================================
 * PLATFORM: MACOS|DARWIN (Raw Syscall)
 * ============================================================================ */
#elif defined(__APPLE__) && (defined(__x86_64__) || defined(__aarch64__))

#include <errno.h>
#include <sys/socket.h>
#include <poll.h>

#ifndef _MMSGHDR_DEFINED
#define _MMSGHDR_DEFINED
struct mmsghdr {
  struct msghdr msg_hdr;
  unsigned int   msg_len;
};
#endif

#if defined(__aarch64__)

static inline long xlang_darwin_net_syscall1(long num, long a1) {
  register long x16 __asm__("x16") = num;
  register long x0 __asm__("x0") = a1;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %1, cs"
      : "+r"(x0), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_net_syscall3(long num, long a1, long a2, long a3) {
  register long x16 __asm__("x16") = num;
  register long x0 __asm__("x0") = a1;
  register long x1 __asm__("x1") = a2;
  register long x2 __asm__("x2") = a3;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %3, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_net_syscall5(long num, long a1, long a2, long a3, long a4, long a5) {
  register long x16 __asm__("x16") = num;
  register long x0 __asm__("x0") = a1;
  register long x1 __asm__("x1") = a2;
  register long x2 __asm__("x2") = a3;
  register long x3 __asm__("x3") = a4;
  register long x4 __asm__("x4") = a5;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %5, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "+r"(x3), "+r"(x4), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -x0 : x0;
}

static inline long xlang_darwin_net_syscall6(long num, long a1, long a2, long a3, long a4, long a5, long a6) {
  register long x16 __asm__("x16") = num;
  register long x0 __asm__("x0") = a1;
  register long x1 __asm__("x1") = a2;
  register long x2 __asm__("x2") = a3;
  register long x3 __asm__("x3") = a4;
  register long x4 __asm__("x4") = a5;
  register long x5 __asm__("x5") = a6;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %6, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "+r"(x3), "+r"(x4), "+r"(x5), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -x0 : x0;
}

#elif defined(__x86_64__)

static inline long xlang_darwin_net_syscall1(long num, long a1) {
  long ret;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "negq %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000000L + num), "D"(a1)
      : "rcx", "r11", "memory", "cc"
  );
  return ret;
}

static inline long xlang_darwin_net_syscall3(long num, long a1, long a2, long a3) {
  long ret;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "negq %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000000L + num), "D"(a1), "S"(a2), "d"(a3)
      : "rcx", "r11", "memory", "cc"
  );
  return ret;
}

static inline long xlang_darwin_net_syscall5(long num, long a1, long a2, long a3, long a4, long a5) {
  long ret;
  register long r10 __asm__("r10") = a4;
  register long r8  __asm__("r8")  = a5;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "negq %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000000L + num), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
      : "rcx", "r11", "memory", "cc"
  );
  return ret;
}

static inline long xlang_darwin_net_syscall6(long num, long a1, long a2, long a3, long a4, long a5, long a6) {
  long ret;
  register long r10 __asm__("r10") = a4;
  register long r8  __asm__("r8")  = a5;
  register long r9  __asm__("r9")  = a6;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "negq %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000000L + num), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "r"(r9)
      : "rcx", "r11", "memory", "cc"
  );
  return ret;
}

#endif

/** Map negative kernel ret to -1 + errno. PLATFORM: MACOS|DARWIN. */
static inline int xlang_darwin_net_ret(long r) {
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/** No-op WSA startup on Darwin. PLATFORM: MACOS|DARWIN */
static inline int xlang_net_ensure_wsa(void) {
  return 0;
}

/**
 * Cap residual socket(2) for Darwin.
 * SYS_socket = 97.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_socket(int domain, int type, int protocol) {
  long r = xlang_darwin_net_syscall3(97, (long)domain, (long)type, (long)protocol);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual connect(2) for Darwin.
 * SYS_connect = 98.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_connect(int sockfd, const void *addr, unsigned int addrlen) {
  if (!addr && addrlen != 0)
    return -1;
  long r = xlang_darwin_net_syscall3(98, (long)sockfd, (long)addr, (long)addrlen);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual bind(2) for Darwin.
 * SYS_bind = 104.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_bind(int sockfd, const void *addr, unsigned int addrlen) {
  if (!addr && addrlen != 0)
    return -1;
  long r = xlang_darwin_net_syscall3(104, (long)sockfd, (long)addr, (long)addrlen);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual listen(2) for Darwin.
 * SYS_listen = 106.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_listen(int sockfd, int backlog) {
  long r = xlang_darwin_net_syscall3(106, (long)sockfd, (long)backlog, 0);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual accept(2) for Darwin.
 * SYS_accept = 30.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_accept(int sockfd, void *addr, unsigned int *addrlen) {
  long r = xlang_darwin_net_syscall3(30, (long)sockfd, (long)addr, (long)addrlen);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual setsockopt(2) for Darwin.
 * SYS_setsockopt = 105.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_setsockopt(int sockfd, int level, int optname, const void *optval,
                                      unsigned int optlen) {
  long r = xlang_darwin_net_syscall5(105, (long)sockfd, (long)level, (long)optname,
                                     (long)optval, (long)optlen);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual close(2) for Darwin.
 * SYS_close = 6.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_close(int fd) {
  long r = xlang_darwin_net_syscall1(6, (long)fd);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual poll(2) for Darwin.
 * SYS_poll = 230.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_poll(void *fds, unsigned int nfds, int timeout_ms) {
  if (!fds && nfds != 0)
    return -1;
  long r = xlang_darwin_net_syscall3(230, (long)fds, (long)nfds, (long)timeout_ms);
  return xlang_darwin_net_ret(r);
}

/**
 * Cap residual sendto(2) for Darwin.
 * SYS_sendto = 133.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline long xlang_net_sendto(int sockfd, const void *buf, size_t len, int flags,
                                   const void *addr, unsigned int addrlen) {
  if (!buf && len != 0)
    return -1;
  long r = xlang_darwin_net_syscall6(133, (long)sockfd, (long)buf, (long)len, (long)flags,
                                     (long)addr, (long)addrlen);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual recvfrom(2) for Darwin.
 * SYS_recvfrom = 29.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline long xlang_net_recvfrom(int sockfd, void *buf, size_t len, int flags, void *addr,
                                     unsigned int *addrlen) {
  if (!buf && len != 0)
    return -1;
  long r = xlang_darwin_net_syscall6(29, (long)sockfd, (long)buf, (long)len, (long)flags,
                                     (long)addr, (long)addrlen);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return r;
}

/**
 * Cap residual fcntl for Darwin.
 * SYS_fcntl = 92.
 * PLATFORM: MACOS|DARWIN raw syscall
 */
static inline int xlang_net_fcntl(int fd, int cmd, long arg) {
  long r = xlang_darwin_net_syscall3(92, (long)fd, (long)cmd, arg);
  if (r < 0) {
    errno = (int)(-r);
    return -1;
  }
  return (int)r;
}

/**
 * Cap residual recvmmsg simulation for Darwin via recvfrom loop.
 * PLATFORM: MACOS|DARWIN Cap
 */
static inline int xlang_net_recvmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags,
                                     void *timeout) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  (void)timeout;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *from = m[i].msg_hdr.msg_name;
    unsigned int fromlen = (unsigned int)m[i].msg_hdr.msg_namelen;
    long r = xlang_net_recvfrom(sockfd, buf, len, flags, from, &fromlen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_hdr.msg_namelen = (socklen_t)fromlen;
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/**
 * Cap residual sendmmsg simulation for Darwin via sendto loop.
 * PLATFORM: MACOS|DARWIN Cap
 */
static inline int xlang_net_sendmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *to = m[i].msg_hdr.msg_name;
    unsigned int tolen = (unsigned int)m[i].msg_hdr.msg_namelen;
    long r = xlang_net_sendto(sockfd, buf, len, flags, to, tolen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/* ============================================================================
 * PLATFORM: Generic POSIX fallback
 * ============================================================================ */
#else

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#ifndef _MMSGHDR_DEFINED
#define _MMSGHDR_DEFINED
struct mmsghdr {
  struct msghdr msg_hdr;
  unsigned int   msg_len;
};
#endif

/** No-op WSA startup on generic POSIX. PLATFORM: POSIX */
static inline int xlang_net_ensure_wsa(void) {
  return 0;
}

/** PLATFORM: POSIX fallback — libc socket. */
static inline int xlang_net_socket(int domain, int type, int protocol) {
  return (int)socket(domain, type, protocol);
}

/** PLATFORM: POSIX fallback — libc connect. */
static inline int xlang_net_connect(int sockfd, const void *addr, unsigned int addrlen) {
  return connect(sockfd, (const struct sockaddr *)addr, (socklen_t)addrlen);
}

/** PLATFORM: POSIX fallback — libc bind. */
static inline int xlang_net_bind(int sockfd, const void *addr, unsigned int addrlen) {
  return bind(sockfd, (const struct sockaddr *)addr, (socklen_t)addrlen);
}

/** PLATFORM: POSIX fallback — libc listen. */
static inline int xlang_net_listen(int sockfd, int backlog) {
  return listen(sockfd, backlog);
}

/** PLATFORM: POSIX fallback — libc accept. */
static inline int xlang_net_accept(int sockfd, void *addr, unsigned int *addrlen) {
  return accept(sockfd, (struct sockaddr *)addr, (socklen_t *)addrlen);
}

/** PLATFORM: POSIX fallback — libc setsockopt. */
static inline int xlang_net_setsockopt(int sockfd, int level, int optname, const void *optval,
                                      unsigned int optlen) {
  return setsockopt(sockfd, level, optname, optval, (socklen_t)optlen);
}

/** PLATFORM: POSIX fallback — libc close. */
static inline int xlang_net_close(int fd) {
  return close(fd);
}

/** PLATFORM: POSIX fallback — libc poll. */
static inline int xlang_net_poll(void *fds, unsigned int nfds, int timeout_ms) {
  return poll((struct pollfd *)fds, (nfds_t)nfds, timeout_ms);
}

/** PLATFORM: POSIX fallback — sendto loop simulation. */
static inline int xlang_net_sendmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *to = m[i].msg_hdr.msg_name;
    socklen_t tolen = (socklen_t)m[i].msg_hdr.msg_namelen;
    long r = (long)sendto(sockfd, buf, len, flags, (const struct sockaddr *)to, tolen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/** PLATFORM: POSIX fallback — recvfrom loop simulation. */
static inline int xlang_net_recvmmsg(int sockfd, void *msgvec, unsigned int vlen, int flags,
                                     void *timeout) {
  struct mmsghdr *m = (struct mmsghdr *)msgvec;
  unsigned int i;
  (void)timeout;
  if (!msgvec && vlen != 0)
    return -1;
  for (i = 0; i < vlen; i++) {
    void *buf = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_base : NULL;
    size_t len = m[i].msg_hdr.msg_iov ? m[i].msg_hdr.msg_iov[0].iov_len : 0;
    void *from = m[i].msg_hdr.msg_name;
    socklen_t fromlen = (socklen_t)m[i].msg_hdr.msg_namelen;
    long r = (long)recvfrom(sockfd, buf, len, flags, (struct sockaddr *)from, &fromlen);
    if (r < 0) {
      if (i > 0)
        return (int)i;
      return -1;
    }
    m[i].msg_hdr.msg_namelen = fromlen;
    m[i].msg_len = (unsigned int)r;
  }
  return (int)vlen;
}

/** PLATFORM: POSIX fallback — libc sendto. */
static inline long xlang_net_sendto(int sockfd, const void *buf, size_t len, int flags,
                                   const void *addr, unsigned int addrlen) {
  return (long)sendto(sockfd, buf, len, flags, (const struct sockaddr *)addr, (socklen_t)addrlen);
}

/** PLATFORM: POSIX fallback — libc recvfrom. */
static inline long xlang_net_recvfrom(int sockfd, void *buf, size_t len, int flags, void *addr,
                                     unsigned int *addrlen) {
  socklen_t al = addrlen ? (socklen_t)(*addrlen) : 0;
  long r = (long)recvfrom(sockfd, buf, len, flags, (struct sockaddr *)addr, addrlen ? &al : 0);
  if (addrlen)
    *addrlen = (unsigned int)al;
  return r;
}

/** PLATFORM: POSIX fallback — libc fcntl. */
static inline int xlang_net_fcntl(int fd, int cmd, long arg) {
  return fcntl(fd, cmd, arg);
}

#endif /* Platform branches */

#endif /* XLANG_NET_CAP_H */
