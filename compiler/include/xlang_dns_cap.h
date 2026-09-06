/*
 * xlang_dns_cap.h — Cap residual 9.1.7 slice2: resolve hostname → IPv4/IPv6
 * without libc getaddrinfo/freeaddrinfo on Linux and Darwin via pure Cap DNS,
 * and Windows via Winsock Cap.
 *
 * Strategy (minimal Cap DNS, G.7 single authority):
 *   1) literal IP parse
 *   2) localhost / ::1 shortcuts
 *   3) /etc/hosts scan (Cap open/read/close)
 *   4) UDP DNS A/AAAA to first nameserver in /etc/resolv.conf (fallback 127.0.0.53)
 *
 * Error codes match net_dns_map_gai_error_c: 1=NONAME 2=NODATA 3=AGAIN 4=system.
 * out_addr IPv4 is host-order u32 (same as prior ntohl(sin_addr) contract).
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock).
 */

#ifndef XLANG_DNS_CAP_H
#define XLANG_DNS_CAP_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <xlang_io_cap.h>
#include <xlang_net_cap.h>

#ifndef AF_INET
#define AF_INET 2
#endif

#ifndef AF_INET6
#if defined(__APPLE__)
#define AF_INET6 30
#elif defined(_WIN32) || defined(_WIN64)
#define AF_INET6 23
#else
#define AF_INET6 10
#endif
#endif

#ifndef SOCK_DGRAM
#define SOCK_DGRAM 2
#endif

#ifndef O_RDONLY
#define O_RDONLY 0
#endif

/* ============================================================================
 * PLATFORM: WINDOWS (Winsock Cap DNS)
 * ============================================================================ */
#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <ws2tcpip.h>

static inline int32_t xlang_dns_map_gai_error_win(int err) {
  if (err == WSANO_DATA || err == WSAHOST_NOT_FOUND)
    return 1;
  if (err == WSANO_RECOVERY)
    return 2;
  if (err == WSATRY_AGAIN)
    return 3;
  return 4;
}

/** Cap resolve IPv4 for Windows. PLATFORM: WINDOWS */
static inline int xlang_dns_resolve_ipv4(const char *host, uint32_t *out_addr, int32_t *out_err) {
  struct addrinfo hints;
  struct addrinfo *res = NULL;
  struct sockaddr_in *sa = NULL;
  int ga;
  uint32_t a = 0;

  if (xlang_net_ensure_wsa() != 0) {
    if (out_addr) *out_addr = 0;
    if (out_err) *out_err = 4;
    return -1;
  }
  if (!host || !out_addr) {
    if (out_addr) *out_addr = 0;
    if (out_err) *out_err = 4;
    return -1;
  }
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  ga = getaddrinfo(host, NULL, &hints, &res);
  if (ga != 0 || !res) {
    if (out_addr) *out_addr = 0;
    if (out_err) *out_err = xlang_dns_map_gai_error_win(ga);
    if (res) freeaddrinfo(res);
    return -1;
  }
  if (res->ai_family == AF_INET && res->ai_addr &&
      res->ai_addrlen >= (socklen_t)sizeof(struct sockaddr_in)) {
    sa = (struct sockaddr_in *)(void *)res->ai_addr;
    a = ntohl(sa->sin_addr.s_addr);
  }
  freeaddrinfo(res);
  if (a == 0) {
    if (out_addr) *out_addr = 0;
    if (out_err) *out_err = 2;
    return -1;
  }
  *out_addr = a;
  if (out_err) *out_err = 0;
  return 0;
}

/** Cap resolve IPv6 for Windows. PLATFORM: WINDOWS */
static inline int xlang_dns_resolve_ipv6(const char *host, uint8_t out16[16], int32_t *out_err) {
  struct addrinfo hints;
  struct addrinfo *res = NULL;
  struct sockaddr_in6 *sa6 = NULL;
  int ga;

  if (xlang_net_ensure_wsa() != 0) {
    if (out_err) *out_err = 4;
    return -1;
  }
  if (!host || !out16) {
    if (out_err) *out_err = 4;
    return -1;
  }
  memset(out16, 0, 16);
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  ga = getaddrinfo(host, NULL, &hints, &res);
  if (ga != 0 || !res) {
    if (out_err) *out_err = xlang_dns_map_gai_error_win(ga);
    if (res) freeaddrinfo(res);
    return -1;
  }
  if (res->ai_family != AF_INET6 || !res->ai_addr ||
      res->ai_addrlen < (socklen_t)sizeof(struct sockaddr_in6)) {
    if (out_err) *out_err = 2;
    freeaddrinfo(res);
    return -1;
  }
  sa6 = (struct sockaddr_in6 *)(void *)res->ai_addr;
  memcpy(out16, &sa6->sin6_addr, 16);
  freeaddrinfo(res);
  if (out_err) *out_err = 0;
  return 0;
}

/* ============================================================================
 * PLATFORM: LINUX & MACOS|DARWIN (Pure Cap DNS without libc)
 * ============================================================================ */
#elif (defined(__linux__) || defined(__APPLE__)) && (defined(__x86_64__) || defined(__aarch64__))

/** Cap open(2) for /etc/hosts|resolv.conf. PLATFORM: LINUX|DARWIN */
static inline int xlang_dns_open_ro(const char *path) {
  if (!path)
    return -1;
#if defined(__linux__)
#if defined(__x86_64__)
  long r = xlang_net_syscall3(2, (long)path, (long)O_RDONLY, 0); /* open */
#elif defined(__aarch64__)
  long r = xlang_net_syscall3(56, (long)(-100) /* AT_FDCWD */, (long)path, (long)O_RDONLY); /* openat */
#endif
  if (r < 0)
    return -1;
  return (int)r;
#elif defined(__APPLE__)
#if defined(__aarch64__)
  register long x16 __asm__("x16") = 5; /* SYS_open */
  register long x0 __asm__("x0") = (long)path;
  register long x1 __asm__("x1") = 0;   /* O_RDONLY */
  register long x2 __asm__("x2") = 0;
  register long failed __asm__("x9");
  __asm__ __volatile__(
      "svc #0x80\n\t"
      "cset %3, cs"
      : "+r"(x0), "+r"(x1), "+r"(x2), "=r"(failed)
      : "r"(x16)
      : "memory", "cc"
  );
  return failed ? -1 : (int)x0;
#elif defined(__x86_64__)
  long ret;
  __asm__ __volatile__(
      "syscall\n\t"
      "jnc 1f\n\t"
      "movq $-1, %%rax\n\t"
      "1:"
      : "=a"(ret)
      : "0"(0x2000005L), "D"(path), "S"(0), "d"(0)
      : "rcx", "r11", "memory", "cc"
  );
  return (int)ret;
#endif
#endif
}

static inline uint16_t xlang_dns_htons(uint16_t v) {
  return (uint16_t)((v << 8) | (v >> 8));
}

static inline uint32_t xlang_dns_htonl(uint32_t v) {
  return ((v & 0xffu) << 24) | ((v & 0xff00u) << 8) | ((v & 0xff0000u) >> 8) |
         ((v & 0xff000000u) >> 24);
}

static inline int xlang_dns_ci_eq(const char *a, const char *b) {
  unsigned char ca, cb;
  if (!a || !b)
    return 0;
  while (*a && *b) {
    ca = (unsigned char)*a;
    cb = (unsigned char)*b;
    if (ca >= 'A' && ca <= 'Z')
      ca = (unsigned char)(ca - 'A' + 'a');
    if (cb >= 'A' && cb <= 'Z')
      cb = (unsigned char)(cb - 'A' + 'a');
    if (ca != cb)
      return 0;
    a++;
    b++;
  }
  return *a == 0 && *b == 0;
}

/** Parse dotted IPv4 → host-order u32. Returns 0 ok. PLATFORM: SHARED Cap */
static inline int xlang_dns_parse_ipv4(const char *s, uint32_t *out_host) {
  unsigned int o[4];
  int i, n, v;
  const char *p;
  if (!s || !out_host)
    return -1;
  p = s;
  for (i = 0; i < 4; i++) {
    if (*p < '0' || *p > '9')
      return -1;
    v = 0;
    n = 0;
    while (*p >= '0' && *p <= '9') {
      v = v * 10 + (*p - '0');
      if (v > 255)
        return -1;
      p++;
      n++;
      if (n > 3)
        return -1;
    }
    o[i] = (unsigned int)v;
    if (i < 3) {
      if (*p != '.')
        return -1;
      p++;
    }
  }
  if (*p != 0)
    return -1;
  *out_host = (o[0] << 24) | (o[1] << 16) | (o[2] << 8) | o[3];
  return 0;
}

static inline int xlang_dns_hex_val(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  return -1;
}

/** Parse full 8-hextet or simple ::1 IPv6. Returns 0 ok. PLATFORM: SHARED Cap */
static inline int xlang_dns_parse_ipv6_simple(const char *s, uint8_t out[16]) {
  uint16_t h[8];
  int i, v, d, hv;
  const char *p = s;
  if (!s || !out)
    return -1;
  if (strcmp(s, "::1") == 0) {
    memset(out, 0, 16);
    out[15] = 1;
    return 0;
  }
  if (strcmp(s, "::") == 0) {
    memset(out, 0, 16);
    return 0;
  }
  for (i = 0; i < 8; i++) {
    v = 0;
    d = 0;
    while (*p) {
      hv = xlang_dns_hex_val(*p);
      if (hv < 0)
        break;
      v = (v << 4) | hv;
      if (v > 0xffff)
        return -1;
      p++;
      d++;
      if (d > 4)
        return -1;
    }
    if (d == 0)
      return -1;
    h[i] = (uint16_t)v;
    if (i < 7) {
      if (*p != ':')
        return -1;
      p++;
    }
  }
  if (*p != 0)
    return -1;
  for (i = 0; i < 8; i++) {
    out[i * 2] = (uint8_t)(h[i] >> 8);
    out[i * 2 + 1] = (uint8_t)(h[i] & 0xff);
  }
  return 0;
}

/** Read whole small file into buf (Cap). Returns bytes or -1. */
static inline long xlang_dns_read_file(const char *path, char *buf, size_t cap) {
  int fd;
  long n, off;
  if (!path || !buf || cap < 2)
    return -1;
  fd = xlang_dns_open_ro(path);
  if (fd < 0)
    return -1;
  off = 0;
  while ((size_t)off + 1 < cap) {
    n = xlang_io_read(fd, buf + off, cap - 1 - (size_t)off);
    if (n < 0) {
      xlang_net_close(fd);
      return -1;
    }
    if (n == 0)
      break;
    off += n;
  }
  xlang_net_close(fd);
  buf[off] = 0;
  return off;
}

/**
 * Scan /etc/hosts for hostname. family 4 → out_v4 host-order; family 6 → out16.
 * Returns 0 hit, -1 miss. PLATFORM: SHARED Cap
 */
static inline int xlang_dns_hosts_lookup(const char *host, int family, uint32_t *out_v4,
                                        uint8_t out16[16]) {
  char file[8192];
  char *line, *next, *tok, *save;
  long n;
  if (!host)
    return -1;
  n = xlang_dns_read_file("/etc/hosts", file, sizeof(file));
  if (n <= 0)
    return -1;
  line = file;
  while (line && *line) {
    next = strchr(line, '\n');
    if (next) {
      *next = 0;
      next++;
    }
    while (*line == ' ' || *line == '\t')
      line++;
    if (*line && *line != '#') {
      tok = line;
      while (*tok && *tok != ' ' && *tok != '\t')
        tok++;
      if (*tok) {
        *tok = 0;
        tok++;
        while (*tok == ' ' || *tok == '\t')
          tok++;
        save = tok;
        while (*save) {
          char *end = save;
          while (*end && *end != ' ' && *end != '\t')
            end++;
          if (*end) {
            *end = 0;
            end++;
          }
          if (xlang_dns_ci_eq(save, host)) {
            if (family == 4 && out_v4) {
              if (xlang_dns_parse_ipv4(line, out_v4) == 0)
                return 0;
            }
            if (family == 6 && out16) {
              if (xlang_dns_parse_ipv6_simple(line, out16) == 0)
                return 0;
            }
          }
          save = end;
          while (*save == ' ' || *save == '\t')
            save++;
        }
      }
    }
    line = next;
  }
  return -1;
}

/** First nameserver IPv4 from /etc/resolv.conf; default 127.0.0.53. host-order. */
static inline uint32_t xlang_dns_first_nameserver(void) {
  char file[4096];
  char *line, *next;
  uint32_t a = 0;
  long n = xlang_dns_read_file("/etc/resolv.conf", file, sizeof(file));
  if (n > 0) {
    line = file;
    while (line && *line) {
      next = strchr(line, '\n');
      if (next) {
        *next = 0;
        next++;
      }
      while (*line == ' ' || *line == '\t')
        line++;
      if (strncmp(line, "nameserver", 10) == 0) {
        line += 10;
        while (*line == ' ' || *line == '\t')
          line++;
        if (xlang_dns_parse_ipv4(line, &a) == 0)
          return a;
      }
      line = next;
    }
  }
  /* Fallback: systemd-resolved stub or public DNS */
  return (127u << 24) | 53u;
}

/** Encode DNS QNAME into dst; returns bytes written or -1. */
static inline int xlang_dns_enc_name(uint8_t *dst, int cap, const char *host) {
  int off = 0;
  const char *p = host;
  if (!dst || !host || cap < 2)
    return -1;
  while (*p) {
    const char *dot = p;
    int lab;
    while (*dot && *dot != '.')
      dot++;
    lab = (int)(dot - p);
    if (lab <= 0 || lab > 63 || off + 1 + lab >= cap)
      return -1;
    dst[off++] = (uint8_t)lab;
    memcpy(dst + off, p, (size_t)lab);
    off += lab;
    if (*dot == '.')
      p = dot + 1;
    else
      p = dot;
  }
  if (off + 1 >= cap)
    return -1;
  dst[off++] = 0;
  return off;
}

/**
 * UDP DNS query for A (qtype=1) or AAAA (qtype=28).
 * On A success writes host-order u32; on AAAA writes 16 bytes.
 * Returns 0 ok; sets *out_err on fail. PLATFORM: SHARED Cap
 */
static inline int xlang_dns_udp_query(const char *host, int qtype, uint32_t *out_v4, uint8_t out16[16],
                                     int32_t *out_err) {
  uint8_t pkt[512];
  uint8_t resp[512];
  uint8_t sin[16];
  uint16_t id = 0xC0DEu;
  int nlen, qlen, fd, i;
  long nr;
  uint32_t ns;
  unsigned int alen;
  struct {
    int fd;
    short events;
    short revents;
  } pfd;

  if (!host) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  memset(pkt, 0, sizeof(pkt));
  pkt[0] = (uint8_t)(id >> 8);
  pkt[1] = (uint8_t)(id & 0xff);
  pkt[2] = 0x01; /* RD */
  pkt[5] = 1;    /* QDCOUNT=1 */
  nlen = xlang_dns_enc_name(pkt + 12, (int)sizeof(pkt) - 16, host);
  if (nlen < 0) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  qlen = 12 + nlen;
  pkt[qlen++] = 0;
  pkt[qlen++] = (uint8_t)qtype;
  pkt[qlen++] = 0;
  pkt[qlen++] = 1; /* IN */

  ns = xlang_dns_first_nameserver();
  memset(sin, 0, sizeof(sin));
#if defined(__APPLE__)
  sin[0] = 16;
  sin[1] = (uint8_t)AF_INET;
#else
  sin[0] = (uint8_t)AF_INET;
  sin[1] = 0;
#endif
  /* port 53 BE at offset 2 */
  sin[2] = 0;
  sin[3] = 53;
  {
    uint32_t be = xlang_dns_htonl(ns);
    memcpy(sin + 4, &be, 4);
  }

  fd = xlang_net_socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  if (xlang_net_sendto(fd, pkt, (size_t)qlen, 0, sin, 16) < 0) {
    xlang_net_close(fd);
    if (out_err)
      *out_err = 3;
    return -1;
  }
  pfd.fd = fd;
  pfd.events = 1; /* POLLIN */
  pfd.revents = 0;
  if (xlang_net_poll(&pfd, 1, 2000) <= 0) {
    xlang_net_close(fd);
    if (out_err)
      *out_err = 3;
    return -1;
  }
  alen = 16;
  nr = xlang_net_recvfrom(fd, resp, sizeof(resp), 0, sin, &alen);
  xlang_net_close(fd);
  if (nr < 12) {
    if (out_err)
      *out_err = 3;
    return -1;
  }
  /* RCODE */
  if ((resp[3] & 0x0f) == 3) {
    if (out_err)
      *out_err = 1;
    return -1;
  }
  if ((resp[3] & 0x0f) != 0) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  {
    int qd = (resp[4] << 8) | resp[5];
    int an = (resp[6] << 8) | resp[7];
    int off = 12;
    /* skip questions */
    for (i = 0; i < qd && off < (int)nr; i++) {
      while (off < (int)nr) {
        uint8_t lab = resp[off];
        if (lab == 0) {
          off++;
          break;
        }
        if ((lab & 0xc0) == 0xc0) {
          off += 2;
          break;
        }
        off += 1 + lab;
      }
      off += 4; /* QTYPE + QCLASS */
    }
    /* parse answers */
    for (i = 0; i < an && off < (int)nr; i++) {
      int rtype, rdlen;
      /* name */
      while (off < (int)nr) {
        uint8_t lab = resp[off];
        if (lab == 0) {
          off++;
          break;
        }
        if ((lab & 0xc0) == 0xc0) {
          off += 2;
          break;
        }
        off += 1 + lab;
      }
      if (off + 10 > (int)nr)
        break;
      rtype = (resp[off] << 8) | resp[off + 1];
      rdlen = (resp[off + 8] << 8) | resp[off + 9];
      off += 10;
      if (off + rdlen > (int)nr)
        break;
      if (rtype == 1 && qtype == 1 && rdlen == 4 && out_v4) {
        *out_v4 = ((uint32_t)resp[off] << 24) | ((uint32_t)resp[off + 1] << 16) |
                  ((uint32_t)resp[off + 2] << 8) | (uint32_t)resp[off + 3];
        if (out_err)
          *out_err = 0;
        return 0;
      }
      if (rtype == 28 && qtype == 28 && rdlen == 16 && out16) {
        memcpy(out16, resp + off, 16);
        if (out_err)
          *out_err = 0;
        return 0;
      }
      off += rdlen;
    }
  }
  if (out_err)
    *out_err = 2; /* NODATA */
  return -1;
}

/**
 * Cap residual resolve IPv4 (host-order u32 out).
 * PLATFORM: SHARED Cap
 */
static inline int xlang_dns_resolve_ipv4(const char *host, uint32_t *out_addr, int32_t *out_err) {
  uint32_t a = 0;
  if (!host || !out_addr) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  *out_addr = 0;
  if (xlang_dns_parse_ipv4(host, &a) == 0) {
    *out_addr = a;
    if (out_err)
      *out_err = 0;
    return 0;
  }
  if (xlang_dns_ci_eq(host, "localhost")) {
    *out_addr = (127u << 24) | 1u;
    if (out_err)
      *out_err = 0;
    return 0;
  }
  if (xlang_dns_hosts_lookup(host, 4, &a, 0) == 0) {
    *out_addr = a;
    if (out_err)
      *out_err = 0;
    return 0;
  }
  return xlang_dns_udp_query(host, 1, out_addr, 0, out_err);
}

/**
 * Cap residual resolve IPv6 (16-byte network order out).
 * PLATFORM: SHARED Cap
 */
static inline int xlang_dns_resolve_ipv6(const char *host, uint8_t out16[16], int32_t *out_err) {
  uint8_t tmp[16];
  if (!host || !out16) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  memset(out16, 0, 16);
  if (xlang_dns_ci_eq(host, "localhost") || xlang_dns_ci_eq(host, "ip6-localhost")) {
    out16[15] = 1;
    if (out_err)
      *out_err = 0;
    return 0;
  }
  if (xlang_dns_parse_ipv6_simple(host, tmp) == 0) {
    memcpy(out16, tmp, 16);
    if (out_err)
      *out_err = 0;
    return 0;
  }
  if (xlang_dns_hosts_lookup(host, 6, 0, tmp) == 0) {
    memcpy(out16, tmp, 16);
    if (out_err)
      *out_err = 0;
    return 0;
  }
  return xlang_dns_udp_query(host, 28, 0, out16, out_err);
}

/* ============================================================================
 * PLATFORM: Generic POSIX fallback
 * ============================================================================ */
#else

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

/** PLATFORM: POSIX fallback — libc getaddrinfo IPv4. */
static inline int xlang_dns_resolve_ipv4(const char *host, uint32_t *out_addr, int32_t *out_err) {
  struct addrinfo hints;
  struct addrinfo *res = 0;
  int ga;
  uint32_t a = 0;
  if (!host || !out_addr) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  ga = getaddrinfo(host, 0, &hints, &res);
  if (ga != 0 || !res) {
    if (out_err)
      *out_err = (ga == EAI_NONAME) ? 1 : (ga == EAI_AGAIN) ? 3 : 4;
    if (res)
      freeaddrinfo(res);
    return -1;
  }
  if (res->ai_family == AF_INET && res->ai_addr)
    a = ntohl(((struct sockaddr_in *)(void *)res->ai_addr)->sin_addr.s_addr);
  freeaddrinfo(res);
  if (a == 0) {
    if (out_err)
      *out_err = 2;
    return -1;
  }
  *out_addr = a;
  if (out_err)
    *out_err = 0;
  return 0;
}

/** PLATFORM: POSIX fallback — libc getaddrinfo IPv6. */
static inline int xlang_dns_resolve_ipv6(const char *host, uint8_t out16[16], int32_t *out_err) {
  struct addrinfo hints;
  struct addrinfo *res = 0;
  int ga;
  if (!host || !out16) {
    if (out_err)
      *out_err = 4;
    return -1;
  }
  memset(out16, 0, 16);
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  ga = getaddrinfo(host, 0, &hints, &res);
  if (ga != 0 || !res) {
    if (out_err)
      *out_err = (ga == EAI_NONAME) ? 1 : (ga == EAI_AGAIN) ? 3 : 4;
    if (res)
      freeaddrinfo(res);
    return -1;
  }
  if (res->ai_family != AF_INET6 || !res->ai_addr) {
    freeaddrinfo(res);
    if (out_err)
      *out_err = 2;
    return -1;
  }
  memcpy(out16, &((struct sockaddr_in6 *)(void *)res->ai_addr)->sin6_addr, 16);
  freeaddrinfo(res);
  if (out_err)
    *out_err = 0;
  return 0;
}

#endif /* Platform branches */

#endif /* XLANG_DNS_CAP_H */
