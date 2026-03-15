/**
 * std/http/http.c — 最小 HTTP 客户端（P4 可选；对标 Zig std.http、Rust reqwest 最小子集）
 *
 * 【文件职责】GET：解析 http://host[:port][/path]，getaddrinfo + socket + connect + send/recv，写回 out_buf。
 * 【所属模块/组件】标准库 std.http；与 std/http/mod.su 同属一模块。依赖 socket/getaddrinfo（Unix -lc；Windows ws2_32）。
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define SHU_HTTP_CLOSE(fd) closesocket((SOCKET)(fd))
#define SHU_HTTP_ERRNO WSAGetLastError()
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#define SHU_HTTP_CLOSE(fd) close(fd)
#define SHU_HTTP_ERRNO errno
#endif

/* 最大 host/path 长度，请求行+头约 2K 足够 */
#define SHU_HTTP_HOST_MAX  256
#define SHU_HTTP_PATH_MAX  2048
#define SHU_HTTP_REQ_MAX   (SHU_HTTP_PATH_MAX + SHU_HTTP_HOST_MAX + 64)

/** 解析 http://host[:port][/path]；返回 0 成功，-1 失败；写入 host_buf、port_buf、path_buf（均 NUL 结尾）。 */
static int parse_http_url(const uint8_t *url, int32_t url_len,
                         char *host_buf, int host_cap,
                         char *port_buf, int port_cap,
                         char *path_buf, int path_cap) {
  if (url_len < 8 || host_cap < 2 || port_cap < 6 || path_cap < 2) return -1;
  if (url[0] != 'h' || url[1] != 't' || url[2] != 't' || url[3] != 'p' || url[4] != ':' || url[5] != '/' || url[6] != '/')
    return -1;
  int32_t i = 7;
  /* host */
  int32_t host_start = i;
  while (i < url_len && url[i] != ':' && url[i] != '/') i++;
  int32_t host_len = i - host_start;
  if (host_len <= 0 || host_len >= host_cap) return -1;
  memcpy(host_buf, url + host_start, (size_t)host_len);
  host_buf[host_len] = '\0';
  /* port (optional) */
  uint16_t port_val = 80;
  if (i < url_len && url[i] == ':') {
    i++;
    int32_t port_start = i;
    while (i < url_len && url[i] != '/') i++;
    if (i > port_start && (i - port_start) < port_cap) {
      int n = 0;
      for (int32_t k = port_start; k < i && n < 10; k++) {
        if (url[k] >= '0' && url[k] <= '9') n = n * 10 + (url[k] - '0');
      }
      if (n > 0 && n <= 65535) port_val = (uint16_t)n;
      int plen = i - port_start;
      memcpy(port_buf, url + port_start, (size_t)plen);
      port_buf[plen] = '\0';
    } else
      port_buf[0] = '8'; port_buf[1] = '0'; port_buf[2] = '\0';
  } else {
    port_buf[0] = '8'; port_buf[1] = '0'; port_buf[2] = '\0';
  }
  /* path */
  if (i < url_len && url[i] == '/') {
    int32_t path_start = i;
    while (i < url_len) i++;
    int32_t path_len = i - path_start;
    if (path_len >= path_cap) return -1;
    memcpy(path_buf, url + path_start, (size_t)path_len);
    path_buf[path_len] = '\0';
  } else {
    path_buf[0] = '/'; path_buf[1] = '\0';
  }
  (void)port_val;
  return 0;
}

/** 最小 GET：url 为 http://host[:port][/path]，响应体+头写入 out_buf，返回写入字节数，失败 -1。 */
int32_t http_get_c(const uint8_t *url, int32_t url_len, uint8_t *out_buf, int32_t out_cap) {
  if (!url || !out_buf || url_len <= 0 || out_cap <= 0) return -1;

  char host_buf[SHU_HTTP_HOST_MAX];
  char port_buf[8];
  char path_buf[SHU_HTTP_PATH_MAX];
  if (parse_http_url(url, url_len, host_buf, SHU_HTTP_HOST_MAX, port_buf, sizeof(port_buf), path_buf, SHU_HTTP_PATH_MAX) != 0)
    return -1;

#if defined(_WIN32) || defined(_WIN64)
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
#endif

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  struct addrinfo *res = NULL;
  if (getaddrinfo(host_buf, port_buf, &hints, &res) != 0 || !res) {
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif
    return -1;
  }

#if defined(_WIN32) || defined(_WIN64)
  SOCKET fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (fd == INVALID_SOCKET) {
#else
  int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (fd < 0) {
#endif
    freeaddrinfo(res);
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif
    return -1;
  }
#if defined(_WIN32) || defined(_WIN64)
  if (connect(fd, res->ai_addr, (int)res->ai_addrlen) != 0) {
#else
  if (connect(fd, res->ai_addr, (int)res->ai_addrlen) != 0) {
#endif
    SHU_HTTP_CLOSE(fd);
    freeaddrinfo(res);
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif
    return -1;
  }
  freeaddrinfo(res);

  /* 构造 "GET path HTTP/1.0\r\nHost: host\r\n\r\n" */
  char req[SHU_HTTP_REQ_MAX];
  int req_len = 0;
  req_len += (int)snprintf(req + req_len, (size_t)(SHU_HTTP_REQ_MAX - req_len), "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", path_buf, host_buf);
  if (req_len <= 0 || req_len >= SHU_HTTP_REQ_MAX) {
    SHU_HTTP_CLOSE(fd);
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif
    return -1;
  }
  int sent = 0;
  while (sent < req_len) {
#if defined(_WIN32) || defined(_WIN64)
    int n = send(fd, req + sent, req_len - sent, 0);
#else
    ssize_t n = send(fd, req + sent, (size_t)(req_len - sent), 0);
#endif
    if (n <= 0) {
      SHU_HTTP_CLOSE(fd);
#if defined(_WIN32) || defined(_WIN64)
      WSACleanup();
#endif
      return -1;
    }
    sent += (int)n;
  }

  int32_t total = 0;
  while (total < out_cap) {
#if defined(_WIN32) || defined(_WIN64)
    int n = recv(fd, (char *)out_buf + total, (int)(out_cap - total), 0);
#else
    ssize_t n = recv(fd, out_buf + total, (size_t)(out_cap - total), 0);
#endif
    if (n <= 0) break;
    total += (int32_t)n;
  }
  SHU_HTTP_CLOSE(fd);
#if defined(_WIN32) || defined(_WIN64)
  WSACleanup();
#endif
  return total;
}
