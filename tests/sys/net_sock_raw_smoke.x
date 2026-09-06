/**
 * Stage9 Cap residual 9.1.7 slice0 probe: listen/close without libc socket
 * (std.net → net.o merge → net_sock_fast Cap xlang_net_cap.h).
 *
 * Contract: net_tcp_listen_c succeeds; net_close_socket_c succeeds.
 * PLATFORM: SHARED Cap (LINUX raw syscall, MACOS|DARWIN raw syscall, WINDOWS Winsock Cap).
 */
const net = import("std.net");

extern function net_tcp_listen_c(addr_u32: u32, port_u32: u32): i32;
extern function net_close_socket_c(fd: i32): i32;

/**
 * Probe entry for Cap residual 9.1.7 slice0 sock face.
 * @return i32 — 0 ok; 1 bad listen; 2 bad close
 */
export function main(): i32 {
  /* Host-order 127.0.0.1; set_addr_port applies htonl. */
  let addr: u32 = 0x7f000001;
  let fd: i32 = 0;
  let crc: i32 = 0;
  unsafe {
    fd = net_tcp_listen_c(addr, 39817);
  }
  if (fd < 0) {
    return 1;
  }
  unsafe {
    crc = net_close_socket_c(fd);
  }
  if (crc != 0) {
    return 2;
  }
  return 0;
}
