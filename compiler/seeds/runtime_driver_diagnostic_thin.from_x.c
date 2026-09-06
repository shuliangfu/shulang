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
extern void driver_diagnostic_entry_already(int32_t v);
extern void driver_diagnostic_after_dep_codegen(int32_t j, int32_t out_len);
extern void driver_diagnostic_typeck_fail(void);
extern int32_t driver_diag_append_cstr(uint8_t * dst, int32_t cap, int32_t at, uint8_t * src);
extern int32_t driver_diag_append_name(uint8_t * dst, int32_t cap, int32_t at, uint8_t * name, int32_t name_len);
extern int32_t driver_diag_append_i32(uint8_t * dst, int32_t cap, int32_t at, int32_t val);
extern int32_t driver_diag_copy_bytes(uint8_t * dst, int64_t dst_size, uint8_t * src, int32_t src_len);
extern int32_t driver_diag_env_debug_pipe(void);
extern void driver_diagnostic_before_codegen(int32_t num_funcs, int32_t out_len);
extern void driver_diagnostic_source_len(int32_t len);
extern void driver_diagnostic_after_entry_parse(int32_t num_funcs);
extern void driver_diagnostic_pipe_marker(int32_t id);
extern void driver_diagnostic_typeck_if_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_while_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_for_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_deref_outside_unsafe(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_extern_call_outside_unsafe(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_linear_addr_of(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_subscript_base(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_enum_no_variant(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_try_propagate_bad_enclosing(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_break_continue_outside(int32_t line, int32_t col, int32_t is_break);
extern void driver_diagnostic_typeck_invalid_ptr_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_float_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_aggregate_cmp(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_as_cast(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_arity_mismatch(int32_t line, int32_t col);
extern int32_t parser_is_ident_allow(uint8_t * ident, int32_t len);
extern void driver_diagnostic_parse_fail(int32_t main_idx, int32_t num_funcs, int32_t arena_num_types);
extern void driver_diagnostic_codegen_fail(int32_t dep_index, int32_t is_dep);
extern void driver_diagnostic_typeck_func_fail(int32_t func_idx, uint8_t * name, int32_t name_len, int32_t kind);
extern void driver_diagnostic_typeck_ptr_field(int32_t bt_kind, int32_t inner_kind, int32_t inner_nlen, int32_t base_resolved_ref, int32_t num_struct_layouts);
extern void driver_diagnostic_typeck_ret_fail(int32_t stage, int32_t op_expr_ref, int32_t expect_ty_ref, int32_t got_ty_ref);
extern int32_t driver_parse_strict_enabled(void);
extern void driver_diag_note(uint8_t * msg);
extern void driver_diagnostic_asm_last_expr_kind_set(int32_t k);
extern void driver_diagnostic_asm_set_last_expr_kind(int32_t k);
extern void driver_diagnostic_asm_current_func_store(uint8_t * name, int32_t len);
extern void driver_diagnostic_asm_current_func_maybe_trace(void);
extern void driver_diagnostic_asm_set_current_func(uint8_t * name, int32_t len);
extern void driver_diagnostic_asm_print_current_func(void);
extern void driver_diagnostic_asm_var_not_found(uint8_t * name, int32_t len, int32_t num_locals, uint8_t * first_slot, int32_t first_len);
extern void driver_diagnostic_asm_fail_at(int32_t loc);
extern void driver_diag_report_prefixed(int32_t line, int32_t col, uint8_t * msg);
extern void driver_diag_pipe_note(int32_t kind, int32_t a, int32_t b);
extern int32_t driver_diag_parse_debug_enabled(void);
extern void driver_debug_log(int32_t step);
extern void parser_diag_tok_kind(int32_t k);
extern void parser_diag_ident_len(int32_t len);
extern void parser_diag_scan_fail(int32_t step);
extern void driver_diagnostic_typeck_block_enter(int32_t func_idx, int32_t block_ref, int32_t n_const, int32_t n_let, int32_t n_loop, int32_t n_for, int32_t n_expr, int32_t final_ref);
extern void driver_diagnostic_typeck_fn_enter(int32_t func_idx, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_var_resolution(int32_t expr_ref, uint8_t * name, int32_t name_len, int32_t func_idx, int32_t block_ref, int32_t source, int32_t type_ref);
extern uint8_t * driver_typeck_diag_scratch_expect(void);
extern uint8_t * driver_typeck_diag_scratch_found(void);
extern void driver_diag_fill_expr_part(uint8_t * dst, int32_t cap, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diag_build_expected_found(uint8_t * msg, int32_t msg_cap, uint8_t * pref, uint8_t * epart, uint8_t * fpart);
extern void driver_diagnostic_typeck_return_unresolved(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_return_subexpr(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_return_mismatch(int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_assign_mismatch(int32_t is_compound, int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_call_not_generic(int32_t line, int32_t col, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_call_wrong_num_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len, int32_t expect_n, int32_t got_n);
extern void driver_diagnostic_typeck_call_requires_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_struct_padding_before(uint8_t * sname, int32_t sname_len, int32_t gap, uint8_t * fname, int32_t fname_len);
extern void driver_diagnostic_typeck_struct_padding_trailing(uint8_t * sname, int32_t sname_len, int32_t gap);
extern void driver_diagnostic_typeck_struct_field_bad_size(uint8_t * sname, int32_t sname_len, uint8_t * fname, int32_t fname_len);
extern void driver_diagnostic_asm_unsupported_expr(int32_t kind);
extern void driver_diagnostic_asm_elf_unresolved_patch(uint8_t * name, int32_t len);
extern void driver_diagnostic_asm_macho_empty_reloc(int32_t reloc_idx);
extern void driver_diagnostic_asm_macho_missing_und_reloc(int32_t reloc_idx);
extern void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name);
extern void driver_diagnostic_parse_commit_fail(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name);
extern void driver_diagnostic_parse_func_generic(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t num_generic_params, int32_t is_main);
extern void driver_diagnostic_parser_onefunc_param_ref(uint8_t * func_name, int32_t func_name_len, uint8_t * param_name, int32_t param_name_len, int32_t stage, int32_t param_idx, int32_t type_ref);
extern void driver_diagnostic_typeck_import_const_must_be_qualified(int32_t line, int32_t col, uint8_t * name, int32_t name_len, uint8_t * binding, int32_t binding_len);
extern void driver_diagnostic_warn_pad_fields_same_cache_line(uint8_t * sname, int32_t sname_len, uint8_t * f0, int32_t f0_len, uint8_t * f1, int32_t f1_len);
extern void driver_diagnostic_warn_hot_reorder_field(uint8_t * sname, int32_t sname_len, uint8_t * hot, int32_t hot_len, uint8_t * cold, int32_t cold_len);
extern void driver_diagnostic_hint_unused_binding(int32_t line, int32_t col, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_binop_operands(int32_t expr_ref, int32_t left_ref, int32_t right_ref, int32_t left_kind, int32_t right_kind, int32_t left_block_ref, int32_t right_block_ref, int32_t left_ty_ref, int32_t right_ty_ref, uint8_t * left_ty, int32_t left_ty_len, uint8_t * right_ty, int32_t right_ty_len);
extern void driver_diagnostic_parse_commit_shape(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t phase, int32_t block_ref, int32_t pool_num_consts, int32_t pool_num_lets, int32_t pool_num_ifs, int32_t pool_num_regions, int32_t pool_num_stmt_order, int32_t block_num_consts, int32_t block_num_lets, int32_t block_num_ifs, int32_t block_num_regions, int32_t block_num_stmt_order, int32_t final_expr_ref);
extern void parser_diagnostic_parse_commit_shape(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t phase, int32_t block_ref, int32_t pool_num_consts, int32_t pool_num_lets, int32_t pool_num_ifs, int32_t pool_num_regions, int32_t pool_num_stmt_order, int32_t block_num_consts, int32_t block_num_lets, int32_t block_num_ifs, int32_t block_num_regions, int32_t block_num_stmt_order, int32_t final_expr_ref);
extern void driver_diagnostic_after_entry_parse_module(uint8_t * module);
extern void driver_diagnostic_codegen_emit_func_fail(uint8_t * module, int32_t func_index);
extern int32_t runtime_driver_diagnostic_slice_marker(void);
static int32_t g_asm_last_expr_kind;
static uint8_t g_asm_current_func[72];
static int32_t g_asm_current_func_len;
static uint8_t g_type_diag_scratch_expect[96];
static uint8_t g_type_diag_scratch_found[96];
static void init_globals(void) {
  g_asm_last_expr_kind = -(1);
  g_asm_current_func_len = 0;
}
/* wave228 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv). */
extern uint8_t * link_abi_getenv(uint8_t * name);
extern int32_t driver_env_flag_truthy(uint8_t * name);
extern int32_t pipeline_module_num_funcs(uint8_t * module);
extern int32_t pipeline_module_func_is_extern_at(uint8_t * module, int32_t fi);
extern int32_t pipeline_module_func_name_len_at(uint8_t * module, int32_t fi);
extern uint8_t pipeline_module_func_name_byte_at(uint8_t * module, int32_t fi, int32_t bi);
extern int32_t lsp_diag_get_enabled(void);
extern int32_t driver_check_only_get(void);
extern int32_t driver_check_diag_emitted_get(void);
void driver_diagnostic_entry_already(int32_t v) {
  (void)(0);
}
void driver_diagnostic_after_dep_codegen(int32_t j, int32_t out_len) {
  (void)(0);
}
void driver_diagnostic_typeck_fail(void) {
  {
    int32_t _a = driver_check_only_get();
    int32_t _b = driver_check_diag_emitted_get();
  }
  (void)(0);
  return;
}
int32_t driver_diag_append_cstr(uint8_t * dst, int32_t cap, int32_t at, uint8_t * src) {
  if ((dst ==0)) {
    return at;
  }
  if ((src ==0)) {
    return at;
  }
  int32_t j = at;
  int32_t i = 0;
  while (((j + 1) < cap)) {
    uint8_t c = (src)[i];
    if ((c ==0)) {
      break;
    }
    (void)(((dst)[j] = c));
    (void)((j = (j + 1)));
    (void)((i = (i + 1)));
  }
  (void)(((dst)[j] = 0));
  return j;
}
int32_t driver_diag_append_name(uint8_t * dst, int32_t cap, int32_t at, uint8_t * name, int32_t name_len) {
  if ((name ==0)) {
    return at;
  }
  if ((name_len <=0)) {
    return at;
  }
  int32_t n = 0;
  while ((n < name_len)) {
    if (((at + 1) >=cap)) {
      break;
    }
    (void)(((dst)[at] = (name)[n]));
    (void)((at = (at + 1)));
    (void)((n = (n + 1)));
  }
  (void)(((dst)[at] = 0));
  return at;
}
int32_t driver_diag_append_i32(uint8_t * dst, int32_t cap, int32_t at, int32_t val) {
  if ((dst ==0)) {
    return at;
  }
  if (((at + 1) >=cap)) {
    return at;
  }
  int32_t v = val;
  if ((v < 0)) {
    (void)(((dst)[at] = 45));
    (void)((at = (at + 1)));
    (void)((v = (0 - v)));
  }
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
  int32_t dn = 0;
  if ((v ==0)) {
    (void)((d0 = 0));
    (void)((dn = 1));
  } else {
    int32_t t = v;
    while ((t > 0)) {
      int32_t dig = (t % 10);
      if ((dn >=10)) {
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
      (void)((t = (t / 10)));
      (void)((dn = (dn + 1)));
    }
  }
  int32_t i = (dn - 1);
  while ((i >=0)) {
    int32_t dig = 0;
    if (((at + 1) >=cap)) {
      break;
    }
    if ((i ==0)) {
      (void)((dig = d0));
    }
    if ((i ==1)) {
      (void)((dig = d1));
    }
    if ((i ==2)) {
      (void)((dig = d2));
    }
    if ((i ==3)) {
      (void)((dig = d3));
    }
    if ((i ==4)) {
      (void)((dig = d4));
    }
    if ((i ==5)) {
      (void)((dig = d5));
    }
    if ((i ==6)) {
      (void)((dig = d6));
    }
    if ((i ==7)) {
      (void)((dig = d7));
    }
    if ((i ==8)) {
      (void)((dig = d8));
    }
    if ((i ==9)) {
      (void)((dig = d9));
    }
    (void)(((dst)[at] = ((uint8_t)((dig + 48)))));
    (void)((at = (at + 1)));
    (void)((i = (i - 1)));
  }
  (void)(((dst)[at] = 0));
  return at;
}
int32_t driver_diag_copy_bytes(uint8_t * dst, int64_t dst_size, uint8_t * src, int32_t src_len) {
  if ((dst ==0)) {
    return 0;
  }
  if ((dst_size ==0)) {
    return 0;
  }
  int32_t n = 0;
  if ((src !=0)) {
    if ((src_len > 0)) {
      while ((n < src_len)) {
        if (((((int64_t)(n)) + 1) >=dst_size)) {
          break;
        }
        (void)(((dst)[n] = (src)[n]));
        (void)((n = (n + 1)));
      }
    }
  }
  (void)(((dst)[n] = 0));
  return n;
}
extern void lsp_diag_report_typeck(int32_t line, int32_t col, uint8_t * msg);
int32_t driver_diag_env_debug_pipe(void) {
  return driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x49\x50\x45"));
  return 0;
}
void driver_diagnostic_before_codegen(int32_t num_funcs, int32_t out_len) {
  if ((driver_diag_env_debug_pipe() !=0)) {
    (void)(driver_diag_pipe_note(0, num_funcs, out_len));
  }
  (void)(0);
  return;
}
void driver_diagnostic_source_len(int32_t len) {
  if ((driver_diag_env_debug_pipe() !=0)) {
    (void)(driver_diag_pipe_note(1, len, 0));
  }
  (void)(0);
  return;
}
void driver_diagnostic_after_entry_parse(int32_t num_funcs) {
  if ((driver_diag_env_debug_pipe() !=0)) {
    (void)(driver_diag_pipe_note(2, num_funcs, 0));
  }
  (void)(0);
  return;
}
void driver_diagnostic_pipe_marker(int32_t id) {
  if ((driver_diag_env_debug_pipe() !=0)) {
    (void)(driver_diag_pipe_note(3, id, 0));
  }
  (void)(0);
  return;
}
void driver_diagnostic_typeck_if_condition_not_bool(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x69\x66\x20\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x62\x6f\x6f\x6c\x20\x28\x6e\x6f\x20\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x69\x6e\x74\x2d\x74\x6f\x2d\x62\x6f\x6f\x6c\x29")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_while_condition_not_bool(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x77\x68\x69\x6c\x65\x20\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x62\x6f\x6f\x6c\x20\x28\x6e\x6f\x20\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x69\x6e\x74\x2d\x74\x6f\x2d\x62\x6f\x6f\x6c\x29")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_for_condition_not_bool(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x66\x6f\x72\x20\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x62\x6f\x6f\x6c\x20\x28\x6e\x6f\x20\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x69\x6e\x74\x2d\x74\x6f\x2d\x62\x6f\x6f\x6c\x29")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_deref_outside_unsafe(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x70\x6f\x69\x6e\x74\x65\x72\x20\x64\x65\x72\x65\x66\x65\x72\x65\x6e\x63\x65\x20\x72\x65\x71\x75\x69\x72\x65\x73\x20\x75\x6e\x73\x61\x66\x65\x20\x62\x6c\x6f\x63\x6b")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_extern_call_outside_unsafe(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x65\x78\x74\x65\x72\x6e\x20\x63\x61\x6c\x6c\x20\x72\x65\x71\x75\x69\x72\x65\x73\x20\x75\x6e\x73\x61\x66\x65\x20\x62\x6c\x6f\x63\x6b")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_linear_addr_of(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x63\x61\x6e\x6e\x6f\x74\x20\x74\x61\x6b\x65\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x6c\x69\x6e\x65\x61\x72\x20\x76\x61\x6c\x75\x65")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_subscript_base(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x73\x75\x62\x73\x63\x72\x69\x70\x74\x20\x62\x61\x73\x65\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x61\x72\x72\x61\x79\x2c\x20\x73\x6c\x69\x63\x65\x20\x6f\x72\x20\x70\x6f\x69\x6e\x74\x65\x72")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_enum_no_variant(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x65\x6e\x75\x6d\x20\x68\x61\x73\x20\x6e\x6f\x20\x76\x61\x72\x69\x61\x6e\x74")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_try_propagate_bad_enclosing(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x60\x3f\x60\x20\x72\x65\x71\x75\x69\x72\x65\x73\x20\x74\x68\x65\x20\x65\x6e\x63\x6c\x6f\x73\x69\x6e\x67\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x74\x6f\x20\x72\x65\x74\x75\x72\x6e\x20\x74\x68\x65\x20\x73\x61\x6d\x65\x20\x52\x65\x73\x75\x6c\x74\x20\x74")));
  (void)(0);
  return;
}
void driver_diagnostic_typeck_break_continue_outside(int32_t line, int32_t col, int32_t is_break) {
  if ((is_break !=0)) {
    (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x62\x72\x65\x61\x6b\x20\x6f\x6e\x6c\x79\x20\x61\x6c\x6c\x6f\x77\x65\x64\x20\x69\x6e\x73\x69\x64\x65\x20\x61\x20\x6c\x6f\x6f\x70")));
  } else {
    (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)"\x63\x6f\x6e\x74\x69\x6e\x75\x65\x20\x6f\x6e\x6c\x79\x20\x61\x6c\x6c\x6f\x77\x65\x64\x20\x69\x6e\x73\x69\x64\x65\x20\x61\x20\x6c\x6f\x6f\x70")));
  }
  (void)(0);
  return;
}
/* wave285/wave289 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_ptr_binop */
void driver_diagnostic_typeck_invalid_ptr_binop(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"invalid pointer arithmetic (ptr+ptr / non-offset ops / unary -~ not allowed; use integer offset, std.string, or adjacent string literals)")));
  (void)(0);
  return;
}
/* wave286/wave289 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_float_binop */
void driver_diagnostic_typeck_invalid_float_binop(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"invalid float operation (bitwise / mod / shift / unary ~ not allowed on f32/f64; use + - * / and unary - only)")));
  (void)(0);
  return;
}
/* wave657 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_aggregate_cmp */
void driver_diagnostic_typeck_invalid_aggregate_cmp(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"invalid aggregate operation (cmp/arith/unary -/~/! not allowed on array/slice/struct; use scalars or fields)")));
  (void)(0);
  return;
}
/* wave659 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_as_cast */
void driver_diagnostic_typeck_invalid_as_cast(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"invalid cast (as not allowed for aggregate or float↔pointer; use numeric/ptr casts or fields)")));
  (void)(0);
  return;
}
/* wave660 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_call_arity_mismatch */
void driver_diagnostic_typeck_call_arity_mismatch(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"wrong number of arguments in function call (arity mismatch)")));
  (void)(0);
  return;
}
/* wave661 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_call_arg_type_mismatch */
void driver_diagnostic_typeck_call_arg_type_mismatch(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"argument type mismatch in function call")));
  (void)(0);
  return;
}
/* wave675 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_call_unresolved */
void driver_diagnostic_typeck_call_unresolved(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"unresolved function call (no matching function)")));
  (void)(0);
  return;
}
/* wave664 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_subscript_index */
void driver_diagnostic_typeck_subscript_index(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"subscript index must be an integer type")));
  (void)(0);
  return;
}
/* wave666 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_comparison_type_mismatch */
void driver_diagnostic_typeck_comparison_type_mismatch(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      "comparison operands have incompatible types"));
  return;
}
/* wave667 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_void_binop */
void driver_diagnostic_typeck_invalid_void_binop(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      "invalid void operation (void cannot be used in arithmetic or unary -/~)"));
  return;
}
/* wave677 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_invalid_bool_binop */
void driver_diagnostic_typeck_invalid_bool_binop(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      "invalid bool operation (bool cannot be used in arithmetic, bitops, shifts, or unary -/~; use logical ops or `as`)"));
  return;
}
/* wave678 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_assign_to_const */
void driver_diagnostic_typeck_assign_to_const(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      "cannot assign to const binding (const is immutable; use let for a mutable variable)"));
  return;
}
/* wave680 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_duplicate_local */
void driver_diagnostic_typeck_duplicate_local(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      "duplicate local binding in the same block (redeclaration of let/const or parameter name)"));
  return;
}

/* wave665 Cap residual: G.7 ≡ thin.x driver_diagnostic_typeck_logical_operand_not_bool */
void driver_diagnostic_typeck_logical_operand_not_bool(int32_t line, int32_t col) {
  (void)(lsp_diag_report_typeck(line, col,
      ((uint8_t *)"logical operand must be bool (no implicit int-to-bool)")));
  (void)(0);
  return;
}
int32_t parser_is_ident_allow(uint8_t * ident, int32_t len) {
  if ((ident ==0)) {
    return 0;
  }
  if ((len !=5)) {
    return 0;
  }
  if (((((((ident)[0] ==97) && ((ident)[1] ==108)) && ((ident)[2] ==108)) && ((ident)[3] ==111)) && ((ident)[4] ==119))) {
    return 1;
  }
  return 0;
}
extern void diag_report(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * msg, uint8_t * detail);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern void lsp_diag_add(int32_t line, int32_t col, int32_t severity, uint8_t * msg);
extern void lsp_diag_add_code(int32_t line, int32_t col, int32_t severity, uint8_t * code, uint8_t * msg);
extern void driver_check_diag_emitted_note(void);
void driver_diagnostic_parse_fail(int32_t main_idx, int32_t num_funcs, int32_t arena_num_types) {
  {
    uint8_t msg[256] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 256, 0, ((uint8_t *)"\x2e\x78\x20\x70\x61\x72\x73\x65\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x6d\x61\x69\x6e\x5f\x69\x64\x78\x3d"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 256, at, main_idx)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x2c\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 256, at, num_funcs)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x2c\x20\x61\x72\x65\x6e\x61\x5f\x6e\x75\x6d\x5f\x74\x79\x70\x65\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 256, at, arena_num_types)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x29"))));
    if ((lsp_diag_get_enabled() !=0)) {
      (void)(lsp_diag_add_code(1, 1, 1, ((uint8_t *)"\x58\x50\x30\x30\x31"), &((msg)[0])));
      return;
    }
    if ((driver_check_only_get() !=0)) {
      (void)(driver_check_diag_emitted_note());
    }
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x58\x50\x30\x30\x31"), &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
void driver_diagnostic_codegen_fail(int32_t dep_index, int32_t is_dep) {
  uint8_t msg[160] = {};
  int32_t at = 0;
  if ((is_dep !=0)) {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x61\x74\x20\x64\x65\x70\x65\x6e\x64\x65\x6e\x63\x79\x20\x65\x6d\x69\x73\x73\x69\x6f\x6e\x20\x28\x64\x65\x70\x5f\x69\x6e\x64\x65\x78\x3d"))));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x61\x74\x20\x65\x6e\x74\x72\x79\x20\x6d\x6f\x64\x75\x6c\x65\x20\x65\x6d\x69\x73\x73\x69\x6f\x6e\x20\x28\x64\x65\x70\x5f\x69\x6e\x64\x65\x78\x3d"))));
  }
  (void)((at = driver_diag_append_i32(&((msg)[0]), 160, at, dep_index)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x29"))));
  (void)(driver_diag_note(&((msg)[0])));
}
extern int32_t pipeline_typeck_diag_soft_suppress_get(void);
void driver_diagnostic_typeck_func_fail(int32_t func_idx, uint8_t * name, int32_t name_len, int32_t kind) {
  /* PLATFORM: SHARED — dep prerun soft-suppress (see pipeline_typeck_dep_prerun_module_c). */
  if (pipeline_typeck_diag_soft_suppress_get() != 0)
    return;
  {
    uint8_t msg[240] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x2e\x78\x20\x74\x79\x70\x65\x20\x63\x68\x65\x63\x6b\x20\x66\x61\x69\x6c\x65\x64\x20\x69\x6e\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x23"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, func_idx)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20"))));
    if (((name !=((uint8_t *)(0))) && (name_len > 0))) {
      int32_t nl = name_len;
      if ((nl > 64)) {
        (void)((nl = 64));
      }
      (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, nl)));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x28\x75\x6e\x6b\x6e\x6f\x77\x6e\x29"))));
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x28"))));
    if ((kind ==(0 - 6))) {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x74\x61\x69\x6c\x20\x72\x65\x74\x75\x72\x6e"))));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x63\x68\x65\x63\x6b\x5f\x62\x6c\x6f\x63\x6b\x20\x66\x61\x69\x6c\x65\x64"))));
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x29"))));
    if ((lsp_diag_get_enabled() !=0)) {
      (void)(lsp_diag_add_code(1, 1, 1, ((uint8_t *)"\x58\x54\x30\x30\x31"), &((msg)[0])));
      return;
    }
    (void)(driver_check_diag_emitted_note());
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x58\x54\x30\x30\x31"), &((msg)[0]), ((uint8_t *)(0))));
    if ((kind ==(0 - 6))) {
      (void)(driver_diag_report_prefixed(0, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72\x3a\x20\x72\x65\x74\x75\x72\x6e\x20\x76\x61\x6c\x75\x65\x20\x6d\x75\x73\x74\x20\x75\x73\x65\x20\x65\x78\x70\x6c\x69\x63\x69\x74\x20\x72\x65\x74\x75\x72\x6e\x20\x73\x74\x61\x74\x65\x6d\x65\x6e\x74\x20\x28")));
    }
  }
  (void)(0);
  return;
}
void driver_diagnostic_typeck_ptr_field(int32_t bt_kind, int32_t inner_kind, int32_t inner_nlen, int32_t base_resolved_ref, int32_t num_struct_layouts) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x50\x54\x52")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x70\x74\x72\x20\x64\x65\x62\x75\x67\x3a\x20\x46\x49\x45\x4c\x44\x5f\x41\x43\x43\x45\x53\x53\x20\x62\x74\x5f\x6b\x69\x6e\x64\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, bt_kind)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x69\x6e\x6e\x65\x72\x5f\x6b\x69\x6e\x64\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, inner_kind)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x69\x6e\x6e\x65\x72\x5f\x6e\x6c\x65\x6e\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, inner_nlen)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x62\x61\x73\x65\x5f\x72\x65\x73\x6f\x6c\x76\x65\x64\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, base_resolved_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x6e\x75\x6d\x5f\x73\x74\x72\x75\x63\x74\x5f\x6c\x61\x79\x6f\x75\x74\x73\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, num_struct_layouts)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_typeck_ret_fail(int32_t stage, int32_t op_expr_ref, int32_t expect_ty_ref, int32_t got_ty_ref) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x52\x45\x54")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[200] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x72\x65\x74\x75\x72\x6e\x20\x64\x65\x62\x75\x67\x3a\x20\x73\x74\x61\x67\x65\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, stage)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x6f\x70\x5f\x65\x78\x70\x72\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, op_expr_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x65\x78\x70\x65\x63\x74\x5f\x74\x79\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, expect_ty_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x67\x6f\x74\x5f\x74\x79\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, got_ty_ref)));
  (void)(driver_diag_note(&((msg)[0])));
}
/* wave check-false-green (2026-08-05): check_only OR XLANG_PARSE_STRICT.
 * Seed hex was SHUX_PARSE_STRICT (rename residual); product .x uses XLANG_*.
 * PLATFORM: SHARED — keep seed ≡ thin.x. */
int32_t driver_parse_strict_enabled(void) {
  if (driver_check_only_get() != 0)
    return 1;
  /* "XLANG_PARSE_STRICT" */
  return driver_env_flag_truthy((uint8_t *)"XLANG_PARSE_STRICT");
}
void driver_diag_note(uint8_t * msg) {
  {
    uint8_t * m = msg;
    if ((m ==0)) {
      (void)((m = ((uint8_t *)"")));
    }
    (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x6e\x6f\x74\x65"), m, ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
void driver_diagnostic_asm_last_expr_kind_set(int32_t k) {
  (void)((g_asm_last_expr_kind = k));
}
void driver_diagnostic_asm_set_last_expr_kind(int32_t k) {
  (void)((g_asm_last_expr_kind = k));
}
void driver_diagnostic_asm_current_func_store(uint8_t * name, int32_t len) {
  int32_t n = 0;
  if ((len > 0)) {
    if ((len <=64)) {
      (void)((n = len));
    }
  }
  (void)((g_asm_current_func_len = n));
  if ((name !=((uint8_t *)(0)))) {
    if ((n > 0)) {
      int32_t i = 0;
      while ((i < n)) {
        (void)(((g_asm_current_func)[i] = (name)[i]));
        (void)((i = (i + 1)));
      }
    }
  }
}
void driver_diagnostic_asm_current_func_maybe_trace(void) {
  if ((driver_env_flag_truthy(((uint8_t *)"\x53\x48\x55\x58\x5f\x41\x53\x4d\x5f\x46\x55\x4e\x43\x5f\x54\x52\x41\x43\x45")) ==0)) {
    return;
  }
  if ((g_asm_current_func_len <=0)) {
    return;
  }
  uint8_t msg[160] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x61\x73\x6d\x20\x74\x72\x61\x63\x65\x3a\x20"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 160, at, &((g_asm_current_func)[0]), g_asm_current_func_len)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_set_current_func(uint8_t * name, int32_t len) {
  (void)(driver_diagnostic_asm_current_func_store(name, len));
  (void)(driver_diagnostic_asm_current_func_maybe_trace());
}
void driver_diagnostic_asm_print_current_func(void) {
  uint8_t msg[200] = {};
  int32_t at = 0;
  if ((g_asm_current_func_len > 0)) {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x69\x6e\x20\x66\x75\x6e\x63\x3d"))));
    (void)((at = driver_diag_append_name(&((msg)[0]), 200, at, &((g_asm_current_func)[0]), g_asm_current_func_len)));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x66\x75\x6e\x63\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x29"))));
  }
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_var_not_found(uint8_t * name, int32_t len, int32_t num_locals, uint8_t * first_slot, int32_t first_len) {
  uint8_t namebuf[65] = {};
  uint8_t firstbuf[65] = {};
  int32_t _n = driver_diag_copy_bytes(&((namebuf)[0]), 65, name, len);
  int32_t _f = driver_diag_copy_bytes(&((firstbuf)[0]), 65, first_slot, first_len);
  uint8_t msg[320] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 320, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x45\x58\x50\x52\x5f\x56\x41\x52\x20\x6e\x6f\x74\x20\x69\x6e\x20\x63\x74\x78\x3a\x20\x5c\x22"));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, &((namebuf)[0]))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x5c\x22\x20\x28\x66\x75\x6e\x63\x3a\x20"))));
  if ((g_asm_current_func_len > 0)) {
    (void)((at = driver_diag_append_name(&((msg)[0]), 320, at, &((g_asm_current_func)[0]), g_asm_current_func_len)));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x3f"))));
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x2c\x20\x6e\x75\x6d\x5f\x6c\x6f\x63\x61\x6c\x73\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 320, at, num_locals)));
  if ((num_locals > 0)) {
    if ((first_slot !=((uint8_t *)(0)))) {
      if ((first_len > 0)) {
        if ((first_len <=64)) {
          (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x2c\x20\x66\x69\x72\x73\x74\x5f\x73\x6c\x6f\x74\x3d\x5c\x22"))));
          (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, &((firstbuf)[0]))));
          (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x5c\x22\x20\x6c\x65\x6e\x3d"))));
          (void)((at = driver_diag_append_i32(&((msg)[0]), 320, at, first_len)));
        }
      }
    }
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x29"))));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_fail_at(int32_t loc) {
  uint8_t msg[240] = {};
  int32_t at = 0;
  if ((g_asm_current_func_len > 0)) {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x75\x6e\x63\x3d"))));
    (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, &((g_asm_current_func)[0]), g_asm_current_func_len)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x66\x61\x69\x6c\x5f\x61\x74\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, loc)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x28\x6c\x61\x73\x74\x5f\x65\x78\x70\x72\x5f\x6b\x69\x6e\x64\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, g_asm_last_expr_kind)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x29"))));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x66\x61\x69\x6c\x5f\x61\x74\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, loc)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x28\x6c\x61\x73\x74\x5f\x65\x78\x70\x72\x5f\x6b\x69\x6e\x64\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, g_asm_last_expr_kind)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x29"))));
  }
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diag_report_prefixed(int32_t line, int32_t col, uint8_t * msg) {
  {
    uint8_t * m2 = msg;
    if ((lsp_diag_get_enabled() !=0)) {
      int32_t ln = line;
      int32_t cl = col;
      if ((ln <=0)) {
        (void)((ln = 1));
      }
      if ((cl <=0)) {
        (void)((cl = 1));
      }
      uint8_t * m = msg;
      if ((m ==((uint8_t *)(0)))) {
        (void)((m = ((uint8_t *)"")));
      }
      (void)(lsp_diag_add(ln, cl, 1, m));
      return;
    }
    if ((driver_check_only_get() !=0)) {
      (void)(driver_check_diag_emitted_note());
    }
    if ((m2 ==((uint8_t *)(0)))) {
      (void)((m2 = ((uint8_t *)"")));
    }
    (void)(diag_report(((uint8_t *)(0)), line, col, ((uint8_t *)(0)), m2, m2));
  }
  (void)(0);
  return;
}
void driver_diag_pipe_note(int32_t kind, int32_t a, int32_t b) {
  uint8_t msg[128] = {};
  if ((kind ==0)) {
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x62\x65\x66\x6f\x72\x65\x5f\x63\x6f\x64\x65\x67\x65\x6e\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, a)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 128, at, ((uint8_t *)"\x20\x6f\x75\x74\x5f\x6c\x65\x6e\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, b)));
    (void)(driver_diag_note(&((msg)[0])));
    return;
  }
  if ((kind ==1)) {
    int32_t at1 = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x65\x6e\x74\x72\x79\x5f\x73\x6f\x75\x72\x63\x65\x5f\x6c\x65\x6e\x3d"));
    (void)((at1 = driver_diag_append_i32(&((msg)[0]), 128, at1, a)));
    (void)(driver_diag_note(&((msg)[0])));
    return;
  }
  if ((kind ==2)) {
    int32_t at2 = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x61\x66\x74\x65\x72\x5f\x65\x6e\x74\x72\x79\x5f\x70\x61\x72\x73\x65\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"));
    (void)((at2 = driver_diag_append_i32(&((msg)[0]), 128, at2, a)));
    (void)(driver_diag_note(&((msg)[0])));
    return;
  }
  if ((kind ==3)) {
    int32_t at3 = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x70\x69\x70\x65\x5f\x6d\x61\x72\x6b\x65\x72\x3d"));
    (void)((at3 = driver_diag_append_i32(&((msg)[0]), 128, at3, a)));
    (void)(driver_diag_note(&((msg)[0])));
    return;
  }
  (void)(0);
  return;
}
int32_t driver_diag_parse_debug_enabled(void) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x41\x52\x53\x45")) !=((uint8_t *)(0)))) {
    return 1;
  }
  return driver_parse_strict_enabled();
}
void driver_debug_log(int32_t step) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  uint8_t msg[128] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x73\x74\x65\x70\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, step)));
  (void)(driver_diag_note(&((msg)[0])));
}
void parser_diag_tok_kind(int32_t k) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  uint8_t msg[128] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x72\x2e\x74\x6f\x6b\x2e\x6b\x69\x6e\x64\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, k)));
  (void)(driver_diag_note(&((msg)[0])));
}
void parser_diag_ident_len(int32_t len) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  uint8_t msg[128] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x66\x69\x72\x73\x74\x20\x69\x64\x65\x6e\x74\x5f\x6c\x65\x6e\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, len)));
  (void)(driver_diag_note(&((msg)[0])));
}
void parser_diag_scan_fail(int32_t step) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  uint8_t msg[128] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 128, 0, ((uint8_t *)"\x6c\x69\x62\x72\x61\x72\x79\x20\x73\x63\x61\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x61\x74\x20\x73\x74\x65\x70\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 128, at, step)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_typeck_block_enter(int32_t func_idx, int32_t block_ref, int32_t n_const, int32_t n_let, int32_t n_loop, int32_t n_for, int32_t n_expr, int32_t final_ref) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x42\x4c\x4f\x43\x4b")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x62\x6c\x6f\x63\x6b\x20\x64\x65\x62\x75\x67\x3a\x20\x66\x75\x6e\x63\x5f\x69\x64\x78\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, func_idx)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x62\x6c\x6f\x63\x6b\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, block_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x63\x6f\x6e\x73\x74\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, n_const)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x6c\x65\x74\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, n_let)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x77\x68\x69\x6c\x65\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, n_loop)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x66\x6f\x72\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, n_for)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x65\x78\x70\x72\x5f\x73\x74\x6d\x74\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, n_expr)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x66\x69\x6e\x61\x6c\x5f\x65\x78\x70\x72\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, final_ref)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_typeck_fn_enter(int32_t func_idx, uint8_t * name, int32_t name_len) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x46\x4e")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[160] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64\x65\x62\x75\x67\x3a\x20\x66\x75\x6e\x63\x5f\x69\x64\x78\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 160, at, func_idx)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x20\x6e\x61\x6d\x65\x3d"))));
  if (((name !=((uint8_t *)(0))) && (name_len > 0))) {
    (void)((at = driver_diag_append_name(&((msg)[0]), 160, at, name, name_len)));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x28\x75\x6e\x6b\x6e\x6f\x77\x6e\x29"))));
  }
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_typeck_var_resolution(int32_t expr_ref, uint8_t * name, int32_t name_len, int32_t func_idx, int32_t block_ref, int32_t source, int32_t type_ref) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x56\x41\x52")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[200] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x76\x61\x72\x20\x64\x65\x62\x75\x67\x3a\x20\x65\x78\x70\x72\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, expr_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x6e\x61\x6d\x65\x3d"))));
  if (((name !=((uint8_t *)(0))) && (name_len > 0))) {
    (void)((at = driver_diag_append_name(&((msg)[0]), 200, at, name, name_len)));
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x3f"))));
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x66\x75\x6e\x63\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, func_idx)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x62\x6c\x6f\x63\x6b\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, block_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x73\x6f\x75\x72\x63\x65\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, source)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x74\x79\x70\x65\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, type_ref)));
  (void)(driver_diag_note(&((msg)[0])));
}
uint8_t * driver_typeck_diag_scratch_expect(void) {
  return &((g_type_diag_scratch_expect)[0]);
}
uint8_t * driver_typeck_diag_scratch_found(void) {
  return &((g_type_diag_scratch_found)[0]);
}
void driver_diag_fill_expr_part(uint8_t * dst, int32_t cap, uint8_t * expr_buf, int32_t expr_len) {
  if ((dst ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  int32_t el = 0;
  if ((expr_buf !=0)) {
    if ((expr_len > 0)) {
      (void)((el = expr_len));
    }
  }
  if ((el > 0)) {
    if ((el < cap)) {
      int32_t n = driver_diag_copy_bytes(dst, ((int64_t)(cap)), expr_buf, el);
      return;
    }
  }
  (void)(((dst)[0] = 63));
  if ((cap > 1)) {
    (void)(((dst)[1] = 0));
  }
}
void driver_diag_build_expected_found(uint8_t * msg, int32_t msg_cap, uint8_t * pref, uint8_t * epart, uint8_t * fpart) {
  uint8_t * mid = ((uint8_t *)"\x2c\x20\x66\x6f\x75\x6e\x64\x20");
  int32_t at = driver_diag_append_cstr(msg, msg_cap, 0, pref);
  (void)((at = driver_diag_append_cstr(msg, msg_cap, at, epart)));
  (void)((at = driver_diag_append_cstr(msg, msg_cap, at, mid)));
  (void)((at = driver_diag_append_cstr(msg, msg_cap, at, fpart)));
}
void driver_diagnostic_typeck_return_unresolved(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len) {
  uint8_t expr_part[128] = {};
  uint8_t msg[240] = {};
  (void)(driver_diag_fill_expr_part(&((expr_part)[0]), 128, expr_buf, expr_len));
  uint8_t * pref = ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x72\x65\x73\x6f\x6c\x76\x65\x20\x72\x65\x74\x75\x72\x6e\x20\x73\x75\x62\x65\x78\x70\x72\x65\x73\x73\x69\x6f\x6e\x3a\x20");
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, pref);
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, &((expr_part)[0]))));
  (void)(driver_diag_report_prefixed(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_return_subexpr(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len) {
  uint8_t expr_part[128] = {};
  uint8_t msg[240] = {};
  (void)(driver_diag_fill_expr_part(&((expr_part)[0]), 128, expr_buf, expr_len));
  uint8_t * pref = ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x6e\x6f\x74\x65\x3a\x20\x72\x65\x74\x75\x72\x6e\x20\x73\x75\x62\x65\x78\x70\x72\x65\x73\x73\x69\x6f\x6e\x3a\x20");
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, pref);
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, &((expr_part)[0]))));
  (void)(driver_diag_report_prefixed(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_return_mismatch(int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len) {
  uint8_t epart[112] = {};
  uint8_t fpart[112] = {};
  uint8_t msg[240] = {};
  (void)(driver_diag_fill_expr_part(&((epart)[0]), 112, expect_buf, expect_len));
  (void)(driver_diag_fill_expr_part(&((fpart)[0]), 112, found_buf, found_len));
  uint8_t * pref = ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72\x3a\x20\x72\x65\x74\x75\x72\x6e\x20\x65\x78\x70\x72\x65\x73\x73\x69\x6f\x6e\x20\x74\x79\x70\x65\x20\x6d\x69\x73\x6d\x61\x74\x63\x68\x3a\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20");
  (void)(driver_diag_build_expected_found(&((msg)[0]), 240, pref, &((epart)[0]), &((fpart)[0])));
  (void)(driver_diag_report_prefixed(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_assign_mismatch(int32_t is_compound, int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len) {
  uint8_t epart[112] = {};
  uint8_t fpart[112] = {};
  uint8_t msg[240] = {};
  (void)(driver_diag_fill_expr_part(&((epart)[0]), 112, expect_buf, expect_len));
  (void)(driver_diag_fill_expr_part(&((fpart)[0]), 112, found_buf, found_len));
  uint8_t * pref = ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72\x3a\x20\x61\x73\x73\x69\x67\x6e\x6d\x65\x6e\x74\x20\x74\x79\x70\x65\x20\x6d\x69\x73\x6d\x61\x74\x63\x68\x3a\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20");
  if ((is_compound !=0)) {
    (void)((pref = ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x65\x72\x72\x6f\x72\x3a\x20\x63\x6f\x6d\x70\x6f\x75\x6e\x64\x20\x61\x73\x73\x69\x67\x6e\x6d\x65\x6e\x74\x20\x74\x79\x70\x65\x20\x6d\x69\x73\x6d\x61\x74\x63\x68\x3a\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20")));
  }
  (void)(driver_diag_build_expected_found(&((msg)[0]), 240, pref, &((epart)[0]), &((fpart)[0])));
  (void)(driver_diag_report_prefixed(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_call_not_generic(int32_t line, int32_t col, uint8_t * name, int32_t name_len) {
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, name_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x27\x20\x69\x73\x20\x6e\x6f\x74\x20\x67\x65\x6e\x65\x72\x69\x63\x20\x62\x75\x74\x20\x74\x79\x70\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x77\x65\x72\x65\x20\x70\x72\x6f\x76\x69\x64\x65\x64"))));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_call_wrong_num_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len, int32_t expect_n, int32_t got_n) {
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x67\x65\x6e\x65\x72\x69\x63\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, name_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x27\x20\x65\x78\x70\x65\x63\x74\x73\x20"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, expect_n)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x74\x79\x70\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x2c\x20\x67\x6f\x74\x20"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, got_n)));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_call_requires_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len) {
  uint8_t msg[280] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 280, 0, ((uint8_t *)"\x67\x65\x6e\x65\x72\x69\x63\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, name, name_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x27\x20\x72\x65\x71\x75\x69\x72\x65\x73\x20\x74\x79\x70\x65\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x28\x65\x2e\x67\x2e\x20"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, name, name_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x3c\x54\x79\x70\x65\x3e\x28\x2e\x2e\x2e\x29\x29"))));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
}
void driver_diagnostic_typeck_struct_padding_before(uint8_t * sname, int32_t sname_len, int32_t gap, uint8_t * fname, int32_t fname_len) {
  uint8_t msg[320] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 320, 0, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 320, at, sname, sname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x27\x20\x68\x61\x73\x20"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 320, at, gap)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x20\x62\x79\x74\x65\x28\x73\x29\x20\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x70\x61\x64\x64\x69\x6e\x67\x20\x62\x65\x66\x6f\x72\x65\x20\x66\x69\x65\x6c\x64\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 320, at, fname, fname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x27\x3b\x20\x61\x64\x64\x20\x65\x78\x70\x6c\x69\x63\x69\x74\x20\x70\x61\x64\x64\x69\x6e\x67\x20\x66\x69\x65\x6c\x64\x20\x6f\x72\x20\x61\x6c\x6c\x6f\x77\x28\x70\x61\x64\x64\x69\x6e\x67\x29"))));
  (void)(lsp_diag_report_typeck(0, 0, &((msg)[0])));
}
void driver_diagnostic_typeck_struct_padding_trailing(uint8_t * sname, int32_t sname_len, int32_t gap) {
  uint8_t msg[320] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 320, 0, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 320, at, sname, sname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x27\x20\x68\x61\x73\x20"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 320, at, gap)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 320, at, ((uint8_t *)"\x20\x62\x79\x74\x65\x28\x73\x29\x20\x69\x6d\x70\x6c\x69\x63\x69\x74\x20\x74\x72\x61\x69\x6c\x69\x6e\x67\x20\x70\x61\x64\x64\x69\x6e\x67\x3b\x20\x61\x64\x64\x20\x65\x78\x70\x6c\x69\x63\x69\x74\x20\x70\x61\x64\x64\x69\x6e\x67\x20\x66\x69\x65\x6c\x64\x20"))));
  (void)(lsp_diag_report_typeck(0, 0, &((msg)[0])));
}
void driver_diagnostic_typeck_struct_field_bad_size(uint8_t * sname, int32_t sname_len, uint8_t * fname, int32_t fname_len) {
  uint8_t msg[280] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 280, 0, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, sname, sname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x27\x20\x66\x69\x65\x6c\x64\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, fname, fname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x27\x20\x68\x61\x73\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x6f\x72\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x74\x79\x70\x65\x20\x73\x69\x7a\x65"))));
  (void)(lsp_diag_report_typeck(0, 0, &((msg)[0])));
}
void driver_diagnostic_asm_unsupported_expr(int32_t kind) {
  uint8_t msg[96] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 96, 0, ((uint8_t *)"\x61\x73\x6d\x20\x63\x6f\x64\x65\x67\x65\x6e\x20\x75\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x45\x78\x70\x72\x4b\x69\x6e\x64\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 96, at, kind)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_elf_unresolved_patch(uint8_t * name, int32_t len) {
  uint8_t namebuf[65] = {};
  (void)(driver_diag_fill_expr_part(&((namebuf)[0]), 65, name, len));
  uint8_t msg[160] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x65\x6c\x66\x20\x75\x6e\x72\x65\x73\x6f\x6c\x76\x65\x64\x20\x70\x61\x74\x63\x68\x20\x6c\x61\x62\x65\x6c\x20\x6e\x61\x6d\x65\x5f\x6c\x65\x6e\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 160, at, len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x20\x6e\x61\x6d\x65\x3d\x27"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, &((namebuf)[0]))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x27"))));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_macho_empty_reloc(int32_t reloc_idx) {
  uint8_t msg[96] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 96, 0, ((uint8_t *)"\x6d\x61\x63\x68\x6f\x20\x65\x6d\x70\x74\x79\x20\x72\x65\x6c\x6f\x63\x20\x73\x79\x6d\x62\x6f\x6c\x20\x61\x74\x20\x69\x64\x78\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 96, at, reloc_idx)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_asm_macho_missing_und_reloc(int32_t reloc_idx) {
  uint8_t msg[96] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 96, 0, ((uint8_t *)"\x6d\x61\x63\x68\x6f\x20\x75\x6e\x64\x65\x66\x20\x72\x65\x6c\x6f\x63\x20\x6e\x6f\x74\x20\x69\x6e\x20\x75\x6e\x64\x20\x70\x6f\x6f\x6c\x20\x61\x74\x20\x69\x64\x78\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 96, at, reloc_idx)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_parse_skip_function(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  {
    uint8_t * tag = ((uint8_t *)"\x73\x74\x72\x69\x63\x74");
    if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x41\x52\x53\x45")) !=((uint8_t *)(0)))) {
      (void)((tag = ((uint8_t *)"\x64\x65\x62\x75\x67")));
    }
    uint8_t msg[240] = {};
    int32_t at = 0;
    if ((lsp_diag_get_enabled() !=0)) {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x73\x6b\x69\x70\x20\x61\x74\x20\x62\x79\x74\x65\x20"))));
      (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, byte_pos)));
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x28\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
      (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, num_funcs_so_far)));
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x29\x20\x6e\x61\x6d\x65\x3d"))));
      if ((name !=((uint8_t *)(0)))) {
        if ((name_len > 0)) {
          (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, name_len)));
        } else {
          (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
        }
      } else {
        (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
      }
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x5b"))));
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, tag)));
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x5d"))));
      (void)(lsp_diag_add(1, 1, 1, &((msg)[0])));
      return;
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x73\x6b\x69\x70\x20\x61\x74\x20\x62\x79\x74\x65\x20"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, byte_pos)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x28\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, num_funcs_so_far)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x2c\x20\x6e\x61\x6d\x65\x3d"))));
    if ((name !=((uint8_t *)(0)))) {
      if ((name_len > 0)) {
        (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, name_len)));
      } else {
        (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
      }
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x2c\x20\x6d\x6f\x64\x65\x3d"))));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, tag)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x29"))));
    (void)(driver_diag_note(&((msg)[0])));
  }
  (void)(0);
  return;
}
void driver_diagnostic_parse_commit_fail(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name) {
  if ((driver_diag_parse_debug_enabled() ==0)) {
    return;
  }
  {
    uint8_t * tag = ((uint8_t *)"\x73\x74\x72\x69\x63\x74");
    if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x41\x52\x53\x45")) !=((uint8_t *)(0)))) {
      (void)((tag = ((uint8_t *)"\x64\x65\x62\x75\x67")));
    }
    uint8_t msg[256] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 256, 0, ((uint8_t *)"\x2e\x78\x20\x70\x61\x72\x73\x65\x20\x63\x6f\x6d\x6d\x69\x74\x20\x66\x61\x69\x6c\x65\x64\x20\x61\x74\x20\x62\x79\x74\x65\x20"));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 256, at, byte_pos)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x20\x28\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 256, at, num_funcs_so_far)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x2c\x20\x6e\x61\x6d\x65\x3d"))));
    if ((name !=((uint8_t *)(0)))) {
      if ((name_len > 0)) {
        if ((name_len < 64)) {
          (void)((at = driver_diag_append_name(&((msg)[0]), 256, at, name, name_len)));
        } else {
          (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x3f"))));
        }
      } else {
        (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x3f"))));
      }
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x3f"))));
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x2c\x20\x6d\x6f\x64\x65\x3d"))));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, tag)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x29"))));
    if ((lsp_diag_get_enabled() !=0)) {
      (void)(lsp_diag_add_code(1, 1, 1, ((uint8_t *)"\x58\x50\x30\x30\x32"), &((msg)[0])));
      return;
    }
    if ((driver_check_only_get() !=0)) {
      (void)(driver_check_diag_emitted_note());
    }
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x58\x50\x30\x30\x32"), &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
void driver_diagnostic_parse_func_generic(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t num_generic_params, int32_t is_main) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x41\x52\x53\x45\x5f\x47\x45\x4e\x45\x52\x49\x43")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x67\x65\x6e\x65\x72\x69\x63\x20\x64\x65\x62\x75\x67\x3a\x20\x62\x79\x74\x65\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, byte_pos)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, num_funcs_so_far)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x67\x65\x6e\x65\x72\x69\x63\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, num_generic_params)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x69\x73\x5f\x6d\x61\x69\x6e\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, is_main)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x6e\x61\x6d\x65\x3d"))));
  if ((name !=((uint8_t *)(0)))) {
    if ((name_len > 0)) {
      (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, name, name_len)));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
    }
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
  }
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_parser_onefunc_param_ref(uint8_t * func_name, int32_t func_name_len, uint8_t * param_name, int32_t param_name_len, int32_t stage, int32_t param_idx, int32_t type_ref) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x50\x41\x52\x53\x45\x5f\x50\x41\x52\x41\x4d")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t msg[240] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 240, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x72\x20\x70\x61\x72\x61\x6d\x20\x64\x65\x62\x75\x67\x3a\x20\x66\x75\x6e\x63\x3d"));
  if ((func_name !=((uint8_t *)(0)))) {
    if ((func_name_len > 0)) {
      (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, func_name, func_name_len)));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
    }
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x73\x74\x61\x67\x65\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, stage)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x70\x61\x72\x61\x6d\x5f\x69\x64\x78\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, param_idx)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x70\x61\x72\x61\x6d\x3d"))));
  if ((param_name !=((uint8_t *)(0)))) {
    if ((param_name_len > 0)) {
      (void)((at = driver_diag_append_name(&((msg)[0]), 240, at, param_name, param_name_len)));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
    }
  } else {
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x3f"))));
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 240, at, ((uint8_t *)"\x20\x74\x79\x70\x65\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 240, at, type_ref)));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_typeck_import_const_must_be_qualified(int32_t line, int32_t col, uint8_t * name, int32_t name_len, uint8_t * binding, int32_t binding_len) {
  uint8_t msg[280] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 280, 0, ((uint8_t *)"\x69\x6d\x70\x6f\x72\x74\x20\x63\x6f\x6e\x73\x74\x61\x6e\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, name, name_len)));
  if ((binding !=((uint8_t *)(0)))) {
    if ((binding_len > 0)) {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x27\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x71\x75\x61\x6c\x69\x66\x69\x65\x64\x3b\x20\x75\x73\x65\x20"))));
      (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, binding, binding_len)));
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x2e"))));
      (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, name, name_len)));
      (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
      return;
    }
  }
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 280, at, ((uint8_t *)"\x27\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x71\x75\x61\x6c\x69\x66\x69\x65\x64\x20\x61\x73\x20\x62\x69\x6e\x64\x69\x6e\x67\x2e"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 280, at, name, name_len)));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
}
void driver_diagnostic_warn_pad_fields_same_cache_line(uint8_t * sname, int32_t sname_len, uint8_t * f0, int32_t f0_len, uint8_t * f1, int32_t f1_len) {
  uint8_t msg[384] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 384, 0, ((uint8_t *)"\x2d\x70\x61\x64\x2d\x66\x69\x65\x6c\x64\x73\x3a\x20\x73\x74\x72\x75\x63\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 384, at, sname, sname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x27\x20\x66\x69\x65\x6c\x64\x73\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 384, at, f0, f0_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x27\x20\x61\x6e\x64\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 384, at, f1, f1_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x27\x20\x73\x68\x61\x72\x65\x20\x61\x20\x36\x34\x2d\x62\x79\x74\x65\x20\x63\x61\x63\x68\x65\x20\x6c\x69\x6e\x65\x3b\x20"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x63\x6f\x6e\x73\x69\x64\x65\x72\x20\x61\x6c\x69\x67\x6e\x28\x36\x34\x29\x20\x74\x6f\x20\x61\x76\x6f\x69\x64\x20\x66\x61\x6c\x73\x65\x20\x73\x68\x61\x72\x69\x6e\x67"))));
  if ((lsp_diag_get_enabled() !=0)) {
    (void)(lsp_diag_add(1, 1, 2, &((msg)[0])));
    return;
  }
  (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x77\x61\x72\x6e\x69\x6e\x67"), &((msg)[0]), ((uint8_t *)(0))));
}
void driver_diagnostic_warn_hot_reorder_field(uint8_t * sname, int32_t sname_len, uint8_t * hot, int32_t hot_len, uint8_t * cold, int32_t cold_len) {
  uint8_t msg[256] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 256, 0, ((uint8_t *)"\x2d\x68\x6f\x74\x2d\x72\x65\x6f\x72\x64\x65\x72\x3a\x20\x73\x74\x72\x75\x63\x74\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 256, at, sname, sname_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x27\x3a\x20\x63\x6f\x6e\x73\x69\x64\x65\x72\x20\x6d\x6f\x76\x69\x6e\x67\x20\x68\x6f\x74\x20\x66\x69\x65\x6c\x64\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 256, at, hot, hot_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x27\x20\x62\x65\x66\x6f\x72\x65\x20\x27"))));
  (void)((at = driver_diag_append_name(&((msg)[0]), 256, at, cold, cold_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 256, at, ((uint8_t *)"\x27"))));
  if ((lsp_diag_get_enabled() !=0)) {
    (void)(lsp_diag_add(1, 1, 2, &((msg)[0])));
    return;
  }
  (void)(diag_report(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x77\x61\x72\x6e\x69\x6e\x67"), &((msg)[0]), ((uint8_t *)(0))));
}
void driver_diagnostic_hint_unused_binding(int32_t line, int32_t col, uint8_t * name, int32_t name_len) {
  uint8_t msg[160] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 160, 0, ((uint8_t *)"\x75\x6e\x75\x73\x65\x64\x20\x62\x69\x6e\x64\x69\x6e\x67\x20\x27"));
  (void)((at = driver_diag_append_name(&((msg)[0]), 160, at, name, name_len)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 160, at, ((uint8_t *)"\x27"))));
  {
    int32_t ln = line;
    int32_t cl = col;
    if ((ln <=0)) {
      (void)((ln = 1));
    }
    if ((cl <=0)) {
      (void)((cl = 1));
    }
    if ((lsp_diag_get_enabled() !=0)) {
      (void)(lsp_diag_add(ln, cl, 3, &((msg)[0])));
      return;
    }
    (void)(diag_report(((uint8_t *)(0)), ln, cl, ((uint8_t *)"\x69\x6e\x66\x6f"), &((msg)[0]), ((uint8_t *)(0))));
  }
}
void driver_diagnostic_typeck_binop_operands(int32_t expr_ref, int32_t left_ref, int32_t right_ref, int32_t left_kind, int32_t right_kind, int32_t left_block_ref, int32_t right_block_ref, int32_t left_ty_ref, int32_t right_ty_ref, uint8_t * left_ty, int32_t left_ty_len, uint8_t * right_ty, int32_t right_ty_len) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x54\x59\x50\x45\x43\x4b\x5f\x42\x49\x4e\x4f\x50")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t left_buf[112] = {};
  uint8_t right_buf[112] = {};
  (void)(driver_diag_fill_expr_part(&((left_buf)[0]), 112, left_ty, left_ty_len));
  (void)(driver_diag_fill_expr_part(&((right_buf)[0]), 112, right_ty, right_ty_len));
  uint8_t msg[384] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 384, 0, ((uint8_t *)"\x74\x79\x70\x65\x63\x6b\x20\x62\x69\x6e\x6f\x70\x20\x64\x65\x62\x75\x67\x3a\x20\x65\x78\x70\x72\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, expr_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x6c\x65\x66\x74\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, left_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x6c\x65\x66\x74\x5f\x6b\x69\x6e\x64\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, left_kind)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x6c\x65\x66\x74\x5f\x62\x6c\x6f\x63\x6b\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, left_block_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x6c\x65\x66\x74\x5f\x74\x79\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, left_ty_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x6c\x65\x66\x74\x5f\x74\x79\x3d"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, &((left_buf)[0]))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x72\x69\x67\x68\x74\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, right_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x72\x69\x67\x68\x74\x5f\x6b\x69\x6e\x64\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, right_kind)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x72\x69\x67\x68\x74\x5f\x62\x6c\x6f\x63\x6b\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, right_block_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x72\x69\x67\x68\x74\x5f\x74\x79\x5f\x72\x65\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 384, at, right_ty_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, ((uint8_t *)"\x20\x72\x69\x67\x68\x74\x5f\x74\x79\x3d"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 384, at, &((right_buf)[0]))));
  (void)(driver_diag_note(&((msg)[0])));
}
void driver_diagnostic_parse_commit_shape(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t phase, int32_t block_ref, int32_t pool_num_consts, int32_t pool_num_lets, int32_t pool_num_ifs, int32_t pool_num_regions, int32_t pool_num_stmt_order, int32_t block_num_consts, int32_t block_num_lets, int32_t block_num_ifs, int32_t block_num_regions, int32_t block_num_stmt_order, int32_t final_expr_ref) {
  if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x41\x52\x53\x45\x5f\x43\x4f\x4d\x4d\x49\x54")) ==((uint8_t *)(0)))) {
    return;
  }
  uint8_t namebuf[72] = {};
  (void)(driver_diag_fill_expr_part(&((namebuf)[0]), 72, name, name_len));
  uint8_t * phase_name = ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e");
  if ((phase ==0)) {
    (void)((phase_name = ((uint8_t *)"\x70\x72\x65\x5f\x66\x69\x6c\x6c")));
  } else {
    if ((phase ==1)) {
      (void)((phase_name = ((uint8_t *)"\x70\x6f\x73\x74\x5f\x62\x6c\x6f\x63\x6b")));
    }
  }
  uint8_t msg[512] = {};
  int32_t at = driver_diag_append_cstr(&((msg)[0]), 512, 0, ((uint8_t *)"\x70\x61\x72\x73\x65\x20\x63\x6f\x6d\x6d\x69\x74\x20\x64\x65\x62\x75\x67\x3a\x20\x62\x79\x74\x65\x3d"));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, byte_pos)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, num_funcs_so_far)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x70\x68\x61\x73\x65\x3d"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, phase_name)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x62\x6c\x6f\x63\x6b\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x70\x6f\x6f\x6c\x28\x63\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, pool_num_consts)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x6c\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, pool_num_lets)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x69\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, pool_num_ifs)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x72\x65\x67\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, pool_num_regions)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x73\x6f\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, pool_num_stmt_order)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x29\x20\x62\x6c\x6f\x63\x6b\x28\x63\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_num_consts)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x6c\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_num_lets)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x69\x66\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_num_ifs)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x72\x65\x67\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_num_regions)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x73\x6f\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, block_num_stmt_order)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x20\x66\x69\x6e\x3d"))));
  (void)((at = driver_diag_append_i32(&((msg)[0]), 512, at, final_expr_ref)));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, ((uint8_t *)"\x29\x20\x6e\x61\x6d\x65\x3d"))));
  (void)((at = driver_diag_append_cstr(&((msg)[0]), 512, at, &((namebuf)[0]))));
  (void)(driver_diag_note(&((msg)[0])));
}
void parser_diagnostic_parse_commit_shape(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t phase, int32_t block_ref, int32_t pool_num_consts, int32_t pool_num_lets, int32_t pool_num_ifs, int32_t pool_num_regions, int32_t pool_num_stmt_order, int32_t block_num_consts, int32_t block_num_lets, int32_t block_num_ifs, int32_t block_num_regions, int32_t block_num_stmt_order, int32_t final_expr_ref) {
  (void)(driver_diagnostic_parse_commit_shape(byte_pos, num_funcs_so_far, name, name_len, phase, block_ref, pool_num_consts, pool_num_lets, pool_num_ifs, pool_num_regions, pool_num_stmt_order, block_num_consts, block_num_lets, block_num_ifs, block_num_regions, block_num_stmt_order, final_expr_ref));
}
/* wave302 G.7: parse_commit_pre/post cold twin — pure authority thin.x; dual-export ban
 * vs pipeline_glue_strict_minimal (body deleted there). PLATFORM: SHARED.
 * Incomplete struct — ABI matches parser ASTArena*; no layout read here. */
struct ast_ASTArena;
void parser_diagnostic_parse_commit_pre(struct ast_ASTArena *arena, uint8_t *name, int32_t name_len,
                                        int32_t block_ref, uint8_t *pool, int32_t final_expr_ref) {
  extern int32_t pipeline_onefunc_num_consts(uint8_t *out);
  extern int32_t pipeline_onefunc_num_lets(uint8_t *out);
  extern int32_t pipeline_onefunc_num_if_stmts(uint8_t *out);
  extern int32_t pipeline_onefunc_num_regions(uint8_t *out);
  extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t *out);
  (void)arena;
  driver_diagnostic_parse_commit_shape(0, 0, name, name_len, 0, block_ref,
                                       pool ? pipeline_onefunc_num_consts(pool) : 0,
                                       pool ? pipeline_onefunc_num_lets(pool) : 0,
                                       pool ? pipeline_onefunc_num_if_stmts(pool) : 0,
                                       pool ? pipeline_onefunc_num_regions(pool) : 0,
                                       pool ? pipeline_onefunc_num_src_stmt_order(pool) : 0,
                                       0, 0, 0, 0, 0, final_expr_ref);
}
void parser_diagnostic_parse_commit_post(struct ast_ASTArena *arena, uint8_t *name, int32_t name_len,
                                         int32_t block_ref, uint8_t *pool) {
  extern int32_t pipeline_onefunc_num_consts(uint8_t *out);
  extern int32_t pipeline_onefunc_num_lets(uint8_t *out);
  extern int32_t pipeline_onefunc_num_if_stmts(uint8_t *out);
  extern int32_t pipeline_onefunc_num_regions(uint8_t *out);
  extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t *out);
  extern int32_t ast_ast_block_num_consts(struct ast_ASTArena *a, int32_t block_ref);
  extern int32_t ast_ast_block_num_lets(struct ast_ASTArena *a, int32_t block_ref);
  extern int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena *a, int32_t block_ref);
  extern int32_t ast_ast_block_num_regions(struct ast_ASTArena *a, int32_t block_ref);
  extern int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena *a, int32_t block_ref);
  extern int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena *a, int32_t block_ref);
  driver_diagnostic_parse_commit_shape(0, 0, name, name_len, 1, block_ref,
                                       pool ? pipeline_onefunc_num_consts(pool) : 0,
                                       pool ? pipeline_onefunc_num_lets(pool) : 0,
                                       pool ? pipeline_onefunc_num_if_stmts(pool) : 0,
                                       pool ? pipeline_onefunc_num_regions(pool) : 0,
                                       pool ? pipeline_onefunc_num_src_stmt_order(pool) : 0,
                                       arena ? ast_ast_block_num_consts(arena, block_ref) : 0,
                                       arena ? ast_ast_block_num_lets(arena, block_ref) : 0,
                                       arena ? ast_ast_block_num_if_stmts(arena, block_ref) : 0,
                                       arena ? ast_ast_block_num_regions(arena, block_ref) : 0,
                                       arena ? ast_ast_block_num_stmt_order(arena, block_ref) : 0,
                                       arena ? ast_ast_block_final_expr_ref(arena, block_ref) : 0);
}
void driver_diagnostic_after_entry_parse_module(uint8_t * module) {
  {
    int32_t nf = pipeline_module_num_funcs(module);
    int32_t ndef = 0;
    int32_t next = 0;
    int32_t i = 0;
    uint8_t msg[200] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x61\x66\x74\x65\x72\x5f\x65\x6e\x74\x72\x79\x5f\x70\x61\x72\x73\x65\x20\x6e\x75\x6d\x5f\x66\x75\x6e\x63\x73\x3d"));
    uint8_t * m = module;
    int32_t ntl = (((((int32_t)((m)[12])) | (((int32_t)((m)[13])) <<8)) | (((int32_t)((m)[14])) <<16)) | (((int32_t)((m)[15])) <<24));
    uint8_t msg2[120] = {};
    int32_t at2 = driver_diag_append_cstr(&((msg2)[0]), 120, 0, ((uint8_t *)"\x70\x69\x70\x65\x6c\x69\x6e\x65\x20\x64\x65\x62\x75\x67\x3a\x20\x61\x66\x74\x65\x72\x5f\x65\x6e\x74\x72\x79\x5f\x70\x61\x72\x73\x65\x20\x6e\x75\x6d\x5f\x74\x6f\x70\x5f\x6c\x65\x76\x65\x6c\x5f\x6c\x65\x74\x73\x3d"));
    if ((link_abi_getenv(((uint8_t *)"\x53\x48\x55\x58\x5f\x44\x45\x42\x55\x47\x5f\x50\x49\x50\x45")) ==((uint8_t *)(0)))) {
      return;
    }
    if ((module ==((uint8_t *)(0)))) {
      return;
    }
    while ((i < nf)) {
      if ((pipeline_module_func_is_extern_at(module, i) !=0)) {
        (void)((next = (next + 1)));
      } else {
        (void)((ndef = (ndef + 1)));
      }
      (void)((i = (i + 1)));
    }
    (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, nf)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x6e\x75\x6d\x5f\x64\x65\x66\x69\x6e\x65\x64\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, ndef)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x20\x6e\x75\x6d\x5f\x65\x78\x74\x65\x72\x6e\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, next)));
    (void)(driver_diag_note(&((msg)[0])));
    (void)((at2 = driver_diag_append_i32(&((msg2)[0]), 120, at2, ntl)));
    (void)(driver_diag_note(&((msg2)[0])));
  }
  (void)(0);
  return;
}
void driver_diagnostic_codegen_emit_func_fail(uint8_t * module, int32_t func_index) {
  {
    int32_t nl = pipeline_module_func_name_len_at(module, func_index);
    uint8_t namebuf[80] = {};
    int32_t out_i = 0;
    int32_t k = 0;
    uint8_t msg[200] = {};
    int32_t at = driver_diag_append_cstr(&((msg)[0]), 200, 0, ((uint8_t *)"\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x65\x6d\x69\x74\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x27"));
    if ((module ==((uint8_t *)(0)))) {
      return;
    }
    if ((func_index < 0)) {
      return;
    }
    while (((k < nl) && (k < 72))) {
      (void)(((namebuf)[out_i] = pipeline_module_func_name_byte_at(module, func_index, k)));
      (void)((out_i = (out_i + 1)));
      (void)((k = (k + 1)));
    }
    (void)(((namebuf)[out_i] = 0));
    if ((out_i > 0)) {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, &((namebuf)[0]))));
    } else {
      (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x3f"))));
    }
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x27\x20\x28\x69\x64\x78\x3d"))));
    (void)((at = driver_diag_append_i32(&((msg)[0]), 200, at, func_index)));
    (void)((at = driver_diag_append_cstr(&((msg)[0]), 200, at, ((uint8_t *)"\x29"))));
    if ((driver_check_only_get() !=0)) {
      (void)(driver_check_diag_emitted_note());
    }
    (void)(diag_report_with_code(((uint8_t *)(0)), 0, 0, ((uint8_t *)"\x63\x6f\x64\x65\x67\x65\x6e\x20\x65\x72\x72\x6f\x72"), ((uint8_t *)"\x43\x47\x30\x30\x33"), &((msg)[0]), ((uint8_t *)(0))));
  }
  (void)(0);
  return;
}
int32_t runtime_driver_diagnostic_slice_marker(void) {
  return 1;
}
