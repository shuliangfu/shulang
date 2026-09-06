#include <xlang_weak.h>
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
#include <stdio.h>
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
#include <stddef.h>
#include <sys/types.h>
void xlang_panic_(int has_msg, int msg_val);
extern int32_t driver_env_flag_truthy(uint8_t * name);
extern int32_t driver_env_nonnull(uint8_t * name);
extern int64_t driver_parse_u32_cstr(uint8_t * s);
extern int32_t * driver_check_only_flag_slot(void);
extern int32_t * driver_check_diag_emitted_flag_slot(void);
extern int32_t * driver_freestanding_flag_slot(void);
extern int32_t * driver_sanitize_address_flag_slot(void);
extern int32_t * driver_fmt_check_only_flag_slot(void);
extern int32_t * driver_x_pipeline_skip_typeck_flag_slot(void);
extern int32_t * driver_x_pipeline_skip_codegen_flag_slot(void);
extern int32_t * driver_skip_codegen_dep_0_flag_slot(void);
extern int32_t * driver_large_stack_thread_flag_slot(void);
extern void driver_current_dep_path_store(uint8_t * path);
extern uint8_t * driver_current_dep_path_load(void);
extern void driver_pipeline_entry_source_len_store(int64_t len);
extern void driver_path_last_preprocess_len_store(int64_t len);
extern int64_t driver_path_last_preprocess_len(void);
extern uint8_t * driver_path_read_preprocess_malloc(uint8_t * path);
extern void driver_fmt_check_only_set(int32_t v);
extern void driver_large_stack_thread_mark(int32_t on);
extern int32_t driver_is_large_stack_thread(void);
extern void driver_check_only_set(int32_t v);
extern int32_t driver_skip_codegen_dep_0_get(void);
extern int32_t driver_x_pipeline_skip_typeck_get(void);
extern int32_t driver_freestanding_get(void);
extern int32_t driver_check_only_get(void);
extern void driver_set_current_dep_path_for_codegen(uint8_t * path);
extern int32_t driver_argv_is_D_alone(uint8_t * arg);
extern int32_t driver_argv_is_D_inline(uint8_t * arg);
extern int32_t driver_argv_is_target_flag(uint8_t * arg);
extern int32_t driver_argv_is_value_skip_flag(uint8_t * arg);
extern int32_t driver_cstr_contains_bytes(uint8_t * hay, uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t n4, int32_t nlen);
extern int32_t driver_target_arg_os_kind(uint8_t * target);
extern void driver_x_pipeline_skip_typeck_set(int32_t v);
extern void driver_x_pipeline_skip_codegen_set(int32_t v);
extern void driver_sanitize_address_set(int32_t v);
extern int32_t driver_x_pipeline_skip_codegen_get(void);
extern void driver_skip_codegen_dep_0_set(int32_t v);
extern void driver_freestanding_set(int32_t v);
extern void driver_check_diag_emitted_note(void);
extern void driver_check_diag_emitted_reset(void);
extern int32_t driver_fmt_check_only_get(void);
extern int32_t driver_check_diag_emitted_get(void);
extern int32_t driver_abi_append_i64(uint8_t * dst, int32_t cap, int32_t at, int64_t val);
extern void driver_print_check_ok(uint8_t * input_path);
extern double compile_phase_now_sec(void);
extern void driver_run_fn_on_current_large_stack(uint8_t * fn, uint8_t * arg);
extern int32_t driver_compile_phase_index_ok(int32_t phase);
extern int32_t driver_compile_phase_timing_enabled(void);
extern double driver_compile_phase_acc_ms_get(int32_t phase);
extern void driver_compile_phase_timing_clear(void);
extern void driver_compile_phase_timing_begin(int32_t phase);
extern void driver_compile_phase_timing_end(int32_t phase);
extern void driver_compile_phase_timing_flush(void);
extern int32_t driver_ascii_toupper(int32_t c);
extern int32_t driver_typeck_skip_large_entry(void);
extern int32_t driver_sanitize_address_get(void);
extern int32_t driver_typeck_force_c_enabled(void);
extern int32_t driver_asm_build_skip_typeck(void);
extern int32_t driver_asm_entry_emit_heavy(void);
extern int32_t driver_pipeline_no_large_stack_env(void);
extern int32_t driver_asm_entry_module_only_from_env(void);
extern int32_t driver_asm_parse_metric_only_from_env(void);
extern int32_t driver_pipeline_entry_source_len_i32(void);
extern void driver_defines_set_at(uint8_t * defines, int32_t i, uint8_t * s);
extern int64_t driver_stack_limit_want_bytes(void);
extern void driver_bump_stack_limit(void);
extern void driver_set_pipeline_entry_source_len(int64_t len);
extern int32_t compile_phase_timing_enabled(void);
extern uint8_t * driver_os_define_lit(int32_t kind);
extern void driver_pipeline_fail_code(int32_t rc, uint8_t * path);
extern void driver_print_x_smoke_summary(uint8_t * module, int64_t codegen_len);
extern int32_t driver_peek_source_file(uint8_t * path, uint8_t * content, int64_t cap);
extern uint8_t * driver_get_current_dep_path_for_codegen(void);
extern int32_t driver_argv_collect_defines(int32_t argc, uint8_t * argv, uint8_t * defines, int32_t max_defines);
extern int32_t driver_source_scan_top_level_import(uint8_t * src, int64_t src_len);
extern int32_t driver_source_has_top_level_import(uint8_t * src, int64_t src_len);
extern int32_t driver_source_has_top_level_import_path(uint8_t * path);
extern void driver_run_thread_on_large_stack(uint8_t * fn, uint8_t * arg);
extern void driver_run_on_large_stack_pthread(uint8_t * fn, uint8_t * arg);
extern int64_t driver_pipeline_entry_source_len_load_and_maybe_debug(void);
extern int64_t driver_pipeline_entry_source_len(void);
static int32_t g_driver_check_only_flag[1] = {0};
static int32_t g_driver_check_diag_emitted_flag[1] = {0};
static int32_t g_driver_freestanding_flag[1] = {0};
static int32_t g_driver_sanitize_address_flag[1] = {0};
static int32_t g_driver_fmt_check_only_flag[1] = {0};
static int32_t g_driver_x_pipeline_skip_typeck_flag[1] = {0};
static int32_t g_driver_x_pipeline_skip_codegen_flag[1] = {0};
static int32_t g_driver_skip_codegen_dep_0_flag[1] = {0};
static int32_t g_driver_on_large_stack_thread_flag[1] = {0};
static uint8_t g_driver_current_dep_path_buf[128];
static uint8_t * g_driver_current_dep_path;
static int64_t g_pipeline_entry_source_len[1] = {0};
static int64_t g_driver_path_last_preprocess_len[1] = {0};
static double g_compile_phase_acc_ms[3] = {0.0, 0.0, 0.0};
static double g_compile_phase_start_sec[3] = {0.0, 0.0, 0.0};
static int32_t g_compile_phase_active[3] = {0, 0, 0};
static void init_globals(void) {
  g_driver_current_dep_path_buf[0] = 0;
  g_driver_current_dep_path = ((uint8_t *)(0));
}
/* wave228 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv). */
extern uint8_t * link_abi_getenv(uint8_t * name);
extern double xlang_driver_wall_clock_sec(void);
extern void xlang_driver_call_fn_void_arg(uint8_t * fn, uint8_t * arg);
extern void xlang_driver_bump_stack_limit(int64_t want_bytes);
extern uint8_t * xlang_driver_path_read_preprocess_malloc(uint8_t * path);
extern void diag_report(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * msg, uint8_t * detail);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern int32_t driver_diag_append_cstr(uint8_t * dst, int32_t cap, int32_t at, uint8_t * src);
extern int32_t driver_diag_append_i32(uint8_t * dst, int32_t cap, int32_t at, int32_t val);
extern void xlang_ptr_slot_set(uint8_t * arr, int32_t i, uint8_t * p);
int32_t driver_env_flag_truthy(uint8_t * name) {
  {
    /* wave228 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
    uint8_t * e = link_abi_getenv(name);
    if ((e ==((uint8_t *)(0)))) {
      return 0;
    }
    if (((e)[0] ==0)) {
      return 0;
    }
    if (((e)[0] ==48)) {
      return 0;
    }
    return 1;
  }
  return 0;
}
int32_t driver_env_nonnull(uint8_t * name) {
  {
    /* wave228 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
    uint8_t * e = link_abi_getenv(name);
    if ((e ==((uint8_t *)(0)))) {
      return 0;
    }
    return 1;
  }
  return 0;
}
int64_t driver_parse_u32_cstr(uint8_t * s) {
  if ((s ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if (((s)[0] ==0)) {
    return (0 - 1);
  }
  int64_t n = 0;
  int32_t i = 0;
  while ((i < 20)) {
    int32_t c = ((int32_t)((s)[i]));
    if (((s)[i] ==0)) {
      break;
    }
    if ((c < 48)) {
      return (0 - 1);
    }
    if ((c > 57)) {
      return (0 - 1);
    }
    (void)((n = ((n * 10) + ((int64_t)((c - 48))))));
    (void)((i = (i + 1)));
  }
  if ((i ==0)) {
    return (0 - 1);
  }
  return n;
}
extern int32_t driver_check_quiet_ok_get(void);
extern uint8_t * driver_argv_at(uint8_t * argv, int32_t i);
extern uint8_t * xlang_cstr_offset(uint8_t * s, int32_t off);
extern int32_t xlang_driver_argv_append_uname(uint8_t * defines, int32_t ndefines, int32_t max_defines);
extern int32_t driver_get_module_num_funcs(uint8_t * m);
extern int32_t driver_get_module_main_func_index(uint8_t * m);
extern int32_t xlang_read_file_into_path(uint8_t * path, uint8_t * buf, int64_t cap);
extern void free(uint8_t * p);
extern int32_t bootstrap_nostdlib_pthread_is_stub(void);
extern void xlang_driver_run_thread_on_large_stack_pthread(uint8_t * fn, uint8_t * arg);
int32_t * driver_check_only_flag_slot(void) {
  return &((g_driver_check_only_flag)[0]);
}
int32_t * driver_check_diag_emitted_flag_slot(void) {
  return &((g_driver_check_diag_emitted_flag)[0]);
}
int32_t * driver_freestanding_flag_slot(void) {
  return &((g_driver_freestanding_flag)[0]);
}
int32_t * driver_sanitize_address_flag_slot(void) {
  return &((g_driver_sanitize_address_flag)[0]);
}
int32_t * driver_fmt_check_only_flag_slot(void) {
  return &((g_driver_fmt_check_only_flag)[0]);
}
int32_t * driver_x_pipeline_skip_typeck_flag_slot(void) {
  return &((g_driver_x_pipeline_skip_typeck_flag)[0]);
}
int32_t * driver_x_pipeline_skip_codegen_flag_slot(void) {
  return &((g_driver_x_pipeline_skip_codegen_flag)[0]);
}
int32_t * driver_skip_codegen_dep_0_flag_slot(void) {
  return &((g_driver_skip_codegen_dep_0_flag)[0]);
}
int32_t * driver_large_stack_thread_flag_slot(void) {
  return &((g_driver_on_large_stack_thread_flag)[0]);
}
void driver_current_dep_path_store(uint8_t * path) {
  int32_t i;
  if (!path || path[0] == 0) {
    g_driver_current_dep_path_buf[0] = 0;
    g_driver_current_dep_path = 0;
    return;
  }
  i = 0;
  while (i < 127) {
    uint8_t c = path[i];
    g_driver_current_dep_path_buf[i] = c;
    if (c == 0)
      break;
    i = i + 1;
  }
  g_driver_current_dep_path_buf[127] = 0;
  g_driver_current_dep_path = &g_driver_current_dep_path_buf[0];
}
uint8_t * driver_current_dep_path_load(void) {
  return &g_driver_current_dep_path_buf[0];
}
void driver_pipeline_entry_source_len_store(int64_t len) {
  (void)(((g_pipeline_entry_source_len)[0] = len));
}
void driver_path_last_preprocess_len_store(int64_t len) {
  (void)(((g_driver_path_last_preprocess_len)[0] = len));
}
int64_t driver_path_last_preprocess_len(void) {
  return (g_driver_path_last_preprocess_len)[0];
}
uint8_t * driver_path_read_preprocess_malloc(uint8_t * path) {
  return xlang_driver_path_read_preprocess_malloc(path);
  return ((uint8_t *)(0));
}
void driver_fmt_check_only_set(int32_t v) {
  {
    int32_t * p = driver_fmt_check_only_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
void driver_large_stack_thread_mark(int32_t on) {
  {
    int32_t * p = driver_large_stack_thread_flag_slot();
    (void)(((p)[0] = on));
  }
  (void)(0);
  return;
}
int32_t driver_is_large_stack_thread(void) {
  {
    int32_t * p = driver_large_stack_thread_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
void driver_check_only_set(int32_t v) {
  {
    int32_t * p = driver_check_only_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
int32_t driver_skip_codegen_dep_0_get(void) {
  {
    int32_t * p = driver_skip_codegen_dep_0_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t driver_x_pipeline_skip_typeck_get(void) {
  {
    int32_t * p = driver_x_pipeline_skip_typeck_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t driver_freestanding_get(void) {
  {
    int32_t * p = driver_freestanding_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t driver_check_only_get(void) {
  {
    int32_t * p = driver_check_only_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
void driver_set_current_dep_path_for_codegen(uint8_t * path) {
  (void)(driver_current_dep_path_store(path));
}
int32_t driver_argv_is_D_alone(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((arg)[0] !=45)) {
    return 0;
  }
  if (((arg)[1] !=68)) {
    return 0;
  }
  if (((arg)[2] !=0)) {
    return 0;
  }
  return 1;
  return 0;
}
int32_t driver_argv_is_D_inline(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((arg)[0] !=45)) {
    return 0;
  }
  if (((arg)[1] !=68)) {
    return 0;
  }
  if (((arg)[2] ==0)) {
    return 0;
  }
  return 1;
  return 0;
}
int32_t driver_argv_is_target_flag(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((arg)[0] !=45)) {
    return 0;
  }
  if (((arg)[1] !=116)) {
    return 0;
  }
  if (((arg)[2] !=97)) {
    return 0;
  }
  if (((arg)[3] !=114)) {
    return 0;
  }
  if (((arg)[4] !=103)) {
    return 0;
  }
  if (((arg)[5] !=101)) {
    return 0;
  }
  if (((arg)[6] !=116)) {
    return 0;
  }
  if (((arg)[7] !=0)) {
    return 0;
  }
  return 1;
  return 0;
}
int32_t driver_argv_is_value_skip_flag(uint8_t * arg) {
  if ((arg ==((uint8_t *)(0)))) {
    return 0;
  }
  if (((arg)[0] !=45)) {
    return 0;
  }
  if (((arg)[1] ==111)) {
    if (((arg)[2] ==0)) {
      return 1;
    }
  }
  if (((arg)[1] ==76)) {
    if (((arg)[2] ==0)) {
      return 1;
    }
  }
  if (((arg)[1] ==79)) {
    if (((arg)[2] ==0)) {
      return 1;
    }
  }
  if (((arg)[1] ==98)) {
    if (((arg)[2] ==97)) {
      if (((arg)[3] ==99)) {
        if (((arg)[4] ==107)) {
          if (((arg)[5] ==101)) {
            if (((arg)[6] ==110)) {
              if (((arg)[7] ==100)) {
                if (((arg)[8] ==0)) {
                  return 1;
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
int32_t driver_cstr_contains_bytes(uint8_t * hay, uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t n4, int32_t nlen) {
  if ((hay ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((nlen <=0)) {
    return 0;
  }
  {
    int32_t i = 0;
    while ((i < 4096)) {
      if (((hay)[i] ==0)) {
        return 0;
      }
      if (((hay)[i] ==n0)) {
        if ((nlen ==1)) {
          return 1;
        }
        if (((hay)[(i + 1)] ==n1)) {
          if ((nlen ==2)) {
            return 1;
          }
          if (((hay)[(i + 2)] ==n2)) {
            if ((nlen ==3)) {
              return 1;
            }
            if (((hay)[(i + 3)] ==n3)) {
              if ((nlen ==4)) {
                return 1;
              }
              if (((hay)[(i + 4)] ==n4)) {
                return 1;
              }
            }
          }
        }
      }
      (void)((i = (i + 1)));
    }
  }
  return 0;
}
int32_t driver_target_arg_os_kind(uint8_t * target) {
  if ((target ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((driver_cstr_contains_bytes(target, 108, 105, 110, 117, 120, 5) !=0)) {
    return 1;
  }
  if ((driver_cstr_contains_bytes(target, 100, 97, 114, 119, 105, 5) !=0)) {
    return 2;
  }
  if ((driver_cstr_contains_bytes(target, 97, 112, 112, 108, 101, 5) !=0)) {
    return 2;
  }
  if ((driver_cstr_contains_bytes(target, 102, 114, 101, 101, 98, 5) !=0)) {
    return 3;
  }
  if ((driver_cstr_contains_bytes(target, 119, 105, 110, 100, 111, 5) !=0)) {
    return 4;
  }
  return 0;
}
void driver_x_pipeline_skip_typeck_set(int32_t v) {
  {
    int32_t * p = driver_x_pipeline_skip_typeck_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
void driver_x_pipeline_skip_codegen_set(int32_t v) {
  {
    int32_t * p = driver_x_pipeline_skip_codegen_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
void driver_sanitize_address_set(int32_t v) {
  {
    int32_t * p = driver_sanitize_address_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
int32_t driver_x_pipeline_skip_codegen_get(void) {
  {
    int32_t * p = driver_x_pipeline_skip_codegen_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
void driver_skip_codegen_dep_0_set(int32_t v) {
  {
    int32_t * p = driver_skip_codegen_dep_0_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
void driver_freestanding_set(int32_t v) {
  {
    int32_t * p = driver_freestanding_flag_slot();
    (void)(((p)[0] = v));
  }
  (void)(0);
  return;
}
void driver_check_diag_emitted_note(void) {
  {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    (void)(((p)[0] = 1));
  }
  (void)(0);
  return;
}
void driver_check_diag_emitted_reset(void) {
  {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    (void)(((p)[0] = 0));
  }
  (void)(0);
  return;
}
int32_t driver_fmt_check_only_get(void) {
  {
    int32_t * p = driver_fmt_check_only_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t driver_check_diag_emitted_get(void) {
  {
    int32_t * p = driver_check_diag_emitted_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t driver_abi_append_i64(uint8_t * dst, int32_t cap, int32_t at, int64_t val) {
  {
    int32_t d0 = 0;
    int32_t d1 = 0;
    int32_t d2 = 0;
    int32_t d3 = 0;
    int32_t d4 = 0;
    int32_t d5 = 0;
    int32_t d6 = 0;
    int32_t d7 = 0;
    int32_t d8 = 0;
    int32_t d9 = 0;
    int32_t d10 = 0;
    int32_t d11 = 0;
    int32_t d12 = 0;
    int32_t d13 = 0;
    int32_t d14 = 0;
    int32_t d15 = 0;
    int32_t d16 = 0;
    int32_t d17 = 0;
    int32_t d18 = 0;
    int32_t d19 = 0;
    int32_t dn = 0;
    int64_t t = val;
    int32_t i = (dn - 1);
    if ((dst ==((uint8_t *)(0)))) {
      return at;
    }
    if ((val < 0)) {
      if (((at + 1) >=cap)) {
        return at;
      }
      (void)(((dst)[at] = 45));
      (void)((at = (at + 1)));
      (void)((val = (0 - val)));
    }
    if ((val <=2147483647)) {
      return driver_diag_append_i32(dst, cap, at, ((int32_t)(val)));
    }
    while ((t > 0)) {
      int32_t dig = ((int32_t)((t % 10)));
      if ((dn >=20)) {
        break;
      }
      if ((dn ==0)) {
        (void)((d0 = dig));
      }
      if ((dn ==1)) {
        (void)((d1 = dig));
      }
      if ((dn ==2)) {
        (void)((d2 = dig));
      }
      if ((dn ==3)) {
        (void)((d3 = dig));
      }
      if ((dn ==4)) {
        (void)((d4 = dig));
      }
      if ((dn ==5)) {
        (void)((d5 = dig));
      }
      if ((dn ==6)) {
        (void)((d6 = dig));
      }
      if ((dn ==7)) {
        (void)((d7 = dig));
      }
      if ((dn ==8)) {
        (void)((d8 = dig));
      }
      if ((dn ==9)) {
        (void)((d9 = dig));
      }
      if ((dn ==10)) {
        (void)((d10 = dig));
      }
      if ((dn ==11)) {
        (void)((d11 = dig));
      }
      if ((dn ==12)) {
        (void)((d12 = dig));
      }
      if ((dn ==13)) {
        (void)((d13 = dig));
      }
      if ((dn ==14)) {
        (void)((d14 = dig));
      }
      if ((dn ==15)) {
        (void)((d15 = dig));
      }
      if ((dn ==16)) {
        (void)((d16 = dig));
      }
      if ((dn ==17)) {
        (void)((d17 = dig));
      }
      if ((dn ==18)) {
        (void)((d18 = dig));
      }
      if ((dn ==19)) {
        (void)((d19 = dig));
      }
      (void)((t = (t / 10)));
      (void)((dn = (dn + 1)));
    }
    if ((dn ==0)) {
      (void)((d0 = 0));
      (void)((dn = 1));
    }
    while ((i >=0)) {
      int32_t dig2 = 0;
      if (((at + 1) >=cap)) {
        break;
      }
      if ((i ==0)) {
        (void)((dig2 = d0));
      }
      if ((i ==1)) {
        (void)((dig2 = d1));
      }
      if ((i ==2)) {
        (void)((dig2 = d2));
      }
      if ((i ==3)) {
        (void)((dig2 = d3));
      }
      if ((i ==4)) {
        (void)((dig2 = d4));
      }
      if ((i ==5)) {
        (void)((dig2 = d5));
      }
      if ((i ==6)) {
        (void)((dig2 = d6));
      }
      if ((i ==7)) {
        (void)((dig2 = d7));
      }
      if ((i ==8)) {
        (void)((dig2 = d8));
      }
      if ((i ==9)) {
        (void)((dig2 = d9));
      }
      if ((i ==10)) {
        (void)((dig2 = d10));
      }
      if ((i ==11)) {
        (void)((dig2 = d11));
      }
      if ((i ==12)) {
        (void)((dig2 = d12));
      }
      if ((i ==13)) {
        (void)((dig2 = d13));
      }
      if ((i ==14)) {
        (void)((dig2 = d14));
      }
      if ((i ==15)) {
        (void)((dig2 = d15));
      }
      if ((i ==16)) {
        (void)((dig2 = d16));
      }
      if ((i ==17)) {
        (void)((dig2 = d17));
      }
      if ((i ==18)) {
        (void)((dig2 = d18));
      }
      if ((i ==19)) {
        (void)((dig2 = d19));
      }
      (void)(((dst)[at] = ((uint8_t)((48 + dig2)))));
      (void)((at = (at + 1)));
      (void)((i = (i - 1)));
    }
    if ((at < cap)) {
      (void)(((dst)[at] = 0));
    }
    return at;
  }
  return at;
}
void driver_print_check_ok(uint8_t * input_path) {
  {
    uint8_t msg[512] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 512, 0, ((uint8_t *)"\x63\x68\x65\x63\x6b\x20\x4f\x4b\x3a\x20"));
    if ((driver_check_quiet_ok_get() !=0)) {
      return;
    }
    if ((input_path !=((uint8_t *)(0)))) {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, input_path)));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x3f"))));
    }
    (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x69\x6e\x66\x6f"), &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
double compile_phase_now_sec(void) {
  return xlang_driver_wall_clock_sec();
  return 0.0;
}
void driver_run_fn_on_current_large_stack(uint8_t * fn, uint8_t * arg) {
  if ((fn ==((uint8_t *)(0)))) {
    return;
  }
  (void)(driver_large_stack_thread_mark(1));
  (void)(driver_bump_stack_limit());
  (void)(xlang_driver_call_fn_void_arg(fn, arg));
  (void)(driver_large_stack_thread_mark(0));
}
int32_t driver_compile_phase_index_ok(int32_t phase) {
  if ((phase < 0)) {
    return 0;
  }
  if ((phase >=3)) {
    return 0;
  }
  return 1;
}
int32_t driver_compile_phase_timing_enabled(void) {
  return driver_env_nonnull(((uint8_t *)"\x53\x48\x55\x58\x5f\x43\x4f\x4d\x50\x49\x4c\x45\x5f\x50\x48\x41\x53\x45\x5f\x54\x49\x4d\x49\x4e\x47"));
}
double driver_compile_phase_acc_ms_get(int32_t phase) {
  if ((driver_compile_phase_index_ok(phase) ==0)) {
    return 0.0;
  }
  return (g_compile_phase_acc_ms)[phase];
}
void driver_compile_phase_timing_clear(void) {
  (void)(((g_compile_phase_acc_ms)[0] = 0.0));
  (void)(((g_compile_phase_acc_ms)[1] = 0.0));
  (void)(((g_compile_phase_acc_ms)[2] = 0.0));
  (void)(((g_compile_phase_active)[0] = 0));
  (void)(((g_compile_phase_active)[1] = 0));
  (void)(((g_compile_phase_active)[2] = 0));
}
void driver_compile_phase_timing_begin(int32_t phase) {
  if ((driver_compile_phase_timing_enabled() ==0)) {
    return;
  }
  if ((driver_compile_phase_index_ok(phase) ==0)) {
    return;
  }
  (void)(((g_compile_phase_start_sec)[phase] = compile_phase_now_sec()));
  (void)(((g_compile_phase_active)[phase] = 1));
}
void driver_compile_phase_timing_end(int32_t phase) {
  if ((driver_compile_phase_timing_enabled() ==0)) {
    return;
  }
  if ((driver_compile_phase_index_ok(phase) ==0)) {
    return;
  }
  if (((g_compile_phase_active)[phase] ==0)) {
    return;
  }
  double now = compile_phase_now_sec();
  (void)(((g_compile_phase_acc_ms)[phase] = ((g_compile_phase_acc_ms)[phase] + ((now - (g_compile_phase_start_sec)[phase]) * ((double)(1000))))));
  (void)(((g_compile_phase_active)[phase] = 0));
}
void driver_compile_phase_timing_flush(void) {
  if ((driver_compile_phase_timing_enabled() ==0)) {
    return;
  }
  {
    int32_t a0 = ((int32_t)(driver_compile_phase_acc_ms_get(0)));
    int32_t a1 = ((int32_t)(driver_compile_phase_acc_ms_get(1)));
    int32_t a2 = ((int32_t)(driver_compile_phase_acc_ms_get(2)));
    int32_t total = ((a0 + a1) + a2);
    uint8_t msg[192] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 192, 0, ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x20\x70\x68\x61\x73\x65\x20\x74\x69\x6d\x69\x6e\x67\x3a\x20\x70\x61\x72\x73\x65\x5f\x6d\x73\x3d"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 192, at, a0)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 192, at, ((uint8_t *)"\x20\x74\x79\x70\x65\x63\x6b\x5f\x6d\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 192, at, a1)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 192, at, ((uint8_t *)"\x20\x63\x6f\x64\x65\x67\x65\x6e\x5f\x6d\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 192, at, a2)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 192, at, ((uint8_t *)"\x20\x74\x6f\x74\x61\x6c\x5f\x6d\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 192, at, total)));
    (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x6e\x6f\x74\x65"), &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(driver_compile_phase_timing_clear());
}
int32_t driver_ascii_toupper(int32_t c) {
  if ((c < 97)) {
    return c;
  }
  if ((c > 122)) {
    return c;
  }
  return (c - 32);
}
int32_t driver_typeck_skip_large_entry(void) {
  int32_t len = driver_pipeline_entry_source_len_i32();
  if ((len > 150000)) {
    return 1;
  }
  return 0;
}
int32_t driver_sanitize_address_get(void) {
  {
    int32_t * p = driver_sanitize_address_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x53\x41\x4e\x49\x54\x49\x5a\x45\x5f\x41\x44\x44\x52\x45\x53\x53"));
  }
  return 0;
}
int32_t driver_typeck_force_c_enabled(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x46\x4f\x52\x43\x45\x5f\x43"));
}
int32_t driver_asm_build_skip_typeck(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x41\x53\x4d\x5f\x42\x55\x49\x4c\x44\x5f\x53\x4b\x49\x50\x5f\x54\x59\x50\x45\x43\x4b"));
}
int32_t driver_asm_entry_emit_heavy(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x41\x53\x4d\x5f\x45\x4e\x54\x52\x59\x5f\x45\x4d\x49\x54\x5f\x48\x45\x41\x56\x59"));
}
int32_t driver_pipeline_no_large_stack_env(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x50\x49\x50\x45\x4c\x49\x4e\x45\x5f\x4e\x4f\x5f\x4c\x41\x52\x47\x45\x5f\x53\x54\x41\x43\x4b"));
}
int32_t driver_asm_entry_module_only_from_env(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x41\x53\x4d\x5f\x45\x4e\x54\x52\x59\x5f\x4d\x4f\x44\x55\x4c\x45\x5f\x4f\x4e\x4c\x59"));
}
int32_t driver_asm_parse_metric_only_from_env(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x41\x53\x4d\x5f\x50\x41\x52\x53\x45\x5f\x4d\x45\x54\x52\x49\x43\x5f\x4f\x4e\x4c\x59"));
}
int32_t driver_pipeline_entry_source_len_i32(void) {
  {
    int64_t len = driver_pipeline_entry_source_len_load_and_maybe_debug();
    if ((len > 2147483647)) {
      return 2147483647;
    }
    if ((len < 0)) {
      return 0;
    }
    return ((int32_t)(len));
  }
  return 0;
}
void driver_defines_set_at(uint8_t * defines, int32_t i, uint8_t * s) {
  if ((defines ==((uint8_t *)(0)))) {
    return;
  }
  if ((i < 0)) {
    return;
  }
  (void)(xlang_ptr_slot_set(defines, i, s));
  (void)(0);
  return;
}
int64_t driver_stack_limit_want_bytes(void) {
  int64_t def = ((((int64_t)(512)) * ((int64_t)(1024))) * ((int64_t)(1024)));
  {
    /* wave228 G.7: link_abi_getenv (not raw getenv); host residual = link_abi_getenv_impl. */
    uint8_t * e = link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x53\x54\x41\x43\x4b\x5f\x4c\x49\x4d\x49\x54\x5f\x4d\x42"));
    if ((e ==((uint8_t *)(0)))) {
      return def;
    }
    if (((e)[0] ==0)) {
      return def;
    }
    int64_t mb = driver_parse_u32_cstr(e);
    if ((mb < 64)) {
      return def;
    }
    if ((mb > 8192)) {
      return def;
    }
    return (mb * (((int64_t)(1024)) * ((int64_t)(1024))));
  }
  return def;
}
void driver_bump_stack_limit(void) {
  (void)(xlang_driver_bump_stack_limit(driver_stack_limit_want_bytes()));
  (void)(0);
  return;
}
void driver_set_pipeline_entry_source_len(int64_t len) {
  (void)(driver_pipeline_entry_source_len_store(len));
}
int32_t compile_phase_timing_enabled(void) {
  return driver_env_nonnull(((uint8_t *)"\x53\x48\x55\x58\x5f\x43\x4f\x4d\x50\x49\x4c\x45\x5f\x50\x48\x41\x53\x45\x5f\x54\x49\x4d\x49\x4e\x47"));
}
uint8_t * driver_os_define_lit(int32_t kind) {
  if ((kind ==1)) {
    return ((uint8_t *)"\x4f\x53\x5f\x4c\x49\x4e\x55\x58");
  }
  if ((kind ==2)) {
    return ((uint8_t *)"\x4f\x53\x5f\x4d\x41\x43\x4f\x53");
  }
  if ((kind ==3)) {
    return ((uint8_t *)"\x4f\x53\x5f\x46\x52\x45\x45\x42\x53\x44");
  }
  if ((kind ==4)) {
    return ((uint8_t *)"\x4f\x53\x5f\x57\x49\x4e\x44\x4f\x57\x53");
  }
  return ((uint8_t *)(0));
}
void driver_pipeline_fail_code(int32_t rc, uint8_t * path) {
  {
    uint8_t msg[96] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 96, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x66\x61\x69\x6c\x65\x64\x20\x72\x63\x3d"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 96, at, rc)));
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x58\x50\x30\x30\x33"), &((msg)[0]), ((uint8_t *)(0))));
    if ((rc !=(0 - 7))) {
      return;
    }
    if ((path ==((uint8_t *)(0)))) {
      return;
    }
    uint8_t msg2[512] = {};
    int32_t at2 = driver_diag_append_cstr(&((msg2)[0]), 512, 0, ((uint8_t *)"\x72\x65\x73\x6f\x6c\x76\x65\x20\x70\x61\x74\x68\x20\x74\x72\x69\x65\x64\x3a\x20"));
    (void)((at2 = driver_diag_append_cstr(&((msg2)[0]), 512, at2, path)));
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x58\x50\x30\x30\x34"), &((msg2)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
void driver_print_x_smoke_summary(uint8_t * module, int64_t codegen_len) {
  if ((module ==((uint8_t *)(0)))) {
    return;
  }
  {
    int32_t num_funcs = driver_get_module_num_funcs(module);
    int32_t main_ix = driver_get_module_main_func_index(module);
    uint8_t msg[160] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x4f\x4b\x3a\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"));
    if ((driver_check_diag_emitted_get() !=0)) {
      return;
    }
    (void)((at = driver_diag_append_i32(&((msg)[0]), 160, at, num_funcs)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x20\x6d\x61\x69\x6e\x5f\x69\x64\x78\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 160, at, main_ix)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x20\x63\x6f\x64\x65\x67\x65\x6e\x5f\x62\x79\x74\x65\x73\x3d"))));
    (void)((at = driver_abi_append_i64(&((msg)[0]), 160, at, codegen_len)));
    (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x69\x6e\x66\x6f"), &((msg)[0]), ((uint8_t *)(0))));
    if ((num_funcs <=0)) {
      (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x50\x30\x30\x31"), ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x70\x72\x6f\x64\x75\x63\x65\x64\x20\x6e\x6f\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x73\x20\x69\x6e\x20\x6d\x6f\x64\x75\x6c\x65"), ((uint8_t *)(0))));
      return;
    }
    (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x69\x6e\x66\x6f"), ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x4f\x4b"), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
int32_t driver_peek_source_file(uint8_t * path, uint8_t * content, int64_t cap) {
  if ((path ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((content ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((cap <=1)) {
    return (0 - 1);
  }
  {
    int32_t n = xlang_read_file_into_path(path, content, (cap - 1));
    return n;
  }
  return (0 - 1);
}
uint8_t * driver_get_current_dep_path_for_codegen(void) {
  return driver_current_dep_path_load();
}
int32_t driver_argv_collect_defines(int32_t argc, uint8_t * argv, uint8_t * defines, int32_t max_defines) {
  if ((argv ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((defines ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((max_defines <=0)) {
    return 0;
  }
  if ((argc <=0)) {
    return 0;
  }
  int32_t ndefines = 0;
  uint8_t * target_arg = ((uint8_t *)(0));
  int32_t i = 1;
  while ((i < argc)) {
    {
      uint8_t * arg = driver_argv_at(argv, i);
      if ((arg ==((uint8_t *)(0)))) {
        (void)((i = (i + 1)));
      } else {
        if ((driver_argv_is_D_alone(arg) !=0)) {
          if (((i + 1) >=argc)) {
            (void)((i = (i + 1)));
          } else {
            uint8_t * v = driver_argv_at(argv, (i + 1));
            if ((v !=((uint8_t *)(0)))) {
              if ((ndefines < max_defines)) {
                (void)(driver_defines_set_at(defines, ndefines, v));
                (void)((ndefines = (ndefines + 1)));
              }
            }
            (void)((i = (i + 2)));
          }
        } else {
          if ((driver_argv_is_D_inline(arg) !=0)) {
            uint8_t * def = xlang_cstr_offset(arg, 2);
            if ((def !=((uint8_t *)(0)))) {
              if ((ndefines < max_defines)) {
                (void)(driver_defines_set_at(defines, ndefines, def));
                (void)((ndefines = (ndefines + 1)));
              }
            }
            (void)((i = (i + 1)));
          } else {
            if ((driver_argv_is_target_flag(arg) !=0)) {
              if (((i + 1) < argc)) {
                (void)((target_arg = driver_argv_at(argv, (i + 1))));
                (void)((i = (i + 2)));
              } else {
                (void)((i = (i + 1)));
              }
            } else {
              if ((driver_argv_is_value_skip_flag(arg) !=0)) {
                if (((i + 1) < argc)) {
                  (void)((i = (i + 2)));
                } else {
                  (void)((i = (i + 1)));
                }
              } else {
                (void)((i = (i + 1)));
              }
            }
          }
        }
      }
    }
  }
  if ((target_arg !=((uint8_t *)(0)))) {
    if ((ndefines < max_defines)) {
      int32_t k = driver_target_arg_os_kind(target_arg);
      if ((k !=0)) {
        {
          uint8_t * lit = driver_os_define_lit(k);
          if ((lit !=((uint8_t *)(0)))) {
            (void)(driver_defines_set_at(defines, ndefines, lit));
            (void)((ndefines = (ndefines + 1)));
          }
        }
      }
    }
  }
  if (((ndefines + 2) <=max_defines)) {
    (void)((ndefines = xlang_driver_argv_append_uname(defines, ndefines, max_defines)));
  }
  return ndefines;
}
int32_t driver_source_scan_top_level_import(uint8_t * src, int64_t src_len) {
  if ((src ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((src_len < 8)) {
    return 0;
  }
  {
    int64_t i = 0;
    while (((i + 8) <=src_len)) {
      if (((src)[i] ==105)) {
        if (((src)[(i + 1)] ==109)) {
          if (((src)[(i + 2)] ==112)) {
            if (((src)[(i + 3)] ==111)) {
              if (((src)[(i + 4)] ==114)) {
                if (((src)[(i + 5)] ==116)) {
                  if (((src)[(i + 6)] ==40)) {
                    if (((src)[(i + 7)] ==34)) {
                      return 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (((i + 9) <=src_len)) {
        if (((src)[i] ==61)) {
          if (((src)[(i + 1)] ==32)) {
            if (((src)[(i + 2)] ==105)) {
              if (((src)[(i + 3)] ==109)) {
                if (((src)[(i + 4)] ==112)) {
                  if (((src)[(i + 5)] ==111)) {
                    if (((src)[(i + 6)] ==114)) {
                      if (((src)[(i + 7)] ==116)) {
                        if (((src)[(i + 8)] ==40)) {
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
      }
      (void)((i = (i + 1)));
    }
  }
  return 0;
}
int32_t driver_source_has_top_level_import(uint8_t * src, int64_t src_len) {
  if ((src ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((src_len < 9)) {
    return 0;
  }
  return driver_source_scan_top_level_import(src, src_len);
}
int32_t driver_source_has_top_level_import_path(uint8_t * path) {
  if ((path ==((uint8_t *)(0)))) {
    return 0;
  }
  {
    uint8_t * src = driver_path_read_preprocess_malloc(path);
    if ((src ==((uint8_t *)(0)))) {
      return 0;
    }
    int64_t len = driver_path_last_preprocess_len();
    int32_t has = driver_source_has_top_level_import(src, len);
    (void)(free(src));
    return has;
  }
  return 0;
}
void driver_run_thread_on_large_stack(uint8_t * fn, uint8_t * arg) {
  if ((fn ==((uint8_t *)(0)))) {
    return;
  }
  if ((driver_is_large_stack_thread() !=0)) {
    (void)(xlang_driver_call_fn_void_arg(fn, arg));
    return;
  }
  (void)(driver_bump_stack_limit());
  if ((bootstrap_nostdlib_pthread_is_stub() !=0)) {
    (void)(driver_run_fn_on_current_large_stack(fn, arg));
    return;
  }
  if ((driver_pipeline_no_large_stack_env() !=0)) {
    (void)(driver_run_fn_on_current_large_stack(fn, arg));
    return;
  }
  (void)(xlang_driver_run_thread_on_large_stack_pthread(fn, arg));
}
void driver_run_on_large_stack_pthread(uint8_t * fn, uint8_t * arg) {
  if ((fn ==((uint8_t *)(0)))) {
    return;
  }
  (void)(driver_run_thread_on_large_stack(fn, arg));
}
int64_t driver_pipeline_entry_source_len_load_and_maybe_debug(void) {
  {
    int64_t len = (g_pipeline_entry_source_len)[0];
    if ((driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x49\x50\x45")) !=0)) {
      uint8_t msg[96] = {0};
      int32_t at = driver_diag_append_cstr(&((msg)[0]), 96, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x65\x6e\x74\x72\x79\x5f\x73\x6f\x75\x72\x63\x65\x5f\x6c\x65\x6e\x5f\x67\x6c\x6f\x62\x61\x6c\x3d"));
      (void)((at = driver_abi_append_i64(&((msg)[0]), 96, at, len)));
      (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x6e\x6f\x74\x65"), &((msg)[0]), ((uint8_t *)(0))));
    }
    return len;
  }
  return 0;
}
int64_t driver_pipeline_entry_source_len(void) {
  return driver_pipeline_entry_source_len_load_and_maybe_debug();
}
