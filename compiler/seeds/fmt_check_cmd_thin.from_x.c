/* regen from fmt_check_cmd_thin.x -E (path_bss pure rest T=0 + xlang_fmt_* wrappers) */
/* prove prologue (g05_try_x_to_o aligned + uio/poll + dirent wrappers) */
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <xlang_io_cap.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/uio.h>
#include <poll.h>
#include <dirent.h>
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "Generated code needs C11. Compile with -std=gnu11 or -std=c11."
#endif
/* wave234 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — cold/surface twin of fmt_check_cmd_thin.x. */
extern uint8_t * link_abi_getenv(uint8_t * name);
static inline ssize_t xlang_sys_read(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_read((int)fd, (void *)buf, count);
}
static inline ssize_t xlang_sys_write(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_write((int)fd, (const void *)buf, count);
}
static inline ssize_t xlang_sys_readv(int32_t fd, uint8_t *iov, int32_t iovcnt) {
  return readv((int)fd, (const struct iovec *)(const void *)iov, (int)iovcnt);
}
static inline ssize_t xlang_sys_writev(int32_t fd, uint8_t *iov, int32_t iovcnt) {
  return writev((int)fd, (const struct iovec *)(const void *)iov, (int)iovcnt);
}
static inline int32_t xlang_sys_poll(uint8_t *fds, int32_t nfds, int32_t timeout) {
  return (int32_t)poll((struct pollfd *)(void *)fds, (nfds_t)nfds, (int)timeout);
}
static inline ssize_t xlang_sys_pread(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {
  return pread((int)fd, (void *)buf, count, (off_t)offset);
}
static inline ssize_t xlang_sys_pwrite(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {
  return pwrite((int)fd, (const void *)buf, count, (off_t)offset);
}
static inline int32_t xlang_fs_unlink(uint8_t *path) {
  return (int32_t)unlink((const char *)path);
}
static inline int32_t xlang_fs_rmdir(uint8_t *path) {
  return (int32_t)rmdir((const char *)path);
}
struct xlang_slice_uint8_t { uint8_t *data; size_t length; };
struct xlang_slice_int32_t { int32_t *data; size_t length; };
struct xlang_slice_uint64_t { uint64_t *data; size_t length; };
struct xlang_slice_size_t { size_t *data; size_t length; };
#if defined(__GNUC__) || defined(__clang__)
typedef int32_t i32x4_t __attribute__((vector_size(16)));
typedef int32_t i32x8_t __attribute__((vector_size(32)));
typedef int32_t i32x16_t __attribute__((vector_size(64)));
typedef uint32_t u32x4_t __attribute__((vector_size(16)));
typedef uint32_t u32x8_t __attribute__((vector_size(32)));
typedef uint32_t u32x16_t __attribute__((vector_size(64)));
#else
typedef struct { int32_t e[4]; } i32x4_t;
typedef struct { int32_t e[8]; } i32x8_t;
typedef struct { int32_t e[16]; } i32x16_t;
typedef struct { uint32_t e[4]; } u32x4_t;
typedef struct { uint32_t e[8]; } u32x8_t;
typedef struct { uint32_t e[16]; } u32x16_t;
#endif
typedef struct { uint8_t *ptr; size_t length; size_t handle; } xlang_batch_buf_t;
extern int io_register_buffer(uint8_t *ptr, size_t len);
extern int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr);
/* wave315 G.7: monofile dual WEAK polyfills → extern-only (runtime mega host-cc leave).
 * live STRONG = runtime/product .o (freestanding dual leave).
 * PLATFORM: SHARED freestanding dual leave. */
extern int io_register_buffers_buf_c(const xlang_batch_buf_t *bufs, int nr);

static inline int io_register_buffers_buf_i32(intptr_t bufs, int nr) { return io_register_buffers_buf_c((const xlang_batch_buf_t *)(uintptr_t)bufs, nr); }
#define io_register_buffers_buf(bufs, nr) io_register_buffers_buf_i32((intptr_t)(void *)(bufs), (nr))
extern void io_unregister_buffers(void);
extern ptrdiff_t io_read(int fd, uint8_t *buf, size_t count, unsigned timeout_ms);
extern ptrdiff_t io_write(int fd, uint8_t *buf, size_t count, unsigned timeout_ms);
extern ptrdiff_t io_read_batch(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, int n, unsigned timeout_ms);
extern ptrdiff_t io_write_batch(int fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, int n, unsigned timeout_ms);
extern ptrdiff_t io_read_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms);
extern ptrdiff_t io_write_fixed(int fd, unsigned buf_index, size_t offset, size_t len, unsigned timeout_ms);
extern int io_wait_readable(int32_t *fds, int n, unsigned timeout_ms);
extern uint8_t *io_read_ptr(size_t handle, unsigned timeout_ms);
extern int io_read_ptr_len(void);
extern int32_t xlang_io_register(uint8_t *ptr, size_t len, size_t handle);
extern int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
extern int32_t xlang_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
extern int32_t xlang_io_read_fixed(size_t handle, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_m);
extern int32_t xlang_io_write_fixed(size_t handle, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_m);
extern uint8_t *xlang_io_read_ptr(size_t handle, unsigned timeout_ms);
extern int32_t xlang_io_read_ptr_len(void);
typedef struct { void *ptr; size_t length; size_t handle; } xlang_buffer_abi_t;
static inline int32_t xlang_io_register_buf(intptr_t buf) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return xlang_io_register((uint8_t *)b->ptr, b->length, b->handle); }
static inline int32_t xlang_io_submit_read_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return (xlang_io_submit_read)((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }
static inline int32_t xlang_io_submit_write_buf(intptr_t buf, int32_t timeout_m) { const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf; return (xlang_io_submit_write)((uint8_t *)b->ptr, b->length, b->handle, (uint32_t)timeout_m); }
static inline int32_t std_io_driver_submit_read_via_ptr(ptrdiff_t buf, uint32_t timeout_ms) { return xlang_io_submit_read_buf((intptr_t)buf, (int32_t)timeout_ms); }
static inline int32_t std_io_driver_submit_write_via_ptr(ptrdiff_t buf, uint32_t timeout_ms) { return xlang_io_submit_write_buf((intptr_t)buf, (int32_t)timeout_ms); }
#define xlang_io_register(buf) xlang_io_register_buf(buf)
#define xlang_io_submit_read(buf, timeout_m) xlang_io_submit_read_buf(buf, timeout_m)
#define xlang_io_submit_write(buf, timeout_m) xlang_io_submit_write_buf(buf, timeout_m)
/* 撤销宏：X codegen 会生成同名函数定义(xlang_io_register/submit_read/submit_write)，宏与多参签名冲突，在函数体前必须 undef。 */
#undef xlang_io_register
#undef xlang_io_submit_read
#undef xlang_io_submit_write
struct std_io_driver_Buffer { void *ptr; size_t length; size_t handle; };
typedef struct std_io_driver_Buffer std_io_Buffer;
#define std_io_Buffer std_io_driver_Buffer
extern ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);
extern ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);
extern int32_t std_io_driver_submit_register_fixed_buffers_buf(struct std_io_driver_Buffer * bufs, uint32_t nr);
#define std_io_driver_driver_read_ptr_len xlang_io_read_ptr_len
#define std_io_driver_driver_read_ptr xlang_io_read_ptr
#define driver_read_ptr_len std_io_driver_driver_read_ptr_len
#define driver_read_ptr std_io_driver_driver_read_ptr
#define submit_register_fixed_buffers_buf std_io_driver_submit_register_fixed_buffers_buf
/* 短名 submit_read/write → via_ptr；全名 std_io_driver_submit_* 由 co-emit 定义。 */
#define submit_read(buf, timeout_ms) std_io_driver_submit_read_via_ptr((ptrdiff_t)(uintptr_t)&(buf), (timeout_ms))
#define submit_write(buf, timeout_ms) std_io_driver_submit_write_via_ptr((ptrdiff_t)(uintptr_t)&(buf), (timeout_ms))
#define std_io_driver_read_ptr driver_read_ptr
#define std_io_driver_read_ptr_len driver_read_ptr_len
extern size_t std_io_handle_stdin(void);
extern size_t std_io_handle_stdout(void);
extern size_t std_io_handle_stderr(void);
extern size_t std_io_handle_from_fd(int32_t fd, int32_t unused);
extern size_t std_io_driver_handle_from_fd(int32_t fd, int32_t unused);
extern int32_t std_io_write_stdout(uint8_t *ptr, size_t len);
#define std_io_driver_handle_stdin std_io_handle_stdin
#define std_io_driver_handle_stdout std_io_handle_stdout
#define std_io_driver_handle_stderr std_io_handle_stderr
#define std_io_driver_write_stdout std_io_write_stdout
/* std.io.core 体内调 extern io_*；codegen 前缀为 std_io_core_io_*，映射到 preamble 已声明的 io_*。 */
#define std_io_core_io_read io_read
#define std_io_core_io_write io_write
#define std_io_core_io_read_batch io_read_batch
#define std_io_core_io_write_batch io_write_batch
#define std_io_core_io_read_fixed io_read_fixed
#define std_io_core_io_write_fixed io_write_fixed
#define std_io_core_xlang_io_register xlang_io_register
#define std_io_core_xlang_io_register_buffers xlang_io_register_buffers
#define std_io_core_xlang_io_unregister_buffers xlang_io_unregister_buffers
#define std_io_core_xlang_io_submit_read xlang_io_submit_read
#define std_io_core_xlang_io_read_ptr xlang_io_read_ptr
#define std_io_core_xlang_io_read_ptr_len xlang_io_read_ptr_len
#define std_io_core_xlang_io_submit_write xlang_io_submit_write
#define std_io_core_xlang_io_submit_read_batch xlang_io_submit_read_batch
#define std_io_core_xlang_io_submit_write_batch xlang_io_submit_write_batch
#define std_io_core_xlang_io_read_fixed xlang_io_read_fixed
#define std_io_core_xlang_io_write_fixed xlang_io_write_fixed
#define std_io_core_xlang_io_register_buffers_buf io_register_buffers_buf
#define std_io_core_xlang_io_read_ptr_gen xlang_io_read_ptr_gen
#define std_io_core_xlang_io_read_ptr_gen_valid xlang_io_read_ptr_gen_valid
#define std_io_core_xlang_io_read_ptr_backend xlang_io_read_ptr_backend
#define std_io_core_xlang_io_read_ptr_slice xlang_io_read_ptr_slice
#define std_io_core_xlang_io_read_batch_buf(fd, bufs, n, t) io_read_batch_buf((fd), (const struct std_io_driver_Buffer *)(const void *)(bufs), (n), (t))
#define std_io_core_xlang_io_write_batch_buf(fd, bufs, n, t) io_write_batch_buf((fd), (const struct std_io_driver_Buffer *)(const void *)(bufs), (n), (t))
#define std_io_core_xlang_io_register_provided_buffers xlang_io_register_provided_buffers
#define std_io_core_xlang_io_provided_buffer_size xlang_io_provided_buffer_size
#define std_io_core_xlang_io_read_provided xlang_io_read_provided
#define std_io_core_xlang_io_read_batch_provided xlang_io_read_batch_provided
#define std_io_core_xlang_io_submit_read_async xlang_io_submit_read_async
#define std_io_core_xlang_io_complete_read_async xlang_io_complete_read_async
#define std_io_core_xlang_io_complete_read_async_slot xlang_io_complete_read_async_slot
#define std_io_core_xlang_io_submit_write_async xlang_io_submit_write_async
#define std_io_core_xlang_io_complete_write_async xlang_io_complete_write_async
#define std_io_core_xlang_io_complete_write_async_slot xlang_io_complete_write_async_slot
#define std_io_core_xlang_io_poll_async_completions xlang_io_poll_async_completions
#define std_io_core_xlang_io_uring_is_available_c xlang_io_uring_is_available_c
extern int32_t xlang_io_read_ptr_gen_valid(uint64_t saved);
extern int32_t xlang_io_read_ptr_backend(void);
extern uint64_t xlang_io_read_ptr_gen(void);
extern struct xlang_slice_uint8_t xlang_io_read_ptr_slice(size_t handle, uint32_t timeout_ms);
extern int32_t xlang_io_register_provided_buffers(uint32_t nr, uint32_t bufsz);
extern uint32_t xlang_io_provided_buffer_size(void);
extern int32_t xlang_io_read_provided(size_t handle, uint32_t timeout_ms, uint32_t *out_bid, uint32_t *out_len);
extern int32_t xlang_io_read_batch_provided(size_t handle, int32_t n, uint32_t timeout_ms, uint32_t *out_bids, uint32_t *out_lens);
extern int32_t xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle);
extern int32_t xlang_io_complete_read_async(void);
extern int32_t xlang_io_complete_read_async_slot(int32_t slot);
extern int32_t xlang_io_submit_write_async(uint8_t *ptr, size_t len, size_t handle);
extern int32_t xlang_io_complete_write_async(void);
extern int32_t xlang_io_complete_write_async_slot(int32_t slot);
extern uint32_t xlang_io_poll_async_completions(uint32_t timeout_ms);
extern int32_t xlang_io_uring_is_available_c(void);
#define std_io_driver_io_register_buffers_buf(bufs, nr) io_register_buffers_buf((intptr_t)(void *)(bufs), (int)(nr))
extern int32_t std_io_driver_submit_read_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);
extern int32_t std_io_driver_submit_write_batch_buf(size_t handle, struct std_io_driver_Buffer * bufs, int32_t n, uint32_t timeout_ms);
#define std_io_submit_read_batch_buf std_io_driver_submit_read_batch_buf
#define std_io_submit_write_batch_buf std_io_driver_submit_write_batch_buf
extern int32_t std_io_read_fixed_fd_impl(int32_t fd, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_ms);
extern int32_t std_io_write_fixed_fd_impl(int32_t fd, uint32_t buf_index, size_t offset, size_t len, uint32_t timeout_ms);
/* X 生成代码可能调用 std_io_* / std_net_* 带前缀名且首参为 stream/listener 结构体；以下宏统一转为 .fd 再调 _impl。C 路径下 std.io 仍定义 std_io_read_fixed_fd，故仅 X 需宏。 */
struct std_net_TcpStream { int32_t fd; };
struct std_net_TcpListener { int32_t fd; };
struct std_net_UdpSocket { int32_t fd; };
#if defined(__clang__)
#define xlang_io_net_fd(x) _Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (int32_t)(x))
#elif defined(__GNUC__)
/* 仅用 *(int32_t*)&(x)：int32_t 与仅含 .fd 的 struct 首字节相同，且避免 __builtin_types_compatible_p 在部分环境报错、三元分支被全量类型检查。调用方须传 lvalue。 */
#define xlang_io_net_fd(x) (*(int32_t*)(void*)&(x))
#else
#define xlang_io_net_fd(x) _Generic((x), struct std_net_TcpStream: (x).fd, struct std_net_TcpListener: (x).fd, struct std_net_UdpSocket: (x).fd, default: (int32_t)(x))
#endif
#define std_io_read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)
#define std_io_write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)
/* X 内联 std.io 会生成函数定义；撤销与定义/extern 冲突的宏，并补齐 batch 注册符号映射。 */
#undef std_io_driver_io_register_buffers_buf
#undef std_io_read_fixed_fd
#undef std_io_write_fixed_fd
#undef std_io_core_xlang_io_register_buffers
#undef std_io_core_xlang_io_unregister_buffers
#undef std_io_core_xlang_io_read_fixed
#undef std_io_core_xlang_io_write_fixed
#undef std_io_core_xlang_io_wait_readable
#define std_io_core_xlang_io_register_buffers io_register_buffers_4
#define std_io_core_xlang_io_unregister_buffers io_unregister_buffers
#define std_io_core_xlang_io_read_fixed xlang_io_read_fixed
#define std_io_core_xlang_io_write_fixed xlang_io_write_fixed
#define std_io_core_xlang_io_wait_readable io_wait_readable
/* codegen 体内调 std_io_driver_io_*；#undef 后重绑到 preamble/io.o 的 io_*。 */
#define std_io_driver_io_read_batch_buf io_read_batch_buf
#define std_io_driver_io_write_batch_buf io_write_batch_buf
#define std_io_driver_io_register_buffers_buf(bufs, nr) io_register_buffers_buf((intptr_t)(void *)(bufs), (int)(nr))
#ifndef __cplusplus
/* 仅补 co-emit 未定义的符号；勿桩 xlang_io_submit_write / submit_read_batch_buf（同 TU 强定义）。 */
extern int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);

extern int32_t xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle);

extern int32_t xlang_io_read_fixed(size_t h, uint32_t bi, size_t o, size_t l, uint32_t t);

extern int32_t xlang_io_write_fixed(size_t h, uint32_t bi, size_t o, size_t l, uint32_t t);

extern int32_t xlang_io_read_ptr_backend(void);

extern int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr);

extern int io_wait_readable(int32_t *fds, int n, unsigned timeout_ms);

extern ptrdiff_t io_read_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);

extern ptrdiff_t io_write_batch_buf(int fd, const struct std_io_driver_Buffer *bufs, int n, unsigned timeout_ms);

extern int32_t process_xlang_argc_get(void);
extern uint8_t *process_xlang_argv_get(int32_t i);
extern int32_t process_args_count_c(void);

extern uint8_t * process_arg_c(int32_t i);

extern int32_t args_iter_count_c(void);

extern uint8_t * args_iter_at_c(int32_t i);

extern uint64_t std_io_driver_driver_read_ptr_gen(void);

extern int64_t ctx_background_c(void);

extern void ctx_cancel_c(int64_t c);

extern int64_t ctx_deadline_ns_c(int64_t c);

extern void ctx_free_c(int64_t c);

extern int32_t ctx_get_value_c(int64_t h, uint8_t *key, int64_t *out);

extern int32_t ctx_is_cancelled_c(int64_t c);

extern int64_t ctx_remaining_ns_c(int64_t c);

extern int32_t ctx_set_value_c(int64_t h, uint8_t *key, int64_t value);

extern int64_t ctx_with_cancel_c(int64_t p);

extern int64_t ctx_with_deadline_c(int64_t p, int64_t ns);

extern int64_t ctx_with_timeout_c(int64_t p, int64_t ns);

#endif
struct std_net_Ipv4Addr { uint8_t a; uint8_t b; uint8_t c; uint8_t d; };
struct std_net_Ipv6Addr { uint8_t b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15; };
#define handle_from_fd std_io_handle_from_fd
#define submit_read_batch_buf std_io_submit_read_batch_buf
#define submit_write_batch_buf std_io_submit_write_batch_buf
#define read_fixed_fd(x, a, b, c, d) std_io_read_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)
#define write_fixed_fd(x, a, b, c, d) std_io_write_fixed_fd_impl(xlang_io_net_fd(x), a, b, c, d)
/* 实际符号用 _real；仅定义 std_net_net_* 宏。
 * 【Why 勿 #define net_close_socket_c / net_run_accept_workers_c】
 * link_only 路径会 emit `extern int32_t net_close_socket_c(...)`；
 * 若宏同名，extern 声明被展开 → expected parameter declarator。 */
extern int32_t net_close_socket_c_real(int32_t fd);
extern int32_t net_run_accept_workers_c_real(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms);
extern int32_t net_close_socket_c(int32_t fd);
extern int32_t net_run_accept_workers_c(int32_t listener_fd, int32_t n_workers, uint32_t timeout_ms);
#define std_net_net_close_socket_c(x) net_close_socket_c_real(xlang_io_net_fd(x))
#define std_net_net_run_accept_workers_c(x, n, t) net_run_accept_workers_c_real(xlang_io_net_fd(x), n, t)
#define STD_FS_FS_IOVEC_BUF_DEFINED
struct std_fs_FsIovecBuf { void *ptr; size_t length; size_t handle; };
#define std_fs_posix_FsIovecBuf std_fs_FsIovecBuf
struct std_io_sync_Iovec { uint8_t *base; size_t length; };
#define std_fs_posix_Iovec std_io_sync_Iovec
struct std_map_Map_i32_i32;
typedef struct std_io_driver_Buffer std_net_Buffer;
struct std_error_Error { int32_t code; };
struct std_error_ErrorChain { int32_t depth; int32_t c0; int32_t c1; int32_t c2; int32_t c3; };
struct std_string_String { uint8_t data[256]; int32_t length; };
typedef struct std_string_String String;
struct std_string_StrView { uint8_t *ptr; int32_t length; };
struct std_heap_Arena64 { uint8_t *chunk; size_t cap; size_t off; };
struct std_heap_Allocator { int32_t kind; struct std_heap_Arena64 *arena; };
struct std_vec_Vec_i32;
struct core_option_Option_i32 { int is_some; int32_t value; };
struct core_option_Option_u8 { int is_some; uint8_t value; uint8_t _pad0; uint8_t _pad1; uint8_t _pad2; };
struct core_option_Option_u64 { int is_some; int32_t _pad; uint64_t value; };
struct core_option_Option_ptr_u8 { int is_some; int32_t _pad; uint8_t *value; };
struct core_result_Result_i32 { int32_t value; int32_t _pad1; int32_t err; int32_t _pad2; };
struct core_result_Result_u8 { uint8_t value; uint8_t _pad1; uint8_t _pad2; uint8_t _pad3; int32_t err; int32_t _pad4; };
extern void xlang_panic_(int, int);
extern int32_t core_types_placeholder(void);
extern int32_t std_heap_alloc_size_zero(void);
extern int32_t std_runtime_runtime_ready(void);
#ifndef __cplusplus
extern int32_t std_vec_vec_len_empty(void);

extern int32_t std_vec_len_empty(void);

#else
extern int32_t std_vec_vec_len_empty(void);
extern int32_t std_vec_len_empty(void);
#endif
#define vec_len_empty std_vec_vec_len_empty
#define alloc_size_zero std_heap_alloc_size_zero
#define runtime_ready std_runtime_runtime_ready
#ifndef __cplusplus
extern int32_t std_string_placeholder(void);

#else
extern int32_t std_string_placeholder(void);
#endif
extern int32_t fmt_i32(int32_t);
extern struct std_string_String std_string_string_new(void);
typedef struct std_fs_FsIovecBuf fs_iovec_buf_t;
extern int32_t fs_open_read_c(uint8_t *path);
extern uint64_t fs_direct_align_c(void);
extern int32_t fs_fadvise_sequential_c(int32_t fd);
extern int32_t fs_fadvise_willneed_c(int32_t fd, int64_t offset, size_t len);
extern int64_t fs_copy_file_range_c(int32_t fd_in, int32_t fd_out, size_t len);
extern int64_t fs_sendfile_c(int32_t out_fd, int32_t in_fd, size_t count);
extern int64_t fs_pipe_splice_c(int32_t fd_in, int32_t fd_out, size_t len);
extern int32_t fs_sync_range_c(int32_t fd, int64_t offset, size_t len);
extern int32_t fs_sync_c(int32_t fd);
extern int32_t fs_fallocate_c(int32_t fd, int64_t offset, int64_t len);
extern int32_t fs_last_error_c(void);
extern int64_t fs_readv_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);
extern int64_t fs_writev_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);
extern int32_t std_path_empty_len(void);
#define empty_len() std_path_empty_len()
extern int32_t map_i32_i32_find_c(const int32_t *keys, const uint8_t *occupied, int32_t cap, int32_t key);
extern int32_t std_map_empty_size(void);
#define empty_size(_a, _b) std_map_empty_size()
extern int32_t std_error_error_ok(void);
#define error_ok(_a, _b) std_error_error_ok()
void xlang_panic_(int has_msg, int msg_val);
extern int32_t driver_check_quiet_ok_get(void);
extern int32_t fmt_walk_skip_dot_name(uint8_t * name);
extern int32_t check_one_need_fallback_diag(int32_t rc, int32_t nd, int32_t nd_errors, int32_t nd_warnings, int32_t nd_infos, int32_t direct_diag);
extern int32_t xlang_path_is_absolute(uint8_t * path);
extern int32_t check_one_finalize_rc(int32_t rc, int32_t warn_count);
extern uint8_t * driver_fmt_check_lit_check_error(void);
extern uint8_t * driver_fmt_check_lit_fmt_error(void);
extern uint8_t * driver_fmt_check_lit_chk002(void);
extern uint8_t * driver_fmt_check_lit_fmt001(void);
extern uint8_t * driver_collect_error_kind(void);
extern uint8_t * driver_collect_missing_path_code(void);
extern uint8_t * fmt_builtin_ignore_at(int32_t i);
extern uint8_t * fmt_default_product_sub_at(int32_t i);
extern uint8_t * fmt_user_ignore_at(int32_t i);
extern uint8_t * fmt_path_resolve_abs(uint8_t * path);
extern int32_t driver_collect_mode_is_check(void);
extern void driver_collect_mode_set(int32_t v);
extern int32_t check_user_passed_L_get(void);
extern void check_user_passed_L_set(int32_t v);
extern int32_t fmt_user_ignore_count(void);
extern void fmt_user_ignore_count_set(int32_t v);
extern int32_t fmt_path_ends_with_dot_x(uint8_t * path);
extern int32_t fmt_file_list_n(void);
extern void fmt_file_list_n_set(int32_t v);
extern uint8_t * fmt_file_list_at(int32_t i);
extern int32_t fmt_file_list_store(uint8_t * abs_path);
extern int32_t fmt_check_lib_bufs_n(void);
extern void fmt_check_lib_bufs_n_set(int32_t v);
extern void fmt_check_lib_bufs_reset(void);
extern uint8_t * fmt_check_lib_buf_at(int32_t i);
extern int32_t fmt_check_lib_buf_store(int32_t i, uint8_t * path);
extern int32_t check_lint_fail_on_warnings(void);
extern int32_t fmt_check_invoke_compile(int32_t argc, uint8_t * check_argv);
extern void fmt_check_dep_clear(void);
extern int32_t fmt_path_stat_kind(uint8_t * path);
extern void check_try_append_lib_root(uint8_t * check_argv, int32_t * n, uint8_t * dir);
extern void check_init_user_lib_flags(int32_t argc, uint8_t * argv, int32_t path_start);
extern void driver_check_set_current_file(uint8_t * path);
extern int32_t driver_check_print_collected_diagnostics(uint8_t * path);
extern int32_t check_one_file(uint8_t * path, int32_t argc, uint8_t * argv);
extern int32_t path_should_ignore(uint8_t * path);
extern int32_t file_list_push(uint8_t * path);
extern void walk_dir_collect_process_child(uint8_t * child, int32_t is_dir, int32_t is_reg);
extern void walk_dir_collect(uint8_t * dir);
extern void parse_ignore_opt(uint8_t * arg);
extern void file_list_clear(void);
extern int32_t fmt_try_walk_if_product_subdir(uint8_t * sub);
extern void fmt_walk_cwd_fallback(void);
extern void check_collect_default_product_dirs(void);
extern void collect_paths_missing_diag_pure(uint8_t * path);
extern void collect_paths_from_arg(uint8_t * arg);
extern void check_append_repo_lib_roots(uint8_t * path, uint8_t * check_argv, int32_t * n);
extern void check_argv_append_default_libs_for_path(uint8_t * path, uint8_t * check_argv, int32_t * n);
extern int32_t driver_run_fmt(int32_t argc, uint8_t * argv);
extern int32_t driver_run_compiler_check(int32_t argc, uint8_t * argv);
static int32_t g_fmt_collect_mode[1] = {1};
static int32_t g_fmt_user_passed_L[1] = {0};
static int32_t g_fmt_file_list_n[1] = {0};
static int32_t g_fmt_user_ignore_n[1] = {0};
static int32_t g_fmt_check_lib_bufs_n[1] = {0};
static uint8_t g_fmt_user_ignore_paths[8192];
static uint8_t g_fmt_check_lib_bufs[4096];
static uint8_t g_fmt_file_list_paths[4194304];
static uint8_t g_fmt_check_path_bss[1024];
static uint8_t g_fmt_lit_check_error[12] = {99, 104, 101, 99, 107, 32, 101, 114, 114, 111, 114, 0};
static uint8_t g_fmt_lit_fmt_error[10] = {102, 109, 116, 32, 101, 114, 114, 111, 114, 0};
static uint8_t g_fmt_lit_chk002[7] = {67, 72, 75, 48, 48, 50, 0};
static uint8_t g_fmt_lit_chk001[7] = {67, 72, 75, 48, 48, 49, 0};
static uint8_t g_fmt_lit_fmt001[7] = {70, 77, 84, 48, 48, 49, 0};
static uint8_t g_fmt_lit_check_failed_prefix[15] = {99, 104, 101, 99, 107, 32, 102, 97, 105, 108, 101, 100, 58, 32, 0};
static uint8_t g_fmt_lit_dash_L[3] = {45, 76, 0};
static uint8_t g_fmt_lit_cmd_check[6] = {99, 104, 101, 99, 107, 0};
static uint8_t g_fmt_lit_fail_fast[12] = {45, 45, 102, 97, 105, 108, 45, 102, 97, 115, 116, 0};
static uint8_t g_fmt_lit_ignore_eq[10] = {45, 45, 105, 103, 110, 111, 114, 101, 61, 0};
static uint8_t g_fmt_lit_dash_I[3] = {45, 73, 0};
static uint8_t g_fmt_lit_dash_o[3] = {45, 111, 0};
static uint8_t g_fmt_lit_dash_O[3] = {45, 79, 0};
static uint8_t g_fmt_lit_backend[9] = {45, 98, 97, 99, 107, 101, 110, 100, 0};
static uint8_t g_fmt_lit_no_x_paths[38] = {110, 111, 32, 46, 120, 32, 102, 105, 108, 101, 115, 32, 102, 111, 117, 110, 100, 32, 117, 110, 100, 101, 114, 32, 103, 105, 118, 101, 110, 32, 112, 97, 116, 104, 40, 115, 41, 0};
static uint8_t g_fmt_lit_no_x_cwd[39] = {110, 111, 32, 46, 120, 32, 102, 105, 108, 101, 115, 32, 102, 111, 117, 110, 100, 32, 105, 110, 32, 99, 117, 114, 114, 101, 110, 116, 32, 100, 105, 114, 101, 99, 116, 111, 114, 121, 0};
static uint8_t g_fmt_lit_dash_check[8] = {45, 45, 99, 104, 101, 99, 107, 0};
static uint8_t g_fmt_lit_note[5] = {110, 111, 116, 101, 0};
static uint8_t g_fmt_lit_info[5] = {105, 110, 102, 111, 0};
static uint8_t g_fmt_lit_needs_formatting[18] = {110, 101, 101, 100, 115, 32, 102, 111, 114, 109, 97, 116, 116, 105, 110, 103, 0};
static uint8_t g_fmt_lit_found_not_formatted[26] = {102, 111, 117, 110, 100, 32, 110, 111, 116, 32, 102, 111, 114, 109, 97, 116, 116, 101, 100, 32, 102, 105, 108, 101, 115, 0};
static uint8_t g_fmt_lit_run_xlang_fmt[38] = {114, 117, 110, 32, 96, 120, 108, 97, 110, 103, 32, 102, 109, 116, 96, 32, 116, 111, 32, 102, 111, 114, 109, 97, 116, 32, 116, 104, 101, 115, 101, 32, 102, 105, 108, 101, 115, 0};
static uint8_t g_fmt_lit_fmt_verbose_env[17] = {83, 72, 85, 88, 95, 70, 77, 84, 95, 86, 69, 82, 66, 79, 83, 69, 0};
static uint8_t g_fmt_lit_formatted_files[17] = {70, 111, 114, 109, 97, 116, 116, 101, 100, 32, 102, 105, 108, 101, 115, 0};
static uint8_t g_fmt_builtin_ignore_0[8] = {47, 46, 103, 105, 116, 47, 0, 0};
static uint8_t g_fmt_builtin_ignore_1[12] = {47, 98, 117, 105, 108, 100, 95, 97, 115, 109, 47, 0};
static uint8_t g_fmt_builtin_ignore_2[8] = {47, 98, 117, 105, 108, 100, 47, 0};
static uint8_t g_fmt_builtin_ignore_3[15] = {47, 110, 111, 100, 101, 95, 109, 111, 100, 117, 108, 101, 115, 47, 0};
static uint8_t g_fmt_builtin_ignore_4[11] = {47, 46, 99, 117, 114, 115, 111, 114, 47, 0, 0};
static uint8_t g_fmt_builtin_ignore_5[21] = {47, 99, 111, 109, 112, 105, 108, 101, 114, 47, 98, 117, 105, 108, 100, 95, 97, 115, 109, 47, 0};
static uint8_t g_fmt_builtin_ignore_6[17] = {47, 99, 111, 109, 112, 105, 108, 101, 114, 47, 98, 117, 105, 108, 100, 47, 0};
static uint8_t g_fmt_builtin_ignore_7[17] = {47, 99, 111, 109, 112, 105, 108, 101, 114, 47, 116, 101, 115, 116, 115, 47, 0};
static uint8_t g_fmt_builtin_ignore_8[8] = {47, 116, 101, 115, 116, 115, 47, 0};
static uint8_t g_fmt_default_product_sub_0[13] = {99, 111, 109, 112, 105, 108, 101, 114, 47, 115, 114, 99, 0};
static uint8_t g_fmt_default_product_sub_1[5] = {99, 111, 114, 101, 0};
static uint8_t g_fmt_default_product_sub_2[4] = {115, 116, 100, 0};
static uint8_t g_fmt_default_product_sub_3[9] = {101, 120, 97, 109, 112, 108, 101, 115, 0};
static void init_globals(void) {
}
extern int32_t lsp_diag_print_stderr_human(uint8_t * path);
extern int32_t driver_run_compiler_full(int32_t argc, uint8_t * argv);
extern void driver_dep_seeded_clear_all(void);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern void diag_report(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * msg, uint8_t * detail);
extern void diag_set_file(uint8_t * path, uint8_t * source, int64_t source_len);
extern void diag_push_file(uint8_t * snapshot, uint8_t * path, uint8_t * source, int64_t source_len);
extern void diag_restore(uint8_t * snapshot);
extern int32_t runtime_read_file_view(uint8_t * path, uint8_t * out);
extern void runtime_release_file_view(uint8_t * view);
extern void lsp_diag_collect_begin(void);
extern void lsp_diag_collect_end(void);
extern int32_t lsp_diag_count_severity(int32_t severity);
extern void driver_check_diag_emitted_reset(void);
extern int32_t driver_check_diag_emitted_get(void);
extern void driver_check_only_set(int32_t v);
extern int32_t driver_fmt_one_file(uint8_t * path, int32_t path_len);
extern void driver_fmt_check_only_set(int32_t v);
extern int32_t driver_fmt_check_only_get(void);
extern uint8_t * fmt_check_path_bss_slot(int32_t which);
extern uint8_t * xlang_ptr_slot_get(uint8_t * arr, int32_t i);
extern void xlang_ptr_slot_set(uint8_t * arr, int32_t i, uint8_t * p);
int32_t driver_check_quiet_ok_get(void) {
  return 1;
}
int32_t fmt_walk_skip_dot_name(uint8_t * name) {
  if ((name ==((uint8_t *)(0)))) {
    return 1;
  }
  if (((name)[0] ==0)) {
    return 1;
  }
  if (((name)[0] ==46)) {
    return 1;
  }
  return 0;
}
int32_t check_one_need_fallback_diag(int32_t rc, int32_t nd, int32_t nd_errors, int32_t nd_warnings, int32_t nd_infos, int32_t direct_diag) {
  if ((rc ==0)) {
    return 0;
  }
  if ((direct_diag !=0)) {
    return 0;
  }
  if ((nd ==0)) {
    return 1;
  }
  if ((nd_errors !=0)) {
    return 0;
  }
  if ((nd_warnings !=0)) {
    return 0;
  }
  if ((nd_infos !=0)) {
    return 0;
  }
  return 1;
}
int32_t xlang_path_is_absolute(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((path)[0] ==0)) {
    return 0;
  }
  if (((path)[0] ==47)) {
    return 1;
  }
  if (((path)[1] ==0)) {
    return 0;
  }
  if (((path)[1] !=58)) {
    return 0;
  }
  if (((path)[0] < 65)) {
    return 0;
  }
  if (((path)[0] <=90)) {
    return 1;
  }
  if (((path)[0] < 97)) {
    return 0;
  }
  if (((path)[0] <=122)) {
    return 1;
  }
  return 0;
}
int32_t check_one_finalize_rc(int32_t rc, int32_t warn_count) {
  if ((rc !=0)) {
    return rc;
  }
  if ((warn_count <=0)) {
    return 0;
  }
  if ((check_lint_fail_on_warnings() !=0)) {
    return 1;
  }
  return 0;
}
uint8_t * driver_fmt_check_lit_check_error(void) {
  return &((g_fmt_lit_check_error)[0]);
}
uint8_t * driver_fmt_check_lit_fmt_error(void) {
  return &((g_fmt_lit_fmt_error)[0]);
}
uint8_t * driver_fmt_check_lit_chk002(void) {
  return &((g_fmt_lit_chk002)[0]);
}
uint8_t * driver_fmt_check_lit_fmt001(void) {
  return &((g_fmt_lit_fmt001)[0]);
}
uint8_t * driver_collect_error_kind(void) {
  if ((driver_collect_mode_is_check() !=0)) {
    return &((g_fmt_lit_check_error)[0]);
  }
  return &((g_fmt_lit_fmt_error)[0]);
}
uint8_t * driver_collect_missing_path_code(void) {
  if ((driver_collect_mode_is_check() !=0)) {
    return &((g_fmt_lit_chk002)[0]);
  }
  return &((g_fmt_lit_fmt001)[0]);
}
uint8_t * fmt_builtin_ignore_at(int32_t i) {
  if ((i ==0)) {
    return &((g_fmt_builtin_ignore_0)[0]);
  }
  if ((i ==1)) {
    return &((g_fmt_builtin_ignore_1)[0]);
  }
  if ((i ==2)) {
    return &((g_fmt_builtin_ignore_2)[0]);
  }
  if ((i ==3)) {
    return &((g_fmt_builtin_ignore_3)[0]);
  }
  if ((i ==4)) {
    return &((g_fmt_builtin_ignore_4)[0]);
  }
  if ((i ==5)) {
    return &((g_fmt_builtin_ignore_5)[0]);
  }
  if ((i ==6)) {
    return &((g_fmt_builtin_ignore_6)[0]);
  }
  if ((i ==7)) {
    return &((g_fmt_builtin_ignore_7)[0]);
  }
  if ((i ==8)) {
    return &((g_fmt_builtin_ignore_8)[0]);
  }
  return ((uint8_t *)(0));
}
uint8_t * fmt_default_product_sub_at(int32_t i) {
  if ((i ==0)) {
    return &((g_fmt_default_product_sub_0)[0]);
  }
  if ((i ==1)) {
    return &((g_fmt_default_product_sub_1)[0]);
  }
  if ((i ==2)) {
    return &((g_fmt_default_product_sub_2)[0]);
  }
  if ((i ==3)) {
    return &((g_fmt_default_product_sub_3)[0]);
  }
  return ((uint8_t *)(0));
}
uint8_t * fmt_user_ignore_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  {
    uint8_t * base = &((g_fmt_user_ignore_paths)[0]);
    if ((i >=(g_fmt_user_ignore_n)[0])) {
      return ((uint8_t *)(0));
    }
    return (base + (i * 256));
  }
  return ((uint8_t *)(0));
}
uint8_t * fmt_path_resolve_abs(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return ((uint8_t *)(0));
  }
  {
    uint8_t * buf = fmt_check_path_bss_slot(1);
    if ((buf ==((uint8_t *)(0)))) {
      return ((uint8_t *)(0));
    }
    if ((xlang_path_is_absolute(path) !=0)) {
      int32_t i = 0;
      while ((i < 511)) {
        uint8_t c = (path)[i];
        (void)(((buf)[i] = c));
        if ((c ==0)) {
          return buf;
        }
        (void)((i = (i + 1)));
      }
      (void)(((buf)[511] = 0));
      return buf;
    }
    uint8_t * p = getcwd(buf, 512);
    if ((p ==((uint8_t *)(0)))) {
      return ((uint8_t *)(0));
    }
    int32_t n = 0;
    while ((n < 511)) {
      if (((buf)[n] ==0)) {
        break;
      }
      (void)((n = (n + 1)));
    }
    int32_t plen = 0;
    while ((plen < 512)) {
      if (((path)[plen] ==0)) {
        break;
      }
      (void)((plen = (plen + 1)));
    }
    if ((((n + 1) + plen) >=512)) {
      return ((uint8_t *)(0));
    }
    (void)(((buf)[n] = 47));
    (void)((n = (n + 1)));
    int32_t j = 0;
    while ((j <=plen)) {
      uint8_t c2 = (path)[j];
      (void)(((buf)[(n + j)] = c2));
      if ((c2 ==0)) {
        break;
      }
      (void)((j = (j + 1)));
    }
    return buf;
  }
  return ((uint8_t *)(0));
}
int32_t driver_collect_mode_is_check(void) {
  if (((g_fmt_collect_mode)[0] ==2)) {
    return 1;
  }
  return 0;
}
void driver_collect_mode_set(int32_t v) {
  (void)(((g_fmt_collect_mode)[0] = v));
  (void)(0);
  return;
}
int32_t check_user_passed_L_get(void) {
  return (g_fmt_user_passed_L)[0];
  return 0;
}
void check_user_passed_L_set(int32_t v) {
  if ((v !=0)) {
    (void)(((g_fmt_user_passed_L)[0] = 1));
  } else {
    (void)(((g_fmt_user_passed_L)[0] = 0));
  }
  (void)(0);
  return;
}
int32_t fmt_user_ignore_count(void) {
  return (g_fmt_user_ignore_n)[0];
  return 0;
}
void fmt_user_ignore_count_set(int32_t v) {
  if ((v < 0)) {
    (void)(((g_fmt_user_ignore_n)[0] = 0));
  } else {
    (void)(((g_fmt_user_ignore_n)[0] = v));
  }
  (void)(0);
  return;
}
int32_t fmt_path_ends_with_dot_x(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    int32_t i = 0;
    while ((i < 4096)) {
      if (((path)[i] ==0)) {
        if ((i < 2)) {
          return 0;
        }
        if (((path)[(i - 2)] ==46)) {
          if (((path)[(i - 1)] ==120)) {
            return 1;
          }
        }
        return 0;
      }
      (void)((i = (i + 1)));
    }
  }
  return 0;
}
int32_t fmt_file_list_n(void) {
  return (g_fmt_file_list_n)[0];
  return 0;
}
void fmt_file_list_n_set(int32_t v) {
  if ((v < 0)) {
    (void)(((g_fmt_file_list_n)[0] = 0));
  } else {
    (void)(((g_fmt_file_list_n)[0] = v));
  }
  (void)(0);
  return;
}
uint8_t * fmt_file_list_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  {
    uint8_t * base = &((g_fmt_file_list_paths)[0]);
    if ((i >=(g_fmt_file_list_n)[0])) {
      return ((uint8_t *)(0));
    }
    return (base + (i * 512));
  }
  return ((uint8_t *)(0));
}
int32_t fmt_file_list_store(uint8_t * abs_path) {
  if ((abs_path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    int32_t n = (g_fmt_file_list_n)[0];
    if ((n >=8192)) {
      return (0 - 1);
    }
    uint8_t * base = &((g_fmt_file_list_paths)[0]);
    uint8_t * slot = (base + (n * 512));
    int32_t k = 0;
    while ((k < 511)) {
      uint8_t c = (abs_path)[k];
      (void)(((slot)[k] = c));
      if ((c ==0)) {
        (void)(fmt_file_list_n_set((n + 1)));
        return 0;
      }
      (void)((k = (k + 1)));
    }
    (void)(((slot)[511] = 0));
    (void)(fmt_file_list_n_set((n + 1)));
  }
  return 0;
}
int32_t fmt_check_lib_bufs_n(void) {
  return (g_fmt_check_lib_bufs_n)[0];
  return 0;
}
void fmt_check_lib_bufs_n_set(int32_t v) {
  if ((v < 0)) {
    (void)(((g_fmt_check_lib_bufs_n)[0] = 0));
  } else {
    (void)(((g_fmt_check_lib_bufs_n)[0] = v));
  }
  (void)(0);
  return;
}
void fmt_check_lib_bufs_reset(void) {
  (void)(fmt_check_lib_bufs_n_set(0));
}
uint8_t * fmt_check_lib_buf_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=8)) {
    return ((uint8_t *)(0));
  }
  {
    uint8_t * base = &((g_fmt_check_lib_bufs)[0]);
    return (base + (i * 512));
  }
  return ((uint8_t *)(0));
}
uint8_t * fmt_check_path_bss_slot(int32_t which) {
  {
    uint8_t * base = &((g_fmt_check_path_bss)[0]);
    if ((which < 0)) {
      return base;
    }
    if ((which > 1)) {
      return base;
    }
    return (base + (which * 512));
  }
  return ((uint8_t *)(0));
}
int32_t fmt_check_lib_buf_store(int32_t i, uint8_t * path) {
  if ((i < 0)) {
    return 0;
  }
  if ((i >=8)) {
    return 0;
  }
  if ((path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    uint8_t * slot = fmt_check_lib_buf_at(i);
    if ((slot ==((uint8_t *)(0)))) {
      return 0;
    }
    int32_t k = 0;
    while ((k < 511)) {
      uint8_t c = (path)[k];
      (void)(((slot)[k] = c));
      if ((c ==0)) {
        return 1;
      }
      (void)((k = (k + 1)));
    }
    (void)(((slot)[511] = 0));
  }
  return 1;
}
int32_t check_lint_fail_on_warnings(void) {
  {
    /* wave234 G.7: XLANG_LINT_CI_FAIL_ON via link_abi_getenv (not raw getenv). */
    uint8_t * v = link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x4c\x49\x4e\x54\x5f\x43\x49\x5f\x46\x41\x49\x4c\x5f\x4f\x4e"));
    if ((v ==((uint8_t *)(0)))) {
      return 0;
    }
    if (((v)[0] ==119)) {
      if (((v)[1] ==97)) {
        if (((v)[2] ==114)) {
          if (((v)[3] ==110)) {
            if (((v)[4] ==0)) {
              return 1;
            }
            if (((v)[4] ==105)) {
              if (((v)[5] ==110)) {
                if (((v)[6] ==103)) {
                  if (((v)[7] ==0)) {
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
int32_t fmt_check_invoke_compile(int32_t argc, uint8_t * check_argv) {
  return driver_run_compiler_full(argc, check_argv);
  return 0;
}
void fmt_check_dep_clear(void) {
  (void)(driver_dep_seeded_clear_all());
  (void)(0);
  return;
}
int32_t fmt_path_stat_kind(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    uint8_t * d = xlang_fmt_opendir(path);
    if ((d !=((uint8_t *)(0)))) {
      (void)(xlang_fmt_closedir(d));
      return 1;
    }
    if ((xlang_fmt_access(path, 0) ==0)) {
      return 0;
    }
  }
  return (0 - 1);
}
void check_try_append_lib_root(uint8_t * check_argv, int32_t * n, uint8_t * dir) {
  if ((check_argv ==((uint8_t *)(0)))) {
    return;
  }
  if ((n ==((int32_t *)(0)))) {
    return;
  }
  if ((dir ==((uint8_t *)(0)))) {
    return;
  }
  if (((dir)[0] ==0)) {
    return;
  }
  if ((check_user_passed_L_get() !=0)) {
    return;
  }
  {
    uint8_t core_path[560] = {};
    uint8_t std_path[560] = {};
    int32_t di = 0;
    int32_t nb = fmt_check_lib_bufs_n();
    int32_t i = 0;
    uint8_t * slot2 = fmt_check_lib_buf_at(nb);
    int32_t ni = (n)[0];
    if (((n)[0] >=58)) {
      return;
    }
    while ((di < 512)) {
      uint8_t c = (dir)[di];
      if ((c ==0)) {
        break;
      }
      (void)(((core_path)[di] = c));
      (void)(((std_path)[di] = c));
      (void)((di = (di + 1)));
    }
    if (((di + 6) >=560)) {
      return;
    }
    (void)(((core_path)[di] = 47));
    (void)(((core_path)[(di + 1)] = 99));
    (void)(((core_path)[(di + 2)] = 111));
    (void)(((core_path)[(di + 3)] = 114));
    (void)(((core_path)[(di + 4)] = 101));
    (void)(((core_path)[(di + 5)] = 0));
    (void)(((std_path)[di] = 47));
    (void)(((std_path)[(di + 1)] = 115));
    (void)(((std_path)[(di + 2)] = 116));
    (void)(((std_path)[(di + 3)] = 100));
    (void)(((std_path)[(di + 4)] = 0));
    if ((fmt_path_stat_kind(&((core_path)[0])) !=1)) {
      return;
    }
    if ((fmt_path_stat_kind(&((std_path)[0])) !=1)) {
      return;
    }
    while ((i < nb)) {
      uint8_t * slot = fmt_check_lib_buf_at(i);
      if ((slot !=((uint8_t *)(0)))) {
        int32_t eq = 1;
        int32_t j = 0;
        while ((j < 512)) {
          uint8_t a = (slot)[j];
          uint8_t b = (dir)[j];
          if ((a !=b)) {
            (void)((eq = 0));
            break;
          }
          if ((a ==0)) {
            break;
          }
          (void)((j = (j + 1)));
        }
        if ((eq !=0)) {
          return;
        }
      }
      (void)((i = (i + 1)));
    }
    if ((nb >=8)) {
      return;
    }
    if ((fmt_check_lib_buf_store(nb, dir) ==0)) {
      return;
    }
    if ((slot2 ==((uint8_t *)(0)))) {
      return;
    }
    (void)(xlang_ptr_slot_set(check_argv, ni, &((g_fmt_lit_dash_L)[0])));
    (void)(xlang_ptr_slot_set(check_argv, (ni + 1), slot2));
    (void)(((n)[0] = (ni + 2)));
    (void)(fmt_check_lib_bufs_n_set((nb + 1)));
  }
  (void)(0);
  return;
}
void check_init_user_lib_flags(int32_t argc, uint8_t * argv, int32_t path_start) {
  (void)(check_user_passed_L_set(0));
  (void)(fmt_check_lib_bufs_reset());
  if ((argv ==((uint8_t *)(0)))) {
    return;
  }
  if ((path_start < 0)) {
    return;
  }
  {
    int32_t i = path_start;
    while ((i < argc)) {
      uint8_t * a = xlang_ptr_slot_get(argv, i);
      if ((a !=((uint8_t *)(0)))) {
        if (((a)[0] ==45)) {
          if (((a)[1] ==76)) {
            if (((a)[2] ==0)) {
              (void)(check_user_passed_L_set(1));
              return;
            }
          }
        }
      }
      (void)((i = (i + 1)));
    }
  }
}
void driver_check_set_current_file(uint8_t * path) {
  {
    uint8_t * buf = fmt_check_path_bss_slot(0);
    if ((buf ==((uint8_t *)(0)))) {
      return;
    }
    if ((path ==((uint8_t *)(0)))) {
      (void)(((buf)[0] = 0));
      return;
    }
    int32_t i = 0;
    while ((i < 511)) {
      uint8_t c = (path)[i];
      (void)(((buf)[i] = c));
      if ((c ==0)) {
        return;
      }
      (void)((i = (i + 1)));
    }
    (void)(((buf)[511] = 0));
  }
  (void)(0);
  return;
}
int32_t driver_check_print_collected_diagnostics(uint8_t * path) {
  {
    uint8_t * buf = fmt_check_path_bss_slot(0);
    if ((path !=((uint8_t *)(0)))) {
      return lsp_diag_print_stderr_human(path);
    }
    if ((buf ==((uint8_t *)(0)))) {
      return 0;
    }
    return lsp_diag_print_stderr_human(buf);
  }
  return 0;
}
int32_t check_one_file(uint8_t * path, int32_t argc, uint8_t * argv) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((argv ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((argc <=0)) {
    return (0 - 1);
  }
  {
    uint8_t view[32] = {};
    int32_t z = 0;
    while ((z < 32)) {
      (void)(((view)[z] = 0));
      (void)((z = (z + 1)));
    }
    int32_t have_diag_view = 0;
    uint8_t * view_data = ((uint8_t *)(0));
    int64_t view_len = 0;
    if ((runtime_read_file_view(path, &((view)[0])) ==0)) {
      uint8_t * len_bits = xlang_ptr_slot_get(&((view)[0]), 1);
      (void)((view_data = xlang_ptr_slot_get(&((view)[0]), 0)));
      (void)((view_len = ((int64_t)(len_bits))));
      (void)(diag_set_file(path, view_data, view_len));
      (void)((have_diag_view = 1));
    } else {
      (void)(diag_set_file(path, ((uint8_t *)(0)), 0));
    }
    (void)(lsp_diag_collect_begin());
    (void)(driver_check_diag_emitted_reset());
    (void)(driver_check_set_current_file(path));
    (void)(fmt_check_lib_bufs_reset());
    uint8_t check_argv[512] = {};
    int32_t n = 0;
    uint8_t * a0 = xlang_ptr_slot_get(argv, 0);
    (void)(xlang_ptr_slot_set(&((check_argv)[0]), 0, a0));
    (void)((n = 1));
    (void)(xlang_ptr_slot_set(&((check_argv)[0]), n, &((g_fmt_lit_cmd_check)[0])));
    (void)((n = (n + 1)));
    int32_t i = 2;
    while ((i < argc)) {
      uint8_t * ai = xlang_ptr_slot_get(argv, i);
      if ((n >=60)) {
        break;
      }
      if ((ai !=((uint8_t *)(0)))) {
        if (((ai)[0] ==45)) {
          int32_t take_val = 0;
          (void)(xlang_ptr_slot_set(&((check_argv)[0]), n, ai));
          (void)((n = (n + 1)));
          if ((strcmp(ai, &((g_fmt_lit_dash_L)[0])) ==0)) {
            (void)((take_val = 1));
          } else {
            if ((strcmp(ai, &((g_fmt_lit_dash_I)[0])) ==0)) {
              (void)((take_val = 1));
            } else {
              if ((strcmp(ai, &((g_fmt_lit_dash_o)[0])) ==0)) {
                (void)((take_val = 1));
              } else {
                if ((strcmp(ai, &((g_fmt_lit_backend)[0])) ==0)) {
                  (void)((take_val = 1));
                } else {
                  if ((strcmp(ai, &((g_fmt_lit_dash_O)[0])) ==0)) {
                    (void)((take_val = 1));
                  }
                }
              }
            }
          }
          if ((take_val !=0)) {
            if (((i + 1) < argc)) {
              if ((n < 60)) {
                uint8_t * av = xlang_ptr_slot_get(argv, i);
                (void)((i = (i + 1)));
                (void)(xlang_ptr_slot_set(&((check_argv)[0]), n, av));
                (void)((n = (n + 1)));
              }
            }
          }
        } else {
          if ((strcmp(ai, &((g_fmt_lit_fail_fast)[0])) ==0)) {
            (void)(xlang_ptr_slot_set(&((check_argv)[0]), n, ai));
            (void)((n = (n + 1)));
          }
        }
      }
      (void)((i = (i + 1)));
    }
    (void)(check_argv_append_default_libs_for_path(path, &((check_argv)[0]), &(n)));
    if ((n < 64)) {
      (void)(xlang_ptr_slot_set(&((check_argv)[0]), n, path));
      (void)((n = (n + 1)));
    }
    (void)(driver_check_only_set(1));
    int32_t rc = fmt_check_invoke_compile(n, &((check_argv)[0]));
    (void)(driver_check_only_set(0));
    uint8_t snap[32] = {};
    int32_t si = 0;
    while ((si < 32)) {
      (void)(((snap)[si] = 0));
      (void)((si = (si + 1)));
    }
    if ((have_diag_view !=0)) {
      (void)(diag_push_file(&((snap)[0]), path, view_data, view_len));
    } else {
      (void)(diag_push_file(&((snap)[0]), path, ((uint8_t *)(0)), 0));
    }
    int32_t nd = lsp_diag_print_stderr_human(path);
    int32_t nd_errors = lsp_diag_count_severity(1);
    int32_t nd_warnings = lsp_diag_count_severity(2);
    int32_t nd_infos = lsp_diag_count_severity(3);
    int32_t direct_diag = driver_check_diag_emitted_get();
    (void)(diag_restore(&((snap)[0])));
    if ((check_one_need_fallback_diag(rc, nd, nd_errors, nd_warnings, nd_infos, direct_diag) !=0)) {
      uint8_t msg[600] = {};
      int32_t at = 0;
      uint8_t * pfx = &((g_fmt_lit_check_failed_prefix)[0]);
      int32_t pi = 0;
      while ((pi < 14)) {
        (void)(((msg)[at] = (pfx)[pi]));
        (void)((at = (at + 1)));
        (void)((pi = (pi + 1)));
      }
      int32_t qi = 0;
      while ((qi < 512)) {
        uint8_t c = (path)[qi];
        if ((c ==0)) {
          break;
        }
        if ((at >=598)) {
          break;
        }
        (void)(((msg)[at] = c));
        (void)((at = (at + 1)));
        (void)((qi = (qi + 1)));
      }
      (void)(((msg)[at] = 0));
      (void)(diag_report_with_code(path, 0, 0, &((g_fmt_lit_check_error)[0]), &((g_fmt_lit_chk001)[0]), &((msg)[0]), ((uint8_t *)(0))));
    }
    if ((nd_errors > 0)) {
      (void)((rc = 1));
    }
    (void)((rc = check_one_finalize_rc(rc, nd_warnings)));
    (void)(lsp_diag_collect_end());
    if ((have_diag_view !=0)) {
      (void)(runtime_release_file_view(&((view)[0])));
    }
    (void)(fmt_check_dep_clear());
    return rc;
  }
  return (0 - 1);
}
int32_t path_should_ignore(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return 1;
  }
  {
    int32_t i = 0;
    while ((i < 32)) {
      uint8_t * b = fmt_builtin_ignore_at(i);
      if ((b ==((uint8_t *)(0)))) {
        break;
      }
      if ((strstr(path, b) !=((uint8_t *)(0)))) {
        return 1;
      }
      (void)((i = (i + 1)));
    }
    int32_t n = fmt_user_ignore_count();
    int32_t j = 0;
    while ((j < n)) {
      uint8_t * u = fmt_user_ignore_at(j);
      if ((u !=((uint8_t *)(0)))) {
        if (((u)[0] !=0)) {
          if ((strstr(path, u) !=((uint8_t *)(0)))) {
            return 1;
          }
        }
      }
      (void)((j = (j + 1)));
    }
  }
  return 0;
}
int32_t file_list_push(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    uint8_t * abs_path = fmt_path_resolve_abs(path);
    if ((fmt_file_list_n() >=8192)) {
      return (0 - 1);
    }
    if ((abs_path ==((uint8_t *)(0)))) {
      return (0 - 1);
    }
    if ((path_should_ignore(abs_path) !=0)) {
      return 0;
    }
    if ((fmt_path_ends_with_dot_x(abs_path) ==0)) {
      return 0;
    }
    return fmt_file_list_store(abs_path);
  }
  return (0 - 1);
}
void walk_dir_collect_process_child(uint8_t * child, int32_t is_dir, int32_t is_reg) {
  if ((child ==((uint8_t *)(0)))) {
    return;
  }
  if ((path_should_ignore(child) !=0)) {
    return;
  }
  if ((is_dir !=0)) {
    (void)(walk_dir_collect(child));
    return;
  }
  if ((is_reg !=0)) {
    if ((fmt_path_ends_with_dot_x(child) !=0)) {
      (void)(file_list_push(child));
    }
  }
  (void)(0);
  return;
}
void walk_dir_collect(uint8_t * dir) {
  if ((dir ==((uint8_t *)(0)))) {
    return;
  }
  {
    uint8_t dir_buf[512] = {};
    int32_t di = 0;
    while ((di < 511)) {
      uint8_t c = (dir)[di];
      (void)(((dir_buf)[di] = c));
      if ((c ==0)) {
        break;
      }
      (void)((di = (di + 1)));
    }
    (void)(((dir_buf)[511] = 0));
    uint8_t * d = xlang_fmt_opendir(&((dir_buf)[0]));
    if ((d ==((uint8_t *)(0)))) {
      return;
    }
    int32_t guard = 0;
    while ((guard < 100000)) {
      uint8_t * name = xlang_fmt_readdir_name(d);
      uint8_t child[768] = {};
      int32_t ci = 0;
      int32_t ni = 0;
      int32_t is_dir = 0;
      int32_t is_reg = 0;
      int32_t k = 0;
      (void)((guard = (guard + 1)));
      if ((name ==((uint8_t *)(0)))) {
        break;
      }
      if ((fmt_walk_skip_dot_name(name) !=0)) {
        continue;
      }
      while ((ci < 511)) {
        uint8_t c2 = (dir_buf)[ci];
        if ((c2 ==0)) {
          break;
        }
        (void)(((child)[ci] = c2));
        (void)((ci = (ci + 1)));
      }
      if ((ci >=767)) {
        continue;
      }
      (void)(((child)[ci] = 47));
      (void)((ci = (ci + 1)));
      while ((ci < 767)) {
        uint8_t c3 = (name)[ni];
        (void)(((child)[ci] = c3));
        if ((c3 ==0)) {
          break;
        }
        (void)((ci = (ci + 1)));
        (void)((ni = (ni + 1)));
      }
      (void)(((child)[767] = 0));
      (void)((k = fmt_path_stat_kind(&((child)[0]))));
      if ((k ==1)) {
        (void)((is_dir = 1));
      } else {
        if ((k ==0)) {
          (void)((is_reg = 1));
        }
      }
      (void)(walk_dir_collect_process_child(&((child)[0]), is_dir, is_reg));
    }
    (void)(xlang_fmt_closedir(d));
  }
  (void)(0);
  return;
}
void parse_ignore_opt(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return;
  }
  if (((arg)[0] !=45)) {
    return;
  }
  if (((arg)[1] !=45)) {
    return;
  }
  if (((arg)[2] !=105)) {
    return;
  }
  if (((arg)[3] !=103)) {
    return;
  }
  if (((arg)[4] !=110)) {
    return;
  }
  if (((arg)[5] !=111)) {
    return;
  }
  if (((arg)[6] !=114)) {
    return;
  }
  if (((arg)[7] !=101)) {
    return;
  }
  if (((arg)[8] !=61)) {
    return;
  }
  {
    int32_t p = 9;
    int32_t n = fmt_user_ignore_count();
    uint8_t * base = &((g_fmt_user_ignore_paths)[0]);
    while ((n < 32)) {
      int32_t start = p;
      int32_t end = p;
      if (((arg)[p] ==0)) {
        break;
      }
      while (((arg)[end] !=0)) {
        if (((arg)[end] ==44)) {
          break;
        }
        (void)((end = (end + 1)));
      }
      if ((start < end)) {
        uint8_t * slot = (base + (n * 256));
        int32_t k = 0;
        while ((k < 255)) {
          if (((start + k) >=end)) {
            break;
          }
          (void)(((slot)[k] = (arg)[(start + k)]));
          (void)((k = (k + 1)));
        }
        (void)(((slot)[k] = 0));
        (void)((n = (n + 1)));
        (void)(fmt_user_ignore_count_set(n));
      }
      (void)((p = end));
      if (((arg)[p] ==44)) {
        (void)((p = (p + 1)));
      } else {
        break;
      }
    }
  }
  (void)(0);
  return;
}
void file_list_clear(void) {
  (void)(fmt_file_list_n_set(0));
}
int32_t fmt_try_walk_if_product_subdir(uint8_t * sub) {
  if ((sub ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    uint8_t cwd[512] = {};
    uint8_t * p = getcwd(&((cwd)[0]), 512);
    if ((p ==((uint8_t *)(0)))) {
      return 0;
    }
    uint8_t subp[560] = {};
    int32_t i = 0;
    while ((i < 511)) {
      uint8_t c = (cwd)[i];
      if ((c ==0)) {
        break;
      }
      (void)(((subp)[i] = c));
      (void)((i = (i + 1)));
    }
    if ((i >=559)) {
      return 0;
    }
    (void)(((subp)[i] = 47));
    (void)((i = (i + 1)));
    int32_t j = 0;
    while ((i < 559)) {
      uint8_t c2 = (sub)[j];
      (void)(((subp)[i] = c2));
      if ((c2 ==0)) {
        break;
      }
      (void)((i = (i + 1)));
      (void)((j = (j + 1)));
    }
    (void)(((subp)[559] = 0));
    if ((fmt_path_stat_kind(&((subp)[0])) ==1)) {
      (void)(walk_dir_collect(&((subp)[0])));
      return 1;
    }
  }
  return 0;
}
void fmt_walk_cwd_fallback(void) {
  {
    uint8_t cwd[512] = {};
    uint8_t * p = getcwd(&((cwd)[0]), 512);
    if ((p ==((uint8_t *)(0)))) {
      return;
    }
    (void)(walk_dir_collect(&((cwd)[0])));
  }
  (void)(0);
  return;
}
void check_collect_default_product_dirs(void) {
  /* Bare check: recursive cwd *.x (match thin.x / cold seed). */
  (void)(fmt_walk_cwd_fallback());
  (void)(0);
  return;
}
void collect_paths_missing_diag_pure(uint8_t * path) {
  {
    uint8_t msg[600] = {};
    (void)(((msg)[0] = 99));
    (void)(((msg)[1] = 97));
    (void)(((msg)[2] = 110));
    (void)(((msg)[3] = 110));
    (void)(((msg)[4] = 111));
    (void)(((msg)[5] = 116));
    (void)(((msg)[6] = 32));
    (void)(((msg)[7] = 97));
    (void)(((msg)[8] = 99));
    (void)(((msg)[9] = 99));
    (void)(((msg)[10] = 101));
    (void)(((msg)[11] = 115));
    (void)(((msg)[12] = 115));
    (void)(((msg)[13] = 32));
    (void)(((msg)[14] = 112));
    (void)(((msg)[15] = 97));
    (void)(((msg)[16] = 116));
    (void)(((msg)[17] = 104));
    (void)(((msg)[18] = 32));
    (void)(((msg)[19] = 39));
    int32_t at = 20;
    if ((path !=((uint8_t *)(0)))) {
      int32_t i = 0;
      while ((i < 512)) {
        uint8_t c = (path)[i];
        if ((c ==0)) {
          break;
        }
        if ((at >=598)) {
          break;
        }
        (void)(((msg)[at] = c));
        (void)((at = (at + 1)));
        (void)((i = (i + 1)));
      }
    }
    if ((at < 599)) {
      (void)(((msg)[at] = 39));
      (void)((at = (at + 1)));
    }
    (void)(((msg)[at] = 0));
    uint8_t * kind = driver_collect_error_kind();
    uint8_t * code = driver_collect_missing_path_code();
    (void)(diag_report_with_code(path, 0, 0, kind, code, &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
void collect_paths_from_arg(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return;
  }
  {
    int32_t k = fmt_path_stat_kind(arg);
    if ((k < 0)) {
      (void)(collect_paths_missing_diag_pure(arg));
      return;
    }
    if ((k ==1)) {
      uint8_t * base = fmt_path_resolve_abs(arg);
      if ((base !=((uint8_t *)(0)))) {
        (void)(walk_dir_collect(base));
      }
      return;
    }
    (void)(file_list_push(arg));
  }
  (void)(0);
  return;
}
void check_append_repo_lib_roots(uint8_t * path, uint8_t * check_argv, int32_t * n) {
  if ((check_argv ==((uint8_t *)(0)))) {
    return;
  }
  if ((n ==((int32_t *)(0)))) {
    return;
  }
  if ((check_user_passed_L_get() !=0)) {
    return;
  }
  {
    uint8_t start[512] = {};
    int32_t last_slash = (0 - 1);
    int32_t k = 0;
    uint8_t cur[512] = {};
    int32_t ci = 0;
    int32_t depth = 0;
    if (((n)[0] >=58)) {
      return;
    }
    if ((path ==((uint8_t *)(0)))) {
      uint8_t * p0 = getcwd(&((start)[0]), 512);
      if ((p0 ==((uint8_t *)(0)))) {
        return;
      }
      (void)(check_try_append_lib_root(check_argv, n, &((start)[0])));
      return;
    }
    if (((path)[0] ==0)) {
      uint8_t * p1 = getcwd(&((start)[0]), 512);
      if ((p1 ==((uint8_t *)(0)))) {
        return;
      }
      (void)(check_try_append_lib_root(check_argv, n, &((start)[0])));
      return;
    }
    if (((path)[0] ==47)) {
      int32_t i = 0;
      while ((i < 511)) {
        uint8_t c = (path)[i];
        (void)(((start)[i] = c));
        if ((c ==0)) {
          break;
        }
        (void)((i = (i + 1)));
      }
      (void)(((start)[511] = 0));
    } else {
      uint8_t * p2 = getcwd(&((start)[0]), 512);
      if ((p2 ==((uint8_t *)(0)))) {
        return;
      }
      int32_t sl = 0;
      while ((sl < 511)) {
        if (((start)[sl] ==0)) {
          break;
        }
        (void)((sl = (sl + 1)));
      }
      int32_t plen = 0;
      while ((plen < 512)) {
        if (((path)[plen] ==0)) {
          break;
        }
        (void)((plen = (plen + 1)));
      }
      if ((((sl + 1) + plen) >=512)) {
        return;
      }
      (void)(((start)[sl] = 47));
      (void)((sl = (sl + 1)));
      int32_t j = 0;
      while ((j <=plen)) {
        uint8_t c2 = (path)[j];
        (void)(((start)[(sl + j)] = c2));
        if ((c2 ==0)) {
          break;
        }
        (void)((j = (j + 1)));
      }
    }
    while ((k < 512)) {
      if (((start)[k] ==0)) {
        break;
      }
      if (((start)[k] ==47)) {
        (void)((last_slash = k));
      }
      (void)((k = (k + 1)));
    }
    if ((last_slash > 0)) {
      (void)(((start)[last_slash] = 0));
    } else {
      if ((last_slash ==0)) {
        (void)(((start)[1] = 0));
      }
    }
    while ((ci < 512)) {
      uint8_t cc = (start)[ci];
      (void)(((cur)[ci] = cc));
      if ((cc ==0)) {
        break;
      }
      (void)((ci = (ci + 1)));
    }
    while ((depth < 8)) {
      int32_t plash = (0 - 1);
      int32_t pi = 0;
      (void)(check_try_append_lib_root(check_argv, n, &((cur)[0])));
      if (((cur)[0] ==47)) {
        if (((cur)[1] ==0)) {
          break;
        }
      }
      while ((pi < 512)) {
        if (((cur)[pi] ==0)) {
          break;
        }
        if (((cur)[pi] ==47)) {
          (void)((plash = pi));
        }
        (void)((pi = (pi + 1)));
      }
      if ((plash < 0)) {
        break;
      }
      if ((plash ==0)) {
        (void)(((cur)[0] = 47));
        (void)(((cur)[1] = 0));
      } else {
        (void)(((cur)[plash] = 0));
      }
      (void)((depth = (depth + 1)));
    }
  }
  (void)(0);
  return;
}
void check_argv_append_default_libs_for_path(uint8_t * path, uint8_t * check_argv, int32_t * n) {
  if ((check_argv ==((uint8_t *)(0)))) {
    return;
  }
  if ((n ==((int32_t *)(0)))) {
    return;
  }
  if ((check_user_passed_L_get() !=0)) {
    return;
  }
  {
    uint8_t cwd[512] = {};
    uint8_t * p = getcwd(&((cwd)[0]), 512);
    uint8_t needle_src[14] = {99, 111, 109, 112, 105, 108, 101, 114, 47, 115, 114, 99, 47, 0};
    uint8_t cs[560] = {};
    int32_t ci = 0;
    uint8_t needle_asm[18] = {99, 111, 109, 112, 105, 108, 101, 114, 47, 115, 114, 99, 47, 97, 115, 109, 47, 0};
    int32_t ai = 0;
    if (((n)[0] >=58)) {
      return;
    }
    (void)(check_append_repo_lib_roots(path, check_argv, n));
    if ((p ==((uint8_t *)(0)))) {
      return;
    }
    (void)(check_try_append_lib_root(check_argv, n, &((cwd)[0])));
    if ((path ==((uint8_t *)(0)))) {
      return;
    }
    /* wave1222: also accept bare "compiler" or "compiler/..." (without /src/).
     * Previously needle_src="compiler/src/" only matched paths already inside
     * the src tree, so `xlang check compiler` (the natural invocation) failed
     * to inject <cwd>/compiler/src as a lib root, breaking all cross-subdir
     * imports like import("asm.backend") from pipeline/pipeline.x.
     * PLATFORM: SHARED — both bare and /src/ forms now trigger lib_root inject. */
    {
      int matched = (strstr(path, &((needle_src)[0])) !=((uint8_t *)(0))) ? 1 : 0;
      if (!matched) {
        /* Try needle_compiler = "compiler" (bare form). */
        uint8_t needle_compiler[9] = {99, 111, 109, 112, 105, 108, 101, 114, 0};
        if (strstr(path, &((needle_compiler)[0])) !=((uint8_t *)(0))) {
          matched = 1;
        }
      }
      if (!matched) {
        return;
      }
    }
    if (((n)[0] >=56)) {
      return;
    }
    while ((ci < 511)) {
      uint8_t c = (cwd)[ci];
      if ((c ==0)) {
        break;
      }
      (void)(((cs)[ci] = c));
      (void)((ci = (ci + 1)));
    }
    if (((ci + 14) >=560)) {
      return;
    }
    (void)(((cs)[ci] = 47));
    (void)(((cs)[(ci + 1)] = 99));
    (void)(((cs)[(ci + 2)] = 111));
    (void)(((cs)[(ci + 3)] = 109));
    (void)(((cs)[(ci + 4)] = 112));
    (void)(((cs)[(ci + 5)] = 105));
    (void)(((cs)[(ci + 6)] = 108));
    (void)(((cs)[(ci + 7)] = 101));
    (void)(((cs)[(ci + 8)] = 114));
    (void)(((cs)[(ci + 9)] = 47));
    (void)(((cs)[(ci + 10)] = 115));
    (void)(((cs)[(ci + 11)] = 114));
    (void)(((cs)[(ci + 12)] = 99));
    (void)(((cs)[(ci + 13)] = 0));
    if ((fmt_path_stat_kind(&((cs)[0])) ==1)) {
      int32_t nb = fmt_check_lib_bufs_n();
      if ((nb < 8)) {
        if ((fmt_check_lib_buf_store(nb, &((cs)[0])) !=0)) {
          uint8_t * slot = fmt_check_lib_buf_at(nb);
          if ((slot !=((uint8_t *)(0)))) {
            int32_t ni = (n)[0];
            (void)(xlang_ptr_slot_set(check_argv, ni, &((g_fmt_lit_dash_L)[0])));
            (void)(xlang_ptr_slot_set(check_argv, (ni + 1), slot));
            (void)(((n)[0] = (ni + 2)));
            (void)(fmt_check_lib_bufs_n_set((nb + 1)));
          }
        }
      }
    }
    /* always inject compiler/src/asm after compiler/src match */
    if (((n)[0] >=56)) {
      return;
    }
    while ((ai < 511)) {
      uint8_t c2 = (cwd)[ai];
      if ((c2 ==0)) {
        break;
      }
      (void)(((cs)[ai] = c2));
      (void)((ai = (ai + 1)));
    }
    if (((ai + 18) >=560)) {
      return;
    }
    (void)(((cs)[ai] = 47));
    (void)(((cs)[(ai + 1)] = 99));
    (void)(((cs)[(ai + 2)] = 111));
    (void)(((cs)[(ai + 3)] = 109));
    (void)(((cs)[(ai + 4)] = 112));
    (void)(((cs)[(ai + 5)] = 105));
    (void)(((cs)[(ai + 6)] = 108));
    (void)(((cs)[(ai + 7)] = 101));
    (void)(((cs)[(ai + 8)] = 114));
    (void)(((cs)[(ai + 9)] = 47));
    (void)(((cs)[(ai + 10)] = 115));
    (void)(((cs)[(ai + 11)] = 114));
    (void)(((cs)[(ai + 12)] = 99));
    (void)(((cs)[(ai + 13)] = 47));
    (void)(((cs)[(ai + 14)] = 97));
    (void)(((cs)[(ai + 15)] = 115));
    (void)(((cs)[(ai + 16)] = 109));
    (void)(((cs)[(ai + 17)] = 0));
    if ((fmt_path_stat_kind(&((cs)[0])) ==1)) {
      int32_t nb2 = fmt_check_lib_bufs_n();
      if ((nb2 < 8)) {
        if ((fmt_check_lib_buf_store(nb2, &((cs)[0])) !=0)) {
          uint8_t * slot2 = fmt_check_lib_buf_at(nb2);
          if ((slot2 !=((uint8_t *)(0)))) {
            int32_t ni2 = (n)[0];
            (void)(xlang_ptr_slot_set(check_argv, ni2, &((g_fmt_lit_dash_L)[0])));
            (void)(xlang_ptr_slot_set(check_argv, (ni2 + 1), slot2));
            (void)(((n)[0] = (ni2 + 2)));
            (void)(fmt_check_lib_bufs_n_set((nb2 + 1)));
          }
        }
      }
    }
  }
  (void)(0);
  return;
}
int32_t driver_run_fmt(int32_t argc, uint8_t * argv) {
  (void)(fmt_user_ignore_count_set(0));
  (void)(driver_collect_mode_set(1));
  (void)(file_list_clear());
  int32_t fail_fast = 0;
  int32_t any_path = 0;
  int32_t failed = 0;
  int32_t formatted = 0;
  int32_t check_mode = 0;
  {
    int32_t i = 1;
    while ((i < argc)) {
      if ((argv !=((uint8_t *)(0)))) {
        uint8_t * a = xlang_ptr_slot_get(argv, i);
        if ((a !=((uint8_t *)(0)))) {
          if ((strcmp(a, &((g_fmt_lit_dash_check)[0])) ==0)) {
            (void)(driver_fmt_check_only_set(1));
            (void)((check_mode = 1));
          } else {
            if ((strcmp(a, &((g_fmt_lit_fail_fast)[0])) ==0)) {
              (void)((fail_fast = 1));
            } else {
              if ((strncmp(a, &((g_fmt_lit_ignore_eq)[0]), 9) ==0)) {
                (void)(parse_ignore_opt(a));
              } else {
                if (((a)[0] !=45)) {
                  (void)((any_path = 1));
                  (void)(collect_paths_from_arg(a));
                }
              }
            }
          }
        }
      }
      (void)((i = (i + 1)));
    }
  }
  if ((any_path ==0)) {
    uint8_t cwd[512] = {};
    {
      uint8_t * p = getcwd(&((cwd)[0]), 512);
      if ((p !=((uint8_t *)(0)))) {
        (void)(walk_dir_collect(&((cwd)[0])));
      }
    }
  }
  if ((fmt_file_list_n() ==0)) {
    {
      uint8_t * kind = &((g_fmt_lit_fmt_error)[0]);
      uint8_t * code = &((g_fmt_lit_fmt001)[0]);
      if ((any_path !=0)) {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, code, &((g_fmt_lit_no_x_paths)[0]), ((uint8_t *)(0))));
      } else {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, code, &((g_fmt_lit_no_x_cwd)[0]), ((uint8_t *)(0))));
      }
    }
    return 1;
  }
  {
    int32_t n = fmt_file_list_n();
    int32_t j = 0;
    while ((j < n)) {
      uint8_t * path = fmt_file_list_at(j);
      if ((path !=((uint8_t *)(0)))) {
        int32_t plen = 0;
        while ((plen < 512)) {
          if (((path)[plen] ==0)) {
            break;
          }
          (void)((plen = (plen + 1)));
        }
        int32_t rc = driver_fmt_one_file(path, plen);
        if ((rc !=0)) {
          (void)((failed = 1));
          if ((check_mode !=0)) {
            (void)(diag_report(path, 0, 0, &((g_fmt_lit_note)[0]), &((g_fmt_lit_needs_formatting)[0]), ((uint8_t *)(0))));
          }
          if ((fail_fast !=0)) {
            break;
          }
        } else {
          if ((check_mode ==0)) {
            (void)((formatted = (formatted + 1)));
          }
        }
      }
      (void)((j = (j + 1)));
    }
  }
  (void)(driver_fmt_check_only_set(0));
  (void)(file_list_clear());
  if ((failed !=0)) {
    if ((check_mode !=0)) {
      (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, &((g_fmt_lit_fmt_error)[0]), &((g_fmt_lit_fmt001)[0]), &((g_fmt_lit_found_not_formatted)[0]), ((uint8_t *)(0))));
      (void)(diag_report(((uint8_t *)(0)), 0, 0, &((g_fmt_lit_note)[0]), &((g_fmt_lit_run_xlang_fmt)[0]), ((uint8_t *)(0))));
      return 1;
    }
    return 1;
  }
  if ((check_mode ==0)) {
    if ((formatted > 0)) {
      {
        /* wave234 G.7: XLANG_FMT_VERBOSE via link_abi_getenv (not raw getenv). */
        uint8_t * ev = link_abi_getenv(&((g_fmt_lit_fmt_verbose_env)[0]));
        if ((ev !=((uint8_t *)(0)))) {
          (void)(diag_report(((uint8_t *)(0)), 0, 0, &((g_fmt_lit_info)[0]), &((g_fmt_lit_formatted_files)[0]), ((uint8_t *)(0))));
        }
      }
    }
  }
  return 0;
}
int32_t driver_run_compiler_check(int32_t argc, uint8_t * argv) {
  (void)(driver_collect_mode_set(2));
  (void)(file_list_clear());
  int32_t path_start = 1;
  int32_t fail_fast = 0;
  int32_t any_path = 0;
  int32_t failed = 0;
  if ((argc >=2)) {
    if ((argv !=((uint8_t *)(0)))) {
      uint8_t * a1 = xlang_ptr_slot_get(argv, 1);
      if ((a1 !=((uint8_t *)(0)))) {
        if ((strcmp(a1, &((g_fmt_lit_cmd_check)[0])) ==0)) {
          (void)((path_start = 2));
        }
      }
    }
  }
  (void)(check_init_user_lib_flags(argc, argv, path_start));
  {
    int32_t i = path_start;
    while ((i < argc)) {
      int32_t step = 1;
      if ((argv !=((uint8_t *)(0)))) {
        uint8_t * a = xlang_ptr_slot_get(argv, i);
        if ((a !=((uint8_t *)(0)))) {
          if ((strcmp(a, &((g_fmt_lit_fail_fast)[0])) ==0)) {
            (void)((fail_fast = 1));
          } else {
            if ((strncmp(a, &((g_fmt_lit_ignore_eq)[0]), 9) ==0)) {
              (void)(parse_ignore_opt(a));
            } else {
              if ((strcmp(a, &((g_fmt_lit_dash_L)[0])) ==0)) {
                (void)((step = 2));
              } else {
                if ((strcmp(a, &((g_fmt_lit_dash_I)[0])) ==0)) {
                  (void)((step = 2));
                } else {
                  if ((strcmp(a, &((g_fmt_lit_dash_o)[0])) ==0)) {
                    (void)((step = 2));
                  } else {
                    if ((strcmp(a, &((g_fmt_lit_backend)[0])) ==0)) {
                      (void)((step = 2));
                    } else {
                      if ((strcmp(a, &((g_fmt_lit_dash_O)[0])) ==0)) {
                        (void)((step = 2));
                      } else {
                        if (((a)[0] !=45)) {
                          (void)((any_path = 1));
                          (void)(collect_paths_from_arg(a));
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      (void)((i = (i + step)));
    }
  }
  if ((any_path ==0)) {
    (void)(check_collect_default_product_dirs());
  }
  if ((fmt_file_list_n() ==0)) {
    {
      uint8_t * kind = &((g_fmt_lit_check_error)[0]);
      uint8_t * code = &((g_fmt_lit_chk002)[0]);
      if ((any_path !=0)) {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, code, &((g_fmt_lit_no_x_paths)[0]), ((uint8_t *)(0))));
      } else {
        (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, kind, code, &((g_fmt_lit_no_x_cwd)[0]), ((uint8_t *)(0))));
      }
    }
    return 1;
  }
  {
    int32_t n = fmt_file_list_n();
    int32_t j = 0;
    while ((j < n)) {
      uint8_t * path = fmt_file_list_at(j);
      if ((path !=((uint8_t *)(0)))) {
        if ((check_one_file(path, argc, argv) !=0)) {
          (void)((failed = 1));
          if ((fail_fast !=0)) {
            break;
          }
        }
      }
      (void)((j = (j + 1)));
    }
  }
  (void)(file_list_clear());
  if ((failed !=0)) {
    return 1;
  }
  return 0;
}
