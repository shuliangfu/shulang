/* seeds/runtime_net_dns_fast.from_x.c — G-02f-20 product TU
 * G-02f-103 helper gates.
 * Product: ../std/net/net_dns_fast.o; logic still C until full .x port.
 * Cap residual 9.1.7 slice2: resolve via xlang_dns_cap.h (no libc getaddrinfo).
 *
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock Cap).
 */
#include <stdint.h>
#include <string.h>
#include <xlang_dns_cap.h>

int32_t net_resolve_ipv4_ex_c(uint8_t *hostname, uint32_t *out_addr, int32_t *out_err);
int32_t net_resolve_ipv6_ex_c(uint8_t *hostname, uint8_t *out_addr_16, int32_t *out_err);

int32_t net_dns_ai_addconfig_c_impl_c(void) {
#if defined(__linux__)
    return 32;
#else
    return 1024;
#endif
}

#ifndef XLANG_RUNTIME_NET_DNS_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_dns_ai_addconfig_c(void) {
    return net_dns_ai_addconfig_c_impl_c();
}
#endif

int32_t net_dns_map_gai_error_c_impl_c(int err) {
    if (err == 1)
        return 1;
    if (err == 2)
        return 2;
    if (err == 3)
        return 3;
    return 4;
}

#ifndef XLANG_RUNTIME_NET_DNS_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_dns_map_gai_error_c(int err) {
    return net_dns_map_gai_error_c_impl_c(err);
}
#endif

int32_t net_dns_ensure_wsa_c_impl_c(void) {
    return xlang_net_ensure_wsa();
}

#ifndef XLANG_RUNTIME_NET_DNS_FAST_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t net_dns_ensure_wsa_c(void) {
    return net_dns_ensure_wsa_c_impl_c();
}
#endif

uint32_t net_resolve_ipv4_c(uint8_t *hostname) {
    uint32_t addr = 0;
    int32_t err = 0;
    if (net_resolve_ipv4_ex_c(hostname, &addr, &err) != 0)
        return 0;
    return addr;
}

/**
 * Cap residual 9.1.7 slice2: IPv4 resolve via xlang_dns_cap.h.
 * Exported for dns.x / http_glue. PLATFORM: SHARED Cap.
 */
int32_t xlang_dns_cap_resolve_ipv4(uint8_t *hostname, uint32_t *out_addr, int32_t *out_err) {
    return (int32_t)xlang_dns_resolve_ipv4((const char *)hostname, out_addr, out_err);
}

/**
 * Cap residual 9.1.7 slice2: IPv6 resolve via xlang_dns_cap.h.
 * Exported for dns.x / http_glue. PLATFORM: SHARED Cap.
 */
int32_t xlang_dns_cap_resolve_ipv6(uint8_t *hostname, uint8_t *out_addr_16, int32_t *out_err) {
    return (int32_t)xlang_dns_resolve_ipv6((const char *)hostname, out_addr_16, out_err);
}

int32_t net_resolve_ipv4_ex_c(uint8_t *hostname, uint32_t *out_addr, int32_t *out_err) {
    return xlang_dns_cap_resolve_ipv4(hostname, out_addr, out_err);
}

int32_t net_resolve_ipv6_ex_c(uint8_t *hostname, uint8_t *out_addr_16, int32_t *out_err) {
    return xlang_dns_cap_resolve_ipv6(hostname, out_addr_16, out_err);
}
