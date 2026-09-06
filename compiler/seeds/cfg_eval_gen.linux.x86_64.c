#include <stdint.h>
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "Generated code needs C11. Compile with -std=gnu11 or -std=c11."
#endif
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <xlang_io_cap.h>
#include <sys/uio.h>
#include <poll.h>
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
#include <stdio.h>
#ifndef __cplusplus
/* wave313 G.7: monofile dual WEAK polyfills → extern-only (n=29).
 * live STRONG = runtime/product .o (freestanding dual leave).
 * PLATFORM: SHARED freestanding dual leave. */
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

extern uint8_t *process_arg_c(int32_t i);

extern int32_t args_iter_count_c(void);

extern uint8_t *args_iter_at_c(int32_t i);

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
#include <stddef.h>
#include <sys/types.h>
void xlang_panic_(int has_msg, int msg_val);
extern int32_t lexer_cfg_strlen(uint8_t * s);
extern uint8_t lexer_cfg_tolower_c(uint8_t c);
extern void lexer_cfg_copy_cstr(uint8_t * dest, int32_t dest_sz, uint8_t * src);
extern int32_t lexer_cfg_range_eq_ci(uint8_t * buf, int32_t b, int32_t e, uint8_t * lit);
extern int32_t lexer_cfg_triple_contains_ci(uint8_t * buf, int32_t b, int32_t e, uint8_t * needle);
extern int32_t lexer_cfg_triple_has(uint8_t * triple, int32_t tlen, uint8_t * a, uint8_t * b);
extern void lexer_cfg_parse_triple_literals(uint8_t * triple, int32_t tlen, uint8_t * os_out, int32_t os_sz, uint8_t * arch_out, int32_t arch_sz);
extern uint8_t * lexer_cfg_effective_os_lit(void);
extern uint8_t * lexer_cfg_effective_arch_lit(void);
extern int32_t lexer_cfg_skip_ws(uint8_t * buf, int32_t p, int32_t end);
extern int32_t lexer_cfg_prefix4(uint8_t * buf, int32_t p, int32_t end, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3);
extern int32_t lexer_cfg_is_ident_char(uint8_t c);
extern int32_t lexer_cfg_scan_delim(uint8_t c, int32_t depth);
extern int32_t lexer_cfg_buf_eq_at(uint8_t * buf, int32_t p, int32_t end, uint8_t c);
extern int32_t lexer_cfg_eval_all(uint8_t * buf, int32_t b, int32_t end);
extern int32_t lexer_cfg_eval_not(uint8_t * buf, int32_t b, int32_t end);
extern int32_t lexer_cfg_eval_target_os(uint8_t * buf, int32_t p, int32_t end);
extern int32_t lexer_cfg_eval_target_arch(uint8_t * buf, int32_t p, int32_t end);
extern int32_t lexer_cfg_eval_freestanding_flag(uint8_t * buf, int32_t p, int32_t end);
extern int32_t lexer_cfg_eval_expr_range(uint8_t * buf, int32_t b, int32_t end);
extern int32_t lexer_cfg_eval_expr_c(uint8_t * start, int32_t len);
extern void lexer_cfg_apply_compile_target_from_triple(uint8_t * triple, int32_t len);
extern void lexer_cfg_reset_compile_target(void);
extern void lexer_cfg_set_freestanding(int32_t v);
static uint8_t g_cfg_os_override[32];
static uint8_t g_cfg_arch_override[32];
static int32_t g_cfg_has_target_override;
static int32_t g_cfg_freestanding;
static void init_globals(void) {
  g_cfg_has_target_override = 0;
  g_cfg_freestanding = 0;
}
extern uint8_t * cfg_host_os_lit(void);
extern uint8_t * cfg_host_arch_lit(void);
int32_t lexer_cfg_strlen(uint8_t * s) {
  int32_t n = 0;
  if ((s ==0)) {
    return 0;
  }
  while (((s)[n] !=0)) {
    (void)((n = (n + 1)));
  }
  return n;
}
uint8_t lexer_cfg_tolower_c(uint8_t c) {
  if ((c < 65)) {
    return c;
  }
  if ((c > 90)) {
    return c;
  }
  return ((uint8_t)((c + 32)));
}
void lexer_cfg_copy_cstr(uint8_t * dest, int32_t dest_sz, uint8_t * src) {
  int32_t i = 0;
  if ((dest ==0)) {
    return;
  }
  if ((dest_sz <=0)) {
    return;
  }
  if ((src ==0)) {
    return;
  }
  while ((i < (dest_sz - 1))) {
    if (((src)[i] ==0)) {
      break;
    }
    (void)(((dest)[i] = (src)[i]));
    (void)((i = (i + 1)));
  }
  (void)(((dest)[i] = 0));
}
int32_t lexer_cfg_range_eq_ci(uint8_t * buf, int32_t b, int32_t e, uint8_t * lit) {
  int32_t blen = (e - b);
  int32_t llen = lexer_cfg_strlen(lit);
  int32_t i = 0;
  if ((buf ==0)) {
    return 0;
  }
  if ((lit ==0)) {
    return 0;
  }
  if ((blen !=llen)) {
    return 0;
  }
  while ((i < blen)) {
    uint8_t ca = lexer_cfg_tolower_c((buf)[(b + i)]);
    uint8_t cb = lexer_cfg_tolower_c((lit)[i]);
    if ((ca !=cb)) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t lexer_cfg_triple_contains_ci(uint8_t * buf, int32_t b, int32_t e, uint8_t * needle) {
  int32_t nlen = lexer_cfg_strlen(needle);
  int32_t i = b;
  if ((buf ==0)) {
    return 0;
  }
  if ((needle ==0)) {
    return 0;
  }
  if ((nlen <=0)) {
    return 0;
  }
  if (((e - b) < nlen)) {
    return 0;
  }
  while (((i + nlen) <=e)) {
    int32_t j = 0;
    int32_t ok = 1;
    while ((j < nlen)) {
      uint8_t a = lexer_cfg_tolower_c((buf)[(i + j)]);
      uint8_t nb = lexer_cfg_tolower_c((needle)[j]);
      if ((a !=nb)) {
        (void)((ok = 0));
        break;
      }
      (void)((j = (j + 1)));
    }
    if ((ok !=0)) {
      return 1;
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t lexer_cfg_triple_has(uint8_t * triple, int32_t tlen, uint8_t * a, uint8_t * b) {
  if ((lexer_cfg_triple_contains_ci(triple, 0, tlen, a) !=0)) {
    return 1;
  }
  if ((lexer_cfg_triple_contains_ci(triple, 0, tlen, b) !=0)) {
    return 1;
  }
  return 0;
}
void lexer_cfg_parse_triple_literals(uint8_t * triple, int32_t tlen, uint8_t * os_out, int32_t os_sz, uint8_t * arch_out, int32_t arch_sz) {
  uint8_t lit_linux[6] = {108, 105, 110, 117, 120, 0};
  uint8_t lit_macos[6] = {109, 97, 99, 111, 115, 0};
  uint8_t lit_darwin[7] = {100, 97, 114, 119, 105, 110, 0};
  uint8_t lit_windows[8] = {119, 105, 110, 100, 111, 119, 115, 0};
  uint8_t lit_freebsd[8] = {102, 114, 101, 101, 98, 115, 100, 0};
  uint8_t lit_win32[6] = {119, 105, 110, 51, 50, 0};
  uint8_t lit_aarch64[8] = {97, 97, 114, 99, 104, 54, 52, 0};
  uint8_t lit_arm64[6] = {97, 114, 109, 54, 52, 0};
  uint8_t lit_x86_64[7] = {120, 56, 54, 95, 54, 52, 0};
  uint8_t lit_amd64[6] = {97, 109, 100, 54, 52, 0};
  uint8_t lit_riscv64[8] = {114, 105, 115, 99, 118, 54, 52, 0};
  if ((os_out ==0)) {
    return;
  }
  if ((os_sz <=0)) {
    return;
  }
  if ((arch_out ==0)) {
    return;
  }
  if ((arch_sz <=0)) {
    return;
  }
  (void)(lexer_cfg_copy_cstr(os_out, os_sz, cfg_host_os_lit()));
  (void)(lexer_cfg_copy_cstr(arch_out, arch_sz, cfg_host_arch_lit()));
  if ((triple ==0)) {
    return;
  }
  if ((tlen <=0)) {
    return;
  }
  if ((lexer_cfg_triple_contains_ci(triple, 0, tlen, &((lit_linux)[0])) !=0)) {
    (void)(lexer_cfg_copy_cstr(os_out, os_sz, &((lit_linux)[0])));
  } else {
    if ((lexer_cfg_triple_has(triple, tlen, &((lit_darwin)[0]), &((lit_macos)[0])) !=0)) {
      (void)(lexer_cfg_copy_cstr(os_out, os_sz, &((lit_macos)[0])));
    } else {
      if ((lexer_cfg_triple_contains_ci(triple, 0, tlen, &((lit_freebsd)[0])) !=0)) {
        (void)(lexer_cfg_copy_cstr(os_out, os_sz, &((lit_freebsd)[0])));
      } else {
        if ((lexer_cfg_triple_has(triple, tlen, &((lit_windows)[0]), &((lit_win32)[0])) !=0)) {
          (void)(lexer_cfg_copy_cstr(os_out, os_sz, &((lit_windows)[0])));
        }
      }
    }
  }
  if ((lexer_cfg_triple_has(triple, tlen, &((lit_aarch64)[0]), &((lit_arm64)[0])) !=0)) {
    (void)(lexer_cfg_copy_cstr(arch_out, arch_sz, &((lit_aarch64)[0])));
  } else {
    if ((lexer_cfg_triple_has(triple, tlen, &((lit_x86_64)[0]), &((lit_amd64)[0])) !=0)) {
      (void)(lexer_cfg_copy_cstr(arch_out, arch_sz, &((lit_x86_64)[0])));
    } else {
      if ((lexer_cfg_triple_contains_ci(triple, 0, tlen, &((lit_riscv64)[0])) !=0)) {
        (void)(lexer_cfg_copy_cstr(arch_out, arch_sz, &((lit_riscv64)[0])));
      }
    }
  }
  (void)(0);
  return;
}
uint8_t * lexer_cfg_effective_os_lit(void) {
  if ((g_cfg_has_target_override ==0)) {
    return cfg_host_os_lit();
  }
  if (((g_cfg_os_override)[0] ==0)) {
    return cfg_host_os_lit();
  }
  return &((g_cfg_os_override)[0]);
}
uint8_t * lexer_cfg_effective_arch_lit(void) {
  if ((g_cfg_has_target_override ==0)) {
    return cfg_host_arch_lit();
  }
  if (((g_cfg_arch_override)[0] ==0)) {
    return cfg_host_arch_lit();
  }
  return &((g_cfg_arch_override)[0]);
}
int32_t lexer_cfg_skip_ws(uint8_t * buf, int32_t p, int32_t end) {
  while ((p < end)) {
    uint8_t c = (buf)[p];
    int32_t is_ws = 0;
    if ((c ==32)) {
      (void)((is_ws = 1));
    }
    if ((c ==9)) {
      (void)((is_ws = 1));
    }
    if ((c ==10)) {
      (void)((is_ws = 1));
    }
    if ((c ==13)) {
      (void)((is_ws = 1));
    }
    if ((is_ws ==0)) {
      break;
    }
    (void)((p = (p + 1)));
  }
  return p;
}
int32_t lexer_cfg_prefix4(uint8_t * buf, int32_t p, int32_t end, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3) {
  if (((p + 4) > end)) {
    return 0;
  }
  if (((buf)[p] !=c0)) {
    return 0;
  }
  if (((buf)[(p + 1)] !=c1)) {
    return 0;
  }
  if (((buf)[(p + 2)] !=c2)) {
    return 0;
  }
  if (((buf)[(p + 3)] !=c3)) {
    return 0;
  }
  return 1;
}
int32_t lexer_cfg_is_ident_char(uint8_t c) {
  if ((c ==95)) {
    return 1;
  }
  if ((c < 48)) {
    return 0;
  }
  if ((c > 122)) {
    return 0;
  }
  if ((c <=57)) {
    return 1;
  }
  if ((c < 65)) {
    return 0;
  }
  if ((c <=90)) {
    return 1;
  }
  if ((c < 97)) {
    return 0;
  }
  return 1;
}
int32_t lexer_cfg_scan_delim(uint8_t c, int32_t depth) {
  if ((c ==41)) {
    if ((depth ==0)) {
      return 1;
    }
    return 2;
  }
  if ((c ==44)) {
    if ((depth ==0)) {
      return 1;
    }
    return 3;
  }
  return 0;
}
int32_t lexer_cfg_buf_eq_at(uint8_t * buf, int32_t p, int32_t end, uint8_t c) {
  if ((p >=end)) {
    return 0;
  }
  if (((buf)[p] ==c)) {
    return 1;
  }
  return 0;
}
int32_t lexer_cfg_eval_all(uint8_t * buf, int32_t b, int32_t end) {
  int32_t p = (b + 4);
  while ((p < end)) {
    int32_t part = 0;
    int32_t depth = 0;
    (void)((p = lexer_cfg_skip_ws(buf, p, end)));
    if ((p >=end)) {
      break;
    }
    if (((buf)[p] ==41)) {
      return 1;
    }
    (void)((part = p));
    (void)((depth = 0));
    while ((p < end)) {
      int32_t sd = lexer_cfg_scan_delim((buf)[p], depth);
      if (((buf)[p] ==40)) {
        (void)((depth = (depth + 1)));
        (void)((p = (p + 1)));
        continue;
      }
      if ((sd ==1)) {
        break;
      }
      if ((sd ==2)) {
        (void)((depth = (depth - 1)));
        (void)((p = (p + 1)));
        continue;
      }
      if ((sd ==3)) {
        (void)((p = (p + 1)));
        continue;
      }
      (void)((p = (p + 1)));
    }
    if ((lexer_cfg_eval_expr_range(buf, part, p) ==0)) {
      return 0;
    }
    if ((lexer_cfg_buf_eq_at(buf, p, end, 41) !=0)) {
      return 1;
    }
  }
  return 1;
}
int32_t lexer_cfg_eval_not(uint8_t * buf, int32_t b, int32_t end) {
  int32_t inner = (b + 4);
  int32_t close = inner;
  int32_t depth = 1;
  while ((close < end)) {
    if ((depth <=0)) {
      break;
    }
    if (((buf)[close] ==40)) {
      (void)((depth = (depth + 1)));
    } else {
      if (((buf)[close] ==41)) {
        (void)((depth = (depth - 1)));
      }
    }
    if ((depth > 0)) {
      (void)((close = (close + 1)));
    }
  }
  if ((lexer_cfg_eval_expr_range(buf, inner, close) !=0)) {
    return 0;
  }
  return 1;
}
int32_t lexer_cfg_eval_target_os(uint8_t * buf, int32_t p, int32_t end) {
  uint8_t lit_target_os[10] = {116, 97, 114, 103, 101, 116, 95, 111, 115, 0};
  if (((p + 9) > end)) {
    return -(1);
  }
  if ((lexer_cfg_range_eq_ci(buf, p, (p + 9), &((lit_target_os)[0])) ==0)) {
    return -(1);
  }
  (void)((p = (p + 9)));
  (void)((p = lexer_cfg_skip_ws(buf, p, end)));
  if ((p >=end)) {
    return 0;
  }
  if (((buf)[p] !=61)) {
    return 0;
  }
  (void)((p = (p + 1)));
  if ((p < end)) {
    if (((buf)[p] ==61)) {
      (void)((p = (p + 1)));
    }
  }
  (void)((p = lexer_cfg_skip_ws(buf, p, end)));
  if ((p >=end)) {
    return 0;
  }
  if (((buf)[p] !=34)) {
    return 0;
  }
  (void)((p = (p + 1)));
  int32_t lit = p;
  while ((p < end)) {
    if (((buf)[p] ==34)) {
      break;
    }
    (void)((p = (p + 1)));
  }
  if ((lexer_cfg_range_eq_ci(buf, lit, p, lexer_cfg_effective_os_lit()) !=0)) {
    return 1;
  }
  return 0;
}
int32_t lexer_cfg_eval_target_arch(uint8_t * buf, int32_t p, int32_t end) {
  uint8_t lit_target_arch[12] = {116, 97, 114, 103, 101, 116, 95, 97, 114, 99, 104, 0};
  if (((p + 11) > end)) {
    return -(1);
  }
  if ((lexer_cfg_range_eq_ci(buf, p, (p + 11), &((lit_target_arch)[0])) ==0)) {
    return -(1);
  }
  (void)((p = (p + 11)));
  (void)((p = lexer_cfg_skip_ws(buf, p, end)));
  if ((p >=end)) {
    return 0;
  }
  if (((buf)[p] !=61)) {
    return 0;
  }
  (void)((p = (p + 1)));
  if ((p < end)) {
    if (((buf)[p] ==61)) {
      (void)((p = (p + 1)));
    }
  }
  (void)((p = lexer_cfg_skip_ws(buf, p, end)));
  if ((p >=end)) {
    return 0;
  }
  if (((buf)[p] !=34)) {
    return 0;
  }
  (void)((p = (p + 1)));
  int32_t lit = p;
  while ((p < end)) {
    if (((buf)[p] ==34)) {
      break;
    }
    (void)((p = (p + 1)));
  }
  if ((lexer_cfg_range_eq_ci(buf, lit, p, lexer_cfg_effective_arch_lit()) !=0)) {
    return 1;
  }
  return 0;
}
int32_t lexer_cfg_eval_freestanding_flag(uint8_t * buf, int32_t p, int32_t end) {
  uint8_t lit_freestanding[13] = {102, 114, 101, 101, 115, 116, 97, 110, 100, 105, 110, 103, 0};
  int32_t q = p;
  while ((q < end)) {
    uint8_t c = (buf)[q];
    if ((lexer_cfg_is_ident_char(c) ==0)) {
      break;
    }
    (void)((q = (q + 1)));
  }
  if ((lexer_cfg_range_eq_ci(buf, p, q, &((lit_freestanding)[0])) !=0)) {
    return g_cfg_freestanding;
  }
  return 0;
}
int32_t lexer_cfg_eval_expr_range(uint8_t * buf, int32_t b, int32_t end) {
  int32_t p = lexer_cfg_skip_ws(buf, b, end);
  int32_t r = 0;
  if ((p >=end)) {
    return 0;
  }
  if ((lexer_cfg_prefix4(buf, p, end, 97, 108, 108, 40) !=0)) {
    return lexer_cfg_eval_all(buf, p, end);
  }
  if ((lexer_cfg_prefix4(buf, p, end, 110, 111, 116, 40) !=0)) {
    return lexer_cfg_eval_not(buf, p, end);
  }
  (void)((r = lexer_cfg_eval_target_os(buf, p, end)));
  if ((r !=-(1))) {
    return r;
  }
  (void)((r = lexer_cfg_eval_target_arch(buf, p, end)));
  if ((r !=-(1))) {
    return r;
  }
  return lexer_cfg_eval_freestanding_flag(buf, p, end);
}
int32_t lexer_cfg_eval_expr_c(uint8_t * start, int32_t len) {
  if ((start ==0)) {
    return 0;
  }
  if ((len <=0)) {
    return 0;
  }
  if ((lexer_cfg_eval_expr_range(start, 0, len) !=0)) {
    return 1;
  }
  return 0;
}
void lexer_cfg_apply_compile_target_from_triple(uint8_t * triple, int32_t len) {
  (void)(lexer_cfg_parse_triple_literals(triple, len, &((g_cfg_os_override)[0]), 32, &((g_cfg_arch_override)[0]), 32));
  (void)((g_cfg_has_target_override = 1));
}
void lexer_cfg_reset_compile_target(void) {
  (void)((g_cfg_has_target_override = 0));
  (void)(((g_cfg_os_override)[0] = 0));
  (void)(((g_cfg_arch_override)[0] = 0));
}
void lexer_cfg_set_freestanding(int32_t v) {
  (void)((g_cfg_freestanding = v));
}
